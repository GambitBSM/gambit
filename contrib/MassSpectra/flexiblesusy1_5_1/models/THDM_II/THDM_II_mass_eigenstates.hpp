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

// File generated at Wed 29 Mar 2017 15:37:10

/**
 * @file THDM_II_mass_eigenstates.hpp
 *
 * @brief contains class for model with routines needed to solve boundary
 *        value problem using the two_scale solver by solving EWSB
 *        and determine the pole masses and mixings
 *
 * This file was generated at Wed 29 Mar 2017 15:37:10 with FlexibleSUSY
 * 1.5.1 (git commit: unknown) and SARAH 4.9.0 .
 */

#ifndef THDM_II_MASS_EIGENSTATES_H
#define THDM_II_MASS_EIGENSTATES_H

#include "THDM_II_two_scale_soft_parameters.hpp"
#include "THDM_II_physical.hpp"
#include "THDM_II_info.hpp"
#include "two_loop_corrections.hpp"
#include "problems.hpp"
#include "config.h"

#include <iosfwd>
#include <string>

#ifdef ENABLE_THREADS
#include <mutex>
#endif

#include <gsl/gsl_vector.h>
#include <Eigen/Core>

namespace flexiblesusy {

class EWSB_solver;
/**
 * @class THDM_II_mass_eigenstates
 * @brief model class with routines for determing masses and mixinga and EWSB
 */
class THDM_II_mass_eigenstates : public THDM_II_soft_parameters {
public:
   explicit THDM_II_mass_eigenstates(const THDM_II_input_parameters& input_ = THDM_II_input_parameters());
   virtual ~THDM_II_mass_eigenstates();

   /// number of EWSB equations
   static const std::size_t number_of_ewsb_equations = 2;

   void calculate_DRbar_masses();
   void calculate_DRbar_parameters();
   void calculate_pole_masses();
   void check_pole_masses_for_tachyons();
   virtual void clear();
   void clear_DRbar_parameters();
   Eigen::ArrayXd get_DRbar_masses() const;
   void do_calculate_sm_pole_masses(bool);
   bool do_calculate_sm_pole_masses() const;
   void do_force_output(bool);
   bool do_force_output() const;
   void reorder_DRbar_masses();
   void reorder_pole_masses();
   void set_ewsb_iteration_precision(double);
   void set_ewsb_loop_order(unsigned);
   void set_two_loop_corrections(const Two_loop_corrections&);
   const Two_loop_corrections& get_two_loop_corrections() const;
   void set_DRbar_masses(const Eigen::ArrayXd&);
   void set_number_of_ewsb_iterations(std::size_t);
   void set_number_of_mass_iterations(std::size_t);
   std::size_t get_number_of_ewsb_iterations() const;
   std::size_t get_number_of_mass_iterations() const;
   void set_pole_mass_loop_order(unsigned);
   unsigned get_pole_mass_loop_order() const;
   void set_physical(const THDM_II_physical&);
   double get_ewsb_iteration_precision() const;
   double get_ewsb_loop_order() const;
   const THDM_II_physical& get_physical() const;
   THDM_II_physical& get_physical();
   const Problems<THDM_II_info::NUMBER_OF_PARTICLES>& get_problems() const;
   Problems<THDM_II_info::NUMBER_OF_PARTICLES>& get_problems();
   int solve_ewsb_tree_level();
   int solve_ewsb_one_loop();
   int solve_ewsb();            ///< solve EWSB at ewsb_loop_order level

   void calculate_spectrum();
   void clear_problems();
   std::string name() const;
   void run_to(double scale, double eps = -1.0);
   void print(std::ostream& out = std::cout) const;
   void set_precision(double);
   double get_precision() const;


