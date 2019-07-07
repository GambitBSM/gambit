///
///  \author Rose Kudzman-Blais
///  \date 2017 May
///
///  Checked and minor bug fixes by Martin White
///  Feb 2018
///  *********************************************

// Based on http://cms-results.web.cern.ch/cms-results/public-results/superseded/SUS-16-034/index.html

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

namespace Gambit {
  namespace ColliderBit {

    class Analysis_CMS_13TeV_2OSLEP_confnote_36invfb : public Analysis {
    private:

      // Numbers passing cuts
      double _numSR1, _numSR2, _numSR3, _numSR4, _numSR5, _numSR6, _numSR7, _numSR8, _numSR9;
      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      size_t NCUTS;
      // vector<double> cutFlowVectorCMS_550_200;
      // double xsecCMS_550_200;

      // ofstream cutflowFile;

    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      struct ptComparison {
        bool operator() (HEPUtils::Particle* i,HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison {
        bool operator() (HEPUtils::Jet* i,HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;

      Analysis_CMS_13TeV_2OSLEP_confnote_36invfb() {

        set_analysis_name("CMS_13TeV_2OSLEP_confnote_36invfb");
        set_luminosity(35.9);

        _numSR1=0;
        _numSR2=0;
        _numSR3=0;
        _numSR4=0;
        _numSR5=0;
        _numSR6=0;
        _numSR7=0;
        _numSR8=0;
        _numSR9=0;

        NCUTS=13;
        // xsecCMS_550_200=30.2;

        for (size_t i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          // cutFlowVectorCMS_550_200.push_back(0);
          cutFlowVector_str.push_back("");
        }
      }


      void run(const HEPUtils::Event* event) {

        double met = event->met();

        // Baseline objects
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT()>10. && fabs(electron->eta())<2.5)baselineElectrons.push_back(electron);
        }

        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT()>10. &&fabs(muon->eta())<2.4)baselineMuons.push_back(muon);
        }

        vector<HEPUtils::Particle*> baselinePhotons;
        for (HEPUtils::Particle* photon : event->photons()) {
          if (photon->pT()>25. && fabs(photon->eta())<2.4 && (fabs(photon->eta())<1.4 || fabs(photon->eta())>1.6) && fabs(photon->phi()-event->missingmom().phi())>0.4)baselinePhotons.push_back(photon);
        }

        vector<HEPUtils::Jet*> baselineJets;
        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT()>35. &&fabs(jet->eta())<2.4)baselineJets.push_back(jet);
        }

        // Signal objects
        vector<HEPUtils::Particle*> signalLeptons;
        vector<HEPUtils::Particle*> signalElectrons;
        vector<HEPUtils::Particle*> signalMuons;
        vector<HEPUtils::Jet*> signalJets;
        vector<HEPUtils::Jet*> signalBJets;

        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_el_034_ttbar.pdf
        const vector<double> aEl={0,0.8,1.442,1.556,2.,2.5};
        const vector<double> bEl={0.,25.,30.,40.,50.,10000.};  // Assuming flat efficiency above pT = 200 GeV, where the CMS map stops.
        const vector<double> cEl={0.619,0.669,0.7,0.737,0.79,0.625,0.658,0.72,0.712,0.793,0.338,0.372,0.36,0.365,0.416,0.576,0.531,0.614,0.644,0.712,0.440,0.527,0.585,0.606,0.648};
        HEPUtils::BinnedFn2D<double> _eff2dEl(aEl,bEl,cEl);
        for (size_t iEl=0;iEl<baselineElectrons.size();iEl++) {
          bool isEl=has_tag(_eff2dEl, baselineElectrons.at(iEl)->eta(), baselineElectrons.at(iEl)->pT());
          if (isEl && baselineElectrons.at(iEl)->pT()>20. && (fabs(baselineElectrons.at(iEl)->eta())<1.4 || fabs(baselineElectrons.at(iEl)->eta())>1.6)) signalElectrons.push_back(baselineElectrons.at(iEl));
        }

