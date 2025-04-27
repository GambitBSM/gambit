///
///  \author Tomas Gonzalo
///  \date 2019 June
///  \date 2023 Sep
///
///  \author Chris Chang
///  \date 2024 Nov
///
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2019-014/
// Updated by the published paper SUSY-2018-16, https://arxiv.org/abs/1911.12606

// - 139 fb^-1 data

// Old Analysis Name: ATLAS_13TeV_2LEPsoft_139invfb

#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ROOT
#ifndef EXCLUDE_RESTFRAMES

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/Utils/util_functions.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

#include "RestFrames/RestFrames.hh"
#include "TLorentzVector.h"

using namespace std;

// Renamed from: 
//      ATLAS_13TeV_2LEPsoft_139invfb

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_SUSY_2018_16 : public Analysis
    {

    private:

      unique_ptr<RestFrames::LabRecoFrame>        LAB;
      unique_ptr<RestFrames::DecayRecoFrame>      CM;
      unique_ptr<RestFrames::DecayRecoFrame>      S;

      unique_ptr<RestFrames::VisibleRecoFrame>    ISR;
      unique_ptr<RestFrames::VisibleRecoFrame>    V;
      unique_ptr<RestFrames::VisibleRecoFrame>    L;

      unique_ptr<RestFrames::InvisibleRecoFrame>  I;
      unique_ptr<RestFrames::InvisibleGroup>      INV;

      unique_ptr<RestFrames::SetMassInvJigsaw>    INV_Mass;

      unique_ptr<RestFrames::CombinatoricGroup>   VIS;

      unique_ptr<RestFrames::MinMassesCombJigsaw> SplitVis;


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_SUSY_2018_16()
      {

        DEFINE_SIGNAL_REGIONS("SR-E-low-ee-", 6, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "120 < met < 200 GeV", "met/HTlep < 10", "0.8 < RISR < 1.0", "subleading lepton pT > 5+mll/4", "10 < mTl1 < 60 GeV")
        DEFINE_SIGNAL_REGIONS("SR-E-low-mumu-", 8, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "120 < met < 200 GeV", "met/HTlep < 10", "0.8 < RISR < 1.0", "subleading lepton pT > 5+mll/4", "10 < mTl1 < 60 GeV")
        DEFINE_SIGNAL_REGIONS("SR-E-low-combined-", 8, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "120 < met < 200 GeV", "met/HTlep < 10", "0.8 < RISR < 1.0", "subleading lepton pT > 5+mll/4", "10 < mTl1 < 60 GeV")


        DEFINE_SIGNAL_REGIONS("SR-E-med-ee-", 4, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "120 < met < 200 GeV", "met/HTlep > 10", "MTS < 50 GeV")
        DEFINE_SIGNAL_REGIONS("SR-E-med-mumu-", 6, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "120 < met < 200 GeV", "met/HTlep > 10", "MTS < 50 GeV")
        DEFINE_SIGNAL_REGIONS("SR-E-med-combined-", 6, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "120 < met < 200 GeV", "met/HTlep > 10", "MTS < 50 GeV")

        DEFINE_SIGNAL_REGIONS("SR-E-high-ee-", 6, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "mTl1 < 60 GeV", "met > 200 GeV", "max(0.85, 0.98-0.02xmll) < RISR < 1.0", "subleading lepton pT > min(10,2+mll/3)")
        DEFINE_SIGNAL_REGIONS("SR-E-high-mumu-", 8, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "mTl1 < 60 GeV", "met > 200 GeV", "max(0.85, 0.98-0.02xmll) < RISR < 1.0", "subleading lepton pT > min(10,2+mll/3)")
        DEFINE_SIGNAL_REGIONS("SR-E-high-combined-", 8, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "mTl1 < 60 GeV", "met > 200 GeV", "max(0.85, 0.98-0.02xmll) < RISR < 1.0", "subleading lepton pT > min(10,2+mll/3)")

        DEFINE_SIGNAL_REGIONS("SR-E-1l1T-", 6, "njets > 0", "MET trigger", "1 lepton and >=1 track", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "MET > 200GeV", "min(DeltaPhi(any jet,MET) > 0.4", "Delta(j1) > 2.0", "0.5 < mltrack < 5GeV", "DeltaRltrack > 0.05", "number of jets >= 1", "leading jet pT > 100 GeV", "MET/HTlep > 30", "Deltaltrack < 1.5", "Lepton pT < 10 GeV", "Track pT < 5 GeV", "DeltaPhi(l,MET) < 1.0", "SF lepton-track pair", "OS lepton-track pair")

        DEFINE_SIGNAL_REGIONS("SR-VBF-low-", 7, "pTl1 > 5", "2 baseline leptons", "2 signal leptons", "MET trigger", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "SF", "OS", "1 < mll < 60 GeV", "veto 3 GeV < mll < 3.2 GeV", "mtautau < 0 or > 160 GeV", "number of b-tagged jets = 0", "leading jet pT > 100 GeV", "pT(j2) > 40 GeV", "met > 200 GeV", "met/HTlep > 2.0", "subleading lepton pT > min(10,2+mll/3)", "mTl1 < 60 GeV", "RVBF < 1.0", "RVBF > max(0.6,0.92-mll/2 GeV)", "etaj1*etaj2 < 0", "mjj > 400 GeV", "Deltaetajj > 2")
        DEFINE_SIGNAL_REGIONS("SR-VBF-high-", 7, "pTl1 > 5", "2 baseline leptons", "2 signal leptons", "MET trigger", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "SF", "OS", "1 < mll < 60 GeV", "veto 3 GeV < mll < 3.2 GeV", "mtautau < 0 or > 160 GeV", "number of b-tagged jets = 0", "leading jet pT > 100 GeV", "pT(j2) > 40 GeV", "met > 200 GeV", "met/HTlep > 2.0", "subleading lepton pT > min(10,2+mll/3)", "mTl1 < 60 GeV", "RVBF < 1.0", "RVBF > max(0.6,0.92-mll/2 GeV)", "etaj1*etaj2 < 0", "mjj > 400 GeV", "Deltaetajj > 2")

        DEFINE_SIGNAL_REGIONS("SR-S-low-ee-", 8, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "150 < met < 200 GeV", "0.8 < RISR < 1.0", "subleading lepton pT > min(15,7.5+0.75*(mT2100-100))")
        DEFINE_SIGNAL_REGIONS("SR-S-low-mumu-", 8, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "150 < met < 200 GeV", "0.8 < RISR < 1.0", "subleading lepton pT > min(15,7.5+0.75*(mT2100-100))")
        DEFINE_SIGNAL_REGIONS("SR-S-low-combined-", 8, "njets > 0", "MET trigger", "2 leptons", "veto 3 GeV < mll < 3.2 GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "150 < met < 200 GeV", "0.8 < RISR < 1.0", "subleading lepton pT > min(15,7.5+0.75*(mT2100-100))")

        DEFINE_SIGNAL_REGIONS("SR-S-high-ee-", 8, "njets > 0", "MET trigger", "2 leptons", "veto 3GeV < mll < 3.2GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "met > 200 GeV", "max(0.85,0.98-0.02*mT2100) < RISR < 1.0", "subleading lepton pT > min(20,2.5+2.5*(mT2100-100))")
        DEFINE_SIGNAL_REGIONS("SR-S-high-mumu-", 8, "njets > 0", "MET trigger", "2 leptons", "veto 3GeV < mll < 3.2GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "met > 200 GeV", "max(0.85,0.98-0.02*mT2100) < RISR < 1.0", "subleading lepton pT > min(20,2.5+2.5*(mT2100-100))")
        DEFINE_SIGNAL_REGIONS("SR-S-high-combined-", 8, "njets > 0", "MET trigger", "2 leptons", "veto 3GeV < mll < 3.2GeV", "lepton author 16 veto", "min(DeltaPhi(any jet)) > 0.4", "DeltaPhi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "met > 200 GeV", "max(0.85,0.98-0.02*mT2100) < RISR < 1.0", "subleading lepton pT > min(20,2.5+2.5*(mT2100-100))")

        set_analysis_name("ATLAS_SUSY_2018_16");
        set_luminosity(139);


        // Recursive jigsaw stuff
        #pragma omp critical (init_ATLAS_SUSY_2018_16)
        {
          LAB.reset(new RestFrames::LabRecoFrame("LAB","LAB"));
          CM.reset(new RestFrames::DecayRecoFrame("CM","CM"));
          S.reset(new RestFrames::DecayRecoFrame("S","S"));
          ISR.reset(new RestFrames::VisibleRecoFrame("ISR","ISR"));
          V.reset(new RestFrames::VisibleRecoFrame("V","V"));
          L.reset(new RestFrames::VisibleRecoFrame("L","L"));
          I.reset(new RestFrames::InvisibleRecoFrame("I","I"));

          INV.reset(new RestFrames::InvisibleGroup("INV","INV"));
          INV_Mass.reset(new RestFrames::SetMassInvJigsaw("INV_Mass", "INV_Mass"));

          VIS.reset(new RestFrames::CombinatoricGroup("VIS","VIS"));
          SplitVis.reset(new RestFrames::MinMassesCombJigsaw("SplitVis", "SplitVis"));

          LAB->SetChildFrame(*CM);
          CM->AddChildFrame(*ISR);
          CM->AddChildFrame(*S);
          S->AddChildFrame(*V);
          S->AddChildFrame(*I);
          S->AddChildFrame(*L);

          if(!LAB->InitializeTree())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB->InitializeTree() from the Analysis_ATLAS_SUSY_2018_16 analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }

          //////////////////////////////
          //Setting the invisible
          //////////////////////////////
          INV->AddFrame(*I);

          VIS->AddFrame(*ISR);
          VIS->SetNElementsForFrame(*ISR, 1, false);
          VIS->AddFrame(*V);
          VIS->SetNElementsForFrame(*V, 0, false);

          INV->AddJigsaw(*INV_Mass);
          VIS->AddJigsaw(*SplitVis);

          SplitVis->AddFrame(*ISR,0);
          SplitVis->AddFrame(*V,1);
          SplitVis->AddFrame(*I,1);
          SplitVis->AddFrame(*L,1);

          if(!LAB->InitializeAnalysis())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB->InitializeAnalysis() from the Analysis_ATLAS_SUSY_2018_16 analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }
        }
      }

      void run(const HEPUtils::Event* event)
      {

        // Missing momentum and energy
        double met = event->met();
        HEPUtils::P4 ptot = event->missingmom();

        // TODO: Candidate events are required to have at least one reconstructed pp interaction vertex
        // with a minimum of two associated tracks with pT > 500 MeV
        // TODO: In events with multiple vertices, the primary vertex is defined as the one
        // with the highest sum pT^2 of associated tracks.
        // Missing: We cannot reject events with detector noise or non-collision backgrounds.

        // *******************
        // Preselected objects

        // Electrons are required to have pT > 4.5 GeV and |η| < 2.47.
        // There is no VeryLoose criterium in 1908.00005, so using Loose
        BASELINE_PARTICLES(event->electrons(), preselectedElectrons, 4.5, 0, DBL_MAX, 2.47)
        applyEfficiency(preselectedElectrons, ATLAS::eff1DEl.at("ATLAS_SUSY_2018_16"), /* bin_pT*/ true);

        // Preselected electrons are further required to pass the calorimeter-
        // and tracking-based VeryLoose likelihood identification (arXiv:1902.04655),
        // and to have a longitudinal impact parameter z0 relative to the primary vertex
        // that satisfies |z0 sin θ| < 0.5 mm.
        // Missing: We cannot add cuts relating to impact parameters

        // Muons are required to satisfy pT > 3 GeV and |η| < 2.5.
        // Preselected muons are identified using the LowPt criterion,
        // a re-optimised selection similar to those defined in (arXiv:1603.05598)
        // but with improved signal efficiency and background rejection for pT < 10 GeV muon candidates.
        // Preselected muons must also satisfy |z0 sin θ| < 0.5 mm
        // Missing: No impact parameter info

        BASELINE_PARTICLES(event->muons(), preselectedMuons, 3.0, 0, DBL_MAX, 2.5)
        applyEfficiency(preselectedMuons, ATLAS::eff1DMu.at("ATLAS_SUSY_2018_16"), /* bin_pT*/ true);

        // Preselected tracks with pT > 500 MeV and η < 2.5
        // Signal tracks are required to be within ∆R = 0.01 of a reconstructed electron or muon candidate.
        // Electron (muon) candidates can be reconstructed with transverse momenta as low as 1 (2) GeV, 
        // and are required to fail the signal lepton requirements defined above to avoid any overlap
        // We do not really have tracks, so for our purposes, signal tracks are just leptons
        // down to 500 MeV that are not signal leptons.
        // First select the preselected tracks and we'll compare to signal leptons later
        std::vector<const HEPUtils::Particle*> preselectedTracks;
        for (const HEPUtils::Particle* e : event->electrons())
        {
          if (e->pT() > 0.5 && e->pT() < 4.5 && e->abseta() < 2.5) preselectedTracks.push_back(e);
        }

        for (const HEPUtils::Particle* mu : event->electrons())
        {
          if (mu->pT() > 0.5 && mu->pT() < 3.0 && mu->abseta() < 2.5) preselectedTracks.push_back(mu);
        }

        // Apply Track Efficiency (Figure 3 of 1911.12606)
        applyEfficiency(preselectedTracks, ATLAS::eff1DTrack.at("ATLAS_SUSY_2018_16_isolated_track"), /* use pT bins*/ true);


        // Preselected jets are reconstructed from calorimeter topological energy clusters [105]
        // in the region |η| < 4.5 using the anti-kt algorithm [106, 107]
        // with radius parameter R = 0.4. The jets are required to have pT > 20 GeV
        // after being calibrated in accord with Ref. [108]
        // and having the expected energy contribution from pileup subtracted according to the jet area [109].
        // In order to suppress jets due to pileup, jets with pT < 120 GeV
        // and |η| < 2.5 are required to satisfy the Medium working point of the jet vertex tagger [109],
        // which uses information from the tracks associated with the jet.
        // The Loose working point of the forward jet vertex tagger [110] is in turn used
        // to suppress pileup in jets with pT < 50 GeV and |η| > 2.5.
        // TODO: There are neither Medium nor Loose WP defined in the references, so not sure which efficiency to apply
        BASELINE_JETS(event->jets("antikt_R04"), preselectedJets, 20, 0, DBL_MAX, 4.5)

        // B-tagged jets, are identified from preselected jets within |η| < 2.5.
        // The pT > 20 GeV requirement is maintained to maximise the rejection of the tt¯ background.
        // The b-tagging algorithm working point is chosen so that b-jets 
        // from simulated tt¯ events are identified with an 85% efficiency,
        // with rejection factors of 3 for charm-quark jets and 34 for light-quark and gluon jets.
        // Jets identified as containing b-hadron decays, referred to as b-tagged jets,
        // are identified from preselected jets within |η| < 2.5 using the MV2c10 algorithm [111].
        // The pT > 20 GeV requirement is maintained to maximize the rejection of the tt¯ background.
        // The b-tagging algorithm working point is chosen so that b-jets from simulated tt¯ events
        // are identified with an 85% efficiency, with rejection factors of 2.7 for charm-quark jets
        // and 25 for light-quark and gluon jets.
        std::vector<const HEPUtils::Jet*> preselectedBJets, preselectedNonBJets;
        double btag = 0.85; double cmisstag = 1/2.7; double misstag = 1/25.;
        for (const HEPUtils::Jet* jet : preselectedJets)
        {
          if (jet->btag() && jet->abseta() < 2.5 && random_bool(btag) ) preselectedBJets.push_back(jet);
          else if (jet->ctag() && random_bool(cmisstag) ) preselectedBJets.push_back(jet);
          else if (random_bool(misstag)) preselectedBJets.push_back(jet);
          else preselectedNonBJets.push_back(jet);
        }

        // ***************
        // Overlap removal

        // Electrons within R < 0.2 of a muon are removed
        removeOverlap(preselectedElectrons, preselectedMuons, 0.01);

        // Non-b-tagged jets that are separated from the remaining electrons by ∆Ry < 0.2 are removed
        // Using rapidity instead of pseudorapidity
        removeOverlap(preselectedNonBJets, preselectedElectrons, 0.2, true);

        // Jets containing a muon candidate within ∆Ry < 0.4 and with fewer than three tracks
        // with pT > 500 MeV are removed to suppress muon bremsstrahlung.
        // Using rapidity instead of pseudorapidity
        // Do this for both on b-tagged and non-b-tagged jets
        // Missing: We have no information about internal jet tracks
        removeOverlap(preselectedBJets, preselectedMuons, 0.4, true);
        removeOverlap(preselectedNonBJets, preselectedMuons, 0.4, true);

        // Electrons or muons with ∆Ry < 0.4 from surviving jet candidates are removed
        // to suppress bottom and charm hadron decays
        // Do this for both b-tagged and non-b-tagged jets
        removeOverlap(preselectedElectrons, preselectedNonBJets, 0.4);
        removeOverlap(preselectedMuons, preselectedNonBJets, 0.4);
        removeOverlap(preselectedElectrons, preselectedBJets, 0.4);
        removeOverlap(preselectedMuons, preselectedBJets, 0.4);

        // Preselected leptons
        BASELINE_PARTICLE_COMBINATION(preselectedLeptons, preselectedElectrons, preselectedMuons)
        size_t nBaselineLeptons = preselectedLeptons.size();

        int Filter_N_jets = preselectedBJets.size() + preselectedNonBJets.size();

        //***************
        // Signal objects

        // Signal electrons must satisfy the Medium identification criterion (arXiv:1902.04655),
        // and be compatible with originating from the primary vertex,
        // with the significance of the transverse impact parameter defined relative to
        // the beam position satisfying |d0|/σ(d0) < 5.
        // Signal electrons are further refined using the Gradient isolation working point (arXiv:1902.04655),
        // which uses both tracking and calorimeter information.
        // Missing: No impact parameter info
        // All Electron Efficiency is covered in the preselected Electrons
        SIGNAL_PARTICLES(preselectedElectrons, signalElectrons)

        // All Muon Efficiency is covered in the preselected muons
        SIGNAL_PARTICLES(preselectedMuons, signalMuons)

        // Signal leptons
        SIGNAL_PARTICLE_COMBINATION(signalLeptons, signalElectrons, signalMuons)

        // Signal tracks
        // Signal tracks are required to be within ∆R = 0.01 of a reconstructed electron or muon candidate.
        // Electron (muon) candidates can be reconstructed with transverse momenta as low as 1 (2) GeV,
        // and are required to fail the signal lepton requirements defined above to avoid any overlap
        // Remove all signals that match a signallepton
        std::vector<const HEPUtils::Particle*> candidateTracks;
        for(auto &track : preselectedTracks)
        {
          bool isSignalLepton = false;
          for(auto &lep : signalLeptons)
          {
            if(lep == track) isSignalLepton = true;
          }
          if(not isSignalLepton) candidateTracks.push_back(track);
        }

        // The sum pT of preselected tracks within ∆R < 0.3 of signal tracks, excluding the contributions
        // from nearby leptons, is required to be smaller than 0.5 GeV.
        // Finally, signal tracks must satisfy pT > 1 GeV, |z0 sin θ| < 0.5 mm and |d0|/σ(d0) < 3.
        // Mising: cannot do impact parameter cuts
        std::vector<const HEPUtils::Particle*> signalTracks;
        for (const HEPUtils::Particle* track1 : candidateTracks)
        {
          double pTSum = 0;
          for (const HEPUtils::Particle* track2 : candidateTracks)
          {
            if (track2 != track1 && track1->mom().deltaR_eta(track2->mom()) < 0.3) pTSum += track2->pT();
          }
          if (pTSum < 0.5 && track1->pT() > 1.) signalTracks.push_back(track1);
        }

        // Signal tracks must also satisfy dedicated isolation criteria – they are required
        // to be separated from preselected jets by at least ∆R > 0.5
        removeOverlap(signalTracks, preselectedNonBJets, 0.5);
        removeOverlap(signalTracks, preselectedBJets, 0.5);

        // Signal jets. From the sample of preselected jets, signal jets are selected
        // if they satisfy pT > 30 GeV and |η| < 2.8.
        // The VBF search uses a modified version of signal jets, labeled VBF jets, satisfying pT > 30 GeV and |η| < 4.5.
        std::vector<const HEPUtils::Jet*> signalJets;
        std::vector<const HEPUtils::Jet*> signalVBFJets;
        std::vector<const HEPUtils::Jet*> signalBJets;

        // Signal jets are selected if they satisfy pT > 30 GeV and |η| < 2.8.
        for (const HEPUtils::Jet* jet : preselectedNonBJets)
        {
          if (jet->pT() > 30. && jet->abseta() < 2.8) signalJets.push_back(jet);
          if (jet->pT() > 30. && jet->abseta() < 4.5) signalVBFJets.push_back(jet);
        }
        for (const HEPUtils::Jet* jet : preselectedBJets)
        {
          if (jet->pT() > 30. && jet->abseta() < 2.8)
          {
            signalJets.push_back(jet);
            signalBJets.push_back(jet);
          }
          if (jet->pT() > 30. && jet->abseta() < 4.5) signalVBFJets.push_back(jet);
        }

        // Sort by pT
        sortByPt(signalJets);
        sortByPt(signalBJets);
        sortByPt(signalVBFJets);
        sortByPt(signalLeptons);
        sortByPt(signalTracks);

        // Preselection requirements
        // Variable            2l                                              1l1T
        // ------------------------------------------------------------------------------
        // n-leptons           =2                                          =1 l + >=1 T     
        // lepton-1  pT        > 5                                          < 10            
        // Delta Rll           DRee > 0.3, DRmm > 0.05, DRem > 0.2      0.05 < DRlT < 1.5   
        // Charge/Flav         e+- e-+ or mu+- mu-+                     e+- e-+ or mu+- mu-+
        // Inv mass            3 < mee < 60,  1 < mmumu < 60               0.5 < mlT < 5    
        // J/psi inv mass      veto 3 < mll < 3.2                         veto 3 < mlT < 3.2
        // mtt                 < 0 or > 160                                     -           
        // MET                 > 120                                          > 120         
        // n-jets              >= 1                                           >= 1          
        // n-b-tagged-jets     = 0                                              -           
        // leading jet pT      > 100                                         > 100           
        // min(Dphi(j,ptmiss)  > 0.4                                         > 0.4           
        // Dphi(j1,ptmiss)     >= 2.0                                        >= 2.0          

        // Count signal leptons and jets
        size_t nSignalLeptons = signalLeptons.size();
        size_t nSignalJets = signalJets.size();
        size_t nSignalVBFJets = signalVBFJets.size();
        size_t nSignalBJets = signalBJets.size();
        size_t nSignalTracks = signalTracks.size();

        // MET trigger
        bool mettrigger = random_bool(ATLAS::eff1DMET.at("CERN_EP_2015_241"), met);

        // 2-particle system
        std::vector<const HEPUtils::Particle *> signalParticles;

        if (nSignalLeptons == 2)
        {
          signalParticles.push_back(signalLeptons.at(0));
          signalParticles.push_back(signalLeptons.at(1));
        }
        else if (nSignalLeptons == 1 && nSignalTracks >=1 )
        {
          signalParticles.push_back(signalLeptons.at(0));
          signalParticles.push_back(signalTracks.at(0));
        }
        size_t nSignalParticles = signalParticles.size();

        // DeltaR
        double deltaR = nSignalParticles > 1 ? signalParticles.at(0)->mom().deltaR_eta(signalParticles.at(1)->mom()) : 0.;

        // ID
        bool electron_pair = nSignalParticles > 1 ? (signalParticles.at(0)->isElectron() && signalParticles.at(1)->isElectron()) : false;
        bool muon_pair = nSignalParticles > 1 ? (signalParticles.at(0)->isMuon() && signalParticles.at(1)->isMuon()) : false;

        // SFOS
        bool SF = nSignalParticles > 1 ? signalParticles.at(0)->abspid() == signalParticles.at(1)->abspid() : false;
        bool OS = nSignalParticles > 1 ? signalParticles.at(0)->pid() * signalParticles.at(1)->pid() < 0 : false;
        bool SFOS = SF && OS;

        // Invariant mass
        double mll = nSignalParticles > 1 ? (signalParticles.at(0)->mom() + signalParticles.at(1)->mom() ).m() : 0.;

        // HTlep
        double metOverHTlep = nSignalParticles > 1 ? met/(signalParticles.at(0)->pT() + signalParticles.at(1)->pT()) : 0.;

        // mtautau
        double mtautau = 0.;
        if (nSignalLeptons == 2 and SFOS)
        {
          double determinant = signalLeptons.at(0)->mom().px() * signalLeptons.at(1)->mom().py() - signalLeptons.at(0)->mom().py() * signalLeptons.at(1)->mom().px();
          double xi_1 = (ptot.px() * signalLeptons.at(1)->mom().py() - signalLeptons.at(1)->mom().px() * ptot.py()) / determinant;
          double xi_2 = (ptot.py() * signalLeptons.at(0)->mom().px() - signalLeptons.at(0)->mom().py() * ptot.px()) / determinant;
          mtautau = (1.+xi_1) * (1.+xi_2) * 2. * signalLeptons.at(0)->mom().dot(signalLeptons.at(1)->mom());
          if(mtautau > 0) mtautau = sqrt(mtautau);
          if(mtautau < 0) mtautau = -sqrt(-mtautau);
        }

        // DeltaPhi
        double minPhi = M_PI;
        for(const HEPUtils::Jet *jet : signalJets)
        {
          if(jet != signalJets.at(0))
          {
            double deltaphi = jet->mom().deltaPhi(ptot);
            if (deltaphi < minPhi)
            {
              minPhi = deltaphi;
            }
          }
        }


        // Initialize cutflow counters
        BEGIN_PRESELECTION
        // There is no particular preseletion cut
        END_PRESELECTION

        // Preselection cuts for 2l regions
        std::vector<bool> preselection_2l = {(Filter_N_jets > 0 ),
                                             mettrigger,
                                             nSignalLeptons == 2,
                                             (mll < 3. || mll > 3.2),
                                             true, // lepton author 16 veto
                                             (minPhi  > 0.4),
                                             (nSignalJets > 0 && signalJets.at(0)->mom().deltaPhi(ptot) >= 2.),
                                             true, // lepton truth matching
                                             (mll > (electron_pair ? 3. : 1.) && mll < 60.),
                                             (deltaR > (electron_pair ? 0.3 : (muon_pair ? 0.05 : 0.2) ) ),
                                             (nSignalLeptons > 0 && signalLeptons.at(0)->pT() > 5.),
                                             (nSignalJets >= 1),
                                             (nSignalJets > 0 && signalJets.at(0)->pT() >= 100.),
                                             (nSignalBJets == 0),
                                             (mtautau <= 0. || mtautau > 160.),
                                             (SFOS)
                                           };


        LOG_CUTS_N(preselection_2l, "SR-E-low-ee-", 6)
        LOG_CUTS_N(preselection_2l, "SR-E-low-mumu-", 8)
        LOG_CUTS_N(preselection_2l, "SR-E-low-combined-", 8)
        LOG_CUTS_N(preselection_2l, "SR-E-med-ee-", 4)
        LOG_CUTS_N(preselection_2l, "SR-E-med-mumu-", 6)
        LOG_CUTS_N(preselection_2l, "SR-E-med-combined-", 6)
        LOG_CUTS_N(preselection_2l, "SR-E-high-ee-", 6)
        LOG_CUTS_N(preselection_2l, "SR-E-high-mumu-", 8)
        LOG_CUTS_N(preselection_2l, "SR-E-high-combined-", 8)
        LOG_CUTS_N(preselection_2l, "SR-S-low-ee-", 6)
        LOG_CUTS_N(preselection_2l, "SR-S-low-mumu-", 8)
        LOG_CUTS_N(preselection_2l, "SR-S-low-combined-", 8)
        LOG_CUTS_N(preselection_2l, "SR-S-high-ee-", 6)
        LOG_CUTS_N(preselection_2l, "SR-S-high-mumu-", 8)
        LOG_CUTS_N(preselection_2l, "SR-S-high-combined-", 8)

        // Preselection cuts for 2l VBF regions
        std::vector<bool> preselection_2l_VBF = { (nSignalLeptons > 0 && signalLeptons.at(0)->pT() > 5.),
                                                  (nBaselineLeptons == 2),
                                                  (nSignalLeptons == 2),
                                                  (mettrigger),
                                                  true, // lepton author 16 veto
                                                  (minPhi  > 0.4),
                                                  (deltaR > (electron_pair ? 0.3 : (muon_pair ? 0.05 : 0.2) ) ),
                                                  SF,
                                                  OS,
                                                  (mll > (electron_pair ? 3. : 1.) && mll < 60.),
                                                  (mll < 3. || mll > 3.2),
                                                  (mtautau < 0. || mtautau > 160.),
                                                  (nSignalBJets == 0),
                                                  (nSignalVBFJets >= 1 && signalVBFJets.at(0)->pT() >= 100.)
                                                };
        LOG_CUTS_N(preselection_2l_VBF, "SR-VBF-low-", 7)
        LOG_CUTS_N(preselection_2l_VBF, "SR-VBF-high-", 7)

        // Preselecton cuts for 1l1T region
        std::vector<bool> preselection_1l1T = { (Filter_N_jets > 0 ),
                                                (mettrigger),
                                                (nSignalLeptons == 1 && nSignalTracks >= 1),
                                                (mll < 3. || mll > 3.2),
                                                true, // lepton author 16 veto
                                                (met > 200.),
                                                (minPhi > 0.4),
                                                (nSignalJets > 0 && signalJets.at(0)->mom().deltaPhi(ptot) >= 2.),
                                                (mll > 0.5 && mll < 5),
                                                (deltaR > 0.05),
                                                (nSignalJets >= 1),
                                                (nSignalJets > 0 && signalJets.at(0)->pT() >= 100.),
                                                (metOverHTlep > 30.),
                                                (deltaR < 1.5),
                                                (nSignalLeptons > 0 && signalLeptons.at(0)->pT() < 10.)
                                              };
        LOG_CUTS_N(preselection_1l1T, "SR-E-1l1T-", 6)

        // EWino Signal regions
        // Variable                   SR-E-low          SR-E-med                SR-E-high                        SR-E-1l1T
        // ---------------------------------------------------------------------------------------------------------------
        // MET                        [120,200]         [120,200]               > 200                            > 200
        // MET/HTlep                  < 10              > 10                    -                                > 30
        // DPhi(lep,ptot)             -                 -                       -                                < 1.0
        // l2 or track pT             -                 > 5 + mll/4             > min(10, 2+mll/3)               < 5
        // MTS                        -                 < 50                       -                             -
        // mTl1                       -                 [10,60]                 < 60                             -  
        // RISR                       [0.8,1.0]         -               [max(0.85, 0.98-0.02 mll),1.0]           -

        // mTl1 variable
        double mTl1 = 0.0;
        if (nSignalLeptons > 0)
        {
         double v1_mt = sqrt(signalLeptons.at(0)->mom().E2() - signalLeptons.at(0)->mom().pz2());
         mTl1 = sqrt(signalLeptons.at(0)->mom().m2() + 2.0*v1_mt*ptot.pT() - 2.0*signalLeptons.at(0)->mom().pT()*ptot.pT()*cos(signalLeptons.at(0)->mom().deltaPhi(ptot)));
        }


        //---------------------
        // RJR Variables
        // -------------------
        double Pt_ISR = 0.0; 
        double RISR = 0.0;
        double MTS = 0.0;

        // Only calculate RJR variables in the case that there is at least 1 signal jet, this will also cover the VBF case
        if (nSignalJets > 0)
        {
          LAB->ClearEvent();

          vector<RestFrames::RFKey> jetID;
          for (const auto jet : signalJets)
          {
            TLorentzVector jetmom;
            jetmom.SetPtEtaPhiM((jet->mom()).pT(),0.0,(jet->mom()).phi(),(jet->mom()).m());
            jetID.push_back(VIS->AddLabFrameFourVector(jetmom));
          }

          TLorentzVector lepSys(0.,0.,0.,0.);
          for(const auto lep1 : signalLeptons)
          {
            TLorentzVector tmom;
            tmom.SetPtEtaPhiM((lep1->mom()).pT(),0.0,(lep1->mom()).phi(),(lep1->mom()).m());
            lepSys = lepSys + tmom;
          }

          L->SetLabFrameFourVector(lepSys);
          TLorentzVector metVec;
          metVec.SetPtEtaPhiM(ptot.pT(),ptot.eta(),ptot.phi(),ptot.m());
          TVector3 met3Vec = metVec.Vect();
          met3Vec.SetZ(0.0);
          INV->SetLabFrameThreeVector(met3Vec);


          if (!LAB->AnalyzeEvent())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB->AnalyzeEvent() from the Analysis_ATLAS_SUSY_2018_16 analysis class.\n";
            piped_warnings.request(LOCAL_INFO, errmsg);
            return;
          }

          TVector3 v_P_ISR = ISR->GetFourVector(*CM).Vect();
          TVector3 v_P_I   = I->GetFourVector(*CM).Vect();
          Pt_ISR = v_P_ISR.Mag();
          RISR = fabs(v_P_I.Dot(v_P_ISR.Unit())) / Pt_ISR;
          MTS = S->GetMass();
        }


        // SR-E-low
        std::vector<bool> cuts_2l_e_low = { met > 120. && met < 200.,
                                            metOverHTlep < 10.,
                                            RISR >= 0.8 && RISR <= 1.0,
                                            nSignalLeptons > 1 && signalLeptons.at(1)->pT() > 5. + mll/4.,
                                            mTl1 >= 10. && mTl1 <= 60
                                          };
        if (Utils::all_of(preselection_2l))
        {
          LOG_CUTS_N(cuts_2l_e_low, "SR-E-low-ee-", 6)
          LOG_CUTS_N(cuts_2l_e_low, "SR-E-low-mumu-", 8)
          LOG_CUTS_N(cuts_2l_e_low, "SR-E-low-combined-", 8)
        }
        if (Utils::all_of(preselection_2l) && Utils::all_of(cuts_2l_e_low))
        {
          if (electron_pair)
          {
            if (mll > 3.2 && mll <= 5)      { FILL_SIGNAL_REGION("SR-E-low-ee-1") }
            else if (mll > 5 && mll <= 10)  { FILL_SIGNAL_REGION("SR-E-low-ee-2") }
            else if (mll > 10 && mll <= 20) { FILL_SIGNAL_REGION("SR-E-low-ee-3") }
            else if (mll > 20 && mll <= 30) { FILL_SIGNAL_REGION("SR-E-low-ee-4") }
            else if (mll > 30 && mll <= 40) { FILL_SIGNAL_REGION("SR-E-low-ee-5") }
            else if (mll > 40 && mll <= 60) { FILL_SIGNAL_REGION("SR-E-low-ee-6") }
          }
          else if (muon_pair)
          {
            if(mll >= 1 && mll <= 2)        { FILL_SIGNAL_REGION("SR-E-low-mumu-1") }
            else if (mll > 2 && mll <= 3)   { FILL_SIGNAL_REGION("SR-E-low-mumu-2") }
            else if (mll > 3.2 && mll <= 5) { FILL_SIGNAL_REGION("SR-E-low-mumu-3") }
            else if (mll > 5 && mll <= 10)  { FILL_SIGNAL_REGION("SR-E-low-mumu-4") }
            else if (mll > 10 && mll <= 20) { FILL_SIGNAL_REGION("SR-E-low-mumu-5") }
            else if (mll > 20 && mll <= 30) { FILL_SIGNAL_REGION("SR-E-low-mumu-6") }
            else if (mll > 30 && mll <= 40) { FILL_SIGNAL_REGION("SR-E-low-mumu-7") }
            else if (mll > 40 && mll <= 60) { FILL_SIGNAL_REGION("SR-E-low-mumu-8") }
          }
          
          if(mll >= 1 && mll <= 2)        { FILL_SIGNAL_REGION("SR-E-low-combined-1") }
          else if (mll > 2 && mll <= 3)   { FILL_SIGNAL_REGION("SR-E-low-combined-2") }
          else if (mll > 3.2 && mll <= 5) { FILL_SIGNAL_REGION("SR-E-low-combined-3") }
          else if (mll > 5 && mll <= 10)  { FILL_SIGNAL_REGION("SR-E-low-combined-4") }
          else if (mll > 10 && mll <= 20) { FILL_SIGNAL_REGION("SR-E-low-combined-5") }
          else if (mll > 20 && mll <= 30) { FILL_SIGNAL_REGION("SR-E-low-combined-6") }
          else if (mll > 30 && mll <= 40) { FILL_SIGNAL_REGION("SR-E-low-combined-7") }
          else if (mll > 40 && mll <= 60) { FILL_SIGNAL_REGION("SR-E-low-combined-8") }
        }

        // SR-E-med
        std::vector<bool> cuts_2l_e_med = { met > 120. && met < 200.,
                                            metOverHTlep > 10.,
                                            MTS < 50.
                                          };
        if (Utils::all_of(preselection_2l))
        {
          LOG_CUTS_N(cuts_2l_e_med, "SR-E-med-ee-", 4)
          LOG_CUTS_N(cuts_2l_e_med, "SR-E-med-mumu-", 6)
          LOG_CUTS_N(cuts_2l_e_med, "SR-E-med-combined-", 6)
        }
        if (Utils::all_of(preselection_2l) && Utils::all_of(cuts_2l_e_med))
        {
          if (electron_pair)
          {
            if (mll > 3.2 && mll <= 5)      { FILL_SIGNAL_REGION("SR-E-med-ee-1") }
            else if (mll > 5 && mll <= 10)  { FILL_SIGNAL_REGION("SR-E-med-ee-2") }
            else if (mll > 10 && mll <= 20) { FILL_SIGNAL_REGION("SR-E-med-ee-3") }
            else if (mll > 20 && mll <= 30) { FILL_SIGNAL_REGION("SR-E-med-ee-4") }
          }
          else if (muon_pair)
          {
            if(mll >= 1 && mll <= 2)        { FILL_SIGNAL_REGION("SR-E-med-mumu-1") }
            else if (mll > 2 && mll <= 3)   { FILL_SIGNAL_REGION("SR-E-med-mumu-2") }
            else if (mll > 3.2 && mll <= 5) { FILL_SIGNAL_REGION("SR-E-med-mumu-3") }
            else if (mll > 5 && mll <= 10)  { FILL_SIGNAL_REGION("SR-E-med-mumu-4") }
            else if (mll > 10 && mll <= 20) { FILL_SIGNAL_REGION("SR-E-med-mumu-5") }
            else if (mll > 20 && mll <= 30) { FILL_SIGNAL_REGION("SR-E-med-mumu-6") }
          }
          if(mll >= 1 && mll <= 2)        { FILL_SIGNAL_REGION("SR-E-med-combined-1") }
          else if (mll > 2 && mll <= 3)   { FILL_SIGNAL_REGION("SR-E-med-combined-2") }
          else if (mll > 3.2 && mll <= 5) { FILL_SIGNAL_REGION("SR-E-med-combined-3") }
          else if (mll > 5 && mll <= 10)  { FILL_SIGNAL_REGION("SR-E-med-combined-4") }
          else if (mll > 10 && mll <= 20) { FILL_SIGNAL_REGION("SR-E-med-combined-5") }
          else if (mll > 20 && mll <= 30) { FILL_SIGNAL_REGION("SR-E-med-combined-6") }
        }

        // SR-E-high
        std::vector<bool> cuts_2l_e_high = { mTl1 < 60.,
                                             met > 200.,
                                             RISR >= max(0.85, 0.98 - 0.02*mll) && RISR <= 1.0,
                                             nSignalLeptons > 1 && signalLeptons.at(1)->pT() > min(10., 2.+mll/3)
                                           };
        if (Utils::all_of(preselection_2l))
        {
          LOG_CUTS_N(cuts_2l_e_high, "SR-E-high-ee-", 6)
          LOG_CUTS_N(cuts_2l_e_high, "SR-E-high-mumu-", 8)
          LOG_CUTS_N(cuts_2l_e_high, "SR-E-high-combined-", 8)
        }
        if (Utils::all_of(preselection_2l) && Utils::all_of(cuts_2l_e_high))
        {
          if (electron_pair)
          {
            if (mll > 3.2 && mll <= 5) { FILL_SIGNAL_REGION("SR-E-high-ee-1") }
            else if (mll > 5 && mll <= 10)  { FILL_SIGNAL_REGION("SR-E-high-ee-2") }
            else if (mll > 10 && mll <= 20) { FILL_SIGNAL_REGION("SR-E-high-ee-3") }
            else if (mll > 20 && mll <= 30) { FILL_SIGNAL_REGION("SR-E-high-ee-4") }
            else if (mll > 30 && mll <= 40) { FILL_SIGNAL_REGION("SR-E-high-ee-5") }
            else if (mll > 40 && mll <= 60) { FILL_SIGNAL_REGION("SR-E-high-ee-6") }
          }
          else if (muon_pair)
          {
            if(mll >= 1 && mll <= 2)        { FILL_SIGNAL_REGION("SR-E-high-mumu-1") }
            else if (mll > 2 && mll <= 3)   { FILL_SIGNAL_REGION("SR-E-high-mumu-2") }
            else if (mll > 3.2 && mll <= 5) { FILL_SIGNAL_REGION("SR-E-high-mumu-3") }
            else if (mll > 5 && mll <= 10)  { FILL_SIGNAL_REGION("SR-E-high-mumu-4") }
            else if (mll > 10 && mll <= 20) { FILL_SIGNAL_REGION("SR-E-high-mumu-5") }
            else if (mll > 20 && mll <= 30) { FILL_SIGNAL_REGION("SR-E-high-mumu-6") }
            else if (mll > 30 && mll <= 40) { FILL_SIGNAL_REGION("SR-E-high-mumu-7") }
            else if (mll > 40 && mll <= 60) { FILL_SIGNAL_REGION("SR-E-high-mumu-8") }
          }
          if(mll >= 1 && mll <= 2)        { FILL_SIGNAL_REGION("SR-E-high-combined-1") }
          else if (mll > 2 && mll <= 3)   { FILL_SIGNAL_REGION("SR-E-high-combined-2") }
          else if (mll > 3.2 && mll <= 5) { FILL_SIGNAL_REGION("SR-E-high-combined-3") }
          else if (mll > 5 && mll <= 10)  { FILL_SIGNAL_REGION("SR-E-high-combined-4") }
          else if (mll > 10 && mll <= 20) { FILL_SIGNAL_REGION("SR-E-high-combined-5") }
          else if (mll > 20 && mll <= 30) { FILL_SIGNAL_REGION("SR-E-high-combined-6") }
          else if (mll > 30 && mll <= 40) { FILL_SIGNAL_REGION("SR-E-high-combined-7") }
          else if (mll > 40 && mll <= 60) { FILL_SIGNAL_REGION("SR-E-high-combined-8") }
        }

        // SR-E-1l1T
        std::vector<bool> cuts_1l1T = { nSignalTracks > 0 && signalTracks.at(0)->pT() < 5.,
                                        nSignalLeptons > 0 && signalLeptons.at(0)->mom().deltaPhi(ptot) < 1.0,
                                        SF,
                                        OS
                                      };
        if (Utils::all_of(preselection_1l1T)) { LOG_CUTS_N(cuts_1l1T, "SR-E-1l1T-", 6) }
        if (Utils::all_of(preselection_1l1T) && Utils::all_of(cuts_1l1T))
        {
           if(mll >= 0.5 && mll <= 1.0)        { FILL_SIGNAL_REGION("SR-E-1l1T-1") }
           else if (mll > 1.0 && mll <= 1.5)   { FILL_SIGNAL_REGION("SR-E-1l1T-2") }
           else if (mll > 1.5 && mll <= 2.0)   { FILL_SIGNAL_REGION("SR-E-1l1T-3") }
           else if (mll > 2.0 && mll <= 3.0)   { FILL_SIGNAL_REGION("SR-E-1l1T-4") }
           else if (mll > 3.2 && mll <= 4.0)   { FILL_SIGNAL_REGION("SR-E-1l1T-5") }
           else if (mll > 4.0 && mll <= 5.0)   { FILL_SIGNAL_REGION("SR-E-1l1T-6") }
        }

        // VBF Signal regions
        // Variable             SR-VBF-low                      SR-VBF-high
        // ----------------------------------------------------------------
        // mll                  < 40                            < 40
        // N jets               >= 2                            >= 2
        // pTj2                 > 40                            > 40
        // MET                  > 150                           > 40
        // MET/HTlep            > 2                             > 2
        // pTl2                 > min(10, 2 + mll/3)           > min(10, 2 + mll/3)
        // mTl1                 < 60                           < 60
        // RVBF                 [max(0.6, 0.92-mll/60), 1.0]   [max(0.6, 0.92-mll/60), 1.0]
        // etaj1 . etaj2        < 0                            < 0
        // mjj                  > 400                          > 400
        // Delta etajj          [2,4]                          > 4


        // RVBF variable
        // TODO: This RJ variable has not been coded up in RestFrames format yet
        double RVBF = RISR;

        // mjj variable
        double mjj = 0.;
        if(nSignalVBFJets >= 2) { mjj = (signalVBFJets.at(0)->mom() + signalVBFJets.at(1)->mom()).m(); }

        // Deletaetajj variable
        double Deltaetajj = 0.;
        if(nSignalVBFJets == 2) { Deltaetajj = fabs(signalVBFJets.at(0)->eta() - signalVBFJets.at(1)->eta()); }


        // SR-VBF-low
        // TODO: Lower limit on RVBF differs from paper (max(0.6, 0.92-mll/60))
        //       and cutflow (max(0.6, 0.92-mll/2)), going with cutflow for now
        std::vector<bool> cuts_2l_VBF = { (nSignalVBFJets > 1 && signalVBFJets.at(1)->pT() > 40.),
                                          (met > 200.), // or 150 from paper
                                          (metOverHTlep > 2.),
                                          (nSignalLeptons > 1 && signalLeptons.at(1)->pT() > min(10., 2+mll/3)),
                                          (mTl1 < 60.),
                                          (RVBF <= 1.),
                                          (RVBF >= max(0.6, 0.92-mll/2)), // or mll/60 from paper
                                          (nSignalVBFJets > 1 && signalVBFJets.at(0)->eta() * signalVBFJets.at(1)->eta() < 0),
                                          (mjj > 400),
                                          (Deltaetajj >= 2.)
                                        };
        if (Utils::all_of(preselection_2l_VBF)) { LOG_CUTS_N(cuts_2l_VBF, "SR-VBF-low-", 7) }
        if (Utils::all_of(preselection_2l_VBF) && Utils::all_of(cuts_2l_VBF) && mll < 40. && Deltaetajj <= 4)
         {
           if(mll >= 1 && mll <= 2)         { FILL_SIGNAL_REGION("SR-VBF-low-1") }
           else if(mll >= 2 && mll <= 3)    { FILL_SIGNAL_REGION("SR-VBF-low-2") }
           else if(mll >= 3.2 && mll <= 5)  { FILL_SIGNAL_REGION("SR-VBF-low-3") }
           else if(mll >= 5 && mll <= 10)   { FILL_SIGNAL_REGION("SR-VBF-low-4") }
           else if(mll >= 10 && mll <= 20)  { FILL_SIGNAL_REGION("SR-VBF-low-5") }
           else if(mll >= 20 && mll <= 30)  { FILL_SIGNAL_REGION("SR-VBF-low-6") }
           else if(mll >= 30 && mll <= 40)  { FILL_SIGNAL_REGION("SR-VBF-low-7") }
         }

        // SR-VBF-high
        if (Utils::all_of(preselection_2l_VBF)) { LOG_CUTS_N(cuts_2l_VBF, "SR-VBF-high-", 7) }
        if (Utils::all_of(preselection_2l_VBF) && Utils::all_of(cuts_2l_VBF) && mll < 40. && Deltaetajj > 4.)
         {
           if(mll >= 1 && mll <= 2)         { FILL_SIGNAL_REGION("SR-VBF-high-1") }
           else if(mll >= 2 && mll <= 3)    { FILL_SIGNAL_REGION("SR-VBF-high-2") }
           else if(mll >= 3.2 && mll <= 5)  { FILL_SIGNAL_REGION("SR-VBF-high-3") }
           else if(mll >= 5 && mll <= 10)   { FILL_SIGNAL_REGION("SR-VBF-high-4") }
           else if(mll >= 10 && mll <= 20)  { FILL_SIGNAL_REGION("SR-VBF-high-5") }
           else if(mll >= 20 && mll <= 30)  { FILL_SIGNAL_REGION("SR-VBF-high-6") }
           else if(mll >= 30 && mll <= 40)  { FILL_SIGNAL_REGION("SR-VBF-high-7") }
         }


        // Slepton Signal regions
        // Variable           SR-S-low                     SR-S-high
        // ----------------------------------------------------------------------------------------------
        // MET                [150,200]                       > 200                                      
        // mT2                < 140                           < 140                                      
        // pTl2               > min(15, 7.5+0.75(mT2-100))    > min(20, 2.5+2.5(mT2-100)                 
        // RISR               [0.8, 1.0]                      [max(0.85, 0.98 − 0.02 × (mT2 − 100)), 1.0]

        // mT2 variable
        double mT2100 = 0;
        if(nSignalLeptons > 1)
        {
          double pa[3] = { 0, signalLeptons.at(0)->mom().px(), signalLeptons.at(0)->mom().py() };
          double pb[3] = { 0, signalLeptons.at(1)->mom().px(), signalLeptons.at(1)->mom().py() };
          double pmiss[3] = { 0, ptot.px(), ptot.py() };
          double mn = 100.;

          mt2_bisect::mt2 mt2_calc;
          mt2_calc.set_momenta(pa,pb,pmiss);
          mt2_calc.set_mn(mn);
          mT2100 = mt2_calc.get_mt2();
        }


        // SR-S-low
        std::vector<bool> cuts_2l_s_low = { met >= 150. && met <= 200.,
                                            RISR >= 0.8 && RISR <= 1.0,
                                            nSignalLeptons > 1 &&signalLeptons.at(1)->pT() > min(15., 7.5 + 0.75*(mT2100-100.))
                                          };
        if (Utils::all_of(preselection_2l))
        {
          LOG_CUTS_N(cuts_2l_s_low, "SR-S-low-ee-", 8)
          LOG_CUTS_N(cuts_2l_s_low, "SR-S-low-mumu-", 8)
          LOG_CUTS_N(cuts_2l_s_low, "SR-S-low-combined-", 8)
        }
        if (Utils::all_of(preselection_2l) && Utils::all_of(cuts_2l_s_low))
        {
          if (electron_pair)
          {
            if(mT2100 >= 100 && mT2100 <= 100.5)      { FILL_SIGNAL_REGION("SR-S-low-ee-1") }
            else if(mT2100 >= 100.5 && mT2100 <= 101) { FILL_SIGNAL_REGION("SR-S-low-ee-2") }
            else if(mT2100 >= 101 && mT2100 <= 102)   { FILL_SIGNAL_REGION("SR-S-low-ee-3") }
            else if(mT2100 >= 102 && mT2100 <= 105)   { FILL_SIGNAL_REGION("SR-S-low-ee-4") }
            else if(mT2100 >= 105 && mT2100 <= 110)   { FILL_SIGNAL_REGION("SR-S-low-ee-5") }
            else if(mT2100 >= 110 && mT2100 <= 120)   { FILL_SIGNAL_REGION("SR-S-low-ee-6") }
            else if(mT2100 >= 120 && mT2100 <= 130)   { FILL_SIGNAL_REGION("SR-S-low-ee-7") }
            else if(mT2100 >= 130 && mT2100 <= 140)   { FILL_SIGNAL_REGION("SR-S-low-ee-8") }
          }
          else if (muon_pair)
          {
            if(mT2100 >= 100 && mT2100 <= 100.5)      { FILL_SIGNAL_REGION("SR-S-low-mumu-1") }
            else if(mT2100 >= 100.5 && mT2100 <= 101) { FILL_SIGNAL_REGION("SR-S-low-mumu-2") }
            else if(mT2100 >= 101 && mT2100 <= 102)   { FILL_SIGNAL_REGION("SR-S-low-mumu-3") }
            else if(mT2100 >= 102 && mT2100 <= 105)   { FILL_SIGNAL_REGION("SR-S-low-mumu-4") }
            else if(mT2100 >= 105 && mT2100 <= 110)   { FILL_SIGNAL_REGION("SR-S-low-mumu-5") }
            else if(mT2100 >= 110 && mT2100 <= 120)   { FILL_SIGNAL_REGION("SR-S-low-mumu-6") }
            else if(mT2100 >= 120 && mT2100 <= 130)   { FILL_SIGNAL_REGION("SR-S-low-mumu-7") }
            else if(mT2100 >= 130 && mT2100 <= 140)   { FILL_SIGNAL_REGION("SR-S-low-mumu-8") }
          }
          
          if(mT2100 >= 100 && mT2100 <= 100.5)      { FILL_SIGNAL_REGION("SR-S-low-combined-1") }
          else if(mT2100 >= 100.5 && mT2100 <= 101) { FILL_SIGNAL_REGION("SR-S-low-combined-2") }
          else if(mT2100 >= 101 && mT2100 <= 102)   { FILL_SIGNAL_REGION("SR-S-low-combined-3") }
          else if(mT2100 >= 102 && mT2100 <= 105)   { FILL_SIGNAL_REGION("SR-S-low-combined-4") }
          else if(mT2100 >= 105 && mT2100 <= 110)   { FILL_SIGNAL_REGION("SR-S-low-combined-5") }
          else if(mT2100 >= 110 && mT2100 <= 120)   { FILL_SIGNAL_REGION("SR-S-low-combined-6") }
          else if(mT2100 >= 120 && mT2100 <= 130)   { FILL_SIGNAL_REGION("SR-S-low-combined-7") }
          else if(mT2100 >= 130 && mT2100 <= 140)   { FILL_SIGNAL_REGION("SR-S-low-combined-8") }
        }

        // SR-S-high
        std::vector<bool> cuts_2l_s_high = { met > 200.,
                                             RISR >= max(0.85, 0.98 - 0.02*(mT2100 - 100.)) && RISR <= 1.0,
                                             nSignalLeptons > 1 && signalLeptons.at(1)->pT() > min(20., 2.5+2.5*(mT2100-100.))
                                           };
        if (Utils::all_of(preselection_2l))
        {
          LOG_CUTS_N(cuts_2l_s_high, "SR-S-high-ee-", 8)
          LOG_CUTS_N(cuts_2l_s_high, "SR-S-high-mumu-", 8)
          LOG_CUTS_N(cuts_2l_s_high, "SR-S-high-combined-", 8)
        }
        if (Utils::all_of(preselection_2l) && Utils::all_of(cuts_2l_s_high))
        {
          if (electron_pair)
          {
            if(mT2100 >= 100 && mT2100 <= 100.5)      { FILL_SIGNAL_REGION("SR-S-high-ee-1") }
            else if(mT2100 >= 100.5 && mT2100 <= 101) { FILL_SIGNAL_REGION("SR-S-high-ee-2") }
            else if(mT2100 >= 101 && mT2100 <= 102)   { FILL_SIGNAL_REGION("SR-S-high-ee-3") }
            else if(mT2100 >= 102 && mT2100 <= 105)   { FILL_SIGNAL_REGION("SR-S-high-ee-4") }
            else if(mT2100 >= 105 && mT2100 <= 110)   { FILL_SIGNAL_REGION("SR-S-high-ee-5") }
            else if(mT2100 >= 110 && mT2100 <= 120)   { FILL_SIGNAL_REGION("SR-S-high-ee-6") }
            else if(mT2100 >= 120 && mT2100 <= 130)   { FILL_SIGNAL_REGION("SR-S-high-ee-7") }
            else if(mT2100 >= 130 && mT2100 <= 140)   { FILL_SIGNAL_REGION("SR-S-high-ee-8") }
          }
          else if (muon_pair)
          {
            if(mT2100 >= 100 && mT2100 <= 100.5)      { FILL_SIGNAL_REGION("SR-S-high-mumu-1") }
            else if(mT2100 >= 100.5 && mT2100 <= 101) { FILL_SIGNAL_REGION("SR-S-high-mumu-2") }
            else if(mT2100 >= 101 && mT2100 <= 102)   { FILL_SIGNAL_REGION("SR-S-high-mumu-3") }
            else if(mT2100 >= 102 && mT2100 <= 105)   { FILL_SIGNAL_REGION("SR-S-high-mumu-4") }
            else if(mT2100 >= 105 && mT2100 <= 110)   { FILL_SIGNAL_REGION("SR-S-high-mumu-5") }
            else if(mT2100 >= 110 && mT2100 <= 120)   { FILL_SIGNAL_REGION("SR-S-high-mumu-6") }
            else if(mT2100 >= 120 && mT2100 <= 130)   { FILL_SIGNAL_REGION("SR-S-high-mumu-7") }
            else if(mT2100 >= 130 && mT2100 <= 140)   { FILL_SIGNAL_REGION("SR-S-high-mumu-8") }
          }
          if(mT2100 >= 100 && mT2100 <= 100.5)      { FILL_SIGNAL_REGION("SR-S-high-combined-1") }
          else if(mT2100 >= 100.5 && mT2100 <= 101) { FILL_SIGNAL_REGION("SR-S-high-combined-2") }
          else if(mT2100 >= 101 && mT2100 <= 102)   { FILL_SIGNAL_REGION("SR-S-high-combined-3") }
          else if(mT2100 >= 102 && mT2100 <= 105)   { FILL_SIGNAL_REGION("SR-S-high-combined-4") }
          else if(mT2100 >= 105 && mT2100 <= 110)   { FILL_SIGNAL_REGION("SR-S-high-combined-5") }
          else if(mT2100 >= 110 && mT2100 <= 120)   { FILL_SIGNAL_REGION("SR-S-high-combined-6") }
          else if(mT2100 >= 120 && mT2100 <= 130)   { FILL_SIGNAL_REGION("SR-S-high-combined-7") }
          else if(mT2100 >= 130 && mT2100 <= 140)   { FILL_SIGNAL_REGION("SR-S-high-combined-8") }
        }
      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {
        // SR-E-low observed and background events, from Table 11 of 1911.12606
        COMMIT_SIGNAL_REGION("SR-E-low-ee-1", 7., 5.3, 1.5)
        COMMIT_SIGNAL_REGION("SR-E-low-ee-2", 11., 8.6, 1.8)
        COMMIT_SIGNAL_REGION("SR-E-low-ee-3", 16., 16.7, 2.5)
        COMMIT_SIGNAL_REGION("SR-E-low-ee-4", 16., 15.5, 2.6)
        COMMIT_SIGNAL_REGION("SR-E-low-ee-5", 10., 12.9, 2.1)
        COMMIT_SIGNAL_REGION("SR-E-low-ee-6", 9., 18.8, 2.2)

        COMMIT_SIGNAL_REGION("SR-E-low-mumu-1", 9., 15.4, 2.4)
        COMMIT_SIGNAL_REGION("SR-E-low-mumu-2", 7., 8.0, 1.7)
        COMMIT_SIGNAL_REGION("SR-E-low-mumu-3", 7., 6.5, 1.6)
        COMMIT_SIGNAL_REGION("SR-E-low-mumu-4", 12., 11.3, 1.9)
        COMMIT_SIGNAL_REGION("SR-E-low-mumu-5", 17., 15.6, 2.3)
        COMMIT_SIGNAL_REGION("SR-E-low-mumu-6", 18., 16.7, 2.3)
        COMMIT_SIGNAL_REGION("SR-E-low-mumu-7", 16., 15.3, 2.0)
        COMMIT_SIGNAL_REGION("SR-E-low-mumu-8", 44., 35.9, 3.3)

        COMMIT_SIGNAL_REGION("SR-E-low-combined-1", 9., 15.4, 2.4)
        COMMIT_SIGNAL_REGION("SR-E-low-combined-2", 7., 8.0, 1.7)
        COMMIT_SIGNAL_REGION("SR-E-low-combined-3", 7.+7., 5.3+6.5, sqrt(1.5*1.5 + 1.6*1.6))
        COMMIT_SIGNAL_REGION("SR-E-low-combined-4", 11.+12., 8.6+11.3, sqrt(1.8*1.8 + 1.9*1.9))
        COMMIT_SIGNAL_REGION("SR-E-low-combined-5", 16.+17., 16.7+15.6, sqrt(2.5*2.5 + 2.3*2.3))
        COMMIT_SIGNAL_REGION("SR-E-low-combined-6", 16.+18., 15.5+16.7, sqrt(2.6*2.6 + 2.3*2.3))
        COMMIT_SIGNAL_REGION("SR-E-low-combined-7", 10.+16., 12.9+15.3, sqrt(2.1*2.1 + 2.0*2.0))
        COMMIT_SIGNAL_REGION("SR-E-low-combined-8", 9.+44., 18.8+35.9, sqrt(2.2*2.2 + 3.3*3.3))

        // SR-E-med observed and background events, from Table 11 of 1911.12606
        COMMIT_SIGNAL_REGION("SR-E-med-ee-1", 6., 6.2, 1.9)
        COMMIT_SIGNAL_REGION("SR-E-med-ee-2", 41., 34., 4.)
        COMMIT_SIGNAL_REGION("SR-E-med-ee-3", 59., 52., 6.)
        COMMIT_SIGNAL_REGION("SR-E-med-ee-4", 21., 18.5, 3.2)

        COMMIT_SIGNAL_REGION("SR-E-med-mumu-1", 16., 14.6, 2.9)
        COMMIT_SIGNAL_REGION("SR-E-med-mumu-2", 8., 6.9, 2.1)
        COMMIT_SIGNAL_REGION("SR-E-med-mumu-3", 0., 0.11, 0.08)
        COMMIT_SIGNAL_REGION("SR-E-med-mumu-4", 4., 5.1, 1.6)
        COMMIT_SIGNAL_REGION("SR-E-med-mumu-5", 11., 7.3, 1.9)
        COMMIT_SIGNAL_REGION("SR-E-med-mumu-6", 4., 2.2, 0.9)

        COMMIT_SIGNAL_REGION("SR-E-med-combined-1", 16., 14.6, 2.9)
        COMMIT_SIGNAL_REGION("SR-E-med-combined-2", 8., 6.9, 2.1)
        COMMIT_SIGNAL_REGION("SR-E-med-combined-3", 6.+0., 6.2+0.11, sqrt(1.9*1.9 + 0.08*0.08))
        COMMIT_SIGNAL_REGION("SR-E-med-combined-4", 41.+4., 34.+5.1, sqrt(4.*4. + 1.6*1.6))
        COMMIT_SIGNAL_REGION("SR-E-med-combined-5", 59.+11., 52.+7.3, sqrt(6.*6. + 1.9*1.9))
        COMMIT_SIGNAL_REGION("SR-E-med-combined-6", 21.+4., 18.5+2.2, sqrt(3.2*3.2 + 0.9*0.9))

        // SR-E-high observed and background events, from Table 11 of 1911.12606
        COMMIT_SIGNAL_REGION("SR-E-high-ee-1", 0., 3.9, 1.3 )
        COMMIT_SIGNAL_REGION("SR-E-high-ee-2", 9., 11.0, 2.0)
        COMMIT_SIGNAL_REGION("SR-E-high-ee-3", 23., 17.8, 2.7)
        COMMIT_SIGNAL_REGION("SR-E-high-ee-4", 3., 8.3, 1.4)
        COMMIT_SIGNAL_REGION("SR-E-high-ee-5", 5., 10.1, 1.5)
        COMMIT_SIGNAL_REGION("SR-E-high-ee-6", 20., 19.6, 2.3)

        COMMIT_SIGNAL_REGION("SR-E-high-mumu-1", 5., 3.4, 1.2)
        COMMIT_SIGNAL_REGION("SR-E-high-mumu-2", 5., 3.5, 1.3)
        COMMIT_SIGNAL_REGION("SR-E-high-mumu-3", 1., 0.7, 0.4)
        COMMIT_SIGNAL_REGION("SR-E-high-mumu-4", 16., 10.3, 2.5)
        COMMIT_SIGNAL_REGION("SR-E-high-mumu-5", 13., 12.1, 2.2)
        COMMIT_SIGNAL_REGION("SR-E-high-mumu-6", 8., 10.1, 1.7)
        COMMIT_SIGNAL_REGION("SR-E-high-mumu-7", 8., 10.4, 1.7)
        COMMIT_SIGNAL_REGION("SR-E-high-mumu-8", 18, 19.3, 2.5)

        COMMIT_SIGNAL_REGION("SR-E-high-combined-1", 5., 3.4, 1.2)
        COMMIT_SIGNAL_REGION("SR-E-high-combined-2", 5., 3.5, 1.3)
        COMMIT_SIGNAL_REGION("SR-E-high-combined-3", 0.+1., 3.9+0.7, sqrt(1.3*1.3 + 0.4*0.4))
        COMMIT_SIGNAL_REGION("SR-E-high-combined-4", 9.+16., 11.0+10.3, sqrt(2.0*2.0 + 2.5*2.5))
        COMMIT_SIGNAL_REGION("SR-E-high-combined-5", 23.+13., 17.8+12.1, sqrt(2.7*2.7 + 2.2*2.2))
        COMMIT_SIGNAL_REGION("SR-E-high-combined-6", 3.+8., 8.3+10.1, sqrt(1.4*1.4 + 1.7*1.7))
        COMMIT_SIGNAL_REGION("SR-E-high-combined-7", 5.+8., 10.1+10.4, sqrt(1.5*1.5 + 1.7*1.7))
        COMMIT_SIGNAL_REGION("SR-E-high-combined-8", 20.+18, 19.6+19.3, sqrt(2.3*2.3 + 2.5*2.5))

        // SR-E-1l1T observed and background events, from Table 12 of 1911.12606
        COMMIT_SIGNAL_REGION("SR-E-1l1T-1", 0., 0.5, 0.5)
        COMMIT_SIGNAL_REGION("SR-E-1l1T-2", 8., 6.0, 1.9)
        COMMIT_SIGNAL_REGION("SR-E-1l1T-3", 8., 7.6, 2.1)
        COMMIT_SIGNAL_REGION("SR-E-1l1T-4", 24., 20.7, 3.4)
        COMMIT_SIGNAL_REGION("SR-E-1l1T-5", 24., 14, 4)
        COMMIT_SIGNAL_REGION("SR-E-1l1T-6", 16., 18.1, 3.1)

        // SR-VBF-low observed and background events, from Table 13 of 1911.12606
        COMMIT_SIGNAL_REGION("SR-VBF-low-1", 0., 0.7, 0.4)
        COMMIT_SIGNAL_REGION("SR-VBF-low-2", 0., 0.47, 0.25)
        COMMIT_SIGNAL_REGION("SR-VBF-low-3", 0., 0.64, 0.32)
        COMMIT_SIGNAL_REGION("SR-VBF-low-4", 6., 4.9, 1.2)
        COMMIT_SIGNAL_REGION("SR-VBF-low-5", 21., 17.3, 2.6)
        COMMIT_SIGNAL_REGION("SR-VBF-low-6", 14., 12.5, 1.8)
        COMMIT_SIGNAL_REGION("SR-VBF-low-7", 15., 15.2, 2.7)

        // SR-VBF-high observed and background events, from Table 13 of 1911.12606
        COMMIT_SIGNAL_REGION("SR-VBF-high-1", 0., 1.6, 0.7)
        COMMIT_SIGNAL_REGION("SR-VBF-high-2", 1., 0.8, 0.6)
        COMMIT_SIGNAL_REGION("SR-VBF-high-3", 1., 0.25, 0.13)
        COMMIT_SIGNAL_REGION("SR-VBF-high-4", 1., 0.9, 0.5)
        COMMIT_SIGNAL_REGION("SR-VBF-high-5", 6., 7.1, 1.5)
        COMMIT_SIGNAL_REGION("SR-VBF-high-6", 8., 8.5, 2.2)
        COMMIT_SIGNAL_REGION("SR-VBF-high-7", 9., 7.7, 1.5)

        // SR-S-low observed and background events, from Table 14 of 1911.12606
        // Combined ee and mumu SR data
        COMMIT_SIGNAL_REGION("SR-S-low-ee-1", 8., 6.0, 1.4 )
        COMMIT_SIGNAL_REGION("SR-S-low-ee-2", 5., 5.3, 2.1)
        COMMIT_SIGNAL_REGION("SR-S-low-ee-3", 15., 11.6, 2.5 )
        COMMIT_SIGNAL_REGION("SR-S-low-ee-4", 19., 22.9, 3.3 )
        COMMIT_SIGNAL_REGION("SR-S-low-ee-5", 30., 31., 4. )
        COMMIT_SIGNAL_REGION("SR-S-low-ee-6", 24., 23.3, 3.0 )
        COMMIT_SIGNAL_REGION("SR-S-low-ee-7", 32., 27.1, 3.1 )
        COMMIT_SIGNAL_REGION("SR-S-low-ee-8", 11., 16.8, 2.1 )

        COMMIT_SIGNAL_REGION("SR-S-low-mumu-1", 3., 5.2, 1.1)
        COMMIT_SIGNAL_REGION("SR-S-low-mumu-2", 6., 4.3, 1.0)
        COMMIT_SIGNAL_REGION("SR-S-low-mumu-3", 15., 12.8, 1.8)
        COMMIT_SIGNAL_REGION("SR-S-low-mumu-4", 23., 24.8, 2.6)
        COMMIT_SIGNAL_REGION("SR-S-low-mumu-5", 37., 38., 5.)
        COMMIT_SIGNAL_REGION("SR-S-low-mumu-6", 44., 37.8, 3.3)
        COMMIT_SIGNAL_REGION("SR-S-low-mumu-7", 41., 36.0, 3.4)
        COMMIT_SIGNAL_REGION("SR-S-low-mumu-8", 28., 28.0, 2.7)

        COMMIT_SIGNAL_REGION("SR-S-low-combined-1", 8.+3., 6.0+5.2, sqrt(1.4*1.4 + 1.1*1.1))
        COMMIT_SIGNAL_REGION("SR-S-low-combined-2", 5.+6., 5.3+4.3, sqrt(2.1*2.1 + 1.0*1.0))
        COMMIT_SIGNAL_REGION("SR-S-low-combined-3", 15.+15., 11.6+12.8, sqrt(2.5*2.5 + 1.8*1.8))
        COMMIT_SIGNAL_REGION("SR-S-low-combined-4", 19.+23., 22.9+24.8, sqrt(3.3*3.3 + 2.6*2.6))
        COMMIT_SIGNAL_REGION("SR-S-low-combined-5", 30.+37., 31.+38., sqrt(4.*4. + 5.*5.))
        COMMIT_SIGNAL_REGION("SR-S-low-combined-6", 24.+44., 23.3+37.8, sqrt(3.0*3.0 + 3.3*3.3))
        COMMIT_SIGNAL_REGION("SR-S-low-combined-7", 32.+41., 27.1+36.0, sqrt(3.1*3.1 + 3.4*3.4))
        COMMIT_SIGNAL_REGION("SR-S-low-combined-8", 11.+28., 16.8+28.0, sqrt(2.1*2.1 + 2.7*2.7))

        // SR-S-high observed and background events, from Table 14 of 1911.12606
        // Combined ee and mumu SR data
        COMMIT_SIGNAL_REGION("SR-S-high-ee-1", 3., 4.0, 1.1 )
        COMMIT_SIGNAL_REGION("SR-S-high-ee-2", 3., 3.6, 1.0 )
        COMMIT_SIGNAL_REGION("SR-S-high-ee-3", 9., 7.9, 1.9 )
        COMMIT_SIGNAL_REGION("SR-S-high-ee-4", 13., 13.2, 2.1 )
        COMMIT_SIGNAL_REGION("SR-S-high-ee-5", 9., 8.6, 1.4 )
        COMMIT_SIGNAL_REGION("SR-S-high-ee-6", 6., 5.7, 1.0 )
        COMMIT_SIGNAL_REGION("SR-S-high-ee-7", 8., 7.0, .2 )
        COMMIT_SIGNAL_REGION("SR-S-high-ee-8", 6., 6.8, 1.1 )

        COMMIT_SIGNAL_REGION("SR-S-high-mumu-1", 10., 11.0, 2.2)
        COMMIT_SIGNAL_REGION("SR-S-high-mumu-2", 3., 5.8, 1.3)
        COMMIT_SIGNAL_REGION("SR-S-high-mumu-3", 11., 8.6, 1.6)
        COMMIT_SIGNAL_REGION("SR-S-high-mumu-4", 12., 14.2, 1.9)
        COMMIT_SIGNAL_REGION("SR-S-high-mumu-5", 9., 10.0, 1.5)
        COMMIT_SIGNAL_REGION("SR-S-high-mumu-6", 11., 11.2, 1.6)
        COMMIT_SIGNAL_REGION("SR-S-high-mumu-7", 10., 11.5, 1.5)
        COMMIT_SIGNAL_REGION("SR-S-high-mumu-8", 8., 7.8, 1.4)

        COMMIT_SIGNAL_REGION("SR-S-high-combined-1", 3.+10., 4.0+11.0, sqrt(1.1*1.1 + 2.2*2.2))
        COMMIT_SIGNAL_REGION("SR-S-high-combined-2", 3.+3., 3.6+5.8, sqrt(1.0*1.0 + 1.3*1.3))
        COMMIT_SIGNAL_REGION("SR-S-high-combined-3", 9.+11., 7.9+8.6, sqrt(1.9*1.9 + 1.6*1.6))
        COMMIT_SIGNAL_REGION("SR-S-high-combined-4", 13.+12., 13.2+14.2, sqrt(2.1*2.1 + 1.9*1.9))
        COMMIT_SIGNAL_REGION("SR-S-high-combined-5", 9.+9., 8.6+10.0, sqrt(1.4*1.4 + 1.5*1.5))
        COMMIT_SIGNAL_REGION("SR-S-high-combined-6", 6.+11., 5.7+11.2, sqrt(1.0*1.0 + 1.6*1.6))
        COMMIT_SIGNAL_REGION("SR-S-high-combined-7", 8.+10., 7.0+11.5, sqrt(.2*.2 + 1.5*1.5))
        COMMIT_SIGNAL_REGION("SR-S-high-combined-8", 6.+8., 6.8+7.8, sqrt(1.1*1.1 + 1.4*1.4))

        COMMIT_CUTFLOWS
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2018_16)


    // Derived analysis that does not combine ee and mu mu signal regions
    class Analysis_ATLAS_SUSY_2018_16_exclusive : public Analysis_ATLAS_SUSY_2018_16
    {

      public:

        Analysis_ATLAS_SUSY_2018_16_exclusive()
        {
          set_analysis_name("ATLAS_SUSY_2018_16_exclusive");
        }

        virtual void collect_results()
        {
          // SR-E-low observed and background events, from Table 11 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-E-low-ee-1", 7., 5.3, 1.5)
          COMMIT_SIGNAL_REGION("SR-E-low-ee-2", 11., 8.6, 1.8)
          COMMIT_SIGNAL_REGION("SR-E-low-ee-3", 16., 16.7, 2.5)
          COMMIT_SIGNAL_REGION("SR-E-low-ee-4", 16., 15.5, 2.6)
          COMMIT_SIGNAL_REGION("SR-E-low-ee-5", 10., 12.9, 2.1)
          COMMIT_SIGNAL_REGION("SR-E-low-ee-6", 9., 18.8, 2.2)

          COMMIT_SIGNAL_REGION("SR-E-low-mumu-1", 9., 15.4, 2.4)
          COMMIT_SIGNAL_REGION("SR-E-low-mumu-2", 7., 8.0, 1.7)
          COMMIT_SIGNAL_REGION("SR-E-low-mumu-3", 7., 6.5, 1.6)
          COMMIT_SIGNAL_REGION("SR-E-low-mumu-4", 12., 11.3, 1.9)
          COMMIT_SIGNAL_REGION("SR-E-low-mumu-5", 17., 15.6, 2.3)
          COMMIT_SIGNAL_REGION("SR-E-low-mumu-6", 18., 16.7, 2.3)
          COMMIT_SIGNAL_REGION("SR-E-low-mumu-7", 16., 15.3, 2.0)
          COMMIT_SIGNAL_REGION("SR-E-low-mumu-8", 44., 35.9, 3.3)

          // SR-E-med observed and background events, from Table 11 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-E-med-ee-1", 6., 6.2, 1.9)
          COMMIT_SIGNAL_REGION("SR-E-med-ee-2", 41., 34., 4.)
          COMMIT_SIGNAL_REGION("SR-E-med-ee-3", 59., 52., 6.)
          COMMIT_SIGNAL_REGION("SR-E-med-ee-4", 21., 18.5, 3.2)

          COMMIT_SIGNAL_REGION("SR-E-med-mumu-1", 16., 14.6, 2.9)
          COMMIT_SIGNAL_REGION("SR-E-med-mumu-2", 8., 6.9, 2.1)
          COMMIT_SIGNAL_REGION("SR-E-med-mumu-3", 0., 0.11, 0.08)
          COMMIT_SIGNAL_REGION("SR-E-med-mumu-4", 4., 5.1, 1.6)
          COMMIT_SIGNAL_REGION("SR-E-med-mumu-5", 11., 7.3, 1.9)
          COMMIT_SIGNAL_REGION("SR-E-med-mumu-6", 4., 2.2, 0.9)

          // SR-E-high observed and background events, from Table 11 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-E-high-ee-1", 0., 3.9, 1.3 )
          COMMIT_SIGNAL_REGION("SR-E-high-ee-2", 9., 11.0, 2.0)
          COMMIT_SIGNAL_REGION("SR-E-high-ee-3", 23., 17.8, 2.7)
          COMMIT_SIGNAL_REGION("SR-E-high-ee-4", 3., 8.3, 1.4)
          COMMIT_SIGNAL_REGION("SR-E-high-ee-5", 5., 10.1, 1.5)
          COMMIT_SIGNAL_REGION("SR-E-high-ee-6", 20., 19.6, 2.3)

          COMMIT_SIGNAL_REGION("SR-E-high-mumu-1", 5., 3.4, 1.2)
          COMMIT_SIGNAL_REGION("SR-E-high-mumu-2", 5., 3.5, 1.3)
          COMMIT_SIGNAL_REGION("SR-E-high-mumu-3", 1., 0.7, 0.4)
          COMMIT_SIGNAL_REGION("SR-E-high-mumu-4", 16., 10.3, 2.5)
          COMMIT_SIGNAL_REGION("SR-E-high-mumu-5", 13., 12.1, 2.2)
          COMMIT_SIGNAL_REGION("SR-E-high-mumu-6", 8., 10.1, 1.7)
          COMMIT_SIGNAL_REGION("SR-E-high-mumu-7", 8., 10.4, 1.7)
          COMMIT_SIGNAL_REGION("SR-E-high-mumu-8", 18, 19.3, 2.5)

          // SR-E-1l1T observed and background events, from Table 12 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-E-1l1T-1", 0., 0.5, 0.5)
          COMMIT_SIGNAL_REGION("SR-E-1l1T-2", 8., 6.0, 1.9)
          COMMIT_SIGNAL_REGION("SR-E-1l1T-3", 8., 7.6, 2.1)
          COMMIT_SIGNAL_REGION("SR-E-1l1T-4", 24., 20.7, 3.4)
          COMMIT_SIGNAL_REGION("SR-E-1l1T-5", 24., 14, 4)
          COMMIT_SIGNAL_REGION("SR-E-1l1T-6", 16., 18.1, 3.1)

          // SR-VBF-low observed and background events, from Table 13 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-VBF-low-1", 0., 0.7, 0.4)
          COMMIT_SIGNAL_REGION("SR-VBF-low-2", 0., 0.47, 0.25)
          COMMIT_SIGNAL_REGION("SR-VBF-low-3", 0., 0.64, 0.32)
          COMMIT_SIGNAL_REGION("SR-VBF-low-4", 6., 4.9, 1.2)
          COMMIT_SIGNAL_REGION("SR-VBF-low-5", 21., 17.3, 2.6)
          COMMIT_SIGNAL_REGION("SR-VBF-low-6", 14., 12.5, 1.8)
          COMMIT_SIGNAL_REGION("SR-VBF-low-7", 15., 15.2, 2.7)

          // SR-VBF-high observed and background events, from Table 13 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-VBF-high-1", 0., 1.6, 0.7)
          COMMIT_SIGNAL_REGION("SR-VBF-high-2", 1., 0.8, 0.6)
          COMMIT_SIGNAL_REGION("SR-VBF-high-3", 1., 0.25, 0.13)
          COMMIT_SIGNAL_REGION("SR-VBF-high-4", 1., 0.9, 0.5)
          COMMIT_SIGNAL_REGION("SR-VBF-high-5", 6., 7.1, 1.5)
          COMMIT_SIGNAL_REGION("SR-VBF-high-6", 8., 8.5, 2.2)
          COMMIT_SIGNAL_REGION("SR-VBF-high-7", 9., 7.7, 1.5)

          // SR-S-low observed and background events, from Table 14 of 1911.12606
          // Combined ee and mumu SR data
          COMMIT_SIGNAL_REGION("SR-S-low-ee-1", 8., 6.0, 1.4 )
          COMMIT_SIGNAL_REGION("SR-S-low-ee-2", 5., 5.3, 2.1)
          COMMIT_SIGNAL_REGION("SR-S-low-ee-3", 15., 11.6, 2.5 )
          COMMIT_SIGNAL_REGION("SR-S-low-ee-4", 19., 22.9, 3.3 )
          COMMIT_SIGNAL_REGION("SR-S-low-ee-5", 30., 31., 4. )
          COMMIT_SIGNAL_REGION("SR-S-low-ee-6", 24., 23.3, 3.0 )
          COMMIT_SIGNAL_REGION("SR-S-low-ee-7", 32., 27.1, 3.1 )
          COMMIT_SIGNAL_REGION("SR-S-low-ee-8", 11., 16.8, 2.1 )

          COMMIT_SIGNAL_REGION("SR-S-low-mumu-1", 3., 5.2, 1.1)
          COMMIT_SIGNAL_REGION("SR-S-low-mumu-2", 6., 4.3, 1.0)
          COMMIT_SIGNAL_REGION("SR-S-low-mumu-3", 15., 12.8, 1.8)
          COMMIT_SIGNAL_REGION("SR-S-low-mumu-4", 23., 24.8, 2.6)
          COMMIT_SIGNAL_REGION("SR-S-low-mumu-5", 37., 38., 5.)
          COMMIT_SIGNAL_REGION("SR-S-low-mumu-6", 44., 37.8, 3.3)
          COMMIT_SIGNAL_REGION("SR-S-low-mumu-7", 41., 36.0, 3.4)
          COMMIT_SIGNAL_REGION("SR-S-low-mumu-8", 28., 28.0, 2.7)

          // SR-S-high observed and background events, from Table 14 of 1911.12606
          // Combined ee and mumu SR data
          COMMIT_SIGNAL_REGION("SR-S-high-ee-1", 3., 4.0, 1.1 )
          COMMIT_SIGNAL_REGION("SR-S-high-ee-2", 3., 3.6, 1.0 )
          COMMIT_SIGNAL_REGION("SR-S-high-ee-3", 9., 7.9, 1.9 )
          COMMIT_SIGNAL_REGION("SR-S-high-ee-4", 13., 13.2, 2.1 )
          COMMIT_SIGNAL_REGION("SR-S-high-ee-5", 9., 8.6, 1.4 )
          COMMIT_SIGNAL_REGION("SR-S-high-ee-6", 6., 5.7, 1.0 )
          COMMIT_SIGNAL_REGION("SR-S-high-ee-7", 8., 7.0, .2 )
          COMMIT_SIGNAL_REGION("SR-S-high-ee-8", 6., 6.8, 1.1 )

          COMMIT_SIGNAL_REGION("SR-S-high-mumu-1", 10., 11.0, 2.2)
          COMMIT_SIGNAL_REGION("SR-S-high-mumu-2", 3., 5.8, 1.3)
          COMMIT_SIGNAL_REGION("SR-S-high-mumu-3", 11., 8.6, 1.6)
          COMMIT_SIGNAL_REGION("SR-S-high-mumu-4", 12., 14.2, 1.9)
          COMMIT_SIGNAL_REGION("SR-S-high-mumu-5", 9., 10.0, 1.5)
          COMMIT_SIGNAL_REGION("SR-S-high-mumu-6", 11., 11.2, 1.6)
          COMMIT_SIGNAL_REGION("SR-S-high-mumu-7", 10., 11.5, 1.5)
          COMMIT_SIGNAL_REGION("SR-S-high-mumu-8", 8., 7.8, 1.4)

          COMMIT_CUTFLOWS
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2018_16_exclusive)


    // Derived analysis that combines ee and mu mu signal regions
    class Analysis_ATLAS_SUSY_2018_16_combined : public Analysis_ATLAS_SUSY_2018_16
    {

      public:

        Analysis_ATLAS_SUSY_2018_16_combined()
        {
          set_analysis_name("ATLAS_SUSY_2018_16_combined");
        }

        virtual void collect_results()
        {
          // SR-E-low observed and background events, from Table 11 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-E-low-combined-1", 9., 15.4, 2.4)
          COMMIT_SIGNAL_REGION("SR-E-low-combined-2", 7., 8.0, 1.7)
          COMMIT_SIGNAL_REGION("SR-E-low-combined-3", 7.+7., 5.3+6.5, sqrt(1.5*1.5 + 1.6*1.6))
          COMMIT_SIGNAL_REGION("SR-E-low-combined-4", 11.+12., 8.6+11.3, sqrt(1.8*1.8 + 1.9*1.9))
          COMMIT_SIGNAL_REGION("SR-E-low-combined-5", 16.+17., 16.7+15.6, sqrt(2.5*2.5 + 2.3*2.3))
          COMMIT_SIGNAL_REGION("SR-E-low-combined-6", 16.+18., 15.5+16.7, sqrt(2.6*2.6 + 2.3*2.3))
          COMMIT_SIGNAL_REGION("SR-E-low-combined-7", 10.+16., 12.9+15.3, sqrt(2.1*2.1 + 2.0*2.0))
          COMMIT_SIGNAL_REGION("SR-E-low-combined-8", 9.+44., 18.8+35.9, sqrt(2.2*2.2 + 3.3*3.3))

          // SR-E-med observed and background events, from Table 11 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-E-med-combined-1", 16., 14.6, 2.9)
          COMMIT_SIGNAL_REGION("SR-E-med-combined-2", 8., 6.9, 2.1)
          COMMIT_SIGNAL_REGION("SR-E-med-combined-3", 6.+0., 6.2+0.11, sqrt(1.9*1.9 + 0.08*0.08))
          COMMIT_SIGNAL_REGION("SR-E-med-combined-4", 41.+4., 34.+5.1, sqrt(4.*4. + 1.6*1.6))
          COMMIT_SIGNAL_REGION("SR-E-med-combined-5", 59.+11., 52.+7.3, sqrt(6.*6. + 1.9*1.9))
          COMMIT_SIGNAL_REGION("SR-E-med-combined-6", 21.+4., 18.5+2.2, sqrt(3.2*3.2 + 0.9*0.9))

          // SR-E-high observed and background events, from Table 11 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-E-high-combined-1", 5., 3.4, 1.2)
          COMMIT_SIGNAL_REGION("SR-E-high-combined-2", 5., 3.5, 1.3)
          COMMIT_SIGNAL_REGION("SR-E-high-combined-3", 0.+1., 3.9+0.7, sqrt(1.3*1.3 + 0.4*0.4))
          COMMIT_SIGNAL_REGION("SR-E-high-combined-4", 9.+16., 11.0+10.3, sqrt(2.0*2.0 + 2.5*2.5))
          COMMIT_SIGNAL_REGION("SR-E-high-combined-5", 23.+13., 17.8+12.1, sqrt(2.7*2.7 + 2.2*2.2))
          COMMIT_SIGNAL_REGION("SR-E-high-combined-6", 3.+8., 8.3+10.1, sqrt(1.4*1.4 + 1.7*1.7))
          COMMIT_SIGNAL_REGION("SR-E-high-combined-7", 5.+8., 10.1+10.4, sqrt(1.5*1.5 + 1.7*1.7))
          COMMIT_SIGNAL_REGION("SR-E-high-combined-8", 20.+18, 19.6+19.3, sqrt(2.3*2.3 + 2.5*2.5))

          // SR-E-1l1T observed and background events, from Table 12 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-E-1l1T-1", 0., 0.5, 0.5)
          COMMIT_SIGNAL_REGION("SR-E-1l1T-2", 8., 6.0, 1.9)
          COMMIT_SIGNAL_REGION("SR-E-1l1T-3", 8., 7.6, 2.1)
          COMMIT_SIGNAL_REGION("SR-E-1l1T-4", 24., 20.7, 3.4)
          COMMIT_SIGNAL_REGION("SR-E-1l1T-5", 24., 14, 4)
          COMMIT_SIGNAL_REGION("SR-E-1l1T-6", 16., 18.1, 3.1)

          // SR-VBF-low observed and background events, from Table 13 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-VBF-low-1", 0., 0.7, 0.4)
          COMMIT_SIGNAL_REGION("SR-VBF-low-2", 0., 0.47, 0.25)
          COMMIT_SIGNAL_REGION("SR-VBF-low-3", 0., 0.64, 0.32)
          COMMIT_SIGNAL_REGION("SR-VBF-low-4", 6., 4.9, 1.2)
          COMMIT_SIGNAL_REGION("SR-VBF-low-5", 21., 17.3, 2.6)
          COMMIT_SIGNAL_REGION("SR-VBF-low-6", 14., 12.5, 1.8)
          COMMIT_SIGNAL_REGION("SR-VBF-low-7", 15., 15.2, 2.7)

          // SR-VBF-high observed and background events, from Table 13 of 1911.12606
          COMMIT_SIGNAL_REGION("SR-VBF-high-1", 0., 1.6, 0.7)
          COMMIT_SIGNAL_REGION("SR-VBF-high-2", 1., 0.8, 0.6)
          COMMIT_SIGNAL_REGION("SR-VBF-high-3", 1., 0.25, 0.13)
          COMMIT_SIGNAL_REGION("SR-VBF-high-4", 1., 0.9, 0.5)
          COMMIT_SIGNAL_REGION("SR-VBF-high-5", 6., 7.1, 1.5)
          COMMIT_SIGNAL_REGION("SR-VBF-high-6", 8., 8.5, 2.2)
          COMMIT_SIGNAL_REGION("SR-VBF-high-7", 9., 7.7, 1.5)

          // SR-S-low observed and background events, from Table 14 of 1911.12606
          // Combined ee and mumu SR data
          COMMIT_SIGNAL_REGION("SR-S-low-combined-1", 8.+3., 6.0+5.2, sqrt(1.4*1.4 + 1.1*1.1))
          COMMIT_SIGNAL_REGION("SR-S-low-combined-2", 5.+6., 5.3+4.3, sqrt(2.1*2.1 + 1.0*1.0))
          COMMIT_SIGNAL_REGION("SR-S-low-combined-3", 15.+15., 11.6+12.8, sqrt(2.5*2.5 + 1.8*1.8))
          COMMIT_SIGNAL_REGION("SR-S-low-combined-4", 19.+23., 22.9+24.8, sqrt(3.3*3.3 + 2.6*2.6))
          COMMIT_SIGNAL_REGION("SR-S-low-combined-5", 30.+37., 31.+38., sqrt(4.*4. + 5.*5.))
          COMMIT_SIGNAL_REGION("SR-S-low-combined-6", 24.+44., 23.3+37.8, sqrt(3.0*3.0 + 3.3*3.3))
          COMMIT_SIGNAL_REGION("SR-S-low-combined-7", 32.+41., 27.1+36.0, sqrt(3.1*3.1 + 3.4*3.4))
          COMMIT_SIGNAL_REGION("SR-S-low-combined-8", 11.+28., 16.8+28.0, sqrt(2.1*2.1 + 2.7*2.7))

          // SR-S-high observed and background events, from Table 14 of 1911.12606
          // Combined ee and mumu SR data
          COMMIT_SIGNAL_REGION("SR-S-high-combined-1", 3.+10., 4.0+11.0, sqrt(1.1*1.1 + 2.2*2.2))
          COMMIT_SIGNAL_REGION("SR-S-high-combined-2", 3.+3., 3.6+5.8, sqrt(1.0*1.0 + 1.3*1.3))
          COMMIT_SIGNAL_REGION("SR-S-high-combined-3", 9.+11., 7.9+8.6, sqrt(1.9*1.9 + 1.6*1.6))
          COMMIT_SIGNAL_REGION("SR-S-high-combined-4", 13.+12., 13.2+14.2, sqrt(2.1*2.1 + 1.9*1.9))
          COMMIT_SIGNAL_REGION("SR-S-high-combined-5", 9.+9., 8.6+10.0, sqrt(1.4*1.4 + 1.5*1.5))
          COMMIT_SIGNAL_REGION("SR-S-high-combined-6", 6.+11., 5.7+11.2, sqrt(1.0*1.0 + 1.6*1.6))
          COMMIT_SIGNAL_REGION("SR-S-high-combined-7", 8.+10., 7.0+11.5, sqrt(.2*.2 + 1.5*1.5))
          COMMIT_SIGNAL_REGION("SR-S-high-combined-8", 6.+8., 6.8+7.8, sqrt(1.1*1.1 + 1.4*1.4))

          COMMIT_CUTFLOWS
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2018_16_combined)

  }
}
#endif
#endif
