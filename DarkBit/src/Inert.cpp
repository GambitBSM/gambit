//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation of Inert
///  DarkBit routines.
///
///  Authors (add name and date if you modify):    
///       *** Automatically created by GUM ***     
///                                                
///  \author The GAMBIT Collaboration             
///  \date 03:33PM on February 18, 2026
///                                                
///  ********************************************* 

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "boost/make_shared.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"

namespace Gambit
{
  namespace DarkBit
  {
    class Inert
    {
      public:
      /// Initialize Inert object (branching ratios etc)
      Inert() {};
      ~Inert() {};
      
      // Annihilation cross-section. sigmav is a pointer to a CalcHEP backend function.
      double sv(str channel, DecayTable& tbl, double (*sigmav)(str&, std::vector<str>&, std::vector<str>&, double&, const DecayTable&), double v_rel)
      {
        /// Returns sigma*v for a given channel.
        double GeV2tocm3s1 = gev2cm2*s2cm;
        
        // CalcHEP args
        str model = "Inert"; // CalcHEP model name
        std::vector<str> in = {"~H0", "~H0"}; // In states: DM+DMbar
        std::vector<str> out; // Out states
        if (channel == "e+_2, e-_1") out = {"E2", "e1"};
        if (channel == "e+_3, e-_1") out = {"E3", "e1"};
        if (channel == "e+_1, e-_1") out = {"E1", "e1"};
        if (channel == "h0_2, A0") out = {"~H0", "~A0"};
        if (channel == "ubar_3, u_2") out = {"U3", "u2"};
        if (channel == "dbar_3, d_2") out = {"D3", "d2"};
        if (channel == "dbar_2, d_2") out = {"D2", "d2"};
        if (channel == "Z0, h0_1") out = {"Z", "h"};
        if (channel == "ubar_2, u_2") out = {"U2", "u2"};
        if (channel == "ubar_1, u_2") out = {"U1", "u2"};
        if (channel == "dbar_1, d_1") out = {"D1", "d1"};
        if (channel == "h0_1, h0_1") out = {"h", "h"};
        if (channel == "e+_3, e-_2") out = {"E3", "e2"};
        if (channel == "e+_2, e-_2") out = {"E2", "e2"};
        if (channel == "g, g") out = {"g", "g"};
        if (channel == "ubar_3, u_3") out = {"U3", "u3"};
        if (channel == "dbar_3, d_3") out = {"D3", "d3"};
        if (channel == "e+_1, e-_2") out = {"E1", "e2"};
        if (channel == "dbar_2, d_3") out = {"D2", "d3"};
        if (channel == "gamma, gamma") out = {"A", "A"};
        if (channel == "H-, H+") out = {"hp2", "Hp2"};
        if (channel == "W-, H+") out = {"Wm", "Hp2"};
        if (channel == "A0, A0") out = {"~A0", "~A0"};
        if (channel == "ubar_2, u_3") out = {"U2", "u3"};
        if (channel == "dbar_1, d_2") out = {"D1", "d2"};
        if (channel == "e+_3, e-_3") out = {"E3", "e3"};
        if (channel == "ubar_1, u_3") out = {"U1", "u3"};
        if (channel == "H-, W+") out = {"hp2", "Wp"};
        if (channel == "e+_2, e-_3") out = {"E2", "e3"};
        if (channel == "ubar_3, u_1") out = {"U3", "u1"};
        if (channel == "W-, W+") out = {"Wm", "Wp"};
        if (channel == "dbar_3, d_1") out = {"D3", "d1"};
        if (channel == "Z0, Z0") out = {"Z", "Z"};
        if (channel == "e+_1, e-_3") out = {"E1", "e3"};
        if (channel == "dbar_2, d_1") out = {"D2", "d1"};
        if (channel == "ubar_2, u_1") out = {"U2", "u1"};
        if (channel == "ubar_1, u_1") out = {"U1", "u1"};
        if (channel == "dbar_1, d_3") out = {"D1", "d3"};
        
        // Check the channel has been filled
        if (out.size() > 1) return sigmav(model, in, out, v_rel, tbl)*GeV2tocm3s1;
        else return 0;
      }
      
      
    };
    
