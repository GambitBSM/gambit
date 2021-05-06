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

// File generated at Tue 7 Apr 2020 02:32:00

#include "THDM_I_soft_parameters.hpp"
#include "config.h"
#include "global_thread_pool.hpp"
#include "wrappers.hpp"
#include "functors.hpp"

#include <iostream>

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT soft_traces
#define TRACE_STRUCT_TYPE Soft_traces
#define CALCULATE_TRACES(l) calc_soft_traces(l);

const int THDM_I_soft_parameters::numberOfParameters;

THDM_I_soft_parameters::THDM_I_soft_parameters(const THDM_I_input_parameters& input_)
   : THDM_I_susy_parameters(input_)
{
   set_number_of_parameters(numberOfParameters);
}

THDM_I_soft_parameters::THDM_I_soft_parameters(
   const THDM_I_susy_parameters& susy_model
   , double M122_, double M112_, double M222_, double v1_, double v2_

)
   : THDM_I_susy_parameters(susy_model)
   , M122(M122_), M112(M112_), M222(M222_), v1(v1_), v2(v2_)

{
   set_number_of_parameters(numberOfParameters);
}

Eigen::ArrayXd THDM_I_soft_parameters::beta() const
{
   return calc_beta().get().unaryExpr(Chop<double>(get_zero_threshold()));
}

THDM_I_soft_parameters THDM_I_soft_parameters::calc_beta(int loops) const
{
   double beta_M122 = 0.;
   double beta_M112 = 0.;
   double beta_M222 = 0.;
   double beta_v1 = 0.;
   double beta_v2 = 0.;

   if (loops > 0) {
      const auto TRACE_STRUCT = CALCULATE_TRACES(loops);

      beta_M122 += calc_beta_M122_1_loop(TRACE_STRUCT);
      beta_M112 += calc_beta_M112_1_loop(TRACE_STRUCT);
      beta_M222 += calc_beta_M222_1_loop(TRACE_STRUCT);
      beta_v1 += calc_beta_v1_1_loop(TRACE_STRUCT);
      beta_v2 += calc_beta_v2_1_loop(TRACE_STRUCT);

      if (loops > 1) {
         beta_M122 += calc_beta_M122_2_loop(TRACE_STRUCT);
         beta_M112 += calc_beta_M112_2_loop(TRACE_STRUCT);
         beta_M222 += calc_beta_M222_2_loop(TRACE_STRUCT);
         beta_v1 += calc_beta_v1_2_loop(TRACE_STRUCT);
         beta_v2 += calc_beta_v2_2_loop(TRACE_STRUCT);

         if (loops > 2) {
         #ifdef ENABLE_THREADS
            {

            }
         #else
         #endif

         }
      }
   }


   const THDM_I_susy_parameters susy_betas(THDM_I_susy_parameters::calc_beta(loops));

   return THDM_I_soft_parameters(susy_betas, beta_M122, beta_M112, beta_M222, beta_v1, beta_v2);
}

THDM_I_soft_parameters THDM_I_soft_parameters::calc_beta() const
{
   return calc_beta(get_loops());
}

void THDM_I_soft_parameters::clear()
{
   THDM_I_susy_parameters::clear();

   M122 = 0.;
   M112 = 0.;
   M222 = 0.;
   v1 = 0.;
   v2 = 0.;

}

Eigen::ArrayXd THDM_I_soft_parameters::get() const
{
   Eigen::ArrayXd pars(THDM_I_susy_parameters::get());
   pars.conservativeResize(numberOfParameters);

   pars(37) = M122;
   pars(38) = M112;
   pars(39) = M222;
   pars(40) = v1;
   pars(41) = v2;


   return pars;
}

void THDM_I_soft_parameters::print(std::ostream& ostr) const
{
   THDM_I_susy_parameters::print(ostr);
   ostr << "soft parameters at Q = " << get_scale() << ":\n";
   ostr << "M122 = " << M122 << '\n';
   ostr << "M112 = " << M112 << '\n';
   ostr << "M222 = " << M222 << '\n';
   ostr << "v1 = " << v1 << '\n';
   ostr << "v2 = " << v2 << '\n';

}

void THDM_I_soft_parameters::set(const Eigen::ArrayXd& pars)
{
   THDM_I_susy_parameters::set(pars);

   M122 = pars(37);
   M112 = pars(38);
   M222 = pars(39);
   v1 = pars(40);
   v2 = pars(41);

}

THDM_I_soft_parameters::Soft_traces THDM_I_soft_parameters::calc_soft_traces(int loops) const
{
   Soft_traces soft_traces;

   if (loops > 0) {
      TRACE_STRUCT.traceYdAdjYd = Re((Yd*Yd.adjoint()).trace());
      TRACE_STRUCT.traceYeAdjYe = Re((Ye*Ye.adjoint()).trace());
      TRACE_STRUCT.traceYuAdjYu = Re((Yu*Yu.adjoint()).trace());

   }

   if (loops > 1) {
      TRACE_STRUCT.traceYdAdjYdYdAdjYd = Re((Yd*Yd.adjoint()*Yd*Yd.adjoint())
         .trace());
      TRACE_STRUCT.traceYdAdjYuYuAdjYd = Re((Yd*Yu.adjoint()*Yu*Yd.adjoint())
         .trace());
      TRACE_STRUCT.traceYeAdjYeYeAdjYe = Re((Ye*Ye.adjoint()*Ye*Ye.adjoint())
         .trace());
      TRACE_STRUCT.traceYuAdjYuYuAdjYu = Re((Yu*Yu.adjoint()*Yu*Yu.adjoint())
         .trace());

   }

   if (loops > 2) {

   }

   return soft_traces;
}

std::ostream& operator<<(std::ostream& ostr, const THDM_I_soft_parameters& soft_pars)
{
   soft_pars.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
