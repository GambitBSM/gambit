//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  SQLite printer retriever class definitions
///  This is a class accompanying the SQLitePrinter
///  which takes care of *reading* from output
///  created by the SQLitePrinter.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk))
///  \date 2018 Dec
///
///  *********************************************

#include <sqlite3.h> // SQLite3 C interface

#include "gambit/Printers/baseprinter.hpp"
#include "gambit/Printers/printers/sqlitebase.hpp"
#include "gambit/Printers/printers/sqlitetypes.hpp"

#include <boost/preprocessor/seq/for_each_i.hpp>

#ifndef __sqlite_reader_hpp__
#define __sqlite_reader_hpp__

namespace Gambit
{
  namespace Printers
  {

    class SQLiteReader : public BaseReader, public SQLiteBase
    {
      public:
        SQLiteReader(const Options& options);
        ~SQLiteReader();

        /// @{ Base class virtual interface functions
        virtual void reset(); // Reset 'read head' position to first entry
        virtual ulong get_dataset_length(); // Get length of input dataset
        virtual PPIDpair get_next_point(); // Get next rank/ptID pair in data file
        virtual PPIDpair get_current_point(); // Get current rank/ptID pair in data file
        virtual ulong    get_current_index(); // Get a linear index which corresponds to the current rank/ptID pair in the iterative sense
        virtual bool eoi(); // Check if 'current point' is past the end of the data file (and thus invalid!)
        /// Get type information for a data entry, i.e. defines the C++ type which this should be
        /// retrieved as, not what it is necessarily literally stored as in the output.
        virtual std::size_t get_type(const std::string& label);
        virtual std::set<std::string> get_all_labels(); // Get all dataset labels
        /// @}

        /// Retrieve functions
        using BaseReader::_retrieve; // Tell compiler we are using some of the base class overloads of this on purpose.
        #define DECLARE_RETRIEVE(r,data,i,elem) bool _retrieve(elem&, const std::string&, const uint, const ulong);
        BOOST_PP_SEQ_FOR_EACH_I(DECLARE_RETRIEVE, , SQL_TYPES)
        #ifndef SCANNER_STANDALONE
          BOOST_PP_SEQ_FOR_EACH_I(DECLARE_RETRIEVE, , SQL_BACKEND_TYPES)
        #endif
        #undef DECLARE_RETRIEVE

      private:

        // Flag that will be set to false when the end of the input table selection is reached
        bool eoi_flag;

        // SQL statement variable used to access current row of table iteration
        sqlite3_stmt *stmt;

        // Variables needed by e.g. postprocessor to track where we are in the database
        ulong current_dataset_index; // index in input dataset of the current read-head position
        PPIDpair current_point;      // PPID of the point at the current read-head position

        // Map from column name to column position
        std::map<std::string, std::size_t, Utils::ci_less> column_map;

        // Map from column name to column type
        std::map<std::string, std::string, Utils::ci_less> column_types;

        // Move the SQL loop ahead one position
        void move_to_next_point();

        // Build map from column name to column position
        void build_column_map();

        // Safely access the column_map and throw informative error when column is missing
        std::size_t get_col_i(const std::string& col_name);

        // Template function for retrieving SQLite column data as various types
        // Need specialisations for each type in SQLITE_CPP_TYPES
        template<typename T> T get_sql_col(const std::string& col_name);

        /// "Master" templated retrieve function.
        /// All other retrieve functions should ultimately call this one
        template<class T>
        bool _retrieve_template(T& out, const std::string& label, int /*aux_id*/, const uint rank, const ulong pointID)
        {
            bool valid(false);
            // The assumption made here is that we are iterating through the database, rather
            // than attempting to access various random table entries constantly. So this reader object
            // steps through the database. This means that most of the time, our sql cursor will already
            // be pointing at the correct rank/pointID pair.
            // In fact, for now at least, I think I will make it an ERROR if the correct rank/pointID is not
            // at this cursor location. TODO: Consider whether more general access will be useful in the future.
            if(not eoi())
            {
                if(current_point != PPIDpair(pointID,rank))
                {
                    std::stringstream err;
                    err<<"Attempted to retrieve '"<<label<<"' from point ("<<rank<<", "<<pointID<<"), however the SQLiteReader object is not presently accessing this point (the 'current_point' is ("<<current_point.rank<<", "<<current_point.pointID<<")). At present this object is only really designed for use by the postprocessor scanner, if you have created another scanner that requires more general reader access then please make a feature request.";
                    printer_error().raise(LOCAL_INFO, err.str());
                }
                // Otherwise we are good to go!

                // First need to check if the result is 'null' for this entry
                int typecode = sqlite3_column_type(stmt, get_col_i(label));
                auto it = typecode2sql.find(typecode);
                if( it == typecode2sql.end() )
                {
                    std::stringstream err;
                    err<<"Received unrecognised type code from sqlite_column_type! (typecode="<<typecode<<")";
                    printer_error().raise(LOCAL_INFO, err.str());
                }
                else if( it->second=="NULL" )
                {
                    // No data in this column.
                    valid = false;
                }
                else if(not SQLite_equaltypes(cpp2sql<T>(),it->second) )
                {
                    // Seems to be data in the column, but type is not correct!
                    // Retrieve could still work since SQLite can do conversions,
                    // but this probably indicates a bug somewhere in this printer.
                    std::stringstream err;
                    err<<"Attempted to retrieve data from table column '"<<label<<"' as type "<<cpp2sql<T>()<<", but SQLite says that the data has type '"<<it->second<<"'. These must map to the same basic column affinity (these were "<<SQLtype_to_basic.at(cpp2sql<T>())<<" and "<<SQLtype_to_basic.at(it->second)<<" respectively)! This is probably a bug in the SQLiteReader 'retrieve' routines, please report it.";
                    printer_error().raise(LOCAL_INFO, err.str());
                }
                else
                {
                    // Do the retrieval!
                    out = get_sql_col<T>(label);
                    valid = true;
                }
            }
            return valid;
        }

    };

    // Template function specialisations for retrieving SQLite column data as various types
    // Need one for each type in SQLITE_CPP_TYPES
    template<> long long int SQLiteReader::get_sql_col<long long int>(const std::string&);
    template<> double        SQLiteReader::get_sql_col<double>       (const std::string&);
    template<> std::string   SQLiteReader::get_sql_col<std::string>  (const std::string&);

    // Register reader so it can be constructed via inifile instructions
    // First argument is string label for inifile access, second is class from which to construct printer
    LOAD_READER(sqlite, SQLiteReader)

  }
}

#endif
