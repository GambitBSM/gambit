//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit
///
///  SpecBit module functions related to the
///  2HDM general model, type-I, type-II, lepton specific (X) & flipped (Y) models
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Oct
///
///  *********************************************

// C/C++ headers
#include <string>
#include <ostream>
#include <sstream>
#include <cmath>
#include <complex>
#include <math.h>
#include <iostream>
#include <fstream>

// GAMBIT headers
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Elements/slhaea_helpers.hpp"
#include "gambit/Utils/stream_overloads.hpp" // Just for more convenient output to logger
#include "gambit/Utils/util_macros.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/Models/SimpleSpectra/SMHiggsSimpleSpec.hpp"
#include "gambit/Models/SimpleSpectra/THDMSimpleSpec.hpp"
#include "gambit/Models/SimpleSpectra/THDMSimpleSpecSM.hpp"
#include "gambit/SpecBit/THDMSpec.hpp"
#include "gambit/SpecBit/THDMSpec_basis.hpp"
#include "gambit/SpecBit/model_files_and_boxes.hpp"
#include "gambit/Utils/statistics.hpp"
#include "flexiblesusy/src/spectrum_generator_settings.hpp"
// FlavBit helper routines for likelihood calculations
#include "gambit/FlavBit/FlavBit_types.hpp"
#include "gambit/FlavBit/flav_utils.hpp"
// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/src/ew_input.hpp"
#include "flexiblesusy/src/lowe.h" // From softsusy; used by flexiblesusy
#include "flexiblesusy/src/numerics2.hpp"
#include "flexiblesusy/models/THDM_I/THDM_I_input_parameters.hpp"
#include "flexiblesusy/models/THDM_II/THDM_II_input_parameters.hpp"
#include "flexiblesusy/models/THDM_LS/THDM_LS_input_parameters.hpp"
#include "flexiblesusy/models/THDM_flipped/THDM_flipped_input_parameters.hpp"
#include "flexiblesusy/src/problems.hpp"
#include "gambit/Core/point_counter.hpp"

// Other headers
// GSL
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_permute.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>
// Eigen
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>

// compiler define statements ------
#define L_MAX 1e50 // used to invalidate likelihood
// #define SPECBIT_DEBUG // turn on debug mode
// #define SPECBIT_DEBUG_COUPLINGS // turn on debug mode for coupling calculations
#define FS_THROW_POINT //required s.t. FS does not terminate the scan on invalid point

// other functionality that removes warnings/helps with debugging ------
// hides the fall through warning (case blocks) when necessary, not only on gcc compilers
#if defined(__GNUC__) && __GNUC__ >= 7
#define FALL_THROUGH __attribute__((fallthrough))
#elif defined(__GNUC__)
#define FALL_THROUGH /* fall through */
#else
#define FALL_THROUGH ((void)0)
#endif /* __GNUC__ >= 7 */

#ifdef SPECBIT_DEBUG
// overloading cout to print std::vector for debug
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
  os << " ";
  for (auto const &each_entry : vec)
    os << each_entry << " ";
  return os;
}
#endif


point_counter::time_point point_counter::startTime = std::chrono::high_resolution_clock::now();


namespace Gambit
{
  namespace SpecBit
  {

    // extra namespace declarations
    using namespace LogTags;
    using namespace flexiblesusy;
    namespace ublas = boost::numeric::ublas;

    // --------------------------------------------------
    // declarations for convenience
    enum yukawa_type
    {
      type_I = 1,
      type_II,
      lepton_specific,
      flipped,
      type_III
    };
    enum particle_type
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

    // model lookup map -> useful for looking up model info
    // the keys correspond to model names which may be matched using the ModelInUse GAMBIT function
    struct model_param
    {
      bool is_model_at_Q;
      yukawa_type model_y_type;
      // constructor
      model_param(bool is_model_at_Q_in, yukawa_type model_y_type_in) : is_model_at_Q(is_model_at_Q_in), model_y_type(model_y_type_in) {}
    };

    std::map<std::string, model_param> THDM_model_lookup_map = {
        {"THDMatQ", model_param(true, type_III)},
        {"THDM", model_param(false, type_III)},
        {"THDMIatQ", model_param(true, type_I)},
        {"THDMI", model_param(false, type_I)},
        {"THDMIIatQ", model_param(true, type_II)},
        {"THDMII", model_param(false, type_II)},
        {"THDMLSatQ", model_param(true, lepton_specific)},
        {"THDMLS", model_param(false, lepton_specific)},
        {"THDMflippedatQ", model_param(true, flipped)},
        {"THDMflipped", model_param(false, flipped)}};
    // --------------------------------------------------

