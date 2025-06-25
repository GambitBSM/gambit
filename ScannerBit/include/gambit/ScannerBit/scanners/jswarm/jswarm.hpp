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

#include <string>
#include <vector>
#include <random>
#include <memory>

#include "gambit/ScannerBit/scanner_plugin.hpp"


namespace Gambit
{

  namespace jswarm_1_0_0
  {

    /// The type of RNG to be used locally in j-Swarm
    typedef std::independent_bits_engine<std::mt19937_64,64,std::uint64_t> rng_type;

    /// An individual particle in a swarm
    class particle
    {

      private:

        /// Parameter space boundaries
        /// @{
        std::vector<double>* lowerbounds;
        std::vector<double>* upperbounds;
        /// @}

        /// pointer to random number generator engine to use
        rng_type* rng;

      public:

        /// Particle position vector
        std::vector<double> x;

        /// Particle velocity vector
        std::vector<double> v;

        /// Current objective value
        double lnlike;

        /// Current personal best fit
        double personal_best_value;

        /// Current personal best-fit vector
        std::vector<double> personal_best_x;

        /// Constructor
        particle(int, std::vector<double>&, std::vector<double>&, rng_type&);

        /// Initialise a particle with a random position and zero/random velocity
        void init(bool zero_vel);

        /// Update the particle's personal best-seen fit so far
        void update_personal_best();

        /// Reflect a particle's position and velocity about the walls of the prior box
        void reflect();

        /// Return a particle's position vector, discretised at some specified indices
        std::vector<double> discretised_x(const std::vector<int>&);

    };


    /// A swarm of particles and methods to evolve them
    class particle_swarm
    {

      private:

        /// MPI process rank
        int rank;

        /// Number of MPI processes
        int nprocs;

        /// MPI process rank
        int NP_per_rank;

        /// Particles making up the swarm (rank-local selection)
        std::vector<particle> particles;

        /// Particles making up the swarm (total population)
        std::vector<particle> particles_global;

        /// Current global best fit
        /// @{
        double global_best_value;
        std::vector<double> global_best_x;
        /// @}

        /// Mean personal best fit across the current generation
        double mean_lnlike;

        /// Smoothed fractional improvement in the mean personal best fit across the most recent generations
        double sfim;

        /// Fractional improvements in the mean personal best lnlike in the most recent generations
        std::vector<double> conv_progress;

        /// Dimensionality of the parameter space including any meta-optimisation parameters
        int nPar_total;

        /// Indices in parameter vector correpsonding to algorithm parameters when using meta-optimisation
        /// @{
        int phi1_index;
        int phi2_index;
        int omega_index;
        /// @}

        /// Input base seed for random number generation; non-positive means seed from the system clock
        int input_seed;

        /// Random number generator engine
        rng_type rng;

        /// Update a particle's velocity and use that to update its position
        void update_particle(particle&);

        /// Update a particle's own best fit and the global best fit
        void update_best_fits(particle&);

        /// Deal with vectors outside the prior box according to the value of bndry
        bool implement_boundary_policy(particle&);

        /// Save swarm settings
        void save_settings();

        /// Read swarm settings
        void read_settings(bool);

        /// Save data from the last generation
        void save_generation(int);

        /// Read data from the last generation
        int read_generation();

        /// Check whether the swarm has converged
        bool converged();

        /// Collect all particles and related data to rank 0
        void collect_data();

      public:

        /// Pointer to objective function
        Scanner::like_ptr likelihood_function;

        /// Pointer to GAMBIT printer
        Scanner::printer_interface* printer;

        /// Prefix for all j-Swarm save files
        std::string path;

        /// Dimensionality of the parameter space
        int nPar;

        /// Number of derived quantities to output (GAMBIT printers handle these).
        int nDerived;

        /// Number of parameters that are to be treated as discrete
        int nDiscrete;

        /// Maximum number of generations
        int maxgen;

        /// Population size (individuals per generation)
        int NP;

        /// Boundary constraint: 1=brick wall, 2=random re-initialization, 3=reflection
        int bndry;

        /// Number of steps to smooth over when checking convergence
        int convsteps;

        /// Save progress every savecount generations
        int savecount;

        /// Initialisation strategy: 0=one shot, 1=n-shot, 2=n-shot with error if no valid vectors found.
        int init_pop_strategy;

        /// Maximum number of times to try to find a valid vector for each slot in the initial population.
        int max_ini_attempts;

        /// Output verbosity: 0=only error messages, 1=basic info, 2=civ-level info, 3+=population info
        int verbose;

        /// Base seed for random number generation; non-positive means seed from the system clock
        int seed;

        /// Number of calls to the objective function so far
        int fcall;

        /// Number of calls to the objective function so far across all processes
        int fcall_global;

        /// Inertial weight
        double omega;

        /// Cognitive weight
        double phi1;

        /// Social weight
        double phi2;

        /// Threshold for gen-level convergence: smoothed fractional improvement in the mean personal best population value
        double convthresh;

        /// Minimum function value to accept for the initial generation if init_population_strategy > 0.
        double min_acceptable_value;

        /// Use self-optimising adaptive choices for phi1 and phi2
        bool adapt_phi;

        /// Use self-optimising adaptive choices for omega
        bool adapt_omega;

        /// Initialise particle velocities to zero
        bool init_stationary;

        /// Resume from previous run
        bool resume;

        /// Allow settings to be overridden with new values when resuming
        bool allow_new_settings;

        /// Save full particle data from every generation
        bool save_particles_natively;

        /// Parameter space boundaries
        /// @{
        std::vector<double> upperbounds;
        std::vector<double> lowerbounds;
        /// @}

        /// Indices of parameters to be treated as discrete
        std::vector<int> discrete;

        /// Constructor
        particle_swarm();

        /// Initialise the swarm
        void init();

        /// Release the swarm
        void run();

    };


  }

}
