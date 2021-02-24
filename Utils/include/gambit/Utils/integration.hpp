//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper functions for numerical integration
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2018 Jan
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Feb
///
///  *********************************************

#include "gambit/Utils/util_functions.hpp"
#include <functional>

namespace Gambit
{

  namespace Utils
  {

    /// Unwrapper for passing std::function to GSL integrator
    /// Based on example from https://martin-ueding.de/articles/cpp-lambda-into-gsl/index.html
    double unwrap(double x, void *p);
 
    /// Integrate a std::function using GSL cquad
    double integrate_cquad(std::function<double(double)> ftor, double a, double b, double abseps, double releps);

  }

}


