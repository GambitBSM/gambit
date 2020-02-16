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
///  *********************************************

#include "gambit/Elements/standalone_module.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/Elements/spectrum_factories.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Models/SimpleSpectra/MSSMSimpleSpec.hpp"
#include "gambit/Utils/util_functions.hpp"

using namespace DarkBit::Functown;     // Functors wrapping the module's actual module functions
using namespace DarkBit::Accessors;    // Helper functions that provide some info about the module
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
  std::cout << "Usage: DarkBit_standalone_MSSM SLHA_file (spectrum) (data) (dump)" << std::endl;
  std::cout << std::endl;
  std::cout << "SLHA_file: SLHA file used to intialise the program (required)" << std::endl;
  std::cout << "spectrum: name of output file for gamma-ray spectrum (default: dNdE.dat)" << std::endl;
  std::cout << "data: name of output file for observables and likelihoods (default: data.dat)" << std::endl;
  std::cout << "dump: name of unit test output file (default: dump.yaml)" << std::endl;
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
    std::string outname = "dNdE.dat";
    if (argc >= 3) outname = argv[2];
    std::string filename_data = "data.dat";
    if (argc >= 4) filename_data = argv[3];
    std::string filename_dump = "dump.yaml";
    if (argc >= 5) filename_dump = argv[4];


    // ---- Initialise logging and exceptions ----

    initialise_standalone_logs("runs/DarkBit_standalone_MSSM/logs/");
    logger()<<"Running DarkBit standalone example"<<LogTags::info<<EOM;
    model_warning().set_fatal(true);

    // ---- Check that required backends are present ----

    if (not Backends::backendInfo().works["DarkSUSY5.1.3"]) backend_error().raise(LOCAL_INFO, "DarkSUSY 5.1.3 is missing!");
    if (not Backends::backendInfo().works["MicrOmegas_MSSM3.6.9.2"]) backend_error().raise(LOCAL_INFO, "MicrOmegas 3.6.9.2 for MSSM is missing!");
    if (not Backends::backendInfo().works["gamLike1.0.1"]) backend_error().raise(LOCAL_INFO, "gamLike 1.0.1 is missing!");
    if (not Backends::backendInfo().works["DDCalc2.0.0"]) backend_error().raise(LOCAL_INFO, "DDCalc 2.0.0 is missing!");
    if (not Backends::backendInfo().works["nulike1.0.8"]) backend_error().raise(LOCAL_INFO, "nulike 1.0.8 is missing!");


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

    // ---- Initialize backends ----

    // Initialize nulike backend
    Backends::nulike_1_0_8::Functown::nulike_bounds.setStatus(2);
    nulike_1_0_8_init.reset_and_calculate();

    // Initialize gamLike backend
    gamLike_1_0_1_init.reset_and_calculate();

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

    // Initialize DarkSUSY backend
    DarkSUSY_5_1_3_init.reset_and_calculate();
    DarkSUSY_PointInit_MSSM.notifyOfModel("MSSM30atQ");
    DarkSUSY_PointInit_MSSM.resolveDependency(&createSpectrum);
    DarkSUSY_PointInit_MSSM.resolveDependency(&createDecays);
    DarkSUSY_PointInit_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::init_diskless);
    DarkSUSY_PointInit_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsgive_model_isasugra);
    DarkSUSY_PointInit_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dssusy_isasugra);
    DarkSUSY_PointInit_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsSLHAread);
    DarkSUSY_PointInit_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsprep);
    if (decays) DarkSUSY_PointInit_MSSM.setOption<bool>("use_dsSLHAread", false);
    else DarkSUSY_PointInit_MSSM.setOption<bool>("use_dsSLHAread", true);
    DarkSUSY_PointInit_MSSM.reset_and_calculate();

    // Assume for direct and indirect detection likelihoods that dark matter
    // density is always the measured one (regardless of relic density results)
    RD_fraction_one.reset_and_calculate();

    // Initialize DarkSUSY Local Halo Model
    DarkSUSY_PointInit_LocalHalo_func.resolveDependency(&ExtractLocalMaxwellianHalo);
    DarkSUSY_PointInit_LocalHalo_func.resolveDependency(&RD_fraction_one);
    DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dshmcom);
    DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dshmisodf);
    DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dshmframevelcom);
    DarkSUSY_PointInit_LocalHalo_func.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dshmnoclue);
    DarkSUSY_PointInit_LocalHalo_func.reset_and_calculate();


    // ---- Relic density ----

    // Relic density calculation with MicrOmegas
    RD_oh2_Xf_MicrOmegas.notifyOfModel("MSSM30atQ");
    RD_oh2_Xf_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_MSSM_3_6_9_2::Functown::darkOmega);
    RD_oh2_Xf_MicrOmegas.setOption<int>("fast", 1);  // 0: accurate; 1: fast
    RD_oh2_Xf_MicrOmegas.setOption<double>("Beps", 1e-5); // Beps=1e-5 recommended, Beps=1 switches coannihilation off
    RD_oh2_Xf_MicrOmegas.reset_and_calculate();
    RD_oh2_MicrOmegas.resolveDependency(&RD_oh2_Xf_MicrOmegas);
    RD_oh2_MicrOmegas.reset_and_calculate();

    // Calculate relic density using RD_oh2_DarkSUSY (for checks only)
    //RD_oh2_DarkSUSY.resolveDependency(&DarkSUSY_PointInit_MSSM);
    //RD_oh2_DarkSUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsrdomega);
    //RD_oh2_DarkSUSY.setOption<int>("fast", 1);  // 0: normal; 1: fast; 2: dirty
    //RD_oh2_DarkSUSY.reset_and_calculate();

    // Relic density calculation with GAMBIT routines:
    RD_spectrum_SUSY.resolveDependency(&DarkSUSY_PointInit_MSSM);
    RD_spectrum_SUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::mspctm);
    RD_spectrum_SUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::widths);
    RD_spectrum_SUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::intdof);
    RD_spectrum_SUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::pacodes);
    RD_spectrum_SUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::DSparticle_code);
    // Below true if charginos and neutralinos are included in coannihilations:
    RD_spectrum_SUSY.setOption<bool>("CoannCharginosNeutralinos", true);
    // Below true if sfermions are included in coannihilations:
    RD_spectrum_SUSY.setOption<bool>("CoannSfermions", true);
    // Maximum sparticle mass to be icluded in coannihilations, in units of DM mass:
    RD_spectrum_SUSY.setOption<double>("CoannMaxMass", 1.6);
    RD_spectrum_SUSY.reset_and_calculate();

    RD_spectrum_ordered_func.resolveDependency(&RD_spectrum_SUSY);
    RD_spectrum_ordered_func.reset_and_calculate();

    RD_annrate_DSprep_func.resolveDependency(&RD_spectrum_SUSY);
    RD_annrate_DSprep_func.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdmgev);
    RD_annrate_DSprep_func.reset_and_calculate();

    RD_eff_annrate_SUSY.resolveDependency(&RD_annrate_DSprep_func);
    RD_eff_annrate_SUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsanwx);
    RD_eff_annrate_SUSY.reset_and_calculate();

    RD_oh2_general.resolveDependency(&RD_spectrum_ordered_func);
    RD_oh2_general.resolveDependency(&RD_eff_annrate_SUSY);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsrdthlim);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsrdtab);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsrdeqn);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsrdwintp);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::DSparticle_code);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::widths);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdmgev);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdpth);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdpars);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdswitch);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdlun);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdpadd);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rddof);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rderrors);
    RD_oh2_general.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::rdtime);
    RD_oh2_general.setOption<int>("fast", 1);  // 0: normal; 1: fast; 2: dirty
    RD_oh2_general.reset_and_calculate();

    // Calculate WMAP likelihoods -- Choose one of the two relic density calculators
    // by uncommenting the appropriate line.
    //lnL_oh2_Simple.resolveDependency(&RD_oh2_MicrOmegas);
    lnL_oh2_Simple.resolveDependency(&RD_oh2_general);
    lnL_oh2_Simple.reset_and_calculate();


    // ---- Set up basic internal structures for direct & indirect detection ----

    // Set identifier for DM particle
    DarkMatter_ID_MSSM.resolveDependency(&createSpectrum);
    DarkMatter_ID_MSSM.reset_and_calculate();

    // Set up process catalog based on DarkSUSY annihilation rates
    TH_ProcessCatalog_MSSM.resolveDependency(&DarkSUSY_PointInit_MSSM);
    TH_ProcessCatalog_MSSM.resolveDependency(&createSpectrum);
    TH_ProcessCatalog_MSSM.resolveDependency(&createDecays);
    TH_ProcessCatalog_MSSM.resolveDependency(&DarkMatter_ID_MSSM);
    TH_ProcessCatalog_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dssigmav);
    TH_ProcessCatalog_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsIBffdxdy);
    TH_ProcessCatalog_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsIBhhdxdy);
    TH_ProcessCatalog_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsIBwhdxdy);
    TH_ProcessCatalog_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsIBwwdxdy);
    TH_ProcessCatalog_MSSM.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::IBintvars);
    TH_ProcessCatalog_MSSM.reset_and_calculate();

    // Set generic WIMP mass object
    mwimp_generic.resolveDependency(&TH_ProcessCatalog_MSSM);
    mwimp_generic.resolveDependency(&DarkMatter_ID_MSSM);
    mwimp_generic.reset_and_calculate();

    // Set generic annihilation rate in late universe (v->0 limit)
    sigmav_late_universe.resolveDependency(&TH_ProcessCatalog_MSSM);
    sigmav_late_universe.resolveDependency(&DarkMatter_ID_MSSM);
    sigmav_late_universe.reset_and_calculate();


    // ---- Direct detection -----

    // Calculate DD couplings with Micromegas
    DD_couplings_MicrOmegas.notifyOfModel("MSSM30atQ");
    DD_couplings_MicrOmegas.notifyOfModel("nuclear_params_fnq");
    DD_couplings_MicrOmegas.resolveDependency(&Models::nuclear_params_fnq::Functown::primary_parameters);
    DD_couplings_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_MSSM_3_6_9_2::Functown::nucleonAmplitudes);
    DD_couplings_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_MSSM_3_6_9_2::Functown::FeScLoop);
    DD_couplings_MicrOmegas.resolveBackendReq(&Backends::MicrOmegas_MSSM_3_6_9_2::Functown::mocommon_);
    // The below includes neutralino-gluon scattering via a box diagram
    DD_couplings_MicrOmegas.setOption<bool>("box", true);
    DD_couplings_MicrOmegas.reset_and_calculate();

    // Calculate DD couplings with DarkSUSY
    DD_couplings_DarkSUSY.notifyOfModel("nuclear_params_fnq");
    DD_couplings_DarkSUSY.resolveDependency(&Models::nuclear_params_fnq::Functown::primary_parameters);
    DD_couplings_DarkSUSY.resolveDependency(&DarkSUSY_PointInit_MSSM);
    DD_couplings_DarkSUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsddgpgn);
    DD_couplings_DarkSUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::mspctm);
    DD_couplings_DarkSUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::ddcom);
    // The below calculates the DD couplings using the full 1 loop calculation of
    // Drees Nojiri Phys.Rev. D48 (1993) 3483
    DD_couplings_DarkSUSY.setOption<bool>("loop", true);
    // When the calculation is done at tree level (loop = false), setting the below to false
    // approximates the squark propagator as 1/m_sq^2 to avoid poles.
    // DD_couplings_DarkSUSY.setOption<bool>("pole", false);
    DD_couplings_DarkSUSY.reset_and_calculate();

    // Initialize DDCalc backend
    Backends::DDCalc_2_0_0::Functown::DDCalc_CalcRates_simple.setStatus(2);
    Backends::DDCalc_2_0_0::Functown::DDCalc_Experiment.setStatus(2);
    Backends::DDCalc_2_0_0::Functown::DDCalc_LogLikelihood.setStatus(2);
    DDCalc_2_0_0_init.resolveDependency(&ExtractLocalMaxwellianHalo);
    DDCalc_2_0_0_init.resolveDependency(&RD_fraction_one);
    DDCalc_2_0_0_init.resolveDependency(&mwimp_generic);
    //Choose between the two backends
    //DDCalc_2_0_0_init.resolveDependency(&DD_couplings_MicrOmegas);
    DDCalc_2_0_0_init.resolveDependency(&DD_couplings_DarkSUSY);
    DDCalc_2_0_0_init.reset_and_calculate();

    // Calculate direct detection rates for LUX 2016
    LUX_2016_Calc.resolveBackendReq(&Backends::DDCalc_2_0_0::Functown::DDCalc_Experiment);
    LUX_2016_Calc.resolveBackendReq(&Backends::DDCalc_2_0_0::Functown::DDCalc_CalcRates_simple);
    LUX_2016_Calc.reset_and_calculate();

    // Calculate direct detection likelihood for LUX 2016
    LUX_2016_GetLogLikelihood.resolveDependency(&LUX_2016_Calc);
    LUX_2016_GetLogLikelihood.resolveBackendReq(&Backends::DDCalc_2_0_0::Functown::DDCalc_Experiment);
    LUX_2016_GetLogLikelihood.resolveBackendReq(&Backends::DDCalc_2_0_0::Functown::DDCalc_LogLikelihood);
    LUX_2016_GetLogLikelihood.reset_and_calculate();

    // Set generic scattering cross-section for later use
    double sigma_SI_p_DS, sigma_SI_p_MO;

    sigma_SI_p_simple.resolveDependency(&mwimp_generic);
    sigma_SI_p_simple.resolveDependency(&DD_couplings_MicrOmegas);
    sigma_SI_p_simple.reset_and_calculate();
    sigma_SI_p_MO = sigma_SI_p_simple(0);

    sigma_SI_p_simple.resolveDependency(&DD_couplings_DarkSUSY);
    sigma_SI_p_simple.reset_and_calculate();
    sigma_SI_p_DS = sigma_SI_p_simple(0);

    // Set generic scattering cross-section for later use
    double sigma_SD_p_DS, sigma_SD_p_MO;

    sigma_SD_p_simple.resolveDependency(&mwimp_generic);
    sigma_SD_p_simple.resolveDependency(&DD_couplings_MicrOmegas);
    sigma_SD_p_simple.reset_and_calculate();
    sigma_SD_p_MO = sigma_SD_p_simple(0);

    sigma_SD_p_simple.resolveDependency(&DD_couplings_DarkSUSY);
    sigma_SD_p_simple.reset_and_calculate();
    sigma_SD_p_DS = sigma_SD_p_simple(0);


    // ---- Gamma-ray yields ----

    // Initialize tabulated gamma-ray yields
    SimYieldTable_DarkSUSY.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dshayield);
    SimYieldTable_DarkSUSY.reset_and_calculate();

    // Collect missing final states for simulation in cascade MC
    GA_missingFinalStates.resolveDependency(&TH_ProcessCatalog_MSSM);
    GA_missingFinalStates.resolveDependency(&SimYieldTable_DarkSUSY);
    GA_missingFinalStates.resolveDependency(&DarkMatter_ID_MSSM);
    GA_missingFinalStates.reset_and_calculate();

    // Infer for which type of final states particles MC should be performed
    cascadeMC_FinalStates.setOption<std::vector<std::string>>("cMC_finalStates", daFunk::vec<std::string>("gamma"));
    cascadeMC_FinalStates.reset_and_calculate();

    // Collect decay information for cascade MC
    cascadeMC_DecayTable.resolveDependency(&TH_ProcessCatalog_MSSM);
    cascadeMC_DecayTable.resolveDependency(&SimYieldTable_DarkSUSY);
    cascadeMC_DecayTable.reset_and_calculate();

    // cascadeMC_LoopManager.setOption<int>("cMC_maxEvents", 100000);
    // cascadeMC_Histograms.setOption<double>("cMC_endCheckFrequency", 25);
    // cascadeMC_Histograms.setOption<double>("cMC_gammaRelError", .05);
    // cascadeMC_Histograms.setOption<int>("cMC_numSpecSamples", 25);
    // cascadeMC_Histograms.setOption<int>("cMC_NhistBins", 300);

    // Set up MC loop manager for cascade MC
    cascadeMC_LoopManager.resolveDependency(&GA_missingFinalStates);
    std::vector<functor*> nested_functions = initVector<functor*>(
            &cascadeMC_InitialState, &cascadeMC_GenerateChain, &cascadeMC_Histograms, &cascadeMC_EventCount);
    cascadeMC_LoopManager.setNestedList(nested_functions);

    // Set up initial state for cascade MC step
    cascadeMC_InitialState.resolveDependency(&GA_missingFinalStates);
    cascadeMC_InitialState.resolveLoopManager(&cascadeMC_LoopManager);

    // Perform MC step for cascade MC
    cascadeMC_GenerateChain.resolveDependency(&cascadeMC_InitialState);
    cascadeMC_GenerateChain.resolveDependency(&cascadeMC_DecayTable);
    cascadeMC_GenerateChain.resolveLoopManager(&cascadeMC_LoopManager);

    // Generate histogram for cascade MC
    cascadeMC_Histograms.resolveDependency(&cascadeMC_InitialState);
    cascadeMC_Histograms.resolveDependency(&cascadeMC_GenerateChain);
    cascadeMC_Histograms.resolveDependency(&TH_ProcessCatalog_MSSM);
    cascadeMC_Histograms.resolveDependency(&SimYieldTable_DarkSUSY);
    cascadeMC_Histograms.resolveDependency(&cascadeMC_FinalStates);
    cascadeMC_Histograms.resolveLoopManager(&cascadeMC_LoopManager);

    // Check convergence of cascade MC
    cascadeMC_EventCount.resolveDependency(&cascadeMC_InitialState);
    cascadeMC_EventCount.resolveLoopManager(&cascadeMC_LoopManager);

    // Start cascade MC loop
    cascadeMC_LoopManager.reset_and_calculate();

    // Infer gamma-ray spectra for recorded MC results
    cascadeMC_gammaSpectra.resolveDependency(&GA_missingFinalStates);
    cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_FinalStates);
    cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_Histograms);
    cascadeMC_gammaSpectra.resolveDependency(&cascadeMC_EventCount);
    cascadeMC_gammaSpectra.reset_and_calculate();

    // Calculate total gamma-ray yield (cascade MC + tabulated results)
    GA_AnnYield_General.resolveDependency(&TH_ProcessCatalog_MSSM);
    GA_AnnYield_General.resolveDependency(&SimYieldTable_DarkSUSY);
    GA_AnnYield_General.resolveDependency(&DarkMatter_ID_MSSM);
    GA_AnnYield_General.resolveDependency(&cascadeMC_gammaSpectra);
    GA_AnnYield_General.reset_and_calculate();

    // Dump spectrum into file
    dump_GammaSpectrum.resolveDependency(&GA_AnnYield_General);
    dump_GammaSpectrum.setOption<std::string>("filename", outname);
    dump_GammaSpectrum.reset_and_calculate();

    // Calculate Fermi LAT dwarf likelihood
    lnL_FermiLATdwarfs_gamLike.resolveDependency(&GA_AnnYield_General);
    lnL_FermiLATdwarfs_gamLike.resolveDependency(&RD_fraction_one);
    lnL_FermiLATdwarfs_gamLike.resolveBackendReq(&Backends::gamLike_1_0_1::Functown::lnL);
    lnL_FermiLATdwarfs_gamLike.reset_and_calculate();

    // ---- IceCube limits ----

    // Infer WIMP capture rate in Sun
    capture_rate_Sun_const_xsec.resolveDependency(&mwimp_generic);
    capture_rate_Sun_const_xsec.resolveDependency(&sigma_SI_p_simple);
    capture_rate_Sun_const_xsec.resolveDependency(&sigma_SD_p_simple);
    capture_rate_Sun_const_xsec.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsntcapsuntab);
    capture_rate_Sun_const_xsec.resolveDependency(&DarkSUSY_PointInit_LocalHalo_func);
    capture_rate_Sun_const_xsec.reset_and_calculate();

    // Infer WIMP equilibration time in Sun
    equilibration_time_Sun.resolveDependency(&TH_ProcessCatalog_MSSM);
    equilibration_time_Sun.resolveDependency(&DarkMatter_ID_MSSM);
    equilibration_time_Sun.resolveDependency(&mwimp_generic);
    equilibration_time_Sun.resolveDependency(&capture_rate_Sun_const_xsec);
    equilibration_time_Sun.reset_and_calculate();

    // Infer WIMP annihilation rate in Sun
    annihilation_rate_Sun.resolveDependency(&equilibration_time_Sun);
    annihilation_rate_Sun.resolveDependency(&capture_rate_Sun_const_xsec);
    annihilation_rate_Sun.reset_and_calculate();

    // Infer neutrino yield from Sun
    nuyield_from_DS.resolveDependency(&TH_ProcessCatalog_MSSM);
    nuyield_from_DS.resolveDependency(&mwimp_generic);
    nuyield_from_DS.resolveDependency(&sigmav_late_universe);
    nuyield_from_DS.resolveDependency(&DarkMatter_ID_MSSM);
    nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::dsgenericwimp_nusetup);
    nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::neutrino_yield);
    nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::DS_neutral_h_decay_channels);
    nuyield_from_DS.resolveBackendReq(&Backends::DarkSUSY_5_1_3::Functown::DS_charged_h_decay_channels);
    nuyield_from_DS.reset_and_calculate();

    // Calculate number of events at IceCube
    IC79WH_full.resolveDependency(&mwimp_generic);
    IC79WH_full.resolveDependency(&annihilation_rate_Sun);
    IC79WH_full.resolveDependency(&nuyield_from_DS);
    IC79WH_full.resolveBackendReq(&Backends::nulike_1_0_8::Functown::nulike_bounds);
    IC79WH_full.reset_and_calculate();
    IC79WL_full.resolveDependency(&mwimp_generic);
    IC79WL_full.resolveDependency(&annihilation_rate_Sun);
    IC79WL_full.resolveDependency(&nuyield_from_DS);
    IC79WL_full.resolveBackendReq(&Backends::nulike_1_0_8::Functown::nulike_bounds);
    IC79WL_full.reset_and_calculate();
    IC79SL_full.resolveDependency(&mwimp_generic);
    IC79SL_full.resolveDependency(&annihilation_rate_Sun);
    IC79SL_full.resolveDependency(&nuyield_from_DS);
    IC79SL_full.resolveBackendReq(&Backends::nulike_1_0_8::Functown::nulike_bounds);
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

    // ---- Run DarkBit UnitTests ----

    UnitTest_DarkBit.setOption<std::string>("filename", filename_dump);
    UnitTest_DarkBit.resolveDependency(&RD_oh2_DarkSUSY);
    UnitTest_DarkBit.resolveDependency(&GA_AnnYield_General);
    UnitTest_DarkBit.resolveDependency(&TH_ProcessCatalog_MSSM);
    UnitTest_DarkBit.resolveDependency(&DarkMatter_ID_MSSM);
    UnitTest_DarkBit.resolveDependency(&DD_couplings_DarkSUSY);
    UnitTest_DarkBit.reset_and_calculate();


    // ---- Dump results on screen ----

    cout << endl;
    // Retrieve and print MicrOmegas result
    cout << "Omega h^2 from MicrOmegas: " << RD_oh2_MicrOmegas(0) << endl;

    // Retrieve and print DarkSUSY result
    cout << "Omega h^2 from RD_oh2_general routine: " << RD_oh2_general(0) << endl;

    cout << "Relic density lnL: " << lnL_oh2_Simple(0) << endl;
    cout << endl;

    // Print scattering cross section for DS and MO:
    cout << " sigma_SI_p [cm^2]: " << endl;
    cout << "    MO: " << sigma_SI_p_MO << endl;

    cout << "    DS: " << sigma_SI_p_DS << endl;
    cout << " sigma_SD_p [cm^2]: " << endl;
    cout << "    MO: " << sigma_SD_p_MO << endl;
    cout << "    DS: " << sigma_SD_p_DS << endl;

    cout << "LUX 2016 lnL: " << LUX_2016_GetLogLikelihood(0) << endl;
    cout << "IceCube 79 lnL: " << IC79_loglike(0) << endl;
    cout << endl;

    cout << "<sigma v> [cm^3/s]: " << sigmav_late_universe(0) << endl;
    cout << "Fermi LAT dwarf spheroidal lnL: " << lnL_FermiLATdwarfs_gamLike(0) << endl;


    // ---- Dump output into file ----

    std::fstream file;
    file.open(filename_data, std::ios_base::out);

    file << "Omega h^2:"<< endl;
    file << "  MO: " << RD_oh2_MicrOmegas(0) << endl;
    file << "  DS: " << RD_oh2_general(0) << endl;

    file << "WMAP lnL: " << lnL_oh2_Simple(0) << endl;
    file << endl;

    file << " sigma_SI_p [cm^2]: " << endl;
    file << "    MO: " << sigma_SI_p_MO << endl;
    file << "    DS: " << sigma_SI_p_DS << endl;
    file << " sigma_SD_p [cm^2]: " << endl;
    file << "    MO: " << sigma_SD_p_MO << endl;
    file << "    DS: " << sigma_SD_p_DS << endl;

    file << "LUX 2016 lnL: " << LUX_2016_GetLogLikelihood(0) << endl;
    file << "IceCube 79 lnL: " << IC79_loglike(0) << endl;
    file << endl;

    file << "<sigma v> [cm^3/s]: " << sigmav_late_universe(0) << endl;
    file << "Fermi LAT dwarf spheroidal lnL: " << lnL_FermiLATdwarfs_gamLike(0) << endl;

    file.close();
  }

  catch (std::exception& e)
  {
    std::cout << "DarkBit_standalone_MSSM has exited with fatal exception: " << e.what() << std::endl;
  }

  return 0;

}
