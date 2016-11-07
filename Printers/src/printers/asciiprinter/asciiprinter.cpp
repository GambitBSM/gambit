//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Ascii printer class member function definitions
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 Jul, Sep, 2014 Jan
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Jan
///
///  *********************************************


// Standard libraries
#include <map>
#include <vector>
#include <algorithm>
#include <ios>
#include <sstream>
#include <fstream>
#include <iomanip>

// Gambit
#include "gambit/Printers/printers/asciiprinter.hpp"
#include "gambit/Core/error_handlers.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/util_functions.hpp"

// MPI bindings
#include "gambit/Utils/mpiwrapper.hpp"

// Switch for debugging output (manual at the moment)

//#define AP_DEBUG_MODE

#ifdef AP_DEBUG_MODE 
  #define AP_DBUG(x) x
#else 
  #define AP_DBUG(x)
#endif


// Code!
namespace Gambit
{

  namespace Printers 
  {

    /// Open file stream with error checking
    //TODO: It would be good to add something like this to the Gambit Utils to use as a standard I think.

    void open_output_file(std::ofstream& output, std::string filename, std::ios_base::openmode mode)
    {
      // Pass in reference to externally created ofstream "output"
      output.open(filename, std::ofstream::out | mode);

      if( output.fail() | output.bad() )
      {
         std::ostringstream ss;
         ss << "IO error while opening file for writing! Tried to open ofstream to file \""<<filename<<"\", but encountered error bit in the created ostream.";
         throw std::runtime_error( ss.str() ); 
      }
    }

    Record::Record() : readyToPrint(false) {};

    void Record::reset()
    {
       data.clear();
       readyToPrint = false;
    }
 
    // Printer to ascii file (i.e. table of doubles)

    // Common constructor tasks
    void asciiPrinter::common_constructor(const Options& options)
    {
      if( this->is_auxilliary_printer() ) // check if this is an auxilliary printer
      {

         // Get stream name from printermanager
         printer_name = options.getValue<std::string>("name");

         // Get primary printer (need to cast from BasePrinter type to asciiPrinter)
         asciiPrinter* primary = dynamic_cast<asciiPrinter*>(this->get_primary_printer());

         // Name files based on the primary printer filenames
         std::ostringstream f;
         f << primary->get_output_filename() << "_" << printer_name;
         output_file = Utils::ensure_path_exists(options.getValueOrDef<std::string>(f.str(),"output_file"));

         // Match the buffer length to the primary printer, or use a user-supplied option
         bufferlength = options.getValueOrDef<uint>(primary->get_bufferlength(),"buffer_length");
      }
      else
      {
         printer_name = "Primary";     

         std::ostringstream f;
         if(options.hasKey("output_path"))
         {
           f << options.getValue<std::string>("output_path") << "/";
         }
         else
         {
           f << options.getValue<std::string>("default_output_path") << "/";
         }
         f << options.getValue<std::string>("output_file");
         output_file = Utils::ensure_path_exists(f.str());

         bufferlength = options.getValueOrDef<uint>(100,"buffer_length");
      }

      // Name "info" file to match "output" file
      std::ostringstream finfo;
      finfo<< output_file <<"_info";
      info_file = finfo.str();

      #ifdef WITH_MPI
      myRank = myComm.Get_rank();
      mpiSize = myComm.Get_size();

      // Append mpi rank to file names to avoid collisions between processes
      std::ostringstream fout;
      std::ostringstream finfo2;
      fout << output_file <<"_"<<myRank;
      finfo2<< info_file  <<"_"<<myRank;
      output_file = fout.str();
      info_file = finfo2.str();
      #endif


      // Initialise "lastPointID" map to -1 (i.e. no last point)
      #ifdef WITH_MPI
      for(uint i=0; i<mpiSize; i++)
      {
        lastPointID[i] = -1;
      }
      #else
      lastPointID[myRank] = -1;
      #endif 

      // Erase contents of output_file and info_file if they already exist
      std::ofstream output;
      open_output_file(output, output_file, std::ofstream::trunc);
      output.close();
      
      std::ofstream info;
      open_output_file(info, info_file, std::ofstream::trunc);
      info.close();
    }

