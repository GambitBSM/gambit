#ifndef __wrapper_CMSSM_parameter_getter_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_parameter_getter_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <string>
#include <vector>
#include <array>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM_parameter_getter.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class CMSSM_parameter_getter : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_CMSSM_parameter_getter* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                ::std::array<std::basic_string<char>, 111> get_parameter_names() const;
        
                ::std::array<std::basic_string<char>, 18> get_particle_names() const;
        
                ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > get_DRbar_mass_names() const;
        
                ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > get_pole_mass_names() const;
        
                ::std::array<std::basic_string<char>, 289> get_DRbar_mixing_names() const;
        
                ::std::array<std::basic_string<char>, 289> get_pole_mixing_names() const;
        
                ::std::array<std::basic_string<char>, 5> get_input_parameter_names() const;
        
                ::std::array<std::basic_string<char>, 0> get_extra_parameter_names() const;
        
        
                // Wrappers for original constructors: 
            public:
                CMSSM_parameter_getter();
        
                // Special pointer-based constructor: 
                CMSSM_parameter_getter(Abstract_CMSSM_parameter_getter* in);
        
                // Copy constructor: 
                CMSSM_parameter_getter(const CMSSM_parameter_getter& in);
        
                // Assignment operator: 
                CMSSM_parameter_getter& operator=(const CMSSM_parameter_getter& in);
        
                // Destructor: 
                ~CMSSM_parameter_getter();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_CMSSM_parameter_getter* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_parameter_getter_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
