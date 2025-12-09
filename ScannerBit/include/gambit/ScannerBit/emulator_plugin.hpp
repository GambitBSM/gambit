//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Macros and related classes for declaring
///  scanner test functions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 August
///        2014 Feb
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)   
///  \date 2014 Dec
///
///  *********************************************

#ifndef EMULATOR_PLUGIN_HPP
#define EMULATOR_PLUGIN_HPP

#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/ScannerBit/scanner_util_types.hpp"
#include "gambit/ScannerBit/plugin_defs.hpp"
#include "gambit/ScannerBit/plugin_macros.hpp"

///\name Emulator Plugin Macros
///Macros used by the emulator plugins.
///@{
///Emulator plugin declaration.  Is of the form:  emulator_plugin(name, version)
#define emulator_plugin(...)           EMULATOR_PLUGIN( __VA_ARGS__ )
///@}

#define __EMULATOR_SETUP__                                                                                      \
using namespace Gambit::Scanner;                                                                                \
using Gambit::Printers::get_point_id;                                                                           \
using Gambit::Scanner::map_vector;                                                                              \
inline MPI_Comm &get_mpi_comm(){return get_input_value<MPI_Comm>(0);}                                           \

#define EMULATOR_PLUGIN(plug_name, ...)                                                                         \
    GAMBIT_PLUGIN_INITIALIZE(__EMULATOR_SETUP__, plug_name, emulator, __VA_ARGS__)                              \

#endif
