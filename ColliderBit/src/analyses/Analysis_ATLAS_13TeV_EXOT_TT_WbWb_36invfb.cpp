///
///  \author Pengxuan Zhu (zhupx99@icloud.com)
///  \date 2024 Jun
///
///  *********************************************

// Based on
//  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/EXOT-2016-14/
//  - https://cds.cern.ch/record/2274216
//  - http://arxiv.org/abs/1707.03347
//
// Search for the pair production of heavy vector-like T and B quarks in pp collisions at s√= 13 TeV
//   primarily targeting the events of T quark decays to a W boson + b-quark

/*
  Note:
  1. No Identification selection level provide for electron and muon, so I just using the Loose selection criteria;
  2. Missing the electron track cut |d0|/|sigma(d0)| < 5 && |z0 sin(theta)| < 0.5 mm
*/

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "HEPUtils/FastJet.h"
// #include "HEPUtils/Cutflow.h"
#include "HEPUtils/Event.h"
#include "HEPUtils/Jet.h"
// #include "fastjet/Filter.hh"

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
# define CHECK_CUTFLOW

namespace Gambit
{
    namespace ColliderBit
    {

        class Analysis_ATLAS_13TeV_EXOT_TT_WbWb_36invfb : public Analysis
        {
        protected:
            // Counters for the number of accepted events for each signal region
            std::map<string, EventCounter> _counters = {
                {"SR", EventCounter("SR")},
            };
            //   Cutflow _cutflow;

        public:
            // Require detector sim
            #ifdef CHECK_CUTFLOW
                Cutflows _cfs; 
            #endif 

            static constexpr const char *detector = "ATLAS";

            Analysis_ATLAS_13TeV_EXOT_TT_WbWb_36invfb()
            {
                set_analysis_name("ATLAS_13TeV_EXOT_TT_WbWb_36invfb");
                set_luminosity(36.1);

                #ifdef CHECK_CUTFLOW
                    cout << "Starting run Analysis \n booking Cutflows" << endl; 
                    // Booking Cutflows 
                    const vector<string> cutnames = {
                        "No Cut", 
                        "Base Selection", 
                        ">= 1 Whad cand.",
                        "ETmiss >= 60 GeV",
                        ">= 1 b-tagged jet",
                        "S_T >= 1800 GeV",
                        "DeltaR(lep, v) <= 0.7",
                        "DeltaM < 300 GeV"                    
                    }
                    _cfs.addCutflow("ATLAS_13TeV_EXOT_TT_WbWb_36invfb-SR", cutnames); 
                #endif
            }

