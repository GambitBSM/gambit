//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  ScannerBit interface to Diver 1.4.0
///
///  Header file
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patrickcolinscott@gmail.com)
///  \date 2025 Apr
///
///  \author Will Handley
///          (will.handley@gmail.com)
///  \date 2025 Dec
///
///  *********************************************

#pragma once

#include "gambit/ScannerBit/scanner_plugin.hpp"

// C++ prototype of the main run_de function for Diver.
// Note: final int parameter is the MPI communicator (negative = use MPI_COMM_WORLD)
extern "C" double cdiver(double (*)(double[], const int, int&, bool&, const bool, void*&), int, const double[], const double[],
           const char[], int, double[], double[], int, const int[], bool, int, int, int, const double[], double, double, bool,
           bool, int, bool, bool, double, int, bool, int, bool, bool, bool, bool, int, int, const double[], bool, int, double, int,
           void*&, int, int);

namespace Gambit
{

  namespace Diver_1_4_0
  {

    /// Structure for passing likelihood and printer data through Diver to the objective function.
    struct diverScanData
    {
      Scanner::like_ptr likelihood_function;
      Scanner::printer_interface* printer;
    };

    /// Function to be minimised by Diver
    double objective(double params[], const int param_dim, int &fcall, bool &quit, const bool validvector, void*& context);

  }

}
