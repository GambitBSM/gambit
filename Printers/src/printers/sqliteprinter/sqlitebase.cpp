//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  SQLite printer/reader base class member function definitions
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

#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
// SQLite3 C interface 
#include <sqlite3.h> 

#include "gambit/Printers/printers/sqlitebase.hpp"

// Activate extra debugging output on error
#define SQL_DEBUG

namespace Gambit
{
  namespace Printers
  {
    /* Callback function for retrieving the column names and types of a table
     * Called for each row of the results table
     *
     * Arguments:
     *
     *     list - Pointer to a map from column names to types
     *    count - The number of columns in the result set
     *     data - The row's data
     *  columns - The column names
     */
    int col_name_callback(void* colmap_in, int /*count*/, char** data, char** /* columns */)
    {
        typedef std::map<std::string, std::string, Utils::ci_less> mymaptype;
        mymaptype *colmap = static_cast<mymaptype*>(colmap_in);
   
        // We know that the column name is the second column of the results set, and the
        // type is the third column
        std::string column_name(data[1]);
        std::string column_type(data[2]);

        //std::cout<<"Reading existing columns: name: "<<column_name<<", type: "<<column_type<<std::endl;

        // Add to map
        (*colmap)[column_name] = column_type;
    
        return 0;
    }

    // Matching of SQL types to C++ types
    template<> std::string cpp2sql<long long int>(){return "INTEGER";}
    template<> std::string cpp2sql<double>()       {return "REAL";}
    template<> std::string cpp2sql<std::string>()  {return "TEXT";}

    // Matching of SQLite "type codes" to SQL types
    // Names should match results of cpp2sql above
    // Codes should match https://www.sqlite.org/c3ref/c_blob.html
    std::map<unsigned int,std::string> define_typecodes()
    {
       std::map<unsigned int,std::string> out;
       out[1] = "INTEGER";
       out[2] = "FLOAT";
       out[3] = "TEXT";
       out[4] = "BLOB";
       out[5] = "NULL";
       return out;
    }
    const std::map<unsigned int,std::string> typecode2sql(define_typecodes());

    // Map from all SQLite "suggestion" types into the five "base" SQLite types
    // Used for type comparisons.
    std::map<std::string,std::string,Utils::ci_less> fill_SQLtype_to_basic()
    {
       std::map<std::string,std::string,Utils::ci_less> out;
       
       out["INT"] = "INTEGER";
       out["INTEGER"] = "INTEGER";
       out["TINYINT"] = "INTEGER";
       out["SMALLINT"] = "INTEGER";
       out["MEDIUMINT"] = "INTEGER";
       out["BIGINT"] = "INTEGER";
       out["UNSIGNED BIG INT"] = "INTEGER";
       out["INT2"] = "INTEGER";
       out["INT8"] = "INTEGER";
       
       out["CHARACTER(20)"] = "TEXT";
       out["VARCHAR(255)"] = "TEXT";
       out["VARYING CHARACTER(255)"] = "TEXT";
       out["NCHAR(55)"] = "TEXT";
       out["NATIVE CHARACTER(70)"] = "TEXT";
       out["NVARCHAR(100)"] = "TEXT";
       out["CLOB"] = "TEXT";
       out["TEXT"] = "TEXT";
       
       out["BLOB"] = "NONE";
       out["NONE"] = "NONE";
       
       out["DOUBLE"] = "REAL";
       out["DOUBLE PRECISION"] = "REAL";
       out["FLOAT"] = "REAL";
       out["REAL"] = "REAL";
       
       out["DECIMAL(10,5)"] = "NUMERIC";
       out["BOOLEAN"] = "NUMERIC";
       out["DATE"] = "NUMERIC";
       out["DATETIME"] = "NUMERIC";
       out["NUMERIC"] = "NUMERIC";
 
       return out;
    }  
    const std::map<std::string,std::string,Utils::ci_less> SQLtype_to_basic(fill_SQLtype_to_basic());  

    // Compare SQLite data types to see if they are equivalent to the same basic 'affinity' for a column
    bool SQLite_equaltypes(const std::string& type1, const std::string& type2)
    {
        // There are five "basic" types in SQLite, but many
        // "aliases" for them. We will need to map each input string
        // to its "basic" type, and then check if those are the same
        // for each input type.
        auto it1 = SQLtype_to_basic.find(type1);
        auto it2 = SQLtype_to_basic.find(type2);
        if(it1==SQLtype_to_basic.end())
        {
            std::stringstream err;
            err<<"Could not determine a basic SQLite 'affinity' type for data type named '"<<type1<<"' (first argument to this type checking dunction)";
            printer_error().raise(LOCAL_INFO,err.str());
        }
        if(it2==SQLtype_to_basic.end())
        {
            std::stringstream err;
            err<<"Could not determine a basic SQLite 'affinity' type for data type named '"<<type2<<"' (second argument to this type checking dunction)";
            printer_error().raise(LOCAL_INFO,err.str());
        }
        return (it1->second) == (it2->second);
    }

