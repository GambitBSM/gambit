// -*- C++ -*-
///
///  \author Ida-Marie Johansson
///  \date 2023 November
///  
///  *********************************************

/// based on https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2019-22/
/// arXiv:2305.09322
#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <numeric>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
#include "METSignificance/METSignificance.hpp"

using namespace std;

namespace Gambit 
{
  namespace ColliderBit 
  {
    static bool SSLeptons(vector<const HEPUtils::Particle*> leptons){
      bool samesign;
      if (leptons.size()< 2){samesign=false;}
      else if (leptons.size() == 2){
        samesign = (leptons.at(0)->pid()*leptons.at(1)->pid()) > 0;
      }
      else if (leptons.size()>3){samesign=true;}
      return samesign;
    }

    class Analysis_ATLAS_13TeV_2OR3LEP_139invfb : public Analysis 
    {
    protected:
      
      Cutflows _cutflows;

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";


      Analysis_ATLAS_13TeV_2OR3LEP_139invfb() 
      {
        set_analysis_name("ATLAS_13TeV_2OR3LEP_139invfb");
        set_luminosity(139);

        //Defining signal regions
        // wh
        DEFINE_SIGNAL_REGION("SRWh-high-mt2-ee-1",   "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 >= 80 GeV",  "met sig >= 7", "met: [75, 125) GeV",  "type ee")
        DEFINE_SIGNAL_REGION("SRWh-high-mt2-ee-2",   "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 >= 80 GeV",  "met sig >= 7", "met: [125,175) GeV",  "type ee")
        DEFINE_SIGNAL_REGION("SRWh-high-mt2-ee-3",   "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 >= 80 GeV",  "met sig >= 7", "met >= 175 GeV",      "type ee")
        DEFINE_SIGNAL_REGION("SRWh-high-mt2-emu-1",  "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 >= 80 GeV",  "met sig >= 7", "met: [75, 125) GeV",  "type emu")
        DEFINE_SIGNAL_REGION("SRWh-high-mt2-emu-2",  "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 >= 80 GeV",  "met sig >= 7", "met: [125, 175) GeV", "type emu")
        DEFINE_SIGNAL_REGION("SRWh-high-mt2-emu-3",  "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 >= 80 GeV",  "met sig >= 7", "met >= 175 GeV",      "type emu")
        DEFINE_SIGNAL_REGION("SRWh-high-mt2-mumu-1", "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 >= 80 GeV",  "met sig >= 7", "met: [75, 125) GeV",  "type mumu")
        DEFINE_SIGNAL_REGION("SRWh-high-mt2-mumu-2", "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 >= 80 GeV",  "met sig >= 7", "met: [125, 175) GeV", "type mumu")
        DEFINE_SIGNAL_REGION("SRWh-high-mt2-mumu-3", "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 >= 80 GeV",  "met sig >= 7", "met >= 175 GeV",      "type mumu")

        DEFINE_SIGNAL_REGION("SRWh-low-mt2-ee",      "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 < 80 GeV", "mtmin >= 100 GeV", "met sig >= 6", "type ee")
        DEFINE_SIGNAL_REGION("SRWh-low-mt2-emu",     "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 < 80 GeV", "mtmin >= 100 GeV", "met sig >= 6", "type emu")
        DEFINE_SIGNAL_REGION("SRWh-low-mt2-mumu",    "n jets (pt>25) >= 1", "Nsig >= 2", "pt(l) >= 25GeV", "Nsig = 2", "same-sign", "n bjets = 0", "met >= 50", "mjj < 350 GeV", "mt2 < 80 GeV", "mtmin >= 100 GeV", "met sig >= 6", "type mumu")

        //wz
        // DEFINE_SIGNAL_REGION("SRWZ-high-mt2-1", "n jets >= 1", "Nsig(l) >= 2 && Nbl(l) >= 2", "same-sign", "Nbl(l)=2", "Nsig(l)==2", "pt(l) >= 25GeV", "n jets (pt>25) >= 1", "n bjets = 0", "mjj <= 350 GeV", "mt2 >= 100 GeV",  "mtmin >= 100 GeV", "met >= 100 GeV", "MET sig: [0,10]", "spread >= 2.2")
        // DEFINE_SIGNAL_REGION("SRWZ-high-mt2-2", "n jets >= 1", "Nsig(l) >= 2 && Nbl(l) >= 2", "same-sign", "Nbl(l)=2", "Nsig(l)==2", "pt(l) >= 25GeV", "n jets (pt>25) >= 1", "n bjets = 0", "mjj <= 350 GeV", "mt2 >= 100 GeV",  "mtmin >= 100 GeV", "met >= 100 GeV", "MET sig: [10,13]")
        // DEFINE_SIGNAL_REGION("SRWZ-high-mt2-3", "n jets >= 1", "Nsig(l) >= 2 && Nbl(l) >= 2", "same-sign", "Nbl(l)=2", "Nsig(l)==2", "pt(l) >= 25GeV", "n jets (pt>25) >= 1", "n bjets = 0", "mjj <= 350 GeV", "mt2 >= 100 GeV",  "mtmin >= 100 GeV", "met >= 100 GeV", "MET sig >= 13",   "dR_ll >= 1")
        // DEFINE_SIGNAL_REGION("SRWZ-low-mt2",    "n jets >= 1", "Nsig(l) >= 2 && Nbl(l) >= 2", "same-sign", "Nbl(l)=2", "Nsig(l)==2", "pt(l) >= 25GeV", "n jets (pt>25) >= 1", "n bjets = 0", "mjj <= 350 GeV", "mt2 <= 100 GeV",  "mtmin >= 130 GeV", "met >= 140 GeV", "meff <= 600 GeV", "dR_ll <= 3")

        // // bRPV
        // DEFINE_SIGNAL_REGION("SRbRPV-2l-SS", "pt >= 20GeV", "n jets (> 25GeV) >= 1", "Nsig = 2", "charge = same-sign", "mt2 >= 60 GeV" , "met >= 100 GeV", "n bjets = 0", "njets (>40 GeV) <= 4")
        // DEFINE_SIGNAL_REGION("SRbRPV-3l",    "pt >= 20GeV", "n jets (> 25GeV) >= 1", "Nsig = 3", "mt2 >= 80 GeV" , "met >= 120 GeV", "meff >= 350 GeV", "mee,mmumu notin [81,101] GeV")


        // //UDD
        // DEFINE_SIGNAL_REGION("SRRPV-2l1b-L", "Nbl=2", "Nsig = 2", "charge = same-sign", "pt > 25GeV", "n jets (> 25GeV) >= 1", "n bjets = 1",  "sum pt(l) >= 100" , "met >= 100 GeV", "njets (>20 GeV) <= 2",     "sum pt_bjet / sum pt jet >= 0.7",  "sum pt jet >= 120GeV", "dR(l_1, jet)min <= 1.2", "dRll>=2.0")
        // DEFINE_SIGNAL_REGION("SRRPV-2l1b-M", "Nbl=2", "Nsig = 2", "charge = same-sign", "pt > 25GeV", "n jets (> 25GeV) >= 1", "n bjets = 1",  "sum pt(l) >= 100" , "met >= 50 GeV",  "njets (>20 GeV) = 2 or 3", "sum pt_bjet / sum pt jet >= 0.45", "sum pt jet >= 400GeV", "dR(l_1, jet)min <= 1.0", "dRll>=2.5")
        // DEFINE_SIGNAL_REGION("SRRPV-2l2b-L", "Nbl=2", "Nsig = 2", "charge = same-sign", "pt > 25GeV", "n jets (> 25GeV) >= 1", "n bjets = 2",  "met >= 80 GeV", "njets (>20 GeV) <= 3",     "sum pt_bjet / sum pt jet >= 097",  "sum pt jet >= 300GeV", "dR(l_1, jet)min <= 1.0", "dRll>=2.5")
        // DEFINE_SIGNAL_REGION("SRRPV-2l2b-M", "Nbl=2", "Nsig = 2", "charge = same-sign", "pt > 25GeV", "n jets (> 25GeV) >= 1", "n bjets = 2",  "met >= 80 GeV", "njets (>20 GeV) = 3 or 4", "sum pt_bjet / sum pt jet >= 0.75", "sum pt jet >= 420GeV", "dR(l_1, jet)min <= 1.0", "dRll>=2.5")
        // DEFINE_SIGNAL_REGION("SRRPV-2l2b-H", "Nbl=2", "Nsig = 2", "charge = same-sign", "pt > 25GeV", "n jets (> 25GeV) >= 1", "n bjets = 2",  "met >= 80 GeV", "njets (>20 GeV) => 5 or <=6", "sum pt jet >= 420GeV", "dR(l_1, jet)min <= 1.0", "dRll>=2.0")
        // DEFINE_SIGNAL_REGION("SRRPV-2l3b-L", "Nbl=2", "Nsig = 2", "charge = same-sign", "pt > 25GeV", "n jets (> 25GeV) >= 1", "n bjets >= 3", "met >= 20 GeV", "njets (>20 GeV) <= 3 ", "sum pt_bjet / sum pt jet >= 0.8", "dR(l_1, jet)min <= 1.5", "dRll>=2.0")
        // DEFINE_SIGNAL_REGION("SRRPV-2l3b-M", "Nbl=2", "Nsig = 2", "charge = same-sign", "pt > 25GeV", "n jets (> 25GeV) >= 1", "n bjets >= 3", "met >= 20 GeV", "njets (>20 GeV) <= 3 ", "sum pt_bjet / sum pt jet >= 0.8")
        // DEFINE_SIGNAL_REGION("SRRPV-2l3b-H", "Nbl=2", "Nsig = 2", "charge = same-sign", "pt > 25GeV", "n jets (> 25GeV) >= 1", "n bjets >= 3", "met >= 20 GeV", "njets (>20 GeV) <= 6",  "sum pt_bjet / sum pt jet >= 0.5", "sum pt jet >= 350GeV", "dR(l_1, jet)min <= 1.0", "dRll>=2.0")

      }


