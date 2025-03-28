//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example of GAMBIT NeutrinoBit standalone
///  main program.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///  \date 2024 Dec
///
///  *********************************************

#include <iostream>
#include <fstream>

#include <boost/multi_array.hpp>

#include "gambit/Elements/standalone_module.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/NeutrinoBit/NeutrinoBit_rollcall.hpp"

//#define NEUTRINOBIT_STANDALONE_WIMP_DEBUG

using namespace NeutrinoBit::Functown;     // Functors wrapping the module's actual module functions

int main(int argc, char *argv[])
{
  std::cout << std::endl;
  std::cout << "Welcome to the NeutrinoBit standalone program!" << std::endl;
  std::cout << std::endl;
  std::cout << "********************************************************************************" << std::endl;
  std::cout << "Usage: NeutrinoBit_standalone SLHA_file (output)" << std::endl;
  std::cout << std::endl;
  std::cout << "SLHA_file: SLHA file used to intialise the program (required)" << std::endl;
  std::cout << "(output): name of output file for observables and likelihoods (default: NeutrinoBit_standalone.out)" << std::endl;
  std::cout << std::endl;
  std::cout << "Example SLHA files can be found in NeutrinoBit/examples/benchmarks/" << std::endl;
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
    std::string outname_data = "NeutrinoBit_standalone.out";
    if (argc >= 3) outname_data = argv[3];

    // ---- Initialise logging and exceptions ----

    initialise_standalone_logs("runs/NeutrinoBit_standalone/logs/");
    logger()<<"Running NeutrinoBit standalone example"<<LogTags::info<<EOM;
    model_warning().set_fatal(true);

    // Initialise settings for printer (required)
    YAML::Node printerNode = get_standalone_printer("cout", "runs/NeutrinoBit_standalone/logs/","");
    Printers::PrinterManager printerManager(printerNode, false);
    set_global_printer_manager(&printerManager);

    // ---- Useful variables ----
    //
    // Prepare a str-double map of maps to hold the results.
    std::map<std::string, double> results;

    // ---- Initialize models ----

    // Read SLHA file
    SLHAstruct data = read_SLHA(filename);
    double alphainv = SLHAea_get(data, "SMINPUTS",  1);
    double GF       = SLHAea_get(data, "SMINPUTS",  2);
    double alphaS   = SLHAea_get(data, "SMINPUTS",  3);
    double mZ       = SLHAea_get(data, "SMINPUTS",  4);
    double mBmB     = SLHAea_get(data, "SMINPUTS",  5);
    double mT       = SLHAea_get(data, "SMINPUTS",  6);
    double mTau     = SLHAea_get(data, "SMINPUTS",  7);
    double mE       = SLHAea_get(data, "SMINPUTS", 11);
    double mMu      = SLHAea_get(data, "SMINPUTS", 13);
    double mD       = SLHAea_get(data, "SMINPUTS", 21);
    double mU       = SLHAea_get(data, "SMINPUTS", 22);
    double mS       = SLHAea_get(data, "SMINPUTS", 23);
    double mCmC     = SLHAea_get(data, "SMINPUTS", 24);

    double mNu1, mNu2, mNu3;
    if(SLHAea_check_block(data, "SMINPUTS", 12) and
       SLHAea_check_block(data, "SMINPUTS", 14) and
       SLHAea_check_block(data, "SMINPUTS", 8))
    {
      mNu1     = SLHAea_get(data, "SMINPUTS", 12);
      mNu2     = SLHAea_get(data, "SMINPUTS", 14);
      mNu3     = SLHAea_get(data, "SMINPUTS",  8);
    }
    else if (SLHAea_check_block(data, "SMINPUTS", 100) and
             SLHAea_check_block(data, "SMINPUTS", 101) and
             SLHAea_check_block(data, "SMINPUTS", 102))
    {
      double mNu0  = SLHAea_get(data, "SMINPUTS", 100);
      double m21Sq = SLHAea_get(data, "SMINPUTS", 101);
      double m3lSq = SLHAea_get(data, "SMINPUTS", 102);
      if(m3lSq > 0) // NO
      {
        mNu1 = mNu0*1e-9;
        mNu2 = sqrt(mNu1*mNu1 + m21Sq*1e-18);
        mNu3 = sqrt(mNu2*mNu2 + m3lSq*1e-18);
      }
      else // IO
      {
        mNu3 = mNu0*1e-9;
        mNu1 = sqrt(mNu3*mNu3 - m3lSq*1e-18);
        mNu2 = sqrt(mNu1*mNu1 + m21Sq*1e-18);
      }
    }
    else
    {
      std::ostringstream errmsg;
      errmsg << "Error reading SLHA file! ";
      errmsg << "SMINPUTS must contain either the pole masses of neutrinos, entries 8, 12 and 14, ";
      errmsg << "or the lightest mass and mass splittings, entries 100, 101 and 102." << std::endl;
      std::cout << errmsg.str() << std::endl;
      throw std::runtime_error(errmsg.str());
    }

    double lambda  = SLHAea_get(data,"VCKMIN", 1);
    double A       = SLHAea_get(data,"VCKMIN", 2);
    double rhobar  = SLHAea_get(data,"VCKMIN", 3);
    double etabar  = SLHAea_get(data,"VCKMIN", 4);

    double th12    = SLHAea_get(data, "UPMNSIN", 1);
    double th23    = SLHAea_get(data, "UPMNSIN", 2);
    double th13    = SLHAea_get(data, "UPMNSIN", 3);
    double d13     = SLHAea_get(data, "UPMNSIN", 4);
    double alpha1  = SLHAea_get(data, "UPMNSIN", 5);
    double alpha2  = SLHAea_get(data, "UPMNSIN", 6);

    // Initialize Standard Model
    ModelParameters* StandardModel_SLHA2_primary_parameters = Models::StandardModel_SLHA2::Functown::primary_parameters.getcontentsPtr();
    StandardModel_SLHA2_primary_parameters->setValue("alphainv"  ,  alphainv);
    StandardModel_SLHA2_primary_parameters->setValue("GF"        ,  GF);
    StandardModel_SLHA2_primary_parameters->setValue("alphaS"    ,  alphaS);
    StandardModel_SLHA2_primary_parameters->setValue("mZ"        ,  mZ);
    StandardModel_SLHA2_primary_parameters->setValue("mD"        ,  mD);
    StandardModel_SLHA2_primary_parameters->setValue("mU"        ,  mU);
    StandardModel_SLHA2_primary_parameters->setValue("mS"        ,  mS);
    StandardModel_SLHA2_primary_parameters->setValue("mCmC"      ,  mCmC);
    StandardModel_SLHA2_primary_parameters->setValue("mBmB"      ,  mBmB);
    StandardModel_SLHA2_primary_parameters->setValue("mT"        ,  mT);
    StandardModel_SLHA2_primary_parameters->setValue("mE"        ,  mE);
    StandardModel_SLHA2_primary_parameters->setValue("mMu"       ,  mMu);
    StandardModel_SLHA2_primary_parameters->setValue("mTau"      ,  mTau);
    StandardModel_SLHA2_primary_parameters->setValue("CKM_lambda",  lambda);
    StandardModel_SLHA2_primary_parameters->setValue("CKM_A"     ,  A);
    StandardModel_SLHA2_primary_parameters->setValue("CKM_rhobar",  rhobar);
    StandardModel_SLHA2_primary_parameters->setValue("CKM_etabar",  etabar);

    StandardModel_SLHA2_primary_parameters->setValue("mNu1"   ,  mNu1);
    StandardModel_SLHA2_primary_parameters->setValue("mNu2"   ,  mNu2);
    StandardModel_SLHA2_primary_parameters->setValue("mNu3"   ,  mNu3);
    StandardModel_SLHA2_primary_parameters->setValue("theta12",  th12);
    StandardModel_SLHA2_primary_parameters->setValue("theta23",  th23);
    StandardModel_SLHA2_primary_parameters->setValue("theta13",  th13);
    StandardModel_SLHA2_primary_parameters->setValue("delta13",  d13);
    StandardModel_SLHA2_primary_parameters->setValue("alpha1" ,  alpha1);
    StandardModel_SLHA2_primary_parameters->setValue("alpha2" ,  alpha2);

    // ---- Calculate active neutrino parameters ----

    // Mass ordering
    ordering.notifyOfModel("StandardModel_SLHA2");
    ordering.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    ordering.reset_and_calculate();
    results["ordering"] = ordering(0);

    // Neutrino masses
    M_nu.notifyOfModel("StandardModel_SLHA2");
    M_nu.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    M_nu.resolveDependency(&ordering);
    M_nu.reset_and_calculate();

    md21.resolveDependency(&M_nu);
    md21.reset_and_calculate();
    results["md21"] = md21(0);

    md31.resolveDependency(&M_nu);
    md31.reset_and_calculate();
    results["md31"] = md31(0);

    md32.resolveDependency(&M_nu);
    md32.reset_and_calculate();
    results["md32"] = md32(0);

    min_mass.resolveDependency(&M_nu);
    min_mass.resolveDependency(&ordering);
    min_mass.reset_and_calculate();
    results["min_mass"] = min_mass(0);

    // Neutrino mixings
    theta12.notifyOfModel("StandardModel_SLHA2");
    theta12.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    theta12.reset_and_calculate();
    results["theta12"] = theta12(0);

    theta13.notifyOfModel("StandardModel_SLHA2");
    theta13.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    theta13.reset_and_calculate();
    results["theta13"] = theta13(0);

    theta23.notifyOfModel("StandardModel_SLHA2");
    theta23.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    theta23.reset_and_calculate();
    results["theta23"] = theta23(0);

    deltaCP.notifyOfModel("StandardModel_SLHA2");
    deltaCP.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    deltaCP.reset_and_calculate();
    results["deltaCP"] = deltaCP(0);

    // PMNS matrix
    UPMNS.notifyOfModel("StandardModel_SLHA2");
    UPMNS.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    UPMNS.reset_and_calculate();


    // ---- Calculate oscillation constraints ----

    // Use NuFit 4.1 2D likelihood for mass splittings
    md21_md3l_NuFit_v4_1_lnL.resolveDependency(&ordering);
    md21_md3l_NuFit_v4_1_lnL.resolveDependency(&md21);
    md21_md3l_NuFit_v4_1_lnL.resolveDependency(&md31);
    md21_md3l_NuFit_v4_1_lnL.resolveDependency(&md32);
    md21_md3l_NuFit_v4_1_lnL.reset_and_calculate();
    results["md21_md3l_NuFit_v4_1_lnL"] = md21_md3l_NuFit_v4_1_lnL(0);
    results["LogLike" ] = md21_md3l_NuFit_v4_1_lnL(0);

    // 1D NuFit 4.1 for the rest
    theta12_NuFit_v4_1_lnL.resolveDependency(&ordering);
    theta12_NuFit_v4_1_lnL.resolveDependency(&theta12);
    theta12_NuFit_v4_1_lnL.reset_and_calculate();
    results["theta12_NuFit_v4_1_lnL"] = theta12_NuFit_v4_1_lnL(0);
    results["LogLike" ] += theta12_NuFit_v4_1_lnL(0);

    theta13_NuFit_v4_1_lnL.resolveDependency(&ordering);
    theta13_NuFit_v4_1_lnL.resolveDependency(&theta13);
    theta13_NuFit_v4_1_lnL.reset_and_calculate();
    results["theta13_NuFit_v4_1_lnL"] = theta13_NuFit_v4_1_lnL(0);
    results["LogLike"] += theta13_NuFit_v4_1_lnL(0);

    theta23_NuFit_v4_1_lnL.resolveDependency(&ordering);
    theta23_NuFit_v4_1_lnL.resolveDependency(&theta23);
    theta23_NuFit_v4_1_lnL.reset_and_calculate();
    results["theta23_NuFit_v4_1_lnL"] = theta23_NuFit_v4_1_lnL(0);
    results["LogLike"] += theta23_NuFit_v4_1_lnL(0);

    deltaCP_NuFit_v4_1_lnL.resolveDependency(&ordering);
    deltaCP_NuFit_v4_1_lnL.resolveDependency(&deltaCP);
    deltaCP_NuFit_v4_1_lnL.reset_and_calculate();
    results["deltaCP_NuFit_v4_1_lnL"] = deltaCP_NuFit_v4_1_lnL(0);
    results["LogLike"] += deltaCP_NuFit_v4_1_lnL(0);

    // ---- Calculate cosmological bounds ----0

    // Sum of neutrino masses
    sum_mnu_lnL.notifyOfModel("StandardModel_SLHA2");
    sum_mnu_lnL.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    sum_mnu_lnL.reset_and_calculate();
    results["sum_mnu_lnL2"] = sum_mnu_lnL(0);
    results["LogLike"] += sum_mnu_lnL(0);

    //
    // ======= Construct the output string =======
    //

    std::stringstream results_ss;

    for(auto result : results)
    {
      results_ss << result.first;
      results_ss << " : " ;
      results_ss << result.second;
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
    std::cout << "NeutrinoBit_standalone has exited with fatal exception: " << e.what() << std::endl;
  }

  return 0;


}

