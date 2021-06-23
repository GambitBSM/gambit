//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Routines for the calculation of gamma-ray yield
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

    //////////////////////////////////////////////////////////////////////////
    //
    //                        Gamma-ray yields
    //
    //////////////////////////////////////////////////////////////////////////


    /*! \brief Identification of final states that are not yet tabulated.
     *
     * Structure
     * ---------
     *
     * 1) Go through process catalog and find all final states that require
     * to be calculated in the cascade code.  To this end, check whether
     * two-body channels are tabulated for two-body final states, and whether
     * one-particle spectra exist for one-particle final states.
     *
     * 2) Calculate via the cascade code the missing energy spectra.
     *
     * 3) Put together the full spectrum.
     *
     */

    void GA_missingFinalStates(std::vector<std::string> &result)
    {
      using namespace Pipes::GA_missingFinalStates;
      std::set<std::string> missingFinalStates;
      std::string DMid= *Dep::DarkMatter_ID;

      /// Option ignore_all<bool>: Ignore all missing final states (default false)
      if ( runOptions->getValueOrDef(false, "ignore_all") ) return;

      TH_Process process = (*Dep::TH_ProcessCatalog).getProcess(DMid, DMid);

      // Add only gamma-ray spectra for two and three body final states
      for (std::vector<TH_Channel>::iterator it = process.channelList.begin();
          it != process.channelList.end(); ++it)
      {
        if ( it->nFinalStates == 2 )
        {
          /// Option ignore_two_body<bool>: Ignore two-body missing final states (default false)
          if ( not runOptions->getValueOrDef(false, "ignore_two_body") )
          {
            #ifdef DARKBIT_DEBUG
              std::cout << "Checking for missing two-body final states: "
                        << it->finalStateIDs[0] << " " << it->finalStateIDs[1]  << std::endl;
            #endif
            if ( not Dep::SimYieldTable->hasChannel(it->finalStateIDs[0], it->finalStateIDs[1], "gamma") )
            {
                if ( not Dep::SimYieldTable->hasChannel(it->finalStateIDs[0], "gamma") )
                  missingFinalStates.insert(it->finalStateIDs[0]);
                if ( not Dep::SimYieldTable->hasChannel(it->finalStateIDs[1], "gamma") )
                    missingFinalStates.insert(it->finalStateIDs[1]);
            }
          }
        }
        else if ( it->nFinalStates == 3 )
        {
          /// Option ignore_three_body<bool>: Ignore three-body missing final states (default false)
          if ( not runOptions->getValueOrDef(false, "ignore_three_body") )
          {
            #ifdef DARKBIT_DEBUG
              std::cout << "Checking for missing three-body final states: "
                        << it->finalStateIDs[0] << " " << it->finalStateIDs[1]
                        << " " << it->finalStateIDs[2] << std::endl;
            #endif
            if (not Dep::SimYieldTable->hasChannel(it->finalStateIDs[0], "gamma") )
              missingFinalStates.insert(it->finalStateIDs[0]);
            if (not Dep::SimYieldTable->hasChannel(it->finalStateIDs[1], "gamma") )
              missingFinalStates.insert(it->finalStateIDs[1]);
            if (not Dep::SimYieldTable->hasChannel(it->finalStateIDs[2], "gamma") )
              missingFinalStates.insert(it->finalStateIDs[2]);
          }
        }
      }
      // Remove particles we don't have decays for.
      for (auto it = missingFinalStates.begin(); it != missingFinalStates.end();)
      {
          if ((*Dep::TH_ProcessCatalog).find(*it, "") == NULL)
          {
            #ifdef DARKBIT_DEBUG
              std::cout << "Erasing (because no decays known): " << *it << std::endl;
            #endif
            missingFinalStates.erase(it++);
          }
          else
          {
            #ifdef DARKBIT_DEBUG
              std::cout << "Keeping (because decay known): " << *it << std::endl;
            #endif
            ++it;
          }
      }

      #ifdef DARKBIT_DEBUG
        std::cout << "Number of missing final states: " << missingFinalStates.size() << std::endl;
        for (auto it = missingFinalStates.begin(); it != missingFinalStates.end(); it++)
        {
          std::cout << *it << std::endl;
        }
      #endif

      result.assign(missingFinalStates.begin(), missingFinalStates.end());
    }

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

    /*! \brief General routine to derive annihilation yield.
     *
     * Depends on:
     * - SimYieldTable
     * - TH_ProcessCatalog
     * - cascadeMC_gammaSpectra
     *
     * This function returns
     *
     *   k*dN/dE*(sv)/mDM**2 (E, v)  [cm^3/s/GeV^3]
     *
     * the energy spectrum of photons times sigma*v/m^2, as function of
     * energy (GeV) and velocity (c), multiplied by k=1 for self-conjugate DM
     * or k=1/2 for non-self conjugate.  By default, only the v=0 component
     * is calculated.
     *
     */
    void GA_AnnYield_General(daFunk::Funk &result)
    {
      using namespace Pipes::GA_AnnYield_General;
      using DarkBit_utils::gamma3bdy_limits;

      std::string DMid= *Dep::DarkMatter_ID;

      /// Option line_width<double>: Set relative line width used in gamma-ray spectra (default 0.03)
      double line_width = runOptions->getValueOrDef<double>(0.03,  "line_width");

      // Get annihilation process from process catalog
      TH_Process annProc = (*Dep::TH_ProcessCatalog).getProcess(DMid, DMid);

      // If process involves non-self-conjugate DM then we need to add a factor of 1/2 to the final spectrum. This must be explicitly set in the process catalogue.
      double k = (annProc.isSelfConj) ? 1. : 0.5;

      // Get particle mass from process catalog
      const double mass = (*Dep::TH_ProcessCatalog).getParticleProperty(DMid).mass;
      const double Ecm = 2*mass;

      // Loop over all channels for that process
      daFunk::Funk Yield = daFunk::zero("E", "v");

      // Adding two-body channels
      for (std::vector<TH_Channel>::iterator it = annProc.channelList.begin();
          it != annProc.channelList.end(); ++it)
      {
        bool added = false;  // If spectrum is not available from any source

        // Here only take care of two-body final states
        if (it->nFinalStates != 2) continue;

        // Get final state masses
        double m0 = (*Dep::TH_ProcessCatalog).getParticleProperty(
            it->finalStateIDs[0]).mass;
        double m1 = (*Dep::TH_ProcessCatalog).getParticleProperty(
            it->finalStateIDs[1]).mass;

        // Ignore channels that are kinematically closed for v=0
        if ( m0 + m1 > Ecm ) continue;

        // Ignore channels with 0 BR in v=0 limit
        if (it->genRate->bind("v")->eval(0.) <= 0.) continue;

        double E0 = 0.5*(Ecm*Ecm+m0*m0-m1*m1)/Ecm;
        double E1 = Ecm-E0;

        // Check whether two-body final state is in SimYield table
        if ( Dep::SimYieldTable->hasChannel(
              it->finalStateIDs[0], it->finalStateIDs[1], "gamma") )
        {
          Yield = Yield +
            it->genRate*(*Dep::SimYieldTable)(
                it->finalStateIDs[0], it->finalStateIDs[1], "gamma", Ecm);
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
          if ( Dep::SimYieldTable->hasChannel(it->finalStateIDs[0], "gamma") )
          {
            spec0 = (*Dep::SimYieldTable)(it->finalStateIDs[0], "gamma")->set("Ecm",E0);
          }
          // Gamma-ray line?
          else if ( it->finalStateIDs[0] == "gamma" )
          {
            daFunk::Funk E = daFunk::var("E");
            spec0 = exp(-pow((E-E0)/line_width/E0,2)/2)/E0/sqrt(2*M_PI)/line_width;
          }
          // MC spectra available?
          else if ( Dep::cascadeMC_gammaSpectra->count(it->finalStateIDs[0]) )
          {
            double gamma0 = E0/m0;
            //std::cout << it->finalStateIDs[0] << " " << gamma0 << std::endl;
            spec0 = boost_dNdE(Dep::cascadeMC_gammaSpectra->at(it->finalStateIDs[0]), gamma0, 0.0);
          }
          else added = false;

          // Final state particle two
          if ( Dep::SimYieldTable->hasChannel(it->finalStateIDs[1], "gamma") )
          {
            spec1 = (*Dep::SimYieldTable)(it->finalStateIDs[1], "gamma")->set("Ecm", E1);
          }
          else if ( it->finalStateIDs[1] == "gamma" )
          {
            daFunk::Funk E = daFunk::var("E");
            spec1 = exp(-pow((E-E1)/line_width/E1,2)/2)/E1/sqrt(2*M_PI)/line_width;
          }
          else if ( Dep::cascadeMC_gammaSpectra->count(it->finalStateIDs[1]) )
          {
            double gamma1 = E1/m1;
            //std::cout << it->finalStateIDs[1] << " " << gamma1 << std::endl;
            spec1 = boost_dNdE(Dep::cascadeMC_gammaSpectra->at(it->finalStateIDs[1]), gamma1, 0.0);
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
            DarkBit_warning().raise(LOCAL_INFO,
                "GA_AnnYield_General: cannot find spectra for "
                + it->finalStateIDs[0] + " " + it->finalStateIDs[1]);
          }

          Yield = Yield + (spec0 + spec1) * it->genRate;
        }
      } // End adding two-body final states

      #ifdef DARKBIT_DEBUG
        std::vector<std::string> test1 = initVector<std::string> ("h0_1_test","h0_2_test","h0_2_test","h0_1_test","WH_test", "A0_test", "h0_1_test", "W+");
        std::vector<std::string> test2 = initVector<std::string> ("A0_test",  "A0_test",  "Z0_test",  "Z0_test",  "WH_test", "Z0_test", "h0_2_test", "W-");

        for(size_t i=0; i<test1.size();i++)
        {
            daFunk::Funk chnSpec = (*Dep::SimYieldTable)(test1[i], test2[i], "gamma", Ecm);
            std::vector<double> y = chnSpec->bind("E")->vect(x);
            os << test1[i] << test2[i] << ":\n";
            os << "  E: [";
            for (std::vector<double>::iterator it2 = x.begin(); it2 != x.end(); it2++)
              os << *it2 << ", ";
            os  << "]\n";
            os << "  dNdE: [";
            for (std::vector<double>::iterator it2 = y.begin(); it2 != y.end(); it2++)
              os << *it2 << ", ";
            os  << "]\n";
        }
      #endif

      // Adding three-body final states
      //
      // NOTE:  Three body processes are added even if they are closed for at v=0
      for (std::vector<TH_Channel>::iterator it = annProc.channelList.begin();
          it != annProc.channelList.end(); ++it)
      {
        bool added = true;

        // Here only take care of three-body final states
        if (it->nFinalStates != 3) continue;

        // Implement tabulated three-body final states
        /*
           if ( it->nFinalStates == 3
           and Dep::SimYieldTable->hasChannel(it->finalStateIDs[0], "gamma")
           and Dep::SimYieldTable->hasChannel(it->finalStateIDs[1], "gamma")
           and Dep::SimYieldTable->hasChannel(it->finalStateIDs[2], "gamma")
           )
           {
           daFunk::Funk dNdE1dE2 = it->genRate->set("v",0.);
           daFunk::Funk spec0 =
             (*Dep::SimYieldTable)(it->finalStateIDs[0], "gamma");
           daFunk::Funk spec1 =
             (*Dep::SimYieldTable)(it->finalStateIDs[1], "gamma");
           daFunk::Funk spec2 =
             (*Dep::SimYieldTable)(it->finalStateIDs[2], "gamma");
           Yield = Yield + convspec(spec0, spec1, spec2, dNdE1dE2);
           }
        */

        if ( it->finalStateIDs[0] == "gamma" )
        {
          if ( it->finalStateIDs[1] == "gamma" or it->finalStateIDs[2] == "gamma")
          {
            DarkBit_warning().raise(LOCAL_INFO, "Second and/or third primary gamma rays in three-body final states ignored.");
          }
          double m1 = (*Dep::TH_ProcessCatalog).getParticleProperty(
              it->finalStateIDs[1]).mass;
          double m2 = (*Dep::TH_ProcessCatalog).getParticleProperty(
              it->finalStateIDs[2]).mass;
          daFunk::Funk E1_low =  daFunk::func(gamma3bdy_limits<0>, daFunk::var("E"),
              mass, m1, m2);
          daFunk::Funk E1_high =  daFunk::func(gamma3bdy_limits<1>, daFunk::var("E"),
              mass, m1, m2);
          daFunk::Funk dsigmavde = it->genRate->gsl_integration(
              "E1", E1_low, E1_high);

          #ifdef DARKBIT_DEBUG
            daFunk::Funk chnSpec = (daFunk::zero("v", "E") + dsigmavde)-> set("v", 0.);
            std::vector<double> y = chnSpec->bind("E")->vect(x);
            os << it->finalStateIDs[0] << it->finalStateIDs[1] << it->finalStateIDs[2] << ":\n";
            os << "  E: [";
            for (std::vector<double>::iterator it2 = x.begin(); it2 != x.end(); it2++)
              os << *it2 << ", ";
            os  << "]\n";
            os << "  dNdE: [";
            for (std::vector<double>::iterator it2 = y.begin(); it2 != y.end(); it2++)
              os << *it2 << ", ";
            os  << "]\n";
          #endif

          Yield = Yield + dsigmavde;
        }
        else added = false;

        if (!added)
        {
          DarkBit_warning().raise(LOCAL_INFO,
              "GA_AnnYield_General: ignoring final state "
              + it->finalStateIDs[0] + " " + it->finalStateIDs[1] + " " + it->finalStateIDs[2]);
        }
      }
      #ifdef DARKBIT_DEBUG
        if(debug) os.close();
      #endif

      result = k*daFunk::ifelse(1e-6 - daFunk::var("v"), Yield/(mass*mass),
          daFunk::throwError("Spectrum currently only defined for v=0."));
    }


    /// SimYieldTable based on DarkSUSY5 tabulated results. (DS6 below)
    void SimYieldTable_DS5(SimYieldTable& result)
    {
      using namespace Pipes::SimYieldTable_DS5;

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
           daFunk::var("E"), ch, yieldk, flag)->set("mwimp", daFunk::var("Ecm")/2);
          result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax);
        };

        // The following routine adds an annihilation channel, for which the yields are extrapolated below Ecm_ToScale
        // using the approximation that x*dN/dx is a constant function of the dark matter mass.
        auto add_channel_with_scaling = [&](int ch, str P1, str P2, str FINAL, double EcmMin, double EcmMax, double Ecm_ToScale)
        {
          daFunk::Funk Ecm_ToUse = fmax(Ecm_ToScale, daFunk::var("Ecm"));
          daFunk::Funk ScalingFactor = Ecm_ToUse/daFunk::var("Ecm");
          daFunk::Funk dNdE = ScalingFactor * daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("mwimp"),
           ScalingFactor * daFunk::var("E"), ch, yieldk, flag)->set("mwimp", Ecm_ToUse/2);
          result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax);
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
        dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("Ecm"), daFunk::var("E"), 12, yieldk, flag);
        result.addChannel(dNdE/2, "Z0", "gamma", 90.288, mDM_max);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("Ecm"), daFunk::var("E"), 13, yieldk, flag);
        result.addChannel(dNdE/2, "W+", "gamma", 79.4475, mDM_max);
        result.addChannel(dNdE/2, "W-", "gamma", 79.4475, mDM_max);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("Ecm"), daFunk::var("E"), 15, yieldk, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("e+"), "gamma", std::max(mDM_min, 0.0), mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("e-"), "gamma", std::max(mDM_min, 0.0), mDM_max);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("Ecm"), daFunk::var("E"), 17, yieldk, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("mu+"), "gamma", std::max(mDM_min, 0.0), mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("mu-"), "gamma", std::max(mDM_min, 0.0), mDM_max);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("Ecm"), daFunk::var("E"), 19, yieldk, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("tau+"), "gamma", std::max(mDM_min, 1.7841), mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("tau-"), "gamma", std::max(mDM_min, 1.7841), mDM_max);

        double Ecm_ToScale_top = 173.3;
        daFunk::Funk Ecm_ToUse_top = fmax(Ecm_ToScale_top, daFunk::var("Ecm"));
        daFunk::Funk ScalingFactor_top = Ecm_ToUse_top/daFunk::var("Ecm");
        dNdE = ScalingFactor_top * daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), Ecm_ToUse_top,
         ScalingFactor_top * daFunk::var("E"), 24, yieldk, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("t"), "gamma", 160.0, mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("tbar"), "gamma", 160.0, mDM_max);

        // add channels with "mixed final states", i.e. final state particles with (potentially) different masses
        daFunk::Funk Ecm = daFunk::var("Ecm");
        auto add_channel_mixedmasses = [&](int ch1, int ch2, str P1, str P2, str FINAL, double m1, double m2, double EcmMin, double EcmMax)
        {
          daFunk::Funk dNdE_1 = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("E1"),
           daFunk::var("E"), ch1, yieldk, flag)->set("E1", Ecm/2 + (m1*m1 - m2*m2)/(2*Ecm));
          daFunk::Funk dNdE_2 = daFunk::func_fromThreadsafe(BEreq::dshayield.pointer(), daFunk::var("E2"),
           daFunk::var("E"), ch2, yieldk, flag)->set("E2", Ecm/2 + (m2*m2 - m1*m1)/(2*Ecm));
          result.addChannel(0.5*(dNdE_1 + dNdE_2), str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax);
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

    /// SimYieldTable based on DarkSUSY6 tabulated results.
    void SimYieldTable_DarkSUSY(SimYieldTable& result)
    {
      using namespace Pipes::SimYieldTable_DarkSUSY;

      static bool initialized = false;
      if ( not initialized )
      {
        int flag = 0;            // some flag
        int yieldpdg = 22;       // gamma ray yield (pdg code)
        int diff=1;              // differential yields (=1)
        char*hel =  (char *)"0"; //helicity

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
          mDM_min = 3.0; // minimal dark matter mass simulated in DarkSUSY6.
          mDM_max = 20000.; // maximal dark matter mass simulated in DarkSUSY6.
        }

        auto add_channel = [&](int pdg, str P1, str P2, str FINAL, double EcmMin, double EcmMax)
        {
          daFunk::Funk dNdE = daFunk::func_fromThreadsafe(BEreq::dsanyield_sim.pointer(), daFunk::var("mwimp"),
           daFunk::var("E"), pdg, hel,yieldpdg, diff, flag)->set("mwimp", daFunk::var("Ecm")/2);
          result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax);
        };

        // The following routine adds an annihilation channel, for which the yields are extrapolated below Ecm_ToScale
        // using the approximation that x*dN/dx is a constant function of the dark matter mass.
        auto add_channel_with_scaling = [&](int pdg, str P1, str P2, str FINAL, double EcmMin, double EcmMax, double Ecm_ToScale)
        {
          daFunk::Funk Ecm_ToUse = fmax(Ecm_ToScale, daFunk::var("Ecm"));
          daFunk::Funk ScalingFactor = Ecm_ToUse/daFunk::var("Ecm");
          daFunk::Funk dNdE = ScalingFactor * daFunk::func_fromThreadsafe(BEreq::dsanyield_sim.pointer(), daFunk::var("mwimp"),
           ScalingFactor * daFunk::var("E"), pdg, hel, yieldpdg, diff, flag)->set("mwimp", Ecm_ToUse/2);
          result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax);
        };

        // specifies also center of mass energy range
        add_channel(23, "Z0", "Z0", "gamma", 2*90.288, 2*mDM_max);
        add_channel(24, "W+", "W-", "gamma", 2*79.4475, 2*mDM_max);
        add_channel(12, "nu_e", "nubar_e", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
        add_channel(11, "e+", "e-", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
        add_channel(14, "nu_mu", "nubar_mu", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
        add_channel(13, "mu+", "mu-", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);
        add_channel(16, "nu_tau", "nubar_tau", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);  // Zero
        add_channel(15, "tau+", "tau-", "gamma", 2*std::max(mDM_min, 1.7841), 2*mDM_max);
        //add_channel(2, "u", "ubar", "gamma", 0., 2*mDM_max);  // Zero
        add_channel(2, "u", "ubar", "gamma", 2*std::max(mDM_min, 1.35), 2*mDM_max);  // approx by cc
        //add_channel(1, "d", "dbar", "gamma", 0., 2*mDM_max);  // Zero
        add_channel(1, "d", "dbar", "gamma", 2*std::max(mDM_min, 1.35), 2*mDM_max);  // approx by cc
        add_channel(4, "c", "cbar", "gamma", 2*std::max(mDM_min, 1.35), 2*mDM_max);
        //add_channel(3, "s", "sbar", "gamma", 0., 2*mDM_max);  // Zero
        add_channel(3, "s", "sbar", "gamma", 2*std::max(mDM_min, 1.35), 2*mDM_max);  // approx by cc
        add_channel_with_scaling(6, "t", "tbar", "gamma", 2*160.0, 2*mDM_max, 2*173.3);
        add_channel(5, "b", "bbar", "gamma", 2*std::max(mDM_min, 5.0), 2*mDM_max);
        add_channel(21, "g", "g", "gamma", 2*std::max(mDM_min, 0.0), 2*mDM_max);

        // Add approximations for single-particle cases.
        // TODO: Replace by boosted rest frame spectrum Z0
        daFunk::Funk dNdE;
        dNdE = daFunk::func_fromThreadsafe(BEreq::dsanyield_sim.pointer(), daFunk::var("Ecm"), daFunk::var("E"), 23, hel,yieldpdg, diff,flag);
        result.addChannel(dNdE/2, "Z0", "gamma", 90.288, mDM_max);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dsanyield_sim.pointer(), daFunk::var("Ecm"), daFunk::var("E"), 24, hel,yieldpdg, diff, flag);
        result.addChannel(dNdE/2, "W+", "gamma", 79.4475, mDM_max);
        result.addChannel(dNdE/2, "W-", "gamma", 79.4475, mDM_max);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dsanyield_sim.pointer(), daFunk::var("Ecm"), daFunk::var("E"), 11, hel, yieldpdg, diff, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("e+"), "gamma", std::max(mDM_min, 0.0), mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("e-"), "gamma", std::max(mDM_min, 0.0), mDM_max);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dsanyield_sim.pointer(), daFunk::var("Ecm"), daFunk::var("E"), 13, hel, yieldpdg, diff, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("mu+"), "gamma", std::max(mDM_min, 0.0), mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("mu-"), "gamma", std::max(mDM_min, 0.0), mDM_max);
        dNdE = daFunk::func_fromThreadsafe(BEreq::dsanyield_sim.pointer(), daFunk::var("Ecm"), daFunk::var("E"), 15, hel, yieldpdg, diff, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("tau+"), "gamma", std::max(mDM_min, 1.7841), mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("tau-"), "gamma", std::max(mDM_min, 1.7841), mDM_max);

        double Ecm_ToScale_top = 173.3;
        daFunk::Funk Ecm_ToUse_top = fmax(Ecm_ToScale_top, daFunk::var("Ecm"));
        daFunk::Funk ScalingFactor_top = Ecm_ToUse_top/daFunk::var("Ecm");
        dNdE = ScalingFactor_top * daFunk::func_fromThreadsafe(BEreq::dsanyield_sim.pointer(), Ecm_ToUse_top,
         ScalingFactor_top * daFunk::var("E"), 6, hel, yieldpdg, diff, flag);
        result.addChannel(dNdE/2, str_flav_to_mass("t"), "gamma", 160.0, mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("tbar"), "gamma", 160.0, mDM_max);

        // Add channels with "mixed final states", i.e. final state particles with (potentially) different masses
        daFunk::Funk Ecm = daFunk::var("Ecm");
        auto add_channel_mixedmasses = [&](int pdg1, int pdg2, str P1, str P2, str FINAL, double m1, double m2, double EcmMin, double EcmMax)
        {
          daFunk::Funk dNdE_1 = daFunk::func_fromThreadsafe(BEreq::dsanyield_sim.pointer(), daFunk::var("E1"),
           daFunk::var("E"), pdg1, hel, yieldpdg, diff, flag)->set("E1", Ecm/2 + (m1*m1 - m2*m2)/(2*Ecm));
          daFunk::Funk dNdE_2 = daFunk::func_fromThreadsafe(BEreq::dsanyield_sim.pointer(), daFunk::var("E2"),
           daFunk::var("E"), pdg2, hel, yieldpdg, diff, flag)->set("E2", Ecm/2 + (m2*m2 - m1*m1)/(2*Ecm));
          result.addChannel(0.5*(dNdE_1 + dNdE_2), str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax);
        };

        // - The numerical values for EcmMin and EcmMax are obtained from applying the corresponding two-body kinematics
        //   to the minimally/maximally allowed center-of-mass energies. Hence, EcmMin depends on the flag allow_yield_extrapolation.

        add_channel_mixedmasses(2, -1, "u", "dbar", "gamma", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
        add_channel_mixedmasses(1, -2, "d", "ubar", "gamma", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
        add_channel_mixedmasses(2, -3, "u", "sbar", "gamma", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
        add_channel_mixedmasses(3, -2, "s", "ubar", "gamma", 0.0, 0.0, (allow_yield_extrapolation ? 2*1.35 : 20.0), 2*mDM_max);
        add_channel_mixedmasses(2, -5, "u", "bbar", "gamma", 0.0, 5.0, (allow_yield_extrapolation ? 6.530 : 21.181), 2*mDM_max);
        add_channel_mixedmasses(5, -2, "b", "ubar", "gamma", 5.0, 0.0, (allow_yield_extrapolation ? 6.530 : 21.181), 2*mDM_max);

        add_channel_mixedmasses(4, -1, "c", "dbar", "gamma", 1.35, 0.0, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
        add_channel_mixedmasses(1, -4, "d", "cbar", "gamma", 0.0, 1.35, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
        add_channel_mixedmasses(4, -3, "c", "sbar", "gamma", 1.35, 0.0, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
        add_channel_mixedmasses(3, -4, "s", "cbar", "gamma", 0.0, 1.35, (allow_yield_extrapolation ? 3.260 : 20.091), 2*mDM_max);
        add_channel_mixedmasses(4, -5, "c", "bbar", "gamma", 1.35, 5.0, (allow_yield_extrapolation ? 6.35 : 21.099), 2*mDM_max);
        add_channel_mixedmasses(5, -4, "b", "cbar", "gamma", 5.0, 1.35, (allow_yield_extrapolation ? 6.35 : 21.099), 2*mDM_max);

        add_channel_mixedmasses(6, -1, "t", "dbar", "gamma", 175.0, 0.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
        add_channel_mixedmasses(1, -6, "d", "tbar", "gamma", 0.0, 175.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
        add_channel_mixedmasses(6, -3, "t", "sbar", "gamma", 175.0, 0.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
        add_channel_mixedmasses(3, -6, "s", "tbar", "gamma", 0.0, 175.0, (allow_yield_extrapolation ? 176.355 : 185.285), 2*mDM_max);
        add_channel_mixedmasses(6, -5, "t", "bbar", "gamma", 175.0, 5.0, (allow_yield_extrapolation ? 180.0 : 185.214), 2*mDM_max);
        add_channel_mixedmasses(5, -6, "b", "tbar", "gamma", 5.0, 175.0, (allow_yield_extrapolation ? 180.0 : 185.214), 2*mDM_max);

        initialized = true;
      }
    }

    /// SimYieldTable based on MicrOmegas tabulated results.
    void SimYieldTable_MicrOmegas(SimYieldTable& result)
    {
      using namespace Pipes::SimYieldTable_MicrOmegas;
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
          result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax);  // specifies also center of mass energy range
        };

        // The following routine adds an annihilation channel, for which the yields are extrapolated below Ecm_ToScale
        // using the approximation that x*dN/dx is a constant function of the dark matter mass.
        auto add_channel_with_scaling = [&](int inP, str P1, str P2, str FINAL, double EcmMin, double EcmMax, double Ecm_ToScale)
        {
          daFunk::Funk Ecm_ToUse = fmax(Ecm_ToScale, daFunk::var("Ecm"));
          daFunk::Funk ScalingFactor = Ecm_ToUse/daFunk::var("Ecm");
          daFunk::Funk dNdE = ScalingFactor * daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), Ecm_ToUse,
           ScalingFactor * daFunk::var("E"), inP, outN)/(ScalingFactor * daFunk::var("E"));
          result.addChannel(dNdE, str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax);
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

        result.addChannel(daFunk::zero("Ecm", "E"), "nu_e", "nubar_e", "gamma", 2*2., 2*mDM_max);
        result.addChannel(daFunk::zero("Ecm", "E"), "nu_mu", "nubar_mu", "gamma", 2*2., 2*mDM_max);
        result.addChannel(daFunk::zero("Ecm", "E"), "nu_tau", "nubar_tau", "gamma", 2*2., 2*mDM_max);

        // Add approximations for single-particle cases.
        daFunk::Funk dNdE;
        dNdE = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("_Ecm"), daFunk::var("E"), 8, outN)
               /daFunk::var("E"))->set("_Ecm", daFunk::var("Ecm")*2);
        result.addChannel(dNdE/2, str_flav_to_mass("mu+"), "gamma", 2., mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("mu-"), "gamma", 2., mDM_max);
        dNdE = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("_Ecm"), daFunk::var("E"), 9, outN)
               /daFunk::var("E"))->set("_Ecm", daFunk::var("Ecm")*2);
        result.addChannel(dNdE/2, str_flav_to_mass("tau+"), "gamma", 2., mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("tau-"), "gamma", 2., mDM_max);
        dNdE = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("_Ecm"), daFunk::var("E"), 10, outN)
               /daFunk::var("E"))->set("_Ecm", daFunk::var("Ecm")*2);
        result.addChannel(dNdE/2, "Z0", "gamma", 90.288, mDM_max);
        dNdE = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("_Ecm"), daFunk::var("E"), 13, outN)
               /daFunk::var("E"))->set("_Ecm", daFunk::var("Ecm")*2);
        result.addChannel(dNdE/2, "W+", "gamma", 79.497, mDM_max);
        result.addChannel(dNdE/2, "W-", "gamma", 79.497, mDM_max);

        // Add single particle lookup for t tbar to prevent them from being tagged as missing final states for cascades.
        double Ecm_ToScale_top = 176.0;
        daFunk::Funk Ecm_ToUse_top = fmax(Ecm_ToScale_top, daFunk::var("Ecm"));
        daFunk::Funk ScalingFactor_top = Ecm_ToUse_top/daFunk::var("Ecm");
        dNdE =  ScalingFactor_top * (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("_Ecm"), ScalingFactor_top * daFunk::var("E"), 6, outN)
               /(ScalingFactor_top * daFunk::var("E")))->set("_Ecm", Ecm_ToUse_top*2.0);
        result.addChannel(dNdE/2, str_flav_to_mass("t"),    "gamma", 160.0, mDM_max);
        result.addChannel(dNdE/2, str_flav_to_mass("tbar"), "gamma", 160.0, mDM_max);

        // Add channels with "mixed final states", i.e. final state particles with (potentially) different masses
        daFunk::Funk Ecm = daFunk::var("Ecm");
        auto add_channel_mixedmasses = [&](int inP1, int inP2, str P1, str P2, str FINAL, double m1, double m2, double EcmMin, double EcmMax)
        {
          daFunk::Funk dNdE_1 = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("Ecm1"),
           daFunk::var("E"), inP1, outN)->set("Ecm1", Ecm + (m1*m1 - m2*m2)/Ecm))/daFunk::var("E");
          daFunk::Funk dNdE_2 = (daFunk::func_fromThreadsafe(BEreq::dNdE.pointer(), daFunk::var("Ecm2"),
           daFunk::var("E"), inP2, outN)->set("Ecm2", Ecm + (m2*m2 - m1*m1)/Ecm))/daFunk::var("E");
          result.addChannel(0.5*(dNdE_1 + dNdE_2), str_flav_to_mass(P1), str_flav_to_mass(P2), FINAL, EcmMin, EcmMax);
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

    class PPPC_interpolation
    {
      public:
        PPPC_interpolation(std::string filename)
        {
          table = ASCIItableReader(filename);
          std::vector<std::string> colnames = initVector<std::string>(
              "mass", "log10x", "ee", "mumu", "tautau", "qq", "cc", "bb", "tt",
              "WW", "ZZ", "gg", "gammagamma", "hh");
          table.setcolnames(colnames);
          // log10x = log10(E_gamma/m);
          log10x = std::vector<double>(table["log10x"].begin(), table["log10x"].begin()+180);
        }
        PPPC_interpolation() {}  // Dummy initializer

        double operator()(std::string channel, double /*m*/, double /*e*/)
        {
          // Not yet implemented
          std::vector<double> y(table[channel].begin(), table[channel].end());
          return 0;
        }

      private:
        std::vector<double> log10x;
        ASCIItableReader table;
    };

    /// SimYieldTable based on PPPC4DMID Cirelli et al. 2010
    void SimYieldTable_PPPC(SimYieldTable& /*result*/)
    {
      using namespace Pipes::SimYieldTable_PPPC;
      static bool initialized = false;
      static PPPC_interpolation PPPC_gam_object;

      if ( not initialized )
      {
        std::string filename = "DarkBit/data/AtProductionNoEW_gammas.dat";
        PPPC_gam_object = PPPC_interpolation(filename);
        initialized = true;
        DarkBit_error().raise(LOCAL_INFO,
            "SimYieldTable_PPPC is not implemented yet.  Use e.g. SimYieldTable_DarkSUSY instead.");
      }
    }
  }
}
