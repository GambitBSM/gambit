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

#ifndef OBJECTIVE_PLUGIN_HPP
#define OBJECTIVE_PLUGIN_HPP

#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/ScannerBit/plugin_defs.hpp"
#include "gambit/ScannerBit/plugin_macros.hpp"

///\name Objective Plugin Macros
///Macros used by the objective plugins.
///@{
///Objective plugin declaration.  Is of the form:  objective_plugin(name, version)
#define objective_plugin(...)           OBJECTIVE_PLUGIN( __VA_ARGS__ )
///@}

#define __OBJECTIVE_SETUP__                                                                                     \
using namespace Gambit::Scanner;                                                                                \
using Gambit::Printers::get_point_id;                                                                           \
                                                                                                                \
inline std::vector<std::string> &get_keys() {return get_input_value<std::vector<std::string>>(0);}              \
inline void set_dimension(unsigned int val) {get_input_value<unsigned int>(1) = val;}                           \
inline void print_parameters(std::unordered_map<std::string, double> &key_map)                                  \
{                                                                                                               \
    using Gambit::Printers::get_main_param_id;                                                                  \
    Gambit::Scanner::printer *printer = get_printer().get_stream();                                             \
    for (auto it = get_keys().begin(), end = get_keys().end(); it != end; ++it)                                 \
    {                                                                                                           \
        printer->print(key_map[*it], *it, get_main_param_id(*it), printer->getRank(), get_point_id());          \
    }                                                                                                           \
}                                                                                                               \

#define OBJECTIVE_PLUGIN(plug_name, ...)                                                                        \
    GAMBIT_PLUGIN_INITIALIZE(__OBJECTIVE_SETUP__, plug_name, objective, __VA_ARGS__)                            \

#endif
