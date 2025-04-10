///
///  \author Pengxuan Zhu (zhupx99@icloud.com)
///  \date 2024 Jun
///
///  *********************************************

// Based on
//  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/EXOT-2016-14/
//  - https://cds.cern.ch/record/2274216
//  - http://arxiv.org/abs/1707.03347
// Search for the pair production of heavy vector-like T and B quarks in pp collisions at s√= 13 TeV
//   primarily targeting the events of T quark decays to a W boson + b-quark

/*
  Note:
  1. No Identification selection level provide for electron and muon, so I just using the Loose selection criteria;
  2. Missing the electron track cut |d0|/|sigma(d0)| < 5 && |z0 sin(theta)| < 0.5 mm
*/

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "HEPUtils/FastJet.h"
#include "HEPUtils/Event.h"
#include "HEPUtils/Jet.h"
// #include "fastjet/Filter.hh"
#include <random>

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
#include "fastjet/contrib/EnergyCorrelator.hh"
// #include "gambit/contrib/fjcontrib-1.045/EnergyCorrelator/EnergyCorrelator.hh"
#else
#include "fjcore.hh"
#ifndef FJNS
#define FJNS fjcore
#endif
#endif

using namespace std;
// #define CHECK_CUTFLOW

class JetD2Threshold {
    private:
        std::vector<std::pair<double, double>> thresholds; // 存储 (p_T 上限, D2 阈值) 对

    public:
        JetD2Threshold() {
                    thresholds.emplace_back(300, 1.03);   // pT   < 300
                    thresholds.emplace_back(400, 1.10);   // 300  < pT <= 400
                    thresholds.emplace_back(500, 1.15);   // 400  < pT <= 500 
                    thresholds.emplace_back(600, 1.23);   // 500  < pT <= 600 
                    thresholds.emplace_back(700, 1.30);   // 600  < pT <= 700
                    thresholds.emplace_back(800, 1.38);   // 700  < pT <= 800
                    thresholds.emplace_back(900, 1.45);   // 800  < pT <= 900
                    thresholds.emplace_back(1000, 1.50);  // 900  < pT <= 1000
                    thresholds.emplace_back(1100, 1.58);  // 1000 < pT <= 1100
                    thresholds.emplace_back(1250, 1.70);  // 1100 < pT <= 1250
                    thresholds.emplace_back(1500, 1.80);  // 1250 < pT <= 1500
                    thresholds.emplace_back(1750, 2.00);  // 1500 < pT <= 1750
                    thresholds.emplace_back(2000, 2.57);  // 1750 < pT <= 2000
            }

    double getThreshold(double jet_pt) {
        for (const auto& threshold : thresholds) {
            if (jet_pt < threshold.first) {
                return threshold.second;
            }
        }
        return thresholds.back().second; 
    }
};

namespace Gambit
{
    namespace ColliderBit
    {
        

        class Analysis_ATLAS_EXOT_2016_014 : public Analysis
        {
            // protected:
            //     // Counters for the number of accepted events for each signal region
            //     std::map<string, EventCounter> _counters = {
            //         {"SR", EventCounter("SR")},
            //     };

        public:
            #ifdef CHECK_CUTFLOW
                Cutflows _cutflows;
            #endif

            static constexpr const char *detector = "ATLAS";


            
            double getThreshold(double jet_pt) {
                for (const auto& threshold : thresholds) {
                    if (jet_pt < threshold.first) {
                        return threshold.second;
                    }
                }
                return thresholds.back().second; // 如果 p_T 超过最高限制，使用最高阈值
            }

            Analysis_ATLAS_EXOT_2016_014()
            {
                DEFINE_SIGNAL_REGION("SR");

                set_analysis_name("ATLAS_EXOT_2016_014");
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
                        "DeltaM < 300 GeV"};

                    _cutflows.addCutflow("ATLAS_EXOT_2016_014", cutnames);

                    cout << _cutflows << endl;
                #endif
            }

