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
///  *********************************************


#include "gambit/Utils/threadsafe_rng.hpp"
#include "gambit/Utils/util_macros.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Logs/logger.hpp"

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

#define ALL_RNGS (default_random_engine, minstd_rand, minstd_rand0, mt19937, mt19937_64, ranlux24_base, ranlux48_base, ranlux24, ranlux48, knuth_b)
#define MAKE_SPECIALISED_RNG(r, data, elem)                                    \
        else if (engine == STRINGIFY(elem))                                    \
        {                                                                      \
          static Utils::specialised_threadsafe_rng<elem> ultralocal_rng(seed); \
          local_rng = &ultralocal_rng;                                         \
        }
#define ENABLE_ALL_RNGS BOOST_PP_SEQ_FOR_EACH(MAKE_SPECIALISED_RNG, , BOOST_PP_TUPLE_TO_SEQ(ALL_RNGS))

namespace Gambit
{

  /// Choose the engine to use for random number generation, based on the contents of the ini file.
  void Random::create_rng_engine(str engine, int seed)
  {
    using namespace std;
    if (engine == "default")
    {
      engine = "mt19937_64 (default)";
      static Utils::specialised_threadsafe_rng<mt19937_64> ultralocal_rng(seed);
      local_rng = &ultralocal_rng;
    }
    ENABLE_ALL_RNGS
    else utils_error().raise(LOCAL_INFO, "Unknown random number generation engine: "+engine+".  Please check your yaml file.");
    logger() << LogTags::utils << "Random number engine " << engine << " selected with ";
    if (seed == -1) logger() << "hardware random ";
    logger() << "seed " << seed << "." << EOM;
  }

  /// Draw a single uniform random deviate in the range (0,1) using the chosen RNG engine
  double Random::draw()
  {
    if (local_rng == NULL) create_rng_engine("default", -1);
    return std::generate_canonical<double, 32>(rng());
  }

}







