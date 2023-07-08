#ifndef __wrapper_MSSMNoFV_onshell_mass_eigenstates_decl_gm2calc_1_2_0_hpp__
#define __wrapper_MSSMNoFV_onshell_mass_eigenstates_decl_gm2calc_1_2_0_hpp__

#include <cstddef>
#include <string>
#include <ostream>
#include <Eigen/Core>
#include <complex>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_MSSMNoFV_onshell_mass_eigenstates.hpp"
#include "wrapper_MSSMNoFV_onshell_soft_parameters_decl.hpp"
#include "wrapper_MSSMNoFV_onshell_physical_decl.hpp"
#include "wrapper_MSSMNoFV_onshell_problems_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      class MSSMNoFV_onshell_mass_eigenstates : public MSSMNoFV_onshell_soft_parameters
      {
            // Member variables: 
         public:
            // -- Static factory pointers: 
            static Abstract_MSSMNoFV_onshell_mass_eigenstates* (*__factory0)();
      
            // -- Other member variables: 
      
            // Member functions: 
         public:
            void calculate_DRbar_masses();
      
            void clear();
      
            void clear_DRbar_parameters();
      
            void copy_DRbar_masses_to_pole_masses();
      
            void do_force_output(bool arg_1);
      
            bool do_force_output() const;
      
            void reorder_DRbar_masses();
      
            void reorder_pole_masses();
      
            void set_physical(const gm2calc::MSSMNoFV_onshell_physical& arg_1);
      
            const gm2calc::MSSMNoFV_onshell_physical& get_physical() const;
      
            gm2calc::MSSMNoFV_onshell_physical& get_physical();
      
            const gm2calc::MSSMNoFV_onshell_problems& get_problems() const;
      
            gm2calc::MSSMNoFV_onshell_problems& get_problems();
      
            int solve_ewsb_tree_level();
      
            int solve_ewsb();
      
            ::std::string name() const;
      
            void print(std::ostream& arg_1) const;
      
            double get_MVG() const;
      
            double get_MGlu() const;
      
            double get_MVP() const;
      
            double get_MVZ() const;
      
            double get_MFd() const;
      
            double get_MFs() const;
      
            double get_MFb() const;
      
            double get_MFu() const;
      
            double get_MFc() const;
      
            double get_MFt() const;
      
            double get_MFve() const;
      
            double get_MFvm() const;
      
            double get_MFvt() const;
      
            double get_MFe() const;
      
            double get_MFm() const;
      
            double get_MFtau() const;
      
            double get_MSveL() const;
      
            double get_MSvmL() const;
      
            double get_MSvtL() const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MSd() const;
      
            double get_MSd(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MSu() const;
      
            double get_MSu(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MSe() const;
      
            double get_MSe(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MSm() const;
      
            double get_MSm(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MStau() const;
      
            double get_MStau(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MSs() const;
      
            double get_MSs(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MSc() const;
      
            double get_MSc(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MSb() const;
      
            double get_MSb(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MSt() const;
      
            double get_MSt(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_Mhh() const;
      
            double get_Mhh(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MAh() const;
      
            double get_MAh(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MHpm() const;
      
            double get_MHpm(int i) const;
      
            const ::Eigen::Array<double, 4, 1, 0>& get_MChi() const;
      
            double get_MChi(int i) const;
      
            const ::Eigen::Array<double, 2, 1, 0>& get_MCha() const;
      
            double get_MCha(int i) const;
      
            double get_MVWm() const;
      
            ::Eigen::Array<double, 1, 1, 0> get_MChargedHiggs() const;
      
            ::Eigen::Array<double, 1, 1, 0> get_MPseudoscalarHiggs() const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZD() const;
      
            double get_ZD(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZU() const;
      
            double get_ZU(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZE() const;
      
            double get_ZE(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZM() const;
      
            double get_ZM(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZTau() const;
      
            double get_ZTau(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZS() const;
      
            double get_ZS(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZC() const;
      
            double get_ZC(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZB() const;
      
            double get_ZB(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZT() const;
      
            double get_ZT(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZH() const;
      
            double get_ZH(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZA() const;
      
            double get_ZA(int i, int k) const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_ZP() const;
      
            double get_ZP(int i, int k) const;
      
            const ::Eigen::Matrix<std::complex<double>, 4, 4, 0>& get_ZN() const;
      
            const ::std::complex<double>& get_ZN(int i, int k) const;
      
            const ::Eigen::Matrix<std::complex<double>, 2, 2, 0>& get_UM() const;
      
            const ::std::complex<double>& get_UM(int i, int k) const;
      
            const ::Eigen::Matrix<std::complex<double>, 2, 2, 0>& get_UP() const;
      
            const ::std::complex<double>& get_UP(int i, int k) const;
      
            void set_PhaseGlu(std::complex<double> PhaseGlu_);
      
            ::std::complex<double> get_PhaseGlu() const;
      
            double get_mass_matrix_VG() const;
      
            void calculate_MVG();
      
            double get_mass_matrix_Glu() const;
      
            void calculate_MGlu();
      
            double get_mass_matrix_VP() const;
      
            void calculate_MVP();
      
            double get_mass_matrix_VZ() const;
      
            void calculate_MVZ();
      
            double get_mass_matrix_Fd() const;
      
            void calculate_MFd();
      
            double get_mass_matrix_Fs() const;
      
            void calculate_MFs();
      
            double get_mass_matrix_Fb() const;
      
            void calculate_MFb();
      
            double get_mass_matrix_Fu() const;
      
            void calculate_MFu();
      
            double get_mass_matrix_Fc() const;
      
            void calculate_MFc();
      
            double get_mass_matrix_Ft() const;
      
            void calculate_MFt();
      
            double get_mass_matrix_Fve() const;
      
            void calculate_MFve();
      
            double get_mass_matrix_Fvm() const;
      
            void calculate_MFvm();
      
            double get_mass_matrix_Fvt() const;
      
            void calculate_MFvt();
      
            double get_mass_matrix_Fe() const;
      
            void calculate_MFe();
      
            double get_mass_matrix_Fm() const;
      
            void calculate_MFm();
      
            double get_mass_matrix_Ftau() const;
      
            void calculate_MFtau();
      
            double get_mass_matrix_SveL() const;
      
            void calculate_MSveL();
      
            double get_mass_matrix_SvmL() const;
      
            void calculate_MSvmL();
      
            double get_mass_matrix_SvtL() const;
      
            void calculate_MSvtL();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Sd() const;
      
            void calculate_MSd();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Su() const;
      
            void calculate_MSu();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Se() const;
      
            void calculate_MSe();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Sm() const;
      
            void calculate_MSm();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Stau() const;
      
            void calculate_MStau();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Ss() const;
      
            void calculate_MSs();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Sc() const;
      
            void calculate_MSc();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Sb() const;
      
            void calculate_MSb();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_St() const;
      
            void calculate_MSt();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_hh() const;
      
            void calculate_Mhh();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Ah() const;
      
            void calculate_MAh();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Hpm() const;
      
            void calculate_MHpm();
      
            ::Eigen::Matrix<double, 4, 4, 0> get_mass_matrix_Chi() const;
      
            void calculate_MChi();
      
            ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Cha() const;
      
            void calculate_MCha();
      
            double get_mass_matrix_VWm() const;
      
            void calculate_MVWm();
      
            double get_ewsb_eq_hh_1() const;
      
            double get_ewsb_eq_hh_2() const;
      
            double ThetaW() const;
      
            double v() const;
      
      
            // Wrappers for original constructors: 
         public:
            MSSMNoFV_onshell_mass_eigenstates();
      
            // Special pointer-based constructor: 
            MSSMNoFV_onshell_mass_eigenstates(Abstract_MSSMNoFV_onshell_mass_eigenstates* in);
      
            // Copy constructor: 
            MSSMNoFV_onshell_mass_eigenstates(const MSSMNoFV_onshell_mass_eigenstates& in);
      
            // Assignment operator: 
            MSSMNoFV_onshell_mass_eigenstates& operator=(const MSSMNoFV_onshell_mass_eigenstates& in);
      
            // Destructor: 
            ~MSSMNoFV_onshell_mass_eigenstates();
      
            // Returns correctly casted pointer to Abstract class: 
            Abstract_MSSMNoFV_onshell_mass_eigenstates* get_BEptr() const;
      
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_mass_eigenstates_decl_gm2calc_1_2_0_hpp__ */