    // SQLite base class for both reader and writer (Constructor)
    SQLiteBase::SQLiteBase()
    : database_file("uninitialised")
    , table_name("uninitialised")
    , db(NULL)
    , db_is_open(false)
    , table_exists(false)
    {}

    // Destructor
    SQLiteBase::~SQLiteBase()
    {
        close_db();
    }

    // Open database and 'attach' it to this object
    void SQLiteBase::open_db(const std::string& path, char access)
    { 
        // Check if we already have an open database
        if(db!=NULL)
        {
            std::stringstream err;
            err << "Refused to open database file '"<<path<<"'; a database file pointer has already been attached to the SQLite printer!";
            printer_error().raise(LOCAL_INFO,err.str()); 
        }

        if(db_is_open)
        {
            std::stringstream err;
            err << "Refused to open database file '"<<path<<"'; a database file is already flagged by the SQLite printer as open!";
            printer_error().raise(LOCAL_INFO,err.str());  
        }

        int sql_access;
        switch(access) {
           case 'r' :
              sql_access = SQLITE_OPEN_READONLY;
              break;
           case 'w':
              sql_access = SQLITE_OPEN_READWRITE;
              break;
           case '+':
              sql_access = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
              break;
        }   

        int rc; // return code
        //rc = sqlite3_open(path.c_str(), &db);
        rc = sqlite3_open_v2(path.c_str(), &db, sql_access, NULL);
 
        if( rc ) 
        {
            std::stringstream err;
            err << "Failed to open database file '"<<path<<"' (are you sure it exists?). SQLite error was: " << sqlite3_errmsg(db);
            printer_error().raise(LOCAL_INFO, err.str());
        }
        else
        {
           db_is_open = true;
           database_file = path;
        }
    }

    void SQLiteBase::close_db()
    {
        sqlite3_close(get_db()); // Check error code?
        db_is_open = false;
    }

    sqlite3* SQLiteBase::get_db()
    {
        if(db==NULL)
        {
            std::stringstream err;
            err << "Attempted to access SQLite database pointer, but it is NULL! This means that some SQLitePrinter/Reader routine called 'get_db()' before the database was opened (or after it was closed)! This is a bug, please report it.";
            printer_error().raise(LOCAL_INFO,err.str());  
        }
        return db;
    }

    // Make sure the outbase database is open and the results table exists
    // Throws an error if it isn't
    void SQLiteBase::require_output_ready()
    {
        if(db==NULL || !db_is_open || !table_exists)
        {
            std::stringstream err;
            // Something was not ready, check further and throw an error
            if(db==NULL)
            {
                err << "Output readiness check failed! Database pointer was NULL!";
                printer_error().raise(LOCAL_INFO,err.str());  
            }   

            if(!db_is_open)
            {
                err << "Output readiness check failed! Database is not flagged as open!";
                printer_error().raise(LOCAL_INFO,err.str());  
            }

            if(!table_exists)
            {
                err << "Output readiness check failed! Results table is not flagged as existing!";
                printer_error().raise(LOCAL_INFO,err.str());  
            }
        }
        // Else we are good to go!
    } 

    // Function to repeatedly attempt an SQLite statement if the database is locked/busy
    int SQLiteBase::submit_sql(const std::string& local_info, const std::string& sqlstr, bool allow_fail, sql_callback_fptr callback, void* data, char **zErrMsg_in)
    {
        int rc;
        char *zErrMsg;
        char **zErrMsg_ptr;
        if(zErrMsg_in==NULL) 
        {
           zErrMsg_ptr = &zErrMsg;
        }
        else
        {
           zErrMsg_ptr = zErrMsg_in;
        }

        do
        {
            rc = sqlite3_exec(get_db(), sqlstr.c_str(), callback, data, zErrMsg_ptr);
            if(rc==SQLITE_BUSY)
            {
                // Wait at least a short time to avoid slamming the filesystem too much
                std::chrono::milliseconds timespan(10);
                std::this_thread::sleep_for(timespan);
            }
        }
        while (rc == SQLITE_BUSY);

        // if allow_fail is true then we don't catch this error, we allow the caller of this function to hander it.
        if( (rc != SQLITE_OK) and not allow_fail ){
            std::stringstream err;
            err << "SQL error: " << *zErrMsg_ptr << std::endl;
#ifdef SQL_DEBUG
            err << "The attempted SQL statement was:"<<std::endl;
            err << sqlstr << std::endl;; 
#endif
            sqlite3_free(*zErrMsg_ptr);
            printer_error().raise(local_info,err.str());
       }
       return rc;
    }

