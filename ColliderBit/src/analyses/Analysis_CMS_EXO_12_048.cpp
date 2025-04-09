#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
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

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS; //=24;

      // Debug histos

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_EXO_12_048()
        : NCUTS(12)
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

        for (int i=0; i<NCUTS; i++) {
          cutFlowVector.push_back(0);
          cutFlowVector_str.push_back("");
        }
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

        // CUTS
        // pT(j1) > 110 GeV & eta < 2.4
        // njets <=2
        // dPhi(j1,j2) < 2.5
        // nLeptons = 0
        // met > 250
        // met > 300
        // met > 350
        // met > 400
        // met > 450
        // met > 500
        // met > 550

        cutFlowVector_str[0] = "No cuts ";
        cutFlowVector_str[1] = "pT(j1) > 110 GeV and |eta(j1)| < 2.4 ";
        cutFlowVector_str[2] = "njets <=2 ";
        cutFlowVector_str[3] = "dPhi(j1,j2) < 2.5 ";
        cutFlowVector_str[4] = "nLeptons = 0 ";
        cutFlowVector_str[5] = "met > 250 ";
        cutFlowVector_str[6] = "met > 300 ";
        cutFlowVector_str[7] = "met > 350 ";
        cutFlowVector_str[8] = "met > 400 ";
        cutFlowVector_str[9] = "met > 450 ";
        cutFlowVector_str[10] = "met > 500 ";
        cutFlowVector_str[11] = "met > 550 ";

        double dPhiJ1J2 = 5.;
        if(nJets>=2)dPhiJ1J2=acos(cos((baselineJets[0]->phi() - baselineJets[1]->phi())));


        for(int j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             (j==1 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4) ||

             (j==2 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2) ||

             (j==3 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5) ||

             (j==4 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0) ||

             (j==5 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 250.) ||

             (j==6 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 300.) ||

             (j==7 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 350.) ||

             (j==8 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 400.) ||

             (j==9 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 450.) ||

             (j==10 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 500.) ||

             (j==11 && nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 550.))

            cutFlowVector[j]++;
        }

        //We're now ready to apply the cuts for each signal region

        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 250.) _counters["250"].add_event(event);
        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 350.) _counters["350"].add_event(event);
        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 400.) _counters["400"].add_event(event);
        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 450.) _counters["450"].add_event(event);
        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 500.) _counters["500"].add_event(event);
        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 550.) _counters["550"].add_event(event);

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

        return;
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_EXO_12_048)


  }
}