            void run(const HEPUtils::Event *event)
            {
                // cout << "\n ============= \n Start Run new events " << endl;
                #ifdef CHECK_CUTFLOW
                    const double w = event->weight();
                    // cout << "Event weight ->" << w << endl;
                    _cutflows["ATLAS_EXOT_2016_014"].fillinit(w);
                    _cutflows["ATLAS_EXOT_2016_014"].fillnext(w);
                #endif

                // cout << "0. pass cutflow init" << endl;
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
                vector<const HEPUtils::Jet *> trimmedLargeRJets;
                vector<fastjet::PseudoJet> trimmedJets;
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
                const double beta = 1.0; 
                FJNS::Filter trimmer(fastjet::JetDefinition(fastjet::kt_algorithm, Rsub), fastjet::SelectorPtFractionMin(ptfrac));
                FJNS::contrib::EnergyCorrelator C2(2, beta, fastjet::contrib::EnergyCorrelator::pt_R);
                FJNS::contrib::EnergyCorrelator C3(3, beta, fastjet::contrib::EnergyCorrelator::pt_R);  

                std::random_device rd;
                std::mt19937 gen(rd()); 
                std::uniform_real_distribution<> dis(0.0, 1.0);


                // W-tagging from https://cds.cern.ch/record/2041461/files/ATL-PHYS-PUB-2015-033.pdf
                for (size_t i = 0; i < baselineLargeRJets.size(); ++i)
                {
                    // Obtain the FastJet PseudoJet objects;
                    const fastjet::PseudoJet &pseudojet = baselineLargeRJets.at(i)->pseudojet();
                    // Make sure there is constituents inside the jets
                    if (pseudojet.constituents().empty()) continue;
                    fastjet::PseudoJet trimmedJet = trimmer(pseudojet);
                    HEPUtils::Jet* hepUtilsJet = new HEPUtils::Jet(trimmedJet);

                    if (trimmedJet.pt() > 200 &&  abs(trimmedJet.eta() < 2.0)) { // Setting The pT lower limit
                        // Applying The W-jet Grooming


                        // Define Jet mass 
                        double jet_mass = trimmedJet.m();
                        if (jet_mass < 0) continue; // filter the negative mass situation 

                        // Calculate the Energy correlator function 
                        double C2_value = C2(trimmedJet);
                        double C3_value = C3(trimmedJet);
                        double D2_value = (C2_value > 0) ? C3_value / std::pow(C2_value, 3) : 0.0;
                        
                        JetD2Threshold d2Threshold;
                        double D2_upper = d2Threshold.getThreshold(trimmedJet.pt()); 

                        // W tagging 
                        if (std::abs(jet_mass - 80.4) < 15 && D2_value < D2_upper) {
                            
                            double randomNumber = dis(gen);
                            if (randomNumber < 0.5) {
                                trimmedLargeRJets.push_back(hepUtilsJet);
                            }
                        }
                    }
                }

                // Define the Energy Correlation Function of W-tagging 

                // cout << "3. There are " << trimmedLargeRJets.size() << " trimmed Large-R Jets" << endl; 

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
                vector<const HEPUtils::Jet *> signalWhad = trimmedLargeRJets;

                // Event Preselection
                bool presel = false;

                int n_leptons = signalLeptons.size();
                int n_jets = signalJets.size() + signalBjets.size();
                int n_bjets = signalBjets.size();
                int n_Whad = signalWhad.size();

                if (n_leptons == 1 && n_jets >= 3)
                {
#ifdef CHECK_CUTFLOW
                    _cutflows["ATLAS_EXOT_2016_014"].fill(2, true, event->weight());
#endif
                    if (n_Whad >= 1)
                    {
#ifdef CHECK_CUTFLOW
                        _cutflows["ATLAS_EXOT_2016_014"].fill(3, true, event->weight());
#endif
                        if (met >= 60)
                        {
#ifdef CHECK_CUTFLOW
                            _cutflows["ATLAS_EXOT_2016_014"].fill(4, true, event->weight());
#endif
                            if (n_bjets >= 1)
                            {
#ifdef CHECK_CUTFLOW
                                _cutflows["ATLAS_EXOT_2016_014"].fill(5, true, event->weight());
#endif
                                presel = true;
                            }
                        }
                    }
                }

                if (!presel)
                    return;
                // cout << "5. Pass preselection " << endl; 
                // TT reconstraction
                // Define Whad
                HEPUtils::Jet *signal_Whad = const_cast<HEPUtils::Jet *>(signalWhad[0]);
                double dm = signal_Whad->mom().m() - mW;
                if (n_Whad > 1)
                {
                    for (const HEPUtils::Jet *wcand : signalWhad)
                    {
                        double massdiff = wcand->mom().m() - mW;
                        if (massdiff < dm)
                        {
                            signal_Whad = const_cast<HEPUtils::Jet *>(wcand);
                            dm = massdiff;
                        }
                    }
                }

                // cout << "6. Whad candidate construct!" << endl; 

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
                // cout << "7. After pairing WbWb" << endl; 
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

#ifdef CHECK_CUTFLOW
                if (ST > 1800)
                {
                    _cutflows["ATLAS_EXOT_2016_014"].fill(6, true, event->weight());
                    if (dRvlep < 0.7)
                    {
                        _cutflows["ATLAS_EXOT_2016_014"].fill(7, true, event->weight());
                        if (abs(mTlep - mThad) < 300)
                        {
                            _cutflows["ATLAS_EXOT_2016_014"].fill(8, true, event->weight());
                        }
                    }
                }
#endif
                // cout << "8. Fill the signal region" << endl; 
                return; 

            } // End run function

            virtual void
            collect_results()
            {
                // This data is used if not running ATLAS_FullLikes.
                add_result(SignalRegionData(_counters.at("SR"), 58, {64.0, 9.0}));

                COMMIT_CUTFLOWS;

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

            std::vector<std::pair<double, double>> thresholds; // Save D2 thresHolds; Using the LookUP table method to get D2 upper limit; 



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
                double ETM2 = met_px * met_px + met_py * met_py; 

                double m_l = lep.m(); 

                double A = mW * mW - m_l * m_l + 2.0 * px_l * met_px + 2.0 * met_py * py_l; 
                double B = 2.0 * pz_l; 
                double C = -2.0 * E_l; 

                double discriminant = (A * A) * (C * C) + (B * B) * (C * C) * ETM2 - (C * C * C * C) * ETM2; 
                double denominator = (C * C) - (B * B); 

                std::vector<double> solutions;

                if (discriminant >= 0)
                {
                    double sqrt_discriminant = std::sqrt(discriminant);
                    solutions.push_back((A * B + sqrt_discriminant)/denominator);
                    solutions.push_back((A * B - sqrt_discriminant)/denominator);
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
        DEFINE_ANALYSIS_FACTORY(ATLAS_EXOT_2016_014)
    } // namespace ColliderBit
} // namespace Gambit {