//   3-BIT-HIT: Calculate MSSM spectra, decays and EWPO.
//   *************************************************
///  \file
///
///  A simple program that uses SpecBit, DecayBit and
///  PrecisionBit in standalone mode.  Basically
///  does the same thing SUSY-HIT, but
///  - uses SPheno for spectrum generation
///    instead of SuSpect
///  - uses FeynHiggs for MSSM Higgs decays instead
///    of SDECAY
///  - also computes electroweak precision
///    observables, using FeynHiggs and GM2Calc.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///  \date 2016 June
///        2020 Apr (switched from FlexibleSUSY to SPheno)
///
///  *********************************************

#include <stdexcept>

#include "gambit/Elements/standalone_module.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/DecayBit/DecayBit_rollcall.hpp"
#include "gambit/PrecisionBit/PrecisionBit_rollcall.hpp"

using namespace BackendIniBit::Functown;
using namespace SpecBit::Functown;
using namespace DecayBit::Functown;
using namespace PrecisionBit::Functown;

using std::cout;
using std::endl;

const std::string filename_in = "DecayBit/data/3bithit.in";
const std::string filename_out[2] = {"3bithit.out.slha1", "3bithit.out.slha2"};

int main()
{

  try
  {

    cout <<                                                                endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "  ____        ____ _____ _______   _    _ _____ _______  " << endl;
    cout << " |___ \\      |  _ \\_   _|__   __| | |  | |_   _|__   __|"<< endl;
    cout << "   __) |_____| |_) || |    | |____| |__| | | |    | |    " << endl;
    cout << "  |__ <______|  _ < | |    | |____|  __  | | |    | |    " << endl;
    cout << "  ___) |     | |_) || |_   | |    | |  | |_| |_   | |    " << endl;
    cout << " |____/      |____/_____|  |_|    |_|  |_|_____|  |_|    " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout <<                                                                endl;
    cout << "  MSSM spectrum generation, decay and EWPO calculator    " << endl;
    cout << "  based on GAMBIT modules SpecBit, DecayBit and          " << endl;
    cout << "  PrecisionBit.  Uses the following backends:            " << endl;
    cout << "    SPheno                                               " << endl;
    cout << "    GM2Calc                                              " << endl;
    cout << "    FeynHiggs                                            " << endl;
    cout << "    SDECAY (via SUSY-HIT)                                " << endl;
    cout <<                                                                endl;
    cout << "  GAMBIT Models Workgroup                                " << endl;
    cout << "  EPJC 2018 78:22                                        " << endl;
    cout << "  (arXiv:1705.07936)                                     " << endl;
    cout <<                                                                endl;
    cout << "---------------------------------------------------------" << endl;
    cout <<                                                                endl;

    // Setup logging
    std::map<std::string, std::string> loggerinfo;
    loggerinfo["Default"] = "3bithit.log";
    logger().initialise(loggerinfo);

    // Initialise the random number generator.
    Random::create_rng_engine("default");

    // Check that required backends are present
    if (not Backends::backendInfo().works["SPheno4.0.3"]) backend_error().raise(LOCAL_INFO, "SPheno 4.0.3 is missing!");
    if (not Backends::backendInfo().works["gm2calc1.3.0"]) backend_error().raise(LOCAL_INFO, "gm2calc 1.3.1 is missing!");
    if (not Backends::backendInfo().works["FeynHiggs2.11.3"]) backend_error().raise(LOCAL_INFO, "FeynHiggs 2.11.3 is missing!");
    if (not Backends::backendInfo().works["SUSY_HIT1.5"]) backend_error().raise(LOCAL_INFO, "SUSY-HIT 1.5 is missing!");

    // Read in the model
    YAML::Node infile, SM_parameters, SUSY_parameters;
    bool model_is_GUT_scale;
    std::map<bool,std::string> model;
    model[true] = "NUHM2";
    model[false] = "MSSM20atQ";
    try
    {
      infile = YAML::LoadFile(filename_in);
      if (infile["StandardModel_SLHA2"]) SM_parameters = infile["StandardModel_SLHA2"];
      else throw std::runtime_error("Block StandardModel_SLHA2 not found in "+filename_in+".  Quitting...");
      model_is_GUT_scale = infile[model[true]];
      if (model_is_GUT_scale) SUSY_parameters = infile[model[true]];
      if (infile[model[false]])
      {
        if (model_is_GUT_scale) throw std::runtime_error("Error: two different models given in "+filename_in+"!");
        SUSY_parameters = infile[model[false]];
      }
      else if (not model_is_GUT_scale) throw std::runtime_error("You must give an " + model[false] + " or " +
                                                             model[true] + " model in "+filename_in+".");
    }
    catch (YAML::Exception &e)
    {
      throw std::runtime_error("YAML error in "+filename_in+".\n(yaml-cpp error: "+std::string(e.what())+" )");
    }
    std::string SUSY_model = model[model_is_GUT_scale];

    // Retrieve a raw pointer to the parameter set of each primary model to be scanned, for manually setting parameter values
    ModelParameters* SM_primpar = Models::StandardModel_SLHA2::Functown::primary_parameters.getcontentsPtr();
    ModelParameters* SUSY_primpar = model_is_GUT_scale ? Models::NUHM2::Functown::primary_parameters.getcontentsPtr()
                                                       : Models::MSSM20atQ::Functown::primary_parameters.getcontentsPtr();

    // Resolve backend requirements 'by hand'.  Must be done before dependencies are resolved.
    get_MSSM_spectrum_SPheno.resolveBackendReq(&Backends::SPheno_4_0_3::Functown::run_SPheno);

    FeynHiggs_AllHiggsMasses.resolveBackendReq(&Backends::FeynHiggs_2_11_3::Functown::FHHiggsCorr);
    FeynHiggs_AllHiggsMasses.resolveBackendReq(&Backends::FeynHiggs_2_11_3::Functown::FHUncertainties);
    FeynHiggs_Couplings.resolveBackendReq(&Backends::FeynHiggs_2_11_3::Functown::FHCouplings);
    FeynHiggs_Couplings.resolveBackendReq(&Backends::FeynHiggs_2_11_3::Functown::FHSelectUZ);
    FeynHiggs_PrecisionObs.resolveBackendReq(&Backends::FeynHiggs_2_11_3::Functown::FHConstraints);

    gluino_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_glui2body);
    gluino_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_glui3body);
    gluino_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_gluiloop);
    gluino_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_gluiwidth);

    stop_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stop2body);
    stop_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stop3body);
    stop_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stop4body);
    stop_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stoploop);
    stop_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stopwidth);

    stop_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stop2body);
    stop_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stop3body);
    stop_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stopwidth);

    sbottom_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sbot2body);
    sbottom_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sbot3body);
    sbottom_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sbotwidth);

    sbottom_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sbot2body);
    sbottom_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sbot3body);
    sbottom_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sbotwidth);

    sup_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sup2body);
    sup_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_supwidth);

    sup_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sup2body);
    sup_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_supwidth);

    sdown_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sdown2body);
    sdown_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sdownwidth);

    sdown_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sdown2body);
    sdown_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sdownwidth);

    scharm_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sup2body);
    scharm_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_supwidth);

    scharm_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sup2body);
    scharm_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_supwidth);

    sstrange_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sdown2body);
    sstrange_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sdownwidth);
    sstrange_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sdown2body);
    sstrange_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sdownwidth);

    selectron_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sel2body);
    selectron_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_selwidth);

    selectron_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sel2body);
    selectron_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_selwidth);

    smuon_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sel2body);
    smuon_l_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_selwidth);

    smuon_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sel2body);
    smuon_r_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_selwidth);

    stau_1_decays_SH.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stau2body);
    stau_1_decays_SH.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stau2bodygrav);
    stau_1_decays_SH.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stauwidth);

    stau_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stau2body);
    stau_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_stauwidth);

    snu_electronl_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_snel2body);
    snu_electronl_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_snelwidth);

    snu_muonl_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_snel2body);
    snu_muonl_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_snelwidth);

    snu_taul_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sntau2body);
    snu_taul_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_sntauwidth);

    chargino_plus_1_decays_SH.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_char2body);
    chargino_plus_1_decays_SH.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_char2bodygrav);
    chargino_plus_1_decays_SH.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_char3body);
    chargino_plus_1_decays_SH.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_charwidth);

    chargino_plus_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_char2body);
    chargino_plus_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_char2bodygrav);
    chargino_plus_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_char3body);
    chargino_plus_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_charwidth);

    neutralino_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut2body);
    neutralino_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut2bodygrav);
    neutralino_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut3body);
    neutralino_1_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neutwidth);

    neutralino_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut2body);
    neutralino_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut2bodygrav);
    neutralino_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut3body);
    neutralino_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neutloop);
    neutralino_2_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neutwidth);

    neutralino_3_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut2body);
    neutralino_3_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut2bodygrav);
    neutralino_3_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut3body);
    neutralino_3_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neutloop);
    neutralino_3_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neutwidth);

    neutralino_4_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut2body);
    neutralino_4_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut2bodygrav);
    neutralino_4_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neut3body);
    neutralino_4_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neutloop);
    neutralino_4_decays.resolveBackendReq(&Backends::SUSY_HIT_1_5::Functown::sd_neutwidth);

    GM2C_SUSY.resolveBackendReq(&Backends::gm2calc_1_3_0::Functown::calculate_amu_1loop);
    GM2C_SUSY.resolveBackendReq(&Backends::gm2calc_1_3_0::Functown::calculate_amu_2loop);
    GM2C_SUSY.resolveBackendReq(&Backends::gm2calc_1_3_0::Functown::calculate_uncertainty_amu_2loop);

    // Notify any module functions that care of the models being scanned.
    get_SMINPUTS.notifyOfModel("StandardModel_SLHA2");
    if (model_is_GUT_scale)
    {
      Models::NUHM2::Functown::MSSM63atMGUT_parameters.notifyOfModel(SUSY_model);
    }
    else
    {
      Models::MSSM20atQ::Functown::MSSM25atQ_parameters.notifyOfModel(SUSY_model);
      Models::MSSM25atQ::Functown::MSSM30atQ_parameters.notifyOfModel(SUSY_model);
      Models::MSSM30atQ::Functown::MSSM63atQ_parameters.notifyOfModel(SUSY_model);
    }
    SPheno_4_0_3_init.notifyOfModel(SUSY_model);
    get_MSSM_spectrum_SPheno.notifyOfModel(SUSY_model);
    FeynHiggs_AllHiggsMasses.notifyOfModel(SUSY_model);
    FeynHiggs_Couplings.notifyOfModel(SUSY_model);
    SUSY_HIT_1_5_init.notifyOfModel(SUSY_model);
    FeynHiggs_2_11_3_init.notifyOfModel(SUSY_model);
    all_decays.notifyOfModel(SUSY_model);

    // Resolve dependencies 'by hand'.  Ordering is unimportant, but something must be filled by primary parameters.
    if (model_is_GUT_scale)
    {
      Models::NUHM2::Functown::MSSM63atMGUT_parameters.resolveDependency(&Models::NUHM2::Functown::primary_parameters);
      get_MSSM_spectrum_SPheno.resolveDependency(&Models::NUHM2::Functown::MSSM63atMGUT_parameters);
    }
    else
    {
      Models::MSSM20atQ::Functown::MSSM25atQ_parameters.resolveDependency(&Models::MSSM20atQ::Functown::primary_parameters);
      Models::MSSM25atQ::Functown::MSSM30atQ_parameters.resolveDependency(&Models::MSSM20atQ::Functown::MSSM25atQ_parameters);
      Models::MSSM30atQ::Functown::MSSM63atQ_parameters.resolveDependency(&Models::MSSM25atQ::Functown::MSSM30atQ_parameters);
      get_MSSM_spectrum_SPheno.resolveDependency(&Models::MSSM30atQ::Functown::MSSM63atQ_parameters);
    }
    make_MSSM_precision_spectrum_4H_W.resolveDependency(&get_MSSM_spectrum_SPheno);
    FeynHiggs_HiggsMass.resolveDependency(&get_MSSM_spectrum_SPheno);
    FeynHiggs_HeavyHiggsMasses.resolveDependency(&get_MSSM_spectrum_SPheno);
    FeynHiggs_2_11_3_init.resolveDependency(&get_MSSM_spectrum_SPheno);
    get_MSSM_spectrum_SPheno.resolveDependency(&get_SMINPUTS);

    get_SMINPUTS.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    get_mass_es_pseudonyms.resolveDependency(&make_MSSM_precision_spectrum_4H_W);
    stau_1_decays_smallsplit.resolveDependency(&make_MSSM_precision_spectrum_4H_W);
    stau_1_decays_smallsplit.resolveDependency(&tau_minus_decays);
    chargino_plus_1_decays_smallsplit.resolveDependency(&make_MSSM_precision_spectrum_4H_W);
    chargino_plus_1_decays_smallsplit.resolveDependency(&rho_0_decays);
    chargino_plus_1_decays_smallsplit.resolveDependency(&rho1450_decays);

    FeynHiggs_PrecisionObs.resolveDependency(&FeynHiggs_Couplings);
    FeynHiggs_precision_mw.resolveDependency(&FeynHiggs_PrecisionObs);
    FeynHiggs_precision_sinW2.resolveDependency(&FeynHiggs_PrecisionObs);
    FeynHiggs_precision_deltarho.resolveDependency(&FeynHiggs_PrecisionObs);
    make_MSSM_precision_spectrum_4H_W.resolveDependency(&FeynHiggs_precision_mw);
    make_MSSM_precision_spectrum_4H_W.resolveDependency(&FeynHiggs_HiggsMass);
    make_MSSM_precision_spectrum_4H_W.resolveDependency(&FeynHiggs_HeavyHiggsMasses);
    FeynHiggs_HiggsMass.resolveDependency(&FeynHiggs_AllHiggsMasses);
    FeynHiggs_HeavyHiggsMasses.resolveDependency(&FeynHiggs_AllHiggsMasses);
    GM2C_SUSY.resolveDependency(&make_MSSM_precision_spectrum_4H_W);

    SUSY_HIT_1_5_init.resolveDependency(&make_MSSM_precision_spectrum_4H_W);
    SUSY_HIT_1_5_init.resolveDependency(&W_plus_decays);
    SUSY_HIT_1_5_init.resolveDependency(&W_minus_decays);
    SUSY_HIT_1_5_init.resolveDependency(&Z_decays);

    W_minus_decays.resolveDependency(&W_plus_decays);
    tbar_decays.resolveDependency(&t_decays);
    mu_minus_decays.resolveDependency(&mu_plus_decays);
    tau_minus_decays.resolveDependency(&tau_plus_decays);
    pi_minus_decays.resolveDependency(&pi_plus_decays);
    rho_minus_decays.resolveDependency(&rho_plus_decays);

    FeynHiggs_MSSM_h0_1_decays.resolveDependency(&FeynHiggs_Couplings);
    FeynHiggs_h0_2_decays.resolveDependency(&FeynHiggs_Couplings);
    FeynHiggs_A0_decays.resolveDependency(&FeynHiggs_Couplings);
    FeynHiggs_H_plus_decays.resolveDependency(&FeynHiggs_Couplings);
    FeynHiggs_t_decays.resolveDependency(&FeynHiggs_Couplings);

    stau_1_decays.resolveDependency(&stau_1_decays_SH);
    stau_1_decays.resolveDependency(&stau_1_decays_smallsplit);
    chargino_plus_1_decays.resolveDependency(&chargino_plus_1_decays_SH);
    chargino_plus_1_decays.resolveDependency(&chargino_plus_1_decays_smallsplit);

    FeynHiggs_MSSM_h0_1_decays.resolveDependency(&get_mass_es_pseudonyms);
    FeynHiggs_h0_2_decays.resolveDependency(&get_mass_es_pseudonyms);
    FeynHiggs_A0_decays.resolveDependency(&get_mass_es_pseudonyms);
    FeynHiggs_H_plus_decays.resolveDependency(&get_mass_es_pseudonyms);
    gluino_decays.resolveDependency(&get_mass_es_pseudonyms);
    stop_1_decays.resolveDependency(&get_mass_es_pseudonyms);
    stop_2_decays.resolveDependency(&get_mass_es_pseudonyms);
    sbottom_1_decays.resolveDependency(&get_mass_es_pseudonyms);
    sbottom_2_decays.resolveDependency(&get_mass_es_pseudonyms);
    stau_1_decays_SH.resolveDependency(&get_mass_es_pseudonyms);
    stau_1_decays_smallsplit.resolveDependency(&get_mass_es_pseudonyms);
    stau_2_decays.resolveDependency(&get_mass_es_pseudonyms);
    snu_taul_decays.resolveDependency(&get_mass_es_pseudonyms);
    chargino_plus_1_decays_SH.resolveDependency(&get_mass_es_pseudonyms);
    chargino_plus_1_decays_smallsplit.resolveDependency(&get_mass_es_pseudonyms);
    chargino_plus_2_decays.resolveDependency(&get_mass_es_pseudonyms);
    neutralino_1_decays.resolveDependency(&get_mass_es_pseudonyms);
    neutralino_2_decays.resolveDependency(&get_mass_es_pseudonyms);
    neutralino_3_decays.resolveDependency(&get_mass_es_pseudonyms);
    neutralino_4_decays.resolveDependency(&get_mass_es_pseudonyms);

    H_minus_decays.resolveDependency(&H_plus_decays);
    stopbar_1_decays.resolveDependency(&stop_1_decays);
    stopbar_2_decays.resolveDependency(&stop_2_decays);
    sbottombar_1_decays.resolveDependency(&sbottom_1_decays);
    sbottombar_2_decays.resolveDependency(&sbottom_2_decays);
    supbar_l_decays.resolveDependency(&sup_l_decays);
    supbar_r_decays.resolveDependency(&sup_r_decays);
    sdownbar_l_decays.resolveDependency(&sdown_l_decays);
    sdownbar_r_decays.resolveDependency(&sdown_r_decays);
    scharmbar_l_decays.resolveDependency(&scharm_l_decays);
    scharmbar_r_decays.resolveDependency(&scharm_r_decays);
    sstrangebar_l_decays.resolveDependency(&sstrange_l_decays);
    sstrangebar_r_decays.resolveDependency(&sstrange_r_decays);
    selectronbar_l_decays.resolveDependency(&selectron_l_decays);
    selectronbar_r_decays.resolveDependency(&selectron_r_decays);
    smuonbar_l_decays.resolveDependency(&smuon_l_decays);
    smuonbar_r_decays.resolveDependency(&smuon_r_decays);
    staubar_1_decays.resolveDependency(&stau_1_decays);
    staubar_2_decays.resolveDependency(&stau_2_decays);
    snubar_electronl_decays.resolveDependency(&snu_electronl_decays);
    snubar_muonl_decays.resolveDependency(&snu_muonl_decays);
    snubar_taul_decays.resolveDependency(&snu_taul_decays);
    chargino_minus_1_decays.resolveDependency(&chargino_plus_1_decays);
    chargino_minus_2_decays.resolveDependency(&chargino_plus_2_decays);

    all_decays.resolveDependency(&get_mass_es_pseudonyms);
    all_decays.resolveDependency(&make_MSSM_precision_spectrum_4H_W);
    all_decays.resolveDependency(&FeynHiggs_MSSM_h0_1_decays);
    all_decays.resolveDependency(&W_minus_decays);
    all_decays.resolveDependency(&W_plus_decays);
    all_decays.resolveDependency(&Z_decays);
    all_decays.resolveDependency(&FeynHiggs_t_decays);
    all_decays.resolveDependency(&tbar_decays);
    all_decays.resolveDependency(&mu_minus_decays);
    all_decays.resolveDependency(&mu_plus_decays);
    all_decays.resolveDependency(&tau_minus_decays);
    all_decays.resolveDependency(&tau_plus_decays);
    all_decays.resolveDependency(&pi_0_decays);
    all_decays.resolveDependency(&pi_minus_decays);
    all_decays.resolveDependency(&pi_plus_decays);
    all_decays.resolveDependency(&eta_decays);
    all_decays.resolveDependency(&rho_0_decays);
    all_decays.resolveDependency(&rho_minus_decays);
    all_decays.resolveDependency(&rho_plus_decays);
    all_decays.resolveDependency(&rho1450_decays);
    all_decays.resolveDependency(&omega_decays);
    all_decays.resolveDependency(&FeynHiggs_h0_2_decays);
    all_decays.resolveDependency(&FeynHiggs_A0_decays);
    all_decays.resolveDependency(&FeynHiggs_H_plus_decays);
    all_decays.resolveDependency(&H_minus_decays);
    all_decays.resolveDependency(&gluino_decays);
    all_decays.resolveDependency(&stop_1_decays);
    all_decays.resolveDependency(&stop_2_decays);
    all_decays.resolveDependency(&sbottom_1_decays);
    all_decays.resolveDependency(&sbottom_2_decays);
    all_decays.resolveDependency(&sup_l_decays);
    all_decays.resolveDependency(&sup_r_decays);
    all_decays.resolveDependency(&sdown_l_decays);
    all_decays.resolveDependency(&sdown_r_decays);
    all_decays.resolveDependency(&scharm_l_decays);
    all_decays.resolveDependency(&scharm_r_decays);
    all_decays.resolveDependency(&sstrange_l_decays);
    all_decays.resolveDependency(&sstrange_r_decays);
    all_decays.resolveDependency(&selectron_l_decays);
    all_decays.resolveDependency(&selectron_r_decays);
    all_decays.resolveDependency(&smuon_l_decays);
    all_decays.resolveDependency(&smuon_r_decays);
    all_decays.resolveDependency(&stau_1_decays);
    all_decays.resolveDependency(&stau_2_decays);
    all_decays.resolveDependency(&snu_electronl_decays);
    all_decays.resolveDependency(&snu_muonl_decays);
    all_decays.resolveDependency(&snu_taul_decays);
    all_decays.resolveDependency(&stopbar_1_decays);
    all_decays.resolveDependency(&stopbar_2_decays);
    all_decays.resolveDependency(&sbottombar_1_decays);
    all_decays.resolveDependency(&sbottombar_2_decays);
    all_decays.resolveDependency(&supbar_l_decays);
    all_decays.resolveDependency(&supbar_r_decays);
    all_decays.resolveDependency(&sdownbar_l_decays);
    all_decays.resolveDependency(&sdownbar_r_decays);
    all_decays.resolveDependency(&scharmbar_l_decays);
    all_decays.resolveDependency(&scharmbar_r_decays);
    all_decays.resolveDependency(&sstrangebar_l_decays);
    all_decays.resolveDependency(&sstrangebar_r_decays);
    all_decays.resolveDependency(&selectronbar_l_decays);
    all_decays.resolveDependency(&selectronbar_r_decays);
    all_decays.resolveDependency(&smuonbar_l_decays);
    all_decays.resolveDependency(&smuonbar_r_decays);
    all_decays.resolveDependency(&staubar_1_decays);
    all_decays.resolveDependency(&staubar_2_decays);
    all_decays.resolveDependency(&snubar_electronl_decays);
    all_decays.resolveDependency(&snubar_muonl_decays);
    all_decays.resolveDependency(&snubar_taul_decays);
    all_decays.resolveDependency(&chargino_plus_1_decays);
    all_decays.resolveDependency(&chargino_minus_1_decays);
    all_decays.resolveDependency(&chargino_plus_2_decays);
    all_decays.resolveDependency(&chargino_minus_2_decays);
    all_decays.resolveDependency(&neutralino_1_decays);
    all_decays.resolveDependency(&neutralino_2_decays);
    all_decays.resolveDependency(&neutralino_3_decays);
    all_decays.resolveDependency(&neutralino_4_decays);

    // Set some module function options
    get_MSSM_spectrum_SPheno.setOption<double>("n_run", 30);
    get_MSSM_spectrum_SPheno.setOption<double>("delta_mass", 1.0e-4);

    try
    {
      // Hand over the parameter values
      auto names = SM_primpar->getKeys();
      for (auto it = names.begin(); it != names.end(); ++it) SM_primpar->setValue(*it, SM_parameters[*it].as<double>());
      names = SUSY_primpar->getKeys();
      for (auto it = names.begin(); it != names.end(); ++it) SUSY_primpar->setValue(*it, SUSY_parameters[*it].as<double>());
    }
    catch (YAML::Exception &e)
    {
      // Balk if a required parameter is missing
      throw std::runtime_error("YAML error attempting to read parameter values.\n (yaml-cpp error: "+std::string(e.what())+" )");
    }

    // Call the module functions, taking care to calculate in the order implied by how the dependencies have been filled;
    try
    {

      // Start with the spectrum.
      get_SMINPUTS.reset_and_calculate();
      if (model_is_GUT_scale)
      {
        Models::NUHM2::Functown::MSSM63atMGUT_parameters.reset_and_calculate();
      }
      else
      {
        Models::MSSM20atQ::Functown::MSSM25atQ_parameters.reset_and_calculate();
        Models::MSSM25atQ::Functown::MSSM30atQ_parameters.reset_and_calculate();
        Models::MSSM30atQ::Functown::MSSM63atQ_parameters.reset_and_calculate();
      }
      SPheno_4_0_3_init.reset_and_calculate();
      get_MSSM_spectrum_SPheno.reset_and_calculate();
      FeynHiggs_2_11_3_init.reset_and_calculate();
      FeynHiggs_AllHiggsMasses.reset_and_calculate();
      FeynHiggs_HiggsMass.reset_and_calculate();
      FeynHiggs_HeavyHiggsMasses.reset_and_calculate();
      FeynHiggs_Couplings.reset_and_calculate();
      FeynHiggs_PrecisionObs.reset_and_calculate();
      FeynHiggs_precision_mw.reset_and_calculate();
      make_MSSM_precision_spectrum_4H_W.reset_and_calculate();

      // Now the decays.
      get_mass_es_pseudonyms.reset_and_calculate();
      W_plus_decays.reset_and_calculate();
      W_minus_decays.reset_and_calculate();
      Z_decays.reset_and_calculate();
      SUSY_HIT_1_5_init.reset_and_calculate();
      FeynHiggs_MSSM_h0_1_decays.reset_and_calculate();
      FeynHiggs_t_decays.reset_and_calculate();
      tbar_decays.reset_and_calculate();
      mu_plus_decays.reset_and_calculate();
      mu_minus_decays.reset_and_calculate();
      tau_plus_decays.reset_and_calculate();
      tau_minus_decays.reset_and_calculate();
      pi_0_decays.reset_and_calculate();
      pi_plus_decays.reset_and_calculate();
      pi_minus_decays.reset_and_calculate();
      eta_decays.reset_and_calculate();
      rho_0_decays.reset_and_calculate();
      rho_plus_decays.reset_and_calculate();
      rho_minus_decays.reset_and_calculate();
      rho1450_decays.reset_and_calculate();
      omega_decays.reset_and_calculate();
      get_mass_es_pseudonyms.reset_and_calculate();
      FeynHiggs_h0_2_decays.reset_and_calculate();
      FeynHiggs_A0_decays.reset_and_calculate();
      FeynHiggs_H_plus_decays.reset_and_calculate();
      H_minus_decays.reset_and_calculate();
      gluino_decays.reset_and_calculate();
      stop_1_decays.reset_and_calculate();
      stop_2_decays.reset_and_calculate();
      sbottom_1_decays.reset_and_calculate();
      sbottom_2_decays.reset_and_calculate();
      sup_l_decays.reset_and_calculate();
      sup_r_decays.reset_and_calculate();
      sdown_l_decays.reset_and_calculate();
      sdown_r_decays.reset_and_calculate();
      scharm_l_decays.reset_and_calculate();
      scharm_r_decays.reset_and_calculate();
      sstrange_l_decays.reset_and_calculate();
      sstrange_r_decays.reset_and_calculate();
      selectron_l_decays.reset_and_calculate();
      selectron_r_decays.reset_and_calculate();
      smuon_l_decays.reset_and_calculate();
      smuon_r_decays.reset_and_calculate();
      stau_1_decays_SH.reset_and_calculate();
      stau_1_decays_smallsplit.reset_and_calculate();
      stau_1_decays.reset_and_calculate();
      stau_2_decays.reset_and_calculate();
      snu_electronl_decays.reset_and_calculate();
      snu_muonl_decays.reset_and_calculate();
      snu_taul_decays.reset_and_calculate();
      stopbar_1_decays.reset_and_calculate();
      stopbar_2_decays.reset_and_calculate();
      sbottombar_1_decays.reset_and_calculate();
      sbottombar_2_decays.reset_and_calculate();
      supbar_l_decays.reset_and_calculate();
      supbar_r_decays.reset_and_calculate();
      sdownbar_l_decays.reset_and_calculate();
      sdownbar_r_decays.reset_and_calculate();
      scharmbar_l_decays.reset_and_calculate();
      scharmbar_r_decays.reset_and_calculate();
      sstrangebar_l_decays.reset_and_calculate();
      sstrangebar_r_decays.reset_and_calculate();
      selectronbar_l_decays.reset_and_calculate();
      selectronbar_r_decays.reset_and_calculate();
      smuonbar_l_decays.reset_and_calculate();
      smuonbar_r_decays.reset_and_calculate();
      staubar_1_decays.reset_and_calculate();
      staubar_2_decays.reset_and_calculate();
      snubar_electronl_decays.reset_and_calculate();
      snubar_muonl_decays.reset_and_calculate();
      snubar_taul_decays.reset_and_calculate();
      chargino_plus_1_decays_SH.reset_and_calculate();
      chargino_plus_1_decays_smallsplit.reset_and_calculate();
      chargino_plus_1_decays.reset_and_calculate();
      chargino_minus_1_decays.reset_and_calculate();
      chargino_plus_2_decays.reset_and_calculate();
      chargino_minus_2_decays.reset_and_calculate();
      neutralino_1_decays.reset_and_calculate();
      neutralino_2_decays.reset_and_calculate();
      neutralino_3_decays.reset_and_calculate();
      neutralino_4_decays.reset_and_calculate();
      all_decays.reset_and_calculate();

      // Now the other EWPO.
      FeynHiggs_precision_sinW2.reset_and_calculate();
      FeynHiggs_precision_deltarho.reset_and_calculate();
      GM2C_SUSY.reset_and_calculate();

      // Dump the final results to SLHA files.
      SLHAstruct slha[2] = {make_MSSM_precision_spectrum_4H_W(0).getSLHAea(1), make_MSSM_precision_spectrum_4H_W(0).getSLHAea(2)};
      SLHAstruct decays[2] = {all_decays(0).getSLHAea(1,false,get_mass_es_pseudonyms(0)), all_decays(0).getSLHAea(2,false,get_mass_es_pseudonyms(0))};
      for (int i = 0; i < 2; i++) slha[i].insert(slha[i].end(), decays[i].cbegin(), decays[i].cend());
      SLHAea::Block ewpo_block("EWPO");
      ewpo_block.push_back("BLOCK EWPO              # Electroweak precision observable predictions");
      ewpo_block.push_back("#       central                 +1sigma                 -1sigma");
      SLHAea::Line line1, line2, line3, line4, line5;
      const SubSpectrum& HE = make_MSSM_precision_spectrum_4H_W(0).get_HE();
      line1 << 1 << HE.get(Par::Pole_Mass, 25, 0)   << "  " << HE.get(Par::Pole_Mass_1srd_high, 25, 0) << "  " << HE.get(Par::Pole_Mass_1srd_low, 25, 0) << "# Precision Higgs mass (GeV)";
      line2 << 2 << FeynHiggs_precision_mw(0).central       << "  " << FeynHiggs_precision_mw(0).upper                 << "  " << FeynHiggs_precision_mw(0).lower                << "# Precision W mass (GeV)";
      line3 << 3 << FeynHiggs_precision_sinW2(0).central    << "  " << FeynHiggs_precision_sinW2(0).upper              << "  " << FeynHiggs_precision_sinW2(0).lower             << "# sin^2 \\theta_W effective (leptonic)";
      line4 << 4 << FeynHiggs_precision_deltarho(0).central << "  " << FeynHiggs_precision_deltarho(0).upper           << "  " << FeynHiggs_precision_deltarho(0).lower          << "# \\Delta \\rho";
      line5 << 5 << GM2C_SUSY(0).central             << "  " << GM2C_SUSY(0).upper                       << "  " << GM2C_SUSY(0).lower                      << "# SUSY contribution to muon g-2";
      ewpo_block.push_back(line1);
      ewpo_block.push_back(line2);
      ewpo_block.push_back(line3);
      ewpo_block.push_back(line4);
      ewpo_block.push_back(line5);
      for (int i = 0; i < 2; i++)
      {
        slha[i].push_back(ewpo_block);
        Utils::FileLock mylock(filename_out[i]);
        mylock.get_lock();
        std::ofstream ofs(filename_out[i]);
        ofs << slha[i];
        ofs.close();
        mylock.release_lock();
        cout << endl << "SLHA file " << filename_out[i] << " successfully emitted.";
      }
      cout << endl << endl;

    }

    // Be sure to do something sensible in cases where the point was invalidated by one of the functions.
    catch (Gambit::invalid_point_exception& e)
    {
      cout << endl << "Model is invalid according to " << e.thrower()->origin() << "::" << e.thrower()->name() << "." << endl;
      cout << "Reason: " << e.message() << endl;
    }

    cout << endl << "3-BIT-HIT has finished." << endl << endl;
    return 0;

  }

  catch (std::exception& e)
  {
    cout << endl << "3-BIT-HIT has exited with fatal exception: " << e.what() << endl << endl;
  }

  return(1);

}
