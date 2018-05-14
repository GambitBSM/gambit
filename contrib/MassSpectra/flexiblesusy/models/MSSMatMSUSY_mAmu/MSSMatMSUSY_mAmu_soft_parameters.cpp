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

// File generated at Thu 10 May 2018 14:25:43

#include "MSSMatMSUSY_mAmu_soft_parameters.hpp"
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

const int MSSMatMSUSY_mAmu_soft_parameters::numberOfParameters;

MSSMatMSUSY_mAmu_soft_parameters::MSSMatMSUSY_mAmu_soft_parameters(const MSSMatMSUSY_mAmu_input_parameters& input_)
   : MSSMatMSUSY_mAmu_susy_parameters(input_)
{
   set_number_of_parameters(numberOfParameters);
}

MSSMatMSUSY_mAmu_soft_parameters::MSSMatMSUSY_mAmu_soft_parameters(
   const MSSMatMSUSY_mAmu_susy_parameters& susy_model
   , const Eigen::Matrix<double,3,3>& TYd_, const Eigen::Matrix<double,3,3>&
   TYe_, const Eigen::Matrix<double,3,3>& TYu_, double BMu_, const
   Eigen::Matrix<double,3,3>& mq2_, const Eigen::Matrix<double,3,3>& ml2_,
   double mHd2_, double mHu2_, const Eigen::Matrix<double,3,3>& md2_, const
   Eigen::Matrix<double,3,3>& mu2_, const Eigen::Matrix<double,3,3>& me2_,
   double MassB_, double MassWB_, double MassG_

)
   : MSSMatMSUSY_mAmu_susy_parameters(susy_model)
   , TYd(TYd_), TYe(TYe_), TYu(TYu_), BMu(BMu_), mq2(mq2_), ml2(ml2_), mHd2(
   mHd2_), mHu2(mHu2_), md2(md2_), mu2(mu2_), me2(me2_), MassB(MassB_), MassWB(
   MassWB_), MassG(MassG_)

{
   set_number_of_parameters(numberOfParameters);
}

Eigen::ArrayXd MSSMatMSUSY_mAmu_soft_parameters::beta() const
{
   return calc_beta().get().unaryExpr(Chop<double>(get_zero_threshold()));
}

