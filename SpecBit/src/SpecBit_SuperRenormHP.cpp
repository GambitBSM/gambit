//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit
///
///  SpecBit module functions related to the
///  super-renormalizable Higgs portal model.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Inigo Saez Casares
///          (inigo.saez_casares@ens-paris-saclay.fr)
///    \date 2020 March
///
///  *********************************************

// TODO: Temporarily disabled until project is ready
/*
#include <string>
#include <sstream>

#include "gambit/Elements/gambit_module_headers.hpp"

#include "gambit/Elements/spectrum.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/util_macros.hpp"

#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/Models/SimpleSpectra/SMHiggsSimpleSpec.hpp"
#include "gambit/Models/SimpleSpectra/SuperRenormHPSimpleSpec.hpp"
#include "gambit/SpecBit/model_files_and_boxes.hpp"

namespace Gambit
{
  namespace SpecBit
  {
    using namespace LogTags;

    /// Get a (simple) Spectrum object wrapper for the SuperRenormHP model
    void get_SuperRenormHP_spectrum(Spectrum& result)
    {
      namespace myPipe = Pipes::get_SuperRenormHP_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Initialise an object to carry the Singlet plus Higgs sector information
      Models::SuperRenormHPModel scalarmodel;

      // Higgs sector
      double mh = *myPipe::Param["mH"];
      scalarmodel.HiggsPoleMass = mh;

      double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);
      scalarmodel.HiggsVEV = vev;

      // Scalar DM sector
      scalarmodel.ScalarPoleMass = *myPipe::Param["mS"];
      scalarmodel.MixingAngle = *myPipe::Param["theta"];

      // Create a SubSpectrum object to wrap the EW sector information
      Models::SuperRenormHPSimpleSpec scalarspec(scalarmodel);

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // We don't supply a LE subspectrum here; an SMSimpleSpec will therefore be automatically created from 'sminputs'
      result = Spectrum(scalarspec,sminputs,&myPipe::Param,mass_cut,mass_ratio_cut);
    }

  } // end namespace SpecBit
} // end namespace Gambit
*/
