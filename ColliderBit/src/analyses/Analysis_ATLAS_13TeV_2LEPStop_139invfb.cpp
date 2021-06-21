#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

//#define CHECK_CUTFLOW

using namespace std;

/* 
  The ATLAS 2 lepton direct stop analysis (139 fb^-1) - `heavy stop'.

  Based on: 
  - ATLAS analysis arXiv:2102.01444, and the GAMBIT implenmen
  - The code in Analysis_ATLAS_13TeV_2LEPStop_139invfb.cpp (by Yang Zhang)

  Author: Anders Kvellestad

  Known issues:
  - 3-body and 4-body SRs not yet implemented
  - Use the event-based ETmiss significance rather than the object-based one. 
    See https://cds.cern.ch/record/2630948/files/ATLAS-CONF-2018-038.pdf

*/

namespace Gambit 
{
  namespace ColliderBit 
  {

    // This analysis class is a base class for two SR-specific analysis classes
    // defined further down:
    // - ATLAS_13TeV_2LEPStop_inclusive_139invfb
    // - ATLAS_13TeV_2LEPStop_exclusive_139invfb
    class Analysis_ATLAS_13TeV_2LEPStop_139invfb : public Analysis 
    {
    public:

        // Numbers passing cuts
        std::map<string, EventCounter> _counters = {
            {"SR2bSF110", EventCounter("SR2bSF110")},
            {"SR2bSF120", EventCounter("SR2bSF120")},
            {"SR2bSF140", EventCounter("SR2bSF140")},
            {"SR2bSF160", EventCounter("SR2bSF160")},
            {"SR2bSF180", EventCounter("SR2bSF180")},
            {"SR2bSF220", EventCounter("SR2bSF220")},
            // 
            {"SR2bDF110", EventCounter("SR2bDF110")},
            {"SR2bDF120", EventCounter("SR2bDF120")},
            {"SR2bDF140", EventCounter("SR2bDF140")},
            {"SR2bDF160", EventCounter("SR2bDF160")},
            {"SR2bDF180", EventCounter("SR2bDF180")},
            {"SR2bDF220", EventCounter("SR2bDF220")},
            //
            {"SR2bInc110", EventCounter("SR2bInc110")},
            {"SR2bInc120", EventCounter("SR2bInc120")},
            {"SR2bInc140", EventCounter("SR2bInc140")},
            {"SR2bInc160", EventCounter("SR2bInc160")},
            {"SR2bInc180", EventCounter("SR2bInc180")},
            {"SR2bInc200", EventCounter("SR2bInc200")},
            {"SR2bInc220", EventCounter("SR2bInc220")},
        };

        #ifdef CHECK_CUTFLOW
            Cutflows _cutflows;
        #endif

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        Analysis_ATLAS_13TeV_2LEPStop_139invfb()
        {

            set_analysis_name("ATLAS_13TeV_2LEPStop_139invfb");
            set_luminosity(139.);

            #ifdef CHECK_CUTFLOW
                // Book cutflows
                _cutflows.addCutflow("SR2b",{"no cut",
                                             "2 leptons",
                                             "2 signal leptons",
                                             "pT(l1) > 25, pT(l2) > 20",
                                             "trigger",
                                             "OS leptons",
                                             "mll > 20",
                                             "SF w/ |mll - mZ| > 20 or DF",
                                             "n_bjets >= 1",
                                             "Delta phi_boost < 1.5",
                                             "ETmiss significance > 12",
                                             "mT2 >= 110"});
            #endif

        }

