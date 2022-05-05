#ifndef __wrapper_Spectrum_generator_settings_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_Spectrum_generator_settings_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <string>
#include <array>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Spectrum_generator_settings.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class Spectrum_generator_settings : public WrapperBase
        {
                // Types: 
            public:
                typedef flexiblesusy::Abstract_Spectrum_generator_settings::Settings Settings;
                static constexpr Settings precision = flexiblesusy::Abstract_Spectrum_generator_settings::precision;
        
                static constexpr Settings max_iterations = flexiblesusy::Abstract_Spectrum_generator_settings::max_iterations;
        
                static constexpr Settings solver = flexiblesusy::Abstract_Spectrum_generator_settings::solver;
        
                static constexpr Settings calculate_sm_masses = flexiblesusy::Abstract_Spectrum_generator_settings::calculate_sm_masses;
        
                static constexpr Settings pole_mass_loop_order = flexiblesusy::Abstract_Spectrum_generator_settings::pole_mass_loop_order;
        
                static constexpr Settings ewsb_loop_order = flexiblesusy::Abstract_Spectrum_generator_settings::ewsb_loop_order;
        
                static constexpr Settings beta_loop_order = flexiblesusy::Abstract_Spectrum_generator_settings::beta_loop_order;
        
                static constexpr Settings threshold_corrections_loop_order = flexiblesusy::Abstract_Spectrum_generator_settings::threshold_corrections_loop_order;
        
                static constexpr Settings higgs_2loop_correction_at_as = flexiblesusy::Abstract_Spectrum_generator_settings::higgs_2loop_correction_at_as;
        
                static constexpr Settings higgs_2loop_correction_ab_as = flexiblesusy::Abstract_Spectrum_generator_settings::higgs_2loop_correction_ab_as;
        
                static constexpr Settings higgs_2loop_correction_at_at = flexiblesusy::Abstract_Spectrum_generator_settings::higgs_2loop_correction_at_at;
        
                static constexpr Settings higgs_2loop_correction_atau_atau = flexiblesusy::Abstract_Spectrum_generator_settings::higgs_2loop_correction_atau_atau;
        
                static constexpr Settings force_output = flexiblesusy::Abstract_Spectrum_generator_settings::force_output;
        
                static constexpr Settings top_pole_qcd_corrections = flexiblesusy::Abstract_Spectrum_generator_settings::top_pole_qcd_corrections;
        
                static constexpr Settings beta_zero_threshold = flexiblesusy::Abstract_Spectrum_generator_settings::beta_zero_threshold;
        
                static constexpr Settings calculate_observables = flexiblesusy::Abstract_Spectrum_generator_settings::calculate_observables;
        
                static constexpr Settings force_positive_masses = flexiblesusy::Abstract_Spectrum_generator_settings::force_positive_masses;
        
                static constexpr Settings pole_mass_scale = flexiblesusy::Abstract_Spectrum_generator_settings::pole_mass_scale;
        
                static constexpr Settings eft_pole_mass_scale = flexiblesusy::Abstract_Spectrum_generator_settings::eft_pole_mass_scale;
        
                static constexpr Settings eft_matching_scale = flexiblesusy::Abstract_Spectrum_generator_settings::eft_matching_scale;
        
                static constexpr Settings eft_matching_loop_order_up = flexiblesusy::Abstract_Spectrum_generator_settings::eft_matching_loop_order_up;
        
                static constexpr Settings eft_matching_loop_order_down = flexiblesusy::Abstract_Spectrum_generator_settings::eft_matching_loop_order_down;
        
                static constexpr Settings eft_higgs_index = flexiblesusy::Abstract_Spectrum_generator_settings::eft_higgs_index;
        
                static constexpr Settings calculate_bsm_masses = flexiblesusy::Abstract_Spectrum_generator_settings::calculate_bsm_masses;
        
                static constexpr Settings threshold_corrections = flexiblesusy::Abstract_Spectrum_generator_settings::threshold_corrections;
        
                static constexpr Settings higgs_3loop_ren_scheme_atb_as2 = flexiblesusy::Abstract_Spectrum_generator_settings::higgs_3loop_ren_scheme_atb_as2;
        
                static constexpr Settings higgs_3loop_correction_at_as2 = flexiblesusy::Abstract_Spectrum_generator_settings::higgs_3loop_correction_at_as2;
        
                static constexpr Settings higgs_3loop_correction_ab_as2 = flexiblesusy::Abstract_Spectrum_generator_settings::higgs_3loop_correction_ab_as2;
        
                static constexpr Settings higgs_3loop_correction_at2_as = flexiblesusy::Abstract_Spectrum_generator_settings::higgs_3loop_correction_at2_as;
        
                static constexpr Settings higgs_3loop_correction_at3 = flexiblesusy::Abstract_Spectrum_generator_settings::higgs_3loop_correction_at3;
        
                static constexpr Settings NUMBER_OF_OPTIONS = flexiblesusy::Abstract_Spectrum_generator_settings::NUMBER_OF_OPTIONS;
        
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Spectrum_generator_settings* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                double get(flexiblesusy::Abstract_Spectrum_generator_settings::Settings arg_1) const;
        
                ::std::basic_string<char> get_description(flexiblesusy::Abstract_Spectrum_generator_settings::Settings arg_1) const;
        
                void set(flexiblesusy::Abstract_Spectrum_generator_settings::Settings arg_1, double arg_2);
        
                void reset();
        
        
                // Wrappers for original constructors: 
            public:
                Spectrum_generator_settings();
        
                // Special pointer-based constructor: 
                Spectrum_generator_settings(Abstract_Spectrum_generator_settings* in);
        
                // Copy constructor: 
                Spectrum_generator_settings(const Spectrum_generator_settings& in);
        
                // Assignment operator: 
                Spectrum_generator_settings& operator=(const Spectrum_generator_settings& in);
        
                // Destructor: 
                ~Spectrum_generator_settings();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Spectrum_generator_settings* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Spectrum_generator_settings_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
