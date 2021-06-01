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
///  \date 2019 Aug
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
///  \author Tomas Gonzalo
///  \date 2017 July
///
///  \author Cristian Sierra
///  \date 2020 June-December
///  \date 2021 Jan-May
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
///
///  \author Jihyun Bhom
///  \date 2019 July
///  \date 2019 Aug
///
///  \author Markus Prim
///  \date 2019 Aug
///
///  *********************************************

#ifndef __FlavBit_rollcall_hpp__
#define __FlavBit_rollcall_hpp__

#include "gambit/FlavBit/FlavBit_types.hpp"

#define MODULE FlavBit
START_MODULE

  #define CAPABILITY BDstarlnu_40_45
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_40_45
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDstarlnu_45_50
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_45_50
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDstarlnu_50_55
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_50_55
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDstarlnu_55_60
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_55_60
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDstarlnu_60_65
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_60_65
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDstarlnu_65_70
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_65_70
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDstarlnu_70_75
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_70_75
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDstarlnu_75_80
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_75_80
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDstarlnu_80_85
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_80_85
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDstarlnu_85_90
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_85_90
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDstarlnu_90_95
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_90_95
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDstarlnu_95_100
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_95_100
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDstarlnu_100_105
  START_CAPABILITY
    #define FUNCTION THDM_BDstarlnu_100_105
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  // B-Dstartanu distribution measurements
  #define CAPABILITY BDstartaunu_M
  START_CAPABILITY
    #define FUNCTION BDstartaunu_measurements
    START_FUNCTION(FlavBit::predictions_measurements_covariances)
    DEPENDENCY(BDstarlnu_40_45, double)
    DEPENDENCY(BDstarlnu_45_50, double)
    DEPENDENCY(BDstarlnu_50_55, double)
    DEPENDENCY(BDstarlnu_55_60, double)
    DEPENDENCY(BDstarlnu_60_65, double)
    DEPENDENCY(BDstarlnu_65_70, double)
    DEPENDENCY(BDstarlnu_70_75, double)
    DEPENDENCY(BDstarlnu_75_80, double)
    DEPENDENCY(BDstarlnu_80_85, double)
    DEPENDENCY(BDstarlnu_85_90, double)
    DEPENDENCY(BDstarlnu_90_95, double)
    DEPENDENCY(BDstarlnu_95_100, double)
    DEPENDENCY(BDstarlnu_100_105, double)
    #undef FUNCTION
  #undef CAPABILITY
 
  // B-Dstartaunu distributions likelihood [Normalized differential partial width]
  #define CAPABILITY BDstartaunu_LL
  START_CAPABILITY
    #define FUNCTION BDstartaunu_likelihood
    START_FUNCTION(double)
    DEPENDENCY(BDstartaunu_M, FlavBit::predictions_measurements_covariances)
    #undef FUNCTION
  #undef CAPABILITY
 
 
  #define CAPABILITY BDlnu_40_45
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_40_45
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDlnu_45_50
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_45_50
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDlnu_50_55
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_50_55
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDlnu_55_60
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_55_60
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDlnu_60_65
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_60_65
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDlnu_65_70
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_65_70
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDlnu_70_75
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_70_75
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDlnu_75_80
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_75_80
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDlnu_80_85
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_80_85
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDlnu_85_90
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_85_90
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDlnu_90_95
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_90_95
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDlnu_95_100
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_95_100
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDlnu_100_105
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_100_105
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY BDlnu_105_110
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_105_110
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  #define CAPABILITY BDlnu_110_115
  START_CAPABILITY
    #define FUNCTION THDM_BDlnu_110_115
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

  // B-Dtanu distribution measurements
  #define CAPABILITY BDtaunu_M
  START_CAPABILITY
    #define FUNCTION BDtaunu_measurements
    START_FUNCTION(FlavBit::predictions_measurements_covariances)
    DEPENDENCY(BDlnu_40_45, double)
    DEPENDENCY(BDlnu_45_50, double)
    DEPENDENCY(BDlnu_50_55, double)
    DEPENDENCY(BDlnu_55_60, double)
    DEPENDENCY(BDlnu_60_65, double)
    DEPENDENCY(BDlnu_65_70, double)
    DEPENDENCY(BDlnu_70_75, double)
    DEPENDENCY(BDlnu_75_80, double)
    DEPENDENCY(BDlnu_80_85, double)
    DEPENDENCY(BDlnu_85_90, double)
    DEPENDENCY(BDlnu_90_95, double)
    DEPENDENCY(BDlnu_95_100, double)
    DEPENDENCY(BDlnu_100_105, double)
    DEPENDENCY(BDlnu_105_110, double)
    DEPENDENCY(BDlnu_110_115, double)
    #undef FUNCTION
  #undef CAPABILITY
 
  // B-Dtanu distributions likelihood [Normalized differential partial width]
  #define CAPABILITY BDtaunu_LL
  START_CAPABILITY
    #define FUNCTION BDtaunu_likelihood
    START_FUNCTION(double)
    DEPENDENCY(BDtaunu_M, FlavBit::predictions_measurements_covariances)
    #undef FUNCTION
  #undef CAPABILITY
  
