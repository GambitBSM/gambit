///
///  \author Yang Zhang
///  \date 2019 May
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2021 Sep
///  \author Tore Klungland
///  \date 2026 Feb
///
///  *********************************************

// Based on https://arxiv.org/abs/1908.08215 and corresponding ATLAS analysis: Analysis_ATLAS_13TeV_2OSLEP_chargino_139invfb
// Search for electroweak production of charginos and sleptons decaying in final states with two leptons and missing transverse momentum in √s = 85 TeV p p collisions at FCC-hh

// NB: 
// Signal regions, background estimates under construction

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/FCChhEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    // This analysis class is a base class for two SR-specific analysis classes
    // defined further down:
    // - FCChh_85TeV_2OSLEP_chargino_binned_1000invfb
    // - FCChh_85TeV_2OSLEP_chargino_inclusive_1000invfb
    class Analysis_FCChh_85TeV_2OSLEP_chargino_1000invfb : public Analysis
    {

    protected:

      // Counters for the number of accepted events for each signal region
      std::map<string, EventCounter> _counters = {
        {"SR-SF-0J-150", EventCounter("SR-SF-0J-150")},
        {"SR-SF-0J-350", EventCounter("SR-SF-0J-350")},
        {"SR-SF-0J-150-250", EventCounter("SR-SF-0J-150-250")},
        {"SR-SF-0J-250-350", EventCounter("SR-SF-0J-250-350")},
        {"SR-SF-1J-150", EventCounter("SR-SF-1J-150")},
        {"SR-SF-1J-350", EventCounter("SR-SF-1J-350")},
        {"SR-SF-1J-150-250", EventCounter("SR-SF-1J-150-250")},
        {"SR-SF-1J-250-350", EventCounter("SR-SF-1J-250-350")},
      };

      std::map<string, EventCounter> _counters_bin = {
        {"SR-SF-0J-150-180", EventCounter("SR-SF-0J-150-180")},
        {"SR-SF-0J-180-220", EventCounter("SR-SF-0J-180-220")},
        {"SR-SF-0J-220-270", EventCounter("SR-SF-0J-220-270")},
        {"SR-SF-0J-270-330", EventCounter("SR-SF-0J-270-330")},
        {"SR-SF-0J-330-400", EventCounter("SR-SF-0J-330-400")},
        {"SR-SF-0J-400-480", EventCounter("SR-SF-0J-400-480")},
        {"SR-SF-0J-480-570", EventCounter("SR-SF-0J-480-570")},
        {"SR-SF-0J-570-670", EventCounter("SR-SF-0J-570-670")},
        {"SR-SF-0J-670", EventCounter("SR-SF-0J-670")},
        {"SR-SF-1J-150-180", EventCounter("SR-SF-1J-150-180")},
        {"SR-SF-1J-180-220", EventCounter("SR-SF-1J-180-220")},
        {"SR-SF-1J-220-270", EventCounter("SR-SF-1J-220-270")},
        {"SR-SF-1J-270-330", EventCounter("SR-SF-1J-270-330")},
        {"SR-SF-1J-330-400", EventCounter("SR-SF-1J-330-400")},
        {"SR-SF-1J-400-480", EventCounter("SR-SF-1J-400-480")},
        {"SR-SF-1J-480-570", EventCounter("SR-SF-1J-480-570")},
        {"SR-SF-1J-570-670", EventCounter("SR-SF-1J-570-670")},
        {"SR-SF-1J-670", EventCounter("SR-SF-1J-670")},
      };

      Cutflow _cutflow;

    public:

      // Required detector sim
      static constexpr const char* detector = "FCChh";

      Analysis_FCChh_85TeV_2OSLEP_chargino_1000invfb():
      _cutflow("FCC-hh 2-lep chargino-W 85 TeV", {"Two_OSSF_leptons", "pT_100_50", "b_jet_veto", "MET_150", "MET_significance_10", "n_j<=1", "m_ll_m_Z"})
      {

        set_analysis_name("FCChh_85TeV_2OSLEP_chargino_1000invfb");
        set_luminosity(1000);

      }

      // The following section copied from Analysis_ATLAS_1LEPStop_20invfb.cpp
      void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &lepvec, double DeltaRMax) {
        //Routine to do jet-lepton check
        //Discards jets if they are within DeltaRMax of a lepton

        vector<const HEPUtils::Jet*> Survivors;

        for(unsigned int itjet = 0; itjet < jetvec.size(); itjet++) {
        bool overlap = false;
          HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
          for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
            HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
            double dR;

            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(jetvec.at(itjet));
        }
        jetvec=Survivors;

        return;
      }

      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec) {
        //Routine to do lepton-jet check
        //Discards leptons if they are within dR of a jet as defined in analysis paper

        vector<const HEPUtils::Particle*> Survivors;

        for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
          bool overlap = false;
          HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
          for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            double dR;
            double DeltaRMax = std::min(0.4, 0.04 + 10 / lepmom.pT());
            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lepvec.at(itlep));
        }
        lepvec=Survivors;

        return;
      }


      struct ptComparison {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      double btag_eff(double pT,double abseta) {
        // b tagging efficiency, from https://cds.cern.ch/record/2717698/files/CERN-FCC-PHYS-2020-0003.pdf
        return (pT > 30 && pT < 15000) * ((abseta < 2.5) * 0.85 * (1. - pT/15.)
          + (abseta >= 2.5 && abseta < 4) * 0.64 * (1.-pT/15.));
      }

      double cmistag_eff(double pT, double abseta) {
        // c mistagging efficiency, from https://cds.cern.ch/record/2717698/files/CERN-FCC-PHYS-2020-0003.pdf
        return (pT > 30 && pT < 15000) * ((abseta < 2.5) * 0.05 * (1. - pT/15.)
          + (abseta >= 2.5 && abseta < 4) * 0.03 * (1.-pT/15.));
      }

      double lmistag_eff(double pT, double abseta) {
        // Light-quark mistagging efficiency, from https://cds.cern.ch/record/2717698/files/CERN-FCC-PHYS-2020-0003.pdf
        return (pT > 30 && pT < 15000) * ((abseta < 2.5) * 0.01 * (1. - pT/15.)
          + (abseta >= 2.5 && abseta < 4) * 0.0075 * (1.-pT/15.));
      }

      void run(const HEPUtils::Event* event)
      {
        _cutflow.fillinit();

        // Baseline objects
        // Electrons
        vector<const HEPUtils::Particle*> electrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10.
              && fabs(electron->eta()) < 3.)
            electrons.push_back(electron);
        }

        // Apply electron efficiency
        FCChh::applyElectronEff(electrons);

        // Muons
        vector<const HEPUtils::Particle*> muons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10.
              && fabs(muon->eta()) < 3.)
            muons.push_back(muon);
        }

        // Apply muon efficiency
        FCChh::applyMuonEff(muons);

        // Calculate missing energy with smeared momenta
        const std::vector<const HEPUtils::Particle*> visibles = event->visible_particles();
        HEPUtils::P4 pmiss;
        for (const HEPUtils::Particle* visible : visibles)
        {
          pmiss -= visible->mom();
        }
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          pmiss -= jet->mom();
        }
        double met = pmiss.pT();

        // Jets
        vector<const HEPUtils::Jet*> candJets;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04")) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 3.)
            candJets.push_back(jet);
        }

        // Overlap removal
        JetLeptonOverlapRemoval(candJets,electrons,0.2);
        LeptonJetOverlapRemoval(electrons,candJets);
        JetLeptonOverlapRemoval(candJets,muons,0.4);
        LeptonJetOverlapRemoval(muons,candJets);

        // Jets
        vector<const HEPUtils::Jet*> bJets;
        vector<const HEPUtils::Jet*> nonbJets;

        // Find b-jets
        double btag; double cmistag; double lmistag;
        double jetpT, jetabseta;
        for (const HEPUtils::Jet* jet : candJets) {
          jetpT = jet->pT();
          jetabseta = fabs(jet->eta());
          btag = btag_eff(jetpT, jetabseta);
          cmistag = cmistag_eff(jetpT, jetabseta);
          lmistag = lmistag_eff(jetpT, jetabseta);
          // Tag
          if( jet->btag() && random_bool(btag) ) bJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmistag) ) bJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(lmistag) ) bJets.push_back(jet);
          // Non b-jet
          else nonbJets.push_back(jet);
        }


        // Find signal leptons with pT > 20 GeV
        vector<const HEPUtils::Particle*> signalElectrons;
        for (const HEPUtils::Particle* electron : electrons) {
          if (electron->pT() > 50.) signalElectrons.push_back(electron);
        }
        vector<const HEPUtils::Particle*> signalMuons;
        for (const HEPUtils::Particle* muon : muons) {
          if (muon->pT() > 50.) signalMuons.push_back(muon);
        }

        // Signal leptons = electrons + muons
        vector<const HEPUtils::Particle*> signalLeptons;
        signalLeptons=signalElectrons;
        signalLeptons.insert(signalLeptons.end(),signalMuons.begin(),signalMuons.end());
        sort(signalLeptons.begin(),signalLeptons.end(),comparePt);


        // Two exactly opposite-sign, same-flavor leptons
        if (signalLeptons.size() != 2) return;
        if (signalLeptons[0]->pid()*signalLeptons[1]->pid()>0) return;
        bool flag_SF = signalLeptons[0]->pid() + signalLeptons[1]->pid() == 0;
        if(!flag_SF) return;
        _cutflow.fill(1);


        // Hardest lepton pT >= 100 GeV
        if(signalLeptons[0]->pT() < 100. && signalLeptons[1]->pT() < 100.) return;
        _cutflow.fill(2);

        // b-jet veto
        if (bJets.size()>0) return;
        _cutflow.fill(3);

        // MET>110 GeV
        if (met<150) return;
        _cutflow.fill(4);

        // The missing transverse momentum significance >10
        // TODO Use event-based MET significance instead of object-based significance
        // https://cds.cern.ch/record/2630948/files/ATLAS-CONF-2018-038.pdf
        double met_sig=met/sqrt(met);
        if (met_sig<10) return;
        _cutflow.fill(5);

        // n_non_b_tagged_jets <= 1
        if (nonbJets.size()>1) return;
        _cutflow.fill(6);

        // Same flavour; mll >= mZ+20GeV
        double mll=(signalLeptons[0]->mom()+signalLeptons[1]->mom()).m();
        if (flag_SF) {
            if (mll<111.2) return ;
        }
        _cutflow.fill(7);

        // Mt2
        double pLep1[3] = {signalLeptons[0]->mass(), signalLeptons[0]->mom().px(), signalLeptons[0]->mom().py()};
        double pLep2[3] = {signalLeptons[1]->mass(), signalLeptons[1]->mom().px(), signalLeptons[1]->mom().py()};
        double pMiss[3] = {0., pmiss.px(), pmiss.py() };
        mt2_bisect::mt2 mt2_calc;
        mt2_calc.set_momenta(pLep1,pLep2,pMiss);
        mt2_calc.set_mn(0.0);
        double mT2 = mt2_calc.get_mt2();

        if (flag_SF) {
            if (nonbJets.size()==0){

                if (mT2>150)             _counters.at("SR-SF-0J-150").add_event(event);
                if (mT2>350)             _counters.at("SR-SF-0J-350").add_event(event);
                if (mT2>150 and mT2<250) _counters.at("SR-SF-0J-150-250").add_event(event);
                if (mT2>250 and mT2<350) _counters.at("SR-SF-0J-250-350").add_event(event);
                // binned SRs
                if (mT2>150 and mT2<180) _counters_bin.at("SR-SF-0J-150-180").add_event(event);
                if (mT2>180 and mT2<220) _counters_bin.at("SR-SF-0J-180-220").add_event(event);
                if (mT2>220 and mT2<270) _counters_bin.at("SR-SF-0J-220-270").add_event(event);
                if (mT2>270 and mT2<330) _counters_bin.at("SR-SF-0J-270-330").add_event(event);
                if (mT2>330 and mT2<400) _counters_bin.at("SR-SF-0J-330-400").add_event(event);
                if (mT2>400 and mT2<480) _counters_bin.at("SR-SF-0J-400-480").add_event(event);
                if (mT2>480 and mT2<570) _counters_bin.at("SR-SF-0J-480-570").add_event(event);
                if (mT2>570 and mT2<670) _counters_bin.at("SR-SF-0J-570-670").add_event(event);
                if (mT2>670            ) _counters_bin.at("SR-SF-0J-670").add_event(event);
            } else {

                if (mT2>150)             _counters.at("SR-SF-1J-150").add_event(event);
                if (mT2>350)             _counters.at("SR-SF-1J-350").add_event(event);
                if (mT2>150 and mT2<250) _counters.at("SR-SF-1J-150-250").add_event(event);
                if (mT2>250 and mT2<350) _counters.at("SR-SF-1J-250-350").add_event(event);
                // binned SRs
                if (mT2>150 and mT2<180) _counters_bin.at("SR-SF-1J-150-180").add_event(event);
                if (mT2>180 and mT2<220) _counters_bin.at("SR-SF-1J-180-220").add_event(event);
                if (mT2>220 and mT2<270) _counters_bin.at("SR-SF-1J-220-270").add_event(event);
                if (mT2>270 and mT2<330) _counters_bin.at("SR-SF-1J-270-330").add_event(event);
                if (mT2>330 and mT2<400) _counters_bin.at("SR-SF-1J-330-400").add_event(event);
                if (mT2>400 and mT2<480) _counters_bin.at("SR-SF-1J-400-480").add_event(event);
                if (mT2>480 and mT2<570) _counters_bin.at("SR-SF-1J-480-570").add_event(event);
                if (mT2>570 and mT2<670) _counters_bin.at("SR-SF-1J-570-670").add_event(event);
                if (mT2>670            ) _counters_bin.at("SR-SF-1J-670").add_event(event);
            }
        } else {
            //
        }

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_FCChh_85TeV_2OSLEP_chargino_1000invfb* specificOther
                = dynamic_cast<const Analysis_FCChh_85TeV_2OSLEP_chargino_1000invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

        for (auto& pair : _counters_bin) { pair.second += specificOther->_counters_bin.at(pair.first); }

      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results() {

        #ifdef CHECK_CUTFLOW
        cout << _cutflow << endl;
        for (auto& el : _counters) {
            cout << el.first << "\t" << _counters.at(el.first).sum() << endl;
        }
        for (auto& el : _counters_bin) {
            cout << el.first << "\t" << _counters_bin.at(el.first).sum() << endl;
        }
        #endif

        add_result(SignalRegionData(_counters.at("SR-SF-0J-150"), 449., {449., 228.}));
        add_result(SignalRegionData(_counters.at("SR-SF-0J-350"), 15., {15., 10.}));
        add_result(SignalRegionData(_counters.at("SR-SF-0J-150-250"), 392., {392., 227.}));
        add_result(SignalRegionData(_counters.at("SR-SF-0J-250-350"), 42., {42., 20.}));

        add_result(SignalRegionData(_counters.at("SR-SF-1J-150"), 5573., {5573., 905.}));
        add_result(SignalRegionData(_counters.at("SR-SF-1J-350"), 100., {100., 27.}));
        add_result(SignalRegionData(_counters.at("SR-SF-1J-150-250"), 5107., {5107., 903.}));
        add_result(SignalRegionData(_counters.at("SR-SF-1J-250-350"), 365., {365., 59.}));

        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-150-180"), 310. , { 310. , 225. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-180-220"), 61. , { 61. , 24. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-220-270"), 40. , { 40. , 20. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-270-330"), 11. , { 11. , 10. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-330-400"), 22. , { 22. , 14. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-400-480"), 3. , { 3.1 , 1.5 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-480-570"), 1. , { 0.90 , 0.75 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-570-670"), 0. , { 0.08 , 0.08 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-670"), 0. , { 0.20 , 0.12 }));

        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-150-180"), 2802. , { 2802. , 677. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-180-220"), 1840. , { 1840. , 552. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-220-270"), 571. , { 571. , 231. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-270-330"), 218. , { 218. , 45. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-330-400"), 86. , { 85.8 , 28. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-400-480"), 30. , { 30. , 14.2 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-480-570"), 15. , { 15.08 , 10.05 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-570-670"), 4. , { 4.43 , 1.67 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-670"), 6. , { 5.68 , 1.84 }));
      }


    protected:
      void analysis_specific_reset() {
        for (auto& pair : _counters) { pair.second.reset(); }
        for (auto& pair : _counters_bin) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(FCChh_85TeV_2OSLEP_chargino_1000invfb)


    //
    // Derived analysis class for the 2Lep0Jets SRs
    //
    class Analysis_FCChh_85TeV_2OSLEP_chargino_inclusive_1000invfb : public Analysis_FCChh_85TeV_2OSLEP_chargino_1000invfb {

    public:
      Analysis_FCChh_85TeV_2OSLEP_chargino_inclusive_1000invfb() {
        set_analysis_name("FCChh_85TeV_2OSLEP_chargino_inclusive_1000invfb");
      }

      virtual void collect_results() {

        add_result(SignalRegionData(_counters.at("SR-SF-0J-150"), 449., {449., 228.}));
        add_result(SignalRegionData(_counters.at("SR-SF-0J-350"), 15., {15., 10.}));
        add_result(SignalRegionData(_counters.at("SR-SF-0J-150-250"), 392., {392., 227.}));
        add_result(SignalRegionData(_counters.at("SR-SF-0J-250-350"), 42., {42., 20.}));

        add_result(SignalRegionData(_counters.at("SR-SF-1J-150"), 5573., {5573., 905.}));
        add_result(SignalRegionData(_counters.at("SR-SF-1J-350"), 100., {100., 27.}));
        add_result(SignalRegionData(_counters.at("SR-SF-1J-150-250"), 5107., {5107., 903.}));
        add_result(SignalRegionData(_counters.at("SR-SF-1J-250-350"), 365., {365., 59.}));

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(FCChh_85TeV_2OSLEP_chargino_inclusive_1000invfb)

    //
    // Derived analysis class for the 3Lep SRs
    //
    class Analysis_FCChh_85TeV_2OSLEP_chargino_binned_1000invfb : public Analysis_FCChh_85TeV_2OSLEP_chargino_1000invfb {

    public:
      Analysis_FCChh_85TeV_2OSLEP_chargino_binned_1000invfb() {
        set_analysis_name("FCChh_85TeV_2OSLEP_chargino_binned_1000invfb");
      }

      virtual void collect_results() {

        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-150-180"), 310. , { 310. , 225. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-180-220"), 61. , { 61. , 24. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-220-270"), 40. , { 40. , 20. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-270-330"), 11. , { 11. , 10. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-330-400"), 22. , { 22. , 14. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-400-480"), 3. , { 3.1 , 1.5 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-480-570"), 1. , { 0.90 , 0.75 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-570-670"), 0. , { 0.08 , 0.08 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-0J-670"), 0. , { 0.20 , 0.12 }));

        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-150-180"), 2802. , { 2802. , 677. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-180-220"), 1840. , { 1840. , 552. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-220-270"), 571. , { 571. , 231. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-270-330"), 218. , { 218. , 45. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-330-400"), 86. , { 85.8 , 28. }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-400-480"), 30. , { 30. , 14.2 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-480-570"), 15. , { 15.08 , 10.05 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-570-670"), 4. , { 4.43 , 1.67 }));
        add_result(SignalRegionData(_counters_bin.at("SR-SF-1J-670"), 6. , { 5.68 , 1.84 }));

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(FCChh_85TeV_2OSLEP_chargino_binned_1000invfb)


  }
}
