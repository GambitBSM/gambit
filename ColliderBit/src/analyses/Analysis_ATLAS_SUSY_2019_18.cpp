///
///  \author Holly Pacey
///  \date 2023 September
///
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2019-18/
// Luminosity: 139 fb^-1

// Old Analysis Name: ATLAS_13TeV_bTaus_StopStau_139invfb

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

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_SUSY_2019_18 : public Analysis
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

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_SUSY_2019_18()
      {
//        std::cout<<"define analysis"<<std::endl;
        set_analysis_name("ATLAS_SUSY_2019_18");
        set_luminosity(139);
//
//        // Counters for the number of accepted events for each signal region
        DEFINE_SIGNAL_REGION("SRdiTau_cuts_0", "di-tau preselection", "OS(tau1,tau2) == 1", "MET > 280 GeV")//, "mT2 > 70 GeV");
        DEFINE_SIGNAL_REGION("SRsingleTau_pT50-100_cuts_0", "single-tau Preselection", "MET > 280 GeV", "mTtau > 150 GeV", "summTb > 700 GeV", "sT > 600 GeV")//, "pTtau1: [50, 100] GeV");
        DEFINE_SIGNAL_REGION("SRsingleTau_pT100-200_cuts_0", "single-tau Preselection", "MET > 280 GeV", "mTtau > 150 GeV", "summTb > 700 GeV", "sT > 600 GeV")//, "pTtau1: [100, 200] GeV");
        DEFINE_SIGNAL_REGION("SRsingleTau_pT200_cuts_0", "single-tau Preselection", "MET > 280 GeV", "mTtau > 150 GeV", "summTb > 700 GeV", "sT > 600 GeV")//, "pTtau1 > 200 GeV");
//
      }