//Observable: mu-e universality for the gTHDM from JHEP07(2013)044
  #define CAPABILITY gmu_ge
  START_CAPABILITY
    #define FUNCTION THDM_gmu_ge
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

//  mu-e universality likelihood
  #define CAPABILITY gmu_ge_lnL
  START_CAPABILITY
    #define FUNCTION gmu_ge_likelihood
    START_FUNCTION(double)
    DEPENDENCY(gmu_ge, double)
    #undef FUNCTION
  #undef CAPABILITY    

//Observable: FLDstar polarization
  #define CAPABILITY FLDstar
  START_CAPABILITY
    #define FUNCTION THDM_FLDstar
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY
  
//  FLDstar likelihood
  #define CAPABILITY FLDstar_lnL
  START_CAPABILITY
    #define FUNCTION FLDstar_likelihood
    START_FUNCTION(double)
    DEPENDENCY(FLDstar, double)
    #undef FUNCTION
  #undef CAPABILITY  

//Observable: Bc lifetime
  #define CAPABILITY Bc_lifetime
  START_CAPABILITY
    #define FUNCTION THDM_Bc_lifetime
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY
  
//  Bc lifetime likelihood
  #define CAPABILITY Bc_lifetime_lnL
  START_CAPABILITY
    #define FUNCTION Bc_lifetime_likelihood
    START_FUNCTION(double)
    DEPENDENCY(Bc_lifetime, double)
    #undef FUNCTION
  #undef CAPABILITY  

//Observable: Bs2mutau 
  #define CAPABILITY Bs2mutau
  START_CAPABILITY
    #define FUNCTION THDM_Bs2mutau
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

 //Observable: Bs2tautau 
  #define CAPABILITY Bs2tautau
  START_CAPABILITY
    #define FUNCTION THDM_Bs2tautau
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

// Bs2llp likelihood
  #define CAPABILITY Bs2llp_lnL
  START_CAPABILITY
    #define FUNCTION Bs2llp_likelihood
    START_FUNCTION(double)
    DEPENDENCY(Bs2mutau, double)
    DEPENDENCY(Bs2tautau, double)
    #undef FUNCTION
  #undef CAPABILITY

 //Observable: B2Kmue 
  #define CAPABILITY B2Kmue
  START_CAPABILITY
    #define FUNCTION THDM_B2Kmue
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

 //Observable: B2Ktaumu 
  #define CAPABILITY B2Ktaumu
  START_CAPABILITY
    #define FUNCTION THDM_B2Ktaumu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B+ ->K+ tau tau)
  #define CAPABILITY B2Ktautau
  START_CAPABILITY
    #define FUNCTION SI_BRBKtautau
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBKtautau_CONV, (libsuperiso), double, (const parameters*, double, double))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

// Bs2llp likelihood
  #define CAPABILITY B2Kllp_lnL
  START_CAPABILITY
    #define FUNCTION B2Kllp_likelihood
    START_FUNCTION(double)
    DEPENDENCY(B2Kmue, double)
    DEPENDENCY(B2Ktaumu, double)
    DEPENDENCY(B2Ktautau, double)
    #undef FUNCTION
  #undef CAPABILITY

//Observable: RKnunu
  #define CAPABILITY RKnunu
  START_CAPABILITY
    #define FUNCTION THDM_RKnunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

//Observable: RKstarnunu
  #define CAPABILITY RKstarnunu
  START_CAPABILITY
    #define FUNCTION THDM_RKstarnunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

//  RKnunu and RKstarnunu likelihood
  #define CAPABILITY RK_RKstarnunu_lnL
  START_CAPABILITY
    #define FUNCTION RK_RKstarnunu_likelihood
    START_FUNCTION(double)
    DEPENDENCY(RKnunu, double)
    DEPENDENCY(RKstarnunu, double)
    #undef FUNCTION
  #undef CAPABILITY 

 // ---------------------------------
 //  Wilson coefficients in the GTHDM
 // ---------------------------------

//C2 in the general THDM capability
  #define CAPABILITY DeltaC2
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC2
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

//C7 in the general THDM capability
  #define CAPABILITY DeltaC7
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC7
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY
  
//C8 in the general THDM capability
  #define CAPABILITY DeltaC8
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC8
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

//C9 in the general THDM capability
  #define CAPABILITY DeltaC9
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC9
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY   
  
//C10 in the general THDM capability
  #define CAPABILITY DeltaC10
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC10
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY
  
//C7' in the general THDM capability
  #define CAPABILITY DeltaC7_Prime
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC7_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY

//C8' in the general THDM capability
  #define CAPABILITY DeltaC8_Prime
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC8_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY
  
//C9' in the general THDM capability
  #define CAPABILITY DeltaC9_Prime
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC9_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY   
  
