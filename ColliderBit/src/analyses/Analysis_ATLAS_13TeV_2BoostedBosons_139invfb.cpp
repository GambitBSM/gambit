///
///  \author Are Raklev
///  \date 2021 July
///
///
///  Based on the search presented in 2108.07586.
///
///  WARNING: This implementation only predicts the non-b-jet signal regions due to problems reproducing
///  the b-tagging used based on small radius track jets. Some further limitations are:
///
///  * Due to the lack of mis-tagging probabilities for W- and Z-jets, events will be missing from
///  signal regions not directly corresponding to the produced bosons, e.g. in chargino--neutralino
///  production with decays into W and Z, events would otherwise also be expected in the ZZ signal region
///  due to misidentification of W-jets as Z-jets jets, but this will not be the case with the current
///  inplementation. As a result the most reliable and most constraining signal region will typically be the VV
///  signal region.
///
///  * For b-tagging we take the conservative approach of allowing no events with b-labeled jets and use
///  the mis-tagging probabilities for the small radius track jets for non-b-labeled jets.
///
///  * The separation of E_T^miss and jets in the analysis is done using small radius jets. Here we use the
///  large radius jets since they are the only ones available.
///
///  *********************************************


//#define CHECK_CUTFLOW
//#define BENCHMARK "WW"
//#define BENCHMARK "WZ"
//#define BENCHMARK "Wh"
//#define BENCHMARK "HG"

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
//#include "gambit/ColliderBit/lester_mt2_bisect.h"

//#define CHECK_CUTFLOW

using namespace std;


namespace Gambit
{
  namespace ColliderBit
  {


    class Analysis_ATLAS_13TeV_2BoostedBosons_139invfb : public Analysis
    {

      protected:
        // Signal region map
        std::map<string, EventCounter> _counters = {
          // Exclusion regions
          {"SR-4Q-WW", EventCounter("SR-4Q-WW")},
          {"SR-4Q-WZ", EventCounter("SR-4Q-WZ")},
          {"SR-4Q-ZZ", EventCounter("SR-4Q-ZZ")},
          {"SR-4Q-VV", EventCounter("SR-4Q-VV")},
  //        {"SR-2B2Q-WZ", EventCounter("SR-2B2Q-WZ")},
  //        {"SR-2B2Q-ZZ", EventCounter("SR-2B2Q-ZZ")},
  //        {"SR-2B2Q-Wh", EventCounter("SR-2B2Q-Wh")},
  //        {"SR-2B2Q-Zh", EventCounter("SR-2B2Q-Zh")},
  //        {"SR-2B2Q-VZ", EventCounter("SR-2B2Q-VZ")},
  //        {"SR-2B2Q-Vh", EventCounter("SR-2B2Q-Vh")},
  //        // Discovery regions
  //        {"Disc-SR-2B2Q", EventCounter("Disc-SR-2B2Q")},  // Union of SR-2B2Q-VZ and SR-2B2Q-Vh
  //        {"Disc-SR-Incl", EventCounter("Disc-SR-Incl")},  // Union of SR-4Q-VV and Disc-SR-2B2Q
        };

      public:

        #ifdef CHECK_CUTFLOW
        // Cut-flow variables
        string benchmark = BENCHMARK;
        size_t NCUTS=20;
        vector<double> _cutflow_GAMBIT{vector<double>(NCUTS)};
        vector<double> _cutflow_ATLAS{vector<double>(NCUTS)};
        vector<string> _cuts{vector<string>(NCUTS)};
        // SR yields {4Q-WW, 4Q-WZ, 4Q-ZZ, 4Q-VV, 2B2Q-WZ, 2B2Q-Wh, 2B2Q-ZZ, 2B2Q-Zh, 2B2Q-VZ, 2B2Q-Vh}
        vector<double> _yield_model{vector<double>(10)};
        // meff distribution
        const vector<double> _meff_bins = {700., 850., 1000., 1150., 1300., 1450., 1600., 1750., 1900., 2050., 2200., 2350., 2500,};
        vector<double> _meff_4QVV{vector<double>(12)};
        vector<double> _meff_4QVV_model{vector<double>(12)};
        #endif

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        Analysis_ATLAS_13TeV_2BoostedBosons_139invfb()
        {

          set_analysis_name("ATLAS_13TeV_2BoostedBosons_139invfb");
          set_luminosity(139.);

        }

