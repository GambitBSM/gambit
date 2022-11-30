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

// GSL headers
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_deriv.h>

// Eigen headers
#include <Eigen/Eigenvalues>

// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/src/spectrum_generator_settings.hpp"
#include "flexiblesusy/models/THDM_I/THDM_I_input_parameters.hpp"
#include "flexiblesusy/models/THDM_II/THDM_II_input_parameters.hpp"
#include "flexiblesusy/models/THDM_LS/THDM_LS_input_parameters.hpp"
#include "flexiblesusy/models/THDM_flipped/THDM_flipped_input_parameters.hpp"

// GAMBIT headers
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Utils/stream_overloads.hpp" // Just for more convenient output to logger
#include "gambit/Utils/util_macros.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/Models/SimpleSpectra/THDMSimpleSpec.hpp"
#include "gambit/SpecBit/THDMSpec.hpp"
#include "gambit/SpecBit/THDMSpec_basis.hpp"
#include "gambit/SpecBit/model_files_and_boxes.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/Utils/slhaea_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/point_counter.hpp"

// #define SPECBIT_DEBUG // turn on debug mode

#define L_MAX 1e50 // used to invalidate likelihood
namespace Gambit
{
  namespace SpecBit
  {
    // extra namespace declarations
    using namespace LogTags;
    using namespace flexiblesusy;
    using std::vector;
    using std::complex;

    // additional type definitions
    enum scalar_type
    {
      h0 = 1,
      H0,
      A0,
      G0,
      Hp,
      Hm,
      Gp,
      Gm
    };

    struct physical_basis_input
    {
      double mh, mH, mC, mA, mG, mGC, beta, lambda6, lambda7, m122, alpha;
    };


    /// =========================
    /// == spectrum generation ==
    /// =========================

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

      // Do the W mass separately.  Here we use 10 MeV based on the size of corrections from two-loop papers and advice from Dominik Stockinger.
      // double rd_mW = 0.01 / thdmspec.get(Par::Pole_Mass, "W+");
      // thdmspec.set_override(Par::Pole_Mass_1srd_high, rd_mW, "W+", true);
      // thdmspec.set_override(Par::Pole_Mass_1srd_low,  rd_mW, "W+", true);

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

