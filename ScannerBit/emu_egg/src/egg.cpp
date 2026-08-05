#include <mpi.h>
#include <csignal>
// #include "egg.hpp"
#include "gambit/ScannerBit/py_module.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/static_members.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Utils/signal_helpers.hpp"
#include "gambit/Utils/signal_handling.hpp"
#include "gambit/Utils/yaml_parser_base.hpp"
#include "yaml-cpp/yaml.h"
#include "gambit/ScannerBit/plugin_interface.hpp"
#include "gambit/ScannerBit/plugin_factory.hpp"
#include "gambit/ScannerBit/emulator_utils.hpp"
#include "gambit/ScannerBit/scanner_util_types.hpp"


// using namespace Gambit;
using namespace Gambit;
using namespace Gambit::Scanner;
using Gambit::Scanner::map_vector;
using Gambit::Scanner::vector;

int main(int argc, char *argv[])
{
    //////////// Initializing ///////////////////
    // initialize MPI
    GMPI::Init();

    // make errorComm
    GMPI::Comm errorComm;
    errorComm.dup(MPI_COMM_WORLD,"errorComm"); // duplicates the COMM_WORLD context
    const int ERROR_TAG=1;         // Tag for error messages
    errorComm.mytag = ERROR_TAG;
    signaldata().set_MPI_comm(&errorComm);

    /////// Read yaml file and capability
    // read terminal input and extract capability and yaml file
    std::unordered_map<str, str> argsMap;
    if ( argc >= 3) {
        for (int i = 1; i < argc; i += 2) 
        {
            str key = argv[i];
            str value = argv[i + 1];
            argsMap[key] = value;
        }
    }
    else
    {
        std::cerr << "egg: too few arguments (" << argc << " given, need at least "
                     "'-c <CapabilityName>'). Aborting the whole MPI job." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Get plugin capability
    str capability = argsMap["-c"];

    int* appnum;
    int flag;
    MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_APPNUM, &appnum, &flag);
    if (!flag)
    {
        std::cerr << "egg: MPI_APPNUM is not set on this communicator. "
                     "egg must be launched as part of an MPMD job (colon "
                     "syntax, e.g. 'mpirun -n N gambit ... : -n M egg ...'). "
                     "Aborting the whole MPI job." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    int my_process_color = 1+*appnum;
    

    //////////////// Make emulator communicators to give to plugin /////////////////

    // get world size/rank
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // check number of processes in egg
    std::vector<int> all_process_colors(world_size);
    MPI_Allgather(&my_process_color, 1, MPI_INT, all_process_colors.data(), 1, MPI_INT, MPI_COMM_WORLD);

    // extact processes with my process color
    // processes with color 1 belong to gambit executable
    int numberOfGambitProcesses = 0;
    std::vector<int> emuProcesses;
    for (int i = 0; i < world_size; ++i) 
    { 
        if (all_process_colors[i] == my_process_color) {emuProcesses.push_back(i);}
        if (all_process_colors[i] == 1) {++numberOfGambitProcesses;}
    }

    //////// split the communicator
    GMPI::Comm emuComm(emuProcesses, "emuComm");
   
    // find local rank/size
    int local_rank = emuComm.Get_rank();
    // int local_size = emuComm.Get_size();

    /////// send plugin info to world rank 0
    // add the worldrank to the back of the plugin-name before sending
    std::ostringstream oss;
    oss << capability << " " << world_rank;
    std::string message = oss.str();

    // send plugin name and world rank to gambit processes
    for (int i = 0; i < numberOfGambitProcesses; i++)
    {
        MPI_Send(message.c_str(), message.length() +1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
    }

    //////// Get yaml file
    str filename;
    int msg_size;

    // get size
    MPI_Bcast(&msg_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    filename.resize(msg_size);

    // get yaml filename
    MPI_Bcast(filename.data(), msg_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    // read yaml file
    IniParser::Parser iniFile;
    iniFile.readFile(filename);

    // Check if user wants to disable use of MPI_Abort (mirrors gambit.cpp's
    // reading of the same yaml key, so egg behaves consistently with the rest
    // of the MPMD job on an emergency shutdown)
    bool use_mpi_abort = iniFile.getValueOrDef<bool>(true, "use_mpi_abort");

    // get emulator node
    YAML::Node emulator_node = iniFile.getEmulationNode();
    str plugin_name = emulator_node["emulators"][capability]["plugin"].as<str>();
    Plugins::plugin_info.iniFile(emulator_node);
    
    ////////// Make plugin

    Scanner::Plugins::plugin_info.initMPIdata(&emuComm);
    Plugins::Plugin_Interface<void (map_vector<double> , map_vector<double> , map_vector<double>, unsigned short int &), std::pair<vector<double>, vector<double>> (map_vector<double>, unsigned short int &)> plugin_interface("emulator", capability);
    std::cout << "made plugin " << std::endl;

    ///////// Recieve messages from gambit

    // containers for the NN "emulator"
    std::vector<std::vector<double>> parameters;
    std::vector<double> likes;

    // keep going until shutdown
    bool finished = false;
    bool allow_finalize = true;
    try
    {
    while (!finished)
    {
        // Probe for incomming message with tag 3 ( 3 = train/predict )
        MPI_Status status;
        int flag;
        MPI_Iprobe(MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &flag, &status);

        // if message with tag 3, accept it
        if (flag && status.MPI_TAG == 3)
        {
            // get size of buffer
            int receiver_size;
            MPI_Get_count(&status, MPI_CHAR, &receiver_size);

            // Prepare to recieve datapoints
            Scanner::Emulator::feed_def receiver;
            MPI_Status status_recv;

            // resize receiver
            receiver.resize(receiver_size);

            // recieve data
            MPI_Recv(receiver.buffer.data(), receiver_size, MPI_CHAR, status.MPI_SOURCE, 3, MPI_COMM_WORLD, &status_recv);

            // Malformed/truncated message:
            if (!receiver.has_valid_header())
            {
                std::cerr << "egg: received a malformed/truncated message (" << receiver_size
                          << " bytes) from rank " << status_recv.MPI_SOURCE
                          << " -- too small to hold its own header." << std::endl;

                // We can still tell train from predict as long as at least the flag
                // itself is readable (2 bytes); a predict request must always get a reply 
                if (receiver.buffer.size() >= sizeof(unsigned short int) && receiver.if_predict())
                {
                    std::vector<unsigned int> error_sizes = {0, 0, 0};
                    Scanner::Emulator::feed_def error_buffer(error_sizes);
                    error_buffer.set_result();
                    error_buffer.set_not_valid();
                    error_buffer.set_protocol_error();
                    MPI_Send(error_buffer.buffer.data(), error_buffer.buffer.size(), MPI_CHAR, status_recv.MPI_SOURCE, 4, MPI_COMM_WORLD);
                    std::cerr << "egg: sent a PROTOCOL_ERROR reply to rank " << status_recv.MPI_SOURCE << "." << std::endl;
                }
                else
                {
                    std::cerr << "egg: message too small to even determine train vs. predict -- dropping it." << std::endl;
                }

                continue;
            }

            // Train, add point to buffer
            if (receiver.if_train())
            {
                // extract parameters
                auto params = receiver.params();
                auto target = receiver.target();
                auto target_uncertainty = receiver.target_uncertainty();

                plugin_interface(params, target, target_uncertainty, receiver.flag());
            }
            // Predict, ask for prediction and send
            else if (receiver.if_predict())
            {
                // extract parameters
                auto params = receiver.params();
                unsigned short int flag = receiver.flag();
                auto pred = plugin_interface(params, flag);

                // if result is returned, send reply
                if (flag & Scanner::Emulator::feed_def::RESULT)
                {
                    // make new buffer with size 0 for the input parameters
                    std::vector<unsigned int> sizes = {0, (unsigned int)pred.first.size(), (unsigned int)pred.second.size()};
                    Scanner::Emulator::feed_def answer_buffer(sizes);
                    answer_buffer.flag() = flag;
                    answer_buffer.set_result(); // always reply, even if the result is invalid

                    // populate answer_buffer
                    answer_buffer.add_for_result(pred.first, pred.second);

                    // send to process it arrived from ( tag 4 = results )
                    MPI_Send(answer_buffer.buffer.data(), answer_buffer.buffer.size(), MPI_CHAR, status_recv.MPI_SOURCE, 4, MPI_COMM_WORLD);
                }
            }
        }
        
        // Always listen to messages for shut down 
        finished = signaldata().check_if_shutdown_begun();
    }

    ////// Shut down egg
    std::cout << "rank " << local_rank <<" got shut down" << std::endl;
    signaldata().broadcast_shutdown_signal(SignalData::NO_MORE_MESSAGES);
    }
    catch (const MPIShutdownException& e)
    {
        std::cerr << "egg: shutting down due to an emergency shutdown signal "
                     "from another process: " << e.what() << std::endl;
        allow_finalize = GMPI::PrepareForFinalizeWithTimeout(use_mpi_abort);
    }

    if (allow_finalize) GMPI::Finalize();

    return 0;
}
