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

// File generated at Thu 10 May 2018 14:43:40

#include "HSSUSY_soft_parameters.hpp"
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

const int HSSUSY_soft_parameters::numberOfParameters;

HSSUSY_soft_parameters::HSSUSY_soft_parameters(const HSSUSY_input_parameters& input_)
   : HSSUSY_susy_parameters(input_)
{
   set_number_of_parameters(numberOfParameters);
}

HSSUSY_soft_parameters::HSSUSY_soft_parameters(
   const HSSUSY_susy_parameters& susy_model
   , double mu2_, double v_

)
   : HSSUSY_susy_parameters(susy_model)
   , mu2(mu2_), v(v_)

{
   set_number_of_parameters(numberOfParameters);
}

Eigen::ArrayXd HSSUSY_soft_parameters::beta() const
{
   return calc_beta().get().unaryExpr(Chop<double>(get_zero_threshold()));
}

HSSUSY_soft_parameters HSSUSY_soft_parameters::calc_beta(int loops) const
{
   double beta_mu2 = 0.;
   double beta_v = 0.;

   if (loops > 0) {
      const auto TRACE_STRUCT = CALCULATE_TRACES(loops);

      beta_mu2 += calc_beta_mu2_1_loop(TRACE_STRUCT);
      beta_v += calc_beta_v_1_loop(TRACE_STRUCT);

      if (loops > 1) {
         beta_mu2 += calc_beta_mu2_2_loop(TRACE_STRUCT);
         beta_v += calc_beta_v_2_loop(TRACE_STRUCT);

         if (loops > 2) {
         #ifdef ENABLE_THREADS
            {
               auto fut_mu2 = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_mu2_3_loop(TRACE_STRUCT); });

               beta_mu2 += fut_mu2.get();

            }
         #else
            beta_mu2 += calc_beta_mu2_3_loop(TRACE_STRUCT);
         #endif

         }
      }
   }


   const HSSUSY_susy_parameters susy_betas(HSSUSY_susy_parameters::calc_beta(loops));

   return HSSUSY_soft_parameters(susy_betas, beta_mu2, beta_v);
}

HSSUSY_soft_parameters HSSUSY_soft_parameters::calc_beta() const
{
   return calc_beta(get_loops());
}

void HSSUSY_soft_parameters::clear()
{
   HSSUSY_susy_parameters::clear();

   mu2 = 0.;
   v = 0.;

}

Eigen::ArrayXd HSSUSY_soft_parameters::get() const
{
   Eigen::ArrayXd pars(HSSUSY_susy_parameters::get());
   pars.conservativeResize(numberOfParameters);

   pars(31) = mu2;
   pars(32) = v;


   return pars;
}

void HSSUSY_soft_parameters::print(std::ostream& ostr) const
{
   HSSUSY_susy_parameters::print(ostr);
   ostr << "soft parameters at Q = " << get_scale() << ":\n";
   ostr << "mu2 = " << mu2 << '\n';
   ostr << "v = " << v << '\n';

}

void HSSUSY_soft_parameters::set(const Eigen::ArrayXd& pars)
{
   HSSUSY_susy_parameters::set(pars);

   mu2 = pars(31);
   v = pars(32);

}

HSSUSY_soft_parameters::Soft_traces HSSUSY_soft_parameters::calc_soft_traces(int loops) const
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

std::ostream& operator<<(std::ostream& ostr, const HSSUSY_soft_parameters& soft_pars)
{
   soft_pars.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
