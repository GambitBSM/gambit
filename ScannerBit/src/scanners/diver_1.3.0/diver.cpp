//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface to Diver 1.3.0
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patrickcolinscott@gmail.com)
///  \date 2025 Apr
///
///  *********************************************

#include <vector>
#include <limits>
#include <fstream>

#include "gambit/ScannerBit/scanners/diver_1.3.0/diver.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/variadic_functions.hpp"

/// =================================================
/// Interface to ScannerBit
/// =================================================

scanner_plugin(diver, version(1, 3, 0))
{

  // Access Diver stuff and standard Gambit things
  using namespace Gambit;
  using namespace Gambit::Diver_1_3_0;

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
    size_t nPar                = get_dimension();                                         // Dimensionality of the parameter space
    size_t nDerived            =                                                 0;       // Number of derived quantities to output (GAMBIT printers handle these).
    size_t nDiscrete           = get_inifile_value<int>   ("nDiscrete",          0);      // Number of parameters that are to be treated as discrete
    bool   partitionDiscrete   = get_inifile_value<bool>  ("partitionDiscrete",  false);  // Split the population evenly amongst discrete parameters and evolve separately
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
    int    savecount           = get_inifile_value<int>   ("savecount",          1);      // Save progress every savecount generations
    bool   disableIO           = get_inifile_value<bool>  ("disableIO", false);           // Disable all IO (overrides outputRaw and outputSam if true)
    bool   outputRaw           = get_inifile_value<bool>  ("outputRaw", true);            // Output .raw file (Diver native sample output format)
    bool   outputSam           = get_inifile_value<bool>  ("outputSam", true);            // Output .sam file (rounded and derived parameter samples)
    int    init_pop_strategy   = get_inifile_value<int>   ("init_population_strategy", 2);// Initialisation strategy: 0=one shot, 1=n-shot, 2=n-shot with error if no valid vectors found.
    bool   discard_unfit_points= get_inifile_value<bool>  ("discard_unfit_points", false);// Recalculate any trial vector whose fitness is above max_acceptable_value
    int    max_ini_attempts    = get_inifile_value<int>   ("max_initialisation_attempts", 10000); // Maximum number of times to try to find a valid vector for each slot in the initial population.
    double max_acceptable_value= get_inifile_value<double>("max_acceptable_value",0.9999*gl0); // Maximum function value to accept for the initial gen if init_population_strategy > 0, or any gen if discard_unfit_points=T.
    int    verbose             = get_inifile_value<int>   ("verbosity",          0);      // Output verbosity: 0=only error messages, 1=basic info, 2+=population info
    int    seed                = get_inifile_value<int>   ("seed",               -1);     // Base seed for random number generation; non-positive means seed from the system clock
    void*  context             = &data;                                                   // Pointer to GAMBIT likelihood function and printers, passed through to objective function.

    // Copy the contents of root to a char array.
    std::vector<char> path(root.length()+1);
    strcpy(&path[0], root.c_str());

    // Unit cube boundaries
    std::vector<double> lowerbounds(nPar, 0.0);                                                             // Lower boundaries of parameter space to scan
    std::vector<double> upperbounds(nPar, 1.0);                                                             // Upper boundaries of parameter space to scan

    // Containers for returned best-fit parameters and derived quantities (not used)
    std::vector<double> bestFitParams(nPar);                                                                // Placeholder for returned parameters at best-fit point
    double bestFitDerived[] = {0};                                                                          // Placeholder for returned derived quantities at best-fit point

    // Scale factors
    std::vector<double> Fvec = get_inifile_value<std::vector<double> >("F", initVector<double>(0.7));
    size_t nF = Fvec.size();                                                                                // Size of the array indicating scale factors

    // Discrete parameters. TODO Needs to be set automatically somehow?  Not yet sure how to deal with discrete parameters in GAMBIT.
    std::vector<int> discrete(nDiscrete, 0);                                                                // Indices of discrete parameters, Fortran style, i.e. starting at 1!!

    // Initial guesses.
    size_t nGuesses = 0;
    std::vector<double> initial_guesses = {0};
    const YAML::Node initial_guesses_node = get_inifile_node("initial_guesses");
    if (initial_guesses_node)
    {
      // Make sure the parameter names and values are both present
      if (!initial_guesses_node["parameters"] or !initial_guesses_node["values"])
      {
        scan_err << "Diver \"initial_guesses\" option requires both \"parameters\" and \"values\"." << scan_end;
      }
      std::vector<std::string> ig_parnames = initial_guesses_node["parameters"].as<std::vector<std::string>>();
      std::vector<std::vector<double>> ig_values = initial_guesses_node["values"].as<std::vector<std::vector<double>>>();

      // Make sure the parameter names all match up to ones being scanned.
      const std::vector<std::string> valid_parameters = data.likelihood_function->getPrior().getSetParameters();
      for (auto parname : ig_parnames)
      {
        if (not std::count(valid_parameters.begin(), valid_parameters.end(), parname))
        {
          scan_err << "Parameter " << parname << " specified in \"initial_guesses\" is not one of the following being scanned over:"
          << endl << "  " << valid_parameters << scan_end;
        }
      }

      // Determine the total number of guesses, and therefore the size of the array that needs to be passed to Diver
      nGuesses = ig_values.size();
      initial_guesses = std::vector<double>(nPar*nGuesses);

      // Make sure the number of stated parameters matches the number of free ones in the scan
      if (ig_parnames.size() != nPar) scan_err << "Initial guess \"parameters\" field contains " << ig_parnames.size() << " parameters, but the scan is over " << nPar << "." << scan_end;

      // Convert each guess to the unit hypercube
      for (size_t i = 0; i < nGuesses; i++)
      {
        const std::vector<double>& guess = ig_values[i];
        // Make sure the number of guessed parameters matches the number of free ones in the scan
        if (guess.size() != nPar) scan_err << "Initial guess contains " << guess.size() << " parameters; expected " << nPar << ".\n Guess: " << guess << scan_end;
        // Construct the guess as a map from parameters to values
        std::unordered_map<std::string, double> parmap;
        std::transform(ig_parnames.begin(), ig_parnames.end(), guess.begin(), std::inserter(parmap, parmap.end() ), std::make_pair<const std::string&, const double&>);
        // For each physical guess, save its correctly-ordered equivalent in the hypercube
        size_t j = 0;
        for (const double& par : data.likelihood_function->inverse_transform(parmap))
        {
          // Initial guesses is read inside Diver as a C++ 2D array with first index the parameter, second the individual.
          initial_guesses[j*nGuesses + i] = par;
          j++;
        }
      }
    }

    // Run Diver
    if (data.likelihood_function->getRank() == 0) cout << "Starting Diver run..." << std::endl;
    cdiver(&objective, nPar, &lowerbounds[0], &upperbounds[0], &path[0], nDerived, &bestFitParams[0],
           bestFitDerived, nDiscrete, &discrete[0], partitionDiscrete, maxgen, NP, nF, &Fvec[0], Cr,
           lambda, current, expon, bndry, jDE, lambdajDE, convthresh, convsteps, removeDuplicates,
           savecount, resume, disableIO, outputRaw, outputSam, init_pop_strategy, nGuesses, &initial_guesses[0],
           discard_unfit_points, max_ini_attempts, max_acceptable_value, seed, context, verbose);
    if (data.likelihood_function->getRank() == 0) cout << "Diver run finished!" << std::endl;
    return 0;

  }

}

/// =================================================
/// Function definitions
/// =================================================

namespace Gambit
{

  namespace Diver_1_3_0
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

