#ifndef __wrapper_CMSSM_spectrum_generator_interface_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_spectrum_generator_interface_def_FlexibleSUSY_CMSSM_2_0_1_h__

#include <string>
#include "wrapper_Spectrum_generator_problems_decl.h"
#include "wrapper_Spectrum_generator_settings_decl.h"
#include "wrapper_QedQcd_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline flexiblesusy::Spectrum_generator_problems CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::get_problems() const
        {
            return flexiblesusy::Spectrum_generator_problems( const_cast<const Abstract_CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>*>(get_BEptr())->get_problems__BOSS() );
        }
        
        inline double CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::get_reached_precision() const
        {
            return get_BEptr()->get_reached_precision();
        }
        
        inline const flexiblesusy::Spectrum_generator_settings& CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::get_settings() const
        {
            return const_cast<flexiblesusy::Abstract_Spectrum_generator_settings&>(const_cast<const Abstract_CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>*>(get_BEptr())->get_settings__BOSS()).get_init_wref();
        }
        
        inline void CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::set_parameter_output_scale(double s)
        {
            get_BEptr()->set_parameter_output_scale(s);
        }
        
        inline void CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::set_settings(const flexiblesusy::Spectrum_generator_settings& arg_1)
        {
            get_BEptr()->set_settings__BOSS(*arg_1.get_BEptr());
        }
        
        inline void CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::run(const softsusy::QedQcd& arg_1, const flexiblesusy::CMSSM_input_parameters& arg_2)
        {
            get_BEptr()->run__BOSS(*arg_1.get_BEptr(), *arg_2.get_BEptr());
        }
        
        inline void CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::write_running_couplings(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& filename, double arg_1, double arg_2) const
        {
            get_BEptr()->write_running_couplings(filename, arg_1, arg_2);
        }
        
        inline void CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::write_spectrum(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& filename) const
        {
            get_BEptr()->write_spectrum(filename);
        }
        
        inline void CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::write_spectrum() const
        {
            get_BEptr()->write_spectrum__BOSS();
        }
        
        
        // Wrappers for original constructors: 
        inline CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::CMSSM_spectrum_generator_interface() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::CMSSM_spectrum_generator_interface(Abstract_CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::CMSSM_spectrum_generator_interface(const CMSSM_spectrum_generator_interface& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>& CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::operator=(const CMSSM_spectrum_generator_interface& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::~CMSSM_spectrum_generator_interface()
        {
            if (get_BEptr() != 0)
            {
                get_BEptr()->set_delete_wrapper(false);
                if (can_delete_BEptr())
                {
                    delete BEptr;
                    BEptr = 0;
                }
            }
            set_delete_BEptr(false);
        }
        
        // Returns correctly casted pointer to Abstract class: 
        inline Abstract_CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>* flexiblesusy::CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>::get_BEptr() const
        {
            return dynamic_cast<Abstract_CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_spectrum_generator_interface_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
