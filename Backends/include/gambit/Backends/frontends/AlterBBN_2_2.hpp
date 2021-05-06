//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for AlterBBN v 2.2
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date   2018 Jun
///
///  \author Patrick Stöcker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2019 Sep
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  *********************************************


#define BACKENDNAME AlterBBN
#define BACKENDLANG CC
#define VERSION 2.2
#define SAFE_VERSION 2_2


LOAD_LIBRARY

BE_FUNCTION(Init_cosmomodel, void, (AlterBBN_2_2::relicparam*), "Init_cosmomodel", "Init_cosmomodel")
BE_FUNCTION(nucl_err, int, (AlterBBN_2_2::relicparam*,double*,double*), "nucl_err", "nucl_err")

BE_CONV_FUNCTION(get_NNUC, size_t, (), "get_NNUC")
BE_CONV_FUNCTION(get_abund_map_AlterBBN, map_str_int, (), "get_abund_map_AlterBBN")
BE_CONV_FUNCTION(fill_cosmomodel, void, (AlterBBN_2_2::relicparam*, map_str_dbl &), "Init_AlterBBN")
BE_CONV_FUNCTION(call_nucl_err, int, (map_str_dbl&,double*,double*), "call_nucl_err")

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
