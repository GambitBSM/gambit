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
 * Calculates the 1-loop beta function of mu2.
 *
 * @return 1-loop beta function
 */
double HSSUSY_soft_parameters::calc_beta_mu2_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;


   double beta_mu2;

   beta_mu2 = Re(oneOver16PiSqr*(2*mu2*(3*traceYdAdjYd + traceYeAdjYe + 3
      *(traceYuAdjYu + Lambdax)) - 0.9*mu2*Sqr(g1) - 4.5*mu2*Sqr(g2)));


   return beta_mu2;
}

/**
 * Calculates the 2-loop beta function of mu2.
 *
 * @return 2-loop beta function
 */
double HSSUSY_soft_parameters::calc_beta_mu2_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;


   double beta_mu2;

   beta_mu2 = Re(0.0025*mu2*twoLoop*(1671*Quad(g1) + 10*Sqr(g1)*(50*
      traceYdAdjYd + 150*traceYeAdjYe + 170*traceYuAdjYu + 288*Lambdax + 45*Sqr
      (g2)) - 25*(145*Quad(g2) - 12*(15*traceYdAdjYd + 5*traceYeAdjYe + 15*
      traceYuAdjYu + 48*Lambdax)*Sqr(g2) - 640*(traceYdAdjYd + traceYuAdjYu)*
      Sqr(g3) + 24*(9*traceYdAdjYdYdAdjYd + 14*traceYdAdjYuYuAdjYd + 3*
      traceYeAdjYeYeAdjYe + 9*traceYuAdjYuYuAdjYu + 24*traceYdAdjYd*Lambdax + 8
      *traceYeAdjYe*Lambdax + 24*traceYuAdjYu*Lambdax + 10*Sqr(Lambdax)))));


   return beta_mu2;
}

/**
 * Calculates the 3-loop beta function of mu2.
 *
 * @return 3-loop beta function
 */
double HSSUSY_soft_parameters::calc_beta_mu2_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_mu2;

   beta_mu2 = Re(2*mu2*threeLoop*(128.25*Cube(Lambdax) +
      8.378314604562993*Power6(g1) + 301.7235994495886*Power6(g2) +
      154.40506064218175*Power6(Yd(2,2)) + 3.4683535473939138*Power6(Ye(2,2)) +
      154.40506064218175*Power6(Yu(2,2)) + 173.69714554123618*Lambdax*Quad(Yd(
      2,2)) + 75.89904851374538*Lambdax*Quad(Ye(2,2)) + 173.69714554123618*
      Lambdax*Quad(Yu(2,2)) - 209.24048513745396*Quad(Yd(2,2))*Sqr(g3) -
      209.24048513745396*Quad(Yu(2,2))*Sqr(g3) + 178.48396765750311*Quad(g3)*
      Sqr(Yd(2,2)) + 72.*Quad(Ye(2,2))*Sqr(Yd(2,2)) + 296.2115485137454*Quad(Yu
      (2,2))*Sqr(Yd(2,2)) + 40.19238810996319*Lambdax*Sqr(g3)*Sqr(Yd(2,2)) +
      37.125*Sqr(Lambdax)*Sqr(Yd(2,2)) + 72.*Quad(Yd(2,2))*Sqr(Ye(2,2)) + 72.*
      Quad(Yu(2,2))*Sqr(Ye(2,2)) + 12.375*Sqr(Lambdax)*Sqr(Ye(2,2)) - 54.*
      Lambdax*Sqr(Yd(2,2))*Sqr(Ye(2,2)) + Quad(g2)*(-32.25723415592714*Lambdax
      - 28.572145541236182*Sqr(g3) - 102.62651936694535*Sqr(Yd(2,2)) -
      34.208839788981784*Sqr(Ye(2,2)) - 102.62651936694535*Sqr(Yu(2,2))) + Quad
      (g1)*(-32.90278936623708*Lambdax + 9.778005607297105*Sqr(g2) -
      4.190581346047974*Sqr(g3) - 11.837888914984243*Sqr(Yd(2,2)) -
      20.542464319265452*Sqr(Ye(2,2)) - 27.721423523790055*Sqr(Yu(2,2))) +
      178.48396765750311*Quad(g3)*Sqr(Yu(2,2)) + 296.2115485137454*Quad(Yd(2,2)
      )*Sqr(Yu(2,2)) + 72.*Quad(Ye(2,2))*Sqr(Yu(2,2)) + 40.19238810996319*
      Lambdax*Sqr(g3)*Sqr(Yu(2,2)) + 37.125*Sqr(Lambdax)*Sqr(Yu(2,2)) -
      208.57214554123618*Lambdax*Sqr(Yd(2,2))*Sqr(Yu(2,2)) - 16.698731351660527
      *Sqr(g3)*Sqr(Yd(2,2))*Sqr(Yu(2,2)) - 54.*Lambdax*Sqr(Ye(2,2))*Sqr(Yu(2,2)
      ) + 10.5*Sqr(Yd(2,2))*Sqr(Ye(2,2))*Sqr(Yu(2,2)) + Sqr(g2)*(
      -3.829281688145728*Quad(Yd(2,2)) + 3.223572770618091*Quad(Ye(2,2)) -
      3.829281688145728*Quad(Yu(2,2)) - 48.205536385309045*Sqr(Lambdax) -
      53.09857277061809*Lambdax*Sqr(Ye(2,2)) + Sqr(Yd(2,2))*(
      -159.29571831185424*Lambdax - 13.500000000000004*Sqr(Ye(2,2)) -
      62.83053638530905*Sqr(Yu(2,2))) - 159.29571831185424*Lambdax*Sqr(Yu(2,2))
      - 13.500000000000004*Sqr(Ye(2,2))*Sqr(Yu(2,2)) + Sqr(g3)*(
      7.572145541236182*Sqr(Yd(2,2)) + 7.572145541236182*Sqr(Yu(2,2)))) + Sqr(
      g1)*(9.930778506201856*Quad(g2) + 11.916358216494471*Quad(Yd(2,2)) -
      15.051929108247235*Quad(Ye(2,2)) - 7.507690297250921*Quad(Yu(2,2)) -
      9.641107277061808*Sqr(Lambdax) - 32.86395336511993*Lambdax*Sqr(Yd(2,2)) -
      7.605285445876382*Lambdax*Sqr(Ye(2,2)) - 2.7*Sqr(Yd(2,2))*Sqr(Ye(2,2)) -
      29.849524256872694*Lambdax*Sqr(Yu(2,2)) - 23.946234141895758*Sqr(Yd(2,2)
      )*Sqr(Yu(2,2)) - 2.7*Sqr(Ye(2,2))*Sqr(Yu(2,2)) + Sqr(g3)*(
      -2.091983828751535*Sqr(Yd(2,2)) + 8.727254982244787*Sqr(Yu(2,2))) + Sqr(
      g2)*(-18.911535445876382*Lambdax - 8.109375*Sqr(Yd(2,2)) +
      10.602411385309043*Sqr(Ye(2,2)) + 11.470322300901756*Sqr(Yu(2,2))))));


   return beta_mu2;
}

} // namespace flexiblesusy
