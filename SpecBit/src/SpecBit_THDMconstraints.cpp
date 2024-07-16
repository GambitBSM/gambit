//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///
///  *********************************************
///
///  Authors:
///
///  \author A.S. Woodcock
///          (alex.woodcock@outlook.com)
///  \date   Feb 2022
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
///
///  **********************************************


// GSL headers
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_deriv.h>

// Eigen headers
#include "gambit/Utils/begin_ignore_warnings_eigen.hpp"
#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include "gambit/Utils/end_ignore_warnings.hpp"

// GAMBIT headers
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Elements/couplingtable.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Utils/point_counter.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"

namespace Gambit
{
  
  namespace SpecBit
  {

    // ----- HELPERS -----

    constexpr double inv_LL_threshold = 1e5;
    // ...
    constexpr double eps = 1e-10;
    // ...
    constexpr double minInvalidLL = 10.;
    // used to invalidate likelihood
    constexpr double L_MAX = 1e50;
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    // type aliases
    using namespace Utils;
    using std::vector;
    using std::complex;
    using std::real;
    using std::imag;
    using std::conj;
    struct ThdmSpec;

    typedef std::function<double(const SubSpectrum&)> LL_type;
    typedef std::function<double(const SubSpectrum&, const CouplingTable&)> LL_type2;
    typedef double(*gsl_funn)(double, void*);

    namespace RunScale
    {
      // constexpr double NONE = -2.0;
      constexpr double INPUT = -1.0;
    }

    // forward declarations
    double Z_w(const ThdmSpec &s, const std::vector<complexd>& C3, const std::vector<complexd>& C4);

    // imaginary unit
    constexpr complexd ii(0,1);

    // helper function to ensure that the 2HDM scalar sector is Z2 symmetric
    void check_Z2(const double lambda6, const double lambda7, const str calculation_name)
    {
      if (std::abs(lambda6) != 0.0 || std::abs(lambda7) != 0.0)
      {
        std::ostringstream msg;
        msg << "SpecBit error (fatal): " << calculation_name << " is only compatible with Z2 conserving models. \
        Please fix you yaml file."
            << std::endl;
        std::cerr << msg.str();
        SpecBit_error().raise(LOCAL_INFO, msg.str());
      }
    }

    // simple structure for passing around 2HDM parameters at a fixed scale
    // with short variable names so that you don't need to unwrap them
    struct ThdmSpec
    {
      // Generic basis params
      double lam1=nan, lam2=nan, lam3=nan, lam4=nan, lam5=nan, lam6=nan, lam7=nan;
      
      // Higgs basis params
      double Lam1=nan, Lam2=nan, Lam3=nan, Lam4=nan, Lam5=nan, Lam6=nan, Lam7=nan;
      
      // Physical params
      double mh=nan, mH=nan, mA=nan, mHp=nan, mG=nan, mGp=nan, v=nan, v2=nan, m122=nan, m112=nan, m222=nan;
      
      // angles
      double beta=nan, alpha=nan, tanb=nan, cosba=nan, sinba=nan;
      
      // other
      double g1=nan, g2=nan, g3=nan;

      // model type
      int model_type;
      
      // Yukawas
      std::vector<double> Ye, Yu, Yd;

      void fill_generic(const SubSpectrum& he)
      {
          lam1 = he.get(Par::dimensionless,"lambda1");
          lam2 = he.get(Par::dimensionless,"lambda2");
          lam3 = he.get(Par::dimensionless,"lambda3");
          lam4 = he.get(Par::dimensionless,"lambda4");
          lam5 = he.get(Par::dimensionless,"lambda5");
          lam6 = he.get(Par::dimensionless,"lambda6");
          lam7 = he.get(Par::dimensionless,"lambda7");
      }

      void fill_higgs(const SubSpectrum& he)
      {
          Lam1 = he.get(Par::dimensionless,"Lambda1");
          Lam2 = he.get(Par::dimensionless,"Lambda2");
          Lam3 = he.get(Par::dimensionless,"Lambda3");
          Lam4 = he.get(Par::dimensionless,"Lambda4");
          Lam5 = he.get(Par::dimensionless,"Lambda5");
          Lam6 = he.get(Par::dimensionless,"Lambda6");
          Lam7 = he.get(Par::dimensionless,"Lambda7");
      }

      void fill_physical(const SubSpectrum& he)
      {
        // needs to be mass1 to match scale of couplings
          mh = he.get(Par::mass1,"h0_1");
          mH = he.get(Par::mass1,"h0_2");
          mA = he.get(Par::mass1,"A0");
          mHp = he.get(Par::mass1,"H+");
          mG = he.get(Par::mass1,"G0");
          mGp = he.get(Par::mass1,"G+");
          v = he.get(Par::mass1,"vev");
          v2 = v*v;
          m122 = he.get(Par::mass1,"m12_2");
          m112 = he.get(Par::mass1,"m11_2");
          m222 = he.get(Par::mass1,"m22_2");
      }

      void fill_angles(const SubSpectrum& he)
      {
          beta = he.get(Par::dimensionless,"beta");
          alpha = he.get(Par::dimensionless,"alpha");
          tanb = he.get(Par::dimensionless,"tanb");
          cosba = cos(beta-alpha);
          sinba = sin(beta-alpha);
      }

      void fill_yukawas(const SubSpectrum& he)
      {
          Ye = std::vector<double>({he.get(Par::dimensionless,"Ye",1,1),he.get(Par::dimensionless,"Ye",2,2),he.get(Par::dimensionless,"Ye",3,3)});
          Yu = std::vector<double>({he.get(Par::dimensionless,"Yu",1,1),he.get(Par::dimensionless,"Yu",2,2),he.get(Par::dimensionless,"Yu",3,3)});
          Yd = std::vector<double>({he.get(Par::dimensionless,"Yd",1,1),he.get(Par::dimensionless,"Yd",2,2),he.get(Par::dimensionless,"Yd",3,3)});
          model_type = he.get(Par::dimensionless,"model_type");
          g1 = he.get(Par::dimensionless,"g1");
          g2 = he.get(Par::dimensionless,"g2");
          g3 = he.get(Par::dimensionless,"g3");
      }
    };

    // get leading-order scattering eigenvalues (with fixed ordering) (requires Z2-symmetric THDM)
    vector<complex<double>> get_LO_scattering_eigenvalues_ordered(const ThdmSpec &s)
    {
      // ensure that we have a Z2-symmetric scalar sector
      check_Z2(s.lam6, s.lam7, "get_LO_scattering_eigenvalues_ordered");

      // a00
      complex<double> a00_even_plus = 1.0 / 2.0 * (3.0 * (s.lam1 + s.lam2) + sqrt(9.0 * pow((s.lam1 - s.lam2), 2) + 4.0 * pow((2.0 * s.lam3 + s.lam4), 2)));
      complex<double> a00_even_minus = 1.0 / 2.0 * (3.0 * (s.lam1 + s.lam2) - sqrt(9.0 * pow((s.lam1 - s.lam2), 2) + 4.0 * pow((2.0 * s.lam3 + s.lam4), 2)));
      complex<double> a00_odd_plus = s.lam3 + 2.0 * s.lam4 + 3.0 * s.lam5;
      complex<double> a00_odd_minus = s.lam3 + 2.0 * s.lam4 - 3.0 * s.lam5;
      // a01
      complex<double> a01_even_plus = 1.0 / 2.0 * (s.lam1 + s.lam2 + sqrt(pow((s.lam1 - s.lam2), 2) + 4.0 * sqr(s.lam4)));
      complex<double> a01_even_minus = 1.0 / 2.0 * (s.lam1 + s.lam2 - sqrt(pow((s.lam1 - s.lam2), 2) + 4.0 * sqr(s.lam4)));
      complex<double> a01_odd_plus = s.lam3 + s.lam5;
      complex<double> a01_odd_minus = s.lam3 - s.lam5;
      // a20
      complex<double> a20_odd = s.lam3 - s.lam4;
      // a21
      complex<double> a21_even_plus = 1.0 / 2.0 * (s.lam1 + s.lam2 + sqrt(pow((s.lam1 - s.lam2), 2) + 4.0 * sqr(s.lam5)));
      complex<double> a21_even_minus = 1.0 / 2.0 * (s.lam1 + s.lam2 - sqrt(pow((s.lam1 - s.lam2), 2) + 4.0 * sqr(s.lam5)));
      complex<double> a21_odd = s.lam3 + s.lam4;

      vector<complexd> lo_eigenvalues = {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus,
              a01_even_minus, a01_odd_plus, a01_odd_minus, a20_odd, a21_even_plus, a21_even_minus, a21_odd};

      return lo_eigenvalues;
    }

    // get leading-order scattering eigenvalues (with no particular order) (supports GCP 2HDM with lam6,lam7)
    vector<complex<double>> get_LO_scattering_eigenvalues(const ThdmSpec &s)
    {
      vector<double> lambda;
      vector<complex<double>> lo_eigenvalues;

      // Scattering matrix (7a) Y=2 sigma=1
      Eigen::MatrixXcd S_21(3, 3);
      S_21(0, 0) = s.lam1;
      S_21(0, 1) = s.lam5;
      S_21(0, 2) = sqrt(2.0) * s.lam6;

      S_21(1, 0) = std::conj(s.lam5);
      S_21(1, 1) = s.lam2;
      S_21(1, 2) = sqrt(2.0) * std::conj(s.lam7);

      S_21(2, 0) = sqrt(2.0) * std::conj(s.lam6);
      S_21(2, 1) = sqrt(2.0) * s.lam7;
      S_21(2, 2) = s.lam3 + s.lam4;

      Eigen::ComplexEigenSolver<Eigen::MatrixXcd> eigensolver_S_21(S_21);
      Eigen::VectorXcd eigenvalues_S_21 = eigensolver_S_21.eigenvalues();
      lo_eigenvalues.push_back((eigenvalues_S_21(0)));
      lo_eigenvalues.push_back((eigenvalues_S_21(1)));
      lo_eigenvalues.push_back((eigenvalues_S_21(2)));

      // Scattering matrix (7b) Y=2 sigma=0
      complex<double> S_20 = s.lam3 - s.lam4;
      lo_eigenvalues.push_back((S_20));

      // Scattering matrix (7c) Y=0 sigma=1
      Eigen::MatrixXcd S_01(4, 4);
      S_01(0, 0) = s.lam1;
      S_01(0, 1) = s.lam4;
      S_01(0, 2) = s.lam6;
      S_01(0, 3) = std::conj(s.lam6);

      S_01(1, 0) = s.lam4;
      S_01(1, 1) = s.lam2;
      S_01(1, 2) = s.lam7;
      S_01(1, 3) = std::conj(s.lam7);

      S_01(2, 0) = std::conj(s.lam6);
      S_01(2, 1) = std::conj(s.lam7);
      S_01(2, 2) = s.lam3;
      S_01(2, 3) = s.lam5;

      S_01(3, 0) = s.lam6;
      S_01(3, 1) = s.lam7;
      S_01(3, 2) = s.lam5;
      S_01(3, 3) = s.lam3;

      Eigen::ComplexEigenSolver<Eigen::MatrixXcd> eigensolver_S_01(S_01);
      Eigen::VectorXcd eigenvalues_S_01 = eigensolver_S_01.eigenvalues();
      lo_eigenvalues.push_back((eigenvalues_S_01(0)));
      lo_eigenvalues.push_back((eigenvalues_S_01(1)));
      lo_eigenvalues.push_back((eigenvalues_S_01(2)));
      lo_eigenvalues.push_back((eigenvalues_S_01(3)));

      // Scattering matrix (7d) Y=0 sigma=0
      Eigen::MatrixXcd S_00(4, 4);
      S_00(0, 0) = 3.0 * s.lam1;
      S_00(0, 1) = 2.0 * s.lam3 + s.lam4;
      S_00(0, 2) = 3.0 * s.lam6;
      S_00(0, 3) = 3.0 * std::conj(s.lam6);

      S_00(1, 0) = 2.0 * s.lam3 + s.lam4;
      S_00(1, 1) = 3.0 * s.lam2;
      S_00(1, 2) = 3.0 * s.lam7;
      S_00(1, 3) = 3.0 * std::conj(s.lam7);

      S_00(2, 0) = 3.0 * std::conj(s.lam6);
      S_00(2, 1) = 3.0 * std::conj(s.lam7);
      S_00(2, 2) = s.lam3 + 2.0 * s.lam4;
      S_00(2, 3) = 3.0 * std::conj(s.lam5);

      S_00(3, 0) = 3.0 * s.lam6;
      S_00(3, 1) = 3.0 * s.lam7;
      S_00(3, 2) = 3.0 * s.lam5;
      S_00(3, 3) = s.lam3 + 2.0 * s.lam4;

      Eigen::ComplexEigenSolver<Eigen::MatrixXcd> eigensolver_S_00(S_00);
      Eigen::VectorXcd eigenvalues_S_00 = eigensolver_S_00.eigenvalues();
      lo_eigenvalues.push_back((eigenvalues_S_00(0)));
      lo_eigenvalues.push_back((eigenvalues_S_00(1)));
      lo_eigenvalues.push_back((eigenvalues_S_00(2)));
      lo_eigenvalues.push_back((eigenvalues_S_00(3)));

      return lo_eigenvalues;
    }

