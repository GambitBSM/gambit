#ifndef __abstract_CMSSM_susy_parameters_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_CMSSM_susy_parameters_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <ostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_CMSSM_input_parameters_decl.h"
#include "wrapper_Beta_function_decl.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_CMSSM_susy_parameters : virtual public flexiblesusy::Abstract_Beta_function
        {
            public:
    
                virtual flexiblesusy::Abstract_CMSSM_susy_parameters& operator_equal__BOSS(const flexiblesusy::Abstract_CMSSM_susy_parameters&) =0;
    
                virtual void print(::std::basic_ostream<char>&) const =0;
    
                virtual const flexiblesusy::Abstract_CMSSM_input_parameters& get_input__BOSS() const =0;
    
                virtual flexiblesusy::Abstract_CMSSM_input_parameters& get_input__BOSS() =0;
    
                virtual void set_input_parameters__BOSS(const flexiblesusy::Abstract_CMSSM_input_parameters&) =0;
    
                virtual flexiblesusy::Abstract_CMSSM_susy_parameters* calc_beta__BOSS() const =0;
    
                virtual flexiblesusy::Abstract_CMSSM_susy_parameters* calc_beta__BOSS(int) const =0;
    
                virtual void clear() =0;
    
                virtual void set_Yd(int, int, const double&) =0;
    
                virtual void set_Ye(int, int, const double&) =0;
    
                virtual void set_Yu(int, int, const double&) =0;
    
                virtual void set_Mu(double) =0;
    
                virtual void set_g1(double) =0;
    
                virtual void set_g2(double) =0;
    
                virtual void set_g3(double) =0;
    
                virtual void set_vd(double) =0;
    
                virtual void set_vu(double) =0;
    
                virtual double get_Yd(int, int) const =0;
    
                virtual double get_Ye(int, int) const =0;
    
                virtual double get_Yu(int, int) const =0;
    
                virtual double get_Mu() const =0;
    
                virtual double get_g1() const =0;
    
                virtual double get_g2() const =0;
    
                virtual double get_g3() const =0;
    
                virtual double get_vd() const =0;
    
                virtual double get_vu() const =0;
    
                virtual double get_SHdSHd() const =0;
    
                virtual double get_SHuSHu() const =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_CMSSM_susy_parameters*) =0;
                virtual Abstract_CMSSM_susy_parameters* pointer_copy__BOSS() =0;
    
            private:
                CMSSM_susy_parameters* wptr;
                bool delete_wrapper;
            public:
                CMSSM_susy_parameters* get_wptr() { return wptr; }
                void set_wptr(CMSSM_susy_parameters* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_CMSSM_susy_parameters()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_susy_parameters(const Abstract_CMSSM_susy_parameters& in) : 
                    flexiblesusy::Abstract_Beta_function(in)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_susy_parameters& operator=(const Abstract_CMSSM_susy_parameters&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                CMSSM_susy_parameters* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                CMSSM_susy_parameters& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_CMSSM_susy_parameters() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_CMSSM_susy_parameters_FlexibleSUSY_CMSSM_2_0_1_h__ */