            void run(const HEPUtils::Event *event)
            {
                #ifdef CHECK_CUTFLOW
                    _cfs['ATLAS_13TeV_EXOT_TT_WbWb_36invfb-SR'].fillinit(event->weight()); 
                    _cfs['ATLAS_13TeV_EXOT_TT_WbWb_36invfb-SR'].fillnext(event->weight()); 
                #endif

                // Define the missing momentum & MET
                HEPUtils::P4 pmiss = event->missingmom();
                const double met = event->met();

                // Baseline lepton objects
                vector<const HEPUtils::Particle *> baselineElectrons, baselineMuons;
                for (const HEPUtils::Particle *electron : event->electrons())
                {
                    if (electron->pT() > 30 && electron->abseta() < 2.47 && (electron->abseta() < 1.37 || electron->abseta() > 1.52))
                    {
                        // bool passIsolation = LeptonIsolation(electron, event);
                        // if (passIsolation)
                        // {
                            baselineElectrons.push_back(electron);
                        // }
                    }
                }
                for (const HEPUtils::Particle *muon : event->muons())
                {
                    if (muon->pT() > 30 && muon->abseta() < 2.5 && (muon->abseta() < 1.37 || muon->abseta() > 1.52))
                    {
                        // bool passIsolation = LeptonIsolation(muon, event);
                        // if (passIsolation)
                        // {
                            baselineMuons.push_back(muon);
                        // }
                    }
                }

                // Missing the Lepton isolation requirement

                // Apply electron efficiency
                // Electron efficiency is defined in ATLAS-CONF-2016-024, susperseded by arXiv:1902.04655.
                applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_VeryLoose"));
                // ATLAS::applyElectronEff(baselineElectrons);
                // Muon efficiency is defined in CERN-EP-2016-033, arXiv:1603.05598. PREF-2015-10
                // Due to the muon pT in this work is required to be larger than 30 GeV, choosing the full Run-II effcicency instead.
                applyEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Loose"));
                // ATLAS::applyMuonEff(baselineMuons); 
                // Jets
                vector<const HEPUtils::Jet *> baselineSmallRJets;
                vector<const HEPUtils::Jet *> baselineLargeRJets;
                vector<const HEPUtils::Jet *> trimmedLargeRJets;

                vector<const HEPUtils::Jet *> bJets;
                vector<const HEPUtils::Jet *> nonbJets;

                // Define smallR-jets and b-jets
                const double btageff = 0.77;
                const double cmistag = 1.0 / 6.0;
                const double misstag = 1.0 / 130.0;
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

                for (const HEPUtils::Jet *jet : event->jets("antikt_R1"))
                {
                    baselineLargeRJets.push_back(jet);
                }
                // Define trimming parameter, needs the checks

                // Two different way to trimming Large R-Jets
                // Method 1:
                // ============================================================== //
                // const double Rsub = 0.2;
                // const double ptfrac = 0.05;

                // for (const auto &jet : baselineLargeRJets)
                // {
                //   FJNS::PseudoJet fj_jet(jet->px(), jet->py(), jet->pz(), jet->E());
                //   FJNS::JetDefinition jet_def(FJNS::kt_algorithm, Rsub);
                //   FJNS::ClusterSequence cs(fj_jet.constituents(), jet_def);
                //   std::vector<FJNS::PseudoJet> trimmed_subjets;

                //   for (const auto &subjet : cs.inclusive_jets())
                //   {
                //     if (subjet.pt() > ptfrac * fj_jet.pt())
                //     {
                //       trimmed_subjets.push_back(subjet);
                //     }
                //   }
                //   FJNS::PseudoJet trimmed_jet = fastjet::join(trimmed_subjets);
                //   HEPUtils::P4 trimmed_p4(trimmed_jet.px(), trimmed_jet.py(), trimmed_jet.pz(), trimmed_jet.E());
                //   HEPUtils::Jet *hep_trimmed_jet = new HEPUtils::Jet(trimmed_p4);
                //   trimmedLargeRJets.push_back(hep_trimmed_jet);
                // }
                // ============================================================== //

                // Method 2:
                const double Rsub = 0.2;
                const double ptfrac = 0.05;
                fastjet::Filter trimmer(fastjet::JetDefinition(fastjet::kt_algorithm, Rsub), fastjet::SelectorPtFractionMin(ptfrac));

                for (const auto &jet : baselineLargeRJets)
                {
                    FJNS::PseudoJet fj_jet(jet->mom().px(), jet->mom().py(), jet->mom().pz(), jet->mom().E());
                    FJNS::PseudoJet trimmed_jet = trimmer(fj_jet);
                    HEPUtils::P4 trimmed_p4(trimmed_jet.px(), trimmed_jet.py(), trimmed_jet.pz(), trimmed_jet.E());
                    HEPUtils::Jet *trimmed_largeRjet = new HEPUtils::Jet(trimmed_p4);
                    if (trimmed_largeRjet->pT() > 200 && trimmed_largeRjet->abseta() < 2.5)
                    {
                        trimmedLargeRJets.push_back(trimmed_largeRjet);
                    }
                }

                // Removing Overlaping
                // 1) Remove trimmed-LargeR jets with b-tagged small-R jets within DeltaR < 1.0.
                removeOverlap(trimmedLargeRJets, bJets, 1.0);
                // 2) Remove smallR-jet within DeltaR < 0.2 of electron
                removeOverlap(bJets, baselineElectrons, 0.2);
                removeOverlap(nonbJets, baselineElectrons, 0.2);
                // 3) then Remove electron within 0.2 < DeltaR < 0.4 of smallR-jet
                removeOverlap(baselineElectrons, bJets, 0.4);
                removeOverlap(baselineElectrons, nonbJets, 0.4);
                // 4) Remove smallR-jet within DeltaR < 0.2 of muon
                removeOverlap(bJets, baselineMuons, 0.2);
                removeOverlap(nonbJets, baselineMuons, 0.2);
                // 5) then Remove muon within 0.2 < DeltaR < 0.4 of smallR-jet
                removeOverlap(baselineMuons, bJets, 0.4);
                removeOverlap(baselineMuons, nonbJets, 0.4);
                // 6) Remove largeR jets within DeltaR < 1 of electrons and muons
                removeOverlap(trimmedLargeRJets, baselineElectrons, 1.0);
                removeOverlap(trimmedLargeRJets, baselineMuons, 1.0);

                // Define Signal objects;
                vector<const HEPUtils::Jet *> signalJets = nonbJets;
                vector<const HEPUtils::Jet *> signalBjets = bJets;
                vector<const HEPUtils::Particle *> signalLeptons = baselineElectrons;
                // vector<const HEPUtils::Particle*> signalMuons = baselineMuons;
                for (const HEPUtils::Particle *muon : baselineMuons)
                {
                    signalLeptons.push_back(muon);
                }
                vector<const HEPUtils::Jet *> signalWhad = trimmedLargeRJets;

                // Event Preselection
                bool presel = false;

                int n_leptons = signalLeptons.size();
                int n_jets = signalJets.size() + signalBjets.size();
                int n_bjets = signalBjets.size();
                int n_Whad = signalWhad.size();

                if (n_leptons == 1 && n_jets >= 3 && n_bjets >= 1 && n_Whad >= 1 && met >= 60)
                {
                    presel = true;
                    #ifdef CHECK_CUTFLOW
                        _cfs['ATLAS_13TeV_EXOT_TT_WbWb_36invfb-SR'].fillnext(event->weight());
                    #endif
                }
                if (!presel)
                    return;

                // TT reconstraction
                // Define Whad
                HEPUtils::Jet *signal_Whad = nullptr;
                double dm = 99999.0;
                if (n_Whad > 1)
                {
                    for (const HEPUtils::Jet *wcand : signalWhad)
                    {
                        double massdiff = wcand->mom().m() - mW;
                        if (massdiff < dm)
                        {
                            signal_Whad = const_cast<HEPUtils::Jet *>(wcand); // 使用const_cast将const指针转换为非const指针
                            dm = massdiff;
                        }
                    }
                }

                // Deine Wlep
                // Solving the four-momentum of the neutrino analytically.
                double met_px = pmiss.px();
                double met_py = pmiss.py();
                std::vector<double> pz_nu_values = calculate_pvz(signalLeptons.at(0)->mom(), met_px, met_py);
                double met_pz = solute_pvZ(pz_nu_values);
                double met_e = std::sqrt(met_px * met_px + met_py * met_py + met_pz * met_pz);
                HEPUtils::P4 pv4(met_px, met_py, met_pz, met_e);
                // HEPUtils::Particle Wlep(pv4 + signalLeptons.at(0)->mom(), 23);
                HEPUtils::Particle *Wlep = new HEPUtils::Particle(pv4 + signalLeptons.at(0)->mom(), 23);

                // Define combination of WbWb
                HEPUtils::P4 p4bJethad;
                HEPUtils::P4 p4bJetlep;
                if (n_bjets >= 2)
                {
                    double mTcand11 = (signalBjets.at(0)->mom() + signal_Whad->mom()).m();
                    double mTcand12 = (signalBjets.at(0)->mom() + Wlep->mom()).m();
                    double mTcand21 = (signalBjets.at(1)->mom() + signal_Whad->mom()).m();
                    double mTcand22 = (signalBjets.at(1)->mom() + Wlep->mom()).m();

                    if (abs(mTcand11 - mTcand22) < abs(mTcand12 - mTcand21))
                    {
                        p4bJethad = signalBjets.at(0)->mom();
                        p4bJetlep = signalBjets.at(1)->mom();
                    }
                    else
                    {
                        p4bJethad = signalBjets.at(1)->mom();
                        p4bJetlep = signalBjets.at(0)->mom();
                    }
                }
                else if (n_bjets == 1)
                {
                    double dm = 999999.0;
                    // bjet paired with Wlep
                    for (const HEPUtils::Jet *bjet : signalJets)
                    {
                        double mTl = (signalBjets.at(0)->mom() + Wlep->mom()).m();
                        double mTh = (bjet->mom() + signal_Whad->mom()).m();
                        if (abs(mTl - mTh) < dm)
                        {
                            dm = abs(mTl - mTh);
                            p4bJethad = bjet->mom();
                            p4bJetlep = signalBjets.at(0)->mom();
                        }
                    }
                    // bjet paired with Whad
                    for (const HEPUtils::Jet *bjet : signalJets)
                    {
                        double mTl = (bjet->mom() + Wlep->mom()).m();
                        double mTh = (signalBjets.at(0)->mom() + signal_Whad->mom()).m();
                        if (abs(mTl - mTh) < dm)
                        {
                            dm = abs(mTl - mTh);
                            p4bJethad = signalBjets.at(0)->mom();
                            p4bJetlep = bjet->mom();
                        }
                    }
                }

                // Define statistical variables
                const double mTlep = (p4bJetlep + Wlep->mom()).m();
                const double mThad = (p4bJethad + signal_Whad->mom()).m();
                double ST = met + signalLeptons.at(0)->pT();
                // for (vector<const HEPUtils::Jet *> jet : signalBjets)
                for (const HEPUtils::Jet *jet : signalBjets)
                {
                    ST += jet->pT();
                }
                // for (vector<const HEPUtils::Jet *> jet : signalJets)
                for (const HEPUtils::Jet *jet : signalJets)
                {
                    ST += jet->pT();
                }
                const double dRvlep = signalLeptons.at(0)->mom().deltaR_eta(pv4);

                // Define the Signal Region
                if (dRvlep < 0.7 && ST > 1800 && abs(mTlep - mThad) < 300)
                {
                    _counters.at("SR").add_event(event);
                }

            } // End run function

