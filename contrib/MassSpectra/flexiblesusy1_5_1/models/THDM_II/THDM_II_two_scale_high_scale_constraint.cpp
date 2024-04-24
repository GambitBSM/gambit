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

// File generated at Wed 29 Mar 2017 15:35:52

#include "THDM_II_two_scale_high_scale_constraint.hpp"
#include "THDM_II_two_scale_model.hpp"
#include "wrappers.hpp"
#include "logger.hpp"
#include "ew_input.hpp"
#include "gsl_utils.hpp"
#include "minimizer.hpp"
#include "root_finder.hpp"
#include "threshold_loop_functions.hpp"
#include "numerics2.hpp"

#include <cassert>
#include <cmath>
#include <cerrno>
#include <cstring>

namespace flexiblesusy {

#define DERIVEDPARAMETER(p) model->p()
#define INPUTPARAMETER(p) model->get_input().p
#define MODELPARAMETER(p) model->get_##p()
#define PHASE(p) model->get_##p()
#define BETAPARAMETER(p) beta_functions.get_##p()
#define BETA(p) beta_##p
#define LowEnergyConstant(p) Electroweak_constants::p
#define MZPole Electroweak_constants::MZ
#define STANDARDDEVIATION(p) Electroweak_constants::Error_##p
#define Pole(p) model->get_physical().p
#define SCALE model->get_scale()
#define THRESHOLD static_cast<int>(model->get_thresholds())
#define MODEL model
#define MODELCLASSNAME THDM_II<Two_scale>

THDM_II_high_scale_constraint<Two_scale>::THDM_II_high_scale_constraint()
   : Constraint<Two_scale>()
   , scale(0.)
   , initial_scale_guess(0.)
   , model(0)
{
}

THDM_II_high_scale_constraint<Two_scale>::THDM_II_high_scale_constraint(
   THDM_II<Two_scale>* model_)
   : Constraint<Two_scale>()
   , model(model_)
{
   initialize();
}

THDM_II_high_scale_constraint<Two_scale>::~THDM_II_high_scale_constraint()
{
}

void THDM_II_high_scale_constraint<Two_scale>::apply()
{
   assert(model && "Error: THDM_II_high_scale_constraint::apply():"
          " model pointer must not be zero");



   update_scale();



   check_non_perturbative();


}

bool THDM_II_high_scale_constraint<Two_scale>::check_non_perturbative()
{
   bool problem = false;

   const auto g1 = MODELPARAMETER(g1);
   const auto g2 = MODELPARAMETER(g2);
   const auto g3 = MODELPARAMETER(g3);
   const auto Lambda6 = MODELPARAMETER(Lambda6);
   const auto Lambda5 = MODELPARAMETER(Lambda5);
   const auto Lambda7 = MODELPARAMETER(Lambda7);
   const auto Lambda1 = MODELPARAMETER(Lambda1);
   const auto Lambda4 = MODELPARAMETER(Lambda4);
   const auto Lambda3 = MODELPARAMETER(Lambda3);
   const auto Lambda2 = MODELPARAMETER(Lambda2);
   const auto Yd = MODELPARAMETER(Yd);
   const auto Ye = MODELPARAMETER(Ye);
   const auto Yu = MODELPARAMETER(Yu);

   if (MaxAbsValue(g1) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("g1", MaxAbsValue(g1), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("g1");
   }
   if (MaxAbsValue(g2) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("g2", MaxAbsValue(g2), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("g2");
   }
   if (MaxAbsValue(g3) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("g3", MaxAbsValue(g3), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("g3");
   }
   if (MaxAbsValue(Lambda6) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("Lambda6", MaxAbsValue(Lambda6), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("Lambda6");
   }
   if (MaxAbsValue(Lambda5) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("Lambda5", MaxAbsValue(Lambda5), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("Lambda5");
   }
   if (MaxAbsValue(Lambda7) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("Lambda7", MaxAbsValue(Lambda7), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("Lambda7");
   }
   if (MaxAbsValue(Lambda1) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("Lambda1", MaxAbsValue(Lambda1), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("Lambda1");
   }
   if (MaxAbsValue(Lambda4) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("Lambda4", MaxAbsValue(Lambda4), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("Lambda4");
   }
   if (MaxAbsValue(Lambda3) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("Lambda3", MaxAbsValue(Lambda3), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("Lambda3");
   }
   if (MaxAbsValue(Lambda2) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("Lambda2", MaxAbsValue(Lambda2), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("Lambda2");
   }
   if (MaxAbsValue(Yd) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("Yd", MaxAbsValue(Yd), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("Yd");
   }
   if (MaxAbsValue(Ye) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("Ye", MaxAbsValue(Ye), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("Ye");
   }
   if (MaxAbsValue(Yu) > 3.5449077018110318) {
      problem = true;
      model->get_problems().flag_non_perturbative_parameter("Yu", MaxAbsValue(Yu), model->get_scale(), 3.5449077018110318);
   } else {
      model->get_problems().unflag_non_perturbative_parameter("Yu");
   }


   return problem;
}

double THDM_II_high_scale_constraint<Two_scale>::get_scale() const
{
   return scale;
}

double THDM_II_high_scale_constraint<Two_scale>::get_initial_scale_guess() const
{
   return initial_scale_guess;
}

const THDM_II_input_parameters& THDM_II_high_scale_constraint<Two_scale>::get_input_parameters() const
{
   return model->get_input();
}

THDM_II<Two_scale>* THDM_II_high_scale_constraint<Two_scale>::get_model() const
{
   return model;
}

void THDM_II_high_scale_constraint<Two_scale>::set_model(Two_scale_model* model_)
{
   model = cast_model<THDM_II<Two_scale>*>(model_);
}

void THDM_II_high_scale_constraint<Two_scale>::set_scale(double s)
{
   scale = s;
}

void THDM_II_high_scale_constraint<Two_scale>::clear()
{
   scale = 0.;
   initial_scale_guess = 0.;
   model = NULL;
}

void THDM_II_high_scale_constraint<Two_scale>::initialize()
{
   assert(model && "THDM_II_high_scale_constraint<Two_scale>::"
          "initialize(): model pointer is zero.");

   initial_scale_guess = 2.e16;

   scale = initial_scale_guess;
}

void THDM_II_high_scale_constraint<Two_scale>::update_scale()
{
   assert(model && "THDM_II_high_scale_constraint<Two_scale>::"
          "update_scale(): model pointer is zero.");

   const double currentScale = model->get_scale();
   const THDM_II_soft_parameters beta_functions(model->calc_beta());

   scale = 20000000000000000;


   if (errno == ERANGE) {
#ifdef ENABLE_VERBOSE
      ERROR("THDM_II_high_scale_constraint<Two_scale>: Overflow error"
            " during calculation of high scale: " << strerror(errno) << '\n'
            << "   current scale = " << currentScale << '\n'
            << "   new scale = " << scale << '\n'
            << "   resetting scale to " << get_initial_scale_guess());
#endif
      scale = get_initial_scale_guess();
      errno = 0;
   }


}

} // namespace flexiblesusy
