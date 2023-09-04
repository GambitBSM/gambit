#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

// #include "RestFrames/RestFrames.hh"

using namespace std;

/* The ATLAS 0 lepton direct stop analysis

   Based on: https://arxiv.org/abs/1709.04183

   Code by Martin White

   KNOWN ISSUES

   a) Should apply Very Loose selection to electron candidates
   b) Cannot apply requirement that the ETmiss calculated from tracking information is aligned in phi with that calculated from the calo system.
   c) We do not apply the tau veto. Could approximate by removing events with tagged taus in?

Note: have removed RJ code for now to save time (the cutflows are too divergent to make this code usable, probably due to the Pythia ISR modelling).

*/

namespace Gambit {
  namespace ColliderBit {

    // Need two different functions here for use with std::sort
    bool sortByPT13(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortByPT13_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2) { return sortByPT13(jet1.get(), jet2.get()); }

    // Need two different functions here for use with std::sort
    bool sortByMass(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->mass() > jet2->mass()); }
    bool sortByMass_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2) { return sortByMass(jet1.get(), jet2.get()); }

    double calcMT(HEPUtils::P4 jetMom,HEPUtils::P4 metMom){

      //std::cout << "metMom.px() " << metMom.px() << " jetMom PT " << jetMom.pT() << std::endl;

      double met=sqrt(metMom.px()*metMom.px()+metMom.py()*metMom.py());
      double dphi = metMom.deltaPhi(jetMom);
      double mt=sqrt(2*jetMom.pT()*met*(1-std::cos(dphi)));

      return mt;

    }


    class Analysis_ATLAS_13TeV_0LEPStop_36invfb : public Analysis {
    private:

      // Numbers passing cuts

      std::map<string, EventCounter> _counters = {
        {"SRA_TT", EventCounter("SRA_TT")},
        {"SRA_TW", EventCounter("SRA_TW")},
        {"SRA_T0", EventCounter("SRA_T0")},
        {"SRB_TT", EventCounter("SRB_TT")},
        {"SRB_TW", EventCounter("SRB_TW")},
        {"SRB_T0", EventCounter("SRB_T0")},
        {"SRC1", EventCounter("SRC1")},
        {"SRC2", EventCounter("SRC2")},
        {"SRC3", EventCounter("SRC3")},
        {"SRC4", EventCounter("SRC4")},
        {"SRC5", EventCounter("SRC5")},
        {"SRD_low", EventCounter("SRD_low")},
        {"SRD_high", EventCounter("SRD_high")},
        {"SRE", EventCounter("SRE")},
      };

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS; //=16;

      // Define RestFrames objects

      /*unique_ptr<RestFrames::LabRecoFrame> LAB;
      unique_ptr<RestFrames::DecayRecoFrame> CM;
      unique_ptr<RestFrames::DecayRecoFrame> S;
      unique_ptr<RestFrames::VisibleRecoFrame> ISR;
      unique_ptr<RestFrames::VisibleRecoFrame> V;
      unique_ptr<RestFrames::InvisibleRecoFrame> I;
      unique_ptr<RestFrames::InvisibleGroup>  INV;
      unique_ptr<RestFrames::CombinatoricGroup> VIS;
      unique_ptr<RestFrames::SetMassInvJigsaw>   InvMass;
      unique_ptr<RestFrames::MinMassesCombJigsaw> SplitVis;*/



      void LeptonLeptonOverlapRemoval(vector<const HEPUtils::Particle*> &lep1vec, vector<const HEPUtils::Particle*> &lep2vec, double DeltaRMax) {

          //Routine to do jet-lepton check
        //Discards jets if they are within DeltaRMax of a lepton

        vector<const HEPUtils::Particle*> Survivors;

        for(unsigned int itlep1 = 0; itlep1 < lep1vec.size(); itlep1++) {
          bool overlap = false;
          HEPUtils::P4 lep1mom=lep1vec.at(itlep1)->mom();
          for(unsigned int itlep2 = 0; itlep2 < lep2vec.size(); itlep2++) {
            HEPUtils::P4 lep2mom=lep2vec.at(itlep2)->mom();
            double dR;

            dR=lep1mom.deltaR_eta(lep2mom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lep1vec.at(itlep1));
        }
        lep1vec=Survivors;

        return;
      }

      void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &lepvec, double DeltaRMax) {
        //Routine to do jet-lepton check
        //Discards jets if they are within DeltaRMax of a lepton

        vector<const HEPUtils::Jet*> Survivors;

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

      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec, double DeltaRMax) {
        //Routine to do lepton-jet check
        //Discards leptons if they are within DeltaRMax of a jet

        vector<const HEPUtils::Particle*> Survivors;

        for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
          bool overlap = false;
          HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
          for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            double dR;

            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lepvec.at(itlep));
        }
        lepvec=Survivors;

        return;
      }


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_0LEPStop_36invfb() {

        set_analysis_name("ATLAS_13TeV_0LEPStop_36invfb");
        set_luminosity(36.);

        NCUTS=120;

        for(int i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVector_str.push_back("");
        }

        // RestFrames initialisation

        /*LAB.reset(new RestFrames::LabRecoFrame("LAB","lab"));
        CM.reset(new RestFrames::DecayRecoFrame("CM","cm"));
        S.reset(new RestFrames::DecayRecoFrame("S","s"));
        ISR.reset(new RestFrames::VisibleRecoFrame("ISR","isr"));
        V.reset(new RestFrames::VisibleRecoFrame("V","v"));
        I.reset(new RestFrames::InvisibleRecoFrame("I","i"));

        // Connect the frames
        LAB->SetChildFrame(*CM);
        CM->AddChildFrame(*ISR);
        CM->AddChildFrame(*S);
        S->AddChildFrame(*V);
        S->AddChildFrame(*I);

        // Initialize the tree
        LAB->InitializeTree();

        // Define groups
        INV.reset(new RestFrames::InvisibleGroup("INV","inv"));
        INV->AddFrame(*I);
        VIS.reset(new RestFrames::CombinatoricGroup("VIS","vis"));
        VIS->AddFrame(*ISR);
        VIS->SetNElementsForFrame(*ISR,1,false);
        VIS->AddFrame(*V);
        VIS->SetNElementsForFrame(*V,0,false);

        // set the invisible system mass to zero
        InvMass.reset(new RestFrames::SetMassInvJigsaw("InvMass","kSetMass"));
        INV->AddJigsaw(*InvMass);

        // define the rule for partitioning objects between "ISR" and "V"
        SplitVis.reset(new RestFrames::MinMassesCombJigsaw("CombPPJigsaw", "kMinMasses"));
        VIS->AddJigsaw(*SplitVis);
        // "0" group (ISR)
        SplitVis->AddFrame(*ISR, 0);
        // "1" group (V + I)
        SplitVis->AddFrame(*V,1);
        SplitVis->AddFrame(*I,1);

        LAB->InitializeAnalysis();*/

      }



      void run(const HEPUtils::Event* event) {

        // Missing energy
        HEPUtils::P4 metVec = event->missingmom();
        double Met = event->met();


        // Baseline lepton objects
        vector<const HEPUtils::Particle*> baselineElectrons, baselineMuons, baselineTaus;

        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 7. && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 6. && muon->abseta() < 2.7) baselineMuons.push_back(muon);
        }

        // Apply lepton efficiencies
        ATLAS::applyElectronEff(baselineElectrons);
        ATLAS::applyMuonEff(baselineMuons);

        // Photons
        vector<const HEPUtils::Particle*> signalPhotons;
        for (const HEPUtils::Particle* photon : event->photons()) {
          signalPhotons.push_back(photon);
        }


        // No taus used in 13 TeV analysis?
        //for (const HEPUtils::Particle* tau : event->taus()) {
        //if (tau->pT() > 10. && tau->abseta() < 2.47) baselineTaus.push_back(tau);
        //}
        //ATLAS::applyTauEfficiencyR1(baselineTaus);


        // Jets
        vector<const HEPUtils::Jet*> bJets;
        vector<const HEPUtils::Jet*> nonBJets;
        vector<const HEPUtils::Jet*> trueBJets; //for debugging

        // Get b jets
        /// @note We assume that b jets have previously been 100% tagged
        const std::vector<double>  a = {0,10.};
        const std::vector<double>  b = {0,10000.};
        const std::vector<double> c = {0.77}; // set b-tag efficiency to 77%
        HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);
        for (const HEPUtils::Jet* jet : event->jets())
        {
          bool hasTag=has_tag(_eff2d, fabs(jet->eta()), jet->pT());
          if (jet->pT() > 20. && fabs(jet->eta()) < 2.8)
          {
            if(jet->btag() && hasTag && fabs(jet->eta()) < 2.5 && jet->pT() > 20.)
            {
              bJets.push_back(jet);
            }
            else
            {
              nonBJets.push_back(jet);
            }
          }
        }

        // Overlap removal
        // Note: use paper description instead of code snippet
        JetLeptonOverlapRemoval(nonBJets,baselineElectrons,0.2);
        LeptonJetOverlapRemoval(baselineElectrons,nonBJets,0.4);
        LeptonJetOverlapRemoval(baselineElectrons,bJets,0.4);
        LeptonJetOverlapRemoval(baselineMuons,nonBJets,0.4);
        LeptonJetOverlapRemoval(baselineMuons,bJets,0.4);

        // Fill a jet-pointer-to-bool map to make it easy to check
        // if a given jet is treated as a b-jet in this analysis
        map<const HEPUtils::Jet*,bool> analysisBtags;
        for (const HEPUtils::Jet* jet : bJets) analysisBtags[jet] = true;
        for (const HEPUtils::Jet* jet : nonBJets) analysisBtags[jet] = false;

        // Signal object containers
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        vector<const HEPUtils::Particle*> electronsForVeto;
        vector<const HEPUtils::Particle*> muonsForVeto;

        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBJets;
        vector<const HEPUtils::Jet*> signalNonBJets;

        // It seems that there are no extra signal jet requirements (unlike 8 TeV analysis)
        for (const HEPUtils::Jet* jet : bJets) {
          signalJets.push_back(jet);
          signalBJets.push_back(jet);
        }

        for (const HEPUtils::Jet* jet : nonBJets) {
          signalJets.push_back(jet);
          signalNonBJets.push_back(jet);
        }

        //Put signal jets in pT order
        std::sort(signalJets.begin(), signalJets.end(), sortByPT13);
        std::sort(signalBJets.begin(), signalBJets.end(), sortByPT13);
        std::sort(signalNonBJets.begin(), signalNonBJets.end(), sortByPT13);

        for (const HEPUtils::Particle* electron : baselineElectrons) {
          signalElectrons.push_back(electron);
        }

        for (const HEPUtils::Particle* muon : baselineMuons) {
          signalMuons.push_back(muon);
        }

        // Need to recluster jets at this point (R=0.8 and R=1.2)
        vector<std::shared_ptr<HEPUtils::Jet>> fatJetsR8=get_jets(signalJets,0.8);
        vector<std::shared_ptr<HEPUtils::Jet>> fatJetsR12=get_jets(signalJets,1.2);

        //Put 1_2 signal jets in decreasing pT order
        std::sort(fatJetsR12.begin(), fatJetsR12.end(), sortByPT13_sharedptr);

        //Put 0_8 signal jets in pT order
        std::sort(fatJetsR8.begin(), fatJetsR8.end(), sortByPT13_sharedptr);

        // We now have the signal electrons, muons, jets and b jets- move on to the analysis

        // The following code follow the ATLAS public snippet closely
        float DRBB = 0;
        int NBJets = signalBJets.size();

        float AntiKt8M_0 = 0;
        float AntiKt8M_1 = 0;
        float AntiKt12M_0 = 0;
        float AntiKt12M_1 = 0;
        // float MtTauCand = -1 ;
        float MtBMin = 0 ;
        float MtBMax = 0 ;

        if (fatJetsR8.size()>0)  AntiKt8M_0 = fatJetsR8[0]->mass() ;
        if (fatJetsR8.size()>1)  AntiKt8M_1 = fatJetsR8[1]->mass() ;
        if (fatJetsR12.size()>0) AntiKt12M_0 = fatJetsR12[0]->mass() ;
        if (fatJetsR12.size()>1) AntiKt12M_1 = fatJetsR12[1]->mass() ;
        if (NBJets>1) DRBB = signalBJets[1]->mom().deltaR_eta(signalBJets[0]->mom());

        double dPhi_min = 1000.;
        double dPhi_max = 0.;
        if (signalBJets.size()>=2)  {
          for (const HEPUtils::Jet* jet : signalBJets) {
            double dphi = fabs(metVec.deltaPhi(jet->mom()));
            if (dphi<dPhi_min) {
              dPhi_min=dphi;
              MtBMin=calcMT(jet->mom(),metVec);
            }
            if (dphi>dPhi_max) {
              dPhi_max=dphi;
              MtBMax=calcMT(jet->mom(),metVec);
            }
          }
        }

        float realWMass = 80.385;
        float realTopMass = 173.210;

         //Chi2 method
        double Chi2min = 99999999999999999.;
        int W1j1_low = -1,W1j2_low = -1,W2j1_low = -1,W2j2_low = -1,b1_low = -1,b2_low = -1;

        double m_mt2Chi2 = 0;

        if (signalJets.size()>=4 && signalBJets.size()>=2 && signalNonBJets.size()>=2)
          {
            for(int W1j1=0; W1j1<(int)signalNonBJets.size(); W1j1++) {// <------------------This lines has to be replaced
              for(int W2j1=0;W2j1<(int)signalNonBJets.size(); W2j1++) {// <------------------This lines has to be replaced
                if (W2j1==W1j1) continue;// <------------------This lines has to be added
                //            for(int W1j1=0; W1j1<(int)ljets.size()-1; W1j1++) {
                //            for(int W2j1=W1j1+1;W2j1<(int)ljets.size(); W2j1++) {
                for(int b1=0;b1<(int)signalBJets.size();b1++){
                  for(int b2=0;b2<(int)signalBJets.size();b2++){
                    if(b2==b1) continue;
                    double chi21, chi22, mW1, mW2, mt1, mt2;

                    if(W2j1>W1j1){

                      mW1 = signalNonBJets[W1j1]->mass();
                      mW2 = signalNonBJets[W2j1]->mass();
                      mt1 = (signalNonBJets[W1j1]->mom()+signalBJets[b1]->mom()).m();
                      mt2 = (signalNonBJets[W2j1]->mom()+signalBJets[b2]->mom()).m();

                      chi21 = (mW1-realWMass)*(mW1-realWMass)/realWMass + (mt1-realTopMass)*(mt1-realTopMass)/realTopMass;
                      chi22 = (mW2-realWMass)*(mW2-realWMass)/realWMass + (mt2-realTopMass)*(mt2-realTopMass)/realTopMass;

                      if(Chi2min > (chi21 + chi22)){
                        Chi2min = chi21 + chi22;
                        if(chi21 < chi22){
                          W1j1_low = W1j1;
                          W1j2_low = -1;
                          W2j1_low = W2j1;
                          W2j2_low = -1;
                          b1_low = b1;
                          b2_low = b2;
                        }
                        else{
                          W2j1_low = W1j1;
                          W2j2_low = -1;
                          W1j1_low = W2j1;
                          W1j2_low = -1;
                          b2_low = b1;
                          b1_low = b2;
                        }
                      }
                    }

                    if (signalNonBJets.size()<3)
                      continue;

                    for(int W1j2=W1j1+1;W1j2 < (int)signalNonBJets.size(); W1j2++) {
                      if(W1j2==W2j1) continue;

                      //try bll,bl top candidates
                      mW1 = (signalNonBJets[W1j1]->mom() + signalNonBJets[W1j2]->mom()).m();
                      mW2 = (signalNonBJets[W2j1])->mass();
                      mt1 = (signalNonBJets[W1j1]->mom() + signalNonBJets[W1j2]->mom() + signalBJets[b1]->mom()).m();
                      mt2 = (signalNonBJets[W2j1]->mom() + signalBJets[b2]->mom()).m();
                      chi21 = (mW1-realWMass)*(mW1-realWMass)/realWMass + (mt1-realTopMass)*(mt1-realTopMass)/realTopMass;
                      chi22 = (mW2-realWMass)*(mW2-realWMass)/realWMass + (mt2-realTopMass)*(mt2-realTopMass)/realTopMass;
                      if(Chi2min > (chi21 + chi22)){
                        Chi2min = chi21 + chi22;
                        if(chi21 < chi22){
                          W1j1_low = W1j1;
                          W1j2_low = W1j2;
                          W2j1_low = W2j1;
                          W2j2_low = -1;
                          b1_low = b1;
                          b2_low = b2;
                        }
                        else{
                          W2j1_low = W1j1;
                          W2j2_low = W1j2;
                          W1j1_low = W2j1;
                          W1j2_low = -1;
                          b2_low = b1;
                          b1_low = b2;
                        }
                      }
                      if(signalNonBJets.size() < 4)continue;
                      //try bll, bll top candidates
                      for(int W2j2=W2j1+1;W2j2<(int)signalNonBJets.size(); W2j2++){
                        if((W2j2==W1j1) || (W2j2==W1j2)) continue;
                        if(W2j1<W1j1) continue;  //runtime reasons, we don't want combinations checked twice <--------------------This line should be added
                        mW1 = (signalNonBJets[W1j1]->mom() + signalNonBJets[W1j2]->mom()).m();
                        mW2 = (signalNonBJets[W2j1]->mom() + signalNonBJets[W2j2]->mom()).m();
                        mt1 = (signalNonBJets[W1j1]->mom() + signalNonBJets[W1j2]->mom() + signalBJets[b1]->mom()).m();
                        mt2 = (signalNonBJets[W2j1]->mom() + signalNonBJets[W2j2]->mom() + signalBJets[b2]->mom()).m();
                        chi21 = (mW1-realWMass)*(mW1-realWMass)/realWMass + (mt1-realTopMass)*(mt1-realTopMass)/realTopMass;
                        chi22 = (mW2-realWMass)*(mW2-realWMass)/realWMass + (mt2-realTopMass)*(mt2-realTopMass)/realTopMass;
                        if(Chi2min > (chi21 + chi22)){
                          Chi2min = chi21 + chi22;
                          if(chi21 < chi22){
                            W1j1_low = W1j1;
                            W1j2_low = W1j2;
                            W2j1_low = W2j1;
                            W2j2_low = W2j2;
                            b1_low = b1;
                            b2_low = b2;
                          }
                          else{
                            W2j1_low = W1j1;
                            W2j2_low = W1j2;
                            W1j1_low = W2j1;
                            W1j2_low = W2j2;
                            b2_low = b1;
                            b1_low = b2;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }

            HEPUtils::P4 WCand0=signalNonBJets[W1j1_low]->mom();
            if (W1j2_low != -1) WCand0 +=signalNonBJets[W1j2_low]->mom();
            HEPUtils::P4 topCand0 = WCand0 + signalBJets[b1_low]->mom();

            HEPUtils::P4 WCand1 = signalNonBJets[W2j1_low]->mom();
            if(W2j2_low != -1) WCand1 += signalNonBJets[W2j2_low]->mom();
            HEPUtils::P4 topCand1 = WCand1 + signalBJets[b2_low]->mom();

            HEPUtils::P4 tempTop0=HEPUtils::P4::mkEtaPhiMPt(0.,topCand0.phi(),173.210,topCand0.pT());
            HEPUtils::P4 tempTop1=HEPUtils::P4::mkEtaPhiMPt(0.,topCand1.phi(),173.210,topCand1.pT());

            // Note that the first component here is the mass
            // This must be the top mass (i.e. mass of our vectors) and not zero!

            double pa_a[3] = { tempTop0.m() , tempTop0.px(), tempTop0.py() };
            double pb_a[3] = { tempTop1.m() , tempTop1.px(), tempTop1.py() };
            double pmiss_a[3] = { 0, metVec.px(), metVec.py() };
            double mn_a = 0.;

            mt2_bisect::mt2 mt2_event_a;

            mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
            mt2_event_a.set_mn(mn_a);

            m_mt2Chi2  = mt2_event_a.get_mt2();

          }

        float MT2Chi2 = m_mt2Chi2;

        // RestFrames stuff

        /*double CA_PTISR=0;
        double CA_MS=0;
        double CA_NbV=0;
        double CA_NjV=0;
        double CA_RISR=0;
        double CA_dphiISRI=0;
        double CA_pTjV4=0;
        double CA_pTbV1=0;

        int m_NjV(0);
        int m_NbV(0);
        int m_NbISR(0);
        double m_pTjV4(0.);
        double m_pTbV1(0);
        double m_PTISR(0.);
        double m_MS(0.);
        double m_RISR(0.);
        double m_dphiISRI(0.);

        LAB->ClearEvent();

        if (!(Met<250 || (baselineElectrons.size()+baselineMuons.size())>0 || signalJets.size()<4 || signalBJets.size()<1 || signalJets[3]->pT()<40)){

          std::vector<RestFrames::RFKey> jetID;

          for(size_t i=0;i<signalJets.size();i++){

            TLorentzVector tmpJet;
            tmpJet.SetPtEtaPhiM(signalJets[i]->pT(),0.,signalJets[i]->phi(),signalJets[i]->mass());

            jetID.push_back(VIS->AddLabFrameFourVector(tmpJet));

          }

          TVector3 ETMiss;
          ETMiss.SetXYZ(metVec.px(),metVec.py(),0.0);
          INV->SetLabFrameThreeVector(ETMiss);

          if(!LAB->AnalyzeEvent()) std::cout << "Something went wrong..." << std::endl;

          for(size_t i = 0; i < signalJets.size(); i++){
            if (VIS->GetFrame(jetID[i]) == *V){ // sparticle group
              m_NjV++;
              if (m_NjV == 4) m_pTjV4 = signalJets[i]->pT();
              if ( analysisBtags.at(signalJets[i]) && fabs(signalJets[i]->eta())<2.5) {
                m_NbV++;
                if (m_NbV == 1) m_pTbV1 = signalJets[i]->pT();
              }
            } else {
              if ( analysisBtags.at(signalJets[i]) && fabs(signalJets[i]->eta())<2.5)
                m_NbISR++;
            }
          }

          // need at least one jet associated with MET-side of event
          if(m_NjV >= 1)
            {
              TVector3 vP_ISR = ISR->GetFourVector(*CM).Vect();
              TVector3 vP_I   = I->GetFourVector(*CM).Vect();

              m_PTISR = vP_ISR.Mag();
              m_RISR = fabs(vP_I.Dot(vP_ISR.Unit())) / m_PTISR;

              m_MS = S->GetMass();

              m_dphiISRI = fabs(vP_ISR.DeltaPhi(vP_I));

              CA_PTISR=m_PTISR;
              CA_MS=m_MS;
              CA_NbV=m_NbV;
              CA_NjV=m_NjV;
              CA_RISR=m_RISR;
              CA_dphiISRI=m_dphiISRI;
              CA_pTjV4=m_pTjV4;
              CA_pTbV1=m_pTbV1;
            }
            }*/


        bool isSRA_TT=false;
        bool isSRA_TW=false;
        bool isSRA_T0=false;
        bool isSRB_TT=false;
        bool isSRB_TW=false;
        bool isSRB_T0=false;
        bool isSRC1=false;
        bool isSRC2=false;
        bool isSRC3=false;
        bool isSRC4=false;
        bool isSRC5=false;
        bool isSRD_low=false;
        bool isSRD_high=false;
        bool isSRE=false;

        cutFlowVector_str[0] = "No cuts ";
        cutFlowVector_str[1] = "Derivation skim";
        cutFlowVector_str[2] = "Lepton veto ";
        cutFlowVector_str[3] = "Njets >= 4 ";
        cutFlowVector_str[4] = "Nbjets >= 1 ";
        cutFlowVector_str[5] = "met > 250 GeV ";
        cutFlowVector_str[6] = "dPhi(jet,MET) > 0.4 ";
        cutFlowVector_str[7] = "pT jet 1 > 80 GeV ";
        cutFlowVector_str[8] = "pT jet 3 > 40 GeV ";
        cutFlowVector_str[9] = "m jet0, R=1.2 > 120 GeV ";
        cutFlowVector_str[10] = "SRA-TT: m jet1, R=1.2 > 120 GeV";
        cutFlowVector_str[11] = "SRA-TT: met > 400 GeV";
        cutFlowVector_str[12] = "SRA-TT: m jet0, R=0.8 > 60 GeV ";
        cutFlowVector_str[13] = "SRA-TT: mT(b,MET) min > 200 ";
        cutFlowVector_str[14] = "SRA-TT: deltaR(b,b) > 1 ";
        cutFlowVector_str[15] = "SRA-TT: mT2 > 400 GeV";
        cutFlowVector_str[16] = "SRA-TT: Nbjets >=2 ";
        cutFlowVector_str[17] = "SRA-TW: m jet1, R=1.2 < 120 GeV";
        cutFlowVector_str[18] = "SRA-TW: m jet1, R=1.2 > 60 GeV";
        cutFlowVector_str[19] = "SRA-TW: met > 500 GeV ";
        cutFlowVector_str[20] = "SRA-TW: m jet0, R=0.8 > 60 GeV";
        cutFlowVector_str[21] = "SRA-TW: mT(b,MET) min > 200 GeV";
        cutFlowVector_str[22] = "SRA-TW: mT2 > 400 GeV ";
        cutFlowVector_str[23] = "SRA-TW: Nbjets >=2 ";
        cutFlowVector_str[24] = "SRA-T0: m jet1, R=1.2 < 60 GeV";
        cutFlowVector_str[25] = "SRA-T0: m jet0, R=0.8 > 60 GeV";
        cutFlowVector_str[26] = "SRA-T0: met > 550 GeV ";
        cutFlowVector_str[27] = "SRA-T0: mT(b,MET) min > 200 GeV";
        cutFlowVector_str[28] = "SRA-T0: mT2 > 500 GeV ";
        cutFlowVector_str[29] = "SRA-T0: Nbjets >=2 ";
        cutFlowVector_str[30] = "SRB-TT: m jet1, R=1.2 > 120 GeV";
        cutFlowVector_str[31] = "SRB-TT: deltaR(b,b) > 1.2";
        cutFlowVector_str[32] = "SRB-TT: mT(b,MET) max > 200 GeV";
        cutFlowVector_str[33] = "SRB-TT: mT(b,MET) min > 200 GeV";
        cutFlowVector_str[34] = "SRB-TT: Nbjets >=2 ";
        cutFlowVector_str[35] = "SRB-TW: m jet1, R=1.2 < 120 GeV";
        cutFlowVector_str[36] = "SRB-TW: m jet1, R=1.2 > 60 GeV";
        cutFlowVector_str[37] = "SRB-TW: deltaR(b,b) > 1.2";
        cutFlowVector_str[38] = "SRB-TW: mT(b,MET) max > 200 GeV";
        cutFlowVector_str[39] = "SRB-TW: mT(b,MET) min > 200 GeV";
        cutFlowVector_str[40] = "SRB-TW: Nbjets >=2 ";
        cutFlowVector_str[41] = "SRB-T0: m jet1, R=1.2 < 60 GeV";
        cutFlowVector_str[42] = "SRB-T0: mT(b,MET) min > 200 GeV";
        cutFlowVector_str[43] = "SRB-T0: deltaR(b,b) > 1.2";
        cutFlowVector_str[44] = "SRB-T0: mT(b,MET) max > 200 GeV";
        cutFlowVector_str[45] = "SRB-T0: met > 250 GeV ";
        cutFlowVector_str[46] = "SRB-T0: Nbjets >=2 ";

        // Cutflow for SRD
        cutFlowVector_str[47] = "SRD-high: No cuts ";
        cutFlowVector_str[48] = "SRD-high: Derivation skim";
        cutFlowVector_str[49] = "SRD-high: Lepton veto ";
        cutFlowVector_str[50] = "SRD-high: Njets >= 4 ";
        cutFlowVector_str[51] = "SRD-high: Nbjets >= 1 ";
        cutFlowVector_str[52] = "SRD-high: met > 250 GeV ";
        cutFlowVector_str[53] = "SRD-high: dPhi(jet,MET) > 0.4 ";
        cutFlowVector_str[54] = "SRD-high: pT jet 1 > 80 GeV ";
        cutFlowVector_str[55] = "SRD-high: pT jet 3 > 40 GeV ";
        cutFlowVector_str[56] = "SRD-high: Njets >= 5 ";
        cutFlowVector_str[57] = "SRD-high: pT jet 1 > 150 ";
        cutFlowVector_str[58] = "SRD-high: pT jet 3 > 80 ";
        cutFlowVector_str[59] = "SRD-high: pT jet 4 > 60 ";
        cutFlowVector_str[60] = "SRD-high: mT(b,MET) min > 350 GeV ";
        cutFlowVector_str[61] = "SRD-high: mT(b,MET) max > 450 GeV ";
        cutFlowVector_str[62] = "SRD-high: Nbjets >=2 ";
        cutFlowVector_str[63] = "SRD-high: met > 250 GeV ";
        cutFlowVector_str[64] = "SRD-high: deltaR(b,b) > 0.8";
        cutFlowVector_str[65] = "SRD-high: pT0b + pT1b > 400 GeV";
        cutFlowVector_str[66] = "SRD-low: Njets >=5";
        cutFlowVector_str[67] = "SRD-low: NBjets >=2";
        cutFlowVector_str[68] = "SRD-low: met > 250 GeV";
        cutFlowVector_str[69] = "SRD-low: mT(b,MET) min > 250 GeV ";
        cutFlowVector_str[70] = "SRD-low: mT(b,MET) max > 300 GeV ";
        cutFlowVector_str[71] = "SRD-low: deltaR(b,b) > 0.8";
        cutFlowVector_str[72] = "SRD-low: pT jet 1 > 150 GeV ";
        cutFlowVector_str[73] = "SRD-low: pT jet 3 > 100 GeV ";
        cutFlowVector_str[74] = "SRD-low: pT jet 4 > 60 GeV ";
        cutFlowVector_str[75] = "SRD-low: pT0b + pT1b > 300 GeV";

        // Cutflow for SRE
        cutFlowVector_str[76] = "SRE: met > 550 GeV";
        cutFlowVector_str[77] = "SRE: m jet0, R = 0.8 > 120 GeV";
        cutFlowVector_str[78] = "SRE: m jet1, R = 0.8 > 80 GeV";
        cutFlowVector_str[79] = "SRE: HT > 800 GeV";
        cutFlowVector_str[80] = "SRE: met/sqrt(HT) > 18 GeV^1/2";
        cutFlowVector_str[81] = "SRE: mT(b,MET) min > 200 GeV";
        cutFlowVector_str[82] = "SRE: NBjets >=2";

        // Cutflow for SRC1

        cutFlowVector_str[83] = "SRC: Derivation skim";
        cutFlowVector_str[84] = "SRC: Lepton veto ";
        cutFlowVector_str[85] = "SRC: Njets >= 4 ";
        cutFlowVector_str[86] = "SRC: Nbjets >= 1 ";
        cutFlowVector_str[87] = "SRC: met > 250 GeV ";
        cutFlowVector_str[88] = "SRC: dPhi(jet,MET) > 0.4 ";
        cutFlowVector_str[89] = "SRC: pT jet 1 > 80 GeV ";
        cutFlowVector_str[90] = "SRC: pT jet 3 > 40 GeV ";
        cutFlowVector_str[91] = "SRC: NSbjet >=1";
        cutFlowVector_str[92] = "SRC: NSjet >=5";
        cutFlowVector_str[93] = "SRC: pT0sb > 40";
        cutFlowVector_str[94] = "SRC: mS > 300";
        cutFlowVector_str[95] = "SRC: dPhi(ISR,met) > 3";
        cutFlowVector_str[96] = "SRC: pTISR > 400";
        cutFlowVector_str[97] = "SRC: pT4S > 50";
        cutFlowVector_str[98] = "SRC1: 0.30 <= R_ISR <= 0.40";
        cutFlowVector_str[99] = "SRC2: 0.40 <= R_ISR <= 0.50";
        cutFlowVector_str[100] = "SRC3: 0.50 <= R_ISR <= 0.60";
        cutFlowVector_str[101] = "SRC4: 0.60 <= R_ISR <= 0.70";
        cutFlowVector_str[102] = "SRC5: 0.70 <= R_ISR <= 0.80";

        int nElectrons=signalElectrons.size();
        int nMuons=signalMuons.size();
        int nJets=signalJets.size();

        bool cut_LeptonVeto=true;
        if((nElectrons + nMuons)>0.)cut_LeptonVeto=false;

        double Ht=0;

        for(size_t jet=0;jet<signalJets.size();jet++)Ht+=signalJets[jet]->pT();

        double HtSig = Met/sqrt(Ht);

        bool devSkim = false;

        if( (Ht > 150.) || (signalElectrons.size() > 0 && signalElectrons[0]->pT() > 100.) || (signalElectrons.size() > 1 && signalElectrons[0]->pT() > 20. && signalElectrons[1]->pT() > 20.) || (signalMuons.size() > 0 && signalMuons[0]->pT() > 100.) || (signalMuons.size() > 1 && signalMuons[0]->pT() > 20. && signalMuons[1]->pT() > 20.) || (signalPhotons.size() > 0 && signalPhotons[0]->pT() > 100.) || (signalPhotons.size() > 1 && signalPhotons[0]->pT() > 50. && signalPhotons[1]->pT() > 50.))devSkim=true;

        bool cut_dPhiJetsPresel=false;
        bool cut_dPhiJet2=false;
        bool cut_dPhiJet1=false;
        double dphi_jetmet1=9999;
        if(nJets>0)dphi_jetmet1=std::acos(std::cos(signalJets.at(0)->phi()-metVec.phi()));
        double dphi_jetmet2=9999;
        if(nJets>1)dphi_jetmet2=std::acos(std::cos(signalJets.at(1)->phi()-metVec.phi()));
        if(dphi_jetmet2>0.4)cut_dPhiJet2=true;
        if(dphi_jetmet1>0.4)cut_dPhiJet1=true;
        if(cut_dPhiJet1 && cut_dPhiJet2)cut_dPhiJetsPresel=true;

        bool cut_dPhiJet3=false;
        bool cut_dPhiJets_AB=false;
        double dphi_jetmet3=9999;
        if(nJets>2)dphi_jetmet3=std::acos(std::cos(signalJets.at(2)->phi()-metVec.phi()));
        if(dphi_jetmet3>0.4)cut_dPhiJet3=true;
        if(cut_dPhiJetsPresel && cut_dPhiJet3)cut_dPhiJets_AB=true;

        //if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && DRBB > 1.2 && MtBMax > 200. && MtBMin > 200.)std::cout << "Met " << Met << " AntiKt12M_0 " << AntiKt12M_0 << " AntiKt12M_1 " << AntiKt12M_1 << " DRBB " << DRBB << " MtBMax " << MtBMax << " MtBMin " << MtBMin << std::endl;


        for(int j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             (j==1 && devSkim) ||

             (j==2 && devSkim && cut_LeptonVeto) ||

             (j==3 && devSkim && cut_LeptonVeto && signalJets.size()>3) ||

             (j==4 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0) ||

             (j==5 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250.) ||

             (j==6 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB) ||

             (j==7 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80.) ||

             (j==8 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40.) ||

             (j==9 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120.) ||

             // SRA-TT

             (j==10 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120.) ||

             (j==11 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 400. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120.) ||

             (j==12 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 400. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && AntiKt8M_0>60.) ||

             (j==13 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 400. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && AntiKt8M_0>60. && MtBMin > 200.) ||

             (j==14 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 400. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && AntiKt8M_0>60. && MtBMin > 200. && DRBB > 1.) ||

             (j==15 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 400. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && AntiKt8M_0>60. && MtBMin > 200. && DRBB > 1. &&  MT2Chi2>400.) ||

             (j==16 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 400. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && AntiKt8M_0>60. && MtBMin > 200. && DRBB > 1. &&  MT2Chi2>400. && NBJets>=2) ||

             // SRA-TW

             /* cutFlowVector_str[17] = "SRA-TW: m jet1, R=1.2 < 120 GeV";
                cutFlowVector_str[18] = "SRA-TW: m jet1, R=1.2 > 60 GeV";
                cutFlowVector_str[19] = "SRA-TW: met > 500 GeV ";
                cutFlowVector_str[20] = "SRA-TW: m jet0, R=0.8 > 60 GeV";
                cutFlowVector_str[21] = "SRA-TW: mT(b,MET) min > 200 GeV";
                cutFlowVector_str[22] = "SRA-TW: mT2 > 400 GeV ";*/

             (j==17 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. &&  AntiKt12M_0>120. && AntiKt12M_1<120.)  ||

             (j==18 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. && AntiKt12M_1>60.)  ||

             (j==19 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. && AntiKt12M_1>60. && Met > 500.)  ||

             (j==20 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. && AntiKt12M_1>60. && Met > 500. &&  AntiKt8M_0>60.)  ||

             (j==21 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. && AntiKt12M_1>60. && Met > 500. &&  AntiKt8M_0>60. && MtBMin > 200.)  ||

             (j==22 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. && AntiKt12M_1>60. && Met > 500. &&  AntiKt8M_0>60. && MtBMin > 200. && MT2Chi2>400.)  ||

             (j==23 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. && AntiKt12M_1>60. && Met > 500. &&  AntiKt8M_0>60. && MtBMin > 200. && MT2Chi2>400.) ||

             /* cutFlowVector_str[24] = "SRA-T0: m jet1, R=1.2 < 60 GeV";
                cutFlowVector_str[25] = "SRA-T0: m jet0, R=0.8 > 60 GeV";
                cutFlowVector_str[26] = "SRA-T0: met > 550 GeV ";
                cutFlowVector_str[27] = "SRA-T0: mT(b,MET) min > 200 GeV";
                cutFlowVector_str[28] = "SRA-T0: mT2 > 500 GeV ";
                cutFlowVector_str[29] = "SRA-T0: Nbjets >=2 "; */


             (j==24 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0 > 120. && AntiKt12M_1<60.)  ||

             (j==25 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0 > 120. && AntiKt12M_1<60. && AntiKt8M_0>60.)  ||

             (j==26 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0 > 120. && AntiKt12M_1<60. && AntiKt8M_0>60. && Met > 550.)  ||

             (j==27 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0 > 120. && AntiKt12M_1<60. && AntiKt8M_0>60. && Met > 550. &&  MtBMin > 200.)  ||

             (j==28 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0 > 120. && AntiKt12M_1<60. && AntiKt8M_0>60. && Met > 550. &&  MtBMin > 200. && MT2Chi2 > 500.)  ||

             (j==29 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0 > 120. && AntiKt12M_1<60. && AntiKt8M_0>60. && Met > 550. &&  MtBMin > 200. && MT2Chi2 > 500.) ||

             /* cutFlowVector_str[30] = "SRB-TT: m jet1, R=1.2 > 120 GeV";
             cutFlowVector_str[31] = "SRB-TT: deltaR(b,b) > 1.2";
             cutFlowVector_str[32] = "SRB-TT: mT(b,MET) max > 200 GeV";
             cutFlowVector_str[33] = "SRB-TT: mT(b,MET) min > 200 GeV";
             cutFlowVector_str[34] = "SRB-TT: Nbjets >=2 ";*/

             (j==30 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120.)  ||

             (j==31 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && DRBB > 1.2)  ||

             (j==32 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && DRBB > 1.2 && MtBMax > 200.)  ||

             (j==33 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && DRBB > 1.2 && MtBMax > 200. && MtBMin > 200.)  ||

             (j==34 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && DRBB > 1.2 && MtBMax > 200. && MtBMin > 200.)  ||

             /* cutFlowVector_str[35] = "SRB-TW: m jet1, R=1.2 < 120 GeV";
             cutFlowVector_str[36] = "SRB-TW: m jet1, R=1.2 > 60 GeV";
             cutFlowVector_str[37] = "SRB-TW: deltaR(b,b) > 1.2";
             cutFlowVector_str[38] = "SRB-TW: mT(b,MET) max > 200 GeV";
             cutFlowVector_str[39] = "SRB-TW: mT(b,MET) min > 200 GeV";
             cutFlowVector_str[40] = "SRB-TW: Nbjets >=2 ";*/

             (j==35 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120.)  ||

             (j==36 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. &&AntiKt12M_1>60.)  ||

             (j==37 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. &&AntiKt12M_1>60. && DRBB > 1.2)  ||

             (j==38 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. &&AntiKt12M_1>60. && DRBB > 1.2 &&  MtBMax > 200.)   ||

             (j==39 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. &&AntiKt12M_1>60. && DRBB > 1.2 &&  MtBMax > 200. && MtBMin > 200.)   ||

             (j==40 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. &&AntiKt12M_1>60. && DRBB > 1.2 &&  MtBMax > 200. && MtBMin > 200.)   ||

             /* cutFlowVector_str[41] = "SRB-T0: m jet1, R=1.2 < 60 GeV";
                cutFlowVector_str[42] = "SRB-T0: mT(b,MET) min > 200 GeV";
                cutFlowVector_str[43] = "SRB-T0: deltaR(b,b) > 1.2";
                cutFlowVector_str[44] = "SRB-T0: mT(b,MET) max > 200 GeV";
                cutFlowVector_str[45] = "SRB-T0: met > 250 GeV ";
                cutFlowVector_str[46] = "SRB-T0: Nbjets >=2 ";*/

             (j==41 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<60.)  ||

             (j==42 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<60. && MtBMin > 200.)  ||

             (j==43 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<60. && MtBMin > 200. && DRBB > 1.2)  ||

             (j==44 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<60. && MtBMin > 200. && DRBB > 1.2 && MtBMax > 200.)  ||

             (j==45 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<60. && MtBMin > 200. && DRBB > 1.2 && MtBMax > 200.)  ||

             (j==46 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<60. && MtBMin > 200. && DRBB > 1.2 && MtBMax > 200.) ||

              // Cutflow for SRD
             /*cutFlowVector_str[47] = "SRD-high: No cuts ";
             cutFlowVector_str[48] = "SRD-high: Derivation skim";
             cutFlowVector_str[49] = "SRD-high: Lepton veto ";
             cutFlowVector_str[50] = "SRD-high: Njets >= 4 ";
             cutFlowVector_str[51] = "SRD-high: Nbjets >= 1 ";
             cutFlowVector_str[52] = "SRD-high: met > 250 GeV ";
             cutFlowVector_str[53] = "SRD-high: dPhi(jet,MET) > 0.4 ";
             cutFlowVector_str[54] = "SRD-high: pT jet 1 > 80 GeV ";
             cutFlowVector_str[55] = "SRD-high: pT jet 3 > 40 GeV ";
             cutFlowVector_str[56] = "SRD-high: Njets >= 5 ";
             cutFlowVector_str[57] = "SRD-high: pT jet 1 > 150 ";
             cutFlowVector_str[58] = "SRD-high: pT jet 3 > 80 ";
             cutFlowVector_str[59] = "SRD-high: pT jet 4 > 60 ";
             cutFlowVector_str[60] = "SRD-high: mT(b,MET) min > 350 GeV ";
             cutFlowVector_str[61] = "SRD-high: mT(b,MET) max > 450 GeV ";
             cutFlowVector_str[62] = "SRD-high: Nbjets >=2 ";
             cutFlowVector_str[63] = "SRD-high: met > 250 GeV ";
             cutFlowVector_str[64] = "SRD-high: deltaR(b,b) > 0.8";
             cutFlowVector_str[65] = "SRD-high: pT0b + pT1b > 400 GeV";*/

             (j==47) ||

             (j==48 && devSkim) ||

             (j==49 && devSkim && cut_LeptonVeto) ||

             (j==50 && devSkim && cut_LeptonVeto && signalJets.size()>3) ||

             (j==51 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0) ||

             (j==52 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250.) ||

             (j==53 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB) ||

             (j==54 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80.) ||

             (j==55 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. )  ||

             (j==56 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. )  ||

             (j==57 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>40. )  ||

             (j==58 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>80. )  ||

             (j==59 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>80. && signalJets[4]->pT()>60.)  ||

             (j==60 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>80. && signalJets[4]->pT()>60. && MtBMin > 350.)  ||

             (j==61 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>80. && signalJets[4]->pT()>60. && MtBMin > 350. && MtBMax > 450.)  ||

             (j==62 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>80. && signalJets[4]->pT()>60. && MtBMin > 350. && MtBMax > 450.)  ||

             (j==63 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>80. && signalJets[4]->pT()>60. && MtBMin > 350. && MtBMax > 450.)  ||

             (j==64 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>80. && signalJets[4]->pT()>60. && MtBMin > 350. && MtBMax > 450. && DRBB > 0.8)  ||

             (j==65 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>80. && signalJets[4]->pT()>60. && MtBMin > 350. && MtBMax > 450. && DRBB > 0.8 && ( (signalBJets[0]->pT() + signalBJets[1]->pT())>400.)) ||

             /*cutFlowVector_str[66] = "SRD-low: Njets >=5";
             cutFlowVector_str[67] = "SRD-low: NBjets >=2";
             cutFlowVector_str[68] = "SRD-low: met > 250 GeV";
             cutFlowVector_str[69] = "SRD-low: mT(b,MET) min > 250 GeV ";
             cutFlowVector_str[70] = "SRD-low: mT(b,MET) max > 300 GeV ";
             cutFlowVector_str[71] = "SRD-low: deltaR(b,b) > 0.8";
             cutFlowVector_str[72] = "SRD-low: pT jet 1 > 150 GeV ";
             cutFlowVector_str[73] = "SRD-low: pT jet 3 > 100 GeV ";
             cutFlowVector_str[74] = "SRD-low: pT jet 4 > 60 GeV ";
             cutFlowVector_str[75] = "SRD-low: pT0b + pT1b > 300 GeV";*/


             (j==66 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40.)  ||

             (j==67 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40.)  ||

             (j==68 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40.)  ||

             (j==69 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && MtBMin > 250.)  ||

             (j==70 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && MtBMin > 250. && MtBMax > 300.)  ||

             (j==71 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && MtBMin > 250. && MtBMax > 300. && DRBB > 0.8)  ||

             (j==72 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>40. && MtBMin > 250. && MtBMax > 300. && DRBB > 0.8)  ||

             (j==73 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>100. && MtBMin > 250. && MtBMax > 300. && DRBB > 0.8)  ||

             (j==74 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>100. && signalJets[4]->pT()>60. && MtBMin > 250. && MtBMax > 300. && DRBB > 0.8)  ||

             (j==75 && devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>100. && signalJets[4]->pT()>60. && MtBMin > 250. && MtBMax > 300. && DRBB > 0.8 &&  ( (signalBJets[0]->pT() + signalBJets[1]->pT())>300.))   ||

             /* cutFlowVector_str[76] = "SRE: met > 550 GeV";
                cutFlowVector_str[77] = "SRE: m jet0, R = 0.8 > 120 GeV";
                cutFlowVector_str[78] = "SRE: m jet1, R = 0.8 > 80 GeV";
                cutFlowVector_str[79] = "SRE: HT > 800 GeV";
                cutFlowVector_str[80] = "SRE: met/sqrt(HT) > 18 GeV^1/2";
                cutFlowVector_str[81] = "SRE: mT(b,MET) min > 200 GeV";
                cutFlowVector_str[82] = "SRE: NBjets >=2";*/

             (j==76 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 550. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40.)  ||

             (j==77 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 550. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt8M_0 > 120.)  ||

             (j==78 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 550. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt8M_0 > 120. && AntiKt8M_1 > 80.)  ||

             (j==79 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 550. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt8M_0 > 120. && AntiKt8M_1 > 80. && Ht > 800.)  ||

             (j==80 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 550. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt8M_0 > 120. && AntiKt8M_1 > 80. && Ht > 800. && HtSig > 18.)  ||

             (j==81 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 550. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt8M_0 > 120. && AntiKt8M_1 > 80. && Ht > 800. && HtSig > 18. && MtBMin > 200.)  ||

             (j==82 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 550. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt8M_0 > 120. && AntiKt8M_1 > 80. && Ht > 800. && HtSig > 18. && MtBMin > 200.)

             /*cutFlowVector_str[83] = "SRC: Derivation skim";
               cutFlowVector_str[84] = "SRC: Lepton veto ";
               cutFlowVector_str[85] = "SRC: Njets >= 4 ";
               cutFlowVector_str[86] = "SRC: Nbjets >= 1 ";
               cutFlowVector_str[87] = "SRC: met > 250 GeV ";
               cutFlowVector_str[88] = "SRC: dPhi(jet,MET) > 0.4 ";
               cutFlowVector_str[89] = "SRC: pT jet 1 > 80 GeV ";
               cutFlowVector_str[90] = "SRC: pT jet 3 > 40 GeV ";
               cutFlowVector_str[91] = "SRC: NSbjet >=1";
               cutFlowVector_str[92] = "SRC: NSjet >=5";
               cutFlowVector_str[93] = "SRC: pT0sb > 40";
               cutFlowVector_str[94] = "SRC: mS > 300";
               cutFlowVector_str[95] = "SRC: dPhi(ISR,met) > 3";
               cutFlowVector_str[96] = "SRC: pTISR > 400";
               cutFlowVector_str[97] = "SRC: pT4S > 50";
               cutFlowVector_str[98] = "SRC1: 0.30 <= R_ISR <= 0.40";
               cutFlowVector_str[99] = "SRC2: 0.40 <= R_ISR <= 0.50";
               cutFlowVector_str[100] = "SRC3: 0.50 <= R_ISR <= 0.60";
               cutFlowVector_str[101] = "SRC4: 0.60 <= R_ISR <= 0.70";
               cutFlowVector_str[102] = "SRC5: 0.70 <= R_ISR <= 0.80";*/

             /*(j==83 && devSkim) ||

             (j==84 && devSkim && cut_LeptonVeto) ||

             (j==85 && devSkim && cut_LeptonVeto && signalJets.size()>3) ||

             (j==86 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0) ||

             (j==87 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250.) ||

             (j==88 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB) ||

             (j==89 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80.) ||

             (j==90 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. )  ||

             (j==91 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1)  ||

             (j==92 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5)  ||

             (j==93 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40)  ||

             (j==94 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300)  ||

             (j==95 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00)  ||

             (j==96 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400)  ||

             (j==97 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50)  ||

             (j==98 && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50 && CA_RISR >= 0.30 && CA_RISR <= 0.4)  ||

             (j==99  && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50 && CA_RISR >= 0.40 && CA_RISR <= 0.5) ||

             (j==100  && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50 && CA_RISR >= 0.50 && CA_RISR <= 0.6) ||

             (j==101  && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50 && CA_RISR >= 0.60 && CA_RISR <= 0.7) ||

             (j==102  && devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50 && CA_RISR >= 0.70 && CA_RISR <= 0.8) */


             ){

            cutFlowVector[j]++;
          }

        }


        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 400. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && AntiKt8M_0>60. && MtBMin > 200. && DRBB > 1. &&  MT2Chi2>400. && NBJets>=2)isSRA_TT=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. && AntiKt12M_1>60. && Met > 500. &&  AntiKt8M_0>60. && MtBMin > 200. && MT2Chi2>400.)isSRA_TW=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0 > 120. && AntiKt12M_1<60. && AntiKt8M_0>60. && Met > 550. &&  MtBMin > 200. && MT2Chi2 > 500.)isSRA_T0=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1>120. && DRBB > 1.2 && MtBMax > 200. && MtBMin > 200.)isSRB_TT=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<120. &&AntiKt12M_1>60. && DRBB > 1.2 &&  MtBMax > 200. && MtBMin > 200.)isSRB_TW=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt12M_0>120. && AntiKt12M_1<60. && MtBMin > 200. && DRBB > 1.2 && MtBMax > 200.)isSRB_T0=true;

        /*if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50 && CA_RISR >= 0.30 && CA_RISR <= 0.4)isSRC1=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50 && CA_RISR >= 0.40 && CA_RISR <= 0.5)isSRC2=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50 && CA_RISR >= 0.50 && CA_RISR <= 0.6)isSRC3=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50 && CA_RISR >= 0.60 && CA_RISR <= 0.7)isSRC4=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>0 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && CA_NbV >= 1 && CA_NjV >= 5 && CA_pTbV1 > 40 && CA_MS > 300 && CA_dphiISRI > 3.00 && CA_PTISR > 400 && CA_pTjV4 > 50 && CA_RISR >= 0.70 && CA_RISR <= 0.8)isSRC5=true;*/

        if( devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>80. && signalJets[4]->pT()>60. && MtBMin > 350. && MtBMax > 450. && DRBB > 0.8 && ( (signalBJets[0]->pT() + signalBJets[1]->pT())>400.))isSRD_high=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>4 && signalBJets.size()>1 && Met > 250. && cut_dPhiJets_AB && signalJets[1]->pT()>150. && signalJets[3]->pT()>100. && signalJets[4]->pT()>60. && MtBMin > 250. && MtBMax > 300. && DRBB > 0.8 &&  ( (signalBJets[0]->pT() + signalBJets[1]->pT())>300.))isSRD_low=true;

        if(devSkim && cut_LeptonVeto && signalJets.size()>3 && signalBJets.size()>1 && Met > 550. && cut_dPhiJets_AB && signalJets[1]->pT()>80. && signalJets[3]->pT()>40. && AntiKt8M_0 > 120. && AntiKt8M_1 > 80. && Ht > 800. && HtSig > 18. && MtBMin > 200.)isSRE=true;


        if(isSRA_TT) _counters.at("SRA_TT").add_event(event);
        if(isSRA_TW) _counters.at("SRA_TW").add_event(event);
        if(isSRA_T0) _counters.at("SRA_T0").add_event(event);
        if(isSRB_TT) _counters.at("SRB_TT").add_event(event);
        if(isSRB_TW) _counters.at("SRB_TW").add_event(event);
        if(isSRB_T0) _counters.at("SRB_T0").add_event(event);
        if(isSRC1) _counters.at("SRC1").add_event(event);
        if(isSRC2) _counters.at("SRC2").add_event(event);
        if(isSRC3) _counters.at("SRC3").add_event(event);
        if(isSRC4) _counters.at("SRC4").add_event(event);
        if(isSRC5) _counters.at("SRC5").add_event(event);
        if(isSRD_low) _counters.at("SRD_low").add_event(event);
        if(isSRD_high) _counters.at("SRD_high").add_event(event);
        if(isSRE) _counters.at("SRE").add_event(event);

        return;

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_0LEPStop_36invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_13TeV_0LEPStop_36invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (int j=0; j<NCUTS; j++) {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }
      }


      void collect_results() {

        // double scale_by=1.;
        // cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
        // cout << "CUT FLOW: ATLAS 13 TeV 0 lep stop paper "<<endl;
        // cout << "------------------------------------------------------------------------------------------------------------------------------"<<endl;
        // cout<< right << setw(40) << "CUT" << setw(20) << "RAW" << setw(20) << "SCALED"
        //     << setw(20) << "%" << setw(20) << "clean adj RAW"<< setw(20) << "clean adj %" << endl;
        // for (int j=0; j<NCUTS; j++) {
        //   cout << right << setw(40) << cutFlowVector_str[j].c_str() << setw(20)
        //        << cutFlowVector[j] << setw(20) << cutFlowVector[j]*scale_by << setw(20)
        //        << 100.*cutFlowVector[j]/cutFlowVector[0] << "%" << setw(20)
        //        << cutFlowVector[j]*scale_by << setw(20) << 100.*cutFlowVector[j]/cutFlowVector[0]<< "%" << endl;
        // }
        // cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;

        /// Register results objects with the results for each SR; obs & bkg numbers from the paper

        add_result(SignalRegionData(_counters.at("SRA_TT"), 11, {8.6, 2.1}));
        add_result(SignalRegionData(_counters.at("SRA_TW"), 9, {9.3, 2.2}));
        add_result(SignalRegionData(_counters.at("SRA_T0"),  18, {18.7, 2.7}));
        add_result(SignalRegionData(_counters.at("SRB_TT"),  38, { 39.3,  7.6}));
        add_result(SignalRegionData(_counters.at("SRB_TW"), 53, {52.4, 7.4}));
        add_result(SignalRegionData(_counters.at("SRB_T0"), 206, { 179.,  26.}));

        // MJW removes the recursive jigsaw signal regions for the Feb 2018 SUSY scans
        // The ISR modelling in Pythia does not give reliable answers

        /*
        add_result(SignalRegionData(_counters.at("SRC1"), 20, { 20.6,  6.5}));
        add_result(SignalRegionData(_counters.at("SRC2"), 22, { 27.6,  4.9}));
        add_result(SignalRegionData(_counters.at("SRC3"), 22, {  18.9, 3.4}));
        add_result(SignalRegionData(_counters.at("SRC4"), 1, {  7.7, 1.2}));
        add_result(SignalRegionData(_counters.at("SRC5"), 0, { 0.91,  0.73}));
        */

        add_result(SignalRegionData(_counters.at("SRD_low"), 27, {  25.1, 6.2}));
        add_result(SignalRegionData(_counters.at("SRD_high"), 11, {  8.5,1.5}));
        add_result(SignalRegionData(_counters.at("SRE"), 3, {  3.64,0.79}));

        return;
      }


    protected:
      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };


    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_0LEPStop_36invfb)


  }
}
