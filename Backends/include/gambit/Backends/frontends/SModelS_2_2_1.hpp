//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend file for SModelS 2.2.1. 
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Martin White
///          (martin.white@adelaide.edu.au)
///  \date 2022 Oct
///
///  *********************************************

#define BACKENDNAME smodels
#define BACKENDLANG Python3
#define VERSION 2.2.1
#define SAFE_VERSION 2_2_1
#define REFERENCE Ambrogi:2017neo,Ambrogi:2018ujg,Kraml:2013mwa,Bierlich:2022pfr,Beenakker:1996ch,Beenakker:2015rna,Beenakker:2011fu,Beenakker:2010nq,Beenakker:1997ut,Beenakker:2011fu,Beenakker:2009ha,Kulesza:2009kq,Kulesza:2008jb


/* The following macro imports the module in the Python interpreter
 * when this header file is included somewhere. */

LOAD_LIBRARY

#ifdef HAVE_PYBIND11

  BE_FUNCTION(smodels_results, double, (const str&), "run_smodels", "smodels_results")

#endif

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

