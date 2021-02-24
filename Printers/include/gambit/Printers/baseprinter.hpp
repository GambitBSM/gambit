//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declaration and definition of printer base class
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 Jul, Sep
///  \date 2014 Jan
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  *********************************************

#ifndef __base_printer_hpp__
#define __base_printer_hpp__

// Standard libraries
#include <vector>

// Gambit
#include "gambit/Printers/basebaseprinter.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/boost_fallbacks.hpp"
#include "gambit/Utils/factory_registry.hpp"
#include "gambit/Utils/model_parameters.hpp"
#include "gambit/Utils/export_symbols.hpp"

#include "gambit/Logs/logmaster.hpp"

// Boost
#include <boost/preprocessor/seq/for_each_i.hpp>

// Printable types
#ifndef SCANNER_STANDALONE
   // If we are in a main gambit executable, we need to know all the GAMBIT printable types
   #include "gambit/Elements/printable_types.hpp"
#else
   // Otherwise, we are in the ScannerBit standalone executable and need only a limited set.
   #include "gambit/ScannerBit/printable_types.hpp"

   // Already dealt with in basebaseprinter? Can possibly do this to deal with
   // lack of new types, rest will be inherited anyway.
   #define PRINTABLE_TYPES SCANNER_PRINTABLE_TYPES
   #define RETRIEVABLE_TYPES SCANNER_RETRIEVABLE_TYPES
#endif

// This macro registers each printer so that they can be constructed automatically from inifile instructions
#define LOAD_PRINTER(tag, ...) REGISTER(printer_creators, tag, __VA_ARGS__)

// This macro registers each reader so that they can be constructed automatically from inifile instructions
#define LOAD_READER(tag, ...) REGISTER(reader_creators, tag, __VA_ARGS__)

// Code!
namespace Gambit
{
  namespace Printers
  {

    // Helper function for parsing ModelParameters label strings.
    bool parse_label_for_ModelParameters(const std::string& fulllabel, const std::string& modelname, std::string& out, std::string& rest, bool case_sensitive=true);

    /// Helper function for parsing Spectrum label strings
    bool parse_label_for_spectrum_entry(const std::string& fulllabel, const std::string& req_capability, const std::string& req_module, const std::string& req_function, std::string& outname, std::string& outtag, std::string& labelroot, bool case_sensitive=true);

    /// For debugging; print to stdout all the typeIDs for all types.
    void printAllTypeIDs(void);

    /// Declare specialisations of type ID getters
    #define DECLARE_GETTYPEID(r,data,i,elem) \
      template<> \
      EXPORT_SYMBOLS std::size_t getTypeID<elem>(void);
    BOOST_PP_SEQ_FOR_EACH_I(DECLARE_GETTYPEID, _, PRINTABLE_TYPES)
    #undef DECLARE_GETTYPEID

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //% Printer class declarations                          %
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    /// BASE PRINTER CLASS
    class BasePrinter: public BaseBasePrinter
    {
      private:
        BasePrinter* primary_printer;
        bool is_aux;

      public:
        BasePrinter()
          : primary_printer(NULL)
          , is_aux(false)
       {}

        BasePrinter(BasePrinter* const primary, bool is_aux_IN)
          : primary_printer(primary)
          , is_aux(is_aux_IN)
       {}

        /// Destructor
        virtual ~BasePrinter() {}

        /// Initialisation function
        // Run by dependency resolver, which supplies the functors with a vector of VertexIDs whose requiresPrinting flags are set to true. (TODO: probably extend this to be a list of functors THIS printer is supposed to print, since we may want several printers handling different functors, for SLHA output or some such perhaps).
        virtual void initialise(const std::vector<int>&) = 0;

        /// Signal printer to flush data in buffers to disk
        /// Printers should do this automatically as needed, but this is useful if a scanner is printing
        /// a bunch of data as a batch, to make sure it is all on disk after the batch is done.
        virtual void flush() = 0;        

        // Get options required to construct a reader object that can read
        // the previous output of this printer.
        virtual Options resume_reader_options() = 0;

