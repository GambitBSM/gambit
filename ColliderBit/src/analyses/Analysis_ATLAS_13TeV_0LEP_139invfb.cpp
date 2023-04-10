// -*- C++ -*-
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

#include "gambit/Utils/begin_ignore_warnings_eigen.hpp"
#include "Eigen/Eigen"
#include "gambit/Utils/end_ignore_warnings.hpp"

// #define CHECK_CUTFLOW

namespace Gambit
{
  namespace ColliderBit
  {

    using namespace std;
    using namespace HEPUtils;


    /// @brief ATLAS Run 2 0-lepton jet+MET SUSY analysis, with 139/fb of data
    ///
    /// Originally based on this confnote:
    ///   https://cds.cern.ch/record/2686254
    ///   https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2019-040/
    /// Updated to the paper version:
    ///   https://arxiv.org/abs/2010.14293
    ///   https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-22/

    class Analysis_ATLAS_13TeV_0LEP_139invfb : public Analysis
    {
      public:

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        // Numbers passing cuts
        std::map<string, EventCounter> _counters = {
          {"2j-1600", EventCounter("2j-1600")},
          {"2j-2200", EventCounter("2j-2200")},
          {"2j-2800", EventCounter("2j-2800")},
          {"4j-1000", EventCounter("4j-1000")},
          {"4j-2200", EventCounter("4j-2200")},
          {"4j-3400", EventCounter("4j-3400")},
          {"5j-1600", EventCounter("5j-1600")},
          {"6j-1000", EventCounter("6j-1000")},
          {"6j-2200", EventCounter("6j-2200")},
          {"6j-3400", EventCounter("6j-3400")},
        };

        Cutflows _cutflows;


        // static const size_t NUMSR = 10;
        // double _srnums[NUMSR] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
        // enum SRNames { SR2J_1600=0, "2j_2200", "2j_2800",
        //                "4j_1000", "4j_2200", "4j_3400", "5j_1600",
        //                "6j_1000", "6j_2200", "6j_3400" };


        Analysis_ATLAS_13TeV_0LEP_139invfb()
        {

          set_analysis_name("ATLAS_13TeV_0LEP_139invfb");
          set_luminosity(139.0);

          // Book cut-flows
          const vector<string> cutnames = {"Pre-sel + MET + pT1 + meff",
                                           "Njet >= 2", "Cleaning",
                                           "Njet > x + pT1",
                                           "Dphi(j123,MET)min", "Dphi(j4+,MET)min",
                                           "pTx", "|eta_x|",
                                           "Aplanarity", "MET/sqrt(HT)", "m_eff(incl)",};
          _cutflows.addCutflow("2j-1600", cutnames);
          _cutflows.addCutflow("2j-2200", {"Pre-sel + MET + pT1 + meff",
                                           "Njet >= 2", "Cleaning",
                                           "Dphi(j123,MET)min", "Dphi(j4+,MET)min",
                                           "pT1", "|eta_x|",
                                           "MET/sqrt(HT)", "m_eff(incl)",});
          _cutflows.addCutflow("2j-2800", cutnames);
          _cutflows.addCutflow("4j-1000", cutnames);
          _cutflows.addCutflow("4j-2200", cutnames);
          _cutflows.addCutflow("4j-3400", cutnames);
          _cutflows.addCutflow("5j-1600", cutnames);
          _cutflows.addCutflow("6j-1000", cutnames);
          _cutflows.addCutflow("6j-2200", cutnames);
          _cutflows.addCutflow("6j-3400", cutnames);

        }

