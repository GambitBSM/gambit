#ifndef __wrapper_Error_def_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_Error_def_FlexibleSUSY_CMSSM_2_4_0_h__

#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Error::what_detailed() const
        {
            return get_BEptr()->what_detailed();
        }
        
        
        // Wrappers for original constructors: 
        inline flexiblesusy::Error::Error(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& msg) :
            WrapperBase(__factory0(msg))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline flexiblesusy::Error::Error(const char* msg) :
            WrapperBase(__factory1(msg))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline flexiblesusy::Error::Error(flexiblesusy::Abstract_Error* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline flexiblesusy::Error::Error(const Error& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline flexiblesusy::Error& Error::operator=(const Error& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline flexiblesusy::Error::~Error()
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
        inline flexiblesusy::Abstract_Error* flexiblesusy::Error::get_BEptr() const
        {
            return dynamic_cast<flexiblesusy::Abstract_Error*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Error_def_FlexibleSUSY_CMSSM_2_4_0_h__ */
