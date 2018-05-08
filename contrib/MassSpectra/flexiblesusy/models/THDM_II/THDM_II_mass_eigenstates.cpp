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
 * @file THDM_II_mass_eigenstates.cpp
 * @brief implementation of the THDM_II model class
 *
 * Contains the definition of the THDM_II model class methods
 * which solve EWSB and calculate pole masses and mixings from DRbar
 * parameters.
 *
 * This file was generated at Wed 29 Mar 2017 15:37:10 with FlexibleSUSY
 * 1.5.1 (git commit: unknown) and SARAH 4.9.0 .
 */

#include "THDM_II_mass_eigenstates.hpp"
#include "eigen_utils.hpp"
#include "wrappers.hpp"
#include "linalg2.hpp"
#include "numerics2.hpp"
#include "logger.hpp"
#include "error.hpp"
#include "root_finder.hpp"
#include "fixed_point_iterator.hpp"
#include "gsl_utils.hpp"
#include "config.h"
#include "pv.hpp"
#include "functors.hpp"




#include <cmath>
#include <iostream>
#include <algorithm>

#ifdef ENABLE_THREADS
#include <thread>
#endif

#include <gsl/gsl_multiroots.h>

namespace flexiblesusy {

using namespace THDM_II_info;

#define CLASSNAME THDM_II_mass_eigenstates

#define PHYSICAL(parameter) physical.parameter
#define INPUT(parameter) model->get_input().parameter
#define LOCALINPUT(parameter) input.parameter
#define MODELPARAMETER(parameter) model->get_##parameter()

#define HIGGS_2LOOP_CORRECTION_AT_AS     two_loop_corrections.higgs_at_as
#define HIGGS_2LOOP_CORRECTION_AB_AS     two_loop_corrections.higgs_ab_as
#define HIGGS_2LOOP_CORRECTION_AT_AT     two_loop_corrections.higgs_at_at
#define HIGGS_2LOOP_CORRECTION_ATAU_ATAU two_loop_corrections.higgs_atau_atau
#define TOP_2LOOP_CORRECTION_QCD         two_loop_corrections.top_qcd
#define HIGGS_3LOOP_CORRECTION_AT_AS_AS  1

#ifdef ENABLE_THREADS
   std::mutex CLASSNAME::mtx_fortran;
   #define LOCK_MUTEX() mtx_fortran.lock()
   #define UNLOCK_MUTEX() mtx_fortran.unlock()
#else
   #define LOCK_MUTEX()
   #define UNLOCK_MUTEX()
#endif

CLASSNAME::THDM_II_mass_eigenstates(const THDM_II_input_parameters& input_)
   : THDM_II_soft_parameters(input_)
   , number_of_ewsb_iterations(100)
   , number_of_mass_iterations(20)
   , ewsb_loop_order(2)
   , pole_mass_loop_order(2)
   , calculate_sm_pole_masses(false)
   , force_output(false)
   , precision(1.0e-3)
   , ewsb_iteration_precision(1.0e-5)
   , physical()
   , problems(THDM_II_info::particle_names)
   , two_loop_corrections()
#ifdef ENABLE_THREADS
   , thread_exception()
#endif
   , MVG(0), MFv(Eigen::Array<double,3,1>::Zero()), Mhh(Eigen::Array<double,2,1
      >::Zero()), MAh(Eigen::Array<double,2,1>::Zero()), MHm(Eigen::Array<double,2
      ,1>::Zero()), MFd(Eigen::Array<double,3,1>::Zero()), MFu(Eigen::Array<double
      ,3,1>::Zero()), MFe(Eigen::Array<double,3,1>::Zero()), MVWm(0), MVP(0), MVZ(
      0)

