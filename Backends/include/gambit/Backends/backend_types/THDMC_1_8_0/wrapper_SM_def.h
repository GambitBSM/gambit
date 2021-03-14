#ifndef __wrapper_SM_def_THDMC_1_8_0_h__
#define __wrapper_SM_def_THDMC_1_8_0_h__

#include <complex>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    // Member functions: 
    inline void SM::set_alpha(double alpha_in)
    {
        get_BEptr()->set_alpha(alpha_in);
    }
    
    inline void SM::set_alpha0(double alpha_in)
    {
        get_BEptr()->set_alpha0(alpha_in);
    }
    
    inline void SM::set_GF(double GF_in)
    {
        get_BEptr()->set_GF(GF_in);
    }
    
    inline void SM::set_MZ(double MZ_in)
    {
        get_BEptr()->set_MZ(MZ_in);
    }
    
    inline void SM::set_MW(double MW_in)
    {
        get_BEptr()->set_MW(MW_in);
    }
    
    inline void SM::set_gamma_Z(double GammaZ_in)
    {
        get_BEptr()->set_gamma_Z(GammaZ_in);
    }
    
    inline void SM::set_gamma_W(double GammaW_in)
    {
        get_BEptr()->set_gamma_W(GammaW_in);
    }
    
    inline void SM::set_alpha_s(double alpha_s_in)
    {
        get_BEptr()->set_alpha_s(alpha_s_in);
    }
    
    inline double SM::get_alpha()
    {
        return get_BEptr()->get_alpha();
    }
    
    inline double SM::get_alpha0()
    {
        return get_BEptr()->get_alpha0();
    }
    
    inline double SM::get_GF()
    {
        return get_BEptr()->get_GF();
    }
    
    inline double SM::get_sintw()
    {
        return get_BEptr()->get_sintw();
    }
    
    inline double SM::get_costw()
    {
        return get_BEptr()->get_costw();
    }
    
    inline double SM::get_g()
    {
        return get_BEptr()->get_g();
    }
    
    inline double SM::get_gprime()
    {
        return get_BEptr()->get_gprime();
    }
    
    inline double SM::get_e()
    {
        return get_BEptr()->get_e();
    }
    
    inline double SM::get_alpha_s()
    {
        return get_BEptr()->get_alpha_s();
    }
    
    inline double SM::get_MW()
    {
        return get_BEptr()->get_MW();
    }
    
    inline double SM::get_gamma_W()
    {
        return get_BEptr()->get_gamma_W();
    }
    
    inline double SM::get_MZ()
    {
        return get_BEptr()->get_MZ();
    }
    
    inline double SM::get_gamma_Z()
    {
        return get_BEptr()->get_gamma_Z();
    }
    
    inline double SM::get_v()
    {
        return get_BEptr()->get_v();
    }
    
    inline double SM::get_v2()
    {
        return get_BEptr()->get_v2();
    }
    
    inline double SM::get_vmass(int v)
    {
        return get_BEptr()->get_vmass(v);
    }
    
    inline double SM::get_gamma_V(int v)
    {
        return get_BEptr()->get_gamma_V(v);
    }
    
    inline void SM::set_diagonal_CKM()
    {
        get_BEptr()->set_diagonal_CKM();
    }
    
    inline void SM::set_CKM_element_complex(int i, int j, ::std::complex<double> Vij)
    {
        get_BEptr()->set_CKM_element_complex(i, j, Vij);
    }
    
    inline double SM::get_CKM_element(int i, int j)
    {
        return get_BEptr()->get_CKM_element(i, j);
    }
    
    inline ::std::complex<double> SM::get_CKM_element_complex(int i, int j)
    {
        return get_BEptr()->get_CKM_element_complex(i, j);
    }
    
    inline void SM::set_lmass_pole(int l, double lmass_in)
    {
        get_BEptr()->set_lmass_pole(l, lmass_in);
    }
    
    inline void SM::set_qmass_pole(int q, double qmass_in)
    {
        get_BEptr()->set_qmass_pole(q, qmass_in);
    }
    
    inline void SM::set_qmass_msbar(int flav, double qmass_in)
    {
        get_BEptr()->set_qmass_msbar(flav, qmass_in);
    }
    
    inline void SM::set_dmass_pole(int d, double dmass_in)
    {
        get_BEptr()->set_dmass_pole(d, dmass_in);
    }
    
    inline void SM::set_umass_pole(int u, double umass_in)
    {
        get_BEptr()->set_umass_pole(u, umass_in);
    }
    
    inline double SM::get_qmass_pole(int q)
    {
        return get_BEptr()->get_qmass_pole(q);
    }
    
    inline double SM::get_dmass_pole(int d)
    {
        return get_BEptr()->get_dmass_pole(d);
    }
    
    inline double SM::get_umass_pole(int u)
    {
        return get_BEptr()->get_umass_pole(u);
    }
    
    inline double SM::get_lmass_pole(int l)
    {
        return get_BEptr()->get_lmass_pole(l);
    }
    
    inline double SM::get_qmass_MSbar(int q)
    {
        return get_BEptr()->get_qmass_MSbar(q);
    }
    
    inline double SM::get_dmass_MSbar(int d)
    {
        return get_BEptr()->get_dmass_MSbar(d);
    }
    
    inline double SM::get_umass_MSbar(int u)
    {
        return get_BEptr()->get_umass_MSbar(u);
    }
    
    inline double SM::run_qmass_MSbar(double quark_mass, double Qinit, double Qfin, double mtop, double mbot)
    {
        return get_BEptr()->run_qmass_MSbar(quark_mass, Qinit, Qfin, mtop, mbot);
    }
    
    inline double SM::run_alphas_MSbar(double Q, double mtop, double mbot)
    {
        return get_BEptr()->run_alphas_MSbar(Q, mtop, mbot);
    }
    
    inline int SM::get_Nactivef(double M)
    {
        return get_BEptr()->get_Nactivef(M);
    }
    
    inline double SM::get_gamma_top()
    {
        return get_BEptr()->get_gamma_top();
    }
    
    inline double SM::get_gamma_tWd(int d)
    {
        return get_BEptr()->get_gamma_tWd(d);
    }
    
    inline void SM::set_CKM(double ckm11, double ckm12, double ckm13, double ckm21, double ckm22, double ckm23, double ckm31, double ckm32, double ckm33)
    {
        get_BEptr()->set_CKM(ckm11, ckm12, ckm13, ckm21, ckm22, ckm23, ckm31, ckm32, ckm33);
    }
    
    
    // Wrappers for original constructors: 
    inline SM::SM() :
        WrapperBase(__factory0()),
        alpha( get_BEptr()->alpha_ref__BOSS()),
        alpha0( get_BEptr()->alpha0_ref__BOSS()),
        GF( get_BEptr()->GF_ref__BOSS()),
        MZ( get_BEptr()->MZ_ref__BOSS()),
        MW( get_BEptr()->MW_ref__BOSS()),
        alpha_s( get_BEptr()->alpha_s_ref__BOSS()),
        GammaZ( get_BEptr()->GammaZ_ref__BOSS()),
        GammaW( get_BEptr()->GammaW_ref__BOSS()),
        md_p( get_BEptr()->md_p_ref__BOSS()),
        mu_p( get_BEptr()->mu_p_ref__BOSS()),
        ms_p( get_BEptr()->ms_p_ref__BOSS()),
        Q_ms( get_BEptr()->Q_ms_ref__BOSS()),
        mc_p( get_BEptr()->mc_p_ref__BOSS()),
        mb_p( get_BEptr()->mb_p_ref__BOSS()),
        mt_p( get_BEptr()->mt_p_ref__BOSS()),
        me_p( get_BEptr()->me_p_ref__BOSS()),
        mmu_p( get_BEptr()->mmu_p_ref__BOSS()),
        mtau_p( get_BEptr()->mtau_p_ref__BOSS()),
        Vud( get_BEptr()->Vud_ref__BOSS()),
        Vus( get_BEptr()->Vus_ref__BOSS()),
        Vub( get_BEptr()->Vub_ref__BOSS()),
        Vcd( get_BEptr()->Vcd_ref__BOSS()),
        Vcs( get_BEptr()->Vcs_ref__BOSS()),
        Vcb( get_BEptr()->Vcb_ref__BOSS()),
        Vtd( get_BEptr()->Vtd_ref__BOSS()),
        Vts( get_BEptr()->Vts_ref__BOSS()),
        Vtb( get_BEptr()->Vtb_ref__BOSS()),
        Q_HD( get_BEptr()->Q_HD_ref__BOSS()),
        b_HD( get_BEptr()->b_HD_ref__BOSS()),
        ms_5( get_BEptr()->ms_5_ref__BOSS()),
        mc_5( get_BEptr()->mc_5_ref__BOSS()),
        mb_5( get_BEptr()->mb_5_ref__BOSS()),
        mt_5( get_BEptr()->mt_5_ref__BOSS())
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Special pointer-based constructor: 
    inline SM::SM(Abstract_SM* in) :
        WrapperBase(in),
        alpha( get_BEptr()->alpha_ref__BOSS()),
        alpha0( get_BEptr()->alpha0_ref__BOSS()),
        GF( get_BEptr()->GF_ref__BOSS()),
        MZ( get_BEptr()->MZ_ref__BOSS()),
        MW( get_BEptr()->MW_ref__BOSS()),
        alpha_s( get_BEptr()->alpha_s_ref__BOSS()),
        GammaZ( get_BEptr()->GammaZ_ref__BOSS()),
        GammaW( get_BEptr()->GammaW_ref__BOSS()),
        md_p( get_BEptr()->md_p_ref__BOSS()),
        mu_p( get_BEptr()->mu_p_ref__BOSS()),
        ms_p( get_BEptr()->ms_p_ref__BOSS()),
        Q_ms( get_BEptr()->Q_ms_ref__BOSS()),
        mc_p( get_BEptr()->mc_p_ref__BOSS()),
        mb_p( get_BEptr()->mb_p_ref__BOSS()),
        mt_p( get_BEptr()->mt_p_ref__BOSS()),
        me_p( get_BEptr()->me_p_ref__BOSS()),
        mmu_p( get_BEptr()->mmu_p_ref__BOSS()),
        mtau_p( get_BEptr()->mtau_p_ref__BOSS()),
        Vud( get_BEptr()->Vud_ref__BOSS()),
        Vus( get_BEptr()->Vus_ref__BOSS()),
        Vub( get_BEptr()->Vub_ref__BOSS()),
        Vcd( get_BEptr()->Vcd_ref__BOSS()),
        Vcs( get_BEptr()->Vcs_ref__BOSS()),
        Vcb( get_BEptr()->Vcb_ref__BOSS()),
        Vtd( get_BEptr()->Vtd_ref__BOSS()),
        Vts( get_BEptr()->Vts_ref__BOSS()),
        Vtb( get_BEptr()->Vtb_ref__BOSS()),
        Q_HD( get_BEptr()->Q_HD_ref__BOSS()),
        b_HD( get_BEptr()->b_HD_ref__BOSS()),
        ms_5( get_BEptr()->ms_5_ref__BOSS()),
        mc_5( get_BEptr()->mc_5_ref__BOSS()),
        mb_5( get_BEptr()->mb_5_ref__BOSS()),
        mt_5( get_BEptr()->mt_5_ref__BOSS())
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Copy constructor: 
    inline SM::SM(const SM& in) :
        WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
        alpha( get_BEptr()->alpha_ref__BOSS()),
        alpha0( get_BEptr()->alpha0_ref__BOSS()),
        GF( get_BEptr()->GF_ref__BOSS()),
        MZ( get_BEptr()->MZ_ref__BOSS()),
        MW( get_BEptr()->MW_ref__BOSS()),
        alpha_s( get_BEptr()->alpha_s_ref__BOSS()),
        GammaZ( get_BEptr()->GammaZ_ref__BOSS()),
        GammaW( get_BEptr()->GammaW_ref__BOSS()),
        md_p( get_BEptr()->md_p_ref__BOSS()),
        mu_p( get_BEptr()->mu_p_ref__BOSS()),
        ms_p( get_BEptr()->ms_p_ref__BOSS()),
        Q_ms( get_BEptr()->Q_ms_ref__BOSS()),
        mc_p( get_BEptr()->mc_p_ref__BOSS()),
        mb_p( get_BEptr()->mb_p_ref__BOSS()),
        mt_p( get_BEptr()->mt_p_ref__BOSS()),
        me_p( get_BEptr()->me_p_ref__BOSS()),
        mmu_p( get_BEptr()->mmu_p_ref__BOSS()),
        mtau_p( get_BEptr()->mtau_p_ref__BOSS()),
        Vud( get_BEptr()->Vud_ref__BOSS()),
        Vus( get_BEptr()->Vus_ref__BOSS()),
        Vub( get_BEptr()->Vub_ref__BOSS()),
        Vcd( get_BEptr()->Vcd_ref__BOSS()),
        Vcs( get_BEptr()->Vcs_ref__BOSS()),
        Vcb( get_BEptr()->Vcb_ref__BOSS()),
        Vtd( get_BEptr()->Vtd_ref__BOSS()),
        Vts( get_BEptr()->Vts_ref__BOSS()),
        Vtb( get_BEptr()->Vtb_ref__BOSS()),
        Q_HD( get_BEptr()->Q_HD_ref__BOSS()),
        b_HD( get_BEptr()->b_HD_ref__BOSS()),
        ms_5( get_BEptr()->ms_5_ref__BOSS()),
        mc_5( get_BEptr()->mc_5_ref__BOSS()),
        mb_5( get_BEptr()->mb_5_ref__BOSS()),
        mt_5( get_BEptr()->mt_5_ref__BOSS())
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Assignment operator: 
    inline SM& SM::operator=(const SM& in)
    {
        if (this != &in)
        {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
        }
        return *this;
    }
    
    
    // Destructor: 
    inline SM::~SM()
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
    inline Abstract_SM* SM::get_BEptr() const
    {
        return dynamic_cast<Abstract_SM*>(BEptr);
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SM_def_THDMC_1_8_0_h__ */
