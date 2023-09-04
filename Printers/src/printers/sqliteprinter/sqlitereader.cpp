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

#include "gambit/Utils/boost_fallbacks.hpp"
#include "gambit/Printers/printers/sqlitereader.hpp"
#include "gambit/Utils/util_functions.hpp"

// Activate extra debug output on errors
#define SQL_DEBUG

namespace Gambit
{
  namespace Printers
  {
     
     SQLiteReader::SQLiteReader(const Options& options)
     : BaseReader()
     , SQLiteBase()
     , stmt(NULL)
     , current_dataset_index(0)
     , current_point(nullpoint)
     {
        // Open the database file 
        open_db(options.getValue<std::string>("file"),'r');
 
        // Tell the base class what table we want to access
        set_table_name(options.getValue<std::string>("table"));
      
        // Make sure that the requested table exists
        check_table_exists();

        // Determine the types of all columns in the input table
        column_types = get_column_info();
        build_column_map();        

        // Set up the reader loop
        reset();
     }

     SQLiteReader::~SQLiteReader()
     {
         if(not eoi() and stmt!=NULL)
         {
             // Finalise any existing loop
             sqlite3_finalize(stmt); 
         }
     }

     /// @{ Template function specialisations for retrieving SQLite column data as various types
     template<>
     long long int SQLiteReader::get_sql_col<long long int>(const std::string& col_name)
     {
         return sqlite3_column_int64(stmt, get_col_i(col_name)); 
     }

     template<>
     double SQLiteReader::get_sql_col<double>(const std::string& col_name)
     {
         return sqlite3_column_double(stmt, get_col_i(col_name)); 
     }

     template<>
     std::string SQLiteReader::get_sql_col<std::string>(const std::string& col_name)
     {
         char* p = (char*)sqlite3_column_text(stmt, get_col_i(col_name));
         if(p==NULL)
         {
             std::stringstream err;
             err<<"Pointer returned by sqlite3_column_text was NULL!";
             printer_error().raise(LOCAL_INFO, err.str());
         }
         return std::string(p); 
     }
     /// @}

     // Determine mapping from column names to indices
     void SQLiteReader::build_column_map()
     {
         // We will SELECT the columns according to the results of get_column_info,
         // so there is no need to directly inspect the table again.
         require_output_ready();
         column_map.clear();
         std::size_t i=0;
         for(auto it=column_types.begin(); it!=column_types.end(); ++it)
         {
             std::string col_name = it->first;
             column_map[col_name] = i;
             i++; 
         }
     }

     /// @{ Base class virtual interface functions

     /// Reset 'read head' position to first entry
     void SQLiteReader::reset()
     {
         if(not eoi() and stmt!=NULL)
         {
             // Finalise the previous loop so we can start a new one
             sqlite3_finalize(stmt);
         }

         // Reset loop variables
         current_dataset_index = 0;
         current_point = nullpoint;
         eoi_flag = false;

         std::stringstream sql;
         sql<<"SELECT ";
         for(auto it=column_types.begin(); it!=column_types.end(); ++it)
         {
            std::string col_name = it->first;
            sql<<"`"<<col_name<<"`"<<comma_unless_last(it,column_types);
         }  
         sql<<" FROM "<<get_table_name();
    
         /* Execute SQL statement and iterate through results*/ 
         int rc = sqlite3_prepare_v2(get_db(), sql.str().c_str(), -1, &stmt, NULL);
         if (rc != SQLITE_OK) {
             std::stringstream err;
             err<<"Encountered SQLite error while preparing to read data from previous run: "<<sqlite3_errmsg(get_db());
#ifdef SQL_DEBUG
             err << "  The attempted SQL statement was:"<<std::endl;
             err << sql.str() << std::endl; 
#endif
             printer_error().raise(LOCAL_INFO, err.str());
         }

         // Read first row
         move_to_next_point();

         if(eoi())
         {
             std::stringstream err;
             err<<"Immediately reached end of input after beginning to loop through table "<<get_table_name()<<" in file "<<get_database_file()<<"! Perhaps the table is empty?";
             printer_error().raise(LOCAL_INFO, err.str());
         }
     }

     /// Safely access the column_map and throw informative error when column is missing
     std::size_t SQLiteReader::get_col_i(const std::string& col_name)
     {
         auto it = column_map.find(col_name);
         if(it==column_map.end())
         {
             std::stringstream err;
             err<<"Attempted to retrieve data for column with name '"<<col_name<<"' using SQLiteReader, however this column does not seem to exist in the table we are reading!"; 
             printer_error().raise(LOCAL_INFO, err.str());
         }
         return it->second;
     }


     /// Get length of input dataset
     ulong SQLiteReader::get_dataset_length()
     {
         std::stringstream sql;
         sql<<"SELECT COUNT(pairID) FROM "<<get_table_name()<<";";
         sqlite3_stmt *temp_stmt;
         int rc = sqlite3_prepare_v2(get_db(), sql.str().c_str(), -1, &temp_stmt, NULL);
         if (rc != SQLITE_OK) {
             std::stringstream err;
             err<<"Encountered SQLite error while preparing to measure length of input table: "<<sqlite3_errmsg(get_db());
             printer_error().raise(LOCAL_INFO, err.str());
         }
         rc = sqlite3_step(temp_stmt);
         cout_row(temp_stmt); // DEBUG
         if (rc != SQLITE_ROW) {
             std::stringstream err;
             err<<"Encountered SQLite error while attempting to measure length of input table: "<<sqlite3_errmsg(get_db());
             printer_error().raise(LOCAL_INFO, err.str());
         }
         long long int rowcount = sqlite3_column_int64(temp_stmt, 0);
         sqlite3_finalize(temp_stmt);
         if(rowcount<0)
         {
             std::stringstream err;
             err<<"Row count for input table was measured to be negative ("<<rowcount<<")! This clearly makes no sense and is probably a bug in the SQLiteReader class, please report it.";
             printer_error().raise(LOCAL_INFO, err.str());   
         }
         return rowcount; 
     }

