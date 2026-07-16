///
///  \author Pengxuan Zhu (zhupx99@icloud.com, pengxuan.zhu@adelaide.edu.au)
///  \date 2026 March
///
///  *********************************************

// Based on
//  - https://cds.cern.ch/record/2688952/files/1909.04721.pdf
//  - https://cms-results.web.cern.ch/cms-results/public-results/publications/B2G-18-003/
//  - https://arxiv.org/abs/1909.04721
//
// Search for electroweak production of a vector-like T quark using fully hadronic final states
//
// Implementation state:
//   - Low-mass (resolved, 0.6-1.2 TeV) search: the five-jet (T-candidate) invariant mass is
//     histogrammed in 40 GeV bins over 300-1300 GeV, and every bin is committed as a signal
//     region via the histogram-backed SR system (DEFINE_HISTOGRAM_SR_1D / COMMIT_HISTOGRAM_SRS).
//     Three mutually exclusive b-tag categories (3T / 3M / 2M1L) x two channels (tH / tZ) are
//     wired. The 3M obs/bkg are digitised from Fig. 4(c,d); the 3T and 2M1L per-bin obs/bkg
//     vectors are still TODO (their histograms commit no SRs until the data are supplied, but
//     the distributions are filled and available for plotting).
//   - High-mass (merged, >1 TeV) search: 8 cut-and-count signal regions (SRHM-{S,T,R,Q}H and
//     SRHM-{S,L,R,Q}Z), using FastJet reclustering, soft-drop/pruned masses, N-subjettiness, and
//     AK4-associated subjet b-tag proxies. This is a public-recast approximation, not a faithful
//     soft-drop-subjet CSVv2 implementation, and is not a T-mass shape fit.
//
// Overflow: the last m5j bin ends at 1.3 TeV; events above are discarded (Histogram1D default).
// This is acceptable here because the low-mass search only targets 0.6-1.2 TeV.

#include <algorithm>
#include <cmath>
#include <cfloat>
#include <memory>
#include <vector>

#include "SoftDrop.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/contrib/Nsubjettiness.hh"

#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"

using namespace std;

namespace
{
  class ConstantPseudoJetDouble : public fastjet::FunctionOfPseudoJet<double>
  {
  public:
    explicit ConstantPseudoJetDouble(double value) : _value(value) {}

    double result(const fastjet::PseudoJet &) const override { return _value; }

    std::string description() const override { return "constant FunctionOfPseudoJet<double>"; }

  private:
    double _value;
  };
} // namespace

namespace Gambit
{
  namespace ColliderBit
  {
    class Analysis_CMS_B2G_18_003 : public Analysis
    {
    private:
      static constexpr const char *CFLMTH = "CMS-B2G-18-003-lowmass-tH";
      static constexpr const char *CFLMTZ = "CMS-B2G-18-003-lowmass-tZ";
      static constexpr const char *CFHM   = "CMS-B2G-18-003-highmass";
      static constexpr double mt = 172.76;
      static constexpr double mH_MC = 121.9;
      static constexpr double mZ_MC = 90.9;
      static constexpr double mW_MC = 83.8;
      static constexpr double mt_MC = 173.8;
      static constexpr double sH_MC = 13.5;
      static constexpr double sZ_MC = 11.4;
      static constexpr double sW_MC = 10.0;
      static constexpr double st_MC = 16.0;

      /// Result of the low-mass five-jet (t + H/Z) reconstruction for one b-tag category.
      struct LowMassReco
      {
        bool passtH = false;
        bool passtZ = false;
        double m5j_tH = 0.0;
        double m5j_tZ = 0.0;
        std::vector<bool> cutbits_tH; ///< per-cut booleans for the tH cutflow
        std::vector<bool> cutbits_tZ; ///< per-cut booleans for the tZ cutflow
      };

    public:
      static constexpr const char *detector = "CMS";

      Analysis_CMS_B2G_18_003()
      {
        book_regions();
        set_analysis_name("CMS_B2G_18_003");
        set_luminosity(35.9);
      }

