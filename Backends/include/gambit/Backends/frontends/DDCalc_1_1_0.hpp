//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend header for the DDCalc backend.
///
///  Compile-time registration of available
///  functions and variables from this backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2014 Jul
///
///  \author Christopher Savage
///          (chris@savage.name)
///  \date 2014 Sept
///  \date 2015 Jan,Feb,June
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016 Apr
///
///  \author Sebastian Wild
///          (sebastian.wild@ph.tum.de)
///  \date 2016 Aug
///
///  \author Felix Kahlhoefer
///          (felix.kahlhoefer@desy.de)
///  \date 2016 Aug
///
///  *********************************************

// Identify backend
#define BACKENDNAME DDCalc
#define BACKENDLANG Fortran
#define VERSION 1.1.0
#define SAFE_VERSION 1_1_0
#define REFERENCE GAMBIT:2017fax

// Load it
LOAD_LIBRARY

// BACKEND FUNCTIONS =======================================

/* Import functions.

  BE_FUNCTION arguments:
    * Function name used within GAMBIT.
    * Function return type (void for fortran subroutines).
    * Argument type list (pointers for fortran routines).
    * Symbol name in compiled object file (see below).
    * Capability name.

  Naming conventions for the object/library symbols of Fortran module
  routines are typically:
     __<modulename>_MOD_<routinename>  [gfortran]
     <modulename>_mp_<routinename>_    [ifort]
  where the module and routine names are in lower case.  To avoid
  compiler-dependendent symbol names, BIND() statements are used in
  the Fortran source code to explicitly specify the symbol names.
  [n.b.: For non-module routines, '<routinename>_' (again in lower
  case) is the convention for both compilers.]  We take as our naming
  convention for the externally-accessible DDCalc routines:
     C_DDCalc_<modulename(kinda)>_routinename>
  The 'C' is to signify routines intended for calling from C/C++
  (argument and return types are expressly declared to be type-
  compatible with the C bool, int, and double types).
 */

// Default initialisation of three main classes via factory functions
BE_FUNCTION(DDCalc_InitWIMP,     int, (),            "C_DDWIMP_ddcalc_initwimp", "InitWIMP")
BE_FUNCTION(DDCalc_InitHalo,     int, (),            "C_DDHalo_ddcalc_inithalo", "InitHalo")
BE_FUNCTION(DDCalc_InitDetector, int, (const bool&), "C_DDExperiments_ddcalc_initdetector", "InitDetector")

// Initialization (specific experimental factory functions). Single boolean argument indicates if extra calculations
// should be performed for some no-background-subtraction limits (not necessary for likelihoods).
BE_FUNCTION(XENON100_2012_Init,  int, (const bool&), "C_DDCalc_xenon100_2012_init",  "XENON100_2012_Init")
BE_FUNCTION(XENON1T_2017_Init,   int, (const bool&), "C_DDCalc_xenon1t_2017_init",   "XENON1T_2017_Init")
BE_FUNCTION(LUX_2013_Init,       int, (const bool&), "C_DDCalc_lux_2013_init",       "LUX_2013_Init")
BE_FUNCTION(LUX_2016_Init,       int, (const bool&), "C_DDCalc_lux_2016_init",       "LUX_2016_Init")
BE_FUNCTION(PandaX_2016_Init,    int, (const bool&), "C_DDCalc_pandax_2016_init",    "PandaX_2016_Init")
BE_FUNCTION(LUX_2015_Init,       int, (const bool&), "C_DDCalc_lux_2015_init",       "LUX_2015_Init")
BE_FUNCTION(PICO_2L_Init,        int, (const bool&), "C_DDCalc_pico_2l_init",        "PICO_2L_Init")
BE_FUNCTION(PICO_60_F_Init,      int, (const bool&), "C_DDCalc_pico_60_f_init",      "PICO_60_F_Init")
BE_FUNCTION(PICO_60_I_Init,      int, (const bool&), "C_DDCalc_pico_60_i_init",      "PICO_60_I_Init")
BE_FUNCTION(PICO_60_2017_Init,   int, (const bool&), "C_DDCalc_pico_60_2017_init",   "PICO_60_2017_Init")
BE_FUNCTION(SuperCDMS_2014_Init, int, (const bool&), "C_DDCalc_supercdms_2014_init", "SuperCDMS_2014_Init")
BE_FUNCTION(SIMPLE_2014_Init,    int, (const bool&), "C_DDCalc_simple_2014_init",    "SIMPLE_2014_Init")
//BE_FUNCTION(DARWIN_Ar_Init,      int, (const bool&), "C_DDCalc_darwin_ar_init", "DARWIN_Ar_Init")
//BE_FUNCTION(DARWIN_Xe_Init,      int, (const bool&), "C_DDCalc_darwin_xe_init", "DARWIN_Xe_Init")

// Set halo parameters (Standard Halo Model):
//   rho [GeV/cm^3], vrot [km/s], v0 [km/s], vesc [km/s]
// This need only be called once at the beginning if the halo parameters will not be modified during a scan.  Default
// values are already set via DDCalc_InitHalo routine, so it need not be called at all if the default values are to be used.
BE_FUNCTION(DDCalc_SetSHM, void, (const int&, const double&, const double&, const double&, const double&), "C_DDCalc_ddcalc_setshm", "SetSHM")

