//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for DecayBit.
///
///  Compile-time registration of available
///  observables and likelihoods for calculating
///  particle decay rates and branching fractions,
///  along with their dependencies.
///
///  Don't put typedefs or other type definitions
///  in this file; see
///  Core/include/types_rollcall.hpp for further
///  instructions on how to add new types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2014 Aug
///
///  \author Csaba Balazs
///  \date 2015 Jan-May
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Aug
///
///   \author Tomas Gonzalo
///           (t.e.gonzalo@fys.uio.no)
///  \date 2018 Feb
///  \author Andrew Fowlie
///  \date 2018 May
///  \author Peter Athron
///  \date 2018 May
///
///  *********************************************


#ifndef __DecayBit_rollcall_hpp__
#define __DecayBit_rollcall_hpp__


#define MODULE DecayBit
START_MODULE

  #define CAPABILITY t_decay_rates
  START_CAPABILITY

    #define FUNCTION t_decays
    START_FUNCTION(DecayTable::Entry)
    #undef FUNCTION

    #define FUNCTION FH_t_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(FH_Couplings_output, fh_Couplings)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY


  #define CAPABILITY Reference_SM_Higgs_decay_rates
  START_CAPABILITY

    #define FUNCTION Ref_SM_Higgs_decays_table
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(mh, triplet<double>)
    #undef FUNCTION

    #define FUNCTION Ref_SM_Higgs_decays_FH
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    DEPENDENCY(FH_Couplings_output, fh_Couplings)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY


  #define CAPABILITY Reference_SM_other_Higgs_decay_rates
  START_CAPABILITY

    #define FUNCTION Ref_SM_other_Higgs_decays_table
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

    #define FUNCTION Ref_SM_other_Higgs_decays_FH
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    DEPENDENCY(FH_Couplings_output, fh_Couplings)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY


  #define CAPABILITY Reference_SM_A0_decay_rates
  START_CAPABILITY

    #define FUNCTION Ref_SM_A0_decays_table
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

    #define FUNCTION Ref_SM_A0_decays_FH
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(FH_Couplings_output, fh_Couplings)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY


  #define CAPABILITY Higgs_decay_rates
  START_CAPABILITY

    #define FUNCTION SM_Higgs_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(Reference_SM_Higgs_decay_rates, DecayTable::Entry)
    #undef FUNCTION

    #define FUNCTION ScalarSingletDM_Higgs_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(Reference_SM_Higgs_decay_rates, DecayTable::Entry)
    MODEL_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z2_spectrum, Spectrum, ScalarSingletDM_Z2, ScalarSingletDM_Z2_running)
    MODEL_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z3_spectrum, Spectrum, ScalarSingletDM_Z3, ScalarSingletDM_Z3_running)
    ALLOW_MODELS(ScalarSingletDM_Z2, ScalarSingletDM_Z2_running, ScalarSingletDM_Z3, ScalarSingletDM_Z3_running)
    #undef FUNCTION

    #define FUNCTION VectorSingletDM_Higgs_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(Reference_SM_Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(VectorSingletDM_Z2_spectrum, Spectrum)
    ALLOW_MODELS(VectorSingletDM_Z2)
    #undef FUNCTION

    #define FUNCTION MajoranaSingletDM_Higgs_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(Reference_SM_Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(MajoranaSingletDM_Z2_spectrum, Spectrum)
    ALLOW_MODELS(MajoranaSingletDM_Z2)
    #undef FUNCTION

    #define FUNCTION DiracSingletDM_Higgs_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(Reference_SM_Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(DiracSingletDM_Z2_spectrum, Spectrum)
    ALLOW_MODELS(DiracSingletDM_Z2)
    #undef FUNCTION

    #define FUNCTION MSSM_h0_1_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_widthhl_hdec, (sh_reqd), widthhl_hdec_type)
    BACKEND_REQ(cb_wisusy_hdec, (sh_reqd), wisusy_hdec_type)
    BACKEND_REQ(cb_wisfer_hdec, (sh_reqd), wisfer_hdec_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

    #define FUNCTION FH_MSSM_h0_1_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(FH_Couplings_output, fh_Couplings)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY h0_2_decay_rates
  START_CAPABILITY

    #define FUNCTION h0_2_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_widthhh_hdec, (sh_reqd), widthhh_hdec_type)
    BACKEND_REQ(cb_wisusy_hdec, (sh_reqd), wisusy_hdec_type)
    BACKEND_REQ(cb_wisfer_hdec, (sh_reqd), wisfer_hdec_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

    #define FUNCTION FH_h0_2_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    DEPENDENCY(FH_Couplings_output, fh_Couplings)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY A0_decay_rates
  START_CAPABILITY

    #define FUNCTION A0_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_widtha_hdec, (sh_reqd), widtha_hdec_type)
    BACKEND_REQ(cb_wisusy_hdec, (sh_reqd), wisusy_hdec_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

    #define FUNCTION FH_A0_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(FH_Couplings_output, fh_Couplings)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY H_plus_decay_rates
  START_CAPABILITY

    #define FUNCTION H_plus_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_widthhc_hdec, (sh_reqd), widthhc_hdec_type)
    BACKEND_REQ(cb_wisusy_hdec, (sh_reqd), wisusy_hdec_type)
    BACKEND_REQ(cb_wisfer_hdec, (sh_reqd), wisfer_hdec_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

    #define FUNCTION FH_H_plus_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    DEPENDENCY(FH_Couplings_output, fh_Couplings)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY gluino_decay_rates
  START_CAPABILITY

    #define FUNCTION gluino_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_gluiwidth, (sh_reqd), sd_gluiwidth_type)
    BACKEND_REQ(cb_sd_glui2body, (sh_reqd), sd_glui2body_type)
    BACKEND_REQ(cb_sd_gluiloop, (sh_reqd), sd_gluiloop_type)
    BACKEND_REQ(cb_sd_glui3body, (sh_reqd), sd_glui3body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY stop_1_decay_rates
  START_CAPABILITY

    #define FUNCTION stop_1_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_stopwidth, (sh_reqd), sd_stopwidth_type)
    BACKEND_REQ(cb_sd_stop2body, (sh_reqd), sd_stop2body_type)
    BACKEND_REQ(cb_sd_stoploop, (sh_reqd), sd_stoploop_type)
    BACKEND_REQ(cb_sd_stop3body, (sh_reqd), sd_stop3body_type)
    BACKEND_REQ(cb_sd_stop4body, (sh_reqd), sd_stop4body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY stop_2_decay_rates
  START_CAPABILITY

    #define FUNCTION stop_2_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_stopwidth, (sh_reqd), sd_stopwidth_type)
    BACKEND_REQ(cb_sd_stop2body, (sh_reqd), sd_stop2body_type)
    BACKEND_REQ(cb_sd_stop3body, (sh_reqd), sd_stop3body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY sbottom_1_decay_rates
  START_CAPABILITY

    #define FUNCTION sbottom_1_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_sbotwidth, (sh_reqd), sd_sbotwidth_type)
    BACKEND_REQ(cb_sd_sbot2body, (sh_reqd), sd_sbot2body_type)
    BACKEND_REQ(cb_sd_sbot3body, (sh_reqd), sd_sbot3body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY sbottom_2_decay_rates
  START_CAPABILITY

    #define FUNCTION sbottom_2_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_sbotwidth, (sh_reqd), sd_sbotwidth_type)
    BACKEND_REQ(cb_sd_sbot2body, (sh_reqd), sd_sbot2body_type)
    BACKEND_REQ(cb_sd_sbot3body, (sh_reqd), sd_sbot3body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY sup_l_decay_rates
  START_CAPABILITY

    #define FUNCTION sup_l_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_supwidth, (sh_reqd), sd_supwidth_type)
    BACKEND_REQ(cb_sd_sup2body, (sh_reqd), sd_sup2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY sup_r_decay_rates
  START_CAPABILITY

    #define FUNCTION sup_r_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_supwidth, (sh_reqd), sd_supwidth_type)
    BACKEND_REQ(cb_sd_sup2body, (sh_reqd), sd_sup2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY sdown_l_decay_rates
  START_CAPABILITY

    #define FUNCTION sdown_l_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_sdownwidth, (sh_reqd), sd_sdownwidth_type)
    BACKEND_REQ(cb_sd_sdown2body, (sh_reqd), sd_sdown2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY sdown_r_decay_rates
  START_CAPABILITY

    #define FUNCTION sdown_r_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_sdownwidth, (sh_reqd), sd_sdownwidth_type)
    BACKEND_REQ(cb_sd_sdown2body, (sh_reqd), sd_sdown2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY scharm_l_decay_rates
  START_CAPABILITY

    #define FUNCTION scharm_l_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_supwidth, (sh_reqd), sd_supwidth_type)
    BACKEND_REQ(cb_sd_sup2body, (sh_reqd), sd_sup2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY scharm_r_decay_rates
  START_CAPABILITY

    #define FUNCTION scharm_r_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_supwidth, (sh_reqd), sd_supwidth_type)
    BACKEND_REQ(cb_sd_sup2body, (sh_reqd), sd_sup2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY sstrange_l_decay_rates
  START_CAPABILITY

    #define FUNCTION sstrange_l_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_sdownwidth, (sh_reqd), sd_sdownwidth_type)
    BACKEND_REQ(cb_sd_sdown2body, (sh_reqd), sd_sdown2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY sstrange_r_decay_rates
  START_CAPABILITY

    #define FUNCTION sstrange_r_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_sdownwidth, (sh_reqd), sd_sdownwidth_type)
    BACKEND_REQ(cb_sd_sdown2body, (sh_reqd), sd_sdown2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY selectron_l_decay_rates
  START_CAPABILITY

    #define FUNCTION selectron_l_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_selwidth, (sh_reqd), sd_selwidth_type)
    BACKEND_REQ(cb_sd_sel2body, (sh_reqd), sd_sel2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY selectron_r_decay_rates
  START_CAPABILITY

    #define FUNCTION selectron_r_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_selwidth, (sh_reqd), sd_selwidth_type)
    BACKEND_REQ(cb_sd_sel2body, (sh_reqd), sd_sel2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY smuon_l_decay_rates
  START_CAPABILITY

    #define FUNCTION smuon_l_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_selwidth, (sh_reqd), sd_selwidth_type)
    BACKEND_REQ(cb_sd_sel2body, (sh_reqd), sd_sel2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY smuon_r_decay_rates
  START_CAPABILITY

    #define FUNCTION smuon_r_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_selwidth, (sh_reqd), sd_selwidth_type)
    BACKEND_REQ(cb_sd_sel2body, (sh_reqd), sd_sel2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY stau_1_decay_rates
  START_CAPABILITY

    #define FUNCTION stau_1_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(stau_1_decay_rates_SH, DecayTable::Entry)
    DEPENDENCY(stau_1_decay_rates_smallsplit, DecayTable::Entry)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY stau_1_decay_rates_SH
  START_CAPABILITY

    #define FUNCTION stau_1_decays_SH
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_stauwidth, (sh_reqd), sd_stauwidth_type)
    BACKEND_REQ(cb_sd_stau2body, (sh_reqd), sd_stau2body_type)
    BACKEND_REQ(cb_sd_stau2bodygrav, (sh_reqd), sd_stau2bodygrav_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY stau_1_decay_rates_smallsplit
  START_CAPABILITY

    #define FUNCTION stau_1_decays_smallsplit
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    DEPENDENCY(tau_minus_decay_rates, DecayTable::Entry)
    ALLOW_MODEL_DEPENDENCE(MSSM63atQ, MSSM63atMGUT, StandardModel_SLHA2)
    MODEL_GROUP(group1, (StandardModel_SLHA2))
    MODEL_GROUP(group2, (MSSM63atQ, MSSM63atMGUT))
    ALLOW_MODEL_COMBINATION(group1,group2)
    #undef FUNCTION

  #undef CAPABILITY



  #define CAPABILITY stau_2_decay_rates
  START_CAPABILITY

    #define FUNCTION stau_2_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_stauwidth, (sh_reqd), sd_stauwidth_type)
    BACKEND_REQ(cb_sd_stau2body, (sh_reqd), sd_stau2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY snu_electronl_decay_rates
  START_CAPABILITY

    #define FUNCTION snu_electronl_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_snelwidth, (sh_reqd), sd_snelwidth_type)
    BACKEND_REQ(cb_sd_snel2body, (sh_reqd), sd_snel2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY snu_muonl_decay_rates
  START_CAPABILITY

    #define FUNCTION snu_muonl_decays
    START_FUNCTION(DecayTable::Entry)
    BACKEND_REQ(cb_sd_snelwidth, (sh_reqd), sd_snelwidth_type)
    BACKEND_REQ(cb_sd_snel2body, (sh_reqd), sd_snel2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY snu_taul_decay_rates
  START_CAPABILITY

    #define FUNCTION snu_taul_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_sntauwidth, (sh_reqd), sd_sntauwidth_type)
    BACKEND_REQ(cb_sd_sntau2body, (sh_reqd), sd_sntau2body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY chargino_plus_1_decay_rates
  START_CAPABILITY

    #define FUNCTION chargino_plus_1_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(chargino_plus_1_decay_rates_SH, DecayTable::Entry)
    DEPENDENCY(chargino_plus_1_decay_rates_smallsplit, DecayTable::Entry)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY chargino_plus_1_decay_rates_SH
  START_CAPABILITY

    #define FUNCTION chargino_plus_1_decays_SH
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_charwidth, (sh_reqd), sd_charwidth_type)
    BACKEND_REQ(cb_sd_char2body, (sh_reqd), sd_char2body_type)
    BACKEND_REQ(cb_sd_char2bodygrav, (sh_reqd), sd_char2bodygrav_type)
    BACKEND_REQ(cb_sd_char3body, (sh_reqd), sd_char3body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY chargino_plus_1_decay_rates_smallsplit
  START_CAPABILITY

    #define FUNCTION chargino_plus_1_decays_smallsplit
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    DEPENDENCY(rho_0_decay_rates, DecayTable::Entry)
    DEPENDENCY(rho1450_decay_rates, DecayTable::Entry)
    ALLOW_MODEL_DEPENDENCE(MSSM63atQ, MSSM63atMGUT, StandardModel_SLHA2)
    MODEL_GROUP(group1, (StandardModel_SLHA2))
    MODEL_GROUP(group2, (MSSM63atQ, MSSM63atMGUT))
    ALLOW_MODEL_COMBINATION(group1,group2)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY chargino_plus_2_decay_rates
  START_CAPABILITY

    #define FUNCTION chargino_plus_2_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_charwidth, (sh_reqd), sd_charwidth_type)
    BACKEND_REQ(cb_sd_char2body, (sh_reqd), sd_char2body_type)
    BACKEND_REQ(cb_sd_char2bodygrav, (sh_reqd), sd_char2bodygrav_type)
    BACKEND_REQ(cb_sd_char3body, (sh_reqd), sd_char3body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY neutralino_1_decay_rates
  START_CAPABILITY

    #define FUNCTION neutralino_1_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_neutwidth, (sh_reqd), sd_neutwidth_type)
    BACKEND_REQ(cb_sd_neut2body, (sh_reqd), sd_neut2body_type)
    BACKEND_REQ(cb_sd_neut2bodygrav, (sh_reqd), sd_neut2bodygrav_type)
    BACKEND_REQ(cb_sd_neut3body, (sh_reqd), sd_neut3body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY neutralino_2_decay_rates
  START_CAPABILITY

    #define FUNCTION neutralino_2_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_neutwidth, (sh_reqd), sd_neutwidth_type)
    BACKEND_REQ(cb_sd_neut2body, (sh_reqd), sd_neut2body_type)
    BACKEND_REQ(cb_sd_neut2bodygrav, (sh_reqd), sd_neut2bodygrav_type)
    BACKEND_REQ(cb_sd_neutloop, (sh_reqd), sd_neutloop_type)
    BACKEND_REQ(cb_sd_neut3body, (sh_reqd), sd_neut3body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY neutralino_3_decay_rates
  START_CAPABILITY

    #define FUNCTION neutralino_3_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_neutwidth, (sh_reqd), sd_neutwidth_type)
    BACKEND_REQ(cb_sd_neut2body, (sh_reqd), sd_neut2body_type)
    BACKEND_REQ(cb_sd_neut2bodygrav, (sh_reqd), sd_neut2bodygrav_type)
    BACKEND_REQ(cb_sd_neutloop, (sh_reqd), sd_neutloop_type)
    BACKEND_REQ(cb_sd_neut3body, (sh_reqd), sd_neut3body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY neutralino_4_decay_rates
  START_CAPABILITY

    #define FUNCTION neutralino_4_decays
    START_FUNCTION(DecayTable::Entry)
    DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms)
    BACKEND_REQ(cb_sd_neutwidth, (sh_reqd), sd_neutwidth_type)
    BACKEND_REQ(cb_sd_neut2body, (sh_reqd), sd_neut2body_type)
    BACKEND_REQ(cb_sd_neut2bodygrav, (sh_reqd), sd_neut2bodygrav_type)
    BACKEND_REQ(cb_sd_neutloop, (sh_reqd), sd_neutloop_type)
    BACKEND_REQ(cb_sd_neut3body, (sh_reqd), sd_neut3body_type)
    BACKEND_OPTION( (SUSY_HIT), (sh_reqd) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION


  #undef CAPABILITY

  #define CAPABILITY decay_rates
  START_CAPABILITY

    #define FUNCTION all_decays_from_SLHA
    START_FUNCTION(DecayTable)
    #undef FUNCTION

    #define FUNCTION all_decays
    START_FUNCTION(DecayTable)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    DEPENDENCY(W_minus_decay_rates, DecayTable::Entry)
    DEPENDENCY(W_plus_decay_rates, DecayTable::Entry)
    DEPENDENCY(Z_decay_rates, DecayTable::Entry)
    DEPENDENCY(t_decay_rates, DecayTable::Entry)
    DEPENDENCY(tbar_decay_rates, DecayTable::Entry)
    DEPENDENCY(mu_minus_decay_rates, DecayTable::Entry)
    DEPENDENCY(mu_plus_decay_rates, DecayTable::Entry)
    DEPENDENCY(tau_minus_decay_rates, DecayTable::Entry)
    DEPENDENCY(tau_plus_decay_rates, DecayTable::Entry)
    DEPENDENCY(pi_0_decay_rates, DecayTable::Entry)
    DEPENDENCY(pi_minus_decay_rates, DecayTable::Entry)
    DEPENDENCY(pi_plus_decay_rates, DecayTable::Entry)
    DEPENDENCY(eta_decay_rates, DecayTable::Entry)
    DEPENDENCY(rho_0_decay_rates, DecayTable::Entry)
    DEPENDENCY(rho_minus_decay_rates, DecayTable::Entry)
    DEPENDENCY(rho_plus_decay_rates, DecayTable::Entry)
    DEPENDENCY(omega_decay_rates, DecayTable::Entry)
    DEPENDENCY(rho1450_decay_rates, DecayTable::Entry)
    MODEL_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(h0_2_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(A0_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(H_plus_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(H_minus_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(gluino_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(stop_1_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(stop_2_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sbottom_1_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sbottom_2_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sup_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sup_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sdown_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sdown_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(scharm_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(scharm_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sstrange_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sstrange_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(selectron_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(selectron_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(smuon_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(smuon_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(stau_1_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(stau_2_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(snu_electronl_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(snu_muonl_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(snu_taul_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(stopbar_1_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(stopbar_2_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sbottombar_1_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sbottombar_2_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(supbar_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(supbar_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sdownbar_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sdownbar_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(scharmbar_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(scharmbar_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sstrangebar_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(sstrangebar_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(selectronbar_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(selectronbar_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(smuonbar_l_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(smuonbar_r_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(staubar_1_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(staubar_2_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(snubar_electronl_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(snubar_muonl_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(snubar_taul_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(chargino_plus_1_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(chargino_minus_1_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(chargino_plus_2_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(chargino_minus_2_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(neutralino_1_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(neutralino_2_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(neutralino_3_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(neutralino_4_decay_rates, DecayTable::Entry, MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

  #define CAPABILITY all_BFs
  START_CAPABILITY
    #define FUNCTION get_decaytable_as_map
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(decay_rates, DecayTable)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY SLHA1_violation
  START_CAPABILITY
    #define FUNCTION check_first_sec_gen_mixing
    START_FUNCTION(int)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY SLHA_pseudonyms
  START_CAPABILITY
    #define FUNCTION get_mass_es_pseudonyms
    START_FUNCTION(mass_es_pseudonyms)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Z_gamma_nu
  START_CAPABILITY
    #define FUNCTION Z_gamma_nu_2l
    START_FUNCTION(triplet<double>)
    DEPENDENCY(SM_spectrum, Spectrum)
    MODEL_CONDITIONAL_DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd, RightHandedNeutrinos)
    MODEL_CONDITIONAL_DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd, RightHandedNeutrinos)
    ALLOW_MODELS(StandardModel_SLHA2,RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY Z_gamma_chi_0
  START_CAPABILITY
    #define FUNCTION Z_gamma_chi_0_MSSM_tree
    START_FUNCTION(triplet<double>)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_Z_inv
  START_CAPABILITY
    #define FUNCTION lnL_Z_inv
    START_FUNCTION(double)
    DEPENDENCY(Z_gamma_nu, triplet<double>)
    MODEL_CONDITIONAL_DEPENDENCY(Z_gamma_chi_0, triplet<double>, MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY W_to_l_decays
  START_CAPABILITY
    #define FUNCTION RHN_W_to_l_decays
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(mw, triplet<double>)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_W_decays
  START_CAPABILITY
    #define FUNCTION lnL_W_decays_chi2
    START_FUNCTION(double)
    DEPENDENCY(W_to_l_decays, std::vector<double>)
    DEPENDENCY(W_plus_decay_rates, DecayTable::Entry)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY lnL_Higgs_invWidth
  START_CAPABILITY
    #define FUNCTION lnL_Higgs_invWidth_SMlike
    START_FUNCTION(double)
    DEPENDENCY(inv_Higgs_BF, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY inv_Higgs_BF
  START_CAPABILITY

    #define FUNCTION ScalarSingletDM_inv_Higgs_BF
    START_FUNCTION(double)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    ALLOW_MODELS(ScalarSingletDM_Z2, ScalarSingletDM_Z2_running, ScalarSingletDM_Z3, ScalarSingletDM_Z3_running)
    #undef FUNCTION

    #define FUNCTION VectorSingletDM_inv_Higgs_BF
    START_FUNCTION(double)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    ALLOW_MODELS(VectorSingletDM_Z2)
    #undef FUNCTION

    #define FUNCTION MajoranaSingletDM_inv_Higgs_BF
    START_FUNCTION(double)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    ALLOW_MODELS(MajoranaSingletDM_Z2)
    #undef FUNCTION

    #define FUNCTION DiracSingletDM_inv_Higgs_BF
    START_FUNCTION(double)
    DEPENDENCY(Higgs_decay_rates, DecayTable::Entry)
    ALLOW_MODELS(DiracSingletDM_Z2)
    #undef FUNCTION

    #define FUNCTION MSSM_inv_Higgs_BF
    START_FUNCTION(double)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

  #undef CAPABILITY

#undef MODULE

// SM decay rate functions
QUICK_FUNCTION(DecayBit, W_plus_decay_rates,    NEW_CAPABILITY, W_plus_decays,    DecayTable::Entry)
QUICK_FUNCTION(DecayBit, W_minus_decay_rates ,  NEW_CAPABILITY, W_minus_decays,   DecayTable::Entry, (), (W_plus_decay_rates,   DecayTable::Entry))
QUICK_FUNCTION(DecayBit, Z_decay_rates,         OLD_CAPABILITY, Z_decays,         DecayTable::Entry)
QUICK_FUNCTION(DecayBit, tbar_decay_rates,      NEW_CAPABILITY, tbar_decays,      DecayTable::Entry, (), (t_decay_rates,        DecayTable::Entry))
QUICK_FUNCTION(DecayBit, mu_plus_decay_rates,   NEW_CAPABILITY, mu_plus_decays,   DecayTable::Entry)
QUICK_FUNCTION(DecayBit, mu_minus_decay_rates,  NEW_CAPABILITY, mu_minus_decays,  DecayTable::Entry, (), (mu_plus_decay_rates,  DecayTable::Entry))
QUICK_FUNCTION(DecayBit, tau_plus_decay_rates,  NEW_CAPABILITY, tau_plus_decays,  DecayTable::Entry)
QUICK_FUNCTION(DecayBit, tau_minus_decay_rates, NEW_CAPABILITY, tau_minus_decays, DecayTable::Entry, (), (tau_plus_decay_rates, DecayTable::Entry))
QUICK_FUNCTION(DecayBit, pi_0_decay_rates,      NEW_CAPABILITY, pi_0_decays,      DecayTable::Entry)
QUICK_FUNCTION(DecayBit, pi_plus_decay_rates,   NEW_CAPABILITY, pi_plus_decays,   DecayTable::Entry)
QUICK_FUNCTION(DecayBit, pi_minus_decay_rates,  NEW_CAPABILITY, pi_minus_decays,  DecayTable::Entry, (), (pi_plus_decay_rates,  DecayTable::Entry))
QUICK_FUNCTION(DecayBit, eta_decay_rates,       NEW_CAPABILITY, eta_decays,       DecayTable::Entry)
QUICK_FUNCTION(DecayBit, rho_0_decay_rates,     NEW_CAPABILITY, rho_0_decays,     DecayTable::Entry)
QUICK_FUNCTION(DecayBit, rho_plus_decay_rates,  NEW_CAPABILITY, rho_plus_decays,  DecayTable::Entry)
QUICK_FUNCTION(DecayBit, rho_minus_decay_rates, NEW_CAPABILITY, rho_minus_decays, DecayTable::Entry, (), (rho_plus_decay_rates, DecayTable::Entry))
QUICK_FUNCTION(DecayBit, omega_decay_rates,     NEW_CAPABILITY, omega_decays,     DecayTable::Entry)
QUICK_FUNCTION(DecayBit, rho1450_decay_rates,   NEW_CAPABILITY, rho1450_decays,   DecayTable::Entry)

// CP-conserving MSSM antiparticle decay rate functions
QUICK_FUNCTION(DecayBit, H_minus_decay_rates,          NEW_CAPABILITY, H_minus_decays,          DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (H_plus_decay_rates,          DecayTable::Entry))
QUICK_FUNCTION(DecayBit, stopbar_1_decay_rates,        NEW_CAPABILITY, stopbar_1_decays,        DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (stop_1_decay_rates,         DecayTable::Entry))
QUICK_FUNCTION(DecayBit, stopbar_2_decay_rates,        NEW_CAPABILITY, stopbar_2_decays,        DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (stop_2_decay_rates,         DecayTable::Entry))
QUICK_FUNCTION(DecayBit, sbottombar_1_decay_rates,     NEW_CAPABILITY, sbottombar_1_decays,     DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (sbottom_1_decay_rates,      DecayTable::Entry))
QUICK_FUNCTION(DecayBit, sbottombar_2_decay_rates,     NEW_CAPABILITY, sbottombar_2_decays,     DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (sbottom_2_decay_rates,      DecayTable::Entry))
QUICK_FUNCTION(DecayBit, supbar_l_decay_rates,         NEW_CAPABILITY, supbar_l_decays,         DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (sup_l_decay_rates,          DecayTable::Entry))
QUICK_FUNCTION(DecayBit, supbar_r_decay_rates,         NEW_CAPABILITY, supbar_r_decays,         DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (sup_r_decay_rates,          DecayTable::Entry))
QUICK_FUNCTION(DecayBit, sdownbar_l_decay_rates,       NEW_CAPABILITY, sdownbar_l_decays,       DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (sdown_l_decay_rates,        DecayTable::Entry))
QUICK_FUNCTION(DecayBit, sdownbar_r_decay_rates,       NEW_CAPABILITY, sdownbar_r_decays,       DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (sdown_r_decay_rates,        DecayTable::Entry))
QUICK_FUNCTION(DecayBit, scharmbar_l_decay_rates,      NEW_CAPABILITY, scharmbar_l_decays,      DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (scharm_l_decay_rates,       DecayTable::Entry))
QUICK_FUNCTION(DecayBit, scharmbar_r_decay_rates,      NEW_CAPABILITY, scharmbar_r_decays,      DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (scharm_r_decay_rates,       DecayTable::Entry))
QUICK_FUNCTION(DecayBit, sstrangebar_l_decay_rates,    NEW_CAPABILITY, sstrangebar_l_decays,    DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (sstrange_l_decay_rates,     DecayTable::Entry))
QUICK_FUNCTION(DecayBit, sstrangebar_r_decay_rates,    NEW_CAPABILITY, sstrangebar_r_decays,    DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (sstrange_r_decay_rates,     DecayTable::Entry))
QUICK_FUNCTION(DecayBit, selectronbar_l_decay_rates,   NEW_CAPABILITY, selectronbar_l_decays,   DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (selectron_l_decay_rates,    DecayTable::Entry))
QUICK_FUNCTION(DecayBit, selectronbar_r_decay_rates,   NEW_CAPABILITY, selectronbar_r_decays,   DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (selectron_r_decay_rates,    DecayTable::Entry))
QUICK_FUNCTION(DecayBit, smuonbar_l_decay_rates,       NEW_CAPABILITY, smuonbar_l_decays,       DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (smuon_l_decay_rates,        DecayTable::Entry))
QUICK_FUNCTION(DecayBit, smuonbar_r_decay_rates,       NEW_CAPABILITY, smuonbar_r_decays,       DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (smuon_r_decay_rates,        DecayTable::Entry))
QUICK_FUNCTION(DecayBit, staubar_1_decay_rates,        NEW_CAPABILITY, staubar_1_decays,        DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (stau_1_decay_rates,         DecayTable::Entry))
QUICK_FUNCTION(DecayBit, staubar_2_decay_rates,        NEW_CAPABILITY, staubar_2_decays,        DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (stau_2_decay_rates,         DecayTable::Entry))
QUICK_FUNCTION(DecayBit, snubar_electronl_decay_rates, NEW_CAPABILITY, snubar_electronl_decays, DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (snu_electronl_decay_rates,  DecayTable::Entry))
QUICK_FUNCTION(DecayBit, snubar_muonl_decay_rates,     NEW_CAPABILITY, snubar_muonl_decays,     DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (snu_muonl_decay_rates,      DecayTable::Entry))
QUICK_FUNCTION(DecayBit, snubar_taul_decay_rates,      NEW_CAPABILITY, snubar_taul_decays,      DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (snu_taul_decay_rates,       DecayTable::Entry))
QUICK_FUNCTION(DecayBit, chargino_minus_1_decay_rates, NEW_CAPABILITY, chargino_minus_1_decays, DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (chargino_plus_1_decay_rates,DecayTable::Entry))
QUICK_FUNCTION(DecayBit, chargino_minus_2_decay_rates, NEW_CAPABILITY, chargino_minus_2_decays, DecayTable::Entry, (MSSM63atQ, MSSM63atMGUT), (chargino_plus_2_decay_rates,DecayTable::Entry))

#endif /* defined(__DecayBit_rollcall_hpp__) */

