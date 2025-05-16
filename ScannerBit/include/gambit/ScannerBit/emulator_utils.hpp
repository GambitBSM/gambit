#include "gambit/ScannerBit/scanner_util_types.hpp"

namespace Gambit
{

    namespace Scanner
    {

        namespace Emulator
        {

            struct feed_def
            {
                //int n1, n2;
                std::vector<unsigned char> buffer;

                static const unsigned short int NONE = 0x0000;
                static const unsigned short int TRAIN = 0x0001;
                static const unsigned short int PREDICT = 0x0002;
                static const unsigned short int RESULT = 0x0003;

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

                uint &get_sizes(int i) // changed name of function
                {
                    return ((uint *)&buffer[2*sizeof(usint)])[i]; // changed from uint to usint
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

                    // store the flags
                    (unsigned short int &)(buffer[0]) = flag;
                    pos += sizeof(unsigned short int);

                    // store the total size of the vectors first sizes
                    (size_t &)(buffer[pos]) = (size_t )sizes.size();
                    pos += sizeof(unsigned short int);
    
                    // store the sizes of the vectors
                    for (auto &&s : sizes)
                    {
                        (uint &)buffer[pos] = s;
                        pos += sizeof(uint);
                    }
                }
                unsigned char * buffer_0() {return &buffer[0];}

                // cant figure out how to get the correct address when using this function
                map_vector<double> buffer_vector_greg(uint i)
                {
                    assert(i < dim());
                    double *_data = data();
                    for (uint j = 0; j < i; ++j){
                        _data += get_sizes(j);
                    }
                    return Eigen::Map< vector<double>, Eigen::Unaligned, Eigen::Stride<1,1> >((double*)&_data, get_sizes(i));
                }

                // _ida: Made new buffer_vector function using the positions to get correct address
                map_vector<double> buffer_vector(uint i)
                {
                    assert(i < dim());
                    uint pos = 2*sizeof(usint) + dim()*sizeof(uint);
                    for (uint j = 0; j < i; ++j){
                        pos += get_sizes(j)*sizeof(double);
                    }
                    return Eigen::Map< vector<double>, Eigen::Unaligned, Eigen::Stride<1,1> >((double*)&buffer[pos], get_sizes(i));
                }

                // constructing the buffer
                decltype(auto) params(){return buffer_vector(0);}
                decltype(auto) target(){return buffer_vector(1);}
                decltype(auto) target_uncertainty(){return buffer_vector(2);}
                decltype(auto) prediction(){return buffer_vector(1);}
                decltype(auto) prediction_uncertainty(){return buffer_vector(2);}
                
                void add_for_evaluation(std::vector<double> parameters)
                {
                    set_predict();
                    auto params_pointer = buffer_vector(0);
                    params_pointer = map_vector<double>(&parameters[0], parameters.size());
                
                }

                void add_for_training(std::vector<double> parameters, std::vector<double> target_value, std::vector<double> target_uncertainty_value)
                {
                    set_train();
                    auto params_pointer = buffer_vector(0);
                    params_pointer = map_vector<double>(&parameters[0], parameters.size());
                
                    auto target_pointer = buffer_vector(1);
                    target_pointer = map_vector<double>(&target_value[0], target_value.size());

                    auto target_uncertainty_pointer = buffer_vector(2);
                    target_uncertainty_pointer = map_vector<double>(&target_uncertainty_value[0], target_uncertainty_value.size());
                }

                void add_for_result(std::vector<double> result, std::vector<double> result_uncertainty)
                {
                    set_result();
                    
                    auto prediction_pointer = buffer_vector(1);
                    prediction_pointer = map_vector<double>(&result[0], result.size());

                    auto prediction_uncertainty_pointer = buffer_vector(2);
                    prediction_uncertainty_pointer = map_vector<double>(&result_uncertainty[0], result_uncertainty.size());
                }

                // flags
                bool if_train() {return TRAIN & flag();}
                bool if_predict() {return PREDICT & flag();}
                bool if_result() {return RESULT & flag();}
                void set_train() { flag() = flag() | TRAIN;}
                void set_predict() { flag() = flag() | PREDICT;}
                void set_result() { flag() = flag() | RESULT;}

            };

        }

    }

}