   , ZH(Eigen::Matrix<double,2,2>::Zero()), ZA(Eigen::Matrix<double,2,2>::Zero(
      )), ZP(Eigen::Matrix<double,2,2>::Zero()), Vd(Eigen::Matrix<std::complex<
      double>,3,3>::Zero()), Ud(Eigen::Matrix<std::complex<double>,3,3>::Zero()),
      Vu(Eigen::Matrix<std::complex<double>,3,3>::Zero()), Uu(Eigen::Matrix<
      std::complex<double>,3,3>::Zero()), Ve(Eigen::Matrix<std::complex<double>,3,
      3>::Zero()), Ue(Eigen::Matrix<std::complex<double>,3,3>::Zero()), ZZ(
      Eigen::Matrix<double,2,2>::Zero())


{
}

CLASSNAME::~THDM_II_mass_eigenstates()
{
}

void CLASSNAME::do_calculate_sm_pole_masses(bool flag)
{
   calculate_sm_pole_masses = flag;
}

bool CLASSNAME::do_calculate_sm_pole_masses() const
{
   return calculate_sm_pole_masses;
}

void CLASSNAME::do_force_output(bool flag)
{
   force_output = flag;
}

bool CLASSNAME::do_force_output() const
{
   return force_output;
}

void CLASSNAME::set_ewsb_loop_order(unsigned loop_order)
{
   ewsb_loop_order = loop_order;
}

void CLASSNAME::set_two_loop_corrections(const Two_loop_corrections& two_loop_corrections_)
{
   two_loop_corrections = two_loop_corrections_;
}

const Two_loop_corrections& CLASSNAME::get_two_loop_corrections() const
{
   return two_loop_corrections;
}

void CLASSNAME::set_number_of_ewsb_iterations(std::size_t iterations)
{
   number_of_ewsb_iterations = iterations;
}

std::size_t CLASSNAME::get_number_of_ewsb_iterations() const
{
   return number_of_ewsb_iterations;
}

void CLASSNAME::set_number_of_mass_iterations(std::size_t iterations)
{
   number_of_mass_iterations = iterations;
}

std::size_t CLASSNAME::get_number_of_mass_iterations() const
{
   return number_of_mass_iterations;
}

void CLASSNAME::set_precision(double precision_)
{
   precision = precision_;
   ewsb_iteration_precision = precision_;
}

void CLASSNAME::set_pole_mass_loop_order(unsigned loop_order)
{
   pole_mass_loop_order = loop_order;
}

unsigned CLASSNAME::get_pole_mass_loop_order() const
{
   return pole_mass_loop_order;
}

void CLASSNAME::set_ewsb_iteration_precision(double precision)
{
   ewsb_iteration_precision = precision;
}

double CLASSNAME::get_ewsb_iteration_precision() const
{
   return ewsb_iteration_precision;
}

double CLASSNAME::get_precision() const
{
   return precision;
}

double CLASSNAME::get_ewsb_loop_order() const
{
   return ewsb_loop_order;
}

const THDM_II_physical& CLASSNAME::get_physical() const
{
   return physical;
}

THDM_II_physical& CLASSNAME::get_physical()
{
   return physical;
}

void CLASSNAME::set_physical(const THDM_II_physical& physical_)
{
   physical = physical_;
}

const Problems<THDM_II_info::NUMBER_OF_PARTICLES>& CLASSNAME::get_problems() const
{
   return problems;
}

Problems<THDM_II_info::NUMBER_OF_PARTICLES>& CLASSNAME::get_problems()
{
   return problems;
}

/**
 * Method which calculates the tadpoles at the current loop order.
 *
 * @param tadpole array of tadpole
 */
void CLASSNAME::tadpole_equations(double tadpole[number_of_ewsb_equations]) const
{
   tadpole[0] = get_ewsb_eq_hh_1();
   tadpole[1] = get_ewsb_eq_hh_2();

   if (ewsb_loop_order > 0) {
      tadpole[0] -= Re(tadpole_hh(0));
      tadpole[1] -= Re(tadpole_hh(1));

      if (ewsb_loop_order > 1) {

      }
   }
}

/**
 * Method which calculates the tadpoles at loop order specified in the
 * pointer to the CLASSNAME::EWSB_args struct.
 *
 * @param x GSL vector of EWSB output parameters
 * @param params pointer to CLASSNAME::EWSB_args struct
 * @param f GSL vector with tadpoles
 *
 * @return GSL_EDOM if x contains Nans, GSL_SUCCESS otherwise.
 */
int CLASSNAME::tadpole_equations(const gsl_vector* x, void* params, gsl_vector* f)
{
   if (!is_finite(x)) {
      gsl_vector_set_all(f, std::numeric_limits<double>::max());
      return GSL_EDOM;
   }

   const CLASSNAME::EWSB_args* ewsb_args
      = static_cast<CLASSNAME::EWSB_args*>(params);
   THDM_II_mass_eigenstates* model = ewsb_args->model;
   const unsigned ewsb_loop_order = ewsb_args->ewsb_loop_order;

   model->set_M112(gsl_vector_get(x, 0));
   model->set_M222(gsl_vector_get(x, 1));


   if (ewsb_loop_order > 0)
      model->calculate_DRbar_masses();

   double tadpole[number_of_ewsb_equations] = { 0. };

   model->tadpole_equations(tadpole);

   for (std::size_t i = 0; i < number_of_ewsb_equations; ++i)
      gsl_vector_set(f, i, tadpole[i]);

   return is_finite<number_of_ewsb_equations>(tadpole) ? GSL_SUCCESS : GSL_EDOM;
}

/**
 * This method solves the EWSB conditions iteratively, trying several
 * root finding methods until a solution is found.
 */
int CLASSNAME::solve_ewsb_iteratively()
{
   EWSB_args params = {this, ewsb_loop_order};

   EWSB_solver* solvers[] = {
      new Fixed_point_iterator<number_of_ewsb_equations, fixed_point_iterator::Convergence_tester_relative>(CLASSNAME::ewsb_step, &params, number_of_ewsb_iterations, ewsb_iteration_precision),
      new Root_finder<number_of_ewsb_equations>(CLASSNAME::tadpole_equations, &params, number_of_ewsb_iterations, ewsb_iteration_precision, gsl_multiroot_fsolver_hybrids),
      new Root_finder<number_of_ewsb_equations>(CLASSNAME::tadpole_equations, &params, number_of_ewsb_iterations, ewsb_iteration_precision, gsl_multiroot_fsolver_broyden)
   };

   const std::size_t number_of_solvers = sizeof(solvers)/sizeof(*solvers);
   double x_init[number_of_ewsb_equations] = { 0. };
   ewsb_initial_guess(x_init);

#ifdef ENABLE_VERBOSE
   std::cout << "Solving EWSB equations ...\n"
      "\tInitial guess: x_init =";
   for (std::size_t i = 0; i < number_of_ewsb_equations; ++i)
      std::cout << ' ' << x_init[i];
   std::cout << '\n';
#endif

   int status;
   for (std::size_t i = 0; i < number_of_solvers; ++i) {
      VERBOSE_MSG("\tStarting EWSB iteration using solver " << i);
      status = solve_ewsb_iteratively_with(solvers[i], x_init);
      if (status == EWSB_solver::SUCCESS) {
         VERBOSE_MSG("\tSolver " << i << " finished successfully!");
         break;
      }
#ifdef ENABLE_VERBOSE
      else {
         WARNING("\tSolver " << i << " could not find a solution!"
                 " (requested precision: " << ewsb_iteration_precision << ")");
      }
#endif
   }

   if (status == EWSB_solver::SUCCESS) {
      problems.unflag_no_ewsb();
   } else {
      problems.flag_no_ewsb();
#ifdef ENABLE_VERBOSE
      WARNING("\tCould not find a solution to the EWSB equations!"
              " (requested precision: " << ewsb_iteration_precision << ")");
#endif
   }

   std::for_each(solvers, solvers + number_of_solvers, Delete_object());

   return status;
}

/**
 * Solves EWSB equations with given EWSB solver
 *
 * @param solver EWSB solver
 * @param x_init initial values
 *
 * @return status of the EWSB solver
 */
int CLASSNAME::solve_ewsb_iteratively_with(
   EWSB_solver* solver,
   const double x_init[number_of_ewsb_equations]
)
{
   const int status = solver->solve(x_init);

   M112 = solver->get_solution(0);
   M222 = solver->get_solution(1);


   return status;
}

int CLASSNAME::solve_ewsb_iteratively(unsigned loop_order)
{
   // temporarily set `ewsb_loop_order' to `loop_order' and do
   // iteration
   const unsigned old_loop_order = ewsb_loop_order;
   ewsb_loop_order = loop_order;
   const int status = solve_ewsb_iteratively();
   ewsb_loop_order = old_loop_order;
   return status;
}


int CLASSNAME::solve_ewsb_tree_level()
{
   int error = 0;

   const double old_M112 = M112;
   const double old_M222 = M222;

   M112 = Re((0.25*(-2*Lambda1*Power(v1,3) + 2*M122*v2 - Lambda7*Power(v2,3) -
      Power(v2,3)*Conj(Lambda7) + 2*v2*Conj(M122) - 3*Lambda6*v2*Sqr(v1) - 3*v2*
      Conj(Lambda6)*Sqr(v1) - 2*Lambda3*v1*Sqr(v2) - 2*Lambda4*v1*Sqr(v2) -
      Lambda5*v1*Sqr(v2) - v1*Conj(Lambda5)*Sqr(v2)))/v1);
   M222 = Re((0.25*(2*M122*v1 - Lambda6*Power(v1,3) - 2*Lambda2*Power(v2,3) -
      Power(v1,3)*Conj(Lambda6) + 2*v1*Conj(M122) - 2*Lambda3*v2*Sqr(v1) - 2*
      Lambda4*v2*Sqr(v1) - Lambda5*v2*Sqr(v1) - v2*Conj(Lambda5)*Sqr(v1) - 3*
      Lambda7*v1*Sqr(v2) - 3*v1*Conj(Lambda7)*Sqr(v2)))/v2);

   const bool is_finite = IsFinite(M112) && IsFinite(M222);

   if (!is_finite) {
      M112 = old_M112;
      M222 = old_M222;
      error = 1;
   }


   return error;
}

int CLASSNAME::solve_ewsb_tree_level_custom()
{
   int error = 0;



   return error;
}

int CLASSNAME::solve_ewsb_one_loop()
{
   return solve_ewsb_iteratively(1);
}

int CLASSNAME::solve_ewsb()
{
   VERBOSE_MSG("\tSolving EWSB at " << ewsb_loop_order << "-loop order");

   if (ewsb_loop_order == 0)
      return solve_ewsb_tree_level();

   return solve_ewsb_iteratively(ewsb_loop_order);
}

void CLASSNAME::ewsb_initial_guess(double x_init[number_of_ewsb_equations])
{
   x_init[0] = M112;
   x_init[1] = M222;

}

/**
 * Calculates EWSB output parameters including loop-corrections.
 *
 * @param ewsb_parameters new EWSB output parameters.  \a
 * ewsb_parameters is only modified if all new parameters are finite.
 *
 * @return GSL_SUCCESS if new EWSB output parameters are finite,
 * GSL_EDOM otherwise.
 */
int CLASSNAME::ewsb_step(double ewsb_parameters[number_of_ewsb_equations]) const
{
   int error;
   double tadpole[number_of_ewsb_equations] = { 0. };

   if (ewsb_loop_order > 0) {
      tadpole[0] += Re(tadpole_hh(0));
      tadpole[1] += Re(tadpole_hh(1));

      if (ewsb_loop_order > 1) {

      }
   }

   double M112;
   double M222;

   M112 = Re((0.25*(-2*Lambda1*Power(v1,3) + 2*M122*v2 - Lambda7*Power(v2,3) -
      Power(v2,3)*Conj(Lambda7) + 2*v2*Conj(M122) + 4*tadpole[0] - 3*Lambda6*v2*
      Sqr(v1) - 3*v2*Conj(Lambda6)*Sqr(v1) - 2*Lambda3*v1*Sqr(v2) - 2*Lambda4*v1*
      Sqr(v2) - Lambda5*v1*Sqr(v2) - v1*Conj(Lambda5)*Sqr(v2)))/v1);
   M222 = Re((0.25*(2*M122*v1 - Lambda6*Power(v1,3) - 2*Lambda2*Power(v2,3) -
      Power(v1,3)*Conj(Lambda6) + 2*v1*Conj(M122) + 4*tadpole[1] - 2*Lambda3*v2*
      Sqr(v1) - 2*Lambda4*v2*Sqr(v1) - Lambda5*v2*Sqr(v1) - v2*Conj(Lambda5)*Sqr(
      v1) - 3*Lambda7*v1*Sqr(v2) - 3*v1*Conj(Lambda7)*Sqr(v2)))/v2);

   const bool is_finite = IsFinite(M112) && IsFinite(M222);


   if (is_finite) {
      error = GSL_SUCCESS;
      ewsb_parameters[0] = M112;
      ewsb_parameters[1] = M222;

   } else {
      error = GSL_EDOM;
   }

   return error;
}

/**
 * Calculates EWSB output parameters including loop-corrections.
 *
 * @param x old EWSB output parameters
 * @param params further function parameters
 * @param f new EWSB output parameters
 *
 * @return Returns status of CLASSNAME::ewsb_step
 */
int CLASSNAME::ewsb_step(const gsl_vector* x, void* params, gsl_vector* f)
{
   if (!is_finite(x)) {
      gsl_vector_set_all(f, std::numeric_limits<double>::max());
      return GSL_EDOM;
   }

   const CLASSNAME::EWSB_args* ewsb_args
      = static_cast<CLASSNAME::EWSB_args*>(params);
   THDM_II_mass_eigenstates* model = ewsb_args->model;
   const unsigned ewsb_loop_order = ewsb_args->ewsb_loop_order;

   const double M112 = gsl_vector_get(x, 0);
   const double M222 = gsl_vector_get(x, 1);

   model->set_M112(M112);
   model->set_M222(M222);


   if (ewsb_loop_order > 0)
      model->calculate_DRbar_masses();

   double ewsb_parameters[number_of_ewsb_equations] =
      { M112, M222 };

   const int status = model->ewsb_step(ewsb_parameters);

   for (std::size_t i = 0; i < number_of_ewsb_equations; ++i)
      gsl_vector_set(f, i, ewsb_parameters[i]);

   return status;
}

void CLASSNAME::print(std::ostream& ostr) const
{
   ostr << "========================================\n"
           "THDM_II\n"
           "========================================\n";
   THDM_II_soft_parameters::print(ostr);
   ostr << "----------------------------------------\n"
           "tree-level DRbar masses:\n"
           "----------------------------------------\n";
   ostr << "MVG = " << MVG << '\n';
   ostr << "MFv = " << MFv.transpose() << '\n';
   ostr << "Mhh = " << Mhh.transpose() << '\n';
   ostr << "MAh = " << MAh.transpose() << '\n';
   ostr << "MHm = " << MHm.transpose() << '\n';
   ostr << "MFd = " << MFd.transpose() << '\n';
   ostr << "MFu = " << MFu.transpose() << '\n';
   ostr << "MFe = " << MFe.transpose() << '\n';
   ostr << "MVWm = " << MVWm << '\n';

   ostr << "----------------------------------------\n"
           "tree-level DRbar mixing matrices:\n"
           "----------------------------------------\n";
   ostr << "ZH = " << ZH << '\n';
   ostr << "ZA = " << ZA << '\n';
   ostr << "ZP = " << ZP << '\n';
   ostr << "Vd = " << Vd << '\n';
   ostr << "Ud = " << Ud << '\n';
   ostr << "Vu = " << Vu << '\n';
   ostr << "Uu = " << Uu << '\n';
   ostr << "Ve = " << Ve << '\n';
   ostr << "Ue = " << Ue << '\n';
   ostr << "ZZ = " << ZZ << '\n';

   physical.print(ostr);
}

/**
 * wrapper routines for passarino Veltman functions
 */

double CLASSNAME::A0(double m) const
{
   return passarino_veltman::ReA0(m*m, Sqr(get_scale()));
}

double CLASSNAME::B0(double p, double m1, double m2) const
{
   return passarino_veltman::ReB0(p*p, m1*m1, m2*m2, Sqr(get_scale()));
}

double CLASSNAME::B1(double p, double m1, double m2) const
{
   return passarino_veltman::ReB1(p*p, m1*m1, m2*m2, Sqr(get_scale()));
}

double CLASSNAME::B00(double p, double m1, double m2) const
{
   return passarino_veltman::ReB00(p*p, m1*m1, m2*m2, Sqr(get_scale()));
}

double CLASSNAME::B22(double p, double m1, double m2) const
{
   return passarino_veltman::ReB22(p*p, m1*m1, m2*m2, Sqr(get_scale()));
}

double CLASSNAME::H0(double p, double m1, double m2) const
{
   return passarino_veltman::ReH0(p*p, m1*m1, m2*m2, Sqr(get_scale()));
}

double CLASSNAME::F0(double p, double m1, double m2) const
{
   return passarino_veltman::ReF0(p*p, m1*m1, m2*m2, Sqr(get_scale()));
}

double CLASSNAME::G0(double p, double m1, double m2) const
{
   return passarino_veltman::ReG0(p*p, m1*m1, m2*m2, Sqr(get_scale()));
}

/**
 * routine which finds the DRbar mass eigenstates and mixings.
 */
void CLASSNAME::calculate_DRbar_masses()
{
   const auto old_M112 = M112;
   const auto old_M222 = M222;

   solve_ewsb_tree_level();

   calculate_MVPVZ();
   calculate_MVWm();
   calculate_MFe();
   calculate_MFu();
   calculate_MFd();
   calculate_MHm();
   calculate_MAh();
   calculate_Mhh();
   calculate_MFv();
   calculate_MVG();

   M112 = old_M112;
   M222 = old_M222;

}

/**
 * Backward compatibility routine which finds the DRbar mass
 * eigenstates and mixings.
 */
void CLASSNAME::calculate_DRbar_parameters()
{
   calculate_DRbar_masses();
}

/**
 * routine which finds the pole mass eigenstates and mixings.
 */
void CLASSNAME::calculate_pole_masses()
{
#ifdef ENABLE_THREADS
   thread_exception = 0;

   std::thread thread_MAh(Thread(this, &CLASSNAME::calculate_MAh_pole));
   std::thread thread_Mhh(Thread(this, &CLASSNAME::calculate_Mhh_pole));
   std::thread thread_MHm(Thread(this, &CLASSNAME::calculate_MHm_pole));

   if (calculate_sm_pole_masses) {
      std::thread thread_MVG(Thread(this, &CLASSNAME::calculate_MVG_pole));
      std::thread thread_MFv(Thread(this, &CLASSNAME::calculate_MFv_pole));
      std::thread thread_MVP(Thread(this, &CLASSNAME::calculate_MVP_pole));
      std::thread thread_MVZ(Thread(this, &CLASSNAME::calculate_MVZ_pole));
      std::thread thread_MFd(Thread(this, &CLASSNAME::calculate_MFd_pole));
      std::thread thread_MFu(Thread(this, &CLASSNAME::calculate_MFu_pole));
      std::thread thread_MFe(Thread(this, &CLASSNAME::calculate_MFe_pole));
      std::thread thread_MVWm(Thread(this, &CLASSNAME::calculate_MVWm_pole));
      thread_MVG.join();
      thread_MFv.join();
      thread_MVP.join();
      thread_MVZ.join();
      thread_MFd.join();
      thread_MFu.join();
      thread_MFe.join();
      thread_MVWm.join();
   }

   thread_MAh.join();
   thread_Mhh.join();
   thread_MHm.join();


   if (thread_exception != 0)
      std::rethrow_exception(thread_exception);
#else
   calculate_MAh_pole();
   calculate_Mhh_pole();
   calculate_MHm_pole();

   if (calculate_sm_pole_masses) {
      calculate_MVG_pole();
      calculate_MFv_pole();
      calculate_MVP_pole();
      calculate_MVZ_pole();
      calculate_MFd_pole();
      calculate_MFu_pole();
      calculate_MFe_pole();
      calculate_MVWm_pole();
   }

#endif
}

void CLASSNAME::copy_DRbar_masses_to_pole_masses()
{
   PHYSICAL(MVG) = MVG;
   PHYSICAL(MFv) = MFv;
   PHYSICAL(Mhh) = Mhh;
   PHYSICAL(ZH) = ZH;
   PHYSICAL(MAh) = MAh;
   PHYSICAL(ZA) = ZA;
   PHYSICAL(MHm) = MHm;
   PHYSICAL(ZP) = ZP;
   PHYSICAL(MFd) = MFd;
   PHYSICAL(Vd) = Vd;
   PHYSICAL(Ud) = Ud;
   PHYSICAL(MFu) = MFu;
   PHYSICAL(Vu) = Vu;
   PHYSICAL(Uu) = Uu;
   PHYSICAL(MFe) = MFe;
   PHYSICAL(Ve) = Ve;
   PHYSICAL(Ue) = Ue;
   PHYSICAL(MVWm) = MVWm;
   PHYSICAL(MVP) = MVP;
   PHYSICAL(MVZ) = MVZ;

}

/**
 * reorders DRbar masses so that golstones are placed at the index
 * specified in the model files definition of the associated
 * gauge boson (see Z-boson definition in default particles.m file
 * in the Models directory of your SARAH distribution for example)
 */
void CLASSNAME::reorder_DRbar_masses()
{
   move_goldstone_to(0, MVZ, MAh, ZA);
   move_goldstone_to(0, MVWm, MHm, ZP);

}

/**
 * reorders pole masses so that golstones are placed at the index
 * specified in the model files definition of the associated
 * gauge boson (see Z-boson definition in default particles.m file
 * in the Models directory of your SARAH distribution for example)
 */
void CLASSNAME::reorder_pole_masses()
{
   move_goldstone_to(0, MVZ, PHYSICAL(MAh), PHYSICAL(ZA));
   move_goldstone_to(0, MVWm, PHYSICAL(MHm), PHYSICAL(ZP));

}

/**
 * Checks the pole masses for tachyons
 */
void CLASSNAME::check_pole_masses_for_tachyons()
{
   if (PHYSICAL(Mhh).tail<2>().minCoeff() < 0.) problems.flag_tachyon(hh);
   if (PHYSICAL(MAh).tail<1>().minCoeff() < 0.) problems.flag_tachyon(Ah);
   if (PHYSICAL(MHm).tail<1>().minCoeff() < 0.) problems.flag_tachyon(Hm);

}

/**
 * calculates spectrum for model once the DRbar parameters at
 * at low energies are known
 */
void CLASSNAME::calculate_spectrum()
{
   calculate_DRbar_masses();
   if (pole_mass_loop_order > 0)
      calculate_pole_masses();

   // move goldstone bosons to the front
   reorder_DRbar_masses();
   if (pole_mass_loop_order == 0)
      copy_DRbar_masses_to_pole_masses();
   else
      reorder_pole_masses();

   check_pole_masses_for_tachyons();

   if (problems.have_problem() && !force_output) {
      clear_DRbar_parameters();
      physical.clear();
   }
}

void CLASSNAME::clear_DRbar_parameters()
{
   MVG = 0.;
   MFv = Eigen::Matrix<double,3,1>::Zero();
   Mhh = Eigen::Matrix<double,2,1>::Zero();
   ZH = Eigen::Matrix<double,2,2>::Zero();
   MAh = Eigen::Matrix<double,2,1>::Zero();
   ZA = Eigen::Matrix<double,2,2>::Zero();
   MHm = Eigen::Matrix<double,2,1>::Zero();
   ZP = Eigen::Matrix<double,2,2>::Zero();
   MFd = Eigen::Matrix<double,3,1>::Zero();
   Vd = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   Ud = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFu = Eigen::Matrix<double,3,1>::Zero();
   Vu = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   Uu = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MFe = Eigen::Matrix<double,3,1>::Zero();
   Ve = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   Ue = Eigen::Matrix<std::complex<double>,3,3>::Zero();
   MVWm = 0.;
   MVP = 0.;
   MVZ = 0.;


}

void CLASSNAME::clear_problems()
{
   problems.unflag_all_tachyons();
}

void CLASSNAME::clear()
{
   THDM_II_soft_parameters::clear();
   clear_DRbar_parameters();
   physical.clear();
   problems.clear();
}

void CLASSNAME::set_DRbar_masses(const Eigen::ArrayXd& pars)
{
   MVG = pars(0);
   MFv(0) = pars(1);
   MFv(1) = pars(2);
   MFv(2) = pars(3);
   Mhh(0) = pars(4);
   Mhh(1) = pars(5);
   MAh(0) = pars(6);
   MAh(1) = pars(7);
   MHm(0) = pars(8);
   MHm(1) = pars(9);
   MFd(0) = pars(10);
   MFd(1) = pars(11);
   MFd(2) = pars(12);
   MFu(0) = pars(13);
   MFu(1) = pars(14);
   MFu(2) = pars(15);
   MFe(0) = pars(16);
   MFe(1) = pars(17);
   MFe(2) = pars(18);
   MVWm = pars(19);
   MVP = pars(20);
   MVZ = pars(21);

}

Eigen::ArrayXd CLASSNAME::get_DRbar_masses() const
{
   Eigen::ArrayXd pars(22);

   pars(0) = MVG;
   pars(1) = MFv(0);
   pars(2) = MFv(1);
   pars(3) = MFv(2);
   pars(4) = Mhh(0);
   pars(5) = Mhh(1);
   pars(6) = MAh(0);
   pars(7) = MAh(1);
   pars(8) = MHm(0);
   pars(9) = MHm(1);
   pars(10) = MFd(0);
   pars(11) = MFd(1);
   pars(12) = MFd(2);
   pars(13) = MFu(0);
   pars(14) = MFu(1);
   pars(15) = MFu(2);
   pars(16) = MFe(0);
   pars(17) = MFe(1);
   pars(18) = MFe(2);
   pars(19) = MVWm;
   pars(20) = MVP;
   pars(21) = MVZ;

   return pars;
}

std::string CLASSNAME::name() const
{
   return "THDM_II";
}

void CLASSNAME::run_to(double scale, double eps)
{
   if (eps < 0.0)
      eps = precision;
   THDM_II_soft_parameters::run_to(scale, eps);
}


Eigen::Array<double,1,1> CLASSNAME::get_MChargedHiggs() const
{
   Eigen::Array<double,1,1> MHm_ChargedHiggs;
   Eigen::Array<double,1,1> MHm_goldstone;

   MHm_goldstone(0) = MVWm;

   remove_if_equal(MHm, MHm_goldstone, MHm_ChargedHiggs);

   return MHm_ChargedHiggs;
}

Eigen::Array<double,1,1> CLASSNAME::get_MPseudoscalarHiggs() const
{
   Eigen::Array<double,1,1> MAh_PseudoscalarHiggs;
   Eigen::Array<double,1,1> MAh_goldstone;

   MAh_goldstone(0) = MVZ;

   remove_if_equal(MAh, MAh_goldstone, MAh_PseudoscalarHiggs);

   return MAh_PseudoscalarHiggs;
}




double CLASSNAME::get_mass_matrix_VG() const
{
   const double mass_matrix_VG = Re(0);

   return mass_matrix_VG;
}

void CLASSNAME::calculate_MVG()
{
   const auto mass_matrix_VG = get_mass_matrix_VG();
   MVG = calculate_singlet_mass(mass_matrix_VG);
}

Eigen::Matrix<double,3,3> CLASSNAME::get_mass_matrix_Fv() const
{
   Eigen::Matrix<double,3,3> mass_matrix_Fv;

   mass_matrix_Fv(0,0) = 0;
   mass_matrix_Fv(0,1) = 0;
   mass_matrix_Fv(0,2) = 0;
   mass_matrix_Fv(1,1) = 0;
   mass_matrix_Fv(1,2) = 0;
   mass_matrix_Fv(2,2) = 0;

   Symmetrize(mass_matrix_Fv);

   return mass_matrix_Fv;
}

void CLASSNAME::calculate_MFv()
{
   MFv.setConstant(0);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_hh() const
{
   Eigen::Matrix<double,2,2> mass_matrix_hh;

   mass_matrix_hh(0,0) = M112 + 1.5*Lambda6*v1*v2 + 1.5*v1*v2*Conj(
      Lambda6) + 1.5*Lambda1*Sqr(v1) + 0.5*Lambda3*Sqr(v2) + 0.5*Lambda4*Sqr(v2
      ) + 0.25*Lambda5*Sqr(v2) + 0.25*Conj(Lambda5)*Sqr(v2);
   mass_matrix_hh(0,1) = -0.5*M122 + Lambda3*v1*v2 + Lambda4*v1*v2 + 0.5*
      Lambda5*v1*v2 + 0.5*v1*v2*Conj(Lambda5) - 0.5*Conj(M122) + 0.75*Lambda6*
      Sqr(v1) + 0.75*Conj(Lambda6)*Sqr(v1) + 0.75*Lambda7*Sqr(v2) + 0.75*Conj(
      Lambda7)*Sqr(v2);
   mass_matrix_hh(1,1) = M222 + 1.5*Lambda7*v1*v2 + 1.5*v1*v2*Conj(
      Lambda7) + 0.5*Lambda3*Sqr(v1) + 0.5*Lambda4*Sqr(v1) + 0.25*Lambda5*Sqr(
      v1) + 0.25*Conj(Lambda5)*Sqr(v1) + 1.5*Lambda2*Sqr(v2);

   Symmetrize(mass_matrix_hh);

   return mass_matrix_hh;
}

void CLASSNAME::calculate_Mhh()
{
   const auto mass_matrix_hh(get_mass_matrix_hh());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_hh, Mhh, ZH, eigenvalue_error);
   problems.flag_bad_mass(THDM_II_info::hh, eigenvalue_error > precision
      * Abs(Mhh(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_hh, Mhh, ZH);
#endif


   if (Mhh.minCoeff() < 0.) {
      problems.flag_tachyon(THDM_II_info::hh);
   }

   Mhh = AbsSqrt(Mhh);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Ah() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Ah;

   mass_matrix_Ah(0,0) = M112 + 0.5*Lambda6*v1*v2 + 0.5*v1*v2*Conj(
      Lambda6) + 0.5*Lambda1*Sqr(v1) + 0.5*g1*g2*Cos(ThetaW())*Sin(ThetaW())*
      Sqr(v1) + 0.5*Lambda3*Sqr(v2) + 0.5*Lambda4*Sqr(v2) - 0.25*Lambda5*Sqr(v2
      ) - 0.25*Conj(Lambda5)*Sqr(v2) + 0.25*Sqr(g2)*Sqr(v1)*Sqr(Cos(ThetaW()))
      + 0.25*Sqr(g1)*Sqr(v1)*Sqr(Sin(ThetaW()));
   mass_matrix_Ah(0,1) = -0.5*M122 + 0.5*Lambda5*v1*v2 + 0.5*v1*v2*Conj(
      Lambda5) - 0.5*Conj(M122) + 0.5*g1*g2*v1*v2*Cos(ThetaW())*Sin(ThetaW()) +
      0.25*Lambda6*Sqr(v1) + 0.25*Conj(Lambda6)*Sqr(v1) + 0.25*Lambda7*Sqr(v2)
      + 0.25*Conj(Lambda7)*Sqr(v2) + 0.25*v1*v2*Sqr(g2)*Sqr(Cos(ThetaW())) +
      0.25*v1*v2*Sqr(g1)*Sqr(Sin(ThetaW()));
   mass_matrix_Ah(1,1) = M222 + 0.5*Lambda7*v1*v2 + 0.5*v1*v2*Conj(
      Lambda7) + 0.5*Lambda3*Sqr(v1) + 0.5*Lambda4*Sqr(v1) - 0.25*Lambda5*Sqr(
      v1) - 0.25*Conj(Lambda5)*Sqr(v1) + 0.5*Lambda2*Sqr(v2) + 0.5*g1*g2*Cos(
      ThetaW())*Sin(ThetaW())*Sqr(v2) + 0.25*Sqr(g2)*Sqr(v2)*Sqr(Cos(ThetaW()))
      + 0.25*Sqr(g1)*Sqr(v2)*Sqr(Sin(ThetaW()));

   Symmetrize(mass_matrix_Ah);

   return mass_matrix_Ah;
}

void CLASSNAME::calculate_MAh()
{
   const auto mass_matrix_Ah(get_mass_matrix_Ah());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Ah, MAh, ZA, eigenvalue_error);
   problems.flag_bad_mass(THDM_II_info::Ah, eigenvalue_error > precision
      * Abs(MAh(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Ah, MAh, ZA);
#endif


   if (MAh.minCoeff() < 0.) {
      problems.flag_tachyon(THDM_II_info::Ah);
   }

   MAh = AbsSqrt(MAh);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_Hm() const
{
   Eigen::Matrix<double,2,2> mass_matrix_Hm;

   mass_matrix_Hm(0,0) = M112 + 0.5*Lambda6*v1*v2 + 0.5*v1*v2*Conj(
      Lambda6) + 0.5*Lambda1*Sqr(v1) + 0.25*Sqr(g2)*Sqr(v1) + 0.5*Lambda3*Sqr(
      v2);
   mass_matrix_Hm(0,1) = -M122 + 0.5*Lambda4*v1*v2 + 0.5*v1*v2*Conj(
      Lambda5) + 0.25*v1*v2*Sqr(g2) + 0.5*Conj(Lambda6)*Sqr(v1) + 0.5*Conj(
      Lambda7)*Sqr(v2);
   mass_matrix_Hm(1,0) = 0.5*Lambda4*v1*v2 + 0.5*Lambda5*v1*v2 - Conj(
      M122) + 0.25*v1*v2*Sqr(g2) + 0.5*Lambda6*Sqr(v1) + 0.5*Lambda7*Sqr(v2);
   mass_matrix_Hm(1,1) = M222 + 0.5*Lambda7*v1*v2 + 0.5*v1*v2*Conj(
      Lambda7) + 0.5*Lambda3*Sqr(v1) + 0.5*Lambda2*Sqr(v2) + 0.25*Sqr(g2)*Sqr(
      v2);

   return mass_matrix_Hm;
}

void CLASSNAME::calculate_MHm()
{
   const auto mass_matrix_Hm(get_mass_matrix_Hm());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_Hm, MHm, ZP, eigenvalue_error);
   problems.flag_bad_mass(THDM_II_info::Hm, eigenvalue_error > precision
      * Abs(MHm(0)));
#else
   fs_diagonalize_hermitian(mass_matrix_Hm, MHm, ZP);
#endif


   if (MHm.minCoeff() < 0.) {
      problems.flag_tachyon(THDM_II_info::Hm);
   }

   MHm = AbsSqrt(MHm);
}

Eigen::Matrix<double,3,3> CLASSNAME::get_mass_matrix_Fd() const
{
   Eigen::Matrix<double,3,3> mass_matrix_Fd;

   mass_matrix_Fd(0,0) = 0;
   mass_matrix_Fd(0,1) = 0;
   mass_matrix_Fd(0,2) = 0;
   mass_matrix_Fd(1,1) = 0;
   mass_matrix_Fd(1,2) = 0;
   mass_matrix_Fd(2,2) = 0;

   Symmetrize(mass_matrix_Fd);

   return mass_matrix_Fd;
}

void CLASSNAME::calculate_MFd()
{
   const auto mass_matrix_Fd(get_mass_matrix_Fd());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_svd(mass_matrix_Fd, MFd, Vd, Ud, eigenvalue_error);
   problems.flag_bad_mass(THDM_II_info::Fd, eigenvalue_error > precision
      * Abs(MFd(0)));
#else
   fs_svd(mass_matrix_Fd, MFd, Vd, Ud);
#endif

}

Eigen::Matrix<double,3,3> CLASSNAME::get_mass_matrix_Fu() const
{
   Eigen::Matrix<double,3,3> mass_matrix_Fu;

   mass_matrix_Fu(0,0) = 0;
   mass_matrix_Fu(0,1) = 0;
   mass_matrix_Fu(0,2) = 0;
   mass_matrix_Fu(1,1) = 0;
   mass_matrix_Fu(1,2) = 0;
   mass_matrix_Fu(2,2) = 0;

   Symmetrize(mass_matrix_Fu);

   return mass_matrix_Fu;
}

void CLASSNAME::calculate_MFu()
{
   const auto mass_matrix_Fu(get_mass_matrix_Fu());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_svd(mass_matrix_Fu, MFu, Vu, Uu, eigenvalue_error);
   problems.flag_bad_mass(THDM_II_info::Fu, eigenvalue_error > precision
      * Abs(MFu(0)));
#else
   fs_svd(mass_matrix_Fu, MFu, Vu, Uu);
#endif

}

Eigen::Matrix<double,3,3> CLASSNAME::get_mass_matrix_Fe() const
{
   Eigen::Matrix<double,3,3> mass_matrix_Fe;

   mass_matrix_Fe(0,0) = 0;
   mass_matrix_Fe(0,1) = 0;
   mass_matrix_Fe(0,2) = 0;
   mass_matrix_Fe(1,1) = 0;
   mass_matrix_Fe(1,2) = 0;
   mass_matrix_Fe(2,2) = 0;

   Symmetrize(mass_matrix_Fe);

   return mass_matrix_Fe;
}

void CLASSNAME::calculate_MFe()
{
   const auto mass_matrix_Fe(get_mass_matrix_Fe());


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_svd(mass_matrix_Fe, MFe, Ve, Ue, eigenvalue_error);
   problems.flag_bad_mass(THDM_II_info::Fe, eigenvalue_error > precision
      * Abs(MFe(0)));
#else
   fs_svd(mass_matrix_Fe, MFe, Ve, Ue);
#endif

}

double CLASSNAME::get_mass_matrix_VWm() const
{
   const double mass_matrix_VWm = Re(0.25*Sqr(g2)*(Sqr(v1) + Sqr(v2)));

   return mass_matrix_VWm;
}

void CLASSNAME::calculate_MVWm()
{
   const auto mass_matrix_VWm = get_mass_matrix_VWm();
   MVWm = calculate_singlet_mass(mass_matrix_VWm);

   if (MVWm < 0.) {
      problems.flag_tachyon(THDM_II_info::VWm);
   }

   MVWm = AbsSqrt(MVWm);
}

Eigen::Matrix<double,2,2> CLASSNAME::get_mass_matrix_VPVZ() const
{
   Eigen::Matrix<double,2,2> mass_matrix_VPVZ;

   mass_matrix_VPVZ(0,0) = 0.25*Sqr(g1)*Sqr(v1) + 0.25*Sqr(g1)*Sqr(v2);
   mass_matrix_VPVZ(0,1) = -0.25*g1*g2*Sqr(v1) - 0.25*g1*g2*Sqr(v2);
   mass_matrix_VPVZ(1,1) = 0.25*Sqr(g2)*Sqr(v1) + 0.25*Sqr(g2)*Sqr(v2);

   Symmetrize(mass_matrix_VPVZ);

   return mass_matrix_VPVZ;
}

void CLASSNAME::calculate_MVPVZ()
{
   const auto mass_matrix_VPVZ(get_mass_matrix_VPVZ());
   Eigen::Array<double,2,1> MVPVZ;


#ifdef CHECK_EIGENVALUE_ERROR
   double eigenvalue_error;
   fs_diagonalize_hermitian(mass_matrix_VPVZ, MVPVZ, ZZ, eigenvalue_error
      );
   ZZ.transposeInPlace();
#else
   fs_diagonalize_hermitian(mass_matrix_VPVZ, MVPVZ, ZZ);
   ZZ.transposeInPlace();
#endif


   MVPVZ = AbsSqrt(MVPVZ);

   MVP = 0.;
   MVZ = MVPVZ(1);
}


double CLASSNAME::get_ewsb_eq_hh_1() const
{
   double result = Re(M112*v1 + 0.5*Lambda1*Power(v1,3) - 0.5*M122*v2 + 0.25*
      Lambda7*Power(v2,3) + 0.25*Power(v2,3)*Conj(Lambda7) - 0.5*v2*Conj(M122) +
      0.75*Lambda6*v2*Sqr(v1) + 0.75*v2*Conj(Lambda6)*Sqr(v1) + 0.5*Lambda3*v1*Sqr
      (v2) + 0.5*Lambda4*v1*Sqr(v2) + 0.25*Lambda5*v1*Sqr(v2) + 0.25*v1*Conj(
      Lambda5)*Sqr(v2));

   return result;
}

double CLASSNAME::get_ewsb_eq_hh_2() const
{
   double result = Re(-0.5*M122*v1 + 0.25*Lambda6*Power(v1,3) + M222*v2 + 0.5*
      Lambda2*Power(v2,3) + 0.25*Power(v1,3)*Conj(Lambda6) - 0.5*v1*Conj(M122) +
      0.5*Lambda3*v2*Sqr(v1) + 0.5*Lambda4*v2*Sqr(v1) + 0.25*Lambda5*v2*Sqr(v1) +
      0.25*v2*Conj(Lambda5)*Sqr(v1) + 0.75*Lambda7*v1*Sqr(v2) + 0.75*v1*Conj(
      Lambda7)*Sqr(v2));

   return result;
}



std::complex<double> CLASSNAME::CpUhhVZVZ(unsigned gO2) const
{
   std::complex<double> result;

   result = 0.5*(v1*KroneckerDelta(0,gO2) + v2*KroneckerDelta(1,gO2))*Sqr(g2*
      Cos(ThetaW()) + g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpUhhconjVWmVWm(unsigned gO2) const
{
   std::complex<double> result;

   result = 0.5*(v1*KroneckerDelta(0,gO2) + v2*KroneckerDelta(1,gO2))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpUhhbargWmgWm(unsigned gO1) const
{
   std::complex<double> result;

   result = -0.25*(v1*KroneckerDelta(0,gO1) + v2*KroneckerDelta(1,gO1))*Sqr(g2)
      ;

   return result;
}

std::complex<double> CLASSNAME::CpUhhbargWmCgWmC(unsigned gO1) const
{
   std::complex<double> result;

   result = -0.25*(v1*KroneckerDelta(0,gO1) + v2*KroneckerDelta(1,gO1))*Sqr(g2)
      ;

   return result;
}

std::complex<double> CLASSNAME::CpUhhbargZgZ(unsigned gO1) const
{
   std::complex<double> result;

   result = -0.25*(v1*KroneckerDelta(0,gO1) + v2*KroneckerDelta(1,gO1))*Sqr(g2*
      Cos(ThetaW()) + g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhconjVWmVWm(unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   result = 0.5*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + KroneckerDelta(1
      ,gO1)*KroneckerDelta(1,gO2))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhVZVZ(unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   result = 0.5*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + KroneckerDelta(1
      ,gO1)*KroneckerDelta(1,gO2))*Sqr(g2*Cos(ThetaW()) + g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhAhAh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*(ZA(gI1,1)*((
      Lambda7 + Conj(Lambda7))*ZA(gI2,0) + 2*Lambda2*ZA(gI2,1)) + ZA(gI1,0)*((2*
      Lambda3 + 2*Lambda4 - Lambda5 - Conj(Lambda5))*ZA(gI2,0) + (Lambda7 + Conj(
      Lambda7))*ZA(gI2,1))) + KroneckerDelta(0,gO2)*(ZA(gI1,0)*((Lambda6 + Conj(
      Lambda6))*ZA(gI2,0) + (Lambda5 + Conj(Lambda5))*ZA(gI2,1)) + ZA(gI1,1)*((
      Lambda5 + Conj(Lambda5))*ZA(gI2,0) + (Lambda7 + Conj(Lambda7))*ZA(gI2,1)))))
      - KroneckerDelta(0,gO1)*(KroneckerDelta(0,gO2)*(ZA(gI1,1)*((Lambda6 + Conj(
      Lambda6))*ZA(gI2,0) + (2*Lambda3 + 2*Lambda4 - Lambda5 - Conj(Lambda5))*ZA(
      gI2,1)) + ZA(gI1,0)*(2*Lambda1*ZA(gI2,0) + (Lambda6 + Conj(Lambda6))*ZA(gI2,
      1))) + KroneckerDelta(1,gO2)*(ZA(gI1,0)*((Lambda6 + Conj(Lambda6))*ZA(gI2,0)
      + (Lambda5 + Conj(Lambda5))*ZA(gI2,1)) + ZA(gI1,1)*((Lambda5 + Conj(Lambda5
      ))*ZA(gI2,0) + (Lambda7 + Conj(Lambda7))*ZA(gI2,1)))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhconjHmHm(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(1,gO1)*(2*KroneckerDelta(1,gO2)*(ZP(gI1,1)*(
      Lambda7*ZP(gI2,0) + Lambda2*ZP(gI2,1)) + ZP(gI1,0)*(Lambda3*ZP(gI2,0) + Conj
      (Lambda7)*ZP(gI2,1))) + KroneckerDelta(0,gO2)*(ZP(gI1,0)*((Lambda6 + Conj(
      Lambda6))*ZP(gI2,0) + (Lambda4 + Conj(Lambda5))*ZP(gI2,1)) + ZP(gI1,1)*((
      Lambda4 + Lambda5)*ZP(gI2,0) + (Lambda7 + Conj(Lambda7))*ZP(gI2,1))))) -
      KroneckerDelta(0,gO1)*(2*KroneckerDelta(0,gO2)*(ZP(gI1,1)*(Lambda6*ZP(gI2,0)
      + Lambda3*ZP(gI2,1)) + ZP(gI1,0)*(Lambda1*ZP(gI2,0) + Conj(Lambda6)*ZP(gI2,
      1))) + KroneckerDelta(1,gO2)*(ZP(gI1,0)*((Lambda6 + Conj(Lambda6))*ZP(gI2,0)
      + (Lambda4 + Conj(Lambda5))*ZP(gI2,1)) + ZP(gI1,1)*((Lambda4 + Lambda5)*ZP(
      gI2,0) + (Lambda7 + Conj(Lambda7))*ZP(gI2,1)))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhUhhhhhh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*(3*ZH(gI1,1)*((
      Lambda7 + Conj(Lambda7))*ZH(gI2,0) + 2*Lambda2*ZH(gI2,1)) + ZH(gI1,0)*((2*
      Lambda3 + 2*Lambda4 + Lambda5 + Conj(Lambda5))*ZH(gI2,0) + 3*(Lambda7 + Conj
      (Lambda7))*ZH(gI2,1))) + KroneckerDelta(0,gO2)*(ZH(gI1,0)*(3*(Lambda6 + Conj
      (Lambda6))*ZH(gI2,0) + (2*Lambda3 + 2*Lambda4 + Lambda5 + Conj(Lambda5))*ZH(
      gI2,1)) + ZH(gI1,1)*((2*Lambda3 + 2*Lambda4 + Lambda5 + Conj(Lambda5))*ZH(
      gI2,0) + 3*(Lambda7 + Conj(Lambda7))*ZH(gI2,1))))) - KroneckerDelta(0,gO1)*(
      KroneckerDelta(0,gO2)*(ZH(gI1,1)*(3*(Lambda6 + Conj(Lambda6))*ZH(gI2,0) + (2
      *Lambda3 + 2*Lambda4 + Lambda5 + Conj(Lambda5))*ZH(gI2,1)) + 3*ZH(gI1,0)*(2*
      Lambda1*ZH(gI2,0) + (Lambda6 + Conj(Lambda6))*ZH(gI2,1))) + KroneckerDelta(1
      ,gO2)*(ZH(gI1,0)*(3*(Lambda6 + Conj(Lambda6))*ZH(gI2,0) + (2*Lambda3 + 2*
      Lambda4 + Lambda5 + Conj(Lambda5))*ZH(gI2,1)) + ZH(gI1,1)*((2*Lambda3 + 2*
      Lambda4 + Lambda5 + Conj(Lambda5))*ZH(gI2,0) + 3*(Lambda7 + Conj(Lambda7))*
      ZH(gI2,1)))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhAhAh(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(0,gO2)*(ZA(gI1,0)*((2*Lambda1*v1 + Lambda6*v2
      + v2*Conj(Lambda6))*ZA(gI2,0) + (Lambda6*v1 + Lambda5*v2 + v2*Conj(Lambda5)
      + v1*Conj(Lambda6))*ZA(gI2,1)) + ZA(gI1,1)*((Lambda6*v1 + Lambda5*v2 + v2*
      Conj(Lambda5) + v1*Conj(Lambda6))*ZA(gI2,0) + (2*Lambda3*v1 + 2*Lambda4*v1 -
      Lambda5*v1 + Lambda7*v2 - v1*Conj(Lambda5) + v2*Conj(Lambda7))*ZA(gI2,1))))
      - KroneckerDelta(1,gO2)*(ZA(gI1,1)*((Lambda5*v1 + Lambda7*v2 + v1*Conj(
      Lambda5) + v2*Conj(Lambda7))*ZA(gI2,0) + (Lambda7*v1 + 2*Lambda2*v2 + v1*
      Conj(Lambda7))*ZA(gI2,1)) + ZA(gI1,0)*((Lambda6*v1 + 2*Lambda3*v2 + 2*
      Lambda4*v2 - Lambda5*v2 - v2*Conj(Lambda5) + v1*Conj(Lambda6))*ZA(gI2,0) + (
      Lambda5*v1 + Lambda7*v2 + v1*Conj(Lambda5) + v2*Conj(Lambda7))*ZA(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhconjHmHm(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(0,gO2)*(ZP(gI1,0)*((2*Lambda1*v1 + Lambda6*v2
      + v2*Conj(Lambda6))*ZP(gI2,0) + (Lambda4*v2 + v2*Conj(Lambda5) + 2*v1*Conj(
      Lambda6))*ZP(gI2,1)) + ZP(gI1,1)*((2*Lambda6*v1 + (Lambda4 + Lambda5)*v2)*ZP
      (gI2,0) + (2*Lambda3*v1 + Lambda7*v2 + v2*Conj(Lambda7))*ZP(gI2,1)))) -
      KroneckerDelta(1,gO2)*(ZP(gI1,1)*((Lambda4*v1 + Lambda5*v1 + 2*Lambda7*v2)*
      ZP(gI2,0) + (Lambda7*v1 + 2*Lambda2*v2 + v1*Conj(Lambda7))*ZP(gI2,1)) + ZP(
      gI1,0)*((Lambda6*v1 + 2*Lambda3*v2 + v1*Conj(Lambda6))*ZP(gI2,0) + (Lambda4*
      v1 + v1*Conj(Lambda5) + 2*v2*Conj(Lambda7))*ZP(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhhhAh(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,0.5)*(KroneckerDelta(1,gO2)*(ZA(gI2,1)*((-(
      Lambda5*v1) - Lambda7*v2 + v1*Conj(Lambda5) + v2*Conj(Lambda7))*ZH(gI1,0) +
      v1*(-Lambda7 + Conj(Lambda7))*ZH(gI1,1)) + ZA(gI2,0)*((Lambda6*v1 + Lambda5*
      v2 - v2*Conj(Lambda5) - v1*Conj(Lambda6))*ZH(gI1,0) + (Lambda5*v1 + 3*
      Lambda7*v2 - v1*Conj(Lambda5) - 3*v2*Conj(Lambda7))*ZH(gI1,1))) +
      KroneckerDelta(0,gO2)*(ZA(gI2,0)*(v2*(Lambda6 - Conj(Lambda6))*ZH(gI1,0) + (
      Lambda6*v1 + Lambda5*v2 - v2*Conj(Lambda5) - v1*Conj(Lambda6))*ZH(gI1,1)) +
      ZA(gI2,1)*((-3*Lambda6*v1 - Lambda5*v2 + v2*Conj(Lambda5) + 3*v1*Conj(
      Lambda6))*ZH(gI1,0) + (-(Lambda5*v1) - Lambda7*v2 + v1*Conj(Lambda5) + v2*
      Conj(Lambda7))*ZH(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhhhhh(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(1,gO2)*(ZH(gI1,1)*((2*Lambda3*v1 + 2*Lambda4*
      v1 + Lambda5*v1 + 3*Lambda7*v2 + v1*Conj(Lambda5) + 3*v2*Conj(Lambda7))*ZH(
      gI2,0) + 3*(Lambda7*v1 + 2*Lambda2*v2 + v1*Conj(Lambda7))*ZH(gI2,1)) + ZH(
      gI1,0)*((3*Lambda6*v1 + 2*Lambda3*v2 + 2*Lambda4*v2 + Lambda5*v2 + v2*Conj(
      Lambda5) + 3*v1*Conj(Lambda6))*ZH(gI2,0) + (2*Lambda3*v1 + 2*Lambda4*v1 +
      Lambda5*v1 + 3*Lambda7*v2 + v1*Conj(Lambda5) + 3*v2*Conj(Lambda7))*ZH(gI2,1)
      ))) - KroneckerDelta(0,gO2)*(ZH(gI1,0)*(3*(2*Lambda1*v1 + Lambda6*v2 + v2*
      Conj(Lambda6))*ZH(gI2,0) + (3*Lambda6*v1 + 2*Lambda3*v2 + 2*Lambda4*v2 +
      Lambda5*v2 + v2*Conj(Lambda5) + 3*v1*Conj(Lambda6))*ZH(gI2,1)) + ZH(gI1,1)*(
      (3*Lambda6*v1 + 2*Lambda3*v2 + 2*Lambda4*v2 + Lambda5*v2 + v2*Conj(Lambda5)
      + 3*v1*Conj(Lambda6))*ZH(gI2,0) + (2*Lambda3*v1 + 2*Lambda4*v1 + Lambda5*v1
      + 3*Lambda7*v2 + v1*Conj(Lambda5) + 3*v2*Conj(Lambda7))*ZH(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUhhbarFuFdPR(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_0;
   std::complex<double> tmp_1;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_2;
      std::complex<double> tmp_3;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_3 += Conj(Yd(j1,j2))*Ud(gI2,j1);
      }
      tmp_2 += tmp_3;
      tmp_1 += (Vu(gI1,j2)) * tmp_2;
   }
   tmp_0 += tmp_1;
   result += (0.7071067811865475*KroneckerDelta(0,gO2)) * tmp_0;

   return result;
}

std::complex<double> CLASSNAME::CpUhhbarFuFdPL(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_4;
   std::complex<double> tmp_5;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_6;
      std::complex<double> tmp_7;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_7 += Conj(Uu(gI1,j1))*Yu(j1,j2);
      }
      tmp_6 += tmp_7;
      tmp_5 += (Conj(Vd(gI2,j2))) * tmp_6;
   }
   tmp_4 += tmp_5;
   result += (-0.7071067811865475*KroneckerDelta(1,gO1)) * tmp_4;

   return result;
}

std::complex<double> CLASSNAME::CpUhhbarFvFePR(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_8;
   std::complex<double> tmp_9;
   for (unsigned j1 = 0; j1 < 3; ++j1) {
      tmp_9 += Conj(Ye(j1,gI1))*Ue(gI2,j1);
   }
   tmp_8 += tmp_9;
   result += (0.7071067811865475*KroneckerDelta(0,gO2)) * tmp_8;

   return result;
}

double CLASSNAME::CpUhhbarFvFePL(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpUhhVZAh(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,0.5)*(g2*Cos(ThetaW()) + g1*Sin(ThetaW()))*(
      KroneckerDelta(0,gO2)*ZA(gI2,0) + KroneckerDelta(1,gO2)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUhhconjVWmHm(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   result = -0.5*g2*(KroneckerDelta(0,gO2)*ZP(gI2,0) + KroneckerDelta(1,gO2)*ZP
      (gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhbargWmgWm(unsigned gO1) const
{
   std::complex<double> result;

   result = std::complex<double>(0,0.25)*(v1*KroneckerDelta(0,gO1) + v2*
      KroneckerDelta(1,gO1))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpUAhbargWmCgWmC(unsigned gO1) const
{
   std::complex<double> result;

   result = std::complex<double>(0,-0.25)*(v1*KroneckerDelta(0,gO1) + v2*
      KroneckerDelta(1,gO1))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhconjVWmVWm(unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   result = 0.5*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + KroneckerDelta(1
      ,gO1)*KroneckerDelta(1,gO2))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhVZVZ(unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   result = 0.5*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + KroneckerDelta(1
      ,gO1)*KroneckerDelta(1,gO2))*Sqr(g2*Cos(ThetaW()) + g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhAhAh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*(3*ZA(gI1,1)*((
      Lambda7 + Conj(Lambda7))*ZA(gI2,0) + 2*Lambda2*ZA(gI2,1)) + ZA(gI1,0)*((2*
      Lambda3 + 2*Lambda4 + Lambda5 + Conj(Lambda5))*ZA(gI2,0) + 3*(Lambda7 + Conj
      (Lambda7))*ZA(gI2,1))) + KroneckerDelta(0,gO2)*(ZA(gI1,0)*(3*(Lambda6 + Conj
      (Lambda6))*ZA(gI2,0) + (2*Lambda3 + 2*Lambda4 + Lambda5 + Conj(Lambda5))*ZA(
      gI2,1)) + ZA(gI1,1)*((2*Lambda3 + 2*Lambda4 + Lambda5 + Conj(Lambda5))*ZA(
      gI2,0) + 3*(Lambda7 + Conj(Lambda7))*ZA(gI2,1))))) - KroneckerDelta(0,gO1)*(
      KroneckerDelta(0,gO2)*(ZA(gI1,1)*(3*(Lambda6 + Conj(Lambda6))*ZA(gI2,0) + (2
      *Lambda3 + 2*Lambda4 + Lambda5 + Conj(Lambda5))*ZA(gI2,1)) + 3*ZA(gI1,0)*(2*
      Lambda1*ZA(gI2,0) + (Lambda6 + Conj(Lambda6))*ZA(gI2,1))) + KroneckerDelta(1
      ,gO2)*(ZA(gI1,0)*(3*(Lambda6 + Conj(Lambda6))*ZA(gI2,0) + (2*Lambda3 + 2*
      Lambda4 + Lambda5 + Conj(Lambda5))*ZA(gI2,1)) + ZA(gI1,1)*((2*Lambda3 + 2*
      Lambda4 + Lambda5 + Conj(Lambda5))*ZA(gI2,0) + 3*(Lambda7 + Conj(Lambda7))*
      ZA(gI2,1)))));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhconjHmHm(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(1,gO1)*(2*KroneckerDelta(1,gO2)*(ZP(gI1,1)*(
      Lambda7*ZP(gI2,0) + Lambda2*ZP(gI2,1)) + ZP(gI1,0)*(Lambda3*ZP(gI2,0) + Conj
      (Lambda7)*ZP(gI2,1))) + KroneckerDelta(0,gO2)*(ZP(gI1,0)*((Lambda6 + Conj(
      Lambda6))*ZP(gI2,0) + (Lambda4 + Conj(Lambda5))*ZP(gI2,1)) + ZP(gI1,1)*((
      Lambda4 + Lambda5)*ZP(gI2,0) + (Lambda7 + Conj(Lambda7))*ZP(gI2,1))))) -
      KroneckerDelta(0,gO1)*(2*KroneckerDelta(0,gO2)*(ZP(gI1,1)*(Lambda6*ZP(gI2,0)
      + Lambda3*ZP(gI2,1)) + ZP(gI1,0)*(Lambda1*ZP(gI2,0) + Conj(Lambda6)*ZP(gI2,
      1))) + KroneckerDelta(1,gO2)*(ZP(gI1,0)*((Lambda6 + Conj(Lambda6))*ZP(gI2,0)
      + (Lambda4 + Conj(Lambda5))*ZP(gI2,1)) + ZP(gI1,1)*((Lambda4 + Lambda5)*ZP(
      gI2,0) + (Lambda7 + Conj(Lambda7))*ZP(gI2,1)))));

   return result;
}

std::complex<double> CLASSNAME::CpUAhUAhhhhh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(1,gO1)*(KroneckerDelta(1,gO2)*(ZH(gI1,1)*((
      Lambda7 + Conj(Lambda7))*ZH(gI2,0) + 2*Lambda2*ZH(gI2,1)) + ZH(gI1,0)*((2*
      Lambda3 + 2*Lambda4 - Lambda5 - Conj(Lambda5))*ZH(gI2,0) + (Lambda7 + Conj(
      Lambda7))*ZH(gI2,1))) + KroneckerDelta(0,gO2)*(ZH(gI1,0)*((Lambda6 + Conj(
      Lambda6))*ZH(gI2,0) + (Lambda5 + Conj(Lambda5))*ZH(gI2,1)) + ZH(gI1,1)*((
      Lambda5 + Conj(Lambda5))*ZH(gI2,0) + (Lambda7 + Conj(Lambda7))*ZH(gI2,1)))))
      - KroneckerDelta(0,gO1)*(KroneckerDelta(0,gO2)*(ZH(gI1,1)*((Lambda6 + Conj(
      Lambda6))*ZH(gI2,0) + (2*Lambda3 + 2*Lambda4 - Lambda5 - Conj(Lambda5))*ZH(
      gI2,1)) + ZH(gI1,0)*(2*Lambda1*ZH(gI2,0) + (Lambda6 + Conj(Lambda6))*ZH(gI2,
      1))) + KroneckerDelta(1,gO2)*(ZH(gI1,0)*((Lambda6 + Conj(Lambda6))*ZH(gI2,0)
      + (Lambda5 + Conj(Lambda5))*ZH(gI2,1)) + ZH(gI1,1)*((Lambda5 + Conj(Lambda5
      ))*ZH(gI2,0) + (Lambda7 + Conj(Lambda7))*ZH(gI2,1)))));

   return result;
}

std::complex<double> CLASSNAME::CpUAhAhAh(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,0.5)*(KroneckerDelta(1,gO2)*(ZA(gI1,1)*((-(
      Lambda5*v1) + Lambda7*v2 + v1*Conj(Lambda5) - v2*Conj(Lambda7))*ZA(gI2,0) +
      3*v1*(-Lambda7 + Conj(Lambda7))*ZA(gI2,1)) + ZA(gI1,0)*((-(Lambda6*v1) +
      Lambda5*v2 - v2*Conj(Lambda5) + v1*Conj(Lambda6))*ZA(gI2,0) + (-(Lambda5*v1)
      + Lambda7*v2 + v1*Conj(Lambda5) - v2*Conj(Lambda7))*ZA(gI2,1))) +
      KroneckerDelta(0,gO2)*(ZA(gI1,0)*(3*v2*(Lambda6 - Conj(Lambda6))*ZA(gI2,0) +
      (-(Lambda6*v1) + Lambda5*v2 - v2*Conj(Lambda5) + v1*Conj(Lambda6))*ZA(gI2,1
      )) + ZA(gI1,1)*((-(Lambda6*v1) + Lambda5*v2 - v2*Conj(Lambda5) + v1*Conj(
      Lambda6))*ZA(gI2,0) + (-(Lambda5*v1) + Lambda7*v2 + v1*Conj(Lambda5) - v2*
      Conj(Lambda7))*ZA(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUAhconjHmHm(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,0.5)*(v2*KroneckerDelta(0,gO2) - v1*
      KroneckerDelta(1,gO2))*(ZP(gI1,0)*((Lambda6 - Conj(Lambda6))*ZP(gI2,0) + (
      Lambda4 - Conj(Lambda5))*ZP(gI2,1)) + ZP(gI1,1)*((-Lambda4 + Lambda5)*ZP(gI2
      ,0) + (Lambda7 - Conj(Lambda7))*ZP(gI2,1)));

   return result;
}

std::complex<double> CLASSNAME::CpUAhhhAh(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(1,gO2)*(ZA(gI2,1)*((2*Lambda3*v1 + 2*Lambda4*
      v1 - Lambda5*v1 + Lambda7*v2 - v1*Conj(Lambda5) + v2*Conj(Lambda7))*ZH(gI1,0
      ) + (Lambda7*v1 + 2*Lambda2*v2 + v1*Conj(Lambda7))*ZH(gI1,1)) + ZA(gI2,0)*((
      Lambda6*v1 + Lambda5*v2 + v2*Conj(Lambda5) + v1*Conj(Lambda6))*ZH(gI1,0) + (
      Lambda5*v1 + Lambda7*v2 + v1*Conj(Lambda5) + v2*Conj(Lambda7))*ZH(gI1,1))))
      - KroneckerDelta(0,gO2)*(ZA(gI2,0)*((2*Lambda1*v1 + Lambda6*v2 + v2*Conj(
      Lambda6))*ZH(gI1,0) + (Lambda6*v1 + 2*Lambda3*v2 + 2*Lambda4*v2 - Lambda5*v2
      - v2*Conj(Lambda5) + v1*Conj(Lambda6))*ZH(gI1,1)) + ZA(gI2,1)*((Lambda6*v1
      + Lambda5*v2 + v2*Conj(Lambda5) + v1*Conj(Lambda6))*ZH(gI1,0) + (Lambda5*v1
      + Lambda7*v2 + v1*Conj(Lambda5) + v2*Conj(Lambda7))*ZH(gI1,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUAhhhhh(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,0.5)*(KroneckerDelta(0,gO2)*(ZH(gI1,0)*(v2*(
      Lambda6 - Conj(Lambda6))*ZH(gI2,0) + (Lambda6*v1 + Lambda5*v2 - v2*Conj(
      Lambda5) - v1*Conj(Lambda6))*ZH(gI2,1)) + ZH(gI1,1)*((Lambda6*v1 + Lambda5*
      v2 - v2*Conj(Lambda5) - v1*Conj(Lambda6))*ZH(gI2,0) + (Lambda5*v1 + 3*
      Lambda7*v2 - v1*Conj(Lambda5) - 3*v2*Conj(Lambda7))*ZH(gI2,1))) +
      KroneckerDelta(1,gO2)*(ZH(gI1,1)*((-(Lambda5*v1) - Lambda7*v2 + v1*Conj(
      Lambda5) + v2*Conj(Lambda7))*ZH(gI2,0) + v1*(-Lambda7 + Conj(Lambda7))*ZH(
      gI2,1)) + ZH(gI1,0)*((-3*Lambda6*v1 - Lambda5*v2 + v2*Conj(Lambda5) + 3*v1*
      Conj(Lambda6))*ZH(gI2,0) + (-(Lambda5*v1) - Lambda7*v2 + v1*Conj(Lambda5) +
      v2*Conj(Lambda7))*ZH(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUAhbarFuFdPR(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_10;
   std::complex<double> tmp_11;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_12;
      std::complex<double> tmp_13;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_13 += Conj(Yd(j1,j2))*Ud(gI2,j1);
      }
      tmp_12 += tmp_13;
      tmp_11 += (Vu(gI1,j2)) * tmp_12;
   }
   tmp_10 += tmp_11;
   result += (std::complex<double>(0.,-0.7071067811865475)*KroneckerDelta(0,gO2
      )) * tmp_10;

   return result;
}

std::complex<double> CLASSNAME::CpUAhbarFuFdPL(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_14;
   std::complex<double> tmp_15;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_16;
      std::complex<double> tmp_17;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_17 += Conj(Uu(gI1,j1))*Yu(j1,j2);
      }
      tmp_16 += tmp_17;
      tmp_15 += (Conj(Vd(gI2,j2))) * tmp_16;
   }
   tmp_14 += tmp_15;
   result += (std::complex<double>(0.,0.7071067811865475)*KroneckerDelta(1,gO1)
      ) * tmp_14;

   return result;
}

std::complex<double> CLASSNAME::CpUAhbarFvFePR(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_18;
   std::complex<double> tmp_19;
   for (unsigned j1 = 0; j1 < 3; ++j1) {
      tmp_19 += Conj(Ye(j1,gI1))*Ue(gI2,j1);
   }
   tmp_18 += tmp_19;
   result += (std::complex<double>(0.,-0.7071067811865475)*KroneckerDelta(0,gO2
      )) * tmp_18;

   return result;
}

double CLASSNAME::CpUAhbarFvFePL(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpUAhVZhh(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,0.5)*(g2*Cos(ThetaW()) + g1*Sin(ThetaW()))*(
      KroneckerDelta(0,gO2)*ZH(gI2,0) + KroneckerDelta(1,gO2)*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpUAhconjVWmHm(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,-0.5)*g2*(KroneckerDelta(0,gO2)*ZP(gI2,0) +
      KroneckerDelta(1,gO2)*ZP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmVWmVP(unsigned gO2) const
{
   std::complex<double> result;

   result = 0.5*g1*g2*Cos(ThetaW())*(v1*KroneckerDelta(0,gO2) + v2*
      KroneckerDelta(1,gO2));

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmVZVWm(unsigned gO2) const
{
   std::complex<double> result;

   result = -0.5*g1*g2*(v1*KroneckerDelta(0,gO2) + v2*KroneckerDelta(1,gO2))*
      Sin(ThetaW());

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmbargWmCgZ(unsigned gO1) const
{
   std::complex<double> result;

   result = -0.25*g2*(v1*KroneckerDelta(0,gO1) + v2*KroneckerDelta(1,gO1))*(g2*
      Cos(ThetaW()) - g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpUHmgWmCbargZ(unsigned gO2) const
{
   std::complex<double> result;

   result = 0.25*g2*(v1*KroneckerDelta(0,gO2) + v2*KroneckerDelta(1,gO2))*(g2*
      Cos(ThetaW()) + g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmbargZgWm(unsigned gO1) const
{
   std::complex<double> result;

   result = 0.25*g2*(v1*KroneckerDelta(0,gO1) + v2*KroneckerDelta(1,gO1))*(g2*
      Cos(ThetaW()) + g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpUHmgZbargWm(unsigned gO2) const
{
   std::complex<double> result;

   result = -0.25*g2*(v1*KroneckerDelta(0,gO2) + v2*KroneckerDelta(1,gO2))*(g2*
      Cos(ThetaW()) - g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpUHmconjUHmconjVWmVWm(unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   result = 0.5*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + KroneckerDelta(1
      ,gO1)*KroneckerDelta(1,gO2))*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpUHmconjUHmVZVZ(unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   result = 0.5*(KroneckerDelta(0,gO1)*KroneckerDelta(0,gO2) + KroneckerDelta(1
      ,gO1)*KroneckerDelta(1,gO2))*Sqr(g2*Cos(ThetaW()) - g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpUHmconjUHmAhAh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(ZA(gI1,0)*(2*
      Lambda6*ZA(gI2,0) + (Lambda4 + Lambda5)*ZA(gI2,1)) + ZA(gI1,1)*((Lambda4 +
      Lambda5)*ZA(gI2,0) + 2*Lambda7*ZA(gI2,1))) + KroneckerDelta(0,gO2)*(ZA(gI1,1
      )*((Lambda6 + Conj(Lambda6))*ZA(gI2,0) + 2*Lambda3*ZA(gI2,1)) + ZA(gI1,0)*(2
      *Lambda1*ZA(gI2,0) + (Lambda6 + Conj(Lambda6))*ZA(gI2,1))))) -
      KroneckerDelta(1,gO1)*(2*Conj(Lambda6)*KroneckerDelta(0,gO2)*ZA(gI1,0)*ZA(
      gI2,0) + KroneckerDelta(0,gO2)*((Lambda4 + Conj(Lambda5))*ZA(gI1,0)*ZA(gI2,1
      ) + ZA(gI1,1)*((Lambda4 + Conj(Lambda5))*ZA(gI2,0) + 2*Conj(Lambda7)*ZA(gI2,
      1))) + KroneckerDelta(1,gO2)*(ZA(gI1,1)*((Lambda7 + Conj(Lambda7))*ZA(gI2,0)
      + 2*Lambda2*ZA(gI2,1)) + ZA(gI1,0)*(2*Lambda3*ZA(gI2,0) + (Lambda7 + Conj(
      Lambda7))*ZA(gI2,1)))));

   return result;
}

std::complex<double> CLASSNAME::CpUHmconjUHmconjHmHm(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = -(KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(ZP(gI1,0)*(2*
      Lambda6*ZP(gI2,0) + (Lambda3 + Lambda4)*ZP(gI2,1)) + 2*ZP(gI1,1)*(Lambda5*ZP
      (gI2,0) + Lambda7*ZP(gI2,1))) + KroneckerDelta(0,gO2)*(ZP(gI1,1)*(2*Lambda6*
      ZP(gI2,0) + (Lambda3 + Lambda4)*ZP(gI2,1)) + 2*ZP(gI1,0)*(Lambda1*ZP(gI2,0)
      + Conj(Lambda6)*ZP(gI2,1))))) - KroneckerDelta(1,gO1)*(2*Conj(Lambda6)*
      KroneckerDelta(0,gO2)*ZP(gI1,0)*ZP(gI2,0) + KroneckerDelta(1,gO2)*(2*ZP(gI1,
      1)*(Lambda7*ZP(gI2,0) + Lambda2*ZP(gI2,1)) + ZP(gI1,0)*((Lambda3 + Lambda4)*
      ZP(gI2,0) + 2*Conj(Lambda7)*ZP(gI2,1))) + KroneckerDelta(0,gO2)*(2*Conj(
      Lambda5)*ZP(gI1,0)*ZP(gI2,1) + ZP(gI1,1)*((Lambda3 + Lambda4)*ZP(gI2,0) + 2*
      Conj(Lambda7)*ZP(gI2,1))));

   return result;
}

std::complex<double> CLASSNAME::CpUHmconjUHmhhhh(unsigned gO1, unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(0,gO1)*(KroneckerDelta(1,gO2)*(ZH(gI1,0)*(2*
      Lambda6*ZH(gI2,0) + (Lambda4 + Lambda5)*ZH(gI2,1)) + ZH(gI1,1)*((Lambda4 +
      Lambda5)*ZH(gI2,0) + 2*Lambda7*ZH(gI2,1))) + KroneckerDelta(0,gO2)*(ZH(gI1,1
      )*((Lambda6 + Conj(Lambda6))*ZH(gI2,0) + 2*Lambda3*ZH(gI2,1)) + ZH(gI1,0)*(2
      *Lambda1*ZH(gI2,0) + (Lambda6 + Conj(Lambda6))*ZH(gI2,1))))) -
      KroneckerDelta(1,gO1)*(2*Conj(Lambda6)*KroneckerDelta(0,gO2)*ZH(gI1,0)*ZH(
      gI2,0) + KroneckerDelta(0,gO2)*((Lambda4 + Conj(Lambda5))*ZH(gI1,0)*ZH(gI2,1
      ) + ZH(gI1,1)*((Lambda4 + Conj(Lambda5))*ZH(gI2,0) + 2*Conj(Lambda7)*ZH(gI2,
      1))) + KroneckerDelta(1,gO2)*(ZH(gI1,1)*((Lambda7 + Conj(Lambda7))*ZH(gI2,0)
      + 2*Lambda2*ZH(gI2,1)) + ZH(gI1,0)*(2*Lambda3*ZH(gI2,0) + (Lambda7 + Conj(
      Lambda7))*ZH(gI2,1)))));

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmHmAh(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,0.5)*(v2*ZA(gI2,0) - v1*ZA(gI2,1))*(
      KroneckerDelta(0,gO2)*((Lambda6 - Conj(Lambda6))*ZP(gI1,0) + (Lambda4 - Conj
      (Lambda5))*ZP(gI1,1)) + KroneckerDelta(1,gO2)*((-Lambda4 + Lambda5)*ZP(gI1,0
      ) + (Lambda7 - Conj(Lambda7))*ZP(gI1,1)));

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmHmhh(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*(-(KroneckerDelta(1,gO2)*(ZH(gI2,1)*((Lambda4*v1 + Lambda5*v1 +
      2*Lambda7*v2)*ZP(gI1,0) + (Lambda7*v1 + 2*Lambda2*v2 + v1*Conj(Lambda7))*ZP
      (gI1,1)) + ZH(gI2,0)*((2*Lambda6*v1 + (Lambda4 + Lambda5)*v2)*ZP(gI1,0) + (2
      *Lambda3*v1 + Lambda7*v2 + v2*Conj(Lambda7))*ZP(gI1,1)))) - KroneckerDelta(0
      ,gO2)*(ZH(gI2,0)*((2*Lambda1*v1 + Lambda6*v2 + v2*Conj(Lambda6))*ZP(gI1,0) +
      (Lambda4*v2 + v2*Conj(Lambda5) + 2*v1*Conj(Lambda6))*ZP(gI1,1)) + ZH(gI2,1)
      *((Lambda6*v1 + 2*Lambda3*v2 + v1*Conj(Lambda6))*ZP(gI1,0) + (Lambda4*v1 +
      v1*Conj(Lambda5) + 2*v2*Conj(Lambda7))*ZP(gI1,1))));

   return result;
}

double CLASSNAME::CpconjUHmbarFdFdPR(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmbarFdFdPL(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_20;
   std::complex<double> tmp_21;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_22;
      std::complex<double> tmp_23;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_23 += Conj(Ud(gI1,j1))*Yd(j1,j2);
      }
      tmp_22 += tmp_23;
      tmp_21 += (Conj(Vd(gI2,j2))) * tmp_22;
   }
   tmp_20 += tmp_21;
   result += (-KroneckerDelta(0,gO1)) * tmp_20;

   return result;
}

double CLASSNAME::CpconjUHmbarFeFePR(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmbarFeFePL(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_24;
   std::complex<double> tmp_25;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_26;
      std::complex<double> tmp_27;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_27 += Conj(Ue(gI1,j1))*Ye(j1,j2);
      }
      tmp_26 += tmp_27;
      tmp_25 += (Conj(Ve(gI2,j2))) * tmp_26;
   }
   tmp_24 += tmp_25;
   result += (-KroneckerDelta(0,gO1)) * tmp_24;

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmbarFuFuPR(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_28;
   std::complex<double> tmp_29;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_30;
      std::complex<double> tmp_31;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_31 += Conj(Yu(j1,j2))*Uu(gI2,j1);
      }
      tmp_30 += tmp_31;
      tmp_29 += (Vu(gI1,j2)) * tmp_30;
   }
   tmp_28 += tmp_29;
   result += (-KroneckerDelta(1,gO2)) * tmp_28;

   return result;
}

double CLASSNAME::CpconjUHmbarFuFuPL(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmVWmAh(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,-0.5)*g2*(KroneckerDelta(0,gO2)*ZA(gI2,0) +
      KroneckerDelta(1,gO2)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmVWmhh(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   result = -0.5*g2*(KroneckerDelta(0,gO2)*ZH(gI2,0) + KroneckerDelta(1,gO2)*ZH
      (gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmVPHm(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 2) {
      result += -0.5*g1*Cos(ThetaW())*ZP(gI2,gO2);
   }
   if (gI2 < 2) {
      result += -0.5*g2*Sin(ThetaW())*ZP(gI2,gO2);
   }

   return result;
}

std::complex<double> CLASSNAME::CpconjUHmVZHm(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 2) {
      result += -0.5*g2*Cos(ThetaW())*ZP(gI2,gO2);
   }
   if (gI2 < 2) {
      result += 0.5*g1*Sin(ThetaW())*ZP(gI2,gO2);
   }

   return result;
}

double CLASSNAME::CpVZbargWmgWm() const
{
   double result = 0.0;

   result = -(g2*Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpVZbargWmCgWmC() const
{
   double result = 0.0;

   result = g2*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpVZconjVWmVWm() const
{
   double result = 0.0;

   result = -(g2*Cos(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpVZVZAhAh(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*Sqr(g2*Cos(ThetaW()) + g1*Sin(ThetaW()))*(ZA(gI1,0)*ZA(gI2,0) +
      ZA(gI1,1)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpVZVZconjHmHm(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*Sqr(g2*Cos(ThetaW()) - g1*Sin(ThetaW()))*(ZP(gI1,0)*ZP(gI2,0) +
      ZP(gI1,1)*ZP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpVZVZhhhh(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*Sqr(g2*Cos(ThetaW()) + g1*Sin(ThetaW()))*(ZH(gI1,0)*ZH(gI2,0) +
      ZH(gI1,1)*ZH(gI2,1));

   return result;
}

double CLASSNAME::CpVZconjHmHm(unsigned gI1, unsigned gI2) const
{
   double result = 0.0;

   result = -0.5*KroneckerDelta(gI1,gI2)*(g2*Cos(ThetaW()) - g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpVZhhAh(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,0.5)*(g2*Cos(ThetaW()) + g1*Sin(ThetaW()))*(
      ZA(gI2,0)*ZH(gI1,0) + ZA(gI2,1)*ZH(gI1,1));

   return result;
}

double CLASSNAME::CpVZbarFdFdPL(unsigned gI1, unsigned gI2) const
{
   double result = 0.0;

   result = 0.16666666666666666*KroneckerDelta(gI1,gI2)*(3*g2*Cos(ThetaW()) +
      g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpVZbarFdFdPR(unsigned gI1, unsigned gI2) const
{
   double result = 0.0;

   result = -0.3333333333333333*g1*KroneckerDelta(gI1,gI2)*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpVZbarFeFePL(unsigned gI1, unsigned gI2) const
{
   double result = 0.0;

   result = 0.5*KroneckerDelta(gI1,gI2)*(g2*Cos(ThetaW()) - g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpVZbarFeFePR(unsigned gI1, unsigned gI2) const
{
   double result = 0.0;

   result = -(g1*KroneckerDelta(gI1,gI2)*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpVZbarFuFuPL(unsigned gI1, unsigned gI2) const
{
   double result = 0.0;

   result = -0.16666666666666666*KroneckerDelta(gI1,gI2)*(3*g2*Cos(ThetaW()) -
      g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpVZbarFuFuPR(unsigned gI1, unsigned gI2) const
{
   double result = 0.0;

   result = 0.6666666666666666*g1*KroneckerDelta(gI1,gI2)*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpVZbarFvFvPL(unsigned gI1, unsigned gI2) const
{
   double result = 0.0;

   result = -0.5*KroneckerDelta(gI1,gI2)*(g2*Cos(ThetaW()) + g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpVZbarFvFvPR(unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpVZVZhh(unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*Sqr(g2*Cos(ThetaW()) + g1*Sin(ThetaW()))*(v1*ZH(gI2,0) + v2*ZH(
      gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpVZconjVWmHm(unsigned gI2) const
{
   std::complex<double> result;

   result = -0.5*g1*g2*Sin(ThetaW())*(v1*ZP(gI2,0) + v2*ZP(gI2,1));

   return result;
}

double CLASSNAME::CpVZVZconjVWmVWm1() const
{
   double result = 0.0;

   result = -2*Sqr(g2)*Sqr(Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpVZVZconjVWmVWm2() const
{
   double result = 0.0;

   result = Sqr(g2)*Sqr(Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpVZVZconjVWmVWm3() const
{
   double result = 0.0;

   result = Sqr(g2)*Sqr(Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpconjVWmbargPgWm() const
{
   double result = 0.0;

   result = g2*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpconjVWmbargWmCgP() const
{
   double result = 0.0;

   result = -(g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpconjVWmbargWmCgZ() const
{
   double result = 0.0;

   result = -(g2*Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpconjVWmbargZgWm() const
{
   double result = 0.0;

   result = g2*Cos(ThetaW());

   return result;
}

double CLASSNAME::CpconjVWmVWmVP() const
{
   double result = 0.0;

   result = -(g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpconjVWmVZVWm() const
{
   double result = 0.0;

   result = g2*Cos(ThetaW());

   return result;
}

std::complex<double> CLASSNAME::CpVWmconjVWmAhAh(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*Sqr(g2)*(ZA(gI1,0)*ZA(gI2,0) + ZA(gI1,1)*ZA(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpVWmconjVWmconjHmHm(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*Sqr(g2)*(ZP(gI1,0)*ZP(gI2,0) + ZP(gI1,1)*ZP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpVWmconjVWmhhhh(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*Sqr(g2)*(ZH(gI1,0)*ZH(gI2,0) + ZH(gI1,1)*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpconjVWmHmAh(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = std::complex<double>(0,-0.5)*g2*(ZA(gI2,0)*ZP(gI1,0) + ZA(gI2,1)*ZP
      (gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpconjVWmHmhh(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   result = -0.5*g2*(ZH(gI2,0)*ZP(gI1,0) + ZH(gI2,1)*ZP(gI1,1));

   return result;
}

std::complex<double> CLASSNAME::CpconjVWmbarFuFdPL(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_32;
   std::complex<double> tmp_33;
   for (unsigned j1 = 0; j1 < 3; ++j1) {
      tmp_33 += Conj(Vd(gI2,j1))*Vu(gI1,j1);
   }
   tmp_32 += tmp_33;
   result += (-0.7071067811865475*g2) * tmp_32;

   return result;
}

double CLASSNAME::CpconjVWmbarFuFdPR(unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpconjVWmbarFvFePL(unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gI1 < 3) {
      result += -0.7071067811865475*g2*Conj(Ve(gI2,gI1));
   }

   return result;
}

double CLASSNAME::CpconjVWmbarFvFePR(unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpconjVWmVPHm(unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*g1*g2*Cos(ThetaW())*(v1*ZP(gI2,0) + v2*ZP(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpconjVWmVWmhh(unsigned gI2) const
{
   std::complex<double> result;

   result = 0.5*Sqr(g2)*(v1*ZH(gI2,0) + v2*ZH(gI2,1));

   return result;
}

std::complex<double> CLASSNAME::CpconjVWmVZHm(unsigned gI2) const
{
   std::complex<double> result;

   result = -0.5*g1*g2*Sin(ThetaW())*(v1*ZP(gI2,0) + v2*ZP(gI2,1));

   return result;
}

double CLASSNAME::CpVWmconjVWmVPVP1() const
{
   double result = 0.0;

   result = -2*Sqr(g2)*Sqr(Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpVWmconjVWmVPVP2() const
{
   double result = 0.0;

   result = Sqr(g2)*Sqr(Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpVWmconjVWmVPVP3() const
{
   double result = 0.0;

   result = Sqr(g2)*Sqr(Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpVWmconjVWmVZVZ1() const
{
   double result = 0.0;

   result = -2*Sqr(g2)*Sqr(Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpVWmconjVWmVZVZ2() const
{
   double result = 0.0;

   result = Sqr(g2)*Sqr(Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpVWmconjVWmVZVZ3() const
{
   double result = 0.0;

   result = Sqr(g2)*Sqr(Cos(ThetaW()));

   return result;
}

double CLASSNAME::CpVWmconjVWmconjVWmVWm1() const
{
   double result = 0.0;

   result = -Sqr(g2);

   return result;
}

double CLASSNAME::CpVWmconjVWmconjVWmVWm2() const
{
   double result = 0.0;

   result = -Sqr(g2);

   return result;
}

double CLASSNAME::CpVWmconjVWmconjVWmVWm3() const
{
   double result = 0.0;

   result = 2*Sqr(g2);

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdconjHmFdPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO2 < 3) {
      std::complex<double> tmp_34;
      std::complex<double> tmp_35;
      for (unsigned j2 = 0; j2 < 3; ++j2) {
         tmp_35 += Conj(Vd(gI2,j2))*Yd(gO2,j2);
      }
      tmp_34 += tmp_35;
      result += (-ZP(gI1,0)) * tmp_34;
   }

   return result;
}

double CLASSNAME::CpbarUFdconjHmFdPR(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdhhFuPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO2 < 3) {
      std::complex<double> tmp_36;
      std::complex<double> tmp_37;
      for (unsigned j2 = 0; j2 < 3; ++j2) {
         tmp_37 += Conj(Vu(gI2,j2))*Yd(gO2,j2);
      }
      tmp_36 += tmp_37;
      result += (0.7071067811865475*ZH(gI1,0)) * tmp_36;
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdhhFuPR(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO1 < 3) {
      std::complex<double> tmp_38;
      std::complex<double> tmp_39;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_39 += Conj(Yu(j1,gO1))*Uu(gI2,j1);
      }
      tmp_38 += tmp_39;
      result += (-0.7071067811865475*ZH(gI1,1)) * tmp_38;
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdFuAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO2 < 3) {
      std::complex<double> tmp_40;
      std::complex<double> tmp_41;
      for (unsigned j2 = 0; j2 < 3; ++j2) {
         tmp_41 += Conj(Vu(gI1,j2))*Yd(gO2,j2);
      }
      tmp_40 += tmp_41;
      result += (std::complex<double>(0.,0.7071067811865475)*ZA(gI2,0)) *
         tmp_40;
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdFuAhPR(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO1 < 3) {
      std::complex<double> tmp_42;
      std::complex<double> tmp_43;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_43 += Conj(Yu(j1,gO1))*Uu(gI1,j1);
      }
      tmp_42 += tmp_43;
      result += (std::complex<double>(0.,-0.7071067811865475)*ZA(gI2,1)) *
         tmp_42;
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdVGFdPR(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -(g3*Ud(gI2,gO2));
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdVGFdPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -(g3*Conj(Vd(gI2,gO1)));
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdVPFdPR(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += 0.3333333333333333*g1*Cos(ThetaW())*Ud(gI2,gO2);
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdVPFdPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -0.16666666666666666*g1*Conj(Vd(gI2,gO1))*Cos(ThetaW());
   }
   if (gI2 < 3) {
      result += 0.5*g2*Conj(Vd(gI2,gO1))*Sin(ThetaW());
   }

   return result;
}

double CLASSNAME::CpbarUFdVWmFuPR(unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdVWmFuPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO1 < 3) {
      result += -0.7071067811865475*g2*Conj(Vu(gI2,gO1));
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdVZFdPR(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -0.3333333333333333*g1*Sin(ThetaW())*Ud(gI2,gO2);
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFdVZFdPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += 0.5*g2*Conj(Vd(gI2,gO1))*Cos(ThetaW());
   }
   if (gI2 < 3) {
      result += 0.16666666666666666*g1*Conj(Vd(gI2,gO1))*Sin(ThetaW());
   }

   return result;
}

double CLASSNAME::CpbarUFuconjHmFuPL(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuconjHmFuPR(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO1 < 3) {
      std::complex<double> tmp_44;
      std::complex<double> tmp_45;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_45 += Conj(Yu(j1,gO1))*Uu(gI2,j1);
      }
      tmp_44 += tmp_45;
      result += (-ZP(gI1,1)) * tmp_44;
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuhhFdPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO2 < 3) {
      std::complex<double> tmp_46;
      std::complex<double> tmp_47;
      for (unsigned j2 = 0; j2 < 3; ++j2) {
         tmp_47 += Conj(Vd(gI2,j2))*Yu(gO2,j2);
      }
      tmp_46 += tmp_47;
      result += (-0.7071067811865475*ZH(gI1,1)) * tmp_46;
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuhhFdPR(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO1 < 3) {
      std::complex<double> tmp_48;
      std::complex<double> tmp_49;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_49 += Conj(Yd(j1,gO1))*Ud(gI2,j1);
      }
      tmp_48 += tmp_49;
      result += (0.7071067811865475*ZH(gI1,0)) * tmp_48;
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuFdAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO2 < 3) {
      std::complex<double> tmp_50;
      std::complex<double> tmp_51;
      for (unsigned j2 = 0; j2 < 3; ++j2) {
         tmp_51 += Conj(Vd(gI1,j2))*Yu(gO2,j2);
      }
      tmp_50 += tmp_51;
      result += (std::complex<double>(0.,0.7071067811865475)*ZA(gI2,1)) *
         tmp_50;
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuFdAhPR(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO1 < 3) {
      std::complex<double> tmp_52;
      std::complex<double> tmp_53;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_53 += Conj(Yd(j1,gO1))*Ud(gI1,j1);
      }
      tmp_52 += tmp_53;
      result += (std::complex<double>(0.,-0.7071067811865475)*ZA(gI2,0)) *
         tmp_52;
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuVGFuPR(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -(g3*Uu(gI2,gO2));
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuVGFuPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -(g3*Conj(Vu(gI2,gO1)));
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuVPFuPR(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -0.6666666666666666*g1*Cos(ThetaW())*Uu(gI2,gO2);
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuVPFuPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -0.16666666666666666*g1*Conj(Vu(gI2,gO1))*Cos(ThetaW());
   }
   if (gI2 < 3) {
      result += -0.5*g2*Conj(Vu(gI2,gO1))*Sin(ThetaW());
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuVZFuPR(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += 0.6666666666666666*g1*Sin(ThetaW())*Uu(gI2,gO2);
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuVZFuPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -0.5*g2*Conj(Vu(gI2,gO1))*Cos(ThetaW());
   }
   if (gI2 < 3) {
      result += 0.16666666666666666*g1*Conj(Vu(gI2,gO1))*Sin(ThetaW());
   }

   return result;
}

double CLASSNAME::CpbarUFuconjVWmFdPR(unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarUFuconjVWmFdPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO1 < 3) {
      result += -0.7071067811865475*g2*Conj(Vd(gI2,gO1));
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFeconjHmFePL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO2 < 3) {
      std::complex<double> tmp_54;
      std::complex<double> tmp_55;
      for (unsigned j2 = 0; j2 < 3; ++j2) {
         tmp_55 += Conj(Ve(gI2,j2))*Ye(gO2,j2);
      }
      tmp_54 += tmp_55;
      result += (-ZP(gI1,0)) * tmp_54;
   }

   return result;
}

double CLASSNAME::CpbarUFeconjHmFePR(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarUFehhFvPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO2 < 3) {
      result += 0.7071067811865475*Ye(gO2,gI2)*ZH(gI1,0);
   }

   return result;
}

double CLASSNAME::CpbarUFehhFvPR(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarUFeFvAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   if (gO2 < 3) {
      result += std::complex<double>(0.,0.7071067811865475)*Ye(gO2,gI1)*ZA(
         gI2,0);
   }

   return result;
}

double CLASSNAME::CpbarUFeFvAhPR(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarUFeVPFePR(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += g1*Cos(ThetaW())*Ue(gI2,gO2);
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFeVPFePL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += 0.5*g1*Conj(Ve(gI2,gO1))*Cos(ThetaW());
   }
   if (gI2 < 3) {
      result += 0.5*g2*Conj(Ve(gI2,gO1))*Sin(ThetaW());
   }

   return result;
}

double CLASSNAME::CpbarUFeVWmFvPR(unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

double CLASSNAME::CpbarUFeVWmFvPL(unsigned gO1, unsigned gI2) const
{
   double result = 0.0;

   if (gI2 < 3) {
      result += -0.7071067811865475*g2*KroneckerDelta(gI2,gO1);
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFeVZFePR(unsigned gO2, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -(g1*Sin(ThetaW())*Ue(gI2,gO2));
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarUFeVZFePL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += 0.5*g2*Conj(Ve(gI2,gO1))*Cos(ThetaW());
   }
   if (gI2 < 3) {
      result += -0.5*g1*Conj(Ve(gI2,gO1))*Sin(ThetaW());
   }

   return result;
}

std::complex<double> CLASSNAME::CpbarFdconjHmFdPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_56;
   std::complex<double> tmp_57;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_58;
      std::complex<double> tmp_59;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_59 += Conj(Ud(gO2,j1))*Yd(j1,j2);
      }
      tmp_58 += tmp_59;
      tmp_57 += (Conj(Vd(gI2,j2))) * tmp_58;
   }
   tmp_56 += tmp_57;
   result += (-ZP(gI1,0)) * tmp_56;

   return result;
}

double CLASSNAME::CpbarFdconjHmFdPR(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFdhhFuPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_60;
   std::complex<double> tmp_61;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_62;
      std::complex<double> tmp_63;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_63 += Conj(Ud(gO2,j1))*Yd(j1,j2);
      }
      tmp_62 += tmp_63;
      tmp_61 += (Conj(Vu(gI2,j2))) * tmp_62;
   }
   tmp_60 += tmp_61;
   result += (0.7071067811865475*ZH(gI1,0)) * tmp_60;

   return result;
}

std::complex<double> CLASSNAME::CpbarFdhhFuPR(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_64;
   std::complex<double> tmp_65;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_66;
      std::complex<double> tmp_67;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_67 += Conj(Yu(j1,j2))*Uu(gI2,j1);
      }
      tmp_66 += tmp_67;
      tmp_65 += (Vd(gO1,j2)) * tmp_66;
   }
   tmp_64 += tmp_65;
   result += (-0.7071067811865475*ZH(gI1,1)) * tmp_64;

   return result;
}

std::complex<double> CLASSNAME::CpbarFdFuAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_68;
   std::complex<double> tmp_69;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_70;
      std::complex<double> tmp_71;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_71 += Conj(Ud(gO2,j1))*Yd(j1,j2);
      }
      tmp_70 += tmp_71;
      tmp_69 += (Conj(Vu(gI1,j2))) * tmp_70;
   }
   tmp_68 += tmp_69;
   result += (std::complex<double>(0.,0.7071067811865475)*ZA(gI2,0)) * tmp_68;

   return result;
}

std::complex<double> CLASSNAME::CpbarFdFuAhPR(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_72;
   std::complex<double> tmp_73;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_74;
      std::complex<double> tmp_75;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_75 += Conj(Yu(j1,j2))*Uu(gI1,j1);
      }
      tmp_74 += tmp_75;
      tmp_73 += (Vd(gO1,j2)) * tmp_74;
   }
   tmp_72 += tmp_73;
   result += (std::complex<double>(0.,-0.7071067811865475)*ZA(gI2,1)) * tmp_72;

   return result;
}

double CLASSNAME::CpbarFdVWmFuPR(unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFdVWmFuPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_76;
   std::complex<double> tmp_77;
   for (unsigned j1 = 0; j1 < 3; ++j1) {
      tmp_77 += Conj(Vu(gI2,j1))*Vd(gO1,j1);
   }
   tmp_76 += tmp_77;
   result += (-0.7071067811865475*g2) * tmp_76;

   return result;
}

double CLASSNAME::CpbarFdVZFdPR(unsigned gO2, unsigned gI2) const
{
   double result = 0.0;

   result = -0.3333333333333333*g1*KroneckerDelta(gI2,gO2)*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFdVZFdPL(unsigned gO1, unsigned gI2) const
{
   double result = 0.0;

   result = 0.16666666666666666*KroneckerDelta(gI2,gO1)*(3*g2*Cos(ThetaW()) +
      g1*Sin(ThetaW()));

   return result;
}

std::complex<double> CLASSNAME::CpbarFeconjHmFePL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_78;
   std::complex<double> tmp_79;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_80;
      std::complex<double> tmp_81;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_81 += Conj(Ue(gO2,j1))*Ye(j1,j2);
      }
      tmp_80 += tmp_81;
      tmp_79 += (Conj(Ve(gI2,j2))) * tmp_80;
   }
   tmp_78 += tmp_79;
   result += (-ZP(gI1,0)) * tmp_78;

   return result;
}

double CLASSNAME::CpbarFeconjHmFePR(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFehhFvPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_82;
   std::complex<double> tmp_83;
   for (unsigned j1 = 0; j1 < 3; ++j1) {
      tmp_83 += Conj(Ue(gO2,j1))*Ye(j1,gI2);
   }
   tmp_82 += tmp_83;
   result += (0.7071067811865475*ZH(gI1,0)) * tmp_82;

   return result;
}

double CLASSNAME::CpbarFehhFvPR(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFeFvAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_84;
   std::complex<double> tmp_85;
   for (unsigned j1 = 0; j1 < 3; ++j1) {
      tmp_85 += Conj(Ue(gO2,j1))*Ye(j1,gI1);
   }
   tmp_84 += tmp_85;
   result += (std::complex<double>(0.,0.7071067811865475)*ZA(gI2,0)) * tmp_84;

   return result;
}

double CLASSNAME::CpbarFeFvAhPR(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

double CLASSNAME::CpbarFeVWmFvPR(unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFeVWmFvPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   if (gI2 < 3) {
      result += -0.7071067811865475*g2*Ve(gO1,gI2);
   }

   return result;
}

double CLASSNAME::CpbarFeVZFePR(unsigned gO2, unsigned gI2) const
{
   double result = 0.0;

   result = -(g1*KroneckerDelta(gI2,gO2)*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFeVZFePL(unsigned gO1, unsigned gI2) const
{
   double result = 0.0;

   result = 0.5*KroneckerDelta(gI2,gO1)*(g2*Cos(ThetaW()) - g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFuconjHmFuPL(unsigned , unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFuconjHmFuPR(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_86;
   std::complex<double> tmp_87;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_88;
      std::complex<double> tmp_89;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_89 += Conj(Yu(j1,j2))*Uu(gI2,j1);
      }
      tmp_88 += tmp_89;
      tmp_87 += (Vu(gO1,j2)) * tmp_88;
   }
   tmp_86 += tmp_87;
   result += (-ZP(gI1,1)) * tmp_86;

   return result;
}

std::complex<double> CLASSNAME::CpbarFuhhFdPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_90;
   std::complex<double> tmp_91;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_92;
      std::complex<double> tmp_93;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_93 += Conj(Uu(gO2,j1))*Yu(j1,j2);
      }
      tmp_92 += tmp_93;
      tmp_91 += (Conj(Vd(gI2,j2))) * tmp_92;
   }
   tmp_90 += tmp_91;
   result += (-0.7071067811865475*ZH(gI1,1)) * tmp_90;

   return result;
}

std::complex<double> CLASSNAME::CpbarFuhhFdPR(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_94;
   std::complex<double> tmp_95;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_96;
      std::complex<double> tmp_97;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_97 += Conj(Yd(j1,j2))*Ud(gI2,j1);
      }
      tmp_96 += tmp_97;
      tmp_95 += (Vu(gO1,j2)) * tmp_96;
   }
   tmp_94 += tmp_95;
   result += (0.7071067811865475*ZH(gI1,0)) * tmp_94;

   return result;
}

std::complex<double> CLASSNAME::CpbarFuFdAhPL(unsigned gO2, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_98;
   std::complex<double> tmp_99;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_100;
      std::complex<double> tmp_101;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_101 += Conj(Uu(gO2,j1))*Yu(j1,j2);
      }
      tmp_100 += tmp_101;
      tmp_99 += (Conj(Vd(gI1,j2))) * tmp_100;
   }
   tmp_98 += tmp_99;
   result += (std::complex<double>(0.,0.7071067811865475)*ZA(gI2,1)) * tmp_98;

   return result;
}

std::complex<double> CLASSNAME::CpbarFuFdAhPR(unsigned gO1, unsigned gI1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_102;
   std::complex<double> tmp_103;
   for (unsigned j2 = 0; j2 < 3; ++j2) {
      std::complex<double> tmp_104;
      std::complex<double> tmp_105;
      for (unsigned j1 = 0; j1 < 3; ++j1) {
         tmp_105 += Conj(Yd(j1,j2))*Ud(gI1,j1);
      }
      tmp_104 += tmp_105;
      tmp_103 += (Vu(gO1,j2)) * tmp_104;
   }
   tmp_102 += tmp_103;
   result += (std::complex<double>(0.,-0.7071067811865475)*ZA(gI2,0)) * tmp_102
      ;

   return result;
}

double CLASSNAME::CpbarFuVPFuPR(unsigned gO2, unsigned gI2) const
{
   double result = 0.0;

   result = -0.6666666666666666*g1*Cos(ThetaW())*KroneckerDelta(gI2,gO2);

   return result;
}

double CLASSNAME::CpbarFuVPFuPL(unsigned gO1, unsigned gI2) const
{
   double result = 0.0;

   result = -0.16666666666666666*KroneckerDelta(gI2,gO1)*(g1*Cos(ThetaW()) + 3*
      g2*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFuVZFuPR(unsigned gO2, unsigned gI2) const
{
   double result = 0.0;

   result = 0.6666666666666666*g1*KroneckerDelta(gI2,gO2)*Sin(ThetaW());

   return result;
}

double CLASSNAME::CpbarFuVZFuPL(unsigned gO1, unsigned gI2) const
{
   double result = 0.0;

   result = -0.16666666666666666*KroneckerDelta(gI2,gO1)*(3*g2*Cos(ThetaW()) -
      g1*Sin(ThetaW()));

   return result;
}

double CLASSNAME::CpbarFuconjVWmFdPR(unsigned , unsigned ) const
{
   double result = 0.0;

   result = 0;

   return result;
}

std::complex<double> CLASSNAME::CpbarFuconjVWmFdPL(unsigned gO1, unsigned gI2) const
{
   std::complex<double> result;

   std::complex<double> tmp_106;
   std::complex<double> tmp_107;
   for (unsigned j1 = 0; j1 < 3; ++j1) {
      tmp_107 += Conj(Vd(gI2,j1))*Vu(gO1,j1);
   }
   tmp_106 += tmp_107;
   result += (-0.7071067811865475*g2) * tmp_106;

   return result;
}


std::complex<double> CLASSNAME::self_energy_hh(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   result += -(B0(p,MVWm,MVWm)*CpUhhbargWmCgWmC(gO1)*CpUhhbargWmCgWmC(gO2));
   result += -(B0(p,MVWm,MVWm)*CpUhhbargWmgWm(gO1)*CpUhhbargWmgWm(gO2));
   result += -(B0(p,MVZ,MVZ)*CpUhhbargZgZ(gO1)*CpUhhbargZgZ(gO2));
   result += 4*(-0.5 + B0(p,MVWm,MVWm))*Conj(CpUhhconjVWmVWm(gO2))*
      CpUhhconjVWmVWm(gO1);
   result += 2*(-0.5 + B0(p,MVZ,MVZ))*Conj(CpUhhVZVZ(gO2))*CpUhhVZVZ(gO1);
   std::complex<double> tmp_108;
   std::complex<double> tmp_109;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_109 += A0(MAh(gI1))*CpUhhUhhAhAh(gO1,gO2,gI1,gI1);
   }
   tmp_108 += tmp_109;
   result += (-0.5) * tmp_108;
   std::complex<double> tmp_110;
   std::complex<double> tmp_111;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_111 += A0(MHm(gI1))*CpUhhUhhconjHmHm(gO1,gO2,gI1,gI1);
   }
   tmp_110 += tmp_111;
   result += (-1) * tmp_110;
   std::complex<double> tmp_112;
   std::complex<double> tmp_113;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_113 += A0(Mhh(gI1))*CpUhhUhhhhhh(gO1,gO2,gI1,gI1);
   }
   tmp_112 += tmp_113;
   result += (-0.5) * tmp_112;
   std::complex<double> tmp_114;
   std::complex<double> tmp_115;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_116;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_116 += B0(p,MAh(gI1),MAh(gI2))*Conj(CpUhhAhAh(gO2,gI1,gI2))*
            CpUhhAhAh(gO1,gI1,gI2);
      }
      tmp_115 += tmp_116;
   }
   tmp_114 += tmp_115;
   result += (0.5) * tmp_114;
   std::complex<double> tmp_117;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_118;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_118 += B0(p,MHm(gI1),MHm(gI2))*Conj(CpUhhconjHmHm(gO2,gI1,
            gI2))*CpUhhconjHmHm(gO1,gI1,gI2);
      }
      tmp_117 += tmp_118;
   }
   result += tmp_117;
   std::complex<double> tmp_119;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_120;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_120 += B0(p,Mhh(gI1),MAh(gI2))*Conj(CpUhhhhAh(gO2,gI1,gI2))*
            CpUhhhhAh(gO1,gI1,gI2);
      }
      tmp_119 += tmp_120;
   }
   result += tmp_119;
   std::complex<double> tmp_121;
   std::complex<double> tmp_122;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_123;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_123 += B0(p,Mhh(gI1),Mhh(gI2))*Conj(CpUhhhhhh(gO2,gI1,gI2))*
            CpUhhhhhh(gO1,gI1,gI2);
      }
      tmp_122 += tmp_123;
   }
   tmp_121 += tmp_122;
   result += (0.5) * tmp_121;
   std::complex<double> tmp_124;
   std::complex<double> tmp_125;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_126;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_126 += (Conj(CpUhhbarFuFdPL(gO2,gI1,gI2))*CpUhhbarFuFdPL(gO1
            ,gI1,gI2) + Conj(CpUhhbarFuFdPR(gO2,gI1,gI2))*CpUhhbarFuFdPR(gO1,gI1,
            gI2))*G0(p,MFu(gI1),MFd(gI2));
      }
      tmp_125 += tmp_126;
   }
   tmp_124 += tmp_125;
   result += (6) * tmp_124;
   std::complex<double> tmp_127;
   std::complex<double> tmp_128;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_129;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_129 += (Conj(CpUhhbarFvFePL(gO2,gI1,gI2))*CpUhhbarFvFePL(gO1
            ,gI1,gI2) + Conj(CpUhhbarFvFePR(gO2,gI1,gI2))*CpUhhbarFvFePR(gO1,gI1,
            gI2))*G0(p,MFv(gI1),MFe(gI2));
      }
      tmp_128 += tmp_129;
   }
   tmp_127 += tmp_128;
   result += (2) * tmp_127;
   std::complex<double> tmp_130;
   std::complex<double> tmp_131;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_132;
      std::complex<double> tmp_133;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_133 += B0(p,MFu(gI1),MFd(gI2))*(Conj(CpUhhbarFuFdPR(gO2,gI1,
            gI2))*CpUhhbarFuFdPL(gO1,gI1,gI2) + Conj(CpUhhbarFuFdPL(gO2,gI1,gI2))*
            CpUhhbarFuFdPR(gO1,gI1,gI2))*MFd(gI2);
      }
      tmp_132 += tmp_133;
      tmp_131 += (MFu(gI1)) * tmp_132;
   }
   tmp_130 += tmp_131;
   result += (-12) * tmp_130;
   std::complex<double> tmp_134;
   std::complex<double> tmp_135;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_136;
      std::complex<double> tmp_137;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_137 += B0(p,MFv(gI1),MFe(gI2))*(Conj(CpUhhbarFvFePR(gO2,gI1,
            gI2))*CpUhhbarFvFePL(gO1,gI1,gI2) + Conj(CpUhhbarFvFePL(gO2,gI1,gI2))*
            CpUhhbarFvFePR(gO1,gI1,gI2))*MFe(gI2);
      }
      tmp_136 += tmp_137;
      tmp_135 += (MFv(gI1)) * tmp_136;
   }
   tmp_134 += tmp_135;
   result += (-4) * tmp_134;
   std::complex<double> tmp_138;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_138 += Conj(CpUhhVZAh(gO2,gI2))*CpUhhVZAh(gO1,gI2)*F0(p,MAh(gI2),
         MVZ);
   }
   result += tmp_138;
   std::complex<double> tmp_139;
   std::complex<double> tmp_140;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_140 += Conj(CpUhhconjVWmHm(gO2,gI2))*CpUhhconjVWmHm(gO1,gI2)*F0(p,
         MHm(gI2),MVWm);
   }
   tmp_139 += tmp_140;
   result += (2) * tmp_139;
   result += 4*CpUhhUhhconjVWmVWm(gO1,gO2)*(A0(MVWm) - 0.5*Sqr(MVWm));
   result += 2*CpUhhUhhVZVZ(gO1,gO2)*(A0(MVZ) - 0.5*Sqr(MVZ));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Ah(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   result += -(B0(p,MVWm,MVWm)*CpUAhbargWmCgWmC(gO1)*CpUAhbargWmCgWmC(gO2));
   result += -(B0(p,MVWm,MVWm)*CpUAhbargWmgWm(gO1)*CpUAhbargWmgWm(gO2));
   std::complex<double> tmp_141;
   std::complex<double> tmp_142;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_142 += A0(MAh(gI1))*CpUAhUAhAhAh(gO1,gO2,gI1,gI1);
   }
   tmp_141 += tmp_142;
   result += (-0.5) * tmp_141;
   std::complex<double> tmp_143;
   std::complex<double> tmp_144;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_144 += A0(MHm(gI1))*CpUAhUAhconjHmHm(gO1,gO2,gI1,gI1);
   }
   tmp_143 += tmp_144;
   result += (-1) * tmp_143;
   std::complex<double> tmp_145;
   std::complex<double> tmp_146;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_146 += A0(Mhh(gI1))*CpUAhUAhhhhh(gO1,gO2,gI1,gI1);
   }
   tmp_145 += tmp_146;
   result += (-0.5) * tmp_145;
   std::complex<double> tmp_147;
   std::complex<double> tmp_148;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_149;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_149 += B0(p,MAh(gI1),MAh(gI2))*Conj(CpUAhAhAh(gO2,gI1,gI2))*
            CpUAhAhAh(gO1,gI1,gI2);
      }
      tmp_148 += tmp_149;
   }
   tmp_147 += tmp_148;
   result += (0.5) * tmp_147;
   std::complex<double> tmp_150;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_151;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_151 += B0(p,MHm(gI1),MHm(gI2))*Conj(CpUAhconjHmHm(gO2,gI1,
            gI2))*CpUAhconjHmHm(gO1,gI1,gI2);
      }
      tmp_150 += tmp_151;
   }
   result += tmp_150;
   std::complex<double> tmp_152;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_153;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_153 += B0(p,Mhh(gI1),MAh(gI2))*Conj(CpUAhhhAh(gO2,gI1,gI2))*
            CpUAhhhAh(gO1,gI1,gI2);
      }
      tmp_152 += tmp_153;
   }
   result += tmp_152;
   std::complex<double> tmp_154;
   std::complex<double> tmp_155;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_156;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_156 += B0(p,Mhh(gI1),Mhh(gI2))*Conj(CpUAhhhhh(gO2,gI1,gI2))*
            CpUAhhhhh(gO1,gI1,gI2);
      }
      tmp_155 += tmp_156;
   }
   tmp_154 += tmp_155;
   result += (0.5) * tmp_154;
   std::complex<double> tmp_157;
   std::complex<double> tmp_158;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_159;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_159 += (Conj(CpUAhbarFuFdPL(gO2,gI1,gI2))*CpUAhbarFuFdPL(gO1
            ,gI1,gI2) + Conj(CpUAhbarFuFdPR(gO2,gI1,gI2))*CpUAhbarFuFdPR(gO1,gI1,
            gI2))*G0(p,MFu(gI1),MFd(gI2));
      }
      tmp_158 += tmp_159;
   }
   tmp_157 += tmp_158;
   result += (6) * tmp_157;
   std::complex<double> tmp_160;
   std::complex<double> tmp_161;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_162;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_162 += (Conj(CpUAhbarFvFePL(gO2,gI1,gI2))*CpUAhbarFvFePL(gO1
            ,gI1,gI2) + Conj(CpUAhbarFvFePR(gO2,gI1,gI2))*CpUAhbarFvFePR(gO1,gI1,
            gI2))*G0(p,MFv(gI1),MFe(gI2));
      }
      tmp_161 += tmp_162;
   }
   tmp_160 += tmp_161;
   result += (2) * tmp_160;
   std::complex<double> tmp_163;
   std::complex<double> tmp_164;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_165;
      std::complex<double> tmp_166;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_166 += B0(p,MFu(gI1),MFd(gI2))*(Conj(CpUAhbarFuFdPR(gO2,gI1,
            gI2))*CpUAhbarFuFdPL(gO1,gI1,gI2) + Conj(CpUAhbarFuFdPL(gO2,gI1,gI2))*
            CpUAhbarFuFdPR(gO1,gI1,gI2))*MFd(gI2);
      }
      tmp_165 += tmp_166;
      tmp_164 += (MFu(gI1)) * tmp_165;
   }
   tmp_163 += tmp_164;
   result += (-12) * tmp_163;
   std::complex<double> tmp_167;
   std::complex<double> tmp_168;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_169;
      std::complex<double> tmp_170;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_170 += B0(p,MFv(gI1),MFe(gI2))*(Conj(CpUAhbarFvFePR(gO2,gI1,
            gI2))*CpUAhbarFvFePL(gO1,gI1,gI2) + Conj(CpUAhbarFvFePL(gO2,gI1,gI2))*
            CpUAhbarFvFePR(gO1,gI1,gI2))*MFe(gI2);
      }
      tmp_169 += tmp_170;
      tmp_168 += (MFv(gI1)) * tmp_169;
   }
   tmp_167 += tmp_168;
   result += (-4) * tmp_167;
   std::complex<double> tmp_171;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_171 += Conj(CpUAhVZhh(gO2,gI2))*CpUAhVZhh(gO1,gI2)*F0(p,Mhh(gI2),
         MVZ);
   }
   result += tmp_171;
   std::complex<double> tmp_172;
   std::complex<double> tmp_173;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_173 += Conj(CpUAhconjVWmHm(gO2,gI2))*CpUAhconjVWmHm(gO1,gI2)*F0(p,
         MHm(gI2),MVWm);
   }
   tmp_172 += tmp_173;
   result += (2) * tmp_172;
   result += 4*CpUAhUAhconjVWmVWm(gO1,gO2)*(A0(MVWm) - 0.5*Sqr(MVWm));
   result += 2*CpUAhUAhVZVZ(gO1,gO2)*(A0(MVZ) - 0.5*Sqr(MVZ));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Hm(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   result += 4*(-0.5 + B0(p,0,MVWm))*Conj(CpconjUHmVWmVP(gO2))*CpconjUHmVWmVP(
      gO1);
   result += 4*(-0.5 + B0(p,MVWm,MVZ))*Conj(CpconjUHmVZVWm(gO2))*CpconjUHmVZVWm
      (gO1);
   result += -(B0(p,MVZ,MVWm)*CpconjUHmbargWmCgZ(gO1)*CpUHmgWmCbargZ(gO2));
   result += -(B0(p,MVWm,MVZ)*CpconjUHmbargZgWm(gO1)*CpUHmgZbargWm(gO2));
   std::complex<double> tmp_174;
   std::complex<double> tmp_175;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_175 += A0(MAh(gI1))*CpUHmconjUHmAhAh(gO1,gO2,gI1,gI1);
   }
   tmp_174 += tmp_175;
   result += (-0.5) * tmp_174;
   std::complex<double> tmp_176;
   std::complex<double> tmp_177;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_177 += A0(MHm(gI1))*CpUHmconjUHmconjHmHm(gO1,gO2,gI1,gI1);
   }
   tmp_176 += tmp_177;
   result += (-1) * tmp_176;
   std::complex<double> tmp_178;
   std::complex<double> tmp_179;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_179 += A0(Mhh(gI1))*CpUHmconjUHmhhhh(gO1,gO2,gI1,gI1);
   }
   tmp_178 += tmp_179;
   result += (-0.5) * tmp_178;
   std::complex<double> tmp_180;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_181;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_181 += B0(p,MHm(gI1),MAh(gI2))*Conj(CpconjUHmHmAh(gO2,gI1,
            gI2))*CpconjUHmHmAh(gO1,gI1,gI2);
      }
      tmp_180 += tmp_181;
   }
   result += tmp_180;
   std::complex<double> tmp_182;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_183;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_183 += B0(p,MHm(gI1),Mhh(gI2))*Conj(CpconjUHmHmhh(gO2,gI1,
            gI2))*CpconjUHmHmhh(gO1,gI1,gI2);
      }
      tmp_182 += tmp_183;
   }
   result += tmp_182;
   std::complex<double> tmp_184;
   std::complex<double> tmp_185;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_186;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_186 += (Conj(CpconjUHmbarFdFdPL(gO2,gI1,gI2))*
            CpconjUHmbarFdFdPL(gO1,gI1,gI2) + Conj(CpconjUHmbarFdFdPR(gO2,gI1,gI2)
            )*CpconjUHmbarFdFdPR(gO1,gI1,gI2))*G0(p,MFd(gI1),MFd(gI2));
      }
      tmp_185 += tmp_186;
   }
   tmp_184 += tmp_185;
   result += (1.5) * tmp_184;
   std::complex<double> tmp_187;
   std::complex<double> tmp_188;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_189;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_189 += (Conj(CpconjUHmbarFeFePL(gO2,gI1,gI2))*
            CpconjUHmbarFeFePL(gO1,gI1,gI2) + Conj(CpconjUHmbarFeFePR(gO2,gI1,gI2)
            )*CpconjUHmbarFeFePR(gO1,gI1,gI2))*G0(p,MFe(gI1),MFe(gI2));
      }
      tmp_188 += tmp_189;
   }
   tmp_187 += tmp_188;
   result += (0.5) * tmp_187;
   std::complex<double> tmp_190;
   std::complex<double> tmp_191;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_192;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_192 += (Conj(CpconjUHmbarFuFuPL(gO2,gI1,gI2))*
            CpconjUHmbarFuFuPL(gO1,gI1,gI2) + Conj(CpconjUHmbarFuFuPR(gO2,gI1,gI2)
            )*CpconjUHmbarFuFuPR(gO1,gI1,gI2))*G0(p,MFu(gI1),MFu(gI2));
      }
      tmp_191 += tmp_192;
   }
   tmp_190 += tmp_191;
   result += (1.5) * tmp_190;
   std::complex<double> tmp_193;
   std::complex<double> tmp_194;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_195;
      std::complex<double> tmp_196;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_196 += B0(p,MFd(gI1),MFd(gI2))*(Conj(CpconjUHmbarFdFdPR(gO2,
            gI1,gI2))*CpconjUHmbarFdFdPL(gO1,gI1,gI2) + Conj(CpconjUHmbarFdFdPL(
            gO2,gI1,gI2))*CpconjUHmbarFdFdPR(gO1,gI1,gI2))*MFd(gI2);
      }
      tmp_195 += tmp_196;
      tmp_194 += (MFd(gI1)) * tmp_195;
   }
   tmp_193 += tmp_194;
   result += (-3) * tmp_193;
   std::complex<double> tmp_197;
   std::complex<double> tmp_198;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_199;
      std::complex<double> tmp_200;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_200 += B0(p,MFe(gI1),MFe(gI2))*(Conj(CpconjUHmbarFeFePR(gO2,
            gI1,gI2))*CpconjUHmbarFeFePL(gO1,gI1,gI2) + Conj(CpconjUHmbarFeFePL(
            gO2,gI1,gI2))*CpconjUHmbarFeFePR(gO1,gI1,gI2))*MFe(gI2);
      }
      tmp_199 += tmp_200;
      tmp_198 += (MFe(gI1)) * tmp_199;
   }
   tmp_197 += tmp_198;
   result += (-1) * tmp_197;
   std::complex<double> tmp_201;
   std::complex<double> tmp_202;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_203;
      std::complex<double> tmp_204;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_204 += B0(p,MFu(gI1),MFu(gI2))*(Conj(CpconjUHmbarFuFuPR(gO2,
            gI1,gI2))*CpconjUHmbarFuFuPL(gO1,gI1,gI2) + Conj(CpconjUHmbarFuFuPL(
            gO2,gI1,gI2))*CpconjUHmbarFuFuPR(gO1,gI1,gI2))*MFu(gI2);
      }
      tmp_203 += tmp_204;
      tmp_202 += (MFu(gI1)) * tmp_203;
   }
   tmp_201 += tmp_202;
   result += (-3) * tmp_201;
   std::complex<double> tmp_205;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_205 += Conj(CpconjUHmVWmAh(gO2,gI2))*CpconjUHmVWmAh(gO1,gI2)*F0(p,
         MAh(gI2),MVWm);
   }
   result += tmp_205;
   std::complex<double> tmp_206;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_206 += Conj(CpconjUHmVWmhh(gO2,gI2))*CpconjUHmVWmhh(gO1,gI2)*F0(p,
         Mhh(gI2),MVWm);
   }
   result += tmp_206;
   std::complex<double> tmp_207;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_207 += Conj(CpconjUHmVPHm(gO2,gI2))*CpconjUHmVPHm(gO1,gI2)*F0(p,
         MHm(gI2),0);
   }
   result += tmp_207;
   std::complex<double> tmp_208;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_208 += Conj(CpconjUHmVZHm(gO2,gI2))*CpconjUHmVZHm(gO1,gI2)*F0(p,
         MHm(gI2),MVZ);
   }
   result += tmp_208;
   result += 4*CpUHmconjUHmconjVWmVWm(gO1,gO2)*(A0(MVWm) - 0.5*Sqr(MVWm));
   result += 2*CpUHmconjUHmVZVZ(gO1,gO2)*(A0(MVZ) - 0.5*Sqr(MVZ));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_VZ(double p ) const
{
   std::complex<double> result;

   result += AbsSqr(CpVZbargWmCgWmC())*B00(p,MVWm,MVWm);
   result += AbsSqr(CpVZbargWmgWm())*B00(p,MVWm,MVWm);
   result += -(A0(MVWm)*(4*CpVZVZconjVWmVWm1() + CpVZVZconjVWmVWm2() +
      CpVZVZconjVWmVWm3()));
   std::complex<double> tmp_209;
   std::complex<double> tmp_210;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_210 += A0(MAh(gI1))*CpVZVZAhAh(gI1,gI1);
   }
   tmp_209 += tmp_210;
   result += (0.5) * tmp_209;
   std::complex<double> tmp_211;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_211 += A0(MHm(gI1))*CpVZVZconjHmHm(gI1,gI1);
   }
   result += tmp_211;
   std::complex<double> tmp_212;
   std::complex<double> tmp_213;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_213 += A0(Mhh(gI1))*CpVZVZhhhh(gI1,gI1);
   }
   tmp_212 += tmp_213;
   result += (0.5) * tmp_212;
   std::complex<double> tmp_214;
   std::complex<double> tmp_215;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_216;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_216 += AbsSqr(CpVZconjHmHm(gI1,gI2))*B00(p,MHm(gI1),MHm(gI2)
            );
      }
      tmp_215 += tmp_216;
   }
   tmp_214 += tmp_215;
   result += (-4) * tmp_214;
   std::complex<double> tmp_217;
   std::complex<double> tmp_218;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_219;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_219 += AbsSqr(CpVZhhAh(gI1,gI2))*B00(p,MAh(gI2),Mhh(gI1));
      }
      tmp_218 += tmp_219;
   }
   tmp_217 += tmp_218;
   result += (-4) * tmp_217;
   std::complex<double> tmp_220;
   std::complex<double> tmp_221;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_222;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_222 += (AbsSqr(CpVZbarFdFdPL(gI1,gI2)) + AbsSqr(
            CpVZbarFdFdPR(gI1,gI2)))*H0(p,MFd(gI1),MFd(gI2));
         tmp_222 += 4*B0(p,MFd(gI1),MFd(gI2))*MFd(gI1)*MFd(gI2)*Re(Conj(
            CpVZbarFdFdPL(gI1,gI2))*CpVZbarFdFdPR(gI1,gI2));
      }
      tmp_221 += tmp_222;
   }
   tmp_220 += tmp_221;
   result += (3) * tmp_220;
   std::complex<double> tmp_223;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_224;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_224 += (AbsSqr(CpVZbarFeFePL(gI1,gI2)) + AbsSqr(
            CpVZbarFeFePR(gI1,gI2)))*H0(p,MFe(gI1),MFe(gI2));
         tmp_224 += 4*B0(p,MFe(gI1),MFe(gI2))*MFe(gI1)*MFe(gI2)*Re(Conj(
            CpVZbarFeFePL(gI1,gI2))*CpVZbarFeFePR(gI1,gI2));
      }
      tmp_223 += tmp_224;
   }
   result += tmp_223;
   std::complex<double> tmp_225;
   std::complex<double> tmp_226;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_227;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_227 += (AbsSqr(CpVZbarFuFuPL(gI1,gI2)) + AbsSqr(
            CpVZbarFuFuPR(gI1,gI2)))*H0(p,MFu(gI1),MFu(gI2));
         tmp_227 += 4*B0(p,MFu(gI1),MFu(gI2))*MFu(gI1)*MFu(gI2)*Re(Conj(
            CpVZbarFuFuPL(gI1,gI2))*CpVZbarFuFuPR(gI1,gI2));
      }
      tmp_226 += tmp_227;
   }
   tmp_225 += tmp_226;
   result += (3) * tmp_225;
   std::complex<double> tmp_228;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_229;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_229 += (AbsSqr(CpVZbarFvFvPL(gI1,gI2)) + AbsSqr(
            CpVZbarFvFvPR(gI1,gI2)))*H0(p,MFv(gI1),MFv(gI2));
         tmp_229 += 4*B0(p,MFv(gI1),MFv(gI2))*MFv(gI1)*MFv(gI2)*Re(Conj(
            CpVZbarFvFvPL(gI1,gI2))*CpVZbarFvFvPR(gI1,gI2));
      }
      tmp_228 += tmp_229;
   }
   result += tmp_228;
   std::complex<double> tmp_230;
   std::complex<double> tmp_231;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_231 += AbsSqr(CpVZconjVWmHm(gI2))*B0(p,MVWm,MHm(gI2));
   }
   tmp_230 += tmp_231;
   result += (2) * tmp_230;
   std::complex<double> tmp_232;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_232 += AbsSqr(CpVZVZhh(gI2))*B0(p,MVZ,Mhh(gI2));
   }
   result += tmp_232;
   result += 2*CpVZVZconjVWmVWm1()*Sqr(MVWm);
   result += -(AbsSqr(CpVZconjVWmVWm())*(2*A0(MVWm) + 10*B00(p,MVWm,MVWm) - 2*(
      2*Sqr(MVWm) - 0.3333333333333333*Sqr(p)) + B0(p,MVWm,MVWm)*(2*Sqr(MVWm) + 4*
      Sqr(p))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_VWm(double p ) const
{
   std::complex<double> result;

   result += AbsSqr(CpconjVWmbargPgWm())*B00(p,MVWm,MVP);
   result += AbsSqr(CpconjVWmbargWmCgP())*B00(p,MVP,MVWm);
   result += AbsSqr(CpconjVWmbargWmCgZ())*B00(p,MVZ,MVWm);
   result += AbsSqr(CpconjVWmbargZgWm())*B00(p,MVWm,MVZ);
   result += -(A0(MVWm)*(4*CpVWmconjVWmconjVWmVWm1() + CpVWmconjVWmconjVWmVWm2(
      ) + CpVWmconjVWmconjVWmVWm3()));
   result += 0;
   std::complex<double> tmp_233;
   std::complex<double> tmp_234;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_234 += A0(MAh(gI1))*CpVWmconjVWmAhAh(gI1,gI1);
   }
   tmp_233 += tmp_234;
   result += (0.5) * tmp_233;
   std::complex<double> tmp_235;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_235 += A0(MHm(gI1))*CpVWmconjVWmconjHmHm(gI1,gI1);
   }
   result += tmp_235;
   std::complex<double> tmp_236;
   std::complex<double> tmp_237;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_237 += A0(Mhh(gI1))*CpVWmconjVWmhhhh(gI1,gI1);
   }
   tmp_236 += tmp_237;
   result += (0.5) * tmp_236;
   std::complex<double> tmp_238;
   std::complex<double> tmp_239;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_240;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_240 += AbsSqr(CpconjVWmHmAh(gI1,gI2))*B00(p,MAh(gI2),MHm(gI1
            ));
      }
      tmp_239 += tmp_240;
   }
   tmp_238 += tmp_239;
   result += (-4) * tmp_238;
   std::complex<double> tmp_241;
   std::complex<double> tmp_242;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_243;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_243 += AbsSqr(CpconjVWmHmhh(gI1,gI2))*B00(p,Mhh(gI2),MHm(gI1
            ));
      }
      tmp_242 += tmp_243;
   }
   tmp_241 += tmp_242;
   result += (-4) * tmp_241;
   std::complex<double> tmp_244;
   std::complex<double> tmp_245;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_246;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_246 += (AbsSqr(CpconjVWmbarFuFdPL(gI1,gI2)) + AbsSqr(
            CpconjVWmbarFuFdPR(gI1,gI2)))*H0(p,MFu(gI1),MFd(gI2));
         tmp_246 += 4*B0(p,MFu(gI1),MFd(gI2))*MFd(gI2)*MFu(gI1)*Re(Conj(
            CpconjVWmbarFuFdPL(gI1,gI2))*CpconjVWmbarFuFdPR(gI1,gI2));
      }
      tmp_245 += tmp_246;
   }
   tmp_244 += tmp_245;
   result += (3) * tmp_244;
   std::complex<double> tmp_247;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_248;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_248 += (AbsSqr(CpconjVWmbarFvFePL(gI1,gI2)) + AbsSqr(
            CpconjVWmbarFvFePR(gI1,gI2)))*H0(p,MFv(gI1),MFe(gI2));
         tmp_248 += 4*B0(p,MFv(gI1),MFe(gI2))*MFe(gI2)*MFv(gI1)*Re(Conj(
            CpconjVWmbarFvFePL(gI1,gI2))*CpconjVWmbarFvFePR(gI1,gI2));
      }
      tmp_247 += tmp_248;
   }
   result += tmp_247;
   std::complex<double> tmp_249;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_249 += AbsSqr(CpconjVWmVPHm(gI2))*B0(p,0,MHm(gI2));
   }
   result += tmp_249;
   std::complex<double> tmp_250;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_250 += AbsSqr(CpconjVWmVWmhh(gI2))*B0(p,MVWm,Mhh(gI2));
   }
   result += tmp_250;
   std::complex<double> tmp_251;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_251 += AbsSqr(CpconjVWmVZHm(gI2))*B0(p,MVZ,MHm(gI2));
   }
   result += tmp_251;
   result += 2*CpVWmconjVWmconjVWmVWm1()*Sqr(MVWm);
   result += -(AbsSqr(CpconjVWmVWmVP())*(A0(MVWm) + 10*B00(p,MVWm,0) - 2*(Sqr(
      MVWm) - 0.3333333333333333*Sqr(p)) + B0(p,MVWm,0)*(Sqr(MVWm) + 4*Sqr(p))));
   result += 0.5*(-(A0(MVZ)*(4*CpVWmconjVWmVZVZ1() + CpVWmconjVWmVZVZ2() +
      CpVWmconjVWmVZVZ3())) + 2*CpVWmconjVWmVZVZ1()*Sqr(MVZ));
   result += -(AbsSqr(CpconjVWmVZVWm())*(A0(MVWm) + A0(MVZ) + 10*B00(p,MVZ,MVWm
      ) - 2*(Sqr(MVWm) + Sqr(MVZ) - 0.3333333333333333*Sqr(p)) + B0(p,MVZ,MVWm)*(
      Sqr(MVWm) + Sqr(MVZ) + 4*Sqr(p))));

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fd_1(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_252;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_253;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_253 += B0(p,MFd(gI2),MHm(gI1))*Conj(CpbarUFdconjHmFdPL(gO2,
            gI1,gI2))*CpbarUFdconjHmFdPR(gO1,gI1,gI2)*MFd(gI2);
      }
      tmp_252 += tmp_253;
   }
   result += tmp_252;
   std::complex<double> tmp_254;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_255;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_255 += B0(p,MFu(gI2),Mhh(gI1))*Conj(CpbarUFdhhFuPL(gO2,gI1,
            gI2))*CpbarUFdhhFuPR(gO1,gI1,gI2)*MFu(gI2);
      }
      tmp_254 += tmp_255;
   }
   result += tmp_254;
   std::complex<double> tmp_256;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_257;
      std::complex<double> tmp_258;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_258 += B0(p,MFu(gI1),MAh(gI2))*Conj(CpbarUFdFuAhPL(gO2,gI1,
            gI2))*CpbarUFdFuAhPR(gO1,gI1,gI2);
      }
      tmp_257 += tmp_258;
      tmp_256 += (MFu(gI1)) * tmp_257;
   }
   result += tmp_256;
   std::complex<double> tmp_259;
   std::complex<double> tmp_260;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_260 += (-0.5 + B0(p,MFd(gI2),0))*Conj(CpbarUFdVGFdPR(gO2,gI2))*
         CpbarUFdVGFdPL(gO1,gI2)*MFd(gI2);
   }
   tmp_259 += tmp_260;
   result += (-5.333333333333333) * tmp_259;
   std::complex<double> tmp_261;
   std::complex<double> tmp_262;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_262 += (-0.5 + B0(p,MFd(gI2),0))*Conj(CpbarUFdVPFdPR(gO2,gI2))*
         CpbarUFdVPFdPL(gO1,gI2)*MFd(gI2);
   }
   tmp_261 += tmp_262;
   result += (-4) * tmp_261;
   std::complex<double> tmp_263;
   std::complex<double> tmp_264;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_264 += (-0.5 + B0(p,MFd(gI2),MVZ))*Conj(CpbarUFdVZFdPR(gO2,gI2))*
         CpbarUFdVZFdPL(gO1,gI2)*MFd(gI2);
   }
   tmp_263 += tmp_264;
   result += (-4) * tmp_263;
   std::complex<double> tmp_265;
   std::complex<double> tmp_266;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_266 += (-0.5 + B0(p,MFu(gI2),MVWm))*Conj(CpbarUFdVWmFuPR(gO2,gI2))
         *CpbarUFdVWmFuPL(gO1,gI2)*MFu(gI2);
   }
   tmp_265 += tmp_266;
   result += (-4) * tmp_265;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fd_PR(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_267;
   std::complex<double> tmp_268;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_269;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_269 += B1(p,MFd(gI2),MHm(gI1))*Conj(CpbarUFdconjHmFdPR(gO2,
            gI1,gI2))*CpbarUFdconjHmFdPR(gO1,gI1,gI2);
      }
      tmp_268 += tmp_269;
   }
   tmp_267 += tmp_268;
   result += (-0.5) * tmp_267;
   std::complex<double> tmp_270;
   std::complex<double> tmp_271;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_272;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_272 += B1(p,MFu(gI2),Mhh(gI1))*Conj(CpbarUFdhhFuPR(gO2,gI1,
            gI2))*CpbarUFdhhFuPR(gO1,gI1,gI2);
      }
      tmp_271 += tmp_272;
   }
   tmp_270 += tmp_271;
   result += (-0.5) * tmp_270;
   std::complex<double> tmp_273;
   std::complex<double> tmp_274;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_275;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_275 += B1(p,MFu(gI1),MAh(gI2))*Conj(CpbarUFdFuAhPR(gO2,gI1,
            gI2))*CpbarUFdFuAhPR(gO1,gI1,gI2);
      }
      tmp_274 += tmp_275;
   }
   tmp_273 += tmp_274;
   result += (-0.5) * tmp_273;
   std::complex<double> tmp_276;
   std::complex<double> tmp_277;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_277 += (0.5 + B1(p,MFd(gI2),0))*Conj(CpbarUFdVGFdPL(gO2,gI2))*
         CpbarUFdVGFdPL(gO1,gI2);
   }
   tmp_276 += tmp_277;
   result += (-1.3333333333333333) * tmp_276;
   std::complex<double> tmp_278;
   std::complex<double> tmp_279;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_279 += (0.5 + B1(p,MFd(gI2),0))*Conj(CpbarUFdVPFdPL(gO2,gI2))*
         CpbarUFdVPFdPL(gO1,gI2);
   }
   tmp_278 += tmp_279;
   result += (-1) * tmp_278;
   std::complex<double> tmp_280;
   std::complex<double> tmp_281;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_281 += (0.5 + B1(p,MFu(gI2),MVWm))*Conj(CpbarUFdVWmFuPL(gO2,gI2))*
         CpbarUFdVWmFuPL(gO1,gI2);
   }
   tmp_280 += tmp_281;
   result += (-1) * tmp_280;
   std::complex<double> tmp_282;
   std::complex<double> tmp_283;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_283 += (0.5 + B1(p,MFd(gI2),MVZ))*Conj(CpbarUFdVZFdPL(gO2,gI2))*
         CpbarUFdVZFdPL(gO1,gI2);
   }
   tmp_282 += tmp_283;
   result += (-1) * tmp_282;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fd_PL(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_284;
   std::complex<double> tmp_285;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_286;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_286 += B1(p,MFd(gI2),MHm(gI1))*Conj(CpbarUFdconjHmFdPL(gO2,
            gI1,gI2))*CpbarUFdconjHmFdPL(gO1,gI1,gI2);
      }
      tmp_285 += tmp_286;
   }
   tmp_284 += tmp_285;
   result += (-0.5) * tmp_284;
   std::complex<double> tmp_287;
   std::complex<double> tmp_288;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_289;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_289 += B1(p,MFu(gI2),Mhh(gI1))*Conj(CpbarUFdhhFuPL(gO2,gI1,
            gI2))*CpbarUFdhhFuPL(gO1,gI1,gI2);
      }
      tmp_288 += tmp_289;
   }
   tmp_287 += tmp_288;
   result += (-0.5) * tmp_287;
   std::complex<double> tmp_290;
   std::complex<double> tmp_291;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_292;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_292 += B1(p,MFu(gI1),MAh(gI2))*Conj(CpbarUFdFuAhPL(gO2,gI1,
            gI2))*CpbarUFdFuAhPL(gO1,gI1,gI2);
      }
      tmp_291 += tmp_292;
   }
   tmp_290 += tmp_291;
   result += (-0.5) * tmp_290;
   std::complex<double> tmp_293;
   std::complex<double> tmp_294;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_294 += (0.5 + B1(p,MFd(gI2),0))*Conj(CpbarUFdVGFdPR(gO2,gI2))*
         CpbarUFdVGFdPR(gO1,gI2);
   }
   tmp_293 += tmp_294;
   result += (-1.3333333333333333) * tmp_293;
   std::complex<double> tmp_295;
   std::complex<double> tmp_296;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_296 += (0.5 + B1(p,MFd(gI2),0))*Conj(CpbarUFdVPFdPR(gO2,gI2))*
         CpbarUFdVPFdPR(gO1,gI2);
   }
   tmp_295 += tmp_296;
   result += (-1) * tmp_295;
   std::complex<double> tmp_297;
   std::complex<double> tmp_298;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_298 += (0.5 + B1(p,MFu(gI2),MVWm))*Conj(CpbarUFdVWmFuPR(gO2,gI2))*
         CpbarUFdVWmFuPR(gO1,gI2);
   }
   tmp_297 += tmp_298;
   result += (-1) * tmp_297;
   std::complex<double> tmp_299;
   std::complex<double> tmp_300;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_300 += (0.5 + B1(p,MFd(gI2),MVZ))*Conj(CpbarUFdVZFdPR(gO2,gI2))*
         CpbarUFdVZFdPR(gO1,gI2);
   }
   tmp_299 += tmp_300;
   result += (-1) * tmp_299;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_1(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_301;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_302;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_302 += B0(p,MFd(gI2),Mhh(gI1))*Conj(CpbarUFuhhFdPL(gO2,gI1,
            gI2))*CpbarUFuhhFdPR(gO1,gI1,gI2)*MFd(gI2);
      }
      tmp_301 += tmp_302;
   }
   result += tmp_301;
   std::complex<double> tmp_303;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_304;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_304 += B0(p,MFu(gI2),MHm(gI1))*Conj(CpbarUFuconjHmFuPL(gO2,
            gI1,gI2))*CpbarUFuconjHmFuPR(gO1,gI1,gI2)*MFu(gI2);
      }
      tmp_303 += tmp_304;
   }
   result += tmp_303;
   std::complex<double> tmp_305;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_306;
      std::complex<double> tmp_307;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_307 += B0(p,MFd(gI1),MAh(gI2))*Conj(CpbarUFuFdAhPL(gO2,gI1,
            gI2))*CpbarUFuFdAhPR(gO1,gI1,gI2);
      }
      tmp_306 += tmp_307;
      tmp_305 += (MFd(gI1)) * tmp_306;
   }
   result += tmp_305;
   std::complex<double> tmp_308;
   std::complex<double> tmp_309;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_309 += (-0.5 + B0(p,MFd(gI2),MVWm))*Conj(CpbarUFuconjVWmFdPR(gO2,
         gI2))*CpbarUFuconjVWmFdPL(gO1,gI2)*MFd(gI2);
   }
   tmp_308 += tmp_309;
   result += (-4) * tmp_308;
   std::complex<double> tmp_310;
   std::complex<double> tmp_311;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_311 += (-0.5 + B0(p,MFu(gI2),0))*Conj(CpbarUFuVGFuPR(gO2,gI2))*
         CpbarUFuVGFuPL(gO1,gI2)*MFu(gI2);
   }
   tmp_310 += tmp_311;
   result += (-5.333333333333333) * tmp_310;
   std::complex<double> tmp_312;
   std::complex<double> tmp_313;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_313 += (-0.5 + B0(p,MFu(gI2),0))*Conj(CpbarUFuVPFuPR(gO2,gI2))*
         CpbarUFuVPFuPL(gO1,gI2)*MFu(gI2);
   }
   tmp_312 += tmp_313;
   result += (-4) * tmp_312;
   std::complex<double> tmp_314;
   std::complex<double> tmp_315;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_315 += (-0.5 + B0(p,MFu(gI2),MVZ))*Conj(CpbarUFuVZFuPR(gO2,gI2))*
         CpbarUFuVZFuPL(gO1,gI2)*MFu(gI2);
   }
   tmp_314 += tmp_315;
   result += (-4) * tmp_314;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_PR(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_316;
   std::complex<double> tmp_317;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_318;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_318 += B1(p,MFu(gI2),MHm(gI1))*Conj(CpbarUFuconjHmFuPR(gO2,
            gI1,gI2))*CpbarUFuconjHmFuPR(gO1,gI1,gI2);
      }
      tmp_317 += tmp_318;
   }
   tmp_316 += tmp_317;
   result += (-0.5) * tmp_316;
   std::complex<double> tmp_319;
   std::complex<double> tmp_320;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_321;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_321 += B1(p,MFd(gI2),Mhh(gI1))*Conj(CpbarUFuhhFdPR(gO2,gI1,
            gI2))*CpbarUFuhhFdPR(gO1,gI1,gI2);
      }
      tmp_320 += tmp_321;
   }
   tmp_319 += tmp_320;
   result += (-0.5) * tmp_319;
   std::complex<double> tmp_322;
   std::complex<double> tmp_323;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_324;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_324 += B1(p,MFd(gI1),MAh(gI2))*Conj(CpbarUFuFdAhPR(gO2,gI1,
            gI2))*CpbarUFuFdAhPR(gO1,gI1,gI2);
      }
      tmp_323 += tmp_324;
   }
   tmp_322 += tmp_323;
   result += (-0.5) * tmp_322;
   std::complex<double> tmp_325;
   std::complex<double> tmp_326;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_326 += (0.5 + B1(p,MFd(gI2),MVWm))*Conj(CpbarUFuconjVWmFdPL(gO2,
         gI2))*CpbarUFuconjVWmFdPL(gO1,gI2);
   }
   tmp_325 += tmp_326;
   result += (-1) * tmp_325;
   std::complex<double> tmp_327;
   std::complex<double> tmp_328;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_328 += (0.5 + B1(p,MFu(gI2),0))*Conj(CpbarUFuVGFuPL(gO2,gI2))*
         CpbarUFuVGFuPL(gO1,gI2);
   }
   tmp_327 += tmp_328;
   result += (-1.3333333333333333) * tmp_327;
   std::complex<double> tmp_329;
   std::complex<double> tmp_330;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_330 += (0.5 + B1(p,MFu(gI2),0))*Conj(CpbarUFuVPFuPL(gO2,gI2))*
         CpbarUFuVPFuPL(gO1,gI2);
   }
   tmp_329 += tmp_330;
   result += (-1) * tmp_329;
   std::complex<double> tmp_331;
   std::complex<double> tmp_332;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_332 += (0.5 + B1(p,MFu(gI2),MVZ))*Conj(CpbarUFuVZFuPL(gO2,gI2))*
         CpbarUFuVZFuPL(gO1,gI2);
   }
   tmp_331 += tmp_332;
   result += (-1) * tmp_331;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_PL(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_333;
   std::complex<double> tmp_334;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_335;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_335 += B1(p,MFu(gI2),MHm(gI1))*Conj(CpbarUFuconjHmFuPL(gO2,
            gI1,gI2))*CpbarUFuconjHmFuPL(gO1,gI1,gI2);
      }
      tmp_334 += tmp_335;
   }
   tmp_333 += tmp_334;
   result += (-0.5) * tmp_333;
   std::complex<double> tmp_336;
   std::complex<double> tmp_337;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_338;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_338 += B1(p,MFd(gI2),Mhh(gI1))*Conj(CpbarUFuhhFdPL(gO2,gI1,
            gI2))*CpbarUFuhhFdPL(gO1,gI1,gI2);
      }
      tmp_337 += tmp_338;
   }
   tmp_336 += tmp_337;
   result += (-0.5) * tmp_336;
   std::complex<double> tmp_339;
   std::complex<double> tmp_340;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_341;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_341 += B1(p,MFd(gI1),MAh(gI2))*Conj(CpbarUFuFdAhPL(gO2,gI1,
            gI2))*CpbarUFuFdAhPL(gO1,gI1,gI2);
      }
      tmp_340 += tmp_341;
   }
   tmp_339 += tmp_340;
   result += (-0.5) * tmp_339;
   std::complex<double> tmp_342;
   std::complex<double> tmp_343;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_343 += (0.5 + B1(p,MFd(gI2),MVWm))*Conj(CpbarUFuconjVWmFdPR(gO2,
         gI2))*CpbarUFuconjVWmFdPR(gO1,gI2);
   }
   tmp_342 += tmp_343;
   result += (-1) * tmp_342;
   std::complex<double> tmp_344;
   std::complex<double> tmp_345;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_345 += (0.5 + B1(p,MFu(gI2),0))*Conj(CpbarUFuVGFuPR(gO2,gI2))*
         CpbarUFuVGFuPR(gO1,gI2);
   }
   tmp_344 += tmp_345;
   result += (-1.3333333333333333) * tmp_344;
   std::complex<double> tmp_346;
   std::complex<double> tmp_347;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_347 += (0.5 + B1(p,MFu(gI2),0))*Conj(CpbarUFuVPFuPR(gO2,gI2))*
         CpbarUFuVPFuPR(gO1,gI2);
   }
   tmp_346 += tmp_347;
   result += (-1) * tmp_346;
   std::complex<double> tmp_348;
   std::complex<double> tmp_349;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_349 += (0.5 + B1(p,MFu(gI2),MVZ))*Conj(CpbarUFuVZFuPR(gO2,gI2))*
         CpbarUFuVZFuPR(gO1,gI2);
   }
   tmp_348 += tmp_349;
   result += (-1) * tmp_348;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_1(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_350;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_351;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_351 += B0(p,MFe(gI2),MHm(gI1))*Conj(CpbarUFeconjHmFePL(gO2,
            gI1,gI2))*CpbarUFeconjHmFePR(gO1,gI1,gI2)*MFe(gI2);
      }
      tmp_350 += tmp_351;
   }
   result += tmp_350;
   std::complex<double> tmp_352;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_353;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_353 += B0(p,MFv(gI2),Mhh(gI1))*Conj(CpbarUFehhFvPL(gO2,gI1,
            gI2))*CpbarUFehhFvPR(gO1,gI1,gI2)*MFv(gI2);
      }
      tmp_352 += tmp_353;
   }
   result += tmp_352;
   std::complex<double> tmp_354;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_355;
      std::complex<double> tmp_356;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_356 += B0(p,MFv(gI1),MAh(gI2))*Conj(CpbarUFeFvAhPL(gO2,gI1,
            gI2))*CpbarUFeFvAhPR(gO1,gI1,gI2);
      }
      tmp_355 += tmp_356;
      tmp_354 += (MFv(gI1)) * tmp_355;
   }
   result += tmp_354;
   std::complex<double> tmp_357;
   std::complex<double> tmp_358;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_358 += (-0.5 + B0(p,MFe(gI2),0))*Conj(CpbarUFeVPFePR(gO2,gI2))*
         CpbarUFeVPFePL(gO1,gI2)*MFe(gI2);
   }
   tmp_357 += tmp_358;
   result += (-4) * tmp_357;
   std::complex<double> tmp_359;
   std::complex<double> tmp_360;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_360 += (-0.5 + B0(p,MFe(gI2),MVZ))*Conj(CpbarUFeVZFePR(gO2,gI2))*
         CpbarUFeVZFePL(gO1,gI2)*MFe(gI2);
   }
   tmp_359 += tmp_360;
   result += (-4) * tmp_359;
   std::complex<double> tmp_361;
   std::complex<double> tmp_362;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_362 += (-0.5 + B0(p,MFv(gI2),MVWm))*Conj(CpbarUFeVWmFvPR(gO2,gI2))
         *CpbarUFeVWmFvPL(gO1,gI2)*MFv(gI2);
   }
   tmp_361 += tmp_362;
   result += (-4) * tmp_361;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_PR(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_363;
   std::complex<double> tmp_364;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_365;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_365 += B1(p,MFe(gI2),MHm(gI1))*Conj(CpbarUFeconjHmFePR(gO2,
            gI1,gI2))*CpbarUFeconjHmFePR(gO1,gI1,gI2);
      }
      tmp_364 += tmp_365;
   }
   tmp_363 += tmp_364;
   result += (-0.5) * tmp_363;
   std::complex<double> tmp_366;
   std::complex<double> tmp_367;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_368;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_368 += B1(p,MFv(gI2),Mhh(gI1))*Conj(CpbarUFehhFvPR(gO2,gI1,
            gI2))*CpbarUFehhFvPR(gO1,gI1,gI2);
      }
      tmp_367 += tmp_368;
   }
   tmp_366 += tmp_367;
   result += (-0.5) * tmp_366;
   std::complex<double> tmp_369;
   std::complex<double> tmp_370;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_371;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_371 += B1(p,MFv(gI1),MAh(gI2))*Conj(CpbarUFeFvAhPR(gO2,gI1,
            gI2))*CpbarUFeFvAhPR(gO1,gI1,gI2);
      }
      tmp_370 += tmp_371;
   }
   tmp_369 += tmp_370;
   result += (-0.5) * tmp_369;
   std::complex<double> tmp_372;
   std::complex<double> tmp_373;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_373 += (0.5 + B1(p,MFe(gI2),0))*Conj(CpbarUFeVPFePL(gO2,gI2))*
         CpbarUFeVPFePL(gO1,gI2);
   }
   tmp_372 += tmp_373;
   result += (-1) * tmp_372;
   std::complex<double> tmp_374;
   std::complex<double> tmp_375;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_375 += (0.5 + B1(p,MFv(gI2),MVWm))*Conj(CpbarUFeVWmFvPL(gO2,gI2))*
         CpbarUFeVWmFvPL(gO1,gI2);
   }
   tmp_374 += tmp_375;
   result += (-1) * tmp_374;
   std::complex<double> tmp_376;
   std::complex<double> tmp_377;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_377 += (0.5 + B1(p,MFe(gI2),MVZ))*Conj(CpbarUFeVZFePL(gO2,gI2))*
         CpbarUFeVZFePL(gO1,gI2);
   }
   tmp_376 += tmp_377;
   result += (-1) * tmp_376;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_PL(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_378;
   std::complex<double> tmp_379;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_380;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_380 += B1(p,MFe(gI2),MHm(gI1))*Conj(CpbarUFeconjHmFePL(gO2,
            gI1,gI2))*CpbarUFeconjHmFePL(gO1,gI1,gI2);
      }
      tmp_379 += tmp_380;
   }
   tmp_378 += tmp_379;
   result += (-0.5) * tmp_378;
   std::complex<double> tmp_381;
   std::complex<double> tmp_382;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_383;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_383 += B1(p,MFv(gI2),Mhh(gI1))*Conj(CpbarUFehhFvPL(gO2,gI1,
            gI2))*CpbarUFehhFvPL(gO1,gI1,gI2);
      }
      tmp_382 += tmp_383;
   }
   tmp_381 += tmp_382;
   result += (-0.5) * tmp_381;
   std::complex<double> tmp_384;
   std::complex<double> tmp_385;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_386;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_386 += B1(p,MFv(gI1),MAh(gI2))*Conj(CpbarUFeFvAhPL(gO2,gI1,
            gI2))*CpbarUFeFvAhPL(gO1,gI1,gI2);
      }
      tmp_385 += tmp_386;
   }
   tmp_384 += tmp_385;
   result += (-0.5) * tmp_384;
   std::complex<double> tmp_387;
   std::complex<double> tmp_388;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_388 += (0.5 + B1(p,MFe(gI2),0))*Conj(CpbarUFeVPFePR(gO2,gI2))*
         CpbarUFeVPFePR(gO1,gI2);
   }
   tmp_387 += tmp_388;
   result += (-1) * tmp_387;
   std::complex<double> tmp_389;
   std::complex<double> tmp_390;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_390 += (0.5 + B1(p,MFv(gI2),MVWm))*Conj(CpbarUFeVWmFvPR(gO2,gI2))*
         CpbarUFeVWmFvPR(gO1,gI2);
   }
   tmp_389 += tmp_390;
   result += (-1) * tmp_389;
   std::complex<double> tmp_391;
   std::complex<double> tmp_392;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_392 += (0.5 + B1(p,MFe(gI2),MVZ))*Conj(CpbarUFeVZFePR(gO2,gI2))*
         CpbarUFeVZFePR(gO1,gI2);
   }
   tmp_391 += tmp_392;
   result += (-1) * tmp_391;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_VZ_heavy(double p ) const
{
   std::complex<double> result;

   std::complex<double> tmp_393;
   std::complex<double> tmp_394;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_394 += AbsSqr(CpVZhhAh(gI1,1))*B00(p,MAh(1),Mhh(gI1));
   }
   tmp_393 += tmp_394;
   result += (-4) * tmp_393;
   std::complex<double> tmp_395;
   std::complex<double> tmp_396;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_396 += A0(Mhh(gI1))*CpVZVZhhhh(gI1,gI1);
   }
   tmp_395 += tmp_396;
   result += (0.5) * tmp_395;
   std::complex<double> tmp_397;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_397 += AbsSqr(CpVZVZhh(gI2))*B0(p,MVZ,Mhh(gI2));
   }
   result += tmp_397;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_VWm_heavy(double p ) const
{
   std::complex<double> result;

   std::complex<double> tmp_398;
   std::complex<double> tmp_399;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_399 += A0(Mhh(gI1))*CpVWmconjVWmhhhh(gI1,gI1);
   }
   tmp_398 += tmp_399;
   result += (0.5) * tmp_398;
   std::complex<double> tmp_400;
   std::complex<double> tmp_401;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_401 += AbsSqr(CpconjVWmHmhh(1,gI2))*B00(p,Mhh(gI2),MHm(1));
   }
   tmp_400 += tmp_401;
   result += (-4) * tmp_400;
   std::complex<double> tmp_402;
   for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
      tmp_402 += AbsSqr(CpconjVWmVWmhh(gI2))*B0(p,MVWm,Mhh(gI2));
   }
   result += tmp_402;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fd_1_heavy_rotated(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_403;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_404;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_404 += B0(p,MFd(gI2),MHm(gI1))*Conj(CpbarFdconjHmFdPL(gO2,
            gI1,gI2))*CpbarFdconjHmFdPR(gO1,gI1,gI2)*MFd(gI2);
      }
      tmp_403 += tmp_404;
   }
   result += tmp_403;
   std::complex<double> tmp_405;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_406;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_406 += B0(p,MFu(gI2),Mhh(gI1))*Conj(CpbarFdhhFuPL(gO2,gI1,
            gI2))*CpbarFdhhFuPR(gO1,gI1,gI2)*MFu(gI2);
      }
      tmp_405 += tmp_406;
   }
   result += tmp_405;
   std::complex<double> tmp_407;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_408;
      std::complex<double> tmp_409;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_409 += B0(p,MFu(gI1),MAh(gI2))*Conj(CpbarFdFuAhPL(gO2,gI1,
            gI2))*CpbarFdFuAhPR(gO1,gI1,gI2);
      }
      tmp_408 += tmp_409;
      tmp_407 += (MFu(gI1)) * tmp_408;
   }
   result += tmp_407;
   std::complex<double> tmp_410;
   std::complex<double> tmp_411;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_411 += (-0.5 + B0(p,MFd(gI2),MVZ))*Conj(CpbarFdVZFdPR(gO2,gI2))*
         CpbarFdVZFdPL(gO1,gI2)*MFd(gI2);
   }
   tmp_410 += tmp_411;
   result += (-4) * tmp_410;
   std::complex<double> tmp_412;
   std::complex<double> tmp_413;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_413 += (-0.5 + B0(p,MFu(gI2),MVWm))*Conj(CpbarFdVWmFuPR(gO2,gI2))*
         CpbarFdVWmFuPL(gO1,gI2)*MFu(gI2);
   }
   tmp_412 += tmp_413;
   result += (-4) * tmp_412;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fd_PR_heavy_rotated(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_414;
   std::complex<double> tmp_415;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_416;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_416 += B1(p,MFd(gI2),MHm(gI1))*Conj(CpbarFdconjHmFdPR(gO2,
            gI1,gI2))*CpbarFdconjHmFdPR(gO1,gI1,gI2);
      }
      tmp_415 += tmp_416;
   }
   tmp_414 += tmp_415;
   result += (-0.5) * tmp_414;
   std::complex<double> tmp_417;
   std::complex<double> tmp_418;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_419;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_419 += B1(p,MFu(gI2),Mhh(gI1))*Conj(CpbarFdhhFuPR(gO2,gI1,
            gI2))*CpbarFdhhFuPR(gO1,gI1,gI2);
      }
      tmp_418 += tmp_419;
   }
   tmp_417 += tmp_418;
   result += (-0.5) * tmp_417;
   std::complex<double> tmp_420;
   std::complex<double> tmp_421;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_422;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_422 += B1(p,MFu(gI1),MAh(gI2))*Conj(CpbarFdFuAhPR(gO2,gI1,
            gI2))*CpbarFdFuAhPR(gO1,gI1,gI2);
      }
      tmp_421 += tmp_422;
   }
   tmp_420 += tmp_421;
   result += (-0.5) * tmp_420;
   std::complex<double> tmp_423;
   std::complex<double> tmp_424;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_424 += (0.5 + B1(p,MFu(gI2),MVWm))*Conj(CpbarFdVWmFuPL(gO2,gI2))*
         CpbarFdVWmFuPL(gO1,gI2);
   }
   tmp_423 += tmp_424;
   result += (-1) * tmp_423;
   std::complex<double> tmp_425;
   std::complex<double> tmp_426;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_426 += (0.5 + B1(p,MFd(gI2),MVZ))*Conj(CpbarFdVZFdPL(gO2,gI2))*
         CpbarFdVZFdPL(gO1,gI2);
   }
   tmp_425 += tmp_426;
   result += (-1) * tmp_425;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fd_PL_heavy_rotated(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_427;
   std::complex<double> tmp_428;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_429;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_429 += B1(p,MFd(gI2),MHm(gI1))*Conj(CpbarFdconjHmFdPL(gO2,
            gI1,gI2))*CpbarFdconjHmFdPL(gO1,gI1,gI2);
      }
      tmp_428 += tmp_429;
   }
   tmp_427 += tmp_428;
   result += (-0.5) * tmp_427;
   std::complex<double> tmp_430;
   std::complex<double> tmp_431;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_432;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_432 += B1(p,MFu(gI2),Mhh(gI1))*Conj(CpbarFdhhFuPL(gO2,gI1,
            gI2))*CpbarFdhhFuPL(gO1,gI1,gI2);
      }
      tmp_431 += tmp_432;
   }
   tmp_430 += tmp_431;
   result += (-0.5) * tmp_430;
   std::complex<double> tmp_433;
   std::complex<double> tmp_434;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_435;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_435 += B1(p,MFu(gI1),MAh(gI2))*Conj(CpbarFdFuAhPL(gO2,gI1,
            gI2))*CpbarFdFuAhPL(gO1,gI1,gI2);
      }
      tmp_434 += tmp_435;
   }
   tmp_433 += tmp_434;
   result += (-0.5) * tmp_433;
   std::complex<double> tmp_436;
   std::complex<double> tmp_437;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_437 += (0.5 + B1(p,MFu(gI2),MVWm))*Conj(CpbarFdVWmFuPR(gO2,gI2))*
         CpbarFdVWmFuPR(gO1,gI2);
   }
   tmp_436 += tmp_437;
   result += (-1) * tmp_436;
   std::complex<double> tmp_438;
   std::complex<double> tmp_439;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_439 += (0.5 + B1(p,MFd(gI2),MVZ))*Conj(CpbarFdVZFdPR(gO2,gI2))*
         CpbarFdVZFdPR(gO1,gI2);
   }
   tmp_438 += tmp_439;
   result += (-1) * tmp_438;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_1_heavy_rotated(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_440;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_441;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_441 += B0(p,MFe(gI2),MHm(gI1))*Conj(CpbarFeconjHmFePL(gO2,
            gI1,gI2))*CpbarFeconjHmFePR(gO1,gI1,gI2)*MFe(gI2);
      }
      tmp_440 += tmp_441;
   }
   result += tmp_440;
   std::complex<double> tmp_442;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_443;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_443 += B0(p,MFv(gI2),Mhh(gI1))*Conj(CpbarFehhFvPL(gO2,gI1,
            gI2))*CpbarFehhFvPR(gO1,gI1,gI2)*MFv(gI2);
      }
      tmp_442 += tmp_443;
   }
   result += tmp_442;
   std::complex<double> tmp_444;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_445;
      std::complex<double> tmp_446;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_446 += B0(p,MFv(gI1),MAh(gI2))*Conj(CpbarFeFvAhPL(gO2,gI1,
            gI2))*CpbarFeFvAhPR(gO1,gI1,gI2);
      }
      tmp_445 += tmp_446;
      tmp_444 += (MFv(gI1)) * tmp_445;
   }
   result += tmp_444;
   std::complex<double> tmp_447;
   std::complex<double> tmp_448;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_448 += (-0.5 + B0(p,MFe(gI2),MVZ))*Conj(CpbarFeVZFePR(gO2,gI2))*
         CpbarFeVZFePL(gO1,gI2)*MFe(gI2);
   }
   tmp_447 += tmp_448;
   result += (-4) * tmp_447;
   std::complex<double> tmp_449;
   std::complex<double> tmp_450;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_450 += (-0.5 + B0(p,MFv(gI2),MVWm))*Conj(CpbarFeVWmFvPR(gO2,gI2))*
         CpbarFeVWmFvPL(gO1,gI2)*MFv(gI2);
   }
   tmp_449 += tmp_450;
   result += (-4) * tmp_449;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_PR_heavy_rotated(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_451;
   std::complex<double> tmp_452;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_453;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_453 += B1(p,MFe(gI2),MHm(gI1))*Conj(CpbarFeconjHmFePR(gO2,
            gI1,gI2))*CpbarFeconjHmFePR(gO1,gI1,gI2);
      }
      tmp_452 += tmp_453;
   }
   tmp_451 += tmp_452;
   result += (-0.5) * tmp_451;
   std::complex<double> tmp_454;
   std::complex<double> tmp_455;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_456;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_456 += B1(p,MFv(gI2),Mhh(gI1))*Conj(CpbarFehhFvPR(gO2,gI1,
            gI2))*CpbarFehhFvPR(gO1,gI1,gI2);
      }
      tmp_455 += tmp_456;
   }
   tmp_454 += tmp_455;
   result += (-0.5) * tmp_454;
   std::complex<double> tmp_457;
   std::complex<double> tmp_458;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_459;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_459 += B1(p,MFv(gI1),MAh(gI2))*Conj(CpbarFeFvAhPR(gO2,gI1,
            gI2))*CpbarFeFvAhPR(gO1,gI1,gI2);
      }
      tmp_458 += tmp_459;
   }
   tmp_457 += tmp_458;
   result += (-0.5) * tmp_457;
   std::complex<double> tmp_460;
   std::complex<double> tmp_461;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_461 += (0.5 + B1(p,MFv(gI2),MVWm))*Conj(CpbarFeVWmFvPL(gO2,gI2))*
         CpbarFeVWmFvPL(gO1,gI2);
   }
   tmp_460 += tmp_461;
   result += (-1) * tmp_460;
   std::complex<double> tmp_462;
   std::complex<double> tmp_463;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_463 += (0.5 + B1(p,MFe(gI2),MVZ))*Conj(CpbarFeVZFePL(gO2,gI2))*
         CpbarFeVZFePL(gO1,gI2);
   }
   tmp_462 += tmp_463;
   result += (-1) * tmp_462;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fe_PL_heavy_rotated(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_464;
   std::complex<double> tmp_465;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_466;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_466 += B1(p,MFe(gI2),MHm(gI1))*Conj(CpbarFeconjHmFePL(gO2,
            gI1,gI2))*CpbarFeconjHmFePL(gO1,gI1,gI2);
      }
      tmp_465 += tmp_466;
   }
   tmp_464 += tmp_465;
   result += (-0.5) * tmp_464;
   std::complex<double> tmp_467;
   std::complex<double> tmp_468;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_469;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_469 += B1(p,MFv(gI2),Mhh(gI1))*Conj(CpbarFehhFvPL(gO2,gI1,
            gI2))*CpbarFehhFvPL(gO1,gI1,gI2);
      }
      tmp_468 += tmp_469;
   }
   tmp_467 += tmp_468;
   result += (-0.5) * tmp_467;
   std::complex<double> tmp_470;
   std::complex<double> tmp_471;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_472;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_472 += B1(p,MFv(gI1),MAh(gI2))*Conj(CpbarFeFvAhPL(gO2,gI1,
            gI2))*CpbarFeFvAhPL(gO1,gI1,gI2);
      }
      tmp_471 += tmp_472;
   }
   tmp_470 += tmp_471;
   result += (-0.5) * tmp_470;
   std::complex<double> tmp_473;
   std::complex<double> tmp_474;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_474 += (0.5 + B1(p,MFv(gI2),MVWm))*Conj(CpbarFeVWmFvPR(gO2,gI2))*
         CpbarFeVWmFvPR(gO1,gI2);
   }
   tmp_473 += tmp_474;
   result += (-1) * tmp_473;
   std::complex<double> tmp_475;
   std::complex<double> tmp_476;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_476 += (0.5 + B1(p,MFe(gI2),MVZ))*Conj(CpbarFeVZFePR(gO2,gI2))*
         CpbarFeVZFePR(gO1,gI2);
   }
   tmp_475 += tmp_476;
   result += (-1) * tmp_475;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_1_heavy_rotated(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_477;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_478;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_478 += B0(p,MFd(gI2),Mhh(gI1))*Conj(CpbarFuhhFdPL(gO2,gI1,
            gI2))*CpbarFuhhFdPR(gO1,gI1,gI2)*MFd(gI2);
      }
      tmp_477 += tmp_478;
   }
   result += tmp_477;
   std::complex<double> tmp_479;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_480;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_480 += B0(p,MFu(gI2),MHm(gI1))*Conj(CpbarFuconjHmFuPL(gO2,
            gI1,gI2))*CpbarFuconjHmFuPR(gO1,gI1,gI2)*MFu(gI2);
      }
      tmp_479 += tmp_480;
   }
   result += tmp_479;
   std::complex<double> tmp_481;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_482;
      std::complex<double> tmp_483;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_483 += B0(p,MFd(gI1),MAh(gI2))*Conj(CpbarFuFdAhPL(gO2,gI1,
            gI2))*CpbarFuFdAhPR(gO1,gI1,gI2);
      }
      tmp_482 += tmp_483;
      tmp_481 += (MFd(gI1)) * tmp_482;
   }
   result += tmp_481;
   std::complex<double> tmp_484;
   std::complex<double> tmp_485;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_485 += (-0.5 + B0(p,MFd(gI2),MVWm))*Conj(CpbarFuconjVWmFdPR(gO2,
         gI2))*CpbarFuconjVWmFdPL(gO1,gI2)*MFd(gI2);
   }
   tmp_484 += tmp_485;
   result += (-4) * tmp_484;
   std::complex<double> tmp_486;
   std::complex<double> tmp_487;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_487 += (-0.5 + B0(p,MFu(gI2),0))*Conj(CpbarFuVPFuPR(gO2,gI2))*
         CpbarFuVPFuPL(gO1,gI2)*MFu(gI2);
   }
   tmp_486 += tmp_487;
   result += (-4) * tmp_486;
   std::complex<double> tmp_488;
   std::complex<double> tmp_489;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_489 += (-0.5 + B0(p,MFu(gI2),MVZ))*Conj(CpbarFuVZFuPR(gO2,gI2))*
         CpbarFuVZFuPL(gO1,gI2)*MFu(gI2);
   }
   tmp_488 += tmp_489;
   result += (-4) * tmp_488;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_PR_heavy_rotated(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_490;
   std::complex<double> tmp_491;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_492;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_492 += B1(p,MFu(gI2),MHm(gI1))*Conj(CpbarFuconjHmFuPR(gO2,
            gI1,gI2))*CpbarFuconjHmFuPR(gO1,gI1,gI2);
      }
      tmp_491 += tmp_492;
   }
   tmp_490 += tmp_491;
   result += (-0.5) * tmp_490;
   std::complex<double> tmp_493;
   std::complex<double> tmp_494;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_495;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_495 += B1(p,MFd(gI2),Mhh(gI1))*Conj(CpbarFuhhFdPR(gO2,gI1,
            gI2))*CpbarFuhhFdPR(gO1,gI1,gI2);
      }
      tmp_494 += tmp_495;
   }
   tmp_493 += tmp_494;
   result += (-0.5) * tmp_493;
   std::complex<double> tmp_496;
   std::complex<double> tmp_497;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_498;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_498 += B1(p,MFd(gI1),MAh(gI2))*Conj(CpbarFuFdAhPR(gO2,gI1,
            gI2))*CpbarFuFdAhPR(gO1,gI1,gI2);
      }
      tmp_497 += tmp_498;
   }
   tmp_496 += tmp_497;
   result += (-0.5) * tmp_496;
   std::complex<double> tmp_499;
   std::complex<double> tmp_500;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_500 += (0.5 + B1(p,MFd(gI2),MVWm))*Conj(CpbarFuconjVWmFdPL(gO2,gI2
         ))*CpbarFuconjVWmFdPL(gO1,gI2);
   }
   tmp_499 += tmp_500;
   result += (-1) * tmp_499;
   std::complex<double> tmp_501;
   std::complex<double> tmp_502;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_502 += (0.5 + B1(p,MFu(gI2),0))*Conj(CpbarFuVPFuPL(gO2,gI2))*
         CpbarFuVPFuPL(gO1,gI2);
   }
   tmp_501 += tmp_502;
   result += (-1) * tmp_501;
   std::complex<double> tmp_503;
   std::complex<double> tmp_504;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_504 += (0.5 + B1(p,MFu(gI2),MVZ))*Conj(CpbarFuVZFuPL(gO2,gI2))*
         CpbarFuVZFuPL(gO1,gI2);
   }
   tmp_503 += tmp_504;
   result += (-1) * tmp_503;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_PL_heavy_rotated(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_505;
   std::complex<double> tmp_506;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_507;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_507 += B1(p,MFu(gI2),MHm(gI1))*Conj(CpbarFuconjHmFuPL(gO2,
            gI1,gI2))*CpbarFuconjHmFuPL(gO1,gI1,gI2);
      }
      tmp_506 += tmp_507;
   }
   tmp_505 += tmp_506;
   result += (-0.5) * tmp_505;
   std::complex<double> tmp_508;
   std::complex<double> tmp_509;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_510;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_510 += B1(p,MFd(gI2),Mhh(gI1))*Conj(CpbarFuhhFdPL(gO2,gI1,
            gI2))*CpbarFuhhFdPL(gO1,gI1,gI2);
      }
      tmp_509 += tmp_510;
   }
   tmp_508 += tmp_509;
   result += (-0.5) * tmp_508;
   std::complex<double> tmp_511;
   std::complex<double> tmp_512;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_513;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_513 += B1(p,MFd(gI1),MAh(gI2))*Conj(CpbarFuFdAhPL(gO2,gI1,
            gI2))*CpbarFuFdAhPL(gO1,gI1,gI2);
      }
      tmp_512 += tmp_513;
   }
   tmp_511 += tmp_512;
   result += (-0.5) * tmp_511;
   std::complex<double> tmp_514;
   std::complex<double> tmp_515;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_515 += (0.5 + B1(p,MFd(gI2),MVWm))*Conj(CpbarFuconjVWmFdPR(gO2,gI2
         ))*CpbarFuconjVWmFdPR(gO1,gI2);
   }
   tmp_514 += tmp_515;
   result += (-1) * tmp_514;
   std::complex<double> tmp_516;
   std::complex<double> tmp_517;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_517 += (0.5 + B1(p,MFu(gI2),0))*Conj(CpbarFuVPFuPR(gO2,gI2))*
         CpbarFuVPFuPR(gO1,gI2);
   }
   tmp_516 += tmp_517;
   result += (-1) * tmp_516;
   std::complex<double> tmp_518;
   std::complex<double> tmp_519;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_519 += (0.5 + B1(p,MFu(gI2),MVZ))*Conj(CpbarFuVZFuPR(gO2,gI2))*
         CpbarFuVZFuPR(gO1,gI2);
   }
   tmp_518 += tmp_519;
   result += (-1) * tmp_518;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_1_heavy(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_520;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_521;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_521 += B0(p,MFd(gI2),Mhh(gI1))*Conj(CpbarUFuhhFdPL(gO2,gI1,
            gI2))*CpbarUFuhhFdPR(gO1,gI1,gI2)*MFd(gI2);
      }
      tmp_520 += tmp_521;
   }
   result += tmp_520;
   std::complex<double> tmp_522;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_523;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_523 += B0(p,MFu(gI2),MHm(gI1))*Conj(CpbarUFuconjHmFuPL(gO2,
            gI1,gI2))*CpbarUFuconjHmFuPR(gO1,gI1,gI2)*MFu(gI2);
      }
      tmp_522 += tmp_523;
   }
   result += tmp_522;
   std::complex<double> tmp_524;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_525;
      std::complex<double> tmp_526;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_526 += B0(p,MFd(gI1),MAh(gI2))*Conj(CpbarUFuFdAhPL(gO2,gI1,
            gI2))*CpbarUFuFdAhPR(gO1,gI1,gI2);
      }
      tmp_525 += tmp_526;
      tmp_524 += (MFd(gI1)) * tmp_525;
   }
   result += tmp_524;
   std::complex<double> tmp_527;
   std::complex<double> tmp_528;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_528 += (-0.5 + B0(p,MFd(gI2),MVWm))*Conj(CpbarUFuconjVWmFdPR(gO2,
         gI2))*CpbarUFuconjVWmFdPL(gO1,gI2)*MFd(gI2);
   }
   tmp_527 += tmp_528;
   result += (-4) * tmp_527;
   std::complex<double> tmp_529;
   std::complex<double> tmp_530;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_530 += (-0.5 + B0(p,MFu(gI2),0))*Conj(CpbarUFuVPFuPR(gO2,gI2))*
         CpbarUFuVPFuPL(gO1,gI2)*MFu(gI2);
   }
   tmp_529 += tmp_530;
   result += (-4) * tmp_529;
   std::complex<double> tmp_531;
   std::complex<double> tmp_532;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_532 += (-0.5 + B0(p,MFu(gI2),MVZ))*Conj(CpbarUFuVZFuPR(gO2,gI2))*
         CpbarUFuVZFuPL(gO1,gI2)*MFu(gI2);
   }
   tmp_531 += tmp_532;
   result += (-4) * tmp_531;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_PR_heavy(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_533;
   std::complex<double> tmp_534;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_535;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_535 += B1(p,MFu(gI2),MHm(gI1))*Conj(CpbarUFuconjHmFuPR(gO2,
            gI1,gI2))*CpbarUFuconjHmFuPR(gO1,gI1,gI2);
      }
      tmp_534 += tmp_535;
   }
   tmp_533 += tmp_534;
   result += (-0.5) * tmp_533;
   std::complex<double> tmp_536;
   std::complex<double> tmp_537;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_538;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_538 += B1(p,MFd(gI2),Mhh(gI1))*Conj(CpbarUFuhhFdPR(gO2,gI1,
            gI2))*CpbarUFuhhFdPR(gO1,gI1,gI2);
      }
      tmp_537 += tmp_538;
   }
   tmp_536 += tmp_537;
   result += (-0.5) * tmp_536;
   std::complex<double> tmp_539;
   std::complex<double> tmp_540;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_541;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_541 += B1(p,MFd(gI1),MAh(gI2))*Conj(CpbarUFuFdAhPR(gO2,gI1,
            gI2))*CpbarUFuFdAhPR(gO1,gI1,gI2);
      }
      tmp_540 += tmp_541;
   }
   tmp_539 += tmp_540;
   result += (-0.5) * tmp_539;
   std::complex<double> tmp_542;
   std::complex<double> tmp_543;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_543 += (0.5 + B1(p,MFd(gI2),MVWm))*Conj(CpbarUFuconjVWmFdPL(gO2,
         gI2))*CpbarUFuconjVWmFdPL(gO1,gI2);
   }
   tmp_542 += tmp_543;
   result += (-1) * tmp_542;
   std::complex<double> tmp_544;
   std::complex<double> tmp_545;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_545 += (0.5 + B1(p,MFu(gI2),0))*Conj(CpbarUFuVPFuPL(gO2,gI2))*
         CpbarUFuVPFuPL(gO1,gI2);
   }
   tmp_544 += tmp_545;
   result += (-1) * tmp_544;
   std::complex<double> tmp_546;
   std::complex<double> tmp_547;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_547 += (0.5 + B1(p,MFu(gI2),MVZ))*Conj(CpbarUFuVZFuPL(gO2,gI2))*
         CpbarUFuVZFuPL(gO1,gI2);
   }
   tmp_546 += tmp_547;
   result += (-1) * tmp_546;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::self_energy_Fu_PL_heavy(double p , unsigned gO1, unsigned gO2) const
{
   std::complex<double> result;

   std::complex<double> tmp_548;
   std::complex<double> tmp_549;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_550;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_550 += B1(p,MFu(gI2),MHm(gI1))*Conj(CpbarUFuconjHmFuPL(gO2,
            gI1,gI2))*CpbarUFuconjHmFuPL(gO1,gI1,gI2);
      }
      tmp_549 += tmp_550;
   }
   tmp_548 += tmp_549;
   result += (-0.5) * tmp_548;
   std::complex<double> tmp_551;
   std::complex<double> tmp_552;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      std::complex<double> tmp_553;
      for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
         tmp_553 += B1(p,MFd(gI2),Mhh(gI1))*Conj(CpbarUFuhhFdPL(gO2,gI1,
            gI2))*CpbarUFuhhFdPL(gO1,gI1,gI2);
      }
      tmp_552 += tmp_553;
   }
   tmp_551 += tmp_552;
   result += (-0.5) * tmp_551;
   std::complex<double> tmp_554;
   std::complex<double> tmp_555;
   for (unsigned gI1 = 0; gI1 < 3; ++gI1) {
      std::complex<double> tmp_556;
      for (unsigned gI2 = 0; gI2 < 2; ++gI2) {
         tmp_556 += B1(p,MFd(gI1),MAh(gI2))*Conj(CpbarUFuFdAhPL(gO2,gI1,
            gI2))*CpbarUFuFdAhPL(gO1,gI1,gI2);
      }
      tmp_555 += tmp_556;
   }
   tmp_554 += tmp_555;
   result += (-0.5) * tmp_554;
   std::complex<double> tmp_557;
   std::complex<double> tmp_558;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_558 += (0.5 + B1(p,MFd(gI2),MVWm))*Conj(CpbarUFuconjVWmFdPR(gO2,
         gI2))*CpbarUFuconjVWmFdPR(gO1,gI2);
   }
   tmp_557 += tmp_558;
   result += (-1) * tmp_557;
   std::complex<double> tmp_559;
   std::complex<double> tmp_560;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_560 += (0.5 + B1(p,MFu(gI2),0))*Conj(CpbarUFuVPFuPR(gO2,gI2))*
         CpbarUFuVPFuPR(gO1,gI2);
   }
   tmp_559 += tmp_560;
   result += (-1) * tmp_559;
   std::complex<double> tmp_561;
   std::complex<double> tmp_562;
   for (unsigned gI2 = 0; gI2 < 3; ++gI2) {
      tmp_562 += (0.5 + B1(p,MFu(gI2),MVZ))*Conj(CpbarUFuVZFuPR(gO2,gI2))*
         CpbarUFuVZFuPR(gO1,gI2);
   }
   tmp_561 += tmp_562;
   result += (-1) * tmp_561;

   return result * oneOver16PiSqr;

}

