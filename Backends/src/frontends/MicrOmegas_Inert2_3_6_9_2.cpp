//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for MicrOmegas Inert2
///  3.6.9.2 backend.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:45PM on September 21, 2022
///                                                
///  ********************************************* 

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/MicrOmegas_Inert2_3_6_9_2.hpp"
#include <unistd.h>
#include <fstream>

constexpr bool use_ithdm_models = true;

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
    // std::cout << "Assign micrOMEGAs param: " << parameter << "  " << value << std::endl;
    int error = assignVal(&parameter[0], value);
    if (error != 0) backend_error().raise(LOCAL_INFO, "Unable to set " + std::string(parameter) +
        " in MicrOmegas. MicrOmegas error code: " + std::to_string(error)+ ". Please check your model files.\n");
  }
  
}
END_BE_NAMESPACE

  bool match(std::vector<int> pp1, std::vector<int> pp2)
  {
    enum {u1,u2,u3,d1,d2,d3,e1,e2,e3,v1,v2,v3,u1c,u2c,u3c,d1c,d2c,d3c,e1c,e2c,e3c,v1c,v2c,v3c,a,z,wp,wm,g,h1,h2,ha,hp,hm,  f,v,h};

    if (pp1.size() != pp2.size()) return false;
    for (size_t i=0; i<pp1.size(); ++i)
    {
      if (pp1[i] == pp2[i]) continue;
      if (pp1[i] == f && pp2[i] >= u1 && pp2[i] <= v3c) continue;
      if (pp1[i] == v && pp2[i] >= a && pp2[i] <= g) continue;
      if (pp1[i] == h && pp2[i] >= h1 && pp2[i] <= hm) continue;
      return false;
    }
    return true;
  }

