///  =============================================
///
///  \author Pengxuan Zhu (zhupx99@icloud.com, pengxuan.zhu@adelaide.edu.cn)
///  \date Jan 2025
///
///  =============================================

// Based on
//  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/EXOT-2016-13/
//  - https://cds.cern.ch/record/2310460
//  - http://arxiv.org/abs/1803.09678
//
// Search for the pair production of heavy vector-like T and B quarks in pp collisions at s√= 13 TeV
//   primarily targeting the events of T quark decays to a Higgs boson / Z + t-quark

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "HEPUtils/FastJet.h"
#include "HEPUtils/Event.h"
#include "HEPUtils/Jet.h"
// #include "fastjet/Filter.hh"
#include <random>
#include "YODA/Histo1D.h"
#include "YODA/WriterYODA.h"

// Similar to ATLAS_13_TeV_3b_NN_139invfb (define structure copied from heputils/FastJet.h)
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

using namespace std;
// #define CHECK_CUTFLOW
// #define CHECK_PLOT

namespace Gambit
{
    namespace ColliderBit
    {
        static bool sortByPT_jet(const HEPUtils::Jet *jet1, const HEPUtils::Jet *jet2) { return (jet1->pT() > jet2->pT()); }

        class Analysis_ATLAS_EXOT_2016_013 : public Analysis
        {

        private:

        #ifdef CHECK_PLOT
            YODA::Histo1D *_histo_NHiggs;
            YODA::Histo1D *_histo_Ntop;
            YODA::Histo1D *_histo_Njet;
            YODA::Histo1D *_histo_Nbjet;
            YODA::Histo1D *_histo_meff_SR1L_03;
            YODA::Histo1D *_histo_meff_SR0L_01; 
            YODA::Histo1D *_histo_mTBmin; 
        #endif

        public:
            static constexpr const char *detector = "ATLAS";

            int Nevent = 0;

            Analysis_ATLAS_EXOT_2016_013()
            {
                DEFINE_SIGNAL_REGION("SR1L-01"); // >=2t, 0-1H, >=6j, 3b
                DEFINE_SIGNAL_REGION("SR1L-02"); // 1t, 0H, >=6j, >=4b
                DEFINE_SIGNAL_REGION("SR1L-03"); // 1t, 1H, >=6j, >=4b
                DEFINE_SIGNAL_REGION("SR1L-04"); // >=2t, 0-1H,>=6j,>=4b
                DEFINE_SIGNAL_REGION("SR1L-05"); // >=0t, >=2H, >=6j, >=4b

                DEFINE_SIGNAL_REGION("SR0L-01"); // >=2tH, >=7j, 2b, HM
                DEFINE_SIGNAL_REGION("SR0L-02"); // 1t, 1H, >=7j, 3b, HM
                DEFINE_SIGNAL_REGION("SR0L-03"); // >=2t, 0-1H, >=7j, 3b, HM
                DEFINE_SIGNAL_REGION("SR0L-04"); // 1t, 0H, >=7j, >=4b, HM
                DEFINE_SIGNAL_REGION("SR0L-05"); // >=2tH, >=7j, >=4b

                set_analysis_name("ATLAS_EXOT_2016_013");
                set_luminosity(36.1);


                #ifdef CHECK_PLOT
                    _histo_NHiggs           = new YODA::Histo1D(5, 0., 5., "/ATLAS_EXOT_2016_013-1L/Higgs-tagged_jet_multiplicity");
                    _histo_Ntop             = new YODA::Histo1D(5, 0., 5., "/ATLAS_EXOT_2016_013-0L/Top-tagged_jet_multiplicity");
                    _histo_Njet             = new YODA::Histo1D(10, 5., 15., "/ATLAS_EXOT_2016_013-1L/Jet_multiplicity");
                    _histo_Nbjet            = new YODA::Histo1D(6, 2., 8., "/ATLAS_EXOT_2016_013-0L/B-tagged_jet_multiplicity");
                    _histo_meff_SR1L_03     = new YODA::Histo1D(12, 500., 3500., "/ATLAS_EXOT_2016_013-1L/meff_SR1L_03");
                    _histo_meff_SR0L_01     = new YODA::Histo1D(12, 500., 3500., "/ATLAS_EXOT_2016_013-0L/meff_SR0L_01");
                    _histo_mTBmin           = new YODA::Histo1D(20, 0., 500., "ATLAS_EXOT_2016_013-0L/mTBmin_SR0L_01"); 
                #endif
            }

