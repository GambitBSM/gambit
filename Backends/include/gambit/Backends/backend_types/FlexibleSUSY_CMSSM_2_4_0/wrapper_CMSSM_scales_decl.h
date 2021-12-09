#ifndef __wrapper_CMSSM_scales_decl_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_CMSSM_scales_decl_FlexibleSUSY_CMSSM_2_4_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM_scales.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class CMSSM_scales : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static flexiblesusy::Abstract_CMSSM_scales* (*__factory0)();
        
                // -- Other member variables: 
            public:
                double& HighScale;
                double& SUSYScale;
                double& LowScale;
                double& pole_mass_scale;
        
                // Member functions: 
        
                // Wrappers for original constructors: 
            public:
                CMSSM_scales();
        
                // Special pointer-based constructor: 
                CMSSM_scales(flexiblesusy::Abstract_CMSSM_scales* in);
        
                // Copy constructor: 
                CMSSM_scales(const CMSSM_scales& in);
        
                // Assignment operator: 
                CMSSM_scales& operator=(const CMSSM_scales& in);
        
                // Destructor: 
                ~CMSSM_scales();
        
                // Returns correctly casted pointer to Abstract class: 
                flexiblesusy::Abstract_CMSSM_scales* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_scales_decl_FlexibleSUSY_CMSSM_2_4_0_h__ */
