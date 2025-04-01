#include <mpi.h>
#include <stdio.h>

#include "egg.hpp"

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    MPI_Comm parentcomm;
    MPI_Comm_get_parent(&parentcomm);

    if (parentcomm == MPI_COMM_NULL)
    {
        std::cout << "bad stuff happening" << std::endl;
    }
    else
    {
        int message;
        int size, rank;
        int parent_size, parent_rank;
        //MPI_Comm_size(parentcomm, &parent_size);
        //MPI_Comm_rank(parentcomm, &parent_rank);
        //MPI_Comm_size(MPI_COMM_WORLD, &size);
        //MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        int num;
        MPI_Status status;
        feed_def buffer;
        
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, parentcomm, &status);
        MPI_Get_count(&status, MPI_INT, &num);
        buffer.resize(num);

        MPI_Recv(buffer.buffer(), num, MPI_CHAR, ANY_RANK, MPI_ANY_TAG, parentcomm, status);
            
        if (buffer.flag() & feed_crap::TRAINING_PT)
        {
            std::cout << "doing training" << std::endl;
            // std::cout << "input: " << buffer.get_vector(0).transpose() << std::endl;
            // std::cout << "target: " << buffer.get_vector(1).transpose() << std::endl;
            // std::cout << "target uncertainty: " << buffer.get_vector(2).transpose() << std::endl;
            //call emuplugin
        }
        else if (buffer.flag() & feed_crap::PREDICT)
        {
            std::cout << "doing predict" << std::endl;
            // std::cout << "input": << buffer.get_vector(0).transpose() << std::endl;
            // //call emu.predict(input)
            // int N = buffer.sizes(0);
            // feed_def ret({N, N});
            // MPI_Send(buffer.buffer, buffer.size(), MPI_CHAR, status.MPI_SOURCE, ANY_TAG, parentcomm)
        }
    }

    MPI_Finalize();
    return 0;
}
