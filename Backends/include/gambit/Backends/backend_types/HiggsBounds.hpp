//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of types
///  for the HiggsBounds backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Rogan
///          (crogan@cern.ch)
///  \date 2015 Apr
///
///  *********************************************

#ifndef __HiggsBounds_types_hpp__
#define __HiggsBounds_types_hpp__

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{
  // Container for HiggsBounds parameter inputs (masses, BR's, CS's etc.)
  // Compatible with v4.x HB
  struct hb_neutral_ModelParameters_part
  {
    // Neutral Higgs Parameters
    double Mh[3];
    double deltaMh[3];
    double hGammaTot[3];
    int CP[3];
    double CS_lep_hjZ_ratio[3];
    double CS_lep_bbhj_ratio[3];
    double CS_lep_tautauhj_ratio[3];
    double CS_lep_hjhi_ratio[3][3];
    double CS_gg_hj_ratio[3];
    double CS_bb_hj_ratio[3];
    double CS_bg_hjb_ratio[3];
    double CS_ud_hjWp_ratio[3];
    double CS_cs_hjWp_ratio[3];
    double CS_ud_hjWm_ratio[3];
    double CS_cs_hjWm_ratio[3];
    double CS_gg_hjZ_ratio[3];
    double CS_dd_hjZ_ratio[3];
    double CS_uu_hjZ_ratio[3];
    double CS_ss_hjZ_ratio[3];
    double CS_cc_hjZ_ratio[3];
    double CS_bb_hjZ_ratio[3];
    double CS_tev_vbf_ratio[3];
    double CS_tev_tthj_ratio[3];
    double CS_lhc7_vbf_ratio[3];
    double CS_lhc7_tthj_ratio[3];
    double CS_lhc8_vbf_ratio[3];
    double CS_lhc8_tthj_ratio[3];
    double BR_hjss[3];
    double BR_hjcc[3];
    double BR_hjbb[3];
    double BR_hjmumu[3];
    double BR_hjtautau[3];
    double BR_hjWW[3];
    double BR_hjZZ[3];
    double BR_hjZga[3];
    double BR_hjgaga[3];
    double BR_hjgg[3];
    double BR_hjinvisible[3];
    double BR_hjhihi[3][3];
  };

  // compatible with v5.x(beta) HB 
  // NB compatible with v4.x HB if coupling ratios are squared
  struct hb_neutral_ModelParameters_effc
  {
   double Mh[3];
   double deltaMh[3];
   double CP[3];
   double hGammaTot[3];
   double ghjss_s[3];
   double ghjss_p[3];
   double ghjcc_s[3];
   double ghjcc_p[3];
   double ghjbb_s[3];
   double ghjbb_p[3];
   double ghjtt_s[3];
   double ghjtt_p[3];
   double ghjmumu_s[3];
   double ghjmumu_p[3];
   double ghjtautau_s[3];
   double ghjtautau_p[3];
   double ghjWW[3];
   double ghjZZ[3];
   double ghjZga[3];
   double ghjgaga[3];
   double ghjgg[3];
   double ghjggZ[3];
   double ghjhiZ[3][3];
   double BR_hjinvisible[3];
   double BR_hjhihi[3][3];
  };

  // compatible with v5.x(beta) HB 
  // compatible with v4.x HB
  struct hb_charged_ModelParameters
  {
    double MHplus[1];
    double deltaMHplus[1];
    double HpGammaTot[1];
    double CS_lep_HpjHmi_ratio[1];
    double BR_tWpb;
    double BR_tHpjb[1];
    double BR_Hpjcs[1];
    double BR_Hpjcb[1];
    double BR_Hptaunu[1];
    // extra HB v5.x (beta) input
    double BR_Hpjtb[1];
    double BR_HpjWZ[1];
    double BR_HpjhiW[3];
  };
}

#endif /* defined __FeynHiggs_types_hpp__ */
