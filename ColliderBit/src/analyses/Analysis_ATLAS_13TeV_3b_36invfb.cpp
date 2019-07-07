///
///  \author Are Raklev
///  \date 2018 June
///
///  Based on the search presented in 1806.04030.
///  Only the high mass analysis is implemented here.
///  This analysis has overlapping exclusion and discovery signal regions,
///  the discovery regions are separated into a derived class.
///  *********************************************

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

using namespace std;

// TODO: See if adding muons to jets gives some improvement.

namespace Gambit {
  namespace ColliderBit {


    class Analysis_ATLAS_13TeV_3b_36invfb : public Analysis {

    protected:
      // Signal region map
      std::map<string,double> _numSR = {
        {"SR-3b-meff1-A", 0.},       // Exclusion regions, disjoint
        {"SR-3b-meff2-A", 0.},
        {"SR-3b-meff3-A", 0.},
        {"SR-4b-meff1-A", 0.},
        {"SR-4b-meff1-B", 0.},
        {"SR-4b-meff2-A", 0.},
        {"SR-4b-meff2-B", 0.},
        {"SR-4b-meff1-A-disc", 0.}   // Discovery regions, SR-4b-meff1-A and SR-4b-meff2-A are subsets
      };

    private:

      // Cut-flows
      size_t NCUTS;
      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      vector<double> cutFlowVectorATLAS;

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      static bool sortByPT(HEPUtils::Jet* jet1, HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }

      Analysis_ATLAS_13TeV_3b_36invfb() {

        set_analysis_name("ATLAS_13TeV_3b_36invfb");
        set_luminosity(36.1);

        NCUTS=14;

        for(size_t i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVectorATLAS.push_back(0);
          cutFlowVector_str.push_back("");
        }
      }

      // The following section copied from Analysis_ATLAS_1LEPStop_20invfb.cpp
      void JetLeptonOverlapRemoval(vector<HEPUtils::Jet*> &jetvec, vector<HEPUtils::Particle*> &lepvec, double DeltaRMax) {
        //Routine to do jet-lepton check
        //Discards jets if they are within DeltaRMax of a lepton

        vector<HEPUtils::Jet*> Survivors;

        for(unsigned int itjet = 0; itjet < jetvec.size(); itjet++) {
          bool overlap = false;
          HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
          for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
            HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
            double dR;

            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(jetvec.at(itjet));
        }
        jetvec=Survivors;

        return;
      }

      void LeptonJetOverlapRemoval(vector<HEPUtils::Particle*> &lepvec, vector<HEPUtils::Jet*> &jetvec) {
        //Routine to do lepton-jet check
        //Discards leptons if they are within dR of a jet as defined in analysis paper

        vector<HEPUtils::Particle*> Survivors;

        for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
          bool overlap = false;
          HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
          for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            double dR;
            double DeltaRMax = std::min(0.4, 0.04 + 10 / lepmom.pT());
            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lepvec.at(itlep));
        }
        lepvec=Survivors;

        return;
      }

      // Calculate transverse mass
      double mTrans(HEPUtils::P4 pmiss, HEPUtils::P4 jet) {
        double mT = sqrt( pow(pmiss.pT()+jet.pT(),2) - pow(pmiss.px()+jet.px(),2) - pow(pmiss.py()+jet.py(),2) );
        //cout << "pTmiss " << pmiss.pT() << " jetpT " << jet.pT() << endl;
        //cout << "pxmiss " << pmiss.px() << "pxjet " << jet.px() << " pymiss " << pmiss.py() << " pyjet " << jet.py() << endl;
        return mT;
      }

      void run(const HEPUtils::Event* event) {

        // Get the missing energy in the event
        double met = event->met();
        HEPUtils::P4 metVec = event->missingmom();

        // Now define vectors of baseline objects, including:
        // - retrieval of electron, muon and jets from the event
        // - application of basic pT and eta cuts

        // Electrons
        vector<HEPUtils::Particle*> electrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 5.
              && fabs(electron->eta()) < 2.47)
            electrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(electrons);

