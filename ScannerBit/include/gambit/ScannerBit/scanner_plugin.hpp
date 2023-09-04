//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  declaration for scanner module
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
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2016 Jul
///
///  *********************************************

#ifndef SCANNER_PLUGIN_HPP
#define SCANNER_PLUGIN_HPP

#include "gambit/ScannerBit/scanner_utils.hpp"
#include "gambit/ScannerBit/plugin_defs.hpp"
#include "gambit/ScannerBit/plugin_macros.hpp"
#include "gambit/ScannerBit/factory_defs.hpp"

// Needed for plugin_info access. If there is a better way to call the "early_shutdown_in_progress"
// function then feel free to change this.
#include "gambit/ScannerBit/plugin_loader.hpp"

///\name Scanner Plugin Macros 
///Macros used by the scanner plugin
///@{
///Defines a scanner plugin.  Has the form:  scanner_plugin(name, version).
#define scanner_plugin(...)             SCANNER_PLUGIN(__VA_ARGS__)
///@}

#define __SCANNER_SETUP__                                                                   \
using namespace Gambit::Scanner;                                                            \
                                                                                            \
void *get_purpose(const std::string &purpose)                                               \
{                                                                                           \
    void *ptr = (get_input_value<Factory_Base>(1))(purpose);                                \
    static_cast <Function_Base<void(void)>*>(ptr)->setPurpose(purpose);                     \
    static_cast <Function_Base<void(void)>*>(ptr)->setPrinter(get_printer().get_stream());  \
    static_cast <Function_Base<void(void)>*>(ptr)->setPrior(&get_prior());                  \
    assign_aux_numbers(purpose, "pointID", "MPIrank");                                      \
                                                                                            \
    return ptr;                                                                             \
}                                                                                           \
                                                                                            \
inline unsigned int &get_dimension() {return get_input_value<unsigned int>(0);}             \

#define SCANNER_PLUGIN(plug_name, ...)                                                      \
    GAMBIT_PLUGIN_INITIALIZE(__SCANNER_SETUP__, plug_name, scanner, __VA_ARGS__)            \
        
#endif
