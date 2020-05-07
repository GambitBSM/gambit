//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Module functions associated with creating
///  and translating WIMP-nucleon and WIMP-quark 
///  effective operator couplings from GAMBIT
///  ModelParameters. Functions which compute
///  these EFT couplings for specific "UV" models 
///  live in DarkBit sources files named after those
///  models.
///
///  Includes module functions to compute
///  non-relativistic operator couplings from
///  relativistic ones using DirectDM.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2019 Jul
///
///  *********************************************

#include <boost/make_shared.hpp>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"
#include "gambit/DarkBit/ProcessCatalog.hpp"
#include "gambit/Utils/numerical_constants.hpp"

//#define DARKBIT_DEBUG

namespace Gambit
{

  namespace DarkBit
  {

    // Helper class used for WIMP EFT process catalog construction
    class WIMP_EFT_DM
    {
      public:
        /// Initialize object (branching ratios etc)
        WIMP_EFT_DM(
            TH_ProcessCatalog* const catalog)
            : mh   (catalog->getParticleProperty("h0_1").mass)
            , mb   (catalog->getParticleProperty("d_3").mass)
            , mc   (catalog->getParticleProperty("u_2").mass)
            , mtau (catalog->getParticleProperty("e-_3").mass)
            , mt   (catalog->getParticleProperty("u_3").mass)
            , mZ0  (catalog->getParticleProperty("Z0").mass)
            , mW   (catalog->getParticleProperty("W+").mass)
        {};

        /*! \brief Returns <sigma v> in cm3/s for given channel, velocity and
         *         model parameters.
         *
         * channel: bb, tautau, mumu, ss, cc, tt, gg, gammagamma, Zgamma, WW,
         * ZZ, hh
         *
         * Parameterises <sigma v> as A + Bv^2, i.e. s + p wave annihilation
         * with no resonances, subject to basic kinematic constraints. 
         */
        double sv(std::string channel, double mass, double A, double B, double v)
        {
          // Note: Valid for mass > 45 GeV

          // Hardcoded minimum velocity avoids NaN results.
          // Pat didn't like the hardcoded velocity
          v = std::max(v, 1e-6);

          double s = 4*mass*mass/(1-v*v/4);
          double sqrt_s = sqrt(s);
          if ( sqrt_s < 90 )
          {
            piped_invalid_point.request(
                "WIMP_EFT_DM sigmav called with sqrt_s < 90 GeV.");
            return 0;
          }

          if ( channel == "hh" )
          {
            if ( sqrt_s > mh*2 )
            {
              return A + B*v*v;
            }
            else return 0;
          }

          if ( channel == "bb" and sqrt_s < mb*2 ) return 0;
          if ( channel == "cc" and sqrt_s < mc*2  ) return 0;
          if ( channel == "tautau" and sqrt_s < mtau*2 ) return 0;
          if ( channel == "tt" and sqrt_s < mt*2 ) return 0;
          if ( channel == "ZZ" and sqrt_s < mZ0*2) return 0;
          if ( channel == "WW" and sqrt_s < mW*2) return 0;

          if ( sqrt_s < 300 )
          {
            // Explicitly close channel for off-shell top quarks
            if ( channel == "tt" and sqrt_s < mt*2) return 0;

            return A + B*v*v;
          }
          else
          {
            return A + B*v*v;
          }
          return 0;
        }

      private:
        double mh, mb, mc, mtau, mt, mZ0, mW;
    };

    /// DarkMatter_ID string for generic EFT dark matter 
    void DarkMatter_ID_EFT(std::string& result)
    {
       using namespace Pipes::DarkMatter_ID_EFT;
       result = Dep::WIMP_properties->name;
    }

    /// WIMP spin property extractor
    void jwimpx2_from_WIMPprops(unsigned int& result)
    {
       using namespace Pipes::jwimpx2_from_WIMPprops;
       result = Dep::WIMP_properties->spinx2;
    }

    /// WIMP mass property extractor
    void mwimp_from_WIMPprops(double& result)
    {
       using namespace Pipes::mwimp_from_WIMPprops;
       result = Dep::WIMP_properties->mass;
    }

    /// WIMP self conjugacy extractor
    void wimp_sc_from_WIMPprops(bool& result)
    {
       using namespace Pipes::wimp_sc_from_WIMPprops;
       result = Dep::WIMP_properties->sc;
    }



    //////////////////////////////////////////////////////////////////////////
    //
    //   Translation of NREO ModelParameters into NREO_DM_nucleon_couplings
    //
    //////////////////////////////////////////////////////////////////////////

