#ifndef __abstract_CMSSM_soft_parameters_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_CMSSM_soft_parameters_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <ostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_CMSSM_input_parameters_decl.h"
#include "wrapper_CMSSM_susy_parameters_decl.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_CMSSM_soft_parameters : virtual public flexiblesusy::Abstract_CMSSM_susy_parameters
        {
            public:
    
                virtual flexiblesusy::Abstract_CMSSM_soft_parameters& operator_equal__BOSS(const flexiblesusy::Abstract_CMSSM_soft_parameters&) =0;
    
                virtual void print(::std::basic_ostream<char>&) const =0;
    
                virtual flexiblesusy::Abstract_CMSSM_soft_parameters* calc_beta__BOSS() const =0;
    
                virtual flexiblesusy::Abstract_CMSSM_soft_parameters* calc_beta__BOSS(int) const =0;
    
                virtual void clear() =0;
    
                virtual void set_TYd(int, int, const double&) =0;
    
                virtual void set_TYe(int, int, const double&) =0;
    
                virtual void set_TYu(int, int, const double&) =0;
    
                virtual void set_BMu(double) =0;
    
                virtual void set_mq2(int, int, const double&) =0;
    
                virtual void set_ml2(int, int, const double&) =0;
    
                virtual void set_mHd2(double) =0;
    
                virtual void set_mHu2(double) =0;
    
                virtual void set_md2(int, int, const double&) =0;
    
                virtual void set_mu2(int, int, const double&) =0;
    
                virtual void set_me2(int, int, const double&) =0;
    
                virtual void set_MassB(double) =0;
    
                virtual void set_MassWB(double) =0;
    
                virtual void set_MassG(double) =0;
    
                virtual double get_TYd(int, int) const =0;
    
                virtual double get_TYe(int, int) const =0;
    
                virtual double get_TYu(int, int) const =0;
    
                virtual double get_BMu() const =0;
    
                virtual double get_mq2(int, int) const =0;
    
                virtual double get_ml2(int, int) const =0;
    
                virtual double get_mHd2() const =0;
    
                virtual double get_mHu2() const =0;
    
                virtual double get_md2(int, int) const =0;
    
                virtual double get_mu2(int, int) const =0;
    
                virtual double get_me2(int, int) const =0;
    
                virtual double get_MassB() const =0;
    
                virtual double get_MassWB() const =0;
    
                virtual double get_MassG() const =0;
    
            public:
                using flexiblesusy::Abstract_CMSSM_susy_parameters::pointer_assign__BOSS;
                virtual void pointer_assign__BOSS(Abstract_CMSSM_soft_parameters*) =0;
                virtual Abstract_CMSSM_soft_parameters* pointer_copy__BOSS() =0;
    
            private:
                CMSSM_soft_parameters* wptr;
                bool delete_wrapper;
            public:
                CMSSM_soft_parameters* get_wptr() { return wptr; }
                void set_wptr(CMSSM_soft_parameters* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_CMSSM_soft_parameters()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_soft_parameters(const Abstract_CMSSM_soft_parameters& in) : 
                    flexiblesusy::Abstract_Beta_function(in), flexiblesusy::Abstract_CMSSM_susy_parameters(in)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_soft_parameters& operator=(const Abstract_CMSSM_soft_parameters&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                CMSSM_soft_parameters* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                CMSSM_soft_parameters& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_CMSSM_soft_parameters() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_CMSSM_soft_parameters_FlexibleSUSY_CMSSM_2_0_1_h__ */
