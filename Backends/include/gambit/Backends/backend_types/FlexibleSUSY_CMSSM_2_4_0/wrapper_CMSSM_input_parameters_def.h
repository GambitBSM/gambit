#ifndef __wrapper_CMSSM_input_parameters_def_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_CMSSM_input_parameters_def_FlexibleSUSY_CMSSM_2_4_0_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        
        // Wrappers for original constructors: 
        inline flexiblesusy::CMSSM_input_parameters::CMSSM_input_parameters() :
            WrapperBase(__factory0()),
            m0( get_BEptr()->m0_ref__BOSS()),
            m12( get_BEptr()->m12_ref__BOSS()),
            TanBeta( get_BEptr()->TanBeta_ref__BOSS()),
            SignMu( get_BEptr()->SignMu_ref__BOSS()),
            Azero( get_BEptr()->Azero_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline flexiblesusy::CMSSM_input_parameters::CMSSM_input_parameters(flexiblesusy::Abstract_CMSSM_input_parameters* in) :
            WrapperBase(in),
            m0( get_BEptr()->m0_ref__BOSS()),
            m12( get_BEptr()->m12_ref__BOSS()),
            TanBeta( get_BEptr()->TanBeta_ref__BOSS()),
            SignMu( get_BEptr()->SignMu_ref__BOSS()),
            Azero( get_BEptr()->Azero_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline flexiblesusy::CMSSM_input_parameters::CMSSM_input_parameters(const CMSSM_input_parameters& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            m0( get_BEptr()->m0_ref__BOSS()),
            m12( get_BEptr()->m12_ref__BOSS()),
            TanBeta( get_BEptr()->TanBeta_ref__BOSS()),
            SignMu( get_BEptr()->SignMu_ref__BOSS()),
            Azero( get_BEptr()->Azero_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline flexiblesusy::CMSSM_input_parameters& CMSSM_input_parameters::operator=(const CMSSM_input_parameters& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline flexiblesusy::CMSSM_input_parameters::~CMSSM_input_parameters()
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
        inline flexiblesusy::Abstract_CMSSM_input_parameters* flexiblesusy::CMSSM_input_parameters::get_BEptr() const
        {
            return dynamic_cast<flexiblesusy::Abstract_CMSSM_input_parameters*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_input_parameters_def_FlexibleSUSY_CMSSM_2_4_0_h__ */
