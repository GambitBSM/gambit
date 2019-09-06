//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for ColliderBit module;
///  SUSY models.
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

    #define FUNCTION getPythia
    START_FUNCTION(ColliderPythia_defaultversion)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    DEPENDENCY(decay_rates, DecayTable)
    MODEL_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ, MSSM63atMGUT)
    #undef FUNCTION

    #define FUNCTION getPythiaAsBase
    START_FUNCTION(const BaseCollider*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    DEPENDENCY(HardScatteringSim, ColliderPythia_defaultversion)
    #undef FUNCTION

  #undef CAPABILITY


  // Run event generator
  #define CAPABILITY HardScatteringEvent
    #define FUNCTION generateEventPythia
    START_FUNCTION(Pythia_default::Pythia8::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    DEPENDENCY(HardScatteringSim, ColliderPythia_defaultversion)
    #undef FUNCTION
  #undef CAPABILITY


  // Get detector simulations

  #define CAPABILITY ATLASDetectorSim
    #define FUNCTION getBuckFastATLASPythia
    START_FUNCTION(BaseDetector<Pythia_default::Pythia8::Event>*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CMSDetectorSim
    #define FUNCTION getBuckFastCMSPythia
    START_FUNCTION(BaseDetector<Pythia_default::Pythia8::Event>*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY IdentityDetectorSim
    #define FUNCTION getBuckFastIdentityPythia
    START_FUNCTION(BaseDetector<Pythia_default::Pythia8::Event>*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    #undef FUNCTION
  #undef CAPABILITY


  // Run detector simulations

  #define CAPABILITY ATLASSmearedEvent
    #define FUNCTION smearEventATLAS
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    DEPENDENCY(HardScatteringEvent, Pythia_default::Pythia8::Event)
    DEPENDENCY(ATLASDetectorSim, BaseDetector<Pythia_default::Pythia8::Event>*)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CMSSmearedEvent
    #define FUNCTION smearEventCMS
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    DEPENDENCY(HardScatteringEvent, Pythia_default::Pythia8::Event)
    DEPENDENCY(CMSDetectorSim, BaseDetector<Pythia_default::Pythia8::Event>*)
    #undef FUNCTION
  #undef CAPABILITY

  #define CAPABILITY CopiedEvent
    #define FUNCTION copyEvent
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    DEPENDENCY(HardScatteringEvent, Pythia_default::Pythia8::Event)
    DEPENDENCY(IdentityDetectorSim, BaseDetector<Pythia_default::Pythia8::Event>*)
    #undef FUNCTION
  #undef CAPABILITY

#undef MODULE