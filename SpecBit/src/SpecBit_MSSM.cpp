//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit
///
///  These functions link ModelParameters to
///  Spectrum objects in various ways (by running
///  spectrum generators, etc.)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2014 Sep - Dec, 2015 Jan - Mar
///
///  \author Christopher Rogan
///          (christophersrogan@gmail.com)
///  \date 2015 Apr
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 June
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015, 2016
///
///  *********************************************

#include <string>
#include <sstream>
#include <cmath>
#include <complex>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
#include "gambit/Elements/smlike_higgs.hpp"
#include "gambit/Models/SimpleSpectra/MSSMSimpleSpec.hpp"
#include "gambit/Utils/stream_overloads.hpp" // Just for more convenient output to logger
#include "gambit/Utils/util_macros.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/SpecBit/MSSMSpec.hpp"
#include "gambit/SpecBit/model_files_and_boxes.hpp" // #includes lots of flexiblesusy headers and defines interface classes

// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/src/ew_input.hpp"
#include "flexiblesusy/src/lowe.h" // From softsusy; used by flexiblesusy
#include "flexiblesusy/src/numerics2.hpp"
//#include "flexiblesusy/src/mssm_twoloophiggs.hpp"
#include "flexiblesusy/src/spectrum_generator_settings.hpp"

// Switch for debug mode
//#define SPECBIT_DEBUG

namespace Gambit
{

  namespace SpecBit
  {
    using namespace LogTags;
    using namespace flexiblesusy;

    // To check if a model is currently being scanned:
    // bool Pipes::<fname>::ModelInUse(str model_name)

    /// @{ Non-Gambit convenience functions
    //  =======================================================================
    //  These are not known to Gambit, but they do basically all the real work.
    //  The Gambit module functions merely wrap the functions here and hook
    //  them up to their dependencies, and input parameters.