            void run(const HEPUtils::Event *event)
            {
                if (Nevent % 200 == 0)
                {
                    cout << "Complete " << Nevent << " Events" << endl;
                }
                HEPUtils::P4 pmiss = event->missingmom();
                const double met = event->met();

                // Baseline lepton objects
                vector<const HEPUtils::Particle *> baselineElectrons, baselineMuons;
                for (const HEPUtils::Particle *electron : event->electrons())
                {
                    if (electron->pT() > 30 && electron->abseta() < 2.47 && (electron->abseta() < 1.37 || electron->abseta() > 1.52))
                    {
                        baselineElectrons.push_back(electron);
                    }
                }
                for (const HEPUtils::Particle *muon : event->muons())
                {
                    if (muon->pT() > 30 && muon->abseta() < 2.5 && (muon->abseta() < 1.37 || muon->abseta() > 1.52))
                    {
                        baselineMuons.push_back(muon);
                    }
                }

                // Missing the Lepton isolation requirement

                // Apply electron efficiency
                // Electron efficiency is defined in ATLAS-CONF-2016-024, susperseded by arXiv:1902.04655.
                applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Tight"));
                // ATLAS::applyElectronEff(baselineElectrons);
                // Muon efficiency is defined in CERN-EP-2016-033, arXiv:1603.05598. PREF-2015-10
                // Due to the muon pT in this work is required to be larger than 30 GeV, choosing the full Run-II effcicency instead.
                applyEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Medium"));
                // ATLAS::applyMuonEff(baselineMuons);
                // Jets

                // cout << "1. Define Lepton candidates" << endl;
                vector<const HEPUtils::Jet *> baselineSmallRJets;
                vector<const HEPUtils::Jet *> baselineLargeRJets;
                vector<fastjet::PseudoJet> trimmedJets;
                vector<HEPUtils::Jet *> higgsJets;
                vector<HEPUtils::Jet *> topJets;
                vector<const HEPUtils::Jet *> bJets;
                vector<const HEPUtils::Jet *> nonbJets;

                // Define smallR-jets and b-jets
                const double btageff = 0.77;
                const double cmistag = 1.0 / 6.2;
                const double misstag = 1.0 / 134.0;
                for (const HEPUtils::Jet *jet : event->jets("antikt_R04"))
                {
                    if (jet->pT() > 25.0 && jet->abseta() < 2.5)
                    {
                        baselineSmallRJets.push_back(jet);
                        if (random_bool(btageff) && jet->btag())
                        {
                            bJets.push_back(jet);
                        }
                        else if (random_bool(cmistag) && jet->ctag())
                        {
                            bJets.push_back(jet);
                        }
                        else if (random_bool(misstag))
                        {
                            bJets.push_back(jet);
                        }
                        else
                            nonbJets.push_back(jet);
                    }
                }
                // Define largeR-jets
                // cout << "2. Define Jet candidates" << endl;
                for (const HEPUtils::Jet *jet : event->jets("antikt_R10"))
                {
                    baselineLargeRJets.push_back(jet);
                }
                // cout << "SmallR jet Number ->" << event->jets("antikt_R04").size() << endl;
                // cout << "LargeR jet Number ->" << baselineLargeRJets.size() << endl;
                // cout << "Before Trimming Jet " << endl;
                const double Rsub = 0.2;
                const double ptfrac = 0.05;
                FJNS::Filter trimmer(fastjet::JetDefinition(fastjet::kt_algorithm, Rsub), fastjet::SelectorPtFractionMin(ptfrac));
                // FJNS::contrib::EnergyCorrelator C2(2, beta, fastjet::contrib::EnergyCorrelator::pt_R);
                // FJNS::contrib::EnergyCorrelator C3(3, beta, fastjet::contrib::EnergyCorrelator::pt_R);

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, 1.0);

