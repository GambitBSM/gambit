#ifndef __forward_decls_abstract_classes_FlexibleSUSY_CMSSM_2_0_1_h__
#define __forward_decls_abstract_classes_FlexibleSUSY_CMSSM_2_0_1_h__


#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_Two_scale;
        class Abstract_CMSSM_input_parameters;
        template <class T>
        class Abstract_CMSSM_spectrum_generator_interface;
        class Abstract_Spectrum_generator_settings;
        class Abstract_Spectrum_generator_problems;
        class Abstract_Physical_input;
        class Abstract_CMSSM_parameter_getter;
        class Abstract_Error;
    }
    namespace softsusy
    {
        class Abstract_QedQcd;
    }
    
    
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __forward_decls_abstract_classes_FlexibleSUSY_CMSSM_2_0_1_h__ */
