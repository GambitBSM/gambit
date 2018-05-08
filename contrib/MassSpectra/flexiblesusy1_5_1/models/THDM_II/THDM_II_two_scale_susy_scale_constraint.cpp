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

// File generated at Wed 29 Mar 2017 15:35:53

#include "THDM_II_two_scale_susy_scale_constraint.hpp"
#include "THDM_II_two_scale_model.hpp"
#include "wrappers.hpp"
#include "logger.hpp"
#include "ew_input.hpp"
#include "gsl_utils.hpp"
#include "minimizer.hpp"
#include "root_finder.hpp"
#include "threshold_loop_functions.hpp"

#include <cassert>
#include <cmath>

namespace flexiblesusy {

#define DERIVEDPARAMETER(p) model->p()
#define INPUTPARAMETER(p) model->get_input().p
#define MODELPARAMETER(p) model->get_##p()
#define PHASE(p) model->get_##p()
#define BETAPARAMETER(p) beta_functions.get_##p()
#define BETA(p) beta_##p
#define LowEnergyConstant(p) Electroweak_constants::p
#define MZPole qedqcd.displayPoleMZ()
#define STANDARDDEVIATION(p) Electroweak_constants::Error_##p
#define Pole(p) model->get_physical().p
#define SCALE model->get_scale()
#define THRESHOLD static_cast<int>(model->get_thresholds())
#define MODEL model
#define MODELCLASSNAME THDM_II<Two_scale>

THDM_II_susy_scale_constraint<Two_scale>::THDM_II_susy_scale_constraint()
   : Constraint<Two_scale>()
   , scale(0.)
   , initial_scale_guess(0.)
   , model(0)
   , qedqcd()
{
}

THDM_II_susy_scale_constraint<Two_scale>::THDM_II_susy_scale_constraint(
   THDM_II<Two_scale>* model_, const softsusy::QedQcd& qedqcd_)
   : Constraint<Two_scale>()
   , model(model_)
   , qedqcd(qedqcd_)
{
   initialize();
}

THDM_II_susy_scale_constraint<Two_scale>::~THDM_II_susy_scale_constraint()
{
}

void THDM_II_susy_scale_constraint<Two_scale>::apply()
{
   assert(model && "Error: THDM_II_susy_scale_constraint::apply():"
          " model pointer must not be zero");



   model->calculate_DRbar_masses();
   update_scale();

   // apply user-defined susy scale constraints
   const auto Lambda1IN = INPUTPARAMETER(Lambda1IN);
   const auto Lambda2IN = INPUTPARAMETER(Lambda2IN);
   const auto Lambda3IN = INPUTPARAMETER(Lambda3IN);
   const auto Lambda4IN = INPUTPARAMETER(Lambda4IN);
   const auto Lambda5IN = INPUTPARAMETER(Lambda5IN);
   const auto Lambda6IN = INPUTPARAMETER(Lambda6IN);
   const auto Lambda7IN = INPUTPARAMETER(Lambda7IN);
   const auto M122IN = INPUTPARAMETER(M122IN);

   MODEL->set_Lambda1(Re(Lambda1IN));
   MODEL->set_Lambda2(Re(Lambda2IN));
   MODEL->set_Lambda3(Re(Lambda3IN));
   MODEL->set_Lambda4(Re(Lambda4IN));
   MODEL->set_Lambda5(Re(Lambda5IN));
   MODEL->set_Lambda6(Re(Lambda6IN));
   MODEL->set_Lambda7(Re(Lambda7IN));
   MODEL->set_M122(Re(M122IN));
   MODEL->solve_ewsb();


}

double THDM_II_susy_scale_constraint<Two_scale>::get_scale() const
{
   return scale;
}

double THDM_II_susy_scale_constraint<Two_scale>::get_initial_scale_guess() const
{
   return initial_scale_guess;
}

const THDM_II_input_parameters& THDM_II_susy_scale_constraint<Two_scale>::get_input_parameters() const
{
   assert(model && "Error: THDM_II_susy_scale_constraint::"
          "get_input_parameters(): model pointer is zero.");

   return model->get_input();
}

THDM_II<Two_scale>* THDM_II_susy_scale_constraint<Two_scale>::get_model() const
{
   return model;
}

void THDM_II_susy_scale_constraint<Two_scale>::set_model(Two_scale_model* model_)
{
   model = cast_model<THDM_II<Two_scale>*>(model_);
}

void THDM_II_susy_scale_constraint<Two_scale>::set_sm_parameters(
   const softsusy::QedQcd& qedqcd_)
{
   qedqcd = qedqcd_;
}

const softsusy::QedQcd& THDM_II_susy_scale_constraint<Two_scale>::get_sm_parameters() const
{
   return qedqcd;
}

void THDM_II_susy_scale_constraint<Two_scale>::clear()
{
   scale = 0.;
   initial_scale_guess = 0.;
   model = NULL;
   qedqcd = softsusy::QedQcd();
}

void THDM_II_susy_scale_constraint<Two_scale>::initialize()
{
   assert(model && "THDM_II_susy_scale_constraint<Two_scale>::"
          "initialize(): model pointer is zero.");

   const auto QEWSB = INPUTPARAMETER(QEWSB);

   initial_scale_guess = QEWSB;

   scale = initial_scale_guess;
}

void THDM_II_susy_scale_constraint<Two_scale>::update_scale()
{
   assert(model && "THDM_II_susy_scale_constraint<Two_scale>::"
          "update_scale(): model pointer is zero.");

   const auto QEWSB = INPUTPARAMETER(QEWSB);

   scale = QEWSB;


}

} // namespace flexiblesusy
