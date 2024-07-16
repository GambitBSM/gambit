//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit
///
///  SpecBit module functions related to the
///  2HDM general models:
///  - Type-I
///  - Type-II
///  - lepton specific (X)
///  - flipped (Y)
///  - general (Type-III)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2016-2019
///  \date 2020 Oct
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Apr
///
///  \author Cristian Sierra
///          (cristian.sierra@monash.edu)
///  \date 2021 Apr
///
///  \author A.S. Woodcock
///          (alex.woodcock@outlook.com)
///  \date   May 2022
///
///  *********************************************

// Eigen headers
#include "gambit/Utils/begin_ignore_warnings_eigen.hpp"
#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include "gambit/Utils/end_ignore_warnings.hpp"

// FlexibleSUSY headers
#include "flexiblesusy/src/lowe.h"
#include "flexiblesusy/src/spectrum_generator_settings.hpp"
#include "flexiblesusy/models/THDM_I/THDM_I_input_parameters.hpp"
#include "flexiblesusy/models/THDM_II/THDM_II_input_parameters.hpp"
#include "flexiblesusy/models/THDM_LS/THDM_LS_input_parameters.hpp"
#include "flexiblesusy/models/THDM_flipped/THDM_flipped_input_parameters.hpp"

// GAMBIT headers
#include "gambit/Elements/spectrum_types.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/smlike_higgs.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Elements/couplingtable.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/util_macros.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/Utils/slhaea_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Utils/point_counter.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/SpecBit/THDMSpec.hpp"
#include "gambit/SpecBit/model_files_and_boxes.hpp"
#include "gambit/Models/SimpleSpectra/THDMSimpleSpec.hpp"

// #define SPECBIT_DEBUG // turn on debug mode


namespace Gambit
{
  namespace SpecBit
  {
    // ----- HELPERS -----

    // type aliases
    using namespace LogTags;
    using namespace flexiblesusy;
    using namespace Utils;
    using std::vector;
    using std::complex;
    using std::real;
    using std::imag;
    using std::conj;

    // imaginary unit
    constexpr complex<double> ii(0,1);

    // get symmetry factor for a list of particles. MUST be sorted first
    int get_symmetry_factor(const std::vector<std::string>& particles)
    {
      int symm_factor = 1;
      int count = 1;
      static std::string tmp = "    ";
      const std::string* prev = &tmp;

      for (auto& particle : particles)
      {
        // can assume they are sorted here
        if (particle == *prev)
        {
          count += 1;
        }
        else
        {
          symm_factor *= Utils::factorial(count);
          count = 1;
          prev = &particle;
        }
      }
      symm_factor *= Utils::factorial(count);

      return symm_factor;
    }
    
    // efficiently sort 3 integers
    void sort(int& j, int& k, int& l)
    {
      if (j>k) std::swap(j,k);
      if (j>l) std::swap(j,l);
      if (k>l) std::swap(l,k);
    }

    // efficiently sort 4 integers
    void sort(int& j, int& k, int& l, int& m)
    {
      if (k<j) std::swap(k,j);
      if (l<k) std::swap(l,k);
      if (k<j) std::swap(k,j);
      if (m<l) std::swap(m,l);
      if (l<k) std::swap(l,k);
      if (k<j) std::swap(k,j);
    }

    // ----- tree-level spectrum generation -----

    // get a gambit::Spectrum for tree-level 2HDM
    void get_THDM_spectrum_tree(Spectrum &result)
    {
      using namespace Pipes::get_THDM_spectrum_tree;
      const SMInputs& sminputs = *Dep::SMINPUTS;

      // SoftSUSY object used to set quark and lepton masses and gauge
      // couplings in QEDxQCD effective theory
      softsusy::QedQcd oneset;

      // Fill QedQcd object with SMInputs values
      setup_QedQcd(oneset, sminputs);

      // Run everything to Mz
      oneset.toMz();

      // Create a SubSpectrum object to wrap the qedqcd object
      // Attach the sminputs object as well, so that SM pole masses can be passed on (these aren't easily
      // extracted from the QedQcd object, so use the values that we put into it.)
      QedQcdWrapper qedqcdspec(oneset, sminputs);

      // fill generic basis
      double lam1 = *Param.at("lambda1");
      double lam2 = *Param.at("lambda2");
      double lam3 = *Param.at("lambda3");
      double lam4 = *Param.at("lambda4");
      double lam5 = *Param.at("lambda5");
      double lam6 = *Param.at("lambda6");
      double lam7 = *Param.at("lambda7");
      double tanb = *Param.at("tanb");
      double m122 = *Param.at("m12_2");
      double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
      double beta = atan(tanb);
      double sb = sin(beta), cb = cos(beta), tb = tanb;
      double sb2 = sb*sb, cb2 = cb*cb, ctb = 1./tb, s2b = sin(2*beta), c2b = cos(2*beta);
      double lam345 = lam3 + lam4 + lam5;
      // https://arxiv.org/pdf/hep-ph/0207010 page 6
      double m112 = m122*tb  - 0.5*v2 * (lam1*cb*cb + lam345*sb*sb + 3.0*lam6*sb*cb + lam7*sb*sb*tb);
      double m222 = m122*ctb - 0.5*v2 * (lam2*sb*sb + lam345*cb*cb + lam6*cb*cb*ctb + 3.0*lam7*sb*cb);

      // fill Higgs basis
      // https://arxiv.org/pdf/1507.04281 page 5-6
      // double M122 = (m112-m222)*s2b + m122*c2b;
      // double M112 = m112*cb2 + m222*sb2 - m122*s2b;
      double M222 = m112*sb2 + m222*cb2 + m122*s2b;
      double Lam1 = lam1*pow(cb,4) + lam2*pow(sb,4) + 0.5*lam345*pow(s2b,2) + 2.*s2b*(cb2*lam6+sb2*lam7);
      // double Lam2 = lam1*pow(sb,4) + lam2*pow(cb,4) + 0.5*lam345*pow(s2b,2) - 2.*s2b*(sb2*lam6+cb2*lam7);
      double Lam3 = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam3 - s2b*c2b*(lam6-lam7);
      double Lam4 = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam4 - s2b*c2b*(lam6-lam7);
      double Lam5 = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam5 - s2b*c2b*(lam6-lam7);
      double Lam6 = -0.5*s2b*(lam1*cb2-lam2*sb2-lam345*c2b) + cb*cos(3.*beta)*lam6 + sb*sin(3.*beta)*lam7;
      // double Lam7 = -0.5*s2b*(lam1*sb2-lam2*cb2+lam345*c2b) + sb*sin(3.*beta)*lam6 + cb*cos(3.*beta)*lam7;

      // fill physical basis
      // https://arxiv.org/pdf/1507.04281 page 7
      double mA2  = M222 + 0.5*v2*(Lam3+Lam4-Lam5);
      double mHp2 = M222 + 0.5*v2*Lam3;

      // https://arxiv.org/pdf/hep-ph/0207010 page 7
      double sM112 = mA2*sb2+v2*(lam1*cb2+2.*lam6*sb*cb+lam5*sb2);
      double sM122 = -mA2*sb*cb+v2*((lam3+lam4)*sb*cb+lam6*cb2+lam7*sb2);
      double sM222 = mA2*cb2+v2*(lam2*sb2+2.*lam7*sb*cb+lam5*cb2);
      double mh2 = 0.5*(sM112+sM222-sqrt(sqr(sM112-sM222)+sqr(2.*sM122)));
      double mH2 = 0.5*(sM112+sM222+sqrt(sqr(sM112-sM222)+sqr(2.*sM122)));

      if (mA2 < -0. || mHp2 < -0. || mh2 < -0. || mH2 < -0.)
      {
        invalid_point().raise("Negative mass-squared encountered. Point invalidated");
      }

      double mA = sqrt(abs(mA2));
      double mHp = sqrt(abs(mHp2));
      double mh = sqrt(abs(mh2));
      double mH = sqrt(abs(mH2));

      // calculate alpha

      // see https://arxiv.org/pdf/1507.04281 page 8
      double cba = -sgn(Lam6)*sqrt(abs((Lam1*v2-mh2)/(mH2-mh2)));
      double ba = acos(cba);
      double alpha = beta - ba;

      // conventions for alpha

      if (beta-alpha >= pi) alpha += 2*pi;
      if (beta-alpha <= -pi) alpha -= 2*pi;

      // CONVENTION-A: ba in (0,pi), sba in (0,+1), cba in (-1,+1)B
      // if (beta-alpha >= pi) alpha += pi;
      // if (beta-alpha < 0) alpha -= pi;

      // CONVENTION-B: ba in (-pi/2,+pi/2), sba in (-1,+1), cba in (0,+1)
      if (beta-alpha >= pi/2) alpha += pi;
      if (beta-alpha < -pi/2) alpha -= pi;

      // Initialise an object to carry the THDM sector information
      Models::THDMModel thdm_model;
      thdm_model.model_type = *Dep::THDM_Type;
      thdm_model.tanb       = tanb;
      thdm_model.alpha      = alpha;
      thdm_model.lambda1    = lam1;
      thdm_model.lambda2    = lam2;
      thdm_model.lambda3    = lam3;
      thdm_model.lambda4    = lam4;
      thdm_model.lambda5    = lam5;
      thdm_model.lambda6    = lam6;
      thdm_model.lambda7    = lam7;
      thdm_model.m11_2      = m112;
      thdm_model.m22_2      = m222;
      thdm_model.m12_2      = m122;
      thdm_model.mh0        = mh;
      thdm_model.mH0        = mH;
      thdm_model.mA0        = mA;
      thdm_model.mC         = mHp;
      thdm_model.mG0        = 0.0;
      thdm_model.mGC        = 0.0;

      // quantities needed to fill spectrum, intermediate calculations
      const double vev      = sqrt(v2);
      const double alpha_em = 1.0 / sminputs.alphainv;
      const double e        = sqrt(4*pi*alpha_em);
      const double cosW     = sminputs.mW/sminputs.mZ;
      const double sinW     = sqrt(1 - sqr(cosW)); // Warning: always positive

      // Standard model
      thdm_model.sinW2 = sqr(sinW);
      thdm_model.vev = vev;
      // TODO: figure out why g1,g2 are different elsewhere
      // NOTE: g1,g2 have now been swapped
      thdm_model.g2 = e / sinW;
      thdm_model.g1 = e / cosW;
      thdm_model.g3 = pow(4 * pi * (sminputs.alphaS), 0.5);
      thdm_model.mW = sminputs.mW;

      // Yukawas
      for(int i=0; i<3; i++)
      {
        for(int j=0; j<3; j++)
        {
          thdm_model.Yu2[i][j] = *Param["yu2_re_"+std::to_string(i+1)+std::to_string(j+1)];
          thdm_model.Yd2[i][j] = *Param["yd2_re_"+std::to_string(i+1)+std::to_string(j+1)];
          thdm_model.Ye2[i][j] = *Param["yl2_re_"+std::to_string(i+1)+std::to_string(j+1)];

          thdm_model.ImYu2[i][j] = *Param["yu2_im_"+std::to_string(i+1)+std::to_string(j+1)];
          thdm_model.ImYd2[i][j] = *Param["yd2_im_"+std::to_string(i+1)+std::to_string(j+1)];
          thdm_model.ImYe2[i][j] = *Param["yl2_im_"+std::to_string(i+1)+std::to_string(j+1)];

          thdm_model.Yu1[i][j] = -tanb * thdm_model.Yu2[i][j];
          thdm_model.Yd1[i][j] = -tanb * thdm_model.Yd2[i][j];
          thdm_model.Ye1[i][j] = -tanb * thdm_model.Ye2[i][j];

          thdm_model.ImYu1[i][j] = -tanb * thdm_model.ImYu2[i][j];
          thdm_model.ImYd1[i][j] = -tanb * thdm_model.ImYd2[i][j];
          thdm_model.ImYe1[i][j] = -tanb * thdm_model.ImYe2[i][j];
        }
      }

      const double sqrt2v = sqrt(2.0)/vev;

      thdm_model.Yu1[0][0] += sqrt2v * sminputs.mU / cb;
      thdm_model.Yu1[1][1] += sqrt2v * sminputs.mCmC / cb;
      thdm_model.Yu1[2][2] += sqrt2v * sminputs.mT / cb;
      thdm_model.Yd1[0][0] += sqrt2v * sminputs.mD / cb;
      thdm_model.Yd1[1][1] += sqrt2v * sminputs.mS / cb;
      thdm_model.Yd1[2][2] += sqrt2v * sminputs.mBmB / cb;
      thdm_model.Ye1[0][0] += sqrt2v * sminputs.mE / cb;
      thdm_model.Ye1[1][1] += sqrt2v * sminputs.mMu / cb;
      thdm_model.Ye1[2][2] += sqrt2v * sminputs.mTau / cb;

      // Create a SimpleSpec object to wrap the spectrum
      THDMSimpleSpec thdm_spec(thdm_model,sminputs);

      thdm_spec.set_override(Par::dimensionless, 0, "isIDM", true);
      thdm_spec.set_override(Par::dimensionless, cos(beta-alpha), "cosba", true);

      // add Goldstones to tree-level spectrum
      thdm_spec.set_override(Par::mass1, 0, "G0", true);
      thdm_spec.set_override(Par::mass1, 0, "G+", true);
      thdm_spec.set_override(Par::Pole_Mass, 0, "G0", true);
      thdm_spec.set_override(Par::Pole_Mass, 0, "G+", true);

      THDM_TYPE THDM_type = *Dep::THDM_Type;

      for (int j=1; j<=3; ++j)
      {
        for (int i=1; i<=3; ++i)
        {
          if (THDM_type == THDM_TYPE::TYPE_I)
          {
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Yd2", i, j), "Yd", i, j, true);
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Yu2", i, j), "Yu", i, j, true);
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Ye2", i, j), "Ye", i, j, true);
          }
          if (THDM_type == THDM_TYPE::TYPE_II)
          {
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Yd1", i, j), "Yd", i, j, true);
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Yu2", i, j), "Yu", i, j, true);
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Ye1", i, j), "Ye", i, j, true);
          }
          if (THDM_type == THDM_TYPE::TYPE_LS)
          {
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Yd2", i, j), "Yd", i, j, true);
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Yu2", i, j), "Yu", i, j, true);
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Ye1", i, j), "Ye", i, j, true);
          }
          if (THDM_type == THDM_TYPE::TYPE_flipped)
          {
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Yd1", i, j), "Yd", i, j, true);
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Yu2", i, j), "Yu", i, j, true);
            thdm_spec.set_override(Par::dimensionless, thdm_spec.get(Par::dimensionless, "Ye2", i, j), "Ye", i, j, true);
          }
        }
      }

      // Create full Spectrum object from components above
      // Note: SubSpectrum objects cannot be copied, but Spectrum
      // objects can due to a special copy constructor which does
      // the required cloning of the constituent SubSpectra.
      //static Spectrum full_spectrum;

      // Note subtlety! There are TWO constructors for the Spectrum object:
      // If pointers to SubSpectrum objects are passed, it is assumed that
      // these objects are managed EXTERNALLY! So if we were to do this:
      //   full_spectrum = Spectrum(&qedqcdspec,&singletspec,sminputs);
      // then the SubSpectrum objects would end up DELETED at the end of
      // this scope, and we will get a segfault if we try to access them
      // later. INSTEAD, we should just pass the objects themselves, and
      // then they will be CLONED and the Spectrum object will take
      // possession of them:

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      result = Spectrum(qedqcdspec,thdm_spec,sminputs,&Param,mass_cut,mass_ratio_cut);
    }

