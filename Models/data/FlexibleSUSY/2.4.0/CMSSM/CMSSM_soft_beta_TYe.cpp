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

// File generated at Thu 10 Oct 2019 17:27:30

#include "CMSSM_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of TYe.
 *
 * @return 1-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYe_1_loop(const Soft_traces& soft_traces) const
{
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;


   Eigen::Matrix<double,3,3> beta_TYe;

   beta_TYe = (oneOver16PiSqr*(0.2*(30*traceAdjYdTYd*Ye + 10*traceAdjYeTYe*Ye +
      18*MassB*Ye*Sqr(g1) + 30*MassWB*Ye*Sqr(g2) + 15*traceYdAdjYd*TYe + 5*
      traceYeAdjYe*TYe - 9*Sqr(g1)*TYe - 15*Sqr(g2)*TYe) + 4*(Ye*Ye.adjoint()*
      TYe) + 5*(TYe*Ye.adjoint()*Ye))).real();


   return beta_TYe;
}

/**
 * Calculates the 2-loop beta function of TYe.
 *
 * @return 2-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYe_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceYdAdjYdTYdAdjYd = TRACE_STRUCT.traceYdAdjYdTYdAdjYd;
   const double traceYdAdjYuTYuAdjYd = TRACE_STRUCT.traceYdAdjYuTYuAdjYd;
   const double traceYeAdjYeTYeAdjYe = TRACE_STRUCT.traceYeAdjYeTYeAdjYe;
   const double traceYuAdjYdTYdAdjYu = TRACE_STRUCT.traceYuAdjYdTYdAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;


   Eigen::Matrix<double,3,3> beta_TYe;

   beta_TYe = (twoLoop*(0.1*(-360*traceYdAdjYdTYdAdjYd*Ye - 60*
      traceYdAdjYuTYuAdjYd*Ye - 120*traceYeAdjYeTYeAdjYe*Ye - 60*
      traceYuAdjYdTYdAdjYu*Ye - 540*MassB*Ye*Quad(g1) - 300*MassWB*Ye*Quad(g2)
      - 8*traceAdjYdTYd*Ye*Sqr(g1) + 24*traceAdjYeTYe*Ye*Sqr(g1) + 8*MassB*
      traceYdAdjYd*Ye*Sqr(g1) - 24*MassB*traceYeAdjYe*Ye*Sqr(g1) - 36*MassB*Ye*
      Sqr(g1)*Sqr(g2) - 36*MassWB*Ye*Sqr(g1)*Sqr(g2) + 320*traceAdjYdTYd*Ye*Sqr
      (g3) - 320*MassG*traceYdAdjYd*Ye*Sqr(g3) - 90*traceYdAdjYdYdAdjYd*TYe -
      30*traceYdAdjYuYuAdjYd*TYe - 30*traceYeAdjYeYeAdjYe*TYe + 135*Quad(g1)*
      TYe + 75*Quad(g2)*TYe - 4*traceYdAdjYd*Sqr(g1)*TYe + 12*traceYeAdjYe*Sqr(
      g1)*TYe + 18*Sqr(g1)*Sqr(g2)*TYe + 160*traceYdAdjYd*Sqr(g3)*TYe) - 6*(3*
      traceAdjYdTYd + traceAdjYeTYe + 2*MassWB*Sqr(g2))*(Ye*Ye.adjoint()*Ye) +
      0.4*(-30*traceYdAdjYd - 10*traceYeAdjYe + 3*Sqr(g1) + 15*Sqr(g2))*(Ye*Ye.
      adjoint()*TYe) + 0.2*(-75*traceYdAdjYd - 25*traceYeAdjYe - 6*Sqr(g1) + 60
      *Sqr(g2))*(TYe*Ye.adjoint()*Ye) - 6*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*TYe)
      - 8*(Ye*Ye.adjoint()*TYe*Ye.adjoint()*Ye) - 6*(TYe*Ye.adjoint()*Ye*Ye.
      adjoint()*Ye))).real();


   return beta_TYe;
}

/**
 * Calculates the 3-loop beta function of TYe.
 *
 * @return 3-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYe_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceTYdAdjYd = TRACE_STRUCT.traceTYdAdjYd;
   const double traceTYeAdjYe = TRACE_STRUCT.traceTYeAdjYe;
   const double traceTYuAdjYu = TRACE_STRUCT.traceTYuAdjYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYdTYdAdjYdYd = TRACE_STRUCT.traceAdjYdTYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYeTYeAdjYeYe = TRACE_STRUCT.traceAdjYeTYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceTYdAdjYuYuAdjYd = TRACE_STRUCT.traceTYdAdjYuYuAdjYd;
   const double traceAdjYdYdAdjYdYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdYdAdjYdYd;
   const double traceAdjYdYdAdjYdTYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdTYdAdjYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeYeAdjYeYe;
   const double traceAdjYeYeAdjYeTYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeTYeAdjYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuTYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuTYuAdjYuYuAdjYdYd;
   const double traceTYdAdjYuYuAdjYuYuAdjYd = TRACE_STRUCT.
      traceTYdAdjYuYuAdjYuYuAdjYd;


   Eigen::Matrix<double,3,3> beta_TYe;

   const Eigen::Matrix<double,3,3> beta_TYe_1 = ((-0.0013333333333333333*
      threeLoop*Ye*(-162000*traceAdjYdTYdAdjYdYd*traceAdjYdYd - 13500*
      traceAdjYdYdAdjYdTYdAdjYdYd - 54000*traceAdjYdYd*traceAdjYeTYeAdjYeYe -
      54000*traceAdjYdTYdAdjYdYd*traceAdjYeYe - 18000*traceAdjYeTYeAdjYeYe*
      traceAdjYeYe - 4500*traceAdjYeYeAdjYeTYeAdjYeYe - 13500*
      traceAdjYuTYuAdjYuYuAdjYdYd - 27000*traceAdjYuTYuAdjYdYd*traceAdjYuYu -
      13500*traceAdjYuYuAdjYuTYuAdjYdYd - 81000*traceAdjYdYdAdjYdYd*
      traceTYdAdjYd - 27000*traceAdjYeYeAdjYeYe*traceTYdAdjYd - 27000*
      traceAdjYuYu*traceTYdAdjYuYuAdjYd - 13500*traceTYdAdjYuYuAdjYuYuAdjYd -
      27000*traceAdjYdYdAdjYdYd*traceTYeAdjYe - 9000*traceAdjYeYeAdjYeYe*
      traceTYeAdjYe - 27000*traceAdjYuYuAdjYdYd*traceTYuAdjYu + 449874*MassB*
      Power6(g1) + 776250*MassWB*Power6(g2) - 75250*MassB*traceAdjYdYd*Quad(g1)
      - 130950*MassB*traceAdjYeYe*Quad(g1) - 70200*MassB*traceAdjYuYu*Quad(g1)
      + 37625*traceTYdAdjYd*Quad(g1) + 65475*traceTYeAdjYe*Quad(g1) + 35100*
      traceTYuAdjYu*Quad(g1) - 236250*MassWB*traceAdjYdYd*Quad(g2) - 78750*
      MassWB*traceAdjYeYe*Quad(g2) - 135000*MassWB*traceAdjYuYu*Quad(g2) +
      118125*traceTYdAdjYd*Quad(g2) + 39375*traceTYeAdjYe*Quad(g2) + 67500*
      traceTYuAdjYu*Quad(g2) - 160000*MassG*traceAdjYdYd*Quad(g3) + 80000*
      traceTYdAdjYd*Quad(g3) - 9000*traceAdjYdTYdAdjYdYd*Sqr(g1) + 4500*MassB*
      traceAdjYdYdAdjYdYd*Sqr(g1) - 27000*traceAdjYeTYeAdjYeYe*Sqr(g1) + 13500*
      MassB*traceAdjYeYeAdjYeYe*Sqr(g1) + 3600*traceAdjYuTYuAdjYdYd*Sqr(g1) -
      3600*MassB*traceAdjYuYuAdjYdYd*Sqr(g1) + 3600*traceTYdAdjYuYuAdjYd*Sqr(g1
      ) + 6750*MassB*Quad(g2)*Sqr(g1) + 13500*MassWB*Quad(g2)*Sqr(g1) - 27000*
      traceAdjYdTYdAdjYdYd*Sqr(g2) + 13500*MassWB*traceAdjYdYdAdjYdYd*Sqr(g2) -
      9000*traceAdjYeTYeAdjYeYe*Sqr(g2) + 4500*MassWB*traceAdjYeYeAdjYeYe*Sqr(
      g2) - 27000*traceAdjYuTYuAdjYdYd*Sqr(g2) + 27000*MassWB*
      traceAdjYuYuAdjYdYd*Sqr(g2) - 27000*traceTYdAdjYuYuAdjYd*Sqr(g2) + 50220*
      MassB*Quad(g1)*Sqr(g2) + 25110*MassWB*Quad(g1)*Sqr(g2) - 450*MassB*
      traceAdjYdYd*Sqr(g1)*Sqr(g2) - 450*MassWB*traceAdjYdYd*Sqr(g1)*Sqr(g2) -
      12150*MassB*traceAdjYeYe*Sqr(g1)*Sqr(g2) - 12150*MassWB*traceAdjYeYe*Sqr(
      g1)*Sqr(g2) + 450*traceTYdAdjYd*Sqr(g1)*Sqr(g2) + 12150*traceTYeAdjYe*Sqr
      (g1)*Sqr(g2) - 216000*traceAdjYdTYdAdjYdYd*Sqr(g3) + 108000*MassG*
      traceAdjYdYdAdjYdYd*Sqr(g3) - 36000*traceAdjYuTYuAdjYdYd*Sqr(g3) + 36000*
      MassG*traceAdjYuYuAdjYdYd*Sqr(g3) - 36000*traceTYdAdjYuYuAdjYd*Sqr(g3) +
      237600*MassB*Quad(g1)*Sqr(g3) + 118800*MassG*Quad(g1)*Sqr(g3) + 270000*
      MassG*Quad(g2)*Sqr(g3) + 540000*MassWB*Quad(g2)*Sqr(g3) - 28400*MassB*
      traceAdjYdYd*Sqr(g1)*Sqr(g3) - 28400*MassG*traceAdjYdYd*Sqr(g1)*Sqr(g3) +
      28400*traceTYdAdjYd*Sqr(g1)*Sqr(g3) - 198000*MassG*traceAdjYdYd*Sqr(g2)*
      Sqr(g3) - 198000*MassWB*traceAdjYdYd*Sqr(g2)*Sqr(g3) + 198000*
      traceTYdAdjYd*Sqr(g2)*Sqr(g3)) + 0.016*threeLoop*(6750*
      traceAdjYdYdAdjYdTYdAdjYdYd + 16119*MassB*Power6(g1) - 118125*MassWB*
      Power6(g2) + 385*MassB*traceAdjYdYd*Quad(g1) - 405*MassB*traceAdjYeYe*
      Quad(g1) + 23625*MassWB*traceAdjYdYd*Quad(g2) + 4000*MassG*traceAdjYdYd*
      Quad(g3) + 2700*traceAdjYdTYdAdjYdYd*Sqr(g1) - 1350*MassB*
      traceAdjYdYdAdjYdYd*Sqr(g1) - 2700*traceAdjYeTYeAdjYeYe*Sqr(g1) + 2025*
      MassB*Quad(g2)*Sqr(g1) + 4050*MassWB*Quad(g2)*Sqr(g1) + 13500*
      traceAdjYdTYdAdjYdYd*Sqr(g2) - 6750*MassWB*traceAdjYdYdAdjYdYd*Sqr(g2) +
      4500*traceAdjYeTYeAdjYeYe*Sqr(g2) + 7290*MassB*Quad(g1)*Sqr(g2) + 3645*
      MassWB*Quad(g1)*Sqr(g2) + 1125*MassB*traceAdjYdYd*Sqr(g1)*Sqr(g2) + 1125*
      MassWB*traceAdjYdYd*Sqr(g1)*Sqr(g2) - 36000*traceAdjYdTYdAdjYdYd*Sqr(g3)
      + 18000*MassG*traceAdjYdYdAdjYdYd*Sqr(g3) + 23760*MassB*Quad(g1)*Sqr(g3)
      + 11880*MassG*Quad(g1)*Sqr(g3) + 27000*MassG*Quad(g2)*Sqr(g3) + 54000*
      MassWB*Quad(g2)*Sqr(g3) - 2800*MassB*traceAdjYdYd*Sqr(g1)*Sqr(g3) - 2800*
      MassG*traceAdjYdYd*Sqr(g1)*Sqr(g3) - 18000*MassG*traceAdjYdYd*Sqr(g2)*Sqr
      (g3) - 18000*MassWB*traceAdjYdYd*Sqr(g2)*Sqr(g3))*(Ye*1.2020569031595942)
      )*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYe_2 = ((-0.04*threeLoop*(-900*
      traceAdjYeYeAdjYeTYeAdjYeYe + 77*traceTYdAdjYd*Quad(g1) - 81*
      traceTYeAdjYe*Quad(g1) - 3150*MassWB*traceAdjYeYe*Quad(g2) + 4725*
      traceTYdAdjYd*Quad(g2) + 1575*traceTYeAdjYe*Quad(g2) + 800*traceTYdAdjYd*
      Quad(g3) - 540*MassB*traceAdjYeYeAdjYeYe*Sqr(g1) - 420*
      traceAdjYuTYuAdjYdYd*Sqr(g1) + 420*MassB*traceAdjYuYuAdjYdYd*Sqr(g1) -
      420*traceTYdAdjYuYuAdjYd*Sqr(g1) + 900*MassWB*traceAdjYeYeAdjYeYe*Sqr(g2)
      + 810*MassB*traceAdjYeYe*Sqr(g1)*Sqr(g2) + 810*MassWB*traceAdjYeYe*Sqr(g1
      )*Sqr(g2) + 450*traceTYdAdjYd*Sqr(g1)*Sqr(g2) - 810*traceTYeAdjYe*Sqr(g1)
      *Sqr(g2) + 2400*traceAdjYuTYuAdjYdYd*Sqr(g3) - 2400*MassG*
      traceAdjYuYuAdjYdYd*Sqr(g3) + 2400*traceTYdAdjYuYuAdjYd*Sqr(g3) - 1120*
      traceTYdAdjYd*Sqr(g1)*Sqr(g3) - 7200*traceTYdAdjYd*Sqr(g2)*Sqr(g3))*(Ye*
      1.2020569031595942) - 0.004*threeLoop*(-4500*traceAdjYdYdAdjYdYdAdjYdYd -
      1500*traceAdjYeYeAdjYeYeAdjYeYe + 10746*Power6(g1) - 78750*Power6(g2) +
      385*traceAdjYdYd*Quad(g1) - 405*traceAdjYeYe*Quad(g1) + 23625*
      traceAdjYdYd*Quad(g2) + 7875*traceAdjYeYe*Quad(g2) + 4000*traceAdjYdYd*
      Quad(g3) - 2700*traceAdjYdYdAdjYdYd*Sqr(g1) + 2700*traceAdjYeYeAdjYeYe*
      Sqr(g1) - 2100*traceAdjYuYuAdjYdYd*Sqr(g1) + 4050*Quad(g2)*Sqr(g1) -
      13500*traceAdjYdYdAdjYdYd*Sqr(g2) - 4500*traceAdjYeYeAdjYeYe*Sqr(g2) +
      7290*Quad(g1)*Sqr(g2) + 2250*traceAdjYdYd*Sqr(g1)*Sqr(g2) - 4050*
      traceAdjYeYe*Sqr(g1)*Sqr(g2) + 36000*traceAdjYdYdAdjYdYd*Sqr(g3) + 12000*
      traceAdjYuYuAdjYdYd*Sqr(g3) + 23760*Quad(g1)*Sqr(g3) + 54000*Quad(g2)*Sqr
      (g3) - 5600*traceAdjYdYd*Sqr(g1)*Sqr(g3) - 36000*traceAdjYdYd*Sqr(g2)*Sqr
      (g3))*(TYe*1.2020569031595942) + 0.12*threeLoop*(1800*
      traceAdjYdTYdAdjYdYd + 600*traceAdjYeTYeAdjYeYe + 300*
      traceAdjYuTYuAdjYdYd - 900*traceAdjYdYd*traceTYdAdjYd - 300*traceAdjYeYe*
      traceTYdAdjYd + 300*traceTYdAdjYuYuAdjYd - 300*traceAdjYdYd*traceTYeAdjYe
       - 100*traceAdjYeYe*traceTYeAdjYe + 1917*MassB*Quad(g1) + 1825*MassWB*
      Quad(g2) - 490*MassB*traceAdjYdYd*Sqr(g1) - 30*MassB*traceAdjYeYe*Sqr(g1)
      + 490*traceTYdAdjYd*Sqr(g1) + 30*traceTYeAdjYe*Sqr(g1) - 750*MassWB*
      traceAdjYdYd*Sqr(g2) - 250*MassWB*traceAdjYeYe*Sqr(g2) + 750*
      traceTYdAdjYd*Sqr(g2) + 250*traceTYeAdjYe*Sqr(g2) + 585*MassB*Sqr(g1)*Sqr
      (g2) + 585*MassWB*Sqr(g1)*Sqr(g2) + 1600*MassG*traceAdjYdYd*Sqr(g3) -
      1600*traceTYdAdjYd*Sqr(g3))*(Ye*Ye.adjoint()*Ye) - 0.04*threeLoop*(-1800*
      traceAdjYdYdAdjYdYd + 600*traceAdjYdYd*traceAdjYeYe - 600*
      traceAdjYeYeAdjYeYe - 600*traceAdjYuYuAdjYdYd + 2124*Quad(g1) + 1650*Quad
      (g2) - 935*traceAdjYdYd*Sqr(g1) - 45*traceAdjYeYe*Sqr(g1) - 1575*
      traceAdjYdYd*Sqr(g2) - 525*traceAdjYeYe*Sqr(g2) + 1080*Sqr(g1)*Sqr(g2) +
      3200*traceAdjYdYd*Sqr(g3) + 900*Sqr(traceAdjYdYd) + 100*Sqr(traceAdjYeYe)
      )*(Ye*Ye.adjoint()*TYe) - 0.01*threeLoop*(-9000*traceAdjYdYdAdjYdYd +
      3000*traceAdjYdYd*traceAdjYeYe - 3000*traceAdjYeYeAdjYeYe - 3000*
      traceAdjYuYuAdjYdYd + 8757*Quad(g1) + 9825*Quad(g2) - 5080*traceAdjYdYd*
      Sqr(g1) - 360*traceAdjYeYe*Sqr(g1) - 7200*traceAdjYdYd*Sqr(g2) - 2400*
      traceAdjYeYe*Sqr(g2) + 6210*Sqr(g1)*Sqr(g2) + 16000*traceAdjYdYd*Sqr(g3)
      + 4500*Sqr(traceAdjYdYd) + 500*Sqr(traceAdjYeYe))*(TYe*Ye.adjoint()*Ye) +
      0.72*threeLoop*(81*MassB*Quad(g1) + 225*MassWB*Quad(g2) + 10*MassB*
      traceAdjYdYd*Sqr(g1) - 135*MassB*Sqr(g1)*Sqr(g2) - 135*MassWB*Sqr(g1)*Sqr
      (g2))*(Ye*Ye.adjoint()*Ye*1.2020569031595942))*UNITMATRIX(3)).real();
   const Eigen::Matrix<double,3,3> beta_TYe_3 = ((0.0006666666666666666*
      threeLoop*(81000*traceAdjYdYd*traceAdjYdYdAdjYdYd + 4500*
      traceAdjYdYdAdjYdYdAdjYdYd + 27000*traceAdjYdYdAdjYdYd*traceAdjYeYe +
      27000*traceAdjYdYd*traceAdjYeYeAdjYeYe + 9000*traceAdjYeYe*
      traceAdjYeYeAdjYeYe + 1500*traceAdjYeYeAdjYeYeAdjYeYe + 27000*
      traceAdjYuYu*traceAdjYuYuAdjYdYd + 13500*traceAdjYuYuAdjYuYuAdjYdYd +
      149958*Power6(g1) + 258750*Power6(g2) - 37625*traceAdjYdYd*Quad(g1) -
      65475*traceAdjYeYe*Quad(g1) - 35100*traceAdjYuYu*Quad(g1) - 118125*
      traceAdjYdYd*Quad(g2) - 39375*traceAdjYeYe*Quad(g2) - 67500*traceAdjYuYu*
      Quad(g2) - 80000*traceAdjYdYd*Quad(g3) + 4500*traceAdjYdYdAdjYdYd*Sqr(g1)
      + 13500*traceAdjYeYeAdjYeYe*Sqr(g1) - 3600*traceAdjYuYuAdjYdYd*Sqr(g1) +
      6750*Quad(g2)*Sqr(g1) + 13500*traceAdjYdYdAdjYdYd*Sqr(g2) + 4500*
      traceAdjYeYeAdjYeYe*Sqr(g2) + 27000*traceAdjYuYuAdjYdYd*Sqr(g2) + 25110*
      Quad(g1)*Sqr(g2) - 450*traceAdjYdYd*Sqr(g1)*Sqr(g2) - 12150*traceAdjYeYe*
      Sqr(g1)*Sqr(g2) + 108000*traceAdjYdYdAdjYdYd*Sqr(g3) + 36000*
      traceAdjYuYuAdjYdYd*Sqr(g3) + 118800*Quad(g1)*Sqr(g3) + 270000*Quad(g2)*
      Sqr(g3) - 28400*traceAdjYdYd*Sqr(g1)*Sqr(g3) - 198000*traceAdjYdYd*Sqr(g2
      )*Sqr(g3))*TYe - 7.2*threeLoop*(3*MassB*traceAdjYeYe*Sqr(g1) +
      traceTYdAdjYd*Sqr(g1) - 3*traceTYeAdjYe*Sqr(g1) - 15*MassWB*traceAdjYdYd*
      Sqr(g2) - 5*MassWB*traceAdjYeYe*Sqr(g2) + 15*traceTYdAdjYd*Sqr(g2) + 5*
      traceTYeAdjYe*Sqr(g2) + 40*MassG*traceAdjYdYd*Sqr(g3) - 40*traceTYdAdjYd*
      Sqr(g3))*(Ye*Ye.adjoint()*Ye*1.2020569031595942) - 0.24*threeLoop*(54*
      Quad(g1) + 300*Quad(g2) + 65*traceAdjYdYd*Sqr(g1) - 45*traceAdjYeYe*Sqr(
      g1) + 225*traceAdjYdYd*Sqr(g2) + 75*traceAdjYeYe*Sqr(g2) - 270*Sqr(g1)*
      Sqr(g2) - 800*traceAdjYdYd*Sqr(g3))*(Ye*Ye.adjoint()*TYe*
      1.2020569031595942) - 0.06*threeLoop*(513*Quad(g1) + 825*Quad(g2) - 80*
      traceAdjYdYd*Sqr(g1) - 360*traceAdjYeYe*Sqr(g1) + 1800*traceAdjYdYd*Sqr(
      g2) + 600*traceAdjYeYe*Sqr(g2) - 1350*Sqr(g1)*Sqr(g2) - 4000*traceAdjYdYd
      *Sqr(g3))*(TYe*Ye.adjoint()*Ye*1.2020569031595942) - 0.8*threeLoop*(-30*
      traceTYdAdjYd - 10*traceTYeAdjYe + 27*MassB*Sqr(g1) + 15*MassWB*Sqr(g2))*
      (Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye) + 0.6*threeLoop*(30*traceAdjYdYd +
      10*traceAdjYeYe + 33*Sqr(g1) + 5*Sqr(g2))*(Ye*Ye.adjoint()*Ye*Ye.adjoint(
      )*TYe) + 0.8*threeLoop*(30*traceAdjYdYd + 10*traceAdjYeYe + 27*Sqr(g1) +
      15*Sqr(g2))*(Ye*Ye.adjoint()*TYe*Ye.adjoint()*Ye) + 0.6*threeLoop*(30*
      traceAdjYdYd + 10*traceAdjYeYe + 21*Sqr(g1) + 25*Sqr(g2))*(TYe*Ye.adjoint
      ()*Ye*Ye.adjoint()*Ye) - 3.6*threeLoop*(3*Sqr(g1) - 5*Sqr(g2))*(Ye*Ye.
      adjoint()*Ye*Ye.adjoint()*TYe*1.2020569031595942) + 3.6*threeLoop*(3*Sqr(
      g1) - 5*Sqr(g2))*(TYe*Ye.adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942)
      + 6*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*TYe) + 12*
      threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*TYe*Ye.adjoint()*Ye) + 12*
      threeLoop*(Ye*Ye.adjoint()*TYe*Ye.adjoint()*Ye*Ye.adjoint()*Ye) + 12*
      threeLoop*(TYe*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye) + 24*
      threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*TYe*
      1.2020569031595942) + 36*threeLoop*(Ye*Ye.adjoint()*Ye*Ye.adjoint()*TYe*
      Ye.adjoint()*Ye*1.2020569031595942) + 36*threeLoop*(Ye*Ye.adjoint()*TYe*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942) + 30*threeLoop*(TYe*
      Ye.adjoint()*Ye*Ye.adjoint()*Ye*Ye.adjoint()*Ye*1.2020569031595942))*
      UNITMATRIX(3)).real();

   beta_TYe = beta_TYe_1 + beta_TYe_2 + beta_TYe_3;


   return beta_TYe;
}

/**
 * Calculates the 4-loop beta function of TYe.
 *
 * @return 4-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYe_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_TYe;

   beta_TYe = ZEROMATRIX(3,3);


   return beta_TYe;
}

/**
 * Calculates the 5-loop beta function of TYe.
 *
 * @return 5-loop beta function
 */
Eigen::Matrix<double,3,3> CMSSM_soft_parameters::calc_beta_TYe_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   Eigen::Matrix<double,3,3> beta_TYe;

   beta_TYe = ZEROMATRIX(3,3);


   return beta_TYe;
}

} // namespace flexiblesusy
