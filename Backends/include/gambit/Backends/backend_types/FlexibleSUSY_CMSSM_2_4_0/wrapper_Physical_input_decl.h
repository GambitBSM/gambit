#ifndef __wrapper_Physical_input_decl_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_Physical_input_decl_FlexibleSUSY_CMSSM_2_4_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Physical_input.h"
#include <array>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class Physical_input : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static flexiblesusy::Abstract_Physical_input* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void reset();
        
        
                // Wrappers for original constructors: 
            public:
                Physical_input();
        
                // Special pointer-based constructor: 
                Physical_input(flexiblesusy::Abstract_Physical_input* in);
        
                // Copy constructor: 
                Physical_input(const Physical_input& in);
        
                // Assignment operator: 
                Physical_input& operator=(const Physical_input& in);
        
                // Destructor: 
                ~Physical_input();
        
                // Returns correctly casted pointer to Abstract class: 
                flexiblesusy::Abstract_Physical_input* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Physical_input_decl_FlexibleSUSY_CMSSM_2_4_0_h__ */
