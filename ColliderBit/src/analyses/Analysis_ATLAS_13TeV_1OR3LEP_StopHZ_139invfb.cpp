///
///  \author Holly Pacey
///  \date 2023 December
///
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-21/
// Luminosity: 139 fb^-1

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "METSignificance/METSignificance.hpp"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_1OR3LEP_StopHZ_139invfb : public Analysis
    {

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

      bool doCutflow = false;

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_1OR3LEP_StopHZ_139invfb()
      {
        set_analysis_name("ATLAS_13TeV_1OR3LEP_StopHZ_139invfb");
        set_luminosity(139);
//
//      Counters for the number of accepted events for each signal region

//      3l preselection = Trigger, >=3 signal leptons, njets(pt>30GeV)>=3, MET>50 GeV, pTl1>40 GeV, pTl2>20 GeV, nSFOS>=1
//      1l preselection = Trigger, 1 signal lepton, Veto events with >=2 baseline leptons. njets(pt>30GeV)>=4, nbjets(pt>30GeV)>=3


        if (doCutflow)
        {
            DEFINE_SIGNAL_REGION_NOCUTS("Total");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AZ_3L_presel");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AZ_3L_presel_pTl3");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AZ_3L_presel_pTl3_mZ");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AZ_3L_presel_pTl3_mZ_nbjets");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AZ_3L_presel_pTl3_mZ_nbjets_njets");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AZ_3L_presel_pTl3_mZ_nbjets_njets_MET");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BZ_3L_presel");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BZ_3L_presel_pTl3");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BZ_3L_presel_pTl3_mZ");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BZ_3L_presel_pTl3_mZ_nbjets");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BZ_3L_presel_pTl3_mZ_nbjets_njets");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BZ_3L_presel_pTl3_mZ_nbjets_njets_MET");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BZ_3L_presel_pTl3_mZ_nbjets_njets_MET_pTll");
            DEFINE_SIGNAL_REGION_NOCUTS("SR2AZ_3L_presel");
            DEFINE_SIGNAL_REGION_NOCUTS("SR2AZ_3L_presel_pTl3");
            DEFINE_SIGNAL_REGION_NOCUTS("SR2AZ_3L_presel_pTl3_mZ");
            DEFINE_SIGNAL_REGION_NOCUTS("SR2AZ_3L_presel_pTl3_mZ_pTj1");
            DEFINE_SIGNAL_REGION_NOCUTS("SR2AZ_3L_presel_pTl3_mZ_pTj1_MET");
            DEFINE_SIGNAL_REGION_NOCUTS("SR2BZ_3L_presel");
            DEFINE_SIGNAL_REGION_NOCUTS("SR2BZ_3L_presel_pTl3");
            DEFINE_SIGNAL_REGION_NOCUTS("SR2BZ_3L_presel_pTl3_mZ");
            DEFINE_SIGNAL_REGION_NOCUTS("SR2BZ_3L_presel_pTl3_mZ_nbjets");
            DEFINE_SIGNAL_REGION_NOCUTS("SR2BZ_3L_presel_pTl3_mZ_nbjets_MET");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AH_1L_presel");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AH_1L_presel_nbjets");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AH_1L_presel_nbjets_nh");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AH_1L_presel_nbjets_nh_mT");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1AH_1L_presel_nbjets_nh_mT_njets");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BH_1L_presel");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BH_1L_presel_nbjets");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BH_1L_presel_nbjets_nh");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BH_1L_presel_nbjets_nh_mT");
            DEFINE_SIGNAL_REGION_NOCUTS("SR1BH_1L_presel_nbjets_nh_mT_njets");
        }

//      SR1AZ_3L =  "3l preselection", "pTl3 > 20 GeV", "|mSFOS-mZ| < 15 GeV", "nbjets >= 1", "njets >= 4", "MET > 250 GeV", "mT2(3l) > 100 GeV"
        DEFINE_SIGNAL_REGION_NOCUTS("SR1AZ_3L"); // MT2(3L)

