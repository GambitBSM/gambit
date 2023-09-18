///
///  \author Pengxuan Zhu
///         (zhupx99@icloud.com)
///  \date 2023 Sep
///  *********************************************
// Based on the CMS publication https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-20-003/index.html
// JHEP 10 (2021) 045, arXiv:2107.12553 [hep-ex],

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "HEPUtils/FastJet.h"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {
    bool sortByPT13(const HEPUtils::Jet *jet1, const HEPUtils::Jet *jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortByPT13_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2) { return sortByPT13(jet1.get(), jet2.get()); }

    class Analysis_CMS_13TeV_1LEPbb_137invfb : public Analysis
    {

    public:
      // Required detector sim
      static constexpr const char *detector = "CMS";

      Analysis_CMS_13TeV_1LEPbb_137invfb()
      {
        DEFINE_SIGNAL_REGIONS("SR2J-0H-", 4);
        DEFINE_SIGNAL_REGIONS("SR2J-1H-", 2);
        DEFINE_SIGNAL_REGIONS("SR3J-0H-", 4);
        DEFINE_SIGNAL_REGIONS("SR3J-1H-", 2);

        set_analysis_name("CMS_13TeV_1LEPbb_137invfb");
        set_luminosity(137.0);
      }

      void run(const HEPUtils::Event *event)
      {
        ////////////////////////
        // Useful definiitons //
        double mZ = 91.1876;
        double met = event->met();

        // Baseline ELectrons
        BASELINE_PARTICLES(electrons, baselineElectrons, 30, 0, DBL_MAX, 1.44, CMS::eff2DEl.at("SUS_19_008"));

        // Baseline Muons
        BASELINE_PARTICLES(muons, baselineMuons, 25, 0, DBL_MAX, 2.1, CMS::eff2DMu.at("SUS_19_008"));

        // Baseline Jets, tow jets
        // ColliderBit::JetDefinition baselineSmallRjets(ColliderBit::antikt_algorithm, 0.4);
        // FastJet::JetDefinition baselineSmallRjets(FastJet::antikt_algorithm, 0.4);
        // FastJet::JetDefinition baselineLargeRjets(FastJet::antikt_algorithm, 0.8);

        // BASELINE_JETS(baselineSmallRjets, SmallRJets, 30., 0, DBL_MAX, 2.4);
        // BASELINE_JETS(baselineLargeRjets, LargeRJets, 250., 0, DBL_MAX, 2.4);
        // BASELINE_BJETS(baselineSmallRjets, BJets, 25., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("CSVv2Tight"), CMS::missIDBJet.at("CSVv2Tight"))
        vector<const HEPUtils::Jet *> bJets;
        vector<const HEPUtils::Jet *> nonBJets;

        const std::vector<double> a = {0, 10.};
        const std::vector<double> b = {0, 10000.};
        const std::vector<double> c = {0.77}; // set b-tag efficiency to 77%
        HEPUtils::BinnedFn2D<double> _eff2d(a, b, c);
        for (const HEPUtils::Jet *jet : event->jets())
        {
          bool hasTag = has_tag(_eff2d, fabs(jet->eta()), jet->pT());
          if (jet->pT() > 30. && fabs(jet->eta()) < 2.4)
          {
            if (jet->btag() && hasTag)
            {
              bJets.push_back(jet);
            }
            else
            {
              nonBJets.push_back(jet);
            }
          }
        }

        vector<const HEPUtils::Particle *> baselineTaus;
        for (const HEPUtils::Particle *tau : event->taus())
        {
          if (tau->pT() > 10. && tau->abseta() < 2.4)
            baselineTaus.push_back(tau);
        }

        // The track is not included in this version:
        // vector<const HEPUtils::Particle*> pfcandidates;

        ////////////////////
        // Signal objects //

        // Define signal objects from baseline objects, automatically order by pT (highest first)

        // Vote on isolated objects
        double Rrel;
        vector<const HEPUtils::Particle *> Electrons;
        for (const Particle *e : baselineElectrons)
        {
          if (e->pT() < 50.0)
            Rrel = 0.2;
          else if (e->pT() < 200.0)
            Rrel = 10.0 / e->pT();
          else
            Rrel = 0.05;

          double sumpt = 0.0;
          double sumpt_in_03 = 0.0;
          for (const HEPUtils::Jet *j : event->jets())
          {
            if (e->mom().deltaR_eta(j->mom()) < Rrel)
            {
              sumpt += j->pT();
            }
            if (e->mom().deltaR_eta(j->mom()) < 0.3)
            {
              sumpt_in_03 += j->pT();
            }
          }
          if (sumpt / e->pT() < 0.1 && sumpt_in_03 < 5.0)
            Electrons.push_back(e);
        }

        vector<const HEPUtils::Particle *> Muons;
        for (const HEPUtils::Particle *mu : baselineMuons)
        {
          if (mu->pT() < 50.)
            Rrel = 0.2;
          else if (mu->pT() < 200.)
            Rrel = 10. / mu->pT();
          else
            Rrel = 0.05;
          double sumpt = 0.0;
          double sumpt_in_03 = 0.0;
          for (const HEPUtils::Jet *j : event->jets())
          {
            if (mu->mom().deltaR_eta(j->mom()) < Rrel)
            {
              sumpt += j->pT();
            }
            if (mu->mom().deltaR_eta(j->mom()) < 0.3)
            {
              sumpt_in_03 += j->pT();
            }
          }
          if (sumpt / mu->pT() < 0.1 && sumpt_in_03 < 5.0)
            Muons.push_back(mu);
        }
        SIGNAL_PARTICLE_COMBINATION(signalLeptons, Electrons, Muons);

        // veto leptons selections

        BASELINE_PARTICLES(electrons, vetoElectrons, 5.0, 0, DBL_MAX, 2.4, CMS::eff2DEl.at("SUS_19_008"));
        BASELINE_PARTICLES(muons, vetoMuons, 5.0, 0, DBL_MAX, 2.4, CMS::eff2DMu.at("SUS_19_008"));

        vector<const HEPUtils::Particle *> vetoLeptons;
        for (const HEPUtils::Particle *e : vetoElectrons)
        {
          if (e->pT() < 50.0)
            Rrel = 0.2;
          else if (e->pT() < 200.0)
            Rrel = 10.0 / e->pT();
          else
            Rrel = 0.05;

          double sumpt = 0.;
          for (const HEPUtils::Jet *j : event->jets())
          {
            if (e->mom().deltaR_eta(j->mom()) < Rrel)
              sumpt += j->pT();
          }
          if (sumpt / e->pT() < 0.2)
            vetoLeptons.push_back(e);
        }

        for (const HEPUtils::Particle *mu : vetoMuons)
        {
          if (mu->pT() < 50.0)
            Rrel = 0.2;
          else if (mu->pT() < 200.0)
            Rrel = 10.0 / mu->pT();
          else
            Rrel = 0.05;

          double sumpt = 0.;
          for (const HEPUtils::Jet *j : event->jets())
          {
            if (mu->mom().deltaR_eta(j->mom()) < Rrel)
              sumpt += j->pT();
          }
          if (sumpt / mu->pT() < 0.2)
            vetoLeptons.push_back(mu);
        }

        vector<const HEPUtils::Jet *> signalJets;
        vector<const HEPUtils::Jet *> signalBJets;
        vector<const HEPUtils::Jet *> signalNonBJets;

        for (const HEPUtils::Jet *jet : bJets)
        {
          signalBJets.push_back(jet);
          signalJets.push_back(jet);
        }

        for (const HEPUtils::Jet *jet : nonBJets)
        {
          signalNonBJets.push_back(jet);
          signalJets.push_back(jet);
        }

        std::sort(signalJets.begin(), signalJets.end(), sortByPT13);
        std::sort(signalBJets.begin(), signalBJets.end(), sortByPT13);
        std::sort(signalNonBJets.begin(), signalNonBJets.end(), sortByPT13);

        vector<std::shared_ptr<HEPUtils::Jet>>LargeRJets = get_jets(signalJets, 0.8);
        std::sort(LargeRJets.begin(), LargeRJets.end(), sortByPT13_sharedptr);

        vector<std::shared_ptr<HEPUtils::Jet>> signalLargeRJets;
        for (const auto& jet : LargeRJets)
        {
          if (jet->pT() > 250. && jet->abseta() < 2.4)
          {
            signalLargeRJets.push_back(jet);
          }
        }

        // removeOverlap(signalLargeRJets, signalLeptons, 0.8);
        removeOverlap(signalJets, signalLeptons, 0.4);
        removeOverlap(signalBJets, signalLeptons, 0.4);
        removeOverlap(signalNonBJets, signalLeptons, 0.4);

        bool lepton2_veto = true;
        if (vetoLeptons.size() > 1)
          lepton2_veto = false;

        bool tau_veto = true;
        if (baselineTaus.size() > 0)
          tau_veto = false;

        // flag of preselection requirement; Table 3
        bool nlepton_ps = false;
        bool nsRjs_ps = false;
        bool ptmiss_ps = false;
        bool mbb_ps = false;
        bool mt_ps = false;
        bool mct_ps = false;

        double mbb;
        double mCT;
        double mTl;
        int NHjet = 0;
        int Njets = signalJets.size();

        if (signalLeptons.size() == 1 && lepton2_veto && tau_veto)
        {
          nlepton_ps = true;
          mTl = mT(signalLeptons.at(0)->mom(), event->missingmom());
          if (mTl > 150.)
            mt_ps = true;
        }
        if (Njets == 2 && signalBJets.size() == 2)
          nsRjs_ps = true;
        if (Njets == 3 && signalBJets.size() == 2)
        {
          if (signalJets[0]->pT() < 300.)
            nsRjs_ps = true;
        }
        if (met > 125.)
          ptmiss_ps = true;
        if (nsRjs_ps)
        {
          mbb = (signalBJets.at(0)->mom() + signalBJets.at(1)->mom()).m();
          mCT = mT(signalBJets.at(0)->mom(), signalBJets.at(1)->mom());
          if (mbb > 90. && mbb < 150.)
            mbb_ps = true;
          if (mCT > 200.)
            mct_ps = true;
          if (signalLargeRJets.size() == 1)
          {
            if ((signalLargeRJets.at(0)->mom().deltaR_eta(signalBJets.at(0)->mom()) < 0.8) && (signalLargeRJets.at(0)->mom().deltaR_eta(signalBJets.at(1)->mom()) < 0.8))
              NHjet = 1;
          }
        }

        // Counting numbers of SRs
        if (nlepton_ps && nsRjs_ps && ptmiss_ps && mbb_ps && mt_ps && mct_ps)
        {
          if (NHjet == 0 && Njets == 2 && met >= 125. && met < 200.)
          {
            FILL_SIGNAL_REGION("SR2J-0H-1");
          }
          if (NHjet == 0 && Njets == 2 && met >= 200. && met < 300.)
          {
            FILL_SIGNAL_REGION("SR2J-0H-2");
          }
          if (NHjet == 0 && Njets == 2 && met >= 300. && met < 400.)
          {
            FILL_SIGNAL_REGION("SR2J-0H-3");
          }
          if (NHjet == 0 && Njets == 2 && met >= 400.)
          {
            FILL_SIGNAL_REGION("SR2J-0H-4");
          }
          if (NHjet == 1 && Njets == 2 && met >= 125. && met < 300.)
          {
            FILL_SIGNAL_REGION("SR2J-1H-1");
          }
          if (NHjet == 1 && Njets == 2 && met >= 300.)
          {
            FILL_SIGNAL_REGION("SR2J-1H-2");
          }

          if (NHjet == 0 && Njets == 3 && met >= 125. && met < 200.)
          {
            FILL_SIGNAL_REGION("SR3J-0H-1");
          }
          if (NHjet == 0 && Njets == 3 && met >= 200. && met < 300.)
          {
            FILL_SIGNAL_REGION("SR3J-0H-2");
          }
          if (NHjet == 0 && Njets == 3 && met >= 300. && met < 400.)
          {
            FILL_SIGNAL_REGION("SR3J-0H-3");
          }
          if (NHjet == 0 && Njets == 3 && met >= 400.)
          {
            FILL_SIGNAL_REGION("SR3J-0H-4");
          }
          if (NHjet == 1 && Njets == 3 && met >= 125. && met < 300.)
          {
            FILL_SIGNAL_REGION("SR3J-1H-1");
          }
          if (NHjet == 1 && Njets == 3 && met >= 300.)
          {
            FILL_SIGNAL_REGION("SR3J-1H-2");
          }
        }
        // if
      }

      void combine(const Analysis *other)
      {
        const Analysis_CMS_13TeV_1LEPbb_137invfb *specificOther = dynamic_cast<const Analysis_CMS_13TeV_1LEPbb_137invfb *>(other);
        for (auto &pair : _counters)
        {
          pair.second += specificOther->_counters.at(pair.first);
        }
      }

      virtual void collect_results()
      {

        // Commit the results for signal regions, included observed and bacground counts
        // COMMIT_SIGNAL_REGION(SR, OBS, BKG, BKG_ERR)

        COMMIT_SIGNAL_REGION("SR2J-0H-1", 8., 6.9, 1.3);
        COMMIT_SIGNAL_REGION("SR2J-0H-2", 2., 3.4, 0.6);
        COMMIT_SIGNAL_REGION("SR2J-0H-3", 1., 1.0, 0.3);
        COMMIT_SIGNAL_REGION("SR2J-0H-4", 1., 0.3, 0.1);

        COMMIT_SIGNAL_REGION("SR2J-1H-1", 3., 2.5, 0.9);
        COMMIT_SIGNAL_REGION("SR2J-1H-2", 1., 0.9, 0.5);

        COMMIT_SIGNAL_REGION("SR3J-0H-1", 17., 17.8, 3.0);
        COMMIT_SIGNAL_REGION("SR3J-0H-2", 6., 7.8, 1.7);
        COMMIT_SIGNAL_REGION("SR3J-0H-3", 0., 1.5, 0.5);
        COMMIT_SIGNAL_REGION("SR3J-0H-4", 0., 0.5, 0.3);

        COMMIT_SIGNAL_REGION("SR3J-1H-1", 10., 5.9, 2.1);
        COMMIT_SIGNAL_REGION("SR3J-1H-2", 0., 2.1, 0.6);

        // Add cutflow data to the analysis results
        COMMIT_CUTFLOWS;
      }

      double mT(const HEPUtils::P4 &pV, const HEPUtils::P4 &pI)
      {
        double deltaPhi = pV.deltaPhi(pI);
        double mT = sqrt(
            2 * pV.pT() * pI.pT() * (1 - cos(deltaPhi)));

        return mT;
      }

    protected:
      void analysis_specific_reset()
      {
        for (auto &pair : _counters)
        {
          pair.second.reset();
        }

        // std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }
    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_1LEPbb_137invfb)

  }
}
