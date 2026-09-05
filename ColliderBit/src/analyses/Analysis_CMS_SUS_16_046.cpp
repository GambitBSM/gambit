///
///  \author Yang Zhang
///  \date 2019 Jan
///
///  *********************************************

// Based on http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-16-046/index.html
// Search for gauge-mediated supersymmetry in events with at least one photon and missing transverse momentum in pp collisions at s√= 13 TeV

/*
  Note:
        Isolation of photons and jets are not performed.
*/

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

// #define CHECK_CUTFLOW

using namespace std;

// Renamed from: 
//        Analysis_CMS_13TeV_Photon_GMSB_36invfb

namespace Gambit {
  namespace ColliderBit {


    class Analysis_CMS_SUS_16_046 : public Analysis {
    public:

      static constexpr const char* detector = "CMS";
      static constexpr const char* CUTFLOW_NAME = "CMS-SUS-16-046";

      Analysis_CMS_SUS_16_046()
      {
        #ifdef CHECK_CUTFLOW
        _cutflows.addCutflow(CUTFLOW_NAME, {"preselection", "MET>300GeV", "MT(g,MET)>300GeV", "S_T^g>600GeV"});
        #endif

        // Counters for the number of accepted events for each signal region
        _counters["SR-600-800"] = EventCounter("SR-600-800");
        _counters["SR-800-1000"] = EventCounter("SR-800-1000");
        _counters["SR-1000-1300"] = EventCounter("SR-1000-1300");
        _counters["SR-1300"] = EventCounter("SR-1300");


        set_analysis_name("CMS_SUS_16_046");
        set_luminosity(35.9);
      }


      void run(const HEPUtils::Event* event)
      {
        // Baseline objects
        HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();
        #ifdef CHECK_CUTFLOW
        _cutflows[CUTFLOW_NAME].fillinit();
        #endif

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
          if (isPhoton && photon->pT()>15.) Photons.push_back(photon);
        }


        // jets
        vector<const HEPUtils::Jet*> Jets;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT()>30. &&fabs(jet->eta())<3.0) Jets.push_back(jet);
        }
        // TODO: Apply jets isolation instead of removeOverlap.
        removeOverlap(Jets, Photons, 0.2);

        // Preselection
        bool high_pT_photon = false;  // At least one high-pT photon;
        bool delta_R_g_j = false;     // Photons are required to have delta_R>0.5 to the nearest jet;
        bool delta_phi_j_MET = false; // Jets with pT>100 GeV must fulfill delta_phi(MET,jet)>0.3;
        for (const HEPUtils::Particle* photon  : Photons){
            if (photon->pT()>180. && fabs(photon->eta()) < 1.44) {
                high_pT_photon = true;
                for (const HEPUtils::Jet* jet : Jets){
                    if ( jet->mom().deltaR_eta(photon->mom()) < 0.5 ) delta_R_g_j=true;
                }
            }
        }
        if (not high_pT_photon) return;
        if (delta_R_g_j) return;
        for (const HEPUtils::Jet* jet : Jets){
            if (jet->pT()>100. && jet->mom().deltaPhi(ptot) < 0.3 ) delta_phi_j_MET=true;
        }
        if (delta_phi_j_MET) return;
        #ifdef CHECK_CUTFLOW
        _cutflows[CUTFLOW_NAME].fill(1);
        #endif


        // MET > 300 GeV
        if (met<300)return;
        #ifdef CHECK_CUTFLOW
        _cutflows[CUTFLOW_NAME].fill(2);
        #endif

        // MT(photon,MET) > 300 GeV
        double MT = sqrt(2.*Photons[0]->pT()*met*(1. - std::cos(Photons[0]->mom().deltaPhi(ptot)) ));
        if (MT<300)return;
        #ifdef CHECK_CUTFLOW
        _cutflows[CUTFLOW_NAME].fill(3);
        #endif

        // S_T^gamma > 600 GeV
        double STgamma = met;
        for (const HEPUtils::Particle* photon  : Photons){
            STgamma += photon->pT();
        }
        if (STgamma<600) return;
        #ifdef CHECK_CUTFLOW
        _cutflows[CUTFLOW_NAME].fill(4);
        #endif

        // Signal regions
        if      (STgamma<800)  _counters.at("SR-600-800").add_event(event);
        else if (STgamma<1000) _counters.at("SR-800-1000").add_event(event);
        else if (STgamma<1300) _counters.at("SR-1000-1300").add_event(event);
        else                   _counters.at("SR-1300").add_event(event);

      }


      virtual void collect_results()
      {
        add_result(SignalRegionData(_counters.at("SR-600-800")  , 281., {267,  27.2}));
        add_result(SignalRegionData(_counters.at("SR-800-1000") , 101., {100.2,10.8}));
        add_result(SignalRegionData(_counters.at("SR-1000-1300"),  65., {52.8, 6.16}));
        add_result(SignalRegionData(_counters.at("SR-1300")     ,  24., {17.6, 2.76}));

COMMIT_CUTFLOWS;
      }


    protected:
      void analysis_specific_reset() {
       for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_16_046)


  }
}
