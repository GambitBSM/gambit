#ifndef __wrapper_THDM_decl_THDMC_1_8_0_h__
#define __wrapper_THDM_decl_THDMC_1_8_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_THDM.h"
#include "wrapper_SM_decl.h"
#include <complex>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    class THDM : public WrapperBase
    {
            // Member variables: 
        public:
            // -- Static factory pointers: 
            static Abstract_THDM* (*__factory0)();
    
            // -- Other member variables: 
        public:
            const double& EPS;
    
            // Member functions: 
        public:
            void free_gsl();
    
            void set_SM(SM sm_in);
    
            SM get_SM();
    
            SM* get_SM_pointer();
    
            bool set_param_full(double lambda1, double lambda2, double lambda3, double lambda4, double lambda5, double lambda6, double lambda7, double m12_2, double tan_beta, double m_h, double m_H, double m_A, double m_Hp, double sba);
    
            bool set_param_gen(double lambda1, double lambda2, double lambda3, double lambda4, double lambda5, double lambda6, double lambda7, double m12_2, double tan_beta);
    
            bool set_param_higgs(double Lambda1, double Lambda2, double Lambda3, double Lambda4, double Lambda5, double Lambda6, double Lambda7, double m_Hp);
    
            bool set_param_hybrid(double mh, double mH, double cba, double Z4, double Z5, double Z7, double tanb);
    
            bool set_param_hybrid_sba(double mh, double mH, double sba, double Z4, double Z5, double Z7, double tanb);
    
            bool set_param_HHG(double lambda1, double lambda2, double lambda3, double lambda4, double lambda5, double lambda6, double tan_beta);
    
            bool set_param_phys(double m_h, double m_H, double m_A, double m_Hp, double sba, double lambda6, double lambda7, double m12_2, double tan_beta);
    
            bool set_param_sm(double mh);
    
            bool set_MSSM(double m_A, double tan_beta);
    
            bool set_hMSSM(double mh, double mA, double tanb);
    
            bool set_inert(double m_h, double m_H, double m_A, double m_Hp, double lambda2, double lambda3);
    
            void get_param_gen(double& lambda1, double& lambda2, double& lambda3, double& lambda4, double& lambda5, double& lambda6, double& lambda7, double& m12_2, double& tan_beta);
    
            void get_param_higgs(double& Lambda1, double& Lambda2, double& Lambda3, double& Lambda4, double& Lambda5, double& Lambda6, double& Lambda7, double& m_Hp);
    
            void get_param_hybrid(double& m_h, double& m_H, double& sba, double& Z4, double& Z5, double& Z7, double& tan_beta);
    
            void get_param_HHG(double& lambda1, double& lambda2, double& lambda3, double& lambda4, double& lambda5, double& lambda6, double& tan_beta);
    
            void get_param_phys(double& m_h, double& m_H, double& m_A, double& m_Hp, double& sba, double& lambda6, double& lambda7, double& m12_2, double& tan_beta);
    
            void recalc_tan_beta(double tan_beta);
    
            double get_hmass(int h);
    
            double get_sba();
    
            double get_cba();
    
            ::std::complex<double> get_qki(int k, int i);
    
            void set_yukawas_type(int type);
    
            int get_yukawas_type();
    
            void set_yukawas_down(double rhod, double rhos, double rhob);
    
            void set_yukawas_up(double rhou, double rhoc, double rhot);
    
            void set_yukawas_lepton(double rhoe, double rhomu, double rhotau);
    
            void set_yukawas_down(::std::complex<double> rho11, ::std::complex<double> rho22, ::std::complex<double> rho33, ::std::complex<double> rho12, ::std::complex<double> rho13, ::std::complex<double> rho23, ::std::complex<double> rho21, ::std::complex<double> rho31, ::std::complex<double> rho32);
    
            void set_yukawas_up(::std::complex<double> rho11, ::std::complex<double> rho22, ::std::complex<double> rho33, ::std::complex<double> rho12, ::std::complex<double> rho13, ::std::complex<double> rho23, ::std::complex<double> rho21, ::std::complex<double> rho31, ::std::complex<double> rho32);
    
            void set_yukawas_lepton(::std::complex<double> rho11, ::std::complex<double> rho22, ::std::complex<double> rho33, ::std::complex<double> rho12, ::std::complex<double> rho13, ::std::complex<double> rho23, ::std::complex<double> rho21, ::std::complex<double> rho31, ::std::complex<double> rho32);
    
            void set_yukawas_inert();
    
            void get_yukawas_down(::std::complex<double>& rhod, ::std::complex<double>& rhos, ::std::complex<double>& rhob);
    
            void get_yukawas_up(::std::complex<double>& rhou, ::std::complex<double>& rhoc, ::std::complex<double>& rhot);
    
            void get_yukawas_lepton(::std::complex<double>& rhoe, ::std::complex<double>& rhomu, ::std::complex<double>& rhotau);
    
            void get_kappa_down(::std::complex<double>& kd, ::std::complex<double>& ks, ::std::complex<double>& kb);
    
            void get_kappa_up(::std::complex<double>& ku, ::std::complex<double>& kc, ::std::complex<double>& kt);
    
            void get_kappa_lepton(::std::complex<double>& ke, ::std::complex<double>& kmu, ::std::complex<double>& ktau);
    
            void get_kappa_down(double mu, ::std::complex<double>& kd, ::std::complex<double>& ks, ::std::complex<double>& kb);
    
            void get_kappa_up(double mu, ::std::complex<double>& ku, ::std::complex<double>& kc, ::std::complex<double>& kt);
    
            void get_kappa_lepton(double mu, ::std::complex<double>& ke, ::std::complex<double>& kmu, ::std::complex<double>& ktau);
    
            void get_rho_down(double mu, ::std::complex<double>& rd, ::std::complex<double>& rs, ::std::complex<double>& rb);
    
            void get_rho_up(double mu, ::std::complex<double>& ru, ::std::complex<double>& rc, ::std::complex<double>& rt);
    
            void get_rho_lepton(double mu, ::std::complex<double>& re, ::std::complex<double>& rmu, ::std::complex<double>& rtau);
    
            void get_coupling_hdd(int h, int f1, int f2, ::std::complex<double>& cs, ::std::complex<double>& cp);
    
            void get_coupling_huu(int h, int f1, int f2, ::std::complex<double>& cs, ::std::complex<double>& cp);
    
            void get_coupling_hdu(int h, int d, int u, ::std::complex<double>& cs, ::std::complex<double>& cp);
    
            void get_coupling_hud(int h, int d, int u, ::std::complex<double>& cs, ::std::complex<double>& cp);
    
            void get_coupling_hll(int h, int f1, int f2, ::std::complex<double>& cs, ::std::complex<double>& cp);
    
            void get_coupling_hln(int h, int l, int n, ::std::complex<double>& cs, ::std::complex<double>& cp);
    
            void get_coupling_vvh(int v1, int v2, int h, ::std::complex<double>& c);
    
            void get_coupling_vhh(int v, int h1, int h2, ::std::complex<double>& c);
    
            void get_coupling_hhh(int h1, int h2, int h3, ::std::complex<double>& c);
    
            void get_coupling_vvhh(int v1, int v2, int h1, int h2, ::std::complex<double>& c);
    
            void get_coupling_hhhh(int h1, int h2, int h3, int h4, ::std::complex<double>& c);
    
            double calc_unitarity();
    
            bool check_unitarity(double unitarity_limit);
    
            bool check_unitarity();
    
            void calc_perturbativity(::std::complex<double>& gmax, int& imax, int& jmax, int& kmax, int& lmax);
    
            bool check_perturbativity(double perturbativity_limit);
    
            bool check_perturbativity();
    
            bool check_stability();
    
            void print_param_gen();
    
            void print_param_higgs();
    
            void print_param_hybrid();
    
            void print_param_phys();
    
            void print_param_HHG();
    
            void print_yukawas();
    
            void print_hdecay();
    
            bool read_LesHouches(const char* file);
    
            double get_alpha();
    
    
            // Wrappers for original constructors: 
        public:
            THDM();
    
            // Special pointer-based constructor: 
            THDM(Abstract_THDM* in);
    
            // Copy constructor: 
            THDM(const THDM& in);
    
            // Assignment operator: 
            THDM& operator=(const THDM& in);
    
            // Destructor: 
            ~THDM();
    
            // Returns correctly casted pointer to Abstract class: 
            Abstract_THDM* get_BEptr() const;
    
    };
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_THDM_decl_THDMC_1_8_0_h__ */