      void run(const HEPUtils::Event *event)
      {
#ifdef CHECK_CUTFLOW
        BEGIN_PRESELECTION
#endif

        // ------------------------------------------------------------------
        // 1. Build baseline jet collections
        // ------------------------------------------------------------------
        BASELINE_JETS(event->jets("antikt_R04"), ak4jets, 30., 0., DBL_MAX, 5.0)
        BASELINE_JETS(event->jets("antikt_R08"), ak8jets, 200., 0., DBL_MAX, 2.4)
        BASELINE_BJETS(event->jets("antikt_R04"), csvv2_loose, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("CSVv2Loose"), CMS::misIDBJet.at("CSVv2Loose"))
        BASELINE_BJETS(event->jets("antikt_R04"), csvv2_medium, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("CSVv2Medium"), CMS::misIDBJet.at("CSVv2Medium"))
        BASELINE_BJETS(event->jets("antikt_R04"), deepcsv_loose, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("DeepCSVLoose"), CMS::misIDBJet.at("DeepCSVLoose"))
        BASELINE_BJETS(event->jets("antikt_R04"), deepcsv_medium, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("DeepCSVMedium"), CMS::misIDBJet.at("DeepCSVMedium"))
        BASELINE_BJETS(event->jets("antikt_R04"), deepcsv_tight, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("DeepCSVTight"), CMS::misIDBJet.at("DeepCSVTight"))

        sort(ak4jets.begin(), ak4jets.end(), [](const HEPUtils::Jet *a, const HEPUtils::Jet *b) { return a->pT() > b->pT(); });
        sort(ak8jets.begin(), ak8jets.end(), [](const HEPUtils::Jet *a, const HEPUtils::Jet *b) { return a->pT() > b->pT(); });

        // ------------------------------------------------------------------
        // 2. Low-mass (resolved) search
        // ------------------------------------------------------------------
        // Signal jets (pT > 40, |eta| < 4.5) and their DeepCSV b-tagged subsets at each WP.
        SIGNAL_JETS(ak4jets, signalAK4Jets, 1, 40., 0., DBL_MAX, 4.5)
        SIGNAL_JETS(deepcsv_loose, sigBloose, 1, 40., 0., DBL_MAX, 4.5)
        SIGNAL_JETS(deepcsv_medium, sigBmedium, 1, 40., 0., DBL_MAX, 4.5)
        SIGNAL_JETS(deepcsv_tight, sigBtight, 1, 40., 0., DBL_MAX, 4.5)

        // Preselection (b-tag agnostic): >= 6 signal jets, leading-jet pT thresholds.
        const bool lm_jet_multiplicity = (signalAK4Jets.size() >= 6);
        const bool lm_leading_jets = (signalAK4Jets.size() >= 3 &&
                                      signalAK4Jets[0]->pT() > 170. &&
                                      signalAK4Jets[1]->pT() > 130. &&
                                      signalAK4Jets[2]->pT() > 80.);
        const bool pass_lm_preselection = lm_jet_multiplicity && lm_leading_jets;

        if (pass_lm_preselection)
        {
          double HT = 0.;
          for (const HEPUtils::Jet *j : signalAK4Jets) HT += j->pT();

          // Mutually exclusive b-tag categories (paper Sec. 5.1):
          //   3T   : >= 3 tight DeepCSV
          //   3M   : >= 3 medium DeepCSV, excluding 3T
          //   2M1L : 2 medium + >= 1 additional loose, excluding 3M and 3T
          const bool is3T = (sigBtight.size() >= 3);
          const bool is3M = (!is3T && sigBmedium.size() >= 3);
          const bool is2M1L = (!is3T && !is3M && sigBmedium.size() >= 2 && sigBloose.size() >= 3);

          // Build the non-b signal jets relative to a given b-candidate set.
          auto build_nonb = [&](const std::vector<const HEPUtils::Jet *> &bset)
          {
            std::vector<const HEPUtils::Jet *> nonb;
            nonb.reserve(signalAK4Jets.size());
            for (const HEPUtils::Jet *j : signalAK4Jets)
              if (find(bset.begin(), bset.end(), j) == bset.end()) nonb.push_back(j);
            return nonb;
          };

          if (is3M)
          {
            const LowMassReco r = reconstruct_lowmass(sigBmedium, build_nonb(sigBmedium), HT);
            if (r.passtH) FILL_HISTOGRAM_1D("SRLM-TH_3M", r.m5j_tH);
            if (r.passtZ) FILL_HISTOGRAM_1D("SRLM-TZ_3M", r.m5j_tZ);
#ifdef CHECK_CUTFLOW
            _cutflows[CFLMTH].fillnext(event->weight()); // LM preselection
            _cutflows[CFLMTZ].fillnext(event->weight());
            _cutflows[CFLMTH].fillnext(event->weight()); // 3M category
            _cutflows[CFLMTZ].fillnext(event->weight());
            _cutflows[CFLMTH].fillnext(r.cutbits_tH, event->weight());
            _cutflows[CFLMTZ].fillnext(r.cutbits_tZ, event->weight());
#endif
          }
          else if (is3T)
          {
            const std::vector<const HEPUtils::Jet *> bset = sigBtight;
            const LowMassReco r = reconstruct_lowmass(bset, build_nonb(bset), HT);
            if (r.passtH) FILL_HISTOGRAM_1D("SRLM-TH_3T", r.m5j_tH);
            if (r.passtZ) FILL_HISTOGRAM_1D("SRLM-TZ_3T", r.m5j_tZ);
          }
          else if (is2M1L)
          {
            // b-candidate set: the 2 medium jets plus the first loose jet that is not medium.
            std::vector<const HEPUtils::Jet *> bset = sigBmedium;
            for (const HEPUtils::Jet *j : sigBloose)
            {
              if (find(sigBmedium.begin(), sigBmedium.end(), j) == sigBmedium.end()) { bset.push_back(j); break; }
            }
            const LowMassReco r = reconstruct_lowmass(bset, build_nonb(bset), HT);
            if (r.passtH) FILL_HISTOGRAM_1D("SRLM-TH_2M1L", r.m5j_tH);
            if (r.passtZ) FILL_HISTOGRAM_1D("SRLM-TZ_2M1L", r.m5j_tZ);
          }
        }

        // ------------------------------------------------------------------
        // 3. High-mass (merged) search
        // ------------------------------------------------------------------
        const bool nSmallRjet = (ak4jets.size() >= 4 && ak4jets[3]->pT() > 30.);
        const bool nLargeRjet = (ak8jets.size() >= 2 && ak8jets[0]->pT() > 300. && ak8jets[1]->pT() > 200.);
        const bool pass_hm_preselection = nSmallRjet && nLargeRjet;
        if (pass_hm_preselection)
        {
          const double beta = 0.0;
          const double z_cut = 0.1;
          const double RSD = 0.8;
          FJNS::contrib::SoftDrop sd(beta, z_cut, RSD);

          // CMS uses pruned mass for the H/Z mass windows and the leading AK8
          // preselection mass cut. This setup uses Cambridge/Aachen reclustering
          // with the AK8 radius, together with a fixed angular pruning threshold
          // DeltaRcut = 0.5 and zcut = 0.1.
          const fastjet::JetDefinition pruning_jet_def(fastjet::cambridge_algorithm, 0.8);
          const ConstantPseudoJetDouble zcut_prune(0.1);
          const ConstantPseudoJetDouble rcut_prune(0.5);
          fastjet::Pruner pruner(pruning_jet_def, &zcut_prune, &rcut_prune);

          const FJNS::PseudoJet groomed0 = sd(ak8jets[0]->pseudojet());
          const FJNS::PseudoJet groomed1 = sd(ak8jets[1]->pseudojet());
          const double msoftdrop0 = groomed0.m();
          const double msoftdrop1 = groomed1.m();

          const FJNS::PseudoJet pruned0 = pruner(ak8jets[0]->pseudojet());
          const FJNS::PseudoJet pruned1 = pruner(ak8jets[1]->pseudojet());
          const double mpruned0 = pruned0.m();
          const double mpruned1 = pruned1.m();

          const bool pass_leading_ak8 = (ak8jets[0]->pT() > 400. && mpruned0 > 50.);
          if (!pass_leading_ak8) return;
#ifdef CHECK_CUTFLOW
          _cutflows[CFHM].fillnext(event->weight()); // Leading AK8
#endif

          // Scalar pT sum of the two leading AK8 jets > 850 GeV.
          const bool pass_scalar_pt_sum = (ak8jets[0]->pT() + ak8jets[1]->pT() > 850.);
          if (!pass_scalar_pt_sum) return;
#ifdef CHECK_CUTFLOW
          _cutflows[CFHM].fillnext(event->weight()); // Scalar pT sum > 850
#endif

          // ------------------------------------------------------------------
          // 3a. Identify candidate-associated AK4 jets
          // ------------------------------------------------------------------
          int n_extra_ak4 = 0;
          int n_forward_extra_ak4 = 0;
          for (const HEPUtils::Jet *j : ak4jets)
          {
            const double dR0 = j->mom().deltaR_eta(ak8jets[0]->mom());
            const double dR1 = j->mom().deltaR_eta(ak8jets[1]->mom());
            if (dR0 > 1.2 && dR1 > 1.2)
            {
              ++n_extra_ak4;
              if (std::fabs(j->eta()) > 2.4) ++n_forward_extra_ak4;
            }
          }

          if (n_extra_ak4 < 2) return;
          if (n_forward_extra_ak4 < 1) return;
#ifdef CHECK_CUTFLOW
          _cutflows[CFHM].fillnext(event->weight()); // Extra AK4 jets
#endif

          // Build soft-drop subjet proxies by matching tagged AK4 jets to the two
          // groomed subjets of each AK8 jet. This keeps the public proxy strategy,
          // but moves the b-tag bookkeeping to the soft-drop-subjet level.
          vector<const HEPUtils::Jet *> assoc0;
          vector<const HEPUtils::Jet *> assoc1;
          for (const HEPUtils::Jet *j : ak4jets)
          {
            if (j->mom().deltaR_eta(ak8jets[0]->mom()) < 0.8) assoc0.push_back(j);
            if (j->mom().deltaR_eta(ak8jets[1]->mom()) < 0.8) assoc1.push_back(j);
          }
          std::vector<FJNS::PseudoJet> sdsubjets0 = groomed0.exclusive_subjets_up_to(2);
          std::vector<FJNS::PseudoJet> sdsubjets1 = groomed1.exclusive_subjets_up_to(2);
          sort(sdsubjets0.begin(), sdsubjets0.end(), [](const FJNS::PseudoJet &a, const FJNS::PseudoJet &b) { return a.perp() > b.perp(); });
          sort(sdsubjets1.begin(), sdsubjets1.end(), [](const FJNS::PseudoJet &a, const FJNS::PseudoJet &b) { return a.perp() > b.perp(); });

          auto match_subjet_to_ak4 = [](const FJNS::PseudoJet &subjet, const vector<const HEPUtils::Jet *> &candidates, const HEPUtils::Jet *exclude) -> const HEPUtils::Jet *
          {
            const HEPUtils::Jet *best = nullptr;
            double best_dr = DBL_MAX;
            for (const HEPUtils::Jet *jet : candidates)
            {
              if (jet == exclude) { continue; }
              const double dr = subjet.delta_R(jet->pseudojet());
              if (dr < best_dr)
              {
                best_dr = dr;
                best = jet;
              }
            }
            return best;
          };

          const HEPUtils::Jet *a0 = sdsubjets0.size() > 0 ? match_subjet_to_ak4(sdsubjets0[0], assoc0, nullptr) : nullptr;
          const HEPUtils::Jet *a1 = sdsubjets0.size() > 1 ? match_subjet_to_ak4(sdsubjets0[1], assoc0, a0) : nullptr;
          const HEPUtils::Jet *b0 = sdsubjets1.size() > 0 ? match_subjet_to_ak4(sdsubjets1[0], assoc1, nullptr) : nullptr;
          const HEPUtils::Jet *b1 = sdsubjets1.size() > 1 ? match_subjet_to_ak4(sdsubjets1[1], assoc1, b0) : nullptr;

          // ------------------------------------------------------------------
          // 3b. Tagging proxies and candidate reconstruction
          // ------------------------------------------------------------------
          // CMS resolved-top and resolved-boson reconstruction are not public
          // enough in the current event record to implement faithfully.
          // This implementation therefore keeps the public merged-path structure,
          // with CSVv2-based AK8 subjet proxies for the high-mass search and
          // DeepCSV medium AK4 tags reserved for the low-mass resolved path above.
          const bool jet0_loose1 = a0 && find(csvv2_loose.begin(), csvv2_loose.end(), a0) != csvv2_loose.end();
          const bool jet0_loose2 = a1 && find(csvv2_loose.begin(), csvv2_loose.end(), a1) != csvv2_loose.end();
          const bool jet1_loose1 = b0 && find(csvv2_loose.begin(), csvv2_loose.end(), b0) != csvv2_loose.end();
          const bool jet1_loose2 = b1 && find(csvv2_loose.begin(), csvv2_loose.end(), b1) != csvv2_loose.end();

          const bool jet0_med1 = a0 && find(csvv2_medium.begin(), csvv2_medium.end(), a0) != csvv2_medium.end();
          const bool jet0_med2 = a1 && find(csvv2_medium.begin(), csvv2_medium.end(), a1) != csvv2_medium.end();
          const bool jet1_med1 = b0 && find(csvv2_medium.begin(), csvv2_medium.end(), b0) != csvv2_medium.end();
          const bool jet1_med2 = b1 && find(csvv2_medium.begin(), csvv2_medium.end(), b1) != csvv2_medium.end();

          const bool jet0_has_proxy_subjet = (a0 || a1);
          const bool jet1_has_proxy_subjet = (b0 || b1);
          const bool jet0_has_two = (a0 && a1);
          const bool jet1_has_two = (b0 && b1);
          const bool jet0_subjet1_loose = jet0_loose1 || jet0_med1;
          const bool jet0_subjet2_loose = jet0_loose2 || jet0_med2;
          const bool jet1_subjet1_loose = jet1_loose1 || jet1_med1;
          const bool jet1_subjet2_loose = jet1_loose2 || jet1_med2;
          const bool jet0_proxy_top_b = (jet0_med1 || jet0_med2);
          const bool jet1_proxy_top_b = (jet1_med1 || jet1_med2);

          bool jet0_iso = true;
          bool jet1_iso = true;
          for (const HEPUtils::Jet *j : ak4jets)
          {
            if (j == a0 || j == a1) { continue; }
            const double dR = j->mom().deltaR_eta(ak8jets[0]->mom());
            if (dR > 0.55 && dR < 0.9) jet0_iso = false;
          }
          for (const HEPUtils::Jet *j : ak4jets)
          {
            if (j == b0 || j == b1) { continue; }
            const double dR = j->mom().deltaR_eta(ak8jets[1]->mom());
            if (dR > 0.55 && dR < 0.9) jet1_iso = false;
          }

          // CMS Run-2 N-subjettiness uses 1-pass exclusive kT axes with the
          // normalised measure (beta=1), as documented in CMS-PAS-JME-16-003.
          // OnePass_KT_Axes performs one pass of minimisation starting from
          // exclusive kT seeds, matching the CMS object-level definition.
          // The normalisation cancels in the tau_N ratios used here, so
          // NormalizedMeasure and UnnormalizedMeasure give identical tau21/tau32.
          const fastjet::contrib::OnePass_KT_Axes nsub_axes;
          const fastjet::contrib::NormalizedMeasure nsub_measure(1.0, 0.8);
          const fastjet::contrib::Nsubjettiness nsub1(1, nsub_axes, nsub_measure);
          const fastjet::contrib::Nsubjettiness nsub2(2, nsub_axes, nsub_measure);
          const fastjet::contrib::Nsubjettiness nsub3(3, nsub_axes, nsub_measure);

          const double tau1_0 = nsub1(ak8jets[0]->pseudojet());
          const double tau2_0 = nsub2(ak8jets[0]->pseudojet());
          const double tau3_0 = nsub3(ak8jets[0]->pseudojet());
          const double tau1_1 = nsub1(ak8jets[1]->pseudojet());
          const double tau2_1 = nsub2(ak8jets[1]->pseudojet());
          const double tau3_1 = nsub3(ak8jets[1]->pseudojet());

          const double tau21_0 = (tau1_0 > 0.) ? (tau2_0 / tau1_0) : DBL_MAX;
          const double tau32_0 = (tau2_0 > 0.) ? (tau3_0 / tau2_0) : DBL_MAX;
          const double tau21_1 = (tau1_1 > 0.) ? (tau2_1 / tau1_1) : DBL_MAX;
          const double tau32_1 = (tau2_1 > 0.) ? (tau3_1 / tau2_1) : DBL_MAX;

          const bool pass_tau21_0 = (tau21_0 < 0.6);
          const bool pass_tau32_0 = (tau32_0 < 0.57);
          const bool pass_tau21_1 = (tau21_1 < 0.6);
          const bool pass_tau32_1 = (tau32_1 < 0.57);

          // H/Z/top subjet b-tagging uses AK4-associated proxy subjets.
          // This is a public recast approximation, not a faithful soft-drop-subjet
          // CSVv2 implementation.
          // Top-tag proxy: the true highest-CSVv2 soft-drop subjet is unavailable,
          // so we approximate it by requiring at least one matched proxy subjet to
          // be medium-tagged.
          const bool jet0_t = pass_tau32_0 && jet0_has_proxy_subjet && ak8jets[0]->pT() > 400. && msoftdrop0 > 105. && msoftdrop0 < 220. && jet0_proxy_top_b;
          // Reversed-top proxy: the unavailable highest-CSVv2 soft-drop subjet would
          // fail medium. Require at least one matched proxy subjet and no matched
          // proxy subjet to be medium-tagged.
          const bool jet0_rev_t = pass_tau32_0 && jet0_has_proxy_subjet && ak8jets[0]->pT() > 400. && msoftdrop0 > 105. && msoftdrop0 < 220. && !jet0_proxy_top_b;
          const bool jet1_t = pass_tau32_1 && jet1_has_proxy_subjet && ak8jets[1]->pT() > 400. && msoftdrop1 > 105. && msoftdrop1 < 220. && jet1_proxy_top_b;
          const bool jet1_rev_t = pass_tau32_1 && jet1_has_proxy_subjet && ak8jets[1]->pT() > 400. && msoftdrop1 > 105. && msoftdrop1 < 220. && !jet1_proxy_top_b;

          const bool jet0_h = pass_tau21_0 && jet0_has_two && ak8jets[0]->pT() > 300. && mpruned0 > 105. && mpruned0 < 135. &&
                              ((jet0_med1 && jet0_subjet2_loose) || (jet0_med2 && jet0_subjet1_loose));
          const bool jet0_rev_h = pass_tau21_0 && jet0_has_two && ak8jets[0]->pT() > 300. && mpruned0 > 105. && mpruned0 < 135. &&
                                  ((jet0_med1 && !jet0_subjet2_loose) || (jet0_med2 && !jet0_subjet1_loose));
          const bool jet0_z = pass_tau21_0 && jet0_has_two && ak8jets[0]->pT() > 200. && mpruned0 > 65. && mpruned0 < 105. &&
                              ((jet0_med1 && jet0_subjet2_loose) || (jet0_med2 && jet0_subjet1_loose));
          const bool jet0_rev_z = pass_tau21_0 && jet0_has_two && ak8jets[0]->pT() > 200. && mpruned0 > 65. && mpruned0 < 105. && (!jet0_subjet1_loose && !jet0_subjet2_loose);

          const bool jet1_h = pass_tau21_1 && jet1_has_two && ak8jets[1]->pT() > 300. && mpruned1 > 105. && mpruned1 < 135. &&
                              ((jet1_med1 && jet1_subjet2_loose) || (jet1_med2 && jet1_subjet1_loose));
          const bool jet1_rev_h = pass_tau21_1 && jet1_has_two && ak8jets[1]->pT() > 300. && mpruned1 > 105. && mpruned1 < 135. &&
                                  ((jet1_med1 && !jet1_subjet2_loose) || (jet1_med2 && !jet1_subjet1_loose));
          const bool jet1_z = pass_tau21_1 && jet1_has_two && ak8jets[1]->pT() > 200. && mpruned1 > 65. && mpruned1 < 105. &&
                              ((jet1_med1 && jet1_subjet2_loose) || (jet1_med2 && jet1_subjet1_loose));
          const bool jet1_rev_z = pass_tau21_1 && jet1_has_two && ak8jets[1]->pT() > 200. && mpruned1 > 65. && mpruned1 < 105. && (!jet1_subjet1_loose && !jet1_subjet2_loose);

          // ------------------------------------------------------------------
          // 3c. Event categorisation
          // ------------------------------------------------------------------
          // Paper-style ambiguous-case handling: if both leading AK8 jets can be
          // interpreted as the top-like and boson-like candidate in the same
          // region family, assign the higher-pT jet (ak8jets[0]) as the top
          // candidate and the lower-pT jet (ak8jets[1]) as the boson candidate.
          const bool srsh_01 = jet0_t && jet1_h && jet1_iso;
          const bool srsh_10 = jet1_t && jet0_h && jet0_iso;
          const bool srth_01 = jet0_t && jet1_rev_h;
          const bool srth_10 = jet1_t && jet0_rev_h;
          const bool srrh_01 = jet0_rev_t && jet1_h && jet1_iso;
          const bool srrh_10 = jet1_rev_t && jet0_h && jet0_iso;
          const bool srqh_01 = jet0_rev_t && jet1_rev_h;
          const bool srqh_10 = jet1_rev_t && jet0_rev_h;

          const bool srsz_01 = jet0_t && jet1_z && jet1_iso;
          const bool srsz_10 = jet1_t && jet0_z && jet0_iso;
          const bool srlz_01 = jet0_t && jet1_rev_z;
          const bool srlz_10 = jet1_t && jet0_rev_z;
          const bool srrz_01 = jet0_rev_t && jet1_z && jet1_iso;
          const bool srrz_10 = jet1_rev_t && jet0_z && jet0_iso;
          const bool srqz_01 = jet0_rev_t && jet1_rev_z;
          const bool srqz_10 = jet1_rev_t && jet0_rev_z;

          const bool pass_SRSH = srsh_01 || srsh_10;
          const bool pass_SRTH = srth_01 || srth_10;
          const bool pass_SRRH = srrh_01 || srrh_10;
          const bool pass_SRQH = srqh_01 || srqh_10;

          const bool pass_SRSZ = srsz_01 || srsz_10;
          const bool pass_SRLZ = srlz_01 || srlz_10;
          const bool pass_SRRZ = srrz_01 || srrz_10;
          const bool pass_SRQZ = srqz_01 || srqz_10;

          const bool choose_SRSH = pass_SRSH;
          const bool choose_SRTH = !choose_SRSH && pass_SRTH;
          const bool choose_SRRH = !choose_SRSH && !choose_SRTH && pass_SRRH;
          const bool choose_SRQH = !choose_SRSH && !choose_SRTH && !choose_SRRH && pass_SRQH;
          const bool choose_SRSZ = !choose_SRSH && !choose_SRTH && !choose_SRRH && !choose_SRQH && pass_SRSZ;
          const bool choose_SRLZ = !choose_SRSH && !choose_SRTH && !choose_SRRH && !choose_SRQH && !choose_SRSZ && pass_SRLZ;
          const bool choose_SRRZ = !choose_SRSH && !choose_SRTH && !choose_SRRH && !choose_SRQH && !choose_SRSZ && !choose_SRLZ && pass_SRRZ;
          const bool choose_SRQZ = !choose_SRSH && !choose_SRTH && !choose_SRRH && !choose_SRQH && !choose_SRSZ && !choose_SRLZ && !choose_SRRZ && pass_SRQZ;

          if (choose_SRSH) { _counters.at("SRHM-SH").add_event(event); }
          else if (choose_SRTH) { _counters.at("SRHM-TH").add_event(event); }
          else if (choose_SRRH) { _counters.at("SRHM-RH").add_event(event); }
          else if (choose_SRQH) { _counters.at("SRHM-QH").add_event(event); }
          else if (choose_SRSZ) { _counters.at("SRHM-SZ").add_event(event); }
          else if (choose_SRLZ) { _counters.at("SRHM-LZ").add_event(event); }
          else if (choose_SRRZ) { _counters.at("SRHM-RZ").add_event(event); }
          else if (choose_SRQZ) { _counters.at("SRHM-QZ").add_event(event); }
        }
      }

