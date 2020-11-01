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
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
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

    // gayge couplings, weinberg angle and vevs
    addParameter(Par::dimensionless, "g1", scalar);
    addParameter(Par::dimensionless, "g2", scalar);
    addParameter(Par::dimensionless, "g3", scalar);
    addParameter(Par::dimensionless, "sinW2", scalar);
    addParameter(Par::mass1, "vev", scalar);
    addParameter(Par::mass1, "v1", scalar);
    addParameter(Par::mass1, "v2", scalar);

    // yukawas
    addParameter(Par::dimensionless, "Yd", m3x3);
    addParameter(Par::dimensionless, "Yu", m3x3);
    addParameter(Par::dimensionless, "Ye", m3x3);

    // pole masses
    addParameter(Par::Pole_Mass, "h0",    v2);
    addParameter(Par::Pole_Mass, "A0", scalar);
    addParameter(Par::Pole_Mass, "H+", scalar);
    addParameter(Par::Pole_Mass, "W+", scalar);

    // running masses
    addParameter(Par::mass1, "h0",    v2);
    addParameter(Par::mass1, "A0", scalar);
    addParameter(Par::mass1, "H+", scalar);
    addParameter(Par::mass1, "W+", scalar);

    // generic basis
    addParameter(Par::mass1, "lambda_1");
    addParameter(Par::mass1, "lambda_2");
    addParameter(Par::mass1, "lambda_3");
    addParameter(Par::mass1, "lambda_4");
    addParameter(Par::mass1, "lambda_5");
    addParameter(Par::mass1, "lambda_6");
    addParameter(Par::mass1, "lambda_7");
    addParameter(Par::mass1, "m12_2");
    addParameter(Par::mass1, "m11_2");
    addParameter(Par::mass1, "m22_2");

    // higgs basis
    addParameter(Par::mass1, "Lambda_1");
    addParameter(Par::mass1, "Lambda_2");
    addParameter(Par::mass1, "Lambda_3");
    addParameter(Par::mass1, "Lambda_4");
    addParameter(Par::mass1, "Lambda_5");
    addParameter(Par::mass1, "Lambda_6");
    addParameter(Par::mass1, "Lambda_7");
    addParameter(Par::mass1, "M12_2");
    addParameter(Par::mass1, "M11_2");
    addParameter(Par::mass1, "M22_2");

    // angles
    addParameter(Par::dimensionless, "tanb");
    addParameter(Par::dimensionless, "beta");
    addParameter(Par::dimensionless, "alpha");
    
  }
  
}
#endif
