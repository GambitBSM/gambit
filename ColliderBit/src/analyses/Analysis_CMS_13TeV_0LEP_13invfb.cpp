// -*- C++ -*-
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "Eigen/Eigen"

namespace Gambit {
  namespace ColliderBit {

    using namespace std;
    using namespace HEPUtils;


    /// @brief CMS Run 2 0-lepton jet+MET SUSY analysis, with 13/fb of data
    ///
    /// Based on:
    ///
    class Analysis_CMS_13TeV_0LEP_13invfb : public Analysis {
    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      // Numbers passing cuts
      static const size_t NUMSR = 12; //160;
      double _srnums[NUMSR];
      Cutflow _cutflow;

      Analysis_CMS_13TeV_0LEP_13invfb() :
        _cutflow("CMS 0-lep 13 TeV", {"Njet >= 3", "HT > 300", "HTmiss > 300", "Nmuon = 0", "Nelectron = 0", "Nhadron = 0 (no-op)", "Dphi_htmiss_j1", "Dphi_htmiss_j2", "Dphi_htmiss_j3", "Dphi_htmiss_j4"})
      {
        set_analysis_name("CMS_13TeV_0LEP_13invfb");
        set_luminosity(12.9);

        for (size_t i = 0; i < NUMSR; ++i) _srnums[i] = 0;
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
        vector<Particle*> baseelecs;
        for (Particle* electron : event->electrons())
          if (electron->pT() > 10. && electron->abseta() < 2.5)
            baseelecs.push_back(electron);

        // Apply electron efficiency
        CMS::applyElectronEff(baseelecs);

        // Get baseline muons
        vector<Particle*> basemuons;
        for (Particle* muon : event->muons())
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
        // _srnums[ibin] += 1;


        // Fill aggregate SR bins
        const size_t nj = jets24.size();
        size_t nbj = 0;
        for (const Jet* j : jets24) {
          if (j->pT() < 50 && j->abseta() > 2.5) continue;
          // b-tag effs: b: 0.55, c: 0.12, l: 0.016
          const bool btagged = Random::draw() < (j->btag() ? 0.55 : j->ctag() ? 0.12 : 0.016);
          if (btagged) nbj += 1;
        }
        if (nj >= 3 && nbj == 0 && ht >  500 && htmiss > 500) _srnums[ 0] += 1;
        if (nj >= 3 && nbj == 0 && ht > 1500 && htmiss > 750) _srnums[ 1] += 1;
        if (nj >= 5 && nbj == 0 && ht >  500 && htmiss > 500) _srnums[ 2] += 1;
        if (nj >= 5 && nbj == 0 && ht > 1500 && htmiss > 750) _srnums[ 3] += 1;
        if (nj >= 9 && nbj == 0 && ht > 1500 && htmiss > 750) _srnums[ 4] += 1;
        if (nj >= 3 && nbj >= 2 && ht >  500 && htmiss > 500) _srnums[ 5] += 1;
        if (nj >= 3 && nbj >= 1 && ht >  750 && htmiss > 750) _srnums[ 6] += 1;
        if (nj >= 5 && nbj >= 3 && ht >  500 && htmiss > 500) _srnums[ 7] += 1;
        if (nj >= 5 && nbj >= 2 && ht > 1500 && htmiss > 750) _srnums[ 8] += 1;
        if (nj >= 9 && nbj >= 3 && ht >  750 && htmiss > 750) _srnums[ 9] += 1;
        if (nj >= 7 && nbj >= 1 && ht >  300 && htmiss > 300) _srnums[10] += 1;
        if (nj >= 5 && nbj >= 1 && ht >  750 && htmiss > 750) _srnums[11] += 1;

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_0LEP_13invfb* specificOther = dynamic_cast<const Analysis_CMS_13TeV_0LEP_13invfb*>(other);
        for (size_t i = 0; i < NUMSR; ++i) _srnums[i] += specificOther->_srnums[i];
      }


