//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  This is a minimal (pure virtual) precursor 
///  to the printer base class, for use only in 
///  ScannerBit. This helps to minimize the parts 
///  of the printers which are essential for 
///  ScannerBit to run.
///
///  Now includes base 'reader' class as well,
///  for retrieving data from printer output
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

#ifndef __base_base_printer_hpp__
#define __base_base_printer_hpp__

// Standard libraries
#include <string>
#include <sstream>
#include <vector>

// Boost
#include <boost/preprocessor/seq/for_each.hpp>

// Gambit
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Printers/printer_id_tools.hpp"

namespace Gambit
{
  // Forward declarations needed for some of the _print/_retrieve functions
  class ModelParameters;

  namespace Printers 
  {
    // Convenienece typedefs for printers
    typedef unsigned int      uint;
    typedef unsigned long int ulong;
    typedef std::map<std::string,double> map_str_dbl; // can't have commas in macro input

    class BaseBasePrinter  
    {
      public:
        BaseBasePrinter(): printer_enabled(true), _print_timing(false) {}
        BaseBasePrinter(bool p): printer_enabled(true), _print_timing(p) {}
        virtual ~BaseBasePrinter() {}
        /// Function to signal to the printer to write buffer contents to disk
        //virtual void flush() {}; // TODO: needed?

        /// Signal printer to reset contents, i.e. delete old data in preperation for replacement
        virtual void reset(bool force=false) = 0;

        /// Retrieve MPI rank
        virtual int getRank() = 0;

        /// Signal printer that scan is finished, and final output needs to be performed
        virtual void finalise(bool abnormal=false) = 0;

        /// "Turn off" printer; i.e. calls to print functions will do nothing while this is active
        void disable() { printer_enabled = false; }

        /// "Turn on" printer; print calls will work as normal.
        void enable() { printer_enabled = true; }
 
        /// Bool to check whether timing data should be printed.
        /// Note: this doesn't do anything in the printer itself, it is just a kind
        /// global variable that other parts of the code should check when deciding
        /// whether to print timing data. Currently the printers cannot tell
        /// themselves what kind of data is being printed, so they cannot turn off
        /// the printing of timing data internally.
        bool printTiming() { return _print_timing; }

        // Printer dispatch function. If a virtual function override exists for
        // the print type, info is passed on, otherwise the function call is resolved
        // to a default function which raises an informative runtime error explaining
        // that the type is not printable.
        template<typename T>
        void print(T const& in, const std::string& label,
                   const int vertexID, const uint rank,
                   const ulong pointID)
        {
          if(printer_enabled) _print(in, label, vertexID, rank, pointID);
        }

        // Overload which automatically determines a unique ID code
        // based on the label. Used by scanner plugin.
        template<typename T>
        inline void print(T const& in, const std::string& label,
                           const uint rank,
                           const ulong pointID)
        {
          print(in, label, get_aux_param_id(label), rank, pointID);
        }

      protected:
        /// Flag to check if print functions are enabled or disabled
        bool printer_enabled;

        /// Flag for external code to check to see if it should print
        /// timing data or not. 
        bool _print_timing;

        /// Default _print function. Throws an error if no matching 
        /// virtual function for the type of the attempted print is
        /// found.
        template<typename T>
        void _print(T const&, const std::string& label,
                    const int vertexID, const uint,
                    const ulong)
        {
          std::ostringstream err;                               
                                                                
          err << "Attempted to print a functor whose return type "
              << "is not registered as being printable. "
              << "If you really want to print this functor, you must "
              << "add its return type to the PRINTABLE_TYPES sequence "
              << "in \"gambit/Elements/printable_types.hpp\". You will then have "
              << "to define a print function for it in whatever printer "
              << "you are using (see documentation for GAMBIT printers)."
              << "\n  Available info for this print attempt..."                
              << "\n   Label      : " << label                  
              << "\n   vertexID   : " << vertexID               
              << "\n   Type       : " << STRINGIFY(T);       
          printer_error().raise(LOCAL_INFO,err.str());         
        }

        /// Declarations of minimal print functions needed by ScannerBit
        #define SCANNER_PRINTABLE_TYPES \
          (bool)                     \
          (int)(uint)(long)(ulong)   \
          (float)(double)            \
          (std::vector<bool>)        \
          (std::vector<int>)         \
          (std::vector<double>)      \
          (map_str_dbl)              \

        // Virtual print methods for base printer classes
        #define VPRINT(r,data,elem)                                \
        virtual void _print(elem const&, const std::string& label, \
                           const int vertexID, const uint /*rank*/, \
                           const ulong /*pointID*/)               \
        {                                                         \
          std::ostringstream err;                                 \
                                                                  \
          err << "No print function override has been "           \
              << "\ndefined for this type (for whatever printer"  \
              << "\nclass the current printer comes from)"        \
              << "\n  Dumping available info..."                  \
              << "\n   Label      : " << label                    \
              << "\n   vertexID   : " << vertexID                 \
              << "\n   Type       : " << STRINGIFY(elem);         \
          printer_error().raise(LOCAL_INFO,err.str());          \
        }

        #define ADD_VIRTUAL_PRINTS(TYPES) BOOST_PP_SEQ_FOR_EACH(VPRINT, _, TYPES)

        // Add the base virtual functions for registered printable and
        // retrievable types, to be overloaded in each printer.
        ADD_VIRTUAL_PRINTS(SCANNER_PRINTABLE_TYPES) 

    };

