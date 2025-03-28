///
///  \author Holly Pacey
///  \date 2025 January
///
///  \author Pengxuan Zhu
///  \date 2025 March
///  *********************************************

// Based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/EXOT-2019-07/
// Luminosity: 139 fb^-1

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "fastjet/contrib/VariableRPlugin.hh"

#ifndef FJCORE
#ifndef FJNS
#define FJNS fastjet
#endif
#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/tools/Filter.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/Selector.hh"
#else
#include "fjcore.hh"
#ifndef FJNS
#define FJNS fjcore
#endif
#endif

// #define CHECK_CUTFLOW

#ifdef CHECK_CUTFLOW
#include "YODA/Histo1D.h"
#include "YODA/WriterYODA.h"
#endif

using namespace std;

namespace Gambit
{
    namespace ColliderBit
    {

        class Analysis_ATLAS_EXOT_2019_07 : public Analysis
        {

        protected:
            // std::map<string, EventCounter> _counters = {
            //     {"SR_bin_mJJ_1p0_1p1", EventCounter("SR_bin_mJJ_1p0_1p1")},
            //     {"SR_bin_mJJ_1p1_1p2", EventCounter("SR_bin_mJJ_1p1_1p2")},
            //     {"SR_bin_mJJ_1p2_1p3", EventCounter("SR_bin_mJJ_1p2_1p3")},
            //     {"SR_bin_mJJ_1p3_1p4", EventCounter("SR_bin_mJJ_1p3_1p4")},
            //     {"SR_bin_mJJ_1p4_1p5", EventCounter("SR_bin_mJJ_1p4_1p5")},
            //     {"SR_bin_mJJ_1p5_1p6", EventCounter("SR_bin_mJJ_1p5_1p6")},
            //     {"SR_bin_mJJ_1p6_1p7", EventCounter("SR_bin_mJJ_1p6_1p7")},
            //     {"SR_bin_mJJ_1p7_1p8", EventCounter("SR_bin_mJJ_1p7_1p8")},
            //     {"SR_bin_mJJ_1p8_1p9", EventCounter("SR_bin_mJJ_1p8_1p9")},
            //     {"SR_bin_mJJ_1p9_2p0", EventCounter("SR_bin_mJJ_1p9_2p0")},
            //     {"SR_bin_mJJ_2p0_2p1", EventCounter("SR_bin_mJJ_2p0_2p1")},
            //     {"SR_bin_mJJ_2p1_2p2", EventCounter("SR_bin_mJJ_2p1_2p2")},
            //     {"SR_bin_mJJ_2p2_2p3", EventCounter("SR_bin_mJJ_2p2_2p3")},
            //     {"SR_bin_mJJ_2p3_2p4", EventCounter("SR_bin_mJJ_2p3_2p4")},
            //     {"SR_bin_mJJ_2p4_2p5", EventCounter("SR_bin_mJJ_2p4_2p5")},
            //     {"SR_bin_mJJ_2p5_3p1", EventCounter("SR_bin_mJJ_2p5_3p1")},
            // };

        private:
            struct ptComparison
            {
                bool operator()(const HEPUtils::Particle *i, const HEPUtils::Particle *j) { return (i->pT() > j->pT()); }
            } comparePt;

            struct ptJetComparison
            {
                bool operator()(const HEPUtils::Jet *i, const HEPUtils::Jet *j) { return (i->pT() > j->pT()); }
            } compareJetPt;

            // Trim reclustered jets (and conveniently apply pt/eta cuts at the same time)
            static void trimJets(const vector<FJNS::PseudoJet> &pjs_in, vector<Jet> &largeJetsOut,
                                 const double frac = 0.00, const double minPt = 0.,
                                 const double maxEta = 6., const double minPt_twosubJets = 0.)
            {
                largeJetsOut.clear();
                for (const FJNS::PseudoJet &pj : pjs_in)
                {
                    if (pj.pt() < minPt || abs(pj.eta()) > maxEta ||
                        (pj.pt() < minPt_twosubJets && pj.constituents().size() == 1))
                        continue;
                    const double vetoPt = frac * pj.pt();
                    P4 running_total;
                    vector<FJNS::PseudoJet> preserved_subjets;
                    for (const FJNS::PseudoJet &constit : pj.constituents())
                    {
                        if (constit.pt() > vetoPt)
                        {
                            preserved_subjets.push_back(constit);
                            running_total += P4(constit.px(), constit.py(), constit.pz(), constit.E());
                        }
                    }
                    if (running_total.pT() < minPt || running_total.abseta() > maxEta ||
                        (running_total.pT() < minPt_twosubJets && preserved_subjets.size() == 1))
                        continue;
                    largeJetsOut.emplace_back(running_total);
                }
            }

