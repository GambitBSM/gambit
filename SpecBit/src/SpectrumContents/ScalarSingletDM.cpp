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
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2016 Feb, 2019 Oct
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2016 Mar
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Sep
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct
///
///  *********************************************

#include "gambit/SpecBit/RegisteredSpectra.hpp"

namespace Gambit
{

  /////// Z2 model ///////
  SpectrumContents::ScalarSingletDM_Z2::ScalarSingletDM_Z2()
    : Contents("ScalarSingletDM_Z2")
  {
     // shape prototypes
     std::vector<int> scalar; // Empty vector, i.e. no indices, i.e.. get(Par::Tag, "name")
     std::vector<int> m3x3 = initVector(3,3);

     addParameter(Par::mass1, "vev", scalar, "VEVS", 1);
     addParameter(Par::dimensionless, "lambda_hS", scalar, "COUPLINGS", 1);
     addParameter(Par::dimensionless, "lambda_S" , scalar, "COUPLINGS", 2);
     addParameter(Par::dimensionless, "lambda_h" , scalar, "COUPLINGS", 3);

     addParameter(Par::Pole_Mass, "h0_1", scalar, "MASS");
     addParameter(Par::Pole_Mass, "S"   , scalar, "MASS");

     addParameter(Par::dimensionless, "g1", scalar, "GAUGE", 1);
     addParameter(Par::dimensionless, "g2", scalar, "GAUGE", 2);
     addParameter(Par::dimensionless, "g3", scalar, "GAUGE", 3);

     addParameter(Par::dimensionless, "sinW2", scalar, "SINTHETAW", 1);

     addParameter(Par::dimensionless, "Yd", m3x3, "YD");
     addParameter(Par::dimensionless, "Yu", m3x3, "YU");
     addParameter(Par::dimensionless, "Ye", m3x3, "YE");
  }

  /////// Z3 model ///////
  SpectrumContents::ScalarSingletDM_Z3::ScalarSingletDM_Z3()
    : Contents("ScalarSingletDM_Z3")
  {
     // shape prototypes
     std::vector<int> scalar; // Empty vector, i.e. no indices, i.e.. get(Par::Tag, "name")
     std::vector<int> m3x3 = initVector(3,3);

     addParameter(Par::mass1, "vev", scalar, "VEVS", 1);
     addParameter(Par::dimensionless, "lambda_hS", scalar, "COUPLINGS", 1);
     addParameter(Par::dimensionless, "lambda_S" , scalar, "COUPLINGS", 2);
     addParameter(Par::dimensionless, "lambda_h" , scalar, "COUPLINGS", 3);
     addParameter(Par::mass1, "mu3", scalar, "COUPLINGS", 4);

     addParameter(Par::Pole_Mass, "h0_1", scalar, "MASS");
     addParameter(Par::Pole_Mass, "S"   , scalar, "MASS");

     addParameter(Par::dimensionless, "g1", scalar, "GAUGE", 1);
     addParameter(Par::dimensionless, "g2", scalar, "GAUGE", 2);
     addParameter(Par::dimensionless, "g3", scalar, "GAUGE", 3);

     addParameter(Par::dimensionless, "sinW2", scalar, "SINTHETAW", 1);

     addParameter(Par::dimensionless, "Yd", m3x3, "YD");
     addParameter(Par::dimensionless, "Yu", m3x3, "YU");
     addParameter(Par::dimensionless, "Ye", m3x3, "YE");
  }

}
