// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Thu 10 May 2018 14:59:59

/**
 * @file MSSMNoFV_mass_eigenstates.hpp
 *
 * @brief contains class for model with routines needed to solve boundary
 *        value problem using the two_scale solver by solving EWSB
 *        and determine the pole masses and mixings
 *
 * This file was generated at Thu 10 May 2018 14:59:59 with FlexibleSUSY
 * 2.0.1 (git commit: unknown) and SARAH 4.12.2 .
 */

#ifndef MSSMNoFV_MASS_EIGENSTATES_H
#define MSSMNoFV_MASS_EIGENSTATES_H

#include "MSSMNoFV_info.hpp"
#include "MSSMNoFV_physical.hpp"
#include "MSSMNoFV_soft_parameters.hpp"
#include "loop_corrections.hpp"
#include "threshold_corrections.hpp"
#include "error.hpp"
#include "problems.hpp"
#include "config.h"

#include <iosfwd>
#include <memory>
#include <string>

#include <Eigen/Core>

namespace flexiblesusy {

class MSSMNoFV_ewsb_solver_interface;
/**
 * @class MSSMNoFV_mass_eigenstates
 * @brief model class with routines for determing masses and mixinga and EWSB
 */
class MSSMNoFV_mass_eigenstates : public MSSMNoFV_soft_parameters {
public:
   explicit MSSMNoFV_mass_eigenstates(const MSSMNoFV_input_parameters& input_ = MSSMNoFV_input_parameters());
   MSSMNoFV_mass_eigenstates(const MSSMNoFV_mass_eigenstates&) = default;
   MSSMNoFV_mass_eigenstates(MSSMNoFV_mass_eigenstates&&) = default;
   virtual ~MSSMNoFV_mass_eigenstates() = default;
   MSSMNoFV_mass_eigenstates& operator=(const MSSMNoFV_mass_eigenstates&) = default;
   MSSMNoFV_mass_eigenstates& operator=(MSSMNoFV_mass_eigenstates&&) = default;

   /// number of EWSB equations
   static const int number_of_ewsb_equations = 2;

   void calculate_DRbar_masses();
   void calculate_pole_masses();
   void check_pole_masses_for_tachyons();
   virtual void clear() override;
   void clear_DRbar_parameters();
   Eigen::ArrayXd get_DRbar_masses() const;
   Eigen::ArrayXd get_DRbar_masses_and_mixings() const;
   Eigen::ArrayXd get_extra_parameters() const;
   void do_calculate_sm_pole_masses(bool);
   bool do_calculate_sm_pole_masses() const;
   void do_calculate_bsm_pole_masses(bool);
   bool do_calculate_bsm_pole_masses() const;
   void do_force_output(bool);
   bool do_force_output() const;
   void reorder_DRbar_masses();
   void reorder_pole_masses();
   void set_ewsb_iteration_precision(double);
   void set_ewsb_loop_order(int);
   void set_loop_corrections(const Loop_corrections&);
   const Loop_corrections& get_loop_corrections() const;
   void set_threshold_corrections(const Threshold_corrections&);
   const Threshold_corrections& get_threshold_corrections() const;
   void set_DRbar_masses(const Eigen::ArrayXd&);
   void set_DRbar_masses_and_mixings(const Eigen::ArrayXd&);
   void set_extra_parameters(const Eigen::ArrayXd&);
   void set_pole_mass_loop_order(int);
   int get_pole_mass_loop_order() const;
   void set_physical(const MSSMNoFV_physical&);
   double get_ewsb_iteration_precision() const;
   double get_ewsb_loop_order() const;
   const MSSMNoFV_physical& get_physical() const;
   MSSMNoFV_physical& get_physical();
   const Problems& get_problems() const;
   Problems& get_problems();
   void set_ewsb_solver(const std::shared_ptr<MSSMNoFV_ewsb_solver_interface>&);
   int solve_ewsb_tree_level();
   int solve_ewsb_one_loop();
   int solve_ewsb();            ///< solve EWSB at ewsb_loop_order level

   void calculate_spectrum();
   void clear_problems();
   std::string name() const;
   void run_to(double scale, double eps = -1.0) override;
   void print(std::ostream& out = std::cerr) const override;
   void set_precision(double);
   double get_precision() const;


   double get_MVG() const { return MVG; }
   double get_MGlu() const { return MGlu; }
   double get_MFd() const { return MFd; }
   double get_MFs() const { return MFs; }
   double get_MFb() const { return MFb; }
   double get_MFu() const { return MFu; }
   double get_MFc() const { return MFc; }
   double get_MFt() const { return MFt; }
   double get_MFve() const { return MFve; }
   double get_MFvm() const { return MFvm; }
   double get_MFvt() const { return MFvt; }
   double get_MFe() const { return MFe; }
   double get_MFm() const { return MFm; }
   double get_MFtau() const { return MFtau; }
   double get_MSveL() const { return MSveL; }
   double get_MSvmL() const { return MSvmL; }
   double get_MSvtL() const { return MSvtL; }
   const Eigen::Array<double,2,1>& get_MSd() const { return MSd; }
   double get_MSd(int i) const { return MSd(i); }
   const Eigen::Array<double,2,1>& get_MSu() const { return MSu; }
   double get_MSu(int i) const { return MSu(i); }
   const Eigen::Array<double,2,1>& get_MSe() const { return MSe; }
   double get_MSe(int i) const { return MSe(i); }
   const Eigen::Array<double,2,1>& get_MSm() const { return MSm; }
   double get_MSm(int i) const { return MSm(i); }
   const Eigen::Array<double,2,1>& get_MStau() const { return MStau; }
   double get_MStau(int i) const { return MStau(i); }
   const Eigen::Array<double,2,1>& get_MSs() const { return MSs; }
   double get_MSs(int i) const { return MSs(i); }
   const Eigen::Array<double,2,1>& get_MSc() const { return MSc; }
   double get_MSc(int i) const { return MSc(i); }
   const Eigen::Array<double,2,1>& get_MSb() const { return MSb; }
   double get_MSb(int i) const { return MSb(i); }
   const Eigen::Array<double,2,1>& get_MSt() const { return MSt; }
   double get_MSt(int i) const { return MSt(i); }
   const Eigen::Array<double,2,1>& get_Mhh() const { return Mhh; }
   double get_Mhh(int i) const { return Mhh(i); }
   const Eigen::Array<double,2,1>& get_MAh() const { return MAh; }
   double get_MAh(int i) const { return MAh(i); }
   const Eigen::Array<double,2,1>& get_MHpm() const { return MHpm; }
   double get_MHpm(int i) const { return MHpm(i); }
   const Eigen::Array<double,4,1>& get_MChi() const { return MChi; }
   double get_MChi(int i) const { return MChi(i); }
   const Eigen::Array<double,2,1>& get_MCha() const { return MCha; }
   double get_MCha(int i) const { return MCha(i); }
   double get_MVWm() const { return MVWm; }
   double get_MVP() const { return MVP; }
   double get_MVZ() const { return MVZ; }

   
   Eigen::Array<double,1,1> get_MChargedHiggs() const;

   Eigen::Array<double,1,1> get_MPseudoscalarHiggs() const;

