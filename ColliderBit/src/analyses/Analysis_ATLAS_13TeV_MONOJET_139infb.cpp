// -*- C++ -*-
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "Eigen/Eigen"

// This is based on the ATLAS 139 invfb Monojet analysis, found at: https://arxiv.org/pdf/2102.10874.pdf

// #define CHECK_CUTFLOW

namespace Gambit
{
  namespace ColliderBit
  {

    using namespace std;
    using namespace HEPUtils;


    /// @brief ATLAS Monojet analysis, with 139/fb of data
    ///
    class Analysis_ATLAS_13TeV_MONOJET_139infb : public Analysis
    {
      public:

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        // Numbers passing cuts TODO: Do the inclusive as well
        std::map<string, EventCounter> _counters = {
          {"EM0", EventCounter("EM0")},
          {"EM1", EventCounter("EM1")},
          {"EM2", EventCounter("EM2")},
          {"EM3", EventCounter("EM3")},
          {"EM4", EventCounter("EM4")},
          {"EM5", EventCounter("EM5")},
          {"EM6", EventCounter("EM6")},
          {"EM7", EventCounter("EM7")},
          {"EM8", EventCounter("EM8")},
          {"EM9", EventCounter("EM9")},
          {"EM10", EventCounter("EM10")},
          {"EM11", EventCounter("EM11")},
          {"EM12", EventCounter("EM12")},
        };

        #ifdef CHECK_CUTFLOW
          Cutflows _cutflows;
        #endif

        static const size_t NUMSR = 13;

        Cutflow _cutflow;

        Analysis_ATLAS_13TeV_MONOJET_139infb()
        {

          analysis_specific_reset();
          set_analysis_name("ATLAS_13TeV_MONOJET_139infb");
          set_luminosity(139.0);

          #ifdef CHECK_CUTFLOW
            _cutflows.addCutflow("EM",{"MET>150", //The analysis starts with a trigger of Met > 150GeV
                                       "Lepton",
                                       "Njets<4",
                                       "min DeltaPhi",
                                       "Lead jet pT and eta",
                                       "MET>200"});
          #endif

        }

        // Overlap removal of particle if within delta R range of a jet
        void ejetOverlapRemoval(vector<const HEPUtils::Particle*>& electrons, vector<const HEPUtils::Jet*>& jets, double DeltaRMin, double DeltaRMax)
        {
          vector<const HEPUtils::Particle*> survivors;
          for(const HEPUtils::Particle* e : electrons)
          {
            bool overlap = false;
            for(const HEPUtils::Jet* jet : jets)
            {
              double dR = jet->mom().deltaR_eta(e->mom());
              if(fabs(dR)>=DeltaRMin && fabs(dR)<=DeltaRMax) overlap = true;
            }
            if(!overlap) survivors.push_back(e);
          }
          electrons = survivors;
          return;
        }


