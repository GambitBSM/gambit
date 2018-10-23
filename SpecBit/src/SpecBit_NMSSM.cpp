//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit for the NMSSM
///
///  These functions link ModelParameters to
///  Spectrum objects in various ways (by running
///  spectrum generators, etc.)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2018 Oct 
///
///  *********************************************

//#include <string>
//#include <sstream>
//#include <cmath>
//#include <complex>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
//#include "gambit/Elements/smlike_higgs.hpp"
#include "gambit/Models/SimpleSpectra/NMSSMSimpleSpec.hpp"
//#include "gambit/Utils/stream_overloads.hpp" // Just for more convenient output to logger
//#include "gambit/Utils/util_macros.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
//#include "gambit/SpecBit/QedQcdWrapper.hpp"
//#include "gambit/SpecBit/MSSMSpec.hpp"

// Switch for debug mode
//#define SPECBIT_DEBUG

namespace Gambit
{

  namespace SpecBit
  {
    using namespace LogTags;

    void get_NMSSM_spectrum_SPheno (Spectrum& spectrum)
    {
      namespace myPipe = Pipes::get_NMSSM_spectrum_SPheno;
      const SMInputs &sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      Finputs inputs;
      inputs.sminputs = sminputs;
      inputs.param = myPipe::Param;
      inputs.options = myPipe::runOptions;

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // Get the spectrum from the Backend
      myPipe::BEreq::SPheno_NMSSMspectrum(spectrum, inputs);
 
      // Get the SLHA struct from the spectrum object
      SLHAstruct slha = spectrum.getSLHAea(2);

      // Convert into a spectrum object
      spectrum = spectrum_from_SLHAea<NMSSMSimpleSpec, SLHAstruct>(slha,slha,mass_cut,mass_ratio_cut);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");

      // Only allow neutralino LSPs.
      if (not has_neutralino_LSP(spectrum)) invalid_point().raise("Neutralino is not LSP.");
    }

    /// @} End Gambit module functions

  } // end namespace SpecBit
} // end namespace Gambit

