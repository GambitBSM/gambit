#ifndef __abstract_CMSSM__Two_scale_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_CMSSM__Two_scale_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <ostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_CMSSM_input_parameters_decl.h"
#include "wrapper_Model_decl.h"
#include "wrapper_CMSSM_mass_eigenstates_decl.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_CMSSM__Two_scale : virtual public flexiblesusy::Abstract_Model, virtual public flexiblesusy::Abstract_CMSSM_mass_eigenstates
        {
            public:
    
                virtual flexiblesusy::Abstract_CMSSM<flexiblesusy::Abstract_Two_scale>& operator_equal__BOSS(const flexiblesusy::Abstract_CMSSM<flexiblesusy::Abstract_Two_scale>&) =0;
    
                virtual void calculate_spectrum() =0;
    
                virtual void clear_problems() =0;
    
                virtual ::std::basic_string<char> name() const =0;
    
                virtual void run_to(double, double) =0;
    
                virtual void run_to__BOSS(double) =0;
    
                virtual void print(::std::basic_ostream<char>&) const =0;
    
                virtual void print__BOSS() const =0;
    
                virtual void set_precision(double) =0;
    
            public:
                using flexiblesusy::Abstract_CMSSM_mass_eigenstates::pointer_assign__BOSS;
                virtual void pointer_assign__BOSS(Abstract_CMSSM__Two_scale*) =0;
                virtual Abstract_CMSSM__Two_scale* pointer_copy__BOSS() =0;
    
            private:
                CMSSM__Two_scale* wptr;
                bool delete_wrapper;
            public:
                CMSSM__Two_scale* get_wptr() { return wptr; }
                void set_wptr(CMSSM__Two_scale* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_CMSSM__Two_scale()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM__Two_scale(const Abstract_CMSSM__Two_scale& in) : 
                    flexiblesusy::Abstract_Beta_function(in), flexiblesusy::Abstract_CMSSM_susy_parameters(in), flexiblesusy::Abstract_CMSSM_soft_parameters(in), flexiblesusy::Abstract_CMSSM_mass_eigenstates(in), flexiblesusy::Abstract_Model(in)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM__Two_scale& operator=(const Abstract_CMSSM__Two_scale&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                CMSSM__Two_scale* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                CMSSM__Two_scale& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_CMSSM__Two_scale() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_CMSSM__Two_scale_FlexibleSUSY_CMSSM_2_0_1_h__ */
