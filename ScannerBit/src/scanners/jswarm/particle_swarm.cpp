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
    : global_best_value(std::numeric_limits<double>::min())
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
    , min_acceptable_value(std::numeric_limits<double>::min())
    , adapt_phi(false)
    , adapt_omega(false)
    , init_stationary(false)
    , resume(false)
    {}

    /// Initialise the swarm
    void particle_swarm::init()
    {
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
      if (seed == -1) seed = std::random_device()();
      rng.seed(seed);

      // Create the particles
      for (int i = 0; i < NP; i++) particles.push_back(particle(nPar_total, lowerbounds, upperbounds, rng));

      // Create an array to hold the indices of the discrete parameters
      // TODO deal properly with discrete parameters
      if (nDiscrete != 0) discrete.resize(nDiscrete);

      // Done
      if (verbose > 1) std::cout << "j-Swarm: successfully initialised swarm with NP = " << NP << ", nPar = " << nPar << ", nDiscrete = " << nDiscrete << std::endl;
    }

    /// Release the swarm
    void particle_swarm::run()
    {
      if (verbose > 0) std::cout << "j-Swarm: beginning run..." << std::endl;

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

      // Save the run settings and first generation
      save_settings();
      save_generation();

      // Begin the generation loop
      // TODO MPI parallelise
      for (int gen = 2; gen <= maxgen; gen++)
      {
        if (verbose > 1) std::cout << "j-Swarm: moving on to generation " << gen << "." << std::endl;

        // Loop over the population of this generation
        for (int pi = 0; pi < NP; pi++)
        {

          if (verbose > 2) std::cout << "j-Swarm: working on particle " << pi << "." << std::endl;

          // Get the particle
          particle& p = particles[pi];

          // Update the particle's position and velocity
          update_particle(p);

          // Check if the particle is now outside the prior box, and fix it if so (when bndry = 2 or 3)
          if (implement_boundary_policy(p))

            // Call the likelihood function
            p.lnlike = likelihood_function(p.x);

            // Update the particle's personal best and the global best if necessary
            update_best_fits(p);

            // Increment the number of function calls
            fcall += 1;

            // Check whether the calling code wants us to shut down early
            if (Scanner::Plugins::plugin_info.early_shutdown_in_progress())
            {
              // TODO broadcast to other processes and get out
              break;
            }

          else
          {
            // Return the worst possible likelihood if the point is outside the prior box and bndry = 1
            p.lnlike = std::numeric_limits<double>::min();
          }

        }

        // Save generation
        if (gen%savecount == 0) save_generation();

        // Check for convergence
        if (converged()) break;

      }

      if (verbose > 0) std::cout << "j-Swarm: completed run." << std::endl;

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
        case(2): p.init(init_stationary);
        // Reflect the position and velocity about the borders violated
        case(3): p.reflect();
        // Something went wrong
        default: Scanner::scan_error().raise(LOCAL_INFO, "Unrecognised bndry setting for j-Swarm. Please set bndry = 1, 2 or 3.");
      }
      return true;
    }

    /// Save swarm settings
    void particle_swarm::save_settings()
    {
      //TODO, using path
    }

    /// Save generation data
    void particle_swarm::save_generation()
    {
      //TODO, using path
    }

    /// Check whether the swarm has converged
    bool particle_swarm::converged()
    {
      //TODO, using convsteps, savecount;
      return false;
    }

  }

}
