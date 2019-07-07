#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "gambit/ColliderBit/lester_mt2_bisect.h"

using namespace std;

// Based on arXiv:1708.09266
// Code by Martin White, January 2018
// Based on ATLAS public code snippet

// Known issues: No lepton isolation cuts applied
// The b tagging working point keeps changing in the ATLAS code snippet, but this is not referred to in the paper
// Have gone with the code snippet version (60% working point for the signal B jets)
//

namespace Gambit {
  namespace ColliderBit {

    /// A useful MT2 class for this module
    class MT2 {
    public:
      MT2(){
        MT2tauB=0;
        aMT2_BM=0;
      }

      double MT2tauB;
      double aMT2_BM;
    };

    class Analysis_ATLAS_13TeV_2bMET_36invfb : public Analysis {
    private:

      // Variables that hold the number of events passing signal region cuts

      double _numb0L_SRA350, _numb0L_SRA450, _numb0L_SRA550, _numb0L_SRB, _numb0L_SRC;
      double _numb1L_SRA600, _numb1L_SRA750, _numb1L_SRA300_2j, _numb1L_SRB;

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS;

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      static bool sortByPT(HEPUtils::Jet* jet1, HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }

      Analysis_ATLAS_13TeV_2bMET_36invfb() {

        set_analysis_name("ATLAS_13TeV_2bMET_36invfb");
        set_luminosity(36.1);

        // Set number of events passing cuts to zero upon initialisation
        _numb0L_SRA350=0; _numb0L_SRA450=0; _numb0L_SRA550=0;
        _numb0L_SRB=0; _numb0L_SRC=0;

        _numb1L_SRA600=0; _numb1L_SRA750=0; _numb1L_SRA300_2j=0; _numb1L_SRB=0;

        NCUTS=70;

        for(int i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
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
            double DeltaRMax = std::max(0.1,std::min(0.4, 0.04 + 10 / lepmom.pT()));
            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lepvec.at(itlep));
        }
        lepvec=Survivors;

        return;
      }

      void SpecialLeptonJetOverlapRemoval(vector<HEPUtils::Particle*> &lepvec, vector<HEPUtils::Jet*> &jetvec) {
        //Routine to do lepton-jet check
        //Discards leptons if they are within dR of a jet as defined in analysis paper

        vector<HEPUtils::Particle*> Survivors;

        for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
          bool overlap = false;
          HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
          for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            double dR;
            double DeltaRMax = std::min(0.4, 0.04 + 10/lepvec[itlep]->pT());
            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lepvec.at(itlep));
        }
        lepvec=Survivors;

