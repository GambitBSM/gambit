#ifndef __wrapper_Error_decl_gm2calc_1_2_0_hpp__
#define __wrapper_Error_decl_gm2calc_1_2_0_hpp__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Error.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      class Error : public WrapperBase
      {
            // Member variables: 
         public:
            // -- Static factory pointers: 
            static Abstract_Error* (*__factory0)();
      
            // -- Other member variables: 
      
            // Member functions: 
         public:
            ::std::basic_string<char> what() const;
      
      
            // Wrappers for original constructors: 
         public:
            Error();
      
            // Special pointer-based constructor: 
            Error(Abstract_Error* in);
      
            // Copy constructor: 
            Error(const Error& in);
      
            // Assignment operator: 
            Error& operator=(const Error& in);
      
            // Destructor: 
            ~Error();
      
            // Returns correctly casted pointer to Abstract class: 
            Abstract_Error* get_BEptr() const;
      
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Error_decl_gm2calc_1_2_0_hpp__ */
