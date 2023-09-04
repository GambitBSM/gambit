//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit module function for obtaining the 
///  list of the active collider processes
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (a.kvellestad@imperial.ac.uk)
///  \date   2019 Sep
///
///  *********************************************

#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"

// #define COLLIDERBIT_DEBUG
#define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ":  "

namespace Gambit
{

  namespace ColliderBit
  {

    /// Get the list of active collider process codes
    void getActiveProcessCodes(std::vector<int>& result)
    {
      using namespace Pipes::getActiveProcessCodes;

      if (*Loop::iteration == COLLIDER_INIT)
      {
        result.clear();
      }

      if (*Loop::iteration == XSEC_CALCULATION)
      {
        result = (*Dep::HardScatteringSim)->all_active_process_codes();

        #ifdef COLLIDERBIT_DEBUG
          for (int pcode : result)
          {
            cout << DEBUG_PREFIX << "getActiveProcessCodes: - active process: " << pcode << endl;
          }
        #endif
      }
    }

  } 
} 


