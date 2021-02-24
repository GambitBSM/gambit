//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  "cout" printer class declaration
///
///  An extremely simple printer which just outputs
///  the results of functor evaluations to cout.
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


#ifndef __cout_printer_hpp__
#define __cout_printer_hpp__

// Standard libraries
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>

// Gambit
#include "gambit/Printers/baseprinter.hpp"
#include "gambit/Printers/printers/asciitypes.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/stream_overloads.hpp"

// BOOST_PP
#include <boost/preprocessor/seq/for_each_i.hpp>

// Code!
namespace Gambit
{
  namespace Printers
  {

    class coutPrinter : public BasePrinter
    {
      public:
        /// Constructor (for construction via inifile options)
        coutPrinter(const Options&, BasePrinter* const primary = NULL);

        /// Tasks common to the various constructors
        void common_constructor(const Options&);

        /// Virtual function overloads:
        ///@{

        // Initialisation function
        // Run by dependency resolver, which supplies the functors with a vector of VertexIDs whose requiresPrinting flags are set to true.
        void initialise(const std::vector<int>&);
        void reset(bool force=false);
        void finalise(bool abnormal=false);
        void flush() {}; // No buffers with this printer, so flush function doesn't need to do anything

        // Permanently unavailable for this printer
        Options resume_reader_options();

        ///@}

        /// @{ coutPrinter specific functions

        /// Perform any point-specific logic
        void check_point(unsigned int mpirank, unsigned long pointID);

        /// @}

        // PRINT FUNCTIONS
        //----------------------------
        // Need to define one of these for every type we want to print!
        // Could use macros again to generate identical print functions
        // for all types that have a << operator already defined.

        ///@{ Print functions
        using BasePrinter::_print; // Tell compiler we are using some of the base class overloads of this on purpose.
        #define DECLARE_PRINT(r,data,i,elem) void _print(elem const&, const std::string&, const int, const uint, const ulong);
        BOOST_PP_SEQ_FOR_EACH_I(DECLARE_PRINT, , ASCII_TYPES)
        #ifndef SCANNER_STANDALONE
          BOOST_PP_SEQ_FOR_EACH_I(DECLARE_PRINT, , ASCII_BACKEND_TYPES)
        #endif
        #undef DECLARE_PRINT
        ///@}

        /// Helper print functions
        // Used to reduce repetition in definitions of virtual function overloads
        // (useful since there is no automatic type conversion possible)
        // This works for any type that already has an appropriate stream operator defined.
        template<class T>
        void template_print(T const& value, const std::string& label, const int /*IDcode*/, const unsigned int mpirank, const unsigned long pointID)
        {
           check_point(mpirank,pointID);
           std::cout << label << ": " << value << std::endl;
        }

      private:
    };

    // Register printer so it can be constructed via inifile instructions
    // First argument is string label for inifile access, second is class from which to construct printer
    LOAD_PRINTER(cout, coutPrinter)

  } // end namespace Printers
} // end namespace Gambit

#endif //ifndef __ascii_printer_hpp__
