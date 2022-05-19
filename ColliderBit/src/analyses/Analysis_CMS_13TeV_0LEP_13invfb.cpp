// -*- C++ -*-
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

namespace Gambit {
  namespace ColliderBit {

    using namespace std;
    using namespace HEPUtils;


    /// @brief CMS Run 2 0-lepton jet+MET SUSY analysis, with 13/fb of data
    ///
    /// Based on: CMS-SUS-16-014,  http://cms-results.web.cern.ch/cms-results/public-results/preliminary-results/SUS-16-014/index.html
    ///
    class Analysis_CMS_13TeV_0LEP_13invfb : public Analysis {
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

      static const size_t NUMSR = 12; //160;

      Cutflow _cutflow;

      Analysis_CMS_13TeV_0LEP_13invfb() :
        _cutflow("CMS 0-lep 13 TeV", {"Njet >= 3", "HT > 300", "HTmiss > 300", "Nmuon = 0", "Nelectron = 0", "Nhadron = 0 (no-op)", "Dphi_htmiss_j1", "Dphi_htmiss_j2", "Dphi_htmiss_j3", "Dphi_htmiss_j4"})
      {
        set_analysis_name("CMS_13TeV_0LEP_13invfb");
        set_luminosity(12.9);
      }


      void run(const Event* event) {

        _cutflow.fillinit();

        // FinalState isofs(Cuts::abseta < 3.0 && Cuts::abspid != PID::ELECTRON && Cuts::abspid != PID::MUON);
        // FinalState cfs(Cuts::abseta < 2.5 && Cuts::abscharge != 0);

        // Get baseline jets
        vector<const Jet*> jets24, jets50;
        for (const Jet* jet : event->jets()) {
          if (jet->pT() < 30) continue;
          if (jet->abseta() < 2.4) jets24.push_back(jet);
          if (jet->abseta() < 5.0) jets50.push_back(jet);
        }
        if (jets24.size() < 3) return;
        _cutflow.fill(1);

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


        // Get baseline electrons
        vector<const Particle*> baseelecs;
        for (const Particle* electron : event->electrons())
          if (electron->pT() > 10. && electron->abseta() < 2.5)
            baseelecs.push_back(electron);

        // Apply electron efficiency
        CMS::applyElectronEff(baseelecs);

        // Get baseline muons
        vector<const Particle*> basemuons;
        for (const Particle* muon : event->muons())
          if (muon->pT() > 10. && muon->abseta() < 2.4)
            basemuons.push_back(muon);

        // Apply electron efficiency
        CMS::applyMuonEff(basemuons);

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
        _cutflow.fill(4);
        if (!elecs.empty()) return;
        _cutflow.fill(5);


        /// @todo Need access to charged hadrons to do this isolation
        // // Get isolated tracks
        // Particles trks25 = apply<ParticleFinder>(event, "Tracks").particles();
        // ifilter_discard(trks25, [&](const Particle& t) {
        //     double ptsum = -t->pT();
        //     for (const Particle& p : trks25)
        //       if (deltaR(p,t) < 0.3) ptsum += p->pT();
        //     return ptsum/t->pT() > ((t.abspid() == PID::ELECTRON || t.abspid() == PID::MUON) ? 0.2 : 0.1);
        //   });
        // const Particles trks = filter_select(trks25, Cuts::abseta < 2.4);
        //
        // // Isolated track pT, pTmiss and mT cut
        // // mT^2 = m1^2 + m2^2 + 2(ET1 ET2 - pT1 . pT2))
        // // => mT0^2 = 2(ET1 |pT2| - pT1 . pT2)) for m1, m2 -> 0
        // FourMomentum ptmissvec = htmissvec; ///< @todo Can we do better? No e,mu left...
        // const double ptmiss = ptmissvec->pT();
        // for (const Particle& t : trks) {
        //   const double ptcut = (t.abspid() == PID::ELECTRON || t.abspid() == PID::MUON) ? 5 : 10;
        //   const double mT = sqrt( t.mass2() + 2*(t.Et()*ptmiss - t->pT()*ptmiss*cos(deltaPhi(t,ptmissvec))) );
        //   if (mT < 100 && t->pT() < ptcut) vetoEvent;
        // }
        _cutflow.fill(6);


        // Lead jets isolation from Htmiss
        if (deltaPhi(-htvec, jets24[0]->mom()) < 0.5) return;
        _cutflow.fill(7);
        if (deltaPhi(-htvec, jets24[1]->mom()) < 0.5) return;
        _cutflow.fill(8);
        if (deltaPhi(-htvec, jets24[2]->mom()) < 0.3) return;
        _cutflow.fill(9);
        if (jets24.size() >= 4 && deltaPhi(-htvec, jets24[3]->mom()) < 0.3) return;
        _cutflow.fill(10);


        ////////


        // // Calculate a bin index for this event
        // // Nj bin
        // static const vector<double> njedges = {3., 5., 7., 9.};
        // const size_t nj = jets24.size();
        // const size_t inj = binIndex(nj, njedges, true);
        // // Nbj bin
        // static const vector<double> njbedges = {0., 1., 2., 3.};
        // size_t nbj = 0;
        // for (const Jet* j : jets24) {
        //   if (j->pT() < 50 && j->abseta() > 2.5) continue;
        //   // b-tag effs: b: 0.55, c: 0.12, l: 0.016
        //   const bool btagged = Random::draw() < (j->btag() ? 0.55 : j->ctag() ? 0.12 : 0.016);
        //   if (btagged) nbj += 1;
        // }
        // const size_t inbj = binIndex(nbj, njbedges, true);
        // // HTmiss vs HT 2D bin
        // int iht = 0;
        // if (htmiss < 350) {
        //   iht = ht < 500 ? 1 : ht < 1000 ? 2 : 3;
        // } else if (htmiss < 500 && ht > 350) {
        //   iht = ht < 500 ? 4 : ht < 1000 ? 5 : 6;
        // } else if (htmiss < 750 && ht > 500) {
        //   iht = ht < 1000 ? 7 : 8;
        // } else if (ht > 750) {
        //   iht = ht < 1500 ? 9 : 10;
        // }

        // // Calc total bin number and fill SR counter (NB. no overlaps)
        // if (iht == 0) return;
        // iht -= 1; //< change from the paper's indexing scheme to C++ zero-indexed
        // const size_t ibin = 40*inj + 10*inbj + (size_t)iht;
        // if (ibin >= NUMSR) throw std::runtime_error("ibin out of range");
        // _srnums[ibin] += event->weight();


        // Fill aggregate SR bins
        const size_t nj = jets24.size();
        size_t nbj = 0;
        for (const Jet* j : jets24) {
          if (j->pT() < 50 && j->abseta() > 2.5) continue;
          // b-tag effs: b: 0.55, c: 0.12, l: 0.016
          const bool btagged = Random::draw() < (j->btag() ? 0.55 : j->ctag() ? 0.12 : 0.016);
          if (btagged) nbj += 1;
        }
        if (nj >= 3 && nbj == 0 && ht >  500 && htmiss > 500) _counters.at("SR1").add_event(event);
        if (nj >= 3 && nbj == 0 && ht > 1500 && htmiss > 750) _counters.at("SR2").add_event(event);
        if (nj >= 5 && nbj == 0 && ht >  500 && htmiss > 500) _counters.at("SR3").add_event(event);
        if (nj >= 5 && nbj == 0 && ht > 1500 && htmiss > 750) _counters.at("SR4").add_event(event);
        if (nj >= 9 && nbj == 0 && ht > 1500 && htmiss > 750) _counters.at("SR5").add_event(event);
        if (nj >= 3 && nbj >= 2 && ht >  500 && htmiss > 500) _counters.at("SR6").add_event(event);
        if (nj >= 3 && nbj >= 1 && ht >  750 && htmiss > 750) _counters.at("SR7").add_event(event);
        if (nj >= 5 && nbj >= 3 && ht >  500 && htmiss > 500) _counters.at("SR8").add_event(event);
        if (nj >= 5 && nbj >= 2 && ht > 1500 && htmiss > 750) _counters.at("SR9").add_event(event);
        if (nj >= 9 && nbj >= 3 && ht >  750 && htmiss > 750) _counters.at("SR10").add_event(event);
        if (nj >= 7 && nbj >= 1 && ht >  300 && htmiss > 300) _counters.at("SR11").add_event(event);
        if (nj >= 5 && nbj >= 1 && ht >  750 && htmiss > 750) _counters.at("SR12").add_event(event);

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_0LEP_13invfb* specificOther = dynamic_cast<const Analysis_CMS_13TeV_0LEP_13invfb*>(other);
        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }


