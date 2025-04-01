#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    MPI_Comm parentcomm;
    MPI_Comm_get_parent(&parentcomm);

    if (parentcomm == MPI_COMM_NULL) {
        printf("No parent process\n");
    } else {
        int message;
        int size, rank;
        MPI_Comm_size(parentcomm, &size);
        MPI_Comm_rank(parentcomm, &rank);
        std::cout << "child size = " << size << std::endl;
        std::cout << "child rank = " << rank << std::endl;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        std::cout << "child world size = " << size << std::endl;
        std::cout << "child world rank = " << rank << std::endl;
        MPI_Recv(&message, 1, MPI_INT, 1, 0, parentcomm, MPI_STATUS_IGNORE);
        printf("Received message: %d\n", message);
    }

    MPI_Finalize();
    return 0;
}
