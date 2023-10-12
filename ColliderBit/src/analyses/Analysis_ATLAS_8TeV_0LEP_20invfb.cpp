#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

using namespace std;

// Based on arXiv:1405.7875

//Note: have not included the W signal regions

namespace Gambit {
  namespace ColliderBit {

    class Analysis_ATLAS_8TeV_0LEP_20invfb : public Analysis {
    private:

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      size_t NCUTS; //=16;


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_8TeV_0LEP_20invfb() {

        set_analysis_name("ATLAS_8TeV_0LEP_20invfb");
        set_luminosity(20.3);

        // Numbers passing cuts
        _counters["2jl"] = EventCounter("2jl");
        _counters["2jm"] = EventCounter("2jm");
        _counters["2jt"] = EventCounter("2jt");
        _counters["3j"] = EventCounter("3j");
        _counters["4jlm"] = EventCounter("4jlm");
        _counters["4jl"] = EventCounter("4jl");
        _counters["4jm"] = EventCounter("4jm");
        _counters["4jt"] = EventCounter("4jt");
        _counters["5j"] = EventCounter("5j");
        _counters["6jl"] = EventCounter("6jl");
        _counters["6jm"] = EventCounter("6jm");
        _counters["6jt"] = EventCounter("6jt");
        _counters["6jtp"] = EventCounter("6jtp");

        NCUTS=60;

        for (size_t i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVector_str.push_back("");
        }


      }


      void run(const HEPUtils::Event* event) {

        // Missing energy
        HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();

        // Now define vectors of baseline objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && fabs(electron->eta()) < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);

        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && fabs(muon->eta()) < 2.4) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);

