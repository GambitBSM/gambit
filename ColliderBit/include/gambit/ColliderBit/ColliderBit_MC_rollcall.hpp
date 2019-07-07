//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for ColliderBit module.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  \author Aldo Saavedra
///
///  \author Christopher Rogan
///          (christophersrogan@gmail.com)
///  \date 2015 Apr
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///  \date 2018 Jan
///  \date 2019 Jan, Feb
///
///  \author Andy Buckley
///          (andy.buckley@cern.ch)
///  \date 2017 Jun
///
///  *********************************************

#pragma once

#define MODULE ColliderBit

  /// Execute the main Monte Carlo event loop.
  #define CAPABILITY RunMC
  START_CAPABILITY
    #define FUNCTION operateLHCLoop
    START_FUNCTION(MCLoopInfo, CAN_MANAGE_LOOPS)
    #undef FUNCTION
  #undef CAPABILITY

  /// Cross-section calculators
  /// @{
  #define CAPABILITY CrossSection
  START_CAPABILITY

    #define FUNCTION getMCxsec
    START_FUNCTION(xsec)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(HardScatteringSim, const BaseCollider*)
    #undef FUNCTION

    #define FUNCTION getNLLFastxsec
    START_FUNCTION(xsec)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    #undef FUNCTION

  #undef CAPABILITY
  /// @}

  /// Lists of analyses to run
  /// @{
  #define CAPABILITY ATLASAnalysisContainer
  START_CAPABILITY
    #define FUNCTION getATLASAnalysisContainer
    START_FUNCTION(AnalysisContainer)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(CrossSection, xsec)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CMSAnalysisContainer
  START_CAPABILITY
    #define FUNCTION getCMSAnalysisContainer
    START_FUNCTION(AnalysisContainer)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(CrossSection, xsec)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IdentityAnalysisContainer
  START_CAPABILITY
    #define FUNCTION getIdentityAnalysisContainer
    START_FUNCTION(AnalysisContainer)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(CrossSection, xsec)
    #undef FUNCTION
  #undef CAPABILITY
  /// @}

  /// Run all analyses and fill vector of analysis results.
  /// @{
  #define CAPABILITY ATLASAnalysisNumbers
  START_CAPABILITY
    #define FUNCTION runATLASAnalyses
    START_FUNCTION(AnalysisDataPointers)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(ATLASSmearedEvent, HEPUtils::Event)
    DEPENDENCY(ATLASAnalysisContainer, AnalysisContainer)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CMSAnalysisNumbers
  START_CAPABILITY
    #define FUNCTION runCMSAnalyses
    START_FUNCTION(AnalysisDataPointers)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(CMSSmearedEvent, HEPUtils::Event)
    DEPENDENCY(CMSAnalysisContainer, AnalysisContainer)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IdentityAnalysisNumbers
  START_CAPABILITY
    #define FUNCTION runIdentityAnalyses
    START_FUNCTION(AnalysisDataPointers)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(CopiedEvent, HEPUtils::Event)
    DEPENDENCY(IdentityAnalysisContainer, AnalysisContainer)
    #undef FUNCTION
  #undef CAPABILITY
  /// @}

  /// Collect all the analysis numbers in one place
  #define CAPABILITY AllAnalysisNumbers
  START_CAPABILITY
    #define FUNCTION CollectAnalyses
    START_FUNCTION(AnalysisDataPointers)
    DEPENDENCY(ATLASAnalysisNumbers, AnalysisDataPointers)
    DEPENDENCY(CMSAnalysisNumbers, AnalysisDataPointers)
    DEPENDENCY(IdentityAnalysisNumbers, AnalysisDataPointers)
    #undef FUNCTION
  #undef CAPABILITY

  /// Extract the signal predictions and uncertainties for all analyses
  #define CAPABILITY LHC_signals
  START_CAPABILITY
    #define FUNCTION calc_LHC_signals
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(AllAnalysisNumbers, AnalysisDataPointers)
    #undef FUNCTION
  #undef CAPABILITY

  /// Calculate the log likelihood for each SR in each analysis using the analysis numbers
  #define CAPABILITY LHC_LogLikes
  START_CAPABILITY
    #define FUNCTION calc_LHC_LogLikes
    START_FUNCTION(map_str_AnalysisLogLikes)
    DEPENDENCY(AllAnalysisNumbers, AnalysisDataPointers)
    DEPENDENCY(RunMC, MCLoopInfo)
    BACKEND_REQ_FROM_GROUP(lnlike_marg_poisson, lnlike_marg_poisson_lognormal_error, (), double, (const int&, const double&, const double&, const double&) )
    BACKEND_REQ_FROM_GROUP(lnlike_marg_poisson, lnlike_marg_poisson_gaussian_error, (), double, (const int&, const double&, const double&, const double&) )
    BACKEND_GROUP(lnlike_marg_poisson)
    #undef FUNCTION
  #undef CAPABILITY

  /// Extract the log likelihood for each SR to a simple map_str_dbl
  #define CAPABILITY LHC_LogLike_per_SR
  START_CAPABILITY
    #define FUNCTION get_LHC_LogLike_per_SR
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(LHC_LogLikes, map_str_AnalysisLogLikes)
    #undef FUNCTION
  #undef CAPABILITY

  /// Extract the combined log likelihood for each analysis to a simple map_str_dbl
  #define CAPABILITY LHC_LogLike_per_analysis
  START_CAPABILITY
    #define FUNCTION get_LHC_LogLike_per_analysis
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(LHC_LogLikes, map_str_AnalysisLogLikes)
    #undef FUNCTION
  #undef CAPABILITY

  /// Extract the labels for the SRs used in the analysis loglikes
  #define CAPABILITY LHC_LogLike_SR_labels
  START_CAPABILITY
    #define FUNCTION get_LHC_LogLike_SR_labels
    START_FUNCTION(map_str_str)
    DEPENDENCY(LHC_LogLikes, map_str_AnalysisLogLikes)
    #undef FUNCTION
  #undef CAPABILITY

  /// Extract the indices for the SRs used in the analysis loglikes (alphabetical SR ordering)
  #define CAPABILITY LHC_LogLike_SR_indices
  START_CAPABILITY
    #define FUNCTION get_LHC_LogLike_SR_indices
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(LHC_LogLikes, map_str_AnalysisLogLikes)
    #undef FUNCTION
  #undef CAPABILITY

  /// Calculate the total LHC log likelihood
  #define CAPABILITY LHC_Combined_LogLike
  START_CAPABILITY
    #define FUNCTION calc_combined_LHC_LogLike
    START_FUNCTION(double)
    DEPENDENCY(LHC_LogLike_per_analysis, map_str_dbl)
    DEPENDENCY(RunMC, MCLoopInfo)
    #undef FUNCTION
  #undef CAPABILITY

  /// Output some info about the event loop
  #define CAPABILITY LHCEventLoopInfo
  START_CAPABILITY
    #define FUNCTION getLHCEventLoopInfo
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(RunMC, MCLoopInfo)
    #undef FUNCTION
  #undef CAPABILITY

  /// Dummy observable that creates a dependency on TestModel1D, which is used to satisfy the normal
  /// GAMBIT model requrements in a minimal way. This is useful in the case where we just want to test
  /// ColliderBit on a single point with Pythia's SLHA interface, but not use the ColliderBit standalone
  /// interface.
  #define CAPABILITY DummyColliderObservable
  START_CAPABILITY
    #define FUNCTION getDummyColliderObservable
      START_FUNCTION(double)
      ALLOW_MODELS(TestModel1D)
    #undef FUNCTION
  #undef CAPABILITY

  // All other functions are declared in additional headers in the ColliderBit/models directory.
  // The following capabilities need to be provided for each new model:

  /// Collider sim capability.
  #define CAPABILITY HardScatteringSim
  START_CAPABILITY
  #undef CAPABILITY

  /// Collider sim event capability.
  #define CAPABILITY HardScatteringEvent
  START_CAPABILITY
  #undef CAPABILITY

  /// Detector sim capabilities.
  /// @{
  #define CAPABILITY ATLASDetectorSim
  START_CAPABILITY
  #undef CAPABILITY
  #define CAPABILITY CMSDetectorSim
  START_CAPABILITY
  #undef CAPABILITY
  #define CAPABILITY IdentityDetectorSim
  START_CAPABILITY
  #undef CAPABILITY
  /// @}

  /// Run detector simulators and produce the standard event format.
  /// @{
  #define CAPABILITY ATLASSmearedEvent
  START_CAPABILITY
  #undef CAPABILITY
  #define CAPABILITY CMSSmearedEvent
  START_CAPABILITY
  #undef CAPABILITY
  #define CAPABILITY CopiedEvent
  START_CAPABILITY
  #undef CAPABILITY
  /// @}

#undef MODULE
