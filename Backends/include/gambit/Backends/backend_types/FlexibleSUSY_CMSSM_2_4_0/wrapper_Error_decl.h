#ifndef __wrapper_Error_decl_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_Error_decl_FlexibleSUSY_CMSSM_2_4_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Error.h"
#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class Error : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static flexiblesusy::Abstract_Error* (*__factory0)(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >&);
                static flexiblesusy::Abstract_Error* (*__factory1)(const char*);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > what_detailed() const;
        
        
                // Wrappers for original constructors: 
            public:
                Error(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& msg);
                Error(const char* msg);
        
                // Special pointer-based constructor: 
                Error(flexiblesusy::Abstract_Error* in);
        
                // Copy constructor: 
                Error(const Error& in);
        
                // Assignment operator: 
                Error& operator=(const Error& in);
        
                // Destructor: 
                ~Error();
        
                // Returns correctly casted pointer to Abstract class: 
                flexiblesusy::Abstract_Error* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Error_decl_FlexibleSUSY_CMSSM_2_4_0_h__ */
