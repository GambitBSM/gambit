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
///          (benjamin.farmer@imperial.ac.uk)
///  \date 2016 Feb, 2019 Oct
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct
///
///  *********************************************

#include "gambit/SpecBit/RegisteredSpectra.hpp"

namespace Gambit
{

  /// Only have to define the constructor
  SpectrumContents::SM_slha::SM_slha()
    : Contents("SM_slha")
  {
     std::vector<int> scalar;   // i.e. get(Par::Tag, "name")
     std::vector<int> v3 = initVector(3);   // i.e. get(Par::Tag, "name", i)

     //addParameter(Par::mass1, "u"   , v3);
     //addParameter(Par::mass1, "d"   , v3);
     //addParameter(Par::mass1, "e-"  , v3);
     //
     // SLHA SMINPUTS doesn't provide all those running masses. Only the light quarks:
     addParameter(Par::mass1, "u_1", scalar, "SMINPUTS", 22); // u
     addParameter(Par::mass1, "d_1", scalar, "SMINPUTS", 21); // d
     addParameter(Par::mass1, "d_2", scalar, "SMINPUTS", 23); // s
     addParameter(Par::mass1, "u_2", scalar, "SMINPUTS", 24); // c

     // Some extra stuff from SMINPUTS that we need to store just so that we can spit it out again when writing SLHA files
     addParameter(Par::dimensionless, "invalpha_em(MZ)_MSbar", scalar, "SMINPUTS", 1);
     addParameter(Par::dimensionless, "alpha_s(MZ)_MSbar",     scalar, "SMINPUTS", 3);
     addParameter(Par::imass2, "GF", scalar, "SMINPUTS", 2); // So far the only example of inverse mass dimension usage. Should be useful for other EFT couplings though.

     // doesn't provide these either, although they are just zero of course
     //addParameter(Par::mass1, "gamma", scalar);
     //addParameter(Par::mass1, "g"    , scalar);

     // And we don't provide these either since they cannot be provided at the same scale.
     //addParameter(Par::dimensionless, "alpha" , scalar);
     //addParameter(Par::dimensionless, "alphaS", scalar);

     addParameter(Par::Pole_Mass, "gamma", scalar, "MASS");
     addParameter(Par::Pole_Mass, "g"    , scalar, "MASS");
     addParameter(Par::Pole_Mass, "Z0"   , scalar, "SMINPUTS", 4);
     addParameter(Par::Pole_Mass, "W+"   , scalar, "MASS");

     addParameter(Par::Pole_Mass, "u_3" , scalar, "SMINPUTS", 6); // t
     addParameter(Par::mass1, "d_3" , scalar, "SMINPUTS", 5); // b (technically mb(mb)^{MSbar}, not pole)

     //addParameter(Par::Pole_Mass, "e-", v3, "MASS");
     // These need to point to SMINPUTS. Our system is slightly limited when it comes to
     // pointing vectors of parameters to different places, but in the case of single indices
     // they can be inferred from the particle database, so we can do it as follows in this case:
     addParameter(Par::Pole_Mass, "e-_1", scalar, "SMINPUTS", 11);
     addParameter(Par::Pole_Mass, "e-_2", scalar, "SMINPUTS", 13);
     addParameter(Par::Pole_Mass, "e-_3", scalar, "SMINPUTS", 7);
 
     addParameter(Par::Pole_Mass, "nu_1", scalar, "SMINPUTS", 12);
     addParameter(Par::Pole_Mass, "nu_2", scalar, "SMINPUTS", 14);
     addParameter(Par::Pole_Mass, "nu_3", scalar, "SMINPUTS", 8);

     //addParameter(Par::Pole_Mixing, "sinW2", scalar, "SINTHETAW", 2); // TODO: Need to sort out exact definition of this. If we want it then we need to be able to get it from somewhere.

     // Nearest flavour 'aliases' for the SM mass eigenstates
     // Can point these to the same internal SLHAea location as "u_3", "d_3", etc., no problem with that.
     addParameter(Par::Pole_Mass, "t" , scalar, "SMINPUTS", 6);
     addParameter(Par::mass1, "b" , scalar, "SMINPUTS", 5); // b (technically mb(mb)^{MSbar}, not pole)


     addParameter(Par::Pole_Mass, "e-"  , scalar, "SMINPUTS", 11);
     addParameter(Par::Pole_Mass, "mu-" , scalar, "SMINPUTS", 13);
     addParameter(Par::Pole_Mass, "tau-", scalar, "SMINPUTS", 7);
  }

  //static SLHAstruct SM_slha::generateOutputSLHAea(const Spectrum& spec, const int version)
  //{
  //   SLHAstruct output;
  //   SLHAea_add(output,"SMINPUTS", spec.get(Par::dimensionless,"invalpha_em(MZ)_MSbar"), 1);
  //   SLHAea_add(output,"SMINPUTS", spec.get(Par::dimensionless,"alpha_s(MZ)_MSbar"),     3);
  //   SLHAea_add(output,"SMINPUTS", spec.get(Par::imass2,   "GF"),   2);
  //   SLHAea_add(output,"SMINPUTS", spec.get(Par::Pole_Mass,"Z0"),   4);
  //   SLHAea_add(output,"SMINPUTS", spec.get(Par::Pole_Mass,"b"),    5); // TODO: Store internally as mb(mb)? Since not technically a pole mass?
  //   SLHAea_add(output,"SMINPUTS", spec.get(Par::Pole_Mass,"t"),    6);
  //   SLHAea_add(output,"SMINPUTS", spec.get(Par::Pole_Mass,"tau-"), 7);
  //   if(version>1)
  //   {
  //      // TODO: Could always output this stuff, since SLHA doesn't really care if you have extra stuff
  //      SLHAea_add(output,"SMINPUTS", spec.get(Par::mass1,"d_1"), 21); // TODO: Again, store specifically at 2 GeV? Might be better to separate from "real" running masses.
  //      SLHAea_add(output,"SMINPUTS", spec.get(Par::mass1,"u_1"), 22); // " "
  //            
  //   } 

  //          
  //  21    4.75000000e-03   # Mdown(2 GeV) MSbar
  //  22    2.40000000e-03   # Mup(2 GeV) MSbar
  //  23    1.04000000e-01   # Mstrange(2 GeV) MSbar
  //  24    1.27000000e+00   # Mcharm(Mcharm) MSbar
  //  11    5.10998902e-04   # Me(pole)
  //  13    1.05658357e-01   # Mmu(pole)
  //}

}