        void run(const HEPUtils::Event* event)
        {

            #ifdef CHECK_CUTFLOW
                const double w = event->weight();
                _cutflows.fillinit(w);
                _cutflows.fillnext(w);  // no cut
            #endif


            // 
            // Collect baseline objects
            // 

            // Missing energy
            double met = event->met();
            HEPUtils::P4 pmiss = event->missingmom();

            // Baseline lepton objects
            vector<const HEPUtils::Particle*> baselineElectrons, baselineMuons;
            for (const HEPUtils::Particle* electron : event->electrons())
            {
                if (electron->pT() > 4.5 && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
            }

            // Apply electron efficiency
            ATLAS::applyElectronEff(baselineElectrons);

            // Apply loose electron selection
            ATLAS::applyLooseIDElectronSelectionR2(baselineElectrons);

            // Create a list of baseline electrons with pT > 100 (used for overlap removal)
            vector<const HEPUtils::Particle*> baselineElectronsPTgt100;
            for (const HEPUtils::Particle* electron : baselineElectrons)
            {
                if (electron->pT() > 100.)
                {
                    baselineElectronsPTgt100.push_back(electron);
                }
            }

            // AK: Ask Yang about this flat 89% effiency -- is it a replacement for ID efficiency?
            // const std::vector<double>  a = {0,10.};
            // const std::vector<double>  b = {0,10000.};
            // const vector<double> cMu={0.89};
            // HEPUtils::BinnedFn2D<double> _eff2dMu(a,b,cMu);
            for (const HEPUtils::Particle* muon : event->muons())
            {
                // bool hasTrig=has_tag(_eff2dMu, muon->abseta(), muon->pT());
                // if (muon->pT() > 4. && muon->abseta() < 2.4 && hasTrig) baselineMuons.push_back(muon);
                if (muon->pT() > 4. && muon->abseta() < 2.4) baselineMuons.push_back(muon);
            }

            // Apply muon efficiency
            ATLAS::applyMuonEffR2(baselineMuons);

            // AK: Is "Medium" identification included in applyMuonEffR2 efficiency?
            // TG: No, and it is also missing from the ATLAS efficiencies, but it's generally over 99% effieciency

            // Jets
            // 
            // - Including a 90% efficiency for jets w/ pT < 120 and |eta| < 2.5, 
            //   to emualte the requirement that many tracks are consistent with 
            //   primary vertex (see paper)

            vector<const HEPUtils::Jet*> baselineJets;
            for (const HEPUtils::Jet* jet : event->jets()) 
            {
                if (jet->pT() > 20. && jet->abseta() < 2.8) 
                {
                    if (jet->pT() < 120 && jet->abseta() < 2.5)
                    {
                        if (random_bool(0.90)) baselineJets.push_back(jet);
                    }
                    else
                    {
                        baselineJets.push_back(jet);
                    }
                }
            }


            // Get map<Jet*,bool> with generated btags for this analysis.
            // B-tag efficiencies:
            // - for correctly tagging a b-jet: 77%
            // - for misstagging a c-jet: 1/4.9 = 20.4%
            // - for misstagging a gluon or light-quark jet: 1/110 = 0.9%
            std::map<const Jet*,bool> analysisBtags = generateBTagsMap(baselineJets, 0.77, 0.204, 0.009);

            // AK: This is missing a 1/15 = 6.7% chance for misstagging a tau jet as a b-jet

            // Split baseline jets into exlusive categories: b-jets and non-bjets (based on our generated tags)
            vector<const HEPUtils::Jet*> baselineBJets;
            vector<const HEPUtils::Jet*> baselineNonBJets;
            for (const HEPUtils::Jet* j : baselineJets)
            {
                if (analysisBtags.at(j))
                {
                    baselineBJets.push_back(j);
                }
                else
                {
                    baselineNonBJets.push_back(j);                    
                }
            }


            // Overlap removal
            // 1) Remove muons with 0.01 of an electron, mimics shared tracks
            removeOverlap(baselineMuons, baselineElectrons, 0.01);
            // 2) Remove non-b-jets within DeltaR = 0.2 of electron
            removeOverlap(baselineNonBJets, baselineElectrons, 0.2);
            // 3) Also remove b-jets within DeltaR = 0.2 of electron *if* electron has pT > 100
            removeOverlap(baselineBJets, baselineElectronsPTgt100, 0.2);
            // 4) If any lepton has Delta R < min(0.4, 0.04 + 10/pT(l)) with a jet, remove the lepton.
            auto lambda = [](double lepton_pT) { return std::min(0.4, 0.04 + 10./(lepton_pT) ); };
            removeOverlap(baselineElectrons, baselineNonBJets, lambda);
            removeOverlap(baselineElectrons, baselineBJets, lambda);
            removeOverlap(baselineMuons, baselineNonBJets, lambda);
            removeOverlap(baselineMuons, baselineBJets, lambda);

            int n_baseline_leptons = baselineElectrons.size();
            n_baseline_leptons += baselineMuons.size();

            // Scalar sum of the transverse momenta from all the reconstructed hard objects
            // Needed for calculating ETmiss significance later
            double HT = 0.0;
            for (const HEPUtils::Jet* j : baselineJets) HT += j->pT();
            for (const HEPUtils::Particle* p : event->photons()) HT += p->pT();
            for (const HEPUtils::Particle* e : baselineElectrons) HT += e->pT();
            for (const HEPUtils::Particle* mu : baselineMuons) HT += mu->pT();

            // 
            // Signal objects
            // 

            // b jets
            vector<const HEPUtils::Jet*> signalBJets = baselineBJets;

            // non-b jets
            vector<const HEPUtils::Jet*> signalNonBJets = baselineNonBJets;

            // all jets
            vector<const HEPUtils::Jet*> signalJets = signalBJets;
            signalJets.insert(signalJets.end(), signalNonBJets.begin(), signalNonBJets.end());

            // electrons
            vector<const HEPUtils::Particle*> signalElectrons = baselineElectrons;
            ATLAS::applyMediumIDElectronSelectionR2(signalElectrons);

            // muons
            vector<const HEPUtils::Particle*> signalMuons = baselineMuons;

            // all leptons
            vector<const HEPUtils::Particle*> signalLeptons;
            signalLeptons = signalElectrons;
            signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());


            // Sort in order of decreasing pT
            sortByPt(signalBJets);
            sortByPt(signalNonBJets);
            sortByPt(signalJets);
            sortByPt(signalElectrons);
            sortByPt(signalMuons);
            sortByPt(signalLeptons);


            // 
            // Event selection
            // 

            // Implements the selection via a bunch of bools instead of early return
            // statements, to make it easy to implement cut-flows for SR2b*, SR3b* and
            // SR4* all at once

            // ----- Two-body SRs (SR2b) -----

            bool SR2b_2leptons      = false;
            bool SR2b_2signalleptons= false;
            bool SR2b_pTl1_pTl2     = false;

            bool SR2b_trigger       = false;
            bool SR2b_OS            = false;
            bool SR2b_mll           = false;

            bool SR2b_SF            = false;
            bool SR2b_SF_mll_req    = false;
            bool SR2b_DF            = false;

            bool SR2b_nbjets        = false;
            bool SR2b_dphiboost     = false;
            bool SR2b_ETmiss_sig    = false;
            bool SR2b_mT2           = false;

            bool SR2b_mT2_gt_110    = false;
            bool SR2b_mT2_gt_120    = false;
            bool SR2b_mT2_gt_140    = false;
            bool SR2b_mT2_gt_160    = false;
            bool SR2b_mT2_gt_180    = false;
            bool SR2b_mT2_gt_200    = false;
            bool SR2b_mT2_gt_220    = false;

            bool SR2b_mT2_110_120   = false;
            bool SR2b_mT2_120_140   = false;
            bool SR2b_mT2_140_160   = false;
            bool SR2b_mT2_160_180   = false;
            bool SR2b_mT2_180_220   = false;
            bool SR2b_mT2_220_inf   = false;


            // Need a block to break out from when a cut fails
            while(true)
            {
                // Require exactly 2 leptons
                if (n_baseline_leptons == 2) { SR2b_2leptons = true; }

                // Require exactly 2 signal leptons
                if (signalLeptons.size() == 2) { SR2b_2signalleptons = true; }
                else break;

                // Require pT > 25 GeV and pT > 20 GeV for the two leptons
                const Particle* lep1 = signalLeptons.at(0);
                const Particle* lep2 = signalLeptons.at(1);
                if (lep1->pT() > 25 && lep2->pT() > 20) { SR2b_pTl1_pTl2 = true; }
                else break;

                // ATLAS cutflow has trigger entry -- don't know exactly what it refers to
                SR2b_trigger = true;

                // Require opposite-sign leptons
                if (lep1->pid() * lep2->pid() < 0) { SR2b_OS = true; }
                else break;

                // Require mll > 20 GeV
                double mll = (lep1->mom() + lep2->mom()).m();
                if (mll > 20.) { SR2b_mll = true; }
                else break;

                // Require same-flavour leptons w/ |mll - mZ| > 20
                // or different-flavour leptons
                if (lep1->abspid() == lep2->abspid())
                { 
                    SR2b_SF = true;
                }
                else
                {
                    SR2b_DF = true;
                }
                if (SR2b_SF)
                {
                    if (mll < 71.2 || mll > 111.2) { SR2b_SF_mll_req = true; }
                    else break;
                }

                // Require at least 1 b-jet
                if (signalBJets.size() >= 1) { SR2b_nbjets = true; }
                else break;

                // Require Delta phi_boost < 1.5
                HEPUtils::P4 pbll = lep1->mom() + lep2->mom() + pmiss;
                double dPhi_pmiss_pbll = fabs(pbll.deltaPhi(pmiss));
                if (dPhi_pmiss_pbll < 1.5) { SR2b_dphiboost = true; }
                else break;

                // Require ETmiss significance > 12
                double met_sig = met / sqrt(HT);
                if (met_sig > 12.) { SR2b_ETmiss_sig = true; }
                else break;

                // Require mT2 > 110 GeV
                double mT2 = 0;
                double pa_a[3] = { 0, lep1->mom().px(), lep1->mom().py() };
                double pb_a[3] = { 0, lep2->mom().px(), lep2->mom().py() };
                double pmiss_a[3] = { 0, pmiss.px(), pmiss.py() };
                double mn_a = 0.;
                mt2_bisect::mt2 mt2_event_a;
                mt2_event_a.set_momenta(pa_a,pb_a,pmiss_a);
                mt2_event_a.set_mn(mn_a);
                mT2 = mt2_event_a.get_mt2();
                if (mT2 > 110) {SR2b_mT2 = true; }
                else break;

                // Find mT2 bin(s)
                // First the inclusive bins
                if (mT2 > 110) SR2b_mT2_gt_110 = true;
                if (mT2 > 120) SR2b_mT2_gt_120 = true;
                if (mT2 > 140) SR2b_mT2_gt_140 = true;
                if (mT2 > 160) SR2b_mT2_gt_160 = true;
                if (mT2 > 180) SR2b_mT2_gt_180 = true;
                if (mT2 > 200) SR2b_mT2_gt_200 = true;
                if (mT2 > 220) SR2b_mT2_gt_220 = true;
                // Then the exclusive bins
                if (mT2 > 110 && mT2 < 120) SR2b_mT2_110_120 = true;
                else if (mT2 > 120 && mT2 < 140) SR2b_mT2_120_140 = true;
                else if (mT2 > 140 && mT2 < 160) SR2b_mT2_140_160 = true;
                else if (mT2 > 160 && mT2 < 180) SR2b_mT2_160_180 = true;
                else if (mT2 > 180 && mT2 < 220) SR2b_mT2_180_220 = true;
                else if (mT2 > 220)              SR2b_mT2_220_inf = true;

                // We're done here
                break;
            }

            // Fill cutflow
            #ifdef CHECK_CUTFLOW
                if (SR2b_2leptons) _cutflows["SR2b"].fillnext(w);              // "2 leptons"
                if (SR2b_2signalleptons) _cutflows["SR2b"].fillnext(w);        // "2 signal leptons"
                if (SR2b_pTl1_pTl2) _cutflows["SR2b"].fillnext(w);             // "pT(l1) > 25, pT(l2) > 20"
                if (SR2b_trigger) _cutflows["SR2b"].fillnext(w);               // "trigger"
                if (SR2b_OS) _cutflows["SR2b"].fillnext(w);                    // "OS leptons"
                if (SR2b_mll) _cutflows["SR2b"].fillnext(w);                   // "mll > 20"
                if (SR2b_SF_mll_req || SR2b_DF) _cutflows["SR2b"].fillnext(w); // "SF w/ |mll - mZ| > 20 or DF"
                if (SR2b_nbjets) _cutflows["SR2b"].fillnext(w);                // "n_bjets >= 1"            
                if (SR2b_dphiboost) _cutflows["SR2b"].fillnext(w);             // "Delta phi_boost < 1.5"            
                if (SR2b_ETmiss_sig) _cutflows["SR2b"].fillnext(w);            // "ETmiss significance > 12"            
                if (SR2b_mT2) _cutflows["SR2b"].fillnext(w);                   // "mT2 >= 110"            
            #endif


            // Fill SR counters
            if (SR2b_2leptons && SR2b_2signalleptons && SR2b_pTl1_pTl2 && SR2b_trigger && SR2b_OS && SR2b_mll && (SR2b_SF_mll_req || SR2b_DF)
                && SR2b_nbjets && SR2b_dphiboost && SR2b_ETmiss_sig && SR2b_mT2)
            {
                // Inclusive bins
                if (SR2b_mT2_gt_110) _counters.at("SR2bInc110").add_event(event);
                if (SR2b_mT2_gt_120) _counters.at("SR2bInc120").add_event(event);
                if (SR2b_mT2_gt_140) _counters.at("SR2bInc140").add_event(event);
                if (SR2b_mT2_gt_160) _counters.at("SR2bInc160").add_event(event);
                if (SR2b_mT2_gt_180) _counters.at("SR2bInc180").add_event(event);
                if (SR2b_mT2_gt_200) _counters.at("SR2bInc200").add_event(event);
                if (SR2b_mT2_gt_220) _counters.at("SR2bInc220").add_event(event);

                // Exclusive SF bins
                if (SR2b_SF_mll_req)
                {
                    if (SR2b_mT2_110_120) _counters.at("SR2bSF110").add_event(event);
                    if (SR2b_mT2_120_140) _counters.at("SR2bSF120").add_event(event);
                    if (SR2b_mT2_140_160) _counters.at("SR2bSF140").add_event(event);
                    if (SR2b_mT2_160_180) _counters.at("SR2bSF160").add_event(event);
                    if (SR2b_mT2_180_220) _counters.at("SR2bSF180").add_event(event);
                    if (SR2b_mT2_220_inf) _counters.at("SR2bSF220").add_event(event);
                }
                // Exclusive DF bins
                if (SR2b_DF)
                {
                    if (SR2b_mT2_110_120) _counters.at("SR2bDF110").add_event(event);
                    if (SR2b_mT2_120_140) _counters.at("SR2bDF120").add_event(event);
                    if (SR2b_mT2_140_160) _counters.at("SR2bDF140").add_event(event);
                    if (SR2b_mT2_160_180) _counters.at("SR2bDF160").add_event(event);
                    if (SR2b_mT2_180_220) _counters.at("SR2bDF180").add_event(event);
                    if (SR2b_mT2_220_inf) _counters.at("SR2bDF220").add_event(event);
                }
            }

        }


        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
            const Analysis_ATLAS_13TeV_2LEPStop_139invfb* specificOther
                = dynamic_cast<const Analysis_ATLAS_13TeV_2LEPStop_139invfb*>(other);

