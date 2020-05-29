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

  // SLHAea object with spectrum and decays for a Pythia8 collider
  #define CAPABILITY SpectrumAndDecaysForPythia


    #define FUNCTION getSpectrumAndDecaysForPythia_EM
    START_FUNCTION(SLHAstruct)
    NEEDS_MANAGER(RunMC, MCLoopInfo)      // @todo Why is this needed?
    DEPENDENCY(decay_rates, DecayTable)
    DEPENDENCY(EM_spectrum, Spectrum)
    #undef FUNCTION

  #undef CAPABILITY

  // Get Monte Carlo event generator
  #define CAPABILITY HardScatteringSim

    #define FUNCTION getPythia_EM
    START_FUNCTION(Py8Collider_EM_defaultversion)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    DEPENDENCY(SpectrumAndDecaysForPythia, SLHAstruct)
    #undef FUNCTION

    #define FUNCTION getPythia_EMAsBase
    START_FUNCTION(const BaseCollider*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    DEPENDENCY(HardScatteringSim, Py8Collider_EM_defaultversion)
    #undef FUNCTION

  #undef CAPABILITY


  // Run event generator
  #define CAPABILITY HardScatteringEvent
    #define FUNCTION generateEventPythia_EM
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia_EM, default)
    DEPENDENCY(HardScatteringSim, Py8Collider_EM_defaultversion)
    DEPENDENCY(EventWeighterFunction, EventWeighterFunctionType)
    #undef FUNCTION
  #undef CAPABILITY

#undef MODULE