    // FlexibleSUSY spectrum
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
    template <class MI>
    Spectrum run_FS_spectrum_generator(const typename MI::InputParameters &input, const SMInputs &sminputs, const Options &runOptions, const std::map<str, safe_ptr<const double>> &input_Param)
    {
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
      settings.set(Spectrum_generator_settings::beta_zero_threshold, runOptions.getValueOrDef<int>(1.000000000e-14, "beta_zero_threshold"));
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
      thdmspec.set_override(Par::mass1, spectrum_generator.get_susy_scale(), "susy_scale", true);
      thdmspec.set_override(Par::mass1, spectrum_generator.get_low_scale(), "low_scale", true);

      if (input_Param.find("TanBeta") != input_Param.end())
      {
        thdmspec.set_override(Par::dimensionless, *input_Param.at("tanb"), "tanbeta(mZ)", true);
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
        if (runOptions.getValueOrDef<bool>(false, "invalid_point_fatal"))
        {
          ///TODO: Need to tell gambit that the spectrum is not viable somehow. For now
          /// just die.
          std::ostringstream errmsg;
          errmsg << "A serious problem was encountered during spectrum generation!; ";
          errmsg << "Message from FlexibleSUSY below:" << std::endl;
          problems.print_problems(errmsg);
          problems.print_warnings(errmsg);
          SpecBit_error().raise(LOCAL_INFO, errmsg.str());
        }
        else
        {
#ifdef FS_THROW_POINT
          std::cout << "SpecBit throwing invalid point" << std::endl;
          std::ostringstream msg;
          /// Apply fast way for now:
          problems.print_problems(msg);
          std::cout << msg.str() << std::endl;
          invalid_point().raise(msg.str()); //TODO: This message isn't ending up in the logs.
#endif
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

    template <class FS_THDM_input_struct>
    void fill_THDM_FS_input(FS_THDM_input_struct &input, const std::map<str, safe_ptr<const double>> &Param)
    {
      // read in THDM model parameters
      input.TanBeta = *Param.at("tanb");
      input.Lambda1IN = *Param.at("lambda_1");
      input.Lambda2IN = *Param.at("lambda_2");
      input.Lambda3IN = *Param.at("lambda_3");
      input.Lambda4IN = *Param.at("lambda_4");
      input.Lambda5IN = *Param.at("lambda_5");
      input.Lambda6IN = *Param.at("lambda_6");
      input.Lambda7IN = *Param.at("lambda_7");
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
    
    // ~~ 13 ~~ (get thdm spectrum)
    /// Get a Spectrum object wrapper for the THDM model
    void get_THDM_spectrum(Spectrum &result)
    {
      namespace myPipe = Pipes::get_THDM_spectrum;
      const SMInputs &sminputs = *myPipe::Dep::SMINPUTS;

      // set THDM model type
      int y_type = -1;
      bool is_at_Q = false;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (myPipe::ModelInUse(THDM_model.first))
        {
          is_at_Q = THDM_model.second.is_model_at_Q;
          y_type = THDM_model.second.model_y_type;
          break;
        }
      }

      if ((y_type < 0) | (y_type > 5))
      {
        // by definition this error should never be raised due to ALLOWED_MODELS protection in rollcall file
        std::ostringstream errmsg;
        errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
        errmsg << "The chosen THDM model was not recognized." << std::endl;
        SpecBit_error().raise(LOCAL_INFO, errmsg.str());
      }
      else if (y_type == 5)
      {
        std::ostringstream errmsg;
        errmsg << "The general THDM is not yet supported by GAMBIT." << std::endl;
        SpecBit_error().raise(LOCAL_INFO, errmsg.str());
      }
      else if (!is_at_Q)
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
        basis["lambda1"] = *myPipe::Param.at("lambda_1"), basis["lambda2"] = *myPipe::Param.at("lambda_2"), basis["lambda3"] = *myPipe::Param.at("lambda_3");
        basis["lambda4"] = *myPipe::Param.at("lambda_4"), basis["lambda5"] = *myPipe::Param.at("lambda_5"), basis["lambda6"] = *myPipe::Param.at("lambda_6");
        basis["lambda7"] = *myPipe::Param.at("lambda_7"), basis["tanb"] = *myPipe::Param.at("tanb"), basis["m12_2"] = *myPipe::Param.at("m12_2");

        // run tree level spectrum generator
        generate_THDM_spectrum_tree_level(basis, sminputs);
#ifdef SPECBIT_DEBUG
        print_THDM_spectrum(basis);
#endif

        // copy any info that will be reused
        const double alpha = basis["alpha"];
        const double tanb = basis["tanb"];

        // fill spectrum container
        thdm_model.tanb = tanb;
        thdm_model.alpha = alpha;
        thdm_model.beta = basis["beta"];

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

        thdm_model.Lambda1 = basis["Lambda1"];
        thdm_model.Lambda2 = basis["Lambda2"];
        thdm_model.Lambda3 = basis["Lambda3"];
        thdm_model.Lambda4 = basis["Lambda4"];
        thdm_model.Lambda5 = basis["Lambda5"];
        thdm_model.Lambda6 = basis["Lambda6"];
        thdm_model.Lambda7 = basis["Lambda7"];
        thdm_model.M11_2 = basis["M11_2"];
        thdm_model.M22_2 = basis["M22_2"];
        thdm_model.M12_2 = basis["M12_2"];

        thdm_model.mh0 = basis["m_h"];
        thdm_model.mH0 = basis["m_H"];
        thdm_model.mA0 = basis["m_A"];
        thdm_model.mC = basis["m_Hp"];

        //for debug reasons may choose to continue with negative mass
        const bool continue_with_negative_mass = false; // ~~ !!!!!!!

        static point_counter count("non-physical mass"); count.count();

        if (basis["m_h"] < 0.0 || basis["m_H"] < 0.0 || basis["m_A"] < 0.0 || basis["m_Hp"] < 0.0)
        {
          count.count_invalid();
          std::ostringstream msg;
          msg << "Negative mass encountered. Point invalidated." << std::endl;
          if (!continue_with_negative_mass)
            invalid_point().raise(msg.str());
        }

        thdm_model.mG0 = 0.0;
        thdm_model.mGC = 0.0;

        // quantities needed to fill container spectrum, intermediate calculations
        const double alpha_em = 1.0 / sminputs.alphainv, C_calc = alpha_em * pi / (sminputs.GF * pow(2, 0.5));
        const double sinW2 = 0.5 - pow(0.25 - C_calc / pow(sminputs.mZ, 2), 0.5), cosW2 = 0.5 + pow(0.25 - C_calc / pow(sminputs.mZ, 2), 0.5);
        const double e = pow(4 * pi * (alpha_em), 0.5), v2 = 1.0 / (sqrt(2.0) * sminputs.GF), vev = sqrt(v2);

        // Standard model
        thdm_model.sinW2 = sinW2;
        // gauge couplings
        thdm_model.g1 = e / sinW2;
        thdm_model.g2 = e / cosW2;
        thdm_model.g3 = pow(4 * pi * (sminputs.alphaS), 0.5);
        thdm_model.mW = sminputs.mZ * cosW2;
        // Yukawas
        const double sqrt2v = pow(2.0, 0.5) / vev, b = atan(tanb);
        const double cb = cos(b), sb = sin(b);
        // set Yukawa scalign based on type
        double beta_scaling_u = sb, beta_scaling_d = sb, beta_scaling_e = sb;
        switch (y_type)
        {
        case type_I:
          break;
        case type_II:
          beta_scaling_d = cb;
          beta_scaling_e = cb;
          break;
        case lepton_specific:
          beta_scaling_e = cb;
          break;
        case flipped:
          beta_scaling_d = cb;
          break;
        }
        // set Yukawas
        thdm_model.Yu[0] = sqrt2v * sminputs.mU / beta_scaling_u;
        thdm_model.Yu[1] = sqrt2v * sminputs.mCmC / beta_scaling_u;
        thdm_model.Yu[2] = sqrt2v * sminputs.mT / beta_scaling_u;
        thdm_model.Ye[0] = sqrt2v * sminputs.mE / beta_scaling_e;
        thdm_model.Ye[1] = sqrt2v * sminputs.mMu / beta_scaling_e;
        thdm_model.Ye[2] = sqrt2v * sminputs.mTau / beta_scaling_e;
        thdm_model.Yd[0] = sqrt2v * sminputs.mD / beta_scaling_d;
        thdm_model.Yd[1] = sqrt2v * sminputs.mS / beta_scaling_d;
        thdm_model.Yd[2] = sqrt2v * sminputs.mBmB / beta_scaling_d;
        thdm_model.yukawaCoupling = y_type;
        thdm_model.vev = vev;

        // Create a SubSpectrum object to wrap the EW sector information
        Models::THDMSimpleSpecSM thdm_spec(thdm_model);
        // Create full Spectrum object from components above
        // Note: SubSpectrum objects cannot be copied, but Spectrum
        // objects can due to a special copy constructor which does
        // the required cloning of the constituent SubSpectra.
        static Spectrum full_spectrum;
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
        static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
        static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

        full_spectrum = Spectrum(qedqcdspec, thdm_spec, sminputs, &myPipe::Param, mass_cut, mass_ratio_cut);
        result = full_spectrum;
      }
      else
      {
        // check perturbativity if key exists in yaml
        if (myPipe::runOptions->getValueOrDef<bool>(false, "check_perturbativity"))
        {
          bool is_perturbative = true;
          std::vector<std::string> lambda_keys = {"lambda_1", "lambda_2", "lambda_3", "lambda_4",
                                                  "lambda_5", "lambda_6", "lambda_7"};
          for (auto const &each_lambda : lambda_keys)
          {
            if (*myPipe::Param.at(each_lambda) > 4. * M_PI)
            {
              is_perturbative = false;
              break;
            }
          }
          if (!is_perturbative)
            invalid_point().raise("FS Invalid Point: Perturbativity Failed");
        }
        using namespace softsusy;
        switch (y_type)
        {
        case type_I:
        {
#if (FS_MODEL_THDM_I_IS_BUILT)
          THDM_I_input_parameters input;
          fill_THDM_FS_input(input, myPipe::Param);
          result = run_FS_spectrum_generator<THDM_I_interface<ALGORITHM1>>(input, sminputs, *myPipe::runOptions, myPipe::Param);
          if (myPipe::runOptions->getValueOrDef<bool>(false, "at_QrunTo"))
          {
            double const scale = *myPipe::Param.at("QrunTo");
            std::cout << "Running spectrum to " << scale << " GeV." << std::endl;
            result.RunBothToScale(scale);
          }
#else
          std::ostringstream errmsg;
          errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
          errmsg << "FS models for THDM_I not built." << std::endl;
          SpecBit_error().raise(LOCAL_INFO, errmsg.str());
#endif
          break;
        }
        case type_II:
        {
#if (FS_MODEL_THDM_II_IS_BUILT)
          THDM_II_input_parameters input;
          fill_THDM_FS_input(input, myPipe::Param);
          result = run_FS_spectrum_generator<THDM_II_interface<ALGORITHM1>>(input, sminputs, *myPipe::runOptions, myPipe::Param);
          if (myPipe::runOptions->getValueOrDef<bool>(false, "at_QrunTo"))
          {
            double const scale = *myPipe::Param.at("QrunTo");
            std::cout << "Running spectrum to " << scale << " GeV." << std::endl;
            result.RunBothToScale(scale);
          }
#else
          std::ostringstream errmsg;
          errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
          errmsg << "FS models for THDM_II not built." << std::endl;
          SpecBit_error().raise(LOCAL_INFO, errmsg.str());
#endif
          break;
        }
        case lepton_specific:
        {
#if (FS_MODEL_THDM_LS_IS_BUILT)
          THDM_LS_input_parameters input;
          fill_THDM_FS_input(input, myPipe::Param);
          result = run_FS_spectrum_generator<THDM_LS_interface<ALGORITHM1>>(input, sminputs, *myPipe::runOptions, myPipe::Param);
          if (myPipe::runOptions->getValueOrDef<bool>(false, "at_QrunTo"))
          {
            double const scale = *myPipe::Param.at("QrunTo");
            std::cout << "Running spectrum to " << scale << " GeV." << std::endl;
            result.RunBothToScale(scale);
          }
#else
          std::ostringstream errmsg;
          errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
          errmsg << "FS models for THDM_LS not built." << std::endl;
          SpecBit_error().raise(LOCAL_INFO, errmsg.str());
#endif
          break;
        }
        case flipped:
        {
#if (FS_MODEL_THDM_flipped_IS_BUILT)
          THDM_flipped_input_parameters input;
          fill_THDM_FS_input(input, myPipe::Param);
          result = run_FS_spectrum_generator<THDM_flipped_interface<ALGORITHM1>>(input, sminputs, *myPipe::runOptions, myPipe::Param);
          if (myPipe::runOptions->getValueOrDef<bool>(false, "at_QrunTo"))
          {
            double const scale = *myPipe::Param.at("QrunTo");
            std::cout << "Running spectrum to " << scale << " GeV." << std::endl;
            result.RunBothToScale(scale);
          }
#else
          std::ostringstream errmsg;
          errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
          errmsg << "FS models for THDM_flipped not built." << std::endl;
          SpecBit_error().raise(LOCAL_INFO, errmsg.str());
#endif
          break;
        }
        default:
        {
          // this error should never be raised due to previous check of y_type
          std::ostringstream errmsg;
          errmsg << "A fatal problem was encountered during spectrum generation." << std::endl;
          errmsg << "Tried to set the Yukawa Type to " << y_type << " . Yukawa Type should be 1-4." << std::endl;
          SpecBit_error().raise(LOCAL_INFO, errmsg.str());
          break;
        }
        }
      }
    }




    /// @{ helper functions to unwrap parameters from the spectrum and help with calculations
    //  ============================================================

    // get the VEV from a container (from the spectrum within)
    double get_v(THDM_spectrum_container &container)
    {
      return container.he->get(Par::mass1, "vev");
    }

    // helper function to get the vev squared
    double get_v2(THDM_spectrum_container &container)
    {
      return pow(get_v(container), 2);
    }

    // fills a template struct that includes physical basis parameters form the spectrum conatainer
    template <class T>
    void fill_physical_basis(T &input, THDM_spectrum_container &container)
    {
      input.mh = container.he->get(Par::mass1, "h0", 1);
      input.mH = container.he->get(Par::mass1, "h0", 2);
      input.mA = container.he->get(Par::mass1, "A0");
      input.mC = container.he->get(Par::mass1, "H+");
      input.mG = container.he->get(Par::mass1, "G0");
      input.mGC = container.he->get(Par::mass1, "G+");
      input.alpha = container.he->get(Par::dimensionless, "alpha");
      input.beta = container.he->get(Par::dimensionless, "beta");
      input.m122 = container.he->get(Par::mass1, "m12_2");
    }

    // helper function to fill from physical basis within a container from the spectrum in the container itself
    physical_basis_input fill_physical_basis_input(THDM_spectrum_container &container)
    {
      physical_basis_input input;
      fill_physical_basis(input, container);
      return input;
    }

    // fills a vector with lambas from the spectrum object
    std::vector<double> get_lambdas_from_spectrum(THDM_spectrum_container &container)
    {
      std::vector<double> Lambda(8);
      Lambda[1] = container.he->get(Par::mass1, "lambda_1");
      Lambda[2] = container.he->get(Par::mass1, "lambda_2");
      Lambda[3] = container.he->get(Par::mass1, "lambda_3");
      Lambda[4] = container.he->get(Par::mass1, "lambda_4");
      Lambda[5] = container.he->get(Par::mass1, "lambda_5");
      Lambda[6] = container.he->get(Par::mass1, "lambda_6");
      Lambda[7] = container.he->get(Par::mass1, "lambda_7");
      return Lambda;
    }

    // return factorial of n
    int factorial(int n)
    {
      if (n == 0)
        return 1;
      else
        return factorial(n - 1) * n;
    }

    // returns the symmetry factor for a set of particels
    int get_symmetry_factor(std::vector<int> n_identical_particles)
    {
      int symm_factor = 1;
      for (const auto &n_identical : n_identical_particles)
      {
        symm_factor *= factorial(n_identical);
      }
      return symm_factor;
    }

    // gets the sign of the input
    // https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
    template <typename T>
    int sgn(T input)
    {
      return (T(0) < input) - (input < T(0));
    }

    // returns Class I q_ij matrix based upon Higgs basis
    std::vector<std::vector<std::complex<double>>> get_qij(const double ba, const double Lam6)
    {
      const double sba = sin(ba), cba = abs(cos(ba));
      const std::complex<double> i(0.0, 1.0);
      std::vector<std::vector<std::complex<double>>> q = {{0.0, 0.0, 0.0}, {0.0, sba, (double)sgn(Lam6) * cba}, {0.0, -(double)sgn(Lam6) * cba, sba}, {0.0, 0.0, i}, {0.0, i, 0.0}};
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
    std::vector<std::vector<particle_type>> get_neutral_particle_permutations(std::vector<particle_type> particles)
    {
      int neutral_index = 0, neutral_index_identical = 0, identical_counter = 0;
      std::vector<std::vector<particle_type>> particle_permutations;
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
      std::vector<int> identical_particles;
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
    bool particles_match(std::vector<particle_type> particles, std::vector<particle_type> test_particles)
    {
      return particles == test_particles;
    }

    // checks that our model is Z2 symmetric
    int check_Z2(const double lambda6, const double lambda7, const std::string calculation_name)
    {
      if (lambda6 != 0.0 || lambda7 != 0.0)
      {
        std::ostringstream msg;
        msg << "SpecBit warning (non-fatal): " << calculation_name << " is only compatible with Z2 conserving models. \
        This calculation will terminate and return zero."
            << std::endl;
        SpecBit_warning().raise(LOCAL_INFO, msg.str());
        std::cerr << msg.str();
        return false;
      }
      return true;
    }

    // prints scale warning if needed
    void print_calculation_at_scale_warning(const std::string calculation_name)
    {
      std::cerr << "SpecBit warning (non-fatal): requested " << calculation_name << " at all scales. However model in use is incompatible with running to scales. Will revert to regular calculation." << std::endl;
    }

    // checks a coupling for NaN
    void check_coupling(std::complex<double> var)
    {
      static point_counter count("NaN coupling"); count.count();

      // ~~ !!!!!!!!!!
      if (std::isnan(var.real()) || std::isnan(var.imag()))
      {
        count.count_invalid();
        std::ostringstream msg;
        msg << "SpecBit warning (non-fatal) a coupling has evaluated to NaN." << std::endl;
        SpecBit_warning().raise(LOCAL_INFO, msg.str());
        std::cerr << msg.str();
      }
    }
    /// @} end helpers

    /// @{ Higgs couplings calculated using both physical & Higgs bases
    //  ============================================================

    /// Higgs couplings calculated using the Higgs basis (see arXiv:hep-ph/0602242)
    //  ------------------------------------------------------------

    // hhh coupling using Higgs basis
    std::complex<double> get_cubic_coupling_higgs_hhh(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, std::vector<particle_type> particles)
    {
      const particle_type j = particles[0], k = particles[1], l = particles[2];

      const double Lam1 = container.he->get(Par::mass1,"Lambda_1"), Lam34 = container.he->get(Par::mass1,"Lambda_3") + container.he->get(Par::mass1,"Lambda_4");
      const double Lam5 = container.he->get(Par::mass1,"Lambda_5"), Lam6 = container.he->get(Par::mass1,"Lambda_6"), Lam7 = container.he->get(Par::mass1,"Lambda_7");
      std::complex<double> c(0.0, 0.0);

      c += q[j][1] * std::conj(q[k][1]) * (q[l][1]).real() * Lam1;
      c += q[j][2] * std::conj(q[k][2]) * (q[l][1]).real() * Lam34;
      c += (std::conj(q[j][1]) * q[k][2] * q[l][2] * Lam5).real();
      c += ((2.0 * q[j][1] + std::conj(q[j][1])) * std::conj(q[k][1]) * q[l][2] * Lam6 * (double)sgn(Lam6)).real();
      c += (std::conj(q[j][2]) * q[k][2] * q[l][2] * Lam7 * (double)sgn(Lam6)).real();
      c *= 0.5 * get_v(container);
      return c;
    }

    // hH+H- coupling
    std::complex<double> get_cubic_coupling_higgs_hHpHm(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, particle_type k)
    {
      return get_v(container) * ((q[k][1]).real() * container.he->get(Par::mass1,"Lambda_3") + (q[k][2] * (double)sgn(container.he->get(Par::mass1,"Lambda_6")) * container.he->get(Par::mass1,"Lambda_7")).real());
    }

    // hG+G- coupling
    std::complex<double> get_cubic_coupling_higgs_hGpGm(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, particle_type k)
    {
      double Lambda6 = container.he->get(Par::mass1,"Lambda_6");
      return get_v(container) * ((q[k][1]).real() * container.he->get(Par::mass1,"Lambda_1") + (q[k][2] * (double)sgn(Lambda6) * Lambda6).real());
    }

    // hG-H+ coupling
    std::complex<double> get_cubic_coupling_higgs_hGmHp(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, particle_type k)
    {
      double Lambda6 = container.he->get(Par::mass1,"Lambda_6");
      return get_v(container) * 0.5 * (double)sgn(Lambda6) * (std::conj(q[k][2]) * container.he->get(Par::mass1,"Lambda_4") + q[k][2] * container.he->get(Par::mass1,"Lambda_5") + 2.0 * (q[k][1]).real() * Lambda6 * (double)sgn(Lambda6));
    }

    // hhG0 coupling
    std::complex<double> get_cubic_coupling_higgs_hhG0(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, std::vector<particle_type> particles)
    {
      const particle_type k = particles[0], l = particles[1];
      double Lambda6 = container.he->get(Par::mass1,"Lambda_6");
      return get_v(container) * 0.5 * ((q[k][2] * q[l][2] * container.he->get(Par::mass1,"Lambda_5")).imag() + 2.0 * q[k][1] * (q[l][2] * Lambda6 * (double)sgn(Lambda6)).imag());
    }

    // hG0G0 coupling
    std::complex<double> get_cubic_coupling_higgs_hG0G0(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, particle_type k)
    {
      double Lambda6 = container.he->get(Par::mass1,"Lambda_6");
      return 0.5 * get_v(container) * (q[k][1] * container.he->get(Par::mass1,"Lambda_1") + (q[k][2] * Lambda6 * (double)sgn(Lambda6)).real());
    }

    // hhhh coupling
    std::complex<double> get_quartic_coupling_higgs_hhhh(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, std::vector<particle_type> particles)
    {
      const particle_type j = particles[0], k = particles[1], l = particles[2], m = particles[3];
      const double Lam1 = container.he->get(Par::mass1,"Lambda_1"), Lam2 = container.he->get(Par::mass1,"Lambda_2"), Lam34 = container.he->get(Par::mass1,"Lambda_3") + container.he->get(Par::mass1,"Lambda_4");
      const double Lam5 = container.he->get(Par::mass1,"Lambda_5"), Lam6 = container.he->get(Par::mass1,"Lambda_6"), Lam7 = container.he->get(Par::mass1,"Lambda_7");
      std::complex<double> c(0.0, 0.0);

      c += q[j][1] * q[k][1] * std::conj(q[l][1]) * std::conj(q[m][1]) * Lam1;
      c += q[j][2] * q[k][2] * std::conj(q[l][2]) * std::conj(q[m][2]) * Lam2;
      c += 2.0 * q[j][1] * std::conj(q[k][1]) * q[l][2] * std::conj(q[m][2]) * Lam34;
      c += 2.0 * (std::conj(q[j][1]) * std::conj(q[k][1]) * q[l][2] * q[m][2] * Lam5).real();
      c += 4.0 * (q[j][1] * std::conj(q[k][1]) * std::conj(q[l][1]) * q[m][2] * Lam6 * (double)sgn(Lam6)).real();
      c += 4.0 * (std::conj(q[j][1]) * q[k][2] * q[l][2] * std::conj(q[m][2]) * Lam7 * (double)sgn(Lam6)).real();
      return 0.125 * c;
    }

    // hhG+G- coupling
    std::complex<double> get_quartic_coupling_higgs_hhGpGm(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, std::vector<particle_type> particles)
    {
      const particle_type j = particles[0], k = particles[1];
      const double Lambda6 = container.he->get(Par::mass1,"Lambda_6");
      return 0.5 * (q[j][1] * std::conj(q[k][1]) * container.he->get(Par::mass1,"Lambda_1") + q[j][2] * std::conj(q[k][2]) * container.he->get(Par::mass1,"Lambda_3") + 2.0 * (q[j][1] * q[k][2] * Lambda6 * (double)sgn(Lambda6)).real());
    }

    // hhH+H- coupling
    std::complex<double> get_quartic_coupling_higgs_hhHpHm(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, std::vector<particle_type> particles)
    {
      const particle_type j = particles[0], k = particles[1];
      return 0.5 * (q[j][2] * std::conj(q[k][2]) * container.he->get(Par::mass1,"Lambda_2") + q[j][1] * std::conj(q[k][1]) * container.he->get(Par::mass1,"Lambda_3") + 2.0 * (q[j][1] * q[k][2] * container.he->get(Par::mass1,"Lambda_7") * (double)sgn(container.he->get(Par::mass1,"Lambda_6"))).real());
    }

    // hhG+H- coupling
    std::complex<double> get_quartic_coupling_higgs_hhGmHp(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, std::vector<particle_type> particles)
    {
      const particle_type j = particles[0], k = particles[1];
      const double Lam4 = container.he->get(Par::mass1,"Lambda_4"), Lam5 = container.he->get(Par::mass1,"Lambda_5"), Lam6 = container.he->get(Par::mass1,"Lambda_6"), Lam7 = container.he->get(Par::mass1,"Lambda_7");
      std::complex<double> c(0.0, 0.0);
      c += (double)sgn(Lam6) * q[j][1] * std::conj(q[k][2]) * Lam4;
      c += std::conj(q[j][1]) * q[k][2] * Lam5;
      c += q[j][1] * std::conj(q[k][1]) * Lam6 * (double)sgn(Lam6);
      c += q[j][2] * std::conj(q[k][2]) * Lam7 * (double)sgn(Lam6);
      return 0.5 * c;
    }

    // hG0G0G0 coupling
    std::complex<double> get_quartic_coupling_higgs_hG0G0G0(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, particle_type m)
    {
      const double Lam6 = container.he->get(Par::mass1,"Lambda_6");
      return 0.5 * (q[m][2] * Lam6 * (double)sgn(Lam6)).imag();
    }

    // hhG0G0 coupling
    std::complex<double> get_quartic_coupling_higgs_hhG0G0(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, std::vector<particle_type> particles)
    {
      const particle_type l = particles[0], m = particles[1];
      const double Lam6 = container.he->get(Par::mass1,"Lambda_6");
      std::complex<double> c(0.0, 0.0);
      c = (q[l][1] * q[m][1] * container.he->get(Par::mass1,"Lambda_1") + q[l][2] * std::conj(q[m][2]) * (container.he->get(Par::mass1,"Lambda_3") + container.he->get(Par::mass1,"Lambda_4")));
      c += -(q[l][2] * q[m][2] * container.he->get(Par::mass1,"Lambda_5")).real() + 2.0 * q[l][1] * (q[m][2] * Lam6 * (double)sgn(Lam6)).real();
      return 0.25 * c;
    }

    // hhhG0 coupling
    std::complex<double> get_quartic_coupling_higgs_hhhG0(THDM_spectrum_container &container, std::vector<std::vector<std::complex<double>>> q, std::vector<particle_type> particles)
    {
      const particle_type k = particles[1], l = particles[1], m = particles[2];
      const double Lam6 = container.he->get(Par::mass1,"Lambda_6");
      std::complex<double> c(0.0, 0.0);
      c = q[k][1] * (q[l][2] * q[m][2] * container.he->get(Par::mass1,"Lambda_5")).real() + q[k][1] * q[l][1] * (q[m][2] * Lam6 * (double)sgn(Lam6)).real();
      c += (q[k][2] * q[l][2] * std::conj(q[m][2]) * container.he->get(Par::mass1,"Lambda_7") * (double)sgn(Lam6)).real();
      return 0.5 * c;
    }

    // main function to get cubic higgs coupling
    std::complex<double> get_cubic_coupling_higgs(THDM_spectrum_container &container, particle_type p1, particle_type p2, particle_type p3)
    {
      std::complex<double> c(0.0, 0.0);
      const std::complex<double> i(0.0, 1.0);
      const double ba = container.he->get(Par::dimensionless, "beta") - container.he->get(Par::dimensionless, "alpha");
      const double Lam6 = container.he->get(Par::mass1,"Lambda_6");
      const std::vector<std::vector<std::complex<double>>> q = get_qij(ba, Lam6);

      std::vector<particle_type> particles = {p1, p2, p3};
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
            c += get_cubic_coupling_higgs_hG0G0(container, q, p1);
          else if (particles_match(particles, {p1, p2, G0}))
            c += get_cubic_coupling_higgs_hhG0(container, q, particles_perm);
          else
            c += get_cubic_coupling_higgs_hhh(container, q, particles_perm);
        }
      }
      else if (is_neutral(p1) && !is_neutral(p2) && !is_neutral(p3))
      {
        if (particles_match(particles, {p1, Hp, Hm}))
          c += get_cubic_coupling_higgs_hHpHm(container, q, p1);
        else if (particles_match(particles, {p1, Gp, Gm}))
          c += get_cubic_coupling_higgs_hGpGm(container, q, p1);
        else if (particles_match(particles, {p1, Hp, Gm}))
          c += get_cubic_coupling_higgs_hGmHp(container, q, p1);
        else if (particles_match(particles, {p1, Hm, Gp}))
          c += std::conj(get_cubic_coupling_higgs_hGmHp(container, q, p1));
      }

      return -i * c * (double)sign;
    }

    // main function to get quartic higgs couplings
    std::complex<double> get_quartic_coupling_higgs(THDM_spectrum_container &container, particle_type p1, particle_type p2, particle_type p3, particle_type p4)
    {
      std::complex<double> c(0.0, 0.0);
      const std::complex<double> i(0.0, 1.0);
      const double ba = container.he->get(Par::dimensionless, "beta") - container.he->get(Par::dimensionless, "alpha");
      const double Lam1 = container.he->get(Par::mass1,"Lambda_4"), Lam2 = container.he->get(Par::mass1,"Lambda_2"), Lam3 = container.he->get(Par::mass1,"Lambda_3");
      const double Lam4 = container.he->get(Par::mass1,"Lambda_4"), Lam5 = container.he->get(Par::mass1,"Lambda_5"), Lam6 = container.he->get(Par::mass1,"Lambda_6"), Lam7 = container.he->get(Par::mass1,"Lambda_7");
      const std::vector<std::vector<std::complex<double>>> q = get_qij(ba, Lam6);

      std::vector<particle_type> particles = {p1, p2, p3, p4};
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
            c += get_quartic_coupling_higgs_hG0G0G0(container, q, p1);
          else if (particles_match(particles, {p1, p2, G0, G0}))
            c += get_quartic_coupling_higgs_hhG0G0(container, q, particles_perm);
          else if (particles_match(particles, {p1, p2, p3, G0}))
            c += get_quartic_coupling_higgs_hhhG0(container, q, particles_perm);
          else
            c += get_quartic_coupling_higgs_hhhh(container, q, particles_perm);
        }
        else if (is_neutral(p1) && is_neutral(p2) && !is_neutral(p3) && !is_neutral(p4))
        {
          if (particles_match(particles, {G0, G0, Hp, Hm}))
            c += 0.5 * Lam3;
          else if (particles_match(particles, {p1, G0, Hp, Hm}))
            c += -(q[p1][2] * Lam7 * (double)sgn(Lam6)).imag();
          else if (particles_match(particles, {p1, p2, Hp, Hm}))
            c += get_quartic_coupling_higgs_hhHpHm(container, q, particles_perm);
          else if (particles_match(particles, {p1, p2, Gp, Gm}))
            c += get_quartic_coupling_higgs_hhGpGm(container, q, particles_perm);
          else if (particles_match(particles, {p1, p2, Hp, Gm}))
            c += get_quartic_coupling_higgs_hhGmHp(container, q, particles_perm);
          else if (particles_match(particles, {p1, p2, Hm, Gp}))
            c += std::conj(get_quartic_coupling_higgs_hhGmHp(container, q, particles_perm));
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

    /// Higgs couplings calculated using the physical basis
    //  ------------------------------------------------------------

    // h0G+G- coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_h0GpGm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mh = input_pars.mh;
      const double mh2 = pow(mh, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a);
      const double v = get_v(container);
      return 1.0 / v * (-1.0 * mh2 * sba);
    }

    // H0G+G- coupling using physical basiss
    std::complex<double> get_cubic_coupling_physical_H0GpGm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mH = input_pars.mH;
      const double mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double cba = (cos(b - a));
      const double v = get_v(container);
      return 1.0 / v * (-1.0 * mH2 * cba);
    }

    // h0G+H- coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_h0GpHm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mh = input_pars.mh, mC = input_pars.mC;
      const double mh2 = pow(mh, 2), mC2 = pow(mC, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double cba = (cos(b - a));
      const double v = get_v(container);
      return 1.0 / v * (-1.0 * (mh2 - mC2) * cba);
    }

    // h0G0A0 coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_h0G0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mh = input_pars.mh, mA = input_pars.mA;
      const double mh2 = pow(mh, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double cba = (cos(b - a));
      const double v = get_v(container);
      return 1.0 / v * (-1.0 * (mh2 - mA2) * cba);
    }

    // H0G+H- coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_H0GpHm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mH = input_pars.mH, mC = input_pars.mC;
      const double mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a);
      const double v = get_v(container);
      return 1.0 / v * (1.0 * (mH2 - mC2) * sba);
    }