   double get_MVG() const { return MVG; }
   const Eigen::Array<double,3,1>& get_MFv() const { return MFv; }
   double get_MFv(int i) const { return MFv(i); }
   const Eigen::Array<double,2,1>& get_Mhh() const { return Mhh; }
   double get_Mhh(int i) const { return Mhh(i); }
   const Eigen::Array<double,2,1>& get_MAh() const { return MAh; }
   double get_MAh(int i) const { return MAh(i); }
   const Eigen::Array<double,2,1>& get_MHm() const { return MHm; }
   double get_MHm(int i) const { return MHm(i); }
   const Eigen::Array<double,3,1>& get_MFd() const { return MFd; }
   double get_MFd(int i) const { return MFd(i); }
   const Eigen::Array<double,3,1>& get_MFu() const { return MFu; }
   double get_MFu(int i) const { return MFu(i); }
   const Eigen::Array<double,3,1>& get_MFe() const { return MFe; }
   double get_MFe(int i) const { return MFe(i); }
   double get_MVWm() const { return MVWm; }
   double get_MVP() const { return MVP; }
   double get_MVZ() const { return MVZ; }

   
   Eigen::Array<double,1,1> get_MChargedHiggs() const;

   Eigen::Array<double,1,1> get_MPseudoscalarHiggs() const;

