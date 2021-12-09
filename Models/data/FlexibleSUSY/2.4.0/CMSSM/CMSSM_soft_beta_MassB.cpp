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

// File generated at Thu 10 Oct 2019 17:27:52

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
 * Calculates the 1-loop beta function of MassB.
 *
 * @return 1-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_MassB_1_loop(const Soft_traces& soft_traces) const
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
double CMSSM_soft_parameters::calc_beta_MassB_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;


   double beta_MassB;

   beta_MassB = Re(0.08*twoLoop*Sqr(g1)*(70*traceAdjYdTYd + 90*traceAdjYeTYe +
      130*traceAdjYuTYu - 70*MassB*traceYdAdjYd - 90*MassB*traceYeAdjYe - 130*
      MassB*traceYuAdjYu + 398*MassB*Sqr(g1) + 135*MassB*Sqr(g2) + 135*MassWB*
      Sqr(g2) + 440*MassB*Sqr(g3) + 440*MassG*Sqr(g3)));


   return beta_MassB;
}

/**
 * Calculates the 3-loop beta function of MassB.
 *
 * @return 3-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_MassB_3_loop(const Soft_traces& soft_traces) const
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

   beta_MassB = Re(-0.005333333333333333*threeLoop*Sqr(g1)*(8100*
      traceAdjYdTYdAdjYdYd - 4050*MassB*traceAdjYdYdAdjYdYd + 8100*
      traceAdjYeTYeAdjYeYe - 6300*MassB*traceAdjYdYd*traceAdjYeYe - 4050*MassB*
      traceAdjYeYeAdjYeYe + 4350*traceAdjYuTYuAdjYdYd + 12600*
      traceAdjYuTYuAdjYuYu - 4350*MassB*traceAdjYuYuAdjYdYd - 6300*MassB*
      traceAdjYuYuAdjYuYu + 5400*traceAdjYdYd*traceTYdAdjYd + 6300*traceAdjYeYe
      *traceTYdAdjYd + 4350*traceTYdAdjYuYuAdjYd + 6300*traceAdjYdYd*
      traceTYeAdjYe + 3600*traceAdjYeYe*traceTYeAdjYe + 13500*traceAdjYuYu*
      traceTYuAdjYu + 96351*MassB*Quad(g1) + 6075*MassB*Quad(g2) + 12150*MassWB
      *Quad(g2) - 12100*MassB*Quad(g3) - 24200*MassG*Quad(g3) + 490*MassB*
      traceAdjYdYd*Sqr(g1) + 2430*MassB*traceAdjYeYe*Sqr(g1) + 1690*MassB*
      traceAdjYuYu*Sqr(g1) - 245*traceTYdAdjYd*Sqr(g1) - 1215*traceTYeAdjYe*Sqr
      (g1) - 845*traceTYuAdjYu*Sqr(g1) + 2475*MassB*traceAdjYdYd*Sqr(g2) + 2475
      *MassWB*traceAdjYdYd*Sqr(g2) + 4725*MassB*traceAdjYeYe*Sqr(g2) + 4725*
      MassWB*traceAdjYeYe*Sqr(g2) + 6525*MassB*traceAdjYuYu*Sqr(g2) + 6525*
      MassWB*traceAdjYuYu*Sqr(g2) - 2475*traceTYdAdjYd*Sqr(g2) - 4725*
      traceTYeAdjYe*Sqr(g2) - 6525*traceTYuAdjYu*Sqr(g2) + 2070*MassB*Sqr(g1)*
      Sqr(g2) + 1035*MassWB*Sqr(g1)*Sqr(g2) + 6400*MassB*traceAdjYdYd*Sqr(g3) +
      6400*MassG*traceAdjYdYd*Sqr(g3) + 8800*MassB*traceAdjYuYu*Sqr(g3) + 8800*
      MassG*traceAdjYuYu*Sqr(g3) - 6400*traceTYdAdjYd*Sqr(g3) - 8800*
      traceTYuAdjYu*Sqr(g3) + 10960*MassB*Sqr(g1)*Sqr(g3) + 5480*MassG*Sqr(g1)*
      Sqr(g3) + 1800*MassB*Sqr(g2)*Sqr(g3) + 1800*MassG*Sqr(g2)*Sqr(g3) + 1800*
      MassWB*Sqr(g2)*Sqr(g3) - 2700*MassB*Sqr(traceAdjYdYd) - 1800*MassB*Sqr(
      traceAdjYeYe) - 6750*MassB*Sqr(traceAdjYuYu)));


   return beta_MassB;
}

/**
 * Calculates the 4-loop beta function of MassB.
 *
 * @return 4-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_MassB_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_MassB;

   beta_MassB = 0;


   return beta_MassB;
}

/**
 * Calculates the 5-loop beta function of MassB.
 *
 * @return 5-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_MassB_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_MassB;

   beta_MassB = 0;


   return beta_MassB;
}

} // namespace flexiblesusy
