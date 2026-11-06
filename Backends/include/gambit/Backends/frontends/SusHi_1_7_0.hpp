//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for SusHi 1.7.0 backend
///
///  Exposes gg->h and bb->h Higgs production cross sections
///  at NNLO for MSSM, computed at LHC 13 TeV.
///
///  The frontend talks to SusHi entirely in memory: the
///  parameter point is written straight into the Fortran
///  COMMON blocks that SusHi's own SLHA reader would fill
///  when parsing an input file (see backend_types/SusHi.hpp),
///  and SusHi is then run in a "no input file" mode added by
///  the GAMBIT patch.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ida-Marie Fauske Johansson
///  \date 2026 Apr
///
///  \author Anders Kvellestad
///  \date 2026 Nov
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

// SusHi's SLHA input COMMON blocks (src/commons/common-slha.f).  These are
// the variables that SusHi's readslha/slhablocks routines fill when parsing
// an SLHA input file. The frontend fills them directly instead.
BE_VARIABLE(slhaparam,   SusHi_slhaparam_type,   "slhaparam_",   "SusHi_slhaparam")    // real-valued entries + PDF set names
BE_VARIABLE(slhamass,    SusHi_slhamass_type,    "slhamass_",    "SusHi_slhamass")     // Block MASS
BE_VARIABLE(slhamix,     SusHi_slhamix_type,     "slhamix_",     "SusHi_slhamix")      // mixing matrix blocks (STOPMIX, SBOTMIX, ...)
BE_VARIABLE(slhaint,     SusHi_slhaint_type,     "slhaint_",     "SusHi_slhaint")      // integer-valued entries (VEGAS, PDFSPEC, ...)
BE_VARIABLE(slhareal,    SusHi_slhareal_type,    "slhareal_",    "SusHi_slhareal")     // further real-valued entries (GGHMT, QQH, TMP)
BE_VARIABLE(slhalogical, SusHi_slhalogical_type, "slhalogical_", "SusHi_slhalogical")  // "entry given" flags for all of the above

// SusHi's input/output file names (src/commons/common-inputoutput.f).
// No files are used by this frontend; see SusHi_run_point.
BE_VARIABLE(fileinfileout, SusHi_fileinfileout_type, "fileinfileout_", "SusHi_fileinfileout")

// Function pointer SusHi's fatal-error routine (gsdie) calls instead of STOP.
BE_VARIABLE(ErrorHandler_cptr, fptr_void, "C_sushi_errorhandler_cptr", "sushi_errorhandler_cptr")

// Run SusHi's ggh+bbh cross-section computation on the input currently held
// in the SLHA COMMON blocks above (GAMBIT patch: src/sushi/sushi_gambit_interface.f).
// Returns xeff (ggh NNLO effective, pb) and SUbbh(3) (bbh NNLO, pb), followed by
// their VEGAS integration errors [pb], via output args.
BE_FUNCTION(gambit_sushi_compute, void, (double&, double&, double&, double&),
            "gambit_sushi_compute_", "gambit_sushi_compute")

// Reset SusHi's RANLUX random number generator (used by VEGAS) to the state
// it has at the start of a fresh standalone SusHi run. This gives the same
// behaviour as if we were launching a standalone SusHi at each parameter point.
BE_FUNCTION(gambit_sushi_reset_ranlux, void, (),
            "gambit_sushi_reset_ranlux_", "gambit_sushi_reset_ranlux")

// Takes a map of optional settings (see getSusHi_h_xsec_total in ColliderBit_Higgs.cpp
// and the option list at the top of SusHi_run_point in SusHi_1_7_0.cpp).
// Output args: ggh, bbh cross sections, then their VEGAS integration errors [pb].
// Fills SusHi's input COMMON blocks from the spectrum and runs the ggh/bbh NNLO
// computation. 
BE_CONV_FUNCTION(SusHi_run_point, void, (const Spectrum&, const map_str_dbl&, double&, double&, double&, double&), "SusHi_run_point")

#include "gambit/Backends/backend_undefs.hpp"