    // ----- loop-level spectrum generation -----

    // helper to setup Spectrum with a FlexibleSUSY spectrum generator
    template <class MI>
    Spectrum run_FS_spectrum_generator(const typename MI::InputParameters &input, const SMInputs &sminputs, const Options &runOptions,
                                        const std::map<str, safe_ptr<const double>> &input_Param, THDM_TYPE &model_type)
    {
      // Compute an THDM spectrum using flexiblesusy
      // In GAMBIT there are THREE flexiblesusy spectrum generators currently in
      // use, for each of three possible boundary condition types:
      //   - GUT scale input
      //   - Electroweak symmetry breaking scale input
      //   - Intermediate scale Q input
      // These each require slightly different setup, but once that is done the rest
      // of the code required to run them is the same; this is what is contained in
      // the below template function.
      // MI for Model Interface, as defined in model_files_and_boxes.hpp


      // SoftSUSY object used to set quark and lepton masses and gauge
      // couplings in QEDxQCD effective theory
      // Will be initialised by default using values in lowe.h, which we will
      // override next.
      softsusy::QedQcd oneset;

      // Fill QedQcd object with SMInputs values
      setup_QedQcd(oneset, sminputs);

      // Run everything to Mz
      oneset.toMz();

      // Create spectrum generator object
      typename MI::SpectrumGenerator spectrum_generator;

      // Spectrum generator settings
      // Default options copied from flexiblesusy/src/spectrum_generator_settings.hpp
      //
      // | enum                             | possible values              | default value   |
      // |----------------------------------|------------------------------|-----------------|
      // | precision                        | any positive double          | 1.0e-4          |
      // | max_iterations                   | any positive double          | 0 (= automatic) |
      // | algorithm                        | 0 (two-scale) or 1 (lattice) | 0 (= two-scale) |
      // | calculate_sm_masses              | 0 (no) or 1 (yes)            | 0 (= no)        |
      // | pole_mass_loop_order             | 0, 1, 2                      | 2 (= 2-loop)    |
      // | ewsb_loop_order                  | 0, 1, 2                      | 2 (= 2-loop)    |
      // | beta_loop_order                  | 0, 1, 2                      | 2 (= 2-loop)    |
      // | threshold_corrections_loop_order | 0, 1                         | 1 (= 1-loop)    |
      // | higgs_2loop_correction_at_as     | 0, 1                         | 1 (= enabled)   |
      // | higgs_2loop_correction_ab_as     | 0, 1                         | 1 (= enabled)   |
      // | higgs_2loop_correction_at_at     | 0, 1                         | 1 (= enabled)   |
      // | higgs_2loop_correction_atau_atau | 0, 1                         | 1 (= enabled)   |

      Spectrum_generator_settings settings;
      settings.set(Spectrum_generator_settings::precision, runOptions.getValueOrDef<double>(1.0e-4, "precision_goal"));
      settings.set(Spectrum_generator_settings::max_iterations, runOptions.getValueOrDef<double>(0, "max_iterations"));
      settings.set(Spectrum_generator_settings::calculate_sm_masses, runOptions.getValueOrDef<bool>(true, "calculate_sm_masses"));

      settings.set(Spectrum_generator_settings::pole_mass_loop_order, runOptions.getValueOrDef<int>(2, "pole_mass_loop_order"));
      settings.set(Spectrum_generator_settings::pole_mass_loop_order, runOptions.getValueOrDef<int>(2, "ewsb_loop_order"));
      settings.set(Spectrum_generator_settings::beta_loop_order, runOptions.getValueOrDef<int>(2, "beta_loop_order"));
      settings.set(Spectrum_generator_settings::threshold_corrections_loop_order, runOptions.getValueOrDef<int>(2, "threshold_corrections_loop_order"));
      
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_as, runOptions.getValueOrDef<int>(1, "higgs_2loop_correction_at_as"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_ab_as, runOptions.getValueOrDef<int>(1, "higgs_2loop_correction_ab_as"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_at, runOptions.getValueOrDef<int>(1, "higgs_2loop_correction_at_at"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_atau_atau, runOptions.getValueOrDef<int>(1, "higgs_2loop_correction_atau_atau"));
      
      settings.set(Spectrum_generator_settings::top_pole_qcd_corrections, runOptions.getValueOrDef<int>(1, "top_pole_qcd_corrections"));
      settings.set(Spectrum_generator_settings::beta_zero_threshold, runOptions.getValueOrDef<double>(1.000000000e-14, "beta_zero_threshold"));
      settings.set(Spectrum_generator_settings::eft_matching_loop_order_up, runOptions.getValueOrDef<int>(1, "eft_matching_loop_order_up"));
      settings.set(Spectrum_generator_settings::eft_matching_loop_order_down, runOptions.getValueOrDef<int>(1, "eft_matching_loop_order_down"));
      settings.set(Spectrum_generator_settings::threshold_corrections, runOptions.getValueOrDef<int>(123111321, "threshold_corrections"));
      
      // Spectrum_generator_settings settings;
      // settings.set(Spectrum_generator_settings::precision, runOptions.getValueOrDef<double>(1.0e-4, "precision_goal"));
      // settings.set(Spectrum_generator_settings::max_iterations, runOptions.getValueOrDef<double>(0, "max_iterations"));
      // settings.set(Spectrum_generator_settings::calculate_sm_masses, runOptions.getValueOrDef<bool>(true, "calculate_sm_masses"));

      // settings.set(Spectrum_generator_settings::pole_mass_loop_order, runOptions.getValueOrDef<int>(0, "pole_mass_loop_order"));
      // settings.set(Spectrum_generator_settings::ewsb_loop_order, runOptions.getValueOrDef<int>(0, "ewsb_loop_order"));
      // settings.set(Spectrum_generator_settings::beta_loop_order, runOptions.getValueOrDef<int>(1, "beta_loop_order"));
      // settings.set(Spectrum_generator_settings::threshold_corrections_loop_order, runOptions.getValueOrDef<int>(0, "threshold_corrections_loop_order"));

      // settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_as, runOptions.getValueOrDef<int>(0, "higgs_2loop_correction_at_as"));
      // settings.set(Spectrum_generator_settings::higgs_2loop_correction_ab_as, runOptions.getValueOrDef<int>(0, "higgs_2loop_correction_ab_as"));
      // settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_at, runOptions.getValueOrDef<int>(0, "higgs_2loop_correction_at_at"));
      // settings.set(Spectrum_generator_settings::higgs_2loop_correction_atau_atau, runOptions.getValueOrDef<int>(0, "higgs_2loop_correction_atau_atau"));

      // settings.set(Spectrum_generator_settings::top_pole_qcd_corrections, runOptions.getValueOrDef<int>(0, "top_pole_qcd_corrections"));
      // settings.set(Spectrum_generator_settings::beta_zero_threshold, runOptions.getValueOrDef<double>(1.0e-14, "beta_zero_threshold"));
      // settings.set(Spectrum_generator_settings::eft_matching_loop_order_up, runOptions.getValueOrDef<int>(0, "eft_matching_loop_order_up"));
      // settings.set(Spectrum_generator_settings::eft_matching_loop_order_down, runOptions.getValueOrDef<int>(0, "eft_matching_loop_order_down"));
      // settings.set(Spectrum_generator_settings::threshold_corrections, runOptions.getValueOrDef<int>(123111321, "threshold_corrections"));

      spectrum_generator.set_settings(settings);

      // Generate spectrum
      spectrum_generator.run(oneset, input);

      // Extract report on problems...
      const typename MI::Problems &problems = spectrum_generator.get_problems();

      // Create Model_interface to carry the input and results, and know
      // how to access the flexiblesusy routines.
      // Note: Output of spectrum_generator.get_model() returns type, e.g. CMSSM.
      // Need to convert it to type CMSSM_slha (which alters some conventions of
      // parameters into SLHA format)
      MI model_interface(spectrum_generator, oneset, input);

      // Create SubSpectrum object to wrap flexiblesusy data
      // THIS IS STATIC so that it lives on once we leave this module function. We
      // therefore cannot run the same spectrum generator twice in the same loop and
      // maintain the spectrum resulting from both. But we should never want to do
      // this.
      // A pointer to this object is what gets turned into a SubSpectrum pointer and
      // passed around Gambit.
      //
      // This object will COPY the interface data members into itself, so it is now the
      // one-stop-shop for all spectrum information, including the model interface object.
      THDMSpec<MI> thdmspec(model_interface, "FlexibleSUSY", "2.0.beta");
      // Add extra information about the scales used to the wrapper object
      // (last parameter turns on the 'allow_new' option for the override setter, which allows
      //  us to set parameters that don't previously exist)
      thdmspec.set_override(Par::mass1, spectrum_generator.get_high_scale(), "high_scale", true);
      thdmspec.set_override(Par::mass1, spectrum_generator.get_low_scale(), "low_scale", true);
      thdmspec.set_override(Par::dimensionless, 0, "isIDM", true);
      // thdmspec.set_override(Par::dimensionless, cos(thdmspec.get(Par::dimensionless, "beta")-thdmspec.get(Par::dimensionless, "alpha")), "cosba", true);

      if (input_Param.find("TanBeta") != input_Param.end())
      {
        thdmspec.set_override(Par::dimensionless, *input_Param.at("tanb"), "tanbeta(mZ)", true);
      }

      // Set the model type manually
      thdmspec.set_override(Par::dimensionless, model_type, "model_type", true);

      // Manually fill the yuakwa couplings that are input parameters
      const double tanb = thdmspec.get(Par::dimensionless, "tanb");

      for(int i=1; i<=3; i++)
      {
        for(int j=1; j<=3; j++)
        {
          // As this is a full spectrum, make sure to improve the translations
          double Yu2 = 0, Yd2 = 0, Ye2 = 0, Yu1 = 0, Yd1 = 0, Ye1 = 0;
          switch(model_type)
          {
            case TYPE_I:
              Yu2 = thdmspec.get(Par::dimensionless, "Yu", i, j);
              Yd2 = thdmspec.get(Par::dimensionless, "Yd", i, j);
              Ye2 = thdmspec.get(Par::dimensionless, "Ye", i, j);
              break;
            case TYPE_II:
              Yu2 = -thdmspec.get(Par::dimensionless, "Yu", i, j);
              Yd1 = thdmspec.get(Par::dimensionless, "Yd", i, j);
              Ye1 = thdmspec.get(Par::dimensionless, "Ye", i, j);
              break;
            case TYPE_LS:
              Yu2 = -thdmspec.get(Par::dimensionless, "Yu", i, j);
              Yd2 = thdmspec.get(Par::dimensionless, "Yd", i, j);
              Ye1 = thdmspec.get(Par::dimensionless, "Ye", i, j);
              break;
            case TYPE_flipped:
              Yu2 = -thdmspec.get(Par::dimensionless, "Yu", i, j);
              Yd1 = thdmspec.get(Par::dimensionless, "Yd", i, j);
              Ye2 = thdmspec.get(Par::dimensionless, "Ye", i, j);
              break;
            case TYPE_III:
              // Use input values here
              Yu2 = *input_Param.at("yu2_re_"+std::to_string(i)+std::to_string(j));
              Yd2 = *input_Param.at("yd2_re_"+std::to_string(i)+std::to_string(j));
              Ye2 = *input_Param.at("yl2_re_"+std::to_string(i)+std::to_string(j));
              Yu1 = -tanb*(Yu2-thdmspec.get(Par::dimensionless, "Yu", i, j));
              Yd1 = -tanb*(Yd2-thdmspec.get(Par::dimensionless, "Yd", i, j));
              Ye1 = -tanb*(Ye2-thdmspec.get(Par::dimensionless, "Ye", i, j));
              break;
            default:
              SpecBit_error().raise(LOCAL_INFO, "invalid model type");
          }

          thdmspec.set_override(Par::dimensionless, Yu2, "Yu2", i, j, true);
          thdmspec.set_override(Par::dimensionless, Yd2, "Yd2", i, j, true);
          thdmspec.set_override(Par::dimensionless, Ye2, "Ye2", i, j, true);
          thdmspec.set_override(Par::dimensionless, Yu1, "Yu1", i, j, true);
          thdmspec.set_override(Par::dimensionless, Yd1, "Yd1", i, j, true);
          thdmspec.set_override(Par::dimensionless, Ye1, "Ye1", i, j, true);

          thdmspec.set_override(Par::dimensionless, *input_Param.at("yu2_im_"+std::to_string(i)+std::to_string(j)), "ImYu2", i, j, true);
          thdmspec.set_override(Par::dimensionless, *input_Param.at("yd2_im_"+std::to_string(i)+std::to_string(j)), "ImYd2", i, j, true);
          thdmspec.set_override(Par::dimensionless, *input_Param.at("yl2_im_"+std::to_string(i)+std::to_string(j)), "ImYe2", i, j, true);
          thdmspec.set_override(Par::dimensionless, -tanb * thdmspec.get(Par::dimensionless, "ImYu2", i, j), "ImYu1", i, j, true);
          thdmspec.set_override(Par::dimensionless, -tanb * thdmspec.get(Par::dimensionless, "ImYd2", i, j), "ImYd1", i, j, true);
          thdmspec.set_override(Par::dimensionless, -tanb * thdmspec.get(Par::dimensionless, "ImYe2", i, j), "ImYe1", i, j, true);

        }
      }

      // Create a second SubSpectrum object to wrap the qedqcd object used to initialise the spectrum generator
      // Attach the sminputs object as well, so that SM pole masses can be passed on (these aren't easily
      // extracted from the QedQcd object, so use the values that we put into it.)
      QedQcdWrapper qedqcdspec(oneset, sminputs);

      // Deal with points where spectrum generator encountered a problem
      #ifdef SPECBIT_DEBUG
        std::cout << "Problem? " << problems.have_problem() << std::endl;
      #endif
      if (problems.have_problem())
      {
        std::ostringstream errmsg;
        errmsg << "A serious problem was encountered during spectrum generation!; ";
        errmsg << "Message from FlexibleSUSY below:" << std::endl;
        problems.print_problems(errmsg);
        problems.print_warnings(errmsg);

        if (runOptions.getValueOrDef<bool>(false, "invalid_point_fatal"))
        {
          SpecBit_error().raise(LOCAL_INFO, errmsg.str());
        }
        else
        {
          logger() << errmsg.str() << EOM;
          invalid_point().raise(errmsg.str());
        }
      }

      if (problems.have_warning())
      {
        std::ostringstream msg;
        problems.print_warnings(msg);
        SpecBit_warning().raise(LOCAL_INFO, msg.str()); //TODO: Is a warning the correct thing to do here?
      }

      // Write SLHA file (for debugging purposes...)
      #ifdef SPECBIT_DEBUG
        typename MI::SlhaIo slha_io;
        slha_io.set_spinfo(problems);
        slha_io.set_sminputs(oneset);
        //  slha_io.set_minpar(input);
        //  slha_io.set_extpar(input);
        slha_io.set_spectrum(thdmspec.model_interface.model);
        slha_io.write_to_file("SpecBit/initial_THDM_spectrum->slha");
        thdmspec.model().print(std::cout);
      #endif

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = runOptions.getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = runOptions.getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // Package QedQcd SubSpectrum object, MSSM SubSpectrum object, and SMInputs struct into a 'full' Spectrum object
      return Spectrum(qedqcdspec, thdmspec, sminputs, &input_Param, mass_cut, mass_ratio_cut);
    }

    // helper function to fill in FlexibleSUSY input parameters
    template <class FS_THDM_input_struct>
    void fill_THDM_FS_input(FS_THDM_input_struct &input, const std::map<str, safe_ptr<const double>> &Param)
    {
      // read in THDM model parameters
      input.TanBeta = *Param.at("tanb");
      input.Lambda1IN = *Param.at("lambda1");
      input.Lambda2IN = *Param.at("lambda2");
      input.Lambda3IN = *Param.at("lambda3");
      input.Lambda4IN = *Param.at("lambda4");
      input.Lambda5IN = *Param.at("lambda5");
      input.Lambda6IN = *Param.at("lambda6");
      input.Lambda7IN = *Param.at("lambda7");
      input.M122IN = *Param.at("m12_2");
      input.Qin = *Param.at("Qin");
      // Sanity check on tanb
      if (input.TanBeta < 0)
      {
        std::ostringstream msg;
        msg << "Tried to set TanBeta parameter to a negative value (" << input.TanBeta << ")! This parameter must be positive. Please check your inifile and try again.";
        SpecBit_error().raise(LOCAL_INFO, msg.str());
      }
    }

    // get a gambit::Spectrum for loop-level 2HDM
    void get_THDM_spectrum_FS(Spectrum &result)
    {
      using namespace Pipes::get_THDM_spectrum_FS;
      const SMInputs& sminputs = *Dep::SMINPUTS;
      using namespace softsusy;

      // Determine THDM type
      THDM_TYPE THDM_type = *Dep::THDM_Type;
      switch (THDM_type)
      {
        case TYPE_I:
        {
          #if (FS_MODEL_THDM_I_IS_BUILT)
            THDM_I_input_parameters input;
            fill_THDM_FS_input(input, Param);
            result = run_FS_spectrum_generator<THDM_I_interface<ALGORITHM1>>(input, sminputs, *runOptions, Param, THDM_type);
            const double scale = runOptions->getValueOrDef<double>(sminputs.mZ, "QrunTo");
            if(scale != sminputs.mZ)
              result.RunBothToScale(scale);
          #else
            std::ostringstream errmsg;
            errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
            errmsg << "FS models for THDM_I not built." << std::endl;
            SpecBit_error().raise(LOCAL_INFO, errmsg.str());
          #endif
          break;
        }
        case TYPE_II:
        {
          #if (FS_MODEL_THDM_II_IS_BUILT)
            THDM_II_input_parameters input;
            fill_THDM_FS_input(input, Param);
            result = run_FS_spectrum_generator<THDM_II_interface<ALGORITHM1>>(input, sminputs, *runOptions, Param, THDM_type);
            const double scale = runOptions->getValueOrDef<double>(sminputs.mZ, "QrunTo");
            if(scale != sminputs.mZ)
              result.RunBothToScale(scale);
          #else
            std::ostringstream errmsg;
            errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
            errmsg << "FS models for THDM_II not built." << std::endl;
            SpecBit_error().raise(LOCAL_INFO, errmsg.str());
          #endif
          break;
        }
        case TYPE_LS:
        {
          #if (FS_MODEL_THDM_LS_IS_BUILT)
            THDM_LS_input_parameters input;
            fill_THDM_FS_input(input, Param);
            result = run_FS_spectrum_generator<THDM_LS_interface<ALGORITHM1>>(input, sminputs, *runOptions, Param, THDM_type);
            const double scale = runOptions->getValueOrDef<double>(sminputs.mZ, "QrunTo");
            if(scale != sminputs.mZ)
              result.RunBothToScale(scale);
          #else
            std::ostringstream errmsg;
            errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
            errmsg << "FS models for THDM_LS not built." << std::endl;
            SpecBit_error().raise(LOCAL_INFO, errmsg.str());
          #endif
          break;
        }
        case TYPE_flipped:
        {
          #if (FS_MODEL_THDM_flipped_IS_BUILT)
            THDM_flipped_input_parameters input;
            fill_THDM_FS_input(input, Param);
            result = run_FS_spectrum_generator<THDM_flipped_interface<ALGORITHM1>>(input, sminputs, *runOptions, Param, THDM_type);
            const double scale = runOptions->getValueOrDef<double>(sminputs.mZ, "QrunTo");
            if(scale != sminputs.mZ)
              result.RunBothToScale(scale);
          #else
            std::ostringstream errmsg;
            errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
            errmsg << "FS models for THDM_flipped not built." << std::endl;
            SpecBit_error().raise(LOCAL_INFO, errmsg.str());
          #endif
          break;
        }
        case TYPE_III:
        {
          // TODO: Implement the typeIII model in FS
          std::ostringstream errmsg;
          errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
          errmsg << "FS model for the general THDM does not exist." << std::endl;
          SpecBit_error().raise(LOCAL_INFO, errmsg.str());
          break;
        }
        default:
        {
          std::ostringstream errmsg;
          errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
          errmsg << "Tried to set an unkwown THDM type." << std::endl;
          SpecBit_error().raise(LOCAL_INFO, errmsg.str());
          break;
        }
      }

      const double scale = runOptions->getValueOrDef<double>(sminputs.mZ, "QrunTo");
      if(scale != sminputs.mZ)
      {
        logger() << "Running spectrum to " << scale << " GeV." << EOM;
        result.RunBothToScale(scale);
      }
    }

    // ----- spectrum generation using SPheno -----

    // get spectrum from spheno and do basic theory constraints
    void get_THDMII_spectrum_SPheno(Spectrum& spectrum)
    {
      namespace myPipe = Pipes::get_THDMII_spectrum_SPheno;


      auto myPipe_Param = myPipe::Param;

      const double lam1 = *myPipe_Param.at("lambda1");
      const double lam2 = *myPipe_Param.at("lambda2");
      const double lam3 = *myPipe_Param.at("lambda3");
      const double lam4 = *myPipe_Param.at("lambda4");
      const double lam5 = *myPipe_Param.at("lambda5");
      const double lam6 = 0, lam7 = 0, lam345 = lam3 + lam4 + lam5;

      // Set up the input structure
      const SMInputs &sminputs = *myPipe::Dep::SMINPUTS;
      Finputs inputs;
      inputs.sminputs = sminputs;
      inputs.param = myPipe_Param;
      inputs.options = myPipe::runOptions;
      
      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cuts = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      
      // Get the spectrum from the Backend
      myPipe::BEreq::SARAHSPheno_gumTHDMII_spectrum(spectrum, inputs);
      
      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");

      // add missing parameters for compatibility with Filip THDM
      auto& he = spectrum.get_HE();

      he.set_override(Par::dimensionless, TYPE_II, "model_type", true);
      he.set_override(Par::mass1, 0, "G0", true);
      he.set_override(Par::mass1, 0, "G+", true);
      he.set_override(Par::dimensionless, 0, "isIDM", true);

      for (int i=1; i<=3; ++i)
      {
        for (int j=1; j<=3; ++j)
        {
          he.set_override(Par::dimensionless, 0.0, "ImYd1", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "ImYu1", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "ImYe1", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "ImYd2", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "ImYu2", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "ImYe2", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "Yd1", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "Yu1", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "Ye1", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "Yd2", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "Yu2", i, j, true);
          he.set_override(Par::dimensionless, 0.0, "Ye2", i, j, true);
        }
      }

      for (int i=1; i<=3; ++i)
      {
        he.set_override(Par::dimensionless, he.get(Par::dimensionless, "Yd", i, i), "Yd1", i, i, true);
        he.set_override(Par::dimensionless, he.get(Par::dimensionless, "Yu", i, i), "Yu2", i, i, true);
        he.set_override(Par::dimensionless, he.get(Par::dimensionless, "Ye", i, i), "Ye1", i, i, true);
      }

      double vev = sqrt(sqr(he.get(Par::dimensionless,"v1")) + sqr(he.get(Par::dimensionless,"v2")));

      he.set_override(Par::dimensionless, spectrum.get(Par::Pole_Mixing, "sinW2"), "sinW2", true);
      he.set_override(Par::mass1, vev, "v", true);
      he.set_override(Par::mass1, he.get(Par::mass1, "v"), "vev", true);
      he.set_override(Par::dimensionless, atan(he.get(Par::dimensionless, "tanb")), "beta", true);

      {
        const double m11_2 = he.get(Par::mass1, "m11_2");
        const double m22_2 = he.get(Par::mass1, "m22_2");
        const double m12_2 = he.get(Par::mass1, "m12_2");
        const double beta = he.get(Par::dimensionless, "beta");
        const double vsq = sqr(he.get(Par::mass1, "v"));
        const double sb = sin(beta), cb = cos(beta), s2b = sin(2.*beta), c2b = cos(2.*beta);
        
        const double M12_2 = (m11_2-m22_2)*s2b + m12_2*c2b;
        const double M11_2 = m11_2*pow(cb,2) + m22_2*pow(sb,2) - m12_2*s2b;
        const double M22_2 = m11_2*pow(sb,2) + m22_2*pow(cb,2) + m12_2*s2b;
        const double Lambda1 = lam1*pow(cb,4) + lam2*pow(sb,4) + 0.5*lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*lam6+pow(sb,2)*lam7);
        const double Lambda2 = lam1*pow(sb,4) + lam2*pow(cb,4) + 0.5*lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*lam6+pow(cb,2)*lam7);
        const double Lambda3 = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam3 - s2b*c2b*(lam6-lam7);
        const double Lambda4 = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam4 - s2b*c2b*(lam6-lam7);
        const double Lambda5 = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam5 - s2b*c2b*(lam6-lam7);
        const double Lambda6 = -0.5*s2b*(lam1*pow(cb,2)-lam2*pow(sb,2)-lam345*c2b) + cb*cos(3.*beta)*lam6 + sb*sin(3.*beta)*lam7;
        const double Lambda7 = -0.5*s2b*(lam1*pow(sb,2)-lam2*pow(cb,2)+lam345*c2b) + sb*sin(3.*beta)*lam6 + cb*cos(3.*beta)*lam7;

        double ba = 0.5*atan2(-2.*Lambda6*vsq,-(sqr(he.get(Par::Pole_Mass,"A0"))+(Lambda5-Lambda1)*vsq));
        double alpha = beta - ba;

        // fix conventions to match FS and THDMC

        // CONVENTION-A: ba in (0,pi), sba in (0,+1), cba in (-1,+1)
        // if (beta-alpha >= M_PI) alpha += M_PI;
        // if (beta-alpha < 0) alpha -= M_PI;

        // CONVENTION-B: ba in (-pi/2,+pi/2), sba in (-1,+1), cba in (0,+1)
        if (beta-alpha >= M_PI/2) alpha += M_PI;
        if (beta-alpha < -M_PI/2) alpha -= M_PI;

        he.set_override(Par::mass1, M11_2, "M11_2", true);
        he.set_override(Par::mass1, M22_2, "M22_2", true);
        he.set_override(Par::mass1, M12_2, "M12_2", true);
        he.set_override(Par::dimensionless, Lambda1, "Lambda1", true);
        he.set_override(Par::dimensionless, Lambda2, "Lambda2", true);
        he.set_override(Par::dimensionless, Lambda3, "Lambda3", true);
        he.set_override(Par::dimensionless, Lambda4, "Lambda4", true);
        he.set_override(Par::dimensionless, Lambda5, "Lambda5", true);
        he.set_override(Par::dimensionless, Lambda6, "Lambda6", true);
        he.set_override(Par::dimensionless, Lambda7, "Lambda7", true);
        he.set_override(Par::dimensionless, alpha, "alpha", true);
        he.set_override(Par::dimensionless, cos(beta-alpha), "cosba", true);

      }
    }

