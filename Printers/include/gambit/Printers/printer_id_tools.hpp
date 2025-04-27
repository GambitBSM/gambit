//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Tools for accessing printers
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Gregory Martinez
///          (gregory.david.martinez@gmail.com)
///  \date 2013 August 2013 Feb 2014
///
///  *********************************************

#include "gambit/Utils/util_macros.hpp"
#include "gambit/Printers/baseprintermanager.hpp"
#include "gambit/Printers/basebaseprinter.hpp"

#ifndef PRINTER_ID_TOOLS_HPP
#define PRINTER_ID_TOOLS_HPP

#include <string>
#include <vector>

namespace Gambit
{
    namespace Printers
    {
        /// Global flag to indicate if auto-incrementing of the PointID by the likelihood container is allowed
        EXPORT_SYMBOLS bool& auto_increment();

        /// Returns unigue pointid;
        EXPORT_SYMBOLS unsigned long long int &get_point_id();

        /// Consolidated 'get id' function, for both main and aux
        EXPORT_SYMBOLS int get_param_id(const std::string& name, bool& is_new);
        EXPORT_SYMBOLS int get_param_id(const std::string& name);
        /// Get names of all parameters known to printer system (vector index corresponds to ID number)
        EXPORT_SYMBOLS std::vector<std::string> get_all_params();

        /// Returns unique positive parameter id; just a thin wrapper for get_param_id
        EXPORT_SYMBOLS int get_main_param_id(const std::string &);
        /// Extra argument returns true if new ID was assigned
        EXPORT_SYMBOLS int get_main_param_id(const std::string &, bool& is_new);

        /// Returns unique negative parameter id; just a thin wrapper for get_param_id
        EXPORT_SYMBOLS int get_aux_param_id(const std::string &);
        /// Extra argument returns true if new ID was assigned
        EXPORT_SYMBOLS int get_aux_param_id(const std::string &, bool& is_new);
    }

}

#endif
