//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementation of scalar singlet DM routines.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date Oct 2014, Apr 2015
///
///  \author Torsten Bringmann
///  \date May 2015
///
///  \author Pat Scott
///          <p.scott@imperial.ac.uk>
///  \date 2015 May, Jul
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/virtual_higgs.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "boost/make_shared.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"

namespace Gambit
{

  namespace DarkBit
  {
    //#define DARKBIT_DEBUG

    class ScalarSingletDM
    {
      public:
        /// Initialize SingletDM object (branching ratios etc)
        ScalarSingletDM(
            TH_ProcessCatalog* const catalog,
            double gammaH,
            double vev,
            double alpha_strong,
            double vSigma_s)
        : Gamma_mh(gammaH), v0 (vev),
          alpha_s (alpha_strong), vSigma_semi (vSigma_s)
        {
          mh   = catalog->getParticleProperty("h0_1").mass;
          mb   = catalog->getParticleProperty("d_3").mass;
          mc   = catalog->getParticleProperty("u_2").mass;
          mtau = catalog->getParticleProperty("e-_3").mass;
          mt   = catalog->getParticleProperty("u_3").mass;
          mZ0  = catalog->getParticleProperty("Z0").mass;
          mW   = catalog->getParticleProperty("W+").mass;
          mS   = catalog->getParticleProperty("S").mass;
        };
        ~ScalarSingletDM() {}

        /// Helper function (Breit-Wigner)
        double Dh2 (double s)
        {
          return 1/((s-mh*mh)*(s-mh*mh)+mh*mh*Gamma_mh*Gamma_mh);
        }

