//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class defining the parameters that SubSpectrum
///  objects providing Standard Model parameters
///  (minus the Higgs sector) must provide.
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

#include "gambit/Models/SpectrumContents/RegisteredSpectra.hpp"

namespace Gambit
{

  /// Only have to define the constructor
  SpectrumContents::SM_slha::SM_slha()
  {
     setName("SM_slha");

     std::vector<int> scalar = initVector(1);   // i.e. get(Par::Tag, "name")
     std::vector<int> v3     = initVector(3);   // i.e. get(Par::Tag, "name", i)

     // TEMP change: add all these back otherwise fill_spectrum_as_map does not work
 
     addParameter(Par::mass1, "u"   , v3);
     addParameter(Par::mass1, "d"   , v3);
     addParameter(Par::mass1, "e-"  , v3);
     //
     // SLHA SMINPUTS doesn't provide all those running masses. Only the light quarks:
     //addParameter(Par::mass1, "u_1", scalar); // u
     //addParameter(Par::mass1, "d_1", scalar); // d
     //addParameter(Par::mass1, "d_2", scalar); // s

     // doesn't provide these either, although they are just zero of course
     // TEMP change: add them otherwise fill_spectrum_as_map does not work
     addParameter(Par::mass1, "gamma", scalar);
     addParameter(Par::mass1, "g"    , scalar);

     // And we don't provide these either since they cannot be provided at the same scale.
     addParameter(Par::dimensionless, "alpha" , scalar);
     addParameter(Par::dimensionless, "alphaS", scalar);

     addParameter(Par::Pole_Mass, "gamma", scalar);
     addParameter(Par::Pole_Mass, "g"    , scalar);
     addParameter(Par::Pole_Mass, "Z0"   , scalar);
     addParameter(Par::Pole_Mass, "W+"   , scalar);

     addParameter(Par::Pole_Mass, "u_3" , scalar); // t
     addParameter(Par::Pole_Mass, "d_3" , scalar); // b

     addParameter(Par::Pole_Mass, "e-", v3);
     addParameter(Par::Pole_Mass, "nu", v3);

     addParameter(Par::Pole_Mixing, "sinW2", scalar);

     // Nearest flavour 'aliases' for the SM mass eigenstates
     addParameter(Par::Pole_Mass, "t" , scalar);
     addParameter(Par::Pole_Mass, "b" , scalar);

     addParameter(Par::Pole_Mass, "e-"  , scalar);
     addParameter(Par::Pole_Mass, "mu-" , scalar);
     addParameter(Par::Pole_Mass, "tau-", scalar);
  }

}
