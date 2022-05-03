#ifndef __wrapper_CMSSM_spectrum_generator__flexiblesusy::Two_scale_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_spectrum_generator__flexiblesusy::Two_scale_def_FlexibleSUSY_CMSSM_2_0_1_h__

#include <string>
#include "wrapper_QedQcd_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        namespace CMSSM_spectrum_generator__flexiblesusy
        {
            
            // Member functions: 
            inline double CMSSM_spectrum_generator__flexiblesusy::Two_scale::get_high_scale() const
            {
                return get_BEptr()->get_high_scale();
            }
            
            inline double CMSSM_spectrum_generator__flexiblesusy::Two_scale::get_susy_scale() const
            {
                return get_BEptr()->get_susy_scale();
            }
            
            inline double CMSSM_spectrum_generator__flexiblesusy::Two_scale::get_low_scale() const
            {
                return get_BEptr()->get_low_scale();
            }
            
            inline double CMSSM_spectrum_generator__flexiblesusy::Two_scale::get_pole_mass_scale() const
            {
                return get_BEptr()->get_pole_mass_scale();
            }
            
            inline void CMSSM_spectrum_generator__flexiblesusy::Two_scale::write_running_couplings(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& filename) const
            {
                get_BEptr()->write_running_couplings(filename);
            }
            
            inline void CMSSM_spectrum_generator__flexiblesusy::Two_scale::write_running_couplings() const
            {
                get_BEptr()->write_running_couplings__BOSS();
            }
            
            
            // Wrappers for original constructors: 
            inline CMSSM_spectrum_generator__flexiblesusy::Two_scale::CMSSM_spectrum_generator__flexiblesusy::Two_scale() :
                CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>(__factory0())
            {
                get_BEptr()->set_wptr(this);
                get_BEptr()->set_delete_wrapper(false);
            }
            
            // Special pointer-based constructor: 
            inline CMSSM_spectrum_generator__flexiblesusy::Two_scale::CMSSM_spectrum_generator__flexiblesusy::Two_scale(Abstract_Two_scale* in) :
                CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>(in)
            {
                get_BEptr()->set_wptr(this);
                get_BEptr()->set_delete_wrapper(false);
            }
            
            // Copy constructor: 
            inline CMSSM_spectrum_generator__flexiblesusy::Two_scale::CMSSM_spectrum_generator__flexiblesusy::Two_scale(const CMSSM_spectrum_generator__flexiblesusy::Two_scale& in) :
                CMSSM_spectrum_generator_interface<flexiblesusy::Two_scale>(in.get_BEptr()->pointer_copy__BOSS())
            {
                get_BEptr()->set_wptr(this);
                get_BEptr()->set_delete_wrapper(false);
            }
            
            // Assignment operator: 
            inline CMSSM_spectrum_generator__flexiblesusy::Two_scale& CMSSM_spectrum_generator__flexiblesusy::Two_scale::operator=(const CMSSM_spectrum_generator__flexiblesusy::Two_scale& in)
            {
                if (this != &in)
                {
                    get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
                }
                return *this;
            }
            
            
            // Destructor: 
            inline CMSSM_spectrum_generator__flexiblesusy::Two_scale::~CMSSM_spectrum_generator__flexiblesusy::Two_scale()
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
            inline Abstract_Two_scale* flexiblesusy::CMSSM_spectrum_generator__flexiblesusy::Two_scale::get_BEptr() const
            {
                return dynamic_cast<Abstract_Two_scale*>(BEptr);
            }
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_spectrum_generator__flexiblesusy::Two_scale_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
