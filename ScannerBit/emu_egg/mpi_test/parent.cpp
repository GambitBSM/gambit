
#include <stdio.h>
#include <string>
#include <iostream>

// #ifdef WITH_MPI
#include <mpi.h>
// #endif


void train() {}
int main(int argc, char *argv[]) 
{
    MPI_Init(&argc, &argv);

    // get rank and size
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

   

    // creating children
    int num_procs_to_spawn = 2;

    if (world_size < num_procs_to_spawn +1) {std::cout << "too few processes to split into a group with " << num_procs_to_spawn << " processes" << std::endl;}
    
    int color;
    if (world_rank < world_size - num_procs_to_spawn) {color=0;}
    else {color = 1;}

    

    // split communicator
    MPI_Comm comm_local;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &comm_local);

    int local_rank, local_size;
    MPI_Comm_rank(comm_local, &local_rank);
    MPI_Comm_size(comm_local, &local_size);

    std::cout  << world_rank << " # " << world_size << " # " << color << " # " << local_rank << " # " << local_size << std::endl;


    MPI_Comm comm_inter;
    int local_leader = 0;
    int remote_leader_world_rank = (color == 0 ? (world_size - 2) : 0);;

    MPI_Intercomm_create(
        comm_local,            // local intra‐communicator
        local_leader,          // rank in comm_local that acts as "bridge"
        MPI_COMM_WORLD,        // the parent communicator
        remote_leader_world_rank, // rank in MPI_COMM_WORLD of the other group’s leader
        MPI_ANY_TAG,
        &comm_inter
    );

    // inter-communicator allows any process in group A to communicate with any process in group B


    if (color == 1) 
    {
        int r;
        // For parent to receive messages from children (e.g., ranks other than 0)
        for (int i = 0; i < world_size-num_procs_to_spawn; ++i) 
        {
            MPI_Recv(&r, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, comm_inter, MPI_STATUS_IGNORE);
            // You can handle received messages 
            std::cout << "My rank is: " << world_rank << ", I Received from child: " << r << std::endl;
        }

    }
    else 
    {
        MPI_Send(&world_rank, 1, MPI_INT, 0, 0, comm_inter); // child sends its rank to the parent

        MPI_Send(&world_rank, 1, MPI_INT, 1, 0, comm_inter); // child sends its rank to the parent
    }



    //     const char *worker_program = "./parent";
    //     const char *argv_spawn[] = {"child", NULL};
    //     MPI_Info info = MPI_INFO_NULL;

    //     // intercomm
    //     MPI_Comm intercomm;

    //     // spawning
    //     MPI_Comm_spawn(
    //             (char *)worker_program, // the program to run
    //             (char**)argv_spawn,     // extra command line arguments
    //             num_procs_to_spawn,     // number of processes to spawn
    //             info,                   // default info
    //             0,                      // root rank is 0 in MPI_COMM_WORLD
    //             MPI_COMM_WORLD,         // communicator of the parent
    //             &intercomm,             // intercommunicator of the children
    //             MPI_ERRCODES_IGNORE     // error codes
    //         );


    //     int message = 42;
    //     int parent_size, r;

    //     MPI_Comm_size(MPI_COMM_WORLD, &parent_size);

    //     std::cout << "parnet: " << parent_size << std::endl;

    //     // For parent to receive messages from children (e.g., ranks other than 0)
    //     for (int i = 0; i < num_procs_to_spawn; ++i) {
    //         MPI_Recv(&r, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, intercomm, MPI_STATUS_IGNORE);
    //         // You can handle received messages 
    //         std::cout << "My rank is: " << world_rank << ", I Received from child: " << r << std::endl;
    //     }

    //     MPI_Send(&message, 1, MPI_INT, 0, 0, intercomm); // parent sends message to child

    //     // }
    // } 
    // else 
    // {
    //     int size,rank; 
    //     int x;

    //     MPI_Comm_size(MPI_COMM_WORLD, &size); // total number of processes
    //     MPI_Comm_rank(MPI_COMM_WORLD, &rank); // identifier of current process

    //     std::cout << size << std::endl;
        
    //     MPI_Send(&rank, 1, MPI_INT, 0, 0, parentcomm); // child sends its rank to the parent
    //     // sendig rank, count, data type, destination rank, tag, communicator

    //     // recieve a value from parent
    //     if (rank == 0)
    //     {
    //         MPI_Recv(&x, 1, MPI_INT, 0, 0, parentcomm, MPI_STATUS_IGNORE);
    //         // buffer, count, data type, sender rank, tag, communicator, flag
    //         std::cout << "child: " << rank << "recieved: " << x << std::endl;
    //     }
    // }
    // sleep(10);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}

