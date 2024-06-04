#ifndef __abstract_CombineMatchingInput_Pythia_VLQ_8_212_h__
#define __abstract_CombineMatchingInput_Pythia_VLQ_8_212_h__

#include <cstddef>
#include <iostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Pythia_decl.h"
#include "wrapper_UserHooks_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_CombineMatchingInput : public virtual AbstractBase
        {
            public:
    
                virtual Pythia8::Abstract_UserHooks* getHook__BOSS(Pythia8::Abstract_Pythia&) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_CombineMatchingInput*) =0;
                virtual Abstract_CombineMatchingInput* pointer_copy__BOSS() =0;
    
            private:
                CombineMatchingInput* wptr;
                bool delete_wrapper;
            public:
                CombineMatchingInput* get_wptr() { return wptr; }
                void set_wptr(CombineMatchingInput* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_CombineMatchingInput()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CombineMatchingInput(const Abstract_CombineMatchingInput&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CombineMatchingInput& operator=(const Abstract_CombineMatchingInput&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                CombineMatchingInput* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                CombineMatchingInput& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_CombineMatchingInput() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_CombineMatchingInput_Pythia_VLQ_8_212_h__ */
