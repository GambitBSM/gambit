#include <mpi.h>
#include <stdio.h>
#include <cstring> // For strlen
#include <sstream> // For stringstream

// #include "egg.hpp"
// #include "yaml-cpp/yaml.h"

// using namespace Gambit;

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // get plugin name from arguments
    char* plugin_name = argv[1];

    std::ostringstream oss;
    oss << plugin_name << " " << world_rank; // Append rank to the original string
    std::string message = oss.str();


    // do mpi split
    int color = 1;
    MPI_Comm comm_local;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &comm_local);

    // find local rank
    int local_rank, local_size;
    MPI_Comm_rank(comm_local, &local_rank);
    MPI_Comm_size(comm_local, &local_size);

    std::cout  << "In egg:   world rank " << world_rank << ", color " << color << ", local rank " << local_rank << ", local size " << local_size << std::endl;

    // read yaml file to get emulator plugin name and options
    // std::cout << "Filename: " << argv[2] << std::endl;
    // YAML::Node node = YAML::LoadFile(argv[2])["Emulation"];
    // std::cout << "Number of emulators: " << node.size() << std::endl;
    // for (int i = 0; i < node.size(); ++i)
    // {
    //     std::cout << "Capabilitiy: " <<  node[i]["capability"] << std::endl; 
    //     std::cout << "Plugin name: " <<  node[i]["emulator_plugin"] << std::endl; 
    // }


    // initialize emulator plugins
    

    // send plugin name and world rank to gambit processes
    std::cout <<"In egg: " << message  << " # " << message.length()+1 << std::endl;
    if (local_rank == 0)
    {
        MPI_Send(message.c_str(), message.length() +1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }


    //////////////// Actuall egg stuff (sketch)
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
    

    MPI_Finalize();
    return 0;
}
