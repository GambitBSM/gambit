//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  j-Swarm: particle swarm optimisation with
///  meta-optimisation a la jDE.
///
///  Implementations of particle class
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

#include "gambit/ScannerBit/scanners/jswarm/jswarm.hpp"


namespace Gambit
{

  namespace jswarm_1_0_0
  {

    /// Constructor
    particle::particle(int nPar, std::vector<double>& lb, std::vector<double>& ub, rng_type& generator)
    : lowerbounds(&lb)
    , upperbounds(&ub)
    , rng(&generator)
    , personal_best_value(-std::numeric_limits<double>::max())
    {
      if (nPar <= 0) Scanner::scan_error().raise(LOCAL_INFO, "You must set nPar positive before creating a particle!");
      x.resize(nPar);
      v.resize(nPar);
      personal_best_x.resize(nPar);
    }

    /// Initialise a particle with a random position and zero/random velocity
    void particle::init(bool zero_vel)
    {
      for (unsigned int i = 0; i < x.size(); i++)
      {
        double extent = upperbounds->at(i) - lowerbounds->at(i);
        // Set position randomly
        x.at(i) = lowerbounds->at(i) + extent * std::generate_canonical<double, 32>(*rng);
        // Reset velocity to either zero or a random number in [-extent,extent].  Velocity is in units of [x] per generation 'timestep'.
        v.at(i) = (zero_vel ? 0.0 : extent * (2.0 * std::generate_canonical<double, 32>(*rng) - 1.0));
      }
    }

    /// Update the particle's personal best fit seen so far
    void particle::update_personal_best()
    {
      if (lnlike > personal_best_value)
      {
        personal_best_value = lnlike;
        personal_best_x = x;
      }
    }

    /// Reflect a particle's position and velocity off the walls of the prior box
    void particle::reflect()
    {
      for (unsigned int i = 0; i < x.size(); i++)
      {
        double bound_violated, other_bound;
        double lb = lowerbounds->at(i);
        double ub = upperbounds->at(i);

        // Work out whether it is the upper, lower, or no bound exceeded for this dimension
        if (x.at(i) < lb)
        {
          bound_violated = lb;
          other_bound = ub;
        }
        else if (x.at(i) > ub)
        {
          bound_violated = ub;
          other_bound = lb;
        }
        else continue;

        // Work out how many prior box lengths the particle has overshot (= how many reflections needed)
        double overshoot_factor = (x.at(i) - bound_violated) / (ub - lb);
        int reflections = (int) overshoot_factor;
        double offset = (overshoot_factor - reflections) *  (ub - lb);

        // Perform the reflections
        if (reflections%2 == 1) // odd number of reflections
        {
          x.at(i) = bound_violated - offset;
          v.at(i) = -v.at(i);
        }
        else x.at(i) = other_bound + offset; //even number of reflections
      }


    }

    /// Return a particle's position vector, discretised at some specified indices
    std::vector<double> particle::discretised_x(const std::vector<int>& indices)
    {
      std::vector<double> x_discrete = x;
      for (int i : indices) x_discrete.at(i) = round(x.at(i));
      return x_discrete;
    }


  }

}