//
      void run(const HEPUtils::Event* event)
      {
//        std::cout<<"start of run"<<std::endl;

        // Baseline objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        vector<const HEPUtils::Particle*> baselineMuons;
        vector<const HEPUtils::Particle*> baselineLeptons;
        vector<const HEPUtils::Particle*> baselineTaus;
        vector<const HEPUtils::Jet*> baselineJets;

        // Missing momentum and energy
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        // Baseline electrons have pT > 10 GeV, satisfy the "looseAndBLayer" ID criteria, and have |eta|<2.47.
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 10. && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        // LooseAndBLayer electron ID selection
        applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Loose"));

        // Baseline muons have satisfy "medium" criteria and have pT > 10 GeV and |eta| < 2.7
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 10. && muon->abseta() < 2.7) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        // TODO Missing: "Medium" muon ID criteria
        applyEfficiency(baselineMuons, ATLAS::eff2DMu.at("R2"));

        // TODO Missing: impact parameter cuts

        // Only jet candidates with pT > 20 GeV and |η| < 2.8 are considered in the analysis
        // TODO Missing:  cut based on detector noise and non-collision backgrounds
        float JVTeff = 0.95;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT()>20. && jet->abseta()<2.8)
          {
            if ((jet->pT()<60. && jet->abseta()<2.4 && random_bool(JVTeff)) || jet->pT()>60. || jet->abseta()>2.4) baselineJets.push_back(jet);
          }
        }

        // Baseline taus have pT > 10 GeV, satisfy the "medium" RNN ID criteria, and have |eta|<2.5, and not 1.37<|eta|<1.52
        // need charge to be +-1 too.
        for (const HEPUtils::Particle* tau : event->taus())
        {
          if (tau->pT() > 10 && tau->abspid()==15 && tau->abseta() < 2.5 && (tau->abseta()>1.52 || tau->abseta()<1.37))
          {
            // Veto electrons that fake 1-prong hadronic taus
            // If DeltaR(tau,e) and e pt>5 GeV keep 95% of 1prong Loose ID taus
            // 0.05*0.85 = 0.0425
            bool vetoTau = false;
            for (const HEPUtils::Particle* electron : baselineElectrons)
            {
                if (tau->mom().deltaR2_eta(electron->mom())<0.4 && electron->pT()>5.)
                {
                    if (random_bool(0.0425)) vetoTau = true;
                }
            }
            if (!vetoTau) baselineTaus.push_back(tau);
          }
        }

        // Apply tau efficiency RNN Medium ID https://cds.cern.ch/record/2688062/
        applyEfficiency(baselineTaus, ATLAS::effTau.at("R2_RNN_Medium"));


        // Overlap removal
        // 1) Remove taus within DeltaRy 0.2 of an electron
        removeOverlap(baselineTaus, baselineElectrons, 0.2, true);
        // 2) Remove taus within DeltaRy 0.2 of an muon
        removeOverlap(baselineTaus, baselineMuons, 0.2, true);
        // 3) Remove electron if share tracks with a muon
        removeOverlap(baselineElectrons, baselineMuons, 0.01);
        // 4) Remove jets if within DeltaRy 0.2 of an electron
        removeOverlap(baselineJets, baselineElectrons, 0.2, true);
        // 5) Remove electrons if within DeltaRy 0.4 of a jet
        removeOverlap(baselineElectrons, baselineJets, 0.4, true);
        // 6) Remove jet if share tracks with a muon
        removeOverlap(baselineJets, baselineMuons, 0.01);
        // 7) Remove jets if within DeltaRy 0.2 of an muon
        removeOverlap(baselineJets, baselineMuons, 0.2, true);
        // 8) Remove electrons if within DeltaRy 0.4 of a jet
        removeOverlap(baselineMuons, baselineJets, 0.4, true);

        // Signal objects
        vector<const HEPUtils::Jet*> signalJets = baselineJets;
        vector<const HEPUtils::Jet*> signalBJets;
        vector<const HEPUtils::Particle*> signalTaus = baselineTaus;

        // Find b-jets
        double btag = 0.77; double cmisstag = 0.067; double misstag = 0.009;
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
        sort(signalTaus.begin(), signalTaus.end(), comparePt);

        int n_electrons = baselineElectrons.size();
        int n_muons = baselineMuons.size();
        int n_taus = signalTaus.size();
        int n_jets = signalJets.size();
        int n_bjets = signalBJets.size();

        /* Preselection */
        // True if passes this cut, false otherwise
        bool bTaus_presel = false; // Total Pre-selection cut
        bool bTaus_singleTau_presel = false; // single-tau Pre-selection cut
        bool bTaus_diTau_presel = false; // di-tau Pre-selection cut

        // Perform all pre-selection cuts
        BEGIN_PRESELECTION
        while(true)
        {

          // Passes the MET Trigger plateau cut
          if (!(met > 250.))
          {
            break;
          }
          // Passes the light lepton vetoes
          if (!(n_electrons == 0) || !(n_muons == 0))
          {
            break;
          }
          // Passes the jet selection
          if (!(n_jets >= 2))
          {
            break;
          }
          // Set common preselection as passed :)
          bTaus_presel = true;

          // Passes the single-tau preselection
          if (n_taus == 1 && n_bjets >= 2)
          {
            bTaus_singleTau_presel = true;
          }
          // Passes the di-tau preselection
          else if (n_taus >= 2 && n_bjets >= 1){
            bTaus_diTau_presel = true;
          }
          // Applied all cuts
          break;

        }

        // If event doesn't pass Pre-selection, exit early
        if (!bTaus_presel) return;
      END_PRESELECTION

        /* Signal Regions */

        // Initialise some useful variables
        double mT2 = -1.;
        double sT = -1.;
        double mTtau = -1.;
        double summTb = -1.;
        double pTtau1 = -1.;

        // Calculate them
        if (bTaus_diTau_presel)
        {
          mT2 = get_mT2(signalTaus.at(0), signalTaus.at(1), metVec, 0.);
        }
        else if (bTaus_singleTau_presel)
        {
          sT = signalTaus.at(0)->pT() + signalJets.at(0)->pT() + signalJets.at(1)->pT();
          mTtau = get_mT(signalTaus.at(0), metVec);
          summTb = get_mT(signalBJets.at(0)->mom(), metVec) + get_mT(signalBJets.at(1)->mom(), metVec);
          pTtau1 = signalTaus.at(0)->pT();
        }

        // SR di-tau
        while (true)
        {

          if (bTaus_diTau_presel)
          {
//            std::cout<<"passed presel"<<std::endl;
            LOG_CUT("SRdiTau_cuts_0");
          }
          else {break;}

          if (signalTaus.at(0)->pid()*signalTaus.at(1)->pid()<0)
          {
//            std::cout<<"OS pair"<<std::endl;
            LOG_CUT("SRdiTau_cuts_0");
          }
          else {break;}

          if (met > 280.)
          {
//            std::cout<<"met>280"<<std::endl;
            LOG_CUT("SRdiTau_cuts_0");
          }
          else {break;}

          if (mT2 > 70.)
          {
//            std::cout<<"mt2>70"<<std::endl;
            FILL_SIGNAL_REGION("SRdiTau_cuts_0");
          }

          // Applied all cuts
          break;
        }

        // SR signal-tau
        while (true)
        {

          if (bTaus_singleTau_presel)
          {
//            std::cout<<"presel passed"<<std::endl;
            LOG_CUT("SRsingleTau_pT50-100_cuts_0", "SRsingleTau_pT100-200_cuts_0", "SRsingleTau_pT200_cuts_0");
          }
          else {break;}

          if (met > 280.)
          {
//            std::cout<<"met>280"<<std::endl;
            LOG_CUT("SRsingleTau_pT50-100_cuts_0", "SRsingleTau_pT100-200_cuts_0", "SRsingleTau_pT200_cuts_0");
          }
          else {break;}

          if (mTtau > 150.)
          {
//            std::cout<<"mTtau>150"<<std::endl;
            LOG_CUT("SRsingleTau_pT50-100_cuts_0", "SRsingleTau_pT100-200_cuts_0", "SRsingleTau_pT200_cuts_0");
          }
          else {break;}

          if (summTb > 700.)
          {
//            std::cout<<"summTb>700"<<std::endl;
            LOG_CUT("SRsingleTau_pT50-100_cuts_0", "SRsingleTau_pT100-200_cuts_0", "SRsingleTau_pT200_cuts_0");
          }
          else {break;}

          if (sT > 600.)
          {
//            std::cout<<"sT>600"<<std::endl;
            LOG_CUT("SRsingleTau_pT50-100_cuts_0", "SRsingleTau_pT100-200_cuts_0", "SRsingleTau_pT200_cuts_0");
          }
          else {break;}

          if (pTtau1 > 50. && pTtau1 <= 100.)
          {
//            std::cout<<"pTtau1=[0,100]"<<std::endl;
            FILL_SIGNAL_REGION("SRsingleTau_pT50-100_cuts_0");
          }
          else if (pTtau1 > 100. && pTtau1 <= 200.)
          {
//            std::cout<<"pTtau1=[100,200]"<<std::endl;
            FILL_SIGNAL_REGION("SRsingleTau_pT100-200_cuts_0");
          }
          else if (pTtau1 > 200.)
          {
//            std::cout<<"pTtau1>200"<<std::endl;
            FILL_SIGNAL_REGION("SRsingleTau_pT200_cuts_0");
          }

          // Applied all cuts
          break;
        }
//        std::cout<<"end of run"<<std::endl;

      } // End run function

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {
//        std::cout<<"collect results"<<std::endl;
        // Obs. Exp. Err.
        COMMIT_SIGNAL_REGION("SRsingleTau_pT50-100_cuts_0", 8., 10.1, 1.8);
        COMMIT_SIGNAL_REGION("SRsingleTau_pT100-200_cuts_0", 6., 5.1, 1.1);
        COMMIT_SIGNAL_REGION("SRsingleTau_pT200_cuts_0", 2., 2.05, 0.64);
        COMMIT_SIGNAL_REGION("SRdiTau_cuts_0", 2., 4.1, 1.0);

        COMMIT_CUTFLOWS;
      }

    protected:
      void analysis_specific_reset()
      {
//        std::cout<<"analysis_specific_reset"<<std::endl;
        for (auto& pair : _counters)
        {
          pair.second.reset();
        }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2019_18)

  }
}
