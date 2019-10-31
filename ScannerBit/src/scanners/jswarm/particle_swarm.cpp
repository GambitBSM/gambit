//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  j-Swarm: particle swarm optimisation with
///  meta-optimisation a la jDE.
///
///  Implementations of particle_swarm class
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

#include <limits>
#include "gambit/ScannerBit/scanners/jswarm/jswarm.hpp"

namespace Gambit
{

  namespace jswarm_1_0_0
  {

    /// Constructor
    particle_swarm::particle_swarm()
    : global_best_value(-std::numeric_limits<double>::max())
    , nPar_total(0)
    , phi1_index(0)
    , phi2_index(0)
    , omega_index(0)
    , path("")
    , nPar(0)
    , nDerived(0)
    , nDiscrete(0)
    , maxgen(100)
    , NP(100)
    , bndry(1)
    , convsteps(10)
    , savecount(10)
    , init_pop_strategy(1)
    , max_ini_attempts(1)
    , verbose(0)
    , seed(-1)
    , fcall(0)
    , omega(1)
    , phi1(1.5)
    , phi2(1.5)
    , convthresh(1e-2)
    , min_acceptable_value(-std::numeric_limits<double>::max())
    , adapt_phi(false)
    , adapt_omega(false)
    , init_stationary(false)
    , resume(false)
    {}

    /// Initialise the swarm
    void particle_swarm::init()
    {
      // Read the saved settings if resuming and forbidding new settings.
      if (resume and not allow_new_settings) read_settings(true);

      // Make sure that there are actually positive numbers of particles and parameters
      if (NP <= 0 or nPar <= 0) Scanner::scan_error().raise(LOCAL_INFO, "You must set NP and nPar positive before initialising a particle swarm!");

      // Add adaptive parameters (if any) to the total size of the parameter vector
      nPar_total = nPar;
      if (adapt_phi)
      {
        nPar_total += 2;
        phi1_index = nPar_total - 2;
        phi2_index = nPar_total - 1;
      }
      if (adapt_omega)
      {
        nPar_total += 1;
        omega_index = nPar_total - 1;
      }

      // Size the vecotrs to hold the upper and lower parameter boundaries
      lowerbounds.resize(nPar_total);
      upperbounds.resize(nPar_total);

      // Set the limits for the parameters of the algorithm to be determined adaptively
      if (adapt_phi)
      {
        lowerbounds[phi1_index] = lowerbounds[phi2_index] = 1.5;
        upperbounds[phi1_index] = upperbounds[phi2_index] = 3.0;
      }
      if (adapt_omega)
      {
        lowerbounds[omega] = 0.0;
        upperbounds[omega] = 1.0;
      }

      // Seed the random number generator
      input_seed = seed;
      if (seed == -1) seed = std::random_device()();
      rng.seed(seed);

      // Create the particles
      for (int i = 0; i < NP; i++) particles.push_back(particle(nPar_total, lowerbounds, upperbounds, rng));

      // Create an array to hold the indices of the discrete parameters
      // TODO deal properly with discrete parameters
      if (nDiscrete != 0) discrete.resize(nDiscrete);

      // Done
      if (verbose > 1) cout << "j-Swarm: successfully initialised swarm with NP = " << NP << ", nPar = " << nPar << ", nDiscrete = " << nDiscrete << endl;
    }

    /// Release the swarm
    void particle_swarm::run()
    {
      if (verbose > 0) cout << "j-Swarm: beginning run." << endl;

      // Read the saved settings again if resuming and forbidding new settings (in case the user overwrote them between init and now).
      if (resume and not allow_new_settings) read_settings(false);

      // Initialise the first population
      // TODO MPI parallelise
      for (int i = 0; i < NP; i++)
      {
        particle& p = particles[i];
        p.init(init_stationary);
        // TODO implement init strategy
        // using init_pop_strategy, min_acceptable_value, max_ini_attempts
        p.lnlike = likelihood_function(p.x);
        update_best_fits(p);
      }

      if (verbose > 1) cout << "  j-Swarm: successfully tested first generation." << endl;

      // Save the run settings and first generation
      save_settings();
      save_generation();

      // Begin the generation loop
      // TODO MPI parallelise
      for (int gen = 2; gen <= maxgen; gen++)
      {
        if (verbose > 1) cout << "  j-Swarm: moving on to generation " << gen << "." << endl;

        // Loop over the population of this generation
        for (int pi = 0; pi < NP; pi++)
        {

          if (verbose > 2) cout << "    j-Swarm: working on particle " << pi << "." << endl;

          // Get the particle
          particle& p = particles[pi];

          // Update the particle's position and velocity
          update_particle(p);

          if (verbose > 2) cout << "      j-Swarm: updated velocity and position for particle " << pi << "." << endl;

          // Check if the particle is now outside the prior box, and fix it if so (when bndry = 2 or 3)
          if (implement_boundary_policy(p))

            // Call the likelihood function, being sure to discretise any discrete parameters
            p.lnlike = likelihood_function(p.discretised_x(discrete));

            // Update the particle's personal best and the global best if necessary
            update_best_fits(p);

            // Increment the number of function calls
            fcall += 1;

            if (verbose > 2) cout << "      j-Swarm: new objective value for particle " << pi << ": " << p.lnlike << endl;

          else
          {
            // Return the worst possible likelihood if the point is outside the prior box and bndry = 1
            p.lnlike = -std::numeric_limits<double>::max();
          }

        }

        // Check whether the calling code wants us to shut down early
        if (Scanner::Plugins::plugin_info.early_shutdown_in_progress())
        {
           if (verbose > 0) cout << endl << "  j-Swarm: quit requested by objective function; saving and exiting..." << endl;
           save_generation();
           break;
        }

        // Save generation
        if (gen%savecount == 0) save_generation();

        // Check for convergence
        if (converged()) break;

      }

      if (verbose > 0) cout << "j-Swarm: run complete." << endl << endl;

    }

