
#include <stdio.h>
#include <string>
#include <iostream>

// #ifdef WITH_MPI
#include <mpi.h>
// #endif

#include "gambit/ScannerBit/emulator_utils.hpp"

std::pair<double, double> predict(double x)
{
    return {0.0, 0.0};
}

using namespace Gambit::Scanner::Emulator;

void train() {}
int main(int argc, char *argv[]) 
{
    MPI_Init(&argc, &argv);

    // allow children to communicate with parent
    MPI_Comm parentcomm;
    MPI_Comm_get_parent(&parentcomm);

    // check if parentcomm exists
    if (parentcomm == MPI_COMM_NULL) 
    {
        printf("No parent process\n");

        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        if (world_rank == 0){

            // spawning children
            int num_procs_to_spawn = 4;
            const char *worker_program = "./parent";
            const char *argv_spawn[] = {"child", NULL};
            MPI_Info info = MPI_INFO_NULL;

            // intercomm
            MPI_Comm intercomm;

            // spawning
            MPI_Comm_spawn(
                    (char *)worker_program, // the program to run
                    (char**)argv_spawn,     // extra command line arguments
                    num_procs_to_spawn,     // number of processes to spawn
                    info,                   // default info
                    0,                      // root rank is 0 in MPI_COMM_WORLD
                    MPI_COMM_WORLD,         // communicator of the parent
                    &intercomm,             // intercommunicator of the children
                    MPI_ERRCODES_IGNORE     // error codes
                );


            int message = 42;
            int parent_size, world_rank, r;

            MPI_Comm_size(MPI_COMM_WORLD, &parent_size);

            std::cout << "parnet: " << parent_size << std::endl;

            // For parent to receive messages from children (e.g., ranks other than 0)
            for (int i = 0; i < num_procs_to_spawn; ++i) {
                MPI_Recv(&r, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, intercomm, MPI_STATUS_IGNORE);
                // You can handle received messages 
                std::cout << "My rank is: " << world_rank << ", I Received from child: " << r << std::endl;
            }

            MPI_Send(&message, 1, MPI_INT, 0, 0, intercomm); // parent sends message to child

        }
    } 
    else 
    {
        int size,rank; 
        int x;

        MPI_Comm_size(MPI_COMM_WORLD, &size); // total number of processes
        MPI_Comm_rank(MPI_COMM_WORLD, &rank); // identifier of current process

        std::cout << size << std::endl;
        
        MPI_Send(&rank, 1, MPI_INT, 0, 0, parentcomm); // child sends its rank to the parent
        // sendig rank, count, data type, destination rank, tag, communicator

        // recieve a value from parent
        if (rank == 0)
        {
            MPI_Recv(&x, 1, MPI_INT, 0, 0, parentcomm, MPI_STATUS_IGNORE);
            // buffer, count, data type, sender rank, tag, communicator, flag
            std::cout << "child: " << rank << "recieved: " << x << std::endl;
        }
    }
    sleep(10);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}