std::complex<double> CLASSNAME::tadpole_hh(unsigned gO1) const
{
   std::complex<double> result;

   result += A0(MVWm)*CpUhhbargWmCgWmC(gO1);
   result += A0(MVWm)*CpUhhbargWmgWm(gO1);
   result += A0(MVZ)*CpUhhbargZgZ(gO1);
   std::complex<double> tmp_563;
   std::complex<double> tmp_564;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_564 += A0(MAh(gI1))*CpUhhAhAh(gO1,gI1,gI1);
   }
   tmp_563 += tmp_564;
   result += (-0.5) * tmp_563;
   std::complex<double> tmp_565;
   std::complex<double> tmp_566;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_566 += A0(MHm(gI1))*CpUhhconjHmHm(gO1,gI1,gI1);
   }
   tmp_565 += tmp_566;
   result += (-1) * tmp_565;
   std::complex<double> tmp_567;
   std::complex<double> tmp_568;
   for (unsigned gI1 = 0; gI1 < 2; ++gI1) {
      tmp_568 += A0(Mhh(gI1))*CpUhhhhhh(gO1,gI1,gI1);
   }
   tmp_567 += tmp_568;
   result += (-0.5) * tmp_567;
   result += 4*CpUhhconjVWmVWm(gO1)*(A0(MVWm) - 0.5*Sqr(MVWm));
   result += 2*CpUhhVZVZ(gO1)*(A0(MVZ) - 0.5*Sqr(MVZ));

   return result * oneOver16PiSqr;

}










