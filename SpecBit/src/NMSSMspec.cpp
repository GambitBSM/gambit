//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Source file definable quantities for 
///  NMSSMSpec class
///
///  *********************************************
///
///  Authors: 
///  <!-- add name and date if you modify -->
///   
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date Oct 2018
///
///  *********************************************

#include "gambit/SpecBit/NMSSMSpec_head.hpp"

namespace Gambit 
{
   namespace SpecBit 
   {
      NMSSM_strs::NMSSM_strs() {} // Constructor needed to silence certain compiler warnings

      /// Const strings for use in NMSSMspec class 
      
      /// some strings are used in multiple mass
      /// comments indicate first map they appear 
      /// dimension 2, no index
      const str NMSSM_strs::mHd2 = "mHd2";
      const str NMSSM_strs::mHu2 = "mHu2";
      const str NMSSM_strs::ms2 = "ms2";
      /// dimension 2, 2 indices 
      const str NMSSM_strs::mq2 =  "mq2";
      const str NMSSM_strs::ml2 =  "ml2";
      const str NMSSM_strs::md2 =  "md2";
      const str NMSSM_strs::mu2 =  "mu2";
      const str NMSSM_strs::me2 =  "me2";
      /// dimension 1, no index 
      const str NMSSM_strs::M1 =  "M1";
      const str NMSSM_strs::M2 =  "M2";
      const str NMSSM_strs::M3 =  "M3";
      const str NMSSM_strs::vu =  "vu";
      const str NMSSM_strs::vd =  "vd";
      const str NMSSM_strs::vS = "vS";
      const str NMSSM_strs::Tlambda = "Tlambda";
      const str NMSSM_strs::Tkappa = "Tkappa"; 
      /// dimension 1, 2 indices
      const str NMSSM_strs::TYd =  "TYd";
      const str NMSSM_strs::TYe =  "TYe";
      const str NMSSM_strs::TYu =  "TYu";
      const str NMSSM_strs::ad  =  "ad";
      const str NMSSM_strs::ae  =  "ae";
      const str NMSSM_strs::au  =  "au";
      /// dimension 0, no index 
      const str NMSSM_strs::g1  =  "g1";
      const str NMSSM_strs::g2  =  "g2";
      const str NMSSM_strs::g3  =  "g3";
      const str NMSSM_strs::lambda = "lambda";
      const str NMSSM_strs::kappa = "kappa";
      /// dimension 0, no index, special map  
      const str NMSSM_strs::tanbeta = "tanbeta";
      const str NMSSM_strs::sinW2 = "sinW2";
      /// dimension 0, 2 indices
      const str NMSSM_strs::Yd  =  "Yd";
      const str NMSSM_strs::Yu  =  "Yu";
      const str NMSSM_strs::Ye  =  "Ye";

      ///Pole mass
      /// dimension 1, no index , special for setters
      const str NMSSM_strs::gluino = "~g";
      const str NMSSM_strs::A0 = "A0";
      const str NMSSM_strs::Hplus= "H+";
      const str NMSSM_strs::Hminus ="H-";
      const str NMSSM_strs::Goldstone0 ="Goldstone0";
      const str NMSSM_strs::Goldstoneplus ="Goldstone+";
      const str NMSSM_strs::Goldstoneminus ="Goldstone-";
      const str NMSSM_strs::Wplus = "W+";
      const str NMSSM_strs::Wminus = "W-";
      const str NMSSM_strs::Z0 = "Z0";

      
      /// dimension 1, 1 index , special for setters
      const str NMSSM_strs::su        =   "~u";
      const str NMSSM_strs::sd	   =   "~d";
      const str NMSSM_strs::se	   =   "~e-";
      const str NMSSM_strs::snu	   =   "~nu";
      const str NMSSM_strs::chiplus   =   "~chi+";
      const str NMSSM_strs::chi0      =   "~chi0";
      const str NMSSM_strs::h0	   =   "h0";
      const str NMSSM_strs::subar     =   "~ubar";
      const str NMSSM_strs::sdbar     =   "~dbar";
      const str NMSSM_strs::seplus    =   "~e+";
      const str NMSSM_strs::snubar    =   "~nubar";
      const str NMSSM_strs::chiminus  =   "~chi-";

