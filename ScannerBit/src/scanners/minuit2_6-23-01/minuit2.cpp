//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface to Minuit2
///
///  Header file
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andrew Fowlie
///          (andrew.j.fowlie@qq.com)
///  \date 2020 August
///
///  *********************************************

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <iomanip>  // For debugging only

#include "gambit/ScannerBit/scanner_plugin.hpp"
#include "gambit/ScannerBit/scanners/minuit2/minuit2.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/util_functions.hpp"


namespace Gambit
{
   namespace minuit2
   {
      /// Global pointer to loglikelihood wrapper object, for use in the minuit2 callback functions
      LogLikeWrapper *global_loglike_object;
   }
}

/// Typedef for the ScannerBit pointer to the external loglikelihood function
typedef Gambit::Scanner::like_ptr scanPtr;


/// =================================================
/// Interface to ScannerBit
/// =================================================

scanner_plugin(minuit2, version(6, 23, 01))
{
   reqd_inifile_entries();
   reqd_libraries("minuit2");

   // Pointer to the (log)likelihood function
   scanPtr LogLike;

   /// The constructor to run when the minuit2 plugin is loaded.
   plugin_constructor
   {
      // Retrieve the external likelihood calculator
      LogLike = get_purpose(get_inifile_value<std::string>("like"));
      if (LogLike->getRank() == 0) {
        std::cout << "Loading minuit2 plugin for ScannerBit." << std::endl;
      }
   }

   /// The main routine to run for the minuit2 scanner.
   int plugin_main(void)
   {
      // Retrieve the dimensionality of the scan.
      const int dim = get_dimension();

      // Retrieve the global option specifying the minimum interesting likelihood
      double gl0 = get_inifile_value<double>("likelihood: model_invalid_for_lnlike_below");
      // Retrieve the global option specifying the likelihood offset to use
      double offset = get_inifile_value<double>("likelihood: lnlike_offset", 0.);
      // Make sure the likleihood functor knows to apply the offset internally in ScannerBit
      LogLike->setPurposeOffset(offset);
      // Offset the minimum interesting likelihood by the offset
      gl0 = gl0 + offset;

      // minuit2 algorithm options
      const auto algorithm{get_inifile_value<std::string>("algorithm", "minimize")};
      const auto max_loglike_calls{get_inifile_value<int>("max_loglike_calls", 100000)};   
      const auto tolerance{get_inifile_value<double>("tolerace", 0.0001)};   
      const auto print_level{get_inifile_value<int>("print_level", 1)};   

      ROOT::Math::Minimizer* min = new ROOT::Minuit2::Minuit2Minimizer(algorithm.c_str());
      min->SetMaxFunctionCalls(max_loglike_calls);
      min->SetTolerance(tolerance);
      min->SetPrintLevel(print_level);

      // create funciton wrapper for minmizer
      ROOT::Math::Functor f(&LogLike, dim);
      min->SetFunction(f);

      double start[2] = {-1., 1.2};
      double step[2] = {0.01, 0.01};

      // set the free variables to be minimized
      for (int i = 0; i < dim; i++) {
        min->SetVariable(i, "x", start[i], step[i]);
      }

      // do the minimization
      min->Minimize();

      // manually delete the pointer
      delete min;
   }
}

