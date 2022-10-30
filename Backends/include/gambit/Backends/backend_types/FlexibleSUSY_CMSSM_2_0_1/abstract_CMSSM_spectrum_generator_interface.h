#ifndef __abstract_CMSSM_spectrum_generator_interface_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_CMSSM_spectrum_generator_interface_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <string>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_CMSSM__Two_scale_decl.h"
#include "wrapper_Spectrum_generator_problems_decl.h"
#include "wrapper_Spectrum_generator_settings_decl.h"
#include "wrapper_QedQcd_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        template <class T>
        class Abstract_CMSSM_spectrum_generator_interface
        {    };
    
        template <>
        class Abstract_CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale> : public virtual AbstractBase
        {
            public:
    
                virtual flexiblesusy::Abstract_CMSSM<flexiblesusy::Abstract_Two_scale>* get_model__BOSS() const =0;
    
                virtual flexiblesusy::Abstract_Spectrum_generator_problems* get_problems__BOSS() const =0;
    
                virtual double get_reached_precision() const =0;
    
                virtual const flexiblesusy::Abstract_Spectrum_generator_settings& get_settings__BOSS() const =0;
    
                virtual void set_parameter_output_scale(double) =0;
    
                virtual void set_settings__BOSS(const flexiblesusy::Abstract_Spectrum_generator_settings&) =0;
    
                virtual void run__BOSS(const softsusy::Abstract_QedQcd&, const flexiblesusy::Abstract_CMSSM_input_parameters&) =0;
    
                virtual void write_running_couplings(const ::std::basic_string<char>&, double, double) const =0;
    
                virtual void write_spectrum(const ::std::basic_string<char>&) const =0;
    
                virtual void write_spectrum__BOSS() const =0;
    
            private:
                CMSSM_spectrum_generator_interface__Two_scale* wptr;
                bool delete_wrapper;
            public:
                CMSSM_spectrum_generator_interface__Two_scale* get_wptr() { return wptr; }
                void set_wptr(CMSSM_spectrum_generator_interface__Two_scale* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_CMSSM_spectrum_generator_interface()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_spectrum_generator_interface(const Abstract_CMSSM_spectrum_generator_interface&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_spectrum_generator_interface& operator=(const Abstract_CMSSM_spectrum_generator_interface&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                CMSSM_spectrum_generator_interface__Two_scale* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                CMSSM_spectrum_generator_interface__Two_scale& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_CMSSM_spectrum_generator_interface() =0;
        };
    
        typedef Abstract_CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale> Abstract_CMSSM_spectrum_generator_interface__Two_scale;
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"



#endif /* __abstract_CMSSM_spectrum_generator_interface_FlexibleSUSY_CMSSM_2_0_1_h__ */
