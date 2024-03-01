///
///  \author Martin White
///  \date 2023 August
///
///  *********************************************

// Based on RJR regions of https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-05/
// Luminosity: 139 fb^-1

#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ROOT
#ifndef EXCLUDE_RESTFRAMES
//#define CHECK_CUTFLOW

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

#include "RestFrames/RestFrames.hh"
#include "TLorentzVector.h"

using namespace std;

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    bool SortLeptons2LJ(const pair<TLorentzVector,int> lv1, const pair<TLorentzVector,int> lv2)
    //bool VariableConstruction::SortLeptons(const lep lv1, const lep lv2)
    {
      return lv1.first.Pt() > lv2.first.Pt();
    }

    bool SortJets2LJ(const TLorentzVector jv1, const TLorentzVector jv2)
    {
      return jv1.Pt() > jv2.Pt();
    }

    class Analysis_ATLAS_13TeV_2LEPJETS_RJR_139invfb : public Analysis
    {

    protected:

       Cutflows _cutflows;

       //vector<int> _test;
       //int _test2;

    private:

      // Recursive jigsaw objects (using RestFrames)

      unique_ptr<RestFrames::LabRecoFrame>       LAB_2L2J;
      unique_ptr<RestFrames::DecayRecoFrame>     C1N2_2L2J;
      unique_ptr<RestFrames::DecayRecoFrame>     C1a_2L2J;
      unique_ptr<RestFrames::DecayRecoFrame>     N2b_2L2J;

      unique_ptr<RestFrames::VisibleRecoFrame>   J1_2L2J;
      unique_ptr<RestFrames::VisibleRecoFrame>   J2_2L2J;
      unique_ptr<RestFrames::VisibleRecoFrame>   L1b_2L2J;
      unique_ptr<RestFrames::VisibleRecoFrame>   L2b_2L2J;

      unique_ptr<RestFrames::InvisibleRecoFrame> X1a_2L2J;
      unique_ptr<RestFrames::InvisibleRecoFrame> X1b_2L2J;

      unique_ptr<RestFrames::InvisibleGroup>    INV_2L2J;

      unique_ptr<RestFrames::SetMassInvJigsaw>     X1_mass_2L2J;
      unique_ptr<RestFrames::SetRapidityInvJigsaw> X1_eta_2L2J;

      unique_ptr<RestFrames::ContraBoostInvJigsaw> X1X1_contra_2L2J;

      // combinatoric (transverse) tree
      // for jet assignment
      unique_ptr<RestFrames::LabRecoFrame>        LAB_comb;
      unique_ptr<RestFrames::DecayRecoFrame>      CM_comb;
      unique_ptr<RestFrames::DecayRecoFrame>      S_comb;
      unique_ptr<RestFrames::VisibleRecoFrame>    ISR_comb;
      unique_ptr<RestFrames::VisibleRecoFrame>    J_comb;
      unique_ptr<RestFrames::VisibleRecoFrame>    L_comb;
      unique_ptr<RestFrames::InvisibleRecoFrame>  I_comb;
      unique_ptr<RestFrames::InvisibleGroup>      INV_comb;
      unique_ptr<RestFrames::SetMassInvJigsaw>    InvMass_comb;
      unique_ptr<RestFrames::CombinatoricGroup>   JETS_comb;
      unique_ptr<RestFrames::MinMassesCombJigsaw> SplitJETS_comb;

      // 2L+NJ tree (Z->ll + W/Z->qq)
      unique_ptr<RestFrames::LabRecoFrame>        LAB_2LNJ;
      unique_ptr<RestFrames::DecayRecoFrame>      CM_2LNJ;
      unique_ptr<RestFrames::DecayRecoFrame>      S_2LNJ;
      unique_ptr<RestFrames::VisibleRecoFrame>    ISR_2LNJ;

      unique_ptr<RestFrames::DecayRecoFrame>      Ca_2LNJ;
      unique_ptr<RestFrames::DecayRecoFrame>      Z_2LNJ;
      unique_ptr<RestFrames::VisibleRecoFrame>    L1_2LNJ;
      unique_ptr<RestFrames::VisibleRecoFrame>    L2_2LNJ;

      unique_ptr<RestFrames::DecayRecoFrame>          Cb_2LNJ;
      unique_ptr<RestFrames::SelfAssemblingRecoFrame> JSA_2LNJ;
      unique_ptr<RestFrames::VisibleRecoFrame>        J_2LNJ;

      unique_ptr<RestFrames::InvisibleRecoFrame>  Ia_2LNJ;
      unique_ptr<RestFrames::InvisibleRecoFrame>  Ib_2LNJ;

      unique_ptr<RestFrames::InvisibleGroup>       INV_2LNJ;
      unique_ptr<RestFrames::SetMassInvJigsaw>     InvMass_2LNJ;
      unique_ptr<RestFrames::SetRapidityInvJigsaw> InvRapidity_2LNJ;
      unique_ptr<RestFrames::ContraBoostInvJigsaw> SplitINV_2LNJ;
      unique_ptr<RestFrames::CombinatoricGroup>    JETS_2LNJ;


      struct ptComparison
      {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_2LEPJETS_RJR_139invfb()
      {

        // Counters for the number of accepted events for each signal region

        //_counters["SR2L_High"] = EventCounter("SR2L_High");
        _counters["SR2L_Low"] = EventCounter("SR2L_Low");
        //_counters["SR2L_Int"] = EventCounter("SR2L_Int");
        _counters["SR2L_ISR"] = EventCounter("SR2L_ISR");


        set_analysis_name("ATLAS_13TeV_2LEPJETS_RJR_139invfb");
        set_luminosity(139);
      
	_cutflows.addCutflow("SR2L_low", {"Trigger and 2 signal leptons", "Preselection", "0.35 < HPP11/HPP41 < 0.60", "pTlabPP/(pTlabPP+HTPP11) < 0.05", "min(dPhi(j1/j2,ptmiss))<2.4", "HPP41 > 400 GeV",});

	_cutflows.addCutflow("SR2L_ISR", {"Pre-selection", "80 GeV < mZ < 100 GeV", "50 GeV < mJ < 110 GeV", "dPhiCMISR > 2.8", "0.4 < RISR < 0.75", "pTCMISR > 180 GeV","pTCM_I > 100 GeV","pTCM < 30 GeV"});

	
        // Recursive jigsaw setup
        #pragma omp critical (init_ATLAS_13TeV_2LEPJETS_RJR_139invfb)
        {

          LAB_2L2J.reset(new RestFrames::LabRecoFrame("LAB_2L2J","lab2L2J"));
	  C1N2_2L2J.reset(new RestFrames::DecayRecoFrame("C1N2_2L2J","#tilde{#chi}^{ #pm}_{1} #tilde{#chi}^{ 0}_{2}"));
	  C1a_2L2J.reset(new RestFrames::DecayRecoFrame("C1a_2L2J","#tilde{#chi}^{ #pm}_{1}"));
	  N2b_2L2J.reset(new RestFrames::DecayRecoFrame("N2b_2L2J","#tilde{#chi}^{ 0}_{2}"));
	  
          J1_2L2J.reset(new RestFrames::VisibleRecoFrame("J1_2L2J","#it{j}_{1}"));
	  J2_2L2J.reset(new RestFrames::VisibleRecoFrame("J2_2L2J","#it{j}_{2}"));
	  L1b_2L2J.reset(new RestFrames::VisibleRecoFrame("L1b_2L2J","#it{l}_{1}"));
	  L2b_2L2J.reset(new RestFrames::VisibleRecoFrame("L2b_2L2J","#it{l}_{2}"));
	  
	  X1a_2L2J.reset(new RestFrames::InvisibleRecoFrame("X1a_2L2J","#tilde{#chi}^{ 0}_{1 a}"));
	  X1b_2L2J.reset(new RestFrames::InvisibleRecoFrame("X1b_2L2J","#tilde{#chi}^{ 0}_{1 b}"));

          LAB_2L2J->SetChildFrame(*C1N2_2L2J);

          C1N2_2L2J->AddChildFrame(*C1a_2L2J);
          C1N2_2L2J->AddChildFrame(*N2b_2L2J);

          C1a_2L2J->AddChildFrame(*J1_2L2J);
          C1a_2L2J->AddChildFrame(*J2_2L2J);
          C1a_2L2J->AddChildFrame(*X1a_2L2J);

          N2b_2L2J->AddChildFrame(*L1b_2L2J);
          N2b_2L2J->AddChildFrame(*L2b_2L2J);
          N2b_2L2J->AddChildFrame(*X1b_2L2J);

          if(!LAB_2L2J->InitializeTree())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_2L2J->InitializeTree() from the Analysis_ATLAS_13TeV_2LEPJETS_RJR_139invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }

          //setting the invisible components
          INV_2L2J.reset(new RestFrames::InvisibleGroup("INV_2L2J","#tilde{#chi}_{1}^{ 0} Jigsaws"));
          INV_2L2J->AddFrame(*X1a_2L2J);
          INV_2L2J->AddFrame(*X1b_2L2J);

          // Set di-LSP mass to minimum Lorentz-invariant expression
          X1_mass_2L2J.reset(new RestFrames::SetMassInvJigsaw("X1_mass_2L2J", "Set M_{#tilde{#chi}_{1}^{ 0} #tilde{#chi}_{1}^{ 0}} to minimum"));
          INV_2L2J->AddJigsaw(*X1_mass_2L2J);

          // Set di-LSP rapidity to that of visible particles
          X1_eta_2L2J.reset(new RestFrames::SetRapidityInvJigsaw("X1_eta_2L2J", "#eta_{#tilde{#chi}_{1}^{ 0} #tilde{#chi}_{1}^{ 0}} = #eta_{2jet+2#it{l}}"));
          INV_2L2J->AddJigsaw(*X1_eta_2L2J);
          X1_eta_2L2J->AddVisibleFrames(C1N2_2L2J->GetListVisibleFrames());

          X1X1_contra_2L2J.reset(new RestFrames::ContraBoostInvJigsaw("X1X1_contra_2L2J","Contraboost invariant Jigsaw"));
          INV_2L2J->AddJigsaw(*X1X1_contra_2L2J);
          X1X1_contra_2L2J->AddVisibleFrames(C1a_2L2J->GetListVisibleFrames(), 0);
          X1X1_contra_2L2J->AddVisibleFrames(N2b_2L2J->GetListVisibleFrames(), 1);
          X1X1_contra_2L2J->AddInvisibleFrames(C1a_2L2J->GetListInvisibleFrames(),0);
          X1X1_contra_2L2J->AddInvisibleFrames(N2b_2L2J->GetListInvisibleFrames(),1);

	  
          if(!LAB_2L2J->InitializeAnalysis())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_2L2J->InitializeAnalysis() from the Analysis_ATLAS_13TeV_2LEPJETS_RJR_139invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }

          // Compressed tree time
          LAB_comb.reset(new RestFrames::LabRecoFrame("LAB_comb","LAB"));
          CM_comb.reset(new RestFrames::DecayRecoFrame("CM_comb","CM"));
          S_comb.reset(new RestFrames::DecayRecoFrame("S_comb","S"));
          ISR_comb.reset(new RestFrames::VisibleRecoFrame("ISR_comb","ISR"));
          J_comb.reset(new RestFrames::VisibleRecoFrame("J_comb","Jets"));
          L_comb.reset(new RestFrames::VisibleRecoFrame("L_comb","#it{l}'s"));
          I_comb.reset(new RestFrames::InvisibleRecoFrame("I_comb","Inv"));

          LAB_comb->SetChildFrame(*CM_comb);
          CM_comb->AddChildFrame(*ISR_comb);
          CM_comb->AddChildFrame(*S_comb);
          S_comb->AddChildFrame(*L_comb);
          S_comb->AddChildFrame(*J_comb);
          S_comb->AddChildFrame(*I_comb);

          if(!LAB_comb->InitializeTree())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_comb->InitializeTree() from the Analysis_ATLAS_13TeV_2LEPJETS_RJR_139invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }

          // 2L + NJ tree
	  LAB_2LNJ.reset(new RestFrames::LabRecoFrame("LAB_2LNJ","LAB"));
          CM_2LNJ.reset(new RestFrames::DecayRecoFrame("CM_2LNJ","CM"));
          S_2LNJ.reset(new RestFrames::DecayRecoFrame("S_2LNJ","S"));
          ISR_2LNJ.reset(new RestFrames::VisibleRecoFrame("ISR_2LNJ","ISR"));
          Ca_2LNJ.reset(new RestFrames::DecayRecoFrame("Ca_2LNJ","C_{a}"));
          Z_2LNJ.reset(new RestFrames::DecayRecoFrame("Z_2LNJ","Z"));
          L1_2LNJ.reset(new RestFrames::VisibleRecoFrame("L1_2LNJ","#it{l}_{1}"));
          L2_2LNJ.reset(new RestFrames::VisibleRecoFrame("L2_2LNJ","#it{l}_{2}"));
          Cb_2LNJ.reset(new RestFrames::DecayRecoFrame("Cb_2LNJ","C_{b}"));
          JSA_2LNJ.reset(new RestFrames::SelfAssemblingRecoFrame("JSA_2LNJ", "J"));
          J_2LNJ.reset(new RestFrames::VisibleRecoFrame("J_2LNJ","Jets"));
          Ia_2LNJ.reset(new RestFrames::InvisibleRecoFrame("Ia_2LNJ","I_{a}"));
          Ib_2LNJ.reset(new RestFrames::InvisibleRecoFrame("Ib_2LNJ","I_{b}"));

	  LAB_2LNJ->SetChildFrame(*CM_2LNJ);
          CM_2LNJ->AddChildFrame(*ISR_2LNJ);
          CM_2LNJ->AddChildFrame(*S_2LNJ);
          S_2LNJ->AddChildFrame(*Ca_2LNJ);
          S_2LNJ->AddChildFrame(*Cb_2LNJ);
          Ca_2LNJ->AddChildFrame(*Z_2LNJ);
          Ca_2LNJ->AddChildFrame(*Ia_2LNJ);
          Cb_2LNJ->AddChildFrame(*JSA_2LNJ);
          Cb_2LNJ->AddChildFrame(*Ib_2LNJ);
          Z_2LNJ->AddChildFrame(*L1_2LNJ);
          Z_2LNJ->AddChildFrame(*L2_2LNJ);
          JSA_2LNJ->AddChildFrame(*J_2LNJ);
	  
          if(!LAB_2LNJ->InitializeTree())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_2LNJ->InitializeTree() from the Analysis_ATLAS_13TeV_2LEPJETS_RJR_139invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }

          ////////////// Jigsaw rules set-up /////////////////

          // combinatoric (transverse) tree
          // for jet assignment
          INV_comb.reset(new RestFrames::InvisibleGroup("INV_comb","Invisible System"));
          INV_comb->AddFrame(*I_comb);

          InvMass_comb.reset(new RestFrames::SetMassInvJigsaw("InvMass_comb", "Invisible system mass Jigsaw"));
          INV_comb->AddJigsaw(*InvMass_comb);

          JETS_comb.reset(new RestFrames::CombinatoricGroup("JETS_comb","Jets System"));
          JETS_comb->AddFrame(*ISR_comb);
          JETS_comb->SetNElementsForFrame(*ISR_comb, 1, false);
          JETS_comb->AddFrame(*J_comb);
          JETS_comb->SetNElementsForFrame(*J_comb, 0, false);

          SplitJETS_comb.reset(new RestFrames::MinMassesCombJigsaw("SplitJETS_comb", "Minimize M_{ISR} and M_{S} Jigsaw"));
          JETS_comb->AddJigsaw(*SplitJETS_comb);
          SplitJETS_comb->AddCombFrame(*ISR_comb, 0);
          SplitJETS_comb->AddCombFrame(*J_comb, 1);
          SplitJETS_comb->AddObjectFrame(*ISR_comb,0);
          SplitJETS_comb->AddObjectFrame(*S_comb,1);

          if(!LAB_comb->InitializeAnalysis())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_comb->InitializeAnalysis() from the Analysis_ATLAS_13TeV_2LEPJETS_RJR_139invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }

          // 2L+NJ tree (Z->ll + W/Z->qq)
          INV_2LNJ.reset(new RestFrames::InvisibleGroup("INV_2LNJ","Invisible System"));
          INV_2LNJ->AddFrame(*Ia_2LNJ);
          INV_2LNJ->AddFrame(*Ib_2LNJ);

          InvMass_2LNJ.reset(new RestFrames::SetMassInvJigsaw("InvMass_2LNJ", "Invisible system mass Jigsaw"));
          INV_2LNJ->AddJigsaw(*InvMass_2LNJ);
          InvRapidity_2LNJ.reset(new RestFrames::SetRapidityInvJigsaw("InvRapidity_2LNJ", "Set inv. system rapidity"));
          INV_2LNJ->AddJigsaw(*InvRapidity_2LNJ);
          InvRapidity_2LNJ->AddVisibleFrames(S_2LNJ->GetListVisibleFrames());
          SplitINV_2LNJ.reset(new RestFrames::ContraBoostInvJigsaw("SplitINV_2LNJ", "INV -> I_{a}+ I_{b} jigsaw"));
          INV_2LNJ->AddJigsaw(*SplitINV_2LNJ);
          SplitINV_2LNJ->AddVisibleFrames(Ca_2LNJ->GetListVisibleFrames(), 0);
          SplitINV_2LNJ->AddVisibleFrames(Cb_2LNJ->GetListVisibleFrames(), 1);
          SplitINV_2LNJ->AddInvisibleFrame(*Ia_2LNJ, 0);
          SplitINV_2LNJ->AddInvisibleFrame(*Ib_2LNJ, 1);

          JETS_2LNJ.reset(new RestFrames::CombinatoricGroup("JETS_comb","Jets System"));
          JETS_2LNJ->AddFrame(*J_2LNJ);
          JETS_2LNJ->SetNElementsForFrame(*J_2LNJ, 0);

          if(!LAB_2LNJ->InitializeAnalysis())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_2LNJ->InitializeAnalysis() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }


        }

      }

      void run(const HEPUtils::Event* event)
      {

        // Clear
        LAB_2L2J->ClearEvent();
        LAB_comb->ClearEvent();
        LAB_2LNJ->ClearEvent();

        // Baseline objects
        vector<const HEPUtils::Particle*> baselineElectrons;
        vector<const HEPUtils::Particle*> baselineMuons;
        vector<const HEPUtils::Particle*> baselineLeptons;
        vector<const HEPUtils::Jet*> baselineJets;
        vector<const HEPUtils::Jet*> baselineBJets;
        vector<const HEPUtils::Jet*> baselineNonBJets;

        // Missing momentum and energy
        HEPUtils::P4 metVec = event->missingmom();
        //double met = event->met();
        TVector3 ETMiss;
        ETMiss.SetXYZ(metVec.px(),metVec.py(),0.0);


        // Baseline cuts taken from ATLAS code snippet

        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT()>10. && electron->abseta()<2.47) baselineElectrons.push_back(electron);
        }
        //apply1DEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Loose"));
	applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_Recon"));


        // Baseline muons have satisfy "medium" criteria and have pT > 3 GeV and |eta| < 2.7
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT()>10. && muon->abseta()<2.7) baselineMuons.push_back(muon);
        }
        //ATLAS::applyMuonEffR2(baselineMuons);
	applyEfficiency(baselineMuons, ATLAS::eff1DMu.at("MUON_2018_03_ID_Medium"));

        double jet_eff = 0.9;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT()>20. && jet->abseta()<4.5)
            if( (jet->pT() >= 120. || jet->abseta() >= 2.5) || random_bool(jet_eff) ) baselineJets.push_back(jet);
        }

        // Overlap removal
        // Note: the paper and code snippet disagree on this
        // Have used the overlap removal from the paper (shouldn't make much difference)
        // 1) Remove muons with 0.01 of an electron, mimics shared tracks
        removeOverlap(baselineMuons, baselineElectrons, 0.01);
        // 2) Remove jets within DeltaR = 0.2 of electron
        removeOverlap(baselineJets, baselineElectrons, 0.2);
        // 3) If any lepton has Delta R < min(0.4, 0.04 + 10/pT(l)) with a jet, remove the lepton.
        auto lambda = [](double lepton_pT) { return std::min(0.4, 0.04 + 10./(lepton_pT) ); };
        removeOverlap(baselineElectrons, baselineJets, lambda);
        // 4) Remove muons within 0.2 of jets (incorporates shared track approximation)
        removeOverlap(baselineMuons, baselineJets, 0.2);
        // 5) Remove muons subject to pT-dependent deltaR requirement
        removeOverlap(baselineMuons, baselineJets, lambda);

        // Signal objects
        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBJets;
        vector<const HEPUtils::Jet*> signalNonBJets;
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        vector<const HEPUtils::Particle*> signalLeptons;

        // Signal electrons must satisfy the “medium” identification requirement as defined in arXiv: 1902.04655 [hep-ex]
        //apply1DEfficiency(signalElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Medium"));
	applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("EGAM_2018_01_ID_Medium"));
	

        // Signal electrons must have pT > 25 GeV
        for (const HEPUtils::Particle* signalElectron : baselineElectrons)
        {
          if (signalElectron->pT() > 25.) signalElectrons.push_back(signalElectron);
        }

        // Signal muons must have pT > 5 GeV.
        for (const HEPUtils::Particle* signalMuon : baselineMuons)
        {
          if (signalMuon->pT() > 25.) signalMuons.push_back(signalMuon);
        }

        // Signal jets must have pT > 30 GeV
        for (const HEPUtils::Jet* signalJet : baselineJets)
        {
          if (signalJet->pT() > 30. && signalJet->abseta()<2.4) signalJets.push_back(signalJet);
        }

        // Find b-jets
        double btag = 0.77; double cmisstag = 1/16.; double misstag = 1./113.;
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

        // Fill signal leptons
        signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        // Fill baseline leptons
        baselineLeptons = baselineElectrons;
        baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end());

        // Sort by pT
        sort(signalJets.begin(), signalJets.end(), compareJetPt);
        sort(signalBJets.begin(), signalBJets.end(), compareJetPt);
        sort(signalLeptons.begin(), signalLeptons.end(), comparePt);

        // Now ready to start analysis

        bool m_foundSFOS=false;
        //bool m_is2Lep=false;
        //bool m_is2Lep2Jet=false;
        //bool m_is2L2JInt=false;


        size_t nleptons = signalLeptons.size();
        size_t njets = signalJets.size();
        size_t nbjets = signalBJets.size();

        bool cut_2lep=true;
        if (nleptons < 2)cut_2lep=false;

        bool cut_2jets=true;
        if(njets<2)cut_2jets=false;

        // Taken from previous RJ GAMBIT analysis
        // Presumably TLorentzVector stuff is needed for RestFrames
        TLorentzVector metLV;
        //TLorentzVector bigFatJet;
        metLV.SetPxPyPzE(metVec.px(),metVec.py(),0.,sqrt(metVec.px()*metVec.px()+metVec.py()*metVec.py()));

        //Put the Jets in a more useful form
        vector<TLorentzVector> myJets;
        for(unsigned int ijet=0; ijet<signalJets.size();ijet++)
        {
          TLorentzVector tmp;
          tmp.SetPtEtaPhiM(signalJets[ijet]->pT(),signalJets[ijet]->eta(),signalJets[ijet]->phi(),signalJets[ijet]->mass());
          myJets.push_back(tmp);
        }


        //Put the Leptons in a more useful form
        vector<pair<TLorentzVector,int> > myLeptons;
        //vector<lep> myLeptons;
        for(unsigned int ilep=0; ilep<signalLeptons.size(); ilep++)
        {
          pair<TLorentzVector,int> temp;
          TLorentzVector tlv_temp;

          tlv_temp.SetPtEtaPhiM(signalLeptons[ilep]->pT(),signalLeptons[ilep]->eta(),signalLeptons[ilep]->phi(),0.0);
          temp.first = tlv_temp;
          int lepton_charge=0;
          if(signalLeptons[ilep]->pid()<0)lepton_charge=-1;
          if(signalLeptons[ilep]->pid()>0)lepton_charge=1;
          temp.second = lepton_charge;
          myLeptons.push_back(temp);
        }

        sort(myJets.begin(), myJets.end(), SortJets2LJ);
        sort(myLeptons.begin(), myLeptons.end(), SortLeptons2LJ);

        //Only proceed if there are 2 leptons and 2 jets
        if(cut_2lep && cut_2jets)
        {
	  
          bool iscomp = false;
          if (njets>2) iscomp = true;

          // SFOS criteria
          double diff = 10000000000.0;
          int Zlep1 = -99;
          int Zlep2 = -99;
          double Zmass = -999.0;
          bool foundSFOS = false;

          for(unsigned int i=0; i<myLeptons.size(); i++)
          {
            for(unsigned int j=i+1; j<myLeptons.size(); j++)
            {
              //Opposite-Sign
              if(myLeptons[i].second*myLeptons[j].second<0)
              {
                //Same-Flavor
                if(abs(myLeptons[i].second)==abs(myLeptons[j].second))
                {
                  double mass = (myLeptons[i].first+myLeptons[j].first).M();
                  double massdiff = fabs(mass-91.1876);
                  if(massdiff<diff)
                  {
                    diff=massdiff;
                    Zmass=mass;
                    Zlep1 = i;
                    Zlep2 = j;
                    foundSFOS = true;
                  }
                }
              }
            }
          }

          if(!foundSFOS)
          {
            m_foundSFOS=false;
          }
          else
          {
            m_foundSFOS=true;
          }

          if(m_foundSFOS)
          {

            // Use first and second jets
            double mjj = (signalJets.at(0)->mom()+signalJets.at(1)->mom()).m();

            double mindphi=100000.;
            double dphi=0;
            TLorentzVector tempjet;
            for(unsigned int ijet=0; ijet<signalJets.size();ijet++)
            {
              tempjet.SetPtEtaPhiM(signalJets[ijet]->pT(),signalJets[ijet]->eta(),signalJets[ijet]->phi(),signalJets[ijet]->mass());
              dphi = fabs(metLV.DeltaPhi(tempjet));
              if(dphi<mindphi) mindphi=dphi;
            }


            L1b_2L2J->SetLabFrameFourVector(myLeptons[Zlep1].first); // Set lepton 4-vectors
            L2b_2L2J->SetLabFrameFourVector(myLeptons[Zlep2].first);
            J1_2L2J->SetLabFrameFourVector(myJets[0]); // Set jets 4-vectors
            J2_2L2J->SetLabFrameFourVector(myJets[1]);

            TVector3 MET = ETMiss;                     // Get the MET
            MET.SetZ(0.);
            INV_2L2J->SetLabFrameThreeVector(MET);                  // Set the MET in reco tree

            // Analyze the event
            if(!LAB_2L2J->AnalyzeEvent())
            {
              str errmsg;
              errmsg  = "Some problem occurred when calling LAB_2L2J->AnalyzeEvent() from the Analysis_ATLAS_13TeV_2LEPJETS_RJR_139invfb analysis class.\n";
              piped_warnings.request(LOCAL_INFO, errmsg);
              return;
            }

            TLorentzVector vP_V1aPP  = J1_2L2J->GetFourVector(*C1N2_2L2J);
            TLorentzVector vP_V2aPP  = J2_2L2J->GetFourVector(*C1N2_2L2J);
            TLorentzVector vP_V1bPP  = L1b_2L2J->GetFourVector(*C1N2_2L2J);
            TLorentzVector vP_V2bPP  = L2b_2L2J->GetFourVector(*C1N2_2L2J);
            TLorentzVector vP_I1aPP  = X1a_2L2J->GetFourVector(*C1N2_2L2J);
            TLorentzVector vP_I1bPP  = X1b_2L2J->GetFourVector(*C1N2_2L2J);

            double H2PP = (vP_V1aPP + vP_V2aPP + vP_V1bPP + vP_V2bPP).P() + (vP_I1aPP + vP_I1bPP).P();//H(1,1)PP

            double H5PP = vP_V1aPP.P() + vP_V2aPP.P() + vP_V1bPP.P() + vP_V2bPP.P() + (vP_I1aPP + vP_I1bPP).P();//H(3,1)PP
            double HT5PP = vP_V1aPP.Pt() + vP_V2aPP.Pt() + vP_V1bPP.Pt() + vP_V2bPP.Pt() + (vP_I1aPP + vP_I1bPP).Pt();//HT(3,1)PP

            double R_H2PP_H5PP = H2PP/H5PP;

            TVector3 vP_PP = C1N2_2L2J->GetFourVector(*LAB_2L2J).Vect();
            double Pt_PP = vP_PP.Pt();
            double RPT_HT5PP = Pt_PP/(Pt_PP + HT5PP);

            //double dphiVP = C1N2_2L2J->GetDeltaPhiDecayVisible();

            // P frame

            TLorentzVector vP_V1aPa  = J1_2L2J->GetFourVector(*C1a_2L2J);
            TLorentzVector vP_V2aPa = J2_2L2J->GetFourVector(*C1a_2L2J);
            TLorentzVector vP_I1aPa  = X1a_2L2J->GetFourVector(*C1a_2L2J);

            TLorentzVector vP_V1bPb = L1b_2L2J->GetFourVector(*N2b_2L2J);
            TLorentzVector vP_V2bPb = L2b_2L2J->GetFourVector(*N2b_2L2J);
            TLorentzVector vP_I1bPb = X1b_2L2J->GetFourVector(*N2b_2L2J);

            //double H2Pa = (vP_V1aPa + vP_V2aPa).P() + (vP_I1aPa).P(); //H(1,1)P
            //double H2Pb = (vP_V1bPb + vP_V2bPb).P() + vP_I1bPb.P();//H(1,1)P

            //double H3Pa = vP_V1aPa.P() + vP_V2aPa.P() + vP_I1aPa.P();//H(1,1)P
            //double H3Pb = vP_V1bPb.P() + vP_V2bPb.P() + vP_I1bPb.P();//H(2,1)P

            //double minH2P = std::min(H2Pa,H2Pb);
            //double minH3P = std::min(H3Pa,H3Pb);
            //    double R_H2Pa_H2Pb = H2Pa/H2Pb;
            //double R_H3Pa_H3Pb = H3Pa/H3Pb;
            //double R_minH2P_minH3P = minH2P/minH3P;

            //std::cout << "STANDARD REGIONS" << std::endl;
            // we are ready to go
	  
            // Low mass
            if (njets==2 && nbjets==0 && signalJets[0]->pT()>30. && signalJets[1]->pT()>30. && Zmass>80. && Zmass<100. && mjj>70. && mjj<90. && H5PP>400. && RPT_HT5PP<0.05 && R_H2PP_H5PP>0.35 && R_H2PP_H5PP<0.65 && mindphi>2.4)_counters.at("SR2L_Low").add_event(event);

	    // Now fill the low mass cutflow
	    // Note: pre-selection is already applied so first cut won't match
	    const double w = event->weight();
	    _cutflows.fillinit(w);
	 
	    vector<str> SR2L_low = {"Trigger and 2 signal leptons", "Preselection", "0.35 < HPP11/HPP41 < 0.60", "pTlabPP/(pTlabPP+HTPP11) < 0.05", "min(dPhi(j1/j2,ptmiss))>2.4", "HPP41 > 400 GeV"};

	    bool cut_presel = cut_2lep && cut_2jets && m_foundSFOS && nbjets==0 && signalJets[0]->pT()>30. && signalJets[1]->pT()>30. && Zmass>80. && Zmass<100.  && mjj>70. && mjj<90.;
	    
	    _cutflows["SR2L_low"].fillnext({cut_2lep,
		cut_presel,
		R_H2PP_H5PP>0.35 && R_H2PP_H5PP<0.6,
		RPT_HT5PP<0.05,
		mindphi>2.4,
		H5PP>400.}, w);
		    
            // Intermediate
            //Not used in paper, despite being in ATLAS code snippet!
            //if (nbjets==0 && leptons[0].Pt()>25. && leptons[1].Pt()>25. && jets[0].Pt()>30. && jets[1].Pt()>30. && Zmass>80. && Zmass<100. && mjj>60. && mjj<100. && H5PP>600. && RPT_HT5PP<0.05 && dphiVP>0.6 && dphiVP<2.6 && R_minH2P_minH3P>0.8)_counters.at("SR2L_Int").add_event(event);;

            // High
            //Not used - see above
            //if (leptons[0].Pt()>25. && leptons[1].Pt()>25. && jets[0].Pt()>30. && jets[1].Pt()>30. && Zmass>80. && Zmass<100. && mjj>60. && mjj<100. && H5PP>800. && RPT_HT5PP<0.05 && dphiVP>0.3 && dphiVP<2.8 && R_minH2P_minH3P>0.8)_counters.at("SR2L_High").add_event(event);
	  
            // Compressed time
            if(iscomp)
            {

              double NjS = 0;
              double NjISR = 0;

              vector<RestFrames::RFKey> jetID;

              for(int i = 0; i < int(myJets.size()); i++)
              {

                TLorentzVector jet = myJets[i];

                // transverse view of jet 4-vectors
                jet.SetPtEtaPhiM(jet.Pt(),0.0,jet.Phi(),jet.M());
                jetID.push_back(JETS_comb->AddLabFrameFourVector(jet));
              }

              TLorentzVector lepSys(0.,0.,0.,0.);
              for(int i = 0; i < int(myLeptons.size()); i++)
              {
                TLorentzVector lep1;
                // transverse view of mu 4-vectors
                lep1.SetPtEtaPhiM(myLeptons[i].first.Pt(),0.0,myLeptons[i].first.Phi(),myLeptons[i].first.M());
                lepSys = lepSys + lep1;
              }
              L_comb->SetLabFrameFourVector(lepSys);

              INV_comb->SetLabFrameThreeVector(ETMiss);

              if(!LAB_comb->AnalyzeEvent())
              {
                str errmsg;
                errmsg  = "Some problem occurred when calling LAB_comb->AnalyzeEvent() from the Analysis_ATLAS_13TeV_2LEPJETS_RJR_139invfb analysis class.\n";
                piped_warnings.request(LOCAL_INFO, errmsg);
                  return;
              }

              for(int i = 0; i < int(signalJets.size()); i++)
              {
                if(JETS_comb->GetFrame(jetID[i]) == *J_comb)
                {
                  NjS++;
                }
                else
                {
                  NjISR++;
                }
              }

              // put jets in their place
              int NJ = jetID.size();
              TLorentzVector vISR(0.,0.,0.,0.);
              for(int i = 0; i < NJ; i++)
              {
                if(JETS_comb->GetFrame(jetID[i]) == *J_comb)
                {
                  JETS_2LNJ->AddLabFrameFourVector(myJets[i]);
                }
                else
                {
                  vISR += myJets[i];
                }
              }

              ISR_2LNJ->SetLabFrameFourVector(vISR);

              L1_2LNJ->SetLabFrameFourVector(myLeptons[Zlep1].first);
              L2_2LNJ->SetLabFrameFourVector(myLeptons[Zlep2].first);

              INV_2LNJ->SetLabFrameThreeVector(ETMiss);

              if(!LAB_2LNJ->AnalyzeEvent())
              {
                str errmsg;
                errmsg  = "Some problem occurred when calling LAB_2LNJ->AnalyzeEvent() from the Analysis_ATLAS_13TeV_2LEPJETS_RJR_139invfb analysis class.\n";
                piped_warnings.request(LOCAL_INFO, errmsg);
                return;
              }

              // Make the variables
              TLorentzVector vP_CM;
              TLorentzVector vP_ISR;
              TLorentzVector vP_Ia;
              TLorentzVector vP_Ib;
              TLorentzVector vP_I;
              vP_Ia = Ia_2LNJ->GetFourVector();
              vP_Ib = Ib_2LNJ->GetFourVector();
              vP_CM  = CM_2LNJ->GetFourVector();
              vP_ISR = ISR_2LNJ->GetFourVector();
              vP_I   = vP_Ia + vP_Ib;

              double PTCM = vP_CM.Pt();

              TVector3 boostZ = vP_CM.BoostVector();
              boostZ.SetX(0.);
              boostZ.SetY(0.);

              vP_CM.Boost(-boostZ);
              vP_ISR.Boost(-boostZ);
              vP_I.Boost(-boostZ);

              TVector3 boostT = vP_CM.BoostVector();
              vP_ISR.Boost(-boostT);
              vP_I.Boost(-boostT);

              TVector3 vPt_ISR = vP_ISR.Vect();
              TVector3 vPt_I   = vP_I.Vect();
              vPt_ISR -= vPt_ISR.Dot(boostZ.Unit())*boostZ.Unit();
              vPt_I   -= vPt_I.Dot(boostZ.Unit())*boostZ.Unit();

              double PTISR =  vPt_ISR.Mag();
              double RISR  = -vPt_I.Dot(vPt_ISR.Unit()) / PTISR;
              double PTI = vPt_I.Mag();
              double dphiISRI = fabs(vPt_ISR.Angle(vPt_I));
              double MJ = J_2LNJ->GetMass();
              double MZ = Z_2LNJ->GetMass();
	    
              // finally do the selections
              if (NjS==2 && NjISR>0 && njets > 2 && njets < 5 && signalLeptons[0]->pT()>25. && signalLeptons[1]->pT()>25. && signalJets[0]->pT()>30. && signalJets[1]->pT()>30. && MZ>80. && MZ<100. && MJ>50. && MJ<110. && dphiISRI>2.8 && RISR>0.4 && RISR<0.75 && PTISR>180. && PTI>100. && PTCM<20.)_counters.at("SR2L_ISR").add_event(event);

	      bool cut_preselISR = NjS==2 && NjISR > 0 && njets > 2 && nbjets==0 && njets < 5 && signalLeptons[0]->pT()>25. && signalLeptons[1]->pT()>25. && signalJets[0]->pT()>30. && signalJets[1]->pT()>30.;
	      
		
	      
	      // Fill the ISR cutflow
	      // Note the cutflow table has a mistake in the last cut
	      // (< 30 GeV instead of < 20 GeV)
	      
	      _cutflows["SR2L_ISR"].fillnext({cut_preselISR,
		MZ>80. && MZ<100.,
		MJ>50. && MJ<110.,
		dphiISRI>2.8,
		RISR>0.4 && RISR<0.75,
		PTISR>180.,
		PTI>100.,
       		PTCM<20.}, w);
	    	      
            }

          }

        }


	
      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {

        add_result(SignalRegionData(_counters.at("SR2L_Low"), 39., {42., 9}));
        add_result(SignalRegionData(_counters.at("SR2L_ISR"), 30., {31., 9}));

        COMMIT_CUTFLOWS

        #ifdef CHECK_CUTFLOW
          cout << _cutflows << endl;
          //cout << "n signal leptons before = " << _test2 << endl;
          //cout << "n signal leptons = " << _test[0] << endl;
          //cout << "n baseline leptons = " << _test[1] << endl;
        #endif


      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_2LEPJETS_RJR_139invfb)


  }
}

#endif
#endif
