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

#include "gambit/Models/SpectrumContents/subspectrum_contents.hpp"
#include "gambit/Elements/subspectrum.hpp"
#include "gambit/Utils/stream_overloads.hpp"

namespace Gambit 
{ 
   /// Add a parameter to the Contents object
   void SubSpectrumContents::addParameter(const Par::Tags tag, const std::string& name, const std::vector<int>& shape,
                                          const std::string& blockname, const int blockindex)
   {
     parameters.emplace_back(tag,name,shape,blockname,blockindex);
   }

   /// Set the name of this Contents object (i.e. the name of the model to which this spectrum data applies) 
   void SubSpectrumContents::setName(const std::string& name)
   {
     my_name = name;
   }

   /// Function to retreive all parameters
   std::vector<SpectrumParameter> SubSpectrumContents::all_parameters() const 
   {
     return parameters; 
   }
   
   /// Function to retreive all parameters matching a certain tag
   std::vector<SpectrumParameter> SubSpectrumContents::all_parameters_with_tag(Par::Tags tag) const
   {
     std::vector<SpectrumParameter> search_result;
     for( std::vector<SpectrumParameter>::const_iterator it=parameters.begin(); it!=parameters.end(); ++it )
     {
       if(it->tag() == tag) search_result.push_back(*it);        
     }
     return search_result; 
   }
   
   /// Function to retrieve all parameters matching a certain tag and shape
   std::vector<SpectrumParameter> SubSpectrumContents::all_parameters_with_tag_and_shape(Par::Tags tag, std::vector<int>& shape) const
   {
     std::vector<SpectrumParameter> search_result;
     for( std::vector<SpectrumParameter>::const_iterator it=parameters.begin(); it!=parameters.end(); ++it )
     {
       if(it->tag() == tag and it->shape() == shape) search_result.push_back(*it);        
     }
     return search_result; 
   }

   /// Function to retrieve all parameters whose blockname is not SMINPUTS, YUKAWA, CKMBLOCK, or empty.
   std::vector<SpectrumParameter> SubSpectrumContents::all_BSM_parameters() const
   {
    std::vector<SpectrumParameter> search_result;
    for ( std::vector<SpectrumParameter>::const_iterator it=parameters.begin(); it!=parameters.end(); ++it)
    {
      if(it->blockname() != "SMINPUTS" || it->blockname() != "YUKAWA" || it->blockname() != "CKMBLOCK" || it->blockname() != "")
      {
        search_result.push_back(*it);
      }
    }
    return search_result;
   }


