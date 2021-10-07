//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Routines for the calculation of particle yields
///  from dark matter annihilation / decay.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 Jul - 2015 May
///
///  \author Sebastian Wild
///          (sebastian.wild@ph.tum.de)
///  \date 2016 Aug
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2018 Aug
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Nov, Dec
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2021 Mar
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/DarkBit/DarkBit_utils.hpp"

//#define DARKBIT_DEBUG

namespace Gambit
{
  namespace DarkBit
  {

    /*! \brief Boosts an energy spectrum of isotropic particles into another
     *         frame (and isotropizes again).
     *  Parameters:
     *    gamma: Lorentz boost factor
     *    dNdE: Spectrum
     *    mass: mass of particle
     */
    daFunk::Funk boost_dNdE(daFunk::Funk dNdE, double gamma, double mass)
    {
      if ( gamma < 1.0 + .02 )  // Ignore less than 2% boosts
      {
        if (gamma < 1.0)
          DarkBit_error().raise(LOCAL_INFO,
            "boost_dNdE: Requested Lorentz boost with gamma < 1");
        return dNdE;
      }
      double betaGamma = sqrt(gamma*gamma-1);
      daFunk::Funk E = daFunk::var("E");
      daFunk::Funk lnE = daFunk::var("lnE");
      daFunk::Funk Ep = daFunk::var("Ep");
      daFunk::Funk halfBox_int = betaGamma*sqrt(E*E-mass*mass);
      daFunk::Funk halfBox_bound = betaGamma*sqrt(Ep*Ep-mass*mass);
      daFunk::Funk integrand = dNdE/(2*halfBox_int);
      return integrand->gsl_integration("E", Ep*gamma-halfBox_bound, Ep*gamma+halfBox_bound)
        ->set_epsabs(0)->set_limit(100)->set_epsrel(1e-3)->set_use_log_fallback(true)->set("Ep", daFunk::var("E"));
      //
      // Note: integration over lnE causes problems in the WIMP example (3) as the singularity is dropped.
      // return (integrand*E)->set("E", exp(lnE))->gsl_integration("lnE", log(Ep*gamma-halfBox_bound), log(Ep*gamma+halfBox_bound))
      //  ->set_epsabs(0)->set_epsrel(1e-3)->set("Ep", daFunk::var("E"));
    }


    /*! \brief Helper function returning yield from
     *         a given DM process.
     */
    daFunk::Funk getYield(const str& yield, const bool is_annihilation, const str& DMid, const str& DMbarid,
      TH_ProcessCatalog catalog, SimYieldTable table, double line_width, stringFunkMap cascadeMC_spectra)
    {
      using DarkBit_utils::gamma3bdy_limits;

      // Make sure that the ProcessCatalog process matches the is_annihilation flag.
      const TH_Process* p = (is_annihilation ? catalog.find(DMid, DMbarid) : catalog.find(DMid));
      if (p == NULL) DarkBit_error().raise(LOCAL_INFO, "Process does not match type indicated by is_annihilation flag.");

      // Get particle mass from process catalog
      const double mass = catalog.getParticleProperty(DMid).mass;
      const double Ecm(is_annihilation ? 2*mass : mass);

      // Get annihilation or decay process from process catalog and set up yield vector
      TH_Process process(is_annihilation ? catalog.getProcess(DMid, DMbarid) : catalog.getProcess(DMid));
      daFunk::Funk Yield(is_annihilation ? daFunk::zero("E", "v") : daFunk::zero("E"));

      // Adding two-body channels
      for (std::vector<TH_Channel>::iterator it = process.channelList.begin();
          it != process.channelList.end(); ++it)
      {
        bool added = false;  // If spectrum is not available from any source

        // Here only take care of two-body final states
        if (it->nFinalStates != 2) continue;

        // Get final state masses
        double m0 = catalog.getParticleProperty(it->finalStateIDs[0]).mass;
        double m1 = catalog.getParticleProperty(it->finalStateIDs[1]).mass;

        // Ignore channels that are kinematically closed for v=0
        if ( m0 + m1 > Ecm ) continue;

        // Ignore channels with 0 BR in v=0 limit (if "v" is a variable of genRate, i.e. not a decay).
        if (it->genRate->hasArg("v") && it->genRate->bind("v")->eval(0.) <= 0.0) continue;
        else if ( !(it->genRate->hasArgs()) && it->genRate->bind()->eval() <=0.0) continue;

        double E0 = 0.5*(Ecm*Ecm+m0*m0-m1*m1)/Ecm;
        double E1 = Ecm-E0;

        // Check whether two-body hard process final state is in SimYield table
        if ( table.hasChannel(it->finalStateIDs[0], it->finalStateIDs[1], yield) )
        {
          Yield = Yield +
            it->genRate*(table)(
                it->finalStateIDs[0], it->finalStateIDs[1], yield, Ecm);
          added = true;
        }
        // Deal with composite final states
        else
        {
          daFunk::Funk spec0 = daFunk::zero("E");
          daFunk::Funk spec1 = daFunk::zero("E");
          added = true;

          // Final state particle one
          // Tabulated spectrum available?
          if ( table.hasChannel(it->finalStateIDs[0], yield) )
          {
            spec0 = (table)(it->finalStateIDs[0], yield)->set("Ecm",E0);
          }
          // Monochromatic line?
          else if ( it->finalStateIDs[0] == yield )
          {
            daFunk::Funk E = daFunk::var("E");
            spec0 = daFunk::delta("E",E0,E0*line_width);
          }
          // MC spectra available?
          else if ( cascadeMC_spectra.count(it->finalStateIDs[0]) )
          {
            double gamma0 = E0/m0;
            //std::cout << it->finalStateIDs[0] << " " << gamma0 << std::endl;
            spec0 = boost_dNdE(cascadeMC_spectra.at(it->finalStateIDs[0]), gamma0, 0.0);
          }
          else added = false;

          // Final state particle two
          if ( table.hasChannel(it->finalStateIDs[1], yield) )
          {
            spec1 = (table)(it->finalStateIDs[1], yield)->set("Ecm", E1);
          }
          else if ( it->finalStateIDs[1] == yield )
          {
            daFunk::Funk E = daFunk::var("E");
            spec1 = daFunk::delta("E",E1,E1*line_width);
          }
          else if ( cascadeMC_spectra.count(it->finalStateIDs[1]) )
          {
            double gamma1 = E1/m1;
            //std::cout << it->finalStateIDs[1] << " " << gamma1 << std::endl;
            spec1 = boost_dNdE(cascadeMC_spectra.at(it->finalStateIDs[1]), gamma1, 0.0);
          }
          else added = false;

          #ifdef DARKBIT_DEBUG
            std::cout << it->finalStateIDs[0] << " " << it->finalStateIDs[1] << std::endl;
            //std::cout << "gammas: " << gamma0 << ", " << gamma1 << std::endl;
            daFunk::Funk chnSpec = (daFunk::zero("v", "E")
              +  spec0
              +  spec1)-> set("v", 0.);
            auto x = daFunk::logspace(0, 3, 10);
            std::vector<double> y = chnSpec->bind("E")->vect(x);
            std::cout << it->finalStateIDs[0] << it->finalStateIDs[1] << ":\n";
            std::cout << "  E: [";
            for (std::vector<double>::iterator it2 = x.begin(); it2 != x.end(); it2++)
              std::cout << *it2 << ", ";
            std::cout << "]\n";
            std::cout << "  dNdE: [";
            for (std::vector<double>::iterator it2 = y.begin(); it2 != y.end(); it2++)
              std::cout << *it2 << ", ";
            std::cout << "]\n";
          #endif

          if (!added)
          {
            DarkBit_warning().raise(LOCAL_INFO, "DarkBit::getYield (with yield = " + yield + ") cannot "
              "find spectra for " + it->finalStateIDs[0] + " " + it->finalStateIDs[1]);
          }

          Yield = Yield + (spec0 + spec1) * it->genRate;
        }
      } // End adding two-body final states

      // Adding three-body final states
      //
      // NOTE:  Three body processes are added even if they are closed at v=0
      for (std::vector<TH_Channel>::iterator it = process.channelList.begin();
          it != process.channelList.end(); ++it)
      {
        bool added = true;

        // Here only take care of three-body final states
        if (it->nFinalStates != 3) continue;

        /*
        // Implement tabulated three-body final states
        // Keep this for future use
        if ( it->nFinalStates == 3
         and table->hasChannel(it->finalStateIDs[0], yield)
         and table->hasChannel(it->finalStateIDs[1], yield)
         and table->hasChannel(it->finalStateIDs[2], yield) )
        {
         daFunk::Funk dNdE1dE2 = it->genRate->set("v",0.);
         daFunk::Funk spec0 = (table)(it->finalStateIDs[0], yield);
         daFunk::Funk spec1 = (table)(it->finalStateIDs[1], yield);
         daFunk::Funk spec2 = (table)(it->finalStateIDs[2], yield);
         Yield = Yield + convspec(spec0, spec1, spec2, dNdE1dE2);
        }
        */

        if ( it->finalStateIDs[0] == yield )
        {
          if ( it->finalStateIDs[1] == yield or it->finalStateIDs[2] == yield)
          {
            DarkBit_warning().raise(LOCAL_INFO, "Second and/or third primary "+yield+" in three-body final states ignored.");
          }
          double m1 = catalog.getParticleProperty(it->finalStateIDs[1]).mass;
          double m2 = catalog.getParticleProperty(it->finalStateIDs[2]).mass;
          daFunk::Funk E1_low =  daFunk::func(gamma3bdy_limits<0>, daFunk::var("E"),
              mass, m1, m2);
          daFunk::Funk E1_high =  daFunk::func(gamma3bdy_limits<1>, daFunk::var("E"),
              mass, m1, m2);
          daFunk::Funk dsigmavde = it->genRate->gsl_integration(
              "E1", E1_low, E1_high);

          Yield = Yield + dsigmavde;
        }
        else added = false;

        if (!added)
        {
          DarkBit_warning().raise(LOCAL_INFO,
              "DarkBit::getYield ignoring final state "
              + it->finalStateIDs[0] + " " + it->finalStateIDs[1] + " " + it->finalStateIDs[2]);
        }
      }

      // Rescale the yield by the correct kinematic factor
      if (is_annihilation)
      {
        // If process involves non-self-conjugate DM then we need to add a factor of 1/2
        // to the final spectrum. This must be explicitly set in the process catalog.
        double k = (process.isSelfConj) ? 1. : 0.5;
        Yield = k*daFunk::ifelse(1e-6 - daFunk::var("v"), Yield/(mass*mass),
          daFunk::throwError("Spectrum currently only defined for v=0."));
      }
      else
      {
        Yield = Yield/mass;
      }

      return Yield;

    }

