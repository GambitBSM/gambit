#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/BaseAnalysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

/// @brief ATLAS 2 lepton direct stop analysis (36.1fb^-1) - `heavy stop'
///
/// Based on:
///  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2016-27/
///
/// @author Martin White
///
/// Known issues: 
///
/// 1) Photon isolation requirement is missing
/// 2) They use a bizarre HT definition where they don't apply overlap removal 
///    between photons and jets. This might not work for us, since jets won't be 
///    made by photons in our events.
///
/// @warning Not yet validated!
///


namespace Gambit {
  namespace ColliderBit {
    
    bool sortByPT_jet(HEPUtils::Jet* jet1, HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortByPT_lep(HEPUtils::Particle* lep1, HEPUtils::Particle* lep2) { return (lep1->pT() > lep2->pT()); }
    
    
    class Analysis_ATLAS_13TeV_PhotonGGM_36invfb : public HEPUtilsAnalysis {
    private:
      
      // Numbers passing cuts
      int num_SRaa_SL, num_SRaa_SH, num_SRaa_WL, num_SRaa_WH, num_SRaj_L, num_SRaj_L200, num_SRaj_H;
      
      // Cut Flow
      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS;
            
      // // debug
      // ofstream Savelep1;
      // ofstream Savelep2;
      
      // Jet overlap removal
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
        
        // Lepton overlap removal
        void LeptonJetOverlapRemoval(vector<HEPUtils::Particle*> &lepvec, vector<HEPUtils::Jet*> &jetvec, double DeltaRMax) {
            //Routine to do lepton-jet check
            //Discards leptons if they are within DeltaRMax of a jet

            vector<HEPUtils::Particle*> Survivors;

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
      
      Analysis_ATLAS_13TeV_PhotonGGM_36invfb() {

            set_analysis_name("ATLAS_13TeV_PhotonGGM_36invfb");
            set_luminosity(36.1);

	    num_SRaa_SL=0;
	    num_SRaa_SH=0;
	    num_SRaa_WL=0;
	    num_SRaa_WH=0;
	    num_SRaj_L=0;
	    num_SRaj_L200=0;
	    num_SRaj_H=0;
              
            NCUTS= 66;  

            // //debug
            // Savelep1.open("lep1.txt");
            // Savelep2.open("lep2.txt");

            for(int i=0;i<NCUTS;i++){
                cutFlowVector.push_back(0);
                cutFlowVector_str.push_back("");
            }

        }
    
        void analyze(const HEPUtils::Event* event) {
            HEPUtilsAnalysis::analyze(event);

            // Missing energy
            double met = event->met();
            HEPUtils::P4 ptot = event->missingmom();

            // Baseline lepton objects
            vector<HEPUtils::Particle*> blElectrons, blMuons;              // Used for SR-2body and SR-3body 
            vector<HEPUtils::Particle*> baselineElectrons, baselineMuons;  // Used for SR-4body
            for (HEPUtils::Particle* electron : event->electrons()) {
	      bool crack = (electron->abseta() > 1.37) && (electron->abseta() < 1.52);
	      if (electron->pT() > 25. && electron->abseta() < 2.47 && !crack) baselineElectrons.push_back(electron);
            }
            ATLAS::applyTightIDElectronSelection(baselineElectrons);
            
            //const std::vector<double>  a = {0,10.};
            //const std::vector<double>  b = {0,10000.};
            //const vector<double> cMu={0.89};
            //HEPUtils::BinnedFn2D<double> _eff2dMu(a,b,cMu);
            for (HEPUtils::Particle* muon : event->muons()) {
	      //bool hasTrig=has_tag(_eff2dMu, muon->eta(), muon->pT());
	      if (muon->pT() > 25. && muon->abseta() < 2.7) baselineMuons.push_back(muon);
            }
	    
	    // Photons
	    vector<HEPUtils::Particle*> baselinePhotons;
	    for (HEPUtils::Particle* photon : event->photons()) {
	      //if(!random_bool(0.88))continue;
	      bool crack = (photon->abseta() > 1.37) && (photon->abseta() < 1.52);
	      if (photon->pT() > 25. && photon->abseta() < 2.37 && !crack) baselinePhotons.push_back(photon);
            }
	    	    
            // Jets
            vector<HEPUtils::Jet*> jets28;     
	    vector<HEPUtils::Jet*> jets28_nophooverlap; 
            vector<HEPUtils::Jet*> jets25;    
            for (HEPUtils::Jet* jet : event->jets()) {
	      if (jet->pT() > 30. && fabs(jet->eta()) < 2.8) {
		jets28.push_back(jet);
		jets28_nophooverlap.push_back(jet);
	      }
	    }
	    
            // Overlap removal
	    JetLeptonOverlapRemoval(jets28,baselineElectrons,0.2);
	    JetLeptonOverlapRemoval(jets28_nophooverlap,baselineElectrons,0.2);
	    JetLeptonOverlapRemoval(jets28,baselinePhotons,0.2); // JetLepton still works for photons
	    LeptonJetOverlapRemoval(baselineElectrons,jets28_nophooverlap,0.4);
            LeptonJetOverlapRemoval(baselineElectrons,jets28,0.4);
	    LeptonJetOverlapRemoval(baselinePhotons,jets28,0.4); // LeptonJet still works for photons
            LeptonJetOverlapRemoval(baselineMuons,jets28,0.4);
	    LeptonJetOverlapRemoval(baselineMuons,jets28_nophooverlap,0.4);
	    
	    // Make |eta| < 2.5 jets
	    for (HEPUtils::Jet* jet : jets28){
	      if (fabs(jet->eta()) < 2.5) jets25.push_back(jet);
	    }
	
	    //Put signal jets／leptons in pT order
            std::sort(jets28.begin(), jets28.end(), sortByPT_jet);
	    std::sort(jets25.begin(), jets25.end(), sortByPT_jet);
            std::sort(baselineElectrons.begin(), baselineElectrons.end(), sortByPT_lep);
           
            // Function used to get b jets
            vector<HEPUtils::Jet*> bJets25;
	    vector<HEPUtils::Jet*> bJets28;

            const std::vector<double>  a = {0,10.};
            const std::vector<double>  b = {0,10000.};
            const std::vector<double> c = {0.77};
            HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);
            for (HEPUtils::Jet* jet : jets25) {
	      bool hasTag=has_tag(_eff2d, jet->eta(), jet->pT());
	      if(jet->btag() && hasTag) bJets25.push_back(jet);
	    }

	    for (HEPUtils::Jet* jet : jets28) {
	      bool hasTag=has_tag(_eff2d, jet->eta(), jet->pT());
	      if(jet->btag() && hasTag) bJets28.push_back(jet);
	    }
	    
	    // Pre-selection
	    bool preSelection2a=false;
	    if(baselinePhotons.size()==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75.)preSelection2a=true;

	    bool preSelectionSRLaj = false;
	    if(baselinePhotons.size()==1 && baselinePhotons[0]->pT() > 145.)preSelectionSRLaj=true;

	    bool preSelectionSRHaj = false;
	    if(baselinePhotons.size()==1 && baselinePhotons[0]->pT() > 400.)preSelectionSRHaj=true;

	    // Useful variables
	    // "Photon-enhanced" HT, with no overlap removal of photons-jets
	    double HT = 0.;
	    for(HEPUtils::Particle* photon : baselinePhotons) {
	      HT += photon->pT();
	    }
	    for(HEPUtils::Particle* electron : baselineElectrons) {
	      HT += electron->pT();
	    }
	    for(HEPUtils::Particle* muon : baselineMuons) {
	      HT += muon->pT();
	    }
	    for(HEPUtils::Jet* jet : jets28_nophooverlap) {
	      HT += jet->pT();
	    }

	    // meff

	    double meff = met;
	    for(HEPUtils::Particle* photon : baselinePhotons) {
	      meff += photon->pT();
	    }
	    for(HEPUtils::Particle* electron : baselineElectrons) {
	      meff += electron->pT();
	    }
	    for(HEPUtils::Particle* muon : baselineMuons) {
	      meff += muon->pT();
	    }

	    // Note that meff is only used for aj signal regions -> |jet eta| < 2.5 
	    for(HEPUtils::Jet* jet : jets25) {
	      meff += jet->pT();
	    }

	    // dphimin(a,met)

	    double dphimin_amet = 999.;
	    for(HEPUtils::Particle* photon : baselinePhotons) {
	      double dphi_tmp = ptot.deltaPhi(photon->mom());
	      if(dphi_tmp < dphimin_amet)dphimin_amet = dphi_tmp;
	    }

	    double dphimin_j25met = 999.;
	    for(HEPUtils::Jet* jet : jets25) {
	      double dphi_tmp = ptot.deltaPhi(jet->mom());
	      if(dphi_tmp < dphimin_j25met)dphimin_j25met = dphi_tmp;
	    }

	    double dphimin_j28met = 999.;
	    for(HEPUtils::Jet* jet : jets28) {
	      double dphi_tmp = ptot.deltaPhi(jet->mom());
	      if(dphi_tmp < dphimin_j28met)dphimin_j28met = dphi_tmp;
	    }

	    // RT4
	    // Only used in aj regions -> use |jet eta| < 2.5
	    double RT4 = 0.;
	    if(jets25.size() > 3){
	      RT4 = jets25[0]->pT() + jets25[1]->pT() + jets25[2]->pT() + jets25[3]->pT();
	    }
	    double denom=0.;
	    for(HEPUtils::Jet* jet : jets25){
	      denom += jet->pT();
	    }
	    RT4=RT4/denom;

	    // Multiplicities
	    int nLep = baselineElectrons.size() + baselineMuons.size();
	    int nJets25 = jets25.size();
	    int nPhotons = baselinePhotons.size();
	    
	    // All variables are now done
	    // Increment signal region variables
	    // 2a regions
	    if(preSelection2a && met > 150. && HT > 2750 && dphimin_j28met > 0.5)num_SRaa_SL++;
	    if(preSelection2a && met > 250. && HT > 2000 && dphimin_j28met > 0.5 && dphimin_amet > 0.5)num_SRaa_SH++;
	    if(preSelection2a && met > 150. && HT > 1500 && dphimin_j28met > 0.5)num_SRaa_WL++;
	    if(preSelection2a && met > 250. && HT > 1000 && dphimin_j28met > 0.5 && dphimin_amet > 0.5)num_SRaa_WH++;

	    // aj regions
	    if(preSelectionSRLaj && nJets25 >=5 && nLep == 0 && met > 300. && meff > 2000. && RT4 < 0.90 && dphimin_j25met > 0.5 && dphimin_amet > 0.5)num_SRaj_L++;
	    if(preSelectionSRLaj && nJets25 >=5 && nLep == 0 && met > 200. && meff > 2000. && RT4 < 0.90 && dphimin_j25met > 0.5 && dphimin_amet > 0.5)num_SRaj_L200++;
	    if(preSelectionSRHaj && nJets25 >=3 && nLep == 0 && met > 400. && meff > 2400. && dphimin_j25met > 0.5 && dphimin_amet > 0.5)num_SRaj_H++;
	    
	    
            /*                                                       */
            /*********************************************************/
            cutFlowVector_str[0] = "Total ";
            /*---------------------------------------*/
            cutFlowVector_str[1] = "SBL: trigger && 2 photons";
            cutFlowVector_str[2] = "SBL: PhotonsPt";
            cutFlowVector_str[3] = "SBL: MET";
            cutFlowVector_str[4] = "SBL: HT";
            cutFlowVector_str[5] = "SBL: dPhiMin(jet,met)";
            cutFlowVector_str[6] = "SBL: dPhiMin(gamma,met)";

	    cutFlowVector_str[7] = "SBH: trigger && 2 photons";
            cutFlowVector_str[8] = "SBH: PhotonsPt";
            cutFlowVector_str[9] = "SBH: MET";
            cutFlowVector_str[10] = "SBH: HT";
            cutFlowVector_str[11] = "SBH: dPhiMin(jet,met)";
            cutFlowVector_str[12] = "SBH: dPhiMin(gamma,met)";

	    cutFlowVector_str[13] = "WBL: trigger && 2 photons";
            cutFlowVector_str[14] = "WBL: PhotonsPt";
            cutFlowVector_str[15] = "WBL: MET";
            cutFlowVector_str[16] = "WBL: HT";
            cutFlowVector_str[17] = "WBL: dPhiMin(jet,met)";
            cutFlowVector_str[18] = "WBL: dPhiMin(gamma,met)";

	    cutFlowVector_str[19] = "WBH: trigger && 2 photons";
            cutFlowVector_str[20] = "WBH: PhotonsPt";
            cutFlowVector_str[21] = "WBH: MET";
            cutFlowVector_str[22] = "WBH: HT";
            cutFlowVector_str[23] = "WBH: dPhiMin(jet,met)";
            cutFlowVector_str[24] = "WBH: dPhiMin(gamma,met)";

	    cutFlowVector_str[25] = "SRL: trigger && 1 photon";
	    cutFlowVector_str[26] = "SRL: lepton veto";
	    cutFlowVector_str[27] = "SRL: pT_gamma";
	    cutFlowVector_str[28] = "SRL: met";
	    cutFlowVector_str[29] = "SRL: Njets";
	    cutFlowVector_str[30] = "SRL: dphimin(jet,met)";
	    cutFlowVector_str[31] = "SRL: dphimin(gamma,met)";
	    cutFlowVector_str[32] = "SRL: meff";
	    cutFlowVector_str[33] = "SRL: RT4";
		      
	    cutFlowVector_str[34] = "SRH: trigger && 1 photon";
	    cutFlowVector_str[35] = "SRH: lepton veto";
	    cutFlowVector_str[36] = "SRH: pT_gamma";
	    cutFlowVector_str[37] = "SRH: met";
	    cutFlowVector_str[38] = "SRH: Njets";
	    cutFlowVector_str[39] = "SRH: dphimin(jet,met)";
	    cutFlowVector_str[40] = "SRH: dphimin(gamma,met)";
	    cutFlowVector_str[41] = "SRH: meff";
	    
	    for(int j=0;j<NCUTS;j++){
	      if(
		 (j==0) ||

		 /*cutFlowVector_str[1] = "SBL: trigger && 2 photons";
		   cutFlowVector_str[2] = "SBL: PhotonsPt";
		   cutFlowVector_str[3] = "SBL: MET";
		   cutFlowVector_str[4] = "SBL: HT";
		   cutFlowVector_str[5] = "SBL: dPhiMin(jet,met)";
		   cutFlowVector_str[6] = "SBL: dPhiMin(gamma,met)";*/
		 
		 (j==1 && nPhotons==2) ||

		 (j==2 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75.) ||

		 (j==3 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150.) ||

		 (j==4 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 2750.) ||

		 (j==5 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 2750. && dphimin_j28met > 0.5) ||

		 (j==6 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 2750. && dphimin_j28met > 0.5) || // No extra cut in this case

		 /* cutFlowVector_str[7] = "SBH: trigger && 2 photons";
		 cutFlowVector_str[8] = "SBH: PhotonsPt";
		 cutFlowVector_str[9] = "SBH: MET";
		 cutFlowVector_str[10] = "SBH: HT";
		 cutFlowVector_str[11] = "SBH: dPhiMin(jet,met)";
		 cutFlowVector_str[12] = "SBH: dPhiMin(gamma,met)";*/
		 
		 (j==7 && nPhotons==2) ||

		 (j==8 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75.) ||

		 (j==9 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250.) ||

		 (j==10 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 2000.) ||

		 (j==11 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 2000. && dphimin_j28met > 0.5) ||

		 (j==12 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 2000. && dphimin_j28met > 0.5 && dphimin_amet > 0.5) || 

		 /* cutFlowVector_str[13] = "WBL: trigger && 2 photons";
		 cutFlowVector_str[14] = "WBL: PhotonsPt";
		 cutFlowVector_str[15] = "WBL: MET";
		 cutFlowVector_str[16] = "WBL: HT";
		 cutFlowVector_str[17] = "WBL: dPhiMin(jet,met)";
		 cutFlowVector_str[18] = "WBL: dPhiMin(gamma,met)";*/

		 (j==13 && nPhotons==2) ||

		 (j==14 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75.) ||

		 (j==15 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150.) ||

		 (j==16 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 1500.) ||

		 (j==17 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 1500. && dphimin_j28met > 0.5) ||

		 (j==18 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 150. && HT > 1500. && dphimin_j28met > 0.5) || // no additional cut in this case

		 /* cutFlowVector_str[19] = "WBH: trigger && 2 photons";
		    cutFlowVector_str[20] = "WBH: PhotonsPt";
		    cutFlowVector_str[21] = "WBH: MET";
		    cutFlowVector_str[22] = "WBH: HT";
		    cutFlowVector_str[23] = "WBH: dPhiMin(jet,met)";
		    cutFlowVector_str[24] = "WBH: dPhiMin(gamma,met)";*/

		 (j==19 && nPhotons==2) ||
		 
		 (j==20 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75.) ||
		 
		 (j==21 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250.) ||

		 (j==22 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 1000.) ||

		 (j==23 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 1000. && dphimin_j28met > 0.5) ||

		 (j==24 && nPhotons==2 && baselinePhotons[0]->pT() > 75. && baselinePhotons[1]->pT() > 75. && met > 250. && HT > 1000. && dphimin_j28met > 0.5 && dphimin_amet > 0.5) || // no additional cut in this case
	    
		 /* cutFlowVector_str[25] = "SRL: trigger && 1 photon";
		    cutFlowVector_str[26] = "SRL: lepton veto";
		    cutFlowVector_str[27] = "SRL: pT_gamma";
		    cutFlowVector_str[28] = "SRL: met";
		    cutFlowVector_str[29] = "SRL: Njets";
		    cutFlowVector_str[30] = "SRL: dphimin(jet,met)";
		    cutFlowVector_str[31] = "SRL: dphimin(gamma,met)";
		    cutFlowVector_str[32] = "SRL: meff";
		    cutFlowVector_str[33] = "SRL: RT4";*/

		 (j==25 && nPhotons==1) ||

		 (j==26 && nPhotons==1 && nLep==0 ) ||

		 (j==27 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145.) ||

		 (j==28 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300.) ||

		 (j==29 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300. && nJets25 >= 5) ||

		 (j==30 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300. && nJets25 >= 5 && dphimin_j25met > 0.4) ||

		 (j==31 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300. && nJets25 >= 5 && dphimin_j25met > 0.4 && dphimin_amet > 0.4) ||

		 (j==32 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300. && nJets25 >= 5 && dphimin_j25met > 0.4 && dphimin_amet > 0.4 && meff > 2000.) ||

		 (j==33 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 145. && met > 300. && nJets25 >= 5 && dphimin_j25met > 0.4 && dphimin_amet > 0.4 && meff > 2000. && RT4 < 0.90) ||

		 /* cutFlowVector_str[34] = "SRH: trigger && 1 photon";
		    cutFlowVector_str[35] = "SRH: lepton veto";
		    cutFlowVector_str[36] = "SRH: pT_gamma";
		    cutFlowVector_str[37] = "SRH: met";
		    cutFlowVector_str[38] = "SRH: Njets";
		    cutFlowVector_str[39] = "SRH: dphimin(jet,met)";
		    cutFlowVector_str[40] = "SRH: dphimin(gamma,met)";
		    cutFlowVector_str[41] = "SRH: meff";*/

		 (j==34 && nPhotons==1) ||
		 
		 (j==35 && nPhotons==1 && nLep==0 ) ||

		 (j==36 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400.) ||
		 
		 (j==37 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400. && met > 400.) ||

		 (j==38 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400. && met > 400. && nJets25 >= 3) ||

		 (j==39 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400. && met > 400. && nJets25 >= 3 && dphimin_j25met > 0.4) ||

		 (j==40 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400. && met > 400. && nJets25 >= 3 && dphimin_j25met > 0.4 && dphimin_amet > 0.4) ||

		 (j==41 && nPhotons==1 && nLep==0 && baselinePhotons[0]->pT() > 400. && met > 400. && nJets25 >= 3 && dphimin_j25met > 0.4 && dphimin_amet > 0.4 && meff > 2400.)
		 
		 )cutFlowVector[j]++;
	      
	    }

        return;

        }


        void add(BaseAnalysis* other) {
            // The base class add function handles the signal region vector and total # events.
            HEPUtilsAnalysis::add(other);

            Analysis_ATLAS_13TeV_PhotonGGM_36invfb* specificOther
                = dynamic_cast<Analysis_ATLAS_13TeV_PhotonGGM_36invfb*>(other);

            // Here we will add the subclass member variables:
            if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
            for (int j=0; j<NCUTS; j++) {
                cutFlowVector[j] += specificOther->cutFlowVector[j];
                cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
            }
	    
	    //num_SRaj_L, num_SRaj_L200, num_SRaj_H;

	    num_SRaa_SL += specificOther->num_SRaa_SL;
	    num_SRaa_SH += specificOther->num_SRaa_SH;
	    num_SRaa_WL += specificOther->num_SRaa_WL;
	    num_SRaa_WH += specificOther->num_SRaa_WH;
	    num_SRaj_L += specificOther->num_SRaj_L;
	    num_SRaj_L200 += specificOther->num_SRaj_L200;
	    num_SRaj_H += specificOther->num_SRaj_H;
	    
        }


        void collect_results() {

            // double scale_by=1.;
            // cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
            // cout << "CUT FLOW: ATLAS 13 TeV 2 lep stop paper "<<endl;
            // cout << "------------------------------------------------------------------------------------------------------------------------------"<<endl;
            // cout<< right << setw(40) << "CUT" <<  "," << setw(20) << "RAW" <<  "," << setw(20) << "SCALED"
            // <<  "," << setw(20) << "%" <<  "," << setw(20) << "clean adj RAW"<<  "," << setw(20) << "clean adj %" << endl;
            // for (int j=0; j<NCUTS; j++) {
            //     cout << right <<  setw(40) << cutFlowVector_str[j].c_str() <<  "," << setw(20)
            //     << cutFlowVector[j] <<  "," << setw(20) << cutFlowVector[j]*scale_by <<  "," << setw(20)
            //     << 100.*cutFlowVector[j]/cutFlowVector[0] << "%" <<  "," << setw(20)
            //     << cutFlowVector[j]*scale_by <<  "," << setw(20) << 100.*cutFlowVector[j]/cutFlowVector[0]<< "%" << endl;
            // }
            // cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;

	  
     	  
	  SignalRegionData results_SRaa_SL;
	  results_SRaa_SL.sr_label = "SRaa_SL";
	  results_SRaa_SL.n_observed = 0.;
	  results_SRaa_SL.n_background = 0.50;
	  results_SRaa_SL.background_sys = 0.30;
	  results_SRaa_SL.signal_sys = 0.;
	  results_SRaa_SL.n_signal = num_SRaa_SL;
	  add_result(results_SRaa_SL);

	  SignalRegionData results_SRaa_SH;
	  results_SRaa_SH.sr_label = "SRaa_SH";
	  results_SRaa_SH.n_observed = 0.;
	  results_SRaa_SH.n_background = 0.48;
	  results_SRaa_SH.background_sys = 0.30;
	  results_SRaa_SH.signal_sys = 0.;
	  results_SRaa_SH.n_signal = num_SRaa_SH;
	  add_result(results_SRaa_SH);

	  SignalRegionData results_SRaa_WL;
	  results_SRaa_WL.sr_label = "SRaa_WL";
	  results_SRaa_WL.n_observed = 6.;
	  results_SRaa_WL.n_background = 3.7;
	  results_SRaa_WL.background_sys = 1.1;
	  results_SRaa_WL.signal_sys = 0.;
	  results_SRaa_WL.n_signal = num_SRaa_WL;
	  add_result(results_SRaa_WL);

	  SignalRegionData results_SRaa_WH;
	  results_SRaa_WH.sr_label = "SRaa_WH";
	  results_SRaa_WH.n_observed = 1.;
	  results_SRaa_WH.n_background = 2.05;
	  results_SRaa_WH.background_sys = 0.65;
	  results_SRaa_WH.signal_sys = 0.;
	  results_SRaa_WH.n_signal = num_SRaa_WH;
	  add_result(results_SRaa_WH);

	  SignalRegionData results_SRaj_L;
	  results_SRaj_L.sr_label = "SRaj_L";
	  results_SRaj_L.n_observed = 4.;
	  results_SRaj_L.n_background = 1.33;
	  results_SRaj_L.background_sys = 0.54;
	  results_SRaj_L.signal_sys = 0.;
	  results_SRaj_L.n_signal = num_SRaj_L;
	  add_result(results_SRaj_L);

	  SignalRegionData results_SRaj_L200;
	  results_SRaj_L200.sr_label = "SRaj_L200";
	  results_SRaj_L200.n_observed = 8.;
	  results_SRaj_L200.n_background = 2.68;
	  results_SRaj_L200.background_sys = 0.64;
	  results_SRaj_L200.signal_sys = 0.;
	  results_SRaj_L200.n_signal = num_SRaj_L200;
	  add_result(results_SRaj_L200);

	  SignalRegionData results_SRaj_H;
	  results_SRaj_H.sr_label = "SRaj_H";
	  results_SRaj_H.n_observed = 3.;
	  results_SRaj_H.n_background = 1.14;
	  results_SRaj_H.background_sys = 0.61;
	  results_SRaj_H.signal_sys = 0.;
	  results_SRaj_H.n_signal = num_SRaj_H;
	  add_result(results_SRaj_H);
	  
	  return;
        }
      
    protected:
      void clear() {
	num_SRaa_SL=0;
	num_SRaa_SH=0;
	num_SRaa_WL=0;
	num_SRaa_WH=0;
	num_SRaj_L=0;
	num_SRaj_L200=0;
	num_SRaj_H=0;
	
	std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

	
      
	};

    

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_PhotonGGM_36invfb)


  }
}
