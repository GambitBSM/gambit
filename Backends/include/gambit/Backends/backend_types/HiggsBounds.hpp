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
  struct hb_ModelParameters
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

    // Charged Higgs Parameters
    double MHplus[1];
    double deltaMHplus[1];
    double HpGammaTot[1];
    double CS_lep_HpjHmi_ratio[1];
    double BR_tWpb;
    double BR_tHpjb[1];
    double BR_Hpjcs[1];
    double BR_Hpjcb[1];
    double BR_Hptaunu[1];
  };

  struct hb_ModelParameters_effC
  {
   double Mh[3];
   double hGammaTot[3];
   double g2hjss_s[3];
   double g2hjss_p[3];
   double g2hjcc_s[3];
   double g2hjcc_p[3];
   double g2hjbb_s[3];
   double g2hjbb_p[3];
   double g2hjtt_s[3];
   double g2hjtt_p[3];
   double g2hjmumu_s[3];
   double g2hjmumu_p[3];
   double g2hjtautau_s[3];
   double g2hjtautau_p[3];
   double g2hjWW[3];
   double g2hjZZ[3];
   double g2hjZga[3];
   double g2hjgaga[3];
   double g2hjgg[3];
   double g2hjggZ[3];
   double g2hjhiZ[3];
   double BR_hjinvisible[3];
   double BR_hjhihi[3][3];
  };


}

#endif /* defined __FeynHiggs_types_hpp__ */