    // // Convert to standard Spectrum_THDM capability
    // void convert_THDM_spectrum_SPheno(Spectrum& spectrum)
    // {
    //   namespace myPipe = Pipes::convert_THDM_spectrum_SPheno;
    //   spectrum = *myPipe::Dep::THDM_spectrum_SPheno;
    // }

    // ----- spectrum info -----

    // Get Spectrum as std::map so that it can be printed
    void get_THDM_spectrum_as_map(std::map<str,double> &specmap)
    {
      using namespace Pipes::get_THDM_spectrum_as_map;
      THDM_TYPE THDM_type = *Dep::THDM_Type;
      namespace myPipe = Pipes::get_THDM_spectrum_as_map;
      const Spectrum &thdmspec(*myPipe::Dep::THDM_spectrum);

      bool print_minimal_yukawas = runOptions->getValueOrDef<bool>(false, "print_minimal_yukawas");
      bool print_Higgs_basis_params = runOptions->getValueOrDef<bool>(true, "print_Higgs_basis_params");
      bool print_running_masses = runOptions->getValueOrDef<bool>(false, "print_running_masses");

      print_Higgs_basis_params = true;

      /// Add everything... use spectrum contents routines to automate task
      static const SpectrumContents::THDM contents;
      static const vector<SpectrumParameter> required_parameters = contents.all_parameters();

      for (vector<SpectrumParameter>::const_iterator it = required_parameters.begin();
            it != required_parameters.end(); ++it)
      {
        const Par::Tags tag = it->tag();
        const std::string name = it->name();
        const vector<int> shape = it->shape();

        // useless stuff
        if (name == "vev" || name == "model_type" || name == "lambda6" || name == "lambda7") continue;

        // // TODO: some stuff not in SPheno??
        // if (name == "W-") continue;
        // if (name == "W+") continue;

        // only enable in final combined fit
        // if (name == "sinW2" || name == "m22_2" || name == "m12_2" || name == "m11_2" || name == "g1" || name == "g2" || name == "g3" || name == "W+") continue;

        // skip Yukawas that are zero for the model being scanned
        if (print_minimal_yukawas)
        {
          if (THDM_type != TYPE_III)
            if (name.rfind("ImY", 0) == 0)
              continue;

          if (THDM_type == TYPE_I)
            if (name.rfind("Yu1", 0) == 0 || name.rfind("Yd1", 0) == 0 || name.rfind("Ye1", 0) == 0)
              continue;

          if (THDM_type == TYPE_II)
            if (name.rfind("Yu1", 0) == 0 || name.rfind("Yd2", 0) == 0 || name.rfind("Ye2", 0) == 0)
              continue;

          if (THDM_type == TYPE_LS)
            if (name.rfind("Yu1", 0) == 0 || name.rfind("Yd1", 0) == 0 || name.rfind("Ye2", 0) == 0)
              continue;

          if (THDM_type == TYPE_flipped)
            if (name.rfind("Yu1", 0) == 0 || name.rfind("Yd2", 0) == 0 || name.rfind("Ye1", 0) == 0)
              continue;
        }

        /// Verification routine should have taken care of invalid shapes etc, so won't check for that here.

        // Check scalar case
        if (shape.size() == 1 and shape[0] == 1)
        {
          std::ostringstream label;
          label << name << " " << Par::toString.at(tag);
          specmap[label.str()] = thdmspec.get_HE().get(tag, name);
        }
        // Check vector case
        else if (shape.size() == 1 and shape[0] > 1)
        {
          for (int i = 1; i <= shape[0]; ++i)
          {
            std::ostringstream label;
            label << name << "_" << i << " " << Par::toString.at(tag);
            specmap[label.str()] = thdmspec.get_HE().get(tag, name, i);
          }
        }
        // Check matrix case
        else if (shape.size() == 2)
        {
          for (int i = 1; i <= shape[0]; ++i)
          {
            for (int j = 1; j <= shape[1]; ++j)
            {
              if (print_minimal_yukawas && THDM_type != TYPE_III && i != j && (name.rfind("Yu", 0) == 0 || name.rfind("Yd", 0) == 0 || name.rfind("Ye", 0) == 0))
                continue;

              std::string name2 = name;
              if (print_minimal_yukawas && THDM_type != TYPE_III)
              {
                if (name2 == "Yu2" || name2 == "Yu1") name2 = "Yu";
                if (name2 == "Yd2" || name2 == "Yd1") name2 = "Yd";
                if (name2 == "Ye2" || name2 == "Ye1") name2 = "Ye";
              }

              std::ostringstream label;
              label << name2 << "_(" << i << "," << j << ") " << Par::toString.at(tag);
              specmap[label.str()] = thdmspec.get_HE().get(tag, name, i, j);
            }
          }
        }
        // Deal with all other cases
        else
        {
          // ERROR
          std::ostringstream errmsg;
          errmsg << "Error, invalid parameter received while converting THDMspectrum to map of strings! This should no be possible if the spectrum content verification routines were working correctly; they must be buggy, please report this.";
          errmsg << "Problematic parameter was: " << tag << ", " << name << ", shape=" << shape;
          utils_error().forced_throw(LOCAL_INFO, errmsg.str());
        }
      }

      // for convenience also print cba, sba
      double beta = thdmspec.get_HE().get(Par::dimensionless, "beta");
      double alpha = thdmspec.get_HE().get(Par::dimensionless, "alpha");

      specmap["sba dimensionless"] = sin(beta - alpha);
      specmap["cba dimensionless"] = cos(beta - alpha);
      specmap["m12_2tree mass1"] = *Param.at("m12_2");

      if (print_Higgs_basis_params)
      {
        // Higgs basis params
        specmap["Lambda1 dimensionless"] = thdmspec.get_HE().get(Par::dimensionless, "Lambda1");
        specmap["Lambda2 dimensionless"] = thdmspec.get_HE().get(Par::dimensionless, "Lambda2");
        specmap["Lambda3 dimensionless"] = thdmspec.get_HE().get(Par::dimensionless, "Lambda3");
        specmap["Lambda4 dimensionless"] = thdmspec.get_HE().get(Par::dimensionless, "Lambda4");
        specmap["Lambda5 dimensionless"] = thdmspec.get_HE().get(Par::dimensionless, "Lambda5");
        specmap["Lambda6 dimensionless"] = thdmspec.get_HE().get(Par::dimensionless, "Lambda6");
        specmap["Lambda7 dimensionless"] = thdmspec.get_HE().get(Par::dimensionless, "Lambda7");
        // specmap["M12_2 mass1"] = thdmspec.get_HE().get(Par::mass1, "M12_2");
        // specmap["M11_2 mass1"] = thdmspec.get_HE().get(Par::mass1, "M11_2");
        specmap["M22_2 mass1"] = thdmspec.get_HE().get(Par::mass1, "M22_2");
      }

      if (print_running_masses)
      {
        // running masses
        specmap["h0_1 mass1"] = thdmspec.get_HE().get(Par::mass1, "h0_1");
        specmap["h0_2 mass1"] = thdmspec.get_HE().get(Par::mass1, "h0_2");
        specmap["A0 mass1"] = thdmspec.get_HE().get(Par::mass1, "A0");
        specmap["H+ mass1"] = thdmspec.get_HE().get(Par::mass1, "H+");
      }

      // TODO: add input params
      // TODO: option for tree-level masses??
      // TODO: LL distribution data
    }