            constexpr static double mtop = 172.76; // [GeV]

        public:
            #ifdef CHECK_CUTFLOW
                    Cutflows _cutflows;
                    YODA::Histo1D *_histo_mHt;
                    int Nents = 0;
            #endif

            // Required detector sim
            static constexpr const char *detector = "ATLAS";

            Analysis_ATLAS_EXOT_2019_07()
            {
                DEFINE_SIGNAL_REGION("SR");
                set_analysis_name("ATLAS_EXOT_2019_07");
                set_luminosity(140.);

            #ifdef CHECK_CUTFLOW
                _histo_mHt = new YODA::Histo1D(15, 1000., 2500., "SR/mHt");
                cout << "====== Cutflows ======" << endl;
                _cutflows.addCutflow("Signal Region", {"Initial signal event",
                                                       "Large-R jet pT and eta cuts",
                                                       "Lepton veto",
                                                       "Leading large-R jet mass in (100, 225) GeV",
                                                       "Second-leading large-R jet mass in (100, 225) GeV",
                                                       "SR tagging requirements",
                                                       "m_Ht > 1 TeV"});
            #endif

                // _cutflows.addCutflow( "SR_binAll", {"JetpTEta", "0LEP", "massJ1", "massJ2", "htTagging", "massHt",});
                // _cutflows.addCutflow( "SR_bin_mJJ_1p0_1p1", {"1.0 TeV < mJJ < 1.1 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_1p1_1p2", {"1.1 TeV < mJJ < 1.2 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_1p2_1p3", {"1.2 TeV < mJJ < 1.3 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_1p3_1p4", {"1.3 TeV < mJJ < 1.4 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_1p4_1p5", {"1.4 TeV < mJJ < 1.5 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_1p5_1p6", {"1.5 TeV < mJJ < 1.6 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_1p6_1p7", {"1.6 TeV < mJJ < 1.7 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_1p7_1p8", {"1.7 TeV < mJJ < 1.8 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_1p8_1p9", {"1.8 TeV < mJJ < 1.9 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_1p9_2p0", {"1.9 TeV < mJJ < 2.0 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_2p0_2p1", {"2.0 TeV < mJJ < 2.1 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_2p1_2p2", {"2.1 TeV < mJJ < 2.2 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_2p2_2p3", {"2.2 TeV < mJJ < 2.3 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_2p3_2p4", {"2.3 TeV < mJJ < 2.4 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_2p4_2p5", {"2.4 TeV < mJJ < 2.5 TeV",});
                // _cutflows.addCutflow( "SR_bin_mJJ_2p5_3p1", {"2.5 TeV < mJJ < 3.1 TeV",});

                //
                //      Counters for the number of accepted events for each signal region

                //      Trigger: >1 Jet, various pT cuts up to 480 GeV, analysis on plateau.

                //      Electrons: ET > 25 GeV, |eta| < 2.47, exclude crack region 1.37 < |eta| < 1.52,
                //                 Gradient Isolation, Tight ID
                //      Muons: pT > 25 GeV, |eta| < 2.5,
                //             muons removed if within dR < 0.4 of a jet
                //      jets: AntiKt_R04, pT > 35 GeV, |eta| < 2.5
                //            JVT something for jets with |eta| < 2.4, pT < 60 GeV
                //      Jets: AntiKt_R10, pT > 350 GeV, |eta| < 2.0
                //            Trimming algorithm applied
                //      VR-jets: AntiKt_R002-04, pT > 35 GeV, |eta| < 2.5,
                //               associate to large-R jet if dR(VRj, J) < 1.0
                //               b-tagging 70% DL1, 10 (400) bg rejection for c (light) jets

                //      H-tag: 100 GeV < mJ < 140 GeV
                //             tau_21 selection binned in pT(J) with a 70% efficiency
                //             5-10 bg rejection factor for light quark and gluon jets.

                //      top-tag: 140 GeV < mJ < 225 GeV
                //               substructure-based DNN 80% efficiency

                //      Preselection: >=2 Large-R jets with pT > 350 GeV and |eta| < 2.0,
                //                    pT(J1) > 500 GeV
                //                    100 GeV < m(J1) < 225 GeV, 100 GeV < m(J2) < 225 GeV,
                //                    ==0 electrons, ==0 muons
                //      SR: one J is H-tagged and has >=2 associated b-jets
                //          other J is top-tagged and has >=1 associated b-jets
                //      Discriminant: 1 TeV < mJJ < 2.3 TeV, bin-width 0.1 TeV
            }

