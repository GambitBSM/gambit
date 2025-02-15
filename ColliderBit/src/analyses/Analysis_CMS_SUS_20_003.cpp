///
///  \author Pengxuan Zhu
///         (zhupx99@icloud.com)
///  \date 2023 Dec
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
#define CHECK_CUTFLOW

namespace Gambit
{
  namespace ColliderBit
  {
    bool sortByPT14(const HEPUtils::Jet *jet1, const HEPUtils::Jet *jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortByPT14_sharedptr(std::shared_ptr<HEPUtils::Jet> jet1, std::shared_ptr<HEPUtils::Jet> jet2) { return sortByPT14(jet1.get(), jet2.get()); }

    class Analysis_CMS_SUS_20_003 : public Analysis
    {
    // protected:

    //     Cutflow _cutflows;

    public:

      #ifdef CHECK_CUTFLOW
        Cutflows _cutflows;
      #endif
      // Required detector sim
      static constexpr const char *detector = "CMS";

      Analysis_CMS_SUS_20_003()
      {
        DEFINE_SIGNAL_REGIONS("SR2J-0H-", 4);
        DEFINE_SIGNAL_REGIONS("SR2J-1H-", 2);
        DEFINE_SIGNAL_REGIONS("SR3J-0H-", 4);
        DEFINE_SIGNAL_REGIONS("SR3J-1H-", 2);

        set_analysis_name("CMS_SUS_20_003");
        set_luminosity(137.0);

        #ifdef CHECK_CUTFLOW
          cout << "Starting the Run Analysis \n booking Cutflows" << endl;
          // Book Cutflows
          const vector<string> cutnames = {
                                  "no cut",
                                  "Pre-selection",
                                  "No-veto-Lepton",
                                  "No-veto-hadronic taus",
                                  "1 Single Lepton",
                                  "mT(l) >= 150 GeV",
                                  "N_bjet = 2",
                                  "N_jet = 2",
                                  "N_jet = 3",
                                  "ETmiss >= 125 GeV",
                                  "90 GeV <= mbb <= 150 GeV",
                                  "mCT >= 200 GeV",
                                  "1 AK8 Jet",
                                  "1 Higgs Jet",
                                  "Selection criteria",
                                  "SR2J-0H",
                                  "SR2J-1H",
                                  "SR3J-0H",
                                  "SR3J-1H"
                                  };

          // _cutflows.addCutflow("SR2J-0H-1", cutnames);
          // _cutflows.addCutflow("SR2J-0H-2", cutnames);
          // _cutflows.addCutflow("SR2J-0H-3", cutnames);
          // _cutflows.addCutflow("SR2J-0H-4", cutnames);

          // _cutflows.addCutflow("SR2J-1H-1", cutnames);
          // _cutflows.addCutflow("SR2J-1H-2", cutnames);

          // _cutflows.addCutflow("SR3J-0H-1", cutnames);
          // _cutflows.addCutflow("SR3J-0H-2", cutnames);
          // _cutflows.addCutflow("SR3J-0H-3", cutnames);
          // _cutflows.addCutflow("SR3J-0H-4", cutnames);

          // _cutflows.addCutflow("SR3J-1H-1", cutnames);
          // _cutflows.addCutflow("SR3J-1H-2", cutnames);

          _cutflows.addCutflow("CMS_SUS_20_003", cutnames);

          cout << _cutflows << endl;
        #endif
      }

      void run(const HEPUtils::Event *event)
      {
        #ifdef CHECK_CUTFLOW
          const double w = event->weight();
          _cutflows["CMS_SUS_20_003"].fillinit(w);
          _cutflows["CMS_SUS_20_003"].fillnext(w); // no cut
        #endif
        ////////////////////////
        // Useful definiitons //
        // Baseline objects
        double met = event->met();
        // double w = event->weight();
        // cout << "Event weight is -> " << w << endl;

        // Baseline ELectrons
        BASELINE_PARTICLES(event->electrons(), baselineElectrons, 30, 0, DBL_MAX, 1.44, CMS::eff2DEl.at("SUS_19_008"))
        BASELINE_PARTICLES(event->muons(), baselineMuons, 25, 0, DBL_MAX, 2.1, CMS::eff2DMu.at("SUS_19_008"))
        BASELINE_PARTICLE_COMBINATION(baselineLeptons, baselineElectrons, baselineMuons);
        BASELINE_JETS(event->jets("antikt_R04"), baselineJets, 30., 0., DBL_MAX, 2.4)
        BASELINE_BJETS(event->jets("antikt_R04"), baselineBJets, 30., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("DeepCSVMedium"), CMS::misIDBJet.at("DeepCSVMedium"))
        BASELINE_JETS(event->jets("antikt_R08"), baselineLargeRJets, 250., 0., DBL_MAX, 2.4)

        vector<const HEPUtils::Particle *> baselineTaus;
        for (const HEPUtils::Particle *tau : event->taus())
        {
          if (tau->pT() > 10. && tau->abseta() < 2.4)
            baselineTaus.push_back(tau);
        }

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
          for (const HEPUtils::Jet *j : event->jets("antikt_R04"))
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
          for (const HEPUtils::Jet *j : event->jets("antikt_R04"))
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

        BASELINE_PARTICLES(event->electrons(), vetoElectrons, 5.0, 0, DBL_MAX, 2.4, CMS::eff2DEl.at("SUS_19_008"));
        BASELINE_PARTICLES(event->muons(), vetoMuons, 5.0, 0, DBL_MAX, 2.4, CMS::eff2DMu.at("SUS_19_008"));

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
          for (const HEPUtils::Jet *j : event->jets("antikt_R04"))
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
          for (const HEPUtils::Jet *j : event->jets("antikt_R04"))
          {
            if (mu->mom().deltaR_eta(j->mom()) < Rrel)
              sumpt += j->pT();
          }
          if (sumpt / mu->pT() < 0.2)
            vetoLeptons.push_back(mu);
        }

        ////////////////////
        // Signal objects //
        SIGNAL_JETS(baselineJets, signalJets_AK4);
        SIGNAL_JETS(baselineBJets, signalBJets);
        SIGNAL_JETS(baselineLargeRJets, signalJets_AK8)

        removeOverlap(signalJets_AK8, signalLeptons, 0.8);
        removeOverlap(signalJets_AK4, signalLeptons, 0.4);
        removeOverlap(signalBJets, signalLeptons, 0.4);


        #ifdef CHECK_CUTFLOW
          _cutflows["CMS_SUS_20_003"].fill(2, w); // no cut
        #endif

        if (vetoLeptons.size() > 1) return;

        #ifdef CHECK_CUTFLOW
          _cutflows["CMS_SUS_20_003"].fill(3, w); // no cut
        #endif

        if (baselineTaus.size() > 0) return;

        #ifdef CHECK_CUTFLOW
          _cutflows["CMS_SUS_20_003"].fill(4, w); // no cut
        #endif
        // #ifdef CHECK_CUTFLOW
        //   _cutflows.fill(4, event->weight()); // no cut
        // #endif
        // flag of preselection requirement; Table 3
        bool nlepton_ps = false;
        bool nsRjs_ps = false;
        bool ptmiss_ps = false;
        bool mbb_ps = false;
        bool mt_ps = false;
        bool mct_ps = false;

        double mbb;
        double mct;
        double mTl;
        int NHjet = 0;
        int Njets = signalJets_AK4.size();

        if (signalLeptons.size() == 1)
        {
          nlepton_ps = true;
          #ifdef CHECK_CUTFLOW
            _cutflows["CMS_SUS_20_003"].fill(5, w); // no cut
          #endif

          mTl = mT(signalLeptons.at(0)->mom(), event->missingmom());

          if (mTl > 150.)
          {
            mt_ps = true;
            #ifdef CHECK_CUTFLOW
              _cutflows["CMS_SUS_20_003"].fill(6, w); // no cut
            #endif
          }
        }
        if (Njets == 2 && signalBJets.size() == 2)
        {
          nsRjs_ps = true;
          #ifdef CHECK_CUTFLOW
            _cutflows["CMS_SUS_20_003"].fill(7, w); // no cut
            _cutflows["CMS_SUS_20_003"].fill(8, w); // no cut
          #endif
        }

        if (Njets == 3 && signalBJets.size() == 2)
        {
          if (signalJets_AK4[0]->pT() < 300.){
            nsRjs_ps = true;
            #ifdef CHECK_CUTFLOW
              _cutflows["CMS_SUS_20_003"].fill(7, w); // no cut
              _cutflows["CMS_SUS_20_003"].fill(9, w); // no cut
            #endif
          }
        }
        if (met > 125.){
          ptmiss_ps = true;
          #ifdef CHECK_CUTFLOW
            _cutflows["CMS_SUS_20_003"].fill(10, w); // no cut
          #endif
        }

        if (nsRjs_ps)
        {
          mbb = (signalBJets.at(0)->mom() + signalBJets.at(1)->mom()).m();
          mct = mCT(signalBJets.at(0)->mom(), signalBJets.at(1)->mom());
          if (mbb > 90. && mbb < 150.)
          {
            mbb_ps = true;
            #ifdef CHECK_CUTFLOW
              _cutflows["CMS_SUS_20_003"].fill(11, w);
            #endif
          }
          if (mct > 200.)
          {
            mct_ps = true;
            #ifdef CHECK_CUTFLOW
              _cutflows["CMS_SUS_20_003"].fill(12, w);
            #endif
          }
          if (signalJets_AK8.size() == 1)
          {
            #ifdef CHECK_CUTFLOW
              _cutflows["CMS_SUS_20_003"].fill(13, w);
            #endif
            if ((signalJets_AK8.at(0)->mom().deltaR_eta(signalBJets.at(0)->mom()) < 0.8) && (signalJets_AK8.at(0)->mom().deltaR_eta(signalBJets.at(1)->mom()) < 0.8))
            {
              NHjet = 1;
              #ifdef CHECK_CUTFLOW
                _cutflows["CMS_SUS_20_003"].fill(14, w);
              #endif
            }
          }
        }


        // Counting numbers of SRs
        // if (nlepton_ps && nsRjs_ps && ptmiss_ps && mbb_ps && mt_ps && mct_ps)
        if (nlepton_ps && nsRjs_ps && ptmiss_ps && mbb_ps && mt_ps && mct_ps)
        {
          #ifdef CHECK_CUTFLOW
            _cutflows["CMS_SUS_20_003"].fill(15, w);
          #endif

          if (NHjet == 0 && Njets == 2)
          {
            if (met >= 125. && met < 200.) {_counters.at("SR2J-0H-1").add_event(event);}
            if (met >= 200. && met < 300.) {_counters.at("SR2J-0H-2").add_event(event);}
            if (met >= 300. && met < 400.) {_counters.at("SR2J-0H-3").add_event(event);}
            if (met >= 400.)               {_counters.at("SR2J-0H-4").add_event(event);}

            #ifdef CHECK_CUTFLOW
              _cutflows["CMS_SUS_20_003"].fill(16, w);
            #endif

          }

          if (NHjet == 1 && Njets == 2)
          {
            if (met >= 125. && met < 300.) {_counters.at("SR2J-1H-1").add_event(event);}
            if (met >= 300.)               {_counters.at("SR2J-1H-2").add_event(event);}

            #ifdef CHECK_CUTFLOW
              _cutflows["CMS_SUS_20_003"].fill(17, w);
            #endif

          }

          if (NHjet == 0 && Njets == 3)
          {
            if (met >= 125. && met < 200.) {_counters.at("SR3J-0H-1").add_event(event);}
            if (met >= 200. && met < 300.) {_counters.at("SR3J-0H-2").add_event(event);}
            if (met >= 300. && met < 400.) {_counters.at("SR3J-0H-3").add_event(event);}
            if (met >= 400.)               {_counters.at("SR3J-0H-4").add_event(event);}

            #ifdef CHECK_CUTFLOW
              _cutflows["CMS_SUS_20_003"].fill(18, w);
            #endif
          }

          if (NHjet == 1 && Njets == 3)
          {
            if (met >= 125. && met < 300.) {_counters.at("SR3J-1H-1").add_event(event);}
            if (met >= 300.)               {_counters.at("SR3J-1H-2").add_event(event);}

            #ifdef CHECK_CUTFLOW
              _cutflows["CMS_SUS_20_003"].fill(19, w);
            #endif
          }
        }

        return;
      }

      virtual void collect_results()
      {

        // Commit the results for signal regions, included observed and bacground counts
        // COMMIT_SIGNAL_REGION(SR, OBS, BKG, BKG_ERR)

        add_result(SignalRegionData(_counters.at("SR2J-0H-1"), 8.,  {6.9,  1.3}));
        add_result(SignalRegionData(_counters.at("SR2J-0H-2"), 2.,  {3.4,  0.6}));
        add_result(SignalRegionData(_counters.at("SR2J-0H-3"), 1.,  {1.0,  0.3}));
        add_result(SignalRegionData(_counters.at("SR2J-0H-4"), 1.,  {0.3,  0.1}));
        add_result(SignalRegionData(_counters.at("SR2J-1H-1"), 3.,  {2.5,  0.9}));
        add_result(SignalRegionData(_counters.at("SR2J-1H-2"), 1.,  {0.9,  0.5}));
        add_result(SignalRegionData(_counters.at("SR3J-0H-1"), 17., {17.8, 3.0}));
        add_result(SignalRegionData(_counters.at("SR3J-0H-2"), 6.,  {7.8,  1.7}));
        add_result(SignalRegionData(_counters.at("SR3J-0H-3"), 0.,  {1.5,  0.5}));
        add_result(SignalRegionData(_counters.at("SR3J-0H-4"), 0.,  {0.5,  0.3}));
        add_result(SignalRegionData(_counters.at("SR3J-1H-1"), 10., {5.9,  2.1}));
        add_result(SignalRegionData(_counters.at("SR3J-1H-2"), 0.,  {2.1,  0.6}));

        // Add cutflow data to the analysis results
        COMMIT_CUTFLOWS;
          // _cutflows.combine();
        //cout << "\nCUTFLOWS:\n" << _cutflows << endl;
        //cout << "\nSRCOUNTS:\n";
        // Note: The sum() call below gives the raw event count. Use weight_sum() for the sum of event weights.
        //for (auto& pair : _counters) cout << pair.first << " ->\t"<< pair.second.sum() << "\n";
        //cout << "\n" << endl;
      }

      double mT(const HEPUtils::P4 &pV, const HEPUtils::P4 &pI)
      {
        double deltaPhi = pV.deltaPhi(pI);
        double mT = sqrt(
            2 * pV.pT() * pI.pT() * (1 - cos(deltaPhi)));

        return mT;
      }

      double mCT(const HEPUtils::P4 &pV, const HEPUtils::P4 &pI)
      {
        double deltaPhi = pV.deltaPhi(pI);
        double mCT = sqrt(
            2 * pV.pT() * pI.pT() * (1 + cos(deltaPhi)));

        return mCT;
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
    DEFINE_ANALYSIS_FACTORY(CMS_SUS_20_003)

  }
}
