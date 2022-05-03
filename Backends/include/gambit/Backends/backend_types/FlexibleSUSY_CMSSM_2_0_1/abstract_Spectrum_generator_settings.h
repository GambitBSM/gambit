#ifndef __abstract_Spectrum_generator_settings_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_Spectrum_generator_settings_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <array>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_Spectrum_generator_settings : public virtual AbstractBase
        {
            public:
    
                enum Settings {
                    precision,
                    max_iterations,
                    solver,
                    calculate_sm_masses,
                    pole_mass_loop_order,
                    ewsb_loop_order,
                    beta_loop_order,
                    threshold_corrections_loop_order,
                    higgs_2loop_correction_at_as,
                    higgs_2loop_correction_ab_as,
                    higgs_2loop_correction_at_at,
                    higgs_2loop_correction_atau_atau,
                    force_output,
                    top_pole_qcd_corrections,
                    beta_zero_threshold,
                    calculate_observables,
                    force_positive_masses,
                    pole_mass_scale,
                    eft_pole_mass_scale,
                    eft_matching_scale,
                    eft_matching_loop_order_up,
                    eft_matching_loop_order_down,
                    eft_higgs_index,
                    calculate_bsm_masses,
                    threshold_corrections,
                    higgs_3loop_ren_scheme_atb_as2,
                    higgs_3loop_correction_at_as2,
                    higgs_3loop_correction_ab_as2,
                    higgs_3loop_correction_at2_as,
                    higgs_3loop_correction_at3,
                    NUMBER_OF_OPTIONS,
                };
    
                virtual double get(Settings) const =0;
    
                virtual ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > get_description(Settings) const =0;
    
                virtual void set(Settings, double) =0;
    
                virtual void reset() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Spectrum_generator_settings*) =0;
                virtual Abstract_Spectrum_generator_settings* pointer_copy__BOSS() =0;
    
            private:
                Spectrum_generator_settings* wptr;
                bool delete_wrapper;
            public:
                Spectrum_generator_settings* get_wptr() { return wptr; }
                void set_wptr(Spectrum_generator_settings* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Spectrum_generator_settings()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Spectrum_generator_settings(const Abstract_Spectrum_generator_settings&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Spectrum_generator_settings& operator=(const Abstract_Spectrum_generator_settings&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Spectrum_generator_settings* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Spectrum_generator_settings& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Spectrum_generator_settings() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Spectrum_generator_settings_FlexibleSUSY_CMSSM_2_0_1_h__ */
