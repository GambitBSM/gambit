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

#include "gambit/ColliderBit/getPy8Collider.hpp"
#include "gambit/ColliderBit/generateEventPy8Collider.hpp"
#include "gambit/Elements/emulator_functions.hpp"
#include "gambit/Core/emu_map.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    // Get spectrum and decays for Pythia
    GET_SPECTRUM_AND_DECAYS_FOR_PYTHIA_SUSY(getSpectrumAndDecaysForPythia, MSSM_spectrum)

    // Get Monte Carlo event generator
    GET_SPECIFIC_PYTHIA(getPythia, Pythia_default, /* blank MODEL_EXTENSION argument */ )
    GET_PYTHIA_AS_BASE_COLLIDER(getPythiaAsBase)

    // Run event generator
    GET_PYTHIA_EVENT(generateEventPythia, Pythia_default::Pythia8::Event)

    // Emulator translate functions for PerformInitialCrossSection_Pythia
    // Inputs: M2 and mu (EWino parameters); all other MSSM11atQ_mA params are fixed.
    void PerformInitialCrossSection_Pythia_EmulatorTranslateInput(std::vector<double>& input)
    {
      using namespace Pipes::PerformInitialCrossSection_Pythia;
      input = {*Param["M2"], *Param["mu"]};
    }

    bool PerformInitialCrossSection_Pythia_EmulatorCheckThreshold(str& name, std::vector<double>& uncertainty)
    {
      return checkThreshold(name, uncertainty);
    }

    // Target: the total cross-section for each collider (one entry per collider).
    // Uncertainty: use the Pythia MC relative statistical error.
    void PerformInitialCrossSection_Pythia_EmulatorTranslateTarget(
        std::vector<double>& target, initialxsec_container& result, std::vector<double>& uncertainty)
    {
      target.clear();
      uncertainty.clear();
      for (const auto& [name, xsec] : result.first)
      {
        target.push_back(xsec.xsec());
        uncertainty.push_back(xsec.xsec_relerr());
      }
    }

    // Prediction: reconstruct initialxsec_container from emulator output.
    // Note: hardcoded collider name "LHC_13TeV" for this example.
    void PerformInitialCrossSection_Pythia_EmulatorTranslatePrediction(
        std::vector<double>& prediction, initialxsec_container& result)
    {
      result.first.clear();
      result.second.clear();
      xsec_container xsec;
      xsec.set_xsec(prediction[0], 0.0);
      result.first["LHC_13TeV"] = xsec;
    }

    // Run initial Pythia cross-section estimation
    GET_INITIAL_XSEC_PYTHIA(PerformInitialCrossSection_Pythia, Py8Collider_defaultversion, Pythia_default)

  }
}
