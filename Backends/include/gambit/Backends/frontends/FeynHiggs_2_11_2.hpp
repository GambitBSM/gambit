//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
/// Frontend for FeynHiggs backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Rogan
///  \date Sep 2015
///
///  \author Pat Scott
///  \date Dec 2015
///
///  *****************************************


#define BACKENDNAME FeynHiggs
#define BACKENDLANG FORTRAN
#define VERSION 2.11.2
#define SAFE_VERSION 2_11_2

/* The following macro loads the library using dlopen
 * when this header file is included somewhere. */

LOAD_LIBRARY

/* Next we use macros BE_VARIABLE and BE_FUNCTION to load pointers
 * (using dlsym) to the variables and functions within the library.
 *
 * The macros also set up a minimal interface providing 'get/set'
 * functions for the library variables and function pointers
 * for the library functions.
 *
 * These functions are then wrapped in functors that the core can connect
 * to the modules via the rollcall system */

/* Syntax for BE_FUNCTION:
 * BE_FUNCTION([choose function name], [type], [arguement types], "[exact symbol name]", "[choose capability name]") */


BE_FUNCTION(FHSetFlags, void, (int&,int&,int&,int&,int&,int&,int&,int&,int&,int&), "fhsetflags_", "FHSetFlags")

BE_FUNCTION(FHSetDebug, void, (int&), "fhsetdebug_", "FHSetDebug")

BE_FUNCTION(FHSetSMPara, void, (int&,fh_creal&,fh_creal&,fh_creal&,fh_creal&,fh_creal&,
        fh_creal&,fh_creal&,fh_creal&,fh_creal&,fh_creal&,fh_creal&,
        fh_creal&,fh_creal&,fh_creal&,fh_creal&,fh_creal&,fh_creal&), "fhsetsmpara_", "FHSetSMPara")

BE_FUNCTION(FHSetPara, void, (int&,fh_creal&,fh_creal&,fh_creal&,fh_creal&,fh_creal&,
            fh_creal&,fh_creal&,fh_creal&,fh_creal&,fh_creal&,
            fh_creal&,fh_creal&,fh_creal&,fh_creal&,fh_creal&,
            fh_creal&,fh_creal&,fh_creal&,fh_creal&,fh_creal&,
            fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,
            fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,
            fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,
            fh_ccomplex&,fh_creal&,fh_creal&,fh_creal&), "fhsetpara_", "FHSetPara")

BE_FUNCTION(FHSetNMFV, void, (int&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,
            fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,
            fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,
            fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,
            fh_ccomplex&,fh_ccomplex&), "fhsetnmfv_", "FHSetNMFV")

BE_FUNCTION(FHSetLFV, void, (int&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,
           fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,
           fh_ccomplex&,fh_ccomplex&,fh_ccomplex&,fh_ccomplex&), "fhsetlfv_", "FHSetLFV")

BE_FUNCTION(FHConstraints, void, (int&,fh_real&,fh_real&,fh_real&,fh_real&,
          fh_real&,fh_real&,fh_real&,fh_real&,fh_real&,int&), "fhconstraints_", "FHConstraints")

BE_FUNCTION(FHFlavour, void, (int&,fh_real&,fh_real&,fh_real&,fh_real&,fh_real&,fh_real&), "fhflavour_", "FHFlavour")

BE_FUNCTION(FHGetPara, void, (int&,int&,
            Farray<fh_real, 1,2, 1,5, 1,3>&, Farray<fh_complex, 1,2, 1,2, 1,5, 1,3>&,
            Farray<fh_real, 1,6, 1,5>&, Farray<fh_complex, 1,36, 1,5>&,
            Farray< fh_real,1,2>&, Farray< fh_complex,1,4>&,
            Farray< fh_complex,1,4>&, Farray< fh_real,1,4>&,
            Farray< fh_complex,1,16>&, fh_complex&, fh_real&,
            Farray< fh_real,1,4>&, fh_real&), "fhgetpara_", "FHGetPara")

BE_FUNCTION(FHHiggsCorr, void, (int&, Farray< fh_real,1,4>&, fh_complex&, Farray<fh_complex, 1,3, 1,3>&,
        Farray<fh_complex, 1,3, 1,3>&), "fhhiggscorr_", "FHHiggsCorr")

BE_FUNCTION(FHUncertainties, void, (int&, Farray< fh_real,1,4>&, fh_complex&, Farray<fh_complex, 1,3, 1,3>&,
            Farray<fh_complex, 1,3, 1,3>&), "fhuncertainties_", "FHUncertainties")

BE_FUNCTION(FHSelectUZ, void, (int&,int&,int&,int&), "fhselectuz_", "FHSelectUZ")

BE_FUNCTION(FHCouplings, void, (int&, Farray< fh_complex,1,681>&, Farray< fh_complex,1,231>&,
                                Farray< fh_real,1,978>&, Farray< fh_real,1,250>&, int&), "fhcouplings_", "FHCouplings")

BE_FUNCTION(FHHiggsProd, void, (int&, fh_real&, Farray< fh_real,1,52>&), "fhhiggsprod_", "FHHiggsProd")

// Initialisation function (dependencies)
BE_INI_DEPENDENCY(unimproved_MSSM_spectrum, Spectrum)   // Need MSSM spectrum inputs to initialize FH

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