        //@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/2d_full_pteta_mu_034_ttbar.pdf
        const vector<double> aMu={0,0.9,1.2,2.1,2.4};
        const vector<double> bMu={0.,25.,30.,40.,50.,10000.};  // Assuming flat efficiency above pT = 200 GeV, where the CMS map stops.
        const vector<double> cMu={0.869,0.889,0.91,0.929,0.93,0.857,0.88,0.893,0.937,0.93,0.891,0.894,0.901,0.912,0.927,0.803,0.818,0.817,0.855,0.869};
        HEPUtils::BinnedFn2D<double> _eff2dMu(aMu,bMu,cMu);
        for (size_t iMu=0;iMu<baselineMuons.size();iMu++) {
          bool isMu=has_tag(_eff2dMu, baselineMuons.at(iMu)->eta(), baselineMuons.at(iMu)->pT());
          if (isMu && baselineMuons.at(iMu)->pT()>20. && (fabs(baselineMuons.at(iMu)->eta())<1.4 || fabs(baselineMuons.at(iMu)->eta())>1.6))signalMuons.push_back(baselineMuons.at(iMu));
        }

        sort(baselinePhotons.begin(),baselinePhotons.end(),comparePt);
        for (size_t iJet=0;iJet<baselineJets.size();iJet++) {
          bool overlap=false;
          for (size_t iLe=0;iLe<baselineElectrons.size();iLe++) {
            if (fabs(baselineElectrons.at(iLe)->mom().deltaR_eta(baselineJets.at(iJet)->mom()))<0.4)overlap=true;
          }
          for (size_t iLe=0;iLe<baselineMuons.size();iLe++) {
            if (fabs(baselineMuons.at(iLe)->mom().deltaR_eta(baselineJets.at(iJet)->mom()))<0.4)overlap=true;
          }
          if (baselinePhotons.size()!=0) {
            if (fabs(baselinePhotons.at(0)->mom().deltaR_eta(baselineJets.at(iJet)->mom()))<0.4)overlap=true;
          }
          if (!overlap) {
            signalJets.push_back(baselineJets.at(iJet));
            if (baselineJets.at(iJet)->btag())signalBJets.push_back(baselineJets.at(iJet));
          }
        }
        CMS::applyCSVv2MediumBtagEff(signalBJets);

        signalLeptons=signalElectrons;
        signalLeptons.insert(signalLeptons.end(),signalMuons.begin(),signalMuons.end());
        int nSignalLeptons = signalLeptons.size();
        int nSignalJets = signalJets.size();
        int nSignalBJets = signalBJets.size();
        sort(signalLeptons.begin(),signalLeptons.end(),comparePt);
        sort(signalJets.begin(),signalJets.end(),compareJetPt);
        sort(signalBJets.begin(),signalBJets.end(),compareJetPt);

        // Variables + Preselection
        bool preselection=false;

        double mT2=0;
        double mll=0;
        double mjj=0;
        double mbb=0;
        double pT_j1=0;
        double deltaPhi_met_j0=0;
        double deltaPhi_met_j1=0;

        vector<vector<HEPUtils::Particle*>> SFOSpair_cont = getSFOSpairs(signalLeptons);
        for (size_t iPa=0;iPa<SFOSpair_cont.size();iPa++) {
          vector<HEPUtils::Particle*> pair = SFOSpair_cont.at(iPa);
          sort(pair.begin(),pair.end(),comparePt);
          if (pair.at(0)->pT()>25. && fabs(pair.at(0)->mom().deltaR_eta(pair.at(1)->mom()))>0.1 && (pair.at(0)->mom()+pair.at(1)->mom()).pT()>25)preselection=true;
        }

        if (nSignalBJets>1)mbb=(signalBJets.at(0)->mom()+signalBJets.at(1)->mom()).m();
        if (nSignalJets>0)deltaPhi_met_j0=event->missingmom().deltaPhi(signalJets.at(0)->mom());
        if (nSignalJets>1) {
          pT_j1=signalJets.at(1)->pT();
          deltaPhi_met_j1=event->missingmom().deltaPhi(signalJets.at(1)->mom());
          mjj=get_mjj(signalJets);
        }
        if (nSignalLeptons>1) {
          mll=(signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()).m();
          mT2=get_mT2(signalLeptons,signalBJets,event->missingmom());
        }