void CLASSNAME::calculate_MVG_pole()
{
   // diagonalization with medium precision
   PHYSICAL(MVG) = 0.;
}

void CLASSNAME::calculate_MFv_pole()
{
   // diagonalization with medium precision
   PHYSICAL(MFv).setConstant(0.);
}

void CLASSNAME::calculate_MVP_pole()
{
   // diagonalization with medium precision
   PHYSICAL(MVP) = 0.;
}

void CLASSNAME::calculate_MVZ_pole()
{
   if (!force_output && problems.is_tachyon(VZ))
      return;

   // diagonalization with medium precision
   const double M_tree(Sqr(MVZ));
   const double p = MVZ;
   const double self_energy = Re(self_energy_VZ(p));
   const double mass_sqr = M_tree - self_energy;

   if (mass_sqr < 0.)
      problems.flag_tachyon(VZ);

   PHYSICAL(MVZ) = AbsSqrt(mass_sqr);
}

void CLASSNAME::calculate_Mhh_pole()
{
   if (!force_output && problems.is_tachyon(hh))
      return;

   // diagonalization with high precision
   unsigned iteration = 0;
   double diff = 0.0;
   decltype(Mhh) old_Mhh(Mhh), new_Mhh(Mhh);

   do {
      Eigen::Matrix<double,2,2> self_energy;
      const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_hh());

      for (unsigned es = 0; es < 2; ++es) {
         const double p = Abs(old_Mhh(es));
         for (unsigned i1 = 0; i1 < 2; ++i1) {
            for (unsigned i2 = i1; i2 < 2; ++i2) {
               self_energy(i1,i2) = Re(self_energy_hh(p,i1,i2
                  ));
            }
         }

         Symmetrize(self_energy);
         const Eigen::Matrix<double,2,2> M_loop(M_tree -
            self_energy);
         Eigen::Array<double,2,1> eigen_values;
         Eigen::Matrix<double,2,2> mix_ZH;
         #ifdef CHECK_EIGENVALUE_ERROR
            double eigenvalue_error;
            fs_diagonalize_hermitian(M_loop, eigen_values,
               mix_ZH, eigenvalue_error);
            problems.flag_bad_mass(THDM_II_info::hh,
               eigenvalue_error > precision * Abs(eigen_values(0)));
         #else
            fs_diagonalize_hermitian(M_loop, eigen_values,
               mix_ZH);
         #endif

         PHYSICAL(Mhh(es)) = SignedAbsSqrt(eigen_values(es));
         if (es == 0)
            PHYSICAL(ZH) = mix_ZH;
      }

      new_Mhh = PHYSICAL(Mhh);
      diff = MaxRelDiff(new_Mhh, old_Mhh);
      old_Mhh = new_Mhh;
      iteration++;
   } while (diff > precision
            && iteration < number_of_mass_iterations);

   if (diff > precision)
      problems.flag_no_pole_mass_convergence(THDM_II_info::hh);
   else
      problems.unflag_no_pole_mass_convergence(THDM_II_info::hh);
}

