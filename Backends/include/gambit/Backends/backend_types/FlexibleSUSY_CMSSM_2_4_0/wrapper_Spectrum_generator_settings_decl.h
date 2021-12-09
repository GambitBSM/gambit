#ifndef __wrapper_Spectrum_generator_settings_decl_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_Spectrum_generator_settings_decl_FlexibleSUSY_CMSSM_2_4_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Spectrum_generator_settings.h"
#include <string>
#include <array>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class Spectrum_generator_settings : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static flexiblesusy::Abstract_Spectrum_generator_settings* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void reset();
        
        
                // Wrappers for original constructors: 
            public:
                Spectrum_generator_settings();
        
                // Special pointer-based constructor: 
                Spectrum_generator_settings(flexiblesusy::Abstract_Spectrum_generator_settings* in);
        
                // Copy constructor: 
                Spectrum_generator_settings(const Spectrum_generator_settings& in);
        
                // Assignment operator: 
                Spectrum_generator_settings& operator=(const Spectrum_generator_settings& in);
        
                // Destructor: 
                ~Spectrum_generator_settings();
        
                // Returns correctly casted pointer to Abstract class: 
                flexiblesusy::Abstract_Spectrum_generator_settings* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Spectrum_generator_settings_decl_FlexibleSUSY_CMSSM_2_4_0_h__ */