MSSMatMSUSY_mAmu_soft_parameters MSSMatMSUSY_mAmu_soft_parameters::calc_beta(int loops) const
{
   Eigen::Matrix<double,3,3> beta_TYd = Eigen::Matrix<double,3,3>::Zero();
   Eigen::Matrix<double,3,3> beta_TYe = Eigen::Matrix<double,3,3>::Zero();
   Eigen::Matrix<double,3,3> beta_TYu = Eigen::Matrix<double,3,3>::Zero();
   double beta_BMu = 0.;
   Eigen::Matrix<double,3,3> beta_mq2 = Eigen::Matrix<double,3,3>::Zero();
   Eigen::Matrix<double,3,3> beta_ml2 = Eigen::Matrix<double,3,3>::Zero();
   double beta_mHd2 = 0.;
   double beta_mHu2 = 0.;
   Eigen::Matrix<double,3,3> beta_md2 = Eigen::Matrix<double,3,3>::Zero();
   Eigen::Matrix<double,3,3> beta_mu2 = Eigen::Matrix<double,3,3>::Zero();
   Eigen::Matrix<double,3,3> beta_me2 = Eigen::Matrix<double,3,3>::Zero();
   double beta_MassB = 0.;
   double beta_MassWB = 0.;
   double beta_MassG = 0.;

   if (loops > 0) {
      const auto TRACE_STRUCT = CALCULATE_TRACES(loops);

      beta_TYd += calc_beta_TYd_1_loop(TRACE_STRUCT);
      beta_TYe += calc_beta_TYe_1_loop(TRACE_STRUCT);
      beta_TYu += calc_beta_TYu_1_loop(TRACE_STRUCT);
      beta_BMu += calc_beta_BMu_1_loop(TRACE_STRUCT);
      beta_mq2 += calc_beta_mq2_1_loop(TRACE_STRUCT);
      beta_ml2 += calc_beta_ml2_1_loop(TRACE_STRUCT);
      beta_mHd2 += calc_beta_mHd2_1_loop(TRACE_STRUCT);
      beta_mHu2 += calc_beta_mHu2_1_loop(TRACE_STRUCT);
      beta_md2 += calc_beta_md2_1_loop(TRACE_STRUCT);
      beta_mu2 += calc_beta_mu2_1_loop(TRACE_STRUCT);
      beta_me2 += calc_beta_me2_1_loop(TRACE_STRUCT);
      beta_MassB += calc_beta_MassB_1_loop(TRACE_STRUCT);
      beta_MassWB += calc_beta_MassWB_1_loop(TRACE_STRUCT);
      beta_MassG += calc_beta_MassG_1_loop(TRACE_STRUCT);

      if (loops > 1) {
         beta_TYd += calc_beta_TYd_2_loop(TRACE_STRUCT);
         beta_TYe += calc_beta_TYe_2_loop(TRACE_STRUCT);
         beta_TYu += calc_beta_TYu_2_loop(TRACE_STRUCT);
         beta_BMu += calc_beta_BMu_2_loop(TRACE_STRUCT);
         beta_mq2 += calc_beta_mq2_2_loop(TRACE_STRUCT);
         beta_ml2 += calc_beta_ml2_2_loop(TRACE_STRUCT);
         beta_mHd2 += calc_beta_mHd2_2_loop(TRACE_STRUCT);
         beta_mHu2 += calc_beta_mHu2_2_loop(TRACE_STRUCT);
         beta_md2 += calc_beta_md2_2_loop(TRACE_STRUCT);
         beta_mu2 += calc_beta_mu2_2_loop(TRACE_STRUCT);
         beta_me2 += calc_beta_me2_2_loop(TRACE_STRUCT);
         beta_MassB += calc_beta_MassB_2_loop(TRACE_STRUCT);
         beta_MassWB += calc_beta_MassWB_2_loop(TRACE_STRUCT);
         beta_MassG += calc_beta_MassG_2_loop(TRACE_STRUCT);

         if (loops > 2) {
         #ifdef ENABLE_THREADS
            {
               auto fut_TYd = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_TYd_3_loop(TRACE_STRUCT); });
               auto fut_TYe = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_TYe_3_loop(TRACE_STRUCT); });
               auto fut_TYu = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_TYu_3_loop(TRACE_STRUCT); });
               auto fut_BMu = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_BMu_3_loop(TRACE_STRUCT); });
               auto fut_mq2 = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_mq2_3_loop(TRACE_STRUCT); });
               auto fut_ml2 = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_ml2_3_loop(TRACE_STRUCT); });
               auto fut_mHd2 = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_mHd2_3_loop(TRACE_STRUCT); });
               auto fut_mHu2 = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_mHu2_3_loop(TRACE_STRUCT); });
               auto fut_md2 = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_md2_3_loop(TRACE_STRUCT); });
               auto fut_mu2 = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_mu2_3_loop(TRACE_STRUCT); });
               auto fut_me2 = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_me2_3_loop(TRACE_STRUCT); });
               auto fut_MassB = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_MassB_3_loop(TRACE_STRUCT); });
               auto fut_MassWB = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_MassWB_3_loop(TRACE_STRUCT); });
               auto fut_MassG = global_thread_pool()
                  .run_packaged_task([this, &TRACE_STRUCT](){ return
                  calc_beta_MassG_3_loop(TRACE_STRUCT); });

               beta_TYd += fut_TYd.get();
               beta_TYe += fut_TYe.get();
               beta_TYu += fut_TYu.get();
               beta_BMu += fut_BMu.get();
               beta_mq2 += fut_mq2.get();
               beta_ml2 += fut_ml2.get();
               beta_mHd2 += fut_mHd2.get();
               beta_mHu2 += fut_mHu2.get();
               beta_md2 += fut_md2.get();
               beta_mu2 += fut_mu2.get();
               beta_me2 += fut_me2.get();
               beta_MassB += fut_MassB.get();
               beta_MassWB += fut_MassWB.get();
               beta_MassG += fut_MassG.get();

            }
         #else
            beta_TYd += calc_beta_TYd_3_loop(TRACE_STRUCT);
            beta_TYe += calc_beta_TYe_3_loop(TRACE_STRUCT);
            beta_TYu += calc_beta_TYu_3_loop(TRACE_STRUCT);
            beta_BMu += calc_beta_BMu_3_loop(TRACE_STRUCT);
            beta_mq2 += calc_beta_mq2_3_loop(TRACE_STRUCT);
            beta_ml2 += calc_beta_ml2_3_loop(TRACE_STRUCT);
            beta_mHd2 += calc_beta_mHd2_3_loop(TRACE_STRUCT);
            beta_mHu2 += calc_beta_mHu2_3_loop(TRACE_STRUCT);
            beta_md2 += calc_beta_md2_3_loop(TRACE_STRUCT);
            beta_mu2 += calc_beta_mu2_3_loop(TRACE_STRUCT);
            beta_me2 += calc_beta_me2_3_loop(TRACE_STRUCT);
            beta_MassB += calc_beta_MassB_3_loop(TRACE_STRUCT);
            beta_MassWB += calc_beta_MassWB_3_loop(TRACE_STRUCT);
            beta_MassG += calc_beta_MassG_3_loop(TRACE_STRUCT);
         #endif

         }
      }
   }


   const MSSMatMSUSY_mAmu_susy_parameters susy_betas(MSSMatMSUSY_mAmu_susy_parameters::calc_beta(loops));

   return MSSMatMSUSY_mAmu_soft_parameters(susy_betas, beta_TYd, beta_TYe, beta_TYu, beta_BMu, beta_mq2, beta_ml2, beta_mHd2, beta_mHu2, beta_md2, beta_mu2, beta_me2, beta_MassB, beta_MassWB, beta_MassG);
}

MSSMatMSUSY_mAmu_soft_parameters MSSMatMSUSY_mAmu_soft_parameters::calc_beta() const
{
   return calc_beta(get_loops());
}

void MSSMatMSUSY_mAmu_soft_parameters::clear()
{
   MSSMatMSUSY_mAmu_susy_parameters::clear();

   TYd = Eigen::Matrix<double,3,3>::Zero();
   TYe = Eigen::Matrix<double,3,3>::Zero();
   TYu = Eigen::Matrix<double,3,3>::Zero();
   BMu = 0.;
   mq2 = Eigen::Matrix<double,3,3>::Zero();
   ml2 = Eigen::Matrix<double,3,3>::Zero();
   mHd2 = 0.;
   mHu2 = 0.;
   md2 = Eigen::Matrix<double,3,3>::Zero();
   mu2 = Eigen::Matrix<double,3,3>::Zero();
   me2 = Eigen::Matrix<double,3,3>::Zero();
   MassB = 0.;
   MassWB = 0.;
   MassG = 0.;

}

