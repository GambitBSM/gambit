#ifndef __wrapper_CMSSM_slha_Model_Two_scale_def_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_CMSSM_slha_Model_Two_scale_def_FlexibleSUSY_CMSSM_2_4_0_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        
        // Wrappers for original constructors: 
        inline flexiblesusy::CMSSM_slha_Model_Two_scale::CMSSM_slha_Model_Two_scale() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline flexiblesusy::CMSSM_slha_Model_Two_scale::CMSSM_slha_Model_Two_scale(flexiblesusy::Abstract_CMSSM_slha_Model_Two_scale* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline flexiblesusy::CMSSM_slha_Model_Two_scale::CMSSM_slha_Model_Two_scale(const CMSSM_slha_Model_Two_scale& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline flexiblesusy::CMSSM_slha_Model_Two_scale& CMSSM_slha_Model_Two_scale::operator=(const CMSSM_slha_Model_Two_scale& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline flexiblesusy::CMSSM_slha_Model_Two_scale::~CMSSM_slha_Model_Two_scale()
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
        inline flexiblesusy::Abstract_CMSSM_slha_Model_Two_scale* flexiblesusy::CMSSM_slha_Model_Two_scale::get_BEptr() const
        {
            return dynamic_cast<flexiblesusy::Abstract_CMSSM_slha_Model_Two_scale*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_slha_Model_Two_scale_def_FlexibleSUSY_CMSSM_2_4_0_h__ */
