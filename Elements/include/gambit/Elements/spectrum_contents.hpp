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
///  \date 2016 Feb, 2019 June
///
///  *********************************************

#ifndef __spectrum_contents_hpp__ 
#define __spectrum_contents_hpp__ 

#include "gambit/Elements/spectrum_helpers.hpp"
#include "gambit/Utils/variadic_functions.hpp"

namespace SLHAea { class Coll; } // Forward declaration

namespace Gambit { 

   class Spectrum;
   typedef class SLHAea::Coll SLHAstruct;

   namespace SpectrumContents {

       /// Simple class to contain information defining how some parameter in a Spectrum object can be accessed
       class Parameter
       {
         private:
           const Par::Tags my_tag;
           const std::string my_name;
           const std::vector<int> my_shape;

           const std::string my_blockname;
           const int my_blockname_index;
       
         public:
           Parameter(const Par::Tags tag, const std::string label, const std::vector<int> shape, const std::string blockname, const int blockindex)
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

           /// Function to retrieve all valid indices for this parameter
           /// Returns them in the most general form, vector of vectors, regardless of actual shape
           std::vector<std::vector<int>> allowed_indices();
       };

       /// Base class for defining the required contents of a SubSpectrum object
       class Contents
       {
          private:
            /// Type to use for parameter map lookup keys
            typedef std::pair<Par::Tags, std::string> parameter_key;

            /// Vector defining what parameters a wrapper must contain
            std::map<parameter_key,Parameter> parameters;
        
            /// Name of SubSpectrumContents class (for more helpful error messages)
            std::string my_name;
       
            /// Typedefs for transform function signatures
            typedef SLHAstruct (*inputTfunc)(const SLHAstruct&);
            typedef SLHAstruct (*outputTfunc)(const Spectrum&, const int);

            /// Pointers to transform functions
            inputTfunc  inputTransform;
            outputTfunc outputTransform;

          protected:
            /// Define a new parameter requirement
            void addParameter(const Par::Tags tag, const std::string& name, const std::vector<int>& shape, const std::string& blockname, const int index=1);

            /// Import all parameter definitions from another Contents object
            void addAllFrom(const Contents& other);

            /// Constructor; sets name of contents object
            Contents(const std::string& name);
            
          public:
            // Default constructor. Should not be used by Derived classes, they should set a name!
            Contents();

            std::string getName() const {return my_name;}

            /// Function to check if a parameter definition exists in this object, identified by tag and string name
            bool has_parameter(const Par::Tags tag, const std::string& name) const;

            /// Function to check if a parameter definition exists in this object, this time also checking the index shape
            bool has_parameter(const Par::Tags tag, const std::string& name, const std::vector<int>& indices) const;

            /// Function to retrieve a version of the parameter name and indices that exists in this Contents object
            /// i.e. attempts conversions based on particle database
            std::pair<std::string,std::vector<int>> find_matching_parameter(const Par::Tags tag, const std::string& name, const std::vector<int>& indices, bool& success) const;

            /// Function to get definition information for one parameter, identified by tag and string name
            Parameter get_parameter(const Par::Tags tag, const std::string& name) const;

            /// Function to get indices in SLHAea block in which requested index item can be found
            std::pair<std::string,std::vector<int>> get_SLHA_indices(const Par::Tags tag, const std::string& name, std::vector<int> indices) const;

            /// Function to retreive all parameters
            std::vector<Parameter> all_parameters() const;
        
            /// Function to retreive all parameters matching a certain tag
            std::vector<Parameter> all_parameters_with_tag(Par::Tags tag) const; 

            /// Function to retrieve all parameters matching a certain tag and shape
            std::vector<Parameter> all_parameters_with_tag_and_shape(Par::Tags tag, std::vector<int>& shape) const; 

            /// Function to retrieve all parameters whose blockName is not SMINPUTS, YUKAWA, CKMBLOCK, or empty.
            std::vector<Parameter> all_BSM_parameters() const;

            /// Function to verify that a SubSpectrum wrapper contains everything that this class says it should
            void verify_contents(const Spectrum& spec) const;

            /// Create template SLHAea object to match this SpectrumContents: mainly used to help Spectrum object creators to know what exactly is required in the SLHAea objects for a given SpectrumContents, and to run tests.
            SLHAstruct create_template_SLHAea(const int version) const;
            
            /// Create template SLHA file to match this SpectrumContents
            void create_template_SLHA_file(const std::string& filename, const int version) const;

            /// Perform transformations on input 'Standard' SLHAea object to make it conform to this Contents definition
            /// E.g. for transforming SLHA-standard information into our internally required format
            /// A function pointer to a function doing this transformation should be set in the derived Contents 
            /// constructor using setInputTransform;
            SLHAstruct transformInputSLHAea(const SLHAstruct& input, bool ignore_input_transform=false) const;

            /// Obtain SLHA-compliant (or similar) SLHAea object from spectrum object.
            /// E.g. for transformation internal SLHA-like format of Spectrum objects back into SLHA-compliant format
            /// To be overridden in model-specific derived classes, if needed
            /// Can take an integer specifying version of standard to use.
            /// A function pointer to a function doing this transformation should be set in the derived Contents 
            /// constructor using setOutputTransform;
            SLHAstruct generateOutputSLHAea(const Spectrum& spec, const int version) const;

            /// Setters for transform functions
            void setInputTransform(const inputTfunc);
            void setOutputTransform(const outputTfunc);
       };
    }
}

#endif
