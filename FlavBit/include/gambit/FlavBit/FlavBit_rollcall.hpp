//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
/// \file
///
/// Rollcall header for module FlavBit.
///
/// Compile-time registration of available
/// observables and likelihoods, as well as their
/// dependencies.
///
/// Add to this if you want to add an observable
/// or likelihood to this module.
///
/// *********************************************
///
/// Authors (add name and date if you modify):
///
/// \author Nazila Mahmoudi
/// \date 2013 Oct
/// \date 2014 Jun
/// \date 2014 Sep
/// \date 2015 Feb
/// \date 2016 Jul
/// \date 2018 Jan
/// \date 2019 Aug
///
/// \author Pat Scott
/// \date 2015 May
/// \date 2016 Aug
/// \date 2017 March
///
/// \author Marcin Chrzaszcz
/// \date 2015 May
/// \date 2016 Aug
/// \date 2016 Oct
/// \date 2018 Jan
///
/// \author Tomas Gonzalo
/// \date 2017 July
///
/// \author Cristian Sierra
/// \date 2020 June-December
/// \date 2021 Jan-May
///
/// \author Filip Rajec
///         (filip.rajec@adelaide.edu.au)
/// \date 2020 Apr
///
/// \author Jihyun Bhom
/// \date 2019 July
/// \date 2019 Aug
///
/// \author Markus Prim
/// \date 2019 Aug
///
/// *********************************************

#ifndef __FlavBit_rollcall_hpp__
#define __FlavBit_rollcall_hpp__

#include "gambit/FlavBit/FlavBit_types.hpp"

