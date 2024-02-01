///
///  \author Adil Jueid
///  \date 2023 Sep
///
///
///  *********************************************
// Based on the CMS publication https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-21-002/
// Phys. Lett. B 842 (2023) 137460, arXiv:2205.09597 [hep-ex],

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>
#include "SoftDrop.hh"

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"

#define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_CMS_13TeV_0LEP_chargino_VV_VH_137invfb : public Analysis
    {
    private:
      std::map<string, EventCounter> _counters = {
          {"0b-MET-200-250", EventCounter("0b-MET-200-250")},
          {"0b-MET-250-300", EventCounter("0b-MET-250-300")},
          {"0b-MET-300-350", EventCounter("0b-MET-300-350")},
          {"0b-MET-350-400", EventCounter("0b-MET-350-400")},
          {"0b-MET-400-450", EventCounter("0b-MET-400-450")},
          {"0b-MET-450-500", EventCounter("0b-MET-450-500")},
          {"0b-MET-500-600", EventCounter("0b-MET-500-600")},
          {"0b-MET-600-800", EventCounter("0b-MET-600-800")},
          {"0b-MET-800-1200", EventCounter("0b-MET-800-1200")},
          {"WH-MET-200-250", EventCounter("WH-MET-200-250")},
          {"WH-MET-250-300", EventCounter("WH-MET-250-300")},
          {"WH-MET-300-350", EventCounter("WH-MET-300-350")},
          {"WH-MET-350-400", EventCounter("WH-MET-350-400")},
          {"WH-MET-400-450", EventCounter("WH-MET-400-450")},
          {"WH-MET-450-500", EventCounter("WH-MET-450-500")},
          {"WH-MET-500-600", EventCounter("WH-MET-500-600")},
          {"WH-MET-600-900", EventCounter("WH-MET-600-900")},
          {"1W-MET-200-250", EventCounter("1W-MET-200-250")},
          {"1W-MET-250-300", EventCounter("1W-MET-250-300")},
          {"1W-MET-300-350", EventCounter("1W-MET-300-350")},
          {"1W-MET-350-400", EventCounter("1W-MET-350-400")},
          {"1W-MET-400-450", EventCounter("1W-MET-400-450")},
          {"1W-MET-450-500", EventCounter("1W-MET-450-500")},
          {"1W-MET-500-600", EventCounter("1W-MET-500-600")},
          {"1W-MET-600-800", EventCounter("1W-MET-600-800")},
          {"1W-MET-800-1200", EventCounter("1W-MET-800-1200")},
          {"1H-MET-200-250", EventCounter("1H-MET-200-250")},
          {"1H-MET-250-300", EventCounter("1H-MET-250-300")},
          {"1H-MET-300-350", EventCounter("1H-MET-300-350")},
          {"1H-MET-350-400", EventCounter("1H-MET-350-400")},
          {"1H-MET-400-450", EventCounter("1H-MET-400-450")},
          {"1H-MET-450-500", EventCounter("1H-MET-450-500")},
          {"1H-MET-500-600", EventCounter("1H-MET-500-600")},
          {"1H-MET-600-800", EventCounter("1H-MET-600-800")},
          {"1H-MET-800-1200", EventCounter("1H-MET-800-1200")},
      };

      // ofstream cutflowFile;

    public:
      // Required detector sim
      static constexpr const char *detector = "CMS";

      Cutflow _cutflow;

      Analysis_CMS_13TeV_0LEP_chargino_VV_VH_137invfb():
      _cutflow("CMS 0 lepton charginos 13 TeV", {"Electron veto", "Muon veto", "MET>300 GeV", "HT > 300 GeV", "Njets > 2", "Photon veto", "NAK8 > 0", "Delta phi", "NAK8 > 1", "b-veto", "WH SR", "W SR", "H SR"})

      {

        set_analysis_name("CMS_13TeV_0LEP_chargino_VV_VH_137invfb");
        set_luminosity(137.0);
      }

      double findMapValue(map<double, double> effMap, double pt)
      {
        double eff = -1.0;
        for (const auto& pair : effMap)
        {
          if (pt > pair.first)
          {
            eff = pair.second; 
          }
        }
        return eff;
      }

      void run(const HEPUtils::Event *event)
      {

        double met = event->met();

        // Baseline objects
        // Another requirement on electrons and muons are needed to be implemented
        // In other words, the sum of pT of all charged tracks within some R (defined in eq. 1 of https://arxiv.org/pdf/1605.04608.pdf) 
        // excluding the lepton candidate itself
        // needs to be smaller than 10% and 20 % of the electron and muon pT respectively.
        vector<const HEPUtils::Particle *> vetoedElectrons;
        for (const HEPUtils::Particle *electron : event->electrons())
        {
          if ( electron->pT() > 10. && electron->abseta() < 2.5) vetoedElectrons.push_back(electron);
        }
        applyEfficiency(vetoedElectrons, CMS::eff2DEl.at("Generic"));


        // Muons
        vector<const HEPUtils::Particle *> vetoedMuons;
        for (const HEPUtils::Particle *muon : event->muons())
        {
          if ( muon->pT() > 10. && muon->abseta() < 2.4 ) vetoedMuons.push_back(muon);
        }
        applyEfficiency(vetoedMuons, CMS::eff2DMu.at("Generic"));

        // Photons
        vector<const HEPUtils::Particle*> vetoedPhotons;
        for (const HEPUtils::Particle* photon : event->photons())
        {
          if ( photon->pT() > 100. && fabs( photon->eta() ) < 2.4 ) vetoedPhotons.push_back(photon);
        }

        // Need other selection on tracks (to recover also electrons and muons coming from tau decays)

        // Signal objects
        vector<const HEPUtils::Jet *> signalJets;
        vector<const HEPUtils::Jet *> signalBJets;
        double btag = 0.68; 
        double cmisstag = 0.12;
        double misstag = 0.01;
        for ( const HEPUtils::Jet * jet : event->jets("antikt_R04") ) 
        {
          if ( jet->pT() > 30. && fabs( jet->eta() ) < 2.4 )                  signalJets.push_back(jet);
        }
        for ( const HEPUtils::Jet* jet : signalJets ) {
          if ( jet->btag() && random_bool(btag) )         signalBJets.push_back(jet);
          if ( jet->ctag() && random_bool(cmisstag) )     signalBJets.push_back(jet);
          if ( random_bool(misstag) )                     signalBJets.push_back(jet);
        }

//        CMS::applyCSVv2MediumBtagEff(signalBJets);
//        applyEfficiency(signalBJets, CMS::)
//        applyEfficiency(signalBJets, CMS::eff2DBJet.at("CSVv2Medium"));
//        applyBtagMisId(signalJets, signalBJets, CMS::misIDBJet.at("CSVv2Medium"));

        vector<const HEPUtils::Jet *> baselineAK8Jets;
        for ( const HEPUtils::Jet * jet : event->jets("antikt_R08") ) {
          if ( jet->pT() > 200. && fabs( jet->eta() ) < 2.0 && jet->mass() > 50. )   baselineAK8Jets.push_back(jet);
        }

        int nElectrons = vetoedElectrons.size();
        int nMuons     = vetoedMuons.size();
        int nPhotons   = vetoedPhotons.size();
        int nJets      = signalJets.size();
        int nBJets     = signalBJets.size();
        int nAK8Jets   = baselineAK8Jets.size();

        double HT = 0.;
        for ( unsigned int ij=0; ij < signalJets.size(); ij++ ) {
          HT += signalJets[ij]->pT();
        }

        // Initial events
        _cutflow.fillinit();
        if ( nElectrons > 0 ) return;
        _cutflow.fill(1);

        if ( nMuons > 0 ) return;
        _cutflow.fill(2);

        if ( met <= 200. ) return;
        _cutflow.fill(3);

        if ( HT <= 300. ) return;
        _cutflow.fill(4);

        if ( nJets < 2 || nJets > 6 ) return;
        _cutflow.fill(5);

        if ( nPhotons > 0 ) return;
        _cutflow.fill(6);

        if ( nAK8Jets == 0 ) return;
        _cutflow.fill(7);

        // Now deltaphi cuts
        // CMS require deltaphi(pmiss, j1) > 1.5, deltaphi(pmiss, j2) > 0.5, deltaphi(pmiss, j3, j4) > 3
        //             deltaphi(pmiss, AK8) > 1.5 and deltaphi(pmiss, AK8_2) > 0.5
        HEPUtils::P4  pmiss = event->missingmom();
        double deltaPhi_j3 = 9999.0; 
        double deltaPhi_j4 = 9999.0;
        double deltaPhi_J2 = 9999.0;
        double deltaPhi_j1=signalJets.at(0)->mom().deltaPhi(pmiss);
        double deltaPhi_j2=signalJets.at(1)->mom().deltaPhi(pmiss);
        if ( nJets > 2 ) deltaPhi_j3=signalJets.at(2)->mom().deltaPhi(pmiss);
        if ( nJets > 3 ) deltaPhi_j4=signalJets.at(3)->mom().deltaPhi(pmiss);
        double deltaPhi_J1=baselineAK8Jets.at(0)->mom().deltaPhi(pmiss);
        if ( nAK8Jets > 1 )  deltaPhi_J2=baselineAK8Jets.at(1)->mom().deltaPhi(pmiss);
        bool deltaphi_cuts = false;
        if ( deltaPhi_j1 > 1.5 && deltaPhi_j2 > 0.5 && deltaPhi_J1 > 1.5 ) deltaphi_cuts = true;
        if ( deltaPhi_j3 > 0.3 ) deltaphi_cuts = true;
        if ( deltaPhi_j4 > 0.3 ) deltaphi_cuts = true;      
        if ( deltaPhi_J2 > 0.5 ) deltaphi_cuts = true;

        if ( !deltaphi_cuts ) return;
        _cutflow.fill(8);

        if ( nAK8Jets < 2 ) return;
        _cutflow.fill(9);

      // Defining the signal regions
      // @todo use realistic (pT, eta) maps when available
      const std::vector<double>  a = {0, 200., 300., 100000.};
      const std::vector<double>  b_W = {0., 1.0, 0.41};
      const std::vector<double>  b_H = {0., 0.0, 0.54};
      HEPUtils::BinnedFn1D<double> _eff1dW(a, b_W);
      HEPUtils::BinnedFn1D<double> _eff1dH(a, b_H);
      vector<const FJNS::PseudoJet*> SDWJets;
      double beta = 0.0;
      double z_cut = 0.1;
      double RSD  = 0.8;
      FJNS::contrib::SoftDrop sd(beta, z_cut, RSD);
      for ( const HEPUtils::Jet* jet : baselineAK8Jets ) {
        bool isW=has_tag(_eff1dW, jet->pT());
        if ( !isW ) continue;
        FJNS::PseudoJet pj = jet->pseudojet();
        FJNS::PseudoJet groomed_jet = sd(pj);
        if ( groomed_jet.m() <= 65.0 || groomed_jet.m() >= 105.0 ) continue;
        SDWJets.push_back(&groomed_jet);
       }
       int nWJets = SDWJets.size();
       bool ZeroB_SR = ( nBJets == 0 ) && ( nWJets >= 2 );
       if ( ZeroB_SR ) _cutflow.fill(10);

      // Signal regions with at least one b-tagged jet
      // Higgs jet is defined as a SD AK 8 jet with pT > 200 GeV and m in ]75, 140[ GeV
      // Higgs jet is also defined to contain at least one b-tagged jet, i.e. Delta R (b, H) < 0.8
      vector <const FJNS::PseudoJet*> SDHJets;
      if ( nBJets > 0 ) {
        for ( unsigned int ib=0; ib < signalBJets.size(); ib++ ) {
          for ( unsigned int IJ=0; IJ < baselineAK8Jets.size(); IJ++ ) {
            double dR = signalBJets.at(ib)->mom().deltaR_eta(baselineAK8Jets.at(IJ)->mom());
            if ( dR >= 0.8 ) continue;
            bool isH=has_tag(_eff1dH, baselineAK8Jets[IJ]->pT());
            if ( !isH ) continue;
            FJNS::PseudoJet pj = baselineAK8Jets[IJ]->pseudojet();
            FJNS::PseudoJet groomed_jet = sd(pj);
            if ( groomed_jet.m() <= 75.0 || groomed_jet.m() >= 140.0 ) continue;
            SDHJets.push_back(&groomed_jet);            
          }
        }
      }

      int nHJets = SDHJets.size();
      bool WH_SR = ( nBJets > 0 && nHJets > 0 && nWJets > 0 );
      bool W_SR  = ( nBJets > 0 && nHJets == 0 && nWJets > 0 );
      bool H_SR  = ( nBJets > 0 && nHJets > 0 && nWJets == 0 );

      if ( WH_SR ) _cutflow.fill(11);  // WH SR
      if (  W_SR ) _cutflow.fill(12);  // W  SR
      if (  H_SR ) _cutflow.fill(13);  // H  SR


      if ( ZeroB_SR ) {
        if  ( met > 200. && met <= 250. )   _counters.at("0b-MET-200-250").add_event(event);
        if  ( met > 250. && met <= 300. )   _counters.at("0b-MET-250-300").add_event(event);
        if  ( met > 300. && met <= 350. )   _counters.at("0b-MET-300-350").add_event(event);
        if  ( met > 350. && met <= 400. )   _counters.at("0b-MET-350-400").add_event(event);
        if  ( met > 400. && met <= 450. )   _counters.at("0b-MET-400-450").add_event(event);
        if  ( met > 450. && met <= 500. )   _counters.at("0b-MET-450-500").add_event(event);
        if  ( met > 500. && met <= 600. )   _counters.at("0b-MET-500-600").add_event(event);
        if  ( met > 600. && met <= 800. )   _counters.at("0b-MET-600-800").add_event(event);
        if  ( met > 800. && met <= 1200. )  _counters.at("0b-MET-800-1200").add_event(event);
      }

      if ( W_SR ) {
        if  ( met > 200. && met <= 250. )   _counters.at("1W-MET-200-250").add_event(event);
        if  ( met > 250. && met <= 300. )   _counters.at("1W-MET-250-300").add_event(event);
        if  ( met > 300. && met <= 350. )   _counters.at("1W-MET-300-350").add_event(event);
        if  ( met > 350. && met <= 400. )   _counters.at("1W-MET-350-400").add_event(event);
        if  ( met > 400. && met <= 450. )   _counters.at("1W-MET-400-450").add_event(event);
        if  ( met > 450. && met <= 500. )   _counters.at("1W-MET-450-500").add_event(event);
        if  ( met > 500. && met <= 600. )   _counters.at("1W-MET-500-600").add_event(event);
        if  ( met > 600. && met <= 800. )   _counters.at("1W-MET-600-800").add_event(event);
        if  ( met > 800. && met <= 1200. )  _counters.at("1W-MET-800-1200").add_event(event);
      }

      if ( WH_SR ) {
        if  ( met > 200. && met <= 250. )   _counters.at("WH-MET-200-250").add_event(event);
        if  ( met > 250. && met <= 300. )   _counters.at("WH-MET-250-300").add_event(event);
        if  ( met > 300. && met <= 350. )   _counters.at("WH-MET-300-350").add_event(event);
        if  ( met > 350. && met <= 400. )   _counters.at("WH-MET-350-400").add_event(event);
        if  ( met > 400. && met <= 450. )   _counters.at("WH-MET-400-450").add_event(event);
        if  ( met > 450. && met <= 500. )   _counters.at("WH-MET-450-500").add_event(event);
        if  ( met > 500. && met <= 600. )   _counters.at("WH-MET-500-600").add_event(event);
        if  ( met > 600. && met <= 900. )   _counters.at("WH-MET-600-900").add_event(event);
      }

      if ( H_SR ) {
        if  ( met > 200. && met <= 250. )   _counters.at("1H-MET-200-250").add_event(event);
        if  ( met > 250. && met <= 300. )   _counters.at("1H-MET-250-300").add_event(event);
        if  ( met > 300. && met <= 350. )   _counters.at("1H-MET-300-350").add_event(event);
        if  ( met > 350. && met <= 400. )   _counters.at("1H-MET-350-400").add_event(event);
        if  ( met > 400. && met <= 450. )   _counters.at("1H-MET-400-450").add_event(event);
        if  ( met > 450. && met <= 500. )   _counters.at("1H-MET-450-500").add_event(event);
        if  ( met > 500. && met <= 600. )   _counters.at("1H-MET-500-600").add_event(event);
        if  ( met > 600. && met <= 800. )   _counters.at("1H-MET-600-800").add_event(event);
        if  ( met > 800. && met <= 1200. )  _counters.at("1H-MET-800-1200").add_event(event);
      }
    }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis *other)
      {
        const Analysis_CMS_13TeV_0LEP_chargino_VV_VH_137invfb *specificOther = dynamic_cast<const Analysis_CMS_13TeV_0LEP_chargino_VV_VH_137invfb *>(other);

        for (auto &pair : _counters)
        {
          pair.second += specificOther->_counters.at(pair.first);
        }
      }

      void collect_results()
      {

        #ifdef CHECK_CUTFLOW  
          cout << _cutflow << endl;
          // Note: The EventCount::sum() call below gives the raw MC event count.
          //       Use weight_sum() to get the sum of event weights.
          for (auto& pair : _counters) {
              cout << pair.first << "\t" << pair.second.sum() << endl;
          }
        #endif
        add_result(SignalRegionData(_counters.at("0b-MET-200-250"),  82.0, {88.139, 9.2357}));
        add_result(SignalRegionData(_counters.at("0b-MET-250-300"),  48.0, {48.165, 6.7386}));
        add_result(SignalRegionData(_counters.at("0b-MET-300-350"),  24.0, {25.378, 4.4114}));
        add_result(SignalRegionData(_counters.at("0b-MET-350-400"),  9.0,  {15.523, 3.7379}));
        add_result(SignalRegionData(_counters.at("0b-MET-400-450"),  8.0,  {12.258, 3.1539}));
        add_result(SignalRegionData(_counters.at("0b-MET-450-500"),  6.0,  {7.8949, 2.1316}));
        add_result(SignalRegionData(_counters.at("0b-MET-500-600"),  9.0,  {9.5994, 2.7618}));
        add_result(SignalRegionData(_counters.at("0b-MET-600-800"),  6.0,  {6.1672, 2.2207}));
        add_result(SignalRegionData(_counters.at("0b-MET-800-1200"), 3.0,  {0.8677, 0.7351}));
        add_result(SignalRegionData(_counters.at("WH-MET-200-250"),  32.0, {34.897, 5.4092}));
        add_result(SignalRegionData(_counters.at("WH-MET-250-300"),  13.0, {16.169, 3.2782}));
        add_result(SignalRegionData(_counters.at("WH-MET-300-350"),  8.0,  {5.1953, 1.2923}));
        add_result(SignalRegionData(_counters.at("WH-MET-350-400"),  8.0,  {3.1096, 1.3459}));
        add_result(SignalRegionData(_counters.at("WH-MET-400-450"),  4.0,  {2.9124, 1.1509}));
        add_result(SignalRegionData(_counters.at("WH-MET-450-500"),  3.0,  {1.2895, 0.62421}));
        add_result(SignalRegionData(_counters.at("WH-MET-500-600"),  1.0,  {1.1892, 1.12000}));
        add_result(SignalRegionData(_counters.at("WH-MET-600-900"),  1.0,  {1.0161, 1.09000}));
        add_result(SignalRegionData(_counters.at("1W-MET-200-250"),  680.0, {749.41, 46.066}));
        add_result(SignalRegionData(_counters.at("1W-MET-250-300"),  312.0, {332.41, 32.533}));
        add_result(SignalRegionData(_counters.at("1W-MET-300-350"),  175.0, {176.44, 13.463}));
        add_result(SignalRegionData(_counters.at("1W-MET-350-400"),  95.0,  {99.358, 9.8858}));
        add_result(SignalRegionData(_counters.at("1W-MET-400-450"),  63.0,  {60.705, 6.9053}));
        add_result(SignalRegionData(_counters.at("1W-MET-450-500"),  23.0,  {34.733, 4.6856}));
        add_result(SignalRegionData(_counters.at("1W-MET-500-600"),  28.0,  {26.873, 3.6029}));
        add_result(SignalRegionData(_counters.at("1W-MET-600-800"),  17.0,  {18.835, 3.2202}));
        add_result(SignalRegionData(_counters.at("1W-MET-800-1200"), 4.0,   {3.5228, 1.7000}));
        add_result(SignalRegionData(_counters.at("1H-MET-200-250"),  1212.0, {1244.1, 61.086}));
        add_result(SignalRegionData(_counters.at("1H-MET-250-300"),  563.0, {555.26, 27.194}));
        add_result(SignalRegionData(_counters.at("1H-MET-300-350"),  282.0, {310.59, 19.810}));
        add_result(SignalRegionData(_counters.at("1H-MET-350-400"),  160.0,  {156.06, 13.592}));
        add_result(SignalRegionData(_counters.at("1H-MET-400-450"),  115.0,  {92.935, 10.050}));
        add_result(SignalRegionData(_counters.at("1H-MET-450-500"),   60.0,  {77.114, 7.9706}));
        add_result(SignalRegionData(_counters.at("1H-MET-500-600"),   65.0,  {55.800, 7.1271}));
        add_result(SignalRegionData(_counters.at("1H-MET-600-800"),   39.0,  {30.174, 4.7484}));
        add_result(SignalRegionData(_counters.at("1H-MET-800-1200"),   8.0,  {7.5232, 2.4987}));

      }

    protected:
      void analysis_specific_reset()
      {
        for (auto &pair : _counters)
        {
          pair.second.reset();
        }

      }
    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_0LEP_chargino_VV_VH_137invfb)

  }
}