            void run(const HEPUtils::Event *event)
            {
                #ifdef CHECK_CUTFLOW
                    _cutflows["Signal Region"].fillinit(event->weight());
                    _cutflows["Signal Region"].fill(1, true, event->weight());
                    if (Nents % 200 == 0)
                    {
                        cout << "Complete " << Nents << " Events" << endl;
                    }
                    Nents += 1;
                #endif

                // const double w = event->weight();
                // _cutflows.fillinit(w);

                // Baseline objects
                vector<const HEPUtils::Particle *> Electrons;
                vector<const HEPUtils::Particle *> Muons;
                vector<const HEPUtils::Jet *> largeR_Jets;
                vector<const HEPUtils::Jet *> smallR_Jets;
                // vector<const HEPUtils::Jet*> tinyR_Jets;
                vector<const HEPUtils::Jet *> VR_track_Jets;
                vector<const HEPUtils::Jet *> bTagged_Jets;

                // Electrons: pT > 25 GeV, |eta|<1.37 or 1.52<|eta|<2.47. Tight ID, Gradient Iso.
                for (const HEPUtils::Particle *electron : event->electrons())
                {
                    if (electron->pT() > 25 && (electron->abseta() > 1.37 || (electron->abseta() > 1.52 && electron->abseta() < 2.47)))
                        Electrons.push_back(electron);
                }
                applyEfficiency(Electrons, ATLAS::eff1DEl.at("EGAM_2018_01_ID_Tight"));
                applyEfficiency(Electrons, ATLAS::eff1DEl.at("EGAM_2018_01_Iso_Gradient"));

                // Muons: pT > 25 GeV, |eta| < 2.5. Medium ID, Gradient Iso. Remove muons within DeltaRy<0.4 of jet
                for (const HEPUtils::Particle *muon : event->muons())
                {
                    if (muon->pT() > 25. && muon->abseta() < 2.5)
                        Muons.push_back(muon);
                }
                applyEfficiency(Muons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Medium"));
                applyEfficiency(Muons, ATLAS::eff1DMu.at("MUON_2018_03_Iso_Loose")); // Gradient not implemented, hopefully this is similar enough.

                // Small-R jets: pT > 25 GeV, |η| < 2.5, JVT.
                float JVTeff = 0.90;
                for (const HEPUtils::Jet *jet : event->jets("antikt_R04"))
                {
                    if (jet->pT() > 25. && jet->abseta() < 2.5)
                    {
                        if ((jet->pT() < 60. && jet->abseta() < 2.4 && random_bool(JVTeff)) || jet->pT() > 60. || jet->abseta() > 2.4)
                            smallR_Jets.push_back(jet);
                    }
                }
                sort(smallR_Jets.begin(), smallR_Jets.end(), compareJetPt);

                // Large-R jets: pT > 350 GeV, |η| < 2.0.
                for (const HEPUtils::Jet *jet : event->jets("antikt_R10"))
                {
                    if (jet->pT() > 350. && jet->abseta() < 2.0)
                        largeR_Jets.push_back(jet);
                }
                sort(largeR_Jets.begin(), largeR_Jets.end(), compareJetPt);

                
                vector<const HEPUtils::Jet *> VR_jets;
                for (auto &pj : event->vrjets("VRTrackJets"))
                {
                    if (pj->pT() > 25.0 && pj->abseta() < 2.5)
                    VR_jets.push_back(pj);
                }
                sort(VR_jets.begin(), VR_jets.end(), compareJetPt);
                // // B-tag Efficiencies: Figure 3 of ATLAS-CONF-2019-027
                std::map<const Jet *, bool> vrbtag = generateBTagsMap(VR_jets, 0.70119, 0.09639, 0.00390); // 20-30
                for (const HEPUtils::Jet *jet : VR_jets)
                {
                    bool isbtag = vrbtag.at(jet);
                    if (isbtag && jet->abseta() < 2.5 && jet->pT() > 25.)
                    {
                        bTagged_Jets.push_back(jet);
                    }
                }
                
                // Large-R jet Trimming
                vector<const HEPUtils::Jet *> higgsJets;
                vector<const HEPUtils::Jet *> topJets;
                vector<const HEPUtils::Jet *> signalLargeRJets; 
                
                const double Rsub = 0.2;
                const double ptfrac = 0.05;
                FJNS::Filter trimmer(fastjet::JetDefinition(fastjet::antikt_algorithm, Rsub), fastjet::SelectorPtFractionMin(ptfrac));
                int hid = -1; 
                int tid = -1; 
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, 1.0);
                for (size_t i = 0; i < largeR_Jets.size(); ++i)
                {
                    // Obtain the FastJet PseudoJet objects;
                    const fastjet::PseudoJet &pseudojet = largeR_Jets.at(i)->pseudojet();
                    // Make sure there is constituents inside the jets
                    if (pseudojet.constituents().empty())
                    continue;
                    fastjet::PseudoJet trimmedJet = trimmer(pseudojet);
                    vector<fastjet::PseudoJet> subjets = trimmedJet.pieces();
                    
                    int Nsub = subjets.size();
                    double randomNumber = dis(gen);
                    // cout << "Trimming LargeR Jet -> " << i << " contains -> " << Nsub << " items" << endl;
                    bool lrjet  = (trimmedJet.pt() > 350.) && (abs(trimmedJet.eta()) < 2.0); 
                    bool toptag = lrjet && (trimmedJet.m() >= 140.) && (trimmedJet.m() <= 225.) && (randomNumber < 0.8);
                    bool higgstag = lrjet && (trimmedJet.m() >= 105.) && (trimmedJet.m() <= 140.) && (randomNumber < 0.7);
                    
                    HEPUtils::Jet *hepUtilsJet = new HEPUtils::Jet(trimmedJet);
                    if (toptag)
                    {
                        topJets.push_back(hepUtilsJet);
                        if (tid < 0) tid = i;
                    }
                    else if (higgstag)
                    {
                        higgsJets.push_back(hepUtilsJet);
                        if (hid < 0) hid = i;
                    }
                    if (lrjet) signalLargeRJets.push_back(hepUtilsJet); 
                }
                
                
                // Overlap Remove 
                removeOverlap(Electrons, Muons, 0.01);
                removeOverlap(smallR_Jets, Electrons, 0.2);
                removeOverlap(VR_jets, Electrons, 0.2); 
                removeOverlap(Electrons, smallR_Jets, 0.4); 
                removeOverlap(Electrons, VR_jets, 0.4); 

                removeOverlap(smallR_Jets, Muons, 0.2);
                removeOverlap(VR_jets, Muons, 0.2); 
                removeOverlap(Muons, smallR_Jets, 0.4); 
                removeOverlap(Muons, VR_jets, 0.4); 

                removeOverlap(signalLargeRJets, Electrons, 1.0 ); 
                removeOverlap(smallR_Jets, signalLargeRJets, 1.0 ); 
                
                bool leadingj = (signalLargeRJets.size() > 0) ? signalLargeRJets.at(0)->pT() > 500. : false; 
                int n_leptons = Electrons.size() + Muons.size();
                double mJ1 = signalLargeRJets.size() >= 1 ? signalLargeRJets.at(0)->mass() : 0.; 
                double mJ2 = signalLargeRJets.size() >= 2 ? signalLargeRJets.at(1)->mass() : 0.; 
                
                int  nbHiggs = 0; 
                if (higgsJets.size() >= 1) {
                    for (const HEPUtils::Jet *jet : bTagged_Jets) {
                        if (jet->mom().deltaR_eta(higgsJets.at(0)->mom()) < 1.0) {
                            nbHiggs += 1; 
                        }
                    }
                }
                
                int  nbtop = 0; 
                if (topJets.size() >= 1) {
                    for (const HEPUtils::Jet *jet : bTagged_Jets) {
                        if (jet->mom().deltaR_eta(topJets.at(0)->mom()) < 1.0) {
                            nbtop += 1; 
                        }
                    }
                }
                bool srht = (tid == 0 && hid == 1) || (tid == 1 && hid == 0); 
                bool srnb = srht && (nbtop >= 1) && (nbHiggs >= 2); 
                double mHt = srht ? (higgsJets.at(0)->mom() + topJets.at(0)->mom()).m() : 0.; 
                
                bool pass_JetpTEta = (signalLargeRJets.size() >= 2) && leadingj;
                bool pass_JetpTEta_0LEP = pass_JetpTEta && (n_leptons == 0);
                bool pass_JetpTEta_0LEP_massJ1 = pass_JetpTEta_0LEP && (mJ1 >= 100.) && (mJ1 <= 225.);
                bool pass_JetpTEta_0LEP_massJ1_massJ2 = pass_JetpTEta_0LEP_massJ1 && (mJ2 >= 100.) && (mJ2 <= 225.);
                bool pass_JetpTEta_0LEP_massJ1_massJ2_htTagging = pass_JetpTEta_0LEP_massJ1_massJ2 && (srnb) ;
                bool pass_JetpTEta_0LEP_massJ1_massJ2_htTagging_massht = pass_JetpTEta_0LEP_massJ1_massJ2_htTagging && (mHt >= 1000.);
                // if (pass_JetpTEta_0LEP_massJ1_massJ2_htTagging)
                    // std::cout << "tid -> " << tid << ",hid -> " << hid << ",nbtop -> " << nbtop << ",hbHiggs -> " << nbHiggs << "; " << srnb01 << "; " << srnb02 << "; " << srnb03 << "; " << srnb04 << endl;
                if (pass_JetpTEta_0LEP_massJ1_massJ2_htTagging_massht)  _counters.at("SR").add_event(event);

                #ifdef CHECK_CUTFLOW
                    _cutflows["Signal Region"].fillnext({
                        pass_JetpTEta,
                        pass_JetpTEta_0LEP,
                        pass_JetpTEta_0LEP_massJ1,
                        pass_JetpTEta_0LEP_massJ1_massJ2,
                        pass_JetpTEta_0LEP_massJ1_massJ2_htTagging,
                        pass_JetpTEta_0LEP_massJ1_massJ2_htTagging_massht}, event->weight());
                    if (pass_JetpTEta_0LEP_massJ1_massJ2_htTagging_massht) _histo_mHt->fill(mHt, 1.); 

                #endif

                return;

            } // End run function

