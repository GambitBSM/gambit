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

// File generated at Thu 10 May 2018 15:14:51

#include "MSSM_soft_parameters.hpp"
#include "wrappers.hpp"

namespace flexiblesusy {

#define INPUT(parameter) input.parameter
#define TRACE_STRUCT soft_traces

namespace {

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator+(const Eigen::MatrixBase<Derived>& m, double n)
{
   return m + Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator+(double n, const Eigen::MatrixBase<Derived>& m)
{
   return m + Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator-(const Eigen::MatrixBase<Derived>& m, double n)
{
   return m - Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

template <typename Derived>
typename Eigen::MatrixBase<Derived>::PlainObject operator-(double n, const Eigen::MatrixBase<Derived>& m)
{
   return - m + Eigen::Matrix<double,
                            Eigen::MatrixBase<Derived>::RowsAtCompileTime,
                            Eigen::MatrixBase<Derived>::ColsAtCompileTime>::Identity() * n;
}

} // anonymous namespace

/**
 * Calculates the 1-loop beta function of BMu.
 *
 * @return 1-loop beta function
 */
double MSSM_soft_parameters::calc_beta_BMu_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;


   double beta_BMu;

   beta_BMu = Re(oneOver16PiSqr*(1.2*MassB*Mu*Sqr(g1) + BMu*(3*
      traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu - 0.6*Sqr(g1) - 3*Sqr(g2)) +
      2*Mu*(3*traceAdjYdTYd + traceAdjYeTYe + 3*traceAdjYuTYu + 3*MassWB*Sqr(
      g2))));


   return beta_BMu;
}

/**
 * Calculates the 2-loop beta function of BMu.
 *
 * @return 2-loop beta function
 */
double MSSM_soft_parameters::calc_beta_BMu_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceYdAdjYdTYdAdjYd = TRACE_STRUCT.traceYdAdjYdTYdAdjYd;
   const double traceYdAdjYuTYuAdjYd = TRACE_STRUCT.traceYdAdjYuTYuAdjYd;
   const double traceYeAdjYeTYeAdjYe = TRACE_STRUCT.traceYeAdjYeTYeAdjYe;
   const double traceYuAdjYdTYdAdjYu = TRACE_STRUCT.traceYuAdjYdTYdAdjYu;
   const double traceYuAdjYuTYuAdjYu = TRACE_STRUCT.traceYuAdjYuTYuAdjYu;


   double beta_BMu;

   beta_BMu = Re(0.02*twoLoop*(BMu*(207*Quad(g1) + 10*Sqr(g1)*(-2*
      traceYdAdjYd + 6*traceYeAdjYe + 4*traceYuAdjYu + 9*Sqr(g2)) + 25*(-6*(3*
      traceYdAdjYdYdAdjYd + 2*traceYdAdjYuYuAdjYd + traceYeAdjYeYeAdjYe + 3*
      traceYuAdjYuYuAdjYu) + 15*Quad(g2) + 32*(traceYdAdjYd + traceYuAdjYu)*Sqr
      (g3))) - 4*Mu*(207*MassB*Quad(g1) + 5*Sqr(g1)*(2*(traceAdjYdTYd - 3*
      traceAdjYeTYe - 2*traceAdjYuTYu - MassB*traceYdAdjYd + 3*MassB*
      traceYeAdjYe + 2*MassB*traceYuAdjYu) + 9*(MassB + MassWB)*Sqr(g2)) + 25*(
      6*(3*traceYdAdjYdTYdAdjYd + traceYdAdjYuTYuAdjYd + traceYeAdjYeTYeAdjYe +
      traceYuAdjYdTYdAdjYu + 3*traceYuAdjYuTYuAdjYu) + 15*MassWB*Quad(g2) - 16
      *(traceAdjYdTYd + traceAdjYuTYu - MassG*(traceYdAdjYd + traceYuAdjYu))*
      Sqr(g3)))));


   return beta_BMu;
}

/**
 * Calculates the 3-loop beta function of BMu.
 *
 * @return 3-loop beta function
 */
double MSSM_soft_parameters::calc_beta_BMu_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYdYdAdjYdYdAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYdYdAdjYdYd;
   const double traceAdjYdYdAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeYe =
      TRACE_STRUCT.traceAdjYeYeAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYuAdjYuYu =
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYuYu;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceAdjYdYdAdjYdTYd = TRACE_STRUCT.traceAdjYdYdAdjYdTYd;
   const double traceAdjYdTYdAdjYdYd = TRACE_STRUCT.traceAdjYdTYdAdjYdYd;
   const double traceAdjYeYeAdjYeTYe = TRACE_STRUCT.traceAdjYeYeAdjYeTYe;
   const double traceAdjYeTYeAdjYeYe = TRACE_STRUCT.traceAdjYeTYeAdjYeYe;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYuYuAdjYdTYd = TRACE_STRUCT.traceAdjYuYuAdjYdTYd;
   const double traceAdjYuYuAdjYuTYu = TRACE_STRUCT.traceAdjYuYuAdjYuTYu;
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYu = TRACE_STRUCT.traceAdjYuTYuAdjYuYu;
   const double traceAdjYdYdAdjYdYdAdjYdTYd =
      TRACE_STRUCT.traceAdjYdYdAdjYdYdAdjYdTYd;
   const double traceAdjYdYdAdjYdTYdAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYdTYdAdjYdYd;
   const double traceAdjYdYdAdjYuYuAdjYdTYd =
      TRACE_STRUCT.traceAdjYdYdAdjYuYuAdjYdTYd;
   const double traceAdjYdYdAdjYuTYuAdjYdYd =
      TRACE_STRUCT.traceAdjYdYdAdjYuTYuAdjYdYd;
   const double traceAdjYdTYdAdjYdYdAdjYdYd =
      TRACE_STRUCT.traceAdjYdTYdAdjYdYdAdjYdYd;
   const double traceAdjYdTYdAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYdTYdAdjYuYuAdjYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeTYe =
      TRACE_STRUCT.traceAdjYeYeAdjYeYeAdjYeTYe;
   const double traceAdjYeYeAdjYeTYeAdjYeYe =
      TRACE_STRUCT.traceAdjYeYeAdjYeTYeAdjYeYe;
   const double traceAdjYeTYeAdjYeYeAdjYeYe =
      TRACE_STRUCT.traceAdjYeTYeAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdTYd =
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYdTYd;
   const double traceAdjYuYuAdjYuYuAdjYuTYu =
      TRACE_STRUCT.traceAdjYuYuAdjYuYuAdjYuTYu;
   const double traceAdjYuYuAdjYuTYuAdjYdYd =
      TRACE_STRUCT.traceAdjYuYuAdjYuTYuAdjYdYd;
   const double traceAdjYuYuAdjYuTYuAdjYuYu =
      TRACE_STRUCT.traceAdjYuYuAdjYuTYuAdjYuYu;
   const double traceAdjYuTYuAdjYuYuAdjYdYd =
      TRACE_STRUCT.traceAdjYuTYuAdjYuYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYuAdjYuYu =
      TRACE_STRUCT.traceAdjYuTYuAdjYuYuAdjYuYu;


