//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Example of GAMBIT NeutrinoBit standalone
///  main program for the RHN model.
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

QUICK_FUNCTION(NeutrinoBit, SMINPUTS, NEW_CAPABILITY, get_SMINPUTS, SMInputs, (StandardModel_SLHA2))
QUICK_FUNCTION(NeutrinoBit, prec_sinW2_eff, NEW_CAPABILITY, RHN_sinW2_eff, triplet<double>, (RightHandedNeutrinos), (SeesawI_Theta,  Eigen::Matrix3cd))
QUICK_FUNCTION(NeutrinoBit, mw, NEW_CAPABILITY, RHN_mw, triplet<double>, (RightHandedNeutrinos), (SeesawI_Theta, Eigen::Matrix3cd), (prec_sinW2_eff, triplet<double>))
QUICK_FUNCTION(NeutrinoBit, W_to_l_decays, NEW_CAPABILITY, RHN_W_to_l_decays, std::vector<double>, (RightHandedNeutrinos), (SeesawI_Theta,  Eigen::Matrix3cd), (SMINPUTS, SMInputs), (mw, triplet<double>))


// ---- Set up basic sminputs to avoid using SpecBit ----

namespace Gambit
{
  namespace NeutrinoBit
  {

    void get_SMINPUTS(SMInputs &result)
    {
      namespace myPipe = Pipes::get_SMINPUTS;
      SMInputs sminputs;

      // Get values from Params pipe
      // (as defined in SLHA2)
      if(myPipe::ModelInUse("StandardModel_SLHA2"))
      {
         sminputs.alphainv = *myPipe::Param["alphainv"];
         sminputs.GF       = *myPipe::Param["GF"      ];
         sminputs.alphaS   = *myPipe::Param["alphaS"  ];

         sminputs.mZ       = *myPipe::Param["mZ"      ];

         sminputs.mE       = *myPipe::Param["mE"      ];
         sminputs.mMu      = *myPipe::Param["mMu"     ];
         sminputs.mTau     = *myPipe::Param["mTau"    ];

         sminputs.mNu1     = *myPipe::Param["mNu1"    ];
         sminputs.mNu2     = *myPipe::Param["mNu2"    ];
         sminputs.mNu3     = *myPipe::Param["mNu3"    ];

         sminputs.mD       = *myPipe::Param["mD"      ];
         sminputs.mU       = *myPipe::Param["mU"      ];
         sminputs.mS       = *myPipe::Param["mS"      ];
         sminputs.mCmC     = *myPipe::Param["mCmC"    ];
         sminputs.mBmB     = *myPipe::Param["mBmB"    ];
         sminputs.mT       = *myPipe::Param["mT"      ];

         sminputs.mNu1     = *myPipe::Param["mNu1"    ];
         sminputs.mNu2     = *myPipe::Param["mNu2"    ];
         sminputs.mNu3     = *myPipe::Param["mNu3"    ];

         // CKM
         sminputs.CKM.lambda   = *myPipe::Param["CKM_lambda" ];
         sminputs.CKM.A        = *myPipe::Param["CKM_A" ];
         sminputs.CKM.rhobar   = *myPipe::Param["CKM_rhobar" ];
         sminputs.CKM.etabar   = *myPipe::Param["CKM_etabar" ];

         // PMNS
         sminputs.PMNS.theta12 = *myPipe::Param["theta12"];
         sminputs.PMNS.theta23 = *myPipe::Param["theta23"];
         sminputs.PMNS.theta13 = *myPipe::Param["theta13"];
         sminputs.PMNS.delta13 = *myPipe::Param["delta13"];
         sminputs.PMNS.alpha1  = *myPipe::Param["alpha1"];
         sminputs.PMNS.alpha2  = *myPipe::Param["alpha2"];

         // W mass.  Stick with the observed value (set in the default constructor) unless instructed otherwise.
         if (myPipe::runOptions->getValueOrDef<bool>(false,"enforce_tree_level_MW"))
         {
           // Calculate MW from alpha, mZ and G_F, assuming the tree-level relation.
           const double pionroot2 = pi * pow(2,-0.5);
           double cosW2 = 0.5 + pow(0.25 - pionroot2 / (sminputs.alphainv * sminputs.GF * pow(sminputs.mZ,2.0)), 0.5);
           sminputs.mW = sminputs.mZ * pow(cosW2,0.5);
         }

      }
      else
      {
         std::ostringstream errmsg;
         errmsg << "Error mapping Standard Model parameters to SMINPUTS capabilities!";
         errmsg << "Perhaps you have added a new model to the ALLOWED_MODELS of this ";
         errmsg << "module function but have not added a corresponding case in the ";
         errmsg << "function source (here)." << std::endl;
         std::cout << errmsg.str() << std::endl;
         throw std::runtime_error(errmsg.str());
      }
      // Return filled struct
      result = sminputs;
    }