    void NREO_couplings_from_parameters(NREO_DM_nucleon_couplings& NREO_couplings)
    {
       using namespace Pipes::NREO_couplings_from_parameters;
       NREO_couplings = NREO_DM_nucleon_couplings(Param); // Constructor takes care of the parameter copying for us
    }

    //////////////////////////////////////////////////////////////////////////
    //
    //   Translation of DD_couplings into NREO_DM_nucleon_couplings
    //
    //////////////////////////////////////////////////////////////////////////

    void NREO_from_DD_couplings(NREO_DM_nucleon_couplings& NREO_couplings)
    {
       using namespace Pipes::NREO_from_DD_couplings;
       DM_nucleon_couplings ddc = *Dep::DD_couplings;

       // TODO! I have not been able to find the exact conventions
       // used in DDcalc vs the NREO model. I think it is just this:
       // c0 = 0.5*(cp+cn)
       // c1 = 0.5*(cp-cn)
       // so that 
       // cp = c0 + c1
       // cn = c0 - c1
       // Change if needed!

       // From Catena & Schwabe (2015) (arXiv 1501.03729, bottom of page 5):
       // cp = (c0 + c1)/2
       // cn = (c0 - c1)/2
       // so
       // c0 = cp + cn
       // c1 = cp - cn
       // I've implemented the change to the factor of 2
    
       // Compute non-zero isospin basis couplings from DM_nucleon_couplings entries
       // TODO: I also did this from memory, should check I got the operator numbers right
       NREO_couplings.c0[1] = (ddc.gps + ddc.gns);
       NREO_couplings.c1[1] = (ddc.gps - ddc.gns);
       NREO_couplings.c0[4] = (ddc.gpa + ddc.gna);
       NREO_couplings.c1[4] = (ddc.gpa - ddc.gna);
    }

    /* Non-relativistic Wilson Coefficients, model independent */

    /// Obtain the non-relativistic Wilson Coefficients from a set of model
    /// specific relativistic Wilson Coefficients from DirectDM in the flavour
    /// matching scheme (default 5 flavours). NR WCs defined at 2 GeV.
    void DD_nonrel_WCs_flavscheme(NREO_DM_nucleon_couplings &result)
    {
      using namespace Pipes::DD_nonrel_WCs_flavscheme;

      // Number of quark flavours used for matching (default 5)
      int scheme = runOptions->getValueOrDef<int>(5, "flavs");

      // Only defined for 3, 4, + 5 flavour scheme.
      if (scheme != 3 && scheme != 4 && scheme != 5)
      {
        DarkBit_error().raise(LOCAL_INFO, "DD_nonrel_WCs_flavscheme quark flavour matching "
          "scheme must be for 3, 4 or 5 quark flavors only. Please check your YAML file.");
      }

      // Obtain spin of DM particle, plus identify whether DM is self-conjugate
      double mDM = Dep::WIMP_properties->mass;
      unsigned int sDM  = Dep::WIMP_properties->spinx2;
      bool is_SC = Dep::WIMP_properties->sc;

      // Set DM_type based on the spin and & conjugacy of DM
      std::string DM_type;

      // Nuisance params
      map_str_dbl inputs = *Dep::DirectDMNuisanceParameters;

      // Fermion case
      if (sDM == 1) { is_SC ? DM_type = "M" : DM_type = "D"; }
      // Scalar
      else if (sDM == 0) { is_SC ? DM_type = "R" : DM_type = "C"; }
      // Vector etc. DM not supported by DirectDM
      else DarkBit_error().raise(LOCAL_INFO, "DD_nonrel_WCs_flavscheme only usable for spin-0 and spin-1/2 DM.");

      // Relativistic Wilson Coefficients
      map_str_dbl relativistic_WCs = *Dep::DD_rel_WCs_flavscheme;

      // Get non-relativistic coefficients
      result = BEreq::get_NR_WCs_flav(relativistic_WCs, mDM, scheme, DM_type, inputs);
    }