      void collect_results()
      {
        // Low-mass: each five-jet-mass bin is one signal region in the likelihood.
        // 3M is filled with digitised obs/bkg (set in book_regions()); 3T and 2M1L
        // carry no obs/bkg yet, so they commit no SRs until their data are supplied.
        COMMIT_HISTOGRAMS;
        COMMIT_HISTOGRAM_SRS("SRLM-TH_3M");
        COMMIT_HISTOGRAM_SRS("SRLM-TZ_3M");
        COMMIT_HISTOGRAM_SRS("SRLM-TH_3T");
        COMMIT_HISTOGRAM_SRS("SRLM-TZ_3T");
        COMMIT_HISTOGRAM_SRS("SRLM-TH_2M1L");
        COMMIT_HISTOGRAM_SRS("SRLM-TZ_2M1L");

        // High-mass: 8 cut-and-count signal regions. obs/bkg digitised from the paper.
        COMMIT_SIGNAL_REGION("SRHM-QH", 640., 640., 28.);
        COMMIT_SIGNAL_REGION("SRHM-TH", 345., 342., 23.);
        COMMIT_SIGNAL_REGION("SRHM-RH", 151., 149., 12.);
        COMMIT_SIGNAL_REGION("SRHM-SH", 52., 53.1, 7.7);
        COMMIT_SIGNAL_REGION("SRHM-QZ", 6253., 6230., 120.);
        COMMIT_SIGNAL_REGION("SRHM-LZ", 1475., 1480., 180.);
        COMMIT_SIGNAL_REGION("SRHM-RZ", 286., 288., 17.);
        COMMIT_SIGNAL_REGION("SRHM-SZ", 80., 77.5, 9.7);

        COMMIT_CUTFLOWS;
      }

