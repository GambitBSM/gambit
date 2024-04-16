//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A threadsafe interface to the STL random
///  number generators.  The generator to use can
///  be chosen in the ini/yaml file with option
///    rng: name
///  where name is one of the following:
///    default_random_engine
///      Default random engine
///    minstd_rand
///      Minimal Standard minstd_rand generator
///    minstd_rand0
///      Minimal Standard minstd_rand0 generator
///    mt19937
///      Mersenne Twister 19937 generator
///    mt19937_64
///      Mersene Twister 19937 generator (64 bit)
///    ranlux24_base
///      Ranlux 24 base generator
///    ranlux48_base
///      Ranlux 48 base generator
///    ranlux24
///      Ranlux 24 generator
///    ranlux48
///      Ranlux 48 generator
///    knuth_b
///      Knuth-B generator
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2014 Dec
///
///  \author Andy Buckley
///          (andy.buckley@cern.ch)
///  \date 2017 Jun
///
///  \author Ben Farmer
///          (benjamin.farmer@imperial.ac.uk)
///  \data 2018 Aug
///
///  *********************************************


#ifndef __threadsafe_rng_hpp__
#define __threadsafe_rng_hpp__

#include <random>

#include "gambit/Utils/util_macros.hpp"
#include "gambit/Utils/util_types.hpp"


namespace Gambit
{

  namespace Utils
  {

    /// Base class for thread-safe random number generators.
    /// Must conform to the requirements of UniformRandomBitGenerator,
    /// see e.g. https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator
    /// Importantly, operator() must return UNSIGNED INTEGERS!
    class EXPORT_SYMBOLS threadsafe_rng
    {
      public:
        /// Return type (will convert underlying RNG type to this)
        typedef std::uint64_t result_type;

        /// Pure virtual destructor to force overriding in derived class
        virtual ~threadsafe_rng() = 0;

        /// Operator used for getting random deviates
        virtual result_type operator()() = 0;

        /// Operators for compliance with RandomNumberEngine interface -> random distribution sampling
        static constexpr result_type min() { return 0; }
        static constexpr result_type max() { return UINT64_MAX; }
    };

    /// Give an inline implementation of the destructor, to prevent link errors but keep base class pure virtual.
    inline threadsafe_rng::~threadsafe_rng() {}

    /// Derived thread-safe random number generator class, templated on the RNG engine type.
    template<typename Engine>
    class specialised_threadsafe_rng : public threadsafe_rng
    {
      public:
        /// Create RNG engines, one for each thread.
        specialised_threadsafe_rng(int& seed)
        {
          const int max_threads = omp_get_max_threads();
          rngs = new std::independent_bits_engine<Engine,64,result_type>[max_threads];
          if (seed == -1) seed = std::random_device()();
          for(int index = 0; index < max_threads; ++index)
          {
            rngs[index] = std::independent_bits_engine<Engine,64,result_type>(index + seed);
          }
        }

        /// Destroy RNG engines
        virtual ~specialised_threadsafe_rng() { delete [] rngs; }

        /// Generate a random integer using the chosen engine
        /// Selected uniformly from range (min,max).
        /// To be used as an entropy source for stdlib distributions.
        /// If you want (0,1) random doubles then please use Random::draw(), NOT this function!
        virtual result_type operator()()
        { 
          return rngs[omp_get_thread_num()](); 
        }

      private:

        /// Pointer to array of RNGs, one each for each thread
        std::independent_bits_engine<Engine,64,result_type>* rngs;

    };

  }

  class EXPORT_SYMBOLS Random
  {

    public:

      /// Choose the engine to use for random number generation, based on the contents of the ini file.
      static void create_rng_engine(str, int=-1);

      /// Draw a single uniform random deviate from the interval (0,1) using the chosen RNG engine
      static double draw();

      /// Return a threadsafe wrapper for the chosen RNG engine (to be passed to e.g. std library
      /// distribution function objects)
      static Utils::threadsafe_rng& rng() { return *local_rng; }

    private:

      /// Private constructor makes this a purely managerial class, i.e. unable to be instantiated
      Random() {};

      /// Pointer to the actual RNG
      static Utils::threadsafe_rng* local_rng;
  };

}

#endif // #defined __threadsafe_rng_hpp__
