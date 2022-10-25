//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of ColliderBit that deal with SModelS.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Martin White
///          (martin.white@adelaide.edu.au)
///  \date 2022 Oct
///
///  *********************************************

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <numeric>
#include <sstream>
#include <vector>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"

namespace Gambit
{

  namespace ColliderBit
  {

    void calc_smodels_loglike(double& result)
    {

      using namespace Pipes::calc_smodels_loglike;
      std::string inputFile = "lightEWinos.slha";
      result = BEreq::smodels_results(inputFile);


    }
    
  }
}
