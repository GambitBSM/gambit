//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class defining the parameters that SubSpectrum
///  objects providing Inert
///  spectrum data must provide.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:33PM on February 18, 2026
///                                                
///  ********************************************* 

#ifndef __Inert_contents_hpp__
#define __Inert_contents_hpp__

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{
  SpectrumContents::Inert::Inert()
  {
    setName("Inert");
    
    std::vector<int> scalar = initVector(1); // i.e. get(Par::Tag, "name")
    std::vector<int> m3x3  = initVector(3,3); // i.e. get(Par::Tag, "name", i, j)
    std::vector<int> m2x2  = initVector(2,2); // i.e. get(Par::Tag, "name", i, j)
    
    addParameter(Par::dimensionless, "mHd2", scalar, "MSOFT", 21);
    addParameter(Par::dimensionless, "mHu2", scalar, "MSOFT", 22);
    addParameter(Par::dimensionless, "v", scalar, "HMIX", 3);
    addParameter(Par::Pole_Mixing, "ZP", m2x2, "CHARGEMIX", 1);
    addParameter(Par::Pole_Mixing, "ZEL", m3x3, "UELMIX", 1);
    addParameter(Par::Pole_Mixing, "ZER", m3x3, "UERMIX", 1);
    addParameter(Par::Pole_Mixing, "ZDL", m3x3, "UDLMIX", 1);
    addParameter(Par::Pole_Mixing, "ZDR", m3x3, "UDRMIX", 1);
    addParameter(Par::Pole_Mixing, "ZUL", m3x3, "UULMIX", 1);
    addParameter(Par::Pole_Mixing, "ZUR", m3x3, "UURMIX", 1);
    addParameter(Par::dimensionless, "Lam1", scalar, "HDM", 1);
    addParameter(Par::dimensionless, "Lam2", scalar, "HDM", 2);
    addParameter(Par::dimensionless, "Lam3", scalar, "HDM", 3);
    addParameter(Par::dimensionless, "Lam4", scalar, "HDM", 4);
    addParameter(Par::dimensionless, "Lam5", scalar, "HDM", 5);
    addParameter(Par::dimensionless, "g1", scalar, "GAUGE", 1);
    addParameter(Par::dimensionless, "g2", scalar, "GAUGE", 2);
    addParameter(Par::dimensionless, "g3", scalar, "GAUGE", 3);
    addParameter(Par::dimensionless, "Yd", m3x3, "YD", 1);
    addParameter(Par::dimensionless, "Yu", m3x3, "YU", 1);
    addParameter(Par::dimensionless, "Ye", m3x3, "YE", 1);
    addParameter(Par::Pole_Mass, "h0_1", scalar, "MASS", 25);
    addParameter(Par::Pole_Mass, "h0_2", scalar, "MASS", 35);
    addParameter(Par::Pole_Mass, "A0", scalar, "MASS", 36);
    addParameter(Par::Pole_Mass, "H+", scalar, "MASS", 37);
    
  } // namespace Models
} // namespace Gambit
#endif
