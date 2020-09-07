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
    //void HDF5Printer::PRINT(longlong )
    //void HDF5Printer::PRINT(ulonglong)
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

    void HDF5Printer::_print(ModelParameters const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      std::map<std::string, double> parameter_map = value.getValues();
      _print(parameter_map, label, vID, mpirank, pointID);
    }

    void HDF5Printer::_print(triplet<double> const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      std::map<std::string, double> m;
      m["central"] = value.central;
      m["lower"] = value.lower;
      m["upper"] = value.upper;
      _print(m, label, vID, mpirank, pointID);
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

    #ifndef SCANNER_STANDALONE // All the types inside HDF5_MODULE_BACKEND_TYPES need to go inside this def guard.

      void HDF5Printer::_print(DM_nucleon_couplings const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        m["Gp_SI"] = value.gps;
        m["Gn_SI"] = value.gns;
        m["Gp_SD"] = value.gpa;
        m["Gn_SD"] = value.gna;
        _print(m, label, vID, mpirank, pointID);
      }

      void HDF5Printer::_print(DM_nucleon_couplings_fermionic_HP const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        m["Gp_SI"] = value.gps;
        m["Gn_SI"] = value.gns;
        m["Gp_q2"] = value.gp_q2;
        m["Gn_q2"] = value.gn_q2;
        _print(m, label, vID, mpirank, pointID);
      }

      void HDF5Printer::_print(Flav_KstarMuMu_obs const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        std::ostringstream bins;
        bins << value.q2_min << "_" << value.q2_max;
        m["BR_"+bins.str()] = value.BR;
        m["AFB_"+bins.str()] = value.AFB;
        m["FL_"+bins.str()] = value.FL;
        m["S3_"+bins.str()] = value.S3;
        m["S4_"+bins.str()] = value.S4;
        m["S5_"+bins.str()] = value.S5;
        m["S7_"+bins.str()] = value.S7;
        m["S8_"+bins.str()] = value.S8;
        m["S9_"+bins.str()] = value.S9;
        _print(m, label, vID, mpirank, pointID);
      }

    #endif

    /// @}

  }
}

#undef DBUG
#undef DEBUG_MODE
