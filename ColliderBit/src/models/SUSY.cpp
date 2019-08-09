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
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Jan
///
///  *********************************************

#include "gambit/ColliderBit/getColliderPythia.hpp"
#include "gambit/ColliderBit/generateEventColliderPythia.hpp"
#include "gambit/ColliderBit/getBuckFast.hpp"
#include "gambit/ColliderBit/smearEvent.hpp"


namespace Gambit
{
  namespace ColliderBit
  {

    // Get Monte Carlo event generator
    GET_SPECIFIC_PYTHIA(getPythia, Pythia_default, MSSM_spectrum, , IS_SUSY)
    GET_PYTHIA_AS_BASE_COLLIDER(getPythiaAsBase)

    // Run event generator
    GET_PYTHIA_EVENT(generateEventPythia, Pythia_default::Pythia8::Event)

    // Get detector simulations
    GET_BUCKFAST_AS_BASE_DETECTOR(getBuckFastATLASPythia, Pythia_default::Pythia8::Event, ATLAS)
    GET_BUCKFAST_AS_BASE_DETECTOR(getBuckFastCMSPythia, Pythia_default::Pythia8::Event, CMS)
    GET_BUCKFAST_AS_BASE_DETECTOR(getBuckFastIdentityPythia, Pythia_default::Pythia8::Event, Identity)

    // Run detector simulations
    SMEAR_EVENT(smearEventATLAS, ATLAS)
    SMEAR_EVENT(smearEventCMS, CMS)
    SMEAR_EVENT(copyEvent, Identity)

  }
}
