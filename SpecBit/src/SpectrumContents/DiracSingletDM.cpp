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
///  \author Ben Farmer
///          (benjamin.farmer@imperial.ac.uk)
///  \date 2019 Oct
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct
///
///  *********************************************

#include "gambit/SpecBit/RegisteredSpectra.hpp"

namespace Gambit
{

  SpectrumContents::DiracSingletDM_Z2::DiracSingletDM_Z2()
   : Contents("DiracSingletDM_Z2")
  {

     // shape prototypes
     std::vector<int> scalar; // Empty vector, i.e. no indices, i.e.. get(Par::Tag, "name")
     std::vector<int> m3x3 = initVector(3,3);

     addParameter(Par::mass1, "vev", scalar, "VEVS", 1);
     addParameter(Par::dimensionless, "lF",       scalar, "COUPLINGS", 1);
     addParameter(Par::dimensionless, "lambda_h", scalar, "COUPLINGS", 2);
     addParameter(Par::dimensionless, "xi",       scalar, "COUPLINGS", 3);

     addParameter(Par::Pole_Mass, "h0_1", scalar, "MASS"); // Index is PDG code, determined using particle database
     addParameter(Par::Pole_Mass, "F" ,   scalar, "MASS");

     addParameter(Par::dimensionless, "g1", scalar, "GAUGE", 1);
     addParameter(Par::dimensionless, "g2", scalar, "GAUGE", 2);
     addParameter(Par::dimensionless, "g3", scalar, "GAUGE", 3);

     addParameter(Par::dimensionless, "sinW2", scalar, "SINTHETAW", 1);

     addParameter(Par::dimensionless, "Yd", m3x3, "YD");
     addParameter(Par::dimensionless, "Yu", m3x3, "YU");
     addParameter(Par::dimensionless, "Ye", m3x3, "YE");
  }

}