            // This function can be overridden by the derived SR-specific classes
            virtual void collect_results()
            {
                // Obs. Exp. Err.

                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p0_1p1"), 100., {106.54, 6.72}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p1_1p2"), 97. , {101.55, 6.06}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p2_1p3"), 77. , {79.52 , 4.78}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p3_1p4"), 58. , {60.08 , 4.27}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p4_1p5"), 29. , {39.80 , 4.02}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p5_1p6"), 29. , {22.82 , 3.33}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p6_1p7"), 21. , {21.97 , 2.58}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p7_1p8"), 12. , {16.16 , 1.70}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p8_1p9"), 15. , {11.58 , 1.65}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_1p9_2p0"), 10. , {7.33  , 0.92}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p0_2p1"), 7.  , {6.21  , 0.89}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p1_2p2"), 5.  , {3.90  , 0.61}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p2_2p3"), 3.  , {3.38  , 0.64}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p3_2p4"), 1.  , {2.55  , 0.58}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p4_2p5"), 0.  , {1.65  , 0.41}));
                // add_result(SignalRegionData(_counters.at("SR_bin_mJJ_2p5_3p1"), 1.2 , {1.29  , 0.18}));

                add_result(SignalRegionData(_counters.at("SR"), 471., {494., 22.}));

                COMMIT_CUTFLOWS;
                #ifdef CHECK_CUTFLOW
                    std::vector<YODA::AnalysisObject *> histos;
                    histos.push_back(_histo_mHt);
                    YODA::WriterYODA::write("ATLAS_EXOT_2019_07.yoda", histos.begin(), histos.end());
                    delete _histo_mHt;
                #endif
                return;
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

        // Factory fn
        DEFINE_ANALYSIS_FACTORY(ATLAS_EXOT_2019_07);

    }
}