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
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

//#define CHECK_CUTFLOW


using namespace std;

/// @brief Simulation of "Search for new phenomena in final states with photons, jets and missing transverse momentum in pp collisions at sqrt(s)=13 TeV with the ATLAS detector"
///
/// Based on:
///  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2021-028/
///  - code in Analysis_ATLAS_13TeV_PhotonGGM_36invfb.cpp by Martin White
///
///
/// August 2023: Updated to the paper version by Martin White
/// https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-11/
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

      Cutflows _cutflows;

      Analysis_ATLAS_13TeV_PhotonGGM_1Photon_139invfb()
      {
        set_analysis_name("ATLAS_13TeV_PhotonGGM_1Photon_139invfb");
        set_luminosity(139.);

	_cutflows.addCutflow("SRL", {"Trigger (one photon pT > 140 GeV)",
                                           "At least one photon", "Lepton veto",
                                           "Leading photon pT > 145 GeV", "MET > 250 GeV",
                                           "njets >= 5", "dPhi(jet,MET) > 0.4",
				     "dPhi(gamma,MET)>0.4", "HT > 2000 GeV", "RT4<0.9",});

	_cutflows.addCutflow("SRM", {"Trigger (one photon pT > 140 GeV)",
                                           "At least one photon", "Lepton veto",
                                           "Leading photon pT > 300 GeV", "MET > 300 GeV",
                                           "njets >= 5", "dPhi(jet,MET) > 0.4",
				     "dPhi(gamma,MET)>0.4", "HT > 1600 GeV", "RT4<0.9",});

	_cutflows.addCutflow("SRH", {"Trigger (one photon pT > 140 GeV)",
                                           "At least one photon", "Lepton veto",
                                           "Leading photon pT > 400 GeV", "MET > 600 GeV",
                                           "njets >= 3", "dPhi(jet,MET) > 0.4",
				     "dPhi(gamma,MET)>0.4", "HT > 1600 GeV",});


      }

      void run(const HEPUtils::Event* event)
      {

        // Missing energy
        double met = event->met();
        HEPUtils::P4 pmiss = event->missingmom();


        // Baseline Photons
        vector<const HEPUtils::Particle*> baselinePhotons;
        for (const HEPUtils::Particle* photon : event->photons())
        {
	  if (photon->pT() > 25. && photon->abseta() < 2.37) baselinePhotons.push_back(photon);
        }
        // Apply photon efficiency
        ATLAS::applyPhotonEfficiencyR2(baselinePhotons);


        // Baseline electrons
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          bool crack = (electron->abseta() > 1.37) && (electron->abseta() < 1.52);
          if (electron->pT() > 10. && electron->abseta() < 2.47 && !crack) baselineElectrons.push_back(electron);
        }
        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);
        // Apply loose electron ID efficiency
        apply1DEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_ID_Loose"));
        // Apply loose electron isolation efficiency
        apply1DEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_Iso_Loose"));


        // Baseline Muons
	vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 10. && muon->abseta() < 2.7) baselineMuons.push_back(muon);
        }
        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);
        // Apply loose muon isolation efficiency
        apply1DEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_Iso_Loose"));


        // Baseline Jets
        vector<const HEPUtils::Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets())
        {
          if (jet->pT() > 30. && fabs(jet->eta()) < 2.8)
          {
            baselineJets.push_back(jet);
          }
        }


        // Overlap removal
	// Inspire by ATLAS code snippet on HEPData
	// Doesn't exactly match the earlier paper decsription

	removeOverlap(baselineElectrons, baselineMuons, 0.01);
	removeOverlap(baselinePhotons, baselineElectrons, 0.4);
	removeOverlap(baselinePhotons, baselineMuons, 0.4);
	removeOverlap(baselineJets, baselineElectrons, 0.2);
	removeOverlap(baselineElectrons, baselineJets, 0.4);
	removeOverlap(baselineJets, baselinePhotons, 0.4);

	// Define signal objects
	vector<const HEPUtils::Particle*> signalElectrons;
	vector<const HEPUtils::Particle*> signalMuons;
	vector<const HEPUtils::Particle*> signalPhotons;
	vector<const HEPUtils::Jet*> signalJets;


	for (size_t i=0;i<baselinePhotons.size();i++)
          {
	    bool crack = (baselinePhotons.at(i)->abseta() > 1.37) && (baselinePhotons.at(i)->abseta() < 1.52);
            if (baselinePhotons.at(i)->pT()>50. && !crack) signalPhotons.push_back(baselinePhotons.at(i));
          }

	for (size_t i=0;i<baselineMuons.size();i++)
          {
            if (baselineMuons.at(i)->pT()>25.) signalMuons.push_back(baselineMuons.at(i));
          }

	for (size_t i=0;i<baselineElectrons.size();i++)
          {
	    bool crack = (baselineElectrons.at(i)->abseta() > 1.37) && (baselineElectrons.at(i)->abseta() < 1.52);
            if (baselineElectrons.at(i)->pT()>25. && !crack) signalElectrons.push_back(baselineElectrons.at(i));
          }

	for (size_t i=0;i<baselineJets.size();i++)
          {
            if (baselineJets.at(i)->pT()>30.) signalJets.push_back(baselineJets.at(i));
          }


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

	// Increment cutflows for debugging

	const double w = event->weight();
	_cutflows.fillinit(w);

	if (_cutflows["SRL"].fillnext({
                  nPhotons>=1 && pTLeadingPhoton > 140.,
                  nPhotons>=1, nLep==0,
                  pTLeadingPhoton>145., met>250., nJets>=5,
                  deltaPhiJetPmiss > 0.4, deltaPhiPhotonPmiss > 0.4, HT > 2000., RT4<0.9}, w)) _counters.at("SRL").add_event(event);

	if (_cutflows["SRM"].fillnext({
                  nPhotons>=1 && pTLeadingPhoton > 140.,
                  nPhotons>=1, nLep==0,
                  pTLeadingPhoton>300., met>300., nJets>=5,
                  deltaPhiJetPmiss > 0.4, deltaPhiPhotonPmiss > 0.4, HT > 1600., RT4<0.9}, w)) _counters.at("SRL").add_event(event);

	if (_cutflows["SRH"].fillnext({
                  nPhotons>=1 && pTLeadingPhoton > 140.,
                  nPhotons>=1, nLep==0,
                  pTLeadingPhoton>400., met>600., nJets>=3,
                  deltaPhiJetPmiss > 0.4, deltaPhiPhotonPmiss > 0.4, HT > 1600.}, w)) _counters.at("SRL").add_event(event);

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

	// Cutflow printout
        #ifdef CHECK_CUTFLOW
	  _cutflows["SRL"].normalize(47.26, 1);
	  _cutflows["SRM"].normalize(79.60, 1);
	  _cutflows["SRH"].normalize(92.73, 1);
	  cout << "\nCUTFLOWS:\n" << _cutflows << endl;
	  cout << "\nSRCOUNTS:\n";
	  // for (double x : _srnums) cout << x << "  ";
          for (auto& pair : _counters) cout << pair.second.weight_sum() << "  ";
          cout << "\n" << endl;
	#endif


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
