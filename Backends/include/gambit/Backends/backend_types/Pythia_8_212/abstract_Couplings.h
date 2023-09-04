#ifndef __abstract_Couplings_Pythia_8_212_h__
#define __abstract_Couplings_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_CoupSM_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Couplings : virtual public Pythia8::Abstract_CoupSM
        {
            public:
    
                virtual bool& isSUSY_ref__BOSS() =0;
    
            public:
                using Pythia8::Abstract_CoupSM::pointer_assign__BOSS;
                virtual void pointer_assign__BOSS(Abstract_Couplings*) =0;
                virtual Abstract_Couplings* pointer_copy__BOSS() =0;
    
            private:
                Couplings* wptr;
                bool delete_wrapper;
            public:
                Couplings* get_wptr() { return wptr; }
                void set_wptr(Couplings* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Couplings()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Couplings(const Abstract_Couplings& in) : 
                    Pythia8::Abstract_CoupSM(in)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Couplings& operator=(const Abstract_Couplings&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Couplings* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Couplings& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Couplings() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Couplings_Pythia_8_212_h__ */
