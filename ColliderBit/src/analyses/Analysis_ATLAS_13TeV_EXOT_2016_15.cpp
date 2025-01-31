///
///  \author Christopher Chang
///  \date 2024 November
///
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/EXOT-2016-15/
// HepData: https://www.hepdata.net/record/77266

#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ROOT

#include <vector>

#include "gambit/Utils/threadsafe_rng.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisUtil.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "HEPUtils/FastJet.h"
#include "TRandom3.h"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {


    bool sortByPT_jet_convenience(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2)
    {
      return (jet1->pT() > jet2->pT());
    }
      
      
    // Sort by jet pT for sharedptr
    bool sortByPT_jet_convenience_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2)
    {
      return sortByPT_jet_convenience(jet1.get(), jet2.get());
    }


    class Analysis_ATLAS_13TeV_EXOT_2016_15 : public Analysis
    {

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_EXOT_2016_15()
      {

        DEFINE_SIGNAL_REGION("SR0", ">= 1 baseline lep", ">= 1 signal lep", "1 signal lep", "1 baseline lep", "ETmiss > 200 GeV", ">= 4 jets", "|dPhi(j_i, ETmiss)| > 0.4m j_i=1,2", "m_T^W > 120 GeV", ">= 1 b-jet", "am_T2 > 175 GeV", "m^tau_T2 > 80 GeV", "ETmiss > 350 GeV", "m_T^W > 170 GeV", "HTmiss_sig > 12", "small-R jet pT", "1st large-R jet", "2nd large-R jet")


        set_analysis_name("ATLAS_13TeV_EXOT_2016_15");
        set_luminosity(36.1);

      }

      // Lepton jet overlap removal
      // Discards leptons if they are within DeltaRMax of a jet
      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*>& leptons, vector<const HEPUtils::Jet*>& jets)
      {
        vector<const HEPUtils::Particle*> survivors;
        for(const HEPUtils::Particle* lepton : leptons)
        {
          bool overlap = false;
          double DeltaRMax = min(0.4,0.04 + 10 / (lepton->pT()));
          for(const HEPUtils::Jet* jet : jets)
          {
            double dR = jet->mom().deltaR_eta(lepton->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(lepton);
        }
        leptons = survivors;
        return;
      }
      
      // Calculate transverse mass
      double mTrans(HEPUtils::P4 particle, HEPUtils::P4 jet)
      {
        double mT = sqrt( pow(particle.pT()+jet.pT(),2) - pow(particle.px()+jet.px(),2) - pow(particle.py()+jet.py(),2) );
        return mT;
      }
      
      double mTrans(HEPUtils::P4 particle)
      {
        double mT = sqrt( particle.m2() + particle.px2() + particle.py2() );
        return mT;
      }
      

      // Main run call
      void run(const HEPUtils::Event* event)
      {
        // Missing momentum and energy
        double met = event->met();
        HEPUtils::P4 ptot = event->missingmom();
        
        // Baseline lepton objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 7 && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_VeryLoose"));

        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 6 && muon->abseta() < 2.7) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        applyEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_Iso_Loose"));


        // tau leptons
        std::vector<const HEPUtils::Particle*> baselineTaus;
        for (const HEPUtils::Particle* tau : event->taus())
        {
          if (tau->pT() > 20 && tau->abseta() < 2.5) baselineTaus.push_back(tau);
        }
        
        // TODO: Apply tau efficiency?
        

        // Jets
        std::vector<const HEPUtils::Jet*> baselineBJets, baselineNonBJets;
        double btag = 0.77; double cmisstag = 1/6.0; double misstag = 1/130.;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        { if (jet->pT() > 20.0 && jet->abseta() < 4.4)
          {
            if (jet->btag() && random_bool(btag) ) baselineBJets.push_back(jet);
            else if (jet->ctag() && random_bool(cmisstag) ) baselineBJets.push_back(jet);
            else if (random_bool(misstag)) baselineBJets.push_back(jet);
            else baselineNonBJets.push_back(jet);
          }
        }

        // TODO: vertex tagger criteria not currently possible
        // TODO: veto events when a baseline jet does not pass the Loose jet quality criteria


        // Remove Overlapped electrons, muons and jets
        // 1. Jets are rejected if they lie within deltaR=0.2 of a electron
        removeOverlap(baselineNonBJets, baselineElectrons, 0.2);
        removeOverlap(baselineBJets, baselineElectrons, 0.2);
        // 2. Jets are rejected if they lie within deltaR=0.4 of a muon (If the jet has fewer than 3 tracks with pT > 500 MeK, which we cannot know)
        removeOverlap(baselineNonBJets, baselineMuons, 0.4);
        removeOverlap(baselineBJets, baselineMuons, 0.4);
        // 3. Muons are removed if theu lie in a cone (see function for size) around a jet
        LeptonJetOverlapRemoval(baselineMuons, baselineNonBJets);
        LeptonJetOverlapRemoval(baselineMuons, baselineBJets);
        // 4. Electrons are removed if they lie within deltaR=0.4 of a jet
        removeOverlap(baselineElectrons, baselineNonBJets, 0.4);
        removeOverlap(baselineElectrons, baselineBJets, 0.4);
        // 5. Electrons are removed if they lie within deltaR=0.1 of a tau
        removeOverlap(baselineElectrons, baselineTaus, 0.1);
        


        // TODO: Remove small-R jets with less than 5% of their large-R jet pT
        //       This is only possible if I do the jet finding here

        // Initialize cutflow counters
        BEGIN_PRESELECTION
        // There is no particular preseletion cut
        END_PRESELECTION

          /////////////////////
         // Signal Objects  //
        /////////////////////


        vector<const HEPUtils::Particle*> signalElectrons, signalMuons;
        for(auto &electron: baselineElectrons)
        {
          if (electron->pT() > 28) signalElectrons.push_back(electron);
        }
        applyEfficiency(signalElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Tight"));
        // TODO: isolation wrt tracks?
        
        for(auto &muon: baselineMuons)
        {
          if (muon->pT() > 28) signalMuons.push_back(muon);
        }
        applyEfficiency(signalMuons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Medium"));
        
        
        vector<const HEPUtils::Jet*> signalNonBJets;
        vector<const HEPUtils::Jet*> signalBJets;
        

        // Get jets (including b-tagged)
        for (const Jet* jet : baselineNonBJets)
        {
          if (jet->pT() > 25 && jet->abseta() < 2.5 ) signalNonBJets.push_back(jet);
        }

        for (const Jet* jet : baselineBJets)
        {
          if (jet->pT() > 25 && jet->abseta() < 2.5 ) signalBJets.push_back(jet);
        }
        
        SIGNAL_JET_COMBINATION(signalJets, signalNonBJets, signalBJets)
        SIGNAL_PARTICLE_COMBINATION(signalLeptons, signalElectrons, signalMuons)
        
        // Get large-R jets by reclustering small-R jets
        vector<std::shared_ptr<HEPUtils::Jet>> signalJets_largeR=get_jets(signalJets,1.0);
        
        
        


        // Sort in order of decreasing pT
        sortByPt(baselineTaus);
        sortByPt(signalBJets);
        sortByPt(signalNonBJets);
        sortByPt(signalJets);
        std::sort(signalJets_largeR.begin(), signalJets_largeR.end(), sortByPT_jet_convenience_sharedptr);
        sortByPt(signalElectrons);
        sortByPt(signalMuons);
        sortByPt(signalLeptons);
        



        // HT miss significance
        double HtSigMiss = 0.0;
        if (signalLeptons.size() > 0 && signalJets.size() > 0)
        {
          const std::vector<double>  binedges_eta = {0,10.};
          const std::vector<double>  binedges_pt = {0,50.,70.,100.,150.,200.,1000.,10000.};
          const std::vector<double> JetsJER = {0.145,0.115,0.095,0.075,0.07,0.05,0.04};
          static HEPUtils::BinnedFn2D<double> _resJets2D(binedges_eta,binedges_pt,JetsJER);
          vector<double> signalJER;

          for(unsigned int i = 0; i < signalJets.size(); ++i)
          {
            signalJER.push_back(_resJets2D.get_at(signalJets[i]->abseta(), signalJets[i]->pT()));
          }
        
        
          TRandom3 myRandom;
          myRandom.SetSeed(signalJets[0]->pT());
          HEPUtils::P4 leptonHtMiss;
          leptonHtMiss -= signalLeptons[0]->mom();
        
          int PEs = 100;
          double ETmissmean = 0, ETmissRMS = 0;
          double sigmaAbsHtMiss = 0.0;
          for (int j = 0; j < PEs; ++j)
          {
            double jetHtx = leptonHtMiss.px();
            double jetHty = leptonHtMiss.py();

            for (unsigned int i = 0; i < signalJets.size(); ++i)
            {
              jetHtx -= myRandom.Gaus(signalJets[i]->mom().px(), signalJets[i]->mom().px() * signalJER[i]);
              jetHty -= myRandom.Gaus(signalJets[i]->mom().py(), signalJets[i]->mom().px() * signalJER[i]);
            }
            double ETtemp = sqrt(jetHtx * jetHtx + jetHty * jetHty);
            ETmissmean += ETtemp;
            ETmissRMS  += ETtemp * ETtemp;
          }
        
          ETmissmean = ETmissmean / PEs;
          sigmaAbsHtMiss = sqrt((ETmissRMS / PEs) - ETmissmean * ETmissmean);
        
          if (sigmaAbsHtMiss > 0.0) // Prevent dividing by zero
          {
            HtSigMiss = (ETmissmean - 100.) / sigmaAbsHtMiss;
          }
        }
        


          /////////////////////
         // Event Selection //
        /////////////////////


        bool nbaselinelep_geq_1 = false;
        bool nbaselinelep_eq_1 = false;
        bool nsiglep_geq_1 = false;
        bool nsiglep_eq_1 = false;
        
        bool ETmiss_gt_200 = false;
        bool ETmiss_gt_350 = false;
        
        bool nsigjet_geq_4 = false;
        
        bool dPhi_gt_0pt4 = false;
        
        bool mTW_gt_120 = false;
        bool mTW_gt_170 = false;
        
        bool nbjet_geq_1 = false;
        
        bool am_T2_gt_175 = false;
        
        bool mtau_T2_condition = false;
        
        bool HtSigMiss_gt_12 = false;
        
        bool small_jet_pt = false;
        
        bool largeRjet_1 = false;
        bool largeRjet_2 = false;
        

        // Performing the Cuts
        while(true)
        {
        
          // Require at least 1 baseline lepton
          int nbaselinelep = baselineElectrons.size() + baselineMuons.size() + baselineTaus.size();
          if (nbaselinelep >= 1) {nbaselinelep_geq_1 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require at least 1 signal lepton
          int nsiglep = signalLeptons.size();
          if (nsiglep >= 1) {nsiglep_geq_1 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require exactly 1 signal lepton
          if (nsiglep == 1) {nsiglep_eq_1 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require exactly 1 baseline lepton
          if (nbaselinelep == 1) {nbaselinelep_eq_1 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require ETmiss > 200 GeV
          if (met > 200) {ETmiss_gt_200 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require at least 4 signal jets
          int nsigjet = signalJets.size();
          if (nsigjet >= 4) {nsigjet_geq_4 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require |deltaPhi(j_i, ETmiss)| > 0.4, i = 1,2
          double dPhi_1 = signalJets[0]->mom().deltaPhi(ptot);
          double dPhi_2 = signalJets[1]->mom().deltaPhi(ptot);
          if (dPhi_1 > 0.4 && dPhi_2 > 0.4) {dPhi_gt_0pt4 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require m_T^W > 120 GeV
          double mTW = sqrt(2.*(signalLeptons[0]->mom().pT()) * met * (1.0 - cos(signalLeptons[0]->mom().deltaPhi(ptot))));
          if (mTW > 120) {mTW_gt_120 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require at least 1 b-jet
          int nbjet = signalBJets.size();
          if (nbjet >= 1) {nbjet_geq_1 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require  am_T2 > 175 GeV
          // TODO: This is based on the two jets with the highest b-tagging weights, this is info we don't have
          //       so I will at first take two B-jets with the highest pT, and if only one, then I will take the non-b-jet with the highest pT
          double am_T2 = 0.0;
          if (nbjet == 1)
          {
            double mT_v1_case_1 = mTrans(signalLeptons[0]->mom(), signalBJets[0]->mom());
            double mT_v2_case_1 = mTrans(signalNonBJets[0]->mom());
            double max_mT_case_1 = (mT_v1_case_1 > mT_v2_case_1) ? mT_v1_case_1 : mT_v2_case_1;
            double mT_v1_case_2 = mTrans(signalBJets[0]->mom());
            double mT_v2_case_2 = mTrans(signalLeptons[0]->mom(), signalNonBJets[0]->mom());
            double max_mT_case_2 = (mT_v1_case_2 > mT_v2_case_2) ? mT_v1_case_2 : mT_v2_case_2;
            
            am_T2 = (max_mT_case_1 < max_mT_case_2) ? max_mT_case_1 : max_mT_case_2;
            
          }
          else
          {
            double mT_v1_case_1 = mTrans(signalLeptons[0]->mom(), signalBJets[0]->mom());
            double mT_v2_case_1 = mTrans(signalBJets[1]->mom());
            double max_mT_case_1 = (mT_v1_case_1 > mT_v2_case_1) ? mT_v1_case_1 : mT_v2_case_1;
            double mT_v1_case_2 = mTrans(signalBJets[0]->mom());
            double mT_v2_case_2 = mTrans(signalLeptons[0]->mom(), signalBJets[1]->mom());
            double max_mT_case_2 = (mT_v1_case_2 > mT_v2_case_2) ? mT_v1_case_2 : mT_v2_case_2;
            
            am_T2 = (max_mT_case_1 < max_mT_case_2) ? max_mT_case_1 : max_mT_case_2;
          }
          
          if (am_T2 > 175) {am_T2_gt_175 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require  m^tau_T2 > 80 GeV
          // It looks like this condition should only occur if there is a tau in the event (otherwise pass the cut??)
          double mtau_T2 = 0.0;
          int ntaus = baselineTaus.size();
          if (ntaus > 0)
          {
            double mT_v1 = mTrans(baselineTaus[0]->mom());
            double mT_v2 = mTrans(signalLeptons[0]->mom());
            double max_mT = (mT_v1 > mT_v2) ? mT_v1 : mT_v2;
            
            mtau_T2 = max_mT; // There is no min taken because there is only one 'case'
          }
          
          if (ntaus > 0 && mtau_T2 > 80) {mtau_T2_condition = true;}
          else if (ntaus == 0) {mtau_T2_condition = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require  ETmiss > 350 GeV
          if (met > 350) {ETmiss_gt_350 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require  m_T^W > 170 GeV
          if (mTW > 170) {mTW_gt_170 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require  HTmiss_sig > 12
          if (HtSigMiss > 12) {HtSigMiss_gt_12 = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require small-R jet pTs > 120, 80, 50, 25 Gev respectively
          double jet1_pT = signalJets[0]->pT();
          double jet2_pT = signalJets[1]->pT();
          double jet3_pT = signalJets[2]->pT();
          double jet4_pT = signalJets[3]->pT();
          if (jet1_pT > 120 && jet2_pT > 80 && jet3_pT > 50 && jet4_pT > 25) {small_jet_pt = true;}
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require 1st large radius jet with:
          //     pT > 290 GeV if ETmiss < 450 GeV,
          //  or pT > 200 if ETMiss > 450 GeV
          //  and mass > 80 GeV
          int njets_largeR = signalJets_largeR.size();
          if (njets_largeR > 0 &&
              met < 450 &&
              signalJets_largeR[0]->pT() > 290 &&
              signalJets_largeR[0]->mom().m() > 80)
          {
            largeRjet_1 = true;
          }
          else if (njets_largeR > 0 &&
                   met >= 450 &&
                   signalJets_largeR[0]->pT() > 200 &&
                   signalJets_largeR[0]->mom().m() > 80)
          {
            largeRjet_1 = true;
          }
          else break;
          
          LOG_CUT("SR0")
          
          
          // Require 2nd  large radius jet with:
          //     pT > 290 GeV if ETmiss < 450 GeV,
          //  or pT > 200 if ETMiss > 450 GeV
          //  and mass > 60 GeV
          if (njets_largeR > 1 &&
              met < 450 &&
              signalJets_largeR[1]->pT() > 290 &&
              signalJets_largeR[1]->mom().m() > 60)
          {
            largeRjet_2 = true;
          }
          else if (njets_largeR > 1 &&
                   met >= 450 &&
                   signalJets_largeR[1]->pT() > 200 &&
                   signalJets_largeR[1]->mom().m() > 60)
          {
            largeRjet_2 = true;
          }
          else break;
          
          LOG_CUT("SR0")

          // Applied all cuts
          break;
        }
        
        
        // Only fill the signal region if all cuts are passed
        if (nbaselinelep_geq_1 &&
            nbaselinelep_eq_1 &&
            nsiglep_geq_1 &&
            nsiglep_eq_1 &&
            ETmiss_gt_200 &&
            ETmiss_gt_350 &&
            nsigjet_geq_4 &&
            dPhi_gt_0pt4 &&
            mTW_gt_120 &&
            mTW_gt_170 &&
            nbjet_geq_1 &&
            am_T2_gt_175 &&
            mtau_T2_condition &&
            HtSigMiss_gt_12 &&
            small_jet_pt &&
            largeRjet_1 &&
            largeRjet_2)
        {
          FILL_SIGNAL_REGION("SR0")
        }
        
      }


      virtual void collect_results()
      {
        COMMIT_SIGNAL_REGION("SR0", 7, 6.1, 1.9)
        

        COMMIT_CUTFLOWS

      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_EXOT_2016_15)

  }
}

#endif
