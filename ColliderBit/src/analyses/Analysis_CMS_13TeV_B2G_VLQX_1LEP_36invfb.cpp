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
#include "gambit/ColliderBit/toptaggedjet.h" 
#include "gambit/ColliderBit/Utils.hpp"


//#include "fastjet/ClusterSequence.hh"
//#include "fastjet/JetDefinition.hh"
#include "fastjet/tools/Filter.hh"
#include "fastjet/tools/Pruner.hh"
#include "Njettiness.hh"
#include "Nsubjettiness.hh"

#include <fastjet/contrib/SoftDrop.hh>
//#include <fastjet/contrib/Nsubjettiness.hh>



// #define CHECK_CUTFLOW

using namespace std;


namespace Gambit {
  namespace ColliderBit {


    class Analysis_CMS_13TeV_B2G_VLQX_1LEP_36invfb: public Analysis 
    {        


     public: 

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_13TeV_B2G_VLQX_1LEP_36invfb()
      {

        set_analysis_name("CMS_13TeV_B2G_VLQX_1LEP_36invfb");
        set_luminosity(35.9);  

      }

      // -----------------------------------------------------------------------------

      // Utility: compute ΔR
      static double deltaR(double eta1, double phi1, double eta2, double phi2) {
	double dEta = eta1 - eta2;
	double dPhi = std::fabs(phi1 - phi2);
	if (dPhi > M_PI) dPhi = 2*M_PI - dPhi;
	return std::sqrt(dEta*dEta + dPhi*dPhi);
      }

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

	// Trigger-level HT
	double HT_trig = 0.;
	for (auto const* jet : event->jets("antikt_R04")) {
	  if (jet->pT()>30. && fabs(jet->eta())<3.0) HT_trig += jet->pT();
	}

	// Single-lepton trigger
	bool pass_e_trig = false, pass_mu_trig = false;
	for (auto const* e : event->electrons()) {
	  if (e->pT()>32. && IsLooseOrTight(e,event,32.,2.5,0.1)) { pass_e_trig=true; break; }
	  if (e->pT()>15. && IsLooseOrTight(e,event,15.,2.5,0.4) && HT_trig>350.) { pass_e_trig=true; break; }
	}

	for (auto const* mu : event->muons()) {
	  if (mu->pT()>50. && IsLooseOrTight(mu,event,50.,2.4,999.)) { pass_mu_trig=true; break; }
	  if (mu->pT()>15. && IsLooseOrTight(mu,event,15.,2.4,0.4) && HT_trig>350.) { pass_mu_trig=true; break; }
	}
      
	if (! (pass_e_trig||pass_mu_trig)) return;

	// Lepton selection: build tight and loose collections
	std::vector<const HEPUtils::Particle*> tightLeps, looseLeps;
	for (auto const* e : event->electrons()) {
	  if (IsLooseOrTight(e,event,80.,2.5,0.1)) tightLeps.push_back(e);
	  else if (IsLooseOrTight(e,event,10.,2.5,0.4)) looseLeps.push_back(e);
	}
	for (auto const* mu : event->muons()) {
	  if (IsLooseOrTight(mu,event,80.,2.4,0.1)) tightLeps.push_back(mu);
	  else if (IsLooseOrTight(mu,event,10.,2.4,0.4)) looseLeps.push_back(mu);
	}
	if (tightLeps.size()!=1 || looseLeps.size()>0) return;
	// Define the single tight lepton
	const HEPUtils::Particle* lep = tightLeps.front();

	// Jet-lepton cleaning
	// find overlap-cleaned AK4
	std::vector<const HEPUtils::Jet*> cleanAK4;
	for (auto const* j : event->jets("antikt_R04")) {
	  if (j->pT()>30. && fabs(j->eta())<2.4) cleanAK4.push_back(j);
	}
	cleanAK4 = JetLeptonOverlapRemoval(cleanAK4, {lep},
					   [](const HEPUtils::Jet*, const HEPUtils::Particle*){return 0.2;});

	// closest jet to lepton
	double bestDR=1e3, best_pTperp=0.;
	const HEPUtils::Jet* closestJ = nullptr;
	for (auto const* j : cleanAK4) {
	  double dR = deltaR(lep->eta(),lep->phi(),j->eta(),j->phi());
	  if (dR<bestDR) { bestDR=dR; closestJ=j; }
	}
	if (closestJ) {
	  auto L=lep->mom(), J=closestJ->mom();
	  double dot = L.px()*J.px()+L.py()*J.py()+L.pz()*J.pz();
	  double J2 = J.px()*J.px()+J.py()*J.py()+J.pz()*J.pz();
	  double perp2 = L.p2() - dot*dot/J2;
	  best_pTperp = sqrt(fmax(0., perp2));
	}
	if (bestDR<=0.4 && best_pTperp<=40.) return;

