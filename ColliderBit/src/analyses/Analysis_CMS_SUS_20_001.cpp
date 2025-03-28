///
///  \author Yang Zhang
///  \date 2021 June
///
///  \author Anders Kvellestad
///  \date 2024 Feb
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
#include "SoftDrop.hh"

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

// Renamed from: 
//      Analysis_CMS_13TeV_2OSLEP_137invfb

namespace Gambit
{
  namespace ColliderBit
  {

    // This analysis class is also a base class for the classes
    // 
    //   - CMS_SUS_20_001_strong_production
    //   - CMS_SUS_20_001_EW_production
    //   - CMS_SUS_20_001_Slepton
    // 
    // all defined below. The subclasses make use of the background
    // covariance matrices for their respective subset of signal regions.
    // This base class contains all SRs and does not make use of the
    // background covariance information.

    class Analysis_CMS_SUS_20_001 : public Analysis
    {

      protected:

      private:

        // vector<int> cutFlowVector_1;
        // vector<string> cutFlowVector_1_str;
        // size_t NCUTS_1;

        // vector<int> cutFlowVector_2;
        // vector<string> cutFlowVector_2_str;
        // size_t NCUTS_2;

        // ofstream cutflowFile;

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

        Analysis_CMS_SUS_20_001()
        {

          set_analysis_name("CMS_SUS_20_001");
          set_luminosity(137.);

          // Counters for the number of accepted events for each signal region
          _counters["SRA_50_100"] = EventCounter("SRA bveto [50, 100]");
          _counters["SRA_100_150"] = EventCounter("SRA bveto [100, 150]");
          _counters["SRA_150_230"] = EventCounter("SRA bveto [150, 230]");
          _counters["SRA_230_300"] = EventCounter("SRA bveto [230, 300]");
          _counters["SRA_300"] = EventCounter("SRA bveto [300, ~]");
          _counters["SRB_50_100"] = EventCounter("SRB bveto [50, 100]");
          _counters["SRB_100_150"] = EventCounter("SRB bveto [100, 150]");
          _counters["SRB_150_230"] = EventCounter("SRB bveto [150, 230]");
          _counters["SRB_230_300"] = EventCounter("SRB bveto [230, 300]");
          _counters["SRB_300"] = EventCounter("SRB bveto [300, ~]");
          _counters["SRC_50_100"] = EventCounter("SRC bveto [50, 100]");
          _counters["SRC_100_150"] = EventCounter("SRC bveto [100, 150]");
          _counters["SRC_150_250"] = EventCounter("SRC bveto [150, 250]");
          _counters["SRC_250"] = EventCounter("SRC bveto [250, ~]");
          _counters["SRAb_50_100"] = EventCounter("SRA btag [50, 100]");
          _counters["SRAb_100_150"] = EventCounter("SRA btag [100, 150]");
          _counters["SRAb_150_230"] = EventCounter("SRA btag [150, 230]");
          _counters["SRAb_230_300"] = EventCounter("SRA btag [230, 300]");
          _counters["SRAb_300"] = EventCounter("SRA btag [300, ~]");
          _counters["SRBb_50_100"] = EventCounter("SRB btag [50, 100]");
          _counters["SRBb_100_150"] = EventCounter("SRB btag [100, 150]");
          _counters["SRBb_150_230"] = EventCounter("SRB btag [150, 230]");
          _counters["SRBb_230_300"] = EventCounter("SRB btag [230, 300]");
          _counters["SRBb_300"] = EventCounter("SRB btag [300, ~]");
          _counters["SRCb_50_100"] = EventCounter("SRC btag [50, 100]");
          _counters["SRCb_100_150"] = EventCounter("SRC btag [100, 150]");
          _counters["SRCb_150_250"] = EventCounter("SRC btag [150, 250]");
          _counters["SRCb_250"] = EventCounter("SRC btag [250, ~]");

          _counters["SRBoostedVZ_50_100"] = EventCounter("SR EW on-Z BoostedVZ [50, 100]");
          _counters["SRBoostedVZ_100_200"] = EventCounter("SR EW on-Z BoostedVZ [100, 200]");
          _counters["SRBoostedVZ_200_300"] = EventCounter("SR EW on-Z BoostedVZ [200, 300]");
          _counters["SRBoostedVZ_300_400"] = EventCounter("SR EW on-Z BoostedVZ [300, 400]");
          _counters["SRBoostedVZ_400_500"] = EventCounter("SR EW on-Z BoostedVZ [400, 500]");
          _counters["SRBoostedVZ_500"] = EventCounter("SR EW on-Z BoostedVZ [500, ~]");
          _counters["SRResolvedVZ_50_100"] = EventCounter("SR EW on-Z ResolvedVZ [50, 100]");
          _counters["SRResolvedVZ_100_150"] = EventCounter("SR EW on-Z ResolvedVZ [100, 150]");
          _counters["SRResolvedVZ_150_250"] = EventCounter("SR EW on-Z ResolvedVZ [150, 250]");
          _counters["SRResolvedVZ_250_350"] = EventCounter("SR EW on-Z ResolvedVZ [250, 350]");
          _counters["SRResolvedVZ_350"] = EventCounter("SR EW on-Z ResolvedVZ [350, ~]");
          _counters["SRHZ_50_100"] = EventCounter("SR EW on-Z HZ [50, 100]");
          _counters["SRHZ_100_150"] = EventCounter("SR EW on-Z HZ [100, 150]");
          _counters["SRHZ_150_250"] = EventCounter("SR EW on-Z HZ [150, 250]");
          _counters["SRHZ_250"] = EventCounter("SR EW on-Z HZ [250, ~]");

          _counters["SRoffZ0j_100_150"] = EventCounter("SR Off-Z nj=0 [100, 150]");
          _counters["SRoffZ0j_150_225"] = EventCounter("SR Off-Z nj=0 [150, 225]");
          _counters["SRoffZ0j_225_300"] = EventCounter("SR Off-Z nj=0 [225, 300]");
          _counters["SRoffZ0j_300"] = EventCounter("SR Off-Z nj=0 [300, ~]");
          _counters["SRoffZj_100_150"] = EventCounter("SR Off-Z nj>0 [100, 150]");
          _counters["SRoffZj_150_225"] = EventCounter("SR Off-Z nj>0 [150, 225]");
          _counters["SRoffZj_225_300"] = EventCounter("SR Off-Z nj>0 [225, 300]");
          _counters["SRoffZj_300"] = EventCounter("SR Off-Z nj>0 [300, ~]");

          // Control regions
          // _counters["SRonZ0j_100_150"] = EventCounter("SR on-Z nj=0 [100, 150]");
          // _counters["SRonZ0j_150_225"] = EventCounter("SR on-Z nj=0 [150, 225]");
          // _counters["SRonZ0j_225_300"] = EventCounter("SR on-Z nj=0 [225, 300]");
          // _counters["SRonZ0j_300"] = EventCounter("SR on-Z nj=0 [300, ~]");
          // _counters["SRonZj_100_150"] = EventCounter("SR on-Z nj>0 [100, 150]");
          // _counters["SRonZj_150_225"] = EventCounter("SR on-Z nj>0 [150, 225]");
          // _counters["SRonZj_225_300"] = EventCounter("SR on-Z nj>0 [225, 300]");
          // _counters["SRonZj_300"] = EventCounter("SR on-Z nj>0 [300, ~]");


          // NCUTS_1=11;
          // for (size_t i=0;i<NCUTS_1;i++)
          // {
          //   cutFlowVector_1.push_back(0);
          //   cutFlowVector_1_str.push_back("");
          // }

          // cutFlowVector_1_str[0] = "All events";
          // cutFlowVector_1_str[1] = "2 OSSF leptons with $p_{T} > 25(20)$ GeV";
          // cutFlowVector_1_str[2] = "$P_T^{\ell\ell}$>50 GeV";
          // cutFlowVector_1_str[3] = R"($\Delta R(\ell\ell)$>0.1)"; // string literal R"(...)" to avoid compiler warning about the '\D'
          // cutFlowVector_1_str[4] = "$m_{\ell}<$65 or >120 GeV";
          // cutFlowVector_1_str[5] = "Leading lepton $p_{T} > 50$ GeV";
          // cutFlowVector_1_str[6] = "Thied lepton veto";
          // cutFlowVector_1_str[7] = "$M_{T2}(ll) > 100 GeV$";
          // cutFlowVector_1_str[8] = "$E^{miss}_{T} > 100 GeV$";
          // cutFlowVector_1_str[9] = "$n_j>0$,etc.";
          // cutFlowVector_1_str[10] = "$n_j=0$";

          // NCUTS_2=4;
          // for (size_t i=0;i<NCUTS_2;i++)
          // {
          //   cutFlowVector_2.push_back(0);
          //   cutFlowVector_2_str.push_back("");
          // }
          // cutFlowVector_2_str[0] = "All events";
          // cutFlowVector_2_str[1] = "Baseline preliminary selections";
          // cutFlowVector_2_str[2] = "Baseline lepton selections";
          // cutFlowVector_2_str[3] = "Signal regions selections";

        }