   const Eigen::Matrix<double,2,2>& get_ZH() const { return ZH; }
   double get_ZH(int i, int k) const { return ZH(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZA() const { return ZA; }
   double get_ZA(int i, int k) const { return ZA(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZP() const { return ZP; }
   double get_ZP(int i, int k) const { return ZP(i,k); }
   const Eigen::Matrix<std::complex<double>,3,3>& get_Vd() const { return Vd; }
   const std::complex<double>& get_Vd(int i, int k) const { return Vd(i,k); }
   const Eigen::Matrix<std::complex<double>,3,3>& get_Ud() const { return Ud; }
   const std::complex<double>& get_Ud(int i, int k) const { return Ud(i,k); }
   const Eigen::Matrix<std::complex<double>,3,3>& get_Vu() const { return Vu; }
   const std::complex<double>& get_Vu(int i, int k) const { return Vu(i,k); }
   const Eigen::Matrix<std::complex<double>,3,3>& get_Uu() const { return Uu; }
   const std::complex<double>& get_Uu(int i, int k) const { return Uu(i,k); }
   const Eigen::Matrix<std::complex<double>,3,3>& get_Ve() const { return Ve; }
   const std::complex<double>& get_Ve(int i, int k) const { return Ve(i,k); }
   const Eigen::Matrix<std::complex<double>,3,3>& get_Ue() const { return Ue; }
   const std::complex<double>& get_Ue(int i, int k) const { return Ue(i,k); }
   const Eigen::Matrix<double,2,2>& get_ZZ() const { return ZZ; }
   double get_ZZ(int i, int k) const { return ZZ(i,k); }


   double get_mass_matrix_VG() const;
   void calculate_MVG();
   Eigen::Matrix<double,3,3> get_mass_matrix_Fv() const;
   void calculate_MFv();
   Eigen::Matrix<double,2,2> get_mass_matrix_hh() const;
   void calculate_Mhh();
   Eigen::Matrix<double,2,2> get_mass_matrix_Ah() const;
   void calculate_MAh();
   Eigen::Matrix<double,2,2> get_mass_matrix_Hm() const;
   void calculate_MHm();
   Eigen::Matrix<double,3,3> get_mass_matrix_Fd() const;
   void calculate_MFd();
   Eigen::Matrix<double,3,3> get_mass_matrix_Fu() const;
   void calculate_MFu();
   Eigen::Matrix<double,3,3> get_mass_matrix_Fe() const;
   void calculate_MFe();
   double get_mass_matrix_VWm() const;
   void calculate_MVWm();
   Eigen::Matrix<double,2,2> get_mass_matrix_VPVZ() const;
   void calculate_MVPVZ();

   double get_ewsb_eq_hh_1() const;
   double get_ewsb_eq_hh_2() const;

   std::complex<double> CpUhhVZVZ(unsigned gO2) const;
   std::complex<double> CpUhhconjVWmVWm(unsigned gO2) const;
   std::complex<double> CpUhhbargWmgWm(unsigned gO1) const;
   std::complex<double> CpUhhbargWmCgWmC(unsigned gO1) const;
   std::complex<double> CpUhhbargZgZ(unsigned gO1) const;
   std::complex<double> CpUhhUhhconjVWmVWm(unsigned gO1, unsigned gO2) const;
   std::complex<double> CpUhhUhhVZVZ(unsigned gO1, unsigned gO2) const;
   std::complex<double> CpUhhUhhAhAh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUhhUhhconjHmHm(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUhhUhhhhhh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUhhAhAh(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUhhconjHmHm(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUhhhhAh(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUhhhhhh(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUhhbarFuFdPR(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUhhbarFuFdPL(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUhhbarFvFePR(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpUhhbarFvFePL(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpUhhVZAh(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpUhhconjVWmHm(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpUAhbargWmgWm(unsigned gO1) const;
   std::complex<double> CpUAhbargWmCgWmC(unsigned gO1) const;
   std::complex<double> CpUAhUAhconjVWmVWm(unsigned gO1, unsigned gO2) const;
   std::complex<double> CpUAhUAhVZVZ(unsigned gO1, unsigned gO2) const;
   std::complex<double> CpUAhUAhAhAh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUAhUAhconjHmHm(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUAhUAhhhhh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUAhAhAh(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUAhconjHmHm(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUAhhhAh(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUAhhhhh(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUAhbarFuFdPR(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUAhbarFuFdPL(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUAhbarFvFePR(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpUAhbarFvFePL(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpUAhVZhh(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpUAhconjVWmHm(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpconjUHmVWmVP(unsigned gO2) const;
   std::complex<double> CpconjUHmVZVWm(unsigned gO2) const;
   std::complex<double> CpconjUHmbargWmCgZ(unsigned gO1) const;
   std::complex<double> CpUHmgWmCbargZ(unsigned gO2) const;
   std::complex<double> CpconjUHmbargZgWm(unsigned gO1) const;
   std::complex<double> CpUHmgZbargWm(unsigned gO2) const;
   std::complex<double> CpUHmconjUHmconjVWmVWm(unsigned gO1, unsigned gO2) const;
   std::complex<double> CpUHmconjUHmVZVZ(unsigned gO1, unsigned gO2) const;
   std::complex<double> CpUHmconjUHmAhAh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUHmconjUHmconjHmHm(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpUHmconjUHmhhhh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpconjUHmHmAh(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpconjUHmHmhh(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpconjUHmbarFdFdPR(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpconjUHmbarFdFdPL(unsigned gO1, unsigned gI1, unsigned gI2) const;
   double CpconjUHmbarFeFePR(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpconjUHmbarFeFePL(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpconjUHmbarFuFuPR(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpconjUHmbarFuFuPL(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpconjUHmVWmAh(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpconjUHmVWmhh(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpconjUHmVPHm(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpconjUHmVZHm(unsigned gO2, unsigned gI2) const;
   double CpVZbargWmgWm() const;
   double CpVZbargWmCgWmC() const;
   double CpVZconjVWmVWm() const;
   std::complex<double> CpVZVZAhAh(unsigned gI1, unsigned gI2) const;
   std::complex<double> CpVZVZconjHmHm(unsigned gI1, unsigned gI2) const;
   std::complex<double> CpVZVZhhhh(unsigned gI1, unsigned gI2) const;
   double CpVZconjHmHm(unsigned gI1, unsigned gI2) const;
   std::complex<double> CpVZhhAh(unsigned gI1, unsigned gI2) const;
   double CpVZbarFdFdPL(unsigned gI1, unsigned gI2) const;
   double CpVZbarFdFdPR(unsigned gI1, unsigned gI2) const;
   double CpVZbarFeFePL(unsigned gI1, unsigned gI2) const;
   double CpVZbarFeFePR(unsigned gI1, unsigned gI2) const;
   double CpVZbarFuFuPL(unsigned gI1, unsigned gI2) const;
   double CpVZbarFuFuPR(unsigned gI1, unsigned gI2) const;
   double CpVZbarFvFvPL(unsigned gI1, unsigned gI2) const;
   double CpVZbarFvFvPR(unsigned , unsigned ) const;
   std::complex<double> CpVZVZhh(unsigned gI2) const;
   std::complex<double> CpVZconjVWmHm(unsigned gI2) const;
   double CpVZVZconjVWmVWm1() const;
   double CpVZVZconjVWmVWm2() const;
   double CpVZVZconjVWmVWm3() const;
   double CpconjVWmbargPgWm() const;
   double CpconjVWmbargWmCgP() const;
   double CpconjVWmbargWmCgZ() const;
   double CpconjVWmbargZgWm() const;
   double CpconjVWmVWmVP() const;
   double CpconjVWmVZVWm() const;
   std::complex<double> CpVWmconjVWmAhAh(unsigned gI1, unsigned gI2) const;
   std::complex<double> CpVWmconjVWmconjHmHm(unsigned gI1, unsigned gI2) const;
   std::complex<double> CpVWmconjVWmhhhh(unsigned gI1, unsigned gI2) const;
   std::complex<double> CpconjVWmHmAh(unsigned gI1, unsigned gI2) const;
   std::complex<double> CpconjVWmHmhh(unsigned gI1, unsigned gI2) const;
   std::complex<double> CpconjVWmbarFuFdPL(unsigned gI1, unsigned gI2) const;
   double CpconjVWmbarFuFdPR(unsigned , unsigned ) const;
   std::complex<double> CpconjVWmbarFvFePL(unsigned gI1, unsigned gI2) const;
   double CpconjVWmbarFvFePR(unsigned , unsigned ) const;
   std::complex<double> CpconjVWmVPHm(unsigned gI2) const;
   std::complex<double> CpconjVWmVWmhh(unsigned gI2) const;
   std::complex<double> CpconjVWmVZHm(unsigned gI2) const;
   double CpVWmconjVWmVPVP1() const;
   double CpVWmconjVWmVPVP2() const;
   double CpVWmconjVWmVPVP3() const;
   double CpVWmconjVWmVZVZ1() const;
   double CpVWmconjVWmVZVZ2() const;
   double CpVWmconjVWmVZVZ3() const;
   double CpVWmconjVWmconjVWmVWm1() const;
   double CpVWmconjVWmconjVWmVWm2() const;
   double CpVWmconjVWmconjVWmVWm3() const;
   std::complex<double> CpbarUFdconjHmFdPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpbarUFdconjHmFdPR(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpbarUFdhhFuPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarUFdhhFuPR(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarUFdFuAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarUFdFuAhPR(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarUFdVGFdPR(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpbarUFdVGFdPL(unsigned gO1, unsigned gI2) const;
   std::complex<double> CpbarUFdVPFdPR(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpbarUFdVPFdPL(unsigned gO1, unsigned gI2) const;
   double CpbarUFdVWmFuPR(unsigned , unsigned ) const;
   std::complex<double> CpbarUFdVWmFuPL(unsigned gO1, unsigned gI2) const;
   std::complex<double> CpbarUFdVZFdPR(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpbarUFdVZFdPL(unsigned gO1, unsigned gI2) const;
   double CpbarUFuconjHmFuPL(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpbarUFuconjHmFuPR(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarUFuhhFdPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarUFuhhFdPR(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarUFuFdAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarUFuFdAhPR(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarUFuVGFuPR(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpbarUFuVGFuPL(unsigned gO1, unsigned gI2) const;
   std::complex<double> CpbarUFuVPFuPR(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpbarUFuVPFuPL(unsigned gO1, unsigned gI2) const;
   std::complex<double> CpbarUFuVZFuPR(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpbarUFuVZFuPL(unsigned gO1, unsigned gI2) const;
   double CpbarUFuconjVWmFdPR(unsigned , unsigned ) const;
   std::complex<double> CpbarUFuconjVWmFdPL(unsigned gO1, unsigned gI2) const;
   std::complex<double> CpbarUFeconjHmFePL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpbarUFeconjHmFePR(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpbarUFehhFvPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpbarUFehhFvPR(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpbarUFeFvAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpbarUFeFvAhPR(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpbarUFeVPFePR(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpbarUFeVPFePL(unsigned gO1, unsigned gI2) const;
   double CpbarUFeVWmFvPR(unsigned , unsigned ) const;
   double CpbarUFeVWmFvPL(unsigned gO1, unsigned gI2) const;
   std::complex<double> CpbarUFeVZFePR(unsigned gO2, unsigned gI2) const;
   std::complex<double> CpbarUFeVZFePL(unsigned gO1, unsigned gI2) const;
   std::complex<double> CpbarFdconjHmFdPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpbarFdconjHmFdPR(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpbarFdhhFuPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarFdhhFuPR(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarFdFuAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarFdFuAhPR(unsigned gO1, unsigned gI1, unsigned gI2) const;
   double CpbarFdVWmFuPR(unsigned , unsigned ) const;
   std::complex<double> CpbarFdVWmFuPL(unsigned gO1, unsigned gI2) const;
   double CpbarFdVZFdPR(unsigned gO2, unsigned gI2) const;
   double CpbarFdVZFdPL(unsigned gO1, unsigned gI2) const;
   std::complex<double> CpbarFeconjHmFePL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpbarFeconjHmFePR(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpbarFehhFvPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpbarFehhFvPR(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpbarFeFvAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   double CpbarFeFvAhPR(unsigned , unsigned , unsigned ) const;
   double CpbarFeVWmFvPR(unsigned , unsigned ) const;
   std::complex<double> CpbarFeVWmFvPL(unsigned gO1, unsigned gI2) const;
   double CpbarFeVZFePR(unsigned gO2, unsigned gI2) const;
   double CpbarFeVZFePL(unsigned gO1, unsigned gI2) const;
   double CpbarFuconjHmFuPL(unsigned , unsigned , unsigned ) const;
   std::complex<double> CpbarFuconjHmFuPR(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarFuhhFdPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarFuhhFdPR(unsigned gO1, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarFuFdAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const;
   std::complex<double> CpbarFuFdAhPR(unsigned gO1, unsigned gI1, unsigned gI2) const;
   double CpbarFuVPFuPR(unsigned gO2, unsigned gI2) const;
   double CpbarFuVPFuPL(unsigned gO1, unsigned gI2) const;
   double CpbarFuVZFuPR(unsigned gO2, unsigned gI2) const;
   double CpbarFuVZFuPL(unsigned gO1, unsigned gI2) const;
   double CpbarFuconjVWmFdPR(unsigned , unsigned ) const;
   std::complex<double> CpbarFuconjVWmFdPL(unsigned gO1, unsigned gI2) const;
   std::complex<double> self_energy_hh(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Ah(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Hm(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_VZ(double p ) const;
   std::complex<double> self_energy_VWm(double p ) const;
   std::complex<double> self_energy_Fd_1(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fd_PR(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fd_PL(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fu_1(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fu_PR(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fu_PL(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fe_1(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fe_PR(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fe_PL(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_VZ_heavy(double p ) const;
   std::complex<double> self_energy_VWm_heavy(double p ) const;
   std::complex<double> self_energy_Fd_1_heavy_rotated(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fd_PR_heavy_rotated(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fd_PL_heavy_rotated(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fe_1_heavy_rotated(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fe_PR_heavy_rotated(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fe_PL_heavy_rotated(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fu_1_heavy_rotated(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fu_PR_heavy_rotated(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fu_PL_heavy_rotated(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fu_1_heavy(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fu_PR_heavy(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> self_energy_Fu_PL_heavy(double p , unsigned gO1, unsigned gO2) const;
   std::complex<double> tadpole_hh(unsigned gO1) const;


   /// calculates the tadpoles at current loop order
   void tadpole_equations(double[number_of_ewsb_equations]) const;





   void calculate_MVG_pole();
   void calculate_MFv_pole();
   void calculate_MVP_pole();
   void calculate_MVZ_pole();
   void calculate_Mhh_pole();
   void calculate_MAh_pole();
   void calculate_MHm_pole();
   void calculate_MFd_pole();
   void calculate_MFu_pole();
   void calculate_MFe_pole();
   void calculate_MVWm_pole();
   double calculate_MVWm_pole(double);
   double calculate_MVZ_pole(double);

   double calculate_MFv_DRbar(double, int) const;
   double calculate_MFe_DRbar(double, int) const;
   double calculate_MFu_DRbar(double, int) const;
   double calculate_MFd_DRbar(double, int) const;
   double calculate_MVP_DRbar(double);
   double calculate_MVZ_DRbar(double);
   double calculate_MVWm_DRbar(double);

   double Betax() const;
   double Alpha() const;
   double ThetaW() const;


private:
   struct EWSB_args {
      THDM_II_mass_eigenstates* model;
      unsigned ewsb_loop_order;
   };

#ifdef ENABLE_THREADS
   struct Thread {
      typedef void(THDM_II_mass_eigenstates::*Memfun_t)();
      THDM_II_mass_eigenstates* model;
      Memfun_t fun;

      Thread(THDM_II_mass_eigenstates* model_, Memfun_t fun_)
         : model(model_), fun(fun_) {}
      void operator()() {
         try {
            (model->*fun)();
         } catch (...) {
            model->thread_exception = std::current_exception();
         }
      }
   };
#endif

   std::size_t number_of_ewsb_iterations;
   std::size_t number_of_mass_iterations;
   unsigned ewsb_loop_order;
   unsigned pole_mass_loop_order;
   bool calculate_sm_pole_masses; ///< switch to calculate the pole masses of the Standard Model particles
   bool force_output;             ///< switch to force output of pole masses
   double precision;              ///< RG running precision
   double ewsb_iteration_precision;
   THDM_II_physical physical; ///< contains the pole masses and mixings
   Problems<THDM_II_info::NUMBER_OF_PARTICLES> problems;
   Two_loop_corrections two_loop_corrections; ///< used 2-loop corrections
#ifdef ENABLE_THREADS
   std::exception_ptr thread_exception;
   static std::mutex mtx_fortran; /// locks fortran functions
#endif

   int solve_ewsb_iteratively();
   int solve_ewsb_iteratively(unsigned);
   int solve_ewsb_iteratively_with(EWSB_solver*, const double[number_of_ewsb_equations]);
   int solve_ewsb_tree_level_custom();
   void ewsb_initial_guess(double[number_of_ewsb_equations]);
   int ewsb_step(double[number_of_ewsb_equations]) const;
   static int ewsb_step(const gsl_vector*, void*, gsl_vector*);
   static int tadpole_equations(const gsl_vector*, void*, gsl_vector*);
   void copy_DRbar_masses_to_pole_masses();

   // Passarino-Veltman loop functions
   double A0(double) const;
   double B0(double, double, double) const;
   double B1(double, double, double) const;
   double B00(double, double, double) const;
   double B22(double, double, double) const;
   double H0(double, double, double) const;
   double F0(double, double, double) const;
   double G0(double, double, double) const;

   // DR-bar masses
   double MVG;
   Eigen::Array<double,3,1> MFv;
   Eigen::Array<double,2,1> Mhh;
   Eigen::Array<double,2,1> MAh;
   Eigen::Array<double,2,1> MHm;
   Eigen::Array<double,3,1> MFd;
   Eigen::Array<double,3,1> MFu;
   Eigen::Array<double,3,1> MFe;
   double MVWm;
   double MVP;
   double MVZ;

   // DR-bar mixing matrices
   Eigen::Matrix<double,2,2> ZH;
   Eigen::Matrix<double,2,2> ZA;
   Eigen::Matrix<double,2,2> ZP;
   Eigen::Matrix<std::complex<double>,3,3> Vd;
   Eigen::Matrix<std::complex<double>,3,3> Ud;
   Eigen::Matrix<std::complex<double>,3,3> Vu;
   Eigen::Matrix<std::complex<double>,3,3> Uu;
   Eigen::Matrix<std::complex<double>,3,3> Ve;
   Eigen::Matrix<std::complex<double>,3,3> Ue;
   Eigen::Matrix<double,2,2> ZZ;

   // phases

};

std::ostream& operator<<(std::ostream&, const THDM_II_mass_eigenstates&);

} // namespace flexiblesusy

#endif