        void run(const Event* event)
        {
          //cout << "PROCESSING EVENT!!!" << endl;

          // Missing energy
          /// @todo Compute from hard objects instead?
          const P4 pmiss = event->missingmom();
          const double met = event->met();


          // Get baseline jets
          /// @todo Drop b-tag if pT < 50 GeV or |eta| > 2.5?
          vector<const Jet*> baselineJets;
          for (const Jet* jet : event->jets())
          {
            if (jet->pT() > 20. && jet->abseta() < 2.8)
            {
              baselineJets.push_back(jet);
            }
          }


          /// @todo Apply a random 9% loss / 0.91 reweight for jet quality criteria?

          // Get baseline electrons and apply efficiency
          vector<const Particle*> baselineElectrons;
          for (const Particle* electron : event->electrons())
          {
            if (electron->pT() > 7. && electron->abseta() < 2.47)
              baselineElectrons.push_back(electron);
          }
          ATLAS::applyElectronEff(baselineElectrons);

          // Get baseline muons and apply efficiency
          vector<const Particle*> baselineMuons;
          for (const Particle* muon : event->muons())
          {
            if (muon->pT() > 6. && muon->abseta() < 2.7)
              baselineMuons.push_back(muon);
          }
          ATLAS::applyMuonEff(baselineMuons);

          // Remove any |eta| < 2.8 jet within dR = 0.2 of an electron
          vector<const Jet*> signalJets;
          for (const Jet* j : baselineJets)
            if (all_of(baselineElectrons, [&](const Particle* e){ return deltaR_rap(*e, *j) > 0.2; }))
              signalJets.push_back(j);

          // Remove electrons with dR = shrinking cone of surviving |eta| < 2.8 jets
          vector<const Particle*> signalElectrons;
          for (const Particle* e : baselineElectrons)
            if (all_of(signalJets, [&](const Jet* j){ return deltaR_rap(*e, *j) > min(0.4, 0.04+10/e->pT()); }))
              signalElectrons.push_back(e);
          // Apply electron ID selection
          ATLAS::applyLooseIDElectronSelectionR2(signalElectrons);
          /// @todo And tight ID for high purity... used where?

          // Remove muons with dR = 0.4 of surviving |eta| < 2.8 jets
          /// @note Within 0.2, discard the *jet* based on jet track vs. muon criteria... can't be done yet
          vector<const Particle*> signalMuons;
          for (const Particle* m : baselineMuons)
            if (all_of(signalJets, [&](const Jet* j){ return deltaR_rap(*m, *j) > min(0.4, 0.04+10/m->pT()); }))
              signalMuons.push_back(m);
          /// @todo And tight ID for high purity... used where?

          // The subset of jets with pT > 50 GeV is used for several calculations
          vector<const Jet*> signalJets50;
          for (const Jet* j : signalJets)
            if (j->pT() > 50) signalJets50.push_back(j);


          ////////////////////////////////
          // Calculate common variables and cuts

          // Multiplicities
          const size_t nElectrons = signalElectrons.size();
          const size_t nMuons = signalMuons.size();
          const size_t nJets50 = signalJets50.size();
          // const size_t nJets = signalJets.size();

          // HT-related quantities (calculated over all >50 GeV jets)
          double sumptj = 0;
          for (const Jet* j : signalJets50) sumptj += j->pT();
          const double HT = sumptj;
          const double sqrtHT = sqrt(HT);
          const double met_sqrtHT = met/sqrtHT;

          // Meff-related quantities (calculated over >50 GeV jets only)
          double sumptj50_incl = 0; // sumptj50_4 = 0, sumptj50_5 = 0, sumptj50_6 = 0;
          for (size_t i = 0; i < signalJets50.size(); ++i)
          {
            const Jet* j = signalJets50[i];
            // if (i < 4) sumptj50_4 += j->pT();
            // if (i < 5) sumptj50_5 += j->pT();
            // if (i < 6) sumptj50_6 += j->pT();
            sumptj50_incl += j->pT();
          }
          // const double meff_4 = met + sumptj50_4;
          // const double meff_5 = met + sumptj50_5;
          // const double meff_6 = met + sumptj50_6;
          // const double meff_incl = met + sumptj50_incl;
          const double meff = met + sumptj50_incl;
          // const double met_meff_4 = met / meff_4;
          // const double met_meff_5 = met / meff_5;
          // const double met_meff_6 = met / meff_6;

          // Jet |eta|s
          double etamax_2 = 0, etamax_4 = 0, etamax_5 = 0, etamax_6 = 0;
          for (size_t i = 0; i < signalJets50.size(); ++i)
          {
            const Jet* j = signalJets50[i];
            if (i < 2) etamax_2 = max(etamax_2, j->abseta());
            if (i < 4) etamax_4 = max(etamax_4, j->abseta());
            if (i < 5) etamax_5 = max(etamax_5, j->abseta());
            if (i < 6) etamax_6 = max(etamax_6, j->abseta());
          }

          // Jet--MET dphis
          double dphimin_123 = DBL_MAX, dphimin_more = DBL_MAX;
          for (size_t i = 0; i < min(3lu,signalJets50.size()); ++i)
            dphimin_123 = min(dphimin_123, acos(cos(signalJets50[i]->phi() - pmiss.phi())));
          for (size_t i = 3; i < signalJets50.size(); ++i)
            dphimin_more = min(dphimin_more, acos(cos(signalJets50[i]->phi() - pmiss.phi())));

          // Jet aplanarity (on 50 GeV jets only, cf. paper)
          Eigen::Matrix3d momtensor = Eigen::Matrix3d::Zero();
          double norm = 0;
          for (const Jet* jet : signalJets50)
          {
            const P4& p4 = jet->mom();
            norm += p4.p2();
            for (size_t i = 0; i < 3; ++i)
            {
              const double pi = (i == 0) ? p4.px() : (i == 1) ? p4.py() : p4.pz();
              for (size_t j = 0; j < 3; ++j)
              {
                const double pj = (j == 0) ? p4.px() : (j == 1) ? p4.py() : p4.pz();
                momtensor(i,j) += pi*pj;
              }
            }
          }
          momtensor /= norm;
          const double mineigenvalue = momtensor.eigenvalues().real().minCoeff();
          const double aplanarity = 1.5 * mineigenvalue;


          ////////////////////////////////
          // Fill signal regions and cutflows

          const double w = event->weight();
          _cutflows.fillinit(w);

          // Preselection
          if (nElectrons + nMuons != 0) return;
          if (nJets50 < 1 || signalJets50[0]->pT() < 200) return;
          if (met < 300) return;
          if (meff < 800) return;
          if (dphimin_123 < 0.2) return;
          _cutflows.fillnext(w);

          // Njet >= 2
          if (nJets50 < 2) return;
          _cutflows.fillnext(w);

          // Cleaning emulation
          /// @todo Use weighting instead
          if (random_bool(0.02)) return;
          _cutflows.fillnext(w);

          // 2 jet regions
          if (nJets50 >= 2)
          {
            if (_cutflows["2j-1600"].fillnext({
                  signalJets[0]->pT() > 250,
                  dphimin_123 > 0.8, dphimin_more > 0.4,
                  signalJets[1]->pT() > 250, etamax_2 < 2.0,
                  true, met_sqrtHT > 16, meff > 1600}, w)) _counters.at("2j-1600").add_event(event);

            if (_cutflows["2j-2200"].fillnext({
                  dphimin_123 > 0.4, dphimin_more > 0.2,
                  signalJets[0]->pT() > 600, etamax_2 < 2.8,
                  met_sqrtHT > 16, meff > 2200}, w)) _counters.at("2j-2200").add_event(event);
            if (_cutflows["2j-2800"].fillnext({
                  signalJets[0]->pT() > 250,
                  dphimin_123 > 0.8, dphimin_more > 0.4,
                  signalJets[1]->pT() > 250, etamax_2 < 1.2,
                  true, met_sqrtHT > 16, meff > 2800}, w)) _counters.at("2j-2800").add_event(event);
          }

          // 4 jet regions
          if (nJets50 >= 4)
          {
            if (_cutflows["4j-1000"].fillnext({
                  signalJets.at(0)->pT() > 200,
                  dphimin_123 > 0.4, dphimin_more > 0.2,
                  signalJets.at(3)->pT() > 100, etamax_4 < 2.0,
                  aplanarity > 0.04, met_sqrtHT > 16, meff > 1000}, w)) _counters.at("4j-1000").add_event(event);
            if (_cutflows["4j-2200"].fillnext({
                  signalJets[0]->pT() > 200,
                  dphimin_123 > 0.4, dphimin_more > 0.2,
                  signalJets[3]->pT() > 100, etamax_4 < 2.0,
                  aplanarity > 0.04, met_sqrtHT > 16, meff > 2200}, w)) _counters.at("4j-2200").add_event(event);
            if (_cutflows["4j-3400"].fillnext({
                  signalJets[0]->pT() > 200,
                  dphimin_123 > 0.4, dphimin_more > 0.2,
                  signalJets[3]->pT() > 100, etamax_4 < 2.0,
                  aplanarity > 0.04, met_sqrtHT > 10, meff > 3400}, w)) _counters.at("4j-3400").add_event(event);
          }

          // 5 jet region
          if (nJets50 >= 5)
          {
            if (_cutflows["5j-1600"].fillnext({
                  signalJets[0]->pT() > 600,
                  dphimin_123 > 0.4, dphimin_more > 0.2,
                  signalJets[4]->pT() > 50, etamax_5 < 2.8,
                  true, met_sqrtHT > 16, meff > 1600}, w)) _counters.at("5j-1600").add_event(event);
          }

          // 6 jet regions
          if (nJets50 >= 6)
          {
            if (_cutflows["6j-1000"].fillnext({
                  signalJets[0]->pT() > 200,
                  dphimin_123 > 0.4, dphimin_more > 0.2,
                  signalJets[5]->pT() > 75, etamax_6 < 2.0,
                  aplanarity > 0.08, met_sqrtHT > 16, meff > 1000}, w)) _counters.at("6j-1000").add_event(event);
            if (_cutflows["6j-2200"].fillnext({
                  signalJets[0]->pT() > 200,
                  dphimin_123 > 0.4, dphimin_more > 0.2,
                  signalJets[5]->pT() > 75, etamax_6 < 2.0,
                  aplanarity > 0.08, met_sqrtHT > 16, meff > 2200}, w)) _counters.at("6j-2200").add_event(event);
            if (_cutflows["6j-3400"].fillnext({
                  signalJets[0]->pT() > 200,
                  dphimin_123 > 0.4, dphimin_more > 0.2,
                  signalJets[5]->pT() > 75, etamax_6 < 2.0,
                  aplanarity > 0.08, met_sqrtHT > 10, meff > 3400}, w)) _counters.at("6j-3400").add_event(event);
          }

        }


        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
          const Analysis_ATLAS_13TeV_0LEP_139invfb* specificOther = dynamic_cast<const Analysis_ATLAS_13TeV_0LEP_139invfb*>(other);
          for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }


