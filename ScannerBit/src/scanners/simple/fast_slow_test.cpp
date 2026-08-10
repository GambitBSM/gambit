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

scanner_plugin(fast_slow_test, version(1, 0, 0))
{
  like_ptr LogLike;
  int point_number, fast_repeats, slow_speed_threshold;
  int numtasks, rank;
  std::vector<bool> is_fast;
  
  plugin_constructor
  {
    LogLike = get_purpose(get_inifile_value<std::string>("like"));
    point_number = get_inifile_value<int>("point_number", 10);
    fast_repeats = get_inifile_value<int>("fast_repeats", 1);
    slow_speed_threshold = get_inifile_value<int>("slow_speed_threshold", 0);
    
    int dim = get_dimension();
    YAML::Node model_speeds = get_inifile_value<YAML::Node>("ModelSpeeds", YAML::Node());
    std::vector<std::string> params = get_prior().getShownParameters();
    
    is_fast.assign(dim, false);
    for (int i = 0; i < dim; i++)
    {
      std::string::size_type pos = params[i].find("::");
      std::string model = params[i].substr(0, pos);
      std::string param = params[i].substr(pos + 2);
      
      int speed = slow_speed_threshold;
      YAML::Node model_node = model_speeds[model];
      if (model_node)
      {
        if (model_node.IsMap())
        {
          if (model_node[param]) speed = model_node[param].as<int>();
          else if (model_node["default"]) speed = model_node["default"].as<int>();
        }
        else
        {
          speed = model_node.as<int>();
        }
      }
      is_fast[i] = (speed > slow_speed_threshold);
    }

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
    int dim = get_dimension();
    std::vector<double> a(dim);
    
    std::cout << "Entering fast-slow test sampler."
              << "\n\t slow points to draw: " << point_number
              << "\n\t fast repeats per slow point: " << fast_repeats << std::endl;
    
    for (int k = 0; k < point_number; k++)
    {
      // Draw the whole point (slow and fast params alike) uniformly at random
      for (int i = rank; i < dim; i += numtasks)
      {
        a[i] = Gambit::Random::draw();
      }
      LogLike(a);
      
      // Repeat the same point, redrawing only the fast params
      for (int r = 1; r < fast_repeats; r++)
      {
        for (int i = rank; i < dim; i += numtasks)
        {
          if (is_fast[i]) a[i] = Gambit::Random::draw();
        }
        LogLike(a);
      }
      
      if (k%1000 == 0) // TODO: User set param
        std::cout << "slow points: " << k << " / " << point_number << std::endl;
    }
    
    return 0;
  }
}
