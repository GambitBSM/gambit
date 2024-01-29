///
///  \author Vinay Hegde
///  \date 2023 Nov
///
///  *********************************************
// Based on https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-21-009/index.html
// Search for new physics in multijet events with at least one photon and large missing transverse momentum in proton-proton collisions at 13 TeV

/*
Objects:
 Photons:
  - pT > 100 GeV, |eta| < 2.4
 AK4 jets:
  - pT > 30 GeV, |eta| < 2.4
  - Not matching with photon
Event selections:
 - MET > 300 GeV
 - Njets_AK4 >= 2 
 - Nphotons >=1 
 - ST = scalar sum pT of AK4 jets + photon pT
 - dphi(AK4 jet1, MET) > 0.3
 - dphi(AK4 jet2, MET) > 0.3
 - No. of electrons = 0
 - No. of muons = 0
 - No. of isolated tracks = 0

To be checked:
- Photon efficiency: https://arxiv.org/pdf/2012.06888.pdf or keep the old one?
- jet->mom().deltaR_eta(photon->mom()) < 0.5 . Should this be < 0.5 or something else?
*/

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"

// #define CHECK_CUTFLOW

using namespace std;
using namespace HEPUtils;

namespace Gambit {
  namespace ColliderBit {


    class Analysis_CMS_13TeV_Photon_GMSB_137invfb : public Analysis {
    public:

      static constexpr const char* detector = "CMS";

      // Counters for the number of accepted events for each signal region
      std::map<string, EventCounter> _counters = {
	//	{"SR1", EventCounter("SR1")}, //CR
	{"SR2", EventCounter("SR2")},
	{"SR3", EventCounter("SR3")},
	{"SR4", EventCounter("SR4")},
	{"SR5", EventCounter("SR5")},
	{"SR6", EventCounter("SR6")},
	{"SR7", EventCounter("SR7")},
	//	{"SR8", EventCounter("SR8")}, //CR
	{"SR9", EventCounter("SR9")},
	{"SR10", EventCounter("SR10")},
	{"SR11", EventCounter("SR11")},
	{"SR12", EventCounter("SR12")},
	{"SR13", EventCounter("SR13")},
	//	{"SR14", EventCounter("SR14")}, //CR
	{"SR15", EventCounter("SR15")},
	{"SR16", EventCounter("SR16")},
	{"SR17", EventCounter("SR17")},
	{"SR18", EventCounter("SR18")},
	//	{"SR19", EventCounter("SR19")}, //CR
	{"SR20", EventCounter("SR20")},
	{"SR21", EventCounter("SR21")},
	{"SR22", EventCounter("SR22")},
	{"SR23", EventCounter("SR23")},
	//	{"SR24", EventCounter("SR24")}, //CR
	{"SR25", EventCounter("SR25")},
	{"SR26", EventCounter("SR26")},
	{"SR27", EventCounter("SR27")},
	{"SR28", EventCounter("SR28")},
	//	{"SR29", EventCounter("SR29")}, //CR
	{"SR30", EventCounter("SR30")},
	{"SR31", EventCounter("SR31")},
	{"SR32", EventCounter("SR32")},
	{"SR33", EventCounter("SR33")},
	//	{"SR34", EventCounter("SR34")}, //CR
	{"SR35", EventCounter("SR35")},
	{"SR36", EventCounter("SR36")},
	{"SR37", EventCounter("SR37")},
	{"SR38", EventCounter("SR38")},
	{"SR39", EventCounter("SR39")},
	//	{"SR40", EventCounter("SR40")}, //CR
	{"SR41", EventCounter("SR41")},
	{"SR42", EventCounter("SR42")},
	{"SR43", EventCounter("SR43")},
	{"SR44", EventCounter("SR44")},
	{"SR45", EventCounter("SR45")},
      };


      Cutflow _cutflow;

      Analysis_CMS_13TeV_Photon_GMSB_137invfb():
	_cutflow("CMS 1-photon 13 TeV 137invfb", {"LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET"})
      {
        set_analysis_name("CMS_13TeV_Photon_GMSB_137invfb");
        set_luminosity(137.0);
      }


