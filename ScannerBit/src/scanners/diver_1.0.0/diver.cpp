//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface to Diver 1.0.0
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 June
///
///  *********************************************

#include <vector>
#include <limits>
#include <fstream>

#include "gambit/ScannerBit/scanners/diver/1.0.0/diver.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/variadic_functions.hpp"

/// =================================================
/// Interface to ScannerBit
/// =================================================

scanner_plugin(diver, version(1, 0, 0))
{

  // Access Diver stuff and standard Gambit things
  using namespace Gambit;
  using namespace Gambit::Diver_1_0_0;

  // Error thrown if the following entries are not present in the inifile
  reqd_inifile_entries("NP");

  // Tell cmake to search for the diver library.
  reqd_libraries("diver");

  // Set up the scan data container
  diverScanData data;

  // Code to execute when the plugin is loaded.
  plugin_constructor
  {
    // Retrieve the external likelihood calculator
    data.likelihood_function = get_purpose(get_inifile_value<std::string>("like"));
    if (data.likelihood_function->getRank() == 0) cout << "Loading Diver differential evolution plugin for ScannerBit." << std::endl;
    // Retrieve the external printer
    data.printer = &(get_printer());
    // Do not allow GAMBIT's own likelihood calculator to directly shut down the scan.
    // Diver will assume responsibility for this process, triggered externally by
    // the 'plugin_info.early_shutdown_in_progress()' function.
    data.likelihood_function->disable_external_shutdown();
  }

  int plugin_main (void)
  {
    // Path to save Diver samples, resume files, etc
    str defpath = get_inifile_value<str>("default_output_path");
    str root = Utils::ensure_path_exists(get_inifile_value<str>("path",defpath+"Diver/native"));

    // Ask the printer if this is a resumed run or not, and check that the necessary files exist if so.
    bool resume = get_printer().resume_mode();
    if (resume)
    {
      bool good = true;
      static const std::vector<str> names = initVector<str>(root+".rparam", root+".devo", root+".raw");
      for (auto it = names.begin(); it != names.end(); ++it)
      {
        std::ifstream file(*it);
        good = good and file.good() and (file.peek() != std::ifstream::traits_type::eof());
        file.close();
      }
      if (not good)
      {
        std::ostringstream warning;
        warning << "Cannot resume previous Diver run because one or all of" << endl;
        for (auto it = names.begin(); it != names.end(); ++it) warning << " " << *it << endl;
        warning << "is missing or empty.  This is probably because your last run didn't " << endl
                << "complete even one generation. Diver will start from scratch, " << endl
                << "as if you had specified -r.";
        if (data.likelihood_function->getRank() == 0) cout << "WARNING: " << warning.str() << endl;
        scan_warn << warning.str() << scan_end;
        resume = false;
      }
    }

    // Retrieve the global option specifying the minimum interesting likelihood.
    double gl0 = get_inifile_value<double>("likelihood: model_invalid_for_lnlike_below");
    // Retrieve the global option specifying the likelihood offset to use
    double offset = get_inifile_value<double>("likelihood: lnlike_offset", 1e-4*gl0);
    // Make sure the likleihood functor knows to apply the offset internally in ScannerBit
    data.likelihood_function->setPurposeOffset(offset);
    // Offset the minimum interesting likelihood by the offset, and flip it to match diver sign convention.
    gl0 = -1.0 * (gl0 + offset);

    // Other Diver run parameters
    int    nPar                = get_dimension();                                         // Dimensionality of the parameter space
    int    nDerived            =                                                 0;       // Number of derived quantities to output (GAMBIT printers handle these).
    int    nDiscrete           = get_inifile_value<int>   ("nDiscrete",          0);      // Number of parameters that are to be treated as discrete
    bool   partitionDiscrete   = get_inifile_value<bool>  ("partitionDiscrete",  false);  // Split the population evenly amongst discrete parameters and evolve separately
    int    maxciv              = get_inifile_value<int>   ("maxciv",             1);      // Maximum number of civilisations
    int    maxgen              = get_inifile_value<int>   ("maxgen",             5000);   // Maximum number of generations per civilisation
    int    NP                  = get_inifile_value<int>   ("NP");                         // Population size (individuals per generation)
    double Cr                  = get_inifile_value<double>("Cr",                 0.9);    // Crossover factor
    double lambda              = get_inifile_value<double>("lambda",             0.0);    // Mixing factor between best and rand/current
    bool   current             = get_inifile_value<bool>  ("current",            false);  // Use current vector for mutation
    bool   expon               = get_inifile_value<bool>  ("expon",              false);  // Use exponential crossover
    int    bndry               = get_inifile_value<int>   ("bndry",              3);      // Boundary constraint: 1=brick wall, 2=random re-initialization, 3=reflection
    bool   jDE                 = get_inifile_value<bool>  ("jDE",                true);   // Use self-adaptive choices for rand/1/bin parameters as per Brest et al 2006
    bool   lambdajDE           = get_inifile_value<bool>  ("lambdajDE",          true);   // Use self-adaptive rand-to-best/1/bin parameters; based on Brest et al 2006
    double convthresh          = get_inifile_value<double>("convthresh",         1.e-3);  // Threshold for gen-level convergence: smoothed fractional improvement in the mean population value
    int    convsteps           = get_inifile_value<int>   ("convsteps",          10);     // Number of steps to smooth over when checking convergence
    bool   removeDuplicates    = get_inifile_value<bool>  ("removeDuplicates",   true);   // Weed out duplicate vectors within a single generation
    bool   doBayesian          =                                                 false;   // Calculate approximate log evidence and posterior weightings
    double maxNodePop          =                                                 1.9;     // Population at which node is partitioned in binary space partitioning for posterior
    double Ztolerance          =                                                 0.01;    // Input tolerance in log-evidence
    int    savecount           = get_inifile_value<int>   ("savecount",          1);      // Save progress every savecount generations
    bool   native_output       = get_inifile_value<bool>  ("full_native_output", true);   // Output .raw file (Diver native sample output format)
    int    init_pop_strategy   = get_inifile_value<int>   ("init_population_strategy", 2);// Initialisation strategy: 0=one shot, 1=n-shot, 2=n-shot with error if no valid vectors found.
    int    max_ini_attempts    = get_inifile_value<int>   ("max_initialisation_attempts", 10000); // Maximum number of times to try to find a valid vector for each slot in the initial population.
    double max_acceptable_value= get_inifile_value<double>("max_acceptable_value",0.9999*gl0); // Maximum function value to accept for the initial generation if init_population_strategy > 0.
    int    verbose             = get_inifile_value<int>   ("verbosity",          0);      // Output verbosity: 0=only error messages, 1=basic info, 2=civ-level info, 3+=population info
    double (*prior)(const double[], const int, void*&) =                         NULL;    // Pointer to prior function, only used if doBayesian = true.
    void*  context             = &data;                                                   // Pointer to GAMBIT likelihood function and printers, passed through to objective function.

    // Copy the contents of root to a char array.
    char path[root.length()+1];
    strcpy(path, root.c_str());

    // Unit cube boundaries
    double lowerbounds[nPar];                                                             // Lower boundaries of parameter space to scan
    double upperbounds[nPar];                                                             // Upper boundaries of parameter space to scan
    for (int i = 0; i < nPar; i++)
    {
      lowerbounds[i] = 0.0;
      upperbounds[i] = 1.0;
    }

    // Scale factors
    std::vector<double> Fvec = get_inifile_value<std::vector<double> >("F", initVector<double>(0.7));
    int nF = Fvec.size();                                                                 // Size of the array indicating scale factors
    double F[nF];                                                                         // Scale factor(s).
    std::copy(Fvec.begin(), Fvec.end(), F);

    // Discrete parameters
    int discrete[nDiscrete];                                                              // Indices of discrete parameters, Fortran style, i.e. starting at 1!!
    for (int i = 0; i < nDiscrete; i++)
    {
      discrete[i] = 0; //TODO Needs to be set automatically somehow?  Not yet sure how to deal with discrete parameters in GAMBIT.
    }

    // Run Diver
    if (data.likelihood_function->getRank() == 0) cout << "Starting Diver run..." << std::endl;
    cdiver(&objective, nPar, lowerbounds, upperbounds, path, nDerived, nDiscrete,
           discrete, partitionDiscrete, maxciv, maxgen, NP, nF, F, Cr, lambda, current,
           expon, bndry, jDE, lambdajDE, convthresh, convsteps, removeDuplicates, doBayesian,
           prior, maxNodePop, Ztolerance, savecount, resume, native_output, init_pop_strategy,
           max_ini_attempts, max_acceptable_value, context, verbose);
    if (data.likelihood_function->getRank() == 0) cout << "Diver run finished!" << std::endl;
    return 0;

  }

}

/// =================================================
/// Function definitions
/// =================================================

namespace Gambit
{

  namespace Diver_1_0_0
  {

    //Function to be minimized.  Corresponds to -ln(Likelihood).  Redirects to the target of context pointer.
    double objective(double params[], const int param_dim, int &fcall, bool &quit, const bool validvector, void*& context)
    {
      // Return the worst possible likelihood if the point is outside the prior box.
      if (not validvector) return std::numeric_limits<double>::max();

      // Put the parameters into a C++ vector
      std::vector<double> param_vec(params, params + param_dim);

      // Retrieve the likelihood function from the context pointer and call it
      diverScanData* data = static_cast<diverScanData*>(context);
      double lnlike = data->likelihood_function(param_vec);

      // Increment the number of function calls, tell Diver to continue and return the likelihood
      fcall += 1;

      // Check whether the calling code wants us to shut down early
      quit = Gambit::Scanner::Plugins::plugin_info.early_shutdown_in_progress();

      return -lnlike;

    }

  }

}

