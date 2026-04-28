//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for SusHi 1.7.0 backend
///
///  Exposes gg->h and bb->h Higgs production cross sections
///  at NNLO for MSSM, computed at LHC 13 TeV.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ida-Marie Fauske Johansson
///  \date 2026 Apr
///
///  *********************************************

#define BACKENDNAME SusHi
#define BACKENDLANG FORTRAN
#define VERSION 1.7.0
#define SAFE_VERSION 1_7_0
#define REFERENCE Harlander:2012pb,Harlander:2016hcx

LOAD_LIBRARY

BE_ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, MSSM63atQ_mG, MSSM63atMGUT_mG,
                MSSM63atQ_mA, MSSM63atMGUT_mA, MSSM63atQ_mA_mG, MSSM63atMGUT_mA_mG)

// Set input filename in SusHi's jfilein common block.
// fn: char buffer of length n (no hidden Fortran length argument via character*1 fn(n) pattern)
BE_FUNCTION(gambit_sushi_setfile, void, (char*, int&),
            "gambit_sushi_setfile_", "gambit_sushi_setfile")

// Run ggh+bbh cross-section computation.
// Returns xeff (ggh NNLO effective, pb) and SUbbh(3) (bbh NNLO, pb) via output args.
BE_FUNCTION(gambit_sushi_compute, void, (double&, double&),
            "gambit_sushi_compute_", "gambit_sushi_compute")

BE_CONV_FUNCTION(SusHi_ggh_xsec, double, (), "SusHi_ggh_xsec")
BE_CONV_FUNCTION(SusHi_bbh_xsec, double, (), "SusHi_bbh_xsec")

BE_INI_DEPENDENCY(MSSM_spectrum, Spectrum)

#include "gambit/Backends/backend_undefs.hpp"
