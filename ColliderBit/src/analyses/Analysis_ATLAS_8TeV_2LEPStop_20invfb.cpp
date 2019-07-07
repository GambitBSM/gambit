#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

/// @todo Remove the ROOT classes...

using namespace std;

// The ATLAS 2 lepton direct stop analysis (20fb^-1) - `heavy stop'.

// based on: arXiv: 1403.4853

//    Code by Martin White, Sky French.
//    Known errors:
//    a) The isolation is already applied in the simulation rather than after overlap removal -> the electron and muon veto technically require a veto on base-line electrons/muons not overlapping with jets

//    Known features:
//    a) Must run simulator with 70% b tagging efficiency and ?% mis-id rate

namespace Gambit {
  namespace ColliderBit {


    //Puts dphi in the range -pi to pi
    double Phi_mpi_pi(double x){
      while (x >= M_PI) x -= 2*M_PI;
      while (x < -M_PI) x += 2*M_PI;
      return x;
    }


    class Analysis_ATLAS_8TeV_2LEPStop_20invfb : public Analysis {
    private:

      // Numbers passing cuts
      int _numSRM90SF, _numSRM100SF, _numSRM110SF, _numSRM120SF,
          _numSRM90DF, _numSRM100DF, _numSRM110DF, _numSRM120DF;

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS; //=24;

      // Debug histos

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_8TeV_2LEPStop_20invfb()
        : _numSRM90SF(0), _numSRM100SF(0), _numSRM110SF(0), _numSRM120SF(0),
          _numSRM90DF(0), _numSRM100DF(0), _numSRM110DF(0), _numSRM120DF(0),
          NCUTS(24)
      {

        set_analysis_name("ATLAS_8TeV_2LEPStop_20invfb");
        set_luminosity(20.3);

        for (int i=0; i<NCUTS; i++) {
          cutFlowVector.push_back(0);
          cutFlowVector_str.push_back("");
        }
      }

      void run(const HEPUtils::Event* event) {

        // Missing energy
        HEPUtils::P4 ptot = event->missingmom();
        //double met = event->met();

        // Now define vector of baseline electrons
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);

        // Now define vector of baseline muons
        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && muon->abseta() < 2.4) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);

        vector<HEPUtils::Particle*> baselineTaus;
        for (HEPUtils::Particle* tau : event->taus()) {
          if (tau->pT() > 10. && tau->abseta() < 2.47) baselineTaus.push_back(tau);
        }
        ATLAS::applyTauEfficiencyR1(baselineTaus);

