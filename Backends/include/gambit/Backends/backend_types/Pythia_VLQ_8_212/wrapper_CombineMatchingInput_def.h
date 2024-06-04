#ifndef __wrapper_CombineMatchingInput_def_Pythia_VLQ_8_212_h__
#define __wrapper_CombineMatchingInput_def_Pythia_VLQ_8_212_h__

#include "wrapper_Pythia_decl.h"
#include "wrapper_UserHooks_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline Pythia8::UserHooks* CombineMatchingInput::getHook(Pythia8::Pythia& pythia)
        {
            return get_BEptr()->getHook__BOSS(*pythia.get_BEptr())->get_init_wptr();
        }
        
        
        // Wrappers for original constructors: 
        inline CombineMatchingInput::CombineMatchingInput() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline CombineMatchingInput::CombineMatchingInput(Abstract_CombineMatchingInput* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline CombineMatchingInput::CombineMatchingInput(const CombineMatchingInput& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline CombineMatchingInput& CombineMatchingInput::operator=(const CombineMatchingInput& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline CombineMatchingInput::~CombineMatchingInput()
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
        inline Abstract_CombineMatchingInput* Pythia8::CombineMatchingInput::get_BEptr() const
        {
            return dynamic_cast<Abstract_CombineMatchingInput*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CombineMatchingInput_def_Pythia_VLQ_8_212_h__ */