    /// \brief General routine to derive gamma-ray annihilation yield.
    /// This function returns
    ///   k*dN/dE*(sv)/mDM**2 (E, v)  [cm^3/s/GeV^3]
    /// the energy spectrum of photons times sigma*v/m^2, as function of energy (in GeV)
    /// and velocity (as a fraction of c), multiplied by k=1 for self-conjugate DM or k=1/2
    /// for non-self conjugate.  By default, only the v=0 component is calculated.
    void GA_AnnYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::GA_AnnYield_General;
      std::string DMid= *Dep::DarkMatter_ID;
      std::string DMbarid = *Dep::DarkMatterConj_ID;
      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      const double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");
      result = getYield("gamma", true, DMid, DMbarid, *Dep::TH_ProcessCatalog, *Dep::GA_SimYieldTable,
                        line_width, *Dep::cascadeMC_gammaSpectra);
    }

    /// \brief General routine to derive gamma-ray decay yield.
    /// This function returns
    ///   dN/dE*(Gamma)/mDM (E)  [1/s/GeV^2]
    /// the energy spectrum of photons times Gamma/m, as function of energy (in GeV).
    void GA_DecayYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::GA_DecayYield_General;
      std::string DMid = *Dep::DarkMatter_ID;
      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      const double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");
      result = getYield("gamma", false, DMid, "null", *Dep::TH_ProcessCatalog, *Dep::GA_SimYieldTable,
                        line_width, *Dep::cascadeMC_gammaSpectra);
    }

    /// \brief General routine to derive electron annihilation yield.
    /// This function returns
    /// k*dN/dE*(sv)/mDM**2 (E, v)  [cm^3/s/GeV^3]
    /// the energy spectrum of electrons times sigma*v/m^2, as function of energy (in GeV)
    /// and velocity (as a fraction of c), multiplied by k=1 for self-conjugate DM or k=1/2
    /// for non-self conjugate.  By default, only the v=0 component is calculated.
    void electron_AnnYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::electron_AnnYield_General;
      std::string DMid= *Dep::DarkMatter_ID;
      std::string DMbarid = *Dep::DarkMatterConj_ID;
      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      const double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");
      result = getYield("e-_1", true, DMid, DMbarid, *Dep::TH_ProcessCatalog, *Dep::electron_SimYieldTable,
                        line_width, *Dep::cascadeMC_electronSpectra);
    }

    /// \brief General routine to derive electron decay yield.
    /// This function returns
    ///   dN/dE*(Gamma)/mDM (E)  [1/s/GeV^2]
    /// the energy spectrum of electrons times Gamma/m, as function of energy (in GeV).
    void electron_DecayYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::electron_DecayYield_General;
      std::string DMid = *Dep::DarkMatter_ID;
      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      const double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");
      result = getYield("e-_1", false, DMid, "null", *Dep::TH_ProcessCatalog, *Dep::electron_SimYieldTable,
                        line_width, *Dep::cascadeMC_electronSpectra);
    }

    /// \brief General routine to derive positron annihilation yield.
    /// This function returns
    /// k*dN/dE*(sv)/mDM**2 (E, v)  [cm^3/s/GeV^3]
    /// the energy spectrum of positrons times sigma*v/m^2, as function of energy (in GeV)
    /// and velocity (as a fraction of c), multiplied by k=1 for self-conjugate DM or k=1/2
    /// for non-self conjugate.  By default, only the v=0 component is calculated.
    void positron_AnnYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::positron_AnnYield_General;
      std::string DMid= *Dep::DarkMatter_ID;
      std::string DMbarid = *Dep::DarkMatterConj_ID;
      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      const double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");
      result = getYield("e+_1", true, DMid, DMbarid, *Dep::TH_ProcessCatalog, *Dep::positron_SimYieldTable,
                        line_width, *Dep::cascadeMC_positronSpectra);
    }

    /// \brief General routine to derive positron decay yield.
    /// This function returns
    ///   dN/dE*(Gamma)/mDM (E)  [1/s/GeV^2]
    /// the energy spectrum of positrons times Gamma/m, as function of energy (in GeV).
    void positron_DecayYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::positron_DecayYield_General;
      std::string DMid = *Dep::DarkMatter_ID;
      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      const double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");
      result = getYield("e+_1", false, DMid, "null", *Dep::TH_ProcessCatalog, *Dep::positron_SimYieldTable,
                        line_width, *Dep::cascadeMC_positronSpectra);
    }

    /// \brief General routine to derive antiproton annihilation yield.
    /// This function returns
    /// k*dN/dE*(sv)/mDM**2 (E, v)  [cm^3/s/GeV^3]
    /// the energy spectrum of antiprotons times sigma*v/m^2, as function of energy (in GeV)
    /// and velocity (as a fraction of c), multiplied by k=1 for self-conjugate DM or k=1/2
    /// for non-self conjugate.  By default, only the v=0 component is calculated.
    void antiproton_AnnYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::antiproton_AnnYield_General;
      std::string DMid= *Dep::DarkMatter_ID;
      std::string DMbarid = *Dep::DarkMatterConj_ID;
      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      const double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");
      result = getYield("pbar", true, DMid, DMbarid, *Dep::TH_ProcessCatalog, *Dep::antiproton_SimYieldTable,
                        line_width, *Dep::cascadeMC_antiprotonSpectra);
    }

    /// \brief General routine to derive antiproton decay yield.
    /// This function returns
    ///   dN/dE*(Gamma)/mDM (E)  [1/s/GeV^2]
    /// the energy spectrum of antiprotons times Gamma/m, as function of energy (in GeV).
    void antiproton_DecayYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::antiproton_DecayYield_General;
      std::string DMid = *Dep::DarkMatter_ID;
      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      const double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");
      result = getYield("pbar", false, DMid, "null", *Dep::TH_ProcessCatalog, *Dep::antiproton_SimYieldTable,
                        line_width, *Dep::cascadeMC_antiprotonSpectra);
    }

    /// \brief General routine to derive antideuteron annihilation yield.
    /// This function returns
    /// k*dN/dE*(sv)/mDM**2 (E, v)  [cm^3/s/GeV^3]
    /// the energy spectrum of antideuterons times sigma*v/m^2, as function of energy (in GeV)
    /// and velocity (as a fraction of c), multiplied by k=1 for self-conjugate DM or k=1/2
    /// for non-self conjugate.  By default, only the v=0 component is calculated.
    void antideuteron_AnnYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::antideuteron_AnnYield_General;
      std::string DMid= *Dep::DarkMatter_ID;
      std::string DMbarid = *Dep::DarkMatterConj_ID;
      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      const double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");
      result = getYield("Dbar", true, DMid, DMbarid, *Dep::TH_ProcessCatalog, *Dep::antideuteron_SimYieldTable,
                        line_width, *Dep::cascadeMC_antideuteronSpectra);
    }

    /// \brief General routine to derive antideuteron decay yield.
    /// This function returns
    ///   dN/dE*(Gamma)/mDM (E)  [1/s/GeV^2]
    /// the energy spectrum of antideuterons times Gamma/m, as function of energy (in GeV).
    void antideuteron_DecayYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::antideuteron_DecayYield_General;
      std::string DMid = *Dep::DarkMatter_ID;
      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      const double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");
      result = getYield("Dbar", false, DMid, "null", *Dep::TH_ProcessCatalog, *Dep::antideuteron_SimYieldTable,
                        line_width, *Dep::cascadeMC_antideuteronSpectra);
    }


    // SimYields =======================================================


    /// Combined SimYieldTable containing final yields of all stable particles
    void Combine_SimYields(SimYieldTable& result)
    {
      using namespace Pipes::Combine_SimYields;
      static bool initialized = false;
      if ( not initialized )
      {
        if (Downstream::neededFor("cascadeMC_gammaSpectra")) Dep::GA_SimYieldTable->donateChannels(result);
        if (Downstream::neededFor("cascadeMC_electronSpectra")) Dep::positron_SimYieldTable->donateChannels(result);
        if (Downstream::neededFor("cascadeMC_positronSpectra")) Dep::electron_SimYieldTable->donateChannels(result);
        if (Downstream::neededFor("cascadeMC_antiprotonSpectra")) Dep::antiproton_SimYieldTable->donateChannels(result);
        if (Downstream::neededFor("cascadeMC_antideuteronSpectra")) Dep::antideuteron_SimYieldTable->donateChannels(result);
        initialized = true;
      }
    }

    /// Gamma-ray SimYieldTable based on DarkSUSY5 tabulated results. (DS6 below)
    void GA_SimYieldTable_DS5(SimYieldTable& result)
    {
      using namespace Pipes::GA_SimYieldTable_DS5;

      static bool initialized = false;
      if ( not initialized )
      {
        int flag = 0;      // some flag
        int yieldk = 152;  // gamma ray yield

        using DarkBit_utils::str_flav_to_mass;

        double mDM_min, mDM_max;
        /// Option allow_yield_extrapolation<bool>: Spectra extrapolated for masses beyond Pythia results (default false)
        bool allow_yield_extrapolation = runOptions->getValueOrDef(false, "allow_yield_extrapolation");
        if ( allow_yield_extrapolation )
        {
          mDM_min = 0.0; // in this case, the minimally allowed dark matter mass will later be set to be the mass of the final state particle,
                         // with an additional factor 0.99 for the case of Z, W or t final states (following DarkSUSY)
          mDM_max = 1.0e6;
        }
        else
        {
          mDM_min = 10.0; // minimal dark matter mass simulated in DarkSUSY.
          mDM_max = 5000.; // maximal dark matter mass simulated in DarkSUSY.
        }

        auto add_channel = [&](int ch, str P1, str P2, str FINAL, double EcmMin, double EcmMax)
        {
          daFunk::Funk dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("mwimp"),
           daFunk::var("Ekin"), ch, yieldk, flag)->set("mwimp", daFunk::var("Ecm")/2);
          result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax, runOptions);
        };

        // The following routine adds an annihilation channel, for which the yields are extrapolated below Ecm_ToScale
        // using the approximation that x*dN/dx is a constant function of the dark matter mass.
        auto add_channel_with_scaling = [&](int ch, str P1, str P2, str FINAL, double EcmMin, double EcmMax, double Ecm_ToScale)
        {
          daFunk::Funk Ecm_ToUse = fmax(Ecm_ToScale, daFunk::var("Ecm"));
          daFunk::Funk ScalingFactor = Ecm_ToUse/daFunk::var("Ecm");
          daFunk::Funk dNdE = ScalingFactor * daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("mwimp"),
           ScalingFactor * daFunk::var("Ekin"), ch, yieldk, flag)->set("mwimp", Ecm_ToUse/2);
          result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax, runOptions);
        };

        // Specifies also center of mass energy range
        add_channel(12, "Z0", "Z0", "gamma", 2*90.288, 2*mDM_max);
        add_channel(13, "W+", "W-", "gamma", 2*79.4475, 2*mDM_max);
        add_channel(14, "nu_e", "nubar_e", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
        add_channel(15, "e+", "e-", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
        add_channel(16, "nu_mu", "nubar_mu", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
        add_channel(17, "mu+", "mu-", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);
        add_channel(18, "nu_tau", "nubar_tau", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
        add_channel(19, "tau+", "tau-", "gamma", 2*std::max(mDM_min, 1.7841), 2*mDM_max);
        //add_channel(20, "u", "ubar", "gamma", 0., 2*mDM_max);  // Zero
        add_channel(22, "u", "ubar", "gamma", 2*std::max(mDM_min, 1.35), 2*mDM_max);  // approx by cc
        //add_channel(21, "d", "dbar", "gamma", 0., 2*mDM_max);  // Zero
        add_channel(22, "d", "dbar", "gamma", 2*std::max(mDM_min, 1.35), 2*mDM_max);  // approx by cc
        add_channel(22, "c", "cbar", "gamma", 2*std::max(mDM_min, 1.35), 2*mDM_max);
        //add_channel(23, "s", "sbar", "gamma", 0., 2*mDM_max);  // Zero
        add_channel(22, "s", "sbar", "gamma", 2*std::max(mDM_min, 1.35), 2*mDM_max);  // approx by cc
        add_channel_with_scaling(24, "t", "tbar", "gamma", 2*160.0, 2*mDM_max, 2*173.3);
        add_channel(25, "b", "bbar", "gamma", 2*std::max(mDM_min, 5.0), 2*mDM_max);
        add_channel(26, "g", "g", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);

        // Add approximations for single-particle cases.
        // TODO: Replace by boosted rest frame spectrum Z0
        daFunk::Funk dNdE;
        dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("Ecm"), daFunk::var("Ekin"), 12, yieldk, flag);
        result.addChannel(dNdE/2, "Z0", "gamma", 90.288, mDM_max, runOptions);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("Ecm"), daFunk::var("Ekin"), 13, yieldk, flag);
        result.addChannel(dNdE/2, "W+", "gamma", 79.4475, mDM_max, runOptions);
        result.addChannel(dNdE/2, "W-", "gamma", 79.4475, mDM_max, runOptions);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("Ecm"), daFunk::var("Ekin"), 15, yieldk, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("e+"), "gamma", std::max(mDM_min, 0.0), mDM_max, runOptions);
        result.addChannel(dNdE/2, str_flav_to_mass("e-"), "gamma", std::max(mDM_min, 0.0), mDM_max, runOptions);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("Ecm"), daFunk::var("Ekin"), 17, yieldk, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("mu+"), "gamma", std::max(mDM_min, 0.0), mDM_max, runOptions);
        result.addChannel(dNdE/2, str_flav_to_mass("mu-"), "gamma", std::max(mDM_min, 0.0), mDM_max, runOptions);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("Ecm"), daFunk::var("Ekin"), 19, yieldk, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("tau+"), "gamma", std::max(mDM_min, 1.7841), mDM_max, runOptions);
        result.addChannel(dNdE/2, str_flav_to_mass("tau-"), "gamma", std::max(mDM_min, 1.7841), mDM_max, runOptions);

        double Ecm_ToScale_top = 173.3;
        daFunk::Funk Ecm_ToUse_top = fmax(Ecm_ToScale_top, daFunk::var("Ecm"));
        daFunk::Funk ScalingFactor_top = Ecm_ToUse_top/daFunk::var("Ecm");
        dNdE = ScalingFactor_top * daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), Ecm_ToUse_top,
         ScalingFactor_top * daFunk::var("Ekin"), 24, yieldk, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("t"), "gamma", 160.0, mDM_max, runOptions);
        result.addChannel(dNdE/2, str_flav_to_mass("tbar"), "gamma", 160.0, mDM_max, runOptions);

        // add channels with "mixed final states", i.e. final state particles with (potentially) different masses
        daFunk::Funk Ecm = daFunk::var("Ecm");
        auto add_channel_mixedmasses = [&](int ch1, int ch2, str P1, str P2, str FINAL, double m1, double m2, double EcmMin, double EcmMax)
        {
          daFunk::Funk dNdE_1 = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("E1"),
           daFunk::var("Ekin"), ch1, yieldk, flag)->set("E1", Ecm/2 + (m1*m1 - m2*m2)/(2*Ecm));
          daFunk::Funk dNdE_2 = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("E2"),
           daFunk::var("Ekin"), ch2, yieldk, flag)->set("E2", Ecm/2 + (m2*m2 - m1*m1)/(2*Ecm));
          result.addChannel(0.5*(dNdE_1 + dNdE_2), str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax, runOptions);
        };

        // - In the following: approximate spectra from u,d,s (20,21,23) by spectrum from c (22).
        // - The numerical values for EcmMin and EcmMax are obtained from applying the corresponding two-body kinematics
        //   to the minimally/maximally allowed center-of-mass energies. Hence, EcmMin depends on the flag allow_yield_extrapolation.
        //   If it is false, the assigmnents of Ecm_min assume the value mDM_min = 10.0.

        add_channel_mixedmasses(22, 22, "u", "dbar", "gamma", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
        add_channel_mixedmasses(22, 22, "d", "ubar", "gamma", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
        add_channel_mixedmasses(22, 22, "u", "sbar", "gamma", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
        add_channel_mixedmasses(22, 22, "s", "ubar", "gamma", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
        add_channel_mixedmasses(22, 25, "u", "bbar", "gamma", 0.0, 5.0, (allow_yield_extrapolation ? 6.530 : 21.181), 2*mDM_max);
        add_channel_mixedmasses(25, 22, "b", "ubar", "gamma", 5.0, 0.0, (allow_yield_extrapolation ? 6.530 : 21.181), 2*mDM_max);

        add_channel_mixedmasses(22, 22, "c", "dbar", "gamma", 1.35, 0.0, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
        add_channel_mixedmasses(22, 22, "d", "cbar", "gamma", 0.0, 1.35, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
        add_channel_mixedmasses(22, 22, "c", "sbar", "gamma", 1.35, 0.0, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
        add_channel_mixedmasses(22, 22, "s", "cbar", "gamma", 0.0, 1.35, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
        add_channel_mixedmasses(22, 25, "c", "bbar", "gamma", 1.35, 5.0, (allow_yield_extrapolation ? 6.35 : 21.099), 2*mDM_max);
        add_channel_mixedmasses(25, 22, "b", "cbar", "gamma", 5.0, 1.35, (allow_yield_extrapolation ? 6.35 : 21.099), 2*mDM_max);

        add_channel_mixedmasses(24, 22, "t", "dbar", "gamma", 175.0, 0.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
        add_channel_mixedmasses(22, 24, "d", "tbar", "gamma", 0.0, 175.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
        add_channel_mixedmasses(24, 22, "t", "sbar", "gamma", 175.0, 0.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
        add_channel_mixedmasses(22, 24, "s", "tbar", "gamma", 0.0, 175.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
        add_channel_mixedmasses(24, 25, "t", "bbar", "gamma", 175.0, 5.0, (allow_yield_extrapolation ? 180.0 : 185.214), 2*mDM_max);
        add_channel_mixedmasses(25, 24, "b", "tbar", "gamma", 5.0, 175.0, (allow_yield_extrapolation ? 180.0 : 185.214), 2*mDM_max);

        initialized = true;
      }
    }

    /// Construct a SimYieldTable based on DarkSUSY6 tabulated results.
    SimYieldTable SimYieldTable_DarkSUSY(const str& yield, const bool allow_yield_extrapolation, double(*dsanyield)(double&,double&,int&,char*,int&,int&,int&), safe_ptr<Options> runOptions)
    {
      using DarkBit_utils::str_flav_to_mass;

      const int flag = 0;            // some flag
      const int diff=1;              // differential yields (=1)
      char*hel =  (char *)"0";       // helicity

      int yieldpdg;                  // PDG code of final state
      double mDM_min, mDM_max;       // Boundaries of tabulation
      SimYieldTable result;          // The table itself

      // Determine PDG code of the particle for which the yield has been requested
      if (yield == "gamma")
        yieldpdg =  22;
      else if (yield == "e+_1")
        yieldpdg = -11;
      else if (yield == "pbar")
        yieldpdg = -2212;
      else if (yield == "Dbar")
        yieldpdg = -1000010020;
      else if (yield == "pi0")
        yieldpdg = 111;
      else if (yield == "nu_e + nu_ebar")
        yieldpdg = 12;
      else if (yield == "nu_mu + nu_mubar")
        yieldpdg = 14;
      else if (yield == "nu_tau + nu_taubar")
        yieldpdg = 16;
      else
        DarkBit_error().raise(LOCAL_INFO, "SimYieldTable_DarkSUSY called with unrecognised final state " + yield);

      if ( allow_yield_extrapolation )
      {
        mDM_min = 0.0; // in this case, the minimally allowed dark matter mass will later be set to be the mass of the final state particle,
                       // with an additional factor 0.99 for the case of Z, W or t final states (following DarkSUSY)
        mDM_max = 1.0e6;
      }
      else
      {
        mDM_min = 3.0; // minimal dark matter mass simulated in DarkSUSY6.
        mDM_max = 20000.; // maximal dark matter mass simulated in DarkSUSY6.
      }

      auto add_channel = [&](int pdg, str p1, str p2, double EcmMin, double EcmMax)
      {
        daFunk::Funk dNdE = daFunk::func_fromThreadsafe(dsanyield, daFunk::var("mwimp"),
         daFunk::var("Ekin"), pdg, hel, yieldpdg, diff, flag)->set("mwimp", daFunk::var("Ecm")/2);
        result.addChannel(dNdE, str_flav_to_mass(p1), str_flav_to_mass(p2), yield, EcmMin, EcmMax, runOptions);
      };

      // The following routine adds an annihilation/decay channel, for which the yields are extrapolated below Ecm_ToScale
      // using the approximation that x*dN/dx is a constant function of the dark matter mass.
      auto add_channel_with_scaling = [&](int pdg, str P1, str P2, double EcmMin, double EcmMax, double Ecm_ToScale)
      {
        daFunk::Funk Ecm_ToUse = fmax(Ecm_ToScale, daFunk::var("Ecm"));
        daFunk::Funk ScalingFactor = Ecm_ToUse/daFunk::var("Ecm");
        daFunk::Funk dNdE = ScalingFactor * daFunk::func_fromThreadsafe(dsanyield, daFunk::var("mwimp"),
         ScalingFactor * daFunk::var("Ekin"), pdg, hel, yieldpdg, diff, flag)->set("mwimp", Ecm_ToUse/2);
        result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), yield, EcmMin, EcmMax, runOptions);
      };

      // specifies also center of mass energy range
      add_channel(23, "Z0", "Z0", 2*90.288, 2*mDM_max);
      add_channel(24, "W+", "W-", 2*79.4475, 2*mDM_max);
      add_channel(12, "nu_e", "nubar_e", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
      add_channel(11, "e+", "e-", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
      add_channel(14, "nu_mu", "nubar_mu", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
      add_channel(13, "mu+", "mu-", 2*std::max(mDM_min, 0.0), 2*mDM_max);
      add_channel(16, "nu_tau", "nubar_tau", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
      add_channel(15, "tau+", "tau-", 2*std::max(mDM_min, 1.7841), 2*mDM_max);
      //add_channel(2, "u", "ubar", 0., 2*mDM_max);  // Zero
      add_channel(2, "u", "ubar", 2*std::max(mDM_min, 1.35), 2*mDM_max);  // approx by cc
      //add_channel(1, "d", "dbar", 0., 2*mDM_max);  // Zero
      add_channel(1, "d", "dbar", 2*std::max(mDM_min, 1.35), 2*mDM_max);  // approx by cc
      add_channel(4, "c", "cbar", 2*std::max(mDM_min, 1.35), 2*mDM_max);
      //add_channel(3, "s", "sbar", 0., 2*mDM_max);  // Zero
      add_channel(3, "s", "sbar", 2*std::max(mDM_min, 1.35), 2*mDM_max);  // approx by cc
      add_channel_with_scaling(6, "t", "tbar", 2*160.0, 2*mDM_max, 2*173.3);
      add_channel(5, "b", "bbar", 2*std::max(mDM_min, 5.0), 2*mDM_max);
      add_channel(21, "g", "g", 2*std::max(mDM_min, 0.0), 2*mDM_max);

      // Add approximations for single-particle cases.
      // TODO: Replace by boosted rest frame spectrum Z0
      daFunk::Funk dNdE;
      dNdE = daFunk::func_fromThreadsafe(dsanyield, daFunk::var("Ecm"), daFunk::var("Ekin"), 23, hel,yieldpdg, diff,flag);
      result.addChannel(dNdE/2, "Z0", yield, 90.288, mDM_max, runOptions);
      dNdE = daFunk::func_fromThreadsafe(dsanyield, daFunk::var("Ecm"), daFunk::var("Ekin"), 24, hel,yieldpdg, diff, flag);
      result.addChannel(dNdE/2, "W+", yield, 79.4475, mDM_max, runOptions);
      result.addChannel(dNdE/2, "W-", yield, 79.4475, mDM_max, runOptions);
      dNdE = daFunk::func_fromThreadsafe(dsanyield, daFunk::var("Ecm"), daFunk::var("Ekin"), 11, hel, yieldpdg, diff, flag);
      result.addChannel(dNdE/2, str_flav_to_mass("e+"), yield, std::max(mDM_min, 0.0), mDM_max, runOptions);
      result.addChannel(dNdE/2, str_flav_to_mass("e-"), yield, std::max(mDM_min, 0.0), mDM_max, runOptions);
      dNdE = daFunk::func_fromThreadsafe(dsanyield, daFunk::var("Ecm"), daFunk::var("Ekin"), 13, hel, yieldpdg, diff, flag);
      result.addChannel(dNdE/2, str_flav_to_mass("mu+"), yield, std::max(mDM_min, 0.0), mDM_max, runOptions);
      result.addChannel(dNdE/2, str_flav_to_mass("mu-"), yield, std::max(mDM_min, 0.0), mDM_max, runOptions);
      dNdE = daFunk::func_fromThreadsafe(dsanyield, daFunk::var("Ecm"), daFunk::var("Ekin"), 15, hel, yieldpdg, diff, flag);
      result.addChannel(dNdE/2, str_flav_to_mass("tau+"), yield, std::max(mDM_min, 1.7841), mDM_max, runOptions);
      result.addChannel(dNdE/2, str_flav_to_mass("tau-"), yield, std::max(mDM_min, 1.7841), mDM_max, runOptions);

      double Ecm_ToScale_top = 173.3;
      daFunk::Funk Ecm_ToUse_top = fmax(Ecm_ToScale_top, daFunk::var("Ecm"));
      daFunk::Funk ScalingFactor_top = Ecm_ToUse_top/daFunk::var("Ecm");
      dNdE = ScalingFactor_top * daFunk::func_fromThreadsafe(dsanyield, Ecm_ToUse_top,
       ScalingFactor_top * daFunk::var("Ekin"), 6, hel, yieldpdg, diff, flag);
      result.addChannel(dNdE/2, str_flav_to_mass("t"), yield, 160.0, mDM_max, runOptions);
      result.addChannel(dNdE/2, str_flav_to_mass("tbar"), yield, 160.0, mDM_max, runOptions);

      // Add channels with "mixed final states", i.e. final state particles with (potentially) different masses
      daFunk::Funk Ecm = daFunk::var("Ecm");
      auto add_channel_mixedmasses = [&](int pdg1, int pdg2, str P1, str P2, double m1, double m2, double EcmMin, double EcmMax)
      {
        daFunk::Funk dNdE_1 = daFunk::func_fromThreadsafe(dsanyield, daFunk::var("E1"),
         daFunk::var("Ekin"), pdg1, hel, yieldpdg, diff, flag)->set("E1", Ecm/2 + (m1*m1 - m2*m2)/(2*Ecm));
        daFunk::Funk dNdE_2 = daFunk::func_fromThreadsafe(dsanyield, daFunk::var("E2"),
         daFunk::var("Ekin"), pdg2, hel, yieldpdg, diff, flag)->set("E2", Ecm/2 + (m2*m2 - m1*m1)/(2*Ecm));
        result.addChannel(0.5*(dNdE_1 + dNdE_2), str_flav_to_mass(P1), str_flav_to_mass(P2), yield, EcmMin, EcmMax, runOptions);
      };

      // - The numerical values for EcmMin and EcmMax are obtained from applying the corresponding two-body kinematics
      //   to the minimally/maximally allowed center-of-mass energies. Hence, EcmMin depends on the flag allow_yield_extrapolation.

      add_channel_mixedmasses(2, -1, "u", "dbar", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
      add_channel_mixedmasses(1, -2, "d", "ubar", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
      add_channel_mixedmasses(2, -3, "u", "sbar", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
      add_channel_mixedmasses(3, -2, "s", "ubar", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
      add_channel_mixedmasses(2, -5, "u", "bbar", 0.0, 5.0, (allow_yield_extrapolation ? 6.530 : 21.181), 2*mDM_max);
      add_channel_mixedmasses(5, -2, "b", "ubar", 5.0, 0.0, (allow_yield_extrapolation ? 6.530 : 21.181), 2*mDM_max);

      add_channel_mixedmasses(4, -1, "c", "dbar", 1.35, 0.0, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
      add_channel_mixedmasses(1, -4, "d", "cbar", 0.0, 1.35, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
      add_channel_mixedmasses(4, -3, "c", "sbar", 1.35, 0.0, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
      add_channel_mixedmasses(3, -4, "s", "cbar", 0.0, 1.35, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
      add_channel_mixedmasses(4, -5, "c", "bbar", 1.35, 5.0, (allow_yield_extrapolation ? 6.35 : 21.099), 2*mDM_max);
      add_channel_mixedmasses(5, -4, "b", "cbar", 5.0, 1.35, (allow_yield_extrapolation ? 6.35 : 21.099), 2*mDM_max);

      add_channel_mixedmasses(6, -1, "t", "dbar", 175.0, 0.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
      add_channel_mixedmasses(1, -6, "d", "tbar", 0.0, 175.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
      add_channel_mixedmasses(6, -3, "t", "sbar", 175.0, 0.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
      add_channel_mixedmasses(3, -6, "s", "tbar", 0.0, 175.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
      add_channel_mixedmasses(6, -5, "t", "bbar", 175.0, 5.0, (allow_yield_extrapolation ? 180.0 : 185.214), 2*mDM_max);
      add_channel_mixedmasses(5, -6, "b", "tbar", 5.0, 175.0, (allow_yield_extrapolation ? 180.0 : 185.214), 2*mDM_max);

      return result;
    }

    /// Gamma-ray SimYieldTable based on DarkSUSY6 tabulated results.
    void GA_SimYieldTable_DarkSUSY(SimYieldTable& result)
    {
      using namespace Pipes::GA_SimYieldTable_DarkSUSY;

      static bool initialized = false;
      if ( not initialized )
      {
        /// Option allow_yield_extrapolation<bool>: Spectra extrapolated for masses beyond Pythia results (default false)
        bool allow_yield_extrapolation = runOptions->getValueOrDef(false, "allow_yield_extrapolation");
        result = SimYieldTable_DarkSUSY("gamma", allow_yield_extrapolation, BEreq::dsanyield_sim.pointer(), runOptions);
        initialized = true;
      }
    }

    /// Positron SimYieldTable based on DarkSUSY6 tabulated results.
    void positron_SimYieldTable_DarkSUSY(SimYieldTable& result)
    {
      using namespace Pipes::positron_SimYieldTable_DarkSUSY;

      static bool initialized = false;
      if ( not initialized )
      {
        /// Option allow_yield_extrapolation<bool>: Spectra extrapolated for masses beyond Pythia results (default false)
        bool allow_yield_extrapolation = runOptions->getValueOrDef(false, "allow_yield_extrapolation");
        result = SimYieldTable_DarkSUSY("e+_1", allow_yield_extrapolation, BEreq::dsanyield_sim.pointer(), runOptions);
        initialized = true;
      }
    }

    /// Anti-proton SimYieldTable based on DarkSUSY6 tabulated results.
    void antiproton_SimYieldTable_DarkSUSY(SimYieldTable& result)
    {
      using namespace Pipes::antiproton_SimYieldTable_DarkSUSY;

      static bool initialized = false;
      if ( not initialized )
      {
        /// Option allow_yield_extrapolation<bool>: Spectra extrapolated for masses beyond Pythia results (default false)
        bool allow_yield_extrapolation = runOptions->getValueOrDef(false, "allow_yield_extrapolation");
        result = SimYieldTable_DarkSUSY("pbar", allow_yield_extrapolation, BEreq::dsanyield_sim.pointer(), runOptions);
        initialized = true;
      }
    }

    /// Anti-deuteron SimYieldTable based on DarkSUSY6 tabulated results.
    void antideuteron_SimYieldTable_DarkSUSY(SimYieldTable& result)
    {
      using namespace Pipes::antideuteron_SimYieldTable_DarkSUSY;

      static bool initialized = false;
      if ( not initialized )
      {
        /// Option allow_yield_extrapolation<bool>: Spectra extrapolated for masses beyond Pythia results (default false)
        bool allow_yield_extrapolation = runOptions->getValueOrDef(false, "allow_yield_extrapolation");
        result = SimYieldTable_DarkSUSY("Dbar", allow_yield_extrapolation, BEreq::dsanyield_sim.pointer(), runOptions);
        initialized = true;
      }
    }

    /// Gamma-ray SimYieldTable based on MicrOmegas tabulated results.
    void GA_SimYieldTable_MicrOmegas(SimYieldTable& result)
    {
      using namespace Pipes::GA_SimYieldTable_MicrOmegas;
      using DarkBit_utils::str_flav_to_mass;

      static bool initialized = false;
      const int outN = 0;  // gamma

      if ( not initialized )
      {
        double mDM_max;
        if ( runOptions->getValueOrDef(false, "allow_yield_extrapolation") )
        {
          mDM_max = 1.0e6;
        }
        else
        {
          mDM_max = 5000.; // maximal dark matter mass simulated in micromegas.
        }

        auto add_channel = [&](int inP, str P1, str P2, str FINAL, double EcmMin, double EcmMax)
        {
          daFunk::Funk dNdE = daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("Ecm"), daFunk::var("E"), inP, outN)/daFunk::var("E");
          result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax, runOptions);  // specifies also center of mass energy range
        };

        // The following routine adds an annihilation channel, for which the yields are extrapolated below Ecm_ToScale
        // using the approximation that x*dN/dx is a constant function of the dark matter mass.
        auto add_channel_with_scaling = [&](int inP, str P1, str P2, str FINAL, double EcmMin, double EcmMax, double Ecm_ToScale)
        {
          daFunk::Funk Ecm_ToUse = fmax(Ecm_ToScale, daFunk::var("Ecm"));
          daFunk::Funk ScalingFactor = Ecm_ToUse/daFunk::var("Ecm");
          daFunk::Funk dNdE = ScalingFactor * daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), Ecm_ToUse,
           ScalingFactor * daFunk::var("E"), inP, outN)/(ScalingFactor * daFunk::var("E"));
          result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax, runOptions);
        };

        add_channel(0, "g", "g", "gamma", 2*2., 2*mDM_max);
        add_channel(1, "d", "dbar", "gamma", 2*2., 2*mDM_max);
        add_channel(2, "u", "ubar", "gamma", 2*2., 2*mDM_max);
        add_channel(3, "s", "sbar", "gamma", 2*2., 2*mDM_max);
        add_channel(4, "c", "cbar", "gamma", 2*2., 2*mDM_max);
        add_channel(5, "b", "bbar", "gamma", 2*5., 2*mDM_max);
        add_channel_with_scaling(6, "t", "tbar", "gamma", 2*160.0, 2*mDM_max, 2.0*176.0);
        add_channel(7, "e+", "e-", "gamma", 2*2., 2*mDM_max);
        add_channel(8, "mu+", "mu-", "gamma", 2*2., 2*mDM_max);
        add_channel(9, "tau+", "tau-", "gamma", 2*2., 2*mDM_max);
        add_channel(10, "Z0", "Z0", "gamma", 2*90.288, 2*mDM_max);
        add_channel(13, "W+", "W-", "gamma", 2*79.497, 2*mDM_max);

        result.addChannel(daFunk::zero("Ecm", "E"), "nu_e", "nubar_e", "gamma", 2*2., 2*mDM_max, runOptions);
        result.addChannel(daFunk::zero("Ecm", "E"), "nu_mu", "nubar_mu", "gamma", 2*2., 2*mDM_max, runOptions);
        result.addChannel(daFunk::zero("Ecm", "E"), "nu_tau", "nubar_tau", "gamma", 2*2., 2*mDM_max, runOptions);

        // Add approximations for single-particle cases.
        daFunk::Funk dNdE;
        dNdE = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("_Ecm"), daFunk::var("E"), 8, outN)
               /daFunk::var("E"))->set("_Ecm", daFunk::var("Ecm")*2);
        result.addChannel(dNdE/2, str_flav_to_mass("mu+"), "gamma", 2., mDM_max, runOptions);
        result.addChannel(dNdE/2, str_flav_to_mass("mu-"), "gamma", 2., mDM_max, runOptions);
        dNdE = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("_Ecm"), daFunk::var("E"), 9, outN)
               /daFunk::var("E"))->set("_Ecm", daFunk::var("Ecm")*2);
        result.addChannel(dNdE/2, str_flav_to_mass("tau+"), "gamma", 2., mDM_max, runOptions);
        result.addChannel(dNdE/2, str_flav_to_mass("tau-"), "gamma", 2., mDM_max, runOptions);
        dNdE = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("_Ecm"), daFunk::var("E"), 10, outN)
               /daFunk::var("E"))->set("_Ecm", daFunk::var("Ecm")*2);
        result.addChannel(dNdE/2, "Z0", "gamma", 90.288, mDM_max, runOptions);
        dNdE = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("_Ecm"), daFunk::var("E"), 13, outN)
               /daFunk::var("E"))->set("_Ecm", daFunk::var("Ecm")*2);
        result.addChannel(dNdE/2, "W+", "gamma", 79.497, mDM_max, runOptions);
        result.addChannel(dNdE/2, "W-", "gamma", 79.497, mDM_max, runOptions);

        // Add single particle lookup for t tbar to prevent them from being tagged as missing final states for cascades.
        double Ecm_ToScale_top = 176.0;
        daFunk::Funk Ecm_ToUse_top = fmax(Ecm_ToScale_top, daFunk::var("Ecm"));
        daFunk::Funk ScalingFactor_top = Ecm_ToUse_top/daFunk::var("Ecm");
        dNdE =  ScalingFactor_top * (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("_Ecm"), ScalingFactor_top * daFunk::var("E"), 6, outN)
               /(ScalingFactor_top * daFunk::var("E")))->set("_Ecm", Ecm_ToUse_top*2.0);
        result.addChannel(dNdE/2, str_flav_to_mass("t"),    "gamma", 160.0, mDM_max, runOptions);
        result.addChannel(dNdE/2, str_flav_to_mass("tbar"), "gamma", 160.0, mDM_max, runOptions);

        // Add channels with "mixed final states", i.e. final state particles with (potentially) different masses
        daFunk::Funk Ecm = daFunk::var("Ecm");
        auto add_channel_mixedmasses = [&](int inP1, int inP2, str P1, str P2, str FINAL, double m1, double m2, double EcmMin, double EcmMax)
        {
          daFunk::Funk dNdE_1 = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("Ecm1"),
           daFunk::var("E"), inP1, outN)->set("Ecm1", Ecm + (m1*m1 - m2*m2)/Ecm))/daFunk::var("E");
          daFunk::Funk dNdE_2 = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("Ecm2"),
           daFunk::var("E"), inP2, outN)->set("Ecm2", Ecm + (m2*m2 - m1*m1)/Ecm))/daFunk::var("E");
          result.addChannel(0.5*(dNdE_1 + dNdE_2), str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax, runOptions);
        };

        // - The numerical values for EcmMin and EcmMax are obtained from applying the corresponding two-body kinematics
        //   to the minimal/maximal center-of-mass energies allowed by the micromegas tables
        add_channel_mixedmasses(2, 1, "u", "dbar", "gamma", 0.0, 0.0, 2*2., 2*mDM_max);
        add_channel_mixedmasses(1, 2, "d", "ubar", "gamma", 0.0, 0.0, 2*2., 2*mDM_max);
        add_channel_mixedmasses(2, 3, "u", "sbar", "gamma", 0.0, 0.0, 2*2., 2*mDM_max);
        add_channel_mixedmasses(3, 2, "s", "ubar", "gamma", 0.0, 0.0, 2*2., 2*mDM_max);
        add_channel_mixedmasses(2, 5, "u", "bbar", "gamma", 0.0, 5.0, 7.386, 2*mDM_max);
        add_channel_mixedmasses(5, 2, "b", "ubar", "gamma", 5.0, 0.0, 7.386, 2*mDM_max);

        add_channel_mixedmasses(4, 1, "c", "dbar", "gamma", 1.35, 0.0, 4.413, 2*mDM_max);
        add_channel_mixedmasses(1, 4, "d", "cbar", "gamma", 0.0, 1.35, 4.413, 2*mDM_max);
        add_channel_mixedmasses(4, 3, "c", "sbar", "gamma", 1.35, 0.0, 4.413, 2*mDM_max);
        add_channel_mixedmasses(3, 4, "s", "cbar", "gamma", 0.0, 1.35, 4.413, 2*mDM_max);
        add_channel_mixedmasses(4, 5, "c", "bbar", "gamma", 1.35, 5.0, 7.214, 2*mDM_max);
        add_channel_mixedmasses(5, 4, "b", "cbar", "gamma", 5.0, 1.35, 7.214, 2*mDM_max);

        add_channel_mixedmasses(6, 1, "t", "dbar", "gamma", 176.0, 0.0, 178.011, 2*mDM_max);
        add_channel_mixedmasses(1, 6, "d", "tbar", "gamma", 0.0, 176.0, 178.011, 2*mDM_max);
        add_channel_mixedmasses(6, 3, "t", "sbar", "gamma", 176.0, 0.0, 178.011, 2*mDM_max);
        add_channel_mixedmasses(3, 6, "s", "tbar", "gamma", 0.0, 176.0, 178.011, 2*mDM_max);
        add_channel_mixedmasses(6, 5, "t", "bbar", "gamma", 176.0, 5.0, 181.0, 2*mDM_max);
        add_channel_mixedmasses(5, 6, "b", "tbar", "gamma", 5.0, 176.0, 181.0, 2*mDM_max);

        initialized = true;
      }
    }

    /// Positron SimYieldTable based on MicrOmegas tabulated results.
    void positron_SimYieldTable_MicrOmegas(SimYieldTable& /*result*/)
    {
      using namespace Pipes::positron_SimYieldTable_MicrOmegas;
      static bool initialized = false;

      if ( not initialized )
      {
        DarkBit_error().raise(LOCAL_INFO,
            "positron_SimYieldTable_MicrOmegas is not implemented yet.  Use e.g. positron_SimYieldTable_DarkSUSY instead.");
      }
    }

    SimYieldTable SimYieldTable_PPPC(const str& yield, bool allow_yield_extrapolation, double(*PPPC_yield)(double,double,std::string), safe_ptr<Options> runOptions)
    {
      using DarkBit_utils::str_flav_to_mass;

      SimYieldTable result;

      const double mDM_min = 5.0;
      const double mDM_max = 100000.0;

      auto add_channel = [&](const str& p1, const str& p2, const str& channel, double EcmMin, double EcmMax)
      {
        daFunk::Funk m = daFunk::var("m");
        daFunk::Funk x = daFunk::var("x");
        daFunk::Funk E = daFunk::var("Ekin");
        daFunk::Funk Ecm = daFunk::var("Ecm");

        daFunk::Funk dNdE = daFunk::func( PPPC_yield, daFunk::var("m"), daFunk::var("x"), channel);
        dNdE = dNdE->set("x", E/m);

        if (p2.size() > 0)
        {
          dNdE = dNdE->set("m",Ecm/2);
          result.addChannel(dNdE, str_flav_to_mass(p1), str_flav_to_mass(p2), yield, EcmMin, EcmMax, runOptions);
        }
        else
        {
          dNdE = dNdE->set("m",Ecm);
          result.addChannel(dNdE/2, str_flav_to_mass(p1), yield, EcmMin, EcmMax, runOptions);
        }
      };

      // The following routine adds an annihilation/decay channel, for which the yields are extrapolated below Ecm_ToScale
      // using the approximation that x*dN/dx is a constant function of the dark matter mass.
      auto add_channel_with_scaling = [&](const str& p1, const str& p2, const str& channel, double EcmMin, double EcmMax, double Ecm_ToScale)
      {
        daFunk::Funk m = daFunk::var("m");
        daFunk::Funk x = daFunk::var("x");
        daFunk::Funk E = daFunk::var("Ekin");

        daFunk::Funk Ecm_ToUse = fmax(Ecm_ToScale, daFunk::var("Ecm"));
        daFunk::Funk ScalingFactor = Ecm_ToUse/daFunk::var("Ecm");

        daFunk::Funk dNdE = daFunk::func( PPPC_yield, daFunk::var("m"), daFunk::var("x"), channel);
        dNdE = (ScalingFactor*dNdE)->set("x", E/m);

        if (p2.size() > 0)
        {
          dNdE = dNdE->set("m",Ecm_ToUse/2);
          result.addChannel(dNdE, str_flav_to_mass(p1), str_flav_to_mass(p2), yield, EcmMin, EcmMax, runOptions);
        }
        else
        {
          dNdE = dNdE->set("m",Ecm_ToUse);
          result.addChannel(dNdE/2, str_flav_to_mass(p1), yield, EcmMin, EcmMax, runOptions);
        }
      };

      add_channel("e+",   "e-",   "e",   2*std::max(mDM_min, 0.0), 2*mDM_max);
      add_channel("mu+",  "mu-",  "mu",  2*std::max(mDM_min, 0.0), 2*mDM_max);
      add_channel("tau+", "tau-", "tau", 2*std::max(mDM_min, 0.0), 2*mDM_max);

      add_channel("u", "ubar", "q", 2*std::max(mDM_min, 1.35), 2*mDM_max);  // u,d,s are treated as one species
      add_channel("d", "dbar", "q", 2*std::max(mDM_min, 1.35), 2*mDM_max);
      add_channel("s", "sbar", "q", 2*std::max(mDM_min, 1.35), 2*mDM_max);

      add_channel("c", "cbar", "c", 2*std::max(mDM_min, 1.35), 2*mDM_max);
      add_channel("b", "bbar", "b", 2*std::max(mDM_min, 5.0),  2*mDM_max);
      add_channel_with_scaling("t", "tbar", "t", 2*std::max(mDM_min, 160.0), 2*mDM_max, 2*173.3);

      add_channel("W+", "W-", "W", 2*std::max(mDM_min, 79.4475), 2*mDM_max);
      add_channel("Z0", "Z0", "Z", 2*std::max(mDM_min, 90.288),  2*mDM_max);
      add_channel("g",  "g",  "g", 2*std::max(mDM_min, 0.0),     2*mDM_max);
      //add_channel("gamma",  "gamma",  "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);
      //add_channel("h",  "h",  "h", 2*std::max(mDM_min, 125.1), 2*mDM_max);

      add_channel("nu_e",   "nubar_e",   "nu_e",   2*std::max(mDM_min, 0.0), 2*mDM_max);
      add_channel("nu_mu",  "nubar_mu",  "nu_mu",  2*std::max(mDM_min, 0.0), 2*mDM_max);
      add_channel("nu_tau", "nubar_tau", "nu_tau", 2*std::max(mDM_min, 0.0), 2*mDM_max);

      // Add approximations for single-particle cases.
      add_channel("Z0", "", "Z", std::max(mDM_min, 90.288),  mDM_max);
      add_channel("W+", "", "W", std::max(mDM_min, 79.4475), mDM_max);
      add_channel("W-", "", "W", std::max(mDM_min, 79.4475), mDM_max);

      add_channel("e+",   "", "e",   std::max(mDM_min, 0.0), mDM_max);
      add_channel("e-",   "", "e",   std::max(mDM_min, 0.0), mDM_max);
      add_channel("mu+",  "", "mu",  std::max(mDM_min, 0.0), mDM_max);
      add_channel("mu-",  "", "mu",  std::max(mDM_min, 0.0), mDM_max);
      add_channel("tau+", "", "tau", std::max(mDM_min, 0.0), mDM_max);
      add_channel("tau-", "", "tau", std::max(mDM_min, 0.0), mDM_max);

      add_channel_with_scaling("t",    "", "t", std::max(mDM_min, 160.0), mDM_max, 173.3);
      add_channel_with_scaling("tbar", "", "t", std::max(mDM_min, 160.0), mDM_max, 173.3);

      // Add channels with "mixed final states", i.e. final state particles with (potentially) different masses
      auto add_channel_mixedmasses = [&](const str& p1, const str& p2, const str& ch1, const str& ch2, double m1, double m2, double EcmMin, double EcmMax)
      {
        daFunk::Funk m = daFunk::var("m");
        daFunk::Funk x = daFunk::var("x");
        daFunk::Funk E = daFunk::var("Ekin");
        daFunk::Funk Ecm = daFunk::var("Ecm");

        daFunk::Funk dNdE1 = daFunk::func( PPPC_yield, daFunk::var("m"), daFunk::var("x"), ch1);
        dNdE1 = dNdE1->set("x", E/m)->set("m", Ecm/2 + (m1*m1 - m2*m2)/(2*Ecm));
        daFunk::Funk dNdE2 = daFunk::func( PPPC_yield, daFunk::var("m"), daFunk::var("x"), ch2);
        dNdE2 = dNdE2->set("x", E/m)->set("m", Ecm/2 + (m2*m2 - m1*m1)/(2*Ecm));

        result.addChannel((dNdE1+dNdE2)/2, str_flav_to_mass(p1), str_flav_to_mass(p2), yield, EcmMin, EcmMax, runOptions);
      };
      // - The numerical values for EcmMin and EcmMax are obtained from applying the corresponding two-body kinematics
      //   to the minimally/maximally allowed center-of-mass energies. Hence, EcmMin depends on the flag allow_yield_extrapolation
      add_channel_mixedmasses("u", "dbar", "q","q", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 10.0), 2*mDM_max);
      add_channel_mixedmasses("d", "ubar", "q","q", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 10.0), 2*mDM_max);
      add_channel_mixedmasses("u", "sbar", "q","q", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 10.0), 2*mDM_max);
      add_channel_mixedmasses("s", "ubar", "q","q", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 10.0), 2*mDM_max);
      add_channel_mixedmasses("u", "bbar", "q","b", 0.0, 5.0, (allow_yield_extrapolation ? 6.530 : 21.181), 2*mDM_max);
      add_channel_mixedmasses("b", "ubar", "b","q", 5.0, 0.0, (allow_yield_extrapolation ? 6.530 : 21.181), 2*mDM_max);

      add_channel_mixedmasses("c", "dbar", "c","q", 1.35, 0.0, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
      add_channel_mixedmasses("d", "cbar", "q","c", 0.0, 1.35, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
      add_channel_mixedmasses("c", "sbar", "c","q", 1.35, 0.0, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
      add_channel_mixedmasses("s", "cbar", "q","c", 0.0, 1.35, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
      add_channel_mixedmasses("c", "bbar", "c","b", 1.35, 5.0, (allow_yield_extrapolation ? 6.35 : 21.099), 2*mDM_max);
      add_channel_mixedmasses("b", "cbar", "b","c", 5.0, 1.35, (allow_yield_extrapolation ? 6.35 : 21.099), 2*mDM_max);

      add_channel_mixedmasses("t", "dbar", "t","q", 175.0, 0.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
      add_channel_mixedmasses("d", "tbar", "q","t", 0.0, 175.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
      add_channel_mixedmasses("t", "sbar", "t","q", 175.0, 0.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
      add_channel_mixedmasses("s", "tbar", "q","t", 0.0, 175.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
      add_channel_mixedmasses("t", "bbar", "t","b", 175.0, 5.0, (allow_yield_extrapolation ? 180.0 : 185.214), 2*mDM_max);
      add_channel_mixedmasses("b", "tbar", "b","t", 5.0, 175.0, (allow_yield_extrapolation ? 180.0 : 185.214), 2*mDM_max);

      return result;
    }

    // Functions for the PPPC yields are defined elsewhere
    // (in PPPC.cpp if someone asks)
    double PPPC_dNdE_gamma(double m, double x, std::string channel);
    double PPPC_dNdE_positron(double m, double x, std::string channel);

    /// Gamma-ray SimYieldTable based on PPPC4DMID Cirelli et al. 2010
    void GA_SimYieldTable_PPPC(SimYieldTable& result)
    {
      using namespace Pipes::GA_SimYieldTable_PPPC;
      static bool initialized = false;

      if ( not initialized )
      {
        /// Option allow_yield_extrapolation<bool>: Spectra extrapolated for masses beyond Pythia results (default false)
        //bool allow_yield_extrapolation = runOptions->getValueOrDef(false, "allow_yield_extrapolation");
        bool allow_yield_extrapolation = false;
        result = SimYieldTable_PPPC("gamma", allow_yield_extrapolation, &PPPC_dNdE_gamma, runOptions);
        initialized = true;
      }
    }

    /// Positron SimYieldTable based on PPPC4DMID Cirelli et al. 2010
    void positron_SimYieldTable_PPPC(SimYieldTable& result)
    {
      using namespace Pipes::positron_SimYieldTable_PPPC;
      static bool initialized = false;

      if ( not initialized )
      {
        /// Option allow_yield_extrapolation<bool>: Spectra extrapolated for masses beyond Pythia results (default false)
        //bool allow_yield_extrapolation = runOptions->getValueOrDef(false, "allow_yield_extrapolation");
        bool allow_yield_extrapolation = false;
        result = SimYieldTable_PPPC("e+_1", allow_yield_extrapolation, &PPPC_dNdE_positron, runOptions);
        initialized = true;
      }
    }

    /// Bypasses to skip specific yields in FullSimYieldTable
    void GA_SimYieldTable_empty(SimYieldTable& result)
    {
      static const SimYieldTable empty_table;
      result = empty_table;
    }

    void positron_SimYieldTable_empty(SimYieldTable& result)
    {
      static const SimYieldTable empty_table;
      result = empty_table;
    }

    void antiproton_SimYieldTable_empty(SimYieldTable& result)
    {
      static const SimYieldTable empty_table;
      result = empty_table;
    }

    void antideuteron_SimYieldTable_empty(SimYieldTable& result)
    {
      static const SimYieldTable empty_table;
      result = empty_table;
    }

    /// Electron SimYieldTable based on positron table
    void electron_SimYieldTable_from_positron_SimYieldTable(SimYieldTable& result)
    {
      static bool initialized = false;
      if ( not initialized )
      {
        // Just duplicate the positron yield.  DarkSUSY at least does not offer separate electron yields.
        result = *Pipes::electron_SimYieldTable_from_positron_SimYieldTable::Dep::positron_SimYieldTable;
        result.replaceFinalState("e+_1","e-_1");
        initialized = true;
      }
    }

    // Dumper functions ================================================

    /// \brief Helper function to dump any spectra
    int dump(const str& filename, const daFunk::Funk& spectrum)
    {
      std::ofstream myfile (filename);
      if (myfile.is_open())
      {
        for (int i = 0; i<=1200; i++)
        {
          double energy = pow(10., i/200. - 4.);
          myfile << energy << " " << spectrum->bind("E")->eval(energy) << "\n";
        }
        myfile.close();
        return 0;
      }
      else
      {
        DarkBit_error().raise(LOCAL_INFO, "Failed to open file " + filename + ".");
      }
      return 1;
    }

    /// \brief Helper function to dump gamma-ray spectra.
    void dump_gammaSpectrum(int &result)
    {
      using namespace Pipes::dump_gammaSpectrum;
      daFunk::Funk spectrum = (*Dep::GA_Yield)->set("v", 0.);
      // Option filename<string>: Filename for gamma-ray spectrum dump
      // (default: dNdE_gamma.dat)
      std::string filename = runOptions->getValueOrDef<std::string>("dNdE_gamma.dat", "filename");
      logger() << "FILENAME for gamma dump: " << filename << EOM;
      result = dump(filename, spectrum);
    }

    /// \brief Helper function to dump electron spectra.
    void dump_electronSpectrum(int &result)
    {
      using namespace Pipes::dump_electronSpectrum;
      daFunk::Funk spectrum = (*Dep::electron_Yield)->set("v", 0.);
      // Option filename<string>: Filename for electron spectrum dump
      // (default: dNdE_electron.dat)
      std::string filename = runOptions->getValueOrDef<std::string>("dNdE_electron.dat", "filename");
      logger() << "FILENAME for electron dump: " << filename << EOM;
      result = dump(filename, spectrum);
    }

    /// \brief Helper function to dump positron spectra.
    void dump_positronSpectrum(int &result)
    {
      using namespace Pipes::dump_positronSpectrum;
      daFunk::Funk spectrum = (*Dep::positron_Yield)->set("v", 0.);
      // Option filename<string>: Filename for positron spectrum dump
      // (default: dNdE_positron.dat)
      std::string filename = runOptions->getValueOrDef<std::string>("dNdE_positron.dat", "filename");
      logger() << "FILENAME for positron dump: " << filename << EOM;
      result = dump(filename, spectrum);
    }

    /// \brief Helper function to dump anti-proton spectra.
    void dump_antiprotonSpectrum(int &result)
    {
      using namespace Pipes::dump_antiprotonSpectrum;
      daFunk::Funk spectrum = (*Dep::antiproton_Yield)->set("v", 0.);
      // Option filename<string>: Filename for antiproton spectrum dump
      // (default: dNdE_antiproton.dat)
      std::string filename = runOptions->getValueOrDef<std::string>("dNdE_antiproton.dat", "filename");
      logger() << "FILENAME for antiproton dump: " << filename << EOM;
      result = dump(filename, spectrum);
    }

    /// \brief Helper function to dump anti-deuteron spectra.
    void dump_antideuteronSpectrum(int &result)
    {
      using namespace Pipes::dump_antideuteronSpectrum;
      daFunk::Funk spectrum = (*Dep::antideuteron_Yield)->set("v", 0.);
      // Option filename<string>: Filename for antideuteron spectrum dump
      // (default: dNdE_antideuteron.dat)
      std::string filename = runOptions->getValueOrDef<std::string>("dNdE_antideuteron.dat", "filename");
      logger() << "FILENAME for antideuteron dump: " << filename << EOM;
      result = dump(filename, spectrum);
    }

  }
}
