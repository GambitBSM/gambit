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
///
///  \author Sebastian Wild
///  \date 2016 Aug
///
///  \author Pat Scott
///  \date 2016 Nov
///
///  \author Jonathan Cornell
///  \date 2016-2017
///
///  \author Torsten Bringmann
///  \date 2019 May, October
///
///  \author Anders Kvellestad
///  \date 2020 Feb
///
///  \author Ankit Beniwal
///  \date 2020
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
QUICK_FUNCTION(DarkBit, MSSM_spectrum, OLD_CAPABILITY, createSpectrum, Spectrum, ())
QUICK_FUNCTION(DarkBit, SLHA_pseudonyms, NEW_CAPABILITY, createSLHA1Names, mass_es_pseudonyms, (), (MSSM_spectrum, Spectrum))
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

    // Create spectrum object from SLHA file
    void createSpectrum(Spectrum& outSpec)
    {
      using namespace Pipes::createSpectrum;
      /// Option inputFileName<std::string>: Input SLHA (required)
      std::string inputFileName = runOptions->getValue<std::string>("filename");
      std::cout << "Loading spectrum from: " << inputFileName << std::endl;
      outSpec = spectrum_from_SLHA<MSSMSimpleSpec>(inputFileName, Spectrum::mc_info(), Spectrum::mr_info());
    }

    // Create decay object from SLHA file
    void createDecays(DecayTable& outDecays)
    {
      using namespace Pipes::createDecays;
      /// Option inputFileName<std::string>: Input SLHA (required)
      std::string inputFileName = runOptions->getValue<std::string>("filename");
      std::cout << "Loading decays from: " << inputFileName << std::endl;
      outDecays = DecayTable(inputFileName, 0, true);
    }

    // Create SLHA1 pseudonyms from Spectrum object
    void createSLHA1Names(mass_es_pseudonyms& names)
    {
      const double gauge_mixing_tol = 0.5;
      const bool tol_invalidates_pt = true;
      const bool debug = false;
      names.refill(Pipes::createSLHA1Names::Dep::MSSM_spectrum->get_HE(), gauge_mixing_tol, tol_invalidates_pt, debug);
    }

  }
}