    /// Obtain the non-relativistic Wilson Coefficients from a set of model
    /// specific relativistic Wilson Coefficients from DirectDM in the
    /// unbroken SM phase. NR WCs defined at 2 GeV.
    void DD_nonrel_WCs_EW(NREO_DM_nucleon_couplings &result)
    {
      using namespace Pipes::DD_nonrel_WCs_EW;

      // Specify the scale that the Lagrangian is defined at
      double scale = runOptions->getValue<double>("scale");
      // Hypercharge of DM
      double Ychi = runOptions->getValue<double>("Ychi");
      // SU(2) dimension of DM
      double dchi = runOptions->getValue<int>("dchi");

      // Obtain spin of DM particle, plus identify whether DM is self-conjugate
      double mDM = Dep::WIMP_properties->mass;
      unsigned int sDM  = Dep::WIMP_properties->spinx2;
      bool is_SC = Dep::WIMP_properties->sc;

      // Set DM_type based on the spin and & conjugacy of DM
      std::string DM_type;

      // Fermion case: set DM_type to Majorana or Dirac
      if (sDM == 1) { is_SC ? DM_type = "M" : DM_type = "D"; }
      // Scalar case: set DM type to real or complex
      else if (sDM == 0) { is_SC ? DM_type = "R" : DM_type = "C"; }
      // Vector etc. DM not supported by DirectDM
      else DarkBit_error().raise(LOCAL_INFO, "DD_nonrel_WCs_EW only usable for spin-0 and spin-1/2 DM.");

      // Relativistic Wilson Coefficients
      map_str_dbl relativistic_WCs = *Dep::DD_rel_WCs_EW;

      // Nuisance params
      map_str_dbl inputs = *Dep::DirectDMNuisanceParameters;

      // Get non-relativistic coefficients
      /// TODO - How to get hypercharge and SU(2) dimension for these fields!?
      /// Currently just comes from the YAML file. GUM? Process Catalogue?
      result = BEreq::get_NR_WCs_EW(relativistic_WCs, mDM, dchi, Ychi, scale, DM_type, inputs);
    }

    /// Module function providing nuisance parameters for
    /// to be passed to DirectDM directly from the model parameters.
    void ExtractDirectDMNuisanceParameters(map_str_dbl &result)
    {
      using namespace Pipes::ExtractDirectDMNuisanceParameters;


      // Kick things off with SMInputs
      SMInputs sminputs = *Dep::SMINPUTS; 

      result["aMZinv"] = sminputs.alphainv;    // 1: Inverse electromagnetic coupling at the Z pole in the MSbar scheme (with 5 active flavours)
      result["GF"] = sminputs.GF;              // 2: Fermi constant (in units of GeV^-2)
      result["asMZ"] = sminputs.alphaS;        // 3: Strong coupling at the Z pole in the MSbar scheme (with 5 active flavours).
      result["Mz"] = sminputs.mZ;              // 4: Z pole mass
      result["mb_at_mb"] = sminputs.mBmB;      // 5: b quark running mass in the MSbar scheme (at mB)
      result["mt_pole"] = sminputs.mT;         // 6: Top quark pole mass
      result["mtau"] = sminputs.mTau;          // 7: Tau pole mass
      result["me"] = sminputs.mE;              // 11: Electron pole mass
      result["mmu"] = sminputs.mMu;            // 13: Muon pole mass
      result["md_at_2GeV"] = sminputs.mD;      // 21: d quark running mass in the MSbar scheme at 2 GeV
      result["mu_at_2GeV"] = sminputs.mU;      // 22: u quark running mass in the MSbar scheme at 2 GeV
      result["ms_at_2GeV"] = sminputs.mS;      // 23: s quark running mass in the MSbar scheme at 2 GeV
      result["mc_at_mc"] = sminputs.mCmC;      // 24: c quark running mass in the MSbar scheme at mC

      // Then top it up with parameters from nuclear_params_ChPT.
      result["gA"]      = *Param["gA"];
      result["mG"]      = *Param["mG"];
      result["sigmaup"] = *Param["sigmaup"];
      result["sigmadp"] = *Param["sigmadp"];
      result["sigmaun"] = *Param["sigmaun"];
      result["sigmadn"] = *Param["sigmadn"];
      result["sigmas"]  = *Param["sigmas"];
      // Set p and n equal
      result["Deltaup"] = *Param["Deltaup"];
      result["Deltaun"] = *Param["Deltaup"];
      // Set p and n equal
      result["Deltadp"] = *Param["Deltadp"];
      result["Deltadn"] = *Param["Deltadp"];
      result["Deltas"]  = *Param["Deltas"];
      result["B0mu"]    = *Param["B0mu"];
      result["B0md"]    = *Param["B0md"];
      result["B0ms"]    = *Param["B0ms"];
      result["mup"]     = *Param["mup"];
      result["mun"]     = *Param["mun"];
      result["ap"]      = *Param["ap"];
      result["an"]      = *Param["an"];
      result["F2sp"]    = *Param["F2sp"];
      result["gTu"]     = *Param["gTu"];
      result["gTd"]     = *Param["gTd"];
      result["gTs"]     = *Param["gTs"];
      // Set p and n equal
      result["BT10up"]  = *Param["BT10up"];
      result["BT10un"]  = *Param["BT10up"];
      // Set p and n equal
      result["BT10dp"]  = *Param["BT10dp"];
      result["BT10dn"]  = *Param["BT10dp"];
      result["BT10s"]   = *Param["BT10s"];      
    }

