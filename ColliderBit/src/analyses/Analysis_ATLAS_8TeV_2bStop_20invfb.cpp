#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;


// The ATLAS 2b stop/bottom analysis (20fb^-1)
//
// based on: arXiv:1308.2631
//
//    Code by Martin White, Sky French.
//    Known errors:
//    a) The isolation is already applied in the simulation rather than after overlap removal -> the electron and muon veto technically require a veto on base-line electrons/muons not overlapping with jets
//
//    Known features:
//    a) Must run simulator with 60% b tagging efficiency and ?% mis-id rate


namespace Gambit {
  namespace ColliderBit {


    class Analysis_ATLAS_8TeV_2bStop_20invfb : public Analysis {
    private:

      // Numbers passing cuts
      int _numSRA, _numSRB;
      int _numSRA15, _numSRA20, _numSRA25, _numSRA30, _numSRA35;

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS; //=2;

      // Debug histos

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_8TeV_2bStop_20invfb() {

        set_analysis_name("ATLAS_8TeV_2bStop_20invfb");
        set_luminosity(20.1);

        _numSRA = 0 ; _numSRB = 0; _numSRA15 = 0; _numSRA20 = 0; _numSRA25 = 0; _numSRA30 = 0; _numSRA35 = 0;
        NCUTS=30;

        for(int i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVector_str.push_back("");
        }

      }

      void run(const HEPUtils::Event* event) {

        // Missing energy
        HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();

        // Now define vector of baseline electrons
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 7. && fabs(electron->eta()) < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);

        // Now define vector of baseline muons
        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 6. && fabs(muon->eta()) < 2.4) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);

