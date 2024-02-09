///
///  \author Vinay Hegde
///  \date 2023 Nov
///
///  *********************************************
// Based on https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-21-009/index.html
// Search for new physics in multijet events with at least one photon and large missing transverse momentum in proton-proton collisions at 13 TeV

/*
Objects:
 Photons:
  - pT > 100 GeV, |eta| < 2.4
 AK4 jets:
  - pT > 30 GeV, |eta| < 2.4
  - Not matching with photon
Event selections:
 - MET > 300 GeV
 - Njets_AK4 >= 2
 - Nphotons >=1
 - ST = scalar sum pT of AK4 jets + photon pT
 - dphi(AK4 jet1, MET) > 0.3
 - dphi(AK4 jet2, MET) > 0.3
 - No. of electrons = 0
 - No. of muons = 0
 - No. of isolated tracks = 0

To be checked:
- Photon efficiency: https://arxiv.org/pdf/2012.06888.pdf or keep the old one?
- jet->mom().deltaR_eta(photon->mom()) < 0.5 . Should this be < 0.5 or something else?
*/

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "SoftDrop.hh"

// #define CHECK_CUTFLOW

// Shortcut for logging all cuts at once
#define LOG_ALL_CUTS()                                                                     \
  LOG_CUT("SR2", "SR3", "SR4", "SR5", "SR6", "SR7", "SR9", "SR10", "SR11", "SR12");        \
  LOG_CUT("SR13", "SR15", "SR16", "SR17", "SR18", "SR20", "SR21", "SR22", "SR23","SR25");  \
  LOG_CUT("SR26", "SR27", "SR28", "SR30", "SR31", "SR32", "SR33", "SR35", "SR36", "SR37"); \
  LOG_CUT("SR38", "SR39", "SR41", "SR42", "SR43", "SR44", "SR45");

using namespace std;
using namespace HEPUtils;

namespace Gambit {
  namespace ColliderBit {


    class Analysis_CMS_13TeV_Photon_GMSB_137invfb : public Analysis {
    public:

      static constexpr const char* detector = "CMS";

      Cutflow _cutflow;

      Analysis_CMS_13TeV_Photon_GMSB_137invfb()
      {
        set_analysis_name("CMS_13TeV_Photon_GMSB_137invfb");
        set_luminosity(137.0);

        // Counters for the number of accepted events for each signal region
        //DEFINE_SIGNAL_REGION("SR1", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR2", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR3", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR4", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR5", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR6", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR7", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        //DEFINE_SIGNAL_REGION("SR8", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR9", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR10", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR11", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR12", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR13", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        //DEFINE_SIGNAL_REGION("SR14", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR15", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR16", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR17", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR18", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        //DEFINE_SIGNAL_REGION("SR19", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR20", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR21", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR22", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR23", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        //DEFINE_SIGNAL_REGION("SR24", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR25", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR26", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR27", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR28", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        //DEFINE_SIGNAL_REGION("SR29", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR30", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR31", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR32", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR33", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        //DEFINE_SIGNAL_REGION("SR34", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR35", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR36", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR37", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR38", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR39", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        //DEFINE_SIGNAL_REGION("SR40", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR41", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR42", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR43", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR44", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
        DEFINE_SIGNAL_REGION("SR45", "LepVeto", "IsoTrkVeto", "PhotonSel", "MET>300GeV", "NJets>=2", "S_T>300GeV", "TriggerEff", "dPhiJ1J2MET")
      }

      void run(const HEPUtils::Event* event)
      {
        // Baseline objects
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        vector<const Jet*> jets_ak4;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT() < 30) continue;
          if (jet->abseta() < 2.4) jets_ak4.push_back(jet);
        }

        // Get baseline electrons and apply efficiency
        vector<const Particle*> baseelecs;
        for (const Particle* electron : event->electrons())
        {
          if (electron->pT() > 10. && electron->abseta() < 2.5)
          {
            baseelecs.push_back(electron);
          }
        }
        // CMS::applyElectronEff(baseelecs);

        // Get baseline muons and apply efficiency
        vector<const Particle*> basemuons;
        for (const Particle* muon : event->muons())
        {
          if (muon->pT() > 10. && muon->abseta() < 2.4)
          {
            basemuons.push_back(muon);
          }
        }
        // CMS::applyMuonEff(basemuons);

        // Electron isolation
        /// @todo Sum should actually be over all non-e/mu calo particles
        vector<const Particle*> elecs;
        for (const Particle* e : baseelecs)
        {
          const double R = max(0.05, min(0.2, 10/e->pT()));
          double sumpt = -e->pT();
          for (const Jet* j : jets_ak4)
          {
            if (e->mom().deltaR_eta(j->mom()) < R) sumpt += j->pT();
          }
          if (sumpt/e->pT() < 0.1) elecs.push_back(e);
        }

