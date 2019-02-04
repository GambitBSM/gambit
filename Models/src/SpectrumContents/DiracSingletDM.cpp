//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class defining the parameters that SubSpectrum
///  objects providing DiracSingletDM spectrum
///  data must provide
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Aug, 2017 Jun
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2018 Aug
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Sep
///
///  *********************************************

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{

  SpectrumContents::DiracSingletDM_Z2::DiracSingletDM_Z2()
  {
     setName("DiracSingletDM_Z2");

     // shape prototypes
     std::vector<int> m3x3 = initVector(3,3);

     addParameter(Par::mass1, "vev");
     addParameter(Par::dimensionless, "lF");
     addParameter(Par::dimensionless, "lambda_h");
     addParameter(Par::dimensionless, "xi");

     addParameter(Par::Pole_Mass, "h0_1");
     addParameter(Par::Pole_Mass, "F" );

     addParameter(Par::dimensionless, "g1");
     addParameter(Par::dimensionless, "g2");
     addParameter(Par::dimensionless, "g3");

     addParameter(Par::dimensionless, "sinW2");

     addParameter(Par::dimensionless, "Yd", m3x3);
     addParameter(Par::dimensionless, "Yu", m3x3);
     addParameter(Par::dimensionless, "Ye", m3x3);
  }

}
