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

// File generated at Thu 10 May 2018 15:01:38

#include "NUHMSSM_susy_parameters.hpp"
#include "config.h"
#include "global_thread_pool.hpp"
#include "wrappers.hpp"
#include "functors.hpp"

#include <iostream>

namespace flexiblesusy {

#define CLASSNAME NUHMSSM_susy_parameters
#define INPUT(parameter) input.parameter
#define TRACE_STRUCT susy_traces
#define TRACE_STRUCT_TYPE Susy_traces
#define CALCULATE_TRACES(l) calc_susy_traces(l);

const int NUHMSSM_susy_parameters::numberOfParameters;

NUHMSSM_susy_parameters::NUHMSSM_susy_parameters(const NUHMSSM_input_parameters& input_)
   : input(input_)
{
   set_number_of_parameters(numberOfParameters);
}

NUHMSSM_susy_parameters::NUHMSSM_susy_parameters(
   double scale_, int loops_, int thresholds_,
   const NUHMSSM_input_parameters& input_
   , const Eigen::Matrix<double,3,3>& Yd_, const Eigen::Matrix<double,3,3>& Ye_
   , const Eigen::Matrix<double,3,3>& Yu_, double Mu_, double g1_, double g2_,
   double g3_, double vd_, double vu_

)
   : Beta_function()
   , Yd(Yd_), Ye(Ye_), Yu(Yu_), Mu(Mu_), g1(g1_), g2(g2_), g3(g3_), vd(vd_), vu
   (vu_)

