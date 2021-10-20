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
///  \author Anders Kvellestad
///          (a.kvellestad@imperial.ac.uk)
///  \date 2019 Sep
///
///  *********************************************

#pragma once

#include "gambit/Utils/util_types.hpp"

#define MODULE ColliderBit

  /// Execute the main Monte Carlo event loop.
  /// Note: 
  ///   "Non-loop" capabilities that some in-loop capabilities depend on
  ///   can be added as dependencies here to ensure that they are calculated
  ///   before the loop starts.
  #define CAPABILITY RunMC
  START_CAPABILITY
    #define FUNCTION operateLHCLoop
    START_FUNCTION(MCLoopInfo, CAN_MANAGE_LOOPS)
    MODEL_CONDITIONAL_DEPENDENCY(SLHAFileNameAndContent, pair_str_SLHAstruct, ColliderBit_SLHA_file_model, ColliderBit_SLHA_scan_model)
    #undef FUNCTION

    // Make a dummy MCLoopInfo object for interpolated yield "colliders"
    #define FUNCTION InterpolatedMCInfo
    START_FUNCTION(MCLoopInfo)
    #undef FUNCTION
  #undef CAPABILITY



  /// Total cross-section
  /// @{
  // Get total cross-section as calculated by the event generator
  #define CAPABILITY TotalEvGenCrossSection
  START_CAPABILITY
    #define FUNCTION getEvGenCrossSection
    START_FUNCTION(MC_xsec_container)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(HardScatteringSim, const BaseCollider*)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY TotalCrossSection
  START_CAPABILITY
    /// Convert the TotalEvGenCrossSection (type MC_xsec_container) into 
    /// a regular TotalCrossSection (type xsec_container)
    #define FUNCTION getEvGenCrossSection_as_base
    START_FUNCTION(xsec_container)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(TotalEvGenCrossSection, MC_xsec_container)
    #undef FUNCTION

    /// Example function for interfacing alternative cross-section calculators
    #define FUNCTION getNLLFastCrossSection
    START_FUNCTION(xsec_container)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    #undef FUNCTION

    /// A function that reads the total cross-section from the input file,
    /// but builds up the number of events from the event loop
    #define FUNCTION getYAMLCrossSection
    START_FUNCTION(xsec_container)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    #undef FUNCTION

    /// A function that assigns a total cross-sections to a given SLHA input file
    /// (for model ColliderBit_SLHA_file_model)
    #define FUNCTION getYAMLCrossSection_SLHA
    START_FUNCTION(xsec_container)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    ALLOW_MODELS(ColliderBit_SLHA_file_model)
    DEPENDENCY(SLHAFileNameAndContent, pair_str_SLHAstruct)
    #undef FUNCTION

    /// A function that assigns a total cross-sections directly from the scan parameters
    /// for model ColliderBit_SLHA_scan_model
    #define FUNCTION getYAMLCrossSection_param
    START_FUNCTION(xsec_container)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    ALLOW_MODELS(ColliderBit_SLHA_scan_model)
    #undef FUNCTION
  #undef CAPABILITY

  /// Output info on TotalCrossSection as 
  /// a str-double map, for easy printing
  #define CAPABILITY TotalCrossSectionAsMap
  START_CAPABILITY
    #define FUNCTION getTotalCrossSectionAsMap
    START_FUNCTION(map_str_dbl)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(TotalCrossSection, xsec_container)
    #undef FUNCTION
  #undef CAPABILITY
  /// @}


  /// Process codes and PID pairs
  /// @{
  /// Get list of Pythia process codes for all active processes
  #define CAPABILITY ActiveProcessCodes
  START_CAPABILITY
    #define FUNCTION getActiveProcessCodes
    START_FUNCTION(std::vector<int>)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(HardScatteringSim, const BaseCollider*)
    #undef FUNCTION
  #undef CAPABILITY 

  /// Get a list of all the PID pairs related to active process codes
  #define CAPABILITY ActivePIDPairs
  START_CAPABILITY
    #define FUNCTION getActivePIDPairs
    START_FUNCTION(vec_PID_pair)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(ActiveProcessCodeToPIDPairsMap, multimap_int_PID_pair)
    #undef FUNCTION
  #undef CAPABILITY 

  /// Translate a list of Pythia process codes to list of (PID,PID) pairs
  /// for the two final state particles of the hard process.
  #define CAPABILITY ActiveProcessCodeToPIDPairsMap
  START_CAPABILITY
    #define FUNCTION getActiveProcessCodeToPIDPairsMap
    START_FUNCTION(multimap_int_PID_pair)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(ActiveProcessCodes, std::vector<int>)
    #undef FUNCTION
  #undef CAPABILITY 
  /// @}



  /// Process-level cross-sections
  /// @{
  /// A map between Pythia process codes and cross-sections
  #define CAPABILITY ProcessCrossSectionsMap
  START_CAPABILITY
    #define FUNCTION getProcessCrossSectionsMap
    START_FUNCTION(map_int_process_xsec)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(ActiveProcessCodes, std::vector<int>)
    DEPENDENCY(ActiveProcessCodeToPIDPairsMap, multimap_int_PID_pair)
    DEPENDENCY(PIDPairCrossSectionsMap, map_PID_pair_PID_pair_xsec) 
    #undef FUNCTION
  #undef CAPABILITY

  /// A map between PID pairs and cross-sections
  #define CAPABILITY PIDPairCrossSectionsMap
  START_CAPABILITY
    #define FUNCTION getPIDPairCrossSectionsMap_testing
    START_FUNCTION(map_PID_pair_PID_pair_xsec)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(ActivePIDPairs, vec_PID_pair)
    #undef FUNCTION
  #undef CAPABILITY

  /// Output PID pair cross-sections as a 
  /// str-dbl map, for easy printing
  #define CAPABILITY PIDPairCrossSectionsInfo
  START_CAPABILITY
    #define FUNCTION getPIDPairCrossSectionsInfo
    START_FUNCTION(map_str_dbl)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(PIDPairCrossSectionsMap, map_PID_pair_PID_pair_xsec)
    #undef FUNCTION
  #undef CAPABILITY
  /// @}

  /// A consistency check that ensures that if each event is weighted
  /// by a process-level cross-section from an external calculator, then
  /// the total cross-section is taken from the event generator
  #define CAPABILITY CrossSectionConsistencyCheck
  START_CAPABILITY
    #define FUNCTION doCrossSectionConsistencyCheck
    START_FUNCTION(bool)
    // NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(TotalCrossSection, xsec_container)
    DEPENDENCY(EventWeighterFunction, EventWeighterFunctionType)
    #undef FUNCTION
  #undef CAPABILITY


  /// Lists of analyses to run
  /// @{
  #define CAPABILITY ATLASAnalysisContainer
  START_CAPABILITY
    #define FUNCTION getATLASAnalysisContainer
    START_FUNCTION(AnalysisContainer)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(TotalCrossSection, xsec_container)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CMSAnalysisContainer
  START_CAPABILITY
    #define FUNCTION getCMSAnalysisContainer
    START_FUNCTION(AnalysisContainer)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(TotalCrossSection, xsec_container)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IdentityAnalysisContainer
  START_CAPABILITY
    #define FUNCTION getIdentityAnalysisContainer
    START_FUNCTION(AnalysisContainer)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(TotalCrossSection, xsec_container)
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
    DEPENDENCY(CrossSectionConsistencyCheck, bool)
    DEPENDENCY(ATLASAnalysisNumbers, AnalysisDataPointers)
    DEPENDENCY(CMSAnalysisNumbers, AnalysisDataPointers)
    DEPENDENCY(IdentityAnalysisNumbers, AnalysisDataPointers)
    #undef FUNCTION

    #define FUNCTION DMEFT_results_profiled
    START_FUNCTION(AnalysisDataPointers)
    DEPENDENCY(AllAnalysisNumbersUnmodified, AnalysisDataPointers)
    DEPENDENCY(DMEFT_profiled_LHC_nuisance_params, map_str_dbl)
    DEPENDENCY(DMEFT_spectrum, Spectrum)
    ALLOW_MODELS(DMEFT)
    #undef FUNCTION

    #define FUNCTION DMEFT_results_cutoff
    START_FUNCTION(AnalysisDataPointers)
    DEPENDENCY(AllAnalysisNumbersUnmodified, AnalysisDataPointers)
    DEPENDENCY(DMEFT_spectrum, Spectrum)
    ALLOW_MODELS(DMEFT)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY AllAnalysisNumbersUnmodified
    #define FUNCTION DMEFT_results
    START_FUNCTION(AnalysisDataPointers)
    DEPENDENCY(DMEFT_spectrum, Spectrum)
    ALLOW_MODELS(DMEFT)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY DMEFT_profiled_LHC_nuisance_params
    #define FUNCTION calc_DMEFT_profiled_LHC_nuisance_params
    START_FUNCTION(map_str_dbl)
    DEPENDENCY(AllAnalysisNumbersUnmodified, AnalysisDataPointers)
    DEPENDENCY(DMEFT_spectrum, Spectrum)
    ALLOW_MODELS(DMEFT)
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

  /// Calculate the total LHC log likelihood
  #define CAPABILITY LHC_LogLike_scan_guide
  START_CAPABILITY
    #define FUNCTION calc_LHC_LogLike_scan_guide
    START_FUNCTION(double)
    DEPENDENCY(LHC_Combined_LogLike, double)
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

  /// Detector sim capabilities.
  /// @{
  #define CAPABILITY ATLASDetectorSim
  START_CAPABILITY
    #define FUNCTION getBuckFastATLAS
    START_FUNCTION(BaseDetector*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CMSDetectorSim
  START_CAPABILITY
    #define FUNCTION getBuckFastCMS
    START_FUNCTION(BaseDetector*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IdentityDetectorSim
  START_CAPABILITY
    #define FUNCTION getBuckFastIdentity
    START_FUNCTION(BaseDetector*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    #undef FUNCTION
  #undef CAPABILITY
  /// @}

  /// Run detector simulators and produce the standard event format.
  /// @{
  #define CAPABILITY ATLASSmearedEvent
  START_CAPABILITY
    #define FUNCTION smearEventATLAS
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(HardScatteringEvent, HEPUtils::Event)
    DEPENDENCY(ATLASDetectorSim, BaseDetector*)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CMSSmearedEvent
  START_CAPABILITY
    #define FUNCTION smearEventCMS
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(HardScatteringEvent, HEPUtils::Event)
    DEPENDENCY(CMSDetectorSim, BaseDetector*)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CopiedEvent
  START_CAPABILITY
    #define FUNCTION copyEvent
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(HardScatteringEvent, HEPUtils::Event)
    DEPENDENCY(IdentityDetectorSim, BaseDetector*)
    #undef FUNCTION
  #undef CAPABILITY
  /// @}


  /// Provide functions that can be used for event weighting, e.g. for process-level cross-section scaling.
  /// {@
  #define CAPABILITY EventWeighterFunction
  START_CAPABILITY

    /// This function is intended as a fallback option 
    /// that simply assigns a unit weight to all events
    #define FUNCTION setEventWeight_unity
    START_FUNCTION(EventWeighterFunctionType)
    #undef FUNCTION

    /// Weight events according to process cross-section 
    #define FUNCTION setEventWeight_fromCrossSection
    START_FUNCTION(EventWeighterFunctionType)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    DEPENDENCY(ProcessCrossSectionsMap, map_int_process_xsec)
    #undef FUNCTION

    /// Event weight functions that depend on model-specific Py8Collider versions
    /// should be declared in the corresponding model header in ColliderBit/models.

  #undef CAPABILITY
  /// @{


  // All other functions are declared in additional headers in the ColliderBit/models directory.
  // The following capabilities need to be provided for each new model:

  // SLHAea object with spectrum and decays for a Pythia8 collider
  #define CAPABILITY SpectrumAndDecaysForPythia
  START_CAPABILITY
  #undef CAPABILITY

  /// Collider sim capability.
  #define CAPABILITY HardScatteringSim
  START_CAPABILITY
  #undef CAPABILITY

  /// Collider sim event capability.
  #define CAPABILITY HardScatteringEvent
  START_CAPABILITY

    /// Only activate these functions if HepMC is activated
    #ifndef EXCLUDE_HEPMC

      /// A nested function that reads in Les Houches Event files and converts them to HEPUtils::Event format
      #define FUNCTION getLHEvent
      START_FUNCTION(HEPUtils::Event)
      NEEDS_MANAGER(RunMC, MCLoopInfo)
      #undef FUNCTION

      /// A nested function that reads in HepMC event files and converts them to HEPUtils::Event format
      #define FUNCTION getHepMCEvent
      START_FUNCTION(HEPUtils::Event)
      NEEDS_MANAGER(RunMC, MCLoopInfo)
      #undef FUNCTION

    #endif

  #undef CAPABILITY

#undef MODULE
