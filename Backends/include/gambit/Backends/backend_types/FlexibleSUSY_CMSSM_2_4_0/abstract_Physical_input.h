#ifndef __abstract_Physical_input_FlexibleSUSY_CMSSM_2_4_0_h__
#define __abstract_Physical_input_FlexibleSUSY_CMSSM_2_4_0_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include <array>
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_Physical_input : public virtual AbstractBase
        {
            public:
    
                virtual void reset() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Physical_input*) =0;
                virtual Abstract_Physical_input* pointer_copy__BOSS() =0;
    
            private:
                Physical_input* wptr;
                bool delete_wrapper;
            public:
                Physical_input* get_wptr() { return wptr; }
                void set_wptr(Physical_input* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Physical_input()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Physical_input(const Abstract_Physical_input&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Physical_input& operator=(const Abstract_Physical_input&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Physical_input* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Physical_input& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Physical_input() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Physical_input_FlexibleSUSY_CMSSM_2_4_0_h__ */