      void run(const HEPUtils::Event* event) 
      {
        // Containers for baseline objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        vector<const HEPUtils::Particle*> baselineMuons;
        vector<const HEPUtils::Particle*> baselineTaus;
        vector<const HEPUtils::Particle*> baselinePhotons;
        vector<const HEPUtils::Jet*> baselineJets;


        // Missing momentim and energy
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();


        // Get baseline electrons and apply efficiency
        for (const HEPUtils::Particle* electron : event->electrons()) 
        {
          if (electron->pT() > 10. && electron->abseta() < 2.47)
          {
            if (electron->abseta() < 1.37 || electron->abseta() > 1.52)
            {
              baselineElectrons.push_back(electron);
            }
          }
        }
        // Apply electron isolation efficiency from "Loose" criteria in 1908.00005
        // apply1DEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_Iso_Loose"));
        // // Apply electron ID efficiency from "Loose" criteria in 1908.00005
        apply1DEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_ID_Loose"));

       
        // Get baseline muons and apply efficiency
        for (const HEPUtils::Particle* muon : event->muons()) 
        {
          if (muon->pT() > 10. && muon->abseta() < 2.5)
          {
            baselineMuons.push_back(muon);
          }
        }
        // Apply muon Id efficiency from "Medium" creteria in 2012.00578
        apply1DEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Medium"));
        // // Apply muon isolation efficiency from "Tight" criteria in 2012.00578
        // apply1DEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_Iso_Tight"));
 

        // Get baseline jets
        for (const HEPUtils::Jet* jet : event->jets()) 
        {
          if (jet->pT() > 20. && jet->abseta() < 4.5) 
          {
            baselineJets.push_back(jet);
          }
        }


        // 
        // Overlap removal
        // 
        const bool use_rapidity = true;
        removeOverlap(baselineElectrons, baselineElectrons, 0.05, use_rapidity, DBL_MAX);

        // // // 1) Remove electrons within DeltaR = 0.01 of muons
        removeOverlap(baselineElectrons, baselineMuons, 0.01, use_rapidity, DBL_MAX);

        // // 2) Remove jets within DeltaR = 0.2 of electron
        removeOverlap(baselineJets, baselineElectrons, 0.2, use_rapidity, DBL_MAX, 0.70);

        auto deltaRLimitFunc = [](double pT_lepton) { return std::min(0.4, 0.1 + 9.6 / pT_lepton); };
        removeOverlap(baselineElectrons, baselineJets, deltaRLimitFunc, use_rapidity, DBL_MAX);

        removeOverlap(baselineJets, baselineMuons, 0.4, use_rapidity, DBL_MAX);


        removeOverlap(baselineMuons, baselineJets, deltaRLimitFunc, use_rapidity, DBL_MAX);

        vector<const HEPUtils::Jet*> overlapBJets;
        // Find b-jets  
        double btag = 0.70; double cmisstag = 1/6.; double misstag = 1./134.;
        for (const HEPUtils::Jet* jet : baselineJets)
        {
          // Tag
          if( jet->btag() && random_bool(btag) ) overlapBJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) overlapBJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) overlapBJets.push_back(jet);
        }   

