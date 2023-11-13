///
///  \author Tomas Gonzalo
///  \date 2019 June
///  \date 2023 Sep
///
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2019-014/
// Updated by the published paper SUSY-2018-16, https://arxiv.org/abs/1911.12606

// - 139 fb^-1 data

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

 #define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_2LEPsoft_139invfb : public Analysis
    {

    private:

//      struct ptComparison
//      {
//        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
//      } comparePt;

//      struct ptJetComparison
//      {
//        bool operator() (HEPUtils::Jet* i,HEPUtils::Jet* j) {return (i->pT()>j->pT());}
//      } compareJetPt;


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_2LEPsoft_139invfb()
      {

        DEFINE_SIGNAL_REGIONS("SR-E-low-", 8, "MET trigger", "2 leptons", "veto 3GeV < mll < 3.2GeV", "lepton author 16 veto", "min(Deltaphi(any jet)) > 0.4", "Deltaphi(j1) > 2.0", "lepton truth matching", "1<mll < 60 GeV", "DeltaRee > 0.3, DeltaRmumu > 0.05, DeltaRemu > 0.2", "leading lepton pT > 5GeV", "number of jets > 1", "leading jet pT > 100GeV", "number of b-tagged jets = 0", "mtautau < 0 or > 160 GeV", "ee or mumu", "120 < met < 200 GeV", "met/HTlep < 10", "0.8 < RISR < 1.0", "subleading lepton pT > min(5+mll/4)", "10 < mTl1 < 60 GeV")
        DEFINE_SIGNAL_REGION("SR-E-med-")
        DEFINE_SIGNAL_REGION("SR-E-high-")
        DEFINE_SIGNAL_REGION("SR-E-1l1T-")
        DEFINE_SIGNAL_REGION("SR-S-low-")
        DEFINE_SIGNAL_REGION("SR-S-high-")
        DEFINE_SIGNAL_REGION("SR-VBF-")

        set_analysis_name("ATLAS_13TeV_2LEPsoft_139invfb");
        set_luminosity(139);
      }

      void run(const HEPUtils::Event* event)
      {

        // Preselected objects
        std::vector<const HEPUtils::Particle*> preselectedTracks; // This corresponds to low pT electrons and muons
        std::vector<const HEPUtils::Jet*> preselectedJets;
        std::vector<const HEPUtils::Jet*> preselectedBJets;
        std::vector<const HEPUtils::Jet*> preselectedNonBJets;

        // Missing momentum and energy
        double met = event->met();
        HEPUtils::P4 ptot = event->missingmom();


        // TODO: Candidate events are required to have at least one reconstructed pp interaction vertex with a minimum of two associated tracks with pT > 500 MeV
        // TODO: In events with multiple vertices, the primary vertex is defined as the one with the highest sum pT^2 of associated tracks.
        // Missing: We cannot reject events with detector noise or non-collision backgrounds.

        // Electrons are required to have pT > 4.5 GeV and |η| < 2.47.
        // Preselected tracks with pT > 500 MeV and η < 2.5
        BASELINE_PARTICLES(electrons, preselectedElectrons, 4.5, 0, DBL_MAX, 2.47, ATLAS::eff2DEl.at(""))
        BASELINE_PARTICLES(muons, preselectedMuons, 3.0, 0, DBL_MAX, 2.5, ATLAS::eff2DMu.at(""))

        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 4.5 && electron->abseta() < 2.47)  preselectedElectrons.push_back(electron);
          else if (electron->pT() > 0.5 && electron->abseta() < 2.5) preselectedTracks.push_back(electron);
        }

        // Preselected electrons are further required to pass the calorimeter- and tracking-based VeryLoose likelihood identification (arXiv:1902.04655), and to have a longitudinal impact parameter z0 relative to the primary vertex that satisfies |z0 sin θ| < 0.5 mm.
        // Missing: We cannot add cuts relating to impact parameters

        // Apply electron efficiency
        // TODO: Is this needed if below is done
        applyEfficiency(preselectedElectrons, ATLAS::eff2DEl.at("Generic"));

        // TODO: This is not the same as in the reference. Need the VeryLoose efficiency
        applyEfficiency(preselectedElectrons, ATLAS::eff2DEl.at("ATLAS_PHYS_PUB_2015_041_Loose"));

        // Muons are required to satisfy pT > 3 GeV and |η| < 2.5.
        // Preselected tracks with pT > 500 MeV and η < 2.5
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 3.0 && muon->abseta() > 2.5) preselectedMuons.push_back(muon);
          else if (muon->pT() > 0.5 && muon->abseta() > 2.5) preselectedTracks.push_back(muon);
        }

        // Preselected muons are identified using the LowPt criterion, a re-optimised selection similar to those defined in (arXiv:1603.05598) but with improved signal efficiency and background rejection for pT < 10 GeV muon candidates. Preselected muons must also satisfy |z0 sin θ| < 0.5 mm
        // Missing: No impact parameter info

        // Apply muon efficiency
        // TODO: Is this needed if below is done
        applyEfficiency(preselectedMuons, ATLAS::eff2DMu.at("Generic"));

        // TODO Apply "LowPt" muon ID criteria. This is missing from (arXiv:1603.05598)

        // TODO: Apply "Tight-Primary" working point efficiencies to tracks (ATL-PHYS-PUB-2015-018)

        // Preselected jets are reconstructed from calorimeter topological energy clusters in the region |η| < 4.5 using the anti-kt algorithm with radius parameter R = 0.4. The jets are required to have pT > 20 GeV after being calibrated in accord with Ref. [92] and having the expected energy contribution from pileup subtracted according to the jet area.
        // In order to suppress jets due to pileup, jets with pT < 120 GeV and |η| < 2.5 are required to satisfy the Medium working point of the jet vertex tagger [93], which uses information from the tracks associated to the jet.
        // Missing : no track info
        for (const HEPUtils::Jet* jet : event->jets())
        {
          if (jet->abseta() < 4.5 && jet->pT() > 20.) preselectedJets.push_back(jet);
        }

        // B-tagged jets, are identified from preselected jets within |η| < 2.5. The pT > 20 GeV requirement is maintained to maximise the rejection of the tt¯ background. The b-tagging algorithm working point is chosen so that b-jets from simulated tt¯ events are identified with an 85% efficiency, with rejection factors of 3 for charm-quark jets and 34 for light-quark and gluon jets.
        double btag = 0.85; double cmisstag = 1/3.; double misstag = 1/34.;
        for (const HEPUtils::Jet* jet : preselectedJets)
        {
          if (jet->btag() && jet->abseta() < 2.5 && random_bool(btag) ) preselectedBJets.push_back(jet);
          else if (jet->ctag() && random_bool(cmisstag) ) preselectedBJets.push_back(jet);
          else if (random_bool(misstag)) preselectedBJets.push_back(jet);
          else preselectedNonBJets.push_back(jet);
        }

        // Non-b-tagged jets that are separated from the remaining electrons by ∆Ry < 0.2 are removed
        // Using rapidity instead of pseudorapidity
        // TODO: Should this be done for preselected or signal electrons?
        removeOverlap(preselectedNonBJets, preselectedElectrons, 0.2, true);

        // Jets containing a muon candidate within ∆Ry < 0.4 and with fewer than three tracks with pT > 500 MeV are removed to suppress muon bremsstrahlung.
        // Using rapidity instead of pseudorapidity
        // Do this for both on b-tagged and non-b-tagged jets
        // Missing: We have no information about internal jet tracks
        // TODO: Should this be done for preselected or signal muons?
        removeOverlap(preselectedBJets, preselectedMuons, 0.4, true);
        removeOverlap(preselectedNonBJets, preselectedMuons, 0.4, true);

        // Electrons or muons with ∆Ry < 0.4 from surviving jet candidates are removed to suppress bottom and charm hadron decays
        // Do this for both b-tagged and non-b-tagged jets
        removeOverlap(preselectedElectrons, preselectedNonBJets, 0.4);
        removeOverlap(preselectedMuons, preselectedNonBJets, 0.4);
        removeOverlap(preselectedElectrons, preselectedBJets, 0.4);
        removeOverlap(preselectedMuons, preselectedBJets, 0.4);

        // Signal tracks must also satisfy dedicated isolation criteria – they are required to be separated from preselected jets by at least ∆R > 0.5
        removeOverlap(preselectedTracks, preselectedNonBJets, 0.5);
        removeOverlap(preselectedTracks, preselectedBJets, 0.5);

        // Missing: Cuts on signal tracks
        // The efficiency of selecting signal tracks for the studied electroweakino signals is 20% for electrons with 3 < pT < 4 GeV and 35% for muons with 2 < pT < 3 GeV.
        // TODO: Should we just apply an efficiency cut of 20% on electrons and 35% on muons?

        //***************
        // Signal objects
        std::vector<const HEPUtils::Particle*> signalElectrons = preselectedElectrons;
        std::vector<const HEPUtils::Particle*> signalMuons = preselectedMuons;
        std::vector<const HEPUtils::Jet*> signalJets, signalBJets;
        std::vector<const HEPUtils::Particle*> signalLeptons, signalTracks;

        // Signal electrons must satisfy the Medium identification criterion (arXiv:1902.04655), and be compatible with originating from the primary vertex, with the significance of the transverse impact parameter defined relative to the beam position satisfying |d0|/σ(d0) < 5.
        // Signal electrons are further refined using the Gradient isolation working point (arXiv:1902.04655), which uses both tracking and calorimeter information.
        // Missing: No impact parameter info
        // TODO: Isolation?
        // TODO: Outdated efficiency selection, use newer one (arXiv:1902.04655)
        applyEfficiency(signalElectrons, ATLAS::eff2DEl.at("ATLAS_PHYS_PUB_2015_041_Medium"));

        // Signal muons are required to pass the FCTightTrackOnly isolation working point, which uses only tracking information.
        // Missing: No tracking information

        // After all lepton selection criteria are applied, the efficiency for reconstructing and identifying signal electrons within the detector acceptance in the Higgsino and slepton signal samples ranges from 20% for pT = 4.5 GeV to over 75% for pT > 30 GeV. The corresponding efficiency for signal muons ranges from approximately 50% at pT = 3 GeV to 90% for pT > 30 GeV
        // TODO: maybe use this to avoid efficiency cuts above

        // Signal jets are selected if they satisfy pT > 30 GeV and |η| < 2.8.
        for (const HEPUtils::Jet* jet : preselectedNonBJets)
        {
          if (jet->pT() > 30. && jet->abseta() < 2.8) signalJets.push_back(jet);
        }
        for (const HEPUtils::Jet* jet : preselectedBJets)
        {
          if (jet->pT() > 30. && jet->abseta() < 2.8)
          {
            signalJets.push_back(jet);
            signalBJets.push_back(jet);
          }
        }

        // The sum pT of preselected tracks within ∆R < 0.3 of signal tracks, excluding the contributions from nearby leptons, is required to be smaller than 0.5 GeV.
        // Finally, signal tracks must satisfy pT > 1 GeV, |z0 sin θ| < 0.5 mm and |d0|/σ(d0) < 3.
        // Mising: cannot do impact parameter cuts
        // The efficiency of selecting signal tracks for the studied electroweakino signals is 20% for electrons with 3 < pT < 4 GeV and 35% for muons with 2 < pT < 3 GeV.
        for (const HEPUtils::Particle* track1 : preselectedTracks)
        {
          double pTSum = 0;
          for (const HEPUtils::Particle* track2 : preselectedTracks)
          {
            if (track2 != track1 && track1->mom().deltaR_eta(track2->mom()) < 0.3)
              pTSum += track2->pT();
          }
          double track_el_eff = 0.2, track_mu_eff = 0.35;
          if (pTSum < 0.5 && track1->pT() > 1. &&
             ( ( track1->isElectron() && (track1->pT() <= 3. || track1->pT() >= 4.) && random_bool(track_el_eff) ) ||
               ( track1->isMuon() && (track1->pT() <= 2. || track1->pT() >= 3.) && random_bool(track_mu_eff)  ) ) )
            signalTracks.push_back(track1);

        }

        // Fill signal leptons
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Sort by pT
        sortByPt(signalJets);
        sortByPt(signalBJets);
        sortByPt(signalLeptons);
        sortByPt(signalTracks);

        // Preselection requirements
        // Variable            2l                                              1l1T
        // ------------------------------------------------------------------------------
        // n-leptons           =2                                          =1 l + >=1 T        // done
        // lepton-1  pT        > 5                                          < 10               // done
        // Delta Rll           DRee > 0.3, DRmm > 0.05, DRem > 0.2      0.05 < DRlT < 1.5      // done
        // Charge/Flav         e+- e-+ or mu+- mu-+                     e+- e-+ or mu+- mu-+   // done
        // Inv mass            3 < mee < 60,  1 < mmumu < 60               0.5 < mlT < 5       // done
        // J/psi inv mass      veto 3 < mll < 3.2                         veto 3 < mlT < 3.2   // done
        // mtt                 < 0 or > 160                                     -              // TODO
        // MET                 > 120                                          > 120            // done
        // n-jets              >= 1                                           >= 1             // done
        // n-b-tagged-jets     = 0                                              -              // done
        // leading jet pT      > 100                                         > 100             // done
        // min(Dphi(j,ptmiss)  > 0.4                                         > 0.4             // done
        // Dphi(j1,ptmiss)     >= 2.0                                        >= 2.0            // done

        // Count signal leptons and jets
        size_t nSignalLeptons = signalLeptons.size();
        size_t nSignalJets = signalJets.size();
        size_t nSignalBJets = signalBJets.size();
        size_t nSignalTracks = signalTracks.size();

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
        else
          return ;

        // DeltaR
        double deltaR = signalParticles.at(0)->mom().deltaR_eta(signalParticles.at(1)->mom());

        // ID
        bool electron_pair = signalParticles.at(0)->isElectron() && signalParticles.at(1)->isElectron();
        bool muon_pair = signalParticles.at(0)->isMuon() && signalParticles.at(1)->isMuon();

        // SFOS
        bool SFOS = signalParticles.at(0)->abspid() == signalParticles.at(1)->abspid() && signalParticles.at(0)->pid() != signalParticles.at(0)->pid();

        // Invariant mass
        double mll = (signalParticles.at(0)->mom() + signalParticles.at(1)->mom() ).m();

        // mtautau
        double mtautau_eff = 0.8;

        // DeltaPhi
        double minPhi = 0.;
        for(const HEPUtils::Jet *jet : signalJets)
        {
          if(minPhi > fabs(jet->phi() - ptot.phi()))
            minPhi = fabs(jet->phi() - ptot.phi());
        }

        // Preselection cuts for 2l regions
        bool preselection_2l = (nSignalLeptons == 2) &&
                               (signalLeptons.at(0)->pT() > 5.) &&
                               (deltaR > (electron_pair ? 0.3 : (muon_pair ? 0.05 : 0.2) ) ) &&
                               (SFOS) &&
                               (mll > electron_pair ? 3. : 1. && mll < 60.) &&
                               (mll < 3. && mll > 3.2) &&
                               (random_bool(mtautau_eff)) && // TODO: make sure this efficiency makes sense
                               (met  > 120.) &&
                               (nSignalJets >= 1) &&
                               (nSignalBJets == 0) &&
                               (signalJets.at(0)->pT() >= 100.) &&
                               (minPhi  > 0.4) &&
                               (fabs(signalJets.at(0)->phi() - ptot.phi()) >= 2.);


        // Preselecton cuts for 1l1T region
        bool preselection_1l1T = (nSignalLeptons == 1 && nSignalTracks >= 1) &&
                                 (signalLeptons.at(0)->pT() < 10.) &&
                                 (deltaR > 0.05 && deltaR < 1.5) &&
                                 (SFOS) &&
                                 (mll > 0.5 && mll < 5) &&
                                 (mll < 3. && mll > 3.2) &&
                                 (met > 120.) &&
                                 (nSignalJets >= 1) &&
                                 // -
                                 (signalJets.at(0)->pT() >= 100.) &&
                                 (minPhi > 0.4) &&
                                 (fabs(signalJets.at(0)->phi() - ptot.phi()) >= 2.);

        // EWino Signal regions
        // Variable         EW, 2l, Low-MET, Low-DeltaM    EW, 2l, Low-MET, High-DeltaM    EW, 2l, High-MET              EW, 1l1T
        // ----------------------------------------------------------------------------------------------------------------------
        // MET                        [120,200]                    [120,200]               > 200                           > 200 // done
        // MET/HTlep                  > 10                         < 10                    -                               > 30  // done
        // DPhi(lep,ptot)             -                            -                       -                               < 1.0 // done
        // l2 or track pT             -                            > 5 + mll/4             > min(10, 2+mll/3)              < 5   // done
        // MTS                        < 50                         -                       -                               -     // done
        // mTl1                       -                            [10,60]                 < 60                            -     // done
        // RISR                       -                            [0.8,1.0]               [max(0.85, 0.98-0.02 mll),1.0]  -     // done

        // mTl1 variable
        double mTl1 = 0.0;
        if (nSignalLeptons > 0)
        {
         mTl1 = sqrt(2*(signalLeptons.at(0)->mom().E()*met - signalLeptons.at(0)->mom().dot3(ptot)));
        }

        // MTS variable
        // TODO: This should be a RJ variable. It's done like this for simplicity but it needs to be looked into
        double MTS = 0.0;
        if (nSignalLeptons > 1)
        {
          P4 PS = ptot + signalLeptons.at(0)->mom() + signalLeptons.at(1)->mom();
          MTS = sqrt(PS.m2() + PS.px2() + PS.py2());
        }

        // RISR variable
        // TODO: This should be a RJ variable. It's done like this for simplicity but it needs to be looked into
        double RISR = 0.0;
        if (nSignalJets > 0)
        {
          RISR = met / signalJets.at(0)->pT();
        }

        // SR_chi_lowMET_lowDM
        if (preselection_2l &&
            met > 120. && met > 200. &&
            met/(signalLeptons.at(0)->pT() + signalLeptons.at(1)->pT()) > 10. &&
            // -
            // -
            MTS < 50.
            // -
            // -
           )
          _counters["SR_chi_lowMET_lowDM"].add_event(event);

        // SR_chi_lowMET_highDM
        if (preselection_2l &&
            met > 120. && met > 200. &&
            met/(signalLeptons.at(0)->pT() + signalLeptons.at(1)->pT()) < 10. &&
            // -
            signalLeptons.at(1)->pT() > 5. + mll/4. &&
            // -
            mTl1 >= 10. && mTl1 <= 60 &&
            RISR >= 0.8 && RISR <= 1.0
           )
          _counters["SR_chi_lowMET_highDM"].add_event(event);

        // SR_chi_highMET
        if (preselection_2l &&
            met > 200. &&
            // -
            // -
            signalLeptons.at(1)->pT() > min(10., 2.+mll/3) &&
            // -
            mTl1 < 60. &&
            RISR >= max(0.85, 0.98 - 0.02*mll) && RISR <= 1.0
           )
          _counters["SR_chi_highMET"].add_event(event);

        // SR_chi_1l1T
        if (preselection_1l1T &&
            met > 200. &&
            met/(signalLeptons.at(0)->pT() + signalLeptons.at(1)->pT()) > 10. && // This limit is shown inconsistently in text and table, so be wary of it
            fabs(signalLeptons.at(0)->phi() - ptot.phi()) > 1.0 &&
            signalTracks.at(0)->pT() < 5.
            // -
            // -
            // -
           )
          _counters["SR_chi_1l1T"].add_event(event);

        // Slepton Signal regions
        // Variable           Sl, Low-MET                     Sl, High-MET
        // ----------------------------------------------------------------------------------------------
        // MET                [150,200]                       > 200                                       // done
        // mT2                < 140                           < 140                                       // done
        // pTl2               > min(15, 7.5+0.75(mT2-100))    > min(20, 2.5+2.5(mT2-100)                  // done
        // RISR               [0.8, 1.0]                      [max(0.85, 0.98 − 0.02 × (mT2 − 100)), 1.0] // done

        // mT2 variable
        double mT2 = 0;
        if(nSignalLeptons > 1)
        {
          double pa[3] = { 0, signalLeptons.at(0)->mom().px(), signalLeptons.at(0)->mom().py() };
          double pb[3] = { 0, signalLeptons.at(1)->mom().px(), signalLeptons.at(1)->mom().py() };
          double pmiss[3] = { 0, ptot.px(), ptot.py() };
          double mn = 0.;

          mt2_bisect::mt2 mt2_calc;
          mt2_calc.set_momenta(pa,pb,pmiss);
          mt2_calc.set_mn(mn);
          mT2 = mt2_calc.get_mt2();
        }


        // SR_sl_lowMET
        if (preselection_2l &&
            met >= 150. && met <= 200. &&
            mT2 < 140. &&
            signalLeptons.at(1)->pT() > min(15., 7.5 + 0.75*(mT2-100.)) &&
            RISR >= 0.8 && RISR <= 1.0
           )
          _counters["SR_sl_lowMET"].add_event(event);

        // SR_sl_highMET
        if (preselection_2l &&
           met > 200. &&
           mT2 < 140. &&
           signalLeptons.at(1)->pT() > min(20., 2.5+2.5*(mT2-100.)) &&
           RISR >= max(0.85, 0.98 - 0.02*(mT2 - 100.)) && RISR <= 1.0
           )
          _counters["SR_sl_highMET"].add_event(event);


      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {
        // SR-E-low observed and background events, from Table 11 of 1911.12606
        // Combined ee and mumu SR data
        COMMIT_SIGNAL_REGION("SR-E-low-1", 9., 15.4, 2.4)
        COMMIT_SIGNAL_REGION("SR-E-low-2", 7., 8.0, 1.7)
        COMMIT_SIGNAL_REGION("SR-E-low-3", 7.+7., 5.3+6.5, 1.5+1.6)
        COMMIT_SIGNAL_REGION("SR-E-low-4", 11.+12., 8.6+11.3, 1.8+1.9)
        COMMIT_SIGNAL_REGION("SR-E-low-5", 16.+17., 16.7+15.6, 2.5+2.3)
        COMMIT_SIGNAL_REGION("SR-E-low-6", 16.+18., 15.5+16.7, 2.6+2.3)
        COMMIT_SIGNAL_REGION("SR-E-low-7", 10.+16., 12.9+15.3, 2.1+2.0)
        COMMIT_SIGNAL_REGION("SR-E-low-8", 9.+44., 18.8+35.9, 2.2+3.3)

        // SR-E-med observed and background events, from Table 11 of 1911.12606
        // Combined ee and mumu SR data


        COMMIT_CUTFLOWS

      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2LEPsoft_139invfb)


  }
}