        //Signal regions
        if (preselection && mll>86. && mll<96. && met>100. && (nSignalJets==2 || nSignalJets==3)  && (baselineMuons.size()+baselineElectrons.size())==2 && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4) {
          //VZ
          if (nSignalBJets==0 && mT2>80. && mjj<110.) {
            if (met>50. && met<100.)_numSR1++;
            if (met>100. && met<150.)_numSR2++;
            if (met>150. && met<250.)_numSR3++;
            if (met>250. && met<350.)_numSR4++;
            if (met>350.)_numSR5++;
          }
          //HZ
          if (nSignalBJets==2 && mbb<150. && mT2>200.) {
            if (met>50. && met<100.)_numSR6++;
            if (met>100. && met<150.)_numSR7++;
            if (met>150. && met<250.)_numSR8++;
            if (met>250.)_numSR9++;
          }
        }

        cutFlowVector_str[0] = "All events";
        cutFlowVector_str[1] = "$\\geq$ 2 SFOS leptons with (sub)leading $p_{T} > 25(20) GeV$";
        cutFlowVector_str[2] = "Extra lepton vetos";
        cutFlowVector_str[3] = "$86 < m_{ll} < 96 GeV$";
        cutFlowVector_str[4] = "2-3 Jets";
        cutFlowVector_str[5] = "$\\Delta\\Phi(E^{miss}_{T},j_{0}),\\Delta\\Phi(E^{miss}_{T},j_{1}) > 0.4$";
        cutFlowVector_str[6] = "Btag veto";
        cutFlowVector_str[7] = "$M_{T2}(ll) > 80 GeV$";
        cutFlowVector_str[8] = "$M_{jj}$ for min $\\Delta\\Phi$ jets $< 150 GeV$";
        cutFlowVector_str[9] = "$E^{miss}_{T} > 100 GeV$";
        cutFlowVector_str[10] = "$E^{miss}_{T} > 150 GeV$";
        cutFlowVector_str[11] = "$E^{miss}_{T} > 250 GeV$";
        cutFlowVector_str[12] = "$E^{miss}_{T} > 350 GeV$";

        // cutFlowVectorCMS_550_200[0] = 109.35;
        // cutFlowVectorCMS_550_200[1] = 24.21;
        // cutFlowVectorCMS_550_200[2] = 18.37;
        // cutFlowVectorCMS_550_200[3] = 14.13;
        // cutFlowVectorCMS_550_200[4] = 11.98;
        // cutFlowVectorCMS_550_200[5] = 10.95;
        // cutFlowVectorCMS_550_200[6] = 9.92;
        // cutFlowVectorCMS_550_200[7] = 8.04;
        // cutFlowVectorCMS_550_200[8] = 5.62;
        // cutFlowVectorCMS_550_200[9] = 5.41;
        // cutFlowVectorCMS_550_200[10] = 4.96;
        // cutFlowVectorCMS_550_200[11] = 3.59;
        // cutFlowVectorCMS_550_200[12] = 1.94;

