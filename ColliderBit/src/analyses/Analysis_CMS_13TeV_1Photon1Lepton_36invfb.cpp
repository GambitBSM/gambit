///
///  \author Anders Kvellestad
///  \date 2020 Oct
///
///  *********************************************

/*
  Based on:
    "Search for supersymmetry in events with a photon, a lepton, and missing transverse momentum in proton-proton collisions at 13 TeV"
    http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-17-012/index.html
    http://arxiv.org/abs/1812.04066

  Notes:

    - No published cutflows, so we'll validate by reproducing exclusion contours

    - No table with event count numbers -- had to digitze from a log-scale histogram. 
      (But I think I got it reasonable accurate.)

  
  Event selection summary:

    - Both e+gamma and mu+gamma signal regions
    - Photon candidates identfied with loose criteria --> 90% selection efficiency
    - Jet candidates: pT > 30, |eta| < 2.5

    - Trigger for e+gamma SRs:
      - CMS use a di-photon trigger that also allow events with 1 photon + 1 electron (EM objects)
      - pTs of the two leading EM objects (e/gamma): pT > 30, 18
      - Invariant mass m_(EM1,EM2) > 90 GeV
      - Avg. trigger eff: 96%

    - Trigger for mu+gamma SRs:
      - CMS use a combination of two triggers for muon+photon events
      - 1) Photon isolation + pT_gamma > 30, pT_muon > 17   
      - 2) No photon isolation, pT_gamma > 38, pT_muon > 38
      - Avg. trigger eff: 94%

    - At least 1 photon, with pT > 35, |eta| < 1.44
    - At least one e (mu) with pT > 25, |eta| < 2.5 (2.4)
    - Exclude electrons in 1.44 < |eta| < 1.56
    - If more than one e (mu), choose the one with highest pT

    - Veto photons candidates within DeltaR < 0.3 of any reconstructed e/mu
    - Require DeltaR(leading photon, leading lepton) > 0.8
    - If e+gamma event, require m(e,gamma) > 101.2 (= mZ + 10)

    - Selection variable: mT
      mT = sqrt(2 * pT_lepton * pTmiss * (1 - cos DeltaPhi(lepton,pTmiss_vector)))

    - Selection variable: HT
      HT = scalar sum of pT for all jets that have DeltaR(jet, leading photon) > 0.4 
           and DeltaR(jet, leading lepon) > 0.4

    - Signal regions defined in terms of pTmss, pTgamma and HT:

    - e+gamma SRs:

      - SR1:   35 < pTgamma < 200, 120 < pTmiss < 200,   0 < HT < 100
      - SR2:   35 < pTgamma < 200, 120 < pTmiss < 200, 100 < HT < 400
      - SR3:   35 < pTgamma < 200, 120 < pTmiss < 200, 400 < HT < 
      - SR4:   35 < pTgamma < 200, 200 < pTmiss < 400,   0 < HT < 100
      - SR5:   35 < pTgamma < 200, 200 < pTmiss < 400, 100 < HT < 400
      - SR6:   35 < pTgamma < 200, 200 < pTmiss < 400, 400 < HT < 
      - SR7:   35 < pTgamma < 200, 400 < pTmiss      ,   0 < HT < 100
      - SR8:   35 < pTgamma < 200, 400 < pTmiss      , 100 < HT < 400
      - SR9:   35 < pTgamma < 200, 400 < pTmiss      , 400 < HT < 

      - SR10: 200 < pTgamma     , 120 < pTmiss < 200,   0 < HT < 100
      - SR11: 200 < pTgamma     , 120 < pTmiss < 200, 100 < HT < 400
      - SR12: 200 < pTgamma     , 120 < pTmiss < 200, 400 < HT < 
      - SR13: 200 < pTgamma     , 200 < pTmiss < 400,   0 < HT < 100
      - SR14: 200 < pTgamma     , 200 < pTmiss < 400, 100 < HT < 400
      - SR15: 200 < pTgamma     , 200 < pTmiss < 400, 400 < HT < 
      - SR16: 200 < pTgamma     , 400 < pTmiss      ,   0 < HT < 100
      - SR17: 200 < pTgamma     , 400 < pTmiss      , 100 < HT < 400
      - SR18: 200 < pTgamma     , 400 < pTmiss      , 400 < HT < 

    - mu+gamma SRs:

      - SR19:   35 < pTgamma < 200, 120 < pTmiss < 200,   0 < HT < 100
      - SR20:   35 < pTgamma < 200, 120 < pTmiss < 200, 100 < HT < 400
      - SR21:   35 < pTgamma < 200, 120 < pTmiss < 200, 400 < HT < 
      - SR22:   35 < pTgamma < 200, 200 < pTmiss < 400,   0 < HT < 100
      - SR23:   35 < pTgamma < 200, 200 < pTmiss < 400, 100 < HT < 400
      - SR24:   35 < pTgamma < 200, 200 < pTmiss < 400, 400 < HT < 
      - SR25:   35 < pTgamma < 200, 400 < pTmiss      ,   0 < HT < 100
      - SR26:   35 < pTgamma < 200, 400 < pTmiss      , 100 < HT < 400
      - SR27:   35 < pTgamma < 200, 400 < pTmiss      , 400 < HT < 

      - SR28: 200 < pTgamma     , 120 < pTmiss < 200,   0 < HT < 100
      - SR29: 200 < pTgamma     , 120 < pTmiss < 200, 100 < HT < 400
      - SR30: 200 < pTgamma     , 120 < pTmiss < 200, 400 < HT < 
      - SR31: 200 < pTgamma     , 200 < pTmiss < 400,   0 < HT < 100
      - SR32: 200 < pTgamma     , 200 < pTmiss < 400, 100 < HT < 400
      - SR33: 200 < pTgamma     , 200 < pTmiss < 400, 400 < HT < 
      - SR34: 200 < pTgamma     , 400 < pTmiss      ,   0 < HT < 100
      - SR35: 200 < pTgamma     , 400 < pTmiss      , 100 < HT < 400
      - SR36: 200 < pTgamma     , 400 < pTmiss      , 400 < HT < 

*/

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
// #include "gambit/ColliderBit/analyses/Cutflow.hpp"

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    // This analysis class is also a base class for the analysis 
    // class Analysis_CMS_13TeV_1Photon1Lepton_emu_combined_36invfb 
    // defined further down
    class Analysis_CMS_13TeV_1Photon1Lepton_36invfb : public Analysis {
    public:

      static constexpr const char* detector = "CMS";

      // Counters for the number of accepted events for each signal region
      std::map<string, EventCounter> _counters = {
        {"SR1", EventCounter("SR1")},
        {"SR2", EventCounter("SR2")},
        {"SR3", EventCounter("SR3")},
        {"SR4", EventCounter("SR4")},
        {"SR5", EventCounter("SR5")},
        {"SR6", EventCounter("SR6")},
        {"SR7", EventCounter("SR7")},
        {"SR8", EventCounter("SR8")},
        {"SR9", EventCounter("SR9")},
        {"SR10", EventCounter("SR10")},
        {"SR11", EventCounter("SR11")},
        {"SR12", EventCounter("SR12")},
        {"SR13", EventCounter("SR13")},
        {"SR14", EventCounter("SR14")},
        {"SR15", EventCounter("SR15")},
        {"SR16", EventCounter("SR16")},
        {"SR17", EventCounter("SR17")},
        {"SR18", EventCounter("SR18")},
        {"SR19", EventCounter("SR19")},
        {"SR20", EventCounter("SR20")},
        {"SR21", EventCounter("SR21")},
        {"SR22", EventCounter("SR22")},
        {"SR23", EventCounter("SR23")},
        {"SR24", EventCounter("SR24")},
        {"SR25", EventCounter("SR25")},
        {"SR26", EventCounter("SR26")},
        {"SR27", EventCounter("SR27")},
        {"SR28", EventCounter("SR28")},
        {"SR29", EventCounter("SR29")},
        {"SR30", EventCounter("SR30")},
        {"SR31", EventCounter("SR31")},
        {"SR32", EventCounter("SR32")},
        {"SR33", EventCounter("SR33")},
        {"SR34", EventCounter("SR34")},
        {"SR35", EventCounter("SR35")},
        {"SR36", EventCounter("SR36")},
      };

      // Analysis_CMS_13TeV_1Photon1Lepton_36invfb():
      Analysis_CMS_13TeV_1Photon1Lepton_36invfb()
      {
        set_analysis_name("CMS_13TeV_1Photon1Lepton_36invfb");
        set_luminosity(35.9);
      }


      void run(const HEPUtils::Event* event)
      {
        // Baseline objects
        HEPUtils::P4 pTmissVector = event->missingmom();
        double pTmiss = event->met();

        // Photons
        // Apply photon efficiency and collect baseline photons
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
                                     0.0,    0.0,      0.0,      0.0,      0.0,     // eta > 2.5
                                 };
        HEPUtils::BinnedFn2D<double> _eff2dPhoton(aPhoton,bPhoton,cPhoton);
        vector<const HEPUtils::Particle*> photons;
        for (const HEPUtils::Particle* photon : event->photons())
        {
          bool isPhoton=has_tag(_eff2dPhoton, photon->abseta(), photon->pT());
          if (isPhoton && photon->pT() > 35. && photon->abseta() < 1.44)
          {
            photons.push_back(photon);
          }
        }


        // Electrons
        // Apply electron efficiency and collect baseline electrons
        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/eff_el_17012.pdf
        //@note The efficiency map has been extended to cover the low-pT region (simply set to 0 for pT < 25 GeV)
        const vector<double> aEl={0., 0.8, 1.442, 1.556, 2., 2.5, DBL_MAX};   // Bin edges in eta
        const vector<double> bEl={0., 25., 30., 40., 50., 100., DBL_MAX}; // Bin edges in pT
        const vector<double> cEl={
                          // pT: (0,25),  (25,30),  (30,40),  (40,50),  (50,100), (100,inf)
                                   0.0,    0.659,    0.724,    0.769,    0.824,    0.865,  // eta: (0, 0.8)
                                   0.0,    0.470,    0.561,    0.650,    0.765,    0.847,  // eta: (0.8, 1.442)
                                   0.0,    0.276,    0.341,    0.401,    0.437,    0.498,  // eta: (1.442, 1.556)
                                   0.0,    0.332,    0.439,    0.538,    0.664,    0.794,  // eta: (1.556, 2)
                                   0.0,    0.468,    0.575,    0.656,    0.727,    0.805,  // eta: (2, 2.5)
                                   0.0,    0.0,      0.0,      0.0,      0.0,      0.0,    // eta > 2.5
                                  };
        HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
        vector<const HEPUtils::Particle*> electrons;
        for (const HEPUtils::Particle* electron : event->electrons()) 
        {
          bool isEl=has_tag(_eff2dEl, electron->abseta(), electron->pT());
          if (isEl && electron->pT() > 25. && electron->abseta() < 2.5)
          {
            if (electron->abseta() < 1.442 || electron->abseta() > 1.556)
            {
              electrons.push_back(electron);
            }
          }
        }
        // // Sort
        // sortByPt(electrons);


        // Muons
        // Apply electron efficiency and collect baseline electrons
        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/eff_mu_17012.pdf
        //@note The efficiency map has been extended to cover the low-pT region (simply set to 0 for pT < 25 GeV)
        const vector<double> aMu={0., 0.9, 1.2, 2.1, 2.4, DBL_MAX};   // Bin edges in eta
        const vector<double> bMu={0., 25., 30., 40., 50., 100., DBL_MAX};  // Bin edges in pT
        const vector<double> cMu={
                           // pT:  (0,25),   (25,30),  (30,40),  (40,50),  (50,100),  (100,inf)
                                     0.0,     0.882,    0.924,    0.937,    0.956,     0.969,  // eta: (0, 0.9)
                                     0.0,     0.869,    0.922,    0.937,    0.959,     0.971,  // eta: (0.9, 1.2)
                                     0.0,     0.881,    0.936,    0.948,    0.970,     0.982,  // eta: (1.2, 2.1)
                                     0.0,     0.808,    0.883,    0.894,    0.910,     0.920,  // eta: (2.1, 2.4)
                                     0.0,     0.0,      0.0,      0.0,      0.0,       0.0,    // eta > 2.4
                                 };
        HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
        vector<const HEPUtils::Particle*> muons;
        for (const HEPUtils::Particle* muon : event->muons())
        {
          bool isMu=has_tag(_eff2dMu, muon->abseta(), muon->pT());
          if (isMu && muon->pT() > 25. && muon->abseta() < 2.4)
          {
            muons.push_back(muon);
          }
        }
        // // Sort
        // sortByPt(muons);



        // Jets
        vector<const HEPUtils::Jet*> jets;
        for (const HEPUtils::Jet* jet : event->jets())
        {
          if (jet->pT()>30. && jet->abseta()<2.5) jets.push_back(jet);
        }
        // // Sort
        // sortByPt(jets);

        // Remove any photon within DeltaR < 0.3 of any reconstructed e/mu
        removeOverlap(photons, electrons, 0.3);
        removeOverlap(photons, muons, 0.3);

        // Signal leptons, sorted by pT
        vector<const HEPUtils::Particle*> signalLeptons;
        signalLeptons = electrons;
        signalLeptons.insert(signalLeptons.end(), muons.begin(), muons.end());
        sortByPt(signalLeptons);
        size_t n_leptons = signalLeptons.size();

        // Signal photons, sorted by pT
        vector<const HEPUtils::Particle*> signalPhotons;
        signalPhotons = photons;
        sortByPt(signalPhotons);
        size_t n_photons = signalPhotons.size();

        // Require at least one signal photon and one signal lepton
        if (n_photons < 1 || n_leptons < 1) return;

        // Get leadning lepton and leading photon
        const HEPUtils::Particle* lepton1 = signalLeptons.at(0);
        const HEPUtils::Particle* photon1 = signalPhotons.at(0);

        // Is this an e+gamma or mu+gamma event?
        bool is_egamma = true;
        if (lepton1->abspid() == 13) is_egamma = false;

        // If e+gamma event, require m(e,gamma) > 101.2 
        if (is_egamma)
        {
          double m_egamma = (lepton1->mom() + photon1->mom()).m();
          if (m_egamma < 101.2) return;
        }


        // Require DeltaR(lepton1,photon1) > 0.8
        double dR = deltaR_eta(lepton1->mom(), photon1->mom());
        if (dR < 0.8) return;

        // Require mT > 100 and pTmiss > 120
        double mT = sqrt(2. * lepton1->pT() * pTmiss * ( 1. - std::cos( deltaPhi(lepton1->mom(), pTmissVector) ) ) );
        if (!(mT > 100. && pTmiss > 120.)) return;

        // SR selection variable: HT
        double HT = 0;
        for (const HEPUtils::Jet* jet : jets)
        {
          if (deltaR_eta(jet->mom(), photon1->mom()) > 0.4)
          {
            if (deltaR_eta(jet->mom(), lepton1->mom()) > 0.4)
            {
              HT += jet->pT();
            }
          }
        }

        // SR selection variable: pTgamma
        double pTgamma = photon1->pT();

        // 
        // Fill signal regions
        // 

        // e+gamma SRs
        if (is_egamma)
        {
          if      ( 35 < pTgamma && pTgamma < 200  &&  120 < pTmiss && pTmiss < 200  &&    0 < HT && HT < 100) _counters.at("SR1").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  120 < pTmiss && pTmiss < 200  &&  100 < HT && HT < 400) _counters.at("SR2").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  120 < pTmiss && pTmiss < 200  &&  400 < HT            ) _counters.at("SR3").add_event(event);

          else if ( 35 < pTgamma && pTgamma < 200  &&  200 < pTmiss && pTmiss < 400  &&    0 < HT && HT < 100) _counters.at("SR4").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  200 < pTmiss && pTmiss < 400  &&  100 < HT && HT < 400) _counters.at("SR5").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  200 < pTmiss && pTmiss < 400  &&  400 < HT            ) _counters.at("SR6").add_event(event);

          else if ( 35 < pTgamma && pTgamma < 200  &&  400 < pTmiss                  &&    0 < HT && HT < 100) _counters.at("SR7").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  400 < pTmiss                  &&  100 < HT && HT < 400) _counters.at("SR8").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  400 < pTmiss                  &&  400 < HT            ) _counters.at("SR9").add_event(event);

          else if (200 < pTgamma                   &&  120 < pTmiss && pTmiss < 200  &&    0 < HT && HT < 100) _counters.at("SR10").add_event(event);
          else if (200 < pTgamma                   &&  120 < pTmiss && pTmiss < 200  &&  100 < HT && HT < 400) _counters.at("SR11").add_event(event);
          else if (200 < pTgamma                   &&  120 < pTmiss && pTmiss < 200  &&  400 < HT            ) _counters.at("SR12").add_event(event);

          else if (200 < pTgamma                   &&  200 < pTmiss && pTmiss < 400  &&    0 < HT && HT < 100) _counters.at("SR13").add_event(event);
          else if (200 < pTgamma                   &&  200 < pTmiss && pTmiss < 400  &&  100 < HT && HT < 400) _counters.at("SR14").add_event(event);
          else if (200 < pTgamma                   &&  200 < pTmiss && pTmiss < 400  &&  400 < HT            ) _counters.at("SR15").add_event(event);

          else if (200 < pTgamma                   &&  400 < pTmiss                  &&    0 < HT && HT < 100) _counters.at("SR16").add_event(event);
          else if (200 < pTgamma                   &&  400 < pTmiss                  &&  100 < HT && HT < 400) _counters.at("SR17").add_event(event);
          else if (200 < pTgamma                   &&  400 < pTmiss                  &&  400 < HT            ) _counters.at("SR18").add_event(event);
        }
        // mu+gamma SRs
        else
        {
          if      ( 35 < pTgamma && pTgamma < 200  &&  120 < pTmiss && pTmiss < 200  &&    0 < HT && HT < 100) _counters.at("SR19").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  120 < pTmiss && pTmiss < 200  &&  100 < HT && HT < 400) _counters.at("SR20").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  120 < pTmiss && pTmiss < 200  &&  400 < HT            ) _counters.at("SR21").add_event(event);

          else if ( 35 < pTgamma && pTgamma < 200  &&  200 < pTmiss && pTmiss < 400  &&    0 < HT && HT < 100) _counters.at("SR22").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  200 < pTmiss && pTmiss < 400  &&  100 < HT && HT < 400) _counters.at("SR23").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  200 < pTmiss && pTmiss < 400  &&  400 < HT            ) _counters.at("SR24").add_event(event);

          else if ( 35 < pTgamma && pTgamma < 200  &&  400 < pTmiss                  &&    0 < HT && HT < 100) _counters.at("SR25").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  400 < pTmiss                  &&  100 < HT && HT < 400) _counters.at("SR26").add_event(event);
          else if ( 35 < pTgamma && pTgamma < 200  &&  400 < pTmiss                  &&  400 < HT            ) _counters.at("SR27").add_event(event);

          else if (200 < pTgamma                   &&  120 < pTmiss && pTmiss < 200  &&    0 < HT && HT < 100) _counters.at("SR28").add_event(event);
          else if (200 < pTgamma                   &&  120 < pTmiss && pTmiss < 200  &&  100 < HT && HT < 400) _counters.at("SR29").add_event(event);
          else if (200 < pTgamma                   &&  120 < pTmiss && pTmiss < 200  &&  400 < HT            ) _counters.at("SR30").add_event(event);

          else if (200 < pTgamma                   &&  200 < pTmiss && pTmiss < 400  &&    0 < HT && HT < 100) _counters.at("SR31").add_event(event);
          else if (200 < pTgamma                   &&  200 < pTmiss && pTmiss < 400  &&  100 < HT && HT < 400) _counters.at("SR32").add_event(event);
          else if (200 < pTgamma                   &&  200 < pTmiss && pTmiss < 400  &&  400 < HT            ) _counters.at("SR33").add_event(event);

          else if (200 < pTgamma                   &&  400 < pTmiss                  &&    0 < HT && HT < 100) _counters.at("SR34").add_event(event);
          else if (200 < pTgamma                   &&  400 < pTmiss                  &&  100 < HT && HT < 400) _counters.at("SR35").add_event(event);
          else if (200 < pTgamma                   &&  400 < pTmiss                  &&  400 < HT            ) _counters.at("SR36").add_event(event);
        }

      } // END: run function


      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_1Photon1Lepton_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_1Photon1Lepton_36invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }


      virtual void collect_results()
      {
        add_result(SignalRegionData( _counters.at("SR1"),  153, { 175.0, 14.9 } ));
        add_result(SignalRegionData( _counters.at("SR2"),  275, { 275.4, 49.8 } ));
        add_result(SignalRegionData( _counters.at("SR3"),   67, { 84.75, 19.95 } ));
        add_result(SignalRegionData( _counters.at("SR4"),   32, { 18.36, 2.59 } ));
        add_result(SignalRegionData( _counters.at("SR5"),   46, { 53.26, 10.77 } ));
        add_result(SignalRegionData( _counters.at("SR6"),   32, { 30.57, 8.31 } ));
        add_result(SignalRegionData( _counters.at("SR7"),    1, { 1.370, 0.26 } ));
        add_result(SignalRegionData( _counters.at("SR8"),    1, { 1.223, 0.46 } ));
        add_result(SignalRegionData( _counters.at("SR9"),    4, { 2.961, 0.76 } ));
        add_result(SignalRegionData( _counters.at("SR10"),  10, { 6.620, 1.92 } ));
        add_result(SignalRegionData( _counters.at("SR11"),  21, { 23.03, 6.74 } ));
        add_result(SignalRegionData( _counters.at("SR12"),  14, { 12.35, 3.61 } ));
        add_result(SignalRegionData( _counters.at("SR13"),   6, { 4.712, 1.39 } ));
        add_result(SignalRegionData( _counters.at("SR14"),   9, { 9.406, 3.14 } ));
        add_result(SignalRegionData( _counters.at("SR15"),   4, { 5.399, 1.80 } ));
        add_result(SignalRegionData( _counters.at("SR16"),   0, { 0.4169, 0.19 } ));
        add_result(SignalRegionData( _counters.at("SR17"),   1, { 0.5598, 0.21 } ));
        add_result(SignalRegionData( _counters.at("SR18"),   3, { 0.9010, 0.49 } ));
        add_result(SignalRegionData( _counters.at("SR19"), 308, { 333.9, 37.20 } ));
        add_result(SignalRegionData( _counters.at("SR20"), 491, { 496.4, 89.45 } ));
        add_result(SignalRegionData( _counters.at("SR21"),  85, { 105.1, 25.73 } ));
        add_result(SignalRegionData( _counters.at("SR22"),  32, { 27.92, 3.96 } ));
        add_result(SignalRegionData( _counters.at("SR23"),  64, { 63.84, 12.30 } ));
        add_result(SignalRegionData( _counters.at("SR24"),  45, { 47.55, 13.08 } ));
        add_result(SignalRegionData( _counters.at("SR25"),   1, { 1.252, 0.20 } ));
        add_result(SignalRegionData( _counters.at("SR26"),   1, { 2.556, 1.34 } ));
        add_result(SignalRegionData( _counters.at("SR27"),   5, { 5.522, 2.00 } ));
        add_result(SignalRegionData( _counters.at("SR28"),  12, { 6.620, 2.27 } ));
        add_result(SignalRegionData( _counters.at("SR29"),  23, { 22.26, 7.09 } ));
        add_result(SignalRegionData( _counters.at("SR30"),  20, { 16.02, 4.71 } ));
        add_result(SignalRegionData( _counters.at("SR31"),   4, { 5.101, 1.77 } ));
        add_result(SignalRegionData( _counters.at("SR32"),  12, { 8.689, 3.14 } ));
        add_result(SignalRegionData( _counters.at("SR33"),   7, { 5.713, 1.94 } ));
        add_result(SignalRegionData( _counters.at("SR34"),   1, { 0.7688, 0.39 } ));
        add_result(SignalRegionData( _counters.at("SR35"),   1, { 0.6560, 0.23 } ));
        add_result(SignalRegionData( _counters.at("SR36"),   0, { 0.5598, 0.21 } ));
      }


    protected:
      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_1Photon1Lepton_36invfb)



    //
    // Derived analysis class, where we combine the e+gamma and 
    // mu+gamma SRs, to reduce the SR flip-flopping issue
    //
    class Analysis_CMS_13TeV_1Photon1Lepton_emu_combined_36invfb : public Analysis_CMS_13TeV_1Photon1Lepton_36invfb {

    public:
      Analysis_CMS_13TeV_1Photon1Lepton_emu_combined_36invfb() {
        set_analysis_name("CMS_13TeV_1Photon1Lepton_emu_combined_36invfb");
      }

      virtual void collect_results() {

        // We could of course combine the e+gamma and mu+gamma data once and just 
        // hardcode those numbers here, but doing it explicitly here in the code
        // makes it clear what is going on.
        add_result(SignalRegionData( _counters.at("SR1").combine(_counters.at("SR19")),  153 + 308, { 175.0 + 333.9   , sqrt(pow(14.9,2) + pow(37.20,2)) } ));
        add_result(SignalRegionData( _counters.at("SR2").combine(_counters.at("SR20")),  275 + 491, { 275.4 + 496.4   , sqrt(pow(49.8,2) + pow(89.45,2)) } ));
        add_result(SignalRegionData( _counters.at("SR3").combine(_counters.at("SR21")),  67 + 85,   { 84.75 + 105.1   , sqrt(pow(19.95,2) + pow(25.73,2)) } ));
        add_result(SignalRegionData( _counters.at("SR4").combine(_counters.at("SR22")),  32 + 32,   { 18.36 + 27.92   , sqrt(pow(2.59,2) + pow(3.96,2)) } ));
        add_result(SignalRegionData( _counters.at("SR5").combine(_counters.at("SR23")),  46 + 64,   { 53.26 + 63.84   , sqrt(pow(10.77,2) + pow(12.30,2)) } ));
        add_result(SignalRegionData( _counters.at("SR6").combine(_counters.at("SR24")),  32 + 45,   { 30.57 + 47.55   , sqrt(pow(8.31,2) + pow(13.08,2)) } ));
        add_result(SignalRegionData( _counters.at("SR7").combine(_counters.at("SR25")),  1 + 1,     { 1.370 + 1.252   , sqrt(pow(0.26,2) + pow(0.20,2)) } ));
        add_result(SignalRegionData( _counters.at("SR8").combine(_counters.at("SR26")),  1 + 1,     { 1.223 + 2.556   , sqrt(pow(0.46,2) + pow(1.34,2)) } ));
        add_result(SignalRegionData( _counters.at("SR9").combine(_counters.at("SR27")),  4 + 5,     { 2.961 + 5.522   , sqrt(pow(0.76,2) + pow(2.00,2)) } ));
        add_result(SignalRegionData( _counters.at("SR10").combine(_counters.at("SR28")), 10 + 12,   { 6.620 + 6.620   , sqrt(pow(1.92,2) + pow(2.27,2)) } ));
        add_result(SignalRegionData( _counters.at("SR11").combine(_counters.at("SR29")), 21 + 23,   { 23.03 + 22.26   , sqrt(pow(6.74,2) + pow(7.09,2)) } ));
        add_result(SignalRegionData( _counters.at("SR12").combine(_counters.at("SR30")), 14 + 20,   { 12.35 + 16.02   , sqrt(pow(3.61,2) + pow(4.71,2)) } ));
        add_result(SignalRegionData( _counters.at("SR13").combine(_counters.at("SR31")), 6 + 4,     { 4.712 + 5.101   , sqrt(pow(1.39,2) + pow(1.77,2)) } ));
        add_result(SignalRegionData( _counters.at("SR14").combine(_counters.at("SR32")), 9 + 12,    { 9.406 + 8.689   , sqrt(pow(3.14,2) + pow(3.14,2)) } ));
        add_result(SignalRegionData( _counters.at("SR15").combine(_counters.at("SR33")), 4 + 7,     { 5.399 + 5.713   , sqrt(pow(1.80,2) + pow(1.94,2)) } ));
        add_result(SignalRegionData( _counters.at("SR16").combine(_counters.at("SR34")), 0 + 1,     { 0.4169 + 0.7688 , sqrt(pow(0.19,2) + pow(0.39,2)) } ));
        add_result(SignalRegionData( _counters.at("SR17").combine(_counters.at("SR35")), 1 + 1,     { 0.5598 + 0.6560 , sqrt(pow(0.21,2) + pow(0.23,2)) } ));
        add_result(SignalRegionData( _counters.at("SR18").combine(_counters.at("SR36")), 3 + 0,     { 0.9010 + 0.5598 , sqrt(pow(0.49,2) + pow(0.21,2)) } ));

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_1Photon1Lepton_emu_combined_36invfb)


  }
}