   /// Verify that the supplied SubSpectrum object conforms to the requirements specified by the Contents class
   void SubSpectrumContents::verify_contents(const SubSpectrum& spec) const
   {
      const std::vector<SpectrumParameter> required_parameters = all_parameters();
      
      for(std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin();
           it != required_parameters.end(); ++it)
      {
         const Par::Tags        tag   = it->tag();
         const std::string      name  = it->name();
         const std::vector<int> shape = it->shape();

         // Deal with empty shape case
         if(shape.size()==0)
         {
           // ERROR, please use length 1 vector for scalar case
           std::ostringstream errmsg;           
           errmsg << "Error while verifying contents of SubSpectrum object against SubSpectrumContents object with name \""<<my_name<<"\" !" << std::endl;
           errmsg << "Encountered a required parameter ("<<Par::toString.at(tag)<<", "<<name<<") with shape.size()==0. This is not allowed; if you want this parameter to be considered a scalar, please set the shape to '1', i.e. std::vector<int> shape = initVector(1). Please fix this parameter in the SubSpectrumContents class." << std::endl;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
         // Check scalar case
         else if(shape.size()==1 and shape[0]==1)
         {
           if(not spec.has(tag,name))
           {
             // ERROR, Required parameter not found
             std::ostringstream errmsg;           
             errmsg << "Error while verifying contents of SubSpectrum object against SubSpectrumContents object with name \""<<my_name<<"\" !" << std::endl;
             errmsg << "Required scalar-valued parameter ("<<Par::toString.at(tag)<<", "<<name<<") is not accessible via subspectrum->get(Par::"<<Par::toString.at(tag)<<", \""<<name<<"\"). Please fix the relevant SubSpectrum wrapper class so that this parameter can be accessed." << std::endl;
             utils_error().forced_throw(LOCAL_INFO,errmsg.str());
           }
         }
         // Check vector case
         else if(shape.size()==1 and shape[0]>1)
         {
           if(shape[0]<0)
           {
             // ERROR, asked for negative length vector
             std::ostringstream errmsg;           
             errmsg << "Error while verifying contents of SubSpectrum object against SubSpectrumContents object with name \""<<my_name<<"\" !" << std::endl;
             errmsg << "Encountered a vector-valued required parameter ("<<Par::toString.at(tag)<<", "<<name<<") with negative required length ("<<shape[0]<<")! This is invalid; Please fix this parameter in the SubSpectrumContents class so that the required length is a positive number." << std::endl;
             utils_error().forced_throw(LOCAL_INFO,errmsg.str());
           }
           else
           { 
             for(int i = 1; i<=shape[0]; ++i) {
               if(not spec.has(tag,name,i))
               {
                 // ERROR, Required parameter not found
                 std::ostringstream errmsg;           
                 errmsg << "Error while verifying contents of SubSpectrum object against SubSpectrumContents object with name \""<<my_name<<"\" !" << std::endl;
                 errmsg << "An entry of the required vector-valued parameter ("<<Par::toString.at(tag)<<", "<<name<<") with required length "<<shape[0]<<" is not accessible via subspectrum->get(Par::"<<Par::toString.at(tag)<<", \""<<name<<"\", "<<i<<"). Please fix the relevant SubSpectrum wrapper class so that this parameter can be accessed. Keep in mind that you may need to override index_offset() to align the expected indices." << std::endl;
                 utils_error().forced_throw(LOCAL_INFO,errmsg.str());
               }            
             }
           }  
         }
         // Check matrix case
         else if(shape.size()==2)
         {
           if(shape[0]<0 or shape[1]<0)
           {
             // ERROR, asked for negative matrix dimensions
             std::ostringstream errmsg;           
             errmsg << "Error while verifying contents of SubSpectrum object against SubSpectrumContents object with name \""<<my_name<<"\" !" << std::endl;
             errmsg << "Encountered a matrix-valued required parameter ("<<Par::toString.at(tag)<<", "<<name<<") with at least one negative required dimension (dims = ["<<shape[0]<<", "<<shape[1]<<"])! This is invalid; Please fix the shape settings for this parameter in the SubSpectrumContents so that they are positive numbers." << std::endl;
             utils_error().forced_throw(LOCAL_INFO,errmsg.str());
           }
           else
           {
             for(int i = 1; i<=shape[0]; ++i) {
               for(int j = 1; j<=shape[0]; ++j) {
                  if(not spec.has(tag,name,i,j))
                  {
                    // ERROR, Required parameter not found
                    std::ostringstream errmsg;           
                    errmsg << "Error while verifying contents of SubSpectrum object against SubSpectrumContents object with name \""<<my_name<<"\" !" << std::endl;
                    errmsg << "An entry of the required matrix-valued parameter ("<<Par::toString.at(tag)<<", "<<name<<") with required dimensions ("<<shape[0]<<", "<<shape[1]<<") is not accessible via subspectrum->get(Par::"<<Par::toString.at(tag)<<", \""<<name<<"\", "<<i<<", "<<j<<"). Please fix the relevant SubSpectrum wrapper class so that this parameter can be accessed. Keep in mind that you may need to override index_offset() to align the expected indices." << std::endl;
                    utils_error().forced_throw(LOCAL_INFO,errmsg.str());
                  }            
               }
             }  
           }
         }
         // Deal with all other cases
         else
         {
           // ERROR invalid shape
           std::ostringstream errmsg;           
           errmsg << "Error while verifying contents of SubSpectrum object against SubSpectrumContents object with name \""<<my_name<<"\" !" << std::endl;
           errmsg << "The specified shape for the required parameter ("<<Par::toString.at(tag)<<", "<<name<<") is invalid. The length of the shape vector is only permitted to be 1 or 2 (received shape vector was "<<shape<<"). Please fix this parameter entry in the SubSpectrumContents class."<<std::endl;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
      }
      // End constructor
   }
   /// @}

}

