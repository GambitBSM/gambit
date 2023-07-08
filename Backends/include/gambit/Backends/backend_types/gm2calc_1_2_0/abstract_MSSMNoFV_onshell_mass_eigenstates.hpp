#ifndef __abstract_MSSMNoFV_onshell_mass_eigenstates_gm2calc_1_2_0_hpp__
#define __abstract_MSSMNoFV_onshell_mass_eigenstates_gm2calc_1_2_0_hpp__

#include <cstddef>
#include <iostream>
#include <string>
#include <ostream>
#include <Eigen/Core>
#include <complex>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_MSSMNoFV_onshell_physical_decl.hpp"
#include "wrapper_MSSMNoFV_onshell_problems_decl.hpp"
#include "wrapper_MSSMNoFV_onshell_soft_parameters_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   namespace gm2calc
   {
      class Abstract_MSSMNoFV_onshell_mass_eigenstates : virtual public gm2calc::Abstract_MSSMNoFV_onshell_soft_parameters
      {
         public:
   
            virtual void calculate_DRbar_masses() =0;
   
            virtual void clear() =0;
   
            virtual void clear_DRbar_parameters() =0;
   
            virtual void copy_DRbar_masses_to_pole_masses() =0;
   
            virtual void do_force_output(bool) =0;
   
            virtual bool do_force_output() const =0;
   
            virtual void reorder_DRbar_masses() =0;
   
            virtual void reorder_pole_masses() =0;
   
            virtual void set_physical__BOSS(const gm2calc::Abstract_MSSMNoFV_onshell_physical&) =0;
   
            virtual const gm2calc::Abstract_MSSMNoFV_onshell_physical& get_physical__BOSS() const =0;
   
            virtual gm2calc::Abstract_MSSMNoFV_onshell_physical& get_physical__BOSS() =0;
   
            virtual const gm2calc::Abstract_MSSMNoFV_onshell_problems& get_problems__BOSS() const =0;
   
            virtual gm2calc::Abstract_MSSMNoFV_onshell_problems& get_problems__BOSS() =0;
   
            virtual int solve_ewsb_tree_level() =0;
   
            virtual int solve_ewsb() =0;
   
            virtual ::std::string name() const =0;
   
            virtual void print(std::ostream&) const =0;
   
            virtual double get_MVG() const =0;
   
            virtual double get_MGlu() const =0;
   
            virtual double get_MVP() const =0;
   
            virtual double get_MVZ() const =0;
   
            virtual double get_MFd() const =0;
   
            virtual double get_MFs() const =0;
   
            virtual double get_MFb() const =0;
   
            virtual double get_MFu() const =0;
   
            virtual double get_MFc() const =0;
   
            virtual double get_MFt() const =0;
   
            virtual double get_MFve() const =0;
   
            virtual double get_MFvm() const =0;
   
            virtual double get_MFvt() const =0;
   
            virtual double get_MFe() const =0;
   
            virtual double get_MFm() const =0;
   
            virtual double get_MFtau() const =0;
   
            virtual double get_MSveL() const =0;
   
            virtual double get_MSvmL() const =0;
   
            virtual double get_MSvtL() const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MSd() const =0;
   
            virtual double get_MSd(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MSu() const =0;
   
            virtual double get_MSu(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MSe() const =0;
   
            virtual double get_MSe(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MSm() const =0;
   
            virtual double get_MSm(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MStau() const =0;
   
            virtual double get_MStau(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MSs() const =0;
   
            virtual double get_MSs(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MSc() const =0;
   
            virtual double get_MSc(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MSb() const =0;
   
            virtual double get_MSb(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MSt() const =0;
   
            virtual double get_MSt(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_Mhh() const =0;
   
            virtual double get_Mhh(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MAh() const =0;
   
            virtual double get_MAh(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MHpm() const =0;
   
            virtual double get_MHpm(int) const =0;
   
            virtual const ::Eigen::Array<double, 4, 1, 0>& get_MChi() const =0;
   
            virtual double get_MChi(int) const =0;
   
            virtual const ::Eigen::Array<double, 2, 1, 0>& get_MCha() const =0;
   
            virtual double get_MCha(int) const =0;
   
            virtual double get_MVWm() const =0;
   
            virtual ::Eigen::Array<double, 1, 1, 0> get_MChargedHiggs() const =0;
   
            virtual ::Eigen::Array<double, 1, 1, 0> get_MPseudoscalarHiggs() const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZD() const =0;
   
            virtual double get_ZD(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZU() const =0;
   
            virtual double get_ZU(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZE() const =0;
   
            virtual double get_ZE(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZM() const =0;
   
            virtual double get_ZM(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZTau() const =0;
   
            virtual double get_ZTau(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZS() const =0;
   
            virtual double get_ZS(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZC() const =0;
   
            virtual double get_ZC(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZB() const =0;
   
            virtual double get_ZB(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZT() const =0;
   
            virtual double get_ZT(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZH() const =0;
   
            virtual double get_ZH(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZA() const =0;
   
            virtual double get_ZA(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_ZP() const =0;
   
            virtual double get_ZP(int, int) const =0;
   
            virtual const ::Eigen::Matrix<std::complex<double>, 4, 4, 0>& get_ZN() const =0;
   
            virtual const ::std::complex<double>& get_ZN(int, int) const =0;
   
            virtual const ::Eigen::Matrix<std::complex<double>, 2, 2, 0>& get_UM() const =0;
   
            virtual const ::std::complex<double>& get_UM(int, int) const =0;
   
            virtual const ::Eigen::Matrix<std::complex<double>, 2, 2, 0>& get_UP() const =0;
   
            virtual const ::std::complex<double>& get_UP(int, int) const =0;
   
            virtual void set_PhaseGlu(std::complex<double>) =0;
   
            virtual ::std::complex<double> get_PhaseGlu() const =0;
   
            virtual double get_mass_matrix_VG() const =0;
   
            virtual void calculate_MVG() =0;
   
            virtual double get_mass_matrix_Glu() const =0;
   
            virtual void calculate_MGlu() =0;
   
            virtual double get_mass_matrix_VP() const =0;
   
            virtual void calculate_MVP() =0;
   
            virtual double get_mass_matrix_VZ() const =0;
   
            virtual void calculate_MVZ() =0;
   
            virtual double get_mass_matrix_Fd() const =0;
   
            virtual void calculate_MFd() =0;
   
            virtual double get_mass_matrix_Fs() const =0;
   
            virtual void calculate_MFs() =0;
   
            virtual double get_mass_matrix_Fb() const =0;
   
            virtual void calculate_MFb() =0;
   
            virtual double get_mass_matrix_Fu() const =0;
   
            virtual void calculate_MFu() =0;
   
            virtual double get_mass_matrix_Fc() const =0;
   
            virtual void calculate_MFc() =0;
   
            virtual double get_mass_matrix_Ft() const =0;
   
            virtual void calculate_MFt() =0;
   
            virtual double get_mass_matrix_Fve() const =0;
   
            virtual void calculate_MFve() =0;
   
            virtual double get_mass_matrix_Fvm() const =0;
   
            virtual void calculate_MFvm() =0;
   
            virtual double get_mass_matrix_Fvt() const =0;
   
            virtual void calculate_MFvt() =0;
   
            virtual double get_mass_matrix_Fe() const =0;
   
            virtual void calculate_MFe() =0;
   
            virtual double get_mass_matrix_Fm() const =0;
   
            virtual void calculate_MFm() =0;
   
            virtual double get_mass_matrix_Ftau() const =0;
   
            virtual void calculate_MFtau() =0;
   
            virtual double get_mass_matrix_SveL() const =0;
   
            virtual void calculate_MSveL() =0;
   
            virtual double get_mass_matrix_SvmL() const =0;
   
            virtual void calculate_MSvmL() =0;
   
            virtual double get_mass_matrix_SvtL() const =0;
   
            virtual void calculate_MSvtL() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Sd() const =0;
   
            virtual void calculate_MSd() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Su() const =0;
   
            virtual void calculate_MSu() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Se() const =0;
   
            virtual void calculate_MSe() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Sm() const =0;
   
            virtual void calculate_MSm() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Stau() const =0;
   
            virtual void calculate_MStau() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Ss() const =0;
   
            virtual void calculate_MSs() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Sc() const =0;
   
            virtual void calculate_MSc() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Sb() const =0;
   
            virtual void calculate_MSb() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_St() const =0;
   
            virtual void calculate_MSt() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_hh() const =0;
   
            virtual void calculate_Mhh() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Ah() const =0;
   
            virtual void calculate_MAh() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Hpm() const =0;
   
            virtual void calculate_MHpm() =0;
   
            virtual ::Eigen::Matrix<double, 4, 4, 0> get_mass_matrix_Chi() const =0;
   
            virtual void calculate_MChi() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0> get_mass_matrix_Cha() const =0;
   
            virtual void calculate_MCha() =0;
   
            virtual double get_mass_matrix_VWm() const =0;
   
            virtual void calculate_MVWm() =0;
   
            virtual double get_ewsb_eq_hh_1() const =0;
   
            virtual double get_ewsb_eq_hh_2() const =0;
   
            virtual double ThetaW() const =0;
   
            virtual double v() const =0;
   
         public:
            using gm2calc::Abstract_MSSMNoFV_onshell_soft_parameters::pointer_assign__BOSS;
            virtual void pointer_assign__BOSS(Abstract_MSSMNoFV_onshell_mass_eigenstates*) =0;
            virtual Abstract_MSSMNoFV_onshell_mass_eigenstates* pointer_copy__BOSS() =0;
   
         private:
            MSSMNoFV_onshell_mass_eigenstates* wptr;
            bool delete_wrapper;
         public:
            MSSMNoFV_onshell_mass_eigenstates* get_wptr() { return wptr; }
            void set_wptr(MSSMNoFV_onshell_mass_eigenstates* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
         public:
            Abstract_MSSMNoFV_onshell_mass_eigenstates()
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell_mass_eigenstates(const Abstract_MSSMNoFV_onshell_mass_eigenstates& in) : 
               gm2calc::Abstract_MSSMNoFV_onshell_susy_parameters(in), gm2calc::Abstract_MSSMNoFV_onshell_soft_parameters(in)
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell_mass_eigenstates& operator=(const Abstract_MSSMNoFV_onshell_mass_eigenstates&) { return *this; }
   
            virtual void init_wrapper() =0;
   
            MSSMNoFV_onshell_mass_eigenstates* get_init_wptr()
            {
               init_wrapper();
               return wptr;
            }
   
            MSSMNoFV_onshell_mass_eigenstates& get_init_wref()
            {
               init_wrapper();
               return *wptr;
            }
   
            virtual ~Abstract_MSSMNoFV_onshell_mass_eigenstates() =0;
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_MSSMNoFV_onshell_mass_eigenstates_gm2calc_1_2_0_hpp__ */