    /// Compute an MSSM spectrum using flexiblesusy
    // In GAMBIT there are THREE flexiblesusy MSSM spectrum generators currently in
    // use, for each of three possible boundary condition types:
    //   - GUT scale input
    //   - Electroweak symmetry breaking scale input
    //   - Intermediate scale Q input
    // These each require slightly different setup, but once that is done the rest
    // of the code required to run them is the same; this is what is contained in
    // the below template function.
    // MI for Model Interface, as defined in model_files_and_boxes.hpp
    template <class MI>
    Spectrum run_FS_spectrum_generator
        ( const typename MI::InputParameters& input
        , const SMInputs& sminputs
        , const Options& runOptions
        , const std::map<str, safe_ptr<const double> >& input_Param
        )
    {
      // SoftSUSY object used to set quark and lepton masses and gauge
      // couplings in QEDxQCD effective theory
      // Will be initialised by default using values in lowe.h, which we will
      // override next.
      softsusy::QedQcd oneset;

      // Fill QedQcd object with SMInputs values
      setup_QedQcd(oneset,sminputs);

      // Run everything to Mz
      //oneset.toMz();

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
      settings.set(Spectrum_generator_settings::precision, runOptions.getValueOrDef<double>(1.0e-4,"precision_goal"));
      settings.set(Spectrum_generator_settings::max_iterations, runOptions.getValueOrDef<double>(0,"max_iterations"));
      settings.set(Spectrum_generator_settings::calculate_sm_masses, runOptions.getValueOrDef<bool> (false, "calculate_sm_masses"));
      settings.set(Spectrum_generator_settings::pole_mass_loop_order, runOptions.getValueOrDef<int>(2,"pole_mass_loop_order"));
      settings.set(Spectrum_generator_settings::pole_mass_loop_order, runOptions.getValueOrDef<int>(2,"ewsb_loop_order"));
      settings.set(Spectrum_generator_settings::beta_loop_order, runOptions.getValueOrDef<int>(2,"beta_loop_order"));
      settings.set(Spectrum_generator_settings::threshold_corrections_loop_order, runOptions.getValueOrDef<int>(2,"threshold_corrections_loop_order"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_as, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_at_as"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_ab_as, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_ab_as"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_at, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_at_at"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_atau_atau, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_atau_atau"));
      settings.set(Spectrum_generator_settings::top_pole_qcd_corrections, runOptions.getValueOrDef<int>(1,"top_pole_qcd_corrections"));
      settings.set(Spectrum_generator_settings::beta_zero_threshold, runOptions.getValueOrDef<double>(1.000000000e-14,"beta_zero_threshold"));
      settings.set(Spectrum_generator_settings::eft_matching_loop_order_up, runOptions.getValueOrDef<int>(1,"eft_matching_loop_order_up"));
      settings.set(Spectrum_generator_settings::eft_matching_loop_order_down, runOptions.getValueOrDef<int>(1,"eft_matching_loop_order_down"));
      settings.set(Spectrum_generator_settings::threshold_corrections, runOptions.getValueOrDef<int>(123111321,"threshold_corrections"));


      spectrum_generator.set_settings(settings);

      // Generate spectrum
      spectrum_generator.run(oneset, input);

      // Extract report on problems...
      const typename MI::Problems& problems = spectrum_generator.get_problems();

      // Create Model_interface to carry the input and results, and know
      // how to access the flexiblesusy routines.
      // Note: Output of spectrum_generator.get_model() returns type, e.g. CMSSM.
      // Need to convert it to type CMSSM_slha (which alters some conventions of
      // parameters into SLHA format)
      MI model_interface(spectrum_generator,oneset,input);

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
      MSSMSpec<MI> mssmspec(model_interface, "FlexibleSUSY", "2.0.beta");

      // Add extra information about the scales used to the wrapper object
      // (last parameter turns on the 'allow_new' option for the override setter, which allows
      //  us to set parameters that don't previously exist)
      mssmspec.set_override(Par::mass1,spectrum_generator.get_high_scale(),"high_scale",true);
      mssmspec.set_override(Par::mass1,spectrum_generator.get_susy_scale(),"susy_scale",true);
      mssmspec.set_override(Par::mass1,spectrum_generator.get_low_scale(), "low_scale", true);


      // Has the user chosen to override any pole mass values?
      // This will typically break consistency, but may be useful in some special cases
      if (runOptions.hasKey("override_FS_pole_masses"))
      {
        std::vector<str> particle_names = runOptions.getNames("override_FS_pole_masses");
        for (auto& name : particle_names)
        {
          double mass = runOptions.getValue<double>("override_FS_pole_masses", name);
          mssmspec.set_override(Par::Pole_Mass, mass, name);
        }
      }

      // Add theory errors
      static const MSSM_strs ms;

      static const std::vector<int> i12     = initVector(1,2);
      static const std::vector<int> i123    = initVector(1,2,3);
      static const std::vector<int> i1234   = initVector(1,2,3,4);
      static const std::vector<int> i123456 = initVector(1,2,3,4,5,6);

      // 3% theory "error"
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_pred, true);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_pred, true);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_6, i123456, true);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_6, i123456, true);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, "~chi0", i1234, true);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, "~chi0", i1234, true);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_3, i123, true);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_3, i123, true);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_2, i12,  true);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_2, i12,  true);

      // Do the lightest Higgs mass separately.  The default in most codes is 3 GeV. That seems like
      // an underestimate if the stop masses are heavy enough, but an overestimate for most points.
      double rd_mh1 = 2.0 / mssmspec.get(Par::Pole_Mass, ms.h0, 1);
      mssmspec.set_override(Par::Pole_Mass_1srd_high, rd_mh1, ms.h0, 1, true);
      mssmspec.set_override(Par::Pole_Mass_1srd_low,  rd_mh1, ms.h0, 1, true);

      // Do the W mass separately.  Here we use 10 MeV based on the size of corrections from two-loop papers and advice from Dominik Stockinger.
      double rd_mW = 0.01 / mssmspec.get(Par::Pole_Mass, "W+");
      mssmspec.set_override(Par::Pole_Mass_1srd_high, rd_mW, "W+", true);
      mssmspec.set_override(Par::Pole_Mass_1srd_low,  rd_mW, "W+", true);

      // Save the input value of TanBeta
      // Probably need to make it a full requirement of the MSSM SpectrumContents
      if(input_Param.find("TanBeta") != input_Param.end())
      {
        mssmspec.set_override(Par::dimensionless, *input_Param.at("TanBeta"), "tanbeta(mZ)", true);
      }

      // Create a second SubSpectrum object to wrap the qedqcd object used to initialise the spectrum generator
      // Attach the sminputs object as well, so that SM pole masses can be passed on (these aren't easily
      // extracted from the QedQcd object, so use the values that we put into it.)
      QedQcdWrapper qedqcdspec(oneset,sminputs);

      // Deal with points where spectrum generator encountered a problem
      #ifdef SPECBIT_DEBUG
        std::cout<<"Problem? "<<problems.have_problem()<<std::endl;
      #endif
      if( problems.have_problem() )
      {
         if( runOptions.getValueOrDef<bool>(false,"invalid_point_fatal") )
         {
            ///TODO: Need to tell gambit that the spectrum is not viable somehow. For now
            /// just die.
            std::ostringstream errmsg;
            errmsg << "A serious problem was encountered during spectrum generation!; ";
            errmsg << "Message from FlexibleSUSY below:" << std::endl;
            problems.print_problems(errmsg);
            problems.print_warnings(errmsg);
            SpecBit_error().raise(LOCAL_INFO,errmsg.str());
         }
         else
         {
            /// Check what the problem was
            /// see: contrib/MassSpectra/flexiblesusy/src/problems.hpp
            std::ostringstream msg;
            //msg << "";
            //if( have_bad_mass()      ) msg << "bad mass " << std::endl; // TODO: check which one
            //if( have_tachyon()       ) msg << "tachyon" << std::endl;
            //if( have_thrown()        ) msg << "error" << std::endl;
            //if( have_non_perturbative_parameter()   ) msg << "non-perturb. param" << std::endl; // TODO: check which
            //if( have_failed_pole_mass_convergence() ) msg << "fail pole mass converg." << std::endl; // TODO: check which
            //if( no_ewsb()            ) msg << "no ewsb" << std::endl;
            //if( no_convergence()     ) msg << "no converg." << std::endl;
            //if( no_perturbative()    ) msg << "no pertub." << std::endl;
            //if( no_rho_convergence() ) msg << "no rho converg." << std::endl;
            //if( msg.str()=="" ) msg << " Unrecognised problem! ";

            /// Fast way for now:
            problems.print_problems(msg);
            invalid_point().raise(msg.str()); //TODO: This message isn't ending up in the logs.
         }
      }

      if( problems.have_warning() )
      {
         std::ostringstream msg;
         problems.print_warnings(msg);
         SpecBit_warning().raise(LOCAL_INFO,msg.str()); //TODO: Is a warning the correct thing to do here?
      }

      // Write SLHA file (for debugging purposes...)
      #ifdef SPECBIT_DEBUG
         typename MI::SlhaIo slha_io;
         slha_io.set_spinfo(problems);
         slha_io.set_sminputs(oneset);
         slha_io.set_minpar(input);
         slha_io.set_extpar(input);
         slha_io.set_spectrum(mssmspec.model_interface.model);
         slha_io.write_to_file("SpecBit/initial_CMSSM_spectrum->slha");
      #endif

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = runOptions.getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = runOptions.getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // Package QedQcd SubSpectrum object, MSSM SubSpectrum object, and SMInputs struct into a 'full' Spectrum object
      return Spectrum(qedqcdspec,mssmspec,sminputs,&input_Param,mass_cut,mass_ratio_cut);
    }

  //Version for 1.5.1 commented out because we should make it possible to support FS versions in parallel.

  // template <class MI>
  //   Spectrum run_FS1_5_1_spectrum_generator
  //       ( const typename MI::InputParameters& input
  //       , const SMInputs& sminputs
  //       , const Options& runOptions
  //       , const std::map<str, safe_ptr<const double> >& input_Param
  //       )
  //   {
  //     // SoftSUSY object used to set quark and lepton masses and gauge
  //     // couplings in QEDxQCD effective theory
  //     // Will be initialised by default using values in lowe.h, which we will
  //     // override next.
  //     softsusy::QedQcd oneset;

  //     // Fill QedQcd object with SMInputs values
  //     setup_QedQcd(oneset,sminputs);

  //     // Run everything to Mz
  //     oneset.toMz();

  //     // Create spectrum generator object
  //     typename MI::SpectrumGenerator spectrum_generator;

  //     // Spectrum generator settings
  //     // Default options copied from flexiblesusy/src/spectrum_generator_settings.hpp
  //     //
  //     // | enum                             | possible values              | default value   |
  //     // |----------------------------------|------------------------------|-----------------|
  //     // | precision                        | any positive double          | 1.0e-4          |
  //     // | max_iterations                   | any positive double          | 0 (= automatic) |
  //     // | algorithm                        | 0 (two-scale) or 1 (lattice) | 0 (= two-scale) |
  //     // | calculate_sm_masses              | 0 (no) or 1 (yes)            | 0 (= no)        |
  //     // | pole_mass_loop_order             | 0, 1, 2                      | 2 (= 2-loop)    |
  //     // | ewsb_loop_order                  | 0, 1, 2                      | 2 (= 2-loop)    |
  //     // | beta_loop_order                  | 0, 1, 2                      | 2 (= 2-loop)    |
  //     // | threshold_corrections_loop_order | 0, 1                         | 1 (= 1-loop)    |
  //     // | higgs_2loop_correction_at_as     | 0, 1                         | 1 (= enabled)   |
  //     // | higgs_2loop_correction_ab_as     | 0, 1                         | 1 (= enabled)   |
  //     // | higgs_2loop_correction_at_at     | 0, 1                         | 1 (= enabled)   |
  //     // | higgs_2loop_correction_atau_atau | 0, 1                         | 1 (= enabled)   |

  //     spectrum_generator.set_precision_goal                  (runOptions.getValueOrDef<double>(1.0e-4,"precision_goal"));
  //     spectrum_generator.set_max_iterations                  (runOptions.getValueOrDef<double>(0,     "max_iterations"));
  //     spectrum_generator.set_calculate_sm_masses             (runOptions.getValueOrDef<bool>  (false, "calculate_sm_masses"));
  //     spectrum_generator.set_pole_mass_loop_order            (runOptions.getValueOrDef<int>   (2,     "pole_mass_loop_order"));
  //     spectrum_generator.set_ewsb_loop_order                 (runOptions.getValueOrDef<int>   (2,     "ewsb_loop_order"));
  //     spectrum_generator.set_beta_loop_order                 (runOptions.getValueOrDef<int>   (2,     "beta_loop_order"));
  //     spectrum_generator.set_threshold_corrections_loop_order(runOptions.getValueOrDef<int>   (2,     "threshold_corrections_loop_order"));

  //     // Higgs loop corrections are a little different... sort them out now
  //     Two_loop_corrections two_loop_settings;

  //     // alpha_t alpha_s
  //     // alpha_b alpha_s
  //     // alpha_t^2 + alpha_t alpha_b + alpha_b^2
  //     // alpha_tau^2
  //     two_loop_settings.higgs_at_as = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_at_as");
  //     two_loop_settings.higgs_ab_as = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_ab_as");
  //     two_loop_settings.higgs_at_at = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_at_at");
  //     two_loop_settings.higgs_atau_atau = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_atau_atau");

  //     spectrum_generator.set_two_loop_corrections(two_loop_settings);

  //     // Generate spectrum
  //     spectrum_generator.run(oneset, input);

  //     // Extract report on problems...
  //     const typename MI::Problems& problems = spectrum_generator.get_problems();

  //     // Create Model_interface to carry the input and results, and know
  //     // how to access the flexiblesusy routines.
  //     // Note: Output of spectrum_generator.get_model() returns type, e.g. CMSSM.
  //     // Need to convert it to type CMSSM_slha (which alters some conventions of
  //     // parameters into SLHA format)
  //     MI model_interface(spectrum_generator,oneset,input);

  //     // Create SubSpectrum object to wrap flexiblesusy data
  //     // THIS IS STATIC so that it lives on once we leave this module function. We
  //     // therefore cannot run the same spectrum generator twice in the same loop and
  //     // maintain the spectrum resulting from both. But we should never want to do
  //     // this.
  //     // A pointer to this object is what gets turned into a SubSpectrum pointer and
  //     // passed around Gambit.
  //     //
  //     // This object will COPY the interface data members into itself, so it is now the
  //     // one-stop-shop for all spectrum information, including the model interface object.
  //     MSSMSpec<MI> mssmspec(model_interface, "FlexibleSUSY", "1.5.1");

  //     // Add extra information about the scales used to the wrapper object
  //     // (last parameter turns on the 'allow_new' option for the override setter, which allows
  //     //  us to set parameters that don't previously exist)
  //     mssmspec.set_override(Par::mass1,spectrum_generator.get_high_scale(),"high_scale",true);
  //     mssmspec.set_override(Par::mass1,spectrum_generator.get_susy_scale(),"susy_scale",true);
  //     mssmspec.set_override(Par::mass1,spectrum_generator.get_low_scale(), "low_scale", true);

  //     // Add theory errors
  //     static const MSSM_strs ms;

  //     static const std::vector<int> i12     = initVector(1,2);
  //     static const std::vector<int> i123    = initVector(1,2,3);
  //     static const std::vector<int> i1234   = initVector(1,2,3,4);
  //     static const std::vector<int> i123456 = initVector(1,2,3,4,5,6);

  //     // 3% theory "error"
  //     mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_pred, true);
  //     mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_pred, true);
  //     mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_6, i123456, true);
  //     mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_6, i123456, true);
  //     mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, "~chi0", i1234, true);
  //     mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, "~chi0", i1234, true);
  //     mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_3, i123, true);
  //     mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_3, i123, true);
  //     mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_2, i12,  true);
  //     mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_2, i12,  true);

  //     // Do the lightest Higgs mass separately.  The default in most codes is 3 GeV. That seems like
  //     // an underestimate if the stop masses are heavy enough, but an overestimate for most points.
  //     double rd_mh1 = 2.0 / mssmspec.get(Par::Pole_Mass, ms.h0, 1);
  //     mssmspec.set_override(Par::Pole_Mass_1srd_high, rd_mh1, ms.h0, 1, true);
  //     mssmspec.set_override(Par::Pole_Mass_1srd_low,  rd_mh1, ms.h0, 1, true);

  //     // Do the W mass separately.  Here we use 10 MeV based on the size of corrections from two-loop papers and advice from Dominik Stockinger.
  //     double rd_mW = 0.01 / mssmspec.get(Par::Pole_Mass, "W+");
  //     mssmspec.set_override(Par::Pole_Mass_1srd_high, rd_mW, "W+", true);
  //     mssmspec.set_override(Par::Pole_Mass_1srd_low,  rd_mW, "W+", true);

  //     // Save the input value of TanBeta
  //     // Probably need to make it a full requirement of the MSSM SpectrumContents
  //     if(input_Param.find("TanBeta") != input_Param.end())
  //     {
  //       mssmspec.set_override(Par::dimensionless, *input_Param.at("TanBeta"), "tanbeta(mZ)", true);
  //     }

  //     // Create a second SubSpectrum object to wrap the qedqcd object used to initialise the spectrum generator
  //     // Attach the sminputs object as well, so that SM pole masses can be passed on (these aren't easily
  //     // extracted from the QedQcd object, so use the values that we put into it.)
  //     QedQcdWrapper qedqcdspec(oneset,sminputs);

  //     // Deal with points where spectrum generator encountered a problem
  //     #ifdef SPECBIT_DEBUG
  //       std::cout<<"Problem? "<<problems.have_problem()<<std::endl;
  //     #endif
  //     if( problems.have_problem() )
  //     {
  //        if( runOptions.getValueOrDef<bool>(false,"invalid_point_fatal") )
  //        {
  //           ///TODO: Need to tell gambit that the spectrum is not viable somehow. For now
  //           /// just die.
  //           std::ostringstream errmsg;
  //           errmsg << "A serious problem was encountered during spectrum generation!; ";
  //           errmsg << "Message from FlexibleSUSY below:" << std::endl;
  //           problems.print_problems(errmsg);
  //           problems.print_warnings(errmsg);
  //           SpecBit_error().raise(LOCAL_INFO,errmsg.str());
  //        }
  //        else
  //        {
  //           /// Check what the problem was
  //           /// see: contrib/MassSpectra/flexiblesusy/src/problems.hpp
  //           std::ostringstream msg;
  //           //msg << "";
  //           //if( have_bad_mass()      ) msg << "bad mass " << std::endl; // TODO: check which one
  //           //if( have_tachyon()       ) msg << "tachyon" << std::endl;
  //           //if( have_thrown()        ) msg << "error" << std::endl;
  //           //if( have_non_perturbative_parameter()   ) msg << "non-perturb. param" << std::endl; // TODO: check which
  //           //if( have_failed_pole_mass_convergence() ) msg << "fail pole mass converg." << std::endl; // TODO: check which
  //           //if( no_ewsb()            ) msg << "no ewsb" << std::endl;
  //           //if( no_convergence()     ) msg << "no converg." << std::endl;
  //           //if( no_perturbative()    ) msg << "no pertub." << std::endl;
  //           //if( no_rho_convergence() ) msg << "no rho converg." << std::endl;
  //           //if( msg.str()=="" ) msg << " Unrecognised problem! ";

  //           /// Fast way for now:
  //           problems.print_problems(msg);
  //           invalid_point().raise(msg.str()); //TODO: This message isn't ending up in the logs.
  //        }
  //     }

  //     if( problems.have_warning() )
  //     {
  //        std::ostringstream msg;
  //        problems.print_warnings(msg);
  //        SpecBit_warning().raise(LOCAL_INFO,msg.str()); //TODO: Is a warning the correct thing to do here?
  //     }

  //     // Write SLHA file (for debugging purposes...)
  //     #ifdef SPECBIT_DEBUG
  //        typename MI::SlhaIo slha_io;
  //        slha_io.set_spinfo(problems);
  //        slha_io.set_sminputs(oneset);
  //        slha_io.set_minpar(input);
  //        slha_io.set_extpar(input);
  //        slha_io.set_spectrum(mssmspec.model_interface.model);
  //        slha_io.write_to_file("SpecBit/initial_CMSSM_spectrum->slha");
  //     #endif

  //     // Retrieve any mass cuts
  //     static const Spectrum::mc_info mass_cut = runOptions.getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
  //     static const Spectrum::mr_info mass_ratio_cut = runOptions.getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

  //     // Package QedQcd SubSpectrum object, MSSM SubSpectrum object, and SMInputs struct into a 'full' Spectrum object
  //     return Spectrum(qedqcdspec,mssmspec,sminputs,&input_Param,mass_cut,mass_ratio_cut);
  //   }

    /// Helper function for setting 3x3 matrix-valued parameters
    //  Names must conform to convention "<parname>_ij"
    Eigen::Matrix<double,3,3> fill_3x3_parameter_matrix(const std::string& rootname, const std::map<str, safe_ptr<const double> >& Param)
    {
       Eigen::Matrix<double,3,3> output;
       for(int i=0; i<3; ++i) for(int j=0; j<3; ++j)
       {
          output(i,j) = *Param.at(rootname + "_" + std::to_string(i+1) + std::to_string(j+1));
       }
       return output;
    }

    /// As above, but for symmetric input (i.e. 6 entries, assumed to be the upper triangle)
    Eigen::Matrix<double,3,3> fill_3x3_symmetric_parameter_matrix(const std::string& rootname, const std::map<str, safe_ptr<const double> >& Param)
    {
       Eigen::Matrix<double,3,3> output;
       for(int i=0; i<3; ++i) for(int j=0; j<3; ++j)
       {
         str parname = rootname + "_" + ( i < j ? std::to_string(i+1) + std::to_string(j+1) : std::to_string(j+1) + std::to_string(i+1));
         output(i,j) = *Param.at(parname);
       }
       return output;
    }

    /// Helper function for filling MSSM63-compatible input parameter objects
    /// Leaves out mHu2, mHd2, SignMu, (mA, mu) because we use two different parameterisations of these
    template <class T>
    void fill_MSSM63_input(T& input, const std::map<str, safe_ptr<const double> >& Param )
    {
      //double valued parameters
      input.TanBeta     = *Param.at("TanBeta");
      input.MassBInput  = *Param.at("M1");
      input.MassWBInput = *Param.at("M2");
      input.MassGInput  = *Param.at("M3");

      // Sanity checks
      if(input.TanBeta<0)
      {
         std::ostringstream msg;
         msg << "Tried to set TanBeta parameter to a negative value ("<<input.TanBeta<<")! This parameter must be positive. Please check your inifile and try again.";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }

      //3x3 matrices; filled with the help of a convenience function
      input.mq2Input = fill_3x3_symmetric_parameter_matrix("mq2", Param);
      input.ml2Input = fill_3x3_symmetric_parameter_matrix("ml2", Param);
      input.md2Input = fill_3x3_symmetric_parameter_matrix("md2", Param);
      input.mu2Input = fill_3x3_symmetric_parameter_matrix("mu2", Param);
      input.me2Input = fill_3x3_symmetric_parameter_matrix("me2", Param);
      input.Aeij = fill_3x3_parameter_matrix("Ae", Param);
      input.Adij = fill_3x3_parameter_matrix("Ad", Param);
      input.Auij = fill_3x3_parameter_matrix("Au", Param);

      #ifdef SPECBIT_DEBUG
        #define INPUT(p) input.p
        #define ostr std::cout
        #define oend std::endl
        ostr << "TanBeta = " << INPUT(TanBeta) << ", " << oend ;
        ostr << "mq2Input = " << oend << INPUT(mq2Input) << ", " << oend;
        ostr << "ml2Input = " << oend << INPUT(ml2Input) << ", " << oend;
        ostr << "md2Input = " << oend << INPUT(md2Input) << ", " << oend;
        ostr << "mu2Input = " << oend << INPUT(mu2Input) << ", " << oend;
        ostr << "me2Input = " << oend << INPUT(me2Input) << ", " << oend;
        ostr << "MassBInput = " << INPUT(MassBInput) << ", " << oend;
        ostr << "MassWBInput = " << INPUT(MassWBInput) << ", " << oend;
        ostr << "MassGInput = " << INPUT(MassGInput) << ", " << oend;
        ostr << "Aeij = " << oend << INPUT(Aeij) << ", " << oend;
        ostr << "Adij = " << oend << INPUT(Adij) << ", " << oend;
        ostr << "Auij = " << oend << INPUT(Auij) << ", " << oend;
        #undef INPUT
        #undef ostr
        #undef oend
      #endif
    }


  // Similar to above, except this is for MSSMEFTHiggs spectrum
  // generator and a few others where different names for inputs for many
  // parameters are used. This should be standardised.

    template <class T>
    void fill_MSSM63_input_altnames(T& input, const std::map<str, safe_ptr<const double> >& Param )
    {
      //double valued parameters
      input.TanBeta     = *Param.at("TanBeta");
      input.M1Input  = *Param.at("M1");
      input.M2Input = *Param.at("M2");
      input.M3Input  = *Param.at("M3");

      // Sanity checks
      if(input.TanBeta<0)
      {
         std::ostringstream msg;
         msg << "Tried to set TanBeta parameter to a negative value ("<<input.TanBeta<<")! This parameter must be positive. Please check your inifile and try again.";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }

      //3x3 matrices; filled with the help of a convenience function
      input.mq2Input = fill_3x3_symmetric_parameter_matrix("mq2", Param);
      input.ml2Input = fill_3x3_symmetric_parameter_matrix("ml2", Param);
      input.md2Input = fill_3x3_symmetric_parameter_matrix("md2", Param);
      input.mu2Input = fill_3x3_symmetric_parameter_matrix("mu2", Param);
      input.me2Input = fill_3x3_symmetric_parameter_matrix("me2", Param);
      input.AeInput = fill_3x3_parameter_matrix("Ae", Param);
      input.AdInput= fill_3x3_parameter_matrix("Ad", Param);
      input.AuInput = fill_3x3_parameter_matrix("Au", Param);

      #ifdef SPECBIT_DEBUG
        #define INPUT(p) input.p
        #define ostr std::cout
        #define oend std::endl
        ostr << "TanBeta = " << INPUT(TanBeta) << ", " << oend ;
        ostr << "mq2Input = " << oend << INPUT(mq2Input) << ", " << oend;
        ostr << "ml2Input = " << oend << INPUT(ml2Input) << ", " << oend;
        ostr << "md2Input = " << oend << INPUT(md2Input) << ", " << oend;
        ostr << "mu2Input = " << oend << INPUT(mu2Input) << ", " << oend;
        ostr << "me2Input = " << oend << INPUT(me2Input) << ", " << oend;
        ostr << "M1Input = " << INPUT(M1Input) << ", " << oend;
        ostr << "M2Input = " << INPUT(M2Input) << ", " << oend;
        ostr << "M3Input = " << INPUT(M3Input) << ", " << oend;
        ostr << "AeInput = " << oend << INPUT(AeInput) << ", " << oend;
        ostr << "AdInput = " << oend << INPUT(AdInput) << ", " << oend;
        ostr << "AuInput = " << oend << INPUT(AuInput) << ", " << oend;
        #undef INPUT
        #undef ostr
        #undef oend
      #endif

    }


    /// Check that the spectrum has a neutralino LSP.
    bool has_neutralino_LSP(const Spectrum& result)
    {
      double msqd  = result.get(Par::Pole_Mass, 1000001, 0);
      double msqu  = result.get(Par::Pole_Mass, 1000002, 0);
      double msl   = result.get(Par::Pole_Mass, 1000011, 0);
      double msneu = result.get(Par::Pole_Mass, 1000012, 0);
      double mglui = result.get(Par::Pole_Mass, 1000021, 0);
      double mchi0 = std::abs(result.get(Par::Pole_Mass, 1000022, 0));
      double mchip = std::abs(result.get(Par::Pole_Mass, 1000024, 0));

      return mchi0 < mchip &&
             mchi0 < mglui &&
             mchi0 < msl   &&
             mchi0 < msneu &&
             mchi0 < msqu  &&
             mchi0 < msqd;
    }
    /// Helper to work with pointer
    bool has_neutralino_LSP(const Spectrum* result)
    {
      return has_neutralino_LSP(*result);
    }


    /// @} End module convenience functions


    /// @{ Gambit module functions
    //  =======================================================================
    //  These are wrapped up in Gambit functor objects according to the
    //  instructions in the rollcall header

    // Functions to change the capability associated with a Spectrum object to "SM_spectrum"
    void convert_MSSM_to_SM   (Spectrum &result) {result = *Pipes::convert_MSSM_to_SM::Dep::MSSM_spectrum;}
    void convert_NMSSM_to_SM  (Spectrum &result) {result = *Pipes::convert_NMSSM_to_SM::Dep::NMSSM_spectrum;}
    void convert_E6MSSM_to_SM (Spectrum &result) {result = *Pipes::convert_E6MSSM_to_SM::Dep::E6MSSM_spectrum;}

    void get_MSSM_spectrum_SPheno (Spectrum& spectrum)
    {
      namespace myPipe = Pipes::get_MSSM_spectrum_SPheno;
      const SMInputs &sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      Finputs inputs;
      inputs.sminputs = sminputs;
      inputs.param = myPipe::Param;
      inputs.options = myPipe::runOptions;

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // Get the spectrum from the Backend
      myPipe::BEreq::SPheno_MSSMspectrum(spectrum, inputs);

    }

  // Runs FlexibleSUSY MSSMEFTHiggs model spectrum generator with SUSY
  // scale boundary conditions, ie accepts MSSM parameters at MSUSY,
  // and has DRbar mA and mu as an input and mHu2 and mHd2 as EWSB
  // outputs, so it is for the MSSMatMSUSY_mA model.
  #if(FS_MODEL_MSSMatMSUSYEFTHiggs_mAmu_IS_BUILT)
  void get_MSSMatMSUSY_mA_spectrum_FlexibleEFTHiggs (Spectrum& result)
  {
     // Access the pipes for this function to get model and parameter information
     namespace myPipe = Pipes::get_MSSMatMSUSY_mA_spectrum_FlexibleEFTHiggs;

     // Get SLHA2 SMINPUTS values
     const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

     // Get input parameters (from flexiblesusy namespace)
     MSSMatMSUSYEFTHiggs_mAmu_input_parameters input;
     input.MuInput  = *myPipe::Param.at("mu");
     // This FS spectrum generator has mA as the parameter
     input.mAInput = *myPipe::Param.at("mA");
     fill_MSSM63_input_altnames(input,myPipe::Param); // Fill the rest
     result = run_FS_spectrum_generator<MSSMatMSUSYEFTHiggs_mAmu_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);

      // Only allow neutralino LSPs.
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");

      // Drop SLHA files if requested
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");

  }
  #endif

  // Runs FlexibleSUSY MSSMEFTHiggs model spectrum generator
  // and has m3^2 and mu as EWSB outputs, so it is for the
  // MSSMatQ_model.
  #if(FS_MODEL_MSSMEFTHiggs_IS_BUILT)
  void get_MSSMatQ_spectrum_FlexibleEFTHiggs (Spectrum& result)
  {
     // Access the pipes for this function to get model and parameter information
     namespace myPipe = Pipes::get_MSSMatQ_spectrum_FlexibleEFTHiggs;

     // Get SLHA2 SMINPUTS values
     const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

     // Get input parameters (from flexiblesusy namespace)
     MSSMEFTHiggs_input_parameters input;
     // MSSMatQ also requires input scale to be supplied with name MSUSY
     input.MSUSY  = *myPipe::Param.at("Qin");
     input.mHu2IN = *myPipe::Param.at("mHu2");
     input.mHd2IN = *myPipe::Param.at("mHd2");
     input.SignMu = *myPipe::Param.at("SignMu");
     fill_MSSM63_input_altnames(input,myPipe::Param); // Fill the rest
     result = run_FS_spectrum_generator<MSSMEFTHiggs_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);

      // Only allow neutralino LSPs.
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");

      // Drop SLHA files if requested
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");

   }
   #endif

   // Runs FlexibleSUSY MSSMEFTHiggs_mAmu spectrum generator with
   // boundary conditions at a user specified scale, ie accepts MSSM
   // parameters at Q, and has DRbar mA and mu as an input and mHu2
   // and mHd2 as EWSB outputs, so it is for the MSSMatMSUSY_mA model.
   #if(FS_MODEL_MSSMEFTHiggs_mAmu_IS_BUILT)
   void get_MSSMatQ_mA_spectrum_FlexibleEFTHiggs (Spectrum& result)
   {
     // Access the pipes for this function to get model and parameter information
     namespace myPipe = Pipes::get_MSSMatQ_mA_spectrum_FlexibleEFTHiggs;

     // Get SLHA2 SMINPUTS values
     const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

     // Get input parameters (from flexiblesusy namespace)
     MSSMEFTHiggs_mAmu_input_parameters input;
     input.MuInput  = *myPipe::Param.at("mu");
     // This FS spectrum generator has mA as the parameter
     input.mAInput = *myPipe::Param.at("mA");
     // Note: Qin has been named MSUSY inside the spectrum generator
     // but it is a user-input scale in this case.
     input.MSUSY = *myPipe::Param.at("Qin");
     // Fill the rest.
     // Note: This particular spectrum generator has been created with
     // different names for parameter inputs.  We should standardise this
     fill_MSSM63_input_altnames(input,myPipe::Param);
     result = run_FS_spectrum_generator<MSSMEFTHiggs_mAmu_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);

      // Only allow neutralino LSPs.
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");

      // Drop SLHA files if requested
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");

   }
   #endif



    // Runs FlexibleSUSY MSSM spectrum generator with CMSSM (GUT scale) boundary conditions
    // In principle an identical spectrum can be obtained from the function
    // get_MSSMatGUT_spectrum_FS
    // by setting the input parameters to match the CMSSM assumptions
    #if(FS_MODEL_CMSSM_IS_BUILT)
    void get_CMSSM_spectrum_FS (Spectrum& result)
    {

      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_CMSSM_spectrum_FS;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Get input parameters (from flexiblesusy namespace)
      CMSSM_input_parameters input;

      input.m0      = *myPipe::Param["M0"];
      input.m12     = *myPipe::Param["M12"];
      input.TanBeta = *myPipe::Param["TanBeta"];
      input.SignMu  = *myPipe::Param["SignMu"];
      input.Azero   = *myPipe::Param["A0"];

      // Sanity checks
      if(input.TanBeta<0)
      {
         std::ostringstream msg;
         msg << "Tried to set TanBeta parameter to a negative value ("<<input.TanBeta<<")! This parameter must be positive. Please check your inifile and try again.";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }
      if(input.SignMu!=-1 and input.SignMu!=1)
      {
         std::ostringstream msg;
         msg << "Tried to set SignMu parameter to a value that is not a sign! ("<<input.SignMu<<")! This parameter must be set to either 1 or -1. Please check your inifile and try again.";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }

      // Run spectrum generator
      result = run_FS_spectrum_generator<CMSSM_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);

      // Only allow neutralino LSPs.
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");

      // Drop SLHA files if requested
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");

    }
    #endif

    // Runs FlexibleSUSY MSSM spectrum generator with EWSB scale input (boundary conditions)
    #if(FS_MODEL_MSSM_IS_BUILT)
    void get_MSSMatQ_spectrum_FS (Spectrum& result)
    {
      using namespace softsusy;
      namespace myPipe = Pipes::get_MSSMatQ_spectrum_FS;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      MSSM_input_parameters input;
      input.Qin    = *myPipe::Param.at("Qin"); // MSSMatQ also requires input scale to be supplied
      input.mHu2IN = *myPipe::Param.at("mHu2");
      input.mHd2IN = *myPipe::Param.at("mHd2");
      input.SignMu = *myPipe::Param.at("SignMu");
      if(input.SignMu!=-1 and input.SignMu!=1)
      {
         std::ostringstream msg;
         msg << "Tried to set SignMu parameter to a value that is not a sign! ("<<input.SignMu<<")! This parameter must be set to either 1 or -1. Please check your inifile and try again.";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }
      fill_MSSM63_input(input,myPipe::Param);
      result = run_FS_spectrum_generator<MSSM_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }
    #endif

    // Runs FlexibleSUSY MSSM spectrum generator with EWSB scale input (boundary conditions)
    // but with mA and mu as parameters instead of mHu2 and mHd2
    #if(FS_MODEL_MSSM_mAmu_IS_BUILT)
    void get_MSSMatQ_mA_spectrum_FS (Spectrum& result)
    {
      using namespace softsusy;
      namespace myPipe = Pipes::get_MSSMatQ_mA_spectrum_FS;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      MSSM_mAmu_input_parameters input;
      input.Qin      = *myPipe::Param.at("Qin"); // MSSMatQ also requires input scale to be supplied
      input.MuInput  = *myPipe::Param.at("mu");
      // Note this spectrum generator mA2 is the parameter.
      // However this freedom is not used in GAMBIT
      // and not needed as mA is a DRbar mass eigenstate for a scalar
      double mA = *myPipe::Param.at("mA");
      input.mA2Input = mA*mA;
      fill_MSSM63_input(input,myPipe::Param); // Fill the rest
      result = run_FS_spectrum_generator<MSSM_mAmu_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }
    #endif

    // Runs FlexibleSUSY MSSM spectrum generator with GUT scale input (boundary conditions)
    #if(FS_MODEL_MSSMatMGUT_IS_BUILT)
    void get_MSSMatMGUT_spectrum_FS (Spectrum& result)
    {
      using namespace softsusy;
      namespace myPipe = Pipes::get_MSSMatMGUT_spectrum_FS;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      MSSMatMGUT_input_parameters input;
      input.mHu2IN = *myPipe::Param.at("mHu2");
      input.mHd2IN = *myPipe::Param.at("mHd2");
      input.SignMu = *myPipe::Param.at("SignMu");
      if(input.SignMu!=-1 and input.SignMu!=1)
      {
         std::ostringstream msg;
         msg << "Tried to set SignMu parameter to a value that is not a sign! ("<<input.SignMu<<")! This parameter must be set to either 1 or -1. Please check your inifile and try again.";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }
      fill_MSSM63_input(input,myPipe::Param);
      result = run_FS_spectrum_generator<MSSMatMGUT_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }
    #endif

  // Runs FlexibleSUSY MSSMatMGUTEFTHiggs model spectrum generator
  // and has m3^2 and mu as EWSB outputs, so it is for the
  // MSSMatMGUT_model.
  #if(FS_MODEL_MSSMatMGUTEFTHiggs_IS_BUILT)
  void get_MSSMatMGUT_spectrum_FlexibleEFTHiggs (Spectrum& result)
  {
     // Access the pipes for this function to get model and parameter information
     namespace myPipe = Pipes::get_MSSMatMGUT_spectrum_FlexibleEFTHiggs;

     // Get SLHA2 SMINPUTS values
     const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

     // Get input parameters (from flexiblesusy namespace)
     MSSMatMGUTEFTHiggs_input_parameters input;
     input.mHu2IN = *myPipe::Param.at("mHu2");
     input.mHd2IN = *myPipe::Param.at("mHd2");
     input.SignMu = *myPipe::Param.at("SignMu");
     if(input.SignMu!=-1 and input.SignMu!=1)
      {
         std::ostringstream msg;
         msg << "Tried to set SignMu parameter to a value that is not a sign! ("<<input.SignMu<<")! This parameter must be set to either 1 or -1. Please check your inifile and try again.";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }

     fill_MSSM63_input(input,myPipe::Param); // Fill the rest
     result = run_FS_spectrum_generator<MSSMatMGUTEFTHiggs_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);

      // Only allow neutralino LSPs.
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");

      // Drop SLHA files if requested
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");

   }
   #endif


    // Runs FlexibleSUSY MSSM spectrum generator with GUT scale input (boundary conditions)
    // but with mA and mu as parameters instead of mHu2 and mHd2
    #if(FS_MODEL_MSSMatMGUT_mAmu_IS_BUILT)
    void get_MSSMatMGUT_mA_spectrum_FS (Spectrum& result)
    {
      using namespace softsusy;
      namespace myPipe = Pipes::get_MSSMatMGUT_mA_spectrum_FS;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      MSSMatMGUT_mAmu_input_parameters input;
      input.MuInput  = *myPipe::Param.at("mu");
      // Note this spectrum generator mA2 is the parameter.
      // However this freedom is not used in GAMBIT
      // and not needed as mA is a DRbar mass eigenstate for a scalar
      double mA = *myPipe::Param.at("mA");
      input.mA2Input = mA*mA;
      fill_MSSM63_input(input,myPipe::Param); // Fill the rest
      result = run_FS_spectrum_generator<MSSMatMGUT_mAmu_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }
    #endif

  // Runs FlexibleSUSY MSSMatMGUTEFTHiggs model spectrum generator
  // and has m3^2 and mu as EWSB outputs, so it is for the
  // MSSMatMGUT_model.
  #if(FS_MODEL_MSSMatMGUTEFTHiggs_mAmu_IS_BUILT)
  void get_MSSMatMGUT_mA_spectrum_FlexibleEFTHiggs (Spectrum& result)
  {
     // Access the pipes for this function to get model and parameter information
     namespace myPipe = Pipes::get_MSSMatMGUT_mA_spectrum_FlexibleEFTHiggs;

     // Get SLHA2 SMINPUTS values
     const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

     // Get input parameters (from flexiblesusy namespace)
     MSSMatMGUTEFTHiggs_mAmu_input_parameters input;
     input.MuInput  = *myPipe::Param.at("mu");
     // Note this spectrum generator mA2 is the parameter.
     // However this freedom is not used in GAMBIT
     // and not needed as mA is a DRbar mass eigenstate for a scalar
     double mA = *myPipe::Param.at("mA");
     input.mA2Input = mA*mA;

     fill_MSSM63_input(input,myPipe::Param); // Fill the rest
     result = run_FS_spectrum_generator<MSSMatMGUTEFTHiggs_mAmu_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);

      // Only allow neutralino LSPs.
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");

      // Drop SLHA files if requested
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");

   }
   #endif


    // Runs FlexibleSUSY MSSM spectrum generator with SUSY scale input (boundary conditions)
    // but with mA and mu as parameters instead of mHu2 and mHd2
    #if(FS_MODEL_MSSMatMSUSY_mAmu_IS_BUILT)
    void get_MSSMatMSUSY_mA_spectrum_FS (Spectrum& result)
    {
      using namespace softsusy;
      namespace myPipe = Pipes::get_MSSMatMSUSY_mA_spectrum_FS;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      MSSMatMSUSY_mAmu_input_parameters input;
      input.MuInput  = *myPipe::Param.at("mu");
      // Note this spectrum generator mA2 is the parameter.
      // However this freedom is not used in GAMBIT
      // and not needed as mA is a DRbar mass eigenstate for a scalar
      double mA = *myPipe::Param.at("mA");
      input.mA2Input = mA*mA;    // FS has mA^2 as the parameter
      fill_MSSM63_input(input,myPipe::Param); // Fill the rest
      result = run_FS_spectrum_generator<MSSMatMSUSY_mAmu_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");
      result.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }
    #endif

    void get_GUTMSSMB_spectrum (Spectrum &/*result*/)
    {
      // Placeholder
    }

    /// @{
    /// Functions to decompose Spectrum object (of type MSSM_spectrum)

    /// @}
    /// Retrieve SubSpectrum* to SM LE model from Spectrum object
    /// DEPENDENCY(MSSM_spectrum, Spectrum)
    void get_SM_SubSpectrum_from_MSSM_Spectrum (const SubSpectrum* &result)
    {
      namespace myPipe = Pipes::get_SM_SubSpectrum_from_MSSM_Spectrum;
      const Spectrum& matched_spectra(*myPipe::Dep::unimproved_MSSM_spectrum);
      result = &matched_spectra.get_LE();
    }

    /// Extract an SLHAea version of the spectrum contained in a Spectrum object, in SLHA1 format
    void get_MSSM_spectrum_as_SLHAea_SLHA1(SLHAstruct &result)
    {
      result = Pipes::get_MSSM_spectrum_as_SLHAea_SLHA1::Dep::unimproved_MSSM_spectrum->getSLHAea(1);
    }

    /// Extract an SLHAea version of the spectrum contained in a Spectrum object, in SLHA2 format
    void get_MSSM_spectrum_as_SLHAea_SLHA2(SLHAstruct &result)
    {
      result = Pipes::get_MSSM_spectrum_as_SLHAea_SLHA2::Dep::unimproved_MSSM_spectrum->getSLHAea(2);
    }

    /// Get an MSSMSpectrum object from an SLHA file
    /// Wraps it up in MSSMSimpleSpec; i.e. no RGE running possible.
    /// This is mainly for testing against benchmark points, but may be a useful last
    /// resort for interacting with "difficult" spectrum generators.
    void get_MSSM_spectrum_from_SLHAfile(Spectrum &result)
    {
      // Static counter running in a loop over all filenames
      static unsigned int counter = 0;
      static long int ncycle = 1;
      SLHAstruct input_slha;

      namespace myPipe = Pipes::get_MSSM_spectrum_from_SLHAfile;

      // Read filename from yaml file
      std::vector<std::string> filenames =
        myPipe::runOptions->getValue<std::vector<std::string>>("filenames");

      // Check how many loop over the input files we are doing.
      long int cycles = myPipe::runOptions->getValueOrDef<int>(-1,"cycles");

      // Check if we have completed the requested number of cycles
      if(cycles>0 and ncycle>cycles)
      {
         std::ostringstream msg;
         msg << "Preset number of loops through input files reached! Stopping. (tried to start cycle "<<ncycle<<" of "<<cycles<<")";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }

      std::string filename = filenames[counter];

      logger() << "Reading SLHA file: " << filename << EOM;
      std::ifstream ifs(filename.c_str());
      if(!ifs.good()){ SpecBit_error().raise(LOCAL_INFO,"ERROR: SLHA file not found."); }
      ifs >> input_slha;
      ifs.close();
      counter++;
      if( counter >= filenames.size() )
      {
        logger() << "Returning to start of input SLHA file list (finished "<<ncycle<<" cycles)" << EOM;
        counter = 0;
        ncycle++;
      }

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // Create Spectrum object from the slhaea object
      result = spectrum_from_SLHAea<MSSMSimpleSpec, SLHAstruct>(input_slha, input_slha, mass_cut, mass_ratio_cut);

      // Add getter for susy scale if option set for this
      bool add_susy_scale = myPipe::runOptions->getValueOrDef<bool>(false,"assume_Q_is_MSUSY");
      if(add_susy_scale)
      {
         result.get_HE().set_override(Par::mass1,result.get_HE().GetScale(),"susy_scale",true);
      }

      // No sneaking in charged LSPs via SLHA, jävlar.
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");
    }

    /// Get an MSSMSpectrum object from an SLHAstruct
    /// Wraps it up in MSSMSimpleSpec; i.e. no RGE running possible.
    /// This can be used as a poor-man's interface to backend spectrum generators
    void get_MSSM_spectrum_from_SLHAstruct(Spectrum& result)
    {
      namespace myPipe = Pipes::get_MSSM_spectrum_from_SLHAstruct;
      const SLHAstruct& input_slha_tmp = *myPipe::Dep::unimproved_MSSM_spectrum; // Retrieve dependency on SLHAstruct

      /// @todo FIXME this needs to be fixed -- is it needed any more?  Where is this GAMBIT block supposed to be written?
      SLHAstruct input_slha(input_slha_tmp); // Copy struct (for demo adding of GAMBIT block only)
      // For example; add this to your input SLHAstruct:
      input_slha["GAMBIT"][""] << "BLOCK" << "GAMBIT";
      input_slha["GAMBIT"][""] <<      1  << 1e99 << "# Input scale";

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // Create Spectrum object from the slhaea object
      result = spectrum_from_SLHAea<MSSMSimpleSpec, SLHAstruct>(input_slha, input_slha, mass_cut, mass_ratio_cut);

      // No sneaking in charged LSPs via SLHA, jävlar.
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");

      // In order to translate from e.g. MSSM63atMGUT to MSSM63atQ, we need
      // to know that input scale Q. This is generally not stored in SLHA format,
      // but we need it, so if you want to produce a Spectrum object this way you
      // will need to add this information to your SLHAstruct:
      // BLOCK GAMBIT
      //   1     <high_scale>    # Input scale of (upper) boundary conditions, e.g. GUT scale

      // Need to check if this information exists:
      SLHAstruct::const_iterator block = input_slha.find("GAMBIT");
      std::vector<std::string> key(1, "1");
      if(block == input_slha.end() or block->find(key) == block->end())
      {
        // Big problem
        std::ostringstream errmsg;
        errmsg << "Error constructing Spectrum object from a pre-existing SLHAstruct!    " << endl
               << "The supplied SLHAstruct did not have the special GAMBIT block added.  " << endl
               << "This block carries extra information from the spectrum generator      " << endl
               << "that is usually thrown away, but which is needed for properly creating" << endl
               << "a Spectrum object. In whatever module function created the SLHAstruct " << endl
               << "that you want to use, please add code that adds the following         " << endl
               << "information to the SLHAstruct (SLHAea::Coll):                         " << endl
               << "  BLOCK GAMBIT                                                        " << endl
               << " 1 <high_scale>  # Input scale of (upper) boundary conditions, e.g. GUT scale\n";
        SpecBit_error().raise(LOCAL_INFO,errmsg.str());
      }

      // OK the GAMBIT block exists, add the data to the MSSM SubSpectrum object.
      result.get_HE().set_override(Par::mass1,SLHAea::to<double>(input_slha.at("GAMBIT").at(1).at(1)), "high_scale", false);
    }

    /// FeynHiggs SUSY masses and mixings
    void FH_MSSMMasses(fh_MSSMMassObs &result)
    {
      using namespace Pipes::FH_MSSMMasses;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FH_MSSMMasses ******" << endl;
      #endif

      // zero if minimal, non-zero if non-minimal flavour violation
      int nmfv;

      // MSf(s,t,g) MFV squark masses with indices
      // s = 1..2   sfermion index
      // t = 1..5   sfermion type nu,e,u,d,?
      // g = 1..3   generation index
      Farray<fh_real, 1,2, 1,5, 1,3> MSf;

      // USf(s1,s2,t,g) MFV squark mixing matrices with indices
      // s1 = 1..2  sfermion index (mass eigenstates)
      // s2 = 1..2  sfermion index (gauge eigenstates, L/R)
      // t  = 1..5  sfermion type nu,e,u,d,?
      // g  = 1..3  generation index
      Farray<fh_complex, 1,2, 1,2, 1,5, 1,3> USf;

      // NMFV squark masses, with indices
      // a = 1..6   extended sfermion index
      // t = 1..5   sfermion type
      Farray<fh_real, 1,6, 1,5> MASf;

      // NMFV squark mixing matrices, with indices
      // a1 = 1..6  extended sfermion index (mass eigenstates)
      // a2 = 1..6  extended sfermion index (gauge eigenstates)
      //  t = 1..5  sftermion type nu,e,u,d,?
      Farray<fh_complex, 1,36, 1,5> UASf;

      // chargino masses
      Farray<fh_real, 1,2> MCha;

      // chargino mixing matrices (mass,gauge) eigenstates (2 x 2)
      Farray<fh_complex, 1,4> UCha;
      Farray<fh_complex, 1,4> VCha;

      // neutralino masses
      Farray<fh_real, 1,4> MNeu;

      // neutralino mixing matrices (mass,gauge) eigenstates (4 x 4)
      Farray<fh_complex, 1,16> ZNeu;

      // correction to bottom Yukawa coupling
      fh_complex DeltaMB;

      // gluino mass
      fh_real MGl;

      // tree-level Higgs masses (Mh, MH, MA, MHpm)
      Farray<fh_real, 1,4> MHtree;

      // tree-level Higgs mixing parameters sin alpha
      fh_real SAtree;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FHGetPara ******" << endl;
      #endif

      int error = 1;
      BEreq::FHGetPara(error, nmfv, MSf, USf, MASf, UASf,
           MCha, UCha, VCha, MNeu, ZNeu,
           DeltaMB, MGl, MHtree, SAtree);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHGetPara raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      fh_MSSMMassObs MassObs;
      for(int i = 0; i < 2; i++)
        for(int j = 0; j < 5; j++)
          for(int k = 0; k < 3; k++)
            MassObs.MSf[i][j][k] = MSf(i+1,j+1,k+1);
      for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
          for(int k = 0; k < 5; k++)
            for(int l = 0; l < 3; l++)
              MassObs.USf[i][j][k][l] = USf(i+1,j+1,k+1,l+1);
      for(int i = 0; i < 6; i++)
        for(int j = 0; j < 5; j++)
          MassObs.MASf[i][j] = MASf(i+1,j+1);
      for(int i = 0; i < 36; i++)
        for(int j = 0; j < 5; j++)
          MassObs.UASf[i][j] = UASf(i+1,j+1);
      for(int i = 0; i < 2; i++)
        MassObs.MCha[i] = MCha(i+1);
      for(int i = 0; i < 4; i++)
      {
        MassObs.UCha[i] = UCha(i+1);
        MassObs.VCha[i] = VCha(i+1);
      }
      for(int i = 0; i < 4; i++)
        MassObs.MNeu[i] = MNeu(i+1);
      for(int i = 0; i < 16; i++)
        MassObs.ZNeu[i] = ZNeu(i+1);
      MassObs.deltaMB = DeltaMB;
      MassObs.MGl = MGl;
      for(int i = 0; i < 4; i++)
        MassObs.MHtree[i] = MHtree(i+1);
      MassObs.SinAlphatree = SAtree;

      result = MassObs;
    }


    /// Higgs masses and mixings with theoretical uncertainties
    void FH_AllHiggsMasses(fh_HiggsMassObs &result)
    {
      using namespace Pipes::FH_AllHiggsMasses;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FH_HiggsMasses ******" << endl;
      #endif

      // Higgs mass with
      // 0 - m1 (Mh in rMSSM)
      // 1 - m2 (MH in rMSSM)
      // 2 - m3 (MA in rMSSM)
      // 3 - MHpm
      Farray<fh_real, 1,4> MHiggs;
      Farray<fh_real, 1,4> DeltaMHiggs;

      // sine of effective Higgs mixing angle, alpha_eff
      fh_complex SAeff;
      fh_complex DeltaSAeff;

      // matrix needed to rotate Higgs
      // mass matrix to diagonal form
      Farray<fh_complex, 1,3, 1,3> UHiggs;
      Farray<fh_complex, 1,3, 1,3> DeltaUHiggs;

      // matrix of Z-factors needed to combine
      // amplitudes involving on-shell Higgs
      Farray<fh_complex, 1,3, 1,3> ZHiggs;
      Farray<fh_complex, 1,3, 1,3> DeltaZHiggs;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FHHiggsCorr ******" << endl;
      #endif

      int error = 1;
      BEreq::FHHiggsCorr(error, MHiggs, SAeff, UHiggs, ZHiggs);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHHiggsCorr raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FHUncertainties ******" << endl;
      #endif

      error = 1;
      BEreq::FHUncertainties(error, DeltaMHiggs, DeltaSAeff, DeltaUHiggs, DeltaZHiggs);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHUncertainties raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      fh_HiggsMassObs HiggsMassObs;
      for(int i = 0; i < 4; i++)
      {
        HiggsMassObs.MH[i] = MHiggs(i+1);
        HiggsMassObs.deltaMH[i] = DeltaMHiggs(i+1);
      }
      HiggsMassObs.SinAlphaEff = SAeff;
      HiggsMassObs.deltaSinAlphaEff = DeltaSAeff;
      for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
          HiggsMassObs.UH[i][j] = UHiggs(i+1,j+1);
          HiggsMassObs.deltaUH[i][j] = DeltaUHiggs(i+1,j+1);
          HiggsMassObs.ZH[i][j] = ZHiggs(i+1,j+1);
          HiggsMassObs.deltaZH[i][j] = DeltaZHiggs(i+1,j+1);
        }

      result = HiggsMassObs;
    }

