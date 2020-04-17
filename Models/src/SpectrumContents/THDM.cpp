//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class defining the parameters that SubSpectrum
///  objects providing THDM
///  spectrum data must provide
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Filip Rajec
///   June 2016
///
///  Cristian Sierra
///  cristian.sierra@monash.edu
///  Apr 2020 
///
///  *********************************************

#ifndef __THDM_contents_hpp__
#define __THDM_contents_hpp__

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit {
  
  /// Only have to define the constructor
  SpectrumContents::THDM::THDM()
  {
    setName("THDM");
    std::vector<int> scalar = initVector(1);   // i.e. get(Par::Tag, "name")
    std::vector<int> v2     = initVector(2);   // i.e. get(Par::Tag, "name", i)
    std::vector<int> v3     = initVector(3);   // "
    std::vector<int> v4     = initVector(4);   // "
    std::vector<int> v6     = initVector(6);   // "
    std::vector<int> m2x2   = initVector(2,2); // i.e. get(Par::Tag, "name", i, j)
    std::vector<int> m3x3   = initVector(3,3); // "
    std::vector<int> m4x4   = initVector(4,4); // "
    std::vector<int> m6x6   = initVector(6,6); // "

    addParameter(Par::dimensionless, "g1", scalar,"GAUGE",1);
    addParameter(Par::dimensionless, "g2", scalar,"GAUGE",2);
    addParameter(Par::dimensionless, "g3", scalar,"GAUGE",3);

    addParameter(Par::dimensionless, "sinW2", scalar);

    addParameter(Par::dimensionless, "Yd", m3x3, "Yd");
    addParameter(Par::dimensionless, "Yu", m3x3, "Yu");
    addParameter(Par::dimensionless, "Ye", m3x3, "Ye");

    // addParameter(Par::dimensionless, "ReYd2", m3x3);
    // addParameter(Par::dimensionless, "ReYu2", m3x3);
    // addParameter(Par::dimensionless, "ReYe2", m3x3);

    // addParameter(Par::dimensionless, "ImYd2", m3x3);
    // addParameter(Par::dimensionless, "ImYu2", m3x3);
    // addParameter(Par::dimensionless, "ImYe2", m3x3);

    addParameter(Par::Pole_Mass, "h0",    v2); 
    addParameter(Par::Pole_Mass, "A0", scalar,"MASS",36); 
    addParameter(Par::Pole_Mass, "H+", scalar,"MASS",37);
    addParameter(Par::Pole_Mass, "W+", scalar,"MASS",24);

    addParameter(Par::mass1, "lambda1",scalar,"MINPAR",11);
    addParameter(Par::mass1, "lambda2",scalar,"MINPAR",12);
    addParameter(Par::mass1, "lambda3",scalar,"MINPAR",13);
    addParameter(Par::mass1, "lambda4",scalar,"MINPAR",14);
    addParameter(Par::mass1, "lambda5",scalar,"MINPAR",15);
    addParameter(Par::mass1, "lambda6",scalar,"MINPAR",16);
    addParameter(Par::mass1, "lambda7",scalar,"MINPAR",17);

    addParameter(Par::dimensionless, "tanb",scalar,"MINPAR",3);
    addParameter(Par::dimensionless, "alpha",scalar, "ALPHA",0);
    addParameter(Par::mass1, "m12_2",scalar,"MINPAR",18);

  }
  
}
#endif
