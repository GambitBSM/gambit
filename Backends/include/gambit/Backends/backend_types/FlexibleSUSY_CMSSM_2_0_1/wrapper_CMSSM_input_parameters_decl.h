#ifndef __wrapper_CMSSM_input_parameters_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_input_parameters_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM_input_parameters.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class CMSSM_input_parameters : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static flexiblesusy::Abstract_CMSSM_input_parameters* (*__factory0)();
        
                // -- Other member variables: 
            public:
                double& m0;
                double& m12;
                double& TanBeta;
                int& SignMu;
                double& Azero;
        
                // Member functions: 
        
                // Wrappers for original constructors: 
            public:
                CMSSM_input_parameters();
        
                // Special pointer-based constructor: 
                CMSSM_input_parameters(flexiblesusy::Abstract_CMSSM_input_parameters* in);
        
                // Copy constructor: 
                CMSSM_input_parameters(const CMSSM_input_parameters& in);
        
                // Assignment operator: 
                CMSSM_input_parameters& operator=(const CMSSM_input_parameters& in);
        
                // Destructor: 
                ~CMSSM_input_parameters();
        
                // Returns correctly casted pointer to Abstract class: 
                flexiblesusy::Abstract_CMSSM_input_parameters* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_input_parameters_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
