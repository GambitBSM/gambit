//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Rollcall header for THDM models in
///  ColliderBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date 2023
///
///  *********************************************

#pragma once

#include "gambit/ColliderBit/models/SUSY_extras.hpp"

#define MODULE ColliderBit


  // Construct an SLHAea object with spectrum and decays for Pythia
  #define CAPABILITY SpectrumAndDecaysForPythia

    #define FUNCTION getSpectrumAndDecaysForPythia_THDM
    START_FUNCTION(SLHAstruct)
    DEPENDENCY(decay_rates, DecayTable)
    DEPENDENCY(THDM_spectrum, Spectrum)
    DEPENDENCY(Higgs_Couplings, HiggsCouplingsTable)
    DEPENDENCY(couplingtable_THDM, CouplingTable)
    ALLOW_MODELS(THDM, THDMatQ)
    #undef FUNCTION

  #undef CAPABILITY


  // Get Monte Carlo event generator
  #define CAPABILITY HardScatteringSim

    #define FUNCTION getPythia_THDM
    START_FUNCTION(Py8Collider_defaultversion)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    ALLOW_MODELS(THDM, THDMatQ)
    DEPENDENCY(SpectrumAndDecaysForPythia, SLHAstruct)
    #undef FUNCTION

    #define FUNCTION getPythiaAsBase_THDM
    START_FUNCTION(const BaseCollider*)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    DEPENDENCY(HardScatteringSim, Py8Collider_defaultversion)
    ALLOW_MODELS(THDM, THDMatQ)
    ALLOW_MODELS(ColliderBit_SLHA_file_model, ColliderBit_SLHA_scan_model)
    #undef FUNCTION

  #undef CAPABILITY


  // Run event generator
  #define CAPABILITY HardScatteringEvent
    #define FUNCTION generateEventPythia_THDM
    START_FUNCTION(Pythia_default::Pythia8::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    DEPENDENCY(HardScatteringSim, Py8Collider_defaultversion)
    DEPENDENCY(EventWeighterFunction, EventWeighterFunctionType)
    ALLOW_MODELS(THDM, THDMatQ)
    ALLOW_MODELS(ColliderBit_SLHA_file_model, ColliderBit_SLHA_scan_model)
    #undef FUNCTION

    #define FUNCTION generateEventPythia_THDM_HEPUtils
    START_FUNCTION(HEPUtils::Event)
    NEEDS_MANAGER(RunMC, MCLoopInfo)
    NEEDS_CLASSES_FROM(Pythia, default)
    DEPENDENCY(HardScatteringSim, Py8Collider_defaultversion)
    DEPENDENCY(HardScatteringEvent, Pythia_default::Pythia8::Event)
    DEPENDENCY(EventWeighterFunction, EventWeighterFunctionType)
    #undef FUNCTION

    #ifndef EXCLUDE_HEPMC
      #define FUNCTION generateEventPythia_THDM_HepMC
      START_FUNCTION(HepMC3::GenEvent)
      NEEDS_MANAGER(RunMC, MCLoopInfo)
      NEEDS_CLASSES_FROM(Pythia, default)
      DEPENDENCY(HardScatteringSim, Py8Collider_defaultversion)
      DEPENDENCY(HardScatteringEvent, Pythia_default::Pythia8::Event)
      #undef FUNCTION
    #endif

  #undef CAPABILITY

#undef MODULE