        /*! \brief Returns <sigma v> in cm3/s for given channel, velocity and
         *         model parameters.
         *
         * channel: bb, tautau, mumu, ss, cc, tt, gg, gammagamma, Zgamma, WW,
         * ZZ, hh
         */
        double sv(std::string channel, double lambda, double mass, double v)
        {

          // Note: Valid for mass > 45 GeV
          double s = 4*mass*mass/(1-v*v/4);
          double sqrt_s = sqrt(s);
          if ( sqrt_s < 90 )
          {
            piped_invalid_point.request(
                "SingletDM sigmav called with sqrt_s < 90 GeV.");
            return 0;
          }

          if ( channel == "Sh" )
          {
            if (sqrt_s > (mh+mS)) return vSigma_semi;
            else return 0;
          }

          if ( channel == "hh" )
          {
            if ( sqrt_s > mh*2 )
            {
              double GeV2tocm3s1 = gev2cm2*s2cm;
              return sv_hh(lambda, mass, v)*GeV2tocm3s1;
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
            double br = virtual_SMHiggs_widths(channel,sqrt_s);
            double Gamma_s = virtual_SMHiggs_widths("Gamma",sqrt_s);
            double GeV2tocm3s1 = gev2cm2*s2cm;

            // Explicitly close channel for off-shell top quarks
            if ( channel == "tt" and sqrt_s < mt*2) return 0;

            double res = 2*lambda*lambda*v0*v0/
              sqrt_s*Dh2(s)*Gamma_s*GeV2tocm3s1*br;
            return res;
          }
          else
          {
            if ( channel == "bb" ) return sv_ff(lambda, mass, v, mb, true);
            if ( channel == "cc" ) return sv_ff(lambda, mass, v, mc, true);
            if ( channel == "tautau" ) return sv_ff(lambda, mass, v, mtau, false);
            if ( channel == "tt" ) return sv_ff(lambda, mass, v, mt, true);
            if ( channel == "ZZ" ) return sv_ZZ(lambda, mass, v);
            if ( channel == "WW" ) return sv_WW(lambda, mass, v);
          }
          return 0;
        }

        // Annihilation into W bosons.
        double sv_WW(double lambda, double mass, double v)
        {
          double s = 4*mass*mass/(1-v*v/4);
          double x = pow(mW,2)/s;
          double GeV2tocm3s1 = gev2cm2*s2cm;
          return pow(lambda,2)*s/8/M_PI*sqrt(1-4*x)*Dh2(s)*(1-4*x+12*pow(x,2))
            *GeV2tocm3s1;
        }

        // Annihilation into Z bosons.
        double sv_ZZ(double lambda, double mass, double v)
        {
          double s = 4*mass*mass/(1-v*v/4);
          double x = pow(mZ0,2)/s;
          double GeV2tocm3s1 = gev2cm2*s2cm;
          return pow(lambda,2)*s/16/M_PI*sqrt(1-4*x)*Dh2(s)*(1-4*x+12*pow(x,2))
            * GeV2tocm3s1;
        }

        // Annihilation into fermions
        double sv_ff(
            double lambda, double mass, double v, double mf, bool is_quark)
        {
          double s = 4*mass*mass/(1-v*v/4);
          double vf = sqrt(1-4*pow(mf,2)/s);
          double Xf = 1;
          if ( is_quark ) Xf = 3 *
            (1+(3/2*log(pow(mf,2)/s)+9/4)*4*alpha_s/3/M_PI);
          double GeV2tocm3s1 = gev2cm2*s2cm;
          return pow(lambda,2)*
            pow(mf,2)/4/M_PI*Xf*pow(vf,3) * Dh2(s) * GeV2tocm3s1;
        }

        /// Annihilation into hh
        double sv_hh(double lambda, double mass, double v)
        {

          double s = 4*mass*mass/(1-v*v/4);  // v is relative velocity
          double vh = sqrt(1-4*mh*mh/s);  // vh and vs are lab velocities
          // Hardcoded lower velocity avoids nan results
          double vs = std::max(v/2, 1e-6);
          double tp = pow(mass,2)+pow(mh,2)-0.5*s*(1-vs*vh);
          double tm = pow(mass,2)+pow(mh,2)-0.5*s*(1+vs*vh);

          double aR = 1+3*mh*mh*(s-mh*mh)*Dh2(s);
          double aI = 3*mh*mh*sqrt(s)*Gamma_mh*Dh2(s);

          return pow(lambda,2)/16/M_PI/pow(s,2)/vs *
            (
             (pow(aR,2)+pow(aI,2))*s*vh*vs
             +4*lambda*pow(v0,2)*(aR-lambda*pow(v0,2)/(s-2*pow(mh,2)))
             *log(std::abs(pow(mass,2)-tp)/std::abs(pow(mass,2)-tm))
             +(2*pow(lambda,2)*pow(v0,4)*s*vh*vs)
             /(pow(mass,2)-tm)/(pow(mass,2)-tp));
        }

      private:
        double Gamma_mh, mh, v0, alpha_s, mb, mc, mtau, mt, mZ0, mW, mS, vSigma_semi;
    };

    void DarkMatter_ID_ScalarSingletDM(std::string & result) { result = "S"; }

    /// Common code for different scalar singlet direct detection coupling routines
    void get_ScalarSingletDM_DD_couplings(const Spectrum &spec, DM_nucleon_couplings &result, Models::safe_param_map<safe_ptr<const double> > &Param)
    {
      const SubSpectrum& he = spec.get_HE();
      double mass = spec.get(Par::Pole_Mass,"S");
      double lambda = he.get(Par::dimensionless,"lambda_hS");
      double mh = spec.get(Par::Pole_Mass,"h0_1");

      // Expressions taken from Cline et al. (2013, PRD 88:055025, arXiv:1306.4710)
      double fp = 2./9. + 7./9.*(*Param["fpu"] + *Param["fpd"] + *Param["fps"]);
      double fn = 2./9. + 7./9.*(*Param["fnu"] + *Param["fnd"] + *Param["fns"]);

      result.gps = lambda*fp*m_proton/pow(mh,2)/mass/2;
      result.gns = lambda*fn*m_neutron/pow(mh,2)/mass/2;
      result.gpa = 0;  // Only SI cross-section
      result.gna = 0;

      logger() << LogTags::debug << "Singlet DM DD couplings:" << std::endl;
      logger() << " gps = " << result.gps << std::endl;
      logger() << " gns = " << result.gns << std::endl;
      logger() << " gpa = " << result.gpa << std::endl;
      logger() << " gna = " << result.gna << EOM;
    }

