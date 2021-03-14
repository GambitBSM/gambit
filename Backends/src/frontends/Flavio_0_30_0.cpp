//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for Flavio backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///
/// \author Marcin Chrzaszcz
///         (mchrzasz@cern.ch)
/// \date 2018
///
///  *********************************************

#include <sstream>
#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/Flavio_0_30_0.hpp"


// Initialisation
BE_INI_FUNCTION{}
END_BE_INI_FUNCTION


// Convenience functions (definitions)
BE_NAMESPACE
{
  double sm_prediction_CONV(std::string a)
  {
    double result=sm_prediction(a);
    return result;

  }
  
}
END_BE_NAMESPACE  
