//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation of SpecBit routines for 
///  Inert.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:33PM on February 18, 2026
///                                                
///  ********************************************* 

#include <cmath>
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
#include "gambit/Elements/smlike_higgs.hpp"
#include "gambit/Models/SimpleSpectra/InertSimpleSpec.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"

namespace Gambit
{
  
  namespace SpecBit
  {
    using namespace LogTags;
    
    void get_Inert_spectrum_SPheno(Spectrum& spectrum)
    {
      namespace myPipe = Pipes::get_Inert_spectrum_SPheno;
      const SMInputs &sminputs = *myPipe::Dep::SMINPUTS;
      
      // Set up the input structure
      Finputs inputs;
      inputs.sminputs = sminputs;
      inputs.param = myPipe::Param;
      inputs.options = myPipe::runOptions;
      
      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cuts = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      
      // Get the spectrum from the Backend
      myPipe::BEreq::SARAHSPheno_Inert_spectrum(spectrum, inputs);
      
      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }
    
    /// Helper function to work out if the LSP is invisible, and if so, which particle it is.
    std::vector<std::pair<str,str>> get_invisibles_Inert(const SubSpectrum& spec)
    {
        /// GUM has computed that there are no invisible decays for
        /// the Higgs sector of this model.
        (void)spec; // Silence compiler warnings.
        return std::vector<std::pair<str,str>>();
    }
    
    
    /// Put together the Higgs couplings for the Inert, from SPheno
    void Inert_higgs_couplings_SPheno(HiggsCouplingsTable &result)
    {
      namespace myPipe = Pipes::Inert_higgs_couplings_SPheno;
      
      // Retrieve spectrum contents
      const Spectrum& spec = *myPipe::Dep::Inert_spectrum;
      const SubSpectrum& he = spec.get_HE();
      const SMInputs &sminputs = spec.get_SMInputs();
      
      const DecayTable* tbl = &(*myPipe::Dep::decay_rates);
      
      // Set up the input structure for SPheno
      Finputs inputs;
      inputs.sminputs = sminputs;
      inputs.param = myPipe::Param;
      inputs.options = myPipe::runOptions;
      
      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
      result.set_n_neutral_higgs(3);
      
      // Set the CP of the Higgs states. Note that this would
      // need to be more sophisticated to deal with complex models.
      result.CP[0] = 1.;  // "h0_1"
      result.CP[1] = 1.;  // "h0_2"
      result.CP[2] = -1.; // "A0"
      
      // Set up charged Higgses
      static const std::vector<str> sHchar = initVector<str>("H+");
      result.set_n_charged_higgs(1);
      
      // Work out which SM values correspond to which Higgs
      int higgs = (SMlike_higgs_PDG_code(he) == 25 ? 0 : 1);
      int other_higgs = (higgs == 0 ? 1 : 0);
      
      
      // Set the Higgs sector decays from the DecayTable
      result.set_neutral_decays(higgs, sHneut[higgs], tbl->at("h0_1"));
      result.set_neutral_decays(other_higgs, sHneut[other_higgs], tbl->at("h0_2"));
      result.set_neutral_decays(2, sHneut[2], tbl->at("A0"));
      
      //Charged Higgses
      result.set_charged_decays(0, "H+", tbl->at("H+"));
      
      // Add t decays since t can decay to light Higgses
      result.set_t_decays(tbl->at("t"));
      
      // Fill HiggsCouplingsTable object from SPheno backend
      // This fills the effective couplings (C_XX2)
      myPipe::BEreq::SARAHSPheno_Inert_HiggsCouplingsTable(spec, result, inputs);
      
      // The SPheno frontend provides the invisible width for each Higgs, however this requires
      // loads of additional function calls. Just use the helper function instead.
      result.invisibles = get_invisibles_Inert(he);
    }
    
    
    // Declaration: print spectrum out
    void fill_map_from_Inert_spectrum(std::map<std::string,double>&, const Spectrum&);
    
    void get_Inert_spectrum_as_map(std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_Inert_spectrum_as_map;
      const Spectrum& spec(*myPipe::Dep::Inert_spectrum);
      fill_map_from_Inert_spectrum(specmap, spec);
    }
    
    void fill_map_from_Inert_spectrum(std::map<std::string, double>& specmap, const Spectrum& spec)
    {
      /// Use SpectrumContents routines to automate
      static const SpectrumContents::Inert contents;
      static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters();
      
      for(std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin(); it != required_parameters.end(); ++it)
      {
        const Par::Tags        tag   = it->tag();
        const std::string      name  = it->name();
        const std::vector<int> shape = it->shape();
        
        // Scalar case
        if(shape.size()==1 and shape[0]==1)
        {
          std::ostringstream label;
          label << name <<" "<< Par::toString.at(tag);
          specmap[label.str()] = spec.get_HE().get(tag,name);
        }
        // Vector case
        else if(shape.size()==1 and shape[0]>1)
        {
          for(int i = 1; i<=shape[0]; ++i)
          {
            std::ostringstream label;
            label << name <<"_"<<i<<" "<< Par::toString.at(tag);
            specmap[label.str()] = spec.get_HE().get(tag,name,i);
          }
        }
        // Matrix case
        else if(shape.size()==2)
        {
          for(int i = 1; i<=shape[0]; ++i)
          {
            for(int j = 1; j<=shape[0]; ++j)
            {
              std::ostringstream label;
              label << name <<"_("<<i<<","<<j<<") "<<Par::toString.at(tag);
              specmap[label.str()] = spec.get_HE().get(tag,name,i,j);
            }
          }
        }
        // Deal with all other cases
        else
        {
          // ERROR
          std::ostringstream errmsg;
          errmsg << "Invalid parameter received while converting Inert_spectrum to map of strings!";
          errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape;
          utils_error().forced_throw(LOCAL_INFO,errmsg.str());
        }
      }
    }
    
  }
  
}
