//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas DMsimpVectorMedVectorDM
///  3.6.9.2 backend.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:49PM on February 07, 2023
///                                                
///  ********************************************* 

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/MicrOmegas_DMsimpVectorMedVectorDM_3_6_9_2.hpp"
#include <unistd.h>

// Convenience functions (definitions)
BE_NAMESPACE
{
  double dNdE(double Ecm, double E, int inP, int outN)
  {
    // outN 0-5: gamma, e+, p-, nu_e, nu_mu, nu_tau
    // inP:  0 - 6: glu, d, u, s, c, b, t
    //       7 - 9: e, m, l
    //       10 - 15: Z, ZT, ZL, W, WT, WL
    double tab[250];  // NZ = 250
    // readSpectra() moved to initialization function.
    // Must be inside critical block if used here!
    // readSpectra();
    mInterp(Ecm/2, inP, outN, tab);
    return zInterp(log(E/Ecm*2), tab);
  }

  /// Assigns gambit value to parameter, with error-checking.
  void Assign_Value(std::string parameter, double value)
  {
    int error;
    char *param = &parameter[0];
    error = assignVal(param, value);
    if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set " + std::string(parameter) +
        " in MicrOmegas. MicrOmegas error code: " + std::to_string(error)+ ". Please check your model files.\n");
  }

}
END_BE_NAMESPACE

// Initialisation function (definition)
BE_INI_FUNCTION
{
  int error;
  char cdmName[10];

  const Spectrum& spec = *Dep::DMsimpVectorMedVectorDM_spectrum;
  const SMInputs& sminputs = spec.get_SMInputs();

  // YAML options for 3-body final states
  int VZdecayOpt, VWdecayOpt; // 0=no 3 body final states
                              // 1=3 body final states in annihlations
                              // 2=3 body final states in co-annihilations
  VZdecayOpt = runOptions->getValueOrDef<int>(1, "VZdecay");
  VWdecayOpt = runOptions->getValueOrDef<int>(1, "VWdecay");
  *VZdecay = VZdecayOpt;
  *VWdecay = VWdecayOpt;

  logger() << LogTags::debug << "Initializing MicrOmegas DMsimpVectorMedVectorDM with ";
  logger() << "VWdecay: " << VWdecay << " VZdecay: " << VZdecay << EOM;

  // Uncomment below to force MicrOmegas to do calculations in unitary gauge
  *ForceUG=1;

  // BSM parameters
  Assign_Value("gVXv", spec.get(Par::dimensionless, "gVXv"));
  Assign_Value("gVq", spec.get(Par::dimensionless, "gVq"));
  // Masses
  Assign_Value("MH", spec.get(Par::Pole_Mass, "h0_1"));
  Assign_Value("mXv", spec.get(Par::Pole_Mass, "~Xv"));
  Assign_Value("MY1", spec.get(Par::Pole_Mass, "Y1"));

  // SMInputs
  Assign_Value("MZ", sminputs.mZ);
  Assign_Value("Me", sminputs.mE);
  Assign_Value("MMU", sminputs.mMu);
  Assign_Value("MTA", sminputs.mTau);
  Assign_Value("MU", sminputs.mU);
  Assign_Value("MC", sminputs.mCmC);
  Assign_Value("MT", sminputs.mT);
  Assign_Value("MD", sminputs.mD);
  Assign_Value("MS", sminputs.mS);
  Assign_Value("MB", sminputs.mBmB);

  // SMInputs constantsAssign_Value("Gf", sminputs.GF); // Fermi constant
  Assign_Value("aS", sminputs.alphaS); // alphaS 
  Assign_Value("aEWM1", sminputs.alphainv); // Fine structure constant


  // Set particle widths in micrOmegas
  const DecayTable* tbl = &(*Dep::decay_rates);
  double width = 0.0;
  bool present = true;

  try { width = tbl->at("Z0").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("WZ", width);
  present = true;

  try { width = tbl->at("W+").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("WW", width);
  present = true;

  try { width = tbl->at("u_3").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("WT", width);
  present = true;

  try { width = tbl->at("h0_1").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("WH", width);
  present = true;

  try { width = tbl->at("~Xv").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("WXv", width);
  present = true;

  try { width = tbl->at("Y1").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("WY1", width);
  present = true;

  // Initialise micrOMEGAs mass spectrum
  error = sortOddParticles(byVal(cdmName));
  if (error != 0) backend_error().raise(LOCAL_INFO, "MicrOmegas function "
          "sortOddParticles returned error code: " + std::to_string(error));

}
END_BE_INI_FUNCTION