    // helper function get list of energy scales, check constraint at each, and get the worst performer
    double get_worst_LL_of_all_scales(const Spectrum& spec, LL_type LL, bool is_FS_model, vector<double> scales_to_check, bool canRun)
    {
      if (!is_FS_model)
      {
        bool has_input = false;
        for (auto& x : scales_to_check)
        {
          if (x == -1.0)
          {
            has_input = true;
            break;
          }
        }
        scales_to_check.clear();
        if (has_input) scales_to_check.push_back(-1.0);
      }

      // // we always check the input scale
      // vector<double> scales_to_check = { RunScale::INPUT };

      // // also check the custom scale from the yaml file. Skip if tree level
      // if (other_scale != RunScale::NONE && other_scale != RunScale::INPUT && is_FS_model)
      //   scales_to_check.push_back(other_scale);

      // // hax !!!
      // if (other_scale != RunScale::NONE && other_scale != RunScale::INPUT && is_FS_model) 
      // {
      //   scales_to_check.clear();
      //   if (canRun) scales_to_check.push_back(other_scale);
      // }

      // // print warning if we ask for likelihood at check_other_scale but not using FlexibleSUSY model
      // if (other_scale != RunScale::NONE && other_scale != RunScale::INPUT && !is_FS_model)
      // {
      //   std::ostringstream os;
      //   os << "SpecBit warning (non-fatal): requested " << calculation_name << " at all scales. However model in use is incompatible with running to scales. Will revert to regular calculation.";
      //   SpecBit_error().raise(LOCAL_INFO, os.str());
      // }

      // get the worst performing likelihood at all scales
      double result = std::numeric_limits<double>::max();
      for (auto& scale : scales_to_check)
      {
        if (scale == RunScale::INPUT)
        {
          result = std::min(LL(spec.get_HE()), result);
        }
        else
        {
          if (!canRun) continue;
          auto he = spec.clone_HE();
          he->RunToScale(scale);
          result = std::min(LL(*he), result);
        }

        // don't waste time when it will be invalid anyway
        if (result < -1e7) break;
      }
      return result;
    }

    // helper function get list of energy scales, check constraint at each, and get the worst performer
    double get_worst_LL_of_all_scales(const Spectrum& spec, const CouplingTable& coup, LL_type2 LL, bool is_FS_model, vector<double> scales_to_check, bool canRun)
    {
      if (!is_FS_model)
      {
        bool has_input = false;
        for (auto& x : scales_to_check)
        {
          if (x == -1.0)
          {
            has_input = true;
            break;
          }
        }
        scales_to_check.clear();
        if (has_input) scales_to_check.push_back(-1.0);
      }

      // // we always check the input scale
      // vector<double> scales_to_check = { RunScale::INPUT };

      // // also check the custom scale from the yaml file. Skip if tree level
      // if (other_scale != RunScale::NONE && other_scale != RunScale::INPUT && is_FS_model)
      //   scales_to_check.push_back(other_scale);

      // // print warning if we ask for likelihood at check_other_scale but not using FlexibleSUSY model
      // if (other_scale != RunScale::NONE && other_scale != RunScale::INPUT && !is_FS_model)
      // {
      //   std::ostringstream os;
      //   os << "SpecBit warning (non-fatal): requested " << calculation_name << " at all scales. However model in use is incompatible with running to scales. Will revert to regular calculation.";
      //   SpecBit_error().raise(LOCAL_INFO, os.str());
      // }

      // get the worst performing likelihood at all scales
      double result = std::numeric_limits<double>::max();
      for (auto& scale : scales_to_check)
      {
        if (scale == RunScale::INPUT)
        {
          result = std::min(LL(spec.get_HE(), coup), result);
        }
        else
        {
          if (!canRun) continue;
          auto he = spec.clone_HE();
          auto coup2 = coup;
          he->RunToScale(scale);
          coup2.runToScale(scale);
          coup2.update();
          result = std::min(LL(*he,coup2), result);
        }

        // don't waste time when it will be invalid anyway
        if (result < -1e7) break;
      }
      return result;
    }

    // hard cutoff function
    double cutoff_hard(const double error, const double error_invalid_val, const double invalid_threshold)
    {
        (void) error_invalid_val;
        return error > eps ? invalid_threshold : 0.0;
    }

    // soft cutoff function (square)
    double cutoff_soft_square(const double error, const double error_invalid_val, const double invalid_threshold)
    {
        if (error <= eps) return 0.0;
        double sigma = error_invalid_val / sqrt(invalid_threshold);
        double result = Utils::sqr(error/sigma);

        // make sure the result is non-negligible if constraints are indeed violated
        return result + minInvalidLL;
    }

    // soft cutoff function (linear)
    double cutoff_soft_linear(const double error, const double error_invalid_val, const double invalid_threshold)
    {
        if (error <= eps) return 0.0;
        double sigma = error_invalid_val / invalid_threshold;
        double result = error/sigma;

        // make sure the result is non-negligible if constraints are indeed violated
        return result + minInvalidLL;
    }

    // rescale a vector of doubles using a vector of scales
    double rescale_components(std::vector<double>& comp, const std::vector<double>& scales, const int roots, const std::string&)
    {
      double error_sum = 0.0;
      for (int i=0; i< (int)comp.size(); ++i)
      {
        comp[i] = std::max(0.0, comp[i]);
        for (int j=0; j<roots; ++j) comp[i] = sqrt(comp[i]);
        // test_data[name + std::to_string(i)] = comp[i];
        if (!scales.empty()) comp[i] *= scales[i];
        error_sum += comp[i];
      }
      return error_sum / comp.size();
    }

    // linear shift + rescale x such that the input range transforms to the output range
    double range(double x, double x_min, double x_max, double y_min, double y_max)
    {
      return (x-x_min)*((y_max-y_min)/(x_max-x_min)) + y_min;
    }

    // clamp x within the give range
    double clamp(double x, double min, double max)
    {
      return std::max(std::min(x,max),min);
    }

    // ----- LIKELIHOOD FUNCTIONS -----

    // basic set of theory constraints that can be applied before spectrum generation (hard-cutoff)
    void basic_theory_LogLikelihood_THDM(double& result)
    {
      // get options from yaml file
      using namespace Pipes::basic_theory_LogLikelihood_THDM;
      bool only_perturbativity = runOptions->getValueOrDef<bool>(false, "only_perturbativity");
      double target_failure_rate = runOptions->getValueOrDef<double>(0.995, "target_failure_rate");
      result = 0.0;

      static int pcount = 0, icount = 0;

      ++pcount;

      double lam1 = *Param.at("lambda1");
      double lam2 = *Param.at("lambda2");
      double lam3 = *Param.at("lambda3");
      double lam4 = *Param.at("lambda4");
      double lam5 = *Param.at("lambda5");
      double lam6 = *Param.at("lambda6");
      double lam7 = *Param.at("lambda7");
      double lam_345_bar = lam3 + lam4 - std::abs(lam5);

      // -- theory limits; set larger value to weaken limits

      static double x = 0.;

      static auto startTime = std::chrono::high_resolution_clock::now();
      auto currTime = std::chrono::high_resolution_clock::now();
      double totalDur = std::chrono::duration<double>(currTime - startTime).count();

      if (totalDur > 1.00 && pcount > 100)
      {
        startTime = std::chrono::high_resolution_clock::now();

        double f = icount / (double)pcount;
        double df = f - target_failure_rate;

        pcount = 0;
        icount = 0;

        if (df > 0.002) x += 0.01;
        if (df < -0.002) x -= 0.01;
      }


      x = clamp(x, 0.0, 1.0);

      double pert_limit = 4*pi;
      double unitarity_limit = 8*pi;
      double stability_limit = 0;

      pert_limit = range(x, 0, 1, 4*pi, 12*pi);
      unitarity_limit = range(x, 0, 1, 8*pi, 16*pi);
      stability_limit = range(x, 0, 1, 0, 8*pi);

      // --- check perturbativity of lambdas

      if (abs(lam1) > pert_limit || abs(lam2) > pert_limit ||
          abs(lam3) > pert_limit || abs(lam4) > pert_limit ||
          abs(lam5) > pert_limit || abs(lam6) > pert_limit ||
          abs(lam7) > pert_limit)
      {
        result = -L_MAX;
      }

      // --- check basic stability of lam1, lam2

      if (lam1 < -stability_limit || lam2 < -stability_limit)
      {
        result = -L_MAX;
      }

      if (!only_perturbativity)
      {
        // https://arxiv.org/pdf/hep-ph/0508020 page 4
        // https://arxiv.org/pdf/hep-ph/0312374 page 5

        // double mbar = 2*(*Param.at("m12_2")) / sin(2*atan(*Param.at("tanb")));
        // double v2 = 246*246;

        // WARNING: everything below only for Z2-symmetric models
        check_Z2(lam6, lam7, "check_minimum_is_global");

        // --- check LO unitarity

        // a00
        double a00_even_plus  = 1.0 / 2.0 * (3.0 * (lam1 + lam2) + sqrt(9.0 * pow((lam1 - lam2), 2) + 4.0 * pow((2.0 * lam3 + lam4), 2)));
        double a00_even_minus = 1.0 / 2.0 * (3.0 * (lam1 + lam2) - sqrt(9.0 * pow((lam1 - lam2), 2) + 4.0 * pow((2.0 * lam3 + lam4), 2)));
        double a00_odd_plus  = lam3 + 2.0 * lam4 + 3.0 * abs(lam5);
        double a00_odd_minus = lam3 + 2.0 * lam4 - 3.0 * abs(lam5);
        // a01
        double a01_even_plus  = 1.0 / 2.0 * (lam1 + lam2 + sqrt(pow((lam1 - lam2), 2) + 4.0 * sqr(lam4)));
        double a01_even_minus = 1.0 / 2.0 * (lam1 + lam2 - sqrt(pow((lam1 - lam2), 2) + 4.0 * sqr(lam4)));
        double a01_odd_plus  = lam3 + abs(lam5);
        double a01_odd_minus = lam3 - abs(lam5);
        // a20
        double a20_odd = lam3 - lam4;
        // a21
        double a21_even_plus  = 1.0 / 2.0 * (lam1 + lam2 + sqrt(pow((lam1 - lam2), 2) + 4.0 * sqr(lam5)));
        double a21_even_minus = 1.0 / 2.0 * (lam1 + lam2 - sqrt(pow((lam1 - lam2), 2) + 4.0 * sqr(lam5)));
        double a21_odd = lam3 + lam4;

        vector<double> lo_eigenvalues = {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus,
                a01_even_minus, a01_odd_plus, a01_odd_minus, a20_odd, a21_even_plus, a21_even_minus, a21_odd};

        for (auto const &eachEig : lo_eigenvalues)
        {
          if (abs(eachEig) > unitarity_limit) result = -L_MAX;
        }

        // --- check vacuum stability

        double sqrt_lam12 = std::sqrt(std::abs(lam1 * lam2)) * sgn(lam1 * lam2);

        if (lam1 < -stability_limit ||
            lam2 < -stability_limit ||
            lam3 + sqrt_lam12 < -stability_limit ||
            lam_345_bar + sqrt_lam12 < -stability_limit)
        {
          result = -L_MAX;
        }

      }

      // count failure rate
      if (result < -0.0) ++icount;
    }