        void run(const HEPUtils::Event* event)
        {
          // cutFlowVector_1[0]++;
          // cutFlowVector_2[0]++;

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
          for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
          {
            if (jet->pT()>25. && fabs(jet->eta())<2.4) baselineJets.push_back(jet);
          }

          // Baseline Vjets
          vector<const HEPUtils::Jet*> baselineVJets;
          const double beta = 0.0;
          const double z_cut = 0.1;
          const double RSD = 0.8;
          FJNS::contrib::SoftDrop sd(beta, z_cut, RSD);
          // Get jets with anti-kT R=0.8
          for (const HEPUtils::Jet* jet : event->jets("antikt_R08"))
          {
            // High pT requirement
            if (jet->pT() > 200. && fabs(jet->eta())<2.4)
            {
              // Check softdrop mass
              FJNS::PseudoJet groomed_jet = sd(jet->pseudojet());
              double m = groomed_jet.m();              
              if (m > 65. && m < 105.)
              {
                // Accept jet
                baselineVJets.push_back(jet);
              }
            }
          }

          // Signal objects
          vector<const HEPUtils::Particle*> signalLeptons;
          vector<const HEPUtils::Particle*> signalElectrons;
          vector<const HEPUtils::Particle*> signalMuons;
          vector<const HEPUtils::Jet*> signalJets25; // used in regions in which the presence of jets is vetoed
          vector<const HEPUtils::Jet*> signalJets; // used to construct regions aiming for topologies with jets.
          vector<const HEPUtils::Jet*> signalBJets;
          vector<const HEPUtils::Jet*> signalVJets;

          // Signal electrons
          for (size_t iEl=0; iEl<baselineElectrons.size(); iEl++)
          {
            if (baselineElectrons.at(iEl)->pT()>20.) signalElectrons.push_back(baselineElectrons.at(iEl));
          }

          // Signal muons
          for (size_t iMu=0; iMu<baselineMuons.size(); iMu++)
          {
            if (baselineMuons.at(iMu)->pT()>20.) signalMuons.push_back(baselineMuons.at(iMu));
          }

          // Signal jets
          sort(baselinePhotons.begin(),baselinePhotons.end(),comparePt);
          for (size_t iJet=0; iJet<baselineJets.size(); iJet++)
          {
            bool overlap=false;
            for (size_t iLe=0; iLe<signalElectrons.size(); iLe++)
            {
              if (signalElectrons.at(iLe)->mom().deltaR_eta(baselineJets.at(iJet)->mom())<0.4) overlap=true;
            }
            for (size_t iLe=0; iLe<signalMuons.size(); iLe++)
            {
              if (signalMuons.at(iLe)->mom().deltaR_eta(baselineJets.at(iJet)->mom())<0.4) overlap=true;
            }
            if (baselinePhotons.size()!=0)
            {
              if (baselinePhotons.at(0)->mom().deltaR_eta(baselineJets.at(iJet)->mom())<0.4) overlap=true;
            }
            if (!overlap)
            {
              signalJets25.push_back(baselineJets.at(iJet));

              if (baselineJets.at(iJet)->pT() >= 35.)
              {
                signalJets.push_back(baselineJets.at(iJet));
              }
            }
          }

          // Get subset of signal jets that get b-tags.
          // For b-jets, jets down to pT > 25 should be considered, so we'll use signalJets25 below.
          const double btag_eff = 0.70;
          const double misstag_eff = 0.01;
          const double cmisstag_eff = 0.12;
          for (const HEPUtils::Jet* jet : signalJets25)
          {
            bool btag = false;
            if      (jet->btag() && random_bool(btag_eff))     btag = true;
            else if (jet->ctag() && random_bool(cmisstag_eff)) btag = true;
            else if (random_bool(misstag_eff))                 btag = true;

            if (btag) signalBJets.push_back(jet);
          }

          // Signal V-jets
          signalVJets = baselineVJets;

          // Signal leptons = electrons + muons
          signalLeptons=signalElectrons;
          signalLeptons.insert(signalLeptons.end(),signalMuons.begin(),signalMuons.end());

          sort(signalLeptons.begin(),signalLeptons.end(),comparePt);
          sort(signalJets25.begin(),signalJets25.end(),compareJetPt);
          sort(signalJets.begin(),signalJets.end(),compareJetPt);
          sort(signalBJets.begin(),signalBJets.end(),compareJetPt);
          sort(signalVJets.begin(),signalVJets.end(),compareJetPt);

          size_t nSignalLeptons = signalLeptons.size();
          size_t nSignalJets25 = signalJets25.size();
          size_t nSignalJets = signalJets.size();
          size_t nSignalBJets = signalBJets.size();
          size_t nSignalVJets = signalVJets.size();


          // ###### Baseline selection ########
          // the presence of two OS leptons with > 25 (20) GeV for the highest (next-to-highest) pT lepton

          // the two highest pT OS leptons are required to have the same flavor
          if (nSignalLeptons < 2) return;
          if (signalLeptons[0]->pid() + signalLeptons[1]->pid() !=0) return;
          if (signalLeptons[0]->pT() < 25. || signalLeptons[1]->pT() < 20.) return;
          // cutFlowVector_1[1]++;

          double pTll = (signalLeptons[0]->mom()+signalLeptons[1]->mom()).pT();
          if (pTll < 50) return;
          // cutFlowVector_1[2]++;

          // the two highest pT leptons are required to be separated by a distance dR>0.1
          if (signalLeptons[0]->mom().deltaR_eta(signalLeptons[1]->mom())<0.1) return;
          // cutFlowVector_1[3]++;

          double mll = (signalLeptons[0]->mom()+signalLeptons[1]->mom()).m();
          if (mll < 20.) return;

          if (met < 50.) return;

          double mT2 = get_mT2(signalLeptons, event->missingmom());
          double HT = 0.;
          for (size_t iJet=0; iJet<nSignalJets; iJet++){
            HT += signalJets[iJet]->pT();
          }

          // cutFlowVector_2[1]++;

          // The two highest-pT jets must be separated from pTmiss vector by delta phi > 0.4
          bool deltaPhiJet1PTmissSeparation = true;
          bool deltaPhiJet2PTmissSeparation = true;
          if (nSignalJets == 1)
          {
            deltaPhiJet1PTmissSeparation = ( event->missingmom().deltaR_eta(signalJets[0]->mom()) > 0.4 );
          }
          else if (nSignalJets >= 2) 
          {
            deltaPhiJet1PTmissSeparation = ( event->missingmom().deltaR_eta(signalJets[0]->mom()) > 0.4 );
            deltaPhiJet2PTmissSeparation = ( event->missingmom().deltaR_eta(signalJets[1]->mom()) > 0.4 );
          }
          bool deltaPhiJet12PTmissSeparation = (deltaPhiJet1PTmissSeparation && deltaPhiJet2PTmissSeparation); 

          // For SRs with V jets, a baseline requirement is separation from pTmiss by 
          // delta phi > 0.4 *or* > 0.8, depending on the type of jet
          bool deltaPhiJet1TmissSeparation_VJetSR = true;
          if (nSignalJets >= 1 && nSignalVJets == 0)
          {
            deltaPhiJet1TmissSeparation_VJetSR = ( event->missingmom().deltaR_eta(signalJets[0]->mom()) > 0.4 );
          }
          else if (nSignalJets == 0 && nSignalVJets >= 1)
          {
            deltaPhiJet1TmissSeparation_VJetSR = ( event->missingmom().deltaR_eta(signalVJets[0]->mom()) > 0.8 );
          }
          else if (nSignalJets >= 1 && nSignalVJets >= 1)
          {
            if (signalJets[0]->pT() > signalVJets[0]->pT())
            {
              deltaPhiJet1TmissSeparation_VJetSR = ( event->missingmom().deltaR_eta(signalJets[0]->mom()) > 0.4 );
            }
            else 
            {
              deltaPhiJet1TmissSeparation_VJetSR = ( event->missingmom().deltaR_eta(signalVJets[0]->mom()) > 0.8 );
            }
          }


          // Compute some SR selection variables
          double mjj = 0.;
          if (nSignalJets >= 2)
          {
            mjj = (signalJets[0]->mom()+signalJets[1]->mom()).m();
          }

          double mbb = 0.;
          if (nSignalBJets >= 2)
          {
            mbb = (signalBJets[0]->mom()+signalBJets[1]->mom()).m();
          }

          double mT2_lblb = 0.;
          if (nSignalBJets >= 2 && nSignalLeptons >= 2)
          {
            mT2_lblb = get_mT2_lblb(signalLeptons, signalBJets, event->missingmom());
          }


          // ###### on-Z regions, strong production ########
          if (mll>86 and mll<96 and nSignalLeptons==2 and met > 50 and nSignalJets >1 and deltaPhiJet12PTmissSeparation)
          {
            // cutFlowVector_2[2]++;
            if (nSignalBJets==0)
            {
              if (mT2>80)
              {
                if (HT>500)
                {
                  // cutFlowVector_2[3]++;
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

          // ###### on-Z regions, EW production ########
          if (mll>86 and mll<96 and nSignalLeptons==2)
          {
            // Boosted VZ
            if (deltaPhiJet1TmissSeparation_VJetSR)
            {
              if      (nSignalJets25 == 0 and nSignalVJets == 1 and nSignalBJets == 0 and met > 50.  and met < 100.) _counters.at("SRBoostedVZ_50_100").add_event(event);
              else if (nSignalJets25 == 0 and nSignalVJets == 1 and nSignalBJets == 0 and met > 100. and met < 200.) _counters.at("SRBoostedVZ_100_200").add_event(event);
              else if (nSignalJets25 == 0 and nSignalVJets == 1 and nSignalBJets == 0 and met > 200. and met < 300.) _counters.at("SRBoostedVZ_200_300").add_event(event);
              else if (nSignalJets25 == 0 and nSignalVJets == 1 and nSignalBJets == 0 and met > 300. and met < 400.) _counters.at("SRBoostedVZ_300_400").add_event(event);
              else if (nSignalJets25 == 0 and nSignalVJets == 1 and nSignalBJets == 0 and met > 400. and met < 500.) _counters.at("SRBoostedVZ_400_500").add_event(event);
              else if (nSignalJets25 == 0 and nSignalVJets == 1 and nSignalBJets == 0 and met > 500.)                _counters.at("SRBoostedVZ_500").add_event(event);
            }

            // Resolved VZ
            if (deltaPhiJet12PTmissSeparation)
            {
              if      (nSignalJets > 1 and nSignalBJets == 0 and mjj < 110. and mT2 > 80. and met > 50.  and met < 100.) _counters.at("SRResolvedVZ_50_100").add_event(event);
              else if (nSignalJets > 1 and nSignalBJets == 0 and mjj < 110. and mT2 > 80. and met > 100. and met < 150.) _counters.at("SRResolvedVZ_100_150").add_event(event);
              else if (nSignalJets > 1 and nSignalBJets == 0 and mjj < 110. and mT2 > 80. and met > 150. and met < 250.) _counters.at("SRResolvedVZ_150_250").add_event(event);
              else if (nSignalJets > 1 and nSignalBJets == 0 and mjj < 110. and mT2 > 80. and met > 250. and met < 350.) _counters.at("SRResolvedVZ_250_350").add_event(event);
              else if (nSignalJets > 1 and nSignalBJets == 0 and mjj < 110. and mT2 > 80. and met > 350.)                _counters.at("SRResolvedVZ_350").add_event(event);
            }

            // HZ
            if (deltaPhiJet12PTmissSeparation)
            {
              if      (nSignalJets > 1 and nSignalBJets == 2 and mbb < 150. and mT2_lblb > 200. and met > 50.  and met < 100.) _counters.at("SRHZ_50_100").add_event(event);
              else if (nSignalJets > 1 and nSignalBJets == 2 and mbb < 150. and mT2_lblb > 200. and met > 100. and met < 150.) _counters.at("SRHZ_100_150").add_event(event);
              else if (nSignalJets > 1 and nSignalBJets == 2 and mbb < 150. and mT2_lblb > 200. and met > 150. and met < 250.) _counters.at("SRHZ_150_250").add_event(event);
              else if (nSignalJets > 1 and nSignalBJets == 2 and mbb < 150. and mT2_lblb > 200. and met > 250.)                _counters.at("SRHZ_250").add_event(event);
            }

          }


          // ###### slepton region #######
          if (mll<65 or mll>120)
          {
            // cutFlowVector_1[4]++;
            if (signalLeptons[0]->pT()>50)
            {
              // cutFlowVector_1[5]++;
              if (nSignalLeptons==2)
              {
                // cutFlowVector_1[6]++;
                if (mT2>100)
                {
                  // cutFlowVector_1[7]++;
                  if (met>50)
                  {
                    // cutFlowVector_1[8]++;
                    if (nSignalBJets==0){
                      if (nSignalJets25>0 and event->missingmom().deltaR_eta(signalJets25.at(0)->mom())>0.4
                        and (signalLeptons[1]->pT()/signalJets25[0]->pT())>1.2 )
                      {
                        // cutFlowVector_1[9]++;
                        if (mT2<150) _counters.at("SRoffZj_100_150").add_event(event);
                        else if (mT2<225) _counters.at("SRoffZj_150_225").add_event(event);
                        else if (mT2<300) _counters.at("SRoffZj_225_300").add_event(event);
                        else _counters.at("SRoffZj_300").add_event(event);
                      }
                      if (nSignalJets25==0)
                      {
                        // cutFlowVector_1[10]++;
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

          // // Contral regions
          // if (mll>65 and mll<120)
          // {
          //   if (signalLeptons[0]->pT()>50)
          //   {
          //     if (nSignalLeptons==2)
          //     {
          //       if (mT2>100)
          //       {
          //         if (met>50)
          //         {
          //           if (nSignalBJets==0)
          //           {
          //             if (nSignalJets>0 and deltaPhiJet12PTmissSeparation
          //               and signalLeptons[1]->pT()/signalJets[0]->pT()>1.2 )
          //             {
          //               if (mT2<150) _counters.at("SRonZj_100_150").add_event(event);
          //               else if (mT2<225) _counters.at("SRonZj_150_225").add_event(event);
          //               else if (mT2<300) _counters.at("SRonZj_225_300").add_event(event);
          //               else _counters.at("SRonZj_300").add_event(event);
          //             }
          //             if (nSignalJets25==0)
          //             {
          //               if (mT2<150) _counters.at("SRonZ0j_100_150").add_event(event);
          //               else if (mT2<225) _counters.at("SRonZ0j_150_225").add_event(event);
          //               else if (mT2<300) _counters.at("SRonZ0j_225_300").add_event(event);
          //               else _counters.at("SRonZ0j_300").add_event(event);
          //             }
          //           }
          //         }
          //       }
          //     }
          //   }
          // }

        }


        virtual void collect_results()
        {
          //for (size_t i=0;i<NCUTS_1;i++)
          //{
          //  cout << i << "\t" << cutFlowVector_1_str[i] << "\t" << cutFlowVector_1[i] << endl;
          //}
          //cout << "=========================" << endl;
          //for (size_t i=0;i<NCUTS_2;i++)
          //{
          //  cout << i << "\t" << cutFlowVector_2_str[i] << "\t" << cutFlowVector_2[i] << endl;
          //}

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

          add_result(SignalRegionData(_counters.at("SRHZ_50_100"),  168., {168., 15.}));
          add_result(SignalRegionData(_counters.at("SRHZ_100_150"), 14.,  {15.6, 4.3}));
          add_result(SignalRegionData(_counters.at("SRHZ_150_250"), 5.,   {5.6, 2.8}));
          add_result(SignalRegionData(_counters.at("SRHZ_250"),     0.,   {1.2, 0.4}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_50_100"),  43., {43.0, 9.9}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_100_200"), 5.,  {2.3, 0.8}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_200_300"), 1.,  {0.5, 0.5}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_300_400"), 0.,  {0.2, 0.2}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_400_500"), 0.,  {0.0, 0.1}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_500"),     0.,  {0.2, 0.1}));
          add_result(SignalRegionData(_counters.at("SRResolvedVZ_50_100"),  3648., {3648., 80.}));
          add_result(SignalRegionData(_counters.at("SRResolvedVZ_100_150"), 461.,  {439., 47.}));
          add_result(SignalRegionData(_counters.at("SRResolvedVZ_150_250"), 69.,   {58., 19.}));
          add_result(SignalRegionData(_counters.at("SRResolvedVZ_250_350"), 7.,    {11.9, 3.2}));
          add_result(SignalRegionData(_counters.at("SRResolvedVZ_350"),     2.,    {6.3, 2.2}));

          add_result(SignalRegionData(_counters.at("SRoffZ0j_100_150"), 228.,  {198., 37.}));
          add_result(SignalRegionData(_counters.at("SRoffZ0j_150_225"), 99.,   {120., 16.}));
          add_result(SignalRegionData(_counters.at("SRoffZ0j_225_300"), 29.,   {20.8, 4.1}));
          add_result(SignalRegionData(_counters.at("SRoffZ0j_300"),     17.,   {9.3, 2.3}));
          add_result(SignalRegionData(_counters.at("SRoffZj_100_150"),  283.,  {245., 33.}));
          add_result(SignalRegionData(_counters.at("SRoffZj_150_225"),  97.,   {112., 12.}));
          add_result(SignalRegionData(_counters.at("SRoffZj_225_300"),  19.,   {14.7, 3.3}));
          add_result(SignalRegionData(_counters.at("SRoffZj_300"),      8.,    {8.7, 2.3}));

          // Control regions
          // add_result(SignalRegionData(_counters.at("SRonZ0j_100_150"), 1059., {1059., 34.}));
          // add_result(SignalRegionData(_counters.at("SRonZ0j_150_225"), 573.,  {573., 26.}));
          // add_result(SignalRegionData(_counters.at("SRonZ0j_225_300"), 116.,  {116., 11.}));
          // add_result(SignalRegionData(_counters.at("SRonZ0j_300"),     47.,   {47.5, 5.3}));
          // add_result(SignalRegionData(_counters.at("SRonZj_100_150"),  674.,  {674., 29.}));
          // add_result(SignalRegionData(_counters.at("SRonZj_150_225"),  241.,  {241., 16.}));
          // add_result(SignalRegionData(_counters.at("SRonZj_225_300"),  72.,   {72., 8.2}));
          // add_result(SignalRegionData(_counters.at("SRonZj_300"),      30.,   {34.9, 3.8}));

        }


        double get_mT2(vector<const HEPUtils::Particle*> leptons, HEPUtils::P4 pTmiss)
        {
          double mT2 = 0.;
          double pLep0[3] = {leptons.at(0)->mass(), leptons.at(0)->mom().px(), leptons.at(0)->mom().py()};
          double pLep1[3] = {leptons.at(1)->mass(), leptons.at(1)->mom().px(), leptons.at(1)->mom().py()};
          double pMiss[3] = {0., pTmiss.px(), pTmiss.py() };
          double mn = 0.;

          mt2_bisect::mt2 mt2_calc;
          mt2_calc.set_momenta(pLep0,pLep1,pMiss);
          mt2_calc.set_mn(mn);
          mT2 = mt2_calc.get_mt2();
          return mT2;
        }


        double get_mT2_lblb(vector<const HEPUtils::Particle*> leptons, vector<const HEPUtils::Jet*> bjets, HEPUtils::P4 pTmiss)
        {
          double mT2 = DBL_MAX;

          HEPUtils::P4 p4L0 = leptons.at(0)->mom();
          HEPUtils::P4 p4L1 = leptons.at(1)->mom();
          HEPUtils::P4 p4B0 = bjets.at(0)->mom();
          HEPUtils::P4 p4B1 = bjets.at(1)->mom();

          double pL0[3] = {p4L0.m(), p4L0.px(), p4L0.py()};
          double pL1[3] = {p4L1.m(), p4L1.px(), p4L1.py()};
          double pB0[3] = {p4B0.m(), p4B0.px(), p4B0.py()};
          double pB1[3] = {p4B1.m(), p4B1.px(), p4B1.py()};

          double pMiss[3] = {0., pTmiss.px(), pTmiss.py() };
          double mn = 0.;

          mt2_bisect::mt2 mt2_calc;

          // L0B0
          mt2_calc.set_momenta(pL0, pB0, pMiss);
          mt2_calc.set_mn(mn);
          double mT2_L0B0 = mt2_calc.get_mt2();
          if (mT2_L0B0 < mT2) mT2 = mT2_L0B0;

          // L0B1
          mt2_calc.set_momenta(pL0, pB1, pMiss);
          mt2_calc.set_mn(mn);
          double mT2_L0B1 = mt2_calc.get_mt2();
          if (mT2_L0B1 < mT2) mT2 = mT2_L0B1;

          // L1B0
          mt2_calc.set_momenta(pL1, pB0, pMiss);
          mt2_calc.set_mn(mn);
          double mT2_L1B0 = mt2_calc.get_mt2();
          if (mT2_L1B0 < mT2) mT2 = mT2_L1B0;

          // L1B1
          mt2_calc.set_momenta(pL1, pB1, pMiss);
          mt2_calc.set_mn(mn);
          double mT2_L1B1 = mt2_calc.get_mt2();
          if (mT2_L1B1 < mT2) mT2 = mT2_L1B1;

          return mT2;
        }


      protected:
        void analysis_specific_reset()
        {

          for (auto& pair : _counters) { pair.second.reset(); }
          // std::fill(cutFlowVector_1.begin(), cutFlowVector_1.end(), 0);
          // std::fill(cutFlowVector_2.begin(), cutFlowVector_2.end(), 0);
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_20_001)



    //
    // Derived analysis class for the Strong-production on-Z search regions
    //
    class Analysis_CMS_SUS_20_001_strong_production : public Analysis_CMS_SUS_20_001
    {

      public:
        Analysis_CMS_SUS_20_001_strong_production()
        {
          set_analysis_name("CMS_SUS_20_001_strong_production");
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
            {  1.452e+03,  5.520e+01,  6.065e+00,  2.108e-01,  1.155e+01, -1.256e+01,  1.464e+01,  9.276e+00, -3.391e+00, -2.705e-01,  5.499e+01,  1.271e+01,  5.089e+00,  1.827e+00,  1.310e+00, -1.869e+01,  9.333e+00,  3.090e+00,  1.961e-01,  3.105e-01, -2.595e+01, -6.031e-01, -1.319e+00, -1.782e-01, -9.342e+00,  6.544e-01,  5.301e-01,  2.918e-01},
            {  5.520e+01,  8.951e+01,  1.150e+00,  1.281e-01,  1.362e+00, -6.715e+00, -5.015e+00,  1.540e+00,  1.607e-01, -1.297e+00, -1.806e+01,  8.218e-01, -2.626e-01,  3.463e-01,  1.048e+00, -1.869e+00, -2.680e+00,  1.655e+00, -9.247e-01,  2.914e-01,  1.131e+01,  4.606e+00,  1.656e-01, -6.022e-02,  5.787e+00,  7.082e-01, -7.456e-01, -9.488e-02},
            {  6.065e+00,  1.150e+00,  1.292e+01,  5.063e-01,  6.763e-01,  2.064e+00,  7.629e-01,  1.270e+00,  3.418e-01, -2.157e-01, -4.355e+00, -1.803e+00,  2.381e-01,  1.947e-01,  5.755e-02, -2.888e-01,  1.852e+00, -1.372e-01, -6.102e-02, -4.821e-02,  3.029e+00, -4.796e-01, -4.683e-03,  7.452e-02,  1.020e-01, -1.387e-01, -1.291e-02,  6.423e-02},
            {  2.108e-01,  1.281e-01,  5.063e-01,  1.269e+00,  5.195e-01, -2.980e+00,  6.383e-01,  1.385e-01, -1.206e-01,  1.386e-01, -7.064e-01,  1.993e-01, -3.736e-02,  1.208e-01,  4.178e-01,  7.681e-01,  4.376e-01,  1.824e-01, -4.175e-02,  5.818e-02,  7.057e-01,  2.261e-01,  3.256e-02,  5.835e-03,  3.278e-01,  2.051e-01,  9.631e-02, -1.608e-02},
            {  1.155e+01,  1.362e+00,  6.763e-01,  5.195e-01,  5.757e+00,  5.328e-01,  1.464e+00,  4.344e-01,  4.581e-01, -6.634e-02,  5.949e-01, -1.829e-01, -6.941e-02,  2.903e-01,  2.779e-01,  2.487e+00,  7.570e-01,  1.129e+00,  1.035e-01,  2.009e-01,  7.607e-01, -4.274e-01,  1.812e-01,  5.611e-02,  2.391e-01,  3.097e-01,  1.284e-01,  1.133e-02},
            { -1.256e+01, -6.715e+00,  2.064e+00, -2.980e+00,  5.328e-01,  5.385e+02,  3.979e+01,  5.810e+00, -1.716e+00,  4.631e-01, -3.255e+00,  1.523e+00,  2.440e+00, -4.337e-01, -2.865e+00,  2.929e+01, -1.925e+00, -1.552e+00,  7.214e-01, -2.651e-01, -3.514e+01,  3.420e+00,  5.076e-01,  1.209e-01, -1.129e+01,  1.112e+00,  8.845e-01, -2.365e-01},
            {  1.464e+01, -5.015e+00,  7.629e-01,  6.383e-01,  1.464e+00,  3.979e+01,  5.900e+01,  2.444e+00, -4.674e-01,  9.869e-01,  1.726e+01, -3.747e+00, -1.258e-01,  9.008e-01,  8.168e-01, -8.619e+00, -5.931e-01,  1.844e+00, -6.811e-01, -8.318e-02, -1.362e+01, -1.495e+00, -2.469e-01, -3.841e-02,  2.875e+00,  1.797e+00,  4.827e-01,  5.825e-02},
            {  9.276e+00,  1.540e+00,  1.270e+00,  1.385e-01,  4.344e-01,  5.810e+00,  2.444e+00,  8.527e+00,  4.039e-01,  1.010e-01,  5.171e+00, -9.649e-02,  1.026e-01, -3.732e-02, -1.596e-01, -1.287e+00,  1.889e-01,  1.530e+00,  1.583e-01, -1.583e-01,  2.207e+00,  4.422e-01,  2.908e-01,  1.150e-01, -1.935e+00, -4.113e-01,  1.751e-01,  3.050e-02},
            { -3.391e+00,  1.607e-01,  3.418e-01, -1.206e-01,  4.581e-01, -1.716e+00, -4.674e-01,  4.039e-01,  2.062e+00, -1.386e-01,  4.329e+00,  8.825e-01, -1.137e-01,  7.204e-02, -1.119e-01,  1.574e+00,  9.343e-01,  5.913e-02,  5.029e-02,  2.520e-02,  5.472e-01, -3.377e-01,  2.077e-02, -2.006e-02, -4.156e-01, -5.192e-02,  7.807e-02,  5.625e-03},
            { -2.705e-01, -1.297e+00, -2.157e-01,  1.386e-01, -6.634e-02,  4.631e-01,  9.869e-01,  1.010e-01, -1.386e-01,  1.226e+00, -4.217e-01,  1.526e-01, -2.764e-01,  9.797e-03,  1.160e-01, -1.614e+00, -9.743e-02,  1.656e-01,  1.626e-01, -2.911e-02, -3.194e-01,  6.205e-01,  3.984e-02,  4.874e-03,  1.048e-01,  3.995e-01,  5.159e-02,  7.744e-03},
            {  5.499e+01, -1.806e+01, -4.355e+00, -7.064e-01,  5.949e-01, -3.255e+00,  1.726e+01,  5.171e+00,  4.329e+00, -4.217e-01,  4.994e+02,  5.501e+01,  5.672e+00,  1.608e+00,  2.141e+00,  3.590e+00, -1.623e+01, -1.304e+00, -9.334e-02, -7.603e-01,  1.552e+01, -1.431e+00,  1.274e-01,  3.804e-01, -1.066e+01,  1.272e+00, -4.184e-01,  1.848e-01},
            {  1.271e+01,  8.218e-01, -1.803e+00,  1.993e-01, -1.829e-01,  1.523e+00, -3.747e+00, -9.649e-02,  8.825e-01,  1.526e-01,  5.501e+01,  3.323e+01, -1.025e-01,  4.484e-01,  9.853e-01,  1.574e+00, -4.783e+00,  8.212e-01,  8.628e-01,  2.036e-02, -2.952e-01,  1.093e+00,  6.855e-02,  1.830e-02, -3.384e+00, -2.841e-01,  1.675e-02,  1.840e-02},
            {  5.089e+00, -2.626e-01,  2.381e-01, -3.736e-02, -6.941e-02,  2.440e+00, -1.258e-01,  1.026e-01, -1.137e-01, -2.764e-01,  5.672e+00, -1.025e-01,  2.766e+00,  4.068e-02,  6.872e-02, -4.854e-01,  5.115e-02,  6.044e-01, -7.796e-02,  4.929e-03,  9.611e-01, -4.168e-01,  1.602e-02,  3.640e-02, -2.099e-01, -1.223e-01, -1.148e-01,  1.220e-02},
            {  1.827e+00,  3.463e-01,  1.947e-01,  1.208e-01,  2.903e-01, -4.337e-01,  9.008e-01, -3.732e-02,  7.204e-02,  9.797e-03,  1.608e+00,  4.484e-01,  4.068e-02,  5.483e-01,  2.647e-01, -1.416e-01,  2.261e-01,  4.727e-01,  5.982e-02,  4.022e-02,  1.485e-01, -9.278e-02, -7.810e-03,  5.590e-03,  5.271e-01,  3.142e-02,  6.860e-02,  6.962e-03},
            {  1.310e+00,  1.048e+00,  5.755e-02,  4.178e-01,  2.779e-01, -2.865e+00,  8.168e-01, -1.596e-01, -1.119e-01,  1.160e-01,  2.141e+00,  9.853e-01,  6.872e-02,  2.647e-01,  1.692e+00, -5.146e-01,  1.645e-01,  2.094e-01,  1.982e-01,  9.853e-02, -7.599e-01,  3.152e-01,  2.030e-02,  3.398e-02, -4.637e-01, -1.669e-01,  9.292e-02,  3.160e-03},
            { -1.869e+01, -1.869e+00, -2.888e-01,  7.681e-01,  2.487e+00,  2.929e+01, -8.619e+00, -1.287e+00,  1.574e+00, -1.614e+00,  3.590e+00,  1.574e+00, -4.854e-01, -1.416e-01, -5.146e-01,  2.059e+02,  1.621e+01,  2.981e+00,  4.137e+00,  7.318e-01, -8.653e+00,  6.625e+00,  3.979e-01,  1.413e-01, -4.641e+00,  7.063e-01,  1.048e+00, -1.788e-01},
            {  9.333e+00, -2.680e+00,  1.852e+00,  4.376e-01,  7.570e-01, -1.925e+00, -5.931e-01,  1.889e-01,  9.343e-01, -9.743e-02, -1.623e+01, -4.783e+00,  5.115e-02,  2.261e-01,  1.645e-01,  1.621e+01,  4.549e+01,  1.857e+00,  1.088e+00, -1.138e-02,  1.901e+00, -2.752e-01,  3.633e-01, -1.619e-01,  2.882e+00,  1.070e+00,  7.118e-01, -2.643e-02},
            {  3.090e+00,  1.655e+00, -1.372e-01,  1.824e-01,  1.129e+00, -1.552e+00,  1.844e+00,  1.530e+00,  5.913e-02,  1.656e-01, -1.304e+00,  8.212e-01,  6.044e-01,  4.727e-01,  2.094e-01,  2.981e+00,  1.857e+00,  9.166e+00,  4.064e-01,  4.732e-02, -2.229e+00,  2.742e-02, -3.174e-02,  7.366e-02, -3.753e-01, -3.602e-01,  2.893e-01,  2.619e-02},
            {  1.961e-01, -9.247e-01, -6.102e-02, -4.175e-02,  1.035e-01,  7.214e-01, -6.811e-01,  1.583e-01,  5.029e-02,  1.626e-01, -9.334e-02,  8.628e-01, -7.796e-02,  5.982e-02,  1.982e-01,  4.137e+00,  1.088e+00,  4.064e-01,  1.486e+00,  3.016e-02,  3.212e-02,  6.526e-01,  1.075e-01, -3.688e-03, -9.324e-01,  2.636e-02,  2.924e-02,  5.746e-03},
            {  3.105e-01,  2.914e-01, -4.821e-02,  5.818e-02,  2.009e-01, -2.651e-01, -8.318e-02, -1.583e-01,  2.520e-02, -2.911e-02, -7.603e-01,  2.036e-02,  4.929e-03,  4.022e-02,  9.853e-02,  7.318e-01, -1.138e-02,  4.732e-02,  3.016e-02,  3.315e-01,  1.396e-01,  7.636e-02, -1.378e-02,  5.065e-03,  4.837e-01,  4.154e-02,  3.568e-02,  4.027e-04},
            { -2.595e+01,  1.131e+01,  3.029e+00,  7.057e-01,  7.607e-01, -3.514e+01, -1.362e+01,  2.207e+00,  5.472e-01, -3.194e-01,  1.552e+01, -2.952e-01,  9.611e-01,  1.485e-01, -7.599e-01, -8.653e+00,  1.901e+00, -2.229e+00,  3.212e-02,  1.396e-01,  1.135e+02,  1.307e+01,  8.353e-01,  3.103e-01, -1.452e+00, -3.202e-01,  1.189e-01, -7.054e-03},
            { -6.031e-01,  4.606e+00, -4.796e-01,  2.261e-01, -4.274e-01,  3.420e+00, -1.495e+00,  4.422e-01, -3.377e-01,  6.205e-01, -1.431e+00,  1.093e+00, -4.168e-01, -9.278e-02,  3.152e-01,  6.625e+00, -2.752e-01,  2.742e-02,  6.526e-01,  7.636e-02,  1.307e+01,  1.318e+01,  1.195e-01,  9.273e-02, -1.788e+00, -1.113e-01,  9.844e-02, -1.298e-02},
            { -1.319e+00,  1.656e-01, -4.683e-03,  3.256e-02,  1.812e-01,  5.076e-01, -2.469e-01,  2.908e-01,  2.077e-02,  3.984e-02,  1.274e-01,  6.855e-02,  1.602e-02, -7.810e-03,  2.030e-02,  3.979e-01,  3.633e-01, -3.174e-02,  1.075e-01, -1.378e-02,  8.353e-01,  1.195e-01,  3.116e-01,  3.173e-03,  1.348e-01,  2.785e-02, -2.181e-03,  1.080e-03},
            { -1.782e-01, -6.022e-02,  7.452e-02,  5.835e-03,  5.611e-02,  1.209e-01, -3.841e-02,  1.150e-01, -2.006e-02,  4.874e-03,  3.804e-01,  1.830e-02,  3.640e-02,  5.590e-03,  3.398e-02,  1.413e-01, -1.619e-01,  7.366e-02, -3.688e-03,  5.065e-03,  3.103e-01,  9.273e-02,  3.173e-03,  5.248e-02, -2.122e-01, -3.972e-02,  2.820e-03,  2.261e-03},
            { -9.342e+00,  5.787e+00,  1.020e-01,  3.278e-01,  2.391e-01, -1.129e+01,  2.875e+00, -1.935e+00, -4.156e-01,  1.048e-01, -1.066e+01, -3.384e+00, -2.099e-01,  5.271e-01, -4.637e-01, -4.641e+00,  2.882e+00, -3.753e-01, -9.324e-01,  4.837e-01, -1.452e+00, -1.788e+00,  1.348e-01, -2.122e-01,  3.424e+01,  7.284e+00,  1.590e+00, -2.497e-02},
            {  6.544e-01,  7.082e-01, -1.387e-01,  2.051e-01,  3.097e-01,  1.112e+00,  1.797e+00, -4.113e-01, -5.192e-02,  3.995e-01,  1.272e+00, -2.841e-01, -1.223e-01,  3.142e-02, -1.669e-01,  7.063e-01,  1.070e+00, -3.602e-01,  2.636e-02,  4.154e-02, -3.202e-01, -1.113e-01,  2.785e-02, -3.972e-02,  7.284e+00,  3.739e+00,  6.303e-01, -6.870e-03},
            {  5.301e-01, -7.456e-01, -1.291e-02,  9.631e-02,  1.284e-01,  8.845e-01,  4.827e-01,  1.751e-01,  7.807e-02,  5.159e-02, -4.184e-01,  1.675e-02, -1.148e-01,  6.860e-02,  9.292e-02,  1.048e+00,  7.118e-01,  2.893e-01,  2.924e-02,  3.568e-02,  1.189e-01,  9.844e-02, -2.181e-03,  2.820e-03,  1.590e+00,  6.303e-01,  5.599e-01,  1.894e-03},
            {  2.918e-01, -9.488e-02,  6.423e-02, -1.608e-02,  1.133e-02, -2.365e-01,  5.825e-02,  3.050e-02,  5.625e-03,  7.744e-03,  1.848e-01,  1.840e-02,  1.220e-02,  6.962e-03,  3.160e-03, -1.788e-01, -2.643e-02,  2.619e-02,  5.746e-03,  4.027e-04, -7.054e-03, -1.298e-02,  1.080e-03,  2.261e-03, -2.497e-02, -6.870e-03,  1.894e-03,  1.502e-02},
          };

          set_covariance(BKGCOV);

        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_20_001_strong_production)



    //
    // Derived analysis class for the EW-production on-Z search regions
    //
    class Analysis_CMS_SUS_20_001_EW_production : public Analysis_CMS_SUS_20_001
    {

      public:
        Analysis_CMS_SUS_20_001_EW_production()
        {
          set_analysis_name("CMS_SUS_20_001_EW_production");
        }

        virtual void collect_results()
        {
          add_result(SignalRegionData(_counters.at("SRHZ_50_100"),  168., {168., 15.}));
          add_result(SignalRegionData(_counters.at("SRHZ_100_150"), 14.,  {15.6, 4.3}));
          add_result(SignalRegionData(_counters.at("SRHZ_150_250"), 5.,   {5.6, 2.8}));
          add_result(SignalRegionData(_counters.at("SRHZ_250"),     0.,   {1.2, 0.4}));

          add_result(SignalRegionData(_counters.at("SRBoostedVZ_50_100"),  43., {43.0, 9.9}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_100_200"), 5.,  {2.3, 0.8}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_200_300"), 1.,  {0.5, 0.5}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_300_400"), 0.,  {0.2, 0.2}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_400_500"), 0.,  {0.0, 0.1}));
          add_result(SignalRegionData(_counters.at("SRBoostedVZ_500"),     0.,  {0.2, 0.1}));

          add_result(SignalRegionData(_counters.at("SRResolvedVZ_50_100"),  3648., {3648., 80.}));
          add_result(SignalRegionData(_counters.at("SRResolvedVZ_100_150"), 461.,  {439., 47.}));
          add_result(SignalRegionData(_counters.at("SRResolvedVZ_150_250"), 69.,   {58., 19.}));
          add_result(SignalRegionData(_counters.at("SRResolvedVZ_250_350"), 7.,    {11.9, 3.2}));
          add_result(SignalRegionData(_counters.at("SRResolvedVZ_350"),     2.,    {6.3, 2.2}));

          // Covariance matrix
          // NOTE: The ordering of the bin labels is wrong in the pdf/png figures of the covariance matrix 
          // provided at https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-20-001/index.html
          // The ROOT file has the correct bin labels, so the covariance matrix below is extracted from the ROOT file 
          // and the order in which the SRs are registered above is matched to this.
          static const vector< vector<double> > BKGCOV = {
            {  1.617e+02,  1.135e+01,  4.261e+00,  8.042e-01,  3.021e+00,  4.050e-01, -6.691e-02,  2.447e-01, -1.306e-02,  3.087e-02, -8.126e+01, -1.601e+01,  1.789e+01,  5.536e+00,  3.430e+00},
            {  1.135e+01,  9.444e+00,  1.657e+00,  4.450e-01,  2.818e+00,  3.480e-01, -1.021e-02,  7.137e-02, -6.388e-04,  2.926e-02, -1.639e+00,  8.133e+00,  6.670e+00,  5.999e-01,  5.488e-01},
            {  4.261e+00,  1.657e+00,  1.070e+01,  3.303e-01,  2.220e+00,  4.126e-01,  7.900e-02,  3.939e-02,  7.144e-03,  2.884e-03,  1.233e+01,  3.676e+00,  5.360e+00,  1.160e+00,  2.478e-01},
            {  8.042e-01,  4.450e-01,  3.303e-01,  4.496e-01,  1.250e+00,  1.687e-01,  6.884e-03,  9.276e-03,  6.434e-04,  4.373e-03,  4.501e+00, -2.516e-01,  4.067e-01,  8.973e-02,  2.017e-01},
            {  3.021e+00,  2.818e+00,  2.220e+00,  1.250e+00,  5.713e+01,  2.615e+00,  2.296e-02,  2.641e-02,  1.040e-02,  1.746e-02,  4.645e+01,  1.384e+01,  7.127e+00,  2.057e+00, -9.674e-02},
            {  4.050e-01,  3.480e-01,  4.126e-01,  1.687e-01,  2.615e+00,  7.216e-01,  1.581e-02,  1.177e-02,  1.585e-03,  8.841e-03,  2.161e+00,  3.361e-01,  2.421e+00,  4.444e-01,  7.708e-02},
            { -6.691e-02, -1.021e-02,  7.900e-02,  6.884e-03,  2.296e-02,  1.581e-02,  1.799e-02,  1.075e-03,  8.228e-05, -5.897e-04, -1.143e-01,  1.465e-01,  9.678e-03,  5.187e-02,  1.273e-03},
            {  2.447e-01,  7.137e-02,  3.939e-02,  9.276e-03,  2.641e-02,  1.177e-02,  1.075e-03,  8.658e-03,  4.431e-05,  7.488e-04, -3.198e-01, -1.815e-01,  1.731e-01,  6.114e-02,  2.023e-02},
            { -1.306e-02, -6.388e-04,  7.144e-03,  6.434e-04,  1.040e-02,  1.585e-03,  8.228e-05,  4.431e-05,  1.200e-04, -6.649e-05,  2.397e-02,  5.324e-03,  8.599e-03,  9.841e-04,  1.045e-03},
            {  3.087e-02,  2.926e-02,  2.884e-03,  4.373e-03,  1.746e-02,  8.841e-03, -5.897e-04,  7.488e-04, -6.649e-05,  6.347e-03, -1.133e-01,  2.368e-03,  2.057e-01,  2.448e-02,  2.246e-02},
            { -8.126e+01, -1.639e+00,  1.233e+01,  4.501e+00,  4.645e+01,  2.161e+00, -1.143e-01, -3.198e-01,  2.397e-02, -1.133e-01,  3.182e+03, -1.200e+02,  3.101e-01, -1.399e+01,  1.763e+01},
            { -1.601e+01,  8.133e+00,  3.676e+00, -2.516e-01,  1.384e+01,  3.361e-01,  1.465e-01, -1.815e-01,  5.324e-03,  2.368e-03, -1.200e+02,  3.946e+02,  3.451e+01,  1.497e+00,  2.006e+00},
            {  1.789e+01,  6.670e+00,  5.360e+00,  4.067e-01,  7.127e+00,  2.421e+00,  9.678e-03,  1.731e-01,  8.599e-03,  2.057e-01,  3.101e-01,  3.451e+01,  1.372e+02,  1.012e+01,  1.963e+00},
            {  5.536e+00,  5.999e-01,  1.160e+00,  8.973e-02,  2.057e+00,  4.444e-01,  5.187e-02,  6.114e-02,  9.841e-04,  2.448e-02, -1.399e+01,  1.497e+00,  1.012e+01,  9.865e+00,  6.006e-01},
            {  3.430e+00,  5.488e-01,  2.478e-01,  2.017e-01, -9.674e-02,  7.708e-02,  1.273e-03,  2.023e-02,  1.045e-03,  2.246e-02,  1.763e+01,  2.006e+00,  1.963e+00,  6.006e-01,  3.896e+00},
          };

          set_covariance(BKGCOV);

        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_20_001_EW_production)



    //
    // Derived analysis class for the Slepton search regions
    //
    class Analysis_CMS_SUS_20_001_Slepton : public Analysis_CMS_SUS_20_001
    {

      public:
        Analysis_CMS_SUS_20_001_Slepton()
        {
          set_analysis_name("CMS_SUS_20_001_Slepton");
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
            {  1.779e+03,  5.261e+02,  8.049e+01,  5.835e-01,  1.514e+03,  2.663e+02,  6.504e+01,  1.779e+01},
            {  5.261e+02,  3.024e+02,  2.857e+01,  2.160e+00,  5.096e+02,  9.804e+01,  2.575e+01,  7.001e+00},
            {  8.049e+01,  2.857e+01,  1.919e+01,  1.351e+00,  8.333e+01,  2.001e+01,  3.431e+00,  2.017e+00},
            {  5.835e-01,  2.160e+00,  1.351e+00,  4.298e+00, -1.159e+00, -4.992e-01, -2.374e-01, -3.336e-01},
            {  1.514e+03,  5.096e+02,  8.333e+01, -1.159e+00,  1.670e+03,  2.608e+02,  6.750e+01,  1.392e+01},
            {  2.663e+02,  9.804e+01,  2.001e+01, -4.992e-01,  2.608e+02,  1.825e+02,  1.545e+01,  1.083e+00},
            {  6.504e+01,  2.575e+01,  3.431e+00, -2.374e-01,  6.750e+01,  1.545e+01,  1.228e+01,  9.861e-01},
            {  1.779e+01,  7.001e+00,  2.017e+00, -3.336e-01,  1.392e+01,  1.083e+00,  9.861e-01,  6.608e+00},
          };

          set_covariance(BKGCOV);

        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_20_001_Slepton)

  }
}