void CLASSNAME::calculate_MAh_pole()
{
   if (!force_output && problems.is_tachyon(Ah))
      return;

   // diagonalization with high precision
   unsigned iteration = 0;
   double diff = 0.0;
   decltype(MAh) old_MAh(MAh), new_MAh(MAh);

   do {
      Eigen::Matrix<double,2,2> self_energy;
      const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Ah());

      for (unsigned es = 0; es < 2; ++es) {
         const double p = Abs(old_MAh(es));
         for (unsigned i1 = 0; i1 < 2; ++i1) {
            for (unsigned i2 = i1; i2 < 2; ++i2) {
               self_energy(i1,i2) = Re(self_energy_Ah(p,i1,i2
                  ));
            }
         }

         Symmetrize(self_energy);
         const Eigen::Matrix<double,2,2> M_loop(M_tree -
            self_energy);
         Eigen::Array<double,2,1> eigen_values;
         Eigen::Matrix<double,2,2> mix_ZA;
         #ifdef CHECK_EIGENVALUE_ERROR
            double eigenvalue_error;
            fs_diagonalize_hermitian(M_loop, eigen_values,
               mix_ZA, eigenvalue_error);
            problems.flag_bad_mass(THDM_II_info::Ah,
               eigenvalue_error > precision * Abs(eigen_values(0)));
         #else
            fs_diagonalize_hermitian(M_loop, eigen_values,
               mix_ZA);
         #endif

         PHYSICAL(MAh(es)) = SignedAbsSqrt(eigen_values(es));
         if (es == 1)
            PHYSICAL(ZA) = mix_ZA;
      }

      new_MAh = PHYSICAL(MAh);
      diff = MaxRelDiff(new_MAh, old_MAh);
      old_MAh = new_MAh;
      iteration++;
   } while (diff > precision
            && iteration < number_of_mass_iterations);

   if (diff > precision)
      problems.flag_no_pole_mass_convergence(THDM_II_info::Ah);
   else
      problems.unflag_no_pole_mass_convergence(THDM_II_info::Ah);
}

