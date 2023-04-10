///
///  \author Yang Zhang
///  \date 2021 June
///
///  *********************************************

// Based on http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-20-001/index.html
// Search for supersymmetry in final states with two oppositely charged same-flavor leptons and missing transverse momentum in proton-proton collisions at s√= 13 TeV
//
// * No preselection

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    // This analysis class is also a base class for the class
    // This is the same analysis, but it does not make use of the
    // SR covariance information.
    class Analysis_CMS_13TeV_2OSLEP_137invfb : public Analysis
    {

      protected:

        // Counters for the number of accepted events for each signal region
        std::map<string, EventCounter> _counters = {
          {"SRA_50_100", EventCounter("SRA bveto [50, 100]")},
          {"SRA_100_150", EventCounter("SRA bveto [100, 150]")},
          {"SRA_150_230", EventCounter("SRA bveto [150, 230]")},
          {"SRA_230_300", EventCounter("SRA bveto [230, 300]")},
          {"SRA_300", EventCounter("SRA bveto [300, ~]")},
          {"SRB_50_100", EventCounter("SRB bveto [50, 100]")},
          {"SRB_100_150", EventCounter("SRB bveto [100, 150]")},
          {"SRB_150_230", EventCounter("SRB bveto [150, 230]")},
          {"SRB_230_300", EventCounter("SRB bveto [230, 300]")},
          {"SRB_300", EventCounter("SRB bveto [300, ~]")},
          {"SRC_50_100", EventCounter("SRC bveto [50, 100]")},
          {"SRC_100_150", EventCounter("SRC bveto [100, 150]")},
          {"SRC_150_250", EventCounter("SRC bveto [150, 250]")},
          {"SRC_250", EventCounter("SRC bveto [250, ~]")},
          {"SRAb_50_100", EventCounter("SRA btag [50, 100]")},
          {"SRAb_100_150", EventCounter("SRA btag [100, 150]")},
          {"SRAb_150_230", EventCounter("SRA btag [150, 230]")},
          {"SRAb_230_300", EventCounter("SRA btag [230, 300]")},
          {"SRAb_300", EventCounter("SRA btag [300, ~]")},
          {"SRBb_50_100", EventCounter("SRB btag [50, 100]")},
          {"SRBb_100_150", EventCounter("SRB btag [100, 150]")},
          {"SRBb_150_230", EventCounter("SRB btag [150, 230]")},
          {"SRBb_230_300", EventCounter("SRB btag [230, 300]")},
          {"SRBb_300", EventCounter("SRB btag [300, ~]")},
          {"SRCb_50_100", EventCounter("SRC btag [50, 100]")},
          {"SRCb_100_150", EventCounter("SRC btag [100, 150]")},
          {"SRCb_150_250", EventCounter("SRC btag [150, 250]")},
          {"SRCb_250", EventCounter("SRC btag [250, ~]")},
          {"SRoffZ0j_100_150", EventCounter("SR Off-Z nj=0 [100, 150]")},
          {"SRoffZ0j_150_225", EventCounter("SR Off-Z nj=0 [150, 225]")},
          {"SRoffZ0j_225_300", EventCounter("SR Off-Z nj=0 [225, 300]")},
          {"SRoffZ0j_300", EventCounter("SR Off-Z nj=0 [300, ~]")},
          {"SRoffZj_100_150", EventCounter("SR Off-Z nj>0 [100, 150]")},
          {"SRoffZj_150_225", EventCounter("SR Off-Z nj>0 [150, 225]")},
          {"SRoffZj_225_300", EventCounter("SR Off-Z nj>0 [225, 300]")},
          {"SRoffZj_300", EventCounter("SR Off-Z nj>0 [300, ~]")},
  //        {"SRonZ0j_100_150", EventCounter("SR on-Z nj=0 [100, 150]")},
  //        {"SRonZ0j_150_225", EventCounter("SR on-Z nj=0 [150, 225]")},
  //        {"SRonZ0j_225_300", EventCounter("SR on-Z nj=0 [225, 300]")},
  //        {"SRonZ0j_300", EventCounter("SR on-Z nj=0 [300, ~]")},
  //        {"SRonZj_100_150", EventCounter("SR on-Z nj>0 [100, 150]")},
  //        {"SRonZj_150_225", EventCounter("SR on-Z nj>0 [150, 225]")},
  //        {"SRonZj_225_300", EventCounter("SR on-Z nj>0 [225, 300]")},
  //        {"SRonZj_300", EventCounter("SR on-Z nj>0 [300, ~]")},
        };

      private:

        vector<int> cutFlowVector_1;
        vector<string> cutFlowVector_1_str;
        size_t NCUTS_1;

        vector<int> cutFlowVector_2;
        vector<string> cutFlowVector_2_str;
        size_t NCUTS_2;

        ofstream cutflowFile;

      public:

        // Required detector sim
        static constexpr const char* detector = "CMS";

        struct ptComparison
        {
          bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
        } comparePt;

        struct ptJetComparison
        {
          bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
        } compareJetPt;

        Analysis_CMS_13TeV_2OSLEP_137invfb()
        {
          set_analysis_name("CMS_13TeV_2OSLEP_137invfb");
          set_luminosity(137.);

          NCUTS_1=11;

          for (size_t i=0;i<NCUTS_1;i++)
          {
            cutFlowVector_1.push_back(0);
            cutFlowVector_1_str.push_back("");
          }

          cutFlowVector_1_str[0] = "All events";
          cutFlowVector_1_str[1] = "2 OSSF leptons with $p_{T} > 25(20)$ GeV";
          cutFlowVector_1_str[2] = "$P_T^{\ell\ell}$>50 GeV";
          cutFlowVector_1_str[3] = R"($\Delta R(\ell\ell)$>0.1)"; // string literal R"(...)" to avoid compiler warning about the '\D'
          cutFlowVector_1_str[4] = "$m_{\ell}<$65 or >120 GeV";
          cutFlowVector_1_str[5] = "Leading lepton $p_{T} > 50$ GeV";
          cutFlowVector_1_str[6] = "Thied lepton veto";
          cutFlowVector_1_str[7] = "$M_{T2}(ll) > 100 GeV$";
          cutFlowVector_1_str[8] = "$E^{miss}_{T} > 100 GeV$";
          cutFlowVector_1_str[9] = "$n_j>0$,etc.";
          cutFlowVector_1_str[10] = "$n_j=0$";

          NCUTS_2=4;
          for (size_t i=0;i<NCUTS_2;i++)
          {
            cutFlowVector_2.push_back(0);
            cutFlowVector_2_str.push_back("");
          }
          cutFlowVector_2_str[0] = "All events";
          cutFlowVector_2_str[1] = "Baseline preliminary selections";
          cutFlowVector_2_str[2] = "Baseline lepton selections";
          cutFlowVector_2_str[3] = "Signal regions selections";


        }


        void run(const HEPUtils::Event* event)
        {
          cutFlowVector_1[0]++;
          cutFlowVector_2[0]++;
          // Baseline objects
          double met = event->met();

          // Apply electron efficiency and collect baseline electrons
          const vector<double> aEl={0., DBL_MAX};
          const vector<double> bEl={0., DBL_MAX};
          const vector<double> cEl={0.9};
          HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
          vector<const HEPUtils::Particle*> baselineElectrons;
          for (const HEPUtils::Particle* electron : event->electrons())
          {
            bool isEl=has_tag(_eff2dEl, fabs(electron->eta()), electron->pT());
            if (isEl && electron->pT()>8.
            && fabs(electron->eta())<2.4
            && (fabs(electron->eta())<1.4 || fabs(electron->eta())>1.6) )
            baselineElectrons.push_back(electron);
          }


          // Apply muon efficiency and collect baseline muons
          const vector<double> aMu={0., DBL_MAX};
          const vector<double> bMu={0., DBL_MAX};
          const vector<double> cMu={0.99};
          HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
          vector<const HEPUtils::Particle*> baselineMuons;
          for (const HEPUtils::Particle* muon : event->muons())
          {
            bool isMu=has_tag(_eff2dMu, fabs(muon->eta()), muon->pT());
            if (isMu && muon->pT()>8.
             && fabs(muon->eta())<2.4
             && (fabs(muon->eta())<1.4 || fabs(muon->eta())>1.6) )
             baselineMuons.push_back(muon);
          }

          // Baseline photons
          vector<const HEPUtils::Particle*> baselinePhotons;
          for (const HEPUtils::Particle* photon : event->photons())
          {
            if (photon->pT()>50.
             && fabs(photon->eta())<2.4
             && (fabs(photon->eta())<1.4 || fabs(photon->eta())>1.6)
             && event->missingmom().deltaPhi(photon->mom())>0.4 )
             baselinePhotons.push_back(photon);
          }

          // Baseline jets
          vector<const HEPUtils::Jet*> baselineJets;
          for (const HEPUtils::Jet* jet : event->jets())
          {
            if (jet->pT()>25. && fabs(jet->eta())<2.4) baselineJets.push_back(jet);
          }

          // Signal objects
          vector<const HEPUtils::Particle*> signalLeptons;
          vector<const HEPUtils::Particle*> signalElectrons;
          vector<const HEPUtils::Particle*> signalMuons;
          vector<const HEPUtils::Jet*> signalJets25; // used in regions in which the presence of jets is vetoed
          vector<const HEPUtils::Jet*> signalJets; // used to construct regions aiming for topologies with jets.
          vector<const HEPUtils::Jet*> signalBJets;

          // Signal electrons
          for (size_t iEl=0;iEl<baselineElectrons.size();iEl++)
          {
            if (baselineElectrons.at(iEl)->pT()>20.) signalElectrons.push_back(baselineElectrons.at(iEl));
          }

          // Signal muons
          for (size_t iMu=0;iMu<baselineMuons.size();iMu++)
          {
            if (baselineMuons.at(iMu)->pT()>20.) signalMuons.push_back(baselineMuons.at(iMu));
          }

          // Signal jets and b-jets
          sort(baselinePhotons.begin(),baselinePhotons.end(),comparePt);
          for (size_t iJet=0;iJet<baselineJets.size();iJet++)
          {
            bool overlap=false;
            for (size_t iLe=0;iLe<signalElectrons.size();iLe++)
            {
              if (signalElectrons.at(iLe)->mom().deltaR_eta(baselineJets.at(iJet)->mom())<0.4)overlap=true;
            }
            for (size_t iLe=0;iLe<signalMuons.size();iLe++)
            {
              if (signalMuons.at(iLe)->mom().deltaR_eta(baselineJets.at(iJet)->mom())<0.4)overlap=true;
            }
            if (baselinePhotons.size()!=0)
            {
              if (baselinePhotons.at(0)->mom().deltaR_eta(baselineJets.at(iJet)->mom())<0.4)overlap=true;
            }
            if (!overlap)
            {
              signalJets25.push_back(baselineJets.at(iJet));
              if (baselineJets.at(iJet)->pT() >= 35.)
              {
                signalJets.push_back(baselineJets.at(iJet));
              }
              // For the b-jets, jets down to pT > 25 should be considered
              if (baselineJets.at(iJet)->btag())signalBJets.push_back(baselineJets.at(iJet));
            }
          }
  //        CMS::applyCSVv2MediumBtagEffAndMisId(signalJets25,signalBJets);

          // Signal leptons = electrons + muons
          signalLeptons=signalElectrons;
          signalLeptons.insert(signalLeptons.end(),signalMuons.begin(),signalMuons.end());

          sort(signalLeptons.begin(),signalLeptons.end(),comparePt);
          sort(signalJets25.begin(),signalJets25.end(),compareJetPt);
          sort(signalJets.begin(),signalJets.end(),compareJetPt);
          sort(signalBJets.begin(),signalBJets.end(),compareJetPt);

          size_t nSignalLeptons = signalLeptons.size();
          size_t nSignalJets25 = signalJets25.size();
          size_t nSignalJets = signalJets.size();
          size_t nSignalBJets = signalBJets.size();


          // ###### Baseline selection ########
          // the presence of two OS leptons with > 25 (20) GeV for the highest (next-to-highest) pT lepton

          // the two highest pT OS leptons are required to have the same flavor
          if (nSignalLeptons<2) return;
          if (signalLeptons[0]->pid() + signalLeptons[1]->pid() !=0) return;
          if (signalLeptons[0]->pT()<25) return;
          cutFlowVector_1[1]++;

          double pTll = (signalLeptons[0]->mom()+signalLeptons[1]->mom()).pT();
          if (pTll < 50) return;
          cutFlowVector_1[2]++;

          // the two highest pT leptons are required to be separated by a distance dR>0.1
          if (signalLeptons[0]->mom().deltaR_eta(signalLeptons[1]->mom())<0.1) return;
          cutFlowVector_1[3]++;

          double mll = (signalLeptons[0]->mom()+signalLeptons[1]->mom()).m();
          if (mll < 20) return;

          double mT2=get_mT2(signalLeptons,event->missingmom());
          double HT=0;
          for (size_t iJet=0; iJet<nSignalJets; iJet++){
            HT += signalJets[iJet]->pT();
          }

          cutFlowVector_2[1]++;
          // ###### on-Z regions ########
          if (mll>86 and mll<96 and nSignalLeptons==2 and met > 50 and nSignalJets >1 and event->missingmom().deltaR_eta(signalJets.at(0)->mom())>0.4 )
          {
            cutFlowVector_2[2]++;
            if (nSignalBJets==0)
            {
              if (mT2>80)
              {
                if (HT>500)
                {
                  cutFlowVector_2[3]++;
                  if ( nSignalJets < 4 )
                  {
                    if (met<100) _counters.at("SRA_50_100").add_event(event);
                    else if (met<150) _counters.at("SRA_100_150").add_event(event);
                    else if (met<230) _counters.at("SRA_150_230").add_event(event);
                    else if (met<300) _counters.at("SRA_230_300").add_event(event);
                    else _counters.at("SRA_300").add_event(event);
                  }
                  else if ( nSignalJets < 6 )
                  {
                    if (met<100) _counters.at("SRB_50_100").add_event(event);
                    else if (met<150) _counters.at("SRB_100_150").add_event(event);
                    else if (met<230) _counters.at("SRB_150_230").add_event(event);
                    else if (met<300) _counters.at("SRB_230_300").add_event(event);
                    else _counters.at("SRB_300").add_event(event);
                  }
                }
                if (nSignalJets>5)
                {
                  if (met<100) _counters.at("SRC_50_100").add_event(event);
                  else if (met<150) _counters.at("SRC_100_150").add_event(event);
                  else if (met<250) _counters.at("SRC_150_250").add_event(event);
                  else _counters.at("SRC_250").add_event(event);
                }
              }
            }
            else // nSignalBJets > 0
            {
              if (mT2>100)
              {
                if (HT>200)
                {
                  if ( nSignalJets < 4 )
                  {
                    if (met<100) _counters.at("SRAb_50_100").add_event(event);
                    else if (met<150) _counters.at("SRAb_100_150").add_event(event);
                    else if (met<230) _counters.at("SRAb_150_230").add_event(event);
                    else if (met<300) _counters.at("SRAb_230_300").add_event(event);
                    else _counters.at("SRAb_300").add_event(event);
                  }
                  else if ( nSignalJets < 6 )
                  {
                    if (met<100) _counters.at("SRBb_50_100").add_event(event);
                    else if (met<150) _counters.at("SRBb_100_150").add_event(event);
                    else if (met<230) _counters.at("SRBb_150_230").add_event(event);
                    else if (met<300) _counters.at("SRBb_230_300").add_event(event);
                    else _counters.at("SRBb_300").add_event(event);
                  }
                }
                if (nSignalJets>5)
                {
                  if (met<100) _counters.at("SRCb_50_100").add_event(event);
                  else if (met<150) _counters.at("SRCb_100_150").add_event(event);
                  else if (met<250) _counters.at("SRCb_150_250").add_event(event);
                  else _counters.at("SRCb_250").add_event(event);
                }
              }
            }
          }

          // ###### slepton region #######
          if (mll<65 or mll>120)
          {
            cutFlowVector_1[4]++;
            if (signalLeptons[0]->pT()>50)
            {
              cutFlowVector_1[5]++;
              if (nSignalLeptons==2)
              {
                cutFlowVector_1[6]++;
                if (mT2>100)
                {
                  cutFlowVector_1[7]++;
                  if (met>50)
                  {
                    cutFlowVector_1[8]++;
                    if (nSignalBJets==0){
                      if (nSignalJets25>0 and event->missingmom().deltaR_eta(signalJets25.at(0)->mom())>0.4
                        and (signalLeptons[1]->pT()/signalJets25[0]->pT())>1.2 )
                      {
                        cutFlowVector_1[9]++;
                        if (mT2<150) _counters.at("SRoffZj_100_150").add_event(event);
                        else if (mT2<225) _counters.at("SRoffZj_150_225").add_event(event);
                        else if (mT2<300) _counters.at("SRoffZj_225_300").add_event(event);
                        else _counters.at("SRoffZj_300").add_event(event);
                      }
                      if (nSignalJets25==0)
                      {
                        cutFlowVector_1[10]++;
                        if (mT2<150) _counters.at("SRoffZ0j_100_150").add_event(event);
                        else if (mT2<225) _counters.at("SRoffZ0j_150_225").add_event(event);
                        else if (mT2<300) _counters.at("SRoffZ0j_225_300").add_event(event);
                        else _counters.at("SRoffZ0j_300").add_event(event);
                      }
                    }
                  }
                }
              }
            }
          }
//          // Contral regions
//          if (mll>65 and mll<120)
//          {
//            if (signalLeptons[0]->pT()>50)
//            {
//              if (nSignalLeptons==2)
//              {
//                if (mT2>100)
//                {
//                  if (met>50)
//                  {
//                  if (nSignalBJets==0)
//                  {
//                    if (nSignalJets>0 and event->missingmom().deltaR_eta(signalJets.at(0)->mom())>0.4
//                      and signalLeptons[1]->pT()/signalJets[0]->pT()>1.2 )
//                    {
//                      if (mT2<150) _counters.at("SRonZj_100_150").add_event(event);
//                      else if (mT2<225) _counters.at("SRonZj_150_225").add_event(event);
//                      else if (mT2<300) _counters.at("SRonZj_225_300").add_event(event);
//                      else _counters.at("SRonZj_300").add_event(event);
//                    }
//                    if (nSignalJets25==0)
//                    {
//                      if (mT2<150) _counters.at("SRonZ0j_100_150").add_event(event);
//                      else if (mT2<225) _counters.at("SRonZ0j_150_225").add_event(event);
//                      else if (mT2<300) _counters.at("SRonZ0j_225_300").add_event(event);
//                      else _counters.at("SRonZ0j_300").add_event(event);
//                    }
//                  }
//                }
//              }
//            }
//          }
//        }

        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
          const Analysis_CMS_13TeV_2OSLEP_137invfb* specificOther
                  = dynamic_cast<const Analysis_CMS_13TeV_2OSLEP_137invfb*>(other);

          for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

          if (NCUTS_1 != specificOther->NCUTS_1) NCUTS_1 = specificOther->NCUTS_1;
          for (size_t j = 0; j < NCUTS_1; j++)
          {
            cutFlowVector_1[j] += specificOther->cutFlowVector_1[j];
            cutFlowVector_1_str[j] = specificOther->cutFlowVector_1_str[j];
          }

          if (NCUTS_2 != specificOther->NCUTS_2) NCUTS_2 = specificOther->NCUTS_2;
          for (size_t j = 0; j < NCUTS_2; j++)
          {
            cutFlowVector_2[j] += specificOther->cutFlowVector_2[j];
            cutFlowVector_2_str[j] = specificOther->cutFlowVector_2_str[j];
          }

        }


        virtual void collect_results()
        {
          for (size_t i=0;i<NCUTS_1;i++)
          {
            cout << i << "\t" << cutFlowVector_1_str[i] << "\t" << cutFlowVector_1[i] << endl;
          }
          cout << "=========================" << endl;
          for (size_t i=0;i<NCUTS_2;i++)
          {
            cout << i << "\t" << cutFlowVector_2_str[i] << "\t" << cutFlowVector_2[i] << endl;
          }

          add_result(SignalRegionData(_counters.at("SRA_50_100"),   1261., {1261., 41.}));
          add_result(SignalRegionData(_counters.at("SRA_100_150"),  186.,  {160.,  16.}));
          add_result(SignalRegionData(_counters.at("SRA_150_230"),  27.,   {28.8,  5.}));
          add_result(SignalRegionData(_counters.at("SRA_230_300"),  5.,    {4.2,   1.}));
          add_result(SignalRegionData(_counters.at("SRA_300"),      14.,   {9.6,   3.2}));
          add_result(SignalRegionData(_counters.at("SRAb_50_100"),  616.,  {616.,  28.}));
          add_result(SignalRegionData(_counters.at("SRAb_100_150"), 148.,  {128.,  10.}));
          add_result(SignalRegionData(_counters.at("SRAb_150_230"), 42.,   {31.4, 3.8}));
          add_result(SignalRegionData(_counters.at("SRAb_230_300"), 10.,   {6.3, 1.7}));
          add_result(SignalRegionData(_counters.at("SRAb_300"),     4.,    {4.1, 1.2}));
          add_result(SignalRegionData(_counters.at("SRB_50_100"),   700.,  {700., 31.}));
          add_result(SignalRegionData(_counters.at("SRB_100_150"),  108.,  {108.2, 7.1}));
          add_result(SignalRegionData(_counters.at("SRB_150_230"),  18.,   {15.7, 2.3}));
          add_result(SignalRegionData(_counters.at("SRB_230_300"),  2.,    {2.2, 0.7}));
          add_result(SignalRegionData(_counters.at("SRB_300"),      3.,    {3.0, 1.0}));
          add_result(SignalRegionData(_counters.at("SRBb_50_100"),  225.,  {225., 16.}));
          add_result(SignalRegionData(_counters.at("SRBb_100_150"), 69.,   {65., 16.}));
          add_result(SignalRegionData(_counters.at("SRBb_150_230"), 17.,   {22.7, 4.2}));
          add_result(SignalRegionData(_counters.at("SRBb_230_300"), 3.,    {5.3, 1.4}));
          add_result(SignalRegionData(_counters.at("SRBb_300"),     5.,    {2.1, 0.6}));
          add_result(SignalRegionData(_counters.at("SRC_50_100"),   135.,  {135., 14.}));
          add_result(SignalRegionData(_counters.at("SRC_100_150"),  19.,   {29.7, 5.6}));
          add_result(SignalRegionData(_counters.at("SRC_150_250"),  5.,    {2.4, 0.6}));
          add_result(SignalRegionData(_counters.at("SRC_250"),      1.,    {0.6, 0.3}));
          add_result(SignalRegionData(_counters.at("SRCb_50_100"),  41.,   {41., 7.1}));
          add_result(SignalRegionData(_counters.at("SRCb_100_150"), 14.,   {10.7, 2.1}));
          add_result(SignalRegionData(_counters.at("SRCb_150_250"), 5.,    {3.8, 0.9}));
          add_result(SignalRegionData(_counters.at("SRCb_250"),     1.,    {0.7, 0.2}));

          add_result(SignalRegionData(_counters.at("SRoffZ0j_100_150"),228.,  {198., 37.}));
          add_result(SignalRegionData(_counters.at("SRoffZ0j_150_225"),99.,   {120., 16.}));
          add_result(SignalRegionData(_counters.at("SRoffZ0j_225_300"),29.,   {20.8, 4.1}));
          add_result(SignalRegionData(_counters.at("SRoffZ0j_300"),    17.,   {9.3, 2.3}));
          add_result(SignalRegionData(_counters.at("SRoffZj_100_150"), 283.,  {245., 33.}));
          add_result(SignalRegionData(_counters.at("SRoffZj_150_225"), 97.,   {112., 12.}));
          add_result(SignalRegionData(_counters.at("SRoffZj_225_300"), 19.,   {14.7, 3.3}));
          add_result(SignalRegionData(_counters.at("SRoffZj_300"),     8.,    {8.7, 2.3}));
//          add_result(SignalRegionData(_counters.at("SRonZ0j_100_150"), 1059., {1059., 34.}));
//          add_result(SignalRegionData(_counters.at("SRonZ0j_150_225"), 573.,  {573., 26.}));
//          add_result(SignalRegionData(_counters.at("SRonZ0j_225_300"), 116.,  {116., 11.}));
//          add_result(SignalRegionData(_counters.at("SRonZ0j_300"),     47.,   {47.5, 5.3}));
//          add_result(SignalRegionData(_counters.at("SRonZj_100_150"),  674.,  {674., 29.}));
//          add_result(SignalRegionData(_counters.at("SRonZj_150_225"),  241.,  {241., 16.}));
//          add_result(SignalRegionData(_counters.at("SRonZj_225_300"),  72.,   {72., 8.2}));
//          add_result(SignalRegionData(_counters.at("SRonZj_300"),      30.,   {34.9, 3.8}));

        }


        double get_mT2(vector<const HEPUtils::Particle*> leptons, HEPUtils::P4 met)
        {
          double mT2=0;
          double pLep0[3] = {leptons.at(0)->mass(), leptons.at(0)->mom().px(), leptons.at(0)->mom().py()};
          double pLep1[3] = {leptons.at(1)->mass(), leptons.at(1)->mom().px(), leptons.at(1)->mom().py()};
          double pMiss[3] = {0., met.px(), met.py() };
          double mn = 0.;

          mt2_bisect::mt2 mt2_calc;
          mt2_calc.set_momenta(pLep0,pLep1,pMiss);
          mt2_calc.set_mn(mn);
          mT2 = mt2_calc.get_mt2();
          return mT2;
        }


      protected:
        void analysis_specific_reset()
        {

          for (auto& pair : _counters) { pair.second.reset(); }

          std::fill(cutFlowVector_1.begin(), cutFlowVector_1.end(), 0);
          std::fill(cutFlowVector_2.begin(), cutFlowVector_2.end(), 0);
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2OSLEP_137invfb)

    //
    // Derived analysis class for the Strong-production on-Z search regions
    //
    class Analysis_CMS_13TeV_2OSLEP_Strong_Production_137invfb : public Analysis_CMS_13TeV_2OSLEP_137invfb
    {

      public:
        Analysis_CMS_13TeV_2OSLEP_Strong_Production_137invfb()
        {
          set_analysis_name("CMS_13TeV_2OSLEP_Strong_Production_137invfb");
        }

        virtual void collect_results()
        {

          add_result(SignalRegionData(_counters.at("SRA_50_100"),   1261., {1261., 41.}));
          add_result(SignalRegionData(_counters.at("SRA_100_150"),  186.,  {160.,  16.}));
          add_result(SignalRegionData(_counters.at("SRA_150_230"),  27.,   {28.8,  5.}));
          add_result(SignalRegionData(_counters.at("SRA_230_300"),  5.,    {4.2,   1.}));
          add_result(SignalRegionData(_counters.at("SRA_300"),      14.,   {9.6,   3.2}));
          add_result(SignalRegionData(_counters.at("SRAb_50_100"),  616.,  {616.,  28.}));
          add_result(SignalRegionData(_counters.at("SRAb_100_150"), 148.,  {128.,  10.}));
          add_result(SignalRegionData(_counters.at("SRAb_150_230"), 42.,   {31.4, 3.8}));
          add_result(SignalRegionData(_counters.at("SRAb_230_300"), 10.,   {6.3, 1.7}));
          add_result(SignalRegionData(_counters.at("SRAb_300"),     4.,    {4.1, 1.2}));
          add_result(SignalRegionData(_counters.at("SRB_50_100"),   700.,  {700., 31.}));
          add_result(SignalRegionData(_counters.at("SRB_100_150"),  108.,  {108.2, 7.1}));
          add_result(SignalRegionData(_counters.at("SRB_150_230"),  18.,   {15.7, 2.3}));
          add_result(SignalRegionData(_counters.at("SRB_230_300"),  2.,    {2.2, 0.7}));
          add_result(SignalRegionData(_counters.at("SRB_300"),      3.,    {3.0, 1.0}));
          add_result(SignalRegionData(_counters.at("SRBb_50_100"),  225.,  {225., 16.}));
          add_result(SignalRegionData(_counters.at("SRBb_100_150"), 69.,   {65., 16.}));
          add_result(SignalRegionData(_counters.at("SRBb_150_230"), 17.,   {22.7, 4.2}));
          add_result(SignalRegionData(_counters.at("SRBb_230_300"), 3.,    {5.3, 1.4}));
          add_result(SignalRegionData(_counters.at("SRBb_300"),     5.,    {2.1, 0.6}));
          add_result(SignalRegionData(_counters.at("SRC_50_100"),   135.,  {135., 14.}));
          add_result(SignalRegionData(_counters.at("SRC_100_150"),  19.,   {29.7, 5.6}));
          add_result(SignalRegionData(_counters.at("SRC_150_250"),  5.,    {2.4, 0.6}));
          add_result(SignalRegionData(_counters.at("SRC_250"),      1.,    {0.6, 0.3}));
          add_result(SignalRegionData(_counters.at("SRCb_50_100"),  41.,   {41., 7.1}));
          add_result(SignalRegionData(_counters.at("SRCb_100_150"), 14.,   {10.7, 2.1}));
          add_result(SignalRegionData(_counters.at("SRCb_150_250"), 5.,    {3.8, 0.9}));
          add_result(SignalRegionData(_counters.at("SRCb_250"),     1.,    {0.7, 0.2}));

          // Covariance matrix
          static const vector< vector<double> > BKGCOV = {
            {1.4521e+03, 5.5203e+01, 6.0650e+00, 2.1085e-01, 1.1549e+01, -1.2563e+01, 1.4640e+01, 9.2761e+00, -3.3911e+00, -2.7049e-01, 5.4988e+01, 1.2710e+01, 5.0895e+00, 1.8274e+00, 1.3101e+00, -1.8685e+01, 9.3332e+00, 3.0903e+00, 1.9607e-01, 3.1051e-01, -2.5945e+01, -6.0308e-01, -1.3191e+00, -1.7823e-01, -9.3416e+00, 6.5442e-01, 5.3011e-01, 2.9185e-01},
            {5.5203e+01, 8.9511e+01, 1.1500e+00, 1.2805e-01, 1.3616e+00, -6.7154e+00, -5.0154e+00, 1.5398e+00, 1.6068e-01, -1.2968e+00, -1.8061e+01, 8.2175e-01, -2.6257e-01, 3.4625e-01, 1.0484e+00, -1.8691e+00, -2.6804e+00, 1.6552e+00, -9.2475e-01, 2.9139e-01, 1.1311e+01, 4.6062e+00, 1.6555e-01, -6.0225e-02, 5.7873e+00, 7.0825e-01, -7.4564e-01, -9.4884e-02},
            {6.0650e+00, 1.1500e+00, 1.2920e+01, 5.0631e-01, 6.7628e-01, 2.0637e+00, 7.6292e-01, 1.2700e+00, 3.4177e-01, -2.1569e-01, -4.3552e+00, -1.8029e+00, 2.3807e-01, 1.9466e-01, 5.7548e-02, -2.8882e-01, 1.8522e+00, -1.3725e-01, -6.1019e-02, -4.8209e-02, 3.0286e+00, -4.7960e-01, -4.6834e-03, 7.4520e-02, 1.0201e-01, -1.3870e-01, -1.2913e-02, 6.4226e-02},
            {2.1085e-01, 1.2805e-01, 5.0631e-01, 1.2694e+00, 5.1945e-01, -2.9795e+00, 6.3830e-01, 1.3851e-01, -1.2063e-01, 1.3857e-01, -7.0635e-01, 1.9933e-01, -3.7357e-02, 1.2077e-01, 4.1778e-01, 7.6811e-01, 4.3755e-01, 1.8244e-01, -4.1748e-02, 5.8184e-02, 7.0573e-01, 2.2611e-01, 3.2559e-02, 5.8350e-03, 3.2783e-01, 2.0513e-01, 9.6306e-02, -1.6076e-02},
            {1.1549e+01, 1.3616e+00, 6.7628e-01, 5.1945e-01, 5.7572e+00, 5.3280e-01, 1.4637e+00, 4.3437e-01, 4.5808e-01, -6.6341e-02, 5.9487e-01, -1.8286e-01, -6.9414e-02, 2.9026e-01, 2.7794e-01, 2.4874e+00, 7.5698e-01, 1.1291e+00, 1.0347e-01, 2.0091e-01, 7.6066e-01, -4.2736e-01, 1.8125e-01, 5.6105e-02, 2.3908e-01, 3.0974e-01, 1.2836e-01, 1.1331e-02},
            {-1.2563e+01, -6.7154e+00, 2.0637e+00, -2.9795e+00, 5.3280e-01, 5.3853e+02, 3.9787e+01, 5.8103e+00, -1.7162e+00, 4.6307e-01, -3.2551e+00, 1.5229e+00, 2.4401e+00, -4.3367e-01, -2.8654e+00, 2.9285e+01, -1.9252e+00, -1.5521e+00, 7.2142e-01, -2.6510e-01, -3.5144e+01, 3.4202e+00, 5.0759e-01, 1.2089e-01, -1.1291e+01, 1.1117e+00, 8.8448e-01, -2.3650e-01},
            {1.4640e+01, -5.0154e+00, 7.6292e-01, 6.3830e-01, 1.4637e+00, 3.9787e+01, 5.8997e+01, 2.4435e+00, -4.6743e-01, 9.8687e-01, 1.7262e+01, -3.7466e+00, -1.2577e-01, 9.0076e-01, 8.1680e-01, -8.6186e+00, -5.9311e-01, 1.8444e+00, -6.8109e-01, -8.3176e-02, -1.3621e+01, -1.4951e+00, -2.4687e-01, -3.8413e-02, 2.8754e+00, 1.7971e+00, 4.8273e-01, 5.8252e-02},
            {9.2761e+00, 1.5398e+00, 1.2700e+00, 1.3851e-01, 4.3437e-01, 5.8103e+00, 2.4435e+00, 8.5267e+00, 4.0394e-01, 1.0102e-01, 5.1706e+00, -9.6494e-02, 1.0258e-01, -3.7319e-02, -1.5961e-01, -1.2869e+00, 1.8887e-01, 1.5304e+00, 1.5826e-01, -1.5827e-01, 2.2073e+00, 4.4216e-01, 2.9077e-01, 1.1504e-01, -1.9350e+00, -4.1133e-01, 1.7511e-01, 3.0503e-02},
            {-3.3911e+00, 1.6068e-01, 3.4177e-01, -1.2063e-01, 4.5808e-01, -1.7162e+00, -4.6743e-01, 4.0394e-01, 2.0618e+00, -1.3859e-01, 4.3295e+00, 8.8253e-01, -1.1370e-01, 7.2044e-02, -1.1193e-01, 1.5744e+00, 9.3435e-01, 5.9132e-02, 5.0289e-02, 2.5199e-02, 5.4717e-01, -3.3770e-01, 2.0771e-02, -2.0063e-02, -4.1563e-01, -5.1919e-02, 7.8065e-02, 5.6252e-03},
            {-2.7049e-01, -1.2968e+00, -2.1569e-01, 1.3857e-01, -6.6341e-02, 4.6307e-01, 9.8687e-01, 1.0102e-01, -1.3859e-01, 1.2260e+00, -4.2174e-01, 1.5263e-01, -2.7637e-01, 9.7971e-03, 1.1605e-01, -1.6137e+00, -9.7427e-02, 1.6562e-01, 1.6255e-01, -2.9108e-02, -3.1936e-01, 6.2055e-01, 3.9837e-02, 4.8745e-03, 1.0483e-01, 3.9951e-01, 5.1592e-02, 7.7439e-03},
            {5.4988e+01, -1.8061e+01, -4.3552e+00, -7.0635e-01, 5.9487e-01, -3.2551e+00, 1.7262e+01, 5.1706e+00, 4.3295e+00, -4.2174e-01, 4.9938e+02, 5.5006e+01, 5.6719e+00, 1.6080e+00, 2.1410e+00, 3.5895e+00, -1.6232e+01, -1.3038e+00, -9.3336e-02, -7.6029e-01, 1.5524e+01, -1.4310e+00, 1.2741e-01, 3.8043e-01, -1.0665e+01, 1.2716e+00, -4.1845e-01, 1.8484e-01},
            {1.2710e+01, 8.2175e-01, -1.8029e+00, 1.9933e-01, -1.8286e-01, 1.5229e+00, -3.7466e+00, -9.6494e-02, 8.8253e-01, 1.5263e-01, 5.5006e+01, 3.3230e+01, -1.0250e-01, 4.4840e-01, 9.8534e-01, 1.5739e+00, -4.7827e+00, 8.2120e-01, 8.6277e-01, 2.0358e-02, -2.9515e-01, 1.0928e+00, 6.8551e-02, 1.8299e-02, -3.3840e+00, -2.8414e-01, 1.6747e-02, 1.8402e-02},
            {5.0895e+00, -2.6257e-01, 2.3807e-01, -3.7357e-02, -6.9414e-02, 2.4401e+00, -1.2577e-01, 1.0258e-01, -1.1370e-01, -2.7637e-01, 5.6719e+00, -1.0250e-01, 2.7663e+00, 4.0676e-02, 6.8720e-02, -4.8544e-01, 5.1153e-02, 6.0445e-01, -7.7956e-02, 4.9290e-03, 9.6107e-01, -4.1676e-01, 1.6022e-02, 3.6403e-02, -2.0987e-01, -1.2231e-01, -1.1477e-01, 1.2197e-02},
            {1.8274e+00, 3.4625e-01, 1.9466e-01, 1.2077e-01, 2.9026e-01, -4.3367e-01, 9.0076e-01, -3.7319e-02, 7.2044e-02, 9.7971e-03, 1.6080e+00, 4.4840e-01, 4.0676e-02, 5.4834e-01, 2.6468e-01, -1.4157e-01, 2.2605e-01, 4.7266e-01, 5.9822e-02, 4.0220e-02, 1.4850e-01, -9.2780e-02, -7.8103e-03, 5.5901e-03, 5.2711e-01, 3.1416e-02, 6.8599e-02, 6.9622e-03},
            {1.3101e+00, 1.0484e+00, 5.7548e-02, 4.1778e-01, 2.7794e-01, -2.8654e+00, 8.1680e-01, -1.5961e-01, -1.1193e-01, 1.1605e-01, 2.1410e+00, 9.8534e-01, 6.8720e-02, 2.6468e-01, 1.6921e+00, -5.1457e-01, 1.6452e-01, 2.0942e-01, 1.9817e-01, 9.8534e-02, -7.5988e-01, 3.1519e-01, 2.0297e-02, 3.3985e-02, -4.6371e-01, -1.6694e-01, 9.2917e-02, 3.1600e-03},
            {-1.8685e+01, -1.8691e+00, -2.8882e-01, 7.6811e-01, 2.4874e+00, 2.9285e+01, -8.6186e+00, -1.2869e+00, 1.5744e+00, -1.6137e+00, 3.5895e+00, 1.5739e+00, -4.8544e-01, -1.4157e-01, -5.1457e-01, 2.0592e+02, 1.6212e+01, 2.9808e+00, 4.1373e+00, 7.3180e-01, -8.6525e+00, 6.6253e+00, 3.9786e-01, 1.4130e-01, -4.6411e+00, 7.0626e-01, 1.0477e+00, -1.7875e-01},
            {9.3332e+00, -2.6804e+00, 1.8522e+00, 4.3755e-01, 7.5698e-01, -1.9252e+00, -5.9311e-01, 1.8887e-01, 9.3435e-01, -9.7427e-02, -1.6232e+01, -4.7827e+00, 5.1153e-02, 2.2605e-01, 1.6452e-01, 1.6212e+01, 4.5487e+01, 1.8569e+00, 1.0878e+00, -1.1379e-02, 1.9010e+00, -2.7519e-01, 3.6326e-01, -1.6192e-01, 2.8821e+00, 1.0704e+00, 7.1178e-01, -2.6429e-02},
            {3.0903e+00, 1.6552e+00, -1.3725e-01, 1.8244e-01, 1.1291e+00, -1.5521e+00, 1.8444e+00, 1.5304e+00, 5.9132e-02, 1.6562e-01, -1.3038e+00, 8.2120e-01, 6.0445e-01, 4.7266e-01, 2.0942e-01, 2.9808e+00, 1.8569e+00, 9.1661e+00, 4.0639e-01, 4.7322e-02, -2.2287e+00, 2.7419e-02, -3.1738e-02, 7.3655e-02, -3.7532e-01, -3.6019e-01, 2.8927e-01, 2.6187e-02},
            {1.9607e-01, -9.2475e-01, -6.1019e-02, -4.1748e-02, 1.0347e-01, 7.2142e-01, -6.8109e-01, 1.5826e-01, 5.0289e-02, 1.6255e-01, -9.3336e-02, 8.6277e-01, -7.7956e-02, 5.9822e-02, 1.9817e-01, 4.1373e+00, 1.0878e+00, 4.0639e-01, 1.4865e+00, 3.0158e-02, 3.2119e-02, 6.5265e-01, 1.0746e-01, -3.6876e-03, -9.3238e-01, 2.6358e-02, 2.9238e-02, 5.7457e-03},
            {3.1051e-01, 2.9139e-01, -4.8209e-02, 5.8184e-02, 2.0091e-01, -2.6510e-01, -8.3176e-02, -1.5827e-01, 2.5199e-02, -2.9108e-02, -7.6029e-01, 2.0358e-02, 4.9290e-03, 4.0220e-02, 9.8534e-02, 7.3180e-01, -1.1379e-02, 4.7322e-02, 3.0158e-02, 3.3153e-01, 1.3960e-01, 7.6362e-02, -1.3776e-02, 5.0654e-03, 4.8365e-01, 4.1544e-02, 3.5684e-02, 4.0270e-04},
            {-2.5945e+01, 1.1311e+01, 3.0286e+00, 7.0573e-01, 7.6066e-01, -3.5144e+01, -1.3621e+01, 2.2073e+00, 5.4717e-01, -3.1936e-01, 1.5524e+01, -2.9515e-01, 9.6107e-01, 1.4850e-01, -7.5988e-01, -8.6525e+00, 1.9010e+00, -2.2287e+00, 3.2119e-02, 1.3960e-01, 1.1350e+02, 1.3072e+01, 8.3534e-01, 3.1025e-01, -1.4518e+00, -3.2020e-01, 1.1889e-01, -7.0540e-03},
            {-6.0308e-01, 4.6062e+00, -4.7960e-01, 2.2611e-01, -4.2736e-01, 3.4202e+00, -1.4951e+00, 4.4216e-01, -3.3770e-01, 6.2055e-01, -1.4310e+00, 1.0928e+00, -4.1676e-01, -9.2780e-02, 3.1519e-01, 6.6253e+00, -2.7519e-01, 2.7419e-02, 6.5265e-01, 7.6362e-02, 1.3072e+01, 1.3178e+01, 1.1952e-01, 9.2730e-02, -1.7878e+00, -1.1135e-01, 9.8442e-02, -1.2978e-02},
            {-1.3191e+00, 1.6555e-01, -4.6834e-03, 3.2559e-02, 1.8125e-01, 5.0759e-01, -2.4687e-01, 2.9077e-01, 2.0771e-02, 3.9837e-02, 1.2741e-01, 6.8551e-02, 1.6022e-02, -7.8103e-03, 2.0297e-02, 3.9786e-01, 3.6326e-01, -3.1738e-02, 1.0746e-01, -1.3776e-02, 8.3534e-01, 1.1952e-01, 3.1161e-01, 3.1731e-03, 1.3477e-01, 2.7847e-02, -2.1812e-03, 1.0801e-03},
            {-1.7823e-01, -6.0225e-02, 7.4520e-02, 5.8350e-03, 5.6105e-02, 1.2089e-01, -3.8413e-02, 1.1504e-01, -2.0063e-02, 4.8745e-03, 3.8043e-01, 1.8299e-02, 3.6403e-02, 5.5901e-03, 3.3985e-02, 1.4130e-01, -1.6192e-01, 7.3655e-02, -3.6876e-03, 5.0654e-03, 3.1025e-01, 9.2730e-02, 3.1731e-03, 5.2476e-02, -2.1216e-01, -3.9722e-02, 2.8203e-03, 2.2613e-03},
            {-9.3416e+00, 5.7873e+00, 1.0201e-01, 3.2783e-01, 2.3908e-01, -1.1291e+01, 2.8754e+00, -1.9350e+00, -4.1563e-01, 1.0483e-01, -1.0665e+01, -3.3840e+00, -2.0987e-01, 5.2711e-01, -4.6371e-01, -4.6411e+00, 2.8821e+00, -3.7532e-01, -9.3238e-01, 4.8365e-01, -1.4518e+00, -1.7878e+00, 1.3477e-01, -2.1216e-01, 3.4245e+01, 7.2843e+00, 1.5902e+00, -2.4965e-02},
            {6.5442e-01, 7.0825e-01, -1.3870e-01, 2.0513e-01, 3.0974e-01, 1.1117e+00, 1.7971e+00, -4.1133e-01, -5.1919e-02, 3.9951e-01, 1.2716e+00, -2.8414e-01, -1.2231e-01, 3.1416e-02, -1.6694e-01, 7.0626e-01, 1.0704e+00, -3.6019e-01, 2.6358e-02, 4.1544e-02, -3.2020e-01, -1.1135e-01, 2.7847e-02, -3.9722e-02, 7.2843e+00, 3.7389e+00, 6.3033e-01, -6.8704e-03},
            {5.3011e-01, -7.4564e-01, -1.2913e-02, 9.6306e-02, 1.2836e-01, 8.8448e-01, 4.8273e-01, 1.7511e-01, 7.8065e-02, 5.1592e-02, -4.1845e-01, 1.6747e-02, -1.1477e-01, 6.8599e-02, 9.2917e-02, 1.0477e+00, 7.1178e-01, 2.8927e-01, 2.9238e-02, 3.5684e-02, 1.1889e-01, 9.8442e-02, -2.1812e-03, 2.8203e-03, 1.5902e+00, 6.3033e-01, 5.5992e-01, 1.8936e-03},
            {2.9185e-01, -9.4884e-02, 6.4226e-02, -1.6076e-02, 1.1331e-02, -2.3650e-01, 5.8252e-02, 3.0503e-02, 5.6252e-03, 7.7439e-03, 1.8484e-01, 1.8402e-02, 1.2197e-02, 6.9622e-03, 3.1600e-03, -1.7875e-01, -2.6429e-02, 2.6187e-02, 5.7457e-03, 4.0270e-04, -7.0540e-03, -1.2978e-02, 1.0801e-03, 2.2613e-03, -2.4965e-02, -6.8704e-03, 1.8936e-03, 1.5020e-02}
          };

          set_covariance(BKGCOV);

        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2OSLEP_Strong_Production_137invfb)

    //
    // Derived analysis class for the Slepton search regions
    //
    class Analysis_CMS_13TeV_2OSLEP_Slepton_137invfb : public Analysis_CMS_13TeV_2OSLEP_137invfb
    {

      public:
        Analysis_CMS_13TeV_2OSLEP_Slepton_137invfb()
        {
          set_analysis_name("CMS_13TeV_2OSLEP_Slepton_137invfb");
        }

        virtual void collect_results()
        {

          add_result(SignalRegionData(_counters.at("SRoffZ0j_100_150"),228.,  {198., 37.}));
          add_result(SignalRegionData(_counters.at("SRoffZ0j_150_225"),99.,   {120., 16.}));
          add_result(SignalRegionData(_counters.at("SRoffZ0j_225_300"),29.,   {20.8, 4.1}));
          add_result(SignalRegionData(_counters.at("SRoffZ0j_300"),    17.,   {9.3, 2.3}));
          add_result(SignalRegionData(_counters.at("SRoffZj_100_150"), 283.,  {245., 33.}));
          add_result(SignalRegionData(_counters.at("SRoffZj_150_225"), 97.,   {112., 12.}));
          add_result(SignalRegionData(_counters.at("SRoffZj_225_300"), 19.,   {14.7, 3.3}));
          add_result(SignalRegionData(_counters.at("SRoffZj_300"),     8.,    {8.7, 2.3}));

          // Covariance matrix
          static const vector< vector<double> > BKGCOV = {
            {1.7786e+03, 5.2615e+02, 8.0495e+01, 5.8355e-01, 1.5138e+03, 2.6629e+02, 6.5045e+01, 1.7791e+01},
            {5.2615e+02, 3.0245e+02, 2.8575e+01, 2.1602e+00, 5.0962e+02, 9.8039e+01, 2.5751e+01, 7.0010e+00},
            {8.0495e+01, 2.8575e+01, 1.9189e+01, 1.3511e+00, 8.3331e+01, 2.0008e+01, 3.4306e+00, 2.0171e+00},
            {5.8355e-01, 2.1602e+00, 1.3511e+00, 4.2977e+00, -1.1595e+00, -4.9924e-01, -2.3743e-01, -3.3360e-01},
            {1.5138e+03, 5.0962e+02, 8.3331e+01, -1.1595e+00, 1.6701e+03, 2.6076e+02, 6.7503e+01, 1.3919e+01},
            {2.6629e+02, 9.8039e+01, 2.0008e+01, -4.9924e-01, 2.6076e+02, 1.8247e+02, 1.5454e+01, 1.0831e+00},
            {6.5045e+01, 2.5751e+01, 3.4306e+00, -2.3743e-01, 6.7503e+01, 1.5454e+01, 1.2282e+01, 9.8613e-01},
            {1.7791e+01, 7.0010e+00, 2.0171e+00, -3.3360e-01, 1.3919e+01, 1.0831e+00, 9.8613e-01, 6.6077e+00}
          };

          set_covariance(BKGCOV);

        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2OSLEP_Slepton_137invfb)

  }
}