    //////////////////////////////////////////////////////////////////////////
    //
    //   Process catalog setup
    //
    //////////////////////////////////////////////////////////////////////////


    /// Set up process catalog for a generic parameterisation of (two body) WIMP dark matter decays and annihilations.
    void TH_ProcessCatalog_WIMP_EFT(DarkBit::TH_ProcessCatalog &result)
    {
      using namespace Pipes::TH_ProcessCatalog_WIMP_EFT;
      using std::vector;
      using std::string;

      // Initialize empty catalog
      TH_ProcessCatalog catalog;

      // Select initial state particles from particle database
      std::string DMstr = Dep::WIMP_properties->name;
      double WIMP_mass = Dep::WIMP_properties->mass;
      unsigned int WIMP_spinx2 = Dep::WIMP_properties->spinx2;

      // Create container for annihilation processes for dark matter initial state
      TH_Process process_ann(DMstr, DMstr);

      // Explicitly state that Dirac DM is not self-conjugate to add extra
      // factors of 1/2 where necessary
      process_ann.isSelfConj = Dep::WIMP_properties->sc;

      ///////////////////////////////////////
      // Import particle masses and couplings
      ///////////////////////////////////////

      // Convenience macros
      #define getSMmass(Name, spinX2)                                           \
       catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> \
       (Name , TH_ParticleProperty(spec.get(Par::Pole_Mass,Name), spinX2)));
      #define addParticle(Name, Mass, spinX2)                                   \
       catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> \
       (Name , TH_ParticleProperty(Mass, spinX2)));

      // Import Standard Model spectrum object
      const Spectrum& spec = *Dep::SM_spectrum;
      const SMInputs& SMI  = spec.get_SMInputs();

      // Import couplings

      // Get SM pole masses
      getSMmass("e-_1",     1)
      getSMmass("e+_1",     1)
      getSMmass("e-_2",     1)
      getSMmass("e+_2",     1)
      getSMmass("e-_3",     1)
      getSMmass("e+_3",     1)
      getSMmass("Z0",     2)
      getSMmass("W+",     2)
      getSMmass("W-",     2)
      getSMmass("g",      2)
      getSMmass("gamma",  2)
      getSMmass("u_3",      1)
      getSMmass("ubar_3",   1)
      getSMmass("d_3",      1)
      getSMmass("dbar_3",   1)

      // Pole masses not available for the light quarks.
      addParticle("u_1"   , SMI.mU,  1) // mu(2 GeV)^MS-bar, not pole mass
      addParticle("ubar_1", SMI.mU,  1) // mu(2 GeV)^MS-bar, not pole mass
      addParticle("d_1"   , SMI.mD,  1) // md(2 GeV)^MS-bar, not pole mass
      addParticle("dbar_1", SMI.mD,  1) // md(2 GeV)^MS-bar, not pole mass
      addParticle("u_2"   , SMI.mCmC,1) // mc(mc)^MS-bar, not pole mass
      addParticle("ubar_2", SMI.mCmC,1) // mc(mc)^MS-bar, not pole mass
      addParticle("d_2"   , SMI.mS,  1) // ms(2 GeV)^MS-bar, not pole mass
      addParticle("dbar_2", SMI.mS,  1) // ms(2 GeV)^MS-bar, not pole mass

      // Masses for neutrino flavour eigenstates. Set to zero.
      // (presently not required)
      addParticle("nu_e",     0.0, 1)
      addParticle("nubar_e",  0.0, 1)
      addParticle("nu_mu",    0.0, 1)
      addParticle("nubar_mu", 0.0, 1)
      addParticle("nu_tau",   0.0, 1)
      addParticle("nubar_tau",0.0, 1)

      // Higgs-sector masses
      double mH = spec.get(Par::Pole_Mass,"h0_1");
      addParticle("h0_1",     mH, 0)  // SM-like Higgs
      addParticle("pi0",   meson_masses.pi0,       0)
      addParticle("pi+",   meson_masses.pi_plus,   0)
      addParticle("pi-",   meson_masses.pi_minus,  0)
      addParticle("eta",   meson_masses.eta,       0)
      addParticle("rho0",  meson_masses.rho0,      1)
      addParticle("rho+",  meson_masses.rho_plus,  1)
      addParticle("rho-",  meson_masses.rho_minus, 1)
      addParticle("omega", meson_masses.omega,     1)

