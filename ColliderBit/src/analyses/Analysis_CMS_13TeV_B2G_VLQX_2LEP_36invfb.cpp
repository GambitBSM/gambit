///
///  \author Roberto Ruiz
///  \date 2024 August
///  *********************************************

// Based on:
// - https://cds.cern.ch/record/2642373/files/1810.03188.pdf?version=2

// Search for top quark partners with charge 5/3 in the same-sign dilepton and single-lepton final states in proton-proton collisions at √s = 13 TeV

#include <vector>
#include <iostream>
#include <algorithm>

//#include "gambit/ColliderBit/simple_histogram.hpp"

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
//#include "gambit/ColliderBit/analyses/Cutflow.hpp"


// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit {
  namespace ColliderBit {


    class Analysis_CMS_13TeV_B2G_VLQX_2LEP_36invfb: public Analysis 
    {        

     public: 

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_13TeV_B2G_VLQX_2LEP_36invfb(){

	/* Signal region declaration */
        // purely electronic channel
        _counters["ee"] = EventCounter("ee");
        // purely muonic channel
        _counters["mm"] = EventCounter("mm");
        // mixed channel
        _counters["em"] = EventCounter("em");

        set_analysis_name("CMS_13TeV_B2G_VLQX_2LEP_36invfb");
        set_luminosity(35.9);  

      }

      // -----------------------------------------------------------------------------
      /* Use to find out if the lepton is loose (iminiTH=0.4) or tight (iminiTH = 0.1) */
      /* There are some additional relaxed requirements for loose leptons, but they are not specified in the CMS article */
      bool IsLooseOrTight(const HEPUtils::Particle* Lep, const HEPUtils::Event* event, const double &ptTH, const double &etaTH, const double &iminiTH) {
	double eta = std::fabs(Lep->eta());
	double pt = Lep->pT();
  
	// Compute the cone radius based on CMS-like criteria
	double DR = 10.0 / std::min(std::max(pt, 50.0), 200.0);
  
	// Calculate the isolation sum within the cone radius
	double isolation = calculateIsolation(Lep, event, DR);

	// Normalize the isolation sum by the lepton's pT
	double imini = isolation / pt;

	// Apply the eta, pT, and isolation cuts
	if (eta < etaTH && pt > ptTH && imini < iminiTH) {
	  return true;
	}
	return false;
      }

      double calculateIsolation(const HEPUtils::Particle* Lep, const HEPUtils::Event* event, double coneSize) {
	double isolation_sum = 0.0;
  
	// Get the direction of the lepton
	HEPUtils::P4 lepton_p4 = Lep->mom();

	// Loop over all particles in the event
	for (const auto& particle : event->particles()) {
	  // Exclude the lepton itself from the isolation sum
	  if (particle == Lep) continue;

	  // Check if the particle is within the cone size
	  if (lepton_p4.deltaR_eta(particle->mom()) < coneSize) {
	    isolation_sum += particle->pT(); // Add the particle's pT to the isolation sum
	  }
	}

	return isolation_sum;
      }


      vector<const Jet*> JetLeptonOverlapRemoval(const vector<const Jet*>& jets,
								const vector<const Particle*>& leptons, std::function<float(const Jet*, const Particle*)> radiusFunc) 
{
        vector<const Jet*> cleanedJets;

	for (const auto& jet : jets) {
	  bool overlap = false;
	  for (const auto& lepton : leptons) {
            // Check if the jet is within a specified deltaR of the lepton
            if (jet->mom().deltaR_eta(lepton->mom()) < radiusFunc(jet, lepton)) {
                overlap = true;
                break;  // No need to check further leptons if overlap is found
            }
	  }
	  // Add the jet to the cleanedJets vector only if no overlap was found
	  if (!overlap) {
            cleanedJets.push_back(jet);
	  }
	}

	return cleanedJets;
}

      void run(const HEPUtils::Event* event) {

	double HT = 0.0;
  
	// Vectors for leptons and jets
	std::vector<const Particle*> TightElectrons, LooseElectrons, Electrons;
	std::vector<const Particle*> TightMuons, LooseMuons, Muons;
	std::vector<const Jet*> SignalJets;

	// Lepton Selection
	for (const auto& electron : event->electrons()) {
	  double pt = electron->pT();
	  double eta = std::fabs(electron->eta());
	  Electrons.push_back(electron);  // Collect all electrons
	  if (eta > 1.44 && eta < 1.57) continue; // Veto barrel-endcap transition
	  if (IsLooseOrTight(electron, event, 0.0, 2.5, 0.1)) {
	    TightElectrons.push_back(electron);
	    HT += pt;
	  }
	  if (IsLooseOrTight(electron, event, 0.0, 2.5, 0.4)) {
	    LooseElectrons.push_back(electron);
	  }
	}

	for (const auto& muon : event->muons()) {
	  Muons.push_back(muon);  // Collect all muons
	  if (IsLooseOrTight(muon, event, 0.0, 2.4, 0.1)) {
	    TightMuons.push_back(muon);
	    HT += muon->pT();
	  }
	  if (IsLooseOrTight(muon, event, 0.0, 2.4, 0.4)) {
	    LooseMuons.push_back(muon);
	  }
	}

	// Sorting leptons by pT (highest pT first)
	std::sort(TightElectrons.begin(), TightElectrons.end(), [](const Particle* a, const Particle* b) {
        return a->pT() > b->pT();
	  });

	std::sort(TightMuons.begin(), TightMuons.end(), [](const Particle* a, const Particle* b) {
        return a->pT() > b->pT();
	 });

	// Jet Selection
	for (const auto& jet : event->jets("antikt_R04")) {
	  if (jet->pT() > 30 && std::fabs(jet->eta()) < 2.4) {
	    SignalJets.push_back(jet);
	  }
	}

	// Cleaning jets from overlap with selected leptons
	SignalJets = JetLeptonOverlapRemoval(SignalJets, Electrons, [](const Jet*, const Particle*) { return 0.2; });
	SignalJets = JetLeptonOverlapRemoval(SignalJets, Muons, [](const Jet*, const Particle*) { return 0.2; });

	// Require at least 2 jets
        if (SignalJets.size() < 2) return;

	for (const auto& jet : SignalJets) HT += jet->pT();

	// Apply HT cut
	if (HT < 1200) return;

	// Number of constituents and Signal Region Classification
	int njets = SignalJets.size();
	int ne = TightElectrons.size(), nm = TightMuons.size();
	unsigned int Nconst = njets + ne + nm - 2;
	if (Nconst < 5) return;

	// Apply cuts and categorize into signal regions
	bool isEE = (ne >= 2 && TightElectrons[0]->pT() > 40 && TightElectrons[1]->pT() > 35 && TightElectrons[0]->pid() * TightElectrons[1]->pid() > 0);
	bool isMM = (nm >= 2 && TightMuons[0]->pT() > 40 && TightMuons[1]->pT() > 30 && TightMuons[0]->pid() * TightMuons[1]->pid() > 0);
	bool isEM = (ne >= 1 && nm >= 1 && TightElectrons[0]->pT() > 40 && TightMuons[0]->pT() > 30 && TightElectrons[0]->pid() * TightMuons[0]->pid() > 0);

	// Fill histograms for HT before applying final cuts
	//if (isEE) fill_histo("HT_preselected_ee", HT);
	//if (isMM) fill_histo("HT_preselected_mm", HT);
	//if (isEM) fill_histo("HT_preselected_em", HT);


	// Quarkonium veto (check for low invariant mass same-sign lepton pairs)
	bool vetoQuarkonium = false;

	// Check same-sign dilepton pairs among TightElectrons
	for (size_t i = 0; i < TightElectrons.size(); ++i) {
	  for (size_t j = i + 1; j < TightElectrons.size(); ++j) {
            if (TightElectrons[i]->pid() == TightElectrons[j]->pid()) {
                double Mll = (TightElectrons[i]->mom() + TightElectrons[j]->mom()).m();
                if (Mll < 20.0) { // Quarkonium veto condition
                    vetoQuarkonium = true;
                    break;
                }
            }
	  }
	  if (vetoQuarkonium) break;
	}

	// Check same-sign dilepton pairs among TightMuons
	if (!vetoQuarkonium) { // Only check if not already vetoed
	  for (size_t i = 0; i < TightMuons.size(); ++i) {
            for (size_t j = i + 1; j < TightMuons.size(); ++j) {
                if (TightMuons[i]->pid() == TightMuons[j]->pid()) {
                    double Mll = (TightMuons[i]->mom() + TightMuons[j]->mom()).m();
                    if (Mll < 20.0) { // Quarkonium veto condition
                        vetoQuarkonium = true;
                        break;
                    }
                }
            }
            if (vetoQuarkonium) break;
	  }
	}

	// Check same-sign electron-muon pairs (for cases with one electron and one muon)
	if (!vetoQuarkonium && TightElectrons.size() >= 1 && TightMuons.size() >= 1) {
	  if (TightElectrons[0]->pid() == TightMuons[0]->pid()) {
            double Mll = (TightElectrons[0]->mom() + TightMuons[0]->mom()).m();
            if (Mll < 20.0) { // Quarkonium veto condition
                vetoQuarkonium = true;
            }
	  }
	}

	// Stop processing if Quarkonium veto fails
	if (vetoQuarkonium) return;

	// Quarkonium veto
	//double Mll = 0;
	//if (isEE) Mll = (TightElectrons[0]->mom() + TightElectrons[1]->mom()).m();
	//if (isMM) Mll = (TightMuons[0]->mom() + TightMuons[1]->mom()).m();
	//if (isEM) Mll = (TightElectrons[0]->mom() + TightMuons[0]->mom()).m();
	//if (!apply_cut("vetoQuarkonium", Mll > 20, "All")) return;

	// Z resonance veto
	bool mll_Z = false;
	for (size_t i = 0; i < LooseElectrons.size(); ++i) {
	  for (size_t j = i + 1; j < LooseElectrons.size(); ++j) {
            if (LooseElectrons[i]->pid() != LooseElectrons[j]->pid()) {
                double mll = (LooseElectrons[i]->mom() + LooseElectrons[j]->mom()).m();
                if (std::fabs(mll - 91.2) < 15.0) {
                    mll_Z = true;
                    break;
                }
            }
	  }
	}
	if (!mll_Z) {
	  for (size_t i = 0; i < LooseMuons.size(); ++i) {
            for (size_t j = i + 1; j < LooseMuons.size(); ++j) {
                if (LooseMuons[i]->pid() != LooseMuons[j]->pid()) {
                    double mll = (LooseMuons[i]->mom() + LooseMuons[j]->mom()).m();
                    if (std::fabs(mll - 91.2) < 15.0) {
                        mll_Z = true;
                        break;
                    }
                }
            }
	  }
	}

	// Stop processing if Z veto fails
	if (mll_Z) return;
	// (Veto implementation, same as before)
	//if (!apply_cut("vetoZ", !mll_Z, "All")) return;

	// Require at least 2 jets
	//if (!apply_cut("2_jets", SignalJets.size() >= 2, "All")) return;

	// Calculate the number of constituents
	//unsigned int Nconst = SignalJets.size() + ne + nm - 2;
	//if (!apply_cut("More4Const", Nconst >= 5, "All")) return;

	// HT cut
	//if (!apply_cut("HT", HT >= 1200, "All")) return;

	// If the event passes all the cuts, count it in the appropriate signal region
	if (isEE) {
          _counters["ee"].add_event(event);
        }
	if (isMM) {
	  _counters["mm"].add_event(event);
        }
	if (isEM) {
	  _counters["em"].add_event(event);
	}  

	//run End
      }

      void collect_results() {

	add_result(SignalRegionData(_counters.at("ee"), 10, {12.8, 9.}));
	add_result(SignalRegionData(_counters.at("mm"), 12, {13.2, 9.2}));
	add_result(SignalRegionData(_counters.at("em"), 26, {26.9, 22.5}));

	//for (const auto& entry : cutflow) {
	//  std::cout << entry.first << ": " << entry.second*scale_factor << std::endl;
	//}

      }

    protected:

        void analysis_specific_reset()
        {
          for (auto& pair : _counters) { pair.second.reset(); }
        }
      
    };

    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_B2G_VLQX_2LEP_36invfb)

  }
}


