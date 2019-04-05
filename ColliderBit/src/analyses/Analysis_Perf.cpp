///  \file
///
///  Code to test simulation modules.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Aldo Saavedra
///  \date 2013 June
///
///  \author Martin White
///  \date 2015 Jan
///
///  *********************************************

#include <vector>
#include <algorithm>

#include "gambit/ColliderBit/analyses/BaseAnalysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/cmake/cmake_variables.hpp"

// Only include these headers if ROOT is present
#ifndef EXCLUDE_ROOT
#include "TH1.h"
#include "TVirtualPad.h"
#include "TApplication.h"
#include "TFile.h"
#endif

using namespace std;

namespace Gambit {
  namespace ColliderBit {


    bool SortPt(const HEPUtils::Particle* i, const HEPUtils::Particle* j) { return (i->pT() > j->pT()); }


    class Analysis_Perf : public HEPUtilsAnalysis {
    private:

      #ifndef EXCLUDE_ROOT
      TH1F *_hElectron1Pt, *_hElectron1Eta, *_hElectron1Phi;
      TH1F *_hElectron2Pt, *_hElectron2Eta, *_hElectron2Phi;
      TH1F *_hMuon1Pt;
      TH1F *_hMuon2Pt;
      TH1F *_hNelec, *_hNelec30, *_hNelec100, *_hNelec500;
      TH1F *_hNtau, *_hNtau30, *_hNtau100, *_hNtau500;
      TH1F *_hNmuon, *_hNmuon30, *_hNmuon100, *_hNmuon500;
      TH1F *_hNjet30, *_hNjet100, *_hNjet500;
      TH1F *_hNcentraljet30, *_hNcentraljet100, *_hNcentraljet500;
      TH1F *_hNbjet30, *_hNbjet100, *_hNbjet500;
      TH1F *_hinv, *_hmet, *_hmet_1_muon, *_hmet_1_electron;
      TH1F *_hinv_truth, *_hmet_truth;
      TH1F *_hElectronPt, *_hElectronEta, *_hElectronPhi, *_hElectronE;
      TH1F *_hTauPt, *_hTauEta, *_hTauPhi, *_hTauE;
      TH1F *_hMuonPt, *_hMuonEta, *_hMuonPhi, *_hMuonE;
      TH1F *_hJetPt, *_hJetEta, *_hJetPhi, *_hJetE;
      TH1F *_hCentralJetPt, *_hCentralJetE;
      TH1F *_hBJetPt, *_hBJetEta, *_hBJetPhi, *_hBJetE;

      std::string _output_filename;
      TFile *_ROOToutFile;
      static bool _openTFile;
      bool _hasTFile;
      #endif

    public:

      ~Analysis_Perf() {
        #ifndef EXCLUDE_ROOT
        if(_hasTFile)
          delete _ROOToutFile;
        #endif
      }


