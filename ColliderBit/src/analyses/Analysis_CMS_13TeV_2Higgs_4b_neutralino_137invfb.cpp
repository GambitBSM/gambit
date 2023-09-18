///
///  \author Yang Zhang
///  \date 2023 September
///  *********************************************

// Based on: 
// - https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-20-004

// Search for higgsinos decaying to two Higgs bosons and missing transverse momentum in proton-proton collisions at 13 TeV
// https://arxiv.org/abs/2201.04206
// CMS-SUS-20-004, CERN-EP-2021-214
// 
// Note:
//    * Not validate.
//    * No AK8 jets.
//    * No b-tag discriminator values



#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/Utils.hpp"

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    class Analysis_CMS_13TeV_2Higgs_4b_neutralino_137invfb : public Analysis {
    protected:
    
        // Counters for the number of accepted events for each signal region
        std::map<str, EventCounter> _counters;
        Cutflow _cutflow;

    public:
        // Required detector sim
        static constexpr const char* detector = "CMS";

        Analysis_CMS_13TeV_2Higgs_4b_neutralino_137invfb():
        _cutflow("CMS_13TeV_2Higgs_4b_neutralino_137invfb", {
          "Filters", 
          "N_vl=N_tk=0", 
          "4<=N_jet<=5",
          "N_b>=2"})
        {
            set_analysis_name("CMS_13TeV_2Higgs_4b_neutralino_137invfb");
            set_luminosity(137);
            
            for(size_t i=1; i<=21; ++i)
            {
              _counters["SR"+std::to_string(i)] =  EventCounter("SR"+std::to_string(i));
            }
        }

        struct ptComparison {
            bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
        } comparePt;

        void run(const HEPUtils::Event* event) {
            _cutflow.fillinit();

            // Missing energy
            double met = event->met();
            HEPUtils::P4 ptot = event->missingmom();

            // Define baseline jets
            BASELINE_JETS(jets, baselineJets_AK4, 30,  0, DBL_MAX, 2.4)
            BASELINE_JETS(jets, baselineJets_AK8, 300, 0, DBL_MAX, 2.4) // TODO: use jets_AK8
            BASELINE_BJETS(jets, baselineBJets_L, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("CSVv2Loose"), CMS::missIDBJet.at("CSVv2Loose"))
            BASELINE_BJETS(jets, baselineBJets_M, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("CSVv2Medium"), CMS::missIDBJet.at("CSVv2Medium"))
            BASELINE_BJETS(jets, baselineBJets_T, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("CSVv2Tight"), CMS::missIDBJet.at("CSVv2Tight"))
            vector<const HEPUtils::Jet*> baselineBJets_AK8;
            for (const HEPUtils::Jet* jet : baselineJets_AK8) {
                // Tag
                if( jet->btag() && random_bool(0.90) ) baselineBJets_AK8.push_back(jet);
                // Misstag light jet
                else if( random_bool(0.05) ) baselineBJets_AK8.push_back(jet);
            }
            
            // Define baseline objects with BASELINE(object_type, variable_name, minpT, mineta[, maxpT, maxeta, efficiency])
            BASELINE_PARTICLES(electrons, baselineElectrons, 10, 0, DBL_MAX, 2.5, CMS::eff2DEl.at("SUS_19_008"))
            BASELINE_PARTICLES(muons, baselineMuons, 10, 0, DBL_MAX, 2.4, CMS::eff2DMu.at("SUS_19_008"))


            // Define signal objects from baseline objects, automatically order by pT (highest first)
            SIGNAL_JETS(baselineJets_AK4, signalJets_AK4)
            SIGNAL_JETS(baselineJets_AK8, signalJets_AK8)
            SIGNAL_JETS(baselineBJets_L, signalBJets_L)
            SIGNAL_JETS(baselineBJets_M, signalBJets_M)
            SIGNAL_JETS(baselineBJets_T, signalBJets_T)
            SIGNAL_JETS(baselineBJets_AK8, signalBJets_AK8)
          

            // for the boosted signature
            if ( signalJets_AK8.size()>=2 ) { // N_AK8>=2
              double mj1 = (signalJets_AK8.at(0)->mom()).m();
              double mj2 = (signalJets_AK8.at(1)->mom()).m();
              if ( min(mj1,mj2)>60 and max(mj1,mj2)<260){// m_J1&J2 [60,260] GeV
                if (signalBJets_AK8.size()==1){ // N_H=1
                  // TODO reseolved event veto?
                  if (min(mj1,mj2)>95 and max(mj1,mj2)<145) {
                    if (met < 500.) {
                      _counters.at("SR17").add_event(event);
                    } else if (met < 700.) {
                      _counters.at("SR18").add_event(event);
                    } else{
                      _counters.at("SR19").add_event(event);
                    }
                  }
                }else{ // N_H=2
                  if (min(mj1,mj2)>95 and max(mj1,mj2)<145) {
                    if (met < 500.) {
                      _counters.at("SR20").add_event(event);
                    } else if (met < 700.) {
                      _counters.at("SR21").add_event(event);
                    } else{
                      _counters.at("SR22").add_event(event);
                    }
                  }
                }
              } 
            }
            
            // the resolved signature
            if(met < 150.) return;
            _cutflow.fill(1); // MET>150
            if (baselineElectrons.size()>0 or baselineMuons.size()>0 ) return; 
            _cutflow.fill(2); // N_vl=N_tk=0 TODO?
            if (signalJets_AK4.size()<4 or signalJets_AK4.size()>5) return;
            _cutflow.fill(3); // 4<=N_jet<=5
            if (signalBJets_T.size()<2 or signalBJets_M.size()<2) return;
            _cutflow.fill(4); // N_b>=2
            for (int ii=0; ii<4; ii++)
            {
              double deltaPhi_cut =  ii<2 ? 0.5 : 0.3;
              if ( deltaR_eta(ptot, signalJets_AK4.at(ii)->mom()) < deltaPhi_cut) return;
            }
            _cutflow.fill(5); // DeltaPhi cuts
            // Instead of using four jets with the highest b-tag
            // discriminator values, we use the four hardest jets.
            // This should be fine for signal processes, but not for bkg.
            // TODO
            std::vector<std::vector<double>> pair1 = {{0,1},{0,2},{0,3}};
            std::vector<std::vector<double>> pair2 = {{2,3},{1,3},{1,2}};
            int i_smallest = -1;
            double mbb_delta_smallest = 9999.;
            double mbb_average = 9999.;
            for (int ii=1; ii<3; ii++)
            {
              double mbb1 = (signalJets_AK4.at(pair1[ii][0])->mom() + signalJets_AK4.at(pair1[ii][1])->mom()).m();
              double mbb2 = (signalJets_AK4.at(pair2[ii][0])->mom() + signalJets_AK4.at(pair2[ii][1])->mom()).m();
              double mbb_delta = fabs(mbb2 - mbb1);
              if (mbb_delta<mbb_delta_smallest){
                mbb_delta_smallest = mbb_delta;
                mbb_average = 0.5*(mbb2 + mbb1);
                i_smallest = ii;
              }
            }
            if (mbb_delta_smallest>40 or mbb_average>200) return;
            _cutflow.fill(6); // Delta_m_bb < 40 GeV, <m_bb> < 200 GeV
            
            double Delta_R_max = max(deltaR_eta(signalJets_AK4.at(pair1[i_smallest][0])->mom(), signalJets_AK4.at(pair1[i_smallest][1])->mom()),
                                     deltaR_eta(signalJets_AK4.at(pair2[i_smallest][0])->mom(), signalJets_AK4.at(pair2[i_smallest][1])->mom()));
            if (Delta_R_max > 2.2) return;
            _cutflow.fill(7); // Delta_R_max< 2.2
 
            if (mbb_average>140 or mbb_average<100) return;
            _cutflow.fill(8); // 100 < <m_bb> < 140 GeV
 
            if (Delta_R_max>1.1) { // && Delta_R_max<2.2
              if (signalBJets_M.size() == 3 and signalBJets_L.size() == 3 ) { // Nb=3
                 // and signalBJets_T.size() >= 2
                if (met < 200.) {
                  _counters.at("SR1").add_event(event);
                } else if (met < 300.) {
                  _counters.at("SR2").add_event(event);
                } else if (met < 400.) {
                  _counters.at("SR3").add_event(event);
                } else { //met > 400.
                  _counters.at("SR4").add_event(event);
                }
              } else if (signalBJets_M.size() >= 3 and signalBJets_L.size() >= 4 ) { // Nb=4
                 // and signalBJets_T.size() >= 2
                if (met < 200.) {
                  _counters.at("SR5").add_event(event);
                } else if (met < 300.) {
                  _counters.at("SR6").add_event(event);
                } else if (met < 400.) {
                  _counters.at("SR7").add_event(event);
                } else { //met > 400.
                  _counters.at("SR8").add_event(event);
                }
              }
            } else { // Delta_R_max<1.1
              if (signalBJets_M.size() == 3 and signalBJets_L.size() == 3 ) { // Nb=3
                 // and signalBJets_T.size() >= 2
                if (met < 200.) {
                  _counters.at("SR9").add_event(event);
                } else if (met < 300.) {
                  _counters.at("SR10").add_event(event);
                } else if (met < 400.) {
                  _counters.at("SR11").add_event(event);
                } else { //met > 400.
                  _counters.at("SR12").add_event(event);
                }
              } else if (signalBJets_M.size() >= 3 and signalBJets_L.size() >= 4 ) { // Nb=4
                 // and signalBJets_T.size() >= 2
                if (met < 200.) {
                  _counters.at("SR13").add_event(event);
                } else if (met < 300.) {
                  _counters.at("SR14").add_event(event);
                } else if (met < 400.) {
                  _counters.at("SR15").add_event(event);
                } else { //met > 400.
                  _counters.at("SR16").add_event(event);
                }
              }
            }

            return;
        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
            const Analysis_CMS_13TeV_2Higgs_4b_neutralino_137invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2Higgs_4b_neutralino_137invfb*>(other);

            for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }


        void collect_results() {
            add_result(SignalRegionData(_counters.at("SR1"), 138, {149.74,8.8574}));
            add_result(SignalRegionData(_counters.at("SR2"), 91,  {91.536,6.8599}));
            add_result(SignalRegionData(_counters.at("SR3"), 14,  {12.757,2.5972}));
            add_result(SignalRegionData(_counters.at("SR4"), 3,   {2.8097,1.4218}));
            add_result(SignalRegionData(_counters.at("SR5"), 54,  {54.095,5.6413}));
            add_result(SignalRegionData(_counters.at("SR6"), 38,  {33.195,4.2411}));
            add_result(SignalRegionData(_counters.at("SR7"), 4,   {3.2223,1.2999}));
            add_result(SignalRegionData(_counters.at("SR8"), 0,   {1.2679,0.97784}));
            add_result(SignalRegionData(_counters.at("SR9"), 8,   {5.882,1.4052}));
            add_result(SignalRegionData(_counters.at("SR10"), 2,  {2.3094,0.73274}));
            add_result(SignalRegionData(_counters.at("SR11"), 4,  {0.71703,0.5334}));
            add_result(SignalRegionData(_counters.at("SR12"), 0,  {0.51656,0.64712}));
            add_result(SignalRegionData(_counters.at("SR13"), 1,  {2.5764,0.85482}));
            add_result(SignalRegionData(_counters.at("SR14"), 3,  {1.6197,0.64834}));
            add_result(SignalRegionData(_counters.at("SR15"), 1,  {1.156,0.86595}));
            add_result(SignalRegionData(_counters.at("SR16"), 1,  {0.7792,0.76461}));
            add_result(SignalRegionData(_counters.at("SR17"), 42, {37.03,4.4312}));
            add_result(SignalRegionData(_counters.at("SR18"), 6,  {7.2132,1.4753}));
            add_result(SignalRegionData(_counters.at("SR19"), 1,  {1.5016,0.74554}));
            add_result(SignalRegionData(_counters.at("SR20"), 4,  {4.0059,1.2035}));
            add_result(SignalRegionData(_counters.at("SR21"), 0,  {0.735,0.29432}));
            add_result(SignalRegionData(_counters.at("SR22"), 0,  {0.14552,0.13395}));

            // static const vector< vector<double> > BKGCOV = {
            //     {},
            //     {}
            // };

            // set_covariance(BKGCOV);

            return;
        }

    protected:
      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };


    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2Higgs_4b_neutralino_137invfb)

  }
}
