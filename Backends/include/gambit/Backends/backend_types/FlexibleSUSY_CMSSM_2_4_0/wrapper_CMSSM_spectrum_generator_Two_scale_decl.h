#ifndef __wrapper_CMSSM_spectrum_generator_Two_scale_decl_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_CMSSM_spectrum_generator_Two_scale_decl_FlexibleSUSY_CMSSM_2_4_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM_spectrum_generator_Two_scale.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class CMSSM_spectrum_generator_Two_scale : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static flexiblesusy::Abstract_CMSSM_spectrum_generator_Two_scale* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
        
                // Wrappers for original constructors: 
            public:
                CMSSM_spectrum_generator_Two_scale();
        
                // Special pointer-based constructor: 
                CMSSM_spectrum_generator_Two_scale(flexiblesusy::Abstract_CMSSM_spectrum_generator_Two_scale* in);
        
                // Copy constructor: 
                CMSSM_spectrum_generator_Two_scale(const CMSSM_spectrum_generator_Two_scale& in);
        
                // Assignment operator: 
                CMSSM_spectrum_generator_Two_scale& operator=(const CMSSM_spectrum_generator_Two_scale& in);
        
                // Destructor: 
                ~CMSSM_spectrum_generator_Two_scale();
        
                // Returns correctly casted pointer to Abstract class: 
                flexiblesusy::Abstract_CMSSM_spectrum_generator_Two_scale* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_spectrum_generator_Two_scale_decl_FlexibleSUSY_CMSSM_2_4_0_h__ */
