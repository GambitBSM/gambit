//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  SQLite printer/reader base class declaration
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2018 Dec
///
///  *********************************************

#ifndef __sqlitebase_hpp__
#define __sqlitebase_hpp__

#include <map>
#include <string>

// Gambit
#include "gambit/Utils/util_functions.hpp" // Need Utils::ci_less to make map find() functions case-insensitive, since SQLite is case insensitive

// Forward declare sqlite3 objects
struct sqlite3;
struct sqlite3_stmt;

namespace Gambit
{
  namespace Printers
  {
    // Compute unique integer from two integers
    // We use this to turn MPI rank and point ID integers into an SQLite row ID
    inline std::size_t pairfunc(const std::size_t i, const std::size_t j)
    {
        // The Cantor pairing function should be good enough for this purpose I think
        // If we exceed the maximum size of size_t then we'll have to use a more space-efficient pairing function
        return ((i+j)*(i+j+1))/2 + j;
    }


    // Type of function pointer for SQLite callback function
    typedef int sql_callback_fptr(void*, int, char**, char**);

    // Callback function for counting columns in table
    int col_name_callback(void* colmap_in, int /*count*/, char** data, char** /* columns */);

    // Matching of SQL types to C++ types
    typedef long long int llint;
    typedef std::string str;
    #define SQLITE_CPP_TYPES (llint) (double) (str)
    template<typename T> std::string cpp2sql();
    template<> std::string cpp2sql<long long int>();
    template<> std::string cpp2sql<double>();
    template<> std::string cpp2sql<std::string>();

    // Matching of SQLite "type codes" to SQL types
    // Names should match results of cpp2sql above
    std::map<unsigned int,std::string> define_typecodes();
    extern const std::map<unsigned int,std::string> typecode2sql;

    // Map from all SQLite "suggestion" types into the five "base" SQLite types
    // Used for type comparisons.
    std::map<std::string,std::string, Utils::ci_less> fill_SQLtype_to_basic();
    extern const std::map<std::string,std::string, Utils::ci_less> SQLtype_to_basic;

    // Compare SQLite data types to see if they are equivalent to the same basic 'affinity' for a column
    bool SQLite_equaltypes(const std::string& type1, const std::string& type2);

    // Returns new iterator pointing to next element
    template <typename Iter>
    Iter next_el(Iter iter)
    {
        return ++iter;
    }

    // Return a comma unless iterator is the last in the supplied iterable
    // (or if it points to end())
    template <typename Iter, typename Cont>
    std::string comma_unless_last(Iter it, const Cont& c)
    {
       std::string out("");
       if((it == c.end()) || (next_el(it) == c.end()))
       { /* this is the last element or end(), do nothing */ }
       else
       { out = ","; }
       return out;
    }

    /// SQLite base class for both reader and writer
    class SQLiteBase
    {
      public:
        SQLiteBase();
        ~SQLiteBase();

      protected:
        std::string get_database_file();
        std::string get_table_name();
        std::string get_metadata_table_name();
        void set_table_name(const std::string& table_name);
        void set_metadata_table_name(const std::string& metadata_table_name);

        // Verify that the outbase database is open and the results table exists
        void require_output_ready();

        // Open database and 'attach' it to this object
        // A database will be created if it doesn't exist
        void open_db(const std::string&, char access='r');

        // Close the database file that is attached to this object
        void close_db();

        // Get the pointer to the target SQLite database
        sqlite3* get_db();

        // Dump a row of results to std::cout
        void cout_row(sqlite3_stmt* tmp_stmt);

        // Check that the required table exists
        // Sets 'table_exists' to true if successful, otherwise throws error
        void check_table_exists();

        // Sets the 'table_exists' flag to true
        void set_table_exists();

        // Get names and types for all columns in the target table
        // (Output is a map from names to types)
        std::map<std::string, std::string, Utils::ci_less> get_column_info();

        // Submit an SQL statement to the database
        int submit_sql(const std::string& local_info, const std::string& sqlstr, bool allow_fail=false, sql_callback_fptr callback=NULL, void* data=NULL, char **zErrMsg=NULL);

      private:
        // Path to SQLite database file
        std::string database_file;

        // Name of data table to be accessed
        std::string table_name;
        std::string metadata_table_name;

        // Pointer to target sqlite3 database
        sqlite3* db;

        // Bool to record if we already have a database file open
        bool db_is_open;

        // Bool to record if the table to be accessed exists yet
        bool table_exists;

    };

  }
}

#endif
