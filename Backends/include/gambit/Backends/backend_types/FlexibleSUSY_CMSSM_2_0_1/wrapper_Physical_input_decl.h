#ifndef __wrapper_Physical_input_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_Physical_input_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <array>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Physical_input.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class Physical_input : public WrapperBase
        {
                // Types: 
            public:
                typedef flexiblesusy::Abstract_Physical_input::Input Input;
                static constexpr Input alpha_em_0 = flexiblesusy::Abstract_Physical_input::alpha_em_0;
        
                static constexpr Input mh_pole = flexiblesusy::Abstract_Physical_input::mh_pole;
        
                static constexpr Input NUMBER_OF_INPUT_PARAMETERS = flexiblesusy::Abstract_Physical_input::NUMBER_OF_INPUT_PARAMETERS;
        
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Physical_input* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                double get(flexiblesusy::Abstract_Physical_input::Input arg_1) const;
        
                void set(flexiblesusy::Abstract_Physical_input::Input arg_1, double arg_2);
        
                void reset();
        
        
                // Wrappers for original constructors: 
            public:
                Physical_input();
        
                // Special pointer-based constructor: 
                Physical_input(Abstract_Physical_input* in);
        
                // Copy constructor: 
                Physical_input(const Physical_input& in);
        
                // Assignment operator: 
                Physical_input& operator=(const Physical_input& in);
        
                // Destructor: 
                ~Physical_input();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Physical_input* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Physical_input_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
