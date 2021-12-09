//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class defining the parameters that Spectrum
///  objects providing Standard Model parameters
///  must provide.
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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct
///
///  *********************************************

#include "gambit/SpecBit/RegisteredSpectra.hpp"

namespace Gambit {

  /// Only have to define the constructor
  SpectrumContents::SM::SM()
    : Contents("SM")
  {
     std::vector<int> scalar; // Empty vector means no indices   // i.e. get(Par::Tag, "name")
     std::vector<int> v3     = initVector(3);   // i.e. get(Par::Tag, "name", i)

     addParameter(Par::dimensionless, "alphainv", scalar, "SMINPUTS", 1); // TODO: Was 'alpha'. Needs consideration.
     addParameter(Par::imass2, "GF", scalar, "SMINPUTS", 2); // So far the only example of inverse mass dimension usage. Should be useful for other EFT couplings though.
     addParameter(Par::dimensionless, "alphaS",   scalar, "SMINPUTS", 3);

     addParameter(Par::Pole_Mass, "gamma", scalar, "MASS");
     addParameter(Par::Pole_Mass, "g"    , scalar, "MASS");
     addParameter(Par::Pole_Mass, "Z0"   , scalar, "SMINPUTS", 4);
     addParameter(Par::Pole_Mass, "W+"   , scalar, "MASS");

     addParameter(Par::Pole_Mass, "u_3" , scalar, "SMINPUTS", 6);
     addParameter(Par::mass1, "d_3" , scalar, "SMINPUTS", 5); // Not a pole mass but MSbar

     addParameter(Par::Pole_Mass, "nu_1", scalar, "SMINPUTS", 12);
     addParameter(Par::Pole_Mass, "nu_2", scalar, "SMINPUTS", 14);
     addParameter(Par::Pole_Mass, "nu_3", scalar, "SMINPUTS", 8);

     // SLHA SMINPUTS doesn't provide all those running masses. Only the light quarks:
     addParameter(Par::mass1, "u_1", scalar, "SMINPUTS", 22); // u
     addParameter(Par::mass1, "d_1", scalar, "SMINPUTS", 21); // d
     addParameter(Par::mass1, "d_2", scalar, "SMINPUTS", 23); // s
     addParameter(Par::mass1, "u_2", scalar, "SMINPUTS", 24); // c

     addParameter(Par::Pole_Mass, "e-_1"  , scalar, "SMINPUTS", 11);
     addParameter(Par::Pole_Mass, "e-_2" , scalar, "SMINPUTS", 13);
     addParameter(Par::Pole_Mass, "e-_3", scalar, "SMINPUTS", 7);


     // Weinberg angle
     addParameter(Par::Pole_Mixing, "sinW2", scalar, "SINTHETAW", 2);

     // Additional pole masses for SMInputs running masses
     addParameter(Par::Pole_Mass, "d_3", scalar, "MASS"); // b

     // Nearest flavour 'aliases' for the SM mass eigenstates
     addParameter(Par::Pole_Mass, "t" , scalar, "MASS");
     addParameter(Par::Pole_Mass, "b" , scalar, "MASS");

     addParameter(Par::Pole_Mass, "e-"  , scalar, "MASS");
     addParameter(Par::Pole_Mass, "mu-" , scalar, "MASS");
     addParameter(Par::Pole_Mass, "tau-", scalar, "MASS");

     // Higgs mass and vev
     addParameter(Par::Pole_Mass, "h0_1", scalar, "MASS");
     addParameter(Par::mass1, "v", scalar, "VEVS");

     // CKM matrix
     addParameter(Par::dimensionless, "CKM_lambda", scalar, "VCKM", 1);
     addParameter(Par::dimensionless, "CKM_A", scalar, "VCKM", 2);
     addParameter(Par::dimensionless, "CKM_rhobar", scalar, "VCKM", 3);
     addParameter(Par::dimensionless, "CKM_etabar", scalar, "VCKM", 4);

     // PMNS matrix
     addParameter(Par::dimensionless, "theta12", scalar, "UPMNS", 1);
     addParameter(Par::dimensionless, "theta23", scalar, "UPMNS", 2);
     addParameter(Par::dimensionless, "theta13", scalar, "UPMNS", 3);
     addParameter(Par::dimensionless, "delta13", scalar, "UPMNS", 4);
     addParameter(Par::dimensionless, "alpha1", scalar, "UPMNS", 5);
     addParameter(Par::dimensionless, "alpha2", scalar, "UPMNS", 6);
  }

}