     /// Move the SQL loop ahead one
     void SQLiteReader::move_to_next_point()
     {
         if(eoi())
         {
             std::stringstream err;
             err<<"Attempted to move SQLiteReader to next row of input table, but eoi() has been reached! This should have been checked by whatever code called this function!";
             printer_error().raise(LOCAL_INFO, err.str());
         }
         else if(stmt==NULL)
         {
             std::stringstream err;
             err<<"Attempted to move SQLiteReader to next row of input table, but no sql statement has been prepared for iteration!";
             printer_error().raise(LOCAL_INFO, err.str()); 
         }
         else
         {
             // Process the next row
             int rc = sqlite3_step(stmt);
             if(rc==SQLITE_ROW)
             {
                 std::size_t rank = sqlite3_column_int64(stmt, get_col_i("MPIrank"));
                 std::size_t pID  = sqlite3_column_int64(stmt, get_col_i("pointID"));
                 current_point = PPIDpair(pID,rank);
             }
             else if(rc==SQLITE_DONE)
             {
                 // We are at the end of the dataset!
                 eoi_flag = true;
                 current_point = nullpoint;
                 sqlite3_finalize(stmt);
             }
             else
             {
                 // Not the next row, and not the end, something bad has happened.
                 std::stringstream err;
                 err<<"Encountered SQLite error while processing input file: "<<sqlite3_errmsg(get_db());
                 printer_error().raise(LOCAL_INFO, err.str());
             }
         }
     }

     /// Get next rank/ptID pair in data file
     PPIDpair SQLiteReader::get_next_point()
     {
        move_to_next_point();
        ++current_dataset_index;
        return get_current_point();
     }

     /// Get current rank/ptID pair in data file
     PPIDpair SQLiteReader::get_current_point()
     {
        if(eoi())
        {
          // End of data, return nullpoint;
          current_point = nullpoint;
        }
        return current_point;
     }

     // Get a linear index which corresponds to the current rank/ptID pair in the iterative sense
     ulong SQLiteReader::get_current_index()
     {
       return current_dataset_index;
     }

     /// Check if 'current point' is past the end of the datasets (and thus invalid!)
     bool SQLiteReader::eoi()
     {
        return eoi_flag;
     }

     /// Get type information for a data entry, i.e. defines the C++ type which this should be
     /// retrieved as, not what it is necessarily literally stored as in the output.
     std::size_t SQLiteReader::get_type(const std::string& label)
     {
         // Need to match SQL datatype to a printer type ID code.
         // In principle we may like to retrieve a certain type of data in a fancy way,
         // as with ModelParameters or vectors, however we can't really do that in an
         // automated way because this higher-level information is lost during output.
         // So the type matching has to be of a basic sort, i.e. individual ModelParameters
         // elements will be identified as 'double' and so on. But if they are stored that
         // way in the output, then we should be able to copy them that way too (which is
         // the main usage of this get_type function), so this should be ok to do.
         // Currently we only store data in basic types, so those are all that this
         // function needs to retrieve.

         // First find out the SQL type for the column with this label
         auto it = column_types.find(label);
         if(it==column_types.end())
         {
             std::stringstream err;
             err<<"Column with name '"<<label<<"' is not registered in the column_types map!";
             printer_error().raise(LOCAL_INFO,err.str());
         }
         std::string coltype=it->second;

         if(coltype=="NULL")
         {
             std::stringstream err;
             err<<"Column with name '"<<label<<"' is registered as having type 'NULL'! This doesn't make sense, only individual table slots with missing data should have type NULL, it should not be the 'affinity' for a whole column. This indicates a bug in the SQLiteReader object, please report it";
             printer_error().raise(LOCAL_INFO,err.str()); 
         }

         // Now match the SQL datatypes to Printer type IDs (via appropriate C++ types)
         // TODO might need more careful checking, not sure if e.g. INTEGER type name will
         // always be retrieved as INTERGER (as opposed to say INT or something else)
         std::size_t typeID=0;
         #define GET_SQL_TYPE_CASES(r,data,elem) \
         if( SQLite_equaltypes(coltype,cpp2sql<elem>()) )\
         { \
             typeID = getTypeID<elem>(); \
         } \
         else
         BOOST_PP_SEQ_FOR_EACH(GET_SQL_TYPE_CASES, _, SQLITE_CPP_TYPES)
         #undef GET_SQL_TYPE_CASES
         {
             std::ostringstream err;
             err << "Did not recognise retrieved SQL type for data label '"<<label<<"' (its SQL type is registered as '"<<coltype<<"')! This may indicate a bug in the SQLiteReader class, please report it.";
             printer_error().raise(LOCAL_INFO,err.str());
         }
         if(typeID==0)
         {
             std::ostringstream err;
             err << "Did not recognise retrieved Printer type for data label '"<<label<<"' (its SQL type is registered as '"<<coltype<<"')! This may indicate a bug in the Printer system, please report it.";
             printer_error().raise(LOCAL_INFO,err.str());
         }
         return typeID;
     }

     /// Get labels of all datasets in the linked group
     std::set<std::string> SQLiteReader::get_all_labels()
     {
         std::set<std::string> out;
         for (auto it = column_map.begin(); it != column_map.end(); ++it)
         {
             out.insert(it->first);
         }
         return out;
     }

     /// @}

  }
}