    /// Update a particle's velocity and use that to update its position
    void particle_swarm::update_particle(particle& p)
    {
      if (adapt_omega) omega = p.x[omega_index];
      if (adapt_phi)
      {
        phi1 = p.x[phi1_index];
        phi2 = p.x[phi2_index];
      }
      for (int i; i < nPar_total; i++)
      {
        double r1 = std::generate_canonical<double, 32>(rng);
        double r2 = std::generate_canonical<double, 32>(rng);
        p.v[i] = omega*p.v[i] + phi1*r1*(p.personal_best_x[i]-p.x[i]) + phi2*r2*(global_best_x[i]-p.x[i]);
        p.x[i] = p.x[i] + p.v[i];
      }
    }

    /// Update a particle's own best fit and the global best fit
    void particle_swarm::update_best_fits(particle& p)
    {
      p.update_personal_best();
      if (p.lnlike > global_best_value)
      {
        global_best_value = p.lnlike;
        global_best_x = p.x;
      }
    }

    /// Deal with vectors outside the prior box according to the value of bndry
    bool particle_swarm::implement_boundary_policy(particle& p)
    {
      // Test if the particle has a valid position
      bool validVector = true;
      for (int i = 0; i < nPar_total; i++)
      {
        if (p.x[i] < lowerbounds[i] or p.x[i] > upperbounds[i]) validVector = false;
      }
      // Return true immediately if it has a valid position, or false if it does not and the brick wall boundary condition is in use.
      if (validVector or bndry == 1) return validVector;

      // Modify the particle position and velocity if other boundary strategies are in use.
      switch(bndry)
      {
        // Randomly choose new values somewhere in the prior box, and reset the velocity.
        case 2:
          p.init(init_stationary);
          break;

        // Reflect the position and velocity about the borders violated
        case 3:
          p.reflect();
          break;

        // Something went wrong
        default:
          Scanner::scan_error().raise(LOCAL_INFO, "Unrecognised bndry setting for j-Swarm. Please set bndry = 1, 2 or 3.");
      }
      return true;
    }