   double beta_BMu;

   const double beta_BMu_1 = Re(threeLoop*Mu*(49.27404851374539*
      traceAdjYdTYdAdjYdYdAdjYdYd + 18.*traceAdjYdTYdAdjYuYuAdjYdYd + 108.*
      traceAdjYdTYdAdjYdYd*traceAdjYdYd + 108.*traceAdjYdYd*
      traceAdjYdYdAdjYdTYd + 49.27404851374539*traceAdjYdYdAdjYdTYdAdjYdYd +
      108.*traceAdjYdTYd*traceAdjYdYdAdjYdYd + 49.27404851374539*
      traceAdjYdYdAdjYdYdAdjYdTYd + 18.*traceAdjYdYdAdjYuTYuAdjYdYd + 18.*
      traceAdjYdYdAdjYuYuAdjYdTYd + 36.*traceAdjYdYdAdjYdYd*traceAdjYeTYe + 36.
      *traceAdjYdYd*traceAdjYeTYeAdjYeYe + 16.42468283791513*
      traceAdjYeTYeAdjYeYeAdjYeYe + 36.*traceAdjYdTYdAdjYdYd*traceAdjYeYe + 36.
      *traceAdjYdYdAdjYdTYd*traceAdjYeYe + 12.*traceAdjYeTYeAdjYeYe*
      traceAdjYeYe + 36.*traceAdjYdYd*traceAdjYeYeAdjYeTYe + 12.*traceAdjYeYe*
      traceAdjYeYeAdjYeTYe + 16.42468283791513*traceAdjYeYeAdjYeTYeAdjYeYe +
      36.*traceAdjYdTYd*traceAdjYeYeAdjYeYe + 12.*traceAdjYeTYe*
      traceAdjYeYeAdjYeYe + 16.42468283791513*traceAdjYeYeAdjYeYeAdjYeTYe + 36.
      *traceAdjYdYd*traceAdjYuTYuAdjYdYd + 12.*traceAdjYeYe*
      traceAdjYuTYuAdjYdYd + 18.*traceAdjYuTYuAdjYuYuAdjYdYd +
      49.27404851374539*traceAdjYuTYuAdjYuYuAdjYuYu + 36.*traceAdjYuTYuAdjYdYd*
      traceAdjYuYu + 108.*traceAdjYuTYuAdjYuYu*traceAdjYuYu + 36.*traceAdjYdYd*
      traceAdjYuYuAdjYdTYd + 12.*traceAdjYeYe*traceAdjYuYuAdjYdTYd -
      117.341572149176*MassB*Power6(g1) - 3306.887546971633*MassWB*Power6(g2) -
      145.1324875677737*traceAdjYdTYd*Quad(g3) + 290.2649751355474*MassG*
      traceAdjYdYd*Quad(g3) - 145.1324875677737*traceAdjYuTYu*Quad(g3) +
      290.2649751355474*MassG*traceAdjYuYu*Quad(g3) - 202.19238810996313*
      traceAdjYdTYdAdjYdYd*Sqr(g3) - 202.19238810996313*traceAdjYdYdAdjYdTYd*
      Sqr(g3) + 202.19238810996313*MassG*traceAdjYdYdAdjYdYd*Sqr(g3) -
      134.7949254066421*traceAdjYuTYuAdjYdYd*Sqr(g3) - 202.19238810996313*
      traceAdjYuTYuAdjYuYu*Sqr(g3) - 134.7949254066421*traceAdjYuYuAdjYdTYd*Sqr
      (g3) + Quad(g1)*(-37.069001928398215*traceAdjYdTYd + 74.13800385679643*
      MassB*traceAdjYdYd - 61.80533563376292*traceAdjYeTYe + 123.61067126752584
      *MassB*traceAdjYeYe - 81.69201461488161*traceAdjYuTYu +
      163.38402922976323*MassB*traceAdjYuYu + (44.575972394845024*MassB +
      22.287986197422512*MassWB)*Sqr(g2) + (46.72465076838378*MassB +
      23.36232538419189*MassG)*Sqr(g3)) + Quad(g2)*(-384.6887546971633*
      traceAdjYdTYd + 769.3775093943266*MassWB*traceAdjYdYd -
      128.22958489905443*traceAdjYeTYe + 256.45916979810886*MassWB*traceAdjYeYe
      - 384.6887546971633*traceAdjYuTYu + 769.3775093943266*MassWB*
      traceAdjYuYu + (159.28858216494473*MassG + 318.57716432988946*MassWB)*Sqr
      (g3)) + Sqr(g1)*(31.964429108247238*traceAdjYdTYdAdjYdYd +
      31.964429108247238*traceAdjYdYdAdjYdTYd - 31.964429108247238*MassB*
      traceAdjYdYdAdjYdYd - 7.964429108247239*traceAdjYeTYeAdjYeYe -
      7.964429108247239*traceAdjYeYeAdjYeTYe + 7.964429108247239*MassB*
      traceAdjYeYeAdjYeYe + 20.67949254066421*traceAdjYuTYuAdjYdYd +
      14.145190297250922*traceAdjYuTYuAdjYuYu + 20.67949254066421*
      traceAdjYuYuAdjYdTYd + (29.946643662370857*MassB + 59.89328732474171*
      MassWB)*Quad(g2) + (-22.237024256872694*traceAdjYdTYd +
      22.237024256872694*MassB*traceAdjYdYd + 22.237024256872694*MassWB*
      traceAdjYdYd + 22.746643662370854*traceAdjYeTYe - 22.746643662370854*
      MassB*traceAdjYeYe - 22.746643662370854*MassWB*traceAdjYeYe +
      18.89183395962177*traceAdjYuTYu - 18.89183395962177*MassB*traceAdjYuYu -
      18.89183395962177*MassWB*traceAdjYuYu)*Sqr(g2) + (15.98548259488315*
      traceAdjYdTYd - 15.98548259488315*MassB*traceAdjYdYd - 15.98548259488315*
      MassG*traceAdjYdYd + 17.34446767621158*traceAdjYuTYu - 17.34446767621158*
      MassB*traceAdjYuYu - 17.34446767621158*MassG*traceAdjYuYu)*Sqr(g3)) + Sqr
      (g2)*(147.82214554123618*traceAdjYdTYdAdjYdYd + 147.82214554123618*
      traceAdjYdYdAdjYdTYd - 147.82214554123618*MassWB*traceAdjYdYdAdjYdYd +
      49.27404851374539*traceAdjYeTYeAdjYeYe + 49.27404851374539*
      traceAdjYeYeAdjYeTYe - 49.27404851374539*MassWB*traceAdjYeYeAdjYeYe + 72.
      *traceAdjYuTYuAdjYdYd + 147.82214554123618*traceAdjYuTYuAdjYuYu + 72.*
      traceAdjYuYuAdjYdTYd + (82.19238810996313*traceAdjYdTYd -
      82.19238810996313*MassG*traceAdjYdYd - 82.19238810996313*MassWB*
      traceAdjYdYd + 82.19238810996313*traceAdjYuTYu - 82.19238810996313*MassG*
      traceAdjYuYu - 82.19238810996313*MassWB*traceAdjYuYu)*Sqr(g3))));
   const double beta_BMu_2 = Re(threeLoop*(Mu*(36.*traceAdjYdTYd*
      traceAdjYuYuAdjYdYd + 12.*traceAdjYeTYe*traceAdjYuYuAdjYdYd + 36.*
      traceAdjYuTYu*traceAdjYuYuAdjYdYd + traceAdjYuYu*(36.*
      traceAdjYuYuAdjYdTYd + 108.*traceAdjYuYuAdjYuTYu) + 18.*
      traceAdjYuYuAdjYuTYuAdjYdYd + 49.27404851374539*
      traceAdjYuYuAdjYuTYuAdjYuYu + 108.*traceAdjYuTYu*traceAdjYuYuAdjYuYu +
      18.*traceAdjYuYuAdjYuYuAdjYdTYd + 49.27404851374539*
      traceAdjYuYuAdjYuYuAdjYuTYu + (-20.67949254066421*MassB*
      traceAdjYuYuAdjYdYd + 14.145190297250922*traceAdjYuYuAdjYuTYu -
      14.145190297250922*MassB*traceAdjYuYuAdjYuYu)*Sqr(g1) - 72.*MassWB*
      traceAdjYuYuAdjYdYd*Sqr(g2) + 147.82214554123618*traceAdjYuYuAdjYuTYu*Sqr
      (g2) - 147.82214554123618*MassWB*traceAdjYuYuAdjYuYu*Sqr(g2) +
      134.7949254066421*MassG*traceAdjYuYuAdjYdYd*Sqr(g3) - 202.19238810996313*
      traceAdjYuYuAdjYuTYu*Sqr(g3) + 202.19238810996313*MassG*
      traceAdjYuYuAdjYuYu*Sqr(g3)) + BMu*(54*traceAdjYdYd*traceAdjYdYdAdjYdYd +
      24.637024256872696*traceAdjYdYdAdjYdYdAdjYdYd + 9*
      traceAdjYdYdAdjYuYuAdjYdYd + 18*traceAdjYdYdAdjYdYd*traceAdjYeYe + 18*
      traceAdjYdYd*traceAdjYeYeAdjYeYe + 6*traceAdjYeYe*traceAdjYeYeAdjYeYe +
      8.212341418957566*traceAdjYeYeAdjYeYeAdjYeYe + 18*traceAdjYdYd*
      traceAdjYuYuAdjYdYd + 6*traceAdjYeYe*traceAdjYuYuAdjYdYd + 18*
      traceAdjYuYu*traceAdjYuYuAdjYdYd + 54*traceAdjYuYu*traceAdjYuYuAdjYuYu +
      9*traceAdjYuYuAdjYuYuAdjYdYd + 24.637024256872696*
      traceAdjYuYuAdjYuYuAdjYuYu + 19.556928691529336*Power6(g1) +
      551.1479244952723*Power6(g2) - 72.56624378388685*traceAdjYdYd*Quad(g3) -
      72.56624378388685*traceAdjYuYu*Quad(g3) + Quad(g2)*(-192.34437734858165*
      traceAdjYdYd - 64.11479244952722*traceAdjYeYe - 192.34437734858165*
      traceAdjYuYu - 79.64429108247236*Sqr(g3)) + Quad(g1)*(-18.534500964199108
      *traceAdjYdYd - 30.902667816881458*traceAdjYeYe - 40.84600730744081*
      traceAdjYuYu - 11.143993098711256*Sqr(g2) - 11.681162692095945*Sqr(g3)) -
      101.09619405498157*traceAdjYdYdAdjYdYd*Sqr(g3) - 67.39746270332105*
      traceAdjYuYuAdjYdYd*Sqr(g3) - 101.09619405498157*traceAdjYuYuAdjYuYu*Sqr(
      g3) + Sqr(g1)*(15.982214554123619*traceAdjYdYdAdjYdYd - 3.982214554123619
      *traceAdjYeYeAdjYeYe + 10.339746270332105*traceAdjYuYuAdjYdYd +
      7.072595148625461*traceAdjYuYuAdjYuYu - 14.973321831185427*Quad(g2) + (
      -11.118512128436349*traceAdjYdYd + 11.373321831185427*traceAdjYeYe +
      9.445916979810885*traceAdjYuYu)*Sqr(g2) + (7.992741297441576*traceAdjYdYd
      + 8.67223383810579*traceAdjYuYu)*Sqr(g3)) + Sqr(g2)*(73.91107277061809*
      traceAdjYdYdAdjYdYd + 24.637024256872696*traceAdjYeYeAdjYeYe + 36*
      traceAdjYuYuAdjYdYd + 73.91107277061809*traceAdjYuYuAdjYuYu + (
      41.09619405498157*traceAdjYdYd + 41.09619405498157*traceAdjYuYu)*Sqr(g3))
      )));

   beta_BMu = beta_BMu_1 + beta_BMu_2;


   return beta_BMu;
}

} // namespace flexiblesusy
