#ifndef __wrapper_MSSMNoFV_onshell_mass_eigenstates_def_gm2calc_1_2_0_hpp__
#define __wrapper_MSSMNoFV_onshell_mass_eigenstates_def_gm2calc_1_2_0_hpp__

#include <string>
#include <ostream>
#include <Eigen/Core>
#include <complex>
#include "wrapper_MSSMNoFV_onshell_physical_decl.hpp"
#include "wrapper_MSSMNoFV_onshell_problems_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      // Member functions: 
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_DRbar_masses()
      {
         get_BEptr()->calculate_DRbar_masses();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::clear()
      {
         get_BEptr()->clear();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::clear_DRbar_parameters()
      {
         get_BEptr()->clear_DRbar_parameters();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::copy_DRbar_masses_to_pole_masses()
      {
         get_BEptr()->copy_DRbar_masses_to_pole_masses();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::do_force_output(bool arg_1)
      {
         get_BEptr()->do_force_output(arg_1);
      }
      
      inline bool MSSMNoFV_onshell_mass_eigenstates::do_force_output() const
      {
         return get_BEptr()->do_force_output();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::reorder_DRbar_masses()
      {
         get_BEptr()->reorder_DRbar_masses();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::reorder_pole_masses()
      {
         get_BEptr()->reorder_pole_masses();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::set_physical(const gm2calc::MSSMNoFV_onshell_physical& arg_1)
      {
         get_BEptr()->set_physical__BOSS(*arg_1.get_BEptr());
      }
      
      inline const gm2calc::MSSMNoFV_onshell_physical& MSSMNoFV_onshell_mass_eigenstates::get_physical() const
      {
         return const_cast<gm2calc::Abstract_MSSMNoFV_onshell_physical&>(const_cast<const Abstract_MSSMNoFV_onshell_mass_eigenstates*>(get_BEptr())->get_physical__BOSS()).get_init_wref();
      }
      
      inline gm2calc::MSSMNoFV_onshell_physical& MSSMNoFV_onshell_mass_eigenstates::get_physical()
      {
         return get_BEptr()->get_physical__BOSS().get_init_wref();
      }
      
      inline const gm2calc::MSSMNoFV_onshell_problems& MSSMNoFV_onshell_mass_eigenstates::get_problems() const
      {
         return const_cast<gm2calc::Abstract_MSSMNoFV_onshell_problems&>(const_cast<const Abstract_MSSMNoFV_onshell_mass_eigenstates*>(get_BEptr())->get_problems__BOSS()).get_init_wref();
      }
      
      inline gm2calc::MSSMNoFV_onshell_problems& MSSMNoFV_onshell_mass_eigenstates::get_problems()
      {
         return get_BEptr()->get_problems__BOSS().get_init_wref();
      }
      
      inline int MSSMNoFV_onshell_mass_eigenstates::solve_ewsb_tree_level()
      {
         return get_BEptr()->solve_ewsb_tree_level();
      }
      
      inline int MSSMNoFV_onshell_mass_eigenstates::solve_ewsb()
      {
         return get_BEptr()->solve_ewsb();
      }
      
      inline ::std::basic_string<char> MSSMNoFV_onshell_mass_eigenstates::name() const
      {
         return get_BEptr()->name();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::print(::std::basic_ostream<char>& arg_1) const
      {
         get_BEptr()->print(arg_1);
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MVG() const
      {
         return get_BEptr()->get_MVG();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MGlu() const
      {
         return get_BEptr()->get_MGlu();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MVP() const
      {
         return get_BEptr()->get_MVP();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MVZ() const
      {
         return get_BEptr()->get_MVZ();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFd() const
      {
         return get_BEptr()->get_MFd();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFs() const
      {
         return get_BEptr()->get_MFs();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFb() const
      {
         return get_BEptr()->get_MFb();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFu() const
      {
         return get_BEptr()->get_MFu();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFc() const
      {
         return get_BEptr()->get_MFc();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFt() const
      {
         return get_BEptr()->get_MFt();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFve() const
      {
         return get_BEptr()->get_MFve();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFvm() const
      {
         return get_BEptr()->get_MFvm();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFvt() const
      {
         return get_BEptr()->get_MFvt();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFe() const
      {
         return get_BEptr()->get_MFe();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFm() const
      {
         return get_BEptr()->get_MFm();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MFtau() const
      {
         return get_BEptr()->get_MFtau();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSveL() const
      {
         return get_BEptr()->get_MSveL();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSvmL() const
      {
         return get_BEptr()->get_MSvmL();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSvtL() const
      {
         return get_BEptr()->get_MSvtL();
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MSd() const
      {
         return get_BEptr()->get_MSd();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSd(int i) const
      {
         return get_BEptr()->get_MSd(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MSu() const
      {
         return get_BEptr()->get_MSu();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSu(int i) const
      {
         return get_BEptr()->get_MSu(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MSe() const
      {
         return get_BEptr()->get_MSe();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSe(int i) const
      {
         return get_BEptr()->get_MSe(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MSm() const
      {
         return get_BEptr()->get_MSm();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSm(int i) const
      {
         return get_BEptr()->get_MSm(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MStau() const
      {
         return get_BEptr()->get_MStau();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MStau(int i) const
      {
         return get_BEptr()->get_MStau(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MSs() const
      {
         return get_BEptr()->get_MSs();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSs(int i) const
      {
         return get_BEptr()->get_MSs(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MSc() const
      {
         return get_BEptr()->get_MSc();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSc(int i) const
      {
         return get_BEptr()->get_MSc(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MSb() const
      {
         return get_BEptr()->get_MSb();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSb(int i) const
      {
         return get_BEptr()->get_MSb(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MSt() const
      {
         return get_BEptr()->get_MSt();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MSt(int i) const
      {
         return get_BEptr()->get_MSt(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_Mhh() const
      {
         return get_BEptr()->get_Mhh();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_Mhh(int i) const
      {
         return get_BEptr()->get_Mhh(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MAh() const
      {
         return get_BEptr()->get_MAh();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MAh(int i) const
      {
         return get_BEptr()->get_MAh(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MHpm() const
      {
         return get_BEptr()->get_MHpm();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MHpm(int i) const
      {
         return get_BEptr()->get_MHpm(i);
      }
      
      inline const ::Eigen::Array<double, 4, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MChi() const
      {
         return get_BEptr()->get_MChi();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MChi(int i) const
      {
         return get_BEptr()->get_MChi(i);
      }
      
      inline const ::Eigen::Array<double, 2, 1, 0>& MSSMNoFV_onshell_mass_eigenstates::get_MCha() const
      {
         return get_BEptr()->get_MCha();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MCha(int i) const
      {
         return get_BEptr()->get_MCha(i);
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_MVWm() const
      {
         return get_BEptr()->get_MVWm();
      }
      
      inline ::Eigen::Array<double, 1, 1, 0> MSSMNoFV_onshell_mass_eigenstates::get_MChargedHiggs() const
      {
         return get_BEptr()->get_MChargedHiggs();
      }
      
      inline ::Eigen::Array<double, 1, 1, 0> MSSMNoFV_onshell_mass_eigenstates::get_MPseudoscalarHiggs() const
      {
         return get_BEptr()->get_MPseudoscalarHiggs();
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZD() const
      {
         return get_BEptr()->get_ZD();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZD(int i, int k) const
      {
         return get_BEptr()->get_ZD(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZU() const
      {
         return get_BEptr()->get_ZU();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZU(int i, int k) const
      {
         return get_BEptr()->get_ZU(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZE() const
      {
         return get_BEptr()->get_ZE();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZE(int i, int k) const
      {
         return get_BEptr()->get_ZE(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZM() const
      {
         return get_BEptr()->get_ZM();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZM(int i, int k) const
      {
         return get_BEptr()->get_ZM(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZTau() const
      {
         return get_BEptr()->get_ZTau();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZTau(int i, int k) const
      {
         return get_BEptr()->get_ZTau(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZS() const
      {
         return get_BEptr()->get_ZS();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZS(int i, int k) const
      {
         return get_BEptr()->get_ZS(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZC() const
      {
         return get_BEptr()->get_ZC();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZC(int i, int k) const
      {
         return get_BEptr()->get_ZC(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZB() const
      {
         return get_BEptr()->get_ZB();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZB(int i, int k) const
      {
         return get_BEptr()->get_ZB(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZT() const
      {
         return get_BEptr()->get_ZT();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZT(int i, int k) const
      {
         return get_BEptr()->get_ZT(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZH() const
      {
         return get_BEptr()->get_ZH();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZH(int i, int k) const
      {
         return get_BEptr()->get_ZH(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZA() const
      {
         return get_BEptr()->get_ZA();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZA(int i, int k) const
      {
         return get_BEptr()->get_ZA(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZP() const
      {
         return get_BEptr()->get_ZP();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ZP(int i, int k) const
      {
         return get_BEptr()->get_ZP(i, k);
      }
      
      inline const ::Eigen::Matrix<std::complex<double>, 4, 4, 0>& MSSMNoFV_onshell_mass_eigenstates::get_ZN() const
      {
         return get_BEptr()->get_ZN();
      }
      
      inline const ::std::complex<double>& MSSMNoFV_onshell_mass_eigenstates::get_ZN(int i, int k) const
      {
         return get_BEptr()->get_ZN(i, k);
      }
      
      inline const ::Eigen::Matrix<std::complex<double>, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_UM() const
      {
         return get_BEptr()->get_UM();
      }
      
      inline const ::std::complex<double>& MSSMNoFV_onshell_mass_eigenstates::get_UM(int i, int k) const
      {
         return get_BEptr()->get_UM(i, k);
      }
      
      inline const ::Eigen::Matrix<std::complex<double>, 2, 2, 0>& MSSMNoFV_onshell_mass_eigenstates::get_UP() const
      {
         return get_BEptr()->get_UP();
      }
      
      inline const ::std::complex<double>& MSSMNoFV_onshell_mass_eigenstates::get_UP(int i, int k) const
      {
         return get_BEptr()->get_UP(i, k);
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::set_PhaseGlu(::std::complex<double> PhaseGlu_)
      {
         get_BEptr()->set_PhaseGlu(PhaseGlu_);
      }
      
      inline ::std::complex<double> MSSMNoFV_onshell_mass_eigenstates::get_PhaseGlu() const
      {
         return get_BEptr()->get_PhaseGlu();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_VG() const
      {
         return get_BEptr()->get_mass_matrix_VG();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MVG()
      {
         get_BEptr()->calculate_MVG();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Glu() const
      {
         return get_BEptr()->get_mass_matrix_Glu();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MGlu()
      {
         get_BEptr()->calculate_MGlu();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_VP() const
      {
         return get_BEptr()->get_mass_matrix_VP();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MVP()
      {
         get_BEptr()->calculate_MVP();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_VZ() const
      {
         return get_BEptr()->get_mass_matrix_VZ();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MVZ()
      {
         get_BEptr()->calculate_MVZ();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Fd() const
      {
         return get_BEptr()->get_mass_matrix_Fd();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFd()
      {
         get_BEptr()->calculate_MFd();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Fs() const
      {
         return get_BEptr()->get_mass_matrix_Fs();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFs()
      {
         get_BEptr()->calculate_MFs();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Fb() const
      {
         return get_BEptr()->get_mass_matrix_Fb();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFb()
      {
         get_BEptr()->calculate_MFb();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Fu() const
      {
         return get_BEptr()->get_mass_matrix_Fu();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFu()
      {
         get_BEptr()->calculate_MFu();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Fc() const
      {
         return get_BEptr()->get_mass_matrix_Fc();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFc()
      {
         get_BEptr()->calculate_MFc();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Ft() const
      {
         return get_BEptr()->get_mass_matrix_Ft();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFt()
      {
         get_BEptr()->calculate_MFt();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Fve() const
      {
         return get_BEptr()->get_mass_matrix_Fve();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFve()
      {
         get_BEptr()->calculate_MFve();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Fvm() const
      {
         return get_BEptr()->get_mass_matrix_Fvm();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFvm()
      {
         get_BEptr()->calculate_MFvm();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Fvt() const
      {
         return get_BEptr()->get_mass_matrix_Fvt();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFvt()
      {
         get_BEptr()->calculate_MFvt();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Fe() const
      {
         return get_BEptr()->get_mass_matrix_Fe();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFe()
      {
         get_BEptr()->calculate_MFe();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Fm() const
      {
         return get_BEptr()->get_mass_matrix_Fm();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFm()
      {
         get_BEptr()->calculate_MFm();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Ftau() const
      {
         return get_BEptr()->get_mass_matrix_Ftau();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MFtau()
      {
         get_BEptr()->calculate_MFtau();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_SveL() const
      {
         return get_BEptr()->get_mass_matrix_SveL();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSveL()
      {
         get_BEptr()->calculate_MSveL();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_SvmL() const
      {
         return get_BEptr()->get_mass_matrix_SvmL();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSvmL()
      {
         get_BEptr()->calculate_MSvmL();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_SvtL() const
      {
         return get_BEptr()->get_mass_matrix_SvtL();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSvtL()
      {
         get_BEptr()->calculate_MSvtL();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Sd() const
      {
         return get_BEptr()->get_mass_matrix_Sd();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSd()
      {
         get_BEptr()->calculate_MSd();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Su() const
      {
         return get_BEptr()->get_mass_matrix_Su();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSu()
      {
         get_BEptr()->calculate_MSu();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Se() const
      {
         return get_BEptr()->get_mass_matrix_Se();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSe()
      {
         get_BEptr()->calculate_MSe();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Sm() const
      {
         return get_BEptr()->get_mass_matrix_Sm();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSm()
      {
         get_BEptr()->calculate_MSm();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Stau() const
      {
         return get_BEptr()->get_mass_matrix_Stau();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MStau()
      {
         get_BEptr()->calculate_MStau();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Ss() const
      {
         return get_BEptr()->get_mass_matrix_Ss();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSs()
      {
         get_BEptr()->calculate_MSs();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Sc() const
      {
         return get_BEptr()->get_mass_matrix_Sc();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSc()
      {
         get_BEptr()->calculate_MSc();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Sb() const
      {
         return get_BEptr()->get_mass_matrix_Sb();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSb()
      {
         get_BEptr()->calculate_MSb();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_St() const
      {
         return get_BEptr()->get_mass_matrix_St();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MSt()
      {
         get_BEptr()->calculate_MSt();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_hh() const
      {
         return get_BEptr()->get_mass_matrix_hh();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_Mhh()
      {
         get_BEptr()->calculate_Mhh();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Ah() const
      {
         return get_BEptr()->get_mass_matrix_Ah();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MAh()
      {
         get_BEptr()->calculate_MAh();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Hpm() const
      {
         return get_BEptr()->get_mass_matrix_Hpm();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MHpm()
      {
         get_BEptr()->calculate_MHpm();
      }
      
      inline ::Eigen::Matrix<double, 4, 4, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Chi() const
      {
         return get_BEptr()->get_mass_matrix_Chi();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MChi()
      {
         get_BEptr()->calculate_MChi();
      }
      
      inline ::Eigen::Matrix<double, 2, 2, 0> MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_Cha() const
      {
         return get_BEptr()->get_mass_matrix_Cha();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MCha()
      {
         get_BEptr()->calculate_MCha();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_mass_matrix_VWm() const
      {
         return get_BEptr()->get_mass_matrix_VWm();
      }
      
      inline void MSSMNoFV_onshell_mass_eigenstates::calculate_MVWm()
      {
         get_BEptr()->calculate_MVWm();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ewsb_eq_hh_1() const
      {
         return get_BEptr()->get_ewsb_eq_hh_1();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::get_ewsb_eq_hh_2() const
      {
         return get_BEptr()->get_ewsb_eq_hh_2();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::ThetaW() const
      {
         return get_BEptr()->ThetaW();
      }
      
      inline double MSSMNoFV_onshell_mass_eigenstates::v() const
      {
         return get_BEptr()->v();
      }
      
      
      // Wrappers for original constructors: 
      inline MSSMNoFV_onshell_mass_eigenstates::MSSMNoFV_onshell_mass_eigenstates() :
         MSSMNoFV_onshell_soft_parameters(__factory0())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Special pointer-based constructor: 
      inline MSSMNoFV_onshell_mass_eigenstates::MSSMNoFV_onshell_mass_eigenstates(Abstract_MSSMNoFV_onshell_mass_eigenstates* in) :
         MSSMNoFV_onshell_soft_parameters(in)
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Copy constructor: 
      inline MSSMNoFV_onshell_mass_eigenstates::MSSMNoFV_onshell_mass_eigenstates(const MSSMNoFV_onshell_mass_eigenstates& in) :
         MSSMNoFV_onshell_soft_parameters(in.get_BEptr()->pointer_copy__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Assignment operator: 
      inline MSSMNoFV_onshell_mass_eigenstates& MSSMNoFV_onshell_mass_eigenstates::operator=(const MSSMNoFV_onshell_mass_eigenstates& in)
      {
         if (this != &in)
         {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
         }
         return *this;
      }
      
      
      // Destructor: 
      inline MSSMNoFV_onshell_mass_eigenstates::~MSSMNoFV_onshell_mass_eigenstates()
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
      inline Abstract_MSSMNoFV_onshell_mass_eigenstates* gm2calc::MSSMNoFV_onshell_mass_eigenstates::get_BEptr() const
      {
         return dynamic_cast<Abstract_MSSMNoFV_onshell_mass_eigenstates*>(BEptr);
      }
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_mass_eigenstates_def_gm2calc_1_2_0_hpp__ */