            for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
        }


        virtual void collect_results() 
        {
            // Two-body SRs (SR2b*)
            // - SF + DF, inclusive mT2 binning
            add_result(SignalRegionData(_counters.at("SR2bInc110"), 99., { 102., 12.}));
            add_result(SignalRegionData(_counters.at("SR2bInc120"), 63., { 62.2, 6.3}));
            add_result(SignalRegionData(_counters.at("SR2bInc140"), 31., { 32.1, 3.2}));
            add_result(SignalRegionData(_counters.at("SR2bInc160"), 17., { 22.0, 2.1}));
            add_result(SignalRegionData(_counters.at("SR2bInc180"), 13., { 15.7, 1.7}));
            add_result(SignalRegionData(_counters.at("SR2bInc200"), 10., { 11.3, 1.7}));
            add_result(SignalRegionData(_counters.at("SR2bInc220"),  8., {  8.0, 1.4}));
            // - SF, exclusive mT2 binning
            add_result(SignalRegionData(_counters.at("SR2bSF110"), 17., { 18.8, 3.5}));
            add_result(SignalRegionData(_counters.at("SR2bSF120"), 19., { 14.4, 2.9}));
            add_result(SignalRegionData(_counters.at("SR2bSF140"),  9., {  5.1, 0.9}));
            add_result(SignalRegionData(_counters.at("SR2bSF160"),  3., {  3.7, 0.6}));
            add_result(SignalRegionData(_counters.at("SR2bSF180"),  4., {  4.4, 0.7}));
            add_result(SignalRegionData(_counters.at("SR2bSF220"),  5., {  5.,  1.}));
            // - DF, exclusive mT2 binning
            add_result(SignalRegionData(_counters.at("SR2bDF110"), 19., { 22., 4.}));
            add_result(SignalRegionData(_counters.at("SR2bDF120"), 13., { 16.3, 3.2}));
            add_result(SignalRegionData(_counters.at("SR2bDF140"),  5., { 5.1, 0.8}));
            add_result(SignalRegionData(_counters.at("SR2bDF160"),  1., { 2.83, 0.45}));
            add_result(SignalRegionData(_counters.at("SR2bDF180"),  1., { 3.25, 0.45}));
            add_result(SignalRegionData(_counters.at("SR2bDF220"),  3., { 3.11, 0.67}));

            #ifdef CHECK_CUTFLOW
                // Cutflow printout
                _cutflows["SR2b"].normalize(37499., 0);
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

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2LEPStop_139invfb)



