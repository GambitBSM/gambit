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

#include <sstream>
#include <complex>

// Eigen headers
#include <Eigen/Eigenvalues>

// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/src/spectrum_generator_settings.hpp"
#include "flexiblesusy/models/THDM_I/THDM_I_input_parameters.hpp"
#include "flexiblesusy/models/THDM_II/THDM_II_input_parameters.hpp"
#include "flexiblesusy/models/THDM_LS/THDM_LS_input_parameters.hpp"
#include "flexiblesusy/models/THDM_flipped/THDM_flipped_input_parameters.hpp"

// GAMBIT headers
#include "gambit/Elements/spectrum_types.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Utils/stream_overloads.hpp" // Just for more convenient output to logger
#include "gambit/Utils/util_macros.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/Models/SimpleSpectra/THDMSimpleSpec.hpp"
#include "gambit/SpecBit/THDMSpec.hpp"
#include "gambit/SpecBit/THDMSpec_helpers.hpp"
#include "gambit/SpecBit/model_files_and_boxes.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/Utils/slhaea_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/numerical_constants.hpp"
#include "gambit/Elements/spectrum_types.hpp"

// #define SPECBIT_DEBUG // turn on debug mode

namespace Gambit
{

  extern int to_thdmc(const thdm::Particle part);

  namespace hax
  {
    // hack to prevent point from being outputted
    bool skip_output_hax = false;
  }

  namespace SpecBit
  {

    constexpr double eps = 1e-10;
    
      // error === value - upperbound
      // error_invalid_val === error value at which result reaches invalid threshold
      // invalid_threshold === threshold where point is as invalid

      // hard cutoff function
      double cutoff_hard(const double error, const double error_invalid_val, const double invalid_threshold)
      {
         return error > eps ? invalid_threshold : 0.0;
      }

      // soft cutoff function (square)
      double cutoff_soft_square(const double error, const double error_invalid_val, const double invalid_threshold)
      {
         if (error <= eps) return 0.0;
         double sigma = error_invalid_val / sqrt(invalid_threshold);
         double result = Utils::sqr(error/sigma);

         // make sure the result is non-negligible if constraints are indeed violated
         return result + 1.0;
      }

      // soft cutoff function (linear)
      double cutoff_soft_linear(const double error, const double error_invalid_val, const double invalid_threshold)
      {
         if (error <= eps) return 0.0;
         double sigma = error_invalid_val / invalid_threshold;
         double result = error/sigma;

         // make sure the result is non-negligible if constraints are indeed violated
         return result + 1.0;
      }

    // extra namespace declarations
    using namespace LogTags;
    using namespace flexiblesusy;
    using namespace Utils;
    using std::vector;

    namespace RunScale
    {
      constexpr double NONE = -1.0;
      constexpr double INPUT = -2.0;
    }

    // used to invalidate likelihood
    constexpr double L_MAX = 1e50;

    // imaginary unit
    constexpr complexd ii(0,1);

    /// =========================
    /// == spectrum generation ==
    /// =========================

      double g_lam1 = 0.0;
      double g_lam2 = 0.0;
      double g_lam3 = 0.0;
      double g_lam4 = 0.0;
      double g_lam5 = 0.0;
      double g_m122 = 0.0;
      double g_tanb = 0.0;

