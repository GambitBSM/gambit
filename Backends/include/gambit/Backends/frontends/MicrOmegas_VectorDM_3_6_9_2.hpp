//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas VectorDM backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Ankit Beniwal
/// \date Oct 2016, Jun 2017
///
///  *********************************************

#define BACKENDNAME MicrOmegas_VectorDM
#define BACKENDLANG CC
#define VERSION 3.6.9.2
#define SAFE_VERSION 3_6_9_2

LOAD_LIBRARY

BE_FUNCTION(assignVal, int, (char*,double),"assignVal","assignVal", (VectorDM))
BE_FUNCTION(vSigma, double, (double, double, int), "vSigma","vSigma", (VectorDM))
BE_FUNCTION(darkOmega, double, (double*, int, double), "darkOmega", "oh2", (VectorDM))
BE_FUNCTION(sortOddParticles, int, (char*), "sortOddParticles","mass_spectrum", (VectorDM))
BE_FUNCTION(cleanDecayTable, void, (), "cleanDecayTable", "cleanDecayTable", (VectorDM))
BE_FUNCTION(calcSpectrum, double, (int, double*, double*, double*, double*, double*, double*, int*), "calcSpectrum", "calcSpectrum", (VectorDM))
BE_FUNCTION(nucleonAmplitudes, int, (double(*)(double,double,double,double), double*, double*, double*, double*), "nucleonAmplitudes", "nucleonAmplitudes", (VectorDM))
BE_FUNCTION(FeScLoop, double, (double, double, double, double), "FeScLoop", "FeScLoop", (VectorDM))
BE_FUNCTION(calcScalarQuarkFF, void, (double, double, double, double), "calcScalarQuarkFF", "calcScalarQuarkFF", (VectorDM))

BE_FUNCTION(mInterp, int, (double,int,int,double*) , "mInterp", "mInterp")
BE_FUNCTION(zInterp, double, (double,double*) , "zInterp", "zInterp")
BE_FUNCTION(readSpectra, int, (), "readSpectra", "readSpectra")

BE_VARIABLE(mocommon_, MicrOmegas::MOcommonSTR, "mocommon_", "MOcommon", (VectorDM))
BE_VARIABLE(vSigmaCh, MicrOmegas::aChannel*, "vSigmaCh", "vSigmaCh", (VectorDM))
BE_VARIABLE(ForceUG, int, "ForceUG", "ForceUG", (VectorDM))
BE_VARIABLE(VZdecay, int, "VZdecay", "VZdecay", (VectorDM))
BE_VARIABLE(VWdecay, int, "VWdecay", "VWdecay", (VectorDM))

BE_CONV_FUNCTION(dNdE, double, (double,double,int,int), "dNdE")

BE_INI_DEPENDENCY(VectorDM_spectrum, Spectrum)
BE_INI_DEPENDENCY(decay_rates, DecayTable)

#include "gambit/Backends/backend_undefs.hpp"

