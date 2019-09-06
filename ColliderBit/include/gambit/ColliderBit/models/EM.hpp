//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for ColliderBit module;
///  EM models.
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
///
///  \author Andy Buckley
///          (andy.buckley@cern.ch)
///  \date 2017 Jun
///
///  *********************************************

#pragma once

#define MODULE ColliderBit

  // Get Monte Carlo event generator
  #define CAPABILITY HardScatteringSim

    #define FUNCTION getPythia_EM
    START_FUNCTION(ColliderPythia_EM_defaultversion)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    DEPENDENCY(decay_rates, DecayTable)
    DEPENDENCY(EM_spectrum, Spectrum)
    #undef FUNCTION

    #define FUNCTION getPythia_EMAsBase
    START_FUNCTION(const BaseCollider*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    DEPENDENCY(HardScatteringSim, ColliderPythia_EM_defaultversion)
    #undef FUNCTION

  #undef CAPABILITY


  // Run event generator
  #define CAPABILITY HardScatteringEvent
    #define FUNCTION generateEventPythia_EM
    START_FUNCTION(Pythia_EM_default::Pythia8::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    DEPENDENCY(HardScatteringSim, ColliderPythia_EM_defaultversion)
    #undef FUNCTION
  #undef CAPABILITY


  // Get detector simulations

  #define CAPABILITY ATLASDetectorSim
    #define FUNCTION getBuckFastATLASPythia_EM
    START_FUNCTION(BaseDetector<Pythia_EM_default::Pythia8::Event>*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CMSDetectorSim
    #define FUNCTION getBuckFastCMSPythia_EM
    START_FUNCTION(BaseDetector<Pythia_EM_default::Pythia8::Event>*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IdentityDetectorSim
    #define FUNCTION getBuckFastIdentityPythia_EM
    START_FUNCTION(BaseDetector<Pythia_EM_default::Pythia8::Event>*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    #undef FUNCTION
  #undef CAPABILITY


  // Run detector simulations

  #define CAPABILITY ATLASSmearedEvent
    #define FUNCTION smearEventATLAS_EM
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    DEPENDENCY(HardScatteringEvent, Pythia_EM_default::Pythia8::Event)
    DEPENDENCY(ATLASDetectorSim, BaseDetector<Pythia_EM_default::Pythia8::Event>*)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CMSSmearedEvent
    #define FUNCTION smearEventCMS_EM
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    DEPENDENCY(HardScatteringEvent, Pythia_EM_default::Pythia8::Event)
    DEPENDENCY(CMSDetectorSim, BaseDetector<Pythia_EM_default::Pythia8::Event>*)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CopiedEvent
    #define FUNCTION copyEvent_EM
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    DEPENDENCY(HardScatteringEvent, Pythia_EM_default::Pythia8::Event)
    DEPENDENCY(IdentityDetectorSim, BaseDetector<Pythia_EM_default::Pythia8::Event>*)
    #undef FUNCTION
  #undef CAPABILITY

#undef MODULE