#define MODULE FlavBit
#define REFERENCE GAMBITFlavourWorkgroup:2017dbx,Bhom:2020lmk
START_MODULE

  // TODO: All these are only muon flavour, should they be triplets?

  /// C2
  #define CAPABILITY DeltaC2
  START_CAPABILITY

    /// C2 in the THDM
    #define FUNCTION THDM_DeltaC2
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C7
  #define CAPABILITY DeltaC7
  START_CAPABILITY

    /// C7 in the THDM
    #define FUNCTION THDM_DeltaC7
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C8
  #define CAPABILITY DeltaC8
  START_CAPABILITY

    /// C8 in the THDM
    #define FUNCTION THDM_DeltaC8
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C9
  #define CAPABILITY DeltaC9
  START_CAPABILITY

    /// C9 in the THDM
    #define FUNCTION THDM_DeltaC9
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C10 in the THDM
  #define CAPABILITY DeltaC10
  START_CAPABILITY

    /// C10 in the THDM
    #define FUNCTION THDM_DeltaC10
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C7'
  #define CAPABILITY DeltaC7_Prime
  START_CAPABILITY

    /// C7' in the THDM
    #define FUNCTION THDM_DeltaC7_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C8'
  #define CAPABILITY DeltaC8_Prime
  START_CAPABILITY

    /// C8' in the THDM
    #define FUNCTION THDM_DeltaC8_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C9'
  #define CAPABILITY DeltaC9_Prime
  START_CAPABILITY

    /// C9' in the THDM
    #define FUNCTION THDM_DeltaC9_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  /// C10'
  #define CAPABILITY DeltaC10_Prime
  START_CAPABILITY

    /// C10' in the THDM
    #define FUNCTION THDM_DeltaC10_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// CQ1
  #define CAPABILITY DeltaCQ1
  START_CAPABILITY

    /// CQ1 in the THDM
    #define FUNCTION THDM_DeltaCQ1
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// CQ2
  #define CAPABILITY DeltaCQ2
  START_CAPABILITY

    /// CQ2 in the THDM
    #define FUNCTION THDM_DeltaCQ2
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// CQ1'
  #define CAPABILITY DeltaCQ1_Prime
  START_CAPABILITY

    /// CQ1' in the THDM
    #define FUNCTION THDM_DeltaCQ1_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// CQ2'
  #define CAPABILITY DeltaCQ2_Prime
  START_CAPABILITY

    ///CQ2' in the THDM
    #define FUNCTION THDM_DeltaCQ2_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C9 for tau-tau processes
  #define CAPABILITY DeltaC9_tautau
  START_CAPABILITY

    /// C9 for tau-tau processes in the THDM
    #define FUNCTION THDM_DeltaC9_tautau
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C10 for tau-tau processes
  #define CAPABILITY DeltaC10_tautau
  START_CAPABILITY

    /// C10 for tau-tau processes in the THDM
    #define FUNCTION THDM_DeltaC10_tautau
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C9' for tau-tau processes
  #define CAPABILITY DeltaC9_tautau_Prime
  START_CAPABILITY

    /// C9' for tau-tau processes in the THDM
    #define FUNCTION THDM_DeltaC9_tautau_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// C10' for tau-tau processes
  #define CAPABILITY DeltaC10_tautau_Prime
  START_CAPABILITY

    /// C10' for tau-tau processes in the THDM
    #define FUNCTION THDM_DeltaC10_tautau_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// CQ1 for tau-tau processes
  #define CAPABILITY DeltaCQ1_tautau
  START_CAPABILITY

    /// CQ1 for tau-tau processes in the THDM
    #define FUNCTION THDM_DeltaCQ1_tautau
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// CQ2 for tau-tau processes
  #define CAPABILITY DeltaCQ2_tautau
  START_CAPABILITY

    /// CQ2 for tau-tau processes in the THDM
    #define FUNCTION THDM_DeltaCQ2_tautau
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// CQ1' for tau-tau processes
  #define CAPABILITY DeltaCQ1_tautau_Prime
  START_CAPABILITY

    /// CQ1' for tau-tau processes in the THDM
    #define FUNCTION THDM_DeltaCQ1_tautau_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  /// CQ2' for tau-tau processes
  #define CAPABILITY DeltaCQ2_tautau_Prime
  START_CAPABILITY

    /// CQ2' for tau-tau processes in the THDM
    #define FUNCTION THDM_DeltaCQ2_tautau_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Initialisation capability (fill the SuperIso structure)
  #define CAPABILITY SuperIso_modelinfo
  START_CAPABILITY
    #define FUNCTION SuperIso_fill
    START_FUNCTION(parameters)
    ALLOW_MODELS(THDM, THDMatQ)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, GWC)
    BACKEND_REQ(Init_param, (libsuperiso), void, (parameters*))
    BACKEND_REQ(slha_adjust, (libsuperiso), void, (parameters*))
    BACKEND_REQ(mcmc_from_pole, (libsuperiso), double, (double, int, parameters*))
    BACKEND_REQ(mb_1S, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    DEPENDENCY(W_plus_decay_rates, DecayTable::Entry)
    DEPENDENCY(Z_decay_rates, DecayTable::Entry)
    MODEL_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(SM_spectrum, Spectrum, GWC)
    MODEL_CONDITIONAL_DEPENDENCY(THDM_spectrum, Spectrum, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC2, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC7, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC8, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC9, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC10, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC7_Prime, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC8_Prime, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC9_Prime, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC10_Prime, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaCQ1, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaCQ2, std::complex<double>,  THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaCQ1_Prime, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaCQ2_Prime, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC9_tautau, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC10_tautau, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC9_tautau_Prime, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaC10_tautau_Prime, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaCQ1_tautau, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaCQ2_tautau, std::complex<double>,  THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaCQ1_tautau_Prime, std::complex<double>, THDM, THDMatQ)
    MODEL_CONDITIONAL_DEPENDENCY(DeltaCQ2_tautau_Prime, std::complex<double>, THDM, THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY


  ///Initialisation capability (fill the SuperIso nuisance structure)
  #define CAPABILITY SuperIso_nuisance
  START_CAPABILITY
    #define FUNCTION SuperIso_nuisance_fill
    START_FUNCTION(nuisance)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(set_nuisance, (libsuperiso), void, (nuisance*))
    BACKEND_REQ(set_nuisance_value_from_param, (libsuperiso), void, (nuisance*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDstarlnu
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu
    START_FUNCTION(map_dblpair_dbl)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  //B-Dstartanu distribution measurements
  #define CAPABILITY BDstartaunu_M
  START_CAPABILITY
    #define FUNCTION BDstartaunu_measurements
    START_FUNCTION(FlavBit::predictions_measurements_covariances)
    DEPENDENCY(BDstarlnu, map_dblpair_dbl)
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY BDlnu
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu
    START_FUNCTION(map_dblpair_dbl)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  ///B-Dtanu distribution measurements
  #define CAPABILITY BDtaunu_M
  START_CAPABILITY
    #define FUNCTION BDtaunu_measurements
    START_FUNCTION(FlavBit::predictions_measurements_covariances)
    DEPENDENCY(BDlnu, map_dblpair_dbl)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: mu-e universality for the gTHDM from JHEP07(2013)044
  #define CAPABILITY gmu_ge
  START_CAPABILITY
    #define FUNCTION THDM_gmu_ge
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: FLDstar polarization
  #define CAPABILITY FLDstar
  START_CAPABILITY
    #define FUNCTION THDM_FLDstar
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: Bc lifetime
  #define CAPABILITY Bc_lifetime
  START_CAPABILITY
    #define FUNCTION THDM_Bc_lifetime
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: Bs2mutau
  #define CAPABILITY Bs2mutau
  START_CAPABILITY
    #define FUNCTION THDM_Bs2mutau
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: Bs2tautau
  #define CAPABILITY Bs2tautau
  START_CAPABILITY
    #define FUNCTION THDM_Bs2tautau
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: B2Kmue
  #define CAPABILITY B2Kmue
  START_CAPABILITY
    #define FUNCTION THDM_B2Kmue
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: B2Ktaumu
  #define CAPABILITY B2Ktaumu
  START_CAPABILITY
    #define FUNCTION THDM_B2Ktaumu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  // TODO: attempt to upgrade to use the 'observables' backend function
  ///Observable: BR(B+ ->K+ tau tau)
  #define CAPABILITY B2Ktautau
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_BRBKtautau
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBKtautau_CONV, (libsuperiso), double, (const parameters*, double, double))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
    //#define FUNCTION SuperIso_prediction_BKtautauBr_12p6_22p9
    //START_FUNCTION(flav_prediction)
    //DEPENDENCY(SuperIso_modelinfo, parameters)
    //DEPENDENCY(SuperIso_nuisance, nuisance)
    //BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    //BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    //BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    //BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    //BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    //#undef FUNCTION
  #undef CAPABILITY


  ///Observable: RKnunu
  #define CAPABILITY RKnunu
  START_CAPABILITY
    #define FUNCTION THDM_RKnunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: RKstarnunu
  #define CAPABILITY RKstarnunu
  START_CAPABILITY
    #define FUNCTION THDM_RKstarnunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY prediction_B2mumu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_B2mumu
    START_FUNCTION(flav_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    #define FUNCTION FeynHiggs_prediction_Bsmumu
    START_FUNCTION(double)
    DEPENDENCY(FlavourObs, fh_FlavourObs_container)
    #undef FUNCTION

  #undef CAPABILITY


  // TODO: Does not work currently as it is not implemented in SuperIso in this form
  /*#define CAPABILITY prediction_B2taunu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_B2taunu
    START_FUNCTION(flav_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

  #undef CAPABILITY
  */

  /* TODO: this should be re-activated once RD and RDstar can be extracted from a future version of SuperIso using the check_nameobs function.
  #define CAPABILITY prediction_RDRDstar
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_RDRDstar
    START_FUNCTION(flav_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
   #undef FUNCTION
  #undef CAPABILITY
  */


  #define CAPABILITY prediction_b2sgamma
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_b2sgamma
    START_FUNCTION(flav_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    #define FUNCTION FeynHiggs_prediction_bsgamma
    START_FUNCTION(double)
    DEPENDENCY(FlavourObs, fh_FlavourObs_container)
    BACKEND_REQ(FHFlavour, (libfeynhiggs), void, (int&,fh_real&,fh_real&,fh_real&,fh_real&,fh_real&,fh_real&))
    BACKEND_OPTION( (FeynHiggs), (libfeynhiggs) )
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY prediction_B2Kstargamma
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2Kstargamma
    START_FUNCTION(flav_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  // TODO: This is never used in any likelihood, why?
  #define CAPABILITY prediction_BRBXsmumu_lowq2
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_BRBXsmumu_lowq2
    START_FUNCTION(flav_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  // TODO: This is never used in any likelihood, why?
  #define CAPABILITY prediction_BRBXsmumu_highq2
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_BRBXsmumu_highq2
    START_FUNCTION(flav_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  // TODO: This is never used in any likelihood, why?
  #define CAPABILITY prediction_AFBBXsmumu_lowq2
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_AFBBXsmumu_lowq2
    START_FUNCTION(flav_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  // TODO: This is never used in any likelihood, why?
  #define CAPABILITY prediction_AFBBXsmumu_highq2
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_AFBBXsmumu_highq2
    START_FUNCTION(flav_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY prediction_B2KstarmumuBr
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuBr
    START_FUNCTION(flav_binned_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY prediction_B2KmumuBr
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KmumuBr
    START_FUNCTION(flav_binned_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY prediction_Bs2phimumuBr
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_Bs2phimumuBr
    START_FUNCTION(flav_binned_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY prediction_B2KstarmumuAng_Atlas
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_Atlas
    START_FUNCTION(flav_binned_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY prediction_B2KstarmumuAng_CMS
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_CMS
    START_FUNCTION(flav_binned_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY prediction_B2KstarmumuAng_Belle
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_Belle
    START_FUNCTION(flav_binned_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY prediction_B2KstarmumuAng_LHCb
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_LHCb
    START_FUNCTION(flav_binned_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY prediction_B2KstareeAng_Lowq2_LHCb
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstareeAng_Lowq2_LHCb
    START_FUNCTION(flav_binned_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  // TODO: these should be re-activated once RK and RKstar can be extracted from a future version of SuperIso using the check_nameobs function.
  /*
  #define CAPABILITY prediction_RK_LHCb
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_RK_LHCb
    START_FUNCTION(flav_binned_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  #define CAPABILITY prediction_RKstar_LHCb
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_RKstar_LHCb
    START_FUNCTION(flav_binned_prediction)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_REQ(observables, (libsuperiso), void, (int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*))
    BACKEND_REQ(convert_correlation, (libsuperiso), void, (nuiscorr*, int, double**, char**, int))
    BACKEND_REQ(get_th_covariance_nuisance, (libsuperiso), void, (double***, char**, int*, const parameters*, const nuisance*, double**))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  */


  ///Observable: BR(B -> tau nu)
  #define CAPABILITY Btaunu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_Btaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Btaunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_Btaunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM, THDMatQ)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: BR(B->D e nu)/BR(B->D mu nu)
  #define CAPABILITY RDemu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_RDemu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_RDemu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: BR(B->D tau nu)/BR(B->D mu nu)
  #define CAPABILITY RD
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_RD
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BDtaunu_BDenu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_RD
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: BR(B->D tau nu)/BR(B->D mu nu)
  #define CAPABILITY RDstar
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_RDstar
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BDstartaunu_BDstarenu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_RDstar
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: BR(K->mu nu)/BR(pi->mu nu)
  #define CAPABILITY Rmu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_Rmu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Kmunu_pimunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_Rmu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: Rmu23
  #define CAPABILITY Rmu23
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_Rmu23
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Rmu23, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: BR(Ds->tau nu)
  #define CAPABILITY Dstaunu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_Dstaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Dstaunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_Dstaunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: BR(Ds->mu nu)
  #define CAPABILITY Dsmunu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_Dsmunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Dsmunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_Dsmunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: BR(D->mu nu)
  #define CAPABILITY Dmunu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_Dmunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Dmunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_Dmunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: BR(D->tau nu)
  #define CAPABILITY Dtaunu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_Dtaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Dlnu, (libsuperiso), double, (int, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION


    //Function for the general THDM
    #define FUNCTION THDM_Dtaunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: BR(B->D tau nu)
  #define CAPABILITY BDtaunu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_BDtaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_BDtaunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: BR(B->D mu nu)
  #define CAPABILITY BDmunu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_BDmunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_BDmunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: BR(B->D* tau nu)
  #define CAPABILITY BDstartaunu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_BDstartaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDstarlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_BDstartaunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: BR(B->D* mu nu)
  #define CAPABILITY BDstarmunu
  START_CAPABILITY

    #define FUNCTION SuperIso_prediction_BDstarmunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDstarlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    //Function for the general THDM
    #define FUNCTION THDM_BDstarmunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY


  ///Tree-level leptonic and semi-leptonic B & D decay measurements
  #define CAPABILITY SL_M
  START_CAPABILITY
    #define FUNCTION SL_measurements
    START_FUNCTION(FlavBit::predictions_measurements_covariances)
    DEPENDENCY(RD, double)
    DEPENDENCY(RDstar, double)
    DEPENDENCY(BDmunu, double)
    DEPENDENCY(BDstarmunu, double)
    DEPENDENCY(Btaunu, double)
    DEPENDENCY(Rmu, double)
    DEPENDENCY(Dstaunu, double)
    DEPENDENCY(Dsmunu, double)
    DEPENDENCY(Dmunu, double)
    DEPENDENCY(Dtaunu, double)
    DEPENDENCY(RDemu, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: Delta0(B -> K* gamma)
  // TODO: This is never used in any likelihood, why?
  #define CAPABILITY delta0
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_delta0
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(modified_delta0, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: zero of AFB(B -> Xs mu mu)
  // TODO: This is never used in any likelihood, why?
  #define CAPABILITY A_BXsmumu_zero
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_A_BXsmumu_zero
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(A_BXsmumu_zero, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: BR(B -> Xs tau tau)_highq2
  // TODO: This is never used in any likelihood, why?
  #define CAPABILITY BRBXstautau_highq2
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_BRBXstautau_highq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBXstautau_highq2, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: AFB(B -> Xs tau tau)_highq2
  // TODO: This is never used in any likelihood, why?
  #define CAPABILITY A_BXstautau_highq2
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_A_BXstautau_highq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(A_BXstautau_highq2, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: A_I(B -> K* mu mu)
  // TODO: This is never used in any likelihood, why?
  #define CAPABILITY AI_BKstarmumu
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_AI_BKstarmumu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(modified_AI_BKstarmumu, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: zero of A_I(B -> K* mu mu)
  // TODO: This is never used in any likelihood, why?
  #define CAPABILITY AI_BKstarmumu_zero
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_AI_BKstarmumu_zero
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(modified_AI_BKstarmumu_zero, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // TODO: Temporary restore of RK and RKstar convenience functions until their new interface is fixed
  // Observable: RK* in q^2 bin from 0.045 GeV^2 to 1.1 GeV^2
  #define CAPABILITY RKstar_0045_11
  START_CAPABILITY
    #define FUNCTION SuperIso_RKstar_0045_11
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    BACKEND_REQ(RKstar, (libsuperiso), double, (const parameters*, double, double))
    #undef FUNCTION

    // Function to calcualte RK* for RHN
    #define FUNCTION RHN_RKstar_0045_11
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(StandardModel_SLHA2,RightHandedNeutrinos)
    #undef FUNCTION

  #undef CAPABILITY

  // TODO: Temporary restore of RK and RKstar convenience functions until their new interface is fixed
  // Observable: RK* in q^2 bin from 1.1 GeV^2 to 6 GeV^2
  #define CAPABILITY RKstar_11_60
  START_CAPABILITY
    #define FUNCTION SuperIso_RKstar_11_60
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    BACKEND_REQ(RKstar, (libsuperiso), double, (const parameters*, double, double))
    #undef FUNCTION

    // Function to calculate RK* for RHN
    #define FUNCTION RHN_RKstar_11_60
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(StandardModel_SLHA2,RightHandedNeutrinos)
    #undef FUNCTION

  #undef CAPABILITY

  // TODO: Temporary restore of RK and RKstar convenience functions until their new interface is fixed
  // Observable: RK in q^2 bin from 1 GeV^2 to 6 GeV^2
  #define CAPABILITY RK
  START_CAPABILITY
    #define FUNCTION SuperIso_RK
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    BACKEND_REQ(RK, (libsuperiso), double, (const parameters*, double, double))
    #undef FUNCTION

    //Function to calculate RK for RHN
    #define FUNCTION RHN_RK
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(StandardModel_SLHA2,RightHandedNeutrinos)
    #undef FUNCTION
  #undef CAPABILITY


  ///All FeynHiggs flavour observables
  #define CAPABILITY FlavourObs
  START_CAPABILITY
    #define FUNCTION FeynHiggs_FlavourObs
    START_FUNCTION(fh_FlavourObs_container)
    BACKEND_REQ(FHFlavour, (libfeynhiggs), void, (int&,fh_real&,fh_real&,fh_real&,fh_real&,fh_real&,fh_real&))
    BACKEND_OPTION( (FeynHiggs), (libfeynhiggs) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: B_s mass difference
  #define CAPABILITY prediction_DeltaMs
  START_CAPABILITY

    #define FUNCTION FeynHiggs_prediction_DeltaMs
    START_FUNCTION(double)
    DEPENDENCY(FlavourObs, fh_FlavourObs_container)
    #undef FUNCTION

    #define FUNCTION SuperIso_prediction_Delta_MBs
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Delta_MBs, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION

    #define FUNCTION THDM_Delta_MBs
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: B_d mass difference
  #define CAPABILITY DeltaMd
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_Delta_MBd
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Delta_MB, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: BR(h->bs)
  #define CAPABILITY h2bs
  START_CAPABILITY
    #define FUNCTION THDM_h2bs
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: BR(t->ch)
  #define CAPABILITY t2ch
  START_CAPABILITY
    #define FUNCTION THDM_t2ch
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY


  //###############################################
  //Lepton Flavour Universality Violation
  //###############################################


  ///Observable: BR(h->tau mu)
  #define CAPABILITY h2taumu
  START_CAPABILITY
    #define FUNCTION THDM_h2taumu
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: mu -> e gamma
  #define CAPABILITY muegamma
  START_CAPABILITY
    #define FUNCTION RHN_muegamma
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(mu_minus_decay_rates, DecayTable::Entry)
    ALLOW_MODELS(RightHandedNeutrinos)
    #undef FUNCTION
    //Function for gTHDM
    #define FUNCTION THDM_muegamma
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: tau -> e gamma
  #define CAPABILITY tauegamma
  START_CAPABILITY

    #define FUNCTION RHN_tauegamma
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(tau_minus_decay_rates, DecayTable::Entry)
    ALLOW_MODELS(RightHandedNeutrinos)
    #undef FUNCTION

    //Function for gTHDM
    #define FUNCTION THDM_tauegamma
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: tau -> mu gamma
  #define CAPABILITY taumugamma
  START_CAPABILITY

    #define FUNCTION RHN_taumugamma
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(tau_minus_decay_rates, DecayTable::Entry)
    ALLOW_MODELS(RightHandedNeutrinos)
    #undef FUNCTION

    //Function for gTHDM
    #define FUNCTION THDM_taumugamma
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: mu- -> e- e- e+
  #define CAPABILITY mueee
  START_CAPABILITY

    #define FUNCTION RHN_mueee
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(mu_minus_decay_rates, DecayTable::Entry)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_Higgs)
    #undef FUNCTION

    //Function for gTHDM
    #define FUNCTION THDM_mueee
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: tau- -> e- e- e+
  #define CAPABILITY taueee
  START_CAPABILITY

    #define FUNCTION RHN_taueee
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(tau_minus_decay_rates, DecayTable::Entry)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_Higgs)
    #undef FUNCTION

    //Function for gTHDM
    #define FUNCTION THDM_taueee
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: tau- -> mu- mu- mu+
  #define CAPABILITY taumumumu
  START_CAPABILITY

    #define FUNCTION RHN_taumumumu
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(tau_minus_decay_rates, DecayTable::Entry)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_Higgs)
    #undef FUNCTION

    //Function for gTHDM
    #define FUNCTION THDM_taumumumu
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: tau- -> mu- e- e+
  #define CAPABILITY taumuee
  START_CAPABILITY

    #define FUNCTION RHN_taumuee
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(tau_minus_decay_rates, DecayTable::Entry)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_Higgs)
    #undef FUNCTION

    //Function for gTHDM
    #define FUNCTION THDM_taumuee
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: tau- -> e- e- mu+
  #define CAPABILITY taueemu
  START_CAPABILITY

    #define FUNCTION RHN_taueemu
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(tau_minus_decay_rates, DecayTable::Entry)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_Higgs)
    #undef FUNCTION

    //Function for gTHDM
    #define FUNCTION THDM_taueemu
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: tau- -> e- mu- mu+
  #define CAPABILITY tauemumu
  START_CAPABILITY

    #define FUNCTION RHN_tauemumu
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(tau_minus_decay_rates, DecayTable::Entry)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_Higgs)
    #undef FUNCTION

    //Function for gTHDM
    #define FUNCTION THDM_tauemumu
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: tau- -> mu- mu- e+
  #define CAPABILITY taumumue
  START_CAPABILITY

    #define FUNCTION RHN_taumumue
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    DEPENDENCY(tau_minus_decay_rates, DecayTable::Entry)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_Higgs)
    #undef FUNCTION

    //Function for gTHDM
    #define FUNCTION THDM_taumumue
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  ///Observable: mu - e (Ti)
  #define CAPABILITY mueTi
  START_CAPABILITY
    #define FUNCTION RHN_mueTi
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_Higgs)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: mu - e (Au)
  #define CAPABILITY mueAu
  START_CAPABILITY
    #define FUNCTION RHN_mueAu
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_Higgs)
    #undef FUNCTION
  #undef CAPABILITY


  ///Observable: mu - e (Pb)
  #define CAPABILITY muePb
  START_CAPABILITY
    #define FUNCTION RHN_muePb
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Vnu, Eigen::Matrix3cd)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    DEPENDENCY(m_nu, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(RightHandedNeutrinos, StandardModel_Higgs)
    #undef FUNCTION
  #undef CAPABILITY


  //###############################################
  // Likelihoods
  //###############################################


  ///h->tau mu likelihood
  #define CAPABILITY h2taumu_LogLikelihood
  START_CAPABILITY
    #define FUNCTION h2taumu_likelihood
    START_FUNCTION(double)
    DEPENDENCY(h2taumu, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///t->ch likelihood
  #define CAPABILITY t2ch_LogLikelihood
  START_CAPABILITY
    #define FUNCTION t2ch_likelihood
    START_FUNCTION(double)
    DEPENDENCY(t2ch, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///B meson mass aysmmetry likelihood
  #define CAPABILITY deltaMB_LogLikelihood
  START_CAPABILITY
    #define FUNCTION deltaMB_likelihood
    START_FUNCTION(double)
    DEPENDENCY(prediction_DeltaMs, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///B_d meson mass aysmmetry likelihood
  #define CAPABILITY deltaMBd_LogLikelihood
  START_CAPABILITY
    #define FUNCTION deltaMBd_likelihood
    START_FUNCTION(double)
    DEPENDENCY(DeltaMd, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///B-Dstartaunu distributions likelihood [Normalized differential partial width]
  #define CAPABILITY BDstartaunu_LogLikelihood
  START_CAPABILITY
    #define FUNCTION BDstartaunu_likelihood
    START_FUNCTION(double)
    DEPENDENCY(BDstartaunu_M, FlavBit::predictions_measurements_covariances)
    #undef FUNCTION
  #undef CAPABILITY


  ///B-Dtanu distributions likelihood [Normalized differential partial width]
  #define CAPABILITY BDtaunu_LogLikelihood
  START_CAPABILITY
    #define FUNCTION BDtaunu_likelihood
    START_FUNCTION(double)
    DEPENDENCY(BDtaunu_M, FlavBit::predictions_measurements_covariances)
    #undef FUNCTION
  #undef CAPABILITY


  ///mu-e universality likelihood
  #define CAPABILITY gmu_ge_LogLikelihood
  START_CAPABILITY
    #define FUNCTION gmu_ge_likelihood
    START_FUNCTION(double)
    DEPENDENCY(gmu_ge, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///FLDstar likelihood
  #define CAPABILITY FLDstar_LogLikelihood
  START_CAPABILITY
    #define FUNCTION FLDstar_likelihood
    START_FUNCTION(double)
    DEPENDENCY(FLDstar, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///Bc lifetime likelihood
  #define CAPABILITY Bc_lifetime_LogLikelihood
  START_CAPABILITY
    #define FUNCTION Bc_lifetime_likelihood
    START_FUNCTION(double)
    DEPENDENCY(Bc_lifetime, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///Bs2llp likelihood
  #define CAPABILITY Bs2llp_LogLikelihood
  START_CAPABILITY
    #define FUNCTION Bs2llp_likelihood
    START_FUNCTION(double)
    DEPENDENCY(Bs2mutau, double)
    DEPENDENCY(Bs2tautau, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///B2Kllp likelihood
  #define CAPABILITY B2Kllp_LogLikelihood
  START_CAPABILITY
    #define FUNCTION B2Kllp_likelihood
    START_FUNCTION(double)
    DEPENDENCY(B2Kmue, double)
    DEPENDENCY(B2Ktaumu, double)
    DEPENDENCY(B2Ktautau, double)
    //DEPENDENCY(B2Ktautau, flav_prediction)
    #undef FUNCTION
  #undef CAPABILITY


  /// RKnunu and RKstarnunu likelihood
  #define CAPABILITY RK_RKstarnunu_LogLikelihood
  START_CAPABILITY
    #define FUNCTION RK_RKstarnunu_likelihood
    START_FUNCTION(double)
    DEPENDENCY(RKnunu, double)
    DEPENDENCY(RKstarnunu, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///Tree-level leptonic and semi-leptonic B & D decay likelihoods
  #define CAPABILITY SL_LogLikelihood
  START_CAPABILITY
    #define FUNCTION SL_likelihood
    START_FUNCTION(double)
    DEPENDENCY(SL_M, FlavBit::predictions_measurements_covariances)
    #undef FUNCTION
  #undef CAPABILITY


  ///l -> l gamma  likelihood
  #define CAPABILITY l2lgamma_LogLikelihood
  START_CAPABILITY
    #define FUNCTION l2lgamma_likelihood
    START_FUNCTION(double)
    DEPENDENCY(muegamma, double)
    DEPENDENCY(tauegamma, double)
    DEPENDENCY(taumugamma, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///l -> l l l likelihood
  #define CAPABILITY l2lll_LogLikelihood
  START_CAPABILITY
    #define FUNCTION l2lll_likelihood
    START_FUNCTION(double)
    DEPENDENCY(mueee, double)
    DEPENDENCY(taueee, double)
    DEPENDENCY(taumumumu, double)
    DEPENDENCY(taumuee, double)
    DEPENDENCY(taueemu, double)
    DEPENDENCY(tauemumu, double)
    DEPENDENCY(taumumue, double)
    #undef FUNCTION
  #undef CAPABILITY


  ///mu - e conversion likelihood
  #define CAPABILITY mu2e_LogLikelihood
  START_CAPABILITY
    #define FUNCTION mu2e_likelihood
    START_FUNCTION(double)
    DEPENDENCY(mueTi, double)
    DEPENDENCY(mueAu, double)
    DEPENDENCY(muePb, double)
    #undef FUNCTION
  #undef CAPABILITY


  /* TODO: This does not work currently in this form as it is not implemented in SuperIso
  ///HEPLike LogLikelihood B -> tau nu
  #define CAPABILITY B2taunu_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_B2taunu_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2taunu, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY*/


  ///HEPLike LogLikelihood RD RDstar
  #define CAPABILITY RDRDstar_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_RDRDstar_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(RD, double)
    DEPENDENCY(RDstar, double)
    //TODO: Switch dependency as soon as RD and RDstar can be extracted from a future version of SuperIso using the check_nameobs function.
    //DEPENDENCY(prediction_RDRDstar, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood b -> s gamma
  #define CAPABILITY b2sgamma_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_b2sgamma_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(prediction_b2sgamma, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> K* gamma
  #define CAPABILITY B2Kstargamma_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_B2Kstargamma_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2Kstargamma, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> mumu
  #define CAPABILITY B2mumu_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2mumu_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2mumu, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> mu mu
  #define CAPABILITY B2mumu_LogLikelihood_CMS
  START_CAPABILITY
    #define FUNCTION HEPLike_B2mumu_LogLikelihood_CMS
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2mumu, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> mu mu
  #define CAPABILITY B2mumu_LogLikelihood_Atlas
  START_CAPABILITY
    #define FUNCTION HEPLike_B2mumu_LogLikelihood_Atlas
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2mumu, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY

  ///HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_LogLikelihood_Atlas
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_LogLikelihood_Atlas
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_Atlas, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_LogLikelihood_CMS
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_LogLikelihood_CMS
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_CMS, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_LogLikelihood_Belle
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_LogLikelihood_Belle
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_Belle, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> K* l l Angular
  #define CAPABILITY B2KstarellellAng_LogLikelihood_Belle
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarellellAng_LogLikelihood_Belle
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_Belle, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// TODO: If superseded by 2020, need to keep it?
  ///HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_LHCb, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_LogLikelihood_LHCb_2020
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_LogLikelihood_LHCb_2020
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_LHCb, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B_u -> K* mu mu Angular
  #define CAPABILITY Bu2KstarmumuAng_LogLikelihood_LHCb_2020
  START_CAPABILITY
    #define FUNCTION HEPLike_Bu2KstarmumuAng_LogLikelihood_LHCb_2020
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_LHCb, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> K* mu mu Angular CP assymetry
  #define CAPABILITY B2KstarmumuAng_CPAssym_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_CPAssym_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_LHCb, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> K* e e angular low q2
  #define CAPABILITY  B2KstareeAng_Lowq2_LogLikelihood_LHCb_2020
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstareeAng_Lowq2_LogLikelihood_LHCb_2020
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstareeAng_Lowq2_LHCb, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> K* mu mu BR
  #define CAPABILITY B2KstarmumuBr_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuBr_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuBr, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood B -> K mu mu BR
  #define CAPABILITY B2KmumuBr_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KmumuBr_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KmumuBr, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  ///HEPLike LogLikelihood Bs -> Phi mu mu BR
  #define CAPABILITY Bs2phimumuBr_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_Bs2phimumuBr_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(prediction_Bs2phimumuBr, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


  // TODO: these should be re-activated once RK and RKstar can be extracted from a future version of SuperIso using the check_nameobs function.
  ///HEPLike LogLikelihood for RK
  #define CAPABILITY RK_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_RK_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(RK, double)
    //DEPENDENCY(prediction_RK_LHCb, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY

  // TODO: these should be re-activated once RK and RKstar can be extracted from a future version of SuperIso using the check_nameobs function.
  ///HEPLike LogLikelihood for RKstar
  #define CAPABILITY RKstar_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_RKstar_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(RKstar_0045_11, double)
    DEPENDENCY(RKstar_11_60, double)
    //DEPENDENCY(prediction_RKstar_LHCb, flav_binned_prediction)
    NEEDS_CLASSES_FROM(HepLike, default)
    #undef FUNCTION
  #undef CAPABILITY


#undef REFERENCE
#undef MODULE


#endif //defined(__FlavBit_rollcall_hpp__)