        // Muons
        vector<HEPUtils::Particle*> muons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 5.
              && fabs(muon->eta()) < 2.5)
            muons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(muons);

        vector<HEPUtils::Jet*> candJets;
        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 2.8)
            candJets.push_back(jet);
        }

   	    // Jets
        vector<HEPUtils::Jet*> bJets;
        vector<HEPUtils::Jet*> nonbJets;

        // Find b-jets
        double btag = 0.77; double cmisstag = 1/6.; double misstag = 1./134.;
        for (HEPUtils::Jet* jet : candJets) {
          // Tag
          if( jet->btag() && random_bool(btag) ) bJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) bJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) bJets.push_back(jet);
          // Non b-jet
          else nonbJets.push_back(jet);
        }

        // Overlap removal
        JetLeptonOverlapRemoval(nonbJets,electrons,0.2);
        LeptonJetOverlapRemoval(electrons,nonbJets);
        JetLeptonOverlapRemoval(nonbJets,muons,0.2);
        LeptonJetOverlapRemoval(muons,nonbJets);

        // Find veto leptons with pT > 20 GeV
        vector<HEPUtils::Particle*> vetoElectrons;
        for (HEPUtils::Particle* electron : electrons) {
          if (electron->pT() > 20.) vetoElectrons.push_back(electron);
        }
        vector<HEPUtils::Particle*> vetoMuons;
        for (HEPUtils::Particle* muon : muons) {
          if (muon->pT() > 20.) vetoMuons.push_back(muon);
        }

        // Restrict jets to pT > 25 GeV after overlap removal
        vector<HEPUtils::Jet*> bJets_survivors;
        for (HEPUtils::Jet* jet : bJets) {
          if(jet->pT() > 25.) bJets_survivors.push_back(jet);
        }
        vector<HEPUtils::Jet*> nonbJets_survivors;
        for (HEPUtils::Jet* jet : nonbJets) {
          if(jet->pT() > 25.) nonbJets_survivors.push_back(jet);
        }
        vector<HEPUtils::Jet*> jet_survivors;
        jet_survivors = nonbJets_survivors;
        for (HEPUtils::Jet* jet : bJets) {
          jet_survivors.push_back(jet);
        }
        std::sort(jet_survivors.begin(), jet_survivors.end(), sortByPT);

        // Number of objects
        size_t nbJets = bJets_survivors.size();
        size_t nnonbJets = nonbJets_survivors.size();
        size_t nJets = nbJets + nnonbJets;
        //size_t nJets = jet_survivors.size();
        size_t nMuons=vetoMuons.size();
        size_t nElectrons=vetoElectrons.size();
        size_t nLeptons = nElectrons+nMuons;

        // Loop over jets to find angle wrt to missing momentum
        double phi4min = 7;
        for(int i = 0; i < min(4,(int)nJets); i++){
          double phi = jet_survivors.at(i)->mom().deltaPhi(metVec);
          if(phi < phi4min) phi4min = phi;
        }

        // Collect the four signal jets.
        vector<HEPUtils::Jet*> signalJets;
        for(HEPUtils::Jet* jet : bJets_survivors){
          if(signalJets.size() < 4) signalJets.push_back(jet);
        }
        for(HEPUtils::Jet* jet : nonbJets_survivors){
          if(signalJets.size() < 4) signalJets.push_back(jet);
        }

        // Effective mass (using the four jets used in Higgses)
        double meff = met;
        for(HEPUtils::Jet* jet : signalJets){
          meff += jet->pT();
        }

        // Find Higgs candidates
        double mlead = 0;  double msubl = 0;
        double m1 = 0;  double m2 = 0;
        double Rbbmax = 10;
        if(signalJets.size() == 4){
          double R11 = signalJets.at(0)->mom().deltaR_eta(signalJets.at(1)->mom());
          double R12 = signalJets.at(2)->mom().deltaR_eta(signalJets.at(3)->mom());
          double DR1 = max(R11,R12);
          //cout << DR1 << " " << R11 << " " << R12 << endl;
          double R21 = signalJets.at(0)->mom().deltaR_eta(signalJets.at(2)->mom());
          double R22 = signalJets.at(1)->mom().deltaR_eta(signalJets.at(3)->mom());
          double DR2 = max(R21,R22);
          //cout << DR2 << " " << R21 << " " << R22 << endl;
          double R31 = signalJets.at(0)->mom().deltaR_eta(signalJets.at(3)->mom());
          double R32 = signalJets.at(1)->mom().deltaR_eta(signalJets.at(2)->mom());
          double DR3 = max(R31,R32);
          //cout << DR3 << " " << R31 << " " << R32 << endl;
          //cout << endl;
          if( DR1 < DR2 && DR1 < DR3 ){
            m1 = (signalJets.at(0)->mom()+signalJets.at(1)->mom()).m();
            m2 = (signalJets.at(2)->mom()+signalJets.at(3)->mom()).m();
            Rbbmax = DR1;
          }
          else if( DR2 < DR1 && DR2 < DR3 ){
            m1 = (signalJets.at(0)->mom()+signalJets.at(2)->mom()).m();
            m2 = (signalJets.at(1)->mom()+signalJets.at(3)->mom()).m();
            Rbbmax = DR2;
          }
          else{
            m1 = (signalJets.at(0)->mom()+signalJets.at(3)->mom()).m();
            m2 = (signalJets.at(1)->mom()+signalJets.at(2)->mom()).m();
            Rbbmax = DR3;
          }
          mlead = max(m1,m2); msubl = min(m1,m2);
          //cout << mlead << " " << msubl << endl;
        }


        // Transverse mass for leading b-jets
        double mTmin = 10E6;
        for(int i = 0; i < min(3,(int)nbJets); i++){
          double mT = mTrans(metVec,bJets_survivors.at(i)->mom());
          if(mT < mTmin) mTmin = mT;
        }
        //cout << "mTmin " << mTmin << endl;

        // Increment cutFlowVector elements
        // Cut flow strings
