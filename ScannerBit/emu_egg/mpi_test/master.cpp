#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    std::cout << argc << std::endl;
    if (argc >= 2 and std::string(argv[1]) == "child")
    {
    }
    else
    {
        int size, rank;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        std::cout << "world size = " << size << std::endl;
        std::cout << "world rank = " << rank << std::endl;
        
        int num_procs_to_spawn = 4;
        char *worker_program = "./worker";
        char *argv_spawn[] = {"child", NULL};
        MPI_Info info = MPI_INFO_NULL;
        MPI_Comm intercomm;

        //if (rank == 0){
        MPI_Comm_spawn(worker_program, argv_spawn, num_procs_to_spawn, info, 1, MPI_COMM_WORLD, &intercomm, MPI_ERRCODES_IGNORE);

        MPI_Comm_size(intercomm, &size);
        MPI_Comm_rank(intercomm, &rank);
        std::cout << "inter size = " << size << std::endl;
        std::cout << "inter rank = " << rank << std::endl;

        if (rank == 1){
        int message = rank;

        MPI_Send(&message, 1, MPI_INT, 0, 0, intercomm);
        MPI_Send(&message, 1, MPI_INT, 1, 0, intercomm);
        MPI_Send(&message, 1, MPI_INT, 2, 0, intercomm);
        MPI_Send(&message, 1, MPI_INT, 3, 0, intercomm);
        }
    }

    MPI_Finalize();
    return 0;
}
