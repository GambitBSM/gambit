//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Various container for WIMP particle  and
///  annihilation properties
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2019 Sep
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Sep
///
///  *********************************************

#ifndef __wimp_types_hpp__
#define __wimp_types_hpp__

#include <string>
#include <map>

namespace Gambit
{
    // Basic properties of generic WIMP
    struct WIMPprops
    {
      double mass;
      unsigned int spinx2;
      bool sc; // Self-conjugate?
      std::string name; // Name in the particle database
      std::string conjugate; // Name of conjugate in the particle database
    };

    /// Contain for generic parameterisation of WIMP annihilation to various two-body final states,
    /// with <sigma v> expanded as a simple power series in v^2
    class WIMP_annihilation
    {
        public:
            WIMP_annihilation();
            double A(const std::string& channel) const;
            double B(const std::string& channel) const;

            void setA(const std::string& channel, double val);
            void setB(const std::string& channel, double val);
        private:
            std::map<std::string,double> a;
            std::map<std::string,double> b;
    };

}

#endif //__wimp_types_hpp__
