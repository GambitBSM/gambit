//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Retriever overloads that do not differ from
///  printer to printer in the way they utilise
///  existing printer abilities.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2024 Feb
///
///  *********************************************

#pragma once

#include "gambit/Utils/stream_overloads.hpp"

namespace Gambit
{

  namespace Printers
  {

    /// Macro to call to activate a specific common print overload
    #define USE_COMMON_RETRIEVE_OVERLOAD(PRINTER, TYPE)                                                                        \
    void PRINTER :: _retrieve (TYPE& value, const std::string& label, const unsigned int mpirank, const unsigned long pointID) \
    { _common_retrieve<PRINTER>(*this,value,label,mpirank,pointID); }

    /// Macro for undefined retrieve functions
    #define UNDEFINED_RETRIEVE_OVERLOAD(PRINTER, TYPE)                                                                                     \
    bool PRINTER :: _retrieve (TYPE& /*out*/, const std::string& /*label*/, const unsigned int /*rank*/, const unsigned long /*pointID*/)  \
    { printer_error().raise(LOCAL_INFO,"NOT YET IMPLEMENTED"); return false; }

  }

}
