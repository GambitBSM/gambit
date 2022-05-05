#ifndef __abstract_Error_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_Error_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <string>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_Error : public virtual AbstractBase
        {
            public:
    
                virtual ::std::basic_string<char> what() const =0;
    
            private:
                Error* wptr;
                bool delete_wrapper;
            public:
                Error* get_wptr() { return wptr; }
                void set_wptr(Error* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Error()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Error(const Abstract_Error&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Error& operator=(const Abstract_Error&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Error* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Error& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Error() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Error_FlexibleSUSY_CMSSM_2_0_1_h__ */