//C10' in the general THDM capability
  #define CAPABILITY DeltaC10_Prime
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC10_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY        
  
//CQ1 in the general THDM capability
  #define CAPABILITY DeltaCQ1
  START_CAPABILITY
    #define FUNCTION calculate_DeltaCQ1
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY        

//CQ2 in the general THDM capability
  #define CAPABILITY DeltaCQ2
  START_CAPABILITY
    #define FUNCTION calculate_DeltaCQ2
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY 
 
  //CQ1_Prime in the general THDM capability
  #define CAPABILITY DeltaCQ1_Prime
  START_CAPABILITY
    #define FUNCTION calculate_DeltaCQ1_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY        

  //CQ2_Prime in the general THDM capability
  #define CAPABILITY DeltaCQ2_Prime
  START_CAPABILITY
    #define FUNCTION calculate_DeltaCQ2_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  

// WCs for tautau processes

  #define CAPABILITY DeltaC9_tautau
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC9_tautau
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY   
  
  #define CAPABILITY DeltaC10_tautau
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC10_tautau
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY
  
  #define CAPABILITY DeltaC9_tautau_Prime
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC9_tautau_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY   
  
//C10' in the general THDM capability
  #define CAPABILITY DeltaC10_tautau_Prime
  START_CAPABILITY
    #define FUNCTION calculate_DeltaC10_tautau_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY        
  
//CQ1 in the general THDM capability
  #define CAPABILITY DeltaCQ1_tautau
  START_CAPABILITY
    #define FUNCTION calculate_DeltaCQ1_tautau
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY        

//CQ2 in the general THDM capability
  #define CAPABILITY DeltaCQ2_tautau
  START_CAPABILITY
    #define FUNCTION calculate_DeltaCQ2_tautau
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY 

  //CQ1_Prime in the general THDM capability
  #define CAPABILITY DeltaCQ1_tautau_Prime
  START_CAPABILITY
    #define FUNCTION calculate_DeltaCQ1_tautau_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY        

  //CQ2_Prime in the general THDM capability
  #define CAPABILITY DeltaCQ2_tautau_Prime
  START_CAPABILITY
    #define FUNCTION calculate_DeltaCQ2_tautau_Prime
    START_FUNCTION(std::complex<double>)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
  #undef CAPABILITY  