            // void combine(const Analysis *other)
            // {
            //     const Analysis_ATLAS_13TeV_EXOT_TT_WbWb_36invfb *specificOther = dynamic_cast<const Analysis_ATLAS_13TeV_EXOT_TT_WbWb_36invfb *>(other);

            //     for (auto &pair : _counters)
            //     {
            //         pair.second += specificOther->_counters.at(pair.first);
            //     }
            // }

            void collect_results()
            {
                // This data is used if not running ATLAS_FullLikes.
                add_result(SignalRegionData(_counters.at("SR"), 58, {64.0, 9.0}));
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

        private:
            const double mW = 80.4;

            // electron isolation requirement
            // bool LeptonIsolation(const HEPUtils::Particle &lepton, const HEPUtils::Event *event)
            // {
            //     double IR = 0.0;
            //     double Rcut = std::min(10.0 / lepton.pT(), 0.2);
            //     for (const auto &track : event->tracks())
            //     {
            //         double dR = lepton.mom().deltaR_eta(track->mom());
            //         if (dR < Rcut)
            //         {
            //             IR += track->pT();
            //         }
            //     }
            //     return IR < 0.06 * lepton.pT();
            // }

            std::vector<double> calculate_pvz(const HEPUtils::P4 &lep, double met_px, double met_py)
            {
                double px_l = lep.px();
                double py_l = lep.py();
                double pz_l = lep.pz();
                double E_l = lep.E();
                double E_T_miss = std::sqrt(met_px * met_px + met_py * met_py);

                double mu2 = 0.5 * mW * mW + met_px * px_l + met_py * py_l;

                double A = mu2 * pz_l;
                double B = mu2 * mu2 * pz_l * pz_l;
                double C = E_l * E_l - pz_l * pz_l;
                double D = E_l * E_l * E_T_miss * E_T_miss - mu2;

                double discriminant = (B / (C * C)) - (D / C);

                std::vector<double> solutions;

                if (discriminant >= 0)
                {
                    double sqrt_discriminant = std::sqrt(discriminant);
                    solutions.push_back(A / C + sqrt_discriminant);
                    solutions.push_back(A / C - sqrt_discriminant);
                }

                return solutions;
            }

            double solute_pvZ(const std::vector<double> &solutions)
            {
                if (solutions.empty())
                    return 0.0;
                return (std::abs(solutions[0]) < std::abs(solutions[1])) ? solutions[0] : solutions[1];
            }
        };
        DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_EXOT_TT_WbWb_36invfb)
    } // namespace ColliderBit
} // namespace Gambit {
