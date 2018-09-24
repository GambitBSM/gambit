//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  "cout" printer class member function definitions
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2018 Apr
///
///  *********************************************


// Standard libraries
#include <map>
#include <vector>
#include <algorithm>
#include <ios>
#include <sstream>
#include <fstream>
#include <iomanip>

// Gambit
#include "gambit/Printers/printers/coutprinter.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/util_functions.hpp"

// Code!
namespace Gambit
{

  namespace Printers
  {

    // Constructor
    coutPrinter::coutPrinter(const Options& options, BasePrinter* const primary)
      : BasePrinter(primary,options.getValueOrDef<bool>(false,"auxilliary"))
    {
      // This printer requires no setup
    }

    /// Initialisation function
    // Run by dependency resolver, which supplies the functors with a vector of VertexIDs whose requiresPrinting flags are set to true.
    void coutPrinter::initialise(const std::vector<int>& /*printmevec*/)
    {
    }

    /// Do final buffer dumps
    void coutPrinter::finalise(bool /*abnormal*/)
    {
    }

    /// Reset printer and output to clean state
    void coutPrinter::reset(bool)
    {
        // Nothing actually stored by this printer so no need for this to do anything
    }

    /// Perform any point-specific logic 
    void coutPrinter::check_point(unsigned int mpirank, unsigned long pointID)
    {
        // Actually I think it is just good enough to pre-pend the 
        // line with the point information
        std::cout << mpirank << ", " << pointID << ": "; // No endline
    }

  } // end namespace printers
} // end namespace Gambit