        void run(const Event* event)
        {

          #ifdef CHECK_CUTFLOW
            const double w = event->weight();
            _cutflows.fillinit(w);
          #endif

          // Require MET above 200 GeV
          const P4 pmiss = event->missingmom();
          const double met = event->met();

          // Define the cut booleans
          bool EM_ETmiss_gt_150 = false;
          bool EM_lep_lt_1 = false;
          bool EM_Njet_leq_4 = false;
          bool EM_min_deltaphi = false;
          //bool EM_lead_jet_quality = false;
          bool EM_lead_jet_ptandeta = false;
          bool EM_ETmiss_gt_200 = false;

          // lepton and photon objects
          vector<const HEPUtils::Particle*> baselineElectrons;
          vector<const HEPUtils::Particle*> baselineMuons;
          vector<const HEPUtils::Particle*> baselineTaus;
          vector<const HEPUtils::Particle*> baselinePhotons;

          // Fill electron object
          for (const Particle* e : event->electrons())
          {
            if (e->pT() > 7 && e->abseta()<2.47) baselineElectrons.push_back(e);
          }

          // Fill muon object
          for (const Particle* m : event->muons())
          {
            if (m->pT() > 7 && m->abseta()<2.5) baselineMuons.push_back(m);
          }

          // Fill tau object
          for (const Particle* t : event->taus())
          {
            if (t->pT() > 20 && t->abseta()<2.5) baselineTaus.push_back(t);
          }

          // Fill photon object
          for (const Particle* p : event->photons())
          {
            if (p->pT() > 10 && p->abseta()<2.37) baselinePhotons.push_back(p);
          }

          // Get jets (0.9 is to emulate the requirement of coming from a primary vertex)
          vector<const Jet*> baselineJets;
          for (const Jet* jet : event->jets())
          {
            if ((jet->pT() > 30) && (jet->abseta() < 2.8))
            {
              if (jet->pT() < 120 && jet->abseta() < 2.5)
              {
                if (random_bool(0.90)) baselineJets.push_back(jet);
              }
              else
              {
                baselineJets.push_back(jet);
              }
            }
          }

          // B-tag efficiencies
          // 60 % b-tag efficiency
          // 1/35 = 2.857% rejection factor for c-jets
          // 1/1500 = 0.066% rejection factor for gluons and light-quarks
          std::map<const Jet*,bool> analysisBtags = generateBTagsMap(baselineJets,0.6,0.02857,0.00066);

          vector<const Jet*> baselineBJets;
          vector<const Jet*> baselineNonBJets;
          for (const HEPUtils::Jet* j : baselineJets)
          {
            if (j->abseta() < 2.5 && analysisBtags.at(j))
            {
              baselineBJets.push_back(j);
            }
            else
            {
              baselineNonBJets.push_back(j);
            }
          }


          // Overlap removal
          // 1) Remove electrons with 0.01 of an muon, mimics shared tracks
          removeOverlap(baselineElectrons, baselineMuons, 0.01);
          // 2) Remove non-b-jets within DeltaR = 0.2 of electron
          removeOverlap(baselineNonBJets, baselineElectrons, 0.2);
          // 3) Remove electrons that are between 0.2 and 0.4 of a jet
          ejetOverlapRemoval(baselineElectrons, baselineNonBJets, 0.2, 0.4);
          ejetOverlapRemoval(baselineElectrons, baselineBJets, 0.2, 0.4);
          // 4) Remove jets within DeltaR = 0.4 of muon. We don't have track information (analysis specifies for 3 tracks)
          removeOverlap(baselineNonBJets, baselineMuons, 0.4);
          removeOverlap(baselineBJets, baselineMuons, 0.4);
          // 5) Any tau within 0.2 of an electron or muon is removed
          removeOverlap(baselineTaus, baselineElectrons, 0.2);
          removeOverlap(baselineTaus, baselineMuons, 0.2);
          // 6) Any jet within 0.2 of a tau is removed
          removeOverlap(baselineNonBJets, baselineTaus, 0.2);
          removeOverlap(baselineBJets, baselineTaus, 0.2);
          // 7) Any photon within 0.4 of a muon or electron is removed
          removeOverlap(baselinePhotons, baselineElectrons, 0.4);
          removeOverlap(baselinePhotons, baselineMuons, 0.4);
          // 8) Any jet within 0.4 of a photon is removed
          removeOverlap(baselineNonBJets, baselinePhotons, 0.4);
          removeOverlap(baselineBJets, baselinePhotons, 0.4);

          ATLAS::applyLooseIDElectronSelectionR2(baselineElectrons);

          // All jets
          vector<const HEPUtils::Jet*> signalJets = baselineNonBJets;
          signalJets.insert(signalJets.end(), baselineBJets.begin(), baselineBJets.end());

          // Sort by Pt
          sortByPt(signalJets);

          // Performing the cuts
          while(true)
          {

            // Require ETmiss > 150 GeV
            if (met > 150) {EM_ETmiss_gt_150 = true;}
            if (!EM_ETmiss_gt_150) break;

            // Veto on any leptons or photons
            if ((baselineElectrons.size() == 0) && (baselineMuons.size() == 0) && (baselineTaus.size() == 0) && (baselinePhotons.size() == 0)) {EM_lep_lt_1 = true;}
            if (!EM_lep_lt_1) break;

            // Require no more than 4 jets
            if (signalJets.size() <= 4) {EM_Njet_leq_4 = true;}
            if (!EM_Njet_leq_4) break;

            // Cut on maximum delta phi
            EM_min_deltaphi = true;
            for (size_t i = 0; i < 4; ++i)
            {
              if (i >= signalJets.size()) break;
              if (met>250)
              {
                if (fabs(deltaPhi(signalJets[i]->mom(), pmiss))<0.4) EM_min_deltaphi = false;
              }
              else
              {
                if (fabs(deltaPhi(signalJets[i]->mom(), pmiss))<0.6) EM_min_deltaphi = false;
              }
            }

            if (!EM_min_deltaphi) break;

            if (signalJets.empty()) break;
            if ((signalJets[0]->pT() > 150) && (signalJets[0]->abseta() < 2.4)) {EM_lead_jet_ptandeta = true;}
            if (!EM_lead_jet_ptandeta) break;

            // Require ETmiss > 200 GeV
            if (met > 200) {EM_ETmiss_gt_200 = true;}
            if (!EM_ETmiss_gt_200) break;

            // Fill signal regions
            // Identify the ptmiss bin and fill the counter
            const static vector<double> metedges = {200, 250, 300, 350, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200};
            const int i_sr = binIndex(met, metedges, true);

            if (i_sr >= 0)
            {
              std::stringstream sr_key; sr_key << "EM" << i_sr;
              _counters.at(sr_key.str()).add_event(event->weight(), event->weight_err());
            }

            // Applied all cuts
            break;
          }

          // Fill cutflow
          #ifdef CHECK_CUTFLOW
            if (EM_ETmiss_gt_150) _cutflows["EM"].fillnext(w);
            if (EM_lep_lt_1) _cutflows["EM"].fillnext(w);
            if (EM_Njet_leq_4) _cutflows["EM"].fillnext(w);
            if (EM_min_deltaphi) _cutflows["EM"].fillnext(w);
            if (EM_lead_jet_ptandeta) _cutflows["EM"].fillnext(w);
            if (EM_ETmiss_gt_200) _cutflows["EM"].fillnext(w);
          #endif

        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
          const Analysis_ATLAS_13TeV_MONOJET_139infb* specificOther = dynamic_cast<const Analysis_ATLAS_13TeV_MONOJET_139infb*>(other);
          for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }


