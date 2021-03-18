// -*- C++ -*-
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "Eigen/Eigen"

namespace Gambit {
  namespace ColliderBit {

    using namespace std;
    using namespace HEPUtils;


    /// @brief CMS Run 2 0-lepton jet+MET SUSY analysis, with 137/fb of data
    ///
    /// Based on: http://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-19-006/index.html
    ///
    class Analysis_CMS_13TeV_0LEP_137invfb : public Analysis {
    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      // Numbers passing cuts
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
      };

      static const size_t NUMSR = 12;

      Cutflow _cutflow;


      Analysis_CMS_13TeV_0LEP_137invfb() :
        _cutflow("CMS 0-lep 13 TeV",
                 {"Njet >= 2", "HT > 300", "HTmiss > 300", "HTmiss/HT < 1",
                     "Nmuon = 0", "Nelectron = 0", "Nphoton = 0",
                     "Dphi_htmiss_j1", "Dphi_htmiss_j2", "Dphi_htmiss_j3", "Dphi_htmiss_j4",
                     "Evt quality"}) //, "SR HTmiss", "SR HT", "SR Njet", "SR Nbjet"}
      {
        set_analysis_name("CMS_13TeV_0LEP_137invfb");
        set_luminosity(137.0);
      }


      void run(const Event* event) {

        _cutflow.fillinit();

        // Get jets
        vector<const Jet*> jets24, jets50;
        for (const Jet* jet : event->jets()) {
          if (jet->pT() < 30) continue;
          if (jet->abseta() < 2.4) jets24.push_back(jet);
          if (jet->abseta() < 5.0) jets50.push_back(jet);
        }
        const size_t njets = jets24.size();
        if (njets < 2) return;
        _cutflow.fill(1);

        // Count b-jets
        size_t nbjets = 0;
        for (const Jet* j : jets24)
          if (random_bool(j->btag() ? 0.65 : j->ctag() ? 0.13 : 0.016))
            nbjets += 1;


        // HT cut
        double sumptj = 0;
        for (const Jet* j : jets24) sumptj += j->pT();
        const double ht = sumptj;
        if (ht < 300) return;
        _cutflow.fill(2);

        // HTmiss cut, from full set of jets
        P4 htvec;
        for (const Jet* jet : jets50) htvec += jet->mom();
        const double htmiss = htvec.pT();
        if (htmiss < 300) return;
        _cutflow.fill(3);

        // HTmiss/HT cut
        if (htmiss/ht >= 1) return;
        _cutflow.fill(4);


        // Get baseline photons
        vector<const Particle*> basephotons;
        for (const Particle* gamma : event->photons())
          if (gamma->pT() > 10. && gamma->abseta() < 2.4)
            basephotons.push_back(gamma);

        // Get baseline electrons and apply efficiency
        vector<const Particle*> baseelecs;
        for (const Particle* electron : event->electrons())
          if (electron->pT() > 10. && electron->abseta() < 2.5)
            baseelecs.push_back(electron);
        CMS::applyElectronEff(baseelecs);

        // Get baseline muons and apply efficiency
        vector<const Particle*> basemuons;
        for (const Particle* muon : event->muons())
          if (muon->pT() > 10. && muon->abseta() < 2.4)
            basemuons.push_back(muon);
        CMS::applyMuonEff(basemuons);


        // Photon isolation
        /// @todo Sum should actually be over all calo particles
        vector<const Particle*> photons;
        for (const Particle* y : basephotons) {
          const double R = 0.3;
          double sumpt = -y->pT();
          for (const Jet* j : jets50)
            if (y->mom().deltaR_eta(j->mom()) < R) sumpt += j->pT();
          if (sumpt/y->pT() < 0.1) photons.push_back(y); //< guess at threshold: real one not given, and varies between endcap/barrel
        }

        // Electron isolation
        /// @todo Sum should actually be over all non-e/mu calo particles
        vector<const Particle*> elecs;
        for (const Particle* e : baseelecs) {
          const double R = max(0.05, min(0.2, 10/e->pT()));
          double sumpt = -e->pT();
          for (const Jet* j : jets50)
            if (e->mom().deltaR_eta(j->mom()) < R) sumpt += j->pT();
          if (sumpt/e->pT() < 0.1) elecs.push_back(e);
        }

        // Muon isolation
        /// @todo Sum should actually be over all non-e/mu calo particles
        vector<const Particle*> muons;
        for (const Particle* m : basemuons) {
          const double R = max(0.05, min(0.2, 10/m->pT()));
          double sumpt = -m->pT();
          for (const Jet* j : jets50)
            if (m->mom().deltaR_eta(j->mom()) < R) sumpt += j->pT();
          if (sumpt/m->pT() < 0.2) muons.push_back(m);
        }


        // Veto the event if there are any remaining baseline leptons
        if (!muons.empty()) return;
        _cutflow.fill(5);
        if (!elecs.empty()) return;
        _cutflow.fill(6);

        // Veto high-pT photons (should have negligible effect)
        if (!photons.empty() && photons[0]->pT() > 100) return;
        _cutflow.fill(7);


        // Lead jets isolation from Htmiss
        if (deltaPhi(-htvec, jets24[0]->mom()) < 0.5) return;
        _cutflow.fill(8);
        if (deltaPhi(-htvec, jets24[1]->mom()) < 0.5) return;
        _cutflow.fill(9);
        if (jets24.size() >= 3 && deltaPhi(-htvec, jets24[2]->mom()) < 0.3) return;
        _cutflow.fill(10);
        if (jets24.size() >= 4 && deltaPhi(-htvec, jets24[3]->mom()) < 0.3) return;
        _cutflow.fill(11);


        // Downweight for event quality inefficiency
        const double w = 0.95 * event->weight();
        const double werr = 0.95 * event->weight_err();
        if (random_bool(0.95)) _cutflow.fill(12);


        // Fill aggregate SR bins
        if (htmiss >= 600 && ht >=  600 && njets >=  2 && nbjets == 0) _counters.at("SR1").add_event(w,werr);
        if (htmiss >= 850 && ht >= 1700 && njets >=  4 && nbjets == 0) _counters.at("SR2").add_event(w,werr);
        if (htmiss >= 600 && ht >=  600 && njets >=  6 && nbjets == 0) _counters.at("SR3").add_event(w,werr);
        if (htmiss >= 600 && ht >=  600 && njets >=  8 && nbjets <= 1) _counters.at("SR4").add_event(w,werr);
        if (htmiss >= 850 && ht >= 1700 && njets >= 10 && nbjets <= 1) _counters.at("SR5").add_event(w,werr);
        if (htmiss >= 300 && ht >=  300 && njets >=  4 && nbjets >= 2) _counters.at("SR6").add_event(w,werr);
        if (htmiss >= 600 && ht >=  600 && njets >=  2 && nbjets >= 2) _counters.at("SR7").add_event(w,werr);
        if (htmiss >= 350 && ht >=  350 && njets >=  6 && nbjets >= 2) _counters.at("SR8").add_event(w,werr);
        if (htmiss >= 600 && ht >=  600 && njets >=  4 && nbjets >= 2) _counters.at("SR9").add_event(w,werr);
        if (htmiss >= 300 && ht >=  300 && njets >=  8 && nbjets >= 3) _counters.at("SR10").add_event(w,werr);
        if (htmiss >= 600 && ht >=  600 && njets >=  6 && nbjets >= 1) _counters.at("SR11").add_event(w,werr);
        if (htmiss >= 850 && ht >=  850 && njets >= 10 && nbjets >= 3) _counters.at("SR12").add_event(w,werr);

      }


      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_0LEP_137invfb* specificOther = dynamic_cast<const Analysis_CMS_13TeV_0LEP_137invfb*>(other);
        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }


