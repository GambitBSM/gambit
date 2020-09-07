//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  "none" printer class declaration
///
///  This printer has the most simplistic
///  implementation of the virtual functions of BasePrinter
///  All functions are empty.
///  Consequently, this printer does not print anything
///
///  (Based on coutprinter)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2020 May
///
///  *********************************************


#ifndef __none_printer_hpp__
#define __none_printer_hpp__

// Gambit
#include "gambit/Printers/baseprinter.hpp"
#include "gambit/Printers/printers/asciitypes.hpp"

// BOOST_PP
#include <boost/preprocessor/seq/for_each_i.hpp>

// Code!
namespace Gambit
{
  namespace Printers
  {

    class nonePrinter : public BasePrinter
    {
      public:
        // Constructor
        nonePrinter(const Options& options, BasePrinter* const primary)
        : BasePrinter(primary,options.getValueOrDef<bool>(false,"auxilliary"))
        {
          // This printer requires no setup
        }

        /// Virtual function overloads:
        ///@{

        // Initialisation function
        // Run by dependency resolver, which supplies the functors with a vector of VertexIDs whose requiresPrinting flags are set to true.
        void initialise(const std::vector<int>&) {}
        void reset(bool) {}
        void finalise(bool) {}
        void flush() {} // No buffers with this printer, so flush function doesn't need to do anything

        // Permanently unavailable for this printer
        Options resume_reader_options()
        {
          std::ostringstream err;
          err << "The none printer is intrinsically incapable of reading from previous output, since the previous output was never printed." << std::endl;
          printer_error().raise(LOCAL_INFO, err.str());
          return Options();
        }

        ///@}

        // PRINT FUNCTIONS
        //----------------------------
        // Need to define one of these for every type we want to print!
        // Could use macros again to generate identical print functions
        // for all types that have a << operator already defined.

        ///@{ Print functions
        #define DECLARE_PRINT(r,data,i,elem) \
        void _print(elem const&, const std::string&, const int, const uint, const ulong) { /* do nothing */};

        BOOST_PP_SEQ_FOR_EACH_I(DECLARE_PRINT, , ASCII_TYPES)
        #ifndef SCANNER_STANDALONE
          BOOST_PP_SEQ_FOR_EACH_I(DECLARE_PRINT, , ASCII_MODULE_BACKEND_TYPES)
        #endif
        #undef DECLARE_PRINT
        ///@}

      private:
    };

    // Register printer so it can be constructed via inifile instructions
    // First argument is string label for inifile access, second is class from which to construct printer
    LOAD_PRINTER(none, nonePrinter)

  } // end namespace Printers
} // end namespace Gambit

#endif //ifndef __none_printer_hpp__