        void collect_results()
        {

          add_result(SignalRegionData(_counters.at("EM0"), 1791624, {1783000., 26000.}));
          add_result(SignalRegionData(_counters.at("EM1"), 752328, {753000., 9000.}));
          add_result(SignalRegionData(_counters.at("EM2"), 313912, {314000., 3500.}));
          add_result(SignalRegionData(_counters.at("EM3"), 141036, {140100., 1600.}));
          add_result(SignalRegionData(_counters.at("EM4"), 102888, {101600., 1200.}));
          add_result(SignalRegionData(_counters.at("EM5"), 29458, {29200., 400.}));
          add_result(SignalRegionData(_counters.at("EM6"), 10203, {10000., 180.}));
          add_result(SignalRegionData(_counters.at("EM7"), 3986, {3870., 80.}));
          add_result(SignalRegionData(_counters.at("EM8"), 1663, {1640., 40.}));
          add_result(SignalRegionData(_counters.at("EM9"), 738, {754., 20.}));
          add_result(SignalRegionData(_counters.at("EM10"), 413, {359., 10.}));
          add_result(SignalRegionData(_counters.at("EM11"), 187, {182., 6.}));
          add_result(SignalRegionData(_counters.at("EM12"), 207, {218., 9.}));

          #ifdef CHECK_CUTFLOW
            // Cutflow printout
            cout << "\nCUTFLOWS:\n" << _cutflows << endl;
            cout << "\nSRCOUNTS:\n";
            for (auto& pair : _counters) cout << pair.first << ": " << pair.second.weight_sum() << "\n";
            cout << "\n" << endl;
          #endif

        }

      protected:

        void analysis_specific_reset()
        {
          for (auto& pair : _counters) { pair.second.reset(); }
        }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_MONOJET_139infb)

  }
}
