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
///  \date 2016 Feb
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2016 Mar
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Sep
///
///  *********************************************

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{

  /////// Z2 model ///////
  SpectrumContents::ScalarSingletDM_Z2::ScalarSingletDM_Z2()
  {
     setName("ScalarSingletDM_Z2");

     // shape prototypes
     std::vector<int> m3x3 = initVector(3,3);

     addParameter(Par::mass1, "vev");
     addParameter(Par::dimensionless, "lambda_hS");
     addParameter(Par::dimensionless, "lambda_S");
     addParameter(Par::dimensionless, "lambda_h");

     addParameter(Par::Pole_Mass, "h0_1");
     addParameter(Par::Pole_Mass, "S" );

     addParameter(Par::dimensionless, "g1");
     addParameter(Par::dimensionless, "g2");
     addParameter(Par::dimensionless, "g3");

     addParameter(Par::dimensionless, "sinW2");

     addParameter(Par::dimensionless, "Yd", m3x3);
     addParameter(Par::dimensionless, "Yu", m3x3);
     addParameter(Par::dimensionless, "Ye", m3x3);
  }

  /////// Z3 model ///////
  SpectrumContents::ScalarSingletDM_Z3::ScalarSingletDM_Z3()
  {
     setName("ScalarSingletDM_Z3");

     // shape prototypes
     std::vector<int> m3x3 = initVector(3,3);

     addParameter(Par::mass1, "vev");
     addParameter(Par::dimensionless, "lambda_hS");
     addParameter(Par::dimensionless, "lambda_S");
     addParameter(Par::dimensionless, "lambda_h");
     addParameter(Par::mass1, "mu3");

     addParameter(Par::Pole_Mass, "h0_1");
     addParameter(Par::Pole_Mass, "S" );

     addParameter(Par::dimensionless, "g1");
     addParameter(Par::dimensionless, "g2");
     addParameter(Par::dimensionless, "g3");

     addParameter(Par::dimensionless, "sinW2");

     addParameter(Par::dimensionless, "Yd", m3x3);
     addParameter(Par::dimensionless, "Yu", m3x3);
     addParameter(Par::dimensionless, "Ye", m3x3);
  }

}
