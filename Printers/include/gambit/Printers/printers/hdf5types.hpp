//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Sequence of all types printable by the HDF5
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
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2019 Nov
///
///  *********************************************

#ifndef __HDF5TYPES__
#define __HDF5TYPES__

#include "gambit/Elements/module_types_rollcall.hpp"

#define HDF5_TYPES                     \
  (int)                                \
  (uint)                               \
  (long)                               \
  (ulong)                              \
  (longlong)                           \
  (ulonglong)                          \
  (float)                              \
  (double)                             \
  (std::vector<double>)                \
  (bool)                               \
  (map_str_dbl)                        \
  (map_str_str)                        \
  (map_str_map_str_dbl)                \
  (map_const_str_dbl)                  \
  (map_const_str_map_const_str_dbl)    \
  (ModelParameters)                    \
  (triplet<double>)                    \
  (map_intpair_dbl)                    \
  (flav_prediction)                    \

#define HDF5_RETRIEVABLE_TYPES \
  HDF5_TYPES \
  (MSSM_SLHAstruct) \
  (SMslha_SLHAstruct)

#define HDF5_BACKEND_TYPES             \
  (DM_nucleon_couplings)               \
  (BBN_container)                      \

#endif
