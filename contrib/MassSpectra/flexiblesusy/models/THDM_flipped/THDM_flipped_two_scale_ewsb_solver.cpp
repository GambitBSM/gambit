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

// File generated at Tue 7 Apr 2020 14:56:54

/**
 * @file THDM_flipped_two_scale_ewsb_solver.cpp
 *
 * @brief implementation of EWSB solver for two-scale iteration
 *
 * This file was generated at Tue 7 Apr 2020 14:56:54 with FlexibleSUSY
 * 2.0.1 (git commit: unknown) and SARAH 4.13.0 .
 */

#include "THDM_flipped_two_scale_ewsb_solver.hpp"
#include "THDM_flipped_mass_eigenstates.hpp"
#include "logger.hpp"
#include "root_finder.hpp"
#include "fixed_point_iterator.hpp"
#include "raii.hpp"

#include <memory>

namespace flexiblesusy {

#define INPUT(parameter) model.get_input().parameter
#define LOCALINPUT(parameter) INPUT(parameter)
#define INPUTPARAMETER(parameter) LOCALINPUT(parameter)
#define MODELPARAMETER(parameter) model.get_##parameter()
#define EXTRAPARAMETER(parameter) model.get_##parameter()
#define DERIVEDPARAMETER(parameter) model.parameter()
#define PHASE(p) MODELPARAMETER(p)
#define LowEnergyConstant(p) Electroweak_constants::p
#define CLASSNAME THDM_flipped_ewsb_solver<Two_scale>

/**
 * This method solves the EWSB conditions iteratively, trying several
 * root finding methods until a solution is found.
 */
int CLASSNAME::solve_iteratively(THDM_flipped_mass_eigenstates& model_to_solve)
{
   auto model = model_to_solve;
   model.set_ewsb_loop_order(loop_order);

   auto ewsb_stepper = [this, model](const EWSB_vector_t& ewsb_pars) mutable -> EWSB_vector_t {
      const double M112 = ewsb_pars(0);
      const double M222 = ewsb_pars(1);

      model.set_M112(M112);
      model.set_M222(M222);


      if (this->loop_order > 0)
         model.calculate_DRbar_masses();

      return this->ewsb_step(model);
   };

   auto tadpole_stepper = [this, model](const EWSB_vector_t& ewsb_pars) mutable -> EWSB_vector_t {
      const double M112 = ewsb_pars(0);
      const double M222 = ewsb_pars(1);

      model.set_M112(M112);
      model.set_M222(M222);


      if (this->loop_order > 0)
         model.calculate_DRbar_masses();

      return this->tadpole_equations(model);
   };

   std::unique_ptr<EWSB_solver> solvers[] = {
      std::unique_ptr<EWSB_solver>(new Fixed_point_iterator<number_of_ewsb_equations, fixed_point_iterator::Convergence_tester_relative>(ewsb_stepper, number_of_iterations, fixed_point_iterator::Convergence_tester_relative(precision))),
      std::unique_ptr<EWSB_solver>(new Root_finder<number_of_ewsb_equations>(tadpole_stepper, number_of_iterations, precision, Root_finder<number_of_ewsb_equations>::GSLHybridS)),
      std::unique_ptr<EWSB_solver>(new Root_finder<number_of_ewsb_equations>(tadpole_stepper, number_of_iterations, precision, Root_finder<number_of_ewsb_equations>::GSLBroyden))
   };

   const auto x_init(initial_guess(model_to_solve));

   VERBOSE_MSG("\t\tSolving EWSB equations ...");
   VERBOSE_MSG("\t\tInitial guess: x_init = " << x_init.transpose());

   int status;
   for (auto& solver: solvers) {
      VERBOSE_MSG("\t\t\tStarting EWSB iteration using " << solver->name());
      status = solve_iteratively_with(model_to_solve, solver.get(), x_init);
      if (status == EWSB_solver::SUCCESS) {
         VERBOSE_MSG("\t\t\t" << solver->name() << " finished successfully!");
         break;
      }
#ifdef ENABLE_VERBOSE
      else {
         WARNING("\t\t\t" << solver->name() << " could not find a solution!"
                 " (requested precision: " << precision << ")");
      }
#endif
   }

   if (status == EWSB_solver::SUCCESS) {
      model_to_solve.get_problems().unflag_no_ewsb();
   } else {
      set_best_ewsb_solution(model_to_solve, std::begin(solvers), std::end(solvers));
      model_to_solve.get_problems().flag_no_ewsb();
#ifdef ENABLE_VERBOSE
      WARNING("\t\tCould not find a solution to the EWSB equations!"
              " (requested precision: " << precision << ")");
#endif
   }

   return status;
}

/**
 * Solves EWSB equations with given EWSB solver
 *
 * @param model_to_solve model to solve EWSB conditions for
 * @param solver EWSB solver
 * @param x_init initial values
 *
 * @return status of the EWSB solver
 */
int CLASSNAME::solve_iteratively_with(
   THDM_flipped_mass_eigenstates& model_to_solve, EWSB_solver* solver, const EWSB_vector_t& x_init)
{
   const int status = solver->solve(x_init);

   if (status == EWSB_solver::SUCCESS)
      set_ewsb_solution(model_to_solve, solver);

   return status;
}

/**
 * Sets EWSB output parameters from given solver.
 *
 * @param model model to set EWSB output parameters in
 * @param solver solver
 */
void CLASSNAME::set_ewsb_solution(THDM_flipped_mass_eigenstates& model, const EWSB_solver* solver)
{
   const auto solution = solver->get_solution();

   const double M112 = solution(0);
   const double M222 = solution(1);
   model.set_M112(M112);
   model.set_M222(M222);


   model.calculate_DRbar_masses();
}

/**
 * Sets EWSB output parameters from the solver from the range [first,
 * last), which minimizes the tadpole equations at most.
 *
 * @param model model to set EWSB output parameters in
 * @param first iterator to first solver
 * @param last iterator to last solver
 */
template <typename It>
void CLASSNAME::set_best_ewsb_solution(THDM_flipped_mass_eigenstates& model, It first, It last)
{
   auto ma(model), mb(model);

   const auto best_solver =
      std::min_element(first, last,
                       [this, &ma, &mb](const std::unique_ptr<EWSB_solver>& a, const std::unique_ptr<EWSB_solver>& b) {
                          this->set_ewsb_solution(ma, a.get());
                          this->set_ewsb_solution(mb, b.get());
                          return Total(Abs(Re(ma.tadpole_equations()))) < Total(Abs(Re(mb.tadpole_equations())));
                       });

   VERBOSE_MSG("\t\tUsing best solution from " << (*best_solver)->name());

   set_ewsb_solution(model, best_solver->get());
}

int CLASSNAME::solve_iteratively_at(THDM_flipped_mass_eigenstates& model_to_solve, int l)
{
   // temporarily set `ewsb_loop_order' to `loop_order' and do
   // iteration
   const auto save_loop_order_raii = make_raii_save(loop_order);
   loop_order = l;

   return solve_iteratively(model_to_solve);
}

int CLASSNAME::solve(THDM_flipped_mass_eigenstates& model_to_solve)
{
   if (loop_order == 0) {
      return solve_tree_level(model_to_solve);
   }
   return solve_iteratively_at(model_to_solve, loop_order);
}

int CLASSNAME::solve_tree_level(THDM_flipped_mass_eigenstates& model)
{
   int error = EWSB_solver::SUCCESS;

   const auto v1 = MODELPARAMETER(v1);
   const auto Lambda1 = MODELPARAMETER(Lambda1);
   const auto M122 = MODELPARAMETER(M122);
   const auto v2 = MODELPARAMETER(v2);
   const auto Lambda6 = MODELPARAMETER(Lambda6);
   const auto Lambda3 = MODELPARAMETER(Lambda3);
   const auto Lambda4 = MODELPARAMETER(Lambda4);
   const auto Lambda5 = MODELPARAMETER(Lambda5);
   const auto Lambda7 = MODELPARAMETER(Lambda7);
   const auto Lambda2 = MODELPARAMETER(Lambda2);

   double M112;
   double M222;

   M112 = Re((0.25*(2*M122*v2 + 2*v2*Conj(M122) - 2*Lambda1*Cube(v1) - Lambda7*
      Cube(v2) - Conj(Lambda7)*Cube(v2) - 3*Lambda6*v2*Sqr(v1) - 3*v2*Conj(Lambda6
      )*Sqr(v1) - 2*Lambda3*v1*Sqr(v2) - 2*Lambda4*v1*Sqr(v2) - Lambda5*v1*Sqr(v2)
      - v1*Conj(Lambda5)*Sqr(v2)))/v1);
   M222 = Re((0.25*(2*M122*v1 + 2*v1*Conj(M122) - Lambda6*Cube(v1) - Conj(
      Lambda6)*Cube(v1) - 2*Lambda2*Cube(v2) - 2*Lambda3*v2*Sqr(v1) - 2*Lambda4*v2
      *Sqr(v1) - Lambda5*v2*Sqr(v1) - v2*Conj(Lambda5)*Sqr(v1) - 3*Lambda7*v1*Sqr(
      v2) - 3*v1*Conj(Lambda7)*Sqr(v2)))/v2);

   const bool is_finite = IsFinite(M112) && IsFinite(M222);

   if (is_finite) {
      model.set_M112(M112);
      model.set_M222(M222);
      model.get_problems().unflag_no_ewsb();
   } else {
      error = EWSB_solver::FAIL;
      model.get_problems().flag_no_ewsb();
   }

   return error;
}

CLASSNAME::EWSB_vector_t CLASSNAME::initial_guess(const THDM_flipped_mass_eigenstates& model) const
{
   EWSB_vector_t x_init(EWSB_vector_t::Zero());

   const auto M112 = MODELPARAMETER(M112);
   const auto M222 = MODELPARAMETER(M222);
   x_init[0] = M112;
   x_init[1] = M222;


   return x_init;
}

CLASSNAME::EWSB_vector_t CLASSNAME::tadpole_equations(const THDM_flipped_mass_eigenstates& model) const
{
   return model.tadpole_equations();
}

/**
 * Calculates EWSB output parameters including loop-corrections.
 *
 * Throws exception of type EEWSBStepFailed if new EWSB parameters are
 * inf or nan.
 *
 * @param model model to use for calculating the EWSB output parameters
 *
 * @return new set of EWSB output parameters
 */
CLASSNAME::EWSB_vector_t CLASSNAME::ewsb_step(const THDM_flipped_mass_eigenstates& model) const
{
   std::array<double, number_of_ewsb_equations> tadpole{};
   EWSB_vector_t ewsb_parameters(EWSB_vector_t::Zero());

   if (loop_order > 0) {
   tadpole[0] += Re(model.tadpole_hh_1loop(0));
   tadpole[1] += Re(model.tadpole_hh_1loop(1));

      if (loop_order > 1) {

      }
   }

   const auto v1 = MODELPARAMETER(v1);
   const auto Lambda1 = MODELPARAMETER(Lambda1);
   const auto M122 = MODELPARAMETER(M122);
   const auto v2 = MODELPARAMETER(v2);
   const auto Lambda6 = MODELPARAMETER(Lambda6);
   const auto Lambda3 = MODELPARAMETER(Lambda3);
   const auto Lambda4 = MODELPARAMETER(Lambda4);
   const auto Lambda5 = MODELPARAMETER(Lambda5);
   const auto Lambda7 = MODELPARAMETER(Lambda7);
   const auto Lambda2 = MODELPARAMETER(Lambda2);
   double M112;
   double M222;

   M112 = Re((0.25*(2*M122*v2 + 2*v2*Conj(M122) - 2*Lambda1*Cube(v1) - Lambda7*
      Cube(v2) - Conj(Lambda7)*Cube(v2) + 4*tadpole[0] - 3*Lambda6*v2*Sqr(v1) - 3*
      v2*Conj(Lambda6)*Sqr(v1) - 2*Lambda3*v1*Sqr(v2) - 2*Lambda4*v1*Sqr(v2) -
      Lambda5*v1*Sqr(v2) - v1*Conj(Lambda5)*Sqr(v2)))/v1);
   M222 = Re((0.25*(2*M122*v1 + 2*v1*Conj(M122) - Lambda6*Cube(v1) - Conj(
      Lambda6)*Cube(v1) - 2*Lambda2*Cube(v2) + 4*tadpole[1] - 2*Lambda3*v2*Sqr(v1)
      - 2*Lambda4*v2*Sqr(v1) - Lambda5*v2*Sqr(v1) - v2*Conj(Lambda5)*Sqr(v1) - 3*
      Lambda7*v1*Sqr(v2) - 3*v1*Conj(Lambda7)*Sqr(v2)))/v2);

   const bool is_finite = IsFinite(M112) && IsFinite(M222);


   if (!is_finite)
      throw EEWSBStepFailed();

   ewsb_parameters[0] = M112;
   ewsb_parameters[1] = M222;


   return ewsb_parameters;
}

} // namespace flexiblesusy
