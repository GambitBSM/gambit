#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <sstream>

#include "gambit/ColliderBit/analyses/BaseAnalysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

/* A simulation of CMS paper PAS SUS-13-006

   Code by Martin White & Daniel Murnane

   Known features:
   a) Must run with a dedicated detector card due to odd b tagging and isolation

*/

namespace Gambit {
  namespace ColliderBit {

    using namespace std;

    class Analysis_CMS_8TeV_3LEPEW_20invfb : public HEPUtilsAnalysis {
    private:

      // Array of signal regions, set to zero
      static const size_t NUMSR = 180;
      int SR [NUMSR];
      //int Region45=0;
      //int Region46=0;
      vector<double> boundsMll = {0.,75.,105.,9999.};
      vector<double> boundsMt = {0.,120.,160.,9999.};
      vector<double> boundsmet ={0.,50.,100.,150.,200.,9999.};
      vector<double> boundsMll2 = {0.,100.,9999.};
      // Debug histos

    public:

      Analysis_CMS_8TeV_3LEPEW_20invfb() {

        set_analysis_name("CMS_8TeV_3LEPEW_20invfb");
        set_luminosity(19.5);

        for(size_t i=0;i<NUMSR;i++){
          SR[i]=0;
        }

      }

      void JetLeptonOverlapRemoval(vector<HEPUtils::Jet*> &jetvec, vector<HEPUtils::Particle*> &lepvec, double DeltaRMax) {
        //Routine to do jet-lepton check
        //Discards jets if they are within DeltaRMax of a lepton

        vector<HEPUtils::Jet*> Survivors;

        for(unsigned int itjet = 0; itjet < jetvec.size(); itjet++) {
          bool overlap = false;
          HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
          for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
            HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
            float dR;

            dR=jetmom.deltaR_eta(lepmom);

            if(dR <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(jetvec.at(itjet));
        }
        jetvec=Survivors;

        return;
      }

      void LeptonJetOverlapRemoval(vector<HEPUtils::Particle*> &lepvec, vector<HEPUtils::Jet*> &jetvec, double DeltaRMax) {
        //Routine to do lepton-jet check
        //Discards leptons if they are within DeltaRMax of a jet

        vector<HEPUtils::Particle*> Survivors;

        for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
          bool overlap = false;
          HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
          for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            float dR;

            dR=jetmom.deltaR_eta(lepmom);

            if(dR <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lepvec.at(itlep));
        }
        lepvec=Survivors;

        return;
      }

      double TransMass(double eMissing, double ePhi, HEPUtils::Particle* thirdLepton ) {
        //Calculate transverse mass

        double mT = sqrt(2*eMissing*(thirdLepton->pT())*(1. - cos(thirdLepton->phi() - ePhi)));
        return mT;
      }

