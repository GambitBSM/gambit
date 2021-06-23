//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  HDF5 interface printer class print function
///  overloads.  Add a new overload of the _print
///  function in this file if you want to be able
///  to print a new type.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 May
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 March
///
///  *********************************************


#include "gambit/Printers/printers/hdf5printer.hpp"
#include "gambit/Printers/printers/common_print_overloads.hpp"


namespace Gambit
{
  namespace Printers
  {

    /// @{ PRINT FUNCTIONS
    /// Need to define one of these for every type we want to print!

    /// Templatable print functions
    #define PRINT(TYPE) _print(TYPE const& value, const std::string& label, const int vID, const uint rank, const ulong pID) \
       { template_print(value,label,vID,rank,pID); }
    void HDF5Printer::PRINT(int      )
    void HDF5Printer::PRINT(uint     )
    void HDF5Printer::PRINT(long     )
    void HDF5Printer::PRINT(ulong    )
    void HDF5Printer::PRINT(float    )
    void HDF5Printer::PRINT(double   )
    #undef PRINT

    #define PRINTAS(INTYPE,OUTTYPE) _print(INTYPE const& value, const std::string& label, const int vID, const uint rank, const ulong pID) \
    { template_print((OUTTYPE)value,label,vID,rank,pID); }
    void HDF5Printer::PRINTAS(longlong, long)
    void HDF5Printer::PRINTAS(ulonglong, ulong)
    #undef PRINTAS

    /// Bools can't quite use the template print function directly, since there
    /// are some issues with bools and MPI/HDF5 types. Easier to just convert
    /// the bool to an int first.
    void HDF5Printer::_print(bool const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      unsigned int val_as_uint = value;
      template_print(val_as_uint,label,vID,mpirank,pointID);
    }

    void HDF5Printer::_print(std::vector<double> const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      // We will write to several 'double' buffers, rather than a single vector buffer.
      // Change this once a vector buffer is actually available
      // Retrieve the buffer manager for buffers with the desired output type
      auto& buffer_manager = get_mybuffermanager<double>(pointID,mpirank);

#ifdef HDEBUG_MODE
      std::cout<<"printing vector<double>: "<<label<<std::endl;
      std::cout<<"pointID: "<<pointID<<", mpirank: "<<mpirank<<std::endl;
#endif

      for(unsigned int i=0;i<value.size();i++)
      {
        // Might want to find some way to avoid doing this every single loop, seems kind of wasteful.
        std::stringstream ss;
        ss<<label<<"["<<i<<"]";
        //labels.push_back(ss.str());

        // Write to each buffer
        //buffer_manager.get_buffer(vID, i, ss.str()).append(value[i]);
        PPIDpair ppid(pointID,mpirank);
        if(synchronised)
        {
          // Write the data to the selected buffer ("just works" for simple numeric types)
          buffer_manager.get_buffer(vID, i, ss.str()).append(value[i],ppid);
        }
        else
        {
          // Queue up a desynchronised ("random access") dataset write to previous scan iteration
          if(not seen_PPID_before(ppid))
          {
            add_PPID_to_list(ppid);
          }
          buffer_manager.get_buffer(vID, i, ss.str()).RA_write(value[i],ppid,primary_printer->global_index_lookup);
        }
      }
    }

    void HDF5Printer::_print(const map_str_dbl& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      // Retrieve the buffer manager for buffers with this type
      auto& buffer_manager = get_mybuffermanager<double>(pointID,mpirank);

      unsigned int i=0; // index for each buffer
      for (std::map<std::string, double>::const_iterator
           it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        PPIDpair ppid(pointID,mpirank);
        // Write to each buffer
        //buffer_manager.get_buffer(vID, i, ss.str()).append(it->second);
        if(synchronised)
        {
          // Write the data to the selected buffer ("just works" for simple numeric types)
          buffer_manager.get_buffer(vID, i, ss.str()).append(it->second,ppid);
        }
        else
        {
          // Queue up a desynchronised ("random access") dataset write to previous scan iteration
          if(not seen_PPID_before(ppid))
          {
            add_PPID_to_list(ppid);
          }
          buffer_manager.get_buffer(vID, i, ss.str()).RA_write(it->second,ppid,primary_printer->global_index_lookup);
        }
        i++;
      }
    }

    void HDF5Printer::_print(map_intpair_dbl const& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      // Retrieve the buffer manager for buffers with this type
      auto& buffer_manager = get_mybuffermanager<double>(pointID,mpirank);

      unsigned int i=0; // index for each buffer
      for (std::map<std::pair<int,int>, double>::const_iterator it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        PPIDpair ppid(pointID,mpirank);
        // Write to each buffer
        //buffer_manager.get_buffer(vID, i, ss.str()).append(it->second);
        if(synchronised)
        {
          // Write the data to the selected buffer ("just works" for simple numeric types)
          buffer_manager.get_buffer(vID, i, ss.str()).append(it->second,ppid);
        }
        else
        {
          // Queue up a desynchronised ("random access") dataset write to previous scan iteration
          if(not seen_PPID_before(ppid))
          {
            add_PPID_to_list(ppid);
          }
          buffer_manager.get_buffer(vID, i, ss.str()).RA_write(it->second,ppid,primary_printer->global_index_lookup);
        }
        i++;
      }
    }

    // Piggyback off existing print functions to build standard overloads
    USE_COMMON_PRINT_OVERLOAD(HDF5Printer, ModelParameters)
    USE_COMMON_PRINT_OVERLOAD(HDF5Printer, triplet<double>)
    #ifndef SCANNER_STANDALONE
      USE_COMMON_PRINT_OVERLOAD(HDF5Printer, DM_nucleon_couplings)
      USE_COMMON_PRINT_OVERLOAD(HDF5Printer, DM_nucleon_couplings_fermionic_HP)
      USE_COMMON_PRINT_OVERLOAD(HDF5Printer, Flav_KstarMuMu_obs)
      USE_COMMON_PRINT_OVERLOAD(HDF5Printer, BBN_container)
    #endif

    /// @}

  }
}

#undef DBUG
#undef DEBUG_MODE