    //
    // Derived analysis class using the SR2b inclusive SRs
    //
    class Analysis_ATLAS_13TeV_2LEPStop_inclusive_139invfb : public Analysis_ATLAS_13TeV_2LEPStop_139invfb 
    {

    public:
        Analysis_ATLAS_13TeV_2LEPStop_inclusive_139invfb() 
        {
            set_analysis_name("ATLAS_13TeV_2LEPStop_inclusive_139invfb");
        }

        virtual void collect_results() 
        {
            // Two-body SRs (SR2b*)
            // - SF + DF, inclusive mT2 binning
            add_result(SignalRegionData(_counters.at("SR2bInc110"), 99., { 102., 12.}));
            add_result(SignalRegionData(_counters.at("SR2bInc120"), 63., { 62.2, 6.3}));
            add_result(SignalRegionData(_counters.at("SR2bInc140"), 31., { 32.1, 3.2}));
            add_result(SignalRegionData(_counters.at("SR2bInc160"), 17., { 22.0, 2.1}));
            add_result(SignalRegionData(_counters.at("SR2bInc180"), 13., { 15.7, 1.7}));
            add_result(SignalRegionData(_counters.at("SR2bInc200"), 10., { 11.3, 1.7}));
            add_result(SignalRegionData(_counters.at("SR2bInc220"),  8., {  8.0, 1.4}));

            #ifdef CHECK_CUTFLOW
                // Cutflow printout
                _cutflows["SR2b"].normalize(37499., 0);
                cout << "\nCUTFLOWS:\n" << _cutflows << endl;
                cout << "\nSRCOUNTS:\n";
                // for (double x : _srnums) cout << x << "  ";
                for (auto& pair : _counters) cout << pair.second.weight_sum() << "  ";
                cout << "\n" << endl;
            #endif
 
        }

    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2LEPStop_inclusive_139invfb)



