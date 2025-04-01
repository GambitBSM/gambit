#include <mpi.h>
#include <stdio.h>
#include <string>
#include <iostream>

std::pair<double, double> predict(double x)
{
    return {0.0, 0.0};
}

void train() {}
int main(int argc, char *argv[]) 
{
    MPI_Init(&argc, &argv);

    if (argc >= 2 and std::string(argv[1]) == "child")
    {
        MPI_Comm parentcomm;
        MPI_Comm_get_parent(&parentcomm);

        if (parentcomm == MPI_COMM_NULL) 
        {
            printf("No parent process\n");
        } 
        else 
        {
            //MPI_Recv(&message, 1, MPI_INT, 0, 0, parentcomm, MPI_STATUS_IGNORE);
            int size, rank;
            double x;
            MPI_Comm_size(MPI_COMM_WORLD, &size);
            MPI_Comm_rank(MPI_COMM_WORLD, &rank);
            
            MPI_Send(&rank, 1, MPI_INT, 0, 0, parentcomm);
            MPI_Recv(&x, 1, MPI_INT, 0, 0, parentcomm, MPI_STATUS_IGNORE);
            MPI_Recv(buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            if (rank == 0)
            {
                int rankin;
                MPI_Recv(&rankin, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, parentcomm, MPI_STATUS_IGNORE);
            }
        }
    }
    else
    {
        int num_procs_to_spawn = 4;
        const char *worker_program = "./parent";
        const char *argv_spawn[] = {"child", NULL};
        MPI_Info info = MPI_INFO_NULL;
        MPI_Comm intercomm;

        MPI_Comm_spawn((char *)worker_program, (char**)argv_spawn, num_procs_to_spawn, info, 0, MPI_COMM_WORLD, &intercomm, MPI_ERRCODES_IGNORE);

        int message = 42;
        int size, rank, r;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
        MPI_Recv(&r, 1, MPI_INT, )
    }

    MPI_Finalize();
    return 0;
}