      Analysis_Perf() {
        #ifndef EXCLUDE_ROOT

        _output_filename = "SimOutput.root";
        _hasTFile = false;
        if (!Analysis_Perf::_openTFile) {
          std::cout << "Opening ROOT file" << _output_filename << endl;
          _ROOToutFile = new TFile(_output_filename.c_str(), "RECREATE");
          Analysis_Perf::_openTFile = true;
          _hasTFile = true;
        }

        _hElectron1Pt = new TH1F("Electron1Pt", ";Leading e p_{T} [GeV];", 40, 0., 200.);
        _hElectron1Eta = new TH1F("Electron1Eta", ";Leading e #eta;", 40, -5., 5.);
        _hElectron1Phi = new TH1F("Electron1Phi", ";Leading e #phi;", 40, -6.0, 6.0);

        _hElectron2Pt = new TH1F("Electron2Pt","Subleading e p_{T};GeV;", 40, 0., 200.);
        _hElectron2Eta = new TH1F("Electron2Eta","Subleading e #eta;", 40, -5., 5.);
        _hElectron2Phi = new TH1F("Electron2Phi","Subleading e #phi;", 40, -6.0, 6.0);

        _hMuon1Pt = new TH1F("Muon1Pt",";Leading #mu p_{T} [GeV];", 40, 0., 200.);
        _hMuon2Pt = new TH1F("Muon2Pt",";Leading #mu p_{T} [GeV];", 40, 0., 200.);

        _hNelec = new TH1F("Nelec",";N_e/Event", 5, -0.5, 4.5);

        _hNmuon = new TH1F("Nmuon",";N_{#mu}/Event", 5, -0.5, 4.5);

        _hNtau = new TH1F("Ntau",";N_{#tau}/Event", 5, -0.5, 4.5);

        _hNjet30 = new TH1F("Njet30","N_{jet}/Event", 10, -0.5, 9.5);
        _hNjet100 = new TH1F("Njet100","N_{jet}/Event", 10, -0.5, 9.5);
        _hNjet500 = new TH1F("Njet500","N_{jet}/Event", 10, -0.5, 9.5);


        _hNbjet30 = new TH1F("Nbjet30",";N_{bjet}/Event", 10, -0.5, 9.5);
        _hNbjet100 = new TH1F("Nbjet100",";N_{bjet}/Event", 10, -0.5, 9.5);
        _hNbjet500 = new TH1F("Nbjet500",";N_{bjet}/Event", 10, -0.5, 9.5);

        _hNcentraljet30 = new TH1F("Ncentraljet30",";N_{central-jet}/Event", 10, -0.5, 9.5);
        _hNcentraljet100 = new TH1F("Ncentraljet100",";N_{central-jet}/Event", 10, -0.5, 9.5);
        _hNcentraljet500 = new TH1F("Ncentraljet500",";N_{central-jet}/Event", 10, -0.5, 9.5);

        _hinv = new TH1F("Inv","Z invariant mass;GeV", 40, 0, 200);

        _hmet = new TH1F( "MET",";E_{T}^{miss} [GeV]", 50, 0, 1000);
        _hmet_1_muon = new TH1F( "MET_1muon","MET;GeV", 50, 0, 1000);
        _hmet_1_electron = new TH1F( "MET_1electron","MET;GeV", 50, 0, 1000);


        _hmet_truth = new TH1F("METTruth", "MET (truth);GeV", 40, 0, 200);

        _hElectronPt = new TH1F("ElectronPt", ";e p_{T} [GeV];", 50, 0., 500.);
        _hElectronEta = new TH1F("ElectronEta", ";e #eta;", 50, -5., 5.);
        _hElectronPhi = new TH1F("ElectronPhi", ";e #phi;", 50, -6.0, 6.0);
        _hElectronE = new TH1F("ElectronE", ";e E [GeV];", 50, 0., 500.);


        _hTauPt = new TH1F("TauPt", ";#tau p_T [GeV];", 50, 0., 500.);
        _hTauEta = new TH1F("TauEta", ";#tau #eta;", 50, -5., 5.);
        _hTauPhi = new TH1F("TauPhi", ";#tau #phi;", 50, -6.0, 6.0);
        _hTauE = new TH1F("TauE", ";#tau E [GeV];", 50, 0., 500.);

        _hMuonPt = new TH1F("MuonPt",";#mu p_T [GeV];", 50, 0., 500.);
        _hMuonEta = new TH1F("MuonEta",";#mu #eta;", 50, -5., 5.);
        _hMuonPhi = new TH1F("MuonPhi",";#mu #phi;", 50, -6.0, 6.0);
        _hMuonE = new TH1F("MuonE",";#mu E [GeV];", 50, 0., 500.);

        /// @todo Use log/exp binning for E and pT; increase range past 1 TeV?
        _hJetPt = new TH1F("JetPt",";Jet p_{T} [GeV];", 50, 0., 500.);
        _hJetE = new TH1F("JetE",";Jet E [GeV];", 50, 0., 500.);
        _hJetEta = new TH1F("JetEta",";Jet #eta;", 50, -5., 5.);
        _hJetPhi = new TH1F("JetPhi",";Jet #phi;", 50, -6.0, 6.0);
        //
        _hBJetPt = new TH1F("BJetPt",";b-jet p_{T} [GeV];", 50, 0., 500.);
        _hBJetE = new TH1F("BJetE",";b-jet E [GeV];", 50, 0., 500.);
        _hBJetEta = new TH1F("BJetEta","b-jet #eta;", 50, -5., 5.);
        _hBJetPhi = new TH1F("BJetPhi","b-jet #phi;", 50, -6.0, 6.0);
        //
        _hCentralJetPt = new TH1F("CentralJetPt",";Jet p_{T} [GeV];", 50, 0., 500.);
        _hCentralJetE = new TH1F("CentralJetE",";Jet E [GeV];", 50, 0., 500.);
        #endif

      }