      /// Register results objects with the results for each SR; obs & bkg numbers from the CONF note
      void collect_results() {
//        cout << _cutflow << endl;

        static const double OBSNUM[NUMSR] = {
          // 5180, 1780, 146, 2834, 2819, 202, 1070,  93, 134, 11, 1009, 411, 35, 512, 607, 47, 200, 27, 30, 4,   195, 77,  2,  65, 109,  9,   22,   6,   2,   1,    10,    3,  0,    3,   12,   2,   2,   0,   0,   0,
          // 334,   603,  93,  163,  734, 121,  149,  76,  32,  4,  164, 309, 43,  58, 293, 52,  54, 26,  6, 0,    54,133,  4,  11,  97, 14,    9,   9,   4,   1,    11,   13,  4,    1,   13,   3,   1,   2,   0,   0,
          // 8,      69,  27,    3,   78,  35,   14,  22,   3,  2,    6,  55, 26,   2,  42, 14,   9, 10,  1,  2,    2, 28, 13,   1,  23, 12,    2,   3,   1,   1,    2,     4,  4,    0,    1,   3,   1,   1,   0,   0,
          // 0,       3,   4,    0,    2,   4,    0,   3,   0,  1,    0,   2,  3,   0,   6,  4,   0,  3,  0,  1,    0,  9,  3,   0,   0,  3,    0,   1,   0,   0,    0,     3,  2,    0,    2,   3,   0,   2,   0,   0//,
          1614, 18, 306, 7,   1,   71, 54, 7,    2,  0, 316, 17
        };
        static const double BKGNUM[NUMSR] = {
          // 4942, 1671, 140, 2722, 2768, 205,  979, 104, 124,  7, 1081, 412, 38, 551, 563, 50, 181, 24, 22, 1.2, 164, 82, 6.2, 70, 116, 10.9, 19.6, 4.4, 2.2, 0.19, 13.6, 8.6, 1.03, 5.1, 11.0, 1.0, 1.3, 0.3, 0.2, 0.01,
          // 316,   566, 104,  111,  644, 129,  160,  60,  23, 7.5, 151, 279, 54,  46, 265, 53,  48, 24,  8, 2.7,  51,132, 19,  18, 105, 17,   12,   6.7, 1.5, 0.3,  3.4,  22,   2.5, 0.96,12.9, 4.7, 0.8, 0.5, 0.36,0.02,
          // 6.6,    68,  36,  2.4,   76,  40,   11,  16,  1.2, 1.2, 3.8, 58, 20,  1.7, 65, 25,   7, 16, 1.4,0.25, 1.2,44,  9,  0.4, 30, 16,    1.6, 4.5, 0.7, 0.5,  0.15, 14,   3.2, 0.1,  5,   4.8, 0.4, 1.7, 0.06,0.03,
          // 0,       3,   8,   0 ,  2.4, 9.8, 0.13, 2.8,  0.2, 0.2, 0.05, 5,  7,   0, 3.5, 6.4, 0.1,2.5, 0,  0,    0, 3.2, 7.2, 0,  2.1, 4.5,  0.3, 2.7,  0,   0,    0,   0.4,  1.8,  0,   1.3, 1.3,  0,  0.3, 0,   0//,
          1498, 15.9, 284, 8.9, 0.17, 63.3, 41.4, 4.2, 0.9, 0, 385, 15.9
        };
        static const double BKGERR[NUMSR] = { // these quadrature sums are partially guesstimated, to minimise pain!
          // 280,   119,  17,  153,  149,  22,  71,  13,  20,  2.6,  84,  39,  6,  48,  46, 7.6, 19,  5, 4.4,1.4,  21, 12, 2.8, 12, 14.5, 3.6,  4.5, 2.4, 1.7, 1.4,   5.1, 3.5, 2.0,  3.5,  4.5, 1.5, 2.0, 1.5, 1.5, 1.3,
          // 30,     45,  15,   13,   43,  15,  14,   9,  4.6, 2.5,  16,  25,  8,   7,  25, 7,   6.5,4.7,2.2,1.5,  8.3,15, 4.6,  5, 13,   3.7,  3.2, 2.2, 1.3, 1,     2.1, 5,   1.7,  1.9,  3.5, 2.3, 1.4, 1.2, 1.1, 1.0,
          // 2.4,     9,   7,   1.9,  10,  6,    3,  3.5, 1.2, 1.3,   2,   7,  4.5, 2,  10, 4,   2.1, 5, 1.3, 1,   1.2,7.6,2.5, 1.5, 5,   5,    1.3,   2, 1.2, 1.2,   1.1, 4,   1.6,  1.3,  2.1, 2,   1,   1.5, 1,   1,
          // 1,       2,   3,    1,   1.5, 5.2, 1.2, 1.5, 1.2, 1,     1,   2,  2.5, 1,  1.7,2.3, 1.3,1.6,1.2, 1,   1,  1.5,2.6,  1,  1.4, 1.9,  1.5, 1.8, 1.2, 1,     1,   1,   1.4,  1,    1.3, 1.2, 1.3, 1.2, 1.2, 1
          99.7, 3.91, 21.6, 2.86, 0.98, 11.2, 8.24, 4.24, 2.60, 1.60, 33.0, 5.47 //< quad sums of upper limits
        };
        for (size_t ibin = 0; ibin < NUMSR; ++ibin) {
          stringstream ss; ss << "sr-" << ibin;
          add_result(SignalRegionData(ss.str(), OBSNUM[ibin], {_srnums[ibin],  0.}, {BKGNUM[ibin], BKGERR[ibin]}));
        }
      }


    protected:
      void analysis_specific_reset() {
        for(size_t i=0;i<NUMSR;i++) { _srnums[i]=0; }
      }

    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_0LEP_13invfb)


  }
}
