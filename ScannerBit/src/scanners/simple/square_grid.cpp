//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Square grid sampler.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 August
///
///  *********************************************

#ifdef WITH_MPI
#include "gambit/Utils/begin_ignore_warnings_mpi.hpp"
#include "mpi.h"
#include "gambit/Utils/end_ignore_warnings.hpp"
#endif

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>

#include "gambit/ScannerBit/scanner_plugin.hpp"

scanner_plugin(square_grid, version(1, 0, 0))
{
    int plugin_main()
    {
        int rank, numtasks;
        int N = std::abs(get_inifile_value<int>("grid_pts", 2));
        if (N == 0) N = 1;
        int ma = get_dimension();
        
#ifdef WITH_MPI
        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#else
        numtasks = 1;
        rank = 0;
#endif
        
        like_ptr LogLike = get_purpose(get_inifile_value<std::string>("like"));
        std::vector<double> vec(ma, 0.0);

        for (int i = rank, end = std::pow(N, ma); i < end; i+=numtasks)
        {
            int n = i;
            for (int j = 0; j < ma; j++)
            {
                if (N == 1)
                    vec[j] = 0.5;
                else
                    vec[j] = double(n%N)/double(N-1);
                
                n /= N;
            }

            LogLike(vec);
        }

        return 0;
    }
}