      void run(const HEPUtils::Event* event)
      {
        // Baseline objects
	HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();
        _cutflow.fillinit();

	vector<const Jet*> jets_ak4;
	for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
          {
            if (jet->pT() < 30) continue;
            if (jet->abseta() < 2.4) jets_ak4.push_back(jet);
          }
	
	// Get baseline electrons and apply efficiency
	vector<const Particle*> baseelecs;
	for (const Particle* electron : event->electrons())
	  if (electron->pT() > 10. && electron->abseta() < 2.5)
	    baseelecs.push_back(electron);
	//	CMS::applyElectronEff(baseelecs);
	
	// Get baseline muons and apply efficiency
	vector<const Particle*> basemuons;
	for (const Particle* muon : event->muons())
	  if (muon->pT() > 10. && muon->abseta() < 2.4)
	    basemuons.push_back(muon);
	//	CMS::applyMuonEff(basemuons);

	// Electron isolation
	/// @todo Sum should actually be over all non-e/mu calo particles
	vector<const Particle*> elecs;
	for (const Particle* e : baseelecs)
          {
            const double R = max(0.05, min(0.2, 10/e->pT()));
            double sumpt = -e->pT();
            for (const Jet* j : jets_ak4)
              if (e->mom().deltaR_eta(j->mom()) < R) sumpt += j->pT();
            if (sumpt/e->pT() < 0.1) elecs.push_back(e);
          }
	
	// Muon isolation
	/// @todo Sum should actually be over all non-e/mu calo particles
	vector<const Particle*> muons;
	for (const Particle* m : basemuons)
          {
            const double R = max(0.05, min(0.2, 10/m->pT()));
            double sumpt = -m->pT();
            for (const Jet* j : jets_ak4)
              if (m->mom().deltaR_eta(j->mom()) < R) sumpt += j->pT();
            if (sumpt/m->pT() < 0.2) muons.push_back(m);
          }
	
	// Veto the event if there are any remaining baseline leptons
	if (!muons.empty()) return;
	if (!elecs.empty()) return;
	_cutflow.fill(1);
	_cutflow.fill(2); //IsoTrack veto is not implemented.

        // Apply photon efficiency and collect baseline photon
        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/PhotonEfficiencies_ForPublic_Moriond2017_LoosePixelVeto.pdf
        //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aPhoton={0., 0.8, 1.4442, 1.566, 2.0, 2.5, DBL_MAX};   // Bin edges in eta
        const vector<double> bPhoton={0., 20., 35., 50., 90., DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cPhoton={
                           // pT:   (0,20),  (20,35),  (35,50),  (50,90),  (90,inf)
                                     0.0,    0.735,    0.779,    0.805,    0.848,   // eta: (0, 0.8)
                                     0.0,    0.726,    0.746,    0.768,    0.809,   // eta: (0.8, 1.4442)
                                     0.0,    0.0,      0.0,      0.0,      0.0,     // eta: (1.4442, 1.566)
                                     0.0,    0.669,    0.687,    0.704,    0.723,   // eta: (1.566, 2.0)
                                     0.0,    0.564,    0.585,    0.592,    0.612,   // eta: (2.0, 2.5)
                                     0.0,    0.0,      0.0,      0.0,      0.0,     // eta > 2.5
                                 };
        HEPUtils::BinnedFn2D<double> _eff2dPhoton(aPhoton,bPhoton,cPhoton);
        vector<const HEPUtils::Particle*> Photons;
        for (const HEPUtils::Particle* photon : event->photons())
        {
          bool isPhoton=has_tag(_eff2dPhoton, photon->abseta(), photon->pT());
          if (isPhoton && photon->pT()>100.) Photons.push_back(photon);
        }

	// Photon cleaning
        // Remove jets that overlap with photons within dR < 0.3
        removeOverlap(jets_ak4, Photons, 0.3);

	// Count b-jets
	size_t nbjets = 0;
	for (const Jet* j : jets_ak4)
	  if (random_bool(j->btag() ? 0.65 : j->ctag() ? 0.13 : 0.016))
	    nbjets += 1;

        bool high_pT_photon = false;  // At least one high-pT photon;
        bool delta_R_g_j = false;     // Photons are required to have delta_R>0.5 to the nearest jet;
	for (const HEPUtils::Particle* photon  : Photons){
	  if (photon->pT()>100. && fabs(photon->eta()) < 2.4) {
	    high_pT_photon = true;
	    for (const HEPUtils::Jet* jet : jets_ak4){
	      if ( jet->mom().deltaR_eta(photon->mom()) < 0.5 ) delta_R_g_j=true;
	    }
	  }
	}
        if (not high_pT_photon) return;
        if (delta_R_g_j) return;
	_cutflow.fill(3);

	// MET > 300 GeV
        if (met<300)return;
        _cutflow.fill(4);

	//At least 2 AK4 jets
	const size_t njets_ak4 = jets_ak4.size();
	if (njets_ak4 < 2) return;
	_cutflow.fill(5);

	//ST = jets_ak4_pt + photon_pt
	double ST = 0.0;
	for (const Jet* j : jets_ak4)
	  {
	    ST = ST + j->pT();
	  }
	for (const Particle* photon  : Photons)
	  {
	    ST = ST + photon->pT();
	  }
	if (ST < 300) return;
	_cutflow.fill(6);

	// Downweight for event quality inefficiency
	// Trigger efficiencies for events with reconstructed pmissT
	// of at least 200 (300) GeV are found to be 70, 60, and 60%
	// (95, 95, and 97%) for data collected in 2016, 2017, and 2018, respectively.
	// Efficiency for 2016+2017+2018 = lumi*eff/total_lumi = (63.67*0.97+44.99*0.95+35.25*0.95)/143.91 = 0.96.
	// Lumi ref = https://twiki.cern.ch/twiki/bin/view/CMSPublic/LumiPublicResults
	if (!random_bool(0.96)) return;
	_cutflow.fill(7);

	// AK4 jets must fulfill delta_phi(MET,jet)>0.3 for leading two
	if (jets_ak4.size() >= 2 && fabs(jets_ak4[0]->mom().deltaPhi(metVec)) < 0.3) return;
	if (jets_ak4.size() >= 2 && fabs(jets_ak4[1]->mom().deltaPhi(metVec)) < 0.3) return;
	_cutflow.fill(8);

	vector<const Jet*> jets_ak8;
	for (const HEPUtils::Jet* jet : event->jets("antikt_R08"))
          {
            if (jet->pT() < 200) continue;
            if (jet->abseta() < 2.4) jets_ak8.push_back(jet);
          }

	bool isVtag = false, isHtag = false;
	if (jets_ak8.size() > 0 && njets_ak4 <= 6)
	  {
	    double leadMass = jets_ak8[0]->mass(); //Replace it with SD mass	  
	    if (leadMass > 65 && leadMass < 105) isVtag = true;
	    else if (leadMass > 105 && leadMass < 140) isHtag = true;
	  }
        // Signal regions
	if (isVtag)
	  {
	    if (met < 370) _counters.at("SR35").add_event(event);
	    else if (met < 450) _counters.at("SR36").add_event(event);
	    else if (met < 600) _counters.at("SR37").add_event(event);
	    else if (met < 750) _counters.at("SR38").add_event(event);
	    else                _counters.at("SR39").add_event(event);
	  }
	else if (isHtag)
	  {
	    if (met < 370) _counters.at("SR41").add_event(event);
	    else if (met < 450) _counters.at("SR42").add_event(event);
	    else if (met < 600) _counters.at("SR43").add_event(event);
	    else if (met < 750) _counters.at("SR44").add_event(event);
	    else                _counters.at("SR45").add_event(event);
	  }
	else
	  {
	    if      (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met < 370) _counters.at("SR2").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met < 450) _counters.at("SR3").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met < 600) _counters.at("SR4").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met < 750) _counters.at("SR5").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met < 900) _counters.at("SR6").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met >=900) _counters.at("SR7").add_event(event);

