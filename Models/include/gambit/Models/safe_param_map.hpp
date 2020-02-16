//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Simple overlay of std::map that makes [] act
///  like .at(), so that Param map in module
///  functors can give a more customised error.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2014 Dec
///
///  *********************************************


#ifndef __safe_param_map_hpp__
#define __safe_param_map_hpp__

#include "gambit/Utils/standalone_error_handlers.hpp"

#include <map>
#include <stdexcept>

namespace Gambit
{

  namespace Models
  {

    template<typename T>
    class safe_param_map : public std::map<str,T>
    {
      public:
        T& operator[](str key)
        {
          try
          {
            return this->at(key);
          }
          catch(std::out_of_range&)
          {
            model_error().raise("call to [] operator of Param map in a module function", "Requested parameter \""+key+"\" is not available. \n"
                                "Generally this happens because you have requested a parameter of a model that\n"
                                "is not being scanned (check that you are using the ModelInUse() function), or\n"
                                "because you have failed to declare the dependency on the model's parameters  \n"
                                "in your rollcall header using ALLOW_MODEL(S) or ALLOW_MODEL_DEPENDENCE.");
          }
          return this->at(key);  // Will only get here if someone has turned model errors into warnings.  If so, they get what they deserve.
        }
    };

  }

}


#endif //#defined __safe_param_map_hpp
