#ifndef __emulator_functions_hpp__
#define __emulator_functions_hpp__

#ifdef WITH_MPI

#include <mpi.h>
#include <time.h>
#include "gambit/Core/emu_map.hpp"
#include "gambit/ScannerBit/emulator_utils.hpp"

// How long (in seconds) to wait for a prediction reply from an EGG rank before
// concluding it has died/stalled and aborting the whole MPI job. Without this,
// a crashed EGG rank (e.g. an uncaught exception in a plugin's train()) leaves
// the requesting GAMBIT rank blocked forever on MPI_Probe with no diagnostic.
static const double EMULATOR_PREDICT_TIMEOUT_SECONDS = 300.0;

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

    // find rank to send to
    std::vector<int> send_rank = EmulatorMap::mapping_ranks[capability_name];

    // send to egg
    for ( auto rank : send_rank)
    {
        MPI_Send(fd_predict.buffer.data(), fd_predict.buffer.size(), MPI_CHAR, rank, 3, MPI_COMM_WORLD);
    }

    // wait for prediction
    // prepare to get result from egg
    Scanner::Emulator::feed_def predict_results;

    // probe size of result buffer, polling with a timeout instead of blocking
    // forever: if the EGG rank handling this capability has died or stalled,
    // abort the whole job with a clear diagnostic instead of hanging silently.
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
            if (MPI_Wtime() - wait_start > EMULATOR_PREDICT_TIMEOUT_SECONDS)
            {
                std::cerr << "GAMBIT: no prediction response for capability '" << capability_name
                          << "' after " << EMULATOR_PREDICT_TIMEOUT_SECONDS << "s. The EGG rank(s) "
                             "handling this capability may have crashed or stalled. Aborting the "
                             "whole MPI job." << std::endl;
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
            nanosleep(&poll_interval, NULL);
        }
    }
    MPI_Get_count(&status_parent, MPI_CHAR, &size_result);
    predict_results.resize(size_result);

    // recieve buffer (pinned to status_parent.MPI_SOURCE, not MPI_ANY_SOURCE, so we
    // can't accidentally match a differently-sized message from another sender)
    MPI_Recv(predict_results.buffer.data(), size_result, MPI_CHAR, status_parent.MPI_SOURCE, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // results, translate from eigenvector to vector
    Gambit::Scanner::vector<double> prediction_eigen = predict_results.prediction();
    Gambit::Scanner::vector<double> uncertainty_eigen = predict_results.prediction_uncertainty();

    prediction = std::vector<double>(prediction_eigen.data(), prediction_eigen.data() + prediction_eigen.size());
    uncertainty = std::vector<double>(uncertainty_eigen.data(), uncertainty_eigen.data() + uncertainty_eigen.size());

    bool not_valid = predict_results.if_not_valid();
    if (not_valid) {std::cout << "Emulator NOT VALID POINT: " << prediction[0] << ", " << uncertainty[0] << std::endl;}

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
    std::vector<int> send_rank = EmulatorMap::mapping_ranks[capability_name];

    // send to egg
    for ( auto rank : send_rank)
    {
        MPI_Send(fd.buffer.data(), fd.buffer.size(), MPI_CHAR, rank, 3, MPI_COMM_WORLD);
    }

    // done
}

inline bool checkThreshold(str capability_name, std::vector<double> uncertainty)
{
    std::vector<double> threshold = EmulatorMap::mapping_uncertainty[capability_name];
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