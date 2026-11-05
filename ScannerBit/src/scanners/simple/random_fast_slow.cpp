//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  A minimal fast-slow sampler, for verifying that Core's fast-slow
///  caching
///
///  Classifies each scanned parameter as "slow" or "fast" from this plugin's own
///  "ModelSpeeds" option, set directly under this scanner's own yaml block. Each model entry can be either a plain
///  integer (a whole-model default, applied to all of that model's parameters) or a map
///  with a "default" entry plus per-parameter overrides, e.g.
///    ModelSpeeds:
///      CMSSM: 0
///      Fast_Slow_Test_Three: {default: 0, b: 5}
///  A parameter is "fast" if its effective speed is greater than "slow_speed_threshold";
///  parameters with no assigned speed at all are treated as slow. For each of "point_number"
///  outer points, the slow parameters are drawn once uniformly at random; the point is then
///  re-evaluated "fast_repeats" times, with only the fast parameters redrawn each repeat.
///  Comparing printer output for the same outer point should then show slow-only
///  observables reused (identical) across the repeats, and fast-dependent observables
///  varying.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date 2026 Aug
///
///  *********************************************

#ifdef WITH_MPI
#include "gambit/Utils/begin_ignore_warnings_mpi.hpp"
#include "mpi.h"
#include "gambit/Utils/end_ignore_warnings.hpp"
#endif

#include <vector>
#include <string>
#include <iostream>

#include "gambit/ScannerBit/scanner_plugin.hpp"
#include "gambit/Utils/threadsafe_rng.hpp"

scanner_plugin(random_fast_slow, version(1, 0, 0))
{
    like_ptr LogLike;
    int point_number, fast_repeats, slow_speed_threshold;
    int numtasks, rank, dim;
    std::vector<int> ranges;

    plugin_constructor
    {
        LogLike = get_purpose(get_inifile_value<std::string>("like"));
        point_number = get_inifile_value<int>("point_number", 10);
        fast_repeats = get_inifile_value<int>("fast_repeats", 1);
        slow_speed_threshold = get_inifile_value<int>("slow_speed_threshold", 5);

        dim = get_dimension();

        ranges = get_prior().getSpeedRanges({0, slow_speed_threshold, -1});

    #ifdef WITH_MPI
        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    #else
        numtasks = 1;
        rank = 0;
    #endif
    }
  
  int plugin_main()
  {
      vector<double> a(dim);
      auto slow = a.segment(ranges[0], ranges[1] - ranges[0]);
      auto fast = a.segment(ranges[1], ranges[2] - ranges[1]);
      // // or, if you want to use a std::vector:
      // std::vector<double. a(dim);
      // map_vector<double> slow(a.data()+ ranges[0], ranges[1] - ranges[0]);
      // map_vector<double> fast(a.data()+ ranges[1], ranges[2] - ranges[1]);

      std::cout << "Entering fast-slow test sampler."
                << "\n\t slow points to draw: " << point_number
                << "\n\t fast repeats per slow point: " << fast_repeats
                << "\n\t ranges: [" << ranges[0] << ", " << ranges[1] << ", " << ranges[2] << "]" << std::endl;

        for (int k = rank; k < point_number; k+=numtasks)
        {
            // Draw the whole point (slow and fast params alike) uniformly at random
            for (int i = 0; i < dim; ++i)
            {
                a[i] = Gambit::Random::draw();
            }
            LogLike(a);

            // Repeat the same point, redrawing only the fast params
            for (int r = 0; r < fast_repeats; ++r)
            {
                for (int i = 0, end = fast.size(); i < end; ++i)
                {
                    fast[i] = Gambit::Random::draw();
                }
                LogLike(a);
            }

            if (k%1000 == 0) // TODO: User set param
                std::cout << "slow points: " << k << " / " << point_number << std::endl;
        }

        return 0;
    }
}
