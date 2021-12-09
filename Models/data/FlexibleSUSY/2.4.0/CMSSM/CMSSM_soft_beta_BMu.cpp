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

// File generated at Thu 10 Oct 2019 17:27:34

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
 * Calculates the 1-loop beta function of BMu.
 *
 * @return 1-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_BMu_1_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;


   double beta_BMu;

   beta_BMu = Re(0.2*oneOver16PiSqr*(15*traceYdAdjYd*BMu + 5*traceYeAdjYe*BMu +
      15*traceYuAdjYu*BMu + 30*traceAdjYdTYd*Mu + 10*traceAdjYeTYe*Mu + 30*
      traceAdjYuTYu*Mu - 3*BMu*Sqr(g1) + 6*MassB*Mu*Sqr(g1) - 15*BMu*Sqr(g2) +
      30*MassWB*Mu*Sqr(g2)));


   return beta_BMu;
}

/**
 * Calculates the 2-loop beta function of BMu.
 *
 * @return 2-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_BMu_2_loop(const Soft_traces& soft_traces) const
{
   const double traceYdAdjYd = TRACE_STRUCT.traceYdAdjYd;
   const double traceYeAdjYe = TRACE_STRUCT.traceYeAdjYe;
   const double traceYuAdjYu = TRACE_STRUCT.traceYuAdjYu;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceYdAdjYdYdAdjYd = TRACE_STRUCT.traceYdAdjYdYdAdjYd;
   const double traceYdAdjYdTYdAdjYd = TRACE_STRUCT.traceYdAdjYdTYdAdjYd;
   const double traceYdAdjYuYuAdjYd = TRACE_STRUCT.traceYdAdjYuYuAdjYd;
   const double traceYdAdjYuTYuAdjYd = TRACE_STRUCT.traceYdAdjYuTYuAdjYd;
   const double traceYeAdjYeYeAdjYe = TRACE_STRUCT.traceYeAdjYeYeAdjYe;
   const double traceYeAdjYeTYeAdjYe = TRACE_STRUCT.traceYeAdjYeTYeAdjYe;
   const double traceYuAdjYdTYdAdjYu = TRACE_STRUCT.traceYuAdjYdTYdAdjYu;
   const double traceYuAdjYuYuAdjYu = TRACE_STRUCT.traceYuAdjYuYuAdjYu;
   const double traceYuAdjYuTYuAdjYu = TRACE_STRUCT.traceYuAdjYuTYuAdjYu;


   double beta_BMu;

   beta_BMu = Re(0.02*twoLoop*(-450*traceYdAdjYdYdAdjYd*BMu - 300*
      traceYdAdjYuYuAdjYd*BMu - 150*traceYeAdjYeYeAdjYe*BMu - 450*
      traceYuAdjYuYuAdjYu*BMu - 1800*traceYdAdjYdTYdAdjYd*Mu - 600*
      traceYdAdjYuTYuAdjYd*Mu - 600*traceYeAdjYeTYeAdjYe*Mu - 600*
      traceYuAdjYdTYdAdjYu*Mu - 1800*traceYuAdjYuTYuAdjYu*Mu + 207*BMu*Quad(g1)
      - 828*MassB*Mu*Quad(g1) + 375*BMu*Quad(g2) - 1500*MassWB*Mu*Quad(g2) - 20
      *traceYdAdjYd*BMu*Sqr(g1) + 60*traceYeAdjYe*BMu*Sqr(g1) + 40*traceYuAdjYu
      *BMu*Sqr(g1) - 40*traceAdjYdTYd*Mu*Sqr(g1) + 120*traceAdjYeTYe*Mu*Sqr(g1)
      + 80*traceAdjYuTYu*Mu*Sqr(g1) + 40*MassB*traceYdAdjYd*Mu*Sqr(g1) - 120*
      MassB*traceYeAdjYe*Mu*Sqr(g1) - 80*MassB*traceYuAdjYu*Mu*Sqr(g1) + 90*BMu
      *Sqr(g1)*Sqr(g2) - 180*MassB*Mu*Sqr(g1)*Sqr(g2) - 180*MassWB*Mu*Sqr(g1)*
      Sqr(g2) + 800*traceYdAdjYd*BMu*Sqr(g3) + 800*traceYuAdjYu*BMu*Sqr(g3) +
      1600*traceAdjYdTYd*Mu*Sqr(g3) + 1600*traceAdjYuTYu*Mu*Sqr(g3) - 1600*
      MassG*traceYdAdjYd*Mu*Sqr(g3) - 1600*MassG*traceYuAdjYu*Mu*Sqr(g3)));


   return beta_BMu;
}

/**
 * Calculates the 3-loop beta function of BMu.
 *
 * @return 3-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_BMu_3_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)

   const double traceAdjYdYd = TRACE_STRUCT.traceAdjYdYd;
   const double traceAdjYdTYd = TRACE_STRUCT.traceAdjYdTYd;
   const double traceAdjYeYe = TRACE_STRUCT.traceAdjYeYe;
   const double traceAdjYeTYe = TRACE_STRUCT.traceAdjYeTYe;
   const double traceAdjYuYu = TRACE_STRUCT.traceAdjYuYu;
   const double traceAdjYuTYu = TRACE_STRUCT.traceAdjYuTYu;
   const double traceAdjYdYdAdjYdYd = TRACE_STRUCT.traceAdjYdYdAdjYdYd;
   const double traceAdjYdYdAdjYdTYd = TRACE_STRUCT.traceAdjYdYdAdjYdTYd;
   const double traceAdjYdTYdAdjYdYd = TRACE_STRUCT.traceAdjYdTYdAdjYdYd;
   const double traceAdjYeYeAdjYeYe = TRACE_STRUCT.traceAdjYeYeAdjYeYe;
   const double traceAdjYeYeAdjYeTYe = TRACE_STRUCT.traceAdjYeYeAdjYeTYe;
   const double traceAdjYeTYeAdjYeYe = TRACE_STRUCT.traceAdjYeTYeAdjYeYe;
   const double traceAdjYuYuAdjYdYd = TRACE_STRUCT.traceAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYdTYd = TRACE_STRUCT.traceAdjYuYuAdjYdTYd;
   const double traceAdjYuYuAdjYuYu = TRACE_STRUCT.traceAdjYuYuAdjYuYu;
   const double traceAdjYuYuAdjYuTYu = TRACE_STRUCT.traceAdjYuYuAdjYuTYu;
   const double traceAdjYuTYuAdjYdYd = TRACE_STRUCT.traceAdjYuTYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYu = TRACE_STRUCT.traceAdjYuTYuAdjYuYu;
   const double traceAdjYdYdAdjYdYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdYdAdjYdYd;
   const double traceAdjYdYdAdjYdYdAdjYdTYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdYdAdjYdTYd;
   const double traceAdjYdYdAdjYdTYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYdTYdAdjYdYd;
   const double traceAdjYdYdAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYuYuAdjYdYd;
   const double traceAdjYdYdAdjYuYuAdjYdTYd = TRACE_STRUCT.
      traceAdjYdYdAdjYuYuAdjYdTYd;
   const double traceAdjYdYdAdjYuTYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdYdAdjYuTYuAdjYdYd;
   const double traceAdjYdTYdAdjYdYdAdjYdYd = TRACE_STRUCT.
      traceAdjYdTYdAdjYdYdAdjYdYd;
   const double traceAdjYdTYdAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYdTYdAdjYuYuAdjYdYd;
   const double traceAdjYeYeAdjYeYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeYeAdjYeYe;
   const double traceAdjYeYeAdjYeYeAdjYeTYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeYeAdjYeTYe;
   const double traceAdjYeYeAdjYeTYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeYeAdjYeTYeAdjYeYe;
   const double traceAdjYeTYeAdjYeYeAdjYeYe = TRACE_STRUCT.
      traceAdjYeTYeAdjYeYeAdjYeYe;
   const double traceAdjYuYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYdYd;
   const double traceAdjYuYuAdjYuYuAdjYdTYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYdTYd;
   const double traceAdjYuYuAdjYuYuAdjYuYu = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYuYu;
   const double traceAdjYuYuAdjYuYuAdjYuTYu = TRACE_STRUCT.
      traceAdjYuYuAdjYuYuAdjYuTYu;
   const double traceAdjYuYuAdjYuTYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuYuAdjYuTYuAdjYdYd;
   const double traceAdjYuYuAdjYuTYuAdjYuYu = TRACE_STRUCT.
      traceAdjYuYuAdjYuTYuAdjYuYu;
   const double traceAdjYuTYuAdjYuYuAdjYdYd = TRACE_STRUCT.
      traceAdjYuTYuAdjYuYuAdjYdYd;
   const double traceAdjYuTYuAdjYuYuAdjYuYu = TRACE_STRUCT.
      traceAdjYuTYuAdjYuYuAdjYuYu;


   double beta_BMu;

   const double beta_BMu_1 = Re(-117.341572149176*threeLoop*(-
      0.4199197915219974*traceAdjYdTYdAdjYdYdAdjYdYd*Mu - 0.15339831971159082*
      traceAdjYdTYdAdjYuYuAdjYdYd*Mu - 0.9203899182695449*traceAdjYdTYdAdjYdYd*
      traceAdjYdYd*Mu - 0.9203899182695449*traceAdjYdYd*traceAdjYdYdAdjYdTYd*Mu
       - 0.4199197915219974*traceAdjYdYdAdjYdTYdAdjYdYd*Mu - 0.9203899182695449
      *traceAdjYdTYd*traceAdjYdYdAdjYdYd*Mu - 0.4199197915219974*
      traceAdjYdYdAdjYdYdAdjYdTYd*Mu - 0.15339831971159082*
      traceAdjYdYdAdjYuTYuAdjYdYd*Mu - 0.15339831971159082*
      traceAdjYdYdAdjYuYuAdjYdTYd*Mu - 0.30679663942318164*traceAdjYdYdAdjYdYd*
      traceAdjYeTYe*Mu - 0.30679663942318164*traceAdjYdYd*traceAdjYeTYeAdjYeYe*
      Mu - 0.13997326384066577*traceAdjYeTYeAdjYeYeAdjYeYe*Mu -
      0.30679663942318164*traceAdjYdTYdAdjYdYd*traceAdjYeYe*Mu -
      0.30679663942318164*traceAdjYdYdAdjYdTYd*traceAdjYeYe*Mu -
      0.10226554647439387*traceAdjYeTYeAdjYeYe*traceAdjYeYe*Mu -
      0.30679663942318164*traceAdjYdYd*traceAdjYeYeAdjYeTYe*Mu -
      0.10226554647439387*traceAdjYeYe*traceAdjYeYeAdjYeTYe*Mu -
      0.13997326384066577*traceAdjYeYeAdjYeTYeAdjYeYe*Mu - 0.30679663942318164*
      traceAdjYdTYd*traceAdjYeYeAdjYeYe*Mu - 0.10226554647439387*traceAdjYeTYe*
      traceAdjYeYeAdjYeYe*Mu - 0.13997326384066577*traceAdjYeYeAdjYeYeAdjYeTYe*
      Mu - 0.30679663942318164*traceAdjYdYd*traceAdjYuTYuAdjYdYd*Mu -
      0.10226554647439387*traceAdjYeYe*traceAdjYuTYuAdjYdYd*Mu -
      0.15339831971159082*traceAdjYuTYuAdjYuYuAdjYdYd*Mu - 0.4199197915219974*
      traceAdjYuTYuAdjYuYuAdjYuYu*Mu - 0.30679663942318164*traceAdjYuTYuAdjYdYd
      *traceAdjYuYu*Mu - 0.9203899182695449*traceAdjYuTYuAdjYuYu*traceAdjYuYu*
      Mu - 0.30679663942318164*traceAdjYdYd*traceAdjYuYuAdjYdTYd*Mu -
      0.10226554647439387*traceAdjYeYe*traceAdjYuYuAdjYdTYd*Mu + 1.*MassB*Mu*
      Power6(g1) + 28.181721843368493*MassWB*Mu*Power6(g2) +
      0.31590681162233364*traceAdjYdTYd*Mu*Quad(g1) - 0.6318136232446673*MassB*
      traceAdjYdYd*Mu*Quad(g1) + 0.5267130353016745*traceAdjYeTYe*Mu*Quad(g1) -
      1.053426070603349*MassB*traceAdjYeYe*Mu*Quad(g1) + 0.6961898764320866*
      traceAdjYuTYu*Mu*Quad(g1) - 1.3923797528641733*MassB*traceAdjYuYu*Mu*Quad
      (g1) + 3.2783671434716215*traceAdjYdTYd*Mu*Quad(g2) - 6.556734286943243*
      MassWB*traceAdjYdYd*Mu*Quad(g2) + 1.0927890478238738*traceAdjYeTYe*Mu*
      Quad(g2) - 2.1855780956477475*MassWB*traceAdjYeYe*Mu*Quad(g2) +
      3.2783671434716215*traceAdjYuTYu*Mu*Quad(g2) - 6.556734286943243*MassWB*
      traceAdjYuYu*Mu*Quad(g2) + 1.2368377626922127*traceAdjYdTYd*Mu*Quad(g3) -
      2.4736755253844254*MassG*traceAdjYdYd*Mu*Quad(g3) + 1.2368377626922127*
      traceAdjYuTYu*Mu*Quad(g3) - 2.4736755253844254*MassG*traceAdjYuYu*Mu*Quad
      (g3) - 0.27240498420807713*traceAdjYdTYdAdjYdYd*Mu*Sqr(g1) -
      0.27240498420807713*traceAdjYdYdAdjYdTYd*Mu*Sqr(g1) + 0.27240498420807713
      *MassB*traceAdjYdYdAdjYdYd*Mu*Sqr(g1) + 0.06787389125928944*
      traceAdjYeTYeAdjYeYe*Mu*Sqr(g1) + 0.06787389125928944*
      traceAdjYeYeAdjYeTYe*Mu*Sqr(g1) - 0.06787389125928944*MassB*
      traceAdjYeYeAdjYeYe*Mu*Sqr(g1) - 0.1762333004570148*traceAdjYuTYuAdjYdYd*
      Mu*Sqr(g1) - 0.12054713464438828*traceAdjYuTYuAdjYuYu*Mu*Sqr(g1) -
      0.1762333004570148*traceAdjYuYuAdjYdTYd*Mu*Sqr(g1) - 0.25520915660052496*
      MassB*Mu*Quad(g2)*Sqr(g1) - 0.5104183132010499*MassWB*Mu*Quad(g2)*Sqr(g1)
      - 1.2597593745659919*traceAdjYdTYdAdjYdYd*Mu*Sqr(g2) - 1.2597593745659919
      *traceAdjYdYdAdjYdTYd*Mu*Sqr(g2) + 1.2597593745659919*MassWB*
      traceAdjYdYdAdjYdYd*Mu*Sqr(g2) - 0.4199197915219974*traceAdjYeTYeAdjYeYe*
      Mu*Sqr(g2) - 0.4199197915219974*traceAdjYeYeAdjYeTYe*Mu*Sqr(g2) +
      0.4199197915219974*MassWB*traceAdjYeYeAdjYeYe*Mu*Sqr(g2) -
      0.6135932788463633*traceAdjYuTYuAdjYdYd*Mu*Sqr(g2) - 1.2597593745659919*
      traceAdjYuTYuAdjYuYu*Mu*Sqr(g2) - 0.6135932788463633*traceAdjYuYuAdjYdTYd
      *Mu*Sqr(g2) - 0.3798821813821935*MassB*Mu*Quad(g1)*Sqr(g2) -
      0.18994109069109674*MassWB*Mu*Quad(g1)*Sqr(g2) + 0.18950678646611985*
      traceAdjYdTYd*Mu*Sqr(g1)*Sqr(g2) - 0.18950678646611985*MassB*traceAdjYdYd
      *Mu*Sqr(g1)*Sqr(g2) - 0.18950678646611985*MassWB*traceAdjYdYd*Mu*Sqr(g1)*
      Sqr(g2) - 0.19384982871588863*traceAdjYeTYe*Mu*Sqr(g1)*Sqr(g2) +
      0.19384982871588863*MassB*traceAdjYeYe*Mu*Sqr(g1)*Sqr(g2) +
      0.19384982871588863*MassWB*traceAdjYeYe*Mu*Sqr(g1)*Sqr(g2) -
      0.16099864364868605*traceAdjYuTYu*Mu*Sqr(g1)*Sqr(g2) +
      0.16099864364868605*MassB*traceAdjYuYu*Mu*Sqr(g1)*Sqr(g2) +
      0.16099864364868605*MassWB*traceAdjYuYu*Mu*Sqr(g1)*Sqr(g2) +
      1.7231095885856764*traceAdjYdTYdAdjYdYd*Mu*Sqr(g3) + 1.7231095885856764*
      traceAdjYdYdAdjYdTYd*Mu*Sqr(g3) - 1.7231095885856764*MassG*
      traceAdjYdYdAdjYdYd*Mu*Sqr(g3) + 1.1487397257237846*traceAdjYuTYuAdjYdYd*
      Mu*Sqr(g3) + 1.7231095885856764*traceAdjYuTYuAdjYuYu*Mu*Sqr(g3) +
      1.1487397257237846*traceAdjYuYuAdjYdTYd*Mu*Sqr(g3) - 0.3981934953878312*
      MassB*Mu*Quad(g1)*Sqr(g3) - 0.1990967476939156*MassG*Mu*Quad(g1)*Sqr(g3)
      - 1.3574778251857884*MassG*Mu*Quad(g2)*Sqr(g3) - 2.714955650371577*MassWB
      *Mu*Quad(g2)*Sqr(g3) - 0.13623034276855311*traceAdjYdTYd*Mu*Sqr(g1)*Sqr(
      g3) + 0.13623034276855311*MassB*traceAdjYdYd*Mu*Sqr(g1)*Sqr(g3) +
      0.13623034276855311*MassG*traceAdjYdYd*Mu*Sqr(g1)*Sqr(g3) -
      0.14781178876793646*traceAdjYuTYu*Mu*Sqr(g1)*Sqr(g3) +
      0.14781178876793646*MassB*traceAdjYuYu*Mu*Sqr(g1)*Sqr(g3) +
      0.14781178876793646*MassG*traceAdjYuYu*Mu*Sqr(g1)*Sqr(g3) -
      0.7004541238417379*traceAdjYdTYd*Mu*Sqr(g2)*Sqr(g3) + 0.7004541238417379*
      MassG*traceAdjYdYd*Mu*Sqr(g2)*Sqr(g3) + 0.7004541238417379*MassWB*
      traceAdjYdYd*Mu*Sqr(g2)*Sqr(g3) - 0.7004541238417379*traceAdjYuTYu*Mu*Sqr
      (g2)*Sqr(g3) + 0.7004541238417379*MassG*traceAdjYuYu*Mu*Sqr(g2)*Sqr(g3) +
      0.7004541238417379*MassWB*traceAdjYuYu*Mu*Sqr(g2)*Sqr(g3)));
   const double beta_BMu_2 = Re(36.*threeLoop*(1.5*traceAdjYdYd*
      traceAdjYdYdAdjYdYd*BMu + 0.6843617849131305*traceAdjYdYdAdjYdYdAdjYdYd*
      BMu + 0.25*traceAdjYdYdAdjYuYuAdjYdYd*BMu + 0.5*traceAdjYdYdAdjYdYd*
      traceAdjYeYe*BMu + 0.5*traceAdjYdYd*traceAdjYeYeAdjYeYe*BMu +
      0.16666666666666666*traceAdjYeYe*traceAdjYeYeAdjYeYe*BMu +
      0.2281205949710435*traceAdjYeYeAdjYeYeAdjYeYe*BMu + 0.5*traceAdjYdYd*
      traceAdjYuYuAdjYdYd*BMu + 0.16666666666666666*traceAdjYeYe*
      traceAdjYuYuAdjYdYd*BMu + 0.5*traceAdjYuYu*traceAdjYuYuAdjYdYd*BMu + 1.5*
      traceAdjYuYu*traceAdjYuYuAdjYuYu*BMu + 0.25*traceAdjYuYuAdjYuYuAdjYdYd*
      BMu + 0.6843617849131305*traceAdjYuYuAdjYuYuAdjYuYu*BMu + 1.*traceAdjYuYu
      *traceAdjYuYuAdjYdTYd*Mu + 1.*traceAdjYdTYd*traceAdjYuYuAdjYdYd*Mu +
      0.3333333333333333*traceAdjYeTYe*traceAdjYuYuAdjYdYd*Mu + 1.*
      traceAdjYuTYu*traceAdjYuYuAdjYdYd*Mu + 3.*traceAdjYuYu*
      traceAdjYuYuAdjYuTYu*Mu + 0.5*traceAdjYuYuAdjYuTYuAdjYdYd*Mu +
      1.368723569826261*traceAdjYuYuAdjYuTYuAdjYuYu*Mu + 3.*traceAdjYuTYu*
      traceAdjYuYuAdjYuYu*Mu + 0.5*traceAdjYuYuAdjYuYuAdjYdTYd*Mu +
      1.368723569826261*traceAdjYuYuAdjYuYuAdjYuTYu*Mu + 0.5432480192091482*BMu
      *Power6(g1) + 15.309664569313119*BMu*Power6(g2) - 0.5148472490055308*
      traceAdjYdYd*BMu*Quad(g1) - 0.8584074393578184*traceAdjYeYe*BMu*Quad(g1)
      - 1.134611314095578*traceAdjYuYu*BMu*Quad(g1) - 5.342899370793934*
      traceAdjYdYd*BMu*Quad(g2) - 1.7809664569313115*traceAdjYeYe*BMu*Quad(g2)
      - 5.342899370793934*traceAdjYuYu*BMu*Quad(g2) - 2.015728993996857*
      traceAdjYdYd*BMu*Quad(g3) - 2.015728993996857*traceAdjYuYu*BMu*Quad(g3) +
      0.4439504042812115*traceAdjYdYdAdjYdYd*BMu*Sqr(g1) - 0.11061707094787832*
      traceAdjYeYeAdjYeYe*BMu*Sqr(g1) + 0.2872151741758919*traceAdjYuYuAdjYdYd*
      BMu*Sqr(g1) + 0.19646097635070725*traceAdjYuYuAdjYuYu*BMu*Sqr(g1) -
      0.5744303483517837*MassB*traceAdjYuYuAdjYdYd*Mu*Sqr(g1) +
      0.3929219527014145*traceAdjYuYuAdjYuTYu*Mu*Sqr(g1) - 0.3929219527014145*
      MassB*traceAdjYuYuAdjYuYu*Mu*Sqr(g1) - 0.4159256064218175*BMu*Quad(g2)*
      Sqr(g1) + 2.0530853547393915*traceAdjYdYdAdjYdYd*BMu*Sqr(g2) +
      0.6843617849131305*traceAdjYeYeAdjYeYe*BMu*Sqr(g2) + 1.*
      traceAdjYuYuAdjYdYd*BMu*Sqr(g2) + 2.0530853547393915*traceAdjYuYuAdjYuYu*
      BMu*Sqr(g2) - 2.*MassWB*traceAdjYuYuAdjYdYd*Mu*Sqr(g2) +
      4.106170709478783*traceAdjYuYuAdjYuTYu*Mu*Sqr(g2) - 4.106170709478783*
      MassWB*traceAdjYuYuAdjYuYu*Mu*Sqr(g2) - 0.30955536385309046*BMu*Quad(g1)*
      Sqr(g2) - 0.30884755912323186*traceAdjYdYd*BMu*Sqr(g1)*Sqr(g2) +
      0.31592560642181744*traceAdjYeYe*BMu*Sqr(g1)*Sqr(g2) + 0.2623865827725246
      *traceAdjYuYu*BMu*Sqr(g1)*Sqr(g2) - 2.808227612638377*traceAdjYdYdAdjYdYd
      *BMu*Sqr(g3) - 1.8721517417589182*traceAdjYuYuAdjYdYd*BMu*Sqr(g3) -
      2.808227612638377*traceAdjYuYuAdjYuYu*BMu*Sqr(g3) + 3.7443034835178364*
      MassG*traceAdjYuYuAdjYdYd*Mu*Sqr(g3) - 5.616455225276754*
      traceAdjYuYuAdjYuTYu*Mu*Sqr(g3) + 5.616455225276754*MassG*
      traceAdjYuYuAdjYuYu*Mu*Sqr(g3) - 0.3244767414471096*BMu*Quad(g1)*Sqr(g3)
      - 2.212341418957566*BMu*Quad(g2)*Sqr(g3) + 0.22202059159559934*
      traceAdjYdYd*BMu*Sqr(g1)*Sqr(g3) + 0.24089538439182748*traceAdjYuYu*BMu*
      Sqr(g1)*Sqr(g3) + 1.1415609459717104*traceAdjYdYd*BMu*Sqr(g2)*Sqr(g3) +
      1.1415609459717104*traceAdjYuYu*BMu*Sqr(g2)*Sqr(g3)));

   beta_BMu = beta_BMu_1 + beta_BMu_2;


   return beta_BMu;
}

/**
 * Calculates the 4-loop beta function of BMu.
 *
 * @return 4-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_BMu_4_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_BMu;

   beta_BMu = 0;


   return beta_BMu;
}

/**
 * Calculates the 5-loop beta function of BMu.
 *
 * @return 5-loop beta function
 */
double CMSSM_soft_parameters::calc_beta_BMu_5_loop(const Soft_traces& soft_traces) const
{
   DEFINE_PROJECTOR(3,3,3,3)



   double beta_BMu;

   beta_BMu = 0;


   return beta_BMu;
}

} // namespace flexiblesusy