    // make sure we can run spectrum to 1 TeV (soft-cutoff)
    void runToScaleTest_LogLikelihood_THDM(double& result)
    {
      // get options from yaml file
      using namespace Pipes::runToScaleTest_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double other_scale = runOptions->getValueOrDef<double>(1000., "check_other_scale");
      double hard_cutoff = runOptions->getValueOrDef<bool>(false, "hard_cutoff");
      const Spectrum& spec = *Dep::THDM_spectrum;
      result = 0.0;
      if (!is_FS_model) return;
      if (other_scale <= 0) return;

      try
      {
        spec.clone_HE()->RunToScale(other_scale);
      }
      catch(...)
      {
        result = -5e4;
        if (hard_cutoff) result = -L_MAX;
      }

    }

    // Leading-Order S-matrix unitarity constraint (soft-cutoff)
    void LO_unitarity_LogLikelihood_THDM(double& result)
    {
      // get options from yaml file
      using namespace Pipes::LO_unitarity_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double hard_cutoff = runOptions->getValueOrDef<bool>(false, "hard_cutoff");

      vector<double> other_scale = runOptions->getValueOrDef<vector<double>>(std::vector<double>({RunScale::INPUT}), "check_other_scale");
      const Spectrum& spec = *Dep::THDM_spectrum;
      bool canRun = (*Dep::runToScaleTest_LogLikelihood_THDM == 0.0);

      // all values < 8*PI for unitarity conditions (see ivanov paper)
      constexpr double unitarity_upper_limit = 8 * pi;

      // helper to get constraint at a single scale
      auto get_LO_unitarity_LogLikelihood = [&](const SubSpectrum& he)
      {
        // get required spectrum info
        ThdmSpec s;
        s.fill_generic(he);

        // get the leading order scattering eigenvalues
        std::vector<complexd> LO_eigenvalues;

        if (abs(s.lam6) < eps && abs(s.lam7) < eps)
          LO_eigenvalues = get_LO_scattering_eigenvalues_ordered(s);
        else
          LO_eigenvalues = get_LO_scattering_eigenvalues(s);

        // calculate error for each eigenvalue
        int nEig = 12;
        std::vector<double> errors(nEig,0.0);
        for (int i=0; i<nEig; ++i)
          errors[i] = std::max(0.0, std::abs(LO_eigenvalues[i]) - unitarity_upper_limit) / unitarity_upper_limit;

        // rescale error components & get final error sum
        double error = rescale_components(errors, {}, 0, "LO-uni");
        return -cutoff_soft_square(error, 1.0, inv_LL_threshold);
      };

      // get worst performing LogLike at all scales
      result = get_worst_LL_of_all_scales(spec, get_LO_unitarity_LogLikelihood, is_FS_model, other_scale, canRun);
      if (hard_cutoff && result < -0.0) result = -L_MAX;

      // test_data["LO"] = -result;
    }

    // simple lambdas perturbativity constraint (soft-cutoff)
    void perturbativity_lambdas_LogLikelihood_THDM(double& result)
    {
      // Reference
      // https://arxiv.org/pdf/1609.01290 page 4

      // get options from yaml file
      using namespace Pipes::perturbativity_lambdas_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double hard_cutoff = runOptions->getValueOrDef<bool>(false, "hard_cutoff");
      vector<double> other_scale = runOptions->getValueOrDef<vector<double>>(std::vector<double>({RunScale::INPUT}), "check_other_scale");
      const Spectrum& spec = *Dep::THDM_spectrum;
      bool canRun = (*Dep::runToScaleTest_LogLikelihood_THDM == 0.0);

      // helper to get constraint at a single scale
      auto get_simple_perturbativity_LogLikelihood = [&](const SubSpectrum& he)
      {
        // get required spectrum info
        ThdmSpec s;
        s.fill_generic(he);

        // check lambdai (generic couplings)
        // all values < 4*PI for perturbativity conditions
        const double perturbativity_upper_limit = 4 * pi;
        double error = 0.0;
        vector<double> lambda = {s.lam1, s.lam2, s.lam3, s.lam4, s.lam5, s.lam6, s.lam7};
        // loop over all lambdas
        for (auto const &each_lambda : lambda)
        {
          if (abs(each_lambda) > perturbativity_upper_limit)
            error += abs(each_lambda) - perturbativity_upper_limit;
        }

        return -cutoff_soft_square(error, 71, inv_LL_threshold);
      };

      // get worst performing LogLike at all scales
      result = get_worst_LL_of_all_scales(spec, get_simple_perturbativity_LogLikelihood, is_FS_model, other_scale, canRun);
      if (hard_cutoff && result < -0.0) result = -L_MAX;
    }

    // full perturbativity constraint (soft-cutoff)
    void perturbativity_LogLikelihood_THDM(double& result)
    {
      // get options from yaml file
      using namespace Pipes::perturbativity_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double hard_cutoff = runOptions->getValueOrDef<bool>(false, "hard_cutoff");
      vector<double> other_scale = runOptions->getValueOrDef<vector<double>>(std::vector<double>({RunScale::INPUT}), "check_other_scale");
      bool skipCubicCouplings = runOptions->getValueOrDef<bool>(true, "skipCubicCouplings");
      bool skipGoldstoneCouplings = runOptions->getValueOrDef<bool>(false, "skipGoldstoneCouplings");
      const Spectrum& spec = *Dep::THDM_spectrum;
      const CouplingTable& coupl = *Dep::couplingtable_THDM;
      bool canRun = (*Dep::runToScaleTest_LogLikelihood_THDM == 0.0);

      // helper to get constraint at a single scale
      auto get_perturbativity_LogLikelihood = [&](const SubSpectrum&, const CouplingTable& coup)
      {
        // all values < 4*PI for perturbativity conditions
        constexpr double perturbativity_upper_limit = 4*pi;
        double error = 0.0;

        for (auto& pair : coup.table)
        {
          if (skipCubicCouplings && pair.first.size() != 4) continue;
          if (skipGoldstoneCouplings && pair.first[0][0] == 'G') continue;
          if (skipGoldstoneCouplings && pair.first[1][0] == 'G') continue;
          if (skipGoldstoneCouplings && pair.first[2][0] == 'G') continue;
          if (pair.first.size() > 3) if (skipGoldstoneCouplings && pair.first[3][0] == 'G') continue;
          error += std::max(0.0, std::abs(pair.second) - perturbativity_upper_limit) / perturbativity_upper_limit;
        }

        // rescale error components & get final error sum
        return -cutoff_soft_square(error, 100., inv_LL_threshold);
      };

      // get worst performing LogLike at all scales
      result = get_worst_LL_of_all_scales(spec, coupl, get_perturbativity_LogLikelihood, is_FS_model, other_scale, canRun);
      if (hard_cutoff && result < -0.0) result = -L_MAX;

      // test_data["pert"] = -result;
    }

    // simple yukawa perturbativity constraint (soft-cutoff)
    void perturbativity_yukawas_LogLikelihood_THDM(double& result)
    {
      // Reference
      // https://arxiv.org/pdf/1609.01290 page 4

      // get options from yaml file
      using namespace Pipes::perturbativity_yukawas_LogLikelihood_THDM;
      SMInputs sminputs = *Dep::SMINPUTS;
      const Spectrum& spec = *Dep::THDM_spectrum;
      bool canRun = (*Dep::runToScaleTest_LogLikelihood_THDM == 0.0);
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double hard_cutoff = runOptions->getValueOrDef<bool>(false, "hard_cutoff");
      vector<double> other_scale = runOptions->getValueOrDef<vector<double>>(std::vector<double>({RunScale::INPUT}), "check_other_scale");

      auto get_perturbativity_LogLikelihood = [&](const SubSpectrum& he)
      {
        // get list of all Yukawas
        std::vector<double> Yukawas; Yukawas.reserve(3*3*3);
        for (int i=1; i<=3; ++i)
        {
          for (int j=1; j<=3; ++j)
          {
            // if (!(i==3 && j==3))
            Yukawas.push_back(he.get(Par::dimensionless, "Yu", i, j));
            Yukawas.push_back(he.get(Par::dimensionless, "Yd", i, j));
            Yukawas.push_back(he.get(Par::dimensionless, "Ye", i, j));
          }
        }

        // constraint for each Yukawa

        // double Ylim = sqrt(4*pi)/sqrt(1+tanb*tanb);
        double Ylim = sqrt(4*pi);
        double error = 0.0;

      for (auto & each_yukawa : Yukawas)
      {
          error += std::max(0.0, abs(each_yukawa) - Ylim);
        }

        // // Apply softer bound for top Yukawa coupling

        // double Yu2tt = he->get(Par::dimensionless, "Yu", 3, 3);
        // const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
        // const double mT = Dep::SMINPUTS->mT;
        // double tanb = he->get(Par::dimensionless,"tanb");
        // error += max(0.0, abs(Yu2tt) - ((sqrt(4*pi)+((sqrt(2)*tanb*mT)/v))/(sqrt(1+tanb*tanb))));

        // get result

        return -cutoff_soft_square(sqrt(std::max(0.0,error)), 141, inv_LL_threshold);

      };

      // get worst performing LogLike at all scales
      result = get_worst_LL_of_all_scales(spec, get_perturbativity_LogLikelihood, is_FS_model, other_scale, canRun);
      if (hard_cutoff && result < -0.0) result = -L_MAX;
    }