Eigen::ArrayXd MSSMatMSUSY_mAmu_soft_parameters::get() const
{
   Eigen::ArrayXd pars(MSSMatMSUSY_mAmu_susy_parameters::get());
   pars.conservativeResize(numberOfParameters);

   pars(33) = TYd(0,0);
   pars(34) = TYd(0,1);
   pars(35) = TYd(0,2);
   pars(36) = TYd(1,0);
   pars(37) = TYd(1,1);
   pars(38) = TYd(1,2);
   pars(39) = TYd(2,0);
   pars(40) = TYd(2,1);
   pars(41) = TYd(2,2);
   pars(42) = TYe(0,0);
   pars(43) = TYe(0,1);
   pars(44) = TYe(0,2);
   pars(45) = TYe(1,0);
   pars(46) = TYe(1,1);
   pars(47) = TYe(1,2);
   pars(48) = TYe(2,0);
   pars(49) = TYe(2,1);
   pars(50) = TYe(2,2);
   pars(51) = TYu(0,0);
   pars(52) = TYu(0,1);
   pars(53) = TYu(0,2);
   pars(54) = TYu(1,0);
   pars(55) = TYu(1,1);
   pars(56) = TYu(1,2);
   pars(57) = TYu(2,0);
   pars(58) = TYu(2,1);
   pars(59) = TYu(2,2);
   pars(60) = BMu;
   pars(61) = mq2(0,0);
   pars(62) = mq2(0,1);
   pars(63) = mq2(0,2);
   pars(64) = mq2(1,0);
   pars(65) = mq2(1,1);
   pars(66) = mq2(1,2);
   pars(67) = mq2(2,0);
   pars(68) = mq2(2,1);
   pars(69) = mq2(2,2);
   pars(70) = ml2(0,0);
   pars(71) = ml2(0,1);
   pars(72) = ml2(0,2);
   pars(73) = ml2(1,0);
   pars(74) = ml2(1,1);
   pars(75) = ml2(1,2);
   pars(76) = ml2(2,0);
   pars(77) = ml2(2,1);
   pars(78) = ml2(2,2);
   pars(79) = mHd2;
   pars(80) = mHu2;
   pars(81) = md2(0,0);
   pars(82) = md2(0,1);
   pars(83) = md2(0,2);
   pars(84) = md2(1,0);
   pars(85) = md2(1,1);
   pars(86) = md2(1,2);
   pars(87) = md2(2,0);
   pars(88) = md2(2,1);
   pars(89) = md2(2,2);
   pars(90) = mu2(0,0);
   pars(91) = mu2(0,1);
   pars(92) = mu2(0,2);
   pars(93) = mu2(1,0);
   pars(94) = mu2(1,1);
   pars(95) = mu2(1,2);
   pars(96) = mu2(2,0);
   pars(97) = mu2(2,1);
   pars(98) = mu2(2,2);
   pars(99) = me2(0,0);
   pars(100) = me2(0,1);
   pars(101) = me2(0,2);
   pars(102) = me2(1,0);
   pars(103) = me2(1,1);
   pars(104) = me2(1,2);
   pars(105) = me2(2,0);
   pars(106) = me2(2,1);
   pars(107) = me2(2,2);
   pars(108) = MassB;
   pars(109) = MassWB;
   pars(110) = MassG;


   return pars;
}

void MSSMatMSUSY_mAmu_soft_parameters::print(std::ostream& ostr) const
{
   MSSMatMSUSY_mAmu_susy_parameters::print(ostr);
   ostr << "soft parameters at Q = " << get_scale() << ":\n";
   ostr << "TYd = " << TYd << '\n';
   ostr << "TYe = " << TYe << '\n';
   ostr << "TYu = " << TYu << '\n';
   ostr << "BMu = " << BMu << '\n';
   ostr << "mq2 = " << mq2 << '\n';
   ostr << "ml2 = " << ml2 << '\n';
   ostr << "mHd2 = " << mHd2 << '\n';
   ostr << "mHu2 = " << mHu2 << '\n';
   ostr << "md2 = " << md2 << '\n';
   ostr << "mu2 = " << mu2 << '\n';
   ostr << "me2 = " << me2 << '\n';
   ostr << "MassB = " << MassB << '\n';
   ostr << "MassWB = " << MassWB << '\n';
   ostr << "MassG = " << MassG << '\n';

}

void MSSMatMSUSY_mAmu_soft_parameters::set(const Eigen::ArrayXd& pars)
{
   MSSMatMSUSY_mAmu_susy_parameters::set(pars);

   TYd(0,0) = pars(33);
   TYd(0,1) = pars(34);
   TYd(0,2) = pars(35);
   TYd(1,0) = pars(36);
   TYd(1,1) = pars(37);
   TYd(1,2) = pars(38);
   TYd(2,0) = pars(39);
   TYd(2,1) = pars(40);
   TYd(2,2) = pars(41);
   TYe(0,0) = pars(42);
   TYe(0,1) = pars(43);
   TYe(0,2) = pars(44);
   TYe(1,0) = pars(45);
   TYe(1,1) = pars(46);
   TYe(1,2) = pars(47);
   TYe(2,0) = pars(48);
   TYe(2,1) = pars(49);
   TYe(2,2) = pars(50);
   TYu(0,0) = pars(51);
   TYu(0,1) = pars(52);
   TYu(0,2) = pars(53);
   TYu(1,0) = pars(54);
   TYu(1,1) = pars(55);
   TYu(1,2) = pars(56);
   TYu(2,0) = pars(57);
   TYu(2,1) = pars(58);
   TYu(2,2) = pars(59);
   BMu = pars(60);
   mq2(0,0) = pars(61);
   mq2(0,1) = pars(62);
   mq2(0,2) = pars(63);
   mq2(1,0) = pars(64);
   mq2(1,1) = pars(65);
   mq2(1,2) = pars(66);
   mq2(2,0) = pars(67);
   mq2(2,1) = pars(68);
   mq2(2,2) = pars(69);
   ml2(0,0) = pars(70);
   ml2(0,1) = pars(71);
   ml2(0,2) = pars(72);
   ml2(1,0) = pars(73);
   ml2(1,1) = pars(74);
   ml2(1,2) = pars(75);
   ml2(2,0) = pars(76);
   ml2(2,1) = pars(77);
   ml2(2,2) = pars(78);
   mHd2 = pars(79);
   mHu2 = pars(80);
   md2(0,0) = pars(81);
   md2(0,1) = pars(82);
   md2(0,2) = pars(83);
   md2(1,0) = pars(84);
   md2(1,1) = pars(85);
   md2(1,2) = pars(86);
   md2(2,0) = pars(87);
   md2(2,1) = pars(88);
   md2(2,2) = pars(89);
   mu2(0,0) = pars(90);
   mu2(0,1) = pars(91);
   mu2(0,2) = pars(92);
   mu2(1,0) = pars(93);
   mu2(1,1) = pars(94);
   mu2(1,2) = pars(95);
   mu2(2,0) = pars(96);
   mu2(2,1) = pars(97);
   mu2(2,2) = pars(98);
   me2(0,0) = pars(99);
   me2(0,1) = pars(100);
   me2(0,2) = pars(101);
   me2(1,0) = pars(102);
   me2(1,1) = pars(103);
   me2(1,2) = pars(104);
   me2(2,0) = pars(105);
   me2(2,1) = pars(106);
   me2(2,2) = pars(107);
   MassB = pars(108);
   MassWB = pars(109);
   MassG = pars(110);

}