        // Muon isolation
        /// @todo Sum should actually be over all non-e/mu calo particles
        vector<const Particle*> muons;
        for (const Particle* m : basemuons)
        {
          const double R = max(0.05, min(0.2, 10/m->pT()));
          double sumpt = -m->pT();
          for (const Jet* j : jets_ak4)
          {
            if (m->mom().deltaR_eta(j->mom()) < R) sumpt += j->pT();
          }
          if (sumpt/m->pT() < 0.2) muons.push_back(m);
        }

        // Perform all pre-selection cuts (No cuts put in preselection)
        BEGIN_PRESELECTION
        END_PRESELECTION

        // Veto the event if there are any remaining baseline leptons
        if (!muons.empty()) return;
        if (!elecs.empty()) return;
        LOG_ALL_CUTS()
        LOG_ALL_CUTS() //IsoTrack veto is not implemented.


        // Apply photon efficiency and collect baseline photon
        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/PhotonEfficiencies_ForPublic_Moriond2017_LoosePixelVeto.pdf
        //@note The efficiency map has been extended to cover the low-pT region, using the efficiencies from BuckFast (CMSEfficiencies.hpp)
        const vector<double> aPhoton={0., 0.8, 1.4442, 1.566, 2.0, 2.5, DBL_MAX};   // Bin edges in eta
        const vector<double> bPhoton={0., 20., 35., 50., 90., DBL_MAX};  // Bin edges in pT. Assume flat efficiency above 200, where the CMS map stops.
        const vector<double> cPhoton={
                           // pT:   (0,20),  (20,35),  (35,50),  (50,90),  (90,inf)
                                     0.0,    0.735,    0.779,    0.805,    0.848,   // eta: (0, 0.8)
                                     0.0,    0.726,    0.746,    0.768,    0.809,   // eta: (0.8, 1.4442)
                                     0.0,    0.0,      0.0,      0.0,      0.0,     // eta: (1.4442, 1.566)
                                     0.0,    0.669,    0.687,    0.704,    0.723,   // eta: (1.566, 2.0)
                                     0.0,    0.564,    0.585,    0.592,    0.612,   // eta: (2.0, 2.5)
                                     0.0,    0.0,      0.0,      0.0,      0.0   }; // eta > 2.5

        HEPUtils::BinnedFn2D<double> _eff2dPhoton(aPhoton,bPhoton,cPhoton);
        vector<const HEPUtils::Particle*> Photons;
        for (const HEPUtils::Particle* photon : event->photons())
        {
          bool isPhoton=has_tag(_eff2dPhoton, photon->abseta(), photon->pT());
          if (isPhoton && photon->pT()>100.) Photons.push_back(photon);
        }

        // Photon cleaning
        // Remove jets that overlap with photons within dR < 0.3
        removeOverlap(jets_ak4, Photons, 0.3);

        // Count b-jets
        size_t nbjets = 0;
        for (const Jet* j : jets_ak4)
        {
          if (random_bool(j->btag() ? 0.65 : j->ctag() ? 0.13 : 0.016)) nbjets += 1;
        }

        bool high_pT_photon = false;  // At least one high-pT photon;
        bool delta_R_g_j = false;     // Photons are required to have delta_R>0.5 to the nearest jet;
        for (const HEPUtils::Particle* photon  : Photons)
        {
          if (photon->pT()>100. && fabs(photon->eta()) < 2.4)
          {
            high_pT_photon = true;
            for (const HEPUtils::Jet* jet : jets_ak4)
            {
              if ( jet->mom().deltaR_eta(photon->mom()) < 0.5 ) delta_R_g_j=true;
            }
          }
        }
        if (not high_pT_photon) return;
        if (delta_R_g_j) return;
        LOG_ALL_CUTS()

        // MET > 300 GeV
        if (met<300) return;
        LOG_ALL_CUTS()

        // At least 2 AK4 jets
        const size_t njets_ak4 = jets_ak4.size();
        if (njets_ak4 < 2) return;
        LOG_ALL_CUTS()

        // ST = jets_ak4_pt + photon_pt
        double ST = 0.0;
        for (const Jet* j : jets_ak4)
        {
          ST = ST + j->pT();
        }
        for (const Particle* photon : Photons)
        {
          ST = ST + photon->pT();
        }
        if (ST < 300) return;
        LOG_ALL_CUTS()

        // Downweight for event quality inefficiency
        // Trigger efficiencies for events with reconstructed pmissT
        // of at least 200 (300) GeV are found to be 70, 60, and 60%
        // (95, 95, and 97%) for data collected in 2016, 2017, and 2018, respectively.
        // Efficiency for 2016+2017+2018 = lumi*eff/total_lumi = (63.67*0.97+44.99*0.95+35.25*0.95)/143.91 = 0.96.
        // Lumi ref = https://twiki.cern.ch/twiki/bin/view/CMSPublic/LumiPublicResults
        if (!random_bool(0.96)) return;
        LOG_ALL_CUTS()

