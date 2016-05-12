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
///  *********************************************

#include <string>
#include <sstream>
#include <cmath>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
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
#include "flexiblesusy/src/two_loop_corrections.hpp"

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
    const Spectrum* run_FS_spectrum_generator
        ( const typename MI::InputParameters& input
        , const SMInputs& sminputs
        , const Options& runOptions
        , const std::map<str, safe_ptr<double> >& input_Param
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


      #define SPECGEN_SET(NAME,TYPE,DEFAULTVAL) \
         CAT_2(spectrum_generator.set_, NAME) BOOST_PP_LPAREN() runOptions.getValueOrDef<TYPE> \
               BOOST_PP_LPAREN() DEFAULTVAL BOOST_PP_COMMA() STRINGIFY(NAME) \
               BOOST_PP_RPAREN() BOOST_PP_RPAREN()
      // Ugly I know. It expands to:
      // spectrum_generator.set_NAME(runOptions.getValueOrDef<TYPE>(DEFAULTVAL,"NAME"))

      // For debugging only; check expansions
      // #ifdef SPECBIT_DEBUG
      //    #define ECHO(COMMAND) std::cout << SAFE_STRINGIFY(COMMAND) << std::endl
      //    ECHO(  SPECGEN_SET(precision_goal,                 double, 1.0e-4)  );
      //    #undef ECHO
      // #endif

      // These correspond to the entries in Block FlexibleSUSY (when running FlexibleSUSY manually via SLHA file input)
      SPECGEN_SET(precision_goal,                    double, 1.0e-4);  // 0
      SPECGEN_SET(max_iterations,                    double, 0 );      // 1
      SPECGEN_SET(calculate_sm_masses,               bool, false );    // 3 (2 is algorithm type, currently only two_scale used here)
      SPECGEN_SET(pole_mass_loop_order,              int, 2 );         // 4
      SPECGEN_SET(ewsb_loop_order,                   int, 2 );         // 5
      SPECGEN_SET(beta_loop_order,                   int, 2 );         // 6
      SPECGEN_SET(threshold_corrections_loop_order,  int, 1 );         // 7
      SPECGEN_SET(beta_zero_threshold,               double, 1.0e-11); // 14

      #undef SPECGEN_SET

      // Higgs loop corrections are a little different... sort them out now
      Two_loop_corrections two_loop_settings;

      // alpha_t alpha_s
      // alpha_b alpha_s
      // alpha_t^2 + alpha_t alpha_b + alpha_b^2
      // alpha_tau^2
      two_loop_settings.higgs_at_as
         = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_at_as"); // 8
      two_loop_settings.higgs_ab_as
         = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_ab_as"); // 9
      two_loop_settings.higgs_at_at
         = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_at_at"); // 10, presumably
      two_loop_settings.higgs_atau_atau
         = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_atau_atau"); // 11

      // Top-quark two-loop corrections QCD
      two_loop_settings.top_qcd 
         = runOptions.getValueOrDef<bool>(true,"use_top_2loop_qcd"); // 13, presumably

      spectrum_generator.set_two_loop_corrections(two_loop_settings);

      // index 12 is "force output", not relevant here

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
      MSSMSpec<MI> mssmspec(model_interface, "FlexibleSUSY", "1.1.0");

      // Add extra information about the scales used to the wrapper object
      // (last parameter turns the 'safety' check for the override setter off, which allows
      //  us to set parameters that don't previously exist)
      mssmspec.set_override(Par::mass1,spectrum_generator.get_high_scale(),"high_scale",false);
      mssmspec.set_override(Par::mass1,spectrum_generator.get_susy_scale(),"susy_scale",false);
      mssmspec.set_override(Par::mass1,spectrum_generator.get_low_scale(), "low_scale", false);

      /// add theory errors
      static const MSSM_strs ms;

      static const std::vector<int> i12     = initVector(1,2);
      static const std::vector<int> i123    = initVector(1,2,3);
      static const std::vector<int> i1234   = initVector(1,2,3,4);
      static const std::vector<int> i123456 = initVector(1,2,3,4,5,6);

      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_pred, false); // 3% theory "error"
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_pred, false); // 3% theory "error"
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_6, i123456, false);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_6, i123456, false);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, "~chi0", i1234, false);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, "~chi0", i1234, false);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_3, i123, false);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_3, i123, false);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_2, i12, false);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_2, i12, false);

      /// do the Higgs mass seperately
      /// Default in most codes is 3 GeV,
      /// seems like an underestimate if the stop masses are heavy enough.
      /// (TODO: are we happy assigning the same for both higgses?)
      /// FIXME this does not work for the second higgs
      double rd_mh = 3.0 / mssmspec.get(Par::Pole_Mass, ms.h0, 1);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, rd_mh, "h0", i12, false);
      mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  rd_mh, "h0", i12, false);

      /// Save the input value of TanBeta
      if (input_Param.find("TanBeta") != input_Param.end())
      {
        mssmspec.set_override(Par::dimensionless, *input_Param.at("TanBeta"), "TanBeta_input", false);
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
         if( runOptions.getValue<bool>("invalid_point_fatal") )
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

      // Package pointer to QedQcd SubSpectrum object along with pointer to MSSM SubSpectrum object,
      // and SMInputs struct.
      // Return pointer to this package.
      static Spectrum matched_spectra;
      matched_spectra = Spectrum(qedqcdspec,mssmspec,sminputs,&input_Param);
      return &matched_spectra;
    }


    /// Helper function for setting 3x3 matrix-valued parameters
    //  Names must conform to convention "<parname>_ij"
    Eigen::Matrix<double,3,3> fill_3x3_parameter_matrix(const std::string& rootname, const std::map<str, safe_ptr<double> >& Param)
    {
       Eigen::Matrix<double,3,3> output;
       for(int i=0; i<3; ++i) for(int j=0; j<3; ++j)
       {
         std::stringstream parname;
         parname << rootname << "_" << (i+1) << (j+1); // Assumes names in 1,2,3 convention
         output(i,j) = *Param.at(parname.str());
       }
       return output;
    }

    /// As above, but for symmetric input (i.e. 6 entries, assumed to be the upper triangle)
    Eigen::Matrix<double,3,3> fill_3x3_symmetric_parameter_matrix(const std::string& rootname, const std::map<str, safe_ptr<double> >& Param)
    {
       Eigen::Matrix<double,3,3> output;
       for(int i=0; i<3; ++i) for(int j=i; j<3; ++j)
       {
         std::stringstream parname;
         parname << rootname << "_" << (i+1) << (j+1); // Assumes names in 1,2,3 convention
         output(i,j) = *Param.at(parname.str());
       }
       return output;
    }

    /// Helper function for filling MSSM63-compatible input parameter objects
    template <class T>
    void fill_MSSM63_input(T& input, const std::map<str, safe_ptr<double> >& Param )
    {
      //double valued parameters
      input.TanBeta     = *Param.at("TanBeta");
      input.SignMu      = *Param.at("SignMu");
      input.mHu2IN      = *Param.at("mHu2");
      input.mHd2IN      = *Param.at("mHd2");
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
      if(input.SignMu!=-1 and input.SignMu!=1)
      {
         std::ostringstream msg;
         msg << "Tried to set SignMu parameter to a value that is not a sign! ("<<input.SignMu<<")! This parameter must be set to either 1 or -1. Please check your inifile and try again.";
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
        ostr << "SignMu = " << INPUT(SignMu) << ", " << oend;
        ostr << "mHd2IN = " << INPUT(mHd2IN) << ", " << oend;
        ostr << "mHu2IN = " << INPUT(mHu2IN) << ", " << oend;
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

    /// Check that the spectrum has a neutralino LSP.
    bool has_neutralino_LSP(const Spectrum* &result)
    {
      double msqd  = result->get(Par::Pole_Mass, 1000001, 0);
      double msqu  = result->get(Par::Pole_Mass, 1000002, 0);
      double msl   = result->get(Par::Pole_Mass, 1000011, 0);
      double msneu = result->get(Par::Pole_Mass, 1000012, 0);
      double mglui = result->get(Par::Pole_Mass, 1000021, 0);
      double mchi0 = std::abs(result->get(Par::Pole_Mass, 1000022, 0));
      double mchip = std::abs(result->get(Par::Pole_Mass, 1000024, 0));

      return mchi0 < mchip &&
             mchi0 < mglui &&
             mchi0 < msl   &&
             mchi0 < msneu &&
             mchi0 < msqu  &&
             mchi0 < msqd;
    }

    /// @} End module convenience functions


    /// @{ Gambit module functions
    //  =======================================================================
    //  These are wrapped up in Gambit functor objects according to the
    //  instructions in the rollcall header

    // Functions to changes the capability associated with a Spectrum object to
    // "SM_spectrum"
    //TODO: "temporarily" removed
    //void convert_MSSM_to_SM   (const Spectrum* &result) {result = *Pipes::convert_MSSM_to_SM::Dep::unimproved_MSSM_spectrum;}

    //void convert_NMSSM_to_SM  (Spectrum* &result) {result = *Pipes::convert_NMSSM_to_SM::Dep::NMSSM_spectrum;}
    //void convert_E6MSSM_to_SM (Spectrum* &result) {result = *Pipes::convert_E6MSSM_to_SM::Dep::E6MSSM_spectrum;}


    void get_CMSSM_spectrum (const Spectrum* &result)
    {

      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_CMSSM_spectrum;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Get input parameters
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

      if (myPipe::runOptions->getValueOrDef<bool>(false, "drop_SLHA_file"))
      {
        // Spit out the full spectrum as an SLHA file.
        std::cout << "Dropping SLHA file 'GAMBIT_unimproved_spectrum.slha'" << std::endl;
        str filename = myPipe::runOptions->getValueOrDef<str>("GAMBIT_unimproved_spectrum.slha", "SLHA_output_filename");
        result->getSLHA(filename);
      }
 
      // Only allow neutralino LSPs.
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");
     
    }

    // Runs MSSM spectrum generator with EWSB scale input
    void get_MSSMatQ_spectrum (const Spectrum* &result)
    {
      using namespace softsusy;
      namespace myPipe = Pipes::get_MSSMatQ_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      MSSM_input_parameters input;
      input.Qin = *myPipe::Param.at("Qin"); // MSSMatQ also requires input scale to be supplied
      fill_MSSM63_input(input,myPipe::Param);
      result = run_FS_spectrum_generator<MSSM_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
      if (myPipe::runOptions->getValueOrDef<bool>(false, "drop_SLHA_file"))
      {
        // Spit out the full spectrum as an SLHA file.
        str filename = myPipe::runOptions->getValueOrDef<str>("GAMBIT_unimproved_spectrum.slha", "SLHA_output_filename");
        result->getSLHA(filename);
      }
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");
    }

    // Runs MSSM spectrum generator with GUT scale input
    void get_MSSMatMGUT_spectrum (const Spectrum* &result)
    {
      using namespace softsusy;
      namespace myPipe = Pipes::get_MSSMatMGUT_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      MSSMatMGUT_input_parameters input;
      fill_MSSM63_input(input,myPipe::Param);
      result = run_FS_spectrum_generator<MSSMatMGUT_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
      if (myPipe::runOptions->getValueOrDef<bool>(false, "drop_SLHA_file"))
      {
        // Spit out the full spectrum as an SLHA file.
        str filename = myPipe::runOptions->getValueOrDef<str>("GAMBIT_unimproved_spectrum.slha", "SLHA_output_filename");
        result->getSLHA(filename);
      }
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");
    }

    void get_GUTMSSMB_spectrum (const Spectrum* &/*result*/)
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
      const Spectrum* matched_spectra(*myPipe::Dep::unimproved_MSSM_spectrum);
      result = matched_spectra->get_LE();
    }

    /// Extract an SLHAea version of the spectrum contained in a Spectrum object
    void get_MSSM_spectrum_as_SLHAea (SLHAstruct &result)
    {
      result = (*Pipes::get_MSSM_spectrum_as_SLHAea::Dep::unimproved_MSSM_spectrum)->getSLHAea();
    }

    /// Get an MSSMSpectrum object from an SLHA file
    /// Wraps it up in MSSMSimpleSpec; i.e. no RGE running possible.
    /// This is mainly for testing against benchmark points, but may be a useful last
    /// resort for interacting with "difficult" spectrum generators.
    void get_MSSM_spectrum_from_SLHAfile(const Spectrum* &result)
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

      // Create Spectrum object from the slhaea object
      static Spectrum matched_spectra;
      matched_spectra = spectrum_from_SLHAea<MSSMSimpleSpec, SLHAstruct>(input_slha, input_slha);
      result = &matched_spectra;

      // No sneaking in charged LSPs via SLHA, jävlar.
      if (not has_neutralino_LSP(result)) invalid_point().raise("Neutralino is not LSP.");
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
    void FH_HiggsMasses(fh_HiggsMassObs &result)
    {
      using namespace Pipes::FH_HiggsMasses;

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


    /// FeynHiggs Higgs couplings
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

      Farray<fh_complex, 1,681> couplings;     // MSSM Higgs couplings
      Farray<fh_complex, 1,231> couplings_sm;  // SM Higgs couplings
      Farray<fh_real, 1,978> gammas;           // Higgs decay widths and BR's (MSSM)
      Farray<fh_real, 1,250> gammas_sm;        // Higgs decay widths and BR's (SM)
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
      for(int i = 0; i < 681; i++) Couplings.couplings[i] = couplings(i+1);
      for(int i = 0; i < 231; i++) Couplings.couplings_sm[i] = couplings_sm(i+1);
      for(int i = 0; i < 978; i++) Couplings.gammas[i] = gammas(i+1);
      for(int i = 0; i < 250; i++) Couplings.gammas_sm[i] = gammas_sm(i+1);
      Couplings.calculator = BEreq::FHCouplings.origin();
      Couplings.calculator_version = BEreq::FHCouplings.version();

      result = Couplings;
    }

    /// @{ Convert MSSM type Spectrum object into a map, so it can be printed
    void fill_map_from_MSSMspectrum(std::map<std::string,double>&, const Spectrum*);
    void get_MSSM_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_MSSM_spectrum_as_map;
      const Spectrum* mssmspec(*myPipe::Dep::MSSM_spectrum);
      fill_map_from_MSSMspectrum(specmap, mssmspec);
    }
    void get_unimproved_MSSM_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_unimproved_MSSM_spectrum_as_map;
      const Spectrum* mssmspec(*myPipe::Dep::unimproved_MSSM_spectrum);
      fill_map_from_MSSMspectrum(specmap, mssmspec);
    }
    /// @}

    /// Common function to fill the spectrum map from a Spectrum object
    void fill_map_from_MSSMspectrum(std::map<std::string,double>& specmap, const Spectrum* mssmspec)
    {
      /// Add everything... use spectrum contents routines to automate task
      static const SpectrumContents::MSSM contents;
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
           specmap[label.str()] = mssmspec->get_HE()->get(tag,name);
         }
         // Check vector case
         else if(shape.size()==1 and shape[0]>1)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             std::ostringstream label;
             label << name <<"_"<<i<<" "<< Par::toString.at(tag);
             specmap[label.str()] = mssmspec->get_HE()->get(tag,name,i);
           }
         }
         // Check matrix case
         else if(shape.size()==2)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             for(int j = 1; j<=shape[0]; ++j) {
               std::ostringstream label;
               label << name <<"_("<<i<<","<<j<<") "<<Par::toString.at(tag);
               specmap[label.str()] = mssmspec->get_HE()->get(tag,name,i,j);
             }  
           }
         }
         // Deal with all other cases
         else
         {
           // ERROR
           std::ostringstream errmsg;           
           errmsg << "Error, invalid parameter received while converting MSSMspectrum to map of strings! This should no be possible if the spectrum content verification routines were working correctly; they must be buggy, please report this.";
           errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape; 
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
      }

    }


    /// @} End Gambit module functions

  } // end namespace SpecBit
} // end namespace Gambit