    // Constructor
    asciiPrinter::asciiPrinter(const Options& options, BasePrinter* const primary)
      : BasePrinter(primary,options)
      , output_file("")
      , info_file("")
      , bufferlength(100) 
      , global(false)
      , printer_name("")
      , myRank(0)
     #ifdef WITH_MPI
      , myComm() // attaches to MPI_COMM_WORLD, beware collisions with e.g. scanning algorithms.
      , mpiSize(1)
     #endif
    {
      common_constructor(options);
    }

 
    /// Destructor
    // Overload the base class virtual destructor
    asciiPrinter::~asciiPrinter()
    {
      // Make sure buffer is completely written to disk (MOVED TO FINALISE)
      AP_DBUG( std::cout << "Destructing asciiPrinter object (with name=\""<<printer_name<<"\")..." << std::endl; )
    }
 
    /// Initialisation function
    // Run by dependency resolver, which supplies the functors with a vector of VertexIDs whose requiresPrinting flags are set to true.
    void asciiPrinter::initialise(const std::vector<int>& /*printmevec*/)
    {
      // Currently don't seem to need this... could use it to check if all VertexID's have submitted print requests.
      // //std::cout << "Initialising asciiprinter..." << std::endl;
      // // Loop through buffer and initialise all the elements
      // for (int i=0; i<bufferlength; i++)
      // {
      //   for (std::vector<int>::const_iterator it = printmevec.begin();
      //   it != printmevec.end(); it++)
      //   {
      //     // Add element to line of buffer (uses default (empty) constructor)
      //     buffer[i][*it];
      //   }
      // } 
    }

    /// Do final buffer dumps
    void asciiPrinter::finalise(bool /*abnormal*/)
    {
      dump_buffer(true);
      AP_DBUG( std::cout << "Buffer (of asciiPrinter with name=\""<<printer_name<<"\") successfully dumped..." << std::endl; )
    }

    /// Delete contents of output file (to be replaced/updated) and erase everything in the buffer
    void asciiPrinter::reset(bool) 
    {
      std::ofstream my_fstream;
      open_output_file(my_fstream, output_file, std::ofstream::trunc);
      my_fstream.close();
      erase_buffer();
      lastPointID.clear();
      #ifdef WITH_MPI
      for(uint i=0; i<mpiSize; i++)
      {
        lastPointID[i] = -1;
      }
      #else
      lastPointID[myRank] = -1;
      #endif 
    }

    /// Retrieve MPI rank
    int asciiPrinter::getRank() {return myRank;}
 
    /// Clear buffer
    void asciiPrinter::erase_buffer()
    {
      // Used to just erase the records, but preserve vertex IDs. Not sure this is necessary, so for now just 
      // emptying the map.
      buffer.clear();

      // Obsolete; redo this
      // for (int i=0; i<bufferlength; i++)
      // {
      //   for (LineBuf::iterator 
      //     it = buffer[i].begin(); it != buffer[i].end(); it++)
      //   {
      //     // We want to preserve the vertex ID's and just erase the vector part (second) of the map
      //     (it->second).clear();
      //   }
      // }
    }
  
    // Tell printer to start a new line of the ascii output file
    void asciiPrinter::endline()
    {
      // Obsolete; no longer a virtual function either I think.
      // std::cout<<"In acsiiPrinter: starting new printer line!"<<std::endl; 

      // // Move buffer location index to the next line
      // buf_loc += 1;
      // 
      // // Check if we have filled the buffer
      // if (buf_loc >= bufferlength)
      // {
      //  // Write to file and reset buffer
      //   dump_buffer();
      //   erase_buffer();
      //   buf_loc = 0;
      // }
    }

    // getters for internal variables 
    std::string asciiPrinter::get_output_filename() { return output_file; }
    int         asciiPrinter::get_bufferlength()    { return bufferlength; }

