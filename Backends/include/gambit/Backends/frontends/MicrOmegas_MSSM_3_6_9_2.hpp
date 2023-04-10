//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas MSSM backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Jonathan Cornell
/// \date Oct 2013
///
/// \author Sebastian Wild
/// \date Aug 2016
///
///  *****************************************

#define BACKENDNAME MicrOmegas_MSSM
#define BACKENDLANG CC
#define VERSION 3.6.9.2
#define SAFE_VERSION 3_6_9_2
#define REFERENCE Belanger:2001fz,Belanger:2004yn,Belanger:2006is,Belanger:2008sj,Belanger:2010gh,Belanger:2013oya,Belanger:2014vza

LOAD_LIBRARY

BE_ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, MSSM63atMGUT_mG, MSSM63atQ_mG,
	            Halo_gNFW, Halo_gNFW_rho0, Halo_gNFW_rhos, Halo_Einasto, Halo_Einasto_rho0, Halo_Einasto_rhos)
// The presence of the various halo models is just a workaround to allow initializing MO without MSSM model

BE_FUNCTION(oneChannel, double, (double,double,char*,char*,char*,char*), "oneChannel", "get_oneChannel", (MSSM63atQ))

BE_FUNCTION(assignVal, int, (char*,double),"assignVal","assignVal", (MSSM63atQ))
BE_FUNCTION(vSigma, double, (double, double, int), "vSigma","vSigma", (MSSM63atQ))
BE_FUNCTION(darkOmega, double, (double*, int, double), "darkOmega", "oh2", (MSSM63atQ))
BE_FUNCTION(suspectSUGRA, int, (double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double), "suspectSUGRA", "suspectSUGRA", (MSSM63atQ))
BE_FUNCTION(lesHinput, int, (char*), "lesHinput", "lesHinput", (MSSM63atQ))
BE_FUNCTION(sortOddParticles, int, (char*), "sortOddParticles","mass_spectrum", (MSSM63atQ))
BE_FUNCTION(cleanDecayTable, void, (), "cleanDecayTable", "cleanDecayTable", (MSSM63atQ))
BE_FUNCTION(nucleonAmplitudes, int, (double(*)(double,double,double,double), double*, double*, double*, double*), "nucleonAmplitudes", "nucleonAmplitudes", (MSSM63atQ))
BE_FUNCTION(FeScLoop, double, (double, double, double, double), "FeScLoop", "FeScLoop", (MSSM63atQ))
BE_FUNCTION(calcScalarQuarkFF, void, (double, double, double, double), "calcScalarQuarkFF", "calcScalarQuarkFF", (MSSM63atQ))
BE_FUNCTION(calcSpectrum, double, (int, double*, double*, double*, double*, double*, double*, int*), "calcSpectrum", "calcSpectrum")

BE_FUNCTION(mInterp, int, (double,int,int,double*) , "mInterp", "mInterp")
BE_FUNCTION(zInterp, double, (double,double*) , "zInterp", "zInterp")
BE_FUNCTION(readSpectra, int, (), "readSpectra", "readSpectra")

BE_VARIABLE(mocommon_, MicrOmegas::MOcommonSTR, "mocommon_", "MOcommon", (MSSM63atQ))
BE_VARIABLE(ForceUG, int, "ForceUG", "ForceUG", (MSSM63atQ))
BE_VARIABLE(VZdecay, int, "VZdecay", "VZdecay", (MSSM63atQ))
BE_VARIABLE(VWdecay, int, "VWdecay", "VWdecay", (MSSM63atQ))

BE_CONV_FUNCTION(dNdE, double, (double,double,int,int), "dNdE")

BE_INI_CONDITIONAL_DEPENDENCY(MSSM_spectrum, Spectrum, MSSM63atQ)
BE_INI_CONDITIONAL_DEPENDENCY(SLHA_pseudonyms, mass_es_pseudonyms, MSSM63atQ)
BE_INI_DEPENDENCY(decay_rates, DecayTable)

#include "gambit/Backends/backend_undefs.hpp"
