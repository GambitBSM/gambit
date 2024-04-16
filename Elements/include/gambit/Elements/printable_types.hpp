//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  List of types printable by GAMBIT printers.
///  Make sure to manually update this list
///  when you want to add a new printable type.
///
///  *********************************************
///
///  Authors:
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2016 Jan
///
///  *********************************************

#ifndef __printable_types_hpp__
#define __printable_types_hpp__

#include "gambit/Elements/types_rollcall.hpp"
#include "gambit/ScannerBit/printable_types.hpp"

// Types that Gambit printers can output (if printer plugin is properly equipped)
#define PRINTABLE_TYPES               \
  SCANNER_PRINTABLE_TYPES             \
  (map_const_str_dbl)                 \
  (map_str_map_str_dbl)               \
  (map_const_str_map_const_str_dbl)   \
  (map_intpair_dbl)                   \
  (triplet<double>)                   \
  (flav_prediction)                   \
  (DM_nucleon_couplings)              \
  (BBN_container)

// Types that can be retrieved from Gambit printer output (if printer plugin is properly equipped)
// Generally needs to be the same as the printable types, i.e. should be able to retrieve everything.
#define RETRIEVABLE_TYPES \
  PRINTABLE_TYPES \
  (MSSM_SLHAstruct) \
  (SMslha_SLHAstruct)

#endif // defined __printable_types_hpp__
