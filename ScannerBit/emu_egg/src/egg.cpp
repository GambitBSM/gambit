#include <mpi.h>
#include <csignal>
#include <getopt.h>
#include <functional>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
#include <sstream>
#include <algorithm>
#include "gambit/Utils/output_path.hpp"
#include "gambit/Utils/util_functions.hpp"
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


/// Per-rank performance log for egg, written in the same style as the gambit log files
/// (<default_output_path>/logs/egg_<capability>.log_<world rank>). Every 'interval' seconds one entry
/// is written with the cumulative message counts and the cumulative time spent in each part of the
/// receive loop, plus the mean/max time of the train and predict calls since the previous entry.
/// Compare the counts between ranks (and with what gambit sent, see the send entries in the gambit
/// logs) to see how well each rank keeps up.
struct EggStats
{
    std::ofstream out;
    std::string capability;
    int world_rank;
    double interval;
    double t_start, t_last_write;
    std::chrono::system_clock::time_point start_time;

    // cumulative
    unsigned long n_train = 0, n_predict = 0, n_reply = 0, n_malformed = 0, bytes_recv = 0;
    double t_probe = 0, t_idle = 0, t_recv = 0, t_train = 0, t_predict = 0, t_reply = 0, t_shutdown = 0;
    unsigned long n_shutdown_checks = 0;

    // current interval (train/predict call durations)
    unsigned long i_train = 0, i_predict = 0;
    double i_train_sum = 0, i_train_max = 0, i_predict_sum = 0, i_predict_max = 0;

    EggStats(const std::string& filename, const std::string& cap, int rank, double interval_seconds)
      : capability(cap), world_rank(rank), interval(interval_seconds)
    {
        out.open(filename);
        t_start = t_last_write = MPI_Wtime();
        start_time = std::chrono::system_clock::now();
        if (out.is_open()) write_entry("Info", "egg rank started for capability '" + capability + "'.");
        else std::cerr << "egg: could not open performance log '" << filename << "' -- continuing without it." << std::endl;
    }

    /// Write one entry in gambit log style: (date)(seconds since start)(Rank)[tags]:\nmessage\n--<>-- separator
    void write_entry(const std::string& level, const std::string& message)
    {
        if (!out.is_open()) return;
        auto now = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = now - start_time;
        out << "(" << Utils::return_time_and_date(now) << ")(" << diff.count() << " [s])(Rank " << world_rank << ")"
            << "[Egg," << capability << "][" << level << "]:\n" << message << "\n"
            << "--<>--<>--<>--<>--<>--<>--<>--" << std::endl;
    }

    void add_train(double dt) { t_train += dt; ++i_train; i_train_sum += dt; i_train_max = std::max(i_train_max, dt); }
    void add_predict(double dt) { t_predict += dt; ++i_predict; i_predict_sum += dt; i_predict_max = std::max(i_predict_max, dt); }

    void tick(bool force = false)
    {
        double now = MPI_Wtime();
        if (!force && now - t_last_write < interval) return;
        t_last_write = now;
        std::ostringstream m;
        m << "stats: train_recv=" << n_train << " predict_recv=" << n_predict << " replies_sent=" << n_reply
          << " malformed=" << n_malformed << " bytes_recv=" << bytes_recv
          << " probe_s=" << t_probe << " idle_s=" << t_idle << " recv_s=" << t_recv
          << " train_s=" << t_train << " predict_s=" << t_predict << " reply_s=" << t_reply
          << " shutdown_check_s=" << t_shutdown << " shutdown_checks=" << n_shutdown_checks
          << " train_mean_ms=" << (i_train ? 1e3 * i_train_sum / i_train : 0.0) << " train_max_ms=" << 1e3 * i_train_max
          << " predict_mean_ms=" << (i_predict ? 1e3 * i_predict_sum / i_predict : 0.0) << " predict_max_ms=" << 1e3 * i_predict_max;
        write_entry("Info", m.str());
        i_train = i_predict = 0;
        i_train_sum = i_train_max = i_predict_sum = i_predict_max = 0;
    }
};