    //
    // Derived analysis class using the SR2b exclusive SRs
    //
    class Analysis_ATLAS_13TeV_2LEPStop_exclusive_139invfb : public Analysis_ATLAS_13TeV_2LEPStop_139invfb 
    {

    public:
        Analysis_ATLAS_13TeV_2LEPStop_exclusive_139invfb() 
        {
            set_analysis_name("ATLAS_13TeV_2LEPStop_exclusive_139invfb");
        }

        virtual void collect_results() 
        {
            // Two-body SRs (SR2b*)
            // - SF, exclusive mT2 binning
            add_result(SignalRegionData(_counters.at("SR2bSF110"), 17., { 18.8, 3.5}));
            add_result(SignalRegionData(_counters.at("SR2bSF120"), 19., { 14.4, 2.9}));
            add_result(SignalRegionData(_counters.at("SR2bSF140"),  9., {  5.1, 0.9}));
            add_result(SignalRegionData(_counters.at("SR2bSF160"),  3., {  3.7, 0.6}));
            add_result(SignalRegionData(_counters.at("SR2bSF180"),  4., {  4.4, 0.7}));
            add_result(SignalRegionData(_counters.at("SR2bSF220"),  5., {  5.,  1.}));
            // - DF, exclusive mT2 binning
            add_result(SignalRegionData(_counters.at("SR2bDF110"), 19., { 22., 4.}));
            add_result(SignalRegionData(_counters.at("SR2bDF120"), 13., { 16.3, 3.2}));
            add_result(SignalRegionData(_counters.at("SR2bDF140"),  5., { 5.1, 0.8}));
            add_result(SignalRegionData(_counters.at("SR2bDF160"),  1., { 2.83, 0.45}));
            add_result(SignalRegionData(_counters.at("SR2bDF180"),  1., { 3.25, 0.45}));
            add_result(SignalRegionData(_counters.at("SR2bDF220"),  3., { 3.11, 0.67}));

            #ifdef CHECK_CUTFLOW
                // Cutflow printout
                _cutflows["SR2b"].normalize(37499., 0);
                cout << "\nCUTFLOWS:\n" << _cutflows << endl;
                cout << "\nSRCOUNTS:\n";
                // for (double x : _srnums) cout << x << "  ";
                for (auto& pair : _counters) cout << pair.second.weight_sum() << "  ";
                cout << "\n" << endl;
            #endif
 
        }

    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2LEPStop_exclusive_139invfb)


  }
}
