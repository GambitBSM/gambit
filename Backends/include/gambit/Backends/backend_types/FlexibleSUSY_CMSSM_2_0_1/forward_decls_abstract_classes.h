#ifndef __forward_decls_abstract_classes_FlexibleSUSY_CMSSM_2_0_1_h__
#define __forward_decls_abstract_classes_FlexibleSUSY_CMSSM_2_0_1_h__


#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_CMSSM_input_parameters;
        class Abstract_CMSSM_scales;
        class Abstract_CMSSM_slha_io;
        class Abstract_Spectrum_generator_problems;
        class Abstract_CMSSM_mass_eigenstates;
        class Abstract_Model;
        class Abstract_CMSSM_soft_parameters;
        class Abstract_CMSSM_susy_parameters;
        class Abstract_Beta_function;
    }
    namespace softsusy
    {
        class Abstract_QedQcd;
    }
    
    namespace flexiblesusy
    {
        class Abstract_Two_scale;
        class Abstract_CMSSM_spectrum_generator__Two_scale;
        template <class T>
        class Abstract_CMSSM_spectrum_generator_interface;
        class Abstract_Spectrum_generator_settings;
        class Abstract_CMSSM__Two_scale;
    }
    
    
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __forward_decls_abstract_classes_FlexibleSUSY_CMSSM_2_0_1_h__ */