    // H0G0A0 coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_H0G0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mH = input_pars.mH, mA = input_pars.mA;
      const double mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a);
      const double v = get_v(container);
      return 1.0 / v * (1.0 * (mH2 - mA2) * sba);
    }

    // A0G+H- coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_A0GpHm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const std::complex<double> i(0.0, 1.0);
      const double mA = input_pars.mA, mC = input_pars.mC;
      const double mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const double v = get_v(container);
      return 1.0 / v * (-1.0 * i * (mA2 - mC2));
    }

    // h0H+H- coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_h0HpHm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mh = input_pars.mh, mC = input_pars.mC, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mC2 = pow(mC, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), cbap = cos(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = get_v(container);
      return 1.0 / v * (sbinv * cbinv * (m122 * cbap * sbinv * cbinv - mh2 * c2b * cba) - (mh2 + 2.0 * mC2) * sba);
    }

    // h0A0A0 coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_h0A0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mh = input_pars.mh, mA = input_pars.mA, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), cbap = cos(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = get_v(container);
      return 1.0 / v * (sbinv * cbinv * (m122 * cbap * sbinv * cbinv - mh2 * c2b * cba) - (mh2 + 2.0 * mA2) * sba);
    }

    // H0H+H- coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_H0HpHm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mH = input_pars.mH, mC = input_pars.mC, m122 = input_pars.m122;
      const double mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), sbap = sin(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = get_v(container);
      return 1.0 / v * (sbinv * cbinv * (m122 * sbap * sbinv * cbinv + mH2 * c2b * sba) - (mH2 + 2.0 * mC2) * cba);
    }

    // H0A0A0 coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_H0A0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mH = input_pars.mH, mA = input_pars.mA, m122 = input_pars.m122;
      const double mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), sbap = sin(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = get_v(container);
      return 1.0 / v * (sbinv * cbinv * (m122 * sbap * sbinv * cbinv + mH2 * c2b * sba) - (mH2 + 2.0 * mA2) * cba);
    }

    // h0h0h0 coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_h0h0h0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mh = input_pars.mh, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), cbap = cos(b + a);
      const double cba2 = pow(cba, 2);
      const double s2b = sin(2.0 * b);
      const double v = get_v(container);
      return 3.0 / (4.0 * v * s2b * s2b) * (16.0 * m122 * cbap * cba2 - mh2 * (3.0 * sin(3.0 * b + a) + 3.0 * sba + sin(3.0 * b - 3.0 * a) + sin(b + 3.0 * a)));
    }

    // h0h0H0 coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_h0h0H0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mh = input_pars.mh, mH = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double cba = (cos(b - a));
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v = get_v(container);
      return -cba / (s2b * v) * (2.0 * m122 + (mH2 + 2.0 * mh2 - 3.0 * m122 * sbinv * cbinv) * s2a);
    }

    // h0H0H0 coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_h0H0H0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mh = input_pars.mh, mH = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v = get_v(container);
      return sba / (s2b * v) * (-2.0 * m122 + (mh2 + 2.0 * mH2 - 3.0 * m122 * sbinv * cbinv) * s2a);
    }

    // H0H0H0 coupling using physical basis
    std::complex<double> get_cubic_coupling_physical_H0H0H0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      const double mH = input_pars.mH, m122 = input_pars.m122;
      const double mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), sbap = sin(b + a);
      const double sba2 = pow(sba, 2);
      const double s2b = sin(2.0 * b);
      const double v = get_v(container);
      return 3.0 / (4.0 * v * s2b * s2b) * (16.0 * m122 * sbap * sba2 + mH2 * (3.0 * cos(3.0 * b + a) - 3.0 * cba + cos(3.0 * b - 3.0 * a) - cos(b + 3.0 * a)));
    }

    // h0h0G0G0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_h0h0G0G0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mA = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double t2binv = 1.0 / (tan(2.0 * b));
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = -1.0 / v2 * (mH2 * pow(cba, 4) + 2.0 * (mh2 - mH2) * pow(cba, 3) * sba * t2binv + mh2 * pow(sba, 4));
      coupling += -1.0 / v2 * cba2 * (2.0 * mA2 - 2.0 * m122 * sbinv * cbinv + (3.0 * mh2 - mH2) * sba2);
      return coupling;
    }

    // h0h0G0G0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_HpHmG0G0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mA = input_pars.mA, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double t2binv = 1.0 / (tan(2.0 * b)), sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = -1.0 / v2 * (mH2 * pow(cba, 4) + 2.0 * (mh2 - mH2) * pow(sba, 3) * cba * t2binv + mh2 * pow(sba, 4));
      coupling += -1.0 / v2 * sba2 * (2.0 * mA2 - 2.0 * m122 * sbinv * cbinv + (3.0 * mH2 - mh2) * cba2);
      return coupling;
    }

    // A0A0G0G0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_A0A0G0G0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mC = input_pars.mC, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double t2binv = 1.0 / (tan(2.0 * b));
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / v2 * (2.0 * m122 * sbinv * cbinv - 2.0 * mC2 - mH2 * cba2 - mh2 * sba2 + (mH2 - mh2) * t2binv * s2b2a);
      return coupling;
    }

    // h0h0G0A0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_h0h0G0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double t2binv = 1.0 / (tan(2.0 * b)), sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / v2 * (2.0 * m122 * sbinv * cbinv - (mH2 + 2.0 * mh2) * cba2 - (mh2 + 2.0 * mH2) * sba2 + (mH2 - mh2) * t2binv * s2b2a);
      return coupling;
    }

    // H0H0G0A0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_H0H0G0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mA = input_pars.mA, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double cba = cos(b - a);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a), s2a2b = sin(2.0 * a - 2.0 * b);
      const double c2b = cos(2.0 * b);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b) * (mH2 * s2b2a * s2a - mA2 * s2b * s2a2b + cba * (4.0 * m122 * cba * sbinv * cbinv * c2b - mh2 * (cos(-1.0 * b + 3.0 * a) + 3.0 * cos(b + a))));
      return coupling;
    }

    // HpHmG0A0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_HpHmG0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mA = input_pars.mA, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a), s2a2b = sin(2.0 * a - 2.0 * b);
      const double c2b = cos(2.0 * b);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b) * (mh2 * s2b2a * s2a + mA2 * s2b * s2a2b + sba * (4.0 * m122 * sba * sbinv * cbinv * c2b - mH2 * (sin(-1.0 * b + 3.0 * a) - 3.0 * sin(b + a))));
      return coupling;
    }

    // A0A0G0A0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_A0A0G0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double s2b = sin(2.0 * b);
      const double c2b = cos(2.0 * b), c2a = cos(2.0 * a);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b * s2b) * (32 * m122 * c2b + 2.0 * (mH2 - mh2) * (3.0 * c2a + cos(4.0 * b - 2.0 * a)) * s2b - 4.0 * (mh2 + mH2) * sin(4.0 * b));
      return coupling;
    }

    // h0h0HpHm coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_h0h0HpHm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mC = input_pars.mC, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sab = sin(a - b), sab2 = pow(sab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 + c2a2b + c4b) + 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a + 6.0 * c2a2b + c4a4b + 3.0 * c4b + 10.0 * c2a2bp) * mh2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) + 2.0 * s2b) * mH2 + 32.0 * sab2 * s2b * mC2);
      return coupling;
    }

    // h0h0A0A0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_h0h0A0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mA = input_pars.mA, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sab = sin(a - b), sab2 = pow(sab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 + c2a2b + c4b) + 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a + 6.0 * c2a2b + c4a4b + 3.0 * c4b + 10.0 * c2a2bp) * mh2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) + 2.0 * s2b) * mH2 + 32.0 * sab2 * s2b * mA2);
      return coupling;
    }

    // H0H0HpHm coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_H0H0HpHm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mC = input_pars.mC, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double cab = cos(a - b), cab2 = pow(cab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (-cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 - c2a2b + c4b) - 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a - 6.0 * c2a2b + c4a4b + 3.0 * c4b - 10.0 * c2a2bp) * mH2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) - 2.0 * s2b) * mh2 + 32.0 * cab2 * s2b * mC2);
      return coupling;
    }

    // H0H0A0A0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_H0H0A0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mA = input_pars.mA, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double cab = cos(a - b), cab2 = pow(cab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (-cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 - c2a2b + c4b) - 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a - 6.0 * c2a2b + c4a4b + 3.0 * c4b - 10.0 * c2a2bp) * mH2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) - 2.0 * s2b) * mh2 + 32.0 * cab2 * s2b * mA2);
      return coupling;
    }

    // h0H0HpHm coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_h0H0HpHm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mC = input_pars.mC, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), cba = cos(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s4b = sin(4.0 * b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double s3b3a = sin(3.0 * b - 3.0 * a);
      const double c4b = cos(4.0 * b);
      const double c2b2a = cos(2.0 * b - 2.0 * a);
      const double c3b3a = cos(3.0 * b - 3.0 * a);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b) * cba * sbinv * cbinv * (3.0 * sba + s3b3a - 3.0 * sin(b + 3.0 * a) - sin(3.0 * b + a)) * mh2;
      coupling += 1.0 / (8.0 * v2 * s2b) * sba * sbinv * cbinv * (3.0 * cba - c3b3a - 3.0 * cos(b + 3.0 * a) + cos(3.0 * b + a)) * mH2;
      coupling += -1.0 / (8.0 * v2 * s2b) * (8.0 * s2b2a * s2b * mC2 + 4.0 * pow(1.0 / s2b, 2) * (2.0 * (1.0 + 3.0 * c4b) * s2b2a - 4.0 * c2b2a * s4b) * m122);
      return coupling;
    }

    // h0H0A0A0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_h0H0A0A0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, mA = input_pars.mA, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a);
      const double cba = cos(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s4b = sin(4.0 * b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double s3b3a = sin(3.0 * b - 3.0 * a);
      const double c4b = cos(4.0 * b);
      const double c2b2a = cos(2.0 * b - 2.0 * a);
      const double c3b3a = cos(3.0 * b - 3.0 * a);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b) * cba * sbinv * cbinv * (3.0 * sba + s3b3a - 3.0 * sin(b + 3.0 * a) - sin(3.0 * b + a)) * mh2;
      coupling += 1.0 / (8.0 * v2 * s2b) * sba * sbinv * cbinv * (3.0 * cba - c3b3a - 3.0 * cos(b + 3.0 * a) + cos(3.0 * b + a)) * mH2;
      coupling += -1.0 / (8.0 * v2 * s2b) * (8.0 * s2b2a * s2b * mA2 + 4.0 * pow(1.0 / s2b, 2) * (2.0 * (1.0 + 3.0 * c4b) * s2b2a - 4.0 * c2b2a * s4b) * m122);
      return coupling;
    }

    // h0h0h0h0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_h0h0h0h0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double cba = cos(b - a), cbap = cos(b + a), cba2 = pow(cba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 3.0 / (4.0 * v2 * s2b * s2b) * 4.0 * cba2 * (4.0 * m122 * sbinv * cbinv * pow(cbap, 2) - mH2 * pow(s2a, 2));
      coupling += -3.0 / (4.0 * v2 * s2b * s2b) * mh2 * pow((cos(-b + 3.0 * a) + 3.0 * cbap), 2);
      return coupling;
    }

    // h0h0h0H0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_h0h0h0H0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a);
      const double cba = cos(b - a), cbap = cos(b + a);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b * s2b) * 3.0 * s2a * (mH2 * s2a * s2b2a - mh2 * cba * (cos(-b + 3.0 * a) + 3.0 * cbap));
      coupling += 1.0 / (2.0 * v2 * s2b * s2b) * 12.0 * m122 * (1.0 / s2b) * cba * (sin(b + 3.0 * a) - sba);
      return coupling;
    }

    // h0h0H0H0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_h0h0H0H0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2b2a = cos(2.0 * b - 2.0 * a), c2b2ap = cos(2.0 * b + 2.0 * a);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b * s2b) * (4.0 * sbinv * cbinv * (2.0 + c4b - 3.0 * c4a) * m122 + 6.0 * (c4a - 1.0) * (mh2 + mH2));
      coupling += 1.0 / (8.0 * v2 * s2b * s2b) * (3.0 * cos(-2.0 * b + 6.0 * a) - c2b2ap - 2.0 * c2b2a) * (mh2 - mH2);
      return coupling;
    }

    // h0H0H0H0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_h0H0H0H0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), sbap = sin(b + a);
      const double cba = cos(b - a);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b * s2b) * 3.0 * s2a * (mh2 * s2a * s2b2a - mH2 * sba * (sin(-b + 3.0 * a) - 3.0 * sbap));
      coupling += 1.0 / (2.0 * v2 * s2b * s2b) * 12.0 * m122 * (1.0 / s2b) * sba * (cos(b + 3.0 * a) - cba);
      return coupling;
    }

    // H0H0H0H0 coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_H0H0H0H0(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), sbap = sin(b + a), sba2 = pow(sba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 3.0 / (4.0 * v2 * s2b * s2b) * 4.0 * sba2 * (4.0 * m122 * sbinv * cbinv * pow(sbap, 2) - mh2 * pow(s2a, 2));
      coupling += -3.0 / (4.0 * v2 * s2b * s2b) * mH2 * pow((sin(-b + 3.0 * a) - 3.0 * sbap), 2);
      return coupling;
    }

    // HpHmHpHm coupling using physical basis
    std::complex<double> get_quartic_coupling_physical_HpHmHpHm(THDM_spectrum_container &container, physical_basis_input input_pars)
    {
      // extract parameters
      const double mh = input_pars.mh, mH = input_pars.mH, m122 = input_pars.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = input_pars.beta, a = input_pars.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double t2binv = 1.0 / (tan(2.0 * b)), sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double c2b = cos(2.0 * b);
      const double v2 = get_v2(container);
      // calculate coupling
      std::complex<double> coupling = 0.0;
      coupling = 2.0 / v2 * ((mH2 - mh2) * c2b * sbinv * cbinv * s2b2a - mh2 * sba2);
      coupling += -2.0 / v2 * (cba2 * (mH2 + 4.0 * mh2 * pow(t2binv, 2)) + 4.0 * pow(t2binv, 2) * (mH2 * sba2 - m122 * sbinv * cbinv));
      return coupling;
    }

    /// @} end Higgs couplings

    /// @{ functions to fill parameters for NLO unitarity likelihood
    //  ============================================================

    // Higgs couplings needed
    // ---------------------------------------------------------------------

    // puts together a vector of cubic higgs couplings (necessary for NLO unitarity calculation)
    std::vector<std::complex<double>> get_cubic_coupling_higgs(THDM_spectrum_container &container)
    {
      const int size = 17;
      const std::complex<double> i(0.0, 1.0);
      std::vector<std::complex<double>> cubic_couplings(size + 1), cubic_couplings_mass(size + 1);
      std::fill(cubic_couplings.begin(), cubic_couplings.end(), 0.0);
      std::fill(cubic_couplings_mass.begin(), cubic_couplings_mass.end(), 0.0);
      const bool use_cubic_couplings_mass = true;

#ifdef SPECBIT_DEBUG_COUPLINGS
      const bool calculate_both = true;
#else
      const bool calculate_both = false;
#endif

      if (use_cubic_couplings_mass || calculate_both)
      {
        const physical_basis_input input_pars = fill_physical_basis_input(container);
        const std::complex<double> i(0.0, 1.0);

        cubic_couplings[1] = get_cubic_coupling_physical_h0GpGm(container, input_pars);
        cubic_couplings[2] = get_cubic_coupling_physical_h0GpGm(container, input_pars);
        cubic_couplings[3] = get_cubic_coupling_physical_H0GpGm(container, input_pars);
        cubic_couplings[4] = get_cubic_coupling_physical_H0GpGm(container, input_pars);
        cubic_couplings[5] = get_cubic_coupling_physical_h0GpHm(container, input_pars);
        cubic_couplings[6] = get_cubic_coupling_physical_h0G0A0(container, input_pars);
        cubic_couplings[7] = get_cubic_coupling_physical_H0GpHm(container, input_pars);
        cubic_couplings[8] = get_cubic_coupling_physical_H0G0A0(container, input_pars);
        cubic_couplings[9] = get_cubic_coupling_physical_A0GpHm(container, input_pars);
        cubic_couplings[10] = get_cubic_coupling_physical_h0HpHm(container, input_pars);
        cubic_couplings[11] = get_cubic_coupling_physical_h0A0A0(container, input_pars);
        cubic_couplings[12] = get_cubic_coupling_physical_H0HpHm(container, input_pars);
        cubic_couplings[13] = get_cubic_coupling_physical_H0A0A0(container, input_pars);
        cubic_couplings[14] = get_cubic_coupling_physical_h0h0h0(container, input_pars);
        cubic_couplings[15] = get_cubic_coupling_physical_h0h0H0(container, input_pars);
        cubic_couplings[16] = get_cubic_coupling_physical_h0H0H0(container, input_pars);
        cubic_couplings[17] = get_cubic_coupling_physical_H0H0H0(container, input_pars);
        if (calculate_both)
          cubic_couplings_mass = cubic_couplings;
      }
      if (!use_cubic_couplings_mass || calculate_both)
      {
        cubic_couplings[1] = get_cubic_coupling_higgs(container, h0, Gp, Gm);
        cubic_couplings[2] = get_cubic_coupling_higgs(container, h0, G0, G0);
        cubic_couplings[3] = get_cubic_coupling_higgs(container, H0, Gp, Gm);
        cubic_couplings[4] = get_cubic_coupling_higgs(container, H0, G0, G0);
        cubic_couplings[5] = get_cubic_coupling_higgs(container, h0, Gp, Hm);
        cubic_couplings[6] = get_cubic_coupling_higgs(container, h0, G0, A0);
        cubic_couplings[7] = get_cubic_coupling_higgs(container, H0, Gp, Hm);
        cubic_couplings[8] = get_cubic_coupling_higgs(container, H0, G0, A0);
        cubic_couplings[9] = get_cubic_coupling_higgs(container, A0, Gp, Hm);
        cubic_couplings[10] = get_cubic_coupling_higgs(container, h0, Hp, Hm);
        cubic_couplings[11] = get_cubic_coupling_higgs(container, h0, A0, A0);
        cubic_couplings[12] = get_cubic_coupling_higgs(container, H0, Hp, Hm);
        cubic_couplings[13] = get_cubic_coupling_higgs(container, H0, A0, A0);
        cubic_couplings[14] = get_cubic_coupling_higgs(container, h0, h0, h0);
        cubic_couplings[15] = get_cubic_coupling_higgs(container, h0, h0, H0);
        cubic_couplings[16] = get_cubic_coupling_higgs(container, h0, H0, H0);
        cubic_couplings[17] = get_cubic_coupling_higgs(container, H0, H0, H0);
        for (int j = 1; j <= size; j++)
          cubic_couplings[j] = -i * cubic_couplings[j];
      }

#ifdef SPECBIT_DEBUG_COUPLINGS
      std::cout << "*** cubic couplings calculated by GAMBIT" << std::endl
                << "Mass Basis | Higgs Basis" << std::endl;
      for (int i = 1; i <= size; i++)
      {
        std::cout << i << " " << cubic_couplings_mass[i] << " | " << cubic_couplings[i] << std::endl;
      }

      std::cout << "*** cubic couplings calculated by GAMBIT & 2HDMC" << std::endl
                << "GAMBIT | 2HDMC" << std::endl;
      for (int h1 = 1; h1 < 4; h1++)
      {
        for (int h2 = 1; h2 < 4; h2++)
        {
          for (int h3 = 1; h3 < 4; h3++)
          {
            std::complex<double> c;
            container.THDM_object->get_coupling_hhh(h1, h2, h3, c);
            std::complex<double> c2 = get_cubic_coupling_higgs(container, particle_type(h1), particle_type(h2), particle_type(h3));
            std::cout << c2 << " | " << c << std::endl;
          }
        }
      }
#endif

      return cubic_couplings;
    }

    // puts together a vector of quartic higgs couplings (necessary for NLO unitarity calculation)
    std::vector<std::complex<double>> get_quartic_couplings(THDM_spectrum_container &container)
    {
      const int size = 22;
      const std::complex<double> i(0.0, 1.0);
      std::vector<std::complex<double>> quartic_couplings(size + 1), quartic_couplings_mass(size + 1);
      std::fill(quartic_couplings.begin(), quartic_couplings.end(), 0.0);
      std::fill(quartic_couplings_mass.begin(), quartic_couplings_mass.end(), 0.0);
      const bool use_quartic_couplings_mass = true;

#ifdef SPECBIT_DEBUG_COUPLINGS
      const bool calculate_both = true;
#else
      const bool calculate_both = false;
#endif

      if (use_quartic_couplings_mass || calculate_both)
      {
        const physical_basis_input input_pars = fill_physical_basis_input(container);

        const std::complex<double> i(0.0, 1.0);

        quartic_couplings[1] = get_quartic_coupling_physical_h0h0G0G0(container, input_pars);
        quartic_couplings[2] = get_quartic_coupling_physical_HpHmG0G0(container, input_pars);
        quartic_couplings[3] = get_quartic_coupling_physical_A0A0G0G0(container, input_pars);
        quartic_couplings[4] = get_quartic_coupling_physical_h0h0G0A0(container, input_pars);
        quartic_couplings[5] = get_quartic_coupling_physical_H0H0G0A0(container, input_pars);
        quartic_couplings[6] = get_quartic_coupling_physical_HpHmG0A0(container, input_pars);
        quartic_couplings[7] = get_quartic_coupling_physical_A0A0G0A0(container, input_pars);
        quartic_couplings[8] = 3.0 * get_quartic_coupling_physical_A0A0G0A0(container, input_pars);
        quartic_couplings[9] = get_quartic_coupling_physical_h0h0HpHm(container, input_pars);
        quartic_couplings[10] = get_quartic_coupling_physical_h0h0A0A0(container, input_pars);
        quartic_couplings[11] = get_quartic_coupling_physical_H0H0HpHm(container, input_pars);
        quartic_couplings[12] = get_quartic_coupling_physical_H0H0A0A0(container, input_pars);
        quartic_couplings[13] = get_quartic_coupling_physical_h0H0HpHm(container, input_pars);
        quartic_couplings[14] = get_quartic_coupling_physical_h0H0A0A0(container, input_pars);
        quartic_couplings[15] = get_quartic_coupling_physical_h0h0h0h0(container, input_pars);
        quartic_couplings[16] = get_quartic_coupling_physical_h0h0h0H0(container, input_pars);
        quartic_couplings[17] = get_quartic_coupling_physical_h0h0H0H0(container, input_pars);
        quartic_couplings[18] = get_quartic_coupling_physical_h0H0H0H0(container, input_pars);
        quartic_couplings[19] = get_quartic_coupling_physical_H0H0H0H0(container, input_pars);
        quartic_couplings[20] = get_quartic_coupling_physical_HpHmHpHm(container, input_pars);
        quartic_couplings[21] = get_quartic_coupling_physical_HpHmHpHm(container, input_pars) / 2.0;
        quartic_couplings[22] = 3.0 * get_quartic_coupling_physical_HpHmHpHm(container, input_pars) / 2.0;
        if (calculate_both)
          quartic_couplings_mass = quartic_couplings;
      }
      if (!use_quartic_couplings_mass || calculate_both)
      {
        quartic_couplings[1] = get_quartic_coupling_higgs(container, h0, h0, G0, G0);
        quartic_couplings[2] = get_quartic_coupling_higgs(container, H0, H0, G0, G0);
        quartic_couplings[3] = get_quartic_coupling_higgs(container, Hp, Hm, G0, G0);
        quartic_couplings[4] = get_quartic_coupling_higgs(container, A0, A0, G0, G0);
        quartic_couplings[5] = get_quartic_coupling_higgs(container, h0, h0, G0, A0); // differs
        quartic_couplings[6] = get_quartic_coupling_higgs(container, H0, H0, G0, A0); // differs
        quartic_couplings[7] = get_quartic_coupling_higgs(container, Hp, Hm, G0, A0); // equal if third term in equation is .imag() not .real()
        quartic_couplings[8] = get_quartic_coupling_higgs(container, A0, A0, G0, A0); // is different by a factor of sign(Lam6)
        quartic_couplings[9] = get_quartic_coupling_higgs(container, h0, h0, Hp, Hm);
        quartic_couplings[10] = get_quartic_coupling_higgs(container, h0, h0, A0, A0);
        quartic_couplings[11] = get_quartic_coupling_higgs(container, H0, H0, Hp, Hm);
        quartic_couplings[12] = get_quartic_coupling_higgs(container, H0, H0, A0, A0);
        quartic_couplings[13] = get_quartic_coupling_higgs(container, h0, H0, Hp, Hm);
        quartic_couplings[14] = get_quartic_coupling_higgs(container, h0, H0, A0, A0);
        quartic_couplings[15] = get_quartic_coupling_higgs(container, h0, h0, h0, h0);
        quartic_couplings[16] = get_quartic_coupling_higgs(container, h0, h0, h0, H0);
        quartic_couplings[17] = get_quartic_coupling_higgs(container, h0, h0, H0, H0);
        quartic_couplings[18] = get_quartic_coupling_higgs(container, h0, H0, H0, H0);
        quartic_couplings[19] = get_quartic_coupling_higgs(container, H0, H0, H0, H0);
        quartic_couplings[20] = get_quartic_coupling_higgs(container, Hp, Hm, Hp, Hm);
        quartic_couplings[21] = get_quartic_coupling_higgs(container, A0, A0, Hp, Hm);
        quartic_couplings[22] = get_quartic_coupling_higgs(container, A0, A0, A0, A0);
        for (int j = 1; j <= size; j++)
          quartic_couplings[j] = -i * quartic_couplings[j];
      }

#ifdef SPECBIT_DEBUG_COUPLINGS
      std::cout << "*** quartic couplings calculated by GAMBIT" << std::endl
                << "Mass Basis | Higgs Basis" << std::endl;
      for (int i = 1; i <= size; i++)
      {
        std::cout << i << " " << quartic_couplings_mass[i] << " | " << quartic_couplings[i] << std::endl;
      }

      std::cout << "*** quartic couplings calculated by GAMBIT & 2HDMC" << std::endl
                << "GAMBIT | 2HDMC" << std::endl;
      for (int h1 = 1; h1 < 4; h1++)
      {
        for (int h2 = 1; h2 < 4; h2++)
        {
          for (int h3 = 1; h3 < 4; h3++)
          {
            for (int h4 = 1; h4 < 4; h4++)
            {
              std::complex<double> c;
              container.THDM_object->get_coupling_hhhh(h1, h2, h3, h4, c);
              std::complex<double> c2 = get_quartic_coupling_higgs(container, particle_type(h1), particle_type(h2), particle_type(h3), particle_type(h4));
              std::cout << c2 << " | " << c << std::endl;
            }
          }
        }
      }
#endif

      return quartic_couplings;
    }

    // wavefunction corrections to beta functions
    // ---------------------------------------------------------------------
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

    std::complex<double> B0_bar(const double p2, const double m12, const double m22)
    {
      const double MZ = 91.15349; // get this from FS
      const std::complex<double> i(0.0, 1.0);
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
      std::vector<std::complex<double>> m;
      std::vector<std::complex<double>> g;
    };

    wavefunction_renormalization_input fill_wavefunction_renormalization_input(THDM_spectrum_container &container)
    {
      wavefunction_renormalization_input input;
      fill_physical_basis(input, container);
      input.m = get_cubic_coupling_higgs(container);
      input.g = get_quartic_couplings(container);
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

    //Self energies & wavefunction renormalizations
    std::complex<double> Pi_tilde_wpwm(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = pow(m[1], 2) * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += pow(m[3], 2) * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += pow(m[5], 2) * (B0_bar(p2, mC2, mh2) - B0_bar(0., mC2, mh2));
      Pi += pow(m[7], 2) * (B0_bar(p2, mC2, mH2) - B0_bar(0., mC2, mH2));
      Pi += m[9] * std::conj(m[9]) * (B0_bar(p2, mC2, mA2) - B0_bar(0., mC2, mA2));
      return -1.0 / (16.0 * pow(M_PI, 2)) * Pi;
    }
    double Pi_tilde_wpwm_re(const double p2, void *params) { return Pi_tilde_wpwm(p2, params).real(); }
    double Pi_tilde_wpwm_im(const double p2, void *params) { return Pi_tilde_wpwm(p2, params).imag(); }

    std::complex<double> Pi_tilde_zz(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = pow(m[2], 2) * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += pow(m[4], 2) * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += pow(m[6], 2) * (B0_bar(p2, mA2, mh2) - B0_bar(0., mA2, mh2));
      Pi += pow(m[8], 2) * (B0_bar(p2, mA2, mH2) - B0_bar(0., mA2, mH2));
      return -1.0 / (16.0 * pow(M_PI, 2)) * Pi;
    }
    double Pi_tilde_zz_re(const double p2, void *params) { return Pi_tilde_zz(p2, params).real(); }
    double Pi_tilde_zz_im(const double p2, void *params) { return Pi_tilde_zz(p2, params).imag(); }

    std::complex<double> Pi_tilde_wpHm(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = m[1] * m[5] * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += m[3] * m[7] * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += m[5] * m[10] * (B0_bar(p2, mC2, mh2) - B0_bar(0., mC2, mh2));
      Pi += m[7] * m[12] * (B0_bar(p2, mC2, mH2) - B0_bar(0., mC2, mH2));
      return -1.0 / (16.0 * pow(M_PI, 2)) * Pi;
    }
    double Pi_tilde_wpHm_re(const double p2, void *params) { return Pi_tilde_wpHm(p2, params).real(); }
    double Pi_tilde_wpHm_im(const double p2, void *params) { return Pi_tilde_wpHm(p2, params).imag(); }

    std::complex<double> Pi_tilde_zA(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = m[2] * m[6] * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += m[4] * m[8] * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += m[6] * m[11] * (B0_bar(p2, mA2, mh2) - B0_bar(0., mA2, mh2));
      Pi += m[8] * m[13] * (B0_bar(p2, mA2, mH2) - B0_bar(0., mA2, mH2));
      return -1.0 / (16.0 * pow(M_PI, 2)) * Pi;
    }
    double Pi_tilde_zA_re(const double p2, void *params) { return Pi_tilde_zA(p2, params).real(); }
    double Pi_tilde_zA_im(const double p2, void *params) { return Pi_tilde_zA(p2, params).imag(); }

    std::complex<double> Pi_zz(void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (g[1] * A0_bar(mh2) + g[2] * A0_bar(mH2) + 2.0 * g[3] * A0_bar(mC2) + g[4] * A0_bar(mA2));
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

    std::complex<double> Pi_zA(void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (g[5] * A0_bar(mh2) + g[6] * A0_bar(mH2) + 2.0 * g[7] * A0_bar(mC2) + g[8] * A0_bar(mA2));
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

    std::complex<double> Pi_tilde_hh(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC, beta = input_pars->beta, alpha = input_pars->alpha;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      const double sba = sin(beta - alpha), cba = abs(cos(beta - alpha));
      std::complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (2.0 * g[9] * A0_bar(mC2) + g[10] * A0_bar(mA2) + g[15] * A0_bar(mh2) + g[17] * A0_bar(mH2));
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

    std::complex<double> Pi_tilde_HH(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC, beta = input_pars->beta, alpha = input_pars->alpha;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      const double sba = sin(beta - alpha), cba = cos(beta - alpha);
      std::complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (2.0 * g[11] * A0_bar(mC2) + g[12] * A0_bar(mA2) + g[17] * A0_bar(mh2) + g[19] * A0_bar(mH2));
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

    std::complex<double> Pi_tilde_hH(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC, beta = input_pars->beta, alpha = input_pars->alpha;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      const double sba = sin(beta - alpha), cba = abs(cos(beta - alpha));
      std::complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (2.0 * g[13] * A0_bar(mC2) + g[14] * A0_bar(mA2) + g[16] * A0_bar(mh2) + g[18] * A0_bar(mH2));
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

    std::complex<double> Pi_tilde_HpHm(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (g[9] * A0_bar(mh2) + g[11] * A0_bar(mH2) + 2.0 * g[20] * A0_bar(mC2) + g[21] * A0_bar(mA2));
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

    std::complex<double> Pi_tilde_AA(const double p2, void *params)
    {
      const wavefunction_renormalization_input *input_pars = static_cast<const wavefunction_renormalization_input *>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = 1.0 / (32.0 * pow(M_PI, 2)) * (g[10] * A0_bar(mh2) + g[12] * A0_bar(mH2) + 2.0 * g[21] * A0_bar(mC2) + g[22] * A0_bar(mA2));
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

    std::complex<double> z_ii(const wavefunction_renormalization type, wavefunction_renormalization_input &params)
    {
      gsl_function F_re;
      gsl_function F_im;
      F_re.params = &params;
      F_im.params = &params;
      double result_re, result_im, abserr_re, abserr_im;
      double m_in = 0.0;
      const std::complex<double> i(0.0, 1.0);
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
      const std::complex<double> Z_ii = 1.0 + 0.5 * (result_re + i * result_im);
      return 16.0 * pow(M_PI, 2) * (Z_ii - 1.0);
    }

    std::complex<double> z_ij(const wavefunction_renormalization type, THDM_spectrum_container &container)
    {
      std::complex<double> z_ij = 0.0;
      double m1 = 0.0, m2 = 0.0;
      wavefunction_renormalization_input input_pars = fill_wavefunction_renormalization_input(container);
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
    // ---------------------------------------------------------------------

    // Custom functions to extend GSL
    std::complex<double> gsl_complex_to_complex_double(const gsl_complex c)
    {
      return std::complex<double>(GSL_REAL(c), GSL_IMAG(c));
    }

    std::complex<double> gsl_matrix_complex_trace_complex(const gsl_matrix_complex *m1)
    {
      return gsl_complex_to_complex_double(gsl_matrix_complex_get(m1, 0, 0)) +
             gsl_complex_to_complex_double(gsl_matrix_complex_get(m1, 1, 1)) +
             gsl_complex_to_complex_double(gsl_matrix_complex_get(m1, 2, 2));
    }

    // gets Yukawa traces required for LO corrections to lambda_i beta functions
    //- easily extendable to Yukawas with off-diagonals
    std::map<std::string, std::complex<double>> get_traces_of_y(THDM_spectrum_container &container)
    {
      std::complex<double> tr_u2, tr_d2, tr_l2, tr_u4, tr_d4, tr_l4, tr_du;
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
      GSL_SET_REAL(&y_u_11, container.he->get(Par::dimensionless, "Yu", 1, 1));
      GSL_SET_IMAG(&y_u_11, 0.0);

      gsl_complex y_u_22;
      GSL_SET_REAL(&y_u_22, container.he->get(Par::dimensionless, "Yu", 2, 2));
      GSL_SET_IMAG(&y_u_22, 0.0);

      gsl_complex y_u_33;
      GSL_SET_REAL(&y_u_33, container.he->get(Par::dimensionless, "Yu", 3, 3));
      GSL_SET_IMAG(&y_u_33, 0.0);

      gsl_matrix_complex_set_zero(y_u);

      gsl_matrix_complex_set(y_u, 0, 0, y_u_11);
      gsl_matrix_complex_set(y_u, 1, 1, y_u_22);
      gsl_matrix_complex_set(y_u, 2, 2, y_u_33);

      // take dagger -> all components currently real so no need to conjugate
      gsl_matrix_complex_transpose_memcpy(y_u_dagger, y_u);

      // set yukawa - down
      gsl_complex y_d_11;
      GSL_SET_REAL(&y_d_11, container.he->get(Par::dimensionless, "Yd", 1, 1));
      GSL_SET_IMAG(&y_d_11, 0.0);

      gsl_complex y_d_22;
      GSL_SET_REAL(&y_d_22, container.he->get(Par::dimensionless, "Yd", 2, 2));
      GSL_SET_IMAG(&y_d_22, 0.0);

      gsl_complex y_d_33;
      GSL_SET_REAL(&y_d_33, container.he->get(Par::dimensionless, "Yd", 3, 3));
      GSL_SET_IMAG(&y_d_33, 0.0);

      gsl_matrix_complex_set_zero(y_d);

      gsl_matrix_complex_set(y_d, 0, 0, y_d_11);
      gsl_matrix_complex_set(y_d, 1, 1, y_d_22);
      gsl_matrix_complex_set(y_d, 2, 2, y_d_33);

      // take dagger -> all components currently real so no need to conjugate
      gsl_matrix_complex_transpose_memcpy(y_d_dagger, y_d);

      // set yukawa - lepton
      gsl_complex y_l_11;
      GSL_SET_REAL(&y_l_11, container.he->get(Par::dimensionless, "Ye", 1, 1));
      GSL_SET_IMAG(&y_l_11, 0.0);

      gsl_complex y_l_22;
      GSL_SET_REAL(&y_l_22, container.he->get(Par::dimensionless, "Ye", 2, 2));
      GSL_SET_IMAG(&y_l_22, 0.0);

      gsl_complex y_l_33;
      GSL_SET_REAL(&y_l_33, container.he->get(Par::dimensionless, "Ye", 3, 3));
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
    // appearing in the LO corrections to lambda_i beta functions
    // see Nucl.Phys.B 262 (1985) 517-537
    std::vector<double> get_alphas_for_type(const int type)
    {
      std::vector<double> a;
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

    // gets Yukawa traces required for LO corrections to lambda_i beta functions
    // simple functions for efficiency - only for diagonal Yukawas
    double get_tr_pow(THDM_spectrum_container &container, std::string yukawa_name, int pow_N)
    {
      double tr = 0.0;
      for (int i = 1; i <= 3; i++)
      {
        tr += pow(container.he->get(Par::dimensionless, yukawa_name, i, i), pow_N);
      }
      return tr;
    }

    double get_tr_dduu(THDM_spectrum_container &container)
    {
      double tr = 0.0;
      for (int i = 1; i <= 3; i++)
      {
        tr += pow(container.he->get(Par::dimensionless, "Yd", i, i), 2) * pow(container.he->get(Par::dimensionless, "Yu", i, i), 2);
      }
      return tr;
    }

    // LO beta function for lambda_1
    std::complex<double> beta_one(THDM_spectrum_container &container, const bool gauge_correction, const bool yukawa_correction)
    {
      std::vector<double> a = get_alphas_for_type(container.yukawa_type);
      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      const double g1 = container.he->get(Par::dimensionless, "g1"), g2 = container.he->get(Par::dimensionless, "g2");
      const std::complex<double> tr_u2 = get_tr_pow(container, "Yu", 2), tr_d2 = get_tr_pow(container, "Yd", 2), tr_l2 = get_tr_pow(container, "Ye", 2);
      const std::complex<double> tr_u4 = get_tr_pow(container, "Yu", 4), tr_d4 = get_tr_pow(container, "Yd", 4), tr_l4 = get_tr_pow(container, "Ye", 4);
      std::complex<double> beta = 12.0 * pow(Lambda[1], 2) + 4.0 * pow(Lambda[3], 2) + 4.0 * Lambda[3] * Lambda[4] + 2.0 * pow(Lambda[4], 2) + 2.0 * pow(Lambda[5], 2);
      if (gauge_correction)
        beta += 3.0 / 4.0 * pow(g1, 4) + 3.0 / 2.0 * pow(g1, 2) * pow(g2, 2) + 9.0 / 4.0 * pow(g2, 4) - 3.0 * pow(g1, 2) * Lambda[1] - 9.0 * pow(g2, 2) * Lambda[1];
      if (yukawa_correction)
        beta += 4.0 * Lambda[1] * (a[1] * tr_l2 + 3.0 * a[2] * tr_d2 + 3.0 * a[3] * tr_u2) - 4.0 * (a[4] * tr_l4 + 3.0 * a[5] * tr_d4 + 3.0 * a[6] * tr_u4);
      return 1.0 / (16.0 * pow(M_PI, 2)) * (beta);
    }

    // LO beta function for lambda_2
    std::complex<double> beta_two(THDM_spectrum_container &container, const bool gauge_correction, const bool yukawa_correction)
    {
      const std::vector<double> a = get_alphas_for_type(container.yukawa_type);
      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      const double g1 = container.he->get(Par::dimensionless, "g1"), g2 = container.he->get(Par::dimensionless, "g2");
      const std::complex<double> tr_u2 = get_tr_pow(container, "Yu", 2), tr_d2 = get_tr_pow(container, "Yd", 2), tr_l2 = get_tr_pow(container, "Ye", 2);
      const std::complex<double> tr_u4 = get_tr_pow(container, "Yu", 4), tr_d4 = get_tr_pow(container, "Yd", 4), tr_l4 = get_tr_pow(container, "Ye", 4);
      std::complex<double> beta = 12.0 * pow(Lambda[2], 2) + 4.0 * pow(Lambda[3], 2) + 4.0 * Lambda[3] * Lambda[4] + 2.0 * pow(Lambda[4], 2) + 2.0 * pow(Lambda[5], 2);
      if (gauge_correction)
        beta += 3.0 / 4.0 * pow(g1, 4) + 3.0 / 2.0 * pow(g1, 2) * pow(g2, 2) + 9.0 / 4.0 * pow(g2, 4) - 3.0 * pow(g1, 2) * Lambda[2] - 9.0 * pow(g2, 2) * Lambda[2];
      if (yukawa_correction)
        beta += 4.0 * Lambda[2] * (a[7] * tr_l2 + 3.0 * a[8] * tr_d2 + 3.0 * a[9] * tr_u2) - 4.0 * (a[10] * tr_l4 + 3.0 * a[11] * tr_d4 + 3.0 * a[12] * tr_u4);
      return 1.0 / (16.0 * pow(M_PI, 2)) * beta;
    }

    // LO beta function for lambda_3
    std::complex<double> beta_three(THDM_spectrum_container &container, const bool gauge_correction, const bool yukawa_correction)
    {
      const std::vector<double> a = get_alphas_for_type(container.yukawa_type);
      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      const double g1 = container.he->get(Par::dimensionless, "g1"), g2 = container.he->get(Par::dimensionless, "g2");
      const std::complex<double> tr_u2 = get_tr_pow(container, "Yu", 2), tr_d2 = get_tr_pow(container, "Yd", 2), tr_l2 = get_tr_pow(container, "Ye", 2);
      const std::complex<double> tr_du = get_tr_dduu(container);
      std::complex<double> beta = 4.0 * pow(Lambda[3], 2) + 2.0 * pow(Lambda[4], 2) + (Lambda[1] + Lambda[2]) * (6.0 * Lambda[3] + 2.0 * Lambda[4]) + 2.0 * pow(Lambda[5], 2);
      if (gauge_correction)
        beta += -3.0 * Lambda[3] * (3.0 * pow(g2, 2) + pow(g1, 2)) + 9.0 / 4.0 * pow(g2, 4) + 3.0 / 4.0 * pow(g1, 4) - 3.0 / 2.0 * pow(g1, 2) * pow(g2, 2);
      if (yukawa_correction)
        beta += 2 * Lambda[3] * (a[13] * tr_l2 + 3.0 * a[14] * tr_d2 + 3.0 * a[15] * tr_u2) - 12.0 * a[16] * tr_du;
      return 1.0 / (16.0 * pow(M_PI, 2)) * beta;
    }

    // LO beta function for lambda_4
    std::complex<double> beta_four(THDM_spectrum_container &container, const bool gauge_correction, const bool yukawa_correction)
    {
      const std::vector<double> a = get_alphas_for_type(container.yukawa_type);
      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      const double g1 = container.he->get(Par::dimensionless, "g1"), g2 = container.he->get(Par::dimensionless, "g2");
      const std::complex<double> tr_u2 = get_tr_pow(container, "Yu", 2), tr_d2 = get_tr_pow(container, "Yd", 2), tr_l2 = get_tr_pow(container, "Ye", 2);
      const std::complex<double> tr_du = get_tr_dduu(container);
      std::complex<double> beta = (2.0 * Lambda[1] + 2.0 * Lambda[2] + 8.0 * Lambda[3]) * Lambda[4] + 4.0 * pow(Lambda[4], 2) + 8.0 * pow(Lambda[5], 2);
      if (gauge_correction)
        beta += -3.0 * Lambda[4] * (3.0 * pow(g2, 2) + pow(g1, 2)) + 3.0 * pow(g1, 2) * pow(g2, 2);
      if (yukawa_correction)
        beta += 2.0 * Lambda[4] * (a[17] * tr_l2 + 3.0 * a[18] * tr_d2 + 3.0 * a[19] * tr_u2) + 12.0 * a[20] * tr_du;
      return 1.0 / (16.0 * pow(M_PI, 2)) * beta;
    }

    // LO beta function for lambda_5
    std::complex<double> beta_five(THDM_spectrum_container &container, const bool gauge_correction, const bool yukawa_correction)
    {
      const std::vector<double> a = get_alphas_for_type(container.yukawa_type);
      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      const double g1 = container.he->get(Par::dimensionless, "g1"), g2 = container.he->get(Par::dimensionless, "g2");
      const std::complex<double> tr_u2 = get_tr_pow(container, "Yu", 2), tr_d2 = get_tr_pow(container, "Yd", 2), tr_l2 = get_tr_pow(container, "Ye", 2);
      std::complex<double> beta = (2.0 * Lambda[1] + 2.0 * Lambda[2] + 8.0 * Lambda[3] + 12.0 * Lambda[4]) * Lambda[5];
      if (gauge_correction)
        beta += -3.0 * Lambda[5] * (3.0 * pow(g2, 2) + pow(g1, 2));
      if (yukawa_correction)
        beta += 2.0 * Lambda[5] * (a[21] * tr_l2 + 3.0 * a[22] * tr_d2 + 3.0 * a[23] * tr_u2);
      return 1.0 / (16.0 * pow(M_PI, 2)) * beta;
    }

    // put everything together to get the NLO unitarity scattering eigenvalues
    std::vector<std::complex<double>> get_NLO_scattering_eigenvalues(THDM_spectrum_container &container, const bool wave_function_corrections, const bool gauge_corrections, const bool yukawa_corrections)
    {
      const std::complex<double> i(0.0, 1.0);

      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);

      // check that model is Z2 conserving
      if (!check_Z2(Lambda[6], Lambda[7], "NLO_unitarity_likelihood_THDM"))
        return {0.0};

      double b = atan(container.he->get(Par::dimensionless, "tanb")), a = container.he->get(Par::dimensionless, "alpha");
      double c2a = cos(2.0 * a), c2b = cos(2.0 * b), s2a = sin(2.0 * a), s2b = sin(2.0 * b);

      // calculate LO beta functions
      const std::complex<double> b_one = beta_one(container, gauge_corrections, yukawa_corrections);
      const std::complex<double> b_two = beta_two(container, gauge_corrections, yukawa_corrections);
      const std::complex<double> b_three = beta_three(container, gauge_corrections, yukawa_corrections);
      const std::complex<double> b_four = beta_four(container, gauge_corrections, yukawa_corrections);
      const std::complex<double> b_five = beta_five(container, gauge_corrections, yukawa_corrections);

      // wavefunction functions
      std::complex<double> zij_wpwm, zij_zz, zij_Hpwm, zij_Az, zij_hh, zij_HH, zij_hH, zij_Hh, zij_HpHm, zij_AA;
      std::complex<double> B1_z, B2_z, B3_z, B20_z, B21_z, B22_z;
      if (wave_function_corrections)
      {
        zij_wpwm = z_ij(wpwm, container);
        zij_zz = z_ij(zz, container);
        zij_Hpwm = z_ij(Hpwm, container);
        zij_Az = z_ij(Az, container);
        zij_hh = z_ij(hh, container);
        zij_HH = z_ij(HH, container);
        zij_hH = z_ij(hH, container);
        zij_Hh = z_ij(Hh, container);
        zij_HpHm = z_ij(HpHm, container);
        zij_AA = z_ij(AA, container);
      }

      std::complex<double> B1 = -3.0 * Lambda[1] + (9.0 / 2.0) * b_one + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (9.0 * pow(Lambda[1], 2) + pow((2.0 * Lambda[3] + Lambda[4]), 2));
      if (wave_function_corrections)
      {
        B1_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + 2.0 * zij_HpHm + zij_HH + 2.0 * zij_wpwm + zij_zz - (zij_HH - zij_hh) * c2a);
        B1_z += 1.0 / (16.0 * pow(M_PI, 2)) * ((2.0 * zij_wpwm - 2.0 * zij_HpHm + zij_zz - zij_AA) * c2b - (zij_Hh + zij_hH) * s2a - (2.0 * zij_Hpwm + zij_Az) * s2b);
        B1 += -3.0 / 2.0 * Lambda[1] * B1_z;
      }

      std::complex<double> B2 = -3.0 * Lambda[2] + (9.0 / 2.0) * b_two + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (9.0 * pow(Lambda[2], 2) + pow((2.0 * Lambda[3] + Lambda[4]), 2));
      if (wave_function_corrections)
      {
        B2_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + 2.0 * zij_HpHm + zij_HH + 2.0 * zij_wpwm + zij_zz - (zij_HH - zij_hh) * c2a);
        B2_z += 1.0 / (16.0 * pow(M_PI, 2)) * (-(2.0 * zij_wpwm - 2.0 * zij_HpHm + zij_zz - zij_AA) * c2b + (zij_Hh + zij_hH) * s2a + (2.0 * zij_Hpwm + zij_Az) * s2b);
        B2 += -3.0 / 2.0 * Lambda[2] * B2_z;
      }

      std::complex<double> B3 = -(2.0 * Lambda[3] + Lambda[4]) + (3.0 / 2.0) * (2.0 * b_three + b_four) + 3.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (Lambda[1] + Lambda[2]) * (2.0 * Lambda[3] + Lambda[4]);
      if (wave_function_corrections)
      {
        std::complex<double> B3_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + 2.0 * zij_HpHm + zij_HH + 2.0 * zij_wpwm + zij_zz);
        B3 += -1.0 / 2.0 * (2.0 * Lambda[3] + Lambda[4]) * B3_z;
      }

      std::complex<double> B4 = -(Lambda[3] + 2.0 * Lambda[4]) + (3.0 / 2.0) * (b_three + 2.0 * b_four) + (1.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * (pow(Lambda[3], 2) + 4.0 * Lambda[3] * Lambda[4] + 4.0 * pow(Lambda[4], 2) + 9.0 * pow(Lambda[5], 2));
      if (wave_function_corrections)
      {
        B4 += -1.0 / 2.0 * (Lambda[3] + Lambda[4] + Lambda[5]) * B3_z;
      }

      std::complex<double> B6 = -3.0 * Lambda[5] + (9.0 / 2.0) * b_five + (6.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * (Lambda[3] + 2.0 * Lambda[4]) * Lambda[5];
      if (wave_function_corrections)
      {
        B6 += -1.0 / 2.0 * (Lambda[4] + 2.0 * Lambda[5]) * B3_z;
      }

      std::complex<double> B7 = -Lambda[1] + (3.0 / 2.0) * b_one + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (pow(Lambda[1], 2) + pow(Lambda[4], 2));
      if (wave_function_corrections)
      {
        B7 += -1.0 / 2.0 * Lambda[1] * B1_z;
      }

      std::complex<double> B8 = -Lambda[2] + (3.0 / 2.0) * b_two + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (pow(Lambda[2], 2) + pow(Lambda[4], 2));
      if (wave_function_corrections)
      {
        B8 += -1.0 / 2.0 * Lambda[2] * B2_z;
      }

      std::complex<double> B9 = -Lambda[4] + (3.0 / 2.0) * b_four + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (Lambda[1] + Lambda[2]) * Lambda[4];
      if (wave_function_corrections)
      {
        B9 += -1.0 / 2.0 * Lambda[4] * B3_z;
      }

      std::complex<double> B13 = -Lambda[3] + (3.0 / 2.0) * b_three + (1.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * (pow(Lambda[3], 2) + pow(Lambda[5], 2));
      if (wave_function_corrections)
      {
        B13 += -1.0 / 2.0 * (Lambda[3] + Lambda[4] + Lambda[5]) * B3_z;
      }

      std::complex<double> B15 = -Lambda[5] + (3.0 / 2.0) * b_five + (2.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * Lambda[3] * Lambda[5];
      if (wave_function_corrections)
      {
        B15 += -1.0 / 2.0 * (Lambda[4] - 2.0 * Lambda[5]) * B3_z;
      }

      std::complex<double> B19 = -(Lambda[3] - Lambda[4]) + (3.0 / 2.0) * (b_three - b_four) + (1.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * pow((Lambda[3] - Lambda[4]), 2);
      if (wave_function_corrections)
      {
        B19 += -1.0 / 2.0 * (Lambda[3] - Lambda[5]) * B3_z;
      }

      std::complex<double> B20 = -Lambda[1] + (3.0 / 2.0) * b_one + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (pow(Lambda[1], 2) + pow(Lambda[5], 2));
      if (wave_function_corrections)
      {
        B20_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + zij_HH + zij_zz + (zij_HH - zij_hh) * c2a + (zij_zz - zij_AA) * c2b - (zij_Hh - zij_hH) * s2a - zij_Az * s2b);
        B20 += -1.0 * Lambda[1] * B20_z;
      }

      std::complex<double> B21 = -Lambda[2] + (3.0 / 2.0) * b_two + 1.0 / (16.0 * pow(M_PI, 2)) * (i * M_PI - 1.) * (pow(Lambda[2], 2) + pow(Lambda[5], 2));
      if (wave_function_corrections)
      {
        B21_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + zij_HH + zij_zz + (zij_HH - zij_hh) * c2a - (zij_zz - zij_AA) * c2b + (zij_Hh - zij_hH) * s2a + zij_Az * s2b);
        B21 += -1.0 * Lambda[2] * B21_z;
      }

      std::complex<double> B22 = -Lambda[5] + (3.0 / 2.0) * b_five + (1.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * (Lambda[1] + Lambda[2]) * Lambda[5];
      if (wave_function_corrections)
      {
        B22_z = 1.0 / (16.0 * pow(M_PI, 2)) * (zij_AA + zij_hh + zij_HH + zij_zz);
        B22 += -1.0 * Lambda[5] * B22_z;
      }

      std::complex<double> B30 = -(Lambda[3] + Lambda[4]) + (3.0 / 2.0) * (b_three + b_four) + (1.0 / (16.0 * pow(M_PI, 2))) * (i * M_PI - 1.) * pow((Lambda[3] + Lambda[4]), 2);
      if (wave_function_corrections)
      {
        B30 += -1.0 * (Lambda[3] + Lambda[4]) * B22_z;
      }

      // eigenvalues
      std::complex<double> a00_even_plus = 1.0 / (32.0 * M_PI) * ((B1 + B2) + sqrt(pow((B1 - B2), 2) + 4. * pow(B3, 2)));
      std::complex<double> a00_even_minus = 1.0 / (32.0 * M_PI) * ((B1 + B2) - sqrt(pow((B1 - B2), 2) + 4. * pow(B3, 2)));
      std::complex<double> a00_odd_plus = 1.0 / (32.0 * M_PI) * (2. * B4 + 2. * B6);
      std::complex<double> a00_odd_minus = 1.0 / (32.0 * M_PI) * (2. * B4 - 2. * B6);
      std::complex<double> a01_even_plus = 1.0 / (32.0 * M_PI) * (B7 + B8 + sqrt(pow((B7 - B8), 2) + 4. * pow(B9, 2)));
      std::complex<double> a01_even_minus = 1.0 / (32.0 * M_PI) * (B7 + B8 - sqrt(pow((B7 - B8), 2) + 4. * pow(B9, 2)));
      std::complex<double> a01_odd_plus = 1.0 / (32.0 * M_PI) * (2. * B13 + 2. * B15);
      std::complex<double> a01_odd_minus = 1.0 / (32.0 * M_PI) * (2. * B13 - 2. * B15);
      std::complex<double> a10_odd = 1.0 / (32.0 * M_PI) * (2. * B19);
      std::complex<double> a11_even_plus = 1.0 / (32.0 * M_PI) * (B20 + B21 + sqrt(pow((B20 - B21), 2) + 4. * pow(B22, 2)));
      std::complex<double> a11_even_minus = 1.0 / (32.0 * M_PI) * (B20 + B21 - sqrt(pow((B20 - B21), 2) + 4. * pow(B22, 2)));
      std::complex<double> a11_odd = 1.0 / (32.0 * M_PI) * (2. * B30);

      return {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus,
              a01_even_minus, a01_odd_plus, a01_odd_minus, a10_odd, a11_even_plus, a11_even_minus, a11_odd};
    }
    
    /// @} end NLO unitarity helpers

    /// @{ likelihood helper functions that call the likleihood/constraint functions after setting up the correct parameters
    //  ============================================================

    // Step Functions (forward declarations)
    double loop_correction_mass_splitting_h0_THDM(THDM_spectrum_container &container);
    double loop_correction_mass_splitting_scalar_THDM(THDM_spectrum_container &container);
    double scalar_masses_THDM(THDM_spectrum_container &container, const double min_scalar_mass, const double max_scalar_mass);
    // Likelihood Functions (forward declarations)
    double unitarity_likelihood_THDM(THDM_spectrum_container &container);
    double NLO_unitarity_likelihood_THDM(THDM_spectrum_container &container, const bool check_correction_ratio, const bool wave_function_corrections, const bool gauge_corrections, const bool yukawa_corrections);
    double perturbativity_likelihood_THDM(THDM_spectrum_container &container);
    double perturbativity_likelihood_simple_THDM(THDM_spectrum_container &container);
    double stability_likelihood_THDM(THDM_spectrum_container &container);
    double alignment_likelihood_THDM(THDM_spectrum_container &container);
    // Observable Functions (forward declatations)
    double global_minimum_discriminant_THDM(THDM_spectrum_container &container);

    // #define NEW_SPECBIT
    void get_unitarity_likelihood_THDM(double &result)
    {
      using namespace Pipes::get_unitarity_likelihood_THDM;
      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      bool is_at_Q = false;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          is_at_Q = THDM_model.second.is_model_at_Q;
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // define likelihood function to use
      std::function<double(THDM_spectrum_container &)> likelihood_function = unitarity_likelihood_THDM;
      // create container
      THDM_spectrum_container container;
      // initialise container at Qin - this is where the 2HDMC is configured
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);
      // evaluate loglike
      const double loglike = likelihood_function(container);
      // note that we may alos check SpecBit's likelihoods at a different scale: check_other_scale
      double loglike_at_Q = L_MAX;
      double check_other_scale = runOptions->getValueOrDef<double>(0.0, "check_other_scale");
      if (check_other_scale > 0.0)
      {
        if (is_at_Q)
        {
          // get likelihood at check_other_scale
          THDM_spectrum_container container_at_scale;
          BEreq::init_THDM_spectrum_container_CONV(container_at_scale, *Dep::THDM_spectrum, byVal(yukawa_type), byVal(check_other_scale), 0);
          loglike_at_Q = likelihood_function(container_at_scale);
        }
        else
        {
          // print warning if we ask for likelihood at check_other_scale but not using FS model
          print_calculation_at_scale_warning("get_unitarity_likelihood_THDM");
        }
      }
      // return the worse performing likelihood
      result = std::min(loglike, loglike_at_Q);
    }

    void get_NLO_unitarity_likelihood_THDM(double &result)
    {
      using namespace Pipes::get_NLO_unitarity_likelihood_THDM;
      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      bool is_at_Q = false;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          is_at_Q = THDM_model.second.is_model_at_Q;
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // define likelihood function to use
      // get options
      const bool check_corrections_ratio = runOptions->getValueOrDef<bool>(false, "check_correction_ratio");
      const bool wave_function_corrections = runOptions->getValueOrDef<bool>(false, "wave_function_corrections");
      const bool gauge_corrections = runOptions->getValueOrDef<bool>(false, "gauge_corrections");
      const bool yukawa_corrections = runOptions->getValueOrDef<bool>(false, "yukawa_corrections");
      // create likelihood function
      std::function<double(THDM_spectrum_container &, const bool, const bool, const bool, const bool)> likelihood_function = NLO_unitarity_likelihood_THDM;

      // create container
      THDM_spectrum_container container;
      // initialise container at Qin - this is where the 2HDMC is configured
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);
      // evaluate loglike
      const double loglike = likelihood_function(container, check_corrections_ratio, wave_function_corrections, gauge_corrections, yukawa_corrections);
      // note that we may alos check SpecBit's likelihoods at a different scale: check_other_scale
      double loglike_at_Q = L_MAX;
      double check_other_scale = runOptions->getValueOrDef<double>(0.0, "check_other_scale");
      if (check_other_scale > 0.0)
      {
        if (is_at_Q)
        {
          // get likelihood at check_other_scale
          THDM_spectrum_container container_at_scale;
          BEreq::init_THDM_spectrum_container_CONV(container_at_scale, *Dep::THDM_spectrum, byVal(yukawa_type), byVal(check_other_scale), 0);
          loglike_at_Q = likelihood_function(container_at_scale, check_corrections_ratio, wave_function_corrections, gauge_corrections, yukawa_corrections);
        }
        else
        {
          // print warning if we ask for likelihood at check_other_scale but not using FS model
          print_calculation_at_scale_warning("get_NLO_unitarity_likelihood_THDM");
        }
      }
      // return the worse performing likelihood
      result = std::min(loglike, loglike_at_Q);
    }

    void get_perturbativity_likelihood_THDM(double &result)
    {
      using namespace Pipes::get_perturbativity_likelihood_THDM;
      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      bool is_at_Q = false;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          is_at_Q = THDM_model.second.is_model_at_Q;
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // define likelihood function to use
      std::function<double(THDM_spectrum_container &)> likelihood_function = perturbativity_likelihood_THDM;
      // create container
      THDM_spectrum_container container;
      // initialise container at Qin - this is where the 2HDMC is configured
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);
      // evaluate loglike
      const double loglike = likelihood_function(container);
      // note that we may alos check SpecBit's likelihoods at a different scale: check_other_scale
      double loglike_at_Q = L_MAX;
      double check_other_scale = runOptions->getValueOrDef<double>(0.0, "check_other_scale");
      if (check_other_scale > 0.0)
      {
        if (is_at_Q)
        {
          // get likelihood at check_other_scale
          THDM_spectrum_container container_at_scale;
          BEreq::init_THDM_spectrum_container_CONV(container_at_scale, *Dep::THDM_spectrum, byVal(yukawa_type), byVal(check_other_scale), 0);
          loglike_at_Q = likelihood_function(container_at_scale);
        }
        else
        {
          // print warning if we ask for likelihood at check_other_scale but not using FS model
          print_calculation_at_scale_warning("get_perturbativity_likelihood_THDM");
        }
      }
      // return the worse performing likelihood
      result = std::min(loglike, loglike_at_Q);
    }

    void get_stability_likelihood_THDM(double &result)
    {
      using namespace Pipes::get_stability_likelihood_THDM;
      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      bool is_at_Q = false;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          is_at_Q = THDM_model.second.is_model_at_Q;
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // define likelihood function to use
      std::function<double(THDM_spectrum_container &)> likelihood_function = stability_likelihood_THDM;
      // create container
      THDM_spectrum_container container;
      // initialise container at Qin - this is where the 2HDMC is configured
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);
      // evaluate loglike
      const double loglike = likelihood_function(container);
      // note that we may alos check SpecBit's likelihoods at a different scale: check_other_scale
      double loglike_at_Q = L_MAX;
      double check_other_scale = runOptions->getValueOrDef<double>(0.0, "check_other_scale");
      if (check_other_scale > 0.0)
      {
        if (is_at_Q)
        {
          // get likelihood at check_other_scale
          THDM_spectrum_container container_at_scale;
          BEreq::init_THDM_spectrum_container_CONV(container_at_scale, *Dep::THDM_spectrum, byVal(yukawa_type), byVal(check_other_scale), 0);
          loglike_at_Q = likelihood_function(container_at_scale);
        }
        else
        {
          // print warning if we ask for likelihood at check_other_scale but not using FS model
          print_calculation_at_scale_warning("get_stability_likelihood_THDM");
        }
      }
      // return the worse performing likelihood
      result = std::min(loglike, loglike_at_Q);
    }

    void get_alignment_likelihood_THDM(double &result)
    {
      using namespace Pipes::get_alignment_likelihood_THDM;
      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      bool is_at_Q = false;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          is_at_Q = THDM_model.second.is_model_at_Q;
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // define likelihood function to use
      std::function<double(THDM_spectrum_container &)> likelihood_function = alignment_likelihood_THDM;
      // create container
      THDM_spectrum_container container;
      // initialise container at Qin - this is where the 2HDMC is configured
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);
      // evaluate loglike
      const double loglike = likelihood_function(container);
      // note that we may alos check SpecBit's likelihoods at a different scale: check_other_scale
      double loglike_at_Q = L_MAX;
      double check_other_scale = runOptions->getValueOrDef<double>(0.0, "check_other_scale");
      if (check_other_scale > 0.0)
      {
        if (is_at_Q)
        {
          // get likelihood at check_other_scale
          THDM_spectrum_container container_at_scale;
          BEreq::init_THDM_spectrum_container_CONV(container_at_scale, *Dep::THDM_spectrum, byVal(yukawa_type), byVal(check_other_scale), 0);
          loglike_at_Q = likelihood_function(container_at_scale);
        }
        else
        {
          // print warning if we ask for likelihood at check_other_scale but not using FS model
          print_calculation_at_scale_warning("get_alignment_likelihood_THDM");
        }
      }
      // return the worse performing likelihood
      result = std::min(loglike, loglike_at_Q);
    }

    void check_vacuum_global_minimum(int &result)
    {
      using namespace Pipes::check_vacuum_global_minimum;
      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      bool is_at_Q = false;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          is_at_Q = THDM_model.second.is_model_at_Q;
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // define likelihood function to use
      std::function<double(THDM_spectrum_container &)> likelihood_function = alignment_likelihood_THDM;
      // create container
      THDM_spectrum_container container;
      // initialise container at Qin - this is where the 2HDMC is configured
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);
      // evaluate loglike
      const double loglike = likelihood_function(container);
      // note that we may alos check SpecBit's likelihoods at a different scale: check_other_scale
      int loglike_at_Q = 1;
      double check_other_scale = runOptions->getValueOrDef<double>(0.0, "check_other_scale");
      if (check_other_scale > 0.0)
      {
        if (is_at_Q)
        {
          // get likelihood at check_other_scale
          THDM_spectrum_container container_at_scale;
          BEreq::init_THDM_spectrum_container_CONV(container_at_scale, *Dep::THDM_spectrum, byVal(yukawa_type), byVal(check_other_scale), 0);
          loglike_at_Q = likelihood_function(container_at_scale);
        }
        else
        {
          // print warning if we ask for likelihood at check_other_scale but not using FS model
          print_calculation_at_scale_warning("check_vacuum_global_minimum");
        }
      }
      // return the worse performing likelihood
      result = (loglike && loglike_at_Q);
    }

    void check_h0_loop_order_corrections(double &result)
    {
      using namespace Pipes::check_h0_loop_order_corrections;
      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // define likelihood function to use
      std::function<double(THDM_spectrum_container &)> likelihood_function = loop_correction_mass_splitting_h0_THDM;
      // create container
      THDM_spectrum_container container;
      // initialise container at Qin - this is where the 2HDMC is configured
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);
      // evaluate loglike
      const double loglike = likelihood_function(container);
      // note that we may alos check SpecBit's likelihoods at a different scale: check_other_scale
      double loglike_at_Q = L_MAX;
      double check_other_scale = runOptions->getValueOrDef<double>(0.0, "check_other_scale");
      if (check_other_scale > 0.0)
      {
        // get likelihood at check_other_scale
        THDM_spectrum_container container_at_scale;
        BEreq::init_THDM_spectrum_container_CONV(container_at_scale, *Dep::THDM_spectrum, byVal(yukawa_type), byVal(check_other_scale), 0);
        loglike_at_Q = likelihood_function(container_at_scale);
      }
      // return the worse performing likelihood
      result = std::min(loglike, loglike_at_Q);
    }

    void check_THDM_scalar_loop_order_corrections(double &result)
    {
      using namespace Pipes::check_THDM_scalar_loop_order_corrections;
      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // define likelihood function to use
      std::function<double(THDM_spectrum_container &)> likelihood_function = loop_correction_mass_splitting_h0_THDM;
      // create container
      THDM_spectrum_container container;
      // initialise container at Qin - this is where the 2HDMC is configured
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);
      // evaluate loglike
      const double loglike = likelihood_function(container);
      // note that we may alos check SpecBit's likelihoods at a different scale: check_other_scale
      double loglike_at_Q = L_MAX;
      double check_other_scale = runOptions->getValueOrDef<double>(0.0, "check_other_scale");
      if (check_other_scale > 0.0)
      {
        // get likelihood at check_other_scale
        THDM_spectrum_container container_at_scale;
        BEreq::init_THDM_spectrum_container_CONV(container_at_scale, *Dep::THDM_spectrum, byVal(yukawa_type), byVal(check_other_scale), 0);
        loglike_at_Q = likelihood_function(container_at_scale);
      }
      // return the worse performing likelihood
      result = std::min(loglike, loglike_at_Q);
    }

    void check_THDM_scalar_masses(double &result)
    {
      using namespace Pipes::check_THDM_scalar_masses;
      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // define likelihood function to use
      std::function<double(THDM_spectrum_container &, const double, const double)> likelihood_function = scalar_masses_THDM;
      // create container
      THDM_spectrum_container container;
      // initialise container at Qin - this is where the 2HDMC is configured
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);
      const double infinity = std::numeric_limits<double>::infinity();
      const double max_scalar_mass = runOptions->getValueOrDef<double>(infinity, "maximum_scalar_mass");
      const double min_scalar_mass = runOptions->getValueOrDef<double>(-1.0*infinity, "minimum_scalar_mass");
      // evaluate loglike
      const double loglike = likelihood_function(container, min_scalar_mass, max_scalar_mass);
      // note that we may also check SpecBit's likelihoods at a different scale: check_other_scale
      double loglike_at_Q = L_MAX;
      double check_other_scale = runOptions->getValueOrDef<double>(0.0, "check_other_scale");
      if (check_other_scale > 0.0)
      {
        // get likelihood at check_other_scale
        THDM_spectrum_container container_at_scale;
        BEreq::init_THDM_spectrum_container_CONV(container_at_scale, *Dep::THDM_spectrum, byVal(yukawa_type), byVal(check_other_scale), 0);
        loglike_at_Q = likelihood_function(container_at_scale, min_scalar_mass, max_scalar_mass);
      }
      // return the worse performing likelihood
      result = std::min(loglike, loglike_at_Q);
    }
    /// @} end likelihood helper functions

    /// @{ likelihood functions
    //  ============================================================

    // only compatible with Z-2 aligned models
    // use this if we require the LO eigenvalues to be ordered
    std::vector<std::complex<double>> get_LO_scattering_eigenvalues_ordered(THDM_spectrum_container &container)
    {
      std::vector<double> lambda;
      std::vector<std::complex<double>> lo_eigenvalues;
      lambda = get_lambdas_from_spectrum(container);
      check_Z2(lambda[6], lambda[7], "get_LO_scattering_eigenvalues_ordered");

      // a00
      std::complex<double> a00_even_plus = 1.0 / 2.0 * (3.0 * (lambda[1] + lambda[2]) + sqrt(9.0 * pow((lambda[1] - lambda[2]), 2) + 4.0 * pow((2.0 * lambda[3] + lambda[4]), 2)));
      std::complex<double> a00_even_minus = 1.0 / 2.0 * (3.0 * (lambda[1] + lambda[2]) - sqrt(9.0 * pow((lambda[1] - lambda[2]), 2) + 4.0 * pow((2.0 * lambda[3] + lambda[4]), 2)));
      std::complex<double> a00_odd_plus = lambda[3] + 2.0 * lambda[4] + 3.0 * lambda[5];
      std::complex<double> a00_odd_minus = lambda[3] + 2.0 * lambda[4] - 3.0 * lambda[5];
      // a01
      std::complex<double> a01_even_plus = 1.0 / 2.0 * (lambda[1] + lambda[2] + sqrt(pow((lambda[1] - lambda[2]), 2) + 4.0 * pow(lambda[4], 2)));
      std::complex<double> a01_even_minus = 1.0 / 2.0 * (lambda[1] + lambda[2] - sqrt(pow((lambda[1] - lambda[2]), 2) + 4.0 * pow(lambda[4], 2)));
      std::complex<double> a01_odd_plus = lambda[3] + lambda[5];
      std::complex<double> a01_odd_minus = lambda[3] - lambda[5];
      // a20
      std::complex<double> a20_odd = lambda[3] - lambda[4];
      // a21
      std::complex<double> a21_even_plus = 1.0 / 2.0 * (lambda[1] + lambda[2] + sqrt(pow((lambda[1] - lambda[2]), 2) + 4.0 * pow(lambda[5], 2)));
      std::complex<double> a21_even_minus = 1.0 / 2.0 * (lambda[1] + lambda[2] - sqrt(pow((lambda[1] - lambda[2]), 2) + 4.0 * pow(lambda[5], 2)));
      std::complex<double> a21_odd = lambda[3] + lambda[4];

      return {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus,
              a01_even_minus, a01_odd_plus, a01_odd_minus, a20_odd, a21_even_plus, a21_even_minus, a21_odd};
    }

    // these are not ordered and depend on the order than Eigen gives which is not guarenteed
    // uses std::complex values
    std::vector<std::complex<double>> get_LO_scattering_eigenvalues(THDM_spectrum_container &container)
    {
      std::vector<double> lambda;
      std::vector<std::complex<double>> lo_eigenvalues;
      lambda = get_lambdas_from_spectrum(container);

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
      std::complex<double> S_20 = lambda[3] - lambda[4];
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

    // - LO unitarity likelihood
    // ---------------------------------------------------------------------
    double unitarity_likelihood_THDM(THDM_spectrum_container &container)
    {
      const std::complex<double> i(0.0, 1.0);

      std::vector<std::complex<double>> LO_eigenvalues = get_LO_scattering_eigenvalues(container);
      //set constraint values
      //-----------------------------
      // all values < 8*PI for unitarity conditions
      const double unitarity_upper_limit = 8 * M_PI; // !!!! 8 pi using conditions given in ivanov paper (used by 2hdmc)
      const double sigma = 0.1;
      //-----------------------------
      //calculate the total error of each point
      double error = 0.0;
      for (auto const &eachEig : LO_eigenvalues)
      {
        if (abs(eachEig) > unitarity_upper_limit)
          error += abs(eachEig) - unitarity_upper_limit;
      }

      static point_counter count("unitarity LL"); count.count();
      if (error > 0.0) count.count_invalid();

      return Stats::gaussian_upper_limit(error, 0.0, 0.0, sigma, false);
    }

    // - NLO unitarity likelihood
    // ---------------------------------------------------------------------
    double NLO_unitarity_likelihood_THDM(THDM_spectrum_container &container, const bool check_correction_ratio, const bool wave_function_corrections, const bool gauge_corrections, const bool yukawa_corrections)
    {
      const std::complex<double> i(0.0, 1.0);

      std::vector<std::complex<double>> NLO_eigenvalues = get_NLO_scattering_eigenvalues(container, wave_function_corrections, gauge_corrections, yukawa_corrections);

      const double unitarity_upper_limit = 0.50; // !!!!
      const double sigma = 0.01;
      double error = 0.0;
      double error_ratio = 0.0;

#ifdef SPECBIT_DEBUG
      // int counter_nlo = 0;
      // std::vector<string> nlo_eig_names = {"a00_even_plus", "a00_even_minus", "a00_odd_plus", "a00_odd_minus",
      //                                      "a01_even_plus", "a01_even_minus", "a01_odd_plus", "a01_odd_minus", "a10_odd", "a11_even_plus",
      //                                      "a11_even_minus", "a11_odd"};
#endif

      for (auto const &eig : NLO_eigenvalues)
      {
        if (abs(eig - i / 2.0) > unitarity_upper_limit)
        {
          error += abs(eig - i / 2.0) - unitarity_upper_limit;
        }
#ifdef SPECBIT_DEBUG
        // std::cout << nlo_eig_names[counter_nlo] << ": " << eig << " | " << abs(eig - i / 2) << std::endl;
        // counter_nlo++;
#endif
      }
      if (check_correction_ratio)
      {
        std::vector<std::complex<double>> LO_eigenvalues = get_LO_scattering_eigenvalues_ordered(container);
        // flip order of plus/minus to match conventions
        std::vector<int> LO_eigenvalue_order = {2, 1, 4, 3, 6, 5, 8, 7, 9, 11, 10, 12};
        for (size_t num = 0; num < LO_eigenvalues.size(); num++)
        {
          // needs to be normalized in accordance to NLO unitarity
          std::complex<double> LO_eigenvalue = -(LO_eigenvalues[LO_eigenvalue_order[num]]) / (32.0 * M_PI * M_PI);
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

      static point_counter count("NLO unitarity LL"); count.count();
      if (error > 0.0) count.count_invalid();
      static point_counter count2("NLO/LO unitarity ratio LL"); count2.count();
      if (error_ratio > 0.0) count2.count_invalid();

      return Stats::gaussian_upper_limit(error + error_ratio, 0.0, 0.0, sigma, false);
    }

    // - perturbativity likelihood (simple)
    // only checks that couplings are less than 4pi
    // ---------------------------------------------------------------------
    double perturbativity_likelihood_simple_THDM(THDM_spectrum_container &container)
    {
      // check lambda_i (generic couplings)
      //-----------------------------
      // all values < 4*PI for perturbativity conditions
      const double perturbativity_upper_limit = 4 * M_PI;
      const double sigma = 0.1;
      //-----------------------------
      double error = 0.0;
      std::vector<double> lambda = get_lambdas_from_spectrum(container);
      // loop over all lambdas
      for (auto const &each_lambda : lambda)
      {
        if (abs(each_lambda) > perturbativity_upper_limit)
          error += abs(each_lambda) - perturbativity_upper_limit;
      }

      static point_counter count("simple perturbativity LL"); count.count();
      if (error > 0.0) count.count_invalid();

      return Stats::gaussian_upper_limit(error, 0.0, 0.0, sigma, false);
    }

    // - perturbativity likelihood
    // checks that all quartic couplings are less than 4pi
    // ---------------------------------------------------------------------
    double perturbativity_likelihood_THDM(THDM_spectrum_container &container)
    {
      //-----------------------------
      // all values < 4*PI for perturbativity conditions
      const double perturbativity_upper_limit = 4 * M_PI; // !!!!!
      const double sigma = 0.1;
      //-----------------------------
      double error = 0.0;
      double previous_coupling = 0.0;
      // using generic model so calculate chi^2 from all possible 4 higgs interactions
      std::complex<double> hhhh_coupling;
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
                hhhh_coupling = get_quartic_coupling_higgs(container, (particle_type)p1, (particle_type)p2, (particle_type)p3, (particle_type)p4);
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

      static point_counter count("perturbativity LL"); count.count();
      if (error > 0.0) count.count_invalid();

      return Stats::gaussian_upper_limit(error, 0.0, 0.0, sigma, false);
    }

    // - stability likelihood
    // ---------------------------------------------------------------------
    double stability_likelihood_THDM(THDM_spectrum_container &container)
    {
      std::vector<double> lambda(8);
      double m122, tanb;
      const double sigma = 0.01;
      double error = 0.;

      container.THDM_object->get_param_gen(lambda[1], lambda[2], lambda[3], lambda[4], lambda[5], lambda[6], lambda[7], m122, tanb);

      //do the full check first - if fails continue with chi^2 calculation to guide scanner
      if (!container.THDM_object->check_stability())
      {
        if (lambda[1] < 0.0)
          error += abs(lambda[1]);
        if (lambda[2] < 0.0)
          error += abs(lambda[2]);

        if (std::isnan(sqrt(lambda[1] * lambda[2])))
        {
          return -L_MAX;
        }
        else
        {
          if (lambda[3] < -sqrt(lambda[1] * lambda[2]))
            error += abs(lambda[3] - (-sqrt(lambda[1] * lambda[2])));
          if (lambda[6] == 0.0 || lambda[7] == 0.0)
          {
            if (lambda[3] + lambda[4] - abs(lambda[5]) < -sqrt(lambda[1] * lambda[2]))
              error += abs(lambda[3] + lambda[4] - abs(lambda[5]) - (-sqrt(lambda[1] * lambda[2])));
          }
          else
          {
            if (lambda[3] + lambda[4] - lambda[5] < -sqrt(lambda[1] * lambda[2]))
              error += abs(lambda[3] + lambda[4] - lambda[5] - (-sqrt(lambda[1] * lambda[2])));
          }
        }
      }

      static point_counter count("stability LL"); count.count();
      if (error > 0.0) count.count_invalid();

      return Stats::gaussian_upper_limit(error, 0.0, 0.0, sigma, false);
    }

    // - alignment likelihood
    // ---------------------------------------------------------------------
    void higgs_mass_LL(double& result)
    {
      using namespace Pipes::higgs_mass_LL;

      // get THDM yukawa type and find out if it is a FS spectrum (at Q)
      int yukawa_type = -1;
      bool is_at_Q = false;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          is_at_Q = THDM_model.second.is_model_at_Q;
          yukawa_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // create container
      THDM_spectrum_container container;
      // initialise container at Qin - this is where the 2HDMC is configured
      BEreq::init_THDM_spectrum_container_CONV(container, *Dep::THDM_spectrum, byVal(yukawa_type), 0.0, 0);
      const double mh_pole = container.he->get(Par::Pole_Mass, "h0", 1);

      // const Spectrum spec = *Dep::THDM_spectrum;
      // std::unique_ptr<SubSpectrum> he = spec.clone_HE();
      // const double mh_pole = he->get(Par::Pole_Mass, "m_h");

      constexpr double mh = 125.10; // experimental value of Higgs mass measured by others GeV
      constexpr double mh_err = 0.14; // uncertainty GeV

      double mh_diff = std::max(0.0, std::abs(mh_pole - mh) - mh_err*20);

      result = -10 * mh_diff / (1.0*mh_err);


      // std::cout << "mass: " << mh_pole << "  | LL: " << result << std::endl;
    }

        // - alignment likelihood
    // ---------------------------------------------------------------------
    double alignment_likelihood_THDM(THDM_spectrum_container &container)
    {
      double b = atan(container.he->get(Par::dimensionless, "tanb")), a = container.he->get(Par::dimensionless, "alpha");
      double sba = sin(b - a);
      //-----------------------------
      // sin(b-a) = 1 in alignment limit - the tolerance gives the distance from alignment limit:
      const double sba_tolerance = 0.01;
      const double sigma = 0.1;
      //-----------------------------
      // loglike function
      return Stats::gaussian_upper_limit((1.0 - sba), sba_tolerance, 0.0, sigma, false);
    }

    // - vacuum metastability constraint
    // (arXiv 1303.5098v1)
    // calculates the global minimum discriminant D
    // D>0 is a necessary & sufficient condition to have a global minimum
    // Z2-aligned models only
    // ---------------------------------------------------------------------
    double global_minimum_discriminant_THDM(THDM_spectrum_container &container)
    {
      const double lambda1 = container.he->get(Par::mass1, "lambda_1");
      const double lambda2 = container.he->get(Par::mass1, "lambda_2");
      const double lambda6 = container.he->get(Par::mass1, "lambda_6");
      const double lambda7 = container.he->get(Par::mass1, "lambda_7");
      const double tb = container.he->get(Par::dimensionless, "tanb");
      const double m12_2 = container.he->get(Par::mass1, "m12_2");

      // check that model is Z2 conserving
      if (!check_Z2(lambda6, lambda7, "global_minimum_discriminant_THDM"))
        return 0.0;

      // minimization conditions to recover m11^2 and m22^2
      const double m11_2 = container.he->get(Par::mass1, "m11_2"); //m12_2*tb - 1/(2*v2)*(lambda1*cb2 + (lambda3+lambda4+lambda5)*sb2 + 3*lambda6*sb*cb + lambda7*sb2*tb);
      const double m22_2 = container.he->get(Par::mass1, "m22_2"); //m12_2*ctb - 1/(2*v2)*(lambda2*sb2 + (lambda3+lambda4+lambda5)*cb2 + lambda6*cb2*ctb + 3*lambda7*sb*cb);

      const std::complex<double> k = pow((std::complex<double>(lambda1) / std::complex<double>(lambda2)), 0.25);
      // the 'dicriminant', if this value is greater than zero then we have only one vacuum and it is global
      const std::complex<double> discriminant = m12_2 * (m11_2 - pow(k, 2) * m22_2) * (tb - k);

      // check for NaN - should *not* happen but has crashed scans before. Most probable culprit is k when lambda_2 = 0. TODO: find workaround
      if (std::isnan(discriminant.real()) || std::isnan(discriminant.imag()))
      {
        std::ostringstream msg;
        msg << "SpecBit warning (non-fatal): global_minimum_discriminant_likelihood_THDM is returning NaN. Ivnvalidating point. Reporting calculated values:"
            << " k= " << k << ", m11^2 = " << m11_2 << ", m22^2 = " << m22_2 << std::endl;
        SpecBit_warning().raise(LOCAL_INFO, msg.str());
        std::cerr << msg.str();
        invalid_point().raise(msg.str());
      }

      // calculate error & loglike
      if (discriminant.real() < 0.0)
        return 0;
      if (discriminant.imag() < 0.0)
        return 0;

      return 1;
    }

    // - loop correction constraint on h0
    // ---------------------------------------------------------------------
    double loop_correction_mass_splitting_h0_THDM(THDM_spectrum_container &container)
    {
      const double mh_running = container.he->get(Par::mass1, "h0", 1), mh_pole = container.he->get(Par::Pole_Mass, "h0", 1);
      const double mh_splitting = abs(mh_pole - mh_running);
      const double lower_limit = mh_running * 0.5;
      if (mh_splitting > lower_limit)
        return -L_MAX;
      return 0.0;
    }

    // - loop correction constraint on H0
    // ---------------------------------------------------------------------
    double loop_correction_mass_splitting_H0_THDM(THDM_spectrum_container &container)
    {
      const double mh_running = container.he->get(Par::mass1, "h0", 2), mh_pole = container.he->get(Par::Pole_Mass, "h0", 2);
      const double mh_splitting = abs(mh_pole - mh_running);
      const double lower_limit = mh_running * 0.5;
      if (mh_splitting > lower_limit)
        return -L_MAX;
      return 0.0;
    }

    // - loop correction constraint on A0
    // ---------------------------------------------------------------------
    double loop_correction_mass_splitting_A0_THDM(THDM_spectrum_container &container)
    {
      const double mh_running = container.he->get(Par::mass1, "A0"), mh_pole = container.he->get(Par::Pole_Mass, "A0");
      const double mh_splitting = abs(mh_pole - mh_running);
      const double lower_limit = mh_running * 0.5;
      if (mh_splitting > lower_limit)
        return -L_MAX;
      return 0.0;
    }

    // - loop correction constraint on H+/H-
    // ---------------------------------------------------------------------
    double loop_correction_mass_splitting_Hpm_THDM(THDM_spectrum_container &container)
    {
      const double mh_running = container.he->get(Par::mass1, "H+"), mh_pole = container.he->get(Par::Pole_Mass, "H+");
      const double mh_splitting = abs(mh_pole - mh_running);
      const double lower_limit = mh_running * 0.5;
      if (mh_splitting > lower_limit)
        return -L_MAX;
      return 0.0;
    }

    // - loop correction constraint on H0,A0 & H+/H-
    // ---------------------------------------------------------------------
    double loop_correction_mass_splitting_scalar_THDM(THDM_spectrum_container &container)
    {
      double loglike = loop_correction_mass_splitting_H0_THDM(container);
      loglike += loop_correction_mass_splitting_A0_THDM(container);
      loglike += loop_correction_mass_splitting_Hpm_THDM(container);
      return loglike;
    }

    // enforces an upper limit on the heavy scalar masses from the yaml
    // ---------------------------------------------------------------------
    double scalar_masses_THDM(THDM_spectrum_container &container, const double min_scalar_mass, const double max_scalar_mass)
    {
      const double mH0 = container.he->get(Par::Pole_Mass, "h0", 2);
      if (mH0 < min_scalar_mass || mH0 > max_scalar_mass)
        return -L_MAX;
      const double mA0 = container.he->get(Par::Pole_Mass, "A0");
      if (mA0 < min_scalar_mass || mA0 > max_scalar_mass)
        return -L_MAX;
      const double mHp = container.he->get(Par::Pole_Mass, "H+");
      if (mHp < min_scalar_mass || mHp > max_scalar_mass)
        return -L_MAX;
      return 0;
    }

    /// @} end likelihoods

    /// @{ observables
    //  ============================================================

    void obs_sba(double &result)
    {
      using namespace Pipes::obs_sba;
      const Spectrum spec = *Dep::THDM_spectrum;
      std::unique_ptr<SubSpectrum> he = spec.clone_HE();
      const double beta = he->get(Par::dimensionless, "beta");
      const double alpha = he->get(Par::dimensionless, "alpha");
      result = sin(beta - alpha);
    }

    double obs_cbaa(double &result)
    {
      using namespace Pipes::obs_cbaa;

      // const Spectrum spec = *Dep::THDM_spectrum;
      // std::unique_ptr<SubSpectrum> he = spec.clone_HE();
      // const double beta = he->get(Par::dimensionless, "beta");
      // const double alpha = he->get(Par::dimensionless, "alpha");
      // result = cos(beta - alpha);

      const Spectrum spec = *Dep::THDM_spectrum;
      std::unique_ptr<SubSpectrum> he = spec.clone_HE();
      const double beta = he->get(Par::dimensionless, "beta");
      const double alpha = he->get(Par::dimensionless, "alpha");

      double cba = std::cos(beta-alpha);
      result = std::log(1e-20 + (1.0 - std::exp(-10.0*cba*cba)));
    }

    void obs_cba(double &result)
    {
      using namespace Pipes::obs_cba;
      const Spectrum spec = *Dep::THDM_spectrum;
      std::unique_ptr<SubSpectrum> he = spec.clone_HE();
      const double beta = he->get(Par::dimensionless, "beta");
      const double alpha = he->get(Par::dimensionless, "alpha");
      result = cos(beta - alpha);
    }

    void obs_ba(double &result)
    {
      using namespace Pipes::obs_ba;
      const Spectrum spec = *Dep::THDM_spectrum;
      std::unique_ptr<SubSpectrum> he = spec.clone_HE();
      const double beta = he->get(Par::dimensionless, "beta");
      const double alpha = he->get(Par::dimensionless, "alpha");
      result = beta - alpha;
    }

    void obs_vev(double &result)
    {
      using namespace Pipes::obs_vev;
      const Spectrum spec = *Dep::THDM_spectrum;
      std::unique_ptr<SubSpectrum> he = spec.clone_HE();
      result = he->get(Par::mass1, "vev");
    }

    /// @} end observables

    /// @{ functions to fill the Higgs coupling table
    //  ============================================================

    /// Put together the Higgs couplings for the THDM, from partial widths only
    void THDM_higgs_couplings_pwid(HiggsCouplingsTable &result)
    {
      using namespace Pipes::THDM_higgs_couplings_pwid;

      // Retrieve spectrum contents
      const Spectrum fullspectrum = *Dep::THDM_spectrum;

      //const DecayTable::Entry& decays = *Dep::Higgs_decay_rates;
      const SubSpectrum &spec = fullspectrum.get_HE();

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
      
      // give higgs indicies names
      enum neutral_higgs_indicies {
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

    // fill necessary couplings from 2HDMC to create the THDM higgs couplings table
    // todo: save computational time by filling only those required in each case
    void fill_THDM_couplings_struct(THDM_couplings &couplings, THDM_spectrum_container &container)
    {
      // give higgs indicies names
      enum neutral_higgs_indicies {
          light_higgs, heavy_higgs, CP_odd_higgs, NUMBER_OF_NEUTRAL_HIGGS
      };
      // note: the below does not include degenerate charged higgs
      enum charged_higgs_indicies {
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
    
    // ~~ 21 ~~ (get higgs couplings from THDMC)
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
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

       // give higgs indicies names
      enum neutral_higgs_indicies {
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

      // set THDM model type
      int y_type = -1;
      for (auto const &THDM_model : THDM_model_lookup_map)
      {
        // model match was found: set values based on matched model
        if (ModelInUse(THDM_model.first))
        {
          y_type = THDM_model.second.model_y_type;
          break;
        }
      }
      // Initiate 2HDM container
      THDM_spectrum_container container;
      BEreq::init_THDM_spectrum_container_CONV(container, fullspectrum, byVal(y_type), 0.0, 0);

      // set up and fill the THDM couplings
      THDM_couplings couplings;
      fill_THDM_couplings_struct(couplings, container);

      // SM-like couplings
      std::vector<THDM_couplings> couplings_SM_like;
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

    void fill_map_from_THDMspectrum(std::map<std::string, double> &specmap, const Spectrum &thdmspec);

    void get_THDM_spectrum_as_map(std::map<std::string, double> &specmap)
    {
      namespace myPipe = Pipes::get_THDM_spectrum_as_map;
      const Spectrum &thdmspec(*myPipe::Dep::THDM_spectrum);
      fill_map_from_THDMspectrum(specmap, thdmspec);
    }

    void fill_map_from_THDMspectrum(std::map<std::string, double> &specmap, const Spectrum &thdmspec)
    {
      /// Add everything... use spectrum contents routines to automate task
      static const SpectrumContents::THDM contents;
      static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters();

      for (std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin();
           it != required_parameters.end(); ++it)
      {
        const Par::Tags tag = it->tag();
        const std::string name = it->name();
        const std::vector<int> shape = it->shape();

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
            for (int j = 1; j <= shape[0]; ++j)
            {
              std::ostringstream label;
              label << name << "_(" << i << "," << j << ") " << Par::toString.at(tag);
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
    }

    /// @} end functions to fill Higgs coupling table

  } // end namespace SpecBit
} // end namespace Gambit
