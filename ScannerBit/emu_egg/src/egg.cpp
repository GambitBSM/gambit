#include <mpi.h>
// #include <stdio.h>
// #include <cstring> // For strlen
// #include <sstream> // For stringstream
#include <csignal>
// #include "egg.hpp"
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/static_members.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Utils/signal_helpers.hpp"
#include "gambit/Utils/signal_handling.hpp"
// #include "gambit/Core/yaml_parser.hpp"
#include "yaml-cpp/yaml.h"

// #include "gambit/Utils/signal_handling.hpp"
// #include "gambit/Utils/static_members.hpp"
// #include "src/new_mpi_datatypes.cpp"

// using namespace Gambit;
using namespace Gambit;

int main(int argc, char *argv[])
{

    std::cout << "egg.cpp. I am Here 1" << std::endl; // TODO: Debugging

    GMPI::Init();

    std::cout << "egg.cpp. I am Here 2" << std::endl; // TODO: Debugging

    GMPI::Comm errorComm;
    errorComm.dup(MPI_COMM_WORLD,"errorComm"); // duplicates the COMM_WORLD context
    const int ERROR_TAG=1;         // Tag for error messages
    errorComm.mytag = ERROR_TAG;
    signaldata().set_MPI_comm(&errorComm);

    std::cout << "egg.cpp. I am here 2.5" << std::endl;
    


    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::cout << "egg.cpp. I am Here 3" << std::endl; // TODO: Debugging
    std::cout << "egg.cpp. world_rank: " << world_rank << ", world_size: " << world_size << std::endl; // TODO: Debugging


    //////// split to create local communicators
    // TODO: recieve color from rank 0
    std::vector<int> processes = {2,3};
    GMPI::Comm emuComm(processes, "emuComm");

    std::cout << "egg.cpp. I am Here 4" << std::endl; // TODO: Debugging

    // find local rank
    int local_rank = emuComm.Get_rank();
    int local_size = emuComm.Get_size();

    std::cout  << "In egg:   world rank " << world_rank<< ", local rank " << local_rank << ", local size " << local_size << std::endl;

    /////// Read yaml node

    // Read YAML file, which also initialises the logger.
    const str filename = "yaml_files/spartan.yaml";

    YAML::Node settings = YAML::LoadFile(filename);

    YAML::Node emulator_node =settings["Emulation"];

    std::cerr << "here: " << YAML::Dump(emulator_node) << std::endl;

    str capability = emulator_node["use_emulator"].as<str>();
    str plugin_name = emulator_node["emulators"][capability]["plugin"].as<str>();

    std::cout << "In egg.cpp: capability = " << capability << " and plugin name = "<<plugin_name << std::endl;


    /////// send plugin info to world rank 0

    // get plugin name from arguments
    // char* plugin_name = argv[1];

    // add the worldrank to the back of the plugin-name before sending
    std::ostringstream oss;
    oss << capability << " " << world_rank;
    std::string message = oss.str();

    // send plugin name and world rank to gambit processes
    std::cout <<"In egg: " << message  << " # " << message.length()+1 << std::endl;
    if (local_rank == 0)
    {
        std::cout << " egg.cpp: In here 5, loop over " << world_size-local_size << std::endl;
        for (int i = 0; i < world_size-local_size; i++)
        {
            std::cout << " sending message of size " << message.length() << " to " << i << std::endl;
            MPI_Send(message.c_str(), message.length() +1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }

    std::cout << "In egg, sent messages " << std::endl;

    ///// Listen to messages either for tasks or for shut down 
    bool finished = false;

    while (!finished)
    {
        if (local_rank == 0)
        {
            MPI_Status status;
            int receiver_size;
            int flag;
            MPI_Iprobe(MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &flag, &status);
            if (flag && status.MPI_TAG != 0)
            {
                std::cout << "######################### " <<status.MPI_TAG << std::endl;
                MPI_Get_count(&status, MPI_CHAR, &receiver_size);

                char *my_string = new char[receiver_size];

                MPI_Recv(my_string, receiver_size, MPI_CHAR, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                std::cout << " ####### " << my_string << std::endl;
            }
        }

        finished = signaldata().check_if_shutdown_begun();
    }

    ////// Shut down egg

    std::cout << "rank " << local_rank <<" got shut down" << std::endl;

    signaldata().broadcast_shutdown_signal(SignalData::NO_MORE_MESSAGES);

    GMPI::Finalize();

    

    //////////////// Actuall egg stuff (sketch)
    
    ///////// read yaml file to get emulator plugin name and options
    // std::cout << "Filename: " << argv[2] << std::endl;
    // YAML::Node node = YAML::LoadFile(argv[2])["Emulation"];
    // std::cout << "Number of emulators: " << node.size() << std::endl;
    // for (int i = 0; i < node.size(); ++i)
    // {
    //     std::cout << "Capabilitiy: " <<  node[i]["capability"] << std::endl; 
    //     std::cout << "Plugin name: " <<  node[i]["emulator_plugin"] << std::endl; 
    // }

    // TODO: send plugin message to rank 0 after checking that plugin exists / works


    //////////// initialize emulator plugins

    /////////// Send and recieve
    // // TODO:  make while loop that continues to recieve

    // // Prepare to recieve datapoints
    // Scanner::Emulator::feed_def receiver;

    // // probe to find receiver size
    // int receiver_size;
    // MPI_Status status;
    // MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, parentcomm, &status);
    // MPI_Get_count(&status, MPI_CHAR, &receiver_size);

    // // resize receiver
    // receiver.resize(receiver_size);

    // // recieve data
    // MPI_Recv(receiver.buffer.data(), receiver_size, MPI_CHAR, 0, 0, parentcomm, MPI_STATUS_IGNORE);
        
    // if (receiver.if_train() && rank==0)
    // {
    //     std::cout << "doing training" << std::endl;
    //     // add training point to training buffer

    //     // check if training buffer is full
    // }
    // else if (receiver.if_predict() && rank == 1)
    // {
    //     std::cout << "doing predict" << std::endl;
    //     // call plugin to do predict

    //     // send results
    //     std::vector<double> pred = {-100.2};
    //     std::vector<double> pred_u = {1.2};

    //     // make new buffer with size 0 for the input parameters
    //     std::vector<unsigned int> sizes = {0, 1, 1};
    //     Scanner::Emulator::feed_def answer_buffer(sizes);

    //     // populate answer_buffer
    //     answer_buffer.add_for_result(pred, pred_u);

    //     // send to parent
    //     MPI_Send(answer_buffer.buffer.data(), answer_buffer.buffer.size(), MPI_CHAR, 0, 0, parentcomm);
    // }
    

    // MPI_Finalize();
    return 0;
}
