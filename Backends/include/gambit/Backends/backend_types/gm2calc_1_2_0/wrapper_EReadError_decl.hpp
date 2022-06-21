#ifndef __wrapper_EReadError_decl_gm2calc_1_2_0_hpp__
#define __wrapper_EReadError_decl_gm2calc_1_2_0_hpp__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_EReadError.hpp"
#include "wrapper_Error_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      class EReadError : public Error
      {
            // Member variables: 
         public:
            // -- Static factory pointers: 
            static Abstract_EReadError* (*__factory0)(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >&);
      
            // -- Other member variables: 
      
            // Member functions: 
         public:
            ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > what() const;
      
      
            // Wrappers for original constructors: 
         public:
            EReadError(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& message_);
      
            // Special pointer-based constructor: 
            EReadError(Abstract_EReadError* in);
      
            // Copy constructor: 
            EReadError(const EReadError& in);
      
            // Assignment operator: 
            EReadError& operator=(const EReadError& in);
      
            // Destructor: 
            ~EReadError();
      
            // Returns correctly casted pointer to Abstract class: 
            Abstract_EReadError* get_BEptr() const;
      
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_EReadError_decl_gm2calc_1_2_0_hpp__ */