//        cutFlowVector_str[0]  = "No cuts ";
//        cutFlowVector_str[1]  = "Trigger, $E_T^{miss} > 200$ GeV";
//        cutFlowVector_str[2]  = "$\\Delta\\phi_{min}^{4j} > 0.4$";
//        cutFlowVector_str[3]  = "$N_{lep} = 0$";
//        cutFlowVector_str[4]  = "$N_{jet} \\ge 4$, $N_{jet} \\le 5$";
//        cutFlowVector_str[5]  = "$110 < m(h_1)< 150$ GeV";
//        cutFlowVector_str[6]  = "$90 < m(h_2)< 140$ GeV$";
//        cutFlowVector_str[7]  = "$m_{T,min}^{b-jets}> 130$ GeV";
//        cutFlowVector_str[8]  = "$m_{eff} > 1100$ GeV";
//        cutFlowVector_str[9]  = "$N_{b-jets} \\ge 3$";
//        cutFlowVector_str[10]  = "$0.4 \\le \\Delta R_{max}^{bb} \\le 1.4$";
//        cutFlowVector_str[11]  = "m_{eff} > 600 GeV";
//        cutFlowVector_str[12]  = "$N_{b-jet} \\ge 4$";
//        cutFlowVector_str[13]  = "$0.4 \\le \\Delta R_{max}^{bb} \\le 1.4$";

        // Cut flow from paper
        // Higgsino 300 GeV
//        cutFlowVectorATLAS[0] = 10276.0;
//        cutFlowVectorATLAS[1] =  1959.1;
//        cutFlowVectorATLAS[2] =  1533.0;
//        cutFlowVectorATLAS[3] =  1319.3;
//        cutFlowVectorATLAS[4] =   664.9;
//        cutFlowVectorATLAS[5] =   249.3;
//        cutFlowVectorATLAS[6] =   123.0;
//        cutFlowVectorATLAS[7] =    74.3;
//        cutFlowVectorATLAS[8] =     4.0;
//        cutFlowVectorATLAS[9] =     1.5;
//        cutFlowVectorATLAS[10] =    1.4;
//        cutFlowVectorATLAS[11] =   90.2;
//        cutFlowVectorATLAS[12] =   15.6;
//        cutFlowVectorATLAS[13] =    6.8;
        // Higgsino 500 GeV
//        cutFlowVectorATLAS[0] = 1220.7;
//        cutFlowVectorATLAS[1] =  739.0;
//        cutFlowVectorATLAS[2] =  647.1;
//        cutFlowVectorATLAS[3] =  548.2;
//        cutFlowVectorATLAS[4] =  291.9;
//        cutFlowVectorATLAS[5] =  133.5;
//        cutFlowVectorATLAS[6] =   78.0;
//        cutFlowVectorATLAS[7] =   64.1;
//        cutFlowVectorATLAS[8] =   12.0;
//        cutFlowVectorATLAS[9] =    5.7;
//        cutFlowVectorATLAS[10] =   4.8;
//        cutFlowVectorATLAS[11] =  74.3;
//        cutFlowVectorATLAS[12] =  15.0;
//        cutFlowVectorATLAS[13] =   9.7;
        // Higgsino 800 GeV
