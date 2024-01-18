///
///  \author Holly Pacey
///  \date 2024 January
///
///  *********************************************

// Based on https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-19-010/index.html
// Luminosity: 137 fb^-1

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "SoftDrop.h" 

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_CMS_13TeV_0LETStop_139invfb : public Analysis
    {

    protected:

      Cutflows _cutflows;

    private:

      struct ptComparison
      {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;


    public:

      bool doCutflow = true;

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_13TeV_0LEPStop_137invfb()
      {
        set_analysis_name("CMS_13TeV_0LEPStop_137invfb");
        set_luminosity(137);
//
//      Counters for the number of accepted events for each signal region

//      Preselections:
//      Baseline: MET>250, Nj>=2, 0e+0mu, 0tau, Ht>300
//      Low dM: Nt+Nw+Nres=0, mTb<175 iff Nb>=1, dPhi(j123,MET)>0.5,0.15,0.15, N_ISR=1 & dPhi(MET, ISRjet)>2, MET/sqrt(Ht)>10
//      High dM: Nj>=5, Nb>=1, dPhi(MET,j1,2,3,4)>0.5

        if (doCutflow)
        {
            DEFINE_SIGNAL_REGION("Total");
            DEFINE_SIGNAL_REGION("baseline_MET");
            DEFINE_SIGNAL_REGION("baseline_MET_Nj");
            DEFINE_SIGNAL_REGION("baseline_MET_Nj_0e0mu");
            DEFINE_SIGNAL_REGION("baseline_MET_Nj_0e0mu_0tau");
            DEFINE_SIGNAL_REGION("baseline_MET_Nj_0e0mu_0tau_Ht");
            DEFINE_SIGNAL_REGION("lowmass_NtNwNres");
            DEFINE_SIGNAL_REGION("lowmass_NtNwNres_mTb");
            DEFINE_SIGNAL_REGION("lowmass_NtNwNres_mTb_dPhi");
            DEFINE_SIGNAL_REGION("lowmass_NtNwNres_mTb_dPhi_ISR");
            DEFINE_SIGNAL_REGION("lowmass_NtNwNres_mTb_dPhi_ISR_METHt");
            DEFINE_SIGNAL_REGION("highmass_Nj");
            DEFINE_SIGNAL_REGION("highmass_Nj_Nb");
            DEFINE_SIGNAL_REGION("highmass_Nj_Nb_dPhi");
        }

//        DEFINE_SIGNAL_REGION("SR1BH_1L"); //, "METSig > 7");
//
      }

      bool passOverlap(vector<const HEPUtils::Jet*> ResolvedTopCand, vector<const FJNS::PseudoJet*> MergedTopPseudoJets)
      {
        for (const HEPUtils::Jet* jet : ResolvedTopCand)
        {
          for (const FJNS::PseudoJet* pjet : MergedTopPseudoJets->constituents())
            double dR = deltaR_eta(jet->mom(), HEPUtils::Jet(pjet&)->mom());
            if (dR<0.4) return false;
        }
        return true;
      }

      double findMapValue(map<double, double> effMap, double pt)
      {
        double eff = -1.0;
        for (const auto& pair : effMap)
        {
          if (pt > pair.first)
          {
            eff = pair.second; 
          }
        }
        return eff;
      }


      void run(const HEPUtils::Event* event)
      {

        // Baseline objects
        vector<const HEPUtils::Particle*> Electrons;
        vector<const HEPUtils::Particle*> Muons;
        vector<const HEPUtils::Particle*> Taus;
        vector<const HEPUtils::Jet*> baselineJets;
        vector<const HEPUtils::Jet*> baselineFatJets;

        // Missing momentum and energy
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        // Baseline electrons have |eta|<2.5
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 5. && electron->abseta() < 2.5) Electrons.push_back(electron);
        }

        // Baseline muons have |eta|<2.4
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 5. && muon->abseta() < 2.4) Muons.push_back(muon);
        }

        // Baseline taus have |eta|<2.4, pT>20 GeV, mT<100GeV
        for (const HEPUtils::Particle* tau : event->taus())
        {
          if (tau->pT() > 20 && tau->abseta() < 2.4 && get_mT(tau, metVec) < 100.) Taus.push_back(tau);
        }

        // Only jet candidates with pT > 20 GeV and |η| < 2.4 are considered in the analysis
        double Ht = 0.; 
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT()>20. && jet->abseta()<2.4)
          {
            baselineJets.push_back(jet);
            Ht += jet->pT();
          }
        }

        for (const HEPUtils::Jet* jet : event->jets("antikt_R08"))
        {
          if (jet->pT()>200. && jet->abseta()<2.4)
          {
            baselineFatJets.push_back(jet);
          }
        }

        // Signal objects
        vector<const HEPUtils::Jet*> signalJets_20 = baselineJets;
        vector<const HEPUtils::Jet*> signalJets_30;
        vector<const HEPUtils::Jet*> signalBJets_20;
        vector<const HEPUtils::Jet*> signalBJets_30;
        vector<const HEPUtils::Jet*> signalFatJets;

        // Signal jets have pT > 30 GeV
        for (const HEPUtils::Jet* jet : baselineJets)
        {
          if (jet->pT() > 30.)
          {
            signalJets_30.push_back(jet);
          }
        }

        // Find b-jets
        vector<int> signalJets_20_isB;
        double btag = 0.68; double cmisstag = 0.012; double misstag = 0.01;
        for (const HEPUtils::Jet* jet : signalJets_20)
        {
          // Tag or Mistag c-jet
          if( (jet->btag() && random_bool(btag)) || (jet->ctag() && random_bool(cmisstag)) )
          {
            signalBJets_20.push_back(jet);
            signalJets_20_isB.push_back(1);
          }
          // Misstag light jet
          else if( random_bool(misstag) )
          {
            signalBJets_20.push_back(jet);
            signalJets_20_isB.push_back(0);
          }
        }

        // Signal jets have pT > 30 GeV
        for (const HEPUtils::Jet* jet : signalBJets_20)
        {
          if (jet->pT() > 30.)
          {
            signalJets_30.push_back(jet);
          }
        }

        // Find soft b-jets
        double softbtag = 0.475; double softmisstag = 0.035;
        for (const HEPUtils::Jet* jet : baselineJets)
        {
          // Tag
          if( jet->btag() && random_bool(softbtag) ) signalBJets_soft.push_back(jet);
          // Misstag light jet
          else if( random_bool(softmisstag) ) signalBJets_soft.push_back(jet);
        }
        removeOverlap(signalBJets_soft, signalBJets_20, 0.4);


        // Sort by pT
        sort(signalJets_20.begin(), signalJets_20.end(), compareJetPt);
        sort(signalJets_30.begin(), signalJets_30.end(), compareJetPt);
        sort(signalBJets_20.begin(), signalBJets_20.end(), compareJetPt);
        sort(signalBJets_30.begin(), signalBJets_30.end(), compareJetPt);
        sort(signalBJets_soft.begin(), signalBJets_soft.end(), compareJetPt);

        // Taggers
        
        // softDrop
        vector<const FJNS::PseudoJet*> SignalFatPseudoJets;
        double beta = 0.0;
        double z_cut = 0.1;
        double R0 = 0.8;
        SoftDrop sd(beta, z_cut, R0);
        for (const HEPUtils::Jet* jet : baselineFatJets)
        {
          FJNS::PseudoJet pj = jet->pseudojet();
          FJNS::PseudoJet groomed_jet = sd(pj);
          SignalFatPseudoJets.push_back(groomed_jet); 
        }

        // Merged Top
        map<double, double> MergedTop_Eff{ {0., 0.0}, {200., 0.000000077667}, {250., 0.0000058738}, {300., 0.00030479}, {350., 0.016794}, {400., 0.12272}, {450., 0.24526}, {500., 0.3266}, {550., 0.37828}, {600., 0.4164}, {650., 0.44189}, {700., 0.45802}, {750., 0.47089}, {800., 0.48097}, {850., 0.49454}, {900., 0.50686}, {950., 0.50204} };
        double QCDmistagTop_Eff = 0.005;
        vector<const HEPUtils::Jet*> MergedTopCands;
        vector<const FJNS::PseudoJet*> MergedTopPseudoJets;
        vector<bool> baselineFatJet_MergedTop;
        int count = 0;
        for (const HEPUtils::Jet* jet : baselineFatJets)
        {
          if (jet->pT() > 400. && signalFatPseudoJets.at[count]->m() > 105.)
          {
            // Tag boosted Top
            if( jet->btag() && random_bool(findMapValue(MergedTop_Eff, jet->pT())) )
            {
              MergedTopCands.push_back(jet);
              MergedTopPseudoJets.push_back(signalFatPseudoJets.at[count]);
              baselineFatJet_MergedTop.push_back(true);
            }
            // Misstag QCD
            else if( random_bool(QCDmistagTop_Eff) )
            {
              MergedTopCands.push_back(jet);
              MergedTopPseudoJets.push_back(signalFatPseudoJets.at[count]);
              baselineFatJet_MergedTop.push_back(true);
            }
            else
            {
              baselineFatJet_MergedTop.push_back(false);
            }
          }
          count++;
        }

        // Merged W
        map<double, double> W_Eff{ {0., 0.00000057412}, {50., 0.000024674}, {100., 0.013233}, {200., 0.16196}, {250., 0.2625}, {300., 0.31157}, {350., 0.35379}, {400., 0.37683}, {450., 0.39368}, {500., 0.41414}, {550., 0.4199}, {600., 0.43428}, {650., 0.47453}, {700., 0.45963}, {750., 0.46506}, {800., 0.43094}, {850., 0.47647}, {900., 0.44126}, {950., 0.47716} };
        double QCDmistagW_Eff = 0.01;
        vector<const FJNS::PseudoJet*> WPseudoJets;
        vector<const HEPUtils::Jet*> WCands;
        vector<bool> baselineFatJet_W;
        int countW = 0;
        for (const HEPUtils::Jet* jet : baselineFatJets)
        {
          if (jet->pT() > 200. && signalFatPseudoJets.at[count]->m() > 65. || signalFatPseudoJets.at[count]->m() < 105.)
          {
            // Tag boosted Top
            if( jet->btag() && random_bool(findMapValue(W_Eff, jet->pT())) )
            {
              WCands.push_back(jet);
              WPseudoJets.push_back(signalFatPseudoJets.at[countW]);
              baselineFatJet_W.push_back(true);
            }
            // Misstag QCD
            else if( random_bool(QCDmistagW_Eff) )
            {
              WCands.push_back(jet);
              WPseudoJets.push_back(signalFatPseudoJets.at[countW]);
              baselineFatJet_W.push_back(true);
            {
            else
            {
              baselineFatJet_W.push_back(false);
            }
          }
          int countW++;
        }

        // Resolved Top
        map<double, double> ResolvedTop_Eff{ {0., 0.036474}, {50., 0.11336}, {100., 0.1946}, {150., 0.25656}, {200., 0.29324}, {250., 0.30583}, {300., 0.30875}, {350., 0.29854}, {400., 0.19588}, {450., 0.10523}, {500., 0.061853}, {550., 0.036214}, {600., 0.020324}, {650., 0.010021}, {700., 0.0052826}, {750., 0.0031672}, {800., 0.0017965}, {850., 0.00064142}, {900., 0.0003081}, {950., 0.00040353} };        // Taggers
        double QCDmistagResTop_Eff = 0.02;
        // 3 smallR jets, pts >40,30,20 GeV, no more than 1 btag, all jets dR>3.1 of the centroid, no overlaps.
        vector<vector<const HEPUtils::Jet*>> ResolvedTopCands;
        vector<const HEPUtils::Jet*> ResolvedTopCand;
        set<int> jetsused;
        if (signalJets_20.size()>2)
        {
          for (int j1=0; j1<signalJets_20.size(); j1++)
          {
            if (jetsused.find(j1)!=jetsused.end()) continue;
            if (signalJets_20.at(j1)->pT()<=40.) continue; 
            for (int j2=1; j2<signalJets_20.size(); j2++)
            {
              if (j1<=j2) continue;
              if (jetsused.find(j2)!=jetsused.end()) continue;
              if (signalJets_20.at(j2)->pT()<=30.) continue; 
              for (int j3=2; j3<signalJets_20.size(); j3++)
              {
                if (j3<=j2) continue;
                if (signalJets_20.at(j3)->pT()<=20.) continue;
                // <=1 btag
                if ((signalJets_20_isB.at(j1) + signalJets_20_isB.at(j2) + signalJets_20_isB.at(j3)) > 1) continue;
                // near centroid
                P4 centroid = signalJets_20.at(j1)->mom() + signalJets_20.at(j3)->mom() + signalJets_20.at(j3)->mom();
                if (deltaR_eta(centroid, signaljets_20.at(j1)->mom()) >= 3.1) continue;
                else if (deltaR_eta(centroid, signaljets_20.at(j2)->mom()) >= 3.1) continue;
                else if (deltaR_eta(centroid, signaljets_20.at(j3)->mom()) >= 3.1) continue;
                // don't use if jet already been used.
                if (jetsused.find(j3)!=jetsused.end()) continue;
                // Tag resolved Top
                if( signalJets_20->at(j1)->tagged(6) && signalJets_20->at(j2)->tagged(6) && signalJets_20->at(j3)->tagged(6) && random_bool(findMapValue(ResolvedTop_Eff, centroid->pT())) ) ResolvedTopCands.push_back(jet);
                // Misstag QCD
                else if( random_bool(QCDmistagResTop_Eff) ) ResolvedTopCands.push_back(jet);
                // passed selections
                jetsused.insert(j1);
                jetsused.insert(j2);
                jetsused.insert(j3);
                ResolvedTopCand.clear();
                ResolvedTopCand.push_back(signalJets_20.at(j1));
                ResolvedTopCand.push_back(signalJets_20.at(j2));
                ResolvedTopCand.push_back(signalJets_20.at(j3));
                if (!passOverlap(ResolvedTopCand, MergedTopPseudoJets)) continue;
                if (!passOverlap(ResolvedTopCand, WPseudoJets)) continue;
                ResolvedTopCands.push_back(ResolvedTopCand);
              }
            }
          }
        }

        // Find non b-jets and non-tagged jets for ISR
        vector<const HEPUtils::Jet*> signalISRJets;
        double loosebtag = 0.80; double loosemisstag = 0.10;
        int f = 0;
        for (const HEPUtils::Jet* jet : baselineFatJets)
        {
          if (baselineFatJet_MergedTop.at(f) || baselineFatJet_W.at(f)) continue;
          if (delta_Phi(jet,metVec)<=2) continue;
          // Tag
          if( jet->btag() && !random_bool(loosebtag) ) signalISRJets.push_back(jet);
          // Misstag light jet
          else if( !random_bool(loosemisstag) ) signalISRJets.push_back(jet);
          f++;
        }

        // Count
        int n_MergedTop = MergedTopCands.size();
        int n_ResolvedTop = ResolvedTopCands.size();
        int n_W = WCands.size();
        int n_electrons = Electrons.size();
        int n_muons = Muons.size();
        int n_taus = Taus.size();
        int n_jets_20 = signalJets_20.size();
        int n_jets_30 = signalJets_30.size();
        int n_bjets_20 = signalBJets_20.size();
        int n_bjets_30 = signalBJets_30.size();
        int n_SV = signalBJets_soft.size();
        int n_ISR = signalISRJets.size();

        double mTb = -1.;
        if (n_bjets_30==1) mTb = get_mT(signal_bjets_30.at(0), metVec);
        else if (n_bjets_30>1) mTb = get_mT((signal_bjets_30.at(0)->mom()+signal_bjets_30.at(1)->mom()), metVec);

        /* Preselection */
        // True if passes this cut, false otherwise
        bool baseline_presel = false; // baseline Pre-selection cut
        bool low_dM_presel = false; // low dM Pre-selection cut
        bool high_dM_presel = false; // high dM Pre-selection cut

        // Perform all pre-selection cuts
        BEGIN_PRESELECTION
        while(true)
        {

            // Passes MET > 250 GeV
            if (met > 250.)
            {
              if (doCutflow){ FILL_SIGNAL_REGION("baseline_MET");}
              // Passes the Nj >= 2
              if (!(n_jets_30 >= 2))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("baseline_MET_Nj");}
              // Passes the e and mu veto
              if (!(n_electrons==0 && n_muons==0))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("baseline_MET_Nj_0e0mu");}
              // Passes the tau veto
              if (!(n_taus==0))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("baseline_MET_Nj_0e0mu_0tau");}
              // Passes Ht > 300 GeV
              if (!(Ht > 300.))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("baseline_MET_Nj_0e0mu_0tau_Ht");}
              // Set Baseline preselection as passed :)
              baseline_presel = true;
            }

            // Low dM selection
            if (baseline_presel)
            {
              // Passes the Nt+NW+Nres=0
              if (!((n_W + n_ResolvedTop + n_MergedTop)==0))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("lowmass_NtNwNres");}
              // Passes the mtb cut
              if (!(n_bjets_30==0 || (n_bjets_30>0 && mTb < 175.)))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("lowmass_NtNwNres_mTb");}
              // Passes the dPhi jet met cuts 
              if (!( (delta_Phi(signalJets_30.at(0),metVec)>0.5 && delta_Phi(signalJets_30.at(1),metVec)>0.15) && (n_jets_30==2 || delta_Phi(signalJets_30.at(2),metVec)>0.15)))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("lowmass_NtNwNres_mTb_dPhi");}
              // Passes ISR
              if (!(n_ISR==1))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("lowmass_NtNwNres_mTb_dPhi_ISR");}
              // Passes MET/HT
              if (!((met/sqrt(Ht)) > 10))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("lowmass_NtNwNres_mTb_dPhi_ISR_METHt");}
              // Set Low deltaM preselection as passed :)
              low_dM_presel = true;
            }
  
            // High dM selection
            if (baseline_presel)
            {
              // Passes the Nj cut
              if (!(n_jets_30 >= 5))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("highmass_Nj");}
              // Passes the Nb cut
              if (!(n_bjets_30 >= 1))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("highmass_Nj_Nb");}
              // Passes the dPhi jet met cuts
              if (!( delta_Phi(signalJets_30.at(0),metVec)>0.5 && delta_Phi(signalJets_30.at(1),metVec)>0.5 && delta_Phi(signalJets_30.at(2),metVec)>0.5 && delta_Phi(signalJets_30.at(3),metVec)>0.5 ))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("highmass_Nj_Nb_dPhi");}
              // Set Low deltaM preselection as passed :)
              high_dM_presel = true;
            }
  
  
            // Applied all cuts
            break;
  
        }

        // If event doesn't pass Pre-selection, exit early
        if (!(oneLep_presel || threeLep_presel)) return;

        END_PRESELECTION

        /* Signal Regions */

        // Initialise some useful variables
        double mT2_3l = -1.;
        double mT = -1.;
        double pTl3 = -1.;
        int n_higgs = -1;
        // SFOS info
        double mSFOS_Z = 100000000.;
        double pTSFOS_Z = -1.;
        HEPUtils::Particle SFOS_Z_net;

        // Calculate them
        if (threeLep_presel)
        {
          // get the SFOS info
          vector<const HEPUtils::Particle*> SFOS_Z;
          if (SFOSpairs.size() > 0)
          {
              for (vector<const HEPUtils::Particle*> SFOSpair : SFOSpairs)
              {
                  double pTll = (SFOSpair.at(0)->mom()+SFOSpair.at(1)->mom()).pT();
                  double mll = (SFOSpair.at(0)->mom()+SFOSpair.at(1)->mom()).m();
                  if (abs(mll - 91.2) < mSFOS_Z)
                  {
                      mSFOS_Z = mll;
                      pTSFOS_Z = pTll;
                      SFOS_Z = SFOSpair;
                  }
              }
              SFOS_Z_net = Particle((SFOS_Z.at(0)->mom()+SFOS_Z.at(1)->mom()), SFOS_Z.at(0)->pid());
          }
          mT2_3l = get_mT2(signalLeptons.at(2), &SFOS_Z_net, metVec, 0.);
          pTl3 = signalLeptons.at(2)->pT();
        }
        else if (oneLep_presel)
        {
          mT = get_mT(signalLeptons.at(0), metVec);
          // Do NN Higgs->bb tagger
          double sigEff = 0.54; // 50%-54% depending on signal mass.
          double bgEff = 0.05; // for ttbar events.
          n_higgs = 0;
          vector<vector<const HEPUtils::Jet*>> JetPairs = getBJetPairs(signalJets);
          for (vector<const HEPUtils::Jet*> JetPair : JetPairs)
          {
            // Tag
            if (JetPair.at(0)->tagged(25) && JetPair.at(1)->tagged(25))
            {
              if (random_bool(sigEff)) n_higgs += 1;
            }
            // Misstag light jet
            else if(random_bool(bgEff)) n_higgs += 1;
          }
        }

        // SR1AZ 3lepton
        while (true)
        {
          if (threeLep_presel)
          {
            if (doCutflow){ FILL_SIGNAL_REGION("SR1AZ_3L_presel")};
            if (pTl3 > 20.)
            {
              if (doCutflow){ FILL_SIGNAL_REGION("SR1AZ_3L_presel_pTl3")};
              if (abs(mSFOS_Z - 91.2) < 15.)
              {
                if (doCutflow){ FILL_SIGNAL_REGION("SR1AZ_3L_presel_pTl3_mZ")};
                if (n_bjets >= 1)
                {
                  if (doCutflow){ FILL_SIGNAL_REGION("SR1AZ_3L_presel_pTl3_mZ_nbjets")};
                  if (n_jets >= 4)
                  {
                    if (doCutflow){ FILL_SIGNAL_REGION("SR1AZ_3L_presel_pTl3_mZ_nbjets_njets")};
                    if (met > 250.)
                    {
                      if (doCutflow){ FILL_SIGNAL_REGION("SR1AZ_3L_presel_pTl3_mZ_nbjets_njets_MET")};
                      if (mT2_3l > 100.)
                      {
                        FILL_SIGNAL_REGION("SR1AZ_3L");
                      }
                    }
                    else {break;}
                  }
                  else {break;}
                }
                else {break;}
              }
              else {break;}
            }
            else {break;}
          }
          else {break;}
          // Applied all cuts
          break;
        }

        // SR1BZ 3lepton
        while (true)
        {

          if (threeLep_presel)
          {
            if (doCutflow){ FILL_SIGNAL_REGION("SR1BZ_3L_presel")};
            if (pTl3 > 20.)
            {
              if (doCutflow){ FILL_SIGNAL_REGION("SR1BZ_3L_presel_pTl3")};
              if (abs(mSFOS_Z - 91.2) < 15.)
              {
                if (doCutflow){ FILL_SIGNAL_REGION("SR1BZ_3L_presel_pTl3_mZ")};
                if (n_bjets >= 1)
                {
                  if (doCutflow){ FILL_SIGNAL_REGION("SR1BZ_3L_presel_pTl3_mZ_nbjets")};
                  if (n_jets >= 5)
                  {
                    if (doCutflow){ FILL_SIGNAL_REGION("SR1BZ_3L_presel_pTl3_mZ_nbjets_njets")};
                    if (met > 150.)
                    {
                      if (doCutflow){ FILL_SIGNAL_REGION("SR1BZ_3L_presel_pTl3_mZ_nbjets_njets_MET")};
                      if (pTSFOS_Z > 150.)
                      {
                        if (doCutflow){ FILL_SIGNAL_REGION("SR1BZ_3L_presel_pTl3_mZ_nbjets_njets_MET_pTll")};
                        if (signalBJets.at(0)->pT() > 100.)
                        {
                          FILL_SIGNAL_REGION("SR1BZ_3L");
                        }
                      }
                      else {break;}
                    }
                    else {break;}
                  }
                  else {break;}
                }
                else {break;}
              }
              else {break;}
            }
            else {break;}
          }
          else {break;}
          // Applied all cuts
          break;
        }

        while (true)
        {
          // SR2AZ 3lepton
          if (threeLep_presel)
          {
            if (doCutflow){ FILL_SIGNAL_REGION("SR2AZ_3L_presel")};
            if (pTl3 < 20.)
            {
              if (doCutflow){ FILL_SIGNAL_REGION("SR2AZ_3L_presel_pTl3")};
              if (abs(mSFOS_Z - 91.2) < 15.)
              {
                if (doCutflow){ FILL_SIGNAL_REGION("SR2AZ_3L_presel_pTl3_mZ")};
                if (signalJets.at(0)->pT() > 150.)
                {
                  if (doCutflow){ FILL_SIGNAL_REGION("SR2AZ_3L_presel_pTl3_mZ_pTj1")};
                  if (met > 200.)
                  {
                    if (doCutflow){ FILL_SIGNAL_REGION("SR2AZ_3L_presel_pTl3_mZ_pTj1_MET")};
                    if (pTSFOS_Z < 50.)
                    {
                      FILL_SIGNAL_REGION("SR2AZ_3L");
                    }
                  }
                  else {break;}
                }
                else {break;}
              }
              else {break;}
            }
            else {break;}
          }
          else {break;}
          // Applied all cuts
          break;
        }

        while (true)
        {
          // SR2BZ 3lepton
          if (threeLep_presel)
          {
            if (doCutflow){ FILL_SIGNAL_REGION("SR2BZ_3L_presel")};
            if (pTl3 < 60.)
            {
              if (doCutflow){ FILL_SIGNAL_REGION("SR2BZ_3L_presel_pTl3")};
              if (abs(mSFOS_Z - 91.2) < 15.)
              {
                if (doCutflow){ FILL_SIGNAL_REGION("SR2BZ_3L_presel_pTl3_mZ")};
                if (n_bjets >= 1)
                {
                  if (doCutflow){ FILL_SIGNAL_REGION("SR2BZ_3L_presel_pTl3_mZ_nbjets")};
                  if (met > 350.)
                  {
                    if (doCutflow){ FILL_SIGNAL_REGION("SR2BZ_3L_presel_pTl3_mZ_nbjets_MET")};
                    if (pTSFOS_Z > 150.)
                    {
                      FILL_SIGNAL_REGION("SR2BZ_3L");
                    }
                  }
                  else {break;}
                }
                else {break;}
              }
              else {break;}
            }
            else {break;}
          }
          else {break;}
          // Applied all cuts
          break;
        }

        while (true)
        {
          // SR1AH 1lepton
          if (oneLep_presel)
          {
            if (doCutflow){ FILL_SIGNAL_REGION("SR1AH_1L_presel")};
            if (n_bjets >= 4)
            {
              if (doCutflow){ FILL_SIGNAL_REGION("SR1AH_1L_presel_nbjets")};
              if (n_higgs >= 1)
              {
                if (doCutflow){ FILL_SIGNAL_REGION("SR1AH_1L_presel_nbjets_nh")};
                if (mT > 150.)
                {
                  if (doCutflow){ FILL_SIGNAL_REGION("SR1AH_1L_presel_nbjets_nh_mT")};
                  if (n_jets_sixty >= 4)
                  {
                    if (doCutflow){ FILL_SIGNAL_REGION("SR1AH_1L_presel_nbjets_nh_mT_njets")};
                    if (metsig > 12.)
                    {
                      FILL_SIGNAL_REGION("SR1AH_1L");
                    }
                  }
                  else {break;}
                }
                else {break;}
              }
              else {break;}
            }
            else {break;}
          }
          else {break;}
          // Applied all cuts
          break;
        }

        while (true)
        {
          // SR1BH 1lepton
          if (oneLep_presel)
          {
            if (doCutflow){ FILL_SIGNAL_REGION("SR1BH_1L_presel")};
            if (n_bjets >= 4)
            {
              if (doCutflow){ FILL_SIGNAL_REGION("SR1BH_1L_presel_nbjets")};
              if (n_higgs >= 1)
              {
                if (doCutflow){ FILL_SIGNAL_REGION("SR1BH_1L_presel_nbjets_nh")};
                if (mT > 150.)
                {
                  if (doCutflow){ FILL_SIGNAL_REGION("SR1BH_1L_presel_nbjets_nh_mT")};
                  if (n_jets_sixty >= 6)
                  {
                    if (doCutflow){ FILL_SIGNAL_REGION("SR1BH_1L_presel_nbjets_nh_mT_njets")};
                    if (metsig > 7.)
                    {
                      FILL_SIGNAL_REGION("SR1BH_1L");
                    }
                  }
                  else {break;}
                }
                else {break;}
              }
              else {break;}
            }
            else {break;}
          }
          else {break;}
          // Applied all cuts
          break;
        }

      } // End run function

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {
        // Obs. Exp. Err.

        if (doCutflow)
        {
            COMMIT_SIGNAL_REGION("Total", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("baseline_MET", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("baseline_MET_Nj", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("baseline_MET_Nj_0e0mu", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("baseline_MET_Nj_0e0mu_0tau", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("baseline_MET_Nj_0e0mu_0tau_Ht", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("lowmass_NtNwNres", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("lowmass_NtNwNres_mTb", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("lowmass_NtNwNres_mTb_dPhi", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("lowmass_NtNwNres_mTb_dPhi_ISR", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("lowmass_NtNwNres_mTb_dPhi_ISR_METHt", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("highmass_Nj", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("highmass_Nj_Nb", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("highmass_Nj_Nb_dPhi", 1., 1., 1.);
        }

        COMMIT_SIGNAL_REGION("SR1AZ_3L", 3.,  5.7,  1.0);
        COMMIT_SIGNAL_REGION("SR1BZ_3L", 14., 12.1, 2.0);
        COMMIT_SIGNAL_REGION("SR2AZ_3L", 3.,  5.6,  1.6);
        COMMIT_SIGNAL_REGION("SR2BZ_3L", 6.,  5.5,  0.9);
        COMMIT_SIGNAL_REGION("SR1AH_1L", 11., 17.0, 3.0);
        COMMIT_SIGNAL_REGION("SR1BH_1L", 24., 3.0,  5.0);

        COMMIT_CUTFLOWS;

      }

    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters)
        {
          pair.second.reset();
        }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_0LEPStop_137invfb);

  }
}