    // vacuum stability + meta-stability constraint (soft-cutoff)
    void stability_LogLikelihood_THDM(double& result)
    {
      // get options from yaml file
      using namespace Pipes::stability_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      vector<double> other_scale = runOptions->getValueOrDef<vector<double>>(std::vector<double>({RunScale::INPUT}), "check_other_scale");
      bool checkMeta = runOptions->getValueOrDef<bool>(false, "check_metastability");
      const Spectrum& spec = *Dep::THDM_spectrum;
      bool canRun = (*Dep::runToScaleTest_LogLikelihood_THDM == 0.0);

      // helper to get constraint at a single scale
      auto get_stability_LogLikelihood = [&](const SubSpectrum& he)
      {
        // Reference: https://arxiv.org/abs/hep-ph/0605142 (A.2)
        //            https://arxiv.org/abs/0902.0851 (also see THDMC code)

        // see also (original reference)
        // https://journals.aps.org/prd/pdf/10.1103/PhysRevD.18.2574

        // WARNING: the conditions for the GCP-2HDM with lam6,7 != 0 are incomplete

        ThdmSpec s;
        s.fill_generic(he);
        s.fill_angles(he);
        s.fill_physical(he);

        // store each vacuum stability error here
        int nStab = 10;
        std::vector<double> errors(nStab,0.0);

        // constraint for gamma = pi/2
        errors[0] = std::max(0.0, -s.lam1);

        // constraint for rho = 0
        errors[1] = std::max(0.0, -s.lam2);

        // Note: technically there is no abs here, but lam1 & lam2 are already constrained to be positive above
        // we add this to avoid NaN and help guide scanner (we could just throw invalid point, but that isn't very helpful)
        double sqrt_lam12 = std::sqrt(std::abs(s.lam1 * s.lam2)) * sgn(s.lam1 * s.lam2);

        // constraint for gamma = 0
        errors[2] = std::max(0.0, -s.lam3 - sqrt_lam12);

        // -- remaining conditions for a Z2-symmetric scalar potential
        if (abs(s.lam6) < 1e-12 && abs(s.lam7) < 1e-12)
        {
          // constraint for cos(theta) = 0
          errors[3] = std::max(0.0, -s.lam3 - s.lam4 + abs(s.lam5) - sqrt_lam12);
        }

        // -- remaining conditions for the General CP-conserving 2HDM
        else
        {
          // constraint for cos(theta) = 0
          errors[3] = std::max(0.0, -s.lam3 - s.lam4 + s.lam5 - sqrt_lam12);

          // a calculation needed for the conditions below
          double calc = (1./2.)*(-s.lam4*s.lam3*s.lam3+s.lam4*s.lam2*s.lam1-s.lam3*s.lam3*s.lam5+s.lam2*s.lam1*s.lam5-2*s.lam7*s.lam7*s.lam1+4*s.lam6*s.lam7*s.lam3-2*s.lam2*s.lam6*s.lam6)/(s.lam4*s.lam1+s.lam4*s.lam2-2*s.lam4*s.lam3+s.lam1*s.lam5-2*s.lam3*s.lam5+s.lam2*s.lam5-2*s.lam6*s.lam6-2*s.lam7*s.lam7+4*s.lam6*s.lam7);

          // cos(theta) = +-1 AND abs(rho) <= 1 AND 0<gamma<pi/2 (first gamma solution)
          double rho,gamma,cosg;
          gamma = acos(sqrt((4*s.lam6*s.lam7-2*s.lam4*s.lam3+s.lam4*s.lam2+s.lam4*s.lam1-2*s.lam3*s.lam5+s.lam2*s.lam5+s.lam1*s.lam5-2*s.lam6*s.lam6-2*s.lam7*s.lam7)*(-2*s.lam7*s.lam7+s.lam2*s.lam5+s.lam4*s.lam2-s.lam3*s.lam5-s.lam4*s.lam3+2*s.lam6*s.lam7))/(4*s.lam6*s.lam7-2*s.lam4*s.lam3+s.lam4*s.lam2+s.lam4*s.lam1-2*s.lam3*s.lam5+s.lam2*s.lam5+s.lam1*s.lam5-2*s.lam6*s.lam6-2*s.lam7*s.lam7));
          cosg  = cos(gamma);
          rho   = sin(gamma)*(s.lam7-cosg*cosg*s.lam7+s.lam6*cosg*cosg)/(cosg*(-s.lam5-s.lam4+cosg*cosg*s.lam4+cosg*cosg*s.lam5));

          if (abs(rho) <= 1.0 && gamma >= 0.0 && gamma <= pi/2.)
          {
            errors[4] = std::max(0.0, -calc);
          }

          // cos(theta) = +-1 AND abs(rho) <= 1 AND 0<gamma<pi/2 (second gamma solution)
          gamma = pi-gamma;
          cosg  = cos(gamma);
          rho   = sin(gamma)*(s.lam7-cosg*cosg*s.lam7+s.lam6*cosg*cosg)/(cosg*(-s.lam5-s.lam4+cosg*cosg*s.lam4+cosg*cosg*s.lam5));

          if (abs(rho) <= 1.0 && gamma >= 0.0 && gamma <= pi/2.)
          {
            errors[5] = std::max(0.0, -calc);
          }

          // a calculation needed for the conditions below
          double calc2 = (1./2.)*(s.lam1*s.lam2*s.lam5-s.lam1*s.lam7*s.lam7-s.lam5*s.lam5*s.lam5+2*s.lam5*s.lam5*s.lam4+2*s.lam5*s.lam5*s.lam3-s.lam5*s.lam4*s.lam4-2*s.lam5*s.lam6*s.lam7-s.lam5*s.lam3*s.lam3-2*s.lam5*s.lam4*s.lam3-s.lam6*s.lam6*s.lam2+2*s.lam6*s.lam7*s.lam3+2*s.lam6*s.lam7*s.lam4)/(s.lam1*s.lam5+2*s.lam6*s.lam7-2*s.lam3*s.lam5+s.lam2*s.lam5-2*s.lam5*s.lam4-s.lam6*s.lam6-s.lam7*s.lam7+2*s.lam5*s.lam5);

          // rho=1 AND abs(ct) <= 1 AND abs(gamma) <= pi/2
          double ct = (1./2.)*(-s.lam6*s.lam3-s.lam6*s.lam4+s.lam6*s.lam2+s.lam5*s.lam6+s.lam7*s.lam1-s.lam7*s.lam3-s.lam7*s.lam4+s.lam7*s.lam5)/sqrt((-s.lam3*s.lam5-s.lam5*s.lam4+s.lam2*s.lam5+s.lam5*s.lam5+s.lam6*s.lam7-s.lam7*s.lam7)*(s.lam1*s.lam5+s.lam6*s.lam7-s.lam3*s.lam5+s.lam5*s.lam5-s.lam5*s.lam4-s.lam6*s.lam6));
          gamma     = atan(sqrt((-s.lam3*s.lam5-s.lam5*s.lam4+s.lam2*s.lam5+s.lam5*s.lam5+s.lam6*s.lam7-s.lam7*s.lam7)*(s.lam1*s.lam5+s.lam6*s.lam7-s.lam3*s.lam5+s.lam5*s.lam5-s.lam5*s.lam4-s.lam6*s.lam6))/(-s.lam3*s.lam5-s.lam5*s.lam4+s.lam2*s.lam5+s.lam5*s.lam5+s.lam6*s.lam7-s.lam7*s.lam7));

          if (abs(ct) <= 1.0 && abs(gamma) <= pi/2.)
          {
            errors[6] = std::max(0.0, -calc2);
          }

          // rho=1 and ct=+1
          // TODO: don't have an analytical form for these...
          errors[7] = 0;
          errors[8] = 0;
        }

        // check meta-stability (only working for Z2-symmetric models for now)
        if (checkMeta && (abs(he.GetScale() - 91.1876) < 1. || !is_FS_model)) // hax !!!
        {
          // Reference: https://arxiv.org/abs/1303.5098

          check_Z2(s.lam6, s.lam7, "check_minimum_is_global");

          // again, lam1 & lam2 are constrained to be positive by vacuum stability, so it is safe
          // to take abs. We could just throw invalid point, but this is better for guiding the scanner
          double rl1 = sgn(s.lam1) * std::sqrt(std::abs(s.lam1));
          double rl2 = sgn(s.lam2) * std::sqrt(std::abs(s.lam2));
          double rrl1l2 = sgn(rl1*rl2) * std::sqrt(std::abs(rl1*rl2));

          // re-scaling things by arbitrary constants to improve scanner performance
          double m122 = s.m122 / s.v2, m112 = s.m112 / s.v2, m222 = s.m222 / s.v2;

          // this has been slightly rearranged for better scanner performance
          double discriminant = sgn(s.lam2) * sgn(m122) * (m112*rl2 - m222*rl1) * (s.tanb * rl2 - rrl1l2);

          // // old version
          // double k2 = std::sqrt(std::abs(s.lam1 / s.lam2)) * sgn(s.lam1 / s.lam2);
          // double k = std::sqrt(std::abs(k2)) * sgn(k2);
          // double discriminant = s.m122 * (s.m112 - k2 * s.m222) * (s.tanb - k);

          if (std::abs(s.lam1) < 1e-50) invalid_point().raise("lam1 too close to zero");
          if (std::abs(s.lam2) < 1e-50) invalid_point().raise("lam2 too close to zero");
          if (std::abs(m122) < 1e-50) invalid_point().raise("m122/v2 too close to zero");
          if (std::isnan(discriminant)) invalid_point().raise("discriminant is NaN");

          // D>0 is a necessary & sufficient condition to have a global minimum
          if (discriminant >= -0.0) errors[9] = 0.0;
          // use log here to fix the horrible distribution and improve scanner performance
          else  errors[9] = sqrt(sqrt(sqrt(-discriminant)));
        }

        // vacuum stability constraints have order(lambda), so divide by 4pi to get order(1)
        for (int i=0; i<9; ++i) errors[i] /= 4*pi;

        // rescale error components & get final error sum
        std::vector<double> rescale = { 5.0, 1.4, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.09 };
        double error = rescale_components(errors, rescale, 0, "v");
        double result = -20*cutoff_soft_square(error, 1.0, inv_LL_threshold);
        return result;
      };

      // get worst performing LogLike at all scales
      result = get_worst_LL_of_all_scales(spec, get_stability_LogLikelihood, is_FS_model, other_scale, canRun);

      // test_data["stab"] = -result;
    }