    // Weak mixing angle sinW2, calculation from 1211.1864
    void RHN_sinW2_eff(triplet<double> &result)
    {
      using namespace Pipes::RHN_sinW2_eff;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3d ThetaNorm = (Theta * Theta.adjoint()).real();

      double sinW2_SM = 0.23152; // taken from 1211.1864
      double sinW2_SM_err = 0.00010;

      result.central = 0.5 - 0.5*sqrt(1.0 - 4*sinW2_SM*(1.0 - sinW2_SM)*sqrt(1.0 - ThetaNorm(0,0) - ThetaNorm(1,1)) );
      result.upper = (1.0 - 2*sinW2_SM) / (1.0 - 2*result.central) * sqrt(1.0 - ThetaNorm(0,0) - ThetaNorm(1,1)) * sinW2_SM_err;
      result.lower = result.upper;
    }

    // Mass of W boson, calculation from 1502.00477
    void RHN_mw(triplet<double> &result)
    {
      using namespace Pipes::RHN_mw;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      triplet<double> sinW2 = *Dep::prec_sinW2_eff;
      Eigen::Matrix3d ThetaNorm = (Theta * Theta.adjoint()).real();

      // SM precision calculation, from 1211.1864
      double sinW2_SM = 0.23152;
      double sinW2_SM_err = 0.00010;
      double mW_SM = 80.361;
      double mW_SM_err = 0.010;

      // Radiative corrections, form Marco's paper
      result.central = sqrt( pow(mW_SM,2) * sinW2_SM / sinW2.central * sqrt(1.0 - ThetaNorm(0,0) - ThetaNorm(1,1))  );
      result.upper = 0.5*result.central*sqrt( pow(2*mW_SM_err/mW_SM,2) + pow(sinW2_SM_err/sinW2_SM,2) + pow(sinW2.upper/sinW2.central,2)  );
      result.lower = result.upper;
    }

    // W decays, calculation from 1407.6607
    void RHN_W_to_l_decays(std::vector<double> &result)
    {
      using namespace Pipes::RHN_W_to_l_decays;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      double Gmu = sminputs.GF;
      double mw = Dep::mw->central;

      Eigen::Matrix3d ThetaNorm = (Theta * Theta.adjoint()).real();
      std::vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      std::vector<double> M = {*Param["M_1"], *Param["M_2"], *Param["M_3"]};

      result.clear();
      for(int i=0; i<3; i++)
      {
        if(M[i] < mw)
          result.push_back(Gmu*pow(mw,3)/(6*sqrt(2)*M_PI)*pow(1.0 - pow(ml[i]/mw,2),2)*(1.0 + pow(ml[i]/mw,2))/sqrt(1.0 - ThetaNorm(0,0) -ThetaNorm(1,1)));
        else
          result.push_back(Gmu*pow(mw,3)/(6*sqrt(2)*M_PI)*(1.0-ThetaNorm(i,i))*pow(1.0 - pow(ml[i]/mw,2),2)*(1.0 + pow(ml[i]/mw,2))/sqrt(1.0 - ThetaNorm(0,0) -ThetaNorm(1,1)));
      }
    }


    /// @} End Gambit module functions

  } // end namespace SpecBit
} // end namespace Gambit



