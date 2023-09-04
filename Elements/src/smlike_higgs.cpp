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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020
///
///  *********************************************

#include "gambit/Elements/smlike_higgs.hpp"

namespace Gambit
{

  /// Determine which higgs is most SM-like.
  /// Works only for 2 and 3 higgses (e.g. MSSM and NMSSM)
  int SMlike_higgs_PDG_code(const SubSpectrum& spec)
  {

    // Find out how many Higgses we have.
    int numhiggses = 2;
    if (spec.has(Par::Pole_Mass,"h0", 3)) { numhiggses = 3; }

    // Check which spelling of tanbeta is in the spectrum
    double tb;
    if (spec.has(Par::dimensionless, "tanbeta"))
      tb = spec.get(Par::dimensionless, "tanbeta");
    else if (spec.has(Par::dimensionless, "TanBeta"))
      tb = spec.get(Par::dimensionless, "TanBeta");
    else
      utils_error().raise(LOCAL_INFO, "TanBeta not present in spectrum.");

    // MSSM(2HDM)-like
    if (numhiggses == 2)
    {
      const double sa =  - spec.get(Par::Pole_Mixing,"h0",1,1);
      const double ca = spec.get(Par::Pole_Mixing,"h0",1,2);
      const double sb = sin(atan(tb));
      const double cb = cos(atan(tb));
      //cos (beta - alpha) and sin(beta-alpha)
      const double cbma = cb * ca + sb * sa;
      const double sbma = sb * ca - cb * ca;
      if(sbma > cbma) return 25;
      return 35;
    }

    // NMSSM-like
    else if (numhiggses == 3)
    {
      // SUSY basis:  Re(H_u, H_d, S)
      // Mass basis:  (h_01, h_02, h_03)
      // Higgs basis: (h_SM, H, H')

      // Rotation matrix to Higgs mass basis. This is just the pole mixings 
      // from the spectrum object.
      const double S11 = spec.get(Par::Pole_Mixing,"h0",1,1);
      const double S12 = spec.get(Par::Pole_Mixing,"h0",1,2);
      const double S21 = spec.get(Par::Pole_Mixing,"h0",2,1);
      const double S22 = spec.get(Par::Pole_Mixing,"h0",2,2);
      const double S31 = spec.get(Par::Pole_Mixing,"h0",3,1);
      const double S32 = spec.get(Par::Pole_Mixing,"h0",3,2);

      // The mixing from the Higgs Basis to the SUSY basis is just a rotation by angle beta
      const double sb = sin(atan(tb));
      const double cb = cos(atan(tb));

      // beta_matrix << cb, -sb,  0,
      //                sb,  cb,  0,
      //                 0,   0,  1.

      // Now the rotation from the Higgs basis to the mass basis is the matrix
      // product of Higgs -> SUSY, SUSY -> Mass

      const double H11 = S11*cb + S12*sb;
      const double H12 = S21*cb + S22*sb;
      const double H13 = S31*cb + S32*sb;

      // The [absolute] value closest to 1 to be given 'most SM-like' status
      if (1-abs(H11) < 1-abs(H12))
      {
        if (1-abs(H11) < 1-abs(H13)) return 25;
      }
      else if (1-abs(H12) < 1-abs(H13)) return 35;
      return 45;

    }

    // If no routines exist for the number of Higgses in the spectrum, throw an error.
    else utils_error().raise(LOCAL_INFO, "No routines exist for finding the most SM-like Higgs for a Higgs sector with " + std::to_string(numhiggses) + " Higgses.");
    return -1;

  }

}