    // checks that the mass corrections to h0,H0,A0,Hp are perturbative (soft-cutoff)
    void scalar_mass_corrections_LogLikelihood_THDM(double& result)
    {
      // get options from yaml file
      using namespace Pipes::scalar_mass_corrections_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double hard_cutoff = runOptions->getValueOrDef<bool>(false, "hard_cutoff");
      vector<double> other_scale = runOptions->getValueOrDef<vector<double>>(std::vector<double>({RunScale::INPUT}), "check_other_scale");
      const Spectrum& spec = *Dep::THDM_spectrum;
      bool canRun = (*Dep::runToScaleTest_LogLikelihood_THDM == 0.0);

      // helper to get constraint at a single scale
      auto get_scalar_mass_correction_LogLikelihood = [&](const SubSpectrum& he)
      {
        int nScalars = 4;
        std::vector<std::string> scalar_names = {"h0_1", "h0_2", "A0", "H+"};
        std::vector<double> errors(nScalars,0.0);

        for (int i=0; i<nScalars; ++i)
        {
          double mass_running = he.get(Par::mass1, scalar_names[i]);
          double mass_pole = he.get(Par::Pole_Mass, scalar_names[i]);
          double mass_splitting = abs(mass_running - mass_pole);
          errors[i] = std::max(0.0, mass_splitting/mass_running - 0.5);
        }

        // rescale error components & get final error sum
        double error = rescale_components(errors, {0.2, 0.2, 0.25, 0.5}, 2, "c");
        double result = -5*cutoff_soft_square(error, 1.0, inv_LL_threshold);
        return result;
      };

      // get worst performing LogLike at all scales
      result = get_worst_LL_of_all_scales(spec, get_scalar_mass_correction_LogLikelihood, is_FS_model, other_scale, canRun);
      if (hard_cutoff && result < -0.0) result = -L_MAX;

      // test_data["corr"] = -result;
    }

    // guides scanner towards mh = 125 GeV. Use to improve performance of HiggsSignals (soft-cutoff)
    void higgs_exp_mass_LogLikelihood_THDM(double& result)
    {
      // get options from yaml file
      using namespace Pipes::higgs_exp_mass_LogLikelihood_THDM;
      double hard_cutoff = runOptions->getValueOrDef<bool>(false, "hard_cutoff");
      double higgs_mass_uncertainty = runOptions->getValueOrDef<double>(2.5, "higgs_mass_uncertainty");
      double valid_range = runOptions->getValueOrDef<double>(60, "valid_range");
      const Spectrum &spec = *Dep::THDM_spectrum;

      // error based on dist from exp value; no penalty if within 'higgs_mass_uncertainty'
      double mh_pole = spec.get_HE().get(Par::Pole_Mass, *Dep::SM_like_scalar);
      double mh_exp = 125.15;
      double error = std::max(0.0, std::abs(mh_pole - mh_exp) - higgs_mass_uncertainty) / valid_range;
      result = -4e-3*cutoff_soft_square(error, 1.0, inv_LL_threshold);
      if (hard_cutoff && result < -0.0) result = -L_MAX;
      // test_data["higgsMass"] = -result; // delete me
    }

    // only keeps points that correspond to hidden Higgs OR regular Higgs scenario (hard-cutoff)
    void higgs_scenario_LogLikelihood_THDM(double& result)
    {
      // get options from yaml file
      using namespace Pipes::higgs_scenario_LogLikelihood_THDM;
      bool hidden_higgs_scenario = runOptions->getValueOrDef<bool>(false, "hidden_higgs_scenario");
      const Spectrum& spec = *Dep::THDM_spectrum;

      // get SM-like and non-SM-like CP-even scalars
      double mh_pole = spec.get_HE().get(Par::Pole_Mass, *Dep::SM_like_scalar);
      double mH_pole = spec.get_HE().get(Par::Pole_Mass, *Dep::additional_scalar);

      // hidden-Higgs scenario -> SM Higgs heavier than other higgs
      if (mh_pole < mH_pole && hidden_higgs_scenario) result = -L_MAX;
      // regular-Higgs scenario -> SM Higgs lighter than other higgs
      else if (mh_pole > mH_pole && !hidden_higgs_scenario) result = -L_MAX;
      else result = 0;
    }

    // ----- STRUCTS NLO UNITARITY -----

    enum wavefunction_renorm_type
    {
      wpwm,
      zz,
      wpHm,
      Hpwm,
      zA,
      Az,
      hh,
      HH,
      hH,
      Hh,
      HpHm,
      AA,
    };

    struct B0_integration_vars
    {
      double x;
      double p2;
      double m12;
      double m22;
      double mu2;
      double z_plus;
    };

    struct wavefunction_renorm_vars
    {
      const ThdmSpec& s;
      const std::vector<complexd>& C3;
      const std::vector<complexd>& C4;
      wavefunction_renorm_vars(const ThdmSpec& s, const std::vector<complexd>& C3, const std::vector<complexd>& C4) : s(s), C3(C3), C4(C4) {}
    };

    //  ----- wavefunction corrections to beta functions -----

    double A0_bar(const double m2)
    {
      const double MZ = 91.15349; // get this from FS
      double mu2 = pow(MZ, 2);
      return m2 * (-log(m2 / mu2) + 1.0);
    }

    double B0_bar_integration_real(const double x, const B0_integration_vars* p)
    {
      double re = (p->p2 * x * x - x * (p->p2 - p->m12 - p->m22) + p->m22) / p->mu2;
      double im = -p->z_plus / p->mu2;
      return log(sqrt(re * re + im * im));
    }

    double B0_bar_integration_imag(const double x, const B0_integration_vars* p)
    {
      double re = (p->p2 * x * x - x * (p->p2 - p->m12 - p->m22) + p->m22) / p->mu2;
      double im = -p->z_plus / p->mu2;
      return atan(im / re);
    }

    complexd B0_bar(const double p2, const double m12, const double m22)
    {
      const double MZ = 91.15349; // get this from FS
      double mu2 = pow(MZ, 2);
      double z_plus = 1E-10;
      double result_real, error_real, result_imag, error_imag;
      // real
      gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
      gsl_function B0_bar_int;
      B0_bar_int.function = reinterpret_cast<gsl_funn>(&B0_bar_integration_real);
      B0_integration_vars input_pars;
      input_pars.p2 = p2;
      input_pars.m12 = m12;
      input_pars.m22 = m22;
      input_pars.mu2 = mu2;
      input_pars.z_plus = z_plus;
      B0_bar_int.params = &input_pars;
      gsl_integration_qag(&B0_bar_int, 0, 1.0, 1e-7, 1e-7, 1000, 1, w, &result_real, &error_real);
      gsl_integration_workspace_free(w);
      // imag
      gsl_integration_workspace *w_imag = gsl_integration_workspace_alloc(1000);
      gsl_function B0_bar_int_imag;
      B0_bar_int_imag.function = reinterpret_cast<gsl_funn>(&B0_bar_integration_imag);
      B0_bar_int_imag.params = &input_pars;
      gsl_integration_qag(&B0_bar_int_imag, 0, 1.0, 1e-7, 1e-7, 1000, 1, w_imag, &result_imag, &error_imag);
      gsl_integration_workspace_free(w_imag);

      return (result_real + ii * result_imag);
    }