    // Get Spectrum for the THDM (either a FlexibleSUSY or tree-level spectrum depending on model)
    void get_THDM_spectrum(Spectrum &result)
    {
      using namespace Pipes::get_THDM_spectrum;
      const SMInputs& sminputs = *Dep::SMINPUTS;

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
        std::map<std::string, double> basis = create_empty_THDM_basis();

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
        const double alpha = basis["alpha"];
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
        const double alpha_em = 1.0 / sminputs.alphainv, C_calc = alpha_em * pi / (sminputs.GF * pow(2, 0.5));
        const double sinW2 = 0.5 - pow(0.25 - C_calc / pow(sminputs.mZ, 2), 0.5), cosW2 = 0.5 + pow(0.25 - C_calc / pow(sminputs.mZ, 2), 0.5);
        const double e = pow(4 * pi * (alpha_em), 0.5), v2 = 1.0 / (sqrt(2.0) * sminputs.GF), vev = sqrt(v2);

        // Standard model
        thdm_model.sinW2 = sinW2;
        thdm_model.vev = vev;
        // gauge couplings
        thdm_model.g1 = e / sinW2;
        thdm_model.g2 = e / cosW2;
        thdm_model.g3 = pow(4 * pi * (sminputs.alphaS), 0.5);
        //thdm_model.mW = sminputs.mZ * sqrt(cosW2);// this is a tree level approximation
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

        // // !!!!!! HACK YUKAWAS TO MATCH FS

        // thdm_model.Yu2[0][0] *= 0.620437956;
        // thdm_model.Yu2[1][1] *= 0.485436039;
        // thdm_model.Yu2[2][2] *= 0.978593122;
        // thdm_model.Yd1[0][0] *= 0.577532073;
        // thdm_model.Yd1[1][1] *= 0.618996779;
        // thdm_model.Yd1[2][2] *= 0.668142186;
        // thdm_model.Ye1[0][0] *= 0.976077011;
        // thdm_model.Ye1[1][1] *= 0.975944523;
        // thdm_model.Ye1[2][2] *= 0.975904405;

        // Create a SimpleSpec object to wrap the spectrum
        THDMSimpleSpec thdm_spec(thdm_model,sminputs);

        thdm_spec.set_override(Par::mass1, 0, "G0", true);
        thdm_spec.set_override(Par::mass1, 0, "G+", true);

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
          vector<std::string> lambda_keys = {"lambda1", "lambda2", "lambda3", "lambda4",
                                                  "lambda5", "lambda6", "lambda7"};
          for (auto const &each_lambda : lambda_keys)
          {
            if (*Param.at(each_lambda) > 4. * M_PI)
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

    // fill a map of THDM spectrum parameters to be printed
    void fill_map_from_THDMspectrum(std::map<std::string, double> &specmap, const Spectrum &thdmspec, const THDM_TYPE THDM_type)
    {
      using namespace Pipes::get_THDM_spectrum_as_map;
      bool print_minimal_yukawas = runOptions->getValueOrDef<bool>(false, "print_minimal_yukawas");
      bool print_Higgs_basis_params = runOptions->getValueOrDef<bool>(true, "print_Higgs_basis_params");
      bool print_running_masses = runOptions->getValueOrDef<bool>(true, "print_running_masses");

      /// Add everything... use spectrum contents routines to automate task
      static const SpectrumContents::THDM contents;
      static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters();

      for (std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin();
           it != required_parameters.end(); ++it)
      {
        const Par::Tags tag = it->tag();
        const std::string name = it->name();
        const std::vector<int> shape = it->shape();

        if (print_minimal_yukawas)
        {
          // skip Yukawas that are zero for the model being scanned
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
        specmap["M12_2 mass1"] = thdmspec.get_HE().get(Par::mass1, "M12_2");
        specmap["M11_2 mass1"] = thdmspec.get_HE().get(Par::mass1, "M11_2");
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
    }

    // get Spectrum as std::map so that it can be printed
    void get_THDM_spectrum_as_map(std::map<std::string, double> &specmap)
    {
      using namespace Pipes::get_THDM_spectrum_as_map;
      THDM_TYPE THDM_type = *Dep::THDM_Type;
      namespace myPipe = Pipes::get_THDM_spectrum_as_map;
      const Spectrum &thdmspec(*myPipe::Dep::THDM_spectrum);
      fill_map_from_THDMspectrum(specmap, thdmspec, THDM_type);
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
              if(yuk.find("yu") != std::string::npos)
                yu_empty = false;
              else if(yuk.find("yd") != std::string::npos)
                yd_empty = false;
              else if(yuk.find("yl") != std::string::npos)
                yl_empty = false;

              // if any imaginary element is non-zero, it is not real
              if(yuk.find("im") != std::string::npos)
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

    // helper function to ensure that the 2HDM scalar sector is Z2 symmetric
    void check_Z2(const double lambda6, const double lambda7, const std::string calculation_name)
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


    /// ========================================================================================
    /// == helper functions to unwrap parameters from the spectrum and help with calculations ==
    /// ========================================================================================


    namespace RunScale
    {
      constexpr double NONE = -1.0;
      constexpr double INPUT = -2.0;
    }

    // simple immutable structure for passing around 2HDM parameters at a fixed scale
    // with simple variable names so that you don't need to unwrap them
    // TODO: finish replacing all of Filip's structures with this
    struct ThdmSpec
    {
      enum ThdmSpecFill
      {
        FILL_GENERIC = 1<<0,
        FILL_HIGGS = 1<<1,
        FILL_PHYSICAL = 1<<2,
        FILL_ANGLES = 1<<3,
        // FILL_TYPE = 1<<4,
        // FILL_YUKAWAS = 1<<5,
      };

      ThdmSpec(const SubSpectrum& he, const int fill = 0xFFFF) :
        fill_mode((ThdmSpecFill)fill),
        lam1(get(he,"lambda1")), lam2(get(he,"lambda2")), lam3(get(he,"lambda3")), lam4(get(he,"lambda4")), lam5(get(he,"lambda5")), lam6(get(he,"lambda6")), lam7(get(he,"lambda7")),
        Lam1(get(he,"Lambda1")), Lam2(get(he,"Lambda2")), Lam3(get(he,"Lambda3")), Lam4(get(he,"Lambda4")), Lam5(get(he,"Lambda5")), Lam6(get(he,"Lambda6")), Lam7(get(he,"Lambda7")),
        mh(get(he,"h0_1")), mH(get(he,"h0_2")), mA(get(he,"A0")), mHp(get(he,"H+")), mG(get(he,"G0")), mGp(get(he,"G+")), v(get(he,"vev")), v2(get(he,"v2")), m122(get(he,"m12_2")), m112(get(he,"m11_2")), m222(get(he,"m22_2")),
        beta(get(he,"beta")), alpha(get(he,"alpha")), tanb(get(he,"tanb")), cosba(get(he,"cosba")), sinba(get(he,"sinba"))
      {}

      // what has been filled
      const ThdmSpecFill fill_mode;
      // Generic basis params
      const double lam1, lam2, lam3, lam4, lam5, lam6, lam7;
      // Higgs basis params
      const double Lam1, Lam2, Lam3, Lam4, Lam5, Lam6, Lam7;
      // Physical params
      const double mh, mH, mA, mHp, mG, mGp, v, v2, m122, m112, m222;
      // angles
      const double beta, alpha, tanb, cosba, sinba;

    private:

      using ccstring = const char* const;

      double get(const SubSpectrum& he, ccstring name) const
      {
        const bool fill_generic  = (fill_mode & FILL_GENERIC) != 0;
        const bool fill_higgs    = (fill_mode & FILL_HIGGS) != 0;
        const bool fill_physical = (fill_mode & FILL_PHYSICAL) != 0;
        const bool fill_angles   = (fill_mode & FILL_ANGLES) != 0;

        ccstring generic[]  = {"lambda1", "lambda2", "lambda3", "lambda4", "lambda5", "lambda6", "lambda7"};
        ccstring higgs[]    = {"Lambda1", "Lambda2", "Lambda3", "Lambda4", "Lambda5", "Lambda6", "Lambda7"};
        ccstring physical[] = {"h0_1", "h0_2", "A0", "H+", "G0", "G+", "vev", "m12_2", "m11_2", "m22_2"};
        ccstring angles[]   = {"beta", "alpha", "tanb"};

        if (fill_generic)
          for (auto& n : generic)
            if (strcmp(name,n) == 0)
              return he.get(Par::dimensionless, name);

        if (fill_higgs)
          for (auto& n : higgs)
            if (strcmp(name,n) == 0)
              return he.get(Par::dimensionless, name);

        if (fill_physical)
        {
          for (auto& n : physical)
            if (strcmp(name,n) == 0)
              return he.get(Par::mass1, name);

          if (strcmp(name,"v2") == 0) return v*v;
        }

        if (fill_angles)
        {
          for (auto& n : angles)
            if (strcmp(name,n) == 0)
              return he.get(Par::dimensionless, name);

          if (strcmp(name,"cosba") == 0) return cos(beta-alpha);
          if (strcmp(name,"sinba") == 0) return sin(beta-alpha);
        }

        return std::numeric_limits<double>::quiet_NaN();
      }

    };

    using q_matrix = vector<vector<complex<double>>>;

    // fills a template struct that includes physical basis parameters form the spectrum conatainer
    template <class T>
    void fill_physical_basis(T &input, ThdmSpec &s)
    {
      input.mh = s.mh;
      input.mH = s.mH;
      input.mA = s.mA;
      input.mC = s.mHp;
      input.mG = s.mG;
      input.mGC = s.mGp;
      input.alpha = s.alpha;
      input.beta = s.beta;
      input.m122 = s.m122;
    }

    // helper function to fill from physical basis
    physical_basis_input fill_physical_basis_input(ThdmSpec &s)
    {
      physical_basis_input input;
      fill_physical_basis(input, s);
      return input;
    }

    // fills a vector with lambas from the spectrum object
    vector<double> get_lambdas_from_spectrum(ThdmSpec &s)
    {
      vector<double> lambda(8);
      lambda[1] = s.lam1;
      lambda[2] = s.lam2;
      lambda[3] = s.lam3;
      lambda[4] = s.lam4;
      lambda[5] = s.lam5;
      lambda[6] = s.lam6;
      lambda[7] = s.lam7;
      return lambda;
    }

    // returns the symmetry factor for a set of particels
    int get_symmetry_factor(vector<int> n_identical_particles)
    {
      int symm_factor = 1;
      for (const auto &n_identical : n_identical_particles)
      {
        symm_factor *= Utils::factorial(n_identical);
      }
      return symm_factor;
    }

    // returns Class I q_ij matrix based upon Higgs basis
    q_matrix get_qij(const double ba, const double Lam6)
    {
      const double sba = sin(ba), cba = abs(cos(ba));
      const complex<double> i(0.0, 1.0);
      q_matrix q = {{0.0, 0.0, 0.0}, {0.0, sba, (double)sgn(Lam6) * cba}, {0.0, -(double)sgn(Lam6) * cba, sba}, {0.0, 0.0, i}, {0.0, i, 0.0}};
      return q;
    }

    // is a particle neutral?
    bool is_neutral(int p1)
    {
      if (p1 == h0 || p1 == H0 || p1 == A0 || p1 == G0)
        return true;
      return false;
    }

    // is a particle a goldstone boson?
    bool is_goldstone(int p1)
    {
      if (p1 == G0 || p1 == Gp || p1 == Gm)
        return true;
      return false;
    }

    // returns all partical permutations for a set of neutral particles
    // includes the symmetry factor for number of times particles are outputed
    // expects particle input to be ordered
    vector<vector<scalar_type>> get_neutral_particle_permutations(vector<scalar_type> particles)
    {
      int neutral_index = 0, neutral_index_identical = 0, identical_counter = 0;
      vector<vector<scalar_type>> particle_permutations;
      // check if particle 0 is neutral
      if (!is_neutral(particles[0]))
        return {particles};
      // cycle through particles to find index of last neutral particle that is not a Goldstone boson
      while (is_neutral(particles[neutral_index]) && !is_goldstone(particles[neutral_index]) && neutral_index < (signed)(particles.size()))
      {
        neutral_index++;
      }
      neutral_index--; // fix to machine index
      // count identical neutral particles in the particles vector
      // retuurns vector with number of identical particles in order
      // starts at the first index of the particle array
      vector<int> identical_particles;
      while (neutral_index_identical < (signed)particles.size())
      {
        identical_counter = 1;
        if (particles[neutral_index_identical] != particles[neutral_index_identical + 1])
        {
          // the particle to the right is different
          identical_particles.push_back(identical_counter);
          neutral_index_identical++;
        }
        else
        {
          // the particle to the right is identical
          // keep searching right until a different particle is found
          while (neutral_index_identical < (signed)particles.size() - 1 && particles[neutral_index_identical] == particles[neutral_index_identical + 1])
          {
            neutral_index_identical++;
            identical_counter++;
          }
          neutral_index_identical++;
          identical_particles.push_back(identical_counter);
        }
      }

      const int symmetry_factor = get_symmetry_factor(identical_particles);
      // start permutating the neutral particles that are not Goldstone particles
      do
      {
        // append permutation *symmetry factor* number of times
        for (int j = 0; j < symmetry_factor; j++)
          particle_permutations.push_back(particles);
      } while (std::next_permutation(particles.begin(), particles.begin() + neutral_index + 1));

      return particle_permutations;
    }

    // helper function for == between particles
    bool particles_match(vector<scalar_type> particles, vector<scalar_type> test_particles)
    {
      return particles == test_particles;
    }


    /// =================================================================================
    /// == Higgs couplings calculated using the Higgs basis (ref arXiv:hep-ph/0602242) ==
    /// =================================================================================


    // hhh coupling using Higgs basis
    complex<double> get_cubic_coupling_higgs_hhh(ThdmSpec &s, const q_matrix &q, vector<scalar_type> particles)
    {
      const scalar_type j = particles[0], k = particles[1], l = particles[2];

      const double Lam1 = s.Lam1, Lam34 = s.Lam3 + s.Lam4;
      const double Lam5 = s.Lam5, Lam6 = s.Lam6, Lam7 = s.Lam7;
      complex<double> c(0.0, 0.0);

      c += q[j][1] * std::conj(q[k][1]) * (q[l][1]).real() * Lam1;
      c += q[j][2] * std::conj(q[k][2]) * (q[l][1]).real() * Lam34;
      c += (std::conj(q[j][1]) * q[k][2] * q[l][2] * Lam5).real();
      c += ((2.0 * q[j][1] + std::conj(q[j][1])) * std::conj(q[k][1]) * q[l][2] * Lam6 * (double)sgn(Lam6)).real();
      c += (std::conj(q[j][2]) * q[k][2] * q[l][2] * Lam7 * (double)sgn(Lam6)).real();
      c *= 0.5 * s.v;
      return c;
    }

    // hH+H- coupling
    complex<double> get_cubic_coupling_higgs_hHpHm(ThdmSpec &s, const q_matrix &q, scalar_type k)
    {
      return s.v * ((q[k][1]).real() * s.Lam3 + (q[k][2] * (double)sgn(s.Lam6) * s.Lam7).real());
    }

    // hG+G- coupling
    complex<double> get_cubic_coupling_higgs_hGpGm(ThdmSpec &s, const q_matrix &q, scalar_type k)
    {
      double Lambda6 = s.Lam6;
      return s.v * ((q[k][1]).real() * s.Lam1 + (q[k][2] * (double)sgn(Lambda6) * Lambda6).real());
    }

    // hG-H+ coupling
    complex<double> get_cubic_coupling_higgs_hGmHp(ThdmSpec &s, const q_matrix &q, scalar_type k)
    {
      double Lambda6 = s.Lam6;
      return s.v * 0.5 * (double)sgn(Lambda6) * (std::conj(q[k][2]) * s.Lam4 + q[k][2] * s.Lam5 + 2.0 * (q[k][1]).real() * Lambda6 * (double)sgn(Lambda6));
    }

    // hhG0 coupling
    complex<double> get_cubic_coupling_higgs_hhG0(ThdmSpec &s, const q_matrix &q, vector<scalar_type> particles)
    {
      const scalar_type k = particles[0], l = particles[1];
      double Lambda6 = s.Lam6;
      return s.v * 0.5 * ((q[k][2] * q[l][2] * s.Lam5).imag() + 2.0 * q[k][1] * (q[l][2] * Lambda6 * (double)sgn(Lambda6)).imag());
    }

    // hG0G0 coupling
    complex<double> get_cubic_coupling_higgs_hG0G0(ThdmSpec &s, const q_matrix &q, scalar_type k)
    {
      double Lambda6 = s.Lam6;
      return 0.5 * s.v * (q[k][1] * s.Lam1 + (q[k][2] * Lambda6 * (double)sgn(Lambda6)).real());
    }

    // hhhh coupling
    complex<double> get_quartic_coupling_higgs_hhhh(ThdmSpec &s, const q_matrix &q, vector<scalar_type> particles)
    {
      const scalar_type j = particles[0], k = particles[1], l = particles[2], m = particles[3];
      const double Lam1 = s.Lam1, Lam2 = s.Lam2, Lam34 = s.Lam3 + s.Lam4;
      const double Lam5 = s.Lam5, Lam6 = s.Lam6, Lam7 = s.Lam7;
      complex<double> c(0.0, 0.0);

      c += q[j][1] * q[k][1] * std::conj(q[l][1]) * std::conj(q[m][1]) * Lam1;
      c += q[j][2] * q[k][2] * std::conj(q[l][2]) * std::conj(q[m][2]) * Lam2;
      c += 2.0 * q[j][1] * std::conj(q[k][1]) * q[l][2] * std::conj(q[m][2]) * Lam34;
      c += 2.0 * (std::conj(q[j][1]) * std::conj(q[k][1]) * q[l][2] * q[m][2] * Lam5).real();
      c += 4.0 * (q[j][1] * std::conj(q[k][1]) * std::conj(q[l][1]) * q[m][2] * Lam6 * (double)sgn(Lam6)).real();
      // TODO: I feel this should be sgn(Lam7), where do these equations come from?
      c += 4.0 * (std::conj(q[j][1]) * q[k][2] * q[l][2] * std::conj(q[m][2]) * Lam7 * (double)sgn(Lam6)).real();
      return 0.125 * c;
    }

    // hhG+G- coupling
    complex<double> get_quartic_coupling_higgs_hhGpGm(ThdmSpec &s, const q_matrix &q, vector<scalar_type> particles)
    {
      const scalar_type j = particles[0], k = particles[1];
      const double Lambda6 = s.Lam6;
      return 0.5 * (q[j][1] * std::conj(q[k][1]) * s.Lam1 + q[j][2] * std::conj(q[k][2]) * s.Lam3 + 2.0 * (q[j][1] * q[k][2] * Lambda6 * (double)sgn(Lambda6)).real());
    }

    // hhH+H- coupling
    complex<double> get_quartic_coupling_higgs_hhHpHm(ThdmSpec &s, const q_matrix &q, vector<scalar_type> particles)
    {
      const scalar_type j = particles[0], k = particles[1];
      return 0.5 * (q[j][2] * std::conj(q[k][2]) * s.Lam2 + q[j][1] * std::conj(q[k][1]) * s.Lam3 + 2.0 * (q[j][1] * q[k][2] * s.Lam7 * (double)sgn(s.Lam6)).real());
    }

    // hhG+H- coupling
    complex<double> get_quartic_coupling_higgs_hhGmHp(ThdmSpec &s, const q_matrix &q, vector<scalar_type> particles)
    {
      const scalar_type j = particles[0], k = particles[1];
      const double Lam4 = s.Lam4, Lam5 = s.Lam5, Lam6 = s.Lam6, Lam7 = s.Lam7;
      complex<double> c(0.0, 0.0);
      c += (double)sgn(Lam6) * q[j][1] * std::conj(q[k][2]) * Lam4;
      c += std::conj(q[j][1]) * q[k][2] * Lam5;
      c += q[j][1] * std::conj(q[k][1]) * Lam6 * (double)sgn(Lam6);
      c += q[j][2] * std::conj(q[k][2]) * Lam7 * (double)sgn(Lam6);
      return 0.5 * c;
    }

    // hG0G0G0 coupling
    complex<double> get_quartic_coupling_higgs_hG0G0G0(ThdmSpec &s, const q_matrix &q, scalar_type m)
    {
      const double Lam6 = s.Lam6;
      return 0.5 * (q[m][2] * Lam6 * (double)sgn(Lam6)).imag();
    }

    // hhG0G0 coupling
    complex<double> get_quartic_coupling_higgs_hhG0G0(ThdmSpec &s, const q_matrix &q, vector<scalar_type> particles)
    {
      const scalar_type l = particles[0], m = particles[1];
      const double Lam6 = s.Lam6;
      complex<double> c(0.0, 0.0);
      c = (q[l][1] * q[m][1] * s.Lam1 + q[l][2] * std::conj(q[m][2]) * (s.Lam3 + s.Lam4));
      c += -(q[l][2] * q[m][2] * s.Lam5).real() + 2.0 * q[l][1] * (q[m][2] * Lam6 * (double)sgn(Lam6)).real();
      return 0.25 * c;
    }

    // hhhG0 coupling
    complex<double> get_quartic_coupling_higgs_hhhG0(ThdmSpec &s, const q_matrix &q, vector<scalar_type> particles)
    {
      const scalar_type k = particles[1], l = particles[1], m = particles[2];
      const double Lam6 = s.Lam6;
      complex<double> c(0.0, 0.0);
      c = q[k][1] * (q[l][2] * q[m][2] * s.Lam5).real() + q[k][1] * q[l][1] * (q[m][2] * Lam6 * (double)sgn(Lam6)).real();
      c += (q[k][2] * q[l][2] * std::conj(q[m][2]) * s.Lam7 * (double)sgn(Lam6)).real();
      return 0.5 * c;
    }


    /// ===========================================================
    /// === Higgs couplings calculated using the physical basis ===
    /// ===========================================================


    // h0G+G- coupling using physical basis
    complex<double> get_cubic_coupling_physical_h0GpGm(ThdmSpec &s)
    {
      const double mh = s.mh;
      const double mh2 = pow(mh, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double v = s.v;
      return 1.0 / v * (-1.0 * mh2 * sba);
    }

    // H0G+G- coupling using physical basiss
    complex<double> get_cubic_coupling_physical_H0GpGm(ThdmSpec &s)
    {
      const double mH = s.mH;
      const double mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = (cos(b - a));
      const double v = s.v;
      return 1.0 / v * (-1.0 * mH2 * cba);
    }

    // h0G+H- coupling using physical basis
    complex<double> get_cubic_coupling_physical_h0GpHm(ThdmSpec &s)
    {
      const double mh = s.mh, mC = s.mHp;
      const double mh2 = pow(mh, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = (cos(b - a));
      const double v = s.v;
      return 1.0 / v * (-1.0 * (mh2 - mC2) * cba);
    }

    // h0G0A0 coupling using physical basis
    complex<double> get_cubic_coupling_physical_h0G0A0(ThdmSpec &s)
    {
      const double mh = s.mh, mA = s.mA;
      const double mh2 = pow(mh, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = (cos(b - a));
      const double v = s.v;
      return 1.0 / v * (-1.0 * (mh2 - mA2) * cba);
    }

    // H0G+H- coupling using physical basis
    complex<double> get_cubic_coupling_physical_H0GpHm(ThdmSpec &s)
    {
      const double mH = s.mH, mC = s.mHp;
      const double mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double v = s.v;
      return 1.0 / v * (1.0 * (mH2 - mC2) * sba);
    }

    // H0G0A0 coupling using physical basis
    complex<double> get_cubic_coupling_physical_H0G0A0(ThdmSpec &s)
    {
      const double mH = s.mH, mA = s.mA;
      const double mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double v = s.v;
      return 1.0 / v * (1.0 * (mH2 - mA2) * sba);
    }

    // A0G+H- coupling using physical basis
    complex<double> get_cubic_coupling_physical_A0GpHm(ThdmSpec &s)
    {
      const complex<double> i(0.0, 1.0);
      const double mA = s.mA, mC = s.mHp;
      const double mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const double v = s.v;
      return 1.0 / v * (-1.0 * i * (mA2 - mC2));
    }

    // h0H+H- coupling using physical basis
    complex<double> get_cubic_coupling_physical_h0HpHm(ThdmSpec &s)
    {
      const double mh = s.mh, mC = s.mHp, m122 = s.m122;
      const double mh2 = pow(mh, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), cbap = cos(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = s.v;
      return 1.0 / v * (sbinv * cbinv * (m122 * cbap * sbinv * cbinv - mh2 * c2b * cba) - (mh2 + 2.0 * mC2) * sba);
    }

    // h0A0A0 coupling using physical basis
    complex<double> get_cubic_coupling_physical_h0A0A0(ThdmSpec &s)
    {
      const double mh = s.mh, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), cbap = cos(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = s.v;
      return 1.0 / v * (sbinv * cbinv * (m122 * cbap * sbinv * cbinv - mh2 * c2b * cba) - (mh2 + 2.0 * mA2) * sba);
    }

    // H0H+H- coupling using physical basis
    complex<double> get_cubic_coupling_physical_H0HpHm(ThdmSpec &s)
    {
      const double mH = s.mH, mC = s.mHp, m122 = s.m122;
      const double mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), sbap = sin(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = s.v;
      return 1.0 / v * (sbinv * cbinv * (m122 * sbap * sbinv * cbinv + mH2 * c2b * sba) - (mH2 + 2.0 * mC2) * cba);
    }

    // H0A0A0 coupling using physical basis
    complex<double> get_cubic_coupling_physical_H0A0A0(ThdmSpec &s)
    {
      const double mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), sbap = sin(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = s.v;
      return 1.0 / v * (sbinv * cbinv * (m122 * sbap * sbinv * cbinv + mH2 * c2b * sba) - (mH2 + 2.0 * mA2) * cba);
    }

    // h0h0h0 coupling using physical basis
    complex<double> get_cubic_coupling_physical_h0h0h0(ThdmSpec &s)
    {
      const double mh = s.mh, m122 = s.m122;
      const double mh2 = pow(mh, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), cbap = cos(b + a);
      const double cba2 = pow(cba, 2);
      const double s2b = sin(2.0 * b);
      const double v = s.v;
      return 3.0 / (4.0 * v * s2b * s2b) * (16.0 * m122 * cbap * cba2 - mh2 * (3.0 * sin(3.0 * b + a) + 3.0 * sba + sin(3.0 * b - 3.0 * a) + sin(b + 3.0 * a)));
    }

    // h0h0H0 coupling using physical basis
    complex<double> get_cubic_coupling_physical_h0h0H0(ThdmSpec &s)
    {
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = (cos(b - a));
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v = s.v;
      return -cba / (s2b * v) * (2.0 * m122 + (mH2 + 2.0 * mh2 - 3.0 * m122 * sbinv * cbinv) * s2a);
    }

    // h0H0H0 coupling using physical basis
    complex<double> get_cubic_coupling_physical_h0H0H0(ThdmSpec &s)
    {
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v = s.v;
      return sba / (s2b * v) * (-2.0 * m122 + (mh2 + 2.0 * mH2 - 3.0 * m122 * sbinv * cbinv) * s2a);
    }

    // H0H0H0 coupling using physical basis
    complex<double> get_cubic_coupling_physical_H0H0H0(ThdmSpec &s)
    {
      const double mH = s.mH, m122 = s.m122;
      const double mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), sbap = sin(b + a);
      const double sba2 = pow(sba, 2);
      const double s2b = sin(2.0 * b);
      const double v = s.v;
      return 3.0 / (4.0 * v * s2b * s2b) * (16.0 * m122 * sbap * sba2 + mH2 * (3.0 * cos(3.0 * b + a) - 3.0 * cba + cos(3.0 * b - 3.0 * a) - cos(b + 3.0 * a)));
    }

    // h0h0G0G0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_h0h0G0G0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double t2binv = 1.0 / (tan(2.0 * b));
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = -1.0 / v2 * (mH2 * pow(cba, 4) + 2.0 * (mh2 - mH2) * pow(cba, 3) * sba * t2binv + mh2 * pow(sba, 4));
      coupling += -1.0 / v2 * cba2 * (2.0 * mA2 - 2.0 * m122 * sbinv * cbinv + (3.0 * mh2 - mH2) * sba2);
      return coupling;
    }

    // h0h0G0G0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_HpHmG0G0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double t2binv = 1.0 / (tan(2.0 * b)), sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = -1.0 / v2 * (mH2 * pow(cba, 4) + 2.0 * (mh2 - mH2) * pow(sba, 3) * cba * t2binv + mh2 * pow(sba, 4));
      coupling += -1.0 / v2 * sba2 * (2.0 * mA2 - 2.0 * m122 * sbinv * cbinv + (3.0 * mH2 - mh2) * cba2);
      return coupling;
    }

    // A0A0G0G0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_A0A0G0G0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mC = s.mHp, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double t2binv = 1.0 / (tan(2.0 * b));
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / v2 * (2.0 * m122 * sbinv * cbinv - 2.0 * mC2 - mH2 * cba2 - mh2 * sba2 + (mH2 - mh2) * t2binv * s2b2a);
      return coupling;
    }

    // h0h0G0A0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_h0h0G0A0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double t2binv = 1.0 / (tan(2.0 * b)), sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / v2 * (2.0 * m122 * sbinv * cbinv - (mH2 + 2.0 * mh2) * cba2 - (mh2 + 2.0 * mH2) * sba2 + (mH2 - mh2) * t2binv * s2b2a);
      return coupling;
    }

    // H0H0G0A0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_H0H0G0A0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = cos(b - a);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a), s2a2b = sin(2.0 * a - 2.0 * b);
      const double c2b = cos(2.0 * b);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b) * (mH2 * s2b2a * s2a - mA2 * s2b * s2a2b + cba * (4.0 * m122 * cba * sbinv * cbinv * c2b - mh2 * (cos(-1.0 * b + 3.0 * a) + 3.0 * cos(b + a))));
      return coupling;
    }

    // HpHmG0A0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_HpHmG0A0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a), s2a2b = sin(2.0 * a - 2.0 * b);
      const double c2b = cos(2.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b) * (mh2 * s2b2a * s2a + mA2 * s2b * s2a2b + sba * (4.0 * m122 * sba * sbinv * cbinv * c2b - mH2 * (sin(-1.0 * b + 3.0 * a) - 3.0 * sin(b + a))));
      return coupling;
    }

    // A0A0G0A0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_A0A0G0A0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double s2b = sin(2.0 * b);
      const double c2b = cos(2.0 * b), c2a = cos(2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b * s2b) * (32 * m122 * c2b + 2.0 * (mH2 - mh2) * (3.0 * c2a + cos(4.0 * b - 2.0 * a)) * s2b - 4.0 * (mh2 + mH2) * sin(4.0 * b));
      return coupling;
    }