        vector<const HEPUtils::Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.5) baselineJets.push_back(jet);
        }

        // Overlap removal: only applied to jets with |eta|<2.8
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        vector<const HEPUtils::Jet*> signalJets;

        // Remove any jet within dR=0.2 of an electrons
        for (size_t iJet=0;iJet<baselineJets.size();iJet++) {
          bool overlap=false;
          HEPUtils::P4 jetVec=baselineJets.at(iJet)->mom();
          if(fabs(jetVec.eta())<2.8){
            for (size_t iEl=0;iEl<baselineElectrons.size();iEl++) {
              HEPUtils::P4 elVec=baselineElectrons.at(iEl)->mom();
              if (fabs(elVec.deltaR_eta(jetVec))<0.2)overlap=true;
            }
          }
          if (!overlap)signalJets.push_back(baselineJets.at(iJet));
        }

        // Remove electrons with dR=0.4 or surviving jets
        for (size_t iEl=0;iEl<baselineElectrons.size();iEl++) {
          bool overlap=false;
          HEPUtils::P4 elVec=baselineElectrons.at(iEl)->mom();
          for (size_t iJet=0;iJet<signalJets.size();iJet++) {
            HEPUtils::P4 jetVec=signalJets.at(iJet)->mom();
            if (fabs(elVec.deltaR_eta(jetVec))<0.4 && fabs(jetVec.eta())<2.8)overlap=true;
          }
          if (!overlap)signalElectrons.push_back(baselineElectrons.at(iEl));
        }

        // Remove muons with dR=0.4 or surviving jets
        for (size_t iMu=0;iMu<baselineMuons.size();iMu++) {
          bool overlap=false;
          HEPUtils::P4 muVec=baselineMuons.at(iMu)->mom();
          for (size_t iJet=0;iJet<signalJets.size();iJet++) {
            HEPUtils::P4 jetVec=signalJets.at(iJet)->mom();
            if (fabs(muVec.deltaR_eta(jetVec))<0.4 && fabs(jetVec.eta())<2.8)overlap=true;
          }
          if (!overlap)signalMuons.push_back(baselineMuons.at(iMu));
        }


        // We now have the signal electrons, muons and jets: move on to the 0 lepton 2012 analysis

        // Calculate common variables and cuts first
        apply2DEfficiency(signalElectrons, ATLAS::eff2DEl.at("ATLAS_CONF_2014_032_Medium"));

        int nElectrons = signalElectrons.size();
        int nMuons = signalMuons.size();
        int nJets = signalJets.size();

        bool leptonCut = (nElectrons == 0 && nMuons == 0);
        bool metCut = (met > 160.);
        double meff_incl = met;
        double HT=0;
        for (const HEPUtils::Jet* j : signalJets)
          if (j->pT() > 40) {
            meff_incl += j->pT();
            HT  += j->pT();
          }

        // Do 2 jet regions
        //double meff2j = 0;
        double dPhiMin2j = 0;
        if (nJets > 1) {
          if (signalJets[0]->pT()>130. && signalJets[1]->pT()>60.) {
            dPhiMin2j = SmallestdPhi(signalJets,ptot.phi());
            //meff2j = met + signalJets[0]->pT() + signalJets[1]->pT();
            if (leptonCut && metCut && dPhiMin2j>0.4) {
              if (met/sqrt(HT)>8. && meff_incl>800.) _counters["2jl"].add_event(event);
              if (met/sqrt(HT)>15. && meff_incl>1200.) _counters["2jm"].add_event(event);
              if (met/sqrt(HT)>15. && meff_incl>1600.) _counters["2jt"].add_event(event);
            }

          }

        }

        // Do the 3 jet regions
        double dPhiMin3j=0;
        double meff3j=0;
        if (nJets > 2) {
          if (signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60.) {
            dPhiMin3j = SmallestdPhi(signalJets,ptot.phi());
            meff3j = met + signalJets.at(0)->pT() + signalJets.at(1)->pT() + signalJets.at(2)->pT();
            if (leptonCut && metCut && dPhiMin3j > 0.4) {
              if (met/meff3j>0.3 && meff_incl>2200.) _counters["3j"].add_event(event);
            }
          }
        }

        // Do the 4 jet regions
        double dPhiMin4=0;
        double dPhiMin2=0;
        double meff4j=0;

        if (nJets > 3) {
          if (signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60.) {
            dPhiMin4 = SmallestdPhi(signalJets,ptot.phi());
            dPhiMin2 = SmallestRemainingdPhi(signalJets,ptot.phi());
            meff4j = met + signalJets.at(0)->pT() + signalJets.at(1)->pT() + signalJets.at(2)->pT() + signalJets.at(3)->pT();
            if (leptonCut && metCut && dPhiMin4 > 0.4 && dPhiMin2 > 0.2) {
              if(met/sqrt(HT)>10. && meff_incl>700.)_counters["4jlm"].add_event(event);
              if(met/sqrt(HT)>10. && meff_incl>1000.)_counters["4jl"].add_event(event);
              if (met/meff4j>0.4 && meff_incl>1300.) _counters["4jm"].add_event(event);
              if (met/meff4j>0.25 && meff_incl>2200.) _counters["4jt"].add_event(event);
            }
          }
        }

        // Do 5 jet region
        if (nJets > 4) {
          if (signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60.) {
            dPhiMin4 = SmallestdPhi(signalJets,ptot.phi());
            dPhiMin2 = SmallestRemainingdPhi(signalJets,ptot.phi());
            double meff5j = met + signalJets.at(0)->pT() + signalJets.at(1)->pT() + signalJets.at(2)->pT() + signalJets.at(3)->pT() + signalJets.at(4)->pT();
            if (leptonCut && metCut && dPhiMin4>0.4 && dPhiMin2>0.2) {
              if (met/meff5j>0.2 && meff_incl>1200.) _counters["5j"].add_event(event);
            }
          }
        }

        // Do the 6 jet regions
        double meff6j=0.;
        if (nJets > 5) {
          if (signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && signalJets.at(5)->pT()>60.) {
            dPhiMin4 = SmallestdPhi(signalJets,ptot.phi());
            dPhiMin2 = SmallestRemainingdPhi(signalJets,ptot.phi());
            meff6j = met + signalJets.at(0)->pT() + signalJets.at(1)->pT() + signalJets.at(2)->pT() + signalJets.at(3)->pT() + signalJets.at(4)->pT() + signalJets.at(5)->pT();
            if (leptonCut && metCut && dPhiMin4>0.4 && dPhiMin2>0.2) {
              if (met/meff6j>0.2 && meff_incl>900.) _counters["6jl"].add_event(event);
              if (met/meff6j>0.2 && meff_incl>1200.) _counters["6jm"].add_event(event);
              if (met/meff6j>0.25 && meff_incl>1500.) _counters["6jt"].add_event(event);
              if (met/meff6j>0.15 && meff_incl>1700.) _counters["6jtp"].add_event(event);
            }
          }
        }

        cutFlowVector_str[0] = "No cuts ";
        cutFlowVector_str[1] = "2j: MET > 160 GeV and jet pT ";
        cutFlowVector_str[2] = "2j: dPhiMin > 0.4 ";
        cutFlowVector_str[3] = "2j: met/sqrt(HT) > 15 ";
        cutFlowVector_str[4] = "2j: meff_incl > 1200 ";
        cutFlowVector_str[5] = "2j: meff_incl > 1600 ";
        cutFlowVector_str[6] = "3j: MET > 160 and jet pT ";
        cutFlowVector_str[7] = "3j: dPhiMin > 0.4 ";
        cutFlowVector_str[8] = "3j: met/meff3j > 0.3 ";
        cutFlowVector_str[9] = "3j: met/meff_incl > 2200. ";
        cutFlowVector_str[10] = "4jlm: MET > 160 and jet pT ";
        cutFlowVector_str[11] = "4jlm: dPhiMin > 0.4 ";
        cutFlowVector_str[12] = "4jlm: dPhiMin2 > 0.2 ";
        cutFlowVector_str[13] = "4jlm: met/sqrt(HT) > 10 ";
        cutFlowVector_str[14] = "4jlm: meff incl > 700 ";
        cutFlowVector_str[15] = "4jl: meff incl > 1000 ";
        cutFlowVector_str[16] = "4jt: met/meff4j > 0.25 ";
        cutFlowVector_str[17] = "4jt: meff incl > 2200 ";
        cutFlowVector_str[18] = "5j: MET > 160 and jet pT ";
        cutFlowVector_str[19] = "5j: dPhiMin > 0.4 ";
        cutFlowVector_str[20] = "5j: dPhiMin2 > 0.2 ";
        cutFlowVector_str[21] = "5j: met/meff5j > 0.2 ";
        cutFlowVector_str[22] = "5j: meff incl > 1200. ";
        cutFlowVector_str[23] = "6jl: MET >  160 and jet pT  ";
        cutFlowVector_str[24] = "6jl: dPhiMin > 0.4 ";
        cutFlowVector_str[25] = "6jl: dPhiMin2 > 0.2 ";
        cutFlowVector_str[26] = "6jl: met/meff6j > 0.2 ";
        cutFlowVector_str[27] = "6jl: meff incl > 900. ";
        cutFlowVector_str[28] = "6jt: met/meff6j > 0.25 ";
        cutFlowVector_str[29] = "6jt: meff incl > 1500. ";

        for (size_t j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             (j==1 && signalJets.size()>1 && signalJets[0]->pT()>130. && signalJets[1]->pT()>60. && metCut && leptonCut) ||

             (j==2 && signalJets.size()>1 && signalJets[0]->pT()>130. && signalJets[1]->pT()>60. && metCut && dPhiMin2j>0.4 && leptonCut) ||

             (j==3 && signalJets.size()>1 && signalJets[0]->pT()>130. && signalJets[1]->pT()>60. && metCut && dPhiMin2j>0.4 && met/sqrt(HT)>15. && leptonCut) ||

             (j==4 && signalJets.size()>1 && signalJets[0]->pT()>130. && signalJets[1]->pT()>60. && metCut && dPhiMin2j>0.4 && met/sqrt(HT)>15. && leptonCut && meff_incl>1200.) ||

             (j==5 && signalJets.size()>1 && signalJets[0]->pT()>130. && signalJets[1]->pT()>60. && metCut && dPhiMin2j>0.4 && met/sqrt(HT)>15. && leptonCut && meff_incl>1600.) ||

             (j==6 && signalJets.size()>2 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && metCut && leptonCut) ||

             (j==7 && signalJets.size()>2 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && metCut && leptonCut && dPhiMin3j > 0.4) ||

             (j==8 && signalJets.size()>2 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && metCut && leptonCut && dPhiMin3j > 0.4 && met/meff3j>0.3) ||

             (j==9 && signalJets.size()>2 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && metCut && leptonCut && dPhiMin3j > 0.4 && met/meff3j>0.3 && meff_incl>2200.) ||

             (j==10 && signalJets.size() > 3 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && metCut) ||

             (j==11 && signalJets.size() > 3 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && metCut && dPhiMin4 > 0.4) ||

             (j==12 && signalJets.size() > 3 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && metCut && dPhiMin4 > 0.4 && dPhiMin2 > 0.2) ||

             (j==13 && signalJets.size() > 3 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && metCut && dPhiMin4 > 0.4 && dPhiMin2 > 0.2 && met/sqrt(HT) > 10.) ||

             (j==14 && signalJets.size() > 3 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && metCut && dPhiMin4 > 0.4 && dPhiMin2 > 0.2 && met/sqrt(HT) > 10. && meff_incl > 700.) ||

             (j==15 && signalJets.size() > 3 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && metCut && dPhiMin4 > 0.4 && dPhiMin2 > 0.2 && met/sqrt(HT) > 10. && meff_incl > 1000.) ||

             (j==16 && signalJets.size() > 3 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && metCut && dPhiMin4 > 0.4 && dPhiMin2 > 0.2 && met/meff4j>0.25) ||

             (j==17 && signalJets.size() > 3 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && metCut && dPhiMin4 > 0.4 && dPhiMin2 > 0.2 && met/meff4j>0.25 && meff_incl > 2200.) ||

             //Start 5j signal regions

             (j==18 && signalJets.size() > 4 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && metCut && leptonCut) ||

             (j==19 && signalJets.size() > 4 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && metCut && leptonCut && dPhiMin4 > 0.4) ||

             (j==20 && signalJets.size() > 4 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && metCut && leptonCut && dPhiMin4 > 0.4 && dPhiMin2 > 0.2) ||

             (j==21 && signalJets.size() > 4 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && metCut && leptonCut && dPhiMin4 > 0.4 && dPhiMin2 > 0.2 && met/meff4j > 0.25) ||

             (j==22 && signalJets.size() > 4 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && metCut && leptonCut && dPhiMin4 > 0.4 && dPhiMin2 > 0.2 && met/meff4j > 0.25 && meff_incl > 1200.) ||

             //Start 6jl region

             (j==23 && signalJets.size() > 5 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && signalJets.at(5)->pT()>60. && leptonCut && metCut) ||

             (j==24 && signalJets.size() > 5 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && signalJets.at(5)->pT()>60. && leptonCut && metCut && dPhiMin4>0.4) ||

             (j==25 && signalJets.size() > 5 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && signalJets.at(5)->pT()>60. && leptonCut && metCut && dPhiMin4>0.4 && dPhiMin2 > 0.2) ||

             (j==26 && signalJets.size() > 5 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && signalJets.at(5)->pT()>60. && leptonCut && metCut && dPhiMin4>0.4 && dPhiMin2 > 0.2 && met/meff6j>0.2) ||

             (j==27 && signalJets.size() > 5 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && signalJets.at(5)->pT()>60. && leptonCut && metCut && dPhiMin4>0.4 && dPhiMin2 > 0.2 && met/meff6j>0.2 && meff_incl > 900.) ||

             (j==28 && signalJets.size() > 5 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && signalJets.at(5)->pT()>60. && leptonCut && metCut && dPhiMin4>0.4 && dPhiMin2 > 0.2 && met/meff6j>0.2 && meff_incl > 900. && met/meff6j>0.25) ||

             (j==29 && signalJets.size() > 5 && signalJets.at(0)->pT()>130. && signalJets.at(1)->pT()>60. && signalJets.at(2)->pT()>60. && signalJets.at(3)->pT()>60. && signalJets.at(4)->pT()>60. && signalJets.at(5)->pT()>60. && leptonCut && metCut && dPhiMin4>0.4 && dPhiMin2 > 0.2 && met/meff6j>0.2 && meff_incl > 900. && met/meff6j>0.25 && meff_incl>1500.)

             ){

            cutFlowVector[j]++;

          }
        }

      }

      void collect_results() {
        // double scale_by=1.;
        // cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
        // cout << "CUT FLOW: ATLAS 0 lepton paper "<<endl;
        // cout << "------------------------------------------------------------------------------------------------------------------------------"<<endl;
        // cout<< right << setw(40) << "CUT" << setw(20) << "RAW" << setw(20) << "SCALED"
        //     << setw(20) << "%" << setw(20) << "clean adj RAW"<< setw(20) << "clean adj %" << endl;
        // for (size_t j=0; j<NCUTS; j++) {
        //   cout << right << setw(40) << cutFlowVector_str[j].c_str() << setw(20)
        //        << cutFlowVector[j] << setw(20) << cutFlowVector[j]*scale_by << setw(20)
        //        << 100.*cutFlowVector[j]/cutFlowVector[0] << "%" << setw(20)
        //        << cutFlowVector[j]*scale_by << setw(20) << 100.*cutFlowVector[j]/cutFlowVector[0]<< "%" << endl;
        // }
        // cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;

        // Now fill a results object with the results for each SR
        // Numbers are taken from CONF note

        // add_result(SignalRegionData(_counters["SR label"], n_obs, {n_bkg, n_bkg_err}));

        add_result(SignalRegionData(_counters["2jl"], 12315., { 13000., 1000.}));
        add_result(SignalRegionData(_counters["2jm"], 715., { 760., 50.}));
        add_result(SignalRegionData(_counters["2jt"], 133., { 125., 10.}));
        add_result(SignalRegionData(_counters["3j"], 7., { 5., 1.2}));
        add_result(SignalRegionData(_counters["4jlm"], 2169., { 2120., 110.}));
        add_result(SignalRegionData(_counters["4jl"], 608., { 630., 50.}));
        add_result(SignalRegionData(_counters["4jm"], 24., { 37., 6.}));
        add_result(SignalRegionData(_counters["4jt"], 0., { 2.5, 1.}));
        add_result(SignalRegionData(_counters["5j"], 121., { 126., 13.}));
        add_result(SignalRegionData(_counters["6jl"], 121., { 111., 11.}));
        add_result(SignalRegionData(_counters["6jm"], 39., { 33., 6.}));
        add_result(SignalRegionData(_counters["6jt"], 5., { 5.2, 1.4}));
        add_result(SignalRegionData(_counters["6jtp"], 6., { 4.9, 1.6}));

      }


      ///////////////////


      double SmallestdPhi(vector<const HEPUtils::Jet*> jets,double phi_met) {
        if (jets.size()<2) return 999;
        double dphi1 = acos(cos(jets.at(0)->phi()-phi_met));
        double dphi2 = acos(cos(jets.at(1)->phi()-phi_met));
        double dphi3 = 999;
        if (jets.size() > 2 && jets[2]->pT() > 40.)
          dphi3 = acos(cos(jets[2]->phi() - phi_met));
        double min1 = min(dphi1, dphi2);
        return min(min1, dphi3);
      }

      double SmallestRemainingdPhi(const vector<const HEPUtils::Jet*> jets,double phi_met) {
        double remainingDPhi = 999;
        double dphiMin = 999;
        for (size_t i = 0; i < jets.size(); i++) {
          if (i > 2 && jets[i]->pT() > 40.) { //< @todo Just start the loop at i = 3?
            remainingDPhi = acos(cos((jets[i]->phi() - phi_met)));
            dphiMin = min(remainingDPhi, dphiMin);
          }
        }
        return dphiMin;
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };


    DEFINE_ANALYSIS_FACTORY(ATLAS_8TeV_0LEP_20invfb)


  }
}
