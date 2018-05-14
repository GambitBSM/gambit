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

// File generated at Thu 10 May 2018 14:42:28

#include "SingletDMZ3_soft_parameters.hpp"
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

const int SingletDMZ3_soft_parameters::numberOfParameters;

SingletDMZ3_soft_parameters::SingletDMZ3_soft_parameters(const SingletDMZ3_input_parameters& input_)
   : SingletDMZ3_susy_parameters(input_)
{
   set_number_of_parameters(numberOfParameters);
}

SingletDMZ3_soft_parameters::SingletDMZ3_soft_parameters(
   const SingletDMZ3_susy_parameters& susy_model
   , double mu3_, double muS_, double muH_, double v_

)
   : SingletDMZ3_susy_parameters(susy_model)
   , mu3(mu3_), muS(muS_), muH(muH_), v(v_)

{
   set_number_of_parameters(numberOfParameters);
}

Eigen::ArrayXd SingletDMZ3_soft_parameters::beta() const
{
   return calc_beta().get().unaryExpr(Chop<double>(get_zero_threshold()));
}

SingletDMZ3_soft_parameters SingletDMZ3_soft_parameters::calc_beta(int loops) const
{
   double beta_mu3 = 0.;
   double beta_muS = 0.;
   double beta_muH = 0.;
   double beta_v = 0.;

   if (loops > 0) {
      const auto TRACE_STRUCT = CALCULATE_TRACES(loops);

      beta_mu3 += calc_beta_mu3_1_loop(TRACE_STRUCT);
      beta_muS += calc_beta_muS_1_loop(TRACE_STRUCT);
      beta_muH += calc_beta_muH_1_loop(TRACE_STRUCT);
      beta_v += calc_beta_v_1_loop(TRACE_STRUCT);

      if (loops > 1) {
         beta_mu3 += calc_beta_mu3_2_loop(TRACE_STRUCT);
         beta_muS += calc_beta_muS_2_loop(TRACE_STRUCT);
         beta_muH += calc_beta_muH_2_loop(TRACE_STRUCT);
         beta_v += calc_beta_v_2_loop(TRACE_STRUCT);

         if (loops > 2) {
         #ifdef ENABLE_THREADS
            {

            }
         #else
         #endif

         }
      }
   }


   const SingletDMZ3_susy_parameters susy_betas(SingletDMZ3_susy_parameters::calc_beta(loops));

   return SingletDMZ3_soft_parameters(susy_betas, beta_mu3, beta_muS, beta_muH, beta_v);
}

SingletDMZ3_soft_parameters SingletDMZ3_soft_parameters::calc_beta() const
{
   return calc_beta(get_loops());
}

void SingletDMZ3_soft_parameters::clear()
{
   SingletDMZ3_susy_parameters::clear();

   mu3 = 0.;
   muS = 0.;
   muH = 0.;
   v = 0.;

}

Eigen::ArrayXd SingletDMZ3_soft_parameters::get() const
{
   Eigen::ArrayXd pars(SingletDMZ3_susy_parameters::get());
   pars.conservativeResize(numberOfParameters);

   pars(33) = mu3;
   pars(34) = muS;
   pars(35) = muH;
   pars(36) = v;


   return pars;
}

void SingletDMZ3_soft_parameters::print(std::ostream& ostr) const
{
   SingletDMZ3_susy_parameters::print(ostr);
   ostr << "soft parameters at Q = " << get_scale() << ":\n";
   ostr << "mu3 = " << mu3 << '\n';
   ostr << "muS = " << muS << '\n';
   ostr << "muH = " << muH << '\n';
   ostr << "v = " << v << '\n';

}

void SingletDMZ3_soft_parameters::set(const Eigen::ArrayXd& pars)
{
   SingletDMZ3_susy_parameters::set(pars);

   mu3 = pars(33);
   muS = pars(34);
   muH = pars(35);
   v = pars(36);

}

SingletDMZ3_soft_parameters::Soft_traces SingletDMZ3_soft_parameters::calc_soft_traces(int loops) const
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

std::ostream& operator<<(std::ostream& ostr, const SingletDMZ3_soft_parameters& soft_pars)
{
   soft_pars.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
