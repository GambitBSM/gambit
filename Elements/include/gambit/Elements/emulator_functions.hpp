#ifndef __emulator_functions_hpp__
#define __emulator_functions_hpp__

#ifdef WITH_MPI

#include <mpi.h>
#include <time.h>
#include "gambit/Core/emu_map.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/ScannerBit/emulator_utils.hpp"

using namespace Gambit;
using namespace Gambit::Scanner;
using Gambit::Scanner::map_vector;
using Gambit::Scanner::vector;


// Returns true if the emulator declined to give a valid prediction for this point
// (in which case 'prediction'/'uncertainty' should not be trusted).
inline bool emulatorPredict(str capability_name, std::vector<double> input, std::vector<double>& prediction, std::vector<double>& uncertainty)
{
    // get message size
    unsigned int n = input.size();
    std::vector<unsigned int> sizes = {n, 1, 1};

    // make send buffer
    Scanner::Emulator::feed_def fd_predict(sizes);
    fd_predict.add_for_evaluation(input);
    fd_predict.set_predict();

    // find this capability's settings
    EmulatorMap::CapabilitySettings& settings = EmulatorMap::capabilities[capability_name];

    // send to egg
    for ( auto rank : settings.ranks)
    {
        MPI_Send(fd_predict.buffer.data(), fd_predict.buffer.size(), MPI_CHAR, rank, 3, MPI_COMM_WORLD);
    }

    // wait for prediction
    // prepare to get result from egg
    Scanner::Emulator::feed_def predict_results;

    // get timeout for the capability to ensure proper shutdown if emulator freezes
    double predict_timeout_seconds = settings.timeout;

    int size_result;
    MPI_Status status_parent;
    int probe_flag = 0;
    double wait_start = MPI_Wtime();
    struct timespec poll_interval = {0, 10000000L}; // 10 ms
    while (!probe_flag)
    {
        MPI_Iprobe(MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &probe_flag, &status_parent);
        if (!probe_flag)
        {
            if (MPI_Wtime() - wait_start > predict_timeout_seconds)
            {
                std::cerr << "GAMBIT: no prediction response for capability '" << capability_name
                          << "' after " << predict_timeout_seconds << "s. The EGG rank(s) "
                             "handling this capability may have crashed or stalled. Aborting the "
                             "whole MPI job. One can change the timeout limit in the emulator settings for the specific capability in the yaml file." << std::endl;
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            nanosleep(&poll_interval, NULL);
        }
    }

    // Store the wait time in the logs for diagnostics
    double predict_wait_seconds = MPI_Wtime() - wait_start;
    logger() << LogTags::core << LogTags::debug << "Emulator prediction wait time for "
                "capability '" << capability_name << "': " << predict_wait_seconds
             << "s (reply from rank " << status_parent.MPI_SOURCE << ")." << EOM;

    MPI_Get_count(&status_parent, MPI_CHAR, &size_result);
    predict_results.resize(size_result);

    // recieve buffer (pinned to status_parent.MPI_SOURCE, not MPI_ANY_SOURCE, so we
    // can't accidentally match a differently-sized message from another sender)
    MPI_Recv(predict_results.buffer.data(), size_result, MPI_CHAR, status_parent.MPI_SOURCE, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // The prediction from EGG does not have a valid header
    // Shut down the entire run
    if (!predict_results.has_valid_header())
    {
        std::cerr << "GAMBIT: *** PROTOCOL ERROR *** received a malformed/truncated "
                     "prediction reply (" << size_result << " bytes) from EGG rank "
                  << status_parent.MPI_SOURCE << " for capability '" << capability_name
                  << "'. This indicates a bug in the wire protocol, not a normal "
                     "emulator decline -- aborting the whole MPI job." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
        return true; // unreachable: MPI_Abort doesn't return, but isn't declared noreturn
    }

    // A PROTOCOL_ERROR reply means EGG itself received a malformed *request* from gambit
    // Should lead to shutdown of entire run
    if (predict_results.if_protocol_error())
    {
        std::cerr << "GAMBIT: *** PROTOCOL ERROR *** EGG rank " << status_parent.MPI_SOURCE
                  << " reported that our request for capability '" << capability_name
                  << "' was malformed. This indicates a bug in the wire protocol, not a "
                     "normal emulator decline -- aborting the whole MPI job." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
        return true; // unreachable: MPI_Abort doesn't return, but isn't declared noreturn
    }

    // results, translate from eigenvector to vector
    Gambit::Scanner::vector<double> prediction_eigen = predict_results.prediction();
    Gambit::Scanner::vector<double> uncertainty_eigen = predict_results.prediction_uncertainty();

    prediction = std::vector<double>(prediction_eigen.data(), prediction_eigen.data() + prediction_eigen.size());
    uncertainty = std::vector<double>(uncertainty_eigen.data(), uncertainty_eigen.data() + uncertainty_eigen.size());

    bool not_valid = predict_results.if_not_valid();
    if (not_valid && !prediction.empty() && !uncertainty.empty())
    {
        std::cout << "Emulator NOT VALID POINT: " << prediction[0] << ", " << uncertainty[0] << std::endl;
    }

    // Log predictions and validity status
    if (!prediction.empty() && !uncertainty.empty())
    {
        logger() << LogTags::core << LogTags::debug << "Emulator prediction for "
                    "capability '" << capability_name << "': " << prediction[0] << ", with uncertainty "
                 << uncertainty[0] << ", not_valid=" << not_valid << " (reply from rank "
                 << status_parent.MPI_SOURCE << ")." << EOM;
    }
    else
    {
        logger() << LogTags::core << LogTags::debug << "Emulator prediction for "
                    "capability '" << capability_name << "': <empty>, not_valid=" << not_valid
                 << " (reply from rank " << status_parent.MPI_SOURCE << ")." << EOM;
    }
    return not_valid;
}


inline void emulatorTrain(str capability_name, std::vector<double> input, std::vector<double> target, std::vector<double> target_uncertainty)
{
    // size of message
    unsigned int n = input.size();
    std::vector<unsigned int> sizes = {n, 1, 1};

    // make send-buffer
    Scanner::Emulator::feed_def fd(sizes);
    fd.add_for_training(input, target, target_uncertainty);
    fd.set_train();

    // find ranks to send to
    const std::vector<int>& send_rank = EmulatorMap::capabilities[capability_name].ranks;

    // send to egg
    for ( auto rank : send_rank)
    {
        MPI_Send(fd.buffer.data(), fd.buffer.size(), MPI_CHAR, rank, 3, MPI_COMM_WORLD);
    }

    // done
}

inline bool checkThreshold(str capability_name, std::vector<double> uncertainty)
{
    const std::vector<double>& threshold = EmulatorMap::capabilities[capability_name].uncertainty;
    bool valid_prediction = true;
    for (size_t j = 0; j<uncertainty.size(); ++j)
    {
        if ((uncertainty[j] >= threshold.at(j)) || (uncertainty[j]==0))
        {
            valid_prediction = false;
        }
    }
   
    return valid_prediction;
}

#endif // WITH_MPI

#endif