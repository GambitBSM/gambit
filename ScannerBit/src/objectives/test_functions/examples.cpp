//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Base functions objects for use in GAMBIT.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///           (gregory.david.martinez@gmail.com)
///  \date 2014 MAY
///
///  *********************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

#include "gambit/ScannerBit/objective_plugin.hpp"
#include "gambit/ScannerBit/cholesky.hpp"

objective_plugin(uniform, version(1,0,0))
{
    double plugin_main (std::unordered_map<std::string, double> /*&map*/)
    {
        return 0;
    }
}

objective_plugin(gaussian, version(1, 0, 0))
{
    Gambit::Cholesky chol;
    std::vector <double> mean;
    std::vector<std::vector<double>> cov;
    unsigned int dim;
    
    plugin_constructor
    {
        dim = get_keys().size();
        std::vector<std::vector<double>> cov(dim, std::vector<double>(dim, 0));
                
        cov = get_inifile_value<std::vector<std::vector<double>>> ("cov", cov);
        
        if (cov.size() != dim)
        {
            scan_err << "Gaussian: Coverance matrix size of " << cov.size() << " is different than the parameter size of " << dim << scan_end;
        }
        
        for (std::vector<std::vector<double>>::iterator it = cov.begin(); it != cov.end(); it++)
        {
            if (it->size() != cov.size())
            {
                scan_err << "Gaussian: Coverance matrix is not square" << scan_end;
            }
        }
        
        if (!chol.EnterMat(cov))
        {
            std::vector <double> sigs = get_inifile_value <std::vector <double>> ("sigs", std::vector<double>(dim, 1.0));
            if (sigs.size() != dim)
            {
                scan_err << "Gaussian: Sigma vector size of " << sigs.size() << " is different than the parameter size of " << dim << scan_end;
            }
            else
            {
                for (int i = 0, end = sigs.size(); i < end; i++)
                {
                    cov[i][i] = sigs[i]*sigs[i];
                }
            }
        }
        
        mean = get_inifile_value<std::vector <double>> ("mean", std::vector <double>(dim, 0));
        
        if (!chol.EnterMat(cov))
        {
            scan_err << "Gaussian: Covariance matrix is not positive definite." << scan_end;
        }
    }
    
    double plugin_main(std::unordered_map<std::string, double> &map)
    {
        static std::vector<double> params(get_keys().size());
        
        print_parameters(map);
        
        auto it_p = params.begin();
        for (auto it = get_keys().begin(), end = get_keys().end(); it != end; ++it, ++it_p)
        {
            *it_p = map[*it];
        }
        
        return -chol.Square(params, mean)/2.0;
    }
}

objective_plugin(normal_example, version(1, 0, 0))
{
    plugin_constructor
    {
        int dim = get_keys().size();
        
        if (dim != 2)
        {
            scan_err << "Normal: Need to have two parameters." << scan_end;
        }
    }
    
    constexpr double SQ(double a) {return a*a;}
    
    double plugin_main(std::unordered_map<std::string, double> &map)
    {
        print_parameters(map);
        
        static const int N = 20;
        static const double samples [] = {
            21.32034213,  20.39713359,  19.27957134,  19.81839231,
            20.89474358,  20.11058756,  22.38214557,  21.41479798,
            23.49896999,  17.55991187,  24.9921142 ,  23.90166585,
            20.97913273,  18.59180551,  23.49038072,  19.08201714,
            21.19538797,  16.42544039,  18.93568891,  22.40925288
            };
        
        double ret = 0.0;
        for (int i = 0; i < N; i++)
            ret += SQ((samples[i] - map["Normal::mu"])/map["Normal::sigma"]);
        
        return -ret/2.0 - N*std::log(map["Normal::sigma"]);
    }
}

objective_plugin(EggBox, version(1, 0, 0))
{
    std::pair <double, double> length;
    unsigned int dim;
    
    plugin_constructor
    {
        dim = get_keys().size();
        
        if (dim != 2)
        {
            scan_err << "EggBox: Need to have two parameters." << scan_end;
        }
        length = get_inifile_value<std::pair<double, double> > ("length", std::pair<double, double>(10.0, 10.0));
    }
    
    double plugin_main(std::unordered_map<std::string, double> &map)
    {
        print_parameters(map);
        
        double params[2];
        params[0] = map[get_keys()[0]]*length.first;
        params[1] = map[get_keys()[1]]*length.second;
        
        return 5.0*std::log(2.0 + std::cos(params[0]*M_PI_2)*std::cos(params[1]*M_PI_2));
    }
}

objective_plugin(flat_prior, version(1, 0, 0))
{
    std::vector<std::string> keys;
    std::pair<double, double> range;
    
    plugin_constructor
    {
        keys = get_keys();
        set_dimension(keys.size());
        range = get_inifile_value<decltype(range)>("range", decltype(range)(0.0, 1.0));
    }
    
    void plugin_main(const std::vector<double> &unitpars, std::unordered_map<std::string, double> &outputMap)
    {
        auto u_it = unitpars.begin();
        for (auto it = keys.begin(), end = keys.end(); it != end; it++)
            outputMap[*it] = range.first + (range.second - range.first)*(*u_it++);
    }
    
    double plugin_main(const std::vector<double>&)
    {
        return 0.0;
    }
}