////////////////////////
//// Higgs routines ////
////////////////////////

    /// Call FH_Couplings from FeynHiggs and collect the output
    void FH_Couplings(fh_Couplings &result)
    {
      using namespace Pipes::FH_Couplings;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FH_Couplings ******" << endl;
      #endif

      // what to use for internal Higgs mixing
      // (ex. in couplings)
      // (default = 1)
      // 0 - no mixing
      // 1 - UHiggs
      // 2 - ZHiggs
      int uzint = 2;
      // what to use for external Higgs mixing
      // (ex. in decays)
      // (default = 2)
      // 0 - no mixing
      // 1 - UHiggs
      // 2 - ZHiggs
      int uzext = 2;
      // which effective bottom mass to use
      int mfeff = 1;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FHSelectUZ ******" << endl;
      #endif

      int error = 1;
      BEreq::FHSelectUZ(error, uzint, uzext, mfeff);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHSelectUZ raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      Farray<fh_complex, 1,ncouplings> couplings;        // MSSM Higgs couplings
      Farray<fh_complex, 1,ncouplingsms> couplings_sm;  // SM Higgs couplings
      Farray<fh_real, 1,ngammas> gammas;                // Higgs decay widths and BR's (MSSM)
      Farray<fh_real, 1,ngammasms> gammas_sm;           // Higgs decay widths and BR's (SM)
      int fast = 1;  // include off-diagonal fermion decays? (1 = no)

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FHCouplings ******" << endl;
      #endif

      error = 1;
      BEreq::FHCouplings(error, couplings, couplings_sm,
                         gammas, gammas_sm, fast);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHCouplings raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      fh_Couplings Couplings;
      for(int i = 0; i < ncouplings; i++) Couplings.couplings[i] = couplings(i+1);
      for(int i = 0; i < ncouplingsms; i++) Couplings.couplings_sm[i] = couplings_sm(i+1);
      for(int i = 0; i < ngammas; i++) Couplings.gammas[i] = gammas(i+1);
      for(int i = 0; i < ngammasms; i++) Couplings.gammas_sm[i] = gammas_sm(i+1);
      Couplings.calculator = BEreq::FHCouplings.origin();
      Couplings.calculator_version = BEreq::FHCouplings.version();

      result = Couplings;
    }


    /// Helper function to work out if the LSP is invisible, and if so, which particle it is.
    std::vector<str> get_invisibles(const SubSpectrum& spec)
    {
      // Get the lighter of the lightest neutralino and the lightest sneutrino
      std::pair<str,double> neutralino("~chi0_1", spec.get(Par::Pole_Mass,"~chi0",1));
      std::pair<str,double> sneutrino("~nu_1", spec.get(Par::Pole_Mass,"~nu",1));
      std::pair<str,double> lnp = (neutralino.second < sneutrino.second ? neutralino : sneutrino);

      // Work out if this is indeed the LSP, and if decays of at least one neutral higgs to it are kinematically possible.
      bool inv_lsp = spec.get(Par::Pole_Mass,"~chi+",1) > lnp.second and
                     spec.get(Par::Pole_Mass,"~g") > lnp.second and
                     spec.get(Par::Pole_Mass,"~d",1) > lnp.second and
                     spec.get(Par::Pole_Mass,"~u",1) > lnp.second and
                     spec.get(Par::Pole_Mass,"~e-",1) > lnp.second and
                     (spec.get(Par::Pole_Mass,"h0",2) > 2.*lnp.second or
                      spec.get(Par::Pole_Mass,"A0") > 2.*lnp.second);

      // Create a vector containing all invisible products of higgs decays.
      if (inv_lsp) return initVector<str>(lnp.first);
      return std::vector<str>();
    }

    /// Put together the Higgs couplings for the MSSM, from partial widths only
    void MSSM_higgs_couplings_pwid(HiggsCouplingsTable &result)
    {
      using namespace Pipes::MSSM_higgs_couplings_pwid;

      // Retrieve spectrum contents
      const SubSpectrum& spec = Dep::MSSM_spectrum->get_HE();

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

      // Set the CP of the Higgs states.  Note that this would need to be more sophisticated to deal with the complex MSSM!
      result.CP[0] = 1;  //h0_1
      result.CP[1] = 1;  //h0_2
      result.CP[2] = -1; //A0

      // Work out which SM values correspond to which SUSY Higgs
      int higgs = (SMlike_higgs_PDG_code(spec) == 25 ? 0 : 1);
      int other_higgs = (higgs == 0 ? 1 : 0);

      // Set the decays
      result.set_neutral_decays_SM(higgs, sHneut[higgs], *Dep::Reference_SM_Higgs_decay_rates);
      result.set_neutral_decays_SM(other_higgs, sHneut[other_higgs], *Dep::Reference_SM_other_Higgs_decay_rates);
      result.set_neutral_decays_SM(2, sHneut[2], *Dep::Reference_SM_A0_decay_rates);
      result.set_neutral_decays(0, sHneut[0],  *Dep::Higgs_decay_rates);
      result.set_neutral_decays(1, sHneut[1], *Dep::h0_2_decay_rates);
      result.set_neutral_decays(2, sHneut[2], *Dep::A0_decay_rates);
      result.set_charged_decays(0, "H+", *Dep::H_plus_decay_rates);
      result.set_t_decays(*Dep::t_decay_rates);

      // Use them to compute effective couplings for all neutral higgses, except for hhZ.
      for (int i = 0; i < 3; i++)
      {
        result.C_WW2[i] = result.compute_effective_coupling(i, std::pair<int,int>(24, 0), std::pair<int,int>(-24, 0));
        result.C_ZZ2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(23, 0));
        result.C_tt2[i] = result.compute_effective_coupling(i, std::pair<int,int>(6, 1), std::pair<int,int>(-6, 1));
        result.C_bb2[i] = result.compute_effective_coupling(i, std::pair<int,int>(5, 1), std::pair<int,int>(-5, 1));
        result.C_cc2[i] = result.compute_effective_coupling(i, std::pair<int,int>(4, 1), std::pair<int,int>(-4, 1));
        result.C_tautau2[i] = result.compute_effective_coupling(i, std::pair<int,int>(15, 1), std::pair<int,int>(-15, 1));
        result.C_gaga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(22, 0), std::pair<int,int>(22, 0));
        result.C_gg2[i] = result.compute_effective_coupling(i, std::pair<int,int>(21, 0), std::pair<int,int>(21, 0));
        result.C_mumu2[i] = result.compute_effective_coupling(i, std::pair<int,int>(13, 1), std::pair<int,int>(-13, 1));
        result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(21, 0));
        result.C_ss2[i] = result.compute_effective_coupling(i, std::pair<int,int>(3, 1), std::pair<int,int>(-3, 1));
      }

      // Calculate hhZ effective couplings.  Here we scale out the kinematic prefactor
      // of the decay width, assuming we are well above threshold if the channel is open.
      // If not, we simply assume SM couplings.
      const double mZ = Dep::MSSM_spectrum->get(Par::Pole_Mass,23,0);
      const double scaling = 8.*sqrt(2.)*pi/Dep::MSSM_spectrum->get_SMInputs().GF;
      for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
      {
        double mhi = spec.get(Par::Pole_Mass, sHneut[i]);
        double mhj = spec.get(Par::Pole_Mass, sHneut[j]);
        if (mhi > mhj + mZ and result.get_neutral_decays(i).has_channel(sHneut[j], "Z0"))
        {
          double gamma = result.get_neutral_decays(i).width_in_GeV*result.get_neutral_decays(i).BF(sHneut[j], "Z0");
          double k[2] = {(mhj + mZ)/mhi, (mhj - mZ)/mhi};
          for (int l = 0; l < 2; l++) k[l] = (1.0 - k[l]) * (1.0 + k[l]);
          double K = mhi*sqrt(k[0]*k[1]);
          result.C_hiZ2[i][j] = scaling / (K*K*K) * gamma;
        }
        else // If the channel is missing from the decays or kinematically disallowed, just return the SM result.
        {
          result.C_hiZ2[i][j] = 1.;
        }
      }

      // Work out which invisible decays are possible
      result.invisibles = get_invisibles(spec);
    }


    /// Put together the Higgs couplings for the MSSM, using FeynHiggs
    void MSSM_higgs_couplings_FH(HiggsCouplingsTable &result)
    {
      using namespace Pipes::MSSM_higgs_couplings_FH;

      // Retrieve spectrum contents
      const SubSpectrum& spec = Dep::MSSM_spectrum->get_HE();
      const SMInputs& sminputs = Dep::MSSM_spectrum->get_SMInputs();

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

      // Work out which SM values correspond to which SUSY Higgs
      int higgs = (SMlike_higgs_PDG_code(spec) == 25 ? 0 : 1);
      int other_higgs = (higgs == 0 ? 1 : 0);

      // Set the decays
      result.set_neutral_decays_SM(higgs, sHneut[higgs], *Dep::Reference_SM_Higgs_decay_rates);
      result.set_neutral_decays_SM(other_higgs, sHneut[other_higgs], *Dep::Reference_SM_other_Higgs_decay_rates);
      result.set_neutral_decays_SM(2, sHneut[2], *Dep::Reference_SM_A0_decay_rates);
      result.set_neutral_decays(0, sHneut[0], *Dep::Higgs_decay_rates);
      result.set_neutral_decays(1, sHneut[1], *Dep::h0_2_decay_rates);
      result.set_neutral_decays(2, sHneut[2], *Dep::A0_decay_rates);
      result.set_charged_decays(0, "H+", *Dep::H_plus_decay_rates);
      result.set_t_decays(*Dep::t_decay_rates);

      // Use the branching fractions to compute gluon, gamma/Z and second generation fermionic effective couplings
      for (int i = 0; i < 3; i++)
      {
        result.C_gg2[i] = result.compute_effective_coupling(i, std::pair<int,int>(21, 0), std::pair<int,int>(21, 0));
        result.C_gaga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(22, 0), std::pair<int,int>(22, 0));
        result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(22, 0));
        result.C_mumu2[i] = result.compute_effective_coupling(i, std::pair<int,int>(13, 1), std::pair<int,int>(-13, 1));
        result.C_ss2[i] = result.compute_effective_coupling(i, std::pair<int,int>(3, 1), std::pair<int,int>(-3, 1));
        result.C_cc2[i] = result.compute_effective_coupling(i, std::pair<int,int>(4, 1), std::pair<int,int>(-4, 1));
      }

      // Use couplings to get effective third-generation couplings
      for(int i = 0; i < 3; i++)
      {
        // Compute effective couplings
        double g2_s[3], g2_p[3];
        for (int j = 0; j < 3; j++) // j=0,1,2 => tau, t, b
        {
          fh_complex fh_L = Dep::FH_Couplings_output->couplings[H0FF(i+1,j+2,3,3)-1];
          fh_complex fh_R = Dep::FH_Couplings_output->couplings[H0FF(i+1,j+2,3,3)+Roffset-1];
          fh_complex fh_SM_L = Dep::FH_Couplings_output->couplings_sm[H0FF(i+1,j+2,3,3)-1];
          fh_complex fh_SM_R = Dep::FH_Couplings_output->couplings_sm[H0FF(i+1,j+2,3,3)+RSMoffset-1];
          std::complex<double> L(fh_L.re,fh_L.im);
          std::complex<double> R(fh_R.re,fh_R.im);
          std::complex<double> SM_L(fh_SM_L.re,fh_SM_L.im);
          std::complex<double> SM_R(fh_SM_R.re,fh_SM_R.im);
          g2_s[j] = 0.25*pow(std::abs(R/SM_R + L/SM_L), 2.);
          g2_p[j] = 0.25*pow(std::abs(R/SM_R - L/SM_L), 2.);
        }
        result.C_tautau2[i] = g2_s[0] + g2_p[0];
        result.C_tt2[i]     = g2_s[1] + g2_p[1];
        result.C_bb2[i]     = g2_s[2] + g2_p[2];

        // Calculate CP of state
        if(g2_p[2] < 1e-10)
          result.CP[i] = 1;
        else if(g2_s[2] < 1e-10)
          result.CP[i] = -1;
        else
          result.CP[i] = 0.;
      }

      // Use couplings to get di-boson effective couplings
      for(int i = 0; i < 3; i++)
      {
        fh_complex c_gWW = Dep::FH_Couplings_output->couplings[H0VV(i+1,4)-1];
        fh_complex c_gWW_SM = Dep::FH_Couplings_output->couplings_sm[H0VV(i+1,4)-1];
        fh_complex c_gZZ = Dep::FH_Couplings_output->couplings[H0VV(i+1,3)-1];
        fh_complex c_gZZ_SM = Dep::FH_Couplings_output->couplings_sm[H0VV(i+1,3)-1];
        std::complex<double> WW(c_gWW.re,c_gWW.im);
        std::complex<double> WW_SM(c_gWW_SM.re,c_gWW_SM.im);
        std::complex<double> ZZ(c_gZZ.re,c_gZZ.im);
        std::complex<double> ZZ_SM(c_gZZ_SM.re,c_gZZ_SM.im);
        result.C_WW2[i] = pow(std::abs(WW/WW_SM), 2.);
        result.C_ZZ2[i] = pow(std::abs(ZZ/ZZ_SM), 2.);
      }

      // Use couplings to get hhZ effective couplings
      double norm = sminputs.GF*sqrt(2.)*sminputs.mZ*sminputs.mZ;
      for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
      {
        fh_complex c_gHV = Dep::FH_Couplings_output->couplings[H0HV(i+1,j+1)-1];
        double g2HV = c_gHV.re*c_gHV.re+c_gHV.im*c_gHV.im;
        result.C_hiZ2[i][j] = g2HV/norm;
      }

      // Work out which invisible decays are possible
      result.invisibles = get_invisibles(spec);
    }