      void analyze(const HEPUtils::Event* event) {
        HEPUtilsAnalysis::analyze(event);

        // Now define vectors of baseline objects
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && electron->abseta() < 2.47 &&
              !object_in_cone(*event, *electron, 0.1*electron->pT(), 0.2)) baselineElectrons.push_back(electron);
        }
        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && muon->abseta() < 2.4 &&
              !object_in_cone(*event, *muon, 1.8, 0.2)) baselineMuons.push_back(muon);
        }

        // Get b jets with efficiency and mistag (fake) rates
        vector<HEPUtils::Jet*> baselineJets, bJets; // trueBJets; //for debugging
        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && jet->abseta() < 5.0) baselineJets.push_back(jet);
          if (jet->abseta() < 2.5 && jet->pT() > 20.) {
            const double rnum = HEPUtils::rand01();
            /// @todo Add a special higher-rate b-mistag treatment for charm jets?
            const bool btagged = jet->btag() ? (rnum < 0.75) : (rnum < 0.02);
            if (btagged) bJets.push_back(jet);
          }
        }

        // Overlap removal
        vector<HEPUtils::Particle*> signalElectrons, signalMuons;
        vector<HEPUtils::Particle*> electronsForVeto, muonsForVeto;
        vector<HEPUtils::Jet*> goodJets, signalJets;

        // Note that ATLAS use |eta|<10 for removing jets close to electrons
        // Then 2.8 is used for the rest of the overlap process
        // Then the signal cut is applied for signal jets

        // Remove any jet within dR=0.2 of an electron
        for (HEPUtils::Jet* j : baselineJets) {
          if (!any(baselineElectrons, [&](HEPUtils::Particle* e){ return deltaR_eta(*e, *j) < 0.2; })) {
            if (j->abseta() < 2.8) goodJets.push_back(j);
            if (j->abseta() < 2.5 && j->pT() > 25) signalJets.push_back(j);
          }
        }

        // Remove electrons and muons within dR=0.4 of surviving jets
        for (HEPUtils::Particle* e : baselineElectrons) {
          if (!any(goodJets, [&](const HEPUtils::Jet* j){ return deltaR_eta(*e, *j) < 0.4; })) {
            electronsForVeto.push_back(e);
            if (e->pT() > 10) signalElectrons.push_back(e);
          }
        }
        for (HEPUtils::Particle* m : baselineMuons) {
          if (!any(goodJets, [&](const HEPUtils::Jet* j){ return deltaR_eta(*m, *j) < 0.4; })) {
            muonsForVeto.push_back(m);
            if (m->pT() > 10) signalMuons.push_back(m);
          }
        }

        // Hadronic taus
        vector<HEPUtils::Particle*> signalTaus;
        for (HEPUtils::Particle* tau : event->taus()) {
          if (tau->pT() > 20. && tau->abseta() < 2.47) signalTaus.push_back(tau);
        }
        // Apply Run 2 medium hadronic tau efficiency
        ATLAS::applyTauEfficiencyR2(signalTaus);

        // Do further electron selection
        ATLAS::applyMediumIDElectronSelection(signalElectrons);

        // We now have the signal electrons, muons and jets; fill the histograms


        #ifndef EXCLUDE_ROOT

        // MET
        _hmet->Fill(event->met());

        if(signalElectrons.size()==1 && signalMuons.size()==0)_hmet_1_electron->Fill(event->met());
        if(signalMuons.size()==1 && signalElectrons.size()==0)_hmet_1_muon->Fill(event->met());


        // Electrons
        _hNelec->Fill(signalElectrons.size());

        for (HEPUtils::Particle* electron : signalElectrons) {
          _hElectronPt->Fill(electron->pT());
          _hElectronEta->Fill(electron->eta());
          _hElectronPhi->Fill(electron->phi());
          _hElectronE->Fill(electron->E());
        }

        // Muons
        _hNmuon->Fill(signalMuons.size());
        for (HEPUtils::Particle* muon : signalMuons) {
          _hMuonPt->Fill(muon->pT(),1.);
          _hMuonEta->Fill(muon->eta(),1.);
          _hMuonPhi->Fill(muon->phi(),1.);
          _hMuonE->Fill(muon->E(),1.);
        }

        // Taus

        _hNtau->Fill(signalTaus.size());
        for (HEPUtils::Particle* tau : signalTaus) {
          _hTauPt->Fill(tau->pT(),1.);
          _hTauEta->Fill(tau->eta(),1.);
          _hTauPhi->Fill(tau->phi(),1.);
          _hTauE->Fill(tau->E(),1.);
        }

        // Jets
        int numJets30(0), numJets100(0), numJets500(0);
        int numCentralJets30(0), numCentralJets100(0), numCentralJets500(0);
        int numBJets30(0), numBJets100(0), numBJets500(0);
        for (HEPUtils::Jet* jet : signalJets) {
          // All jets
          if (jet->pT() > 30) numJets30 += 1;
          if (jet->pT() > 100) numJets100 += 1;
          if (jet->pT() > 500) numJets500 += 1;
          _hJetPt->Fill(jet->pT());
          _hJetE->Fill(jet->E());
          _hJetEta->Fill(jet->eta());
          _hJetPhi->Fill(jet->phi());
          // Central jets
          if (jet->abseta() < 2.5) {
            if (jet->pT() > 30) numCentralJets30 += 1;
            if (jet->pT() > 100) numCentralJets100 += 1;
            if (jet->pT() > 500) numCentralJets500 += 1;
            _hCentralJetPt->Fill(jet->pT());
            _hCentralJetE->Fill(jet->E());
          }
          // b-jets
          if (jet->btag()) {
            if (jet->pT() > 30) numBJets30 += 1;
            if (jet->pT() > 100) numBJets100 += 1;
            if (jet->pT() > 500) numBJets500 += 1;
            _hBJetPt->Fill(jet->pT());
            _hBJetE->Fill(jet->E());
            _hBJetEta->Fill(jet->eta());
            _hBJetPhi->Fill(jet->phi());
          }
        }

        // Jet multiplicities
        _hNjet30->Fill(numJets30);
        _hNjet100->Fill(numJets100);
        _hNjet500->Fill(numJets500);
        _hNcentraljet30->Fill(numCentralJets30);
        _hNcentraljet100->Fill(numCentralJets100);
        _hNcentraljet500->Fill(numCentralJets500);
        _hNbjet30->Fill(numBJets30);
        _hNbjet100->Fill(numBJets100);
        _hNbjet500->Fill(numBJets500);


        // Aldo observables:

        if (signalElectrons.size() > 0) {
          _hElectron1Pt->Fill(signalElectrons[0]->pT());
          _hElectron1Eta->Fill(signalElectrons[0]->eta());
          _hElectron1Phi->Fill(signalElectrons[0]->phi());
        }

        if (signalElectrons.size() > 1) {
          HEPUtils::P4 temp = signalElectrons[0]->mom() + signalElectrons[1]->mom();
          _hinv->Fill(temp.m());
          _hElectron2Pt->Fill(signalElectrons[1]->pT());
          _hElectron2Eta->Fill(signalElectrons[1]->eta());
          _hElectron2Phi->Fill(signalElectrons[1]->phi());
        }

        if (signalMuons.size() > 0) _hMuon1Pt->Fill(signalMuons[0]->pT());
        if (signalMuons.size() > 1) _hMuon2Pt->Fill(signalMuons[1]->pT());

        #endif

      }


      /// @todo -> *const* other?
      void add(BaseAnalysis* other) {
        // The base class add function handles the signal region vector and total # events.
        HEPUtilsAnalysis::add(other);

        // Add the subclass member variables
        #ifndef EXCLUDE_ROOT
        Analysis_Perf* specificOther = dynamic_cast<Analysis_Perf*>(other);
        _hElectron1Pt->Add(specificOther->_hElectron1Pt);
        _hElectron1Eta->Add(specificOther->_hElectron1Eta);
        _hElectron1Phi->Add(specificOther->_hElectron1Phi);
        _hElectron2Pt->Add(specificOther->_hElectron2Pt);
        _hElectron2Eta->Add(specificOther->_hElectron2Eta);
        _hElectron2Phi->Add(specificOther->_hElectron2Phi);
        _hMuon1Pt->Add(specificOther->_hMuon1Pt);
        _hMuon2Pt->Add(specificOther->_hMuon2Pt);
        _hNelec->Add(specificOther->_hNelec);
        _hNtau->Add(specificOther->_hNtau);
        _hNmuon->Add(specificOther->_hNelec);
        _hNjet30->Add(specificOther->_hNjet30);
        _hNjet100->Add(specificOther->_hNjet100);
        _hNjet500->Add(specificOther->_hNjet500);
        _hNcentraljet30->Add(specificOther->_hNcentraljet30);
        _hNcentraljet100->Add(specificOther->_hNcentraljet100);
        _hNcentraljet500->Add(specificOther->_hNcentraljet500);
        _hNbjet30->Add(specificOther->_hNbjet30);
        _hNbjet100->Add(specificOther->_hNbjet100);
        _hNbjet500->Add(specificOther->_hNbjet500);
        _hinv->Add(specificOther->_hinv);
        _hmet->Add(specificOther->_hmet);
        _hmet_1_electron->Add(specificOther->_hmet_1_electron);
        _hmet_1_muon->Add(specificOther->_hmet_1_muon);
        _hElectronPt->Add(specificOther->_hElectronPt);
        _hElectronEta->Add(specificOther->_hElectronEta);
        _hElectronPhi->Add(specificOther->_hElectronPhi);
        _hElectronE->Add(specificOther->_hElectronE);
        _hTauPt->Add(specificOther->_hTauPt);
        _hTauEta->Add(specificOther->_hTauEta);
        _hTauPhi->Add(specificOther->_hTauPhi);
        _hTauE->Add(specificOther->_hTauE);
        _hMuonPt->Add(specificOther->_hMuonPt);
        _hMuonEta->Add(specificOther->_hMuonEta);
        _hMuonPhi->Add(specificOther->_hMuonPhi);
        _hMuonE->Add(specificOther->_hMuonE);
        _hJetPt->Add(specificOther->_hJetPt);
        _hJetEta->Add(specificOther->_hJetEta);
        _hJetPhi->Add(specificOther->_hJetPhi);
        _hJetE->Add(specificOther->_hJetE);
        _hCentralJetPt->Add(specificOther->_hCentralJetPt);
        _hCentralJetE->Add(specificOther->_hCentralJetE);
        _hBJetPt->Add(specificOther->_hBJetPt);
        _hBJetEta->Add(specificOther->_hBJetEta);
        _hBJetPhi->Add(specificOther->_hBJetPhi);
        _hBJetE->Add(specificOther->_hBJetE);
        #endif

      }


      void scale(double) {
        // NOTE: previously called finalize, but I got rid of that crap. --Abram

        #ifndef EXCLUDE_ROOT
        if (_hasTFile)
          _ROOToutFile->Write();
        //_ROOToutFile->Close();
        /// @todo We should close the file. Shouldn't we also delete the histo pointers?... or are they owned by the file?
        #endif
      }


      void collect_results() {
        // DO NOTHING

        SignalRegionData dummy;
        dummy.n_observed = 10.;
        dummy.n_background = 10.;
        dummy.background_sys = 1.;
        dummy.signal_sys = 0.;
        dummy.n_signal = 1.;

        add_result(dummy);

      }


   protected:
      void clear() {
        #ifndef EXCLUDE_ROOT
        _hElectron1Pt->Reset();
        _hElectron1Eta->Reset();
        _hElectron1Phi->Reset();
        _hElectron2Pt->Reset();
        _hElectron2Eta->Reset();
        _hElectron2Phi->Reset();
        _hMuon1Pt->Reset();
        _hMuon2Pt->Reset();
        _hNelec->Reset();
        _hNelec30->Reset();
        _hNelec100->Reset();
        _hNelec500->Reset();
        _hNtau->Reset();
        _hNtau30->Reset();
        _hNtau100->Reset();
        _hNtau500->Reset();
        _hNmuon->Reset();
        _hNmuon30->Reset();
        _hNmuon100->Reset();
        _hNmuon500->Reset();
        _hNjet30->Reset();
        _hNjet100->Reset();
        _hNjet500->Reset();
        _hNcentraljet30->Reset();
        _hNcentraljet100->Reset();
        _hNcentraljet500->Reset();
        _hNbjet30->Reset();
        _hNbjet100->Reset();
        _hNbjet500->Reset();
        _hinv->Reset();
        _hmet->Reset();
        _hmet_1_muon->Reset();
        _hmet_1_electron->Reset();
        _hinv_truth->Reset();
        _hmet_truth->Reset();
        _hElectronPt->Reset();
        _hElectronEta->Reset();
        _hElectronPhi->Reset();
        _hElectronE->Reset();
        _hTauPt->Reset();
        _hTauEta->Reset();
        _hTauPhi->Reset();
        _hTauE->Reset();
        _hMuonPt->Reset();
        _hMuonEta->Reset();
        _hMuonPhi->Reset();
        _hMuonE->Reset();
        _hJetPt->Reset();
        _hJetEta->Reset();
        _hJetPhi->Reset();
        _hJetE->Reset();
        _hCentralJetPt->Reset();
        _hCentralJetE->Reset();
        _hBJetPt->Reset();
        _hBJetEta->Reset();
        _hBJetPhi->Reset();
        _hBJetE->Reset();
        #endif
      }

    };


    DEFINE_ANALYSIS_FACTORY(Perf);

    #ifndef EXCLUDE_ROOT
    // Static member initialization
    bool Analysis_Perf::_openTFile = false;
    #endif

  }
}