        // The following section copied from Analysis_ATLAS_1LEPStop_20invfb.cpp
        void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &lepvec, double DeltaRMax)
        {
          //Routine to do jet-lepton check
          //Discards jets if they are within DeltaRMax of a lepton

          vector<const HEPUtils::Jet*> Survivors;

          for(unsigned int itjet = 0; itjet < jetvec.size(); itjet++)
          {
            bool overlap = false;
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++)
            {
              HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
              double dR;

              dR=jetmom.deltaR_eta(lepmom);

              if(fabs(dR) <= DeltaRMax) overlap=true;
            }
            if(overlap) continue;
            Survivors.push_back(jetvec.at(itjet));
          }
          jetvec=Survivors;

          return;
        }

        // Run main event analysis
        void run(const HEPUtils::Event* event)
        {

          // Get the missing energy in the event
          double met = event->met();
          HEPUtils::P4 metVec = event->missingmom();

          // Define vectors of baseline leptons
          // Baseline electrons
          vector<const HEPUtils::Particle*> electrons;
          for (const HEPUtils::Particle* electron : event->electrons())
          {
            if (electron->pT() > 4.5
                && fabs(electron->eta()) < 2.47)
              electrons.push_back(electron);
          }
          // Apply electron efficiency from "Loose" criteria in 1902.04655
          ATLAS::applyElectronIDEfficiency2019(electrons, "Loose");
          // Baseline muons
          vector<const HEPUtils::Particle*> muons;
          for (const HEPUtils::Particle* muon : event->muons())
          {
            if (muon->pT() > 3.
                && fabs(muon->eta()) < 2.7)
              muons.push_back(muon);
          }
          // Apply muon efficiency
          ATLAS::applyMuonEffR2(muons);

          // Number of leptons
          size_t nMuons = muons.size();
          size_t nElectrons = electrons.size();
          size_t nLeptons = nElectrons+nMuons;

          // Look at jets to see if they fulfil criteria for fat jets
          vector<const HEPUtils::Jet*> fatJets;
          for (const HEPUtils::Jet* jet : event->jets())
          {
            //  cout  << jet->pT() << " " << jet->mass() << " Z-tag " <<  jet->Ztag() << " W-tag " << jet->Wtag() << " " << endl;
            if (jet->pT() > 200. && fabs(jet->eta()) < 2.0 && jet->mass() > 40.)
            {
              fatJets.push_back(jet);
            }
          }
          // Overlap removal (remove fat jets within DR=1 of electrons)
          JetLeptonOverlapRemoval(fatJets, electrons, 1.0);
          size_t nfat = fatJets.size();

          // Tag the large jets (only look at two hardest jets)
          int nW = 0; int nZ = 0; int nH = 0; int ntest = 0;
          const vector<double> bpT = {200., 300., 500., 700., 900., DBL_MAX}; // pT bin edges
          const vector<double> pW = {0.469, 0.475, 0.481, 0.496, 0.522}; // W tag prob
          const vector<double> pWmiss = {1/10.2574, 1/20.2997, 1/33.4745, 1/36.0622, 1/29.1341}; // W misstag prob
          const vector<double> pZ = {0.469, 0.488, 0.513, 0.516, 0.525}; // Z tag prob
          const vector<double> pZmiss = {1/11.5847, 1/18.5291, 1/27.7596, 1/38.4142, 1/26.0997}; // Z misstag prob
          const vector<double> pH = {0.469, 0.488, 0.513, 0.516, 0.525}; // Higgs tag prob TODO: Update with correct numbers
          const HEPUtils::BinnedFn1D<double> _eff1dW(bpT, pW);
          const HEPUtils::BinnedFn1D<double> _eff1dWmiss(bpT, pWmiss);
          const HEPUtils::BinnedFn1D<double> _eff1dZ(bpT, pZ);
          const HEPUtils::BinnedFn1D<double> _eff1dZmiss(bpT, pZmiss);
          const HEPUtils::BinnedFn1D<double> _eff1dH(bpT, pH);
          for (const HEPUtils::Jet* jet : fatJets)
          {
            // Tag W
            if( jet->Wtag() && random_bool( _eff1dW.get_at( jet->pT() ) ) ) nW++;
            // Tag Z
            if( jet->Ztag() && random_bool( _eff1dZ.get_at( jet->pT() ) ) ) nZ++;
            // Tag SM Higgs
            if( jet->htag() && random_bool( _eff1dH.get_at( jet->pT() )  ) ) nH++;
            // Misstag as Z or W
            if( !jet->Wtag() && !jet->Ztag() )
            {
              if( random_bool( _eff1dZmiss.get_at( jet->pT() ) )  ) nZ++;
              if( random_bool( _eff1dWmiss.get_at( jet->pT() ) )  ) nW++;
            }
            ntest++;
            if(ntest > 1) break;
          }
          int nV = nZ + nW;
          //if(nH > 0 ) cout << "nZ " << nZ << " nW " << nW << " nV " << nV << " nH " << nH << endl;

          // b-jet tagging
          /* There is a difference here wrt the actual analysis where small
           sliding radius track jets are used, and the number of such b-jets are
           counted. This means that the rejection for b-jets in the 4Q SRs has to
           be changed. We use the conservative choice of rejecting all events with
           a b-labeled large radius jet and mis-tagging large radius non-b-jets
           according to the mis-tag probabilities of the small radius track jets.
          */
  //        double btag = 0.83;
          double cmisstag = 1/3.; double misstag = 1./33.;
          int nb = 0;
          for ( const HEPUtils::Jet* jet : event->jets() )
          {
            // Tag b-jet
            if( jet->btag() ) nb++;
            // Misstag c-jet
            else if( !jet->btag() && jet->ctag() && random_bool(cmisstag) ) nb++;
            // Misstag light jet
            else if( !jet->btag() && !jet->ctag() && random_bool(misstag) ) nb++;
          }

          // Check separation of jets and ETmiss
          bool delphi = true;
          for ( const HEPUtils::Jet* jet : fatJets )
          {
            double phi = jet->mom().deltaPhi(metVec);
            if (phi < 1.0) delphi = false;
          }

          // Effective mass (missing energy plus two leading fatjet pTs)
          double meff = met;
          if(fatJets.size() > 0) meff += fatJets[0]->pT();
          if(fatJets.size() > 1) meff += fatJets[1]->pT();


          //
          // Count signal region events
          //

          // Preselection conditions
          if(nfat > 1 && nLeptons == 0)
          {
            // First exclusion regions
            if(nb == 0 && delphi)
            {
              if(met > 300. && meff > 1300. && nV == 2 && nW == 2) _counters.at("SR-4Q-WW").add_event(event);
              if(met > 300. && meff > 1300. && nV == 2 && nW > 0 && nZ > 0) _counters.at("SR-4Q-WZ").add_event(event);
              if(met > 300. && meff > 1300. && nV == 2 && nZ ==2) _counters.at("SR-4Q-ZZ").add_event(event);
              if(met > 300. && meff > 1300. && nV == 2) _counters.at("SR-4Q-VV").add_event(event);
            }
            if(nb == 1){ }
            // Then discovery regions

          }

          #ifdef CHECK_CUTFLOW
          // Check meff distribution
          if(nfat > 1 && nLeptons == 0 && nb == 0 && delphi && met > 300. && nV == 2)
          {
            size_t i = floor((meff-_meff_bins[0])/150);
            if(i < _meff_4QVV.size() ) _meff_4QVV[i]++;
          }
          // Do cut-flow proper
          for(size_t j=0; j<NCUTS; j++)
          {
            if(
               (j==0) ||
               (j==1 && met > 200) ||
               (j==2 && met > 200) ||
               (j==3 && met > 200 && nLeptons == 0) ||
               (j==4 && met > 200 && nLeptons == 0 && nfat > 1) ||
               (j==5 && met > 200 && nLeptons == 0 && nfat > 1 && nb == 0) ||
               (j==6 && met > 200 && nLeptons == 0 && nfat > 1 && nb == 0 && delphi) ||
               (j==7 && met > 200 && nLeptons == 0 && nfat > 1 && nb == 0 && delphi && nb < 2) ||
               (j==8 && met > 300 && nLeptons == 0 && nfat > 1 && nb == 0 && delphi && nb < 2) ||
               (j==9 && met > 300 && nLeptons == 0 && nfat > 1 && nb == 0 && delphi && nb < 2 && meff > 1300) ||
               (j==10 && met > 300 && nLeptons == 0 && nfat > 1 && nb == 0 && delphi && nb < 2 && meff > 1300 && nV == 2) ||
               (j==11 && met > 300 && nLeptons == 0 && nfat > 1 && nb == 0 && delphi && nb < 2 && meff > 1300 && nV == 2) ||
               (j==12 && met > 300 && nLeptons == 0 && nfat > 1 && delphi && nH == 1)
               ) _cutflow_GAMBIT[j]++;
          }
          #endif


        } // End of analyze


        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
          const Analysis_ATLAS_13TeV_2BoostedBosons_139invfb* specificOther = dynamic_cast<const Analysis_ATLAS_13TeV_2BoostedBosons_139invfb*>(other);
          for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }


        void collect_results()
        {

          // Now fill a results object with the results for each SR
          add_result(SignalRegionData(_counters.at("SR-4Q-WW"),   2., {1.9, 0.4}));
          add_result(SignalRegionData(_counters.at("SR-4Q-WZ"),   3., {3.4, 0.7}));
          add_result(SignalRegionData(_counters.at("SR-4Q-ZZ"),   1., {1.9, 0.5}));
          add_result(SignalRegionData(_counters.at("SR-4Q-VV"),   3., {3.9, 0.8}));
  //        add_result(SignalRegionData(_counters.at("SR-2B2Q-WZ"), 2., {1.6, 0.4}));
  //        add_result(SignalRegionData(_counters.at("SR-2B2Q-ZZ"), 2., {1.7, 0.5}));
  //        add_result(SignalRegionData(_counters.at("SR-2B2Q-Wh"), 0., {1.9, 0.7}));
  //        add_result(SignalRegionData(_counters.at("SR-2B2Q-Zh"), 1., {1.6, 0.5}));
  //        add_result(SignalRegionData(_counters.at("SR-2B2Q-VZ"), 2., {2.2, 0.6}));
  //        add_result(SignalRegionData(_counters.at("SR-2B2Q-Vh"), 1., {2.5, 0.8}));
  //        add_result(SignalRegionData(_counters.at("Disc-SR-2B2Q"), 3., {4.7, 1.0})); // Union of SR-2B2Q-VZ and SR-2B2Q-Vh
  //        add_result(SignalRegionData(_counters.at("Disc-SR-Incl"), 6., {8.6, 1.3})); // Union of SR-4Q-VV and Disc-SR-2B2Q

          #ifdef CHECK_CUTFLOW
          cout << "Cut flow for " << benchmark << endl;

          double _xsec_model;
          double _lumi = luminosity();

          _cuts = {"Initial events", "E_T^miss > 200 GeV", "Event cleaning", "Lepton veto", "n_jets > 1", "n_bjets = 0", "min Delta phi > 1.0", "n_bjets < 2", "E_T^miss > 300 GeV", "m_eff > 1300 GeV", "n_V = 2", "MC to data efficiency weight for SR-4Q-VV", "n_H = 1" };

          if(benchmark == "WZ")
          {
            _yield_model = {3.5967, 6.3812, 4.1271, 6.7624, 2.0387, 0.3481, 1.8895, 0.2818, 2.3702, 0.3812};
            _meff_4QVV_model = {0.0, 0.30543, 0.62458, 1.264, 1.4178, 1.493, 1.2082, 0.9881, 0.65451, 0.35119, 0.29642, 0.0};
            _cutflow_ATLAS = {348.29, 287.73, 245.63, 172.60, 68.52, 64.64, 44.91, 35.02, 31.90, 23.74, 8.00, 6.76, 7.65, 6.60, 6.35, 3.61, 2.65, 2.34, 0.39, 0.36};
            _xsec_model = 2.52;
          }
          else if(benchmark == "WW")
          {
            _meff_4QVV_model = {0.15911, 1.1519, 2.1652, 2.3533, 2.302, 1.3157, 0.70599, 0.39097, 0.22347, 0.12507, 0.0, 0.0};
            _cutflow_ATLAS = {619.20, 466.99, 395.78, 241.87, 85.18, 81.22, 58.13, 52.01, 42.78, 20.11, 6.21, 5.28, 2.06, 1.60, 1.57, 0.68, 0.40, 0.34, 0.02, 0.02};
            _xsec_model = 4.42;
          }
          else if(benchmark == "Wh")
          {
            _yield_model = {0.3812, 0.6961, 0.4475, 0.7459, 1.1934, 5.2044, 0.8287, 3.6961, 1.2597, 5.5359};
            _cutflow_ATLAS = {348.29, 244.06, 207.07, 156.57, 67.95, 62.74, 42.83, 19.83, 17.67, 12.66, 0.78, 0.73, 19.23, 16.67, 16.08, 8.80, 1.40, 1.27, 6.03, 5.54};
            _xsec_model = 2.52;
          }
          else if(benchmark == "HG")
          {
            _yield_model = {0.8122, 1.5746, 1.2597, 1.8398, 1.5083, 2.0552, 1.9558, 3.0000, 2.1878, 3.2818};
            _meff_4QVV_model = {0.0, 0.1461, 0.56213, 0.43614, 0.4357, 0.66339, 0.40393, 0.1648, 0.0, 0.0, 0.0, 0.0};
            _cutflow_ATLAS = {482.87, 395.66, 336.46, 259.61, 85.00, 76.52, 53.05, 22.99, 19.99, 12.20, 2.08, 1.85, 26.28, 21.97, 20.47, 8.10, 2.55, 2.21, 3.75, 3.29};
            _xsec_model = 3.47;
          }
          double _scale = _xsec_model*_lumi/50000; // Weights of less than 0.01
          cout << "Event scaling factor: " << _scale << endl;

          // Compare final event yield per SR for model
          cout << "SR\t\t" << "GAMBIT\t" << "ATLAS" << endl;
          cout << "SR-4Q-WW\t" << _counters.at("SR-4Q-WW").sum()*_scale << "\t" << _yield_model[0] << endl;
          cout << "SR-4Q-WZ\t" << _counters.at("SR-4Q-WZ").sum()*_scale << "\t" << _yield_model[1] << endl;
          cout << "SR-4Q-ZZ\t" << _counters.at("SR-4Q-ZZ").sum()*_scale << "\t" << _yield_model[2] << endl;
          cout << "SR-4Q-VV\t" << _counters.at("SR-4Q-VV").sum()*_scale << "\t" << _yield_model[3] << endl;
          cout << endl;

          // Compare meff spectrum
          cout << "Meff SR-4Q-VV\t" << "GAMBIT\t" << "ATLAS " << endl;
          for( size_t j = 0; j < _meff_4QVV.size(); j++){
            cout << "[" << _meff_bins[j] << ", " << _meff_bins[j+1] << "]\t" << _meff_4QVV[j]*_scale << "\t" << _meff_4QVV_model[j] << endl;
          }

          // Compare cut-flow
          cout << fixed << setprecision(2);
          cout << "    GAMBIT\tMC error\tATLAS\t\tRatio\t\tCut" <<endl;
          for (size_t i=0; i<NCUTS; i++) {
            cout << i << ":  " <<  _cutflow_GAMBIT[i]*_scale << "\t\t" << sqrt(_cutflow_GAMBIT[i])*_scale << "\t\t" << _cutflow_ATLAS[i] <<  "\t\t" << _cutflow_GAMBIT[i]*_scale/_cutflow_ATLAS[i]  << "\t\t" << _cuts[i] <<endl;
          }


          #endif

        }

        void analysis_specific_reset()
        {
          // Clear signal regions
          for (auto& pair : _counters) { pair.second.reset(); }
        }

    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2BoostedBosons_139invfb)

  }
}


