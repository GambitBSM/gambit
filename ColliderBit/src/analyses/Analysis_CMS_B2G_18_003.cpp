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
//   - high-mass search
//   - low-mass 3M signal regions only
//   - public jet selection and event categorisation
//   - approximate subjet proxy based on associated AK4 jets
//   - no data-driven background fit machinery
// TODO: add the remaining low-mass control regions and background model in a later patch.

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
      static constexpr double mt = 172.76;
      static constexpr double mH_MC = 121.9;
      static constexpr double mZ_MC = 90.9;
      static constexpr double mW_MC = 83.8;
      static constexpr double mt_MC = 173.8;
      static constexpr double sH_MC = 13.5;
      static constexpr double sZ_MC = 11.4;
      static constexpr double sW_MC = 10.0;
      static constexpr double st_MC = 16.0;

    public:
      static constexpr const char *detector = "CMS";

      Analysis_CMS_B2G_18_003()
      {
        DEFINE_SIGNAL_REGION("SRLM-TH_3M");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M");
        // Per-bin 3M SRs: 40 GeV bins 300--1300 GeV (last bin includes overflow)
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_300");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_300");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_340");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_340");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_380");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_380");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_420");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_420");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_460");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_460");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_500");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_500");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_540");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_540");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_580");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_580");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_620");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_620");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_660");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_660");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_700");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_700");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_740");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_740");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_780");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_780");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_820");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_820");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_860");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_860");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_900");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_900");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_940");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_940");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_980");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_980");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_1020");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_1020");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_1060");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_1060");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_1100");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_1100");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_1140");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_1140");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_1180");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_1180");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_1220");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_1220");
        DEFINE_SIGNAL_REGION("SRLM-TZ_3M_1260");
        DEFINE_SIGNAL_REGION("SRLM-TH_3M_1260");
        DEFINE_SIGNAL_REGION("SRHM-QH");
        DEFINE_SIGNAL_REGION("SRHM-TH");
        DEFINE_SIGNAL_REGION("SRHM-RH");
        DEFINE_SIGNAL_REGION("SRHM-SH");
        DEFINE_SIGNAL_REGION("SRHM-QZ");
        DEFINE_SIGNAL_REGION("SRHM-LZ");
        DEFINE_SIGNAL_REGION("SRHM-RZ");
        DEFINE_SIGNAL_REGION("SRHM-SZ");

        set_analysis_name("CMS_B2G_18_003");
        set_luminosity(35.9);

#ifdef CHECK_CUTFLOW
        _cutflows.addCutflow(CFLMTH, {"All events", "LM preselection", "3M category", "Basic selection (m_bb > 100 GeV)", "Relative HT > 0.4", "Max(chi2) < 3.0",
                                      "DeltaR(bb) < 1.1", "chi2_H < 1.5", "DeltaR(jj) < 1.75", "DeltaR(b,W) < 1.2", "Full selection"});
        _cutflows.addCutflow(CFLMTZ, {"All events", "LM preselection", "3M category", "Basic selection (m_bb < 100 GeV)", "Relative HT > 0.4", "Max(chi2) < 3.0",
                                      "DeltaR(bb) < 1.1", "chi2_Z < 1.0", "DeltaR(jj) < 1.75", "DeltaR(b,W) < 1.2", "Full selection"});