/// Print egg's usage information (mirrors gambit's own -h/--help output in Core/src/core.cpp)
void egg_bail(int rank)
{
    if (rank == 0)
    {
        std::cout << "\nusage: egg -c <CapabilityName> [options]                                   "
                     "\n                                                                           "
                     "\negg is the emulator-side MPI process launched alongside the gambit          "
                     "\nexecutable as part of an MPMD job. The gambit ranks must come first, e.g.:   "
                     "\n   mpirun -n N gambit -f <inifile> : -n M egg -c <CapabilityName>           "
                     "\n   srun --multi-prog <conf>   (conf: '0-N-1 gambit ...', 'N-N+M-1 egg -c ...')"
                     "\n                                                                           "
                     "\nOptions:                                                                   "
                     "\n   -c/--capability <name>   Name of the capability this egg instance        "
                     "\n                              trains/predicts for (required)                "
                     "\n   -h/--help                Display this usage information                 "
                     "\n" << std::endl;
    }
}

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

    /////// Parse command line options (mirrors gambit's own getopt_long usage in Core/src/core.cpp)
    str capability;
    bool found_capability = false;

    const struct option egg_options[] = {
        {"capability", required_argument, 0, 'c'},
        {"help",       no_argument,       0, 'h'},
        {0, 0, 0, 0},
    };

    int egg_rank = GMPI::Comm().Get_rank();
    int iarg = 0;
    int index;
    while (iarg != -1)
    {
        iarg = getopt_long(argc, argv, "c:h", egg_options, &index);
        switch (iarg)
        {
        case 'c':
            capability = optarg;
            found_capability = true;
            break;
        case 'h':
            egg_bail(egg_rank);
            GMPI::Finalize();
            return 0;
        case '?':
            egg_bail(egg_rank);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    if (!found_capability)
    {
        std::cerr << "egg: missing required argument '-c <CapabilityName>'. Aborting the whole MPI job." << std::endl;
        egg_bail(egg_rank);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Color egg ranks by capability (GAMBIT is always color 1), so that grouping does not
    // depend on MPI_APPNUM and works for any launcher (mpirun colon syntax, srun --multi-prog, ...).
    // Egg ranks with the same -c share an emulator communicator. Range [2, 1000001] avoids color 1.
    int my_process_color = 2 + static_cast<int>(std::hash<std::string>{}(capability) % 1000000);


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
    Plugins::Plugin_Interface<void (map_vector<double> , map_vector<double> , map_vector<double>, unsigned short int &, int), std::pair<vector<double>, vector<double>> (map_vector<double>, unsigned short int &, int)> plugin_interface("emulator", capability);
    std::cout << "made plugin " << std::endl;

    ///////// Recieve messages from gambit

    // containers for the NN "emulator"
    std::vector<std::vector<double>> parameters;
    std::vector<double> likes;

    // performance log: one file per egg rank in the run's output directory
    double stats_interval = emulator_node["emulators"][capability]["egg_log_interval"].IsDefined()
                          ? emulator_node["emulators"][capability]["egg_log_interval"].as<double>() : 10.0;
    EggStats stats(Utils::default_output_path() + "logs/egg_" + capability + ".log_" + std::to_string(world_rank), capability, world_rank, stats_interval);

    // How often (in seconds) to look for a shutdown message from gambit. The check is an extra MPI_Iprobe, which
    // is not free when many ranks talk to egg, so it is only done this often instead of after every message.
    // 0 = check after every message. Set with Emulation: emulators: <capability>: shutdown_check_interval
    double shutdown_check_interval = emulator_node["emulators"][capability]["shutdown_check_interval"].IsDefined()
                                   ? emulator_node["emulators"][capability]["shutdown_check_interval"].as<double>() : 0.1;
    double t_last_shutdown_check = MPI_Wtime();

    // keep going until shutdown
    bool finished = false;
    bool allow_finalize = true;
    try
    {
    while (!finished)
    {
        stats.tick();
        double t_loop = MPI_Wtime();

        // Probe for incomming message with tag 3 ( 3 = train/predict )
        MPI_Status status;
        int flag;
        MPI_Iprobe(MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &flag, &status);
        stats.t_probe += MPI_Wtime() - t_loop;

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
            double t_recv0 = MPI_Wtime();
            MPI_Recv(receiver.buffer.data(), receiver_size, MPI_CHAR, status.MPI_SOURCE, 3, MPI_COMM_WORLD, &status_recv);
            stats.t_recv += MPI_Wtime() - t_recv0;
            stats.bytes_recv += receiver_size;

            // Malformed/truncated message:
            if (!receiver.has_valid_header())
            {
                ++stats.n_malformed;
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

                double t_train0 = MPI_Wtime();
                plugin_interface(params, target, target_uncertainty, receiver.flag(), status_recv.MPI_SOURCE);
                stats.add_train(MPI_Wtime() - t_train0);
                ++stats.n_train;
            }
            // Predict, ask for prediction and send
            else if (receiver.if_predict())
            {
                // extract parameters
                auto params = receiver.params();
                unsigned short int flag = receiver.flag();
                double t_pred0 = MPI_Wtime();
                auto pred = plugin_interface(params, flag, status_recv.MPI_SOURCE);
                stats.add_predict(MPI_Wtime() - t_pred0);
                ++stats.n_predict;

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
                    double t_reply0 = MPI_Wtime();
                    MPI_Send(answer_buffer.buffer.data(), answer_buffer.buffer.size(), MPI_CHAR, status_recv.MPI_SOURCE, 4, MPI_COMM_WORLD);
                    stats.t_reply += MPI_Wtime() - t_reply0;
                    ++stats.n_reply;
                }
            }
        }
        else
        {
            // nothing to do this pass: count the time as idle
            stats.t_idle += MPI_Wtime() - t_loop;
        }
        
        // Always listen to messages for shut down 
        double t_now = MPI_Wtime();
        if (shutdown_check_interval <= 0 || t_now - t_last_shutdown_check >= shutdown_check_interval)
        {
            finished = signaldata().check_if_shutdown_begun();
            t_last_shutdown_check = MPI_Wtime();
            stats.t_shutdown += t_last_shutdown_check - t_now;
            ++stats.n_shutdown_checks;
        }
    }

    ////// Shut down egg
    stats.tick(true);
    std::cout << "rank " << local_rank <<" got shut down" << std::endl;
    signaldata().broadcast_shutdown_signal(SignalData::NO_MORE_MESSAGES);
    }
    catch (const MPIShutdownException& e)
    {
        stats.tick(true);
        std::cerr << "egg: shutting down due to an emergency shutdown signal "
                     "from another process: " << e.what() << std::endl;
        allow_finalize = GMPI::PrepareForFinalizeWithTimeout(use_mpi_abort);
    }

    if (allow_finalize) GMPI::Finalize();

    return 0;
}
