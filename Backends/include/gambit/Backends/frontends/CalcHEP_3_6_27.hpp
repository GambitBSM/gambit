//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for CalcHEP Backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2017 May, Oct
///        2018 Sep
///
///  *****************************************

#define BACKENDNAME CalcHEP
#define BACKENDLANG CC
#define VERSION 3.6.27
#define SAFE_VERSION 3_6_27
#define REFERENCE Pukhov:2004ca,Belyaev:2012qa

LOAD_LIBRARY

BE_ALLOW_MODELS(ScalarSingletDM_Z2)
BE_ALLOW_MODELS(DMEFT)
BE_ALLOW_MODELS(DMsimpVectorMedScalarDM)
BE_ALLOW_MODELS(DMsimpVectorMedMajoranaDM)
BE_ALLOW_MODELS(DMsimpVectorMedDiracDM)
BE_ALLOW_MODELS(DMsimpVectorMedVectorDM)

BE_FUNCTION(setModel, int, (char*, int), "setModel", "setModel")
BE_FUNCTION(calcMainFunc, int, (), "calcMainFunc", "calcMainFunc")
BE_FUNCTION(getMEcode, numout*, (int ,int, char*, char*, char*, char*), "getMEcode" , "getMEcode")
BE_FUNCTION(passParameters, int, (numout*), "passParameters", "passParameters")
BE_FUNCTION(assignVal, int, (char*, double), "assignVal", "assignVal")
BE_FUNCTION(pMass, double, (char*), "pMass", "pMass")
BE_FUNCTION(pdg2mass, char*, (int), "pdg2mass", "pdg2mass")
BE_FUNCTION(pdg2width, char*, (int), "pdg2width", "pdg2width")

BE_VARIABLE(varNames, char*, "varNames", "varNames")
BE_VARIABLE(VZdecay, int, "VZdecay", "VZdecay")
BE_VARIABLE(VWdecay, int, "VWdecay", "VWdecay")

BE_CONV_FUNCTION(generate_decay_code, numout*, (str, str, std::vector<str>), "generate_decay_code")
BE_CONV_FUNCTION(generate_xsec_code, numout*, (str, std::vector<str>, std::vector<str>), "generate_xsec_code")
BE_CONV_FUNCTION(CH_Decay_Width, double, (str&, str&, std::vector<str>&), "CH_Decay_Width")
BE_CONV_FUNCTION(CH_Sigma_V, double, (str&, std::vector<str>&, std::vector<str>&, double&, const DecayTable&), "CH_Sigma_V")
BE_CONV_FUNCTION(Assign_All_Values, void, (const Spectrum&, std::vector<SpectrumParameter>), "Assign_All_Values")
BE_CONV_FUNCTION(Assign_Widths, void, (const DecayTable&), "Assign_Widths")
BE_CONV_FUNCTION(Assign_Value, void, (char*, double), "Assign_Value")

BE_INI_CONDITIONAL_DEPENDENCY(ScalarSingletDM_Z2_spectrum, Spectrum, ScalarSingletDM_Z2)

BE_INI_CONDITIONAL_DEPENDENCY(DMEFT_spectrum, Spectrum, DMEFT)
BE_INI_CONDITIONAL_DEPENDENCY(DMsimpVectorMedDiracDM_spectrum, Spectrum, DMsimpVectorMedDiracDM)
BE_INI_CONDITIONAL_DEPENDENCY(DMsimpVectorMedMajoranaDM_spectrum, Spectrum, DMsimpVectorMedMajoranaDM)
BE_INI_CONDITIONAL_DEPENDENCY(DMsimpVectorMedScalarDM_spectrum, Spectrum, DMsimpVectorMedScalarDM)
BE_INI_CONDITIONAL_DEPENDENCY(DMsimpVectorMedVectorDM_spectrum, Spectrum, DMsimpVectorMedVectorDM)
// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
