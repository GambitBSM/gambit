#include <mpi.h>
#include <stdio.h>

#include "gambit/ScannerBit/scannerbit_util_types.hpp"

constexpr int N = 1024;

template<int n>
struct feed_def
{
    //int n1, n2;
    std::vector<unsigned char> buffer;
    
    static const unsigned short int NONE = 0x0000;
    static const unsigned short int TRAIN = 0x0001;
    static const unsigned short int PREDICT = 0x0002;
    
    typedef unsigned short int usint;
    typedef unsigned int uint;
    
    usint &flag()
    {
        return (usint &)buffer[0];
    }
    
    usint &dim()
    {
        return (usint &)buffer[sizeof(usint)];
    }
    
    uint &sizes(int i)
    {
        return ((int *)&buffer[2*sizeof(usint)])[i];
    }
    
    double *data()
    {
        return (double*)&buffer[2*sizeof(usint) + dim()*sizeof(unit)];
    }
    
    feed_def() {};
    feed_def(int size) : buffer(size) {}
    void resize(int size)
    {
        buffer.resize(size);
    }

    
    feed_crap(std::vector<uint> sizes, unsigned short int flag = NONE)
    {
        int tot_size = 0;
        for (auto &&s : sizes)
            tot_size += s;
        
        buffer.resize(2*sizeof(usint) + sizes.size()*sizeof(uint) + tot_size*sizeof(double));
        unsigned int pos = 0;
        (unsigned short int &)(buffer[0]) = flag;
        pos += sizeof(unsigned short int);
        
        (unsigned short int &)(buffer[pos]) = (unsigned short int &)sizes.size();
        pos += sizeof(unsigned short int);
        
        for (auto &&s : sizes)
        {
            (unsigned int &)buffer[pos] = s;
            pos += sizeof(unsigned int);
        }
    }
    
    unsigned char * buffer() {return &buffer[0];}
    
    map_vector<double> get_vector(int i)
    {
        assert(i < dim());
        
        double *_data = data();
        for (uint j = 0; j < i; ++j)
            _data += sizes(j);
        
        return eigen::Map<vector<double>>((double *)&_data, sizes(i));
    }
};
    

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
            std::cout << "input: " << buffer.get_vector(0).transpose() << std::endl;
            std::cout << "target: " << buffer.get_vector(1).transpose() << std::endl;
            std::cout << "target uncertainty: " << buffer.get_vector(2).transpose() << std::endl;
            //call emuplugin
        }
        else if (buffer.flag() & feed_crap::PREDICT)
        {
            std::cout << "doing predict" << std::endl;
            std::cout << "input": << buffer.get)vector(0).transpose() << std::endl;
            //call emu.predict(input)
            int N = buffer.sizes(0);
            feed_def ret({N, N});
            MPI_Send(buffer.buffer, buffer.size(), MPI_CHAR, status.MPI_SOURCE, ANY_TAG, parentcomm)
        }
        
    }

    MPI_Finalize();
    return 0;
}
