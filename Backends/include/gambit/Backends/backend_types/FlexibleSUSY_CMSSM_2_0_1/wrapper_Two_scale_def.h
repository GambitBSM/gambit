#ifndef __wrapper_Two_scale_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_Two_scale_def_FlexibleSUSY_CMSSM_2_0_1_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        
        // Wrappers for original constructors: 
        inline flexiblesusy::Two_scale::Two_scale() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline flexiblesusy::Two_scale::Two_scale(flexiblesusy::Abstract_Two_scale* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline flexiblesusy::Two_scale::Two_scale(const Two_scale& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline flexiblesusy::Two_scale& Two_scale::operator=(const Two_scale& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline flexiblesusy::Two_scale::~Two_scale()
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
        inline flexiblesusy::Abstract_Two_scale* flexiblesusy::Two_scale::get_BEptr() const
        {
            return dynamic_cast<flexiblesusy::Abstract_Two_scale*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Two_scale_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
