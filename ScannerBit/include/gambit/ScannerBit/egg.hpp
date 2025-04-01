#include "gambit/ScannerBit/scanner_util_types.hpp"

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
        return ((uint *)&buffer[2*sizeof(uint)])[i];
    }

    double *data()
    {
        return (double*)&buffer[2*sizeof(usint) + dim()*sizeof(uint)];
    }

    feed_def() {};
    feed_def(int size) : buffer(size) {}
    void resize(int size)
    {
        buffer.resize(size);
    }


    feed_def(std::vector<uint> sizes, unsigned short int flag = NONE)
    {
        int tot_size = 0;
        for (auto &&s : sizes)
            tot_size += s;

        buffer.resize(2*sizeof(usint) + sizes.size()*sizeof(uint) + tot_size*sizeof(double));
        uint pos = 0;
        (unsigned short int &)(buffer[0]) = flag;
        pos += sizeof(unsigned short int);

        (size_t &)(buffer[pos]) = (size_t )sizes.size();
        pos += sizeof(unsigned short int);

        for (auto &&s : sizes)
        {
            (uint &)buffer[pos] = s;
            pos += sizeof(uint);
        }
    }

    unsigned char * buffer_0() {return &buffer[0];}

    // map_vector<double> get_vector(int i)
    // {
    //     assert(i < dim());

    //     double *_data = data();
    //     for (uint j = 0; j < i; ++j)
    //         _data += sizes(j);

    //     return eigen::Map<vector<double>>((double *)&_data, sizes(i));
    // }
};