    double mZw2(const ThdmSpec &s)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), sb = sin(s.beta), cb = cos(s.beta), s2b2a = sin(2.0 * s.beta - 2.0 * s.alpha), t2b = tan(2.0 * s.beta);
      return 1.0 / 2.0 * (mh2 * sqr(s.sinba) + mH2 * sqr(s.cosba) + (mh2 - mH2) * s2b2a * (1.0 / t2b) - 2.0 * s.m122 * (1.0 / sb) * (1.0 / cb));
    }

    // ----- Self energies and wavefunction renormalizations -----

    complexd Pi_tilde_wpwm(const double p2, const ThdmSpec &s, const std::vector<complexd>& C3, const std::vector<complexd>&)
    {

      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      complexd Pi = sqr(C3[1]) * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += sqr(C3[3]) * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += sqr(C3[5]) * (B0_bar(p2, mC2, mh2) - B0_bar(0., mC2, mh2));
      Pi += sqr(C3[7]) * (B0_bar(p2, mC2, mH2) - B0_bar(0., mC2, mH2));
      Pi += C3[9] * std::conj(C3[9]) * (B0_bar(p2, mC2, mA2) - B0_bar(0., mC2, mA2));
      return -1.0 / (16.0 * sqr(pi)) * Pi;
    }

    complexd Pi_tilde_zz(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>&)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA);
      complexd Pi = sqr(C3[2]) * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += sqr(C3[4]) * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += sqr(C3[6]) * (B0_bar(p2, mA2, mh2) - B0_bar(0., mA2, mh2));
      Pi += sqr(C3[8]) * (B0_bar(p2, mA2, mH2) - B0_bar(0., mA2, mH2));
      return -1.0 / (16.0 * sqr(pi)) * Pi;
    }

    complexd Pi_tilde_wpHm(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>&)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mC2 = sqr(s.mHp);
      complexd Pi = C3[1] * C3[5] * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += C3[3] * C3[7] * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += C3[5] * C3[10] * (B0_bar(p2, mC2, mh2) - B0_bar(0., mC2, mh2));
      Pi += C3[7] * C3[12] * (B0_bar(p2, mC2, mH2) - B0_bar(0., mC2, mH2));
      return -1.0 / (16.0 * sqr(pi)) * Pi;
    }

    complexd Pi_tilde_zA(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>&)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA);
      complexd Pi = C3[2] * C3[6] * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += C3[4] * C3[8] * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += C3[6] * C3[11] * (B0_bar(p2, mA2, mh2) - B0_bar(0., mA2, mh2));
      Pi += C3[8] * C3[13] * (B0_bar(p2, mA2, mH2) - B0_bar(0., mA2, mH2));
      return -1.0 / (16.0 * sqr(pi)) * Pi;
    }

    complexd Pi_zz(const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (C4[1] * A0_bar(mh2) + C4[2] * A0_bar(mH2) + 2.0 * C4[3] * A0_bar(mC2) + C4[4] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[2]) * B0_bar(0., 0., mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[4]) * B0_bar(0., 0., mH2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[6]) * B0_bar(0., mA2, mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[8]) * B0_bar(0., mA2, mH2);
      return Pi;
    }

    complexd Pi_zA(const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (C4[5] * A0_bar(mh2) + C4[6] * A0_bar(mH2) + 2.0 * C4[7] * A0_bar(mC2) + C4[8] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * sqr(pi)) * C3[2] * C3[6] * B0_bar(0., 0., mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * C3[4] * C3[8] * B0_bar(0., 0., mH2);
      Pi += -1.0 / (16.0 * sqr(pi)) * C3[6] * C3[11] * B0_bar(0., mA2, mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * C3[8] * C3[13] * B0_bar(0., mA2, mH2);
      return Pi;
    }

    complexd Pi_tilde_hh(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      const double sba = sin(s.beta - s.alpha), cba = abs(cos(s.beta - s.alpha));
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (2.0 * C4[9] * A0_bar(mC2) + C4[10] * A0_bar(mA2) + C4[15] * A0_bar(mh2) + C4[17] * A0_bar(mH2));
      Pi += -1.0 / (32.0 * sqr(pi)) * (2.0 * sqr(C3[1]) + sqr(C3[2])) * B0_bar(p2, 0, 0);
      Pi += -1.0 / (32.0 * sqr(pi)) * 4.0 * sqr(C3[5]) * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[6]) * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[10]) * B0_bar(p2, mC2, mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[11]) * B0_bar(p2, mA2, mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[14]) * B0_bar(p2, mh2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[15]) * B0_bar(p2, mH2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[16]) * B0_bar(p2, mH2, mH2);
      Pi += -sqr(sba) * Pi_zz(s,C3,C4) - 2.0 * sba * cba * Pi_zA(s,C3,C4) + (Z_w(s,C3,C4) - 1.0) * (mh2 + mZw2(s) * sqr(cba));
      return Pi;
    }

    complexd Pi_tilde_HH(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      const double sba = sin(s.beta - s.alpha), cba = abs(cos(s.beta - s.alpha));
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (2.0 * C4[11] * A0_bar(mC2) + C4[12] * A0_bar(mA2) + C4[17] * A0_bar(mh2) + C4[19] * A0_bar(mH2));
      Pi += -1.0 / (32.0 * sqr(pi)) * (2.0 * sqr(C3[3]) + sqr(C3[4])) * B0_bar(p2, 0, 0);
      Pi += -1.0 / (32.0 * sqr(pi)) * 4.0 * sqr(C3[7]) * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[8]) * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[12]) * B0_bar(p2, mC2, mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[13]) * B0_bar(p2, mA2, mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[15]) * B0_bar(p2, mh2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[16]) * B0_bar(p2, mH2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[17]) * B0_bar(p2, mH2, mH2);
      Pi += -sqr(cba) * Pi_zz(s,C3,C4) + 2.0 * sba * cba * Pi_zA(s,C3,C4) + (Z_w(s,C3,C4) - 1.0) * (mH2 + mZw2(s) * sqr(sba));
      return Pi;
    }

    complexd Pi_tilde_hH(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      const double sba = sin(s.beta - s.alpha), cba = abs(cos(s.beta - s.alpha));
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (2.0 * C4[13] * A0_bar(mC2) + C4[14] * A0_bar(mA2) + C4[16] * A0_bar(mh2) + C4[18] * A0_bar(mH2));
      Pi += -1.0 / (32.0 * sqr(pi)) * (2.0 * C3[1] * C3[3] + C3[2] * C3[4]) * B0_bar(p2, 0, 0);
      Pi += -1.0 / (32.0 * sqr(pi)) * 4.0 * C3[5] * C3[7] * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * C3[6] * C3[8] * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * C3[10] * C3[12] * B0_bar(p2, mC2, mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * C3[11] * C3[13] * B0_bar(p2, mA2, mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * C3[14] * C3[15] * B0_bar(p2, mh2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * C3[15] * C3[16] * B0_bar(p2, mH2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * C3[16] * C3[17] * B0_bar(p2, mH2, mH2);
      Pi += -sba * cba * Pi_zz(s,C3,C4) - (sqr(cba) - sqr(sba)) * Pi_zA(s,C3,C4) - (Z_w(s,C3,C4) - 1.0) * (mZw2(s) * sba * cba);
      return Pi;
    }

    complexd Pi_tilde_HpHm(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (C4[9] * A0_bar(mh2) + C4[11] * A0_bar(mH2) + 2.0 * C4[20] * A0_bar(mC2) + C4[21] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[5]) * B0_bar(p2, 0., mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[7]) * B0_bar(p2, 0., mH2);
      Pi += -1.0 / (16.0 * sqr(pi)) * std::conj(C3[9]) * C3[9] * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[10]) * B0_bar(p2, mC2, mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[12]) * B0_bar(p2, mC2, mH2);
      Pi += (Z_w(s,C3,C4) - 1.0) * (mC2 + mZw2(s));
      return Pi;
    }

    complexd Pi_tilde_AA(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (C4[10] * A0_bar(mh2) + C4[12] * A0_bar(mH2) + 2.0 * C4[21] * A0_bar(mC2) + C4[22] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[6]) * B0_bar(p2, 0., mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[8]) * B0_bar(p2, 0., mH2);
      Pi += -1.0 / (16.0 * sqr(pi)) * 2.0 * std::conj(C3[9]) * C3[9] * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[11]) * B0_bar(p2, mA2, mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[13]) * B0_bar(p2, mA2, mH2);
      Pi += (Z_w(s,C3,C4) - 1.0) * (mA2 + mZw2(s));
      return Pi;
    }

    // ----- helpers to get real/imag self-energy -----

    double Pi_tilde_wpwm_re(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_wpwm(p2, p->s, p->C3, p->C4).real();
    }
    double Pi_tilde_wpwm_im(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_wpwm(p2, p->s, p->C3, p->C4).imag();
    }
    double Pi_tilde_zz_re(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_zz(p2, p->s, p->C3, p->C4).real();
    }
    double Pi_tilde_zz_im(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_zz(p2, p->s, p->C3, p->C4).imag();
    }
    double Pi_tilde_hh_re(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_hh(p2, p->s, p->C3, p->C4).real();
    }
    double Pi_tilde_hh_im(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_hh(p2, p->s, p->C3, p->C4).imag();
    }
    double Pi_tilde_HH_re(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_HH(p2, p->s, p->C3, p->C4).real();
    }
    double Pi_tilde_HH_im(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_HH(p2, p->s, p->C3, p->C4).imag();
    }
    double Pi_tilde_HpHm_re(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_HpHm(p2, p->s, p->C3, p->C4).real();
    }
    double Pi_tilde_HpHm_im(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_HpHm(p2, p->s, p->C3, p->C4).imag();
    }
    double Pi_tilde_AA_re(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_AA(p2, p->s, p->C3, p->C4).real();
    }
    double Pi_tilde_AA_im(double p2, const wavefunction_renorm_vars* p)
    {
      return Pi_tilde_AA(p2, p->s, p->C3, p->C4).imag();
    }

    complexd z_ii(const wavefunction_renorm_type type, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      wavefunction_renorm_vars params { s, C3, C4 };
      gsl_function F_re;
      gsl_function F_im;
      F_re.params = &params;
      F_im.params = &params;
      double result_re, result_im, abserr_re, abserr_im;
      double m_in = 0.0;

      switch (type)
      {
      case wpwm:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_wpwm_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_wpwm_im);
        m_in = s.mGp;
        break;
      case zz:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_zz_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_zz_im);
        m_in = s.mG;
        break;
      case hh:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_hh_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_hh_im);
        m_in = s.mh;
        break;
      case HH:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_HH_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_HH_im);
        m_in = s.mH;
        break;
      case HpHm:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_HpHm_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_HpHm_im);
        m_in = s.mHp;
        break;
      case AA:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_AA_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_AA_im);
        m_in = s.mA;
        break;
      default:
        std::cerr << "WARNING: Unrecognized wavefunction renormalization particle pair sent to z_ij function. Returning 0." << std::endl;
        return 0.0;
      }
      gsl_deriv_central(&F_re, pow(m_in, 2), 1e-8, &result_re, &abserr_re);
      gsl_deriv_central(&F_im, pow(m_in, 2), 1e-8, &result_im, &abserr_im);
      const complexd Z_ii = 1.0 + 0.5 * (result_re + ii * result_im);
      return 16.0 * sqr(pi) * (Z_ii - 1.0);
    }

    complexd z_ij(const wavefunction_renorm_type type, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      complexd z_ij = 0.0;
      double m1 = 0.0, m2 = 0.0;

      switch (type)
      {
      case wpHm:
        m1 = s.mGp;
        m2 = s.mHp;
        z_ij = Pi_tilde_wpHm(m1, s, C3, C4);
        break;
      case zA:
        m1 = s.mG;
        m2 = s.mA;
        z_ij = Pi_tilde_zA(m1, s, C3, C4);
        break;
      case hH:
        m1 = s.mh;
        m2 = s.mH;
        z_ij = Pi_tilde_hH(m1, s, C3, C4);
        break;
      case Hpwm:
        m1 = s.mHp;
        m2 = s.mGp;
        z_ij = Pi_tilde_wpHm(m1, s, C3, C4);
        break;
      case Az:
        m1 = s.mA;
        m2 = s.mG;
        z_ij = Pi_tilde_zA(m1, s, C3, C4);
        break;
      case Hh:
        m1 = s.mH;
        m2 = s.mh;
        z_ij = Pi_tilde_hH(m1, s, C3, C4);
        break;
      default:
        z_ij = z_ii(type, s, C3, C4);
        return z_ij;
      }
      return 16.0 * sqr(pi) * z_ij / (pow(m1, 2) - pow(m2, 2));
    }

    double Z_w(const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      wavefunction_renorm_vars params { s, C3, C4 };
      gsl_function F_re, F_im;
      F_re.params = &params;
      F_im.params = &params;
      F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_wpwm_re);
      F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_wpwm_im);
      double result_re, abserr_re, result_im, abserr_im;
      double m_in = 0.0;
      gsl_deriv_central(&F_re, m_in, 1e-8, &result_re, &abserr_re);
      gsl_deriv_central(&F_im, m_in, 1e-8, &result_im, &abserr_im);
      return 1.0 + 0.5 * (result_re + result_im);
    }

    // ----- LO beta functions for lambdas -----

    std::array<complexd,6> betas(const ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      // LO beta functions for lam1 to lam5

      std::array<complexd,6> result;
      result[1] = 12.0*sqr(s.lam1) + 4.0*sqr(s.lam3) + 4.0*s.lam3*s.lam4 + 2.0*sqr(s.lam4) + 2.0*sqr(s.lam5);
      result[2] = 12.0*sqr(s.lam2) + 4.0*sqr(s.lam3) + 4.0*s.lam3*s.lam4 + 2.0*sqr(s.lam4) + 2.0*sqr(s.lam5);
      result[3] = 4.0*sqr(s.lam3) + 2.0*sqr(s.lam4) + (s.lam1 + s.lam2)*(6.0*s.lam3 + 2.0*s.lam4) + 2.0*sqr(s.lam5);
      result[4] = (2.0*s.lam1 + 2.0*s.lam2 + 8.0*s.lam3)*s.lam4 + 4.0*sqr(s.lam4) + 8.0*sqr(s.lam5);
      result[5] = (2.0*s.lam1 + 2.0*s.lam2 + 8.0*s.lam3 + 12.0*s.lam4)*s.lam5;

      // corrections due to gauge boson couplings
      if (gauge_correction)
      {
        result[1] += 3.0/4.0*pow(s.g1, 4) + 3.0/2.0*sqr(s.g1*s.g2) + 9.0/4.0*pow(s.g2, 4) - 3.0*sqr(s.g1)*s.lam1 - 9.0*sqr(s.g2)*s.lam1;
        result[2] += 3.0/4.0*pow(s.g1, 4) + 3.0/2.0*sqr(s.g1*s.g2) + 9.0/4.0*pow(s.g2, 4) - 3.0*sqr(s.g1)*s.lam2 - 9.0*sqr(s.g2)*s.lam2;
        result[3] += -3.0*s.lam3*(3.0*sqr(s.g2) + sqr(s.g1)) + 9.0/4.0*pow(s.g2, 4) + 3.0/4.0*pow(s.g1, 4) - 3.0/2.0*sqr(s.g1*s.g2);
        result[4] += -3.0*s.lam4*(3.0*sqr(s.g2) + sqr(s.g1)) + 3.0*sqr(s.g1*s.g2);
        result[5] += -3.0*s.lam5*(3.0*sqr(s.g2) + sqr(s.g1));
      }

      // corrections due to Yukawa couplings
      if (yukawa_correction)
      {
    // returns model specific coeffiecients (a_i) to Yukawa terms
    // see Nucl.Phys.B 262 (1985) 517-537

        // a1,  a2,  a3,  a4,  a5,  a6,  a7,  a8,  a9, a10, a11, a12, 
        // Ye1, Yd1, Yu1, Ye1, Yd1, Yu1, Ye2, Yd2, Yu2, Ye2, Yd2, Yu2, 

        //     a13,     a14,     a15,             a16,     a17,     a18,     a19,             a20,     a21,     a22,     a23
        // Ye1+Ye2, Yd1+Yd2, Yu1+Yu2, Yu1.Yd2+Yu2.Yd1, Ye1+Ye2, Yd1+Yd2, Yu1+Yu2, Yu1.Yd2+Yu2.Yd1, Ye1+Ye2, Yd1+Yd2, Yu1+Yu2

        std::array<int,24> a;
        switch (s.model_type)
      {
          case 1:  a = std::array<int,24>({{0, 0,0,0,0,0,0, 1,1,1,1,1,1, 1,1,1,0, 1,1,1,0, 1,1,1}}); break;
          case 2:  a = std::array<int,24>({{0, 1,1,0,1,1,0, 0,0,1,0,0,1, 1,1,1,1, 1,1,1,1, 1,1,1}}); break;
          case 3:  a = std::array<int,24>({{0, 1,0,0,1,0,0, 0,1,1,0,1,1, 1,1,1,0, 1,1,1,0, 1,1,1}}); break;
          case 4:  a = std::array<int,24>({{0, 0,1,0,0,1,0, 1,0,1,1,0,1, 1,1,1,1, 1,1,1,1, 1,1,1}}); break;
          default: a = std::array<int,24>({{0, 1,1,1,1,1,1, 1,1,1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1}});
        }

        // get tr(|Y|^2) = tr(sqr(Yii))
        double tr_u2 = 0.0, tr_d2 = 0.0, tr_l2 = 0.0, tr_du = 0.0;
        for (int i = 0; i<3; i++) tr_u2 += sqr(s.Yu[i]);
        for (int i = 0; i<3; i++) tr_d2 += sqr(s.Yd[i]);
        for (int i = 0; i<3; i++) tr_l2 += sqr(s.Ye[i]);
        for (int i = 0; i<3; i++) tr_du += sqr(s.Yd[i]*s.Yu[i]);
        double tr_u4 = sqr(tr_u2), tr_d4 = sqr(tr_d2), tr_l4 = sqr(tr_l2);
        
        result[1] += 4.0*s.lam1*(a[1]*tr_l2  + 3.0*a[2]*tr_d2  + 3.0*a[3]*tr_u2)  -  4.0*(a[4]*tr_l4  + 3.0*a[5]*tr_d4  + 3.0*a[6]*tr_u4);
        result[2] += 4.0*s.lam2*(a[7]*tr_l2  + 3.0*a[8]*tr_d2  + 3.0*a[9]*tr_u2)  -  4.0*(a[10]*tr_l4 + 3.0*a[11]*tr_d4 + 3.0*a[12]*tr_u4);
        result[3] += 2.0*s.lam3*(a[13]*tr_l2 + 3.0*a[14]*tr_d2 + 3.0*a[15]*tr_u2) - 12.0*a[16]*tr_du;
        result[4] += 2.0*s.lam4*(a[17]*tr_l2 + 3.0*a[18]*tr_d2 + 3.0*a[19]*tr_u2) + 12.0*a[20]*tr_du;
        result[5] += 2.0*s.lam5*(a[21]*tr_l2 + 3.0*a[22]*tr_d2 + 3.0*a[23]*tr_u2);
      }

      for (auto& x : result) x /= 16.0*sqr(pi);
      return result;
    }

    // put everything together to get the NLO unitarity scattering eigenvalues
    vector<complexd> get_NLO_scattering_eigenvalues(const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4, const bool wave_function_corrections, const bool gauge_corrections, const bool yukawa_corrections)
    {
      // ensure that we have a Z2-symmetric scalar sector
      check_Z2(s.lam6, s.lam7, "get_NLO_unitarity_LogLikelihood_THDM");

      double c2a = cos(2.0 * s.alpha), c2b = cos(2.0 * s.beta), s2a = sin(2.0 * s.alpha), s2b = sin(2.0 * s.beta);

      auto bi = betas(s, gauge_corrections, yukawa_corrections);
      complexd b1 = bi[1], b2 = bi[2], b3 = bi[3], b4 = bi[4], b5 = bi[5];

      // wavefunction functions
      complexd zij_wpwm, zij_zz, zij_Hpwm, zij_Az, zij_hh, zij_HH, zij_hH, zij_Hh, zij_HpHm, zij_AA;
      complexd B1_z, B2_z, B3_z, B20_z, B21_z, B22_z;
      if (wave_function_corrections)
      {
        zij_wpwm = z_ij(wpwm, s, C3, C4);
        zij_zz = z_ij(zz, s, C3, C4);
        zij_Hpwm = z_ij(Hpwm, s, C3, C4);
        zij_Az = z_ij(Az, s, C3, C4);
        zij_hh = z_ij(hh, s, C3, C4);
        zij_HH = z_ij(HH, s, C3, C4);
        zij_hH = z_ij(hH, s, C3, C4);
        zij_Hh = z_ij(Hh, s, C3, C4);
        zij_HpHm = z_ij(HpHm, s, C3, C4);
        zij_AA = z_ij(AA, s, C3, C4);
      }

      double lam1 = s.lam1, lam2 = s.lam2, lam3 = s.lam3, lam4 = s.lam4, lam5 = s.lam5;

      complexd B1 = -3.0*lam1 + (9.0/2.0)*b1 + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(9.0*sqr(lam1) + sqr(2.0*lam3 + lam4));
      if (wave_function_corrections)
      {
        B1_z = 1.0/(16.0*sqr(pi))*(zij_AA + zij_hh + 2.0*zij_HpHm + zij_HH + 2.0*zij_wpwm + zij_zz - (zij_HH - zij_hh)*c2a);
        B1_z += 1.0/(16.0*sqr(pi))*((2.0*zij_wpwm - 2.0*zij_HpHm + zij_zz - zij_AA)*c2b - (zij_Hh + zij_hH)*s2a - (2.0*zij_Hpwm + zij_Az)*s2b);
        B1 += -3.0/2.0*lam1*B1_z;
      }

      complexd B2 = -3.0*lam2 + (9.0/2.0)*b2 + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(9.0*sqr(lam2) + sqr(2.0*lam3 + lam4));
      if (wave_function_corrections)
      {
        B2_z = 1.0/(16.0*sqr(pi))*(zij_AA + zij_hh + 2.0*zij_HpHm + zij_HH + 2.0*zij_wpwm + zij_zz - (zij_HH - zij_hh)*c2a);
        B2_z += 1.0/(16.0*sqr(pi))*(-(2.0*zij_wpwm - 2.0*zij_HpHm + zij_zz - zij_AA)*c2b + (zij_Hh + zij_hH)*s2a + (2.0*zij_Hpwm + zij_Az)*s2b);
        B2 += -3.0/2.0*lam2*B2_z;
      }

      complexd B3 = -(2.0*lam3 + lam4) + (3.0/2.0)*(2.0*b3 + b4) + 3.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(lam1 + lam2)*(2.0*lam3 + lam4);
      if (wave_function_corrections)
      {
        complexd B3_z = 1.0/(16.0*sqr(pi))*(zij_AA + zij_hh + 2.0*zij_HpHm + zij_HH + 2.0*zij_wpwm + zij_zz);
        B3 += -1.0/2.0*(2.0*lam3 + lam4)*B3_z;
      }

      complexd B4 = -(lam3 + 2.0*lam4) + (3.0/2.0)*(b3 + 2.0*b4) + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(sqr(lam3) + 4.0*lam3*lam4 + 4.0*sqr(lam4) + 9.0*sqr(lam5));
      if (wave_function_corrections)
      {
        B4 += -1.0/2.0*(lam3 + lam4 + lam5)*B3_z;
      }

      complexd B6 = -3.0*lam5 + (9.0/2.0)*b5 + 6.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(lam3 + 2.0*lam4)*lam5;
      if (wave_function_corrections)
      {
        B6 += -1.0/2.0*(lam4 + 2.0*lam5)*B3_z;
      }

      complexd B7 = -lam1 + (3.0/2.0)*b1 + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(sqr(lam1) + sqr(lam4));
      if (wave_function_corrections)
      {
        B7 += -1.0/2.0*lam1*B1_z;
      }

      complexd B8 = -lam2 + (3.0/2.0)*b2 + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(sqr(lam2) + sqr(lam4));
      if (wave_function_corrections)
      {
        B8 += -1.0/2.0*lam2*B2_z;
      }

      complexd B9 = -lam4 + (3.0/2.0)*b4 + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(lam1 + lam2)*lam4;
      if (wave_function_corrections)
      {
        B9 += -1.0/2.0*lam4*B3_z;
      }

      complexd B13 = -lam3 + (3.0/2.0)*b3 + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(sqr(lam3) + sqr(lam5));
      if (wave_function_corrections)
      {
        B13 += -1.0/2.0*(lam3 + lam4 + lam5)*B3_z;
      }

      complexd B15 = -lam5 + (3.0/2.0)*b5 + 2.0/(16.0*sqr(pi))*(ii*pi - 1.0)*lam3*lam5;
      if (wave_function_corrections)
      {
        B15 += -1.0/2.0*(lam4 - 2.0*lam5)*B3_z;
      }

      complexd B19 = -(lam3 - lam4) + (3.0/2.0)*(b3 - b4) + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*sqr(lam3 - lam4);
      if (wave_function_corrections)
      {
        B19 += -1.0/2.0*(lam3 - lam5)*B3_z;
      }

      complexd B20 = -lam1 + (3.0/2.0)*b1 + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(sqr(lam1) + sqr(lam5));
      if (wave_function_corrections)
      {
        B20_z = 1.0/(16.0*sqr(pi))*(zij_AA + zij_hh + zij_HH + zij_zz + (zij_HH - zij_hh)*c2a + (zij_zz - zij_AA)*c2b - (zij_Hh - zij_hH)*s2a - zij_Az*s2b);
        B20 += -1.0*lam1*B20_z;
      }

      complexd B21 = -lam2 + (3.0/2.0)*b2 + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(sqr(lam2) + sqr(lam5));
      if (wave_function_corrections)
      {
        B21_z = 1.0/(16.0*sqr(pi))*(zij_AA + zij_hh + zij_HH + zij_zz + (zij_HH - zij_hh)*c2a - (zij_zz - zij_AA)*c2b + (zij_Hh - zij_hH)*s2a + zij_Az*s2b);
        B21 += -1.0*lam2*B21_z;
      }

      complexd B22 = -lam5 + (3.0/2.0)*b5 + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*(lam1 + lam2)*lam5;
      if (wave_function_corrections)
      {
        B22_z = 1.0/(16.0*sqr(pi))*(zij_AA + zij_hh + zij_HH + zij_zz);
        B22 += -1.0*lam5*B22_z;
      }

      complexd B30 = -(lam3 + lam4) + (3.0/2.0)*(b3 + b4) + 1.0/(16.0*sqr(pi))*(ii*pi - 1.0)*sqr(lam3 + lam4);
      if (wave_function_corrections)
      {
        B30 += -1.0*(lam3 + lam4)*B22_z;
      }

      // eigenvalues
      complexd a00_even_plus  = 1.0/(32.0*pi)*(B1 + B2 + sqrt(sqr(B1 - B2) + 4.0*sqr(B3)));
      complexd a00_even_minus = 1.0/(32.0*pi)*(B1 + B2 - sqrt(sqr(B1 - B2) + 4.0*sqr(B3)));

      complexd a00_odd_plus  = 1.0/(32.0*pi)*(2.0*B4 + 2.0*B6);
      complexd a00_odd_minus = 1.0/(32.0*pi)*(2.0*B4 - 2.0*B6);
      
      complexd a01_even_plus  = 1.0/(32.0*pi)*(B7 + B8 + sqrt(sqr(B7 - B8) + 4.0*sqr(B9)));
      complexd a01_even_minus = 1.0/(32.0*pi)*(B7 + B8 - sqrt(sqr(B7 - B8) + 4.0*sqr(B9)));
      
      complexd a01_odd_plus  = 1.0/(32.0*pi)*(2.0*B13 + 2.0*B15);
      complexd a01_odd_minus = 1.0/(32.0*pi)*(2.0*B13 - 2.0*B15);
      
      complexd a10_odd = 1.0/(32.0*pi)*(2.0*B19);
      
      complexd a11_even_plus  = 1.0/(32.0*pi)*(B20 + B21 + sqrt(sqr(B20 - B21) + 4.0*sqr(B22)));
      complexd a11_even_minus = 1.0/(32.0*pi)*(B20 + B21 - sqrt(sqr(B20 - B21) + 4.0*sqr(B22)));
      
      complexd a11_odd = 1.0/(32.0*pi)*(2.0*B30);

      return {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus,
              a01_even_minus, a01_odd_plus, a01_odd_minus, a10_odd, a11_even_plus, a11_even_minus, a11_odd};
    }

    // ----- NLO unitarity constraint -----

    // Next-to-Leading-Order S-matrix unitarity constraint (soft-cutoff)
    void NLO_unitarity_LogLikelihood_THDM(double& result)
    {
      // References
      
      // (expressions for the Eigenvalues, Bs, and betas without any corrections)
      // https://arxiv.org/pdf/1609.01290

      // (Bs with wavefunction corrections, off-diagonal eigenvalues)
      // https://arxiv.org/pdf/1512.04567

      // (Corrections to betas from the gauge couplings g1,g2,g3 and Yukawa couplings)
      // https://arxiv.org/pdf/1503.08216
      // https://doi.org/10.1016/0550-3213(85)90328-1

      // get options from yaml file
      using namespace Pipes::NLO_unitarity_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double hard_cutoff = runOptions->getValueOrDef<bool>(false, "hard_cutoff");
      vector<double> other_scale = runOptions->getValueOrDef<vector<double>>(std::vector<double>({RunScale::INPUT}), "check_other_scale");
      bool check_corrections_ratio = runOptions->getValueOrDef<bool>(false, "check_correction_ratio");
      bool wave_function_corrections = runOptions->getValueOrDef<bool>(false, "wave_function_corrections");
      bool gauge_corrections = runOptions->getValueOrDef<bool>(false, "gauge_corrections");
      bool yukawa_corrections = runOptions->getValueOrDef<bool>(false, "yukawa_corrections");
      const Spectrum& spec = *Dep::THDM_spectrum;
      const CouplingTable& coupl = *Dep::couplingtable_THDM;
      bool canRun = (*Dep::runToScaleTest_LogLikelihood_THDM == 0.0);

      // helper to get constraint at a single scale
      auto get_NLO_unitarity_LogLikelihood = [&](const SubSpectrum& he, const CouplingTable coup)
      {
        // get required spectrum info
        ThdmSpec s;
        s.fill_angles(he);
        s.fill_generic(he);
        s.fill_higgs(he);
        s.fill_physical(he);
        s.fill_yukawas(he);

        // get the cubic and quartic couplings
        std::vector<complexd> C3; // = get_cubic_coupling_higgs(s);
        std::vector<complexd> C4; // = get_quartic_couplings(s);

        // manually fill in C3, C4 from coupling table

        C3.resize(18);
        C3[0] = std::numeric_limits<double>::quiet_NaN();
        C3[1] = -ii* coup.getSafe({"h0_1", "G+", "G-"});
        C3[2] = -ii* coup.getSafe({"h0_1", "G0", "G0"});
        C3[3] = -ii* coup.getSafe({"h0_2", "G+", "G-"});
        C3[4] = -ii* coup.getSafe({"h0_2", "G0", "G0"});
        C3[5] = -ii* coup.getSafe({"h0_1", "G+", "H-"});
        C3[6] = -ii* coup.getSafe({"h0_1", "G0", "A0"});
        C3[7] = -ii* coup.getSafe({"h0_2", "G+", "H-"});
        C3[8] = -ii* coup.getSafe({"h0_2", "G0", "A0"});
        C3[9] = -ii* coup.getSafe({"A0"  , "G+", "H-"});
        C3[10] = -ii* coup.getSafe({"h0_1", "H+", "H-"});
        C3[11] = -ii* coup.getSafe({"h0_1", "A0", "A0"});
        C3[12] = -ii* coup.getSafe({"h0_2", "H+", "H-"});
        C3[13] = -ii* coup.getSafe({"h0_2", "A0", "A0"});
        C3[14] = -ii* coup.getSafe({"h0_1", "h0_1", "h0_1"});
        C3[15] = -ii* coup.getSafe({"h0_1", "h0_1", "h0_2"});
        C3[16] = -ii* coup.getSafe({"h0_1", "h0_2", "h0_2"});
        C3[17] = -ii* coup.getSafe({"h0_2", "h0_2", "h0_2"});

        C4.resize(23);
        C4[0] = std::numeric_limits<double>::quiet_NaN();
        C4[1] = -ii* coup.getSafe({"h0_1", "h0_1", "G0", "G0"});
        C4[2] = -ii* coup.getSafe({"h0_2", "h0_2", "G0", "G0"});
        C4[3] = -ii* coup.getSafe({"H+", "H-", "G0", "G0"});
        C4[4] = -ii* coup.getSafe({"A0", "A0", "G0", "G0"});
        C4[5] = -ii* coup.getSafe({"h0_1", "h0_1", "G0", "A0"});
        C4[6] = -ii* coup.getSafe({"h0_2", "h0_2", "G0", "A0"});
        C4[7] = -ii* coup.getSafe({"H+", "H-", "G0", "A0"});
        C4[8] = -ii* coup.getSafe({"A0", "A0", "G0", "A0"});
        C4[9] = -ii* coup.getSafe({"h0_1", "h0_1", "H+", "H-"});
        C4[10] = -ii* coup.getSafe({"h0_1", "h0_1", "A0", "A0"});
        C4[11] = -ii* coup.getSafe({"h0_2", "h0_2", "H+", "H-"});
        C4[12] = -ii* coup.getSafe({"h0_2", "h0_2", "A0", "A0"});
        C4[13] = -ii* coup.getSafe({"h0_1", "h0_2", "H+", "H-"});
        C4[14] = -ii* coup.getSafe({"h0_1", "h0_2", "A0", "A0"});
        C4[15] = -ii* coup.getSafe({"h0_1", "h0_1", "h0_1", "h0_1"});
        C4[16] = -ii* coup.getSafe({"h0_1", "h0_1", "h0_1", "h0_2"});
        C4[17] = -ii* coup.getSafe({"h0_1", "h0_1", "h0_2", "h0_2"});
        C4[18] = -ii* coup.getSafe({"h0_1", "h0_2", "h0_2", "h0_2"});
        C4[19] = -ii* coup.getSafe({"h0_2", "h0_2", "h0_2", "h0_2"});
        C4[20] = -ii* coup.getSafe({"H+", "H-", "H+", "H-"});
        C4[21] = -ii* coup.getSafe({"A0", "A0", "H+", "H-"});
        C4[22] = -ii* coup.getSafe({"A0", "A0", "A0", "A0"});

        // get the NLO unitarity eigenvalues
        std::vector<complexd> NLO_eigenvalues = get_NLO_scattering_eigenvalues(s, C3, C4, wave_function_corrections, gauge_corrections, yukawa_corrections);

        int nEig = 12; // number of eigenvalues
        double upper_bound = 0.50; // NLO eigenvalue limit
        double pert_ratio_limit = 1.0; // the upper bound for NLO/LO perturbativity check

        // vector<string> nlo_eig_names = {"a00_even_plus", "a00_even_minus", "a00_odd_plus", "a00_odd_minus", "a01_even_plus", "a01_even_minus", "a01_odd_plus", "a01_odd_minus", "a10_odd", "a11_even_plus", "a11_even_minus", "a11_odd"};

        std::vector<double> NLO_err(nEig,0.0); // 'error' for each NLO eigenvalue (greater than 0 implies a constraint)
        std::vector<double> rat_err(nEig,0.0); // 'error' for each perturbativity check (greater than 0 implies a constraint)

        // get error components for NLO unitarity checks
        for (int i=0; i<nEig; i++)
          NLO_err[i] = std::max(0.0, abs(NLO_eigenvalues[i] - ii/2.0) - upper_bound) / upper_bound;

        // get error components for NLO perturbativity checks
        if (check_corrections_ratio)
        {
          // get the LO unitarity eigenvalues
          vector<complexd> LO_eigenvalues = get_LO_scattering_eigenvalues_ordered(s);

          // flip order of plus/minus to match NLO conventions
          std::vector<int> LO_eigenvalue_order = {2, 1, 4, 3, 6, 5, 8, 7, 9, 11, 10, 12};

          for (int i = 0; i<nEig; i++)
          {
            // get LO eigenvalue and normalize to match NLO
            complexd LO_eigenvalue = -(LO_eigenvalues[LO_eigenvalue_order[i]]) / (32.0*sqr(pi));

            // dont apply perturbativity constraint if LO eigenvalues might be 'accidentally' small
            if (abs(LO_eigenvalue) > 1 / (16.0*pi)) // i.e. orig > 2*pi -> todo: check this!!!
            {
              rat_err[i] = std::max(0.0, abs(NLO_eigenvalues[i]) / abs(LO_eigenvalue) - pert_ratio_limit);
            }
          }
        }

        // rescale error components & get final error sum
        std::vector<double> NLO_err_rescale = { 0.3, 0.6, 6.0, 0.35, 2.1, 2.4, 2.7, 2.3, 2.0, 2.4, 2.6, 4.1 };
        std::vector<double> rat_err_rescale = { 0.03, 0.11, 0.18, 0.20, 0.07, 0.07, 0.21, 0.18, 0.14, 0.05, 0.04, 1.0 };

        double NLO_err_sum = rescale_components(NLO_err, NLO_err_rescale, 0, "e");
        double rat_err_sum = rescale_components(rat_err, rat_err_rescale, 0, "r");

        double result = -cutoff_soft_square(NLO_err_sum + rat_err_sum, 1.0, inv_LL_threshold);
        return result;
      };

      // get worst performing LogLike at all scales
      result = get_worst_LL_of_all_scales(spec, coupl, get_NLO_unitarity_LogLikelihood, is_FS_model, other_scale, canRun);
      if (hard_cutoff && result < -0.0) result = -L_MAX;

      // test_data["NLO"] = -result;
    }

  }
}