    // add results to printer buffer
    void asciiPrinter::addtobuffer(const std::vector<double>& functor_data, const std::vector<std::string>& functor_labels, const int vID, const int rank, const int pointID) 
    { 
      //TODO: If a functor gets called twice without the printer advancing the data will currently just be overwritten. Should generate an error or something.

      // Key for accessing buffer
      std::pair<int,int> bkey = std::make_pair(rank,pointID);
 
      // Register <pointID> as coming from process <rank>.
      AP_DBUG( std::cout << "My rank is (reported) " << rank << std::endl; )
      if(lastPointID.at(rank)==pointID)
      {
        // Don't need to do anything
      }
      else if(lastPointID.at(rank)==-1)
      {
        lastPointID.at(rank) = pointID;
      }
      else
      {
        std::pair<int,int> prevbkey = std::make_pair(rank,lastPointID[rank]);
        // Set previous model point accessed by this rank as ready to print
        buffer.at(prevbkey).readyToPrint = true;
        lastPointID.at(rank) = pointID;

        // Check whether it is time to dump the (completed) buffer points to disk
        if(buffer.size()>bufferlength) {
          AP_DBUG( std::cout << "asciiPrinter: Buffer full ("<< buffer.size() <<" records), running buffer dump"<<std::endl; )
          dump_buffer();
        }
      }

      AP_DBUG( std::cout << "asciiprinter: adding "<<functor_labels<<" to buffer"<<std::endl; )
      AP_DBUG( std::cout << "... at slot <rank=" << rank << ", pointID=" << pointID << ">" << std::endl;; )

      if( buffer.find(bkey)!=buffer.end() and buffer.at(bkey).readyToPrint==true )
      {
         std::string errmsg = "Error! Attempted to write to \"old\" model point \
buffer! Bug in asciiprinter.cpp somewhere. Buffer records are initialised with \
readyToPrint=false, and should not be written to again after this flag is set to \
true. The records are destroyed upon writing their contents to disk, and there \
is a unique record for every rank/pointID pair.";
         printer_error().raise(LOCAL_INFO, errmsg);
      }

      // Assign to buffer, adding keys if needed
      buffer[bkey].data[vID] = functor_data;

      if ( info_file_written == false )
      {
        if ( label_record.find(vID)==label_record.end() or functor_labels.size()>label_record.at(vID).size() )
        {
           // Assume the new, longer label list is better to use. This variation of functor_data length from point to point is kind of dangerous for an ascii output file though and we might want to forbid it. There is some probability that my method of allocating the columns according to the longest used by each functor in the first buffer dump will fail.
           label_record[vID] = functor_labels;
        }
      }
    }
 
