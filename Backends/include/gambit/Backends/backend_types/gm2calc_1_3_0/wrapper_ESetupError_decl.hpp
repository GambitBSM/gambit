#ifndef __wrapper_ESetupError_decl_gm2calc_1_3_0_hpp__
#define __wrapper_ESetupError_decl_gm2calc_1_3_0_hpp__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ESetupError.hpp"
#include "wrapper_Error_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      class ESetupError : public Error
      {
            // Member variables: 
         public:
            // -- Static factory pointers: 
            static Abstract_ESetupError* (*__factory0)(const ::std::basic_string<char>&);
      
            // -- Other member variables: 
      
            // Member functions: 
         public:
            ::std::basic_string<char> what() const;
      
      
            // Wrappers for original constructors: 
         public:
            ESetupError(const ::std::basic_string<char>& message_);
      
            // Special pointer-based constructor: 
            ESetupError(Abstract_ESetupError* in);
      
            // Copy constructor: 
            ESetupError(const ESetupError& in);
      
            // Assignment operator: 
            ESetupError& operator=(const ESetupError& in);
      
            // Destructor: 
            ~ESetupError();
      
            // Returns correctly casted pointer to Abstract class: 
            Abstract_ESetupError* get_BEptr() const;
      
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ESetupError_decl_gm2calc_1_3_0_hpp__ */