      void analyze(const HEPUtils::Event* event) {
        HEPUtilsAnalysis::analyze(event);

        // Missing energy
        HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();
        double missingPhi = ptot.phi();

        // Now define vectors of baseline objects
        vector<HEPUtils::Particle*> signalElectrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && fabs(electron->eta()) < 2.4) signalElectrons.push_back(electron);
        }
        vector<HEPUtils::Particle*> signalMuons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && fabs(muon->eta()) < 2.4) signalMuons.push_back(muon);
        }
        vector<HEPUtils::Particle*> signalTaus;
        for (HEPUtils::Particle* tau : event->taus()) {
          if (tau->pT() > 20. && fabs(tau->eta()) < 2.4) signalTaus.push_back(tau);
        }
        CMS::applyTauEfficiency(signalTaus);

        vector<HEPUtils::Jet*> signalJets;
        vector<HEPUtils::Jet*> bJets;

        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 30. && fabs(jet->eta()) < 2.5) signalJets.push_back(jet);
          if(jet->btag() && fabs(jet->eta()) < 2.5 && jet->pT() > 30.) bJets.push_back(jet);
        }

        //Overlap Removal

        //Note that ATLAS use |eta|<10 for removing jets close to electrons
        //Then 2.8 is used for the rest of the overlap process
        //Then the signal cut is applied for signal jets

        JetLeptonOverlapRemoval(signalJets,signalElectrons,0.4);
        JetLeptonOverlapRemoval(signalJets,signalMuons,0.4);

        // int numElectrons = signalElectrons.size();
        // int numMuons = signalMuons.size();
        int numTaus = signalTaus.size();

        vector<HEPUtils::Particle*> signalLeptons;

        for (HEPUtils::Particle* ele : signalElectrons) {
          signalLeptons.push_back(ele);
        }

        for (HEPUtils::Particle* muo : signalMuons) {
          signalLeptons.push_back(muo);
        }

        int numLeptons = signalLeptons.size(); //Only electrons and muons

        //Find transverse mass and invariant mass depending on presence of tau, OSSF/OSOF/SS

        double mLL = 0;
        double mT = 0;
        vector<bool> flavourSign = {false,false,false,false};

        //No taus present
        if(numLeptons==3){
          double smallestDiff1=9999;
          double smallestDiff2=9999;

          //cout << "Lep 1: " << signalLeptons.at(0)->pid() << ", Lep 2: " << signalLeptons.at(1)->pid() << ", Lep 3: " << signalLeptons.at(2)->pid() << endl;

          for(int lep1=0;lep1<numLeptons;lep1++){
            for(int lep2=0;lep2<numLeptons;lep2++){
              //Search for the OSSF pair closest to Z, and use the remaining lepton for transverse mass
              if(signalLeptons.at(lep1)->pid()==-1*signalLeptons.at(lep2)->pid()){
                flavourSign.at(0) = true;
                flavourSign.at(1) = false;
                HEPUtils::P4 lepVec1=signalLeptons.at(lep1)->mom();
                HEPUtils::P4 lepVec2=signalLeptons.at(lep2)->mom();
                double invMass1=(lepVec1+lepVec2).m();
                if(fabs(invMass1-91.2)<smallestDiff1){
                  smallestDiff1=fabs(invMass1-91.2);
                  mLL=invMass1;
                  mT=TransMass(met,missingPhi,signalLeptons.at(3-lep1-lep2));
                }
              }
              //Search for the OSOF pair closest to Z->tau tau dilepton, use remaining lepton for transverse mass
              else if((signalLeptons.at(lep1)->pid() * signalLeptons.at(lep2)->pid()) < 0 && !flavourSign.at(0)){
                flavourSign.at(1) = true;
                HEPUtils::P4 lepVec1=signalLeptons.at(lep1)->mom();
                HEPUtils::P4 lepVec2=signalLeptons.at(lep2)->mom();
                double invMass2=(lepVec1+lepVec2).m();
                if(fabs(invMass2-50)<smallestDiff2){
                  smallestDiff2=fabs(invMass2-50);
                  mLL=invMass2;
                  mT=TransMass(met,missingPhi,signalLeptons.at(3-lep1-lep2));
                }
              }
            }
          }
        }

        //One tau present
        else if(numTaus==1 && numLeptons==2){
          //With SS pair
          if(signalLeptons.at(0)->pid() * signalLeptons.at(1)->pid() > 0){
            flavourSign.at(2) = true;
            HEPUtils::P4 lepVec1=signalLeptons.at(0)->mom();
            HEPUtils::P4 lepVec2=signalLeptons.at(1)->mom();
            HEPUtils::P4 tauVec =signalTaus.at(0)->mom();
            double invMass1 = (lepVec1+tauVec).m();
            double invMass2 = (lepVec2+tauVec).m();
            if(fabs(invMass1 - 60)<fabs(invMass2 - 60)){
              mLL=invMass1;
              mT=TransMass(met,missingPhi,signalLeptons.at(1));
            }
            else {
              mLL=invMass2;
              mT=TransMass(met,missingPhi,signalLeptons.at(0));
            }
          }
          //With OSOF pair
          else if(signalLeptons.at(0)->pid()!= -1*signalLeptons.at(1)->pid()){
            flavourSign.at(3) = true;
            if(signalLeptons.at(0)->pid() * signalTaus.at(0)->pid() < 0){
              HEPUtils::P4 lepVec=signalLeptons.at(0)->mom();
              HEPUtils::P4 tauVec=signalTaus.at(0)->mom();
              mLL=(lepVec+tauVec).m();
              mT=TransMass(met,missingPhi,signalLeptons.at(1));
            }
            else {
              HEPUtils::P4 lepVec=signalLeptons.at(1)->mom();
              HEPUtils::P4 tauVec=signalTaus.at(0)->mom();
              mLL=(lepVec+tauVec).m();
              mT=TransMass(met,missingPhi,signalLeptons.at(0));
            }
          }
        }

        //Cuts to lepton energy

        bool signalAccepted=false;

        for(HEPUtils::Particle * lepton : signalLeptons){
          if(lepton->pT()>20)signalAccepted=true;
        }

        for(int i=0;i<numLeptons;i++){
          for(int j=0;j<numLeptons;j++){
            HEPUtils::P4 lepVec1=signalLeptons.at(i)->mom();
            HEPUtils::P4 lepVec2=signalLeptons.at(j)->mom();
            double invMass = (lepVec1+lepVec2).m();
            if(invMass<12 && (signalLeptons.at(i)->pid()*signalLeptons.at(j)->pid() < 0)){
              signalAccepted=false;
            }
          }
        }
        if(bJets.size() > 0){
          signalAccepted=false;
        }
        //
        //Fill signal vector
        if(signalAccepted){

          int m=0;
          int i=0;
          for(unsigned int j=0;j<(boundsMll.size()-1);j++){
            for(unsigned int k=0;k<(boundsMt.size()-1);k++){
              for(unsigned int l=0;l<(boundsmet.size()-1);l++){
                //cout << "FLAVSIGN " << flavourSign.at(i) << endl;
                if(flavourSign.at(i) && mLL>=boundsMll.at(j) && mLL<boundsMll.at(j+1) && mT>=boundsMt.at(k) && mT<boundsMt.at(k+1) && met>=boundsmet.at(l) && met<boundsmet.at(l+1)){
                  SR[m]++;
                }
                //cout << m << " ";
                //std::cout << "REGION " << m << " Mll bounds " << boundsMll[j]<< " to " << boundsMll[j+1] << " MT bound " << boundsMt[k] << " to " << boundsMt[k+1] << " MET bound " << boundsmet[l] << " to " << boundsmet[l+1] << std::endl;
                m++;
              }
            }
          }

          for(unsigned int i=1;i<(flavourSign.size());i++){
            for(unsigned int j=0;j<(boundsMll2.size()-1);j++){
              for(unsigned int k=0;k<(boundsMt.size()-1);k++){
                for(unsigned int l=0;l<(boundsmet.size()-1);l++){
                  if(flavourSign.at(i) && mLL>=boundsMll2.at(j) && mLL<boundsMll2.at(j+1) && mT>=boundsMt.at(k) && mT<boundsMt.at(k+1) && met>=boundsmet.at(l) && met<boundsmet.at(l+1)){
                    SR[m]++;
                  }

                  //std::cout << "REGION " << m << " Mll bounds " << boundsMll2[j]<< " to " << boundsMll2[j+1] << " MT bound " << boundsMt[k] << " to " << boundsMt[k+1] << " MET bound " << boundsmet[l] << " to " << boundsmet[l+1] << std::endl;
                  m++;
                }
              }
              if(j==0){
                m=m+15;
              }
            }
          }
        }

        /*Region 45 test
          double testMLL=9999;
          double testMT=9999;
          bool reg45 = false;
          if(numLeptons==3){
          double smallestDiff=9999;
          double testmass=0;
          if((signalLeptons.at(0)->pid()>0 && signalLeptons.at(1)->pid()<0 || signalLeptons.at(0)->pid()<0 && signalLeptons.at(1)->pid()>0) && signalLeptons.at(0)->pid()!=-1*signalLeptons.at(1)->pid()){
          HEPUtils::P4 testlep1=signalLeptons.at(0)->mom();
          HEPUtils::P4 testlep2=signalLeptons.at(1)->mom();
          testMLL = (testlep1+testlep2).m();
          smallestDiff = fabs(testMLL-50);
          testMT=TransMass(met,missingPhi,signalLeptons.at(2));
          reg45=true;
          }

          if((signalLeptons.at(0)->pid()>0 && signalLeptons.at(2)->pid()<0 || signalLeptons.at(0)->pid()<0 && signalLeptons.at(2)->pid()>0) && signalLeptons.at(0)->pid()!=-1*signalLeptons.at(2)->pid()){
          HEPUtils::P4 testlep1=signalLeptons.at(0)->mom();
          HEPUtils::P4 testlep2=signalLeptons.at(2)->mom();
          testmass = (testlep1+testlep2).m();
          if(fabs(testmass-50)<smallestDiff){
          testMLL=testmass;
          testMT=TransMass(met,missingPhi,signalLeptons.at(1));
          smallestDiff=testmass-50;
          reg45=true;
          }
          }

          if((signalLeptons.at(1)->pid()>0 && signalLeptons.at(2)->pid()<0 || signalLeptons.at(1)->pid()<0 && signalLeptons.at(2)->pid()>0) && signalLeptons.at(1)->pid()!=-1*signalLeptons.at(2)->pid()){
          HEPUtils::P4 testlep1=signalLeptons.at(1)->mom();
          HEPUtils::P4 testlep2=signalLeptons.at(2)->mom();
          testmass = (testlep1+testlep2).m();
          if(fabs(testmass-50)<smallestDiff){
          testMLL=testmass;
          testMT=TransMass(met,missingPhi,signalLeptons.at(0));
          reg45=true;
          }
          }
          if(signalLeptons.at(1)->pid()==-1*signalLeptons.at(2)->pid())reg45=false;
          if(signalLeptons.at(0)->pid()==-1*signalLeptons.at(1)->pid())reg45=false;
          if(signalLeptons.at(0)->pid()==-1*signalLeptons.at(2)->pid())reg45=false;

          if(reg45 && testMLL<75 && testMT<120 && met<50){
          Region45++;
          }
          }
        */

        return;
      }

      void add(BaseAnalysis* other) {
        // TODO: Need to combine the signal region results here
        // The base class add function handles the signal region vector and total # events.
        HEPUtilsAnalysis::add(other);

        Analysis_CMS_8TeV_3LEPEW_20invfb* specificOther
          = dynamic_cast<Analysis_CMS_8TeV_3LEPEW_20invfb*>(other);

        // Here we will add the subclass member variables:
        for(size_t i=0;i<NUMSR;i++) {
          SR[i] += specificOther->SR[i];
        }
      }


      void collect_results() {

        std::ostringstream *convert;
        // TODO: Need to add all of the signal region results here

        //First do the 3l with OSSF pair results (no tau)
        //Table 1 in the paper

        //MT > 160
        //REGION 11 Mll bounds 0.000e+00 to 7.500e+01 MT bound 1.600e+02 to 9.999e+03 MET bound 5.000e+01 to 1.000e+02
        //REGION 12 Mll bounds 0.000e+00 to 7.500e+01 MT bound 1.600e+02 to 9.999e+03 MET bound 1.000e+02 to 1.500e+02
        //REGION 13 Mll bounds 0.000e+00 to 7.500e+01 MT bound 1.600e+02 to 9.999e+03 MET bound 1.500e+02 to 2.000e+02
        //REGION 14 Mll bounds 0.000e+00 to 7.500e+01 MT bound 1.600e+02 to 9.999e+03 MET bound 2.000e+02 to 9.999e+03
        //REGION 26 Mll bounds 7.500e+01 to 1.050e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 5.000e+01 to 1.000e+02
        //REGION 27 Mll bounds 7.500e+01 to 1.050e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 1.000e+02 to 1.500e+02
        //REGION 28 Mll bounds 7.500e+01 to 1.050e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 1.500e+02 to 2.000e+02
        //REGION 29 Mll bounds 7.500e+01 to 1.050e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 2.000e+02 to 9.999e+03
        //REGION 41 Mll bounds 1.050e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 5.000e+01 to 1.000e+02
        //REGION 42 Mll bounds 1.050e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 1.000e+02 to 1.500e+02
        //REGION 43 Mll bounds 1.050e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 1.500e+02 to 2.000e+02
        //REGION 44 Mll bounds 1.050e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 2.000e+02 to 9.999e+03

        int regions_highmt [12] = {11,12,13,14,26,27,28,29,41,42,43,44};
        float observed_highmt [12] = {12,3,2,0,13,8,3,2,1,3,0,0};
        float background_highmt [12] = {5.8, 4.5, 1.5, 0.81, 7.5, 4.0, 1.5, 1.1, 2.6, 1.8, 0.7, 0.4};
        float err_highmt [12] = {1.1, 1.1, 0.4, 0.21, 1.4, 1.0, 0.5, 0.4, 1.2, 0.9, 0.4, 0.24};

        for(int region=0; region<12;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_highmt[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_highmt[region];
          results_tmp.n_background = background_highmt[region];
          results_tmp.background_sys = err_highmt[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_highmt[region]];
          add_result(results_tmp);

        }

        //MT 120 - 160
        //REGION 6 Mll bounds 0.000e+00 to 7.500e+01 MT bound 1.200e+02 to 1.600e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 7 Mll bounds 0.000e+00 to 7.500e+01 MT bound 1.200e+02 to 1.600e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 8 Mll bounds 0.000e+00 to 7.500e+01 MT bound 1.200e+02 to 1.600e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 9 Mll bounds 0.000e+00 to 7.500e+01 MT bound 1.200e+02 to 1.600e+02 MET bound 2.000e+02 to 9.999e+03
        //REGION 21 Mll bounds 7.500e+01 to 1.050e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 22 Mll bounds 7.500e+01 to 1.050e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 23 Mll bounds 7.500e+01 to 1.050e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 24 Mll bounds 7.500e+01 to 1.050e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 2.000e+02 to 9.999e+03
        //REGION 36 Mll bounds 1.050e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 37 Mll bounds 1.050e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 38 Mll bounds 1.050e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 39 Mll bounds 1.050e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 2.000e+02 to 9.999e+03

        int regions_medmt [12] = {6,7,8,9,21,22,23,24,36,37,38,39};
        float observed_medmt [12] = {8,2,0,0,29,4,1,1,4,2,0,0};
        float background_medmt [12] = {9.6, 3.3, 0.26, 0.29, 23, 3.4, 0.72, 0.36, 2.7, 0.71, 0.38, 0.24};
        float err_medmt [12] = {1.7, 0.8, 0.10, 0.11, 5, 0.7, 0.19, 0.12, 0.5, 0.22, 0.14, 0.20};

        for(int region=0; region<12;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_medmt[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_medmt[region];
          results_tmp.n_background = background_medmt[region];
          results_tmp.background_sys = err_medmt[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_medmt[region]];
          add_result(results_tmp);
        }

        //MT < 120
        //REGION 1 Mll bounds 0.000e+00 to 7.500e+01 MT bound 0.000e+00 to 1.200e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 2 Mll bounds 0.000e+00 to 7.500e+01 MT bound 0.000e+00 to 1.200e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 3 Mll bounds 0.000e+00 to 7.500e+01 MT bound 0.000e+00 to 1.200e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 4 Mll bounds 0.000e+00 to 7.500e+01 MT bound 0.000e+00 to 1.200e+02 MET bound 2.000e+02 to 9.999e+03
        //REGION 16 Mll bounds 7.500e+01 to 1.050e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 17 Mll bounds 7.500e+01 to 1.050e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 18 Mll bounds 7.500e+01 to 1.050e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 19 Mll bounds 7.500e+01 to 1.050e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 2.000e+02 to 9.999e+03
        //REGION 31 Mll bounds 1.050e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 32 Mll bounds 1.050e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 33 Mll bounds 1.050e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 34 Mll bounds 1.050e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 2.000e+02 to 9.999e+03

        int regions_lowmt [12] = {1,2,3,4,16,17,18,19,31,32,33,34};
        float observed_lowmt [12] = {138,16,5,2,821,123,34,14,49,10,4,4};
        float background_lowmt [12] = {132, 20, 4.0, 1.9, 776, 131, 34, 21, 45, 10.0, 2.5, 1.2};
        float err_lowmt [12] = {19, 4, 0.8, 0.4, 125, 30, 8, 7, 7, 1.9, 0.5, 0.3};

        for(int region=0; region<12;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_lowmt[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_lowmt[region];
          results_tmp.n_background = background_lowmt[region];
          results_tmp.background_sys = err_lowmt[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_lowmt[region]];
          add_result(results_tmp);
        }


        //Now do OSOF (no tau) results
        //OSOF (no tau) MT > 160
        //REGION 56 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 5.000e+01 to 1.000e+02
        //REGION 57 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 1.000e+02 to 1.500e+02
        //REGION 58 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 1.500e+02 to 2.000e+02
        //REGION 59 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 2.000e+02 to 9.999e+03
        //REGION 86 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 5.000e+01 to 1.000e+02
        //REGION 87 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 1.000e+02 to 1.500e+02
        //REGION 88 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 1.500e+02 to 2.000e+02
        //REGION 89 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 2.000e+02 to 9.999e+03

        int regions_highmt_osof [8] = {56,57,58,59,86,87,88,89};
        float observed_highmt_osof [8] = {2,3,0,1,0,0,0,0};
        float background_highmt_osof [8] = {3.2, 2.1, 0.59, 0.37, 0.44, 0.42, 0.10, 0.16};
        float err_highmt_osof [8] = {0.8, 0.7, 0.18, 0.13, 0.33, 0.19, 0.06, 0.14};

        for(int region=0; region<8;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_highmt_osof[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_highmt_osof[region];
          results_tmp.n_background = background_highmt_osof[region];
          results_tmp.background_sys = err_highmt_osof[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_highmt_osof[region]];
          add_result(results_tmp);
        }

        //OSOF (no tau) MT 120 - 160
        //REGION 51 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 52 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 53 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 54 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 2.000e+02 to 9.999e+03
        //REGION 81 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 82 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 83 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 84 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 2.000e+02 to 9.999e+03

        int regions_medmt_osof [8] = {51,52,53,54,81,82,83,84};
        float observed_medmt_osof [8] = {3,1,1,0,1,0,0,0};
        float background_medmt_osof [8] = {5.5, 1.9, 0.46, 0.10, 0.25, 0.19, 0.03, 0.008};
        float err_medmt_osof [8] = {1.2, 0.5, 0.18, 0.05, 0.07, 0.10, 0.03, 0.01};

        for(int region=0; region<8;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_medmt_osof[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_medmt_osof[region];
          results_tmp.n_background = background_medmt_osof[region];
          results_tmp.background_sys = err_medmt_osof[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_medmt_osof[region]];
          add_result(results_tmp);
        }

        //OSOF (no tau) MT < 120
        //REGION 46 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 47 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 48 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 49 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 2.000e+02 to 9.999e+03
        //REGION 76 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 77 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 78 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 79 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 2.000e+02 to 9.999e+03

        int regions_lowmt_osof [8] = {46,47,48,49,76,77,78,79};
        float observed_lowmt_osof [8] = {29, 5, 1, 0, 1, 0, 0, 0};
        float background_lowmt_osof [8] = {32, 7.3, 1.0, 0.53, 1.7, 0.30, 0.14, 0.03};
        float err_lowmt_osof [8] = {7, 1.7, 0.3, 0.24, 0.4, 0.11, 0.09, 0.03};

        for(int region=0; region<8;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_lowmt_osof[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_lowmt_osof[region];
          results_tmp.n_background = background_lowmt_osof[region];
          results_tmp.background_sys = err_lowmt_osof[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_lowmt_osof[region]];
          add_result(results_tmp);
        }

        //Now do the SS + 1 tau results
        // SS 1 tau MT > 160
        //REGION 101 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 5.000e+01 to 1.000e+02
        //REGION 102 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 1.000e+02 to 1.500e+02
        //REGION 103 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 1.500e+02 to 2.000e+02
        //REGION 104 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 2.000e+02 to 9.999e+03
        //REGION 131 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 5.000e+01 to 1.000e+02
        //REGION 132 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 1.000e+02 to 1.500e+02
        //REGION 133 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 1.500e+02 to 2.000e+02
        //REGION 134 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 2.000e+02 to 9.999e+03

        int regions_highmt_ss1tau [8] = {101,102,103,104,131,132,133,134};
        float observed_highmt_ss1tau [8] = {2,1,0,2,1,1,0,0};
        float background_highmt_ss1tau [8] = {3.1, 2.3, 0.5, 0.4, 0.5, 0.4, 0.2, 0.06};
        float err_highmt_ss1tau [8] = {0.6, 0.5, 0.2, 0.1, 0.2, 0.2, 0.1, 0.05};

        for(int region=0; region<8;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_highmt_ss1tau[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_highmt_ss1tau[region];
          results_tmp.n_background = background_highmt_ss1tau[region];
          results_tmp.background_sys = err_highmt_ss1tau[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_highmt_ss1tau[region]];
          add_result(results_tmp);
        }

        // SS 1 tau MT 120 - 160
        //REGION 96 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 97 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 98 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 99 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 2.000e+02 to 9.999e+03
        //REGION 126 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 127 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 128 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 129 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 2.000e+02 to 9.999e+03

        int regions_medmt_ss1tau [8] = {96,97,98,99,126,127,128,129};
        float observed_medmt_ss1tau [8] = {6,2,0,0,1,0,0,0};
        float background_medmt_ss1tau [8] = {6, 0.9, 0.3, 0.06, 0.4, 0.06, 0.0, 0.01};
        float err_medmt_ss1tau [8] = {1, 0.3, 0.1, 0.08, 0.1, 0.05, 0.01, 0.01};

        for(int region=0; region<8;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_medmt_ss1tau[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_medmt_ss1tau[region];
          results_tmp.n_background = background_medmt_ss1tau[region];
          results_tmp.background_sys = err_medmt_ss1tau[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_medmt_ss1tau[region]];
          add_result(results_tmp);
        }


        // SS 1 tau MT < 120
        //REGION 91 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 92 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 93 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 94 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 2.000e+02 to 9.999e+03
        //REGION 121 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 122 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 123 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 124 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 2.000e+02 to 9.999e+03

        int regions_lowmt_ss1tau [8] = {91,92,93,94,121,122,123,124};
        float observed_lowmt_ss1tau [8] = {46,1,0,0,3,0,0,0};
        float background_lowmt_ss1tau [8] = {51, 6, 2.0, 0.9, 2.8, 0.5, 0.11, 0.04};
        float err_lowmt_ss1tau [8] = {8, 1, 0.4, 0.2, 0.6, 0.1, 0.07, 0.02};

        for(int region=0; region<8;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_lowmt_ss1tau[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_lowmt_ss1tau[region];
          results_tmp.n_background = background_lowmt_ss1tau[region];
          results_tmp.background_sys = err_lowmt_ss1tau[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_lowmt_ss1tau[region]];
          add_result(results_tmp);
        }


        //Now do 1 tau, OSOF pair
        //1 tau OSOF pair, MT > 160
        //REGION 146 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 5.000e+01 to 1.000e+02
        //REGION 147 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 1.000e+02 to 1.500e+02
        //REGION 148 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 1.500e+02 to 2.000e+02
        //REGION 149 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.600e+02 to 9.999e+03 MET bound 2.000e+02 to 9.999e+03
        //REGION 176 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 5.000e+01 to 1.000e+02
        //REGION 177 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 1.000e+02 to 1.500e+02
        //REGION 178 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 1.500e+02 to 2.000e+02
        //REGION 179 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.600e+02 to 9.999e+03 MET bound 2.000e+02 to 9.999e+03

        int regions_highmt_osof1tau [8] = {146,147,148,149,176,177,178,179};
        float observed_highmt_osof1tau [8] = {19,14,1,2,2,3,3,1};
        float background_highmt_osof1tau [8] = {15, 14, 3.7, 1.5, 5.7, 4.0, 1.3, 0.7};
        float err_highmt_osof1tau [8] = {8, 9, 2.1, 1.0, 2.3, 2.2, 1.0, 0.4};

        for(int region=0; region<8;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_highmt_osof1tau[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_highmt_osof1tau[region];
          results_tmp.n_background = background_highmt_osof1tau[region];
          results_tmp.background_sys = err_highmt_osof1tau[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_highmt_osof1tau[region]];
          add_result(results_tmp);
        }

        //1 tau OSOF pair, MT > 120 - 160
        //REGION 141 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 142 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 143 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 144 Mll bounds 0.000e+00 to 1.000e+02 MT bound 1.200e+02 to 1.600e+02 MET bound 2.000e+02 to 9.999e+03
        //REGION 171 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 172 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 173 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 174 Mll bounds 1.000e+02 to 9.999e+03 MT bound 1.200e+02 to 1.600e+02 MET bound 2.000e+02 to 9.999e+03

        int regions_medmt_osof1tau [8] = {141,142,143,144,171,172,173,174};
        float observed_medmt_osof1tau [8] = {41,18,2,1,7,4,0,0};
        float background_medmt_osof1tau [8] = {42, 17, 2.0, 0.8, 8.3, 2.3, 0.27, 0.5};
        float err_medmt_osof1tau [8] = {16, 9, 1.2, 0.5, 2.9, 1.3, 0.32, 0.4};

        for(int region=0; region<8;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_medmt_osof1tau[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_medmt_osof1tau[region];
          results_tmp.n_background = background_medmt_osof1tau[region];
          results_tmp.background_sys = err_medmt_osof1tau[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_medmt_osof1tau[region]];
          add_result(results_tmp);
        }


        //1 tau OSOF pair, MT < 120
        //REGION 136 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 137 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 138 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 139 Mll bounds 0.000e+00 to 1.000e+02 MT bound 0.000e+00 to 1.200e+02 MET bound 2.000e+02 to 9.999e+03
        //REGION 166 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 5.000e+01 to 1.000e+02
        //REGION 167 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 1.000e+02 to 1.500e+02
        //REGION 168 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 1.500e+02 to 2.000e+02
        //REGION 169 Mll bounds 1.000e+02 to 9.999e+03 MT bound 0.000e+00 to 1.200e+02 MET bound 2.000e+02 to 9.999e+03

        int regions_lowmt_osof1tau [8] = {136,137,138,139,166,167,168,169};
        float observed_lowmt_osof1tau [8] = {290,62,10,2,27,8,0,0};
        float background_lowmt_osof1tau [8] = {259,60,11,2.9, 30, 5.9, 2.3, 1.1};
        float err_lowmt_osof1tau [8] = {93, 25, 5, 1.4, 13, 2.6, 1.4, 0.6};

        for(int region=0; region<8;region++){
          SignalRegionData results_tmp;
          convert = new std::ostringstream();

          (*convert) << regions_lowmt_osof1tau[region];
          results_tmp.sr_label = convert->str();
          delete convert;
          results_tmp.n_observed = observed_lowmt_osof1tau[region];
          results_tmp.n_background = background_lowmt_osof1tau[region];
          results_tmp.background_sys = err_lowmt_osof1tau[region];
          results_tmp.signal_sys = 0.;
          results_tmp.n_signal = SR[regions_lowmt_osof1tau[region]];
          add_result(results_tmp);
        }

      }


    protected:
      void clear() {
        for(size_t i=0;i<NUMSR;i++) { SR[i]=0; }
      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_8TeV_3LEPEW_20invfb)


  }
}
