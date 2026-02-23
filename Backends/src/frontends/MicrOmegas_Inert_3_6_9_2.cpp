//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas Inert
///  3.6.9.2 backend.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:33PM on February 18, 2026
///                                                
///  ********************************************* 

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/MicrOmegas_Inert_3_6_9_2.hpp"
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
  
  const Spectrum& spec = *Dep::Inert_spectrum;
  const SMInputs& sminputs = spec.get_SMInputs();
  
  // YAML options for 3-body final states
  int VZdecayOpt, VWdecayOpt; // 0=no 3 body final states
                              // 1=3 body final states in annihlations
                              // 2=3 body final states in co-annihilations
  VZdecayOpt = runOptions->getValueOrDef<int>(1, "VZdecay");
  VWdecayOpt = runOptions->getValueOrDef<int>(1, "VWdecay");
  *VZdecay = VZdecayOpt;
  *VWdecay = VWdecayOpt;
  
  logger() << LogTags::debug << "Initializing MicrOmegas Inert with ";
  logger() << "VWdecay: " << VWdecay << " VZdecay: " << VZdecay << EOM;
  
  // Uncomment below to force MicrOmegas to do calculations in unitary gauge
  *ForceUG=1;
  
  // BSM parameters
  Assign_Value("v", spec.get(Par::dimensionless, "v"));
  for(int i=1; i<2; i++)
  {
    for(int j=1; j<2; j++)
    {
      std::string paramname = "ZP" + std::to_string(i) + std::to_string(j);
      Assign_Value(paramname, spec.get(Par::Pole_Mixing, "ZP", i, j));
    }
  }
  for(int i=1; i<3; i++)
  {
    for(int j=1; j<3; j++)
    {
      std::string paramname = "ZEL" + std::to_string(i) + std::to_string(j);
      Assign_Value(paramname, spec.get(Par::Pole_Mixing, "ZEL", i, j));
    }
  }
  for(int i=1; i<3; i++)
  {
    for(int j=1; j<3; j++)
    {
      std::string paramname = "ZER" + std::to_string(i) + std::to_string(j);
      Assign_Value(paramname, spec.get(Par::Pole_Mixing, "ZER", i, j));
    }
  }
  for(int i=1; i<3; i++)
  {
    for(int j=1; j<3; j++)
    {
      std::string paramname = "ZDL" + std::to_string(i) + std::to_string(j);
      Assign_Value(paramname, spec.get(Par::Pole_Mixing, "ZDL", i, j));
    }
  }
  for(int i=1; i<3; i++)
  {
    for(int j=1; j<3; j++)
    {
      std::string paramname = "ZDR" + std::to_string(i) + std::to_string(j);
      Assign_Value(paramname, spec.get(Par::Pole_Mixing, "ZDR", i, j));
    }
  }
  for(int i=1; i<3; i++)
  {
    for(int j=1; j<3; j++)
    {
      std::string paramname = "ZUL" + std::to_string(i) + std::to_string(j);
      Assign_Value(paramname, spec.get(Par::Pole_Mixing, "ZUL", i, j));
    }
  }
  for(int i=1; i<3; i++)
  {
    for(int j=1; j<3; j++)
    {
      std::string paramname = "ZUR" + std::to_string(i) + std::to_string(j);
      Assign_Value(paramname, spec.get(Par::Pole_Mixing, "ZUR", i, j));
    }
  }
  Assign_Value("Lam5", spec.get(Par::dimensionless, "Lam5"));
  Assign_Value("Lam1", spec.get(Par::dimensionless, "Lam1"));
  Assign_Value("Lam4", spec.get(Par::dimensionless, "Lam4"));
  Assign_Value("Lam3", spec.get(Par::dimensionless, "Lam3"));
  Assign_Value("Lam2", spec.get(Par::dimensionless, "Lam2"));
  Assign_Value("mHd2", spec.get(Par::dimensionless, "mHd2"));
  Assign_Value("mHu2", spec.get(Par::dimensionless, "mHu2"));
  // Masses
  Assign_Value("Mh", spec.get(Par::Pole_Mass, "h0_1"));
  Assign_Value("MH0", spec.get(Par::Pole_Mass, "h0_2"));
  Assign_Value("MA0", spec.get(Par::Pole_Mass, "A0"));
  Assign_Value("MHp2", spec.get(Par::Pole_Mass, "H+"));
  
  // SMInputs
  Assign_Value("MZ", sminputs.mZ);
  Assign_Value("Md1", sminputs.mD);
  Assign_Value("Md2", sminputs.mS);
  Assign_Value("Md3", sminputs.mBmB);
  Assign_Value("Mu1", sminputs.mU);
  Assign_Value("Mu2", sminputs.mCmC);
  Assign_Value("Mu3", sminputs.mT);
  Assign_Value("Me1", sminputs.mE);
  Assign_Value("Me2", sminputs.mMu);
  Assign_Value("Me3", sminputs.mTau);
  
  // SMInputs constantsAssign_Value("Gf", sminputs.GF); // Fermi constant
  Assign_Value("aS", sminputs.alphaS); // alphaS 
  Assign_Value("alfSMZ", sminputs.alphaS); // alphaS at mZ - for internal running
  Assign_Value("aEWinv", sminputs.alphainv); // Fine structure constant
  
  
  // Set particle widths in micrOmegas
  const DecayTable* tbl = &(*Dep::decay_rates);
  double width = 0.0;
  bool present = true;
  
  try { width = tbl->at("h0_1").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("!Wh", width);
  present = true;
  
  try { width = tbl->at("A0").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("!WA0", width);
  present = true;
  
  try { width = tbl->at("h0_2").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("!WH0", width);
  present = true;
  
  try { width = tbl->at("H+").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("!WHp2", width);
  present = true;
  
  try { width = tbl->at("Z0").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("WZ", width);
  present = true;
  
  try { width = tbl->at("W+").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("WWp", width);
  present = true;
  
  try { width = tbl->at("d_1").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("Wd1", width);
  present = true;
  
  try { width = tbl->at("d_2").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("Wd2", width);
  present = true;
  
  try { width = tbl->at("d_3").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("Wd3", width);
  present = true;
  
  try { width = tbl->at("u_1").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("Wu1", width);
  present = true;
  
  try { width = tbl->at("u_2").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("Wu2", width);
  present = true;
  
  try { width = tbl->at("u_3").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("Wu3", width);
  present = true;
  
  try { width = tbl->at("e-_1").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("We1", width);
  present = true;
  
  try { width = tbl->at("e-_2").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("We2", width);
  present = true;
  
  try { width = tbl->at("e-_3").width_in_GeV; }
  catch(std::exception& e) { present = false; }
  if (present) Assign_Value("We3", width);
  present = true;
  
  // Initialise micrOMEGAs mass spectrum
  error = sortOddParticles(byVal(cdmName));
  if (error != 0) backend_error().raise(LOCAL_INFO, "MicrOmegas function "
          "sortOddParticles returned error code: " + std::to_string(error));
  
}
END_BE_INI_FUNCTION