      /// Register results objects with the results for each SR; obs & bkg numbers from the CONF note
      void collect_results() {

        add_result(SignalRegionData(_counters.at("SR1"), 11281., {12319., add_quad(85., 450.)} ));
        add_result(SignalRegionData(_counters.at("SR2"), 74., {65.8, add_quad(6.0, 4.9)} ));
        add_result(SignalRegionData(_counters.at("SR3"), 505., {489., add_quad(15., 18.)} ));
        add_result(SignalRegionData(_counters.at("SR4"), 63., {54.3, add_quad(5.5, 2.5)} ));
        add_result(SignalRegionData(_counters.at("SR5"), 153., {141., add_quad(10., 9.)} ));
        add_result(SignalRegionData(_counters.at("SR6"), 10216., {10091., add_quad(115., 330.)} ));
        add_result(SignalRegionData(_counters.at("SR7"), 287., {336., add_quad(15., 26.)} ));
        add_result(SignalRegionData(_counters.at("SR8"), 1637., {1720., add_quad(35., 47.)} ));
        add_result(SignalRegionData(_counters.at("SR9"), 224., {230., add_quad(13., 12.)} ));
        add_result(SignalRegionData(_counters.at("SR10"), 168., {176., add_quad(11., 11.)} ));
        add_result(SignalRegionData(_counters.at("SR11"), 282., {304., add_quad(14., 16.)} ));
        add_result(SignalRegionData(_counters.at("SR12"), 0., {0.1, add_quad(1.2, 0.1)} ));


        // Cutflow printout
        // const double sf = 137*crossSection()/femtobarn/sumOfWeights();
        // _cutflows.scale(sf);
        cout << "\nCUTFLOWS:\n" << _cutflow << "\n" << endl;
        cout << "\nSRCOUNTS:\n";
        // Note: The sum() call below gives the raw event count. Use weight_sum() for the sum of event weights.
        for (auto& pair : _counters) cout << pair.second.sum() << "  ";
        cout << "\n" << endl;
      }


    protected:

      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }
      }



    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_0LEP_137invfb)


  }
}