void CLASSNAME::calculate_MHm_pole()
{
   if (!force_output && problems.is_tachyon(Hm))
      return;

   // diagonalization with medium precision
   Eigen::Matrix<double,2,2> self_energy;
   const Eigen::Matrix<double,2,2> M_tree(get_mass_matrix_Hm());

   for (unsigned es = 0; es < 2; ++es) {
      const double p = Abs(MHm(es));
      for (unsigned i1 = 0; i1 < 2; ++i1) {
         for (unsigned i2 = i1; i2 < 2; ++i2) {
            self_energy(i1,i2) = Re(self_energy_Hm(p,i1,i2));
         }
      }

      Symmetrize(self_energy);
      const Eigen::Matrix<double,2,2> M_loop(M_tree - self_energy);
      Eigen::Array<double,2,1> eigen_values;
      Eigen::Matrix<double,2,2> mix_ZP;
      #ifdef CHECK_EIGENVALUE_ERROR
         double eigenvalue_error;
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZP,
            eigenvalue_error);
         problems.flag_bad_mass(THDM_II_info::Hm, eigenvalue_error
            > precision * Abs(eigen_values(0)));
      #else
         fs_diagonalize_hermitian(M_loop, eigen_values, mix_ZP);
      #endif

      PHYSICAL(MHm(es)) = SignedAbsSqrt(eigen_values(es));
      if (es == 1)
         PHYSICAL(ZP) = mix_ZP;
   }
}