        removeOverlap(baselineElectrons, overlapBJets, 0.2, use_rapidity, DBL_MAX);
 
        // // // 3) Remove jets within DeltaR = 0.4 of muon
       
        // // // 4) Remove electrons and muons within DeltaR = min(0.4, 0.1 + 9.6 GeV / pT(e)) of a jet
        // // // Construct a lambda function to calculate the DeltaR limit as function of lepton pT
        
        
        
        
        // Collect all baseline leptons
        vector<const HEPUtils::Particle*> baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end());


        // Signal object containers
        vector<const HEPUtils::Particle*> signalMuons = baselineMuons;
        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalLeptons;
        vector<const HEPUtils::Jet*> signalNonBJets;
        vector<const HEPUtils::Jet*> signalBJets;


        // Require signalElectrons within |eta| < 2.0 and apply "Medium" ID efficiency
        for (const HEPUtils::Particle* p : baselineElectrons)
        {
          if (p->abseta() < 2.0) { signalElectrons.push_back(p); }
        }
        apply1DEfficiency(signalElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_ID_Medium"));

        //Signal jets |eta| < 2.8
        for (const HEPUtils::Jet* jet : baselineJets) 
        {
          if (jet->abseta() < 2.8) 
          {
            signalJets.push_back(jet);
          }
        }

        // Collect all signal leptons
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Find b-jets  
        // double btag = 0.70; double cmisstag = 1/6.; double misstag = 1./134.;
        for (const HEPUtils::Jet* jet : signalJets)
        {
          // Tag
          if( jet->btag() && random_bool(btag) ) signalBJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) signalBJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) signalBJets.push_back(jet);
          // Non b-jet
          else signalNonBJets.push_back(jet);
        }       


        // Sort by pT
        sortByPt(baselineLeptons);
        sortByPt(signalLeptons);
        sortByPt(signalElectrons);
        sortByPt(signalMuons);
        sortByPt(signalJets);
        sortByPt(signalBJets);


        // Count signal objects
        const size_t n_signal_Leptons = signalLeptons.size();
        const size_t n_baseline_Leptons = baselineLeptons.size();
        const size_t n_bjets = signalBJets.size();
        const size_t n_jets = signalJets.size();
        const size_t nElectrons = signalElectrons.size();
        const size_t nMuons = signalMuons.size();


        //
        // Preselection
        // 
        BEGIN_PRESELECTION
        END_PRESELECTION


    

        //
        // Construct selection variables 
        //

        // njets pt>25GeV
        int nJets25 = countPt(signalJets, 25.);

        // njets pt>40GeV
        int nJets40 = countPt(signalJets, 40.);

        // mjj  
        double mjj = 0;
        if (n_jets > 1)
        {
          HEPUtils::P4 dijets = signalJets.at(0)->mom() + signalJets.at(1)->mom();
          mjj = dijets.m();
        }

        //  mt2 
        double mt2 = 0;
        if(n_signal_Leptons > 1)
        {
          double pa[3] = { 0, signalLeptons.at(0)->mom().px(), signalLeptons.at(0)->mom().py() };
          double pb[3] = { 0, signalLeptons.at(1)->mom().px(), signalLeptons.at(1)->mom().py() };
          double pmiss[3] = { 0, event->missingmom().px(), event->missingmom().py()};
          double mn = 0.;

          mt2_bisect::mt2 mt2_calc;
          mt2_calc.set_momenta(pa,pb,pmiss);
          mt2_calc.set_mn(mn);
          mt2 = mt2_calc.get_mt2();
        }

        //mtmin
        double mTmin;
        HEPUtils::P4 p_lep1, p_lep2;
        if (n_signal_Leptons > 1)
        {
          HEPUtils::P4 p_lep1 = signalLeptons.at(0)->mom();
          HEPUtils::P4 p_lep2 = signalLeptons.at(1)->mom();

          double mT_lep1 = sqrt( 2.*p_lep1.pT()*met*( 1.-cos( p_lep1.deltaPhi(metVec) ) ) );
          double mT_lep2 = sqrt( 2.*p_lep2.pT()*met*( 1.-cos( p_lep2.deltaPhi(metVec) ) ) );

          mTmin = min(mT_lep1, mT_lep2);
        }

        // met significance
        double metsig = calcMETSignificance(baselineElectrons, event->photons(), baselineMuons, baselineJets, event->taus(), metVec);

        //meff
        double meff = scalarSumPt(signalLeptons) + scalarSumPt(signalJets) + met;

        // Delta R(l,l)
        double dRll;
        if (n_signal_Leptons > 1){
          dRll = fabs(signalLeptons.at(0)->mom().deltaR_eta(signalLeptons.at(1)->mom()));
        }

        // Spread
        double spread;
        if (n_signal_Leptons > 1){
          vector <double> phi_1 = {p_lep1.phi(), p_lep2.phi(), metVec.phi() };
          vector <double> phi_2;
          for (const HEPUtils::Jet* jet : signalJets) {
              phi_2.push_back(jet->phi());
          }
          vector <double> phi_total = phi_1;

          phi_total.insert(phi_total.end(), phi_2.begin(), phi_2.end());

          // mean of phi vectors
          double mean_phi1 = std::accumulate(phi_1.begin(), phi_1.end(), 0.0) / phi_1.size();
          double mean_phi2 = std::accumulate(phi_2.begin(), phi_2.end(), 0.0) / phi_2.size();
          double mean_phi_total = std::accumulate(phi_total.begin(), phi_total.end(), 0.0) / phi_total.size();

          //RMSE
          double sumOfSquares1 = 0.0;
          for (double phi : phi_1) {
              sumOfSquares1 += pow(phi-mean_phi1, 2);
          }
          double rmse_1 = sqrt(sumOfSquares1 / phi_1.size());
          //RMSE
          double sumOfSquares2 = 0.0;
          for (double phi : phi_2) {
              sumOfSquares2 += pow(phi-mean_phi2,2);
          }
          double rmse_2 = sqrt(sumOfSquares2 / phi_2.size());
          //RMSE
          double sumOfSquares3 = 0.0;
          for (double phi : phi_total) {
              sumOfSquares3 += pow(phi-mean_phi_total,2);
          }

          double rmse_total = sqrt(sumOfSquares3 / phi_total.size());

          spread = rmse_1*rmse_2 / rmse_total;

        }

        // // m_ee, m_mumu 
        // double meemumu = 0.0;
        // if (n_signal_Leptons == 3) {
        //     HEPUtils::P4 p_lep3 = signalLeptons[2]->mom();
        //     if (nElectrons==2){
        //         meemumu = signalElectrons[0]->mom().dot(signalElectrons[1]->mom());
        //     }
        //     else if (nMuons==2){
        //         meemumu = signalMuons[0]->mom().dot(signalMuons[1]->mom());
        //     }
        // }

        // // sum pt(l)
        // double sumpt_l = p_lep1.pT() + p_lep2.pT();

        // // sum pt_bjet / sum pt_jet
        // double sumpt_jet = 0.0;
        // for (const HEPUtils::Jet* jet : signalJets) {
        //     sumpt_jet += jet->pT();
        // }
        // double sumpt_bjet = 0.0;
        // for (const HEPUtils::Jet* jet : signalBJets) {
        //     sumpt_bjet += jet->pT();
        // }
        // double sumpt_bjet_jet = sumpt_bjet/sumpt_jet;

        // //dRl_jet
        // vector <double> dRl_jet;
        // for (const HEPUtils::Jet* jet : signalJets) {
        //     dRl_jet.push_back(jet->mom().deltaR_eta(p_lep1));
        // }
        // double dRl_jet_min = *min_element(dRl_jet.begin(), dRl_jet.end());




        /* Signal Regions */
        // Avoiding repetition with some of the more commonly used cuts
        bool met_75_125  = false; // met between 75 and 125
        bool met_125_175 = false; // met between 125 and 175
        bool met_gt_175  = false; // met greater than 175
        bool met_gt_50   = false; // met greater than 50
        bool mt2_gt_80   = false; // mt2 greater than 80 GeV
        bool mt2_lt_80   = false; // mt2 less than 80 GeV
        bool mt2_gt_100  = false; // mt2 greater than 100 GeV
        bool mt2_lt_100  = false; // mt2 less than 100 GeV
        


        if (75 < met && met < 125) {met_75_125 = true;}
        if (125 < met && met < 175) {met_125_175 = true;}
        if (met >= 175) {met_gt_175 = true;}
        if (mt2 >= 80) {mt2_gt_80 = true;}
        if (mt2 < 80) {mt2_lt_80 = true;}
        if (mt2 >= 100) {mt2_gt_100 = true;}
        if (mt2 < 100) {mt2_lt_100 = true;}

        

        // SR_Wh
        while (true)
        {   //njets (pt > 25 GeV) >= 1
            if (nJets25 >= 1) 
            {
              LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-ee-2", "SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-emu-2" ,"SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-1", "SRWh-high-mt2-mumu-2", "SRWh-high-mt2-mumu-3")
              LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")
            }
            else {break;}

            //N_sig(l) >= 2
            if (n_signal_Leptons >= 2) 
            {
              LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-ee-2", "SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-emu-2" ,"SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-1", "SRWh-high-mt2-mumu-2", "SRWh-high-mt2-mumu-3")
              LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")
            }
            else {break;}
            
            //pt(l) >= 25 
            if (signalLeptons.at(0)->pT() >= 25) 
            {
              LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-ee-2", "SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-emu-2" ,"SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-1", "SRWh-high-mt2-mumu-2", "SRWh-high-mt2-mumu-3")
              LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")
            }
            else {break;}

            //N_sig(l) == 2
            if (n_signal_Leptons == 2) 
            {
              LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-ee-2", "SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-emu-2" ,"SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-1", "SRWh-high-mt2-mumu-2", "SRWh-high-mt2-mumu-3")
              LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")
            }
            else {break;}
            
            // Same sign
            if (SSLeptons(signalLeptons)) 
            {
              LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-ee-2", "SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-emu-2" ,"SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-1", "SRWh-high-mt2-mumu-2", "SRWh-high-mt2-mumu-3")
              LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")
            }
            else {break;}

            //nbjets
            if (n_bjets == 0) 
            {
              LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-ee-2", "SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-emu-2" ,"SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-1", "SRWh-high-mt2-mumu-2", "SRWh-high-mt2-mumu-3")
              LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")
            }
            else {break;}

            // met >= 50
            if (met >= 50) 
            {
              LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-ee-2", "SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-emu-2" ,"SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-1", "SRWh-high-mt2-mumu-2", "SRWh-high-mt2-mumu-3")
              LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")
            }
            else {break;} 
              
            //mjj < 350
            if (mjj < 350) 
            {
              LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-ee-2", "SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-emu-2" ,"SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-1", "SRWh-high-mt2-mumu-2", "SRWh-high-mt2-mumu-3")
              LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")
            }
            else {break;} 
             
            //high mt2 > 80
            if (mt2_gt_80) 
            {
              LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-ee-2", "SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-emu-2" ,"SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-1", "SRWh-high-mt2-mumu-2", "SRWh-high-mt2-mumu-3")
              //met significance >= 7
              if (metsig >= 7) 
              {
                LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-ee-2", "SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-emu-2" ,"SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-1", "SRWh-high-mt2-mumu-2", "SRWh-high-mt2-mumu-3")
                
                //75 <= met < 125 
                if (met_75_125) 
                {
                  LOG_CUT("SRWh-high-mt2-ee-1", "SRWh-high-mt2-emu-1", "SRWh-high-mt2-mumu-1")

                  //type
                  if (nElectrons == 2) {FILL_SIGNAL_REGION("SRWh-high-mt2-ee-1");}
                  else if (nMuons == 2){FILL_SIGNAL_REGION("SRWh-high-mt2-mumu-1");}
                  else {FILL_SIGNAL_REGION("SRWh-high-mt2-emu-1");}
                } 
                else if (met_125_175) 
                {
                  LOG_CUT("SRWh-high-mt2-ee-2", "SRWh-high-mt2-emu-2", "SRWh-high-mt2-mumu-2")

                  //type
                  if (nElectrons == 2) {FILL_SIGNAL_REGION("SRWh-high-mt2-ee-2");} 
                  else if (nMuons == 2){FILL_SIGNAL_REGION("SRWh-high-mt2-mumu-2");} 
                  else {FILL_SIGNAL_REGION("SRWh-high-mt2-emu-2");}
                }
                else if (met_gt_175) 
                {
                  LOG_CUT("SRWh-high-mt2-ee-3", "SRWh-high-mt2-emu-3", "SRWh-high-mt2-mumu-3")

                  // type
                  if (nElectrons == 2) {FILL_SIGNAL_REGION("SRWh-high-mt2-ee-3");} 
                  else if (nMuons == 2){FILL_SIGNAL_REGION("SRWh-high-mt2-mumu-3");} 
                  else {FILL_SIGNAL_REGION("SRWh-high-mt2-emu-3");}
                }
              }
            }
            //low mt2 < 80
            else if( mt2_lt_80) 
            {
              LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")
              
              // mTmin >= 100
              if (mTmin >= 100)
              {
                LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")

                //met significance >= 6
                if( metsig >=6) 
                {
                  LOG_CUT("SRWh-low-mt2-ee", "SRWh-low-mt2-emu", "SRWh-low-mt2-mumu")

                  // type
                  if (nElectrons == 2)  {FILL_SIGNAL_REGION("SRWh-low-mt2-ee");}
                  else if (nMuons == 2) {FILL_SIGNAL_REGION("SRWh-low-mt2-mumu");}
                  else{FILL_SIGNAL_REGION("SRWh-low-mt2-emu");}    
                } 
              }
            }   
            
            // Applied all cuts
            break;   
        }
        

        //WZ 
        // while (true)
        // {   //n jets >= 1
        //     if (n_jets >= 1) 
        //     {
        //       LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3", "SRWZ-low-mt2")}
        //     else {break;}

        //     //Nsig(l) >= 2 && Nbl(l) >= 2
        //     if (n_baseline_Leptons >= 2 && n_signal_Leptons >= 2) 
        //     {
        //       LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3", "SRWZ-low-mt2")}
        //     else {break;}

        //     // same sign
        //     if (SSLeptons(signalLeptons)) 
        //     {
        //       LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3", "SRWZ-low-mt2")
        //     }
        //     else {break;}

        //     // Nbl(l) == 2
        //     if (n_baseline_Leptons == 2) 
        //     {
        //         LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3", "SRWZ-low-mt2")
        //     }
        //     else {break;}

        //     // Nsig(l) == 2
        //     if (n_signal_Leptons == 2) 
        //     {
        //       LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3", "SRWZ-low-mt2")
        //     }
        //     else {break;}
            
        //     //pt(l) >= 25 
        //     if (signalLeptons.at(0)->pT() >= 25) 
        //     {
        //       LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3", "SRWZ-low-mt2")
        //     }
        //     else {break;}

        //     //njets (pt > 25) >= 1
        //     if (nJets25 >= 1) 
        //     {
        //       LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3", "SRWZ-low-mt2")
        //     }
        //     else {break;}

        //     //nbjets == 0
        //     if (n_bjets == 0) 
        //     {
        //       LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3", "SRWZ-low-mt2")
        //     }
        //     else {break;}   

        //     //mjj <= 350
        //     if (mjj <= 350) 
        //     {
        //       LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3", "SRWZ-low-mt2")
        //     }
        //     else {break;}

        //     //high mt2 >= 100
        //     if (mt2_gt_100) 
        //     {
        //       LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3")

        //       //mTmin >= 100
        //       if (mTmin >= 100) 
        //       {
        //         LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3")

        //         // met >= 100
        //         if (met>=100) 
        //         {
        //           LOG_CUT("SRWZ-high-mt2-1", "SRWZ-high-mt2-2", "SRWZ-high-mt2-3")

        //           //type
        //           if (0 <= metsig && metsig < 10 && spread>=2.2) {FILL_SIGNAL_REGION("SRWZ-high-mt2-1");}
        //           else if (10 <= metsig && metsig < 13){FILL_SIGNAL_REGION("SRWZ-high-mt2-2");}
        //           else if (metsig >= 13 && dRll>=1){FILL_SIGNAL_REGION("SRWZ-high-mt2-3");}
        //         }
        //       }
        //     }
        //     // low mt2 <= 100
        //     else if (mt2_lt_100)
        //     {
        //       LOG_CUT("SRWZ-low-mt2")
        //       // mTmin >= 130
        //       if (mTmin >= 130) 
        //       {
        //         LOG_CUT("SRWZ-low-mt2")
        //         // met >= 140
        //         if (met >= 140) 
        //         {
        //           LOG_CUT("SRWZ-low-mt2")
        //           // meff <= 600
        //           if (meff <= 600)
        //           {
        //             LOG_CUT("SRWZ-low-mt2")

        //             // dRll <= 3
        //             if (dRll <= 3) {FILL_SIGNAL_REGION("SRWZ-low-mt2");}
        //           }
        //         }
        //       }
        //     }
        //     // Applied all cuts
        //     break;  
        // }
        

        // //bRVP
        // while (true)
        // {   //pt 
        //     if (p_lep2.pT() >= 20) {LOG_CUT("SRbRPV-2l-SS", "SRbRPV-3l")}
        //     else {break;}
        //     //njets > 25 GeV
        //     if (nJets25 >= 1) {LOG_CUT("SRbRPV-2l-SS", "SRbRPV-3l")}
        //     else {break;}
        //     //nsig
        //     if (n_signal_Leptons == 2) {
        //         LOG_CUT("SRbRPV-2l-SS")
        //         // charge
        //         if (signalLeptons.at(0)->pid() == signalLeptons.at(1)->pid()) {
        //             LOG_CUT("SRbRPV-2l-SS")
        //             //mt2
        //             if (mt2 >= 60){
        //                 LOG_CUT("SRbRPV-2l-SS")
        //                 //met
        //                 if (met >= 100){
        //                     LOG_CUT("SRbRPV-2l-SS")
        //                     // nbjets
        //                     if (n_bjets == 0){
        //                         LOG_CUT("SRbRPV-2l-SS")
        //                         // njets > 40
        //                         if (nJets40>=4) {
        //                             FILL_SIGNAL_REGION("SRbRPV-2l-SS");
        //                         }
        //                     }
        //                 }
        //             }
        //         }
        //     }
        //     else if (n_signal_Leptons == 3){
        //         if (mt2>=80) {
        //             LOG_CUT("SRbRPV-3l")
        //             if (met >= 120) {
        //                 LOG_CUT("SRbRPV-3l")
        //                 if (meff >= 350) {
        //                     LOG_CUT("SRbRPV-3l")
        //                     if (81 <= meemumu && meemumu<= 101) {
        //                         FILL_SIGNAL_REGION("SRbRPV-3l");
        //                     } 
        //                 }
        //             }
        //         }
        //     }
        //     // Applied all cuts
        //     break; 
        // }

        // UDD

        

      } // End run function




      /// Register results objects with the results for each SR; obs & bkg numbers from the paper
      virtual void collect_results() 
      {
        // //Wh
        COMMIT_SIGNAL_REGION("SRWh-high-mt2-ee-1", 22., 14.22, 1.87)
        COMMIT_SIGNAL_REGION("SRWh-high-mt2-ee-2", 8., 7.03, 0.78)
        COMMIT_SIGNAL_REGION("SRWh-high-mt2-ee-3", 5., 4.24, 0.94)
        COMMIT_SIGNAL_REGION("SRWh-high-mt2-emu-1", 37., 25.59, 3.62)
        COMMIT_SIGNAL_REGION("SRWh-high-mt2-emu-2", 10., 14.56, 2.20)
        COMMIT_SIGNAL_REGION("SRWh-high-mt2-emu-3", 3., 4.77, 0.73)
        COMMIT_SIGNAL_REGION("SRWh-high-mt2-mumu-1", 25., 24.13, 3.17)
        COMMIT_SIGNAL_REGION("SRWh-high-mt2-mumu-2", 12., 13.41, 1.49)
        COMMIT_SIGNAL_REGION("SRWh-high-mt2-mumu-3", 2., 7.11, 1.68)
        COMMIT_SIGNAL_REGION("SRWh-low-mt2-ee", 28., 23.57, 3.33)
        COMMIT_SIGNAL_REGION("SRWh-low-mt2-emu", 54., 50.59, 4.54)
        COMMIT_SIGNAL_REGION("SRWh-low-mt2-mumu", 50., 47.70, 4.28)
        //WZ
        //COMMIT_SIGNAL_REGION("SRWZ-high-mt2", 32., 44.59, 15.02)
        // COMMIT_SIGNAL_REGION("SRWZ-high-mt2-1", 0., 1.92, 1.29)
        // COMMIT_SIGNAL_REGION("SRWZ-high-mt2-2", 7., 8.62, 2.98)
        // COMMIT_SIGNAL_REGION("SRWZ-high-mt2-3", 5., 7.37, 2.62)
        // COMMIT_SIGNAL_REGION("SRWZ-low-mt2", 3., 1.71, 0.89)
        //bRPV
        // COMMIT_SIGNAL_REGION("SRbRPV-2l-SS", 40., 44.59, 14.39)
        // COMMIT_SIGNAL_REGION("SRbRPV-3l", 227., 251.19, 59.29)
        //UDD

        COMMIT_CUTFLOWS
      }


    protected:

      void analysis_specific_reset() 
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2OR3LEP_139invfb)

  }
}
