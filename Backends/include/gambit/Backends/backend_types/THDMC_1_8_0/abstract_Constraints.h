#ifndef __abstract_Constraints_THDMC_1_8_0_h__
#define __abstract_Constraints_THDMC_1_8_0_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_THDM_decl.h"
#include "wrapper_SM_decl.h"
#include "wrapper_DecayTableTHDM_decl.h"
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    class Abstract_Constraints : public virtual AbstractBase
    {
        public:
    
            virtual void set_THDM__BOSS(Abstract_THDM*) =0;
    
            virtual bool check_unitarity(double) =0;
    
            virtual bool check_unitarity__BOSS() =0;
    
            virtual bool check_perturbativity(double) =0;
    
            virtual bool check_perturbativity__BOSS() =0;
    
            virtual bool check_stability() =0;
    
            virtual bool check_positivity() =0;
    
            virtual bool check_masses() =0;
    
            virtual bool check_lep() =0;
    
            virtual bool check_charged(bool&, bool&, bool&) =0;
    
            virtual bool check_NMSSMTools(bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&) =0;
    
            virtual double delta_amu() =0;
    
            virtual double delta_rho(double) =0;
    
            virtual void oblique_param(double, double&, double&, double&, double&, double&, double&) =0;
    
            virtual void print_all(double) =0;
    
        public:
            virtual void pointer_assign__BOSS(Abstract_Constraints*) =0;
            virtual Abstract_Constraints* pointer_copy__BOSS() =0;
    
        private:
            Constraints* wptr;
            bool delete_wrapper;
        public:
            Constraints* get_wptr() { return wptr; }
            void set_wptr(Constraints* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
        public:
            Abstract_Constraints()
            {
                wptr = 0;
                delete_wrapper = false;
            }
    
            Abstract_Constraints(const Abstract_Constraints&)
            {
                wptr = 0;
                delete_wrapper = false;
            }
    
            Abstract_Constraints& operator=(const Abstract_Constraints&) { return *this; }
    
            virtual void init_wrapper() =0;
    
            Constraints* get_init_wptr()
            {
                init_wrapper();
                return wptr;
            }
    
            Constraints& get_init_wref()
            {
                init_wrapper();
                return *wptr;
            }
    
            virtual ~Abstract_Constraints() =0;
    };
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Constraints_THDMC_1_8_0_h__ */