    // Get the Type of THDM from the yukawa structure
    void get_THDM_Type(THDM_TYPE &type)
    {
      using namespace Pipes::get_THDM_Type;
      SMInputs sminputs = *Dep::SMINPUTS;

      // Choose a small value to avoid comparing with 0
      const double eps = 1e-20;

      // Needed to compare masses
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double sb = *Param.at("tanb")/sqrt(1+pow(*Param.at("tanb"),2));

      // Flags
      bool yu_empty = true, yd_empty = true, yl_empty= true;
      bool real = true, diagonal = true;

      const vector<std::string> yuk_base = {"yu2_re", "yu2_im", "yd2_re", "yd2_im", "yl2_re", "yl2_im"};
      for (str yuk : yuk_base)
      {
        for(size_t i=1; i<=3; ++i)
        {
          for(size_t j=1; j<=3; ++j)
          {
            std::stringstream ss;
            ss << yuk << "_" << i << j;
            if(std::abs(*Param.at(ss.str())) > eps)
            {
              // if any element is non-zero, it is not empty
              if(yuk.find("yu") != str::npos)
                yu_empty = false;
              else if(yuk.find("yd") != str::npos)
                yd_empty = false;
              else if(yuk.find("yl") != str::npos)
                yl_empty = false;

              // if any imaginary element is non-zero, it is not real
              if(yuk.find("im") != str::npos)
                real = false;

              // if any off-diagonal element, is non-zero, it is not diagonal
              if(i != j)
                diagonal = false;
            }
          }
        }
      }

      // If all y2 yukawas are non-zero, it is type I
      if (real and diagonal and !yu_empty and !yd_empty and !yl_empty)
      {
        type = TYPE_I;
      }
      // All other specific types have real and diagonal yukawas
      else if (real and diagonal and yd_empty and yl_empty and
                std::abs(*Param.at("yu2_re_11") - sqrt(2)/v/sb*sminputs.mU) < eps and
                std::abs(*Param.at("yu2_re_22") - sqrt(2)/v/sb*sminputs.mCmC) < eps and
                std::abs(*Param.at("yu2_re_33") - sqrt(2)/v/sb*sminputs.mT) < eps)
      {
        type = TYPE_II;
      }
      else if(real and diagonal and yl_empty and
              std::abs(*Param.at("yu2_re_11") - sqrt(2)/v/sb * sminputs.mU) < eps and
              std::abs(*Param.at("yu2_re_22") - sqrt(2)/v/sb * sminputs.mCmC) < eps and
              std::abs(*Param.at("yu2_re_33") - sqrt(2)/v/sb * sminputs.mT) < eps and
              std::abs(*Param.at("yd2_re_11") - sqrt(2)/v/sb * sminputs.mD) < eps and
              std::abs(*Param.at("yd2_re_22") - sqrt(2)/v/sb * sminputs.mS) < eps and
              std::abs(*Param.at("yd2_re_33") - sqrt(2)/v/sb * sminputs.mBmB) < eps)
      {
        type = TYPE_LS;
      }
      else if(real and diagonal and yd_empty and
              std::abs(*Param.at("yu2_re_11") - sqrt(2)/v/sb * sminputs.mU) < eps and
              std::abs(*Param.at("yu2_re_22") - sqrt(2)/v/sb * sminputs.mCmC) < eps and
              std::abs(*Param.at("yu2_re_33") - sqrt(2)/v/sb * sminputs.mT) < eps and
              std::abs(*Param.at("yl2_re_11") - sqrt(2)/v/sb * sminputs.mE) < eps and
              std::abs(*Param.at("yl2_re_22") - sqrt(2)/v/sb * sminputs.mMu) < eps and
              std::abs(*Param.at("yl2_re_33") - sqrt(2)/v/sb * sminputs.mTau) < eps)
      {
        type = TYPE_flipped;
      }
      // Otherwise, it is the generic type
      else
      {
        type = TYPE_III;
      }
    }

    // Get name of the SM-like scalar
    void get_SM_like_scalar(str& result)
    {
      const Spectrum& spectrum = *Pipes::get_SM_like_scalar::Dep::THDM_spectrum;

      if (spectrum.get(Par::dimensionless,"isIDM") == true)
      {
        if (spectrum.get(Par::dimensionless, "cosba") == 0)
          result = "h0_1";
        else
          result = "h0_2";
      }
      else
      {
        if (abs(spectrum.get(Par::Pole_Mass,"h0_1")-125.10) <= abs(spectrum.get(Par::Pole_Mass,"h0_2")-125.10))
          result = "h0_1";
        else
          result = "h0_2";
      }
    }

    // Get name of the non-SM, CP-even scalar
    void get_additional_scalar(str& result)
    {
      if (*Pipes::get_additional_scalar::Dep::SM_like_scalar == "h0_1")
        result = "h0_2";
      else
        result = "h0_1";
    }

    // ----- HIGGS COUPLING TABLE -----

    // Put together the Higgs couplings for the 2HDM, using only partial widths
    void THDM_higgs_couplings_pwid(HiggsCouplingsTable &result)
    {
      using namespace Pipes::THDM_higgs_couplings_pwid;

      // Retrieve spectrum contents
      const Spectrum fullspectrum = *Dep::THDM_spectrum;

      //const DecayTable::Entry& decays = *Dep::Higgs_decay_rates;
      const SubSpectrum &spec = fullspectrum.get_HE();

      // Set up neutral Higgses
      static const vector<std::string> sHneut = initVector<std::string>("h0_1", "h0_2", "A0");
      result.set_n_neutral_higgs(3);

      // Set up charged Higgses
      result.set_n_charged_higgs(1);

      // give higgs indices names
      enum neutral_higgs_indices
      {
          light_higgs, heavy_higgs, CP_odd_higgs, NUMBER_OF_NEUTRAL_HIGGS
      };

      // Set the CP of the Higgs states.
      result.CP[light_higgs] = 1;
      result.CP[heavy_higgs] = 1;
      result.CP[CP_odd_higgs] = -1;

      // Set the decays
      result.set_neutral_decays_SM(light_higgs, sHneut[light_higgs], *Dep::Reference_SM_Higgs_decay_rates);
      result.set_neutral_decays_SM(heavy_higgs, sHneut[heavy_higgs], *Dep::Reference_SM_other_Higgs_decay_rates);
      result.set_neutral_decays_SM(CP_odd_higgs, sHneut[CP_odd_higgs], *Dep::Reference_SM_A0_decay_rates);
      result.set_neutral_decays(light_higgs, sHneut[light_higgs], *Dep::Higgs_decay_rates);
      result.set_neutral_decays(heavy_higgs, sHneut[heavy_higgs], *Dep::h0_2_decay_rates);
      result.set_neutral_decays(CP_odd_higgs, sHneut[CP_odd_higgs], *Dep::A0_decay_rates);
      result.set_charged_decays(light_higgs, "H+", *Dep::H_plus_decay_rates);
      result.set_t_decays(*Dep::t_decay_rates);

      // Use them to compute effective couplings for all neutral higgses, except for hhZ.
      for (int i = 0; i < NUMBER_OF_NEUTRAL_HIGGS; i++)
      {
        result.C_WW[i] = sqrt(result.compute_effective_coupling(i, std::pair<int, int>(24, 0), std::pair<int, int>(-24, 0)));
        result.C_ZZ[i] = sqrt(result.compute_effective_coupling(i, std::pair<int, int>(23, 0), std::pair<int, int>(23, 0)));
        result.C_tt2[i] = result.compute_effective_coupling(i, std::pair<int, int>(6, 1), std::pair<int, int>(-6, 1));
        result.C_bb2[i] = result.compute_effective_coupling(i, std::pair<int, int>(5, 1), std::pair<int, int>(-5, 1));
        result.C_cc2[i] = result.compute_effective_coupling(i, std::pair<int, int>(4, 1), std::pair<int, int>(-4, 1));
        result.C_tautau2[i] = result.compute_effective_coupling(i, std::pair<int, int>(15, 1), std::pair<int, int>(-15, 1));
        result.C_gaga2[i] = result.compute_effective_coupling(i, std::pair<int, int>(22, 0), std::pair<int, int>(22, 0));
        result.C_gg2[i] = result.compute_effective_coupling(i, std::pair<int, int>(21, 0), std::pair<int, int>(21, 0));
        result.C_mumu2[i] = result.compute_effective_coupling(i, std::pair<int, int>(13, 1), std::pair<int, int>(-13, 1));
        result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int, int>(23, 0), std::pair<int, int>(22, 0));
        result.C_ss2[i] = result.compute_effective_coupling(i, std::pair<int, int>(3, 1), std::pair<int, int>(-3, 1));
      }

