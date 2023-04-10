///
///  \author Anders Kvellestad
///  \date 2021 Nov
///
///  *********************************************

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

// #define CHECK_CUTFLOW


using namespace std;

/// @brief Simulation of "Search for new phenomena in final states with photons, jets and missing transverse momentum in pp collisions at sqrt(s)=13 TeV with the ATLAS detector"
///
/// Based on:
///  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-028/
///  - code in Analysis_ATLAS_13TeV_PhotonGGM_36invfb.cpp by Martin White
///
/// @author Anders Kvellestad
///
///
///

namespace Gambit
{
  namespace ColliderBit 
  {

    class Analysis_ATLAS_13TeV_PhotonGGM_1Photon_139invfb : public Analysis
    {
    protected:

      // Numbers passing cuts
      std::map<string, EventCounter> _counters = {
        {"SRL", EventCounter("SRL")},
        {"SRM", EventCounter("SRM")},
        {"SRH", EventCounter("SRH")},
      };


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_PhotonGGM_1Photon_139invfb() 
      {
        set_analysis_name("ATLAS_13TeV_PhotonGGM_1Photon_139invfb");
        set_luminosity(139.);
      }

      void run(const HEPUtils::Event* event)
      {

        // Missing energy
        double met = event->met();
        HEPUtils::P4 pmiss = event->missingmom();


        // Photons
        // - tight ID [MISSING]
        // - pT > 50
        // - |eta| < 2.37
        // - |eta| not in (1.37, 1.52)
        // - both track and calorimetric isolation requirements [MISSING]
        vector<const HEPUtils::Particle*> signalPhotons;
        for (const HEPUtils::Particle* photon : event->photons())
        {
          bool crack = (photon->abseta() > 1.37) && (photon->abseta() < 1.52);
          if (photon->pT() > 50. && photon->abseta() < 2.37 && !crack) signalPhotons.push_back(photon);
        }
        // Apply photon efficiency
        ATLAS::applyPhotonEfficiencyR2(signalPhotons);


        // Electrons
        // - pT > 25
        // - |eta| < 2.47
        // - |eta| not in (1.37, 1.52)
        // - loose ID
        // - loose isolation
        vector<const HEPUtils::Particle*> signalElectrons;
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          bool crack = (electron->abseta() > 1.37) && (electron->abseta() < 1.52);
          if (electron->pT() > 25. && electron->abseta() < 2.47 && !crack) signalElectrons.push_back(electron);
        }
        // Apply electron efficiency
        ATLAS::applyElectronEff(signalElectrons);
        // Apply loose electron ID efficiency
        ATLAS::applyElectronIDEfficiency2020(signalElectrons, "Loose");
        // Apply loose electron isolation efficiency
        ATLAS::applyElectronIsolationEfficiency2020(signalElectrons, "Loose");


        // Muons
        // - pT > 25
        // - |eta| < 2.7
        // - loose isolation
        vector<const HEPUtils::Particle*> signalMuons;
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 25. && muon->abseta() < 2.7) signalMuons.push_back(muon);
        }
        // Apply muon efficiency
        ATLAS::applyMuonEff(signalMuons);
        // Apply loose muon isolation efficiency
        ATLAS::applyMuonIsolationEfficiency2020(signalMuons, "Loose");


        // Jets
        // - pT > 30
        // - |eta| < 2.5
        vector<const HEPUtils::Jet*> signalJets;
        for (const HEPUtils::Jet* jet : event->jets())
        {
          if (jet->pT() > 30. && fabs(jet->eta()) < 2.5)
          {
            signalJets.push_back(jet);
          }
        }


        // Overlap removal
        // - If jet and photon within deltaR < 0.4, remove jet
        // - If jet and electron within deltaR < 0.2, remove jet
        // - If jet and electron within 0.2 < deltaR < 0.4, remove electron
        // - If jet and muon within deltaR < 0.4, remove muon