                for (size_t i = 0; i < baselineLargeRJets.size(); ++i)
                {
                    // Obtain the FastJet PseudoJet objects;
                    const fastjet::PseudoJet &pseudojet = baselineLargeRJets.at(i)->pseudojet();
                    // Make sure there is constituents inside the jets
                    if (pseudojet.constituents().empty())
                        continue;
                    fastjet::PseudoJet trimmedJet = trimmer(pseudojet);
                    vector<fastjet::PseudoJet> subjets = trimmedJet.pieces();

                    int Nsub = subjets.size();
                    bool toptag = (Nsub >= 2) && (trimmedJet.pt() >= 300.) && (trimmedJet.m() >= 140.);

                    bool higgstag1 = (Nsub == 2) && (trimmedJet.pt() > 200.) && (trimmedJet.pt() < 500.) && (trimmedJet.m() >= 105.) && (trimmedJet.m() <= 140.);
                    bool higgstag2 = (Nsub == 1 || Nsub == 2) && (trimmedJet.pt() >= 500.) && (trimmedJet.m() >= 105.) && (trimmedJet.m() <= 140.);

                    HEPUtils::Jet *hepUtilsJet = new HEPUtils::Jet(trimmedJet);
                    if (toptag)
                        topJets.push_back(hepUtilsJet);
                    else if (higgstag1 || higgstag2)
                        higgsJets.push_back(hepUtilsJet);
                }

                // Define the Energy Correlation Function of W-tagging
                // cout << "Start remove overlaping" << endl;
                // Removing Overlaping
                // 1) Remove electron with muon within DeltaR < 0.01.
                removeOverlap(baselineElectrons, baselineMuons, 0.01);
                // 2) Remove smallR-jet within DeltaR < 0.2 of electron
                removeOverlap(bJets, baselineElectrons, 0.2);
                removeOverlap(nonbJets, baselineElectrons, 0.2);
                // 3) then Remove electron within 0.2 < DeltaR < 0.4 of smallR-jet
                removeOverlap(baselineElectrons, bJets, 0.4);
                removeOverlap(baselineElectrons, nonbJets, 0.4);
                // 4) then Remove muon within 0.2 < DeltaR < 0.4 of smallR-jet
                removeOverlap(baselineMuons, bJets, 0.4);
                removeOverlap(baselineMuons, nonbJets, 0.4);

                // cout << "4. After Overlep Remove ... " << endl;
                // Define Signal objects;
                vector<const HEPUtils::Jet *> signalJets = nonbJets;
                vector<const HEPUtils::Jet *> signalBjets = bJets;
                vector<const HEPUtils::Particle *> signalLeptons = baselineElectrons;
                // vector<const HEPUtils::Particle*> signalMuons = baselineMuons;
                for (const HEPUtils::Particle *muon : baselineMuons)
                {
                    signalLeptons.push_back(muon);
                }
                for (const HEPUtils::Jet *jet : signalBjets)
                {
                    signalJets.push_back(jet);
                }
                std::sort(signalJets.begin(), signalJets.end(), sortByPT_jet);

                // Event Preselection
                int n_leptons = signalLeptons.size();
                int njets = signalJets.size();
                int nbjets = signalBjets.size();
                double mTW = n_leptons == 1 ? get_mT(signalLeptons[0]->mom(), pmiss) : 0.;

                double mindPhijetMet = 999.;
                if (njets >= 4)
                {
                    for (unsigned int i = 0; i < 4; i++)
                        if (signalJets[i]->mom().deltaPhi(pmiss) <= mindPhijetMet)
                            mindPhijetMet = signalJets[i]->mom().deltaPhi(pmiss);
                }

                bool presel1L = (n_leptons == 1) && (njets >= 5) && (nbjets >= 2) && (met > 20.) && (met + mTW > 60.);
                bool presel0L = (n_leptons == 0) && (njets >= 6) && (nbjets >= 2) && (met > 200.) && (mindPhijetMet > 0.4);

