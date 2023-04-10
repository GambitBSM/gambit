//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  SQLite printer class member function definitions
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
///
///  TODO: Turns out SQLite is case-insensitive, so need
///  to change various string comparisons here to also be
///  case-insensitive.

#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

// SQLite3 C interface
#include <sqlite3.h>

// Gambit
#include "gambit/Printers/printers/sqliteprinter.hpp"
#include "gambit/Logs/logger.hpp"

// Define this macro to dump attempted SQL statements during exceptions
#define SQL_DEBUG

namespace Gambit
{
  namespace Printers
  {

    // Constructor
    SQLitePrinter::SQLitePrinter(const Options& options, BasePrinter* const primary)
    : BasePrinter(primary,options.getValueOrDef<bool>(false,"auxilliary"))
    , SQLiteBase()
#ifdef WITH_MPI
    , myComm() // initially attaches to MPI_COMM_WORLD
#endif
    , mpiRank(0)
    , mpiSize(1)
    , primary_printer(NULL)
    , column_record()
    , lastMetadataID(0)
    , lastPointID(nullpoint)
    , max_buffer_length(options.getValueOrDef<std::size_t>(1,"buffer_length"))
    , buffer_info()
    , buffer_header()
    , transaction_data_buffer()
    , synchronised(!options.getValueOrDef<bool>(false,"auxilliary"))
    {
        std::string database_file;
        std::string table_name;
        std::string metadata_table_name;

        if(is_auxilliary_printer())
        {
            // If this is an "auxilliary" printer then we need to get some
            // of our options from the primary printer
            primary_printer     = dynamic_cast<SQLitePrinter*>(this->get_primary_printer());
            database_file       = primary_printer->get_database_file();
            table_name          = primary_printer->get_table_name();
            metadata_table_name = primary_printer->get_metadata_table_name();
            max_buffer_length   = primary_printer->get_max_buffer_length();
        }
        else
        {
            // MPI setup
#ifdef WITH_MPI
            this->setRank(myComm.Get_rank()); // tells base class about rank
            mpiRank = myComm.Get_rank();
            mpiSize = myComm.Get_size();
#endif

            // Register dataset names that this printer needs to use itself
            // ("MPIrank" and "pointID" are always automatically registered)
            addToPrintList("pairID");

            // Tell scannerbit if we are resuming
            set_resume(options.getValue<bool>("resume"));

            // Get path of database file where results should ultimately end up
            std::ostringstream ff;
            if(options.hasKey("output_path"))
            {
                ff << options.getValue<std::string>("output_path") << "/";
            }
            else
            {
                ff << options.getValue<std::string>("default_output_path") << "/";
            }

            if(options.hasKey("output_file"))
            {
                ff << options.getValue<std::string>("output_file");
            }
            else
            {
                printer_error().raise(LOCAL_INFO, "No 'output_file' entry specified in the options section of the Printer category of the input YAML file. Please add a name there for the output sqlite database file of the scan.");
            }

            database_file = ff.str();

            // Get the name of the data table for this run
            table_name = options.getValueOrDef<std::string>("results","table_name");
            metadata_table_name = options.getValueOrDef<std::string>("metadata", "metadata_table_name");

            // Delete final target file if one with same name already exists? (and if we are restarting the run)
            // Mostly for convenience during testing. Recommend to use 'false' for serious runs to avoid
            // accidentally deleting valuable output.
            bool overwrite_file  = options.getValueOrDef<bool>(false,"delete_file_on_restart");

            if(getRank()==0 and overwrite_file and not get_resume())
            {
                // Note: "not resume" means "start or restart"
                // Delete existing output file
                std::ostringstream command;
                command << "rm -f "<<database_file;
                logger() << LogTags::printers << LogTags::info << "Running shell command: " << command.str() << EOM;
                FILE* fp = popen(command.str().c_str(), "r");
                if(fp==NULL)
                {
                    // Error running popen
                    std::ostringstream errmsg;
                    errmsg << "rank "<<getRank()<<": Error deleting existing output file (requested by 'delete_file_on_restart' printer option; target filename is "<<database_file<<")! popen failed to run the command (command was '"<<command.str()<<"')";
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
                else if(pclose(fp)!=0)
                {
                    // Command returned exit code!=0, or pclose failed
                    std::ostringstream errmsg;
                    errmsg << "rank "<<getRank()<<": Error deleting existing output file (requested by 'delete_file_on_restart' printer option; target filename is "<<database_file<<")! Shell command failed to executed successfully, see stderr (command was '"<<command.str()<<"').";
                    printer_error().raise(LOCAL_INFO, errmsg.str());
                }
            }

#ifdef WITH_MPI
            // Make sure no processes try to open database until we are sure it won't be deleted and replaced
            myComm.Barrier();
#endif
        }

        // Create/open the database file
        open_db(database_file,'+');

        // Create the results table in the database (if it doesn't already exist)
        make_table(table_name);
        make_metadata_table(metadata_table_name);
        set_table_name(table_name); // Inform base class of table name
        set_metadata_table_name(metadata_table_name);

        // If we are resuming and this is the primary printer, need to read the database and find the previous
        // highest pointID numbers used for this rank
        std::size_t my_highest_pointID=0;
        if(not is_auxilliary_printer() and get_resume())
        {
            // Construct the SQLite3 statement to retrieve highest existing pointID in the database for this rank
            std::stringstream sql;
            sql << "SELECT MAX(pointID) FROM "<<get_table_name()<<" WHERE MPIrank="<<mpiRank;

            /* Execute SQL statement and iterate through results*/
            sqlite3_stmt *stmt;
            int rc = sqlite3_prepare_v2(get_db(), sql.str().c_str(), -1, &stmt, NULL);
            if (rc != SQLITE_OK)
            {
                std::stringstream err;
                err<<"Encountered SQLite error while preparing to retrieve previous pointIDs: "<<sqlite3_errmsg(get_db());
                printer_error().raise(LOCAL_INFO, err.str());
            }
            int colcount=0;
            while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
            {
                my_highest_pointID = sqlite3_column_int64(stmt, 0);
                colcount++;
                if(colcount>1)
                {
                    std::stringstream err;
                    err<<"SQLite statement to retrieve highest existing pointID returned more than one result! This doesn't make sense, so there is probably a bug in the statement that was used. Statement was: "<<sql.str();
                    printer_error().raise(LOCAL_INFO, err.str());
                }
            }
            if (rc != SQLITE_DONE) {
                std::stringstream err;
                err<<"Encountered SQLite error while retrieving previous pointIDs: "<<sqlite3_errmsg(get_db());
                printer_error().raise(LOCAL_INFO, err.str());
            }
            sqlite3_finalize(stmt);

            // Read off last metadata entry
            std::stringstream sql2;
            sql2 << "SELECT MAX(metadataID) FROM " << get_metadata_table_name() << ";";
            sqlite3_stmt *stmt2;
            rc = sqlite3_prepare_v2(get_db(), sql2.str().c_str(), -1, &stmt2, NULL);
            if (rc != SQLITE_OK)
            {
                std::stringstream err;
                err<<"Encountered SQLite error while preparing to retrieve previous metadataIDs: "<<sqlite3_errmsg(get_db());
                printer_error().raise(LOCAL_INFO, err.str());
            }
            colcount=0;
            while ((rc = sqlite3_step(stmt2)) == SQLITE_ROW)
            {
                lastMetadataID = sqlite3_column_int64(stmt2, 0);
                lastMetadataID++;
                colcount++;
                if(colcount>1)
                {
                    std::stringstream err;
                    err<<"SQLite statement to retrieve highest existing metadataID returned more than one result! This doesn't make sense, so there is probably a bug in the statement that was used. Statement was: "<<sql.str();
                    printer_error().raise(LOCAL_INFO, err.str());
                }
            }
            if (rc != SQLITE_DONE)
            {
                std::stringstream err;
                err<<"Encountered SQLite error while retrieving previous pointIDs: "<<sqlite3_errmsg(get_db());
                printer_error().raise(LOCAL_INFO, err.str());
            }
            sqlite3_finalize(stmt2);

            // Need to make sure no other processes start adding new stuff before everyone has figured out
            // their next unused pointID
#ifdef WITH_MPI
            myComm.Barrier();
#endif
            if (get_resume())
            {
                get_point_id() = my_highest_pointID;
            }

            // DEBUG
            //std::cout<<"Highest pointID retrieved for rank "<<mpiRank<<" was: "<<get_point_id();
        }
    }

    std::size_t SQLitePrinter::get_max_buffer_length() {return max_buffer_length;}

    void SQLitePrinter::initialise(const std::vector<int>&)
    {
        // Don't need to initialise anything for this printer
    }

    void SQLitePrinter::reset(bool force)
    {
        // This is needed by e.g. MultiNest to delete old weights and replace them
        // with new ones.

        lastPointID = nullpoint;

        // Primary printers aren't allowed to delete stuff unless 'force' is set to true
        if((is_auxilliary_printer() or force) and (buffer_header.size()>0))
        {
            // Read through header to see what columns this printer has been touching. These are
            // the ones that we will reset/delete.
            // (a more nuanced reset might be required in the future?)
            std::stringstream sql;
            sql<<"UPDATE "<<get_table_name()<<" SET ";
            for(auto col_name_it=buffer_header.begin(); col_name_it!=buffer_header.end(); ++col_name_it)
            {
                sql<<"`"<<(*col_name_it)<<"`=null"<<comma_unless_last(col_name_it,buffer_header);
            }
            sql<<";";

            /* Execute SQL statement */
            submit_sql(LOCAL_INFO, sql.str());
        }
    }

    // Print metadata info to file
    void SQLitePrinter::_print_metadata(map_str_str metadata)
    {

      std::stringstream sql;

      // Create columns first
      for (auto key_value : metadata)
      {
        str col_type;
        if (key_value.first == "YAML")
          col_type = "LONGTEXT";
        else
          col_type = "MEDIUMTEXT";

        ensure_column_exists(get_metadata_table_name(), key_value.first, col_type);
      }

      // Now add data
      sql << " INSERT INTO " << get_metadata_table_name() <<" (\nmetadataID,\n";
      for(auto col_name_it=metadata.begin(); col_name_it!=metadata.end(); ++col_name_it)
      {
          sql<<"`"<< col_name_it->first <<"`"<<comma_unless_last(col_name_it,metadata)<<"\n";
      }
      sql << ") VALUES (\n";
      size_t metadataID = lastMetadataID;
      sql << metadataID << ",";
      for(auto row_it=metadata.begin(); row_it!=metadata.end(); ++row_it)
      {
        sql << "\"" << row_it->second << "\"" << comma_unless_last(row_it,metadata);
      }
      sql<<");"; // End statement

      /* Execute SQL statement */
      int rc;
      char *zErrMsg = 0;
      // Need allow_fail=true for this case
      rc = submit_sql(LOCAL_INFO, sql.str(), true, NULL, NULL, &zErrMsg);

      if( rc != SQLITE_OK )
      {
        std::stringstream err;
        err << "Failed to add metadata to output SQL table! The SQL error was: " << zErrMsg << std::endl;
//#ifdef SQL_DEBUG
        err << "The attempted SQL statement was:"<<std::endl;
        err << sql.str() << std::endl;
//#endif
        sqlite3_free(zErrMsg);
        printer_error().raise(LOCAL_INFO,err.str());
      }
    }


    void SQLitePrinter::finalise(bool /*abnormal*/)
    {
      // Dump buffer to disk. Nothing special needed for early shutdown.
      dump_buffer();

      // Add last point ID to metadata
      std::stringstream ssPPID;
      ssPPID << lastPointID;

      std::stringstream sql;
      ensure_column_exists(get_metadata_table_name(), "lastPointID", "MEDIUMTEXT");
      sql << " UPDATE " << get_metadata_table_name() << " SET lastPointID = \"" << ssPPID.str() << "\" WHERE metadataID = " << lastMetadataID << ";\n";

      /* Execute SQL statement */
      int rc;
      char *zErrMsg = 0;
      // Need allow_fail=true for this case
      rc = submit_sql(LOCAL_INFO, sql.str(), true, NULL, NULL, &zErrMsg);

      if( rc != SQLITE_OK )
      {
        std::stringstream err;
        err << "Failed to add metadata to output SQL table! The SQL error was: " << zErrMsg << std::endl;
//#ifdef SQL_DEBUG
        err << "The attempted SQL statement was:"<<std::endl;
        err << sql.str() << std::endl;
//#endif
        sqlite3_free(zErrMsg);
        printer_error().raise(LOCAL_INFO,err.str());
      }

    }

    void SQLitePrinter::flush()
    {
        dump_buffer();
    }

    // Reader construction options for constructing a reader
    // object that can read the output we are printing
    Options SQLitePrinter::resume_reader_options()
    {
        Options options;
        // Set options that we need later to construct a reader object for
        // previous output, if required.
        options.setValue("type", "sqlite");
        options.setValue("file", get_database_file());
        options.setValue("table", get_table_name());
        return options;
    }

    // Create results table
    void SQLitePrinter::make_table(const std::string& name)
    {
        // Construct the SQLite3 statement
        std::stringstream sql;
        sql << "CREATE TABLE IF NOT EXISTS "<<name<<"("
            << "pairID   INT PRIMARY KEY NOT NULL,"
            << "MPIrank  INT,"
            << "pointID  INT"
            << ");";

        /* Execute SQL statement */
        submit_sql(LOCAL_INFO, sql.str());

        // Flag the results table as existing
        set_table_exists();
    }

    // Create the metadata table
    void SQLitePrinter::make_metadata_table(const std::string& name)
    {
        // Construct the SQLite3 statement
        std::stringstream sql;
        sql << "CREATE TABLE IF NOT EXISTS "<<name<<"("
            << "metadataID   INT PRIMARY KEY NOT NULL);";

        /* Execute SQL statement */
        submit_sql(LOCAL_INFO, sql.str());

        // Flag the results table as existing
        set_table_exists();
    }


    // Check that a table column exists with the correct type, and create it if needed
    void SQLitePrinter::ensure_column_exists(const std::string& sql_table_name, const std::string& sql_col_name, const std::string& sql_col_type)
    {
        require_output_ready();
        auto it = column_record.find(sql_col_name);
        if(it == column_record.end())
        {
            // Column not marked as existing. But it might have been
            // created by another process, so we need to check the
            // database directly. It seems like the best way to do
            // this is to just attempt to add the column. If it fails
            // we can then explicitly check the column names to
            // make sure that the reason for failure was because
            // the column already existed, and not some other reason.

            std::stringstream sql;
            sql<<"ALTER TABLE "<<sql_table_name<<" ADD COLUMN `"<<sql_col_name<<"` "<<sql_col_type<<";";

            /* Execute SQL statement */
            int rc;
            char *zErrMsg = 0;
            // Need allow_fail=true for this case
            rc = submit_sql(LOCAL_INFO, sql.str(), true, NULL, NULL, &zErrMsg);

            if( rc != SQLITE_OK ){
                // Operation failed for some reason. Probably because the column already
                // exists, but we better make sure.

                std::stringstream sql2;
                sql2<<"PRAGMA table_info("<<sql_table_name<<");";

                /* Execute SQL statement */
                int rc2;
                char *zErrMsg2 = 0;
                std::map<std::string, std::string, Utils::ci_less> colnames; // Will be passed to and filled by the callback function
                rc2 = submit_sql(LOCAL_INFO, sql2.str(), true, &col_name_callback, &colnames, &zErrMsg2);

                if( rc2 != SQLITE_OK ){
                    std::stringstream err;
                    err << "Failed to check SQL column names in output table, after failing to add a new column '"<<sql_col_name<<"' to that table."<<std::endl;
                    err << "  First SQL error was: " << zErrMsg << std::endl;
#ifdef SQL_DEBUG
                    err << "  The attempted SQL statement was:"<<std::endl;
                    err << sql.str() << std::endl;
#endif
                    err << "  Second SQL error was: " << zErrMsg2 << std::endl;
#ifdef SQL_DEBUG
                    err << "  The attempted SQL statement was:"<<std::endl;
                    err << sql2.str() << std::endl;
#endif
                    sqlite3_free(zErrMsg);
                    sqlite3_free(zErrMsg2);
                    printer_error().raise(LOCAL_INFO,err.str());
                }

                // Operation successful, check if our column name exists and has the correct type
                auto jt = colnames.find(sql_col_name);
                if(jt==colnames.end())
                {
                    // Column not found
                    std::stringstream err;
                    err << "Failed to add new column '"<<sql_col_name<<"' to output SQL table! The ALTER TABLE operation failed, however it was not because the column already existed (we successfully checked and the column was not found). The SQL error was: " << zErrMsg << std::endl;
#ifdef SQL_DEBUG
                    err << "The attempted SQL statement was:"<<std::endl;
                    err << sql.str() << std::endl;
#endif
                    sqlite3_free(zErrMsg);
                    printer_error().raise(LOCAL_INFO,err.str());
                }
                else if(!Utils::iequals(jt->second,sql_col_type))
                {
                    // NOTE: All sorts of type names are equivalent, so this simple string checking is
                    // totally unreliable!

                    // // Column found, but has the wrong type
                    // std::stringstream err;
                    // err << "Failed to add new column '"<<sql_col_name<<"' to output SQL table! The column already exists, but it has the wrong type (existing column has type '"<<jt->second<<"', but we expected it to have type '"<<sql_col_type<<"'!";
                    // sqlite3_free(zErrMsg);
                    // printer_error().raise(LOCAL_INFO,err.str());
                }

                // Column exists and has the right type! So everything is ok after all.
            }

            // Column should exist now. Need to add the fact of this columns existence to our internal record.
            column_record[sql_col_name] = sql_col_type;
        }
        else if(!Utils::iequals(it->second,sql_col_type))
        {
            // // Records say column exists, but not with the type requested!
            // NOTE: All sorts of type names are equivalent, so this simple string checking is
            // totally unreliable!

            // std::stringstream err;
            // err << "SQLitePrinter records indicated that the column '"<<sql_col_name<<"' already exists in the output table, but with a different type than has been requested (existing type is '"<<it->second<<"', requested type was '"<<sql_col_type<<"'). This indicates either duplicate names in the printer output, or an inconsistency in how the print commands have been issued.";
            // printer_error().raise(LOCAL_INFO,err.str());
        }
        // else column exists and type matches, proceed!
    }

    // Queue data for a table insert operation into the SQLitePrinter internal buffer
    void SQLitePrinter::insert_data(const unsigned int mpirank, const unsigned long pointID, const std::string& col_name, const std::string& col_type, const std::string& data)
    {
        // Get the pairID for this rank/pointID combination
        std::size_t rowID = pairfunc(mpirank,pointID);

        // Last point ID
        lastPointID = PPIDpair(pointID,mpirank);

        // Make sure we have a record of this column existing in the output table
        // Create it if needed.
        ensure_column_exists(get_table_name(), col_name, col_type);

        // Check if a row for this data exists in the transaction buffer
        auto buf_it=transaction_data_buffer.find(rowID);
        if(buf_it==transaction_data_buffer.end())
        {
            // Nope, no row yet for this rowID. Add it.
            // But we should first dump the buffer if it was full

            // If the buffer is full, execute a transaction to write
            // data to disk, and clear the buffer
            if(transaction_data_buffer.size()>=max_buffer_length)
            {
                dump_buffer();
            }

            // Data is set to 'null' until we add some.
            std::size_t current_row_size=buffer_info.size();
            transaction_data_buffer.emplace(rowID,std::vector<std::string>(current_row_size,"null"));
        }

        // Check if this column exists in the current output buffer
        // Create it if needed
        auto it=buffer_info.find(col_name);
        if(it==buffer_info.end())
        {
            // Column doesn't exist in buffer. Add it.
            std::size_t next_col_index = buffer_info.size();
            buffer_info[col_name] = std::make_pair(next_col_index,col_type);

            // Add header data
            //std::cout<<"Adding column to buffer: "<<col_name<<std::endl;
            buffer_header.push_back(col_name);
            if(buffer_info.size()!=buffer_header.size())
            {
                std::stringstream err;
                err<<"Size of buffer_header ("<<buffer_header.size()<<") does not match buffer_info ("<<buffer_info.size()<<"). This is a bug, please report it.";
                printer_error().raise(LOCAL_INFO,err.str());
            }

            // Add buffer space
            for(auto jt=transaction_data_buffer.begin();
                     jt!=transaction_data_buffer.end(); ++jt)
            {
               std::vector<std::string>& row = jt->second;

               // Add new empty column to every row
               // Values are null until we add them
               row.push_back("null");

               // Make sure size is correct
               if(row.size()!=buffer_header.size())
               {
                   std::stringstream err;
                   err<<"Size of a row in the transaction_data_buffer ("<<row.size()<<") does not match buffer_header ("<<buffer_info.size()<<"). This is a bug, please report it.";
                   printer_error().raise(LOCAL_INFO,err.str());
               }
            }

            // Now point the map iterator to the right place

            it=buffer_info.find(col_name);
        }
        else
        {
            // Column exists in buffer, but we should also make sure the
            // type is consistent with the new data we are adding
            std::string buffer_col_type = it->second.second;
            if(!Utils::iequals(buffer_col_type,col_type))
            {
                std::stringstream err;
                err<<"Attempted to add data for column '"<<col_name<<"' to SQLitePrinter transaction buffer, but the type of the new data ("<<col_type<<") does not match the type already recorded for this column in the buffer ("<<buffer_col_type<<").";
                printer_error().raise(LOCAL_INFO,err.str());
            }
        }

        // Add the data to the transaction buffer
        std::size_t col_index = it->second.first;
        transaction_data_buffer.at(rowID).at(col_index) = data;
    }

    // Delete all buffer data. Leaves the header intact so that we know what columns
    // this printer has been working with (needed so we can reset them if needed!)
    void SQLitePrinter::clear_buffer()
    {
        transaction_data_buffer.clear();
    }

    // Create an SQL table insert operation for the current transaction_data_buffer
    // Modifies 'sql' stringstream in-place
    void SQLitePrinter::turn_buffer_into_insert(std::stringstream& sql, const std::string& table)
    {
        sql<<"INSERT INTO "<<table<<" (\npairID,\n";
        for(auto col_name_it=buffer_header.begin(); col_name_it!=buffer_header.end(); ++col_name_it)
        {
            sql<<"`"<<(*col_name_it)<<"`"<<comma_unless_last(col_name_it,buffer_header)<<"\n";
        }
        sql<<") VALUES ";
        for(auto row_it=transaction_data_buffer.begin();
                 row_it!=transaction_data_buffer.end(); ++row_it)
        {
            sql<<"(\n";
            std::size_t pairID = row_it->first;
            std::vector<std::string>& row = row_it->second;
            sql<<pairID<<",\n";
            for(auto col_it=row.begin(); col_it!=row.end(); ++col_it)
            {
                sql<<(*col_it)<<comma_unless_last(col_it,row)<<"\n";
            }
            sql<<")\n"<<comma_unless_last(row_it,transaction_data_buffer);
        }
        sql<<";"; // End statement
    }

    // Execute an SQLite transaction to write the buffer to the output table
    void SQLitePrinter::dump_buffer_as_INSERT()
    {
        // Add the table INSERT operation to a stream
        std::stringstream sql;
        turn_buffer_into_insert(sql,get_table_name());

        //std::cout<<sql.str(); // DEBUG

        /* Execute SQL statement */
        submit_sql(LOCAL_INFO,sql.str());
    }

    void SQLitePrinter::dump_buffer_as_UPDATE()
    {
        std::stringstream sql;
        // So for this is seems like the best thing to do is create a temporary
        // table with this new data, and then update the main output table from
        // this. Otherwise we have to write tonnes of separate 'update' statements,
        // which is probably not very fast.
        // So first we need to create the temporary table.
        sql << "DROP TABLE IF EXISTS temp_table;\n"
            << "CREATE TEMPORARY TABLE temp_table("
            << "pairID   INT PRIMARY KEY NOT NULL,\n";
        for(auto col_it=buffer_info.begin(); col_it!=buffer_info.end(); ++col_it)
        {
            const std::string& col_name(col_it->first);
            const std::string& col_type(col_it->second.second);
            sql<<"`"<<col_name<<"`   "<<col_type<<comma_unless_last(col_it,buffer_info)<<"\n";
        }
        sql <<");\n";

        // Insert data into the temporary table
        turn_buffer_into_insert(sql,"temp_table");

        // Update the primary output table using the temporary table
        // Following: https://stackoverflow.com/a/47753166/1447953
        sql<<"UPDATE "<<get_table_name()<<" SET (\n";
        for(auto col_name_it=buffer_header.begin(); col_name_it!=buffer_header.end(); ++col_name_it)
        {
            sql<<*col_name_it<<comma_unless_last(col_name_it,buffer_header)<<"\n";
        }
        sql<<") = (SELECT \n";
        for(auto col_name_it=buffer_header.begin(); col_name_it!=buffer_header.end(); ++col_name_it)
        {
            sql<<"temp_table."<<*col_name_it<<comma_unless_last(col_name_it,buffer_header)<<"\n";
        }
        sql<<" FROM temp_table WHERE temp_table.pairID = "<<get_table_name()<<".pairID)\n";
        sql<<" WHERE EXISTS ( SELECT * FROM temp_table WHERE temp_table.pairID = "<<get_table_name()<<".pairID);\n";

        /* Execute SQL statement */
        submit_sql(LOCAL_INFO,sql.str());
    }

    void SQLitePrinter::dump_buffer()
    {
        require_output_ready();
        // Don't try to dump the buffer if it is empty!
        if(transaction_data_buffer.size()>0)
        {
            if(synchronised)
            {
                // Primary dataset writes can be performed as INSERT operations
                dump_buffer_as_INSERT();
            }
            else
            {
                // Asynchronous ('auxilliary') writes need to be performed as UPDATE operations
                dump_buffer_as_UPDATE();
            }
            // Clear all the buffer data
            clear_buffer();
        }
    }

  }
}
