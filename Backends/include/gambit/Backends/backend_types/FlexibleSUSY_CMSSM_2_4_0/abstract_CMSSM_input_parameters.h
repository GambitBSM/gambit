#ifndef __abstract_CMSSM_input_parameters_FlexibleSUSY_CMSSM_2_4_0_h__
#define __abstract_CMSSM_input_parameters_FlexibleSUSY_CMSSM_2_4_0_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_CMSSM_input_parameters : public virtual AbstractBase
        {
            public:
    
                virtual double& m0_ref__BOSS() =0;
    
                virtual double& m12_ref__BOSS() =0;
    
                virtual double& TanBeta_ref__BOSS() =0;
    
                virtual int& SignMu_ref__BOSS() =0;
    
                virtual double& Azero_ref__BOSS() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_CMSSM_input_parameters*) =0;
                virtual Abstract_CMSSM_input_parameters* pointer_copy__BOSS() =0;
    
            private:
                CMSSM_input_parameters* wptr;
                bool delete_wrapper;
            public:
                CMSSM_input_parameters* get_wptr() { return wptr; }
                void set_wptr(CMSSM_input_parameters* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_CMSSM_input_parameters()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_input_parameters(const Abstract_CMSSM_input_parameters&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_input_parameters& operator=(const Abstract_CMSSM_input_parameters&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                CMSSM_input_parameters* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                CMSSM_input_parameters& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_CMSSM_input_parameters() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_CMSSM_input_parameters_FlexibleSUSY_CMSSM_2_4_0_h__ */
