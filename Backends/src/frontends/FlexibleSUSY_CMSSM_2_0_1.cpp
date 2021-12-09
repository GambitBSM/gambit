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
#include "flexiblesusy/src/lowe.h" // From softsusy; used by flexiblesusy
#include "flexiblesusy/src/spectrum_generator_settings.hpp"
#include "flexiblesusy/models/CMSSM/CMSSM_spectrum_generator.hpp"
#include "flexiblesusy/models/CMSSM/CMSSM_slha_io.hpp"
#include "flexiblesusy/models/CMSSM/CMSSM_two_scale_spectrum_generator.hpp"

// Convenience functions (definitions)
BE_NAMESPACE
{
  // BOSS namespaces 
  //using namespace FlexibleSUSY_CMSSM_default::flexiblesusy;
  //using namespace FlexibleSUSY_CMSSM_default::softsusy;

   using namespace ::flexiblesusy;
   using namespace ::softsusy;

    /// Initialise QedQcd object from SMInputs data
   void setup_QedQcd(::softsusy::QedQcd& oneset, const SMInputs& sminputs)
  {
    // Set pole masses (to be treated specially)
    oneset.setPoleMt(sminputs.mT);
    //oneset.setPoleMb(...);
    oneset.setPoleMtau(sminputs.mTau);
    oneset.setMbMb(sminputs.mBmB);
    /// set running quark masses
    /// TODO: check if we should use
    /// TODO: setMu2GeV, setMd2GeV, setMs2GeV, setMcMc
    oneset.setMass(::softsusy::mDown,    sminputs.mD);
    oneset.setMass(::softsusy::mUp,      sminputs.mU);
    oneset.setMass(::softsusy::mStrange, sminputs.mS);
    oneset.setMass(::softsusy::mCharm,   sminputs.mCmC);
    /// set QED and QCD structure constants
    oneset.setAlpha(::softsusy::ALPHA, 1./sminputs.alphainv);
    oneset.setAlpha(::softsusy::ALPHAS, sminputs.alphaS);
    // set electron, muon and z pole mass
    // TODO: check if we should set set pole masses here instead
    // TODO ie use setPoleMmuon, setPoleMel
    // TODO: has no real impact anyway
    oneset.setMass(::softsusy::mElectron, sminputs.mE);
    oneset.setMass(::softsusy::mMuon,     sminputs.mMu);
    oneset.setPoleMZ(sminputs.mZ);

    /// TODO PA: copying over from the old specbit this misses soem
    /// setters compared to FS 2.0.1. Differences should be zero as
    /// some just FS book keeping or neglible. However test anyway and then
    /// probably keep version matching FS to make following easier
    bool match_fs = true;
    if(match_fs) {
       oneset.setAlphaEmInput(1.0 / sminputs.alphainv); //tested: 1e-4 diff typically, but 1e-3 in some mixing elemnets and 1e-2 in GUT scale value
       // I don't think QedQcd uses this
       oneset.setFermiConstant(sminputs.GF); // tested: zero numerical difference but needed so GF can actually chanage from default and affect results
       oneset.setAlphaSInput(sminputs.alphaS);//tested: affects gauge couplings at 2-3e-3 level and charm yukawa at 1e-2
       oneset.set_scale(sminputs.mZ); // tested: zero diff
       oneset.setMass(::softsusy::mBottom, sminputs.mBmB); //tested zero: diff
       oneset.setMass(::softsusy::mTau,sminputs.mTau); //tested : zero diff
       // always zero so far anyway
       oneset.setNeutrinoPoleMass(3, sminputs.mNu3); //tested : zero diff
       oneset.setPoleMel(sminputs.mE); //tested : zero diff
       oneset.setNeutrinoPoleMass(1, sminputs.mNu1); //tested : zero diff
       oneset.setPoleMmuon(sminputs.mMu); //tested largest impact is at 1e-7 relative error level on Te(2,2) ie muon soft trilnear.
       oneset.setNeutrinoPoleMass(2, sminputs.mNu2); //tested : zero diff
       oneset.setMd2GeV(sminputs.mD); //tested : zero diff
       oneset.setMu2GeV(sminputs.mU); //tested : zero diff
       oneset.setMs2GeV(sminputs.mS); //tested : zero diff
       oneset.setMcMc(sminputs.mCmC); //tested : zero diff
    }
    /// PoleMW can be set in FS if present in SLHA inpuit file,
    /// and if not default value of 80.385 used I think
    /// test for any impact anyway
    /// Note here we set to a GAMBIT value mw_central_observed!
    /// which matches FS default value but not the one in FS example
    /// LesHouches input files
    bool fix_extras = false;
    if(fix_extras) oneset.setPoleMW(sminputs.mW);
  }

  // Function to extract the FS settings form the yaml file
 void Get_yaml_settings(Spectrum_generator_settings& settings, const SpectrumInputs& Input)
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
 

  // Convenience function to compute the spectrum object
  void run_FS_Spectrum(Spectrum& spec, const SpectrumInputs& Input)
  {
    const SMInputs sminputs = Input.sminputs;
    /// TODO: copy the way spheno routinbe uses param and options and
    /// TODO: use these to fill CMSSM inputs, qedqcd and settings
    ::softsusy::QedQcd qedqcd;
    CMSSM_input_parameters cmssm_input;

    // fill cmssm inputs
    cmssm_input.m0 = *Input.param.at("M0");
    cmssm_input.m12 = *Input.param.at("M12");
    cmssm_input.TanBeta = *Input.param.at("TanBeta");
    cmssm_input.SignMu = *Input.param.at("SignMu");
    cmssm_input.Azero = *Input.param.at("A0");

    Spectrum_generator_settings spectrum_generator_settings;
    /// fix FS settings from yaml options 
    Get_yaml_settings(spectrum_generator_settings, Input);

    // Fill QedQcd object with SMInputs values
    setup_QedQcd(qedqcd,sminputs);

    //create FS slha_io object and fill inputs
    CMSSM_slha_io slha_io;
    slha_io.set_sminputs(qedqcd);
    slha_io.set_input(cmssm_input);
    std::cout << "slha file after setting sm inputs = "
              << slha_io.get_slha_io().get_data()
              << std::endl;

    // create instance of spectrum generator
    //GAMBIT BOSS type
    //CMSSM_spectrum_generator_Two_scale spectrum_generator;
    // Static FS type
    CMSSM_spectrum_generator<Two_scale> spectrum_generator;
    spectrum_generator.set_settings(spectrum_generator_settings);

    // Generate spectrum
    spectrum_generator.run(qedqcd, cmssm_input);
    /// TODO: should probably catch errors here


    // extract models and problems that have been found
    // by spectrum generator
    // GAMBIT BOSS type
    // const CMSSM_slha_Model_Two_scale  models = spectrum_generator.get_models_slha();
    //static FS version
    auto models = spectrum_generator.get_models_slha();
    auto model = std::get<0>(models);
    const Spectrum_generator_problems& problems = spectrum_generator.get_problems();

    /// TODO:  add LSP check here?
    // probably not could do this in module function that
    // calls this because LSP check is not FS routine
       
    /// get scales used by spectrum generator
    /// TODO: check we need these.
    CMSSM_scales scales;
    scales.HighScale = spectrum_generator.get_high_scale();
    scales.SUSYScale = spectrum_generator.get_susy_scale();
    scales.LowScale  = spectrum_generator.get_low_scale();
    scales.pole_mass_scale = spectrum_generator.get_pole_mass_scale();

    /// TODO: Should discuss how to handle observables for now can just make leave this empty.  
    CMSSM_observables observables;
    // if (spectrum_generator_settings.get(Spectrum_generator_settings::calculate_observables))
    //    observables = calculate_observables(std::get<0>(models), qedqcd, physical_input, scales.pole_mass_scale);


    ///TODO:" make nice according to needs and create spectrum
    slha_io.set_spinfo(problems);
    slha_io.set_print_imaginary_parts_of_majorana_mixings(
      spectrum_generator_settings.get(
      Spectrum_generator_settings::force_positive_masses));
    slha_io.set_spectrum(models);
    slha_io.set_extra(std::get<0>(models), scales, observables);

    /// for a spectrum object we need an slhea object,
    /// a SpectrumContents::contents, and a scale


    /// we can get a scale from the model object, but actually
    /// not sure why we need this if we pass the slhaea object
    /// the slhae object should have the scale for the blocks
    /// maybe in case they give blocks at multiple scales?
    double scale = std::get<0>(models).get_scale();

    //get SLHEA object from slha_io
    SLHAea::Coll slha = slha_io.get_slha_io().get_data();
    std::cout << "In FS ini slha = "  << slha << std::endl;
    /// Ugly solution to get VCKMIN and UPMNSIN inclded via gambit routines
    sminputs.add_to_SLHAea(slha);
    std::cout << "In FS ini after adding inputs via gambit slha = "  << slha << std::endl;
    // Add DMASS blocks for uncertainty estimate of spectrum generator
    // TODO: give different estmates for specifc masses, e.g. Higgs and W masses
    const double rel_uncertainty = 0.03; 
    auto block = slha["MASS"];
    SLHAea_add_block(slha, "DMASS");
    for(auto it = block.begin(); it != block.end(); it++)
    {
      if((*it)[0] != "Block" )
      {
         // add lower relative uncertainty with second index 0
         slha["DMASS"][""] << (*it)[0] << "0" <<  rel_uncertainty
                          << "# "
                          << Models::ParticleDB().long_name(std::stoi((*it)[0]),0);
         // add upper realtive uncertainty with second index 1
         slha["DMASS"][""] << (*it)[0] << "1" <<  rel_uncertainty
                          << "# "
                          << Models::ParticleDB().long_name(std::stoi((*it)[0]),0);
      }
    } 
    std::cout << "slha after adding DMASS: " << std::endl;
    std::cout << slha << std::endl;

    // For pole masses that come from SMINPUTS or are just know to be zero
    // (photon and gluon) we need to manually add DMASS entry.
    // TODO: decide if this is correct thing to do
    slha["DMASS"][""] << "21" << "0" <<  0.0 << "# gluon";
    slha["DMASS"][""] << "21" << "1" <<  0.0 << "# gluon";
    slha["DMASS"][""] << "22" << "0" <<  0.0 << "# photon";
    slha["DMASS"][""] << "22" << "1" <<  0.0 << "# photon";
    slha["DMASS"][""] << "23" << "0" <<  0.0 << "# MZ(pole)";
    slha["DMASS"][""] << "23" << "1" <<  0.0 << "# MZ(pole)";
    slha["DMASS"][""] << "11" << "0" <<  0.0 << "# e-";
    slha["DMASS"][""] << "11" << "1" <<  0.0 << "# e-"; 
    slha["DMASS"][""] << "13" << "0" <<  0.0 << "# mu-";
    slha["DMASS"][""] << "13" << "1" <<  0.0 << "# mu-";
    slha["DMASS"][""] << "15" << "0" <<  0.0 << "# tau";
    slha["DMASS"][""] << "15" << "1" <<  0.0 << "# tau";

    slha["DMASS"][""] << "12" << "0" <<  0.0 << "# nu_e";
    slha["DMASS"][""] << "12" << "1" <<  0.0 << "# nu_e"; 
    slha["DMASS"][""] << "14" << "0" <<  0.0 << "# nu_mu";
    slha["DMASS"][""] << "14" << "1" <<  0.0 << "# nu_mu";
    slha["DMASS"][""] << "16" << "0" <<  0.0 << "# nu_tau";
    slha["DMASS"][""] << "16" << "1" <<  0.0 << "# nu_tau";

    slha["DMASS"][""] << "6" << "0" <<  0.0 << "# top";
    slha["DMASS"][""] << "6" << "1" <<  0.0 << "# top";
    
    // Not in SMINPUTS as pole masses
    // slha["DMASS"][""] << "1" << "0" <<  0.0 << "# d";
    // slha["DMASS"][""] << "1" << "1" <<  0.0 << "# d";
    // slha["DMASS"][""] << "2" << "0" <<  0.0 << "# u";
    // slha["DMASS"][""] << "2" << "1" <<  0.0 << "# u";

    ///calling constructor from spectrum.hpp in Elements
    Spectrum spectrum(slha, Input.contents, scale, false);

    std::cout << "In FS inin function after constructing Spectrum"  << std::endl;
    // fill Spectrum object -- a fill_spectrum method in Spectrum class would be nice
    spec = std::move(spectrum);

    std::cout << "End of FS inin function"  << std::endl;
  }

}
END_BE_NAMESPACE


BE_INI_FUNCTION
{

}
END_BE_INI_FUNCTION