    /// Direct detection couplings for Z2 scalar singlet DM.
    void DD_couplings_ScalarSingletDM_Z2(DM_nucleon_couplings &result)
    {
      using namespace Pipes::DD_couplings_ScalarSingletDM_Z2;
      const Spectrum& spec = *Dep::ScalarSingletDM_Z2_spectrum;
      get_ScalarSingletDM_DD_couplings(spec, result, Param);
    }

    /// Direct detection couplings for Z3 scalar singlet DM.
    void DD_couplings_ScalarSingletDM_Z3(DM_nucleon_couplings &result)
    {
      using namespace Pipes::DD_couplings_ScalarSingletDM_Z3;
      const Spectrum& spec = *Dep::ScalarSingletDM_Z3_spectrum;
      get_ScalarSingletDM_DD_couplings(spec, result, Param);
    }


    /// Set up process catalog for Z2 scalar singlet DM.
    void TH_ProcessCatalog_ScalarSingletDM_Z2(DarkBit::TH_ProcessCatalog &result)
    {
      using namespace Pipes::TH_ProcessCatalog_ScalarSingletDM_Z2;
      using std::vector;
      using std::string;

      // Initialize empty catalog and main annihilation process
      TH_ProcessCatalog catalog;
      TH_Process process_ann("S", "S");

      // Explicitly state that Z2 Scalar DM is self-conjugate
      process_ann.isSelfConj = true;

      ///////////////////////////////////////
      // Import particle masses and couplings
      ///////////////////////////////////////

      // Convenience macros
      #define getSMmass(Name, spinX2)                                           \
       catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> \
       (Name , TH_ParticleProperty(SM.get(Par::Pole_Mass,Name), spinX2)));
      #define addParticle(Name, Mass, spinX2)                                   \
       catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> \
       (Name , TH_ParticleProperty(Mass, spinX2)));

      // Import Spectrum objects
      const Spectrum& spec = *Dep::ScalarSingletDM_Z2_spectrum;
      const SubSpectrum& he = spec.get_HE();
      const SubSpectrum& SM = spec.get_LE();
      const SMInputs& SMI   = spec.get_SMInputs();

      // Import couplings
      double lambda = he.get(Par::dimensionless,"lambda_hS");
      double v = he.get(Par::mass1,"vev");

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
      double alpha_s = SMI.alphaS;      // alpha_s(mZ)^MSbar

      // Masses for neutrino flavour eigenstates. Set to zero.
      // (presently not required)
      addParticle("nu_e",     0.0, 1)
      addParticle("nubar_e",  0.0, 1)
      addParticle("nu_mu",    0.0, 1)
      addParticle("nubar_mu", 0.0, 1)
      addParticle("nu_tau",   0.0, 1)
      addParticle("nubar_tau",0.0, 1)

      // Higgs-sector masses
      double mS = spec.get(Par::Pole_Mass,"S");
      double mH = spec.get(Par::Pole_Mass,"h0_1");
      addParticle("S",        mS, 0)  // Scalar Singlet DM
      addParticle("h0_1",     mH, 0)  // SM-like Higgs
      addParticle("pi0",   meson_masses.pi0,       0)
      addParticle("pi+",   meson_masses.pi_plus,   0)
      addParticle("pi-",   meson_masses.pi_minus,  0)
      addParticle("eta",   meson_masses.eta,       0)
      addParticle("rho0",  meson_masses.rho0,      1)
      addParticle("rho+",  meson_masses.rho_plus,  1)
      addParticle("rho-",  meson_masses.rho_minus, 1)
      addParticle("omega", meson_masses.omega,     1)

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
      // into SS final states is accounted for, leading to zero photons.
      ImportDecays("h0_1", catalog, importedDecays, tbl, minBranching,
          daFunk::vec<std::string>("Z0", "W+", "W-", "e+_2", "e-_2", "e+_3", "e-_3"));