	    else if (nbjets == 0 && njets_ak4 >=5 && njets_ak4 <=6 && met < 370) _counters.at("SR9").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=5 && njets_ak4 <=6 && met < 450) _counters.at("SR10").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=5 && njets_ak4 <=6 && met < 600) _counters.at("SR11").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=5 && njets_ak4 <=6 && met < 750) _counters.at("SR12").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=5 && njets_ak4 <=6 && met >=750) _counters.at("SR13").add_event(event);

	    else if (nbjets == 0 && njets_ak4 >=7 && met < 370) _counters.at("SR15").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=7 && met < 450) _counters.at("SR16").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=7 && met < 600) _counters.at("SR17").add_event(event);
	    else if (nbjets == 0 && njets_ak4 >=7 && met >=600) _counters.at("SR18").add_event(event);

	    else if (nbjets >= 1 && njets_ak4 >=2 && njets_ak4 <=4 && met < 370) _counters.at("SR20").add_event(event);
	    else if (nbjets >= 1 && njets_ak4 >=2 && njets_ak4 <=4 && met < 450) _counters.at("SR21").add_event(event);
	    else if (nbjets >= 1 && njets_ak4 >=2 && njets_ak4 <=4 && met < 600) _counters.at("SR22").add_event(event);
	    else if (nbjets >= 1 && njets_ak4 >=2 && njets_ak4 <=4 && met >=600) _counters.at("SR23").add_event(event);

	    else if (nbjets >= 1 && njets_ak4 >=5 && njets_ak4 <=6 && met < 370) _counters.at("SR25").add_event(event);
	    else if (nbjets >= 1 && njets_ak4 >=5 && njets_ak4 <=6 && met < 450) _counters.at("SR26").add_event(event);
	    else if (nbjets >= 1 && njets_ak4 >=5 && njets_ak4 <=6 && met < 600) _counters.at("SR27").add_event(event);
	    else if (nbjets >= 1 && njets_ak4 >=5 && njets_ak4 <=6 && met >=600) _counters.at("SR28").add_event(event);

	    else if (nbjets >= 1 && njets_ak4 >=7 && met < 370) _counters.at("SR30").add_event(event);
	    else if (nbjets >= 1 && njets_ak4 >=7 && met < 450) _counters.at("SR31").add_event(event);
	    else if (nbjets >= 1 && njets_ak4 >=7 && met < 600) _counters.at("SR32").add_event(event);
	    else if (nbjets >= 1 && njets_ak4 >=7 && met >=600) _counters.at("SR33").add_event(event);
	  }
	

      }

      virtual void collect_results()
      {
        #ifdef CHECK_CUTFLOW
          cout << _cutflow << endl;
          // Note: The EventCount::sum() call below gives the raw MC event count.
          //       Use weight_sum() to get the sum of event weights.
          for (auto& pair : _counters) {
              cout << pair.first << "\t" << pair.second.sum() << endl;
          }
        #endif
	  
	  add_result(SignalRegionData(_counters.at("SR2") , 641., {626., 72.}));
	  add_result(SignalRegionData(_counters.at("SR3") , 325., {303., 40.}));
	  add_result(SignalRegionData(_counters.at("SR4") , 157., {186., 36.}));
	  add_result(SignalRegionData(_counters.at("SR5") ,  32., {48.,  8.8}));
	  add_result(SignalRegionData(_counters.at("SR6") ,  19., {19.2, 6.4}));
	  add_result(SignalRegionData(_counters.at("SR7") ,  11., {7.79, 2.16}));

	  add_result(SignalRegionData(_counters.at("SR9") ,  41., {39.0, 4.7}));
	  add_result(SignalRegionData(_counters.at("SR10"),  21., {22.7, 3.3}));
	  add_result(SignalRegionData(_counters.at("SR11") , 22., {17.7, 3.1}));
	  add_result(SignalRegionData(_counters.at("SR12") ,  4., {5.00, 1.61}));
	  add_result(SignalRegionData(_counters.at("SR13") ,  0., {4.87, 1.61}));

	  add_result(SignalRegionData(_counters.at("SR15"),   5., {7.19, 1.70}));
	  add_result(SignalRegionData(_counters.at("SR16"),   1., {3.68, 0.97}));
	  add_result(SignalRegionData(_counters.at("SR17") ,  2., {3.14, 0.86}));
	  add_result(SignalRegionData(_counters.at("SR18") ,  1., {1.66, 0.81}));

	  add_result(SignalRegionData(_counters.at("SR20"), 114., {118., 14.}));
	  add_result(SignalRegionData(_counters.at("SR21"),  58., {46.0, 6.4}));
	  add_result(SignalRegionData(_counters.at("SR22") , 35., {30.1, 5.5}));
	  add_result(SignalRegionData(_counters.at("SR23") ,  6., {9.02, 2.73}));

	  add_result(SignalRegionData(_counters.at("SR25"),  48., {42.7, 5.9}));
	  add_result(SignalRegionData(_counters.at("SR26"),  23., {17.8, 3.1}));
	  add_result(SignalRegionData(_counters.at("SR27") ,  8., {6.39, 1.46}));
	  add_result(SignalRegionData(_counters.at("SR28") ,  3., {4.81, 1.22}));

	  add_result(SignalRegionData(_counters.at("SR30"),   8., {15.2, 2.9}));
	  add_result(SignalRegionData(_counters.at("SR31"),   9., {8.07, 1.76}));
	  add_result(SignalRegionData(_counters.at("SR32") ,  3., {5.36, 1.48}));
	  add_result(SignalRegionData(_counters.at("SR33") ,  1., {1.80, 0.83}));

	  add_result(SignalRegionData(_counters.at("SR35"),  97., {103., 13.}));
	  add_result(SignalRegionData(_counters.at("SR36"),  52., {46.2, 7.2}));
	  add_result(SignalRegionData(_counters.at("SR37") , 36., {27.9, 5.2}));
	  add_result(SignalRegionData(_counters.at("SR38") ,  4., {11.9, 3.4}));
	  add_result(SignalRegionData(_counters.at("SR39") ,  2., {4.54, 2.01}));

	  add_result(SignalRegionData(_counters.at("SR41"),  60., {60.7, 8.3}));
	  add_result(SignalRegionData(_counters.at("SR42"),  34., {25.6, 4.5}));
	  add_result(SignalRegionData(_counters.at("SR43") , 20., {17.7, 3.8}));
	  add_result(SignalRegionData(_counters.at("SR44") ,  2., {7.30, 2.28}));
	  add_result(SignalRegionData(_counters.at("SR45") ,  2., {3.72, 1.66}));
      }


    protected:
      void analysis_specific_reset() {
       for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_Photon_GMSB_137invfb)


  }
}
