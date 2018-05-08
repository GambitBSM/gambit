//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class defining the parameters that SubSpectrum
///  objects providing Scalar Singlet Dark Matter
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
///  *********************************************

#ifndef __THDM_contents_hpp__
#define __THDM_contents_hpp__

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit {
  
  /// Only have to define the constructor
  SpectrumContents::THDM::THDM()
  {
    setName("THDM");
    
    addParameter(Par::Pole_Mass, "mh0");
    addParameter(Par::Pole_Mass, "mH0");
    addParameter(Par::Pole_Mass, "mA");
    addParameter(Par::Pole_Mass, "mC");

    addParameter(Par::mass1, "m12_2");
    addParameter(Par::dimensionless, "alpha");
    addParameter(Par::dimensionless, "tanb");
    
    addParameter(Par::mass1, "lambda_1");
    addParameter(Par::mass1, "lambda_2");
    addParameter(Par::mass1, "lambda_3");
    addParameter(Par::mass1, "lambda_4");
    addParameter(Par::mass1, "lambda_5");
    addParameter(Par::mass1, "lambda_6");
    addParameter(Par::mass1, "lambda_7");
    
  }
  
}
#endif