      // Instantiate new ScalarSingletDM object
      auto singletDM = boost::make_shared<ScalarSingletDM>(&catalog, gammaH, v, alpha_s, 0.0);

      // Populate annihilation channel list and add thresholds to threshold
      // list.
      // (remark: the lowest threshold is here = 2*mS, whereas in DS-internal
      // conventions, this lowest threshold is not listed)
      process_ann.resonances_thresholds.threshold_energy.push_back(2*mS);
      auto channel =
        daFunk::vec<string>("bb", "WW", "cc", "tautau", "ZZ", "tt", "hh");
      auto p1 =
        daFunk::vec<string>("d_3",   "W+", "u_2",   "e+_3", "Z0", "u_3",   "h0_1");
      auto p2 =
        daFunk::vec<string>("dbar_3","W-", "ubar_2","e-_3", "Z0", "ubar_3","h0_1");
      {
        for ( unsigned int i = 0; i < channel.size(); i++ )
        {
          double mtot_final =
            catalog.getParticleProperty(p1[i]).mass +
            catalog.getParticleProperty(p2[i]).mass;
          // Include final states that are open for T~m/20
          if ( mS*2 > mtot_final*0.5 )
          {
            daFunk::Funk kinematicFunction = daFunk::funcM(singletDM,
                &ScalarSingletDM::sv, channel[i], lambda, mS, daFunk::var("v"));
            TH_Channel new_channel(
                daFunk::vec<string>(p1[i], p2[i]), kinematicFunction
                );
            process_ann.channelList.push_back(new_channel);
          }
          if ( mS*2 > mtot_final )
          {
            process_ann.resonances_thresholds.threshold_energy.
              push_back(mtot_final);
          }
        }
      }

      // Populate resonance list
      if ( mH >= mS*2 ) process_ann.resonances_thresholds.resonances.
          push_back(TH_Resonance(mH, gammaH));

      catalog.processList.push_back(process_ann);

      // Validate
      catalog.validate();


      #ifdef DARKBIT_DEBUG
        // get DarkBit computed vSigma total
        // so we can compare with that from MO
        ScalarSingletDM test = *singletDM;
        int nc = 7;
        double total = 0;
        for (int ii=0; ii < nc ; ii++)
        {
          total = total + test.sv(channel[ii], lambda, mS, 0.0);
        }
        cout << " --- Testing process catalouge --- " << endl;
        cout << "Total sigma V from process catalouge = " << total << endl;
        cout << " ---------- " << endl;
      #endif



      result = catalog;
    } // function TH_ProcessCatalog_ScalarSingletDM_Z2



