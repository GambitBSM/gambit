#ifndef __wrapper_CMSSM_spectrum_generator__flexiblesusy::Two_scale_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_spectrum_generator__flexiblesusy::Two_scale_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM_spectrum_generator__flexiblesusy::Two_scale.h"
#include "wrapper_CMSSM_spectrum_generator_interface_decl.h"
#include "wrapper_QedQcd_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        namespace CMSSM_spectrum_generator__flexiblesusy
        {
            
            class CMSSM_spectrum_generator__flexiblesusy::Two_scale : public CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>
            {
                    // Member variables: 
                public:
                    // -- Static factory pointers: 
                    static Abstract_Two_scale* (*__factory0)();
            
                    // -- Other member variables: 
            
                    // Member functions: 
                public:
                    double get_high_scale() const;
            
                    double get_susy_scale() const;
            
                    double get_low_scale() const;
            
                    double get_pole_mass_scale() const;
            
                    void write_running_couplings(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& filename) const;
            
                    void write_running_couplings() const;
            
            
                    // Wrappers for original constructors: 
                public:
                    CMSSM_spectrum_generator__flexiblesusy::Two_scale();
            
                    // Special pointer-based constructor: 
                    CMSSM_spectrum_generator__flexiblesusy::Two_scale(Abstract_Two_scale* in);
            
                    // Copy constructor: 
                    CMSSM_spectrum_generator__flexiblesusy::Two_scale(const CMSSM_spectrum_generator__flexiblesusy::Two_scale& in);
            
                    // Assignment operator: 
                    CMSSM_spectrum_generator__flexiblesusy::Two_scale& operator=(const CMSSM_spectrum_generator__flexiblesusy::Two_scale& in);
            
                    // Destructor: 
                    ~CMSSM_spectrum_generator__flexiblesusy::Two_scale();
            
                    // Returns correctly casted pointer to Abstract class: 
                    Abstract_Two_scale* get_BEptr() const;
            
            };
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_spectrum_generator__flexiblesusy::Two_scale_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