        for (size_t j=0;j<NCUTS;j++){
          if(
             (j==0) ||

             (j==1 && preselection) ||

             (j==2 && preselection && (baselineMuons.size()+baselineElectrons.size())==2) ||

             (j==3 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96.) ||

             (j==4 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && (nSignalJets==2 || nSignalJets==3) && pT_j1>35.) ||

             (j==5 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && (nSignalJets==2 || nSignalJets==3) && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4) ||

             (j==6 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && (nSignalJets==2 || nSignalJets==3) && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0) ||
             (j==7 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && (nSignalJets==2 || nSignalJets==3) && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80.) ||

             (j==8 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && (nSignalJets==2 || nSignalJets==3) && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80. && mjj<150.) ||

             (j==9 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && (nSignalJets==2 || nSignalJets==3) && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80. && mjj<150. && met>100.) ||

             (j==10 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && (nSignalJets==2 || nSignalJets==3) && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80. && mjj<150. && met>150.) ||

             (j==11 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && (nSignalJets==2 || nSignalJets==3) && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80. && mjj<150. && met>250.) ||

             (j==12 && preselection && (baselineMuons.size()+baselineElectrons.size())==2 &&  mll>86. && mll<96. && (nSignalJets==2 || nSignalJets==3) && pT_j1>35. && deltaPhi_met_j0>0.4 && deltaPhi_met_j1>0.4 && nSignalBJets==0 && mT2>80. && mjj<150. && met>350.) )

          cutFlowVector[j]++;
        }

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_CMS_13TeV_2OSLEP_confnote_36invfb* specificOther
                = dynamic_cast<const Analysis_CMS_13TeV_2OSLEP_confnote_36invfb*>(other);

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
        for (size_t j = 0; j < NCUTS; j++) {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }
        _numSR1 += specificOther->_numSR1;
        _numSR2 += specificOther->_numSR2;
        _numSR3 += specificOther->_numSR3;
        _numSR4 += specificOther->_numSR4;
        _numSR5 += specificOther->_numSR5;
        _numSR6 += specificOther->_numSR6;
        _numSR7 += specificOther->_numSR7;
        _numSR8 += specificOther->_numSR8;
        _numSR9 += specificOther->_numSR9;
      }


      void collect_results() {

        // string path = "ColliderBit/results/cutflow_";
        // path.append(analysis_name());
        // path.append(".txt");
        // cutflowFile.open(path.c_str());

       //  cutflowFile<<"\\begin{table}[H] \n\\caption{$\\tilde{\\chi}_{1}^{\\pm}\\tilde{\\chi}_{2}^{0}$ decay via $W/Z, [\\tilde{\\chi}_{2}^{0}\\tilde{\\chi}_{1}^{\\pm},\\tilde{\\chi}_{1}^{0}]: [550,200] [GeV]$} \n\\makebox[\\linewidth]{ \n\\renewcommand{\\arraystretch}{0.4} \n\\begin{tabular}{c c c c c} \n\\hline"<<endl;
       //  cutflowFile<<"& CMS & GAMBIT & GAMBIT/CMS & $\\sigma$-corrected GAMBIT/CMS \\\\ \\hline"<<endl;
       //  cutflowFile<<"$\\sigma (pp\\to \\tilde{\\chi}_{1}^{\\pm}, \\tilde{\\chi}_{2}^{0})$ &"<<setprecision(4)<<xsecCMS_550_200<<" $fb$ &"<<setprecision(4)<<xsec()<<"$fb$ &"<<setprecision(4)<<xsec()/xsecCMS_550_200<<" & 1\\\\ \\hline"<<endl;
       //  cutflowFile<<"\\multicolumn{5}{c}{Expected events at 35.9 $fb^{-1}$} \\\\ \\hline"<<endl;
       //  for (size_t i=0; i<NCUTS; i++) {
       //    cutflowFile<<cutFlowVector_str[i]<<"&"<<setprecision(4)<<cutFlowVectorCMS_550_200[i]<<"&"<<setprecision(4)<<cutFlowVector[i]*xsec_per_event()*luminosity()<<"&"<<setprecision(4)<<cutFlowVector[i]*xsec_per_event()*luminosity()/cutFlowVectorCMS_550_200[i]<<"&"<<setprecision(4)<<(xsecCMS_550_200/xsec())*cutFlowVector[i]*xsec_per_event()*luminosity()/cutFlowVectorCMS_550_200[i]<<"\\\\"<< endl;
       //  }
       //  cutflowFile<<"\\hline \\multicolumn{5}{c}{Percentage (\\%)} \\\\ \\hline"<<endl;
       //  for (size_t i=0; i<NCUTS; i++) {
       //    cutflowFile<<cutFlowVector_str[i]<<"&"<<setprecision(4)<<cutFlowVectorCMS_550_200[i]*100./cutFlowVectorCMS_550_200[1]<<"&"<<setprecision(4)<<cutFlowVector[i]*100./cutFlowVector[1]<<"& - & -\\\\"<< endl;
       //  }
       //  cutflowFile<<"\\end{tabular} \n} \n\\end{table}"<<endl;
       // cutflowFile.close();

        // Only 7 of the 9 signal regions are included in the covariance matrix
        // (SR1 and SR6 are left out)
        static const size_t SR_size_cov = 7;
        const int SR_labels_cov[SR_size_cov] = {2, 3, 4, 5, 7, 8, 9};
        const double SR_nums_cov[SR_size_cov] = {
          _numSR2, _numSR3, _numSR4, _numSR5, _numSR7, _numSR8, _numSR9,
        };

        // Observed event counts
        static const double OBSNUM[SR_size_cov] = {
          57., 29., 2., 0., 9., 5., 1.
        };
        // Background estimates
        static const double BKGNUM[SR_size_cov] = {
          54.9, 21.6, 6., 2.5, 7.6, 5.6, 1.3
        };
        // Background uncertainties, same-flavor signal regions
        static const double BKGERR[SR_size_cov] = {
          7., 5.6, 1.9, 0.9, 2.8, 1.6, 0.4,
        };

        for (size_t ibin = 0; ibin < SR_size_cov; ++ibin) {
          stringstream ss; ss << "SR-" << SR_labels_cov[ibin];
          add_result(SignalRegionData(ss.str(), OBSNUM[ibin], {SR_nums_cov[ibin], 0.}, {BKGNUM[ibin], BKGERR[ibin]}));
        }

        // Covariance matrix
        static const vector< vector<double> > BKGCOV = {
          { 52.8, 12.7,  3.0,  1.2,  4.5,  5.1,  1.2 },
          { 12.7, 41.4,  3.6,  2.0,  2.5,  2.0,  0.7 },
          {  3.0,  3.6,  1.6,  0.6,  0.4,  0.3,  0.1},
          {  1.2,  2.0,  0.6,  1.1,  0.3,  0.1,  0.1},
          {  4.5,  2.5,  0.4,  0.3,  6.5,  1.8,  0.4},
          {  5.1,  2.0,  0.3,  0.1,  1.8,  2.4,  0.4},
          {  1.2,  0.7,  0.1,  0.1,  0.4,  0.4,  0.2},
        };

        set_covariance(BKGCOV);

      }

