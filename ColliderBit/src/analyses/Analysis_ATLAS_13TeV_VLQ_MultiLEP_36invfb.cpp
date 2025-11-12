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
#include <iomanip>
#include <cmath>

//#include "gambit/ColliderBit/simple_histogram.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/toptaggedjet.h" 

#include "fastjet/ClusterSequence.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/tools/Filter.hh"
#include "Njettiness.hh"
#include "Nsubjettiness.hh"

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    class Analysis_ATLAS_13TeV_VLQ_MultiLEP_36invfb: public Analysis 
    {        

     public: 

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      bool isElectronIsolated(const HEPUtils::Particle* electron, const HEPUtils::Event* event) {
	double ET = electron->pT();  // For electrons, E_T is approximately pT
	double coneSize = std::min(10.0 / ET, 0.2);  // Calculate the variable cone size

	double trackSum = 0.0;  // Scalar sum of pT of tracks in the isolation cone

	// Get the electron's four-momentum (direction)
	HEPUtils::P4 electronP4 = electron->mom();

	// Loop over all particles in the event to accumulate the pT of tracks in the cone
	for (const auto& track : event->particles()) {
	  // Exclude the electron itself from the isolation sum
	  if (track == electron) continue;

	  // Compute the distance in η–ϕ space
	  double dR = electronP4.deltaR_eta(track->mom());
	  if (dR < coneSize) {
	    trackSum += track->pT();  // Sum up the track pT within the cone
	  }
	}

	// Isolation condition: the sum must be less than 6% of the electron's ET
	return (trackSum <= 0.06 * ET);
      }
      
      bool isMuonIsolated(const HEPUtils::Particle* muon, const HEPUtils::Event* event) {
	double ET = muon->pT();  // For muons, using pT as a proxy for E_T
	double coneSize = std::min(10.0 / ET, 0.3);  // Variable cone size (max 0.3)

	double trackSum = 0.0;

	// (Naming note: It might be clearer to call this variable 'muonP4' rather than 'electronP4')
	HEPUtils::P4 muonP4 = muon->mom();

	for (const auto& track : event->particles()) {
	  if (track == muon) continue;
	  double dR = muonP4.deltaR_eta(track->mom());
	  if (dR < coneSize) {
	    trackSum += track->pT();
	  }
	}

	// Isolation requirement: track sum must be less than 6% of the muon pT
	return (trackSum <= 0.06 * ET);
      }

     // Values taken from fig 17, https://arxiv.org/pdf/1510.03823.pdf
      // (old but most recent JVT publication)
      // This is almost certainly, too conservative.
      static double JVT_eff(const Jet &j){
        if (j.abseta() > 2.4) return 1.;
        if (j.pT() <= 20 || j.pT() >= 60) return 1.;

        const static vector<double> binedges_pt = {20,25,30,35,40,45,50,55,60};
        const static vector<double> binvals = {0.86, 0.9, 0.92, 0.93, 0.94, 0.95, 0.95, 0.96};

        const size_t bini = binIndex(j.pT(), binedges_pt);
        return binvals[bini];
      }

      static double JVT_eff(const Jet* j){
        return JVT_eff(*j);
      }


      //static void apply_JVT(const vector<const Jet*> &jsIn, vector<const Jet*> &jsOut){
      //  for (const Jet* j : jsIn){
      //    if (random_bool(JVT_eff(j))){
      //      jsOut.push_back(j);
      //    }
      //  }
      //}

      static void apply_JVT(const vector<const Jet*>& jets_in, vector<const Jet*>& jets_out) {
	for (const Jet* jet : jets_in) {
	  double abs_eta = fabs(jet->eta());
	  double pt = jet->pT();
	  if (abs_eta < 2.4 && pt < 60.0) {
            if (random_bool(JVT_eff(jet))) {
                jets_out.push_back(jet);
            }
	  } else {
            // Jets outside the JVT region are always accepted
            jets_out.push_back(jet);
	  }
	}
      }

      // Trimming function with mass cut
      static void trimJets(const vector<fastjet::PseudoJet> &pjs_in, vector<Jet> &js_out,
                     const double frac = 0.1,       // Fraction of the jet's pT below which subjets are trimmed
                     const double minPt = 200.,     // Minimum pt of the large-R jet
                     const double maxEta = 2.0,     // Maximum |eta| of the large-R jet
                     const double minPt_twosubJets = 0., // Minimum pt for jets with two subjets
                     const double minMass = 50.0) { // Minimum mass for large-R jets (new addition)
	js_out.clear();  // Clear the output vector of jets

	for (const fastjet::PseudoJet &pj : pjs_in) {
	  // Apply pt and eta cuts on the large-R jet
	  if (pj.pt() < minPt || fabs(pj.eta()) > maxEta || 
            (pj.pt() < minPt_twosubJets && pj.constituents().size() == 1)) continue;

	  // Calculate the veto pt threshold for trimming subjets
	  const double vetoPt = frac * pj.pt();
	  P4 running_total;  // This will hold the 4-momentum of the trimmed jet
	  vector<fastjet::PseudoJet> preserved_subjets;

	  // Loop over the constituents (subjets) of the large-R jet
	  for (const fastjet::PseudoJet &constit : pj.constituents()) {
            // Only keep subjets with pt greater than the veto threshold
            if (constit.pt() > vetoPt) {
                preserved_subjets.push_back(constit);
                running_total += P4(constit.px(), constit.py(), constit.pz(), constit.E());
            }
	  }

	  // Apply kinematic cuts to the trimmed jet
	  if (running_total.pT() < minPt || running_total.abseta() > maxEta || 
            (running_total.pT() < minPt_twosubJets && preserved_subjets.size() == 1)) continue;

	  // Apply mass cut (jet mass must be at least 50 GeV)
	  if (running_total.m() < minMass) continue;

	  // Add the trimmed jet to the output list
	  js_out.emplace_back(running_total);
	}
      }


      // Top-tagging function using N-subjettiness
      //bool applyTopTagging(const fastjet::PseudoJet &jet) {
	// Compute N-subjettiness ratios tau32 = tau3 / tau2
      //	double tau32 = jet.nsubjettiness(3) / jet.nsubjettiness(2);

	// Apply top-tagging: jets with tau32 < 0.6 are considered top-tagged
      //	return tau32 < 0.6;
      //}


      std::vector<fastjet::PseudoJet> applyTopTagging(const std::vector<fastjet::PseudoJet>& jets, double beta, double tau32_max, fastjet::contrib::Njettiness::AxesMode axes_mode) {

	double R0 = 1.0;
	double Rcutoff = 10000.0;  // Or std::numeric_limits<double>::max();


	// Create concrete MeasureDefinition
	//fastjet::contrib::UnnormalizedMeasure measure_def(beta);


	// Apply top-tagging criteria
	std::vector<fastjet::PseudoJet> top_tagged_jets;
	for (const auto& jet : jets) {
	  // Create Nsubjettiness calculators
	  fastjet::contrib::Nsubjettiness tau2_calc(2,  axes_mode, beta, R0, Rcutoff);
	  fastjet::contrib::Nsubjettiness tau3_calc(3, axes_mode, beta, R0, Rcutoff);

	  double tau2 = tau2_calc.result(jet);
	  double tau3 = tau3_calc.result(jet);
	  double tau32 = tau3 / tau2;

	  if (tau32 < tau32_max) {
            top_tagged_jets.push_back(jet);
	  }
	}

	return top_tagged_jets;
      }


      Analysis_ATLAS_13TeV_VLQ_MultiLEP_36invfb(){

       // Counters for the number of accepted events for each signal region
        _counters["SRPP_2_0J"] = EventCounter("SRPP_2_0J");
        _counters["SRPP_2_1J"] = EventCounter("SRPP_2_1J");
        _counters["SRPP_2_2J"] = EventCounter("SRPP_2_2J");
        _counters["SRPP_3L"] = EventCounter("SRPP_3L");
        _counters["SRSP_2L"] = EventCounter("SRSP_2L");
        _counters["SRSP_3L"] = EventCounter("SRSP_3L");

        set_analysis_name("ATLAS_13TeV_VLQ_MultiLEP_36invfb");
        set_luminosity(36.);  

      }

      void run(const HEPUtils::Event* event) {

        // Get the missing energy in the event
        double met = event->met();
        //HEPUtils::P4 metVec = event->missingmom();

        // Vectors for storing selected objects
        vector<const HEPUtils::Particle*> leptons, baselineElectrons, baselineMuons;
        vector<const HEPUtils::Jet*> smallRJets;
        //vector<const HEPUtils::Jet*> largeRJets;


        // Preselect electrons
        for (const auto& electron : event->electrons()) {
         if (electron->pT() > 28.0 && fabs(electron->eta()) < 2.47) {
	   if (fabs(electron->eta()) > 1.37 && fabs(electron->eta()) < 1.52) continue; // Veto barrel-endcap transition
            // Apply the isolation criterion
            if (isElectronIsolated(electron, event)) baselineElectrons.push_back(electron);
         }
        }

	//std::cout << "Number of baseline electrons: " << baselineElectrons.size() << std::endl;

        //Tight electron ID selection
	if (!baselineElectrons.empty()) {
	  // Apply the ID efficiency
	  //applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("eff1DEl_PERF_2017_01_ID_Tight"));
	  applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Tight"));

        }
       
        // Preselect muons
        for (const auto& muon : event->muons()) {
	  if (muon->pT() > 28.0 && fabs(muon->eta()) < 2.5) { 
           if (isMuonIsolated(muon, event)) baselineMuons.push_back(muon);
          }
        }

 
	//std::cout << " Muons " << baselineMuons.size() << std::endl;
        
	// Preselect jets
        vector<const HEPUtils::Jet*> preJVTJets;
        vector<const HEPUtils::Jet*> candJets;
	for (const HEPUtils::Jet* jet : event->jets("antikt_R04")) {
	  double abs_eta = fabs(jet->eta());
	  if (abs_eta < 2.5 && jet->pT() > 25.0) {
	    preJVTJets.push_back(jet);
	  } else if (abs_eta >= 2.5 && abs_eta < 4.5 && jet->pT() >= 35.0) {
	    preJVTJets.push_back(jet);
	  }
	}

        
        //exit(0);

        //for (const HEPUtils::Jet* jet : event->jets("antikt_R04")) {
	//  if (jet->pT() > 25. && fabs(jet->eta()) < 2.5)
        //    preJVTJets.push_back(jet);
        //  }

        apply_JVT(preJVTJets, candJets);


	// Assign candidate jets to smallRJets so that HT is computed on them.
	smallRJets = candJets;

	//std::cout << preJVTJets.size() << "  " <<  candJets.size() << std::endl;
                
        // Find b-jets
	vector<const HEPUtils::Jet*>  bJets, nonbJets;
        const double cmisstag = 1./6.; const double misstag = 1./134.;
        // pt-dependent b-tagging -> turns out to be kind of important due to
        // large number of high-pt jets.
        const static vector<double>binedges_btag_pt = {0.00, 30.0, 40.00, 50.00, 60.0, 75.00, 90.0, 105., 150., 200., 500 };
        const static vector<double> eff_btag_pt = {0.63, 0.705, 0.74, 0.76, 0.775, 0.785, 0.795, 0.80, 0.79, 0.75, 0.675};
        // N.b!!! The overflow value is extrapolated (from ATL-PHYS-PUB-2016-012)
        // You could quite reasonably pick a very wide range of values, and the
        // difference on the final result is order 5-10%.
        for (const HEPUtils::Jet* jet : smallRJets) {
          if (jet->abseta() >= 2.5) continue;
          // Tag
          if( jet->btag() && random_bool(eff_btag_pt[binIndex(jet->pT(), binedges_btag_pt, true)]) ) bJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) bJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) bJets.push_back(jet);
          // Non b-jet
          else nonbJets.push_back(jet);
        }
      
	//std::cout << bJets.size() << "  " << nonbJets.size() << std::endl;
       

	// Convert event particles to PseudoJets
	std::vector<fastjet::PseudoJet> fj_particles;
	for (const auto& particle : event->particles()) {
	  fj_particles.push_back(fastjet::PseudoJet(particle->mom().px(), particle->mom().py(), particle->mom().pz(), particle->mom().E()));
	}

	// Reconstruct large-R jets (R = 1.0)
	fastjet::JetDefinition jet_def_large(fastjet::antikt_algorithm, 1.0);
	fastjet::ClusterSequence cs_large(fj_particles, jet_def_large);
	std::vector<fastjet::PseudoJet> large_R_jets = cs_large.inclusive_jets(200.0); // pT ≥ 200 GeV

	// Apply trimming to reduce pileup and underlying event contributions
	fastjet::Filter trimmer(fastjet::JetDefinition(fastjet::kt_algorithm, 0.2), fastjet::SelectorPtFractionMin(0.05)); // Adjust parameters as needed

	// Apply trimming to reduce pileup and underlying event contributions
	//fastjet::Filter trimmer(fastjet::JetDefinition(fastjet::kt_algorithm, 0.5), fastjet::SelectorPtFractionMin(0.03)); // Adjust parameters as needed
        
	std::vector<fastjet::PseudoJet> trimmed_large_R_jets;
	for (const auto& jet : large_R_jets) {
	  if (fabs(jet.eta()) > 2.0) continue; // Apply |η| < 2.0 cut
	  fastjet::PseudoJet trimmed_jet = trimmer(jet);
	  if (trimmed_jet.m() >= 50.0) { // Apply mass cut: mass ≥ 50 GeV
	    trimmed_large_R_jets.push_back(trimmed_jet);
	  }
	}

	//std::cout <<   trimmed_large_R_jets.size()  << std::endl; 
        
	// Define the jet radius used in normalization (usually the same as the jet definition)
	double R0 = 1.0;
	double beta = 1.0; // Angular exponent

	// Use NormalizedMeasure with the jet radius R0
        fastjet::contrib::NormalizedMeasure normalized_measure(beta, R0);

        // Calculate N-subjettiness τ32
	fastjet::contrib::Nsubjettiness nsub3(beta, fastjet::contrib::OnePass_KT_Axes(), normalized_measure);
	fastjet::contrib::Nsubjettiness nsub2(beta, fastjet::contrib::OnePass_KT_Axes(), normalized_measure);

	// Convert trimmed_large_R_jets into MyTopTaggedJet objects
	std::vector<std::unique_ptr<HEPUtils::MyTopTaggedJet>> largeRJetsVec;
	largeRJetsVec.reserve(trimmed_large_R_jets.size());

	for (const auto& pj : trimmed_large_R_jets) {
	  // Build a MyTopTaggedJet from the pseudojet 4-momentum
	  HEPUtils::P4 jet_p4(pj.px(), pj.py(), pj.pz(), pj.E());
	  auto myjet = std::make_unique<HEPUtils::MyTopTaggedJet>(jet_p4);

	  // Compute τ3/τ2 => τ32
	  double tau3  = nsub3.result(pj);
	  double tau2  = nsub2.result(pj);
	  double tau32 = (tau2 != 0.0) ? (tau3 / tau2) : 0.0;
	  myjet->setTau32(tau32);

	  // Add jet to our container
	  largeRJetsVec.push_back(std::move(myjet));
	}

	//std::cout << largeRJetsVec.size() << std::endl;
        
	// Define top-tagging parameters
	double tau32_threshold = 0.6;
	double mass_threshold  = 150.0;
	static const std::vector<double> binedges_ttag_pt = {
	  213.1, 261.49, 311.495, 362.028, 409.843,
	  460.59, 535.32, 636.91, 738.02, 836.586,
	  940.81, 1087.06, 1283.88, 1533.74
	};
	static const std::vector<double> eff_ttag_pt = {
	  0.654, 0.799, 0.841, 0.849, 0.841,
	  0.835, 0.821, 0.804, 0.818, 0.804,
	  0.809, 0.795, 0.786, 0.816
	};

	// A helper function for binning
	auto binIndex = [&](double pt, const std::vector<double>& edges, bool upper) {
	for (size_t i=0; i<edges.size(); ++i) {
	  if (upper) {
	    if (pt < edges[i]) return i;
	  } else {
	    if (pt <= edges[i]) return i;
	  }
	}
	return edges.size()-1;
	};

	// Select top-tagged jets
	std::vector<const HEPUtils::MyTopTaggedJet*> topTaggedJets;

	for (auto& jetPtr : largeRJetsVec) {
	  // Mass from p4(), e.g. jetPtr->p4().m()

	  // Use Jet's public accessors: mass(), pT(), etc.
	  double m  = jetPtr->mass();
	  double pt = jetPtr->pT();

	  bool passesMass  = (m >= mass_threshold);
	  bool passesTau32 = (jetPtr->getTau32() <= tau32_threshold);

	  if (passesMass && passesTau32) {
	    // Compute pT bin for top-tagging efficiency
	    size_t bin = binIndex(pt, binedges_ttag_pt, true);
	    double efficiency = (bin < eff_ttag_pt.size())
                        ? eff_ttag_pt[bin]
                        : eff_ttag_pt.back();

	    // Accept or reject top tag by random draw
	    if (random_bool(efficiency)) {
	      jetPtr->setTopTagged(true);
	      topTaggedJets.push_back(jetPtr.get());
	    } else {
	      jetPtr->setTopTagged(false);
	    }
	  } else {
	    jetPtr->setTopTagged(false);
	  }
	}

        // Overlap removal
        // 1) Remove electron if share tracks with a muon
        removeOverlap(baselineElectrons, baselineMuons, 0.01);
        // 4) Remove jets if within DeltaRy 0.2 of an electron
        removeOverlap(nonbJets, baselineElectrons, 0.2, true);
        // 5) Remove electrons if within DeltaRy 0.4 of a jet
        removeOverlap(baselineElectrons, nonbJets, 0.4, true);

        auto mudRmax = [](const double mupt){return std::min(0.4, 0.04 + 10./mupt);};
        removeOverlap(baselineMuons, nonbJets, mudRmax);

	// Combine leptons
	leptons.insert(leptons.end(), baselineElectrons.begin(), baselineElectrons.end());
	leptons.insert(leptons.end(), baselineMuons.begin(), baselineMuons.end());

	//std::cout << "end " << std::endl;
        //exit(0);

	// --- Common Preselection and Global Variable Calculation ---

	// Require at least 2 leptons.
	if (leptons.size() < 2) return;

	// Build the Z candidate from the first two leptons.
	HEPUtils::P4 Z_p4 = leptons[0]->mom() + leptons[1]->mom();
	double mll = Z_p4.m();

	// Apply the Z mass window: |m_ll - m_Z| < 10 GeV (using m_Z = 91.2 GeV)
	//if (fabs(mll - 91.2) > 10.0) return;
	//if (fabs(mll - 91.2) > 1000.0) return;

	// --- b-tag Requirements ---
	// For exactly two leptons (dilepton channel), require at least 2 b-tagged jets;
	// for three or more leptons (trilepton channel), require at least 1.
        
	if (leptons.size() == 2) {
	  if (bJets.size() < 2) return;
	} else if (leptons.size() >= 3) {
	  if (bJets.size() < 1) return;
	}
        
	// For the dilepton channels, require the Z candidate pT > 250 GeV.
	if (leptons.size() == 2 && Z_p4.pT() < 250.0) return;
	
	// --- Compute Global Kinematic Variables ---

	// HT: scalar sum of the pT of all small-R jets.
	double HT = 0.0;
	for (const auto& jet : smallRJets) {
	  HT += jet->pT();
	}

	// ST: HT plus the scalar sum of the pT of all leptons (used in the trilepton channel).
	double ST = HT;
	for (const auto& lep : leptons) {
	  ST += lep->pT();
	}

	// --- Signal Region Selection for Pair-Production Channels (PP) ---

        //cout << "n leptons " << leptons.size() << endl;
	// (A) Dilepton Channels (exactly 2 leptons)
	if (leptons.size() == 2) {
	  size_t nLargeR = largeRJetsVec.size();
          //cout << "nLargeR " << nLargeR << " HT " << HT << endl; 
	  if (nLargeR == 0) {
	    // PP 2L 0J: exactly 0 large-R jets with HT > 800 GeV.
	    if (HT > 800) { 
	      _counters["SRPP_2_0J"].add_event(event);
	    }
	  } else if (nLargeR == 1) {
	    // PP 2L 1J: exactly 1 large-R jet with HT > 800 GeV.
	    if (HT > 800) {
             // Fill the HT histogram.
	      _counters["SRPP_2_1J"].add_event(event);
	    }
	  } else if (nLargeR >= 2) {
	    // PP 2L ≥2J: at least 2 large-R jets with HT > 1150 GeV.
	    if (HT > 1150) {
	      // Compute m_Zb: invariant mass of the Z candidate and the highest-pT b-tagged jet.
	      //const HEPUtils::Jet* highestPtBjet = *std::max_element(bJets.begin(), bJets.end(),
	      //[](const HEPUtils::Jet* j1, const HEPUtils::Jet* j2) { return j1->pT() < j2->pT(); });
	      //double m_Zb = (Z_p4 + highestPtBjet->mom()).m();
	      // (Optionally, you can apply further cuts on m_Zb.)
	      _counters["SRPP_2_2J"].add_event(event);
	    }
	  }
	}

	// (B) Trilepton (or more) Channel (PP ≥3L)
	if (leptons.size() >= 3) {
	  // For the trilepton channel, require ST > 1000 GeV and Z candidate pT > 200 GeV.
	  if (ST > 500 && Z_p4.pT() > 200) {
	    _counters["SRPP_3L"].add_event(event);
	  }
	}

	// ================================================================
	// Common Preselection for SP Channels
	// ================================================================

	// Require at least 2 leptons.
	if (leptons.size() < 2) return;

	// Check for a forward jet (using the "antikt_R04" jets):
	bool forwardJetFound = false;
	for (const auto& jet : event->jets("antikt_R04")) {
	  if (fabs(jet->eta()) > 2.5 && jet->pT() > 30.0) {
	    forwardJetFound = true;
	    break;
	  }
	}
	if (!forwardJetFound) return;

	// ================================================================
	// SP 2ℓ Signal Region Selection (Single Production, Dilepton Channel)
	// ================================================================
	if (leptons.size() == 2 && Z_p4.pT() > 200.0) {
	  // Require at least one top-tagged large-R jet.
	  if (topTaggedJets.size() == 0) return;

	  // Compute m_Zt: invariant mass of the Z candidate and the (first) top-tagged large-R jet.
	  const HEPUtils::MyTopTaggedJet* topTaggedJet = topTaggedJets[0];
	  double m_Zt = (Z_p4 + topTaggedJet->mom()).m();

	  // Require that (HT + met) is less than m_Zt to reduce contamination from pair production.
	  if (HT + met > m_Zt) return;
           
	  // Add event to the SP 2ℓ signal region.
	  _counters["SRSP_2L"].add_event(event);
	}

	// ================================================================
	// SP ≥3ℓ Signal Region Selection (Single Production, Trilepton Channel)
	// ================================================================
	if (leptons.size() >= 3) {
	  // In the SP ≥3ℓ channel, require a slightly looser Z candidate pT threshold.
	  if (Z_p4.pT() < 150.0) return;

	  // Among all leptons, find the highest-pT lepton.
	  double max_lep_pt = 0.0;
	  for (const auto& lep : leptons) {
	    if (lep->pT() > max_lep_pt)
	      max_lep_pt = lep->pT();
	  }
	  // Require that the highest-pT lepton has pT > 200 GeV.
	  if (max_lep_pt < 200.0) return;

	  // To reduce T T̄ contamination, require that the product of HT and the number
	  // of small-R jets is less than 6 TeV.
	  if (HT * smallRJets.size() >= 6000.0) return;
 	  // (Optionally, you can also fill ST histograms or apply additional cuts based on ST.)
	  // Add the event to the SP ≥3ℓ signal region.
	  _counters["SRSP_3L"].add_event(event);
	}
 
      }

      /*
      // Finalization: output the histogram.
      virtual void finalize() {
	for (const auto& entry : cutflow) {
	  std::cout << entry.first << ": " << entry.second << std::endl;
	}
      }
      */
      
      void collect_results() {

	add_result(SignalRegionData(_counters.at("SRPP_2_0J"), 35, {15, 33}));
	add_result(SignalRegionData(_counters.at("SRPP_2_1J"), 51, {33, 75}));
	add_result(SignalRegionData(_counters.at("SRPP_2_2J"), 9, {7, 17}));
	add_result(SignalRegionData(_counters.at("SRPP_3L"), 93, {69, 99}));
	add_result(SignalRegionData(_counters.at("SRSP_2L"), 124, {100, 200}));
	add_result(SignalRegionData(_counters.at("SRSP_3L"), 14, {7.5, 11.5}));

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

   DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_VLQ_MultiLEP_36invfb)


  }
}