        /// Register results objects with the results for each SR; obs & bkg numbers from the CONF note
        void collect_results()
        {
          add_result(SignalRegionData(_counters.at("2j-1600"), 2111, {2190., 130.}));
          add_result(SignalRegionData(_counters.at("2j-2200"),  971, { 980.,  50.}));
          add_result(SignalRegionData(_counters.at("2j-2800"),   78, {  87.,   8.}));
          add_result(SignalRegionData(_counters.at("4j-1000"),  535, { 536.,  32.}));
          add_result(SignalRegionData(_counters.at("4j-2200"),   60, {  60.,   5.}));
          add_result(SignalRegionData(_counters.at("4j-3400"),    4, {  5.7,  1.0}));
          add_result(SignalRegionData(_counters.at("5j-1600"),  320, { 319.,  20.}));
          add_result(SignalRegionData(_counters.at("6j-1000"),   25, {  21.,  3.}));
          add_result(SignalRegionData(_counters.at("6j-2200"),    5, {  4.6,  1.0}));
          add_result(SignalRegionData(_counters.at("6j-3400"),    0, {  0.8,  0.4}));

          // Cutflow printout
          #ifdef CHECK_CUTFLOW
            // const double sf = 139*crossSection()/femtobarn/sumOfWeights();

            // // Confnote cutflows:
            // _cutflows["2j-1600"].normalize(1763, 1);
            // _cutflows["2j-2200"].normalize(1763, 1);
            // _cutflows["2j-2800"].normalize(1763, 1);
            // _cutflows["4j-1000"].normalize(2562, 1);
            // _cutflows["4j-2200"].normalize(2562, 1);
            // _cutflows["4j-3400"].normalize(2562, 1);
            // _cutflows["5j-1600"].normalize(6101, 1);
            // _cutflows["6j-1000"].normalize(6101, 1);
            // _cutflows["6j-2200"].normalize(6101, 1);
            // _cutflows["6j-3400"].normalize(6101, 1);

            // Paper cutflows:
            _cutflows["2j-1600"].normalize(1423, 1);  // m_sq = 1200, m_N1 = 600, direct decay
            _cutflows["2j-2200"].normalize(1423, 1);  // m_sq = 1200, m_N1 = 600, direct decay
            _cutflows["2j-2800"].normalize(1423, 1);  // m_sq = 1200, m_N1 = 600, direct decay
            _cutflows["4j-1000"].normalize(1787, 1);  // m_g = 1400, m_N1 = 1000, direct decay
            _cutflows["4j-2200"].normalize(1787, 1);  // m_g = 1400, m_N1 = 1000, direct decay
            _cutflows["4j-3400"].normalize(1787, 1);  // m_g = 1400, m_N1 = 1000, direct decay
            _cutflows["5j-1600"].normalize(1787, 1);  // m_g = 1400, m_N1 = 1000, direct decay
            _cutflows["6j-1000"].normalize(2651, 1);  // m_q = 800, m_C1 = 600, m_N1 = 400, one-step decay
            _cutflows["6j-2200"].normalize(2651, 1);  // m_q = 800, m_C1 = 600, m_N1 = 400, one-step decay
            _cutflows["6j-3400"].normalize(2651, 1);  // m_q = 800, m_C1 = 600, m_N1 = 400, one-step decay


            cout << "\nCUTFLOWS:\n" << _cutflows << endl;
            cout << "\nSRCOUNTS:\n";
            // for (double x : _srnums) cout << x << "  ";
            for (auto& pair : _counters) cout << pair.second.weight_sum() << "  ";
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
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_0LEP_139invfb)


  }
}