    // Get names and types for all columns in the target table
    // (Output is a map from names to types)
    std::map<std::string, std::string, Utils::ci_less> SQLiteBase::get_column_info()
    {
        std::stringstream sql;
        sql<<"PRAGMA table_info("<<get_table_name()<<");";

        /* Execute SQL statement */ 
        int rc;
        char *zErrMsg = 0;
        std::map<std::string, std::string, Utils::ci_less> colnames; // Will be passed to and filled by the callback function
        rc = submit_sql(LOCAL_INFO, sql.str(), true, &col_name_callback, &colnames, &zErrMsg);
 
        if( rc != SQLITE_OK ){
            std::stringstream err;
            err << "Failed to retrieve information about SQL column names in target table!"<<std::endl;
            err << "  The attempted SQL statement was:"<<std::endl;
            err << sql.str() << std::endl; 
            sqlite3_free(zErrMsg);
            printer_error().raise(LOCAL_INFO,err.str());
        }
        return colnames;
    }

    std::string SQLiteBase::get_database_file() {return database_file;}
    std::string SQLiteBase::get_table_name() {return table_name;} 
    void SQLiteBase::set_table_name(const std::string& t) {table_name=t;}
  
    // For debugging: dump a row of a results table to std::cout
    void SQLiteBase::cout_row(sqlite3_stmt* tmp_stmt)
    {
        int ncols = sqlite3_data_count(tmp_stmt);
        for(int i=0; i<ncols; i++)
        {
            std::cout<<" "<<sqlite3_column_text(tmp_stmt, i)<<",";
        }
    }

    // Check that the required table exists
    // Sets 'table_exists' to true if successful, otherwise throws error
    void SQLiteBase::check_table_exists()
    {
        std::stringstream sql;
        sql<<"SELECT name FROM sqlite_master WHERE type='table' AND name='"<<get_table_name()<<"';";
        std::size_t count(0);

        /* Execute SQL statement and iterate through results*/ 
        sqlite3_stmt *temp_stmt;
        int rc = sqlite3_prepare_v2(get_db(), sql.str().c_str(), -1, &temp_stmt, NULL);
        if (rc != SQLITE_OK) {
            std::stringstream err;
            err<<"Encountered SQLite error while preparing statement to check if table '"<<get_table_name()<<"' exists in file '"<<get_database_file()<<"': "<<sqlite3_errmsg(get_db());
            printer_error().raise(LOCAL_INFO, err.str());
        }
        while ((rc = sqlite3_step(temp_stmt)) == SQLITE_ROW) {
            count+=1; // Will be one row for each table with a name matching 'get_table_name()'. Should be 1 or 0.
        }
        if (rc != SQLITE_DONE) {
            std::stringstream err;
            err<<"Encountered SQLite error while checking if table '"<<get_table_name()<<"' exists in file '"<<get_database_file()<<": "<<sqlite3_errmsg(get_db());
            printer_error().raise(LOCAL_INFO, err.str());
        }
        sqlite3_finalize(temp_stmt);

        if(count==0)
        {
            std::stringstream err;
            err<<"Requested input table '"<<get_table_name()<<"' could not be found in file '"<<get_database_file()<<"! Please check that the requested table name is correct!";
            printer_error().raise(LOCAL_INFO, err.str());
        }
        else if(count>1)
        {
            std::stringstream err;
            err<<"Weird error encountered while checking that input table '"<<get_table_name()<<"' exists in file '"<<get_database_file()<<". We apparently found "<<count<<" tables with this name! This doesn't make sense, so there is probably a bug in the SQLiteBase class, please report it.";
            printer_error().raise(LOCAL_INFO, err.str());
        }
        // Else the table exists, no problem.
        set_table_exists(); 
    }

    // Sets the 'table_exists' flag to true
    void SQLiteBase::set_table_exists() {table_exists=true;}

  }
}

