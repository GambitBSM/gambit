//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Toy MCMC sampler.
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
#include "gambit/Utils/threadsafe_rng.hpp"

scanner_plugin(raster, version(1, 0, 0))
{
    std::map<std::string, std::vector<double>> param_map;
    int N = 0, numtasks, rank;
    
    plugin_constructor
    {
        YAML::Node node = get_inifile_node("parameters");
        
        if (!node)
        {
            scan_err << "Need to specify a set of parameters in parameters subsection." << scan_end;
        }
        
        if (!node.IsMap())
        {
            scan_err << "parameters subsection needs to be of map formatt." << scan_end;
        }
        
        for (auto it = node.begin(), end = node.end(); it != end; ++it)
        {
            param_map[it->first.as<std::string>()] = get_yaml_vector<double>(it->second);
            int temp = param_map[it->first.as<std::string>()].size();
            if (temp > N)
                N = temp;
        }
        
#ifdef WITH_MPI
        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#else
        numtasks = 1;
        rank = 0;
#endif
    }

    int plugin_main (void)
    {
        like_ptr LogLike    = get_purpose(get_inifile_value<std::string>("like"));
        int ma              = get_dimension();
        std::vector<double> a(ma);

        std::cout << "Starting Raster Scanner over " << N << " points." << ma << std::endl;

        for (int i = rank; i < N; i+=numtasks)
        {
            std::unordered_map<std::string, double> map;
            for (auto it = param_map.begin(), end = param_map.end(); it != end; ++it)
            {
                map[it->first] = it->second[i%it->second.size()];
            }
            
            for (int j = 0; j < ma; j++)
            {
                a[j] = Gambit::Random::draw();
            }

            LogLike(map, a);
            std::cout << "Point " << i << " done." << std::endl;
        }
        
        std::cout << "Finished!" << std::endl;

        return 0;
    }
}