    /// Set up process catalog for Z3 scalar singlet DM.
    void TH_ProcessCatalog_ScalarSingletDM_Z3(DarkBit::TH_ProcessCatalog &result)
    {
      using namespace Pipes::TH_ProcessCatalog_ScalarSingletDM_Z3;
      using std::vector;
      using std::string;

      // Initialize empty catalog and main annihilation process
      TH_ProcessCatalog catalog;
      TH_Process process_ann("S", "S");

      // Explicitly state that Z3 Scalar DM is not self-conjugate
      process_ann.isSelfConj = false;

      // get semi-annihilation cross-section from MicrOmegas

      // set requested spectra to NULL since we don't need them
      double * SpNe=NULL,*SpNm=NULL,*SpNl=NULL;
      double * SpA=NULL,*SpE=NULL,*SpP=NULL;
      int err;

      double vSigma_total = BEreq::calcSpectrum(byVal(3),byVal(SpA),byVal(SpE),byVal(SpP),byVal(SpNe),byVal(SpNm),byVal(SpNl) ,byVal(&err));

      if (err != 0 )
      {
         DarkBit_error().raise(LOCAL_INFO, "MicrOmegas spectrum calculation returned error code = " + std::to_string(err));
      }

      // get BR for each channel as filled by calcSpectrum
      MicrOmegas::aChannel* vSigmaCh;
      vSigmaCh = *BEreq::vSigmaCh;

      int n_channels = sizeof(vSigmaCh);
      double BR_semi = 0; // semi-annihilation BR
      #ifdef DARKBIT_DEBUG
        cout << "--- Semi-annihilation processes and BRs --- " << endl;
      #endif
      // find semi-annihilation channels
      int i = 0;
      while ((vSigmaCh[i].weight!=0) && (i < n_channels))
      {
        // get final states
        const char* p1 = vSigmaCh[i].prtcl[2];
        const char* p2 = vSigmaCh[i].prtcl[3];
        // semi-annihilation final states are h + ~ss or h + ~SS

        if ( (strcmp(p1,"h")==0) && ( (strcmp(p2,"~ss")==0) || (strcmp(p2,"~SS")==0) ) )
        {
          BR_semi = BR_semi + vSigmaCh[i].weight;
          #ifdef DARKBIT_DEBUG
            cout << "process: " << vSigmaCh[i].prtcl[0] << " + ";
            cout << vSigmaCh[i].prtcl[1] << " -> " << p1 << " + " << p2;
            cout << ",  BR = " << vSigmaCh[i].weight << endl;
          #endif
        }
        i++;
      }

      // Get the semi-annihilation cross-section, accounting for the fact that MO already scales
      // vSigma_total down by a factor of 2 to account for the fact that Z3 scalar singlet DM is not self-conjugate.
      double vSigma_semi = BR_semi * 2.0 * vSigma_total;

      #ifdef DARKBIT_DEBUG
        cout << "---  --- " << endl;
        cout << "Total sigma v from MicrOmegas = " << vSigma_total << " cm^3/s" << endl;
        cout << "semi-annihilation BR = " << BR_semi << endl;
        cout << "semi-annihilation sigma v from MicrOmegas = " << 0.5*vSigma_semi << " cm^3/s" << endl;
        cout << "Total sigma v from MicrOmegas excluding semi-annihilations  = " << vSigma_total - 0.5*vSigma_semi << endl;
        cout << "--------- " << endl;
      #endif


      ///////////////////////////////////////
      // Import particle masses and couplings
      ///////////////////////////////////////

      // Convenience macros
      #define getSMmass(Name, spinX2)                                           \
       catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> \
       (Name , TH_ParticleProperty(SM.get(Par::Pole_Mass,Name), spinX2)));
      #define addParticle(Name, Mass, spinX2)                                   \
       catalog.particleProperties.insert(std::pair<string, TH_ParticleProperty> \
       (Name , TH_ParticleProperty(Mass, spinX2)));

      // Import Spectrum objects
      const Spectrum& spec = *Dep::ScalarSingletDM_Z3_spectrum;
      const SubSpectrum& he = spec.get_HE();
      const SubSpectrum& SM = spec.get_LE();
      const SMInputs& SMI   = spec.get_SMInputs();

      // Import couplings
      double lambda = he.get(Par::dimensionless,"lambda_hS");
      double v = he.get(Par::mass1,"vev");

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
      double alpha_s = SMI.alphaS;      // alpha_s(mZ)^MSbar

      // Masses for neutrino flavour eigenstates. Set to zero.
      // (presently not required)
      addParticle("nu_e",     0.0, 1)
      addParticle("nubar_e",  0.0, 1)
      addParticle("nu_mu",    0.0, 1)
      addParticle("nubar_mu", 0.0, 1)
      addParticle("nu_tau",   0.0, 1)
      addParticle("nubar_tau",0.0, 1)

