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
// First minimal ColliderBit implementation:
//   - high-mass search only
//   - public jet selection and event categorisation
//   - approximate subjet proxy based on associated AK4 jets
//   - no data-driven background fit machinery
// TODO: add the low-mass resolved search in a later patch.

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
}

namespace Gambit
{
  namespace ColliderBit
  {
    class Analysis_CMS_B2G_18_003 : public Analysis
    {
    private:
      static constexpr const char *CUTFLOW_NAME = "CMS-B2G-18-003-highmass";
      static constexpr double mt = 172.76;

    public:
      static constexpr const char *detector = "CMS";

      Analysis_CMS_B2G_18_003()
      {
        DEFINE_SIGNAL_REGION("SRQH");
        DEFINE_SIGNAL_REGION("SRTH");
        DEFINE_SIGNAL_REGION("SRRH");
        DEFINE_SIGNAL_REGION("SRSH");
        DEFINE_SIGNAL_REGION("SRQZ");
        DEFINE_SIGNAL_REGION("SRLZ");
        DEFINE_SIGNAL_REGION("SRRZ");
        DEFINE_SIGNAL_REGION("SRSZ");

        set_analysis_name("CMS_B2G_18_003");
        set_luminosity(35.9);

#ifdef CHECK_CUTFLOW
        _cutflows.addCutflow(CUTFLOW_NAME,
                             {"All events",
                              "AK4 multiplicity",
                              "AK8 multiplicity",
                              "Leading AK8 jet",
                              "Scalar pT sum",
                              "Extra AK4 jets",
                              "High-mass category assignment",
                              "Final region"});
#endif
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
        BASELINE_BJETS(event->jets("antikt_R04"), csvv2_loose, 30., 0., DBL_MAX, 5.0, CMS::eff2DBJet.at("CSVv2Loose"), CMS::misIDBJet.at("CSVv2Loose"))
        BASELINE_BJETS(event->jets("antikt_R04"), csvv2_medium, 30., 0., DBL_MAX, 5.0, CMS::eff2DBJet.at("CSVv2Medium"), CMS::misIDBJet.at("CSVv2Medium"))

        sort(ak4jets.begin(), ak4jets.end(), [](const HEPUtils::Jet *a, const HEPUtils::Jet *b) { return a->pT() > b->pT(); });
        sort(ak8jets.begin(), ak8jets.end(), [](const HEPUtils::Jet *a, const HEPUtils::Jet *b) { return a->pT() > b->pT(); });

        // ------------------------------------------------------------------
        // 2. Apply baseline event preselection
        // ------------------------------------------------------------------
        const bool pass_ak4_multiplicity = (ak4jets.size() >= 4);
        if (!pass_ak4_multiplicity) return;
#ifdef CHECK_CUTFLOW
        _cutflows[CUTFLOW_NAME].fillnext(event->weight());
#endif

        const bool pass_ak8_multiplicity = (ak8jets.size() >= 2);
        if (!pass_ak8_multiplicity) return;
#ifdef CHECK_CUTFLOW
        _cutflows[CUTFLOW_NAME].fillnext(event->weight());
#endif

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
        _cutflows[CUTFLOW_NAME].fillnext(event->weight());
#endif

        const bool pass_scalar_pt_sum = (ak8jets[0]->pT() + ak8jets[1]->pT() > 850.);
        if (!pass_scalar_pt_sum) return;
#ifdef CHECK_CUTFLOW
        _cutflows[CUTFLOW_NAME].fillnext(event->weight());
#endif

        // ------------------------------------------------------------------
        // 3. Identify candidate-associated AK4 jets
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
        _cutflows[CUTFLOW_NAME].fillnext(event->weight());
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

        auto match_subjet_to_ak4 = [](const FJNS::PseudoJet &subjet,
                                      const vector<const HEPUtils::Jet *> &candidates,
                                      const HEPUtils::Jet *exclude) -> const HEPUtils::Jet *
        {
          const HEPUtils::Jet *best = nullptr;
          double best_dr = DBL_MAX;
          for (const HEPUtils::Jet *jet : candidates)
          {
            if (jet == exclude)
            {
              continue;
            }
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
        // 4. Tagging proxies and candidate reconstruction
        // ------------------------------------------------------------------
        // TODO: CMS resolved-top and resolved-boson reconstruction are not
        // public enough in the current event record to implement faithfully.
        // This first patch keeps only the public merged-path structure.
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
          if (j == a0 || j == a1)
          {
            continue;
          }
          const double dR = j->mom().deltaR_eta(ak8jets[0]->mom());
          if (dR > 0.55 && dR < 0.9) jet0_iso = false;
        }
        for (const HEPUtils::Jet *j : ak4jets)
        {
          if (j == b0 || j == b1)
          {
            continue;
          }
          const double dR = j->mom().deltaR_eta(ak8jets[1]->mom());
          if (dR > 0.55 && dR < 0.9) jet1_iso = false;
        }

        // tau21/tau32 now use fjcontrib Nsubjettiness. The axes/measure choice
        // is a conservative standard default and should be validated against the
        // CMS object-level definition if more detail becomes available.
        const fastjet::contrib::OnePass_WTA_KT_Axes nsub_axes;
        const fastjet::contrib::UnnormalizedMeasure nsub_measure(1.0);
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
        const bool jet0_t       = pass_tau32_0 && jet0_has_proxy_subjet && ak8jets[0]->pT() > 400. && msoftdrop0 > 105. && msoftdrop0 < 220. && jet0_proxy_top_b;
        // Reversed-top proxy: the unavailable highest-CSVv2 soft-drop subjet would
        // fail medium. Require at least one matched proxy subjet and no matched
        // proxy subjet to be medium-tagged.
        const bool jet0_rev_t   = pass_tau32_0 && jet0_has_proxy_subjet && ak8jets[0]->pT() > 400. && msoftdrop0 > 105. && msoftdrop0 < 220. && !jet0_proxy_top_b;
        const bool jet1_t       = pass_tau32_1 && jet1_has_proxy_subjet && ak8jets[1]->pT() > 400. && msoftdrop1 > 105. && msoftdrop1 < 220. && jet1_proxy_top_b;
        const bool jet1_rev_t   = pass_tau32_1 && jet1_has_proxy_subjet && ak8jets[1]->pT() > 400. && msoftdrop1 > 105. && msoftdrop1 < 220. && !jet1_proxy_top_b;

        const bool jet0_h       = pass_tau21_0 && jet0_has_two && ak8jets[0]->pT() > 300. && mpruned0 > 105. && mpruned0 < 135. && ((jet0_med1 && jet0_subjet2_loose) || (jet0_med2 && jet0_subjet1_loose));
        const bool jet0_rev_h   = pass_tau21_0 && jet0_has_two && ak8jets[0]->pT() > 300. && mpruned0 > 105. && mpruned0 < 135. && ((jet0_med1 && !jet0_subjet2_loose) || (jet0_med2 && !jet0_subjet1_loose));
        const bool jet0_z       = pass_tau21_0 && jet0_has_two && ak8jets[0]->pT() > 200. && mpruned0 > 65. && mpruned0 < 105. && ((jet0_med1 && jet0_subjet2_loose) || (jet0_med2 && jet0_subjet1_loose));
        const bool jet0_rev_z   = pass_tau21_0 && jet0_has_two && ak8jets[0]->pT() > 200. && mpruned0 > 65. && mpruned0 < 105. && (!jet0_subjet1_loose && !jet0_subjet2_loose);

        const bool jet1_h       = pass_tau21_1 && jet1_has_two && ak8jets[1]->pT() > 300. && mpruned1 > 105. && mpruned1 < 135. && ((jet1_med1 && jet1_subjet2_loose) || (jet1_med2 && jet1_subjet1_loose));
        const bool jet1_rev_h   = pass_tau21_1 && jet1_has_two && ak8jets[1]->pT() > 300. && mpruned1 > 105. && mpruned1 < 135. && ((jet1_med1 && !jet1_subjet2_loose) || (jet1_med2 && !jet1_subjet1_loose));
        const bool jet1_z       = pass_tau21_1 && jet1_has_two && ak8jets[1]->pT() > 200. && mpruned1 > 65. && mpruned1 < 105. && ((jet1_med1 && jet1_subjet2_loose) || (jet1_med2 && jet1_subjet1_loose));
        const bool jet1_rev_z   = pass_tau21_1 && jet1_has_two && ak8jets[1]->pT() > 200. && mpruned1 > 65. && mpruned1 < 105. && (!jet1_subjet1_loose && !jet1_subjet2_loose);

        const HEPUtils::Jet *top = nullptr;
        const HEPUtils::Jet *boson = nullptr;
        bool is_h_channel = false;

        // ------------------------------------------------------------------
        // 5. Event categorisation
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

        if (pass_SRSH)
        {
          if (srsh_01)
          {
            top = ak8jets[0];
            boson = ak8jets[1];
          }
          else
          {
            top = ak8jets[1];
            boson = ak8jets[0];
          }
          is_h_channel = true;
          FILL_SIGNAL_REGION("SRSH");
        }
        else if (pass_SRTH)
        {
          if (srth_01)
          {
            top = ak8jets[0];
            boson = ak8jets[1];
          }
          else
          {
            top = ak8jets[1];
            boson = ak8jets[0];
          }
          is_h_channel = true;
          FILL_SIGNAL_REGION("SRTH");
        }
        else if (pass_SRRH)
        {
          if (srrh_01)
          {
            top = ak8jets[0];
            boson = ak8jets[1];
          }
          else
          {
            top = ak8jets[1];
            boson = ak8jets[0];
          }
          is_h_channel = true;
          FILL_SIGNAL_REGION("SRRH");
        }
        else if (pass_SRQH)
        {
          if (srqh_01)
          {
            top = ak8jets[0];
            boson = ak8jets[1];
          }
          else
          {
            top = ak8jets[1];
            boson = ak8jets[0];
          }
          is_h_channel = true;
          FILL_SIGNAL_REGION("SRQH");
        }
        else if (pass_SRSZ)
        {
          if (srsz_01)
          {
            top = ak8jets[0];
            boson = ak8jets[1];
          }
          else
          {
            top = ak8jets[1];
            boson = ak8jets[0];
          }
          is_h_channel = false;
          FILL_SIGNAL_REGION("SRSZ");
        }
        else if (pass_SRLZ)
        {
          if (srlz_01)
          {
            top = ak8jets[0];
            boson = ak8jets[1];
          }
          else
          {
            top = ak8jets[1];
            boson = ak8jets[0];
          }
          is_h_channel = false;
          FILL_SIGNAL_REGION("SRLZ");
        }
        else if (pass_SRRZ)
        {
          if (srrz_01)
          {
            top = ak8jets[0];
            boson = ak8jets[1];
          }
          else
          {
            top = ak8jets[1];
            boson = ak8jets[0];
          }
          is_h_channel = false;
          FILL_SIGNAL_REGION("SRRZ");
        }
        else if (pass_SRQZ)
        {
          if (srqz_01)
          {
            top = ak8jets[0];
            boson = ak8jets[1];
          }
          else
          {
            top = ak8jets[1];
            boson = ak8jets[0];
          }
          is_h_channel = false;
          FILL_SIGNAL_REGION("SRQZ");
        }
        else
        {
          return;
        }

        // ------------------------------------------------------------------
        // 6. Reconstruct the heavy T candidate mass observable
        // ------------------------------------------------------------------
        const double mX = is_h_channel ? 125.0 : 91.1876;
        const double mTcorr = (top && boson) ? ((top->mom() + boson->mom()).m() - (top->mom().m() - mt) - (boson->mom().m() - mX)) : 0.;
        (void)mTcorr;
      }

      void collect_results()
      {
        COMMIT_SIGNAL_REGION("SRQH", 640., 640., 28.);
        COMMIT_SIGNAL_REGION("SRTH", 345., 342., 23.);
        COMMIT_SIGNAL_REGION("SRRH", 151., 149., 12.);
        COMMIT_SIGNAL_REGION("SRSH", 52., 53.1, 7.7);
        COMMIT_SIGNAL_REGION("SRQZ", 6253., 6230., 120.);
        COMMIT_SIGNAL_REGION("SRLZ", 1475., 1480., 180.);
        COMMIT_SIGNAL_REGION("SRRZ", 286., 288., 17.);
        COMMIT_SIGNAL_REGION("SRSZ", 80., 77.5, 9.7);

        COMMIT_CUTFLOWS;
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

    DEFINE_ANALYSIS_FACTORY(CMS_B2G_18_003)
  } // namespace ColliderBit
} // namespace Gambit
