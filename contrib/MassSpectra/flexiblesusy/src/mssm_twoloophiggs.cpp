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

#include "mssm_twoloophiggs.hpp"
#include "mssm_twoloophiggs.h"
#include "config.h"
#include "dilog.hpp"
#include <cmath>
#include <limits>
#include <utility>

#ifdef ENABLE_THREADS
   #include <mutex>
   #define LOCK_MUTEX() std::lock_guard<std::mutex> lg(mtx_mssm)
   namespace flexiblesusy {namespace mssm_twoloophiggs {
      static std::mutex mtx_mssm; /// locks MSSM fortran functions
   } // namespace mssm_twoloophiggs
} // namespace flexiblesusy
#else
   #define LOCK_MUTEX()
#endif

namespace flexiblesusy {
namespace mssm_twoloophiggs {

namespace {

template <typename T> T constexpr sqr(T a) { return a * a; }
template <typename T> T sqrtabs(T a) { return std::sqrt(std::abs(a)); }
template <typename T> T logabs(T x) { return std::log(std::abs(x)); }

double phi(double x, double y, double z)
{
   using std::log;
   using gm2calc::dilog;

   const double u = x/z, v = y/z;
   const double lambda = sqrtabs(sqr(1 - u - v) - 4*u*v);
   const double xp = 0.5 * (1 + (u - v) - lambda);
   const double xm = 0.5 * (1 - (u - v) - lambda);

   return 1./lambda * (2*logabs(xp)*logabs(xm) - logabs(u)*logabs(v) -
                       2*(dilog(xp) + dilog(xm)) + M_PI*M_PI/3.);
}

/// First derivative of phi[t,T,g] w.r.t. T
double dphi_010(double t, double T, double g)
{
   using std::fabs;
   using std::sqrt;
   using std::log;
   using std::pow;
   using gm2calc::dilog;

   constexpr double Pi2 = M_PI * M_PI;
   const double g2 = sqr(g);
   const double abbr = (-4*t*T)/g2 + sqr(1 - t/g - T/g);
   const double rabbr = sqrtabs(abbr);

   return ((g + t - T)*(Pi2 - 6*dilog((g - rabbr*g + t - T)/(2.*g)) -
      6*dilog((g - rabbr*g - t + T)/(2.*g)) -
      3*logabs(t/g)*logabs(T/g) + 6*logabs((g - rabbr*g + t -
      T)/(2.*g))*logabs((g - rabbr*g - t + T)/(2.*g))) + (3*rabbr*g* (
      rabbr*g*((-1 + rabbr)*g + t - T)*logabs(t/g) +
      2*T*(-2*g*logabs(4.) + (g + rabbr*g + t - T)*logabs((g - rabbr*g
      + t - T)/g) + (g + rabbr*g + t - T)*logabs((g + rabbr*g + t -
      T)/g) + g*logabs((g - rabbr*g - t + T)/g) - rabbr*g*logabs((g -
      rabbr*g - t + T)/g) - t*logabs((g - rabbr*g - t + T)/g) +
      T*logabs((g - rabbr*g - t + T)/g) + g*logabs((g + rabbr*g - t +
      T)/g) - rabbr*g*logabs((g + rabbr*g - t + T)/g) - t*logabs((g +
      rabbr*g - t + T)/g) + T*logabs((g + rabbr*g - t + T)/g)) ) ) /
      (T*(g - rabbr*g - t + T)))/(3.*pow(fabs(abbr),1.5)*g2);
}

double calc_At(double mt2, double mst12, double mst22,
   double sxt, double cxt, double mu, double tanb)
{
   const double s2t = 2*cxt*sxt;
   const double Xt = (mst12 - mst22)*s2t/2./sqrtabs(mt2);
   const double At = Xt - mu/tanb;

   return At;
}

/// limit st -> 0
Eigen::Matrix<double, 2, 1> tadpole_higgs_2loop_at_as_mssm_st_0(
   double mt2, double mg, double mst12, double mst22,
   double /* sxt */, double /* cxt */, double scale2,
   double mu, double tanb, double vev2, double gs)
{
   using std::sqrt;
   using std::atan;
   using std::log;
   using std::sin;
   using std::cos;

   constexpr double Pi4 = M_PI * M_PI * M_PI * M_PI;
   const double g = sqr(mg);
   const double q = scale2;
   const double t = mt2;
   const double T1 = mst12;
   const double T2 = mst22;
   const double v = sqrtabs(vev2);
   const double beta = std::atan(tanb);
   const double v2 = v * std::sin(beta);
   const double v1 = v * std::cos(beta);

   const double t1 = (sqr(gs)*mg*mt2*mu*(T1*T2*(5*(T1 - T2) + (-T1 +
      T2)*logabs(g/q)*logabs(t/q) + ((-g + t)*logabs(t/g) + T1*(-4 +
      logabs((g*t)/sqr(q))))*logabs(T1/q) + ((g - t)*logabs(t/g) -
      T2*(-4 + logabs((g*t)/sqr(q))))*logabs(T2/q)) + (sqr(g) + sqr(t
      - T1) - 2*g*(t + T1))*T2*phi(g,t,T1) - T1*(sqr(g) + sqr(t - T2)
      - 2*g*(t + T2))*phi(g,t,T2)))/(16.*Pi4*T1*(T1 -
      T2)*T2*tanb*sqr(v1));

   const double t2 = (sqr(gs)*mt2*(T1*T2*(-((T1 - T2)*(5*mg*mu + (2*g
      + 5*(-2*t + T1 + T2))*tanb)) + 6*t*(T1 -
      T2)*tanb*sqr(logabs(t/q)) + (4*mg*mu*T1 + 2*(g + t + 2*T1)*(T1 -
      T2)*tanb + g*(-T1 + T2)*tanb*logabs(g/q) + mg*mu*((g -
      t)*logabs(t/g) - T1*logabs((g*t)/sqr(q))))*logabs(T1/q) +
      T1*(-T1 + T2)*tanb*sqr(logabs(T1/q)) + logabs(T2/q)*(-4*mg*mu*T2
      + 2*(T1 - T2)*(g + t + 2*T2)*tanb + g*(-T1 +
      T2)*tanb*logabs(g/q) + mg*mu*((-g + t)*logabs(t/g) +
      T2*logabs((g*t)/sqr(q))) + T2*(-T1 + T2)*tanb*logabs(T2/q)) -
      (T1 - T2)*logabs(t/q)*(12*t*tanb - (mg*mu +
      2*g*tanb)*logabs(g/q) + (g + 2*t)*tanb*(logabs(T1/q) +
      logabs(T2/q)))) - T2*(mg*mu*(sqr(g) + sqr(t - T1) - 2*g*(t +
      T1)) - g*(g + t - T1)*(T1 - T2)*tanb)*phi(g,t,T1) +
      T1*(mg*mu*(sqr(g) + sqr(t - T2) - 2*g*(t + T2)) + g*(g + t -
      T2)*(T1 - T2)*tanb)*phi(g,t,T2)))/(16.*Pi4*T1*(T1 -
      T2)*T2*tanb*sqr(v2));

   Eigen::Matrix<double, 2, 1> result;
   result << t1, t2;

   return -result;
}

/// limit st -> 0 and mst1 -> mst2
Eigen::Matrix<double, 2, 1> tadpole_higgs_2loop_at_as_mssm_st_0_mst1_eq_mst2(
   double mt2, double mg, double mst12, double /* mst22 */,
   double /* sxt */, double /* cxt */, double scale2,
   double mu, double tanb, double vev2, double gs)
{
   using std::sqrt;
   using std::atan;
   using std::log;
   using std::sin;
   using std::cos;
   using gm2calc::dilog;

   constexpr double Pi2 = M_PI * M_PI;
   constexpr double Pi4 = M_PI * M_PI * M_PI * M_PI;
   const double g = sqr(mg);
   const double g2 = sqr(g);
   const double q = scale2;
   const double q2 = sqr(q);
   const double t = mt2;
   const double tsq = sqr(t);
   const double T = mst12;
   const double Tsq = sqr(mst12);
   const double v = sqrtabs(vev2);
   const double beta = std::atan(tanb);
   const double v2 = v * std::sin(beta);
   const double v1 = v * std::cos(beta);

   const double t1 = (sqr(gs)*mg*mt2*mu*(T*((-g + t)*logabs(t/g) +
      T*(1 - logabs(g/q)*logabs(t/q) - 4*logabs(T/q) +
      logabs((g*t)/q2)*(1 + logabs(T/q)))) + T*(((g2 + g*(-2*t + T*(-2
      + sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))) + (t - T)*(t +
      T*(-1 + sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))))*
      logabs(g/T) + (g2 + g*(-2*t + T*(-2 + sqrtabs((g2 + sqr(t - T) -
      2*g*(t + T))/Tsq))) + (t - T)*(t + T*(-1 + sqrtabs((g2 + sqr(t -
      T) - 2*g*(t + T))/Tsq))))* logabs(t/T) - 2*(g*(g - t - T +
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))* logabs((g - t +
      T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/(2.*T)) +
      t*(-g + t - T + T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))*
      logabs((-g + t + T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T)) + g2*logabs((g - t + T + T*sqrtabs((g2 + sqr(t
      - T) - 2*g*(t + T))/Tsq))/(2.*T)) - g*t*logabs((g - t + T +
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/ (2.*T)) -
      g*T*logabs((g - t + T + T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T)) + g*T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq)* logabs((g - t + T + T*sqrtabs((g2 + sqr(t - T) -
      2*g*(t + T))/Tsq))/(2.*T)) - g*t*logabs((-g + t + T +
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/ (2.*T)) +
      tsq*logabs((-g + t + T + T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T)) - t*T*logabs((-g + t + T + T*sqrtabs((g2 +
      sqr(t - T) - 2*g*(t + T))/Tsq))/ (2.*T)) + t*T*sqrtabs((g2 +
      sqr(t - T) - 2*g*(t + T))/Tsq)* logabs((-g + t + T +
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/(2.*T)) ))/(g +
      t - T + T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq)) + ((g2 -
      2*g*t + tsq - 3*g*T - 3*t*T + 2*Tsq)* (Pi2 -
      3*logabs(g/T)*logabs(t/T) + 6*logabs((g - t + T - T*sqrtabs((g2
      + sqr(t - T) - 2*g*(t + T))/Tsq))/(2.*T))* logabs((-g + t + T -
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/(2.*T)) -
      6*dilog((g - t + T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T)) - 6*dilog((-g + t + T - T*sqrtabs((g2 + sqr(t
      - T) - 2*g*(t + T))/Tsq))/ (2.*T))))/(3.*T*sqrtabs((g2 + sqr(t -
      T) - 2*g*(t + T))/Tsq))) - (Tsq*sqrtabs((g2 + sqr(t - T) -
      2*g*(t + T))/Tsq)* (Pi2 - 3*logabs(g/T)*logabs(t/T) +
      6*logabs((g - t + T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T))* logabs((-g + t + T - T*sqrtabs((g2 + sqr(t -
      T) - 2*g*(t + T))/Tsq))/(2.*T)) - 6*dilog((g - t + T -
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/ (2.*T)) -
      6*dilog((-g + t + T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T))))/3.))/ (16.*Pi4*Tsq*tanb*sqr(v1));

   const double t2 = (sqr(gs)*mt2*(T*(-(mg*mu*T) - 2*g*T*tanb +
      10*t*T*tanb - 10*Tsq*tanb + g*mg*mu*logabs(t/g) -
      mg*mu*t*logabs(t/g) - mg*mu*T*logabs((g*t)/q2) -
      12*t*T*tanb*logabs(t/q) + mg*mu*T*logabs(g/q)*logabs(t/q) +
      2*g*T*tanb*logabs(g/q)*logabs(t/q) + 6*t*T*tanb*sqr(logabs(t/q))
      + 4*mg*mu*T*logabs(T/q) + 4*g*T*tanb*logabs(T/q) +
      4*t*T*tanb*logabs(T/q) + 8*Tsq*tanb*logabs(T/q) -
      2*g*T*tanb*logabs(g/q)*logabs(T/q) -
      mg*mu*T*logabs((g*t)/q2)*logabs(T/q) -
      2*g*T*tanb*logabs(t/q)*logabs(T/q) -
      4*t*T*tanb*logabs(t/q)*logabs(T/q) - 2*Tsq*tanb*sqr(logabs(T/q))
      + (g*(g + t - T)*tanb*(Pi2 - 3*logabs(g/T)*logabs(t/T) +
      6*logabs((g - t + T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T))* logabs((-g + t + T - T*sqrtabs((g2 + sqr(t -
      T) - 2*g*(t + T))/Tsq))/(2.*T)) - 6*dilog((g - t + T -
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/(2.*T)) -
      6*dilog((-g + t + T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/ (2.*T))))/(3.*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))) + T*(-((mg*mu*((g2 + g*(-2*t + T*(-2 + sqrtabs((g2 +
      sqr(t - T) - 2*g*(t + T))/Tsq))) + (t - T)*(t + T*(-1 +
      sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))))* logabs(g/T) +
      (g2 + g*(-2*t + T*(-2 + sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))) + (t - T)*(t + T*(-1 + sqrtabs((g2 + sqr(t - T) -
      2*g*(t + T))/Tsq))))* logabs(t/T) - 2*(g*(g - t - T +
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))* logabs((g - t +
      T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/ (2.*T)) +
      t*(-g + t - T + T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))*
      logabs((-g + t + T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/ (2.*T)) + g2* logabs((g - t + T + T*sqrtabs((g2 +
      sqr(t - T) - 2*g*(t + T))/Tsq))/ (2.*T)) - g*t*logabs((g - t + T
      + T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/(2.*T)) -
      g*T*logabs((g - t + T + T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/ (2.*T)) + g*T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq)* logabs((g - t + T + T*sqrtabs((g2 + sqr(t - T) -
      2*g*(t + T))/Tsq))/ (2.*T)) - g*t*logabs((-g + t + T +
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/(2.*T)) +
      tsq*logabs((-g + t + T + T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T)) - t*T*logabs((-g + t + T + T*sqrtabs((g2 +
      sqr(t - T) - 2*g*(t + T))/Tsq))/ (2.*T)) + t*T*sqrtabs((g2 +
      sqr(t - T) - 2*g*(t + T))/Tsq)* logabs((-g + t + T +
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/ (2.*T)))))/ (g
      + t - T + T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))) -
      ((mg*mu*(tsq - 3*t*T + 2*Tsq) + g2*(mg*mu - T*tanb) -
      g*(mg*mu*(2*t + 3*T) + (t - T)*T*tanb))* (Pi2 -
      3*logabs(g/T)*logabs(t/T) + 6*logabs((g - t + T - T*sqrtabs((g2
      + sqr(t - T) - 2*g*(t + T))/Tsq))/(2.*T))* logabs((-g + t + T -
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/(2.*T)) -
      6*dilog((g - t + T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T)) - 6*dilog((-g + t + T - T*sqrtabs((g2 + sqr(t
      - T) - 2*g*(t + T))/Tsq))/ (2.*T))))/(3.*T*sqrtabs((g2 + sqr(t -
      T) - 2*g*(t + T))/Tsq))) + (mg*mu*Tsq*sqrtabs((g2 + sqr(t - T) -
      2*g*(t + T))/Tsq)* (Pi2 - 3*logabs(g/T)*logabs(t/T) +
      6*logabs((g - t + T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T))* logabs((-g + t + T - T*sqrtabs((g2 + sqr(t -
      T) - 2*g*(t + T))/Tsq))/(2.*T)) - 6*dilog((g - t + T -
      T*sqrtabs((g2 + sqr(t - T) - 2*g*(t + T))/Tsq))/ (2.*T)) -
      6*dilog((-g + t + T - T*sqrtabs((g2 + sqr(t - T) - 2*g*(t +
      T))/Tsq))/(2.*T))))/3.))/ (16.*Pi4*Tsq*tanb*sqr(v2));

   Eigen::Matrix<double, 2, 1> result;
   result << t1, t2;

   return -result;
}

/// Pietro Slavich implementation
Eigen::Matrix<double, 2, 1> tadpole_higgs_2loop_at_as_mssm_general(
   double mt2, double mg, double mst12, double mst22,
   double sxt, double cxt, double scale2,
   double mu, double tanb, double vev2, double gs)
{
   Eigen::Matrix<double, 2, 1> result;

   ewsb2loop_(&mt2, &mg, &mst12, &mst22, &sxt, &cxt, &scale2,
              &mu, &tanb, &vev2, &gs, &result(0), &result(1));


   /// Workaround for intel or eigen bug causing unexpected behaviour of allFinite
   if(std::isfinite( result(0) ) == false or std::isfinite( result(1) ) == false )
       result.setZero();

   // if (!result.allFinite())
   //    result.setZero();

   return -result;
}

/// limit st -> 0 and mst1 -> mst2
Eigen::Matrix<double, 2, 2> self_energy_higgs_2loop_at_as_mssm_with_tadpoles_st_0_mst1_eq_mst2(
   double mt2, double mg, double mst12, double /* mst22 */,
   double /* sxt */, double /* cxt */, double scale2, double mu,
   double tanb, double vev2, double gs, int /* scheme */)
{
   using std::fabs;
   using std::sqrt;
   using std::atan;
   using std::log;
   using std::sin;
   using std::pow;
   using gm2calc::dilog;

   constexpr double Pi2 = M_PI * M_PI;
   constexpr double Pi4 = M_PI * M_PI * M_PI * M_PI;
   const double g = sqr(mg);
   const double g2 = sqr(g);
   const double q = scale2;
   const double t = mt2;
   const double tsq = sqr(t);
   const double T = mst12;
   const double Tsq = sqr(mst12);
   const double del = g2 + tsq + Tsq - 2*(g*t + g*T + t*T);
   const double rdel = sqrtabs(del);
   const double sb = sin(atan(tanb));
   const double ht2 = 2./vev2*mt2/sqr(sb);

   Eigen::Matrix<double, 2, 2> result;

   result(0,0) = 0.;

   result(0,1) = (sqr(gs)*ht2*mg*mt2*mu* (-1 + logabs(t/q) -
      (T*((2*del* (-(logabs(t/g)/T) - (2*(g + t - T +
      g*sqrtabs(del/g2))* logabs((g + t - T - g*sqrtabs(del/g2))/
      (2.*g)))/ (g*sqrtabs(del/g2)* (t - T + g*(-1 +
      sqrtabs(del/g2)))) + (2*logabs((g - t + T - g*sqrtabs(del/g2))/
      (2.*g)))/(g*sqrtabs(del/g2)) - (2*((g + t - T +
      g*sqrtabs(del/g2))* logabs((g + t - T + g*sqrtabs(del/g2))/
      (2.*g)) + (g - t + T - g*sqrtabs(del/g2))* logabs((g - t + T +
      g*sqrtabs(del/g2))/ (2.*g))))/ (g*sqrtabs(del/g2)* (t - T +
      g*(-1 + sqrtabs(del/g2))))))/ g2 + (2*(g + t - T)*(Pi2 -
      3*logabs(t/g)*logabs(T/g) + 6*logabs((g + t - T -
      g*sqrtabs(del/g2))/(2.*g))*logabs((g - t + T -
      g*sqrtabs(del/g2))/(2.*g)) - 6*dilog((g + t - T -
      g*sqrtabs(del/g2))/(2.*g)) - 6*dilog((g - t + T -
      g*sqrtabs(del/g2))/(2.*g))))/ (3.*g2)))/(2.*pow(fabs(del)/g2,1.5))))/
      (8.*Pi4*T);

   result(1,0) = result(0,1);

   result(1,1) = (sqr(gs)*ht2*mt2*(-2 - (8*(g + t)*(-1 +
      logabs(g/q)))/T + 8*logabs(t/g) + 6*(-1 + logabs(t/q)) +
      8*sqr(logabs(t/q)) - 4*logabs(T/g) + (4*((g2*T - sqr(t - T)*(2*t
      + T) + 2*g*t*(t + 5*T))*logabs(t/g) +
      4*g2*T*logabs(T/g)))/(del*T) + 2*logabs(T/q) -
      8*sqr(logabs(T/q)) + 5*logabs(Tsq/tsq) + sqr(logabs(Tsq/tsq)) +
      (4*g2*(g + t - T)*(Pi2 - 6*dilog((g + t - T -
      g*sqrtabs(del/g2))/ (2.*g)) - 6*dilog((g - t + T -
      g*sqrtabs(del/g2))/(2.*g)) - 3*logabs(t/g)*logabs(T/g) +
      6*logabs((-rdel + g + t - T)/(2.*g))* logabs((-rdel + g - t +
      T)/(2.*g))))/(3.*pow(fabs(del),1.5)) + (4*g*(g + t - T)*(Pi2 -
      6*dilog((g + t - T - g*sqrtabs(del/g2))/(2.*g)) - 6*dilog((g - t
      + T - g*sqrtabs(del/g2))/ (2.*g)) - 3*logabs(t/g)*logabs(T/g) +
      6*logabs((g + t - T - g*sqrtabs(del/g2))/(2.*g))* logabs((g - t
      + T - g*sqrtabs(del/g2))/(2.*g))))/ (3.*del*sqrtabs(del/g2)) +
      (8*mg*mu*(1/T - logabs(t/q)/T + (g*(g + t - T)* (Pi2 -
      6*dilog((g + t - T - g*sqrtabs(del/g2))/(2.*g)) - 6*dilog((g - t
      + T - g*sqrtabs(del/g2))/ (2.*g)) - 3*logabs(t/g)*logabs(T/g) +
      6*logabs((-rdel + g + t - T)/(2.*g))*logabs((-rdel + g - t +
      T)/(2.*g))))/ (3.*pow(fabs(del),1.5)) + (g*(-(logabs(t/g)/T) -
      (2*(-(g*logabs(4.)) + (rdel + g + t - T)*logabs((-rdel + g + t -
      T)/g) + (-rdel + g - t + T)*logabs((-rdel + g - t + T)/g)))/
      (rdel*(rdel - g + t - T)) - 2*(((rdel + g + t - T)* logabs((g +
      t - T + g*sqrtabs(del/g2))/ (2.*g)))/ (rdel*(t - T + g*(-1 +
      sqrtabs(del/g2)))) - ((rdel - g - t + T)* logabs((g - t + T +
      g*sqrtabs(del/g2))/ (2.*g)))/ (rdel*(-t + T + g*(-1 +
      sqrtabs(del/g2)))))))/ rdel))/tanb))/(32.*Pi4);

   return -result;
}

/// Pietro Slavich implementation
Eigen::Matrix<double, 2, 2> self_energy_higgs_2loop_at_as_mssm_with_tadpoles_general(
   double mt2, double mg, double mst12, double mst22,
   double sxt, double cxt, double scale2, double mu,
   double tanb, double vev2, double gs, int scheme)
{
   Eigen::Matrix<double, 2, 2> result;

   dszhiggs_(&mt2, &mg, &mst12, &mst22, &sxt, &cxt, &scale2, &mu,
             &tanb, &vev2, &gs, &scheme,
             &result(0,0), &result(1,1), &result(0,1));

   result(1,0) = result(0,1);

   return -result;
}

double self_energy_pseudoscalar_2loop_at_as_mssm_with_tadpoles_mst1_eq_mst2(
   double mt2, double mg, double mst12, double mst22,
   double sxt, double cxt, double scale2, double mu,
   double tanb, double vev2, double gs)
{
   using std::atan;
   using std::log;
   using std::sin;

   constexpr double Pi2 = M_PI * M_PI;
   const double g = sqr(mg);
   const double g2 = sqr(g);
   const double q = scale2;
   const double q2 = sqr(scale2);
   const double t = mt2;
   const double T = mst12;
   const double sb = sin(atan(tanb));
   const double ht2 = 2./vev2*mt2/sqr(sb);
   const double At = calc_At(mt2, mst12, mst22, sxt, cxt, mu, tanb);

   const double result = (-2*(g*(2*At*g + 2*At*t - At*T + mg*T + mg*(g
      - t)*logabs(g/t) - At*T*logabs(g/q)*logabs(t/q) -
      mg*T*logabs(g/q)*logabs(t/q) - 4*mg*T*logabs(T/q) -
      2*At*T*sqr(logabs(T/q)) + logabs((g*t)/q2)*(-(At*(g + t - T)) +
      mg*T + (At + mg)*T*logabs(T/q))) - 2*(At + mg)*(g + t -
      T)*T*phi(t,T,g) + T*(At*(g2 + sqr(t - T) - 2*g*T) + mg*(g2 +
      sqr(t - T) - 2*g*(t + T)))*dphi_010(t,T,g)))/ (g*T);

   const double pref = 4*sqr(gs)/sqr(16*Pi2) * ht2*mu*(1./tanb + tanb);

   return -pref * result;
}

double self_energy_pseudoscalar_2loop_at_as_mssm_with_tadpoles_general(
   double mt2, double mg, double mst12, double mst22,
   double sxt, double cxt, double scale2, double mu,
   double tanb, double vev2, double gs)
{
   double result;

   dszodd_(&mt2, &mg, &mst12, &mst22, &sxt, &cxt, &scale2, &mu,
           &tanb, &vev2, &gs, &result);

   return -result;
}

} // anonymous namespace

Eigen::Matrix<double, 2, 1> tadpole_higgs_2loop_at_as_mssm(
   double mt2, double mg, double mst12, double mst22,
   double sxt, double cxt, double scale2,
   double mu, double tanb, double vev2, double gs)
{
   if (std::abs(sxt) < 1e-8) {
      if (std::abs((mst12 - mst22)/mst12) < 1e-6)
         return tadpole_higgs_2loop_at_as_mssm_st_0_mst1_eq_mst2(
            mt2, mg, mst12, mst22, sxt, cxt, scale2, mu, tanb, vev2, gs);

      return tadpole_higgs_2loop_at_as_mssm_st_0(
         mt2, mg, mst12, mst22, sxt, cxt, scale2, mu, tanb, vev2, gs);
   }

   return tadpole_higgs_2loop_at_as_mssm_general(
      mt2, mg, mst12, mst22, sxt, cxt, scale2, mu, tanb, vev2, gs);
}

Eigen::Matrix<double, 2, 1> tadpole_higgs_2loop_at_at_mssm(
   double mt2, double mb2, double mA2, double mst12,
   double mst22, double msb12, double msb22,
   double sxt, double cxt, double sxb, double cxb,
   double scale2, double mu, double tanb, double vev2)
{
   Eigen::Matrix<double, 2, 1> result;

   {
      LOCK_MUTEX();

      ddstad_(&mt2, &mb2, &mA2, &mst12, &mst22, &msb12, &msb22,
              &sxt, &cxt, &sxb, &cxb, &scale2, &mu, &tanb, &vev2,
              &result(0), &result(1));
   }

   /// Workaround for intel or eigen bug causing unexpected behaviour of allFinite
   if(std::isfinite( result(0) ) == false or std::isfinite( result(1) ) == false )
       result.setZero();

   // if (!result.allFinite())
   //    result.setZero();

   return -result;
}

Eigen::Matrix<double, 2, 1> tadpole_higgs_2loop_ab_as_mssm(
   double mb2, double mg, double msb12, double msb22,
   double sxb, double cxb, double scale2,
   double mu, double cotb, double vev2, double gs)
{
   Eigen::Matrix<double, 2, 1> result(tadpole_higgs_2loop_at_as_mssm(
      mb2, mg, msb12, msb22, sxb, cxb, scale2,
      mu, cotb, vev2, gs));

   std::swap(result(0), result(1));

   return result;
}

Eigen::Matrix<double, 2, 1> tadpole_higgs_2loop_atau_atau_mssm(
   double mtau2, double mA2, double msv2, double mstau12,
   double mstau22, double sintau, double costau, double scale2,
   double mu, double tanb, double vev2)
{
   Eigen::Matrix<double, 2, 1> result;

   tausqtad_(&mtau2, &mA2, &msv2, &mstau12, &mstau22, &sintau,
             &costau, &scale2, &mu, &tanb, &vev2, &result(0), &result(1));

   /// Workaround for intel or eigen bug causing unexpected behaviour of allFinite
   if(std::isfinite( result(0) ) == false or std::isfinite( result(1) ) == false )
       result.setZero();

   // if (!result.allFinite())
   //    result.setZero();

   return -result;
}

Eigen::Matrix<double, 2, 2> self_energy_higgs_2loop_at_as_mssm_with_tadpoles(
   double mt2, double mg, double mst12, double mst22,
   double sxt, double cxt, double scale2, double mu,
   double tanb, double vev2, double gs, int scheme)
{
   if (std::abs((mst12 - mst22)/mst12) < 1e-8)
      return self_energy_higgs_2loop_at_as_mssm_with_tadpoles_st_0_mst1_eq_mst2(
         mt2, mg, mst12, mst22, sxt, cxt, scale2, mu, tanb, vev2, gs, scheme);

   return self_energy_higgs_2loop_at_as_mssm_with_tadpoles_general(
      mt2, mg, mst12, mst22, sxt, cxt, scale2, mu, tanb, vev2, gs, scheme);
}

Eigen::Matrix<double, 2, 2> self_energy_higgs_2loop_at_at_mssm_with_tadpoles(
   double mt2, double mb2, double mA2, double mst12,
   double mst22, double msb12, double msb22,
   double sxt, double cxt, double sxb, double cxb,
   double scale2, double mu, double tanb, double vev2)
{
   Eigen::Matrix<double, 2, 2> result;

   {
      LOCK_MUTEX();

      ddshiggs_(&mt2, &mb2, &mA2, &mst12, &mst22, &msb12, &msb22,
                &sxt, &cxt, &sxb, &cxb, &scale2, &mu, &tanb, &vev2,
                &result(0,0), &result(0,1), &result(1,1));
   }

   result(1,0) = result(0,1);

   return -result;
}

Eigen::Matrix<double, 2, 2> self_energy_higgs_2loop_ab_as_mssm_with_tadpoles(
   double mb2, double mg, double msb12, double msb22,
   double sxb, double cxb, double scale2, double mu,
   double cotb, double vev2, double gs, int scheme)
{
   Eigen::Matrix<double, 2, 2> result(self_energy_higgs_2loop_at_as_mssm_with_tadpoles(
      mb2, mg, msb12, msb22, sxb, cxb, scale2, mu,
      cotb, vev2, gs, scheme));

   std::swap(result(0,0), result(1,1));

   return result;
}

Eigen::Matrix<double, 2, 2> self_energy_higgs_2loop_atau_atau_mssm_with_tadpoles(
   double mtau2, double mA2, double msv2, double mstau12,
   double mstau22, double sintau, double costau, double scale2,
   double mu, double tanb, double vev2, int scheme)
{
   Eigen::Matrix<double, 2, 2> result;

   tausqhiggs_(&mtau2, &mA2, &msv2, &mstau12, &mstau22, &sintau,
               &costau, &scale2, &mu, &tanb, &vev2, &scheme,
               &result(0,0), &result(1,1), &result(0,1));

   result(1,0) = result(0,1);

   return -result;
}

double self_energy_pseudoscalar_2loop_at_as_mssm_with_tadpoles(
   double mt2, double mg, double mst12, double mst22,
   double sxt, double cxt, double scale2, double mu,
   double tanb, double vev2, double gs)
{
   if (std::abs((mst12 - mst22)/mst12) < 1e-8) {
      const double At = calc_At(mt2, mst12, mst22, sxt, cxt, mu, tanb);

      // if At = 0 => mu = 0 => dMA(2L) = 0
      if (std::abs(At) < std::numeric_limits<double>::epsilon())
         return 0.;

      return self_energy_pseudoscalar_2loop_at_as_mssm_with_tadpoles_mst1_eq_mst2(
         mt2, mg, mst12, mst22, sxt, cxt, scale2, mu, tanb, vev2, gs);
   }

   return self_energy_pseudoscalar_2loop_at_as_mssm_with_tadpoles_general(
      mt2, mg, mst12, mst22, sxt, cxt, scale2, mu, tanb, vev2, gs);
}

double self_energy_pseudoscalar_2loop_at_at_mssm_with_tadpoles(
   double mt2, double mb2, double mA2, double mst12,
   double mst22, double msb12, double msb22,
   double sxt, double cxt, double sxb, double cxb,
   double scale2, double mu, double tanb, double vev2)
{
   double result;

   {
      LOCK_MUTEX();

      ddsodd_(&mt2, &mb2, &mA2, &mst12, &mst22, &msb12, &msb22,
              &sxt, &cxt, &sxb, &cxb, &scale2, &mu, &tanb, &vev2, &result);
   }

   return -result;
}

double self_energy_pseudoscalar_2loop_ab_as_mssm_with_tadpoles(
   double mb2, double mg, double msb12, double msb22,
   double sxb, double cxb, double scale2, double mu,
   double cotb, double vev2, double gs)
{
   return self_energy_pseudoscalar_2loop_at_as_mssm_with_tadpoles(
      mb2, mg, msb12, msb22, sxb, cxb, scale2, mu,
      cotb, vev2, gs);
}

double self_energy_pseudoscalar_2loop_atau_atau_mssm_with_tadpoles(
   double mtau2, double mA2, double msv2, double mstau12,
   double mstau22, double sintau, double costau, double scale2,
   double mu, double tanb, double vev2)
{
   double result;

   tausqodd_(&mtau2, &mA2, &msv2, &mstau12, &mstau22, &sintau,
             &costau, &scale2, &mu, &tanb, &vev2, &result);

   return -result;
}

// self-energies without tadpoles

Eigen::Matrix<double, 2, 2> rotate_scalar(
   double self_energy, double tanb)
{
   const double tanb2 = sqr(tanb);
   const double sinb = tanb / sqrtabs(1. + tanb2);
   const double cosb = 1. / sqrtabs(1. + tanb2);

   Eigen::Matrix<double, 2, 2> result;

   result(0,0) = self_energy * sqr(sinb);
   result(0,1) = - self_energy * sinb * cosb;
   result(1,0) = result(0,1);
   result(1,1) = self_energy * sqr(cosb);

   return result;
}

Eigen::Matrix<double, 2, 2> subtract_mssm_tadpoles_scalar(
   double self_energy, const Eigen::Matrix<double, 2, 1>& tadpoles,
   double tanb)
{
   return rotate_scalar(self_energy, tanb) + Eigen::Matrix<double, 2, 2>(tadpoles.asDiagonal());
}

Eigen::Matrix<double, 2, 2> self_energy_higgs_2loop_at_as_mssm(
   double mt2, double mg, double mst12, double mst22,
   double sxt, double cxt, double scale2, double mu,
   double tanb, double vev2, double gs, int scheme)
{
   const Eigen::Matrix<double, 2, 2> result =
      self_energy_higgs_2loop_at_as_mssm_with_tadpoles(
         mt2, mg, mst12, mst22, sxt, cxt, scale2, mu,
         tanb, vev2, gs, scheme);

   const double dMA = self_energy_pseudoscalar_2loop_at_as_mssm_with_tadpoles(
      mt2, mg, mst12, mst22, sxt, cxt, scale2, mu,
      tanb, vev2, gs);

   const Eigen::Matrix<double, 2, 1> tadpoles =
      tadpole_higgs_2loop_at_as_mssm(
         mt2, mg, mst12, mst22, sxt, cxt, scale2, mu, tanb, vev2, gs);

   const Eigen::Matrix<double, 2, 2> tM =
      subtract_mssm_tadpoles_scalar(dMA, tadpoles, tanb);

   return result + tM;
}

Eigen::Matrix<double, 2, 2> self_energy_higgs_2loop_at_at_mssm(
   double mt2, double mb2, double mA2, double mst12,
   double mst22, double msb12, double msb22,
   double sxt, double cxt, double sxb, double cxb,
   double scale2, double mu, double tanb, double vev2)
{
   const Eigen::Matrix<double, 2, 2> result =
      self_energy_higgs_2loop_at_at_mssm_with_tadpoles(
         mt2, mb2, mA2, mst12, mst22, msb12, msb22,
         sxt, cxt, sxb, cxb, scale2, mu, tanb, vev2);

   const double dMA = self_energy_pseudoscalar_2loop_at_at_mssm_with_tadpoles(
      mt2, mb2, mA2, mst12, mst22, msb12, msb22,
      sxt, cxt, sxb, cxb, scale2, mu, tanb, vev2);

   const Eigen::Matrix<double, 2, 1> tadpoles =
      tadpole_higgs_2loop_at_at_mssm(
         mt2, mb2, mA2, mst12, mst22, msb12, msb22,
         sxt, cxt, sxb, cxb, scale2, mu, tanb, vev2);

   const Eigen::Matrix<double, 2, 2> tM =
      subtract_mssm_tadpoles_scalar(dMA, tadpoles, tanb);

   return result + tM;
}

Eigen::Matrix<double, 2, 2> self_energy_higgs_2loop_ab_as_mssm(
   double mb2, double mg, double msb12, double msb22,
   double sxb, double cxb, double scale2, double mu,
   double cotb, double vev2, double gs, int scheme)
{
   const Eigen::Matrix<double, 2, 2> result =
      self_energy_higgs_2loop_ab_as_mssm_with_tadpoles(
         mb2, mg, msb12, msb22, sxb, cxb, scale2, mu,
         cotb, vev2, gs, scheme);

   const double dMA = self_energy_pseudoscalar_2loop_ab_as_mssm_with_tadpoles(
      mb2, mg, msb12, msb22, sxb, cxb, scale2, mu, cotb, vev2, gs);

   const Eigen::Matrix<double, 2, 1> tadpoles =
      tadpole_higgs_2loop_ab_as_mssm(
         mb2, mg, msb12, msb22, sxb, cxb, scale2, mu, cotb, vev2, gs);

   const Eigen::Matrix<double, 2, 2> tM =
      subtract_mssm_tadpoles_scalar(dMA, tadpoles, 1./cotb);

   return result + tM;
}

Eigen::Matrix<double, 2, 2> self_energy_higgs_2loop_atau_atau_mssm(
   double mtau2, double mA2, double msv2, double mstau12,
   double mstau22, double sintau, double costau, double scale2,
   double mu, double tanb, double vev2, int scheme)
{
   const Eigen::Matrix<double, 2, 2> result =
      self_energy_higgs_2loop_atau_atau_mssm_with_tadpoles(
         mtau2, mA2, msv2, mstau12, mstau22, sintau, costau, scale2,
         mu, tanb, vev2, scheme);

   const double dMA = self_energy_pseudoscalar_2loop_atau_atau_mssm_with_tadpoles(
      mtau2, mA2, msv2, mstau12, mstau22, sintau, costau, scale2,
      mu, tanb, vev2);

   const Eigen::Matrix<double, 2, 1> tadpoles =
      tadpole_higgs_2loop_atau_atau_mssm(
         mtau2, mA2, msv2, mstau12, mstau22, sintau, costau, scale2,
         mu, tanb, vev2);

   const Eigen::Matrix<double, 2, 2> tM =
      subtract_mssm_tadpoles_scalar(dMA, tadpoles, tanb);

   return result + tM;
}

Eigen::Matrix<double, 2, 2> rotate_pseudoscalar(
   double self_energy, double tanb)
{
   const double tanb2 = sqr(tanb);
   const double sinb = tanb / sqrtabs(1. + tanb2);
   const double cosb = 1. / sqrtabs(1. + tanb2);

   Eigen::Matrix<double, 2, 2> result;

   // see hep-ph/0105096 Eq. (9)
   result(0,0) = self_energy * sqr(sinb);
   result(0,1) = self_energy * sinb * cosb;
   result(1,0) = result(0,1);
   result(1,1) = self_energy * sqr(cosb);

   return result;
}

Eigen::Matrix<double, 2, 2> subtract_mssm_tadpoles_pseudoscalar(
   double self_energy, const Eigen::Matrix<double, 2, 1>& tadpoles,
   double tanb)
{
   return rotate_pseudoscalar(self_energy, tanb) + Eigen::Matrix<double, 2, 2>(tadpoles.asDiagonal());
}

Eigen::Matrix<double, 2, 2> self_energy_pseudoscalar_2loop_at_as_mssm(
   double mt2, double mg, double mst12, double mst22,
   double sxt, double cxt, double scale2, double mu,
   double tanb, double vev2, double gs)
{
   const double se = self_energy_pseudoscalar_2loop_at_as_mssm_with_tadpoles(
      mt2, mg, mst12, mst22, sxt, cxt, scale2, mu, tanb, vev2, gs);

   const Eigen::Matrix<double, 2, 1> tadpoles =
      tadpole_higgs_2loop_at_as_mssm(
         mt2, mg, mst12, mst22, sxt, cxt, scale2, mu, tanb, vev2, gs);

   return subtract_mssm_tadpoles_pseudoscalar(se, tadpoles, tanb);
}

Eigen::Matrix<double, 2, 2> self_energy_pseudoscalar_2loop_at_at_mssm(
   double mt2, double mb2, double mA2, double mst12,
   double mst22, double msb12, double msb22,
   double sxt, double cxt, double sxb, double cxb,
   double scale2, double mu, double tanb, double vev2)
{
   const double se = self_energy_pseudoscalar_2loop_at_at_mssm_with_tadpoles(
      mt2, mb2, mA2, mst12, mst22, msb12, msb22,
      sxt, cxt, sxb, cxb, scale2, mu, tanb, vev2);

   const Eigen::Matrix<double, 2, 1> tadpoles =
      tadpole_higgs_2loop_at_at_mssm(
         mt2, mb2, mA2, mst12, mst22, msb12, msb22,
         sxt, cxt, sxb, cxb, scale2, mu, tanb, vev2);

   return subtract_mssm_tadpoles_pseudoscalar(se, tadpoles, tanb);
}

Eigen::Matrix<double, 2, 2> self_energy_pseudoscalar_2loop_ab_as_mssm(
   double mb2, double mg, double msb12, double msb22,
   double sxb, double cxb, double scale2, double mu,
   double cotb, double vev2, double gs)
{
   const double se = self_energy_pseudoscalar_2loop_ab_as_mssm_with_tadpoles(
      mb2, mg, msb12, msb22, sxb, cxb, scale2, mu, cotb, vev2, gs);

   const Eigen::Matrix<double, 2, 1> tadpoles =
      tadpole_higgs_2loop_ab_as_mssm(
         mb2, mg, msb12, msb22, sxb, cxb, scale2, mu, cotb, vev2, gs);

   return subtract_mssm_tadpoles_pseudoscalar(se, tadpoles, 1./cotb);
}

Eigen::Matrix<double, 2, 2> self_energy_pseudoscalar_2loop_atau_atau_mssm(
   double mtau2, double mA2, double msv2, double mstau12,
   double mstau22, double sintau, double costau, double scale2,
   double mu, double tanb, double vev2)
{
   const double se = self_energy_pseudoscalar_2loop_atau_atau_mssm_with_tadpoles(
      mtau2, mA2, msv2, mstau12, mstau22, sintau, costau, scale2,
      mu, tanb, vev2);

   const Eigen::Matrix<double, 2, 1> tadpoles =
      tadpole_higgs_2loop_atau_atau_mssm(
         mtau2, mA2, msv2, mstau12, mstau22, sintau, costau, scale2,
         mu, tanb, vev2);

   return subtract_mssm_tadpoles_pseudoscalar(se, tadpoles, tanb);
}

} // namespace mssm_twoloophiggs
} // namespace flexiblesusy
