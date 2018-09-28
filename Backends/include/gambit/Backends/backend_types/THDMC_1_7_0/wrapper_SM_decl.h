#ifndef __wrapper_SM_decl_THDMC_1_7_0_h__
#define __wrapper_SM_decl_THDMC_1_7_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_SM.h"
#include <complex>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    class SM : public WrapperBase
    {
            // Member variables: 
        public:
            // -- Static factory pointers: 
            static Abstract_SM* (*__factory0)();
    
            // -- Other member variables: 
        public:
            const double& alpha;
            const double& alpha0;
            const double& GF;
            const double& MZ;
            const double& MW;
            const double& alpha_s;
            const double& GammaZ;
            const double& GammaW;
            const double& md_p;
            const double& mu_p;
            const double& ms_p;
            const double& Q_ms;
            const double& mc_p;
            const double& mb_p;
            const double& mt_p;
            const double& me_p;
            const double& mmu_p;
            const double& mtau_p;
            const std::complex<double>& Vud;
            const std::complex<double>& Vus;
            const std::complex<double>& Vub;
            const std::complex<double>& Vcd;
            const std::complex<double>& Vcs;
            const std::complex<double>& Vcb;
            const std::complex<double>& Vtd;
            const std::complex<double>& Vts;
            const std::complex<double>& Vtb;
            const double& Q_HD;
            const bool& b_HD;
            const double& ms_5;
            const double& mc_5;
            const double& mb_5;
            const double& mt_5;
            double& m_alpha;
            double& m_alpha0;
            double& m_GF;
            double& m_s2tW;
            double& m_alpha_s;
            double (&m_md_p)[3];
            double (&m_mu_p)[3];
            double (&m_ml_p)[3];
            double& m_MW;
            double& m_MZ;
            double& m_GammaW;
            double& m_GammaZ;
            std::complex<double> (&m_CKM)[3][3];
            double (&m_qmass_ms)[7];
    
            // Member functions: 
        public:
            void set_alpha(double alpha_in);
    
            void set_alpha0(double alpha_in);
    
            void set_GF(double GF_in);
    
            void set_MZ(double MZ_in);
    
            void set_MW(double MW_in);
    
            void set_gamma_Z(double GammaZ_in);
    
            void set_gamma_W(double GammaW_in);
    
            void set_alpha_s(double alpha_s_in);
    
            double get_alpha();
    
            double get_alpha0();
    
            double get_GF();
    
            double get_sintw();
    
            double get_costw();
    
            double get_g();
    
            double get_gprime();
    
            double get_e();
    
            double get_alpha_s();
    
            double get_MW();
    
            double get_gamma_W();
    
            double get_MZ();
    
            double get_gamma_Z();
    
            double get_v();
    
            double get_v2();
    
            double get_vmass(int v);
    
            double get_gamma_V(int v);
    
            void set_diagonal_CKM();
    
            double get_CKM_element(int i, int j);
    
            ::std::complex<double> get_CKM_element_complex(int i, int j);
    
            void set_CKM_element(int i, int j, double Vij);
    
            void set_CKM_element_complex(int i, int j, ::std::complex<double> Vij);
    
            void set_lmass_pole(int l, double lmass_in);
    
            void set_qmass_pole(int q, double qmass_in);
    
            void set_qmass_msbar(int flav, double qmass_in);
    
            void set_dmass_pole(int d, double dmass_in);
    
            void set_umass_pole(int u, double umass_in);
    
            double get_qmass_pole(int q);
    
            double get_dmass_pole(int d);
    
            double get_umass_pole(int u);
    
            double get_lmass_pole(int l);
    
            double get_qmass_MSbar(int q);
    
            double get_dmass_MSbar(int d);
    
            double get_umass_MSbar(int u);
    
            double run_qmass_MSbar(double quark_mass, double Qinit, double Qfin, double mtop, double mbot);
    
            double run_alphas_MSbar(double Q, double mtop, double mbot);
    
            int get_Nactivef(double M);
    
            double get_gamma_top();
    
            double get_gamma_tWd(int d);
    
            void clear_lookup();
    
            double m_threshold(double as);
    
            double RQ(double as, int nf, int loops);
    
            double QCD_beta(int c, int nf);
    
    
            // Wrappers for original constructors: 
        public:
            SM();
    
            // Special pointer-based constructor: 
            SM(Abstract_SM* in);
    
            // Copy constructor: 
            SM(const SM& in);
    
            // Assignment operator: 
            SM& operator=(const SM& in);
    
            // Destructor: 
            ~SM();
    
            // Returns correctly casted pointer to Abstract class: 
            Abstract_SM* get_BEptr() const;
    
    };
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SM_decl_THDMC_1_7_0_h__ */
