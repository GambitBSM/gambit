#ifndef __wrapper_Two_scale_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_Two_scale_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Two_scale.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class Two_scale : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Two_scale* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
        
                // Wrappers for original constructors: 
            public:
                Two_scale();
        
                // Special pointer-based constructor: 
                Two_scale(Abstract_Two_scale* in);
        
                // Copy constructor: 
                Two_scale(const Two_scale& in);
        
                // Assignment operator: 
                Two_scale& operator=(const Two_scale& in);
        
                // Destructor: 
                ~Two_scale();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Two_scale* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Two_scale_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