void CLASSNAME::calculate_MFd_pole()
{
   // diagonalization with medium precision
   Eigen::Matrix<double,3,3> self_energy_1;
   Eigen::Matrix<double,3,3> self_energy_PL;
   Eigen::Matrix<double,3,3> self_energy_PR;
   const Eigen::Matrix<double,3,3> M_tree(get_mass_matrix_Fd());
   for (unsigned es = 0; es < 3; ++es) {
      const double p = Abs(MFd(es));
      for (unsigned i1 = 0; i1 < 3; ++i1) {
         for (unsigned i2 = 0; i2 < 3; ++i2) {
            self_energy_1(i1,i2)  = Re(self_energy_Fd_1(p,i1,i2)
               );
            self_energy_PL(i1,i2) = Re(self_energy_Fd_PL(p,i1,i2
               ));
            self_energy_PR(i1,i2) = Re(self_energy_Fd_PR(p,i1,i2
               ));
         }
      }
      const Eigen::Matrix<double,3,3> delta_M(- self_energy_PR *
         M_tree - M_tree * self_energy_PL - self_energy_1);
      const Eigen::Matrix<double,3,3> M_loop(M_tree + delta_M);
      Eigen::Array<double,3,1> eigen_values;
      decltype(Vd) mix_Vd;
      decltype(Ud) mix_Ud;
   #ifdef CHECK_EIGENVALUE_ERROR
      double eigenvalue_error;
      fs_svd(M_loop, eigen_values, mix_Vd, mix_Ud, eigenvalue_error);
      problems.flag_bad_mass(THDM_II_info::Fd, eigenvalue_error >
         precision * Abs(eigen_values(0)));
   #else
      fs_svd(M_loop, eigen_values, mix_Vd, mix_Ud);
   #endif
      if (es == 0) {
         PHYSICAL(Vd) = mix_Vd;
         PHYSICAL(Ud) = mix_Ud;
      }
      PHYSICAL(MFd(es)) = Abs(eigen_values(es));
   }
}