   , input(input_)
{
   set_number_of_parameters(numberOfParameters);
   set_scale(scale_);
   set_loops(loops_);
   set_thresholds(thresholds_);
}

Eigen::ArrayXd NUHMSSM_susy_parameters::beta() const
{
   return calc_beta().get().unaryExpr(Chop<double>(get_zero_threshold()));
}

NUHMSSM_susy_parameters NUHMSSM_susy_parameters::calc_beta(int loops) const
{
   Eigen::Matrix<double,3,3> beta_Yd = Eigen::Matrix<double,3,3>::Zero();
   Eigen::Matrix<double,3,3> beta_Ye = Eigen::Matrix<double,3,3>::Zero();
   Eigen::Matrix<double,3,3> beta_Yu = Eigen::Matrix<double,3,3>::Zero();
   double beta_Mu = 0.;
   double beta_g1 = 0.;
   double beta_g2 = 0.;
   double beta_g3 = 0.;
   double beta_vd = 0.;
   double beta_vu = 0.;

   if (loops > 0) {
      const auto TRACE_STRUCT = CALCULATE_TRACES(loops);

      beta_Yd += calc_beta_Yd_1_loop(TRACE_STRUCT);
      beta_Ye += calc_beta_Ye_1_loop(TRACE_STRUCT);
      beta_Yu += calc_beta_Yu_1_loop(TRACE_STRUCT);
      beta_Mu += calc_beta_Mu_1_loop(TRACE_STRUCT);
      beta_g1 += calc_beta_g1_1_loop(TRACE_STRUCT);
      beta_g2 += calc_beta_g2_1_loop(TRACE_STRUCT);
      beta_g3 += calc_beta_g3_1_loop(TRACE_STRUCT);
      beta_vd += calc_beta_vd_1_loop(TRACE_STRUCT);
      beta_vu += calc_beta_vu_1_loop(TRACE_STRUCT);

      if (loops > 1) {
         beta_Yd += calc_beta_Yd_2_loop(TRACE_STRUCT);
         beta_Ye += calc_beta_Ye_2_loop(TRACE_STRUCT);
         beta_Yu += calc_beta_Yu_2_loop(TRACE_STRUCT);
         beta_Mu += calc_beta_Mu_2_loop(TRACE_STRUCT);
         beta_g1 += calc_beta_g1_2_loop(TRACE_STRUCT);
         beta_g2 += calc_beta_g2_2_loop(TRACE_STRUCT);
         beta_g3 += calc_beta_g3_2_loop(TRACE_STRUCT);
         beta_vd += calc_beta_vd_2_loop(TRACE_STRUCT);
         beta_vu += calc_beta_vu_2_loop(TRACE_STRUCT);

         if (loops > 2) {
         #ifdef ENABLE_THREADS
            {
               auto fut_Yd = global_thread_pool().run_packaged_task
                  ([this, &TRACE_STRUCT](){ return calc_beta_Yd_3_loop(
                  TRACE_STRUCT); });
               auto fut_Ye = global_thread_pool().run_packaged_task
                  ([this, &TRACE_STRUCT](){ return calc_beta_Ye_3_loop(
                  TRACE_STRUCT); });
               auto fut_Yu = global_thread_pool().run_packaged_task
                  ([this, &TRACE_STRUCT](){ return calc_beta_Yu_3_loop(
                  TRACE_STRUCT); });
               auto fut_Mu = global_thread_pool().run_packaged_task
                  ([this, &TRACE_STRUCT](){ return calc_beta_Mu_3_loop(
                  TRACE_STRUCT); });
               auto fut_g1 = global_thread_pool().run_packaged_task
                  ([this, &TRACE_STRUCT](){ return calc_beta_g1_3_loop(
                  TRACE_STRUCT); });
               auto fut_g2 = global_thread_pool().run_packaged_task
                  ([this, &TRACE_STRUCT](){ return calc_beta_g2_3_loop(
                  TRACE_STRUCT); });
               auto fut_g3 = global_thread_pool().run_packaged_task
                  ([this, &TRACE_STRUCT](){ return calc_beta_g3_3_loop(
                  TRACE_STRUCT); });

               beta_Yd += fut_Yd.get();
               beta_Ye += fut_Ye.get();
               beta_Yu += fut_Yu.get();
               beta_Mu += fut_Mu.get();
               beta_g1 += fut_g1.get();
               beta_g2 += fut_g2.get();
               beta_g3 += fut_g3.get();

            }
         #else
            beta_Yd += calc_beta_Yd_3_loop(TRACE_STRUCT);
            beta_Ye += calc_beta_Ye_3_loop(TRACE_STRUCT);
            beta_Yu += calc_beta_Yu_3_loop(TRACE_STRUCT);
            beta_Mu += calc_beta_Mu_3_loop(TRACE_STRUCT);
            beta_g1 += calc_beta_g1_3_loop(TRACE_STRUCT);
            beta_g2 += calc_beta_g2_3_loop(TRACE_STRUCT);
            beta_g3 += calc_beta_g3_3_loop(TRACE_STRUCT);
         #endif

         }
      }
   }


   return NUHMSSM_susy_parameters(get_scale(), loops, get_thresholds(), input,
                    beta_Yd, beta_Ye, beta_Yu, beta_Mu, beta_g1, beta_g2, beta_g3, beta_vd, beta_vu);
}

NUHMSSM_susy_parameters NUHMSSM_susy_parameters::calc_beta() const
{
   return calc_beta(get_loops());
}

void NUHMSSM_susy_parameters::clear()
{
   reset();
   Yd = Eigen::Matrix<double,3,3>::Zero();
   Ye = Eigen::Matrix<double,3,3>::Zero();
   Yu = Eigen::Matrix<double,3,3>::Zero();
   Mu = 0.;
   g1 = 0.;
   g2 = 0.;
   g3 = 0.;
   vd = 0.;
   vu = 0.;

}

Eigen::Matrix<double,3,3> CLASSNAME::get_SqSq() const
{
   Eigen::Matrix<double,3,3> anomDim;

   anomDim = (oneOver16PiSqr*(Yd.adjoint()*Yd + Yu.adjoint()*Yu -
      0.03333333333333333*(Sqr(g1) + 45*Sqr(g2) + 80*Sqr(g3))*UNITMATRIX(3)))
      .real();

   if (get_loops() > 1) {
      anomDim += (twoLoop*(0.8*Sqr(g1)*(Yu.adjoint()*Yu) - 2*(
         Yd.adjoint()*Yd*Yd.adjoint()*Yd) - 2*(Yu.adjoint()*Yu*Yu.adjoint()*Yu)
         + Yd.adjoint()*Yd*(0.4*Sqr(g1) - 3*(Yd*Yd.adjoint()).trace() - (Ye*
         Ye.adjoint()).trace()) - 3*(Yu.adjoint()*Yu)*(Yu*Yu.adjoint()).trace()
         + (0.22111111111111112*Quad(g1) + 3.75*Quad(g2) - 0.8888888888888888*
         Quad(g3) + 8*Sqr(g2)*Sqr(g3) + 0.011111111111111112*Sqr(g1)*(9*Sqr(g2)
         + 16*Sqr(g3)))*UNITMATRIX(3))).real();
   }

   return anomDim;
}

Eigen::Matrix<double,3,3> CLASSNAME::get_SlSl() const
{
   Eigen::Matrix<double,3,3> anomDim;

   anomDim = (oneOver16PiSqr*(Ye.adjoint()*Ye - 0.3*(Sqr(g1) + 5*Sqr(g2))
      *UNITMATRIX(3))).real();

   if (get_loops() > 1) {
      anomDim += (twoLoop*(-2*(Ye.adjoint()*Ye*Ye.adjoint()*Ye) +
         Ye.adjoint()*Ye*(1.2*Sqr(g1) - 3*(Yd*Yd.adjoint()).trace() - (Ye*
         Ye.adjoint()).trace()) + 0.03*(69*Quad(g1) + 125*Quad(g2) + 30*Sqr(g1)
         *Sqr(g2))*UNITMATRIX(3))).real();
   }

   return anomDim;
}

double CLASSNAME::get_SHdSHd() const
{
   double anomDim = 0;

   anomDim = Re(oneOver16PiSqr*(-0.3*(Sqr(g1) + 5*Sqr(g2)) + 3*(Yd*
      Yd.adjoint()).trace() + (Ye*Ye.adjoint()).trace()));

   if (get_loops() > 1) {
      anomDim += Re(twoLoop*(2.07*Quad(g1) + 3.75*Quad(g2) + 0.9*Sqr(
         g1)*Sqr(g2) - 0.4*(Sqr(g1) - 40*Sqr(g3))*(Yd*Yd.adjoint()).trace() +
         1.2*Sqr(g1)*(Ye*Ye.adjoint()).trace() - 9*(Yd*Yd.adjoint()*Yd*
         Yd.adjoint()).trace() - 3*(Yd*Yu.adjoint()*Yu*Yd.adjoint()).trace() -
         3*(Ye*Ye.adjoint()*Ye*Ye.adjoint()).trace()));
   }

   return anomDim;
}

double CLASSNAME::get_SHuSHu() const
{
   double anomDim = 0;

   anomDim = Re(-0.3*oneOver16PiSqr*(Sqr(g1) + 5*Sqr(g2) - 10*(Yu*
      Yu.adjoint()).trace()));

   if (get_loops() > 1) {
      anomDim += Re(twoLoop*(2.07*Quad(g1) + 3.75*Quad(g2) + 0.9*Sqr(
         g1)*Sqr(g2) + 0.8*(Sqr(g1) + 20*Sqr(g3))*(Yu*Yu.adjoint()).trace() - 3
         *(Yd*Yu.adjoint()*Yu*Yd.adjoint()).trace() - 9*(Yu*Yu.adjoint()*Yu*
         Yu.adjoint()).trace()));
   }

   return anomDim;
}

Eigen::Matrix<double,3,3> CLASSNAME::get_SdRSdR() const
{
   Eigen::Matrix<double,3,3> anomDim;

   anomDim = (oneOver16PiSqr*(2*(Yd.conjugate()*Yd.transpose()) -
      0.13333333333333333*(Sqr(g1) + 20*Sqr(g3))*UNITMATRIX(3))).real();

   if (get_loops() > 1) {
      anomDim += (twoLoop*(-2*(Yd.conjugate()*Yd.transpose()*
         Yd.conjugate()*Yd.transpose() + Yd.conjugate()*Yu.transpose()*
         Yu.conjugate()*Yd.transpose()) + Yd.conjugate()*Yd.transpose()*(0.4*
         Sqr(g1) + 6*Sqr(g2) - 6*(Yd*Yd.adjoint()).trace() - 2*(Ye*Ye.adjoint()
         ).trace()) + 0.008888888888888889*(101*Quad(g1) - 100*Quad(g3) + 80*
         Sqr(g1)*Sqr(g3))*UNITMATRIX(3))).real();
   }

   return anomDim;
}

Eigen::Matrix<double,3,3> CLASSNAME::get_SuRSuR() const
{
   Eigen::Matrix<double,3,3> anomDim;

   anomDim = (oneOver16PiSqr*(2*(Yu.conjugate()*Yu.transpose()) -
      0.5333333333333333*(Sqr(g1) + 5*Sqr(g3))*UNITMATRIX(3))).real();

   if (get_loops() > 1) {
      anomDim += (twoLoop*(-2*(Yu.conjugate()*Yd.transpose()*
         Yd.conjugate()*Yu.transpose() + Yu.conjugate()*Yu.transpose()*
         Yu.conjugate()*Yu.transpose()) + Yu.conjugate()*Yu.transpose()*(-0.4*
         Sqr(g1) + 6*Sqr(g2) - 6*(Yu*Yu.adjoint()).trace()) +
         0.035555555555555556*(107*Quad(g1) - 25*Quad(g3) + 80*Sqr(g1)*Sqr(g3))
         *UNITMATRIX(3))).real();
   }

   return anomDim;
}

Eigen::Matrix<double,3,3> CLASSNAME::get_SeRSeR() const
{
   Eigen::Matrix<double,3,3> anomDim;

   anomDim = (oneOver16PiSqr*(2*(Ye.conjugate()*Ye.transpose()) - 1.2*Sqr
      (g1)*UNITMATRIX(3))).real();

   if (get_loops() > 1) {
      anomDim += (twoLoop*(-2*(Ye.conjugate()*Ye.transpose()*
         Ye.conjugate()*Ye.transpose()) + Ye.conjugate()*Ye.transpose()*(-1.2*
         Sqr(g1) + 6*Sqr(g2) - 6*(Yd*Yd.adjoint()).trace() - 2*(Ye*Ye.adjoint()
         ).trace()) + 9.36*Quad(g1)*UNITMATRIX(3))).real();
   }

   return anomDim;
}


Eigen::ArrayXd NUHMSSM_susy_parameters::get() const
{
   Eigen::ArrayXd pars(numberOfParameters);

   pars(0) = Yd(0,0);
   pars(1) = Yd(0,1);
   pars(2) = Yd(0,2);
   pars(3) = Yd(1,0);
   pars(4) = Yd(1,1);
   pars(5) = Yd(1,2);
   pars(6) = Yd(2,0);
   pars(7) = Yd(2,1);
   pars(8) = Yd(2,2);
   pars(9) = Ye(0,0);
   pars(10) = Ye(0,1);
   pars(11) = Ye(0,2);
   pars(12) = Ye(1,0);
   pars(13) = Ye(1,1);
   pars(14) = Ye(1,2);
   pars(15) = Ye(2,0);
   pars(16) = Ye(2,1);
   pars(17) = Ye(2,2);
   pars(18) = Yu(0,0);
   pars(19) = Yu(0,1);
   pars(20) = Yu(0,2);
   pars(21) = Yu(1,0);
   pars(22) = Yu(1,1);
   pars(23) = Yu(1,2);
   pars(24) = Yu(2,0);
   pars(25) = Yu(2,1);
   pars(26) = Yu(2,2);
   pars(27) = Mu;
   pars(28) = g1;
   pars(29) = g2;
   pars(30) = g3;
   pars(31) = vd;
   pars(32) = vu;


   return pars;
}

void NUHMSSM_susy_parameters::print(std::ostream& ostr) const
{
   ostr << "susy parameters at Q = " << get_scale() << ":\n";
   ostr << "Yd = " << Yd << '\n';
   ostr << "Ye = " << Ye << '\n';
   ostr << "Yu = " << Yu << '\n';
   ostr << "Mu = " << Mu << '\n';
   ostr << "g1 = " << g1 << '\n';
   ostr << "g2 = " << g2 << '\n';
   ostr << "g3 = " << g3 << '\n';
   ostr << "vd = " << vd << '\n';
   ostr << "vu = " << vu << '\n';

}

void NUHMSSM_susy_parameters::set(const Eigen::ArrayXd& pars)
{
   Yd(0,0) = pars(0);
   Yd(0,1) = pars(1);
   Yd(0,2) = pars(2);
   Yd(1,0) = pars(3);
   Yd(1,1) = pars(4);
   Yd(1,2) = pars(5);
   Yd(2,0) = pars(6);
   Yd(2,1) = pars(7);
   Yd(2,2) = pars(8);
   Ye(0,0) = pars(9);
   Ye(0,1) = pars(10);
   Ye(0,2) = pars(11);
   Ye(1,0) = pars(12);
   Ye(1,1) = pars(13);
   Ye(1,2) = pars(14);
   Ye(2,0) = pars(15);
   Ye(2,1) = pars(16);
   Ye(2,2) = pars(17);
   Yu(0,0) = pars(18);
   Yu(0,1) = pars(19);
   Yu(0,2) = pars(20);
   Yu(1,0) = pars(21);
   Yu(1,1) = pars(22);
   Yu(1,2) = pars(23);
   Yu(2,0) = pars(24);
   Yu(2,1) = pars(25);
   Yu(2,2) = pars(26);
   Mu = pars(27);
   g1 = pars(28);
   g2 = pars(29);
   g3 = pars(30);
   vd = pars(31);
   vu = pars(32);

}

const NUHMSSM_input_parameters& NUHMSSM_susy_parameters::get_input() const
{
   return input;
}

NUHMSSM_input_parameters& NUHMSSM_susy_parameters::get_input()
{
   return input;
}

void NUHMSSM_susy_parameters::set_input_parameters(const NUHMSSM_input_parameters& input_)
{
   input = input_;
}

NUHMSSM_susy_parameters::Susy_traces NUHMSSM_susy_parameters::calc_susy_traces(int loops) const
{
   Susy_traces susy_traces;

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
      TRACE_STRUCT.traceAdjYdYd = Re((Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYeYe = Re((Ye.adjoint()*Ye).trace());
      TRACE_STRUCT.traceAdjYuYu = Re((Yu.adjoint()*Yu).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdYd = Re((Yd.adjoint()*Yd*Yd.adjoint()*Yd)
         .trace());
      TRACE_STRUCT.traceAdjYeYeAdjYeYe = Re((Ye.adjoint()*Ye*Ye.adjoint()*Ye)
         .trace());
      TRACE_STRUCT.traceAdjYuYuAdjYdYd = Re((Yu.adjoint()*Yu*Yd.adjoint()*Yd)
         .trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYu = Re((Yu.adjoint()*Yu*Yu.adjoint()*Yu)
         .trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdYdAdjYdYd = Re((Yd.adjoint()*Yd*Yd.adjoint()*
         Yd*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYdYd = Re((Yd.adjoint()*Yd*Yu.adjoint()*
         Yu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYeYeAdjYeYeAdjYeYe = Re((Ye.adjoint()*Ye*Ye.adjoint()*
         Ye*Ye.adjoint()*Ye).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYdYd = Re((Yu.adjoint()*Yu*Yu.adjoint()*
         Yu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYuYu = Re((Yu.adjoint()*Yu*Yu.adjoint()*
         Yu*Yu.adjoint()*Yu).trace());

   }

   return susy_traces;
}

std::ostream& operator<<(std::ostream& ostr, const NUHMSSM_susy_parameters& susy_pars)
{
   susy_pars.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
