///
///  \author Martin White
///  \date 2023 August
///
///  *********************************************

// Based on EW regions of https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-05/
// Luminosity: 139 fb^-1
// Note that this uses the ATLAS object-based met significance
// Will approximate with event-based measure, but this will lead to discrepancies
// TODO: Perhaps reformat to make neater, and be consistent with Tomas' cutflow system
// TODO: Implement the JSON HistFactory likelihood

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "METSignificance/METSignificance.hpp"

#define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_2LEPJETS_EW_139invfb : public Analysis
    {

    protected:

        //vector<Cutflow> _cutflow;
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

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_2LEPJETS_EW_139invfb()
      {

        // Counters for the number of accepted events for each signal region

        // a/b is used to represent the first or second bin of the met significance
        _counters["SR_High_8_a"] = EventCounter("SR_High_8_a");
        _counters["SR_High_8_b"] = EventCounter("SR_High_8_b");
        _counters["SR_High_16_a"] = EventCounter("SR_High_16_a");
        _counters["SR_High_16_b"] = EventCounter("SR_High_16_b");
        _counters["SR_High_4"] = EventCounter("SR_High_4");
        _counters["SR_llbb"] = EventCounter("SR_llbb");
        _counters["SR_Int_a"] = EventCounter("SR_Int_a");
        _counters["SR_Int_b"] = EventCounter("SR_Int_b");
        _counters["SR_Low_a"] = EventCounter("SR_Low_a");
        _counters["SR_Low_b"] = EventCounter("SR_Low_b");
        _counters["SR_Low_2"] = EventCounter("SR_Low_2");
        _counters["SR_OffShell_a"] = EventCounter("SR_OffShell_a");
        _counters["SR_OffShell_b"] = EventCounter("SR_OffShell_b");


        set_analysis_name("ATLAS_13TeV_2LEPJETS_EW_139invfb");
        set_luminosity(139);

        _cutflows.addCutflow("SR_High_8_a", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets <= 1", "mll: [71,111] GeV", "MET significance > 18", "mt2 > 80 GeV", "njets >=2", "mjj: [60,110] GeV", "delta Rjj < 0.8", "Met Significance < 21"});
        _cutflows.addCutflow("SR_High_8_b", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets <= 1", "mll: [71,111] GeV", "MET significance > 18", "mt2 > 80 GeV", "njets >=2", "mjj: [60,110] GeV", "delta Rjj < 0.8", "Met Significance > 21"});
        _cutflows.addCutflow("SR_High_16_a", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets <= 1", "mll: [71,111] GeV", "MET significance > 18", "mt2 > 80 GeV", "njets >=2", "mjj: [60,110] GeV", "delta Rjj: [0.8,1.6]", "Met Significance < 21"});
        _cutflows.addCutflow("SR_High_16_b", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets <= 1", "mll: [71,111] GeV", "MET significance > 18", "mt2 > 80 GeV", "njets >=2", "mjj: [60,110] GeV", "delta Rjj: [0.8,1.6]", "Met Significance > 21"});
        _cutflows.addCutflow("SR_High_4", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets <= 1", "mll: [71,111] GeV", "MET significance > 12", "mt2 > 80 GeV", "njets ==1", "mjj: [60,110] GeV"});
        _cutflows.addCutflow("SR_llbb", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "mll: [71,111] GeV", "MET significance > 18", "mt2 > 80 GeV", "nbets >=2", "njets >=2", "mbb: [60,150] GeV"});

        _cutflows.addCutflow("SR_Int_a", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets == 0", "mll: [81,101] GeV", "MET significance: [12,18]", "mt2 > 80 GeV", "jet pt1 > 60 GeV", "njets >=2", "mjj: [60,110] GeV", "Met Significance < 15"});
        _cutflows.addCutflow("SR_Int_b", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets == 0", "mll: [81,101] GeV", "MET significance: [12,18]", "mt2 > 80 GeV", "jet pt1 > 60 GeV", "njets >=2", "mjj: [60,110] GeV", "Met Significance > 15"});

        _cutflows.addCutflow("SR_Low_a", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets == 0", "mll: [81,101] GeV", "MET significance: [6,12]", "mt2 > 80 GeV", "njets ==2", "mjj: [60,110] GeV", "Rll < 1", "Met Significance < 9"});
        _cutflows.addCutflow("SR_Low_b", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets == 0", "mll: [81,101] GeV", "MET significance: [6,12]", "mt2 > 80 GeV", "njets ==2", "mjj: [60,110] GeV", "Rll < 1", "Met Significance > 9"});
        _cutflows.addCutflow("SR_Low_2", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets == 0", "mll: [81,101] GeV", "MET significance: [6,9]", "mt2 < 80 GeV", "njets ==2", "mjj: [60,110] GeV", "Rll < 1.6", "dphiPllMet < 0.6"});

        _cutflows.addCutflow("SR_OffShell_a", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets == 0", "mll: [12,71] GeV", "MET significance > 9", "mt2 > 100 GeV", "njets >=2", "jet pt1 > 100", "Rll < 1.6", "dphiJ1met > 2", "mll < 40"});
        _cutflows.addCutflow("SR_OffShell_b", {"Gen Filter and SUSY kernal", "n baseline leptons >=2", "njets >= 1", "2 baseline and signal leptons", "mll > 12 GeV", "Same Flavour leptons", "Opposite Charge Leptons", "MET significance > 6", "ETmiss > 100 GeV", "n bjets == 0", "mll: [12,71] GeV", "MET significance > 9", "mt2 > 100 GeV", "njets >=2", "jet pt1 > 100", "Rll < 1.6", "dphiJ1met > 2", "mll > 40"});

      }

      // Fill the next cutflow, do nothing if CHECK_CUTFLOW is not defined
      void cutflow_fillnext(str SR, double weight)
      {
        #ifdef CHECK_CUTFLOW
          _cutflows[SR].fillnext(weight);
        #endif
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

        // TODO: Some debugging objects for cutflows
        vector<const HEPUtils::Particle*> GeneratorFilter; // TODO: Debugging Cutflow
        vector<const HEPUtils::Particle*> SUSYKernal; // TODO: Debugging Cutflow
        vector<const HEPUtils::Particle*> SUSYKernal_2; // TODO: Debugging Cutflow
        bool highpT_photon = false; // TODO: Debugging Cutflow

        // Missing momentum and energy
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        // Initialize cutflow
        #ifdef CHECK_CUTFLOW
          const double w = event->weight();
          _cutflows.fillinit(w);
        #endif

        // Baseline electrons have pT > 4.5 GeV, satisfy the "loose" criteria, and have |eta|<2.47.
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 4.5 && electron->abseta() < 2.47) baselineElectrons.push_back(electron);

          if (electron->pT() > 7.0) GeneratorFilter.push_back(electron); // TODO: Debugging
          if (electron->pT() > 9.0 && electron->abseta() < 2.6) SUSYKernal.push_back(electron); // TODO: Debugging
          if (electron->pT() > 25.0 && electron->abseta() < 2.6) SUSYKernal_2.push_back(electron); // TODO: Debugging
        }

        // Apply electron efficiency
        // Loose electron ID selection
        apply1DEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Loose"));

        // Baseline muons have satisfy "medium" criteria and have pT > 3 GeV and |eta| < 2.7
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 3. && muon->abseta() < 2.7) baselineMuons.push_back(muon);

          if (muon->pT() > 7.) GeneratorFilter.push_back(muon); // TODO: Debugging
          if (muon->pT() > 9. && muon->abseta() < 2.6) SUSYKernal.push_back(muon); // TODO: Debugging
          if (muon->pT() > 25. && muon->abseta() < 2.6) SUSYKernal_2.push_back(muon); // TODO: Debugging
        }


        // Apply muon efficiency
        // Missing: "Medium" muon ID criteria
        ATLAS::applyMuonEffR2(baselineMuons);

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

          // TODO: Debugging Cutflow
          if (photon->pT() > 40. && photon->abseta() < 2.6) {highpT_photon = true;}// TODO: Debugging
        }

        double jet_eff = 0.9;
        for (const HEPUtils::Jet* jet : event->jets())
        {
          if (jet->pT()>20. && jet->abseta()<2.8)
          {
            if( (jet->pT() >= 120. || jet->abseta() >= 2.5) || random_bool(jet_eff) ) baselineJets.push_back(jet);
          }
        }


        // TODO: Debugging, Removing events for the cutflow that do not pass the generator test
        if (GeneratorFilter.size() < 2) {return;} // TODO: Debugging
        if ((SUSYKernal.size() < 2) && (SUSYKernal_2.size() < 1 || !highpT_photon)) {return;} // TODO: Debugging
        _cutflows.fillnext(w);  // TODO: Debugging

        // Overlap removal
        // 1) Remove muons with 0.01 of an electron, mimics shared tracks
        removeOverlap(baselineMuons, baselineElectrons, 0.01);
        // 2) Remove jets within DeltaR = 0.2 of electron
        removeOverlap(baselineJets, baselineElectrons, 0.2);
        // 3) If any lepton has Delta R < min(0.4, 0.04 + 10/pT(l)) with a jet, remove the lepton.
        auto lambda = [](double lepton_pT) { return std::min(0.4, 0.04 + 10./(lepton_pT) ); };
        //removeOverlap(baselineElectrons, baselineJets, lambda);
        // 4) Remove muons within 0.2 of jets (incorporates shared track approximation) // TODO: I think this is the wrong way around. I think the jet should be removed. Check This
        //removeOverlap(baselineMuons, baselineJets, 0.2); // TODO: Old version, remove after checking
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
        apply1DEfficiency(signalElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Medium"));
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
        bool cut_2baselinelep = false; // At least 2 baseline leptons
        bool cut_1jet = false; // At least one jet
        bool cut_2lep = false; // exactly two leptons (> 25 GeV)
        bool cut_mll = false; // lepton pair mass in (12, 111)
        bool cut_SF = false; // both leptons of the Same Flavour (SF)
        bool cut_OS = false; // both leptons of Opposite Sign (OS) charge *** except VR_SS
        bool cut_metsig = false; // met significance > 6
        bool cut_met = false; // missing energy: met > 100 GeV
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
        while(true)
        {

          // At least two baseline leptons
          if (n_baseline_leptons >= 2) {cut_2baselinelep = true;}
          else {break;}

          // at least one jet (> 30 GeV)
          if (n_jets >= 1) {cut_1jet = true;}
          else {break;}

          // exactly two leptons (> 25 GeV)
          if (n_leptons == 2 && n_baseline_leptons == 2) {cut_2lep = true;}
          else {break;}

          // lepton pair mass in (12, 111)
          HEPUtils::P4 dilepton = signalLeptons.at(0)->mom() + signalLeptons.at(1)->mom();
          mll = dilepton.m();
          if (12 < mll) {cut_mll = true;}
          else {break;}

          // both leptons of the Same Flavour (SF)
          // since we have exactly two leptons,
          // 0 electron <=> 2 muon => SF
          // 1 electron <=> 1 muon => DF
          // 2 electron <=> 0 muon => SF
          if (!(signalElectrons.size() == 1)) {cut_SF = true;}
          else {break;}

          // both leptons of Opposite Sign (OS) charge
          if (!(signalLeptons.at(0)->pid() == signalLeptons.at(1)->pid())) {cut_OS = true;}
          else {break;}

          // Approximate the significance using HT
          // Best we can do, but still rubbish compared to ATLAS definition :-(
          //double HT = 0.0;
          //for (const HEPUtils::Jet* j : baselineJets) HT += j->pT();
          //for (const HEPUtils::Particle* p : baselinePhotons) HT += p->pT();
          //for (const HEPUtils::Particle* e : baselineElectrons) HT += e->pT();
          //for (const HEPUtils::Particle* mu : baselineMuons) HT += mu->pT();

          // missing energy: met > 100 GeV, met significance > 6
          //metsig = met/sqrt(HT); // The approximate method
          metsig = calcMETSignificance(baselineElectrons, baselinePhotons, baselineMuons, baselineJets, event->taus(), metVec); // Using ATLAS' Simple Analysis Framework


          if (metsig > 6) {cut_metsig = true;}
          else {break;}

          if (met > 100) {cut_met = true;}
          else {break;}

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

        // Pre-selection cutflows
        #ifdef CHECK_CUTFLOW
          if (cut_2baselinelep) {_cutflows.fillnext(w);} //cutflow_fillnext("SR_High_8_a", w);
          if (cut_1jet) {_cutflows.fillnext(w);} //cutflow_fillnext("SR_High_8_a", w);
          if (cut_2lep) {_cutflows.fillnext(w);} //cutflow_fillnext("SR_High_8_a", w);
          if (cut_mll) {_cutflows.fillnext(w);} //cutflow_fillnext("SR_High_8_a", w);
          if (cut_SF) {_cutflows.fillnext(w);} //cutflow_fillnext("SR_High_8_a", w);
          if (cut_OS) {_cutflows.fillnext(w);} //cutflow_fillnext("SR_High_8_a", w);
          if (cut_metsig) {_cutflows.fillnext(w);} //cutflow_fillnext("SR_High_8_a", w);
          if (cut_met) {_cutflows.fillnext(w);} //cutflow_fillnext("SR_High_8_a", w);
        #endif

        // If event doesn't pass Pre-selection, exit early
        if (EWK_2Ljets_presel == false) return;

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

        // Apply each series of cuts to form the cutflows

        // SR_High_8/16_a/b
        while (true)
        {
          if (nbjets <= 1)
          {
            cutflow_fillnext("SR_High_8_a", w);
            cutflow_fillnext("SR_High_8_b", w);
            cutflow_fillnext("SR_High_16_a", w);
            cutflow_fillnext("SR_High_16_b", w);
          }
          else
          {
            break;
          }

          if (mll_71_111)
          {
            cutflow_fillnext("SR_High_8_a", w);
            cutflow_fillnext("SR_High_8_b", w);
            cutflow_fillnext("SR_High_16_a", w);
            cutflow_fillnext("SR_High_16_b", w);
          }
          else
          {
            break;
          }

          if (metsig > 18)
          {
            cutflow_fillnext("SR_High_8_a", w);
            cutflow_fillnext("SR_High_8_b", w);
            cutflow_fillnext("SR_High_16_a", w);
            cutflow_fillnext("SR_High_16_b", w);
          }
          else
          {
            break;
          }

          if (mt2_gt_80)
          {
            cutflow_fillnext("SR_High_8_a", w);
            cutflow_fillnext("SR_High_8_b", w);
            cutflow_fillnext("SR_High_16_a", w);
            cutflow_fillnext("SR_High_16_b", w);
          }
          else
          {
            break;
          }

          if (n_jets >= 2)
          {
            cutflow_fillnext("SR_High_8_a", w);
            cutflow_fillnext("SR_High_8_b", w);
            cutflow_fillnext("SR_High_16_a", w);
            cutflow_fillnext("SR_High_16_b", w);
          }
          else
          {
            break;
          }

          if (mjj_60_110)
          {
            cutflow_fillnext("SR_High_8_a", w);
            cutflow_fillnext("SR_High_8_b", w);
            cutflow_fillnext("SR_High_16_a", w);
            cutflow_fillnext("SR_High_16_b", w);
          }
          else
          {
            break;
          }

          if (Rjj_lt_8)
          {
            cutflow_fillnext("SR_High_8_a", w);
            cutflow_fillnext("SR_High_8_b", w);

            if (metsig < 21)
            {
              cutflow_fillnext("SR_High_8_a", w);
              _counters.at("SR_High_8_a").add_event(event);
            }
            else if (metsig > 21)
            {
              cutflow_fillnext("SR_High_8_b", w);
              _counters.at("SR_High_8_b").add_event(event);
            }
          }
          else if (Rjj_8_16)
          {
            cutflow_fillnext("SR_High_16_a", w);
            cutflow_fillnext("SR_High_16_b", w);

            if (metsig < 21)
            {
              cutflow_fillnext("SR_High_16_a", w);
              _counters.at("SR_High_16_a").add_event(event);
            }
            else if (metsig > 21)
            {
              cutflow_fillnext("SR_High_16_b", w);
              _counters.at("SR_High_16_b").add_event(event);
            }
          }

          // Applied all cuts
          break;
        }

        // SR_High_4
        while (true)
        {
          if (nbjets <= 1) {cutflow_fillnext("SR_High_4", w);}
          else {break;}

          if (mll_71_111) {cutflow_fillnext("SR_High_4", w);}
          else {break;}

          if (metsig > 12) {cutflow_fillnext("SR_High_4", w);}
          else {break;}

          if (mt2_gt_80) {cutflow_fillnext("SR_High_4", w);}
          else {break;}

          if (n_jets == 1) {cutflow_fillnext("SR_High_4", w);}
          else {break;}

          if (60 < jetm1 && jetm1 < 110)
          {
            cutflow_fillnext("SR_High_4", w);
            _counters.at("SR_High_4").add_event(event);
          }

          // Applied all cuts
          break;
        }

        // SR_llbb
        while (true)
        {
          if (mll_71_111) {cutflow_fillnext("SR_llbb", w);}
          else {break;}

          if (metsig > 18) {cutflow_fillnext("SR_llbb", w);}
          else {break;}

          if (mt2_gt_80) {cutflow_fillnext("SR_llbb", w);}
          else {break;}

          if (nbjets >= 2) {cutflow_fillnext("SR_llbb", w);}
          else {break;}

          if (n_jets >= 2) {cutflow_fillnext("SR_llbb", w);}
          else {break;}

          if (60 < mbb && mbb < 150)
          {
            cutflow_fillnext("SR_llbb", w);
            _counters.at("SR_llbb").add_event(event);
          }

          // Applied all cuts
          break;
        }

        // SR Int_a/b
        while (true)
        {
          if (nbjets == 0)
          {
            cutflow_fillnext("SR_Int_a", w);
            cutflow_fillnext("SR_Int_b", w);
          }
          else {break;}

          if (mll_81_101)
          {
            cutflow_fillnext("SR_Int_a", w);
            cutflow_fillnext("SR_Int_b", w);
          }
          else {break;}

          if (12 < metsig && metsig < 18)
          {
            cutflow_fillnext("SR_Int_a", w);
            cutflow_fillnext("SR_Int_b", w);
          }
          else {break;}

          if (mt2_gt_80)
          {
            cutflow_fillnext("SR_Int_a", w);
            cutflow_fillnext("SR_Int_b", w);
          }
          else {break;}

          if (jetpt1 > 60)
          {
            cutflow_fillnext("SR_Int_a", w);
            cutflow_fillnext("SR_Int_b", w);
          }
          else {break;}

          if (n_jets >= 2)
          {
            cutflow_fillnext("SR_Int_a", w);
            cutflow_fillnext("SR_Int_b", w);
          }
          else {break;}

          if (mjj_60_110)
          {
            cutflow_fillnext("SR_Int_a", w);
            cutflow_fillnext("SR_Int_b", w);
          }
          else {break;}


          if (metsig < 15)
          {
            cutflow_fillnext("SR_Int_a", w);
            _counters.at("SR_Int_a").add_event(event);
          }
          else if (metsig > 15)
          {
            cutflow_fillnext("SR_Int_b", w);
            _counters.at("SR_Int_b").add_event(event);
          }

          // Applied all cuts
          break;
        }

        //SR_Low_a/b
        while (true)
        {
          if (nbjets == 0)
          {
            cutflow_fillnext("SR_Low_a", w);
            cutflow_fillnext("SR_Low_b", w);
          }
          else {break;}

          if (mll_81_101)
          {
            cutflow_fillnext("SR_Low_a", w);
            cutflow_fillnext("SR_Low_b", w);
          }
          else {break;}

          if (6 < metsig && metsig < 12)
          {
            cutflow_fillnext("SR_Low_a", w);
            cutflow_fillnext("SR_Low_b", w);
          }
          else {break;}

          if (mt2_gt_80)
          {
            cutflow_fillnext("SR_Low_a", w);
            cutflow_fillnext("SR_Low_b", w);
          }
          else {break;}

          if (n_jets == 2)
          {
            cutflow_fillnext("SR_Low_a", w);
            cutflow_fillnext("SR_Low_b", w);
          }
          else {break;}

          if (mjj_60_110)
          {
            cutflow_fillnext("SR_Low_a", w);
            cutflow_fillnext("SR_Low_b", w);
          }
          else {break;}

          if (Rll < 1)
          {
            cutflow_fillnext("SR_Low_a", w);
            cutflow_fillnext("SR_Low_b", w);
          }
          else {break;}

          if (metsig < 9)
          {
            cutflow_fillnext("SR_Low_a", w);
            _counters.at("SR_Low_a").add_event(event);
          }
          else if (metsig > 9)
          {
            cutflow_fillnext("SR_Low_b", w);
            _counters.at("SR_Low_b").add_event(event);
          }

          // Applied all cuts
          break;
        }

        //SR_Low_2
        while (true)
        {
          if (nbjets == 0) {cutflow_fillnext("SR_Low_2", w);}
          else {break;}

          if (mll_81_101) {cutflow_fillnext("SR_Low_2", w);}
          else {break;}

          if (6 < metsig && metsig < 9) {cutflow_fillnext("SR_Low_2", w);}
          else {break;}

          if (mt2_lt_80) {cutflow_fillnext("SR_Low_2", w);}
          else {break;}

          if (n_jets == 2) {cutflow_fillnext("SR_Low_2", w);}
          else {break;}

          if (mjj_60_110) {cutflow_fillnext("SR_Low_2", w);}
          else {break;}

          if (Rll < 1.6) {cutflow_fillnext("SR_Low_2", w);}
          else {break;}

          if (dphiPllMet < 0.6)
          {
            cutflow_fillnext("SR_Low_2", w);
            _counters.at("SR_Low_2").add_event(event);
          }

          // Applied all cuts
          break;
        }

        // SR_OffShell_a/b
        while (true)
        {
          if (nbjets == 0)
          {
            cutflow_fillnext("SR_OffShell_a", w);
            cutflow_fillnext("SR_OffShell_b", w);
          }
          else {break;}

          if (12 < mll && mll < 71)
          {
            cutflow_fillnext("SR_OffShell_a", w);
            cutflow_fillnext("SR_OffShell_b", w);
          }
          else {break;}

          if (metsig > 9)
          {
            cutflow_fillnext("SR_OffShell_a", w);
            cutflow_fillnext("SR_OffShell_b", w);
          }
          else {break;}

          if (mt2 > 100)
          {
            cutflow_fillnext("SR_OffShell_a", w);
            cutflow_fillnext("SR_OffShell_b", w);
          }
          else {break;}

          if (n_jets >= 2)
          {
            cutflow_fillnext("SR_OffShell_a", w);
            cutflow_fillnext("SR_OffShell_b", w);
          }
          else {break;}

          if (jetpt1 > 100)
          {
            cutflow_fillnext("SR_OffShell_a", w);
            cutflow_fillnext("SR_OffShell_b", w);
          }
          else {break;}

          if (Rll < 1.6)
          {
            cutflow_fillnext("SR_OffShell_a", w);
            cutflow_fillnext("SR_OffShell_b", w);
          }
          else {break;}

          if (dphiJ1met > 2)
          {
            cutflow_fillnext("SR_OffShell_a", w);
            cutflow_fillnext("SR_OffShell_b", w);
          }
          else {break;}

          if (mll < 40)
          {
            cutflow_fillnext("SR_OffShell_a", w);
            _counters.at("SR_OffShell_a").add_event(event);
          }
          else if (mll > 40)
          {
            cutflow_fillnext("SR_OffShell_b", w);
            _counters.at("SR_OffShell_b").add_event(event);
          }

          // Applied all cuts
          break;
        }


      } // End run function


      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {

        add_result(SignalRegionData(_counters.at("SR_High_8_a"), 0., {2.00, 0.23}));
        add_result(SignalRegionData(_counters.at("SR_High_8_b"), 0., {2.00, 0.33}));
        add_result(SignalRegionData(_counters.at("SR_High_16_a"), 4., {3.9, 0.7}));
        add_result(SignalRegionData(_counters.at("SR_High_16_b"), 3., {3.4, 0.9}));
        add_result(SignalRegionData(_counters.at("SR_High_4"), 1., {0.85, 0.34}));
        add_result(SignalRegionData(_counters.at("SR_llbb"), 0., {0.58, 0.20}));
        add_result(SignalRegionData(_counters.at("SR_Int_a"), 24., {22.8, 3.5 }));
        add_result(SignalRegionData(_counters.at("SR_Int_b"), 14., {10.1, 1.0}));
        add_result(SignalRegionData(_counters.at("SR_Low_a"), 10., {12.8, 3.4}));
        add_result(SignalRegionData(_counters.at("SR_Low_b"), 8., {10.5, 2.5}));
        add_result(SignalRegionData(_counters.at("SR_Low_2"), 8., {9, 4}));
        add_result(SignalRegionData(_counters.at("SR_OffShell_a"), 6., {9.2, 1.7}));
        add_result(SignalRegionData(_counters.at("SR_OffShell_b"), 15., {12.5, 1.9}));

        #ifdef CHECK_CUTFLOW
          cout << _cutflows << endl;
        #endif


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
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2LEPJETS_EW_139invfb)


  }
}
