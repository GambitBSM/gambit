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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Aug
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
  (std::complex<double>)               \
  (bool)                               \
  (map_str_dbl)                        \
  (map_str_map_str_dbl)                \
  (map_const_str_dbl)                  \
  (map_const_str_map_const_str_dbl)    \
  (ModelParameters)                    \
  (triplet<double>)                    \
  (map_intpair_dbl)                    \

#define HDF5_MODULE_BACKEND_TYPES      \
  (DM_nucleon_couplings)               \
  (DM_nucleon_couplings_fermionic_HP)  \
  (Flav_KstarMuMu_obs)                 \
  (BBN_container)                      \
  (FlavBit::flav_prediction)           \

#endif
