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
#include <list>
#include <tuple>
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
    // routing: master
    unsigned long n_forwarded = 0, n_batches = 0, n_batch_points = 0, n_dropped_batches = 0, n_master_calls = 0;
    double t_master = 0;
    unsigned long pending_sends = 0;
    // finer time accounting: MPI_Iprobe on passes that found a message, the whole master dispatch (plugin master()
    // call + building and sending the forwarded message + own work), checking finished sends, passes with a message,
    // and the total time of those passes (busy_s). Time outside busy_s is spent spinning in passes that find nothing.
    double t_probe_busy = 0, t_dispatch = 0, t_sweep = 0, t_busy = 0;
    unsigned long n_busy_passes = 0;

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
          << " master_calls=" << n_master_calls << " master_s=" << t_master << " forwarded=" << n_forwarded
          << " batches_sent=" << n_batches << " batch_points=" << n_batch_points
          << " dropped_batches=" << n_dropped_batches << " pending_sends=" << pending_sends
          << " probe_busy_s=" << t_probe_busy << " dispatch_s=" << t_dispatch << " sweep_s=" << t_sweep
          << " busy_passes=" << n_busy_passes << " busy_s=" << t_busy
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
    Plugins::Plugin_Interface<void (map_vector<double> , map_vector<double> , map_vector<double>, unsigned short int &, int),
                              std::pair<vector<double>, vector<double>> (map_vector<double>, unsigned short int &, int),
                              void (map_vector<double> , map_vector<double> , map_vector<double>, unsigned short int &, int, int),
                              std::tuple<int, int, vector<double>, vector<double>, vector<double>> (unsigned short int &, int, map_vector<double>, map_vector<double>, map_vector<double>)> plugin_interface("emulator", capability);
    std::cout << "made plugin " << std::endl;

    ///////// Recieve messages from gambit

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

    // Message routing between the egg ranks of this capability (Emulation: emulators: <capability>: routing)
    //   legacy : gambit sends every message to every egg rank and the plugin decides what to ignore
    //   master : gambit sends only to the master (egg rank 0 of the capability). The master calls the plugin's
    //            master() function, which says which egg rank gets the message. Predict requests are forwarded
    //            and the rank that handles them replies directly to the gambit rank that asked. Training
    //            points are collected by master() and sent on as batches.
    str routing = emulator_node["emulators"][capability]["routing"].IsDefined()
                ? emulator_node["emulators"][capability]["routing"].as<str>() : "legacy";
    if (routing != "legacy" && routing != "master")
    {
        std::cerr << "egg: Emulation.emulators." << capability << ".routing must be 'legacy' or 'master', not '"
                  << routing << "'. Aborting the whole MPI job." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    const bool master_mode = (routing == "master");
    const bool is_master = master_mode && local_rank == 0;
    const bool is_worker = master_mode && local_rank != 0;

    // Seconds between calls of master() while no message arrives, so that it can flush a training cache that
    // has been waiting for too long. 0 = never.
    double master_tick_interval = emulator_node["emulators"][capability]["master_tick_interval"].IsDefined()
                                ? emulator_node["emulators"][capability]["master_tick_interval"].as<double>() : 1.0;
    double t_last_tick = MPI_Wtime();

    // Max number of training batches in flight (sent but not yet received by the target rank). If the trainer falls
    // behind by more than this, new batches are dropped (never predict requests), so the master never blocks.
    unsigned int max_pending_batches = emulator_node["emulators"][capability]["max_pending_batches"].IsDefined()
                                     ? emulator_node["emulators"][capability]["max_pending_batches"].as<unsigned int>() : 100;

    const int TAG_REQUEST = 3;   // gambit -> egg: train/predict request
    const int TAG_RESULT = 4;    // egg -> gambit: prediction
    const int TAG_INTERNAL = 5;  // master -> worker (routing: master)

    // Non-blocking sends from the master to the workers, with their buffers
    struct PendingSend { MPI_Request request; std::vector<unsigned char> buffer; bool batch; };
    std::list<PendingSend> pending;
    unsigned int pending_batches = 0;

    auto sweep_pending = [&]()
    {
        for (auto it = pending.begin(); it != pending.end(); )
        {
            int done = 0;
            MPI_Test(&it->request, &done, MPI_STATUS_IGNORE);
            if (done)
            {
                if (it->batch) --pending_batches;
                it = pending.erase(it);
            }
            else ++it;
        }
        stats.pending_sends = pending.size();
    };

    // Handle one train or predict message with this rank's plugin. 'source' is the world rank that sent it (a
    // gambit rank, or the original gambit rank carried in a forwarded predict request).
    auto do_work = [&](Scanner::Emulator::feed_def &msg, int source)
    {
        auto params = msg.params();
        if (msg.if_train() && msg.if_batch())
        {
            auto target = msg.target();
            auto target_uncertainty = msg.target_uncertainty();
            int n_rows = (int)msg.extra();
            double t0 = MPI_Wtime();
            plugin_interface(params, target, target_uncertainty, msg.flag(), source, n_rows);
            stats.add_train(MPI_Wtime() - t0);
            stats.n_train += n_rows;
        }
        else if (msg.if_train())
        {
            auto target = msg.target();
            auto target_uncertainty = msg.target_uncertainty();
            double t0 = MPI_Wtime();
            plugin_interface(params, target, target_uncertainty, msg.flag(), source);
            stats.add_train(MPI_Wtime() - t0);
            ++stats.n_train;
        }
        else if (msg.if_predict())
        {
            unsigned short int flag = msg.flag();
            double t0 = MPI_Wtime();
            auto pred = plugin_interface(params, flag, source);
            stats.add_predict(MPI_Wtime() - t0);
            ++stats.n_predict;

            // if result is returned, send reply
            if (flag & Scanner::Emulator::feed_def::RESULT)
            {
                std::vector<unsigned int> sizes = {0, (unsigned int)pred.first.size(), (unsigned int)pred.second.size()};
                Scanner::Emulator::feed_def answer_buffer(sizes);
                answer_buffer.flag() = flag;
                answer_buffer.set_result(); // always reply, even if the result is invalid
                answer_buffer.add_for_result(pred.first, pred.second);

                // send straight to the gambit process the request came from ( tag 4 = results )
                double t_reply0 = MPI_Wtime();
                MPI_Send(answer_buffer.buffer.data(), answer_buffer.buffer.size(), MPI_CHAR, source, TAG_RESULT, MPI_COMM_WORLD);
                stats.t_reply += MPI_Wtime() - t_reply0;
                ++stats.n_reply;
            }
        }
    };

    // Master only: call the plugin's master() for a message (or an empty tick, with empty arrays) and carry out its decision
    auto master_dispatch = [&](unsigned short int flag, int source, map_vector<double> x, map_vector<double> y, map_vector<double> z)
    {
        struct DispatchTimer { double &acc; double t; ~DispatchTimer() { acc += MPI_Wtime() - t; } } dispatch_timer{stats.t_dispatch, MPI_Wtime()};
        double t0 = MPI_Wtime();
        auto decision = plugin_interface(flag, source, x, y, z);
        stats.t_master += MPI_Wtime() - t0;
        ++stats.n_master_calls;

        const int dest_local = std::get<0>(decision);
        const int n_rows = std::get<1>(decision);
        if (dest_local < 0) return;
        if (dest_local >= (int)emuProcesses.size())
        {
            std::cerr << "egg: master() of the plugin returned egg rank " << dest_local << ", but there are only "
                      << emuProcesses.size() << " egg ranks for capability '" << capability << "'." << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        Scanner::Emulator::feed_def out;
        bool is_batch = n_rows > 0;
        if (is_batch)
        {
            auto &X = std::get<2>(decision);
            auto &Y = std::get<3>(decision);
            auto &Z = std::get<4>(decision);
            out = Scanner::Emulator::feed_def(std::vector<unsigned int>{(unsigned int)X.size(), (unsigned int)Y.size(), (unsigned int)Z.size(), 1});
            out.set_train();
            out.set_batch();
            auto v0 = out.buffer_vector(0); for (int k = 0; k < X.size(); ++k) v0[k] = X[k];
            auto v1 = out.buffer_vector(1); for (int k = 0; k < Y.size(); ++k) v1[k] = Y[k];
            auto v2 = out.buffer_vector(2); for (int k = 0; k < Z.size(); ++k) v2[k] = Z[k];
            out.buffer_vector(3)[0] = n_rows;
        }
        else if (flag & Scanner::Emulator::feed_def::PREDICT)
        {
            out = Scanner::Emulator::feed_def(std::vector<unsigned int>{(unsigned int)x.size(), 1, 1, 1});
            out.set_predict();
            auto v0 = out.buffer_vector(0); for (int k = 0; k < x.size(); ++k) v0[k] = x[k];
            out.buffer_vector(3)[0] = source;
        }
        else
        {
            std::cerr << "egg: master() of the plugin asked to forward something that is neither a predict request "
                         "nor a training batch (n_rows = 0 is only valid for a predict request)." << std::endl;
            return;
        }

        if (dest_local == local_rank)
        {
            // handled by the master itself
            do_work(out, source);
            return;
        }

        if (is_batch && pending_batches >= max_pending_batches)
        {
            ++stats.n_dropped_batches;
            return;
        }

        pending.emplace_back();
        PendingSend &ps = pending.back();
        ps.buffer = std::move(out.buffer);
        ps.batch = is_batch;
        MPI_Isend(ps.buffer.data(), ps.buffer.size(), MPI_CHAR, emuProcesses[dest_local], TAG_INTERNAL, MPI_COMM_WORLD, &ps.request);
        if (is_batch) { ++pending_batches; ++stats.n_batches; stats.n_batch_points += n_rows; }
        else ++stats.n_forwarded;
        stats.pending_sends = pending.size();
    };

    // keep going until shutdown
    bool finished = false;
    bool allow_finalize = true;
    try
    {
    while (!finished)
    {
        stats.tick();
        double t_loop = MPI_Wtime();

        // Probe for an incoming message: tag 3 (train/predict) from gambit, or, on a worker, tag 5 from the master
        MPI_Status status;
        int flag;
        const int probe_source = is_worker ? emuProcesses[0] : MPI_ANY_SOURCE;
        const int probe_tag = is_worker ? TAG_INTERNAL : TAG_REQUEST;
        MPI_Iprobe(probe_source, probe_tag, MPI_COMM_WORLD, &flag, &status);
        double t_probed = MPI_Wtime();
        stats.t_probe += t_probed - t_loop;
        if (flag) { stats.t_probe_busy += t_probed - t_loop; ++stats.n_busy_passes; }

        if (is_master) { sweep_pending(); stats.t_sweep += MPI_Wtime() - t_probed; }

        // if message, accept it
        if (flag && status.MPI_TAG == probe_tag)
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
            MPI_Recv(receiver.buffer.data(), receiver_size, MPI_CHAR, status.MPI_SOURCE, probe_tag, MPI_COMM_WORLD, &status_recv);
            stats.t_recv += MPI_Wtime() - t_recv0;
            stats.bytes_recv += receiver_size;

            if (is_worker)
            {
                // Forwarded by the master. A predict request carries the gambit rank to reply to, a batch its row count.
                if (!receiver.has_valid_payload() || !receiver.has_extra())
                {
                    ++stats.n_malformed;
                    std::cerr << "egg: received a malformed message (" << receiver_size << " bytes) from the master egg rank -- dropping it." << std::endl;
                }
                else if (receiver.if_predict())
                {
                    do_work(receiver, (int)receiver.extra());
                }
                else if (receiver.if_train() && receiver.if_batch())
                {
                    do_work(receiver, status_recv.MPI_SOURCE);
                }
                else
                {
                    ++stats.n_malformed;
                    std::cerr << "egg: received a message from the master egg rank that is neither a predict request nor a training batch -- dropping it." << std::endl;
                }
            }
            // Malformed/truncated message:
            else if (!receiver.has_valid_header())
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
                    MPI_Send(error_buffer.buffer.data(), error_buffer.buffer.size(), MPI_CHAR, status_recv.MPI_SOURCE, TAG_RESULT, MPI_COMM_WORLD);
                    std::cerr << "egg: sent a PROTOCOL_ERROR reply to rank " << status_recv.MPI_SOURCE << "." << std::endl;
                }
                else
                {
                    std::cerr << "egg: message too small to even determine train vs. predict -- dropping it." << std::endl;
                }

                continue;
            }
            else if (is_master)
            {
                master_dispatch(receiver.flag(), status_recv.MPI_SOURCE, receiver.params(), receiver.target(), receiver.target_uncertainty());
                t_last_tick = MPI_Wtime();
            }
            else
            {
                do_work(receiver, status_recv.MPI_SOURCE);
            }
        }
        else
        {
            // nothing to do this pass: count the time as idle
            stats.t_idle += MPI_Wtime() - t_loop;

            // let the master plugin flush a training cache that has waited too long
            if (is_master && master_tick_interval > 0 && MPI_Wtime() - t_last_tick >= master_tick_interval)
            {
                double no_data = 0.0;
                master_dispatch(0, -1, map_vector<double>(&no_data, 0), map_vector<double>(&no_data, 0), map_vector<double>(&no_data, 0));
                t_last_tick = MPI_Wtime();
            }
        }

        // whole time of a pass that handled a message (everything from the probe on); the rest of the run is
        // spent in passes that found nothing (spinning in the probe loop)
        if (flag && status.MPI_TAG == probe_tag) stats.t_busy += MPI_Wtime() - t_loop;

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
    // Messages to the workers that were not received will not be: drop them
    for (auto &ps : pending) { MPI_Cancel(&ps.request); MPI_Wait(&ps.request, MPI_STATUS_IGNORE); }
    pending.clear();
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
