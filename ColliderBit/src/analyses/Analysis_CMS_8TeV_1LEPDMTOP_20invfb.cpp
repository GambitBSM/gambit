#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/mt2w.h"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

using namespace std;

// The CMS 1 lepton DM + top pair analysis (20fb^-1)

// based on: https://twiki.cern.ch/twiki/bin/view/CMSPublic/PhysicsResultsB2G14004

//    Code by Martin White, Guy Pitman
//    Known issues:
//    a) Impossible to test results against CMS due to the impossibility of reproducing their model information (even after contacting CMS). Note that the variables used have been debugged in other contexts however.
//    b) Overlap removal is not applied (CMS do not use it, but we don't exactly use their particle flow technique either)
//    c) Jets here need kT radius of 0.5 not 0.4

namespace Gambit {
  namespace ColliderBit {



    //Puts dphi in the range -pi to pi
    double _Phi_mpi_pi(double x){
      while (x >= M_PI) x -= 2*M_PI;
      while (x < -M_PI) x += 2*M_PI;
      return x;
    }


    class Analysis_CMS_8TeV_1LEPDMTOP_20invfb : public Analysis {
    private:

      // Numbers passing cuts
      int _numSR;

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS; //=24;

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_8TeV_1LEPDMTOP_20invfb()
        : _numSR(0),
          NCUTS(6)
      {
        set_analysis_name("CMS_8TeV_1LEPDMTOP_20invfb");
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
        // double dphi3 = 999;
        //if (jets.size() > 2 && jets[2]->pT() > 40.)
        //  dphi3 = std::acos(std::cos(jets[2]->phi() - phi_met));
        double min1 = std::min(dphi1, dphi2);

        return min1;

      }

      void run(const HEPUtils::Event* event) {

        // Missing energy
        HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();

        // Baseline electrons
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 30. && fabs(electron->eta()) < 2.5) {
            baselineElectrons.push_back(electron);
          }
        }

        // Apply electron efficiency
        CMS::applyElectronEff(baselineElectrons);

        // Baseline muons
        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 30. && fabs(muon->eta()) < 2.1) {
            baselineMuons.push_back(muon);
          }
        }

        // Apply muon efficiency
        CMS::applyMuonEff(baselineMuons);

        // All baseline leptons
        vector<HEPUtils::Particle*> baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end() );

        vector<HEPUtils::Jet*> baselineJets;
        //vector<LorentzVector> jets;
        vector<HEPUtils::P4> jets;
        vector<HEPUtils::Jet*> bJets;
        vector<bool> btag;

        const std::vector<double>  a = {0,10.};
        const std::vector<double>  b = {0,10000.};
        const std::vector<double> c = {0.60};
        HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);

        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 30. && fabs(jet->eta()) < 4.0) {
            baselineJets.push_back(jet);
            //LorentzVector j1 (jet->mom().px(),jet->mom().py(),jet->mom().pz(),jet->mom().E()) ;
            //jets.push_back(j1);
            jets.push_back(jet->mom());
            bool hasTag=has_tag(_eff2d, jet->eta(), jet->pT());
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
        int nBJets = bJets.size();

        //Preselection cuts
        bool passPresel=false;
        if(nLeptons==1 &&
           nJets>=3 &&
           nBJets>=1 &&
           met > 160.)passPresel=true;

        //Calculate mT
        HEPUtils::P4 lepVec;
        double mT=0;
        if(nLeptons==1){
          lepVec=baselineLeptons[0]->mom();
          mT=sqrt(2.*lepVec.pT()*met*(1. - cos(_Phi_mpi_pi(lepVec.phi()-ptot.phi()))));
        }

        //Calculate MT2W
        double MT2W=0;
        // double MT2W_HU=0;
        if (nJets > 1 && nLeptons==1) {
          HEPUtils::P4 lepVec;
          lepVec=baselineLeptons[0]->mom();
          //LorentzVector lep (lepVec.px(),lepVec.py(),lepVec.pz(),lepVec.E());
          float phi=float (ptot.phi());
          //MT2W=calculateMT2w(jets, btag, lep, met, phi);
          MT2W=calculateMT2wHepUtils(jets,btag,lepVec,met,phi);
        }

        //Calculate dPhi variable
        float  phi=float (ptot.phi());
        double dPhiMin12=SmallestdPhi(baselineJets,phi);

        //Cuts
        //MET > 320
        //MT > 160
        //MT2W > 300
        //dPhiMin12 > 1.2

        cutFlowVector_str[0] = "No cuts ";
        cutFlowVector_str[1] = "Presel ";
        cutFlowVector_str[2] = "MET > 320 GeV ";
        cutFlowVector_str[3] = "MT > 160 GeV ";
        cutFlowVector_str[4] = "MT2W > 300 GeV ";
        cutFlowVector_str[5] = "dPhiMin12 > 1.2 ";

        for(int j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             (j==1 && passPresel) ||

             (j==2 && passPresel && met > 320.) ||

             (j==3 && passPresel && met > 320. && mT > 160.) ||

             (j==4 && passPresel && met > 320. && mT > 160. && MT2W > 300.) ||

             (j==5 && passPresel && met > 320. && mT > 160. && MT2W > 300. && dPhiMin12 > 1.2))

            cutFlowVector[j]++;
        }

        //We're now ready to apply the cuts for each signal region
        //_numSR1, _numSR2, _numSR3;

        if(passPresel && met > 320. && mT > 160. && MT2W > 300. && dPhiMin12 > 1.2)_numSR++;

        return;
      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_8TeV_1LEPDMTOP_20invfb* specificOther
          = dynamic_cast<const Analysis_CMS_8TeV_1LEPDMTOP_20invfb*>(other);
        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (int j=0; j<NCUTS; j++) {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }
        _numSR += specificOther->_numSR;
      }


      double loglikelihood() {
        /// @todo Implement!
        return 0;
      }

      void collect_results() {
        SignalRegionData results_SR;
        results_SR.sr_label = "SR";
        results_SR.n_observed = 18.;
        results_SR.n_background = 16.4;
        results_SR.background_sys = 3.48;
        results_SR.signal_sys = 0.;
        results_SR.n_signal = _numSR;

        add_result(results_SR);

        return;
      }


    protected:
      void analysis_specific_reset() {
        _numSR = 0;
        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_8TeV_1LEPDMTOP_20invfb)


  }
}
