//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT side of Cascade decay codes.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 Jul - 2015 May
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2014 Mar, Jul, Sep, Oct
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"

//#define DARKBIT_DEBUG

namespace Gambit
{
  namespace DarkBit
  {

    //////////////////////////////////////////////////////////////////////////
    //
    //                        Cascade Decays
    //
    //////////////////////////////////////////////////////////////////////////

    /// Special events for event loop
    enum cascadeMC_SpecialEvents {MC_INIT=-1, MC_NEXT_STATE=-2, MC_FINALIZE=-3};

    /*! \brief Identification of hard-process final states for which yield tables do not exist.
     *
     * Structure
     * ---------
     *
     * 1) Go through process catalog and find all hard-process final states that require
     * yields to be calculated with the cascade code.  These will constitute initial states
     * for the cascade code.  To this end, check whether yield tables exist for two-body channels,
     * and whether one-particle decay yield tables exist for single particles.
     *
     * 2) Calculate via the cascade code the missing energy spectra.
     *
     * 3) Put together the full spectrum.
     *
     */

    void cascadeMC_InitialStates(std::set<std::string> &result)
    {
      using namespace Pipes::cascadeMC_InitialStates;
      std::string DMid= *Dep::DarkMatter_ID;
      std::string DMbarid = *Dep::DarkMatterConj_ID;

      result.clear();

      /// Option ignore_all<bool>: Ignore all missing hard process final states (default false)
      if ( runOptions->getValueOrDef(false, "ignore_all") ) return;

      // What type of process are we dealing with?
      TH_Process process = (*Dep::DM_process == "annihilation") ?
        (*Dep::TH_ProcessCatalog).getProcess(DMid, DMbarid) : (*Dep::TH_ProcessCatalog).getProcess(DMid);

      // Loop over all cascade MC final states
      for (const auto& cMCFinalState : *Dep::cascadeMC_FinalStates)
      {
        // Loop over all hard process final states (cascade MC initial states)
        for (const auto& channel : process.channelList)
        {
          if (channel.nFinalStates == 2)
          {
            /// Option ignore_two_body<bool>: Ignore two-body missing final states (default false)
            if ( not runOptions->getValueOrDef(false, "ignore_two_body") )
            {
              #ifdef DARKBIT_DEBUG
                std::cout << "Checking for missing two-body final states: "
                          << channel.finalStateIDs[0] << " " << channel.finalStateIDs[1]  << std::endl;
              #endif
              if (not Dep::FullSimYieldTable->hasChannel(channel.finalStateIDs[0], channel.finalStateIDs[1], cMCFinalState))
              {
                for (const auto& particle : channel.finalStateIDs)
                  if (not Dep::FullSimYieldTable->hasChannel(particle, cMCFinalState))
                    result.insert(particle);
              }
            }
          }
          else if (channel.nFinalStates == 3)
          {
            /// Option ignore_three_body<bool>: Ignore three-body missing final states (default false)
            if (not runOptions->getValueOrDef(false, "ignore_three_body"))
            {
              #ifdef DARKBIT_DEBUG
                std::cout << "Checking for missing three-body final states: "
                          << channel.finalStateIDs[0] << " " << channel.finalStateIDs[1]
                          << " " << channel.finalStateIDs[2] << std::endl;
              #endif
              for (const auto& particle : channel.finalStateIDs)
                if (not Dep::FullSimYieldTable->hasChannel(particle, cMCFinalState))
                  result.insert(particle);
            }
          }
        }
      }

      // Remove particles we don't have decays for.
      for (auto it = result.begin(); it != result.end();)
      {
          if ((*Dep::TH_ProcessCatalog).find(*it, "") == NULL)
          {
            #ifdef DARKBIT_DEBUG
              std::cout << "Erasing (because no decays known): " << *it << std::endl;
            #endif
            result.erase(it++);
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
        std::cout << "Number of missing final states: " << result.size() << std::endl;
        for (auto state : result) std::cout << state << std::endl;
      #endif
    }

    /// Function for retrieving list of final states for cascade decays
    void cascadeMC_FinalStates(std::set<std::string> &states)
    {
      using namespace Pipes::cascadeMC_FinalStates;
      static bool first = true;
      if (first)
      {
        states.clear();
        if (Downstream::neededFor("cascadeMC_gammaSpectra")) states.insert("gamma");
        if (Downstream::neededFor("cascadeMC_electronSpectra")) states.insert("e-_1");
        if (Downstream::neededFor("cascadeMC_positronSpectra")) states.insert("e+_1");
        if (Downstream::neededFor("cascadeMC_antiprotonSpectra")) states.insert("pbar");
        if (Downstream::neededFor("cascadeMC_antideuteronSpectra")) states.insert("Dbar");
        first = false;
        #ifdef DARKBIT_DEBUG
          std::cout << "Final states to generate: " << states.size() << std::endl;
          for (const auto& state : states) std::cout << "  " << state << std::endl;
        #endif
      }
    }

    /// Function setting up the decay table used in decay chains
    void cascadeMC_DecayTable(DarkBit::DecayChain::DecayTable &table)
    {
      using namespace DecayChain;
      using namespace Pipes::cascadeMC_DecayTable;
      std::set<std::string> disabled;
      // Note: One could add to "disabled" particles decays that are in the
      // process catalog but should for some reason not propagate to the FCMC
      // DecayTable.
      try
      {
        table = DecayTable(*Dep::TH_ProcessCatalog, *Dep::FullSimYieldTable, disabled);
      }
      catch(Piped_exceptions::description err)
      {
        DarkBit_error().raise(err.first,err.second);
      }
      #ifdef DARKBIT_DEBUG
        table.printTable();
      #endif
    }

    /// Loop manager for cascade decays
    void cascadeMC_LoopManager(std::string& result)
    {
      using namespace Pipes::cascadeMC_LoopManager;
      const std::set<std::string>& chainList = *Dep::cascadeMC_InitialStates;
      int cMC_minEvents = 2;  // runOptions->getValueOrDef<int>(2, "cMC_minEvents");
      // Get YAML options
      /// Option cMC_maxEvents<int>: Maximum number of cascade MC runs (default 20000)
      int cMC_maxEvents = runOptions->getValueOrDef<int>(20000, "cMC_maxEvents");

      // Initialization run
      Loop::executeIteration(MC_INIT);

      // Check whether there is anything to do
      if ( chainList.size() == 0 )
      {
        return;
      }

      // Iterate over initial state particles
      for (const auto& particle : chainList)
      {
        result = particle;
        int it;
        int counter = 0;
        bool finished = false;
        // Set next initial state
        Loop::executeIteration(MC_NEXT_STATE);
        // Event generation loop
        #pragma omp parallel private(it) shared(counter, finished)
        {
          while (!finished)
          {
            #pragma omp critical (cascadeMC_Counter)
            {
              counter++;
              it = counter;
            }
            Loop::executeIteration(it);
            #pragma omp critical (cascadeMC_Counter)
            {
              if((*Loop::done and ((counter >= cMC_minEvents) or piped_errors.inquire()))
                or (counter >= cMC_maxEvents))
                  finished=true;
              if (counter >= cMC_maxEvents)
                DarkBit_warning().raise(LOCAL_INFO,
                    "WARNING FCMC: cMC_maxEvents reached without convergence.");
            }
          }
        }
        // Raise any exceptions
        piped_invalid_point.check();
        piped_warnings.check(DarkBit_warning());
        piped_errors.check(DarkBit_error());
        Loop::reset();
      }
      Loop::executeIteration(MC_FINALIZE);
    }

    /// Event counter for cascade decays
    void cascadeMC_EventCount(std::map<std::string, int> &counts)
    {
      using namespace Pipes::cascadeMC_EventCount;
      static std::map<std::string, int> counters;
      switch(*Loop::iteration)
      {
        case MC_INIT:
          counters.clear();
          break;
        case MC_NEXT_STATE:
          counters[*Dep::cascadeMC_LoopManagement] = 0;
          break;
        case MC_FINALIZE:
          // For performance, only return the actual result once finished
          counts=counters;
          break;
        default:
        #pragma omp atomic
          counters[*Dep::cascadeMC_LoopManagement]++;
      }
    }

    /// Function for generating decay chains
    void cascadeMC_GenerateChain(
        DarkBit::DecayChain::ChainContainer &chain)
    {
      using namespace DecayChain;
      using namespace Pipes::cascadeMC_GenerateChain;
      static int    cMC_maxChainLength;
      static double cMC_Emin;
      switch(*Loop::iteration)
      {
        case MC_INIT:
          /// Option cMC_maxChainLength<int>: Maximum chain length, -1 is infinite (default -1)
          cMC_maxChainLength = runOptions->getValueOrDef<int>    (-1, "cMC_maxChainLength");
          /// Option cMC_Emin<double>: Cutoff energy for cascade particles (default 0)
          cMC_Emin = runOptions->getValueOrDef<double> (-1, "cMC_Emin");
          return;
        case MC_NEXT_STATE:
        case MC_FINALIZE:
          return;
      }
      shared_ptr<ChainParticle> chn;
      try
      {
        chn.reset(new ChainParticle( vec3(0), &(*Dep::cascadeMC_DecayTable), *Dep::cascadeMC_LoopManagement) );
        chn->generateDecayChainMC(cMC_maxChainLength,cMC_Emin);
      }
      catch(Piped_exceptions::description err)
      {
        Loop::wrapup();
        piped_errors.request(err);
      }
      chain=ChainContainer(chn);
    }

    /** Function for sampling SimYieldTables (tabulated spectra).
      * This is a convenience function used in cascadeMC_Histograms, and does
      * not have an associated capability.  */
    void cascadeMC_sampleSimYield( const SimYieldTable &table,
        const DarkBit::DecayChain::ChainParticle* endpoint,
        std::string finalState,
        const TH_ProcessCatalog &catalog,
        std::map<std::string, std::map<std::string, SimpleHist> > &histList,
        std::string initialState,
        double weight, int cMC_numSpecSamples
        )
    {
      #ifdef DARKBIT_DEBUG
        std::cout << "SampleSimYield" << std::endl;
      #endif
      std::string p1,p2;
      double gamma,beta;
      double M;
      switch(endpoint->getnChildren())
      {
        case 0:
        {
          p1 = endpoint->getpID();
          p2 = "";
          const DarkBit::DecayChain::ChainParticle* parent = endpoint->getParent();
          if(parent == NULL)
          {
            endpoint->getBoost(gamma,beta);
            M = endpoint->m;
          }
          else
          {
            parent->getBoost(gamma,beta);
            M = endpoint->E_parentFrame();
          }
          break;
        }
        case 2:
        {
          p1=(*endpoint)[0]->getpID();
          p2=(*endpoint)[1]->getpID();
          endpoint->getBoost(gamma,beta);
          M = endpoint->m;
          break;
        }
        default:
          piped_errors.request(LOCAL_INFO,
              "cascadeMC_sampleSimYield called with invalid endpoint state.");
          return;
      }
      const SimYieldChannel &chn = table.getChannel(p1 , p2, finalState);
      // Get Lorentz boost information

      const double gammaBeta = gamma*beta;
      // Mass of final state squared
      const double m = catalog.getParticleProperty(finalState).mass;
      const double msq = m*m;
      // Get histogram edges
      double histEmin, histEmax;
      histList[initialState][finalState].getEdges(histEmin, histEmax);

      // Calculate energies to sample between.  A particle decaying
      // isotropically in its rest frame will give a box spectrum.  This is
      // assumed and used here to add box contributions rather than points to
      // the histograms.  Limits are chosen such that we only sample energies
      // that can contribute to histogram bins.
      const double Ecmin = std::max( gamma*histEmin
          - gammaBeta*sqrt(histEmin*histEmin-msq) , 0*chn.Ecm_min );  // CW: chn.Ecm_min refers to initial not final energies
      const double Ecmax = std::min(std::min(
            // Highest energy that can contribute to the histogram
            gamma*histEmax + gammaBeta*sqrt(histEmax*histEmax-msq),
            // Highest energy in SimYieldChannel
            chn.Ecm_max ),
            // Estimate for highest kinematically allowed CoM energy
          0.5*(M*M + msq)/M );
      if(Ecmin>=Ecmax) return;
      const double logmin = log(Ecmin);
      const double logmax = log(Ecmax);
      const double dlogE=logmax-logmin;

      #ifdef DARKBIT_DEBUG
        std::cout << "M = " << M << std::endl;
        std::cout << "E_lab = " << endpoint->E_Lab() << std::endl;
        std::cout << "p_lab = " << endpoint->p_Lab() << std::endl;
        std::cout << "Lorentz factors gamma, beta: " << gamma << ", "
          << beta << std::endl;
        std::cout << "Initial state: " << initialState << std::endl;
        std::cout << "Channel: " << p1 << " " << p2 << std::endl;
        std::cout << "Final particles: " << finalState << std::endl;
        std::cout << "Event weight: "    << weight << std::endl;
        std::cout << "histEmin/histEmax: " << histEmin << " " << histEmax
          << std::endl;
        std::cout << "chn.Ecm_min/max: " << chn.Ecm_min << " " << chn.Ecm_max
          << std::endl;
        std::cout << "Ecmin/max: " << Ecmin << " " << Ecmax << std::endl;
        std::cout << "Final state mass^2: " << msq << std::endl;
      #endif

      double specSum=0;
      int Nsampl=0;
      SimpleHist spectrum(histList[initialState][finalState].binLower);
      while(Nsampl<cMC_numSpecSamples)
      {
        // Draw an energy in the CoM frame of the endpoint. Logarithmic
        // sampling.
        double E_CoM= exp(logmin+(logmax-logmin)*Random::draw());
        double dN_dE = chn.dNdE_bound->eval(E_CoM, M);

        double weight2 = E_CoM*dlogE*dN_dE;
        specSum += weight2;
        weight2 *= weight;
        double tmp1 = gamma*E_CoM;
        double tmp2 = gammaBeta*sqrt(E_CoM*E_CoM-msq);
        // Add box spectrum to histogram
        spectrum.addBox(tmp1-tmp2,tmp1+tmp2,weight2);
        Nsampl++;
      }
      #ifdef DARKBIT_DEBUG
        std::cout << "Number of samples = " << Nsampl << std::endl;
      #endif
      if(Nsampl>0)
      {
        spectrum.multiply(1.0/Nsampl);
        // Add bin contents of spectrum histogram to main histogram as weighted
        // events
        #pragma omp critical (cascadeMC_histList)
          histList[initialState][finalState].addHistAsWeights_sameBin(spectrum);
      }
    }

    /// Function responsible for histogramming, and evaluating end conditions for event loop
    void cascadeMC_Histograms(std::map<std::string, std::map<std::string,
        SimpleHist> > &result)
    {
      using namespace DecayChain;
      using namespace Pipes::cascadeMC_Histograms;

      // YAML options
      static int    cMC_numSpecSamples;
      static int    cMC_endCheckFrequency;
      static double cMC_gammaBGPower;
      static double cMC_gammaRelError;
      static int    cMC_NhistBins;
      static double cMC_binLow;
      static double cMC_binHigh;
      // Histogram list shared between all threads
      static std::map<std::string, std::map<std::string, SimpleHist> > histList;

      switch(*Loop::iteration)
      {
        case MC_INIT:
          // Initialization
          /// Option cMC_numSpecSamples<int>: number of samples to draw from tabulated
          /// spectra (default 25)
          cMC_numSpecSamples = runOptions->getValueOrDef<int>   (25, "cMC_numSpecSamples");
          /// Option cMC_endCheckFrequency: number of events to wait between successive
          /// checks of the convergence criteria (default 25)
          cMC_endCheckFrequency  =
            runOptions->getValueOrDef<int>   (25,     "cMC_endCheckFrequency");
          /// Option cMC_gammaBGPower: power-law slope to assume for astrophysical
          /// background (default -2.5)
          cMC_gammaBGPower       =
            runOptions->getValueOrDef<double>(-2.5,   "cMC_gammaBGPower");
          /// Option cMC_gammaRelError: max allowed relative error in bin with highest
          /// expected signal-to-background (default 0.20)
          cMC_gammaRelError      =
            runOptions->getValueOrDef<double>(0.20,   "cMC_gammaRelError");

          // Note: use same binning for all particle species
          /// Option cMC_NhistBins<int>: Number of histogram bins (default 140)
          cMC_NhistBins = runOptions->getValueOrDef<int>   (140,     "cMC_NhistBins");
          /// Option cMC_binLow<double>: Histogram min energy in GeV (default 0.001)
          cMC_binLow = runOptions->getValueOrDef<double>(0.001,  "cMC_binLow");
          /// Option cMC_binHigh<double>: Histogram max energy in GeV (default 10000)
          cMC_binHigh = runOptions->getValueOrDef<double>(10000.0,"cMC_binHigh");
          histList.clear();
          return;
        case MC_NEXT_STATE:
          // Initialize histograms
          for (const auto& state : *Dep::cascadeMC_FinalStates)
          {
            #ifdef DARKBIT_DEBUG
              std::cout << "Defining new histList entry!!!" << std::endl;
              std::cout << "for: " << *Dep::cascadeMC_LoopManagement << " " << state << std::endl;
            #endif
            double FinalStateMass = Dep::TH_ProcessCatalog->getParticleProperty(state).mass;
            histList[*Dep::cascadeMC_LoopManagement][state] = SimpleHist(cMC_NhistBins,cMC_binLow+FinalStateMass,cMC_binHigh+FinalStateMass,true);
          }
          return;
        case MC_FINALIZE:
          // For performance, only return the actual result once finished
          result = histList;
          return;
      }

      // Get list of endpoint states for this chain
      vector<const ChainParticle*> endpoints;
      Dep::cascadeMC_ChainEvent->chain->collectEndpointStates(endpoints, false);
      // Iterate over final states of interest
      for (const auto& state : *Dep::cascadeMC_FinalStates)
      {
        // Iterate over all endpoint states of the decay chain. These can
        // either be final state particles themselves or parents of final state
        // particles.  The reason for not using only final state particles is
        // that certain endpoints (e.g. quark-antiquark pairs) cannot be
        // handled as separate particles.
        for (const auto& endpoint : endpoints)
        {
          #ifdef DARKBIT_DEBUG
            std::cout << "  working on endpoint: " << endpoint->getpID() << std::endl;
            endpoint->printChain();
          #endif

          // Weighting factor (correction for mismatch between decay width
          // of available decay channels and total decay width)
          double weight;
          // Analyze single particle endpoints
          bool ignored = true;
          if(endpoint->getnChildren() ==0)
          {
            weight = endpoint->getWeight();
            // Check if the final state itself is the particle we are looking
            // for.
            if(endpoint->getpID() == state)
            {
              double E = endpoint->E_Lab();
              #pragma omp critical (cascadeMC_histList)
                histList[*Dep::cascadeMC_LoopManagement][state].addEvent(E,weight);
              ignored = false;
            }
            // Check if tabulated spectra exist for this final state
            else if((*Dep::FullSimYieldTable).hasChannel( endpoint->getpID(), state ))
            {
              cascadeMC_sampleSimYield(
                  *Dep::FullSimYieldTable, endpoint, state, *Dep::TH_ProcessCatalog,
                  histList, *Dep::cascadeMC_LoopManagement, weight,
                  cMC_numSpecSamples
                  );
              // Check if an error was raised
              ignored = false;
              if(piped_errors.inquire())
              {
                Loop::wrapup();
                return;
              }
            }
          }
          // Analyze multiparticle endpoints (the endpoint particle is here the
          // parent of final state particles).
          else
          {
            weight = (*endpoint)[0]->getWeight();
            bool hasTabulated = false;
            if(endpoint->getnChildren() == 2)
            {
              #ifdef DARKBIT_DEBUG
                std::cout << "  check whether two-body final state is tabulated: "
                  << (*endpoint)[0]->getpID() << " " << (*endpoint)[1]->getpID() <<
                  std::endl;
              #endif
              // Check if tabulated spectra exist for this final state
              if((*Dep::FullSimYieldTable).hasChannel(
                    (*endpoint)[0]->getpID() , (*endpoint)[1]->getpID(), state ))
              {
                hasTabulated = true;
                cascadeMC_sampleSimYield(*Dep::FullSimYieldTable, endpoint, state,
                    *Dep::TH_ProcessCatalog, histList,
                    *Dep::cascadeMC_LoopManagement, weight,
                    cMC_numSpecSamples
                    );
                // Check if an error was raised
                ignored = false;
                if(piped_errors.inquire())
                {
                  Loop::wrapup();
                  return;
                }
              }
            }
            if(!hasTabulated)
            {
              for (int i=0; i<(endpoint->getnChildren()); i++)
              {
                const ChainParticle* child = (*endpoint)[i];
                // Check if the child particle is the particle we are looking
                // for.
                if(child->getpID() == state)
                {
                  double E = child->E_Lab();
                  #pragma omp critical (cascadeMC_histList)
                    histList[*Dep::cascadeMC_LoopManagement][state].addEvent(E,weight);
                  ignored = false;
                }
                // Check if tabulated spectra exist for this final state
                else if((*Dep::FullSimYieldTable).hasChannel( child->getpID(), state))
                {
                  cascadeMC_sampleSimYield(*Dep::FullSimYieldTable, child, state,
                      *Dep::TH_ProcessCatalog, histList,
                      *Dep::cascadeMC_LoopManagement, weight,
                      cMC_numSpecSamples
                      );
                  // Check if an error was raised
                  ignored = false;
                  if(piped_errors.inquire())
                  {
                    Loop::wrapup();
                    return;
                  }
                }
              }
            }
          }
          if (ignored)
          {
            DarkBit_warning().raise(LOCAL_INFO, "WARNING FCMC: Missing complete decay "
             "information for " + endpoint->getpID() + ". This state is ignored.");
          }
        }
      }

      // Check if finished every cMC_endCheckFrequency events
      if((*Loop::iteration % cMC_endCheckFrequency) == 0)
      {
        enum status{untouched,unfinished,finished};
        status cond = untouched;
        for (const auto& state : *Dep::cascadeMC_FinalStates)
        {
          // End conditions currently only implemented for gamma final state
          /// @TODO: consider implementing specific convergence criteria for other final states
          if (state == "gamma")
          {
            SimpleHist hist;
            #pragma omp critical (cascadeMC_histList)
              hist = histList[*Dep::cascadeMC_LoopManagement][state];
            #ifdef DARKBIT_DEBUG
              std::cout << "Checking whether convergence is reached" << std::endl;
              for ( int i = 0; i < hist.nBins; i++ )
                std::cout << "Estimated error at " << hist.binCenter(i) << " GeV : " << hist.getRelError(i) << std::endl;
            #endif
            double sbRatioMax=-1.0;
            int maxBin=0;
            for (int i=0; i<hist.nBins; i++)
            {
              double E = hist.binCenter(i);
              double background = pow(E,cMC_gammaBGPower);
              double sbRatio = hist.binVals[i]/background;
              if(sbRatio>sbRatioMax)
              {
                sbRatioMax = sbRatio;
                maxBin=i;
              }
            }
            #ifdef DARKBIT_DEBUG
              std::cout << "Estimated maxBin: " << maxBin << std::endl;
              std::cout << "Energy at maxBin: " << hist.binCenter(maxBin) << std::endl;
              std::cout << "Estimated error at maxBin: " << hist.getRelError(maxBin) << std::endl;
              std::cout << "Value at maxBin: " << hist.getBinValues()[maxBin];
            #endif

            // Check if end condition is fulfilled. If not, set cond to
            // unfinished.
            if(hist.getRelError(maxBin) > cMC_gammaRelError) cond = unfinished;

            // If end condition is fulfilled, set cond to finished, unless
            // already set to unfinished by another condition.
            else if(cond != unfinished) cond = finished;
          }
        }
        // Break Monte Carlo loop if all end conditions are fulfilled.
        if(cond==finished)
        {
          #ifdef DARKBIT_DEBUG
            std::cout << "!! wrapping up !!" << std::endl;
            std::cout << "Performed iterations: " << *Loop::iteration << std::endl;
          #endif
          Loop::wrapup();
        }
      }
    }

    /** Convenience function for getting a daFunk::Funk object of a given spectrum.
        This function has no associated capability.
        Function retrieving specific spectra (like cascadeMC_gammaSpectra)
        should call this function.*/
    void cascadeMC_fetchSpectra(std::map<std::string, daFunk::Funk> &spectra,
        std::string finalState,
        const std::set<std::string> &ini,
        const std::set<std::string> &fin,
        const std::map<std::string, std::map<std::string,SimpleHist> > &h,
        const std::map<std::string,int> &eventCounts)
    {
      spectra.clear();

      // Make sure final state has actually been calculated
      bool calculated = (std::find(fin.begin(), fin.end(), finalState) != fin.end());
      if (not calculated) DarkBit_error().raise(LOCAL_INFO, finalState + " not calculated!");

      // Iterate over initial states
      for (const auto& initial_state : ini)
      {
        #ifdef DARKBIT_DEBUG
          std::cout << "Trying to get cascade spectra for initial state: " << initial_state << std::endl;
          std::cout << eventCounts.at(initial_state) << " events generated" << std::endl;
          int i = 0;
        #endif

        SimpleHist hist = h.at(initial_state).at(finalState);
        hist.divideByBinSize();
        std::vector<double> E = hist.getBinCenters();
        std::vector<double> dN_dE = hist.getBinValues();
        // Normalize to per-event spectrum
        for (std::vector<double>::iterator it2 = dN_dE.begin(); it2 != dN_dE.end(); ++it2)
        {
          *it2 /= eventCounts.at(initial_state);
          #ifdef DARKBIT_DEBUG
            std::cout << E[i] << " " << *it2 << std::endl;
            i++;
          #endif
        }
        // Default values provide 1-2% accuracy for singular integrals
        // Make this optional.
        spectra[initial_state] = daFunk::Funk(new daFunk::FunkInterp("E", E, dN_dE, "lin"));

        for (size_t i = 1; i<E.size()-1; i++)
        {
          if (dN_dE[i]/(dN_dE[i-1]+dN_dE[i+1]+dN_dE[i]*1e-4) > 1e2)
          {
            #ifdef DARKBIT_DEBUG
              std::cout << "Set singularity at " << E[i] << " with width " << E[i+1]-E[i] << endl;
            #endif
            spectra[initial_state]->set_singularity("E", E[i], (E[i+1]-E[i]));
          }
        }
      }
    }

    /// Debug print function for cascase spectra
    void print_spectrum_debug_info(const str& fs, const std::map<std::string, daFunk::Funk> & spectra)
    {
      std::cout << "Retrieving cascade spectra for " << fs << " final states" << std::endl;
      std::cout << "Number of simulated final states: " << spectra.size() << std::endl;
      for ( auto it = spectra.begin(); it != spectra.end(); it ++ )
      {
        std::cout << "Particle: " << it->first << std::endl;
        auto f= it->second;
        for ( double E = 0.1; E < 1000; E*=1.5 )
        {
          std::cout << "  " << E << " " << f->bind("E")->eval(E) << std::endl;
        }
        std::cout << "  Integrated spectrum: " << f->gsl_integration("E", 0, 1000)->bind()->eval() << std::endl;
      }
    }

    /// Function requesting and returning gamma ray spectra from cascade decays.
    void cascadeMC_gammaSpectra(std::map<std::string, daFunk::Funk> &spectra)
    {
      using namespace Pipes::cascadeMC_gammaSpectra;
      cascadeMC_fetchSpectra(spectra, "gamma", *Dep::cascadeMC_InitialStates,
          *Dep::cascadeMC_FinalStates, *Dep::cascadeMC_Histograms,
          *Dep::cascadeMC_EventCount);
      #ifdef DARKBIT_DEBUG
        print_spectrum_debug_info("gamma", spectra);
      #endif
    }

    /// Function requesting and returning electron spectra from cascade decays.
    void cascadeMC_electronSpectra(std::map<std::string, daFunk::Funk> &spectra)
    {
      using namespace Pipes::cascadeMC_electronSpectra;
      cascadeMC_fetchSpectra(spectra, "e-_1", *Dep::cascadeMC_InitialStates,
          *Dep::cascadeMC_FinalStates, *Dep::cascadeMC_Histograms,
          *Dep::cascadeMC_EventCount);
      #ifdef DARKBIT_DEBUG
        print_spectrum_debug_info("electron", spectra);
      #endif
    }

    /// Function requesting and returning positron spectra from cascade decays.
    void cascadeMC_positronSpectra(std::map<std::string, daFunk::Funk> &spectra)
    {
      using namespace Pipes::cascadeMC_positronSpectra;
      cascadeMC_fetchSpectra(spectra, "e+_1", *Dep::cascadeMC_InitialStates,
          *Dep::cascadeMC_FinalStates, *Dep::cascadeMC_Histograms,
          *Dep::cascadeMC_EventCount);
      #ifdef DARKBIT_DEBUG
        print_spectrum_debug_info("positron", spectra);
      #endif
    }

    /// Function requesting and returning pbar spectra from cascade decays.
    void cascadeMC_antiprotonSpectra(std::map<std::string, daFunk::Funk> &spectra)
    {
      using namespace Pipes::cascadeMC_antiprotonSpectra;
      cascadeMC_fetchSpectra(spectra, "pbar", *Dep::cascadeMC_InitialStates,
          *Dep::cascadeMC_FinalStates, *Dep::cascadeMC_Histograms,
          *Dep::cascadeMC_EventCount);
      #ifdef DARKBIT_DEBUG
        print_spectrum_debug_info("antiproton", spectra);
      #endif
    }

    /// Function requesting and returning Dbar spectra from cascade decays.
    void cascadeMC_antideuteronSpectra(std::map<std::string, daFunk::Funk> &spectra)
    {
      using namespace Pipes::cascadeMC_antideuteronSpectra;
      cascadeMC_fetchSpectra(spectra, "Dbar", *Dep::cascadeMC_InitialStates,
          *Dep::cascadeMC_FinalStates, *Dep::cascadeMC_Histograms,
          *Dep::cascadeMC_EventCount);
      #ifdef DARKBIT_DEBUG
        print_spectrum_debug_info("antideuteron", spectra);
      #endif
    }

    /*
    void cascadeMC_PrintResult(bool &dummy)
    {
      dummy=true;
      using namespace Pipes::cascadeMC_PrintResult;
      logger() << "************************" << std::endl;
      logger() << "Cascade decay results:" << std::endl;
      logger() << "------------------------" << EOM;
      std::map<std::string, std::map<std::string,SimpleHist> >
        cascadeMC_HistList = *Dep::cascadeMC_Histograms;

      for (std::map<std::string, std::map<std::string,SimpleHist> >::iterator
          it = cascadeMC_HistList.begin();
          it != cascadeMC_HistList.end(); ++it )
      {
        logger() << "Initial state: " << (it->first) << ":" << EOM;
        int nEvents = (*Dep::cascadeMC_EventCount).at(it->first);
        logger() << "Number of events: " << nEvents << EOM;
        for (std::map<std::string,SimpleHist>::iterator
            it2 = (it->second).begin(); it2 != (it->second).end(); ++it2 )
        {
          logger() << (it2->first) << ": ";
          //(it2->second).divideByBinSize();
          (it2->second).multiply(1.0/nEvents);
          for (int i=0;i<50;i++)
          {
            logger() << (it2->second).binVals[i] << "  ";
          }
          logger() << std::endl;
        }
        logger() << "------------------------" << std::endl;
      }
      logger() << "************************" << EOM;
    }
    */
  }
}

#undef DARKBIT_DEBUG