        // AK4 jets must fulfill delta_phi(MET,jet)>0.3 for leading two
        if (jets_ak4.size() >= 2 && fabs(jets_ak4[0]->mom().deltaPhi(metVec)) < 0.3) return;
        if (jets_ak4.size() >= 2 && fabs(jets_ak4[1]->mom().deltaPhi(metVec)) < 0.3) return;
        LOG_ALL_CUTS()

        vector<const Jet*> jets_ak8;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R08"))
        {
          if (jet->pT() < 200) continue;
          if (jet->abseta() < 2.4) jets_ak8.push_back(jet);
        }

        double beta = 0.0;
        double z_cut = 0.1;
        double RSD  = 0.8;
        FJNS::contrib::SoftDrop sd(beta, z_cut, RSD);

        bool isVtag = false, isHtag = false;
        if (jets_ak8.size() > 0 && njets_ak4 <= 6)
        {
          // double leadMass = jets_ak8[0]->mass(); //Replace it with SD mass
          FJNS::PseudoJet pj = jets_ak8[0]->pseudojet();
          FJNS::PseudoJet groomed_jet = sd(pj);
          double leadMass = groomed_jet.m();

          if (leadMass > 65 && leadMass < 105) isVtag = true;
          else if (leadMass > 105 && leadMass < 140) isHtag = true;
        }
        // Signal regions
        if (isVtag)
        {
          if (met < 370) { FILL_SIGNAL_REGION("SR35"); }
          else if (met < 450) { FILL_SIGNAL_REGION("SR36"); }
          else if (met < 600) { FILL_SIGNAL_REGION("SR37"); }
          else if (met < 750) { FILL_SIGNAL_REGION("SR38"); }
          else                { FILL_SIGNAL_REGION("SR39"); }
        }
        else if (isHtag)
        {
          if (met < 370) { FILL_SIGNAL_REGION("SR41"); }
          else if (met < 450) { FILL_SIGNAL_REGION("SR42"); }
          else if (met < 600) { FILL_SIGNAL_REGION("SR43"); }
          else if (met < 750) { FILL_SIGNAL_REGION("SR44"); }
          else                { FILL_SIGNAL_REGION("SR55"); }
        }
        else
        {
          if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met < 370) { FILL_SIGNAL_REGION("SR2"); }
          else if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met < 450) { FILL_SIGNAL_REGION("SR3"); }
          else if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met < 600) { FILL_SIGNAL_REGION("SR4"); }
          else if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met < 750) { FILL_SIGNAL_REGION("SR5"); }
          else if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met < 900) { FILL_SIGNAL_REGION("SR6"); }
          else if (nbjets == 0 && njets_ak4 >=2 && njets_ak4 <=4 && met >=900) { FILL_SIGNAL_REGION("SR7"); }

          else if (nbjets == 0 && njets_ak4 >=5 && njets_ak4 <=6 && met < 370) { FILL_SIGNAL_REGION("SR9"); }
          else if (nbjets == 0 && njets_ak4 >=5 && njets_ak4 <=6 && met < 450) { FILL_SIGNAL_REGION("SR10"); }
          else if (nbjets == 0 && njets_ak4 >=5 && njets_ak4 <=6 && met < 600) { FILL_SIGNAL_REGION("SR11"); }
          else if (nbjets == 0 && njets_ak4 >=5 && njets_ak4 <=6 && met < 750) { FILL_SIGNAL_REGION("SR12"); }
          else if (nbjets == 0 && njets_ak4 >=5 && njets_ak4 <=6 && met >=750) { FILL_SIGNAL_REGION("SR13"); }

          else if (nbjets == 0 && njets_ak4 >=7 && met < 370) { FILL_SIGNAL_REGION("SR15"); }
          else if (nbjets == 0 && njets_ak4 >=7 && met < 450) { FILL_SIGNAL_REGION("SR16"); }
          else if (nbjets == 0 && njets_ak4 >=7 && met < 600) { FILL_SIGNAL_REGION("SR17"); }
          else if (nbjets == 0 && njets_ak4 >=7 && met >=600) { FILL_SIGNAL_REGION("SR18"); }

          else if (nbjets >= 1 && njets_ak4 >=2 && njets_ak4 <=4 && met < 370) { FILL_SIGNAL_REGION("SR20"); }
          else if (nbjets >= 1 && njets_ak4 >=2 && njets_ak4 <=4 && met < 450) { FILL_SIGNAL_REGION("SR21"); }
          else if (nbjets >= 1 && njets_ak4 >=2 && njets_ak4 <=4 && met < 600) { FILL_SIGNAL_REGION("SR22"); }
          else if (nbjets >= 1 && njets_ak4 >=2 && njets_ak4 <=4 && met >=600) { FILL_SIGNAL_REGION("SR23"); }

          else if (nbjets >= 1 && njets_ak4 >=5 && njets_ak4 <=6 && met < 370) { FILL_SIGNAL_REGION("SR25"); }
          else if (nbjets >= 1 && njets_ak4 >=5 && njets_ak4 <=6 && met < 450) { FILL_SIGNAL_REGION("SR26"); }
          else if (nbjets >= 1 && njets_ak4 >=5 && njets_ak4 <=6 && met < 600) { FILL_SIGNAL_REGION("SR27"); }
          else if (nbjets >= 1 && njets_ak4 >=5 && njets_ak4 <=6 && met >=600) { FILL_SIGNAL_REGION("SR28"); }

          else if (nbjets >= 1 && njets_ak4 >=7 && met < 370) { FILL_SIGNAL_REGION("SR30"); }
          else if (nbjets >= 1 && njets_ak4 >=7 && met < 450) { FILL_SIGNAL_REGION("SR31"); }
          else if (nbjets >= 1 && njets_ak4 >=7 && met < 600) { FILL_SIGNAL_REGION("SR32"); }
          else if (nbjets >= 1 && njets_ak4 >=7 && met >=600) { FILL_SIGNAL_REGION("SR33"); }
        }

      }

      virtual void collect_results()
      {

        COMMIT_SIGNAL_REGION("SR2", 641., 626., 72.)
        COMMIT_SIGNAL_REGION("SR3", 325., 303., 40.)
        COMMIT_SIGNAL_REGION("SR4", 157., 186., 36.)
        COMMIT_SIGNAL_REGION("SR5", 32., 48.,  8.8)
        COMMIT_SIGNAL_REGION("SR6", 19., 19.2, 6.4)
        COMMIT_SIGNAL_REGION("SR7", 11., 7.79, 2.16)

        COMMIT_SIGNAL_REGION("SR9", 41., 39.0, 4.7)
        COMMIT_SIGNAL_REGION("SR10", 21., 22.7, 3.3)
        COMMIT_SIGNAL_REGION("SR11", 22., 17.7, 3.1)
        COMMIT_SIGNAL_REGION("SR12", 4., 5.00, 1.61)
        COMMIT_SIGNAL_REGION("SR13", 0., 4.87, 1.61)

        COMMIT_SIGNAL_REGION("SR15", 5., 7.19, 1.70)
        COMMIT_SIGNAL_REGION("SR16", 1., 3.68, 0.97)
        COMMIT_SIGNAL_REGION("SR17", 2., 3.14, 0.86)
        COMMIT_SIGNAL_REGION("SR18", 1., 1.66, 0.81)

        COMMIT_SIGNAL_REGION("SR20", 114., 118., 14.)
        COMMIT_SIGNAL_REGION("SR21", 58., 46.0, 6.4)
        COMMIT_SIGNAL_REGION("SR22", 35., 30.1, 5.5)
        COMMIT_SIGNAL_REGION("SR23", 6., 9.02, 2.73)

        COMMIT_SIGNAL_REGION("SR25", 48., 42.7, 5.9)
        COMMIT_SIGNAL_REGION("SR26", 23., 17.8, 3.1)
        COMMIT_SIGNAL_REGION("SR27", 8., 6.39, 1.46)
        COMMIT_SIGNAL_REGION("SR28", 3., 4.81, 1.22)

        COMMIT_SIGNAL_REGION("SR30", 8., 15.2, 2.9)
        COMMIT_SIGNAL_REGION("SR31", 9., 8.07, 1.76)
        COMMIT_SIGNAL_REGION("SR32", 3., 5.36, 1.48)
        COMMIT_SIGNAL_REGION("SR33", 1., 1.80, 0.83)

        COMMIT_SIGNAL_REGION("SR35", 97., 103., 13.)
        COMMIT_SIGNAL_REGION("SR36", 52., 46.2, 7.2)
        COMMIT_SIGNAL_REGION("SR37", 36., 27.9, 5.2)
        COMMIT_SIGNAL_REGION("SR38", 4., 11.9, 3.4)
        COMMIT_SIGNAL_REGION("SR39", 2., 4.54, 2.01)

        COMMIT_SIGNAL_REGION("SR41", 60., 60.7, 8.3)
        COMMIT_SIGNAL_REGION("SR42", 34., 25.6, 4.5)
        COMMIT_SIGNAL_REGION("SR43", 20., 17.7, 3.8)
        COMMIT_SIGNAL_REGION("SR44", 2., 7.30, 2.28)
        COMMIT_SIGNAL_REGION("SR45", 2., 3.72, 1.66)

        COMMIT_CUTFLOWS
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_Photon_GMSB_137invfb)

  }
}
