#ifndef __wrapper_DecayTableTHDM_def_THDMC_1_8_0_h__
#define __wrapper_DecayTableTHDM_def_THDMC_1_8_0_h__

#include "wrapper_THDM_decl.h"
#include "wrapper_SM_decl.h"
#include <complex>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    // Member functions: 
    inline void DecayTableTHDM::set_model(THDM* model)
    {
        get_BEptr()->set_model__BOSS((*model).get_BEptr());
    }
    
    inline THDM* DecayTableTHDM::get_model()
    {
        return get_BEptr()->get_model__BOSS()->get_init_wptr();
    }
    
    inline double DecayTableTHDM::get_gamma_huu(int h, int u1, int u2)
    {
        return get_BEptr()->get_gamma_huu(h, u1, u2);
    }
    
    inline double DecayTableTHDM::get_gamma_hdd(int h, int d1, int d2)
    {
        return get_BEptr()->get_gamma_hdd(h, d1, d2);
    }
    
    inline double DecayTableTHDM::get_gamma_hll(int h, int l1, int l2)
    {
        return get_BEptr()->get_gamma_hll(h, l1, l2);
    }
    
    inline double DecayTableTHDM::get_gamma_hdu(int h, int d, int u)
    {
        return get_BEptr()->get_gamma_hdu(h, d, u);
    }
    
    inline double DecayTableTHDM::get_gamma_hln(int h, int l, int n)
    {
        return get_BEptr()->get_gamma_hln(h, l, n);
    }
    
    inline double DecayTableTHDM::get_gamma_hhh(int h, int h1, int h2)
    {
        return get_BEptr()->get_gamma_hhh(h, h1, h2);
    }
    
    inline double DecayTableTHDM::get_gamma_hvv(int h, int v)
    {
        return get_BEptr()->get_gamma_hvv(h, v);
    }
    
    inline double DecayTableTHDM::get_gamma_hvh(int H, int V, int h)
    {
        return get_BEptr()->get_gamma_hvh(H, V, h);
    }
    
    inline double DecayTableTHDM::get_gamma_hgg(int h)
    {
        return get_BEptr()->get_gamma_hgg(h);
    }
    
    inline double DecayTableTHDM::get_gamma_hgaga(int h)
    {
        return get_BEptr()->get_gamma_hgaga(h);
    }
    
    inline double DecayTableTHDM::get_gamma_hZga(int h)
    {
        return get_BEptr()->get_gamma_hZga(h);
    }
    
    inline double DecayTableTHDM::get_gammatot_h(int h)
    {
        return get_BEptr()->get_gammatot_h(h);
    }
    
    inline double DecayTableTHDM::get_gammatot_v(int v)
    {
        return get_BEptr()->get_gammatot_v(v);
    }
    
    inline double DecayTableTHDM::get_gammatot_top()
    {
        return get_BEptr()->get_gammatot_top();
    }
    
    inline double DecayTableTHDM::get_gamma_uhd(int u, int h, int d)
    {
        return get_BEptr()->get_gamma_uhd(u, h, d);
    }
    
    inline double DecayTableTHDM::get_gamma_uhd_flipped(int u, int h, int d)
    {
        return get_BEptr()->get_gamma_uhd_flipped(u, h, d);
    }
    
    inline double DecayTableTHDM::get_gamma_uhu(int u1, int h, int u2)
    {
        return get_BEptr()->get_gamma_uhu(u1, h, u2);
    }
    
    inline double DecayTableTHDM::get_gamma_uhu_flipped(int u1, int h, int u2)
    {
        return get_BEptr()->get_gamma_uhu_flipped(u1, h, u2);
    }
    
    inline void DecayTableTHDM::print_decays(int h)
    {
        get_BEptr()->print_decays(h);
    }
    
    inline void DecayTableTHDM::print_width(int h)
    {
        get_BEptr()->print_width(h);
    }
    
    inline void DecayTableTHDM::print_top_decays()
    {
        get_BEptr()->print_top_decays();
    }
    
    inline void DecayTableTHDM::set_qcd(bool set)
    {
        get_BEptr()->set_qcd(set);
    }
    
    inline double DecayTableTHDM::DHp(double ui, double uj, double xi, double xj, double sqL)
    {
        return get_BEptr()->DHp(ui, uj, xi, xj, sqL);
    }
    
    inline double DecayTableTHDM::DHm(double ui, double uj, double xi, double xj, double sqL)
    {
        return get_BEptr()->DHm(ui, uj, xi, xj, sqL);
    }
    
    inline double DecayTableTHDM::BHp(double ui, double uj, double xi, double xj, double sqL)
    {
        return get_BEptr()->BHp(ui, uj, xi, xj, sqL);
    }
    
    
    // Wrappers for original constructors: 
    inline DecayTableTHDM::DecayTableTHDM(THDM* mod) :
        WrapperBase(__factory0(mod))
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Special pointer-based constructor: 
    inline DecayTableTHDM::DecayTableTHDM(Abstract_DecayTableTHDM* in) :
        WrapperBase(in)
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Copy constructor: 
    inline DecayTableTHDM::DecayTableTHDM(const DecayTableTHDM& in) :
        WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Assignment operator: 
    inline DecayTableTHDM& DecayTableTHDM::operator=(const DecayTableTHDM& in)
    {
        if (this != &in)
        {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
        }
        return *this;
    }
    
    
    // Destructor: 
    inline DecayTableTHDM::~DecayTableTHDM()
    {
        if (get_BEptr() != 0)
        {
            get_BEptr()->set_delete_wrapper(false);
            if (can_delete_BEptr())
            {
                delete BEptr;
                BEptr = 0;
            }
        }
        set_delete_BEptr(false);
    }
    
    // Returns correctly casted pointer to Abstract class: 
    inline Abstract_DecayTableTHDM* DecayTableTHDM::get_BEptr() const
    {
        return dynamic_cast<Abstract_DecayTableTHDM*>(BEptr);
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DecayTableTHDM_def_THDMC_1_8_0_h__ */