MSSMatMSUSY_mAmu_soft_parameters::Soft_traces MSSMatMSUSY_mAmu_soft_parameters::calc_soft_traces(int loops) const
{
   Soft_traces soft_traces;

   if (loops > 0) {
      TRACE_STRUCT.Tr11 = Re(0.7745966692414834*g1*(-mHd2 + mHu2 + (md2).trace() +
         (me2).trace() - (ml2).trace() + (mq2).trace() - 2*(mu2).trace()));
      TRACE_STRUCT.Tr2U111 = Re(0.1*Sqr(g1)*(3*mHd2 + 3*mHu2 + 2*(md2).trace() + 6
         *(me2).trace() + 3*(ml2).trace() + (mq2).trace() + 8*(mu2).trace()));
      TRACE_STRUCT.Tr31 = Re(0.012909944487358056*g1*(-9*mHd2*Sqr(g1) + 9*mHu2*Sqr
         (g1) - 45*mHd2*Sqr(g2) + 45*mHu2*Sqr(g2) + 4*(Sqr(g1) + 20*Sqr(g3))*(md2)
         .trace() + 36*Sqr(g1)*(me2).trace() - 9*Sqr(g1)*(ml2).trace() - 45*Sqr(g2)*(
         ml2).trace() + Sqr(g1)*(mq2).trace() + 45*Sqr(g2)*(mq2).trace() + 80*Sqr(g3)
         *(mq2).trace() - 32*Sqr(g1)*(mu2).trace() - 160*Sqr(g3)*(mu2).trace() + 90*
         mHd2*(Yd*Yd.adjoint()).trace() + 30*mHd2*(Ye*Ye.adjoint()).trace() - 90*mHu2
         *(Yu*Yu.adjoint()).trace() - 60*(Yd*Yd.adjoint()*md2.conjugate()).trace() -
         30*(Yd*mq2.conjugate()*Yd.adjoint()).trace() - 60*(Ye*Ye.adjoint()*
         me2.conjugate()).trace() + 30*(Ye*ml2.conjugate()*Ye.adjoint()).trace() +
         120*(Yu*Yu.adjoint()*mu2.conjugate()).trace() - 30*(Yu*mq2.conjugate()*
         Yu.adjoint()).trace()));
      TRACE_STRUCT.Tr22 = Re(0.5*(mHd2 + mHu2 + (ml2).trace() + 3*(mq2).trace()));
      TRACE_STRUCT.Tr23 = Re(0.5*((md2).trace() + 2*(mq2).trace() + (mu2).trace())
         );

      TRACE_STRUCT.traceYdAdjYd = Re((Yd*Yd.adjoint()).trace());
      TRACE_STRUCT.traceYeAdjYe = Re((Ye*Ye.adjoint()).trace());
      TRACE_STRUCT.traceYuAdjYu = Re((Yu*Yu.adjoint()).trace());
      TRACE_STRUCT.traceAdjYdTYd = Re((Yd.adjoint()*TYd).trace());
      TRACE_STRUCT.traceAdjYeTYe = Re((Ye.adjoint()*TYe).trace());
      TRACE_STRUCT.traceAdjYuTYu = Re((Yu.adjoint()*TYu).trace());
      TRACE_STRUCT.traceconjTYdTpTYd = Re((TYd.conjugate()*(TYd).transpose())
         .trace());
      TRACE_STRUCT.traceconjTYeTpTYe = Re((TYe.conjugate()*(TYe).transpose())
         .trace());
      TRACE_STRUCT.traceconjTYuTpTYu = Re((TYu.conjugate()*(TYu).transpose())
         .trace());
      TRACE_STRUCT.tracemd2YdAdjYd = Re((md2*Yd*Yd.adjoint()).trace());
      TRACE_STRUCT.traceme2YeAdjYe = Re((me2*Ye*Ye.adjoint()).trace());
      TRACE_STRUCT.traceml2AdjYeYe = Re((ml2*Ye.adjoint()*Ye).trace());
      TRACE_STRUCT.tracemq2AdjYdYd = Re((mq2*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.tracemq2AdjYuYu = Re((mq2*Yu.adjoint()*Yu).trace());
      TRACE_STRUCT.tracemu2YuAdjYu = Re((mu2*Yu*Yu.adjoint()).trace());

   }

   if (loops > 1) {
      TRACE_STRUCT.traceconjTYdTpYd = Re((TYd.conjugate()*Yd.transpose()).trace())
         ;
      TRACE_STRUCT.traceconjTYeTpYe = Re((TYe.conjugate()*Ye.transpose()).trace())
         ;
      TRACE_STRUCT.traceconjTYuTpYu = Re((TYu.conjugate()*Yu.transpose()).trace())
         ;
      TRACE_STRUCT.traceYdAdjYdYdAdjYd = Re((Yd*Yd.adjoint()*Yd*Yd.adjoint())
         .trace());
      TRACE_STRUCT.traceYdAdjYdTYdAdjYd = Re((Yd*Yd.adjoint()*TYd*Yd.adjoint())
         .trace());
      TRACE_STRUCT.traceYdAdjYdTYdAdjTYd = Re((Yd*Yd.adjoint()*TYd*(TYd).adjoint()
         ).trace());
      TRACE_STRUCT.traceYdAdjYuYuAdjYd = Re((Yd*Yu.adjoint()*Yu*Yd.adjoint())
         .trace());
      TRACE_STRUCT.traceYdAdjYuTYuAdjYd = Re((Yd*Yu.adjoint()*TYu*Yd.adjoint())
         .trace());
      TRACE_STRUCT.traceYdAdjYuTYuAdjTYd = Re((Yd*Yu.adjoint()*TYu*(TYd).adjoint()
         ).trace());
      TRACE_STRUCT.traceYdAdjTYdTYdAdjYd = Re((Yd*(TYd).adjoint()*TYd*Yd.adjoint()
         ).trace());
      TRACE_STRUCT.traceYdAdjTYuTYuAdjYd = Re((Yd*(TYu).adjoint()*TYu*Yd.adjoint()
         ).trace());
      TRACE_STRUCT.traceYeAdjYeYeAdjYe = Re((Ye*Ye.adjoint()*Ye*Ye.adjoint())
         .trace());
      TRACE_STRUCT.traceYeAdjYeTYeAdjYe = Re((Ye*Ye.adjoint()*TYe*Ye.adjoint())
         .trace());
      TRACE_STRUCT.traceYeAdjYeTYeAdjTYe = Re((Ye*Ye.adjoint()*TYe*(TYe).adjoint()
         ).trace());
      TRACE_STRUCT.traceYeAdjTYeTYeAdjYe = Re((Ye*(TYe).adjoint()*TYe*Ye.adjoint()
         ).trace());
      TRACE_STRUCT.traceYuAdjYdTYdAdjYu = Re((Yu*Yd.adjoint()*TYd*Yu.adjoint())
         .trace());
      TRACE_STRUCT.traceYuAdjYdTYdAdjTYu = Re((Yu*Yd.adjoint()*TYd*(TYu).adjoint()
         ).trace());
      TRACE_STRUCT.traceYuAdjYuYuAdjYu = Re((Yu*Yu.adjoint()*Yu*Yu.adjoint())
         .trace());
      TRACE_STRUCT.traceYuAdjYuTYuAdjYu = Re((Yu*Yu.adjoint()*TYu*Yu.adjoint())
         .trace());
      TRACE_STRUCT.traceYuAdjYuTYuAdjTYu = Re((Yu*Yu.adjoint()*TYu*(TYu).adjoint()
         ).trace());
      TRACE_STRUCT.traceYuAdjTYdTYdAdjYu = Re((Yu*(TYd).adjoint()*TYd*Yu.adjoint()
         ).trace());
      TRACE_STRUCT.traceYuAdjTYuTYuAdjYu = Re((Yu*(TYu).adjoint()*TYu*Yu.adjoint()
         ).trace());
      TRACE_STRUCT.tracemd2YdAdjYdYdAdjYd = Re((md2*Yd*Yd.adjoint()*Yd*Yd.adjoint(
         )).trace());
      TRACE_STRUCT.tracemd2YdAdjYuYuAdjYd = Re((md2*Yd*Yu.adjoint()*Yu*Yd.adjoint(
         )).trace());
      TRACE_STRUCT.traceme2YeAdjYeYeAdjYe = Re((me2*Ye*Ye.adjoint()*Ye*Ye.adjoint(
         )).trace());
      TRACE_STRUCT.traceml2AdjYeYeAdjYeYe = Re((ml2*Ye.adjoint()*Ye*Ye.adjoint()*
         Ye).trace());
      TRACE_STRUCT.tracemq2AdjYdYdAdjYdYd = Re((mq2*Yd.adjoint()*Yd*Yd.adjoint()*
         Yd).trace());
      TRACE_STRUCT.tracemq2AdjYdYdAdjYuYu = Re((mq2*Yd.adjoint()*Yd*Yu.adjoint()*
         Yu).trace());
      TRACE_STRUCT.tracemq2AdjYuYuAdjYdYd = Re((mq2*Yu.adjoint()*Yu*Yd.adjoint()*
         Yd).trace());
      TRACE_STRUCT.tracemq2AdjYuYuAdjYuYu = Re((mq2*Yu.adjoint()*Yu*Yu.adjoint()*
         Yu).trace());
      TRACE_STRUCT.tracemu2YuAdjYdYdAdjYu = Re((mu2*Yu*Yd.adjoint()*Yd*Yu.adjoint(
         )).trace());
      TRACE_STRUCT.tracemu2YuAdjYuYuAdjYu = Re((mu2*Yu*Yu.adjoint()*Yu*Yu.adjoint(
         )).trace());

   }

   if (loops > 2) {
      TRACE_STRUCT.tracemd2 = Re((md2).trace());
      TRACE_STRUCT.traceme2 = Re((me2).trace());
      TRACE_STRUCT.traceml2 = Re((ml2).trace());
      TRACE_STRUCT.tracemq2 = Re((mq2).trace());
      TRACE_STRUCT.tracemu2 = Re((mu2).trace());
      TRACE_STRUCT.traceAdjYdYd = Re((Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYeYe = Re((Ye.adjoint()*Ye).trace());
      TRACE_STRUCT.traceAdjYuYu = Re((Yu.adjoint()*Yu).trace());
      TRACE_STRUCT.traceAdjTYdYd = Re(((TYd).adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjTYeYe = Re(((TYe).adjoint()*Ye).trace());
      TRACE_STRUCT.traceAdjTYuYu = Re(((TYu).adjoint()*Yu).trace());
      TRACE_STRUCT.traceTYdAdjYd = Re((TYd*Yd.adjoint()).trace());
      TRACE_STRUCT.traceTYdAdjTYd = Re((TYd*(TYd).adjoint()).trace());
      TRACE_STRUCT.traceTYeAdjYe = Re((TYe*Ye.adjoint()).trace());
      TRACE_STRUCT.traceTYeAdjTYe = Re((TYe*(TYe).adjoint()).trace());
      TRACE_STRUCT.traceTYuAdjYu = Re((TYu*Yu.adjoint()).trace());
      TRACE_STRUCT.traceTYuAdjTYu = Re((TYu*(TYu).adjoint()).trace());
      TRACE_STRUCT.traceYdAdjYdmd2 = Re((Yd*Yd.adjoint()*md2).trace());
      TRACE_STRUCT.traceYeAdjYeme2 = Re((Ye*Ye.adjoint()*me2).trace());
      TRACE_STRUCT.traceYuAdjYumu2 = Re((Yu*Yu.adjoint()*mu2).trace());
      TRACE_STRUCT.traceAdjYdYdmq2 = Re((Yd.adjoint()*Yd*mq2).trace());
      TRACE_STRUCT.traceAdjYeYeml2 = Re((Ye.adjoint()*Ye*ml2).trace());
      TRACE_STRUCT.traceAdjYuYumq2 = Re((Yu.adjoint()*Yu*mq2).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdYd = Re((Yd.adjoint()*Yd*Yd.adjoint()*Yd)
         .trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdTYd = Re((Yd.adjoint()*Yd*Yd.adjoint()*TYd)
         .trace());
      TRACE_STRUCT.traceAdjYdYdAdjTYdYd = Re((Yd.adjoint()*Yd*(TYd).adjoint()*Yd)
         .trace());
      TRACE_STRUCT.traceAdjYdTYdAdjYdYd = Re((Yd.adjoint()*TYd*Yd.adjoint()*Yd)
         .trace());
      TRACE_STRUCT.traceAdjYdTYdAdjTYdYd = Re((Yd.adjoint()*TYd*(TYd).adjoint()*Yd
         ).trace());
      TRACE_STRUCT.traceAdjYeYeAdjYeYe = Re((Ye.adjoint()*Ye*Ye.adjoint()*Ye)
         .trace());
      TRACE_STRUCT.traceAdjYeYeAdjYeTYe = Re((Ye.adjoint()*Ye*Ye.adjoint()*TYe)
         .trace());
      TRACE_STRUCT.traceAdjYeYeAdjTYeYe = Re((Ye.adjoint()*Ye*(TYe).adjoint()*Ye)
         .trace());
      TRACE_STRUCT.traceAdjYeTYeAdjYeYe = Re((Ye.adjoint()*TYe*Ye.adjoint()*Ye)
         .trace());
      TRACE_STRUCT.traceAdjYeTYeAdjTYeYe = Re((Ye.adjoint()*TYe*(TYe).adjoint()*Ye
         ).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYdYd = Re((Yu.adjoint()*Yu*Yd.adjoint()*Yd)
         .trace());
      TRACE_STRUCT.traceAdjYuYuAdjYdTYd = Re((Yu.adjoint()*Yu*Yd.adjoint()*TYd)
         .trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYu = Re((Yu.adjoint()*Yu*Yu.adjoint()*Yu)
         .trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuTYu = Re((Yu.adjoint()*Yu*Yu.adjoint()*TYu)
         .trace());
      TRACE_STRUCT.traceAdjYuYuAdjTYdYd = Re((Yu.adjoint()*Yu*(TYd).adjoint()*Yd)
         .trace());
      TRACE_STRUCT.traceAdjYuYuAdjTYuYu = Re((Yu.adjoint()*Yu*(TYu).adjoint()*Yu)
         .trace());
      TRACE_STRUCT.traceAdjYuTYuAdjYdYd = Re((Yu.adjoint()*TYu*Yd.adjoint()*Yd)
         .trace());
      TRACE_STRUCT.traceAdjYuTYuAdjYuYu = Re((Yu.adjoint()*TYu*Yu.adjoint()*Yu)
         .trace());
      TRACE_STRUCT.traceAdjYuTYuAdjTYdYd = Re((Yu.adjoint()*TYu*(TYd).adjoint()*Yd
         ).trace());
      TRACE_STRUCT.traceAdjYuTYuAdjTYuYu = Re((Yu.adjoint()*TYu*(TYu).adjoint()*Yu
         ).trace());
      TRACE_STRUCT.traceAdjTYdTYdAdjYdYd = Re(((TYd).adjoint()*TYd*Yd.adjoint()*Yd
         ).trace());
      TRACE_STRUCT.traceAdjTYdTYdAdjYuYu = Re(((TYd).adjoint()*TYd*Yu.adjoint()*Yu
         ).trace());
      TRACE_STRUCT.traceAdjTYeTYeAdjYeYe = Re(((TYe).adjoint()*TYe*Ye.adjoint()*Ye
         ).trace());
      TRACE_STRUCT.traceAdjTYuYuAdjYdYd = Re(((TYu).adjoint()*Yu*Yd.adjoint()*Yd)
         .trace());
      TRACE_STRUCT.traceAdjTYuTYuAdjYdYd = Re(((TYu).adjoint()*TYu*Yd.adjoint()*Yd
         ).trace());
      TRACE_STRUCT.traceAdjTYuTYuAdjYuYu = Re(((TYu).adjoint()*TYu*Yu.adjoint()*Yu
         ).trace());
      TRACE_STRUCT.traceTYdAdjYuYuAdjYd = Re((TYd*Yu.adjoint()*Yu*Yd.adjoint())
         .trace());
      TRACE_STRUCT.traceTYdAdjTYuYuAdjYd = Re((TYd*(TYu).adjoint()*Yu*Yd.adjoint()
         ).trace());
      TRACE_STRUCT.traceYdAdjYdYdAdjYdmd2 = Re((Yd*Yd.adjoint()*Yd*Yd.adjoint()*
         md2).trace());
      TRACE_STRUCT.traceYdAdjYuYuAdjYdmd2 = Re((Yd*Yu.adjoint()*Yu*Yd.adjoint()*
         md2).trace());
      TRACE_STRUCT.traceYeAdjYeYeAdjYeme2 = Re((Ye*Ye.adjoint()*Ye*Ye.adjoint()*
         me2).trace());
      TRACE_STRUCT.traceYuAdjYdYdAdjYumu2 = Re((Yu*Yd.adjoint()*Yd*Yu.adjoint()*
         mu2).trace());
      TRACE_STRUCT.traceYuAdjYuYuAdjYumu2 = Re((Yu*Yu.adjoint()*Yu*Yu.adjoint()*
         mu2).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdYdmq2 = Re((Yd.adjoint()*Yd*Yd.adjoint()*Yd*
         mq2).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYuYumq2 = Re((Yd.adjoint()*Yd*Yu.adjoint()*Yu*
         mq2).trace());
      TRACE_STRUCT.traceAdjYeYeAdjYeYeml2 = Re((Ye.adjoint()*Ye*Ye.adjoint()*Ye*
         ml2).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYdYdmq2 = Re((Yu.adjoint()*Yu*Yd.adjoint()*Yd*
         mq2).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYumq2 = Re((Yu.adjoint()*Yu*Yu.adjoint()*Yu*
         mq2).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdYdAdjYdYd = Re((Yd.adjoint()*Yd*Yd.adjoint()*
         Yd*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdYdAdjYdTYd = Re((Yd.adjoint()*Yd*Yd.adjoint()*
         Yd*Yd.adjoint()*TYd).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdTYdAdjYdYd = Re((Yd.adjoint()*Yd*Yd.adjoint()*
         TYd*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdTYdAdjTYdYd = Re((Yd.adjoint()*Yd*Yd.adjoint()
         *TYd*(TYd).adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYdYd = Re((Yd.adjoint()*Yd*Yu.adjoint()*
         Yu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYdTYd = Re((Yd.adjoint()*Yd*Yu.adjoint()*
         Yu*Yd.adjoint()*TYd).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYuTYuAdjYdYd = Re((Yd.adjoint()*Yd*Yu.adjoint()*
         TYu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYuTYuAdjTYdYd = Re((Yd.adjoint()*Yd*Yu.adjoint()
         *TYu*(TYd).adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdYdAdjTYdTYdAdjYdYd = Re((Yd.adjoint()*Yd*(TYd)
         .adjoint()*TYd*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdYdAdjTYuTYuAdjYdYd = Re((Yd.adjoint()*Yd*(TYu)
         .adjoint()*TYu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdTYdAdjYdYdAdjYdYd = Re((Yd.adjoint()*TYd*Yd.adjoint()
         *Yd*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdTYdAdjYdYdAdjTYdYd = Re((Yd.adjoint()*TYd*Yd.adjoint(
         )*Yd*(TYd).adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdTYdAdjYuYuAdjYdYd = Re((Yd.adjoint()*TYd*Yu.adjoint()
         *Yu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdTYdAdjYuYuAdjTYdYd = Re((Yd.adjoint()*TYd*Yu.adjoint(
         )*Yu*(TYd).adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYdTYdAdjTYuYuAdjYdYd = Re((Yd.adjoint()*TYd*(TYu)
         .adjoint()*Yu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYeYeAdjYeYeAdjYeYe = Re((Ye.adjoint()*Ye*Ye.adjoint()*
         Ye*Ye.adjoint()*Ye).trace());
      TRACE_STRUCT.traceAdjYeYeAdjYeYeAdjYeTYe = Re((Ye.adjoint()*Ye*Ye.adjoint()*
         Ye*Ye.adjoint()*TYe).trace());
      TRACE_STRUCT.traceAdjYeYeAdjYeTYeAdjYeYe = Re((Ye.adjoint()*Ye*Ye.adjoint()*
         TYe*Ye.adjoint()*Ye).trace());
      TRACE_STRUCT.traceAdjYeYeAdjYeTYeAdjTYeYe = Re((Ye.adjoint()*Ye*Ye.adjoint()
         *TYe*(TYe).adjoint()*Ye).trace());
      TRACE_STRUCT.traceAdjYeYeAdjTYeTYeAdjYeYe = Re((Ye.adjoint()*Ye*(TYe)
         .adjoint()*TYe*Ye.adjoint()*Ye).trace());
      TRACE_STRUCT.traceAdjYeTYeAdjYeYeAdjYeYe = Re((Ye.adjoint()*TYe*Ye.adjoint()
         *Ye*Ye.adjoint()*Ye).trace());
      TRACE_STRUCT.traceAdjYeTYeAdjYeYeAdjTYeYe = Re((Ye.adjoint()*TYe*Ye.adjoint(
         )*Ye*(TYe).adjoint()*Ye).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYdTYdAdjYdYd = Re((Yu.adjoint()*Yu*Yd.adjoint()*
         TYd*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYdTYdAdjTYdYd = Re((Yu.adjoint()*Yu*Yd.adjoint()
         *TYd*(TYd).adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYdYd = Re((Yu.adjoint()*Yu*Yu.adjoint()*
         Yu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYdTYd = Re((Yu.adjoint()*Yu*Yu.adjoint()*
         Yu*Yd.adjoint()*TYd).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYuYu = Re((Yu.adjoint()*Yu*Yu.adjoint()*
         Yu*Yu.adjoint()*Yu).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYuTYu = Re((Yu.adjoint()*Yu*Yu.adjoint()*
         Yu*Yu.adjoint()*TYu).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuTYuAdjYdYd = Re((Yu.adjoint()*Yu*Yu.adjoint()*
         TYu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuTYuAdjYuYu = Re((Yu.adjoint()*Yu*Yu.adjoint()*
         TYu*Yu.adjoint()*Yu).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuTYuAdjTYdYd = Re((Yu.adjoint()*Yu*Yu.adjoint()
         *TYu*(TYd).adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuTYuAdjTYuYu = Re((Yu.adjoint()*Yu*Yu.adjoint()
         *TYu*(TYu).adjoint()*Yu).trace());
      TRACE_STRUCT.traceAdjYuYuAdjTYdTYdAdjYdYd = Re((Yu.adjoint()*Yu*(TYd)
         .adjoint()*TYd*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuYuAdjTYdTYdAdjYuYu = Re((Yu.adjoint()*Yu*(TYd)
         .adjoint()*TYd*Yu.adjoint()*Yu).trace());
      TRACE_STRUCT.traceAdjYuYuAdjTYuTYuAdjYdYd = Re((Yu.adjoint()*Yu*(TYu)
         .adjoint()*TYu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuYuAdjTYuTYuAdjYuYu = Re((Yu.adjoint()*Yu*(TYu)
         .adjoint()*TYu*Yu.adjoint()*Yu).trace());
      TRACE_STRUCT.traceAdjYuTYuAdjYdYdAdjTYdYd = Re((Yu.adjoint()*TYu*Yd.adjoint(
         )*Yd*(TYd).adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuTYuAdjYuYuAdjYdYd = Re((Yu.adjoint()*TYu*Yu.adjoint()
         *Yu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuTYuAdjYuYuAdjYuYu = Re((Yu.adjoint()*TYu*Yu.adjoint()
         *Yu*Yu.adjoint()*Yu).trace());
      TRACE_STRUCT.traceAdjYuTYuAdjYuYuAdjTYdYd = Re((Yu.adjoint()*TYu*Yu.adjoint(
         )*Yu*(TYd).adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjYuTYuAdjYuYuAdjTYuYu = Re((Yu.adjoint()*TYu*Yu.adjoint(
         )*Yu*(TYu).adjoint()*Yu).trace());
      TRACE_STRUCT.traceAdjYuTYuAdjTYuYuAdjYdYd = Re((Yu.adjoint()*TYu*(TYu)
         .adjoint()*Yu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjTYdTYdAdjYuYuAdjYdYd = Re(((TYd).adjoint()*TYd*
         Yu.adjoint()*Yu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjTYuYuAdjYdTYdAdjYdYd = Re(((TYu).adjoint()*Yu*
         Yd.adjoint()*TYd*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjTYuYuAdjYuTYuAdjYdYd = Re(((TYu).adjoint()*Yu*
         Yu.adjoint()*TYu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceAdjTYuTYuAdjYuYuAdjYdYd = Re(((TYu).adjoint()*TYu*
         Yu.adjoint()*Yu*Yd.adjoint()*Yd).trace());
      TRACE_STRUCT.traceTYdAdjYuYuAdjYuYuAdjYd = Re((TYd*Yu.adjoint()*Yu*
         Yu.adjoint()*Yu*Yd.adjoint()).trace());
      TRACE_STRUCT.traceTYdAdjYuYuAdjTYuYuAdjYd = Re((TYd*Yu.adjoint()*Yu*(TYu)
         .adjoint()*Yu*Yd.adjoint()).trace());
      TRACE_STRUCT.traceTYdAdjTYuYuAdjYuYuAdjYd = Re((TYd*(TYu).adjoint()*Yu*
         Yu.adjoint()*Yu*Yd.adjoint()).trace());
      TRACE_STRUCT.traceYdAdjYdYdAdjYdYdAdjYdmd2 = Re((Yd*Yd.adjoint()*Yd*
         Yd.adjoint()*Yd*Yd.adjoint()*md2).trace());
      TRACE_STRUCT.traceYdAdjYdYdAdjYuYuAdjYdmd2 = Re((Yd*Yd.adjoint()*Yd*
         Yu.adjoint()*Yu*Yd.adjoint()*md2).trace());
      TRACE_STRUCT.traceYdAdjYuYuAdjYdYdAdjYdmd2 = Re((Yd*Yu.adjoint()*Yu*
         Yd.adjoint()*Yd*Yd.adjoint()*md2).trace());
      TRACE_STRUCT.traceYdAdjYuYuAdjYuYuAdjYdmd2 = Re((Yd*Yu.adjoint()*Yu*
         Yu.adjoint()*Yu*Yd.adjoint()*md2).trace());
      TRACE_STRUCT.traceYeAdjYeYeAdjYeYeAdjYeme2 = Re((Ye*Ye.adjoint()*Ye*
         Ye.adjoint()*Ye*Ye.adjoint()*me2).trace());
      TRACE_STRUCT.traceYuAdjYdYdAdjYdYdAdjYumu2 = Re((Yu*Yd.adjoint()*Yd*
         Yd.adjoint()*Yd*Yu.adjoint()*mu2).trace());
      TRACE_STRUCT.traceYuAdjYdYdAdjYuYuAdjYumu2 = Re((Yu*Yd.adjoint()*Yd*
         Yu.adjoint()*Yu*Yu.adjoint()*mu2).trace());
      TRACE_STRUCT.traceYuAdjYuYuAdjYdYdAdjYumu2 = Re((Yu*Yu.adjoint()*Yu*
         Yd.adjoint()*Yd*Yu.adjoint()*mu2).trace());
      TRACE_STRUCT.traceYuAdjYuYuAdjYuYuAdjYumu2 = Re((Yu*Yu.adjoint()*Yu*
         Yu.adjoint()*Yu*Yu.adjoint()*mu2).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdYdAdjYdYdmq2 = Re((Yd.adjoint()*Yd*Yd.adjoint(
         )*Yd*Yd.adjoint()*Yd*mq2).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYdYdAdjYuYumq2 = Re((Yd.adjoint()*Yd*Yd.adjoint(
         )*Yd*Yu.adjoint()*Yu*mq2).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYdYdmq2 = Re((Yd.adjoint()*Yd*Yu.adjoint(
         )*Yu*Yd.adjoint()*Yd*mq2).trace());
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYuYumq2 = Re((Yd.adjoint()*Yd*Yu.adjoint(
         )*Yu*Yu.adjoint()*Yu*mq2).trace());
      TRACE_STRUCT.traceAdjYeYeAdjYeYeAdjYeYeml2 = Re((Ye.adjoint()*Ye*Ye.adjoint(
         )*Ye*Ye.adjoint()*Ye*ml2).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYdYdAdjYdYdmq2 = Re((Yu.adjoint()*Yu*Yd.adjoint(
         )*Yd*Yd.adjoint()*Yd*mq2).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYdYdAdjYuYumq2 = Re((Yu.adjoint()*Yu*Yd.adjoint(
         )*Yd*Yu.adjoint()*Yu*mq2).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYdYdmq2 = Re((Yu.adjoint()*Yu*Yu.adjoint(
         )*Yu*Yd.adjoint()*Yd*mq2).trace());
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYuYumq2 = Re((Yu.adjoint()*Yu*Yu.adjoint(
         )*Yu*Yu.adjoint()*Yu*mq2).trace());

   }

   return soft_traces;
}

std::ostream& operator<<(std::ostream& ostr, const MSSMatMSUSY_mAmu_soft_parameters& soft_pars)
{
   soft_pars.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