      // Calculate hhZ effective couplings.  Here we scale out the kinematic prefactor
      // of the decay width, assuming we are well above threshold if the channel is open.
      // If not, we simply assume SM couplings.
      const double mZ = fullspectrum.get(Par::Pole_Mass, 23, 0);
      const double scaling = 8. * sqrt(2.) * pi / fullspectrum.get_SMInputs().GF;
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 3; j++)
        {
          // changed mass1 -> Pole_Mass
          double mhi = spec.get(Par::Pole_Mass, sHneut[i]); //mass1 to be consistent
          double mhj = spec.get(Par::Pole_Mass, sHneut[j]);
          if (mhi > mhj + mZ and result.get_neutral_decays(i).has_channel(sHneut[j], "Z0"))
          {
            double gamma = result.get_neutral_decays(i).width_in_GeV * result.get_neutral_decays(i).BF(sHneut[j], "Z0");
            double k[2] = {(mhj + mZ) / mhi, (mhj - mZ) / mhi};
            for (int l = 0; l < 2; l++)
              k[l] = (1.0 - k[l]) * (1.0 + k[l]);
            double K = mhi * sqrt(k[0] * k[1]);
            result.C_hiZ[i][j] = sqrt(scaling / (K * K * K) * gamma);
          }
          else // If the channel is missing from the decays or kinematically disallowed, just return the SM result.
          {
            result.C_hiZ[i][j] = 1.;
          }
        }
      }

      if (ModelInUse("Inert2"))
      {
        std::string DarkMatter_ID = *Dep::DarkMatter_ID;
        std::string DarkMatterConj_ID = *Dep::DarkMatterConj_ID;
        if (spec.get(Par::Pole_Mass,DarkMatter_ID)*2 < spec.get(Par::Pole_Mass, "h0_2"))
          result.invisibles = std::vector<sspair>({{DarkMatter_ID, DarkMatterConj_ID}});
      }

    }

    // helper to get necessary couplings from 2HDMC for higgs couplings table
    void fill_THDM_couplings_struct(THDM_couplings &couplings, THDMC_1_8_0::THDM &container)
    {
      // todo: save computational time by filling only those required in each case

      // checks a coupling for NaN
      auto check_coupling = [](const complexd coupling)
      {
        if (std::isnan(coupling.real()) || std::isnan(coupling.imag()))
        {
          std::ostringstream msg;
          msg << "SpecBit error: a coupling has evaluated to NaN." << std::endl;
          SpecBit_error().raise(LOCAL_INFO, msg.str());
        }
      };

      // give higgs indices names
      enum neutral_higgs_indices
      {
          light_higgs, heavy_higgs, CP_odd_higgs, NUMBER_OF_NEUTRAL_HIGGS
      };

      // note: the below does not include degenerate charged higgs
      enum charged_higgs_indices
      {
          charged_higgs=3, NUMBER_OF_CHARGED_HIGGS=1
      };

      // the total number of higgs does not include degenerate charged higgs
      const int total_number_of_higgs = NUMBER_OF_NEUTRAL_HIGGS + NUMBER_OF_CHARGED_HIGGS;
      const int total_number_of_fermions = 3;
      const int total_number_of_vector_bosons = 3;

      for (int h = 1; h <= total_number_of_higgs; h++)
      {
        for (int f1 = 1; f1 <= total_number_of_fermions; f1++)
        {
          for (int f2 = 1; f2 <= total_number_of_fermions; f2++)
          {
            container.get_coupling_hdd(h, f1, f2, couplings.hdd_cs[h][f1][f2], couplings.hdd_cp[h][f1][f2]);
            container.get_coupling_huu(h, f1, f2, couplings.huu_cs[h][f1][f2], couplings.huu_cp[h][f1][f2]);
            container.get_coupling_hll(h, f1, f2, couplings.hll_cs[h][f1][f2], couplings.hll_cp[h][f1][f2]);
            check_coupling(couplings.hdd_cs[h][f1][f2] + couplings.hdd_cp[h][f1][f2]);
            check_coupling(couplings.huu_cs[h][f1][f2] + couplings.huu_cp[h][f1][f2]);
            check_coupling(couplings.hll_cs[h][f1][f2] + couplings.hll_cp[h][f1][f2]);
          }
        }

        for (int v1 = 1; v1 <= total_number_of_vector_bosons; v1++)
        {
          for (int v2 = 1; v2 <= total_number_of_vector_bosons; v2++)
          {
            container.get_coupling_vvh(v1, v2, h, couplings.vvh[v1][v2][h]);
            check_coupling(couplings.vvh[v1][v2][h]);
          }
          for (int h2 = 1; h2 <= total_number_of_higgs; h2++)
          {
            container.get_coupling_vhh(v1, h, h2, couplings.vhh[v1][h][h2]);
            check_coupling(couplings.vhh[v1][h][h2]);
          }
        }
      }
    }

    // Put together the Higgs couplings for the 2HDM, using 2HDMC
    void THDM_higgs_couplings_2HDMC(HiggsCouplingsTable &result)
    {
      using namespace Pipes::THDM_higgs_couplings_2HDMC;

      // Retrieve spectrum contents
      const Spectrum fullspectrum = *Dep::THDM_spectrum;

      //const DecayTable::Entry& decays = *Dep::Higgs_decay_rates;
      const SubSpectrum &spec = fullspectrum.get_HE();

      // set up some necessary quantities
      // changed mass1 -> Pole_Mass
      const double vev = spec.get(Par::mass1, "vev");
      const double mW = fullspectrum.get(Par::Pole_Mass, "W+");
      const double g = 2.*mW/vev; // TODO: check this
      const double costw = sqrt(1. - spec.get(Par::dimensionless, "sinW2"));

      // Set up neutral Higgses
      static const vector<std::string> sHneut = initVector<std::string>("h0_1", "h0_2", "A0");
      result.set_n_neutral_higgs(3);

      // Set up charged Higgses
      result.set_n_charged_higgs(1);

        // give higgs indices names
      enum neutral_higgs_indices
      {
          light_higgs, heavy_higgs, CP_odd_higgs, NUMBER_OF_NEUTRAL_HIGGS
      };

      // Set the CP of the Higgs states.  Note that this would need to be more sophisticated to deal with the complex MSSM!
      result.CP[light_higgs] = 1;  //h0_1
      result.CP[heavy_higgs] = 1;  //h0_2
      result.CP[CP_odd_higgs] = -1; //A0

      // Set the decays
      result.set_neutral_decays_SM(light_higgs, sHneut[light_higgs], *Dep::Reference_SM_Higgs_decay_rates);
      result.set_neutral_decays_SM(heavy_higgs, sHneut[heavy_higgs], *Dep::Reference_SM_other_Higgs_decay_rates);
      result.set_neutral_decays_SM(CP_odd_higgs, sHneut[CP_odd_higgs], *Dep::Reference_SM_A0_decay_rates);
      result.set_neutral_decays(light_higgs, sHneut[light_higgs], *Dep::Higgs_decay_rates);
      result.set_neutral_decays(heavy_higgs, sHneut[heavy_higgs], *Dep::h0_2_decay_rates);
      result.set_neutral_decays(CP_odd_higgs, sHneut[CP_odd_higgs], *Dep::A0_decay_rates);
      result.set_charged_decays(light_higgs, "H+", *Dep::H_plus_decay_rates);
      result.set_t_decays(*Dep::t_decay_rates);

      // Use the branching fractions to compute gluon, gamma/Z effective couplings
      for (int i = 0; i < NUMBER_OF_NEUTRAL_HIGGS; i++)
      {
        result.C_gg2[i] = result.compute_effective_coupling(i, std::pair<int, int>(21, 0), std::pair<int, int>(21, 0));
        result.C_gaga2[i] = result.compute_effective_coupling(i, std::pair<int, int>(22, 0), std::pair<int, int>(22, 0));
        result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int, int>(23, 0), std::pair<int, int>(22, 0)); // WARNING: will break if scalar mass falls below Z mass
      }

      // Initiate 2HDM container
      THDMsafe container;
      BEreq::setup_thdmc_spectrum(container, *Dep::THDM_spectrum);

      // set up and fill the THDM couplings
      THDM_couplings couplings;
      fill_THDM_couplings_struct(couplings, container.obj);

      // SM-like couplings
      vector<THDM_couplings> couplings_SM_like;
      THDM_couplings SM_couplings; // WARNING: sould be using coupling table

      // so we are getting the sm-like couplings for each scalar; h,H,A

      // loop over each neutral higgs
      for (int h = 1; h <= NUMBER_OF_NEUTRAL_HIGGS; h++)
      {
        // init an SM like container for each neutral higgs
        THDMsafe container;
        BEreq::setup_thdmc_sm_like_spectrum(container, *Dep::THDM_spectrum, byVal(fullspectrum.get_HE().get(Par::Pole_Mass,sHneut[h-1])));
        fill_THDM_couplings_struct(SM_couplings, container.obj);
        couplings_SM_like.push_back(SM_couplings);
      }

      // declare couplings
      double cs, cp;

      // Use couplings to get effective fermion & diboson couplings
      for (int h = 1; h <= NUMBER_OF_NEUTRAL_HIGGS; h++)
      {
        // s
        cs = (couplings.hdd_cs[h][2][2].imag() / couplings_SM_like[h - 1].hdd_cs[1][2][2].imag());
        cp = -(couplings.hdd_cp[h][2][2].real() / couplings_SM_like[h - 1].hdd_cs[1][2][2].imag());
        result.C_ss_s[h - 1] = cs;
        result.C_ss_p[h - 1] = cp;
        result.C_ss2[h - 1] = pow(cs, 2) + pow(cp, 2);
        // b
        cs = (couplings.hdd_cs[h][3][3].imag() / couplings_SM_like[h - 1].hdd_cs[1][3][3].imag());
        cp = -(couplings.hdd_cp[h][3][3].real() / couplings_SM_like[h - 1].hdd_cs[1][3][3].imag());
        result.C_bb_s[h - 1] = cs;
        result.C_bb_p[h - 1] = cp;
        result.C_bb2[h - 1] = pow(cs, 2) + pow(cp, 2);
        // c
        cs = (couplings.huu_cs[h][2][2].imag() / couplings_SM_like[h - 1].huu_cs[1][2][2].imag());
        cp = -(couplings.huu_cp[h][2][2].real() / couplings_SM_like[h - 1].huu_cs[1][2][2].imag());
        result.C_cc_s[h - 1] = cs;
        result.C_cc_p[h - 1] = cp;
        result.C_cc2[h - 1] = pow(cs, 2) + pow(cp, 2);
        // t
        cs = (couplings.huu_cs[h][3][3].imag() / couplings_SM_like[h - 1].huu_cs[1][3][3].imag());
        cp = -(couplings.huu_cp[h][3][3].real() / couplings_SM_like[h - 1].huu_cs[1][3][3].imag());
        result.C_tt_s[h - 1] = cs;
        result.C_tt_p[h - 1] = cp;
        result.C_tt2[h - 1] = pow(cs, 2) + pow(cp, 2);
        // mu
        cs = (couplings.hll_cs[h][2][2].imag() / couplings_SM_like[h - 1].hll_cs[1][2][2].imag());
        cp = -(couplings.hll_cp[h][2][2].real() / couplings_SM_like[h - 1].hll_cs[1][2][2].imag());
        result.C_mumu_s[h - 1] = cs;
        result.C_mumu_p[h - 1] = cp;
        result.C_mumu2[h - 1] = pow(cs, 2) + pow(cp, 2);
        // tautau
        cs = (couplings.hll_cs[h][3][3].imag() / couplings_SM_like[h - 1].hll_cs[1][3][3].imag());
        cp = -(couplings.hll_cp[h][3][3].real() / couplings_SM_like[h - 1].hll_cs[1][3][3].imag());
        result.C_tautau_s[h - 1] = cs;
        result.C_tautau_p[h - 1] = cp;
        result.C_tautau2[h - 1] = pow(cs, 2) + pow(cp, 2);
        // Z
        result.C_ZZ[h - 1] = couplings.vvh[2][2][h].imag() / couplings_SM_like[h - 1].vvh[2][2][1].imag();
        // W
        result.C_WW[h - 1] = couplings.vvh[3][3][h].imag() / couplings_SM_like[h - 1].vvh[3][3][1].imag();

        for (int h2 = 1; h2 <= NUMBER_OF_NEUTRAL_HIGGS; h2++)
        {
          result.C_hiZ[h - 1][h2 - 1] = (couplings.vhh[2][h][h2].real()) / (g / 2. / costw);
        }

      }

      if (ModelInUse("Inert2"))
      {
        str DarkMatter_ID = *Dep::DarkMatter_ID;
        str DarkMatterConj_ID = *Dep::DarkMatterConj_ID;
        if (spec.get(Par::Pole_Mass,DarkMatter_ID)*2 < spec.get(Par::Pole_Mass, "h0_2"))
          result.invisibles = std::vector<sspair>({{DarkMatter_ID, DarkMatterConj_ID}});
      }

      // HiggsCouplingsTable tmp;
      // THDM_higgs_couplings_pwid(tmp);

      // std::cerr << "---- THDMC ----" << std::endl;
      // result.print();

    }

    // ----- SCALAR-SCALAR COUPLING TABLE -----

    // print differences btween two coupling tables
    bool compareCouplingTable(const CouplingTable& A, const CouplingTable& B)
    {
      bool allMatch = true;

      for (auto& pair : A.table)
      {
        auto name = rjust(join(pair.first,","),30);
        auto valA = pair.second;

        if (B.table.find(pair.first) != B.table.end())
        {
          auto valB = B.table.at(pair.first);

          if (abs(real(valA) - real(valB)) < 1e-5 && abs(imag(valA) - imag(valB)) < 1e-5)
          {
            // std::cerr << " match " << name << "  " << valA << std::endl;
          }
          else if (abs(abs(valA) - abs(valB)) < 1e-5)
          {
            // std::cerr << " sign  " << name << "  " << valA << "  " << valB << std::endl;
          }
          else
          {
            // std::cerr << " diff  " << name << "  " << valA << "  " << valB << std::endl;
            allMatch = false;
          }
        }
        else
        {
          // std::cerr << " missing " << name << "  " << valA << std::endl;
        }
      }

      return allMatch;
    }

    // get the 2HDM BSM coupling table (using the physical basis)
    // TODO: This function seems incomplete many couplings are missing
    void get_coupling_table_using_physical_basis(CouplingTable& result)
    {
      // Reference:
      // https://arxiv.org/pdf/hep-ph/9701257.pdf
      // https://arxiv.org/pdf/hep-ph/0206205.pdf
      // https://arxiv.org/pdf/1512.04567.pdf

      using namespace Pipes::get_coupling_table_using_physical_basis;

      // define the calculator function
      CouplingTable::CalcFunc calculator = [](const Spectrum& spec, CouplingTable& coup)
      {
        // get spectrum parameters (all at scale of spec)
        auto& he = spec.get_HE();
        double mh2   = sqr(he.get(Par::mass1, "h0_1"));
        double mH2   = sqr(he.get(Par::mass1, "h0_2"));
        double mA2   = sqr(he.get(Par::mass1, "A0"));
        double mC2   = sqr(he.get(Par::mass1, "H+"));
        double m122  = he.get(Par::mass1, "m12_2");
        double alpha = he.get(Par::dimensionless, "alpha");
        double beta  = he.get(Par::dimensionless, "beta");
        double vev   = he.get(Par::mass1, "vev");

        // angle expressions
        double cb    = cos(beta), ca = cos(alpha), sb = sin(beta), sa = sin(alpha);
        double sinD  = sin(alpha - beta), cosD = cos(alpha - beta);
        double sinE  = sin(alpha + beta), cosE = cos(alpha + beta);
        double sinD2 = sqr(sinD), cosD2 = sqr(cosD);
        double sinE2 = sqr(sinE), cosE2 = sqr(cosE);
        double sin2D = sin(2*(alpha-beta)), cos2D = cos(2*(alpha-beta));
        // double sin2E = sin(2*(alpha+beta)); , cos2E = cos(2*(alpha+beta));
        // double s2E2  = sqr(sin2E);
        double Aab   = cub(cb)*sa + cub(sb)*ca;
        double Bab   = cub(cb)*ca - cub(sb)*sa;
        double Cab   = cub(sa)*cb + cub(ca)*sb;
        double Dab   = cub(ca)*cb - cub(sa)*sb;
        double Aab2  = sqr(Aab), Bab2 = sqr(Bab), Cab2 = sqr(Cab), Dab2 = sqr(Dab);
        double s2b   = sin(2*beta), s2a = sin(2*alpha);
        double c2b   = cos(2*beta);//, c2a = cos(2*alpha);
        double s2b2  = sqr(s2b), s2a2 = sqr(s2a);
        double c2b2  = sqr(c2b); //, c2a2 = sqr(c2a);
        double Eab   = 3*sa*ca+sb*cb;
        double Fab   = 3*sa*ca-sb*cb;
        // double EabX  = 3*sqr(sa)*sqr(ca)+sqr(sb)*sqr(cb);
        double FabX  = 3*sqr(sa)*sqr(ca)-sqr(sb)*sqr(cb);

        // pre-factors
        auto C1 = -2.*ii/vev;
        auto C2 = -ii*4./sqr(vev);

        // name of each scalar
        const static std::string h = "h0_1", H = "h0_2", A = "A0", Hp = "H+", Hm = "H-", G = "G0", Gp = "G+", Gm = "G-";

        // GET CUBIC COUPLINGS

        coup.insert({h,Hp,Hm}, (+C1)*((mh2/s2b)*Bab-mC2*sinD-2*cosE*m122/s2b2));
        coup.insert({H,Hp,Hm}, (+C1)*((mH2/s2b)*Aab+mC2*cosD-2*sinE*m122/s2b2));
        coup.insert({h,A,A},   (+C1)*((mh2/s2b)*Bab-mA2*sinD-2*cosE*m122/s2b2));
        coup.insert({H,A,A},   (+C1)*((mH2/s2b)*Aab+mA2*cosD-2*sinE*m122/s2b2));

        coup.insert({h,h,h},   (+C1*3.)*((mh2/s2b)*Dab-2*cosD2*cosE*m122/s2b2));
        coup.insert({H,H,H},   (+C1*3.)*((mH2/s2b)*Cab-2*sinD2*sinE*m122/s2b2));

        coup.insert({h,H,H},   (+C1/2.)*(+s2a*sinD*(2*mH2+mh2)/s2b-4*Eab*sinD*m122/s2b2));
        coup.insert({h,h,H},   (+C1/2.)*(+s2a*cosD*(2*mh2+mH2)/s2b-4*Fab*cosD*m122/s2b2));

        coup.insert({h,Hm,Gp}, (-C1/2.)*cosD*(mh2-mC2));
        coup.insert({h,Hp,Gm}, (-C1/2.)*cosD*(mh2-mC2));
        coup.insert({H,Hm,Gp}, (-C1/2.)*sinD*(mH2-mC2));
        coup.insert({H,Hp,Gm}, (-C1/2.)*sinD*(mH2-mC2));
        coup.insert({h,A,G},   (-C1/2.)*cosD*(mh2-mA2));
        coup.insert({H,A,G},   (-C1/2.)*sinD*(mH2-mA2));

        coup.insert({h,G,G},   (-C1/2.)*sinD*mh2);
        coup.insert({h,Gp,Gm}, (-C1/2.)*sinD*mh2);
        coup.insert({H,G,G},   (+C1/2.)*cosD*mH2);
        coup.insert({H,Gp,Gm}, (+C1/2.)*cosD*mH2);

        coup.insert({A,Hm,Gp}, (+ii*C1/2.)*(mA2-mC2)); // sign
        coup.insert({A,Hp,Gm}, (-ii*C1/2.)*(mA2-mC2)); // sign

        // GET QUARTIC COUPLINGS

        coup.insert({Hp,Hm,Hp,Hm},       (+2.*C2)*(1./s2b2)*(mH2*Aab2+mh2*Bab2-2*c2b2*m122/s2b));
        coup.insert({A,A,A,A},           (+3.*C2)*(1./s2b2)*(mH2*Aab2+mh2*Bab2-2*c2b2*m122/s2b));
        coup.insert({A,A,Hp,Hm},            (+C2)*(1./s2b2)*(mH2*Aab2+mh2*Bab2-2*c2b2*m122/s2b));

        coup.insert({h,h,Hp,Hm},       (+1/2.*C2)*(1./s2b2*(+mH2*Aab*s2a*cosD+2*mh2*Bab*Dab+1*s2b2*mC2*sinD2-1*(s2b2*sinD2+4*Bab2)/s2b*m122)));
        coup.insert({H,H,Hp,Hm},       (+1/2.*C2)*(1./s2b2*(+mh2*Bab*s2a*sinD+2*mH2*Aab*Cab+1*s2b2*mC2*cosD2-2*(c2b2*sinD2+sinE2)/s2b*m122)));
        coup.insert({h,h,A,A},         (+1/2.*C2)*(1./s2b2*(+mH2*Aab*s2a*cosD+2*mh2*Bab*Dab+1*s2b2*mA2*sinD2-1*(s2b2*sinD2+4*Bab2)/s2b*m122)));
        coup.insert({H,H,A,A},         (+1/2.*C2)*(1./s2b2*(+mh2*Bab*s2a*sinD+2*mH2*Aab*Cab+1*s2b2*mA2*cosD2-2*(c2b2*sinD2+sinE2)/s2b*m122)));

        coup.insert({h,H,A,A},         (+1/2.*C2)*(1./s2b2*(mH2*Aab*s2a*sinD+mh2*Bab*s2a*cosD)-0.5*mA2*sin2D-1*(2*s2a*c2b-2*s2b2*sinD*cosD)/s2b*m122/s2b2));
        coup.insert({h,H,Hp,Hm},       (+1/2.*C2)*(1./s2b2*(mH2*Aab*s2a*sinD+mh2*Bab*s2a*cosD)-0.5*mC2*sin2D-1*(2*s2a*c2b-2*s2b2*sinD*cosD)/s2b*m122/s2b2));

        coup.insert({h,h,h,h},         (+3/4.*C2)*(1./s2b2)*(+4*mh2*Dab2+mH2*s2a2*cosD2-8*cosD2*cosE2*m122/s2b));
        coup.insert({H,H,H,H},         (+3/4.*C2)*(1./s2b2)*(+4*mH2*Cab2+mh2*s2a2*sinD2-8*sinD2*sinE2*m122/s2b));

        coup.insert({h,h,h,H},         (+3/8.*C2)*(1./s2b2)*(4*mh2*Dab*s2a*cosD+mH2*s2a2*sin2D-8*cosE*m122*s2a*cosD/s2b));
        coup.insert({h,H,H,H},         (+3/8.*C2)*(1./s2b2)*(4*mH2*Cab*s2a*sinD+mh2*s2a2*sin2D-8*sinE*m122*s2a*sinD/s2b));

        coup.insert({h,h,H,H},         (+1/4.*C2)*(s2a/s2b)*(mH2-mh2+3.*s2a/s2b*(sinD2*mH2+cosD2*mh2)-8./s2a/s2b2*FabX*m122));

        // coup.insert({A,A,G,G},         (-1/4.*C2)*(s2a/s2b*(mH2-mh2)+3*(sinD2*mH2+cosD2*mh2))); // wrong

        // coup.insert({Hp,Hm,Gp,Gm},     (-1/4.*C2)*(s2a/s2b*(mH2-mh2)+3*(sinD2*mH2+cosD2*mh2)+mA2)); // wrong

        coup.insert({Hp,Hp,Gm,Gm},     (+1/2.*C2)*(-mA2+sinD2*mH2+cosD2*mh2));
        coup.insert({Hm,Hm,Gp,Gp},     (+1/2.*C2)*(-mA2+sinD2*mH2+cosD2*mh2));
        // coup.insert({Hp,Hm,A,G},       (-1/2.*C2)*(-mC2+sinD2*mH2+cosD2*mh2)); // wrong

        // coup.insert({Gp,Gm,A,A},       (-1/2.*C2)*(mC2+1./s2b*(cosD*Aab*mH2-sinD*Bab*mh2))); // wrong
        // coup.insert({Hp,Hm,G,G},       (-1/2.*C2)*(mC2+1./s2b*(cosD*Aab*mH2-sinD*Bab*mh2))); // wrong

        // coup.insert({Hp,Hm,Hm,Gp},          (-C2)*(sinD/s2b*(Aab*mH2+Bab*mh2))); // wrong
        // coup.insert({Hp,Hm,Hp,Gm},          (-C2)*(sinD/s2b*(Aab*mH2+Bab*mh2))); // wrong
        // coup.insert({Hp,Hm,G,A},       (-1/2.*C2)*(sinD/s2b*(Aab*mH2+Bab*mh2))); // wrong
        // coup.insert({A,A,A,G},         (-3/2.*C2)*(sinD/s2b*(Aab*mH2+Bab*mh2))); // wrong
        // coup.insert({A,A,Hm,Gp},       (-1/2.*C2)*(sinD/s2b*(Aab*mH2+Bab*mh2))); // wrong
        // coup.insert({A,A,Hp,Gm},       (-1/2.*C2)*(sinD/s2b*(Aab*mH2+Bab*mh2))); // wrong

        coup.insert({Gp,Gm,G,A},       (+1/8.*C2)*(sin2D*(mH2-mh2)));
        coup.insert({Gp,Gm,Hm,Gp},     (-1/4.*C2)*(sin2D*(mH2-mh2)));
        coup.insert({Gp,Gm,Hp,Gm},     (-1/4.*C2)*(sin2D*(mH2-mh2)));
        coup.insert({G,G,G,A},         (-3/8.*C2)*(sin2D*(mH2-mh2)));
        coup.insert({G,G,Hm,Gp},       (-1/8.*C2)*(sin2D*(mH2-mh2)));
        coup.insert({G,G,Hp,Gm},       (-1/8.*C2)*(sin2D*(mH2-mh2)));

        // coup.insert({Gp,Gm,h,h},       (-1/4.*C2)*(1/s2b*(s2a*cosD2*mH2-2*sinD*Dab*mh2)+2*cosD2*mC2)); // wrong
        // coup.insert({G,G,h,h},         (-1/4.*C2)*(1/s2b*(s2a*cosD2*mH2-2*sinD*Dab*mh2)+2*cosD2*mA2)); // wrong

        // coup.insert({Gp,Gm,H,H},       (-1/4.*C2)*(1/s2b*(-s2a*sinD2*mh2+2*cosD*Cab*mH2)+2*sinD2*mC2)); // wrong
        // coup.insert({G,G,H,H},         (-1/4.*C2)*(1/s2b*(-s2a*sinD2*mh2+2*cosD*Cab*mH2)+2*sinD2*mA2)); // wrong

        // coup.insert({Hm,Gp,H,H},       (-1/8.*C2)*(1/s2b*(s2a*sin2D*mh2+4*cosD*Cab*mH2)-2*sin2D*mC2)); // wrong
        // coup.insert({Hp,Gm,H,H},       (-1/8.*C2)*(1/s2b*(s2a*sin2D*mh2+4*cosD*Cab*mH2)-2*sin2D*mC2)); // wrong
        // coup.insert({Hm,Gp,h,h},       (-1/8.*C2)*(1/s2b*(s2a*sin2D*mH2+4*cosD*Dab*mh2)+2*sin2D*mC2)); // wrong
        // coup.insert({Hp,Gm,h,h},       (-1/8.*C2)*(1/s2b*(s2a*sin2D*mH2+4*cosD*Dab*mh2)+2*sin2D*mC2)); // wrong
        // coup.insert({A,G,H,H},         (-1/8.*C2)*(1/s2b*(s2a*sin2D*mh2+4*cosD*Cab*mH2)-2*sin2D*mA2)); // wrong
        // coup.insert({A,G,h,h},         (-1/8.*C2)*(1/s2b*(s2a*sin2D*mH2+4*cosD*Dab*mh2)+2*sin2D*mA2)); // wrong

        coup.insert({Gm,Hp,h,A},       (+ii*(1/4.)*C2)*(sinD*(mA2-mC2)));
        coup.insert({Gp,Hm,h,A},       (-ii*(1/4.)*C2)*(sinD*(mA2-mC2)));
        coup.insert({Gm,Hp,h,G},       (-ii*(1/4.)*C2)*(cosD*(mA2-mC2)));
        coup.insert({Gp,Hm,h,G},       (+ii*(1/4.)*C2)*(cosD*(mA2-mC2)));
        coup.insert({Gm,Hp,H,A},       (-ii*(1/4.)*C2)*(cosD*(mA2-mC2)));
        coup.insert({Gp,Hm,H,A},       (+ii*(1/4.)*C2)*(cosD*(mA2-mC2)));
        coup.insert({Gm,Hp,H,G},       (-ii*(1/4.)*C2)*(sinD*(mA2-mC2)));
        coup.insert({Gp,Hm,H,G},       (+ii*(1/4.)*C2)*(sinD*(mA2-mC2)));

        // coup.insert({Gp,Gm,h,H},       (-1/8.*C2)*(s2a/s2b*(mH2-mh2)+2*sin2D*mC2)); // wrong
        // coup.insert({G,G,h,H},         (-1/8.*C2)*(s2a/s2b*(mH2-mh2)+2*sin2D*mA2)); // wrong

        // coup.insert({Gm,Hp,h,H},       (-1/4.*C2)*(s2a/s2b*(sinD2*mH2+cosD2*mh2)-cos2D*mC2)); // wrong
        // coup.insert({Gp,Hm,h,H},       (-1/4.*C2)*(s2a/s2b*(sinD2*mH2+cosD2*mh2)-cos2D*mC2)); // wrong
        // coup.insert({A,G,h,H},         (-1/4.*C2)*(s2a/s2b*(sinD2*mH2+cosD2*mh2)-cos2D*mA2)); // wrong

        // coup.insert({Gp,Gm,Gp,Gm},     (+1/4.*C2)*(sinD2*mh2+cosD2*mH2)); // wrong
        coup.insert({G,G,G,G},         (+3/4.*C2)*(sinD2*mh2+cosD2*mH2));
        coup.insert({Gp,Gm,G,G},       (+1/4.*C2)*(sinD2*mh2+cosD2*mH2));

        // https://arxiv.org/pdf/1512.04567.pdf

        {
          // double sba = sin(beta-alpha);
          // double cba = cos(beta-alpha);
          // double sbap = sin(beta+alpha);
          // double cbap = cos(beta+alpha);
          // double sbi = 1./sb, cbi = 1./cb;
          // double sinD4 = sqr(sinD2), cosD4 = sqr(cosD2);
          // double sinD3 = sinD2*sba, cosD3 = cosD2*cba;;

          // double s3bap = sin(3*beta+alpha), c3bap = cos(3*beta+alpha);
          // double s3b3a = sin(3*beta-3*alpha), c3b3a = cos(3*beta-3*alpha);
          // double sb3ap = sin(beta+3*alpha), cb3ap = cos(beta+3*alpha);
          // double t2bi = 1./tan(2*beta);

          // coup.insert({h,Gp,Gm}, -ii*(1/vev)*mh2*sba);
          // coup.insert({h,G,G},   -ii*(1/vev)*mh2*sba);
          // coup.insert({H,Gp,Gm}, -ii*(1/vev)*mH2*cba);
          // coup.insert({H,G,G},   -ii*(1/vev)*mH2*cba);
          // coup.insert({h,Gp,Hm}, -ii*(1/vev)*(mh2-mC2)*cba); // sign
          // coup.insert({h,G,A},   -ii*(1/vev)*(mh2-mA2)*cba); // sign
          // coup.insert({H,Gp,Hm}, ii*(1/vev)*(mH2-mC2)*sba); // sign
          // coup.insert({H,G,A},   ii*(1/vev)*(mH2-mA2)*sba); // sign
          // coup.insert({A,Gp,Hm}, -ii*ii*(1/vev)*(mA2-mC2));
          // coup.insert({h,Hp,Hm}, ii*(1/vev)*(sbi*cbi*(m122*cbap*sbi*cbi-mh2*c2b*cba)-(mh2+2*mC2)*sba));
          // coup.insert({h,A,A},   ii*(1/vev)*(sbi*cbi*(m122*cbap*sbi*cbi-mh2*c2b*cba)-(mh2+2*mA2)*sba));
          // coup.insert({H,Hp,Hm}, ii*(1/vev)*(sbi*cbi*(m122*sbap*sbi*cbi+mH2*c2b*sba)-(mH2+2*mC2)*cba));
          // coup.insert({H,A,A},   ii*(1/vev)*(sbi*cbi*(m122*sbap*sbi*cbi+mH2*c2b*sba)-(mH2+2*mA2)*cba));
          // coup.insert({h,h,h},   ii*(1/(4*s2b2*vev/3))*(16*m122*cbap*cosD2-mh2*(3*s3bap+3*sba+s3b3a+sb3ap)));
          // coup.insert({H,H,H},   ii*(1/(4*s2b2*vev/3))*(16*m122*sbap*sinD2+mH2*(3*c3bap-3*cba+c3b3a-cb3ap)));
          // coup.insert({h,h,H},   ii*(1/(s2b*vev))*(-cba*(+2*m122+(mH2+2*mh2-3*m122*sbi*cbi)*s2a)));
          // coup.insert({h,H,H},   ii*(1/(s2b*vev))*(+sba*(-2*m122+(mh2+2*mH2-3*m122*sbi*cbi)*s2a)));

          // coup.insert({h,h,G,G}, -ii*(1/sqr(vev))*(mH2*cosD4+2*(mh2-mH2)*cosD3*sba*t2bi+mh2*sinD4+cosD2*(2*mA2-2*m122*sbi*cbi+(3*mh2-mH2)*sinD2)));
          // coup.insert({H,H,G,G}, -ii*(1/sqr(vev))*(mH2*cosD4+2*(mh2-mH2)*sinD3*cba*t2bi+mh2*sinD4+sinD2*(2*mA2-2*m122*sbi*cbi+(3*mH2-mh2)*cosD2)));

        }

      };

      Spectrum spectrum = *Dep::THDM_spectrum;
      result.init(spectrum, calculator);
      result.update();

      // compareCouplingTable(ctmp,result);
      // std::cerr << "---------" << std::endl;
      // compareCouplingTable(result,ctmp);
    }

    // get the 2HDM BSM coupling table (using the THDMC)
    void get_coupling_table_THDMC(CouplingTable& result)
    {
      // Reference: https://arxiv.org/pdf/0902.0851.pdf

      using namespace Pipes::get_coupling_table_THDMC;

      thread_local THDMsafe container;

      // define the calculator function
      CouplingTable::CalcFunc calculator = [&](const Spectrum& spec, CouplingTable& coup)
      {
        BEreq::setup_thdmc_spectrum(container, spec);
        auto& obj = container.obj;

        // particle integers (for 2HDMC only)
        const static int h=1, H=2, A=3, Hp=4;

        // particle strings ('n' for name of)
        const static std::string nh = "h0_1", nH = "h0_2", nA = "A0", nHp = "H+", nHm = "H-", nG = "G0", nGp = "G+", nGm = "G-";

        // for temporary result
        complexd tmp;

        // -- hhh couplings --

        obj.get_coupling_hhh(h,Hp,Hp, tmp); coup.insert({nh,nHp,nHm}, tmp);
        obj.get_coupling_hhh(H,Hp,Hp, tmp); coup.insert({nH,nHp,nHm}, tmp);
        obj.get_coupling_hhh(h,A,A,   tmp); coup.insert({nh,nA,nA}, tmp);
        obj.get_coupling_hhh(H,A,A,   tmp); coup.insert({nH,nA,nA}, tmp);
        obj.get_coupling_hhh(h,h,h,   tmp); coup.insert({nh,nh,nh}, tmp);
        obj.get_coupling_hhh(H,H,H,   tmp); coup.insert({nH,nH,nH}, tmp);
        obj.get_coupling_hhh(h,H,H,   tmp); coup.insert({nh,nH,nH}, tmp);
        obj.get_coupling_hhh(h,h,H,   tmp); coup.insert({nh,nh,nH}, tmp);

        // -- hhhh couplings --

        obj.get_coupling_hhhh(Hp,Hp,Hp,Hp, tmp); coup.insert({nHp,nHm,nHp,nHm}, tmp);
        obj.get_coupling_hhhh(A,A,A,A,     tmp); coup.insert({nA,nA,nA,nA}, tmp);
        obj.get_coupling_hhhh(A,A,Hp,Hp,   tmp); coup.insert({nA,nA,nHp,nHm}, tmp);
        obj.get_coupling_hhhh(h,h,Hp,Hp,   tmp); coup.insert({nh,nh,nHp,nHm}, tmp);
        obj.get_coupling_hhhh(H,H,Hp,Hp,   tmp); coup.insert({nH,nH,nHp,nHm}, tmp);
        obj.get_coupling_hhhh(h,h,A,A,     tmp); coup.insert({nh,nh,nA,nA}, tmp);
        obj.get_coupling_hhhh(H,H,A,A,     tmp); coup.insert({nH,nH,nA,nA}, tmp);
        obj.get_coupling_hhhh(h,H,Hp,Hp,   tmp); coup.insert({nh,nH,nHp,nHm}, tmp);
        obj.get_coupling_hhhh(h,H,A,A,     tmp); coup.insert({nh,nH,nA,nA}, tmp);
        obj.get_coupling_hhhh(h,h,h,h,     tmp); coup.insert({nh,nh,nh,nh}, tmp);
        obj.get_coupling_hhhh(H,H,H,H,     tmp); coup.insert({nH,nH,nH,nH}, tmp);
        obj.get_coupling_hhhh(h,h,h,H,     tmp); coup.insert({nh,nh,nh,nH}, tmp);
        obj.get_coupling_hhhh(h,H,H,H,     tmp); coup.insert({nh,nH,nH,nH}, tmp);
        obj.get_coupling_hhhh(h,h,H,H,     tmp); coup.insert({nh,nh,nH,nH}, tmp);
      };

      result.init(*Dep::THDM_spectrum, calculator);
      result.update();

      // compareCouplingTable(ctmp,result);
      // std::cerr << "---------" << std::endl;
      // compareCouplingTable(result,ctmp);
    }

    // get the 2HDM BSM coupling table (using the Higgs basis)
    void get_coupling_table_using_Higgs_basis(CouplingTable& result)
    {
      // Reference:
      // https://arxiv.org/pdf/hep-ph/0504050.pdf
      // https://arxiv.org/pdf/hep-ph/0602242.pdf
      // https://arxiv.org/pdf/1011.6188.pdf

      using namespace Pipes::get_coupling_table_using_Higgs_basis;
      // bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      bool is_FS_model = false;

      // define the calculator function
      CouplingTable::CalcFunc calculator = [&](const Spectrum& spec, CouplingTable& coup)
      {
        // get spectrum parameters (all at scale of spec)
        auto& he = spec.get_HE();
        double Y2 = he.get(Par::mass1, "M22_2");
        double Z1 = he.get(Par::dimensionless, "Lambda1");
        double Z2 = he.get(Par::dimensionless, "Lambda2");
        double Z3 = he.get(Par::dimensionless, "Lambda3");
        double Z4 = he.get(Par::dimensionless, "Lambda4");
        double Z5 = he.get(Par::dimensionless, "Lambda5");
        double Z6 = -he.get(Par::dimensionless, "Lambda6");
        double Z7 = -he.get(Par::dimensionless, "Lambda7");
        double vev   = he.get(Par::mass1, "vev");
        double alpha = he.get(Par::dimensionless, "alpha");
        double beta  = he.get(Par::dimensionless, "beta");
        double mh2 = sqr(he.get(Par::mass1, "h0_1"));
        double mH2 = sqr(he.get(Par::mass1, "h0_2"));
        double mA2 = sqr(he.get(Par::mass1, "A0"));

        // flag if Z2 symmetric
        bool is_Z2 = (abs(he.get(Par::dimensionless, "lambda6")) < 1e-5
                  && abs(he.get(Par::dimensionless, "lambda7")) < 1e-5) ? true : false;

        // get mass matrix for h,H,A (at scale of spec)
        double Z345    = Z3 + Z4 + real(Z5);
        double Z345bar = Z3 + Z4 - real(Z5);

        // alternative calculation of Y2 (for CP-conserving models only)
        // seems to fix problems with FS
        Y2 = mA2 - sqr(vev)/2.*(Z3+Z4-Z5);

        {
          double lam1 = he.get(Par::dimensionless, "lambda1");
          double lam2 = he.get(Par::dimensionless, "lambda2");
          double lam3 = he.get(Par::dimensionless, "lambda3");
          double lam4 = he.get(Par::dimensionless, "lambda4");
          double lam5 = he.get(Par::dimensionless, "lambda5");
          double lam6 = he.get(Par::dimensionless, "lambda6");
          double lam7 = he.get(Par::dimensionless, "lambda7");
          double lam345 = lam3+lam4+lam5;
          double cb = cos(beta), sb = sin(beta);
          double cb2 = sqr(cb), sb2 = sqr(sb);
          double v2 = sqr(vev);
          double c2b = cos(2*beta), s2b = sin(2*beta);
          double tb = tan(beta);
          double ctb = 1./tb;

          // generic basis
          double m122 = (mA2 + 0.5*v2*(2*lam5+lam6*ctb+lam7*tb))*(sb*cb);
          double m112 = m122*tb - 0.5*v2 * (lam1*cb*cb + lam345*sb*sb + 3.0*lam6*sb*cb + lam7*sb*sb*tb);
          double m222 = m122*ctb - 0.5*v2 * (lam2*sb*sb + lam345*cb*cb + lam6*cb*cb*ctb + 3.0*lam7*sb*cb);

          // Higgs basis
          double M122 = (m112-m222)*s2b + m122*c2b;
          double M112 = m112*pow(cb,2) + m222*pow(sb,2) - m122*s2b;
          double M222 = m112*pow(sb,2) + m222*pow(cb,2) + m122*s2b; // same as Y2 above

          // compare them
          // std::cerr << "generic basis" << std::endl;
          // std::cerr << "m112 (expected) " << m112 << " | (FS) " << he.get(Par::mass1, "m11_2") << std::endl;
          // std::cerr << "m122 (expected) " << m122 << " | (FS) " << he.get(Par::mass1, "m12_2") << std::endl;
          // std::cerr << "m222 (expected) " << m222 << " | (FS) " << he.get(Par::mass1, "m22_2") << std::endl;
          // std::cerr << "Higgs basis" << std::endl;
          // std::cerr << "M112 (expected) " << M112 << " | (FS) " << he.get(Par::mass1, "M11_2") << std::endl;
          // std::cerr << "M122 (expected) " << M122 << " | (FS) " << he.get(Par::mass1, "M12_2") << std::endl;
          // std::cerr << "M222 (expected) " << M222 << " | (FS) " << he.get(Par::mass1, "M22_2") << std::endl;
        }

        Eigen::Matrix3d M(3,3);
        M <<  Z1,        +real(Z6),       -imag(Z6),
              +real(Z6),  Z345/2.+Y2/sqr(vev),  -imag(Z5)/2.,
              -imag(Z6), -imag(Z5)/2.,     Z345bar/2.+Y2/sqr(vev);
        M *= sqr(vev);

        // get eigenvectors and eigenvalues
        auto solve = Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d>(M);
        auto eigenVectors = solve.eigenvectors();
        auto eigenValues = solve.eigenvalues();

        // choose the orthogonal matrix to have a positive determinant
        if (eigenVectors.determinant() < +0.0) eigenVectors *= -1;

        // ensure that mass-squared are positive (tree-level only)
        if (!is_FS_model && (eigenValues(0) < 0. || eigenValues(1) < 0. || eigenValues(2) < 0.))
        {
          SpecBit_error().raise(LOCAL_INFO, "negative mass");
        }

        // set eigenvector order: h,H,A
        if (abs(mh2-eigenValues(1)) < abs(mh2-eigenValues(0)))
        {
          std::swap(eigenValues(0),eigenValues(1));
          eigenVectors.col(0).swap(eigenVectors.col(1));
        }
        if (abs(mh2-eigenValues(2)) < abs(mh2-eigenValues(0)))
        {
          std::swap(eigenValues(0),eigenValues(2));
          eigenVectors.col(0).swap(eigenVectors.col(2));
        }
        if (abs(mH2-eigenValues(2)) < abs(mH2-eigenValues(1)))
        {
          std::swap(eigenValues(1),eigenValues(2));
          eigenVectors.col(1).swap(eigenVectors.col(2));
        }

        // std::cerr << "mh2 " << mh2 << " | " << eigenValues(0) << std::endl;
        // std::cerr << "mH2 " << mH2 << " | " << eigenValues(1) << std::endl;
        // std::cerr << "mA2 " << mA2 << " | " << eigenValues(2) << std::endl;

        // finally, get the mixing angles
        auto ea = eigenVectors.eulerAngles(2,1,0);

        double u12 = pi-ea(0); // (0 to pi)
        double u13 = pi-ea(1); // (0 to 2pi)
        double u23 = pi-ea(2); // (0 to 2pi)

        // check angles for Z2-symmetric model
        double u12_expect = pi/2.-(beta-alpha);
        // double u13_expect = 0.;
        // double u23_expect = 0.;
        // if (abs(u12-u12_expect) < 1e-5) std::cerr << "match" << std::endl;
        // else std::cerr << "diff" << std::endl;

        // // hax
        // u12 = pi/2.-(beta-alpha);
        // u13 = 0.;
        // u23 = 0.;

        // calculate the q-vectors

        complexd c123 = cos(u12) - ii*sin(u12)*sin(u13);
        complexd s123 = sin(u12) + ii*cos(u12)*sin(u13);
        Eigen::Vector4cd qA = { cos(u13)*cos(u12), cos(u13)*sin(u12), sin(u13), ii };
        Eigen::Vector4cd qB = { -s123, c123, ii*cos(u13), 0. };
        Eigen::Vector4cd qAc = { conj(qA(0)), conj(qA(1)), conj(qA(2)), conj(qA(3)) };
        Eigen::Vector4cd qBc = { conj(qB(0)), conj(qB(1)), conj(qB(2)), conj(qB(3)) };

        // particle strings ('n' for name of)
        const static std::string nh = "h0_1", nH = "h0_2", nA = "A0", nHp = "H+", nHm = "H-", nG = "G0", nGp = "G+", nGm = "G-";
        const static std::vector<std::string> nhj = { nh, nH, nA, nG };

        // some calcs
        complexd exp_u23 = exp(-ii*u23);
        complexd exp2_u23 = exp(-2.*ii*u23);
        complexd tmp;

        // helper to check for odd number of A0s/G0s

        auto A0count = [&](int h1, int h2=0, int h3=0, int h4=0)
        {
          int count = 0;
          if (h1 >= 2) count += 1;
          if (h2 >= 2) count += 1;
          if (h3 >= 2) count += 1;
          if (h4 >= 2) count += 1;
          return count;
        };

        // {hj hk hl}

        complexd buf3[4][4][4];
        std::fill(&(buf3[0][0][0]), &(buf3[3][3][3]), complexd(0.,0.));

        for (int j=0; j<4; ++j)
        {
          for (int k=0; k<4; ++k)
          {
            for (int l=0; l<4; ++l)
            {
              if (A0count(j,k,l) % 2 == 1 && is_Z2) continue;

              // TODO: check sign for AGh, AGH
              tmp = qA(j)*qAc(k)*real(qA(l))*Z1
                  + qB(j)*qBc(k)*real(qA(l))*(Z3+Z4)
                  + real(qAc(j)*qB(k)*qB(l)*Z5*exp2_u23)
                  + real((2.*qA(j)+qAc(j))*qAc(k)*qB(l)*Z6*exp_u23)
                  + real(qBc(j)*qB(k)*qB(l)*Z7*exp_u23);

              int jj=j, kk=k, ll=l;
              sort(jj,kk,ll);
              buf3[jj][kk][ll] += tmp;
            }
          }
        }

        for (int j=0; j<4; ++j)
        {
          for (int k=j; k<4; ++k)
          {
            for (int l=k; l<4; ++l)
            {
              if (A0count(j,k,l) % 2 == 1 && is_Z2) continue;
              coup.insert({nhj[j], nhj[k], nhj[l]}, buf3[j][k][l]*vev/2.);
            }
          }
        }

        for (int k=0; k<4; ++k)
        {
          if (k==3 && is_Z2) continue; // G0 X+ X- not allowed

          // mysterious CP-odd coupling allowed for A0 only
          // {hk G- H+}
          // {hk G+ H-}
          tmp = exp_u23*(qBc(k)*Z4 + qB(k)*exp2_u23*Z5+2*real(qA(k))*Z6*exp_u23);
          coup.insert({nhj[k], nHp, nGm}, tmp*vev/2.); // TODO: check that sign is ok?
          coup.insert({nhj[k], nGp, nHm}, conj(tmp)*vev/2.);

          if (A0count(k) % 2 == 1 && is_Z2) continue;

          // {hk G+ G-}
          tmp = real(qA(k))*Z1 + real(qB(k)*exp_u23*Z6);
          coup.insert({nhj[k], nGp, nGm}, tmp*vev); // match

          // {hk H+ H-}
          tmp = real(qA(k))*Z3 + real(qB(k)*exp_u23*Z7);
          coup.insert({nhj[k], nHp, nHm}, tmp*vev); // match
        }

        // {hj hk hl hm}

        complexd buf4[4][4][4][4];
        std::fill(&(buf4[0][0][0][0]), &(buf4[3][3][3][3]), complexd(0.,0.));

        for (int j=0; j<4; ++j)
        {
          for (int k=0; k<4; ++k)
          {
            for (int l=0; l<4; ++l)
            {
              for (int m=0; m<4; ++m)
              {
                if (A0count(j,k,l,m) % 2 == 1 && is_Z2) continue;

                tmp = qA(j)*qA(k)*qAc(l)*qAc(m)*Z1
                    + qB(j)*qB(k)*qBc(l)*qBc(m)*Z2
                    + 2.*qA(j)*qAc(k)*qB(l)*qBc(m)*(Z3+Z4)
                    + 2.*real(qAc(j)*qAc(k)*qB(l)*qB(m)*Z5*exp2_u23)
                    + 4.*real(qA(j)*qAc(k)*qAc(l)*qB(m)*Z6*exp_u23)
                    + 4.*real(qAc(j)*qB(k)*qB(l)*qBc(m)*Z7*exp_u23);

                int jj=j, kk=k, ll=l, mm=m;
                sort(jj,kk,ll,mm);
                buf4[jj][kk][ll][mm] += tmp;
              }
            }
          }
        }

        for (int j=0; j<4; ++j)
        {
          for (int k=j; k<4; ++k)
          {
            for (int l=k; l<4; ++l)
            {
              for (int m=l; m<4; ++m)
              {
                if (A0count(j,k,l,m) % 2 == 1 && is_Z2) continue;
                coup.insert({nhj[j], nhj[k], nhj[l], nhj[m]}, buf4[j][k][l][m]/8.);
              }
            }
          }
        }


        for (int j=0; j<4; ++j)
        {
          for (int k=j; k<4; ++k)
          {
            // mysterious CP-odd coupling allowed for A0 and G0
            // {hj hk G- H+}
            complexd tmp = qA(j)*qBc(k)*Z4 + qAc(j)*qB(k)*Z5*exp2_u23 + qA(j)*qAc(k)*Z6*exp_u23 + qB(j)*qBc(k)*Z7*exp_u23;
            if (j != k) tmp += qA(k)*qBc(j)*Z4 + qAc(k)*qB(j)*Z5*exp2_u23 + qA(k)*qAc(j)*Z6*exp_u23 + qB(k)*qBc(j)*Z7*exp_u23;
            tmp *= exp(ii*u23)/2.;
            coup.insert({nhj[j], nhj[k], nGm, nHp}, tmp);
            coup.insert({nhj[j], nhj[k], nGp, nHm}, conj(tmp));

            if (A0count(j,k) % 2 == 1 && is_Z2) continue;

            // {hj hk G+ G-}
            tmp = qA(j)*qAc(k)*Z1 + qB(j)*qBc(k)*Z3 + 2*real(qA(j)*qB(k)*Z6*exp_u23);
            if (k != j) tmp += qA(k)*qAc(j)*Z1 + qB(k)*qBc(j)*Z3 + 2*real(qA(k)*qB(j)*Z6*exp_u23);
            coup.insert({nhj[j], nhj[k], nGp, nGm}, tmp/2.);

            // {hj hk H+ H-}
            tmp = qB(j)*qBc(k)*Z2 + qA(j)*qAc(k)*Z3 + 2*real(qA(j)*qB(k)*Z7*exp_u23);
            if (k != j) tmp += qB(k)*qBc(j)*Z2 + qA(k)*qAc(j)*Z3 + 2*real(qA(k)*qB(j)*Z7*exp_u23);
            coup.insert({nhj[j], nhj[k], nHp, nHm}, tmp/2.);

          }
        }

        // { 4 charged }
        coup.insert({nGp, nGm, nGp, nGm}, Z1/2.);
        coup.insert({nHp, nHm, nHp, nHm}, Z2/2.);
        coup.insert({nGp, nGm, nHp, nHm}, (Z3+Z4));
        coup.insert({nHp, nHp, nGm, nGm}, Z5/2.);
        coup.insert({nHm, nHm, nGp, nGp}, conj(Z5/2.));
        coup.insert({nGp, nGm, nHp, nGm}, Z6);
        coup.insert({nGp, nGm, nHm, nGp}, conj(Z6));
        coup.insert({nHp, nHm, nHp, nGm}, Z7);
        coup.insert({nHp, nHm, nHm, nGp}, conj(Z7));

        for (auto& pair : coup.table)
        {
          // MULTIPLY BY SYMMETRY FACTOR
          pair.second *= get_symmetry_factor(pair.first);
          pair.second *= -ii;
        }

      };

      // Retrieve spectrum contents
      Spectrum spectrum = *Dep::THDM_spectrum;

      result.init(spectrum, calculator);
      result.update();

      // ctmp = result;
    }

    // ----- SCALAR-GAUGE COUPLING TABLE -----


    // ----- SCALAR-FERMION COUPLING TABLE -----


    // ----- SM COUPLING TABLE -----


    // Helper function to work out if the LSP is invisible, and if so, which particle it is.
    std::vector<std::pair<str,str>> get_invisibles_gumTHDMII(const SubSpectrum& spec)
    {
        /// GUM has computed that there are no invisible decays for
        /// the Higgs sector of this model.
        (void)spec; // Silence compiler warnings.
        return std::vector<std::pair<str,str>>();
    }

    // Put together the Higgs couplings for the THDMII, from SPheno
    void gumTHDMII_higgs_couplings_SPheno(HiggsCouplingsTable &result)
    {
      namespace myPipe = Pipes::gumTHDMII_higgs_couplings_SPheno;
      
      // Retrieve spectrum contents
      const Spectrum& spec = *myPipe::Dep::THDM_spectrum_SPheno;
      const SubSpectrum& he = spec.get_HE();
      const SMInputs &sminputs = spec.get_SMInputs();
      
      const DecayTable* tbl = &(*myPipe::Dep::decay_rates);
      
      // Set up the input structure for SPheno
      Finputs inputs;
      inputs.sminputs = sminputs;
      inputs.param = myPipe::Param;
      inputs.options = myPipe::runOptions;
      
      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
      result.set_n_neutral_higgs(3);
      
      // Set the CP of the Higgs states. Note that this would
      // need to be more sophisticated to deal with complex models.
      result.CP[0] = 1.;  // "h0_1"
      result.CP[1] = 1.;  // "h0_2"
      result.CP[2] = -1.; // "A0"
      
      // Set up charged Higgses
      static const std::vector<str> sHchar = initVector<str>("H+");
      result.set_n_charged_higgs(1);
      
      // Work out which SM values correspond to which Higgs
      int higgs = (SMlike_higgs_PDG_code(he) == 25 ? 0 : 1);
      int other_higgs = (higgs == 0 ? 1 : 0);
      
      
      // Set the Higgs sector decays from the DecayTable
      result.set_neutral_decays(higgs, sHneut[higgs], tbl->at("h0_1"));
      result.set_neutral_decays(other_higgs, sHneut[other_higgs], tbl->at("h0_2"));
      result.set_neutral_decays(2, sHneut[2], tbl->at("A0"));
      
      //Charged Higgses
      result.set_charged_decays(0, "H+", tbl->at("H+"));
      
      // Add t decays since t can decay to light Higgses
      result.set_t_decays(tbl->at("t"));
      
      // Fill HiggsCouplingsTable object from SPheno backend
      // This fills the effective couplings (C_XX2)
      myPipe::BEreq::SARAHSPheno_gumTHDMII_HiggsCouplingsTable(spec, result, inputs);
      
      // The SPheno frontend provides the invisible width for each Higgs, however this requires
      // loads of additional function calls. Just use the helper function instead.
      result.invisibles = get_invisibles_gumTHDMII(he);
    }
    
    void effective_couplings_THDM(map_str_dbl& result)
    {
      namespace myPipe = Pipes::effective_couplings_THDM;
      const Spectrum& spec = *myPipe::Dep::THDM_spectrum_SPheno;
      
      DecayTable decays;
      Finputs inputs;
      inputs.param = myPipe::Param;
      inputs.options = myPipe::runOptions;
      
      // Use SPheno to fill the decay table
      myPipe::BEreq::SARAHSPheno_gumTHDMII_decays(spec, decays, inputs);
      

      myPipe::BEreq::SARAHSPheno_gumTHDMII_conv_get_effective_couplings(spec, result);
    }



  }
}
