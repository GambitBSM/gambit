///
///  \author Chris Chang
///  \date 2026 Aug
///
///  *********************************************

// Based on "Search for signatures of electroweakinos with photons, jets, and
// large missing transverse momentum in sqrt(s)=13 TeV pp collisions with the
// ATLAS detector" (ATLAS-SUSY-2021-07), JHEP 04 (2026) 150, arXiv:2511.21240.
//
// Targets GGM models where the lightest neutralino, a bino-higgsino admixture,
// decays to (gravitino + photon/Z/h). Final state: >=1 photon, >=1 jet, MET.
// Uses the ATLAS object-based MET significance (as in the 2LEPJETS_EW analysis).
//
// Five signal regions are implemented, matching Table 2 of the paper:
//  - SRL, SRM, SRH:   inclusive "discovery" regions
//  - SRLe, SRMe:      mutually-exclusive "exclusion" regions (with SRH) used
//                      together with SRH in the simultaneous exclusion fit
// The background estimates and observed yields are taken from Table 5.
// No public covariance/correlation between the signal regions was available,
// so the regions are treated as independent.
//
// Things not implemented:
//  - Calometric isolation energy (E_T^iso), which must be less than 2.45 GeV + 0.022pT (pT is of leading photon)
//    - I suspect this is something on the experiment side perhaps not relevant to our recast
//  - Impact parameters:
//     - e:  |z_0 sin(theta)| < 0.5mm, |d_0| / sigma_d_0 < 5
//     - mu: |z_0 sin(theta)| < 0.5mm, |d_0| / sigma_d_0 < 3
//  - Tracks
//

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

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

    class Analysis_ATLAS_13TeV_PhotonMET_GGM_140invfb : public Analysis
    {

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_PhotonMET_GGM_140invfb()
      {

        set_analysis_name("ATLAS_13TeV_PhotonMET_GGM_140invfb");
        set_detector_name(detector);
        set_luminosity(140.);

        // Common preselection (Nphotons>0, pT(gamma1)>145 GeV, Njet>0,
        // dPhi(jet,MET)>0.4, dPhi(gamma,MET)>0.4, MET/meff>0.5, mgg veto)
        // is bundled into the single "Preselection" step below; only the
        // SR-differentiating cuts on MET and MET significance are logged
        // as named cutflow steps.

        // Discovery (inclusive) signal regions
        defineSignalRegion("SRL", "MET>200GeV", "METsig>20");
        defineSignalRegion("SRM", "MET>300GeV", "METsig>30");
        defineSignalRegion("SRH", "MET>400GeV", "METsig>35");

        // Exclusion (mutually exclusive) signal regions, used with SRH in
        // the simultaneous fit for exclusion limits. The final "not in
        // SRM/SRH" veto is applied as the gate on FILL_SIGNAL_REGION itself,
        // rather than as a separate named cutflow step.
        defineSignalRegion("SRLe", "MET>200GeV", "METsig>20");
        defineSignalRegion("SRMe", "MET>300GeV", "METsig>30");

      }

      void run(const HEPUtils::Event* event)
      {

        // Missing momentum
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        // Baseline photons: tight ID, pT > 50 GeV, |eta| < 2.37, excluding
        // the barrel-endcap transition region 1.37 < |eta| < 1.52
        vector<const HEPUtils::Particle*> baselinePhotons;
        for (const HEPUtils::Particle* photon : event->photons())
        {
          bool endcap = (photon->abseta() > 1.37) && (photon->abseta() < 1.52);
          if (photon->pT() > 50. && photon->abseta() < 2.37 && !endcap) baselinePhotons.push_back(photon);
        }
        // Apply (tight) photon identification/isolation efficiency
        applyEfficiency(baselinePhotons, ATLAS::eff2DPhoton.at("R2"));

        // Baseline electrons: tight ID, loose isolation, pT > 10 GeV, |eta| < 2.47
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          bool endcap = (electron->abseta() > 1.37) && (electron->abseta() < 1.52);
          if (electron->pT() > 10. && electron->abseta() < 2.47 && !endcap) baselineElectrons.push_back(electron);
        }
        applyEfficiency(baselineElectrons, ATLAS::eff2DEl.at("Generic"));
        applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_ID_Tight"));
        applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_Iso_Loose"));

        // Baseline muons: medium quality, loose isolation, pT > 10 GeV, |eta| < 2.7
        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 10. && muon->abseta() < 2.7) baselineMuons.push_back(muon);
        }
        applyEfficiency(baselineMuons, ATLAS::eff2DMu.at("Generic"));
        applyEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_Iso_Loose"));

        // Baseline jets: anti-kt R=0.4, pT > 20 GeV, |eta| < 2.8
        vector<const HEPUtils::Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT() > 20. && jet->abseta() < 2.8) baselineJets.push_back(jet);
        }

        // Overlap removal. Note: no explicit lepton veto is applied in the
        // signal regions (leptons are only used to define the paper's control
        // and validation regions), so the baseline leptons here are used only
        // to construct the MET significance and the object cleaning below.
        removeOverlap(baselineElectrons, baselineMuons, 0.01);
        removeOverlap(baselineJets, baselinePhotons, 0.4);
        removeOverlap(baselineJets, baselineElectrons, 0.2);
        removeOverlap(baselineElectrons, baselineJets, 0.4);
        removeOverlap(baselineJets, baselineMuons, 0.2);

        // Signal objects
        vector<const HEPUtils::Particle*> signalPhotons = baselinePhotons;
        vector<const HEPUtils::Jet*> signalJets = baselineJets;

        sortByPt(signalPhotons);
        sortByPt(signalJets);

        size_t nPhotons = signalPhotons.size();
        size_t nJets = signalJets.size();

        // Leading photon pT
        double pTLeadingPhoton = (nPhotons > 0) ? signalPhotons[0]->pT() : 0.;

        // Effective mass: MET + pT(leading photon) + sum of jet pT
        double meff = met;
        if (nPhotons > 0) meff += signalPhotons[0]->pT();
        for (const HEPUtils::Jet* jet : signalJets) meff += jet->pT();

        // dPhi(jet, MET): minimum over the leading (up to) two jets
        double deltaPhiJetMET = DBL_MAX;
        if (nJets == 1)
        {
          deltaPhiJetMET = fabs(metVec.deltaPhi(signalJets[0]->mom()));
        }
        else if (nJets >= 2)
        {
          deltaPhiJetMET = std::min(fabs(metVec.deltaPhi(signalJets[0]->mom())),
                                     fabs(metVec.deltaPhi(signalJets[1]->mom())));
        }

        // dPhi(gamma, MET): leading photon
        double deltaPhiPhotonMET = DBL_MAX;
        if (nPhotons > 0) deltaPhiPhotonMET = fabs(metVec.deltaPhi(signalPhotons[0]->mom()));

        // Diphoton invariant mass veto (only relevant with >= 2 photons)
        double mgammagamma = -1.;
        if (nPhotons >= 2)
        {
          HEPUtils::P4 diphoton = signalPhotons[0]->mom() + signalPhotons[1]->mom();
          mgammagamma = diphoton.m();
        }
        bool passMggVeto = !(mgammagamma > 120. && mgammagamma < 130.);

        // MET significance (ATLAS object-based definition)
        double metsig = calcMETSignificance(baselineElectrons, baselinePhotons, baselineMuons,
                                             baselineJets, event->taus(), metVec);

        // Common preselection for all signal regions
        bool passPresel = false;
        BEGIN_PRESELECTION
        while (true)
        {
          if (!(nPhotons > 0)) break;
          if (!(pTLeadingPhoton > 145.)) break;
          if (!(nJets > 0)) break;
          if (!(deltaPhiJetMET > 0.4)) break;
          if (!(deltaPhiPhotonMET > 0.4)) break;
          if (!(met / meff > 0.5)) break;
          if (!passMggVeto) break;

          passPresel = true;
          break;
        }
        if (!passPresel) return;
        END_PRESELECTION

        // Discovery signal regions (inclusive in MET/METsig)
        bool inSRM_kinematics = (met > 300. && metsig > 30.);
        bool inSRH_kinematics = (met > 400. && metsig > 35.);

        while (true)
        {
          if (!(met > 200.)) break;
          LOG_CUT("SRL", "SRLe")
          if (!(metsig > 20.)) break;
          LOG_CUT("SRL", "SRLe")

          FILL_SIGNAL_REGION("SRL");
          if (!inSRM_kinematics) { FILL_SIGNAL_REGION("SRLe"); }
          break;
        }

        while (true)
        {
          if (!inSRM_kinematics) break;
          LOG_CUT("SRM", "SRMe")
          LOG_CUT("SRM", "SRMe")

          FILL_SIGNAL_REGION("SRM");
          if (!inSRH_kinematics) { FILL_SIGNAL_REGION("SRMe"); }
          break;
        }

        while (true)
        {
          if (!inSRH_kinematics) break;
          LOG_CUT("SRH")
          LOG_CUT("SRH")

          FILL_SIGNAL_REGION("SRH");
          break;
        }

        return;

      }


      virtual void collect_results()
      {

        // Observed events and background estimate (central, error), from Table 5
        COMMIT_SIGNAL_REGION("SRL",  173., 214.,  19.)
        COMMIT_SIGNAL_REGION("SRM",  21.,  32.5,  3.3)
        COMMIT_SIGNAL_REGION("SRH",  8.,   14.6,  2.0)
        COMMIT_SIGNAL_REGION("SRLe", 152., 182.,  16.)
        COMMIT_SIGNAL_REGION("SRMe", 13.,  17.9,  2.0)

        COMMIT_CUTFLOWS

        return;
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory function
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_PhotonMET_GGM_140invfb)


  }
}
