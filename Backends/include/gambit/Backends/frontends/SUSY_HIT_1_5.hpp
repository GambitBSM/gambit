//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for SUSY-HIT 1.5 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Peter Athron
/// \author Csaba Balazs
/// \author Pat Scott
/// \date 2015 Jan-May
///
///  *********************************************

#define BACKENDNAME SUSY_HIT
#define BACKENDLANG FORTRAN
#define VERSION 1.5
#define SAFE_VERSION 1_5
#define REFERENCE Djouadi:2006bz,Muhlleitner:2003vg,Djouadi:2002ze,Djouadi:1997yw

// Let's go.
LOAD_LIBRARY

// SUSY-HIT only works with diagonal MSSM models where first and second generation sfermions are degenerate.
BE_ALLOW_MODELS(NUHM2, MSSM20atQ, MSSM20atQ_mG)

// Functions
BE_FUNCTION(sdecay, void, (), "sdecay_", "sdecay")               // Converted SUSY-HIT main routine
BE_FUNCTION(unlikely, double, (), "s_hit_unlikely_", "unlikely") // Wrapper for 'unlikely' double

// Variables
BE_VARIABLE(checkfavvio, checkfavvio_type, "checkfavvio_", "cb_checkfavvio")
BE_VARIABLE(susyhitin, susyhitin_type, "susyhitin_", "cb_susyhitin")
BE_VARIABLE(sd_leshouches1, sd_leshouches1_type, "sd_leshouches1_", "cb_sd_leshouches1")
BE_VARIABLE(sd_leshouches2, sd_leshouches2_type, "sd_leshouches2_", "cb_sd_leshouches2")
BE_VARIABLE(slha_leshouches1_hdec, sd_leshouches1_type, "slha_leshouches1_hdec_", "cb_slha_leshouches1_hdec")
BE_VARIABLE(slha_leshouches2_hdec, slha_leshouches2_hdec_type, "slha_leshouches2_hdec_", "cb_slha_leshouches2_hdec")
BE_VARIABLE(widtha_hdec, widtha_hdec_type, "widtha_hdec_", "cb_widtha_hdec")
BE_VARIABLE(widthhl_hdec, widthhl_hdec_type, "widthhl_hdec_", "cb_widthhl_hdec")
BE_VARIABLE(widthhh_hdec, widthhh_hdec_type, "widthhh_hdec_", "cb_widthhh_hdec")
BE_VARIABLE(widthhc_hdec, widthhc_hdec_type, "widthhc_hdec_", "cb_widthhc_hdec")
BE_VARIABLE(wisusy_hdec, wisusy_hdec_type, "wisusy_hdec_", "cb_wisusy_hdec")
BE_VARIABLE(wisfer_hdec, wisfer_hdec_type, "wisfer_hdec_", "cb_wisfer_hdec")
BE_VARIABLE(hd_golddec, hd_golddec_type, "hd_golddec_", "cb_hd_golddec")
BE_VARIABLE(sd_char2body, sd_char2body_type, "sd_char2body_", "cb_sd_char2body")
BE_VARIABLE(sd_char2bodygrav, sd_char2bodygrav_type, "sd_char2bodygrav_", "cb_sd_char2bodygrav")
BE_VARIABLE(sd_char3body, sd_char3body_type, "sd_char3body_", "cb_sd_char3body")
BE_VARIABLE(sd_charwidth, sd_charwidth_type, "sd_charwidth_", "cb_sd_charwidth")
BE_VARIABLE(sd_neut2body, sd_neut2body_type, "sd_neut2body_", "cb_sd_neut2body")
BE_VARIABLE(sd_neut2bodygrav, sd_neut2bodygrav_type, "sd_neut2bodygrav_", "cb_sd_neut2bodygrav")
BE_VARIABLE(sd_neut3body, sd_neut3body_type, "sd_neut3body_", "cb_sd_neut3body")
BE_VARIABLE(sd_neutloop, sd_neutloop_type, "sd_neutloop_", "cb_sd_neutloop")
BE_VARIABLE(sd_neutwidth, sd_neutwidth_type, "sd_neutwidth_", "cb_sd_neutwidth")
BE_VARIABLE(sd_glui2body, sd_glui2body_type, "sd_glui2body_", "cb_sd_glui2body")
BE_VARIABLE(sd_glui3body, sd_glui3body_type, "sd_glui3body_", "cb_sd_glui3body")
BE_VARIABLE(sd_gluiloop, sd_gluiloop_type, "sd_gluiloop_", "cb_sd_gluiloop")
BE_VARIABLE(sd_gluiwidth, sd_gluiwidth_type, "sd_gluiwidth_", "cb_sd_gluiwidth")
BE_VARIABLE(sd_sup2body, sd_sup2body_type, "sd_sup2body_", "cb_sd_sup2body")
BE_VARIABLE(sd_supwidth, sd_supwidth_type, "sd_supwidth_", "cb_sd_supwidth")
BE_VARIABLE(sd_sdown2body, sd_sdown2body_type, "sd_sdown2body_", "cb_sd_sdown2body")
BE_VARIABLE(sd_sdownwidth, sd_sdownwidth_type, "sd_sdownwidth_", "cb_sd_sdownwidth")
BE_VARIABLE(sd_stop2body, sd_stop2body_type, "sd_stop2body_", "cb_sd_stop2body")
BE_VARIABLE(sd_stop3body, sd_stop3body_type, "sd_stop3body_", "cb_sd_stop3body")
BE_VARIABLE(sd_stoploop, sd_stoploop_type, "sd_stoploop_", "cb_sd_stoploop")
BE_VARIABLE(sd_stop4body, sd_stop4body_type, "sd_stop4body_", "cb_sd_stop4body")
BE_VARIABLE(sd_stopwidth, sd_stopwidth_type, "sd_stopwidth_", "cb_sd_stopwidth")
BE_VARIABLE(sd_sbot2body, sd_sbot2body_type, "sd_sbot2body_", "cb_sd_sbot2body")
BE_VARIABLE(sd_sbot3body, sd_sbot3body_type, "sd_sbot3body_", "cb_sd_sbot3body")
BE_VARIABLE(sd_sbotwidth, sd_sbotwidth_type, "sd_sbotwidth_", "cb_sd_sbotwidth")
BE_VARIABLE(sd_sel2body, sd_sel2body_type, "sd_sel2body_", "cb_sd_sel2body")
BE_VARIABLE(sd_selwidth, sd_selwidth_type, "sd_selwidth_", "cb_sd_selwidth")
BE_VARIABLE(sd_snel2body, sd_snel2body_type, "sd_snel2body_", "cb_sd_snel2body")
BE_VARIABLE(sd_snelwidth, sd_snelwidth_type, "sd_snelwidth_", "cb_sd_snelwidth")
BE_VARIABLE(sd_stau2body, sd_stau2body_type, "sd_stau2body_", "cb_sd_stau2body")
BE_VARIABLE(sd_stau2bodygrav, sd_stau2bodygrav_type, "sd_stau2bodygrav_", "cb_sd_stau2bodygrav")
BE_VARIABLE(sd_stauwidth, sd_stauwidth_type, "sd_stauwidth_", "cb_sd_stauwidth")
BE_VARIABLE(sd_sntau2body, sd_sntau2body_type, "sd_sntau2body_", "cb_sd_sntau2body")
BE_VARIABLE(sd_sntauwidth, sd_sntauwidth_type, "sd_sntauwidth_", "cb_sd_sntauwidth")
BE_VARIABLE(sd_top2body, sd_top2body_type, "sd_top2body_", "cb_sd_top2body")
BE_VARIABLE(sd_topwidth, sd_topwidth_type, "sd_topwidth_", "cb_sd_topwidth")
BE_VARIABLE(flavviolation, flavviolation_type, "flavviolation_", "cb_flavviolation")
BE_VARIABLE(sd_mbmb, sd_mbmb_type, "sd_mbmb_", "cb_sd_mbmb")
BE_VARIABLE(sd_selectron, sd_selectron_type, "sd_selectron_", "cb_sd_selectron")

// Convenience functions (registration)
BE_CONV_FUNCTION(run_susy_hit, void, (SLHAstruct, double, double), "susy_hit_backend_level_init")

// Initialisation function (dependencies)
BE_INI_DEPENDENCY(MSSM_spectrum, Spectrum)
BE_INI_DEPENDENCY(W_minus_decay_rates, DecayTable::Entry)
BE_INI_DEPENDENCY(W_plus_decay_rates, DecayTable::Entry)
BE_INI_DEPENDENCY(Z_decay_rates, DecayTable::Entry)

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
