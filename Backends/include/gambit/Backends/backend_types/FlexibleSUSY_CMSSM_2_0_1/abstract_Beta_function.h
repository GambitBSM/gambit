#ifndef __abstract_Beta_function_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_Beta_function_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_Beta_function : public virtual AbstractBase
        {
            public:
    
                virtual flexiblesusy::Abstract_Beta_function& operator_equal__BOSS(const flexiblesusy::Abstract_Beta_function&) =0;
    
                virtual void set_scale(double) =0;
    
                virtual void set_number_of_parameters(int) =0;
    
                virtual void set_loops(int) =0;
    
                virtual void set_thresholds(int) =0;
    
                virtual void set_zero_threshold(double) =0;
    
                virtual double get_scale() const =0;
    
                virtual int get_number_of_parameters() const =0;
    
                virtual int get_loops() const =0;
    
                virtual int get_thresholds() const =0;
    
                virtual double get_zero_threshold() const =0;
    
                virtual void reset() =0;
    
                virtual void run(double, double, double) =0;
    
                virtual void run__BOSS(double, double) =0;
    
                virtual void run_to(double, double) =0;
    
                virtual void run_to__BOSS(double) =0;
    
            private:
                Beta_function* wptr;
                bool delete_wrapper;
            public:
                Beta_function* get_wptr() { return wptr; }
                void set_wptr(Beta_function* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Beta_function()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Beta_function(const Abstract_Beta_function&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Beta_function& operator=(const Abstract_Beta_function&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Beta_function* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Beta_function& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Beta_function() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Beta_function_FlexibleSUSY_CMSSM_2_0_1_h__ */