    protected:
      void analysis_specific_reset()
      {
        // reset() wipes _histograms and _cutflows, so re-book everything here too.
        book_regions();
      }

    private:

      /// Define all signal regions, histograms and cutflows.
      /// Called from the constructor and from analysis_specific_reset().
      void book_regions()
      {
        // High-mass cut-and-count signal regions.
        DEFINE_SIGNAL_REGION("SRHM-QH");
        DEFINE_SIGNAL_REGION("SRHM-TH");
        DEFINE_SIGNAL_REGION("SRHM-RH");
        DEFINE_SIGNAL_REGION("SRHM-SH");
        DEFINE_SIGNAL_REGION("SRHM-QZ");
        DEFINE_SIGNAL_REGION("SRHM-LZ");
        DEFINE_SIGNAL_REGION("SRHM-RZ");
        DEFINE_SIGNAL_REGION("SRHM-SZ");

        // Low-mass five-jet-mass histograms: 40 GeV bins, 300-1300 GeV (25 bins).
        // Events above 1.3 TeV fall in the overflow and are dropped (default).
        const std::vector<double> m5j_edges = {
          300., 340., 380., 420., 460., 500., 540., 580., 620., 660., 700.,
          740., 780., 820., 860., 900., 940., 980., 1020., 1060., 1100.,
          1140., 1180., 1220., 1260., 1300.};

        // 3M obs/bkg/bkg_err digitised from Fig. 4(c,d) of arXiv:1909.04721.
        // obs read off the post-fit data points; err ~ sqrt(bkg).
        const std::vector<double> tz3M_obs = {
          17, 14, 22, 23, 42, 76, 87, 86, 99, 110, 115, 81, 82, 61, 46,
          39, 39, 35, 29, 19, 19, 10, 10, 10, 2};
        const std::vector<double> tz3M_bkg = {
          17.4, 18.1, 25.0, 31.0, 37.7, 57.9, 78.7, 95.4, 97.7, 110.6, 102.0, 82.7, 79.6,
          67.2, 50.1, 43.1, 35.3, 30.5, 26.5, 20.3, 17.6, 15.3, 12.9, 11.0, 6.9};
        const std::vector<double> tz3M_err = {
          1.2, 1.4, 2.2, 1.9, 2.6, 3.1, 3.8, 4.2, 3.8, 4.3, 3.4, 3.1, 3.4, 3.4, 2.8,
          2.4, 2.4, 2.4, 2.1, 1.2, 1.9, 1.4, 1.4, 1.4, 1.2};

        const std::vector<double> th3M_obs = {
          13, 11, 12, 21, 28, 23, 44, 71, 113, 128, 120, 127, 117, 106,
          104, 86, 72, 64, 52, 44, 39, 25, 20, 18, 17};
        const std::vector<double> th3M_bkg = {
          7.7, 12.4, 13.9, 17.7, 22.7, 30.1, 46.4, 70.8, 111.2, 123.0, 129.7, 124.9, 113.2,
          109.1, 94.7, 81.3, 73.2, 63.6, 50.7, 43.1, 36.8, 28.7, 27.3, 21.5, 19.6};
        const std::vector<double> th3M_err = {
          0.9, 1.0, 1.4, 1.9, 1.7, 2.4, 2.9, 3.8, 4.6, 4.3, 4.7,
          4.3, 4.5, 4.3, 3.4, 3.9, 3.8, 2.9, 3.1, 2.8, 2.9, 1.9, 2.4, 1.9, 1.9};

        const std::vector<double> tz2M1L_bkg = {
          76.0, 80.0, 110.0, 136.0, 168.0, 258.0, 352.0, 428.0, 435.0, 494.0, 454.0, 370.0, 358.0, 305.0,
          228.0, 198.0, 164.0, 141.0, 122.0, 94.0, 83.0, 71.0, 61.0, 53.0, 34.0};
        const std::vector<double> tz2M1L_err = {
          6.0, 8.0, 10.0, 10.0, 12.0, 14.0, 14.0, 16.0, 19.0, 20.0, 18.0, 16.0,
          16.0, 15.0, 14.0, 12.0, 8.0, 9.0, 10.0, 8.0, 9.0, 7.0, 7.0, 7.0, 4.0};
        const std::vector<double> tz2M1L_obs = {
          76.0, 85.0, 114.0, 144.0, 165.0, 241.0, 343.0, 423.0, 435.0, 494.0, 449.0, 380.0,
          359.0, 317.0, 233.0, 201.0, 157.0, 136.0, 121.0, 94.0, 83.0, 77.0, 60.0, 54.0, 40.0};

        const std::vector<double> th2M1L_bkg = {
          31.0, 48.4, 53.3, 68.8, 88.1, 118.2, 182.1, 275.1, 431.0, 476.5, 503.6, 483.3, 436.8,
          422.3, 371.9, 324.5, 295.4, 257.6, 206.3, 178.2, 154.0, 122.0, 117.2, 93.0, 85.2};
        const std::vector<double> th2M1L_err = {
          3.9, 5.8, 6.7, 7.7, 6.8, 8.7, 10.6, 12.6, 14.5, 15.5, 16.5, 16.5, 16.5, 15.5, 13.6,
          14.5, 11.6, 13.6, 11.6, 11.6, 12.6, 9.7, 9.7, 7.7, 6.8};
        const std::vector<double> th2M1L_obs = {
          25, 50, 55, 65, 81, 129, 182, 277, 424, 454, 510, 485, 440, 423,
          369, 322, 296, 256, 208, 182, 155, 122, 125, 96, 88};

        const std::vector<double> tz3T_obs = {
          16, 17, 23, 27, 33, 50, 70, 130, 83, 100, 60, 37, 57,
          33, 33, 33, 30, 23, 16, 20, 10, 6, 20, 6, 0};
        const std::vector<double> tz3T_bkg = {
          14.9, 15.6, 21.8, 26.6, 32.8, 50.4, 68.5, 83.4, 85.1, 96.8, 84.9,
          66.7, 61.8, 50.6, 36.2, 30.0, 23.6, 19.6, 16.1, 11.9, 9.9, 7.9, 6.5, 5.2, 3.0};
        const std::vector<double> tz3T_err = {
          1.5, 1.8, 1.5, 1.7, 1.4, 2.2, 3.0, 2.5, 2.2, 5.9,
          3.4, 2.3, 3.2, 2.5, 3.0, 2.8, 2.2, 2.2, 2.8, 2.0, 2.0, 2.5, 1.9, 1.7, 1.5};

        const std::vector<double> th3T_obs = {
          2, 3, 4, 5, 7, 4, 13, 14, 29, 43, 31, 22, 19,
          25, 13, 14, 13, 15, 7, 3, 4, 9, 5, 4, 3};
        const std::vector<double> th3T_bkg = {
          2.0, 3.2, 3.3, 4.4, 5.4, 7.2, 11.0, 16.3, 25.3, 27.4, 28.5,
          26.8, 23.9, 22.6, 19.3, 16.3, 14.4, 12.3, 9.6, 7.8, 6.5, 5.0, 4.7, 3.5, 3.2};
        const std::vector<double> th3T_err = {
          0.3, 0.1, 0.3, 0.3, 0.5, 0.6, 0.6, 0.9, 0.9, 1.1, 1.0, 1.1,
          0.6, 1.0, 0.6, 0.9, 0.8, 0.6, 0.5, 0.8, 0.7, 0.6, 0.6, 0.4, 0.4};


        DEFINE_HISTOGRAM_SR_1D("SRLM-TH_3M", m5j_edges, th3M_obs, th3M_bkg, th3M_err, "$m_T}$ [GeV]")
        DEFINE_HISTOGRAM_SR_1D("SRLM-TZ_3M", m5j_edges, tz3M_obs, tz3M_bkg, tz3M_err, "$m_T}$ [GeV]")
        DEFINE_HISTOGRAM_SR_1D("SRLM-TH_3T", m5j_edges, th3T_obs, th3T_bkg, th3T_err, "$m_T$ [GeV]")
        DEFINE_HISTOGRAM_SR_1D("SRLM-TZ_3T", m5j_edges, tz3T_obs, tz3T_bkg, tz3T_err, "$m_T$ [GeV]")
        DEFINE_HISTOGRAM_SR_1D("SRLM-TH_2M1L", m5j_edges, th2M1L_obs, th2M1L_bkg, th2M1L_err, "$m_T$ [GeV]")
        DEFINE_HISTOGRAM_SR_1D("SRLM-TZ_2M1L", m5j_edges, tz2M1L_obs, tz2M1L_bkg, tz2M1L_err, "$m_T$ [GeV]")

#ifdef CHECK_CUTFLOW
        _cutflows.addCutflow(CFLMTH, {"LM preselection", "3M category", "Basic selection (m_bb > 100 GeV)", "Relative HT > 0.4", "Max(chi2) < 3.0",
                                      "DeltaR(bb) < 1.1", "chi2_H < 1.5", "DeltaR(jj) < 1.75", "DeltaR(b,W) < 1.2", "Full selection"});
        _cutflows.addCutflow(CFLMTZ, {"LM preselection", "3M category", "Basic selection (m_bb < 100 GeV)", "Relative HT > 0.4", "Max(chi2) < 3.0",
                                      "DeltaR(bb) < 1.1", "chi2_Z < 1.0", "DeltaR(jj) < 1.75", "DeltaR(b,W) < 1.2", "Full selection"});
        _cutflows.addCutflow(CFHM, {"Leading AK8", "Scalar pT sum > 850", "Extra AK4 jets"});
#endif
      }