      /// Register results objects with the results for each SR; obs & bkg numbers from the CONF note
      void collect_results() {

        // The bkg errors are the quad sums of upper limits
        add_result(SignalRegionData(_counters.at("SR1"), 1614., {1498., 99.7} ));
        add_result(SignalRegionData(_counters.at("SR2"), 18., {15.9, 3.91} ));
        add_result(SignalRegionData(_counters.at("SR3"), 306., {284., 21.6} ));
        add_result(SignalRegionData(_counters.at("SR4"), 7., {8.9, 2.86} ));
        add_result(SignalRegionData(_counters.at("SR5"), 1., {0.17, 0.98} ));
        add_result(SignalRegionData(_counters.at("SR6"), 71., {63.3, 11.2} ));
        add_result(SignalRegionData(_counters.at("SR7"), 54., {41.4, 8.24} ));
        add_result(SignalRegionData(_counters.at("SR8"), 7., {4.2, 4.24} ));
        add_result(SignalRegionData(_counters.at("SR9"), 2., {0.9, 2.60} ));
        add_result(SignalRegionData(_counters.at("SR10"), 0., {0., 1.60} ));
        add_result(SignalRegionData(_counters.at("SR11"), 316., {385., 33.0} ));
        add_result(SignalRegionData(_counters.at("SR12"), 17., {15.9, 5.47} ));

      }


    protected:
      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_0LEP_13invfb)


  }
}
