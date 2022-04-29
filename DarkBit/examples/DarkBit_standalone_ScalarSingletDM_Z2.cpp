//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example of GAMBIT DarkBit standalone
///  main program.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///  \date 2016 Feb
///  \author Sebastian Wild
///  \date 2016 Aug
///  \author Jonathan Cornell
///  \date 2016, 2020
///
///  *********************************************

#include "gambit/Elements/standalone_module.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Models/SimpleSpectra/MSSMSimpleSpec.hpp"
#include "gambit/Utils/util_functions.hpp"

using namespace DarkBit::Functown;     // Functors wrapping the module's actual module functions
using namespace BackendIniBit::Functown;    // Functors wrapping the backend initialisation functions

QUICK_FUNCTION(DarkBit, decay_rates, NEW_CAPABILITY, createDecays, DecayTable, ())
QUICK_FUNCTION(DarkBit, ScalarSingletDM_Z2_spectrum, OLD_CAPABILITY, createSpectrum, Spectrum, ScalarSingletDM_Z2)
QUICK_FUNCTION(DarkBit, cascadeMC_gammaSpectra, OLD_CAPABILITY, CMC_dummy, DarkBit::stringFunkMap, ())


namespace Gambit
{

  namespace DarkBit
  {

    // Dummy functor for returning empty cascadeMC result spectra
    void CMC_dummy(DarkBit::stringFunkMap& result)
    {
      DarkBit::stringFunkMap sfm;
      result = sfm;
    }

    // Create spectrum object from SLHA file SM.slha and ScalarSingletDM_Z2 model parameters
    void createSpectrum(Spectrum& outSpec)
    {
      using namespace Pipes::createSpectrum;
      std::string inputFileName = "DarkBit/data/SM.slha";

      Models::ScalarSingletDM_Z2Model singletmodel;
      singletmodel.HiggsPoleMass   = 125.;
      singletmodel.HiggsVEV        = 246.;
      singletmodel.SingletPoleMass = *Param["mS"];
      singletmodel.SingletLambda   = *Param["lambda_hS"];

      SLHAstruct slhaea = read_SLHA(inputFileName);
      outSpec = spectrum_from_SLHAea<Models::ScalarSingletDM_Z2SimpleSpec, Models::ScalarSingletDM_Z2Model>(singletmodel, slhaea, Spectrum::mc_info(), Spectrum::mr_info());
    }

    // Create decay object from SLHA file decays.slha
    void createDecays(DecayTable& outDecays)
    {
      using namespace Pipes::createDecays;

      std::string filename = "DarkBit/data/decays.slha";
      outDecays = DecayTable(filename);
    }
  }
}

