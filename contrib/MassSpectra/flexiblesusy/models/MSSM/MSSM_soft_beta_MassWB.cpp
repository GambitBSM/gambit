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

// File generated at Thu 10 May 2018 15:15:22

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
 * Calculates the 1-loop beta function of MassWB.
 *
 * @return 1-loop beta function
 */
double MSSM_soft_parameters::calc_beta_MassWB_1_loop(const Soft_traces& soft_traces) const
{


   double beta_MassWB;

   beta_MassWB = Re(2*MassWB*oneOver16PiSqr*Sqr(g2));


   return beta_MassWB;
}

/**
 * Calculates the 2-loop beta function of MassWB.
 *
 * @return 2-loop beta function
 */
double MSSM_soft_parameters::calc_beta_MassWB_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;


   double beta_MassWB;

   beta_MassWB = Re(0.4*twoLoop*Sqr(g2)*(9*(MassB + MassWB)*Sqr(g1) + 10*
      (3*traceAdjYdTYd + traceAdjYeTYe + 3*traceAdjYuTYu - 3*MassWB*
      traceYdAdjYd - MassWB*traceYeAdjYe - 3*MassWB*traceYuAdjYu + 25*MassWB*
      Sqr(g2) + 12*(MassG + MassWB)*Sqr(g3))));


   return beta_MassWB;
}

/**
 * Calculates the 3-loop beta function of MassWB.
 *
 * @return 3-loop beta function
 */
double MSSM_soft_parameters::calc_beta_MassWB_3_loop(const Soft_traces& soft_traces) const
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


   double beta_MassWB;

   beta_MassWB = Re(0.08*threeLoop*Sqr(g2)*(-457*(2*MassB + MassWB)*Quad(
      g1) - 5*Sqr(g1)*(11*MassB*traceAdjYdYd + 11*MassWB*traceAdjYdYd + 21*
      MassB*traceAdjYeYe + 21*MassWB*traceAdjYeYe + 29*MassB*traceAdjYuYu + 29*
      MassWB*traceAdjYuYu - 11*traceTYdAdjYd - 21*traceTYeAdjYe - 29*
      traceTYuAdjYu - 9*(MassB + 2*MassWB)*Sqr(g2) + 8*(MassB + MassG + MassWB)
      *Sqr(g3)) + 25*(105*MassWB*Quad(g2) + Sqr(g2)*(11*(-2*MassWB*(3*
      traceAdjYdYd + traceAdjYeYe + 3*traceAdjYuYu) + 3*traceTYdAdjYd +
      traceTYeAdjYe + 3*traceTYuAdjYu) + 24*(MassG + 2*MassWB)*Sqr(g3)) + 2*(
      -24*traceAdjYdTYdAdjYdYd + 12*MassWB*traceAdjYdYdAdjYdYd - 8*
      traceAdjYeTYeAdjYeYe + 6*MassWB*traceAdjYdYd*traceAdjYeYe + 4*MassWB*
      traceAdjYeYeAdjYeYe - 6*traceAdjYuTYuAdjYdYd - 24*traceAdjYuTYuAdjYuYu +
      6*MassWB*traceAdjYuYuAdjYdYd + 12*MassWB*traceAdjYuYuAdjYuYu - 18*
      traceAdjYdYd*traceTYdAdjYd - 6*traceAdjYeYe*traceTYdAdjYd - 6*
      traceTYdAdjYuYuAdjYd - 6*traceAdjYdYd*traceTYeAdjYe - 2*traceAdjYeYe*
      traceTYeAdjYe - 18*traceAdjYuYu*traceTYuAdjYu + 22*(2*MassG + MassWB)*
      Quad(g3) - 16*(MassG*(traceAdjYdYd + traceAdjYuYu) + MassWB*(traceAdjYdYd
      + traceAdjYuYu) - traceTYdAdjYd - traceTYuAdjYu)*Sqr(g3) + 9*MassWB*Sqr(
      traceAdjYdYd) + MassWB*Sqr(traceAdjYeYe) + 9*MassWB*Sqr(traceAdjYuYu)))))
      ;


   return beta_MassWB;
}

} // namespace flexiblesusy
