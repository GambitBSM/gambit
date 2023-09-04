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

      public:
        BasePrinterManager() : resume(false) {}
        BasePrinterManager(bool r) : resume(r) {}

        /// Getter for "resume" mode flag
        bool resume_mode() { return resume; }

        /// Setter for "resume" mode flag
        /// (printer may override user choice if no previous output exists)
        void set_resume_mode(bool rflag) { resume = rflag; }

        /// Create auxiliary printer object
        virtual void new_stream(const std::string&, const Options&) = 0;

        /// Create reader object
        virtual void new_reader(const std::string&, const Options&) = 0;

        /// Create for reader object for previous print output ("resume reader")
        virtual void create_resume_reader() = 0;

        /// Getter for auxiliary printer objects
        virtual BaseBasePrinter* get_stream(const std::string& = "") = 0;

        /// Getter for readers
        virtual BaseBaseReader* get_reader(const std::string&) = 0;

        /// Checker for reader existence
        virtual bool reader_exists(const std::string&) = 0;

        /// Delete reader and printer objects (does not harm output, just deletes the objects)
        virtual void delete_stream(const std::string& = "") = 0;
        virtual void delete_reader(const std::string&) = 0;
 
        /// Instruct printers that scan has finished and to perform cleanup
        virtual void finalise(bool abnormal=false) = 0;

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
