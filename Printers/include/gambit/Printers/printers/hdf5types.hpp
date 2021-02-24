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

#define HDF5_TYPES          \
  (int)                     \
  (uint)                    \
  (long)                    \
  (ulong)                   \
  (longlong)                \
  (ulonglong)               \
  (float)                   \
  (double)                  \
  (std::vector<double>)     \
  (bool)                    \
  (map_str_dbl)             \
  (ModelParameters)         \
  (triplet<double>)         \
  (map_intpair_dbl)         

#define HDF5_RETRIEVABLE_TYPES \
  HDF5_TYPES \
  (MSSM_SLHAstruct) \
  (SMslha_SLHAstruct)

#define HDF5_BACKEND_TYPES            \
  (DM_nucleon_couplings)              \
  (DM_nucleon_couplings_fermionic_HP) \
  (Flav_KstarMuMu_obs)                \
  (BBN_container)                     \

#endif
