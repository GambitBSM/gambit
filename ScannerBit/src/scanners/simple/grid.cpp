//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Grid sampler.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
//
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 August
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2026 May
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
#include <sstream>

#include "gambit/ScannerBit/scanner_plugin.hpp"

inline std::vector<std::unordered_set<std::string>> parse_sames(const std::vector<std::string> &params)
{
    std::vector<std::unordered_set<std::string>> paramSet(params.size());
    
    for (int i = 0, end = params.size(); i < end; i++)
    {
        std::string::size_type pos_old = 0;
        std::string::size_type pos = params[i].find("+");
        while (pos != std::string::npos)
        {
            paramSet[i].insert(params[i].substr(pos_old, (pos-pos_old)));
            pos_old = pos + 1;
            pos = params[i].find("+", pos_old);
        }

        paramSet[i].insert(params[i].substr(pos_old));
    }
    
    return paramSet;
}

scanner_plugin(grid, version(1, 0, 0))
{
    reqd_inifile_entries("grid_pts");
    
    plugin_constructor
    {
        
    }

    int plugin_main()
    {
        int ma = get_dimension();
        int numtasks;
        int rank;
        
#ifdef WITH_MPI
        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#else
        numtasks = 1;
        rank = 0;
#endif

        auto params = get_prior().getShownParameters();
        std::vector<std::unordered_set<std::string>> paramSet = parse_sames(params);

        YAML::Node grid_pts_node = get_inifile_node("grid_pts");
        if (!grid_pts_node || !grid_pts_node.IsMap())
        {
            scan_err << "Grid Scanner:  \"grid_pts\" must be a YAML map from "
                     << "\"<model>::<param>\" to integer, e.g.\n"
                     << "    grid_pts:\n"
                     << "      NormalDist::mu: 5\n"
                     << "      NormalDist::sigma: 3" << scan_end;
            return 1;
        }

        std::vector<int> N(ma, -1);

        for (auto it = grid_pts_node.begin(); it != grid_pts_node.end(); ++it)
        {
            std::string key = it->first.as<std::string>();
            int value = it->second.as<int>();

            int matched_index = -1;
            for (int i = 0; i < ma; ++i)
            {
                if (paramSet[i].find(key) != paramSet[i].end())
                {
                    matched_index = i;
                    break;
                }
            }

            if (matched_index < 0)
            {
                scan_err << "Grid Scanner:  parameter \"" << key
                         << "\" listed in grid_pts is not a scanned parameter." << scan_end;
            }
            else if (N[matched_index] != -1)
            {
                scan_err << "Grid Scanner:  parameter \"" << key
                         << "\" is specified more than once in grid_pts." << scan_end;
            }
            else
            {
                N[matched_index] = value;
            }
        }

        for (int i = 0; i < ma; ++i)
        {
            if (N[i] == -1)
            {
                scan_err << "Grid Scanner:  number of grid points for parameter \"" << params[i]
                         << "\" is not specified in grid_pts." << scan_end;
                N[i] = 1;
            }
        }

        int NTot = 1;

        for (auto it = N.begin(), end = N.end(); it != end; it++)
        {
            if (*it < 0)
                *it = -*it;
            else if (*it == 0)
                *it = 1;
            NTot *= *it;
        }

        if (rank == 0)
        {
            std::cout << "Grid Scanner:  parameter -> number of grid points mapping:" << std::endl;
            for (int i = 0; i < ma; ++i)
            {
                std::cout << "    " << params[i] << " -> " << N[i] << std::endl;                
            }
        }

        like_ptr LogLike;
        LogLike = get_purpose(get_inifile_value<std::string>("like"));
        std::vector<double> vec(ma, 0.0);

        for (int i = rank, end = NTot; i < end; i+=numtasks)
        {
            int n = i;
            for (int j = 0; j < ma; j++)
            {
                if (N[j] == 1)
                    vec[j] = 0.5;
                else
                    vec[j] = double(n%N[j])/double(N[j]-1);

                n /= N[j];
            }

            LogLike(vec);
        }

        return 0;
    }
}