int main()
{

  try
  {

    std::cout << std::endl
              << "Start DarkBit Scalar Singlet DM standalone example!" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "This program needs DarkBit/data/SM.slha for SM parameters and            " << std::endl;
    std::cout << "DarkBit/data/decays.slha for the Higgs width and branching fraction. If  " << std::endl;
    std::cout << "these are not present, it dies!"                                           << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << std::endl;

    // ---- Initialise logging and exceptions ----

    initialise_standalone_logs("runs/DarkBit_standalone_ScalarSingletDM_Z2/logs/");
    logger()<<"Running DarkBit standalone example"<<LogTags::info<<EOM;
    model_warning().set_fatal(true);


    // ---- Check that required backends are present ----

    if (not Backends::backendInfo().works["DarkSUSY_generic_wimp6.2.5"]) backend_error().raise(LOCAL_INFO, "DarkSUSY 6.2.5 for a generic WIMP is missing!");
    if (not Backends::backendInfo().works["MicrOmegas_ScalarSingletDM_Z23.6.9.2"]) backend_error().raise(LOCAL_INFO, "MicrOmegas 3.6.9.2 for ScalarSingletDM_Z2 is missing!");
    if (not Backends::backendInfo().works["gamLike1.0.1"]) backend_error().raise(LOCAL_INFO, "gamLike 1.0.1 is missing!");
    if (not Backends::backendInfo().works["DDCalc2.2.0"]) backend_error().raise(LOCAL_INFO, "DDCalc 2.2.0 is missing!");
    if (not Backends::backendInfo().works["nulike1.0.9"]) backend_error().raise(LOCAL_INFO, "nulike 1.0.9 is missing!");


    // ---- Initialize models ----

    // Initialize ScalarSingletDM_Z2 model -- Adjust the model parameters here:
    ModelParameters* SingletDM_primary_parameters = Models::ScalarSingletDM_Z2::Functown::primary_parameters.getcontentsPtr();
    SingletDM_primary_parameters->setValue("mS", 1000.);
    SingletDM_primary_parameters->setValue("lambda_hS", 1.0);

    // Initialize halo model
    ModelParameters* Halo_primary_parameters = Models::Halo_Einasto::Functown::primary_parameters.getcontentsPtr();
    Halo_primary_parameters->setValue("rho0", 0.4);
    Halo_primary_parameters->setValue("rhos", 0.08);
    Halo_primary_parameters->setValue("vrot", 235.);
    Halo_primary_parameters->setValue("v0", 235.);
    Halo_primary_parameters->setValue("vesc", 550.);
    Halo_primary_parameters->setValue("rs", 20.);
    Halo_primary_parameters->setValue("r_sun", 8.5);
    Halo_primary_parameters->setValue("alpha", 0.17);


    // --- Resolve halo dependencies ---
    ExtractLocalMaxwellianHalo.notifyOfModel("Halo_Einasto");
    ExtractLocalMaxwellianHalo.resolveDependency(&Models::Halo_Einasto::Functown::primary_parameters);
    ExtractLocalMaxwellianHalo.reset_and_calculate();

    GalacticHalo_Einasto.notifyOfModel("Halo_Einasto");
    GalacticHalo_Einasto.resolveDependency(&Models::Halo_Einasto::Functown::primary_parameters);
    GalacticHalo_Einasto.reset_and_calculate();

    // Initialize nuclear_params_fnq model
    ModelParameters* nuclear_params_fnq = Models::nuclear_params_fnq::Functown::primary_parameters.getcontentsPtr();
    nuclear_params_fnq->setValue("fpd", 0.034);
    nuclear_params_fnq->setValue("fpu", 0.023);
    nuclear_params_fnq->setValue("fps", 0.14);
    nuclear_params_fnq->setValue("fnd", 0.041);
    nuclear_params_fnq->setValue("fnu", 0.019);
    nuclear_params_fnq->setValue("fns", 0.14);
    nuclear_params_fnq->setValue("deltad", -0.40);
    nuclear_params_fnq->setValue("deltau", 0.74);
    nuclear_params_fnq->setValue("deltas", -0.12);


    // ---- Initialize spectrum and decays ---

    createSpectrum.notifyOfModel("ScalarSingletDM_Z2");
    createSpectrum.resolveDependency(&Models::ScalarSingletDM_Z2::Functown::primary_parameters);
    createSpectrum.reset_and_calculate();

    createDecays.notifyOfModel("ScalarSingletDM_Z2");
    createDecays.reset_and_calculate();


    // ---- Set up basic internal structures for direct & indirect detection ----

    // Set identifier for DM particle
    DarkMatter_ID_ScalarSingletDM.notifyOfModel("ScalarSingletDM_Z2");
    DarkMatter_ID_ScalarSingletDM.reset_and_calculate();
    DarkMatterConj_ID_ScalarSingletDM.notifyOfModel("ScalarSingletDM_Z2");
    DarkMatterConj_ID_ScalarSingletDM.reset_and_calculate();

    // Set up process catalog
    TH_ProcessCatalog_ScalarSingletDM_Z2.notifyOfModel("ScalarSingletDM_Z2");
    TH_ProcessCatalog_ScalarSingletDM_Z2.resolveDependency(&createSpectrum);
    TH_ProcessCatalog_ScalarSingletDM_Z2.resolveDependency(&createDecays);
    TH_ProcessCatalog_ScalarSingletDM_Z2.reset_and_calculate();

    // Assume for direct and indirect detection likelihoods that dark matter
    // density is always the measured one (despite relic density results)
    RD_fraction_one.reset_and_calculate();

    // Set generic WIMP mass object
    WIMP_properties.notifyOfModel("ScalarSingletDM_Z2");
    WIMP_properties.resolveDependency(&DarkMatter_ID_ScalarSingletDM);
    WIMP_properties.resolveDependency(&DarkMatterConj_ID_ScalarSingletDM);
    WIMP_properties.resolveDependency(&createSpectrum);
    WIMP_properties.reset_and_calculate();
    mwimp_generic.resolveDependency(&WIMP_properties);
    mwimp_generic.reset_and_calculate();

    // Set generic annihilation rate in late universe (v->0 limit)
    sigmav_late_universe.resolveDependency(&TH_ProcessCatalog_ScalarSingletDM_Z2);
    sigmav_late_universe.resolveDependency(&DarkMatter_ID_ScalarSingletDM);
    sigmav_late_universe.resolveDependency(&DarkMatterConj_ID_ScalarSingletDM);
    sigmav_late_universe.reset_and_calculate();

    // ---- Initialize backends ----

    // Initialize nulike backend
    Backends::nulike_1_0_9::Functown::nulike_bounds.setStatus(2);
    nulike_1_0_9_init.reset_and_calculate();

    // Initialize gamLike backend
    gamLike_1_0_1_init.reset_and_calculate();

    // Initialize MicrOmegas backend (specific for ScalarSingletDM_Z2)
    MicrOmegas_ScalarSingletDM_Z2_3_6_9_2_init.notifyOfModel("ScalarSingletDM_Z2");
    MicrOmegas_ScalarSingletDM_Z2_3_6_9_2_init.resolveDependency(&createSpectrum);
    MicrOmegas_ScalarSingletDM_Z2_3_6_9_2_init.resolveDependency(&createDecays);
    MicrOmegas_ScalarSingletDM_Z2_3_6_9_2_init.reset_and_calculate();
    // For the below VXdecay = 0 - no 3 body final states via virtual X
    //                         1 - annihilations to 3 body final states via virtual X
    //                         2 - (co)annihilations to 3 body final states via virtual X
    MicrOmegas_ScalarSingletDM_Z2_3_6_9_2_init.setOption<int>("VZdecay", 1);
    MicrOmegas_ScalarSingletDM_Z2_3_6_9_2_init.setOption<int>("VWdecay", 1);
    MicrOmegas_ScalarSingletDM_Z2_3_6_9_2_init.reset_and_calculate();

    // Initialize DarkSUSY backend
    DarkSUSY_generic_wimp_6_2_5_init.reset_and_calculate();

    // Initialize DarkSUSY Local Halo Model
    DarkSUSY_PointInit_LocalHalo_func.resolveDependency(&ExtractLocalMaxwellianHalo);
    DarkSUSY_PointInit_LocalHalo_func.resolveDependency(&RD_fraction_one);
    DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::dshmcom);
    DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::dshmisodf);
    DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::dshmframevelcom);
    DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::dshmnoclue);
    DarkSUSY_PointInit_LocalHalo_func.reset_and_calculate();

    // ---- Relic density ----

    // Relic density calculation with MicrOmegas
    RD_oh2_Xf_MicrOmegas.notifyOfModel("ScalarSingletDM_Z2");
    RD_oh2_Xf_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_ScalarSingletDM_Z2_3_6_9_2::Functown::darkOmega);
    RD_oh2_Xf_MicrOmegas.reset_and_calculate();
    RD_oh2_MicrOmegas.resolveDependency(&RD_oh2_Xf_MicrOmegas);
    RD_oh2_MicrOmegas.reset_and_calculate();

    // Retrieve and print MicrOmegas result
    logger() << "Omega h^2 from MicrOmegas: " << RD_oh2_MicrOmegas(0) << LogTags::info << EOM;

    // Relic density calculation with GAMBIT (DarkSUSY Boltzmann solver)
    RD_spectrum_from_ProcessCatalog.resolveDependency(&TH_ProcessCatalog_ScalarSingletDM_Z2);
    RD_spectrum_from_ProcessCatalog.resolveDependency(&DarkMatter_ID_ScalarSingletDM);
    RD_spectrum_from_ProcessCatalog.resolveDependency(&DarkMatterConj_ID_ScalarSingletDM);
    RD_spectrum_from_ProcessCatalog.reset_and_calculate();

    RD_eff_annrate_from_ProcessCatalog.resolveDependency(&TH_ProcessCatalog_ScalarSingletDM_Z2);
    RD_eff_annrate_from_ProcessCatalog.resolveDependency(&DarkMatter_ID_ScalarSingletDM);
    RD_eff_annrate_from_ProcessCatalog.resolveDependency(&DarkMatterConj_ID_ScalarSingletDM);
    RD_eff_annrate_from_ProcessCatalog.reset_and_calculate();

    RD_spectrum_ordered_func.resolveDependency(&RD_spectrum_from_ProcessCatalog);
    RD_spectrum_ordered_func.reset_and_calculate();

    RD_oh2_DS_general.resolveDependency(&RD_spectrum_ordered_func);
    RD_oh2_DS_general.resolveDependency(&RD_eff_annrate_from_ProcessCatalog);
    RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::rdpars);
    RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::rdtime);
    RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::dsrdcom);
    RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::dsrdstart);
    RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::dsrdens);
    RD_oh2_DS_general.setOption<int>("fast", 1);  // 0: normal; 1: fast; 2: dirty
    RD_oh2_DS_general.reset_and_calculate();

    // Retrieve and print GAMBIT result
    logger() << "Omega h^2 from GAMBIT: " << RD_oh2_DS_general(0) << LogTags::info << EOM;

    // Calculate WMAP likelihoods
    // Uncomment one of the following two line to choose which Omega h^2 value to use
    //lnL_oh2_Simple.resolveDependency(&RD_oh2_MicrOmegas);
    lnL_oh2_Simple.resolveDependency(&RD_oh2_DS_general);
    lnL_oh2_Simple.reset_and_calculate();

    logger() << "Relic density lnL: " << lnL_oh2_Simple((0)) << LogTags::info << EOM;

    // ---- Direct detection -----

    // Calculate DD couplings with Micromegas

    DD_couplings_MicrOmegas.notifyOfModel("ScalarSingletDM_Z2");
    DD_couplings_MicrOmegas.notifyOfModel("nuclear_params_fnq");
    DD_couplings_MicrOmegas.resolveDependency(&Models::nuclear_params_fnq::Functown::primary_parameters);
    DD_couplings_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_ScalarSingletDM_Z2_3_6_9_2::Functown::nucleonAmplitudes);
    DD_couplings_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_ScalarSingletDM_Z2_3_6_9_2::Functown::FeScLoop);
    DD_couplings_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_ScalarSingletDM_Z2_3_6_9_2::Functown::mocommon_);
    DD_couplings_MicrOmegas.reset_and_calculate();

    // Calculate DD couplings with GAMBIT

    DD_couplings_ScalarSingletDM_Z2.notifyOfModel("nuclear_params_fnq");
    DD_couplings_ScalarSingletDM_Z2.notifyOfModel("ScalarSingletDM_Z2");
    DD_couplings_ScalarSingletDM_Z2.resolveDependency(&Models::nuclear_params_fnq::Functown::primary_parameters);
    DD_couplings_ScalarSingletDM_Z2.resolveDependency(&createSpectrum);
    DD_couplings_ScalarSingletDM_Z2.reset_and_calculate();

    // Set generic scattering cross-sections for later use
    double sigma_SI_p_GB, sigma_SI_p_MO;

    sigma_SI_p_simple.resolveDependency(&DD_couplings_MicrOmegas);
    sigma_SI_p_simple.resolveDependency(&mwimp_generic);
    sigma_SI_p_simple.reset_and_calculate();
    sigma_SI_p_MO = sigma_SI_p_simple(0);

    sigma_SD_p_simple.resolveDependency(&DD_couplings_MicrOmegas);
    sigma_SD_p_simple.resolveDependency(&mwimp_generic);
    sigma_SD_p_simple.reset_and_calculate();

    logger() << "sigma_SI,p with MicrOmegas: " << sigma_SI_p_simple(0) << LogTags::info << EOM;

    // Set generic scattering cross-sections for later use
    sigma_SI_p_simple.resolveDependency(&DD_couplings_ScalarSingletDM_Z2);
    sigma_SI_p_simple.reset_and_calculate();
    sigma_SI_p_GB = sigma_SI_p_simple(0);

    sigma_SD_p_simple.resolveDependency(&DD_couplings_ScalarSingletDM_Z2);
    sigma_SD_p_simple.reset_and_calculate();

    logger() << "sigma_SI,p with GAMBIT: " << sigma_SI_p_simple(0) << LogTags::info << EOM;

    // Initialize DDCalc backend
    Backends::DDCalc_2_2_0::Functown::DDCalc_CalcRates_simple.setStatus(2);
    Backends::DDCalc_2_2_0::Functown::DDCalc_Experiment.setStatus(2);
    Backends::DDCalc_2_2_0::Functown::DDCalc_LogLikelihood.setStatus(2);

    // Calculate DD couplings for DDCalc
    DDCalc_Couplings_WIMP_nucleon.resolveDependency(&DD_couplings_ScalarSingletDM_Z2);
    DDCalc_Couplings_WIMP_nucleon.reset_and_calculate();

    DDCalc_2_2_0_init.resolveDependency(&ExtractLocalMaxwellianHalo);
    DDCalc_2_2_0_init.resolveDependency(&RD_fraction_one);
    DDCalc_2_2_0_init.resolveDependency(&mwimp_generic);
    // Choose one of the two below lines to determine where the couplings used in the likelihood
    // calculation come from
    DDCalc_2_2_0_init.resolveDependency(&DDCalc_Couplings_WIMP_nucleon);
    //DDCalc_2_2_0_init.resolveDependency(&DD_couplings_MicrOmegas);
    DDCalc_2_2_0_init.reset_and_calculate();

    // Calculate direct detection rates for LUX 2016
    LUX_2016_Calc.resolveBackendReq(&Backends::DDCalc_2_2_0::Functown::DDCalc_Experiment);
    LUX_2016_Calc.resolveBackendReq(&Backends::DDCalc_2_2_0::Functown::DDCalc_CalcRates_simple);
    LUX_2016_Calc.reset_and_calculate();

    // Calculate direct detection likelihood for LUX 2016
    LUX_2016_GetLogLikelihood.resolveDependency(&LUX_2016_Calc);
    LUX_2016_GetLogLikelihood.resolveBackendReq(&Backends::DDCalc_2_2_0::Functown::DDCalc_Experiment);
    LUX_2016_GetLogLikelihood.resolveBackendReq(&Backends::DDCalc_2_2_0::Functown::DDCalc_LogLikelihood);
    LUX_2016_GetLogLikelihood.reset_and_calculate();

    logger() << "LUX_2016 lnL: " << LUX_2016_GetLogLikelihood(0) << LogTags::info << EOM;

    // ---- Gamma-ray yields ----

    // Initialize tabulated gamma-ray yields
    GA_SimYieldTable_DarkSUSY.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::dsanyield_sim);
    GA_SimYieldTable_DarkSUSY.reset_and_calculate();
    Combine_SimYields.resolveDependency(&GA_SimYieldTable_DarkSUSY);
    // Here we need to establish the dependency chain from Combine_SimYields down to cascadeMC_gammaSpectra
    // *before* Combine_SimYields runs in order for it to correctly realise that it needs to enable gammas.
    cascadeMC_InitialStates.resolveDependency(&Combine_SimYields);
    cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_InitialStates);
    Combine_SimYields.reset_and_calculate();

    // Identify process as annihilation rather than decay
    DM_process_from_ProcessCatalog.resolveDependency(&TH_ProcessCatalog_ScalarSingletDM_Z2);
    DM_process_from_ProcessCatalog.resolveDependency(&DarkMatter_ID_ScalarSingletDM);
    DM_process_from_ProcessCatalog.reset_and_calculate();

    // Infer for which type of final states particles MC should be performed
    cascadeMC_FinalStates.setOption<std::vector<std::string>>("cMC_finalStates", daFunk::vec((std::string)"gamma"));
    // Here we need to establish the dependency chain from cascadeMC_FinalStates down to cascadeMC_gammaSpectra
    // *before* cascadeMC_FinalStates runs in order for it to correctly realise that it needs to enable gammas.
    cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_FinalStates);
    cascadeMC_FinalStates.reset_and_calculate();

    // Set up initial states for cascade MC
    cascadeMC_InitialStates.resolveDependency(&cascadeMC_FinalStates);
    cascadeMC_InitialStates.resolveDependency(&DarkMatter_ID_ScalarSingletDM);
    cascadeMC_InitialStates.resolveDependency(&DarkMatterConj_ID_ScalarSingletDM);
    cascadeMC_InitialStates.resolveDependency(&TH_ProcessCatalog_ScalarSingletDM_Z2);
    cascadeMC_InitialStates.resolveDependency(&DM_process_from_ProcessCatalog);
    cascadeMC_InitialStates.reset_and_calculate();

    // Collect decay information for cascade MC
    cascadeMC_DecayTable.resolveDependency(&TH_ProcessCatalog_ScalarSingletDM_Z2);
    cascadeMC_DecayTable.resolveDependency(&Combine_SimYields);
    cascadeMC_DecayTable.reset_and_calculate();

    // Set up MC loop manager for cascade MC
    cascadeMC_LoopManager.resolveDependency(&cascadeMC_InitialStates);
    std::vector<functor*> nested_functions = initVector<functor*>(
        &cascadeMC_GenerateChain, &cascadeMC_Histograms, &cascadeMC_EventCount);
    cascadeMC_LoopManager.setNestedList(nested_functions);

    // Perform MC step for cascade MC
    cascadeMC_GenerateChain.resolveDependency(&cascadeMC_DecayTable);
    cascadeMC_GenerateChain.resolveLoopManager(&cascadeMC_LoopManager);

    // Generate histogram for cascade MC
    cascadeMC_Histograms.resolveDependency(&cascadeMC_GenerateChain);
    cascadeMC_Histograms.resolveDependency(&TH_ProcessCatalog_ScalarSingletDM_Z2);
    cascadeMC_Histograms.resolveDependency(&Combine_SimYields);
    cascadeMC_Histograms.resolveDependency(&cascadeMC_FinalStates);
    cascadeMC_Histograms.resolveLoopManager(&cascadeMC_LoopManager);

    // Check convergence of cascade MC
    cascadeMC_EventCount.resolveLoopManager(&cascadeMC_LoopManager);

    // Start cascade MC loop
    cascadeMC_LoopManager.reset_and_calculate();

    // Infer gamma-ray spectra for recorded MC results
    cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_Histograms);
    cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_EventCount);
    cascadeMC_gammaSpectra.reset_and_calculate();

    // Calculate total gamma-ray yield (cascade MC + tabulated results)
    GA_AnnYield_General.resolveDependency(&TH_ProcessCatalog_ScalarSingletDM_Z2);
    GA_AnnYield_General.resolveDependency(&GA_SimYieldTable_DarkSUSY);
    GA_AnnYield_General.resolveDependency(&DarkMatter_ID_ScalarSingletDM);
    GA_AnnYield_General.resolveDependency(&DarkMatterConj_ID_ScalarSingletDM);
    GA_AnnYield_General.resolveDependency(&cascadeMC_gammaSpectra);
    GA_AnnYield_General.reset_and_calculate();

    // Calculate Fermi LAT dwarf likelihood
    lnL_FermiLATdwarfs_gamLike.resolveDependency(&GA_AnnYield_General);
    lnL_FermiLATdwarfs_gamLike.resolveDependency(&RD_fraction_one);
    lnL_FermiLATdwarfs_gamLike.resolveDependency(&DM_process_from_ProcessCatalog);
    lnL_FermiLATdwarfs_gamLike.resolveBackendReq(&Backends::gamLike_1_0_1::Functown::lnL);
    lnL_FermiLATdwarfs_gamLike.reset_and_calculate();

    logger() << "Fermi LAT dwarf spheroidal lnL: " << lnL_FermiLATdwarfs_gamLike(0) << LogTags::info << EOM;

    // ---- IceCube limits ----

    // Infer WIMP capture rate in Sun
    capture_rate_Sun_const_xsec.resolveDependency(&mwimp_generic);
    capture_rate_Sun_const_xsec.resolveDependency(&sigma_SI_p_simple);
    capture_rate_Sun_const_xsec.resolveDependency(&sigma_SD_p_simple);
    capture_rate_Sun_const_xsec.resolveDependency(&RD_fraction_one);
    capture_rate_Sun_const_xsec.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::dssenu_capsuntab);
    capture_rate_Sun_const_xsec.resolveDependency(&ExtractLocalMaxwellianHalo);
    capture_rate_Sun_const_xsec.resolveDependency(&DarkSUSY_PointInit_LocalHalo_func);
    capture_rate_Sun_const_xsec.reset_and_calculate();

    // Infer WIMP equilibration time in Sun
    equilibration_time_Sun.resolveDependency(&TH_ProcessCatalog_ScalarSingletDM_Z2);
    equilibration_time_Sun.resolveDependency(&DarkMatter_ID_ScalarSingletDM);
    equilibration_time_Sun.resolveDependency(&DarkMatterConj_ID_ScalarSingletDM);
    equilibration_time_Sun.resolveDependency(&mwimp_generic);
    equilibration_time_Sun.resolveDependency(&capture_rate_Sun_const_xsec);
    equilibration_time_Sun.reset_and_calculate();

    // Infer WIMP annihilation rate in Sun
    annihilation_rate_Sun.resolveDependency(&equilibration_time_Sun);
    annihilation_rate_Sun.resolveDependency(&capture_rate_Sun_const_xsec);
    annihilation_rate_Sun.reset_and_calculate();

    // Infer neutrino yield from Sun
    nuyield_from_DS.resolveDependency(&TH_ProcessCatalog_ScalarSingletDM_Z2);
    nuyield_from_DS.resolveDependency(&mwimp_generic);
    nuyield_from_DS.resolveDependency(&sigmav_late_universe);
    nuyield_from_DS.resolveDependency(&DarkMatter_ID_ScalarSingletDM);
    nuyield_from_DS.resolveDependency(&DarkMatterConj_ID_ScalarSingletDM);
    nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::dsgenericwimp_nusetup);
    nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::neutrino_yield);
    nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::DS_neutral_h_decay_channels);
    nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_generic_wimp_6_2_5::Functown::DS_charged_h_decay_channels);
    nuyield_from_DS.reset_and_calculate();

    // Calculate number of events at IceCube
    IC79WH_full.resolveDependency(&mwimp_generic);
    IC79WH_full.resolveDependency(&annihilation_rate_Sun);
    IC79WH_full.resolveDependency(&nuyield_from_DS);
    IC79WH_full.resolveBackendReq(&Backends::nulike_1_0_9::Functown::nulike_bounds);
    IC79WH_full.reset_and_calculate();
    IC79WL_full.resolveDependency(&mwimp_generic);
    IC79WL_full.resolveDependency(&annihilation_rate_Sun);
    IC79WL_full.resolveDependency(&nuyield_from_DS);
    IC79WL_full.resolveBackendReq(&Backends::nulike_1_0_9::Functown::nulike_bounds);
    IC79WL_full.reset_and_calculate();
    IC79SL_full.resolveDependency(&mwimp_generic);
    IC79SL_full.resolveDependency(&annihilation_rate_Sun);
    IC79SL_full.resolveDependency(&nuyield_from_DS);
    IC79SL_full.resolveBackendReq(&Backends::nulike_1_0_9::Functown::nulike_bounds);
    IC79SL_full.reset_and_calculate();

    // Calculate IceCube likelihood
    IC79WH_bgloglike.resolveDependency(&IC79WH_full);
    IC79WH_bgloglike.reset_and_calculate();
    IC79WH_loglike.resolveDependency(&IC79WH_full);
    IC79WH_loglike.reset_and_calculate();
    IC79WL_bgloglike.resolveDependency(&IC79WL_full);
    IC79WL_bgloglike.reset_and_calculate();
    IC79WL_loglike.resolveDependency(&IC79WL_full);
    IC79WL_loglike.reset_and_calculate();
    IC79SL_bgloglike.resolveDependency(&IC79SL_full);
    IC79SL_bgloglike.reset_and_calculate();
    IC79SL_loglike.resolveDependency(&IC79SL_full);
    IC79SL_loglike.reset_and_calculate();
    IC79_loglike.resolveDependency(&IC79WH_bgloglike);
    IC79_loglike.resolveDependency(&IC79WH_loglike);
    IC79_loglike.resolveDependency(&IC79WL_bgloglike);
    IC79_loglike.resolveDependency(&IC79WL_loglike);
    IC79_loglike.resolveDependency(&IC79SL_bgloglike);
    IC79_loglike.resolveDependency(&IC79SL_loglike);
    IC79_loglike.reset_and_calculate();

    logger() << "IceCube 79 lnL: " << IC79_loglike(0) << LogTags::info << EOM;

    // ---- Dump results on screen ----

    cout << endl;
    cout << "Omega h^2 from MicrOmegas: " << RD_oh2_MicrOmegas(0) << endl;
    cout << "Omega h^2 from DarkSUSY (via DarkBit): " << RD_oh2_DS_general(0) << endl;
    cout << "Relic density lnL: " << lnL_oh2_Simple(0) << endl;
    cout << "sigma_SI,p with MicrOmegas: " << sigma_SI_p_MO << endl;
    cout << "sigma_SI,p with DarkBit: " << sigma_SI_p_GB << endl;
    cout << "LUX_2016 lnL: " << LUX_2016_GetLogLikelihood(0) << endl;
    cout << "Fermi LAT dwarf spheroidal lnL: " << lnL_FermiLATdwarfs_gamLike(0) << endl;
    cout << "IceCube 79 lnL: " << IC79_loglike(0) << endl;
  }

  catch (std::exception& e)
  {
    std::cout << "DarkBit_standalone_ScalarSingletDM_Z2 has exited with fatal exception: " << e.what() << std::endl;
  }

  return 0;
}