      /// Reconstruct the resolved t + H/Z system from a 3-b-jet + non-b-jet set.
      /// Performs one chi2 minimisation that yields both the best tH and best tZ
      /// assignments, then applies the per-channel selection and returns the
      /// five-jet (T-candidate) masses and pass flags.
      LowMassReco reconstruct_lowmass(const std::vector<const HEPUtils::Jet *> &bjets,
                                      const std::vector<const HEPUtils::Jet *> &nonbjets,
                                      double HT) const
      {
        LowMassReco out;
        if (bjets.size() < 3 || nonbjets.size() < 2) return out;

        double chi2tH = DBL_MAX;
        double chi2tZ = DBL_MAX;
        double chi2HB = DBL_MAX, chi2ZB = DBL_MAX;
        double chi2HWB = DBL_MAX, chi2ZWB = DBL_MAX;
        double chi2HTB = DBL_MAX, chi2ZTB = DBL_MAX;
        int Hj1 = -1, Hj2 = -1, Htopb = -1, Htopj1 = -1, Htopj2 = -1;
        int Zj1 = -1, Zj2 = -1, Ztopb = -1, Ztopj1 = -1, Ztopj2 = -1;

        for (size_t btt = 0; btt < bjets.size(); ++btt)
        {
          for (size_t bii = 0; bii < bjets.size(); ++bii)
          {
            for (size_t bjj = bii + 1; bjj < bjets.size(); ++bjj)
            {
              if (btt == bii || btt == bjj) continue;
              for (size_t j1 = 0; j1 < nonbjets.size(); ++j1)
              {
                for (size_t j2 = j1 + 1; j2 < nonbjets.size(); ++j2)
                {
                  const double mbb = (bjets[bii]->mom() + bjets[bjj]->mom()).m();
                  const double mjj = (nonbjets[j1]->mom() + nonbjets[j2]->mom()).m();
                  const double mbjj = (nonbjets[j1]->mom() + nonbjets[j2]->mom() + bjets[btt]->mom()).m();

                  const double chi2t = std::pow((mbjj - mt_MC) / st_MC, 2);
                  const double chi2w = std::pow((mjj - mW_MC) / sW_MC, 2);
                  const double chi2H = std::pow((mbb - mH_MC) / sH_MC, 2);
                  const double chi2Z = std::pow((mbb - mZ_MC) / sZ_MC, 2);

                  if (chi2t + chi2w + chi2H < chi2tH)
                  {
                    chi2tH = chi2t + chi2w + chi2H;
                    chi2HB = chi2H; chi2HTB = chi2t; chi2HWB = chi2w;
                    Hj1 = bii; Hj2 = bjj; Htopb = btt; Htopj1 = j1; Htopj2 = j2;
                  }
                  if (chi2t + chi2w + chi2Z < chi2tZ)
                  {
                    chi2tZ = chi2t + chi2w + chi2Z;
                    chi2ZB = chi2Z; chi2ZTB = chi2t; chi2ZWB = chi2w;
                    Zj1 = bii; Zj2 = bjj; Ztopb = btt; Ztopj1 = j1; Ztopj2 = j2;
                  }
                }
              }
            }
          }
        }

        const bool tHchannel = Hj1 >= 0 && Hj2 >= 0 && Htopb >= 0 && Htopj1 >= 0 && Htopj2 >= 0;
        const bool tZchannel = Zj1 >= 0 && Zj2 >= 0 && Ztopb >= 0 && Ztopj1 >= 0 && Ztopj2 >= 0;

        // Helper to find the leading "rest" jet not used by the t + boson system.
        auto rest_jet_mom = [&](int topb, int hb1, int hb2, int tj1, int tj2) -> HEPUtils::P4
        {
          int exbidx = -1, exnonbidx = -1;
          for (int ii = 0; ii < static_cast<int>(bjets.size()); ++ii)
            if (ii != topb && ii != hb1 && ii != hb2) { exbidx = ii; break; }
          for (int ii = 0; ii < static_cast<int>(nonbjets.size()); ++ii)
            if (ii != tj1 && ii != tj2) { exnonbidx = ii; break; }
          HEPUtils::P4 restjet = HEPUtils::P4();
          if (exbidx != -1 && exnonbidx == -1) restjet = bjets[exbidx]->mom();
          else if (exbidx == -1 && exnonbidx != -1) restjet = nonbjets[exnonbidx]->mom();
          else if (exbidx != -1 && exnonbidx != -1)
            restjet = (nonbjets[exnonbidx]->mom().pT() > bjets[exbidx]->mom().pT()) ? nonbjets[exnonbidx]->mom() : bjets[exbidx]->mom();
          return restjet;
        };

        if (tHchannel)
        {
          const HEPUtils::P4 restjet = rest_jet_mom(Htopb, Hj1, Hj2, Htopj1, Htopj2);
          const double pTtH = (bjets[Htopb]->mom() + nonbjets[Htopj1]->mom() + nonbjets[Htopj2]->mom()).pT();
          const double mbbH = (bjets[Hj1]->mom() + bjets[Hj2]->mom()).m();
          const double pTH = (bjets[Hj1]->mom() + bjets[Hj2]->mom()).pT();
          const double dRbbH = bjets[Hj1]->mom().deltaR_eta(bjets[Hj2]->mom());
          const double dRjjH = nonbjets[Htopj1]->mom().deltaR_eta(nonbjets[Htopj2]->mom());
          const double dRbWH = bjets[Htopb]->mom().deltaR_eta(nonbjets[Htopj1]->mom() + nonbjets[Htopj2]->mom());
          const double mt2ndH = (bjets[Hj1]->mom() + bjets[Hj2]->mom() + restjet).m();
          const double chi2MaxH = std::max({chi2HB, chi2HTB, chi2HWB});
          const double relativeHTH = (pTH + pTtH) / HT;

          const bool pass_mbbH = (mbbH > 100.0);
          const bool pass_relativeHTH = (relativeHTH > 0.40);
          const bool pass_chi2maxH = (chi2MaxH < 3.0);
          const bool pass_dRbbH = (dRbbH < 1.1);
          const bool pass_chi2H = (chi2HB < 1.5);
          const bool pass_dRjjH = (dRjjH < 1.75);
          const bool pass_dRbWH = (dRbWH < 1.2);
          const bool pass_2ndtopH = (mt2ndH > 250.0);
          out.passtH = pass_mbbH && pass_relativeHTH && pass_chi2maxH && pass_dRbbH && pass_chi2H && pass_dRjjH && pass_dRbWH && (chi2tH < 15.) && pass_2ndtopH;
          out.m5j_tH = (bjets[Hj1]->mom() + bjets[Hj2]->mom() + bjets[Htopb]->mom() + nonbjets[Htopj1]->mom() + nonbjets[Htopj2]->mom()).m();
          out.cutbits_tH = {pass_mbbH, pass_relativeHTH, pass_chi2maxH, pass_dRbbH, pass_chi2H, pass_dRjjH, pass_dRbWH, out.passtH};
        }

        if (tZchannel)
        {
          const HEPUtils::P4 restjet = rest_jet_mom(Ztopb, Zj1, Zj2, Ztopj1, Ztopj2);
          const double pTtZ = (bjets[Ztopb]->mom() + nonbjets[Ztopj1]->mom() + nonbjets[Ztopj2]->mom()).pT();
          const double mbbZ = (bjets[Zj1]->mom() + bjets[Zj2]->mom()).m();
          const double pTZ = (bjets[Zj1]->mom() + bjets[Zj2]->mom()).pT();
          const double dRbbZ = bjets[Zj1]->mom().deltaR_eta(bjets[Zj2]->mom());
          const double dRjjZ = nonbjets[Ztopj1]->mom().deltaR_eta(nonbjets[Ztopj2]->mom());
          const double dRbWZ = bjets[Ztopb]->mom().deltaR_eta(nonbjets[Ztopj1]->mom() + nonbjets[Ztopj2]->mom());
          const double mt2ndZ = (bjets[Zj1]->mom() + bjets[Zj2]->mom() + restjet).m();
          const double chi2MaxZ = std::max({chi2ZB, chi2ZTB, chi2ZWB});
          const double relativeHTZ = (pTZ + pTtZ) / HT;

          const bool pass_mbbZ = (mbbZ < 100.0);
          const bool pass_relativeHTZ = (relativeHTZ > 0.40);
          const bool pass_chi2maxZ = (chi2MaxZ < 3.0);
          const bool pass_dRbbZ = (dRbbZ < 1.1);
          const bool pass_chi2Z = (chi2ZB < 1.0);
          const bool pass_dRjjZ = (dRjjZ < 1.75);
          const bool pass_dRbWZ = (dRbWZ < 1.2);
          const bool pass_2ndtopZ = (mt2ndZ > 250.0);
          out.passtZ = pass_mbbZ && pass_relativeHTZ && pass_chi2maxZ && pass_dRbbZ && pass_chi2Z && pass_dRjjZ && pass_dRbWZ && (chi2tZ < 15.) && pass_2ndtopZ;
          out.m5j_tZ = (bjets[Zj1]->mom() + bjets[Zj2]->mom() + bjets[Ztopb]->mom() + nonbjets[Ztopj1]->mom() + nonbjets[Ztopj2]->mom()).m();
          out.cutbits_tZ = {pass_mbbZ, pass_relativeHTZ, pass_chi2maxZ, pass_dRbbZ, pass_chi2Z, pass_dRjjZ, pass_dRbWZ, out.passtZ};
        }

        return out;
      }
    };

    DEFINE_ANALYSIS_FACTORY(CMS_B2G_18_003)
  } // namespace ColliderBit
} // namespace Gambit
