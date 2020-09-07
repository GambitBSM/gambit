//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  SQLite interface printer class print function
///  overloads.  Add a new overload of the _print
///  function in this file if you want to be able
///  to print a new type.
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


#include "gambit/Printers/printers/sqliteprinter.hpp"
#include "gambit/Utils/stream_overloads.hpp"

namespace Gambit
{
  namespace Printers
  {

    /// @{ PRINT FUNCTIONS
    /// Need to define one of these for every type we want to print!

    /// Templatable print functions
    #define PRINT(TYPE,SQLTYPE) _print(TYPE const& value, const std::string& label, const int vID, const uint rank, const ulong pID) \
       { template_print(value,label,vID,rank,pID,SQLTYPE); }
    void SQLitePrinter::PRINT(bool     ,"INTEGER")
    void SQLitePrinter::PRINT(int      ,"INTEGER")
    void SQLitePrinter::PRINT(uint     ,"INTEGER")
    void SQLitePrinter::PRINT(long     ,"INTEGER")
    void SQLitePrinter::PRINT(ulong    ,"INTEGER")
    void SQLitePrinter::PRINT(longlong ,"INTEGER")
    void SQLitePrinter::PRINT(ulonglong,"INTEGER")
    void SQLitePrinter::PRINT(float    ,"REAL")
    void SQLitePrinter::PRINT(double   ,"REAL")
    #undef PRINT

    void SQLitePrinter::_print(ModelParameters const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      std::map<std::string, double> parameter_map = value.getValues();
      _print(parameter_map, label, vID, mpirank, pointID);
    }

    void SQLitePrinter::_print(const map_str_dbl& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      for (std::map<std::string, double>::const_iterator
           it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        _print(it->second, ss.str(), vID, mpirank, pointID);
      }
    }

    void SQLitePrinter::_print(std::vector<double> const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      for(unsigned int i=0;i<value.size();i++)
      {
        std::stringstream ss;
        ss<<label<<"["<<i<<"]";
        _print(value.at(i), ss.str(), vID, mpirank, pointID);
      }
    }

    void SQLitePrinter::_print(triplet<double> const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      std::map<std::string, double> m;
      m["central"] = value.central;
      m["lower"] = value.lower;
      m["upper"] = value.upper;
      _print(m, label, vID, mpirank, pointID);
    }

    void SQLitePrinter::_print(map_intpair_dbl const& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      for (auto it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::("<<it->first.first<<","<<it->first.second<<")";
        _print(it->second, ss.str(), vID, mpirank, pointID);
      }
    }

    #ifndef SCANNER_STANDALONE // All types that are defined by backends need to go inside this include guard
      void SQLitePrinter::_print(DM_nucleon_couplings const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        m["Gp_SI"] = value.gps;
        m["Gn_SI"] = value.gns;
        m["Gp_SD"] = value.gpa;
        m["Gn_SD"] = value.gna;
        _print(m, label, vID, mpirank, pointID);
      }

      void SQLitePrinter::_print(DM_nucleon_couplings_fermionic_HP const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        m["Gp_SI"] = value.gps;
        m["Gn_SI"] = value.gns;
        m["Gp_q2"] = value.gp_q2;
        m["Gn_q2"] = value.gn_q2;
        _print(m, label, vID, mpirank, pointID);
      }

      void SQLitePrinter::_print(Flav_KstarMuMu_obs const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
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
