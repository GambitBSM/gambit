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
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2018 Dec
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Aug
///
///  *********************************************

#ifndef __SQLITETYPES__
#define __SQLITETYPES__

#define SQL_TYPES           \
  (int)                     \
  (uint)                    \
  (long)                    \
  (ulong)                   \
  (longlong)                \
  (ulonglong)               \
  (float)                   \
  (double)                  \
  (std::vector<double>)     \
  (std::complex<double>)    \
  (bool)                    \
  (map_str_dbl)             \
  (ModelParameters)         \
  (triplet<double>)         \
  (map_intpair_dbl)         \


#define SQL_BACKEND_TYPES             \
  (DM_nucleon_couplings)              \
  (DM_nucleon_couplings_fermionic_HP) \
  (Flav_KstarMuMu_obs)                \
  (BBN_container)                     \


#endif