        /// Set this as an auxilliary printer
        void set_as_aux() { is_aux = true; }

        /// Helper initialisation for auxilliary printers
        /// Will be run when the auxilliary printer is
        /// created by a PrinterManager.
        /// Define override of this if two-stage initialisation is needed
        virtual void auxilliary_init() {};

        BasePrinter* get_primary_printer()
        {
          if(not is_aux)
          {
            std::ostringstream err;
            err << "Error! Tried to retrieve pointer to primary printer from a "
                << "printer object not flagged as auxilliary!";
            printer_error().raise(LOCAL_INFO,err.str());
          }
          else if(primary_printer==NULL)
          {
            std::ostringstream err;
            err << "Error! Tried to retrieve pointer to primary printer, but it "
                << "is NULL! Something has gone wrong in the initialisation of "
                << "the printer system.";
            printer_error().raise(LOCAL_INFO,err.str());
          }
          return primary_printer;
        }
        bool is_auxilliary_printer() { return is_aux; }


        // Printer dispatch function. This is defined already
        // in the BaseBasePrinter class, but I think I need it
        // here as well so that that BasePrinter version can
        // detect the new virtual function overloads which exist
        // in this class.
        template<typename T>
        void print(T const& in, const std::string& label,
                   const int vertexID, const uint rank,
                   const ulong pointID)
        {
          if(printer_enabled) _print(in, label, vertexID, rank, pointID);
        }

        // Overload which automatically determines a unique ID code
        // based on the label.
        template<typename T>
        void print(T const& in, const std::string& label,
                   const uint rank,
                   const ulong pointID)
        {
          if(printer_enabled) _print(in, label, rank, pointID);
        }

      protected:
        using BaseBasePrinter::_print; //unhide the default function in the base class

        // We need to have a virtual print method for every type that we want to
        // be able to print. The list of these types is maintained in
        // "gambit/Elements/printable_types.hpp"
        // Run the macro; add all the print functions
        ADD_VIRTUAL_PRINTS(PRINTABLE_TYPES)

    };

    /// BASE READER CLASS
    class BaseReader: public BaseBaseReader
    {
      public:
        BaseReader() {}

        /// Destructor
        virtual ~BaseReader() {}

        /// Reimplement overload for 'retrieve' that uses the current point as the input for rank/pointID
        // Need to do this because otherwise we end up using the scanner-only templates for the retrieves,
        // rather than the full set available here.
        template<typename T>
        bool retrieve(T& out, const std::string& label)
        {
          PPIDpair pt = get_current_point();
          return retrieve(out, label, pt.rank, pt.pointID);
        }

        // retrieve function dispatch
        template<typename T>
        bool retrieve(T& out, const std::string& label, const uint rank, const ulong pointID)
        {
          return _retrieve(out, label, rank, pointID);
        }

        /// Retrieve and directly print data to new output
        bool retrieve_and_print(const std::string& in_label, const std::string& out_label, BaseBasePrinter& printer, const uint rank, const ulong pointID);

      protected:
        using BaseBaseReader::_retrieve; //unhide the default function in the base class

        // We need to have a virtual 'retrieve' method for every type that we want to
        // be able to retrieve. The list of these types is maintained in
        // "gambit/Elements/printable_types.hpp"
        // Run the macro; add all the print functions
        ADD_VIRTUAL_RETRIEVALS(RETRIEVABLE_TYPES)

    };


    /// Maps in which to keep factory functions for the printers (printer_creators)
    /// and readers (reader_creators)
    // (uses the same machinery as in priors.hpp)
    // Note: Arguments to e.g printer_creators need to match constructor for printer object
    // e.g. printer_creators.at(tag)(args...)
    // (this is set up by the typedef)
    gambit_registry
    {
            typedef BasePrinter* create_printer_function(const Options&, BasePrinter* const&);
            reg_elem <create_printer_function> printer_creators;

            typedef BaseReader* create_reader_function(const Options&);
            reg_elem <create_reader_function> reader_creators;
    }

  } //end namespace Printers
} // end namespace Gambit


#endif //ifndef __base_printer_hpp__
