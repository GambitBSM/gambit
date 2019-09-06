///
///  \author Yang Zhang
///  \date 2018 Nov
///
///  *********************************************

// Based on http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-17-010/index.html
// Searches for pair production of charginos and top squarks in final states with two oppositely charged leptons in proton-proton collisions at √s= 13 TeV

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    // This analysis class is a base class for two SR-specific analysis classes
    // defined further down:
    // - Analysis_CMS_13TeV_2OSLEP_chargino_36invfb
    // - Analysis_CMS_13TeV_2OSLEP_stop_36invfb
    class Analysis_CMS_13TeV_2OSLEP_chargino_stop_36invfb : public Analysis {


    protected:
      // Counters for the number of accepted events for each signal region
      static const size_t NUMSR_stop = 84;
      double _srnums_stop[NUMSR_stop];
      static const size_t NUMSR_chargino = 70;
      double _srnums_chargino[NUMSR_chargino];

      Cutflow _cutflow;

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_13TeV_2OSLEP_chargino_stop_36invfb():
      _cutflow("CMS 2-lep stop 13 TeV", {"Two_OC_leptons", "Third_lepton_veto", "mll_20", "mll_mZ_15", "PTmiss_140"})
      {
        set_analysis_name("Analysis_CMS_13TeV_2OSLEP_chargino_stop_36invfb");
        set_luminosity(35.9);
        for (size_t i = 0; i < NUMSR_stop; ++i) _srnums_stop[i] = 0;
        for (size_t i = 0; i < NUMSR_chargino; ++i) _srnums_chargino[i] = 0;
      }

      struct ptComparison {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      void run(const HEPUtils::Event* event)
      {
        // Baseline objects
        HEPUtils::P4 ptot = event->missingmom();
        double met = event->met();
        _cutflow.fillinit();

        // Apply electron efficiency and collect baseline electrons
        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_el_17010_ttbar.pdf
        //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aEl={0., 0.8, 1.442, 1.556, 2., 2.4, DBL_MAX};   // Bin edges in eta
        const vector<double> bEl={0., 10., 20., 25., 30., 40., 50., DBL_MAX}; // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cEl={
                          // pT: (0,10),  (10,20),  (20,25),  (25,30),  (30,40),  (40,50),  (50,inf)
                                    0.0,    0.95,    0.463,     0.537,    0.597,   0.648,    0.701,  // eta: (0, 0.8)
                                    0.0,    0.95,    0.424,     0.520,    0.603,   0.635,    0.700, // eta: (0.8, 1.4429
                                    0.0,    0.95,    0.041,     0.044,    0.053,   0.049,    0.053, // eta: (1.442, 1.556)
                                    0.0,    0.85,    0.271,     0.343,    0.439,   0.508,    0.557, // eta: (1.556, 2)
                                    0.0,    0.85,    0.262,     0.336,    0.411,   0.463,    0.513, // eta: (2, 2.5)
                                    0.0,    0.0,     0.0,       0.0,      0.0,     0.0,      0.0,   // eta > 2.5
                                  };
        HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons())
        {
          bool isEl=has_tag(_eff2dEl, electron->eta(), electron->pT());
          if (isEl && electron->pT()>15. && fabs(electron->eta())<2.4) baselineElectrons.push_back(electron);
        }


        // Apply muon efficiency and collect baseline muons
        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_mu_17010_ttbar.pdf
        //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aMu={0., 0.9, 1.2, 2.1, 2.4, DBL_MAX};   // Bin edges in eta
        const vector<double> bMu={0., 10., 20., 25., 30., 40., 50., DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cMu={
                           // pT:   (0,10),  (10,20),  (20,25),  (25,30),  (30,40),  (40,50),  (50,inf)
                                     0.0,    0.950,    0.692,    0.759,    0.813,    0.852,    0.896,  // eta: (0, 0.9)
                                     0.0,    0.950,    0.679,    0.752,    0.803,    0.856,    0.897,  // eta: (0.9, 1.2)
                                     0.0,    0.950,    0.706,    0.757,    0.801,    0.836,    0.886,  // eta: (1.2, 2.1)
                                     0.0,    0.950,    0.647,    0.711,    0.753,    0.800,    0.806,  // eta: (2.1, 2.4)
                                     0.0,    0.0,      0.0,      0.0,      0.0,      0.0,      0.0,    // eta > 2.4
                                 };
        HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons())
        {
          bool isMu=has_tag(_eff2dMu, muon->eta(), muon->pT());
          if (isMu && muon->pT()>15. && fabs(muon->eta())<2.4) baselineMuons.push_back(muon);
        }

        // Baseline jets
        vector<HEPUtils::Jet*> baselineJets;
        for (HEPUtils::Jet* jet : event->jets())
        {
          if (jet->pT()>20. &&fabs(jet->eta())<2.4) baselineJets.push_back(jet);
        }


        // Signal leptons = electrons + muons
        vector<HEPUtils::Particle*> signalLeptons;
        signalLeptons=baselineElectrons;
        signalLeptons.insert(signalLeptons.end(),baselineMuons.begin(),baselineMuons.end());
        sort(signalLeptons.begin(),signalLeptons.end(),comparePt);

        // Signal jets
        const vector<double> aBJet={0,10.};
        const vector<double> bBJet={0,30., 40., 50., 70., 80., 90., 100.,150., 200., 10000.};
        const vector<double> cBJet={0.63, 0.705, 0.745, 0.76, 0.775, 0.79,0.795, 0.805, 0.795, 0.76};
        HEPUtils::BinnedFn2D<double> _eff2d(aBJet,bBJet,cBJet);
        vector<HEPUtils::Jet*> signalJets,signalBJets;
        bool ISR_btag=false;
        for (size_t iJet=0;iJet<baselineJets.size();iJet++) {
          bool hasTag=has_tag(_eff2d, baselineJets.at(iJet)->eta(), baselineJets.at(iJet)->pT());
          bool ovelap=false;
          for (size_t iEl=0;iEl<signalLeptons.size();iEl++) {
            if (signalLeptons.at(iEl)->mom().deltaR_eta(baselineJets.at(iJet)->mom())<0.4) ovelap=true;
          }
          if ( not ovelap ){
            signalJets.push_back(baselineJets.at(iJet));
            if (baselineJets.at(iJet)->btag() and  hasTag){
                if (iJet==0) ISR_btag = true;
                signalBJets.push_back(baselineJets.at(iJet));
            }
          }
        }
        int nj  = signalJets.size();
        int nbj = signalBJets.size();


        // Tow OC lepton
        if (signalLeptons.size()<2) return;
        if (signalLeptons[0]->pid()*signalLeptons[1]->pid()>0) return;
        if (signalLeptons[0]->pT()<25. or signalLeptons[1]->pT()<20.) return;
        _cutflow.fill(1);

        // Third lepton veto
        if (signalLeptons.size()>2) return;
        _cutflow.fill(2);

        // m_{ll} > 20 GeV
        double mll=(signalLeptons[0]->mom()+signalLeptons[1]->mom()).m();
        if (mll<20) return;
        _cutflow.fill(3);

        // |m_{ll}-m_Z| >15 GeV for ee and mumu events
        bool same_flavor = signalLeptons[0]->abspid() == signalLeptons[1]->abspid();
        if (same_flavor and fabs(mll-91.2)<15 ) return;
        _cutflow.fill(4);

        // MET>140 GeV
        if (met<140) return;
        _cutflow.fill(5);

        // Mt2
        double pLep1[3] = {signalLeptons[0]->mass(), signalLeptons[0]->mom().px(), signalLeptons[0]->mom().py()};
        double pLep2[3] = {signalLeptons[1]->mass(), signalLeptons[1]->mom().px(), signalLeptons[1]->mom().py()};
        double pMiss[3] = {0., event->missingmom().px(), event->missingmom().py() };
        mt2_bisect::mt2 mt2_calc;
        mt2_calc.set_momenta(pLep1,pLep2,pMiss);
        mt2_calc.set_mn(0.0);
        double mT2 = mt2_calc.get_mt2();

        // ISR jet
        int nISR=0;
        if (nj>1){
            if ( signalJets.at(0)->pT()>150. and ptot.deltaPhi(signalJets.at(0)->mom())>2.5 and (not ISR_btag)){
                nISR = 1;
            }
        }

        // For chargino SRs
        // In the order of x axis
        // http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-17-010/CMS-SUS-17-010_Figure-aux_001.png
        if ( not same_flavor ) {
            if (met<200) {
                if (nbj==0 and nj ==0) { //SR1_{0tag}^{0jet}
                    if      (mT2< 20) ++_srnums_chargino[ 0];
                    else if (mT2< 40) ++_srnums_chargino[ 1];
                    else if (mT2< 60) ++_srnums_chargino[ 2];
                    else if (mT2< 80) ++_srnums_chargino[ 3];
                    else if (mT2<100) ++_srnums_chargino[ 4];
                    else if (mT2<120) ++_srnums_chargino[ 5];
                    else              ++_srnums_chargino[ 6];
                }
                if (nbj==0 and nj >=1) { //SR1_{0tag}^{jets}
                    if      (mT2< 20) ++_srnums_chargino[14];
                    else if (mT2< 40) ++_srnums_chargino[15];
                    else if (mT2< 60) ++_srnums_chargino[16];
                    else if (mT2< 80) ++_srnums_chargino[17];
                    else if (mT2<100) ++_srnums_chargino[18];
                    else if (mT2<120) ++_srnums_chargino[19];
                    else              ++_srnums_chargino[20];
                }
            } else if (met<300){
                if (nbj==0 and nj ==0) { //SR2_{0tag}^{0jet}
                    if      (mT2< 20) ++_srnums_chargino[28];
                    else if (mT2< 40) ++_srnums_chargino[29];
                    else if (mT2< 60) ++_srnums_chargino[30];
                    else if (mT2< 80) ++_srnums_chargino[31];
                    else if (mT2<100) ++_srnums_chargino[32];
                    else if (mT2<120) ++_srnums_chargino[33];
                    else              ++_srnums_chargino[34];
                }
                if (nbj==0 and nj >=1) { //SR2_{0tag}^{jets}
                    if      (mT2< 20) ++_srnums_chargino[42];
                    else if (mT2< 40) ++_srnums_chargino[43];
                    else if (mT2< 60) ++_srnums_chargino[44];
                    else if (mT2< 80) ++_srnums_chargino[45];
                    else if (mT2<100) ++_srnums_chargino[46];
                    else if (mT2<120) ++_srnums_chargino[47];
                    else              ++_srnums_chargino[48];
                }
            } else {
                if (nbj==0 and nj >=0) { //SR3_{0tag}
                    if      (mT2< 20) ++_srnums_chargino[56];
                    else if (mT2< 40) ++_srnums_chargino[57];
                    else if (mT2< 60) ++_srnums_chargino[58];
                    else if (mT2< 80) ++_srnums_chargino[59];
                    else if (mT2<100) ++_srnums_chargino[60];
                    else if (mT2<120) ++_srnums_chargino[61];
                    else              ++_srnums_chargino[62];
                }
            }
        } else {
            if (met<200) {
                if (nbj==0 and nj ==0) { //SR1_{0tag}^{0jet}
                    if      (mT2< 20) ++_srnums_chargino[ 7];
                    else if (mT2< 40) ++_srnums_chargino[ 8];
                    else if (mT2< 60) ++_srnums_chargino[ 9];
                    else if (mT2< 80) ++_srnums_chargino[10];
                    else if (mT2<100) ++_srnums_chargino[11];
                    else if (mT2<120) ++_srnums_chargino[12];
                    else              ++_srnums_chargino[13];
                }
                if (nbj==0 and nj >=1) { //SR1_{0tag}^{jets}
                    if      (mT2< 20) ++_srnums_chargino[21];
                    else if (mT2< 40) ++_srnums_chargino[22];
                    else if (mT2< 60) ++_srnums_chargino[23];
                    else if (mT2< 80) ++_srnums_chargino[24];
                    else if (mT2<100) ++_srnums_chargino[25];
                    else if (mT2<120) ++_srnums_chargino[26];
                    else              ++_srnums_chargino[27];

                }
            } else if (met<300){
                if (nbj==0 and nj ==0) { //SR2_{0tag}^{0jet}
                    if      (mT2< 20) ++_srnums_chargino[35];
                    else if (mT2< 40) ++_srnums_chargino[36];
                    else if (mT2< 60) ++_srnums_chargino[37];
                    else if (mT2< 80) ++_srnums_chargino[38];
                    else if (mT2<100) ++_srnums_chargino[39];
                    else if (mT2<120) ++_srnums_chargino[40];
                    else              ++_srnums_chargino[41];
                }
                if (nbj==0 and nj >=1) { //SR2_{0tag}^{jets}
                    if      (mT2< 20) ++_srnums_chargino[49];
                    else if (mT2< 40) ++_srnums_chargino[50];
                    else if (mT2< 60) ++_srnums_chargino[51];
                    else if (mT2< 80) ++_srnums_chargino[52];
                    else if (mT2<100) ++_srnums_chargino[53];
                    else if (mT2<120) ++_srnums_chargino[54];
                    else              ++_srnums_chargino[55];
                }
            } else {
                if (nbj==0 and nj >=0) { //SR3_{0tag}
                    if      (mT2< 20) ++_srnums_chargino[63];
                    else if (mT2< 40) ++_srnums_chargino[64];
                    else if (mT2< 60) ++_srnums_chargino[65];
                    else if (mT2< 80) ++_srnums_chargino[66];
                    else if (mT2<100) ++_srnums_chargino[67];
                    else if (mT2<120) ++_srnums_chargino[68];
                    else              ++_srnums_chargino[69];
                }
            }
        }

        // For stop SRs
        // In the order of x axis in
        // http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-17-010/CMS-SUS-17-010_Figure-aux_003.png
        if ( not same_flavor ) {
            if (met<200) {
                if (nbj==0) {                       //SR1_{0tag}
                    if      (mT2< 20) ++_srnums_stop[42];
                    else if (mT2< 40) ++_srnums_stop[43];
                    else if (mT2< 60) ++_srnums_stop[44];
                    else if (mT2< 80) ++_srnums_stop[45];
                    else if (mT2<100) ++_srnums_stop[46];
                    else if (mT2<120) ++_srnums_stop[47];
                    else              ++_srnums_stop[48];
                }
                if (nbj>=1 and nj >=1) {            //SR1_{tags}
                    if      (mT2< 20) ++_srnums_stop[ 0];
                    else if (mT2< 40) ++_srnums_stop[ 1];
                    else if (mT2< 60) ++_srnums_stop[ 2];
                    else if (mT2< 80) ++_srnums_stop[ 3];
                    else if (mT2<100) ++_srnums_stop[ 4];
                    else if (mT2<120) ++_srnums_stop[ 5];
                    else              ++_srnums_stop[ 6];
                }
            } else if (met<300){
                if (nbj==0) {                       //SR2_{0tag}
                    if      (mT2< 20) ++_srnums_stop[56];
                    else if (mT2< 40) ++_srnums_stop[57];
                    else if (mT2< 60) ++_srnums_stop[58];
                    else if (mT2< 80) ++_srnums_stop[59];
                    else if (mT2<100) ++_srnums_stop[60];
                    else if (mT2<120) ++_srnums_stop[61];
                    else              ++_srnums_stop[62];
                }
                if (nbj>=1 and nj >=1) {            //SR2_{tags}
                    if      (mT2< 20) ++_srnums_stop[14];
                    else if (mT2< 40) ++_srnums_stop[15];
                    else if (mT2< 60) ++_srnums_stop[16];
                    else if (mT2< 80) ++_srnums_stop[17];
                    else if (mT2<100) ++_srnums_stop[18];
                    else if (mT2<120) ++_srnums_stop[19];
                    else              ++_srnums_stop[20];
                }
            } else {
                if (nbj==0 and nj >=1 and nISR>0) { //SR3_{0tag}
                    if      (mT2< 20) ++_srnums_stop[70];
                    else if (mT2< 40) ++_srnums_stop[71];
                    else if (mT2< 60) ++_srnums_stop[72];
                    else if (mT2< 80) ++_srnums_stop[73];
                    else if (mT2<100) ++_srnums_stop[74];
                    else if (mT2<120) ++_srnums_stop[75];
                    else              ++_srnums_stop[76];
                }
                if (nbj>=1 and nj >=2 and nISR>0) { //SR3_{tags}
                    if      (mT2< 20) ++_srnums_stop[28];
                    else if (mT2< 40) ++_srnums_stop[29];
                    else if (mT2< 60) ++_srnums_stop[30];
                    else if (mT2< 80) ++_srnums_stop[31];
                    else if (mT2<100) ++_srnums_stop[32];
                    else if (mT2<120) ++_srnums_stop[33];
                    else              ++_srnums_stop[34];
                }
            }
        } else {
            if (met<200) {
                if (nbj==0) {                       //SR1_{0tag}
                    if      (mT2< 20) ++_srnums_stop[49];
                    else if (mT2< 40) ++_srnums_stop[50];
                    else if (mT2< 60) ++_srnums_stop[51];
                    else if (mT2< 80) ++_srnums_stop[52];
                    else if (mT2<100) ++_srnums_stop[53];
                    else if (mT2<120) ++_srnums_stop[54];
                    else              ++_srnums_stop[55];
                }
                if (nbj>=1 and nj >=1) {            //SR1_{tags}
                    if      (mT2< 20) ++_srnums_stop[ 7];
                    else if (mT2< 40) ++_srnums_stop[ 8];
                    else if (mT2< 60) ++_srnums_stop[ 9];
                    else if (mT2< 80) ++_srnums_stop[10];
                    else if (mT2<100) ++_srnums_stop[11];
                    else if (mT2<120) ++_srnums_stop[12];
                    else              ++_srnums_stop[13];
                }
            } else if (met<300){
                if (nbj==0) {                       //SR2_{0tag}
                    if      (mT2< 20) ++_srnums_stop[63];
                    else if (mT2< 40) ++_srnums_stop[64];
                    else if (mT2< 60) ++_srnums_stop[65];
                    else if (mT2< 80) ++_srnums_stop[66];
                    else if (mT2<100) ++_srnums_stop[67];
                    else if (mT2<120) ++_srnums_stop[68];
                    else              ++_srnums_stop[69];
                }
                if (nbj>=1 and nj >=1) {            //SR2_{tags}
                    if      (mT2< 20) ++_srnums_stop[21];
                    else if (mT2< 40) ++_srnums_stop[22];
                    else if (mT2< 60) ++_srnums_stop[23];
                    else if (mT2< 80) ++_srnums_stop[24];
                    else if (mT2<100) ++_srnums_stop[25];
                    else if (mT2<120) ++_srnums_stop[26];
                    else              ++_srnums_stop[27];
                }
            } else {
                if (nbj==0 and nj >=1 and nISR>0) { //SR3_{0tag}
                    if      (mT2< 20) ++_srnums_stop[77];
                    else if (mT2< 40) ++_srnums_stop[78];
                    else if (mT2< 60) ++_srnums_stop[79];
                    else if (mT2< 80) ++_srnums_stop[80];
                    else if (mT2<100) ++_srnums_stop[81];
                    else if (mT2<120) ++_srnums_stop[82];
                    else              ++_srnums_stop[83];
                }
                if (nbj>=1 and nj >=2 and nISR>0) { //SR3_{tags}
                    if      (mT2< 20) ++_srnums_stop[35];
                    else if (mT2< 40) ++_srnums_stop[36];
                    else if (mT2< 60) ++_srnums_stop[37];
                    else if (mT2< 80) ++_srnums_stop[38];
                    else if (mT2<100) ++_srnums_stop[39];
                    else if (mT2<120) ++_srnums_stop[40];
                    else              ++_srnums_stop[41];
                }

            }
        }

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_2OSLEP_chargino_stop_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2OSLEP_chargino_stop_36invfb*>(other);
        for (size_t i = 0; i < NUMSR_stop; ++i)
            _srnums_stop[i] += specificOther->_srnums_stop[i];
        for (size_t i = 0; i < NUMSR_chargino; ++i)
            _srnums_chargino[i] += specificOther->_srnums_chargino[i];
      }


      virtual void collect_results()
      {
        cout << _cutflow << endl;
        cout << "------------- chargino ----------" << endl;
        for (size_t ibin = 0; ibin < NUMSR_chargino; ++ibin) {
            stringstream ss; ss << "sr-" << ibin;
            cout << "sr-" << ibin << "\t" << _srnums_chargino[ibin] << endl;
        }
        cout << "--------------- stop ------------" << endl;
        for (size_t ibin = 0; ibin < NUMSR_stop; ++ibin) {
            stringstream ss; ss << "sr-" << ibin;
            cout << "sr-" << ibin << "\t" << _srnums_stop[ibin] << endl;
        }

        static const size_t SR_size_cov_chargino = 70;

        // Observed event counts
        static const double OBSNUM_chargino[SR_size_cov_chargino] = {\
            39, 24, 33, 44, 13, 6, 9, \
            43, 40, 39, 33, 17, 6, 12, \
            1484, 532, 732, 725, 298, 47, 13, \
            1324, 499, 609, 659, 284, 57, 47, \
            10, 4, 4, 6, 2, 2, 7, \
            8, 12, 11, 10, 3, 2, 7, \
            511, 162, 156, 176, 43, 5, 9, \
            493, 123, 166, 118, 33, 7, 25, \
            116, 35, 29, 21, 3, 1, 5, \
            110, 35, 26, 26, 2, 1, 14 \
        };
        // Background estimates
        static const double BKGNUM_chargino[SR_size_cov_chargino] = {\
            41.9, 27.4, 34.1, 42, 21.1, 6, 7.9, \
            44.1, 28.5, 33.5, 33.5, 18.6, 7.7, 12.5, \
            1493, 558, 719, 730, 316, 45.1, 13.7, \
            1310, 499, 623, 634, 271.7, 51.6, 48.6, \
            10.3, 7, 6.5, 6.9, 2.19, 1.59, 7.8, \
            10.9, 7.8, 7.3, 7.9, 1.9, 1.28, 7.1, \
            534, 158.6, 167.9, 157.9, 42.4, 5.9, 9,
            474, 134.8, 155.1, 128.5, 37.1, 7.29, 23.9, \
            127.9, 28.3, 30.2, 23.1, 4.96, 1.12, 4.5, \
            112.8, 27.9, 24.2, 22.5, 5.2, 1.36, 10.6 \
        };
        // Background uncertainties, same-flavor signal regions
        static const double BKGERR_chargino[SR_size_cov_chargino] = {\
            5, 3.8, 4.8, 5.5, 3.4, 1.3, 2.1, \
            7.5, 4.1, 4.4, 4.5, 2.6, 1.6, 2.5,\
            32, 12, 16, 16, 10, 3.1, 2.8, \
            29, 12, 14, 15, 8.9, 3.5, 5.5, \
            1.7, 1.5, 1.3, 1.3, 0.69, 0.7, 1.8, \
            1.9, 1.8, 1.4, 1.3, 0.52, 0.58, 1.4, \
            15, 5.9, 6.1, 6.5, 2.9, 1, 1.7, \
            14, 5.1, 5.5, 5.5, 2.5, 0.91, 2.4,\
            7.2, 2, 2.4, 2, 0.73, 0.38, 1.2, \
            6.3, 2.2, 1.8, 1.8, 1, 0.36, 1.2 \
        };

        for (size_t ibin = 0; ibin < SR_size_cov_chargino; ++ibin) {
          stringstream ss; ss << "sr-chargino-" << ibin;
          add_result(SignalRegionData(ss.str(), OBSNUM_chargino[ibin], {_srnums_chargino[ibin],  0.}, {BKGNUM_chargino[ibin], BKGERR_chargino[ibin]}));
        }


        static const size_t SR_size_cov_stop = 84;

        // Observed event counts
        static const double OBSNUM_stop[SR_size_cov_stop] = {\
            3534, 1494, 1938, 2068, 879, 111, 15, \
            3003, 1266, 1674, 1671, 798, 85, 16, \
            1045, 357, 412, 389, 111, 11, 1, \
            900, 315, 343, 325, 86, 13, 11, \
            133, 44, 36, 26, 2, 1, 0, \
            123, 27, 28, 38, 4, 1, 1, \
            1523, 556, 765, 769, 311, 53, 22, \
            1367, 539, 648, 692, 301, 63, 59, \
            521, 166, 160, 182, 45, 7, 16, \
            501, 135, 177, 128, 36, 9, 32,\
            100, 27, 22, 12, 3, 0, 1, \
            92, 26, 17, 12, 1, 1, 2 \
        };
        // Background estimates
        static const double BKGNUM_stop[SR_size_cov_stop] = {\
            3525, 1505, 1958, 2049, 897, 108.4, 13.4,\
            2979, 1277, 1644, 1712, 762, 91.9, 18.1, \
            1036, 363, 415, 377, 105.1, 12.3, 5.02, \
            888, 319, 363, 323, 90.5, 10.8, 7.43, \
            152.1, 35.5, 32.3, 25, 4.67, 0.41, 0.41, \
            129.6, 29.6, 27.8, 22.2, 3.71, 0.47, 0.71, \
            1542, 588, 756, 771, 338.3, 50.6, 21, \
            1350, 526, 656, 670, 289.2, 57.9, 61.8, \
            545, 164.3, 173.2, 165.1, 44.8, 7.1, 15.5, \
            487, 140.7, 161.9, 134.5, 39.6, 8.1, 30.6, \
            103.9, 21.3, 22.2, 15.4, 3.51, 0.53, 0.53,\
            91.5, 20.1, 16.5, 13.7, 3.14, 0.78, 1.63 \
        };
        // Background uncertainties, same-flavor signal regions
        static const double BKGERR_stop[SR_size_cov_stop] = {\
            80, 31, 42, 46, 22, 7.3, 2.2, \
            68, 30, 35, 37, 19, 6.1, 2.1, \
            37, 13, 14, 14, 6.5, 2, 0.82, \
            30, 12, 14, 13, 5.5, 1.5, 0.98,\
            9.9, 2.7, 2.3, 2.2, 0.77, 0.38, 0.26, \
            8.9, 2.1, 2.1, 1.9, 0.57, 0.42, 0.38, \
            33, 13, 15, 19, 9.3, 3.8, 3.8, \
            33, 13, 15, 17, 7.6, 4.2, 5.8, \
            18, 7.3, 6.2, 6.8, 3.1, 1.4, 3, \
            16, 5.5, 5.9, 6.2, 2.7, 1.1, 3,\
            6.8, 1.9, 2.1, 1.6, 0.6, 0.21, 0.34, \
            6.1, 1.8, 1.4, 1.4, 0.58, 0.36, 0.42\
        };

        for (size_t ibin = 0; ibin < SR_size_cov_stop; ++ibin) {
          stringstream ss; ss << "sr-stop-" << ibin;
          add_result(SignalRegionData(ss.str(), OBSNUM_stop[ibin], {_srnums_stop[ibin],  0.}, {BKGNUM_stop[ibin], BKGERR_stop[ibin]}));
        }

      }

    protected:
      void analysis_specific_reset() {

        for(size_t i=0;i<NUMSR_stop;i++) { _srnums_stop[i]=0; }
        for(size_t i=0;i<NUMSR_chargino;i++) { _srnums_chargino[i]=0; }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2OSLEP_chargino_stop_36invfb)



    //
    // Derived analysis class for the chargino SRs
    //
    class Analysis_CMS_13TeV_2OSLEP_for_chargino_36invfb : public Analysis_CMS_13TeV_2OSLEP_chargino_stop_36invfb {

    public:
      Analysis_CMS_13TeV_2OSLEP_for_chargino_36invfb() {
        set_analysis_name("CMS_13TeV_2OSLEP_for_chargino_36invfb");
      }

      virtual void collect_results() {
        static const size_t SR_size_cov = 70;

        // Observed event counts
        static const double OBSNUM[SR_size_cov] = {\
            39, 24, 33, 44, 13, 6, 9, \
            43, 40, 39, 33, 17, 6, 12, \
            1484, 532, 732, 725, 298, 47, 13, \
            1324, 499, 609, 659, 284, 57, 47, \
            10, 4, 4, 6, 2, 2, 7, \
            8, 12, 11, 10, 3, 2, 7, \
            511, 162, 156, 176, 43, 5, 9, \
            493, 123, 166, 118, 33, 7, 25, \
            116, 35, 29, 21, 3, 1, 5, \
            110, 35, 26, 26, 2, 1, 14 \
        };
        // Background estimates
        static const double BKGNUM[SR_size_cov] = {\
            41.9, 27.4, 34.1, 42, 21.1, 6, 7.9, \
            44.1, 28.5, 33.5, 33.5, 18.6, 7.7, 12.5, \
            1493, 558, 719, 730, 316, 45.1, 13.7, \
            1310, 499, 623, 634, 271.7, 51.6, 48.6, \
            10.3, 7, 6.5, 6.9, 2.19, 1.59, 7.8, \
            10.9, 7.8, 7.3, 7.9, 1.9, 1.28, 7.1, \
            534, 158.6, 167.9, 157.9, 42.4, 5.9, 9,
            474, 134.8, 155.1, 128.5, 37.1, 7.29, 23.9, \
            127.9, 28.3, 30.2, 23.1, 4.96, 1.12, 4.5, \
            112.8, 27.9, 24.2, 22.5, 5.2, 1.36, 10.6 \
        };
        // Background uncertainties, same-flavor signal regions
        static const double BKGERR[SR_size_cov] = {\
            5, 3.8, 4.8, 5.5, 3.4, 1.3, 2.1, \
            7.5, 4.1, 4.4, 4.5, 2.6, 1.6, 2.5,\
            32, 12, 16, 16, 10, 3.1, 2.8, \
            29, 12, 14, 15, 8.9, 3.5, 5.5, \
            1.7, 1.5, 1.3, 1.3, 0.69, 0.7, 1.8, \
            1.9, 1.8, 1.4, 1.3, 0.52, 0.58, 1.4, \
            15, 5.9, 6.1, 6.5, 2.9, 1, 1.7, \
            14, 5.1, 5.5, 5.5, 2.5, 0.91, 2.4,\
            7.2, 2, 2.4, 2, 0.73, 0.38, 1.2, \
            6.3, 2.2, 1.8, 1.8, 1, 0.36, 1.2 \
        };

        for (size_t ibin = 0; ibin < SR_size_cov; ++ibin) {
          stringstream ss; ss << "sr-" << ibin;
          add_result(SignalRegionData(ss.str(), OBSNUM[ibin], {_srnums_chargino[ibin],  0.}, {BKGNUM[ibin], BKGERR[ibin]}));
        }

        // Covariance matrix
        static const vector< vector<double> > BKGCOV = {
          {25.598, 13.424, 16.352, 21.763, 10.454, 3.1358, 5.0395, 20.224, 11.944, 15.636, 15.766, 9.1389, 3.6114, 4.94, 2.6272, 3.154, 7.2268, 0.1247, -2.9303, 2.6016, 5.1647, 8.0038, 6.9048, 4.96, 4.2144, -4.5489, 0.15967, -3.3981, -0.50065, -1.0013, -1.2021, -0.74028, -0.55454, -0.37688, 0.81781, 0.23105, -0.76926, -0.8439, 0.87561, -0.27353, -0.1891, 0.53007, 3.1935, 4.2566, 4.7622, 4.4467, 1.1547, 0.86073, 1.1328, 3.145, 4.6289, 3.0738, 3.9791, -0.35038, 0.08308, -0.59277, 2.9314, 0.85789, 0.95815, 0.80839, -0.22872, -0.20368, 0.37534, 0.036379, 0.91204, -0.12344, 1.1105, -0.43384, -0.059015, 0.021492},
          {13.424, 14.732, 13.934, 16.817, 7.5563, 2.0869, 4.0621, 10.85, 9.3898, 12.8, 12.535, 7.2074, 2.8856, 3.7009, 5.1403, 5.3424, 6.0043, -6.0346, -4.7591, 0.82894, 3.969, 1.848, 6.6624, 4.949, -2.3459, -5.6969, 0.17966, -1.6348, -0.77317, -0.50961, -1.028, -0.41171, -0.21445, -0.14702, 0.73228, -0.29575, -0.4156, -0.63977, 1.1138, -0.2098, -0.073943, 0.73573, 3.4323, 4.9122, 5.6673, 5.7584, 1.8314, 0.48373, 0.87761, 4.3208, 3.6063, 3.1656, 4.0424, 0.36072, 0.38937, -0.40417, 4.6683, 1.6053, 2.0176, 0.58621, 0.16382, -0.22106, 0.64897, 2.6099, 1.373, 0.56104, 1.1669, -0.27408, 0.13183, 0.016357},
          {16.352, 13.934, 23.443, 22.339, 10.851, 1.9643, 2.8783, 14.791, 10.303, 16.636, 18.336, 9.7654, 2.7286, 2.4017, -2.3928, 0.0068684, -0.83689, -7.7036, -5.9665, 1.7965, 4.6902, -3.32, 4.4173, -4.8444, -3.0199, -8.3332, 1.2337, -0.18421, -0.71247, -0.37469, -0.68509, -0.03213, 0.29427, -0.17471, -0.14692, -0.59221, -0.14169, 0.073487, 1.0168, -0.30713, 0.03511, 0.5138, 5.6129, 2.5797, 5.5049, 3.8557, 0.9998, 0.60985, 0.78766, 6.3785, 3.5328, 1.7568, 2.5917, 0.76227, 0.25885, -0.5197, 3.8697, 2.0919, 0.58781, 0.53837, -0.0085377, -0.15146, 0.41498, 0.20229, 1.2167, -0.25365, 0.38554, 0.059269, 0.13656, -0.12428},
          {21.763, 16.817, 22.339, 30.637, 12.885, 3.4771, 5.4565, 18.671, 13.394, 19.455, 20.233, 11.389, 4.1264, 5.3366, 2.2129, 1.5101, 2.7146, -4.5576, -7.1423, 2.3775, 6.0463, 2.1879, 7.4826, -2.4881, 0.3577, -9.2436, 0.48727, -1.8632, -1.2212, -1.1026, -1.316, -0.62145, -0.28615, -0.50343, 0.37933, -0.49394, -0.54969, -0.30622, 1.231, -0.38079, -0.14701, 1.0386, 7.2224, 5.4533, 7.0127, 7.1615, 2.0519, 0.69854, 1.4227, 8.4147, 6.0715, 3.1313, 4.5158, 0.58304, 0.10837, -0.82442, 3.3184, 1.6092, 0.80479, 0.50092, -0.038143, -0.23148, 0.70459, 0.83828, 0.86789, -0.053676, 0.49502, -0.25827, 0.043533, -0.013689},
          {10.454, 7.5563, 10.851, 12.885, 11.368, 1.7379, 2.7011, 8.1123, 6.675, 9.9414, 10.831, 5.7571, 2.4072, 3.474, 12.886, 2.6874, 6.8736, -0.59036, 3.7972, 0.6898, 2.0454, 5.34, 2.1361, -1.0307, 3.2042, 1.2168, 0.12116, 0.32738, -0.22175, -0.98143, -0.53424, -0.16166, -0.13425, -0.55009, 0.15357, 0.62498, -1.1812, -0.38457, 0.58849, -0.14978, -0.38286, 0.4138, 1.8466, 2.0078, 2.8708, 2.5539, 0.80124, 0.11968, 0.88128, 4.0822, 2.9067, 0.96611, 1.7963, 1.2178, -0.3998, -0.010887, 0.74091, 0.57659, 0.39618, 0.59183, -0.21966, -0.019598, 0.19665, -0.26736, 0.71993, 0.11782, 0.082895, 0.43587, -0.14995, -0.32898},
          {3.1358, 2.0869, 1.9643, 3.4771, 1.7379, 1.7239, 1.2433, 2.3952, 1.593, 1.9123, 1.9397, 1.1941, 1.1704, 1.2344, 3.0523, 0.56614, 2.1518, -0.40422, -1.3968, 0.87163, 1.0143, 2.3422, -0.51352, 0.91941, -1.4483, -1.7854, 0.59322, -0.073709, -0.08329, -0.4263, -0.19652, -0.12542, -0.028989, -0.1893, -0.092644, 0.10125, -0.11648, -0.054351, 0.31313, -0.044117, -0.10672, 0.19427, 0.56613, 1.1535, -0.04167, 0.46479, 0.39518, 0.20604, -0.024605, -0.79033, 0.7377, 0.10567, 0.46162, 0.10413, 0.01472, -0.043628, 0.1631, -0.068094, -0.068835, 0.001552, -0.10399, -0.027148, 0.15756, -0.20583, 0.065526, -0.045689, 0.020638, -0.098948, -0.0056201, 0.048339},
          {5.0395, 4.0621, 2.8783, 5.4565, 2.7011, 1.2433, 4.2405, 3.6106, 3.3715, 3.6469, 3.177, 2.3216, 1.8983, 3.298, 8.4806, 6.4679, 10.701, 3.2615, 0.26433, 0.40226, 2.5537, 8.7628, 6.2619, 7.8456, 2.2695, 0.64621, 0.15008, -1.1842, -0.20414, -0.67115, -0.47096, -0.21777, -0.3314, -0.28317, 0.45271, -0.14342, -0.12287, -0.27064, 0.44837, -0.10958, -0.2096, 0.21459, 3.7334, 2.9779, 3.5924, 2.8454, 0.60273, 0.40792, 0.3766, 3.8702, 3.0548, 2.3384, 2.8135, 0.37234, -0.04487, -0.21543, 1.1603, 0.4778, 1.004, 0.58676, -0.051547, -0.12327, 0.16737, 1.9167, 1.1645, 0.8653, 0.70675, -0.42694, -0.028331, -0.2513},
          {20.224, 10.85, 14.791, 18.671, 8.1123, 2.3952, 3.6106, 56.696, 20.351, 14.097, 15.222, 7.2973, 3.1421, 4.2514, 2.2481, 6.6313, 6.604, 4.1929, -5.4294, 3.7683, 4.4652, -0.32545, 8.9776, 4.0802, 4.1301, -4.2162, -0.57703, -4.1136, 1.6474, -0.071288, -1.896, -0.40312, -1.0304, -0.53985, 0.21006, 0.97096, 0.48416, -0.25288, 0.50552, -0.46185, -0.046521, 0.015752, 9.1035, 4.3516, 5.3804, 2.7942, -1.3436, 0.098518, 1.3773, 2.1146, 8.3226, 2.9445, 2.7121, -1.0674, -0.14569, -1.4281, 0.22639, 0.70909, -0.8581, 0.07034, -0.25526, -0.031293, -0.69912, -0.94021, 0.4218, -0.33178, 0.42097, -0.7539, -0.17753, -1.2384},
          {11.944, 9.3898, 10.303, 13.394, 6.675, 1.593, 3.3715, 20.351, 16.753, 10.703, 10.277, 5.0751, 2.6071, 2.4326, 8.8003, 4.394, 9.5375, -3.7835, -1.776, 1.442, 3.0151, 6.5256, 6.9766, 5.8501, 1.1178, -2.997, -0.23032, -1.4031, -0.039594, -0.62037, -0.86458, -0.58696, -0.6174, -0.30102, -0.025562, -0.020072, -0.22339, -0.38663, 0.39005, -0.1962, 0.078874, 0.34104, 4.5499, 4.0712, 4.7066, 3.76, 0.70744, 0.12888, 0.66674, 2.4567, 3.5658, 2.3375, 2.1161, 0.55328, 0.18469, -0.7181, 1.5505, 0.54413, 1.0703, 0.50944, -0.23432, -0.089878, 0.18225, 1.0795, 0.43803, 0.57462, 0.69836, -0.4085, -0.035382, -0.531},
          {15.636, 12.8, 16.636, 19.455, 9.9414, 1.9123, 3.6469, 14.097, 10.703, 19.022, 16.075, 8.4085, 2.7253, 3.5931, 1.8308, 2.8534, 5.0785, -7.1158, -6.3644, 1.2248, 4.1807, -1.5353, 6.8474, 0.90808, 0.063125, -6.4677, 0.38691, -1.2963, -0.84374, -0.76479, -0.70865, -0.34424, -0.22362, -0.30956, 0.27915, -0.093113, -0.72308, -0.599, 0.98668, -0.21025, -0.10957, 0.57503, -0.19093, 3.1132, 5.5923, 3.1254, 1.4556, 0.46104, 1.0117, 4.4304, 2.2584, 2.1174, 2.3189, 0.74167, -0.054678, -0.63661, 1.2762, 1.1637, 0.81637, 0.39752, -0.085323, -0.18923, 0.48341, -0.30565, 0.73283, 0.035321, 0.68757, -0.32261, 0.010085, -0.05502},
          {15.766, 12.535, 18.336, 20.233, 10.831, 1.9397, 3.177, 15.222, 10.277, 16.075, 20.658, 8.9857, 2.5087, 3.582, -1.4559, 1.7307, 1.7057, 1.1519, -4.4153, 1.5923, 4.6175, -7.0118, 1.3772, -2.5372, 1.6049, -6.1347, 0.19406, -0.50131, -0.39419, -0.78772, -0.87738, -0.54121, -0.14474, -0.20413, -0.14313, 0.041586, -1.007, -0.50552, 0.59822, -0.42247, -0.23362, 0.63747, 5.9665, 3.9228, 5.6289, 4.722, 1.3586, 0.586, 1.0945, 6.2583, 5.4633, 3.663, 3.677, 0.96268, -0.23419, -0.64859, 2.4029, 1.0165, 0.50394, 0.24659, -0.21119, -0.07656, 0.5889, -0.86287, 1.0692, 0.017292, 0.61971, -0.050324, 0.017878, -0.2399},
          {9.1389, 7.2074, 9.7654, 11.389, 5.7571, 1.1941, 2.3216, 7.2973, 5.0751, 8.4085, 8.9857, 7.0107, 1.8505, 2.0055, -3.0903, 2.2431, 1.3868, -1.8163, 0.10945, 0.92174, 2.3325, -0.49509, 3.2289, -0.16396, -1.3417, -1.1177, 0.34078, 0.44834, -0.75966, -0.40943, -0.49868, -0.24847, -0.10229, -0.17584, 0.19161, -0.56592, -0.073984, -0.15006, 0.64034, -0.12885, -0.11205, 0.49154, 4.7205, 2.2142, 4.1248, 3.1424, 0.96818, 0.34655, 0.70967, 5.6134, 3.0606, 1.7785, 2.5965, 0.25344, 0.046462, -0.14061, 1.6124, 1.0485, 0.68226, 0.3451, -0.016216, -0.19794, 0.35776, 0.65099, 0.90384, 0.39469, 0.46885, -0.28412, 0.09792, 0.04186},
          {3.6114, 2.8856, 2.7286, 4.1264, 2.4072, 1.1704, 1.8983, 3.1421, 2.6071, 2.7253, 2.5087, 1.8505, 2.5358, 2.057, 7.329, 3.1428, 6.2482, 1.8666, -1.3825, 0.97692, 1.1132, 7.6273, 3.9572, 4.4093, 2.1525, -1.5669, 0.71023, -0.35252, 0.031437, -0.4801, -0.21612, -0.12868, -0.13722, -0.23646, 0.044669, 0.22889, -0.36395, -0.16971, 0.58291, -0.06383, -0.061906, 0.47312, 1.4821, 1.638, 1.5501, 1.9128, 0.34938, 0.22106, 0.25257, 1.9351, 1.889, 1.1585, 1.9888, 0.23168, 0.034338, -0.0038304, 1.1165, 0.3405, 0.56394, 0.6285, -0.15373, -0.071301, 0.081612, 0.65917, 0.34453, 0.30854, 0.33984, -0.12766, -0.028528, -0.0045298},
          {4.94, 3.7009, 2.4017, 5.3366, 3.474, 1.2344, 3.298, 4.2514, 2.4326, 3.5931, 3.582, 2.0055, 2.057, 6.3176, 3.0235, 4.9332, 8.2329, 3.5129, 0.31745, -0.14403, 2.5449, 2.3316, 1.1271, 6.1894, 3.8807, 0.39275, 0.21826, -1.2388, -0.071992, -1.1604, -0.20033, -0.56658, -0.41225, -0.46291, 0.019908, 0.51509, -1.3625, -0.8679, 0.47679, -0.13969, -0.29693, 1.0416, 4.2301, 4.6211, 3.672, 3.2182, 0.72637, 0.22306, 0.36167, 5.3624, 3.6347, 2.8217, 3.2931, 0.9365, -0.28769, -0.26655, 1.3363, -0.016717, 0.7429, 1.0894, -0.067804, -0.15297, 0.11619, 1.4223, 1.4237, 0.47888, 0.8269, 0.041538, -0.13146, -0.22882},
          {2.6272, 5.1403, -2.3928, 2.2129, 12.886, 3.0523, 8.4806, 2.2481, 8.8003, 1.8308, -1.4559, -3.0903, 7.329, 3.0235, 1005.2, 191.03, 276.18, 197.44, 75.199, 5.1917, 12.391, 775.45, 187.59, 211.59, 225.45, 79.027, 17.77, 29.546, -3.6499, -5.7408, 2.3791, 1.3095, -2.6249, -4.19, 2.3053, 9.1529, -7.5192, -0.89785, -1.0953, 0.81888, -1.6614, -4.1938, 146.99, 35.679, 31.905, 39.446, 6.1975, -0.089671, 1.371, 139.35, 25.473, 13.444, 25.607, 4.1987, 1.7489, -0.51562, 44.845, 1.3363, 3.0063, 11.812, -3.6055, 1.526, -3.0366, 32.404, 7.2897, 7.0753, 3.4708, 2.4642, -2.3018, -2.8429},
          {3.154, 5.3424, 0.0068684, 1.5101, 2.6874, 0.56614, 6.4679, 6.6313, 4.394, 2.8534, 1.7307, 2.2431, 3.1428, 4.9332, 191.03, 140.33, 144.62, 118.82, 44.564, -0.23552, 1.4017, 145.7, 81.196, 126.18, 92.241, 36.499, 1.5425, 4.3568, 0.63948, -0.88456, -1.7216, 0.067858, -1.4634, -1.2152, 1.6457, -0.88012, -3.392, -1.7393, 0.27602, -0.95785, -1.2749, -0.43992, 34.973, 22.167, 32.164, 27.106, 3.8058, 1.5335, 0.86987, 34.373, 27.458, 29.87, 22.991, 3.5965, 0.3352, 0.42148, 15.092, 4.5219, 6.1384, 5.0727, -0.1724, -0.12908, -0.39814, 11.058, 6.1923, 5.4562, 3.2408, -0.031495, -0.29887, -0.5134},
          {7.2268, 6.0043, -0.83689, 2.7146, 6.8736, 2.1518, 10.701, 6.604, 9.5375, 5.0785, 1.7057, 1.3868, 6.2482, 8.2329, 276.18, 144.62, 257.02, 149.09, 59.159, 2.3928, 2.6817, 214.0, 114.45, 176.84, 128.08, 55.639, 6.0529, 1.8441, 1.2847, -2.9943, -1.4949, -0.85097, -1.7286, -1.2901, 1.8376, 1.9646, -5.8412, -1.9071, 1.696, -0.61983, -1.568, -1.105, 29.217, 32.295, 37.586, 37.769, 8.007, 0.92813, 0.79092, 27.507, 34.217, 35.259, 30.347, 7.5237, 0.21015, -1.3381, 10.835, 3.3516, 7.1291, 9.7984, -0.87667, -0.15276, -0.79979, 13.373, 7.81, 7.9161, 4.1348, -0.25654, -1.4514, -2.635},
          {0.1247, -6.0346, -7.7036, -4.5576, -0.59036, -0.40422, 3.2615, 4.1929, -3.7835, -7.1158, 1.1519, -1.8163, 1.8666, 3.5129, 197.44, 118.82, 149.09, 267.57, 72.183, 7.4667, -3.9256, 147.12, 72.125, 122.55, 182.7, 58.753, 9.3128, 0.29393, 2.0797, -0.81933, -0.807, 1.4339, -1.5508, -1.6415, -0.98953, 2.0516, -7.1659, -0.56927, -0.31085, -1.0527, -1.9645, -0.73402, 47.032, 28.263, 31.246, 26.88, 3.9218, -0.68572, -1.0995, 30.104, 28.41, 34.501, 30.901, 2.4261, -0.91021, -0.062126, 7.8628, 1.2458, 1.5679, 5.7478, -0.29824, -0.076648, -1.3877, 5.7821, 4.7772, 3.8176, 2.1149, -0.83062, -0.9444, -3.256},
          {-2.9303, -4.7591, -5.9665, -7.1423, 3.7972, -1.3968, 0.26433, -5.4294, -1.776, -6.3644, -4.4153, 0.10945, -1.3825, 0.31745, 75.199, 44.564, 59.159, 72.183, 106.3, 3.2193, -2.5975, 61.155, 33.875, 41.429, 56.88, 68.78, 2.8576, 6.5823, -0.023106, -0.79368, 0.24943, -0.78698, -0.5101, 0.062366, 2.0432, -0.82809, -2.0554, 1.0794, -1.0595, 0.25654, -0.81364, 1.535, 10.488, 0.82932, 11.859, 10.302, -0.7168, 0.17481, 0.35513, 8.5053, 8.6549, 10.088, 7.6286, 2.0785, -0.20736, 1.5316, 5.5184, 1.5489, 2.0437, 2.8754, -0.19249, -0.26288, -0.32294, 5.8569, 1.2781, 2.5148, -0.54332, 2.2139, -0.39336, -1.0781},
          {2.6016, 0.82894, 1.7965, 2.3775, 0.6898, 0.87163, 0.40226, 3.7683, 1.442, 1.2248, 1.5923, 0.92174, 0.97692, -0.14403, 5.1917, -0.23552, 2.3928, 7.4667, 3.2193, 9.892, 0.6658, 8.1159, 4.2529, -1.0533, 5.0038, 1.1331, 4.8218, -0.014937, 0.53317, -0.015645, -0.051731, -0.21552, -0.093964, 0.07046, 0.3791, -0.71966, 0.53801, 0.47523, 0.19078, 0.14718, -0.22708, 0.22886, -0.27086, -0.71441, 0.94777, 0.74582, 0.080683, 0.26347, -0.14408, -4.8869, 0.26785, 0.01711, 1.167, -0.37341, 0.039688, -0.62037, 0.29185, -0.21576, -0.5657, -0.1644, -0.12433, 0.019729, 0.21677, -1.6544, -0.70868, -0.38385, -0.75045, 0.087234, -0.068867, 0.35117},
          {5.1647, 3.969, 4.6902, 6.0463, 2.0454, 1.0143, 2.5537, 4.4652, 3.0151, 4.1807, 4.6175, 2.3325, 1.1132, 2.5449, 12.391, 1.4017, 2.6817, -3.9256, -2.5975, 0.6658, 7.6268, 7.4727, 4.8044, 1.6102, -2.4805, -2.1246, 0.82603, -0.67101, -0.34823, -0.078994, -0.31571, -0.31047, -0.16767, 0.040004, 0.29453, -0.30138, 0.5423, -0.011669, 0.13111, -0.24615, 0.036517, 0.0064929, -2.2209, 0.42089, 0.61876, 0.92436, -0.12696, 0.70909, 0.050797, -0.055537, 0.94569, -0.060301, -0.54685, -0.066057, 0.22893, -0.81459, -1.1069, -0.074336, -0.29141, -0.3818, -0.010433, -0.053096, 0.2642, 0.24077, 0.28052, -0.26422, -0.036451, -0.26628, 0.08914, 0.19393},
          {8.0038, 1.848, -3.32, 2.1879, 5.34, 2.3422, 8.7628, -0.32545, 6.5256, -1.5353, -7.0118, -0.49509, 7.6273, 2.3316, 775.45, 145.7, 214.0, 147.12, 61.155, 8.1159, 7.4727, 864.84, 174.49, 184.49, 187.0, 79.635, 20.965, 24.026, -5.9809, -4.4383, 3.9248, 0.91273, -2.9612, -2.8882, 1.6816, 6.4648, -5.631, -1.684, 0.53609, 0.73275, -1.2241, -4.056, 148.93, 36.042, 28.658, 15.215, 6.1151, 1.9253, 0.44102, 164.75, 25.803, 14.004, 27.875, 2.8554, 2.3725, 2.7038, 44.417, -3.4115, 3.9503, 9.8717, -3.2168, 0.96182, -3.918, 37.7, 8.9714, 6.7782, 3.1358, 1.5019, -1.4817, -1.8005},
          {6.9048, 6.6624, 4.4173, 7.4826, 2.1361, -0.51352, 6.2619, 8.9776, 6.9766, 6.8474, 1.3772, 3.2289, 3.9572, 1.1271, 187.59, 81.196, 114.45, 72.125, 33.875, 4.2529, 4.8044, 174.49, 149.07, 96.968, 72.705, 33.681, 7.3158, 2.4811, -0.6066, 0.25435, -2.1961, -0.38102, -1.0307, 0.18447, 4.6355, -3.0005, 0.30969, 0.64656, 1.3946, -0.76384, -0.12478, -0.46679, 14.402, 11.685, 17.411, 16.299, 3.9923, 0.91288, 1.8475, 29.548, 16.668, 16.38, 14.888, 3.7571, 1.7151, 0.097655, 16.398, 3.2601, 5.8141, 4.3172, 0.58883, 0.11353, 0.2141, 14.642, 4.3111, 4.8, 1.1877, -0.43977, -0.24713, 0.49724},
          {4.96, 4.949, -4.8444, -2.4881, -1.0307, 0.91941, 7.8456, 4.0802, 5.8501, 0.90808, -2.5372, -0.16396, 4.4093, 6.1894, 211.59, 126.18, 176.84, 122.55, 41.429, -1.0533, 1.6102, 184.49, 96.968, 203.66, 103.14, 39.565, 1.8975, -0.84505, 1.3439, -1.1532, -2.2715, -0.44702, -1.2243, -0.79013, 3.8397, 1.2177, -2.9062, -2.1223, 1.8249, -0.67287, -0.81445, 0.0092235, 24.309, 31.108, 36.992, 29.25, 5.5954, 1.3255, 1.5828, 29.136, 31.308, 33.713, 26.713, 4.147, 0.40398, 0.31901, 10.304, 4.231, 7.8788, 5.1644, 0.13636, -0.41611, -0.27699, 13.433, 9.2863, 6.6872, 6.2156, -0.9473, -0.42988, -1.1595},
          {4.2144, -2.3459, -3.0199, 0.3577, 3.2042, -1.4483, 2.2695, 4.1301, 1.1178, 0.063125, 1.6049, -1.3417, 2.1525, 3.8807, 225.45, 92.241, 128.08, 182.7, 56.88, 5.0038, -2.4805, 187.0, 72.705, 103.14, 222.18, 52.123, 8.8172, 7.6108, -0.93027, -2.3283, 0.40423, 1.313, -2.094, -1.5952, -1.0749, 3.5292, -6.4909, 0.013684, -0.6305, -0.38203, -1.2475, 0.60193, 44.852, 18.93, 25.83, 27.34, 3.8493, -0.57772, 0.2642, 43.9, 20.827, 21.451, 27.663, 1.7393, -1.1591, 0.81388, 7.3814, 0.20438, 0.4163, 4.4399, -0.88233, 0.194, -1.4806, 7.8418, 2.5241, 3.6985, 0.9328, 0.81216, -1.197, -2.9374},
          {-4.5489, -5.6969, -8.3332, -9.2436, 1.2168, -1.7854, 0.64621, -4.2162, -2.997, -6.4677, -6.1347, -1.1177, -1.5669, 0.39275, 79.027, 36.499, 55.639, 58.753, 68.78, 1.1331, -2.1246, 79.635, 33.681, 39.565, 52.123, 78.491, 4.1388, 4.1153, -0.2825, -0.54238, -0.24108, 0.12568, -0.76637, 0.13006, 1.4864, -0.57598, -2.9236, 0.87828, -1.6415, 0.49672, -0.39603, 0.20591, 16.109, 5.3382, 13.145, 8.1922, 1.2168, -0.37911, 0.89874, 14.244, 9.1829, 12.146, 8.5663, 2.3449, -0.30726, 0.39974, 3.9523, 0.83528, 0.97734, 3.9277, -0.017176, -0.031269, -0.67145, 8.1304, 2.2927, 4.0833, 0.38418, 2.0864, -0.35178, -1.3931},
          {0.15967, 0.17966, 1.2337, 0.48727, 0.12116, 0.59322, 0.15008, -0.57703, -0.23032, 0.38691, 0.19406, 0.34078, 0.71023, 0.21826, 17.77, 1.5425, 6.0529, 9.3128, 2.8576, 4.8218, 0.82603, 20.965, 7.3158, 1.8975, 8.8172, 4.1388, 11.948, 7.4306, 0.36445, 0.02665, -0.010933, -0.025235, -0.03947, -0.096066, 0.28579, 0.19356, -0.42777, 0.017453, 0.2174, -0.0037665, -0.080975, -0.11891, 1.1756, 1.4218, 1.3094, 0.020123, 0.66128, 0.065985, 0.023452, 0.37739, 0.68829, -0.80909, 2.7998, 0.65074, 0.052256, 2.1302, -0.43459, -0.34596, -0.23287, 0.31982, 0.16628, -0.024492, 0.34964, 0.8029, 0.051083, 0.1494, -0.24586, 0.26358, -0.027649, 0.54486},
          {-3.3981, -1.6348, -0.18421, -1.8632, 0.32738, -0.073709, -1.1842, -4.1136, -1.4031, -1.2963, -0.50131, 0.44834, -0.35252, -1.2388, 29.546, 4.3568, 1.8441, 0.29393, 6.5823, -0.014937, -0.67101, 24.026, 2.4811, -0.84505, 7.6108, 4.1153, 7.4306, 30.077, 0.5981, 0.95039, -0.15902, 0.14047, 0.14898, -0.5034, -0.10774, 0.11766, -0.058069, -0.1989, -0.24254, -0.21957, 0.14393, -0.60046, 5.435, -1.4817, 1.2061, 1.8262, -0.20502, 0.049044, -0.81995, 6.294, -0.49673, -3.3697, -0.90142, -0.21458, -0.42224, 5.1888, 0.20002, -0.039729, -0.74974, -0.9656, -0.21937, 0.088207, 0.13618, 1.5707, -0.6525, 0.31853, -0.43034, 1.4358, 0.22148, 0.77249},
          {-0.50065, -0.77317, -0.71247, -1.2212, -0.22175, -0.08329, -0.20414, 1.6474, -0.039594, -0.84374, -0.39419, -0.75966, 0.031437, -0.071992, -3.6499, 0.63948, 1.2847, 2.0797, -0.023106, 0.53317, -0.34823, -5.9809, -0.6066, 1.3439, -0.93027, -0.2825, 0.36445, 0.5981, 3.0363, 0.47383, 0.28498, 0.31652, 0.082069, 0.085649, 0.1066, 0.67372, 0.35649, 0.30778, 0.24599, 0.039394, 0.07034, -0.31823, -0.94614, 0.54309, -0.12497, -0.34174, -0.20425, 0.31684, 0.070544, 0.0042325, 0.41538, 1.0329, -0.93576, -0.2698, -0.069232, 0.0705, -0.0036851, 0.056971, -0.059321, 0.16453, -0.1107, 0.053264, 0.10721, -0.07054, -0.029699, -0.13573, 0.33231, 0.23436, 0.032775, 0.10114},
          {-1.0013, -0.50961, -0.37469, -1.1026, -0.98143, -0.4263, -0.67115, -0.071288, -0.62037, -0.76479, -0.78772, -0.40943, -0.4801, -1.1604, -5.7408, -0.88456, -2.9943, -0.81933, -0.79368, -0.015645, -0.078994, -4.4383, 0.25435, -1.1532, -2.3283, -0.54238, 0.02665, 0.95039, 0.47383, 2.397, 0.43612, 0.77934, 0.20693, 0.23521, 0.17849, 0.17585, 0.96888, 0.65169, 0.29751, -0.02464, 0.159, -0.43491, -3.3946, -1.986, -1.1437, -1.3709, -0.20721, -0.10661, -0.16158, -4.5431, -0.88026, -0.96248, -1.2345, -0.65389, -0.016837, -0.18657, 0.41066, 0.18925, 0.25505, -0.32279, 0.11044, 0.0084046, 0.1446, 1.0136, 0.15157, 0.03518, 0.13793, 0.13685, 0.15121, 0.22571},
          {-1.2021, -1.028, -0.68509, -1.316, -0.53424, -0.19652, -0.47096, -1.896, -0.86458, -0.70865, -0.87738, -0.49868, -0.21612, -0.20033, 2.3791, -1.7216, -1.4949, -0.807, 0.24943, -0.051731, -0.31571, 3.9248, -2.1961, -2.2715, 0.40423, -0.24108, -0.010933, -0.15902, 0.28498, 0.43612, 1.8186, 0.38288, 0.16996, 0.036861, -0.24331, 0.63836, 0.10835, 0.46434, 0.28212, 0.15158, -0.0031401, -0.1391, 0.52592, -0.37689, -1.2661, -0.75338, 0.078156, 0.083182, -0.21231, 1.2401, -1.2545, -1.4714, -0.76851, 0.090389, -0.018768, -0.09086, -0.61999, -0.30131, -0.24967, 0.11554, -0.093306, 0.022901, -0.022815, -0.47356, -0.13041, -0.014645, -0.060077, 0.20323, -0.017683, 0.10174},
          {-0.74028, -0.41171, -0.03213, -0.62145, -0.16166, -0.12542, -0.21777, -0.40312, -0.58696, -0.34424, -0.54121, -0.24847, -0.12868, -0.56658, 1.3095, 0.067858, -0.85097, 1.4339, -0.78698, -0.21552, -0.31047, 0.91273, -0.38102, -0.44702, 1.313, 0.12568, -0.025235, 0.14047, 0.31652, 0.77934, 0.38288, 1.7179, 0.26824, 0.042957, -0.3019, 0.71924, 0.72867, 0.40468, 0.5434, 0.10105, 0.065221, -0.43607, -1.1539, -0.7414, -0.46563, -0.15903, 0.025321, -0.11256, -0.21137, -0.34818, -0.45586, -1.135, -0.33296, -0.19472, -0.021596, -0.45792, -0.20787, 0.060858, -0.095408, 0.039033, 0.082282, 0.041747, -0.032146, 0.66434, -0.050564, 0.1075, 0.041681, 0.086796, 0.062101, 0.017415},
          {-0.55454, -0.21445, 0.29427, -0.28615, -0.13425, -0.028989, -0.3314, -1.0304, -0.6174, -0.22362, -0.14474, -0.10229, -0.13722, -0.41225, -2.6249, -1.4634, -1.7286, -1.5508, -0.5101, -0.093964, -0.16767, -2.9612, -1.0307, -1.2243, -2.094, -0.76637, -0.03947, 0.14898, 0.082069, 0.20693, 0.16996, 0.26824, 0.48189, 0.071586, -0.006261, 0.19506, 0.1773, 0.31724, 0.23233, 0.075451, 0.07883, -0.050137, -1.1992, -0.6027, -0.7487, -0.45372, 0.20235, 0.022138, -0.079742, -0.94507, -0.68788, -0.5317, -0.46554, 0.31178, 0.073204, 0.04103, 0.079697, 0.10544, -0.019683, -0.14025, 0.014688, 0.011932, -0.0053709, -0.24886, -0.071376, 0.0055875, -0.087888, 0.12307, 0.012381, 0.053724},
          {-0.37688, -0.14702, -0.17471, -0.50343, -0.55009, -0.1893, -0.28317, -0.53985, -0.30102, -0.30956, -0.20413, -0.17584, -0.23646, -0.46291, -4.19, -1.2152, -1.2901, -1.6415, 0.062366, 0.07046, 0.040004, -2.8882, 0.18447, -0.79013, -1.5952, 0.13006, -0.096066, -0.5034, 0.085649, 0.23521, 0.036861, 0.042957, 0.071586, 0.49092, 0.13921, -0.14634, 0.34844, 0.12517, -0.019184, 0.017046, 0.11385, 0.033317, -0.27024, -0.02025, -0.14699, -0.34216, 0.012895, 0.072537, 0.12608, -0.82314, -0.26505, -0.13451, -0.20485, -0.13079, 0.10542, -0.23589, 0.15238, -0.10055, 0.14865, -0.13517, 0.020398, 0.019598, 0.13598, 0.14686, 0.075568, 0.042214, 0.052923, 0.054273, 0.053309, 0.059132},
          {0.81781, 0.73228, -0.14692, 0.37933, 0.15357, -0.092644, 0.45271, 0.21006, -0.025562, 0.27915, -0.14313, 0.19161, 0.044669, 0.019908, 2.3053, 1.6457, 1.8376, -0.98953, 2.0432, 0.3791, 0.29453, 1.6816, 4.6355, 3.8397, -1.0749, 1.4864, 0.28579, -0.10774, 0.1066, 0.17849, -0.24331, -0.3019, -0.006261, 0.13921, 3.374, -0.24815, 0.40779, -0.0035665, -0.018133, -0.13671, 0.020826, 0.51494, -0.94637, 0.26336, -0.33344, 0.352, -0.40408, 0.18896, 1.5138, 0.064176, -0.14452, 0.95338, 0.15479, 0.16355, 0.049332, 1.0088, -0.21547, -0.28281, 0.47489, -0.43049, -0.0076041, -0.10077, 0.1266, 0.026931, 0.34774, -0.1601, 0.19682, -0.048397, -0.016816, 0.11669},
          {0.23105, -0.29575, -0.59221, -0.49394, 0.62498, 0.10125, -0.14342, 0.97096, -0.020072, -0.093113, 0.041586, -0.56592, 0.22889, 0.51509, 9.1529, -0.88012, 1.9646, 2.0516, -0.82809, -0.71966, -0.30138, 6.4648, -3.0005, 1.2177, 3.5292, -0.57598, 0.19356, 0.11766, 0.67372, 0.17585, 0.63836, 0.71924, 0.19506, -0.14634, -0.24815, 3.7565, -0.023128, 0.29287, 0.62702, 0.21638, 0.040682, -0.40629, -1.0408, 0.49232, -1.2487, -0.59687, 0.50827, -0.022472, -0.18877, 2.2244, -0.062889, -0.76805, -0.13707, 0.25904, -0.25229, 0.16727, 0.070393, -0.31684, -0.14659, 0.61087, -0.1074, 0.064936, 0.034422, 0.43365, -0.22469, 0.12598, 0.27622, 0.33582, -0.098258, -0.062539},
          {-0.76926, -0.4156, -0.14169, -0.54969, -1.1812, -0.11648, -0.12287, 0.48416, -0.22339, -0.72308, -1.007, -0.073984, -0.36395, -1.3625, -7.5192, -3.392, -5.8412, -7.1659, -2.0554, 0.53801, 0.5423, -5.631, 0.30969, -2.9062, -6.4909, -2.9236, -0.42777, -0.058069, 0.35649, 0.96888, 0.10835, 0.72867, 0.1773, 0.34844, 0.40779, -0.023128, 3.1585, 0.85481, 0.44085, 0.036026, 0.26391, -0.24213, -1.6048, -2.1707, -1.3942, -0.91404, -0.25976, 0.045801, 0.15955, -2.888, -1.0889, -1.5599, -1.997, -0.64429, 0.174, -0.15865, -1.7053, -0.10856, -0.14212, -0.87099, 0.030755, 0.0029116, 0.18354, -0.9967, -0.51281, -0.47502, -0.32232, -0.14572, 0.146, -0.021509},
          {-0.8439, -0.63977, 0.073487, -0.30622, -0.38457, -0.054351, -0.27064, -0.25288, -0.38663, -0.599, -0.50552, -0.15006, -0.16971, -0.8679, -0.89785, -1.7393, -1.9071, -0.56927, 1.0794, 0.47523, -0.011669, -1.684, 0.64656, -2.1223, 0.013684, 0.87828, 0.017453, -0.1989, 0.30778, 0.65169, 0.46434, 0.40468, 0.31724, 0.12517, -0.0035665, 0.29287, 0.85481, 1.8191, 0.46942, 0.12591, 0.13776, -0.083387, -1.8776, -1.7692, -1.4161, -1.0302, 0.018335, 0.040802, -0.14785, -1.2612, -1.0624, -0.8707, -0.88354, 0.090746, 0.034433, -0.083657, -0.61687, 0.019292, -0.26775, -0.17153, -0.080803, -0.016491, 0.12339, -0.51829, -0.50627, -0.17746, -0.25011, 0.12187, 0.033368, 0.08295},
          {0.87561, 1.1138, 1.0168, 1.231, 0.58849, 0.31313, 0.44837, 0.50552, 0.39005, 0.98668, 0.59822, 0.64034, 0.58291, 0.47679, -1.0953, 0.27602, 1.696, -0.31085, -1.0595, 0.19078, 0.13111, 0.53609, 1.3946, 1.8249, -0.6305, -1.6415, 0.2174, -0.24254, 0.24599, 0.29751, 0.28212, 0.5434, 0.23233, -0.019184, -0.018133, 0.62702, 0.44085, 0.46942, 1.7855, 0.092731, 0.075694, -0.016524, 0.95024, 1.2168, 0.571, 1.712, 0.19914, 0.080475, -0.16356, 1.2018, 0.45762, 0.026255, 1.7578, 0.25946, 0.19606, -0.14914, 0.11023, 0.095237, 0.4093, 0.2125, 0.0067498, 0.0030017, 0.17346, 0.46041, 0.13943, 0.12584, 0.11644, -0.18797, 0.028573, -0.019312},
          {-0.27353, -0.2098, -0.30713, -0.38079, -0.14978, -0.044117, -0.10958, -0.46185, -0.1962, -0.21025, -0.42247, -0.12885, -0.06383, -0.13969, 0.81888, -0.95785, -0.61983, -1.0527, 0.25654, 0.14718, -0.24615, 0.73275, -0.76384, -0.67287, -0.38203, 0.49672, -0.0037665, -0.21957, 0.039394, -0.02464, 0.15158, 0.10105, 0.075451, 0.017046, -0.13671, 0.21638, 0.036026, 0.12591, 0.092731, 0.27456, 0.026902, -0.039156, -0.047796, 0.20611, 0.041594, 0.51954, 0.20177, -0.0050747, -0.036481, 0.55724, -0.17175, -0.10247, 0.012013, 0.10246, 0.037313, -0.038864, 0.2465, 0.015836, 0.086386, 0.10785, -0.012111, 0.016911, 0.022922, 0.39349, -0.021292, 0.08011, 0.033139, 0.049773, -0.01184, -0.013878},
          {-0.1891, -0.073943, 0.03511, -0.14701, -0.38286, -0.10672, -0.2096, -0.046521, 0.078874, -0.10957, -0.23362, -0.11205, -0.061906, -0.29693, -1.6614, -1.2749, -1.568, -1.9645, -0.81364, -0.22708, 0.036517, -1.2241, -0.12478, -0.81445, -1.2475, -0.39603, -0.080975, 0.14393, 0.07034, 0.159, -0.0031401, 0.065221, 0.07883, 0.11385, 0.020826, 0.040682, 0.26391, 0.13776, 0.075694, 0.026902, 0.33213, -0.0087142, -0.42828, -0.41311, -0.42172, -0.20635, 0.013635, -0.02135, -0.011957, -0.26421, -0.45019, -0.18478, -0.6033, -0.019935, 0.1354, -0.1478, -0.25401, -0.041011, -0.06355, -0.098918, -0.020208, 0.026565, 0.032674, -0.1033, -0.17055, -0.10093, -0.034697, 0.039596, 0.029079, 0.058839},
          {0.53007, 0.73573, 0.5138, 1.0386, 0.4138, 0.19427, 0.21459, 0.015752, 0.34104, 0.57503, 0.63747, 0.49154, 0.47312, 1.0416, -4.1938, -0.43992, -1.105, -0.73402, 1.535, 0.22886, 0.0064929, -4.056, -0.46679, 0.0092235, 0.60193, 0.20591, -0.11891, -0.60046, -0.31823, -0.43491, -0.1391, -0.43607, -0.050137, 0.033317, 0.51494, -0.40629, -0.24213, -0.083387, -0.016524, -0.039156, -0.0087142, 1.8388, 2.6492, 0.72632, 0.57495, 1.1845, -0.091137, -0.049503, 0.70313, 1.5192, 0.48329, 1.1476, 0.89665, 0.46648, -0.047204, 0.4069, 0.5291, 0.069753, 0.22404, -0.16793, 0.017424, -0.066399, 0.26674, -0.1858, -0.23774, 0.04741, 0.11323, 0.12737, -0.010258, -0.047376},
          {3.1935, 3.4323, 5.6129, 7.2224, 1.8466, 0.56613, 3.7334, 9.1035, 4.5499, -0.19093, 5.9665, 4.7205, 1.4821, 4.2301, 146.99, 34.973, 29.217, 47.032, 10.488, -0.27086, -2.2209, 148.93, 14.402, 24.309, 44.852, 16.109, 1.1756, 5.435, -0.94614, -3.3946, 0.52592, -1.1539, -1.1992, -0.27024, -0.94637, -1.0408, -1.6048, -1.8776, 0.95024, -0.047796, -0.42828, 2.6492, 212.37, 47.73, 46.208, 33.763, 11.081, 1.1642, 2.491, 150.19, 36.961, 37.282, 32.553, 3.8441, 0.86619, -1.2282, 20.004, -0.3638, 1.0022, 0.62394, -0.99638, 0.10472, -1.317, 12.415, 5.4838, 1.7825, 1.7168, -1.9218, -0.11177, -3.0123},
          {4.2566, 4.9122, 2.5797, 5.4533, 2.0078, 1.1535, 2.9779, 4.3516, 4.0712, 3.1132, 3.9228, 2.2142, 1.638, 4.6211, 35.679, 22.167, 32.295, 28.263, 0.82932, -0.71441, 0.42089, 36.042, 11.685, 31.108, 18.93, 5.3382, 1.4218, -1.4817, 0.54309, -1.986, -0.37689, -0.7414, -0.6027, -0.02025, 0.26336, 0.49232, -2.1707, -1.7692, 1.2168, 0.20611, -0.41311, 0.72632, 47.73, 35.213, 21.037, 14.254, 4.9126, 0.60823, 1.326, 43.102, 18.04, 19.053, 14.211, 3.1685, 0.79138, 0.31402, 9.8551, -0.022559, 3.2892, 2.4395, 0.056001, 0.0082911, -0.33872, 6.2341, 4.119, 2.0454, 2.5459, -0.65201, -0.042541, -1.3777},
          {4.7622, 5.6673, 5.5049, 7.0127, 2.8708, -0.04167, 3.5924, 5.3804, 4.7066, 5.5923, 5.6289, 4.1248, 1.5501, 3.672, 31.905, 32.164, 37.586, 31.246, 11.859, 0.94777, 0.61876, 28.658, 17.411, 36.992, 25.83, 13.145, 1.3094, 1.2061, -0.12497, -1.1437, -1.2661, -0.46563, -0.7487, -0.14699, -0.33344, -1.2487, -1.3942, -1.4161, 0.571, 0.041594, -0.42172, 0.57495, 46.208, 21.037, 37.139, 16.274, 4.0828, 0.74642, 1.3011, 37.944, 21.678, 20.516, 13.324, 2.0793, 0.47588, -0.93229, 8.9934, 2.7225, 4.0743, 1.9917, 0.31058, -0.29535, -0.49521, 8.1738, 5.4536, 2.5615, 2.7954, -0.5057, 0.10977, -0.85864},
          {4.4467, 5.7584, 3.8557, 7.1615, 2.5539, 0.46479, 2.8454, 2.7942, 3.76, 3.1254, 4.722, 3.1424, 1.9128, 3.2182, 39.446, 27.106, 37.769, 26.88, 10.302, 0.74582, 0.92436, 15.215, 16.299, 29.25, 27.34, 8.1922, 0.020123, 1.8262, -0.34174, -1.3709, -0.75338, -0.15903, -0.45372, -0.34216, 0.352, -0.59687, -0.91404, -1.0302, 1.712, 0.51954, -0.20635, 1.1845, 33.763, 14.254, 16.274, 42.013, 3.5011, 0.40899, 1.0572, 26.817, 14.488, 13.755, 22.539, 1.7702, 0.72404, -0.28525, 7.5573, 0.915, 1.6294, 1.4229, 0.22026, -0.21718, 0.55395, 6.4563, 3.0243, 1.666, 0.75435, -0.38948, -0.18632, -0.41618},
          {1.1547, 1.8314, 0.9998, 2.0519, 0.80124, 0.39518, 0.60273, -1.3436, 0.70744, 1.4556, 1.3586, 0.96818, 0.34938, 0.72637, 6.1975, 3.8058, 8.007, 3.9218, -0.7168, 0.080683, -0.12696, 6.1151, 3.9923, 5.5954, 3.8493, 1.2168, 0.66128, -0.20502, -0.20425, -0.20721, 0.078156, 0.025321, 0.20235, 0.012895, -0.40408, 0.50827, -0.25976, 0.018335, 0.19914, 0.20177, 0.013635, -0.091137, 11.081, 4.9126, 4.0828, 3.5011, 8.4257, -0.062986, 0.25924, 10.609, 2.9851, 4.8899, 3.1477, 3.3518, 0.28802, -0.37535, 3.7895, 0.89017, 1.0944, 0.75476, 0.092543, 0.067136, 0.37405, 3.236, 0.48326, 0.56786, 0.71756, 0.11273, -0.0045016, -0.050603},
          {0.86073, 0.48373, 0.60985, 0.69854, 0.11968, 0.20604, 0.40792, 0.098518, 0.12888, 0.46104, 0.586, 0.34655, 0.22106, 0.22306, -0.089671, 1.5335, 0.92813, -0.68572, 0.17481, 0.26347, 0.70909, 1.9253, 0.91288, 1.3255, -0.57772, -0.37911, 0.065985, 0.049044, 0.31684, -0.10661, 0.083182, -0.11256, 0.022138, 0.072537, 0.18896, -0.022472, 0.045801, 0.040802, 0.080475, -0.0050747, -0.02135, -0.049503, 1.1642, 0.60823, 0.74642, 0.40899, -0.062986, 1.0078, 0.17467, 1.7201, 0.57385, 0.98774, -0.075809, -0.16454, 0.2772, 0.079737, -0.15566, -0.076556, -0.13049, 0.015378, -0.034579, -0.022909, 0.13255, -0.36735, -0.030313, -0.16383, 0.09493, 0.0099994, 0.050335, 0.20474},
          {1.1328, 0.87761, 0.78766, 1.4227, 0.88128, -0.024605, 0.3766, 1.3773, 0.66674, 1.0117, 1.0945, 0.70967, 0.25257, 0.36167, 1.371, 0.86987, 0.79092, -1.0995, 0.35513, -0.14408, 0.050797, 0.44102, 1.8475, 1.5828, 0.2642, 0.89874, 0.023452, -0.81995, 0.070544, -0.16158, -0.21231, -0.21137, -0.079742, 0.12608, 1.5138, -0.18877, 0.15955, -0.14785, -0.16356, -0.036481, -0.011957, 0.70313, 2.491, 1.326, 1.3011, 1.0572, 0.25924, 0.17467, 2.8596, 2.0835, 0.54478, 2.0246, 0.32583, 0.48306, 0.10881, 1.4284, 0.23666, 0.03358, 0.25156, -0.17627, 0.058012, -0.0454, 0.11436, 0.7081, 0.11881, 0.13698, 0.15322, -0.074524, -0.032798, -0.12537},
          {3.145, 4.3208, 6.3785, 8.4147, 4.0822, -0.79033, 3.8702, 2.1146, 2.4567, 4.4304, 6.2583, 5.6134, 1.9351, 5.3624, 139.35, 34.373, 27.507, 30.104, 8.5053, -4.8869, -0.055537, 164.75, 29.548, 29.136, 43.9, 14.244, 0.37739, 6.294, 0.0042325, -4.5431, 1.2401, -0.34818, -0.94507, -0.82314, 0.064176, 2.2244, -2.888, -1.2612, 1.2018, 0.55724, -0.26421, 1.5192, 150.19, 43.102, 37.944, 26.817, 10.609, 1.7201, 2.0835, 196.63, 30.926, 31.248, 25.761, 5.49, 1.1518, 0.58781, 12.64, -1.1697, 0.98016, 1.2365, -1.1708, -0.22527, -2.1277, 12.614, 3.7489, 1.0235, 2.432, -1.4864, -0.22098, -1.7842},
          {4.6289, 3.6063, 3.5328, 6.0715, 2.9067, 0.7377, 3.0548, 8.3226, 3.5658, 2.2584, 5.4633, 3.0606, 1.889, 3.6347, 25.473, 27.458, 34.217, 28.41, 8.6549, 0.26785, 0.94569, 25.803, 16.668, 31.308, 20.827, 9.1829, 0.68829, -0.49673, 0.41538, -0.88026, -1.2545, -0.45586, -0.68788, -0.26505, -0.14452, -0.062889, -1.0889, -1.0624, 0.45762, -0.17175, -0.45019, 0.48329, 36.961, 18.04, 21.678, 14.488, 2.9851, 0.57385, 0.54478, 30.926, 26.463, 16.933, 10.813, 1.9789, -0.064518, -0.65776, 9.3746, 1.212, 2.9775, 2.4123, 0.11834, 0.010825, -0.1802, 8.1591, 4.6641, 2.2221, 1.5782, -0.54666, 0.07932, -0.56279},
          {3.0738, 3.1656, 1.7568, 3.1313, 0.96611, 0.10567, 2.3384, 2.9445, 2.3375, 2.1174, 3.663, 1.7785, 1.1585, 2.8217, 13.444, 29.87, 35.259, 34.501, 10.088, 0.01711, -0.060301, 14.004, 16.38, 33.713, 21.451, 12.146, -0.80909, -3.3697, 1.0329, -0.96248, -1.4714, -1.135, -0.5317, -0.13451, 0.95338, -0.76805, -1.5599, -0.8707, 0.026255, -0.10247, -0.18478, 1.1476, 37.282, 19.053, 20.516, 13.755, 4.8899, 0.98774, 2.0246, 31.248, 16.933, 30.879, 11.268, 2.676, 0.63611, 0.18156, 7.9323, 1.9352, 2.6577, 2.2152, 0.091243, -0.052012, 0.29261, 5.8704, 3.277, 1.9881, 1.6582, -0.57629, -0.065006, -0.38601},
          {3.9791, 4.0424, 2.5917, 4.5158, 1.7963, 0.46162, 2.8135, 2.7121, 2.1161, 2.3189, 3.677, 2.5965, 1.9888, 3.2931, 25.607, 22.991, 30.347, 30.901, 7.6286, 1.167, -0.54685, 27.875, 14.888, 26.713, 27.663, 8.5663, 2.7998, -0.90142, -0.93576, -1.2345, -0.76851, -0.33296, -0.46554, -0.20485, 0.15479, -0.13707, -1.997, -0.88354, 1.7578, 0.012013, -0.6033, 0.89665, 32.553, 14.211, 13.324, 22.539, 3.1477, -0.075809, 0.32583, 25.761, 10.813, 11.268, 30.362, 0.959, 0.56671, 0.50907, 9.3142, 1.0715, 2.974, 1.7439, 0.071678, -0.31109, 0.44895, 6.5111, 4.1118, 2.2125, 1.6059, -0.72792, -0.17787, -0.12975},
          {-0.35038, 0.36072, 0.76227, 0.58304, 1.2178, 0.10413, 0.37234, -1.0674, 0.55328, 0.74167, 0.96268, 0.25344, 0.23168, 0.9365, 4.1987, 3.5965, 7.5237, 2.4261, 2.0785, -0.37341, -0.066057, 2.8554, 3.7571, 4.147, 1.7393, 2.3449, 0.65074, -0.21458, -0.2698, -0.65389, 0.090389, -0.19472, 0.31178, -0.13079, 0.16355, 0.25904, -0.64429, 0.090746, 0.25946, 0.10246, -0.019935, 0.46648, 3.8441, 3.1685, 2.0793, 1.7702, 3.3518, -0.16454, 0.48306, 5.49, 1.9789, 2.676, 0.959, 6.301, 0.15384, 0.71436, 0.40827, 0.030307, 0.41126, 0.24358, -0.072004, 0.060912, -0.11078, -0.0076855, 0.075308, 0.41243, 0.084728, 0.10542, -0.11954, -0.3819},
          {0.08308, 0.38937, 0.25885, 0.10837, -0.3998, 0.01472, -0.04487, -0.14569, 0.18469, -0.054678, -0.23419, 0.046462, 0.034338, -0.28769, 1.7489, 0.3352, 0.21015, -0.91021, -0.20736, 0.039688, 0.22893, 2.3725, 1.7151, 0.40398, -1.1591, -0.30726, 0.052256, -0.42224, -0.069232, -0.016837, -0.018768, -0.021596, 0.073204, 0.10542, 0.049332, -0.25229, 0.174, 0.034433, 0.19606, 0.037313, 0.1354, -0.047204, 0.86619, 0.79138, 0.47588, 0.72404, 0.28802, 0.2772, 0.10881, 1.1518, -0.064518, 0.63611, 0.56671, 0.15384, 0.821, -0.10031, 0.13803, 0.10873, -0.016054, 0.13047, -0.0062625, -0.0013257, -0.072754, -0.34994, -0.05189, -0.12854, 0.065618, -0.0741, 0.021696, -0.017877},
          {-0.59277, -0.40417, -0.5197, -0.82442, -0.010887, -0.043628, -0.21543, -1.4281, -0.7181, -0.63661, -0.64859, -0.14061, -0.0038304, -0.26655, -0.51562, 0.42148, -1.3381, -0.062126, 1.5316, -0.62037, -0.81459, 2.7038, 0.097655, 0.31901, 0.81388, 0.39974, 2.1302, 5.1888, 0.0705, -0.18657, -0.09086, -0.45792, 0.04103, -0.23589, 1.0088, 0.16727, -0.15865, -0.083657, -0.14914, -0.038864, -0.1478, 0.4069, -1.2282, 0.31402, -0.93229, -0.28525, -0.37535, 0.079737, 1.4284, 0.58781, -0.65776, 0.18156, 0.50907, 0.71436, -0.10031, 5.8031, 0.53741, -0.07518, 0.10585, 0.14348, 0.11102, 0.045871, 0.38792, 0.92506, -0.23979, -0.012505, 0.22315, 0.34107, -0.015032, 0.52797},
          {2.9314, 4.6683, 3.8697, 3.3184, 0.74091, 0.1631, 1.1603, 0.22639, 1.5505, 1.2762, 2.4029, 1.6124, 1.1165, 1.3363, 44.845, 15.092, 10.835, 7.8628, 5.5184, 0.29185, -1.1069, 44.417, 16.398, 10.304, 7.3814, 3.9523, -0.43459, 0.20002, -0.0036851, 0.41066, -0.61999, -0.20787, 0.079697, 0.15238, -0.21547, 0.070393, -1.7053, -0.61687, 0.11023, 0.2465, -0.25401, 0.5291, 20.004, 9.8551, 8.9934, 7.5573, 3.7895, -0.15566, 0.23666, 12.64, 9.3746, 7.9323, 9.3142, 0.40827, 0.13803, 0.53741, 52.348, 8.573, 10.629, 6.6602, 1.5807, 0.5019, 3.0632, 33.701, 8.4649, 7.1736, 6.1623, 1.6314, 0.26709, 2.5077},
          {0.85789, 1.6053, 2.0919, 1.6092, 0.57659, -0.068094, 0.4778, 0.70909, 0.54413, 1.1637, 1.0165, 1.0485, 0.3405, -0.016717, 1.3363, 4.5219, 3.3516, 1.2458, 1.5489, -0.21576, -0.074336, -3.4115, 3.2601, 4.231, 0.20438, 0.83528, -0.34596, -0.039729, 0.056971, 0.18925, -0.30131, 0.060858, 0.10544, -0.10055, -0.28281, -0.31684, -0.10856, 0.019292, 0.095237, 0.015836, -0.041011, 0.069753, -0.3638, -0.022559, 2.7225, 0.915, 0.89017, -0.076556, 0.03358, -1.1697, 1.212, 1.9352, 1.0715, 0.030307, 0.10873, -0.07518, 8.573, 4.0214, 2.1341, 1.3233, 0.49962, 0.01484, 0.59638, 6.258, 1.5577, 1.4229, 1.3315, 0.35576, 0.060371, 0.58519},
          {0.95815, 2.0176, 0.58781, 0.80479, 0.39618, -0.068835, 1.004, -0.8581, 1.0703, 0.81637, 0.50394, 0.68226, 0.56394, 0.7429, 3.0063, 6.1384, 7.1291, 1.5679, 2.0437, -0.5657, -0.29141, 3.9503, 5.8141, 7.8788, 0.4163, 0.97734, -0.23287, -0.74974, -0.059321, 0.25505, -0.24967, -0.095408, -0.019683, 0.14865, 0.47489, -0.14659, -0.14212, -0.26775, 0.4093, 0.086386, -0.06355, 0.22404, 1.0022, 3.2892, 4.0743, 1.6294, 1.0944, -0.13049, 0.25156, 0.98016, 2.9775, 2.6577, 2.974, 0.41126, -0.016054, 0.10585, 10.629, 2.1341, 5.5443, 1.7801, 0.4606, -0.023469, 0.89508, 8.6848, 2.7525, 2.2164, 2.2636, 0.13082, 0.060905, 0.65843},
          {0.80839, 0.58621, 0.53837, 0.50092, 0.59183, 0.001552, 0.58676, 0.07034, 0.50944, 0.39752, 0.24659, 0.3451, 0.6285, 1.0894, 11.812, 5.0727, 9.7984, 5.7478, 2.8754, -0.1644, -0.3818, 9.8717, 4.3172, 5.1644, 4.4399, 3.9277, 0.31982, -0.9656, 0.16453, -0.32279, 0.11554, 0.039033, -0.14025, -0.13517, -0.43049, 0.61087, -0.87099, -0.17153, 0.2125, 0.10785, -0.098918, -0.16793, 0.62394, 2.4395, 1.9917, 1.4229, 0.75476, 0.015378, -0.17627, 1.2365, 2.4123, 2.2152, 1.7439, 0.24358, 0.13047, 0.14348, 6.6602, 1.3233, 1.7801, 4.035, 0.20251, 0.06754, 0.34855, 5.5754, 1.5116, 1.401, 1.6236, 0.2484, -0.086651, 0.0076185},
          {-0.22872, 0.16382, -0.0085377, -0.038143, -0.21966, -0.10399, -0.051547, -0.25526, -0.23432, -0.085323, -0.21119, -0.016216, -0.15373, -0.067804, -3.6055, -0.1724, -0.87667, -0.29824, -0.19249, -0.12433, -0.010433, -3.2168, 0.58883, 0.13636, -0.88233, -0.017176, 0.16628, -0.21937, -0.1107, 0.11044, -0.093306, 0.082282, 0.014688, 0.020398, -0.0076041, -0.1074, 0.030755, -0.080803, 0.0067498, -0.012111, -0.020208, 0.017424, -0.99638, 0.056001, 0.31058, 0.22026, 0.092543, -0.034579, 0.058012, -1.1708, 0.11834, 0.091243, 0.071678, -0.072004, -0.0062625, 0.11102, 1.5807, 0.49962, 0.4606, 0.20251, 0.52694, 0.014445, 0.15378, 1.2289, 0.21433, 0.34274, 0.34238, 0.047618, 0.019479, 0.068346},
          {-0.20368, -0.22106, -0.15146, -0.23148, -0.019598, -0.027148, -0.12327, -0.031293, -0.089878, -0.18923, -0.07656, -0.19794, -0.071301, -0.15297, 1.526, -0.12908, -0.15276, -0.076648, -0.26288, 0.019729, -0.053096, 0.96182, 0.11353, -0.41611, 0.194, -0.031269, -0.024492, 0.088207, 0.053264, 0.0084046, 0.022901, 0.041747, 0.011932, 0.019598, -0.10077, 0.064936, 0.0029116, -0.016491, 0.0030017, 0.016911, 0.026565, -0.066399, 0.10472, 0.0082911, -0.29535, -0.21718, 0.067136, -0.022909, -0.0454, -0.22527, 0.010825, -0.052012, -0.31109, 0.060912, -0.0013257, 0.045871, 0.5019, 0.01484, -0.023469, 0.06754, 0.014445, 0.1434, 0.059692, 0.44744, -0.079508, 0.067325, -0.040732, 0.072969, 0.013289, 0.077849},
          {0.37534, 0.64897, 0.41498, 0.70459, 0.19665, 0.15756, 0.16737, -0.69912, 0.18225, 0.48341, 0.5889, 0.35776, 0.081612, 0.11619, -3.0366, -0.39814, -0.79979, -1.3877, -0.32294, 0.21677, 0.2642, -3.918, 0.2141, -0.27699, -1.4806, -0.67145, 0.34964, 0.13618, 0.10721, 0.1446, -0.022815, -0.032146, -0.0053709, 0.13598, 0.1266, 0.034422, 0.18354, 0.12339, 0.17346, 0.022922, 0.032674, 0.26674, -1.317, -0.33872, -0.49521, 0.55395, 0.37405, 0.13255, 0.11436, -2.1277, -0.1802, 0.29261, 0.44895, -0.11078, -0.072754, 0.38792, 3.0632, 0.59638, 0.89508, 0.34855, 0.15378, 0.059692, 1.3476, 2.4489, 0.27766, 0.39088, 0.54517, 0.14952, 0.068621, 0.71377},
          {0.036379, 2.6099, 0.20229, 0.83828, -0.26736, -0.20583, 1.9167, -0.94021, 1.0795, -0.30565, -0.86287, 0.65099, 0.65917, 1.4223, 32.404, 11.058, 13.373, 5.7821, 5.8569, -1.6544, 0.24077, 37.7, 14.642, 13.433, 7.8418, 8.1304, 0.8029, 1.5707, -0.07054, 1.0136, -0.47356, 0.66434, -0.24886, 0.14686, 0.026931, 0.43365, -0.9967, -0.51829, 0.46041, 0.39349, -0.1033, -0.1858, 12.415, 6.2341, 8.1738, 6.4563, 3.236, -0.36735, 0.7081, 12.614, 8.1591, 5.8704, 6.5111, -0.0076855, -0.34994, 0.92506, 33.701, 6.258, 8.6848, 5.5754, 1.2289, 0.44744, 2.4489, 39.387, 7.6835, 6.6252, 5.8317, 0.94405, 0.44023, 2.0087},
          {0.91204, 1.373, 1.2167, 0.86789, 0.71993, 0.065526, 1.1645, 0.4218, 0.43803, 0.73283, 1.0692, 0.90384, 0.34453, 1.4237, 7.2897, 6.1923, 7.81, 4.7772, 1.2781, -0.70868, 0.28052, 8.9714, 4.3111, 9.2863, 2.5241, 2.2927, 0.051083, -0.6525, -0.029699, 0.15157, -0.13041, -0.050564, -0.071376, 0.075568, 0.34774, -0.22469, -0.51281, -0.50627, 0.13943, -0.021292, -0.17055, -0.23774, 5.4838, 4.119, 5.4536, 3.0243, 0.48326, -0.030313, 0.11881, 3.7489, 4.6641, 3.277, 4.1118, 0.075308, -0.05189, -0.23979, 8.4649, 1.5577, 2.7525, 1.5116, 0.21433, -0.079508, 0.27766, 7.6835, 4.7667, 1.7167, 1.7552, -0.1243, 0.087073, 0.11164},
          {-0.12344, 0.56104, -0.25365, -0.053676, 0.11782, -0.045689, 0.8653, -0.33178, 0.57462, 0.035321, 0.017292, 0.39469, 0.30854, 0.47888, 7.0753, 5.4562, 7.9161, 3.8176, 2.5148, -0.38385, -0.26422, 6.7782, 4.8, 6.6872, 3.6985, 4.0833, 0.1494, 0.31853, -0.13573, 0.03518, -0.014645, 0.1075, 0.0055875, 0.042214, -0.1601, 0.12598, -0.47502, -0.17746, 0.12584, 0.08011, -0.10093, 0.04741, 1.7825, 2.0454, 2.5615, 1.666, 0.56786, -0.16383, 0.13698, 1.0235, 2.2221, 1.9881, 2.2125, 0.41243, -0.12854, -0.012505, 7.1736, 1.4229, 2.2164, 1.401, 0.34274, 0.067325, 0.39088, 6.6252, 1.7167, 3.1713, 1.3502, 0.28197, 0.041063, 0.31349},
          {1.1105, 1.1669, 0.38554, 0.49502, 0.082895, 0.020638, 0.70675, 0.42097, 0.69836, 0.68757, 0.61971, 0.46885, 0.33984, 0.8269, 3.4708, 3.2408, 4.1348, 2.1149, -0.54332, -0.75045, -0.036451, 3.1358, 1.1877, 6.2156, 0.9328, 0.38418, -0.24586, -0.43034, 0.33231, 0.13793, -0.060077, 0.041681, -0.087888, 0.052923, 0.19682, 0.27622, -0.32232, -0.25011, 0.11644, 0.033139, -0.034697, 0.11323, 1.7168, 2.5459, 2.7954, 0.75435, 0.71756, 0.09493, 0.15322, 2.432, 1.5782, 1.6582, 1.6059, 0.084728, 0.065618, 0.22315, 6.1623, 1.3315, 2.2636, 1.6236, 0.34238, -0.040732, 0.54517, 5.8317, 1.7552, 1.3502, 3.1011, -0.016799, 0.04443, 0.22082},
          {-0.43384, -0.27408, 0.059269, -0.25827, 0.43587, -0.098948, -0.42694, -0.7539, -0.4085, -0.32261, -0.050324, -0.28412, -0.12766, 0.041538, 2.4642, -0.031495, -0.25654, -0.83062, 2.2139, 0.087234, -0.26628, 1.5019, -0.43977, -0.9473, 0.81216, 2.0864, 0.26358, 1.4358, 0.23436, 0.13685, 0.20323, 0.086796, 0.12307, 0.054273, -0.048397, 0.33582, -0.14572, 0.12187, -0.18797, 0.049773, 0.039596, 0.12737, -1.9218, -0.65201, -0.5057, -0.38948, 0.11273, 0.0099994, -0.074524, -1.4864, -0.54666, -0.57629, -0.72792, 0.10542, -0.0741, 0.34107, 1.6314, 0.35576, 0.13082, 0.2484, 0.047618, 0.072969, 0.14952, 0.94405, -0.1243, 0.28197, -0.016799, 1.0901, -0.055188, 0.27448},
          {-0.059015, 0.13183, 0.13656, 0.043533, -0.14995, -0.0056201, -0.028331, -0.17753, -0.035382, 0.010085, 0.017878, 0.09792, -0.028528, -0.13146, -2.3018, -0.29887, -1.4514, -0.9444, -0.39336, -0.068867, 0.08914, -1.4817, -0.24713, -0.42988, -1.197, -0.35178, -0.027649, 0.22148, 0.032775, 0.15121, -0.017683, 0.062101, 0.012381, 0.053309, -0.016816, -0.098258, 0.146, 0.033368, 0.028573, -0.01184, 0.029079, -0.010258, -0.11177, -0.042541, 0.10977, -0.18632, -0.0045016, 0.050335, -0.032798, -0.22098, 0.07932, -0.065006, -0.17787, -0.11954, 0.021696, -0.015032, 0.26709, 0.060371, 0.060905, -0.086651, 0.019479, 0.013289, 0.068621, 0.44023, 0.087073, 0.041063, 0.04443, -0.055188, 0.13273, 0.091095},
          {0.021492, 0.016357, -0.12428, -0.013689, -0.32898, 0.048339, -0.2513, -1.2384, -0.531, -0.05502, -0.2399, 0.04186, -0.0045298, -0.22882, -2.8429, -0.5134, -2.635, -3.256, -1.0781, 0.35117, 0.19393, -1.8005, 0.49724, -1.1595, -2.9374, -1.3931, 0.54486, 0.77249, 0.10114, 0.22571, 0.10174, 0.017415, 0.053724, 0.059132, 0.11669, -0.062539, -0.021509, 0.08295, -0.019312, -0.013878, 0.058839, -0.047376, -3.0123, -1.3777, -0.85864, -0.41618, -0.050603, 0.20474, -0.12537, -1.7842, -0.56279, -0.38601, -0.12975, -0.3819, -0.017877, 0.52797, 2.5077, 0.58519, 0.65843, 0.0076185, 0.068346, 0.077849, 0.71377, 2.0087, 0.11164, 0.31349, 0.22082, 0.27448, 0.091095, 1.5519},
        };

        set_covariance(BKGCOV);

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2OSLEP_for_chargino_36invfb)



    //
    // Derived analysis class for the stop SRs
    //
    class Analysis_CMS_13TeV_2OSLEP_for_stop_36invfb : public Analysis_CMS_13TeV_2OSLEP_chargino_stop_36invfb {

    public:
      Analysis_CMS_13TeV_2OSLEP_for_stop_36invfb() {
        set_analysis_name("CMS_13TeV_2OSLEP_for_stop_36invfb");
      }

      virtual void collect_results() {
        static const size_t SR_size_cov = 84;

        // Observed event counts
        static const double OBSNUM[SR_size_cov] = {\
            3534, 1494, 1938, 2068, 879, 111, 15, \
            3003, 1266, 1674, 1671, 798, 85, 16, \
            1045, 357, 412, 389, 111, 11, 1, \
            900, 315, 343, 325, 86, 13, 11, \
            133, 44, 36, 26, 2, 1, 0, \
            123, 27, 28, 38, 4, 1, 1, \
            1523, 556, 765, 769, 311, 53, 22, \
            1367, 539, 648, 692, 301, 63, 59, \
            521, 166, 160, 182, 45, 7, 16, \
            501, 135, 177, 128, 36, 9, 32,\
            100, 27, 22, 12, 3, 0, 1, \
            92, 26, 17, 12, 1, 1, 2 \
        };
        // Background estimates
        static const double BKGNUM[SR_size_cov] = {\
            3525, 1505, 1958, 2049, 897, 108.4, 13.4,\
            2979, 1277, 1644, 1712, 762, 91.9, 18.1, \
            1036, 363, 415, 377, 105.1, 12.3, 5.02, \
            888, 319, 363, 323, 90.5, 10.8, 7.43, \
            152.1, 35.5, 32.3, 25, 4.67, 0.41, 0.41, \
            129.6, 29.6, 27.8, 22.2, 3.71, 0.47, 0.71, \
            1542, 588, 756, 771, 338.3, 50.6, 21, \
            1350, 526, 656, 670, 289.2, 57.9, 61.8, \
            545, 164.3, 173.2, 165.1, 44.8, 7.1, 15.5, \
            487, 140.7, 161.9, 134.5, 39.6, 8.1, 30.6, \
            103.9, 21.3, 22.2, 15.4, 3.51, 0.53, 0.53,\
            91.5, 20.1, 16.5, 13.7, 3.14, 0.78, 1.63 \
        };
        // Background uncertainties, same-flavor signal regions
        static const double BKGERR[SR_size_cov] = {\
            80, 31, 42, 46, 22, 7.3, 2.2, \
            68, 30, 35, 37, 19, 6.1, 2.1, \
            37, 13, 14, 14, 6.5, 2, 0.82, \
            30, 12, 14, 13, 5.5, 1.5, 0.98,\
            9.9, 2.7, 2.3, 2.2, 0.77, 0.38, 0.26, \
            8.9, 2.1, 2.1, 1.9, 0.57, 0.42, 0.38, \
            33, 13, 15, 19, 9.3, 3.8, 3.8, \
            33, 13, 15, 17, 7.6, 4.2, 5.8, \
            18, 7.3, 6.2, 6.8, 3.1, 1.4, 3, \
            16, 5.5, 5.9, 6.2, 2.7, 1.1, 3,\
            6.8, 1.9, 2.1, 1.6, 0.6, 0.21, 0.34, \
            6.1, 1.8, 1.4, 1.4, 0.58, 0.36, 0.42\
        };

        for (size_t ibin = 0; ibin < SR_size_cov; ++ibin) {
          stringstream ss; ss << "sr-" << ibin;
          add_result(SignalRegionData(ss.str(), OBSNUM[ibin], {_srnums_stop[ibin],  0.}, {BKGNUM[ibin], BKGERR[ibin]}));
        }

        // Covariance matrix
        static const vector< vector<double> > BKGCOV = {
          {6875.0, 2377.1, 3179.8, 2837.9, 733.27, -26.073, 16.145, 5545.5, 2171.9, 2506.6, 2068.9, 589.85, -34.232, 16.026, 2674.2, 845.18, 921.25, 822.71, 223.5, 22.604, -1.8677, 2128.7, 739.49, 824.29, 751.1, 124.89, 12.545, -1.8774, 519.98, 116.99, 102.17, 63.98, 4.8098, -10.741, -4.3299, 453.91, 79.243, 69.709, 46.518, 0.49875, -16.329, -10.927, 1687.3, 611.98, 821.71, 672.55, 94.67, -36.091, 13.612, 1427.4, 398.08, 735.36, 590.4, 71.951, 11.927, -14.458, 620.87, 360.06, 290.08, 250.94, 61.003, 10.469, 37.189, 599.35, 229.85, 199.88, 243.85, 41.32, 10.523, 17.981, 143.19, 6.2269, 35.119, 42.799, 5.2863, -4.6229, -9.6257, 133.28, 37.996, 18.791, 26.163, -0.34789, -11.301, -13.304},
          {2377.1, 1037.3, 1301.0, 1133.4, 301.95, 1.9636, 1.9325, 2057.7, 923.63, 1074.8, 846.92, 262.64, -0.90515, 5.3446, 936.29, 342.69, 376.5, 323.2, 77.04, 4.7191, -2.2258, 771.52, 309.78, 348.41, 302.87, 49.105, 4.5238, -1.6665, 192.84, 43.528, 40.798, 30.009, 1.2417, -3.9334, -1.7135, 167.79, 28.75, 27.879, 21.405, 0.29302, -6.2219, -4.0123, 561.85, 257.27, 327.43, 280.2, 29.358, -13.482, 7.3217, 474.28, 186.98, 326.41, 244.36, 34.835, -0.65904, -4.6335, 214.43, 138.28, 118.62, 105.94, 18.631, 4.0438, 10.772, 206.82, 95.52, 98.273, 94.765, 13.923, 4.1986, 4.6787, 53.682, 7.6131, 14.443, 18.063, 3.4481, -1.7142, -3.7851, 51.675, 11.802, 7.9037, 12.996, 0.94846, -3.0998, -5.0949},
          {3179.8, 1301.0, 1914.3, 1568.1, 443.31, 3.0021, 2.3725, 2706.2, 1224.0, 1451.5, 1171.4, 377.53, 0.10504, 5.6596, 1268.8, 475.58, 525.57, 442.96, 111.73, 8.9132, -3.1025, 1001.9, 425.13, 485.24, 397.96, 58.967, 8.7937, -2.5636, 261.73, 59.385, 55.037, 40.051, 1.4739, -5.8213, -2.7571, 234.94, 34.735, 37.838, 27.237, -0.62644, -8.9891, -6.5136, 736.35, 326.62, 437.93, 362.07, 29.713, -12.896, 14.917, 650.9, 220.65, 421.58, 304.45, 41.785, 11.141, 3.1123, 293.18, 198.55, 171.6, 140.02, 29.881, 5.9723, 17.479, 301.95, 128.37, 129.65, 126.06, 15.705, 5.1346, 0.63882, 68.404, 5.3544, 19.098, 25.934, 3.8116, -2.5727, -5.2999, 64.367, 15.312, 9.8362, 17.723, -0.72862, -5.4621, -7.5422},
          {2837.9, 1133.4, 1568.1, 2229.2, 423.8, 18.639, 13.863, 2411.9, 1043.4, 1212.4, 1692.4, 362.35, 13.265, 10.628, 1201.4, 425.43, 476.43, 411.76, 111.93, 11.651, 1.0733, 992.26, 382.27, 435.83, 370.99, 58.093, 10.423, -0.07352, 267.86, 56.569, 55.143, 33.517, 2.7691, -6.1201, -2.3862, 232.19, 33.544, 33.755, 25.411, 0.83701, -8.6285, -5.3105, 704.82, 289.58, 397.59, 563.45, 42.152, 0.52939, 18.947, 608.91, 220.83, 384.33, 472.31, 48.488, 18.147, -2.8368, 227.12, 173.96, 129.36, 110.52, 25.177, 10.39, 14.616, 213.69, 117.65, 102.34, 129.94, 23.635, 4.0268, -3.8269, 71.344, 8.1656, 21.546, 24.793, 5.6235, -2.359, -4.5973, 62.101, 17.339, 9.4796, 16.324, 1.0705, -5.4772, -7.5714},
          {733.27, 301.95, 443.31, 423.8, 491.98, 16.476, 1.7607, 575.31, 244.22, 298.46, 321.92, 385.05, 12.104, 9.0822, 264.26, 98.803, 111.13, 107.94, 37.819, 11.792, -0.50501, 212.17, 72.668, 102.12, 80.966, 19.256, 7.0408, -1.1289, 38.915, 10.302, 8.6825, 4.2637, 0.41795, -1.4276, -0.062549, 39.213, 3.5949, 7.2222, -1.7682, -0.5108, -1.7529, -0.77104, 208.13, 80.548, 81.414, 99.6, 102.64, 9.1283, 0.14761, 189.91, 64.982, 75.618, 65.796, 95.145, 21.429, 14.992, 127.84, 36.482, 44.524, 30.903, 6.4452, 3.5308, 2.5287, 54.388, 29.749, 19.79, 28.767, 2.0666, 5.0371, 4.3261, 17.922, 2.4708, 3.6609, 7.1443, 0.45782, -0.051534, -0.61116, 18.165, 1.2876, 1.4168, 2.4551, -1.0232, -0.73059, -0.34327},
          {-26.073, 1.9636, 3.0021, 18.639, 16.476, 52.951, 1.3261, -22.282, -1.8421, -5.8718, 14.679, 15.016, 40.896, 1.9452, -21.529, -0.69736, 0.86738, 8.5091, 0.21168, 0.19176, 0.14924, -10.512, -6.9398, -3.3981, 8.2094, 2.5704, -0.23476, 0.78763, -7.6937, -0.99854, -1.0256, 1.1852, -0.16071, 0.75163, 0.13102, -6.7634, -1.1926, 0.45039, 0.24247, -0.48635, 0.33625, 0.27946, -8.2705, 5.5661, 1.6232, 2.3096, 8.0253, 15.496, -3.8482, -1.8842, 2.8432, 0.28376, -3.8187, 9.0591, 12.702, 0.18724, 2.25, -5.901, 2.0914, 3.217, -3.1405, 0.50466, -0.82002, -10.134, -3.8521, -2.0038, -1.2375, -2.8201, 1.2213, 0.24996, 5.0165, 2.2836, -0.43902, 0.5769, 0.16264, 0.10145, 0.34921, 1.9407, -0.33875, 0.23405, 1.2497, 0.092468, 0.4824, 0.2535},
          {16.145, 1.9325, 2.3725, 13.863, 1.7607, 1.3261, 5.0221, 10.632, 0.63855, 2.0545, 8.7119, -0.60735, 0.42528, 2.8241, 4.4414, 0.1205, -0.26243, 2.4042, 1.0916, 0.44419, 0.27126, 3.9378, 0.56026, -0.29439, 2.1554, 0.91023, 0.14932, -0.1122, 0.59935, -0.10616, 0.054331, 0.17255, 0.0067127, -0.0462, -0.031351, -0.65209, 0.20392, -0.40135, -0.0011667, 0.094347, -0.00056757, 0.016592, 8.4573, 4.0996, 4.316, 6.8712, 0.92358, 1.0202, 1.4329, 4.6937, 1.5879, 3.1108, 3.2228, 0.40946, 0.18555, -1.1904, -0.67058, 0.97196, -0.82784, -0.30503, 0.10064, 0.080839, -0.69079, -4.2353, -0.16146, -1.0653, 0.12601, 0.76592, 0.11828, -0.55475, 0.31164, 0.52003, -0.026346, 0.45048, 0.015148, 0.0041496, 0.032785, 0.47388, 0.13898, 0.21479, -0.34185, 0.020948, -0.022716, 0.069002},
          {5545.5, 2057.7, 2706.2, 2411.9, 575.31, -22.282, 10.632, 5036.7, 1993.4, 2273.4, 1846.5, 513.36, -22.761, 16.538, 2201.5, 721.14, 776.63, 670.29, 163.8, 11.947, -1.9519, 1862.5, 653.4, 740.74, 643.58, 98.426, 8.3152, -0.64445, 452.97, 101.38, 88.349, 58.19, 3.7695, -10.03, -3.6993, 403.05, 68.73, 65.109, 46.006, 0.20085, -14.33, -9.3423, 1409.6, 531.28, 691.29, 578.59, 48.69, -41.474, 7.8465, 1229.2, 389.8, 691.82, 558.29, 55.798, 0.83294, -2.9666, 521.66, 321.05, 243.0, 207.31, 40.814, 2.9653, 43.988, 529.09, 217.8, 199.47, 210.85, 33.17, 10.532, 22.817, 112.85, 9.3202, 32.119, 35.07, 4.7105, -3.7044, -8.6526, 117.48, 33.107, 18.814, 22.959, 0.92148, -8.5398, -10.899},
          {2171.9, 923.63, 1224.0, 1043.4, 244.22, -1.8421, 0.63855, 1993.4, 975.55, 1052.2, 799.65, 238.92, -2.7605, 6.2283, 870.88, 328.42, 355.92, 294.65, 64.917, 2.3811, -2.2615, 742.51, 308.39, 344.5, 281.88, 40.376, 5.0515, -0.78898, 190.34, 44.632, 40.239, 29.256, -0.44915, -4.6019, -2.047, 172.31, 26.953, 28.024, 23.948, -0.24723, -6.5399, -4.0775, 475.53, 231.02, 290.19, 240.47, 9.3351, -15.815, 9.3885, 431.94, 179.73, 330.47, 240.77, 18.046, -1.9319, -3.0465, 178.34, 143.04, 108.02, 96.588, 13.644, 3.0402, 14.67, 203.19, 98.602, 98.918, 93.495, 10.421, 3.8335, 4.7764, 47.423, 7.8132, 14.746, 17.266, 2.6818, -1.8566, -3.6172, 51.698, 13.203, 6.5307, 13.055, 0.83693, -3.5092, -4.8197},
          {2506.6, 1074.8, 1451.5, 1212.4, 298.46, -5.8718, 2.0545, 2273.4, 1052.2, 1339.7, 958.16, 289.09, -8.2164, 4.8513, 984.69, 361.38, 404.16, 342.04, 71.781, 2.2809, -2.2269, 834.2, 348.56, 386.45, 326.37, 48.579, 4.84, -0.86443, 218.54, 51.377, 46.358, 34.861, -0.40536, -5.2539, -2.5112, 197.14, 34.325, 31.282, 28.713, -0.1451, -7.3807, -5.2407, 563.72, 271.66, 344.94, 273.78, 4.6304, -20.167, 11.492, 484.96, 206.42, 372.98, 262.66, 24.605, -3.5522, -1.9771, 197.68, 149.32, 124.48, 109.82, 20.915, 3.4821, 18.151, 234.74, 109.27, 115.79, 103.22, 15.858, 3.8022, 5.4672, 49.705, 7.8433, 12.007, 18.814, 3.6135, -2.0796, -4.2041, 48.819, 12.428, 9.4889, 12.764, 0.76508, -4.1136, -6.2523},
          {2068.9, 846.92, 1171.4, 1692.4, 321.92, 14.679, 8.7119, 1846.5, 799.65, 958.16, 1458.6, 301.19, 12.083, 3.6195, 916.43, 322.94, 357.37, 315.69, 73.907, 9.7415, 1.455, 786.96, 293.47, 348.37, 293.37, 39.298, 9.5305, -0.75405, 198.47, 40.553, 40.675, 24.559, 0.18442, -4.4402, -1.5689, 175.25, 23.732, 26.711, 19.154, -0.9781, -5.96, -3.9582, 537.79, 211.27, 279.66, 451.02, 40.691, 0.23896, 11.098, 533.87, 194.82, 308.51, 402.12, 47.363, 10.771, -9.934, 168.43, 129.1, 91.852, 76.678, 15.677, 8.4363, 11.986, 174.11, 97.423, 86.873, 101.11, 11.912, 3.5601, -1.8995, 55.338, 6.6239, 15.337, 18.54, 3.6111, -1.6762, -2.9758, 53.414, 15.201, 6.8244, 13.073, 0.054607, -3.9984, -5.4826},
          {589.85, 262.64, 377.53, 362.35, 385.05, 15.016, -0.60735, 513.36, 238.92, 289.09, 301.19, 375.66, 11.711, 7.181, 223.38, 73.584, 86.021, 84.242, 20.104, 7.3233, -0.68929, 187.13, 64.268, 85.28, 72.441, 10.685, 4.9719, -0.72055, 41.759, 11.295, 9.0929, 5.6662, -0.45779, -1.6479, -0.16117, 42.031, 5.4973, 6.8503, 2.2077, -0.72381, -1.8599, -0.82325, 144.07, 66.888, 59.498, 72.802, 74.94, 5.9917, -1.4138, 149.73, 66.24, 64.632, 56.249, 81.288, 15.558, 11.243, 101.03, 28.448, 35.807, 24.465, 0.45378, 2.2434, 3.2774, 50.526, 28.125, 24.488, 24.316, -0.58038, 4.8489, 5.7989, 14.644, 2.823, 0.90556, 5.7822, 0.27991, -0.23285, -0.86764, 14.943, 1.1713, -0.49166, 1.0163, -1.2139, -0.027504, -0.13759},
          {-34.232, -0.90515, 0.10504, 13.265, 12.104, 40.896, 0.42528, -22.761, -2.7605, -8.2164, 12.083, 11.711, 37.822, 1.285, -16.69, -1.9733, 1.1884, 0.72324, 1.2192, 0.043408, 0.045182, -8.9945, -5.7678, -3.0812, 2.5239, 2.6324, -0.14197, 0.69181, -6.1541, -1.3863, -0.90962, 0.73389, -0.090427, 0.5109, 0.12578, -5.2053, -1.0508, 0.51118, -0.02406, -0.40039, 0.26611, 0.31371, -9.4667, 1.9884, -1.6945, 1.9685, 5.2142, 12.349, -2.6593, -0.41898, 2.2224, -0.98705, -1.4898, 6.44, 10.315, 2.9214, 3.4475, -4.7357, 1.8262, 1.8706, -1.8161, 0.49121, -0.35001, -4.8751, -2.6248, -0.51727, -2.2554, -1.6897, 1.0384, 0.38465, 4.8345, 1.9871, -0.15729, 0.33105, 0.24983, 0.086812, 0.2657, 1.576, -0.59997, 0.237, 1.0437, 0.079588, 0.46166, 0.26377},
          {16.026, 5.3446, 5.6596, 10.628, 9.0822, 1.9452, 2.8241, 16.538, 6.2283, 4.8513, 3.6195, 7.181, 1.285, 4.4975, 5.3557, 0.82257, 0.49293, 0.16055, 0.57859, -0.30459, 0.16398, 6.3787, 0.56772, 0.7561, 0.47129, 0.87178, -0.22366, 0.3984, 1.1086, 0.29067, 0.2414, 0.15418, -0.019714, -0.030524, 0.025003, 0.29022, 0.22663, 0.32767, -0.049177, 0.078781, 0.0044717, 0.064289, 8.7422, 5.3475, 3.4264, 4.5856, 0.93592, 1.0529, 0.27648, 4.3063, 2.8114, 3.9935, 1.661, 2.4051, 1.9018, 4.0202, 0.73006, 0.16783, 0.20274, 0.41607, -0.052547, -0.20425, -0.73198, -1.2896, 0.76365, 0.12642, -0.44818, 0.26451, 0.16897, 0.69214, 0.075413, 0.4373, -0.11741, 0.0052932, -0.076339, -0.020105, -0.023112, 0.10096, 0.045522, -0.082929, -0.38429, 0.072075, 0.071571, 0.13305},
          {2674.2, 936.29, 1268.8, 1201.4, 264.26, -21.529, 4.4414, 2201.5, 870.88, 984.69, 916.43, 223.38, -16.69, 5.3557, 1492.3, 438.1, 477.34, 380.25, 106.09, 10.343, -0.59358, 1140.6, 391.26, 443.23, 342.28, 64.784, 5.8829, -0.84863, 240.14, 48.371, 45.828, 28.701, -0.076162, -4.9509, -2.352, 204.8, 35.8, 31.148, 20.671, 0.29186, -6.8969, -5.1103, 705.7, 272.7, 361.36, 365.16, 29.422, -5.6915, 3.7316, 622.69, 166.04, 343.53, 310.57, 21.215, 2.8616, -1.8578, 291.9, 171.51, 128.41, 114.85, 26.271, 5.2289, 16.192, 306.63, 107.95, 101.56, 106.68, 18.28, 1.3685, -1.071, 90.531, 3.2259, 20.896, 20.718, 2.6328, -2.3156, -4.4182, 87.942, 19.336, 8.7434, 14.27, -0.20407, -4.6486, -5.8726},
          {845.18, 342.69, 475.58, 425.43, 98.803, -0.69736, 0.1205, 721.14, 328.42, 361.38, 322.94, 73.584, -1.9733, 0.82257, 438.1, 192.34, 188.78, 140.09, 35.339, 2.4851, -1.1211, 362.09, 158.13, 182.21, 124.71, 19.797, 2.4196, -0.83406, 80.656, 17.18, 17.519, 12.219, 0.35239, -1.7848, -0.94117, 72.506, 10.454, 12.325, 7.6978, -0.5587, -2.7784, -2.1192, 214.38, 75.855, 121.01, 103.96, 6.6188, -1.1944, 3.8948, 196.12, 54.349, 122.38, 91.689, 8.469, 3.1032, -1.0153, 90.784, 62.515, 50.273, 38.665, 6.1575, 0.01782, 3.8105, 91.565, 40.804, 40.202, 38.688, 2.3308, 0.0062285, -0.31346, 26.258, 2.1389, 7.8584, 9.3226, 1.1481, -0.78625, -1.4896, 26.46, 6.1443, 3.811, 6.498, 0.1471, -2.008, -2.3817},
          {921.25, 376.5, 525.57, 476.43, 111.13, 0.86738, -0.26243, 776.63, 355.92, 404.16, 357.37, 86.021, 1.1884, 0.49293, 477.34, 188.78, 224.96, 155.3, 43.345, 2.7149, -1.6763, 385.6, 170.62, 197.65, 138.29, 23.621, 2.9747, -1.1156, 85.926, 18.079, 18.946, 11.488, 0.81786, -1.9214, -0.99093, 76.969, 10.378, 13.481, 7.6694, -0.14901, -2.9462, -2.3346, 222.37, 84.433, 132.45, 124.83, 3.6838, -2.7447, 3.5461, 211.48, 61.355, 135.81, 103.46, 8.803, 5.4557, 2.435, 81.635, 66.61, 51.857, 43.348, 7.3456, 1.2539, 3.371, 93.588, 43.973, 39.246, 44.026, 3.1703, -0.060301, -0.20161, 32.672, 1.3116, 8.6568, 10.709, 1.6445, -0.83036, -1.5472, 29.029, 6.5804, 3.5879, 7.5024, -0.0082883, -1.9768, -2.6177},
          {822.71, 323.2, 442.96, 411.76, 107.94, 8.5091, 2.4042, 670.29, 294.65, 342.04, 315.69, 84.242, 0.72324, 0.16055, 380.25, 140.09, 155.3, 223.7, 38.071, 7.6776, 0.29282, 307.32, 122.99, 145.2, 178.66, 25.233, 4.452, -0.69298, 64.484, 11.798, 13.08, 8.1409, 0.58046, -0.9467, -0.51464, 53.836, 7.7389, 9.3606, 5.3997, -0.39548, -2.3977, -1.9794, 205.61, 87.893, 109.72, 100.14, 3.5718, 3.4843, 2.7529, 191.44, 61.061, 106.83, 83.91, 13.264, 6.8101, -7.9251, 74.124, 44.307, 35.53, 56.904, 7.1593, 2.6625, 1.7495, 56.916, 30.793, 22.276, 58.502, 3.0649, 1.6501, -3.1382, 24.093, 2.3431, 5.7559, 7.6622, 2.0044, -0.53797, -1.2346, 25.571, 5.4145, 3.6718, 5.5981, -0.27416, -1.8913, -2.1},
          {223.5, 77.04, 111.73, 111.93, 37.819, 0.21168, 1.0916, 163.8, 64.917, 71.781, 73.907, 20.104, 1.2192, 0.57859, 106.09, 35.339, 43.345, 38.071, 43.578, 2.8288, -0.60063, 80.204, 29.195, 38.093, 28.702, 30.59, 1.2197, -0.8168, 16.11, 3.3992, 3.938, 0.67273, 0.63093, -0.40147, -0.051805, 13.877, 1.7861, 2.2934, 0.34187, 0.19632, -0.73176, -0.4858, 59.32, 19.726, 27.016, 31.226, 2.722, 0.39378, 0.35321, 66.724, 5.1029, 26.809, 16.346, 4.2586, 2.1482, 0.08067, 24.146, 15.158, 10.607, 7.1859, 11.908, 0.89692, -1.6513, 20.163, 8.6779, 4.626, 9.6435, 7.7811, 0.071057, -2.63, 6.4658, -0.66288, 2.247, 1.5228, 0.13741, -0.21156, -0.59609, 4.6406, 0.85899, 0.45144, 1.5029, -0.24882, -0.64683, -0.86039},
          {22.604, 4.7191, 8.9132, 11.651, 11.792, 0.19176, 0.44419, 11.947, 2.3811, 2.2809, 9.7415, 7.3233, 0.043408, -0.30459, 10.343, 2.4851, 2.7149, 7.6776, 2.8288, 4.0272, 0.058478, 7.7254, -0.19174, 1.6848, 5.1761, 1.6262, 2.4971, -0.08012, 0.88586, -0.21035, -0.0079182, -0.17563, 0.10799, 0.072155, 0.023248, 0.28488, -0.31335, 0.11811, -0.0074621, 0.0088587, -0.057299, 0.014267, 5.2715, 2.512, 3.2424, 4.1055, 4.9902, 1.1256, 0.15765, 7.0261, 0.88018, -0.74699, 3.0634, 4.1668, 0.95996, -1.8804, 3.0705, 0.064568, 0.30295, 1.3984, 0.45334, 1.0693, 0.44051, 0.32337, -0.20251, 0.078497, 1.3687, 0.38787, 0.82935, -0.098493, 2.1879, 0.43556, 0.2233, 0.42178, 0.10736, 0.060472, 0.078225, 1.4999, 0.29595, 0.31824, 0.30007, 0.023148, -0.066968, 0.013475},
          {-1.8677, -2.2258, -3.1025, 1.0733, -0.50501, 0.14924, 0.27126, -1.9519, -2.2615, -2.2269, 1.455, -0.68929, 0.045182, 0.16398, -0.59358, -1.1211, -1.6763, 0.29282, -0.60063, 0.058478, 0.67721, -0.34162, -1.1424, -1.7705, 0.12805, -0.073526, -0.074251, 0.43663, -0.36493, -0.059509, -0.19223, 0.03988, -0.0088415, 0.022597, 0.023009, -0.48174, -0.047644, -0.16749, 0.061183, 0.0095678, 0.017765, 0.048313, 0.4575, -1.0445, -1.317, -0.69928, -0.29095, 0.31108, 0.52899, -0.74694, -0.59426, -1.2365, -0.56622, -0.71837, -0.14541, -0.61237, -0.26002, -1.0215, -0.48575, -0.21366, 0.0022364, -0.099933, -0.0076671, -0.47133, -0.67414, -0.35509, -0.22762, 0.12616, -0.024309, -0.073807, 0.22498, 0.12483, -0.16482, -0.012139, 0.024224, 0.020899, 0.027677, 0.11097, 0.022939, 0.088805, 0.079357, 0.025695, 0.036326, 0.019166},
          {2128.7, 771.52, 1001.9, 992.26, 212.17, -10.512, 3.9378, 1862.5, 742.51, 834.2, 786.96, 187.13, -8.9945, 6.3787, 1140.6, 362.09, 385.6, 307.32, 80.204, 7.7254, -0.34162, 998.03, 321.72, 366.03, 286.52, 52.965, 5.1139, 0.93361, 204.29, 42.826, 40.223, 25.759, -0.015759, -3.7906, -1.6489, 175.36, 31.258, 28.192, 20.0, 0.49023, -5.3211, -3.7617, 576.86, 214.81, 280.58, 287.26, 24.158, -8.7493, 1.0807, 529.76, 148.96, 284.68, 259.08, 22.684, 2.9075, -0.48433, 218.2, 130.09, 97.004, 86.608, 13.734, 2.9248, 13.211, 225.7, 90.14, 81.801, 85.969, 9.481, 1.909, 6.9534, 70.195, 6.6789, 17.539, 16.667, 1.597, -1.6972, -3.4004, 73.723, 17.53, 8.0524, 12.514, 0.32259, -3.2991, -4.3915},
          {739.49, 309.78, 425.13, 382.27, 72.668, -6.9398, 0.56026, 653.4, 308.39, 348.56, 293.47, 64.268, -5.7678, 0.56772, 391.26, 158.13, 170.62, 122.99, 29.195, -0.19174, -1.1424, 321.72, 159.82, 163.91, 111.55, 16.583, 0.95514, -1.1148, 72.331, 15.659, 16.272, 10.67, 0.28897, -1.7978, -0.97414, 66.992, 9.3463, 10.376, 7.2463, -0.16376, -2.5745, -2.0281, 190.04, 67.731, 105.02, 90.884, -4.2971, -5.3456, 3.5825, 170.2, 50.903, 113.13, 86.455, 0.86701, -2.3533, -1.2775, 76.973, 58.721, 42.391, 35.539, 5.402, 0.22332, 3.4656, 87.339, 40.332, 36.759, 37.186, 3.7176, -0.27336, -0.48524, 24.887, 2.1598, 8.3888, 8.8669, 1.4974, -0.75788, -1.4379, 26.365, 6.1641, 3.146, 5.7508, 0.2332, -1.9164, -2.2435},
          {824.29, 348.41, 485.24, 435.83, 102.12, -3.3981, -0.29439, 740.74, 344.5, 386.45, 348.37, 85.28, -3.0812, 0.7561, 443.23, 182.21, 197.65, 145.2, 38.093, 1.6848, -1.7705, 366.03, 163.91, 207.16, 129.42, 20.872, 2.4451, -1.7961, 84.208, 17.433, 17.65, 11.338, 0.57369, -1.9819, -0.8622, 77.69, 9.5281, 13.958, 7.4708, -0.47909, -2.8888, -2.284, 210.44, 75.703, 122.11, 118.18, 2.2583, -2.0169, 2.8962, 210.86, 63.05, 135.15, 106.25, 6.8339, 4.5091, 0.6616, 77.715, 66.588, 46.322, 39.238, 5.6528, 0.19558, 4.7494, 90.244, 44.08, 39.194, 41.275, 2.3396, -0.22988, 0.63261, 26.982, 0.7646, 8.9444, 9.6384, 1.1621, -0.78032, -1.5499, 28.708, 6.0698, 3.4663, 7.0324, -0.26327, -2.1225, -2.4595},
          {751.1, 302.87, 397.96, 370.99, 80.966, 8.2094, 2.1554, 643.58, 281.88, 326.37, 293.37, 72.441, 2.5239, 0.47129, 342.28, 124.71, 138.29, 178.66, 28.702, 5.1761, 0.12805, 286.52, 111.55, 129.42, 171.52, 19.281, 3.4204, -0.2277, 61.016, 11.861, 12.187, 7.7313, 0.077639, -1.1316, -0.71563, 52.441, 7.9414, 9.3397, 5.362, -0.65477, -2.3577, -1.6703, 188.84, 85.689, 106.78, 95.98, 0.42898, 0.072425, 3.4864, 175.51, 57.484, 107.36, 89.738, 8.6257, 4.8875, -3.8669, 60.256, 42.048, 31.724, 51.266, 6.8157, 1.076, 3.2453, 56.884, 29.829, 23.721, 51.644, 2.1975, 1.2745, 0.29921, 20.707, 1.4766, 4.5171, 6.7282, 1.5232, -0.60477, -1.3688, 23.834, 5.2343, 3.2578, 4.9695, -0.40095, -1.3856, -1.7459},
          {124.89, 49.105, 58.967, 58.093, 19.256, 2.5704, 0.91023, 98.426, 40.376, 48.579, 39.298, 10.685, 2.6324, 0.87178, 64.784, 19.797, 23.621, 25.233, 30.59, 1.6262, -0.073526, 52.965, 16.583, 20.872, 19.281, 31.161, 0.48572, -0.045696, 10.752, 2.3864, 2.4662, 0.79663, 0.18822, -0.21964, -0.030534, 8.0285, 2.3748, 0.972, 1.2912, 0.026124, -0.39519, -0.2025, 30.376, 16.06, 14.943, 15.847, 2.513, 0.90171, -0.16197, 30.799, 3.8835, 15.103, 6.7099, 0.70982, 0.54624, -0.35507, 15.01, 5.125, 7.0764, 4.2616, 9.8547, 0.57824, -1.9033, 11.141, 5.0101, 3.8849, 4.5202, 7.4898, -0.16243, -2.0271, 3.4692, 0.69063, 0.6484, 0.17505, -0.055214, -0.14519, -0.48868, 2.4748, 0.21581, 0.63971, 0.58984, 0.06678, -0.17324, -0.57386},
          {12.545, 4.5238, 8.7937, 10.423, 7.0408, -0.23476, 0.14932, 8.3152, 5.0515, 4.84, 9.5305, 4.9719, -0.14197, -0.22366, 5.8829, 2.4196, 2.9747, 4.452, 1.2197, 2.4971, -0.074251, 5.1139, 0.95514, 2.4451, 3.4204, 0.48572, 2.2814, -0.095859, 1.1694, 0.12966, 0.27605, 0.039349, 0.039061, 0.0105, 0.01854, 0.74804, -0.24234, 0.24999, 0.2107, 0.0097038, -0.054472, 0.015893, 0.50791, 1.3953, 2.3153, 3.5149, 2.2279, 0.53071, 0.049082, 2.8121, 0.97301, 1.4333, 3.0943, 2.3154, 0.39475, -0.74842, -0.40985, 0.42403, 0.62336, 1.1382, -0.17362, 0.72337, 0.47904, -0.63898, 0.026638, -0.13133, 0.66333, -0.11929, 0.54462, 0.17878, 1.4204, 0.3383, 0.24556, 0.38115, 0.1154, 0.009533, 0.04267, 1.1722, 0.44881, 0.21989, 0.35543, 0.026903, -0.049482, 0.054287},
          {-1.8774, -1.6665, -2.5636, -0.07352, -1.1289, 0.78763, -0.1122, -0.64445, -0.78898, -0.86443, -0.75405, -0.72055, 0.69181, 0.3984, -0.84863, -0.83406, -1.1156, -0.69298, -0.8168, -0.08012, 0.43663, 0.93361, -1.1148, -1.7961, -0.2277, -0.045696, -0.095859, 0.9529, 0.17926, 0.18193, 0.069675, 0.12401, 0.055141, 0.019703, 0.0091183, 0.014557, 0.10391, 0.098015, 0.21841, -0.0022614, -0.0076383, 0.052848, -0.36193, -0.61371, -1.0099, -1.5968, -0.37207, 0.099733, -0.028849, 1.1726, 0.065589, -1.0935, -0.82195, -0.62876, 0.27036, 1.0019, 0.35516, -1.186, -0.27268, -0.46758, -0.12076, -0.18683, -0.077255, -0.072055, -0.0017108, -0.17464, -0.44657, -0.091251, 0.024978, 0.30936, 0.39282, 0.29719, -0.20712, -0.11924, -0.033664, 0.018167, 0.0054199, 0.23035, 0.029465, 0.081961, 0.062205, 0.079766, 0.069385, 0.07118},
          {519.98, 192.84, 261.73, 267.86, 38.915, -7.6937, 0.59935, 452.97, 190.34, 218.54, 198.47, 41.759, -6.1541, 1.1086, 240.14, 80.656, 85.926, 64.484, 16.11, 0.88586, -0.36493, 204.29, 72.331, 84.208, 61.016, 10.752, 1.1694, 0.17926, 103.99, 23.393, 19.915, 15.048, 1.0032, -1.4475, -0.51662, 87.064, 17.692, 16.002, 12.181, 1.1406, -1.5911, -1.5493, 124.22, 51.852, 74.175, 64.083, -0.85609, -1.8242, 5.3831, 119.21, 36.48, 72.17, 67.971, 0.86465, 2.3959, 1.8843, 51.997, 36.376, 28.492, 19.559, 4.7241, 0.97505, 5.6, 65.281, 21.94, 20.971, 20.637, 5.8331, 0.67008, 3.5389, 19.181, 4.2913, 6.2892, 5.084, 0.69698, -0.3716, -0.96306, 19.226, 6.3498, 3.8913, 4.2237, 0.91432, -0.85104, -1.3607},
          {116.99, 43.528, 59.385, 56.569, 10.302, -0.99854, -0.10616, 101.38, 44.632, 51.377, 40.553, 11.295, -1.3863, 0.29067, 48.371, 17.18, 18.079, 11.798, 3.3992, -0.21035, -0.059509, 42.826, 15.659, 17.433, 11.861, 2.3864, 0.12966, 0.18193, 23.393, 7.5645, 4.8599, 3.7323, 0.37206, -0.31218, -0.11773, 21.181, 4.1665, 3.9707, 3.0858, 0.19716, -0.40532, -0.36567, 31.952, 11.6, 16.441, 10.903, 1.4586, -0.7816, 1.6142, 32.24, 10.24, 18.018, 12.864, 1.6783, 0.30022, -0.15419, 12.787, 7.3701, 5.6896, 3.7028, 0.9836, 0.11886, 0.80341, 15.411, 4.192, 5.3138, 3.9453, 0.84058, 0.26667, 0.81091, 2.9271, 0.94086, 1.0611, 1.053, 0.010074, -0.11098, -0.26652, 3.3823, 1.3027, 0.71598, 0.90243, 0.19963, -0.1217, -0.28456},
          {102.17, 40.798, 55.037, 55.143, 8.6825, -1.0256, 0.054331, 88.349, 40.239, 46.358, 40.675, 9.0929, -0.90962, 0.2414, 45.828, 17.519, 18.946, 13.08, 3.938, -0.0079182, -0.19223, 40.223, 16.272, 17.65, 12.187, 2.4662, 0.27605, 0.069675, 19.915, 4.8599, 5.7425, 3.0596, 0.16956, -0.24308, -0.10867, 17.433, 3.4818, 3.5277, 2.6585, 0.21322, -0.30442, -0.32498, 19.258, 10.221, 13.799, 12.717, -1.6291, -0.60894, 0.84779, 21.98, 6.4361, 14.517, 12.256, -0.27769, 0.61316, 0.80303, 8.1975, 7.316, 5.5237, 3.3256, 0.70433, 0.26187, 0.86627, 10.97, 4.3153, 4.5951, 3.4914, 0.68455, 0.1432, 0.65734, 4.2332, 1.007, 1.4724, 1.0957, 0.1221, -0.098187, -0.19041, 3.6729, 1.3688, 0.74787, 0.97006, 0.20045, -0.13667, -0.18827},
          {63.98, 30.009, 40.051, 33.517, 4.2637, 1.1852, 0.17255, 58.19, 29.256, 34.861, 24.559, 5.6662, 0.73389, 0.15418, 28.701, 12.219, 11.488, 8.1409, 0.67273, -0.17563, 0.03988, 25.759, 10.67, 11.338, 7.7313, 0.79663, 0.039349, 0.12401, 15.048, 3.7323, 3.0596, 4.7722, 0.018921, -0.12314, -0.13646, 12.881, 3.0596, 2.4835, 2.9514, 0.14721, -0.21033, -0.23649, 16.078, 7.2542, 10.608, 5.8025, -0.54475, 0.73841, 1.6707, 13.79, 6.3996, 10.526, 6.7021, 0.087101, 0.3619, -0.66478, 6.8517, 4.26, 4.2431, 2.4115, 0.056371, -0.065526, 0.84958, 9.2845, 2.7421, 3.192, 2.8464, 0.59069, -0.013075, 0.25542, 2.2994, 1.2907, 0.75447, 1.1983, 0.059047, -0.038986, -0.1306, 2.1003, 0.68332, 0.74958, 1.0056, 0.14507, -0.097954, -0.13296},
          {4.8098, 1.2417, 1.4739, 2.7691, 0.41795, -0.16071, 0.0067127, 3.7695, -0.44915, -0.40536, 0.18442, -0.45779, -0.090427, -0.019714, -0.076162, 0.35239, 0.81786, 0.58046, 0.63093, 0.10799, -0.0088415, -0.015759, 0.28897, 0.57369, 0.077639, 0.18822, 0.039061, 0.055141, 1.0032, 0.37206, 0.16956, 0.018921, 0.58568, 0.050272, 0.039224, 0.91572, 0.098376, 0.25952, -0.06869, 0.15313, -0.0098753, 0.018437, 2.2066, -0.78708, 0.44203, -0.35856, -0.012146, -0.027626, -0.42572, 2.4823, -0.29279, -0.7781, -0.83123, -0.2602, 0.26881, -0.47041, 1.5983, 0.52604, 0.12988, -0.091977, 0.045188, 0.083704, -0.16992, 0.844, 0.033006, -0.21129, 0.40511, 0.22676, 0.1123, 0.13323, 0.020207, 0.0067405, 0.14982, 0.040406, 0.12318, 0.030697, 0.021436, 0.41334, 0.072891, 0.076877, 0.035549, 0.11866, -0.00014591, 0.012177},
          {-10.741, -3.9334, -5.8213, -6.1201, -1.4276, 0.75163, -0.0462, -10.03, -4.6019, -5.2539, -4.4402, -1.6479, 0.5109, -0.030524, -4.9509, -1.7848, -1.9214, -0.9467, -0.40147, 0.072155, 0.022597, -3.7906, -1.7978, -1.9819, -1.1316, -0.21964, 0.0105, 0.019703, -1.4475, -0.31218, -0.24308, -0.12314, 0.050272, 0.14757, 0.033658, -1.4057, -0.21608, -0.14504, -0.11125, -0.0021302, 0.079362, 0.046279, -1.4642, -0.85449, -1.4403, -1.3464, 0.17584, 0.25429, -0.16533, -0.84106, -0.65461, -1.9875, -1.4876, -0.082467, 0.053905, -0.18041, -0.25297, -1.0783, -0.56572, -0.38207, -0.16271, 0.04259, -0.052336, -0.98664, -0.71939, -0.50309, -0.49954, -0.12764, 0.0060671, -0.11193, 0.26004, 0.10384, -0.0059066, -0.087589, 0.011588, 0.0319, 0.062492, 0.15862, -0.039299, 0.034302, -0.0017323, 0.015424, 0.05539, 0.058261},
          {-4.3299, -1.7135, -2.7571, -2.3862, -0.062549, 0.13102, -0.031351, -3.6993, -2.047, -2.5112, -1.5689, -0.16117, 0.12578, 0.025003, -2.352, -0.94117, -0.99093, -0.51464, -0.051805, 0.023248, 0.023009, -1.6489, -0.97414, -0.8622, -0.71563, -0.030534, 0.01854, 0.0091183, -0.51662, -0.11773, -0.10867, -0.13646, 0.039224, 0.033658, 0.064314, -0.58579, -0.10148, -0.047533, -0.11358, 0.010784, 0.040011, 0.032026, -0.37667, -0.48416, -0.75503, -0.45248, 0.086299, 0.036409, -0.1345, -0.23042, -0.19427, -0.65822, -0.51765, -0.0051655, 0.14053, 0.02918, -0.079225, -0.37952, -0.29573, -0.24179, -0.053953, 0.017294, -0.054629, -0.47497, -0.28183, -0.19842, -0.31761, -0.12623, 0.023581, 0.055567, 0.01806, 0.014043, -0.018365, -0.073037, 0.022852, 0.014445, 0.02445, 0.01956, -0.004528, 0.0082165, -0.0085739, 0.026334, 0.020798, 0.033145},
          {453.91, 167.79, 234.94, 232.19, 39.213, -6.7634, -0.65209, 403.05, 172.31, 197.14, 175.25, 42.031, -5.2053, 0.29022, 204.8, 72.506, 76.969, 53.836, 13.877, 0.28488, -0.48174, 175.36, 66.992, 77.69, 52.441, 8.0285, 0.74804, 0.014557, 87.064, 21.181, 17.433, 12.881, 0.91572, -1.4057, -0.58579, 83.462, 15.003, 14.956, 10.284, 0.72384, -1.6034, -1.5055, 110.12, 40.548, 60.81, 50.272, -0.0091241, -2.6563, 3.4543, 114.97, 35.025, 64.761, 55.707, 2.0677, 1.1673, 0.77555, 46.606, 33.867, 25.14, 15.06, 3.6409, 0.79281, 4.6739, 58.882, 20.641, 19.919, 19.678, 4.4309, 1.1141, 3.3837, 13.364, 2.5922, 4.6971, 4.6421, 0.30881, -0.49419, -1.0333, 13.588, 5.3577, 2.4981, 3.1702, 0.46214, -0.86248, -1.2939},
          {79.243, 28.75, 34.735, 33.544, 3.5949, -1.1926, 0.20392, 68.73, 26.953, 34.325, 23.732, 5.4973, -1.0508, 0.22663, 35.8, 10.454, 10.378, 7.7389, 1.7861, -0.31335, -0.047644, 31.258, 9.3463, 9.5281, 7.9414, 2.3748, -0.24234, 0.10391, 17.692, 4.1665, 3.4818, 3.0596, 0.098376, -0.21608, -0.10148, 15.003, 4.7169, 2.8912, 2.5495, 0.23816, -0.20585, -0.25025, 19.58, 8.998, 10.179, 5.8586, -1.1863, -0.43191, 0.85956, 16.751, 6.188, 9.7358, 7.9024, -0.39856, -0.21248, 0.03009, 7.3652, 4.2021, 4.1303, 1.7261, 0.94503, -0.039934, 0.74638, 10.048, 2.7834, 3.006, 1.7734, 1.398, 0.01016, 0.64384, 1.9259, 1.0973, 0.57682, 0.51327, 0.054015, -0.078919, -0.17468, 2.0352, 0.84488, 0.59049, 0.24447, 0.16128, -0.028142, -0.17745},
          {69.709, 27.879, 37.838, 33.755, 7.2222, 0.45039, -0.40135, 65.109, 28.024, 31.282, 26.711, 6.8503, 0.51118, 0.32767, 31.148, 12.325, 13.481, 9.3606, 2.2934, 0.11811, -0.16749, 28.192, 10.376, 13.958, 9.3397, 0.972, 0.24999, 0.098015, 16.002, 3.9707, 3.5277, 2.4835, 0.25952, -0.14504, -0.047533, 14.956, 2.8912, 4.4868, 2.0238, 0.16099, -0.17093, -0.24815, 16.9, 5.7917, 7.9708, 6.9888, -2.0677, 0.01833, 0.24521, 20.409, 6.0339, 10.497, 7.2922, 0.68741, 1.0655, 0.53877, 8.1357, 5.7378, 4.2214, 2.5003, 0.16252, 0.024759, 0.99737, 9.7953, 3.1991, 3.3827, 3.1967, 0.26971, 0.22142, 1.3117, 1.9868, 0.73794, 0.82511, 0.69222, -0.057631, -0.051991, -0.1202, 2.7857, 1.0464, 0.38552, 0.64401, 0.072466, -0.04014, -0.074818},
          {46.518, 21.405, 27.237, 25.411, -1.7682, 0.24247, -0.0011667, 46.006, 23.948, 28.713, 19.154, 2.2077, -0.02406, -0.049177, 20.671, 7.6978, 7.6694, 5.3997, 0.34187, -0.0074621, 0.061183, 20.0, 7.2463, 7.4708, 5.362, 1.2912, 0.2107, 0.21841, 12.181, 3.0858, 2.6585, 2.9514, -0.06869, -0.11125, -0.11358, 10.284, 2.5495, 2.0238, 3.6331, 0.13389, -0.12022, -0.20445, 6.795, 6.3425, 6.2699, 2.8422, -2.1492, 0.19849, 1.082, 5.8905, 5.3833, 7.5272, 4.3078, -1.3524, -0.51457, -0.3243, 2.8673, 2.9161, 2.7494, 1.8212, 0.17069, 0.0086756, 1.0929, 5.5613, 1.5993, 3.2318, 1.8362, 0.70308, 0.0029951, 0.50803, 1.9676, 1.139, 0.419, 0.64428, 0.03059, -0.068442, -0.058244, 1.6538, 0.64624, 0.67904, 0.87296, 0.13831, 0.021645, -0.038672},
          {0.49875, 0.29302, -0.62644, 0.83701, -0.5108, -0.48635, 0.094347, 0.20085, -0.24723, -0.1451, -0.9781, -0.72381, -0.40039, 0.078781, 0.29186, -0.5587, -0.14901, -0.39548, 0.19632, 0.0088587, 0.0095678, 0.49023, -0.16376, -0.47909, -0.65477, 0.026124, 0.0097038, -0.0022614, 1.1406, 0.19716, 0.21322, 0.14721, 0.15313, -0.0021302, 0.010784, 0.72384, 0.23816, 0.16099, 0.13389, 0.32249, 0.018787, 0.037216, 1.4939, 0.76453, 0.42063, 1.0946, -0.18881, 0.010741, -0.052065, -0.24729, 0.16994, 0.23142, 0.31439, -0.1325, -0.0067071, -0.47437, 0.63405, 0.21139, -0.041775, 0.020581, 0.031041, 0.05621, -0.069968, 0.46138, -0.11339, -0.1425, 0.20488, 0.30907, 0.0054934, -0.0446, 0.15581, 0.080736, 0.15508, -0.044632, 0.087848, -0.0041836, 0.019659, 0.29247, 0.11583, -0.026978, 0.019691, 0.07997, 0.0081853, 0.016543},
          {-16.329, -6.2219, -8.9891, -8.6285, -1.7529, 0.33625, -0.00056757, -14.33, -6.5399, -7.3807, -5.96, -1.8599, 0.26611, 0.0044717, -6.8969, -2.7784, -2.9462, -2.3977, -0.73176, -0.057299, 0.017765, -5.3211, -2.5745, -2.8888, -2.3577, -0.39519, -0.054472, -0.0076383, -1.5911, -0.40532, -0.30442, -0.21033, -0.0098753, 0.079362, 0.040011, -1.6034, -0.20585, -0.17093, -0.12022, 0.018787, 0.17331, 0.076424, -3.8628, -1.6192, -2.5641, -1.9906, -0.077898, 0.21123, -0.26373, -3.0325, -1.0549, -2.3566, -1.8972, -0.42846, 0.024291, -0.12282, -0.75165, -1.2112, -0.9428, -0.74245, -0.20845, 0.027821, 0.060043, -1.2706, -0.79178, -0.5498, -0.85921, -0.09267, -0.0054633, 0.031126, -0.1205, 0.051167, -0.044558, -0.14107, -0.0053904, 0.028906, 0.070872, -0.0072906, -0.059036, 0.0064081, -0.049861, 0.019651, 0.065295, 0.071045},
          {-10.927, -4.0123, -6.5136, -5.3105, -0.77104, 0.27946, 0.016592, -9.3423, -4.0775, -5.2407, -3.9582, -0.82325, 0.31371, 0.064289, -5.1103, -2.1192, -2.3346, -1.9794, -0.4858, 0.014267, 0.048313, -3.7617, -2.0281, -2.284, -1.6703, -0.2025, 0.015893, 0.052848, -1.5493, -0.36567, -0.32498, -0.23649, 0.018437, 0.046279, 0.032026, -1.5055, -0.25025, -0.24815, -0.20445, 0.037216, 0.076424, 0.14447, -2.1115, -0.93802, -1.4995, -0.71217, 0.28863, 0.094877, -0.22952, -2.5921, -0.38695, -1.4484, -1.0596, -0.029242, 0.034172, -0.1274, -0.85858, -0.88526, -0.55787, -0.52825, -0.1095, 0.022293, -0.099593, -1.225, -0.56679, -0.56672, -0.62734, -0.11094, -0.0071837, -0.0082096, -0.40604, -0.0073464, -0.1131, -0.21328, 0.0088775, 0.011814, 0.040025, -0.37581, -0.094462, -0.083501, -0.091985, 0.03192, 0.045952, 0.049264},
          {1687.3, 561.85, 736.35, 704.82, 208.13, -8.2705, 8.4573, 1409.6, 475.53, 563.72, 537.79, 144.07, -9.4667, 8.7422, 705.7, 214.38, 222.37, 205.61, 59.32, 5.2715, 0.4575, 576.86, 190.04, 210.44, 188.84, 30.376, 0.50791, -0.36193, 124.22, 31.952, 19.258, 16.078, 2.2066, -1.4642, -0.37667, 110.12, 19.58, 16.9, 6.795, 1.4939, -3.8628, -2.1115, 1119.2, 219.7, 307.28, 285.22, 73.789, 12.298, 29.418, 927.21, 241.64, 260.67, 251.69, 64.285, 19.792, 10.881, 275.56, 79.762, 54.755, 44.666, 14.137, 3.5177, 12.289, 241.02, 60.052, 35.207, 53.015, 7.7419, 3.6796, 1.462, 45.744, 2.4116, 7.3729, 7.0657, 1.4226, -0.71599, -1.8578, 57.782, 8.6029, 1.7088, 3.0477, -0.48938, -2.6417, -3.4771},
          {611.98, 257.27, 326.62, 289.58, 80.548, 5.5661, 4.0996, 531.28, 231.02, 271.66, 211.27, 66.888, 1.9884, 5.3475, 272.7, 75.855, 84.433, 87.893, 19.726, 2.512, -1.0445, 214.81, 67.731, 75.703, 85.689, 16.06, 1.3953, -0.61371, 51.852, 11.6, 10.221, 7.2542, -0.78708, -0.85449, -0.48416, 40.548, 8.998, 5.7917, 6.3425, 0.76453, -1.6192, -0.93802, 219.7, 185.14, 161.24, 169.4, 41.706, 2.5018, 6.367, 156.4, 98.53, 145.87, 131.05, 36.121, 3.2199, 3.5706, 69.982, 42.432, 36.389, 46.207, 9.4955, 2.6517, 3.6491, 58.14, 35.501, 34.959, 33.646, 8.8618, 0.52737, 0.078863, 15.007, 3.468, 4.2108, 2.0913, 0.67638, -0.32391, -0.76003, 13.953, 2.8665, 2.8879, 1.8955, 0.89481, -0.52371, -1.2635},
          {821.71, 327.43, 437.93, 397.59, 81.414, 1.6232, 4.316, 691.29, 290.19, 344.94, 279.66, 59.498, -1.6945, 3.4264, 361.36, 121.01, 132.45, 109.72, 27.016, 3.2424, -1.317, 280.58, 105.02, 122.11, 106.78, 14.943, 2.3153, -1.0099, 74.175, 16.441, 13.799, 10.608, 0.44203, -1.4403, -0.75503, 60.81, 10.179, 7.9708, 6.2699, 0.42063, -2.5641, -1.4995, 307.28, 161.24, 246.73, 207.65, 44.285, 1.8644, 12.268, 238.58, 107.96, 183.03, 156.01, 32.174, 7.8142, 5.343, 74.475, 59.263, 47.269, 50.356, 10.086, 2.3743, 7.9144, 76.167, 40.283, 34.345, 39.401, 7.1536, -0.10241, 2.4066, 22.578, 3.0612, 6.9955, 7.1552, 1.0086, -0.32331, -0.93312, 22.896, 4.0914, 4.4733, 4.6094, 0.51655, -1.3533, -2.2055},
          {672.55, 280.2, 362.07, 563.45, 99.6, 2.3096, 6.8712, 578.59, 240.47, 273.78, 451.02, 72.802, 1.9685, 4.5856, 365.16, 103.96, 124.83, 100.14, 31.226, 4.1055, -0.69928, 287.26, 90.884, 118.18, 95.98, 15.847, 3.5149, -1.5968, 64.083, 10.903, 12.717, 5.8025, -0.35856, -1.3464, -0.45248, 50.272, 5.8586, 6.9888, 2.8422, 1.0946, -1.9906, -0.71217, 285.22, 169.4, 207.65, 360.55, 53.546, 6.056, 9.9604, 237.41, 122.29, 188.31, 253.93, 46.09, 11.735, 9.3041, 34.596, 49.934, 32.065, 37.328, 9.8105, 3.6713, 2.3507, 28.6, 38.121, 27.371, 37.631, 6.474, -1.1192, -2.6706, 22.719, 1.2236, 8.5723, 6.7185, 0.79185, -0.34562, -0.53949, 20.71, 4.3316, 2.1993, 3.5506, 0.46894, -1.3375, -1.6517},
          {94.67, 29.358, 29.713, 42.152, 102.64, 8.0253, 0.92358, 48.69, 9.3351, 4.6304, 40.691, 74.94, 5.2142, 0.93592, 29.422, 6.6188, 3.6838, 3.5718, 2.722, 4.9902, -0.29095, 24.158, -4.2971, 2.2583, 0.42898, 2.513, 2.2279, -0.37207, -0.85609, 1.4586, -1.6291, -0.54475, -0.012146, 0.17584, 0.086299, -0.0091241, -1.1863, -2.0677, -2.1492, -0.18881, -0.077898, 0.28863, 73.789, 41.706, 44.285, 53.546, 86.166, 8.4912, -0.29439, 60.947, 32.999, 19.422, 39.046, 47.6, 8.5172, -2.8316, 33.368, 3.0505, 7.6223, 7.9668, 1.04, 1.6451, 0.19491, 2.8777, 5.0626, 6.2621, 3.312, 1.0888, 0.86766, -0.016302, 3.7846, 0.85673, 0.59211, 1.1395, -0.025025, 0.20469, 0.30212, 3.384, 0.21238, 1.3559, -0.22282, -0.044634, 0.15851, 0.063831},
          {-36.091, -13.482, -12.896, 0.52939, 9.1283, 15.496, 1.0202, -41.474, -15.815, -20.167, 0.23896, 5.9917, 12.349, 1.0529, -5.6915, -1.1944, -2.7447, 3.4843, 0.39378, 1.1256, 0.31108, -8.7493, -5.3456, -2.0169, 0.072425, 0.90171, 0.53071, 0.099733, -1.8242, -0.7816, -0.60894, 0.73841, -0.027626, 0.25429, 0.036409, -2.6563, -0.43191, 0.01833, 0.19849, 0.010741, 0.21123, 0.094877, 12.298, 2.5018, 1.8644, 6.056, 8.4912, 14.497, 1.2141, 13.576, 5.1285, -1.2046, 1.6336, 7.3993, 9.6832, 0.42889, 0.2274, -5.1978, -1.3848, -2.357, -0.59237, 1.0859, 0.55444, -5.2919, -2.0934, -2.2761, -1.7827, -0.20828, 0.28787, 0.26223, 2.359, 1.2239, -0.22258, 0.19659, 0.20827, 0.041336, 0.11757, 1.973, -0.41942, 0.095681, 0.21232, -0.19341, 0.094988, 0.043339},
          {13.612, 7.3217, 14.917, 18.947, 0.14761, -3.8482, 1.4329, 7.8465, 9.3885, 11.492, 11.098, -1.4138, -2.6593, 0.27648, 3.7316, 3.8948, 3.5461, 2.7529, 0.35321, 0.15765, 0.52899, 1.0807, 3.5825, 2.8962, 3.4864, -0.16197, 0.049082, -0.028849, 5.3831, 1.6142, 0.84779, 1.6707, -0.42572, -0.16533, -0.1345, 3.4543, 0.85956, 0.24521, 1.082, -0.052065, -0.26373, -0.22952, 29.418, 6.367, 12.268, 9.9604, -0.29439, 1.2141, 14.074, 19.123, 7.2765, 11.946, 7.9355, 0.59182, 0.1532, 2.42, -5.4198, 0.080851, 0.18361, -0.71075, 0.71848, 0.29565, 0.69973, -0.92691, -0.92786, -0.18257, 0.028856, 0.71469, -0.095207, -1.1741, 0.08724, 0.13083, 0.065507, 0.15295, 0.065019, 0.047782, -0.040292, -0.26273, 0.10695, 0.2467, 0.58737, -0.15972, -0.14897, -0.19482},
          {1427.4, 474.28, 650.9, 608.91, 189.91, -1.8842, 4.6937, 1229.2, 431.94, 484.96, 533.87, 149.73, -0.41898, 4.3063, 622.69, 196.12, 211.48, 191.44, 66.724, 7.0261, -0.74694, 529.76, 170.2, 210.86, 175.51, 30.799, 2.8121, 1.1726, 119.21, 32.24, 21.98, 13.79, 2.4823, -0.84106, -0.23042, 114.97, 16.751, 20.409, 5.8905, -0.24729, -3.0325, -2.5921, 927.21, 156.4, 238.58, 237.41, 60.947, 13.576, 19.123, 1123.6, 230.34, 243.41, 242.47, 70.29, 20.737, 16.483, 234.64, 56.148, 35.368, 18.375, 8.5579, 2.7934, 9.097, 209.39, 44.448, 18.021, 39.446, -2.3474, 4.6638, 2.4766, 41.917, 1.9638, 9.115, 8.808, -0.56456, -0.7101, -1.4767, 60.276, 9.928, -0.15223, 2.1647, -1.369, -1.9509, -2.1972},
          {398.08, 186.98, 220.65, 220.83, 64.982, 2.8432, 1.5879, 389.8, 179.73, 206.42, 194.82, 66.24, 2.2224, 2.8114, 166.04, 54.349, 61.355, 61.061, 5.1029, 0.88018, -0.59426, 148.96, 50.903, 63.05, 57.484, 3.8835, 0.97301, 0.065589, 36.48, 10.24, 6.4361, 6.3996, -0.29279, -0.65461, -0.19427, 35.025, 6.188, 6.0339, 5.3833, 0.16994, -1.0549, -0.38695, 241.64, 98.53, 107.96, 122.29, 32.999, 5.1285, 7.2765, 230.34, 162.88, 121.32, 102.78, 32.963, 5.2886, 2.3337, 44.359, 20.785, 20.532, 20.886, -0.49736, 0.74323, 2.0287, 42.439, 22.251, 22.332, 21.068, 0.25964, 1.0555, 1.9167, 12.819, 4.1917, 2.5844, 2.5168, -0.083046, -0.12201, -0.28919, 14.358, 2.8079, 1.7382, 1.139, 0.35091, -0.23474, -0.56486},
          {735.36, 326.41, 421.58, 384.33, 75.618, 0.28376, 3.1108, 691.82, 330.47, 372.98, 308.51, 64.632, -0.98705, 3.9935, 343.53, 122.38, 135.81, 106.83, 26.809, -0.74699, -1.2365, 284.68, 113.13, 135.15, 107.36, 15.103, 1.4333, -1.0935, 72.17, 18.018, 14.517, 10.526, -0.7781, -1.9875, -0.65822, 64.761, 9.7358, 10.497, 7.5272, 0.23142, -2.3566, -1.4484, 260.67, 145.87, 183.03, 188.31, 19.422, -1.2046, 11.946, 243.41, 121.32, 241.49, 159.02, 28.497, 5.7546, 2.513, 54.945, 61.719, 37.982, 43.252, 6.9772, 1.6174, 6.7057, 63.887, 43.208, 40.623, 44.35, 2.9101, 0.42886, 3.584, 12.953, 1.9699, 7.1097, 6.5138, 0.6546, -0.52604, -1.1582, 18.558, 4.2247, 1.839, 5.0753, 0.40136, -1.3279, -1.7542},
          {590.4, 244.36, 304.45, 472.31, 65.796, -3.8187, 3.2228, 558.29, 240.77, 262.66, 402.12, 56.249, -1.4898, 1.661, 310.57, 91.689, 103.46, 83.91, 16.346, 3.0634, -0.56622, 259.08, 86.455, 106.25, 89.738, 6.7099, 3.0943, -0.82195, 67.971, 12.864, 12.256, 6.7021, -0.83123, -1.4876, -0.51765, 55.707, 7.9024, 7.2922, 4.3078, 0.31439, -1.8972, -1.0596, 251.69, 131.05, 156.01, 253.93, 39.046, 1.6336, 7.9355, 242.47, 102.78, 159.02, 278.75, 36.909, 7.423, 9.413, 47.795, 47.104, 26.101, 28.961, 3.956, 4.322, 4.4401, 44.67, 34.455, 26.174, 35.974, 6.2476, 0.6152, 1.1592, 24.445, 2.6719, 7.2723, 7.1011, 1.2355, -0.54132, -0.98656, 24.45, 4.7808, 2.9361, 4.1374, 0.81026, -1.3908, -1.5625},
          {71.951, 34.835, 41.785, 48.488, 95.145, 9.0591, 0.40946, 55.798, 18.046, 24.605, 47.363, 81.288, 6.44, 2.4051, 21.215, 8.469, 8.803, 13.264, 4.2586, 4.1668, -0.71837, 22.684, 0.86701, 6.8339, 8.6257, 0.70982, 2.3154, -0.62876, 0.86465, 1.6783, -0.27769, 0.087101, -0.2602, -0.082467, -0.0051655, 2.0677, -0.39856, 0.68741, -1.3524, -0.1325, -0.42846, -0.029242, 64.285, 36.121, 32.174, 46.09, 47.6, 7.3993, 0.59182, 70.29, 32.963, 28.497, 36.909, 58.101, 9.8701, 5.764, 26.127, 2.9386, 9.3952, 5.9694, -0.46529, 0.89433, -1.1479, 1.4278, 5.1032, 5.594, 6.6898, -0.798, 1.1025, 1.3989, 3.1052, 1.036, 0.62309, 1.5453, -0.042804, 0.047301, 0.12127, 2.0229, 0.26702, 0.029441, 0.16304, -0.38955, -0.11533, 0.10739},
          {11.927, -0.65904, 11.141, 18.147, 21.429, 12.702, 0.18555, 0.83294, -1.9319, -3.5522, 10.771, 15.558, 10.315, 1.9018, 2.8616, 3.1032, 5.4557, 6.8101, 2.1482, 0.95996, -0.14541, 2.9075, -2.3533, 4.5091, 4.8875, 0.54624, 0.39475, 0.27036, 2.3959, 0.30022, 0.61316, 0.3619, 0.26881, 0.053905, 0.14053, 1.1673, -0.21248, 1.0655, -0.51457, -0.0067071, 0.024291, 0.034172, 19.792, 3.2199, 7.8142, 11.735, 8.5172, 9.6832, 0.1532, 20.737, 5.2886, 5.7546, 7.423, 9.8701, 17.707, 7.642, -1.2921, -1.5023, 0.9438, -2.7016, -1.3822, 0.72292, 0.081277, -6.3355, -0.00066012, -3.302, -1.4325, -1.0631, 0.4752, 2.7744, 2.0605, 0.29579, 0.22229, 0.5672, 0.00894, -0.027105, 0.030601, 0.75206, 0.17068, -0.048695, 0.36851, -0.15552, -0.04268, 0.11457},
          {-14.458, -4.6335, 3.1123, -2.8368, 14.992, 0.18724, -1.1904, -2.9666, -3.0465, -1.9771, -9.934, 11.243, 2.9214, 4.0202, -1.8578, -1.0153, 2.435, -7.9251, 0.08067, -1.8804, -0.61237, -0.48433, -1.2775, 0.6616, -3.8669, -0.35507, -0.74842, 1.0019, 1.8843, -0.15419, 0.80303, -0.66478, -0.47041, -0.18041, 0.02918, 0.77555, 0.03009, 0.53877, -0.3243, -0.47437, -0.12282, -0.1274, 10.881, 3.5706, 5.343, 9.3041, -2.8316, 0.42889, 2.42, 16.483, 2.3337, 2.513, 9.413, 5.764, 7.642, 33.127, -5.8942, -2.5339, 1.7456, -4.0418, -0.31585, -1.2046, -0.3069, -4.1096, 0.36461, -2.7325, -5.1929, -0.43165, -0.022493, 4.4641, 1.8153, -0.17395, 0.2346, -1.015, -0.41804, -0.10229, -0.046189, -1.4352, -0.088726, -0.40614, 0.037452, -0.08563, -0.018175, 0.3217},
          {620.87, 214.43, 293.18, 227.12, 127.84, 2.25, -0.67058, 521.66, 178.34, 197.68, 168.43, 101.03, 3.4475, 0.73006, 291.9, 90.784, 81.635, 74.124, 24.146, 3.0705, -0.26002, 218.2, 76.973, 77.715, 60.256, 15.01, -0.40985, 0.35516, 51.997, 12.787, 8.1975, 6.8517, 1.5983, -0.25297, -0.079225, 46.606, 7.3652, 8.1357, 2.8673, 0.63405, -0.75165, -0.85858, 275.56, 69.982, 74.475, 34.596, 33.368, 0.2274, -5.4198, 234.64, 44.359, 54.945, 47.795, 26.127, -1.2921, -5.8942, 324.15, 71.337, 65.164, 56.88, 16.5, 6.0292, 13.561, 237.55, 52.716, 60.867, 45.244, 15.5, 4.7675, 3.6809, 27.708, 3.1279, 5.1462, 3.1798, 1.1233, -0.38403, -1.0726, 28.024, 3.8024, 3.1293, 3.516, 0.30223, -0.77354, -1.1679},
          {360.06, 138.28, 198.55, 173.96, 36.482, -5.901, 0.97196, 321.05, 143.04, 149.32, 129.1, 28.448, -4.7357, 0.16783, 171.51, 62.515, 66.61, 44.307, 15.158, 0.064568, -1.0215, 130.09, 58.721, 66.588, 42.048, 5.125, 0.42403, -1.186, 36.376, 7.3701, 7.316, 4.26, 0.52604, -1.0783, -0.37952, 33.867, 4.2021, 5.7378, 2.9161, 0.21139, -1.2112, -0.88526, 79.762, 42.432, 59.263, 49.934, 3.0505, -5.1978, 0.080851, 56.148, 20.785, 61.719, 47.104, 2.9386, -1.5023, -2.5339, 71.337, 54.908, 31.099, 26.354, 5.9941, 1.0151, 6.829, 75.292, 27.979, 26.947, 26.605, 5.5793, 1.1231, 2.5847, 7.932, -0.18154, 3.8947, 3.7004, 0.59244, -0.34698, -0.77548, 7.8195, 2.536, 1.2708, 3.314, 0.055727, -0.99052, -1.0352},
          {290.08, 118.62, 171.6, 129.36, 44.524, 2.0914, -0.82784, 243.0, 108.02, 124.48, 91.852, 35.807, 1.8262, 0.20274, 128.41, 50.273, 51.857, 35.53, 10.607, 0.30295, -0.48575, 97.004, 42.391, 46.322, 31.724, 7.0764, 0.62336, -0.27268, 28.492, 5.6896, 5.5237, 4.2431, 0.12988, -0.56572, -0.29573, 25.14, 4.1303, 4.2214, 2.7494, -0.041775, -0.9428, -0.55787, 54.755, 36.389, 47.269, 32.065, 7.6223, -1.3848, 0.18361, 35.368, 20.532, 37.982, 26.101, 9.3952, 0.9438, 1.7456, 65.164, 31.099, 39.535, 22.589, 4.7593, 1.0008, 3.441, 61.761, 20.071, 23.594, 17.308, 4.5581, 0.48049, 2.4932, 9.7536, 1.1038, 2.1451, 2.4494, 0.47593, -0.31002, -0.63048, 5.6321, 2.0888, 1.4806, 2.4212, 0.23721, -0.61787, -0.85829},
          {250.94, 105.94, 140.02, 110.52, 30.903, 3.217, -0.30503, 207.31, 96.588, 109.82, 76.678, 24.465, 1.8706, 0.41607, 114.85, 38.665, 43.348, 56.904, 7.1859, 1.3984, -0.21366, 86.608, 35.539, 39.238, 51.266, 4.2616, 1.1382, -0.46758, 19.559, 3.7028, 3.3256, 2.4115, -0.091977, -0.38207, -0.24179, 15.06, 1.7261, 2.5003, 1.8212, 0.020581, -0.74245, -0.52825, 44.666, 46.207, 50.356, 37.328, 7.9668, -2.357, -0.71075, 18.375, 20.886, 43.252, 28.961, 5.9694, -2.7016, -4.0418, 56.88, 26.354, 22.589, 47.819, 5.2986, 1.7587, 5.2481, 54.317, 18.846, 21.394, 27.832, 4.4596, 0.71607, 1.6823, 5.5106, 0.26164, 1.8216, 2.1333, 0.75815, -0.12355, -0.2889, 6.0796, 1.8116, 1.0371, 1.8153, 0.07824, -0.50273, -0.68692},
          {61.003, 18.631, 29.881, 25.177, 6.4452, -3.1405, 0.10064, 40.814, 13.644, 20.915, 15.677, 0.45378, -1.8161, -0.052547, 26.271, 6.1575, 7.3456, 7.1593, 11.908, 0.45334, 0.0022364, 13.734, 5.402, 5.6528, 6.8157, 9.8547, -0.17362, -0.12076, 4.7241, 0.9836, 0.70433, 0.056371, 0.045188, -0.16271, -0.053953, 3.6409, 0.94503, 0.16252, 0.17069, 0.031041, -0.20845, -0.1095, 14.137, 9.4955, 10.086, 9.8105, 1.04, -0.59237, 0.71848, 8.5579, -0.49736, 6.9772, 3.956, -0.46529, -1.3822, -0.31585, 16.5, 5.9941, 4.7593, 5.2986, 9.9175, 0.41022, 0.44785, 17.479, 4.7729, 4.2726, 4.6214, 4.9659, -0.14113, -0.82262, 1.8466, -0.1945, 0.25547, -0.098036, 0.10201, -0.096483, -0.2503, 0.070379, -0.18837, 0.43267, 0.20629, -0.027541, -0.1632, -0.37299},
          {10.469, 4.0438, 5.9723, 10.39, 3.5308, 0.50466, 0.080839, 2.9653, 3.0402, 3.4821, 8.4363, 2.2434, 0.49121, -0.20425, 5.2289, 0.01782, 1.2539, 2.6625, 0.89692, 1.0693, -0.099933, 2.9248, 0.22332, 0.19558, 1.076, 0.57824, 0.72337, -0.18683, 0.97505, 0.11886, 0.26187, -0.065526, 0.083704, 0.04259, 0.017294, 0.79281, -0.039934, 0.024759, 0.0086756, 0.05621, 0.027821, 0.022293, 3.5177, 2.6517, 2.3743, 3.6713, 1.6451, 1.0859, 0.29565, 2.7934, 0.74323, 1.6174, 4.322, 0.89433, 0.72292, -1.2046, 6.0292, 1.0151, 1.0008, 1.7587, 0.41022, 1.9197, 0.33218, 3.1919, 0.85574, 1.2736, 0.78584, 0.39911, 0.62754, -0.11281, 1.1524, 0.22925, 0.10155, 0.099311, 0.17478, -0.020056, 0.0001454, 0.87542, 0.02243, 0.0057581, 0.054649, 0.078881, -0.017753, 0.011246},
          {37.189, 10.772, 17.479, 14.616, 2.5287, -0.82002, -0.69079, 43.988, 14.67, 18.151, 11.986, 3.2774, -0.35001, -0.73198, 16.192, 3.8105, 3.371, 1.7495, -1.6513, 0.44051, -0.0076671, 13.211, 3.4656, 4.7494, 3.2453, -1.9033, 0.47904, -0.077255, 5.6, 0.80341, 0.86627, 0.84958, -0.16992, -0.052336, -0.054629, 4.6739, 0.74638, 0.99737, 1.0929, -0.069968, 0.060043, -0.099593, 12.289, 3.6491, 7.9144, 2.3507, 0.19491, 0.55444, 0.69973, 9.097, 2.0287, 6.7057, 4.4401, -1.1479, 0.081277, -0.3069, 13.561, 6.829, 3.441, 5.2481, 0.44785, 0.33218, 9.166, 14.874, 4.0905, 4.1352, 3.6957, 0.8116, 0.57889, 4.908, 0.65592, -0.1193, 0.31485, -0.1103, 0.051826, 0.0037944, -0.049237, 0.54718, 0.57239, 0.3856, 0.26266, -0.17066, -0.0072469, -0.070075},
          {599.35, 206.82, 301.95, 213.69, 54.388, -10.134, -4.2353, 529.09, 203.19, 234.74, 174.11, 50.526, -4.8751, -1.2896, 306.63, 91.565, 93.588, 56.916, 20.163, 0.32337, -0.47133, 225.7, 87.339, 90.244, 56.884, 11.141, -0.63898, -0.072055, 65.281, 15.411, 10.97, 9.2845, 0.844, -0.98664, -0.47497, 58.882, 10.048, 9.7953, 5.5613, 0.46138, -1.2706, -1.225, 241.02, 58.14, 76.167, 28.6, 2.8777, -5.2919, -0.92691, 209.39, 42.439, 63.887, 44.67, 1.4278, -6.3355, -4.1096, 237.55, 75.292, 61.761, 54.317, 17.479, 3.1919, 14.874, 272.53, 50.531, 60.051, 42.436, 13.976, 2.8181, 4.9264, 21.406, -0.069711, 3.5539, 2.7242, 0.7595, -0.51497, -1.2395, 19.495, 2.4003, 0.89182, 3.7037, 0.17532, -0.93267, -1.878},
          {229.85, 95.52, 128.37, 117.65, 29.749, -3.8521, -0.16146, 217.8, 98.602, 109.27, 97.423, 28.125, -2.6248, 0.76365, 107.95, 40.804, 43.973, 30.793, 8.6779, -0.20251, -0.67414, 90.14, 40.332, 44.08, 29.829, 5.0101, 0.026638, -0.0017108, 21.94, 4.192, 4.3153, 2.7421, 0.033006, -0.71939, -0.28183, 20.641, 2.7834, 3.1991, 1.5993, -0.11339, -0.79178, -0.56679, 60.052, 35.501, 40.283, 38.121, 5.0626, -2.0934, -0.92786, 44.448, 22.251, 43.208, 34.455, 5.1032, -0.00066012, 0.36461, 52.716, 27.979, 20.071, 18.846, 4.7729, 0.85574, 4.0905, 50.531, 31.275, 21.079, 19.762, 4.0779, 0.63449, 3.2255, 5.3076, 0.89108, 2.8264, 2.1599, 0.32574, -0.22399, -0.664, 7.7367, 1.9199, 1.1497, 1.9888, 0.26528, -0.66599, -0.69908},
          {199.88, 98.273, 129.65, 102.34, 19.79, -2.0038, -1.0653, 199.47, 98.918, 115.79, 86.873, 24.488, -0.51727, 0.12642, 101.56, 40.202, 39.246, 22.276, 4.626, 0.078497, -0.35509, 81.801, 36.759, 39.194, 23.721, 3.8849, -0.13133, -0.17464, 20.971, 5.3138, 4.5951, 3.192, -0.21129, -0.50309, -0.19842, 19.919, 3.006, 3.3827, 3.2318, -0.1425, -0.5498, -0.56672, 35.207, 34.959, 34.345, 27.371, 6.2621, -2.2761, -0.18257, 18.021, 22.332, 40.623, 26.174, 5.594, -3.302, -2.7325, 60.867, 26.947, 23.594, 21.394, 4.2726, 1.2736, 4.1352, 60.051, 21.079, 36.474, 17.193, 3.9633, 1.1183, 1.8889, 7.455, 1.6111, 1.7295, 1.6242, 0.48867, -0.10712, -0.45456, 5.1159, 1.1636, 1.6319, 1.9614, 0.3979, -0.23175, -0.50058},
          {243.85, 94.765, 126.06, 129.94, 28.767, -1.2375, 0.12601, 210.85, 93.495, 103.22, 101.11, 24.316, -2.2554, -0.44818, 106.68, 38.688, 44.026, 58.502, 9.6435, 1.3687, -0.22762, 85.969, 37.186, 41.275, 51.644, 4.5202, 0.66333, -0.44657, 20.637, 3.9453, 3.4914, 2.8464, 0.40511, -0.49954, -0.31761, 19.678, 1.7734, 3.1967, 1.8362, 0.20488, -0.85921, -0.62734, 53.015, 33.646, 39.401, 37.631, 3.312, -1.7827, 0.028856, 39.446, 21.068, 44.35, 35.974, 6.6898, -1.4325, -5.1929, 45.244, 26.605, 17.308, 27.832, 4.6214, 0.78584, 3.6957, 42.436, 19.762, 17.193, 39.508, 4.1125, 0.59908, 0.69185, 3.2945, -0.69363, 2.2953, 2.8748, 0.40476, -0.10069, -0.46237, 4.2333, 1.5595, 1.0051, 2.2294, 0.26943, -0.74392, -0.80477},
          {41.32, 13.923, 15.705, 23.635, 2.0666, -2.8201, 0.76592, 33.17, 10.421, 15.858, 11.912, -0.58038, -1.6897, 0.26451, 18.28, 2.3308, 3.1703, 3.0649, 7.7811, 0.38787, 0.12616, 9.481, 3.7176, 2.3396, 2.1975, 7.4898, -0.11929, -0.091251, 5.8331, 0.84058, 0.68455, 0.59069, 0.22676, -0.12764, -0.12623, 4.4309, 1.398, 0.26971, 0.70308, 0.30907, -0.09267, -0.11094, 7.7419, 8.8618, 7.1536, 6.474, 1.0888, -0.20828, 0.71469, -2.3474, 0.25964, 2.9101, 6.2476, -0.798, -1.0631, -0.43165, 15.5, 5.5793, 4.5581, 4.4596, 4.9659, 0.39911, 0.8116, 13.976, 4.0779, 3.9633, 4.1125, 7.3021, -0.054668, -0.54681, 2.1979, 0.23938, 0.31995, 0.071359, 0.15819, -0.083991, -0.14946, 0.42487, -0.092725, 0.48315, 0.22159, 0.10559, -0.065625, -0.23741},
          {10.523, 4.1986, 5.1346, 4.0268, 5.0371, 1.2213, 0.11828, 10.532, 3.8335, 3.8022, 3.5601, 4.8489, 1.0384, 0.16897, 1.3685, 0.0062285, -0.060301, 1.6501, 0.071057, 0.82935, -0.024309, 1.909, -0.27336, -0.22988, 1.2745, -0.16243, 0.54462, 0.024978, 0.67008, 0.26667, 0.1432, -0.013075, 0.1123, 0.0060671, 0.023581, 1.1141, 0.01016, 0.22142, 0.0029951, 0.0054934, -0.0054633, -0.0071837, 3.6796, 0.52737, -0.10241, -1.1192, 0.86766, 0.28787, -0.095207, 4.6638, 1.0555, 0.42886, 0.6152, 1.1025, 0.4752, -0.022493, 4.7675, 1.1231, 0.48049, 0.71607, -0.14113, 0.62754, 0.57889, 2.8181, 0.63449, 1.1183, 0.59908, -0.054668, 1.1354, 0.54314, 0.77513, 0.19546, 0.048054, 0.028894, 0.041566, 0.0026846, -0.020278, 0.62654, 0.29809, -0.019586, 0.11989, 0.065944, 0.01091, 0.047225},
          {17.981, 4.6787, 0.63882, -3.8269, 4.3261, 0.24996, -0.55475, 22.817, 4.7764, 5.4672, -1.8995, 5.7989, 0.38465, 0.69214, -1.071, -0.31346, -0.20161, -3.1382, -2.63, -0.098493, -0.073807, 6.9534, -0.48524, 0.63261, 0.29921, -2.0271, 0.17878, 0.30936, 3.5389, 0.81091, 0.65734, 0.25542, 0.13323, -0.11193, 0.055567, 3.3837, 0.64384, 1.3117, 0.50803, -0.0446, 0.031126, -0.0082096, 1.462, 0.078863, 2.4066, -2.6706, -0.016302, 0.26223, -1.1741, 2.4766, 1.9167, 3.584, 1.1592, 1.3989, 2.7744, 4.4641, 3.6809, 2.5847, 2.4932, 1.6823, -0.82262, -0.11281, 4.908, 4.9264, 3.2255, 1.8889, 0.69185, -0.54681, 0.54314, 8.7891, -0.96787, 0.01943, 0.17173, -0.10037, -0.13612, -0.025259, -0.056009, -0.97856, 0.37666, -0.16058, -0.055656, -0.15256, 0.080084, 0.20464},
          {143.19, 53.682, 68.404, 71.344, 17.922, 5.0165, 0.31164, 112.85, 47.423, 49.705, 55.338, 14.644, 4.8345, 0.075413, 90.531, 26.258, 32.672, 24.093, 6.4658, 2.1879, 0.22498, 70.195, 24.887, 26.982, 20.707, 3.4692, 1.4204, 0.39282, 19.181, 2.9271, 4.2332, 2.2994, 0.020207, 0.26004, 0.01806, 13.364, 1.9259, 1.9868, 1.9676, 0.15581, -0.1205, -0.40604, 45.744, 15.007, 22.578, 22.719, 3.7846, 2.359, 0.08724, 41.917, 12.819, 12.953, 24.445, 3.1052, 2.0605, 1.8153, 27.708, 7.932, 9.7536, 5.5106, 1.8466, 1.1524, 0.65592, 21.406, 5.3076, 7.455, 3.2945, 2.1979, 0.77513, -0.96787, 47.198, 7.3063, 9.1678, 5.3395, 1.3558, 0.06554, 0.16253, 34.035, 6.8281, 5.8692, 5.9116, 0.51682, 0.011871, -0.09616},
          {6.2269, 7.6131, 5.3544, 8.1656, 2.4708, 2.2836, 0.52003, 9.3202, 7.8132, 7.8433, 6.6239, 2.823, 1.9871, 0.4373, 3.2259, 2.1389, 1.3116, 2.3431, -0.66288, 0.43556, 0.12483, 6.6789, 2.1598, 0.7646, 1.4766, 0.69063, 0.3383, 0.29719, 4.2913, 0.94086, 1.007, 1.2907, 0.0067405, 0.10384, 0.014043, 2.5922, 1.0973, 0.73794, 1.139, 0.080736, 0.051167, -0.0073464, 2.4116, 3.468, 3.0612, 1.2236, 0.85673, 1.2239, 0.13083, 1.9638, 4.1917, 1.9699, 2.6719, 1.036, 0.29579, -0.17395, 3.1279, -0.18154, 1.1038, 0.26164, -0.1945, 0.22925, -0.1193, -0.069711, 0.89108, 1.6111, -0.69363, 0.23938, 0.19546, 0.01943, 7.3063, 3.5227, 1.4598, 0.83954, 0.25698, 0.039082, 0.10798, 6.0946, 1.23, 1.365, 0.90233, 0.24358, 0.10835, 0.082853},
          {35.119, 14.443, 19.098, 21.546, 3.6609, -0.43902, -0.026346, 32.119, 14.746, 12.007, 15.337, 0.90556, -0.15729, -0.11741, 20.896, 7.8584, 8.6568, 5.7559, 2.247, 0.2233, -0.16482, 17.539, 8.3888, 8.9444, 4.5171, 0.6484, 0.24556, -0.20712, 6.2892, 1.0611, 1.4724, 0.75447, 0.14982, -0.0059066, -0.018365, 4.6971, 0.57682, 0.82511, 0.419, 0.15508, -0.044558, -0.1131, 7.3729, 4.2108, 6.9955, 8.5723, 0.59211, -0.22258, 0.065507, 9.115, 2.5844, 7.1097, 7.2723, 0.62309, 0.22229, 0.2346, 5.1462, 3.8947, 2.1451, 1.8216, 0.25547, 0.10155, 0.31485, 3.5539, 2.8264, 1.7295, 2.2953, 0.31995, 0.048054, 0.17173, 9.1678, 1.4598, 4.3474, 1.5898, 0.33082, 0.04654, 0.055352, 8.5215, 2.0261, 1.4285, 1.662, 0.18702, -0.1321, -0.062524},
          {42.799, 18.063, 25.934, 24.793, 7.1443, 0.5769, 0.45048, 35.07, 17.266, 18.814, 18.54, 5.7822, 0.33105, 0.0052932, 20.718, 9.3226, 10.709, 7.6622, 1.5228, 0.42178, -0.012139, 16.667, 8.8669, 9.6384, 6.7282, 0.17505, 0.38115, -0.11924, 5.084, 1.053, 1.0957, 1.1983, 0.040406, -0.087589, -0.073037, 4.6421, 0.51327, 0.69222, 0.64428, -0.044632, -0.14107, -0.21328, 7.0657, 2.0913, 7.1552, 6.7185, 1.1395, 0.19659, 0.15295, 8.808, 2.5168, 6.5138, 7.1011, 1.5453, 0.5672, -1.015, 3.1798, 3.7004, 2.4494, 2.1333, -0.098036, 0.099311, -0.1103, 2.7242, 2.1599, 1.6242, 2.8748, 0.071359, 0.028894, -0.10037, 5.3395, 0.83954, 1.5898, 2.6088, 0.20327, 0.0048936, -0.010292, 5.4162, 1.1654, 0.98583, 1.2642, -0.0052886, -0.1292, -0.062383},
          {5.2863, 3.4481, 3.8116, 5.6235, 0.45782, 0.16264, 0.015148, 4.7105, 2.6818, 3.6135, 3.6111, 0.27991, 0.24983, -0.076339, 2.6328, 1.1481, 1.6445, 2.0044, 0.13741, 0.10736, 0.024224, 1.597, 1.4974, 1.1621, 1.5232, -0.055214, 0.1154, -0.033664, 0.69698, 0.010074, 0.1221, 0.059047, 0.12318, 0.011588, 0.022852, 0.30881, 0.054015, -0.057631, 0.03059, 0.087848, -0.0053904, 0.0088775, 1.4226, 0.67638, 1.0086, 0.79185, -0.025025, 0.20827, 0.065019, -0.56456, -0.083046, 0.6546, 1.2355, -0.042804, 0.00894, -0.41804, 1.1233, 0.59244, 0.47593, 0.75815, 0.10201, 0.17478, 0.051826, 0.7595, 0.32574, 0.48867, 0.40476, 0.15819, 0.041566, -0.13612, 1.3558, 0.25698, 0.33082, 0.20327, 0.36003, 0.014729, 0.0037869, 1.3382, 0.14675, 0.3105, 0.18316, 0.06155, -0.005629, -0.0015397},
          {-4.6229, -1.7142, -2.5727, -2.359, -0.051534, 0.10145, 0.0041496, -3.7044, -1.8566, -2.0796, -1.6762, -0.23285, 0.086812, -0.020105, -2.3156, -0.78625, -0.83036, -0.53797, -0.21156, 0.060472, 0.020899, -1.6972, -0.75788, -0.78032, -0.60477, -0.14519, 0.009533, 0.018167, -0.3716, -0.11098, -0.098187, -0.038986, 0.030697, 0.0319, 0.014445, -0.49419, -0.078919, -0.051991, -0.068442, -0.0041836, 0.028906, 0.011814, -0.71599, -0.32391, -0.32331, -0.34562, 0.20469, 0.041336, 0.047782, -0.7101, -0.12201, -0.52604, -0.54132, 0.047301, -0.027105, -0.10229, -0.38403, -0.34698, -0.31002, -0.12355, -0.096483, -0.020056, 0.0037944, -0.51497, -0.22399, -0.10712, -0.10069, -0.083991, 0.0026846, -0.025259, 0.06554, 0.039082, 0.04654, 0.0048936, 0.014729, 0.045891, 0.027021, 0.17679, -0.0063947, 0.048563, 0.008214, 0.019773, 0.016562, 0.017873},
          {-9.6257, -3.7851, -5.2999, -4.5973, -0.61116, 0.34921, 0.032785, -8.6526, -3.6172, -4.2041, -2.9758, -0.86764, 0.2657, -0.023112, -4.4182, -1.4896, -1.5472, -1.2346, -0.59609, 0.078225, 0.027677, -3.4004, -1.4379, -1.5499, -1.3688, -0.48868, 0.04267, 0.0054199, -0.96306, -0.26652, -0.19041, -0.1306, 0.021436, 0.062492, 0.02445, -1.0333, -0.17468, -0.1202, -0.058244, 0.019659, 0.070872, 0.040025, -1.8578, -0.76003, -0.93312, -0.53949, 0.30212, 0.11757, -0.040292, -1.4767, -0.28919, -1.1582, -0.98656, 0.12127, 0.030601, -0.046189, -1.0726, -0.77548, -0.63048, -0.2889, -0.2503, 0.0001454, -0.049237, -1.2395, -0.664, -0.45456, -0.46237, -0.14946, -0.020278, -0.056009, 0.16253, 0.10798, 0.055352, -0.010292, 0.0037869, 0.027021, 0.11528, 0.13536, 0.016809, 0.012251, 0.0054997, 0.037033, 0.034865, 0.058048},
          {133.28, 51.675, 64.367, 62.101, 18.165, 1.9407, 0.47388, 117.48, 51.698, 48.819, 53.414, 14.943, 1.576, 0.10096, 87.942, 26.46, 29.029, 25.571, 4.6406, 1.4999, 0.11097, 73.723, 26.365, 28.708, 23.834, 2.4748, 1.1722, 0.23035, 19.226, 3.3823, 3.6729, 2.1003, 0.41334, 0.15862, 0.01956, 13.588, 2.0352, 2.7857, 1.6538, 0.29247, -0.0072906, -0.37581, 57.782, 13.953, 22.896, 20.71, 3.384, 1.973, -0.26273, 60.276, 14.358, 18.558, 24.45, 2.0229, 0.75206, -1.4352, 28.024, 7.8195, 5.6321, 6.0796, 0.070379, 0.87542, 0.54718, 19.495, 7.7367, 5.1159, 4.2333, 0.42487, 0.62654, -0.97856, 34.035, 6.0946, 8.5215, 5.4162, 1.3382, 0.17679, 0.13536, 37.602, 6.4015, 5.1467, 5.2202, 0.45193, 0.014449, 0.040086},
          {37.996, 11.802, 15.312, 17.339, 1.2876, -0.33875, 0.13898, 33.107, 13.203, 12.428, 15.201, 1.1713, -0.59997, 0.045522, 19.336, 6.1443, 6.5804, 5.4145, 0.85899, 0.29595, 0.022939, 17.53, 6.1641, 6.0698, 5.2343, 0.21581, 0.44881, 0.029465, 6.3498, 1.3027, 1.3688, 0.68332, 0.072891, -0.039299, -0.004528, 5.3577, 0.84488, 1.0464, 0.64624, 0.11583, -0.059036, -0.094462, 8.6029, 2.8665, 4.0914, 4.3316, 0.21238, -0.41942, 0.10695, 9.928, 2.8079, 4.2247, 4.7808, 0.26702, 0.17068, -0.088726, 3.8024, 2.536, 2.0888, 1.8116, -0.18837, 0.02243, 0.57239, 2.4003, 1.9199, 1.1636, 1.5595, -0.092725, 0.29809, 0.37666, 6.8281, 1.23, 2.0261, 1.1654, 0.14675, -0.0063947, 0.016809, 6.4015, 3.2637, 1.167, 1.3238, 0.16761, -0.054958, 0.018141},
          {18.791, 7.9037, 9.8362, 9.4796, 1.4168, 0.23405, 0.21479, 18.814, 6.5307, 9.4889, 6.8244, -0.49166, 0.237, -0.082929, 8.7434, 3.811, 3.5879, 3.6718, 0.45144, 0.31824, 0.088805, 8.0524, 3.146, 3.4663, 3.2578, 0.63971, 0.21989, 0.081961, 3.8913, 0.71598, 0.74787, 0.74958, 0.076877, 0.034302, 0.0082165, 2.4981, 0.59049, 0.38552, 0.67904, -0.026978, 0.0064081, -0.083501, 1.7088, 2.8879, 4.4733, 2.1993, 1.3559, 0.095681, 0.2467, -0.15223, 1.7382, 1.839, 2.9361, 0.029441, -0.048695, -0.40614, 3.1293, 1.2708, 1.4806, 1.0371, 0.43267, 0.0057581, 0.3856, 0.89182, 1.1497, 1.6319, 1.0051, 0.48315, -0.019586, -0.16058, 5.8692, 1.365, 1.4285, 0.98583, 0.3105, 0.048563, 0.012251, 5.1467, 1.167, 2.0879, 1.0594, 0.11576, 0.0047336, -0.034916},
          {26.163, 12.996, 17.723, 16.324, 2.4551, 1.2497, -0.34185, 22.959, 13.055, 12.764, 13.073, 1.0163, 1.0437, -0.38429, 14.27, 6.498, 7.5024, 5.5981, 1.5029, 0.30007, 0.079357, 12.514, 5.7508, 7.0324, 4.9695, 0.58984, 0.35543, 0.062205, 4.2237, 0.90243, 0.97006, 1.0056, 0.035549, -0.0017323, -0.0085739, 3.1702, 0.24447, 0.64401, 0.87296, 0.019691, -0.049861, -0.091985, 3.0477, 1.8955, 4.6094, 3.5506, -0.22282, 0.21232, 0.58737, 2.1647, 1.139, 5.0753, 4.1374, 0.16304, 0.36851, 0.037452, 3.516, 3.314, 2.4212, 1.8153, 0.20629, 0.054649, 0.26266, 3.7037, 1.9888, 1.9614, 2.2294, 0.22159, 0.11989, -0.055656, 5.9116, 0.90233, 1.662, 1.2642, 0.18316, 0.008214, 0.0054997, 5.2202, 1.3238, 1.0594, 2.0747, 0.086583, -0.076052, -0.030465},
          {-0.34789, 0.94846, -0.72862, 1.0705, -1.0232, 0.092468, 0.020948, 0.92148, 0.83693, 0.76508, 0.054607, -1.2139, 0.079588, 0.072075, -0.20407, 0.1471, -0.0082883, -0.27416, -0.24882, 0.023148, 0.025695, 0.32259, 0.2332, -0.26327, -0.40095, 0.06678, 0.026903, 0.079766, 0.91432, 0.19963, 0.20045, 0.14507, 0.11866, 0.015424, 0.026334, 0.46214, 0.16128, 0.072466, 0.13831, 0.07997, 0.019651, 0.03192, -0.48938, 0.89481, 0.51655, 0.46894, -0.044634, -0.19341, -0.15972, -1.369, 0.35091, 0.40136, 0.81026, -0.38955, -0.15552, -0.08563, 0.30223, 0.055727, 0.23721, 0.07824, -0.027541, 0.078881, -0.17066, 0.17532, 0.26528, 0.3979, 0.26943, 0.10559, 0.065944, -0.15256, 0.51682, 0.24358, 0.18702, -0.0052886, 0.06155, 0.019773, 0.037033, 0.45193, 0.16761, 0.11576, 0.086583, 0.34198, 0.0085079, 0.019087},
          {-11.301, -3.0998, -5.4621, -5.4772, -0.73059, 0.4824, -0.022716, -8.5398, -3.5092, -4.1136, -3.9984, -0.027504, 0.46166, 0.071571, -4.6486, -2.008, -1.9768, -1.8913, -0.64683, -0.066968, 0.036326, -3.2991, -1.9164, -2.1225, -1.3856, -0.17324, -0.049482, 0.069385, -0.85104, -0.1217, -0.13667, -0.097954, -0.00014591, 0.05539, 0.020798, -0.86248, -0.028142, -0.04014, 0.021645, 0.0081853, 0.065295, 0.045952, -2.6417, -0.52371, -1.3533, -1.3375, 0.15851, 0.094988, -0.14897, -1.9509, -0.23474, -1.3279, -1.3908, -0.11533, -0.04268, -0.018175, -0.77354, -0.99052, -0.61787, -0.50273, -0.1632, -0.017753, -0.0072469, -0.93267, -0.66599, -0.23175, -0.74392, -0.065625, 0.01091, 0.080084, 0.011871, 0.10835, -0.1321, -0.1292, -0.005629, 0.016562, 0.034865, 0.014449, -0.054958, 0.0047336, -0.076052, 0.0085079, 0.12947, 0.075923},
          {-13.304, -5.0949, -7.5422, -7.5714, -0.34327, 0.2535, 0.069002, -10.899, -4.8197, -6.2523, -5.4826, -0.13759, 0.26377, 0.13305, -5.8726, -2.3817, -2.6177, -2.1, -0.86039, 0.013475, 0.019166, -4.3915, -2.2435, -2.4595, -1.7459, -0.57386, 0.054287, 0.07118, -1.3607, -0.28456, -0.18827, -0.13296, 0.012177, 0.058261, 0.033145, -1.2939, -0.17745, -0.074818, -0.038672, 0.016543, 0.071045, 0.049264, -3.4771, -1.2635, -2.2055, -1.6517, 0.063831, 0.043339, -0.19482, -2.1972, -0.56486, -1.7542, -1.5625, 0.10739, 0.11457, 0.3217, -1.1679, -1.0352, -0.85829, -0.68692, -0.37299, 0.011246, -0.070075, -1.878, -0.69908, -0.50058, -0.80477, -0.23741, 0.047225, 0.20464, -0.09616, 0.082853, -0.062524, -0.062383, -0.0015397, 0.017873, 0.058048, 0.040086, 0.018141, -0.034916, -0.030465, 0.019087, 0.075923, 0.17748},
        };

        set_covariance(BKGCOV);

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2OSLEP_for_stop_36invfb)


  }
}