// -------------------------------
//    End of WCs in the GTHDM
// -------------------------------
  
  // Initialisation capability (fill the SuperIso structure)
  #define CAPABILITY SuperIso_modelinfo
  START_CAPABILITY
    #define FUNCTION SI_fill
    START_FUNCTION(parameters)
    ALLOW_MODELS(THDM, THDMatQ)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, WC, WC_LR, WC_LUV)
    BACKEND_REQ(Init_param, (libsuperiso), void, (parameters*))
    BACKEND_REQ(slha_adjust, (libsuperiso), void, (parameters*))
    // TODO: Why do you need mcmc from the pole mass, if mcmc is given in sminputs?
    BACKEND_REQ(mcmc_from_pole, (libsuperiso), double, (double, int, parameters*))
    BACKEND_REQ(mb_1S, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    DEPENDENCY(W_plus_decay_rates, DecayTable::Entry)
    DEPENDENCY(Z_decay_rates, DecayTable::Entry)
    MODEL_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ, MSSM63atMGUT)
    MODEL_CONDITIONAL_DEPENDENCY(SM_spectrum, Spectrum, WC, WC_LR, WC_LUV)
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

  // Initialisation capability (fill the SuperIso nuisance structure)
  #define CAPABILITY SuperIso_nuisance
  START_CAPABILITY
    #define FUNCTION SI_nuisance_fill
    START_FUNCTION(nuisance)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(set_nuisance, (libsuperiso), void, (nuisance*))
    BACKEND_REQ(set_nuisance_value_from_param, (libsuperiso), void, (nuisance*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Compute values of observable list
  #define CAPABILITY SuperIso_obs_values
  START_CAPABILITY
    #define FUNCTION SI_compute_obs_list
    START_FUNCTION(flav_observable_map)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    DEPENDENCY(SuperIso_nuisance, nuisance)
    BACKEND_REQ(get_predictions_nuisance, (libsuperiso), void, (char**, int*, double**, const parameters*, const nuisance*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
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
  #undef CAPABILITY

  #define CAPABILITY prediction_B2taunu
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
 //Function for the general THDM
   // #define FUNCTION THDM_Btaunu
   // START_FUNCTION(flav_prediction)
   // ALLOW_MODELS(THDM,THDMatQ)
   // DEPENDENCY(SMINPUTS,SMInputs)
   // DEPENDENCY(THDM_spectrum, Spectrum)
   // #undef FUNCTION
  #undef CAPABILITY

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




  #define CAPABILITY prediction_B2KstarmumuBr_0p1_0p98
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuBr_0p1_0p98
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

  #define CAPABILITY prediction_B2KstarmumuBr_1p1_2p5
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuBr_1p1_2p5
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

  #define CAPABILITY prediction_B2KstarmumuBr_2p5_4
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuBr_2p5_4
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

  #define CAPABILITY prediction_B2KstarmumuBr_4_6
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuBr_4_6
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

  #define CAPABILITY prediction_B2KstarmumuBr_6_8
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuBr_6_8
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

  #define CAPABILITY prediction_B2KstarmumuBr_15_19
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuBr_15_19
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

  #define CAPABILITY prediction_B2KmumuBr_0p05_2
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KmumuBr_0p05_2
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

  #define CAPABILITY prediction_B2KmumuBr_2_4p3
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KmumuBr_2_4p3
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

  #define CAPABILITY prediction_B2KmumuBr_4p3_8p68
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KmumuBr_4p3_8p68
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

  #define CAPABILITY prediction_B2KmumuBr_14p18_16
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KmumuBr_14p18_16
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

  #define CAPABILITY prediction_B2KmumuBr_16_18
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KmumuBr_16_18
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

  #define CAPABILITY prediction_B2KmumuBr_18_22
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KmumuBr_18_22
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


  #define CAPABILITY prediction_Bs2phimumuBr_1_6
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_Bs2phimumuBr_1_6
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

  #define CAPABILITY prediction_Bs2phimumuBr_15_19
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_Bs2phimumuBr_15_19
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

  #define CAPABILITY prediction_B2KstarmumuAng_0p1_2_Atlas
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_0p1_2_Atlas
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

  #define CAPABILITY prediction_B2KstarmumuAng_2_4_Atlas
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_2_4_Atlas
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

  #define CAPABILITY prediction_B2KstarmumuAng_4_8_Atlas
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_4_8_Atlas
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

  #define CAPABILITY prediction_B2KstarmumuAng_1_2_CMS
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_1_2_CMS
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

  #define CAPABILITY prediction_B2KstarmumuAng_2_4p3_CMS
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_2_4p3_CMS
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

  #define CAPABILITY prediction_B2KstarmumuAng_4p3_6_CMS
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_4p3_6_CMS
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

  #define CAPABILITY prediction_B2KstarmumuAng_6_8p68_CMS
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_6_8p68_CMS
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

  #define CAPABILITY prediction_B2KstarmumuAng_10p09_12p86_CMS
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_10p09_12p86_CMS
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

  #define CAPABILITY prediction_B2KstarmumuAng_14p18_16_CMS
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_14p18_16_CMS
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

  #define CAPABILITY prediction_B2KstarmumuAng_16_19_CMS
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_16_19_CMS
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

  #define CAPABILITY prediction_B2KstarmumuAng_0p1_4_Belle
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_0p1_4_Belle
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

  #define CAPABILITY prediction_B2KstarmumuAng_4_8_Belle
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_4_8_Belle
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

  #define CAPABILITY prediction_B2KstarmumuAng_10p9_12p9_Belle
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_10p9_12p9_Belle
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

  #define CAPABILITY prediction_B2KstarmumuAng_14p18_19_Belle
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_14p18_19_Belle
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

  #define CAPABILITY prediction_B2KstarmumuAng_0p1_0p98_LHCb
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_0p1_0p98_LHCb
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

  #define CAPABILITY prediction_B2KstarmumuAng_1p1_2p5_LHCb
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_1p1_2p5_LHCb
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

  #define CAPABILITY prediction_B2KstarmumuAng_2p5_4_LHCb
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_2p5_4_LHCb
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

  #define CAPABILITY prediction_B2KstarmumuAng_4_6_LHCb
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_4_6_LHCb
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

  #define CAPABILITY prediction_B2KstarmumuAng_6_8_LHCb
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_6_8_LHCb
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

  #define CAPABILITY prediction_B2KstarmumuAng_15_19_LHCb
  START_CAPABILITY
    #define FUNCTION SuperIso_prediction_B2KstarmumuAng_15_19_LHCb
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

  // Observable: BR(B -> Xs gamma)
  #define CAPABILITY bsgamma
  START_CAPABILITY

    #define FUNCTION SI_bsgamma
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(bsgamma_CONV, (libsuperiso), double,(const parameters*, double))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
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
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
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
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> mu+ mu-)
  #define CAPABILITY Bmumu
  START_CAPABILITY
    #define FUNCTION SI_Bmumu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Bll_CONV, (libsuperiso),  double, (const parameters*, int))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

   //  Observable: BR(B -> tau nu)
   #define CAPABILITY Btaunu
   START_CAPABILITY
    #define FUNCTION SI_Btaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Btaunu, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  //Function for the general THDM
    #define FUNCTION THDM_Btaunu
    START_FUNCTION(double)
    ALLOW_MODELS(THDM,THDMatQ)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    #undef FUNCTION
   #undef CAPABILITY

  // Observable: BR(B->D tau nu)/BR(B->D e nu)
  #define CAPABILITY RD
  START_CAPABILITY
    #define FUNCTION SI_RD
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

  // Observable: BR(B->D tau nu)/BR(B->D e nu)
  #define CAPABILITY RDstar
  START_CAPABILITY
    #define FUNCTION SI_RDstar
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

  // Observable: BR(K->mu nu)/BR(pi->mu nu)
  #define CAPABILITY Rmu
  START_CAPABILITY
    #define FUNCTION SI_Rmu
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

  // Observable: Rmu23
  #define CAPABILITY Rmu23
  START_CAPABILITY
    #define FUNCTION SI_Rmu23
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Rmu23, (libsuperiso), double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(Ds->tau nu)
  #define CAPABILITY Dstaunu
  START_CAPABILITY
    #define FUNCTION SI_Dstaunu
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

  // Observable: BR(Ds->mu nu)
  #define CAPABILITY Dsmunu
  START_CAPABILITY
    #define FUNCTION SI_Dsmunu
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

  // Observable: BR(D->mu nu)
  #define CAPABILITY Dmunu
  START_CAPABILITY
    #define FUNCTION SI_Dmunu
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

  // Observable: BR(B->D tau nu)
  #define CAPABILITY BDtaunu
  START_CAPABILITY
    #define FUNCTION SI_BDtaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B->D mu nu)
  #define CAPABILITY BDmunu
  START_CAPABILITY
    #define FUNCTION SI_BDmunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B->D* tau nu)
  #define CAPABILITY BDstartaunu
  START_CAPABILITY
    #define FUNCTION SI_BDstartaunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDstarlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B->D* mu nu)
  #define CAPABILITY BDstarmunu
  START_CAPABILITY
    #define FUNCTION SI_BDstarmunu
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBDstarlnu, (libsuperiso), double, (int, int, double,  double, double*, const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: Delta0(B -> K* gamma)
  #define CAPABILITY delta0
  START_CAPABILITY
    #define FUNCTION SI_delta0
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(delta0_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> Xs mu mu)_lowq2
  #define CAPABILITY BRBXsmumu_lowq2
  START_CAPABILITY
    #define FUNCTION SI_BRBXsmumu_lowq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBXsmumu_lowq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> Xs mu mu)_highq2
  #define CAPABILITY BRBXsmumu_highq2
  START_CAPABILITY
    #define FUNCTION SI_BRBXsmumu_highq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBXsmumu_highq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: AFB(B -> Xs mu mu)_lowq2
  #define CAPABILITY A_BXsmumu_lowq2
  START_CAPABILITY
    #define FUNCTION SI_A_BXsmumu_lowq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(A_BXsmumu_lowq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: AFB(B -> Xs mu mu)_highq2
  #define CAPABILITY A_BXsmumu_highq2
  START_CAPABILITY
    #define FUNCTION SI_A_BXsmumu_highq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(A_BXsmumu_highq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: zero of AFB(B -> Xs mu mu)
  #define CAPABILITY A_BXsmumu_zero
  START_CAPABILITY
    #define FUNCTION SI_A_BXsmumu_zero
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(A_BXsmumu_zero_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: BR(B -> Xs tau tau)_highq2
  #define CAPABILITY BRBXstautau_highq2
  START_CAPABILITY
    #define FUNCTION SI_BRBXstautau_highq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(BRBXstautau_highq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: AFB(B -> Xs tau tau)_highq2
  #define CAPABILITY A_BXstautau_highq2
  START_CAPABILITY
    #define FUNCTION SI_A_BXstautau_highq2
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(A_BXstautau_highq2_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Helper macro to make the following declarations quicker
  #define KSTARMUMU_BINS                                                                                   \
    START_FUNCTION(Flav_KstarMuMu_obs)                                                                     \
    DEPENDENCY(SuperIso_modelinfo, parameters)                                                             \
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )                                                       \
    BACKEND_REQ(BKstarmumu_CONV, (libsuperiso), Flav_KstarMuMu_obs, (const parameters*, double, double))

  // Observable: BR(B -> K* mu mu) in q^2 bin from 0.1 GeV^2 to 0.98 GeV^2
  #define CAPABILITY BKstarmumu_0p1_0p98
    START_CAPABILITY
    #define FUNCTION SI_BKstarmumu_0p1_0p98
    KSTARMUMU_BINS
    #undef FUNCTION
  #undef CAPABILITY

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

  // Observable: BR(B -> K* mu mu) in q^2 bin from 15 GeV^2 to 19 GeV^2
  #define CAPABILITY BKstarmumu_15_19
  START_CAPABILITY
    #define FUNCTION SI_BKstarmumu_15_19
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
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: zero of A_I(B -> K* mu mu)
  #define CAPABILITY AI_BKstarmumu_zero
  START_CAPABILITY
    #define FUNCTION SI_AI_BKstarmumu_zero
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(SI_AI_BKstarmumu_zero_CONV, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

  // Helper macro to make the following declarations quicker
  #define RKSTAR_BINS                                                                                   \
    START_FUNCTION(double)                                                                     \
    DEPENDENCY(SuperIso_modelinfo, parameters)                                                             \
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )                                                       \
    BACKEND_REQ(RKstar_CONV, (libsuperiso), double, (const parameters*, double, double))

 // Observable: RK* in q^2 bin from 0.045 GeV^2 to 1.1 GeV^2
  #define CAPABILITY RKstar_0045_11
  START_CAPABILITY
    #define FUNCTION SI_RKstar_0045_11
    RKSTAR_BINS
    #undef FUNCTION

    // Function to calcualte RK* for RHN
    #define FUNCTION RHN_RKstar_0045_11
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(StandardModel_SLHA2,RightHandedNeutrinos)
    #undef FUNCTION

  #undef CAPABILITY

 // Observable: RK* in q^2 bin from 1.1 GeV^2 to 6 GeV^2
  #define CAPABILITY RKstar_11_60
  START_CAPABILITY
    #define FUNCTION SI_RKstar_11_60
    RKSTAR_BINS
    #undef FUNCTION

    // Function to calculate RK* for RHN
    #define FUNCTION RHN_RKstar_11_60
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(StandardModel_SLHA2,RightHandedNeutrinos)
    #undef FUNCTION

  #undef CAPABILITY

  // Helper macro to make the following declarations quicker
  #define RK_BINS                                                                                   \
    START_FUNCTION(double)                                                                     \
    DEPENDENCY(SuperIso_modelinfo, parameters)                                                             \
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )                                                       \
    BACKEND_REQ(RK_CONV, (libsuperiso), double, (const parameters*, double, double))

 // Observable: RK in q^2 bin from 1 GeV^2 to 6 GeV^2
  #define CAPABILITY RK
  START_CAPABILITY
    #define FUNCTION SI_RK
    RK_BINS
    #undef FUNCTION

    // Function to calculate RK for RHN
    #define FUNCTION RHN_RK
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS, SMInputs)
    DEPENDENCY(SeesawI_Theta, Eigen::Matrix3cd)
    ALLOW_JOINT_MODEL(StandardModel_SLHA2,RightHandedNeutrinos)
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
    //
    #define FUNCTION SI_Delta_MBs
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Delta_MBs, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
    //
    #define FUNCTION THDM_Delta_MBs
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: B_d mass difference
  #define CAPABILITY DeltaMd
  START_CAPABILITY
    #define FUNCTION SI_Delta_MBd
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_modelinfo, parameters)
    BACKEND_REQ(Delta_MB, (libsuperiso),  double, (const parameters*))
    BACKEND_OPTION( (SuperIso, 4.1), (libsuperiso) )
    #undef FUNCTION
  #undef CAPABILITY

 // Observable: BR(h->bs)
  #define CAPABILITY h2bs
  START_CAPABILITY
    #define FUNCTION THDM_h2bs
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

 // Observable: BR(t->ch)
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
  // Lepton Flavour Violation
  //###############################################

  // Observable: BR(h->tau mu)
  #define CAPABILITY h2taumu
  START_CAPABILITY
    #define FUNCTION THDM_h2taumu
    START_FUNCTION(double)
    DEPENDENCY(SMINPUTS,SMInputs)
    DEPENDENCY(THDM_spectrum, Spectrum)
    ALLOW_MODELS(THDM,THDMatQ)
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: mu -> e gamma
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

  // Observable: tau -> e gamma
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

  // Observable: tau -> mu gamma
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

  // Observable: mu- -> e- e- e+
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

  // Observable: tau- -> e- e- e+
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

   // Observable: tau- -> mu- mu- mu+
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

  // Observable: tau- -> mu- e- e+
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

  // Observable: tau- -> e- e- mu+
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

  // Observable: tau- -> e- mu- mu+
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

  // Observable: tau- -> mu- mu- e+
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

  // Observable: mu - e (Ti)
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

  // Observable: mu - e (Au)
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

  // Observable: mu - e (Pb)
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
  //  Likelihoods
  //###############################################

  // h->tau mu likelihood
  #define CAPABILITY h2taumu_LL
  START_CAPABILITY
    #define FUNCTION h2taumu_likelihood
    START_FUNCTION(double)
    DEPENDENCY(h2taumu, double)
    #undef FUNCTION
  #undef CAPABILITY

  // t->ch likelihood
  #define CAPABILITY t2ch_LL
  START_CAPABILITY
    #define FUNCTION t2ch_likelihood
    START_FUNCTION(double)
    DEPENDENCY(t2ch, double)
    #undef FUNCTION
  #undef CAPABILITY

  // B meson mass aysmmetry likelihood
  #define CAPABILITY deltaMB_LL
  START_CAPABILITY
    #define FUNCTION deltaMB_likelihood
    START_FUNCTION(double)
    DEPENDENCY(DeltaMs, double)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY deltaMBd_LL
  START_CAPABILITY
    #define FUNCTION deltaMBd_likelihood
    START_FUNCTION(double)
    DEPENDENCY(DeltaMd, double)
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

  // Electroweak penguin measurements
  #define CAPABILITY b2sll_BR_M
  START_CAPABILITY
    #define FUNCTION b2sll_BR_measurement
    START_FUNCTION(std::vector<double>)
    DEPENDENCY(BKstarmumu_11_25, Flav_KstarMuMu_obs)
    DEPENDENCY(BKstarmumu_25_40, Flav_KstarMuMu_obs)
    DEPENDENCY(BKstarmumu_40_60, Flav_KstarMuMu_obs)
    DEPENDENCY(BKstarmumu_60_80, Flav_KstarMuMu_obs)
    DEPENDENCY(BKstarmumu_15_17, Flav_KstarMuMu_obs)
    DEPENDENCY(BKstarmumu_17_19, Flav_KstarMuMu_obs)
    #undef FUNCTION
  #undef CAPABILITY

  // Electroweak penguin likelihood [Angular quantities]
  #define CAPABILITY b2sll_LL
  START_CAPABILITY
    #define FUNCTION b2sll_likelihood
    START_FUNCTION(double)
    DEPENDENCY(b2sll_M, FlavBit::predictions_measurements_covariances)
    #undef FUNCTION
  #undef CAPABILITY
  
  // Electroweak penguin likelihood [Branching]
  #define CAPABILITY b2sll_BR_LL
  START_CAPABILITY
    #define FUNCTION b2sll_BR_likelihood
    START_FUNCTION(double)
    DEPENDENCY(b2sll_BR_M, std::vector<double>)
    #undef FUNCTION
  #undef CAPABILITY

  // Electroweak penguin likelihood [isospin symmetry]
  #define CAPABILITY b2sll_AI_LL
  START_CAPABILITY
    #define FUNCTION BKstarmumu_AI_ll
    START_FUNCTION(double)
    DEPENDENCY(AI_BKstarmumu, double)
    #undef FUNCTION
  #undef CAPABILITY

  // Electroweak penguin likelihood [zero of isospin symmetry]
  #define CAPABILITY b2sll_AI_zero_LL
  START_CAPABILITY
    #define FUNCTION BKstarmumu_AI_zero_ll
    START_FUNCTION(double)
    DEPENDENCY(AI_BKstarmumu_zero, double)
    #undef FUNCTION
  #undef CAPABILITY

  // delta0 CP isospin asymmetry
  #define CAPABILITY delta0_LL
  START_CAPABILITY
    #define FUNCTION delta0_ll
    START_FUNCTION(double)
    DEPENDENCY(delta0, double)
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
    //DEPENDENCY(BDmunu, double)
    //DEPENDENCY(BDstarmunu, double)
    DEPENDENCY(Btaunu, double)
    DEPENDENCY(Rmu, double)
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

  // l -> l gamma  likelihood
  #define CAPABILITY l2lgamma_lnL
  START_CAPABILITY
    #define FUNCTION l2lgamma_likelihood
    START_FUNCTION(double)
    DEPENDENCY(muegamma, double)
    DEPENDENCY(tauegamma, double)
    DEPENDENCY(taumugamma, double)
    #undef FUNCTION
  #undef CAPABILITY

  // l -> l l l likelihood
  #define CAPABILITY l2lll_lnL
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

  // mu - e conversion likelihood
  #define CAPABILITY mu2e_lnL
  START_CAPABILITY
    #define FUNCTION mu2e_likelihood
    START_FUNCTION(double)
    DEPENDENCY(mueTi, double)
    DEPENDENCY(mueAu, double)
    DEPENDENCY(muePb, double)
    #undef FUNCTION
  #undef CAPABILITY

  // Observable: Test Flavio
  #define CAPABILITY Flavio_test
  START_CAPABILITY
    #define FUNCTION Flavio_test
    START_FUNCTION(double)
    ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, WC)
    BACKEND_REQ(sm_prediction_CONV, (needs_flavio), double, (std::string) )
    BACKEND_OPTION( (Flavio, 0.30.0), (needs_flavio) )
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> tau nu
  #define CAPABILITY B2taunu_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_B2taunu_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2taunu, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood RD RDstar
  #define CAPABILITY RDRDstar_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_RDRDstar_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(RD, double)
    DEPENDENCY(RDstar, double)
    // TODO: Switch dependency as soon as SuperIso is ready for the "new" way.
    // DEPENDENCY(prediction_RDRDstar, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood b -> s gamma
  #define CAPABILITY b2sgamma_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_b2sgamma_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(prediction_b2sgamma, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> K* gamma
  #define CAPABILITY B2Kstargamma_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_B2Kstargamma_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2Kstargamma, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> mumu
  #define CAPABILITY B2mumu_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2mumu_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2mumu, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> mu mu
  #define CAPABILITY B2mumu_LogLikelihood_CMS
  START_CAPABILITY
    #define FUNCTION HEPLike_B2mumu_LogLikelihood_CMS
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2mumu, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> mu mu
  #define CAPABILITY B2mumu_LogLikelihood_Atlas
  START_CAPABILITY
    #define FUNCTION HEPLike_B2mumu_LogLikelihood_Atlas
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2mumu, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_LogLikelihood_Atlas
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_LogLikelihood_Atlas
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_0p1_2_Atlas, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_2_4_Atlas, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_4_8_Atlas, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> K* mu mu Angular without the first q2 bin
  #define CAPABILITY B2KstarmumuAng_NoLowq2_LogLikelihood_Atlas
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_Atlas
    START_FUNCTION(double)
     DEPENDENCY(prediction_B2KstarmumuAng_2_4_Atlas, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_4_8_Atlas, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY
  
  /// HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_LogLikelihood_CMS
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_LogLikelihood_CMS
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_1_2_CMS, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_2_4p3_CMS, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_4p3_6_CMS, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_6_8p68_CMS, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_10p09_12p86_CMS, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_14p18_16_CMS, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_16_19_CMS, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_LogLikelihood_Belle
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_LogLikelihood_Belle
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_0p1_4_Belle, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_4_8_Belle, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_10p9_12p9_Belle, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_14p18_19_Belle, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY


  /// HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_NoLowq2_LogLikelihood_Belle
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_Belle
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_4_8_Belle, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_10p9_12p9_Belle, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_14p18_19_Belle, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY
  
  /// HEPLike LogLikelihood B -> K* mu mu Angular without the first q2 bin
  #define CAPABILITY B2KstarmumuAng_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_0p1_0p98_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_1p1_2p5_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_2p5_4_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_4_6_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_6_8_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_15_19_LHCb, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_LogLikelihood_LHCb_2020
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_LogLikelihood_LHCb_2020
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_0p1_0p98_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_1p1_2p5_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_2p5_4_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_4_6_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_6_8_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_15_19_LHCb, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> K* mu mu Angular
  #define CAPABILITY B2KstarmumuAng_NoLowq2_LogLikelihood_LHCb_2020
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_LHCb_2020
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_1p1_2p5_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_2p5_4_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_4_6_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_6_8_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_15_19_LHCb, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> K* mu mu Angular CP assymetry
  #define CAPABILITY B2KstarmumuAng_CPAssym_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuAng_CPAssym_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuAng_0p1_0p98_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_1p1_2p5_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_2p5_4_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_4_6_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_6_8_LHCb, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuAng_15_19_LHCb, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY



  /// HEPLike LogLikelihood B -> K* mu mu BR
  #define CAPABILITY B2KstarmumuBr_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuBr_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuBr_0p1_0p98, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuBr_1p1_2p5, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuBr_2p5_4, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuBr_4_6, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuBr_6_8, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuBr_15_19, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood B -> K* mu mu BR
  #define CAPABILITY B2KstarmumuBr_NoLowq2_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KstarmumuBr_NoLowq2_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KstarmumuBr_1p1_2p5, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuBr_2p5_4, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuBr_4_6, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuBr_6_8, flav_prediction)
    DEPENDENCY(prediction_B2KstarmumuBr_15_19, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY


  
  /// HEPLike LogLikelihood B -> K mu mu BR
  #define CAPABILITY B2KmumuBr_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_B2KmumuBr_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(prediction_B2KmumuBr_0p05_2, flav_prediction)
    DEPENDENCY(prediction_B2KmumuBr_2_4p3, flav_prediction)
    DEPENDENCY(prediction_B2KmumuBr_4p3_8p68, flav_prediction)
    DEPENDENCY(prediction_B2KmumuBr_14p18_16, flav_prediction)
    DEPENDENCY(prediction_B2KmumuBr_16_18, flav_prediction)
    DEPENDENCY(prediction_B2KmumuBr_18_22, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood Bs -> Phi mu mu BR
  #define CAPABILITY Bs2phimumuBr_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_Bs2phimumuBr_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(prediction_Bs2phimumuBr_1_6, flav_prediction)
    DEPENDENCY(prediction_Bs2phimumuBr_15_19, flav_prediction)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood for RK
  #define CAPABILITY RK_LogLikelihood
  START_CAPABILITY
    #define FUNCTION HEPLike_RK_LogLikelihood
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_obs_values, flav_observable_map)
    DEPENDENCY(SuperIso_theory_covariance, flav_covariance_map)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY

  /// HEPLike LogLikelihood for RKstar
  #define CAPABILITY RKstar_LogLikelihood_LHCb
  START_CAPABILITY
    #define FUNCTION HEPLike_RKstar_LogLikelihood_LHCb
    START_FUNCTION(double)
    DEPENDENCY(SuperIso_obs_values, flav_observable_map)
    DEPENDENCY(SuperIso_theory_covariance, flav_covariance_map)
    NEEDS_CLASSES_FROM(HepLike)
    #undef FUNCTION
  #undef CAPABILITY


#undef MODULE


#endif // defined(__FlavBit_rollcall_hpp__)