//        cutFlowVectorATLAS[0] = 124.9;
//        cutFlowVectorATLAS[1] = 101.9;
//        cutFlowVectorATLAS[2] =  89.5;
//        cutFlowVectorATLAS[3] =  73.7;
//        cutFlowVectorATLAS[4] =  39.4;
//        cutFlowVectorATLAS[5] =  19.0;
//        cutFlowVectorATLAS[6] =  13.4;
//        cutFlowVectorATLAS[7] =  11.8;
//        cutFlowVectorATLAS[8] =   8.1;
//        cutFlowVectorATLAS[9] =   3.8;
//        cutFlowVectorATLAS[10] =  3.6;
//        cutFlowVectorATLAS[11] = 13.3;
//        cutFlowVectorATLAS[12] =  2.3;
//        cutFlowVectorATLAS[13] =  2.0;

        // Apply cutflow
//        for(size_t j=0;j<NCUTS;j++){
//          if(
//             (j==0) ||
//
//             (j==1 && met > 200.) ||
//
//             (j==2 && met > 200 && phi4min > 0.4) ||
//
//             (j==3 && met > 200 && phi4min > 0.4 && nLeptons == 0) ||
//
//             (j==4 && met > 200 && phi4min > 0.4 && nLeptons == 0 && (nJets == 4 || nJets == 5)) ||
//
//             (j==5 && met > 200 && phi4min > 0.4 && nLeptons == 0 && (nJets == 4 || nJets == 5) && mlead > 110. && mlead < 150.) ||
//
//             (j==6 && met > 200 && phi4min > 0.4 && nLeptons == 0 && (nJets == 4 || nJets == 5) && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140.) ||
//
//             (j==7 && met > 200 && phi4min > 0.4 && nLeptons == 0 && (nJets == 4 || nJets == 5) && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && mTmin > 130.) ||
//
//             (j==8 && met > 200 && phi4min > 0.4 && nLeptons == 0 && (nJets == 4 || nJets == 5)  && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && mTmin > 130. && meff > 1100.) ||
//
//             (j==9 && met > 200 && phi4min > 0.4 && nLeptons == 0 && (nJets == 4 || nJets == 5)  && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && mTmin > 130. && meff > 1100. && nbJets >= 3) ||
//
//             (j==10 && met > 200 && phi4min > 0.4 && nLeptons == 0 && (nJets == 4 || nJets == 5)  && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && mTmin > 130. && meff > 1100. && nbJets >= 3 && Rbbmax > 0.4 && Rbbmax < 1.4) ||
//
//             (j==11 && met > 200 && phi4min > 0.4 && nLeptons == 0 && (nJets == 4 || nJets == 5) && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && meff > 600.) ||
//
//             (j==12 && met > 200 && phi4min > 0.4 && nLeptons == 0 && (nJets == 4 || nJets == 5) && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && meff > 600. && nbJets >= 4) ||
//
//             (j==13 && met > 200 && phi4min > 0.4 && nLeptons == 0 && (nJets == 4 || nJets == 5) && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && meff > 600. && nbJets >= 4 && Rbbmax > 0.4 && Rbbmax < 1.4)
//
//             ) cutFlowVector[j]++;
//        }

        // Now increment signal region variables
        // First exclusion regions
        if(nbJets == 3 && met > 200 && nLeptons == 0 && phi4min > 0.4 && nJets >= 4 && nJets <= 5 && mTmin > 150. && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && Rbbmax > 0.4 && Rbbmax < 1.4 && meff > 600. && meff < 850.) _numSR["SR-3b-meff1-A"]++;
        if(nbJets == 3 && met > 200 && nLeptons == 0 && phi4min > 0.4 && nJets >= 4 && nJets <= 5 && mTmin > 150. && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && Rbbmax > 0.4 && Rbbmax < 1.4 && meff > 850. && meff < 1100.) _numSR["SR-3b-meff2-A"]++;
        if(nbJets >= 3 && met > 200 && nLeptons == 0 && phi4min > 0.4 && nJets >= 4 && nJets <= 5 && mTmin > 130. && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && Rbbmax > 0.4 && Rbbmax < 1.4 && meff > 1100.) _numSR["SR-3b-meff3-A"]++;
        if(nbJets >= 4 && met > 200 && nLeptons == 0 && phi4min > 0.4 && nJets >= 4 && nJets <= 5 && meff > 600. && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && Rbbmax > 0.4 && Rbbmax < 1.4 && meff < 850.) _numSR["SR-4b-meff1-A"]++;
        if(nbJets >= 4 && met > 200 && nLeptons == 0 && phi4min > 0.4 && nJets >= 4 && nJets <= 5 && meff > 600. && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && Rbbmax > 1.4 && Rbbmax < 2.4 && meff < 850.) _numSR["SR-4b-meff1-B"]++;
        if(nbJets >= 4 && met > 200 && nLeptons == 0 && phi4min > 0.4 && nJets >= 4 && nJets <= 6 && meff > 850. && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && Rbbmax > 0.4 && Rbbmax < 1.4 && meff < 1100.) _numSR["SR-4b-meff2-A"]++;
        if(nbJets >= 4 && met > 200 && nLeptons == 0 && phi4min > 0.4 && nJets >= 4 && nJets <= 6 && meff > 850. && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && Rbbmax > 1.4 && Rbbmax < 2.4 && meff < 1100.) _numSR["SR-4b-meff2-B"]++;
        // Discovery regions
        if(nbJets >= 4 && met > 200 && nLeptons == 0 && phi4min > 0.4 && nJets >= 4 && nJets <= 5 && mlead > 110. && mlead < 150. && msubl > 90. && msubl < 140. && Rbbmax > 0.4 && Rbbmax < 1.4 && meff > 600.) _numSR["SR-4b-meff1-A-disc"]++;

        return;

      } // End of analyze

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_3b_36invfb* specificOther
          = dynamic_cast<const Analysis_ATLAS_13TeV_3b_36invfb*>(other);

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (size_t j=0; j<NCUTS; j++) {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }

        for (auto& el : _numSR) {
          el.second += specificOther->_numSR.at(el.first);
        }

      }


      virtual void collect_results() {

//        // DEBUG
//        double L = 36.1;
////        double xsec = 284.65; // 300 GeV
////        double xsec = 33.81; // 500 GeV
//        double xsec = 3.460; // 800 GeV
//        cout << "DEBUG:" << endl;
//        for (size_t i=0; i<NCUTS; i++)
//        {
//          double ATLAS_abs = cutFlowVectorATLAS[i];
//
//          double eff = (double)cutFlowVector[i] / (double)cutFlowVector[0];
//
//          double GAMBIT_scaled = eff * xsec * L;
//
//          double ratio = GAMBIT_scaled/ATLAS_abs;
//          cout << "DEBUG 1: i: " << i << ":   " << setprecision(4) << ATLAS_abs << "\t" << GAMBIT_scaled << "\t" << "\t" << ratio << "\t\t" << cutFlowVector_str[i] << endl;
//        }
//        cout << "DEBUG:" << endl;

        // Now fill a results object with the results for each SR
        // Only exclusion regions here
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR-3b-meff1-A", 4., {_numSR["SR-3b-meff1-A"], 0.}, {2.5, 1.0}));
        add_result(SignalRegionData("SR-3b-meff2-A", 3., {_numSR["SR-3b-meff2-A"], 0.}, {2.0, 0.5}));
        add_result(SignalRegionData("SR-3b-meff3-A", 0., {_numSR["SR-3b-meff3-A"], 0.}, {0.8, 0.5}));
        add_result(SignalRegionData("SR-4b-meff1-A", 1., {_numSR["SR-4b-meff1-A"], 0.}, {0.43, 0.31}));
        add_result(SignalRegionData("SR-4b-meff1-B", 2., {_numSR["SR-4b-meff1-B"], 0.}, {2.6, 0.9}));
        add_result(SignalRegionData("SR-4b-meff2-A", 1., {_numSR["SR-4b-meff2-A"], 0.}, {0.43, 0.27}));
        add_result(SignalRegionData("SR-4b-meff2-B", 0., {_numSR["SR-4b-meff2-B"], 0.}, {1.3, 0.6}));

        return;
      }

      void analysis_specific_reset() {
        // Clear signal regions
        for (auto& el : _numSR) { el.second = 0.;}

        // Clear cut flow vector
        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }



    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_3b_36invfb)


    //
    // Class for collecting results for discovery regions as a derived class
    //

    class Analysis_ATLAS_13TeV_3b_discoverySR_36invfb : public Analysis_ATLAS_13TeV_3b_36invfb {

    public:
      Analysis_ATLAS_13TeV_3b_discoverySR_36invfb() {
        set_analysis_name("ATLAS_13TeV_3b_discoverySR_36invfb");
      }

      virtual void collect_results() {
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("SR-4b-meff1-A-disc", 2., {_numSR["SR-4b-meff1-A-disc"], 0.}, {0.7, 0.5}));
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_3b_discoverySR_36invfb)


  }
}
