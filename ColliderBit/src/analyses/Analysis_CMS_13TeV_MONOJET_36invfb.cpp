// -*- C++ -*-
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

// Based on http://cms-results.web.cern.ch/cms-results/public-results/publications/EXO-16-048/index.html

namespace Gambit {
  namespace ColliderBit {

    using namespace std;
    using namespace HEPUtils;


    /// @brief CMS Run 2 monojet analysis (no W/Z region) with 36/fb of data
    ///
    /// @todo Add W/Z region with AKT8 jets and 2/1 n-subjettiness ratio cut
    ///
    class Analysis_CMS_13TeV_MONOJET_36invfb : public Analysis {
    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      std::map<string, EventCounter> _counters = {
        {"SR-0", EventCounter("SR-0")},
        {"SR-1", EventCounter("SR-1")},
        {"SR-2", EventCounter("SR-2")},
        {"SR-3", EventCounter("SR-3")},
        {"SR-4", EventCounter("SR-4")},
        {"SR-5", EventCounter("SR-5")},
        {"SR-6", EventCounter("SR-6")},
        {"SR-7", EventCounter("SR-7")},
        {"SR-8", EventCounter("SR-8")},
        {"SR-9", EventCounter("SR-9")},
        {"SR-10", EventCounter("SR-10")},
        {"SR-11", EventCounter("SR-11")},
        {"SR-12", EventCounter("SR-12")},
        {"SR-13", EventCounter("SR-13")},
        {"SR-14", EventCounter("SR-14")},
        {"SR-15", EventCounter("SR-15")},
        {"SR-16", EventCounter("SR-16")},
        {"SR-17", EventCounter("SR-17")},
        {"SR-18", EventCounter("SR-18")},
        {"SR-19", EventCounter("SR-19")},
        {"SR-20", EventCounter("SR-20")},
        {"SR-21", EventCounter("SR-21")},
      };

      static const size_t NUMSR = 22;

      Cutflow _cutflow;

      Analysis_CMS_13TeV_MONOJET_36invfb()
      // : _cutflow("CMS monojet 13 TeV", {"Njet >= 3", "HT > 300", "HTmiss > 300", "Nmuon = 0", "Nelectron = 0", "Nhadron = 0 (no-op)", "Dphi_htmiss_j1", "Dphi_htmiss_j2", "Dphi_htmiss_j3", "Dphi_htmiss_j4"})
      {
        analysis_specific_reset();
        set_analysis_name("CMS_13TeV_MONOJET_36invfb");
        set_luminosity(35.9);
      }

      void run(const Event* event) {

        // _cutflow.fillinit();

        // Require large MET
        const P4 pmiss = event->missingmom();
        const double met = pmiss.pT();
        if (met < 250) return; //< VETO

        // Record a trigger weight; we can aggregate this rather than wastefully random-vetoing
        const double trigweight = (met < 350) ? 0.97 : 1.0;

        // Electron objects
        vector<const HEPUtils::Particle*> baselineElectrons = event->electrons();

        // Apply electron efficiency
        CMS::applyElectronEff(baselineElectrons);

        // Muon objects
        vector<const HEPUtils::Particle*> baselineMuons = event->muons();

        // Apply muon efficiency
        CMS::applyMuonEff(baselineMuons);

        // Veto on isolated leptons and photons
        for (const Particle* e : baselineElectrons) if (e->pT() > 10 && e->abseta() < 2.5) return; //< VETO
        for (const Particle* m : baselineMuons) if (m->pT() > 10 && m->abseta() < 2.4) return; //< VETO
        for (const Particle* t : event->taus()) if (t->pT() > 18 && t->abseta() < 2.3) return; //< VETO
        for (const Particle* y : event->photons()) if (y->pT() > 15 && y->abseta() < 2.5) return; //< VETO

        // Get jets
        vector<const Jet*> jets4;
        for (const Jet* jet : event->jets())
          if (jet->pT() > 20) jets4.push_back(jet);

        // Veto if there are any b-tagged jets (reduce top background)
        for (const Jet* jet : jets4) {
          if (jet->abseta() > 2.4) continue;
          const double btag_rate = jet->btag() ? 0.8 : jet->ctag() ? 0.4 : 0.1;
          if (Random::draw() < btag_rate) return; //< VETO
        }

        // Get the 4 leading jets > 3 GeV, and veto if pTmiss is too close to them
        for (size_t i = 0; i < 4; ++i) {
          if (i >= jets4.size()) break;
          if (jets4[i]->pT() < 30) break;
          if (fabs(deltaPhi(jets4[i]->mom(), pmiss))<0.5) return; //< VETO
        }

        // Now the signal regions, but we'll just look at the monojet one
        if (jets4.empty()) return;
        if (jets4[0]->pT() < 100*GeV || jets4[0]->abseta() > 2.4) return;

        // Identify the ptmiss bin and fill the counter
        const static vector<double> metedges = {250, 280, 310, 340, 370, 400, 430, 470, 510, 550, 590,
                                                640, 690, 740, 790, 840, 900, 960, 1020, 1090, 1160, 1250};
        const int i_sr = binIndex(met, metedges, true);
        if (i_sr >= 0)
        {
          std::stringstream sr_key; sr_key << "SR-" << i_sr;
          _counters.at(sr_key.str()).add_event(event->weight() * trigweight, event->weight_err() * trigweight);
        }
      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_MONOJET_36invfb* specificOther = dynamic_cast<const Analysis_CMS_13TeV_MONOJET_36invfb*>(other);
        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }


      /// Register results objects with the results for each SR; obs & bkg numbers from the CONF note
      void collect_results() {
        //cout << _cutflow << endl;

        add_result(SignalRegionData(_counters.at("SR-0"), 136865, {134500, 3700}));
        add_result(SignalRegionData(_counters.at("SR-1"), 74340, {73400, 2000}));
        add_result(SignalRegionData(_counters.at("SR-2"), 42540, {42320, 810}));
        add_result(SignalRegionData(_counters.at("SR-3"), 25316, {25490, 490}));
        add_result(SignalRegionData(_counters.at("SR-4"), 15653, {15430, 310}));
        add_result(SignalRegionData(_counters.at("SR-5"), 10092, {10160, 170}));
        add_result(SignalRegionData(_counters.at("SR-6"), 8298, {8480, 140}));
        add_result(SignalRegionData(_counters.at("SR-7"), 4906, {4865, 95}));
        add_result(SignalRegionData(_counters.at("SR-8"), 2987, {2970, 49}));
        add_result(SignalRegionData(_counters.at("SR-9"), 2032, {1915, 33}));
        add_result(SignalRegionData(_counters.at("SR-10"), 1514, {1506, 32}));
        add_result(SignalRegionData(_counters.at("SR-11"), 926, {844, 18}));
        add_result(SignalRegionData(_counters.at("SR-12"), 557, {526, 14}));
        add_result(SignalRegionData(_counters.at("SR-13"), 316, {325, 12}));
        add_result(SignalRegionData(_counters.at("SR-14"), 233, {223, 9}));
        add_result(SignalRegionData(_counters.at("SR-15"), 172, {169, 8}));
        add_result(SignalRegionData(_counters.at("SR-16"), 101, {107, 6}));
        add_result(SignalRegionData(_counters.at("SR-17"), 65, {88.1, 5.3}));
        add_result(SignalRegionData(_counters.at("SR-18"), 46, {52.8, 3.9}));
        add_result(SignalRegionData(_counters.at("SR-19"), 26, {25.0, 2.5}));
        add_result(SignalRegionData(_counters.at("SR-20"), 31, {25.5, 2.6}));
        add_result(SignalRegionData(_counters.at("SR-21"), 29, {26.9, 2.8}));

        // Covariance
        static const vector< vector<double> > BKGCOV = {
          {  1.37e+07,  7.18e+06,  2.58e+06,  1.54e+06,  9.29e+05,  4.28e+05,  3.26e+05,  2.04e+05,  8.34e+04,  5.37e+04,  4.62e+04,  2.33e+04,  1.45e+04,  1.20e+04,  6.66e+03,  7.99e+03,  4.00e+03,  1.57e+03,  0.00e+00,  1.30e+03,  3.85e+02, -4.14e+02 },
          {  7.18e+06,  4.00e+06,  1.38e+06,  8.43e+05,  5.02e+05,  2.28e+05,  1.74e+05,  1.05e+05,  4.51e+04,  2.84e+04,  2.30e+04,  1.22e+04,  7.56e+03,  6.48e+03,  3.24e+03,  4.00e+03,  2.28e+03,  1.06e+03,  1.56e+02,  8.00e+02,  3.64e+02, -1.68e+02 },
          {  2.58e+06,  1.38e+06,  6.56e+05,  3.57e+05,  2.18e+05,  1.07e+05,  8.73e+04,  5.31e+04,  2.34e+04,  1.50e+04,  1.35e+04,  7.00e+03,  4.20e+03,  3.30e+03,  2.26e+03,  1.81e+03,  1.12e+03,  6.44e+02,  2.21e+02,  3.04e+02,  1.47e+02,  2.27e+01 },
          {  1.54e+06,  8.43e+05,  3.57e+05,  2.40e+05,  1.32e+05,  6.58e+04,  5.14e+04,  3.17e+04,  1.44e+04,  9.22e+03,  8.15e+03,  4.06e+03,  2.88e+03,  2.00e+03,  1.32e+03,  1.25e+03,  7.06e+02,  3.64e+02,  5.73e+01,  1.59e+02,  7.64e+01, -2.74e+01 },
          {  9.29e+05,  5.02e+05,  2.18e+05,  1.32e+05,  9.61e+04,  4.11e+04,  3.21e+04,  1.88e+04,  8.81e+03,  5.73e+03,  5.46e+03,  2.57e+03,  1.78e+03,  1.34e+03,  6.98e+02,  9.18e+02,  4.28e+02,  1.64e+02,  3.63e+01,  1.32e+02,  1.05e+02, -8.68e+00 },
          {  4.28e+05,  2.28e+05,  1.07e+05,  6.58e+04,  4.11e+04,  2.89e+04,  1.76e+04,  1.07e+04,  5.16e+03,  2.92e+03,  2.83e+03,  1.62e+03,  9.76e+02,  8.77e+02,  3.82e+02,  4.49e+02,  2.04e+02,  1.08e+02,  9.94e+01,  1.02e+02,  3.98e+01,  4.76e+00 },
          {  3.26e+05,  1.74e+05,  8.73e+04,  5.14e+04,  3.21e+04,  1.76e+04,  1.96e+04,  9.18e+03,  4.39e+03,  2.82e+03,  2.46e+03,  1.39e+03,  9.21e+02,  7.39e+02,  5.17e+02,  3.70e+02,  2.35e+02,  9.65e+01,  8.19e+01,  4.20e+01,  1.82e+01,  3.14e+01 },
          {  2.04e+05,  1.04e+05,  5.31e+04,  3.17e+04,  1.88e+04,  1.07e+04,  9.18e+03,  9.02e+03,  2.61e+03,  1.72e+03,  1.70e+03,  8.55e+02,  4.52e+02,  4.67e+02,  2.48e+02,  2.66e+02,  1.54e+02,  5.04e+01,  3.33e+01,  1.19e+01,  3.21e+01,  7.98e+00 },
          {  8.34e+04,  4.51e+04,  2.34e+04,  1.44e+04,  8.81e+03,  5.16e+03,  4.39e+03,  2.61e+03,  2.40e+03,  9.22e+02,  8.94e+02,  4.67e+02,  2.13e+02,  2.41e+02,  1.41e+02,  1.29e+02,  4.70e+01,  4.41e+01,  7.64e+00,  2.08e+01,  2.55e+01,  5.49e+00 },
          {  5.37e+04,  2.84e+04,  1.50e+04,  9.22e+03,  5.73e+03,  2.92e+03,  2.82e+03,  1.72e+03,  9.22e+02,  1.09e+03,  5.17e+02,  3.03e+02,  1.62e+02,  1.47e+02,  8.91e+01,  8.18e+01,  3.17e+01,  2.10e+01,  1.29e+00,  7.42e+00,  7.72e+00,  4.62e+00 },
          {  4.62e+04,  2.30e+04,  1.35e+04,  8.15e+03,  5.46e+03,  2.83e+03,  2.46e+03,  1.70e+03,  8.94e+02,  5.17e+02,  1.02e+03,  2.65e+02,  1.57e+02,  1.61e+02,  9.22e+01,  7.94e+01,  3.84e+01,  3.39e+00, -1.25e+00,  1.44e+01,  3.33e+00, -8.96e-01 },
          {  2.33e+04,  1.22e+04,  7.00e+03,  4.06e+03,  2.57e+03,  1.62e+03,  1.39e+03,  8.55e+02,  4.67e+02,  3.03e+02,  2.65e+02,  3.24e+02,  8.57e+01,  9.07e+01,  5.83e+01,  3.02e+01,  2.70e+01,  2.00e+01,  7.02e+00,  2.25e+00,  5.15e+00,  7.06e+00 },
          {  1.45e+04,  7.56e+03,  4.20e+03,  2.88e+03,  1.78e+03,  9.76e+02,  9.21e+02,  4.52e+02,  2.13e+02,  1.62e+02,  1.57e+02,  8.57e+01,  1.96e+02,  5.21e+01,  3.91e+01,  3.92e+01,  2.69e+01,  8.90e+00,  6.55e+00,  0.00e+00,  1.46e+00,  1.57e+00 },
          {  1.20e+04,  6.48e+03,  3.30e+03,  2.00e+03,  1.34e+03,  8.77e+02,  7.39e+02,  4.67e+02,  2.41e+02,  1.47e+02,  1.61e+02,  9.07e+01,  5.21e+01,  1.44e+02,  3.02e+01,  2.02e+01,  1.44e+01,  3.18e+00,  4.68e-01,  4.50e+00,  2.18e+00,  3.02e+00 },
          {  6.66e+03,  3.24e+03,  2.26e+03,  1.32e+03,  6.98e+02,  3.82e+02,  5.17e+02,  2.48e+02,  1.41e+02,  8.91e+01,  9.22e+01,  5.83e+01,  3.91e+01,  3.02e+01,  8.10e+01,  1.15e+01,  1.19e+01,  7.63e+00,  3.16e+00, -2.25e-01,  1.40e+00,  2.52e+00 },
          {  7.99e+03,  4.00e+03,  1.81e+03,  1.25e+03,  9.18e+02,  4.49e+02,  3.70e+02,  2.66e+02,  1.29e+02,  8.18e+01,  7.94e+01,  3.02e+01,  3.92e+01,  2.02e+01,  1.15e+01,  6.40e+01,  1.92e+00, -1.27e+00, -3.12e-01,  1.40e+00,  2.70e+00, -6.72e-01 },
          {  4.00e+03,  2.28e+03,  1.12e+03,  7.06e+02,  4.28e+02,  2.04e+02,  2.35e+02,  1.54e+02,  4.70e+01,  3.17e+01,  3.84e+01,  2.70e+01,  2.69e+01,  1.44e+01,  1.19e+01,  1.92e+00,  3.60e+01,  5.09e+00,  3.74e+00, -1.65e+00,  1.40e+00,  1.51e+00 },
          {  1.57e+03,  1.06e+03,  6.44e+02,  3.64e+02,  1.64e+02,  1.08e+02,  9.65e+01,  5.04e+01,  4.41e+01,  2.10e+01,  3.39e+00,  2.00e+01,  8.90e+00,  3.18e+00,  7.63e+00, -1.27e+00,  5.09e+00,  2.81e+01,  6.20e-01, -1.19e+00,  5.51e-01, -4.45e-01 },
          {  0.00e+00,  1.56e+02,  2.21e+02,  5.73e+01,  3.63e+01,  9.95e+01,  8.19e+01,  3.33e+01,  7.64e+00,  1.29e+00, -1.25e+00,  7.02e+00,  6.55e+00,  4.68e-01,  3.16e+00, -3.12e-01,  3.74e+00,  6.20e-01,  1.52e+01,  7.80e-01,  3.04e-01,  1.64e+00 },
          {  1.30e+03,  8.00e+02,  3.04e+02,  1.59e+02,  1.32e+02,  1.02e+02,  4.20e+01,  1.19e+01,  2.08e+01,  7.42e+00,  1.44e+01,  2.25e+00,  0.00e+00,  4.50e+00, -2.25e-01,  1.40e+00, -1.65e+00, -1.19e+00,  7.80e-01,  6.25e+00,  1.30e-01,  6.30e-01 },
          {  3.85e+02,  3.64e+02,  1.47e+02,  7.64e+01,  1.05e+02,  3.98e+01,  1.82e+01,  3.21e+01,  2.55e+01,  7.72e+00,  3.33e+00,  5.15e+00,  1.46e+00,  2.18e+00,  1.40e+00,  2.70e+00,  1.40e+00,  5.51e-01,  3.04e-01,  1.30e-01,  6.76e+00,  5.82e-01 },
          { -4.14e+02, -1.68e+02,  2.27e+01, -2.74e+01, -8.68e+00,  4.76e+00,  3.14e+01,  7.98e+00,  5.49e+00,  4.62e+00, -8.96e-01,  7.06e+00,  1.57e+00,  3.02e+00,  2.52e+00, -6.72e-01,  1.51e+00, -4.45e-01,  1.64e+00,  6.30e-01,  5.82e-01,  7.84e+00 }
        };
        set_covariance(BKGCOV);

      }

    protected:
      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }
        /// @todo Need to also clear/reset cutflow, but it currently has no method for that
      }

    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_MONOJET_36invfb)


  }
}