//      SR1BZ_3L = "3l preselection", "pTl3 > 20 GeV", "|mSFOS-mZ| < 15 GeV", "nbjets >= 1", "njets >= 5", "MET > 150 GeV", "pTll > 150 GeV", "pTb1 > 100 GeV"
        DEFINE_SIGNAL_REGION_NOCUTS("SR1BZ_3L"); //, "pTb1 > 100 GeV");

//      SR2AZ_3L = "3l preselection", "pTl3 < 20 GeV", "|mSFOS-mZ| < 15 GeV", "pTj1 > 150 GeV", "MET > 200 GeV", "pTll < 50 GeV"
        DEFINE_SIGNAL_REGION_NOCUTS("SR2AZ_3L"); //, "pTll < 50 GeV");

//      SR2BZ_3L = "3l preselection", "pTl3 < 60 GeV", "|mSFOS-mZ| < 15 GeV", "nbjets >= 1", "MET > 350 GeV", "pTll > 150 GeV"
        DEFINE_SIGNAL_REGION_NOCUTS("SR2BZ_3L"); //, "pTll > 150 GeV");

//      SR1AH_1L = "1l Preselection", "nbjets >= 3", "nh >= 1", "mT > 150 GeV", "njets >= 4", "METSig > 12"
        DEFINE_SIGNAL_REGION_NOCUTS("SR1AH_1L"); //, "METSig > 12");

//      SR1BH_1L", "1l Preselection", "nbjets >= 4", "nh >= 1", "mT > 150 GeV", "njets >= 6", "METSig > 7"
        DEFINE_SIGNAL_REGION_NOCUTS("SR1BH_1L"); //, "METSig > 7");
