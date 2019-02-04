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

// File generated at Sat 26 May 2018 14:35:38

#include "ScalarSingletDM_Z3_soft_parameters.hpp"
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
 * Calculates the 1-loop beta function of muS.
 *
 * @return 1-loop beta function
 */
double ScalarSingletDM_Z3_soft_parameters::calc_beta_muS_1_loop(const Soft_traces& soft_traces) const
{


   double beta_muS;

   beta_muS = Re(oneOver16PiSqr*(4*LamSH*muH + 8*LamS*muS + 9*Sqr(mu3)));


   return beta_muS;
}

/**
 * Calculates the 2-loop beta function of muS.
 *
 * @return 2-loop beta function
 */
double ScalarSingletDM_Z3_soft_parameters::calc_beta_muS_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_muS;

   beta_muS = Re(twoLoop*(4.8*LamSH*muH*Sqr(g1) - 2*LamSH*(LamSH*(4*muH +
      muS) + 4*muH*(3*traceYdAdjYd + traceYeAdjYe + 3*traceYuAdjYu) - 12*muH*
      Sqr(g2)) - 40*muS*Sqr(LamS) - 108*LamS*Sqr(mu3)));


   return beta_muS;
}

/**
 * Calculates the 3-loop beta function of muS.
 *
 * @return 3-loop beta function
 */
double ScalarSingletDM_Z3_soft_parameters::calc_beta_muS_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_muS;

   beta_muS = 0;


   return beta_muS;
}

} // namespace flexiblesusy
