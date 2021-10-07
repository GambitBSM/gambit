//  *********************************************
//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions for ModelParameters class. 
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Johan Lundberg (SUfit version; model_types.hpp)
///  \date 2011 Jul - Aug
///
///  \author Ben Farmer
///  \date 2013 May, Jun 
///  \date 2014 Aug 
///  \date 2015 Aug
///
///  \author Pat Scott  
///          (p.scott@imperial.ac.uk)
///  \date 2013 Oct
///  \date 2014 Jan, Nov
///  \date 2015 Sep
///
///  *********************************************


#include <map>
#include <iostream>
#include <sstream>

#include "gambit/Utils/model_parameters.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/local_info.hpp"
#include "gambit/Elements/functors.hpp"
#include "gambit/Models/claw_singleton.hpp"
#include "gambit/Core/core_singleton.hpp"

namespace Gambit 
{

   /// ModelParameters class member function definitions
 
   /// Checks if this model container holds a parameter matching the supplied name
   void ModelParameters::assert_contains(std::string inkey) const
   {
     if(not has(inkey)) 
     { 
       model_error().raise(LOCAL_INFO, "ModelParameters object (with name "+getModelName()+") does not contain the requested parameter '"+inkey+"'.");
     }
   }

   /// Check if a parameter exists in this object
   bool ModelParameters::has(const std::string& inkey) const
   {
      return (_values.count(inkey)!=0);
   }


   /// Default constructor
   ModelParameters::ModelParameters(): _values(), modelname("None"), outputname("None") {}

   /// Constructor using vector of strings
   ModelParameters::ModelParameters(const std::vector<std::string> &paramlist): _values(), modelname("None"), outputname("None") 
   {
     _definePars(paramlist);
   }
   
   /// Constructor using array of char arrays
   ModelParameters::ModelParameters(const char** paramlist): _values(), modelname("None"), outputname("None") 
   {
     _definePars(paramlist);
   }
 
   /// Get value of named parameter 
   double ModelParameters::getValue(std::string const & inkey) const
   {
     assert_contains(inkey);
     return _values.at(inkey);
   }
   
   /// Get values of all parameters
   const std::map<std::string, double>& ModelParameters::getValues() const
   {
     return _values;
   }
   
   /// Get a const iterator to the first parameter map entry
   std::map<std::string, double>::const_iterator ModelParameters::begin() const
   {
     return getValues().begin();
   }
  
   /// Get a const iterator to the last parameter map entry
   std::map<std::string, double>::const_iterator ModelParameters::end() const
   {
     return getValues().end();
   }

   /// Get number of parameters stored in this object
   int ModelParameters::getNumberOfPars() const
   {
     return _values.size();
   }

   /// Get parameter value using bracket operator
   const double & ModelParameters::operator[](std::string const & inkey) const
   {
     assert_contains(inkey);
     return _values.at(inkey);
   }

   /// Get parameter value using 'at' operator
   /// This is no different to the bracket operator method,
   /// since keys cannot be added with the bracket method anyhow,
   /// but for people who are used to maps it is nice to have.
   const double & ModelParameters::at(std::string const & inkey) const
   {
     assert_contains(inkey);
     return _values.at(inkey);
   }


   /// Set single parameter value
   void ModelParameters::setValue(std::string const &inkey,double const&value)
   {
     assert_contains(inkey);
     _values[inkey]=value;
   }
  
   /// Set many parameter values using another ModelParameters object
   void ModelParameters::setValues(ModelParameters const& donor, bool missing_is_error)
   {
     setValues(donor.getValues(), missing_is_error); 
   }

   /// Set many parameter values using a map
   void ModelParameters::setValues(std::map<std::string,double> const& params_map, bool missing_is_error)
   {
     typedef std::map<std::string,double>::const_iterator it_type;
     for(it_type iterator = params_map.begin();
         iterator != params_map.end(); 
         iterator++)
     {
       // iterator->first = key
       // iterator->second = value
       if (missing_is_error) assert_contains(iterator->first);
       if (_values.count(iterator->first)==1) _values[iterator->first]=iterator->second;
     }
   }

   /// Get parameter keys (names), probably for external iteration
   std::vector<std::string> ModelParameters::getKeys() const
   {
     std::vector<std::string> parnames;
     for (std::map<std::string,double>::const_iterator it=_values.begin();it!=_values.end();it++)
     {
       parnames.push_back((*it).first);
     }
     return parnames;
   }

   /// Dump parameter names and values to stdout (should be for debugging only)
   void ModelParameters::print() const
   {
     std::cout << "ModelParameters: Printing: "<<std::endl;
     for (std::map<std::string,double>::const_iterator it=_values.begin();it!=_values.end();it++)
     {
       std::cout << "parameter: " << it->first << "; value: "<<it->second<<std::endl ;
     }
   }

   /// Define a parameter with name, value (i.e. add to internal map). Value is initialised to zero
   void ModelParameters::_definePar(const std::string &newkey)
   {
     _values[newkey]=0.;
   }

   /// Define many new parameters at once via a vector of names
   void ModelParameters::_definePars(const std::vector<std::string> &v)
   {
     for(std::vector<std::string>::const_iterator it = v.begin(); it != v.end(); ++it)
     {
       _definePar(*it);
     }
   }

   /// Define many new parameters at once via an array of char arrays
   void ModelParameters::_definePars(const char** array)
   {
     int i = 0;
     while (array[i] != 0)
     {
       _definePar(array[i]);
       i++;
     }
   }

   /// Getters/setters for model and output names
   std::string ModelParameters::getModelName() const  { return modelname; }
   std::string ModelParameters::getOutputName() const { return outputname; }
   void ModelParameters::setModelName (const std::string& in) { modelname = in; }
   void ModelParameters::setOutputName(const std::string& in) { outputname = in; }

} //end Gambit namespace