//
      }

      void run(const HEPUtils::Event* event)
      {

        // Baseline objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        vector<const HEPUtils::Particle*> baselineMuons;
        vector<const HEPUtils::Jet*> baselineJets;

        // Missing momentum and energy
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        // Baseline electrons have pT > 4.5 GeV, satisfy the "looseAndBLayer" ID criteria, and have |eta|<2.47.
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 4.5 && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        // LooseAndBLayer electron ID selection
        applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Loose"));

        // Baseline muons have satisfy "medium" criteria and have pT > 4 GeV and |eta| < 2.4
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 4. && muon->abseta() < 2.4) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        applyEfficiency(baselineMuons, ATLAS::eff2DMu.at("R2"));

        // Only jet candidates with pT > 20 GeV and |η| < 2.8 are considered in the analysis
        float JVTeff = 0.90;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT()>20. && jet->abseta()<2.8)
          {
            if ((jet->pT()<120. && jet->abseta()<2.4 && random_bool(JVTeff)) || jet->pT()>120. || jet->abseta()>2.4) baselineJets.push_back(jet);
          }
        }

        // Calculate the significance using ATLAS' Simple Analysis Framework
        vector<const HEPUtils::Particle*> photons;
        vector<const HEPUtils::Particle*> taus;
        double metsig = calcMETSignificance(baselineElectrons, photons, baselineMuons, baselineJets, taus, metVec);


        // Overlap removal
        // 1) Remove jets with pT<200 GeV and DeltaRy<0.2 of electron, if not btageff>0.85
        removeOverlap(baselineJets, baselineElectrons, 0.2, true, 200, 0.85);
        // 2) Remove jets within DeltaRy<0.2 of muon, if not btageff>0.85
        removeOverlap(baselineJets, baselineMuons, 0.2, true, DBL_MAX, 0.85);
        // 3) Remove electrons within DeltaRy<0.4 of jet
        removeOverlap(baselineElectrons, baselineJets, 0.4, true);
        // 4) Remove muons within DeltaRy<min(0.4,0.04+ptmu/10) of jet
        removeOverlap(baselineMuons, baselineJets, [](double pT) -> double {return min(0.4,0.04+pT*0.1);}, true);
        // 5) Remove electron if share tracks with a muon
        removeOverlap(baselineElectrons, baselineMuons, 0.01);

        // Signal objects
        vector<const HEPUtils::Jet*> signalJets;;
        vector<const HEPUtils::Jet*> signalBJets;
        vector<const HEPUtils::Particle*> signalElectrons = baselineElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        int n_jets_sixty = 0;

        // Signal Electrons: Medium ID, Iso bespoke
        applyEfficiency(signalElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Medium"));
        vector<const HEPUtils::Particle*> signalLeptons = signalElectrons;

        // Signal Muons: Medium ID, pT > 5 GeV
        for (const HEPUtils::Particle* muon : baselineMuons)
        {
          if (muon->pT() > 5.)
          {
            signalMuons.push_back(muon);
            signalLeptons.push_back(muon);
          }
        }

        // Signal jets have pT > 30 GeV
        for (const HEPUtils::Jet* jet : baselineJets)
        {
          if (jet->pT() > 30.)
          {
            signalJets.push_back(jet);
            if (jet->pT() > 60.)
            {
              n_jets_sixty +=1;
            }
          }
        }

        // Find b-jets
        double btag = 0.77; double cmisstag = 0.063; double misstag = 0.009;
        for (const HEPUtils::Jet* jet : signalJets)
        {
          // Tag
          if( jet->btag() && random_bool(btag) ) signalBJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) signalBJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) signalBJets.push_back(jet);
        }

        // Sort by pT
        sort(signalJets.begin(), signalJets.end(), compareJetPt);
        sort(signalBJets.begin(), signalBJets.end(), compareJetPt);
        sort(signalElectrons.begin(), signalElectrons.end(), comparePt);
        sort(signalMuons.begin(), signalMuons.end(), comparePt);
        sort(signalLeptons.begin(), signalLeptons.end(), comparePt);

        int n_leptons = signalLeptons.size();
        int n_baselineLeptons = baselineElectrons.size() + baselineMuons.size();
        int n_jets = signalJets.size();
        int n_bjets = signalBJets.size();
        // get the SFOS pairs
        vector<vector<const HEPUtils::Particle*>> SFOSpairs = getSFOSpairs(signalLeptons);

        /* Preselection */
        // True if passes this cut, false otherwise
        bool oneLep_presel = false; // 1 Lepton Pre-selection cut
        bool threeLep_presel = false; // 3 Lepton Pre-selection cut

        if (doCutflow){ FILL_SIGNAL_REGION("Total");}

        // Perform all pre-selection cuts
        BEGIN_PRESELECTION
        while(true)
        {

            // Passes 3 lepton selection
            if (n_leptons >= 3)
            {
              // Passes the njets selection
              if (!(n_jets >= 3))
              {
                break;
              }
              // Passes the met>50 GeV selection
              if (!(met > 50.))
              {
                break;
              }
              // Passes the pTl1>40 GeV selection
              if (!(signalLeptons.at(0)->pT() > 40))
              {
                break;
              }
              // Passes the pTl>20 GeV selection
              if (!(signalLeptons.at(1)->pT() > 20))
              {
                break;
              }
              // Set 3 lepton preselection as passed :)
              threeLep_presel = true;
            }
            // Passes 1 lepton selection
            else if (n_leptons == 1)
            {
              // Passes the baseline lepton veto
              if (!(n_baselineLeptons <= 1))
              {
                break;
              }
              // Passes the njets selection
              if (!(n_jets >= 4))
              {
                break;
              }
              // Passes the bjets selection
              if (!(n_bjets >= 3))
              {
                break;
              }
              // Set 1 lepton preselection as passed :)
              oneLep_presel = true;
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
            COMMIT_SIGNAL_REGION("Total", 3.,  5.7,  1.0);
            COMMIT_SIGNAL_REGION("SR1AZ_3L_presel_pTl3_mZ_nbjets_njets_MET", 3.,  5.7,  1.0);
            COMMIT_SIGNAL_REGION("SR1AZ_3L_presel_pTl3_mZ_nbjets_njets", 3.,  5.7,  1.0);
            COMMIT_SIGNAL_REGION("SR1AZ_3L_presel_pTl3_mZ_nbjets", 3.,  5.7,  1.0);
            COMMIT_SIGNAL_REGION("SR1AZ_3L_presel_pTl3_mZ", 3.,  5.7,  1.0);
            COMMIT_SIGNAL_REGION("SR1AZ_3L_presel_pTl3", 3.,  5.7,  1.0);
            COMMIT_SIGNAL_REGION("SR1AZ_3L_presel", 3.,  5.7,  1.0);
            COMMIT_SIGNAL_REGION("SR1BZ_3L_presel_pTl3_mZ_nbjets_njets_MET_pTll", 14., 12.1, 2.0);
            COMMIT_SIGNAL_REGION("SR1BZ_3L_presel_pTl3_mZ_nbjets_njets_MET", 14., 12.1, 2.0);
            COMMIT_SIGNAL_REGION("SR1BZ_3L_presel_pTl3_mZ_nbjets_njets", 14., 12.1, 2.0);
            COMMIT_SIGNAL_REGION("SR1BZ_3L_presel_pTl3_mZ_nbjets", 14., 12.1, 2.0);
            COMMIT_SIGNAL_REGION("SR1BZ_3L_presel_pTl3_mZ", 14., 12.1, 2.0);
            COMMIT_SIGNAL_REGION("SR1BZ_3L_presel_pTl3", 14., 12.1, 2.0);
            COMMIT_SIGNAL_REGION("SR1BZ_3L_presel", 14., 12.1, 2.0);
            COMMIT_SIGNAL_REGION("SR2AZ_3L_presel_pTl3_mZ_pTj1_MET", 3.,  5.6,  1.6);
            COMMIT_SIGNAL_REGION("SR2AZ_3L_presel_pTl3_mZ_pTj1", 3.,  5.6,  1.6);
            COMMIT_SIGNAL_REGION("SR2AZ_3L_presel_pTl3_mZ", 3.,  5.6,  1.6);
            COMMIT_SIGNAL_REGION("SR2AZ_3L_presel_pTl3", 3.,  5.6,  1.6);
            COMMIT_SIGNAL_REGION("SR2AZ_3L_presel", 3.,  5.6,  1.6);
            COMMIT_SIGNAL_REGION("SR2BZ_3L_presel_pTl3_mZ_nbjets_MET", 6.,  5.5,  0.9);
            COMMIT_SIGNAL_REGION("SR2BZ_3L_presel_pTl3_mZ_nbjets", 6.,  5.5,  0.9);
            COMMIT_SIGNAL_REGION("SR2BZ_3L_presel_pTl3_mZ", 6.,  5.5,  0.9);
            COMMIT_SIGNAL_REGION("SR2BZ_3L_presel_pTl3", 6.,  5.5,  0.9);
            COMMIT_SIGNAL_REGION("SR2BZ_3L_presel", 6.,  5.5,  0.9);
            COMMIT_SIGNAL_REGION("SR1AH_1L_presel_nbjets_nh_mT_njets", 11., 17.0, 3.0);
            COMMIT_SIGNAL_REGION("SR1AH_1L_presel_nbjets_nh_mT", 11., 17.0, 3.0);
            COMMIT_SIGNAL_REGION("SR1AH_1L_presel_nbjets_nh", 11., 17.0, 3.0);
            COMMIT_SIGNAL_REGION("SR1AH_1L_presel_nbjets", 11., 17.0, 3.0);
            COMMIT_SIGNAL_REGION("SR1AH_1L_presel", 11., 17.0, 3.0);
            COMMIT_SIGNAL_REGION("SR1BH_1L_presel_nbjets_nh_mT_njets", 24., 3.0,  5.0);
            COMMIT_SIGNAL_REGION("SR1BH_1L_presel_nbjets_nh_mT", 24., 3.0,  5.0);
            COMMIT_SIGNAL_REGION("SR1BH_1L_presel_nbjets_nh", 24., 3.0,  5.0);
            COMMIT_SIGNAL_REGION("SR1BH_1L_presel_nbjets", 24., 3.0,  5.0);
            COMMIT_SIGNAL_REGION("SR1BH_1L_presel", 24., 3.0,  5.0);
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
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_1OR3LEP_StopHZ_139invfb)

  }
}
