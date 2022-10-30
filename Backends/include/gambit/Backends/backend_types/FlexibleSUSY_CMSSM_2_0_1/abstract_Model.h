#ifndef __abstract_Model_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_Model_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <ostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_Model : public virtual AbstractBase
        {
            public:
    
                virtual void calculate_spectrum() =0;
    
                virtual void clear_problems() =0;
    
                virtual ::std::basic_string<char> name() const =0;
    
                virtual void print(::std::basic_ostream<char>&) const =0;
    
                virtual void print__BOSS() const =0;
    
                virtual void run_to(double, double) =0;
    
                virtual void run_to__BOSS(double) =0;
    
                virtual void set_precision(double) =0;
    
            private:
                Model* wptr;
                bool delete_wrapper;
            public:
                Model* get_wptr() { return wptr; }
                void set_wptr(Model* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Model()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Model(const Abstract_Model&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Model& operator=(const Abstract_Model&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Model* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Model& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Model() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Model_FlexibleSUSY_CMSSM_2_0_1_h__ */