      // Dark matter
      addParticle(DMstr, WIMP_mass, WIMP_spinx2)

      // Get rid of convenience macros
      #undef getSMmass
      #undef addParticle

      /////////////////////////////
      // Import Decay information
      /////////////////////////////

      // Import decay table from DecayBit
      const DecayTable* tbl = &(*Dep::decay_rates);

      // Save Higgs width for later
      double gammaH = tbl->at("h0_1").width_in_GeV;

      // Set of imported decays
      std::set<string> importedDecays;

      // Minimum branching ratio to include
      double minBranching = 0;

      // Import relevant decays (only Higgs and subsequent decays)
      using DarkBit_utils::ImportDecays;
      // Notes: Virtual Higgs decays into offshell W+W- final states are not
      // imported.  All other channels are correspondingly rescaled.  Decay
      // into FF final states is accounted for, leading to zero photons.
      ImportDecays("h0_1", catalog, importedDecays, tbl, minBranching,
          daFunk::vec<std::string>("Z0", "W+", "W-", "e+_2", "e-_2", "e+_3", "e-_3"));

      // Instantiate new WIMP_EFT_DM object
      auto wimpDM = boost::make_shared<WIMP_EFT_DM>(&catalog);

      // Populate annihilation channel list and add thresholds to threshold
      // list.
      // (remark: the lowest threshold is here = 2*WIMP_mass, whereas in DS-internal
      // conventions, this lowest threshold is not listed)
      process_ann.resonances_thresholds.threshold_energy.push_back(2*WIMP_mass);
      auto channel =
        daFunk::vec<string>("bb", "WW", "cc", "tautau", "ZZ", "tt", "hh");
      auto p1 =
        daFunk::vec<string>("d_3",   "W+", "u_2",   "e+_3", "Z0", "u_3",   "h0_1");
      auto p2 =
        daFunk::vec<string>("dbar_3","W-", "ubar_2","e-_3", "Z0", "ubar_3","h0_1");
      {
        #ifdef DARKBIT_DEBUG
          cout << "\nTH_ProcessCatalog_WIMP_EFT is constructing channels...\n";
        #endif
        for ( unsigned int i = 0; i < channel.size(); i++ )
        {
          double mtot_final =
            catalog.getParticleProperty(p1[i]).mass +
            catalog.getParticleProperty(p2[i]).mass;
          // Include final states that are open for T~m/20
          
          #ifdef DARKBIT_DEBUG
            cout << endl << channel[i] << " channel made from " << p1[i] << " and " << p2[i] << endl;
          #endif
          if ( WIMP_mass*2 > mtot_final*0.5 )
          {
            double A = Dep::generic_WIMP_sigmav->A(channel[i]);
            double B = Dep::generic_WIMP_sigmav->B(channel[i]);
            daFunk::Funk kinematicFunction = daFunk::funcM(wimpDM,
                &WIMP_EFT_DM::sv, channel[i], WIMP_mass, A, B, daFunk::var("v"));
            TH_Channel new_channel(
                daFunk::vec<string>(p1[i], p2[i]), kinematicFunction
                );
            process_ann.channelList.push_back(new_channel);
            #ifdef DARKBIT_DEBUG
              cout << WIMP_mass*2 << " is strictly greater than " << mtot_final*0.5 << endl;
              cout << "The corresponding parameters from generic_WIMP_sigmav, A: " << A << ", and B: " << B << endl;
              cout << "Printing the new_channel getting pushed onto the channelList: ";
              for ( auto it = new_channel.finalStateIDs.begin(); it != new_channel.finalStateIDs.end(); it++ ) cout << *it << " ";
              cout << endl;
            #endif
          }
          #ifdef DARKBIT_DEBUG
            else cout << "Dark matter mass is too small to add current annihilation channel to the channelList\n";
          #endif
          if ( WIMP_mass*2 > mtot_final )
          {
            process_ann.resonances_thresholds.threshold_energy.
              push_back(mtot_final);
          }
        }
      }

      // Populate resonance list
      // None for this model 

      // Add process to previous list
      catalog.processList.push_back(process_ann);

      // Validate
      catalog.validate();

      // Return the finished process catalog
      result = catalog;

    } // function TH_ProcessCatalog_WIMP_EFT
    
  }
}
