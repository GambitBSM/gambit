#ifndef __wrapper_CMSSM_scales_def_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_CMSSM_scales_def_FlexibleSUSY_CMSSM_2_4_0_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        
        // Wrappers for original constructors: 
        inline flexiblesusy::CMSSM_scales::CMSSM_scales() :
            WrapperBase(__factory0()),
            HighScale( get_BEptr()->HighScale_ref__BOSS()),
            SUSYScale( get_BEptr()->SUSYScale_ref__BOSS()),
            LowScale( get_BEptr()->LowScale_ref__BOSS()),
            pole_mass_scale( get_BEptr()->pole_mass_scale_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline flexiblesusy::CMSSM_scales::CMSSM_scales(flexiblesusy::Abstract_CMSSM_scales* in) :
            WrapperBase(in),
            HighScale( get_BEptr()->HighScale_ref__BOSS()),
            SUSYScale( get_BEptr()->SUSYScale_ref__BOSS()),
            LowScale( get_BEptr()->LowScale_ref__BOSS()),
            pole_mass_scale( get_BEptr()->pole_mass_scale_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline flexiblesusy::CMSSM_scales::CMSSM_scales(const CMSSM_scales& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            HighScale( get_BEptr()->HighScale_ref__BOSS()),
            SUSYScale( get_BEptr()->SUSYScale_ref__BOSS()),
            LowScale( get_BEptr()->LowScale_ref__BOSS()),
            pole_mass_scale( get_BEptr()->pole_mass_scale_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline flexiblesusy::CMSSM_scales& CMSSM_scales::operator=(const CMSSM_scales& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline flexiblesusy::CMSSM_scales::~CMSSM_scales()
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
        inline flexiblesusy::Abstract_CMSSM_scales* flexiblesusy::CMSSM_scales::get_BEptr() const
        {
            return dynamic_cast<flexiblesusy::Abstract_CMSSM_scales*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_scales_def_FlexibleSUSY_CMSSM_2_4_0_h__ */
