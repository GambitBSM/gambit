//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas MajoranaDM backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Ankit Beniwal
/// \date Oct 2016, Jun 2017
///
///  *********************************************

#define BACKENDNAME MicrOmegas_MajoranaDM
#define BACKENDLANG CC
#define VERSION 3.6.9.2
#define SAFE_VERSION 3_6_9_2

LOAD_LIBRARY

BE_FUNCTION(assignVal, int, (char*,double),"assignVal","assignVal", (MajoranaDM))
BE_FUNCTION(vSigma, double, (double, double, int), "vSigma","vSigma", (MajoranaDM))
BE_FUNCTION(darkOmega, double, (double*, int, double), "darkOmega", "oh2", (MajoranaDM))
BE_FUNCTION(sortOddParticles, int, (char*), "sortOddParticles","mass_spectrum", (MajoranaDM))
BE_FUNCTION(cleanDecayTable, void, (), "cleanDecayTable", "cleanDecayTable", (MajoranaDM))
BE_FUNCTION(calcSpectrum, double, (int, double*, double*, double*, double*, double*, double*, int*), "calcSpectrum", "calcSpectrum", (MajoranaDM))
BE_FUNCTION(nucleonAmplitudes, int, (double(*)(double,double,double,double), double*, double*, double*, double*), "nucleonAmplitudes", "nucleonAmplitudes", (MajoranaDM))
BE_FUNCTION(FeScLoop, double, (double, double, double, double), "FeScLoop", "FeScLoop", (MajoranaDM))
BE_FUNCTION(calcScalarQuarkFF, void, (double, double, double, double), "calcScalarQuarkFF", "calcScalarQuarkFF", (MajoranaDM))

BE_FUNCTION(mInterp, int, (double,int,int,double*) , "mInterp", "mInterp")
BE_FUNCTION(zInterp, double, (double,double*) , "zInterp", "zInterp")
BE_FUNCTION(readSpectra, int, (), "readSpectra", "readSpectra")

BE_VARIABLE(mocommon_, MicrOmegas::MOcommonSTR, "mocommon_", "MOcommon", (MajoranaDM))
BE_VARIABLE(vSigmaCh, MicrOmegas::aChannel*, "vSigmaCh", "vSigmaCh", (MajoranaDM))
BE_VARIABLE(ForceUG, int, "ForceUG", "ForceUG", (MajoranaDM))
BE_VARIABLE(VZdecay, int, "VZdecay", "VZdecay", (MajoranaDM))
BE_VARIABLE(VWdecay, int, "VWdecay", "VWdecay", (MajoranaDM))

BE_CONV_FUNCTION(dNdE, double, (double,double,int,int), "dNdE")

BE_INI_DEPENDENCY(MajoranaDM_spectrum, Spectrum)
BE_INI_DEPENDENCY(decay_rates, DecayTable)

#include "gambit/Backends/backend_undefs.hpp"