    // helper to setup Spectrum with a FlexibleSUSY spectrum generator
    template <class MI>
    Spectrum run_FS_spectrum_generator(const typename MI::InputParameters &input, const SMInputs &sminputs, const Options &runOptions,
                                       const std::map<str, safe_ptr<const double>> &input_Param, THDM_TYPE &model_type)
    {
      // *
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
      thdmspec.set_override(Par::dimensionless, cos(thdmspec.get(Par::dimensionless, "beta")-thdmspec.get(Par::dimensionless, "alpha")), "cosba", true);

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


      // fix conventions to match FS and THDMC
      // double beta = atan(tanb);
      // double alpha = thdmspec.get(Par::dimensionless, "alpha");

      // thdmspec.set_override(Par::dimensionless, alpha, "alpha", true);

      // {
      //   double beta = atan(tanb);
      //   double cb = cos(beta), sb = sin(beta);
      //   double v2 = 1.0 / (sqrt(2.0) * sminputs.GF), vev = sqrt(v2);
      //   const double sqrt2v = sqrt(2.0)/vev;

      //   std::cout << "-------\n";

      //   double in_tanb = *input_Param.at("tanb");
      //   double in_beta = atan(in_tanb);
      //   // double in_cba = *input_Param.at("cba");
      //   // double in_alpha = in_beta - acos(in_cba);
      //   // double in_sba = sin(in_beta-in_alpha);
      //   // double in_mHp = *input_Param.at("mHp");

      //   double alpha = thdmspec.get(Par::dimensionless, "alpha");
      //   double sba = sin(beta-alpha);
      //   double cba = cos(beta-alpha);
      //   double mHp = thdmspec.get(Par::mass1, "H+");

      //   std::cout << "mHp " << 0 << " | " << mHp << " alpha " << 0 << " | " << alpha << " beta " << in_beta << " | " << beta << std::endl;

      //   std::cout << "GT_Yu " << sqrt2v * sminputs.mU/sba << "  " << sqrt2v * sminputs.mCmC/sba << "  " << sqrt2v * sminputs.mT/sba << std::endl;
      //   std::cout << "GT_Yd " << sqrt2v * sminputs.mD/cba << "  " << sqrt2v * sminputs.mS/cba << "  " << sqrt2v * sminputs.mBmB/cba << std::endl;
      //   std::cout << "GT_Ye " << sqrt2v * sminputs.mE/cba << "  " << sqrt2v * sminputs.mMu/cba << "  " << sqrt2v * sminputs.mTau/cba << std::endl;
      // }

      // std::cerr << "Yu " << thdmspec.get(Par::dimensionless, "Yu2", 1, 1) << "  " << thdmspec.get(Par::dimensionless, "Yu2", 2, 2) << "  " << thdmspec.get(Par::dimensionless, "Yu2", 3, 3) << std::endl;;
      // std::cerr << "Yd " << thdmspec.get(Par::dimensionless, "Yd1", 1, 1) << "  " << thdmspec.get(Par::dimensionless, "Yd1", 2, 2) << "  " << thdmspec.get(Par::dimensionless, "Yd1", 3, 3) << std::endl;;
      // std::cerr << "Ye " << thdmspec.get(Par::dimensionless, "Ye1", 1, 1) << "  " << thdmspec.get(Par::dimensionless, "Ye1", 2, 2) << "  " << thdmspec.get(Par::dimensionless, "Ye1", 3, 3) << std::endl;;


      // Do the W mass separately.  Here we use 10 MeV based on the size of corrections from two-loop papers and advice from Dominik Stockinger.
      // double rd_mW = 0.01 / thdmspec.get(Par::Pole_Mass, "W+");
      // thdmspec.set_override(Par::Pole_Mass_1srd_high, rd_mW, "W+", true);
      // thdmspec.set_override(Par::Pole_Mass_1srd_low,  rd_mW, "W+", true);

      {
        // fill coupling basis
        // std::map<std::string, double> basis = create_empty_THDM_basis();

        // basis["lambda1"] = *input_Param.at("lambda1");
        // basis["lambda2"] = *input_Param.at("lambda2");
        // basis["lambda3"] = *input_Param.at("lambda3");
        // basis["lambda4"] = *input_Param.at("lambda4");
        // basis["lambda5"] = *input_Param.at("lambda5");
        // basis["lambda6"] = *input_Param.at("lambda6");
        // basis["lambda7"] = *input_Param.at("lambda7");
        // basis["tanb"] = *input_Param.at("tanb");
        // basis["m12_2"] = *input_Param.at("m12_2");

        // // run tree level spectrum generator
        // generate_THDM_spectrum_tree_level(basis, sminputs);

        // std::cout << "lambda1:  " << basis["lambda1"] - thdmspec.get(Par::dimensionless, "lambda1") << "  " << basis["lambda1"] << "  " << thdmspec.get(Par::dimensionless, "lambda1") << std::endl;
        // std::cout << "lambda2:  " << basis["lambda2"] - thdmspec.get(Par::dimensionless, "lambda2") << "  " << basis["lambda2"] << "  " << thdmspec.get(Par::dimensionless, "lambda2") << std::endl;
        // std::cout << "lambda3:  " << basis["lambda3"] - thdmspec.get(Par::dimensionless, "lambda3") << "  " << basis["lambda3"] << "  " << thdmspec.get(Par::dimensionless, "lambda3") << std::endl;
        // std::cout << "lambda4:  " << basis["lambda4"] - thdmspec.get(Par::dimensionless, "lambda4") << "  " << basis["lambda4"] << "  " << thdmspec.get(Par::dimensionless, "lambda4") << std::endl;
        // std::cout << "lambda5:  " << basis["lambda5"] - thdmspec.get(Par::dimensionless, "lambda5") << "  " << basis["lambda5"] << "  " << thdmspec.get(Par::dimensionless, "lambda5") << std::endl;
        // std::cout << "lambda6:  " << basis["lambda6"] - thdmspec.get(Par::dimensionless, "lambda6") << "  " << basis["lambda6"] << "  " << thdmspec.get(Par::dimensionless, "lambda6") << std::endl;
        // std::cout << "lambda7:  " << basis["lambda7"] - thdmspec.get(Par::dimensionless, "lambda7") << "  " << basis["lambda7"] << "  " << thdmspec.get(Par::dimensionless, "lambda7") << std::endl;

        // std::cout << "Lambda1:  " << basis["Lambda1"] - thdmspec.get(Par::dimensionless, "Lambda1") << "  " << basis["Lambda1"] << "  " << thdmspec.get(Par::dimensionless, "Lambda1") << std::endl;
        // std::cout << "Lambda2:  " << basis["Lambda2"] - thdmspec.get(Par::dimensionless, "Lambda2") << "  " << basis["Lambda2"] << "  " << thdmspec.get(Par::dimensionless, "Lambda2") << std::endl;
        // std::cout << "Lambda3:  " << basis["Lambda3"] - thdmspec.get(Par::dimensionless, "Lambda3") << "  " << basis["Lambda3"] << "  " << thdmspec.get(Par::dimensionless, "Lambda3") << std::endl;
        // std::cout << "Lambda4:  " << basis["Lambda4"] - thdmspec.get(Par::dimensionless, "Lambda4") << "  " << basis["Lambda4"] << "  " << thdmspec.get(Par::dimensionless, "Lambda4") << std::endl;
        // std::cout << "Lambda5:  " << basis["Lambda5"] - thdmspec.get(Par::dimensionless, "Lambda5") << "  " << basis["Lambda5"] << "  " << thdmspec.get(Par::dimensionless, "Lambda5") << std::endl;
        // std::cout << "Lambda6:  " << basis["Lambda6"] - thdmspec.get(Par::dimensionless, "Lambda6") << "  " << basis["Lambda6"] << "  " << thdmspec.get(Par::dimensionless, "Lambda6") << std::endl;
        // std::cout << "Lambda7:  " << basis["Lambda7"] - thdmspec.get(Par::dimensionless, "Lambda7") << "  " << basis["Lambda7"] << "  " << thdmspec.get(Par::dimensionless, "Lambda7") << std::endl;

        // std::cout << "h0_1:  " << basis["m_h"] - thdmspec.get(Par::mass1, "h0_1") << "  " << basis["m_h"] << "  " << thdmspec.get(Par::mass1, "h0_1") << std::endl;
        // std::cout << "h0_2:  " << basis["m_H"] - thdmspec.get(Par::mass1, "h0_2") << "  " << basis["m_H"] << "  " << thdmspec.get(Par::mass1, "h0_2") << std::endl;
        // std::cout << "A0:  " << basis["m_A"] - thdmspec.get(Par::mass1, "A0") << "  " << basis["m_A"] << "  " << thdmspec.get(Par::mass1, "A0") << std::endl;
        // std::cout << "H+:  " << basis["m_Hp"] - thdmspec.get(Par::mass1, "H+") << "  " << basis["m_Hp"] << "  " << thdmspec.get(Par::mass1, "H+") << std::endl;
        // // std::cout << "G0:  " << basis["G0"] - thdmspec.get(Par::mass1, "G0") << "  " << basis["G0"] << "  " << thdmspec.get(Par::mass1, "G0") << std::endl;
        // // std::cout << "G+:  " << basis["G+"] - thdmspec.get(Par::mass1, "G+") << "  " << basis["G+"] << "  " << thdmspec.get(Par::mass1, "G+") << std::endl;
        // std::cout << "m12_2:  " << basis["m12_2"] - thdmspec.get(Par::mass1, "m12_2") << "  " << basis["m12_2"] << "  " << thdmspec.get(Par::mass1, "m12_2") << std::endl;
        // std::cout << "m11_2:  " << basis["m11_2"] - thdmspec.get(Par::mass1, "m11_2") << "  " << basis["m11_2"] << "  " << thdmspec.get(Par::mass1, "m11_2") << std::endl;
        // std::cout << "m22_2:  " << basis["m22_2"] - thdmspec.get(Par::mass1, "m22_2") << "  " << basis["m22_2"] << "  " << thdmspec.get(Par::mass1, "m22_2") << std::endl;

        // std::cout << "M12_2:  " << basis["M12_2"] - thdmspec.get(Par::mass1, "M12_2") << "  " << basis["M12_2"] << "  " << thdmspec.get(Par::mass1, "M12_2") << std::endl;
        // std::cout << "M11_2:  " << basis["M11_2"] - thdmspec.get(Par::mass1, "M11_2") << "  " << basis["M11_2"] << "  " << thdmspec.get(Par::mass1, "M11_2") << std::endl;
        // std::cout << "M22_2:  " << basis["M22_2"] - thdmspec.get(Par::mass1, "M22_2") << "  " << basis["M22_2"] << "  " << thdmspec.get(Par::mass1, "M22_2") << std::endl;

        // std::cout << "beta:  " << basis["beta"] - thdmspec.get(Par::dimensionless, "beta") << "  " << basis["beta"] << "  " << thdmspec.get(Par::dimensionless, "beta") << std::endl;
        // std::cout << "alpha:  " << basis["alpha"] - thdmspec.get(Par::dimensionless, "alpha") << "  " << basis["beta"] - basis["alpha"] << "  " << thdmspec.get(Par::dimensionless, "beta") - thdmspec.get(Par::dimensionless, "alpha") << "   tanb:  " << basis["tanb"] - thdmspec.get(Par::dimensionless, "tanb") << "  " << basis["tanb"] << "  " << thdmspec.get(Par::dimensionless, "tanb") << std::endl;

        {

          // double lam1 = *input_Param.at("lambda1");
          // double lam2 = *input_Param.at("lambda2");
          // double lam3 = *input_Param.at("lambda3");
          // double lam4 = *input_Param.at("lambda4");
          // double lam5 = *input_Param.at("lambda5");
          // double lam6 = *input_Param.at("lambda6");
          // double lam7 = *input_Param.at("lambda7");
          // double tanb = *input_Param.at("tanb");
          // double m12_2 = *input_Param.at("m12_2"), m122 = m12_2;
          // double mA2 = pow(basis["m_A"],2);
          // double lam345 = lam3+lam4+lam5;

          // double beta = atan(tanb), cotb = 1/tanb;
          // double cosb = cos(beta), sinb = sin(beta);
          // double vsq = 1.0 / (sqrt(2.0) * sminputs.GF), vev = sqrt(vsq);
          // const double sqrt2v = sqrt(2.0)/vev;

          // double v = vev;
          // double v2   = v * sinb;
          // double v1   = v * cosb;
          // double m112 = m122*tanb - 0.5*(lam1*pow(v1,2) + lam345*pow(v2,2));
          // double m222 = m122*cotb - 0.5*(lam2*pow(v2,2) + lam345*pow(v1,2));
          // double M112 = mA2*pow(sinb,2) + vsq*(lam1*pow(cosb,2)+2*lam6*sinb*cosb+lam5*pow(sinb,2));
          // double M222 = mA2*pow(cosb,2) + vsq*(lam2*pow(sinb,2)+2*lam7*sinb*cosb+lam5*pow(cosb,2));
          // double M122 = -mA2*pow(sinb,2)*pow(cosb,2) + vsq*((lam3+lam4)*sinb*cosb+lam6*pow(cosb,2)+lam7*pow(sinb,2));

          // std::cout << "__m122 " << m122 << std::endl;
          // std::cout << "__m112 " << m112 << std::endl;
          // std::cout << "__m222 " << m222 << std::endl;
          // std::cout << "__M122 " << M122 << std::endl;
          // std::cout << "__M112 " << M112 << std::endl;
          // std::cout << "__M222 " << M222 << std::endl;
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
          ///TODO: Need to tell gambit that the spectrum is not viable somehow. For now
          /// just die.
          SpecBit_error().raise(LOCAL_INFO, errmsg.str());
        }
        else
        {
          logger() << errmsg.str() << EOM;
          invalid_point().raise(errmsg.str()); //TODO: This message isn't ending up in the logs.
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
    
    // apply a basic set of theory constraints at the input scale
    void performance_hax()
    {
        using namespace Pipes::get_THDM_spectrum;
        const bool use_speedhacks = runOptions->getValueOrDef<bool>(true, "use_speedhacks");
        const str err_msg = "bad point encountered. Point invalidated\n";
        constexpr double pert_limit = 12.7; // not intended as a replacement of theory constraints,
                                     // just to skip spectrum calculation when way off the mark
                              
        const double lam1 = *Param.at("lambda1");
        const double lam2 = *Param.at("lambda2");
        const double lam3 = *Param.at("lambda3");
        const double lam4 = *Param.at("lambda4");
        const double lam5 = *Param.at("lambda5");
        const double lam6 = *Param.at("lambda6");
        const double lam7 = *Param.at("lambda7");

        g_lam1 = lam1;
        g_lam2 = lam2;
        g_lam3 = lam3;
        g_lam4 = lam4;
        g_lam5 = lam5;
        g_m122 = *Param.at("m12_2");
        g_tanb = *Param.at("tanb");

        if (abs(lam1) > pert_limit || abs(lam2) > pert_limit ||
            abs(lam3) > pert_limit || abs(lam4) > pert_limit ||
            abs(lam5) > pert_limit || abs(lam6) > pert_limit ||
            abs(lam7) > pert_limit)
        {
            invalid_point().raise(err_msg);
        }

        if (!use_speedhacks) return;
        // double mbar = 2*(*Param.at("m12_2")) / sin(2*atan(*Param.at("tanb")));
        // double v2 = 246*246;
          
        // a00
        double a00_even_plus = 1.0 / 2.0 * (3.0 * (lam1 + lam2) + sqrt(9.0 * pow((lam1 - lam2), 2) + 4.0 * pow((2.0 * lam3 + lam4), 2)));
        double a00_even_minus = 1.0 / 2.0 * (3.0 * (lam1 + lam2) - sqrt(9.0 * pow((lam1 - lam2), 2) + 4.0 * pow((2.0 * lam3 + lam4), 2)));
        double a00_odd_plus = lam3 + 2.0 * lam4 + 3.0 * lam5;
        double a00_odd_minus = lam3 + 2.0 * lam4 - 3.0 * lam5;
        // a01
        double a01_even_plus = 1.0 / 2.0 * (lam1 + lam2 + sqrt(pow((lam1 - lam2), 2) + 4.0 * pow(lam4, 2)));
        double a01_even_minus = 1.0 / 2.0 * (lam1 + lam2 - sqrt(pow((lam1 - lam2), 2) + 4.0 * pow(lam4, 2)));
        double a01_odd_plus = lam3 + lam5;
        double a01_odd_minus = lam3 - lam5;
        // a20
        double a20_odd = lam3 - lam4;
        // a21
        double a21_even_plus = 1.0 / 2.0 * (lam1 + lam2 + sqrt(pow((lam1 - lam2), 2) + 4.0 * pow(lam5, 2)));
        double a21_even_minus = 1.0 / 2.0 * (lam1 + lam2 - sqrt(pow((lam1 - lam2), 2) + 4.0 * pow(lam5, 2)));
        double a21_odd = lam3 + lam4;

        vector<double> lo_eigenvalues = {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus,
                a01_even_minus, a01_odd_plus, a01_odd_minus, a20_odd, a21_even_plus, a21_even_minus, a21_odd};

        constexpr double unitarity_upper_limit = 8 * pi;

        for (auto const &eachEig : lo_eigenvalues)
        {
          if (abs(eachEig) > unitarity_upper_limit)
          {
            invalid_point().raise(err_msg);
          }
        }
    }

    // Get Spectrum for the THDM (either a FlexibleSUSY or tree-level spectrum depending on model)
    void get_THDM_spectrum(Spectrum &result)
    {
      using namespace Pipes::get_THDM_spectrum;
      const SMInputs& sminputs = *Dep::SMINPUTS;

      if (ModelInUse("gumTHDMII"))
      {
        str errmsg = "Cannot use gumTHDMII with Filip's 2HDM spectrum generator";
        SpecBit_error().raise(LOCAL_INFO, errmsg);
      }

      if (ModelInUse("Inert2"))
      {
        str errmsg = "Cannot use IDM with Filip's 2HDM spectrum generator";
        SpecBit_error().raise(LOCAL_INFO, errmsg);
      }

      performance_hax();

      if (ModelInUse("THDM"))
      {
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

        // Initialise an object to carry the THDM sector information
        Models::THDMModel thdm_model;

        // create empty basis
        std::map<str, double> basis = create_empty_THDM_basis();

        // fill coupling basis
        basis["lambda1"] = *Param.at("lambda1");
        basis["lambda2"] = *Param.at("lambda2");
        basis["lambda3"] = *Param.at("lambda3");
        basis["lambda4"] = *Param.at("lambda4");
        basis["lambda5"] = *Param.at("lambda5");
        basis["lambda6"] = *Param.at("lambda6");
        basis["lambda7"] = *Param.at("lambda7");
        basis["tanb"] = *Param.at("tanb");
        basis["m12_2"] = *Param.at("m12_2");

        // run tree level spectrum generator
        generate_THDM_spectrum_tree_level(basis, sminputs);
        #ifdef SPECBIT_DEBUG
          print_THDM_spectrum(basis);
        #endif

        // copy any info that will be reused
        double alpha = basis["alpha"];
        const double tanb = basis["tanb"];

        thdm_model.model_type = *Dep::THDM_Type;

        thdm_model.tanb = tanb;
        thdm_model.alpha = alpha;

        thdm_model.lambda1 = basis["lambda1"];
        thdm_model.lambda2 = basis["lambda2"];
        thdm_model.lambda3 = basis["lambda3"];
        thdm_model.lambda4 = basis["lambda4"];
        thdm_model.lambda5 = basis["lambda5"];
        thdm_model.lambda6 = basis["lambda6"];
        thdm_model.lambda7 = basis["lambda7"];
        thdm_model.m11_2 = basis["m11_2"];
        thdm_model.m22_2 = basis["m22_2"];
        thdm_model.m12_2 = basis["m12_2"];

        thdm_model.mh0 = basis["m_h"];
        thdm_model.mH0 = basis["m_H"];
        thdm_model.mA0 = basis["m_A"];
        thdm_model.mC = basis["m_Hp"];

        //for debug reasons may choose to continue with negative mass
        const bool continue_with_negative_mass = false;

        if (!continue_with_negative_mass && (basis["m_h"] < 0.0 || basis["m_H"] < 0.0 || basis["m_A"] < 0.0 || basis["m_Hp"] < 0.0))
        {
          std::ostringstream msg;
          msg << "Negative mass encountered. Point invalidated." << std::endl;
          invalid_point().raise(msg.str());
        }

        thdm_model.mG0 = 0.0;
        thdm_model.mGC = 0.0;

        // quantities needed to fill spectrum, intermediate calculations
        const double v2 = 1.0 / (sqrt(2.0) * sminputs.GF);
        const double vev = sqrt(v2);
        const double alpha_em = 1.0 / sminputs.alphainv;
        const double e = sqrt(4*pi*alpha_em);
        const double cosW = sminputs.mW/sminputs.mZ; 
        const double sinW = sqrt(1 - sqr(cosW));

        // Standard model
        thdm_model.sinW2 = sqr(sinW);
        thdm_model.vev = vev;
        // gauge couplings
        thdm_model.g1 = e / sinW;
        thdm_model.g2 = e / cosW;
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
        const double cb = sqrt(1.0/(1+tanb*tanb));

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

        thdm_spec.set_override(Par::mass1, 0, "G0", true);
        thdm_spec.set_override(Par::mass1, 0, "G+", true);
        thdm_spec.set_override(Par::dimensionless, 0, "isIDM", true);
        thdm_spec.set_override(Par::dimensionless, cos(thdm_spec.get(Par::dimensionless, "beta")-thdm_spec.get(Par::dimensionless, "alpha")), "cosba", true);

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
      else if(ModelInUse("THDMatQ"))
      {
        // check perturbativity if key exists in yaml
        if (runOptions->getValueOrDef<bool>(false, "check_perturbativity"))
        {
          bool is_perturbative = true;
          vector<str> lambda_keys = {"lambda1", "lambda2", "lambda3", "lambda4",
                                                  "lambda5", "lambda6", "lambda7"};
          for (auto const &each_lambda : lambda_keys)
          {
            if (*Param.at(each_lambda) > 4. * pi)
            {
              is_perturbative = false;
              break;
            }
          }
          if (!is_perturbative)
            invalid_point().raise("FS Invalid Point: Perturbativity Failed");
        }
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
    }

    // get Spectrum as std::map so that it can be printed
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
        const str name = it->name();
        const vector<int> shape = it->shape();

        // useless stuff
        if (name == "vev" || name == "model_type" || name == "lambda6" || name == "lambda7") continue;

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

      // fix conventions

      // CONVENTION-A: ba in (0,pi), sba in (0,+1), cba in (-1,+1)
      // if (beta-alpha >= M_PI) alpha += M_PI;
      // if (beta-alpha < 0) alpha -= M_PI;

      // CONVENTION-B: ba in (-pi/2,+pi/2), sba in (-1,+1), cba in (0,+1)
      // if (beta-alpha >= M_PI/2) alpha += M_PI;
      // if (beta-alpha < -M_PI/2) alpha -= M_PI;

      specmap["sba dimensionless"] = sin(beta - alpha);
      specmap["cba dimensionless"] = cos(beta - alpha);

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

      // return; // !!!!

      specmap["lambda1_in"] = g_lam1;
      specmap["lambda2_in"] = g_lam2;
      specmap["lambda3_in"] = g_lam3;
      specmap["lambda4_in"] = g_lam4;
      specmap["lambda5_in"] = g_lam5;
      specmap["m122_in"] = g_m122;
      specmap["tanb_in"] = g_tanb;

      specmap["mA_mHp"] = thdmspec.get_HE().get(Par::Pole_Mass, "A0") - thdmspec.get_HE().get(Par::Pole_Mass, "H+");
      specmap["mH_mA"] = thdmspec.get_HE().get(Par::Pole_Mass, "h0_2") - thdmspec.get_HE().get(Par::Pole_Mass, "A0");

      specmap["mA_mHp mass1"] = thdmspec.get_HE().get(Par::mass1, "A0") - thdmspec.get_HE().get(Par::mass1, "H+");
      specmap["mH_mA mass1"] = thdmspec.get_HE().get(Par::mass1, "h0_2") - thdmspec.get_HE().get(Par::mass1, "A0");

      {
        double v2 = 1.0/(sqrt(2.0)*thdmspec.get_SMInputs().GF);
        double tanb  = g_tanb;
        double beta = atan(tanb);
        double sb = sin(beta), cb = cos(beta), tb = tan(beta);
        double sb2 = sb*sb, cb2 = cb*cb, ctb = 1./tb;
        double lam1 = g_lam1, lam2 = g_lam2, lam3 = g_lam3, lam4 = g_lam4, lam5 = g_lam5;
        double lam6 = 0, lam7 = 0, m12_2 = g_m122;
        
        double lam345 = lam3 + lam4 + lam5;
        // do the basis conversion
        double m11_2 = m12_2*tb - 0.5*v2 * (lam1*cb*cb + lam345*sb*sb + 3.0*lam6*sb*cb + lam7*sb*sb*tb);
        double m22_2 = m12_2*ctb - 0.5*v2 * (lam2*sb*sb + lam345*cb*cb + lam6*cb*cb*ctb + 3.0*lam7*sb*cb);
        double m_A2;
        if (tb>0) m_A2 = m12_2/sb/cb-0.5*v2*(2*lam5+lam6*ctb+lam7*tb);
        else m_A2 = m22_2+0.5*v2*(lam3+lam4-lam5);
        double m_Hp2 = m_A2+0.5*v2*(lam5-lam4);
        double M112 = m_A2*sb2+v2*(lam1*cb2+2.*lam6*sb*cb+lam5*sb2);
        double M122 = -m_A2*sb*cb+v2*((lam3+lam4)*sb*cb+lam6*cb2+lam7*sb2);
        double M222 = m_A2*cb2+v2*(lam2*sb2+2.*lam7*sb*cb+lam5*cb2);
        double m_h2 = 0.5*(M112+M222-sqrt((M112-M222)*(M112-M222)+4.*M122*M122));
        double m_H2 = 0.5*(M112+M222+sqrt((M112-M222)*(M112-M222)+4.*M122*M122));

        specmap["h0_1 tree"] = sqrt(m_h2);
        specmap["h0_2 tree"] = sqrt(m_H2);
        specmap["A0 tree"] = sqrt(m_A2);
        specmap["H+ tree"] = sqrt(m_Hp2);
      }

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

      const vector<str> yuk_base = {"yu2_re", "yu2_im", "yd2_re", "yd2_im", "yl2_re", "yl2_im"};
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

    // Get the name of the additional
    void get_additional_scalar(str& result)
    {
      if (*Pipes::get_additional_scalar::Dep::SM_like_scalar == "h0_1")
        result = "h0_2";
      else
        result = "h0_1";
    }


    /// =================================
    /// == likelihood function helpers ==
    /// =================================


    // get leading-order scattering eigenvalues (with fixed ordering) (requires Z2-symmetric THDM)
    vector<complexd> get_LO_scattering_eigenvalues_ordered(const ThdmSpec &s)
    {
      // ensure that we have a Z2-symmetric scalar sector
      check_Z2(s.lam6, s.lam7, "get_LO_scattering_eigenvalues_ordered");

      // a00
      complexd a00_even_plus = 1.0 / 2.0 * (3.0 * (s.lam1 + s.lam2) + sqrt(9.0 * pow((s.lam1 - s.lam2), 2) + 4.0 * pow((2.0 * s.lam3 + s.lam4), 2)));
      complexd a00_even_minus = 1.0 / 2.0 * (3.0 * (s.lam1 + s.lam2) - sqrt(9.0 * pow((s.lam1 - s.lam2), 2) + 4.0 * pow((2.0 * s.lam3 + s.lam4), 2)));
      complexd a00_odd_plus = s.lam3 + 2.0 * s.lam4 + 3.0 * s.lam5;
      complexd a00_odd_minus = s.lam3 + 2.0 * s.lam4 - 3.0 * s.lam5;
      // a01
      complexd a01_even_plus = 1.0 / 2.0 * (s.lam1 + s.lam2 + sqrt(pow((s.lam1 - s.lam2), 2) + 4.0 * pow(s.lam4, 2)));
      complexd a01_even_minus = 1.0 / 2.0 * (s.lam1 + s.lam2 - sqrt(pow((s.lam1 - s.lam2), 2) + 4.0 * pow(s.lam4, 2)));
      complexd a01_odd_plus = s.lam3 + s.lam5;
      complexd a01_odd_minus = s.lam3 - s.lam5;
      // a20
      complexd a20_odd = s.lam3 - s.lam4;
      // a21
      complexd a21_even_plus = 1.0 / 2.0 * (s.lam1 + s.lam2 + sqrt(pow((s.lam1 - s.lam2), 2) + 4.0 * pow(s.lam5, 2)));
      complexd a21_even_minus = 1.0 / 2.0 * (s.lam1 + s.lam2 - sqrt(pow((s.lam1 - s.lam2), 2) + 4.0 * pow(s.lam5, 2)));
      complexd a21_odd = s.lam3 + s.lam4;

      vector<complexd> lo_eigenvalues = {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus,
              a01_even_minus, a01_odd_plus, a01_odd_minus, a20_odd, a21_even_plus, a21_even_minus, a21_odd};

      return lo_eigenvalues;
    }

    // get leading-order scattering eigenvalues (with no particular order) (supports GCP 2HDM with lam6,lam7)
    vector<complexd> get_LO_scattering_eigenvalues(const ThdmSpec &s)
    {
      vector<double> lambda;
      vector<complexd> lo_eigenvalues;

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
      complexd S_20 = s.lam3 - s.lam4;
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

    // leading-order S-matrix unitarity likelihood
    double get_LO_unitarity_LogLikelihood(const SubSpectrum& he)
    {
      // get required spectrum info
      ThdmSpec s(he, ThdmSpecFill::FILL_GENERIC);

      // get the leading order scattering eigenvalues
      vector<complexd> LO_eigenvalues;
      
      if (s.lam6 == 0 && s.lam7 == 0)
        LO_eigenvalues = get_LO_scattering_eigenvalues_ordered(s);
      else
        LO_eigenvalues = get_LO_scattering_eigenvalues(s);

      // all values < 8*PI for unitarity conditions (see ivanov paper)
      constexpr double unitarity_upper_limit = 8 * pi;

      //calculate the total error of each point
      double error = 0.0;
      for (auto const &eachEig : LO_eigenvalues)
        if (abs(eachEig) > unitarity_upper_limit)
          error += abs(eachEig) - unitarity_upper_limit;

      return -cutoff_soft_square(error, 71, 1e6);
    }

    // next-to-leading-order S-matrix unitarity likelihood
    double get_NLO_unitarity_LogLikelihood(const SubSpectrum& he, const bool check_correction_ratio, const bool wave_function_corrections, const bool gauge_corrections, const bool yukawa_corrections)
    {
      // get required spectrum info
      const ThdmSpec s(he);


      vector<complexd> C3 = get_cubic_coupling_higgs(s);
      vector<complexd> C4 = get_quartic_couplings(s);

      vector<complexd> NLO_eigenvalues = get_NLO_scattering_eigenvalues(s, C3, C4, wave_function_corrections, gauge_corrections, yukawa_corrections);

      constexpr double unitarity_upper_limit = 0.50;
      constexpr double sigma = 0.05;
      double error = 0.0;
      double error_ratio = 0.0;

      // int counter_nlo = 0;
      // vector<string> nlo_eig_names = {"a00_even_plus", "a00_even_minus", "a00_odd_plus", "a00_odd_minus",
      //                                      "a01_even_plus", "a01_even_minus", "a01_odd_plus", "a01_odd_minus", "a10_odd", "a11_even_plus",
      //                                      "a11_even_minus", "a11_odd"};

      for (auto const &eig : NLO_eigenvalues)
      {
        if (abs(eig - ii / 2.0) > unitarity_upper_limit)
        {
          error += abs(eig - ii / 2.0) - unitarity_upper_limit;
        }
        // std::cout << nlo_eig_names[counter_nlo] << ": " << eig << " | " << abs(eig - i / 2) << std::endl;
        // counter_nlo++;
      }

      if (check_correction_ratio)
      {
        vector<complexd> LO_eigenvalues = get_LO_scattering_eigenvalues_ordered(s);
        // flip order of plus/minus to match conventions
        vector<int> LO_eigenvalue_order = {2, 1, 4, 3, 6, 5, 8, 7, 9, 11, 10, 12};
        for (size_t num = 0; num < LO_eigenvalues.size(); num++)
        {
          // needs to be normalized in accordance to NLO unitarity
          complexd LO_eigenvalue = -(LO_eigenvalues[LO_eigenvalue_order[num]]) / (32.0 * pi * pi);
          // only check for lo eigenvalues larger than 1/16pi as otherwise this may break down
          if (abs(LO_eigenvalue) > 1 / (16.0 * pi))
          {
            double ratio = abs(NLO_eigenvalues[num]) / abs(LO_eigenvalue);
            if (ratio > 1.0)
            {
              error_ratio += abs(ratio - 1.0);
            }
          }
        }
      }

      return -cutoff_soft_square(error*0.7 + error_ratio*0.6, 71, 1e6);
    }

    // basic perturbativity likelihood (only checks that lambdas are less than 4pi)
    double get_simple_perturbativity_LogLikelihood(const SubSpectrum& he)
    {
      // get required spectrum info
      ThdmSpec s(he,ThdmSpecFill::FILL_GENERIC);

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

      return -cutoff_soft_square(error, 71, 1e6);
    }

    // perturbativity likelihood (checks that all quartic couplings are less than 4pi)
    double get_perturbativity_LogLikelihood(const SubSpectrum& he)
    {
      // get required spectrum info
      ThdmSpec s(he,ThdmSpecFill::FILL_GENERIC | ThdmSpecFill::FILL_ANGLES | ThdmSpecFill::FILL_HIGGS | ThdmSpecFill::FILL_PHYSICAL);

      //-----------------------------
      // all values < 4*PI for perturbativity conditions
      const double perturbativity_upper_limit = 4 * pi;
      double error = 0.0;
      double previous_coupling = 0.0;
      // using generic model so calculate chi^2 from all possible 4 higgs interactions
      complexd hhhh_coupling;


      // particle types h0=1, H0, A0, G0, Hp, Hm, Gp, Gm;
      for (int p1 = 1; p1 < 7; p1++)
      {
        for (int p2 = 1; p2 < 7; p2++)
        {
          for (int p3 = 1; p3 < 7; p3++)
          {
            for (int p4 = 1; p4 < 7; p4++)
            {
              // Don't check perturbativity of goldstone G0
              if (p1 != 4 && p2 != 4 && p3 != 4 && p4 != 4)
              {
                hhhh_coupling = get_quartic_coupling_higgs(s, (scalar_type)p1, (scalar_type)p2, (scalar_type)p3, (scalar_type)p4);
                if (abs(hhhh_coupling) > perturbativity_upper_limit)
                {
                  if (previous_coupling != abs(hhhh_coupling))
                  {
                    error += abs(hhhh_coupling) - perturbativity_upper_limit;
                  }
                  previous_coupling = abs(hhhh_coupling);
                }
              }
            }
          }
        }
      }

      return -cutoff_soft_square(error, 113, 1e6);
    }

    // vacuum metastability constraint (checked as part of the stability likelihood)
    bool check_minimum_is_global(const SubSpectrum& he)
    {
      // Reference: https://arxiv.org/abs/1303.5098
      // calculates the global minimum discriminant D
      // D>0 is a necessary & sufficient condition to have a global minimum
      // Z2-aligned models only
      // returns true if the condition is met (meta-stable), otherwise false

      // get required spectrum info
      ThdmSpec s(he,ThdmSpecFill::FILL_GENERIC | ThdmSpecFill::FILL_ANGLES | ThdmSpecFill::FILL_PHYSICAL);

      const double lambda1 = s.lam1;
      const double lambda2 = s.lam2;
      const double lambda6 = s.lam6;
      const double lambda7 = s.lam7;
      const double tb = s.tanb;
      const double m12_2 = s.m122;

      // ensure that we have a Z2-symmetric scalar sector
      check_Z2(lambda6, lambda7, "check_minimum_is_global");

      // minimization conditions to recover m11^2 and m22^2
      const double m11_2 = s.m112;
      const double m22_2 = s.m222;

      // TODO: seems like an imaginary k is invalid?
      auto k2 = sqrt(complexd(lambda1 / lambda2));
      auto k = sqrt(k2);
      const complexd discriminant = m12_2 * (m11_2 - k2 * m22_2) * (tb - k);

      // check for NaN - should *not* happen but has crashed scans before. Most probable culprit is k when lambda2 = 0. TODO: find workaround
      if (std::isnan(discriminant.real()) || std::isnan(discriminant.imag()))
      {
        std::ostringstream msg;
        msg << "SpecBit warning (non-fatal): global_minimum_discriminant_LogLikelihood is returning NaN. Ivnvalidating point. Reporting calculated values:"
            << " k= " << k << ", m11^2 = " << m11_2 << ", m22^2 = " << m22_2 << std::endl;
        SpecBit_warning().raise(LOCAL_INFO, msg.str());
        std::cerr << msg.str();
        invalid_point().raise(msg.str());
      }

      // calculate error & loglike
      bool is_stable = (discriminant.real() >= -0. && discriminant.imag() >= -0.);

      return is_stable;
    }

    // vacuum stability likelihood
    double get_stability_LogLikelihood(const SubSpectrum& he, bool checkMeta)
    {
      // Reference: https://arxiv.org/abs/hep-ph/0605142 (A.2)
      //            https://arxiv.org/abs/0902.0851 (also see THDMC code)

      // WARNING: the conditions for the GCP-2HDM with lam6,7 != 0 are incomplete

      ThdmSpec s(he, ThdmSpecFill::FILL_GENERIC | ThdmSpecFill::FILL_ANGLES | ThdmSpecFill::FILL_HIGGS | ThdmSpecFill::FILL_PHYSICAL);

      double error = 0.;

      error += std::max(0.0, -s.lam1);
      // gamma = pi/2
      error += std::max(0.0, -s.lam2);
      // rho = 0

      // get required spectrum info
      // ThdmSpec s(he,ThdmSpecFill::FILL_GENERIC);
      const double sqrt_lam12 = sqrt(s.lam1 * s.lam2);

      if (std::isnan(sqrt_lam12))
      {
        // rather than throwing an invalid point, 
        // better to just give an awful likelihood
        error *= 4;
      }
      else
      {
        // gamma = 0
        error += std::max(0.0, -s.lam3 - sqrt_lam12);

        // conditions for a Z2-symmetric scalar potential
        if (abs(s.lam6) < 1e-12 && abs(s.lam7) < 1e-12)
        {
          // cos(theta) = 0
          error += std::max(0.0, -s.lam3 - s.lam4 + abs(s.lam5) - sqrt_lam12);
        }
        // conditions for the General CP-conserving 2HDM
        else
        {
          // cos(theta) = 0
          error += std::max(0.0, -s.lam3 - s.lam4 + s.lam5 - sqrt_lam12);

          // a calculation needed for the conditions below
          double calc = (1./2.)*(-s.lam4*s.lam3*s.lam3+s.lam4*s.lam2*s.lam1-s.lam3*s.lam3*s.lam5+s.lam2*s.lam1*s.lam5-2*s.lam7*s.lam7*s.lam1+4*s.lam6*s.lam7*s.lam3-2*s.lam2*s.lam6*s.lam6)/(s.lam4*s.lam1+s.lam4*s.lam2-2*s.lam4*s.lam3+s.lam1*s.lam5-2*s.lam3*s.lam5+s.lam2*s.lam5-2*s.lam6*s.lam6-2*s.lam7*s.lam7+4*s.lam6*s.lam7);
          
          // cos(theta) = +-1 AND abs(rho) <= 1 AND 0<gamma<pi/2 (first gamma solution)
          double rho,gamma,cosg;
          gamma = acos(sqrt((4*s.lam6*s.lam7-2*s.lam4*s.lam3+s.lam4*s.lam2+s.lam4*s.lam1-2*s.lam3*s.lam5+s.lam2*s.lam5+s.lam1*s.lam5-2*s.lam6*s.lam6-2*s.lam7*s.lam7)*(-2*s.lam7*s.lam7+s.lam2*s.lam5+s.lam4*s.lam2-s.lam3*s.lam5-s.lam4*s.lam3+2*s.lam6*s.lam7))/(4*s.lam6*s.lam7-2*s.lam4*s.lam3+s.lam4*s.lam2+s.lam4*s.lam1-2*s.lam3*s.lam5+s.lam2*s.lam5+s.lam1*s.lam5-2*s.lam6*s.lam6-2*s.lam7*s.lam7));
          cosg  = cos(gamma);
          rho   = sin(gamma)*(s.lam7-cosg*cosg*s.lam7+s.lam6*cosg*cosg)/(cosg*(-s.lam5-s.lam4+cosg*cosg*s.lam4+cosg*cosg*s.lam5));
          
          if (abs(rho) <= 1.0 && gamma >= 0.0 && gamma <= pi/2.)
          {
            error += std::max(0.0, -calc);
          }

          // cos(theta) = +-1 AND abs(rho) <= 1 AND 0<gamma<pi/2 (second gamma solution)
          gamma = pi-gamma;
          cosg  = cos(gamma);
          rho   = sin(gamma)*(s.lam7-cosg*cosg*s.lam7+s.lam6*cosg*cosg)/(cosg*(-s.lam5-s.lam4+cosg*cosg*s.lam4+cosg*cosg*s.lam5));

          if (abs(rho) <= 1.0 && gamma >= 0.0 && gamma <= pi/2.)
          {
            error += std::max(0.0, -calc);
          }

          // a calculation needed for the conditions below
          double calc2 = (1./2.)*(s.lam1*s.lam2*s.lam5-s.lam1*s.lam7*s.lam7-s.lam5*s.lam5*s.lam5+2*s.lam5*s.lam5*s.lam4+2*s.lam5*s.lam5*s.lam3-s.lam5*s.lam4*s.lam4-2*s.lam5*s.lam6*s.lam7-s.lam5*s.lam3*s.lam3-2*s.lam5*s.lam4*s.lam3-s.lam6*s.lam6*s.lam2+2*s.lam6*s.lam7*s.lam3+2*s.lam6*s.lam7*s.lam4)/(s.lam1*s.lam5+2*s.lam6*s.lam7-2*s.lam3*s.lam5+s.lam2*s.lam5-2*s.lam5*s.lam4-s.lam6*s.lam6-s.lam7*s.lam7+2*s.lam5*s.lam5);
          
          // rho=1 AND abs(ct) <= 1 AND abs(gamma) <= pi/2
          double ct = (1./2.)*(-s.lam6*s.lam3-s.lam6*s.lam4+s.lam6*s.lam2+s.lam5*s.lam6+s.lam7*s.lam1-s.lam7*s.lam3-s.lam7*s.lam4+s.lam7*s.lam5)/sqrt((-s.lam3*s.lam5-s.lam5*s.lam4+s.lam2*s.lam5+s.lam5*s.lam5+s.lam6*s.lam7-s.lam7*s.lam7)*(s.lam1*s.lam5+s.lam6*s.lam7-s.lam3*s.lam5+s.lam5*s.lam5-s.lam5*s.lam4-s.lam6*s.lam6));
          gamma     = atan(sqrt((-s.lam3*s.lam5-s.lam5*s.lam4+s.lam2*s.lam5+s.lam5*s.lam5+s.lam6*s.lam7-s.lam7*s.lam7)*(s.lam1*s.lam5+s.lam6*s.lam7-s.lam3*s.lam5+s.lam5*s.lam5-s.lam5*s.lam4-s.lam6*s.lam6))/(-s.lam3*s.lam5-s.lam5*s.lam4+s.lam2*s.lam5+s.lam5*s.lam5+s.lam6*s.lam7-s.lam7*s.lam7));
          
          if (abs(ct) <= 1.0 && abs(gamma) <= pi/2.)
          {
            error += std::max(0.0, -calc2);
          }

          // rho=1 and ct=+1
          // TODO: don't have an analytical form for these...
        }

        // check meta-stability
        if (checkMeta)
        {
          if (!check_minimum_is_global(he)) return -L_MAX;
        }

      }

      return -cutoff_soft_square(error, 99, 1e6);
    }

    // loop correction perturbativity constraint on the light scalar, h0
    double get_light_scalar_mass_correction_LogLikelihood(const SubSpectrum& he)
    {
      const double mh_running = he.get(Par::mass1, "h0", 1), mh_pole = he.get(Par::Pole_Mass, "h0", 1);
      const double mh_splitting = abs(mh_pole - mh_running);
      double result = 0.0;

      double error = mh_splitting/mh_running - 0.5;
      result += -cutoff_soft_square(error, 1.0, 1e6);
      
      return result;
    }

    // loop correction perturbativity constraint on the heavy scalars, H0,A0 & H+/H-
    double get_heavy_scalar_mass_correction_LogLikelihood(const SubSpectrum& he)
    {
      vector<str> heavy_scalars = {"h0_2", "A0", "H+"};
      double result = 0.0;

      for (auto& scalar : heavy_scalars)
      {
        double mass_running = he.get(Par::mass1, scalar);
        double mass_pole = he.get(Par::Pole_Mass, scalar);
        double mass_splitting = abs(mass_running - mass_pole);

         double error = mass_splitting/mass_running - 0.5;
         result += -cutoff_soft_square(error, 1.0, 1e6);
      }
      return result;
    }

    // allows the user to enforce upper mass limit on all scalars and lower mass limit on heavy scalars
    double get_scalar_mass_range_LogLikelihood(const SubSpectrum& he, const double min_mass, const double max_mass)
    {
      const double mh0 = he.get(Par::Pole_Mass, "h0", 1);
      const double mH0 = he.get(Par::Pole_Mass, "h0", 2);
      const double mA0 = he.get(Par::Pole_Mass, "A0");
      const double mHp = he.get(Par::Pole_Mass, "H+");

      double result = 0;
      if (mh0 > max_mass || mH0 > max_mass || mA0 > max_mass || mHp > max_mass) result = -L_MAX;
      if (mh0 < 0.0 || mH0 < min_mass || mA0 < min_mass || mHp < min_mass) result = -L_MAX;
      return result;
    }


    /// ==========================
    /// == likelihood functions ==
    /// ==========================


    typedef std::function<double(const SubSpectrum&)> LL_type;

    // helper function get list of energy scales, check constraint at each, and get the worst performer
    double get_worst_LL_of_all_scales(const Spectrum& spec, LL_type LL, bool is_FS_model, double other_scale)
    {
      // we always check the input scale 
      vector<double> scales_to_check = { RunScale::INPUT };

      // also check the custom scale from the yaml file. Skip if tree level
      if (other_scale != RunScale::NONE && other_scale != RunScale::INPUT && is_FS_model) 
        scales_to_check.push_back(other_scale);

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
          auto he = spec.clone_HE();
          he->RunToScale(scale);
          result = std::min(LL(*he), result);
        }

        // don't waste time when it will be invalid anyway
        if (result < -1e7) break;
      }
      return result;
    }

    // Leading-Order unitarity constraint (soft-cutoff)
    void LO_unitarity_LogLikelihood_THDM(double &result)
    {
      // get model type and options from yaml file

      using namespace Pipes::LO_unitarity_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double other_scale = runOptions->getValueOrDef<double>(RunScale::NONE, "check_other_scale");
      const Spectrum& spec = *Dep::THDM_spectrum;

      // wrap up LogLike function & get worst performing LogLike at all scales

      LL_type LL = get_LO_unitarity_LogLikelihood;
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale);
    }

    // Next-to-Leading-Order unitarity constraint (soft-cutoff)
    void NLO_unitarity_LogLikelihood_THDM(double &result)
    {
      // get model type and options from yaml file

      using namespace Pipes::NLO_unitarity_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double other_scale = runOptions->getValueOrDef<double>(RunScale::NONE, "check_other_scale");
      bool check_corrections_ratio = runOptions->getValueOrDef<bool>(false, "check_correction_ratio");
      bool wave_function_corrections = runOptions->getValueOrDef<bool>(false, "wave_function_corrections");
      bool gauge_corrections = runOptions->getValueOrDef<bool>(false, "gauge_corrections");
      bool yukawa_corrections = runOptions->getValueOrDef<bool>(false, "yukawa_corrections");
      const Spectrum& spec = *Dep::THDM_spectrum;

      // wrap up LogLike function & get worst performing LogLike at all scales

      LL_type LL = [&](const SubSpectrum& c){ return get_NLO_unitarity_LogLikelihood(c, check_corrections_ratio, wave_function_corrections, gauge_corrections, yukawa_corrections); };  
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale);
    }

    // LO lambdas perturbativity (soft-cutoff)
    void perturbativity_lambdas_LogLikelihood_THDM(double &result)
    {
      // get model type and options from yaml file

      using namespace Pipes::perturbativity_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double other_scale = runOptions->getValueOrDef<double>(RunScale::NONE, "check_other_scale");
      const Spectrum& spec = *Dep::THDM_spectrum;

      // wrap up LogLike function & get worst performing LogLike at all scales

      LL_type LL = get_simple_perturbativity_LogLikelihood;
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale);
    }

    // perturbativity constraint (soft-cutoff)
    void perturbativity_LogLikelihood_THDM(double &result)
    {
      // get model type and options from yaml file

      using namespace Pipes::perturbativity_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double other_scale = runOptions->getValueOrDef<double>(RunScale::NONE, "check_other_scale");
      const Spectrum& spec = *Dep::THDM_spectrum;

      // wrap up LogLike function & get worst performing LogLike at all scales

      LL_type LL = get_perturbativity_LogLikelihood;
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale);
    }

