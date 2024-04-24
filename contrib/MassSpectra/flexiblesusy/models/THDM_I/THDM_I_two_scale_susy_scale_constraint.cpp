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

// File generated at Tue 7 Apr 2020 02:34:05

#include "THDM_I_two_scale_susy_scale_constraint.hpp"
#include "THDM_I_two_scale_model.hpp"
#include "wrappers.hpp"
#include "logger.hpp"
#include "error.hpp"
#include "ew_input.hpp"
#include "gsl_utils.hpp"
#include "minimizer.hpp"
#include "raii.hpp"
#include "root_finder.hpp"
#include "threshold_loop_functions.hpp"

#include <cmath>

namespace flexiblesusy {

#define DERIVEDPARAMETER(p) model->p()
#define EXTRAPARAMETER(p) model->get_##p()
#define INPUTPARAMETER(p) model->get_input().p
#define MODELPARAMETER(p) model->get_##p()
#define PHASE(p) model->get_##p()
#define BETAPARAMETER(p) beta_functions.get_##p()
#define BETAPARAMETER1(l,p) beta_functions_##l##L.get_##p()
#define BETA(p) beta_##p
#define BETA1(l,p) beta_##l##L_##p
#define LowEnergyConstant(p) Electroweak_constants::p
#define MZPole qedqcd.displayPoleMZ()
#define STANDARDDEVIATION(p) Electroweak_constants::Error_##p
#define Pole(p) model->get_physical().p
#define SCALE model->get_scale()
#define THRESHOLD static_cast<int>(model->get_thresholds())
#define MODEL model
#define MODELCLASSNAME THDM_I<Two_scale>

THDM_I_susy_scale_constraint<Two_scale>::THDM_I_susy_scale_constraint(
   THDM_I<Two_scale>* model_, const softsusy::QedQcd& qedqcd_)
   : model(model_)
   , qedqcd(qedqcd_)
{
   initialize();
}

void THDM_I_susy_scale_constraint<Two_scale>::apply()
{
   check_model_ptr();



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

double THDM_I_susy_scale_constraint<Two_scale>::get_scale() const
{
   return scale;
}

double THDM_I_susy_scale_constraint<Two_scale>::get_initial_scale_guess() const
{
   return initial_scale_guess;
}

const THDM_I_input_parameters& THDM_I_susy_scale_constraint<Two_scale>::get_input_parameters() const
{
   check_model_ptr();

   return model->get_input();
}

THDM_I<Two_scale>* THDM_I_susy_scale_constraint<Two_scale>::get_model() const
{
   return model;
}

void THDM_I_susy_scale_constraint<Two_scale>::set_model(Model* model_)
{
   model = cast_model<THDM_I<Two_scale>*>(model_);
}

void THDM_I_susy_scale_constraint<Two_scale>::set_sm_parameters(
   const softsusy::QedQcd& qedqcd_)
{
   qedqcd = qedqcd_;
}

const softsusy::QedQcd& THDM_I_susy_scale_constraint<Two_scale>::get_sm_parameters() const
{
   return qedqcd;
}

void THDM_I_susy_scale_constraint<Two_scale>::clear()
{
   scale = 0.;
   initial_scale_guess = 0.;
   model = nullptr;
   qedqcd = softsusy::QedQcd();
}

void THDM_I_susy_scale_constraint<Two_scale>::initialize()
{
   check_model_ptr();

   const auto Qin = INPUTPARAMETER(Qin);

   initial_scale_guess = Qin;

   scale = initial_scale_guess;
}

void THDM_I_susy_scale_constraint<Two_scale>::update_scale()
{
   check_model_ptr();

   const auto Qin = INPUTPARAMETER(Qin);

   scale = Qin;


}

void THDM_I_susy_scale_constraint<Two_scale>::check_model_ptr() const
{
   if (!model)
      throw SetupError("THDM_I_susy_scale_constraint<Two_scale>: "
                       "model pointer is zero!");
}

} // namespace flexiblesusy