// Set the WIMP mass and couplings/cross-sections. There are three versions, depending on how the couplings are specified:
//   * mfa:    mass, fp, fn, ap, an
//   * mG:     mass, Gp_SI, Gn_SI, Gp_SD, Gn_SD
//   * msigma: mass, sigmapSI, sigmanSI, sigmapSD, sigmanSD
//  Units: mass [GeV]; f, G [GeV^-2]; a [unitless]; sigma [pb]
// Here, f & a are the typical WIMP-nucleon couplings for spin-independent (SI) and spin-dependent (SD) interactions.
// The G's are the effective 4 fermion vertex couplings, related to f & a by a normalization factor.  The sigmas are WIMP-
// nucleon scattering cross-sections; a negative value can be used to indicated the corresponding coupling should be taken
// to be negative.
BE_FUNCTION(DDCalc_SetWIMP_mfa,    void, (const int&, const double&, const double&, const double&, const double&, const double&), "C_DDCalc_ddcalc_setwimp_mfa",    "SetWIMP_mfa")
BE_FUNCTION(DDCalc_SetWIMP_mG,     void, (const int&, const double&, const double&, const double&, const double&, const double&), "C_DDCalc_ddcalc_setwimp_mg",     "SetWIMP_mG")
BE_FUNCTION(DDCalc_SetWIMP_msigma, void, (const int&, const double&, const double&, const double&, const double&, const double&), "C_DDCalc_ddcalc_setwimp_msigma", "SetWIMP_msigma")

// Get the WIMP mass and couplings/cross-sections. Same signature and units as above for setters.  The only difference is
// that the WIMP-nucleon cross-sections are always positive (physical) values.
BE_FUNCTION(DDCalc_GetWIMP_mfa,    void, (const int&,double&,double&,double&,double&,double&), "C_DDCalc_ddcalc_getwimp_mfa",    "GetWIMP_mfa")
BE_FUNCTION(DDCalc_GetWIMP_mG,     void, (const int&,double&,double&,double&,double&,double&), "C_DDCalc_ddcalc_getwimp_mg",     "GetWIMP_mG")
BE_FUNCTION(DDCalc_GetWIMP_msigma, void, (const int&,double&,double&,double&,double&,double&), "C_DDCalc_ddcalc_getwimp_msigma", "GetWIMP_msigma")

// Specify the minimum recoil energy to be included in the rate calculations [keV].  Note the efficiency curves already account for
// detector and analysis thresholds regardless of this setting, so setting this to 0 keV (the default behavior when initialization is
// performed) does not imply that very low energy recoils actually contribute to the signal.
BE_FUNCTION(DDCalc_SetDetectorEmin,  void, (const int&, const double&), "C_DDCalc_ddcalc_setdetectoremin",  "DD_SetDetectorEmin")

// Calculation function; should be run once for each experiment and model prior to using event and likelihood routines below.
BE_FUNCTION(DDCalc_CalcRates,  void, (const int&, const int&, const int&), "C_DDRates_ddcalc_calcrates",  "DD_CalcRates")

// Observed and expected events, likelihoods and p values.
//   Events:        observed events
//   Background:    average background expectation
//   Signal:        average signal expectation
//   SignalSI:      average signal expectation (spin-independent only)
//   SignalSD:      average signal expectation (spin-dependent only)
//   LogLikelihood: log of the likelihood (not -2lnL)
//   LogPValue:     log of the p value
//   Factor x by which sigma -> x*sigma would yield given p-value (given as log(p))
BE_FUNCTION(DDCalc_Events,        int,    (const int&),                "C_DDRates_ddcalc_events",        "DD_Events")
BE_FUNCTION(DDCalc_Background,    double, (const int&),                "C_DDRates_ddcalc_background",    "DD_Background")
BE_FUNCTION(DDCalc_Signal,        double, (const int&),                "C_DDRates_ddcalc_signal",        "DD_Signal")
BE_FUNCTION(DDCalc_SignalSI,      double, (const int&),                "C_DDRates_ddcalc_signalsi",      "DD_SignalSI")
BE_FUNCTION(DDCalc_SignalSD,      double, (const int&),                "C_DDRates_ddcalc_signalsd",      "DD_SignalSD")
BE_FUNCTION(DDCalc_LogLikelihood, double, (const int&),                "C_DDStats_ddcalc_loglikelihood", "DD_LogLikelihood")
BE_FUNCTION(DDCalc_LogPValue,     double, (const int&),                "C_DDStats_ddcalc_logpvalue",     "DD_LogPValue")
BE_FUNCTION(DDCalc_ScaleToPValue, double, (const int&, const double&), "C_DDStats_ddcalc_scaletopvalue", "DD_SignalSD")

// Do memory cleanup (nowhere to actually use these in GAMBIT proper, but they could be useful in standalones that hammer DDCalc).
BE_FUNCTION(DDCalc_FreeWIMPs,     void, (), "C_DDUtils_ddcalc_freewimps",     "FreeWIMPs")
BE_FUNCTION(DDCalc_FreeHalos,     void, (), "C_DDUtils_ddcalc_freehalos",     "FreeHalos")
BE_FUNCTION(DDCalc_FreeDetectors, void, (), "C_DDUtils_ddcalc_freedetectors", "FreeDetectorss")
BE_FUNCTION(DDCalc_FreeAll,       void, (), "C_DDUtils_ddcalc_freeall",       "FreeAll")

// DM mass, couplings and fraction of cosmological DM that is accounted for by model
BE_INI_DEPENDENCY(mwimp, double)
BE_INI_DEPENDENCY(DD_couplings, DM_nucleon_couplings)
BE_INI_DEPENDENCY(RD_fraction, double)
BE_INI_DEPENDENCY(LocalHalo, LocalMaxwellianHalo)

// Convenience function for returning detector index given an analysis name.
BE_CONV_FUNCTION(DDCalc_Experiment, int, (const str&), "DD_Experiment")

// Convenience function for calling CalcRates with internally-initialised WIMP and halo objects.
BE_CONV_FUNCTION(DDCalc_CalcRates_simple,  void, (const int&), "DD_CalcRates")

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"