/*


 ****
 WW (WW final states)

 SR        GAMBIT  ATLAS
 SR-4Q-VV  5.332    5.065

 Meff SR-4Q-VV  GAMBIT  ATLAS
 [700, 850]  0.233  0.159
 [850, 1e+03]  1.14  1.15
 [1e+03, 1.15e+03]  1.71  2.17
 [1.15e+03, 1.3e+03]  2.58  2.35
 [1.3e+03, 1.45e+03]  2.22  2.3
 [1.45e+03, 1.6e+03]  1.13  1.32
 [1.6e+03, 1.75e+03]  0.872  0.706
 [1.75e+03, 1.9e+03]  0.553  0.391
 [1.9e+03, 2.05e+03]  0.258  0.223
 [2.05e+03, 2.2e+03]  0.147  0.125
 [2.2e+03, 2.35e+03]  0.0492  0
 [2.35e+03, 2.5e+03]  0.0246  0

     GAMBIT  MC error  ATLAS    Ratio    Cut
 0:  614.38    2.75    619.20    0.99    Initial events
 1:  477.58    2.42    466.99    1.02    E_T^miss > 200 GeV
 2:  477.58    2.42    395.78    1.21    Event cleaning
 3:  290.39    1.89    241.87    1.20    Lepton veto
 4:  115.81    1.19    85.18    1.36    n_jets > 1
 5:  75.69    0.96    81.22    0.93    n_bjets = 0
 6:  63.47    0.88    58.13    1.09    min Delta phi > 1.0
 7:  63.47    0.88    52.01    1.22    n_bjets < 2
 8:  51.79    0.80    42.78    1.21    E_T^miss > 300 GeV
 9:  24.59    0.55    20.11    1.22    m_eff > 1300 GeV
 10:  5.33    0.26    6.21    0.86    n_V = 2
 11:  5.33    0.26    5.28    1.01    MC to data efficiency weight


 ****
 HG (ZZ final states)

 Cut-flow output
 SR    GAMBIT  ATLAS
 SR-4Q-WW  0  0.812
 SR-4Q-WZ  0.143  1.57
 SR-4Q-ZZ  0.976  1.26
 SR-4Q-VV  1.12  1.84

 Meff SR-4Q-VV  GAMBIT  ATLAS
 [700, 850]  0.013  0
 [850, 1e+03]  0.0585  0.146
 [1e+03, 1.15e+03]  0.215  0.562
 [1.15e+03, 1.3e+03]  0.254  0.436
 [1.3e+03, 1.45e+03]  0.319  0.436
 [1.45e+03, 1.6e+03]  0.293  0.663
 [1.6e+03, 1.75e+03]  0.182  0.404
 [1.75e+03, 1.9e+03]  0.137  0.165
 [1.9e+03, 2.05e+03]  0.0585  0
 [2.05e+03, 2.2e+03]  0.052  0
 [2.2e+03, 2.35e+03]  0.026  0
 [2.35e+03, 2.5e+03]  0  0

     GAMBIT  MC error  ATLAS    Ratio    Cut
 0:  482.33    2.16    482.87    1.00    Initial events
 1:  399.01    1.96    395.66    1.01    E_T^miss > 200 GeV
 2:  399.01    1.96    336.46    1.19    Event cleaning
 3:  321.78    1.76    259.61    1.24    Lepton veto
 4:  135.22    1.14    85.00    1.59    n_jets > 1
 5:  31.12    0.55    76.52    0.41    n_bjets = 0
 6:  24.98    0.49    53.05    0.47    min Deltaphi > 1.0
 7:  24.98    0.49    22.99    1.09    n_bjets < 2
 8:  21.30    0.45    19.99    1.07    E_T^miss > 300 GeV
 9:  13.70    0.36    12.20    1.12    m_eff > 1300 GeV
 10:  1.66    0.13    2.08    0.80    n_V = 2
 11:  1.66    0.13    1.85    0.90    MC to data efficiency weight


 ****
 WZ (WZ final states)

 Cut-flow output
 SR    GAMBIT  ATLAS
 SR-4Q-WW  0.049  3.6
 SR-4Q-WZ  6.47  6.38
 SR-4Q-ZZ  0.056  4.13
 SR-4Q-VV  6.57  6.76

 Meff SR-4Q-VV  GAMBIT  ATLAS
 [700, 850]  0.00701  0
 [850, 1e+03]  0.231  0.305
 [1e+03, 1.15e+03]  0.673  0.625
 [1.15e+03, 1.3e+03]  0.911  1.26
 [1.3e+03, 1.45e+03]  1.43  1.42
 [1.45e+03, 1.6e+03]  1.36  1.49
 [1.6e+03, 1.75e+03]  1.11  1.21
 [1.75e+03, 1.9e+03]  0.974  0.988
 [1.9e+03, 2.05e+03]  0.595  0.655
 [2.05e+03, 2.2e+03]  0.364  0.351
 [2.2e+03, 2.35e+03]  0.273  0.296
 [2.35e+03, 2.5e+03]  0.182  0

     GAMBIT  MC error  ATLAS    Ratio    Cut
 0:  350.28    1.57    348.29    1.01    Initial events
 1:  297.58    1.44    287.73    1.03    E_T^miss > 200 GeV
 2:  297.58    1.44    245.63    1.21    Event cleaning
 3:  211.46    1.22    172.60    1.23    Lepton veto
 4:  93.52    0.81    68.52    1.36    n_jets > 1
 5:  51.04    0.60    64.64    0.79    n_bjets = 0
 6:  42.83    0.55    44.91    0.95    min Deltaphi > 1.0
 7:  42.83    0.55    35.02    1.22    n_bjets < 2
 8:  37.93    0.52    31.90    1.19    E_T^miss > 300 GeV
 9:  28.74    0.45    23.74    1.21    m_eff > 1300 GeV
 10:  6.57    0.21    8.00    0.82    n_V = 2
 11:  6.57    0.21    6.76    0.97    MC to data efficiency weight


 ***
 Wh (Wbb, WWW^*, WZZ^* final states)

 Cut-flow output
 SR    GAMBIT  ATLAS
 SR-4Q-WW  0.294  0.381
 SR-4Q-WZ  0.252  0.696
 SR-4Q-ZZ  0  0.448
 SR-4Q-VV  0.546  0.746

     GAMBIT  MC error  ATLAS    Ratio    Cut
 0:  350.28    1.57    348.29    1.01    Initial events
 1:  303.19    1.46    244.06    1.24    E_T^miss > 200 GeV
 2:  303.19    1.46    207.07    1.46    Event cleaning
 3:  205.39    1.20    156.57    1.31    Lepton veto
 4:  105.13    0.86    67.95    1.55    n_jets > 1
 5:  24.27    0.41    62.74    0.39    n_bjets = 0
 6:  20.20    0.38    42.83    0.47    min Deltaphi > 1.0
 7:  20.20    0.38    19.83    1.02    n_bjets < 2
 8:  17.95    0.35    17.67    1.02    E_T^miss > 300 GeV
 9:  13.04    0.30    12.66    1.03    m_eff > 1300 GeV
 10:  0.55    0.06    0.78    0.70    n_V = 2
 11:  0.55    0.06    0.73    0.75    MC to data efficiency weight


 */
