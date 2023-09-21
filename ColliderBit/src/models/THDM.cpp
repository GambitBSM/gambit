//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  SUSY-specific sources for ColliderBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date 2023
///
///  *********************************************

#include "gambit/ColliderBit/getPy8Collider.hpp"
#include "gambit/ColliderBit/generateEventPy8Collider.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    // Get spectrum and decays for Pythia
    GET_SPECTRUM_AND_DECAYS_FOR_PYTHIA_NONSUSY(getSpectrumAndDecaysForPythia_THDM, THDM_spectrum)

    // Get Monte Carlo event generator
    GET_SPECIFIC_PYTHIA(getPythia_THDM, Pythia_default, /* blank MODEL_EXTENSION argument */ )
    GET_PYTHIA_AS_BASE_COLLIDER(getPythiaAsBase_THDM)

    // Run event generator
    GET_PYTHIA_EVENT(generateEventPythia_THDM, Pythia_default::Pythia8::Event)

  }
}
