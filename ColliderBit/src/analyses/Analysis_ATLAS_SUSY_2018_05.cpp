///
///  \author Martin White
///  \date 2023 August
///
///  \author Chris Chang
///  \date 2023 Sep
///
///  *********************************************

// Based on EW regions of https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-05/
// Luminosity: 139 fb^-1
// Note that this uses the ATLAS object-based met significance

// Old Analysis Name: ATLAS_13TeV_2LEPJETS_EW_139invfb

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

    class Analysis_ATLAS_SUSY_2018_05 : public Analysis
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

      Analysis_ATLAS_SUSY_2018_05()
      {

        set_analysis_name("ATLAS_SUSY_2018_05");
        set_luminosity(139);
        set_bkgjson("ColliderBit/data/analyses_json_files/ATLAS_SUSY_2018_05_full_bkgonly.json");

        // Counters for the number of accepted events for each signal region
        // 1/2 is used to represent the first or second bin of the met significance
        DEFINE_SIGNAL_REGION("SRHigh8_1_cuts_0", "n bjets <= 1", "mll: [71,111] GeV", "MET sig > 18",
                                               "mt2 > 80 GeV", "njets >=2", "mjj: [60,110] GeV", "delta Rjj < 0.8")
        DEFINE_SIGNAL_REGION("SRHigh8_2_cuts_0", "n bjets <= 1", "mll: [71,111] GeV", "MET sig > 18", "mt2 > 80 GeV",
                                               "njets >=2", "mjj: [60,110] GeV", "delta Rjj < 0.8")
        DEFINE_SIGNAL_REGION("SRHigh16_1_cuts_0", "n bjets <= 1", "mll: [71,111] GeV", "MET sig > 18", "mt2 > 80 GeV",
                                                "njets >=2", "mjj: [60,110] GeV", "delta Rjj: [0.8,1.6]")
        DEFINE_SIGNAL_REGION("SRHigh16_2_cuts_0", "n bjets <= 1", "mll: [71,111] GeV", "MET sig > 18", "mt2 > 80 GeV",
                                                "njets >=2", "mjj: [60,110] GeV", "delta Rjj: [0.8,1.6]")
        DEFINE_SIGNAL_REGION("SRHigh4_cuts_0", "n bjets <= 1", "mll: [71,111] GeV", "MET sig > 12", "mt2 > 80 GeV", "njets ==1")
        DEFINE_SIGNAL_REGION("SRllbb_cuts_0", "mll: [71,111] GeV", "MET sig > 18", "mt2 > 80 GeV", "nbets >=2", "njets >=2")

        DEFINE_SIGNAL_REGION("SRInt_1_cuts_0", "n bjets == 0", "mll: [81,101] GeV", "MET sig: [12,18]", "mt2 > 80 GeV",
                                             "jet pt1 > 60 GeV", "njets >=2", "mjj: [60,110] GeV")
        DEFINE_SIGNAL_REGION("SRInt_2_cuts_0", "n bjets == 0", "mll: [81,101] GeV", "MET sig: [12,18]", "mt2 > 80 GeV",
                                             "jet pt1 > 60 GeV", "njets >=2", "mjj: [60,110] GeV")

        DEFINE_SIGNAL_REGION("SRLow_1_cuts_0", "n bjets == 0", "mll: [81,101] GeV", "MET sig: [6,12]", "mt2 > 80 GeV",
                                             "njets ==2", "mjj: [60,110] GeV", "Rll < 1")
        DEFINE_SIGNAL_REGION("SRLow_2_cuts_0", "n bjets == 0", "mll: [81,101] GeV", "MET sig: [6,12]", "mt2 > 80 GeV",
                                             "njets ==2", "mjj: [60,110] GeV", "Rll < 1")
        DEFINE_SIGNAL_REGION("SRLow2_cuts_0", "n bjets == 0", "mll: [81,101] GeV", "MET sig: [6,9]", "mt2 < 80 GeV",
                                            "njets ==2", "mjj: [60,110] GeV", "Rll < 1.6")

        DEFINE_SIGNAL_REGION("SROffShell_1_cuts_0", "n bjets == 0", "mll: [12,71] GeV", "MET sig > 9", "mt2 > 100 GeV",
                                                 "njets >=2", "jet pt1 > 100", "Rll < 1.6", "dphiJ1met > 2")
        DEFINE_SIGNAL_REGION("SROffShell_2_cuts_0", "n bjets == 0", "mll: [12,71] GeV", "MET sig > 9", "mt2 > 100 GeV",
                                                 "njets >=2", "jet pt1 > 100", "Rll < 1.6", "dphiJ1met > 2")

      }

      void run(const HEPUtils::Event* event)
      {

        // Baseline objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        vector<const HEPUtils::Particle*> baselineMuons;
        vector<const HEPUtils::Particle*> baselineLeptons;
        vector<const HEPUtils::Particle*> baselinePhotons;
        vector<const HEPUtils::Jet*> baselineJets;
        vector<const HEPUtils::Jet*> baselineBJets;
        vector<const HEPUtils::Jet*> baselineNonBJets;

        // Missing momentum and energy
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        // Baseline electrons have pT > 4.5 GeV, satisfy the "loose" criteria, and have |eta|<2.47.
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 4.5 && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        // Loose electron ID selection
        applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Loose"));

        // Baseline muons have satisfy "medium" criteria and have pT > 3 GeV and |eta| < 2.7
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 3. && muon->abseta() < 2.7) baselineMuons.push_back(muon);
        }


        // Apply muon efficiency
        // Missing: "Medium" muon ID criteria
        applyEfficiency(baselineMuons, ATLAS::eff2DMu.at("R2"));

        // Missing: transverse and longitudinal impact parameter cuts


        // Only jet candidates with pT > 20 GeV and |η| < 2.8 are considered in the analysis
        // Jets with pT < 120 GeV and |η| < 2.8 have an efficiency of 90%
        // Missing:  cut based on detector noise and non-collision backgrounds

        // Baseline photons selection (used later in met significance)
        // pT > 25 GeV, and abseta < 2.37, and doesn't lie in 1.37 < abseta < 1.52
        // Missing: "tight" photon ID criteria
        for (const HEPUtils::Particle* photon : event->photons())
        {
          if ((photon->pT() > 25.) && (photon->abseta() < 2.37))
          {
            if (photon->abseta() < 1.37 || photon->abseta() > 1.52) baselinePhotons.push_back(photon);
          }
        }

        double jet_eff = 0.9;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT()>20. && jet->abseta()<2.8)
          {
            if( (jet->pT() >= 120. || jet->abseta() >= 2.5) || random_bool(jet_eff) ) baselineJets.push_back(jet);
          }
        }


        // Overlap removal
        // 1) Remove muons with 0.01 of an electron, mimics shared tracks
        removeOverlap(baselineMuons, baselineElectrons, 0.01);
        // 2) Remove jets within DeltaR = 0.2 of electron
        removeOverlap(baselineJets, baselineElectrons, 0.2);
        // 3) If any lepton has Delta R < min(0.4, 0.04 + 10/pT(l)) with a jet, remove the lepton.
        auto lambda = [](double lepton_pT) { return std::min(0.4, 0.04 + 10./(lepton_pT) ); };
        removeOverlap(baselineElectrons, baselineJets, lambda);
        // 4) Remove jets within 0.2 of muons (incorporates shared track approximation)
        removeOverlap(baselineJets, baselineMuons, 0.2);
        // 5) Remove muons subject to pT-dependent deltaR requirement
        removeOverlap(baselineMuons, baselineJets, lambda);

        // Signal objects
        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBJets;
        vector<const HEPUtils::Jet*> signalNonBJets;
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        vector<const HEPUtils::Particle*> signalLeptons;

        // Signal electrons must satisfy the “medium” identification requirement as defined in arXiv: 1902.04655 [hep-ex]
        applyEfficiency(signalElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Medium"));
        // Signal electrons must have pT > 25 GeV
        for (const HEPUtils::Particle* signalElectron : baselineElectrons)
        {
          if (signalElectron->pT() > 25.) signalElectrons.push_back(signalElectron);
        }

        // Signal muons must have pT > 25 GeV.
        for (const HEPUtils::Particle* signalMuon : baselineMuons)
        {
          if (signalMuon->pT() > 25. && signalMuon->abseta() < 2.6) signalMuons.push_back(signalMuon);
        }

        // Signal jets must have pT > 30 GeV
        for (const HEPUtils::Jet* signalJet : baselineJets)
        {
          if (signalJet->pT() > 30.) signalJets.push_back(signalJet);
        }

        // Find b-jets
        double btag = 0.77; double cmisstag = 1/16.; double misstag = 1./113.;
        for (const HEPUtils::Jet* jet : signalJets)
        {
          // Tag
          if( jet->btag() && random_bool(btag) ) signalBJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) signalBJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) signalBJets.push_back(jet);
          // Non b-jet
          else signalNonBJets.push_back(jet);
        }

        // Fill signal leptons
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Fill baseline leptons
        baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end());

        // Sort by pT
        sort(signalJets.begin(), signalJets.end(), compareJetPt);
        sort(signalBJets.begin(), signalBJets.end(), compareJetPt);
        sort(signalLeptons.begin(), signalLeptons.end(), comparePt);

        // Start of analysis code based on ATLAS public code snippet
        size_t n_baseline_leptons = baselineLeptons.size();
        size_t n_leptons = signalLeptons.size();
        size_t n_jets = signalJets.size();
        size_t nbjets = signalBJets.size();

        /* Preselection */
        // True if passes this cut, false otherwise
        bool EWK_2Ljets_presel = false; // Total Pre-selection cut

        // Initialise some useful variables
        double mll = 0;
        double mt2 = 0;
        double metsig = 0;
        double Rjj = 0;
        double mjj = 0.;
        double jetm1 = 0;
        double mbb = 0.;
        double jetpt1 = 0;
        double Rll = 0;
        double dphiPllMet = 0;
        double dphiJ1met = 0;


        // Perform all pre-selection cuts
        BEGIN_PRESELECTION
        while(true)
        {

          // At least two baseline leptons
          if (!(n_baseline_leptons >= 2)) {break;}

          // at least one jet (> 30 GeV)
          if (!(n_jets >= 1)) {break;}

          // exactly two leptons (> 25 GeV)
          if (!(n_leptons == 2 && n_baseline_leptons == 2)) {break;}

          // lepton pair mass in (12, 111)
          HEPUtils::P4 dilepton = signalLeptons.at(0)->mom() + signalLeptons.at(1)->mom();
          mll = dilepton.m();
          if (!(12 < mll)) {break;}

          // both leptons of the Same Flavour (SF)
          // since we have exactly two leptons,
          // 0 electron <=> 2 muon => SF
          // 1 electron <=> 1 muon => DF
          // 2 electron <=> 0 muon => SF
          if (signalElectrons.size() == 1) {break;}

          // both leptons of Opposite Sign (OS) charge
          if (signalLeptons.at(0)->pid() == signalLeptons.at(1)->pid()) {break;}

          // Approximate the significance using HT
          // Keeping in for use in debugging Met sig code
          // double HT = 0.0;
          // for (const HEPUtils::Jet* j : baselineJets) HT += j->pT();
          // for (const HEPUtils::Particle* p : baselinePhotons) HT += p->pT();
          // for (const HEPUtils::Particle* e : baselineElectrons) HT += e->pT();
          // for (const HEPUtils::Particle* mu : baselineMuons) HT += mu->pT();
          // metsig = met/sqrt(HT); // The approximate method

          // Calculate the significance using ATLAS' Simple Analysis Framework
          metsig = calcMETSignificance(baselineElectrons, baselinePhotons, baselineMuons, baselineJets, event->taus(), metVec);

          // missing energy: met > 100 GeV, met significance > 6
          if (!(metsig > 6)) {break;}
          if (!(met > 100)) {break;}

          /* More event variables */
          dphiPllMet = fabs(dilepton.deltaPhi(metVec));
          dphiJ1met = fabs(signalJets.at(0)->mom().deltaPhi(metVec));

          Rjj = 0.;
          if (n_jets >= 2)
          {
            HEPUtils::P4 dijets = signalJets.at(0)->mom() + signalJets.at(1)->mom();
            mjj = dijets.m();
            Rjj = fabs(signalJets.at(0)->mom().deltaR_eta(signalJets.at(1)->mom()));
          }

          if (nbjets >= 2)
          {
            HEPUtils::P4 dibjets = signalBJets.at(0)->mom() + signalBJets.at(1)->mom();
            mbb = dibjets.m();
          }

          jetpt1 = signalJets.at(0)->mom().pT();
          jetm1 = signalJets.at(0)->mom().m();

          Rll = fabs(signalLeptons.at(0)->mom().deltaR_eta(signalLeptons.at(1)->mom()));

          double pLep1[3] = {signalLeptons.at(0)->mass(), signalLeptons.at(0)->mom().px(), signalLeptons.at(0)->mom().py()};
          double pLep2[3] = {signalLeptons.at(1)->mass(), signalLeptons.at(1)->mom().px(), signalLeptons.at(1)->mom().py()};
          double pMiss[3] = {0., event->missingmom().px(), event->missingmom().py() };

          mt2_bisect::mt2 mt2_calc;
          double mn = 0;
          mt2_calc.set_momenta(pLep1, pLep2, pMiss);
          mt2_calc.set_mn(mn);
          mt2 = mt2_calc.get_mt2();

          // If it has reached this point, it has passed pre-selection
          EWK_2Ljets_presel = true;

          // Applied all cuts
          break;
        }

        // If event doesn't pass Pre-selection, exit early
        if (EWK_2Ljets_presel == false) return;
        END_PRESELECTION

        /* Signal Regions */
        // Avoiding repetition with some of the more commonly used cuts
        bool mll_71_111 = false; // mll between 71-111 GeV
        bool mll_81_101 = false; // mll between 81-101 GeV
        bool mt2_gt_80 = false; // mt2 greater than 80 GeV
        bool mt2_lt_80 = false; // mt2 less than 80 GeV
        bool mjj_60_110 = false; // mjj between 60-110 GeV
        bool Rjj_lt_8 = false; // delta Rjj less than 0.8
        bool Rjj_8_16 = false; // delta Rjj between 0.8 and 1.6

        if (71 < mll && mll < 111) {mll_71_111 = true;}
        if (81 < mll && mll < 101) {mll_81_101 = true;}
        if (mt2 > 80) {mt2_gt_80 = true;}
        if (mt2 < 80) {mt2_lt_80 = true;}
        if (Rjj < 0.8) {Rjj_lt_8 = true;}
        if (0.8 < Rjj && Rjj < 1.6) {Rjj_8_16 = true;}
        if (60 < mjj && mjj < 110) {mjj_60_110 = true;}

        // SR_High_8/16_a/b
        while (true)
        {
          if (nbjets <= 1) {LOG_CUT("SRHigh8_1_cuts_0", "SRHigh8_2_cuts_0", "SRHigh16_1_cuts_0", "SRHigh16_2_cuts_0")}
          else {break;}

          if (mll_71_111) {LOG_CUT("SRHigh8_1_cuts_0", "SRHigh8_2_cuts_0", "SRHigh16_1_cuts_0", "SRHigh16_2_cuts_0")}
          else {break;}

          if (metsig > 18) {LOG_CUT("SRHigh8_1_cuts_0", "SRHigh8_2_cuts_0", "SRHigh16_1_cuts_0", "SRHigh16_2_cuts_0")}
          else {break;}

          if (mt2_gt_80) {LOG_CUT("SRHigh8_1_cuts_0", "SRHigh8_2_cuts_0", "SRHigh16_1_cuts_0", "SRHigh16_2_cuts_0")}
          else {break;}

          if (n_jets >= 2) {LOG_CUT("SRHigh8_1_cuts_0", "SRHigh8_2_cuts_0", "SRHigh16_1_cuts_0", "SRHigh16_2_cuts_0")}
          else {break;}

          if (mjj_60_110) {LOG_CUT("SRHigh8_1_cuts_0", "SRHigh8_2_cuts_0", "SRHigh16_1_cuts_0", "SRHigh16_2_cuts_0")}
          else {break;}

          if (Rjj_lt_8)
          {
            LOG_CUT("SRHigh8_1_cuts_0", "SRHigh8_2_cuts_0")

            if (metsig < 21) {FILL_SIGNAL_REGION("SRHigh8_1_cuts_0");}
            else if (metsig > 21) {FILL_SIGNAL_REGION("SRHigh8_2_cuts_0");}
          }
          else if (Rjj_8_16)
          {
            LOG_CUT("SRHigh16_1_cuts_0", "SRHigh16_2_cuts_0")

            if (metsig < 21) {FILL_SIGNAL_REGION("SRHigh16_1_cuts_0");}
            else if (metsig > 21) {FILL_SIGNAL_REGION("SRHigh16_2_cuts_0");}
          }

          // Applied all cuts
          break;
        }

        // SRHigh4_cuts
        while (true)
        {
          if (nbjets <= 1) {LOG_CUT("SRHigh4_cuts_0")}
          else {break;}

          if (mll_71_111) {LOG_CUT("SRHigh4_cuts_0")}
          else {break;}

          if (metsig > 12) {LOG_CUT("SRHigh4_cuts_0")}
          else {break;}

          if (mt2_gt_80) {LOG_CUT("SRHigh4_cuts_0")}
          else {break;}

          if (n_jets == 1) {LOG_CUT("SRHigh4_cuts_0")}
          else {break;}

          if (60 < jetm1 && jetm1 < 110) {FILL_SIGNAL_REGION("SRHigh4_cuts_0");}

          // Applied all cuts
          break;
        }

        // SRllbb_cuts
        while (true)
        {
          if (mll_71_111) {LOG_CUT("SRllbb_cuts_0")}
          else {break;}

          if (metsig > 18) {LOG_CUT("SRllbb_cuts_0")}
          else {break;}

          if (mt2_gt_80) {LOG_CUT("SRllbb_cuts_0")}
          else {break;}

          if (nbjets >= 2) {LOG_CUT("SRllbb_cuts_0")}
          else {break;}

          if (n_jets >= 2) {LOG_CUT("SRllbb_cuts_0")}
          else {break;}

          if (60 < mbb && mbb < 150) {FILL_SIGNAL_REGION("SRllbb_cuts_0");}

          // Applied all cuts
          break;
        }

        // SR Int_a/b
        while (true)
        {
          if (nbjets == 0) {LOG_CUT("SRInt_1_cuts_0", "SRInt_2_cuts_0")}
          else {break;}

          if (mll_81_101) {LOG_CUT("SRInt_1_cuts_0", "SRInt_2_cuts_0")}
          else {break;}

          if (12 < metsig && metsig < 18) {LOG_CUT("SRInt_1_cuts_0", "SRInt_2_cuts_0")}
          else {break;}

          if (mt2_gt_80) {LOG_CUT("SRInt_1_cuts_0", "SRInt_2_cuts_0")}
          else {break;}

          if (jetpt1 > 60) {LOG_CUT("SRInt_1_cuts_0", "SRInt_2_cuts_0")}
          else {break;}

          if (n_jets >= 2) {LOG_CUT("SRInt_1_cuts_0", "SRInt_2_cuts_0")}
          else {break;}

          if (mjj_60_110) {LOG_CUT("SRInt_1_cuts_0", "SRInt_2_cuts_0")}
          else {break;}

          if (metsig < 15) {FILL_SIGNAL_REGION("SRInt_1_cuts_0");}
          else if (metsig > 15) {FILL_SIGNAL_REGION("SRInt_2_cuts_0");}

          // Applied all cuts
          break;
        }

        //SRLow_1/2_cuts
        while (true)
        {
          if (nbjets == 0) {LOG_CUT("SRLow_1_cuts_0", "SRLow_2_cuts_0")}
          else {break;}

          if (mll_81_101) {LOG_CUT("SRLow_1_cuts_0", "SRLow_2_cuts_0")}
          else {break;}

          if (6 < metsig && metsig < 12) {LOG_CUT("SRLow_1_cuts_0", "SRLow_2_cuts_0")}
          else {break;}

          if (mt2_gt_80) {LOG_CUT("SRLow_1_cuts_0", "SRLow_2_cuts_0")}
          else {break;}

          if (n_jets == 2) {LOG_CUT("SRLow_1_cuts_0", "SRLow_2_cuts_0")}
          else {break;}

          if (mjj_60_110) {LOG_CUT("SRLow_1_cuts_0", "SRLow_2_cuts_0")}
          else {break;}

          if (Rll < 1) {LOG_CUT("SRLow_1_cuts_0", "SRLow_2_cuts_0")}
          else {break;}

          if (metsig < 9) {FILL_SIGNAL_REGION("SRLow_1_cuts_0");}
          else if (metsig > 9) {FILL_SIGNAL_REGION("SRLow_2_cuts_0");}

          // Applied all cuts
          break;
        }

        //SRLow2_cuts
        while (true)
        {
          if (nbjets == 0) {LOG_CUT("SRLow2_cuts_0")}
          else {break;}

          if (mll_81_101) {LOG_CUT("SRLow2_cuts_0")}
          else {break;}

          if (6 < metsig && metsig < 9) {LOG_CUT("SRLow2_cuts_0")}
          else {break;}

          if (mt2_lt_80) {LOG_CUT("SRLow2_cuts_0")}
          else {break;}

          if (n_jets == 2) {LOG_CUT("SRLow2_cuts_0")}
          else {break;}

          if (mjj_60_110) {LOG_CUT("SRLow2_cuts_0")}
          else {break;}

          if (Rll < 1.6) {LOG_CUT("SRLow2_cuts_0")}
          else {break;}

          if (dphiPllMet < 0.6) {FILL_SIGNAL_REGION("SRLow2_cuts_0");}

          // Applied all cuts
          break;
        }

        // SROffShell_1/2_cuts
        while (true)
        {
          if (nbjets == 0) {LOG_CUT("SROffShell_1_cuts_0", "SROffShell_2_cuts_0")}
          else {break;}

          if (12 < mll && mll < 71) {LOG_CUT("SROffShell_1_cuts_0", "SROffShell_2_cuts_0")}
          else {break;}

          if (metsig > 9) {LOG_CUT("SROffShell_1_cuts_0", "SROffShell_2_cuts_0")}
          else {break;}

          if (mt2 > 100) {LOG_CUT("SROffShell_1_cuts_0", "SROffShell_2_cuts_0")}
          else {break;}

          if (n_jets >= 2) {LOG_CUT("SROffShell_1_cuts_0", "SROffShell_2_cuts_0")}
          else {break;}

          if (jetpt1 > 100) {LOG_CUT("SROffShell_1_cuts_0", "SROffShell_2_cuts_0")}
          else {break;}

          if (Rll < 1.6) {LOG_CUT("SROffShell_1_cuts_0", "SROffShell_2_cuts_0")}
          else {break;}

          if (dphiJ1met > 2) {LOG_CUT("SROffShell_1_cuts_0", "SROffShell_2_cuts_0")}
          else {break;}

          if (mll < 40) {FILL_SIGNAL_REGION("SROffShell_1_cuts_0");}
          else if (mll > 40) {FILL_SIGNAL_REGION("SROffShell_2_cuts_0");}

          // Applied all cuts
          break;
        }

      } // End run function


      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {
        COMMIT_SIGNAL_REGION("SRHigh8_1_cuts_0", 0., 2.00, 0.23)
        COMMIT_SIGNAL_REGION("SRHigh8_2_cuts_0", 0., 2.00, 0.33)
        COMMIT_SIGNAL_REGION("SRHigh16_1_cuts_0", 4., 3.9, 0.7)
        COMMIT_SIGNAL_REGION("SRHigh16_2_cuts_0", 3., 3.4, 0.9)
        COMMIT_SIGNAL_REGION("SRHigh4_cuts_0", 1., 0.85, 0.34)
        COMMIT_SIGNAL_REGION("SRllbb_cuts_0", 0., 0.58, 0.20)
        COMMIT_SIGNAL_REGION("SRInt_1_cuts_0", 24., 22.8, 3.5)
        COMMIT_SIGNAL_REGION("SRInt_2_cuts_0", 14., 10.1, 1.0)
        COMMIT_SIGNAL_REGION("SRLow_1_cuts_0", 10., 12.8, 3.4)
        COMMIT_SIGNAL_REGION("SRLow_2_cuts_0", 8., 10.5, 2.5)
        COMMIT_SIGNAL_REGION("SRLow2_cuts_0", 8., 9, 4)
        COMMIT_SIGNAL_REGION("SROffShell_1_cuts_0", 6., 9.2, 1.7)
        COMMIT_SIGNAL_REGION("SROffShell_2_cuts_0", 15., 12.5, 1.9)

        COMMIT_CUTFLOWS
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
    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2018_05)

  }
}