                // cout << "After preselection" << endl;
                #ifdef CHECK_PLOT
                    if (presel0L) _histo_Nbjet->fill(nbjets + 0.5, 1.);
                    if (presel1L) _histo_Njet->fill(njets + 0.5, 1.);
                #endif

                if (presel1L && njets >= 6)
                {
                    // cout << "15. 1 lepton signal region" << endl;
                    int Ntop = topJets.size();
                    int NHiggs = higgsJets.size();
                
                    #ifdef CHECK_PLOT
                        _histo_NHiggs->fill(NHiggs + 0.5, 1.);
                    #endif

                    double meff = signalLeptons[0]->pT() + met;
                    for (const HEPUtils::Jet *jet : signalJets)
                    {
                        meff += jet->pT();
                    }
                    // cout << "16. Calculated Meff " << endl;
                    bool sr1l01 = (Ntop >= 2) && (NHiggs == 0 || NHiggs == 1) && (nbjets == 3);
                    bool sr1l02 = (Ntop == 1) && (NHiggs == 0) && (nbjets >= 4) && (meff > 1000.);
                    bool sr1l03 = (Ntop == 1) && (NHiggs == 1) && (nbjets >= 4);
                    bool sr1l04 = (Ntop >= 2) && (NHiggs == 0 || NHiggs == 1) && (nbjets >= 4);
                    bool sr1l05 = (Ntop >= 0) && (NHiggs >= 2) && (nbjets >= 4);
                    if (sr1l01)
                        _counters.at("SR1L-01").add_event(event);
                    if (sr1l02)
                        _counters.at("SR1L-02").add_event(event);
                    if (sr1l03)
                        _counters.at("SR1L-03").add_event(event);
                    if (sr1l04)
                        _counters.at("SR1L-04").add_event(event);
                    if (sr1l05)
                        _counters.at("SR1L-05").add_event(event);
                
                    #ifdef CHECK_PLOT
                        if (sr1l03) _histo_meff_SR1L_03->fill(meff, 1.); 
                    #endif

                    // cout << "17. After SR1L event counting" << endl;
                }
                if (presel0L && njets >= 7)
                {
                    // cout << "25. Start 0 lepton signal region" << endl;
                    int Ntop = topJets.size();
                    int NHiggs = higgsJets.size();
                    int NtH = Ntop + NHiggs;

                    #ifdef CHECK_PLOT
                        _histo_Ntop->fill(Ntop + 0.5, 1.);
                    #endif

                    double meff = met;
                    for (const HEPUtils::Jet *jet : signalJets)
                    {
                        meff += jet->pT();
                    }
                    // cout << "26. Calcuated meff" << endl;
                    double mTb12 = min(get_mT(signalBjets[0]->mom(), pmiss), get_mT(signalBjets[1]->mom(), pmiss));
                    double mTBmin = (nbjets >= 3) ? min(get_mT(signalBjets[2]->mom(), pmiss), mTb12) : mTb12;

                    // cout << "27. Calculated mTb12 and mTBmin" << endl;
                    #ifdef CHECK_PLOT
                        if ((NtH >= 2) && (nbjets == 2)) _histo_meff_SR0L_01->fill(meff, 1.); 
                        if ((NtH >= 2) && (nbjets == 2) && (mTBmin <= 500.)) _histo_mTBmin->fill(mTBmin, 1.); 
                        if ((NtH >= 2) && (nbjets == 2) && (mTBmin > 500.)) _histo_mTBmin->fill(490., 1.); 
                    #endif 

                    bool sr0l01 = (NtH >= 2) && (nbjets == 2) && (mTBmin > 160.) && (meff > 1000.);
                    bool sr0l02 = (Ntop == 1) && (NHiggs == 1) && (nbjets == 3) && (mTBmin > 160.) && (meff > 1000.);
                    bool sr0l03 = (Ntop >= 2) && (NHiggs == 0 || NHiggs == 1) && (nbjets == 3) && (mTBmin > 160.) && (meff > 1000.);
                    bool sr0l04 = (Ntop == 1) && (NHiggs == 0) && (nbjets >= 4) && (mTBmin > 160.) && (meff > 1000.);
                    bool sr0l05 = (NtH >= 2) && (nbjets >= 4) && (meff > 1000.);
                    if (sr0l01)
                        _counters.at("SR0L-01").add_event(event);
                    if (sr0l02)
                        _counters.at("SR0L-02").add_event(event);
                    if (sr0l03)
                        _counters.at("SR0L-03").add_event(event);
                    if (sr0l04)
                        _counters.at("SR0L-04").add_event(event);
                    if (sr0l05)
                        _counters.at("SR0L-05").add_event(event);

                    // cout << "28. After the o lepton Signal Counting " << endl;
                }
                Nevent += 1;
                return;

            } // End run function

