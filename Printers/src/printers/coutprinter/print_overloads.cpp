//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  cout interface printer class print function
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
///  \date 2018 Apr
///
///  *********************************************


#include "gambit/Printers/printers/coutprinter.hpp"


namespace Gambit
{
  namespace Printers
  {

    /// @{ PRINT FUNCTIONS
    /// Need to define one of these for every type we want to print!
    typedef unsigned short int ushort;

    /// Templatable print functions
    #define PRINT(TYPE) _print(TYPE const& value, const std::string& label, const int vID, const uint rank, const ulong pID) \
       { template_print(value,label,vID,rank,pID); }
    void coutPrinter::PRINT(int      )
    void coutPrinter::PRINT(uint     )
    void coutPrinter::PRINT(short    )
    void coutPrinter::PRINT(ushort   )
    void coutPrinter::PRINT(long     )
    void coutPrinter::PRINT(ulong    )
    void coutPrinter::PRINT(longlong )
    void coutPrinter::PRINT(ulonglong)
    void coutPrinter::PRINT(float    )
    void coutPrinter::PRINT(double   )
    void coutPrinter::PRINT(bool     )
    void coutPrinter::PRINT(std::vector<int      >)
    void coutPrinter::PRINT(std::vector<uint     >)
    void coutPrinter::PRINT(std::vector<short    >)
    void coutPrinter::PRINT(std::vector<ushort   >)
    void coutPrinter::PRINT(std::vector<long     >)
    void coutPrinter::PRINT(std::vector<ulong    >)
    void coutPrinter::PRINT(std::vector<longlong >)
    void coutPrinter::PRINT(std::vector<ulonglong>)
    void coutPrinter::PRINT(std::vector<float    >)
    void coutPrinter::PRINT(std::vector<double   >)
    void coutPrinter::PRINT(std::vector<bool     >)
    #undef PRINT

    void coutPrinter::_print(const map_str_dbl& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      // For maps of doubles, we split them up and print each named entry individually
      for (std::map<std::string, double>::const_iterator
           it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        _print(it->second, ss.str(), vID, mpirank, pointID);
      }
    }

    void coutPrinter::_print(ModelParameters const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
       // ModelParameters converted to a map for printing
       std::map<std::string, double> parameter_map = value.getValues();
       _print(parameter_map, label, vID, mpirank, pointID);
    }

    void coutPrinter::_print(triplet<double> const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      std::map<std::string, double> m;
      m["central"] = value.central;
      m["lower"] = value.lower;
      m["upper"] = value.upper;
      _print(m, label, vID, mpirank, pointID);
    }

    void coutPrinter::_print(map_intpair_dbl const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      // For maps of int pairs, we split them up and print each named entry individually
      for (map_intpair_dbl::const_iterator it = value.begin(); it != value.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first.first<<it->first.second;
        _print(it->second, ss.str(), vID, mpirank, pointID);
      }
    }

    #ifndef SCANNER_STANDALONE // All the types inside HDF5_MODULE_BACKEND_TYPES need to go inside this def guard.

      void coutPrinter::_print(DM_nucleon_couplings const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        m["Gp_SI"] = value.gps;
        m["Gn_SI"] = value.gns;
        m["Gp_SD"] = value.gpa;
        m["Gn_SD"] = value.gna;
        _print(m, label, vID, mpirank, pointID);
      }

      void coutPrinter::_print(DM_nucleon_couplings_fermionic_HP const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        m["Gp_SI"] = value.gps;
        m["Gn_SI"] = value.gns;
        m["Gp_q2"] = value.gp_q2;
        m["Gn_q2"] = value.gn_q2;
        _print(m, label, vID, mpirank, pointID);
      }

      void coutPrinter::_print(Flav_KstarMuMu_obs const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
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