    // simple perturbativity constraint on yukawas (soft-cutoff)
    void simple_perturbativity_yukawas_LogLikelihood_THDM(double &result)
    {
      using namespace Pipes::simple_perturbativity_yukawas_LogLikelihood_THDM;
      SMInputs sminputs = *Dep::SMINPUTS;
      const Spectrum spec = *Dep::THDM_spectrum;
      std::unique_ptr<SubSpectrum> he = spec.clone_HE();
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double mT = Dep::SMINPUTS->mT;
      double tanb = he->get(Par::dimensionless,"tanb");
      double error = 0.0;
      vector<double> Yukawas;

      for (int i = 1; i <= 3; i++)
       {
         for (int j = 1; j <= 3; j++)
         {
          Yukawas.push_back(he->get(Par::dimensionless, "Yd2", i, j));
          Yukawas.push_back(he->get(Par::dimensionless, "Ye2", i, j));
         }
       }
      //The Yu2 matrix is called outside in order to get the Yu2tt element
      //which has a softer perturbativity bound
      //For the moment we do not use neither Yukawas for 1-3 nor 1-2 family interactions
      Yukawas.push_back(he->get(Par::dimensionless, "Yu2", 1, 1));
      Yukawas.push_back(he->get(Par::dimensionless, "Yu2", 1, 2));
      Yukawas.push_back(he->get(Par::dimensionless, "Yu2", 1, 3));
      Yukawas.push_back(he->get(Par::dimensionless, "Yu2", 2, 1));
      Yukawas.push_back(he->get(Par::dimensionless, "Yu2", 2, 2));
      Yukawas.push_back(he->get(Par::dimensionless, "Yu2", 2, 3));
      Yukawas.push_back(he->get(Par::dimensionless, "Yu2", 3, 1));
      Yukawas.push_back(he->get(Par::dimensionless, "Yu2", 3, 2));
      double Yu2tt = he->get(Par::dimensionless, "Yu2", 3, 3);
      // loop over all yukawas
      for (auto & each_yukawa : Yukawas)
      {
        if (abs(each_yukawa) > sqrt(4*pi)/(sqrt(1+tanb*tanb)))
          error += abs(each_yukawa) - (sqrt(4*pi)/(sqrt(1+tanb*tanb)));
      }
      //Apply softer bound for Yu2tt
      error += abs(Yu2tt) - ((sqrt(4*pi)+((sqrt(2)*tanb*mT)/v))/(sqrt(1+tanb*tanb)));
      result = -cutoff_soft_square(error, 141, 1e6);
    }

