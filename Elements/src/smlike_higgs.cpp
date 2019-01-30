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
    // SUSY basis:  Re(H_u, H_d, S)
    // Mass basis:  (h_01, h_02, h_03)
    // Higgs basis: (h_SM, H, H')

    // Rotation matrix to Higgs mass basis. This is just the pole mixings 
    // from the spectrum object.
    double S11 = nmssm_spec.get(Par::Pole_Mixing,"h0",1,1);
    double S12 = nmssm_spec.get(Par::Pole_Mixing,"h0",1,2);
    double S21 = nmssm_spec.get(Par::Pole_Mixing,"h0",2,1);
    double S22 = nmssm_spec.get(Par::Pole_Mixing,"h0",2,2);
    double S31 = nmssm_spec.get(Par::Pole_Mixing,"h0",3,1);
    double S32 = nmssm_spec.get(Par::Pole_Mixing,"h0",3,2);

    // The mixing from the Higgs Basis to the SUSY basis is just a rotation by angle beta
    double tb = nmssm_spec.get(Par::dimensionless, "tanbeta");
    double sb = sin(atan(tb));
    double cb = cos(atan(tb));

    // beta_matrix << cb, -sb,  0,
    //                sb,  cb,  0,
    //                 0,   0,  1.

    // Now the rotation from the Higgs basis to the mass basis is the matrix
    // product of Higgs -> SUSY, SUSY -> Mass

    double H11 = S11*cb + S12*sb;
    double H12 = S21*cb + S22*sb;
    double H13 = S31*cb + S32*sb;

    std::cout << "H11 = " << H11 << std::endl;
    std::cout << "H12 = " << H12 << std::endl;
    std::cout << "H13 = " << H13 << std::endl;

    // The [absolute] value closest to 1 to be given 'most SM-like' status
    if (1-abs(H11) < 1-abs(H12))
    {
      if (1-abs(H11) < 1-abs(H13)) return 25;
    }
    else if (1-abs(H12) < 1-abs(H13)) return 35;
    return 45;
    
  }

}
