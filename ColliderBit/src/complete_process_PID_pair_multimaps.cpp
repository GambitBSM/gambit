//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Source file for the function
///  all_PID_pairs_to_process_codes(), which 
///  returns a "reversed" version of the 
///  all_process_codes_to_PID_pairs multimap
///
///  *********************************************
///
///  Authors (add name if you modify):
///
///  \author Anders Kvellestad
///          (a.kvellestad@imperial.ac.uk)
///  \date 2019 Sep
///
///  *********************************************

#include "gambit/ColliderBit/complete_process_PID_pair_multimaps.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    // A function stat returns the "reversed" multimap, from PID_pair to process codes
    const multimap_PID_pair_int& all_PID_pairs_to_process_codes()
    {
      static bool first = true;
      static multimap_PID_pair_int result;

      // Construct the map the first time this function is called
      if (first)
      {

        // Loop through all elements in all_process_codes_to_PID_pairs
        for (const std::pair<int,PID_pair> elem : all_process_codes_to_PID_pairs)
        {
          // Insert the reversed pair into the result map
          result.insert( std::make_pair(elem.second, elem.first) );
        }

        first = false;
      }

      return result;
    }

  }
}
