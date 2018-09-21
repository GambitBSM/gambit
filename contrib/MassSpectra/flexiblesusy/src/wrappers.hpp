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

#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <algorithm>
#include <cmath>
#include <complex>
#include <functional>
#include <limits>
#include <numeric>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <Eigen/Core>
#include <boost/lexical_cast.hpp>

#include "config.h"
#include "dilog.hpp"
#include "error.hpp"
#include "eigen_tensor.hpp"
#include "error.hpp"
#include "if.hpp"
#include "numerics2.hpp"
#include "sum.hpp"
#include "which.hpp"

namespace flexiblesusy {

static constexpr double Pi = M_PI;
static constexpr double oneOver16PiSqr = 1./(16. * Pi * Pi);
static constexpr double oneLoop = oneOver16PiSqr;
static constexpr double twoLoop = oneOver16PiSqr * oneOver16PiSqr;
static constexpr double threeLoop = oneOver16PiSqr * oneOver16PiSqr * oneOver16PiSqr;
static constexpr bool True = true;

template <typename T>
T Abs(T a) noexcept
{
   return std::abs(a);
}

template <typename T>
T Abs(const std::complex<T>& z) noexcept
{
   return std::abs(z);
}

template <typename Scalar, int M, int N>
Eigen::Array<Scalar, M, N> Abs(const Eigen::Array<Scalar, M, N>& a)
{
   return a.cwiseAbs();
}

template <typename Scalar, int M, int N>
Eigen::Matrix<Scalar, M, N> Abs(const Eigen::Matrix<Scalar, M, N>& a)
{
   return a.cwiseAbs();
}

template <class T>
std::vector<T> Abs(std::vector<T> v) noexcept
{
   for (auto& e: v)
      e = Abs(e);
   return v;
}

inline constexpr double AbsSqr(double z) noexcept
{
   return z * z;
}

inline double AbsSqr(const std::complex<double>& z) noexcept
{
   return std::norm(z);
}

inline double AbsSqrt(double x) noexcept
{
   return std::sqrt(std::fabs(x));
}

template <typename Derived>
Derived AbsSqrt(const Eigen::MatrixBase<Derived>& m)
{
   return m.cwiseAbs().cwiseSqrt();
}

template <typename Derived>
Derived AbsSqrt(const Eigen::ArrayBase<Derived>& m)
{
   return m.cwiseAbs().cwiseSqrt();
}

/**
 * Calculates the mass of a singlet from a (possibly complex)
 * numerical value by taking the magnitude of the value.
 *
 * @param value numerical value
 * @return mass
 */
template <typename T>
double calculate_singlet_mass(T value) noexcept
{
   return std::abs(value);
}

/**
 * Calculates the mass of a Majoran fermion singlet from a (possibly
 * complex) numerical value by taking the magnitude of the value.
 *
 * The phase is set to exp(i theta/2), where theta is the phase angle
 * of the complex value.  If the value is pure real, then the phase
 * will be set to 1.  If the value is purely imaginary, then the phase
 * will be set to \f$e^{i \pi/2}\f$.
 *
 * @param value numerical value
 * @param[out] phase phase
 * @return mass
 */
template <typename T>
double calculate_majorana_singlet_mass(T value, std::complex<double>& phase)
{
   phase = std::polar(1., 0.5 * std::arg(std::complex<double>(value)));
   return std::abs(value);
}

/**
 * Calculates the mass of a Dirac fermion singlet from a (possibly
 * complex) numerical value by taking the magnitude of the value.
 *
 * The phase is set to exp(i theta), where theta is the phase angle of
 * the complex value.  If the value is pure real, then the phase will
 * be set to 1.  If the value is purely imaginary, then the phase will
 * be set to \f$e^{i \pi}\f$.
 *
 * @param value numerical value
 * @param[out] phase phase
 * @return mass
 */
template <typename T>
double calculate_dirac_singlet_mass(T value, std::complex<double>& phase)
{
   phase = std::polar(1., std::arg(std::complex<double>(value)));
   return std::abs(value);
}

inline double ArcTan(double a) noexcept
{
   return std::atan(a);
}

inline double ArcSin(double a) noexcept
{
   return std::asin(a);
}

inline double ArcCos(double a) noexcept
{
   return std::acos(a);
}

inline double Arg(const std::complex<double>& z) noexcept
{
   return std::arg(z);
}

template <typename T>
constexpr T Cbrt(T a) noexcept
{
   return std::cbrt(a);
}

inline constexpr double Conj(double a) noexcept
{
   return a;
}

inline std::complex<double> Conj(const std::complex<double>& a) noexcept
{
   return std::conj(a);
}

template <class T>
T Conjugate(T a) noexcept
{
   return Conj(a);
}

template <typename T>
constexpr T Cube(T a) noexcept
{
   return a * a * a;
}

template <typename T>
T Exp(T z) noexcept
{
   return std::exp(z);
}

inline double Tan(double a) noexcept
{
   return std::tan(a);
}

inline double Cot(double a) noexcept
{
   return 1./Tan(a);
}

inline double Cos(double x) noexcept
{
   return std::cos(x);
}

inline double Sin(double x) noexcept
{
   return std::sin(x);
}

inline double Sec(double x) noexcept
{
   return 1./Cos(x);
}

inline double Csc(double x) noexcept
{
   return 1./Sin(x);
}

inline constexpr int Delta(int i, int j) noexcept
{
   return i == j;
}

#define FSFlagProblem(p) [&](){ (p); return 0.; }()
#define FSFlagWarning(p) [&](){ (p); return 0.; }()

template <typename T>
constexpr T If(bool c, T a, T b) noexcept { return c ? a : b; }

template <typename T>
constexpr T If(bool c, int a, T b)  noexcept{ return c ? T(a) : b; }

template <typename T>
constexpr T If(bool c, T a, int b) noexcept { return c ? a : T(b); }

inline bool IsClose(double a, double b,
                    double eps = std::numeric_limits<double>::epsilon()) noexcept
{
   return std::abs(a - b) < eps;
}

inline bool IsCloseRel(double a, double b,
                       double eps = std::numeric_limits<double>::epsilon()) noexcept
{
   if (IsClose(a, b, std::numeric_limits<double>::epsilon()))
      return true;

   if (std::abs(a) < std::numeric_limits<double>::epsilon())
      return IsClose(a, b, eps);

   return std::abs((a - b)/a) < eps;
}

inline bool IsFinite(double x) noexcept
{
   return std::isfinite(x);
}

inline bool IsFinite(const std::complex<double>& x) noexcept
{
   return std::isfinite(x.real()) && std::isfinite(x.imag());
}

template <class Derived>
bool IsFinite(const Eigen::DenseBase<Derived>& m)
{
  // workaround for intel compiler / eigen bug that causes
  // unexpected behavior from allFinite
  int nr = m.rows();
  int nc = m.cols();
  bool allfinite = true;
  for (int r = 0; r<nr; ++r) {
    for (int c = 0; c<nc; ++c) {
      if ( !std::isfinite( m(r,c) ) ) allfinite = false;
    }
  }

  return allfinite;
  //   return m.allFinite();
}

inline constexpr int KroneckerDelta(int i, int j) noexcept
{
   return i == j;
}

template <class Derived>
typename Eigen::MatrixBase<Derived>::PlainObject Diag(const Eigen::MatrixBase<Derived>& m) noexcept
{
   static_assert(Eigen::MatrixBase<Derived>::RowsAtCompileTime ==
                 Eigen::MatrixBase<Derived>::ColsAtCompileTime,
                 "Diag is only defined for squared matrices");

   typename Eigen::MatrixBase<Derived>::PlainObject diag(m);

   for (int i = 0; i < Eigen::MatrixBase<Derived>::RowsAtCompileTime; ++i)
      for (int k = i + 1; k < Eigen::MatrixBase<Derived>::ColsAtCompileTime; ++k)
         diag(i,k) = 0.0;

   for (int i = 0; i < Eigen::MatrixBase<Derived>::RowsAtCompileTime; ++i)
      for (int k = 0; k < i; ++k)
         diag(i,k) = 0.0;

   return diag;
}

inline std::complex<double> ComplexLog(double a) noexcept
{
   return fast_log(std::complex<double>(a,0.));
}

inline std::complex<double> ComplexLog(const std::complex<double>& z) noexcept
{
   return fast_log(z);
}

inline double FiniteLog(double a) noexcept
{
   const double l = std::log(a);
   return std::isfinite(l) ? l : 0.;
}

/**
 * Fills lower triangle of hermitian matrix from values
 * in upper triangle.
 *
 * @param m matrix
 */
template <typename Derived>
void Hermitianize(Eigen::MatrixBase<Derived>& m) noexcept
{
   static_assert(Eigen::MatrixBase<Derived>::RowsAtCompileTime ==
                 Eigen::MatrixBase<Derived>::ColsAtCompileTime,
                 "Hermitianize is only defined for squared matrices");

   for (int i = 0; i < Eigen::MatrixBase<Derived>::RowsAtCompileTime; i++)
      for (int k = 0; k < i; k++)
         m(i,k) = Conj(m(k,i));
}

///////////////////////// logger commands /////////////////////////

namespace {
inline double PrintTo(std::ostream& ostr)
{
   ostr << '\n';
   return 0.;
}
} // anonymous namespace

///< print information to ostr
template<typename T0, typename... Ts>
double PrintTo(std::ostream& ostr, T0&& v, Ts&&... vs)
{
   ostr << v;
   return PrintTo(ostr, std::forward<Ts>(vs)...);
}

///< print debug information to cerr
template<typename... Ts>
double PrintDEBUG(Ts&&... vs)
{
#ifdef ENABLE_DEBUG
   return PrintTo(std::cerr, std::forward<Ts>(vs)...);
#else
   return 0.;
#endif
}

///< print error to cerr
template<typename... Ts>
double PrintERROR(Ts&&... vs)
{
   std::cerr << "ERROR: ";
   return PrintTo(std::cerr, std::forward<Ts>(vs)...);
}

///< print error to cerr and stop program
template<typename... Ts>
double PrintFATAL(Ts&&... vs)
{
   std::cerr << "FATAL: ";
   PrintTo(std::cerr, std::forward<Ts>(vs)...);
   throw FatalError();
   return 0.;
}

///< print information to cerr
template<typename... Ts>
double PrintINFO(Ts&&... vs)
{
   return PrintTo(std::cerr, std::forward<Ts>(vs)...);
}

///< print verbose information to cerr
template<typename... Ts>
double PrintVERBOSE(Ts&&... vs)
{
#ifdef ENABLE_VERBOSE
   return PrintTo(std::cerr, std::forward<Ts>(vs)...);
#else
   return 0.;
#endif
}

///< print warning to cerr
template<typename... Ts>
double PrintWARNING(Ts&&... vs)
{
   std::cerr << "WARNING: ";
   return PrintTo(std::cerr, std::forward<Ts>(vs)...);
}

///////////////////////// end of logger commands /////////////////////////

inline double Log(double a) noexcept
{
   return std::log(a);
}

double MaxRelDiff(double, double);
double MaxRelDiff(const std::complex<double>&, const std::complex<double>&);

template <class Derived>
double MaxRelDiff(const Eigen::MatrixBase<Derived>& a,
                  const Eigen::MatrixBase<Derived>& b)
{
   typename Eigen::MatrixBase<Derived>::PlainObject sumTol(a.rows());

   if (a.rows() != b.rows())
      throw SetupError("MaxRelDiff: vectors have different size!");

   for (int i = 0; i < a.rows(); i++)
      sumTol(i) = MaxRelDiff(a(i), b(i));

   return sumTol.maxCoeff();
}

template <class Derived>
double MaxRelDiff(const Eigen::ArrayBase<Derived>& a,
                  const Eigen::ArrayBase<Derived>& b)
{
   return MaxRelDiff(a.matrix(), b.matrix());
}

inline double MaxAbsValue(double x) noexcept
{
   return Abs(x);
}

inline double MaxAbsValue(const std::complex<double>& x) noexcept
{
   return Abs(x);
}

template <class Derived>
double MaxAbsValue(const Eigen::MatrixBase<Derived>& x)
{
   return x.cwiseAbs().maxCoeff();
}

template<typename T>
T Max(T&&t)
{
   return std::forward<T>(t);
}

template<typename T0, typename T1, typename... Ts>
typename std::common_type<T0, T1, Ts...>::type Max(T0&& val1, T1&& val2, Ts&&... vs)
{
   if (val2 < val1)
      return Max(val1, std::forward<Ts>(vs)...);
   else
      return Max(val2, std::forward<Ts>(vs)...);
}

template<typename T>
T Min(T&&t)
{
   return std::forward<T>(t);
}

template<typename T0, typename T1, typename... Ts>
typename std::common_type<T0, T1, Ts...>::type Min(T0&& val1, T1&& val2, Ts&&... vs)
{
   if (val2 < val1)
      return Min(val2, std::forward<Ts>(vs)...);
   else
      return Min(val1, std::forward<Ts>(vs)...);
}

inline constexpr int Sign(double x) noexcept
{
   return (x >= 0.0 ? 1 : -1);
}

inline constexpr int Sign(int x) noexcept
{
   return (x >= 0 ? 1 : -1);
}

template <typename T>
constexpr T Quad(T a) noexcept
{
   return a * a * a * a;
}

template <typename T>
T PolyLog(int n, T z) {
   if (n == 2)
      return gm2calc::dilog(z);
   throw SetupError("PolyLog(n!=2) not implemented");
}

template <typename Base, typename Exponent>
Base Power(Base base, Exponent exp) noexcept
{
   return std::pow(base, exp);
}

template <typename Base>
constexpr Base Power2(Base b) noexcept
{
   return b * b;
}

template <typename Base>
constexpr Base Power3(Base b) noexcept
{
   return b * b * b;
}

template <typename Base>
constexpr Base Power4(Base b) noexcept
{
   return b * b * b * b;
}

template <typename Base>
constexpr Base Power5(Base b) noexcept
{
   return b * b * b * b * b;
}

template <typename Base>
constexpr Base Power6(Base b) noexcept
{
   return b * b * b * b * b * b;
}

template <typename Base>
constexpr Base Power7(Base b) noexcept
{
   return b * b * b * b * b *
          b * b;
}

template <typename Base>
constexpr Base Power8(Base b) noexcept
{
   return b * b * b * b * b *
          b * b * b;
}

template <typename Base>
constexpr Base Power9(Base b) noexcept
{
   return b * b * b * b * b *
          b * b * b * b;
}

template <typename Base>
constexpr Base Power10(Base b) noexcept
{
   return b * b * b * b * b *
          b * b * b * b * b;
}

template <typename Base>
constexpr Base Power11(Base b) noexcept
{
   return b * b * b * b * b *
          b * b * b * b * b *
          b;
}

template <typename Base>
constexpr Base Power12(Base b) noexcept
{
   return b * b * b * b * b *
          b * b * b * b * b *
          b * b;
}

inline constexpr double Re(double x) noexcept
{
   return x;
}

inline double Re(const std::complex<double>& x) noexcept
{
   return std::real(x);
}

template<int M, int N>
Eigen::Matrix<double,M,N> Re(const Eigen::Matrix<double,M,N>& x)
{
   return x;
}

template<class Derived>
typename Eigen::Matrix<
   double,
   Eigen::MatrixBase<Derived>::RowsAtCompileTime,
   Eigen::MatrixBase<Derived>::ColsAtCompileTime>
Re(const Eigen::MatrixBase<Derived>& x)
{
   return x.real();
}

inline constexpr double Im(double) noexcept
{
   return 0.;
}

inline double Im(const std::complex<double>& x) noexcept
{
   return std::imag(x);
}

template<int M, int N>
Eigen::Matrix<double,M,N> Im(const Eigen::Matrix<double,M,N>&)
{
   return Eigen::Matrix<double,M,N>::Zero();
}

template<class Derived>
typename Eigen::Matrix<
   double,
   Eigen::MatrixBase<Derived>::RowsAtCompileTime,
   Eigen::MatrixBase<Derived>::ColsAtCompileTime>
Im(const Eigen::MatrixBase<Derived>& x)
{
   return x.imag();
}

template <typename T>
T RelDiff(T a, T b, T eps = std::numeric_limits<T>::epsilon()) noexcept
{
   const T max = std::max(a, b);

   if (std::abs(max) < eps)
      return T();

   return (a - b) / max;
}

inline int Round(double a) noexcept
{
   return static_cast<int>(a >= 0. ? a + 0.5 : a - 0.5);
}

template<int N>
void Sort(Eigen::Array<double, N, 1>& v)
{
   std::sort(v.data(), v.data() + v.size(),
             [] (double a, double b) { return std::abs(a) < std::abs(b); });
}

inline double SignedAbsSqrt(double a) noexcept
{
   return Sign(a) * AbsSqrt(a);
}

template <typename Derived>
Derived SignedAbsSqrt(const Eigen::ArrayBase<Derived>& m)
{
   return m.unaryExpr([](double a) { return SignedAbsSqrt(a); });
}

template <class T, typename = typename std::enable_if<std::is_floating_point<T>::value,T>::type>
T Sqrt(T a) noexcept
{
   return std::sqrt(a);
}

template <class T, typename = typename std::enable_if<std::is_integral<T>::value,T>::type>
double Sqrt(T a) noexcept
{
   return std::sqrt(static_cast<double>(a));
}

template <typename Scalar, int M, int N>
Eigen::Array<Scalar, M, N> Sqrt(const Eigen::Array<Scalar, M, N>& m)
{
   return m.unaryExpr([](Scalar a){ return Sqrt(a); });
}

template <class T>
std::vector<T> Sqrt(std::vector<T> v)
{
   for (auto& e: v)
      e = Sqrt(e);
   return v;
}

template <typename T>
constexpr T Sqr(T a) noexcept
{
   return a * a;
}

template <typename Scalar, int M, int N>
Eigen::Array<Scalar, M, N> Sqr(const Eigen::Array<Scalar, M, N>& a)
{
   return a.unaryExpr([](Scalar a){ return Sqr(a); });
}

template <class T>
std::vector<T> Sqr(std::vector<T> v)
{
   for (auto& e: v)
      e = Sqr(e);
   return v;
}

#define DEFINE_COMMUTATIVE_OPERATOR_COMPLEX_INT(op)                     \
   template <typename T>                                                \
   std::complex<T> operator op(const std::complex<T>& lhs, int rhs)     \
   {                                                                    \
      return lhs op static_cast<T>(rhs);                                \
   }                                                                    \
                                                                        \
   template <typename T>                                                \
   std::complex<T> operator op(int lhs, const std::complex<T>& rhs)     \
   {                                                                    \
      return static_cast<T>(lhs) op rhs;                                \
   }

DEFINE_COMMUTATIVE_OPERATOR_COMPLEX_INT(*)
DEFINE_COMMUTATIVE_OPERATOR_COMPLEX_INT(/)
DEFINE_COMMUTATIVE_OPERATOR_COMPLEX_INT(+)
DEFINE_COMMUTATIVE_OPERATOR_COMPLEX_INT(-)

/**
 * Fills lower triangle of symmetric matrix from values in upper
 * triangle.
 *
 * @param m matrix
 */
template <typename Derived>
void Symmetrize(Eigen::MatrixBase<Derived>& m)
{
   static_assert(Eigen::MatrixBase<Derived>::RowsAtCompileTime ==
                 Eigen::MatrixBase<Derived>::ColsAtCompileTime,
                 "Symmetrize is only defined for squared matrices");

   for (int i = 0; i < Eigen::MatrixBase<Derived>::RowsAtCompileTime; i++)
      for (int k = 0; k < i; k++)
         m(i,k) = m(k,i);
}

#define UNITMATRIX(rows)             Eigen::Matrix<double,rows,rows>::Identity()
#define ZEROMATRIX(rows,cols)        Eigen::Matrix<double,rows,cols>::Zero()
#define ZEROTENSOR3(d1,d2,d3)        ZeroTensor3<double,d1,d2,d3>()
#define ZEROTENSOR4(d1,d2,d3,d4)     ZeroTensor4<double,d1,d2,d3,d4>()
#define ZEROVECTOR(rows)             Eigen::Matrix<double,rows,1>::Zero()
#define ZEROARRAY(rows)              Eigen::Array<double,rows,1>::Zero()
#define UNITMATRIXCOMPLEX(rows)      Eigen::Matrix<std::complex<double>,rows,rows>::Identity()
#define ZEROMATRIXCOMPLEX(rows,cols) Eigen::Matrix<std::complex<double>,rows,cols>::Zero()
#define ZEROVECTORCOMPLEX(rows)      Eigen::Matrix<std::complex<double>,rows,1>::Zero()
#define ZEROTENSOR3COMPLEX(d1,d2,d3) ZeroTensor3<std::complex<double>,d1,d2,d3>()
#define ZEROTENSOR4COMPLEX(d1,d2,d3,d4) ZeroTensor4<std::complex<double>,d1,d2,d3,d4>()
#define ZEROARRAYCOMPLEX(rows)       Eigen::Array<std::complex<double>,rows,1>::Zero()

// MxN matrix projection operator, which projects on the (X,Y)
// component
#define PROJECTOR Proj
#define DEFINE_PROJECTOR(M,N,X,Y)                                       \
   Eigen::Matrix<double,M,N> Proj(Eigen::Matrix<double,M,N>::Zero());   \
   Proj((X)-1,(Y)-1) = 1;

inline double FSThrow(const std::string& s)
{
   throw PhysicalError(s);
   return 0.;
}

template<class Scalar, int M>
Eigen::Matrix<Scalar,M,M> ToMatrix(const Eigen::Array<Scalar,M,1>& a)
{
   return Eigen::Matrix<Scalar,M,M>(a.matrix().asDiagonal());
}

template<class Scalar, int M, int N>
Eigen::Matrix<Scalar,M,N> ToMatrix(const Eigen::Matrix<Scalar,M,N>& a) noexcept
{
   return a;
}

template <typename T>
std::string ToString(T a)
{
   return boost::lexical_cast<std::string>(a);
}

inline double Total(double a) noexcept
{
   return a;
}

inline std::complex<double> Total(const std::complex<double>& a) noexcept
{
   return a;
}

template <class T>
T Total(const std::vector<T>& v)
{
   return std::accumulate(v.begin(), v.end(), T(0));
}

template <typename Scalar, int M, int N>
Scalar Total(const Eigen::Array<Scalar, M, N>& a)
{
   return a.sum();
}

template <typename Scalar, int M, int N>
Scalar Total(const Eigen::Matrix<Scalar, M, N>& a)
{
   return a.sum();
}

template <class Scalar, int M, int N>
Eigen::Array<Scalar,M,N> Total(const std::vector<Eigen::Array<Scalar,M,N> >& v)
{
   if (v.empty()) {
      Eigen::Array<Scalar,M,N> result(0,0);
      result.setZero();
      return result;
   }

   Eigen::Array<Scalar,M,N> result(v[0].rows(), v[0].cols());
   result.setZero();

   for (std::size_t i = 0; i < v.size(); i++)
      result += v[i];

   return result;
}

/// unit vector of length N into direction i
template <int N, int i, typename Scalar = double>
constexpr auto UnitVector() -> Eigen::Matrix<Scalar,N,1>
{
   return Eigen::Matrix<Scalar,N,1>::Unit(i);
}

/// unit vector of length N into direction i
template <int N, typename Scalar = double>
constexpr auto UnitVector(int i) -> Eigen::Matrix<Scalar,N,1>
{
   return Eigen::Matrix<Scalar,N,1>::Unit(i);
}

/// unit vector of length N into direction i
inline Eigen::VectorXd UnitVector(int N, int i)
{
   Eigen::VectorXd v = Eigen::VectorXd::Zero(N);
   v(i) = 1;

   return v;
}

/// matrix projector of size MxN into direction i, j
template <int M, int N, int i, int j, typename Scalar = double>
auto MatrixProjector() -> Eigen::Matrix<Scalar,M,N>
{
   Eigen::Matrix<Scalar,M,N> proj(Eigen::Matrix<Scalar,M,N>::Zero());
   proj(i,j) = 1;

   return proj;
}

/// matrix projector of size MxN into direction i, j
template <int M, int N, typename Scalar = double>
auto MatrixProjector(int i, int j) -> Eigen::Matrix<Scalar,M,N>
{
   Eigen::Matrix<Scalar,M,N> proj(Eigen::Matrix<Scalar,M,N>::Zero());
   proj(i,j) = 1;

   return proj;
}

/// unit matrix projector of size MxN into direction i, j
inline Eigen::MatrixXd MatrixProjector(int M, int N, int i, int j)
{
   Eigen::MatrixXd m = Eigen::MatrixXd::Zero(M,N);
   m(i,j) = 1;

   return m;
}

/// step function (0 for x < 0, 1 otherwise)
template <typename T>
constexpr int UnitStep(T x) noexcept
{
   return x < T() ? 0 : 1;
}

template <typename T>
constexpr T Which(bool cond, T value) noexcept
{
   return cond ? value : T(0);
}

template<typename T, typename ... Trest>
constexpr typename std::common_type<T, Trest...>::type Which(bool cond, T value, Trest... rest) noexcept
{
   return cond ? value : Which(rest...);
}

inline double ZeroSqrt(double x) noexcept
{
   return (x > 0.0 ? std::sqrt(x) : 0.0);
}

template <typename Derived>
Derived ZeroSqrt(const Eigen::ArrayBase<Derived>& m)
{
   return m.unaryExpr([](double a){ return ZeroSqrt(a); });
}

} // namespace flexiblesusy

#endif
