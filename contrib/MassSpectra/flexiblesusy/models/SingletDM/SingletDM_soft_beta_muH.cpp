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

// File generated at Thu 10 May 2018 14:42:52

#include "SingletDM_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of muH.
 *
 * @return 1-loop beta function
 */
double SingletDM_soft_parameters::calc_beta_muH_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_muH;

   beta_muH = Re(oneOver16PiSqr*(6*LamH*muH + LamSH*muS + 6*muH*
      traceYdAdjYd + 2*muH*traceYeAdjYe + 6*muH*traceYuAdjYu - 0.9*muH*Sqr(g1)
      - 4.5*muH*Sqr(g2)));


   return beta_muH;
}

/**
 * Calculates the 2-loop beta function of muH.
 *
 * @return 2-loop beta function
 */
double SingletDM_soft_parameters::calc_beta_muH_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_muH;

   beta_muH = Re(0.0025*twoLoop*(1671*muH*Quad(g1) + 10*muH*Sqr(g1)*(288*
      LamH + 50*traceYdAdjYd + 150*traceYeAdjYe + 170*traceYuAdjYu + 45*Sqr(g2)
      ) - 25*(145*muH*Quad(g2) - 12*muH*(48*LamH + 5*(3*traceYdAdjYd +
      traceYeAdjYe + 3*traceYuAdjYu))*Sqr(g2) + 8*(24*LamH*muH*(3*traceYdAdjYd
      + traceYeAdjYe + 3*traceYuAdjYu) + 3*muH*(9*traceYdAdjYdYdAdjYd + 14*
      traceYdAdjYuYuAdjYd + 3*traceYeAdjYeYeAdjYe + 9*traceYuAdjYuYuAdjYu) - 80
      *muH*(traceYdAdjYd + traceYuAdjYu)*Sqr(g3) + 30*muH*Sqr(LamH) + (muH + 4*
      muS)*Sqr(LamSH)))));


   return beta_muH;
}

/**
 * Calculates the 3-loop beta function of muH.
 *
 * @return 3-loop beta function
 */
double SingletDM_soft_parameters::calc_beta_muH_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_muH;

   beta_muH = 0;


   return beta_muH;
}

} // namespace flexiblesusy
