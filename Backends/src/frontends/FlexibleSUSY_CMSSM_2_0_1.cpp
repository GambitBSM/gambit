//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for FlexibleSUSY_CMSSM 2.0.1 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Peter Athron
///          (peter.athron@monash.edu)
///  \date 2019 Oct
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct
///
///  *********************************************


#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/FlexibleSUSY_CMSSM_2_0_1.hpp"
#include "gambit/Backends/backend_types/FlexibleSUSY.hpp"
#include "gambit/Elements/spectrum.hpp"

//TODO: Static FS includes, remove when BOSSed FS works
//#include "flexiblesusy/src/lowe.h" // From softsusy; used by flexiblesusy
//#include "flexiblesusy/src/spectrum_generator_settings.hpp"
//#include "flexiblesusy/models/CMSSM/CMSSM_spectrum_generator.hpp"
//#include "flexiblesusy/models/CMSSM/CMSSM_slha_io.hpp"
//#include "flexiblesusy/models/CMSSM/CMSSM_two_scale_spectrum_generator.hpp"

// Convenience functions (definitions)
BE_NAMESPACE
{
  // BOSS namespaces 
  using namespace FlexibleSUSY_CMSSM_default::flexiblesusy;
  //using namespace FlexibleSUSY_CMSSM_default::softsusy;

  // using namespace ::flexiblesusy;
  // using namespace ::softsusy;

    /// Initialise QedQcd object from SMInputs data
/*  void setup_QedQcd(softsusy::QedQcd& oneset, const SMInputs& sminputs)
  {
    // Set pole masses (to be treated specially)
    oneset.setPoleMt(sminputs.mT);
    //oneset.setPoleMb(...);
    oneset.setPoleMtau(sminputs.mTau);
    oneset.setMbMb(sminputs.mBmB);
    /// set running quark masses
    /// TODO: check if we should use
    /// TODO: setMu2GeV, setMd2GeV, setMs2GeV, setMcMc
    oneset.setMass(softsusy::mDown,    sminputs.mD);
    oneset.setMass(softsusy::mUp,      sminputs.mU);
    oneset.setMass(softsusy::mStrange, sminputs.mS);
    oneset.setMass(softsusy::mCharm,   sminputs.mCmC);
    /// set QED and QCD structure constants
    oneset.setAlpha(softsusy::ALPHA, 1./sminputs.alphainv);
    oneset.setAlpha(softsusy::ALPHAS, sminputs.alphaS);
    // set electron, muon and z pole mass
    // TODO: check if we should set set pole masses here instead
    // TODO ie use setPoleMmuon, setPoleMel
    // TODO: has no real impact anyway
    oneset.setMass(softsusy::mElectron, sminputs.mE);
    oneset.setMass(softsusy::mMuon,     sminputs.mMu);
    oneset.setPoleMZ(sminputs.mZ);
  }  
*/
  
  // Function to extract the FS settings form the yaml file
/*  void Get_yaml_settings(Spectrum_generator_settings& settings, const SpectrumInputs& Input)
  {
    //inputs.options = myPipe::runOptions;
    auto Options = Input.options;
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

    settings.set(Spectrum_generator_settings::precision, Options->getValueOrDef<double>(1.0e-4,"precision_goal"));
    settings.set(Spectrum_generator_settings::max_iterations, Options->getValueOrDef<double>(0,"max_iterations"));
    settings.set(Spectrum_generator_settings::calculate_sm_masses, Options->getValueOrDef<bool> (false, "calculate_sm_masses"));
    settings.set(Spectrum_generator_settings::pole_mass_loop_order, Options->getValueOrDef<int>(2,"pole_mass_loop_order"));
    settings.set(Spectrum_generator_settings::ewsb_loop_order, Options->getValueOrDef<int>(2,"ewsb_loop_order"));
    settings.set(Spectrum_generator_settings::beta_loop_order, Options->getValueOrDef<int>(2,"beta_loop_order"));
    settings.set(Spectrum_generator_settings::threshold_corrections_loop_order, Options->getValueOrDef<int>(2,"threshold_corrections_loop_order"));
    settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_as, Options->getValueOrDef<int>(1,"higgs_2loop_correction_at_as"));
    settings.set(Spectrum_generator_settings::higgs_2loop_correction_ab_as, Options->getValueOrDef<int>(1,"higgs_2loop_correction_ab_as"));
    settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_at, Options->getValueOrDef<int>(1,"higgs_2loop_correction_at_at"));
    settings.set(Spectrum_generator_settings::higgs_2loop_correction_atau_atau, Options->getValueOrDef<int>(1,"higgs_2loop_correction_atau_atau"));
    settings.set(Spectrum_generator_settings::top_pole_qcd_corrections, Options->getValueOrDef<int>(1,"top_pole_qcd_corrections"));
    settings.set(Spectrum_generator_settings::beta_zero_threshold, Options->getValueOrDef<double>(1.000000000e-14,"beta_zero_threshold"));
    settings.set(Spectrum_generator_settings::calculate_observables, Options->getValueOrDef<int>(0,"calculate_observables")); // 
    settings.set(Spectrum_generator_settings::pole_mass_scale, Options->getValueOrDef<int>(0,"pole_mass_scale")); // Zero means use SUSYScale, otherwise gives scale for pole mass calculation. Mostly used for estimation of errors so unlikely to be used a sgeneral setting chosen in yaml file.
    settings.set(Spectrum_generator_settings::eft_pole_mass_scale, Options->getValueOrDef<int>(0,"eftPoleMassScale")); // Zero means use Mt. Otherwise sets the scale of the pole mass calculation in the EFT in GeV.Mostly used for estimation of errors so unlikely to be used a sgeneral setting chosen in yaml file
    settings.set(Spectrum_generator_settings::eft_matching_scale, Options->getValueOrDef<int>(0,"eftMatchingScale")); // Zero means use SUSYScale. Otherwise sets the EFT matching scale in GeV.  Mostly used for estimation of errors so unlikely to be used a sgeneral setting chosen in yaml file.
    settings.set(Spectrum_generator_settings::eft_matching_loop_order_up, Options->getValueOrDef<int>(1,"eft_matching_loop_order_up"));
    settings.set(Spectrum_generator_settings::eft_matching_loop_order_down, Options->getValueOrDef<int>(1,"eft_matching_loop_order_down"));
    settings.set(Spectrum_generator_settings::eft_higgs_index, Options->getValueOrDef<int>(0,"eftHiggsIndex")); //If set to 0, the lightest field in the Higgs multiplet isinterpreted as SM-like Higgs. If set to 1, the 2nd lightest field is interpreted as SM-like etc
    settings.set(Spectrum_generator_settings::calculate_bsm_masses, Options->getValueOrDef<int>(1,"calculate_bsm_masses")); // enable/disable calculation of BSM pole masses, useful if e.g. only interested in Higgs mass calculation
    settings.set(Spectrum_generator_settings::threshold_corrections, Options->getValueOrDef<int>(123111321,"threshold_corrections"));

  }
*/

  // Convenience function to compute the spectrum object
  void run_FS_Spectrum(Spectrum& spec, const SpectrumInputs& Input)
  {
       
    const SMInputs sminputs = Input.sminputs;
    /// TODO: copy the way spheno routinbe uses param and options and
    /// TODO: use these to fill CMSSM inputs, qedqcd and settings
//    softsusy::QedQcd qedqcd;
//    CMSSM_input_parameters cmssm_input;

    // fill cmssm inputs
//    cmssm_input.m0 = *Input.param.at("M0");
//    cmssm_input.m12 = *Input.param.at("M12");
//    cmssm_input.TanBeta = *Input.param.at("TanBeta");
//    cmssm_input.SignMu = *Input.param.at("SignMu");
//    cmssm_input.Azero = *Input.param.at("A0");

//    Spectrum_generator_settings spectrum_generator_settings;
    /// fix FS settings from yaml options 
//    Get_yaml_settings(spectrum_generator_settings, Input);

    // Fill QedQcd object with SMInputs values
//    setup_QedQcd(qedqcd,sminputs);
        
    // create instance of spectrum generator
    //GAMBIT BOSS type
    //CMSSM_spectrum_generator_Two_scale spectrum_generator;
    // Static FS type
    //CMSSM_spectrum_generator<Two_scale> spectrum_generator;
    //spectrum_generator.set_settings(spectrum_generator_settings);
    // Generate spectrum
    //spectrum_generator.run(qedqcd, cmssm_input);

    /// TODO: should probably catch errors here


    // extract models and problems that have been found
    // by spectrum generator
    // GAMBIT BOSS type
    // const CMSSM_slha_Model_Two_scale  models = spectrum_generator.get_models_slha();
    //static FS version
    //auto models = spectrum_generator.get_models_slha();
    //const Spectrum_generator_problems& problems = spectrum_generator.get_problems();

    /// TODO:  add LSP check here?
    // probably not could do this in module function that
    // calls this because LSP check is not FS routine
       
    /// get scales used by spectrum generator
    /// TODO: check we need these.
    //CMSSM_scales scales;
    //scales.HighScale = spectrum_generator.get_high_scale();
    //scales.SUSYScale = spectrum_generator.get_susy_scale();
    //scales.LowScale  = spectrum_generator.get_low_scale();
    //scales.pole_mass_scale = spectrum_generator.get_pole_mass_scale();

      
    //create FS slha_io object, as
    // TODO: I think we can use this to wrap slhae object
    //CMSSM_slha_io slha_io;
    //try
    //{
    //  slha_io.fill(qedqcd);
    //  slha_io.fill(cmssm_input);
    //}
    //catch (const Error& error)
    //{
    //   backend_error().raise(LOCAL_INFO, "FS does not fill slha correctly.");
    //}

    ///TODO:" make nice according to needs and create spectrum
    //slha_io.set_spinfo(problems);
    //slha_io.set_input(cmssm_input);
    //slha_io.set_print_imaginary_parts_of_majorana_mixings(
    //  spectrum_generator_settings.get(
    //  Spectrum_generator_settings::force_positive_masses));
    //slha_io.set_spectrum(models);
    //slha_io.set_extra(std::get<0>(models), scales, observables);

    /// for a spectrum object we need an slhea object,
    /// a SpectrumContents::contents, and a scale


    /// we can get a scale from the model object, but actually
    /// not sure why we need this if we pass the slhaea object
    /// the slhae object should have the scale for the blocks
    /// maybe in case they give blocks at multiple scales
    //double scale = std::get<0>(models).get_scale();

        
    //get SLHEA object from slha_io
    //SLHAea::Coll slha = slha_io.get_slha_io().get_data();

    /// Construct instance MSSM struct
    /// Models/include/gambit/Models/SpectrumContents/RegisteredSpectra.hpp
    /// Models/src/SpectrumContents/MSSM.cpp
    /// which inherits from the Contents class 
    // TODO: RegisteredSpectra lives now on Specbit, so this would break if Specbit is ditched
    // So now the contents is a part of the SpectrumInputs struct
    //SpectrumContents::MSSM mssm;
        
    /// TODO: something like:
    ///calling constructor 
    // from spectrum.hpp in Elements
    //Spectrum spectrum(slha, Input.content, scale, false);
    // fill Spectrum object -- a fill_spectrum method in Spectrum class would be nice
    //spec = std::move(spectrum);

    backend_warning().raise(LOCAL_INFO, "New FS spectrum calculation not implimented yet.");
     
  }

}
END_BE_NAMESPACE


BE_INI_FUNCTION
{

}
END_BE_INI_FUNCTION