/////////////////////////////
//// Map output routines ////
/////////////////////////////

    /// @{ Convert MSSM type Spectrum object into a map, so it can be printed
    template<class Contents>
    void fill_map_from_subspectrum(std::map<std::string,double>&, const SubSpectrum&);

    /// Adds additional information from interesting combinations of MSSM parameters
    void add_extra_MSSM_parameter_combinations(std::map<std::string,double>& specmap, const SubSpectrum& mssm)
    {
      double At = 0;
      double Ab = 0;
      const double Yt = mssm.get(Par::dimensionless, "Yu", 3, 3);
      const double Yb = mssm.get(Par::dimensionless, "Yd", 3, 3);
      if(std::abs(Yt) > 1e-12)
      {
        At = mssm.get(Par::mass1, "TYu", 3, 3) / Yt;
      }
      if(std::abs(Yb) > 1e-12)
      {
        Ab = mssm.get(Par::mass1, "TYd", 3, 3) / Yb;
      }

      const double MuSUSY = mssm.get(Par::mass1, "Mu");
      const double tb = mssm.get(Par::dimensionless, "tanbeta");

      specmap["Xt"] = At - MuSUSY / tb;
      specmap["Xb"] = Ab - MuSUSY * tb;
      /// Determine which states are the third gens then add them for printing
      str msf1, msf2;
      /// Since this is for printing we only want to invalidate the point
      /// if this is completely wrong.
      /// We can also plot the mixing if we are suspicious.
      const static double tol = 0.5;
      const static bool pt_error = true;
      slhahelp::family_state_mix_matrix("~u", 3, msf1, msf2, mssm, tol,
                                        LOCAL_INFO, pt_error);
      specmap["mstop1"] =  mssm.get(Par::Pole_Mass, msf1);
      specmap["mstop2"] =  mssm.get(Par::Pole_Mass, msf2);
      slhahelp::family_state_mix_matrix("~d", 3, msf1, msf2, mssm, tol,
                                        LOCAL_INFO, pt_error);
      specmap["msbottom1"] =  mssm.get(Par::Pole_Mass, msf1);
      specmap["msbottom2"] =  mssm.get(Par::Pole_Mass, msf2);
      slhahelp::family_state_mix_matrix("~e-", 3, msf1, msf2, mssm, tol,
                                        LOCAL_INFO, pt_error);
      specmap["mstau1"] =  mssm.get(Par::Pole_Mass, msf1);
      specmap["mstau2"] =  mssm.get(Par::Pole_Mass, msf2);
      /// return mass eigenstate strings that best represent required gauge
      /// eigenstate
      const str gs_suL = slhahelp::mass_es_from_gauge_es("~u_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msupL"] = mssm.get(Par::Pole_Mass,gs_suL);
      const str gs_scL = slhahelp::mass_es_from_gauge_es("~c_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["mscharmL"] = mssm.get(Par::Pole_Mass,gs_scL);
      const str gs_sdL = slhahelp::mass_es_from_gauge_es("~d_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msdownL"] = mssm.get(Par::Pole_Mass,gs_sdL);
      const str gs_ssL = slhahelp::mass_es_from_gauge_es("~s_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msstrangeL"] = mssm.get(Par::Pole_Mass,gs_ssL);
      const str gs_suR = slhahelp::mass_es_from_gauge_es("~u_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msupR"] = mssm.get(Par::Pole_Mass,gs_suR);
      const str gs_scR = slhahelp::mass_es_from_gauge_es("~c_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["mscharmR"] = mssm.get(Par::Pole_Mass,gs_scR);
      const str gs_sdR = slhahelp::mass_es_from_gauge_es("~d_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msdownR"] = mssm.get(Par::Pole_Mass,gs_sdR);
      const str gs_ssR = slhahelp::mass_es_from_gauge_es("~s_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msstrangeR"] = mssm.get(Par::Pole_Mass,gs_ssR);
      const str gs_seL = slhahelp::mass_es_from_gauge_es("~e_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["mselectronL"] = mssm.get(Par::Pole_Mass,gs_seL);
      const str gs_sMuL = slhahelp::mass_es_from_gauge_es("~mu_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msmuonL"] = mssm.get(Par::Pole_Mass,gs_sMuL);
      const str gs_seR = slhahelp::mass_es_from_gauge_es("~e_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["mselectronR"] = mssm.get(Par::Pole_Mass,gs_seR);
      const str gs_sMuR = slhahelp::mass_es_from_gauge_es("~mu_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msmuonR"] = mssm.get(Par::Pole_Mass,gs_sMuR);
      const str gs_snu1 = slhahelp::mass_es_from_gauge_es("~nu_e_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msnue"] = mssm.get(Par::Pole_Mass,gs_snu1);
      const str gs_snu2 = slhahelp::mass_es_from_gauge_es("~nu_mu_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msnumu"] = mssm.get(Par::Pole_Mass,gs_snu2);
      const str gs_snu3 = slhahelp::mass_es_from_gauge_es("~nu_tau_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msnutau"] = mssm.get(Par::Pole_Mass,gs_snu3);

    }

    void get_MSSM_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_MSSM_spectrum_as_map;
      const Spectrum& mssmspec(*myPipe::Dep::MSSM_spectrum);
      fill_map_from_subspectrum<SpectrumContents::SM>  (specmap, mssmspec.get_LE());
      fill_map_from_subspectrum<SpectrumContents::MSSM>(specmap, mssmspec.get_HE());
      add_extra_MSSM_parameter_combinations(specmap, mssmspec.get_HE());
    }
    void get_unimproved_MSSM_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_unimproved_MSSM_spectrum_as_map;
      const Spectrum& mssmspec(*myPipe::Dep::unimproved_MSSM_spectrum);
      fill_map_from_subspectrum<SpectrumContents::SM>  (specmap, mssmspec.get_LE());
      fill_map_from_subspectrum<SpectrumContents::MSSM>(specmap, mssmspec.get_HE());
      add_extra_MSSM_parameter_combinations(specmap, mssmspec.get_HE());
    }
    /// @}

    /// Extract all parameters from a subspectrum and put them into a map
    template<class Contents>
    void fill_map_from_subspectrum(std::map<std::string,double>& specmap, const SubSpectrum& subspec)
    {
      /// Add everything... use spectrum contents routines to automate task (make sure to use correct template parameter!)
      static const Contents contents;
      static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters();

      for(std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin();
           it != required_parameters.end(); ++it)
      {
         const Par::Tags        tag   = it->tag();
         const std::string      name  = it->name();
         const std::vector<int> shape = it->shape();

         /// Verification routine should have taken care of invalid shapes etc, so won't check for that here.

         // Check scalar case
         if(shape.size()==1 and shape[0]==1)
         {
           std::ostringstream label;
           label << name <<" "<< Par::toString.at(tag);
           specmap[label.str()] = subspec.get(tag,name);
           // Check again ignoring overrides (if the value has an override defined)
           if(subspec.has(tag,name,overrides_only) and
              subspec.has(tag,name,ignore_overrides))
           {
             label << " (unimproved)";
             specmap[label.str()] = subspec.get(tag,name,ignore_overrides);
           }
         }
         // Check vector case
         else if(shape.size()==1 and shape[0]>1)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             std::ostringstream label;
             label << name <<"_"<<i<<" "<< Par::toString.at(tag);
             specmap[label.str()] = subspec.get(tag,name,i);
             // Check again ignoring overrides
             if(subspec.has(tag,name,i,overrides_only) and
                subspec.has(tag,name,i,ignore_overrides))
             {
               label << " (unimproved)";
               specmap[label.str()] = subspec.get(tag,name,i,ignore_overrides);
             }
           }
         }
         // Check matrix case
         else if(shape.size()==2)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             for(int j = 1; j<=shape[0]; ++j) {
               std::ostringstream label;
               label << name <<"_("<<i<<","<<j<<") "<<Par::toString.at(tag);
               specmap[label.str()] = subspec.get(tag,name,i,j);
               // Check again ignoring overrides
               if(subspec.has(tag,name,i,j,overrides_only) and
                  subspec.has(tag,name,i,j,ignore_overrides))
               {
                 label << " (unimproved)";
                 specmap[label.str()] = subspec.get(tag,name,i,j,ignore_overrides);
               }
             }
           }
         }
         // Deal with all other cases
         else
         {
           // ERROR
           std::ostringstream errmsg;
           errmsg << "Error, invalid parameter received while converting SubSpectrum with contents \""<<contents.getName()<<"\" to map of strings! This should no be possible if the spectrum content verification routines were working correctly; they must be buggy, please report this.";
           errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape;
           SpecBit_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
      }
      // add the scale!
      specmap["scale(Q)"] = subspec.GetScale();
    }

    void FH_HiggsMass(triplet<double>& result)
    {
      using namespace Pipes::FH_HiggsMass;
      //FH indices: 0=h0_1, 1=h0_2
      int i = 0;
      const SubSpectrum& spec = Dep::unimproved_MSSM_spectrum->get_HE();
      int higgs = SMlike_higgs_PDG_code(spec);
      if (higgs == 25) i = 0;
      else if (higgs == 35) i = 1;
      else SpecBit_error().raise(LOCAL_INFO, "Urecognised SM-like Higgs PDG code!");
      result.central = Dep::FH_HiggsMasses->MH[i];
      result.upper = Dep::FH_HiggsMasses->deltaMH[i];
      result.lower = Dep::FH_HiggsMasses->deltaMH[i];
    }

    void FH_HeavyHiggsMasses(map_int_triplet_dbl& result)
    {
      using namespace Pipes::FH_HeavyHiggsMasses;
      const int neutrals[2] = {25, 35};
      int i = -1;
      const SubSpectrum& spec = Dep::unimproved_MSSM_spectrum->get_HE();
      int higgs = SMlike_higgs_PDG_code(spec);
      if (higgs == neutrals[0]) i = 1;
      else if (higgs == neutrals[1]) i = 0;
      else SpecBit_error().raise(LOCAL_INFO, "Urecognised SM-like Higgs PDG code!");
      result.clear();
      result[neutrals[i]].central = Dep::FH_HiggsMasses->MH[i];
      result[neutrals[i]].upper = Dep::FH_HiggsMasses->deltaMH[i];
      result[neutrals[i]].lower = Dep::FH_HiggsMasses->deltaMH[i];
      result[36].central = Dep::FH_HiggsMasses->MH[2];
      result[36].upper = Dep::FH_HiggsMasses->deltaMH[2];
      result[36].lower = Dep::FH_HiggsMasses->deltaMH[2];
      result[37].central = Dep::FH_HiggsMasses->MH[3];
      result[37].upper = Dep::FH_HiggsMasses->deltaMH[3];
      result[37].lower = Dep::FH_HiggsMasses->deltaMH[3];
    }

    void SHD_HiggsMass(triplet<double>& result)
    {
      using namespace Pipes::SHD_HiggsMass;

      const Spectrum& fullspectrum = *Dep::unimproved_MSSM_spectrum;
      SLHAea::Coll slhaea = fullspectrum.getSLHAea(1);

      #ifdef SPECBIT_DEBUG
        cout << "****** calling SHD_HiggsMass ******" << endl;
      #endif

      MList<MReal> parameterList = {
        SLHAea::to<double>(slhaea.at("HMIX").at(2).at(1)), // tanbeta
        SLHAea::to<double>(slhaea.at("MSOFT").at(1).at(1)), // M1
        SLHAea::to<double>(slhaea.at("MSOFT").at(2).at(1)), // M2
        SLHAea::to<double>(slhaea.at("MSOFT").at(3).at(1)), // M3
        SLHAea::to<double>(slhaea.at("HMIX").at(1).at(1)), // mu
        SLHAea::to<double>(slhaea.at("AU").at(3).at(2)), // At
        SLHAea::to<double>(slhaea.at("MSOFT").at(43).at(1)), // mQ3
        SLHAea::to<double>(slhaea.at("MSOFT").at(46).at(1)), // mU3
        SLHAea::to<double>(slhaea.at("MSOFT").at(49).at(1)), // mD3
        SLHAea::to<double>(slhaea.at("MSOFT").at(42).at(1)), // mQ2
        SLHAea::to<double>(slhaea.at("MSOFT").at(45).at(1)), // mU2
        SLHAea::to<double>(slhaea.at("MSOFT").at(48).at(1)), // mD2
        SLHAea::to<double>(slhaea.at("MSOFT").at(41).at(1)), // mQ1
        SLHAea::to<double>(slhaea.at("MSOFT").at(44).at(1)), // mU1
        SLHAea::to<double>(slhaea.at("MSOFT").at(47).at(1)), // mD1
        SLHAea::to<double>(slhaea.at("MSOFT").at(33).at(1)), // mL3
        SLHAea::to<double>(slhaea.at("MSOFT").at(36).at(1)), // mE3
        SLHAea::to<double>(slhaea.at("MSOFT").at(32).at(1)), // mL2
        SLHAea::to<double>(slhaea.at("MSOFT").at(35).at(1)), // mE2
        SLHAea::to<double>(slhaea.at("MSOFT").at(31).at(1)), // mL1
        SLHAea::to<double>(slhaea.at("MSOFT").at(34).at(1)), // mE1
        sqrt(SLHAea::to<double>(slhaea.at("HMIX").at(4).at(1))) // mA
      };

      MReal MHiggs = BEreq::SUSYHD_MHiggs(parameterList);

      #ifdef SPECBIT_DEBUG
        cout << "****** calling SHD_DeltaHiggsMass ******" << endl;
      #endif

      MReal DeltaMHiggs = BEreq::SUSYHD_DeltaMHiggs(parameterList);

      result.central = MHiggs;
      result.upper = DeltaMHiggs;
      result.lower = DeltaMHiggs;

    }


    /// @} End Gambit module functions

  } // end namespace SpecBit
} // end namespace Gambit