	// AK4 multiplicity & b-tags
	if (cleanAK4.size()<4) return;
	std::sort(cleanAK4.begin(), cleanAK4.end(),
		  [](auto a, auto b){return a->pT()>b->pT();});
	if (cleanAK4[0]->pT()<450. || cleanAK4[1]->pT()<150.) return;

	// pt-dependent b-tagging
	vector<const HEPUtils::Jet*> bJets, nonbJets;
	const double cmisstag = 0.12;
	const double misstag  = 0.01;
	const static vector<double> binedges_btag_pt = {0.,25.,40.,60.,80.,100.,150.,200.,250.,300.,400.,500.,1000.};
	const static vector<double> eff_btag_pt =   {0.0,0.58,0.61,0.63,0.64,0.65,0.62,0.6,0.58,0.56,0.52,0.48,0.48};
	for (auto const* jet : cleanAK4) {
	  if (jet->btag() && random_bool(eff_btag_pt[binIndex(jet->pT(), binedges_btag_pt, true)])) {
	    bJets.push_back(jet);
	  } else if (jet->ctag() && random_bool(cmisstag)) {
	    bJets.push_back(jet);
	  } else if (random_bool(misstag)) {
	    bJets.push_back(jet);
	  } else {
	    nonbJets.push_back(jet);
	  }
	}
	int nB = bJets.size();
	if (nB < 1) return;  // require at least one b-tagged jet

	// Signal region DR(lep,j2)>1.0
	double dRj2 = deltaR(lep->eta(),lep->phi(),
                           cleanAK4[1]->eta(),cleanAK4[1]->phi());
	if (dRj2<=1.0) return;

	// 7) AK8 top- and W-tagging (CMS recipe)
        // SoftDrop grooming
        fastjet::contrib::SoftDrop sd(0.0, 0.1, 0.8);
        // N-subjettiness
 
	double R0 = 1.0;
	double beta = 1.0; // Angular exponent

	// Use NormalizedMeasure with the jet radius R0
        fastjet::contrib::NormalizedMeasure normalized_measure(beta, R0);

        // Calculate N-subjettiness τ32
	fastjet::contrib::Nsubjettiness n1(1, fastjet::contrib::OnePass_KT_Axes(), normalized_measure);
	fastjet::contrib::Nsubjettiness n2(2, fastjet::contrib::OnePass_KT_Axes(), normalized_measure);
	fastjet::contrib::Nsubjettiness n3(2, fastjet::contrib::OnePass_KT_Axes(), normalized_measure);
      
	//TRandom3 rnd(0);
      int nT = 0, nW = 0;
      for (auto const* j : event->jets("antikt_R08")) {
        if (j->pT() < 200. || std::fabs(j->eta()) > 2.4) continue;
        auto pj = j->pseudojet();
        auto groomed = sd(pj);
        double ptSD = groomed.pt();
        // t-tag
        if (ptSD >= 400.) {
          double mSD = groomed.m();
          double tau2v = n2(groomed), tau3v = n3(groomed);
          double r32 = (tau2v > 0 ? tau3v / tau2v : 1.0);
          if (mSD >= 105. && mSD <= 220. && r32 < 0.81) { ++nT; continue; }
        }
        // W-tag (if not t-tagged)
        if (ptSD >= 200.) {
          double mSDW = groomed.m();
          double tau1v = n1(groomed), tau2wv = n2(groomed);
          double r21 = (tau1v > 0 ? tau2wv / tau1v : 1.0);
          if (mSDW >= 65. && mSDW <= 105. && r21 < 0.6) ++nW;
        }
      }

      // 8) Fill signal region counter
      std::string tcat = (nT == 0 ? "0t" : "1t");
      std::string wcat = (nW == 0 ? "0W" : "1W");
      std::string bcat = (nB == 1 ? "1b" : "2b");
      std::string key  = tcat + "_" + wcat + "_" + bcat;
      if (_counters.count(key)) _counters[key].add_event(event);

 
      }

      void collect_results() {


	// Add data vs. background yields for each signal region from Table 3
	add_result(SignalRegionData(_counters.at("0t_0W_1b"), 984, {935.0, 62.0}));
	add_result(SignalRegionData(_counters.at("0t_0W_2b"), 416, {396.0, 33.0}));
	add_result(SignalRegionData(_counters.at("0t_1W_1b"), 577, {578.0, 47.0}));
	add_result(SignalRegionData(_counters.at("0t_1W_2b"), 321, {327.0, 30.0}));
	add_result(SignalRegionData(_counters.at("1t_0W_1b"), 465, {482.0, 44.0}));
	add_result(SignalRegionData(_counters.at("1t_0W_2b"), 285, {287.0, 31.0}));
	add_result(SignalRegionData(_counters.at("1t_1W_1b"), 135, {163.0, 17.0}));
	add_result(SignalRegionData(_counters.at("1t_1W_2b"), 123, {111.0, 13.0}));

      }

    protected:

        void analysis_specific_reset()
        {
          for (auto& pair : _counters) { pair.second.reset(); }
        }
      
    };

    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_B2G_VLQX_1LEP_36invfb)

  }
}


