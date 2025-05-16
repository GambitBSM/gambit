
#include <stdio.h>
#include <string>
#include <iostream>

// #ifdef WITH_MPI
#include <mpi.h>
// #endif

#include "gambit/ScannerBit/emulator_utils.hpp"

using namespace Gambit::Scanner::Emulator;

int main(int argc, char *argv[]) 
{
    MPI_Init(&argc, &argv);
    // allow children to communicate with parent
    MPI_Comm parentcomm;
    MPI_Comm_get_parent(&parentcomm);

    // check if parentcomm exists
    if (parentcomm == MPI_COMM_NULL) 
    {
        printf("No parent comm, so spawns the processes\n");

        // This is parent process
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


        // spawning children
        int num_procs_to_spawn = 4; 
        const char *worker_program = "./parent_feed";
        const char *argv_spawn[] = {"child", NULL};
        MPI_Info info = MPI_INFO_NULL;
        MPI_Comm intercomm;
        MPI_Comm_spawn((char *)worker_program, (char**)argv_spawn, num_procs_to_spawn, info, 0, MPI_COMM_WORLD, &intercomm, MPI_ERRCODES_IGNORE);

        // Parent recieves the rank of each child
        int r;
        for (int i = 0; i < num_procs_to_spawn; ++i) {
            MPI_Recv(&r, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, intercomm, MPI_STATUS_IGNORE);
            std::cout << "My rank is: " << world_rank << ", I Received from child: " << r << std::endl;
        }


        
        // Prepare data to enter feed_def
        std::vector<double> input_point = {0.112, 1.344, 0.98};
        std::vector<double> likelihood = {-100.3};
        std::vector<double> likelihood_sigma = {0.3};
        unsigned int n = input_point.size();

        // Create the feed_def object
        std::vector<unsigned int> sizes = {n, 1, 1};
        feed_def fd(sizes);

        // add training input
        fd.add_for_training(input_point, likelihood, likelihood_sigma);
        
        // Print updated values from buffer
        // std::cout << "Updated params: ";
        // for (size_t i = 0; i < params.size(); ++i)    {    std::cout << params[i] << " ";  // Print updated values in the buffer
        // }
        // std::cout << std::endl;

        // send feed_def structure to child
        MPI_Send(fd.buffer.data(), fd.buffer.size(), MPI_CHAR, 2, 0, intercomm);




        // prepare to get result from child
        feed_def results;

        // probe size of result buffer
        int size_result;
        MPI_Status status_parent;
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, intercomm, &status_parent);
        MPI_Get_count(&status_parent, MPI_CHAR, &size_result);
        // std::cout << "size of result buffer: " << size_result << std::endl;
        results.resize(size_result);

        // recieve buffer
        MPI_Recv(results.buffer.data(), size_result, MPI_CHAR, MPI_ANY_SOURCE, 0, intercomm, MPI_STATUS_IGNORE);

        // read prediction
        std::cout << "Parent receives prediction: " << results.prediction()[0] << " +- "  << results.prediction_uncertainty()[0] << std::endl;
        
    }
    else 
    {
        // This is the child processes
        int rank_kid; 
        MPI_Comm_rank(MPI_COMM_WORLD, &rank_kid); // identifier of current process

        // send rank to parent
        MPI_Send(&rank_kid, 1, MPI_INT, 0, 0, parentcomm); // child sends its rank to the parent
        // sendig rank, count, data type, destination rank, tag, communicator

        if (rank_kid == 2)
        {
            // prepare receiving buffer
            feed_def receiver;

            // probe to find receiver size
            int receiver_size;
            MPI_Status status;
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, parentcomm, &status);
            MPI_Get_count(&status, MPI_CHAR, &receiver_size);

            // resize receiver
            // std::cout << "size of receiver buffer: " << receiver_size << std::endl;
            receiver.resize(receiver_size);

            // recieve data
            MPI_Recv(receiver.buffer.data(), receiver_size, MPI_CHAR, 0, 0, parentcomm, MPI_STATUS_IGNORE);

            // read flag
            std::cout << "Does the message tell us to train? " << receiver.if_train() << std::endl;

            // read parameters
            auto pa = receiver.params();
            std::cout << "Child of rank " << rank_kid <<  " received the following parameter values: ";
            for (int i = 0; i < pa.size(); ++i)    {    std::cout << pa[i] << " ";  // Print updated values in the buffer
            }
            std::cout << std::endl;

            // read target
            std::cout << "and target: " << receiver.target()[0] << " +- " << receiver.target_uncertainty()[0] << std::endl;



            // evaluate and calculate prediction
            std::vector<double> pred = {-100.2};
            std::vector<double> pred_u = {1.2};

            // make new buffer with size 0 for the input parameters
            std::vector<unsigned int> sizes = {0, 1, 1};
            feed_def answer_buffer(sizes);

            // populate answer_buffer
            answer_buffer.add_for_result(pred, pred_u);

            // send to parent
            MPI_Send(answer_buffer.buffer.data(), answer_buffer.buffer.size(), MPI_CHAR, 0, 0, parentcomm);
        }
    }
    sleep(10);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}

