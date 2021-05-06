#ifndef __abstract_THDM_THDMC_1_8_0_h__
#define __abstract_THDM_THDMC_1_8_0_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_SM_decl.h"
#include <complex>
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    class Abstract_THDM : public virtual AbstractBase
    {
        public:
    
            virtual void free_gsl() =0;
    
            virtual void set_SM__BOSS(Abstract_SM&) =0;
    
            virtual Abstract_SM* get_SM__BOSS() =0;
    
            virtual Abstract_SM* get_SM_pointer__BOSS() =0;
    
            virtual bool set_param_full(double, double, double, double, double, double, double, double, double, double, double, double, double, double) =0;
    
            virtual bool set_param_gen(double, double, double, double, double, double, double, double, double) =0;
    
            virtual bool set_param_higgs(double, double, double, double, double, double, double, double) =0;
    
            virtual bool set_param_hybrid(double, double, double, double, double, double, double) =0;
    
            virtual bool set_param_hybrid_sba(double, double, double, double, double, double, double) =0;
    
            virtual bool set_param_HHG(double, double, double, double, double, double, double) =0;
    
            virtual bool set_param_phys(double, double, double, double, double, double, double, double, double) =0;
    
            virtual bool set_param_sm(double) =0;
    
            virtual bool set_MSSM(double, double) =0;
    
            virtual bool set_hMSSM(double, double, double) =0;
    
            virtual bool set_inert(double, double, double, double, double, double) =0;
    
            virtual void get_param_gen(double&, double&, double&, double&, double&, double&, double&, double&, double&) =0;
    
            virtual void get_param_higgs(double&, double&, double&, double&, double&, double&, double&, double&) =0;
    
            virtual void get_param_hybrid(double&, double&, double&, double&, double&, double&, double&) =0;
    
            virtual void get_param_HHG(double&, double&, double&, double&, double&, double&, double&) =0;
    
            virtual void get_param_phys(double&, double&, double&, double&, double&, double&, double&, double&, double&) =0;
    
            virtual void recalc_tan_beta(double) =0;
    
            virtual double get_hmass(int) =0;
    
            virtual double get_sba() =0;
    
            virtual double get_cba() =0;
    
            virtual ::std::complex<double> get_qki(int, int) =0;
    
            virtual void set_yukawas_type(int) =0;
    
            virtual int get_yukawas_type() =0;
    
            virtual void set_yukawas_down(double, double, double) =0;
    
            virtual void set_yukawas_up(double, double, double) =0;
    
            virtual void set_yukawas_lepton(double, double, double) =0;
    
            virtual void set_yukawas_down(::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>) =0;
    
            virtual void set_yukawas_up(::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>) =0;
    
            virtual void set_yukawas_lepton(::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>, ::std::complex<double>) =0;
    
            virtual void set_yukawas_inert() =0;
    
            virtual void get_yukawas_down(::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_yukawas_up(::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_yukawas_lepton(::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_kappa_down(::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_kappa_up(::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_kappa_lepton(::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_kappa_down(double, ::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_kappa_up(double, ::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_kappa_lepton(double, ::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_rho_down(double, ::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_rho_up(double, ::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_rho_lepton(double, ::std::complex<double>&, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_coupling_hdd(int, int, int, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_coupling_huu(int, int, int, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_coupling_hdu(int, int, int, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_coupling_hud(int, int, int, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_coupling_hll(int, int, int, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_coupling_hln(int, int, int, ::std::complex<double>&, ::std::complex<double>&) =0;
    
            virtual void get_coupling_vvh(int, int, int, ::std::complex<double>&) =0;
    
            virtual void get_coupling_vhh(int, int, int, ::std::complex<double>&) =0;
    
            virtual void get_coupling_hhh(int, int, int, ::std::complex<double>&) =0;
    
            virtual void get_coupling_vvhh(int, int, int, int, ::std::complex<double>&) =0;
    
            virtual void get_coupling_hhhh(int, int, int, int, ::std::complex<double>&) =0;
    
            virtual double calc_unitarity() =0;
    
            virtual bool check_unitarity(double) =0;
    
            virtual bool check_unitarity__BOSS() =0;
    
            virtual void calc_perturbativity(::std::complex<double>&, int&, int&, int&, int&) =0;
    
            virtual bool check_perturbativity(double) =0;
    
            virtual bool check_perturbativity__BOSS() =0;
    
            virtual bool check_stability() =0;
    
            virtual void print_param_gen() =0;
    
            virtual void print_param_higgs() =0;
    
            virtual void print_param_hybrid() =0;
    
            virtual void print_param_phys() =0;
    
            virtual void print_param_HHG() =0;
    
            virtual void print_yukawas() =0;
    
            virtual void print_hdecay() =0;
    
            virtual bool read_LesHouches(const char*) =0;
    
            virtual double get_alpha() =0;
    
        public:
            virtual void pointer_assign__BOSS(Abstract_THDM*) =0;
            virtual Abstract_THDM* pointer_copy__BOSS() =0;
    
        private:
            THDM* wptr;
            bool delete_wrapper;
        public:
            THDM* get_wptr() { return wptr; }
            void set_wptr(THDM* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
        public:
            Abstract_THDM()
            {
                wptr = 0;
                delete_wrapper = false;
            }
    
            Abstract_THDM(const Abstract_THDM&)
            {
                wptr = 0;
                delete_wrapper = false;
            }
    
            Abstract_THDM& operator=(const Abstract_THDM&) { return *this; }
    
            virtual void init_wrapper() =0;
    
            THDM* get_init_wptr()
            {
                init_wrapper();
                return wptr;
            }
    
            THDM& get_init_wref()
            {
                init_wrapper();
                return *wptr;
            }
    
            virtual ~Abstract_THDM() =0;
    };
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_THDM_THDMC_1_8_0_h__ */
