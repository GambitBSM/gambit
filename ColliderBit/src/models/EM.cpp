//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  External Model-specific sources for ColliderBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Jan
///
///  *********************************************

#include "gambit/ColliderBit/getPy8Collider.hpp"
#include "gambit/ColliderBit/generateEventPy8Collider.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    // Get spectrum and decays for Pythia
    GET_SPECTRUM_AND_DECAYS_FOR_PYTHIA_NONSUSY(getSpectrumAndDecaysForPythia_EM, EM_spectrum)

    // Get Monte Carlo event generator
    GET_SPECIFIC_PYTHIA(getPythia_EM, Pythia_EM_default, _EM)
    GET_PYTHIA_AS_BASE_COLLIDER(getPythia_EMAsBase)

    // Run event generator
    GET_PYTHIA_EVENT(generateEventPythia_EM)

    #ifndef EXCLUDE_HEPMC
      // Template specialization for EM Pythia
      template <>
      void dropHepMCEventPy8Collider<Pythia_EM_8_212::Pythia8::Pythia>(const Pythia_EM_8_212::Pythia8::Pythia* Pythia, const safe_ptr<Options>& runOptions)
      {
         (void) Pythia;
         (void) runOptions;
      }
    #endif
  }
}