   const Eigen::Matrix<double,2,2>& get_ZD() const { return ZD; }
   double get_ZD(int i, int k) const { return ZD(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZU() const { return ZU; }
   double get_ZU(int i, int k) const { return ZU(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZE() const { return ZE; }
   double get_ZE(int i, int k) const { return ZE(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZM() const { return ZM; }
   double get_ZM(int i, int k) const { return ZM(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZTau() const { return ZTau; }
   double get_ZTau(int i, int k) const { return ZTau(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZS() const { return ZS; }
   double get_ZS(int i, int k) const { return ZS(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZC() const { return ZC; }
   double get_ZC(int i, int k) const { return ZC(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZB() const { return ZB; }
   double get_ZB(int i, int k) const { return ZB(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZT() const { return ZT; }
   double get_ZT(int i, int k) const { return ZT(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZH() const { return ZH; }
   double get_ZH(int i, int k) const { return ZH(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZA() const { return ZA; }
   double get_ZA(int i, int k) const { return ZA(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZP() const { return ZP; }
   double get_ZP(int i, int k) const { return ZP(i,k); }
   const Eigen::Matrix<std::complex<double>,4,4>& get_ZN() const { return ZN; }
   std::complex<double> get_ZN(int i, int k) const { return ZN(i,k); }
   const Eigen::Matrix<std::complex<double>,2,2>& get_UM() const { return UM; }
   std::complex<double> get_UM(int i, int k) const { return UM(i,k); }
   const Eigen::Matrix<std::complex<double>,2,2>& get_UP() const { return UP; }
   std::complex<double> get_UP(int i, int k) const { return UP(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZZ() const { return ZZ; }
   double get_ZZ(int i, int k) const { return ZZ(i,k); }

   void set_PhaseGlu(std::complex<double> PhaseGlu_) { PhaseGlu = PhaseGlu_; }
   std::complex<double> get_PhaseGlu() const { return PhaseGlu; }



   double get_mass_matrix_VG() const;
   void calculate_MVG();
   double get_mass_matrix_Glu() const;
   void calculate_MGlu();
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
   Eigen::Matrix<double,2,2> get_mass_matrix_Sd() const;
   void calculate_MSd();
   Eigen::Matrix<double,2,2> get_mass_matrix_Su() const;
   void calculate_MSu();
   Eigen::Matrix<double,2,2> get_mass_matrix_Se() const;
   void calculate_MSe();
   Eigen::Matrix<double,2,2> get_mass_matrix_Sm() const;
   void calculate_MSm();
   Eigen::Matrix<double,2,2> get_mass_matrix_Stau() const;
   void calculate_MStau();
   Eigen::Matrix<double,2,2> get_mass_matrix_Ss() const;
   void calculate_MSs();
   Eigen::Matrix<double,2,2> get_mass_matrix_Sc() const;
   void calculate_MSc();
   Eigen::Matrix<double,2,2> get_mass_matrix_Sb() const;
   void calculate_MSb();
   Eigen::Matrix<double,2,2> get_mass_matrix_St() const;
   void calculate_MSt();
   Eigen::Matrix<double,2,2> get_mass_matrix_hh() const;
   void calculate_Mhh();
   Eigen::Matrix<double,2,2> get_mass_matrix_Ah() const;
   void calculate_MAh();
   Eigen::Matrix<double,2,2> get_mass_matrix_Hpm() const;
   void calculate_MHpm();
   Eigen::Matrix<double,4,4> get_mass_matrix_Chi() const;
   void calculate_MChi();
   Eigen::Matrix<double,2,2> get_mass_matrix_Cha() const;
   void calculate_MCha();
   double get_mass_matrix_VWm() const;
   void calculate_MVWm();
   Eigen::Matrix<double,2,2> get_mass_matrix_VPVZ() const;
   void calculate_MVPVZ();

   double get_ewsb_eq_hh_1() const;
   double get_ewsb_eq_hh_2() const;

   std::complex<double> CpSveLUSdconjSveLconjUSd(int gO1, int gO2) const;
   std::complex<double> CpSvmLUSdconjSvmLconjUSd(int gO1, int gO2) const;
   std::complex<double> CpSvtLUSdconjSvtLconjUSd(int gO1, int gO2) const;
   std::complex<double> CpUSdconjUSdVZVZ(int gO1, int gO2) const;
   double CpUSdconjUSdconjVWmVWm(int gO1, int gO2) const;
   std::complex<double> CpAhAhUSdconjUSd(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUSdconjUSd(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpHpmUSdconjHpmconjUSd(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpUSdconjUSdconjSbSb(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSdconjUSdconjScSc(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSdconjUSdconjSdSd(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSdconjUSdconjSsSs(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSdconjUSdconjStSt(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSdconjUSdconjSuSu(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSdSeconjUSdconjSe(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSdSmconjUSdconjSm(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSdStauconjUSdconjStau(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpAhSdconjUSd(int gI2, int gI1, int gO2) const;
   std::complex<double> CphhSdconjUSd(int gI2, int gI1, int gO2) const;
   std::complex<double> CpHpmSuconjUSd(int gI2, int gI1, int gO2) const;
   std::complex<double> CpSdconjUSdVG(int gI2, int gO2) const;
   std::complex<double> CpSdconjUSdVP(int gI2, int gO2) const;
   std::complex<double> CpSdconjUSdVZ(int gI2, int gO2) const;
   std::complex<double> CpSuconjUSdVWm(int gI2, int gO2) const;
   std::complex<double> CpFuChaconjUSdPR(int gI2, int gO2) const;
   std::complex<double> CpFuChaconjUSdPL(int gI2, int gO1) const;
   std::complex<double> CpChiFdconjUSdPR(int gI2, int gO2) const;
   std::complex<double> CpChiFdconjUSdPL(int gI2, int gO1) const;
   std::complex<double> CpGluFdconjUSdPR(int gO2) const;
   std::complex<double> CpGluFdconjUSdPL(int gO1) const;
   std::complex<double> CpSveLUSuconjSveLconjUSu(int gO1, int gO2) const;
   std::complex<double> CpSvmLUSuconjSvmLconjUSu(int gO1, int gO2) const;
   std::complex<double> CpSvtLUSuconjSvtLconjUSu(int gO1, int gO2) const;
   std::complex<double> CpUSuconjUSuVZVZ(int gO1, int gO2) const;
   double CpUSuconjUSuconjVWmVWm(int gO1, int gO2) const;
   std::complex<double> CpAhAhUSuconjUSu(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUSuconjUSu(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpHpmUSuconjHpmconjUSu(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSeUSuconjSeconjUSu(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSmUSuconjSmconjUSu(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpStauUSuconjStauconjUSu(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpUSuconjUSuconjSbSb(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSuconjUSuconjScSc(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSuconjUSuconjSdSd(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSuconjUSuconjSsSs(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSuconjUSuconjStSt(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSuconjUSuconjSuSu(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpAhSuconjUSu(int gI2, int gI1, int gO2) const;
   std::complex<double> CphhSuconjUSu(int gI2, int gI1, int gO2) const;
   std::complex<double> CpSdconjHpmconjUSu(int gI2, int gI1, int gO2) const;
   std::complex<double> CpbarChaFdconjUSuPR(int gI1, int gO2) const;
   std::complex<double> CpbarChaFdconjUSuPL(int gI1, int gO1) const;
   std::complex<double> CpSdconjUSuconjVWm(int gI2, int gO2) const;
   std::complex<double> CpSuconjUSuVG(int gI2, int gO2) const;
   std::complex<double> CpSuconjUSuVP(int gI2, int gO2) const;
   std::complex<double> CpSuconjUSuVZ(int gI2, int gO2) const;
   std::complex<double> CpChiFuconjUSuPR(int gI2, int gO2) const;
   std::complex<double> CpChiFuconjUSuPL(int gI2, int gO1) const;
   std::complex<double> CpGluFuconjUSuPR(int gO2) const;
   std::complex<double> CpGluFuconjUSuPL(int gO1) const;
   std::complex<double> CpSveLUSeconjSveLconjUSe(int gO1, int gO2) const;
   std::complex<double> CpSvmLUSeconjSvmLconjUSe(int gO1, int gO2) const;
   std::complex<double> CpSvtLUSeconjSvtLconjUSe(int gO1, int gO2) const;
   std::complex<double> CpUSeconjUSeVZVZ(int gO1, int gO2) const;
   double CpUSeconjUSeconjVWmVWm(int gO1, int gO2) const;
   double CpSveLconjUSeVWm(int gO2) const;
   std::complex<double> CpAhAhUSeconjUSe(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUSeconjUSe(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpHpmUSeconjHpmconjUSe(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSbUSeconjSbconjUSe(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpScUSeconjScconjUSe(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSdUSeconjSdconjUSe(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSeUSeconjSeconjUSe(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpUSeSmconjUSeconjSm(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSeSsconjUSeconjSs(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSeStconjUSeconjSt(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSeStauconjUSeconjStau(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSeSuconjUSeconjSu(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpAhSeconjUSe(int gI2, int gI1, int gO2) const;
   std::complex<double> CphhSeconjUSe(int gI2, int gI1, int gO2) const;
   std::complex<double> CpSveLHpmconjUSe(int gI2, int gO2) const;
   std::complex<double> CpSeconjUSeVP(int gI2, int gO2) const;
   std::complex<double> CpSeconjUSeVZ(int gI2, int gO2) const;
   double CpFveChaconjUSePR(int , int ) const;
   std::complex<double> CpFveChaconjUSePL(int gI2, int gO1) const;
   std::complex<double> CpChiFeconjUSePR(int gI2, int gO2) const;
   std::complex<double> CpChiFeconjUSePL(int gI2, int gO1) const;
   std::complex<double> CpSveLUSmconjSveLconjUSm(int gO1, int gO2) const;
   std::complex<double> CpSvmLUSmconjSvmLconjUSm(int gO1, int gO2) const;
   std::complex<double> CpSvtLUSmconjSvtLconjUSm(int gO1, int gO2) const;
   std::complex<double> CpUSmconjUSmVZVZ(int gO1, int gO2) const;
   double CpUSmconjUSmconjVWmVWm(int gO1, int gO2) const;
   double CpSvmLconjUSmVWm(int gO2) const;
   std::complex<double> CpAhAhUSmconjUSm(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUSmconjUSm(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpHpmUSmconjHpmconjUSm(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSbUSmconjSbconjUSm(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpScUSmconjScconjUSm(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSdUSmconjSdconjUSm(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSeUSmconjSeconjUSm(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSmUSmconjSmconjUSm(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpUSmSsconjUSmconjSs(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSmStconjUSmconjSt(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSmStauconjUSmconjStau(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSmSuconjUSmconjSu(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpAhSmconjUSm(int gI2, int gI1, int gO2) const;
   std::complex<double> CphhSmconjUSm(int gI2, int gI1, int gO2) const;
   std::complex<double> CpSvmLHpmconjUSm(int gI2, int gO2) const;
   std::complex<double> CpSmconjUSmVP(int gI2, int gO2) const;
   std::complex<double> CpSmconjUSmVZ(int gI2, int gO2) const;
   double CpFvmChaconjUSmPR(int , int ) const;
   std::complex<double> CpFvmChaconjUSmPL(int gI2, int gO1) const;
   std::complex<double> CpChiFmconjUSmPR(int gI2, int gO2) const;
   std::complex<double> CpChiFmconjUSmPL(int gI2, int gO1) const;
   std::complex<double> CpSveLUStauconjSveLconjUStau(int gO1, int gO2) const;
   std::complex<double> CpSvmLUStauconjSvmLconjUStau(int gO1, int gO2) const;
   std::complex<double> CpSvtLUStauconjSvtLconjUStau(int gO1, int gO2) const;
   std::complex<double> CpUStauconjUStauVZVZ(int gO1, int gO2) const;
   double CpUStauconjUStauconjVWmVWm(int gO1, int gO2) const;
   double CpSvtLconjUStauVWm(int gO2) const;
   std::complex<double> CpAhAhUStauconjUStau(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUStauconjUStau(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpHpmUStauconjHpmconjUStau(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSbUStauconjSbconjUStau(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpScUStauconjScconjUStau(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSdUStauconjSdconjUStau(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSeUStauconjSeconjUStau(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSmUStauconjSmconjUStau(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSsUStauconjSsconjUStau(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpStUStauconjStconjUStau(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpStauUStauconjStauconjUStau(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpUStauSuconjUStauconjSu(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpAhStauconjUStau(int gI2, int gI1, int gO2) const;
   std::complex<double> CphhStauconjUStau(int gI2, int gI1, int gO2) const;
   std::complex<double> CpSvtLHpmconjUStau(int gI2, int gO2) const;
   std::complex<double> CpStauconjUStauVP(int gI2, int gO2) const;
   std::complex<double> CpStauconjUStauVZ(int gI2, int gO2) const;
   double CpFvtChaconjUStauPR(int , int ) const;
   std::complex<double> CpFvtChaconjUStauPL(int gI2, int gO1) const;
   std::complex<double> CpChiFtauconjUStauPR(int gI2, int gO2) const;
   std::complex<double> CpChiFtauconjUStauPL(int gI2, int gO1) const;
   std::complex<double> CpSveLUSsconjSveLconjUSs(int gO1, int gO2) const;
   std::complex<double> CpSvmLUSsconjSvmLconjUSs(int gO1, int gO2) const;
   std::complex<double> CpSvtLUSsconjSvtLconjUSs(int gO1, int gO2) const;
   std::complex<double> CpUSsconjUSsVZVZ(int gO1, int gO2) const;
   double CpUSsconjUSsconjVWmVWm(int gO1, int gO2) const;
   std::complex<double> CpAhAhUSsconjUSs(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUSsconjUSs(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpHpmUSsconjHpmconjUSs(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSeUSsconjSeconjUSs(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSmUSsconjSmconjUSs(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpUSsconjUSsconjSbSb(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSsconjUSsconjScSc(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSsconjUSsconjSdSd(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSsconjUSsconjSsSs(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSsconjUSsconjStSt(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSsconjUSsconjSuSu(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSsStauconjUSsconjStau(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpAhSsconjUSs(int gI2, int gI1, int gO2) const;
   std::complex<double> CphhSsconjUSs(int gI2, int gI1, int gO2) const;
   std::complex<double> CpHpmScconjUSs(int gI2, int gI1, int gO2) const;
   std::complex<double> CpScconjUSsVWm(int gI2, int gO2) const;
   std::complex<double> CpSsconjUSsVG(int gI2, int gO2) const;
   std::complex<double> CpSsconjUSsVP(int gI2, int gO2) const;
   std::complex<double> CpSsconjUSsVZ(int gI2, int gO2) const;
   std::complex<double> CpFcChaconjUSsPR(int gI2, int gO2) const;
   std::complex<double> CpFcChaconjUSsPL(int gI2, int gO1) const;
   std::complex<double> CpChiFsconjUSsPR(int gI2, int gO2) const;
   std::complex<double> CpChiFsconjUSsPL(int gI2, int gO1) const;
   std::complex<double> CpGluFsconjUSsPR(int gO2) const;
   std::complex<double> CpGluFsconjUSsPL(int gO1) const;
   std::complex<double> CpSveLUScconjSveLconjUSc(int gO1, int gO2) const;
   std::complex<double> CpSvmLUScconjSvmLconjUSc(int gO1, int gO2) const;
   std::complex<double> CpSvtLUScconjSvtLconjUSc(int gO1, int gO2) const;
   std::complex<double> CpUScconjUScVZVZ(int gO1, int gO2) const;
   double CpUScconjUScconjVWmVWm(int gO1, int gO2) const;
   std::complex<double> CpAhAhUScconjUSc(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUScconjUSc(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpHpmUScconjHpmconjUSc(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpUScconjUScconjSbSb(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUScconjUScconjScSc(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUScconjUScconjSdSd(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUScconjUScconjSsSs(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUScconjUScconjStSt(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUScconjUScconjSuSu(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUScSeconjUScconjSe(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUScSmconjUScconjSm(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUScStauconjUScconjStau(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpAhScconjUSc(int gI2, int gI1, int gO2) const;
   std::complex<double> CphhScconjUSc(int gI2, int gI1, int gO2) const;
   std::complex<double> CpSsconjHpmconjUSc(int gI2, int gI1, int gO2) const;
   std::complex<double> CpbarChaFsconjUScPR(int gI1, int gO2) const;
   std::complex<double> CpbarChaFsconjUScPL(int gI1, int gO1) const;
   std::complex<double> CpScconjUScVG(int gI2, int gO2) const;
   std::complex<double> CpScconjUScVP(int gI2, int gO2) const;
   std::complex<double> CpScconjUScVZ(int gI2, int gO2) const;
   std::complex<double> CpSsconjUScconjVWm(int gI2, int gO2) const;
   std::complex<double> CpChiFcconjUScPR(int gI2, int gO2) const;
   std::complex<double> CpChiFcconjUScPL(int gI2, int gO1) const;
   std::complex<double> CpGluFcconjUScPR(int gO2) const;
   std::complex<double> CpGluFcconjUScPL(int gO1) const;
   std::complex<double> CpSveLUSbconjSveLconjUSb(int gO1, int gO2) const;
   std::complex<double> CpSvmLUSbconjSvmLconjUSb(int gO1, int gO2) const;
   std::complex<double> CpSvtLUSbconjSvtLconjUSb(int gO1, int gO2) const;
   std::complex<double> CpUSbconjUSbVZVZ(int gO1, int gO2) const;
   double CpUSbconjUSbconjVWmVWm(int gO1, int gO2) const;
   std::complex<double> CpAhAhUSbconjUSb(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUSbconjUSb(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpHpmUSbconjHpmconjUSb(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpUSbconjUSbconjSbSb(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSbconjUSbconjScSc(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSbconjUSbconjSdSd(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSbconjUSbconjSsSs(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSbconjUSbconjStSt(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSbconjUSbconjSuSu(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUSbSeconjUSbconjSe(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSbSmconjUSbconjSm(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUSbStauconjUSbconjStau(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpAhSbconjUSb(int gI2, int gI1, int gO2) const;
   std::complex<double> CphhSbconjUSb(int gI2, int gI1, int gO2) const;
   std::complex<double> CpHpmStconjUSb(int gI2, int gI1, int gO2) const;
   std::complex<double> CpSbconjUSbVG(int gI2, int gO2) const;
   std::complex<double> CpSbconjUSbVP(int gI2, int gO2) const;
   std::complex<double> CpSbconjUSbVZ(int gI2, int gO2) const;
   std::complex<double> CpStconjUSbVWm(int gI2, int gO2) const;
   std::complex<double> CpFtChaconjUSbPR(int gI2, int gO2) const;
   std::complex<double> CpFtChaconjUSbPL(int gI2, int gO1) const;
   std::complex<double> CpChiFbconjUSbPR(int gI2, int gO2) const;
   std::complex<double> CpChiFbconjUSbPL(int gI2, int gO1) const;
   std::complex<double> CpGluFbconjUSbPR(int gO2) const;
   std::complex<double> CpGluFbconjUSbPL(int gO1) const;
   std::complex<double> CpSveLUStconjSveLconjUSt(int gO1, int gO2) const;
   std::complex<double> CpSvmLUStconjSvmLconjUSt(int gO1, int gO2) const;
   std::complex<double> CpSvtLUStconjSvtLconjUSt(int gO1, int gO2) const;
   std::complex<double> CpUStconjUStVZVZ(int gO1, int gO2) const;
   double CpUStconjUStconjVWmVWm(int gO1, int gO2) const;
   std::complex<double> CpAhAhUStconjUSt(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUStconjUSt(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpHpmUStconjHpmconjUSt(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSeUStconjSeconjUSt(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpSmUStconjSmconjUSt(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpUStconjUStconjSbSb(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUStconjUStconjScSc(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUStconjUStconjSdSd(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUStconjUStconjSsSs(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUStconjUStconjStSt(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUStconjUStconjSuSu(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUStStauconjUStconjStau(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpAhStconjUSt(int gI2, int gI1, int gO2) const;
   std::complex<double> CphhStconjUSt(int gI2, int gI1, int gO2) const;
   std::complex<double> CpSbconjHpmconjUSt(int gI2, int gI1, int gO2) const;
   std::complex<double> CpbarChaFbconjUStPR(int gI1, int gO2) const;
   std::complex<double> CpbarChaFbconjUStPL(int gI1, int gO1) const;
   std::complex<double> CpSbconjUStconjVWm(int gI2, int gO2) const;
   std::complex<double> CpStconjUStVG(int gI2, int gO2) const;
   std::complex<double> CpStconjUStVP(int gI2, int gO2) const;
   std::complex<double> CpStconjUStVZ(int gI2, int gO2) const;
   std::complex<double> CpChiFtconjUStPR(int gI2, int gO2) const;
   std::complex<double> CpChiFtconjUStPL(int gI2, int gO1) const;
   std::complex<double> CpGluFtconjUStPR(int gO2) const;
   std::complex<double> CpGluFtconjUStPL(int gO1) const;
   std::complex<double> CpSveLUhhconjSveL(int gO2) const;
   std::complex<double> CpSvmLUhhconjSvmL(int gO2) const;
   std::complex<double> CpSvtLUhhconjSvtL(int gO2) const;
   std::complex<double> CpbargWmgWmUhh(int gO1) const;
   std::complex<double> CpbargWmCgWmCUhh(int gO1) const;
   std::complex<double> CpbargZgZUhh(int gO1) const;
   std::complex<double> CpUhhVZVZ(int gO2) const;
   std::complex<double> CpUhhconjVWmVWm(int gO2) const;
   std::complex<double> CpSveLUhhUhhconjSveL(int gO1, int gO2) const;
   std::complex<double> CpSvmLUhhUhhconjSvmL(int gO1, int gO2) const;
   std::complex<double> CpSvtLUhhUhhconjSvtL(int gO1, int gO2) const;
   std::complex<double> CpUhhUhhVZVZ(int gO1, int gO2) const;
   std::complex<double> CpUhhUhhconjVWmVWm(int gO1, int gO2) const;
   std::complex<double> CpAhAhUhhUhh(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUhhUhh(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpUhhUhhHpmconjHpm(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUhhUhhSbconjSb(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUhhUhhScconjSc(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUhhUhhSdconjSd(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUhhUhhSeconjSe(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUhhUhhSmconjSm(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUhhUhhSsconjSs(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUhhUhhStconjSt(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUhhUhhStauconjStau(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUhhUhhSuconjSu(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpAhAhUhh(int gI1, int gI2, int gO2) const;
   std::complex<double> CphhhhUhh(int gI1, int gI2, int gO2) const;
   std::complex<double> CpUhhHpmconjHpm(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUhhSbconjSb(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUhhScconjSc(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUhhSdconjSd(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUhhSeconjSe(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUhhSmconjSm(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUhhSsconjSs(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUhhStconjSt(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUhhStauconjStau(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUhhSuconjSu(int gO2, int gI2, int gI1) const;
   std::complex<double> CpbarChaChaUhhPR(int gI1, int gI2, int gO2) const;
   std::complex<double> CpbarChaChaUhhPL(int gI1, int gI2, int gO1) const;
   std::complex<double> CpChiChiUhhPR(int gI1, int gI2, int gO2) const;
   std::complex<double> CpChiChiUhhPL(int gI1, int gI2, int gO1) const;
   std::complex<double> CpAhUhhVZ(int gI2, int gO2) const;
   std::complex<double> CpUhhHpmconjVWm(int gO2, int gI2) const;
   double CpbarFbFbUhhPR(int gO2) const;
   double CpbarFbFbUhhPL(int gO1) const;
   double CpbarFcFcUhhPR(int gO2) const;
   double CpbarFcFcUhhPL(int gO1) const;
   double CpbarFdFdUhhPR(int gO2) const;
   double CpbarFdFdUhhPL(int gO1) const;
   double CpbarFeFeUhhPR(int gO2) const;
   double CpbarFeFeUhhPL(int gO1) const;
   double CpbarFmFmUhhPR(int gO2) const;
   double CpbarFmFmUhhPL(int gO1) const;
   double CpbarFsFsUhhPR(int gO2) const;
   double CpbarFsFsUhhPL(int gO1) const;
   double CpbarFtFtUhhPR(int gO2) const;
   double CpbarFtFtUhhPL(int gO1) const;
   double CpbarFtauFtauUhhPR(int gO2) const;
   double CpbarFtauFtauUhhPL(int gO1) const;
   double CpbarFuFuUhhPR(int gO2) const;
   double CpbarFuFuUhhPL(int gO1) const;
   std::complex<double> CpbargWmgWmUAh(int gO1) const;
   std::complex<double> CpbargWmCgWmCUAh(int gO1) const;
   std::complex<double> CpSveLUAhUAhconjSveL(int gO1, int gO2) const;
   std::complex<double> CpSvmLUAhUAhconjSvmL(int gO1, int gO2) const;
   std::complex<double> CpSvtLUAhUAhconjSvtL(int gO1, int gO2) const;
   std::complex<double> CpUAhUAhVZVZ(int gO1, int gO2) const;
   std::complex<double> CpUAhUAhconjVWmVWm(int gO1, int gO2) const;
   std::complex<double> CpAhAhUAhUAh(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpUAhUAhhhhh(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUAhUAhHpmconjHpm(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUAhUAhSbconjSb(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUAhUAhScconjSc(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUAhUAhSdconjSd(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUAhUAhSeconjSe(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUAhUAhSmconjSm(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUAhUAhSsconjSs(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUAhUAhStconjSt(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUAhUAhStauconjStau(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpUAhUAhSuconjSu(int gO1, int gO2, int gI1, int gI2) const;
   std::complex<double> CpAhUAhhh(int gI2, int gO2, int gI1) const;
   std::complex<double> CpUAhHpmconjHpm(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUAhSbconjSb(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUAhScconjSc(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUAhSdconjSd(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUAhSeconjSe(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUAhSmconjSm(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUAhSsconjSs(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUAhStconjSt(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUAhStauconjStau(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUAhSuconjSu(int gO2, int gI2, int gI1) const;
   std::complex<double> CpbarChaChaUAhPR(int gI1, int gI2, int gO2) const;
   std::complex<double> CpbarChaChaUAhPL(int gI1, int gI2, int gO1) const;
   std::complex<double> CpChiChiUAhPR(int gI1, int gI2, int gO2) const;
   std::complex<double> CpChiChiUAhPL(int gI1, int gI2, int gO1) const;
   std::complex<double> CpUAhhhVZ(int gO2, int gI2) const;
   std::complex<double> CpUAhHpmconjVWm(int gO2, int gI2) const;
   std::complex<double> CpbarFbFbUAhPR(int gO2) const;
   std::complex<double> CpbarFbFbUAhPL(int gO1) const;
   std::complex<double> CpbarFcFcUAhPR(int gO2) const;
   std::complex<double> CpbarFcFcUAhPL(int gO1) const;
   std::complex<double> CpbarFdFdUAhPR(int gO2) const;
   std::complex<double> CpbarFdFdUAhPL(int gO1) const;
   std::complex<double> CpbarFeFeUAhPR(int gO2) const;
   std::complex<double> CpbarFeFeUAhPL(int gO1) const;
   std::complex<double> CpbarFmFmUAhPR(int gO2) const;
   std::complex<double> CpbarFmFmUAhPL(int gO1) const;
   std::complex<double> CpbarFsFsUAhPR(int gO2) const;
   std::complex<double> CpbarFsFsUAhPL(int gO1) const;
   std::complex<double> CpbarFtFtUAhPR(int gO2) const;
   std::complex<double> CpbarFtFtUAhPL(int gO1) const;
   std::complex<double> CpbarFtauFtauUAhPR(int gO2) const;
   std::complex<double> CpbarFtauFtauUAhPL(int gO1) const;
   std::complex<double> CpbarFuFuUAhPR(int gO2) const;
   std::complex<double> CpbarFuFuUAhPL(int gO1) const;
   std::complex<double> CpbargWmgZUHpm(int gO2) const;
   std::complex<double> CpbargZgWmconjUHpm(int gO1) const;
   std::complex<double> CpbargWmCgZconjUHpm(int gO1) const;
   std::complex<double> CpbargZgWmCUHpm(int gO2) const;
   std::complex<double> CpconjUHpmVPVWm(int gO2) const;
   std::complex<double> CpconjUHpmVWmVZ(int gO2) const;
   std::complex<double> CpSveLUHpmconjSveLconjUHpm(int gO1, int gO2) const;
   std::complex<double> CpSvmLUHpmconjSvmLconjUHpm(int gO1, int gO2) const;
   std::complex<double> CpSvtLUHpmconjSvtLconjUHpm(int gO1, int gO2) const;
   std::complex<double> CpUHpmconjUHpmVZVZ(int gO1, int gO2) const;
   std::complex<double> CpUHpmconjUHpmconjVWmVWm(int gO1, int gO2) const;
   std::complex<double> CpAhAhUHpmconjUHpm(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CphhhhUHpmconjUHpm(int gI1, int gI2, int gO1, int gO2) const;
   std::complex<double> CpHpmUHpmconjHpmconjUHpm(int gI1, int gO1, int gI2, int gO2) const;
   std::complex<double> CpUHpmSbconjUHpmconjSb(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUHpmScconjUHpmconjSc(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUHpmSdconjUHpmconjSd(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUHpmSeconjUHpmconjSe(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUHpmSmconjUHpmconjSm(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUHpmSsconjUHpmconjSs(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUHpmStconjUHpmconjSt(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUHpmStauconjUHpmconjStau(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpUHpmSuconjUHpmconjSu(int gO1, int gI1, int gO2, int gI2) const;
   std::complex<double> CpAhHpmconjUHpm(int gI2, int gI1, int gO2) const;
   std::complex<double> CphhHpmconjUHpm(int gI2, int gI1, int gO2) const;
   std::complex<double> CpSbconjUHpmconjSt(int gI2, int gO2, int gI1) const;
   std::complex<double> CpSdconjUHpmconjSu(int gI2, int gO2, int gI1) const;
   std::complex<double> CpSsconjUHpmconjSc(int gI2, int gO2, int gI1) const;
   std::complex<double> CpChiChaconjUHpmPR(int gI1, int gI2, int gO2) const;
   std::complex<double> CpChiChaconjUHpmPL(int gI1, int gI2, int gO1) const;
   std::complex<double> CpSeconjSveLconjUHpm(int gI2, int gO2) const;
   std::complex<double> CpSmconjSvmLconjUHpm(int gI2, int gO2) const;
   std::complex<double> CpStauconjSvtLconjUHpm(int gI2, int gO2) const;
   std::complex<double> CpAhconjUHpmVWm(int gI2, int gO2) const;
   std::complex<double> CphhconjUHpmVWm(int gI2, int gO2) const;
   std::complex<double> CpHpmconjUHpmVP(int gI2, int gO2) const;
   std::complex<double> CpHpmconjUHpmVZ(int gI2, int gO2) const;
   double CpbarFcFsconjUHpmPR(int gO2) const;
   double CpbarFcFsconjUHpmPL(int gO1) const;
   double CpbarFtFbconjUHpmPR(int gO2) const;
   double CpbarFtFbconjUHpmPL(int gO1) const;
   double CpbarFuFdconjUHpmPR(int gO2) const;
   double CpbarFuFdconjUHpmPL(int gO1) const;
   double CpbarFveFeconjUHpmPR(int gO2) const;
   double CpbarFveFeconjUHpmPL(int ) const;
   double CpbarFvmFmconjUHpmPR(int gO2) const;
   double CpbarFvmFmconjUHpmPL(int ) const;
   double CpbarFvtFtauconjUHpmPR(int gO2) const;
   double CpbarFvtFtauconjUHpmPL(int ) const;
   double CpSveLSveLconjSveLconjSveL() const;
   double CpSveLSvmLconjSveLconjSvmL() const;
   double CpSveLSvtLconjSveLconjSvtL() const;
   std::complex<double> CpSveLconjSveLVZVZ() const;
   double CpSveLconjSveLconjVWmVWm() const;
   double CpSveLconjSveLVZ() const;
   std::complex<double> CpSveLAhAhconjSveL(int gI1, int gI2) const;
   std::complex<double> CpSveLhhhhconjSveL(int gI1, int gI2) const;
   std::complex<double> CpSveLHpmconjSveLconjHpm(int gI1, int gI2) const;
   std::complex<double> CpSveLSbconjSveLconjSb(int gI1, int gI2) const;
   std::complex<double> CpSveLScconjSveLconjSc(int gI1, int gI2) const;
   std::complex<double> CpSveLSdconjSveLconjSd(int gI1, int gI2) const;
   std::complex<double> CpSveLSeconjSveLconjSe(int gI1, int gI2) const;
   std::complex<double> CpSveLSmconjSveLconjSm(int gI1, int gI2) const;
   std::complex<double> CpSveLSsconjSveLconjSs(int gI1, int gI2) const;
   std::complex<double> CpSveLStconjSveLconjSt(int gI1, int gI2) const;
   std::complex<double> CpSveLStauconjSveLconjStau(int gI1, int gI2) const;
   std::complex<double> CpSveLSuconjSveLconjSu(int gI1, int gI2) const;
   std::complex<double> CpSeconjSveLconjHpm(int gI2, int gI1) const;
   std::complex<double> CpbarChaFeconjSveLPR(int gI1) const;
   std::complex<double> CpbarChaFeconjSveLPL(int gI1) const;
   std::complex<double> CpSveLhhconjSveL(int gI2) const;
   std::complex<double> CpSeconjSveLconjVWm(int gI2) const;
   double CpChiFveconjSveLPR(int ) const;
   std::complex<double> CpChiFveconjSveLPL(int gI2) const;
   double CpSvmLSvmLconjSvmLconjSvmL() const;
   double CpSvmLSvtLconjSvmLconjSvtL() const;
   std::complex<double> CpSvmLconjSvmLVZVZ() const;
   double CpSvmLconjSvmLconjVWmVWm() const;
   double CpSvmLconjSvmLVZ() const;
   std::complex<double> CpSvmLAhAhconjSvmL(int gI1, int gI2) const;
   std::complex<double> CpSvmLhhhhconjSvmL(int gI1, int gI2) const;
   std::complex<double> CpSvmLHpmconjSvmLconjHpm(int gI1, int gI2) const;
   std::complex<double> CpSvmLSbconjSvmLconjSb(int gI1, int gI2) const;
   std::complex<double> CpSvmLScconjSvmLconjSc(int gI1, int gI2) const;
   std::complex<double> CpSvmLSdconjSvmLconjSd(int gI1, int gI2) const;
   std::complex<double> CpSvmLSeconjSvmLconjSe(int gI1, int gI2) const;
   std::complex<double> CpSvmLSmconjSvmLconjSm(int gI1, int gI2) const;
   std::complex<double> CpSvmLSsconjSvmLconjSs(int gI1, int gI2) const;
   std::complex<double> CpSvmLStconjSvmLconjSt(int gI1, int gI2) const;
   std::complex<double> CpSvmLStauconjSvmLconjStau(int gI1, int gI2) const;
   std::complex<double> CpSvmLSuconjSvmLconjSu(int gI1, int gI2) const;
   std::complex<double> CpSmconjSvmLconjHpm(int gI2, int gI1) const;
   std::complex<double> CpbarChaFmconjSvmLPR(int gI1) const;
   std::complex<double> CpbarChaFmconjSvmLPL(int gI1) const;
   std::complex<double> CpSvmLhhconjSvmL(int gI2) const;
   std::complex<double> CpSmconjSvmLconjVWm(int gI2) const;
   double CpChiFvmconjSvmLPR(int ) const;
   std::complex<double> CpChiFvmconjSvmLPL(int gI2) const;
   double CpSvtLSvtLconjSvtLconjSvtL() const;
   std::complex<double> CpSvtLconjSvtLVZVZ() const;
   double CpSvtLconjSvtLconjVWmVWm() const;
   double CpSvtLconjSvtLVZ() const;
   std::complex<double> CpSvtLAhAhconjSvtL(int gI1, int gI2) const;
   std::complex<double> CpSvtLhhhhconjSvtL(int gI1, int gI2) const;
   std::complex<double> CpSvtLHpmconjSvtLconjHpm(int gI1, int gI2) const;
   std::complex<double> CpSvtLSbconjSvtLconjSb(int gI1, int gI2) const;
   std::complex<double> CpSvtLScconjSvtLconjSc(int gI1, int gI2) const;
   std::complex<double> CpSvtLSdconjSvtLconjSd(int gI1, int gI2) const;
   std::complex<double> CpSvtLSeconjSvtLconjSe(int gI1, int gI2) const;
   std::complex<double> CpSvtLSmconjSvtLconjSm(int gI1, int gI2) const;
   std::complex<double> CpSvtLSsconjSvtLconjSs(int gI1, int gI2) const;
   std::complex<double> CpSvtLStconjSvtLconjSt(int gI1, int gI2) const;
   std::complex<double> CpSvtLStauconjSvtLconjStau(int gI1, int gI2) const;
   std::complex<double> CpSvtLSuconjSvtLconjSu(int gI1, int gI2) const;
   std::complex<double> CpStauconjSvtLconjHpm(int gI2, int gI1) const;
   std::complex<double> CpbarChaFtauconjSvtLPR(int gI1) const;
   std::complex<double> CpbarChaFtauconjSvtLPL(int gI1) const;
   std::complex<double> CpSvtLhhconjSvtL(int gI2) const;
   std::complex<double> CpStauconjSvtLconjVWm(int gI2) const;
   double CpChiFvtconjSvtLPR(int ) const;
   std::complex<double> CpChiFvtconjSvtLPL(int gI2) const;
   std::complex<double> CpVGVGVG() const;
   std::complex<double> CpbargGgGVG() const;
   std::complex<double> CpSbconjSbVGVG(int gI1, int gI2) const;
   std::complex<double> CpScconjScVGVG(int gI1, int gI2) const;
   std::complex<double> CpSdconjSdVGVG(int gI1, int gI2) const;
   std::complex<double> CpSsconjSsVGVG(int gI1, int gI2) const;
   std::complex<double> CpStconjStVGVG(int gI1, int gI2) const;
   std::complex<double> CpSuconjSuVGVG(int gI1, int gI2) const;
   double CpSbconjSbVG(int gI2, int gI1) const;
   double CpScconjScVG(int gI2, int gI1) const;
   double CpSdconjSdVG(int gI2, int gI1) const;
   double CpSsconjSsVG(int gI2, int gI1) const;
   double CpStconjStVG(int gI2, int gI1) const;
   double CpSuconjSuVG(int gI2, int gI1) const;
   std::complex<double> CpGluGluVGPL() const;
   std::complex<double> CpGluGluVGPR() const;
   double CpbarFbFbVGPL() const;
   double CpbarFbFbVGPR() const;
   double CpbarFcFcVGPL() const;
   double CpbarFcFcVGPR() const;
   double CpbarFdFdVGPL() const;
   double CpbarFdFdVGPR() const;
   double CpbarFsFsVGPL() const;
   double CpbarFsFsVGPR() const;
   double CpbarFtFtVGPL() const;
   double CpbarFtFtVGPR() const;
   double CpbarFuFuVGPL() const;
   double CpbarFuFuVGPR() const;
   double CpVGVGVGVG1() const;
   double CpVGVGVGVG2() const;
   double CpVGVGVGVG3() const;
   double CpbargWmgWmVP() const;
   double CpbargWmCgWmCVP() const;
   double CpconjVWmVPVWm() const;
   double CpbarFeFeVPPL() const;
   double CpbarFeFeVPPR() const;
   double CpbarFmFmVPPL() const;
   double CpbarFmFmVPPR() const;
   double CpbarFtauFtauVPPL() const;
   double CpbarFtauFtauVPPR() const;
   std::complex<double> CpHpmconjHpmVPVP(int gI1, int gI2) const;
   std::complex<double> CpSbconjSbVPVP(int gI1, int gI2) const;
   std::complex<double> CpScconjScVPVP(int gI1, int gI2) const;
   std::complex<double> CpSdconjSdVPVP(int gI1, int gI2) const;
   std::complex<double> CpSeconjSeVPVP(int gI1, int gI2) const;
   std::complex<double> CpSmconjSmVPVP(int gI1, int gI2) const;
   std::complex<double> CpSsconjSsVPVP(int gI1, int gI2) const;
   std::complex<double> CpStconjStVPVP(int gI1, int gI2) const;
   std::complex<double> CpStauconjStauVPVP(int gI1, int gI2) const;
   std::complex<double> CpSuconjSuVPVP(int gI1, int gI2) const;
   double CpHpmconjHpmVP(int gI2, int gI1) const;
   std::complex<double> CpSbconjSbVP(int gI2, int gI1) const;
   std::complex<double> CpScconjScVP(int gI2, int gI1) const;
   std::complex<double> CpSdconjSdVP(int gI2, int gI1) const;
   std::complex<double> CpSeconjSeVP(int gI2, int gI1) const;
   std::complex<double> CpSmconjSmVP(int gI2, int gI1) const;
   std::complex<double> CpSsconjSsVP(int gI2, int gI1) const;
   std::complex<double> CpStconjStVP(int gI2, int gI1) const;
   std::complex<double> CpStauconjStauVP(int gI2, int gI1) const;
   std::complex<double> CpSuconjSuVP(int gI2, int gI1) const;
   std::complex<double> CpbarChaChaVPPL(int gI1, int gI2) const;
   std::complex<double> CpbarChaChaVPPR(int gI1, int gI2) const;
   std::complex<double> CpHpmconjVWmVP(int gI2) const;
   double CpbarFbFbVPPL() const;
   double CpbarFbFbVPPR() const;
   double CpbarFcFcVPPL() const;
   double CpbarFcFcVPPR() const;
   double CpbarFdFdVPPL() const;
   double CpbarFdFdVPPR() const;
   double CpbarFsFsVPPL() const;
   double CpbarFsFsVPPR() const;
   double CpbarFtFtVPPL() const;
   double CpbarFtFtVPPR() const;
   double CpbarFuFuVPPL() const;
   double CpbarFuFuVPPR() const;
   double CpconjVWmVPVPVWm1() const;
   double CpconjVWmVPVPVWm2() const;
   double CpconjVWmVPVPVWm3() const;
   double CpbargWmgWmVZ() const;
   double CpbargWmCgWmCVZ() const;
   double CpconjVWmVWmVZ() const;
   double CpbarFeFeVZPL() const;
   double CpbarFeFeVZPR() const;
   double CpbarFmFmVZPL() const;
   double CpbarFmFmVZPR() const;
   double CpbarFtauFtauVZPL() const;
   double CpbarFtauFtauVZPR() const;
   double CpbarFveFveVZPL() const;
   double CpbarFveFveVZPR() const;
   double CpbarFvmFvmVZPL() const;
   double CpbarFvmFvmVZPR() const;
   double CpbarFvtFvtVZPL() const;
   double CpbarFvtFvtVZPR() const;
   std::complex<double> CpAhAhVZVZ(int gI1, int gI2) const;
   std::complex<double> CphhhhVZVZ(int gI1, int gI2) const;
   std::complex<double> CpHpmconjHpmVZVZ(int gI1, int gI2) const;
   std::complex<double> CpSbconjSbVZVZ(int gI1, int gI2) const;
   std::complex<double> CpScconjScVZVZ(int gI1, int gI2) const;
   std::complex<double> CpSdconjSdVZVZ(int gI1, int gI2) const;
   std::complex<double> CpSeconjSeVZVZ(int gI1, int gI2) const;
   std::complex<double> CpSmconjSmVZVZ(int gI1, int gI2) const;
   std::complex<double> CpSsconjSsVZVZ(int gI1, int gI2) const;
   std::complex<double> CpStconjStVZVZ(int gI1, int gI2) const;
   std::complex<double> CpStauconjStauVZVZ(int gI1, int gI2) const;
   std::complex<double> CpSuconjSuVZVZ(int gI1, int gI2) const;
   std::complex<double> CpAhhhVZ(int gI2, int gI1) const;
   double CpHpmconjHpmVZ(int gI2, int gI1) const;
   std::complex<double> CpSbconjSbVZ(int gI2, int gI1) const;
   std::complex<double> CpScconjScVZ(int gI2, int gI1) const;
   std::complex<double> CpSdconjSdVZ(int gI2, int gI1) const;
   std::complex<double> CpSeconjSeVZ(int gI2, int gI1) const;
   std::complex<double> CpSmconjSmVZ(int gI2, int gI1) const;
   std::complex<double> CpSsconjSsVZ(int gI2, int gI1) const;
   std::complex<double> CpStconjStVZ(int gI2, int gI1) const;
   std::complex<double> CpStauconjStauVZ(int gI2, int gI1) const;
   std::complex<double> CpSuconjSuVZ(int gI2, int gI1) const;
   std::complex<double> CpbarChaChaVZPL(int gI1, int gI2) const;
   std::complex<double> CpbarChaChaVZPR(int gI1, int gI2) const;
   std::complex<double> CpChiChiVZPL(int gI1, int gI2) const;
   std::complex<double> CpChiChiVZPR(int gI1, int gI2) const;
   std::complex<double> CphhVZVZ(int gI2) const;
   std::complex<double> CpHpmconjVWmVZ(int gI2) const;
   double CpbarFbFbVZPL() const;
   double CpbarFbFbVZPR() const;
   double CpbarFcFcVZPL() const;
   double CpbarFcFcVZPR() const;
   double CpbarFdFdVZPL() const;
   double CpbarFdFdVZPR() const;
   double CpbarFsFsVZPL() const;
   double CpbarFsFsVZPR() const;
   double CpbarFtFtVZPL() const;
   double CpbarFtFtVZPR() const;
   double CpbarFuFuVZPL() const;
   double CpbarFuFuVZPR() const;
   double CpconjVWmVWmVZVZ1() const;
   double CpconjVWmVWmVZVZ2() const;
   double CpconjVWmVWmVZVZ3() const;
   double CpbargPgWmconjVWm() const;
   double CpbargWmCgPconjVWm() const;
   double CpbargWmCgZconjVWm() const;
   double CpbargZgWmconjVWm() const;
   double CpbarFveFeconjVWmPL() const;
   double CpbarFveFeconjVWmPR() const;
   double CpbarFvmFmconjVWmPL() const;
   double CpbarFvmFmconjVWmPR() const;
   double CpbarFvtFtauconjVWmPL() const;
   double CpbarFvtFtauconjVWmPR() const;
   std::complex<double> CpAhAhconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CphhhhconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpHpmconjHpmconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpSbconjSbconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpScconjScconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpSdconjSdconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpSeconjSeconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpSmconjSmconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpSsconjSsconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpStconjStconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpStauconjStauconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpSuconjSuconjVWmVWm(int gI1, int gI2) const;
   std::complex<double> CpAhHpmconjVWm(int gI2, int gI1) const;
   std::complex<double> CphhHpmconjVWm(int gI2, int gI1) const;
   std::complex<double> CpSbconjStconjVWm(int gI2, int gI1) const;
   std::complex<double> CpSdconjSuconjVWm(int gI2, int gI1) const;
   std::complex<double> CpSsconjScconjVWm(int gI2, int gI1) const;
   std::complex<double> CpChiChaconjVWmPL(int gI1, int gI2) const;
   std::complex<double> CpChiChaconjVWmPR(int gI1, int gI2) const;
   std::complex<double> CphhconjVWmVWm(int gI2) const;
   double CpbarFcFsconjVWmPL() const;
   double CpbarFcFsconjVWmPR() const;
   double CpbarFtFbconjVWmPL() const;
   double CpbarFtFbconjVWmPR() const;
   double CpbarFuFdconjVWmPL() const;
   double CpbarFuFdconjVWmPR() const;
   double CpconjVWmconjVWmVWmVWm1() const;
   double CpconjVWmconjVWmVWmVWm2() const;
   double CpconjVWmconjVWmVWmVWm3() const;
   std::complex<double> CpbarChaUChiHpmPL(int gI1, int gO2, int gI2) const;
   std::complex<double> CpbarChaUChiHpmPR(int gI1, int gO1, int gI2) const;
   std::complex<double> CpUChiChaconjHpmPL(int gO2, int gI2, int gI1) const;
   std::complex<double> CpUChiChaconjHpmPR(int gO1, int gI2, int gI1) const;
   std::complex<double> CpChiUChihhPL(int gI2, int gO2, int gI1) const;
   std::complex<double> CpChiUChihhPR(int gI2, int gO1, int gI1) const;
   std::complex<double> CpbarChaUChiVWmPL(int gI1, int gO2) const;
   std::complex<double> CpbarChaUChiVWmPR(int gI1, int gO1) const;
   std::complex<double> CpUChiFbconjSbPL(int gO2, int gI1) const;
   std::complex<double> CpUChiFbconjSbPR(int gO1, int gI1) const;
   std::complex<double> CpUChiFcconjScPL(int gO2, int gI1) const;
   std::complex<double> CpUChiFcconjScPR(int gO1, int gI1) const;
   std::complex<double> CpUChiFdconjSdPL(int gO2, int gI1) const;
   std::complex<double> CpUChiFdconjSdPR(int gO1, int gI1) const;
   std::complex<double> CpUChiFeconjSePL(int gO2, int gI1) const;
   std::complex<double> CpUChiFeconjSePR(int gO1, int gI1) const;
   std::complex<double> CpUChiFmconjSmPL(int gO2, int gI1) const;
   std::complex<double> CpUChiFmconjSmPR(int gO1, int gI1) const;
   std::complex<double> CpUChiFsconjSsPL(int gO2, int gI1) const;
   std::complex<double> CpUChiFsconjSsPR(int gO1, int gI1) const;
   std::complex<double> CpUChiFtconjStPL(int gO2, int gI1) const;
   std::complex<double> CpUChiFtconjStPR(int gO1, int gI1) const;
   std::complex<double> CpUChiFtauconjStauPL(int gO2, int gI1) const;
   std::complex<double> CpUChiFtauconjStauPR(int gO1, int gI1) const;
   std::complex<double> CpUChiFuconjSuPL(int gO2, int gI1) const;
   std::complex<double> CpUChiFuconjSuPR(int gO1, int gI1) const;
   std::complex<double> CpChiUChiAhPL(int gI1, int gO2, int gI2) const;
   std::complex<double> CpChiUChiAhPR(int gI1, int gO1, int gI2) const;
   std::complex<double> CpbarFbUChiSbPL(int gO2, int gI2) const;
   std::complex<double> CpbarFbUChiSbPR(int gO1, int gI2) const;
   std::complex<double> CpbarFcUChiScPL(int gO2, int gI2) const;
   std::complex<double> CpbarFcUChiScPR(int gO1, int gI2) const;
   std::complex<double> CpbarFdUChiSdPL(int gO2, int gI2) const;
   std::complex<double> CpbarFdUChiSdPR(int gO1, int gI2) const;
   std::complex<double> CpbarFeUChiSePL(int gO2, int gI2) const;
   std::complex<double> CpbarFeUChiSePR(int gO1, int gI2) const;
   std::complex<double> CpbarFmUChiSmPL(int gO2, int gI2) const;
   std::complex<double> CpbarFmUChiSmPR(int gO1, int gI2) const;
   std::complex<double> CpbarFsUChiSsPL(int gO2, int gI2) const;
   std::complex<double> CpbarFsUChiSsPR(int gO1, int gI2) const;
   std::complex<double> CpbarFtUChiStPL(int gO2, int gI2) const;
   std::complex<double> CpbarFtUChiStPR(int gO1, int gI2) const;
   std::complex<double> CpbarFtauUChiStauPL(int gO2, int gI2) const;
   std::complex<double> CpbarFtauUChiStauPR(int gO1, int gI2) const;
   std::complex<double> CpbarFuUChiSuPL(int gO2, int gI2) const;
   std::complex<double> CpbarFuUChiSuPR(int gO1, int gI2) const;
   std::complex<double> CpUChiChaconjVWmPR(int gO2, int gI2) const;
   std::complex<double> CpUChiChaconjVWmPL(int gO1, int gI2) const;
   std::complex<double> CpChiUChiVZPL(int gI2, int gO2) const;
   std::complex<double> CpChiUChiVZPR(int gI2, int gO1) const;
   double CpbarFveUChiSveLPL(int ) const;
   std::complex<double> CpbarFveUChiSveLPR(int gO1) const;
   double CpbarFvmUChiSvmLPL(int ) const;
   std::complex<double> CpbarFvmUChiSvmLPR(int gO1) const;
   double CpbarFvtUChiSvtLPL(int ) const;
   std::complex<double> CpbarFvtUChiSvtLPR(int gO1) const;
   std::complex<double> CpUChiFveconjSveLPL(int gO2) const;
   double CpUChiFveconjSveLPR(int ) const;
   std::complex<double> CpUChiFvmconjSvmLPL(int gO2) const;
   double CpUChiFvmconjSvmLPR(int ) const;
   std::complex<double> CpUChiFvtconjSvtLPL(int gO2) const;
   double CpUChiFvtconjSvtLPR(int ) const;
   std::complex<double> CpbarUChaChaAhPL(int gO2, int gI1, int gI2) const;
   std::complex<double> CpbarUChaChaAhPR(int gO1, int gI1, int gI2) const;
   std::complex<double> CpbarUChaChahhPL(int gO2, int gI2, int gI1) const;
   std::complex<double> CpbarUChaChahhPR(int gO1, int gI2, int gI1) const;
   std::complex<double> CpbarUChaChiHpmPL(int gO2, int gI2, int gI1) const;
   std::complex<double> CpbarUChaChiHpmPR(int gO1, int gI2, int gI1) const;
   std::complex<double> CpbarUChaFbconjStPL(int gO2, int gI1) const;
   std::complex<double> CpbarUChaFbconjStPR(int gO1, int gI1) const;
   std::complex<double> CpbarUChaFdconjSuPL(int gO2, int gI1) const;
   std::complex<double> CpbarUChaFdconjSuPR(int gO1, int gI1) const;
   std::complex<double> CpbarUChaFsconjScPL(int gO2, int gI1) const;
   std::complex<double> CpbarUChaFsconjScPR(int gO1, int gI1) const;
   std::complex<double> CpbarFcbarUChaSsPL(int gO2, int gI2) const;
   std::complex<double> CpbarFcbarUChaSsPR(int gO1, int gI2) const;
   std::complex<double> CpbarFtbarUChaSbPL(int gO2, int gI2) const;
   std::complex<double> CpbarFtbarUChaSbPR(int gO1, int gI2) const;
   std::complex<double> CpbarFubarUChaSdPL(int gO2, int gI2) const;
   std::complex<double> CpbarFubarUChaSdPR(int gO1, int gI2) const;
   double CpbarFvebarUChaSePL(int , int ) const;
   std::complex<double> CpbarFvebarUChaSePR(int gO1, int gI2) const;
   double CpbarFvmbarUChaSmPL(int , int ) const;
   std::complex<double> CpbarFvmbarUChaSmPR(int gO1, int gI2) const;
   double CpbarFvtbarUChaStauPL(int , int ) const;
   std::complex<double> CpbarFvtbarUChaStauPR(int gO1, int gI2) const;
   std::complex<double> CpbarUChaChaVPPR(int gO2, int gI2) const;
   std::complex<double> CpbarUChaChaVPPL(int gO1, int gI2) const;
   std::complex<double> CpbarUChaChaVZPR(int gO2, int gI2) const;
   std::complex<double> CpbarUChaChaVZPL(int gO1, int gI2) const;
   std::complex<double> CpbarUChaChiVWmPR(int gO2, int gI2) const;
   std::complex<double> CpbarUChaChiVWmPL(int gO1, int gI2) const;
   double CpbarUChaFeconjSveLPL(int gO2) const;
   double CpbarUChaFeconjSveLPR(int gO1) const;
   double CpbarUChaFmconjSvmLPL(int gO2) const;
   double CpbarUChaFmconjSvmLPR(int gO1) const;
   double CpbarUChaFtauconjSvtLPL(int gO2) const;
   double CpbarUChaFtauconjSvtLPR(int gO1) const;
   std::complex<double> CpGluFbconjSbPL(int gI1) const;
   std::complex<double> CpGluFbconjSbPR(int gI1) const;
   std::complex<double> CpGluFcconjScPL(int gI1) const;
   std::complex<double> CpGluFcconjScPR(int gI1) const;
   std::complex<double> CpGluFdconjSdPL(int gI1) const;
   std::complex<double> CpGluFdconjSdPR(int gI1) const;
   std::complex<double> CpGluFsconjSsPL(int gI1) const;
   std::complex<double> CpGluFsconjSsPR(int gI1) const;
   std::complex<double> CpGluFtconjStPL(int gI1) const;
   std::complex<double> CpGluFtconjStPR(int gI1) const;
   std::complex<double> CpGluFuconjSuPL(int gI1) const;
   std::complex<double> CpGluFuconjSuPR(int gI1) const;
   std::complex<double> CpbarFbGluSbPL(int gI2) const;
   std::complex<double> CpbarFbGluSbPR(int gI2) const;
   std::complex<double> CpbarFcGluScPL(int gI2) const;
   std::complex<double> CpbarFcGluScPR(int gI2) const;
   std::complex<double> CpbarFdGluSdPL(int gI2) const;
   std::complex<double> CpbarFdGluSdPR(int gI2) const;
   std::complex<double> CpbarFsGluSsPL(int gI2) const;
   std::complex<double> CpbarFsGluSsPR(int gI2) const;
   std::complex<double> CpbarFtGluStPL(int gI2) const;
   std::complex<double> CpbarFtGluStPR(int gI2) const;
   std::complex<double> CpbarFuGluSuPL(int gI2) const;
   std::complex<double> CpbarFuGluSuPR(int gI2) const;
   std::complex<double> CpbarFdChaSuPL(int gI2, int gI1) const;
   std::complex<double> CpbarFdChaSuPR(int gI2, int gI1) const;
   std::complex<double> CpbarFdChiSdPL(int gI2, int gI1) const;
   std::complex<double> CpbarFdChiSdPR(int gI2, int gI1) const;
   std::complex<double> CpbarFdFdhhPL(int gI1) const;
   std::complex<double> CpbarFdFdhhPR(int gI1) const;
   std::complex<double> CpbarFdFuHpmPL(int gI1) const;
   std::complex<double> CpbarFdFuHpmPR(int gI1) const;
   std::complex<double> CpbarFdFdAhPL(int gI2) const;
   std::complex<double> CpbarFdFdAhPR(int gI2) const;
   double CpbarFdFuVWmPR() const;
   double CpbarFdFuVWmPL() const;
   std::complex<double> CpbarFsChaScPL(int gI2, int gI1) const;
   std::complex<double> CpbarFsChaScPR(int gI2, int gI1) const;
   std::complex<double> CpbarFsChiSsPL(int gI2, int gI1) const;
   std::complex<double> CpbarFsChiSsPR(int gI2, int gI1) const;
   std::complex<double> CpbarFsFcHpmPL(int gI1) const;
   std::complex<double> CpbarFsFcHpmPR(int gI1) const;
   std::complex<double> CpbarFsFshhPL(int gI1) const;
   std::complex<double> CpbarFsFshhPR(int gI1) const;
   std::complex<double> CpbarFsFsAhPL(int gI2) const;
   std::complex<double> CpbarFsFsAhPR(int gI2) const;
   double CpbarFsFcVWmPR() const;
   double CpbarFsFcVWmPL() const;
   std::complex<double> CpbarFbChaStPL(int gI2, int gI1) const;
   std::complex<double> CpbarFbChaStPR(int gI2, int gI1) const;
   std::complex<double> CpbarFbChiSbPL(int gI2, int gI1) const;
   std::complex<double> CpbarFbChiSbPR(int gI2, int gI1) const;
   std::complex<double> CpbarFbFbhhPL(int gI1) const;
   std::complex<double> CpbarFbFbhhPR(int gI1) const;
   std::complex<double> CpbarFbFtHpmPL(int gI1) const;
   std::complex<double> CpbarFbFtHpmPR(int gI1) const;
   std::complex<double> CpbarFbFbAhPL(int gI2) const;
   std::complex<double> CpbarFbFbAhPR(int gI2) const;
   double CpbarFbFtVWmPR() const;
   double CpbarFbFtVWmPL() const;
   std::complex<double> CpbarFubarChaSdPL(int gI1, int gI2) const;
   std::complex<double> CpbarFubarChaSdPR(int gI1, int gI2) const;
   std::complex<double> CpbarFuChiSuPL(int gI2, int gI1) const;
   std::complex<double> CpbarFuChiSuPR(int gI2, int gI1) const;
   std::complex<double> CpbarFuFdconjHpmPL(int gI1) const;
   std::complex<double> CpbarFuFdconjHpmPR(int gI1) const;
   std::complex<double> CpbarFuFuhhPL(int gI1) const;
   std::complex<double> CpbarFuFuhhPR(int gI1) const;
   std::complex<double> CpbarFuFuAhPL(int gI2) const;
   std::complex<double> CpbarFuFuAhPR(int gI2) const;
   std::complex<double> CpbarFcbarChaSsPL(int gI1, int gI2) const;
   std::complex<double> CpbarFcbarChaSsPR(int gI1, int gI2) const;
   std::complex<double> CpbarFcChiScPL(int gI2, int gI1) const;
   std::complex<double> CpbarFcChiScPR(int gI2, int gI1) const;
   std::complex<double> CpbarFcFchhPL(int gI1) const;
   std::complex<double> CpbarFcFchhPR(int gI1) const;
   std::complex<double> CpbarFcFsconjHpmPL(int gI1) const;
   std::complex<double> CpbarFcFsconjHpmPR(int gI1) const;
   std::complex<double> CpbarFcFcAhPL(int gI2) const;
   std::complex<double> CpbarFcFcAhPR(int gI2) const;
   std::complex<double> CpbarFtbarChaSbPL(int gI1, int gI2) const;
   std::complex<double> CpbarFtbarChaSbPR(int gI1, int gI2) const;
   std::complex<double> CpbarFtChiStPL(int gI2, int gI1) const;
   std::complex<double> CpbarFtChiStPR(int gI2, int gI1) const;
   std::complex<double> CpbarFtFbconjHpmPL(int gI1) const;
   std::complex<double> CpbarFtFbconjHpmPR(int gI1) const;
   std::complex<double> CpbarFtFthhPL(int gI1) const;
   std::complex<double> CpbarFtFthhPR(int gI1) const;
   std::complex<double> CpbarFtFtAhPL(int gI2) const;
   std::complex<double> CpbarFtFtAhPR(int gI2) const;
   double CpbarFvebarChaSePL(int , int ) const;
   std::complex<double> CpbarFvebarChaSePR(int gI1, int gI2) const;
   double CpbarFveFeconjHpmPL(int ) const;
   std::complex<double> CpbarFveFeconjHpmPR(int gI1) const;
   double CpbarFveChiSveLPL(int ) const;
   std::complex<double> CpbarFveChiSveLPR(int gI2) const;
   double CpbarFvmbarChaSmPL(int , int ) const;
   std::complex<double> CpbarFvmbarChaSmPR(int gI1, int gI2) const;
   double CpbarFvmFmconjHpmPL(int ) const;
   std::complex<double> CpbarFvmFmconjHpmPR(int gI1) const;
   double CpbarFvmChiSvmLPL(int ) const;
   std::complex<double> CpbarFvmChiSvmLPR(int gI2) const;
   double CpbarFvtbarChaStauPL(int , int ) const;
   std::complex<double> CpbarFvtbarChaStauPR(int gI1, int gI2) const;
   double CpbarFvtFtauconjHpmPL(int ) const;
   std::complex<double> CpbarFvtFtauconjHpmPR(int gI1) const;
   double CpbarFvtChiSvtLPL(int ) const;
   std::complex<double> CpbarFvtChiSvtLPR(int gI2) const;
   std::complex<double> CpbarFeChiSePL(int gI2, int gI1) const;
   std::complex<double> CpbarFeChiSePR(int gI2, int gI1) const;
   std::complex<double> CpbarFeFehhPL(int gI1) const;
   std::complex<double> CpbarFeFehhPR(int gI1) const;
   std::complex<double> CpbarFeFveHpmPL(int gI1) const;
   double CpbarFeFveHpmPR(int ) const;
   std::complex<double> CpbarFeFeAhPL(int gI2) const;
   std::complex<double> CpbarFeFeAhPR(int gI2) const;
   std::complex<double> CpbarFeChaSveLPL(int gI2) const;
   std::complex<double> CpbarFeChaSveLPR(int gI2) const;
   double CpbarFeFveVWmPR() const;
   double CpbarFeFveVWmPL() const;
   std::complex<double> CpbarFmChiSmPL(int gI2, int gI1) const;
   std::complex<double> CpbarFmChiSmPR(int gI2, int gI1) const;
   std::complex<double> CpbarFmFmhhPL(int gI1) const;
   std::complex<double> CpbarFmFmhhPR(int gI1) const;
   std::complex<double> CpbarFmFvmHpmPL(int gI1) const;
   double CpbarFmFvmHpmPR(int ) const;
   std::complex<double> CpbarFmFmAhPL(int gI2) const;
   std::complex<double> CpbarFmFmAhPR(int gI2) const;
   std::complex<double> CpbarFmChaSvmLPL(int gI2) const;
   std::complex<double> CpbarFmChaSvmLPR(int gI2) const;
   double CpbarFmFvmVWmPR() const;
   double CpbarFmFvmVWmPL() const;
   std::complex<double> CpbarFtauChiStauPL(int gI2, int gI1) const;
   std::complex<double> CpbarFtauChiStauPR(int gI2, int gI1) const;
   std::complex<double> CpbarFtauFtauhhPL(int gI1) const;
   std::complex<double> CpbarFtauFtauhhPR(int gI1) const;
   std::complex<double> CpbarFtauFvtHpmPL(int gI1) const;
   double CpbarFtauFvtHpmPR(int ) const;
   std::complex<double> CpbarFtauFtauAhPL(int gI2) const;
   std::complex<double> CpbarFtauFtauAhPR(int gI2) const;
   std::complex<double> CpbarFtauChaSvtLPL(int gI2) const;
   std::complex<double> CpbarFtauChaSvtLPR(int gI2) const;
   double CpbarFtauFvtVWmPR() const;
   double CpbarFtauFvtVWmPL() const;
   std::complex<double> self_energy_Sd_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Sd_1loop(double p) const;
   std::complex<double> self_energy_Su_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Su_1loop(double p) const;
   std::complex<double> self_energy_Se_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Se_1loop(double p) const;
   std::complex<double> self_energy_Sm_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Sm_1loop(double p) const;
   std::complex<double> self_energy_Stau_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Stau_1loop(double p) const;
   std::complex<double> self_energy_Ss_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Ss_1loop(double p) const;
   std::complex<double> self_energy_Sc_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Sc_1loop(double p) const;
   std::complex<double> self_energy_Sb_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Sb_1loop(double p) const;
   std::complex<double> self_energy_St_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_St_1loop(double p) const;
   std::complex<double> self_energy_hh_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_hh_1loop(double p) const;
   std::complex<double> self_energy_Ah_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Ah_1loop(double p) const;
   std::complex<double> self_energy_Hpm_1loop(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Hpm_1loop(double p) const;
   std::complex<double> self_energy_SveL_1loop(double p ) const;
   std::complex<double> self_energy_SvmL_1loop(double p ) const;
   std::complex<double> self_energy_SvtL_1loop(double p ) const;
   std::complex<double> self_energy_VG_1loop(double p ) const;
   std::complex<double> self_energy_VP_1loop(double p ) const;
   std::complex<double> self_energy_VZ_1loop(double p ) const;
   std::complex<double> self_energy_VWm_1loop(double p ) const;
   std::complex<double> self_energy_Chi_1loop_1(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,4,4> self_energy_Chi_1loop_1(double p) const;
   std::complex<double> self_energy_Chi_1loop_PR(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,4,4> self_energy_Chi_1loop_PR(double p) const;
   std::complex<double> self_energy_Chi_1loop_PL(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,4,4> self_energy_Chi_1loop_PL(double p) const;
   std::complex<double> self_energy_Cha_1loop_1(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Cha_1loop_1(double p) const;
   std::complex<double> self_energy_Cha_1loop_PR(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Cha_1loop_PR(double p) const;
   std::complex<double> self_energy_Cha_1loop_PL(double p , int gO1, int gO2) const;
   Eigen::Matrix<std::complex<double>,2,2> self_energy_Cha_1loop_PL(double p) const;
   std::complex<double> self_energy_Glu_1loop_1(double p ) const;
   std::complex<double> self_energy_Glu_1loop_PR(double p ) const;
   std::complex<double> self_energy_Glu_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fd_1loop_1(double p ) const;
   std::complex<double> self_energy_Fd_1loop_PR(double p ) const;
   std::complex<double> self_energy_Fd_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fs_1loop_1(double p ) const;
   std::complex<double> self_energy_Fs_1loop_PR(double p ) const;
   std::complex<double> self_energy_Fs_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fb_1loop_1(double p ) const;
   std::complex<double> self_energy_Fb_1loop_PR(double p ) const;
   std::complex<double> self_energy_Fb_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fu_1loop_1(double p ) const;
   std::complex<double> self_energy_Fu_1loop_PR(double p ) const;
   std::complex<double> self_energy_Fu_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fc_1loop_1(double p ) const;
   std::complex<double> self_energy_Fc_1loop_PR(double p ) const;
   std::complex<double> self_energy_Fc_1loop_PL(double p ) const;
   std::complex<double> self_energy_Ft_1loop_1(double p ) const;
   std::complex<double> self_energy_Ft_1loop_PR(double p ) const;
   std::complex<double> self_energy_Ft_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fve_1loop_1(double p ) const;
   std::complex<double> self_energy_Fve_1loop_PR(double p ) const;
   std::complex<double> self_energy_Fve_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fvm_1loop_1(double p ) const;
   std::complex<double> self_energy_Fvm_1loop_PR(double p ) const;
   std::complex<double> self_energy_Fvm_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fvt_1loop_1(double p ) const;
   std::complex<double> self_energy_Fvt_1loop_PR(double p ) const;
   std::complex<double> self_energy_Fvt_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fe_1loop_1(double p ) const;
   std::complex<double> self_energy_Fe_1loop_PR(double p ) const;
   std::complex<double> self_energy_Fe_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fm_1loop_1(double p ) const;
   std::complex<double> self_energy_Fm_1loop_PR(double p ) const;
   std::complex<double> self_energy_Fm_1loop_PL(double p ) const;
   std::complex<double> self_energy_Ftau_1loop_1(double p ) const;
   std::complex<double> self_energy_Ftau_1loop_PR(double p ) const;
   std::complex<double> self_energy_Ftau_1loop_PL(double p ) const;
   std::complex<double> self_energy_Fb_1loop_1_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Fb_1loop_PR_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Fb_1loop_PL_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Fe_1loop_1_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Fe_1loop_PR_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Fe_1loop_PL_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Fm_1loop_1_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Fm_1loop_PR_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Fm_1loop_PL_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Ftau_1loop_1_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Ftau_1loop_PR_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Ftau_1loop_PL_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Ft_1loop_1_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Ft_1loop_PR_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Ft_1loop_PL_heavy_rotated(double p ) const;
   std::complex<double> self_energy_Ft_1loop_1_heavy(double p ) const;
   std::complex<double> self_energy_Ft_1loop_PR_heavy(double p ) const;
   std::complex<double> self_energy_Ft_1loop_PL_heavy(double p ) const;
   std::complex<double> tadpole_hh_1loop(int gO1) const;


   /// calculates the tadpoles at current loop order
   void tadpole_equations(double[number_of_ewsb_equations]) const;
   /// calculates the tadpoles at current loop order
   Eigen::Matrix<double,number_of_ewsb_equations,1> tadpole_equations() const;
   /// calculates the tadpoles divided by VEVs at current loop order
   Eigen::Matrix<double,number_of_ewsb_equations,1> tadpole_equations_over_vevs() const;

   void calculate_MTopSquark_2nd_generation(double&, double&, double&) const;
   void calculate_MBottomSquark_2nd_generation(double&, double&, double&) const;
   void calculate_MSneutrino_2nd_generation(double&, double&, double&) const;
   void calculate_MSelectron_2nd_generation(double&, double&, double&) const;

   void calculate_MTopSquark_3rd_generation(double&, double&, double&) const;
   void calculate_MBottomSquark_3rd_generation(double&, double&, double&) const;
   void calculate_MSneutrino_3rd_generation(double&, double&, double&) const;
   void calculate_MSelectron_3rd_generation(double&, double&, double&) const;

   Eigen::Matrix<double,2,2> self_energy_hh_2loop() const;
   Eigen::Matrix<double,2,2> self_energy_Ah_2loop() const;

   Eigen::Matrix<double,2,1> tadpole_hh_2loop() const;


   void calculate_MVG_pole();
   void calculate_MGlu_pole();
   void calculate_MVP_pole();
   void calculate_MVZ_pole();
   void calculate_MFd_pole();
   void calculate_MFs_pole();
   void calculate_MFb_pole();
   void calculate_MFu_pole();
   void calculate_MFc_pole();
   void calculate_MFt_pole();
   void calculate_MFve_pole();
   void calculate_MFvm_pole();
   void calculate_MFvt_pole();
   void calculate_MFe_pole();
   void calculate_MFm_pole();
   void calculate_MFtau_pole();
   void calculate_MSveL_pole();
   void calculate_MSvmL_pole();
   void calculate_MSvtL_pole();
   void calculate_MSd_pole();
   void calculate_MSu_pole();
   void calculate_MSe_pole();
   void calculate_MSm_pole();
   void calculate_MStau_pole();
   void calculate_MSs_pole();
   void calculate_MSc_pole();
   void calculate_MSb_pole();
   void calculate_MSt_pole();
   void calculate_Mhh_pole();
   void calculate_MAh_pole();
   void calculate_MHpm_pole();
   void calculate_MChi_pole();
   void calculate_MCha_pole();
   void calculate_MVWm_pole();
   double calculate_MVWm_pole(double);
   double calculate_MVZ_pole(double);

   double calculate_MFve_DRbar(double) const;
   double calculate_MFvm_DRbar(double) const;
   double calculate_MFvt_DRbar(double) const;
   double calculate_MFe_DRbar(double) const;
   double calculate_MFm_DRbar(double) const;
   double calculate_MFtau_DRbar(double) const;
   double calculate_MFu_DRbar(double) const;
   double calculate_MFc_DRbar(double) const;
   double calculate_MFt_DRbar(double) const;
   double calculate_MFd_DRbar(double) const;
   double calculate_MFs_DRbar(double) const;
   double calculate_MFb_DRbar(double) const;
   double calculate_MVP_DRbar(double);
   double calculate_MVZ_DRbar(double);
   double calculate_MVWm_DRbar(double);

   double v() const;
   double Betax() const;
   double Alpha() const;
   double ThetaW() const;


private:
   int ewsb_loop_order{2};           ///< loop order for EWSB
   int pole_mass_loop_order{2};      ///< loop order for pole masses
   bool calculate_sm_pole_masses{false};  ///< switch to calculate the pole masses of the Standard Model particles
   bool calculate_bsm_pole_masses{true};  ///< switch to calculate the pole masses of the BSM particles
   bool force_output{false};              ///< switch to force output of pole masses
   double precision{1.e-3};               ///< RG running precision
   double ewsb_iteration_precision{1.e-5};///< precision goal of EWSB solution
   MSSMNoFV_physical physical{}; ///< contains the pole masses and mixings
   Problems problems{MSSMNoFV_info::model_name,
                     &MSSMNoFV_info::particle_names_getter,
                     &MSSMNoFV_info::parameter_names_getter}; ///< problems
   Loop_corrections loop_corrections{}; ///< used pole mass corrections
   std::shared_ptr<MSSMNoFV_ewsb_solver_interface> ewsb_solver{};
   Threshold_corrections threshold_corrections{}; ///< used threshold corrections

   int get_number_of_ewsb_iterations() const;
   int get_number_of_mass_iterations() const;
   int solve_ewsb_tree_level_custom();
   void copy_DRbar_masses_to_pole_masses();

   // Passarino-Veltman loop functions
   double A0(double) const noexcept;
   double B0(double, double, double) const noexcept;
   double B1(double, double, double) const noexcept;
   double B00(double, double, double) const noexcept;
   double B22(double, double, double) const noexcept;
   double H0(double, double, double) const noexcept;
   double F0(double, double, double) const noexcept;
   double G0(double, double, double) const noexcept;

   // DR-bar masses
   double MVG{};
   double MGlu{};
   double MFd{};
   double MFs{};
   double MFb{};
   double MFu{};
   double MFc{};
   double MFt{};
   double MFve{};
   double MFvm{};
   double MFvt{};
   double MFe{};
   double MFm{};
   double MFtau{};
   double MSveL{};
   double MSvmL{};
   double MSvtL{};
   Eigen::Array<double,2,1> MSd{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> MSu{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> MSe{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> MSm{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> MStau{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> MSs{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> MSc{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> MSb{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> MSt{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> Mhh{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> MAh{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,2,1> MHpm{Eigen::Array<double,2,1>::Zero()};
   Eigen::Array<double,4,1> MChi{Eigen::Array<double,4,1>::Zero()};
   Eigen::Array<double,2,1> MCha{Eigen::Array<double,2,1>::Zero()};
   double MVWm{};
   double MVP{};
   double MVZ{};

   // DR-bar mixing matrices
   Eigen::Matrix<double,2,2> ZD{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZU{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZE{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZM{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZTau{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZS{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZC{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZB{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZT{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZH{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZA{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZP{Eigen::Matrix<double,2,2>::Zero()};
   Eigen::Matrix<std::complex<double>,4,4> ZN{Eigen::Matrix<std::complex<double>,4,4>::Zero()};
   Eigen::Matrix<std::complex<double>,2,2> UM{Eigen::Matrix<std::complex<double>,2,2>::Zero()};
   Eigen::Matrix<std::complex<double>,2,2> UP{Eigen::Matrix<std::complex<double>,2,2>::Zero()};
   Eigen::Matrix<double,2,2> ZZ{Eigen::Matrix<double,2,2>::Zero()};

   // phases
   std::complex<double> PhaseGlu{1.,0.};

   // extra parameters

};

std::ostream& operator<<(std::ostream&, const MSSMNoFV_mass_eigenstates&);

} // namespace flexiblesusy

#endif
