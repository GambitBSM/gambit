#ifndef __abstract_Parm_Pythia_EM_8_212_h__
#define __abstract_Parm_Pythia_EM_8_212_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include <string>
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Parm : public virtual AbstractBase
        {
            public:
    
                virtual std::basic_string<char, std::char_traits<char>, std::allocator<char> >& name_ref__BOSS() =0;
    
                virtual double& valNow_ref__BOSS() =0;
    
                virtual double& valDefault_ref__BOSS() =0;
    
                virtual bool& hasMin_ref__BOSS() =0;
    
                virtual bool& hasMax_ref__BOSS() =0;
    
                virtual double& valMin_ref__BOSS() =0;
    
                virtual double& valMax_ref__BOSS() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Parm*) =0;
                virtual Abstract_Parm* pointer_copy__BOSS() =0;
    
            private:
                Parm* wptr;
                bool delete_wrapper;
            public:
                Parm* get_wptr() { return wptr; }
                void set_wptr(Parm* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Parm()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Parm(const Abstract_Parm&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Parm& operator=(const Abstract_Parm&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Parm* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Parm& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Parm() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Parm_Pythia_EM_8_212_h__ */