    // write the printer buffer to file       
    void asciiPrinter::dump_buffer(bool force)
    {
      // Write record of what is in each column if we haven't done so yet
      // Note the downside of using a map as the buffer; the order of stuff in the output file is going
      // to be kind of haphazard due to the sorted order used by map. Will have to do more work to achieve
      // an ordering that reflects the order of stuff in, say, the inifile.
      //  force=true -- dumps all records regardless if they are "readyToPrint"
      AP_DBUG( std::cout << "dumping asciiprinter buffer" << std::endl; )
      AP_DBUG( std::cout << "lfpvfc 1" << std::endl; )

      // Open output file in append mode
      std::ofstream my_fstream;
      open_output_file(my_fstream, output_file, std::ofstream::app);
      my_fstream.precision(precision);

      std::map<int,int> newlineindexrecord(lineindexrecord);
      // Work out how to organise the output file            
      // To do this we need to go through the buffer and find the maximum length of vector associated with each VertexID.

      for (Buffer::iterator 
        bufentry = buffer.begin(); bufentry != buffer.end(); ++bufentry)
      {
        Record& record = bufentry->second; 
        for (LineBuf::iterator 
          item = record.data.begin(); item != record.data.end(); ++item)
        { 
          //item->first  - VertexID
          //item->second - std::vector<double> (result values)
          int oldlen = newlineindexrecord[item->first];
          int newlen = (item->second).size();
          newlineindexrecord[item->first] = std::max(oldlen, newlen);
        }
      }
      AP_DBUG( std::cout << "lfpvfc 2" << std::endl; )

      // Check if the output format has changed, and raise an error if so
      if (lineindexrecord.size()==0)
      {
        // initialise if empty
        lineindexrecord = newlineindexrecord;
      }
      else if (lineindexrecord!=newlineindexrecord)
      {
        std::ostringstream errmsg;
        errmsg << "Error! Output format has changed since last buffer dump! The asciiPrinter cannot handle this!"
               << "Details:" << std::endl;
        // First check if a new vertexID has appeared
        std::vector<int> new_vIDs;
        std::vector<int> increased_lengths;
        for (std::map<int,int>::iterator
          it = newlineindexrecord.begin(); it != newlineindexrecord.end(); ++it)
        {
          // try to find each key in the old lineindexrecord 
          if(lineindexrecord.find(it->first)==lineindexrecord.end())
          {
            new_vIDs.push_back(it->first);
          } // otherwise see if its data increased in length
          else if(it->second > lineindexrecord.at(it->first))
          {
            increased_lengths.push_back(it->first);    
          }
        }
        if(new_vIDs.size()!=0)
        {
          errmsg << "   The following vertexIDs are new since the last buffer dump (i.e. they did not try to print themselves during filling of any previous buffer):" <<std::endl;
          for(std::vector<int>::iterator it = new_vIDs.begin(); it!=new_vIDs.end(); ++it)
          {
            errmsg<<"      - vID="<<(*it)<<", label="<<label_record.at(*it)<<std::endl;
          }
        }
        if(increased_lengths.size()!=0)
        {
          errmsg << "   The following vertexIDs tried to print longer data vectors than were seen during filling of the first (and any other) previous buffer:" <<std::endl;
          for(std::vector<int>::iterator it = increased_lengths.begin(); it!=increased_lengths.end(); ++it)
          {
            errmsg<<"      - vID="<<(*it)<<", label="<<label_record.at(*it)<<std::endl;
            errmsg<<"          orig length="<<lineindexrecord.at(*it)<<", new length="<<newlineindexrecord.at(*it)<<std::endl;
          }
        }
        printer_error().raise(LOCAL_INFO,errmsg.str());
      }
      AP_DBUG( std::cout << "lfpvfc 3" << std::endl; )

      // Write the file explaining what is in each column of the output file
      if (info_file_written==false)
      {
        AP_DBUG( std::cout << "asciiPrinter: Writing info file..." << std::endl; )
         
        std::ofstream info_fstream;
        open_output_file(info_fstream, info_file, std::ofstream::trunc); // trunc mode overwrites old content

        int column_index = 1;
        for (std::map<int,int>::iterator
          it = lineindexrecord.begin(); it != lineindexrecord.end(); it++)
        {
          int vID        = it->first;
          int length     = it->second;     // slots reserved in output file for these results
          for (int i=0; i<length; i++)
          {
            AP_DBUG( std::cout<<"Column "<<column_index<<": "<<label_record.at(vID)[i]<<std::endl; )
            info_fstream<<"Column "<<column_index<<": "<<label_record.at(vID)[i]<<std::endl;
            column_index++;
          }
        }
        AP_DBUG( std::cout << "lfpvfc 3.1" << std::endl; )
        //info_fstream.flush();
        info_fstream.close();
        info_file_written=true;
      }

      AP_DBUG( std::cout << "lfpvfc 4" << std::endl; )

      // Actual dump of buffer to file
      for (Buffer::iterator 
        bufentry = buffer.begin(); bufentry != buffer.end(); /* Will increment in loop */ )
      {
        std::pair<int,int> bkey = bufentry->first;
        Record& record = bufentry->second; 
        AP_DBUG( std::cout << "asciiPrinter: Examining record with key <rank="<<bkey.first<<", pointID="<<bkey.second<<">"<< std::endl; )
        if(force or record.readyToPrint)
        {
          AP_DBUG( std::cout << "asciiPrinter: readyToPrint -- writing output..." << std::endl; )
          for (std::map<int,int>::iterator
            it = lineindexrecord.begin(); it != lineindexrecord.end(); ++it)
          { 
            // it->first  - int VertexID
            // it->second - int length

            std::vector<double>* results; // Pointer to results vector
            int reslength; // actual length of the current results vector

            LineBuf::iterator itdata = record.data.find(it->first);
            if( itdata == record.data.end())
            {
               // std::stringstream errss; 
               // errss << "Error! No data for vertex ID \"" << it->first 
               //       << "\" found in record <rank=" << bkey.first 
               //       << ", pointID=" << bkey.second << ">";
               // printer_error().raise(LOCAL_INFO, errss.str());

               // Not an error. This can happen if evaluation of a point is abandoned midway for whatever reason
               // Register results as zero length
               AP_DBUG( std::cout << "asciiPrinter: No data for vertex ID \"" << it->first 
                     << "\" found in record <rank=" << bkey.first 
                     << ", pointID=" << bkey.second << ">, printer will output 'null'" << std::endl; )
               reslength = 0;
            }
            else
            {
               results = &(itdata->second);
               reslength = results->size(); // actual length of the current results vector
            }
            int length     = it->second;     // slots reserved in output file for these results          
 
            // Print to the fstream!
            int colwidth = precision + 8;  // Just kind of guessing here; tweak as needed
            for (int j=0;j<length;j++)
            {
              if(j>=reslength)
              {
                // Finished parsing results vector; fill remaining empty slots with 'none'
                my_fstream<<std::setw(colwidth)<<"none";
              }
              else
              {
                // print an entry from the results vector
                my_fstream<<std::setw(colwidth+5)<<std::scientific<<(*results)[j]; //<<"\t";
              }
            }
            // Result printed
          }
          // Delete the record from the buffer and move to next one
          // Post-increment:  Increment the iterator first, THEN delete old one.
          AP_DBUG( std::cout << "asciiPrinter: Erasing record <rank="<<bkey.first<<", pointID="<<bkey.second<<">"<< std::endl; )
          buffer.erase(bufentry++);
        }
        else
        {
          AP_DBUG( std::cout << "asciiPrinter: Not readyToPrint -- leaving in buffer" << std::endl; )
          ++bufentry;
        } 
        // line printed, print endline character and go to next line
        my_fstream<<std::endl;
      }
      AP_DBUG( std::cout << "lfpvfc 5" << std::endl; )

      // buffer dump complete! Flush the fstream to ensure write to file happens.
      //my_fstream.flush();
      my_fstream.close();

      AP_DBUG( std::cout << "lfpvfc 6" << std::endl; )
    }
 
 
    /// @{ PRINT FUNCTIONS
    //----------------------------
    // Need to define one of these for every type we want to print!
    // Could use macros again to generate identical print functions 
    // for all types that have a << operator already defined.
   