        removeOverlap(signalPhotons,signalElectrons, 0.01); // <-- taken from ATLAS code snippets on HEPData
        removeOverlap(signalJets, signalPhotons, 0.4);
        removeOverlap(signalJets, signalElectrons, 0.2);
        removeOverlap(signalElectrons, signalJets, 0.4);
        removeOverlap(signalMuons, signalJets, 0.4);


        // Put objects in pT order
        sortByPt(signalJets);
        sortByPt(signalElectrons);
        sortByPt(signalMuons);
        sortByPt(signalPhotons);

        // Multiplicities
        int nLep = signalElectrons.size() + signalMuons.size();
        int nJets = signalJets.size();
        int nPhotons = signalPhotons.size();

        // Leading photon pT
        double pTLeadingPhoton = 0.;
        if (nPhotons > 0)
        {
          pTLeadingPhoton = signalPhotons[0]->pT();
        }

        // HT
        double HT = 0.;
        for (const HEPUtils::Jet* jet : signalJets)
        {
          HT += jet->pT();
        }
        if (nPhotons > 0)
        {
          HT += signalPhotons[0]->pT();
        }

        // deltaPhi(jet,pmiss)
        double deltaPhiJetPmiss = DBL_MAX;
        if (nJets == 1)
        {
          deltaPhiJetPmiss = pmiss.deltaPhi(signalJets[0]->mom());
        }
        else if (nJets >= 2)
        {
          deltaPhiJetPmiss = std::min( pmiss.deltaPhi(signalJets[0]->mom()), pmiss.deltaPhi(signalJets[1]->mom()) );
        }

        // deltaPhi(a,pmiss)
        double deltaPhiPhotonPmiss = DBL_MAX;
        if (nPhotons > 0)
        {
          deltaPhiPhotonPmiss = pmiss.deltaPhi(signalPhotons[0]->mom());
        }

        // RT4
        double RT4 = 1.;
        if(signalJets.size() > 3)
        {
          RT4 = signalJets[0]->pT() + signalJets[1]->pT() + signalJets[2]->pT() + signalJets[3]->pT();
          double denom=0.;
          for(const HEPUtils::Jet* jet : signalJets)
          {
            denom += jet->pT();
          }
          RT4 = RT4 / denom;
        }


        // All variables are now done.
        // Increment signal region counters

        if (nPhotons >= 1 && pTLeadingPhoton > 145. && nLep == 0 && nJets >= 5 && deltaPhiJetPmiss > 0.4 && deltaPhiPhotonPmiss > 0.4 && met > 250. && HT > 2000. && RT4 < 0.9) _counters.at("SRL").add_event(event);
        if (nPhotons >= 1 && pTLeadingPhoton > 300. && nLep == 0 && nJets >= 5 && deltaPhiJetPmiss > 0.4 && deltaPhiPhotonPmiss > 0.4 && met > 300. && HT > 1600. && RT4 < 0.9) _counters.at("SRM").add_event(event);
        if (nPhotons >= 1 && pTLeadingPhoton > 400. && nLep == 0 && nJets >= 3 && deltaPhiJetPmiss > 0.4 && deltaPhiPhotonPmiss > 0.4 && met > 600. && HT > 1600.) _counters.at("SRH").add_event(event);

        return;

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_PhotonGGM_1Photon_139invfb* specificOther
          = dynamic_cast<const Analysis_ATLAS_13TeV_PhotonGGM_1Photon_139invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }


      virtual void collect_results()
      {
        // add_result(SignalRegionData("SR label", n_obs, {n_sig_MC, n_sig_MC_sys}, {n_bkg, n_bkg_err}));

        add_result(SignalRegionData(_counters.at("SRL"), 2., { 2.67, 0.75}));
        add_result(SignalRegionData(_counters.at("SRM"), 0., { 2.55, 0.64}));
        add_result(SignalRegionData(_counters.at("SRH"), 5., { 2.55, 0.44}));

        return;
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory function
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_PhotonGGM_1Photon_139invfb)


  }
}