// Initialisation function (definition)
BE_INI_FUNCTION
{
  using std::to_string;
  int error = 0;
  char cdmName[10] { 0 }; // TODO: what is it?

  const Spectrum& spec = *Dep::Inert2_spectrum;
  const SMInputs& sminputs = spec.get_SMInputs();
  const DecayTable* tbl = &(*Dep::decay_rates);
  str additional_scalar_name = *Dep::additional_scalar;
  str SM_like_scalar_name = *Dep::SM_like_scalar;
  const coupling_table& couplings = *Dep::coupling_table_THDM;
  // bool swapped_mass_hierarchy = (spec.get(Par::dimensionless, "cosba") == 1);
  
  // YAML options for 3-body final states
  int VZdecayOpt, VWdecayOpt; // 0=no 3 body final states
                              // 1=3 body final states in annihlations
                              // 2=3 body final states in co-annihilations
  VZdecayOpt = runOptions->getValueOrDef<int>(1, "VZdecay");
  VWdecayOpt = runOptions->getValueOrDef<int>(1, "VWdecay");
  *VZdecay = VZdecayOpt;
  *VWdecay = VWdecayOpt;

  // Uncomment below to force MicrOmegas to do calculations in unitary gauge
  *ForceUG=1;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!

  auto get_coupling = [&](const coupling_table& t, const std::vector<int> c)
  {
    for (auto& i : t)
    {
      if (i.first == c) return i;
    }
    throw "invalid";
  };

  enum {u1,u2,u3,d1,d2,d3,e1,e2,e3,v1,v2,v3,u1c,u2c,u3c,d1c,d2c,d3c,e1c,e2c,e3c,v1c,v2c,v3c,a,z,wp,wm,g,hh,hx,ha,hp,hm,  f,v,h};

  if (use_ithdm_models)
  {
    Assign_Value("MH", spec.get(Par::Pole_Mass, "hh"));
    Assign_Value("Mh1", spec.get(Par::Pole_Mass, "hx"));
    Assign_Value("Mh2", spec.get(Par::Pole_Mass, "A0"));
    Assign_Value("Mhc", spec.get(Par::Pole_Mass, "H-"));
    Assign_Value("ld345", spec.get(Par::dimensionless,"lambda3")+spec.get(Par::dimensionless,"lambda4")+spec.get(Par::dimensionless,"lambda5"));
    Assign_Value("ld", 0.5*spec.get(Par::dimensionless, "lambda2")); // NB: lam1,2 (theirs) = 0.5 lam1,2 (ours)


    coupling CGGH = get_coupling(couplings,{g,g,hh});
    coupling CAAH = get_coupling(couplings,{a,a,hh});
    Assign_Value("CGGH", CGGH.second.first.imag());
    Assign_Value("CAAH", CAAH.second.first.imag());

    // Initialise micrOMEGAs mass spectrum
    error = sortOddParticles(byVal(cdmName));
    if (error != 0) backend_error().raise(LOCAL_INFO, "MicrOmegas function "
            "sortOddParticles returned error code: " + std::to_string(error));

    return;

  }
  
  // masses
  Assign_Value("Mu1", sminputs.mU);
  Assign_Value("Mu2", sminputs.mCmC);
  Assign_Value("Mu3", sminputs.mT);
  Assign_Value("Md1", sminputs.mD);
  Assign_Value("Md2", sminputs.mS);
  Assign_Value("Md3", sminputs.mBmB);
  Assign_Value("Me1", sminputs.mE);
  Assign_Value("Me2", sminputs.mMu);
  Assign_Value("Me3", sminputs.mTau);
  Assign_Value("Mv1", 0);
  Assign_Value("Mv2", 0);
  Assign_Value("Mv3", 0);
  Assign_Value("Ma", 0);
  Assign_Value("Mz", sminputs.mZ);
  Assign_Value("Mwp", spec.get(Par::Pole_Mass, "W+"));
  Assign_Value("Mg", 0);
  Assign_Value("Mhh", spec.get(Par::Pole_Mass, SM_like_scalar_name));
  Assign_Value("Mhx", spec.get(Par::Pole_Mass, additional_scalar_name));
  Assign_Value("Mha", spec.get(Par::Pole_Mass, "A0"));
  Assign_Value("Mhp", spec.get(Par::Pole_Mass, "H-"));

  // widths
  Assign_Value("Wu1", 0);
  Assign_Value("Wu2", 6.6e-12);
  Assign_Value("Wu3", 1.51);
  Assign_Value("Wd1", 0);
  Assign_Value("Wd2", 6.6e-16);
  Assign_Value("Wd3", 5.5e-13);
  Assign_Value("We1", 0);
  Assign_Value("We2", 2.9949e-19);
  Assign_Value("We3", 2.266e-12);
  Assign_Value("Wv1", 0);
  Assign_Value("Wv2", 0);
  Assign_Value("Wv3", 0);
  Assign_Value("Wa", 0);
  Assign_Value("Wz", 2.4952);
  Assign_Value("Wwp", 2.085);
  Assign_Value("Wg", 0);

  double Whh = tbl->at(SM_like_scalar_name).width_in_GeV;
  double Whx = tbl->at(additional_scalar_name).width_in_GeV;
  double Wha = tbl->at("A0").width_in_GeV;
  double Whp = tbl->at("H+").width_in_GeV;

  // fix issue where 2HDMC doesn't give zero width for DM cnadidate
  if (Whh < 1e-15) Whh = 0;
  if (Whx < 1e-15) Whx = 0;
  if (Wha < 1e-15) Wha = 0;
  if (Whp < 1e-15) Whp = 0;

  Assign_Value("Whh", Whh);
  Assign_Value("Whx", Whx);
  Assign_Value("Wha", Wha);
  Assign_Value("Whp", Whp);

  // couplings


  for (size_t i=0; i<couplings.size(); ++i)
  {
    // skip ggg and gggg couplings
    if (match(couplings[i].first,{g,g,g}) || match(couplings[i].first,{g,g,g,g}))
      continue;

    // i*
    Assign_Value("C"+to_string(i)+"RS", -couplings[i].second.first.imag());
    Assign_Value("C"+to_string(i)+"IS", couplings[i].second.first.real());
    Assign_Value("C"+to_string(i)+"RP", -couplings[i].second.second.imag());
    Assign_Value("C"+to_string(i)+"IP", couplings[i].second.second.real());
  }

  // Initialise micrOMEGAs mass spectrum
  error = sortOddParticles(byVal(cdmName));
  if (error != 0) backend_error().raise(LOCAL_INFO, "MicrOmegas function "
          "sortOddParticles returned error code: " + std::to_string(error));

  const bool dump_datapar = false;

  if (dump_datapar)
  {
    // generate data.par
    str path = "~/Desktop/micromegas_5.3.41_IDM_my/IDMMY";
    str name = "data.par";

    std::ofstream datapar(path + "/" + name);
    datapar << "# file to improve default parameters\n";
    datapar << "Mu1 " << sminputs.mU << std::endl;
    datapar << "Mu2 " << sminputs.mCmC << std::endl;
    datapar << "Mu3 " << sminputs.mT << std::endl;
    datapar << "Md1 " << sminputs.mD << std::endl;
    datapar << "Md2 " << sminputs.mS << std::endl;
    datapar << "Md3 " << sminputs.mBmB << std::endl;
    datapar << "Me1 " << sminputs.mE << std::endl;
    datapar << "Me2 " << sminputs.mMu << std::endl;
    datapar << "Me3 " << sminputs.mTau << std::endl;
    datapar << "Mv1 " << 0 << std::endl;
    datapar << "Mv2 " << 0 << std::endl;
    datapar << "Mv3 " << 0 << std::endl;
    datapar << "Ma " << 0 << std::endl;
    datapar << "Mz " << sminputs.mZ << std::endl;
    datapar << "Mwp " << spec.get(Par::Pole_Mass, "W+") << std::endl;
    datapar << "Mg " << 0 << std::endl;
    datapar << "Mhh " << spec.get(Par::Pole_Mass, SM_like_scalar_name) << std::endl;
    datapar << "Mhx " << spec.get(Par::Pole_Mass, additional_scalar_name) << std::endl;
    datapar << "Mha " << spec.get(Par::Pole_Mass, "A0") << std::endl;
    datapar << "Mhp " << spec.get(Par::Pole_Mass, "H-") << std::endl;
    datapar << "Wu1 " << 0 << std::endl;
    datapar << "Wu2 " << 6.6e-12 << std::endl;
    datapar << "Wu3 " << 1.51 << std::endl;
    datapar << "Wd1 " << 0 << std::endl;
    datapar << "Wd2 " << 6.6e-16 << std::endl;
    datapar << "Wd3 " << 5.5e-13 << std::endl;
    datapar << "We1 " << 0 << std::endl;
    datapar << "We2 " << 2.9949e-19 << std::endl;
    datapar << "We3 " << 2.266e-12 << std::endl;
    datapar << "Wv1 " << 0 << std::endl;
    datapar << "Wv2 " << 0 << std::endl;
    datapar << "Wv3 " << 0 << std::endl;
    datapar << "Wa " << 0 << std::endl;
    datapar << "Wz " << 2.4952 << std::endl;
    datapar << "Wwp " << 2.085 << std::endl;
    datapar << "Wg " << 0 << std::endl;
    datapar << "Whh " << Whh << std::endl;
    datapar << "Whx " << Whx << std::endl;
    datapar << "Wha " << Wha << std::endl;
    datapar << "Whp " << Whp << std::endl;

    for (size_t i=0; i<couplings.size(); ++i)
    {
      // skip ggg and gggg couplings
      if (match(couplings[i].first,{g,g,g}) || match(couplings[i].first,{g,g,g,g}))
        continue;

      // i*
      datapar << "C"+to_string(i)+"RS " << -couplings[i].second.first.imag() << std::endl;
      datapar << "C"+to_string(i)+"IS " << couplings[i].second.first.real() << std::endl;
      datapar << "C"+to_string(i)+"RP " << -couplings[i].second.second.imag() << std::endl;
      datapar << "C"+to_string(i)+"IP " << couplings[i].second.second.real() << std::endl;
    }

  }

  
}
END_BE_INI_FUNCTION
