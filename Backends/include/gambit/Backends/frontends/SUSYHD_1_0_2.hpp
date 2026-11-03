//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for SUSYHD.
///
///  *********************************************
///
///  Authors (add name and sate if you modify):
///
///  \author Tomas Gonzalo
///  \date 2016 Dec
///
///  *********************************************

#define BACKENDNAME SUSYHD
#define BACKENDLANG MATHEMATICA
#define VERSION 1.0.2
#define SAFE_VERSION 1_0_2
#define REFERENCE PardoVega:2015eno

LOAD_LIBRARY

BE_ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, MSSM63atMGUT_mG, MSSM63atQ_mG)

BE_FUNCTION(MHiggs, MReal, (const MList<MReal>&), "MHiggs", "SUSYHD_MHiggs")
BE_FUNCTION(DeltaMHiggs, MReal, (const MList<MReal>&), "\\[CapitalDelta]MHiggs", "SUSYHD_DeltaMHiggs")
BE_FUNCTION(SetSMparameters, MVoid, (const MReal&, const MReal&), "SetSMparameters", "SUSYHD_SetSMparameters")

/* Convenience functions (declarations) */

// Initialisation function (dependencies)
BE_INI_DEPENDENCY(SMINPUTS, SMInputs)
BE_INI_DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)

// Undefine macros toa void conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
