#ifndef __abstract_DecayTableTHDM_THDMC_1_8_0_h__
#define __abstract_DecayTableTHDM_THDMC_1_8_0_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_THDM_decl.h"
#include "wrapper_SM_decl.h"
#include <complex>
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    class Abstract_DecayTableTHDM : public virtual AbstractBase
    {
        public:
    
            virtual void set_model__BOSS(Abstract_THDM*) =0;
    
            virtual Abstract_THDM* get_model__BOSS() =0;
    
            virtual double get_gamma_huu(int, int, int) =0;
    
            virtual double get_gamma_hdd(int, int, int) =0;
    
            virtual double get_gamma_hll(int, int, int) =0;
    
            virtual double get_gamma_hdu(int, int, int) =0;
    
            virtual double get_gamma_hln(int, int, int) =0;
    
            virtual double get_gamma_hhh(int, int, int) =0;
    
            virtual double get_gamma_hvv(int, int) =0;
    
            virtual double get_gamma_hvh(int, int, int) =0;
    
            virtual double get_gamma_hgg(int) =0;
    
            virtual double get_gamma_hgaga(int) =0;
    
            virtual double get_gamma_hZga(int) =0;
    
            virtual double get_gammatot_h(int) =0;
    
            virtual double get_gammatot_v(int) =0;
    
            virtual double get_gammatot_top() =0;
    
            virtual double get_gamma_uhd(int, int, int) =0;
    
            virtual double get_gamma_uhd_flipped(int, int, int) =0;
    
            virtual double get_gamma_uhu(int, int, int) =0;
    
            virtual double get_gamma_uhu_flipped(int, int, int) =0;
    
            virtual void print_decays(int) =0;
    
            virtual void print_width(int) =0;
    
            virtual void print_top_decays() =0;
    
            virtual void set_qcd(bool) =0;
    
            virtual double DHp(double, double, double, double, double) =0;
    
            virtual double DHm(double, double, double, double, double) =0;
    
            virtual double BHp(double, double, double, double, double) =0;
    
        public:
            virtual void pointer_assign__BOSS(Abstract_DecayTableTHDM*) =0;
            virtual Abstract_DecayTableTHDM* pointer_copy__BOSS() =0;
    
        private:
            DecayTableTHDM* wptr;
            bool delete_wrapper;
        public:
            DecayTableTHDM* get_wptr() { return wptr; }
            void set_wptr(DecayTableTHDM* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
        public:
            Abstract_DecayTableTHDM()
            {
                wptr = 0;
                delete_wrapper = false;
            }
    
            Abstract_DecayTableTHDM(const Abstract_DecayTableTHDM&)
            {
                wptr = 0;
                delete_wrapper = false;
            }
    
            Abstract_DecayTableTHDM& operator=(const Abstract_DecayTableTHDM&) { return *this; }
    
            virtual void init_wrapper() =0;
    
            DecayTableTHDM* get_init_wptr()
            {
                init_wrapper();
                return wptr;
            }
    
            DecayTableTHDM& get_init_wref()
            {
                init_wrapper();
                return *wptr;
            }
    
            virtual ~Abstract_DecayTableTHDM() =0;
    };
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_DecayTableTHDM_THDMC_1_8_0_h__ */