        /// @{ Printer READ interface
        ///    For reading data back *into* Gambit from a printer output file.
        ///    This is mainly designed for performing "reweighting" of scans, 
        ///    e.g. loading up previously scanned points in order to recompute
        ///    some new observables or likelihoods.
        ///
        ///    It is pretty hard to permit generic read-in of ALL data, so for
        ///    now I will focus on just getting the parameter data. If we read
        ///    in other data we will have to do some gnarly stuff like
        ///    automatically wrap it into functors, and to appropriate
        ///    capabilities etc, in order for it to be usable in other in
        ///    other calculations. So for now, the idea will simply be to
        ///    take the parameter values and recompute everything anew that is
        ///    needed for calculating the new likelihoods or whatever.
        ///    Otherwise it is kind of a nightmare to e.g. reconstruct a
        ///    Spectrum object from printer data, would need special module
        ///    functions and so on that know how to put all the data back
        ///    together. I guess it is possible if we give module writers
        ///    access to the printer read interface so that they can do this
        ///    task themselves... but will leave this aside for now.

        ///    So, need:
        ///      1. some way to iterate through printer output
        ///      2. a generic function that can read in a particular entry, 
        ///         knowing e.g. the following:
        ///       Column 6: #NormalDist_parameters @NormalDist::primary_parameters::mu
        ///         and can put it back into some Gambit object, e.g.
        ///       Parameters: 
        ///         NormalDist:
        ///           mu: 
        ///           sigma:
        ///
        ///       I guess this latter part is scannerbits responsibility, i.e.
        ///       it will have the parameter object and need to fill it with
        ///       numbers that it gets from the printer.
        ///
        ///                functor (model) name    parameter name
        ///      str key = act_it->first + "::" + *par_it;
        ///

    class BaseBaseReader
    {
      public:
        virtual ~BaseBaseReader() {};

        virtual std::pair<uint, ulong> get_current_point() = 0; // Get current rank/ptID pair (i.e. whatever get_next_point() last output)
        virtual std::pair<uint, ulong> get_next_point() = 0; // Get next rank/ptID pair in data file
        virtual bool eoi() = 0; // Check if 'current point' is past the end of the data file (and thus invalid!)

        /// Printer-retrieve dispatch function. If a virtual function override exists for
        /// the retrieve type, info is passed on, otherwise the function call is resolved
        /// to a default function which raises an informative runtime error explaining
        /// that the type is not retrievable.
        ///
        /// Note; this is not quite enough because the entries in the printer output need
        /// not be one-to-one with the printed object, e.g. vectors currently go into 
        /// a series of indexed output slots. Hard for e.g. scanner plugins to know the
        /// label that they need to ask for...
        ///
        /// Perhaps return a map of results matching the label? Or vector? Perhaps both
        /// in different cases...
        ///
        /// Note, cannot overload based on return type, so need to use an "out" parameter
        template<typename T>
        void retrieve(T& out, const std::string& label, const uint rank, const ulong pointID)
        {
          _retrieve(out, label, rank, pointID);
        }

        /// Overload for 'retrieve' that uses the current point as the input for rank/pointID
        template<typename T>
        void retrieve(T& out, const std::string& label)
        {
          std::pair<uint, ulong> pt = get_current_point();
          retrieve(out, label, pt.first, pt.second);
        }

      protected:
        /// Default _retrieve function. Throws an error if no virtual
        /// function matching the type of the attempted retrieval is
        /// found.        
        template<typename T>
        void _retrieve(T& out, const std::string& label, const uint rank, const ulong pointID)
        {
          std::ostringstream err;                               
                                                                
          err << "Attempted to retrieve a print result as an unregistered type!"
              << "If you really want to retrieve a result as this type, you must "
              << "add the type to the RETRIEVABLE_TYPES sequence "
              << "in \"gambit/Elements/printable_types.hpp\". You will then have "
              << "to define a retrieve function for it in whatever printer "
              << "you are using (see documentation for GAMBIT printers)."
              << "\n  Available info for this retrieve attempt..."                
              << "\n   Label      : " << label                  
              << "\n   Type       : " << STRINGIFY(T);       
          printer_error().raise(LOCAL_INFO,err.str());         
        }
      
        #define SCANNER_RETRIEVABLE_TYPES  \
        (double)                   \
        (std::string)              \
        (std::vector<double>)      \
        (map_str_dbl)              \
        (ModelParameters)          \

        // Virtual retrieval methods for base printer classes
        #define VRETRIEVE(r,data,elem)            \
        virtual void _retrieve(elem& /*output*/,  \
                       const std::string& label,  \
                       const uint /*rank*/,       \
                       const ulong /*pointID*/    \
                       )                          \
        {                                                         \
          std::ostringstream err;                                 \
                                                                  \
          err << "No retrieve function override has been "           \
              << "\ndefined for this retrieval type (for whatever printer"  \
              << "\nclass the current printer comes from)"        \
              << "\n  Dumping available info..."                  \
              << "\n   Label      : " << label                    \
              << "\n   Type       : " << STRINGIFY(elem);         \
          printer_warning().raise(LOCAL_INFO,err.str());          \
        }

        #define ADD_VIRTUAL_RETRIEVALS(TYPES) BOOST_PP_SEQ_FOR_EACH(VRETRIEVE, _, TYPES)

        // Add the base virtual functions for registered printable and
        // retrievable types, to be overloaded in each printer.
        ADD_VIRTUAL_RETRIEVALS(SCANNER_RETRIEVABLE_TYPES) 
    };
 
  } //end namespace Printers
} // end namespace Gambit


#endif //ifndef __base_base_printer_hpp__
