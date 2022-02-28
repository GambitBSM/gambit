//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class defining the parameters that SubSpectrum
///  objects providing DMEFT
///  spectrum data must provide.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 12:32PM on October 15, 2019
///                                                
///  ********************************************* 

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
  SpectrumContents::DMEFT::DMEFT()
  {
    setName("DMEFT");
    
    std::vector<int> scalar = initVector(1); // i.e. get(Par::Tag, "name")
    std::vector<int> m3x3   = initVector(3,3); // i.e. get(Par::Tag, "name", i, j)
    
    addParameter(Par::mass1, "Lambda", scalar, "WILSON", 1);
    addParameter(Par::dimensionless, "C51", scalar, "WILSON", 2);
    addParameter(Par::dimensionless, "C52", scalar, "WILSON", 3);
    addParameter(Par::dimensionless, "C61", scalar, "WILSON", 4);
    addParameter(Par::dimensionless, "C62", scalar, "WILSON", 5);
    addParameter(Par::dimensionless, "C63", scalar, "WILSON", 6);
    addParameter(Par::dimensionless, "C64", scalar, "WILSON", 7);
    addParameter(Par::dimensionless, "C71", scalar, "WILSON", 8);
    addParameter(Par::dimensionless, "C72", scalar, "WILSON", 9);
    addParameter(Par::dimensionless, "C73", scalar, "WILSON", 10);
    addParameter(Par::dimensionless, "C74", scalar, "WILSON", 11);
    addParameter(Par::dimensionless, "C75", scalar, "WILSON", 12);
    addParameter(Par::dimensionless, "C76", scalar, "WILSON", 13);
    addParameter(Par::dimensionless, "C77", scalar, "WILSON", 14);
    addParameter(Par::dimensionless, "C78", scalar, "WILSON", 15);
    addParameter(Par::dimensionless, "C79", scalar, "WILSON", 16);
    addParameter(Par::dimensionless, "C710", scalar, "WILSON", 17);
    addParameter(Par::mass1, "vev", scalar);
    addParameter(Par::dimensionless, "g1", scalar, "GAUGE", 1);
    addParameter(Par::dimensionless, "g2", scalar, "GAUGE", 2);
    addParameter(Par::dimensionless, "g3", scalar, "GAUGE", 3);
    addParameter(Par::dimensionless, "sinW2", scalar);
    addParameter(Par::dimensionless, "Yd", m3x3, "YD", 1);
    addParameter(Par::dimensionless, "Yu", m3x3, "YU", 1);
    addParameter(Par::dimensionless, "Ye", m3x3, "YE", 1);
    addParameter(Par::Pole_Mass, "chi", scalar, "MASS", 62);
    addParameter(Par::Pole_Mass, "h0_1", scalar, "MASS", 25);
    
  } // namespace Models
} // namespace Gambit
