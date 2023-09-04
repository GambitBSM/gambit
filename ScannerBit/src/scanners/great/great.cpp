//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface to GreAT 1.0.0
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Antje Putze
///          (putze@lapth.cnrs.fr)
///  \date 2015 Nov
///  \date 2016 Apr
///
///  *********************************************

#include <vector>
#include <limits>
#include <cstdio>

#include "gambit/ScannerBit/scanners/great/great.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/variadic_functions.hpp"
#include "gambit/Utils/mpiwrapper.hpp"

#include "TGreatModel.h"
#include "TGreatManager.h"
#include "TGreatMCMCAlgorithmCovariance.h"


// Set up the global scan data container
namespace Gambit
{
  namespace GreAT
  {
    greatScanData data;
  }
}


/// =================================================
/// Interface to ScannerBit
/// =================================================

scanner_plugin(great, version(1, 0, 0))
{
  // Access standard Gambit things
  using namespace Gambit;
  using namespace Gambit::Scanner;

  //  const static PriorTransform prior;

  // Error thrown if the following entries are not present in the inifile
  reqd_inifile_entries(); // None at the momement. Might need some later.

  // Tell CMake to search for the GreAT library.
  reqd_libraries("great");
  reqd_headers("fparser.hh", "TGreatModel.h", "TGreatManager.h", "TGreatMCMCAlgorithmCovariance.h", "ROOT");

  // Code to execute when the plugin is loaded.
  plugin_constructor
  {
    const int  MPIrank = get_printer().get_stream()->getRank();
    if (MPIrank == 0) std::cout << "\033[1;31mLoading GreAT plugin for ScannerBit.\033[0m" << std::endl;
    // Retrieve the external likelihood calculator
    GreAT::data.likelihood_function = get_purpose(get_inifile_value<std::string>("like"));
    // Retrieve the external printer
    GreAT::data.printer = &(get_printer());
  }

  int plugin_main(void)
  {

    // Run parameters
    const int  nPar         = get_dimension();                            // Dimensionality of the parameter space
    const int  nTrialLists  = get_inifile_value<int> ("nTrialLists", 10); // Number of trial lists (e.g. Markov chains)
    const int  nTrials      = get_inifile_value<int> ("nTrials",  20000); // Number of trials (e.g. Markov steps)
    const int  MPIrank      = get_printer().get_stream()->getRank();      // MPI rank of this process
    const bool resume_mode  = get_printer().resume_mode();                // Resuming run or not
    const str  outpath      = Gambit::Utils::ensure_path_exists(get_inifile_value<std::string>("default_output_path")+"GreAT-native/");
    GreAT::data.min_logLike = get_inifile_value<double>("likelihood: model_invalid_for_lnlike_below");

    // Set up output and MultiRun log filenames
    std::ostringstream ss1, ss2, ss3;
    ss1 << outpath << "MCMC_" << MPIrank << ".root";
    ss2 << outpath << "MultiRun.txt";
    ss3 << outpath << "MultiRun.txt.lock";
    std::string outputfilename = ss1.str();
    std::string multifilename = ss2.str();
    std::string lockfilename = ss3.str();

    if (resume_mode and MPIrank == 0)
    {
      // Clear GreAT lock file
      remove(lockfilename.c_str());
    }
    else
    {
      // Wipe entire previous GreAT output if not resuming
      Utils::remove_all_files_in(outpath);
    }
    #ifdef WITH_MPI
      GMPI::Comm mpi;
      mpi.Barrier();
    #endif

    // Creating GreAT Model, i.e. parameter space and function to be minimised.
    // This is new'd because a TGreATManager later takes ownership of it and deletes it internally.
    TGreatModel* MyModel = new TGreatModel();

    // Setting up the hypercube parameter space
    // MyModel->AddParameter(std::string name, std::string unit, double start_value, double min_value, double max_value);
    std::string x = "";
    for(int i = 0; i < nPar; i++)
    {
      x = "x" + std::to_string(i+1);
      MyModel->AddParameter(x, "", 0.5, 0., 1.);
    }

    // Setting up the logarithmic likelihoodfunction
    MyModel->SetLogLikelihoodFunction(GreAT::LogLikelihoodFunction);

    // Setting up the GreAT Manager
    if (MPIrank == 0) std::cout << "\033[1;31mCreating GreAT Manager\033[0m" << std::endl;
    // TGreatManager<typename T> MyManager(TGreatModel*);
    // Using here a multivariate Gaussian distribution (TGreatMCMCAlgorithmCovariance)
    TGreatManager<TGreatMCMCAlgorithmCovariance> MyManager(MyModel);
    // Tell the algorithm to use former points to update its prior
    MyManager.GetAlgorithm()->SetUpdateStatus(true);
    // Set the output path, file name, and name for the TTree
    MyManager.SetOutputFileName(outputfilename);
    MyManager.SetTreeName("mcmc");
    // Set number of trials (steps) and triallists (chains)
    MyManager.SetNTrialLists(nTrialLists);
    MyManager.SetNTrials(nTrials);
    // Run GreAT
    if (MPIrank == 0) std::cout << "\033[1;31mRunning GreAT...\033[0m" << std::endl;
    //MyManager.ActivateMultiRun(multifilename.c_str());
    MyManager.Run();

    // Analyse
    // 1) Fetch the ROOT file
    TFile *file;
    file = TFile::Open(MyManager.GetOutputFileName().c_str());
    TTree *mcmc = (TTree *) file->Get("mcmc");

    // 2) Define the estimator
    // TGreatEstimator<typename T>(TTree*)
    TGreatEstimator<TGreatMCMCAlgorithmCovariance> estimator(mcmc);
    // Show the scan statistics
    estimator.ShowStatistics();

    // Setup auxilliary stream. It is only needed by the master process
    if(MPIrank == 0)
    {
      Gambit::Options ind_samples_options;// = get_inifile_node("aux_printer_ind_samples_options");

      // Options to desynchronise print streams from the main Gambit iterations. This allows for random access writing, or writing of global scan data.
      ind_samples_options.setValue("synchronised", false);

      if (MPIrank == 0) std::cout << "\033[1;31mWriting points...\033[0m" << std::endl;
      // Initialise auxiliary print stream
      GreAT::data.printer->new_stream("ind_samples", ind_samples_options);

      Scanner::printer* ind_samples_printer(GreAT::data.printer->get_stream("ind_samples"));
      static const int MPIrank = GreAT::data.likelihood_function->getRank();

      TGreatMCMCSample *prev_sample = estimator.GetFirstIndSample();
      unsigned int multiplicity = 0;

      for(TGreatMCMCSample *sample = prev_sample; sample != 0; sample = estimator.GetNextIndSample())
      {
        // count samples to get their posterior weight and save them
        if(prev_sample->GetID() == sample->GetID())
          ++multiplicity;
        else
        {
          ind_samples_printer->print(multiplicity, "multiplicity", MPIrank, prev_sample->GetID());
          ind_samples_printer->print(prev_sample->GetID(), "Point ID", MPIrank, prev_sample->GetID());
          prev_sample = sample;
          multiplicity = 1;
        }
      }
      // Save the last point
      ind_samples_printer->print(multiplicity, "multiplicity", MPIrank, prev_sample->GetID());
      ind_samples_printer->print(prev_sample->GetID(), "Point ID", MPIrank, prev_sample->GetID());

      // Finish.
      std::cout << "\033[1;31mGreAT finished successfully!\033[0m" << std::endl;
    }

    return 0;
  }
}

namespace Gambit
{
  namespace GreAT
  {
    double LogLikelihoodFunction(TGreatPoint& point)
    {
      // check if point is within the unit cube
      std::vector<double> parameter_vector = point.GetPoint();

      bool outside = false;
      for (unsigned int i=0;i<parameter_vector.size();i++)
      {
        if (parameter_vector[i]<0 || parameter_vector[i]>1)
        {
          outside = true;
        }
      }

      if (outside)
      {
        // at least one dimension is outside the unit cube so return -1e100 for LogLike
        return GreAT::data.min_logLike;
      }
      else
      {
        point.SetID(GreAT::data.likelihood_function->getNextPtID()); // Need to use the *next* PtID because PtID will not move on until the likelihood function is called.
        return GreAT::data.likelihood_function(parameter_vector);
      }
    }
  }
}
