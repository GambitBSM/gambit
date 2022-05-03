#ifndef __wrapper_Physical_input_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_Physical_input_def_FlexibleSUSY_CMSSM_2_0_1_h__

#include <array>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline double Physical_input::get(flexiblesusy::Abstract_Physical_input::Input arg_1) const
        {
            return get_BEptr()->get(arg_1);
        }
        
        inline void Physical_input::set(flexiblesusy::Abstract_Physical_input::Input arg_1, double arg_2)
        {
            get_BEptr()->set(arg_1, arg_2);
        }
        
        inline void Physical_input::reset()
        {
            get_BEptr()->reset();
        }
        
        
        // Wrappers for original constructors: 
        inline Physical_input::Physical_input() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Physical_input::Physical_input(Abstract_Physical_input* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Physical_input::Physical_input(const Physical_input& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Physical_input& Physical_input::operator=(const Physical_input& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Physical_input::~Physical_input()
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
        inline Abstract_Physical_input* flexiblesusy::Physical_input::get_BEptr() const
        {
            return dynamic_cast<Abstract_Physical_input*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Physical_input_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
