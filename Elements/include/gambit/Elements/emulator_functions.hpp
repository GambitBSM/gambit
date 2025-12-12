#ifndef __emulator_functions_hpp__
#define __emulator_fynctions_hpp__

#include <mpi.h>
#include "gambit/Core/emu_map.hpp"
// #include "gambit/ScannerBit/emulator_utils.hpp"

using namespace Gambit;
using namespace Gambit::Scanner;
using Gambit::Scanner::map_vector;
using Gambit::Scanner::vector;


void emulatorPredict(str capability_name, std::vector<double> input, vector<double>& prediction, vector<double>& uncertainty)
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

    // probe size of result buffer
    int size_result;
    MPI_Status status_parent;
    MPI_Probe(MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &status_parent);
    MPI_Get_count(&status_parent, MPI_CHAR, &size_result);
    predict_results.resize(size_result);

    // recieve buffer
    MPI_Recv(predict_results.buffer.data(), size_result, MPI_CHAR, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // results
    prediction = predict_results.prediction();
    uncertainty = predict_results.prediction_uncertainty();

    if (predict_results.if_not_valid()) {std::cout << "Emulator NOT VALID POINT: " << prediction[0] << ", " << uncertainty[0] << std::endl;}

}


void emulatorTrain(str capability_name, std::vector<double> input, std::vector<double> target, std::vector<double> target_uncertainty)
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

bool checkThreshold(str capability_name, vector<double> uncertainty)
{
    std::vector<double> threshold = EmulatorMap::mapping_uncertainty[capability_name];
    bool valid_prediction = true;
    for (int j = 0; j<uncertainty.size(); ++j)
    {
        if ((uncertainty[j] >= threshold.at(j)) || (uncertainty[j]==0))
        {
            valid_prediction = false;
        }
    }
   
    return valid_prediction;
}

#endif