    // vacuum stability + meta-stability constraint (soft cutoff)
    void stability_LogLikelihood_THDM(double &result)
    {
      // get model type and options from yaml file

      using namespace Pipes::stability_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double other_scale = runOptions->getValueOrDef<double>(RunScale::NONE, "check_other_scale");
      bool checkMeta = runOptions->getValueOrDef<bool>(false, "check_metastability");
      const Spectrum& spec = *Dep::THDM_spectrum;

      // wrap up LogLike function & get worst performing LogLike at all scales

      LL_type LL = [&](const SubSpectrum& c){ return get_stability_LogLikelihood(c, checkMeta); };
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale);
    }

    // checks that the corrections to h0 are perturbative (hard-cutoff)
    void light_scalar_mass_corrections_LogLikelihood_THDM(double &result)
    {
      // get model type and options from yaml file

      using namespace Pipes::light_scalar_mass_corrections_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double other_scale = runOptions->getValueOrDef<double>(RunScale::NONE, "check_other_scale");
      const Spectrum& spec = *Dep::THDM_spectrum;

      // wrap up LogLike function & get worst performing LogLike at all scales

      LL_type LL = get_light_scalar_mass_correction_LogLikelihood;
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale);
    }

    // checks that the corrections to H0,A0,Hp are perturbative (hard-cutoff)
    void heavy_scalar_mass_corrections_LogLikelihood_THDM(double &result)
    {
      // get model type and options from yaml file

      using namespace Pipes::heavy_scalar_mass_corrections_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double other_scale = runOptions->getValueOrDef<double>(RunScale::NONE, "check_other_scale");
      const Spectrum& spec = *Dep::THDM_spectrum;

      // wrap up LogLike function & get worst performing LogLike at all scales

      LL_type LL = get_heavy_scalar_mass_correction_LogLikelihood;
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale);
    }

    // LIKELIHOOD: guides scanner towards mh = 125 GeV. Use to improve performance of HiggsSignals (soft-cutoff)
    void higgs_mass_LogLikelihood(double &result)
    {
      using namespace Pipes::higgs_mass_LogLikelihood;

      const double higgs_mass_uncertainty = runOptions->getValueOrDef<double>(2.5, "higgs_mass_uncertainty");
      const double valid_range = runOptions->getValueOrDef<double>(60, "valid_range");

      const Spectrum &spec = *Dep::THDM_spectrum;
      const double mh_pole = spec.get_HE().get(Par::Pole_Mass, *Dep::SM_like_scalar);
      constexpr double mh_exp = 125.15;   // experimental value of Higgs mass measured by others GeV
      // constexpr double mh_err_exp = 0.14; // experimental uncertainty GeV
      double model_invalid_for_lnlike_below = -1e6;

      double mass_err = std::abs(mh_pole - mh_exp);

      // scale it so that going 300 GeV above/below the measured higgs mass hits the threshold to bail on the point
      // no penalty if we are within 10 GeV of exp. value
      result = model_invalid_for_lnlike_below * (std::max(0.0, mass_err - higgs_mass_uncertainty) / valid_range);
    }

    // only keeps points that correspond to hidden higgs scenario (hard-cutoff)
    void hidden_higgs_scenario_LogLikelihood_THDM(double& result)
    {
      using namespace Pipes::hidden_higgs_scenario_LogLikelihood_THDM;
      const bool hidden_higgs_scenario = runOptions->getValueOrDef<bool>(true, "hidden_higgs_scenario");
      const Spectrum& spec = *Dep::THDM_spectrum;

      const double mh_pole = spec.get_HE().get(Par::Pole_Mass, *Dep::SM_like_scalar);
      const double mH_pole = spec.get_HE().get(Par::Pole_Mass, *Dep::additional_scalar);
      // constexpr double mh_exp = 125.10; // experimental value of Higgs mass measured by others GeV

      // Hidden-Higgs scenario means the additional scalar has a smaller mass than the SM-like scalar
      if (mH_pole < mh_pole && hidden_higgs_scenario)
        result = -L_MAX;
      else if (mH_pole > mh_pole && !hidden_higgs_scenario)
        result = -L_MAX;
      else
        result = 0;
    }

    // mass range for each heavy scalar, specified in YAML file (soft-cutoff)
    void scalar_mass_range_LogLikelihood_THDM(double &result)
    {
      // get model type and options from yaml file

      using namespace Pipes::scalar_mass_range_LogLikelihood_THDM;
      bool is_FS_model = ModelInUse("THDMatQ") ? true : false;
      double other_scale = runOptions->getValueOrDef<double>(RunScale::NONE, "check_other_scale");
      const double max_scalar_mass = runOptions->getValueOrDef<double>(1e5, "maximum_scalar_mass");
      const double min_scalar_mass = runOptions->getValueOrDef<double>(-1e5, "minimum_scalar_mass");
      const Spectrum& spec = *Dep::THDM_spectrum;

      // wrap up LogLike function & get worst performing LogLike at all scales

      LL_type LL = [&](const SubSpectrum& c){ return get_scalar_mass_range_LogLikelihood(c, min_scalar_mass, max_scalar_mass); };
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale);
    }


    /// ==========================
    /// == Higgs coupling table ==
    /// ==========================

    void test(const Spectrum& s, HiggsCouplingsTable &h)
    {
      const SMInputs& sminputs = s.get_SMInputs();
      const double v2 = 1.0 / (sqrt(2.0) * sminputs.GF);
      const double vev = sqrt(v2);
      double alpha = s.get(Par::dimensionless, "alpha");
      double beta = s.get(Par::dimensionless, "beta");
      double ca = cos(alpha), sa = sin(alpha);
      double cb = cos(beta), sb = sin(beta);
      const vector<double> mU = { sminputs.mU, sminputs.mCmC, sminputs.mT };
      const vector<double> mD = { sminputs.mD, sminputs.mS, sminputs.mBmB };
      const vector<double> mE = { sminputs.mE, sminputs.mMu, sminputs.mTau };

      double C_tt2 = sqr((ca/sb));
      double C_WW = sin(beta-alpha);

      std::cout << "(theory) C_tt2 " << C_tt2 << std::endl;
      std::cout << "(actual) C_tt2 " << h.C_tt2[0] << std::endl;
      std::cout << "(theory) C_WW " << C_WW << std::endl;
      std::cout << "(actual) C_WW " << h.C_WW[0] << std::endl;


        // result.C_WW[i] = sqrt(result.compute_effective_coupling(i, std::pair<int, int>(24, 0), std::pair<int, int>(-24, 0)));
        // result.C_ZZ[i] = sqrt(result.compute_effective_coupling(i, std::pair<int, int>(23, 0), std::pair<int, int>(23, 0)));
        // result.C_tt2[i] = result.compute_effective_coupling(i, std::pair<int, int>(6, 1), std::pair<int, int>(-6, 1));
        // result.C_bb2[i] = result.compute_effective_coupling(i, std::pair<int, int>(5, 1), std::pair<int, int>(-5, 1));
        // result.C_cc2[i] = result.compute_effective_coupling(i, std::pair<int, int>(4, 1), std::pair<int, int>(-4, 1));
        // result.C_tautau2[i] = result.compute_effective_coupling(i, std::pair<int, int>(15, 1), std::pair<int, int>(-15, 1));
        // result.C_gaga2[i] = result.compute_effective_coupling(i, std::pair<int, int>(22, 0), std::pair<int, int>(22, 0));
        // result.C_gg2[i] = result.compute_effective_coupling(i, std::pair<int, int>(21, 0), std::pair<int, int>(21, 0));
        // result.C_mumu2[i] = result.compute_effective_coupling(i, std::pair<int, int>(13, 1), std::pair<int, int>(-13, 1));
        // result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int, int>(23, 0), std::pair<int, int>(22, 0));
        // result.C_ss2[i] = result.compute_effective_coupling(i, std::pair<int, int>(3, 1), std::pair<int, int>(-3, 1));
    }

    /// Put together the Higgs couplings for the THDM, using only partial widths
    void THDM_higgs_couplings_pwid(HiggsCouplingsTable &result)
    {
      using namespace Pipes::THDM_higgs_couplings_pwid;

      // Retrieve spectrum contents
      const Spectrum fullspectrum = *Dep::THDM_spectrum;

      //const DecayTable::Entry& decays = *Dep::Higgs_decay_rates;
      const SubSpectrum &spec = fullspectrum.get_HE();

      // Set up neutral Higgses
      static const vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
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

      if (ModelInUse("Inert2"))
      {
        str DarkMatter_ID = *Dep::DarkMatter_ID;
        str DarkMatterConj_ID = *Dep::DarkMatterConj_ID;
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

    // Put together the Higgs couplings for the THDM, using 2HDMC
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
      const double g = 2.*mW/vev;
      const double costw = sqrt(1. - spec.get(Par::dimensionless, "sinW2"));

      // Set up neutral Higgses
      static const vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
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
        result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int, int>(23, 0), std::pair<int, int>(22, 0));
      }

      // Initiate 2HDM container
      THDMsafe container;
      BEreq::setup_thdmc_spectrum(container, *Dep::THDM_spectrum);

      // set up and fill the THDM couplings
      THDM_couplings couplings;
      fill_THDM_couplings_struct(couplings, container.obj);

      // SM-like couplings
      vector<THDM_couplings> couplings_SM_like;
      THDM_couplings SM_couplings;

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


    }

      // list of SM & BSM particles
    enum {u1,u2,u3,d1,d2,d3,e1,e2,e3,v1,v2,v3, u1c,u2c,u3c,d1c,d2c,d3c,e1c,e2c,e3c,v1c,v2c,v3c, a,z,wp,wm,g, hh,hx,ha,hp,hm};
    const vector<str> names = {"u1","u2","u3","d1","d2","d3","e1","e2","e3","v1","v2","v3", "u1c","u2c","u3c","d1c","d2c","d3c","e1c","e2c","e3c","v1c","v2c","v3c", "a","z","wp","wm","g", "hh","hx","ha","hp","hm"};
    const vector<double> electric_charge = {+2/3.,+2/3.,+2/3.,-1/3.,-1/3.,-1/3.,-1,-1,-1,0,0,0,-2/3.,-2/3.,-2/3.,+1/3.,+1/3.,+1/3.,+1,+1,+1,0,0,0, 0,0,+1,-1,0, 0,0,0,+1,-1};

    using coupling = std::pair<vector<int>,std::pair<complexd,complexd>>;

    void print_coupling(const coupling c)
    {
      str parts = "[";
      for (auto& i : c.first) parts += names[i] + ",";
      parts += "] = " + to_string(c.second.first) + " + g5 x ( " + to_string(c.second.second) +" )";
      std::cout << parts << std::endl;
    }

    complexd hgaga_hacked(const double mh)
    {
      using namespace Pipes::get_coupling_table;
      const DecayTable::Entry* decay = &(*Dep::Higgs_decay_rates2);
      if (*Dep::additional_scalar != "h0_2")
        decay = &(*Dep::h0_2_decay_rates2);
      const double alpha = 0.0072973525, v = 246.22;
      const double C1 = sqr(alpha)*cub(mh) / (256*cub(pi)*sqr(v));
      const double C2 = alpha / (pi*v);
      const double Gamma = decay->width_in_GeV*decay->BF(vector<str>({"gamma","gamma"}));
      const complexd result = -ii*sqrt((1/4.)*Gamma/C1)*C2;
      return result;
    }

    complexd hgg_hacked(const double mh)
    {
      using namespace Pipes::get_coupling_table;
      const DecayTable::Entry* decay = &(*Dep::Higgs_decay_rates2);
      if (*Dep::additional_scalar != "h0_2")
        decay = &(*Dep::h0_2_decay_rates2);
      const double alpha = 0.1185, v = 246.22;
      const double C1 = sqr(alpha)*cub(mh) / (32*cub(pi)*sqr(v));
      const double C2 = alpha / (pi*v);
      const double Gamma = decay->width_in_GeV*decay->BF(vector<str>({"g","g"}));
      const complexd result = -ii*sqrt((1/4.)*Gamma/C1)*C2;
      return result;
    }

    complexd hgaZ_hacked(const double mh)
    {
      using namespace Pipes::get_coupling_table;
      const DecayTable::Entry* decay = &(*Dep::Higgs_decay_rates2);
      if (*Dep::additional_scalar != "h0_2")
        decay = &(*Dep::h0_2_decay_rates2);
      const double alpha = 0.0072973525, alphaZ=0.0072973525/tan(0.5016296), v = 246.22;
      const double C1 = alpha*alphaZ*cub(mh) / (256*cub(pi)*sqr(v));
      const double C2 = sqrt(alpha*alphaZ) / (pi*v);
      const double Gamma = decay->width_in_GeV*decay->BF(vector<str>({"gamma","Z0"}));
      const complexd result = -ii*sqrt((1/4.)*Gamma/C1)*C2;
      // std::cout << "hgaZ " << " C1 " << C1 << " C2 " << C2 << " Gamma " << Gamma << " result " << result << "\n";
      return result;
    }

    void get_coupling_table_SM(coupling_table& result)
    {
      // using namespace Pipes::get_coupling_table;
      // const THDM_TYPE THDM_type = *Dep::THDM_Type;
      // const Spectrum fullspectrum = *Dep::THDM_spectrum;
      // auto& sm = fullspectrum.get_SMInputs();

      enum {u1,u2,u3,d1,d2,d3,e1,e2,e3,v1,v2,v3, u1c,u2c,u3c,d1c,d2c,d3c,e1c,e2c,e3c,v1c,v2c,v3c, a,z,wp,wm,g, h1,h2,ha,hp,hm};

      // T3 for left-chiral component (always 0 for right-chiral component)
      const vector<double> T3 = 
        {+1/2.,+1/2.,+1/2.,-1/2.,-1/2.,-1/2.,-1/2.,-1/2.,-1/2.,+1/2.,+1/2.,+1/2.,  +1/2.,+1/2.,+1/2.,-1/2.,-1/2.,-1/2.,-1/2.,-1/2.,-1/2.,+1/2.,+1/2.,+1/2.,  0,0,0,0,0, 0,0,0,0,0};

      const double gs = 1.214; // Strong coupling constant
      const double W = 0.5016296; // Weak mixing angle
      const double ge = 0.3028221204; // QED coupling constant
      const double sinW = sin(W), cosW = cos(W), tanW = tan(W), cotW = 1/tanW;

      // CKM matrix

      constexpr double deg = 0.0174532925;
      constexpr double p12 = 13.04*deg, p13 = 0.201*deg, p23 = 2.38*deg, alpha = 68.75*deg;
      const double cA = cos(p12), cB = cos(p13), cC = cos(p23), sA = sin(p12), sB = sin(p13), sC = sin(p23);
      const complexd eA = exp(ii*alpha), emA = exp(-ii*alpha);
      const vector<vector<complexd>> V = {

        {cA*cB, sA*cB, sB*emA},
        {-sA*cC-cA*sC*sB*eA, cA*cC-sA*sC*sB*eA, sC*cB},
        {sA*sC-cA*cC*sB*eA, -cA*sC-sA*cC*sB*eA, cC*cB}

      };

      // read this like: part in [first,last]
      auto in = [&](int part, int first, int last)
      {
        return part >= first && part <= last;
      };

      for (int i=u1; i<=hm; ++i)
      {
        for (int j=i; j<=hm; ++j)
        {
          for (int k=j; k<=hm; ++k)
          {

            // skip all Higgs couplings

            if (i >= h1 || j >= h1 || k >= h1)
              continue;

            // higgs-higgs

            // (skip)

            // higgs-gauge

            // (skip)

            // higgs-fermion

            // (skip)

            // gauge-gauge

            if (i == a && j == wp && k == wm) // aww
              result.push_back({{i,j,k},{+ii*ge,0}});

            if (i == z && j == wp && k == wm) // zww
              result.push_back({{i,j,k},{+ii*ge*cotW,0}});

            if (i == g && j == g && k == g) // ggg
              result.push_back({{i,j,k},{+ii*gs,0}});

            // gauge-fermion

            if (in(i,u1,d3) && in(j,u1c,d3c) && (i == j-u1c+u1) && k == g) // qqg
              result.push_back({{i,j,k},{-ii*gs,0}});

            if (in(i,u1,e3) && in(j,u1c,e3c) && (i == j-u1c+u1) && k == a) // ffa
              result.push_back({{i,j,k},{-ii*ge*electric_charge[i],0}});

            complexd tmp = ii*ge/(cosW*sinW);
            if (in(i,u1,v3) && in(j,u1c,v3c) && (i == j-u1c+u1) && k == z) // ffz
              result.push_back({{i,j,k},{tmp*(0.5*T3[i]-electric_charge[i]*sqr(sinW)),-tmp*0.5*T3[i]}});

            int x1 = i-d1, x2 = j-u1c;
            complexd tmp2 = ii*ge/(2*sqrt(2)*sinW);
            if (in(i,d1,d3) && in(j,u1c,u3c) && k == wp) // udw
              result.push_back({{i,j,k},{tmp2*V[x2][x1],-tmp2*V[x2][x1]}});

            x1 = i-u1, x2 = j-d1c;
            if (in(i,u1,u3) && in(j,d1c,d3c) && k == wm) // duw
              result.push_back({{i,j,k},{tmp2*std::conj(V[x1][x2]),-tmp2*std::conj(V[x1][x2])}});

            if (in(i,e1,e3) && in(j,v1c,v3c) && (i == j-v1c+e1) && k == wp) // vew
              result.push_back({{i,j,k},{tmp2,-tmp2}});

            if (in(i,v1,v3) && in(j,e1c,e3c) && (i == j-e1c+v1) && k == wm) // evw
              result.push_back({{i,j,k},{tmp2,-tmp2}});

            // fermion-fermion

            // (all zero)

          }
        }
      }

      for (int i=u1; i<=hm; ++i)
      {
        for (int j=i; j<=hm; ++j)
        {
          for (int k=j; k<=hm; ++k)
          {
            for (int l=j; l<=hm; ++l)
            {
              // skip all Higgs couplings

              if (i >= h1 || j >= h1 || k >= h1 || l >= h1)
                continue;

              // higgs-higgs

              // (skip)

              // higgs-gauge

              // (skip)

              // higgs-fermion

              // (skip)

              // gauge-gauge

              if (i == a && j == a && k == wp && l == wm) // aaww
                result.push_back({{i,j,k,l},{+ii*sqr(ge),0}});

              if (i == z && j == z && k == wp && l == wm) // zzww
                result.push_back({{i,j,k,l},{+ii*sqr(ge*cotW),0}});

              if (i == wp && j == wp && k == wm && l == wm) // wwww
                result.push_back({{i,j,k,l},{-ii*sqr(ge/sinW),0}});

              if (i == a && j == z && k == wp && l == wm) // azww
                result.push_back({{i,j,k,l},{-ii*sqr(ge)*cotW,0}});

              if (i == g && j == g && k == g && l == g) // gggg
                result.push_back({{i,j,k,l},{-ii*sqr(gs),0}});

              // gauge-fermion

              // (all zero)

              // fermion-fermion

              // (all zero)
            }
          }
        }
      }

    }

    void get_coupling_table(coupling_table& result)
    {
      using namespace Pipes::get_coupling_table;

      const Spectrum fullspectrum = *Dep::THDM_spectrum;
      THDMsafe container;
      BEreq::setup_thdmc_spectrum(container, *Dep::THDM_spectrum);
      result.clear();
      auto& sm = fullspectrum.get_SMInputs();
      bool swapped_mass_hierarchy = (fullspectrum.get(Par::dimensionless, "cosba") == 1);
      // std::cout << "swapped_mass_hierarchy" << swapped_mass_hierarchy << std::endl;
      str SM_like_scalar_name = *Dep::SM_like_scalar;
      str additional_scalar_name = *Dep::additional_scalar;

      // fill in mass table for later use
      vector<double> masses(names.size(),0);

      // "a","z","wp","wm","g", "h1","h2","ha","hp","hm"};
      masses[u1] = sm.mU;
      masses[u2] = sm.mCmC;
      masses[u3] = sm.mT;
      masses[d1] = sm.mD;
      masses[d2] = sm.mS;
      masses[d3] = sm.mBmB;
      masses[e1] = sm.mE;
      masses[e2] = sm.mMu;
      masses[e3] = sm.mTau;
      masses[v1] = 0;
      masses[v2] = 0;
      masses[v3] = 0;
      masses[u1c] = sm.mU;
      masses[u2c] = sm.mCmC;
      masses[u3c] = sm.mT;
      masses[d1c] = sm.mD;
      masses[d2c] = sm.mS;
      masses[d3c] = sm.mBmB;
      masses[e1c] = sm.mE;
      masses[e2c] = sm.mMu;
      masses[e3c] = sm.mTau;
      masses[v1c] = 0;
      masses[v2c] = 0;
      masses[v3c] = 0;
      masses[a] = 0;
      masses[z] = sm.mZ;
      masses[wp] = fullspectrum.get(Par::Pole_Mass, "W+");
      masses[wm] = fullspectrum.get(Par::Pole_Mass, "W+");
      masses[g] = 0;
      masses[hh] = fullspectrum.get(Par::Pole_Mass, SM_like_scalar_name);
      masses[hx] = fullspectrum.get(Par::Pole_Mass, additional_scalar_name);
      masses[ha] = fullspectrum.get(Par::Pole_Mass, "A0");
      masses[hp] = fullspectrum.get(Par::Pole_Mass, "H-");
      masses[hm] = fullspectrum.get(Par::Pole_Mass, "H-");

      // convert particle number to THDMC number
      auto to_thdmc = [&](int part)
      {
        if (swapped_mass_hierarchy && part == hh) return 2;
        if (swapped_mass_hierarchy && part == hx) return 1;
        if (part >= u1 && part <= u3) return part-u1+1;
        if (part >= d1 && part <= d3) return part-d1+1;
        if (part >= e1 && part <= e3) return part-e1+1;
        if (part >= v1 && part <= v3) return part-v1+1;
        if (part >= u1c && part <= u3c) return part-u1c+1;
        if (part >= d1c && part <= d3c) return part-d1c+1;
        if (part >= e1c && part <= e3c) return part-e1c+1;
        if (part >= v1c && part <= v3c) return part-v1c+1;
        if (part >= a && part <= wm) return std::min(part,(int)wp)-a+1;
        if (part >= hh && part <= hm) return std::min(part,(int)hp)-hh+1;
        SpecBit_error().raise(LOCAL_INFO, "invalid particle");
        return -1;
      };

      // read this like: part in [first,last]
      auto in = [&](int part, int first, int last)
      {
        return part >= first && part <= last;
      };

      auto equal = [&](double a, double b)
      {
        return std::abs(a-b) < 1e-10;
      };

      // conserved & approximately conserved charges

      const vector<double> e1_number = 
      {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0, 0,0,0,0,0, 0,0,0,0,0};
      const vector<double> e2_number = 
      {0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,-1,0,0,-1,0, 0,0,0,0,0, 0,0,0,0,0};
      const vector<double> e3_number = 
      {0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,-1,0,0,-1, 0,0,0,0,0, 0,0,0,0,0};
      const vector<double> u1_number = 
      {1,0,0,1,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};
      const vector<double> u2_number = 
      {0,1,0,0,1,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};
      const vector<double> u3_number = 
      {0,0,1,0,0,1,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};

      // for IDM only
      const vector<double> Z2_number = 
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0, 0,1,1,1,1};

      // just a hack to get SU(3) color conservation. We don't want to consider individually colored quarks

      const vector<double> color_number = 
      {1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0, 0,0,0,0,2, 0,0,0,0,0};

      // loop over all possible interactions (3-particle)

      for (int i=u1; i<=hm; ++i)
      {
        for (int j=i; j<=hm; ++j)
        {
          for (int k=j; k<=hm; ++k)
          {
            // calculate charge sum of vertex
            double electric_charge_sum = electric_charge[i] + electric_charge[j] + electric_charge[k];
            double e1_number_sum = e1_number[i] + e1_number[j] + e1_number[k];
            double e2_number_sum = e2_number[i] + e2_number[j] + e2_number[k];
            double e3_number_sum = e3_number[i] + e3_number[j] + e3_number[k];
            double u1_number_sum = u1_number[i] + u1_number[j] + u1_number[k];
            double u2_number_sum = u2_number[i] + u2_number[j] + u2_number[k];
            double u3_number_sum = u3_number[i] + u3_number[j] + u3_number[k];
            double Z2_number_sum = Z2_number[i] + Z2_number[j] + Z2_number[k];
            double color_number_sum = color_number[i] + color_number[j] + color_number[k];

            if (int(Z2_number_sum) % 2 != 0) continue;

            // skip interactions that violate conservation laws
            if (!equal(electric_charge_sum,0)) continue; // (U(1) electric charge)
            if (!equal(e1_number_sum + e2_number_sum + e3_number_sum,0)) continue; // (lepton number)
            if (!equal(u1_number_sum + u2_number_sum + u3_number_sum,0)) continue; // (quark number)
            
            // Allows: qqx gxx qqg ggx ggg   qqxx gxxx qqqq ggxx qqgx qqgg gggx gggg
            if (int(color_number_sum) % 2 != 0) continue; // (SU(3) color - just a hack)

            // get rid of gxx gxxx
            // Allows: qqx qqg ggx ggg   qqxx qqqq ggxx qqgx qqgg gggx gggg
            if (equal(color_number_sum,2) && (i==g || j==g || k==g)) continue;

            // skip FCNCs (can be enabled for non-Z2 2HDM)
            if (((equal(electric_charge[i],0) && i >= a) || (equal(electric_charge[j],0) && j >= a) || (equal(electric_charge[k],0) && k >= a)) && 
                (!equal(e1_number_sum,0) || !equal(e2_number_sum,0) || !equal(e3_number_sum,0) || !equal(u1_number_sum,0) || !equal(u2_number_sum,0) || !equal(u3_number_sum,0)))
              continue;

            // skip non-BSM interactions for now
            if (i < hh && j < hh && k < hh) continue;
            
            // store results here
            complexd scalar = 0, pseudo = 0;

            // skipp hgg haa (we do them later)

            if (((i==a && j==a) || (i==g && j==g) || (i==a && j==z)) && k >= hh && k <= hm) continue;

            // call appropriate thdmc wrapper

            if (in(k,hh,hm) && in(j,d1c,d3c) && in(i,d1,d3))
              container.obj.get_coupling_hdd(to_thdmc(k),to_thdmc(i),to_thdmc(j),scalar,pseudo);
            else if (in(k,hh,hm) && in(j,u1c,u3c) && in(i,u1,u3))
              container.obj.get_coupling_huu(to_thdmc(k),to_thdmc(i),to_thdmc(j),scalar,pseudo);
            else if (in(k,hh,hm) && in(j,u1c,u3c) && in(i,d1,d3))
              container.obj.get_coupling_hdu(to_thdmc(k),to_thdmc(i),to_thdmc(j),scalar,pseudo);
            else if (in(k,hh,hm) && in(j,d1c,d3c) && in(i,u1,u3))
              container.obj.get_coupling_hud(to_thdmc(k),to_thdmc(i),to_thdmc(j),scalar,pseudo);
            else if (in(k,hh,hm) && in(j,e1c,e3c) && in(i,e1,e3))
              container.obj.get_coupling_hll(to_thdmc(k),to_thdmc(i),to_thdmc(j),scalar,pseudo);
            else if (in(k,hh,hm) && in(i,v1,v3) && in(j,e1c,e3c))
              container.obj.get_coupling_hln(to_thdmc(k),to_thdmc(i),to_thdmc(j),scalar,pseudo);
            // else if (in(k,hh,hm) && in(i,e1,e3) && in(j,v1c,v3c))
            //   container.obj.get_coupling_hln(to_thdmc(k),to_thdmc(i),to_thdmc(j),scalar,pseudo);
            else if (in(k,hh,hm) && in(i,a,wm) && in(j,a,wm))
              container.obj.get_coupling_vvh(to_thdmc(i),to_thdmc(j),to_thdmc(k),scalar);
            else if (in(k,hh,hm) && in(i,a,wm) && in(j,hh,hm))
              container.obj.get_coupling_vhh(to_thdmc(i),to_thdmc(j),to_thdmc(k),scalar);
            else if (in(k,hh,hm) && in(i,hh,hm) && in(j,hh,hm))
              container.obj.get_coupling_hhh(to_thdmc(k),to_thdmc(i),to_thdmc(j),scalar);
            else
            {
              // std::cout << "unable to get coupling: ";
              // print_coupling({{i,j,k},{scalar,pseudo}});
              continue;
            }

            result.push_back({{i,j,k},{scalar,pseudo}});
          }
        }
      }

      // do the effective couplings (needs to be afterwards)

      for (int k = hh; k<=ha; ++k)
      {
        if (k != hh) continue; // skip z2 violating for now
        result.push_back({ {a,a,k},{ hgaga_hacked(masses[k]),0.0 } });
        result.push_back({ {g,g,k},{ hgg_hacked(masses[k]),0.0 } });
        result.push_back({ {a,z,k},{ hgaZ_hacked(masses[k]),0.0 } });
        // result.push_back({ {a,a,k},{ S_gamma(k,result,masses),P_gamma(k,result,masses) } });
        // result.push_back({ {g,g,k},{ S_gluon(k,result,masses),P_gluon(k,result,masses) } });
      }

      // std::cout << "\n\nfull list of couplings:\n\n";
      // for (auto& c : result) print_coupling(c);

      // loop over all possible interactions (4-particle)

      for (int i=u1; i<=hm; ++i)
      {
        for (int j=i; j<=hm; ++j)
        {
          for (int k=j; k<=hm; ++k)
          {
            for (int l=k; l<=hm; ++l)
            {
            // calculate charge sum of vertex
            double electric_charge_sum = electric_charge[i] + electric_charge[j] + electric_charge[k] + electric_charge[l];
            double e1_number_sum = e1_number[i] + e1_number[j] + e1_number[k] + e1_number[l];
            double e2_number_sum = e2_number[i] + e2_number[j] + e2_number[k] + e2_number[l];
            double e3_number_sum = e3_number[i] + e3_number[j] + e3_number[k] + e3_number[l];
            double u1_number_sum = u1_number[i] + u1_number[j] + u1_number[k] + u1_number[l];
            double u2_number_sum = u2_number[i] + u2_number[j] + u2_number[k] + u2_number[l];
            double u3_number_sum = u3_number[i] + u3_number[j] + u3_number[k] + u3_number[l];
            double Z2_number_sum = Z2_number[i] + Z2_number[j] + Z2_number[k] + Z2_number[l];
            double color_number_sum = color_number[i] + color_number[j] + color_number[k] + color_number[l];

            if (int(Z2_number_sum) % 2 != 0) continue;

            // skip interactions that violate conservation laws
            if (!equal(electric_charge_sum,0)) continue; // (U(1) electric charge)
            if (!equal(e1_number_sum + e2_number_sum + e3_number_sum,0)) continue; // (lepton number)
            if (!equal(u1_number_sum + u2_number_sum + u3_number_sum,0)) continue; // (quark number)
            
            // Allows: qqx gxx qqg ggx ggg   qqxx gxxx qqqq ggxx qqgx qqgg gggx gggg
            if (int(color_number_sum) % 2 != 0) continue; // (SU(3) color - just a hack)

            // get rid of gxx gxxx
            // Allows: qqx qqg ggx ggg   qqxx qqqq ggxx qqgx qqgg gggx gggg
            if (equal(color_number_sum,2) && (i==g || j==g || k==g)) continue;

            // skip FCNCs (can be enabled for non-Z2 2HDM)
            if (((equal(electric_charge[i],0) && i >= a) || (equal(electric_charge[j],0) && j >= a) || (equal(electric_charge[k],0) && k >= a) || (equal(electric_charge[l],0) && l >= a)) && 
                (!equal(e1_number_sum,0) || !equal(e2_number_sum,0) || !equal(e3_number_sum,0) || !equal(u1_number_sum,0) || !equal(u2_number_sum,0) || !equal(u3_number_sum,0)))
              continue;

            // skip non-BSM interactions for now
            if (i < hh && j < hh && k < hh && l < hh) continue;


            // skip couplings that would come out zero (but still picked up by functions below)

            if (((i==a && j==a) || (i==a && j==z)) && in(k,hh,ha) && in(l,hh,ha))
              continue;

            if (i==wp && j==wm && k==hx && l==ha)
              continue;

            if ((i==hx && j==ha && k==hp && l==hm) || (i==hx && j==ha && k==ha && l==ha) 
             || (i==hx && j==hx && k==hx && l==ha) || (i==hh && j==hh && k==hx && l==ha))
              continue;
            
            // store results here
            complexd scalar = 0, pseudo = 0;

            // call appropriate thdmc wrapper

            if (in(l,hh,hm) && in(k,hh,hm) && in(j,a,wm) && in(i,a,wm))
              container.obj.get_coupling_vvhh(to_thdmc(i),to_thdmc(j),to_thdmc(k),to_thdmc(l),scalar);
            else if (in(l,hh,hm) && in(k,hh,hm) && in(j,hh,hm) && in(i,hh,hm))
              container.obj.get_coupling_hhhh(to_thdmc(i),to_thdmc(j),to_thdmc(k),to_thdmc(l),scalar);
            else
            {
              // std::cout << "unable to get coupling: ";
              // print_coupling({{i,j,k,l},{scalar,pseudo}});
              continue;
            }

            result.push_back({{i,j,k,l},{scalar,pseudo}});
            }
          }
        }
      }

      // add th SM couplings 
      get_coupling_table_SM(result);


      // auto get_coupling = [&](coupling_table& t, std::vector<int> c)
      // {
      //   for (auto& i : t)
      //   {
      //     if (i.first == c) return i;
      //   }
      //   throw "invalid";
      // };

      // std::cout << "\n\nwp wm hx" << std::endl;
      // print_coupling(get_coupling(result,{wp,wm,hx,hx}));
      // std::cout << "B wp wm hx" << std::endl;
      // double lam3 = fullspectrum.get(Par::dimensionless, "lambda3");
      // double lam4 = fullspectrum.get(Par::dimensionless, "lambda4");
      // double lam5 = fullspectrum.get(Par::dimensionless, "lambda5");
      // std::cout << lam3+lam4+lam5+2*(sqr(masses[hp])-sqr(masses[hx]))/sqr(246.) << std::endl;

      // std::cout << "z z hx" << std::endl;
      // print_coupling(get_coupling(result,{z,z,hx,hx}));
      // std::cout << "B z z hx" << std::endl;
      // std::cout << lam3+lam4+lam5 << std::endl;


    }

  }

}
