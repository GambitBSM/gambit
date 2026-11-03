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
#include "gambit/Printers/printers/common_print_overloads.hpp"

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

    // Piggyback off existing print functions to build standard overloads
    USE_COMMON_PRINT_OVERLOAD(SQLitePrinter, std::vector<double>)
    USE_COMMON_PRINT_OVERLOAD(SQLitePrinter, map_str_dbl)
    USE_COMMON_PRINT_OVERLOAD(SQLitePrinter, map_str_str)
    USE_COMMON_PRINT_OVERLOAD(SQLitePrinter, map_intpair_dbl)
    USE_COMMON_PRINT_OVERLOAD(SQLitePrinter, ModelParameters)
    USE_COMMON_PRINT_OVERLOAD(SQLitePrinter, triplet<double>)
    #ifndef SCANNER_STANDALONE
      USE_COMMON_PRINT_OVERLOAD(SQLitePrinter, DM_nucleon_couplings)
      USE_COMMON_PRINT_OVERLOAD(SQLitePrinter, BBN_container)
    #endif

    /// @}

  }
}

