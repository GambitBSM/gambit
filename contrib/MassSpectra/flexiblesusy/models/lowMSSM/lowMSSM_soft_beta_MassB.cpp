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

// File generated at Thu 10 May 2018 15:06:01

#include "lowMSSM_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of MassB.
 *
 * @return 1-loop beta function
 */
double lowMSSM_soft_parameters::calc_beta_MassB_1_loop(const Soft_traces& soft_traces) const
{


   double beta_MassB;

   beta_MassB = Re(13.2*MassB*oneOver16PiSqr*Sqr(g1));


   return beta_MassB;
}

/**
 * Calculates the 2-loop beta function of MassB.
 *
 * @return 2-loop beta function
 */
double lowMSSM_soft_parameters::calc_beta_MassB_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;


   double beta_MassB;

   beta_MassB = Re(0.08*twoLoop*Sqr(g1)*(398*MassB*Sqr(g1) + 135*(MassB +
      MassWB)*Sqr(g2) + 10*(7*traceAdjYdTYd + 9*traceAdjYeTYe + 13*
      traceAdjYuTYu - 7*MassB*traceYdAdjYd - 9*MassB*traceYeAdjYe - 13*MassB*
      traceYuAdjYu + 44*(MassB + MassG)*Sqr(g3))));


   return beta_MassB;
}

/**
 * Calculates the 3-loop beta function of MassB.
 *
 * @return 3-loop beta function
 */
double lowMSSM_soft_parameters::calc_beta_MassB_3_loop(const Soft_traces& soft_traces) const
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
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYu = TRACE_STRUCT.traceAdjYuTYuAdjYuYu;
   const double traceTYdAdjYuYuAdjYd = TRACE_STRUCT.traceTYdAdjYuYuAdjYd;


   double beta_MassB;

   beta_MassB = Re(-0.005333333333333333*threeLoop*Sqr(g1)*(96351*MassB*
      Quad(g1) + 5*Sqr(g1)*(98*MassB*traceAdjYdYd + 486*MassB*traceAdjYeYe +
      338*MassB*traceAdjYuYu - 49*traceTYdAdjYd - 243*traceTYeAdjYe - 169*
      traceTYuAdjYu + 207*(2*MassB + MassWB)*Sqr(g2) + 1096*(2*MassB + MassG)*
      Sqr(g3)) + 25*(243*(MassB + 2*MassWB)*Quad(g2) - 484*(MassB + 2*MassG)*
      Quad(g3) + 32*(8*MassB*traceAdjYdYd + 8*MassG*traceAdjYdYd + 11*MassB*
      traceAdjYuYu + 11*MassG*traceAdjYuYu - 8*traceTYdAdjYd - 11*traceTYuAdjYu
      )*Sqr(g3) + 9*Sqr(g2)*(11*MassWB*traceAdjYdYd + 21*MassWB*traceAdjYeYe +
      29*MassWB*traceAdjYuYu + MassB*(11*traceAdjYdYd + 21*traceAdjYeYe + 29*
      traceAdjYuYu) - 11*traceTYdAdjYd - 21*traceTYeAdjYe - 29*traceTYuAdjYu +
      8*(MassB + MassG + MassWB)*Sqr(g3)) + 6*(54*traceAdjYdTYdAdjYdYd + 54*
      traceAdjYeTYeAdjYeYe + 29*traceAdjYuTYuAdjYdYd + 84*traceAdjYuTYuAdjYuYu
      + 36*traceAdjYdYd*traceTYdAdjYd + 42*traceAdjYeYe*traceTYdAdjYd + 29*
      traceTYdAdjYuYuAdjYd + 42*traceAdjYdYd*traceTYeAdjYe + 24*traceAdjYeYe*
      traceTYeAdjYe + 90*traceAdjYuYu*traceTYuAdjYu - MassB*(27*
      traceAdjYdYdAdjYdYd + 42*traceAdjYdYd*traceAdjYeYe + 27*
      traceAdjYeYeAdjYeYe + 29*traceAdjYuYuAdjYdYd + 42*traceAdjYuYuAdjYuYu +
      18*Sqr(traceAdjYdYd) + 12*Sqr(traceAdjYeYe) + 45*Sqr(traceAdjYuYu))))));


   return beta_MassB;
}

} // namespace flexiblesusy