    /// Save swarm settings
    void particle_swarm::save_settings()
    {
      std::ofstream settings;
      settings.open(path + ".settings.yaml");
      settings << "# Dimensionality of the parameter space (int)" << endl
       << "nPar: " << nPar << endl
       << "# Number of derived quantities to output (GAMBIT printers handle these). (int)" << endl
       << "nDerived: " << nDerived << endl
       << "# Number of parameters that are to be treated as discrete (int)" << endl
       << "nDiscrete: " << nDiscrete << endl
       << "# Maximum number of generations (int)" << endl
       << "maxgen: " << maxgen << endl
       << "# Population size (individuals per generation) (int)" << endl
       << "NP: " << NP << endl
       << "# Boundary constraint: 1=brick wall, 2=random re-initialization, 3=reflection (int)" << endl
       << "bndry: " << bndry << endl
       << "# Number of steps to smooth over when checking convergence (int)" << endl
       << "convsteps: " << convsteps << endl
       << "# Save progress every savecount generations (int)" << endl
       << "savecount: " << savecount << endl
       << "# Initialisation strategy: 0=one shot, 1=n-shot, 2=n-shot with error if no valid vectors found. (int)" << endl
       << "init_pop_strategy: " << init_pop_strategy << endl
       << "# Maximum number of times to try to find a valid vector for each slot in the initial population. (int)" << endl
       << "max_ini_attempts: " << max_ini_attempts << endl
       << "# Output verbosity: 0=only error messages, 1=basic info, 2=civ-level info, 3+=population info (int)" << endl
       << "verbose: " << verbose << endl
       << "# Input base seed for random number generation; non-positive means seed from the system clock (int)" << endl
       << "seed: " << input_seed << endl
       << "# Base seed actually used for random number generation in last run (int)" << endl
       << "actual_seed: " << seed << endl
       << "# Inertial weight (double)" << endl
       << "omega: " << omega << endl
       << "# Cognitive weight (double)" << endl
       << "phi1: " << phi1 << endl
       << "# Social weight (double)" << endl
       << "phi2: " << phi2 << endl
       << "# Threshold for gen-level convergence: smoothed fractional improvement in the mean population value (double)" << endl
       << "convthresh: " << convthresh << endl
       << "# Minimum function value to accept for the initial generation if init_population_strategy > 0. (double)" << endl
       << "min_acceptable_value: " << min_acceptable_value << endl
       << "# Use self-optimising adaptive choices for phi1 and phi2 (bool)" << endl
       << "adapt_phi: " << YAML::Node(adapt_phi) << endl
       << "# Use self-optimising adaptive choices for omega (bool)" << endl
       << "adapt_omega: " << YAML::Node(adapt_omega) << endl
       << "# Initialise particle velocities to zero (bool)" << endl
       << "init_stationary: " << YAML::Node(init_stationary) << endl
       << "# Parameter space boundaries (std::vector<double>)" << endl
       << "upperbounds: " << endl << YAML::Node(upperbounds) << endl
       << "lowerbounds: " << endl << YAML::Node(lowerbounds) << endl
       << "# Indices of parameters to be treated as discrete (std::vector<int>) (bool)" << endl
       << "discrete: " << YAML::Node(discrete) << endl;
      settings.close();
    }

    /// Read swarm settings
    void particle_swarm::read_settings(bool init)
    {
      if (verbose > 0 and init)
      {
        cout << "  j-Swarm: WARNING using settings from resumed run and ignoring any new ones!" << endl
             << "           Set allow_new_settings=true to try changing settings when resuming." << endl;
      }
      YAML::Node settings;
      try
      {
        settings = YAML::LoadFile(path + ".settings.yaml");
        nPar = settings["nPar"].as<int>();
        nDerived = settings["nDerived"].as<int>();
        nDiscrete = settings["nDiscrete"].as<int>();
        maxgen = settings["maxgen"].as<int>();
        NP = settings["NP"].as<int>();
        bndry = settings["bndry"].as<int>();
        convsteps = settings["convsteps"].as<int>();
        savecount = settings["savecount"].as<int>();
        init_pop_strategy = settings["init_pop_strategy"].as<int>();
        max_ini_attempts = settings["max_ini_attempts"].as<int>();
        verbose = settings["verbose"].as<int>();
        omega = settings["omega"].as<double>();
        phi1 = settings["phi1"].as<double>();
        phi2 = settings["phi2"].as<double>();
        convthresh = settings["convthresh"].as<double>();
        min_acceptable_value = settings["min_acceptable_value"].as<double>();
        adapt_phi = settings["adapt_phi"].as<bool>();
        adapt_omega = settings["adapt_omega"].as<bool>();
        init_stationary = settings["init_stationary"].as<bool>();
        upperbounds = settings["upperbounds"].as<std::vector<double>>();
        lowerbounds = settings["lowerbounds"].as<std::vector<double>>();
        discrete = settings["discrete"].as<std::vector<int>>();
        if (init) seed = settings["seed"].as<int>();
      }
      catch (YAML::Exception &e)
      {
        std::ostringstream msg;
        msg << "Error reading file \""<<path + ".settings.yaml"<<"\"! " << endl;
        msg << "Please check that file exists and is properly formatted." << endl;
        msg << "(yaml-cpp error: "<<e.what()<<" )";
        Scanner::scan_error().raise(LOCAL_INFO,msg.str());
      }
    }

    /// Save generation data
    void particle_swarm::save_generation()
    {
      // << "# Number of calls to the objective function so far (int)" << endl
      // << "fcall: " << fcall << endl
      // generation num
      // convergence info

      //TODO, using path
    }

    /// Read generation data
    void particle_swarm::read_generation()
    {
      //TODO, using path

      //fcall = progress.as("fcall");
    }

    /// Check whether the swarm has converged
    bool particle_swarm::converged()
    {
      //TODO, using convsteps, savecount;
      return false;
    }

  }

}
