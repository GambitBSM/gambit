#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

/// @todo Remove the ROOT classes...

using namespace std;

// Renamed from: 
//        Analysis_CMS_8TeV_2LEPDMTOP_20invfb


// The CMS 2 lepton DM + top pair analysis (20fb^-1)

// based on: https://twiki.cern.ch/twiki/bin/view/CMSPublic/PhysicsResultsB2G13004

//    Code by Martin White, Guy Pitman
//    Known issues:
//    a) Impossible to test results against CMS due to the impossibility of reproducing their model information (even after contacting CMS). Note that the variables used have been debugged in other contexts however.
//    b) Overlap removal is not applied (CMS do not use it, but we don't exactly use their particle flow technique either)
//    c) Jets here need kT radius of 0.5 not 0.4
//    d) Jets go out to eta of 5: need to make sure that sim does not cut these away

namespace Gambit {
  namespace ColliderBit {


    class Analysis_CMS_B2G_13_004 : public Analysis {
    private:

      // Debug histos

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_B2G_13_004()
      {
        DEFINE_SIGNAL_REGION("SR",
                             "MET > 320 GeV",
                             "pT_j1 + pT_j2 < 400 GeV",
                             "pT_l1 + pT_l2 > 120 GeV",
                             "dPhi_ll < 2.");

        set_analysis_name("CMS_B2G_13_004");
        set_luminosity(19.7);
      }

      double SmallestdPhi(std::vector<HEPUtils::Jet *> jets,double phi_met)
      {
        if (jets.size()<2) return(999);
        double dphi1 = std::acos(std::cos(jets.at(0)->phi()-phi_met));
        double dphi2 = std::acos(std::cos(jets.at(1)->phi()-phi_met));
        // double dphi3 = 999;
        //if (jets.size() > 2 && jets[2]->pT() > 40.)
        //  dphi3 = std::acos(std::cos(jets[2]->phi() - phi_met));
        double min1 = std::min(dphi1, dphi2);

        return min1;

      }

      void run(const HEPUtils::Event* event) {

        // Missing energy
        // HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();

        // Baseline electrons
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 20. && fabs(electron->eta()) < 2.5) {
            baselineElectrons.push_back(electron);
          }
        }

        // Apply electron efficiency
        applyEfficiency(baselineElectrons, CMS::eff2DEl.at("Generic"));

        // Baseline muons
        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 20. && fabs(muon->eta()) < 2.4) {
            baselineMuons.push_back(muon);
          }
        }

        // Apply muon efficiency
        applyEfficiency(baselineMuons, CMS::eff2DMu.at("Generic"));

        // All baseline leptons
        vector<const HEPUtils::Particle*> baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end() );

        vector<const HEPUtils::Jet*> baselineJets;
        vector<HEPUtils::P4> jets;
        vector<const HEPUtils::Jet*> bJets;
        vector<bool> btag;

        const std::vector<double>  a = {0,10.};
        const std::vector<double>  b = {0,10000.};
        const std::vector<double> c = {0.60};
        HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);

        for (const HEPUtils::Jet* jet : event->jets("antikt_R04")) {
          if (jet->pT() > 30. && fabs(jet->eta()) < 5.0) {
            baselineJets.push_back(jet);
            //LorentzVector j1 (jet->mom().px(),jet->mom().py(),jet->mom().pz(),jet->mom().E()) ;
            jets.push_back(jet->mom());
            bool hasTag=has_tag(_eff2d, fabs(jet->eta()), jet->pT());
            bool isB=false;

            if(jet->btag() && hasTag && fabs(jet->eta()) < 2.4 && jet->pT() > 30.) {
              isB=true;
              bJets.push_back(jet);
            }
            btag.push_back(isB);
          }
        }

        // Calculate common variables and cuts first
        //applyTightIDElectronSelection(signalElectrons);

        //int nElectrons = signalElectrons.size();
        //int nMuons = signalMuons.size();
        int nJets = baselineJets.size();
        int nLeptons = baselineLeptons.size();
        // int nBJets = bJets.size();

        //Preselection cuts

        bool passMll=true;
        if(baselineElectrons.size()==2 && baselineMuons.size()==0){
          double mll=(baselineElectrons[0]->mom()+baselineElectrons[1]->mom()).m();
          if(mll<=20.)passMll=false;
          if(fabs(mll-91.)<=15.)passMll=false;
        }

        if(baselineMuons.size()==2 && baselineElectrons.size()==0){
          double mll=(baselineMuons[0]->mom()+baselineMuons[1]->mom()).m();
          if(mll<=20.)passMll=false;
          if(fabs(mll-91.)<=15.)passMll=false;
        }

        bool passPresel=false;
        if(nLeptons==2 &&
           nJets>=2 &&
           passMll)passPresel=true;

        //Cuts

        // met > 320 GeV
        // Scalar sum of leading 2 jet pTs < 400 GeV
        // Scalar sum of pT of leptons > 120 GeV
        // dPhi_ll < 2.

        double jetPtSum=0;
        if(nJets>=2)jetPtSum=baselineJets[0]->pT()+baselineJets[1]->pT();
        double lepPtSum=0;
        if(baselineLeptons.size()==2)lepPtSum=baselineLeptons[0]->pT()+baselineLeptons[1]->pT();

        double dPhiLL=99.;
        if(baselineLeptons.size()==2)dPhiLL=acos(cos((baselineLeptons[0]->phi() - baselineLeptons[1]->phi())));

        const bool passMet = met > 320.;
        const bool passJetPtSum = jetPtSum < 400.;
        const bool passLepPtSum = lepPtSum > 120.;
        const bool passDPhiLL = dPhiLL < 2.;
        const bool passSR = passPresel && passMet && passJetPtSum && passLepPtSum && passDPhiLL;

        #ifdef CHECK_CUTFLOW
          const double w = event->weight();
          _cutflows["SR"].fillinit(w);
          _cutflows["SR"].fillnext(std::vector<bool>{passPresel, passMet, passJetPtSum, passLepPtSum, passDPhiLL}, w);
        #endif

        //We're now ready to apply the cuts for each signal region

        if (passSR)
        {
          FILL_SIGNAL_REGION("SR")
        }

        return;
      }



      double loglikelihood() {
        /// @todo Implement!
        return 0;
      }

      void collect_results() {

        COMMIT_SIGNAL_REGION("SR", 1., 1.89, 0.66)
COMMIT_CUTFLOWS
        return;
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_B2G_13_004)


  }
}
