//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for PrecisionBit.
///
///  Compile-time registration of available
///  observables and likelihoods for (mostly
///  electroweak) precision observables.
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
///  \date 2014 Nov
///  \date 2015 Aug
///
///  \author Christopher Rogan
///          (christophersrogan@gmail.com)
///  \date 2015 Apr
///
///  \author Anders Kvellestad
///          (anders.kvellestad@nordita.org)
///  \date 2016 Feb
///
///  \author Ankit Beniwal
///          (ankit.beniwal@adelaide.edu.au)
///  \date 2016 Oct
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2018 Jan
///
///  *********************************************


#ifndef __PrecisionBit_rollcall_hpp__
#define __PrecisionBit_rollcall_hpp__


#define MODULE PrecisionBit
START_MODULE


  // FeynHiggs EWK precision observables
  #define CAPABILITY FH_Precision
  START_CAPABILITY
    #define FUNCTION FH_PrecisionObs
    START_FUNCTION(fh_PrecisionObs)
    DEPENDENCY(FH_Couplings_output, fh_Couplings)
    BACKEND_REQ(FHConstraints, (libfeynhiggs), void, (int&,fh_real&,fh_real&,fh_real&,fh_real&,
                fh_real&,fh_real&,fh_real&,fh_real&,fh_real&,int&))
    BACKEND_OPTION( (FeynHiggs), (libfeynhiggs) )
    ALLOW_MODELS(MSSM30atQ, MSSM30atMGUT, NUHM2)
    #undef FUNCTION
  #undef CAPABILITY

  // Extractors for FeynHiggs EWK precision observables
  QUICK_FUNCTION(PrecisionBit, muon_gm2,       NEW_CAPABILITY, FH_precision_gm2,      triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (FH_Precision, fh_PrecisionObs))
  QUICK_FUNCTION(PrecisionBit, deltarho,       NEW_CAPABILITY, FH_precision_deltarho, triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (FH_Precision, fh_PrecisionObs))
  QUICK_FUNCTION(PrecisionBit, prec_mw,        NEW_CAPABILITY, FH_precision_mw,       triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (FH_Precision, fh_PrecisionObs))
  QUICK_FUNCTION(PrecisionBit, prec_sinW2_eff, NEW_CAPABILITY, FH_precision_sinW2,    triplet<double>, (MSSM30atQ, MSSM30atMGUT, NUHM2), (FH_Precision, fh_PrecisionObs))
  QUICK_FUNCTION(PrecisionBit, edm_e,          NEW_CAPABILITY, FH_precision_edm_e,    double,          (MSSM30atQ, MSSM30atMGUT, NUHM2), (FH_Precision, fh_PrecisionObs))
  QUICK_FUNCTION(PrecisionBit, edm_n,          NEW_CAPABILITY, FH_precision_edm_n,    double,          (MSSM30atQ, MSSM30atMGUT, NUHM2), (FH_Precision, fh_PrecisionObs))
  QUICK_FUNCTION(PrecisionBit, edm_hg,         NEW_CAPABILITY, FH_precision_edm_hg,   double,          (MSSM30atQ, MSSM30atMGUT, NUHM2), (FH_Precision, fh_PrecisionObs))

  // Precision MSSM spectrum manufacturers
  #define CAPABILITY MSSM_spectrum
  START_CAPABILITY

    #define FUNCTION make_MSSM_precision_spectrum_4H_W
    START_FUNCTION(Spectrum)
    DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)
    DEPENDENCY(prec_mw, triplet<double>)
    DEPENDENCY(prec_mh, triplet<double>)
    DEPENDENCY(prec_HeavyHiggsMasses, map_int_triplet_dbl)
    #undef FUNCTION

    #define FUNCTION make_MSSM_precision_spectrum_H_W
    START_FUNCTION(Spectrum)
    DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)
    DEPENDENCY(prec_mw, triplet<double>)
    DEPENDENCY(prec_mh, triplet<double>)
    #undef FUNCTION

    #define FUNCTION make_MSSM_precision_spectrum_H
    START_FUNCTION(Spectrum)
    DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)
    DEPENDENCY(prec_mh, triplet<double>)
    #undef FUNCTION

    #define FUNCTION make_MSSM_precision_spectrum_W
    START_FUNCTION(Spectrum)
    DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)
    DEPENDENCY(prec_mw, triplet<double>)
    #undef FUNCTION

    #define FUNCTION make_MSSM_precision_spectrum_none
    START_FUNCTION(Spectrum)
    DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY

  // Basic mass extractors for different types of spectra, for use with precision likelihoods and other things not needing a whole spectrum object.
  QUICK_FUNCTION(PrecisionBit, mw, NEW_CAPABILITY, mw_from_SM_spectrum,                   triplet<double>, (),                                              (SM_spectrum, Spectrum))
  QUICK_FUNCTION(PrecisionBit, mw, OLD_CAPABILITY, mw_from_ScalarSingletDM_Z2_spectrum,   triplet<double>, (ScalarSingletDM_Z2,ScalarSingletDM_Z2_running), (ScalarSingletDM_Z2_spectrum, Spectrum))
  QUICK_FUNCTION(PrecisionBit, mw, OLD_CAPABILITY, mw_from_ScalarSingletDM_Z3_spectrum,   triplet<double>, (ScalarSingletDM_Z3,ScalarSingletDM_Z3_running), (ScalarSingletDM_Z3_spectrum, Spectrum))
  QUICK_FUNCTION(PrecisionBit, mw, OLD_CAPABILITY, mw_from_VectorSingletDM_Z2_spectrum,   triplet<double>, (VectorSingletDM_Z2),                            (VectorSingletDM_Z2_spectrum, Spectrum))
  QUICK_FUNCTION(PrecisionBit, mw, OLD_CAPABILITY, mw_from_DiracSingletDM_Z2_spectrum,    triplet<double>, (DiracSingletDM_Z2),                             (DiracSingletDM_Z2_spectrum, Spectrum))
  QUICK_FUNCTION(PrecisionBit, mw, OLD_CAPABILITY, mw_from_MajoranaSingletDM_Z2_spectrum, triplet<double>, (MajoranaSingletDM_Z2),                          (MajoranaSingletDM_Z2_spectrum, Spectrum))
  QUICK_FUNCTION(PrecisionBit, mw, OLD_CAPABILITY, mw_from_MSSM_spectrum,                 triplet<double>, (MSSM63atQ, MSSM63atMGUT),                       (MSSM_spectrum, Spectrum))
  QUICK_FUNCTION(PrecisionBit, mh, NEW_CAPABILITY, mh_from_SM_spectrum,                   triplet<double>, (),                                              (SM_spectrum, Spectrum))
  QUICK_FUNCTION(PrecisionBit, mh, OLD_CAPABILITY, mh_from_ScalarSingletDM_Z2_spectrum,   triplet<double>, (ScalarSingletDM_Z2,ScalarSingletDM_Z2_running), (ScalarSingletDM_Z2_spectrum, Spectrum))
  QUICK_FUNCTION(PrecisionBit, mh, OLD_CAPABILITY, mh_from_ScalarSingletDM_Z3_spectrum,   triplet<double>, (ScalarSingletDM_Z3,ScalarSingletDM_Z3_running), (ScalarSingletDM_Z3_spectrum, Spectrum))
  QUICK_FUNCTION(PrecisionBit, mh, OLD_CAPABILITY, mh_from_MSSM_spectrum,                 triplet<double>, (MSSM63atQ, MSSM63atMGUT),                       (MSSM_spectrum, Spectrum))

  // SM nuisance likelihoods
  QUICK_FUNCTION(PrecisionBit, lnL_Z_mass,   NEW_CAPABILITY, lnL_Z_mass_chi2,   double, (), (SMINPUTS, SMInputs))
  QUICK_FUNCTION(PrecisionBit, lnL_t_mass,   NEW_CAPABILITY, lnL_t_mass_chi2,   double, (), (SMINPUTS, SMInputs))
  QUICK_FUNCTION(PrecisionBit, lnL_mbmb,     NEW_CAPABILITY, lnL_mbmb_chi2,     double, (), (SMINPUTS, SMInputs))
  QUICK_FUNCTION(PrecisionBit, lnL_mcmc,     NEW_CAPABILITY, lnL_mcmc_chi2,     double, (), (SMINPUTS, SMInputs))
  QUICK_FUNCTION(PrecisionBit, lnL_alpha_em, NEW_CAPABILITY, lnL_alpha_em_chi2, double, (), (SMINPUTS, SMInputs))
  QUICK_FUNCTION(PrecisionBit, lnL_alpha_s,  NEW_CAPABILITY, lnL_alpha_s_chi2,  double, (), (SMINPUTS, SMInputs))
  QUICK_FUNCTION(PrecisionBit, lnL_GF,       NEW_CAPABILITY, lnL_GF_chi2,       double, (), (SMINPUTS, SMInputs))

  QUICK_FUNCTION(PrecisionBit, lnL_light_quark_masses, NEW_CAPABILITY, lnL_light_quark_masses_chi2, double, (), (SMINPUTS, SMInputs))


  // Electroweak precision likelihoods: W mass
  #define CAPABILITY lnL_W_mass
  START_CAPABILITY
    #define FUNCTION lnL_W_mass_chi2
    START_FUNCTION(double)
    DEPENDENCY(mw, triplet<double>)
    #undef FUNCTION
  #undef CAPABILITY

  // Naive Higgs mass likelihood
  #define CAPABILITY lnL_h_mass
  START_CAPABILITY
    #define FUNCTION lnL_h_mass_chi2
    START_FUNCTION(double)
    DEPENDENCY(mh, triplet<double>)
    #undef FUNCTION
  #undef CAPABILITY

  // Electroweak precision likelihoods: effective leptonic weak mixing angle
  #define CAPABILITY lnL_sinW2_eff
  START_CAPABILITY
    #define FUNCTION lnL_sinW2_eff_chi2
    START_FUNCTION(double)
    DEPENDENCY(prec_sinW2_eff, triplet<double>)
    #undef FUNCTION
  #undef CAPABILITY


  // Precision likelihood: (g-2)_\mu
  #define CAPABILITY lnL_gm2
  START_CAPABILITY
    #define FUNCTION lnL_gm2_chi2
    START_FUNCTION(double)
    DEPENDENCY(muon_gm2, triplet<double>)
    DEPENDENCY(muon_gm2_SM, triplet<double>)
    #undef FUNCTION
  #undef CAPABILITY

  // Electroweak precision likelihoods: Delta rho
  #define CAPABILITY lnL_deltarho
  START_CAPABILITY
    #define FUNCTION lnL_deltarho_chi2
    START_FUNCTION(double)
    DEPENDENCY(deltarho, triplet<double>)
    #undef FUNCTION
  #undef CAPABILITY

  // SUSYPOPE EWK precision observables
  #define CAPABILITY SP_PrecisionObs
  START_CAPABILITY
    #define FUNCTION SP_PrecisionObs
    START_FUNCTION(double)
    BACKEND_REQ(CalcObs_SUSYPOPE, (libSUSYPOPE), void, (int&,
                                                        Farray<Fdouble,1,35>&,
                                                        Farray<Fdouble,1,35>&))
    BACKEND_OPTION( (SUSYPOPE, 0.2), (libSUSYPOPE) )
    ALLOW_MODELS(MSSM30atQ, MSSM30atMGUT, NUHM2)
    #undef FUNCTION
  #undef CAPABILITY


  // Observable: BSM contribution to (g-2)_mu
  #define CAPABILITY muon_gm2

    // Muon g-2 -- Using SuperIso
    #define FUNCTION SI_muon_gm2
    START_FUNCTION(triplet<double>)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(muon_gm2, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION

    // Muon g-2 -- Using gm2calc
    #define FUNCTION GM2C_SUSY
    START_FUNCTION(triplet<double>)
    NEEDS_CLASSES_FROM(gm2calc, default)
    DEPENDENCY(MSSM_spectrum, Spectrum)
    BACKEND_REQ(calculate_amu_1loop, (libgm2calc), double, (const gm2calc_default::gm2calc::MSSMNoFV_onshell&))
    BACKEND_REQ(calculate_amu_2loop, (libgm2calc), double, (const gm2calc_default::gm2calc::MSSMNoFV_onshell&))
    BACKEND_REQ(calculate_uncertainty_amu_2loop, (libgm2calc), double, (const gm2calc_default::gm2calc::MSSMNoFV_onshell&))
    BACKEND_OPTION( (gm2calc), (libgm2calc) )
    ALLOW_MODELS(MSSM30atQ, MSSM30atQ_mA, MSSM30atMGUT, MSSM30atMGUT_mA, NUHM2)
    #undef FUNCTION

  #undef CAPABILITY

  // Observable: SM contribution to (g-2)_mu
  #define CAPABILITY muon_gm2_SM

    // SM muon g-2, based on e+e- data
    #define FUNCTION gm2_SM_ee
    START_FUNCTION(triplet<double>)
    #undef FUNCTION

    // SM muon g-2, based on tau+tau- data
    #define FUNCTION gm2_SM_tautau
    START_FUNCTION(triplet<double>)
    #undef FUNCTION

  #undef CAPABILITY

  // EWPO corrections from heavy neutrinos
  #define CAPABILITY prec_sinW2_eff
    #define FUNCTION RHN_sinW2_eff
    START_FUNCTION(triplet<double>)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY mw
    #define FUNCTION RHN_mw
    START_FUNCTION(triplet<double>)
    DEPENDENCY(prec_sinW2_eff, triplet<double>)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_MODEL(RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY

  // Neutron lifetime likelihood: beam
  #define CAPABILITY lnL_neutron_lifetime_beam
  START_CAPABILITY
    #define FUNCTION lnL_neutron_lifetime_beam_Yue
    START_FUNCTION(double)
    ALLOW_MODEL(nuclear_params_neutron_lifetime)
    #undef FUNCTION
  #undef CAPABILITY

  // Neutron lifetime likelihood: bottle
  #define CAPABILITY lnL_neutron_lifetime_bottle
  START_CAPABILITY
    #define FUNCTION lnL_neutron_lifetime_bottle_PDG19
    START_FUNCTION(double)
    ALLOW_MODEL(nuclear_params_neutron_lifetime)
    #undef FUNCTION
  #undef CAPABILITY




#undef MODULE


#endif /* defined(__PrecisionBit_rollcall_hpp__) */