        // //Now fill a results object with the results for each SR
        // SignalRegionData results_SR1;
        // results_SR1.sr_label = "SR1";
        // results_SR1.n_observed = 793.;
        // results_SR1.n_background = 793.;
        // results_SR1.background_sys = 32.2;
        // results_SR1.signal_sys = 0.;
        // results_SR1.n_signal = _numSR1;
        // add_result(results_SR1);

        // SignalRegionData results_SR2;
        // results_SR2.sr_label = "SR2";
        // results_SR2.n_observed = 57.;
        // results_SR2.n_background = 54.9;
        // results_SR2.background_sys = 7.;
        // results_SR2.signal_sys = 0.;
        // results_SR2.n_signal = _numSR2;
        // add_result(results_SR2);

        // SignalRegionData results_SR3;
        // results_SR3.sr_label = "SR3";
        // results_SR3.n_observed = 29.;
        // results_SR3.n_background = 21.6;
        // results_SR3.background_sys = 5.6;
        // results_SR3.signal_sys = 0.;
        // results_SR3.n_signal = _numSR3;
        // add_result(results_SR3);

        // SignalRegionData results_SR4;
        // results_SR4.sr_label = "SR4";
        // results_SR4.n_observed = 2.;
        // results_SR4.n_background = 6.;
        // results_SR4.background_sys = 1.9;
        // results_SR4.signal_sys = 0.;
        // results_SR4.n_signal = _numSR4;
        // add_result(results_SR4);

        // SignalRegionData results_SR5;
        // results_SR5.sr_label = "SR5";
        // results_SR5.n_observed = 0.;
        // results_SR5.n_background = 2.5;
        // results_SR5.background_sys = 0.9;
        // results_SR5.signal_sys = 0.;
        // results_SR5.n_signal = _numSR5;
        // add_result(results_SR5);