      /// @{ "Metadata" vectors
      // TODO: replace with a more integrated system
 
      /// @{ Pole_Mass tagged entries

      // pole mass strings with no index
      const std::vector<str> NMSSM_strs::pole_mass_strs = initVector( gluino, Hplus,
       					     Hminus, Goldstone0,
       					     Goldstoneplus,
       					     Goldstoneminus,
       					     Wplus, Wminus, Z0 );

      // as above but without Z0 since we do not predict that mass
      const std::vector<str> NMSSM_strs::pole_mass_pred = initVector( gluino, Hplus,
       					     Hminus, Goldstone0,
       					     Goldstoneplus,
       					     Goldstoneminus,
       					     Wplus, Wminus );

      /// pole mass strings with 1 index
      const std::vector<str> NMSSM_strs::pole_mass_strs_1 = initVector( su, sd, se, 
                                                      subar, sdbar, seplus,
       					       chiplus, chiminus, chi0, A0, h0, 
       					       snu, snubar );

      ///  pole mass strings with 1 index and six entries
      const std::vector<str> NMSSM_strs::pole_mass_strs_1_6  = initVector( su, sd, se,
       						  subar, sdbar, seplus );

      ///  pole mass strings with 1 index and five entries
      const std::vector<str> NMSSM_strs::pole_mass_strs_1_5  = initVector( chi0 );
      
      ///  pole mass strings with 1 index and three entries
      const std::vector<str> NMSSM_strs::pole_mass_strs_1_3  = initVector( snu, snubar, h0 );

      ///  pole mass strings with 1 index and two entries
      const std::vector<str> NMSSM_strs::pole_mass_strs_1_2  = initVector( chiplus, chiminus, A0 );

      /// @}

      /// @{ Pole_Mixing tagged entries

      ///  2 index, 6x6 entries
      const std::vector<str> NMSSM_strs::pole_mixing_strs_2_6x6  = initVector( sd, su, se );

      ///  2 index, 5x5 entries
      const std::vector<str> NMSSM_strs::pole_mixing_strs_2_5x5  = initVector( chi0 );

      ///  2 index, 3x3 entries
      const std::vector<str> NMSSM_strs::pole_mixing_strs_2_3x3  = initVector( snu, h0, A0 );

      ///  2 index, 2x2 entries
      const std::vector<str> NMSSM_strs::pole_mixing_strs_2_2x2  = initVector( Hplus, chiminus, chiplus );

      /// @}

      /// @{ mass2 tagged entries

      // no index 
      const std::vector<str> NMSSM_strs::mass2_strs = initVector( mHd2, mHu2, ms2 );

      // two-index, 3x3 entries
      const std::vector<str> NMSSM_strs::mass2_strs_2_3x3= initVector( mq2, ml2, md2, mu2, me2 );

      /// @}

      /// @{ mass1 tagged entries
   
      // no index
      const std::vector<str> NMSSM_strs::mass1_strs = initVector( M1, M2, M3, vu, vd, vS, Tlambda, Tkappa );
      
      // two-index, 3x3 entries
      const std::vector<str> NMSSM_strs::mass1_strs_2_3x3 = initVector( TYd, TYe, TYu, ad, ae, au );

      /// @}
 
      /// @{ dimensionless tagged entries
   
      // no index
      const std::vector<str> NMSSM_strs::dimensionless_strs = initVector( g1, g2, g3, tanbeta, sinW2, lambda, kappa );

      // two-index, 3x3 entries
      const std::vector<str> NMSSM_strs::dimensionless_strs_2_3x3 = initVector( Yd, Yu, Ye );

      /// @}
      
      /// TODO: left out mass_eigenstate entries for now
   }
}