        return;
      }


      MT2 MT2helper(vector<HEPUtils::Jet*> jets, vector<HEPUtils::Particle*>  electrons,  vector<HEPUtils::Particle*> muons, HEPUtils::P4 metVec){

        MT2 results;

        bool passmu = false;
        if(muons.size()==1)passmu=true;

        bool passel = false;
        if(electrons.size()==1)passel=true;

        int nJet = jets.size();
        if(nJet < 2)return results;

        //ATLAS use the two jets with highest MV1 weights
        //DELPHES does not have a continuous b weight

        //We have all b jets tagged (with 100% efficiency), so can use the two highest pT b jets
        //This corresponds to using the 2 b jets that are first in the collection

        HEPUtils::Jet* trueBjet1 = NULL; //need to assign this
        HEPUtils::Jet* trueBjet2 = NULL; //nee to assign this

        int nTrueBJets=0;
        for(HEPUtils::Jet* tmpJet: jets){
          if(tmpJet->btag()){
            trueBjet1=tmpJet;
            nTrueBJets++;
            break;
          }
        }

        for(HEPUtils::Jet* tmpJet: jets){
          if(tmpJet->btag() && tmpJet!=trueBjet1){
            trueBjet2=tmpJet;
            nTrueBJets++;
            break;
          }
        }

        if(nTrueBJets<2)return results;


	HEPUtils::P4 jet1B, jet2B;
	jet1B.setXYZE(trueBjet1->mom().px(), trueBjet1->mom().py(), trueBjet1->mom().pz(), trueBjet1->E());
	jet2B.setXYZE(trueBjet2->mom().px(), trueBjet2->mom().py(), trueBjet2->mom().pz(), trueBjet2->E());


        HEPUtils::P4 leptontmp;
        // double leptonmass = 0;
        if(passel){
          // leptonmass = 0.510998910; //MeV
          leptontmp = electrons[0]->mom();
        }
        else if(passmu){
          // leptonmass =  105.658367; // MeV
          leptontmp = muons[0]->mom();
        }


	HEPUtils::P4 lepton;
	lepton.setXYZE(leptontmp.px(),leptontmp.py(),leptontmp.pz(),leptontmp.E());


	HEPUtils::P4 lepton_plus_jet1B;
	HEPUtils::P4 lepton_plus_jet2B;

        lepton_plus_jet1B = lepton+jet1B;
        lepton_plus_jet2B = lepton+jet2B;

        double pa_a[3] = { 0, lepton_plus_jet1B.px(), lepton_plus_jet1B.py() };
        double pb_a[3] = { 80, jet2B.px(), jet2B.py() };
        double pmiss_a[3] = { 0, metVec.px(), metVec.py() };
        double mn_a = 0.;

        mt2_bisect::mt2 mt2_event_a;

        mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
        mt2_event_a.set_mn(mn_a);

        double mt2a = mt2_event_a.get_mt2();

        double pa_b[3] = { 0, lepton_plus_jet2B.px(), lepton_plus_jet2B.py() };
        double pb_b[3] = { 80, jet1B.px(), jet1B.py() };
        double pmiss_b[3] = { 0, metVec.px(), metVec.py() };
        double mn_b = 0.;

        mt2_bisect::mt2 mt2_event_b;

        mt2_event_b.set_momenta(pa_b,pb_b,pmiss_b);
        mt2_event_b.set_mn(mn_b);
        double mt2b = mt2_event_b.get_mt2();

        double aMT2_BM = min(mt2a,mt2b);
        results.aMT2_BM=aMT2_BM;

        if (nJet > 3){
          HEPUtils::Jet* jet3=0;
          for(HEPUtils::Jet* current: jets){
            if (current == trueBjet1)continue;
            if (current == trueBjet2)continue;
            jet3 = current;
            break;
          }


	  HEPUtils::P4 jet3B;
	  jet3B.setXYZE(jet3->mom().px(), jet3->mom().py(), jet3->mom().pz(), jet3->mom().E());

          double pa_tau[3] = { 0, jet3B.px(), jet3B.py() };
          double pb_tau[3] = { 0, lepton.px(), lepton.py() };
          double pmiss_tau[3] = { 0, metVec.px(), metVec.py() };
          double mn_tau = 0.;

          mt2_bisect::mt2 mt2_event_tau;

          mt2_event_tau.set_momenta(pa_tau,pb_tau,pmiss_tau);
          mt2_event_tau.set_mn(mn_tau);

          //ComputeMT2 stuff3(jet3B,lepton,MET,0.,0.);
          //double MT2tauB = stuff3.ComputeNumeric();
          double MT2tauB = mt2_event_tau.get_mt2();//calcMT2(0,jet3B.Pt(),jet3B.Eta(),jet3B.Phi(),jet3B.E(),0,lepton.Pt(),lepton.Eta(),lepton.Phi(),lepton.E(),MET.Px(),MET.Py(),0);
          results.MT2tauB=MT2tauB;
        }
        return results;
      }


      void run(const HEPUtils::Event* event) {

        // Get the missing energy and momentum in the event
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        // Now define vectors of baseline objects, including:
        // - retrieval of electron, muon and jets from the event
        // - application of basic pT and eta cuts
        vector<HEPUtils::Particle*> electrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10.
              && fabs(electron->eta()) < 2.47)
            electrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(electrons);

        vector<HEPUtils::Particle*> muons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10.
              && fabs(muon->eta()) < 2.7)
            muons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(muons);

        //vector<HEPUtils::Jet*> candJets;
        //for (HEPUtils::Jet* jet : event->jets()) {
	//if (jet->pT() > 20.
	//    && fabs(jet->eta()) < 2.8)
	//  candJets.push_back(jet);
        //}

	// Jets
        vector<HEPUtils::Jet*> bJets;
        vector<HEPUtils::Jet*> nonBJets;

	// Get b jets
        /// @note We assume that b jets have previously been 100% tagged
        const std::vector<double>  a = {0,10.};
        const std::vector<double>  b = {0,10000.};
        const std::vector<double> c = {0.77}; // set b-tag efficiency to 77%
        HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);
        for (HEPUtils::Jet* jet : event->jets()) {
          bool hasTag=has_tag(_eff2d, jet->eta(), jet->pT());
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.8) {
            if(jet->btag() && hasTag && fabs(jet->eta()) < 2.5 && jet->pT() > 20.){
              bJets.push_back(jet);
            } else {
              nonBJets.push_back(jet);
            }
          }
        }


	JetLeptonOverlapRemoval(nonBJets,electrons,0.2);
	LeptonJetOverlapRemoval(electrons,nonBJets);
        LeptonJetOverlapRemoval(electrons,bJets);
	JetLeptonOverlapRemoval(nonBJets,muons,0.2);
	SpecialLeptonJetOverlapRemoval(muons,nonBJets);
	SpecialLeptonJetOverlapRemoval(muons,bJets);

	vector<HEPUtils::Jet*> signalJets20;
	vector<HEPUtils::Jet*> signalJets35;
	vector<HEPUtils::Particle*> signalElectrons;
	vector<HEPUtils::Particle*> signalMuons;
	vector<HEPUtils::Particle*> signalLeptons;
	vector<HEPUtils::Jet*> signalBJets20;
	vector<HEPUtils::Jet*> signalBJets35;

	// Now apply signal jet cuts
        for (HEPUtils::Jet* jet : bJets) {
	  jet->set_btag(true);
          if(jet->pT() > 20. && fabs(jet->eta())<2.8){
	    signalJets20.push_back(jet);
	    if(fabs(jet->eta())<2.5)signalBJets20.push_back(jet);
	  }

	  if(jet->pT() > 35. && fabs(jet->eta())<2.8){
	    signalJets35.push_back(jet);
	    if(fabs(jet->eta())<2.5)signalBJets35.push_back(jet);
	  }

        }

        for (HEPUtils::Jet* jet : nonBJets) {
	  jet->set_btag(false);
	  if(jet->pT() > 20. && fabs(jet->eta())<2.8){
	    signalJets20.push_back(jet);
	  }

	  if(jet->pT() > 35. && fabs(jet->eta())<2.8){
	    signalJets35.push_back(jet);
	  }

	}

	// Now order the jet collections by pT

	std::sort(signalJets35.begin(), signalJets35.end(), sortByPT);
	std::sort(signalBJets35.begin(), signalBJets35.end(), sortByPT);
	std::sort(signalJets20.begin(), signalJets20.end(), sortByPT);
	std::sort(signalBJets20.begin(), signalBJets20.end(), sortByPT);


	for (HEPUtils::Particle* electron : electrons) {
	  if(electron->pT() > 20. && fabs(electron->eta()) < 2.47){
            signalElectrons.push_back(electron);
            signalLeptons.push_back(electron);
          }
        }

        for (HEPUtils::Particle* muon : muons) {
          if(muon->pT() > 20. && fabs(muon->eta()) < 2.5){
            signalMuons.push_back(muon);
            signalLeptons.push_back(muon);
          }
        }

	HEPUtils::P4 metVecCorr = metVec;

	for(HEPUtils::Particle* lep : signalLeptons){
	  metVecCorr+=lep->mom();
	}

	// double metCorr = metVecCorr.pT();


	//Common Selection
	int nJets20  = signalJets20.size();
	int nBjets20 = signalBJets20.size();
	int nJets35  = signalJets35.size();
	int nBjets35 = signalBJets35.size();

	bool zeroLep = (signalLeptons.size()==0);
	bool oneLep  = (signalLeptons.size()==1);
	// bool twoLep  = ((signalElectrons.size()==2 && muons.size()==0) || (signalMuons.size()==2 && electrons.size()==0)); //DF

	double meff2j = met;
	double meff = met;
	double ht=0;

	for(int jet=0;jet<nJets35;jet++){
	  if(jet<2) meff2j += signalJets35[jet]->pT();
	  meff += signalJets35[jet]->pT();
	  ht +=  signalJets35[jet]->pT();
	}

	double dphib1 = -99.;
	double dphib2 = -99.;

	if(signalBJets35.size()>0)dphib1=signalBJets35[0]->mom().deltaPhi(metVec);
	if(signalBJets35.size()>1)dphib2=signalBJets35[1]->mom().deltaPhi(metVec);

	double dphiMin4=9999.;

	for(int j=0; j<nJets35; j++){
	  double dPhij=fabs(signalJets35[j]->mom().deltaPhi(metVec));
	  if(j<=3)dphiMin4= min(dphiMin4, dPhij);
	}

	double mjj_35 = 0;
	double mCT = 0;
	double mblmin = 0;
	bool  bjetsLeading = false;


	if(nJets35>=2) {
	  mjj_35 = (signalJets35[0]->mom() + signalJets35[1]->mom()).m();   // = mbb for leading-bjets events

	  double jet1_ET = sqrt(signalJets35[0]->mom().pT()*signalJets35[0]->mom().pT()+signalJets35[0]->mom().m()*signalJets35[0]->mom().m());
          double jet2_ET = sqrt(signalJets35[1]->mom().pT()*signalJets35[1]->mom().pT()+signalJets35[1]->mom().m()*signalJets35[1]->mom().m());

          double modPTdiff_squared=(signalJets35[0]->mom().px()-signalJets35[1]->mom().px())*(signalJets35[0]->mom().px()-signalJets35[1]->mom().px())
            +            (signalJets35[0]->mom().py()-signalJets35[1]->mom().py())*(signalJets35[0]->mom().py()-signalJets35[1]->mom().py());

          double mct_squared = pow(jet1_ET+jet2_ET,2)-modPTdiff_squared;
          mCT = sqrt(mct_squared);

	  if(oneLep){
	    if(nBjets35>1) mblmin = std::min( (signalLeptons[0]->mom() + signalBJets35[0]->mom()).m(), (signalLeptons[0]->mom() + signalBJets35[1]->mom()).m());
	    else if(nBjets35>0) mblmin = (signalLeptons[0]->mom() + signalBJets35[0]->mom()).m();
	  }

	  bjetsLeading = (signalJets35[0]->btag() && signalJets35[1]->btag());
	}


	double mt = 0.;
	if(oneLep)mt =  sqrt(2.*signalLeptons[0]->pT()*met*(1. - cos(signalLeptons[0]->mom().deltaPhi(metVec))));

	// Calculate minimum mT with any of the leading four jets and the met

	double mtmin = 9999.;

	for(unsigned int jet=0;jet<signalJets35.size();jet++){
	  double mt_tmp = sqrt(2.*signalJets35[jet]->pT()*met*(1. - cos(signalJets35[jet]->mom().deltaPhi(metVec))));
	  if(mt_tmp<mtmin && jet<=3)mtmin=mt_tmp;
	}

	double mtminb = 9999.;

	for(unsigned int jet=0;jet<signalBJets35.size();jet++){
	  double mt_tmp = sqrt(2.*signalBJets35[jet]->pT()*met*(1. - cos(signalBJets35[jet]->mom().deltaPhi(metVec))));
	  if(mt_tmp<mtminb && jet<=1)mtminb=mt_tmp;
	}



	double amt2 = 0; //need to identify the two bjets here
	// double mbb  = 0;

	/*int bj1=-1; int bj2=-1;
	for(unsigned int ij=0; ij < signalJets35.size() ; ij++){
	  if( signalJets35[ij]->btag() ){
	    if(bj1<0){
	      bj1=ij;
	    }else{
	      bj2=ij;
	      break;
	    }
	  }
	  }*/

	// Scrap the ATLAS identification of b jets and simply use the signal b jets instead


	//cout << "nBjets35 " << nBjets35 << " bj2 " << bj2 << endl;

	if(nBjets35==2){
	  // mbb = (signalBJets35[0]->mom() + signalBJets35[1]->mom()).m();
	  int bj1=0;
	  int bj2=1;
	  if(oneLep){
	    float mbl1 = (signalLeptons[0]->mom()+signalBJets35[bj1]->mom()).m();
	    float mbl2 = (signalLeptons[0]->mom()+signalBJets35[bj2]->mom()).m();

	    if(mbl1 >= 170. && mbl2 < 170.) {
	      // The ATLAS code snippet looks obviously wrong here (doesn't match the paper)
	      // Have corrected it
	      // Question: Is the first entry correct?
	      double pa_a[3] = { (signalLeptons[0]->mom()+signalBJets35[bj2]->mom()).m(), (signalLeptons[0]->mom()+signalBJets35[bj2]->mom()).px(), (signalLeptons[0]->mom()+signalJets35[bj2]->mom()).py() };
	      double pb_a[3] = { signalJets35[bj1]->mom().m(), signalJets35[bj1]->mom().px(), signalJets35[bj1]->mom().py() };
	      double pmiss_a[3] = { 0, metVec.px(), metVec.py() };
	      double mn_a = 0.;

	      mt2_bisect::mt2 mt2_event_a;

	      mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
	      mt2_event_a.set_mn(mn_a);

	      // double amt2 = mt2_event_a.get_mt2();

	      // Now try new Lester method

	      // double amt2_new = asymm_mt2_lester_bisect::get_mT2((signalLeptons[0]->mom()+signalJets35[bj2]->mom()).m(), (signalLeptons[0]->mom()+signalJets35[bj2]->mom()).px(), (signalLeptons[0]->mom()+signalJets35[bj2]->mom()).py(), signalJets35[bj1]->mom().m(), signalJets35[bj1]->mom().px(), signalJets35[bj1]->mom().py(), metVec.px(), metVec.py(), 0., 0.);

	      //cout << "MT2 original " << amt2 << " amt2_new " << amt2_new << endl;

	      //amt2 = calcMT2(signalLeptons[0]+myjets[bj1], myjets[bj1], metVec);

	    }
	    else if(mbl1 < 170. && mbl2 >= 170.) {

	      double pa_a[3] = { (signalLeptons[0]->mom()+signalJets35[bj1]->mom()).m(), (signalLeptons[0]->mom()+signalJets35[bj1]->mom()).px(), (signalLeptons[0]->mom()+signalJets35[bj1]->mom()).py() };
	      double pb_a[3] = {signalJets35[bj2]->mom().m() , signalJets35[bj2]->mom().px(), signalJets35[bj2]->mom().py() };
	      double pmiss_a[3] = { 0, metVec.px(), metVec.py() };
	      double mn_a = 0.;

	      mt2_bisect::mt2 mt2_event_a;

	      mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
	      mt2_event_a.set_mn(mn_a);

	      // double amt2 = mt2_event_a.get_mt2();

	    }
	    //amt2 = calcMT2(myjets[bj1], signalLeptons[0]+myjets[bj1], metVec);
	    else if(mbl1 < 170. && mbl2 < 170.){

	      double pa_a[3] = {(signalLeptons[0]->mom()+signalJets35[bj1]->mom()).m() , (signalLeptons[0]->mom()+signalJets35[bj1]->mom()).px(), (signalLeptons[0]->mom()+signalJets35[bj1]->mom()).py() };
	      double pb_a[3] = {signalJets35[bj2]->mom().m() , signalJets35[bj2]->mom().px(), signalJets35[bj2]->mom().py() };
	      double pa_b[3] = {(signalLeptons[0]->mom()+signalJets35[bj2]->mom()).m() , (signalLeptons[0]->mom()+signalJets35[bj2]->mom()).px(), (signalLeptons[0]->mom()+signalJets35[bj2]->mom()).py() };
	      double pb_b[3] = {signalJets35[bj1]->mom().m() , signalJets35[bj1]->mom().px(), signalJets35[bj1]->mom().py() };
	      double pmiss_a[3] = { 0, metVec.px(), metVec.py() };
	      double mn_a = 0.;

	      mt2_bisect::mt2 mt2_event_a;
	      mt2_bisect::mt2 mt2_event_b;
	      mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
	      mt2_event_a.set_mn(mn_a);

	      mt2_event_b.set_momenta(pa_b,pb_b,pmiss_a);
	      mt2_event_b.set_mn(mn_a);

	      double amt2_a = mt2_event_a.get_mt2();
	      double amt2_b = mt2_event_b.get_mt2();
	      amt2 = std::min(amt2_a, amt2_b);
	    }
	  }
	}



	// Define variables using 20 GeV jets

	double ht4=0;
	double meff4j = met;
	for(size_t jet=0;jet<signalJets20.size();jet++){
	  if(jet<3)continue;
	  ht4 += signalJets20[jet]->pT();
	  meff4j += signalJets20[jet]->pT();
	}

	bool bjetsSublead = (nJets20>=3 && !signalJets20[0]->btag() && signalJets20[1]->btag() &&
			     (!signalJets20[2]->btag() || (nJets20>=4 && signalJets20[3]->btag())));


	double  dphiMin1  = 0;
	if(nJets20>0)dphiMin1 = fabs(signalJets20[0]->mom().deltaPhi(metVec));

	double dphiMin2 = 9999.;
	for(int jet=0;jet < nJets20;jet++){
	  if(jet>1)continue;
	  double dphi_tmp = fabs(signalJets20[jet]->mom().deltaPhi(metVec));
	  if(dphi_tmp < dphiMin2)dphiMin2=dphi_tmp;
	}

	double mjj_20 = 0.;
	double asym = 0.;
	if(nJets20 > 1){
	  mjj_20 = (signalJets20[0]->mom() + signalJets20[1]->mom()).m();
	  asym = (signalJets20[0]->pT()-signalJets20[1]->pT()) / (signalJets20[0]->pT()+signalJets20[1]->pT());
	}

	double mbb_35 = 0.;
	if(nBjets35>=2)mbb_35=(signalBJets35[0]->mom()+signalBJets35[1]->mom()).m();

        // Increment cutFlowVector elements
        cutFlowVector_str[0]  = "No cuts ";
        cutFlowVector_str[1]  = "b0L-SRA: MET > 250 GeV";
	cutFlowVector_str[2]  = "b0L-SRA: dPhiMin4 > 0.4";
        cutFlowVector_str[3]  = "b0L-SRA: MET/meff > 0.25 ";
        cutFlowVector_str[4]  = "b0L-SRA: 2-4 jets (pT > 25 GeV)";
        cutFlowVector_str[5]  = "b0L-SRA: pT j0 > 130 GeV";
        cutFlowVector_str[6]  = "b0L-SRA: pT j1 > 50 GeV";
        cutFlowVector_str[7]  = "b0L-SRA: pT j3 < 50 GeV";
        cutFlowVector_str[8]  = "b0L-SRA: 0 leptons";
	cutFlowVector_str[9]  = "b0L-SRA: 2 b jets ";
        cutFlowVector_str[10] = "b0L-SRA: 2 leading b jets ";
        cutFlowVector_str[11] = "b0L-SRA: mbb > 200 GeV ";
        cutFlowVector_str[12] = "b0L-SRA: mCT > 350 GeV ";
        cutFlowVector_str[13] = "b0L-SRA: mCT > 450 GeV ";
        cutFlowVector_str[14] = "b0L-SRA: mCT > 550 GeV ";

        cutFlowVector_str[15] = "b0L-SRB: pT j1 > 50 GeV ";
        cutFlowVector_str[16] = "b0L-SRB: 0 leptons ";
        cutFlowVector_str[17] = "b0L-SRB: 2 bjets ";
        cutFlowVector_str[18] = "b0L-SRB: dphi(b1,met) < 2.0 ";
        cutFlowVector_str[19] = "b0L-SRB: dphi(b2,met) < 2.5 ";
        cutFlowVector_str[20] = "b0L-SRB: mTmin(j1-4,met)>250 GeV ";
        cutFlowVector_str[21] = "b0L-SRC: Zero leptons ";
        cutFlowVector_str[22] = "b0L-SRC: 2-5 jets (pT > 20 GeV) ";
        cutFlowVector_str[23] = "b0L-SRC: Leading light jet ";
        cutFlowVector_str[24] = "b0-SRC: dPhi(j1,met) > 2.5";
        cutFlowVector_str[25] = "b0L-SRC: dPhi(j2,met) > 0.2";
        cutFlowVector_str[26] = "b0L-SRC: Subleading jet b-tagged ";
        cutFlowVector_str[27] = "b0L-SRC: 2 b jets ";
        cutFlowVector_str[28] = "b0L-SRC: HT4 < 70 ";
        cutFlowVector_str[29] = "b0L-SRC: met > 500 GeV ";
        cutFlowVector_str[30] = "b0L-SRC: pT(j1) > 500 GeV ";
        cutFlowVector_str[31] = "b0L-SRC: meff > 1300 GeV ";
        cutFlowVector_str[32] = "b0L-SRC: A > 0.8 ";
	cutFlowVector_str[33] = "b0L-SRC: mjj > 200 GeV ";
        cutFlowVector_str[34] = "b1L-SRA: 1 lepton ";
        cutFlowVector_str[35] = "b1L-SRA: pT(l1) > 27 GeV ";
        cutFlowVector_str[36] = "b1L-SRA: >= 2 jets (pT > 35 GeV) ";
	cutFlowVector_str[37] = "b1L-SRA: dphi j min > 0.4 ";
        cutFlowVector_str[38] = "b1L-SRA: 2 b jets ";
        cutFlowVector_str[39] = "b1L-SRA: met > 200 GeV ";
        cutFlowVector_str[40] = "b1L-SRA: met/sqrt(HT) ";
        cutFlowVector_str[41] = "b1L-SRA: mT > 140 GeV ";
	cutFlowVector_str[42] = "b1L-SRA: mblmin < 170 GeV ";
        cutFlowVector_str[43] = "b1L-SRA: amT2 > 250 GeV ";
        cutFlowVector_str[44] = "b1L-SRA: mbb > 200 GeV ";
        cutFlowVector_str[45] = "b1L-SRA: meff > 450 GeV ";
        cutFlowVector_str[46] = "b1L-SRA: meff > 600 GeV ";
        cutFlowVector_str[47] = "b1L-SRA: meff > 750 GeV ";
        cutFlowVector_str[48] = "b1L-SRA300-2j: met/sqrt(HT) ";
        cutFlowVector_str[49] = "b1L-SRA300-2j: mT  > 140 GeV ";
        cutFlowVector_str[50] = "b1L-SRA300-2j: mblmin < 170 GeV ";
        cutFlowVector_str[51] = "b1L-SRA300-2j: amt2 > 250 GeV ";
        cutFlowVector_str[52] = "b1L-SRA300-2j: mbb > 200 GeV ";
        cutFlowVector_str[53] = "b1L-SRA300-2j: meff > 300 GeV ";
        cutFlowVector_str[54] = "b1L-SRA300-2j: < 3 jets (pT > 35 GeV) ";
	cutFlowVector_str[55] = "b1L-SRB: mT > 120 GeV ";
	cutFlowVector_str[56] = "b1L-SRB: mblmin < 170 GeV ";
	cutFlowVector_str[57] = "b1L-SRB: amt2 > 200 GeV ";
	cutFlowVector_str[58] = "b1L-SRB: mbb < 200 GeV ";
	cutFlowVector_str[59] = "b1L-SRB: dphi(b1,met) > 2.0 ";
	cutFlowVector_str[60] = "b1L-SRB: mTmin(b1-2,met) > 200 GeV ";

        // Apply cuts to each signal region

	for(int j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             (j==1 && met > 250.) ||

	     (j==2 && met > 250. && dphiMin4 > 0.4) ||

	     (j==3 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25) ||

	     (j==4 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4) ||

	     (j==5 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130.) ||

	     (j==6 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50.) ||

	     (j==7 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.)) ||

	     (j==8 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.) && zeroLep) ||

	     (j==9 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.) && zeroLep && nBjets35==2) ||

	     (j==10 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.) && zeroLep && nBjets35==2 && bjetsLeading) ||

	     (j==11 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.) && zeroLep && nBjets35==2 && bjetsLeading && mjj_35 > 200.) ||

	     (j==12 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.) && zeroLep && nBjets35==2 && bjetsLeading && mjj_35 > 200. && mCT > 350.) ||

	     (j==13 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.) && zeroLep && nBjets35==2 && bjetsLeading && mjj_35 > 200. && mCT > 450.) ||

	     (j==14 && met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.) && zeroLep && nBjets35==2 && bjetsLeading && mjj_35 > 200. && mCT > 550.) ||

	     // b0L-SRB

	     (j==15 && met > 250. && dphiMin4 > 0.4 && nJets35>=2 && nJets35<=4 && signalJets35[1]->pT() > 50.) ||

	     (j==16 && met > 250. && dphiMin4 > 0.4 && nJets35>=2 && nJets35<=4 && signalJets35[1]->pT() > 50. && zeroLep) ||

	     (j==17 && met > 250. && dphiMin4 > 0.4 && nJets35>=2 && nJets35<=4 && signalJets35[1]->pT() > 50. && zeroLep && nBjets35==2) ||

	     (j==18 && met > 250. && dphiMin4 > 0.4 && nJets35>=2 && nJets35<=4 && signalJets35[1]->pT() > 50. && zeroLep && nBjets35==2 && dphib1 < 2.0) ||

	     (j==19 && met > 250. && dphiMin4 > 0.4 && nJets35>=2 && nJets35<=4 && signalJets35[1]->pT() > 50. && zeroLep && nBjets35==2 && dphib1 < 2.0 && dphib2 < 2.5) ||

	     (j==20 && met > 250. && dphiMin4 > 0.4 && nJets35>=2 && nJets35<=4 && signalJets35[1]->pT() > 50. && zeroLep && nBjets35==2 && dphib1 < 2.0 && dphib2 < 2.5 && mtmin > 250.) ||

	     // b0L-SRC

	     (j==21 && zeroLep) ||

	     (j==22 && zeroLep && nJets20>=2 && nJets20<=5) ||

	     (j==23 && zeroLep && nJets20>=2 && nJets20<=5 && !signalJets20[0]->btag()) ||

	     (j==24 && zeroLep && nJets20>=2 && nJets20<=5 && !signalJets20[0]->btag() && dphiMin1 > 2.5) ||

	     (j==25 && zeroLep && nJets20>=2 && nJets20<=5 && !signalJets20[0]->btag() && dphiMin1 > 2.5 && dphiMin2 > 0.2) ||

	     (j==26 && zeroLep && nJets20>=2 && nJets20<=5 && bjetsSublead && dphiMin1 > 2.5 && dphiMin2 > 0.2) ||

	     (j==27 && zeroLep && nJets20>=2 && nJets20<=5 && bjetsSublead && dphiMin1 > 2.5 && dphiMin2 > 0.2 && nBjets20==2) ||

	     (j==28 && zeroLep && nJets20>=2 && nJets20<=5 && bjetsSublead && dphiMin1 > 2.5 && dphiMin2 > 0.2 && nBjets20==2 && ht4 < 70.) ||

	     (j==29 && zeroLep && nJets20>=2 && nJets20<=5 && bjetsSublead && dphiMin1 > 2.5 && dphiMin2 > 0.2 && nBjets20==2 && ht4 < 70. && met > 500.) ||

	     (j==30 && zeroLep && nJets20>=2 && nJets20<=5 && bjetsSublead && dphiMin1 > 2.5 && dphiMin2 > 0.2 && nBjets20==2 && ht4 < 70. && met > 500. && signalJets20[0]->pT() > 500.) ||

	     (j==31 && zeroLep && nJets20>=2 && nJets20<=5 && bjetsSublead && dphiMin1 > 2.5 && dphiMin2 > 0.2 && nBjets20==2 && ht4 < 70. && met > 500. && signalJets20[0]->pT() > 500. && meff4j > 1300.) ||

	     (j==32 && zeroLep && nJets20>=2 && nJets20<=5 && bjetsSublead && dphiMin1 > 2.5 && dphiMin2 > 0.2 && nBjets20==2 && ht4 < 70. && met > 500. && signalJets20[0]->pT() > 500. && meff4j > 1300. && asym > 0.8) ||

	     (j==33 && zeroLep && nJets20>=2 && nJets20<=5 && bjetsSublead && dphiMin1 > 2.5 && dphiMin2 > 0.2 && nBjets20==2 && ht4 < 70. && met > 500. && signalJets20[0]->pT() > 500. && meff4j > 1300. && asym > 0.8 && mjj_20 > 200.) ||

	     // b1L-SRA

	     (j==34 && oneLep) ||

	     (j==35 && oneLep && signalLeptons[0]->pT() > 27.) ||

	     (j==36 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2) ||

	     (j==37 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4) ||

	     (j==38 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2) ||

	     (j==39 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200.) ||

	     (j==40 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8) ||

	     (j==41 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140.) ||

	     (j==42 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170) ||

	     (j==43 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170 && amt2 > 250) ||

	     (j==44 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170 && amt2 > 250 && mbb_35 > 200.) ||

	     (j==45 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170 && amt2 > 250 && mbb_35 > 200. && meff > 450.) ||

	     (j==46 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170 && amt2 > 250 && mbb_35 > 200. && meff > 600.) ||

	     (j==47 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170 && amt2 > 250 && mbb_35 > 200. && meff > 750.) ||

	     // b1L-SRA300-2j

	     (j==48 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8) ||

	     (j==49 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140.) ||

	     (j==50 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170.) ||

	     (j==51 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170. && amt2 > 250.) ||

	     (j==52 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170. && amt2 > 250. && mbb_35 > 200.) ||
	     (j==53 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170. && amt2 > 250. && mbb_35 > 200. && meff>300.) ||

	     (j==54 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170. && amt2 > 250. && mbb_35 > 200. && meff>300. && nJets35==2) ||

	     // b1L-SRB

	     (j==55 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 120.) ||

	     (j==56 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 120. && mblmin < 170.) ||

	     (j==57 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 120. && mblmin < 170. && amt2 > 200.) ||

	     (j==58 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 120. && mblmin < 170. && amt2 > 200. && mbb_35 < 200.) ||
	     (j==59 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 120. && mblmin < 170. && amt2 > 200. && mbb_35 < 200. && fabs(signalBJets35[0]->mom().deltaPhi(metVec)) > 2.0) ||

	     (j==60 && oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 120. && mblmin < 170. && amt2 > 200. && mbb_35 < 200. && fabs(signalBJets35[0]->mom().deltaPhi(metVec)) > 2.0 && mtminb > 200.)

	     )cutFlowVector[j]++;
	}


	// Now increment signal region variables

	if(met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.) && zeroLep && nBjets35==2 && bjetsLeading && mjj_35 > 200. && mCT > 550.)_numb0L_SRA550++;

	if(met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.) && zeroLep && nBjets35==2 && bjetsLeading && mjj_35 > 200. && mCT > 450.)_numb0L_SRA450++;

	if(met > 250. && dphiMin4 > 0.4 && met/meff2j>0.25 && nJets35>=2 && nJets35<=4 &&  signalJets35[0]->pT() > 130. && signalJets35[1]->pT() > 50. && (nJets35<4 || signalJets35[3]->pT() < 50.) && zeroLep && nBjets35==2 && bjetsLeading && mjj_35 > 200. && mCT > 350.)_numb0L_SRA350++;

	if(met > 250. && dphiMin4 > 0.4 && nJets35>=2 && nJets35<=4 && signalJets35[1]->pT() > 50. && zeroLep && nBjets35==2 && dphib1 < 2.0 && dphib2 < 2.5 && mtmin > 250.)_numb0L_SRB++;

	if(zeroLep && nJets20>=2 && nJets20<=5 && bjetsSublead && dphiMin1 > 2.5 && dphiMin2 > 0.2 && nBjets20==2 && ht4 < 70. && met > 500. && signalJets20[0]->pT() > 500. && meff4j > 1300. && asym > 0.8 && mjj_20 > 200.)_numb0L_SRC++;

	if(oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170 && amt2 > 250 && mbb_35 > 200. && meff > 600.)_numb1L_SRA600++;

	if(oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170 && amt2 > 250 && mbb_35 > 200. && meff > 750.)_numb1L_SRA750++;

	if(oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 140. && mblmin < 170. && amt2 > 250. && mbb_35 > 200. && meff>300. && nJets35==2)_numb1L_SRA300_2j++;

	if(oneLep && signalLeptons[0]->pT() > 27. &&  nJets35>=2 && dphiMin4 > 0.4 && nBjets35==2 && met > 200. && met/sqrt(ht) > 8 && mt > 120. && mblmin < 170. && amt2 > 200. && mbb_35 < 200. && fabs(signalBJets35[0]->mom().deltaPhi(metVec)) > 2.0 && mtminb > 200.)_numb1L_SRB++;

        return;

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_2bMET_36invfb* specificOther
          = dynamic_cast<const Analysis_ATLAS_13TeV_2bMET_36invfb*>(other);

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (int j=0; j<NCUTS; j++)
        {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }

        _numb0L_SRA350    += specificOther->_numb0L_SRA350;
        _numb0L_SRA450    += specificOther->_numb0L_SRA450;
        _numb0L_SRA550    += specificOther->_numb0L_SRA550;
        _numb0L_SRB       += specificOther->_numb0L_SRB;
        _numb0L_SRC       += specificOther->_numb0L_SRC;

        _numb1L_SRA600    += specificOther->_numb1L_SRA600;
        _numb1L_SRA750    += specificOther->_numb1L_SRA750;
        _numb1L_SRA300_2j += specificOther->_numb1L_SRA300_2j;
        _numb1L_SRB       += specificOther->_numb1L_SRB;

      }


      void collect_results() {

        // double scale_by=1.;

        // cout << "-------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        // cout << "CUT FLOW: ATLAS multi lepton paper "<<endl;
        // cout << "-------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

        // cout << left << setw(45) << "CUT" << right << setw(20) << "RAW" << setw(20) << "SCALED" << setw(20) << "%" << setw(20) << "clean adj RAW"<< setw(20) << "clean adj %" << std::endl;
        // for (int j=0; j<NCUTS; j++) {
        //   cout << left << setw(45) << right << cutFlowVector_str[j].c_str() << setw(20) << cutFlowVector[j] << setw(20) << cutFlowVector[j]*scale_by << setw(20) << 100.*cutFlowVector[j]/cutFlowVector[0] << "%" << setw(20) << cutFlowVector[j]*scale_by << setw(20) << 100.*cutFlowVector[j]/cutFlowVector[0]<< "%" << std::endl;
        // }
        // cout << "-------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;




        SignalRegionData results_b0L_SRA350;
        results_b0L_SRA350.sr_label = "b0L-SRA350";    // label must be unique for each signal region
        results_b0L_SRA350.n_observed = 81.;           // set number of observed events (in LHC paper)
        results_b0L_SRA350.n_background = 70.;         // set number of predicted background events (in LHC paper)
        results_b0L_SRA350.background_sys = 13.;       // set background uncertainty (in LHC paper)
        results_b0L_SRA350.signal_sys = 0.;            // set signal uncertainty
        results_b0L_SRA350.n_signal = _numb0L_SRA350;  // set this to number of signal events incremented in the analysis above
        add_result(results_b0L_SRA350);

        SignalRegionData results_b0L_SRA450;
        results_b0L_SRA450.sr_label = "b0L-SRA450";
        results_b0L_SRA450.n_observed = 24.;
        results_b0L_SRA450.n_background = 22.;
        results_b0L_SRA450.background_sys = 5.;
        results_b0L_SRA450.signal_sys = 0.;
        results_b0L_SRA450.n_signal = _numb0L_SRA450;
        add_result(results_b0L_SRA450);

        SignalRegionData results_b0L_SRA550;
        results_b0L_SRA550.sr_label = "b0L-SRA550";
        results_b0L_SRA550.n_observed = 10.;
        results_b0L_SRA550.n_background = 7.2;
        results_b0L_SRA550.background_sys = 1.5;
        results_b0L_SRA550.signal_sys = 0.;
        results_b0L_SRA550.n_signal = _numb0L_SRA550;
        add_result(results_b0L_SRA550);

        SignalRegionData results_b0L_SRB;
        results_b0L_SRB.sr_label = "b0L-SRB";
        results_b0L_SRB.n_observed = 45.;
        results_b0L_SRB.n_background = 37.;
        results_b0L_SRB.background_sys = 7.;
        results_b0L_SRB.signal_sys = 0.;
        results_b0L_SRB.n_signal = _numb0L_SRB;
        add_result(results_b0L_SRB);

        SignalRegionData results_b0L_SRC;
        results_b0L_SRC.sr_label = "b0L-SRC";
        results_b0L_SRC.n_observed = 7.;
        results_b0L_SRC.n_background = 5.5;
        results_b0L_SRC.background_sys = 1.5;
        results_b0L_SRC.signal_sys = 0.;
        results_b0L_SRC.n_signal = _numb0L_SRC;
        add_result(results_b0L_SRC);

	// MJW removes these regions for the Feb 2018 MareNostrum scans, since the aMT2 variable is not well-described.

        /*SignalRegionData results_b1L_SRA600;
        results_b1L_SRA600.sr_label = "b1L-SRA600";
        results_b1L_SRA600.n_observed = 21.;
        results_b1L_SRA600.n_background = 24.;
        results_b1L_SRA600.background_sys = 6.;
        results_b1L_SRA600.signal_sys = 0.;
        results_b1L_SRA600.n_signal = _numb1L_SRA600;
        add_result(results_b1L_SRA600);

        SignalRegionData results_b1L_SR750;
        results_b1L_SR750.sr_label = "b1L-SR750";
        results_b1L_SR750.n_observed = 13.;
        results_b1L_SR750.n_background = 15.;
        results_b1L_SR750.background_sys = 4.;
        results_b1L_SR750.signal_sys = 0.;
        results_b1L_SR750.n_signal = _numb1L_SRA750;
        add_result(results_b1L_SR750);

        SignalRegionData results_b1L_SR300_2j;
        results_b1L_SR300_2j.sr_label = "b1L-SR300-2j";
        results_b1L_SR300_2j.n_observed = 12.;
        results_b1L_SR300_2j.n_background = 6.7;
        results_b1L_SR300_2j.background_sys = 2.3;
        results_b1L_SR300_2j.signal_sys = 0.;
        results_b1L_SR300_2j.n_signal = _numb1L_SRA300_2j;
        add_result(results_b1L_SR300_2j);

        SignalRegionData results_b1L_SRB;
        results_b1L_SRB.sr_label = "b1L-SRB";
        results_b1L_SRB.n_observed = 69.;
        results_b1L_SRB.n_background = 53.;
        results_b1L_SRB.background_sys = 12.;
        results_b1L_SRB.signal_sys = 0.;
        results_b1L_SRB.n_signal = _numb1L_SRB;
        add_result(results_b1L_SRB);*/

        return;
      }

      void analysis_specific_reset() {

	_numb0L_SRA350=0; _numb0L_SRA450=0; _numb0L_SRA550=0;
        _numb0L_SRB=0; _numb0L_SRC=0;

        _numb1L_SRA600=0; _numb1L_SRA750=0; _numb1L_SRA300_2j=0; _numb1L_SRB=0;

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }



    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2bMET_36invfb)

  }
}