      // Higgs-sector masses
      double mS = spec.get(Par::Pole_Mass,"S");
      double mH = spec.get(Par::Pole_Mass,"h0_1");
      addParticle("S",        mS, 0)  // Scalar Singlet DM
      addParticle("h0_1",     mH, 0)  // SM-like Higgs
      addParticle("pi0",   meson_masses.pi0,       0)
      addParticle("pi+",   meson_masses.pi_plus,   0)
      addParticle("pi-",   meson_masses.pi_minus,  0)
      addParticle("eta",   meson_masses.eta,       0)
      addParticle("rho0",  meson_masses.rho0,      1)
      addParticle("rho+",  meson_masses.rho_plus,  1)
      addParticle("rho-",  meson_masses.rho_minus, 1)
      addParticle("omega", meson_masses.omega,     1)

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
      // into SS final states is accounted for, leading to zero photons.
      ImportDecays("h0_1", catalog, importedDecays, tbl, minBranching,
          daFunk::vec<std::string>("Z0", "W+", "W-", "e+_2", "e-_2", "e+_3", "e-_3"));

      // Instantiate new ScalarSingletDM object
      auto singletDM = boost::make_shared<ScalarSingletDM>(&catalog, gammaH, v, alpha_s, vSigma_semi);

      // Populate annihilation channel list and add thresholds to threshold
      // list.
      // (remark: the lowest threshold is here = 2*mS, whereas in DS-internal
      // conventions, this lowest threshold is not listed)
      process_ann.resonances_thresholds.threshold_energy.push_back(2*mS);
      auto channel =
        daFunk::vec<string>("bb", "WW", "cc", "tautau", "ZZ", "tt", "hh", "Sh");
      auto p1 =
        daFunk::vec<string>("d_3",   "W+", "u_2",   "e+_3", "Z0", "u_3", "h0_1", "S");
      auto p2 =
        daFunk::vec<string>("dbar_3","W-", "ubar_2","e-_3", "Z0", "ubar_3", "h0_1", "h0_1");
      {
        for ( unsigned int i = 0; i < channel.size(); i++ )
        {
          double mtot_final =
            catalog.getParticleProperty(p1[i]).mass +
            catalog.getParticleProperty(p2[i]).mass;
          // Include final states that are open for T~m/20
          if ( mS*2 > mtot_final*0.5 )
          {
            daFunk::Funk kinematicFunction = daFunk::funcM(singletDM,
                &ScalarSingletDM::sv, channel[i], lambda, mS, daFunk::var("v"));
            TH_Channel new_channel(
                daFunk::vec<string>(p1[i], p2[i]), kinematicFunction
                );
            process_ann.channelList.push_back(new_channel);
          }
          if ( mS*2 > mtot_final )
          {
            process_ann.resonances_thresholds.threshold_energy.
              push_back(mtot_final);
          }
        }
      }

      // Populate resonance list
      if ( mH >= mS*2 ) process_ann.resonances_thresholds.resonances.
          push_back(TH_Resonance(mH, gammaH));

      catalog.processList.push_back(process_ann);

      // Validate
      catalog.validate();

      #ifdef DARKBIT_DEBUG
        // get DarkBit computed vSigma total
        // so we can compare with that from MO
        ScalarSingletDM test = *singletDM;
        int nc = 7;
        double total = 0;
        for (int ii=0; ii < nc ; ii++)
        {
          total = total + test.sv(channel[ii], lambda, mS, 0.0);
        }
        cout << " --- Testing process catalouge --- " << endl;
        cout << "Total sigma V from process catalouge excluding semi-annihilations = " << total << endl;
        total = total + test.sv("Sh", lambda, mS, 0.0);
        cout << "Total including semi-annihilations = " << total << endl;
        cout << " ---------- " << endl;
      #endif

      result = catalog;
    } // function TH_ProcessCatalog_ScalarSingletDM_Z3



  }
}