void CLASSNAME::calculate_MFu_pole()
{
   // diagonalization with medium precision
   const bool add_2loop_corrections = pole_mass_loop_order > 1 &&
      TOP_2LOOP_CORRECTION_QCD;
   const double currentScale = get_scale();

   const double qcd_1l = -0.008443431970194815*(4. - 3.*Log(Sqr(MFu(2))
      /Sqr(currentScale)))*Sqr(g3);

   double qcd_2l = 0.;

   if (add_2loop_corrections) {
      qcd_2l = -0.006995771808874528*Power(g3,4) -
         0.004518101565212638*Power(g3,4)*Log(Sqr(currentScale)/Sqr(MFu(2))) -
         0.0008822328500119351*Power(g3,4)*Sqr(Log(Power(currentScale,2)/Sqr(
         MFu(2))));
   }

   Eigen::Matrix<double,3,3> self_energy_1;
   Eigen::Matrix<double,3,3> self_energy_PL;
   Eigen::Matrix<double,3,3> self_energy_PR;
   const Eigen::Matrix<double,3,3> M_tree(get_mass_matrix_Fu());
   for (unsigned es = 0; es < 3; ++es) {
      const double p = Abs(MFu(es));
      for (unsigned i1 = 0; i1 < 3; ++i1) {
         for (unsigned i2 = 0; i2 < 3; ++i2) {
            if (i1 == 2 && i2 == 2) {
               self_energy_1(i1,i2)  = Re(
                  self_energy_Fu_1_heavy(p,i1,i2));
               self_energy_PL(i1,i2) = Re(
                  self_energy_Fu_PL_heavy(p,i1,i2));
               self_energy_PR(i1,i2) = Re(
                  self_energy_Fu_PR_heavy(p,i1,i2));
            } else {
               self_energy_1(i1,i2)  = Re(self_energy_Fu_1(p,
                  i1,i2));
               self_energy_PL(i1,i2) = Re(self_energy_Fu_PL(p
                  ,i1,i2));
               self_energy_PR(i1,i2) = Re(self_energy_Fu_PR(p
                  ,i1,i2));
            }
         }
      }
      Eigen::Matrix<double,3,3> delta_M(- self_energy_PR * M_tree -
         M_tree * self_energy_PL - self_energy_1);
      delta_M(2,2) -= M_tree(2,2) * (qcd_1l + qcd_2l);
      const Eigen::Matrix<double,3,3> M_loop(M_tree + delta_M);
      Eigen::Array<double,3,1> eigen_values;
      decltype(Vu) mix_Vu;
      decltype(Uu) mix_Uu;
   #ifdef CHECK_EIGENVALUE_ERROR
      double eigenvalue_error;
      fs_svd(M_loop, eigen_values, mix_Vu, mix_Uu, eigenvalue_error);
      problems.flag_bad_mass(THDM_II_info::Fu, eigenvalue_error >
         precision * Abs(eigen_values(0)));
   #else
      fs_svd(M_loop, eigen_values, mix_Vu, mix_Uu);
   #endif
      if (es == 0) {
         PHYSICAL(Vu) = mix_Vu;
         PHYSICAL(Uu) = mix_Uu;
      }
      PHYSICAL(MFu(es)) = Abs(eigen_values(es));
   }
}

void CLASSNAME::calculate_MFe_pole()
{
   // diagonalization with medium precision
   Eigen::Matrix<double,3,3> self_energy_1;
   Eigen::Matrix<double,3,3> self_energy_PL;
   Eigen::Matrix<double,3,3> self_energy_PR;
   const Eigen::Matrix<double,3,3> M_tree(get_mass_matrix_Fe());
   for (unsigned es = 0; es < 3; ++es) {
      const double p = Abs(MFe(es));
      for (unsigned i1 = 0; i1 < 3; ++i1) {
         for (unsigned i2 = 0; i2 < 3; ++i2) {
            self_energy_1(i1,i2)  = Re(self_energy_Fe_1(p,i1,i2)
               );
            self_energy_PL(i1,i2) = Re(self_energy_Fe_PL(p,i1,i2
               ));
            self_energy_PR(i1,i2) = Re(self_energy_Fe_PR(p,i1,i2
               ));
         }
      }
      const Eigen::Matrix<double,3,3> delta_M(- self_energy_PR *
         M_tree - M_tree * self_energy_PL - self_energy_1);
      const Eigen::Matrix<double,3,3> M_loop(M_tree + delta_M);
      Eigen::Array<double,3,1> eigen_values;
      decltype(Ve) mix_Ve;
      decltype(Ue) mix_Ue;
   #ifdef CHECK_EIGENVALUE_ERROR
      double eigenvalue_error;
      fs_svd(M_loop, eigen_values, mix_Ve, mix_Ue, eigenvalue_error);
      problems.flag_bad_mass(THDM_II_info::Fe, eigenvalue_error >
         precision * Abs(eigen_values(0)));
   #else
      fs_svd(M_loop, eigen_values, mix_Ve, mix_Ue);
   #endif
      if (es == 0) {
         PHYSICAL(Ve) = mix_Ve;
         PHYSICAL(Ue) = mix_Ue;
      }
      PHYSICAL(MFe(es)) = Abs(eigen_values(es));
   }
}

void CLASSNAME::calculate_MVWm_pole()
{
   if (!force_output && problems.is_tachyon(VWm))
      return;

   // diagonalization with medium precision
   const double M_tree(Sqr(MVWm));
   const double p = MVWm;
   const double self_energy = Re(self_energy_VWm(p));
   const double mass_sqr = M_tree - self_energy;

   if (mass_sqr < 0.)
      problems.flag_tachyon(VWm);

   PHYSICAL(MVWm) = AbsSqrt(mass_sqr);
}

double CLASSNAME::calculate_MVWm_pole(double p)
{
   if (!force_output && problems.is_tachyon(VWm))
      return 0.;

   const double self_energy = Re(self_energy_VWm(p));
   const double mass_sqr = Sqr(MVWm) - self_energy;

   if (mass_sqr < 0.)
      problems.flag_tachyon(VWm);

   return AbsSqrt(mass_sqr);
}

double CLASSNAME::calculate_MVZ_pole(double p)
{
   if (!force_output && problems.is_tachyon(VZ))
      return 0.;

   const double self_energy = Re(self_energy_VZ(p));
   const double mass_sqr = Sqr(MVZ) - self_energy;

   if (mass_sqr < 0.)
      problems.flag_tachyon(VZ);

   return AbsSqrt(mass_sqr);
}


double CLASSNAME::calculate_MFv_DRbar(double, int) const
{
   return 0.0;
}

double CLASSNAME::calculate_MFe_DRbar(double m_sm_msbar, int idx) const
{
   const double p = m_sm_msbar;
   const double self_energy_1  = Re(self_energy_Fe_1_heavy_rotated(p, idx
      , idx));
   const double self_energy_PL = Re(self_energy_Fe_PL_heavy_rotated(p,
      idx, idx));
   const double self_energy_PR = Re(self_energy_Fe_PR_heavy_rotated(p,
      idx, idx));
   const double drbar_conversion = 1;
   const double m_sm_drbar = m_sm_msbar * drbar_conversion;

   const double m_susy_drbar = m_sm_drbar + self_energy_1 + m_sm_drbar *
      (self_energy_PL + self_energy_PR);

   return m_susy_drbar;
}

double CLASSNAME::calculate_MFu_DRbar(double m_pole, int idx) const
{
   const double p = m_pole;
   const double self_energy_1  = Re(self_energy_Fu_1_heavy_rotated(p, idx
      , idx));
   const double self_energy_PL = Re(self_energy_Fu_PL_heavy_rotated(p,
      idx, idx));
   const double self_energy_PR = Re(self_energy_Fu_PR_heavy_rotated(p,
      idx, idx));

   const double currentScale = get_scale();
   const double qcd_1l = -0.008443431970194815*(4. - 3.*Log(Sqr(MFu(idx))
      /Sqr(currentScale)))*Sqr(g3);
   double qcd_2l = 0., qcd_3l = 0.;

   if (get_thresholds() > 1) {
      qcd_2l = -0.005855107113909601*Power(g3,4) -
         0.0028071045227652486*Power(g3,4)*Log(Sqr(currentScale)/Sqr(MFu(idx)))
         - 0.00024060895909416413*Power(g3,4)*Sqr(Log(Power(currentScale,2)
         /Sqr(MFu(idx))));
   }

   if (get_thresholds() > 2) {
      qcd_3l = -0.0013067805969741943*Power(g3,6) -
         0.0004114970933517977*Power(g3,6)*Log(Sqr(currentScale)/Sqr(MFu(idx)))
         - 5.078913443827405e-6*Power(g3,6)*Power(Log(Sqr(currentScale)/Sqr(
         MFu(idx))),3) - 0.00007466002762426286*Power(g3,6)*Sqr(Log(Power(
         currentScale,2)/Sqr(MFu(idx))));
   }

   const double m_susy_drbar = m_pole + self_energy_1 + m_pole * (
      self_energy_PL + self_energy_PR + qcd_1l + qcd_2l + qcd_3l);

   return m_susy_drbar;
}

double CLASSNAME::calculate_MFd_DRbar(double m_sm_msbar, int idx) const
{
   const double p = m_sm_msbar;
   const double self_energy_1  = Re(self_energy_Fd_1_heavy_rotated(p, idx
      , idx));
   const double self_energy_PL = Re(self_energy_Fd_PL_heavy_rotated(p,
      idx, idx));
   const double self_energy_PR = Re(self_energy_Fd_PR_heavy_rotated(p,
      idx, idx));
   const double m_tree = MFd(idx);
   const double drbar_conversion = 1;
   const double m_sm_drbar = m_sm_msbar * drbar_conversion;

   const double m_susy_drbar = m_sm_drbar / (1.0 - self_energy_1/m_tree -
      self_energy_PL - self_energy_PR);

   return m_susy_drbar;
}

double CLASSNAME::calculate_MVP_DRbar(double)
{
   return 0.0;
}

double CLASSNAME::calculate_MVZ_DRbar(double m_pole)
{
   const double p = m_pole;
   const double self_energy = Re(self_energy_VZ(p));
   const double mass_sqr = Sqr(m_pole) + self_energy;

   if (mass_sqr < 0.) {
      problems.flag_tachyon(VZ);
      return m_pole;
   }

   return AbsSqrt(mass_sqr);
}

double CLASSNAME::calculate_MVWm_DRbar(double m_pole)
{
   const double p = m_pole;
   const double self_energy = Re(self_energy_VWm(p));
   const double mass_sqr = Sqr(m_pole) + self_energy;

   if (mass_sqr < 0.) {
      problems.flag_tachyon(VWm);
      return m_pole;
   }

   return AbsSqrt(mass_sqr);
}


double CLASSNAME::Betax() const
{
   return ArcSin(Abs(ZP(0,1)));
}

double CLASSNAME::Alpha() const
{
   return ArcCos(ZH(0,1));
}

double CLASSNAME::ThetaW() const
{
   return ArcCos(Abs(ZZ(0,0)));
}


std::ostream& operator<<(std::ostream& ostr, const THDM_II_mass_eigenstates& model)
{
   model.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
