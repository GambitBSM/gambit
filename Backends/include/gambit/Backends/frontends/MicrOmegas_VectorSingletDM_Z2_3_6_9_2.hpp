//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas VectorSingletDM_Z2 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Ankit Beniwal
/// \date Oct 2016, Jun 2017
///
///  *********************************************

#define BACKENDNAME MicrOmegas_VectorSingletDM_Z2
#define BACKENDLANG CC
#define VERSION 3.6.9.2
#define SAFE_VERSION 3_6_9_2

LOAD_LIBRARY

BE_ALLOW_MODELS(VectorSingletDM_Z2)

BE_FUNCTION(assignVal, int, (char*,double),"assignVal","assignVal")
BE_FUNCTION(vSigma, double, (double, double, int), "vSigma","vSigma")
BE_FUNCTION(darkOmega, double, (double*, int, double), "darkOmega", "oh2")
BE_FUNCTION(sortOddParticles, int, (char*), "sortOddParticles","mass_spectrum")
BE_FUNCTION(cleanDecayTable, void, (), "cleanDecayTable", "cleanDecayTable")
BE_FUNCTION(nucleonAmplitudes, int, (double(*)(double,double,double,double), double*, double*, double*, double*), "nucleonAmplitudes", "nucleonAmplitudes" )
BE_FUNCTION(FeScLoop, double, (double, double, double, double), "FeScLoop", "FeScLoop")
BE_FUNCTION(calcScalarQuarkFF, void, (double, double, double, double), "calcScalarQuarkFF", "calcScalarQuarkFF")
BE_FUNCTION(calcSpectrum, double, (int, double*, double*, double*, double*, double*, double*, int*), "calcSpectrum", "calcSpectrum")
BE_FUNCTION(printChannels, double, (double, double, double, int, FILE*), "printChannels", "momegas_print_channels")
BE_FUNCTION(oneChannel, double, (double,double,char*,char*,char*,char*), "oneChannel", "get_oneChannel")
BE_FUNCTION(mInterp, int, (double,int,int,double*) , "mInterp", "mInterp")
BE_FUNCTION(zInterp, double, (double,double*) , "zInterp", "zInterp")
BE_FUNCTION(readSpectra, int, (), "readSpectra", "readSpectra")

BE_VARIABLE(mocommon_, MicrOmegas::MOcommonSTR, "mocommon_", "MOcommon")
BE_VARIABLE(vSigmaCh, MicrOmegas::aChannel*, "vSigmaCh", "vSigmaCh")
BE_VARIABLE(ForceUG, int, "ForceUG", "ForceUG")
BE_VARIABLE(VZdecay, int, "VZdecay", "VZdecay")
BE_VARIABLE(VWdecay, int, "VWdecay", "VWdecay")

BE_CONV_FUNCTION(dNdE, double, (double,double,int,int), "dNdE")

BE_INI_DEPENDENCY(VectorSingletDM_Z2_spectrum, Spectrum)
BE_INI_DEPENDENCY(decay_rates, DecayTable)

#include "gambit/Backends/backend_undefs.hpp"

