//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definition of the container for EFT 
///  parameterisation of WIMP
///  annihilations to SM particles
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2019 Sep
///
///  *********************************************

#include "gambit/Elements/wimp_types.hpp"

namespace Gambit
{
    /// Set up generic parameterisation of WIMP self-annihilation cross-section (A + Bv^2) 
    WIMP_annihilation::WIMP_annihilation()
    {}
    
    double WIMP_annihilation::A(const std::string& channel) const
    {
       double out;
       auto it = a.find(channel);
       if(it==a.end())
       {
          out = 0;
       }
       else
       {
          out = it->second;
       }
       return out;
    }

    double WIMP_annihilation::B(const std::string& channel) const
    {
       double out;
       auto it = a.find(channel);
       if(it==a.end())
       {
          out = 0;
       }
       else
       {
          out = it->second;
       }
       return out;
    }

    void WIMP_annihilation::setA(const std::string& channel, double val)
    {
       a[channel] = val;
    }

    void WIMP_annihilation::setB(const std::string& channel, double val)
    {
       b[channel] = val;
    }
}