int main(int argc, char *argv[])
{
  std::cout << std::endl;
  std::cout << "Welcome to the NeutrinoBit RHN standalone program!" << std::endl;
  std::cout << std::endl;
  std::cout << "********************************************************************************" << std::endl;
  std::cout << "Usage: NeutrinoBit_standalone_RHN SLHA_file (output)" << std::endl;
  std::cout << std::endl;
  std::cout << "SLHA_file: SLHA file used to intialise the program (required)" << std::endl;
  std::cout << "(output): name of output file for observables and likelihoods (default: NeutrinoBit_standalone_RHN.out)" << std::endl;
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
    std::string outname_data = "NeutrinoBit_standalone_RHN.out";
    if (argc >= 3) outname_data = argv[3];

    // ---- Initialise logging and exceptions ----

    initialise_standalone_logs("runs/NeutrinoBit_standalone_RHN/logs/");
    logger()<<"Running NeutrinoBit standalone example"<<LogTags::info<<EOM;
    model_warning().set_fatal(true);

    // Initialise settings for printer (required)
    YAML::Node printerNode = get_standalone_printer("cout", "runs/NeutrinoBit_standalone_RHN/logs/","");
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


    double mH       = SLHAea_get(data, "MASS", 25);

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

    double M1     = SLHAea_get(data, "RHN", 1);
    double M2;
    if(SLHAea_check_block(data, "RHN", 2))
      M2 = SLHAea_get(data, "RHN", 2);
    else if (SLHAea_check_block(data, "RHN", 12))
      M2 = M1 + SLHAea_get(data, "RHN", 12);
    else
    {
      std::stringstream errmsg;
      errmsg << "Error reading SLHA! You must provide either M2 (entry 2) or delta_M21 (entry 12)" << std::endl;
      throw std::runtime_error(errmsg.str());
    }
    double M3     = SLHAea_get(data, "RHN", 3);
    double ReOm12 = SLHAea_get(data, "RHN", 4);
    double ImOm12 = SLHAea_get(data, "RHN", 5);
    double ReOm13 = SLHAea_get(data, "RHN", 6);
    double ImOm13 = SLHAea_get(data, "RHN", 7);
    double ReOm23 = SLHAea_get(data, "RHN", 8);
    double ImOm23 = SLHAea_get(data, "RHN", 9);

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

    // Initialize SM Higgs model
    ModelParameters *StandardModel_Higgs_primary_parameters = Models::StandardModel_Higgs::Functown::primary_parameters.getcontentsPtr();
    StandardModel_Higgs_primary_parameters->setValue("mH", mH);

    // Initialize RHN model
    ModelParameters* RightHandedNeutrinos_primary_parameters = Models::RightHandedNeutrinos::Functown::primary_parameters.getcontentsPtr();
    RightHandedNeutrinos_primary_parameters->setValue("M_1", M1);
    RightHandedNeutrinos_primary_parameters->setValue("M_2", M2);
    RightHandedNeutrinos_primary_parameters->setValue("M_3", M3);
    RightHandedNeutrinos_primary_parameters->setValue("ReOm12", ReOm12);
    RightHandedNeutrinos_primary_parameters->setValue("ImOm12", ImOm12);
    RightHandedNeutrinos_primary_parameters->setValue("ReOm13", ReOm13);
    RightHandedNeutrinos_primary_parameters->setValue("ImOm13", ImOm13);
    RightHandedNeutrinos_primary_parameters->setValue("ReOm23", ReOm23);
    RightHandedNeutrinos_primary_parameters->setValue("ImOm23", ImOm23);
    RightHandedNeutrinos_primary_parameters->setValue("Rorder", 0.);


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

    get_SMINPUTS.notifyOfModel("StandardModel_SLHA2");
    get_SMINPUTS.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    get_SMINPUTS.reset_and_calculate();

    // ---- Calculate RHN mixing parameters ----

    CI_Theta.notifyOfModel("StandardModel_Higgs");
    CI_Theta.notifyOfModel("RightHandedNeutrinos");
    CI_Theta.resolveDependency(&Models::StandardModel_Higgs::Functown::primary_parameters);
    CI_Theta.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    CI_Theta.resolveDependency(&M_nu);
    CI_Theta.resolveDependency(&UPMNS);
    CI_Theta.resolveDependency(&get_SMINPUTS);
    CI_Theta.reset_and_calculate();

    Vnu.notifyOfModel("RightHandedNeutrinos");
    Vnu.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    Vnu.resolveDependency(&UPMNS);
    Vnu.resolveDependency(&CI_Theta);
    Vnu.reset_and_calculate();

    Ue1.resolveDependency(&CI_Theta);
    Ue1.reset_and_calculate();
    results["Ue1"] = Ue1(0);

    Ue2.resolveDependency(&CI_Theta);
    Ue2.reset_and_calculate();
    results["Ue2"] = Ue2(0);

    Ue3.resolveDependency(&CI_Theta);
    Ue3.reset_and_calculate();
    results["Ue3"] = Ue3(0);

    Um1.resolveDependency(&CI_Theta);
    Um1.reset_and_calculate();
    results["Um1"] = Um1(0);

    Um2.resolveDependency(&CI_Theta);
    Um2.reset_and_calculate();
    results["Um2"] = Um2(0);

    Um3.resolveDependency(&CI_Theta);
    Um3.reset_and_calculate();
    results["Um3"] = Um3(0);

    Ut1.resolveDependency(&CI_Theta);
    Ut1.reset_and_calculate();
    results["Ut1"] = Ut1(0);

    Ut2.resolveDependency(&CI_Theta);
    Ut2.reset_and_calculate();
    results["Ut2"] = Ut2(0);

    Ut3.resolveDependency(&CI_Theta);
    Ut3.reset_and_calculate();
    results["Ut3"] = Ut3(0);

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

    // ---- Calculate cosmological bounds ----

    // Sum of neutrino masses
    sum_mnu_lnL.notifyOfModel("StandardModel_SLHA2");
    sum_mnu_lnL.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);
    sum_mnu_lnL.reset_and_calculate();
    results["sum_mnu_lnL2"] = sum_mnu_lnL(0);
    results["LogLike"] += sum_mnu_lnL(0);

    RHN_sinW2_eff.notifyOfModel("RightHandedNeutrinos");
    RHN_sinW2_eff.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    RHN_sinW2_eff.resolveDependency(&CI_Theta);
    RHN_sinW2_eff.reset_and_calculate();

    // BBN decays and likelihood
    #define DECAY(channel) \
      channel.notifyOfModel("RightHandedNeutrinos");\
      channel.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);\
      channel.resolveDependency(&get_SMINPUTS);\
      channel.resolveDependency(&CI_Theta);

    #define DECAY1(channel) \
      DECAY(channel) \
      channel.reset_and_calculate();

    #define DECAY2(channel) \
      DECAY(channel) \
      channel.notifyOfModel("StandardModel_SLHA2");\
      channel.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);\
      channel.reset_and_calculate();

    #define DECAY3(channel) \
      DECAY(channel) \
      channel.resolveDependency(&RHN_sinW2_eff); \
      channel.reset_and_calculate();

    #define DECAY4(channel) \
      DECAY(channel) \
      channel.notifyOfModel("StandardModel_SLHA2");\
      channel.resolveDependency(&Models::StandardModel_SLHA2::Functown::primary_parameters);\
      channel.resolveDependency(&RHN_sinW2_eff); \
      channel.reset_and_calculate();

    DECAY2(Gamma_RHN2piplusl)
    DECAY2(Gamma_RHN2Kplusl)
    DECAY2(Gamma_RHN2Dplusl)
    DECAY2(Gamma_RHN2Dsl)
    DECAY2(Gamma_RHN2Bplusl)
    DECAY2(Gamma_RHN2Bcl)
    DECAY1(Gamma_RHN2pi0nu)
    DECAY1(Gamma_RHN2etanu)
    DECAY1(Gamma_RHN2etaprimenu)
    DECAY1(Gamma_RHN2etacnu)
    DECAY2(Gamma_RHN2rhoplusl)
    DECAY2(Gamma_RHN2Dstarplusl)
    DECAY2(Gamma_RHN2Dstarsl)
    DECAY3(Gamma_RHN2rho0nu)
    DECAY3(Gamma_RHN2omeganu)
    DECAY3(Gamma_RHN2phinu)
    DECAY3(Gamma_RHN2Jpsinu)
    DECAY1(Gamma_RHN23nu)
    DECAY2(Gamma_RHN2llnu)
    DECAY4(Gamma_RHN2null)
    DECAY4(Gamma_RHN2nuuubar)
    DECAY4(Gamma_RHN2nuddbar)
    DECAY2(Gamma_RHN2ludbar)

    Gamma_BBN.notifyOfModel("RightHandedNeutrinos");
    Gamma_BBN.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    Gamma_BBN.resolveDependency(&Gamma_RHN2piplusl);
    Gamma_BBN.resolveDependency(&Gamma_RHN2Kplusl);
    Gamma_BBN.resolveDependency(&Gamma_RHN2Dplusl);
    Gamma_BBN.resolveDependency(&Gamma_RHN2Dsl);
    Gamma_BBN.resolveDependency(&Gamma_RHN2Bplusl);
    Gamma_BBN.resolveDependency(&Gamma_RHN2Bcl);
    Gamma_BBN.resolveDependency(&Gamma_RHN2pi0nu);
    Gamma_BBN.resolveDependency(&Gamma_RHN2etanu);
    Gamma_BBN.resolveDependency(&Gamma_RHN2etaprimenu);
    Gamma_BBN.resolveDependency(&Gamma_RHN2etacnu);
    Gamma_BBN.resolveDependency(&Gamma_RHN2rhoplusl);
    Gamma_BBN.resolveDependency(&Gamma_RHN2Dstarplusl);
    Gamma_BBN.resolveDependency(&Gamma_RHN2Dstarsl);
    Gamma_BBN.resolveDependency(&Gamma_RHN2rho0nu);
    Gamma_BBN.resolveDependency(&Gamma_RHN2omeganu);
    Gamma_BBN.resolveDependency(&Gamma_RHN2phinu);
    Gamma_BBN.resolveDependency(&Gamma_RHN2Jpsinu);
    Gamma_BBN.resolveDependency(&Gamma_RHN23nu);
    Gamma_BBN.resolveDependency(&Gamma_RHN2llnu);
    Gamma_BBN.resolveDependency(&Gamma_RHN2null);
    Gamma_BBN.resolveDependency(&Gamma_RHN2nuuubar);
    Gamma_BBN.resolveDependency(&Gamma_RHN2nuddbar);
    Gamma_BBN.resolveDependency(&Gamma_RHN2ludbar);
    Gamma_BBN.reset_and_calculate();
    results["Gamma_BBN(N1)"] = Gamma_BBN(0)[0];
    results["Gamma_BBN(N2)"] = Gamma_BBN(0)[1];
    results["Gamma_BBN(N3)"] = Gamma_BBN(0)[2];

    lnL_bbn.notifyOfModel("RightHandedNeutrinos");
    lnL_bbn.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_bbn.resolveDependency(&Gamma_BBN);
    lnL_bbn.reset_and_calculate();
    results["lnL_bbn"] = lnL_bbn(0);
    results["LogLike"] += lnL_bbn(0);

    // ---- Calculate lepton flavour universality constraints ----

    // R_pi
    RHN_R_pi.notifyOfModel("RightHandedNeutrinos");
    RHN_R_pi.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    RHN_R_pi.resolveDependency(&get_SMINPUTS);
    RHN_R_pi.resolveDependency(&CI_Theta);
    RHN_R_pi.resolveDependency(&Vnu);
    RHN_R_pi.reset_and_calculate();
    results["R_pi"] = RHN_R_pi(0);

    lnL_R_pi.resolveDependency(&RHN_R_pi);
    lnL_R_pi.reset_and_calculate();
    results["lnL_R_pi"] = lnL_R_pi(0);
    results["LogLike"] += lnL_R_pi(0);

    // R_K
    RHN_R_K.notifyOfModel("RightHandedNeutrinos");
    RHN_R_K.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    RHN_R_K.resolveDependency(&get_SMINPUTS);
    RHN_R_K.resolveDependency(&CI_Theta);
    RHN_R_K.resolveDependency(&Vnu);
    RHN_R_K.reset_and_calculate();
    results["R_K"] = RHN_R_K(0);

    lnL_R_K.resolveDependency(&RHN_R_K);
    lnL_R_K.reset_and_calculate();
    results["lnL_R_K"] = lnL_R_K(0);
    results["LogLike"] += lnL_R_K(0);

    // R_tau
    RHN_R_tau.notifyOfModel("RightHandedNeutrinos");
    RHN_R_tau.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    RHN_R_tau.resolveDependency(&get_SMINPUTS);
    RHN_R_tau.resolveDependency(&CI_Theta);
    RHN_R_tau.reset_and_calculate();
    results["R_tau"] = RHN_R_tau(0);

    lnL_R_tau.resolveDependency(&RHN_R_tau);
    lnL_R_tau.reset_and_calculate();
    results["lnL_R_tau"] = lnL_R_tau(0);
    results["LogLike"] += lnL_R_tau(0);

    // R_W
    RHN_mw.resolveDependency(&CI_Theta);
    RHN_mw.resolveDependency(&RHN_sinW2_eff);
    RHN_mw.reset_and_calculate();

    RHN_W_to_l_decays.notifyOfModel("RightHandedNeutrinos");
    RHN_W_to_l_decays.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    RHN_W_to_l_decays.resolveDependency(&get_SMINPUTS);
    RHN_W_to_l_decays.resolveDependency(&CI_Theta);
    RHN_W_to_l_decays.resolveDependency(&RHN_mw);
    RHN_W_to_l_decays.reset_and_calculate();

    RHN_R_W.notifyOfModel("RightHandedNeutrinos");
    RHN_R_W.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    RHN_R_W.resolveDependency(&RHN_W_to_l_decays);
    RHN_R_W.reset_and_calculate();
    results["R_W(e)"] = RHN_R_W(0)[0];
    results["R_W(mu)"] = RHN_R_W(0)[1];
    results["R_W(tau)"] = RHN_R_W(0)[2];

    lnL_R_W.resolveDependency(&RHN_R_W);
    lnL_R_W.reset_and_calculate();
    results["lnL_R_W"] = lnL_R_W(0);
    results["LogLike"] += lnL_R_W(0);


    // ---- Calculate 0nubb constraints ----

    // KamLAND-Zen
    RHN_mbb_0nubb_Xe.notifyOfModel("RightHandedNeutrinos");
    RHN_mbb_0nubb_Xe.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    RHN_mbb_0nubb_Xe.resolveDependency(&M_nu);
    RHN_mbb_0nubb_Xe.resolveDependency(&UPMNS);
    RHN_mbb_0nubb_Xe.resolveDependency(&CI_Theta);
    RHN_mbb_0nubb_Xe.reset_and_calculate();
    results["RHN_mbb_0nubb_Xe"] = RHN_mbb_0nubb_Xe(0);

    lnL_mbb_0nubb_KamLAND_Zen.resolveDependency(&RHN_mbb_0nubb_Xe);
    lnL_mbb_0nubb_KamLAND_Zen.reset_and_calculate();
    results["lnL_mbb_0nubb_KamLAND_Zen"] = lnL_mbb_0nubb_KamLAND_Zen(0);
    results["LogLike"] += lnL_mbb_0nubb_KamLAND_Zen(0);

    // GERDA
    RHN_mbb_0nubb_Ge.notifyOfModel("RightHandedNeutrinos");
    RHN_mbb_0nubb_Ge.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    RHN_mbb_0nubb_Ge.resolveDependency(&M_nu);
    RHN_mbb_0nubb_Ge.resolveDependency(&UPMNS);
    RHN_mbb_0nubb_Ge.resolveDependency(&CI_Theta);
    RHN_mbb_0nubb_Ge.reset_and_calculate();
    results["RHN_mbb_0nubb_Ge"] = RHN_mbb_0nubb_Ge(0);

    lnL_mbb_0nubb_GERDA.resolveDependency(&RHN_mbb_0nubb_Ge);
    lnL_mbb_0nubb_GERDA.reset_and_calculate();
    results["lnL_mbb_0nubb_GERDA"] = lnL_mbb_0nubb_GERDA(0);
    results["LogLike"] += lnL_mbb_0nubb_GERDA(0);


    // ---- Calculate CKM constraints ----

    calc_Vus.notifyOfModel("RightHandedNeutrinos");
    calc_Vus.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    calc_Vus.resolveDependency(&get_SMINPUTS);
    calc_Vus.resolveDependency(&CI_Theta);
    calc_Vus.reset_and_calculate();
    results["Vus"] = calc_Vus(0);

    lnL_ckm_Vusmin.notifyOfModel("RightHandedNeutrinos");
    lnL_ckm_Vusmin.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_ckm_Vusmin.resolveDependency(&get_SMINPUTS);
    lnL_ckm_Vusmin.resolveDependency(&calc_Vus);
    lnL_ckm_Vusmin.resolveDependency(&CI_Theta);
    lnL_ckm_Vusmin.reset_and_calculate();
    results["lnL_ckm_Vusmin"] = lnL_ckm_Vusmin(0);
    results["LogLike"] += lnL_ckm_Vusmin(0);


    // ---- Calculate direct searches constraints ----

    // PiENu
    lnL_pienu.notifyOfModel("RightHandedNeutrinos");
    lnL_pienu.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_pienu.resolveDependency(&Ue1);
    lnL_pienu.resolveDependency(&Ue2);
    lnL_pienu.resolveDependency(&Ue3);
    lnL_pienu.reset_and_calculate();
    results["lnL_pienu"] = lnL_pienu(0);
    results["LogLike"] += lnL_pienu(0);

    // PS191 (e)
    lnL_ps191_e.notifyOfModel("RightHandedNeutrinos");
    lnL_ps191_e.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_ps191_e.resolveDependency(&Ue1);
    lnL_ps191_e.resolveDependency(&Ue2);
    lnL_ps191_e.resolveDependency(&Ue3);
    lnL_ps191_e.resolveDependency(&Um1);
    lnL_ps191_e.resolveDependency(&Um2);
    lnL_ps191_e.resolveDependency(&Um3);
    lnL_ps191_e.resolveDependency(&Ut1);
    lnL_ps191_e.resolveDependency(&Ut2);
    lnL_ps191_e.resolveDependency(&Ut3);
    lnL_ps191_e.reset_and_calculate();
    results["lnL_ps191_e"] = lnL_ps191_e(0);
    results["LogLike"] += lnL_ps191_e(0);

    // PS191 (mu)
    lnL_ps191_mu.notifyOfModel("RightHandedNeutrinos");
    lnL_ps191_mu.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_ps191_mu.resolveDependency(&Ue1);
    lnL_ps191_mu.resolveDependency(&Ue2);
    lnL_ps191_mu.resolveDependency(&Ue3);
    lnL_ps191_mu.resolveDependency(&Um1);
    lnL_ps191_mu.resolveDependency(&Um2);
    lnL_ps191_mu.resolveDependency(&Um3);
    lnL_ps191_mu.resolveDependency(&Ut1);
    lnL_ps191_mu.resolveDependency(&Ut2);
    lnL_ps191_mu.resolveDependency(&Ut3);
    lnL_ps191_mu.reset_and_calculate();
    results["lnL_ps191_mu"] = lnL_ps191_mu(0);
    results["LogLike"] += lnL_ps191_mu(0);

    // CHARM (e)
    lnL_charm_e.notifyOfModel("RightHandedNeutrinos");
    lnL_charm_e.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_charm_e.resolveDependency(&Ue1);
    lnL_charm_e.resolveDependency(&Ue2);
    lnL_charm_e.resolveDependency(&Ue3);
    lnL_charm_e.resolveDependency(&Um1);
    lnL_charm_e.resolveDependency(&Um2);
    lnL_charm_e.resolveDependency(&Um3);
    lnL_charm_e.resolveDependency(&Ut1);
    lnL_charm_e.resolveDependency(&Ut2);
    lnL_charm_e.resolveDependency(&Ut3);
    lnL_charm_e.reset_and_calculate();
    results["lnL_charm_e"] = lnL_charm_e(0);
    results["LogLike"] += lnL_charm_e(0);

    // CHARM (mu)
    lnL_charm_mu.notifyOfModel("RightHandedNeutrinos");
    lnL_charm_mu.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_charm_mu.resolveDependency(&Ue1);
    lnL_charm_mu.resolveDependency(&Ue2);
    lnL_charm_mu.resolveDependency(&Ue3);
    lnL_charm_mu.resolveDependency(&Um1);
    lnL_charm_mu.resolveDependency(&Um2);
    lnL_charm_mu.resolveDependency(&Um3);
    lnL_charm_mu.resolveDependency(&Ut1);
    lnL_charm_mu.resolveDependency(&Ut2);
    lnL_charm_mu.resolveDependency(&Ut3);
    lnL_charm_mu.reset_and_calculate();
    results["lnL_charn_mu"] = lnL_charm_mu(0);
    results["LogLike"] += lnL_charm_mu(0);

    // CHARM (tau)
    lnL_charm_tau.notifyOfModel("RightHandedNeutrinos");
    lnL_charm_tau.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_charm_tau.resolveDependency(&Ut1);
    lnL_charm_tau.resolveDependency(&Ut2);
    lnL_charm_tau.resolveDependency(&Ut3);
    lnL_charm_tau.reset_and_calculate();
    results["lnL_charm_tau"] = lnL_charm_tau(0);
    results["LogLike"] += lnL_charm_tau(0);

    // DELPHI (short lived)
    lnL_delphi_short_lived.notifyOfModel("RightHandedNeutrinos");
    lnL_delphi_short_lived.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_delphi_short_lived.resolveDependency(&Ue1);
    lnL_delphi_short_lived.resolveDependency(&Ue2);
    lnL_delphi_short_lived.resolveDependency(&Ue3);
    lnL_delphi_short_lived.resolveDependency(&Um1);
    lnL_delphi_short_lived.resolveDependency(&Um2);
    lnL_delphi_short_lived.resolveDependency(&Um3);
    lnL_delphi_short_lived.resolveDependency(&Ut1);
    lnL_delphi_short_lived.resolveDependency(&Ut2);
    lnL_delphi_short_lived.resolveDependency(&Ut3);
    lnL_delphi_short_lived.reset_and_calculate();
    results["lnL_delphi_short_lived"] = lnL_delphi_short_lived(0);
    results["LogLike"] += lnL_delphi_short_lived(0);

    // DELPHI (long lived)
    lnL_delphi_long_lived.notifyOfModel("RightHandedNeutrinos");
    lnL_delphi_long_lived.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_delphi_long_lived.resolveDependency(&Ue1);
    lnL_delphi_long_lived.resolveDependency(&Ue2);
    lnL_delphi_long_lived.resolveDependency(&Ue3);
    lnL_delphi_long_lived.resolveDependency(&Um1);
    lnL_delphi_long_lived.resolveDependency(&Um2);
    lnL_delphi_long_lived.resolveDependency(&Um3);
    lnL_delphi_long_lived.resolveDependency(&Ut1);
    lnL_delphi_long_lived.resolveDependency(&Ut2);
    lnL_delphi_long_lived.resolveDependency(&Ut3);
    lnL_delphi_long_lived.reset_and_calculate();
    results["lnL_delphi_long_lived"] = lnL_delphi_long_lived(0);
    results["LogLike"] += lnL_delphi_long_lived(0);

    // ATLAS (e)
    lnL_atlas_e.notifyOfModel("RightHandedNeutrinos");
    lnL_atlas_e.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_atlas_e.resolveDependency(&Ue1);
    lnL_atlas_e.resolveDependency(&Ue2);
    lnL_atlas_e.resolveDependency(&Ue3);
    lnL_atlas_e.reset_and_calculate();
    results["lnL_atlas_e"] = lnL_atlas_e(0);
    results["LogLike"] += lnL_atlas_e(0);

    // ATLAS (mu)
    lnL_atlas_mu.notifyOfModel("RightHandedNeutrinos");
    lnL_atlas_mu.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_atlas_mu.resolveDependency(&Um1);
    lnL_atlas_mu.resolveDependency(&Um2);
    lnL_atlas_mu.resolveDependency(&Um3);
    lnL_atlas_mu.reset_and_calculate();
    results["lnL_altas_mu"] = lnL_atlas_mu(0);
    results["LogLike"] += lnL_atlas_mu(0);

    // E949
    lnL_e949.notifyOfModel("RightHandedNeutrinos");
    lnL_e949.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_e949.resolveDependency(&Um1);
    lnL_e949.resolveDependency(&Um2);
    lnL_e949.resolveDependency(&Um3);
    lnL_e949.reset_and_calculate();
    results["lnL_e949"] = lnL_e949(0);
    results["LogLike"] += lnL_e949(0);

    // NuTeV
    lnL_nutev.notifyOfModel("RightHandedNeutrinos");
    lnL_nutev.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_nutev.resolveDependency(&Um1);
    lnL_nutev.resolveDependency(&Um2);
    lnL_nutev.resolveDependency(&Um3);
    lnL_nutev.reset_and_calculate();
    results["lnL_nutev"] = lnL_nutev(0);
    results["LogLike"] += lnL_nutev(0);

    // CMS (e)
    lnL_lhc_e.notifyOfModel("RightHandedNeutrinos");
    lnL_lhc_e.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_lhc_e.resolveDependency(&Ue1);
    lnL_lhc_e.resolveDependency(&Ue2);
    lnL_lhc_e.resolveDependency(&Ue3);
    lnL_lhc_e.reset_and_calculate();
    results["lnL_lhc_e"] = lnL_lhc_e(0);
    results["LogLike"] += lnL_lhc_e(0);

    // CMS (mu)
    lnL_lhc_mu.notifyOfModel("RightHandedNeutrinos");
    lnL_lhc_mu.resolveDependency(&Models::RightHandedNeutrinos::Functown::primary_parameters);
    lnL_lhc_mu.resolveDependency(&Um1);
    lnL_lhc_mu.resolveDependency(&Um2);
    lnL_lhc_mu.resolveDependency(&Um3);
    lnL_lhc_mu.reset_and_calculate();
    results["lnL_lhc_mu"] = lnL_lhc_mu(0);
    results["LogLike"] += lnL_lhc_mu(0);

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
    std::cout << "NeutrinoBit_standalone_RHN has exited with fatal exception: " << e.what() << std::endl;
  }

  return 0;


}

