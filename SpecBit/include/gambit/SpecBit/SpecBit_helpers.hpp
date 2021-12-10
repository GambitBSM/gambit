//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declarations of convenience (i.e. non-Gambit)
///  functions used by more than one SpecBit 
///  source file.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2014 Sep - Dec, 2015 Jan - May
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date Jul 2020
///  
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Nov
///
///  *********************************************

#ifndef __SpecBit_helpers_hpp__
#define __SpecBit_helpers_hpp__

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/Elements/spectrum.hpp"

#include "gambit/SpecBit/SpecBit_rollcall.hpp"

#include "gambit/Models/partmap.hpp"

namespace Gambit
{

  namespace SpecBit
  {

    /// Non-Gambit helper functions
    //  =======================================================================
    //  These are not known to Gambit, but perform helper tasks used by the
    //  Gambit module functions.

    // {@ SUSY-specific helper functions, here in case SUSY models other than the MSSM need it

    /// Check that the spectrum has the canonical LSP for the model being scanned.
    void check_LSP(const Spectrum& spec, std::vector<int> LSPs);

    /// Helper to work with pointer
    void check_LSP(const Spectrum* spec, std::vector<int> LSPs);

    /// Add gravitino mass to the spectrum and list of LSPs
    void add_gravitino_mass(Spectrum& spec, std::vector<int> &LSPs, double mG, const safe_ptr<Options>& runOptions);

    /// Adds additional information from interesting combinations of MSSM parameters
    void add_extra_MSSM_parameter_combinations(std::map<std::string,double>&, const Spectrum&);

    /// Helper function to work out if the LSP is invisible, and if so, which particle it is.
    std::vector<std::pair<str,str>> get_invisibles(const Spectrum& spec);
  
    // @}

    // {@ Generic map filler function

    /// Extract all parameters from a spectrum and put them into a map
    // TODO: I removed all override stuff since there are no overrides anymore, but check
    template<class Contents>
    void fill_map_from_spectrum(std::map<std::string,double>& specmap, const Spectrum& spec)
    {
      /// Add everything... use spectrum contents routines to automate task (make sure to use correct template parameter!)
      static const Contents contents;
      static const std::vector<SpectrumContents::Parameter> required_parameters = contents.all_parameters();

      for(std::vector<SpectrumContents::Parameter>::const_iterator it = required_parameters.begin();
           it != required_parameters.end(); ++it)
      {
         const Par::Tags        tag   = it->tag();
         const std::string      name  = it->name();
         const std::vector<int> shape = it->shape();

         /// Verification routine should have taken care of invalid shapes etc, so won't check for that here.

         // Check scalar case
         if(shape.size()==0)
         {
           std::ostringstream label;
           label << name <<" "<< Par::toString.at(tag);
           specmap[label.str()] = spec.get(tag,name);
         }
         // Check vector case
         else if(shape.size()==1 and shape[0]>1)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             std::ostringstream label;
             label << name <<"_"<<i<<" "<< Par::toString.at(tag);
             specmap[label.str()] = spec.get(tag,name,i);
           }
         }
         // Check matrix case
         else if(shape.size()==2)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             for(int j = 1; j<=shape[0]; ++j) {
               std::ostringstream label;
               label << name <<"_("<<i<<","<<j<<") "<<Par::toString.at(tag);
               specmap[label.str()] = spec.get(tag,name,i,j);
             }
           }
         }
         // Deal with all other cases
         else
         {
           // ERROR
           std::ostringstream errmsg;
           errmsg << "Error, invalid parameter received while converting Spectrum with contents \""<<contents.getName()<<"\" to map of strings! This should no be possible if the spectrum content verification routines were working correctly; they must be buggy, please report this.";
           errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape;
           SpecBit_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
      }
      // add the scale!
      specmap["scale(Q)"] = spec.GetScale();
    }

    // @}
  }
}
 
#endif