        // SignalRegionData results_SR6;
        // results_SR6.sr_label = "SR6";
        // results_SR6.n_observed = 82;
        // results_SR6.n_background = 82.;
        // results_SR6.background_sys = 9.5;
        // results_SR6.signal_sys = 0.;
        // results_SR6.n_signal = _numSR6;
        // add_result(results_SR6);

        // SignalRegionData results_SR7;
        // results_SR7.sr_label = "SR7";
        // results_SR7.n_observed = 9.;
        // results_SR7.n_background = 7.6;
        // results_SR7.background_sys = 2.8;
        // results_SR7.signal_sys = 0.;
        // results_SR7.n_signal = _numSR7;
        // add_result(results_SR7);

        // SignalRegionData results_SR8;
        // results_SR8.sr_label = "SR8";
        // results_SR8.n_observed = 5.;
        // results_SR8.n_background = 5.6;
        // results_SR8.background_sys = 1.6;
        // results_SR8.signal_sys = 0.;
        // results_SR8.n_signal = _numSR8;
        // add_result(results_SR8);

        // SignalRegionData results_SR9;
        // results_SR9.sr_label = "SR9";
        // results_SR9.n_observed = 1.;
        // results_SR9.n_background = 1.3;
        // results_SR9.background_sys = 0.4;
        // results_SR9.signal_sys = 0.;
        // results_SR9.n_signal = _numSR9;
        // add_result(results_SR9);

      // }



      double get_mjj(vector<HEPUtils::Jet*> jets) {
        double mjj=0;
        double deltaPhi_min=999;
        for (size_t iJet1=0;iJet1<jets.size();iJet1++) {
          for (size_t iJet2=0;iJet2<jets.size();iJet2++) {
             if (iJet1!=iJet2) {
               double deltaPhi=fabs(jets.at(iJet1)->phi()-jets.at(iJet2)->phi());
               if (deltaPhi<deltaPhi_min) {
                 mjj=(jets.at(iJet1)->mom()+jets.at(iJet2)->mom()).m();
                 deltaPhi_min=deltaPhi;
               }
             }
           }
        }
        return mjj;
      }

      double get_mT2(vector<HEPUtils::Particle*> leptons, vector<HEPUtils::Jet*> bjets, HEPUtils::P4 met) {
        double mT2=0;
        if (bjets.size()<2) {
          double pLep0[3] = {leptons.at(0)->mass(), leptons.at(0)->mom().px(), leptons.at(0)->mom().py()};
          double pLep1[3] = {leptons.at(1)->mass(), leptons.at(1)->mom().px(), leptons.at(1)->mom().py()};
          double pMiss[3] = {0., met.px(), met.py() };
          double mn = 0.;

          mt2_bisect::mt2 mt2_calc;
          mt2_calc.set_momenta(pLep0,pLep1,pMiss);
          mt2_calc.set_mn(mn);
          mT2 = mt2_calc.get_mt2();
        }
        if (bjets.size()>1) {
          mT2=999;
          for (size_t iJet=0;iJet<bjets.size();iJet++) {
            for (size_t iLep=0;iLep<leptons.size();iLep++) {
              double pLep[3] = {leptons.at(iLep)->mass(), leptons.at(iLep)->mom().px(), leptons.at(iLep)->mom().py()};
              double pJet[3] = {bjets.at(iJet)->mass(), bjets.at(iJet)->mom().px(), bjets.at(iJet)->mom().py()};
              double pMiss[3] = {0., met.px(), met.py() };
              double mn = 0.;

              mt2_bisect::mt2 mt2_calc;
              mt2_calc.set_momenta(pLep,pJet,pMiss);
              mt2_calc.set_mn(mn);
              double mT2_temp = mt2_calc.get_mt2();
              if (mT2_temp<mT2)mT2=mT2_temp;
            }
          }
        }
        return mT2;
      }


    protected:
      void analysis_specific_reset() {
        _numSR1=0;
        _numSR2=0;
        _numSR3=0;
        _numSR4=0;
        _numSR5=0;
        _numSR6=0;
        _numSR7=0;
        _numSR8=0;
        _numSR9=0;

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2OSLEP_confnote_36invfb)


  }
}
