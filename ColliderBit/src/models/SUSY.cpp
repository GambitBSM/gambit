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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2019
///
///  *********************************************

#include "gambit/ColliderBit/getCollider.hpp"
#include "gambit/ColliderBit/generateColliderEvent.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    // Get spectrum and decays for Pythia
    GET_SPECTRUM_AND_DECAYS_FOR_PYTHIA_SUSY(getSpectrumAndDecaysForPythia, MSSM_spectrum)

    // Get Monte Carlo event generator
    GET_SPECIFIC_PYTHIA(getPythia)

    // Run event generator
    GET_PYTHIA_EVENT(generateEventPythia)

    // Run initial Pythia cross-section estimation
    GET_INITIAL_XSEC_PYTHIA(PerformInitialCrossSection_Pythia)

  }
}
