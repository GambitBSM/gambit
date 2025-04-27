//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  j-Swarm: particle swarm optimisation with
///  meta-optimisation a la jDE.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2019 Oct
///
///  *********************************************

#include <vector>
#include "gambit/ScannerBit/scanners/jswarm/jswarm.hpp"

scanner_plugin(jswarm, version(1, 0, 0))
{

  // Access jswarm stuff and standard Gambit things
  using namespace Gambit;
  using namespace Gambit::jswarm_1_0_0;

  // Error thrown if the following entries are not present in the inifile
  reqd_inifile_entries("NP");

  // Make a new particle swarm
  particle_swarm swarm;

  // Code to execute when the plugin is loaded.
  plugin_constructor
  {
    // Retrieve the external likelihood calculator
    swarm.likelihood_function = get_purpose(get_inifile_value<std::string>("like"));
    if (swarm.likelihood_function->getRank() == 0) cout << "Loading j-Swarm plugin for ScannerBit." << std::endl;
    // Retrieve the external printer
    swarm.printer = &(get_printer());
    // Do not allow GAMBIT's own likelihood calculator to directly shut down the scan.
    // j-Swarm will assume responsibility for this process, triggered externally by
    // the 'plugin_info.early_shutdown_in_progress()' function.
    swarm.likelihood_function->disable_external_shutdown();
  }

  int plugin_main (void)
  {
    // Path to save j-Swarm samples, resume files, etc
    str defpath = get_inifile_value<str>("default_output_path");
    str root = Utils::ensure_path_exists(get_inifile_value<str>("path",defpath+"j-Swarm/native"));
    swarm.path = root;

    // Ask the printer if this is a resumed run or not, and check that the necessary files exist if so.
    bool resume = get_printer().resume_mode();
    if (resume)
    {
      bool good = true;
      static const std::vector<str> names = initVector<str>(root+".settings.yaml", root+".lastgen");
      for (auto it = names.begin(); it != names.end(); ++it)
      {
        std::ifstream file(*it);
        good = good and file.good() and (file.peek() != std::ifstream::traits_type::eof());
        file.close();
      }
      if (not good)
      {
        std::ostringstream warning;
        warning << "Cannot resume previous j-Swarm run because one or all of" << endl;
        for (auto it = names.begin(); it != names.end(); ++it) warning << " " << *it << endl;
        warning << "is missing or empty.  This is probably because your last run didn't " << endl
                << "complete even one generation. j-Swarm will start from scratch, " << endl
                << "as if you had specified -r.";
        if (swarm.likelihood_function->getRank() == 0) cout << "WARNING: " << warning.str() << endl;
        scan_warn << warning.str() << scan_end;
        resume = false;
      }
    }
    swarm.resume = resume;

    // Retrieve the global option specifying the minimum interesting likelihood.
    double gl0 = get_inifile_value<double>("likelihood: model_invalid_for_lnlike_below");
    // Retrieve the global option specifying the likelihood offset to use
    double offset = get_inifile_value<double>("likelihood: lnlike_offset", 1e-4*gl0);
    // Make sure the likleihood functor knows to apply the offset internally in ScannerBit
    swarm.likelihood_function->setPurposeOffset(offset);
    // Offset the minimum interesting likelihood by the offset.
    gl0 = gl0 + offset;

    // Other j-Swarm run parameters
    swarm.nPar                = get_dimension();                                         // Dimensionality of the parameter space
    swarm.nDerived            =                                                 0;       // Number of derived quantities to output (GAMBIT printers handle these).
    swarm.nDiscrete           = get_inifile_value<int>   ("nDiscrete",          0);      // Number of parameters that are to be treated as discrete
    swarm.maxgen              = get_inifile_value<int>   ("maxgen",             5000);   // Maximum number of generations
    swarm.NP                  = get_inifile_value<int>   ("NP");                         // Population size (individuals per generation)
    swarm.omega               = get_inifile_value<double>("omega",              0.7298); // Inertial weight (default is Constriction Coefficient PSO)
    swarm.phi1                = get_inifile_value<double>("phi1",               1.5);    // Cognitive weight (default is Constriction Coefficient PSO)
    swarm.phi2                = get_inifile_value<double>("phi2",               1.5);    // Social weight (default is Constriction Coefficient PSO)
    swarm.bndry               = get_inifile_value<int>   ("bndry",              3);      // Boundary constraint: 1=brick wall, 2=random re-initialization, 3=reflection
    swarm.adapt_phi           = get_inifile_value<bool>  ("adaptive_phi",       false);  // Use self-optimising adaptive choices for phi1 and phi2
    swarm.adapt_omega         = get_inifile_value<bool>  ("adaptive_omega",     false);  // Use self-optimising adaptive choices for omega
    swarm.convthresh          = get_inifile_value<double>("convthresh",         1.e-3);  // Threshold for gen-level convergence: smoothed fractional improvement in the mean personal best population value
    swarm.convsteps           = get_inifile_value<int>   ("convsteps",          10);     // Number of steps to smooth over when checking convergence
    swarm.savecount           = get_inifile_value<int>   ("savecount",          1);      // Save progress every savecount generations
    swarm.init_pop_strategy   = get_inifile_value<int>   ("init_population_strategy", 2);// Initialisation strategy: 0=one shot, 1=n-shot, 2=n-shot with error if no valid vectors found.
    swarm.init_stationary     = get_inifile_value<bool>  ("init_stationary", false);     // Initialise particle velocities to to zero
    swarm.max_ini_attempts    = get_inifile_value<int>   ("max_initialisation_attempts", 10000); // Maximum number of times to try to find a valid vector for each slot in the initial population.
    swarm.min_acceptable_value= get_inifile_value<double>("min_acceptable_value",0.9999*gl0); // Minimum function value to accept for the initial generation if init_population_strategy > 0.
    swarm.verbose             = get_inifile_value<int>   ("verbosity",          1);      // Output verbosity: 0=only error messages, 1=basic info, 2=generation-level info, 3+=particle-level info
    swarm.seed                = get_inifile_value<int>   ("seed",               -1);     // Base seed for random number generation; non-positive means seed from the system clock
    swarm.allow_new_settings  = get_inifile_value<bool>  ("allow_new_settings", false);  // Allow settings to be overridden with new values when resuming
    swarm.save_particles_natively = get_inifile_value<bool>("save_particles_natively", false); // Save full particle data from every generation

    // Initialise the swarm
    swarm.init();

    // Unit cube boundaries
    for (int i = 0; i < swarm.nPar; i++)
    {
      swarm.lowerbounds.at(i) = 0.0;
      swarm.upperbounds.at(i) = 1.0;
    }

    // Discrete parameters
    for (int i = 0; i < swarm.nDiscrete; i++)
    {
      swarm.discrete.at(i) = 0; //Inidices of discrete parameters (C-style, starting at 0)
    }                           //TODO Needs to be set automatically somehow?  Not yet sure how to deal with discrete parameters in GAMBIT.

    // Run the swarm
    if (swarm.likelihood_function->getRank() == 0) cout << "Starting j-Swarm run...\n" << std::endl;
    swarm.run();
    if (swarm.likelihood_function->getRank() == 0) cout << "j-Swarm run finished!" << std::endl;
    return 0;

  }

}