    void TH_ProcessCatalog_Inert(TH_ProcessCatalog &result)
    {
      using namespace Pipes::TH_ProcessCatalog_Inert;
      using std::vector;
      using std::string;
      
      // Initialize empty catalog, main annihilation process
      TH_ProcessCatalog catalog;
      TH_Process process_ann("h0_2", "h0_2");
      
      // Explicitly state that DM is self-conjugate
      process_ann.isSelfConj = true;
      
      
      // Import particle masses 
      
      // Convenience macros
      #define getSMmass(Name, spinX2) catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> (Name, TH_ParticleProperty(SM.get(Par::Pole_Mass,Name), spinX2)));
      #define addParticle(Name, Mass, spinX2) catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> (Name, TH_ParticleProperty(Mass, spinX2)));
      
      // Import Spectrum objects
      const Spectrum& spec = *Dep::Inert_spectrum;
      const SubSpectrum& SM = spec.get_LE();
      const SMInputs& SMI   = spec.get_SMInputs();
      
      // Get SM pole masses
      getSMmass("e-_1",     1)
      getSMmass("e+_1",     1)
      getSMmass("e-_2",     1)
      getSMmass("e+_2",     1)
      getSMmass("e-_3",     1)
      getSMmass("e+_3",     1)
      getSMmass("Z0",       2)
      getSMmass("W+",       2)
      getSMmass("W-",       2)
      getSMmass("g",        2)
      getSMmass("gamma",    2)
      getSMmass("u_3",      1)
      getSMmass("ubar_3",   1)
      getSMmass("d_3",      1)
      getSMmass("dbar_3",   1)
      
      // Pole masses not available for the light quarks.
      addParticle("u_1"   , SMI.mU,  1) // mu(2 GeV)^MS-bar
      addParticle("ubar_1", SMI.mU,  1) // mu(2 GeV)^MS-bar
      addParticle("d_1"   , SMI.mD,  1) // md(2 GeV)^MS-bar
      addParticle("dbar_1", SMI.mD,  1) // md(2 GeV)^MS-bar
      addParticle("u_2"   , SMI.mCmC,1) // mc(mc)^MS-bar
      addParticle("ubar_2", SMI.mCmC,1) // mc(mc)^MS-bar
      addParticle("d_2"   , SMI.mS,  1) // ms(2 GeV)^MS-bar
      addParticle("dbar_2", SMI.mS,  1) // ms(2 GeV)^MS-bar
      
      // Masses for neutrino flavour eigenstates. Set to zero.
      // (presently not required)
      addParticle("nu_e",     0.0, 1)
      addParticle("nubar_e",  0.0, 1)
      addParticle("nu_mu",    0.0, 1)
      addParticle("nubar_mu", 0.0, 1)
      addParticle("nu_tau",   0.0, 1)
      addParticle("nubar_tau",0.0, 1)
      
      // Meson masses
      addParticle("pi0",   meson_masses.pi0,       0)
      addParticle("pi+",   meson_masses.pi_plus,   0)
      addParticle("pi-",   meson_masses.pi_minus,  0)
      addParticle("eta",   meson_masses.eta,       0)
      addParticle("rho0",  meson_masses.rho0,      1)
      addParticle("rho+",  meson_masses.rho_plus,  1)
      addParticle("rho-",  meson_masses.rho_minus, 1)
      addParticle("omega", meson_masses.omega,     1)
      
      // Inert-specific masses
      double mh0_2 = spec.get(Par::Pole_Mass, "h0_2");
      addParticle("h0_2", mh0_2, 0);
      addParticle("h0_1", spec.get(Par::Pole_Mass, "h0_1"), 0);
      addParticle("A0", spec.get(Par::Pole_Mass, "A0"), 0);
      addParticle("H+", spec.get(Par::Pole_Mass, "H+"), 0);
      addParticle("H-", spec.get(Par::Pole_Mass, "H-"), 0);
      
      // Get rid of convenience macros
      #undef getSMmass
      #undef addParticle
      
      // Import decay table from DecayBit
      DecayTable tbl = *Dep::decay_rates;
      
      // Set of imported decays
      std::set<string> importedDecays;
      
      // Minimum branching ratio to include
      double minBranching = runOptions->getValueOrDef<double>(0.0, "ProcessCatalog_MinBranching");
      
      // Import relevant decays
      using DarkBit_utils::ImportDecays;
      
      auto excludeDecays = daFunk::vec<std::string>("Z0", "W+", "W-", "e+_3", "e-_3", "e+_2", "e-_2");
      
      ImportDecays("h0_2", catalog, importedDecays, &tbl, minBranching, excludeDecays);
      ImportDecays("A0", catalog, importedDecays, &tbl, minBranching, excludeDecays);
      ImportDecays("H+", catalog, importedDecays, &tbl, minBranching, excludeDecays);
      ImportDecays("W-", catalog, importedDecays, &tbl, minBranching, excludeDecays);
      ImportDecays("Z0", catalog, importedDecays, &tbl, minBranching, excludeDecays);
      ImportDecays("W+", catalog, importedDecays, &tbl, minBranching, excludeDecays);
      ImportDecays("h0_1", catalog, importedDecays, &tbl, minBranching, excludeDecays);
      ImportDecays("H-", catalog, importedDecays, &tbl, minBranching, excludeDecays);
      
      // Instantiate new Inert object.
      auto pc = boost::make_shared<Inert>();
      
      // Populate annihilation channel list and add thresholds to threshold list.
      process_ann.resonances_thresholds.threshold_energy.push_back(2*mh0_2);
      auto channels = 
        daFunk::vec<string>("e+_2, e-_1", "e+_3, e-_1", "e+_1, e-_1", "h0_2, A0", "ubar_3, u_2", "dbar_3, d_2", "dbar_2, d_2", "Z0, h0_1", "ubar_2, u_2", "ubar_1, u_2", "dbar_1, d_1", "h0_1, h0_1", "e+_3, e-_2", "e+_2, e-_2", "g, g", "ubar_3, u_3", "dbar_3, d_3", "e+_1, e-_2", "dbar_2, d_3", "gamma, gamma", "H-, H+", "W-, H+", "A0, A0", "ubar_2, u_3", "dbar_1, d_2", "e+_3, e-_3", "ubar_1, u_3", "H-, W+", "e+_2, e-_3", "ubar_3, u_1", "W-, W+", "dbar_3, d_1", "Z0, Z0", "e+_1, e-_3", "dbar_2, d_1", "ubar_2, u_1", "ubar_1, u_1", "dbar_1, d_3");
      auto p1 = 
        daFunk::vec<string>("e+_2", "e+_3", "e+_1", "h0_2", "ubar_3", "dbar_3", "dbar_2", "Z0", "ubar_2", "ubar_1", "dbar_1", "h0_1", "e+_3", "e+_2", "g", "ubar_3", "dbar_3", "e+_1", "dbar_2", "gamma", "H-", "W-", "A0", "ubar_2", "dbar_1", "e+_3", "ubar_1", "H-", "e+_2", "ubar_3", "W-", "dbar_3", "Z0", "e+_1", "dbar_2", "ubar_2", "ubar_1", "dbar_1");
      auto p2 = 
        daFunk::vec<string>("e-_1", "e-_1", "e-_1", "A0", "u_2", "d_2", "d_2", "h0_1", "u_2", "u_2", "d_1", "h0_1", "e-_2", "e-_2", "g", "u_3", "d_3", "e-_2", "d_3", "gamma", "H+", "H+", "A0", "u_3", "d_2", "e-_3", "u_3", "W+", "e-_3", "u_1", "W+", "d_1", "Z0", "e-_3", "d_1", "u_1", "u_1", "d_3");
      
      for (unsigned int i = 0; i < channels.size(); ++i)
      {
        double mtot_final = 
        catalog.getParticleProperty(p1[i]).mass + 
        catalog.getParticleProperty(p2[i]).mass;  
        if (mh0_2*2 > mtot_final*0.5)
        {
          daFunk::Funk kinematicFunction = daFunk::funcM(pc, &Inert::sv, channels[i], tbl, 
          BEreq::CH_Sigma_V.pointer(), daFunk::var("v"));
          TH_Channel new_channel(daFunk::vec<string>(p1[i], p2[i]), kinematicFunction);
          process_ann.channelList.push_back(new_channel);
        }
        if (mh0_2*2 < mtot_final)
        {
          process_ann.resonances_thresholds.threshold_energy.
          push_back(mtot_final);
        }
      }
      
      if ( (spec.has(Par::Pole_Mass, "A0") ? spec.get(Par::Pole_Mass, "A0") : spec.get(Par::mass1, "A0")) >= 2*mh0_2)
        process_ann.resonances_thresholds.resonances.push_back(TH_Resonance(spec.get(Par::Pole_Mass, "A0"), tbl.at("A0").width_in_GeV));
      if ( (spec.has(Par::Pole_Mass, "H+") ? spec.get(Par::Pole_Mass, "H+") : spec.get(Par::mass1, "H+")) >= 2*mh0_2)
        process_ann.resonances_thresholds.resonances.push_back(TH_Resonance(spec.get(Par::Pole_Mass, "H+"), tbl.at("H+").width_in_GeV));
      if ( (spec.has(Par::Pole_Mass, "W-") ? spec.get(Par::Pole_Mass, "W-") : spec.get(Par::mass1, "W-")) >= 2*mh0_2)
        process_ann.resonances_thresholds.resonances.push_back(TH_Resonance(spec.get(Par::Pole_Mass, "W-"), tbl.at("W-").width_in_GeV));
      if ( (spec.has(Par::Pole_Mass, "Z0") ? spec.get(Par::Pole_Mass, "Z0") : spec.get(Par::mass1, "Z0")) >= 2*mh0_2)
        process_ann.resonances_thresholds.resonances.push_back(TH_Resonance(spec.get(Par::Pole_Mass, "Z0"), tbl.at("Z0").width_in_GeV));
      if ( (spec.has(Par::Pole_Mass, "W+") ? spec.get(Par::Pole_Mass, "W+") : spec.get(Par::mass1, "W+")) >= 2*mh0_2)
        process_ann.resonances_thresholds.resonances.push_back(TH_Resonance(spec.get(Par::Pole_Mass, "W+"), tbl.at("W+").width_in_GeV));
      if ( (spec.has(Par::Pole_Mass, "h0_1") ? spec.get(Par::Pole_Mass, "h0_1") : spec.get(Par::mass1, "h0_1")) >= 2*mh0_2)
        process_ann.resonances_thresholds.resonances.push_back(TH_Resonance(spec.get(Par::Pole_Mass, "h0_1"), tbl.at("h0_1").width_in_GeV));
      if ( (spec.has(Par::Pole_Mass, "H-") ? spec.get(Par::Pole_Mass, "H-") : spec.get(Par::mass1, "H-")) >= 2*mh0_2)
        process_ann.resonances_thresholds.resonances.push_back(TH_Resonance(spec.get(Par::Pole_Mass, "H-"), tbl.at("H-").width_in_GeV));
      
      catalog.processList.push_back(process_ann);
      
      // Validate
      catalog.validate();
      
      result = catalog;
    } // function TH_ProcessCatalog
    
    void DarkMatter_ID_Inert(std::string& result){ result = "h0_2"; }
    
    void DarkMatterConj_ID_Inert(std::string& result){ result = "h0_2"; }
    
  } //namespace DarkBit
  
} //namespace Gambit