#endif
      }

      void run(const HEPUtils::Event *event)
      {
#ifdef CHECK_CUTFLOW
        BEGIN_PRESELECTION
        _cutflows[CFLMTH].fillinit();
        _cutflows[CFLMTZ].fillinit();
#endif

        // ------------------------------------------------------------------
        // 1. Build baseline jet collections
        // ------------------------------------------------------------------
        BASELINE_JETS(event->jets("antikt_R04"), ak4jets, 30., 0., DBL_MAX, 5.0)
        BASELINE_JETS(event->jets("antikt_R08"), ak8jets, 200., 0., DBL_MAX, 2.4)
        BASELINE_BJETS(event->jets("antikt_R04"), csvv2_loose, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("CSVv2Loose"), CMS::misIDBJet.at("CSVv2Loose"))
        BASELINE_BJETS(event->jets("antikt_R04"), csvv2_medium, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("CSVv2Medium"), CMS::misIDBJet.at("CSVv2Medium"))
        BASELINE_BJETS(event->jets("antikt_R04"), deepcsv_medium, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("DeepCSVMedium"), CMS::misIDBJet.at("DeepCSVMedium"))

        sort(ak4jets.begin(), ak4jets.end(), [](const HEPUtils::Jet *a, const HEPUtils::Jet *b) { return a->pT() > b->pT(); });
        sort(ak8jets.begin(), ak8jets.end(), [](const HEPUtils::Jet *a, const HEPUtils::Jet *b) { return a->pT() > b->pT(); });

        SIGNAL_JETS(ak4jets, signalAK4Jets, 1, 40., 0., DBL_MAX, 4.5)
        SIGNAL_JETS(deepcsv_medium, signalBjets, 1, 40., 0., DBL_MAX, 4.5)

        std::vector<const HEPUtils::Jet *> signalnonBJets;
        signalnonBJets.reserve(signalAK4Jets.size());
        for (const HEPUtils::Jet *j : signalAK4Jets)
        {
          if (find(signalBjets.begin(), signalBjets.end(), j) == signalBjets.end()) { signalnonBJets.push_back(j); }
        }

        const bool lm_jet_multiplicity = (signalnonBJets.size() + signalBjets.size() >= 6);

        SIGNAL_JET_COMBINATION(signalJet, signalnonBJets, signalBjets)

        const bool lm_leading_jets = (signalJet.size() >= 3 && signalJet[0]->pT() > 170. && signalJet[1]->pT() > 130. && signalJet[2]->pT() > 80.);

        const bool pass_lm_preselection = lm_jet_multiplicity && lm_leading_jets;

        // ------------------------------------------------------------------
        // 2. Apply low-mass and high-mass preselection gates
        // ------------------------------------------------------------------
        // Low-mass path: enter the resolved-event selection only if the Sec. 5.1
        if (pass_lm_preselection)
        {
#ifdef CHECK_CUTFLOW
          _cutflows[CFLMTH].fillnext(event->weight());
          _cutflows[CFLMTZ].fillnext(event->weight());
#endif

          if (signalnonBJets.size() >= 2 && signalBjets.size() >= 3)
          {
#ifdef CHECK_CUTFLOW
            _cutflows[CFLMTH].fillnext(event->weight());
            _cutflows[CFLMTZ].fillnext(event->weight());
#endif

            double chi2tH = DBL_MAX;
            double chi2tZ = DBL_MAX;
            double chi2HB = DBL_MAX;
            double chi2ZB = DBL_MAX;
            double chi2HWB = DBL_MAX;
            double chi2ZWB = DBL_MAX;
            double chi2HTB = DBL_MAX;
            double chi2ZTB = DBL_MAX;
            int Hj1 = -1;   // H boson bjet 1
            int Hj2 = -1;   // H boson bjet 2
            int Zj1 = -1;   // Z boson bjet 1
            int Zj2 = -1;   // Z boson bjet 2
            int Htopb = -1; // top bjet
            int Htopj1 = -1;
            int Htopj2 = -1;
            int Ztopb = -1; // top bjet
            int Ztopj1 = -1;
            int Ztopj2 = -1;
            for (size_t btt = 0; btt < signalBjets.size(); ++btt)
            {
              for (size_t bii = 0; bii < signalBjets.size(); ++bii)
              {
                for (size_t bjj = bii + 1; bjj < signalBjets.size(); ++bjj)
                {
                  if (btt == bii || btt == bjj) continue;
                  for (size_t j1 = 0; j1 < signalnonBJets.size(); ++j1)
                  {
                    for (size_t j2 = j1 + 1; j2 < signalnonBJets.size(); ++j2)
                    {
                      double mbb = (signalBjets[bii]->mom() + signalBjets[bjj]->mom()).m();
                      double mjj = (signalnonBJets[j1]->mom() + signalnonBJets[j2]->mom()).m();
                      double mbjj = (signalnonBJets[j1]->mom() + signalnonBJets[j2]->mom() + signalBjets[btt]->mom()).m();

                      double chi2t = std::pow((mbjj - mt_MC) / st_MC, 2);
                      double chi2w = std::pow((mjj - mW_MC) / sW_MC, 2);
                      double chi2H = std::pow((mbb - mH_MC) / sH_MC, 2);
                      double chi2Z = std::pow((mbb - mZ_MC) / sZ_MC, 2);

                      if (chi2t + chi2w + chi2H < chi2tH)
                      {
                        chi2tH = chi2t + chi2w + chi2H;
                        chi2HB = chi2H;
                        chi2HTB = chi2t;
                        chi2HWB = chi2w;
                        Hj1 = bii;
                        Hj2 = bjj;
                        Htopb = btt;
                        Htopj1 = j1;
                        Htopj2 = j2;
                      }
                      if (chi2t + chi2w + chi2Z < chi2tZ)
                      {
                        chi2tZ = chi2t + chi2w + chi2Z;
                        chi2ZB = chi2Z;
                        chi2ZTB = chi2t;
                        chi2ZWB = chi2w;
                        Zj1 = bii;
                        Zj2 = bjj;
                        Ztopb = btt;
                        Ztopj1 = j1;
                        Ztopj2 = j2;
                      }
                    }
                  }
                }
              }
            }

            double HT = 0.;
            for (const HEPUtils::Jet *j : signalJet) HT += j->pT();

            const bool tHchannel = Hj1 >= 0 && Hj2 >= 0 && Htopb >= 0 && Htopj1 >= 0 && Htopj2 >= 0;
            const bool tZchannel = Zj1 >= 0 && Zj2 >= 0 && Ztopb >= 0 && Ztopj1 >= 0 && Ztopj2 >= 0;

            if (tHchannel)
            { // -------------------- tH branch --------------------
              int Hexbidx = -1;
              int Hexnonbidx = -1;
              for (int ii = 0; ii < static_cast<int>(signalBjets.size()); ++ii)
              {
                if (ii != Htopb && ii != Hj1 && ii != Hj2)
                {
                  Hexbidx = ii;
                  break;
                }
              }
              for (int ii = 0; ii < static_cast<int>(signalnonBJets.size()); ++ii)
              {
                if (ii != Htopj1 && ii != Htopj2)
                {
                  Hexnonbidx = ii;
                  break;
                }
              }
              HEPUtils::P4 restjet = HEPUtils::P4();
              if (Hexbidx != -1 && Hexnonbidx == -1) { restjet = signalBjets[Hexbidx]->mom(); }
              if (Hexbidx == -1 && Hexnonbidx != -1) { restjet = signalnonBJets[Hexnonbidx]->mom(); }
              if (Hexbidx != -1 && Hexnonbidx != -1)
              {
                restjet = (signalnonBJets[Hexnonbidx]->mom().pT() > signalBjets[Hexbidx]->mom().pT()) ? signalnonBJets[Hexnonbidx]->mom() : signalBjets[Hexbidx]->mom();
              }
              const double pTtH = (signalBjets[Htopb]->mom() + signalnonBJets[Htopj1]->mom() + signalnonBJets[Htopj2]->mom()).pT();
              const double mbbH = (signalBjets[Hj1]->mom() + signalBjets[Hj2]->mom()).m();
              const double pTH = (signalBjets[Hj1]->mom() + signalBjets[Hj2]->mom()).pT();
              const double dRbbH = signalBjets[Hj1]->mom().deltaR_eta(signalBjets[Hj2]->mom());
              const double dRjjH = signalnonBJets[Htopj1]->mom().deltaR_eta(signalnonBJets[Htopj1]->mom());
              const double dRbWH = signalBjets[Htopj1]->mom().deltaR_eta(signalnonBJets[Htopj1]->mom() + signalnonBJets[Htopj1]->mom());
              const double mt2ndH = (signalBjets[Hj1]->mom() + signalBjets[Hj2]->mom() + restjet).m();
              const bool pass_mbbH = (mbbH > 100.0);
              const bool pass_dRbbH = (dRbbH < 1.1);
              const bool pass_dRjjH = (dRjjH < 1.75);
              const bool pass_dRbWH = (dRbWH < 1.2);
              const bool pass_2ndtopH = (mt2ndH > 250.0);
              const bool pass_chi2H = (chi2HB < 1.5);
              const double chi2MaxH = std::max({chi2HB, chi2HTB, chi2HWB});
              const bool pass_chi2maxH = (chi2MaxH < 3.0);
              const double relativeHTH = (pTH + pTtH) / HT;
              const bool pass_relativeHTH = (relativeHTH > 0.40);
              const bool passtH = pass_mbbH && pass_relativeHTH && pass_chi2maxH && pass_dRbbH && pass_chi2H && pass_dRjjH && pass_dRbWH && (chi2tH < 15.) && pass_2ndtopH;
              if (passtH) FILL_SIGNAL_REGION("SRLM-TH_3M");
#ifdef CHECK_CUTFLOW
              _cutflows[CFLMTH].fillnext(std::vector<bool>{pass_mbbH, pass_relativeHTH, pass_chi2maxH, pass_dRbbH, pass_chi2H, pass_dRjjH, pass_dRbWH, passtH}, event->weight());
#endif
            }
            if (tZchannel)
            {
              // -------------------- tZ branch --------------------
              int Zexbidx = -1;
              int Zexnonbidx = -1;
              for (int ii = 0; ii < static_cast<int>(signalBjets.size()); ++ii)
              {
                if (ii != Htopb && ii != Hj1 && ii != Hj2)
                {
                  Zexbidx = ii;
                  break;
                }
              }
              for (int ii = 0; ii < static_cast<int>(signalnonBJets.size()); ++ii)
              {
                if (ii != Htopj1 && ii != Htopj2)
                {
                  Zexnonbidx = ii;
                  break;
                }
              }
              HEPUtils::P4 restjet = HEPUtils::P4();
              if (Zexbidx != -1 && Zexnonbidx == -1) { restjet = signalBjets[Zexbidx]->mom(); }
              if (Zexbidx == -1 && Zexnonbidx != -1) { restjet = signalnonBJets[Zexnonbidx]->mom(); }
              if (Zexbidx != -1 && Zexnonbidx != -1)
              {
                restjet = (signalnonBJets[Zexnonbidx]->mom().pT() > signalBjets[Zexbidx]->mom().pT()) ? signalnonBJets[Zexnonbidx]->mom() : signalBjets[Zexbidx]->mom();
              }
              const double pTtZ = (signalBjets[Ztopb]->mom() + signalnonBJets[Ztopj1]->mom() + signalnonBJets[Ztopj2]->mom()).pT();
              const double mbbZ = (signalBjets[Zj1]->mom() + signalBjets[Zj2]->mom()).m();
              const double pTZ = (signalBjets[Zj1]->mom() + signalBjets[Zj2]->mom()).pT();
              const double dRbbZ = signalBjets[Zj1]->mom().deltaR_eta(signalBjets[Zj2]->mom());
              const double dRjjZ = signalnonBJets[Ztopj1]->mom().deltaR_eta(signalnonBJets[Ztopj1]->mom());
              const double dRbWZ = signalBjets[Ztopj1]->mom().deltaR_eta(signalnonBJets[Ztopj1]->mom() + signalnonBJets[Ztopj1]->mom());
              const double mt2ndZ = (signalBjets[Zj1]->mom() + signalBjets[Zj2]->mom() + restjet).m();
              const double chi2MaxZ = std::max({chi2ZB, chi2ZTB, chi2ZWB});
              const double relativeHTZ = (pTZ + pTtZ) / HT;

              const bool pass_mbbZ = (mbbZ < 100.0);
              const bool pass_chi2Z = (chi2ZB < 1.0);
              const bool pass_chi2maxZ = (chi2MaxZ < 3.0);
              const bool pass_relativeHTZ = (relativeHTZ > 0.40);
              const bool pass_dRbbZ = (dRbbZ < 1.1);
              const bool pass_dRjjZ = (dRjjZ < 1.75);
              const bool pass_dRbWZ = (dRbWZ < 1.2);
              const bool pass_2ndtopZ = (mt2ndZ > 250.0);
              const bool passtZ = pass_mbbZ && pass_relativeHTZ && pass_chi2maxZ && pass_dRbbZ && pass_chi2Z && pass_dRjjZ && pass_dRbWZ && (chi2tZ < 15.) && pass_2ndtopZ;
              if (passtZ) FILL_SIGNAL_REGION("SRLM-TZ_3M");
#ifdef CHECK_CUTFLOW
              _cutflows[CFLMTZ].fillnext(std::vector<bool>{pass_mbbZ, pass_relativeHTZ, pass_chi2maxZ, pass_dRbbZ, pass_chi2Z, pass_dRjjZ, pass_dRbWZ, passtZ}, event->weight());
#endif
            }
          }
        }
        // High-mass path: enter the merged-event selection only if the
        
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
          _cutflows[CFHM].fillnext(event->weight());
#endif

          const bool pass_scalar_pt_sum = (ak8jets[0]->pT() + ak8jets[1]->pT() > 850.);


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
          _cutflows[CFHM].fillnext(event->weight());
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
          // 4. Tagging proxies and candidate reconstruction
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

          const bool choose_SRSH = pass_SRSH;
          const bool choose_SRTH = !choose_SRSH && pass_SRTH;
          const bool choose_SRRH = !choose_SRSH && !choose_SRTH && pass_SRRH;
          const bool choose_SRQH = !choose_SRSH && !choose_SRTH && !choose_SRRH && pass_SRQH;
          const bool choose_SRSZ = !choose_SRSH && !choose_SRTH && !choose_SRRH && !choose_SRQH && pass_SRSZ;
          const bool choose_SRLZ = !choose_SRSH && !choose_SRTH && !choose_SRRH && !choose_SRQH && !choose_SRSZ && pass_SRLZ;
          const bool choose_SRRZ = !choose_SRSH && !choose_SRTH && !choose_SRRH && !choose_SRQH && !choose_SRSZ && !choose_SRLZ && pass_SRRZ;
          const bool choose_SRQZ = !choose_SRSH && !choose_SRTH && !choose_SRRH && !choose_SRQH && !choose_SRSZ && !choose_SRLZ && !choose_SRRZ && pass_SRQZ;
          if (!(choose_SRSH || choose_SRTH || choose_SRRH || choose_SRQH || choose_SRSZ || choose_SRLZ || choose_SRRZ || choose_SRQZ)) return;

          bool top_is_jet0 = false;
          if (choose_SRSH) top_is_jet0 = srsh_01;
          if (choose_SRTH) top_is_jet0 = srth_01;
          if (choose_SRRH) top_is_jet0 = srrh_01;
          if (choose_SRQH) top_is_jet0 = srqh_01;
          if (choose_SRSZ) top_is_jet0 = srsz_01;
          if (choose_SRLZ) top_is_jet0 = srlz_01;
          if (choose_SRRZ) top_is_jet0 = srrz_01;
          if (choose_SRQZ) top_is_jet0 = srqz_01;
          top = top_is_jet0 ? ak8jets[0] : ak8jets[1];
          boson = top_is_jet0 ? ak8jets[1] : ak8jets[0];
          is_h_channel = choose_SRSH || choose_SRTH || choose_SRRH || choose_SRQH;

          if (choose_SRSH) { FILL_SIGNAL_REGION("SRHM-SH"); }
          else if (choose_SRTH) { FILL_SIGNAL_REGION("SRHM-TH"); }
          else if (choose_SRRH) { FILL_SIGNAL_REGION("SRHM-RH"); }
          else if (choose_SRQH) { FILL_SIGNAL_REGION("SRHM-QH"); }
          else if (choose_SRSZ) { FILL_SIGNAL_REGION("SRHM-SZ"); }
          else if (choose_SRLZ) { FILL_SIGNAL_REGION("SRHM-LZ"); }
          else if (choose_SRRZ) { FILL_SIGNAL_REGION("SRHM-RZ"); }
          else if (choose_SRQZ) { FILL_SIGNAL_REGION("SRHM-QZ"); }

          // ------------------------------------------------------------------
          // 6. Reconstruct the heavy T candidate mass observable
          // ------------------------------------------------------------------
          const double mX = is_h_channel ? 125.0 : 91.1876;
          const double mTcorr = (top && boson) ? ((top->mom() + boson->mom()).m() - (top->mom().m() - mt) - (boson->mom().m() - mX)) : 0.;
          (void)mTcorr;
        }
      }

      void collect_results()
      {
        // Low-mass 3M integrated counts digitised from Fig. 4 (c,d) of
        // arXiv:1909.04721.  The post-fit background and its uncertainty are
        // read off the background-only post-fit distributions (blue histogram
        // + shaded band, 40 GeV bins, 300--1300 GeV integrated).
        // This is a single-bin cut-and-count approximation: mass-shape
        // information is lost, which is conservative for high-mass signals.
        // sigma_bkg ~ 10% of bkg, consistent with the visible post-fit band
        // and the transfer-function systematics quoted in the paper.
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M", 1269., 1295., 130.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M", 1244., 1357., 140.);

        // Per-bin 3M signal regions, digitised from Fig. 4(c,d) of arXiv:1909.04721.
        // T->tZ (left column, 3M row) and T->tH (right column, 3M row).
        // obs/bkg read off the post-fit distributions; err ~ sqrt(bkg).
        //                                  obs    bkg    err
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_300", 20., 18., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_340", 13., 18., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_380", 14., 18., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_420", 23., 20., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_460", 42., 42., 7.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_500", 77., 65., 8.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_540", 87., 80., 9.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_580", 100., 95., 10.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_620", 85., 110., 10.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_660", 115., 113., 11.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_700", 100., 110., 10.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_740", 85., 85., 9.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_780", 80., 82., 9.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_820", 82., 80., 9.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_860", 63., 62., 8.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_900", 40., 44., 7.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_940", 35., 38., 6.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_980", 20., 25., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_1020", 18., 20., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_1060", 18., 18., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_1100", 10., 12., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_1140", 10., 10., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_1180", 10., 10., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_1220", 10., 10., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TZ_3M_1260", 12., 10., 4.);

        COMMIT_SIGNAL_REGION("SRLM-TH_3M_300", 12., 10., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_340", 11., 10., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_380", 11., 12., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_420", 26., 20., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_460", 24., 28., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_500", 44., 45., 7.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_540", 46., 65., 8.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_580", 129., 112., 11.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_620", 121., 125., 11.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_660", 119., 125., 11.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_700", 106., 125., 11.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_740", 104., 117., 11.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_780", 89., 105., 10.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_820", 70., 90., 9.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_860", 40., 75., 9.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_900", 40., 65., 8.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_940", 25., 45., 7.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_980", 20., 38., 6.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_1020", 19., 28., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_1060", 20., 25., 5.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_1100", 10., 18., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_1140", 10., 17., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_1180", 10., 15., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_1220", 20., 14., 4.);
        COMMIT_SIGNAL_REGION("SRLM-TH_3M_1260", 18., 14., 4.);

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
        for (auto &pair : _counters) { pair.second.reset(); }
      }
    };

    DEFINE_ANALYSIS_FACTORY(CMS_B2G_18_003)
  } // namespace ColliderBit
} // namespace Gambit

// TZ.
// Bar0, 17.715617715617725
// Bar1, 18.181818181818198
// Bar2, 25.174825174825184
// Bar3, 30.769230769230777
// Bar4, 38.228438228438236
// Bar5, 58.27505827505828
// Bar6, 78.78787878787878
// Bar7, 96.03729603729603
// Bar8, 97.90209790209789
// Bar9, 110.48951048951048
// Bar10, 102.09790209790211
// Bar11, 82.98368298368298
// Bar12, 79.72027972027973
// Bar13, 67.13286713286715
// Bar14, 49.88344988344989
// Bar15, 35.897435897435905
// Bar16, 30.303030303030305
// Bar17, 20.512820512820507
// Bar18, 17.715617715617725
// Bar19, 15.384615384615389
// Bar20, 13.053613053613052
// Bar21, 11.188811188811187
// Bar22, 7.459207459207458
