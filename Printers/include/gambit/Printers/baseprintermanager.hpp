//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Pure virtual base class for PrinterManager
///  This provides a minimal interface to the
///  PrinterManager class for use in ScannerBit
///  i.e. from here we do not manage the printer
///  streams (much), we merely provide access to them.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Feb
///
///  *********************************************

#ifndef __baseprintermanager_hpp__
#define __baseprintermanager_hpp__

#include <string>
#include "gambit/Utils/mpiwrapper.hpp"
#include "gambit/Utils/yaml_options.hpp"

namespace Gambit
{
  namespace Printers 
  {
    /// Forward declarationa
    class BaseBasePrinter;
    class BaseBaseReader;

    /// Manager class for creating printer objects  
    class BasePrinterManager 
    {
      private:
        /// Flag for "resume" mode
        bool resume;

        /// Flag for printing timing data
        bool _print_timing;

      public:
        BasePrinterManager() : resume(false), _print_timing(false) {}
        BasePrinterManager(bool r, bool p) : resume(r), _print_timing(p) {}

        /// Getter for "resume" mode flag
        bool resume_mode() { return resume; }

        /// Create auxiliary printer object
        virtual void new_stream(const std::string&, const Options&) = 0;

        /// Create reader object
        virtual void new_reader(const std::string&, const Options&) = 0;

        /// Getter for auxiliary printer objects
        virtual BaseBasePrinter* get_stream(const std::string& = "") = 0;

        /// Getter for readers
        virtual BaseBaseReader* get_reader(const std::string&) = 0;

        /// Instruct printers that scan has finished and to perform cleanup
        virtual void finalise(bool abnormal=false) = 0;

        /// Bool to check whether timing data should be printed.
        /// Note: this doesn't do anything in the printer itself, it is just a kind
        /// global variable that other parts of the code should check when deciding
        /// whether to print timing data. Currently the printers cannot tell
        /// themselves what kind of data is being printed, so they cannot turn off
        /// the printing of timing data internally.
        bool printTiming() { return _print_timing; }

        /// For debugging: check up on mpi
        /// For debugging: check up on MPI
        //#ifdef WITH_MPI
        //bool Is_MPI_initialized()  { return GMPI::Is_initialized(); }
        //int getRank()  { GMPI::Comm comm; return comm.Get_rank(); }
        //#endif
    };


  }
}

#endif
