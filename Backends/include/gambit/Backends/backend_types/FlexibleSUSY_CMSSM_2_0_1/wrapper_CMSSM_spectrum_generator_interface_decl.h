#ifndef __wrapper_CMSSM_spectrum_generator_interface_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_spectrum_generator_interface_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM_spectrum_generator_interface.h"
#include "wrapper_Spectrum_generator_problems_decl.h"
#include "wrapper_Spectrum_generator_settings_decl.h"
#include "wrapper_QedQcd_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        template <>
        class CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale> : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                flexiblesusy::Spectrum_generator_problems get_problems() const;
        
                double get_reached_precision() const;
        
                const flexiblesusy::Spectrum_generator_settings& get_settings() const;
        
                void set_parameter_output_scale(double s);
        
                void set_settings(const flexiblesusy::Spectrum_generator_settings& arg_1);
        
                void run(const softsusy::QedQcd& arg_1, const flexiblesusy::CMSSM_input_parameters& arg_2);
        
                void write_running_couplings(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& filename, double arg_1, double arg_2) const;
        
                void write_spectrum(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& filename) const;
        
                void write_spectrum() const;
        
        
                // Wrappers for original constructors: 
            public:
                CMSSM_spectrum_generator_interface();
        
                // Special pointer-based constructor: 
                CMSSM_spectrum_generator_interface(Abstract_CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>* in);
        
                // Copy constructor: 
                CMSSM_spectrum_generator_interface(const CMSSM_spectrum_generator_interface& in);
        
                // Assignment operator: 
                CMSSM_spectrum_generator_interface& operator=(const CMSSM_spectrum_generator_interface& in);
        
                // Destructor: 
                ~CMSSM_spectrum_generator_interface();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_spectrum_generator_interface_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