    // h0h0HpHm coupling using physical basis
    complex<double> get_quartic_coupling_physical_h0h0HpHm(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mC = s.mHp, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sab = sin(a - b), sab2 = pow(sab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 + c2a2b + c4b) + 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a + 6.0 * c2a2b + c4a4b + 3.0 * c4b + 10.0 * c2a2bp) * mh2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) + 2.0 * s2b) * mH2 + 32.0 * sab2 * s2b * mC2);
      return coupling;
    }

    // h0h0A0A0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_h0h0A0A0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sab = sin(a - b), sab2 = pow(sab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 + c2a2b + c4b) + 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a + 6.0 * c2a2b + c4a4b + 3.0 * c4b + 10.0 * c2a2bp) * mh2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) + 2.0 * s2b) * mH2 + 32.0 * sab2 * s2b * mA2);
      return coupling;
    }

    // H0H0HpHm coupling using physical basis
    complex<double> get_quartic_coupling_physical_H0H0HpHm(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mC = s.mHp, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double cab = cos(a - b), cab2 = pow(cab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (-cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 - c2a2b + c4b) - 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a - 6.0 * c2a2b + c4a4b + 3.0 * c4b - 10.0 * c2a2bp) * mH2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) - 2.0 * s2b) * mh2 + 32.0 * cab2 * s2b * mC2);
      return coupling;
    }

    // H0H0A0A0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_H0H0A0A0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double cab = cos(a - b), cab2 = pow(cab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (-cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 - c2a2b + c4b) - 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a - 6.0 * c2a2b + c4a4b + 3.0 * c4b - 10.0 * c2a2bp) * mH2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) - 2.0 * s2b) * mh2 + 32.0 * cab2 * s2b * mA2);
      return coupling;
    }

    // h0H0HpHm coupling using physical basis
    complex<double> get_quartic_coupling_physical_h0H0HpHm(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mC = s.mHp, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = cos(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s4b = sin(4.0 * b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double s3b3a = sin(3.0 * b - 3.0 * a);
      const double c4b = cos(4.0 * b);
      const double c2b2a = cos(2.0 * b - 2.0 * a);
      const double c3b3a = cos(3.0 * b - 3.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b) * cba * sbinv * cbinv * (3.0 * sba + s3b3a - 3.0 * sin(b + 3.0 * a) - sin(3.0 * b + a)) * mh2;
      coupling += 1.0 / (8.0 * v2 * s2b) * sba * sbinv * cbinv * (3.0 * cba - c3b3a - 3.0 * cos(b + 3.0 * a) + cos(3.0 * b + a)) * mH2;
      coupling += -1.0 / (8.0 * v2 * s2b) * (8.0 * s2b2a * s2b * mC2 + 4.0 * pow(1.0 / s2b, 2) * (2.0 * (1.0 + 3.0 * c4b) * s2b2a - 4.0 * c2b2a * s4b) * m122);
      return coupling;
    }

    // h0H0A0A0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_h0H0A0A0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double cba = cos(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s4b = sin(4.0 * b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double s3b3a = sin(3.0 * b - 3.0 * a);
      const double c4b = cos(4.0 * b);
      const double c2b2a = cos(2.0 * b - 2.0 * a);
      const double c3b3a = cos(3.0 * b - 3.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b) * cba * sbinv * cbinv * (3.0 * sba + s3b3a - 3.0 * sin(b + 3.0 * a) - sin(3.0 * b + a)) * mh2;
      coupling += 1.0 / (8.0 * v2 * s2b) * sba * sbinv * cbinv * (3.0 * cba - c3b3a - 3.0 * cos(b + 3.0 * a) + cos(3.0 * b + a)) * mH2;
      coupling += -1.0 / (8.0 * v2 * s2b) * (8.0 * s2b2a * s2b * mA2 + 4.0 * pow(1.0 / s2b, 2) * (2.0 * (1.0 + 3.0 * c4b) * s2b2a - 4.0 * c2b2a * s4b) * m122);
      return coupling;
    }

    // h0h0h0h0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_h0h0h0h0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = cos(b - a), cbap = cos(b + a), cba2 = pow(cba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 3.0 / (4.0 * v2 * s2b * s2b) * 4.0 * cba2 * (4.0 * m122 * sbinv * cbinv * pow(cbap, 2) - mH2 * pow(s2a, 2));
      coupling += -3.0 / (4.0 * v2 * s2b * s2b) * mh2 * pow((cos(-b + 3.0 * a) + 3.0 * cbap), 2);
      return coupling;
    }

    // h0h0h0H0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_h0h0h0H0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double cba = cos(b - a), cbap = cos(b + a);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b * s2b) * 3.0 * s2a * (mH2 * s2a * s2b2a - mh2 * cba * (cos(-b + 3.0 * a) + 3.0 * cbap));
      coupling += 1.0 / (2.0 * v2 * s2b * s2b) * 12.0 * m122 * (1.0 / s2b) * cba * (sin(b + 3.0 * a) - sba);
      return coupling;
    }

    // h0h0H0H0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_h0h0H0H0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2b2a = cos(2.0 * b - 2.0 * a), c2b2ap = cos(2.0 * b + 2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b * s2b) * (4.0 * sbinv * cbinv * (2.0 + c4b - 3.0 * c4a) * m122 + 6.0 * (c4a - 1.0) * (mh2 + mH2));
      coupling += 1.0 / (8.0 * v2 * s2b * s2b) * (3.0 * cos(-2.0 * b + 6.0 * a) - c2b2ap - 2.0 * c2b2a) * (mh2 - mH2);
      return coupling;
    }

    // h0H0H0H0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_h0H0H0H0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sbap = sin(b + a);
      const double cba = cos(b - a);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b * s2b) * 3.0 * s2a * (mh2 * s2a * s2b2a - mH2 * sba * (sin(-b + 3.0 * a) - 3.0 * sbap));
      coupling += 1.0 / (2.0 * v2 * s2b * s2b) * 12.0 * m122 * (1.0 / s2b) * sba * (cos(b + 3.0 * a) - cba);
      return coupling;
    }

    // H0H0H0H0 coupling using physical basis
    complex<double> get_quartic_coupling_physical_H0H0H0H0(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sbap = sin(b + a), sba2 = pow(sba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 3.0 / (4.0 * v2 * s2b * s2b) * 4.0 * sba2 * (4.0 * m122 * sbinv * cbinv * pow(sbap, 2) - mh2 * pow(s2a, 2));
      coupling += -3.0 / (4.0 * v2 * s2b * s2b) * mH2 * pow((sin(-b + 3.0 * a) - 3.0 * sbap), 2);
      return coupling;
    }

    // HpHmHpHm coupling using physical basis
    complex<double> get_quartic_coupling_physical_HpHmHpHm(ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double t2binv = 1.0 / (tan(2.0 * b)), sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double c2b = cos(2.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complex<double> coupling = 0.0;
      coupling = 2.0 / v2 * ((mH2 - mh2) * c2b * sbinv * cbinv * s2b2a - mh2 * sba2);
      coupling += -2.0 / v2 * (cba2 * (mH2 + 4.0 * mh2 * pow(t2binv, 2)) + 4.0 * pow(t2binv, 2) * (mH2 * sba2 - m122 * sbinv * cbinv));
      return coupling;
    }


    ///  ===========================================================
    ///  == helper functions to get couplings in more generic way ==
    ///  ===========================================================


    // main function to get cubic higgs coupling
    complex<double> get_cubic_coupling_higgs(ThdmSpec &s, scalar_type p1, scalar_type p2, scalar_type p3)
    {
      complex<double> c(0.0, 0.0);
      const complex<double> i(0.0, 1.0);
      const double ba = s.beta - s.alpha;
      const double Lam6 = s.Lam6;
      const q_matrix q = get_qij(ba, Lam6);

      vector<scalar_type> particles = {p1, p2, p3};
      std::sort(particles.begin(), particles.end()); // order particles
      p1 = particles[0];
      p2 = particles[1];
      p3 = particles[2];

      // Get a sign factor based on particles involved in the coupling
      // - based up Class I
      int sign = 1;
      for (auto const &each_part : particles)
      {
        if (each_part == H0)
          sign *= -(double)sgn(Lam6);
        else if (each_part == A0)
          sign *= (double)sgn(Lam6);
      }

      // Get coupling
      if (is_neutral(p1) && is_neutral(p2) && is_neutral(p3))
      {
        for (auto const &particles_perm : get_neutral_particle_permutations(particles))
        {
          if (particles_match(particles, {p1, G0, G0}))
            c += get_cubic_coupling_higgs_hG0G0(s, q, p1);
          else if (particles_match(particles, {p1, p2, G0}))
            c += get_cubic_coupling_higgs_hhG0(s, q, particles_perm);
          else
            c += get_cubic_coupling_higgs_hhh(s, q, particles_perm);
        }
      }
      else if (is_neutral(p1) && !is_neutral(p2) && !is_neutral(p3))
      {
        if (particles_match(particles, {p1, Hp, Hm}))
          c += get_cubic_coupling_higgs_hHpHm(s, q, p1);
        else if (particles_match(particles, {p1, Gp, Gm}))
          c += get_cubic_coupling_higgs_hGpGm(s, q, p1);
        else if (particles_match(particles, {p1, Hp, Gm}))
          c += get_cubic_coupling_higgs_hGmHp(s, q, p1);
        else if (particles_match(particles, {p1, Hm, Gp}))
          c += std::conj(get_cubic_coupling_higgs_hGmHp(s, q, p1));
      }

      return -i * c * (double)sign;
    }

    // main function to get quartic higgs couplings
    complex<double> get_quartic_coupling_higgs(ThdmSpec &s, scalar_type p1, scalar_type p2, scalar_type p3, scalar_type p4)
    {
      complex<double> c(0.0, 0.0);
      const complex<double> i(0.0, 1.0);
      const double ba = s.beta - s.alpha;
      const double Lam1 = s.Lam4, Lam2 = s.Lam2, Lam3 = s.Lam3;
      const double Lam4 = s.Lam4, Lam5 = s.Lam5, Lam6 = s.Lam6, Lam7 = s.Lam7;
      const q_matrix q = get_qij(ba, Lam6);

      vector<scalar_type> particles = {p1, p2, p3, p4};
      std::sort(particles.begin(), particles.end()); // order particles
      p1 = particles[0];
      p2 = particles[1];
      p3 = particles[2];
      p4 = particles[3];

      // Get a sign factor based on particles involved in the coupling
      // - based up Class I
      int sign = 1;
      for (auto const &each_part : particles)
      {
        if (each_part == H0)
          sign *= -(double)sgn(Lam6);
        else if (each_part == A0)
          sign *= (double)sgn(Lam6);
      }

      // Get coupling
      for (auto const &particles_perm : get_neutral_particle_permutations(particles))
      {
        if (is_neutral(p1) && is_neutral(p2) && is_neutral(p3) && is_neutral(p4))
        {
          if (particles_match(particles, {p1, G0, G0, G0}))
            c += get_quartic_coupling_higgs_hG0G0G0(s, q, p1);
          else if (particles_match(particles, {p1, p2, G0, G0}))
            c += get_quartic_coupling_higgs_hhG0G0(s, q, particles_perm);
          else if (particles_match(particles, {p1, p2, p3, G0}))
            c += get_quartic_coupling_higgs_hhhG0(s, q, particles_perm);
          else
            c += get_quartic_coupling_higgs_hhhh(s, q, particles_perm);
        }
        else if (is_neutral(p1) && is_neutral(p2) && !is_neutral(p3) && !is_neutral(p4))
        {
          if (particles_match(particles, {G0, G0, Hp, Hm}))
            c += 0.5 * Lam3;
          else if (particles_match(particles, {p1, G0, Hp, Hm}))
            c += -(q[p1][2] * Lam7 * (double)sgn(Lam6)).imag();
          else if (particles_match(particles, {p1, p2, Hp, Hm}))
            c += get_quartic_coupling_higgs_hhHpHm(s, q, particles_perm);
          else if (particles_match(particles, {p1, p2, Gp, Gm}))
            c += get_quartic_coupling_higgs_hhGpGm(s, q, particles_perm);
          else if (particles_match(particles, {p1, p2, Hp, Gm}))
            c += get_quartic_coupling_higgs_hhGmHp(s, q, particles_perm);
          else if (particles_match(particles, {p1, p2, Hm, Gp}))
            c += std::conj(get_quartic_coupling_higgs_hhGmHp(s, q, particles_perm));
        }
        else if (!is_neutral(p1) && !is_neutral(p2) && !is_neutral(p3) && !is_neutral(p4))
        {
          if (particles_match(particles, {Gp, Gp, Gm, Gm}))
            c += 4.0 * 0.5 * Lam1;
          else if (particles_match(particles, {Hp, Hp, Hm, Hm}))
            c += 4.0 * 0.5 * Lam2;
          else if (particles_match(particles, {Hp, Hm, Gp, Gm}))
            c += 4.0 * (Lam3 + Lam4);
          else if (particles_match(particles, {Hp, Hp, Gm, Gm}))
            c += 0.5 * Lam5;
          else if (particles_match(particles, {Hm, Hm, Gp, Gp}))
            c += std::conj(0.5 * Lam5);
          else if (particles_match(particles, {Hp, Gp, Gm, Gm}))
            c += 2.0 * Lam6;
          else if (particles_match(particles, {Hm, Gp, Gp, Gm}))
            c += 4.0 * std::conj(1.0 * Lam6);
          else if (particles_match(particles, {Hp, Hp, Hm, Gm}))
            c += 2.0 * Lam7;
          else if (particles_match(particles, {Hp, Hm, Hm, Gp}))
            c += 4.0 * std::conj(1.0 * Lam7);
        }
      }

      return -i * c * (double)sign;
    }

    // puts together a vector of cubic higgs couplings (necessary for NLO unitarity calculation)
    vector<complex<double>> get_cubic_coupling_higgs(ThdmSpec &s, const bool use_physical_basis = true)
    {
      const int size = 17;
      const complex<double> i(0.0, 1.0);
      vector<complex<double>> result(size+1,0.);

      // couplings calculated using the physical basis
      if (use_physical_basis)
      {
        result[1] = get_cubic_coupling_physical_h0GpGm(s);
        result[2] = get_cubic_coupling_physical_h0GpGm(s); // !!!! h0G0G0
        result[3] = get_cubic_coupling_physical_H0GpGm(s);
        result[4] = get_cubic_coupling_physical_H0GpGm(s); // !!!! H0G0G0
        result[5] = get_cubic_coupling_physical_h0GpHm(s);
        result[6] = get_cubic_coupling_physical_h0G0A0(s);
        result[7] = get_cubic_coupling_physical_H0GpHm(s);
        result[8] = get_cubic_coupling_physical_H0G0A0(s);
        result[9] = get_cubic_coupling_physical_A0GpHm(s);
        result[10] = get_cubic_coupling_physical_h0HpHm(s);
        result[11] = get_cubic_coupling_physical_h0A0A0(s);
        result[12] = get_cubic_coupling_physical_H0HpHm(s);
        result[13] = get_cubic_coupling_physical_H0A0A0(s);
        result[14] = get_cubic_coupling_physical_h0h0h0(s);
        result[15] = get_cubic_coupling_physical_h0h0H0(s);
        result[16] = get_cubic_coupling_physical_h0H0H0(s);
        result[17] = get_cubic_coupling_physical_H0H0H0(s);
      }

      // couplings caluclated using the Higgs basis
      else
      {
        result[1] = get_cubic_coupling_higgs(s,h0,Gp,Gm);
        result[2] = get_cubic_coupling_higgs(s,h0,G0,G0);
        result[3] = get_cubic_coupling_higgs(s,H0,Gp,Gm);
        result[4] = get_cubic_coupling_higgs(s,H0,G0,G0);
        result[5] = get_cubic_coupling_higgs(s,h0,Gp,Hm);
        result[6] = get_cubic_coupling_higgs(s,h0,G0,A0);
        result[7] = get_cubic_coupling_higgs(s,H0,Gp,Hm);
        result[8] = get_cubic_coupling_higgs(s,H0,G0,A0);
        result[9] = get_cubic_coupling_higgs(s,A0,Gp,Hm);
        result[10] = get_cubic_coupling_higgs(s,h0,Hp,Hm);
        result[11] = get_cubic_coupling_higgs(s,h0,A0,A0);
        result[12] = get_cubic_coupling_higgs(s,H0,Hp,Hm);
        result[13] = get_cubic_coupling_higgs(s,H0,A0,A0);
        result[14] = get_cubic_coupling_higgs(s,h0,h0,h0);
        result[15] = get_cubic_coupling_higgs(s,h0,h0,H0);
        result[16] = get_cubic_coupling_higgs(s,h0,H0,H0);
        result[17] = get_cubic_coupling_higgs(s,H0,H0,H0);
        for (int j = 1; j <= size; j++)
          result[j] = -i * result[j];
      }

      return result;
    }

    // puts together a vector of quartic higgs couplings (necessary for NLO unitarity calculation)
    vector<complex<double>> get_quartic_couplings(ThdmSpec &s, const bool use_physical_basis = true)
    {
      const int size = 22;
      const complex<double> i(0.0, 1.0);
      vector<complex<double>> result(size+1,0.);

      // couplings calculated using the physical basis
      if (use_physical_basis)
      {
        result[1] = get_quartic_coupling_physical_h0h0G0G0(s);
        result[2] = get_quartic_coupling_physical_HpHmG0G0(s); // X
        result[3] = get_quartic_coupling_physical_A0A0G0G0(s);
        result[4] = get_quartic_coupling_physical_h0h0G0A0(s);
        result[5] = get_quartic_coupling_physical_H0H0G0A0(s);
        result[6] = get_quartic_coupling_physical_HpHmG0A0(s); // X
        result[7] = get_quartic_coupling_physical_A0A0G0A0(s); // X
        result[8] = 3.0 * get_quartic_coupling_physical_A0A0G0A0(s); // X
        result[9] = get_quartic_coupling_physical_h0h0HpHm(s); // X
        result[10] = get_quartic_coupling_physical_h0h0A0A0(s);
        result[11] = get_quartic_coupling_physical_H0H0HpHm(s);
        result[12] = get_quartic_coupling_physical_H0H0A0A0(s);
        result[13] = get_quartic_coupling_physical_h0H0HpHm(s);
        result[14] = get_quartic_coupling_physical_h0H0A0A0(s);
        result[15] = get_quartic_coupling_physical_h0h0h0h0(s);
        result[16] = get_quartic_coupling_physical_h0h0h0H0(s);
        result[17] = get_quartic_coupling_physical_h0h0H0H0(s);
        result[18] = get_quartic_coupling_physical_h0H0H0H0(s);
        result[19] = get_quartic_coupling_physical_H0H0H0H0(s);
        result[20] = get_quartic_coupling_physical_HpHmHpHm(s);
        result[21] = get_quartic_coupling_physical_HpHmHpHm(s) / 2.0;
        result[22] = 3.0 * get_quartic_coupling_physical_HpHmHpHm(s) / 2.0;
      }

      // couplings caluclated using the Higgs basis
      else
      {
        result[1] = get_quartic_coupling_higgs(s,h0,h0,G0,G0);
        result[2] = get_quartic_coupling_higgs(s,H0,H0,G0,G0);
        result[3] = get_quartic_coupling_higgs(s,Hp,Hm,G0,G0); // X
        result[4] = get_quartic_coupling_higgs(s,A0,A0,G0,G0);
        result[5] = get_quartic_coupling_higgs(s,h0,h0,G0,A0); // differs
        result[6] = get_quartic_coupling_higgs(s,H0,H0,G0,A0); // differs
        result[7] = get_quartic_coupling_higgs(s,Hp,Hm,G0,A0); // X equal if third term in equation is .imag() not .real()
        result[8] = get_quartic_coupling_higgs(s,A0,A0,G0,A0); // X is different by a factor of sign(Lam6)
        result[9] = get_quartic_coupling_higgs(s,h0,h0,Hp,Hm);
        result[10] = get_quartic_coupling_higgs(s,h0,h0,A0,A0);
        result[11] = get_quartic_coupling_higgs(s,H0,H0,Hp,Hm);
        result[12] = get_quartic_coupling_higgs(s,H0,H0,A0,A0);
        result[13] = get_quartic_coupling_higgs(s,h0,H0,Hp,Hm);
        result[14] = get_quartic_coupling_higgs(s,h0,H0,A0,A0);
        result[15] = get_quartic_coupling_higgs(s,h0,h0,h0,h0);
        result[16] = get_quartic_coupling_higgs(s,h0,h0,h0,H0);
        result[17] = get_quartic_coupling_higgs(s,h0,h0,H0,H0);
        result[18] = get_quartic_coupling_higgs(s,h0,H0,H0,H0);
        result[19] = get_quartic_coupling_higgs(s,H0,H0,H0,H0);
        result[20] = get_quartic_coupling_higgs(s,Hp,Hm,Hp,Hm);
        result[21] = get_quartic_coupling_higgs(s,A0,A0,Hp,Hm);
        result[22] = get_quartic_coupling_higgs(s,A0,A0,A0,A0);
        for (int j = 1; j <= size; j++)
          result[j] = -i * result[j];
      }

      return result;
    }

    void check_coupling_calcs(ThdmSpec &s)
    {
      // check cubic couplings

      vector<std::string> names = {"h0GpGm", "h0GpGm", "H0GpGm", "H0GpGm", "h0GpHm", "h0G0A0", "H0GpHm", "H0G0A0", "A0GpHm", "h0HpHm", "h0A0A0", "H0HpHm", "H0A0A0", "h0h0h0", "h0h0H0", "h0H0H0", "H0H0H0", };

      auto couplings_physical = get_cubic_coupling_higgs(s, true);
      auto couplings_higgs = get_cubic_coupling_higgs(s, false);

      for (size_t i=0; i<names.size(); ++i)
      {
        double mag = 0.5 * (abs(couplings_higgs[i+1]) + abs(couplings_physical[i+1]) +1e-6);
        double err = abs(couplings_higgs[i+1] - couplings_physical[i+1]) / mag;
        if (err > 1e-7) std::cerr << "coupling mismatch (" << names[i] << "): " << std::fixed << std::setprecision(4) << err << std::endl;
      }

      // check quartic couplings

      vector<std::string> names2 = { "h0h0G0G0", "HpHmG0G0", "A0A0G0G0", "h0h0G0A0", "H0H0G0A0", "HpHmG0A0", "A0A0G0A0", "A0A0G0A0", "h0h0HpHm", "h0h0A0A0", "H0H0HpHm", "H0H0A0A0", "h0H0HpHm", "h0H0A0A0", "h0h0h0h0", "h0h0h0H0", "h0h0H0H0", "h0H0H0H0", "H0H0H0H0", "HpHmHpHm", "HpHmHpHm", "HpHmHpHm" };

      couplings_physical = get_quartic_couplings(s, true);
      couplings_higgs = get_quartic_couplings(s, false);

      for (size_t i=0; i<names2.size(); ++i)
      {
        double mag = 0.5 * (abs(couplings_higgs[i]) + abs(couplings_physical[i]) + 1e-6);
        double err = abs(couplings_higgs[i] - couplings_physical[i]) / mag;
        if (err > 1e-7) std::cerr << "coupling mismatch (" << names2[i] << "): " << std::fixed << std::setprecision(4) << err << std::endl;
      }
    }
    

    ///  ===============================================================
    ///  == functions to fill parameters for NLO unitarity likelihood ==
    ///  ===============================================================


    // -- wavefunction corrections to beta functions

    double A0_bar(const double m2)
    {
      const double MZ = 91.15349; // get this from FS
      double mu2 = pow(MZ, 2);
      return m2 * (-log(m2 / mu2) + 1.0);
    }

    struct B0_integration_variables
    {
      double x;
      double p2;
      double m12;
      double m22;
      double mu2;
      double z_plus;
    };

    double B0_bar_integration_real(const double x, void *params)
    {
      B0_integration_variables *input_pars = static_cast<B0_integration_variables *>(params);
      double p2 = input_pars->p2, m12 = input_pars->m12, m22 = input_pars->m22, mu2 = input_pars->mu2, z_plus = input_pars->z_plus;
      double re = (p2 * x * x - x * (p2 - m12 - m22) + m22) / mu2;
      double im = -z_plus / mu2;
      return log(sqrt(re * re + im * im));
    }

    double B0_bar_integration_imag(const double x, void *params)
    {
      B0_integration_variables *input_pars = static_cast<B0_integration_variables *>(params);
      double p2 = input_pars->p2, m12 = input_pars->m12, m22 = input_pars->m22, mu2 = input_pars->mu2, z_plus = input_pars->z_plus;
      double re = (p2 * x * x - x * (p2 - m12 - m22) + m22) / mu2;
      double im = -z_plus / mu2;
      return atan(im / re);
    }

    complex<double> B0_bar(const double p2, const double m12, const double m22)
    {
      const double MZ = 91.15349; // get this from FS
      const complex<double> i(0.0, 1.0);
      double mu2 = pow(MZ, 2);
      double z_plus = 1E-10;
      double result_real, error_real, result_imag, error_imag;
      // real
      gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
      gsl_function B0_bar_int;
      B0_bar_int.function = &B0_bar_integration_real;
      B0_integration_variables input_pars;
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
      B0_bar_int_imag.function = &B0_bar_integration_imag;
      B0_bar_int_imag.params = &input_pars;
      gsl_integration_qag(&B0_bar_int_imag, 0, 1.0, 1e-7, 1e-7, 1000, 1, w_imag, &result_imag, &error_imag);
      gsl_integration_workspace_free(w_imag);

      return (result_real + i * result_imag);
    }

    struct wavefunction_renormalization_input
    {
      double mh;
      double mH;
      double mA;
      double mC;
      double mG;
      double mGC;
      double beta;
      double alpha;
      double m122;
      vector<complex<double>> m;
      vector<complex<double>> g;
    };

    wavefunction_renormalization_input fill_wavefunction_renormalization_input(ThdmSpec &s)
    {
      wavefunction_renormalization_input input;
      fill_physical_basis(input, s);
      input.m = get_cubic_coupling_higgs(s);
      input.g = get_quartic_couplings(s);
      return input;
    }

    enum wavefunction_renormalization
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

    double mZw2(const void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, b = input_pars->beta, alpha = input_pars->alpha, m122 = input_pars->m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double a = alpha, sb = sin(b), cb = cos(b), sba = sin(b - a), cba = abs(cos(b - a)), s2b2a = sin(2.0 * b - 2.0 * a), t2b = tan(2.0 * b);
      return 1.0 / 2.0 * (mh2 * pow(sba, 2) + mH2 * pow(cba, 2) + (mh2 - mH2) * s2b2a * (1.0 / t2b) - 2.0 * m122 * (1.0 / sb) * (1.0 / cb));
    }

    // -- Self energies & wavefunction renormalizations

    complex<double> Pi_tilde_wpwm(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      complex<double> Pi = pow(m[1], 2) * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += pow(m[3], 2) * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += pow(m[5], 2) * (B0_bar(p2, mC2, mh2) - B0_bar(0., mC2, mh2));
      Pi += pow(m[7], 2) * (B0_bar(p2, mC2, mH2) - B0_bar(0., mC2, mH2));
      Pi += m[9] * std::conj(m[9]) * (B0_bar(p2, mC2, mA2) - B0_bar(0., mC2, mA2));
      return -1.0 / (16.0 * pow(M_PI, 2)) * Pi;
    }
    double Pi_tilde_wpwm_re(const double p2, void *params) { return Pi_tilde_wpwm(p2, params).real(); }
    double Pi_tilde_wpwm_im(const double p2, void *params) { return Pi_tilde_wpwm(p2, params).imag(); }

    complex<double> Pi_tilde_zz(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      complex<double> Pi = pow(m[2], 2) * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += pow(m[4], 2) * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += pow(m[6], 2) * (B0_bar(p2, mA2, mh2) - B0_bar(0., mA2, mh2));
      Pi += pow(m[8], 2) * (B0_bar(p2, mA2, mH2) - B0_bar(0., mA2, mH2));
      return -1.0 / (16.0 * pow(M_PI, 2)) * Pi;
    }
    double Pi_tilde_zz_re(const double p2, void *params) { return Pi_tilde_zz(p2, params).real(); }
    double Pi_tilde_zz_im(const double p2, void *params) { return Pi_tilde_zz(p2, params).imag(); }

    complex<double> Pi_tilde_wpHm(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      complex<double> Pi = m[1] * m[5] * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += m[3] * m[7] * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += m[5] * m[10] * (B0_bar(p2, mC2, mh2) - B0_bar(0., mC2, mh2));
      Pi += m[7] * m[12] * (B0_bar(p2, mC2, mH2) - B0_bar(0., mC2, mH2));
      return -1.0 / (16.0 * pow(M_PI, 2)) * Pi;
    }
    double Pi_tilde_wpHm_re(const double p2, void *params) { return Pi_tilde_wpHm(p2, params).real(); }
    double Pi_tilde_wpHm_im(const double p2, void *params) { return Pi_tilde_wpHm(p2, params).imag(); }

    complex<double> Pi_tilde_zA(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      complex<double> Pi = m[2] * m[6] * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += m[4] * m[8] * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += m[6] * m[11] * (B0_bar(p2, mA2, mh2) - B0_bar(0., mA2, mh2));
      Pi += m[8] * m[13] * (B0_bar(p2, mA2, mH2) - B0_bar(0., mA2, mH2));
      return -1.0 / (16.0 * pow(M_PI, 2)) * Pi;
    }
    double Pi_tilde_zA_re(const double p2, void *params) { return Pi_tilde_zA(p2, params).real(); }
    double Pi_tilde_zA_im(const double p2, void *params) { return Pi_tilde_zA(p2, params).imag(); }

    complex<double> Pi_zz(void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (g[1] * A0_bar(mh2) + g[2] * A0_bar(mH2) + 2.0 * g[3] * A0_bar(mC2) + g[4] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[2], 2) * B0_bar(0., 0., mh2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[4], 2) * B0_bar(0., 0., mH2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[6], 2) * B0_bar(0., mA2, mh2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[8], 2) * B0_bar(0., mA2, mH2);
      return Pi;
    }
    double Pi_zz_re(void *params) { return Pi_zz(params).real(); }
    double Pi_zz_im(void *params) { return Pi_zz(params).imag(); }

    double Pi_wpwm_re(void *params) { return Pi_zz(params).real(); }
    double Pi_wpwm_im(void *params) { return Pi_zz(params).imag(); }

    complex<double> Pi_zA(void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (g[5] * A0_bar(mh2) + g[6] * A0_bar(mH2) + 2.0 * g[7] * A0_bar(mC2) + g[8] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * m[2] * m[6] * B0_bar(0., 0., mh2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * m[4] * m[8] * B0_bar(0., 0., mH2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * m[6] * m[11] * B0_bar(0., mA2, mh2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * m[8] * m[13] * B0_bar(0., mA2, mH2);
      return Pi;
    }
    double Pi_zA_re(void *params) { return Pi_zA(params).real(); }
    double Pi_zA_im(void *params) { return Pi_zA(params).imag(); }

    double Pi_wpHm_re(void *params) { return Pi_zA(params).real(); }
    double Pi_wpHm_im(void *params) { return Pi_zA(params).imag(); }

    double Z_w(void *params); // Necessary forward declaration

    complex<double> Pi_tilde_hh(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC, beta = input_pars->beta, alpha = input_pars->alpha;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      const double sba = sin(beta - alpha), cba = abs(cos(beta - alpha));
      complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (2.0 * g[9] * A0_bar(mC2) + g[10] * A0_bar(mA2) + g[15] * A0_bar(mh2) + g[17] * A0_bar(mH2));
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * (2.0 * pow(m[1], 2) + pow(m[2], 2)) * B0_bar(p2, 0, 0);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 4.0 * pow(m[5], 2) * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 2.0 * pow(m[6], 2) * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 2.0 * pow(m[10], 2) * B0_bar(p2, mC2, mC2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * pow(m[11], 2) * B0_bar(p2, mA2, mA2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * pow(m[14], 2) * B0_bar(p2, mh2, mh2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 2.0 * pow(m[15], 2) * B0_bar(p2, mH2, mh2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * pow(m[16], 2) * B0_bar(p2, mH2, mH2);
      Pi += -pow(sba, 2) * Pi_zz(params) - 2.0 * sba * cba * Pi_zA(params) + (Z_w(params) - 1.0) * (mh2 + mZw2(params) * pow(cba, 2));
      return Pi;
    }
    double Pi_tilde_hh_re(const double p2, void *params) { return Pi_tilde_hh(p2, params).real(); }
    double Pi_tilde_hh_im(const double p2, void *params) { return Pi_tilde_hh(p2, params).imag(); }

    complex<double> Pi_tilde_HH(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC, beta = input_pars->beta, alpha = input_pars->alpha;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      const double sba = sin(beta - alpha), cba = cos(beta - alpha);
      complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (2.0 * g[11] * A0_bar(mC2) + g[12] * A0_bar(mA2) + g[17] * A0_bar(mh2) + g[19] * A0_bar(mH2));
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * (2.0 * pow(m[3], 2) + pow(m[4], 2)) * B0_bar(p2, 0, 0);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 4.0 * pow(m[7], 2) * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 2.0 * pow(m[8], 2) * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 2.0 * pow(m[12], 2) * B0_bar(p2, mC2, mC2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * pow(m[13], 2) * B0_bar(p2, mA2, mA2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * pow(m[15], 2) * B0_bar(p2, mh2, mh2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 2.0 * pow(m[16], 2) * B0_bar(p2, mH2, mh2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * pow(m[17], 2) * B0_bar(p2, mH2, mH2);
      Pi += -pow(cba, 2) * Pi_zz(params) + 2.0 * sba * cba * Pi_zA(params) + (Z_w(params) - 1.0) * (mH2 + mZw2(params) * pow(sba, 2));
      return Pi;
    }
    double Pi_tilde_HH_re(const double p2, void *params) { return Pi_tilde_HH(p2, params).real(); }
    double Pi_tilde_HH_im(const double p2, void *params) { return Pi_tilde_HH(p2, params).imag(); }

    complex<double> Pi_tilde_hH(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC, beta = input_pars->beta, alpha = input_pars->alpha;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      const double sba = sin(beta - alpha), cba = abs(cos(beta - alpha));
      complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (2.0 * g[13] * A0_bar(mC2) + g[14] * A0_bar(mA2) + g[16] * A0_bar(mh2) + g[18] * A0_bar(mH2));
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * (2.0 * m[1] * m[3] + m[2] * m[4]) * B0_bar(p2, 0, 0);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 4.0 * m[5] * m[7] * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 2.0 * m[6] * m[8] * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 2.0 * m[10] * m[12] * B0_bar(p2, mC2, mC2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * m[11] * m[13] * B0_bar(p2, mA2, mA2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * m[14] * m[15] * B0_bar(p2, mh2, mh2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * 2.0 * m[15] * m[16] * B0_bar(p2, mH2, mh2);
      Pi += -1.0 / (32.0 * pow(M_PI, 2)) * m[16] * m[17] * B0_bar(p2, mH2, mH2);
      Pi += -sba * cba * Pi_zz(params) - (pow(cba, 2) - pow(sba, 2)) * Pi_zA(params) - (Z_w(params) - 1.0) * (mZw2(params) * sba * cba);
      return Pi;
    }
    double Pi_tilde_hH_re(const double p2, void *params) { return Pi_tilde_hH(p2, params).real(); }
    double Pi_tilde_hH_im(const double p2, void *params) { return Pi_tilde_hH(p2, params).imag(); }

    complex<double> Pi_tilde_HpHm(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (g[9] * A0_bar(mh2) + g[11] * A0_bar(mH2) + 2.0 * g[20] * A0_bar(mC2) + g[21] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[5], 2) * B0_bar(p2, 0., mh2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[7], 2) * B0_bar(p2, 0., mH2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * std::conj(m[9]) * m[9] * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[10], 2) * B0_bar(p2, mC2, mh2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[12], 2) * B0_bar(p2, mC2, mH2);
      Pi += (Z_w(params) - 1.0) * (mC2 + mZw2(params));
      return Pi;
    }
    double Pi_tilde_HpHm_re(const double p2, void *params) { return Pi_tilde_HpHm(p2, params).real(); }
    double Pi_tilde_HpHm_im(const double p2, void *params) { return Pi_tilde_HpHm(p2, params).imag(); }

    complex<double> Pi_tilde_AA(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const vector<complex<double>> m = input_pars->m, g = input_pars->g;
      complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (g[10] * A0_bar(mh2) + g[12] * A0_bar(mH2) + 2.0 * g[21] * A0_bar(mC2) + g[22] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[6], 2) * B0_bar(p2, 0., mh2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[8], 2) * B0_bar(p2, 0., mH2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * 2.0 * std::conj(m[9]) * m[9] * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[11], 2) * B0_bar(p2, mA2, mh2);
      Pi += -1.0 / (16.0 * pow(M_PI, 2)) * pow(m[13], 2) * B0_bar(p2, mA2, mH2);
      Pi += (Z_w(params) - 1.0) * (mA2 + mZw2(params));
      return Pi;
    }
    double Pi_tilde_AA_re(const double p2, void *params) { return Pi_tilde_AA(p2, params).real(); }
    double Pi_tilde_AA_im(const double p2, void *params) { return Pi_tilde_AA(p2, params).imag(); }

    complex<double> z_ii(const wavefunction_renormalization type, wavefunction_renormalization_input &params)
    {
      gsl_function F_re;
      gsl_function F_im;
      F_re.params = &params;
      F_im.params = &params;
      double result_re, result_im, abserr_re, abserr_im;
      double m_in = 0.0;
      const complex<double> i(0.0, 1.0);
      switch (type)
      {
      case wpwm:
        F_re.function = &Pi_tilde_wpwm_re;
        F_im.function = &Pi_tilde_wpwm_im;
        m_in = params.mGC;
        break;
      case zz:
        F_re.function = &Pi_tilde_zz_re;
        F_im.function = &Pi_tilde_zz_im;
        m_in = params.mG;
        break;
      case hh:
        F_re.function = &Pi_tilde_hh_re;
        F_im.function = &Pi_tilde_hh_im;
        m_in = params.mh;
        break;
      case HH:
        F_re.function = &Pi_tilde_HH_re;
        F_im.function = &Pi_tilde_HH_im;
        m_in = params.mH;
        break;
      case HpHm:
        F_re.function = &Pi_tilde_HpHm_re;
        F_im.function = &Pi_tilde_HpHm_im;
        m_in = params.mC;
        break;
      case AA:
        F_re.function = &Pi_tilde_AA_re;
        F_im.function = &Pi_tilde_AA_im;
        m_in = params.mA;
        break;
      default:
        std::cerr << "WARNING: Unrecognized wavefunction renormalization particle pair sent to z_ij function. Returning 0." << std::endl;
        return 0.0;
      }
      gsl_deriv_central(&F_re, pow(m_in, 2), 1e-8, &result_re, &abserr_re);
      gsl_deriv_central(&F_im, pow(m_in, 2), 1e-8, &result_im, &abserr_im);
      const complex<double> Z_ii = 1.0 + 0.5 * (result_re + i * result_im);
      return 16.0 * pow(M_PI, 2) * (Z_ii - 1.0);
    }

    complex<double> z_ij(const wavefunction_renormalization type, ThdmSpec &s)
    {
      complex<double> z_ij = 0.0;
      double m1 = 0.0, m2 = 0.0;
      wavefunction_renormalization_input input_pars = fill_wavefunction_renormalization_input(s);
      switch (type)
      {
      case wpHm:
        m1 = input_pars.mGC;
        m2 = input_pars.mC;
        z_ij = Pi_tilde_wpHm(m1, &input_pars);
        break;
      case zA:
        m1 = input_pars.mG;
        m2 = input_pars.mA;
        z_ij = Pi_tilde_zA(m1, &input_pars);
        break;
      case hH:
        m1 = input_pars.mh;
        m2 = input_pars.mH;
        z_ij = Pi_tilde_hH(m1, &input_pars);
        break;
      case Hpwm:
        m1 = input_pars.mC;
        m2 = input_pars.mGC;
        z_ij = Pi_tilde_wpHm(m1, &input_pars);
        break;
      case Az:
        m1 = input_pars.mA;
        m2 = input_pars.mG;
        z_ij = Pi_tilde_zA(m1, &input_pars);
        break;
      case Hh:
        m1 = input_pars.mH;
        m2 = input_pars.mh;
        z_ij = Pi_tilde_hH(m1, &input_pars);
        break;
      default:
        z_ij = z_ii(type, input_pars);
        return z_ij;
      }
      return 16.0 * pow(M_PI, 2) * z_ij / (pow(m1, 2) - pow(m2, 2));
    }

    double Z_w(void *params)
    {
      gsl_function F_re, F_im;
      F_re.params = params;
      F_im.params = params;
      F_re.function = &Pi_tilde_wpwm_re;
      F_im.function = &Pi_tilde_wpwm_im;
      double result_re, abserr_re, result_im, abserr_im;
      double m_in = 0.0;
      gsl_deriv_central(&F_re, m_in, 1e-8, &result_re, &abserr_re);
      gsl_deriv_central(&F_im, m_in, 1e-8, &result_im, &abserr_im);
      return 1.0 + 0.5 * (result_re + result_im);
    }

    // -- Custom functions to extend GSL

    complex<double> gsl_complex_to_complex_double(const gsl_complex c)
    {
      return complex<double>(GSL_REAL(c), GSL_IMAG(c));
    }

    complex<double> gsl_matrix_complex_trace_complex(const gsl_matrix_complex *m1)
    {
      return gsl_complex_to_complex_double(gsl_matrix_complex_get(m1, 0, 0)) +
             gsl_complex_to_complex_double(gsl_matrix_complex_get(m1, 1, 1)) +
             gsl_complex_to_complex_double(gsl_matrix_complex_get(m1, 2, 2));
    }

    // gets Yukawa traces required for LO corrections to lambdai beta functions
    //- easily extendable to Yukawas with off-diagonals
    std::map<std::string, complex<double>> get_traces_of_y(const SubSpectrum& he)
    {
      complex<double> tr_u2, tr_d2, tr_l2, tr_u4, tr_d4, tr_l4, tr_du;
      gsl_matrix_complex *y_u, *y_d, *y_l, *y_u_dagger, *y_d_dagger, *y_l_dagger;
      const int size = 3;

      y_u = gsl_matrix_complex_alloc(size, size);
      y_d = gsl_matrix_complex_alloc(size, size);
      y_l = gsl_matrix_complex_alloc(size, size);
      y_u_dagger = gsl_matrix_complex_alloc(size, size);
      y_d_dagger = gsl_matrix_complex_alloc(size, size);
      y_l_dagger = gsl_matrix_complex_alloc(size, size);

      // set yukawa - up
      gsl_complex y_u_11;
      GSL_SET_REAL(&y_u_11, he.get(Par::dimensionless, "Yu", 1, 1));
      GSL_SET_IMAG(&y_u_11, 0.0);

      gsl_complex y_u_22;
      GSL_SET_REAL(&y_u_22, he.get(Par::dimensionless, "Yu", 2, 2));
      GSL_SET_IMAG(&y_u_22, 0.0);

      gsl_complex y_u_33;
      GSL_SET_REAL(&y_u_33, he.get(Par::dimensionless, "Yu", 3, 3));
      GSL_SET_IMAG(&y_u_33, 0.0);

      gsl_matrix_complex_set_zero(y_u);

      gsl_matrix_complex_set(y_u, 0, 0, y_u_11);
      gsl_matrix_complex_set(y_u, 1, 1, y_u_22);
      gsl_matrix_complex_set(y_u, 2, 2, y_u_33);

      // take dagger -> all components currently real so no need to conjugate
      gsl_matrix_complex_transpose_memcpy(y_u_dagger, y_u);

      // set yukawa - down
      gsl_complex y_d_11;
      GSL_SET_REAL(&y_d_11, he.get(Par::dimensionless, "Yd", 1, 1));
      GSL_SET_IMAG(&y_d_11, 0.0);

      gsl_complex y_d_22;
      GSL_SET_REAL(&y_d_22, he.get(Par::dimensionless, "Yd", 2, 2));
      GSL_SET_IMAG(&y_d_22, 0.0);

      gsl_complex y_d_33;
      GSL_SET_REAL(&y_d_33, he.get(Par::dimensionless, "Yd", 3, 3));
      GSL_SET_IMAG(&y_d_33, 0.0);

      gsl_matrix_complex_set_zero(y_d);

      gsl_matrix_complex_set(y_d, 0, 0, y_d_11);
      gsl_matrix_complex_set(y_d, 1, 1, y_d_22);
      gsl_matrix_complex_set(y_d, 2, 2, y_d_33);

      // take dagger -> all components currently real so no need to conjugate
      gsl_matrix_complex_transpose_memcpy(y_d_dagger, y_d);

      // set yukawa - lepton
      gsl_complex y_l_11;
      GSL_SET_REAL(&y_l_11, he.get(Par::dimensionless, "Ye", 1, 1));
      GSL_SET_IMAG(&y_l_11, 0.0);

      gsl_complex y_l_22;
      GSL_SET_REAL(&y_l_22, he.get(Par::dimensionless, "Ye", 2, 2));
      GSL_SET_IMAG(&y_l_22, 0.0);

      gsl_complex y_l_33;
      GSL_SET_REAL(&y_l_33, he.get(Par::dimensionless, "Ye", 3, 3));
      GSL_SET_IMAG(&y_l_33, 0.0);

      gsl_matrix_complex_set_zero(y_l);

      gsl_matrix_complex_set(y_l, 0, 0, y_l_11);
      gsl_matrix_complex_set(y_l, 1, 1, y_l_22);
      gsl_matrix_complex_set(y_l, 2, 2, y_l_33);

      // take dagger -> all components currently real so no need to conjugate
      gsl_matrix_complex_transpose_memcpy(y_l_dagger, y_l);

      //calculate traces - up
      gsl_matrix_complex *y_u2;
      gsl_matrix_complex *y_u4;
      y_u2 = gsl_matrix_complex_alloc(size, size);
      y_u4 = gsl_matrix_complex_alloc(size, size);

      gsl_matrix_complex_memcpy(y_u2, y_u);
      gsl_matrix_complex_mul_elements(y_u2, y_u_dagger);
      tr_u2 = gsl_matrix_complex_trace_complex(y_u2);

      gsl_matrix_complex_memcpy(y_u4, y_u2);
      gsl_matrix_complex_mul_elements(y_u4, y_u2);
      tr_d4 = gsl_matrix_complex_trace_complex(y_u4);

      //calculate traces - down
      gsl_matrix_complex *y_d2;
      gsl_matrix_complex *y_d4;
      y_d2 = gsl_matrix_complex_alloc(size, size);
      y_d4 = gsl_matrix_complex_alloc(size, size);

      gsl_matrix_complex_memcpy(y_d2, y_d);
      gsl_matrix_complex_mul_elements(y_d2, y_d_dagger);
      tr_d2 = gsl_matrix_complex_trace_complex(y_d2);

      gsl_matrix_complex_memcpy(y_d4, y_d2);
      gsl_matrix_complex_mul_elements(y_d4, y_d2);
      tr_d4 = gsl_matrix_complex_trace_complex(y_d4);

      // calculate trace for down*up
      gsl_matrix_complex_mul_elements(y_d2, y_u2);
      tr_du = gsl_matrix_complex_trace_complex(y_d2);

      gsl_matrix_complex_free(y_d2);
      gsl_matrix_complex_free(y_u2);
      gsl_matrix_complex_free(y_d4);
      gsl_matrix_complex_free(y_u4);

      //calculate traces - lepton
      gsl_matrix_complex *y_l2;
      y_l2 = gsl_matrix_complex_alloc(size, size);
      gsl_matrix_complex_memcpy(y_l2, y_l);

      gsl_matrix_complex_mul_elements(y_l2, y_l_dagger);
      tr_l2 = gsl_matrix_complex_trace_complex(y_l2);

      gsl_matrix_complex_mul_elements(y_l2, y_l2); // y_l^2 is now y_l^4
      tr_l4 = gsl_matrix_complex_trace_complex(y_l2);

      gsl_matrix_complex_free(y_l2);

      gsl_matrix_complex_free(y_u);
      gsl_matrix_complex_free(y_d);
      gsl_matrix_complex_free(y_l);
      gsl_matrix_complex_free(y_u_dagger);
      gsl_matrix_complex_free(y_d_dagger);
      gsl_matrix_complex_free(y_l_dagger);

      return {{"tr_u2", tr_u2},
              {"tr_d2", tr_d2},
              {"tr_l2", tr_l2},
              {"tr_u4", tr_u4},
              {"tr_d4", tr_d4},
              {"tr_l4", tr_l4},
              {"tr_du", tr_du}};
    }

    // returns model specific coeffiecients (a_i) to Yukawa terms
    // appearing in the LO corrections to lambdai beta functions
    // see Nucl.Phys.B 262 (1985) 517-537
    vector<double> get_alphas_for_type(const int type)
    {
      vector<double> a;
      const int size = 24;
      a.push_back(0);
      for (int i = 1; i < size; i++)
      {
        a.push_back(1);
      }
      switch (type)
      {
      case 1:
        a[1] = 0;
        a[2] = 0;
        a[3] = 0;
        a[4] = 0;
        a[5] = 0;
        a[6] = 0;
        a[7] = 1;
        a[8] = 1;
        a[9] = 1;
        a[10] = 1;
        a[11] = 1;
        a[12] = 1;
        a[13] = 1;
        a[14] = 1;
        a[15] = 1;
        a[16] = 0;
        a[17] = 1;
        a[18] = 1;
        a[19] = 1;
        a[20] = 0;
        a[21] = 1;
        a[22] = 1;
        a[23] = 1;
        break;
      case 2:
        a[1] = 1;
        a[2] = 1;
        a[3] = 0;
        a[4] = 1;
        a[5] = 1;
        a[6] = 0;
        a[7] = 0;
        a[8] = 0;
        a[9] = 1;
        a[10] = 0;
        a[11] = 0;
        a[12] = 1;
        a[13] = 1;
        a[14] = 1;
        a[15] = 1;
        a[16] = 1;
        a[17] = 1;
        a[18] = 1;
        a[19] = 1;
        a[20] = 1;
        a[21] = 1;
        a[22] = 1;
        a[23] = 1;
        break;
      case 3:
        a[1] = 1;
        a[2] = 0;
        a[3] = 0;
        a[4] = 1;
        a[5] = 0;
        a[6] = 0;
        a[7] = 0;
        a[8] = 1;
        a[9] = 1;
        a[10] = 0;
        a[11] = 1;
        a[12] = 1;
        a[13] = 1;
        a[14] = 1;
        a[15] = 1;
        a[16] = 0;
        a[17] = 1;
        a[18] = 1;
        a[19] = 1;
        a[20] = 0;
        a[21] = 1;
        a[22] = 1;
        a[23] = 1;
        break;
      case 4:
        a[1] = 0;
        a[2] = 1;
        a[3] = 0;
        a[4] = 0;
        a[5] = 1;
        a[6] = 0;
        a[7] = 1;
        a[8] = 1;
        a[9] = 0;
        a[10] = 1;
        a[11] = 1;
        a[12] = 0;
        a[13] = 1;
        a[14] = 1;
        a[15] = 1;
        a[16] = 1;
        a[17] = 1;
        a[18] = 1;
        a[19] = 1;
        a[20] = 1;
        a[21] = 1;
        a[22] = 1;
        a[23] = 1;
        break;
      case -1:
        break;
      default:
        break;
      }
      return a;
    }

    // gets Yukawa traces required for LO corrections to lambdai beta functions
    // simple functions for efficiency - only for diagonal Yukawas
    double get_tr_pow(const SubSpectrum& he, std::string yukawa_name, int pow_N)
    {
      double tr = 0.0;
      for (int i = 1; i <= 3; i++)
      {
        tr += pow(he.get(Par::dimensionless, yukawa_name, i, i), pow_N);
      }
      return tr;
    }

    double get_tr_dduu(const SubSpectrum& he)
    {
      double tr = 0.0;
      for (int i = 1; i <= 3; i++)
      {
        tr += pow(he.get(Par::dimensionless, "Yd", i, i), 2) * pow(he.get(Par::dimensionless, "Yu", i, i), 2);
      }
      return tr;
    }

    // LO beta function for lambda1
    complex<double> beta_one(const SubSpectrum& he, ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      vector<double> a = get_alphas_for_type(he.get(Par::dimensionless, "model_type"));
      const vector<double> Lambda = get_lambdas_from_spectrum(s);
      const double g1 = he.get(Par::dimensionless, "g1"), g2 = he.get(Par::dimensionless, "g2");
      const complex<double> tr_u2 = get_tr_pow(he, "Yu", 2), tr_d2 = get_tr_pow(he, "Yd", 2), tr_l2 = get_tr_pow(he, "Ye", 2);
      const complex<double> tr_u4 = get_tr_pow(he, "Yu", 4), tr_d4 = get_tr_pow(he, "Yd", 4), tr_l4 = get_tr_pow(he, "Ye", 4);
      complex<double> beta = 12.0 * pow(Lambda[1], 2) + 4.0 * pow(Lambda[3], 2) + 4.0 * Lambda[3] * Lambda[4] + 2.0 * pow(Lambda[4], 2) + 2.0 * pow(Lambda[5], 2);
      if (gauge_correction)
        beta += 3.0 / 4.0 * pow(g1, 4) + 3.0 / 2.0 * pow(g1, 2) * pow(g2, 2) + 9.0 / 4.0 * pow(g2, 4) - 3.0 * pow(g1, 2) * Lambda[1] - 9.0 * pow(g2, 2) * Lambda[1];
      if (yukawa_correction)
        beta += 4.0 * Lambda[1] * (a[1] * tr_l2 + 3.0 * a[2] * tr_d2 + 3.0 * a[3] * tr_u2) - 4.0 * (a[4] * tr_l4 + 3.0 * a[5] * tr_d4 + 3.0 * a[6] * tr_u4);
      return 1.0 / (16.0 * pow(M_PI, 2)) * (beta);
    }

    // LO beta function for lambda2
    complex<double> beta_two(const SubSpectrum& he, ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      const vector<double> a = get_alphas_for_type(he.get(Par::dimensionless, "model_type"));
      const vector<double> Lambda = get_lambdas_from_spectrum(s);
      const double g1 = he.get(Par::dimensionless, "g1"), g2 = he.get(Par::dimensionless, "g2");
      const complex<double> tr_u2 = get_tr_pow(he, "Yu", 2), tr_d2 = get_tr_pow(he, "Yd", 2), tr_l2 = get_tr_pow(he, "Ye", 2);
      const complex<double> tr_u4 = get_tr_pow(he, "Yu", 4), tr_d4 = get_tr_pow(he, "Yd", 4), tr_l4 = get_tr_pow(he, "Ye", 4);
      complex<double> beta = 12.0 * pow(Lambda[2], 2) + 4.0 * pow(Lambda[3], 2) + 4.0 * Lambda[3] * Lambda[4] + 2.0 * pow(Lambda[4], 2) + 2.0 * pow(Lambda[5], 2);
      if (gauge_correction)
        beta += 3.0 / 4.0 * pow(g1, 4) + 3.0 / 2.0 * pow(g1, 2) * pow(g2, 2) + 9.0 / 4.0 * pow(g2, 4) - 3.0 * pow(g1, 2) * Lambda[2] - 9.0 * pow(g2, 2) * Lambda[2];
      if (yukawa_correction)
        beta += 4.0 * Lambda[2] * (a[7] * tr_l2 + 3.0 * a[8] * tr_d2 + 3.0 * a[9] * tr_u2) - 4.0 * (a[10] * tr_l4 + 3.0 * a[11] * tr_d4 + 3.0 * a[12] * tr_u4);
      return 1.0 / (16.0 * pow(M_PI, 2)) * beta;
    }

    // LO beta function for lambda3
    complex<double> beta_three(const SubSpectrum& he, ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      const vector<double> a = get_alphas_for_type(he.get(Par::dimensionless, "model_type"));
      const vector<double> Lambda = get_lambdas_from_spectrum(s);
      const double g1 = he.get(Par::dimensionless, "g1"), g2 = he.get(Par::dimensionless, "g2");
      const complex<double> tr_u2 = get_tr_pow(he, "Yu", 2), tr_d2 = get_tr_pow(he, "Yd", 2), tr_l2 = get_tr_pow(he, "Ye", 2);
      const complex<double> tr_du = get_tr_dduu(he);
      complex<double> beta = 4.0 * pow(Lambda[3], 2) + 2.0 * pow(Lambda[4], 2) + (Lambda[1] + Lambda[2]) * (6.0 * Lambda[3] + 2.0 * Lambda[4]) + 2.0 * pow(Lambda[5], 2);
      if (gauge_correction)
        beta += -3.0 * Lambda[3] * (3.0 * pow(g2, 2) + pow(g1, 2)) + 9.0 / 4.0 * pow(g2, 4) + 3.0 / 4.0 * pow(g1, 4) - 3.0 / 2.0 * pow(g1, 2) * pow(g2, 2);
      if (yukawa_correction)
        beta += 2 * Lambda[3] * (a[13] * tr_l2 + 3.0 * a[14] * tr_d2 + 3.0 * a[15] * tr_u2) - 12.0 * a[16] * tr_du;
      return 1.0 / (16.0 * pow(M_PI, 2)) * beta;
    }

    // LO beta function for lambda4
    complex<double> beta_four(const SubSpectrum& he, ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      const vector<double> a = get_alphas_for_type(he.get(Par::dimensionless, "model_type"));
      const vector<double> Lambda = get_lambdas_from_spectrum(s);
      const double g1 = he.get(Par::dimensionless, "g1"), g2 = he.get(Par::dimensionless, "g2");
      const complex<double> tr_u2 = get_tr_pow(he, "Yu", 2), tr_d2 = get_tr_pow(he, "Yd", 2), tr_l2 = get_tr_pow(he, "Ye", 2);
      const complex<double> tr_du = get_tr_dduu(he);
      complex<double> beta = (2.0 * Lambda[1] + 2.0 * Lambda[2] + 8.0 * Lambda[3]) * Lambda[4] + 4.0 * pow(Lambda[4], 2) + 8.0 * pow(Lambda[5], 2);
      if (gauge_correction)
        beta += -3.0 * Lambda[4] * (3.0 * pow(g2, 2) + pow(g1, 2)) + 3.0 * pow(g1, 2) * pow(g2, 2);
      if (yukawa_correction)
        beta += 2.0 * Lambda[4] * (a[17] * tr_l2 + 3.0 * a[18] * tr_d2 + 3.0 * a[19] * tr_u2) + 12.0 * a[20] * tr_du;
      return 1.0 / (16.0 * pow(M_PI, 2)) * beta;
    }

    // LO beta function for lambda5
    complex<double> beta_five(const SubSpectrum& he, ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      const vector<double> a = get_alphas_for_type(he.get(Par::dimensionless, "model_type"));
      const vector<double> Lambda = get_lambdas_from_spectrum(s);
      const double g1 = he.get(Par::dimensionless, "g1"), g2 = he.get(Par::dimensionless, "g2");
      const complex<double> tr_u2 = get_tr_pow(he, "Yu", 2), tr_d2 = get_tr_pow(he, "Yd", 2), tr_l2 = get_tr_pow(he, "Ye", 2);
      complex<double> beta = (2.0 * Lambda[1] + 2.0 * Lambda[2] + 8.0 * Lambda[3] + 12.0 * Lambda[4]) * Lambda[5];
      if (gauge_correction)
        beta += -3.0 * Lambda[5] * (3.0 * pow(g2, 2) + pow(g1, 2));
      if (yukawa_correction)
        beta += 2.0 * Lambda[5] * (a[21] * tr_l2 + 3.0 * a[22] * tr_d2 + 3.0 * a[23] * tr_u2);
      return 1.0 / (16.0 * pow(M_PI, 2)) * beta;
    }

    // put everything together to get the NLO unitarity scattering eigenvalues
    vector<complex<double>> get_NLO_scattering_eigenvalues(const SubSpectrum& he, ThdmSpec &s, const bool wave_function_corrections, const bool gauge_corrections, const bool yukawa_corrections)
    {
      const complex<double> i(0.0, 1.0);
      const vector<double> Lambda = get_lambdas_from_spectrum(s);

      // ensure that we have a Z2-symmetric scalar sector
      check_Z2(Lambda[6], Lambda[7], "get_NLO_unitarity_LogLikelihood_THDM");

      double b = atan(he.get(Par::dimensionless, "tanb")), a = he.get(Par::dimensionless, "alpha");
      double c2a = cos(2.0 * a), c2b = cos(2.0 * b), s2a = sin(2.0 * a), s2b = sin(2.0 * b);

      // calculate LO beta functions
      const complex<double> b_one = beta_one(he, s, gauge_corrections, yukawa_corrections);
      const complex<double> b_two = beta_two(he, s, gauge_corrections, yukawa_corrections);
      const complex<double> b_three = beta_three(he, s, gauge_corrections, yukawa_corrections);
      const complex<double> b_four = beta_four(he, s, gauge_corrections, yukawa_corrections);
      const complex<double> b_five = beta_five(he, s, gauge_corrections, yukawa_corrections);

      // wavefunction functions
      complex<double> zij_wpwm, zij_zz, zij_Hpwm, zij_Az, zij_hh, zij_HH, zij_hH, zij_Hh, zij_HpHm, zij_AA;
      complex<double> B1_z, B2_z, B3_z, B20_z, B21_z, B22_z;
      if (wave_function_corrections)
      {
        zij_wpwm = z_ij(wpwm, s);
        zij_zz = z_ij(zz, s);
        zij_Hpwm = z_ij(Hpwm, s);
        zij_Az = z_ij(Az, s);
        zij_hh = z_ij(hh, s);
        zij_HH = z_ij(HH, s);
        zij_hH = z_ij(hH, s);
        zij_Hh = z_ij(Hh, s);
        zij_HpHm = z_ij(HpHm, s);
        zij_AA = z_ij(AA, s);
      }

      complex<double> B1 = -3.0 * Lambda[1] + (9.0 / 2.0) * b_one + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (9.0 * pow(Lambda[1], 2) + pow((2.0 * Lambda[3] + Lambda[4]), 2));
      if (wave_function_corrections)
      {
        B1_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + 2.0 * zij_HpHm + zij_HH + 2.0 * zij_wpwm + zij_zz - (zij_HH - zij_hh) * c2a);
        B1_z += 1.0 / (16.0 * pow(M_PI, 2)) * ((2.0 * zij_wpwm - 2.0 * zij_HpHm + zij_zz - zij_AA) * c2b - (zij_Hh + zij_hH) * s2a - (2.0 * zij_Hpwm + zij_Az) * s2b);
        B1 += -3.0 / 2.0 * Lambda[1] * B1_z;
      }

      complex<double> B2 = -3.0 * Lambda[2] + (9.0 / 2.0) * b_two + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (9.0 * pow(Lambda[2], 2) + pow((2.0 * Lambda[3] + Lambda[4]), 2));
      if (wave_function_corrections)
      {
        B2_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + 2.0 * zij_HpHm + zij_HH + 2.0 * zij_wpwm + zij_zz - (zij_HH - zij_hh) * c2a);
        B2_z += 1.0 / (16.0 * pow(M_PI, 2)) * (-(2.0 * zij_wpwm - 2.0 * zij_HpHm + zij_zz - zij_AA) * c2b + (zij_Hh + zij_hH) * s2a + (2.0 * zij_Hpwm + zij_Az) * s2b);
        B2 += -3.0 / 2.0 * Lambda[2] * B2_z;
      }

      complex<double> B3 = -(2.0 * Lambda[3] + Lambda[4]) + (3.0 / 2.0) * (2.0 * b_three + b_four) + 3.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (Lambda[1] + Lambda[2]) * (2.0 * Lambda[3] + Lambda[4]);
      if (wave_function_corrections)
      {
        complex<double> B3_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + 2.0 * zij_HpHm + zij_HH + 2.0 * zij_wpwm + zij_zz);
        B3 += -1.0 / 2.0 * (2.0 * Lambda[3] + Lambda[4]) * B3_z;
      }

      complex<double> B4 = -(Lambda[3] + 2.0 * Lambda[4]) + (3.0 / 2.0) * (b_three + 2.0 * b_four) + (1.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * (pow(Lambda[3], 2) + 4.0 * Lambda[3] * Lambda[4] + 4.0 * pow(Lambda[4], 2) + 9.0 * pow(Lambda[5], 2));
      if (wave_function_corrections)
      {
        B4 += -1.0 / 2.0 * (Lambda[3] + Lambda[4] + Lambda[5]) * B3_z;
      }

      complex<double> B6 = -3.0 * Lambda[5] + (9.0 / 2.0) * b_five + (6.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * (Lambda[3] + 2.0 * Lambda[4]) * Lambda[5];
      if (wave_function_corrections)
      {
        B6 += -1.0 / 2.0 * (Lambda[4] + 2.0 * Lambda[5]) * B3_z;
      }

      complex<double> B7 = -Lambda[1] + (3.0 / 2.0) * b_one + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (pow(Lambda[1], 2) + pow(Lambda[4], 2));
      if (wave_function_corrections)
      {
        B7 += -1.0 / 2.0 * Lambda[1] * B1_z;
      }

      complex<double> B8 = -Lambda[2] + (3.0 / 2.0) * b_two + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (pow(Lambda[2], 2) + pow(Lambda[4], 2));
      if (wave_function_corrections)
      {
        B8 += -1.0 / 2.0 * Lambda[2] * B2_z;
      }

      complex<double> B9 = -Lambda[4] + (3.0 / 2.0) * b_four + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (Lambda[1] + Lambda[2]) * Lambda[4];
      if (wave_function_corrections)
      {
        B9 += -1.0 / 2.0 * Lambda[4] * B3_z;
      }

      complex<double> B13 = -Lambda[3] + (3.0 / 2.0) * b_three + (1.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * (pow(Lambda[3], 2) + pow(Lambda[5], 2));
      if (wave_function_corrections)
      {
        B13 += -1.0 / 2.0 * (Lambda[3] + Lambda[4] + Lambda[5]) * B3_z;
      }

      complex<double> B15 = -Lambda[5] + (3.0 / 2.0) * b_five + (2.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * Lambda[3] * Lambda[5];
      if (wave_function_corrections)
      {
        B15 += -1.0 / 2.0 * (Lambda[4] - 2.0 * Lambda[5]) * B3_z;
      }

      complex<double> B19 = -(Lambda[3] - Lambda[4]) + (3.0 / 2.0) * (b_three - b_four) + (1.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * pow((Lambda[3] - Lambda[4]), 2);
      if (wave_function_corrections)
      {
        B19 += -1.0 / 2.0 * (Lambda[3] - Lambda[5]) * B3_z;
      }

      complex<double> B20 = -Lambda[1] + (3.0 / 2.0) * b_one + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (pow(Lambda[1], 2) + pow(Lambda[5], 2));
      if (wave_function_corrections)
      {
        B20_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + zij_HH + zij_zz + (zij_HH - zij_hh) * c2a + (zij_zz - zij_AA) * c2b - (zij_Hh - zij_hH) * s2a - zij_Az * s2b);
        B20 += -1.0 * Lambda[1] * B20_z;
      }

      complex<double> B21 = -Lambda[2] + (3.0 / 2.0) * b_two + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (pow(Lambda[2], 2) + pow(Lambda[5], 2));
      if (wave_function_corrections)
      {
        B21_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + zij_HH + zij_zz + (zij_HH - zij_hh) * c2a - (zij_zz - zij_AA) * c2b + (zij_Hh - zij_hH) * s2a + zij_Az * s2b);
        B21 += -1.0 * Lambda[2] * B21_z;
      }

      complex<double> B22 = -Lambda[5] + (3.0 / 2.0) * b_five + (1.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * (Lambda[1] + Lambda[2]) * Lambda[5];
      if (wave_function_corrections)
      {
        B22_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + zij_HH + zij_zz);
        B22 += -1.0 * Lambda[5] * B22_z;
      }

      complex<double> B30 = -(Lambda[3] + Lambda[4]) + (3.0 / 2.0) * (b_three + b_four) + (1.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * pow((Lambda[3] + Lambda[4]), 2);
      if (wave_function_corrections)
      {
        B30 += -1.0 * (Lambda[3] + Lambda[4]) * B22_z;
      }

      // eigenvalues
      complex<double> a00_even_plus = 1.0 / (32.0 * M_PI) * ((B1 + B2) + sqrt(pow((B1 - B2), 2) + 4. * pow(B3, 2)));
      complex<double> a00_even_minus = 1.0 / (32.0 * M_PI) * ((B1 + B2) - sqrt(pow((B1 - B2), 2) + 4. * pow(B3, 2)));
      complex<double> a00_odd_plus = 1.0 / (32.0 * M_PI) * (2. * B4 + 2. * B6);
      complex<double> a00_odd_minus = 1.0 / (32.0 * M_PI) * (2. * B4 - 2. * B6);
      complex<double> a01_even_plus = 1.0 / (32.0 * M_PI) * (B7 + B8 + sqrt(pow((B7 - B8), 2) + 4. * pow(B9, 2)));
      complex<double> a01_even_minus = 1.0 / (32.0 * M_PI) * (B7 + B8 - sqrt(pow((B7 - B8), 2) + 4. * pow(B9, 2)));
      complex<double> a01_odd_plus = 1.0 / (32.0 * M_PI) * (2. * B13 + 2. * B15);
      complex<double> a01_odd_minus = 1.0 / (32.0 * M_PI) * (2. * B13 - 2. * B15);
      complex<double> a10_odd = 1.0 / (32.0 * M_PI) * (2. * B19);
      complex<double> a11_even_plus = 1.0 / (32.0 * M_PI) * (B20 + B21 + sqrt(pow((B20 - B21), 2) + 4. * pow(B22, 2)));
      complex<double> a11_even_minus = 1.0 / (32.0 * M_PI) * (B20 + B21 - sqrt(pow((B20 - B21), 2) + 4. * pow(B22, 2)));
      complex<double> a11_odd = 1.0 / (32.0 * M_PI) * (2. * B30);

      vector<complex<double>> result =  {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus,
              a01_even_minus, a01_odd_plus, a01_odd_minus, a10_odd, a11_even_plus, a11_even_minus, a11_odd};

      return result;
    }


    /// =================================
    /// == likelihood function helpers ==
    /// =================================


    // get leading-order scattering eigenvalues (with fixed ordering) (requires Z2-symmetric THDM)
    vector<complex<double>> get_LO_scattering_eigenvalues_ordered(ThdmSpec &s)
    {
      // Note: only compatible with Z-2 aligned models

      vector<double> lambda = get_lambdas_from_spectrum(s);

      // ensure that we have a Z2-symmetric scalar sector
      check_Z2(lambda[6], lambda[7], "get_LO_scattering_eigenvalues_ordered");

      // a00
      complex<double> a00_even_plus = 1.0 / 2.0 * (3.0 * (lambda[1] + lambda[2]) + sqrt(9.0 * pow((lambda[1] - lambda[2]), 2) + 4.0 * pow((2.0 * lambda[3] + lambda[4]), 2)));
      complex<double> a00_even_minus = 1.0 / 2.0 * (3.0 * (lambda[1] + lambda[2]) - sqrt(9.0 * pow((lambda[1] - lambda[2]), 2) + 4.0 * pow((2.0 * lambda[3] + lambda[4]), 2)));
      complex<double> a00_odd_plus = lambda[3] + 2.0 * lambda[4] + 3.0 * lambda[5];
      complex<double> a00_odd_minus = lambda[3] + 2.0 * lambda[4] - 3.0 * lambda[5];
      // a01
      complex<double> a01_even_plus = 1.0 / 2.0 * (lambda[1] + lambda[2] + sqrt(pow((lambda[1] - lambda[2]), 2) + 4.0 * pow(lambda[4], 2)));
      complex<double> a01_even_minus = 1.0 / 2.0 * (lambda[1] + lambda[2] - sqrt(pow((lambda[1] - lambda[2]), 2) + 4.0 * pow(lambda[4], 2)));
      complex<double> a01_odd_plus = lambda[3] + lambda[5];
      complex<double> a01_odd_minus = lambda[3] - lambda[5];
      // a20
      complex<double> a20_odd = lambda[3] - lambda[4];
      // a21
      complex<double> a21_even_plus = 1.0 / 2.0 * (lambda[1] + lambda[2] + sqrt(pow((lambda[1] - lambda[2]), 2) + 4.0 * pow(lambda[5], 2)));
      complex<double> a21_even_minus = 1.0 / 2.0 * (lambda[1] + lambda[2] - sqrt(pow((lambda[1] - lambda[2]), 2) + 4.0 * pow(lambda[5], 2)));
      complex<double> a21_odd = lambda[3] + lambda[4];

      vector<complex<double>> lo_eigenvalues = {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus,
              a01_even_minus, a01_odd_plus, a01_odd_minus, a20_odd, a21_even_plus, a21_even_minus, a21_odd};

      return lo_eigenvalues;
    }

    // get leading-order scattering eigenvalues (with no particular order) (supports GCP 2HDM with lam6,lam7)
    vector<complex<double>> get_LO_scattering_eigenvalues(ThdmSpec &s)
    {
      vector<double> lambda;
      vector<complex<double>> lo_eigenvalues;
      lambda = get_lambdas_from_spectrum(s);

      // Scattering matrix (7a) Y=2 sigma=1
      Eigen::MatrixXcd S_21(3, 3);
      S_21(0, 0) = lambda[1];
      S_21(0, 1) = lambda[5];
      S_21(0, 2) = sqrt(2.0) * lambda[6];

      S_21(1, 0) = std::conj(lambda[5]);
      S_21(1, 1) = lambda[2];
      S_21(1, 2) = sqrt(2.0) * std::conj(lambda[7]);

      S_21(2, 0) = sqrt(2.0) * std::conj(lambda[6]);
      S_21(2, 1) = sqrt(2.0) * lambda[7];
      S_21(2, 2) = lambda[3] + lambda[4];

      Eigen::ComplexEigenSolver<Eigen::MatrixXcd> eigensolver_S_21(S_21);
      Eigen::VectorXcd eigenvalues_S_21 = eigensolver_S_21.eigenvalues();
      lo_eigenvalues.push_back((eigenvalues_S_21(0)));
      lo_eigenvalues.push_back((eigenvalues_S_21(1)));
      lo_eigenvalues.push_back((eigenvalues_S_21(2)));

      // Scattering matrix (7b) Y=2 sigma=0
      complex<double> S_20 = lambda[3] - lambda[4];
      lo_eigenvalues.push_back((S_20));

      // Scattering matrix (7c) Y=0 sigma=1
      Eigen::MatrixXcd S_01(4, 4);
      S_01(0, 0) = lambda[1];
      S_01(0, 1) = lambda[4];
      S_01(0, 2) = lambda[6];
      S_01(0, 3) = std::conj(lambda[6]);

      S_01(1, 0) = lambda[4];
      S_01(1, 1) = lambda[2];
      S_01(1, 2) = lambda[7];
      S_01(1, 3) = std::conj(lambda[7]);

      S_01(2, 0) = std::conj(lambda[6]);
      S_01(2, 1) = std::conj(lambda[7]);
      S_01(2, 2) = lambda[3];
      S_01(2, 3) = lambda[5];

      S_01(3, 0) = lambda[6];
      S_01(3, 1) = lambda[7];
      S_01(3, 2) = lambda[5];
      S_01(3, 3) = lambda[3];

      Eigen::ComplexEigenSolver<Eigen::MatrixXcd> eigensolver_S_01(S_01);
      Eigen::VectorXcd eigenvalues_S_01 = eigensolver_S_01.eigenvalues();
      lo_eigenvalues.push_back((eigenvalues_S_01(0)));
      lo_eigenvalues.push_back((eigenvalues_S_01(1)));
      lo_eigenvalues.push_back((eigenvalues_S_01(2)));
      lo_eigenvalues.push_back((eigenvalues_S_01(3)));

      // Scattering matrix (7d) Y=0 sigma=0
      Eigen::MatrixXcd S_00(4, 4);
      S_00(0, 0) = 3.0 * lambda[1];
      S_00(0, 1) = 2.0 * lambda[3] + lambda[4];
      S_00(0, 2) = 3.0 * lambda[6];
      S_00(0, 3) = 3.0 * std::conj(lambda[6]);

      S_00(1, 0) = 2.0 * lambda[3] + lambda[4];
      S_00(1, 1) = 3.0 * lambda[2];
      S_00(1, 2) = 3.0 * lambda[7];
      S_00(1, 3) = 3.0 * std::conj(lambda[7]);

      S_00(2, 0) = 3.0 * std::conj(lambda[6]);
      S_00(2, 1) = 3.0 * std::conj(lambda[7]);
      S_00(2, 2) = lambda[3] + 2.0 * lambda[4];
      S_00(2, 3) = 3.0 * std::conj(lambda[5]);

      S_00(3, 0) = 3.0 * lambda[6];
      S_00(3, 1) = 3.0 * lambda[7];
      S_00(3, 2) = 3.0 * lambda[5];
      S_00(3, 3) = lambda[3] + 2.0 * lambda[4];

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
      ThdmSpec s(he, ThdmSpec::FILL_GENERIC);

      // get the leading order scattering eigenvalues
      vector<complex<double>> LO_eigenvalues;

      if (s.lam6 == 0 && s.lam7 == 0)
        LO_eigenvalues = get_LO_scattering_eigenvalues_ordered(s);
      else
        LO_eigenvalues = get_LO_scattering_eigenvalues(s);

      // all values < 8*PI for unitarity conditions (see ivanov paper)
      constexpr double unitarity_upper_limit = 8 * M_PI;
      constexpr double sigma = 0.05;

      //calculate the total error of each point
      double error = 0.0;
      for (auto const &eachEig : LO_eigenvalues)
        if (abs(eachEig) > unitarity_upper_limit)
          error += abs(eachEig) - unitarity_upper_limit;

      return Stats::gaussian_upper_limit(error, 0.0, 0.0, sigma, false);
    }

    // next-to-leading-order S-matrix unitarity likelihood
    double get_NLO_unitarity_LogLikelihood(const SubSpectrum& he, const bool check_correction_ratio, const bool wave_function_corrections, const bool gauge_corrections, const bool yukawa_corrections)
    {
      // get required spectrum info
      ThdmSpec s(he, ThdmSpec::FILL_GENERIC | ThdmSpec::FILL_ANGLES | ThdmSpec::FILL_HIGGS | ThdmSpec::FILL_PHYSICAL);

      const complex<double> i(0.0, 1.0);
      vector<complex<double>> NLO_eigenvalues = get_NLO_scattering_eigenvalues(he, s, wave_function_corrections, gauge_corrections, yukawa_corrections);

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
        if (abs(eig - i / 2.0) > unitarity_upper_limit)
        {
          error += abs(eig - i / 2.0) - unitarity_upper_limit;
        }
        // std::cout << nlo_eig_names[counter_nlo] << ": " << eig << " | " << abs(eig - i / 2) << std::endl;
        // counter_nlo++;
      }

      if (check_correction_ratio)
      {
        vector<complex<double>> LO_eigenvalues = get_LO_scattering_eigenvalues_ordered(s);
        // flip order of plus/minus to match conventions
        vector<int> LO_eigenvalue_order = {2, 1, 4, 3, 6, 5, 8, 7, 9, 11, 10, 12};
        for (size_t num = 0; num < LO_eigenvalues.size(); num++)
        {
          // needs to be normalized in accordance to NLO unitarity
          complex<double> LO_eigenvalue = -(LO_eigenvalues[LO_eigenvalue_order[num]]) / (32.0 * M_PI * M_PI);
          // only check for lo eigenvalues larger than 1/16pi as otherwise this may break down
          if (abs(LO_eigenvalue) > 1 / (16.0 * M_PI))
          {
            double ratio = abs(NLO_eigenvalues[num]) / abs(LO_eigenvalue);
            if (ratio >= 1)
            {
              error_ratio += abs(ratio - 1);
            }
          }
        }
      }

      return Stats::gaussian_upper_limit(error*0.7 + error_ratio*0.6, 0.0, 0.0, sigma, false);
    }

    // basic perturbativity likelihood (only checks that lambdas are less than 4pi)
    double get_simple_perturbativity_LogLikelihood(const SubSpectrum& he)
    {
      // get required spectrum info
      ThdmSpec s(he,ThdmSpec::FILL_GENERIC);

      // check lambdai (generic couplings)
      //-----------------------------
      // all values < 4*PI for perturbativity conditions
      const double perturbativity_upper_limit = 4 * M_PI;
      const double sigma = 0.05;
      //-----------------------------
      double error = 0.0;
      vector<double> lambda = get_lambdas_from_spectrum(s);
      // loop over all lambdas
      for (auto const &each_lambda : lambda)
      {
        if (abs(each_lambda) > perturbativity_upper_limit)
          error += abs(each_lambda) - perturbativity_upper_limit;
      }

      return Stats::gaussian_upper_limit(error, 0.0, 0.0, sigma, false);
    }

    // perturbativity likelihood (checks that all quartic couplings are less than 4pi)
    double get_perturbativity_LogLikelihood(const SubSpectrum& he)
    {
      // get required spectrum info
      ThdmSpec s(he,ThdmSpec::FILL_GENERIC | ThdmSpec::FILL_ANGLES | ThdmSpec::FILL_HIGGS | ThdmSpec::FILL_PHYSICAL);

      //-----------------------------
      // all values < 4*PI for perturbativity conditions
      const double perturbativity_upper_limit = 4 * M_PI;
      const double sigma = 0.08;
      //-----------------------------
      double error = 0.0;
      double previous_coupling = 0.0;
      // using generic model so calculate chi^2 from all possible 4 higgs interactions
      complex<double> hhhh_coupling;


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

      return Stats::gaussian_upper_limit(error, 0.0, 0.0, sigma, false);
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
      ThdmSpec s(he,ThdmSpec::FILL_GENERIC | ThdmSpec::FILL_ANGLES | ThdmSpec::FILL_PHYSICAL);

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
      auto k2 = sqrt(complex<double>(lambda1 / lambda2));
      auto k = sqrt(k2);
      const complex<double> discriminant = m12_2 * (m11_2 - k2 * m22_2) * (tb - k);

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

      ThdmSpec s(he, ThdmSpec::FILL_GENERIC | ThdmSpec::FILL_ANGLES | ThdmSpec::FILL_HIGGS | ThdmSpec::FILL_PHYSICAL);

      const double sigma = 0.07;
      double error = 0.;

      error += std::max(0.0, -s.lam1);
      // gamma = pi/2
      error += std::max(0.0, -s.lam2);
      // rho = 0

      // get required spectrum info
      // ThdmSpec s(he,ThdmSpec::FILL_GENERIC);
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

          if (abs(rho) <= 1.0 && gamma >= 0.0 && gamma <= M_PI/2.)
          {
            error += std::max(0.0, -calc);
          }

          // cos(theta) = +-1 AND abs(rho) <= 1 AND 0<gamma<pi/2 (second gamma solution)
          gamma = M_PI-gamma;
          cosg  = cos(gamma);
          rho   = sin(gamma)*(s.lam7-cosg*cosg*s.lam7+s.lam6*cosg*cosg)/(cosg*(-s.lam5-s.lam4+cosg*cosg*s.lam4+cosg*cosg*s.lam5));

          if (abs(rho) <= 1.0 && gamma >= 0.0 && gamma <= M_PI/2.)
          {
            error += std::max(0.0, -calc);
          }

          // a calculation needed for the conditions below
          double calc2 = (1./2.)*(s.lam1*s.lam2*s.lam5-s.lam1*s.lam7*s.lam7-s.lam5*s.lam5*s.lam5+2*s.lam5*s.lam5*s.lam4+2*s.lam5*s.lam5*s.lam3-s.lam5*s.lam4*s.lam4-2*s.lam5*s.lam6*s.lam7-s.lam5*s.lam3*s.lam3-2*s.lam5*s.lam4*s.lam3-s.lam6*s.lam6*s.lam2+2*s.lam6*s.lam7*s.lam3+2*s.lam6*s.lam7*s.lam4)/(s.lam1*s.lam5+2*s.lam6*s.lam7-2*s.lam3*s.lam5+s.lam2*s.lam5-2*s.lam5*s.lam4-s.lam6*s.lam6-s.lam7*s.lam7+2*s.lam5*s.lam5);

          // rho=1 AND abs(ct) <= 1 AND abs(gamma) <= pi/2
          double ct = (1./2.)*(-s.lam6*s.lam3-s.lam6*s.lam4+s.lam6*s.lam2+s.lam5*s.lam6+s.lam7*s.lam1-s.lam7*s.lam3-s.lam7*s.lam4+s.lam7*s.lam5)/sqrt((-s.lam3*s.lam5-s.lam5*s.lam4+s.lam2*s.lam5+s.lam5*s.lam5+s.lam6*s.lam7-s.lam7*s.lam7)*(s.lam1*s.lam5+s.lam6*s.lam7-s.lam3*s.lam5+s.lam5*s.lam5-s.lam5*s.lam4-s.lam6*s.lam6));
          gamma     = atan(sqrt((-s.lam3*s.lam5-s.lam5*s.lam4+s.lam2*s.lam5+s.lam5*s.lam5+s.lam6*s.lam7-s.lam7*s.lam7)*(s.lam1*s.lam5+s.lam6*s.lam7-s.lam3*s.lam5+s.lam5*s.lam5-s.lam5*s.lam4-s.lam6*s.lam6))/(-s.lam3*s.lam5-s.lam5*s.lam4+s.lam2*s.lam5+s.lam5*s.lam5+s.lam6*s.lam7-s.lam7*s.lam7));

          if (abs(ct) <= 1.0 && abs(gamma) <= M_PI/2.)
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

      return Stats::gaussian_upper_limit(error, 0.0, 0.0, sigma, false);
    }

    // loop correction perturbativity constraint on the light scalar, h0
    double get_light_scalar_mass_correction_LogLikelihood(const SubSpectrum& he)
    {
      const double mh_running = he.get(Par::mass1, "h0", 1), mh_pole = he.get(Par::Pole_Mass, "h0", 1);
      const double mh_splitting = abs(mh_pole - mh_running);
      double result = 0.0;

      if (mh_splitting/mh_running > 0.5)
      {
        result += -1e5 * (mh_splitting/mh_running -  0.5);
        // result = -L_MAX;
      }
      return result;
    }

    // loop correction perturbativity constraint on the heavy scalars, H0,A0 & H+/H-
    double get_heavy_scalar_mass_correction_LogLikelihood(const SubSpectrum& he)
    {
      vector<std::string> heavy_scalars = {"h0_2", "A0", "H+"};

      double result = 0.0;

      for (auto& scalar : heavy_scalars)
      {
        double mass_running = he.get(Par::mass1, scalar);
        double mass_pole = he.get(Par::Pole_Mass, scalar);
        double mass_splitting = abs(mass_running - mass_pole);
        if (mass_splitting/mass_running > 0.5)
        {
          result += -1e5 * (mass_splitting/mass_running - 0.5);
          // result = -L_MAX;
        }
      }
      return result;
    }

    // allows the user to enforce upper mass limit on all scalars and lower mass limit on heavy scalars
    double get_scalar_mass_range_LogLikelihood(const SubSpectrum& he, const double min_mass, const double max_mass)
    {
      const double mh0 = he.get(Par::mass1, "h0", 1);
      const double mH0 = he.get(Par::mass1, "h0", 2);
      const double mA0 = he.get(Par::mass1, "A0");
      const double mHp = he.get(Par::mass1, "H+");

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
    double get_worst_LL_of_all_scales(const Spectrum& spec, LL_type LL, bool is_FS_model, double other_scale, std::string calculation_name)
    {
      // we always check the input scale
      vector<double> scales_to_check = { RunScale::INPUT };

      // also check the custom scale from the yaml file
      if (other_scale != RunScale::NONE && other_scale != RunScale::INPUT && is_FS_model)
        scales_to_check.push_back(other_scale);

      // // print warning if we ask for likelihood at check_other_scale but not using FlexibleSUSY model
      // if (other_scale != RunScale::NONE && other_scale != RunScale::INPUT && !is_FS_model)
      // {
      //   std::ostringstream os;
      //   os << "SpecBit warning (non-fatal): requested " << calculation_name << " at all scales. However model in use is incompatible with running to scales. Will revert to regular calculation.";
      //   SpecBit_warning().raise(LOCAL_INFO, os.str());
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

      // normalize to 0
      result = std::min(0.0, result);
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
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale, "LO_unitarity_LogLikelihood_THDM");
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
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale, "NLO_unitarity_LogLikelihood_THDM");
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
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale, "perturbativity_LogLikelihood_THDM");
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
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale, "perturbativity_LogLikelihood_THDM");
    }

    // simple perturbativity constraint on yukawas (soft-cutoff)
    void simple_perturbativity_yukawas_LogLikelihood_THDM(double &result)
    {
      using namespace Pipes::simple_perturbativity_yukawas_LogLikelihood_THDM;
      SMInputs sminputs = *Dep::SMINPUTS;
      const Spectrum spec = *Dep::THDM_spectrum;
      std::unique_ptr<SubSpectrum> he = spec.clone_HE();
      const double sigma = 0.1;
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
        if (abs(each_yukawa) > sqrt(4*M_PI)/(sqrt(1+tanb*tanb)))
          error += abs(each_yukawa) - (sqrt(4*M_PI)/(sqrt(1+tanb*tanb)));
      }
      //Apply softer bound for Yu2tt
      error += abs(Yu2tt) - ((sqrt(4*M_PI)+((sqrt(2)*tanb*mT)/v))/(sqrt(1+tanb*tanb)));
      result = Stats::gaussian_upper_limit(error, 0.0, 0.0, sigma, false);
      result = std::min(0.0, result);
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
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale, "stability_LogLikelihood_THDM");
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
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale, "light_scalar_mass_corrections_LogLikelihood");
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
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale, "heavy_scalar_mass_corrections_LogLikelihood");
    }

    // only keeps points that correspond to hidden higgs scenario (hard-cutoff)
    void hidden_higgs_scenario_LogLikelihood_THDM(double& result)
    {
      using namespace Pipes::hidden_higgs_scenario_LogLikelihood_THDM;
      const bool hidden_higgs_scenario = runOptions->getValueOrDef<bool>(true, "hidden_higgs_scenario");
      const Spectrum& spec = *Dep::THDM_spectrum;

      const double mh_pole = spec.get_HE().get(Par::Pole_Mass, "h0", 1);
      const double mH_pole = spec.get_HE().get(Par::Pole_Mass, "h0", 2);
      constexpr double mh_exp = 125.10; // experimental value of Higgs mass measured by others GeV

      double mass_err_h = std::abs(mh_pole - mh_exp);
      double mass_err_H = std::abs(mH_pole - mh_exp);
      result = 0;

      // we need mass_err_H < mass_err_h for Hidden Higgs scenario

      if (hidden_higgs_scenario && mass_err_h < mass_err_H)
        result = -L_MAX;
      if (!hidden_higgs_scenario && mass_err_h > mass_err_H)
        result = -L_MAX;

      // // weight that pushes mH to 125 Gev
      // result += std::max(0.0, mass_err_H - 10.0) / 1000.0;
      // // weight that pushes mass_err_H < mass_err_h
      // result += std::max(0.0, mass_err_H - mass_err_h) / 20000.0;
      // constexpr double model_invalid_for_lnlike_below = -1e6;
      // result *= model_invalid_for_lnlike_below;

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
      result = get_worst_LL_of_all_scales(spec, LL, is_FS_model, other_scale, "scalar_mass_range_LogLikelihood_THDM");
    }


    /// ==========================
    /// == Higgs coupling table ==
    /// ==========================


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
          double mhi = spec.get(Par::mass1, sHneut[i]); //mass1 to be consistent
          double mhj = spec.get(Par::mass1, sHneut[j]);
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

      // Work out which invisible decays are possible
      //result.invisibles = get_invisibles(spec);
    }

    // helper to get necessary couplings from 2HDMC for higgs couplings table
    void fill_THDM_couplings_struct(THDM_couplings &couplings, THDM_spectrum_container &container)
    {
      // todo: save computational time by filling only those required in each case

      // checks a coupling for NaN
      auto check_coupling = [](const complex<double> coupling)
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
            container.THDM_object->get_coupling_hdd(h, f1, f2, couplings.hdd_cs[h][f1][f2], couplings.hdd_cp[h][f1][f2]);
            container.THDM_object->get_coupling_huu(h, f1, f2, couplings.huu_cs[h][f1][f2], couplings.huu_cp[h][f1][f2]);
            container.THDM_object->get_coupling_hll(h, f1, f2, couplings.hll_cs[h][f1][f2], couplings.hll_cp[h][f1][f2]);
            check_coupling(couplings.hdd_cs[h][f1][f2] + couplings.hdd_cp[h][f1][f2]);
            check_coupling(couplings.huu_cs[h][f1][f2] + couplings.huu_cp[h][f1][f2]);
            check_coupling(couplings.hll_cs[h][f1][f2] + couplings.hll_cp[h][f1][f2]);
          }
        }

        for (int v1 = 1; v1 <= total_number_of_vector_bosons; v1++)
        {
          for (int v2 = 1; v2 <= total_number_of_vector_bosons; v2++)
          {
            container.THDM_object->get_coupling_vvh(v1, v2, h, couplings.vvh[v1][v2][h]);
            check_coupling(couplings.vvh[v1][v2][h]);
          }
          for (int h2 = 1; h2 <= total_number_of_higgs; h2++)
          {
            container.THDM_object->get_coupling_vhh(v1, h, h2, couplings.vhh[v1][h][h2]);
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
      const double vev = spec.get(Par::mass1, "vev");
      const double mW = spec.get(Par::mass1, "W+");
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

      // Determine the type
      THDM_TYPE THDM_type = *Dep::THDM_Type;

      // Initiate 2HDM container
      THDM_spectrum_container container;
      BEreq::init_THDM_spectrum_container_CONV(container, fullspectrum, byVal(THDM_type), 0.0, 0);

      // set up and fill the THDM couplings
      THDM_couplings couplings;
      fill_THDM_couplings_struct(couplings, container);

      // SM-like couplings
      vector<THDM_couplings> couplings_SM_like;
      THDM_couplings SM_couplings;

      // loop over each neutral higgs
      for (int h = 1; h <= NUMBER_OF_NEUTRAL_HIGGS; h++)
      {
        // init an SM like container for each neutral higgs
        BEreq::init_THDM_spectrum_container_CONV(container, fullspectrum, 1, 0.0, byVal(h));
        fill_THDM_couplings_struct(SM_couplings, container);
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
    }

  }
}