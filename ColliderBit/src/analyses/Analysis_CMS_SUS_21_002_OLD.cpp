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

// #define CHECK_CUTFLOW

using namespace std;

// Renamed from: 
//        Analysis_CMS_13TeV_0LEP_chargino_VV_VH_137invfb_OLD


namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_CMS_SUS_21_002_OLD : public Analysis
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

      Analysis_CMS_SUS_21_002_OLD():
      _cutflow("CMS 0 lepton charginos 13 TeV", {"Electron veto", "Muon veto", "MET>300 GeV", "HT > 300 GeV", "Njets > 2", "Photon veto", "NAK8 > 0", "Delta phi", "NAK8 > 1", "b-veto", "WH SR", "W SR", "H SR"})

      {
        set_analysis_name("CMS_SUS_21_002_OLD");
        set_luminosity(137.0);
      }

      // Commented out for now since it's not used.
      // double findMapValue(map<double, double> effMap, double pt)
      // {
      //   double eff = -1.0;
      //   for (const auto& pair : effMap)
      //   {
      //     if (pt > pair.first)
      //     {
      //       eff = pair.second; 
      //     }
      //   }
      //   return eff;
      // }

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

        // CMS::applyCSVv2MediumBtagEff(signalBJets);
        // applyEfficiency(signalBJets, CMS::)
        // applyEfficiency(signalBJets, CMS::eff2DBJet.at("CSVv2Medium"));
        // applyBtagMisId(signalJets, signalBJets, CMS::misIDBJet.at("CSVv2Medium"));

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
        const std::vector<double>  a = {0, 200., 300., DBL_MAX};
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

      virtual void collect_results()
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

        // Background uncertainty covariance matrix from the ROOT file available at
        // https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-21-002/
        static const vector< vector<double> > BKGCOV = {
          {  9.833e+01,  3.216e+01,  1.837e+01,  1.123e+01,  1.047e+01,  6.944e+00,  1.011e+01,  7.588e+00,  1.657e+00,  6.130e-01,  1.880e+00,  3.344e-01,  4.448e-02, -2.987e-01,  2.694e-01,  1.260e-01,  5.901e-02,  9.748e-01,  2.539e+00,  1.636e+00,  5.280e-01,  2.268e+00,  5.849e-01,  7.310e-01,  2.262e-01, -4.796e-02,  2.988e+01,  1.016e+01,  3.569e+00,  3.200e+00,  2.509e+00,  2.515e-01, -9.975e-01, -6.538e-01, -5.628e-02},
          {  3.216e+01,  4.038e+01,  1.311e+01,  8.458e+00,  7.240e+00,  5.411e+00,  7.797e+00,  6.135e+00,  1.381e+00,  6.624e-02,  6.118e-01, -4.265e-02,  1.349e-01, -4.382e-02,  3.364e-02, -3.717e-02,  1.387e-01, -3.834e+00, -6.039e-01, -7.556e-02,  6.097e-01, -1.106e+00,  1.309e+00, -1.334e-01, -1.463e-01, -1.022e-01,  1.844e+01,  1.374e+00, -2.235e+00, -2.994e-01, -1.966e+00, -3.717e-01, -9.804e-01, -8.624e-01, -2.096e-02},
          {  1.837e+01,  1.311e+01,  1.640e+01,  5.690e+00,  5.051e+00,  4.057e+00,  5.685e+00,  4.743e+00,  9.502e-01,  4.510e-02,  2.570e-01, -8.089e-02, -6.037e-02, -9.574e-02,  5.896e-02,  2.698e-02, -3.851e-03, -1.905e+00,  2.467e+00, -1.072e+00,  4.551e-01, -5.938e-01,  2.695e-01,  8.580e-02, -1.648e-01, -6.158e-02,  7.945e+00,  4.261e+00, -1.647e+00, -7.262e-01,  5.010e-01, -4.873e-01, -3.370e-01, -1.812e-01, -1.045e-01},
          {  1.123e+01,  8.458e+00,  5.690e+00,  1.164e+01,  3.719e+00,  2.899e+00,  3.907e+00,  3.276e+00,  7.573e-01,  7.866e-01,  2.307e-01, -6.225e-02,  6.965e-02, -6.044e-02,  5.656e-02,  3.464e-02,  4.602e-02,  4.640e+00,  2.660e+00,  3.392e-01,  1.088e+00,  5.405e-02,  7.109e-01, -1.490e-03, -1.955e-01, -9.825e-02,  4.690e+00,  6.216e-01, -1.148e+00, -8.757e-02, -1.337e-01,  1.582e-01, -8.644e-01, -1.001e-01, -3.278e-01},
          {  1.047e+01,  7.240e+00,  5.051e+00,  3.719e+00,  8.706e+00,  2.804e+00,  3.636e+00,  3.093e+00,  7.173e-01,  4.841e-01,  2.984e-01,  1.013e-01,  6.718e-02, -7.578e-02,  5.297e-02,  6.711e-03,  3.982e-02, -2.558e+00, -1.555e-01,  4.498e-01,  3.620e-01, -4.894e-01,  5.691e-01,  1.269e-01, -2.423e-01, -1.769e-02,  6.649e+00,  8.477e-01, -1.073e+00,  1.894e-01,  2.055e-01, -2.433e-01, -1.080e+00,  1.479e-01, -6.933e-02},
          {  6.944e+00,  5.411e+00,  4.057e+00,  2.899e+00,  2.804e+00,  4.528e+00,  2.959e+00,  2.433e+00,  5.517e-01, -1.301e-01,  2.227e-02, -9.328e-03,  1.868e-02, -7.923e-03,  6.328e-02, -1.397e-02,  2.530e-02, -2.935e+00, -5.991e-01,  2.816e-01,  3.168e-01, -9.581e-02,  2.952e-01, -7.864e-02,  1.292e-01, -4.261e-02,  5.991e+00,  2.029e+00, -2.288e-01,  1.814e-01,  4.744e-01, -1.574e-02, -7.158e-04,  1.049e-01, -2.506e-01},
          {  1.011e+01,  7.797e+00,  5.685e+00,  3.907e+00,  3.636e+00,  2.959e+00,  7.383e+00,  3.490e+00,  7.865e-01,  1.086e-01,  1.608e-01, -7.429e-02,  7.812e-02, -1.358e-01,  2.560e-02, -6.686e-03,  5.997e-02, -5.182e-01,  1.447e+00, -1.386e-01,  6.158e-01, -1.525e-01,  1.692e-01, -2.401e-01, -8.024e-02,  1.439e-02,  8.471e+00,  1.040e+00, -8.238e-01,  5.709e-01,  6.653e-02, -8.294e-01, -5.594e-01, -7.201e-02, -2.554e-01},
          {  7.588e+00,  6.135e+00,  4.743e+00,  3.276e+00,  3.093e+00,  2.433e+00,  3.490e+00,  4.744e+00,  6.724e-01,  2.596e-01,  1.621e-01,  6.022e-02,  4.793e-02,  1.545e-03,  5.461e-02, -2.067e-03,  3.570e-02,  8.978e-01,  2.018e+00,  4.058e-01,  9.986e-01, -2.130e-01,  1.522e-01,  4.763e-02, -1.076e-01,  2.424e-02,  3.406e+00,  6.287e-01, -1.064e+00,  8.259e-01,  5.400e-01, -4.979e-01, -4.912e-01, -2.559e-01, -1.470e-01},
          {  1.657e+00,  1.381e+00,  9.502e-01,  7.573e-01,  7.173e-01,  5.517e-01,  7.865e-01,  6.724e-01,  3.645e-01,  6.398e-02,  1.307e-01,  9.032e-03,  3.610e-02, -1.228e-02,  1.525e-02, -9.855e-04,  1.887e-02,  4.529e-01,  5.710e-01,  3.177e-01,  2.693e-01, -8.758e-02, -2.391e-02,  3.330e-02, -1.968e-03,  1.195e-02,  7.086e-01,  2.793e-02,  1.750e-01, -2.323e-01,  1.188e-01, -1.383e-01, -1.740e-01, -2.560e-02, -3.138e-02},
          {  6.130e-01,  6.624e-02,  4.510e-02,  7.866e-01,  4.841e-01, -1.301e-01,  1.086e-01,  2.596e-01,  6.398e-02,  3.389e+01,  1.695e-01,  3.170e-01, -9.295e-02,  1.799e-01,  9.769e-02,  1.268e-01,  1.382e-01,  3.069e+01,  1.109e+01,  5.443e+00,  3.550e+00,  2.419e+00,  1.081e+00,  2.283e+00,  1.550e+00,  1.925e-01,  1.964e+01,  7.697e+00,  2.251e+00, -4.525e-02,  3.601e+00,  3.405e+00,  1.726e+00,  7.588e-01,  6.519e-01},
          {  1.880e+00,  6.118e-01,  2.570e-01,  2.307e-01,  2.984e-01,  2.227e-02,  1.608e-01,  1.621e-01,  1.307e-01,  1.695e-01,  1.065e+01,  2.725e-01, -6.522e-02,  1.548e-01,  1.478e-01,  9.862e-03,  9.553e-02,  7.679e+00,  4.021e+00,  2.433e+00, -1.328e-01,  5.552e-01,  7.123e-02,  5.451e-01, -3.091e-02,  2.459e-01,  7.697e+00,  3.225e+00,  3.034e+00,  5.422e-01,  4.536e-01,  5.774e-01,  6.473e-01,  3.936e-01,  2.929e-01},
          {  3.344e-01, -4.265e-02, -8.089e-02, -6.225e-02,  1.013e-01, -9.328e-03, -7.429e-02,  6.022e-02,  9.032e-03,  3.170e-01,  2.725e-01,  1.569e+00,  6.887e-02,  3.188e-02,  4.178e-02,  2.905e-02,  2.563e-02,  5.744e+00,  3.890e+00,  1.481e+00,  6.228e-01,  6.870e-01,  4.105e-01,  2.240e-01,  2.206e-01,  1.153e-01,  4.737e+00,  1.506e+00,  1.496e+00,  5.007e-01,  5.180e-01,  3.730e-01,  5.800e-02, -1.421e-02,  3.510e-02},
          {  4.448e-02,  1.349e-01, -6.037e-02,  6.965e-02,  6.718e-02,  1.868e-02,  7.812e-02,  4.793e-02,  3.610e-02, -9.295e-02, -6.522e-02,  6.887e-02,  1.551e+00, -2.580e-02,  1.736e-02,  1.262e-02,  5.626e-03,  3.126e+00,  1.117e+00,  8.714e-01,  4.985e-01,  3.110e-01,  3.572e-02,  1.403e-01, -5.539e-02,  3.444e-02,  2.197e+00,  6.843e-01,  4.186e-01,  5.209e-02,  3.201e-01, -1.950e-01,  1.234e-01,  1.434e-02,  4.487e-02},
          { -2.987e-01, -4.382e-02, -9.574e-02, -6.044e-02, -7.578e-02, -7.923e-03, -1.358e-01,  1.545e-03, -1.228e-02,  1.799e-01,  1.548e-01,  3.188e-02, -2.580e-02,  1.367e+00,  8.442e-02,  2.875e-02,  9.687e-05,  1.335e+00,  1.350e+00,  5.337e-01,  1.323e-02, -4.483e-02,  8.300e-02, -1.147e-02, -5.401e-02,  2.307e-02,  1.808e+00,  8.043e-01,  7.381e-01,  2.077e-01,  3.349e-01,  2.752e-01,  1.078e-02, -7.139e-02,  6.289e-02},
          {  2.694e-01,  3.364e-02,  5.896e-02,  5.656e-02,  5.297e-02,  6.328e-02,  2.560e-02,  5.461e-02,  1.525e-02,  9.769e-02,  1.478e-01,  4.178e-02,  1.736e-02,  8.442e-02,  4.210e-01,  1.788e-02,  9.836e-03,  1.847e+00,  6.806e-01,  4.735e-01,  2.982e-01,  4.273e-02,  3.106e-02,  1.110e-01,  1.134e-01,  3.080e-02, -1.615e-01,  3.396e-01,  5.884e-01, -3.695e-01,  1.059e-01,  1.665e-01,  1.077e-01, -1.459e-02, -1.888e-02},
          {  1.260e-01, -3.717e-02,  2.698e-02,  3.464e-02,  6.711e-03, -1.397e-02, -6.686e-03, -2.067e-03, -9.855e-04,  1.268e-01,  9.862e-03,  2.905e-02,  1.262e-02,  2.875e-02,  1.788e-02,  1.963e-01,  7.539e-03,  2.338e+00,  8.413e-01,  3.462e-01,  1.953e-01,  1.892e-01,  1.745e-01,  1.325e-01,  7.361e-02,  2.034e-02,  8.974e-01,  4.166e-01, -4.042e-02,  2.688e-01,  1.929e-01,  1.594e-01, -9.120e-03, -5.394e-03, -3.052e-02},
          {  5.901e-02,  1.387e-01, -3.851e-03,  4.602e-02,  3.982e-02,  2.530e-02,  5.997e-02,  3.570e-02,  1.887e-02,  1.382e-01,  9.553e-02,  2.563e-02,  5.626e-03,  9.687e-05,  9.836e-03,  7.539e-03,  1.802e-01,  1.808e+00,  7.207e-01,  3.075e-01,  1.381e-01,  2.307e-01,  1.446e-01,  1.177e-01,  9.770e-02,  1.878e-02,  1.926e+00,  6.131e-01,  1.384e-01,  1.658e-01,  1.922e-01,  1.862e-01,  4.945e-02,  6.610e-02,  8.595e-04},
          {  9.748e-01, -3.834e+00, -1.905e+00,  4.640e+00, -2.558e+00, -2.935e+00, -5.182e-01,  8.978e-01,  4.529e-01,  3.069e+01,  7.679e+00,  5.744e+00,  3.126e+00,  1.335e+00,  1.847e+00,  2.338e+00,  1.808e+00,  2.824e+03,  3.024e+02,  1.459e+02,  9.754e+01,  4.589e+01,  4.353e+01,  3.050e+01,  1.937e+01,  7.697e+00, -8.877e+01, -6.070e+00, -1.386e+01, -1.259e+00, -4.646e+00,  8.539e+00,  2.618e+00,  1.652e+00, -1.745e+00},
          {  2.539e+00, -6.039e-01,  2.467e+00,  2.660e+00, -1.555e-01, -5.991e-01,  1.447e+00,  2.018e+00,  5.710e-01,  1.109e+01,  4.021e+00,  3.890e+00,  1.117e+00,  1.350e+00,  6.806e-01,  8.413e-01,  7.207e-01,  3.024e+02,  1.042e+03,  7.540e+01,  2.747e+01,  2.751e+01,  1.590e+01,  1.916e+01,  5.982e+00,  3.532e+00,  8.649e+00,  4.793e+01, -1.678e+01, -3.978e+00,  8.847e+00, -1.657e+00,  3.425e-01, -4.205e+00, -2.627e+00},
          {  1.636e+00, -7.556e-02, -1.072e+00,  3.392e-01,  4.498e-01,  2.816e-01, -1.386e-01,  4.058e-01,  3.177e-01,  5.443e+00,  2.433e+00,  1.481e+00,  8.714e-01,  5.337e-01,  4.735e-01,  3.462e-01,  3.075e-01,  1.459e+02,  7.540e+01,  1.858e+02,  9.442e+00,  8.573e+00,  7.382e+00,  7.502e+00,  4.335e+00,  1.337e+00,  2.423e+01,  1.239e+01,  8.685e+00, -4.708e-01,  5.850e-02,  4.224e+00,  4.170e+00,  1.368e+00,  8.123e-01},
          {  5.280e-01,  6.097e-01,  4.551e-01,  1.088e+00,  3.620e-01,  3.168e-01,  6.158e-01,  9.986e-01,  2.693e-01,  3.550e+00, -1.328e-01,  6.228e-01,  4.985e-01,  1.323e-02,  2.982e-01,  1.953e-01,  1.381e-01,  9.754e+01,  2.747e+01,  9.442e+00,  8.524e+01,  2.010e+00,  4.188e+00,  4.536e+00,  2.028e+00,  5.111e-01,  9.498e+00,  4.248e+00,  6.380e+00, -1.649e+00, -1.645e+00, -8.373e-01,  3.996e-01,  5.892e-01, -4.721e-01},
          {  2.268e+00, -1.106e+00, -5.938e-01,  5.405e-02, -4.894e-01, -9.581e-02, -1.525e-01, -2.130e-01, -8.758e-02,  2.419e+00,  5.552e-01,  6.870e-01,  3.110e-01, -4.483e-02,  4.273e-02,  1.892e-01,  2.307e-01,  4.589e+01,  2.751e+01,  8.573e+00,  2.010e+00,  5.121e+01,  2.734e+00,  3.613e+00,  1.028e+00,  6.643e-01,  2.763e+01,  8.954e+00,  5.692e+00,  6.059e+00,  6.030e-01,  4.594e-01,  2.034e+00,  1.014e+00, -9.588e-02},
          {  5.849e-01,  1.309e+00,  2.695e-01,  7.109e-01,  5.691e-01,  2.952e-01,  1.692e-01,  1.522e-01, -2.391e-02,  1.081e+00,  7.123e-02,  4.105e-01,  3.572e-02,  8.300e-02,  3.106e-02,  1.745e-01,  1.446e-01,  4.353e+01,  1.590e+01,  7.382e+00,  4.188e+00,  2.734e+00,  2.173e+01,  2.284e+00,  1.969e+00,  4.468e-01, -4.314e+00, -1.931e+00, -1.364e+00, -1.428e+00, -1.213e+00,  1.769e-01, -1.313e+00, -8.547e-02, -1.523e-01},
          {  7.310e-01, -1.334e-01,  8.580e-02, -1.490e-03,  1.269e-01, -7.864e-02, -2.401e-01,  4.763e-02,  3.330e-02,  2.283e+00,  5.451e-01,  2.240e-01,  1.403e-01, -1.147e-02,  1.110e-01,  1.325e-01,  1.177e-01,  3.050e+01,  1.916e+01,  7.502e+00,  4.536e+00,  3.613e+00,  2.284e+00,  1.423e+01,  1.342e+00,  4.415e-01, -1.221e+01, -1.069e+00,  5.499e-02,  6.887e-01,  1.233e+00, -9.276e-01, -1.258e-01, -2.687e-01, -3.582e-01},
          {  2.262e-01, -1.463e-01, -1.648e-01, -1.955e-01, -2.423e-01,  1.292e-01, -8.024e-02, -1.076e-01, -1.968e-03,  1.550e+00, -3.091e-02,  2.206e-01, -5.539e-02, -5.401e-02,  1.134e-01,  7.361e-02,  9.770e-02,  1.937e+01,  5.982e+00,  4.335e+00,  2.028e+00,  1.028e+00,  1.969e+00,  1.342e+00,  1.092e+01,  2.084e-01,  7.471e+00, -1.163e+00,  1.286e+00, -7.159e-01, -1.057e+00, -6.688e-02, -1.391e-01,  2.553e-01,  3.457e-02},
          { -4.796e-02, -1.022e-01, -6.158e-02, -9.825e-02, -1.769e-02, -4.261e-02,  1.439e-02,  2.424e-02,  1.195e-02,  1.925e-01,  2.459e-01,  1.153e-01,  3.444e-02,  2.307e-02,  3.080e-02,  2.034e-02,  1.878e-02,  7.697e+00,  3.532e+00,  1.337e+00,  5.111e-01,  6.643e-01,  4.468e-01,  4.415e-01,  2.084e-01,  1.022e+00, -3.246e-01, -1.393e+00, -3.462e-02,  6.254e-02,  3.782e-02, -1.491e-01, -2.556e-01,  9.459e-02,  1.139e-03},
          {  2.988e+01,  1.844e+01,  7.945e+00,  4.690e+00,  6.649e+00,  5.991e+00,  8.471e+00,  3.406e+00,  7.086e-01,  1.964e+01,  7.697e+00,  4.737e+00,  2.197e+00,  1.808e+00, -1.615e-01,  8.974e-01,  1.926e+00, -8.877e+01,  8.649e+00,  2.423e+01,  9.498e+00,  2.763e+01, -4.314e+00, -1.221e+01,  7.471e+00, -3.246e-01,  3.807e+03,  4.977e+02,  2.248e+02,  1.486e+02,  8.531e+01,  1.086e+02,  7.407e+01,  3.843e+01,  1.034e+01},
          {  1.016e+01,  1.374e+00,  4.261e+00,  6.216e-01,  8.477e-01,  2.029e+00,  1.040e+00,  6.287e-01,  2.793e-02,  7.697e+00,  3.225e+00,  1.506e+00,  6.843e-01,  8.043e-01,  3.396e-01,  4.166e-01,  6.131e-01, -6.070e+00,  4.793e+01,  1.239e+01,  4.248e+00,  8.954e+00, -1.931e+00, -1.069e+00, -1.163e+00, -1.393e+00,  4.977e+02,  8.367e+02,  1.077e+02,  4.491e+01,  3.743e+01,  4.234e+01,  2.289e+01,  1.565e+01,  1.150e+00},
          {  3.569e+00, -2.235e+00, -1.647e+00, -1.148e+00, -1.073e+00, -2.288e-01, -8.238e-01, -1.064e+00,  1.750e-01,  2.251e+00,  3.034e+00,  1.496e+00,  4.186e-01,  7.381e-01,  5.884e-01, -4.042e-02,  1.384e-01, -1.386e+01, -1.678e+01,  8.685e+00,  6.380e+00,  5.692e+00, -1.364e+00,  5.499e-02,  1.286e+00, -3.462e-02,  2.248e+02,  1.077e+02,  3.615e+02,  3.131e+01,  2.019e+01,  2.378e+01,  1.686e+01,  7.598e+00,  2.951e+00},
          {  3.200e+00, -2.994e-01, -7.262e-01, -8.757e-02,  1.894e-01,  1.814e-01,  5.709e-01,  8.259e-01, -2.323e-01, -4.525e-02,  5.422e-01,  5.007e-01,  5.209e-02,  2.077e-01, -3.695e-01,  2.688e-01,  1.658e-01, -1.259e+00, -3.978e+00, -4.708e-01, -1.649e+00,  6.059e+00, -1.428e+00,  6.887e-01, -7.159e-01,  6.254e-02,  1.486e+02,  4.491e+01,  3.131e+01,  1.707e+02,  1.046e+01,  1.102e+01,  1.036e+01,  4.656e+00,  1.221e+00},
          {  2.509e+00, -1.966e+00,  5.010e-01, -1.337e-01,  2.055e-01,  4.744e-01,  6.653e-02,  5.400e-01,  1.188e-01,  3.601e+00,  4.536e-01,  5.180e-01,  3.201e-01,  3.349e-01,  1.059e-01,  1.929e-01,  1.922e-01, -4.646e+00,  8.847e+00,  5.850e-02, -1.645e+00,  6.030e-01, -1.213e+00,  1.233e+00, -1.057e+00,  3.782e-02,  8.531e+01,  3.743e+01,  2.019e+01,  1.046e+01,  8.966e+01,  8.082e+00,  5.534e+00,  2.890e+00,  3.719e-01},
          {  2.515e-01, -3.717e-01, -4.873e-01,  1.582e-01, -2.433e-01, -1.574e-02, -8.294e-01, -4.979e-01, -1.383e-01,  3.405e+00,  5.774e-01,  3.730e-01, -1.950e-01,  2.752e-01,  1.665e-01,  1.594e-01,  1.862e-01,  8.539e+00, -1.657e+00,  4.224e+00, -8.373e-01,  4.594e-01,  1.769e-01, -9.276e-01, -6.688e-02, -1.491e-01,  1.086e+02,  4.234e+01,  2.378e+01,  1.102e+01,  8.082e+00,  6.689e+01,  4.741e+00,  3.107e+00,  6.005e-01},
          { -9.975e-01, -9.804e-01, -3.370e-01, -8.644e-01, -1.080e+00, -7.158e-04, -5.594e-01, -4.912e-01, -1.740e-01,  1.726e+00,  6.473e-01,  5.800e-02,  1.234e-01,  1.078e-02,  1.077e-01, -9.120e-03,  4.945e-02,  2.618e+00,  3.425e-01,  4.170e+00,  3.996e-01,  2.034e+00, -1.313e+00, -1.258e-01, -1.391e-01, -2.556e-01,  7.407e+01,  2.289e+01,  1.686e+01,  1.036e+01,  5.534e+00,  4.741e+00,  4.394e+01,  3.774e+00,  7.295e-01},
          { -6.538e-01, -8.624e-01, -1.812e-01, -1.001e-01,  1.479e-01,  1.049e-01, -7.201e-02, -2.559e-01, -2.560e-02,  7.588e-01,  3.936e-01, -1.421e-02,  1.434e-02, -7.139e-02, -1.459e-02, -5.394e-03,  6.610e-02,  1.652e+00, -4.205e+00,  1.368e+00,  5.892e-01,  1.014e+00, -8.547e-02, -2.687e-01,  2.553e-01,  9.459e-02,  3.843e+01,  1.565e+01,  7.598e+00,  4.656e+00,  2.890e+00,  3.107e+00,  3.774e+00,  2.198e+01,  1.053e-01},
          { -5.628e-02, -2.096e-02, -1.045e-01, -3.278e-01, -6.933e-02, -2.506e-01, -2.554e-01, -1.470e-01, -3.138e-02,  6.519e-01,  2.929e-01,  3.510e-02,  4.487e-02,  6.289e-02, -1.888e-02, -3.052e-02,  8.595e-04, -1.745e+00, -2.627e+00,  8.123e-01, -4.721e-01, -9.588e-02, -1.523e-01, -3.582e-01,  3.457e-02,  1.139e-03,  1.034e+01,  1.150e+00,  2.951e+00,  1.221e+00,  3.719e-01,  6.005e-01,  7.295e-01,  1.053e-01,  5.661e+00},
        };

        set_covariance(BKGCOV);

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
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_21_002_OLD)

  }
}
