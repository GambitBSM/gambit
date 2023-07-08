//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Base class for definining the required
///  contents of SubSpectrum wrapper objects
///
///  *********************************************
///
///  Authors: 
///  <!-- add name and date if you modify -->
///   
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2016 Feb 
///
///  *********************************************

#ifndef __subspectrum_contents_hpp__ 
#define __subspectrum_contents_hpp__ 

#include "gambit/Elements/spectrum_helpers.hpp"
#include "gambit/Utils/variadic_functions.hpp"

namespace Gambit { 

   class SubSpectrum;

   /// Simple class to contain information defining how some parameter in a SubSpectrum object can be accessed
   class SpectrumParameter
   {
     private:
       const Par::Tags my_tag;
       const std::string my_name;
       const std::vector<int> my_shape;

       const std::string my_blockname;
       const int my_blockname_index;
   
     public:
       SpectrumParameter(const Par::Tags tag, const std::string label, const std::vector<int> shape, const std::string blockname, const int blockindex)
         : my_tag(tag)
         , my_name(label)
         , my_shape(shape)
         , my_blockname(blockname)
         , my_blockname_index(blockindex)
       {}
   
       Par::Tags        tag()        const { return my_tag; }
       std::string      name()       const { return my_name; }
       std::vector<int> shape()      const { return my_shape; }

       std::string      blockname()  const { return my_blockname; }
       int              blockindex() const { return my_blockname_index; }
   };
   
   /// Base class for defining the required contents of a SubSpectrum object
   class SubSpectrumContents
   {
      private:
        /// Vector defining what parameters a wrapper must contain
        std::vector<SpectrumParameter> parameters;
    
        /// Name of SubSpectrumContents class (for more helpful error messages)
        std::string my_name;
   
      protected:
        void addParameter(const Par::Tags tag, const std::string& name, const std::vector<int>& shape = initVector(1), const std::string& blockname="", const int index=0);
        void setName(const std::string& name);

      public:
        std::string getName() const {return my_name;}

        /// Function to retreive all parameters
        std::vector<SpectrumParameter> all_parameters() const;

        /// Function to retreive all parameters matching a certain tag
        std::vector<SpectrumParameter> all_parameters_with_tag(Par::Tags tag) const; 

        /// Function to retrieve all parameters matching a certain tag and shape
        std::vector<SpectrumParameter> all_parameters_with_tag_and_shape(Par::Tags tag, std::vector<int>& shape) const; 

        /// Function to retrieve all parameters whose blockName is not SMINPUTS, YUKAWA, CKMBLOCK, or empty.
        std::vector<SpectrumParameter> all_BSM_parameters() const;

        /// Function to verify that a SubSpectrum wrapper contains everything that this class says it should
        void verify_contents(const SubSpectrum& spec) const;
   };

}

#endif