        vector<HEPUtils::Jet*> baselineJets;
        vector<HEPUtils::Jet*> bJets;
        vector<HEPUtils::Jet*> trueBJets; //for debugging
        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 2.5) baselineJets.push_back(jet);
          if(jet->btag() && fabs(jet->eta()) < 2.5 && jet->pT() > 20.) bJets.push_back(jet);
        }

        // Overlap removal
        vector<HEPUtils::Particle*> signalLeptons;
        vector<HEPUtils::Particle*> signalElectrons;
        vector<HEPUtils::Particle*> signalMuons;
        vector<HEPUtils::Particle*> electronsForVeto;
        vector<HEPUtils::Particle*> muonsForVeto;
        vector<HEPUtils::Jet*> goodJets;
        vector<HEPUtils::Jet*> signalJets;

        //Note that ATLAS use |eta|<10 for removing jets close to electrons
        //Then 2.8 is used for the rest of the overlap process
        //Then the signal cut is applied for signal jets

        // Remove any jet within dR=0.2 of an electrons
        for (size_t iJet=0;iJet<baselineJets.size();iJet++) {
          bool overlap=false;
          HEPUtils::P4 jetVec=baselineJets.at(iJet)->mom();
          for (size_t iEl=0;iEl<baselineElectrons.size();iEl++) {
            HEPUtils::P4 elVec=baselineElectrons.at(iEl)->mom();
            if (fabs(elVec.deltaR_eta(jetVec))<0.2)overlap=true;
          }
          if (!overlap&&fabs(baselineJets.at(iJet)->eta())<2.5)goodJets.push_back(baselineJets.at(iJet));
          if (!overlap&&fabs(baselineJets.at(iJet)->eta())<2.5 && baselineJets.at(iJet)->pT()>20.)signalJets.push_back(baselineJets.at(iJet));
        }

        // Remove electrons with dR=0.4 or surviving jets
        for (size_t iEl=0;iEl<baselineElectrons.size();iEl++) {
          bool overlap=false;
          HEPUtils::P4 elVec=baselineElectrons.at(iEl)->mom();
          for (size_t iJet=0;iJet<goodJets.size();iJet++) {
            HEPUtils::P4 jetVec=goodJets.at(iJet)->mom();
            if (fabs(elVec.deltaR_eta(jetVec))<0.4)overlap=true;
          }
          if (!overlap && elVec.pT()>10.) {
            signalElectrons.push_back(baselineElectrons.at(iEl));
            signalLeptons.push_back(baselineElectrons.at(iEl));
          }
          if(!overlap)electronsForVeto.push_back(baselineElectrons.at(iEl));
        }

        // Remove muons with dR=0.4 or surviving jets
        for (size_t iMu=0;iMu<baselineMuons.size();iMu++) {
          bool overlap=false;

          HEPUtils::P4 muVec=baselineMuons.at(iMu)->mom();

          for (size_t iJet=0;iJet<goodJets.size();iJet++) {
            HEPUtils::P4 jetVec=goodJets.at(iJet)->mom();
            if (fabs(muVec.deltaR_eta(jetVec))<0.4){
              overlap=true;
            }
          }
          if (!overlap && muVec.pT()>10.) {
            signalMuons.push_back(baselineMuons.at(iMu));
            signalLeptons.push_back(baselineMuons.at(iMu));
          }
          if(!overlap)muonsForVeto.push_back(baselineMuons.at(iMu));
        }

        // We now have the signal electrons, muons, jets and b jets- move on to the analysis

        // Calculate common variables and cuts first
        ATLAS::applyTightIDElectronSelection(signalElectrons);

        //int nElectrons = signalElectrons.size();
        //int nMuons = signalMuons.size();
        int nJets = signalJets.size();
        int nLeptons = signalLeptons.size();

        bool isOS=false;
        bool isMLL=false;
        bool isZsafe=false;
        bool ispT=false;
        bool isdphi=false;
        bool isdphib=false;


        //Calculate MT2
        if (nLeptons==2) {


          if(((signalLeptons.at(0)->pid()<0 && signalLeptons.at(1)->pid()>0) || (signalLeptons.at(0)->pid()>0 && signalLeptons.at(1)->pid()<0))) isOS=true;

          if((signalLeptons[0]->mom()+signalLeptons[1]->mom()).m()>20.) isMLL=true;

          if(fabs((signalLeptons[0]->mom()+signalLeptons[1]->mom()).m()-91.)>20.) isZsafe=true;

          if(signalLeptons[0]->mom().pT()>25. || signalLeptons[1]->mom().pT()>25) ispT=true;

          double dphi_jetmetclose = 9999.;
          for(int j=0; j<nJets; j++) {
            //double temp = std::acos(std::cos(signalJets.at(j)->phi()-ptot.phi()));
            double temp = Phi_mpi_pi(signalJets.at(j)->phi()-ptot.phi());
            if(fabs(temp)<dphi_jetmetclose) {
              dphi_jetmetclose = temp;
            }
          }
          if(fabs(dphi_jetmetclose)>1.0) isdphi=true;

          HEPUtils::P4 ptllmet;
          ptllmet = signalLeptons[0]->mom() + signalLeptons[1]->mom() + ptot;

          //double temp = ptllmet.deltaPhi(ptot);
          double temp=ptllmet.phi()-ptot.phi();
          double dphib=Phi_mpi_pi((double)temp);


          if(fabs(dphib)<1.5) isdphib=true;

        }



        //if(leptonsForVeto.size()>0 && leptonsForVeto[0]->pT()>25.)cout << "Leptons size " << leptonsForVeto.size() << " muons " << nMuons << " electrons " << nElectrons << endl;

        //Common preselection for all signal regions
        bool passJetCut=false;
        //bool passBJetCut=false;

        if(nJets>=2){
          if(signalJets[0]->pT() > 100.
             && signalJets[1]->pT() > 50.)passJetCut=true;
        }

        //Calculate MT2
        double mt2ll=0;
        if(nLeptons==2){
          double pa_a[3] = { 0, signalLeptons[0]->mom().px(), signalLeptons[0]->mom().py() };
          double pb_a[3] = { 0, signalLeptons[1]->mom().px(), signalLeptons[1]->mom().py() };
          double pmiss_a[3] = { 0, ptot.px(), ptot.py() };
          double mn_a = 0.;

          mt2_bisect::mt2 mt2_event_a;

          mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
          mt2_event_a.set_mn(mn_a);

          mt2ll = mt2_event_a.get_mt2();
        }

        bool cut_2leptons_ee=false;
        bool cut_2leptons_emu=false;
        bool cut_2leptons_mumu=false;
        bool cut_2leptons_base=false;
        bool cut_2leptons=false;
        bool cut_2jets=false;
        bool cut_MT290=false;
        bool cut_MT2100=false;
        bool cut_MT2110=false;
        bool cut_MT2120=false;

        if(mt2ll>90) cut_MT290=true;
        if(mt2ll>100) cut_MT2100=true;
        if(mt2ll>110) cut_MT2110=true;
        if(mt2ll>120) cut_MT2120=true;

        if((baselineElectrons.size()+baselineMuons.size())==2) cut_2leptons_base=true;
        if((signalElectrons.size()+signalMuons.size())==2) cut_2leptons=true;
        if(signalElectrons.size()==2 && signalMuons.size()==0) cut_2leptons_ee=true;
        if(signalElectrons.size()==1 && signalMuons.size()==1) cut_2leptons_emu=true;
        if(signalElectrons.size()==0 && signalMuons.size()==2) cut_2leptons_mumu=true;

        if(passJetCut)cut_2jets=true;

        cutFlowVector_str[0] = "No cuts ";
        cutFlowVector_str[1] = "2 Baseline Leptons ";
        cutFlowVector_str[2] = "2 SF Signal Leptons";
        cutFlowVector_str[3] = "2 OS SF Signal Leptons ";
        cutFlowVector_str[4] = "mll > 20 GeV ";
        cutFlowVector_str[5] = "leading lepton pT ";
        cutFlowVector_str[6] = "|mll-mZ|>20 GeV ";
        cutFlowVector_str[7] = "dphi_min > 1.0 ";
        cutFlowVector_str[8] = "dphib < 1.5  ";
        cutFlowVector_str[9] = "SR M90 [SF] ";
        cutFlowVector_str[10] = "SR M120 [SF] ";
        cutFlowVector_str[11] = "SR M100 + 2 jets [SF] ";
        cutFlowVector_str[12] = "SR M110 + 2 jets [SF] ";
        cutFlowVector_str[13] = "2 DF Signal Leptons";
        cutFlowVector_str[14] = "2 OS DF Signal Leptons ";
        cutFlowVector_str[15] = "mll > 20 GeV ";
        cutFlowVector_str[16] = "leading lepton pT ";
        cutFlowVector_str[17] = "dphi_min > 1.0 ";
        cutFlowVector_str[18] = "dphib < 1.5  ";
        cutFlowVector_str[19] = "SR M90 [DF] ";
        cutFlowVector_str[20] = "SR M120 [DF] ";
        cutFlowVector_str[21] = "SR M100 + 2 jets[DF] ";
        cutFlowVector_str[22] = "SR M110 + 2 jets[DF] ";

        for(int j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             (j==1 && cut_2leptons_base) ||

             (j==2 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu)) ||

             (j==3 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS) ||

             (j==4 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS && isMLL) ||

             (j==5 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS && isMLL && ispT) ||

             (j==6 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe) ||

             (j==7 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe && isdphi) ||

             (j==8 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe && isdphi && isdphib) ||

             (j==9 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe && isdphi && isdphib && cut_MT290) ||

             (j==10 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee ||cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe && isdphi && isdphib && cut_MT2120) ||

             (j==11 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee ||cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe && isdphi && isdphib && cut_MT2100 && cut_2jets) ||

             (j==12 && cut_2leptons_base && cut_2leptons && (cut_2leptons_ee ||cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe && isdphi && isdphib && cut_MT2110 && nJets>=2) ||

             (j==13 && cut_2leptons && cut_2leptons_emu) ||

             (j==14 && cut_2leptons && cut_2leptons_emu && isOS) ||

             (j==15 && cut_2leptons && cut_2leptons_emu && isOS && isMLL) ||

             (j==16 && cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT) ||

             (j==17 && cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT && isdphi) ||

             (j==18 && cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT && isdphi && isdphib) ||

             (j==19 && cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT && isdphi && isdphib && cut_MT290) ||

             (j==20 && cut_2leptons_base && cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT && isdphi && isdphib && cut_MT2100 && cut_2jets) ||

             (j==21 && cut_2leptons_base && cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT && isdphi && isdphib && cut_MT2110 && nJets>=2) ||

             (j==22 && cut_2leptons_base && cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT && isdphi && isdphib && cut_MT2120 && nJets>=2) )

            cutFlowVector[j]++;
        }

        //We're now ready to apply the cuts for each signal region
        //_numSR1, _numSR2, _numSR3;

        if(cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe && isdphi && isdphib && cut_MT290) _numSRM90SF++;
        if(cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe && isdphi && isdphib && cut_MT2100 && cut_2jets) _numSRM100SF++;
        if(cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe && isdphi && isdphib && cut_MT2110 && nJets>=2) _numSRM110SF++;
        if(cut_2leptons_base && cut_2leptons && (cut_2leptons_ee || cut_2leptons_mumu) && isOS && isMLL && ispT && isZsafe && isdphi && isdphib && cut_MT2120) _numSRM120SF++;

        if(cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT && isdphi && isdphib && cut_MT290) _numSRM90DF++;
        if(cut_2leptons_base && cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT && isdphi && isdphib && cut_MT2100 && cut_2jets) _numSRM100DF++;
        if(cut_2leptons_base && cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT && isdphi && isdphib && cut_MT2110 && nJets>=2) _numSRM110DF++;
        if(cut_2leptons_base && cut_2leptons && cut_2leptons_emu && isOS && isMLL && ispT && isdphi && isdphib && cut_MT2120) _numSRM120DF++;

        return;
      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_8TeV_2LEPStop_20invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_8TeV_2LEPStop_20invfb*>(other);

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (int j=0; j<NCUTS; j++) {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }
         _numSRM90SF +=  specificOther->_numSRM90SF;
        _numSRM100SF += specificOther->_numSRM100SF;
        _numSRM110SF += specificOther->_numSRM110SF;
        _numSRM120SF += specificOther->_numSRM120SF;
         _numSRM90DF +=  specificOther->_numSRM90DF;
        _numSRM100DF += specificOther->_numSRM100DF;
        _numSRM110DF += specificOther->_numSRM110DF;
        _numSRM120DF += specificOther->_numSRM120DF;
      }


      void collect_results() {
        SignalRegionData results_SRM90;
        results_SRM90.sr_label = "SRM90";
        results_SRM90.n_observed = 274.;
        results_SRM90.n_background = 300.;
        results_SRM90.background_sys = 50.;
        results_SRM90.signal_sys = 0.;
        results_SRM90.n_signal = _numSRM90SF+_numSRM90DF;

        SignalRegionData results_SRM100;
        results_SRM100.sr_label = "SRM100";
        results_SRM100.n_observed = 3.;
        results_SRM100.n_background = 5.2;
        results_SRM100.background_sys = 2.2;
        results_SRM100.signal_sys = 0.;
        results_SRM100.n_signal = _numSRM100SF+_numSRM100DF;

        SignalRegionData results_SRM110;
        results_SRM110.sr_label = "SRM110";
        results_SRM110.n_observed = 8.;
        results_SRM110.n_background = 9.3;
        results_SRM110.background_sys = 3.5;
        results_SRM110.signal_sys = 0.;
        results_SRM110.n_signal = _numSRM110SF+_numSRM110DF;

        SignalRegionData results_SRM120;
        results_SRM120.sr_label = "SRM120";
        results_SRM120.n_observed = 18.;
        results_SRM120.n_background = 19.;
        results_SRM120.background_sys = 9.;
        results_SRM120.signal_sys = 0.;
        results_SRM120.n_signal = _numSRM120SF+_numSRM120DF;

        add_result(results_SRM90);
        add_result(results_SRM100);
        add_result(results_SRM110);
        add_result(results_SRM120);

        return;
      }


    protected:
      void analysis_specific_reset() {
        _numSRM90SF=0; _numSRM100SF=0; _numSRM110SF=0; _numSRM120SF=0;
        _numSRM90DF=0; _numSRM100DF=0; _numSRM110DF=0; _numSRM120DF=0;

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };


    DEFINE_ANALYSIS_FACTORY(ATLAS_8TeV_2LEPStop_20invfb)


  }
}
