//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Sequence of all types printable by the ASCII
///  printer.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Mar
///
///  *********************************************

#ifndef __ASCIITYPES__
#define __ASCIITYPES__

#include "gambit/ScannerBit/printable_types.hpp"

#define ASCII_TYPES                         \
  SCANNER_PRINTABLE_TYPES                   \
  (std::string)                             \
  (triplet<double>)                         \
  (map_intpair_dbl)                         \


#define ASCII_BACKEND_TYPES                 \
  (DM_nucleon_couplings)                    \
  (DM_nucleon_couplings_fermionic_HP)       \
  (Flav_KstarMuMu_obs)                      \
  (BBN_container)                           \

#endif
