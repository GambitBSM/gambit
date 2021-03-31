#ifndef __wrapper_THDM_def_THDMC_1_8_0_h__
#define __wrapper_THDM_def_THDMC_1_8_0_h__

#include "wrapper_SM_decl.h"
#include <complex>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    // Member functions: 
    inline void THDM::free_gsl()
    {
        get_BEptr()->free_gsl();
    }
    
    inline void THDM::set_SM(SM sm_in)
    {
        get_BEptr()->set_SM__BOSS(*sm_in.get_BEptr());
    }
    
    inline SM THDM::get_SM()
    {
        return SM( get_BEptr()->get_SM__BOSS() );
    }
    
    inline SM* THDM::get_SM_pointer()
    {
        return get_BEptr()->get_SM_pointer__BOSS()->get_init_wptr();
    }
    
    inline bool THDM::set_param_full(double lambda1, double lambda2, double lambda3, double lambda4, double lambda5, double lambda6, double lambda7, double m12_2, double tan_beta, double m_h, double m_H, double m_A, double m_Hp, double sba)
    {
        return get_BEptr()->set_param_full(lambda1, lambda2, lambda3, lambda4, lambda5, lambda6, lambda7, m12_2, tan_beta, m_h, m_H, m_A, m_Hp, sba);
    }
    
    inline bool THDM::set_param_gen(double lambda1, double lambda2, double lambda3, double lambda4, double lambda5, double lambda6, double lambda7, double m12_2, double tan_beta)
    {
        return get_BEptr()->set_param_gen(lambda1, lambda2, lambda3, lambda4, lambda5, lambda6, lambda7, m12_2, tan_beta);
    }
    
    inline bool THDM::set_param_higgs(double Lambda1, double Lambda2, double Lambda3, double Lambda4, double Lambda5, double Lambda6, double Lambda7, double m_Hp)
    {
        return get_BEptr()->set_param_higgs(Lambda1, Lambda2, Lambda3, Lambda4, Lambda5, Lambda6, Lambda7, m_Hp);
    }
    
    inline bool THDM::set_param_hybrid(double mh, double mH, double cba, double Z4, double Z5, double Z7, double tanb)
    {
        return get_BEptr()->set_param_hybrid(mh, mH, cba, Z4, Z5, Z7, tanb);
    }
    
    inline bool THDM::set_param_hybrid_sba(double mh, double mH, double sba, double Z4, double Z5, double Z7, double tanb)
    {
        return get_BEptr()->set_param_hybrid_sba(mh, mH, sba, Z4, Z5, Z7, tanb);
    }
    
    inline bool THDM::set_param_HHG(double lambda1, double lambda2, double lambda3, double lambda4, double lambda5, double lambda6, double tan_beta)
    {
        return get_BEptr()->set_param_HHG(lambda1, lambda2, lambda3, lambda4, lambda5, lambda6, tan_beta);
    }
    
    inline bool THDM::set_param_phys(double m_h, double m_H, double m_A, double m_Hp, double sba, double lambda6, double lambda7, double m12_2, double tan_beta)
    {
        return get_BEptr()->set_param_phys(m_h, m_H, m_A, m_Hp, sba, lambda6, lambda7, m12_2, tan_beta);
    }
    
    inline bool THDM::set_param_sm(double mh)
    {
        return get_BEptr()->set_param_sm(mh);
    }
    
    inline bool THDM::set_MSSM(double m_A, double tan_beta)
    {
        return get_BEptr()->set_MSSM(m_A, tan_beta);
    }
    
    inline bool THDM::set_hMSSM(double mh, double mA, double tanb)
    {
        return get_BEptr()->set_hMSSM(mh, mA, tanb);
    }
    
    inline bool THDM::set_inert(double m_h, double m_H, double m_A, double m_Hp, double lambda2, double lambda3)
    {
        return get_BEptr()->set_inert(m_h, m_H, m_A, m_Hp, lambda2, lambda3);
    }
    
    inline void THDM::get_param_gen(double& lambda1, double& lambda2, double& lambda3, double& lambda4, double& lambda5, double& lambda6, double& lambda7, double& m12_2, double& tan_beta)
    {
        get_BEptr()->get_param_gen(lambda1, lambda2, lambda3, lambda4, lambda5, lambda6, lambda7, m12_2, tan_beta);
    }
    
    inline void THDM::get_param_higgs(double& Lambda1, double& Lambda2, double& Lambda3, double& Lambda4, double& Lambda5, double& Lambda6, double& Lambda7, double& m_Hp)
    {
        get_BEptr()->get_param_higgs(Lambda1, Lambda2, Lambda3, Lambda4, Lambda5, Lambda6, Lambda7, m_Hp);
    }
    
    inline void THDM::get_param_hybrid(double& m_h, double& m_H, double& sba, double& Z4, double& Z5, double& Z7, double& tan_beta)
    {
        get_BEptr()->get_param_hybrid(m_h, m_H, sba, Z4, Z5, Z7, tan_beta);
    }
    
    inline void THDM::get_param_HHG(double& lambda1, double& lambda2, double& lambda3, double& lambda4, double& lambda5, double& lambda6, double& tan_beta)
    {
        get_BEptr()->get_param_HHG(lambda1, lambda2, lambda3, lambda4, lambda5, lambda6, tan_beta);
    }
    
    inline void THDM::get_param_phys(double& m_h, double& m_H, double& m_A, double& m_Hp, double& sba, double& lambda6, double& lambda7, double& m12_2, double& tan_beta)
    {
        get_BEptr()->get_param_phys(m_h, m_H, m_A, m_Hp, sba, lambda6, lambda7, m12_2, tan_beta);
    }
    
    inline void THDM::recalc_tan_beta(double tan_beta)
    {
        get_BEptr()->recalc_tan_beta(tan_beta);
    }
    
    inline double THDM::get_hmass(int h)
    {
        return get_BEptr()->get_hmass(h);
    }
    
    inline double THDM::get_sba()
    {
        return get_BEptr()->get_sba();
    }
    
    inline double THDM::get_cba()
    {
        return get_BEptr()->get_cba();
    }
    
    inline ::std::complex<double> THDM::get_qki(int k, int i)
    {
        return get_BEptr()->get_qki(k, i);
    }
    
    inline void THDM::set_yukawas_type(int type)
    {
        get_BEptr()->set_yukawas_type(type);
    }
    
    inline int THDM::get_yukawas_type()
    {
        return get_BEptr()->get_yukawas_type();
    }
    
    inline void THDM::set_yukawas_down(double rhod, double rhos, double rhob)
    {
        get_BEptr()->set_yukawas_down(rhod, rhos, rhob);
    }
    
    inline void THDM::set_yukawas_up(double rhou, double rhoc, double rhot)
    {
        get_BEptr()->set_yukawas_up(rhou, rhoc, rhot);
    }
    
    inline void THDM::set_yukawas_lepton(double rhoe, double rhomu, double rhotau)
    {
        get_BEptr()->set_yukawas_lepton(rhoe, rhomu, rhotau);
    }
    
    inline void THDM::set_yukawas_down(::std::complex<double> rho11, ::std::complex<double> rho22, ::std::complex<double> rho33, ::std::complex<double> rho12, ::std::complex<double> rho13, ::std::complex<double> rho23, ::std::complex<double> rho21, ::std::complex<double> rho31, ::std::complex<double> rho32)
    {
        get_BEptr()->set_yukawas_down(rho11, rho22, rho33, rho12, rho13, rho23, rho21, rho31, rho32);
    }
    
    inline void THDM::set_yukawas_up(::std::complex<double> rho11, ::std::complex<double> rho22, ::std::complex<double> rho33, ::std::complex<double> rho12, ::std::complex<double> rho13, ::std::complex<double> rho23, ::std::complex<double> rho21, ::std::complex<double> rho31, ::std::complex<double> rho32)
    {
        get_BEptr()->set_yukawas_up(rho11, rho22, rho33, rho12, rho13, rho23, rho21, rho31, rho32);
    }
    
    inline void THDM::set_yukawas_lepton(::std::complex<double> rho11, ::std::complex<double> rho22, ::std::complex<double> rho33, ::std::complex<double> rho12, ::std::complex<double> rho13, ::std::complex<double> rho23, ::std::complex<double> rho21, ::std::complex<double> rho31, ::std::complex<double> rho32)
    {
        get_BEptr()->set_yukawas_lepton(rho11, rho22, rho33, rho12, rho13, rho23, rho21, rho31, rho32);
    }
    
    inline void THDM::set_yukawas_inert()
    {
        get_BEptr()->set_yukawas_inert();
    }
    
    inline void THDM::get_yukawas_down(::std::complex<double>& rhod, ::std::complex<double>& rhos, ::std::complex<double>& rhob)
    {
        get_BEptr()->get_yukawas_down(rhod, rhos, rhob);
    }
    
    inline void THDM::get_yukawas_up(::std::complex<double>& rhou, ::std::complex<double>& rhoc, ::std::complex<double>& rhot)
    {
        get_BEptr()->get_yukawas_up(rhou, rhoc, rhot);
    }
    
    inline void THDM::get_yukawas_lepton(::std::complex<double>& rhoe, ::std::complex<double>& rhomu, ::std::complex<double>& rhotau)
    {
        get_BEptr()->get_yukawas_lepton(rhoe, rhomu, rhotau);
    }
    
    inline void THDM::get_kappa_down(::std::complex<double>& kd, ::std::complex<double>& ks, ::std::complex<double>& kb)
    {
        get_BEptr()->get_kappa_down(kd, ks, kb);
    }
    
    inline void THDM::get_kappa_up(::std::complex<double>& ku, ::std::complex<double>& kc, ::std::complex<double>& kt)
    {
        get_BEptr()->get_kappa_up(ku, kc, kt);
    }
    
    inline void THDM::get_kappa_lepton(::std::complex<double>& ke, ::std::complex<double>& kmu, ::std::complex<double>& ktau)
    {
        get_BEptr()->get_kappa_lepton(ke, kmu, ktau);
    }
    
    inline void THDM::get_kappa_down(double mu, ::std::complex<double>& kd, ::std::complex<double>& ks, ::std::complex<double>& kb)
    {
        get_BEptr()->get_kappa_down(mu, kd, ks, kb);
    }
    
    inline void THDM::get_kappa_up(double mu, ::std::complex<double>& ku, ::std::complex<double>& kc, ::std::complex<double>& kt)
    {
        get_BEptr()->get_kappa_up(mu, ku, kc, kt);
    }
    
    inline void THDM::get_kappa_lepton(double mu, ::std::complex<double>& ke, ::std::complex<double>& kmu, ::std::complex<double>& ktau)
    {
        get_BEptr()->get_kappa_lepton(mu, ke, kmu, ktau);
    }
    
    inline void THDM::get_rho_down(double mu, ::std::complex<double>& rd, ::std::complex<double>& rs, ::std::complex<double>& rb)
    {
        get_BEptr()->get_rho_down(mu, rd, rs, rb);
    }
    
    inline void THDM::get_rho_up(double mu, ::std::complex<double>& ru, ::std::complex<double>& rc, ::std::complex<double>& rt)
    {
        get_BEptr()->get_rho_up(mu, ru, rc, rt);
    }
    
    inline void THDM::get_rho_lepton(double mu, ::std::complex<double>& re, ::std::complex<double>& rmu, ::std::complex<double>& rtau)
    {
        get_BEptr()->get_rho_lepton(mu, re, rmu, rtau);
    }
    
    inline void THDM::get_coupling_hdd(int h, int f1, int f2, ::std::complex<double>& cs, ::std::complex<double>& cp)
    {
        get_BEptr()->get_coupling_hdd(h, f1, f2, cs, cp);
    }
    
    inline void THDM::get_coupling_huu(int h, int f1, int f2, ::std::complex<double>& cs, ::std::complex<double>& cp)
    {
        get_BEptr()->get_coupling_huu(h, f1, f2, cs, cp);
    }
    
    inline void THDM::get_coupling_hdu(int h, int d, int u, ::std::complex<double>& cs, ::std::complex<double>& cp)
    {
        get_BEptr()->get_coupling_hdu(h, d, u, cs, cp);
    }
    
    inline void THDM::get_coupling_hud(int h, int d, int u, ::std::complex<double>& cs, ::std::complex<double>& cp)
    {
        get_BEptr()->get_coupling_hud(h, d, u, cs, cp);
    }
    
    inline void THDM::get_coupling_hll(int h, int f1, int f2, ::std::complex<double>& cs, ::std::complex<double>& cp)
    {
        get_BEptr()->get_coupling_hll(h, f1, f2, cs, cp);
    }
    
    inline void THDM::get_coupling_hln(int h, int l, int n, ::std::complex<double>& cs, ::std::complex<double>& cp)
    {
        get_BEptr()->get_coupling_hln(h, l, n, cs, cp);
    }
    
    inline void THDM::get_coupling_vvh(int v1, int v2, int h, ::std::complex<double>& c)
    {
        get_BEptr()->get_coupling_vvh(v1, v2, h, c);
    }
    
    inline void THDM::get_coupling_vhh(int v, int h1, int h2, ::std::complex<double>& c)
    {
        get_BEptr()->get_coupling_vhh(v, h1, h2, c);
    }
    
    inline void THDM::get_coupling_hhh(int h1, int h2, int h3, ::std::complex<double>& c)
    {
        get_BEptr()->get_coupling_hhh(h1, h2, h3, c);
    }
    
    inline void THDM::get_coupling_vvhh(int v1, int v2, int h1, int h2, ::std::complex<double>& c)
    {
        get_BEptr()->get_coupling_vvhh(v1, v2, h1, h2, c);
    }
    
    inline void THDM::get_coupling_hhhh(int h1, int h2, int h3, int h4, ::std::complex<double>& c)
    {
        get_BEptr()->get_coupling_hhhh(h1, h2, h3, h4, c);
    }
    
    inline double THDM::calc_unitarity()
    {
        return get_BEptr()->calc_unitarity();
    }
    
    inline bool THDM::check_unitarity(double unitarity_limit)
    {
        return get_BEptr()->check_unitarity(unitarity_limit);
    }
    
    inline bool THDM::check_unitarity()
    {
        return get_BEptr()->check_unitarity__BOSS();
    }
    
    inline void THDM::calc_perturbativity(::std::complex<double>& gmax, int& imax, int& jmax, int& kmax, int& lmax)
    {
        get_BEptr()->calc_perturbativity(gmax, imax, jmax, kmax, lmax);
    }
    
    inline bool THDM::check_perturbativity(double perturbativity_limit)
    {
        return get_BEptr()->check_perturbativity(perturbativity_limit);
    }
    
    inline bool THDM::check_perturbativity()
    {
        return get_BEptr()->check_perturbativity__BOSS();
    }
    
    inline bool THDM::check_stability()
    {
        return get_BEptr()->check_stability();
    }
    
    inline void THDM::print_param_gen()
    {
        get_BEptr()->print_param_gen();
    }
    
    inline void THDM::print_param_higgs()
    {
        get_BEptr()->print_param_higgs();
    }
    
    inline void THDM::print_param_hybrid()
    {
        get_BEptr()->print_param_hybrid();
    }
    
    inline void THDM::print_param_phys()
    {
        get_BEptr()->print_param_phys();
    }
    
    inline void THDM::print_param_HHG()
    {
        get_BEptr()->print_param_HHG();
    }
    
    inline void THDM::print_yukawas()
    {
        get_BEptr()->print_yukawas();
    }
    
    inline void THDM::print_hdecay()
    {
        get_BEptr()->print_hdecay();
    }
    
    inline bool THDM::read_LesHouches(const char* file)
    {
        return get_BEptr()->read_LesHouches(file);
    }
    
    inline double THDM::get_alpha()
    {
        return get_BEptr()->get_alpha();
    }
    
    
    // Wrappers for original constructors: 
    inline THDM::THDM() :
        WrapperBase(__factory0()),
        EPS( get_BEptr()->EPS_ref__BOSS())
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Special pointer-based constructor: 
    inline THDM::THDM(Abstract_THDM* in) :
        WrapperBase(in),
        EPS( get_BEptr()->EPS_ref__BOSS())
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Copy constructor: 
    inline THDM::THDM(const THDM& in) :
        WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
        EPS( get_BEptr()->EPS_ref__BOSS())
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Assignment operator: 
    inline THDM& THDM::operator=(const THDM& in)
    {
        if (this != &in)
        {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
        }
        return *this;
    }
    
    
    // Destructor: 
    inline THDM::~THDM()
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
    inline Abstract_THDM* THDM::get_BEptr() const
    {
        return dynamic_cast<Abstract_THDM*>(BEptr);
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_THDM_def_THDMC_1_8_0_h__ */