int main(int argc, char* argv[])
{
  std::cout << std::endl;
  std::cout << "Welcome to the DarkBit MSSM standalone program!" << std::endl;
  std::cout << std::endl;
  std::cout << "********************************************************************************" << std::endl;
  std::cout << "Usage: DarkBit_standalone_MSSM SLHA_file (spectrum) (output)" << std::endl;
  std::cout << std::endl;
  std::cout << "SLHA_file: SLHA file used to intialise the program (required)" << std::endl;
  std::cout << "(spectrum): name of output file for gamma-ray spectrum (default: BACKENDNAME_dNdE.dat)" << std::endl;
  std::cout << "(output): name of output file for observables and likelihoods (default: DarkBit_standalone_MSSM.out)" << std::endl;
  std::cout << std::endl;
  std::cout << "The SLHA files for the MSSM-7 benchmarks in the DarkBit paper are located in    " << std::endl;
  std::cout << "DarkBit/data/benchmarks/                                                        " << std::endl;
  std::cout << "********************************************************************************" << std::endl;
  std::cout << std::endl;

  try
  {
    if (argc == 1)
    {
      std::cout << "Please provide name of SLHA file at command line." << std::endl;
      exit(1);
    }
    std::string filename = argv[1];
    std::string outname_dNdE_spectrum = "dNdE.dat";
    if (argc >= 3) outname_dNdE_spectrum = argv[2];
    std::string outname_data = "DarkBit_standalone_MSSM.out";
    if (argc >= 4) outname_data = argv[3];


    // ---- Initialise logging and exceptions ----

    initialise_standalone_logs("runs/DarkBit_standalone_MSSM/logs/");
    logger()<<"Running DarkBit standalone example"<<LogTags::info<<EOM;
    model_warning().set_fatal(true);

    // ---- Check which backends are present ----
    if (not Backends::backendInfo().works["gamLike1.0.1"]) backend_error().raise(LOCAL_INFO, "gamLike 1.0.1 is missing!");
    if (not Backends::backendInfo().works["DDCalc2.2.0"]) backend_error().raise(LOCAL_INFO, "DDCalc 2.2.0 is missing!");
    if (not Backends::backendInfo().works["nulike1.0.9"]) backend_error().raise(LOCAL_INFO, "nulike 1.0.9 is missing!");

    // ---- Useful variables ----
    //
    // Prepare a str-str-double map of maps to hold the results.
    // We will add results for the individual backends as
    //   results["oh2"]["MicrOmegas_MSSM3.6.9.2"] = ...
    //   results["oh2"]["DarkSUSY_MSSM6.1.1"] = ...
    //
    std::map<std::string, std::map<std::string,double> > results;
    results["oh2"] = std::map<std::string,double>();
    results["oh2_lnL"] = std::map<std::string,double>();
    results["sigma_SI_p"] = std::map<std::string,double>();
    results["sigma_SD_p"] = std::map<std::string,double>();
    results["LUX_2016_lnL"] = std::map<std::string,double>();
    results["IceCube_79_lnL"] = std::map<std::string,double>();
    results["sigmav0"] = std::map<std::string,double>();
    results["FermiLAT_dwarfsph_lnL"] = std::map<std::string,double>();

    std::map<std::string, std::string> results_units;
    results_units["oh2"] = "";
    results_units["oh2_lnL"] = "";
    results_units["sigma_SI_p"] = "cm^2";
    results_units["sigma_SD_p"] = "cm^2";
    results_units["LUX_2016_lnL"] = "";
    results_units["IceCube_79_lnL"] = "";
    results_units["sigmav0"] = "cm^3/s";
    results_units["FermiLAT_dwarfsph_lnL"] = "";

    std::vector<std::string> result_output_order = {
      "oh2",
      "oh2_lnL",
      "sigma_SI_p",
      "sigma_SD_p",
      "LUX_2016_lnL",
      "IceCube_79_lnL",
      "sigmav0",
      "FermiLAT_dwarfsph_lnL",
    };


    // A string to refer to the current backend being used for calculations
    std::string current_backend = "";

    // Keep track of which backends are not installed
    std::vector<std::string> backends_not_built;

    // ---- Initialize models ----

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

    // Resolve other dependencies related directly to the GAMBIT Models
    DD_couplings_DarkSUSY_DS5.notifyOfModel("nuclear_params_fnq");
    DD_couplings_DarkSUSY_DS5.resolveDependency(&Models::nuclear_params_fnq::Functown::primary_parameters);

    DD_couplings_DarkSUSY_MSSM.notifyOfModel("nuclear_params_fnq");
    DD_couplings_DarkSUSY_MSSM.resolveDependency(&Models::nuclear_params_fnq::Functown::primary_parameters);

    DD_couplings_MicrOmegas.notifyOfModel("MSSM30atQ");
    DD_couplings_MicrOmegas.notifyOfModel("nuclear_params_fnq");
    DD_couplings_MicrOmegas.resolveDependency(&Models::nuclear_params_fnq::Functown::primary_parameters);


    // ---- Initialize spectrum and decays from SLHA file ----
    createSpectrum.setOption<std::string>("filename", filename);
    createSpectrum.reset_and_calculate();
    createSLHA1Names.resolveDependency(&createSpectrum);
    createSLHA1Names.reset_and_calculate();
    createDecays.setOption<std::string>("filename", filename);
    createDecays.reset_and_calculate();

    // Check that the decay table contains ~chi0_2 (if it doesn't,
    // we do not use information from the SLHA decay block)
    bool decays = true;
    try { createDecays(0).at("~chi0_2"); }
    catch(std::exception& e)
    {
        decays = false;
        cout << "It appears that the decay block is missing from the SLHA file. Decay widths\n"
                "will be determined by the backends." << endl;
    }

    // Set identifier for DM particle
    DarkMatter_ID_MSSM.resolveDependency(&createSpectrum);
    DarkMatter_ID_MSSM.reset_and_calculate();
    DarkMatterConj_ID_MSSM.resolveDependency(&createSpectrum);
    DarkMatterConj_ID_MSSM.reset_and_calculate();

    // Assume for direct and indirect detection likelihoods that dark matter
    // density is always the measured one (regardless of relic density results)
    RD_fraction_one.reset_and_calculate();

    //
    // ======= Initializations that can be done once =======
    //

    // Initialize nulike backend
    Backends::nulike_1_0_9::Functown::nulike_bounds.setStatus(2);
    nulike_1_0_9_init.reset_and_calculate();

    // Initialize gamLike backend
    gamLike_1_0_1_init.reset_and_calculate();



    //
    // ======= Perform all calculations for backend DarkSUSY 5.1.3 =======
    //

    current_backend = "DarkSUSY5.1.3";

    if (not Backends::backendInfo().works[current_backend])
    {
      backends_not_built.push_back(current_backend);
    }
    else
    {
      // Initialize DarkSUSY 5 backend
      DarkSUSY_5_1_3_init.notifyOfModel("MSSM30atQ");
      DarkSUSY_5_1_3_init.resolveDependency(&createSpectrum);
      DarkSUSY_5_1_3_init.resolveDependency(&createDecays);
      if (decays) DarkSUSY_5_1_3_init.setOption<bool>("use_dsSLHAread", false);
      else DarkSUSY_5_1_3_init.setOption<bool>("use_dsSLHAread", true);
      DarkSUSY_5_1_3_init.reset_and_calculate();

      // Initialize DarkSUSY 5 Local Halo Model
      DarkSUSY5_PointInit_LocalHalo_func.resolveDependency(&ExtractLocalMaxwellianHalo);
      DarkSUSY5_PointInit_LocalHalo_func.resolveDependency(&RD_fraction_one);
      DarkSUSY5_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dshmcom);
      DarkSUSY5_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dshmisodf);
      DarkSUSY5_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dshmframevelcom);
      DarkSUSY5_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dshmnoclue);
      DarkSUSY5_PointInit_LocalHalo_func.reset_and_calculate();


      // Relic density calculation with GAMBIT routines and DarkSUSY 5:
      RD_spectrum_SUSY_DS5.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::mspctm);
      RD_spectrum_SUSY_DS5.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::widths);
      RD_spectrum_SUSY_DS5.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::intdof);
      RD_spectrum_SUSY_DS5.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::pacodes);
      RD_spectrum_SUSY_DS5.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::DSparticle_code);
      // Below true if charginos and neutralinos are included in coannihilations:
      RD_spectrum_SUSY_DS5.setOption<bool>("CoannCharginosNeutralinos", true);
      // Below true if sfermions are included in coannihilations:
      RD_spectrum_SUSY_DS5.setOption<bool>("CoannSfermions", true);
      // Maximum sparticle mass to be icluded in coannihilations, in units of DM mass:
      RD_spectrum_SUSY_DS5.setOption<double>("CoannMaxMass", 1.6);
      RD_spectrum_SUSY_DS5.reset_and_calculate();

      RD_spectrum_ordered_func.resolveDependency(&RD_spectrum_SUSY_DS5);
      RD_spectrum_ordered_func.reset_and_calculate();

      RD_annrate_DS5prep_func.resolveDependency(&RD_spectrum_SUSY_DS5);
      RD_annrate_DS5prep_func.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdmgev);
      RD_annrate_DS5prep_func.reset_and_calculate();

      RD_eff_annrate_DS5_MSSM.notifyOfModel("MSSM30atQ");
      RD_eff_annrate_DS5_MSSM.resolveDependency(&RD_annrate_DS5prep_func);
      RD_eff_annrate_DS5_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsanwx);
      RD_eff_annrate_DS5_MSSM.reset_and_calculate();

      RD_oh2_DS5_general.resolveDependency(&RD_spectrum_ordered_func);
      RD_oh2_DS5_general.resolveDependency(&RD_eff_annrate_DS5_MSSM);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsrdthlim);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsrdtab);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsrdeqn);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsrdwintp);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::DSparticle_code);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::widths);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdmgev);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdpth);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdpars);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdswitch);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdlun);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdpadd);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rddof);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rderrors);
      RD_oh2_DS5_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdtime);
      RD_oh2_DS5_general.setOption<int>("fast", 1);  // 0: normal; 1: fast; 2: dirty
      RD_oh2_DS5_general.reset_and_calculate();
      results["oh2"][current_backend] = RD_oh2_DS5_general(0);

      lnL_oh2_Simple.resolveDependency(&RD_oh2_DS5_general);
      lnL_oh2_Simple.reset_and_calculate();
      // Save the result
      results["oh2_lnL"][current_backend] = lnL_oh2_Simple(0);


      // ---- Set up basic internal structures for direct & indirect detection ----

      // Set up process catalog based on DarkSUSY annihilation rates
      TH_ProcessCatalog_DS5_MSSM.resolveDependency(&createSpectrum);
      TH_ProcessCatalog_DS5_MSSM.resolveDependency(&createDecays);
      TH_ProcessCatalog_DS5_MSSM.resolveDependency(&DarkMatter_ID_MSSM);
      TH_ProcessCatalog_DS5_MSSM.resolveDependency(&DarkMatterConj_ID_MSSM);
      TH_ProcessCatalog_DS5_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dssigmav);
      TH_ProcessCatalog_DS5_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsIBffdxdy);
      TH_ProcessCatalog_DS5_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsIBhhdxdy);
      TH_ProcessCatalog_DS5_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsIBwhdxdy);
      TH_ProcessCatalog_DS5_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsIBwwdxdy);
      TH_ProcessCatalog_DS5_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::IBintvars);
      TH_ProcessCatalog_DS5_MSSM.reset_and_calculate();

      // Set generic WIMP mass object
      WIMP_properties.notifyOfModel("MSSM30atQ");
      WIMP_properties.resolveDependency(&DarkMatter_ID_MSSM);
      WIMP_properties.resolveDependency(&DarkMatterConj_ID_MSSM);
      WIMP_properties.resolveDependency(&createSpectrum);
      WIMP_properties.reset_and_calculate();
      mwimp_generic.resolveDependency(&WIMP_properties);
      mwimp_generic.reset_and_calculate();

      // Set generic annihilation rate in late universe (v->0 limit)
      sigmav_late_universe.resolveDependency(&TH_ProcessCatalog_DS5_MSSM);
      sigmav_late_universe.resolveDependency(&DarkMatter_ID_MSSM);
      sigmav_late_universe.resolveDependency(&DarkMatterConj_ID_MSSM);
      sigmav_late_universe.reset_and_calculate();
      // Save the result
      results["sigmav0"][current_backend] = sigmav_late_universe(0);


      // ---- Direct detection -----

      // Calculate DD couplings with DarkSUSY
      // DD_couplings_DarkSUSY_DS5.notifyOfModel("nuclear_params_fnq");
      // DD_couplings_DarkSUSY_DS5.resolveDependency(&Models::nuclear_params_fnq::Functown::primary_parameters);
      DD_couplings_DarkSUSY_DS5.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::DD_couplings);
      DD_couplings_DarkSUSY_DS5.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::mspctm);
      DD_couplings_DarkSUSY_DS5.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::ddcom);
      // The below calculates the DD couplings using the full 1 loop calculation of
      // Drees Nojiri Phys.Rev. D48 (1993) 3483
      DD_couplings_DarkSUSY_DS5.setOption<bool>("loop", true);
      // Setting the below to false approximates the squark propagator as 1/m_sq^2 to avoid poles.
      // To reproduce numbers in Tables 11/12 of DarkBit paper (https://arxiv.org/abs/1705.07920), set "pole" to true.
      DD_couplings_DarkSUSY_DS5.setOption<bool>("pole", false);
      DD_couplings_DarkSUSY_DS5.reset_and_calculate();

      // Calculate DD couplings for DDCalc
      DDCalc_Couplings_WIMP_nucleon.resolveDependency(&DD_couplings_DarkSUSY_DS5);
      DDCalc_Couplings_WIMP_nucleon.reset_and_calculate();

      // Initialize DDCalc backend
      Backends::DDCalc_2_2_0::Functown::DDCalc_CalcRates_simple.setStatus(2);
      Backends::DDCalc_2_2_0::Functown::DDCalc_Experiment.setStatus(2);
      Backends::DDCalc_2_2_0::Functown::DDCalc_LogLikelihood.setStatus(2);
      DDCalc_2_2_0_init.resolveDependency(&ExtractLocalMaxwellianHalo);
      DDCalc_2_2_0_init.resolveDependency(&RD_fraction_one);
      DDCalc_2_2_0_init.resolveDependency(&mwimp_generic);
      DDCalc_2_2_0_init.resolveDependency(&DDCalc_Couplings_WIMP_nucleon);
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
      // Save the result
      results["LUX_2016_lnL"][current_backend] = LUX_2016_GetLogLikelihood(0);

      sigma_SI_p_simple.resolveDependency(&mwimp_generic);
      sigma_SI_p_simple.resolveDependency(&DD_couplings_DarkSUSY_DS5);
      sigma_SI_p_simple.reset_and_calculate();
      // Save the result
      results["sigma_SI_p"][current_backend] = sigma_SI_p_simple(0);

      sigma_SD_p_simple.resolveDependency(&mwimp_generic);
      sigma_SD_p_simple.resolveDependency(&DD_couplings_DarkSUSY_DS5);
      sigma_SD_p_simple.reset_and_calculate();
      // Save the result
      results["sigma_SD_p"][current_backend] = sigma_SD_p_simple(0);


      // ---- Gamma-ray yields ----

      // Initialize tabulated gamma-ray yields
      GA_SimYieldTable_DS5.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dshayield);
      GA_SimYieldTable_DS5.reset_and_calculate();
      Combine_SimYields.resolveDependency(&GA_SimYieldTable_DS5);
      // Here we need to establish the dependency chain from Combine_SimYields down to cascadeMC_gammaSpectra
      // *before* Combine_SimYields runs in order for it to correctly realise that it needs to enable gammas.
      cascadeMC_InitialStates.resolveDependency(&Combine_SimYields);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_InitialStates);
      Combine_SimYields.reset_and_calculate();

      // Identify process as annihilation rather than decay
      DM_process_from_ProcessCatalog.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      DM_process_from_ProcessCatalog.resolveDependency(&DarkMatter_ID_MSSM);
      DM_process_from_ProcessCatalog.reset_and_calculate();

      // Set up initial states for cascade MC
      cascadeMC_InitialStates.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_InitialStates.resolveDependency(&TH_ProcessCatalog_DS5_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DarkMatter_ID_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DarkMatterConj_ID_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DM_process_from_ProcessCatalog);
      cascadeMC_InitialStates.reset_and_calculate();

      // Infer for which type of final states particles MC should be performed
      cascadeMC_FinalStates.setOption<std::vector<std::string>>("cMC_finalStates", daFunk::vec<std::string>("gamma"));
      // Here we need to establish the dependency chain from cascadeMC_FinalStates down to cascadeMC_gammaSpectra
      // *before* cascadeMC_FinalStates runs in order for it to correctly realise that it needs to enable gammas.
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_FinalStates.reset_and_calculate();

      // Collect decay information for cascade MC
      cascadeMC_DecayTable.resolveDependency(&TH_ProcessCatalog_DS5_MSSM);
      cascadeMC_DecayTable.resolveDependency(&Combine_SimYields);
      cascadeMC_DecayTable.reset_and_calculate();

      // cascadeMC_LoopManager.setOption<int>("cMC_maxEvents", 100000);
      // cascadeMC_Histograms.setOption<double>("cMC_endCheckFrequency", 25);
      // cascadeMC_Histograms.setOption<double>("cMC_gammaRelError", .05);
      // cascadeMC_Histograms.setOption<int>("cMC_numSpecSamples", 25);
      // cascadeMC_Histograms.setOption<int>("cMC_NhistBins", 300);

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
      cascadeMC_Histograms.resolveDependency(&TH_ProcessCatalog_DS5_MSSM);
      cascadeMC_Histograms.resolveDependency(&Combine_SimYields);
      cascadeMC_Histograms.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_Histograms.resolveLoopManager(&cascadeMC_LoopManager);

      // Check convergence of cascade MC
      cascadeMC_EventCount.resolveLoopManager(&cascadeMC_LoopManager);

      // Start cascade MC loop
      cascadeMC_LoopManager.reset_and_calculate();

      // Infer gamma-ray spectra for recorded MC results
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_InitialStates);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_Histograms);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_EventCount);
      cascadeMC_gammaSpectra.reset_and_calculate();

      // Calculate total gamma-ray yield (cascade MC + tabulated results)
      GA_AnnYield_General.resolveDependency(&TH_ProcessCatalog_DS5_MSSM);
      GA_AnnYield_General.resolveDependency(&GA_SimYieldTable_DS5);
      GA_AnnYield_General.resolveDependency(&DarkMatter_ID_MSSM);
      GA_AnnYield_General.resolveDependency(&DarkMatterConj_ID_MSSM);
      GA_AnnYield_General.resolveDependency(&cascadeMC_gammaSpectra);
      GA_AnnYield_General.reset_and_calculate();

      // Dump spectrum into file
      dump_gammaSpectrum.resolveDependency(&GA_AnnYield_General);
      dump_gammaSpectrum.setOption<std::string>("filename", current_backend + "_" + outname_dNdE_spectrum);
      dump_gammaSpectrum.reset_and_calculate();

      // Calculate Fermi LAT dwarf likelihood
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&GA_AnnYield_General);
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&RD_fraction_one);
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&DM_process_from_ProcessCatalog);
      lnL_FermiLATdwarfs_gamLike.resolveBackendReq(&Backends::gamLike_1_0_1::Functown::lnL);
      lnL_FermiLATdwarfs_gamLike.reset_and_calculate();
      // Save the result
      results["FermiLAT_dwarfsph_lnL"][current_backend] = lnL_FermiLATdwarfs_gamLike(0);


      // ---- IceCube limits ----

      // Infer WIMP capture rate in Sun
      capture_rate_Sun_const_xsec_DS5.resolveDependency(&mwimp_generic);
      capture_rate_Sun_const_xsec_DS5.resolveDependency(&sigma_SI_p_simple);
      capture_rate_Sun_const_xsec_DS5.resolveDependency(&sigma_SD_p_simple);
      capture_rate_Sun_const_xsec_DS5.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsntcapsuntab);
      capture_rate_Sun_const_xsec_DS5.resolveDependency(&DarkSUSY5_PointInit_LocalHalo_func);
      capture_rate_Sun_const_xsec_DS5.reset_and_calculate();

      // Infer WIMP equilibration time in Sun
      equilibration_time_Sun.resolveDependency(&TH_ProcessCatalog_DS5_MSSM);
      equilibration_time_Sun.resolveDependency(&DarkMatter_ID_MSSM);
      equilibration_time_Sun.resolveDependency(&DarkMatterConj_ID_MSSM);
      equilibration_time_Sun.resolveDependency(&mwimp_generic);
      equilibration_time_Sun.resolveDependency(&capture_rate_Sun_const_xsec_DS5);
      equilibration_time_Sun.reset_and_calculate();

      // Infer WIMP annihilation rate in Sun
      annihilation_rate_Sun.resolveDependency(&equilibration_time_Sun);
      annihilation_rate_Sun.resolveDependency(&capture_rate_Sun_const_xsec_DS5);
      annihilation_rate_Sun.reset_and_calculate();

      // Infer neutrino yield from Sun
      nuyield_from_DS.resolveDependency(&TH_ProcessCatalog_DS5_MSSM);
      nuyield_from_DS.resolveDependency(&mwimp_generic);
      nuyield_from_DS.resolveDependency(&sigmav_late_universe);
      nuyield_from_DS.resolveDependency(&DarkMatter_ID_MSSM);
      nuyield_from_DS.resolveDependency(&DarkMatterConj_ID_MSSM);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsgenericwimp_nusetup);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::neutrino_yield);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::DS_neutral_h_decay_channels);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::DS_charged_h_decay_channels);
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
      // Save the result
      results["IceCube_79_lnL"][current_backend] = IC79_loglike(0);

    } // End of DarkSUSY 5.1.3 calculations




    //
    // ======= Perform all calculations for backend DarkSUSY_MSSM 6.1.1 =======
    //

    current_backend = "DarkSUSY_MSSM6.1.1";

    if (not Backends::backendInfo().works[current_backend])
    {
      backends_not_built.push_back(current_backend);
    }
    else
    {
      // Initialize DarkSUSY 6 MSSM backend
      DarkSUSY_MSSM_6_1_1_init.notifyOfModel("MSSM30atQ");
      DarkSUSY_MSSM_6_1_1_init.resolveDependency(&createSpectrum);
      DarkSUSY_MSSM_6_1_1_init.resolveDependency(&createDecays);
      if (decays) DarkSUSY_MSSM_6_1_1_init.setOption<bool>("use_dsSLHAread", false);
      else DarkSUSY_MSSM_6_1_1_init.setOption<bool>("use_dsSLHAread", true);
      DarkSUSY_MSSM_6_1_1_init.reset_and_calculate();

      // Initialize DarkSUSY 6 Local Halo Model
      DarkSUSY_PointInit_LocalHalo_func.resolveDependency(&ExtractLocalMaxwellianHalo);
      DarkSUSY_PointInit_LocalHalo_func.resolveDependency(&RD_fraction_one);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dshmcom);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dshmisodf);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dshmframevelcom);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dshmnoclue);
      DarkSUSY_PointInit_LocalHalo_func.reset_and_calculate();

      // Relic density calculation with GAMBIT routines and DarkSUSY 6:
      RD_spectrum_MSSM.resolveDependency(&createDecays);
      RD_spectrum_MSSM.resolveDependency(&createSpectrum);
      RD_spectrum_MSSM.resolveDependency(&DarkMatter_ID_MSSM);
      // Below true if charginos and neutralinos are included in coannihilations:
      RD_spectrum_MSSM.setOption<bool>("CoannCharginosNeutralinos", true);
      // Below true if sfermions are included in coannihilations:
      RD_spectrum_MSSM.setOption<bool>("CoannSfermions", true);
      // Maximum sparticle mass to be icluded in coannihilations, in units of DM mass:
      RD_spectrum_MSSM.setOption<double>("CoannMaxMass", 1.6);
      RD_spectrum_MSSM.reset_and_calculate();

      RD_spectrum_ordered_func.resolveDependency(&RD_spectrum_MSSM);
      RD_spectrum_ordered_func.reset_and_calculate();

      RD_annrate_DSprep_MSSM_func.resolveDependency(&RD_spectrum_ordered_func);
      RD_annrate_DSprep_MSSM_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsancoann);
      RD_annrate_DSprep_MSSM_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::DSparticle_code);
      RD_annrate_DSprep_MSSM_func.reset_and_calculate();

      RD_eff_annrate_DS_MSSM.notifyOfModel("MSSM30atQ");
      RD_eff_annrate_DS_MSSM.resolveDependency(&RD_annrate_DSprep_MSSM_func);
      RD_eff_annrate_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsanwx);
      RD_eff_annrate_DS_MSSM.reset_and_calculate();

      RD_oh2_DS_general.resolveDependency(&RD_spectrum_ordered_func);
      RD_oh2_DS_general.resolveDependency(&RD_eff_annrate_DS_MSSM);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::rdpars);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::rdtime);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsrdcom);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsrdstart);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsrdens);
      RD_oh2_DS_general.setOption<int>("fast", 1);  // 0: normal; 1: fast; 2: dirty
      RD_oh2_DS_general.reset_and_calculate();
      // Save the result
      results["oh2"][current_backend] = RD_oh2_DS_general(0);

      lnL_oh2_Simple.resolveDependency(&RD_oh2_DS_general);
      lnL_oh2_Simple.reset_and_calculate();
      // Save the result
      results["oh2_lnL"][current_backend] = lnL_oh2_Simple(0);


      // Set up process catalog based on DarkSUSY annihilation rates
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&createSpectrum);
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&createDecays);
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&DarkMatter_ID_MSSM);
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&DarkMatterConj_ID_MSSM);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dssigmav0);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dssigmav0tot);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsIBffdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsIBhhdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsIBwhdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsIBwwdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::IBintvars);
      TH_ProcessCatalog_DS_MSSM.reset_and_calculate();

      // Set generic WIMP mass object
      WIMP_properties.notifyOfModel("MSSM30atQ");
      WIMP_properties.resolveDependency(&DarkMatter_ID_MSSM);
      WIMP_properties.resolveDependency(&DarkMatterConj_ID_MSSM);
      WIMP_properties.resolveDependency(&createSpectrum);
      WIMP_properties.reset_and_calculate();
      mwimp_generic.resolveDependency(&WIMP_properties);
      mwimp_generic.reset_and_calculate();

      // Set generic annihilation rate in late universe (v->0 limit)
      sigmav_late_universe.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      sigmav_late_universe.resolveDependency(&DarkMatter_ID_MSSM);
      sigmav_late_universe.resolveDependency(&DarkMatterConj_ID_MSSM);
      sigmav_late_universe.reset_and_calculate();
      // Save the result
      results["sigmav0"][current_backend] = sigmav_late_universe(0);


      // ---- Gamma-ray yields ----

      // Initialize tabulated gamma-ray yields
      GA_SimYieldTable_DarkSUSY.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsanyield_sim);
      GA_SimYieldTable_DarkSUSY.reset_and_calculate();
      Combine_SimYields.resolveDependency(&GA_SimYieldTable_DarkSUSY);
      // Here we need to establish the dependency chain from Combine_SimYields down to cascadeMC_gammaSpectra
      // *before* Combine_SimYields runs in order for it to correctly realise that it needs to enable gammas.
      cascadeMC_InitialStates.resolveDependency(&Combine_SimYields);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_InitialStates);
      Combine_SimYields.reset_and_calculate();

      // Identify process as annihilation rather than decay
      DM_process_from_ProcessCatalog.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      DM_process_from_ProcessCatalog.resolveDependency(&DarkMatter_ID_MSSM);
      DM_process_from_ProcessCatalog.reset_and_calculate();

      // Set up initial states for cascade MC
      cascadeMC_InitialStates.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_InitialStates.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DarkMatter_ID_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DarkMatterConj_ID_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DM_process_from_ProcessCatalog);
      cascadeMC_InitialStates.reset_and_calculate();

      // Infer for which type of final states particles MC should be performed
      cascadeMC_FinalStates.setOption<std::vector<std::string>>("cMC_finalStates", daFunk::vec<std::string>("gamma"));
      // Here we need to establish the dependency chain from cascadeMC_FinalStates down to cascadeMC_gammaSpectra
      // *before* cascadeMC_FinalStates runs in order for it to correctly realise that it needs to enable gammas.
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_FinalStates.reset_and_calculate();

      // Collect decay information for cascade MC
      cascadeMC_DecayTable.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
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
      cascadeMC_Histograms.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      cascadeMC_Histograms.resolveDependency(&Combine_SimYields);
      cascadeMC_Histograms.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_Histograms.resolveLoopManager(&cascadeMC_LoopManager);

      // Check convergence of cascade MC
      cascadeMC_EventCount.resolveLoopManager(&cascadeMC_LoopManager);

      // Start cascade MC loop
      cascadeMC_LoopManager.reset_and_calculate();

      // Infer gamma-ray spectra for recorded MC results
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_InitialStates);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_Histograms);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_EventCount);
      cascadeMC_gammaSpectra.reset_and_calculate();

      // Calculate total gamma-ray yield (cascade MC + tabulated results)
      GA_AnnYield_General.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      GA_AnnYield_General.resolveDependency(&GA_SimYieldTable_DarkSUSY);
      GA_AnnYield_General.resolveDependency(&DarkMatter_ID_MSSM);
      GA_AnnYield_General.resolveDependency(&DarkMatterConj_ID_MSSM);
      GA_AnnYield_General.resolveDependency(&cascadeMC_gammaSpectra);
      GA_AnnYield_General.reset_and_calculate();

      // Dump spectrum into file
      dump_gammaSpectrum.resolveDependency(&GA_AnnYield_General);
      dump_gammaSpectrum.setOption<std::string>("filename", current_backend + "_" + outname_dNdE_spectrum);
      dump_gammaSpectrum.reset_and_calculate();

      // Calculate Fermi LAT dwarf likelihood
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&GA_AnnYield_General);
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&RD_fraction_one);
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&DM_process_from_ProcessCatalog);
      lnL_FermiLATdwarfs_gamLike.resolveBackendReq(&Backends::gamLike_1_0_1::Functown::lnL);
      lnL_FermiLATdwarfs_gamLike.reset_and_calculate();
      // Save the result
      results["FermiLAT_dwarfsph_lnL"][current_backend] = lnL_FermiLATdwarfs_gamLike(0);


     // ---- Direct detection and IceCube limits ----

      // Calculate DD couplings with DarkSUSY
      DD_couplings_DarkSUSY_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::DD_couplings);
      DD_couplings_DarkSUSY_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::ddcomlegacy);
      DD_couplings_DarkSUSY_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::ddmssmcom);
      // The below calculates the DD couplings using the full 1 loop calculation of
      // Drees Nojiri Phys.Rev. D48 (1993) 3483
      DD_couplings_DarkSUSY_MSSM.setOption<bool>("loop", true);
      // Setting the below to false approximates the squark propagator as 1/m_sq^2 to avoid poles.
      DD_couplings_DarkSUSY_MSSM.setOption<bool>("pole", false);
      DD_couplings_DarkSUSY_MSSM.reset_and_calculate();

      // Calculate DD couplings for DDCalc
      DDCalc_Couplings_WIMP_nucleon.resolveDependency(&DD_couplings_DarkSUSY_MSSM);
      DDCalc_Couplings_WIMP_nucleon.reset_and_calculate();

      // Initialize DDCalc backend
      Backends::DDCalc_2_2_0::Functown::DDCalc_CalcRates_simple.setStatus(2);
      Backends::DDCalc_2_2_0::Functown::DDCalc_Experiment.setStatus(2);
      Backends::DDCalc_2_2_0::Functown::DDCalc_LogLikelihood.setStatus(2);
      DDCalc_2_2_0_init.resolveDependency(&ExtractLocalMaxwellianHalo);
      DDCalc_2_2_0_init.resolveDependency(&RD_fraction_one);
      DDCalc_2_2_0_init.resolveDependency(&mwimp_generic);
      DDCalc_2_2_0_init.resolveDependency(&DDCalc_Couplings_WIMP_nucleon);
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
      // Save the result
      results["LUX_2016_lnL"][current_backend] = LUX_2016_GetLogLikelihood(0);


      sigma_SI_p_simple.resolveDependency(&mwimp_generic);
      sigma_SI_p_simple.resolveDependency(&DD_couplings_DarkSUSY_MSSM);
      sigma_SI_p_simple.reset_and_calculate();
      // Save the result
      results["sigma_SI_p"][current_backend] = sigma_SI_p_simple(0);

      sigma_SD_p_simple.resolveDependency(&mwimp_generic);
      sigma_SD_p_simple.resolveDependency(&DD_couplings_DarkSUSY_MSSM);
      sigma_SD_p_simple.reset_and_calculate();
      // Save the result
      results["sigma_SD_p"][current_backend] = sigma_SD_p_simple(0);


      // Infer WIMP capture rate in Sun
      capture_rate_Sun_const_xsec.resolveDependency(&mwimp_generic);
      capture_rate_Sun_const_xsec.resolveDependency(&sigma_SI_p_simple);
      capture_rate_Sun_const_xsec.resolveDependency(&sigma_SD_p_simple);
      capture_rate_Sun_const_xsec.resolveDependency(&RD_fraction_one);
      capture_rate_Sun_const_xsec.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dssenu_capsuntab);
      capture_rate_Sun_const_xsec.resolveDependency(&ExtractLocalMaxwellianHalo);
      capture_rate_Sun_const_xsec.resolveDependency(&DarkSUSY_PointInit_LocalHalo_func);
      capture_rate_Sun_const_xsec.reset_and_calculate();

      // Infer WIMP equilibration time in Sun
      equilibration_time_Sun.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      equilibration_time_Sun.resolveDependency(&DarkMatter_ID_MSSM);
      equilibration_time_Sun.resolveDependency(&DarkMatterConj_ID_MSSM);
      equilibration_time_Sun.resolveDependency(&mwimp_generic);
      equilibration_time_Sun.resolveDependency(&capture_rate_Sun_const_xsec);
      equilibration_time_Sun.reset_and_calculate();

      // Infer WIMP annihilation rate in Sun
      annihilation_rate_Sun.resolveDependency(&equilibration_time_Sun);
      annihilation_rate_Sun.resolveDependency(&capture_rate_Sun_const_xsec);
      annihilation_rate_Sun.reset_and_calculate();

      // Infer neutrino yield from Sun
      nuyield_from_DS.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      nuyield_from_DS.resolveDependency(&mwimp_generic);
      nuyield_from_DS.resolveDependency(&sigmav_late_universe);
      nuyield_from_DS.resolveDependency(&DarkMatter_ID_MSSM);
      nuyield_from_DS.resolveDependency(&DarkMatterConj_ID_MSSM);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::dsgenericwimp_nusetup);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::neutrino_yield);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::DS_neutral_h_decay_channels);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_1_1::Functown::DS_charged_h_decay_channels);
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
      // Save the result
      results["IceCube_79_lnL"][current_backend] = IC79_loglike(0);

    }  // End of DarkSUSY_MSSM 6.1.1 calculations




    //
    // ======= Perform all calculations for backend DarkSUSY_MSSM 6.2.2 =======
    //

    current_backend = "DarkSUSY_MSSM6.2.2";

    if (not Backends::backendInfo().works[current_backend])
    {
      backends_not_built.push_back(current_backend);
    }
    else
    {
      // Initialize DarkSUSY 6 MSSM backend
      DarkSUSY_MSSM_6_2_2_init.notifyOfModel("MSSM30atQ");
      DarkSUSY_MSSM_6_2_2_init.resolveDependency(&createSpectrum);
      DarkSUSY_MSSM_6_2_2_init.resolveDependency(&createDecays);
      if (decays) DarkSUSY_MSSM_6_2_2_init.setOption<bool>("use_dsSLHAread", false);
      else DarkSUSY_MSSM_6_2_2_init.setOption<bool>("use_dsSLHAread", true);
      DarkSUSY_MSSM_6_2_2_init.reset_and_calculate();

      // Initialize DarkSUSY 6 Local Halo Model
      DarkSUSY_PointInit_LocalHalo_func.resolveDependency(&ExtractLocalMaxwellianHalo);
      DarkSUSY_PointInit_LocalHalo_func.resolveDependency(&RD_fraction_one);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dshmcom);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dshmisodf);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dshmframevelcom);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dshmnoclue);
      DarkSUSY_PointInit_LocalHalo_func.reset_and_calculate();

      // Relic density calculation with GAMBIT routines and DarkSUSY 6:
      RD_spectrum_MSSM.resolveDependency(&createDecays);
      RD_spectrum_MSSM.resolveDependency(&createSpectrum);
      RD_spectrum_MSSM.resolveDependency(&DarkMatter_ID_MSSM);
      // Below true if charginos and neutralinos are included in coannihilations:
      RD_spectrum_MSSM.setOption<bool>("CoannCharginosNeutralinos", true);
      // Below true if sfermions are included in coannihilations:
      RD_spectrum_MSSM.setOption<bool>("CoannSfermions", true);
      // Maximum sparticle mass to be icluded in coannihilations, in units of DM mass:
      RD_spectrum_MSSM.setOption<double>("CoannMaxMass", 1.6);
      RD_spectrum_MSSM.reset_and_calculate();

      RD_spectrum_ordered_func.resolveDependency(&RD_spectrum_MSSM);
      RD_spectrum_ordered_func.reset_and_calculate();

      RD_annrate_DSprep_MSSM_func.resolveDependency(&RD_spectrum_ordered_func);
      RD_annrate_DSprep_MSSM_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsancoann);
      RD_annrate_DSprep_MSSM_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::DSparticle_code);
      RD_annrate_DSprep_MSSM_func.reset_and_calculate();

      RD_eff_annrate_DS_MSSM.notifyOfModel("MSSM30atQ");
      RD_eff_annrate_DS_MSSM.resolveDependency(&RD_annrate_DSprep_MSSM_func);
      RD_eff_annrate_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsanwx);
      RD_eff_annrate_DS_MSSM.reset_and_calculate();

      RD_oh2_DS_general.resolveDependency(&RD_spectrum_ordered_func);
      RD_oh2_DS_general.resolveDependency(&RD_eff_annrate_DS_MSSM);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::rdpars);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::rdtime);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsrdcom);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsrdstart);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsrdens);
      RD_oh2_DS_general.setOption<int>("fast", 1);  // 0: normal; 1: fast; 2: dirty
      RD_oh2_DS_general.reset_and_calculate();
      // Save the result
      results["oh2"][current_backend] = RD_oh2_DS_general(0);

      lnL_oh2_Simple.resolveDependency(&RD_oh2_DS_general);
      lnL_oh2_Simple.reset_and_calculate();
      // Save the result
      results["oh2_lnL"][current_backend] = lnL_oh2_Simple(0);


      // Set up process catalog based on DarkSUSY annihilation rates
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&createSpectrum);
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&createDecays);
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&DarkMatter_ID_MSSM);
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&DarkMatterConj_ID_MSSM);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dssigmav0);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dssigmav0tot);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsIBffdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsIBhhdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsIBwhdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsIBwwdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::IBintvars);
      TH_ProcessCatalog_DS_MSSM.reset_and_calculate();

      // Set generic WIMP mass object
      WIMP_properties.notifyOfModel("MSSM30atQ");
      WIMP_properties.resolveDependency(&DarkMatter_ID_MSSM);
      WIMP_properties.resolveDependency(&DarkMatterConj_ID_MSSM);
      WIMP_properties.resolveDependency(&createSpectrum);
      WIMP_properties.reset_and_calculate();
      mwimp_generic.resolveDependency(&WIMP_properties);
      mwimp_generic.reset_and_calculate();

      // Set generic annihilation rate in late universe (v->0 limit)
      sigmav_late_universe.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      sigmav_late_universe.resolveDependency(&DarkMatter_ID_MSSM);
      sigmav_late_universe.resolveDependency(&DarkMatterConj_ID_MSSM);
      sigmav_late_universe.reset_and_calculate();
      // Save the result
      results["sigmav0"][current_backend] = sigmav_late_universe(0);


      // ---- Gamma-ray yields ----

      // Initialize tabulated gamma-ray yields
      GA_SimYieldTable_DarkSUSY.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsanyield_sim);
      GA_SimYieldTable_DarkSUSY.reset_and_calculate();
      Combine_SimYields.resolveDependency(&GA_SimYieldTable_DarkSUSY);
      // Here we need to establish the dependency chain from Combine_SimYields down to cascadeMC_gammaSpectra
      // *before* Combine_SimYields runs in order for it to correctly realise that it needs to enable gammas.
      cascadeMC_InitialStates.resolveDependency(&Combine_SimYields);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_InitialStates);
      Combine_SimYields.reset_and_calculate();

      // Identify process as annihilation rather than decay
      DM_process_from_ProcessCatalog.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      DM_process_from_ProcessCatalog.resolveDependency(&DarkMatter_ID_MSSM);
      DM_process_from_ProcessCatalog.reset_and_calculate();

      // Set up initial states for cascade MC
      cascadeMC_InitialStates.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_InitialStates.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DarkMatter_ID_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DarkMatterConj_ID_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DM_process_from_ProcessCatalog);
      cascadeMC_InitialStates.reset_and_calculate();

      // Infer for which type of final states particles MC should be performed
      cascadeMC_FinalStates.setOption<std::vector<std::string>>("cMC_finalStates", daFunk::vec<std::string>("gamma"));
      // Here we need to establish the dependency chain from cascadeMC_FinalStates down to cascadeMC_gammaSpectra
      // *before* cascadeMC_FinalStates runs in order for it to correctly realise that it needs to enable gammas.
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_FinalStates.reset_and_calculate();

      // Collect decay information for cascade MC
      cascadeMC_DecayTable.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
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
      cascadeMC_Histograms.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      cascadeMC_Histograms.resolveDependency(&Combine_SimYields);
      cascadeMC_Histograms.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_Histograms.resolveLoopManager(&cascadeMC_LoopManager);

      // Check convergence of cascade MC
      cascadeMC_EventCount.resolveLoopManager(&cascadeMC_LoopManager);

      // Start cascade MC loop
      cascadeMC_LoopManager.reset_and_calculate();

      // Infer gamma-ray spectra for recorded MC results
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_InitialStates);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_Histograms);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_EventCount);
      cascadeMC_gammaSpectra.reset_and_calculate();

      // Calculate total gamma-ray yield (cascade MC + tabulated results)
      GA_AnnYield_General.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      GA_AnnYield_General.resolveDependency(&GA_SimYieldTable_DarkSUSY);
      GA_AnnYield_General.resolveDependency(&DarkMatter_ID_MSSM);
      GA_AnnYield_General.resolveDependency(&DarkMatterConj_ID_MSSM);
      GA_AnnYield_General.resolveDependency(&cascadeMC_gammaSpectra);
      GA_AnnYield_General.reset_and_calculate();

      // Dump spectrum into file
      dump_gammaSpectrum.resolveDependency(&GA_AnnYield_General);
      dump_gammaSpectrum.setOption<std::string>("filename", current_backend + "_" + outname_dNdE_spectrum);
      dump_gammaSpectrum.reset_and_calculate();

      // Calculate Fermi LAT dwarf likelihood
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&GA_AnnYield_General);
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&RD_fraction_one);
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&DM_process_from_ProcessCatalog);
      lnL_FermiLATdwarfs_gamLike.resolveBackendReq(&Backends::gamLike_1_0_1::Functown::lnL);
      lnL_FermiLATdwarfs_gamLike.reset_and_calculate();
      // Save the result
      results["FermiLAT_dwarfsph_lnL"][current_backend] = lnL_FermiLATdwarfs_gamLike(0);


     // ---- Direct detection and IceCube limits ----

      // Calculate DD couplings with DarkSUSY
      DD_couplings_DarkSUSY_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::DD_couplings);
      DD_couplings_DarkSUSY_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::ddcomlegacy);
      DD_couplings_DarkSUSY_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::ddmssmcom);
      // The below calculates the DD couplings using the full 1 loop calculation of
      // Drees Nojiri Phys.Rev. D48 (1993) 3483
      DD_couplings_DarkSUSY_MSSM.setOption<bool>("loop", true);
      // Setting the below to false approximates the squark propagator as 1/m_sq^2 to avoid poles.
      DD_couplings_DarkSUSY_MSSM.setOption<bool>("pole", false);
      DD_couplings_DarkSUSY_MSSM.reset_and_calculate();

      // Calculate DD couplings for DDCalc
      DDCalc_Couplings_WIMP_nucleon.resolveDependency(&DD_couplings_DarkSUSY_MSSM);
      DDCalc_Couplings_WIMP_nucleon.reset_and_calculate();

      // Initialize DDCalc backend
      Backends::DDCalc_2_2_0::Functown::DDCalc_CalcRates_simple.setStatus(2);
      Backends::DDCalc_2_2_0::Functown::DDCalc_Experiment.setStatus(2);
      Backends::DDCalc_2_2_0::Functown::DDCalc_LogLikelihood.setStatus(2);
      DDCalc_2_2_0_init.resolveDependency(&ExtractLocalMaxwellianHalo);
      DDCalc_2_2_0_init.resolveDependency(&RD_fraction_one);
      DDCalc_2_2_0_init.resolveDependency(&mwimp_generic);
      DDCalc_2_2_0_init.resolveDependency(&DDCalc_Couplings_WIMP_nucleon);
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
      // Save the result
      results["LUX_2016_lnL"][current_backend] = LUX_2016_GetLogLikelihood(0);


      sigma_SI_p_simple.resolveDependency(&mwimp_generic);
      sigma_SI_p_simple.resolveDependency(&DD_couplings_DarkSUSY_MSSM);
      sigma_SI_p_simple.reset_and_calculate();
      // Save the result
      results["sigma_SI_p"][current_backend] = sigma_SI_p_simple(0);

      sigma_SD_p_simple.resolveDependency(&mwimp_generic);
      sigma_SD_p_simple.resolveDependency(&DD_couplings_DarkSUSY_MSSM);
      sigma_SD_p_simple.reset_and_calculate();
      // Save the result
      results["sigma_SD_p"][current_backend] = sigma_SD_p_simple(0);


      // Infer WIMP capture rate in Sun
      capture_rate_Sun_const_xsec.resolveDependency(&mwimp_generic);
      capture_rate_Sun_const_xsec.resolveDependency(&sigma_SI_p_simple);
      capture_rate_Sun_const_xsec.resolveDependency(&sigma_SD_p_simple);
      capture_rate_Sun_const_xsec.resolveDependency(&RD_fraction_one);
      capture_rate_Sun_const_xsec.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dssenu_capsuntab);
      capture_rate_Sun_const_xsec.resolveDependency(&ExtractLocalMaxwellianHalo);
      capture_rate_Sun_const_xsec.resolveDependency(&DarkSUSY_PointInit_LocalHalo_func);
      capture_rate_Sun_const_xsec.reset_and_calculate();

      // Infer WIMP equilibration time in Sun
      equilibration_time_Sun.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      equilibration_time_Sun.resolveDependency(&DarkMatter_ID_MSSM);
      equilibration_time_Sun.resolveDependency(&DarkMatterConj_ID_MSSM);
      equilibration_time_Sun.resolveDependency(&mwimp_generic);
      equilibration_time_Sun.resolveDependency(&capture_rate_Sun_const_xsec);
      equilibration_time_Sun.reset_and_calculate();

      // Infer WIMP annihilation rate in Sun
      annihilation_rate_Sun.resolveDependency(&equilibration_time_Sun);
      annihilation_rate_Sun.resolveDependency(&capture_rate_Sun_const_xsec);
      annihilation_rate_Sun.reset_and_calculate();

      // Infer neutrino yield from Sun
      nuyield_from_DS.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      nuyield_from_DS.resolveDependency(&mwimp_generic);
      nuyield_from_DS.resolveDependency(&sigmav_late_universe);
      nuyield_from_DS.resolveDependency(&DarkMatter_ID_MSSM);
      nuyield_from_DS.resolveDependency(&DarkMatterConj_ID_MSSM);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::dsgenericwimp_nusetup);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::neutrino_yield);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::DS_neutral_h_decay_channels);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_2::Functown::DS_charged_h_decay_channels);
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
      // Save the result
      results["IceCube_79_lnL"][current_backend] = IC79_loglike(0);

    }  // End of DarkSUSY_MSSM 6.2.2 calculations


    //
    // ======= Perform all calculations for backend DarkSUSY_MSSM 6.2.5 =======
    //

    current_backend = "DarkSUSY_MSSM6.2.5";

    if (not Backends::backendInfo().works[current_backend])
    {
      backends_not_built.push_back(current_backend);
    }
    else
    {
      // Initialize DarkSUSY 6 MSSM backend
      DarkSUSY_MSSM_6_2_5_init.notifyOfModel("MSSM30atQ");
      DarkSUSY_MSSM_6_2_5_init.resolveDependency(&createSpectrum);
      DarkSUSY_MSSM_6_2_5_init.resolveDependency(&createDecays);
      if (decays) DarkSUSY_MSSM_6_2_5_init.setOption<bool>("use_dsSLHAread", false);
      else DarkSUSY_MSSM_6_2_5_init.setOption<bool>("use_dsSLHAread", true);
      DarkSUSY_MSSM_6_2_5_init.reset_and_calculate();

      // Initialize DarkSUSY 6 Local Halo Model
      DarkSUSY_PointInit_LocalHalo_func.resolveDependency(&ExtractLocalMaxwellianHalo);
      DarkSUSY_PointInit_LocalHalo_func.resolveDependency(&RD_fraction_one);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dshmcom);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dshmisodf);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dshmframevelcom);
      DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dshmnoclue);
      DarkSUSY_PointInit_LocalHalo_func.reset_and_calculate();

      // Relic density calculation with GAMBIT routines and DarkSUSY 6:
      RD_spectrum_MSSM.resolveDependency(&createDecays);
      RD_spectrum_MSSM.resolveDependency(&createSpectrum);
      RD_spectrum_MSSM.resolveDependency(&DarkMatter_ID_MSSM);
      // Below true if charginos and neutralinos are included in coannihilations:
      RD_spectrum_MSSM.setOption<bool>("CoannCharginosNeutralinos", true);
      // Below true if sfermions are included in coannihilations:
      RD_spectrum_MSSM.setOption<bool>("CoannSfermions", true);
      // Maximum sparticle mass to be icluded in coannihilations, in units of DM mass:
      RD_spectrum_MSSM.setOption<double>("CoannMaxMass", 1.6);
      RD_spectrum_MSSM.reset_and_calculate();

      RD_spectrum_ordered_func.resolveDependency(&RD_spectrum_MSSM);
      RD_spectrum_ordered_func.reset_and_calculate();

      RD_annrate_DSprep_MSSM_func.resolveDependency(&RD_spectrum_ordered_func);
      RD_annrate_DSprep_MSSM_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsancoann);
      RD_annrate_DSprep_MSSM_func.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::DSparticle_code);
      RD_annrate_DSprep_MSSM_func.reset_and_calculate();

      RD_eff_annrate_DS_MSSM.notifyOfModel("MSSM30atQ");
      RD_eff_annrate_DS_MSSM.resolveDependency(&RD_annrate_DSprep_MSSM_func);
      RD_eff_annrate_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsanwx);
      RD_eff_annrate_DS_MSSM.reset_and_calculate();

      RD_oh2_DS_general.resolveDependency(&RD_spectrum_ordered_func);
      RD_oh2_DS_general.resolveDependency(&RD_eff_annrate_DS_MSSM);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::rdpars);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::rdtime);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsrdcom);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsrdstart);
      RD_oh2_DS_general.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsrdens);
      RD_oh2_DS_general.setOption<int>("fast", 1);  // 0: normal; 1: fast; 2: dirty
      RD_oh2_DS_general.reset_and_calculate();
      // Save the result
      results["oh2"][current_backend] = RD_oh2_DS_general(0);

      lnL_oh2_Simple.resolveDependency(&RD_oh2_DS_general);
      lnL_oh2_Simple.reset_and_calculate();
      // Save the result
      results["oh2_lnL"][current_backend] = lnL_oh2_Simple(0);


      // Set up process catalog based on DarkSUSY annihilation rates
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&createSpectrum);
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&createDecays);
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&DarkMatter_ID_MSSM);
      TH_ProcessCatalog_DS_MSSM.resolveDependency(&DarkMatterConj_ID_MSSM);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dssigmav0);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dssigmav0tot);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsIBffdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsIBhhdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsIBwhdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsIBwwdxdy);
      TH_ProcessCatalog_DS_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::IBintvars);
      TH_ProcessCatalog_DS_MSSM.reset_and_calculate();

      // Set generic WIMP mass object
      WIMP_properties.notifyOfModel("MSSM30atQ");
      WIMP_properties.resolveDependency(&DarkMatter_ID_MSSM);
      WIMP_properties.resolveDependency(&DarkMatterConj_ID_MSSM);
      WIMP_properties.resolveDependency(&createSpectrum);
      WIMP_properties.reset_and_calculate();
      mwimp_generic.resolveDependency(&WIMP_properties);
      mwimp_generic.reset_and_calculate();

      // Set generic annihilation rate in late universe (v->0 limit)
      sigmav_late_universe.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      sigmav_late_universe.resolveDependency(&DarkMatter_ID_MSSM);
      sigmav_late_universe.resolveDependency(&DarkMatterConj_ID_MSSM);
      sigmav_late_universe.reset_and_calculate();
      // Save the result
      results["sigmav0"][current_backend] = sigmav_late_universe(0);


      // ---- Gamma-ray yields ----

      // Initialize tabulated gamma-ray yields
      GA_SimYieldTable_DarkSUSY.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsanyield_sim);
      GA_SimYieldTable_DarkSUSY.reset_and_calculate();
      Combine_SimYields.resolveDependency(&GA_SimYieldTable_DarkSUSY);
      // Here we need to establish the dependency chain from Combine_SimYields down to cascadeMC_gammaSpectra
      // *before* Combine_SimYields runs in order for it to correctly realise that it needs to enable gammas.
      cascadeMC_InitialStates.resolveDependency(&Combine_SimYields);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_InitialStates);
      Combine_SimYields.reset_and_calculate();

      // Identify process as annihilation rather than decay
      DM_process_from_ProcessCatalog.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      DM_process_from_ProcessCatalog.resolveDependency(&DarkMatter_ID_MSSM);
      DM_process_from_ProcessCatalog.reset_and_calculate();

      // Set up initial states for cascade MC
      cascadeMC_InitialStates.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_InitialStates.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DarkMatter_ID_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DarkMatterConj_ID_MSSM);
      cascadeMC_InitialStates.resolveDependency(&DM_process_from_ProcessCatalog);
      cascadeMC_InitialStates.reset_and_calculate();

      // Infer for which type of final states particles MC should be performed
      cascadeMC_FinalStates.setOption<std::vector<std::string>>("cMC_finalStates", daFunk::vec<std::string>("gamma"));
      // Here we need to establish the dependency chain from cascadeMC_FinalStates down to cascadeMC_gammaSpectra
      // *before* cascadeMC_FinalStates runs in order for it to correctly realise that it needs to enable gammas.
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_FinalStates.reset_and_calculate();

      // Collect decay information for cascade MC
      cascadeMC_DecayTable.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
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
      cascadeMC_Histograms.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      cascadeMC_Histograms.resolveDependency(&Combine_SimYields);
      cascadeMC_Histograms.resolveDependency(&cascadeMC_FinalStates);
      cascadeMC_Histograms.resolveLoopManager(&cascadeMC_LoopManager);

      // Check convergence of cascade MC
      cascadeMC_EventCount.resolveLoopManager(&cascadeMC_LoopManager);

      // Start cascade MC loop
      cascadeMC_LoopManager.reset_and_calculate();

      // Infer gamma-ray spectra for recorded MC results
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_InitialStates);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_Histograms);
      cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_EventCount);
      cascadeMC_gammaSpectra.reset_and_calculate();

      // Calculate total gamma-ray yield (cascade MC + tabulated results)
      GA_AnnYield_General.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      GA_AnnYield_General.resolveDependency(&GA_SimYieldTable_DarkSUSY);
      GA_AnnYield_General.resolveDependency(&DarkMatter_ID_MSSM);
      GA_AnnYield_General.resolveDependency(&DarkMatterConj_ID_MSSM);
      GA_AnnYield_General.resolveDependency(&cascadeMC_gammaSpectra);
      GA_AnnYield_General.reset_and_calculate();

      // Dump spectrum into file
      dump_gammaSpectrum.resolveDependency(&GA_AnnYield_General);
      dump_gammaSpectrum.setOption<std::string>("filename", current_backend + "_" + outname_dNdE_spectrum);
      dump_gammaSpectrum.reset_and_calculate();

      // Calculate Fermi LAT dwarf likelihood
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&GA_AnnYield_General);
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&RD_fraction_one);
      lnL_FermiLATdwarfs_gamLike.resolveDependency(&DM_process_from_ProcessCatalog);
      lnL_FermiLATdwarfs_gamLike.resolveBackendReq(&Backends::gamLike_1_0_1::Functown::lnL);
      lnL_FermiLATdwarfs_gamLike.reset_and_calculate();
      // Save the result
      results["FermiLAT_dwarfsph_lnL"][current_backend] = lnL_FermiLATdwarfs_gamLike(0);


     // ---- Direct detection and IceCube limits ----

      // Calculate DD couplings with DarkSUSY
      DD_couplings_DarkSUSY_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::DD_couplings);
      DD_couplings_DarkSUSY_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::ddcomlegacy);
      DD_couplings_DarkSUSY_MSSM.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::ddmssmcom);
      // The below calculates the DD couplings using the full 1 loop calculation of
      // Drees Nojiri Phys.Rev. D48 (1993) 3483
      DD_couplings_DarkSUSY_MSSM.setOption<bool>("loop", true);
      // Setting the below to false approximates the squark propagator as 1/m_sq^2 to avoid poles.
      DD_couplings_DarkSUSY_MSSM.setOption<bool>("pole", false);
      DD_couplings_DarkSUSY_MSSM.reset_and_calculate();

      // Calculate DD couplings for DDCalc
      DDCalc_Couplings_WIMP_nucleon.resolveDependency(&DD_couplings_DarkSUSY_MSSM);
      DDCalc_Couplings_WIMP_nucleon.reset_and_calculate();

      // Initialize DDCalc backend
      Backends::DDCalc_2_2_0::Functown::DDCalc_CalcRates_simple.setStatus(2);
      Backends::DDCalc_2_2_0::Functown::DDCalc_Experiment.setStatus(2);
      Backends::DDCalc_2_2_0::Functown::DDCalc_LogLikelihood.setStatus(2);
      DDCalc_2_2_0_init.resolveDependency(&ExtractLocalMaxwellianHalo);
      DDCalc_2_2_0_init.resolveDependency(&RD_fraction_one);
      DDCalc_2_2_0_init.resolveDependency(&mwimp_generic);
      DDCalc_2_2_0_init.resolveDependency(&DDCalc_Couplings_WIMP_nucleon);
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
      // Save the result
      results["LUX_2016_lnL"][current_backend] = LUX_2016_GetLogLikelihood(0);


      sigma_SI_p_simple.resolveDependency(&mwimp_generic);
      sigma_SI_p_simple.resolveDependency(&DD_couplings_DarkSUSY_MSSM);
      sigma_SI_p_simple.reset_and_calculate();
      // Save the result
      results["sigma_SI_p"][current_backend] = sigma_SI_p_simple(0);

      sigma_SD_p_simple.resolveDependency(&mwimp_generic);
      sigma_SD_p_simple.resolveDependency(&DD_couplings_DarkSUSY_MSSM);
      sigma_SD_p_simple.reset_and_calculate();
      // Save the result
      results["sigma_SD_p"][current_backend] = sigma_SD_p_simple(0);


      // Infer WIMP capture rate in Sun
      capture_rate_Sun_const_xsec.resolveDependency(&mwimp_generic);
      capture_rate_Sun_const_xsec.resolveDependency(&sigma_SI_p_simple);
      capture_rate_Sun_const_xsec.resolveDependency(&sigma_SD_p_simple);
      capture_rate_Sun_const_xsec.resolveDependency(&RD_fraction_one);
      capture_rate_Sun_const_xsec.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dssenu_capsuntab);
      capture_rate_Sun_const_xsec.resolveDependency(&ExtractLocalMaxwellianHalo);
      capture_rate_Sun_const_xsec.resolveDependency(&DarkSUSY_PointInit_LocalHalo_func);
      capture_rate_Sun_const_xsec.reset_and_calculate();

      // Infer WIMP equilibration time in Sun
      equilibration_time_Sun.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      equilibration_time_Sun.resolveDependency(&DarkMatter_ID_MSSM);
      equilibration_time_Sun.resolveDependency(&DarkMatterConj_ID_MSSM);
      equilibration_time_Sun.resolveDependency(&mwimp_generic);
      equilibration_time_Sun.resolveDependency(&capture_rate_Sun_const_xsec);
      equilibration_time_Sun.reset_and_calculate();

      // Infer WIMP annihilation rate in Sun
      annihilation_rate_Sun.resolveDependency(&equilibration_time_Sun);
      annihilation_rate_Sun.resolveDependency(&capture_rate_Sun_const_xsec);
      annihilation_rate_Sun.reset_and_calculate();

      // Infer neutrino yield from Sun
      nuyield_from_DS.resolveDependency(&TH_ProcessCatalog_DS_MSSM);
      nuyield_from_DS.resolveDependency(&mwimp_generic);
      nuyield_from_DS.resolveDependency(&sigmav_late_universe);
      nuyield_from_DS.resolveDependency(&DarkMatter_ID_MSSM);
      nuyield_from_DS.resolveDependency(&DarkMatterConj_ID_MSSM);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::dsgenericwimp_nusetup);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::neutrino_yield);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::DS_neutral_h_decay_channels);
      nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_MSSM_6_2_5::Functown::DS_charged_h_decay_channels);
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
      // Save the result
      results["IceCube_79_lnL"][current_backend] = IC79_loglike(0);

    }  // End of DarkSUSY_MSSM 6.2.5 calculations




    //
    // ======= Perform all calculations for backend MicrOmegas_MSSM 3.6.9.2 =======
    //

    current_backend = "MicrOmegas_MSSM3.6.9.2";

    if (not Backends::backendInfo().works[current_backend])
    {
      backends_not_built.push_back(current_backend);
    }
    else
    {
      // Initialize MicrOmegas backend
      MicrOmegas_MSSM_3_6_9_2_init.notifyOfModel("MSSM30atQ");
      MicrOmegas_MSSM_3_6_9_2_init.resolveDependency(&createSpectrum);
      MicrOmegas_MSSM_3_6_9_2_init.resolveDependency(&createDecays);
      MicrOmegas_MSSM_3_6_9_2_init.resolveDependency(&createSLHA1Names);
      // Use decay table if it is present:
      if (decays) MicrOmegas_MSSM_3_6_9_2_init.setOption<bool>("internal_decays", false);
      else MicrOmegas_MSSM_3_6_9_2_init.setOption<bool>("internal_decays", true);
      MicrOmegas_MSSM_3_6_9_2_init.reset_and_calculate();
      // For the below VXdecay = 0 - no 3 body final states via virtual X
      //                         1 - annihilations to 3 body final states via virtual X
      //                         2 - (co)annihilations to 3 body final states via virtual X
      MicrOmegas_MSSM_3_6_9_2_init.setOption<int>("VZdecay", 0);
      MicrOmegas_MSSM_3_6_9_2_init.setOption<int>("VWdecay", 0);
      MicrOmegas_MSSM_3_6_9_2_init.reset_and_calculate();

      // Relic density calculation with MicrOmegas
      RD_oh2_Xf_MicrOmegas.notifyOfModel("MSSM30atQ");
      RD_oh2_Xf_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_MSSM_3_6_9_2::Functown::darkOmega);
      RD_oh2_Xf_MicrOmegas.setOption<int>("fast", 1);  // 0: accurate; 1: fast
      RD_oh2_Xf_MicrOmegas.setOption<double>("Beps", 1e-5); // Beps=1e-5 recommended, Beps=1 switches coannihilation off
      RD_oh2_Xf_MicrOmegas.reset_and_calculate();
      RD_oh2_MicrOmegas.resolveDependency(&RD_oh2_Xf_MicrOmegas);
      RD_oh2_MicrOmegas.reset_and_calculate();
      // Save the result
      results["oh2"][current_backend] = RD_oh2_MicrOmegas(0);

      lnL_oh2_Simple.resolveDependency(&RD_oh2_MicrOmegas);
      lnL_oh2_Simple.reset_and_calculate();
      // Save the result
      results["oh2_lnL"][current_backend] = lnL_oh2_Simple(0);

      // <sigma v> (v->0 limit) self-annihilation calculation with MicrOmegas:
      sigmav_late_universe_MicrOmegas.notifyOfModel("MSSM30atQ");
      sigmav_late_universe_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_MSSM_3_6_9_2::Functown::calcSpectrum);
      sigmav_late_universe_MicrOmegas.reset_and_calculate();
      results["sigmav0"][current_backend] = sigmav_late_universe_MicrOmegas(0);

      // Direct detection calculations with Micromegas

      // Calculate DD couplings with Micromegas
      // DD_couplings_MicrOmegas.notifyOfModel("MSSM30atQ");
      // DD_couplings_MicrOmegas.notifyOfModel("nuclear_params_fnq");
      // DD_couplings_MicrOmegas.resolveDependency(&Models::nuclear_params_fnq::Functown::primary_parameters);
      DD_couplings_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_MSSM_3_6_9_2::Functown::nucleonAmplitudes);
      DD_couplings_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_MSSM_3_6_9_2::Functown::FeScLoop);
      DD_couplings_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_MSSM_3_6_9_2::Functown::mocommon_);
      // The below includes neutralino-gluon scattering via a box diagram
      DD_couplings_MicrOmegas.setOption<bool>("box", true);
      DD_couplings_MicrOmegas.reset_and_calculate();

      // Calculate DD couplings for DDCalc
      DDCalc_Couplings_WIMP_nucleon.resolveDependency(&DD_couplings_MicrOmegas);
      DDCalc_Couplings_WIMP_nucleon.reset_and_calculate();

      // Set generic WIMP mass object
      WIMP_properties.notifyOfModel("MSSM30atQ");
      WIMP_properties.resolveDependency(&DarkMatter_ID_MSSM);
      WIMP_properties.resolveDependency(&DarkMatterConj_ID_MSSM);
      WIMP_properties.resolveDependency(&createSpectrum);
      WIMP_properties.reset_and_calculate();
      mwimp_generic.resolveDependency(&WIMP_properties);
      mwimp_generic.reset_and_calculate();

      // Initialize DDCalc backend
      Backends::DDCalc_2_2_0::Functown::DDCalc_CalcRates_simple.setStatus(2);
      Backends::DDCalc_2_2_0::Functown::DDCalc_Experiment.setStatus(2);
      Backends::DDCalc_2_2_0::Functown::DDCalc_LogLikelihood.setStatus(2);
      DDCalc_2_2_0_init.resolveDependency(&ExtractLocalMaxwellianHalo);
      DDCalc_2_2_0_init.resolveDependency(&RD_fraction_one);
      DDCalc_2_2_0_init.resolveDependency(&mwimp_generic);
      DDCalc_2_2_0_init.resolveDependency(&DDCalc_Couplings_WIMP_nucleon);
      DDCalc_2_2_0_init.reset_and_calculate();


      sigma_SI_p_simple.resolveDependency(&mwimp_generic);
      sigma_SI_p_simple.resolveDependency(&DD_couplings_MicrOmegas);
      sigma_SI_p_simple.reset_and_calculate();
      // Save the result
      results["sigma_SI_p"][current_backend] = sigma_SI_p_simple(0);

      sigma_SD_p_simple.resolveDependency(&mwimp_generic);
      sigma_SD_p_simple.resolveDependency(&DD_couplings_MicrOmegas);
      sigma_SD_p_simple.reset_and_calculate();
      // Save the result
      results["sigma_SD_p"][current_backend] = sigma_SD_p_simple(0);

    } // End of MicrOmegas_MSSM 3.6.9.2 calculations



    //
    // ======= Construct the output string =======
    //

    std::stringstream results_ss;

    for(const std::string& result_key : result_output_order)
    {
      const std::map<std::string,double>& backends_result_map = results.at(result_key);
      results_ss << result_key;
      if (results_units.at(result_key) != "") { results_ss << " [" << results_units.at(result_key) << "]"; }
      results_ss << " :" << endl;

      for(const auto& kv : backends_result_map)
      {
        const std::string& backendname = kv.first;
        const double& result = kv.second;
        results_ss << "  " << backendname << ": " << result << " " << results_units.at(result_key) << endl;
      }
      results_ss << endl;
    }


    //
    // ======= Output the result string to screen =======
    //

    cout << endl;
    cout << "==== RESULTS ====" << endl;
    cout << endl;
    cout << results_ss.str();
    cout << endl;

    // Let the user know what they are missing...
    if (backends_not_built.size() > 0)
    {
      cout << endl;
      cout << "NOTE: The following backend(s) are not present:" << endl;
      for (const std::string& backend_name : backends_not_built)
      {
        cout << "  - " << backend_name << endl;
      }
      cout << "If you want results from these backends you need to build them first." << endl;
      cout << endl;
    }


    //
    // ======= Output the result string to file =======
    //

    std::fstream file;
    file.open(outname_data, std::ios_base::out);
    file << results_ss.str();
    file.close();

  }

  catch (std::exception& e)
  {
    std::cout << "DarkBit_standalone_MSSM has exited with fatal exception: " << e.what() << std::endl;
  }

  return 0;

}