            virtual void
            collect_results()
            {
                // This data is used if not running ATLAS_FullLikes.
                add_result(SignalRegionData(_counters.at("SR1L-01"), 353., {349., 20.}));
                add_result(SignalRegionData(_counters.at("SR1L-02"), 428., {416., 18.}));
                add_result(SignalRegionData(_counters.at("SR1L-03"), 60., {64.9, 4.7}));
                add_result(SignalRegionData(_counters.at("SR1L-04"), 78., {78.2, 8.0}));
                add_result(SignalRegionData(_counters.at("SR1L-05"), 18., {14.4, 1.2}));

                add_result(SignalRegionData(_counters.at("SR0L-01"), 87., {85.5, 6.8}));
                add_result(SignalRegionData(_counters.at("SR0L-02"), 8., {6.7, 0.75}));
                add_result(SignalRegionData(_counters.at("SR0L-03"), 7., {7.8, 1.7}));
                add_result(SignalRegionData(_counters.at("SR0L-04"), 18., {21.6, 1.4}));
                add_result(SignalRegionData(_counters.at("SR0L-05"), 29., {28.8, 3.1}));

                COMMIT_CUTFLOWS;
                // Add cutflow data to the analysis results
                #ifdef CHECK_PLOT
                    double intgnt = _histo_Ntop->integral(); 
                    if (intgnt > 0) _histo_Ntop->scaleW(1.0 / intgnt); 
                    double intgnb = _histo_Nbjet->integral();
                    if (intgnb > 0) _histo_Nbjet->scaleW(1.0 / intgnb); 
                    double intgnh = _histo_NHiggs->integral(); 
                    if (intgnh > 0) _histo_NHiggs->scaleW(1.0 / intgnh); 
                    double intgnj = _histo_Njet->integral();
                    if (intgnj > 0) _histo_Njet->scaleW(1.0 / intgnj); 
                    double intmtb = _histo_mTBmin->integral();
                    if (intmtb > 0) _histo_mTBmin->scaleW(1.0 / intmtb);
                    double intme0 = _histo_meff_SR0L_01->integral();
                    if (intme0 > 0) _histo_meff_SR0L_01->scaleW(1.0 / intme0); 
                    double intme1 = _histo_meff_SR1L_03->integral();
                    if (intme1 > 0) _histo_meff_SR1L_03->scaleW(1.0 / intme1); 

                    std::vector<YODA::AnalysisObject *> histos;
                    histos.push_back(_histo_NHiggs);
                    histos.push_back(_histo_Njet);
                    histos.push_back(_histo_meff_SR1L_03);
                    histos.push_back(_histo_Nbjet);
                    histos.push_back(_histo_Ntop);
                    histos.push_back(_histo_meff_SR0L_01);
                    histos.push_back(_histo_mTBmin);

                    // del _histo_mTBmin;
                    YODA::WriterYODA::write("ATLAS_EXOT_2016_013.yoda", histos.begin(), histos.end());
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
        DEFINE_ANALYSIS_FACTORY(ATLAS_EXOT_2016_013)
    } // namespace ColliderBit
} // namespace Gambit {