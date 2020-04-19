#ifndef __abstract_SM_THDMC_1_8_0_h__
#define __abstract_SM_THDMC_1_8_0_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    class Abstract_SM : public virtual AbstractBase
    {
        public:
    
            virtual const double& alpha_ref__BOSS() =0;
    
            virtual const double& alpha0_ref__BOSS() =0;
    
            virtual const double& GF_ref__BOSS() =0;
    
            virtual const double& MZ_ref__BOSS() =0;
    
            virtual const double& MW_ref__BOSS() =0;
    
            virtual const double& alpha_s_ref__BOSS() =0;
    
            virtual const double& GammaZ_ref__BOSS() =0;
    
            virtual const double& GammaW_ref__BOSS() =0;
    
            virtual const double& md_p_ref__BOSS() =0;
    
            virtual const double& mu_p_ref__BOSS() =0;
    
            virtual const double& ms_p_ref__BOSS() =0;
    
            virtual const double& Q_ms_ref__BOSS() =0;
    
            virtual const double& mc_p_ref__BOSS() =0;
    
            virtual const double& mb_p_ref__BOSS() =0;
    
            virtual const double& mt_p_ref__BOSS() =0;
    
            virtual const double& me_p_ref__BOSS() =0;
    
            virtual const double& mmu_p_ref__BOSS() =0;
    
            virtual const double& mtau_p_ref__BOSS() =0;
    
            virtual const double& Vud_ref__BOSS() =0;
    
            virtual const double& Vus_ref__BOSS() =0;
    
            virtual const double& Vub_ref__BOSS() =0;
    
            virtual const double& Vcd_ref__BOSS() =0;
    
            virtual const double& Vcs_ref__BOSS() =0;
    
            virtual const double& Vcb_ref__BOSS() =0;
    
            virtual const double& Vtd_ref__BOSS() =0;
    
            virtual const double& Vts_ref__BOSS() =0;
    
            virtual const double& Vtb_ref__BOSS() =0;
    
            virtual void set_alpha(double) =0;
    
            virtual void set_alpha0(double) =0;
    
            virtual void set_GF(double) =0;
    
            virtual void set_MZ(double) =0;
    
            virtual void set_MW(double) =0;
    
            virtual void set_gamma_Z(double) =0;
    
            virtual void set_gamma_W(double) =0;
    
            virtual void set_alpha_s(double) =0;
    
            virtual double get_alpha() =0;
    
            virtual double get_alpha0() =0;
    
            virtual double get_GF() =0;
    
            virtual double get_sintw() =0;
    
            virtual double get_costw() =0;
    
            virtual double get_g() =0;
    
            virtual double get_gprime() =0;
    
            virtual double get_e() =0;
    
            virtual double get_alpha_s() =0;
    
            virtual double get_MW() =0;
    
            virtual double get_gamma_W() =0;
    
            virtual double get_MZ() =0;
    
            virtual double get_gamma_Z() =0;
    
            virtual double get_v() =0;
    
            virtual double get_v2() =0;
    
            virtual double get_vmass(int) =0;
    
            virtual double get_gamma_V(int) =0;
    
            virtual void set_diagonal_CKM() =0;
    
            virtual double get_CKM_element(int, int) =0;
    
            virtual void set_lmass_pole(int, double) =0;
    
            virtual void set_qmass_pole(int, double) =0;
    
            virtual void set_qmass_msbar(int, double) =0;
    
            virtual void set_dmass_pole(int, double) =0;
    
            virtual void set_umass_pole(int, double) =0;
    
            virtual double get_qmass_pole(int) =0;
    
            virtual double get_dmass_pole(int) =0;
    
            virtual double get_umass_pole(int) =0;
    
            virtual double get_lmass_pole(int) =0;
    
            virtual double get_qmass_MSbar(int) =0;
    
            virtual double get_dmass_MSbar(int) =0;
    
            virtual double get_umass_MSbar(int) =0;
    
            virtual double run_qmass_MSbar(double, double, double, double, double) =0;
    
            virtual double run_alphas_MSbar(double, double, double) =0;
    
            virtual int get_Nactivef(double) =0;
    
            virtual double get_gamma_top() =0;
    
            virtual double get_gamma_tWd(int) =0;
    
            virtual void set_CKM(double, double, double, double, double, double, double, double, double) =0;
    
            virtual const double& Q_HD_ref__BOSS() =0;
    
            virtual const bool& b_HD_ref__BOSS() =0;
    
            virtual const double& ms_5_ref__BOSS() =0;
    
            virtual const double& mc_5_ref__BOSS() =0;
    
            virtual const double& mb_5_ref__BOSS() =0;
    
            virtual const double& mt_5_ref__BOSS() =0;
    
        public:
            virtual void pointer_assign__BOSS(Abstract_SM*) =0;
            virtual Abstract_SM* pointer_copy__BOSS() =0;
    
        private:
            SM* wptr;
            bool delete_wrapper;
        public:
            SM* get_wptr() { return wptr; }
            void set_wptr(SM* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
        public:
            Abstract_SM()
            {
                wptr = 0;
                delete_wrapper = false;
            }
    
            Abstract_SM(const Abstract_SM&)
            {
                wptr = 0;
                delete_wrapper = false;
            }
    
            Abstract_SM& operator=(const Abstract_SM&) { return *this; }
    
            virtual void init_wrapper() =0;
    
            SM* get_init_wptr()
            {
                init_wrapper();
                return wptr;
            }
    
            SM& get_init_wref()
            {
                init_wrapper();
                return *wptr;
            }
    
            virtual ~Abstract_SM() =0;
    };
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_SM_THDMC_1_8_0_h__ */
