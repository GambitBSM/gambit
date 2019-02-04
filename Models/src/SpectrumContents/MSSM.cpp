//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class defining the parameters that SubSpectrum
///  objects providing MSSM spectrum data must provide
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
///  *********************************************

#ifndef __mssmcontents_hpp__
#define __mssmcontents_hpp__

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit {

  /// Only have to define the constructor
  SpectrumContents::MSSM::MSSM()
  {
     setName("MSSM");

     // shape prototypes
     std::vector<int> scalar = initVector(1);   // i.e. get(Par::Tag, "name")
     std::vector<int> v2     = initVector(2);   // i.e. get(Par::Tag, "name", i)
     std::vector<int> v3     = initVector(3);   // "
     std::vector<int> v4     = initVector(4);   // "
     std::vector<int> v6     = initVector(6);   // "
     std::vector<int> m2x2   = initVector(2,2); // i.e. get(Par::Tag, "name", i, j)
     std::vector<int> m3x3   = initVector(3,3); // "
     std::vector<int> m4x4   = initVector(4,4); // "
     std::vector<int> m6x6   = initVector(6,6); // "

     //           tag,        name,   shape
     addParameter(Par::mass2, "BMu" , scalar);
     addParameter(Par::mass2, "mHd2", scalar);
     addParameter(Par::mass2, "mHu2", scalar);

     addParameter(Par::mass2, "mq2", m3x3);
     addParameter(Par::mass2, "ml2", m3x3);
     addParameter(Par::mass2, "md2", m3x3);
     addParameter(Par::mass2, "mu2", m3x3);
     addParameter(Par::mass2, "me2", m3x3);

     addParameter(Par::mass1, "M1", scalar);
     addParameter(Par::mass1, "M2", scalar);
     addParameter(Par::mass1, "M3", scalar);
     addParameter(Par::mass1, "Mu", scalar);
     addParameter(Par::mass1, "vu", scalar);
     addParameter(Par::mass1, "vd", scalar);

     addParameter(Par::mass1, "TYd", m3x3);
     addParameter(Par::mass1, "TYe", m3x3);
     addParameter(Par::mass1, "TYu", m3x3);
     addParameter(Par::mass1, "ad" , m3x3);
     addParameter(Par::mass1, "ae" , m3x3);
     addParameter(Par::mass1, "au" , m3x3);

     // EXTRAS! Kind of logical to always include these, without forcing users to calculate them themselves
     addParameter(Par::dimensionless, "tanbeta", scalar);
     //addParameter(Par::dimensionless, "tanbeta(mZ)", scalar); // i.e. the SLHA MINPAR value of tanbeta(mZ). Not yet a strict requirement, but highly recommended for wrappers to add it via override setters.
     addParameter(Par::mass2, "mA2" , scalar);
     //

     addParameter(Par::dimensionless, "g1", scalar);
     addParameter(Par::dimensionless, "g2", scalar);
     addParameter(Par::dimensionless, "g3", scalar);

     addParameter(Par::dimensionless, "sinW2", scalar);

     addParameter(Par::dimensionless, "Yd", m3x3);
     addParameter(Par::dimensionless, "Yu", m3x3);
     addParameter(Par::dimensionless, "Ye", m3x3);

     addParameter(Par::Pole_Mass, "~g", scalar);

     addParameter(Par::Pole_Mass, "~d",    v6);
     addParameter(Par::Pole_Mass, "~u",    v6);
     addParameter(Par::Pole_Mass, "~e-",   v6);
     addParameter(Par::Pole_Mass, "~nu",   v3);
     addParameter(Par::Pole_Mass, "~chi+", v2);
     addParameter(Par::Pole_Mass, "~chi0", v4);
     addParameter(Par::Pole_Mass, "h0",    v2);
     addParameter(Par::Pole_Mass, "A0", scalar);
     addParameter(Par::Pole_Mass, "H+", scalar);
     addParameter(Par::Pole_Mass, "W+", scalar);

     addParameter(Par::Pole_Mixing, "~d",    m6x6);
     addParameter(Par::Pole_Mixing, "~u",    m6x6);
     addParameter(Par::Pole_Mixing, "~e-",   m6x6);
     addParameter(Par::Pole_Mixing, "~nu",   m3x3);
     addParameter(Par::Pole_Mixing, "~chi0", m4x4);
     addParameter(Par::Pole_Mixing, "~chi-", m2x2);
     addParameter(Par::Pole_Mixing, "~chi+", m2x2);
     addParameter(Par::Pole_Mixing, "h0",    m2x2);
     addParameter(Par::Pole_Mixing, "A0",    m2x2);
     addParameter(Par::Pole_Mixing, "H+",    m2x2);
  }

}
#endif