        const std::vector<double> a = {0,10.};
        const std::vector<double> b = {0,10000.};
        const std::vector<double> c = {0.60};
        HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);

        vector<HEPUtils::Jet*> baselineJets;
        vector<HEPUtils::Jet*> bJets;
        vector<HEPUtils::Jet*> trueBJets; //for debugging

        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.9) baselineJets.push_back(jet);
        }

        // Overlap removal
        vector<HEPUtils::Particle*> signalElectrons;
        vector<HEPUtils::Particle*> signalMuons;
        vector<HEPUtils::Particle*> electronsForVeto;
        vector<HEPUtils::Particle*> muonsForVeto;
        vector<HEPUtils::Jet*> goodJets;
        vector<HEPUtils::Jet*> signalJets;

        // Remove any jet within dR=0.2 of an electrons
        for (size_t iJet=0;iJet<baselineJets.size();iJet++) {
          bool overlap=false;
          HEPUtils::P4 jetVec=baselineJets.at(iJet)->mom();
          for (size_t iEl=0;iEl<baselineElectrons.size();iEl++) {
            HEPUtils::P4 elVec=baselineElectrons.at(iEl)->mom();
            if (fabs(elVec.deltaR_eta(jetVec))<0.2)overlap=true;
          }
          if (!overlap&&fabs(baselineJets.at(iJet)->eta())<2.8)goodJets.push_back(baselineJets.at(iJet));
          if (!overlap&&fabs(baselineJets.at(iJet)->eta())<2.8 && baselineJets.at(iJet)->pT()>20.)signalJets.push_back(baselineJets.at(iJet));
        }

        // Remove electrons with dR=0.4 or surviving jets
        for (size_t iEl=0;iEl<baselineElectrons.size();iEl++) {
          bool overlap=false;
          HEPUtils::P4 elVec=baselineElectrons.at(iEl)->mom();
          for (size_t iJet=0;iJet<goodJets.size();iJet++) {
            HEPUtils::P4 jetVec=goodJets.at(iJet)->mom();
            if (fabs(elVec.deltaR_eta(jetVec))<0.4)overlap=true;
          }
          if (!overlap && elVec.pT()>25.)signalElectrons.push_back(baselineElectrons.at(iEl));
          if(!overlap)electronsForVeto.push_back(baselineElectrons.at(iEl));
        }

        // Remove muons with dR=0.4 or surviving jets
        for (size_t iMu=0;iMu<baselineMuons.size();iMu++) {
          bool overlap=false;

          HEPUtils::P4 muVec=baselineMuons.at(iMu)->mom();

          for (size_t iJet=0;iJet<goodJets.size();iJet++) {
            HEPUtils::P4 jetVec=goodJets.at(iJet)->mom();
            if (fabs(muVec.deltaR_eta(jetVec))<0.4)overlap=true;
          }
          if (!overlap && muVec.pT()>25.)signalMuons.push_back(baselineMuons.at(iMu));
          if(!overlap)muonsForVeto.push_back(baselineMuons.at(iMu));
        }

        for (HEPUtils::Jet* jet : signalJets) {
          bool hasTag=has_tag(_eff2d, jet->eta(), jet->pT());
          if(jet->btag() && hasTag && fabs(jet->eta()) < 2.5 && jet->pT() > 20.) bJets.push_back(jet);
        }

        // We now have the signal electrons, muons, jets and b jets- move on to the analysis

        // Calculate common variables and cuts first
        int nJets = signalJets.size();

        //Jet cuts for each SR
        bool passSRAJetCut=false;
        bool passSRBJetCut=false;
        bool passSRAbJetCut=false;
        bool passSRBbJetCut=false;

        double mbb=0;
        double mCT=0;

	//cout << "TEST njets " << nJets << " nbjets " << bJets.size() << endl;

        if(nJets>=2){
          if(signalJets[0]->pT() > 130.
             && signalJets[1]->pT() > 50) {
            if(nJets==2) {
              passSRAJetCut=true;
              if(bJets.size()==2) {
                passSRAbJetCut=true;

                mbb = (bJets[0]->mom()+bJets[1]->mom()).m();

                double bjet1_ET = sqrt(bJets[0]->mom().pT()*bJets[0]->mom().pT()+bJets[0]->mom().m()*bJets[0]->mom().m());
                double bjet2_ET = sqrt(bJets[1]->mom().pT()*bJets[1]->mom().pT()+bJets[1]->mom().m()*bJets[1]->mom().m());

                double modPTdiff_squared=(bJets[0]->mom().px()-bJets[1]->mom().px())*(bJets[0]->mom().px()-bJets[1]->mom().px())
                  +                      (bJets[0]->mom().py()-bJets[1]->mom().py())*(bJets[0]->mom().py()-bJets[1]->mom().py());

                double mct_squared = pow(bjet1_ET+bjet2_ET,2)-modPTdiff_squared;
                mCT = sqrt(mct_squared);
              }
            }
            if(nJets>2) {
              if(signalJets[2]->pT() < 50.) {
                passSRAJetCut=true;
                //Check that the two leading jets are the b jets
                if(bJets.size()==2 && (signalJets[0]->pT()==bJets[0]->pT()) && (signalJets[1]->pT()==bJets[1]->pT())){
                  passSRAbJetCut=true;

                  mbb = (bJets[0]->mom()+bJets[1]->mom()).m();
                  double bjet1_ET = sqrt(bJets[0]->mom().pT()*bJets[0]->mom().pT()+bJets[0]->mom().m()*bJets[0]->mom().m());
                  double bjet2_ET = sqrt(bJets[1]->mom().pT()*bJets[1]->mom().pT()+bJets[1]->mom().m()*bJets[1]->mom().m());

                  double modPTdiff_squared=(bJets[0]->mom().px()-bJets[1]->mom().px())*(bJets[0]->mom().px()-bJets[1]->mom().px())
                    +                      (bJets[0]->mom().py()-bJets[1]->mom().py())*(bJets[0]->mom().py()-bJets[1]->mom().py());

                  double mct_squared = pow(bjet1_ET+bjet2_ET,2)-modPTdiff_squared;
                  mCT = sqrt(mct_squared);

                  //double bjet1_ET = sqrt(bjet1.Pt()*bjet1.Pt()+bjet1.M()*bjet1.M());
                  //double bjet2_ET = sqrt(bjet2.Pt()*bjet2.Pt()+bjet2.M()*bjet2.M());
                  //TVector2 bjet1_pT;
                  //TVector2 bjet2_pT;
                  //bjet1_pT.Set(bjet1.Px(),bjet1.Py());
                  //bjet2_pT.Set(bjet2.Px(),bjet2.Py());
                  //double mct_squared = pow(bjet1_ET+bjet2_ET,2)-(bjet1_pT-bjet2_pT).Mod2();
                  //mCT = sqrt(mct_squared);
                }
              }
            }
          }
        }

        if(nJets>=3){
          if(signalJets[0]->pT() > 150.
             && signalJets[1]->pT() > 30.
             && signalJets[2]->pT() > 30.) {
            passSRBJetCut=true;
            //Check that the 2nd and 3rd leading jets are the b jets
            if(bJets.size()==2 && (bJets[0]->pT()==signalJets[1]->pT()) && (bJets[1]->pT()==signalJets[2]->pT())) {
              passSRBbJetCut=true;

              mbb = (bJets[0]->mom()+bJets[1]->mom()).m();
              double bjet1_ET = sqrt(bJets[0]->mom().pT()*bJets[0]->mom().pT()+bJets[0]->mom().m()*bJets[0]->mom().m());
              double bjet2_ET = sqrt(bJets[1]->mom().pT()*bJets[1]->mom().pT()+bJets[1]->mom().m()*bJets[1]->mom().m());

              double modPTdiff_squared=(bJets[0]->mom().px()-bJets[1]->mom().px())*(bJets[0]->mom().px()-bJets[1]->mom().px())
                +                      (bJets[0]->mom().py()-bJets[1]->mom().py())*(bJets[0]->mom().py()-bJets[1]->mom().py());

              double mct_squared = pow(bjet1_ET+bjet2_ET,2)-modPTdiff_squared;
              mCT = sqrt(mct_squared);


              //mbb = (bjet1+bjet2).M();
              //double bjet1_ET = sqrt(bjet1.Pt()*bjet1.Pt()+bjet1.M()*bjet1.M());
              //double bjet2_ET = sqrt(bjet2.Pt()*bjet2.Pt()+bjet2.M()*bjet2.M());
              //TVector2 bjet1_pT;
              //TVector2 bjet2_pT;
              //bjet1_pT.Set(bjet1.Px(),bjet1.Py());
              //bjet2_pT.Set(bjet2.Px(),bjet2.Py());
              //double mct_squared = pow(bjet1_ET+bjet2_ET,2)-(bjet1_pT-bjet2_pT).Mod2();
              //mCT = sqrt(mct_squared);

            }
          }

        }

        //Calculate dphi(jet,met) for the three leading jets
        double dphi_jetmet1=9999;
        if(nJets>0)dphi_jetmet1=std::acos(std::cos(signalJets.at(0)->phi()-ptot.phi()));
        double dphi_jetmet2=9999;
        if(nJets>1)dphi_jetmet2=std::acos(std::cos(signalJets.at(1)->phi()-ptot.phi()));
        double dphi_jetmet3=9999;
        if(nJets>2)dphi_jetmet3=std::acos(std::cos(signalJets.at(2)->phi()-ptot.phi()));

        double dphi_min = min(dphi_jetmet1,dphi_jetmet2);
        dphi_min = min(dphi_min,dphi_jetmet3);

        //Calculate meff (all jets with pT>20 GeV, and met)
        double meff = met;
        for (HEPUtils::Jet* jet : signalJets) {
          if(jet->pT()>20.)meff += jet->pT();
        }
        double meff2 = met; double meff3 = met; int nummeff=0;
        for (HEPUtils::Jet* jet : signalJets) {
          nummeff++;
          if(nummeff<=2 && jet->pT()>20.)meff2 += jet->pT();
          if(nummeff<=3 && jet->pT()>20.)meff3 += jet->pT();
        }


        //Calculate HT,3 (all jets except 3 highest pT)
        double ht3 = 0; int num=0;
        for (HEPUtils::Jet* jet : signalJets) {
          num++;
          if(num>3 && jet->pT()>20.)ht3 += jet->pT();
        }

        //Cutflow flags
        bool cut_ElectronVeto=false;
        bool cut_MuonVeto=false;
        //bool cut_2jets=false;
        //bool cut_3jets=false;
        //bool cut_dPhiJet1=false;
        bool cut_METGt150=false;
        bool cut_METGt250=false;
        bool cut_dPhiJets=false;
        bool cut_METmeff2=false;
        bool cut_METmeff3=false;

        if(electronsForVeto.size()==0)cut_ElectronVeto=true;
        if(muonsForVeto.size()==0)cut_MuonVeto=true;
        //if(passSRAJetCut)cut_2jets=true;
        //if(passSRBJetCut)cut_3jets=true;
        //if(dphi_jetmet1>2.5)cut_dPhiJet1=true;
        if(dphi_min>0.4)cut_dPhiJets=true;
        if(met>150.)cut_METGt150=true;
        if(met>250.)cut_METGt250=true;
        if(met/meff2>0.25)cut_METmeff2=true;
        if(met/meff3>0.25)cut_METmeff3=true;

        cutFlowVector_str[0] = "No cuts ";
        cutFlowVector_str[1] = "MET > 80 ";
        cutFlowVector_str[2] = "Lepton veto ";
        cutFlowVector_str[3] = "MET > 150 ";
        cutFlowVector_str[4] = "Jet selection ";
        cutFlowVector_str[5] = "mbb > 200 ";
        cutFlowVector_str[6] = "mCT > 150 ";
        cutFlowVector_str[7] = "mCT > 200 ";
        cutFlowVector_str[8] = "mCT > 250 ";
        cutFlowVector_str[9] = "mCT > 300 ";
        cutFlowVector_str[10] = "SRB: lepton veto ";
        cutFlowVector_str[11] = "SRB: MET > 250 ";
        cutFlowVector_str[12] = "SRB: Jet selection ";
        cutFlowVector_str[13] = "SRB: HT3 < 50  ";
        cutFlowVector_str[14] = "SRA: Jet selection  ";
        cutFlowVector_str[15] = "SRA: B jet selection  ";


        for(int j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             (j==1 && met>80.) ||

             (j==2 && met>80. && cut_MuonVeto && cut_ElectronVeto) ||

             (j==3 && met>150. && cut_MuonVeto && cut_ElectronVeto) ||

             (j==4 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAbJetCut && passSRAJetCut) ||

             (j==5 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAbJetCut && passSRAJetCut && mbb > 200.) ||

             (j==6 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAbJetCut && passSRAJetCut && mbb > 200. && mCT > 150.) ||

             (j==7 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAbJetCut && passSRAJetCut && mbb > 200. && mCT > 200.) ||

             (j==8 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAbJetCut && passSRAJetCut && mbb > 200. && mCT > 250.) ||

             (j==9 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAbJetCut && passSRAJetCut && mbb > 200. && mCT > 300.) ||

             (j==10 && met>150. && cut_MuonVeto && cut_ElectronVeto) ||

             (j==11 && met>250. && cut_MuonVeto && cut_ElectronVeto) ||

             (j==12 && met>250. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut && passSRBbJetCut) ||

             (j==13 && met>250. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut && passSRBbJetCut && ht3<50.) ||

             (j==14 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut) ||

             (j==15 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut)


             )cutFlowVector[j]++;
        }

        //We're now ready to apply the cuts for each signal region
        //_numSRA, _numSRB, _numSRA15, _numSRA20, _numSRA25, _numSRA30, _numSRA35;

        if(cut_ElectronVeto && cut_MuonVeto && cut_METGt150 && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2 && mbb>200.) {
          _numSRA++;
          if(mCT>150.) _numSRA15++;
          if(mCT>200.) _numSRA20++;
          if(mCT>250.) _numSRA25++;
          if(mCT>300.) _numSRA30++;
          if(mCT>350.) _numSRA35++;
        }
        if(cut_ElectronVeto && cut_MuonVeto && cut_METGt250 && passSRBJetCut && passSRBbJetCut && cut_dPhiJets && cut_METmeff3 && ht3<50.) _numSRB ++;


        return;

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_8TeV_2bStop_20invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_8TeV_2bStop_20invfb*>(other);

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (int j=0; j<NCUTS; j++) {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }
        _numSRA += specificOther->_numSRA;
        _numSRB += specificOther->_numSRB;
        _numSRA15 += specificOther->_numSRA15;
        _numSRA20 += specificOther->_numSRA20;
        _numSRA25 += specificOther->_numSRA25;
        _numSRA30 += specificOther->_numSRA30;
        _numSRA35 += specificOther->_numSRA35;
      }


      void collect_results() {
        SignalRegionData results_SRA15;
        results_SRA15.sr_label = "SRA15";
        results_SRA15.n_observed = 102.;
        results_SRA15.n_background = 94.;
        results_SRA15.background_sys = 13.;
        results_SRA15.signal_sys = 0.;
        results_SRA15.n_signal = _numSRA15;

        SignalRegionData results_SRA20;
        results_SRA20.sr_label = "SRA20";
        results_SRA20.n_observed = 48.;
        results_SRA20.n_background = 39.;
        results_SRA20.background_sys = 6.;
        results_SRA20.signal_sys = 0.;
        results_SRA20.n_signal = _numSRA20;

        SignalRegionData results_SRA25;
        results_SRA25.sr_label = "SRA25";
        results_SRA25.n_observed = 14.;
        results_SRA25.n_background = 15.8;
        results_SRA25.background_sys = 2.8;
        results_SRA25.signal_sys = 0.;
        results_SRA25.n_signal = _numSRA25;

        SignalRegionData results_SRA30;
        results_SRA30.sr_label = "SRA30";
        results_SRA30.n_observed = 7.;
        results_SRA30.n_background = 5.9;
        results_SRA30.background_sys = 1.1;
        results_SRA30.signal_sys = 0.;
        results_SRA30.n_signal = _numSRA30;

        SignalRegionData results_SRA35;
        results_SRA35.sr_label = "SRA35";
        results_SRA35.n_observed = 3.;
        results_SRA35.n_background = 2.5;
        results_SRA35.background_sys = 0.6;
        results_SRA35.signal_sys = 0.;
        results_SRA35.n_signal = _numSRA35;

        SignalRegionData results_SRB;
        results_SRB.sr_label = "SRB";
        results_SRB.n_observed = 65.;
        results_SRB.n_background = 64.;
        results_SRB.background_sys = 10.;
        results_SRB.signal_sys = 0.;
        results_SRB.n_signal = _numSRB;

        add_result(results_SRA15);
        add_result(results_SRA20);
        add_result(results_SRA25);
        add_result(results_SRA30);
        add_result(results_SRA35);
        add_result(results_SRB);

        return;
      }


    protected:
      void analysis_specific_reset() {
        _numSRA = 0 ; _numSRB = 0; _numSRA15 = 0; _numSRA20 = 0; _numSRA25 = 0; _numSRA30 = 0; _numSRA35 = 0;

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };


    DEFINE_ANALYSIS_FACTORY(ATLAS_8TeV_2bStop_20invfb)


  }
}
