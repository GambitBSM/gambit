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
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2018 April
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

#ifndef __MDM_contents_hpp__
#define __MDM_contents_hpp__

#include "gambit/SpecBit/RegisteredSpectra.hpp"

namespace Gambit {

  SpectrumContents::MDM::MDM()
   : Contents("MDM")
  {
     std::vector<int> scalar = initVector(1);   // i.e. get(Par::Tag, "name")
     std::vector<int> v2     = initVector(2);   // i.e. get(Par::Tag, "name", i)
     std::vector<int> v3     = initVector(3);   // "
     std::vector<int> v4     = initVector(4);   // "
     std::vector<int> v6     = initVector(6);   // "
     std::vector<int> m2x2   = initVector(2,2); // i.e. get(Par::Tag, "name", i, j)
     std::vector<int> m3x3   = initVector(3,3); // "
     std::vector<int> m4x4   = initVector(4,4); // "
     std::vector<int> m6x6   = initVector(6,6); // "
  


     addParameter(Par::mass1, "vev", scalar, "VEVS", 1);

     addParameter(Par::Pole_Mass, "h0_1", scalar, "MASS");
     
     addParameter(Par::Pole_Mass, "Chi0", scalar, "MASS"); // TODO: These need to be added to the particle database!
     addParameter(Par::Pole_Mass, "Chi1", scalar, "MASS");
     addParameter(Par::Pole_Mass, "Chi2", scalar, "MASS");
     
     addParameter(Par::dimensionless, "lambda_h", scalar , "COUPLINGS", 1);
    
     addParameter(Par::dimensionless, "g1", scalar, "GAUGE", 1);
     addParameter(Par::dimensionless, "g2", scalar, "GAUGE", 2);
     addParameter(Par::dimensionless, "g3", scalar, "GAUGE", 3);
    
     addParameter(Par::dimensionless, "sinW2", scalar, "SINTHETAW", 1);
  
     addParameter(Par::dimensionless, "Yd", m3x3, "YD");
     addParameter(Par::dimensionless, "Yu", m3x3, "YU");
     addParameter(Par::dimensionless, "Ye", m3x3, "YE");
  }

}
#endif
