#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
//#include "gambit/ColliderBit/mt2w.h"

/// @todo Remove the ROOT classes...

using namespace std;

// The CMS monojet analysis (20fb^-1)

// based on: http://lanl.arxiv.org/pdf/1408.3583v1.pdf

//    Code by Martin White
//    Known issues:
//    a) No cutflow is available for validation. Other CMS cutflows with similar kinematic variables have been validated however.
//    b) Overlap removal is not applied (CMS do not use it, but we don't exactly use their particle flow technique either)
//    c) Jets here need kT radius of 0.5 not 0.4

namespace Gambit {
  namespace ColliderBit {

    class Analysis_CMS_8TeV_MONOJET_20invfb : public Analysis {
    private:

      // Numbers passing cuts
      double _num250,_num300,_num350,_num400,_num450,_num500,_num550;

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS; //=24;

      // Debug histos

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_8TeV_MONOJET_20invfb()
        : _num250(0),_num300(0),_num350(0),_num400(0),_num450(0),_num500(0),_num550(0),
          NCUTS(12)
      {
        set_analysis_name("CMS_8TeV_MONOJET_20invfb");
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
        CMS::applyElectronEff(baselineElectrons);

        // Baseline muons
        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && fabs(muon->eta()) < 2.5) {
            baselineMuons.push_back(muon);
          }
        }

        // Apply muon efficiency
        CMS::applyMuonEff(baselineMuons);

        // Baseline taus
        vector<const HEPUtils::Particle*> baselineTaus;
        for (const HEPUtils::Particle* tau : event->taus()) {
          if (tau->pT() > 20. && fabs(tau->eta()) < 2.3) {
            baselineTaus.push_back(tau);
          }
        }
        CMS::applyTauEfficiency(baselineTaus);

        vector<const HEPUtils::Jet*> baselineJets;
        vector<HEPUtils::P4> jets;

        for (const HEPUtils::Jet* jet : event->jets()) {
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
        //_numSR1, _numSR2, _numSR3;

        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 250.) _num250 += event->weight();
        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 350.) _num350 += event->weight();
        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 400.) _num400 += event->weight();
        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 450.) _num450 += event->weight();
        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 500.) _num500 += event->weight();
        if(nJets > 0 && baselineJets[0]->pT() > 110. && fabs(baselineJets[0]->eta()) < 2.4 && nJets <=2 && dPhiJ1J2 < 2.5 && nLeptons==0 && met > 550.) _num550 += event->weight();

        return;

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_8TeV_MONOJET_20invfb* specificOther
                = dynamic_cast<const Analysis_CMS_8TeV_MONOJET_20invfb*>(other);
        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (int j=0; j<NCUTS; j++)
        {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }
        _num250 += specificOther->_num250;
        _num300 += specificOther->_num300;
        _num350 += specificOther->_num350;
        _num400 += specificOther->_num400;
        _num450 += specificOther->_num450;
        _num500 += specificOther->_num500;
        _num550 += specificOther->_num550;
      }

      void collect_results()
      {

        // add_result(SignalRegionData("SR label", n_obs, {n_sig_MC, n_sig_MC_sys}, {n_bkg, n_bkg_err}));

        add_result(SignalRegionData("250", 52200., {_num250, 0}, { 51800.,  2000.}));
        add_result(SignalRegionData("300", 19800., {_num300, 0}, { 19600.,  830.}));
        add_result(SignalRegionData("350", 8320., {_num350, 0}, { 8190.,  400.}));
        add_result(SignalRegionData("400", 3830., {_num400, 0}, { 3930.,  230.}));
        add_result(SignalRegionData("450", 1830., {_num450, 0}, { 2050.,  150.}));
        add_result(SignalRegionData("500", 934., {_num500, 0}, { 1040.,  100.}));
        add_result(SignalRegionData("550", 519., {_num550, 0}, { 509.,  66.}));

        return;
      }


    protected:
      void analysis_specific_reset() {
        _num250=0; _num300=0; _num350=0; _num400=0; _num450=0; _num500=0; _num550=0;

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_8TeV_MONOJET_20invfb)


  }
}
