///
///  \author Anders Kvellestad
///  \date 2019 Apr
///
///  *********************************************

/*
  Based on:
    "Search for supersymmetry in final states with photons and missing transverse momentum in proton-proton collisions at 13 TeV"

    http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-17-011/index.html
    arxiv:1903.07070

  Notes:

    There are a lot of details missing in the paper, e.g. the exact numbers used for baseline
    object selection, isolation criteria, etc. So we have for now made some hopefully reasonable
    assumptions, to be validated when we get more info from CMS.

  Event selection summary:

    Trigger:
    - Two photons
    - Leading photon: pT > 30
    - Subleading photon: pT > 18
    - Invariant mass m_gg > 95
    - Isolation and cluster shape requirements (not implemented)

    Photon selection:
    - pT > 40
    - |eta| < 1.44
    - Isolated from other reconstructed particles by
      considering pT sum of other particles within
      DeltaR = 0.3. (Not implemented. No details given in the paper...)

    Further requirements:
    - Identify the two highest pT EM objects (gg, ee, ge)
    - Require objects to have DeltaR > 0.6
    - Require objects to have m > 105

    Vetos:
    - Any *additional* electron with pT > 25, |eta| < 2.5
    - Any muon with pT > 25, |eta| < 2.4

    Six SRs based on MET value.
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

namespace Gambit {
  namespace ColliderBit {


    class Analysis_CMS_13TeV_2Photon_GMSB_36invfb : public Analysis {
    public:

      static constexpr const char* detector = "CMS";

      // Counters for the number of accepted events for each signal region
      std::map<string, EventCounter> _counters = {
        {"SR_MET_100-115", EventCounter("SR_MET_100-115")},
        {"SR_MET_115-130", EventCounter("SR_MET_115-130")},
        {"SR_MET_130-150", EventCounter("SR_MET_130-150")},
        {"SR_MET_150-185", EventCounter("SR_MET_150-185")},
        {"SR_MET_185-250", EventCounter("SR_MET_185-250")},
        {"SR_MET_>250", EventCounter("SR_MET_>250")},
      };

      // Cutflow _cutflow;

      // Analysis_CMS_13TeV_2Photon_GMSB_36invfb():
      // _cutflow("CMS 2-photon GMSB 13 TeV", {"preselection", "MET>300GeV", "MT(g,MET)>300GeV", "S_T^g>600GeV"})
      Analysis_CMS_13TeV_2Photon_GMSB_36invfb()
      {
        set_analysis_name("CMS_13TeV_2Photon_GMSB_36invfb");
        set_luminosity(35.9);
      }


      void run(const HEPUtils::Event* event)
      {
        // Baseline objects
        // HEPUtils::P4 pTmissVector = event->missingmom();
        double met = event->met();

        // _cutflow.fillinit();

        // Photons
        // NOTE:
        //   No photon efficiency info available for this analysis.
        //   We therefore assume the same efficiency map as used for
        //   other CMS 36 fb^-1 SUSY searches:
        //
        //   https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/PhotonEfficiencies_ForPublic_Moriond2017_LoosePixelVeto.pdf
        //
        //   The efficiency map has been extended to cover the low-pT region (pT < 20)
        const vector<double> aPhoton={0., 0.8, 1.4442, 1.566, 2.0, 2.5, DBL_MAX};  // Bin edges in eta
        const vector<double> bPhoton={0., 20., 35., 50., 90., DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 500, where the CMS map stops.
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
        vector<const HEPUtils::Particle*> photons;
        for (const HEPUtils::Particle* photon : event->photons())
        {
          bool isPhoton=has_tag(_eff2dPhoton, photon->abseta(), photon->pT());
          if (isPhoton && photon->pT()>15.) photons.push_back(photon);
        }
        // Sort
        sortByPt(photons);

        // Photon trigger cut
        bool trigger = false;
        if (photons.size() >= 2) {
          double mggTrigger = (photons.at(0)->mom() + photons.at(1)->mom()).m();
          if (mggTrigger > 95.) {
            trigger = true;
          }
        }
        // // Return immediately if event didn't pass trigger
        // if (!trigger) return;


        // Electrons
        // NOTE:
        //   No electron efficiency info available for this analysis.
        //   We therefore assume the efficiency map used for the 36 fb^-1 CMS multilepton search:
        //   https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_el_039_multi_ttbar.pdf
        //
        //   See this page for more info:
        //   https://twiki.cern.ch/twiki/bin/view/CMSPublic/SUSMoriond2017ObjectsEfficiency
        //
        //   The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aEl={0., 0.8, 1.442, 1.556, 2., 2.5, DBL_MAX};   // Bin edges in eta
        const vector<double> bEl={0., 10., 15., 20., 25., 30., 40., 50., DBL_MAX}; // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cEl={
                          // pT: (0,10),  (10,15),  (15,20),  (20,25),  (25,30),  (30,40),  (40,50),  (50,inf)
                                   0.0,    0.95,    0.507,    0.619,    0.682,    0.742,    0.798,    0.863,  // eta: (0, 0.8)
                                   0.0,    0.95,    0.429,    0.546,    0.619,    0.710,    0.734,    0.833,  // eta: (0.8, 1.442)
                                   0.0,    0.95,    0.256,    0.221,    0.315,    0.351,    0.373,    0.437,  // eta: (1.442, 1.556)
                                   0.0,    0.85,    0.249,    0.404,    0.423,    0.561,    0.642,    0.749,  // eta: (1.556, 2)
                                   0.0,    0.85,    0.195,    0.245,    0.380,    0.441,    0.533,    0.644,  // eta: (2, 2.5)
                                   0.0,    0.0,     0.0,      0.0,      0.0,      0.0,      0.0,      0.0,    // eta > 2.5
                                  };
        HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
        vector<const HEPUtils::Particle*> electrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          bool isEl=has_tag(_eff2dEl, electron->abseta(), electron->pT());
          // No info in the paper on pT or |eta| cuts for baseline electrons,
          // but the above efficieny map effectively requires pT > 10 and |eta| < 2.5
          if (isEl) electrons.push_back(electron);
        }
        // Sort
        sortByPt(electrons);


        // Muons
        // NOTE:
        //   No muon efficiency info available for this analysis.
        //   We therefore assume the efficiency map used for the 36 fb^-1 CMS multilepton search:
        //   https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_mu_039_multi_ttbar.pdf
        //
        //   See this page for more info:
        //   https://twiki.cern.ch/twiki/bin/view/CMSPublic/SUSMoriond2017ObjectsEfficiency
        //
        //   The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aMu={0., 0.9, 1.2, 2.1, 2.4, DBL_MAX};   // Bin edges in eta
        const vector<double> bMu={0., 10., 15., 20., 25., 30., 40., 50., DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cMu={
                           // pT:   (0,10),  (10,15),  (15,20),  (20,25),  (25,30),  (30,40),  (40,50),  (50,inf)
                                     0.0,     0.704,    0.797,    0.855,    0.880,    0.906,    0.927,    0.931,  // eta: (0, 0.9)
                                     0.0,     0.639,    0.776,    0.836,    0.875,    0.898,    0.940,    0.930,  // eta: (0.9, 1.2)
                                     0.0,     0.596,    0.715,    0.840,    0.862,    0.891,    0.906,    0.925,  // eta: (1.2, 2.1)
                                     0.0,     0.522,    0.720,    0.764,    0.803,    0.807,    0.885,    0.877,  // eta: (2.1, 2.4)
                                     0.0,     0.0,      0.0,      0.0,      0.0,      0.0,      0.0,      0.0,    // eta > 2.4
                                 };
        HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
        vector<const HEPUtils::Particle*> muons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          bool isMu=has_tag(_eff2dMu, muon->abseta(), muon->pT());
          // No info in the paper on pT or |eta| cuts for baseline muons,
          // but the above efficieny map effectively requires pT > 10 and |eta| < 2.4
          if (isMu) muons.push_back(muon);
        }
        // Sort
        sortByPt(muons);


        // Jets
        vector<const HEPUtils::Jet*> jets;
        for (const HEPUtils::Jet* jet : event->jets()) {
          // No info on baseline jet cuts in the paper, so for now we'll
          // apply an|eta| cut for HCAL coverage and a loose jet pT cut
          if (jet->pT()>10. && jet->abseta()<3.0) jets.push_back(jet);
        }
        // Sort
        sortByPt(jets);


        // Select signal photon candidates
        vector<const HEPUtils::Particle*> signalPhotons;
        for (const HEPUtils::Particle* photon : photons)
        {
          if (photon->pT() > 15. && photon->abseta() < 1.44) signalPhotons.push_back(photon);
          // NOTE: there should also be an isolation cut based on pT sums of other objects
          // within DeltaR = 0.3 of the photon, but no details are given in the paper...
        }

        // Requirements on the two highest-pT EM objects
        vector<const HEPUtils::Particle*> EMobjects;
        EMobjects.insert(EMobjects.end(), signalPhotons.begin(), signalPhotons.end());
        EMobjects.insert(EMobjects.end(), electrons.begin(), electrons.end());
        sortByPt(EMobjects);

        vector<const HEPUtils::Particle*> signalEMobjects;
        if (EMobjects.size() < 2) {
          signalEMobjects.insert(signalEMobjects.begin(), EMobjects.begin(), EMobjects.end());
        }
        else {
          signalEMobjects.insert(signalEMobjects.begin(), EMobjects.begin(), EMobjects.begin() + 2);
        }

        bool isDiphoton = false;
        bool DeltaR_gt_06 = false;
        bool mgg_gt_105 = false;
        if (signalEMobjects.size() >= 2) {

          const HEPUtils::Particle* obj1 = signalEMobjects.at(0);
          const HEPUtils::Particle* obj2 = signalEMobjects.at(1);

          if (obj1->pid() == 22 && obj2->pid() == 22) isDiphoton = true;

          if (obj1->mom().deltaR_eta(obj2->mom()) > 0.6) DeltaR_gt_06 = true;

          if ((obj1->mom() + obj2->mom()).m() > 105.) mgg_gt_105 = true;
        }

        // Vetos on muons
        bool muVeto = false;
        for (const HEPUtils::Particle* muon : muons) {
          if (muon->pT() > 25. && muon->abseta() < 2.4) {
            muVeto = true;
            break;
          }
        }

        // Veto on electrons not part of the two signalEMobjects
        bool elVeto = false;
        for (const HEPUtils::Particle* electron : electrons) {
          if (electron->pT() > 25. && electron->abseta() < 2.5) {
            if (electron != signalEMobjects.at(0) && electron != signalEMobjects.at(1)) {
              elVeto = true;
              break;
            }
          }
        }

        // Fill signal region
        if (trigger && isDiphoton && DeltaR_gt_06 && mgg_gt_105 && !muVeto && !elVeto) {
          if      (met > 100. && met < 115) _counters.at("SR_MET_100-115").add_event(event);
          else if (met > 115. && met < 130) _counters.at("SR_MET_115-130").add_event(event);
          else if (met > 130. && met < 150) _counters.at("SR_MET_130-150").add_event(event);
          else if (met > 150. && met < 185) _counters.at("SR_MET_150-185").add_event(event);
          else if (met > 185. && met < 250) _counters.at("SR_MET_185-250").add_event(event);
          else if (met > 250.) _counters.at("SR_MET_>250").add_event(event);
        }

      }


      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_2Photon_GMSB_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2Photon_GMSB_36invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }


      virtual void collect_results()
      {
        add_result(SignalRegionData(_counters.at("SR_MET_100-115"), 105, {114., 13.}));
        add_result(SignalRegionData(_counters.at("SR_MET_115-130"), 39, {42.9, 7.5}));
        add_result(SignalRegionData(_counters.at("SR_MET_130-150"), 21, {27.3, 5.6}));
        add_result(SignalRegionData(_counters.at("SR_MET_150-185"), 21, {17.4, 4.1}));
        add_result(SignalRegionData(_counters.at("SR_MET_185-250"), 11, {10.2, 2.7}));
        add_result(SignalRegionData(_counters.at("SR_MET_>250"), 12, {5.4, 1.6}));
      }


    protected:
      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2Photon_GMSB_36invfb)


  }
}
