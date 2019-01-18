//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper function to determine which Higgs is
///  most SM-like.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Peter Athron
///          (peter.athron@coepp.org.au)
///  \date 2017
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 
///
///  *********************************************

#include "gambit/Elements/smlike_higgs.hpp"

namespace Gambit
{

  /// Determine which MSSM higgs is most SM-like.
  /// Needs expansion to work with non-MSSM (e.g. *HDM) models

  // S.B. I have added an NMSSM-specific version of this, since
  // "ModelInUse" is not available here, until a better solution
  // comes to mind

  int SMlike_higgs_PDG_code(const SubSpectrum& mssm_spec)
  {
    // MSSM
    double sa =  - mssm_spec.get(Par::Pole_Mixing,"h0",1,1);
    double ca = mssm_spec.get(Par::Pole_Mixing,"h0",1,2);
    double tb = mssm_spec.get(Par::dimensionless, "tanbeta" );
    double sb = sin(atan(tb));
    double cb = cos(atan(tb));
    //cos (beta - alpha) and sin(beta-alpha)
    double cbma = cb * ca + sb * sa;
    double sbma = sb * ca - cb * ca;
    if(sbma > cbma) return 25;
    return 35;
  }

  // NMSSM
  int SMlike_higgs_PDG_code_NMSSM(const SubSpectrum& nmssm_spec)
  {

    // Entries of the Higgs mixing matrix
    double S11 = nmssm_spec.get(Par::Pole_Mixing,"h0",1,1);
    double S12 = nmssm_spec.get(Par::Pole_Mixing,"h0",1,2);
    double S21 = nmssm_spec.get(Par::Pole_Mixing,"h0",2,1);
    double S22 = nmssm_spec.get(Par::Pole_Mixing,"h0",2,2);
    double S31 = nmssm_spec.get(Par::Pole_Mixing,"h0",3,1);
    double S32 = nmssm_spec.get(Par::Pole_Mixing,"h0",3,2);

    double tb = nmssm_spec.get(Par::dimensionless, "tanbeta" );
    double sb = sin(atan(tb));
    double cb = cos(atan(tb));

    // Using: https://arxiv.org/pdf/1509.02452.pdf
    // Coupling to gauge bosons in the NMSSM looks like g(i)h(i)VV
    // g(i) ~ g_SM { cos(beta) S[i,2] + sin(beta) S[i,1] } 
    double g1 = cb*S12 + sb*S11;
    double g2 = cb*S22 + sb*S21;
    double g3 = cb*S32 + sb*S31;

    std::cout << "g1 = " << g1  << " " << abs(1-g1) << std::endl;
    std::cout << "g2 = " << g2  << " " << abs(1-g2) << std::endl;
    std::cout << "g3 = " << g3  << " " << abs(1-g3) << std::endl;

    // The value closest to 1 to be most SM-like
    if (abs(1-g1) < abs(1-g2))
    {
      if (abs(1-g1) < abs(1-g3)) return 25;
    }
    else if (abs(1-g2) < abs(1-g3)) return 35;
    return 45;
    
  }

}