    /// Template for print functions of "easy" types
    template<class T>
    void asciiPrinter::template_print(T const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    {
      std::vector<double> vdvalue(1,value); // For now everything has to end up as a vector of doubles
      std::vector<std::string> labels(1,label);
      addtobuffer(vdvalue,labels,IDcode,thread,pointID);       
    }

    void asciiPrinter::_print(int const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    { template_print(value,label,IDcode,thread,pointID); }
    void asciiPrinter::_print(bool const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    { template_print(value,label,IDcode,thread,pointID); }
   void asciiPrinter::_print(double const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    { template_print(value,label,IDcode,thread,pointID); }
    #ifndef STANDALONE  // Need to disable print functions for these if STANDALONE is defined (see baseprinter.hpp line ~41)
    void asciiPrinter::_print(unsigned int const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    { template_print(value,label,IDcode,thread,pointID); }
    #endif 
    // etc. as needed... 

    void asciiPrinter::_print(std::vector<double> const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    {
      std::vector<std::string> labels;
      labels.reserve(value.size());
      for(unsigned int i=0;i<value.size();i++)
      {
        // Might want to find some way to avoid doing this every single loop, seems kind of wasteful.
        std::stringstream ss;
        ss<<label<<"["<<i<<"]"; 
        labels.push_back(ss.str());
      }
      addtobuffer(value,labels,IDcode,thread,pointID);
    }
   
    void asciiPrinter::_print(triplet<double> const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    {
      std::vector<str> labels;
      std::vector<double> values;
      labels.reserve(3);
      values.reserve(3);
      labels.push_back(label+"(central)");
      labels.push_back(label+"(lower)");
      labels.push_back(label+"(upper)");
      values.push_back(value.central);
      values.push_back(value.lower);
      values.push_back(value.upper);
      addtobuffer(values,labels,IDcode,thread,pointID);
    }

    void asciiPrinter::_print(ModelParameters const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    {
      std::map<std::string, double> parameter_map = value.getValues();
      std::vector<std::string> names;
      std::vector<double> vdvalue;
      names.reserve(parameter_map.size());
      vdvalue.reserve(parameter_map.size());
      for (std::map<std::string, double>::iterator 
        it = parameter_map.begin(); it != parameter_map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        names.push_back( ss.str() ); 
        vdvalue.push_back( it->second );
      }
      addtobuffer(vdvalue,names,IDcode,thread,pointID);
    }
    
    /// @}

  } // end namespace printers
} // end namespace Gambit

#undef AP_DBUG
#undef AP_DEBUG_MODE
