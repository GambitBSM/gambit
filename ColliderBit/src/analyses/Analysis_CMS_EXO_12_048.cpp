#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
//#include "gambit/ColliderBit/mt2w.h"

/// @todo Remove the ROOT classes...

using namespace std;

// Renamed from: 
//        Analysis_CMS_8TeV_MONOJET_20invfb

// The CMS monojet analysis (20fb^-1)

// based on: http://lanl.arxiv.org/pdf/1408.3583v1.pdf

//    Code by Martin White
//    Known issues:
//    a) No cutflow is available for validation. Other CMS cutflows with similar kinematic variables have been validated however.
//    b) Overlap removal is not applied (CMS do not use it, but we don't exactly use their particle flow technique either)
//    c) Jets here need kT radius of 0.5 not 0.4

namespace Gambit {
  namespace ColliderBit {

    class Analysis_CMS_EXO_12_048 : public Analysis {
    private:
      static constexpr const char* CUTFLOW_NAME = "CMS-EXO-12-048";

      // Debug histos

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_EXO_12_048()
      {

        // Numbers passing cuts
        _counters["250"] = EventCounter("250");
        _counters["300"] = EventCounter("300");
        _counters["350"] = EventCounter("350");
        _counters["400"] = EventCounter("400");
        _counters["450"] = EventCounter("450");
        _counters["500"] = EventCounter("500");
        _counters["550"] = EventCounter("550");

        set_analysis_name("CMS_EXO_12_048");
        set_luminosity(19.7);

        #ifdef CHECK_CUTFLOW
        _cutflows.addCutflow(CUTFLOW_NAME, {
          "pT(j1) > 110 GeV and |eta(j1)| < 2.4",
          "njets <=2",
          "dPhi(j1,j2) < 2.5",
          "nLeptons = 0",
          "met > 250",
          "met > 300",
          "met > 350",
          "met > 400",
          "met > 450",
          "met > 500",
          "met > 550"
        });
        #endif
      }

      double SmallestdPhi(std::vector<HEPUtils::Jet *> jets,double phi_met)
      {
        if (jets.size()<2) return(999);
        double dphi1 = std::acos(std::cos(jets.at(0)->phi()-phi_met));
        double dphi2 = std::acos(std::cos(jets.at(1)->phi()-phi_met));
        //double dphi3 = 999;
        //if (jets.size() > 2 && jets[2]->pT() > 40.)
        //  dphi3 = std::acos(std::cos(jets[2]->phi() - phi_met));
        double min1 = std::min(dphi1, dphi2);

        return min1;

      }

      void run(const HEPUtils::Event* event) {

        // Missing energy
        //HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();

        // Now define vectors of baseline objects

        // Baseline electrons
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && fabs(electron->eta()) < 2.5) {
            baselineElectrons.push_back(electron);
          }
        }

        // Apply electron efficiency
        applyEfficiency(baselineElectrons, CMS::eff2DEl.at("Generic"));

        // Baseline muons
        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && fabs(muon->eta()) < 2.5) {
            baselineMuons.push_back(muon);
          }
        }

        // Apply muon efficiency
        applyEfficiency(baselineMuons, CMS::eff2DMu.at("Generic"));

        // Baseline taus
        vector<const HEPUtils::Particle*> baselineTaus;
        for (const HEPUtils::Particle* tau : event->taus()) {
          if (tau->pT() > 20. && fabs(tau->eta()) < 2.3) {
            baselineTaus.push_back(tau);
          }
        }
        applyEfficiency(baselineTaus, CMS::effTau.at("Generic"));

        vector<const HEPUtils::Jet*> baselineJets;
        vector<HEPUtils::P4> jets;

        for (const HEPUtils::Jet* jet : event->jets("antikt_R04")) {
          if (jet->pT() > 30. && fabs(jet->eta()) < 4.5) {
            baselineJets.push_back(jet);
          }
        }

        // Calculate common variables and cuts first
        //applyTightIDElectronSelection(signalElectrons);

        //int nElectrons = signalElectrons.size();
        //int nMuons = signalMuons.size();
        int nJets = baselineJets.size();
        int nLeptons = baselineElectrons.size()+baselineMuons.size()+baselineTaus.size();

        double dPhiJ1J2 = 5.;
        if(nJets>=2)dPhiJ1J2=acos(cos((baselineJets[0]->phi() - baselineJets[1]->phi())));
        const bool cut_j1 = nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4;
        const bool cut_njets = cut_j1 && nJets <= 2;
        const bool cut_dphi = cut_njets && dPhiJ1J2 < 2.5;
        const bool cut_nleptons = cut_dphi && nLeptons == 0;
        const bool cut_met250 = cut_nleptons && met > 250.;
        const bool cut_met300 = cut_nleptons && met > 300.;
        const bool cut_met350 = cut_nleptons && met > 350.;
        const bool cut_met400 = cut_nleptons && met > 400.;
        const bool cut_met450 = cut_nleptons && met > 450.;
        const bool cut_met500 = cut_nleptons && met > 500.;
        const bool cut_met550 = cut_nleptons && met > 550.;

        #ifdef CHECK_CUTFLOW
        const double w = event->weight();
        _cutflows[CUTFLOW_NAME].fillinit(w);
        _cutflows[CUTFLOW_NAME].fillnext({
          cut_j1,
          cut_njets,
          cut_dphi,
          cut_nleptons,
          cut_met250,
          cut_met300,
          cut_met350,
          cut_met400,
          cut_met450,
          cut_met500,
          cut_met550
        }, w);
        #endif

        //We're now ready to apply the cuts for each signal region

        if(cut_met250) _counters["250"].add_event(event);
        if(cut_met350) _counters["350"].add_event(event);
        if(cut_met400) _counters["400"].add_event(event);
        if(cut_met450) _counters["450"].add_event(event);
        if(cut_met500) _counters["500"].add_event(event);
        if(cut_met550) _counters["550"].add_event(event);

        return;

      }


      void collect_results()
      {

        add_result(SignalRegionData(_counters["250"], 52200., { 51800.,  2000.}));
        add_result(SignalRegionData(_counters["300"], 19800., { 19600.,  830.}));
        add_result(SignalRegionData(_counters["350"], 8320., { 8190.,  400.}));
        add_result(SignalRegionData(_counters["400"], 3830., { 3930.,  230.}));
        add_result(SignalRegionData(_counters["450"], 1830., { 2050.,  150.}));
        add_result(SignalRegionData(_counters["500"], 934., { 1040.,  100.}));
        add_result(SignalRegionData(_counters["550"], 519., { 509.,  66.}));

        #ifdef CHECK_CUTFLOW
        COMMIT_CUTFLOWS;
        #endif

        return;
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_EXO_12_048)


  }
}
