//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for module FlavBit.
///
///  Compile-time registration of available
///  observables and likelihoods, as well as their
///  dependencies.
///
///  Add to this if you want to add an observable
///  or likelihood to this module.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Nazila Mahmoudi
///  \date 2013 Oct
///  \date 2014 Jun
///  \date 2014 Sep
///  \date 2015 Feb
///  \date 2016 Jul
///  \date 2018 Jan
///
///  \author Pat Scott
///  \date 2015 May
///  \date 2016 Aug
///  \date 2017 March
///
///  \author Marcin Chrzaszcz
///  \date 2015 May
///  \date 2016 Aug
///  \date 2016 Oct
///  \date 2018 Jan
///
///  *********************************************

#ifndef __FlavBit_rollcall_hpp__
#define __FlavBit_rollcall_hpp__

#include "gambit/FlavBit/FlavBit_types.hpp"


#define MODULE FlavBit
START_MODULE

  // Initialisation capability (fill the SuperIso structure)
  #define CAPABILITY SuperIso_modelinfo
  START_CAPABILITY
    #define FUNCTION SI_fill
    START_FUNCTION(parameters)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, WC)
    BACKEND_REQ(Init_param, (libsuperiso), void, (parameters*))
    BACKEND_REQ(slha_adjust, (libsuperiso), void, (parameters*))
    BACKEND_REQ(mb_1S, (libsuperiso),double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    DEPENDENCY(W_plus_decay_rates, DecayTable::Entry)
    DEPENDENCY(Z_decay_rates, DecayTable::Entry)
    MODEL_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(SM_spectrum, Spectrum, WC)
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> Xs gamma)
  #define CAPABILITY bsgamma
  START_CAPABILITY

    #define FUNCTION SI_bsgamma
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(bsgamma_CONV, (libsuperiso), double,(const parameters*, double))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION

    #define FUNCTION FH_bsgamma
    START_FUNCTION(double)
    DEPENDENCY(FH_FlavourObs, fh_FlavourObs)
    #undef FUNCTION

  #undef CAPABILITY

  // Observable: BR(Bs -> mu+ mu-)_untag
  #define CAPABILITY Bsmumu_untag
  START_CAPABILITY

    #define FUNCTION SI_Bsmumu_untag
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Bsll_untag_CONV, (libsuperiso),  double, (const parameters*, int))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION

    #define FUNCTION FH_Bsmumu
    START_FUNCTION(double)
    DEPENDENCY(FH_FlavourObs, fh_FlavourObs)
    #undef FUNCTION

  #undef CAPABILITY

  // Observable: BR(Bs -> e+ e-)_untag
  #define CAPABILITY Bsee_untag
  START_CAPABILITY
    #define FUNCTION SI_Bsee_untag
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Bsll_untag_CONV, (libsuperiso),  double, (const parameters*, int))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> mu+ mu-)
  #define CAPABILITY Bmumu
  START_CAPABILITY
    #define FUNCTION SI_Bmumu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Bll_CONV, (libsuperiso),  double, (const parameters*, int))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> tau nu)
  #define CAPABILITY Btaunu
  START_CAPABILITY
    #define FUNCTION SI_Btaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Btaunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B->D tau nu)/BR(B->D e nu)
  #define CAPABILITY RD
  START_CAPABILITY
    #define FUNCTION SI_RD
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BDtaunu_BDenu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B->D tau nu)/BR(B->D e nu)
  #define CAPABILITY RDstar
  START_CAPABILITY
    #define FUNCTION SI_RDstar
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BDstartaunu_BDstarenu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(K->mu nu)/BR(pi->mu nu)
  #define CAPABILITY Rmu
  START_CAPABILITY
    #define FUNCTION SI_Rmu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Kmunu_pimunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: Rmu23
  #define CAPABILITY Rmu23
  START_CAPABILITY
    #define FUNCTION SI_Rmu23
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Rmu23, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(Ds->tau nu)
  #define CAPABILITY Dstaunu
  START_CAPABILITY
    #define FUNCTION SI_Dstaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Dstaunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(Ds->mu nu)
  #define CAPABILITY Dsmunu
  START_CAPABILITY
    #define FUNCTION SI_Dsmunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Dsmunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(D->mu nu)
  #define CAPABILITY Dmunu
  START_CAPABILITY
    #define FUNCTION SI_Dmunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Dmunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B->D tau nu)
  #define CAPABILITY BDtaunu
  START_CAPABILITY
    #define FUNCTION SI_BDtaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B->D mu nu)
  #define CAPABILITY BDmunu
  START_CAPABILITY
    #define FUNCTION SI_BDmunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B->D* tau nu)
  #define CAPABILITY BDstartaunu
  START_CAPABILITY
    #define FUNCTION SI_BDstartaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDstarlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B->D* mu nu)
  #define CAPABILITY BDstarmunu
  START_CAPABILITY
    #define FUNCTION SI_BDstarmunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDstarlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: Delta0(B -> K* gamma)
  #define CAPABILITY delta0
  START_CAPABILITY
    #define FUNCTION SI_delta0
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(delta0_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> Xs mu mu)_lowq2
  #define CAPABILITY BRBXsmumu_lowq2
  START_CAPABILITY
    #define FUNCTION SI_BRBXsmumu_lowq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBXsmumu_lowq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> Xs mu mu)_highq2
  #define CAPABILITY BRBXsmumu_highq2
  START_CAPABILITY
    #define FUNCTION SI_BRBXsmumu_highq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBXsmumu_highq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: AFB(B -> Xs mu mu)_lowq2
  #define CAPABILITY A_BXsmumu_lowq2
  START_CAPABILITY
    #define FUNCTION SI_A_BXsmumu_lowq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(A_BXsmumu_lowq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: AFB(B -> Xs mu mu)_highq2
  #define CAPABILITY A_BXsmumu_highq2
  START_CAPABILITY
    #define FUNCTION SI_A_BXsmumu_highq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(A_BXsmumu_highq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: zero of AFB(B -> Xs mu mu)
  #define CAPABILITY A_BXsmumu_zero
  START_CAPABILITY
    #define FUNCTION SI_A_BXsmumu_zero
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(A_BXsmumu_zero_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> Xs tau tau)_highq2
  #define CAPABILITY BRBXstautau_highq2
  START_CAPABILITY
    #define FUNCTION SI_BRBXstautau_highq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBXstautau_highq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: AFB(B -> Xs tau tau)_highq2
  #define CAPABILITY A_BXstautau_highq2
  START_CAPABILITY
    #define FUNCTION SI_A_BXstautau_highq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(A_BXstautau_highq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Helper macro to make the following declarations quicker
  #define KSTARMUMU_BINS                                                                                   \
    START_FUNCTION(Flav_KstarMuMu_obs)                                                                     \
    DEPENDENCY(SuperIso_modelinfo, parameters)                                                             \
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )                                                       \
    BACKEND_REQ(BKstarmumu_CONV, (libsuperiso), Flav_KstarMuMu_obs, (const parameters*, double, double))

  // Observable: BR(B -> K* mu mu) in q^2 bin from 1.1 GeV^2 to 2.5 GeV^2
  #define CAPABILITY BKstarmumu_11_25
  START_CAPABILITY
    #define FUNCTION SI_BKstarmumu_11_25
    KSTARMUMU_BINS
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> K* mu mu) in q^2 bin from 2.5 GeV^2 to 4 GeV^2
  #define CAPABILITY BKstarmumu_25_40
  START_CAPABILITY
    #define FUNCTION SI_BKstarmumu_25_40
    KSTARMUMU_BINS
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> K* mu mu) in q^2 bin from 4 GeV^2 to 6 GeV^2
  #define CAPABILITY BKstarmumu_40_60
  START_CAPABILITY
    #define FUNCTION SI_BKstarmumu_40_60
    KSTARMUMU_BINS
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> K* mu mu) in q^2 bin from 6 GeV^2 to 8 GeV^2
  #define CAPABILITY BKstarmumu_60_80
  START_CAPABILITY
    #define FUNCTION SI_BKstarmumu_60_80
    KSTARMUMU_BINS
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> K* mu mu) in q^2 bin from 15 GeV^2 to 17 GeV^2
  #define CAPABILITY BKstarmumu_15_17
  START_CAPABILITY
    #define FUNCTION SI_BKstarmumu_15_17
    KSTARMUMU_BINS
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> K* mu mu) in q^2 bin from 17 GeV^2 to 19 GeV^2
  #define CAPABILITY BKstarmumu_17_19
  START_CAPABILITY
    #define FUNCTION SI_BKstarmumu_17_19
    KSTARMUMU_BINS
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: A_I(B -> K* mu mu)
  #define CAPABILITY AI_BKstarmumu
  START_CAPABILITY
    #define FUNCTION SI_AI_BKstarmumu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(SI_AI_BKstarmumu_CONV, (libsuperiso),  double, (const parameters*))
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: zero of A_I(B -> K* mu mu)
  #define CAPABILITY AI_BKstarmumu_zero
  START_CAPABILITY
    #define FUNCTION SI_AI_BKstarmumu_zero
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(SI_AI_BKstarmumu_zero_CONV, (libsuperiso),  double, (const parameters*))
    #undef FUNCTION
  #undef CAPABILITY

  // Helper macro to make the following declarations quicker
  #define RKSTAR_BINS                                                                                   \
    START_FUNCTION(double)                                                                     \
    DEPENDENCY(SuperIso_modelinfo, parameters)                                                             \
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )                                                       \
    BACKEND_REQ(RKstar_CONV, (libsuperiso), double, (const parameters*, double, double))

 // Observable: RK* in q^2 bin from 0.045 GeV^2 to 1.1 GeV^2
  #define CAPABILITY RKstar_0045_11
  START_CAPABILITY
    #define FUNCTION SI_RKstar_0045_11
    RKSTAR_BINS
    #undef FUNCTION
  #undef CAPABILITY

 // Observable: RK* in q^2 bin from 1.1 GeV^2 to 6 GeV^2
  #define CAPABILITY RKstar_11_60
  START_CAPABILITY
    #define FUNCTION SI_RKstar_11_60
    RKSTAR_BINS
    #undef FUNCTION
  #undef CAPABILITY

  // Helper macro to make the following declarations quicker
  #define RK_BINS                                                                                   \
    START_FUNCTION(double)                                                                     \
    DEPENDENCY(SuperIso_modelinfo, parameters)                                                             \
    BACKEND_OPTION( (SuperIso, 3.6), (libsuperiso) )                                                       \
    BACKEND_REQ(RK_CONV, (libsuperiso), double, (const parameters*, double, double))

 // Observable: RK in q^2 bin from 1 GeV^2 to 6 GeV^2
  #define CAPABILITY RK
  START_CAPABILITY
    #define FUNCTION SI_RK
    RK_BINS
    #undef FUNCTION
  #undef CAPABILITY

  // All FeynHiggs flavour observables
  #define CAPABILITY FH_FlavourObs
  START_CAPABILITY
    #define FUNCTION FH_FlavourObs
    START_FUNCTION(fh_FlavourObs)
    BACKEND_REQ(FHFlavour, (libfeynhiggs), void, (int&,fh_real&,fh_real&,fh_real&,fh_real&,fh_real&,fh_real&))
    BACKEND_OPTION( (FeynHiggs), (libfeynhiggs) )
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: B_s mass difference
  #define CAPABILITY DeltaMs
  START_CAPABILITY
    #define FUNCTION FH_DeltaMs
    START_FUNCTION(double)
    DEPENDENCY(FH_FlavourObs, fh_FlavourObs)
    #undef FUNCTION
  #undef CAPABILITY


  //###############################################
  //  Likelihoods
  //###############################################

  // B meson mass aysmmetry likelihood
  #define CAPABILITY deltaMB_LL
  START_CAPABILITY
    #define FUNCTION deltaMB_likelihood
    START_FUNCTION(double)
    DEPENDENCY(DeltaMs, double)
    #undef FUNCTION
  #undef CAPABILITY

  // b -> s gamma likelihood
  #define CAPABILITY b2sgamma_LL
  START_CAPABILITY
    #define FUNCTION b2sgamma_likelihood
    START_FUNCTION(double)
    DEPENDENCY(bsgamma, double)
    #undef FUNCTION
  #undef CAPABILITY

  // Electroweak penguin measurements
  #define CAPABILITY b2sll_M
  START_CAPABILITY
    #define FUNCTION b2sll_measurements
    START_FUNCTION(FlavBit::predictions_measurements_covariances)
    DEPENDENCY(BKstarmumu_11_25, Flav_KstarMuMu_obs)
    DEPENDENCY(BKstarmumu_25_40, Flav_KstarMuMu_obs)
    DEPENDENCY(BKstarmumu_40_60, Flav_KstarMuMu_obs)
    DEPENDENCY(BKstarmumu_60_80, Flav_KstarMuMu_obs)
    DEPENDENCY(BKstarmumu_15_17, Flav_KstarMuMu_obs)
    DEPENDENCY(BKstarmumu_17_19, Flav_KstarMuMu_obs)
    #undef FUNCTION
  #undef CAPABILITY

  // Electroweak penguin likelihood
  #define CAPABILITY b2sll_LL
  START_CAPABILITY
    #define FUNCTION b2sll_likelihood
    START_FUNCTION(double)
    DEPENDENCY(b2sll_M, FlavBit::predictions_measurements_covariances)
    #undef FUNCTION
  #undef CAPABILITY

  // Rare fully leptonic B decay measurements
  #define CAPABILITY b2ll_M
  START_CAPABILITY
    #define FUNCTION b2ll_measurements
    START_FUNCTION(FlavBit::predictions_measurements_covariances)
    DEPENDENCY(Bsmumu_untag, double)
    DEPENDENCY(Bmumu, double )
    #undef FUNCTION
  #undef CAPABILITY

  // Rare fully leptonic B decay likelihood
  #define CAPABILITY b2ll_LL
  START_CAPABILITY
    #define FUNCTION b2ll_likelihood
    START_FUNCTION(double)
    DEPENDENCY(b2ll_M, FlavBit::predictions_measurements_covariances)
    #undef FUNCTION
  #undef CAPABILITY

  // Tree-level leptonic and semi-leptonic B & D decay measurements
  #define CAPABILITY SL_M
  START_CAPABILITY
    #define FUNCTION SL_measurements
    START_FUNCTION(FlavBit::predictions_measurements_covariances)
    DEPENDENCY(RD, double)
    DEPENDENCY(RDstar, double)
    DEPENDENCY(BDmunu, double)
    DEPENDENCY(BDstarmunu, double)
    DEPENDENCY(Btaunu, double)
    DEPENDENCY(Dstaunu, double)
    DEPENDENCY(Dsmunu, double)
    DEPENDENCY(Dmunu, double)
    #undef FUNCTION
  #undef CAPABILITY

  // Tree-level leptonic and semi-leptonic B & D decay likelihoods
  #define CAPABILITY SL_LL
  START_CAPABILITY
    #define FUNCTION SL_likelihood
    START_FUNCTION(double)
    DEPENDENCY(SL_M, FlavBit::predictions_measurements_covariances)
    #undef FUNCTION
  #undef CAPABILITY
   
  // Tree-level leptonic and semi-leptonic B & D decay measurements
  #define CAPABILITY LUV_M
  START_CAPABILITY
    #define FUNCTION LUV_measurements
    START_FUNCTION(FlavBit::predictions_measurements_covariances)
    DEPENDENCY(RK, double)
    DEPENDENCY(RKstar_0045_11, double)
    DEPENDENCY(RKstar_11_60, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY LUV_LL
  START_CAPABILITY
    #define FUNCTION LUV_likelihood
    START_FUNCTION(double)
    DEPENDENCY(LUV_M, FlavBit::predictions_measurements_covariances)
    #undef FUNCTION
  #undef CAPABILITY

  
   

#undef MODULE


#endif // defined(__FlavBit_rollcall_hpp__)
