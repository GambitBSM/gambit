///
///  \author Tomas Gonzalo
///  \date 2023 Aug
///
///  *********************************************

// Based on https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-18-004/index.html

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <fstream>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_CMS_13TeV_2LEPsoft_137invfb : public Analysis
    {

      public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_13TeV_2LEPsoft_137invfb()
      {
        //std::cout << "constructor" << std::endl;
        DEFINE_SIGNAL_REGIONS("2lEWlow", 4, "2 leptons",  "pT(l2) > 3.5 (5) GeV for muon (electron)", "4 GeV < mll < 50 GeV", "Y veto", "pT(ll) > 3 GeV", "1 jet", "2/3 < met/HT < 1.4", "HT > 100 GeV", "met > 125 GeV && 125 GeV < metcorr < 200 GeV", "trigger path combination (low)", "OS leptons", "5 GeV < pT(l1) < 30 GeV", "Tight lepton ID", "No b-jets", "m(tautau) < 0. or m(tautau) > 160.", "MT(l1, met) < 70. GeV && MT(l2, met) < 70.0 GeV", "SF leptons", "2 muons", "pT(l2) > 5 GeV")
        DEFINE_SIGNAL_REGIONS("2lEWmed", 5, "2 leptons", "pT(l2) > 3.5 (5) GeV for muon (electron)", "Y veto", "pT(ll) > 3 GeV", "1 jet", "2/3 < met/HT < 1.4", "HT > 100 GeV", "200 GeV < metcorr < 240 GeV", "trigger path combination (med)", "OS leptons", "Tight lepton ID", "No b-jets", "m(tautau) < 0. or m(tautau) > 160.", "MT(l1, met) < 70. GeV && MT(l2, met) < 70.0 GeV", "SF leptons", "1 GeV < mll < 50 GeV", "J/Psi veto", "3.5 (5) GeV < pT(l1) < 30.0 GeV", "deltaR < 0.3")
        DEFINE_SIGNAL_REGIONS("2lEWhigh",5, "2 leptons", "pT(l2) > 3.5 (5) GeV for muon (electron)", "Y veto", "pT(ll) > 3 GeV", "1 jet", "2/3 < met/HT < 1.4", "HT > 100 GeV", "240 GeV < metcorr < 290 GeV", "trigger path combination (high)", "OS leptons", "Tight lepton ID", "No b-jets", "m(tautau) < 0. or m(tautau) > 160.", "MT(l1, met) < 70. GeV && MT(l2, met) < 70.0 GeV", "SF leptons", "1 GeV < mll < 50 GeV", "J/Psi veto", "3.5 (5) GeV < pT(l1) < 30.0 GeV", "deltaR < 0.3")
        DEFINE_SIGNAL_REGIONS("2lEWultra", 5, "2 leptons", "pT(l2) > 3.5 (5) GeV for muon (electron)", "Y veto", "pT(ll) > 3 GeV", "1 jet", "2/3 < met/HT < 1.4", "HT > 100 GeV", "290 GeV < metcorr", "trigger path combination (ultra)", "OS leptons", "Tight lepton ID", "No b-jets", "m(tautau) < 0. or m(tautau) > 160.", "MT(l1, met) < 70. GeV && MT(l2, met) < 70.0 GeV", "SF leptons", "1 GeV < mll < 50 GeV", "J/Psi veto", "3.5 (5) GeV < pT(l1) < 30.0 GeV", "deltaR < 0.3")
        DEFINE_SIGNAL_REGIONS("2lSTlow", 6, "2 leptons", "pT(l2) > 3.5 (5) GeV for muon (electron)", "4 GeV < mll < 50 GeV","Y veto", "pT(ll) > 3 GeV", "1 jet", "2/3 < met/HT < 1.4", "HT > 100 GeV", "met > 125 GeV && 125 GeV < metcorr < 200 GeV", "trigger path combination (low)","OS leptons", "5 GeV < pT(l1) < 30 GeV", "Tight lepton ID", "No b-jets", "m(tautau) < 0. or m(tautau) > 160.",  "2 muons", "pT(l2) > 5 GeV")
        DEFINE_SIGNAL_REGIONS("2lSTmed", 6, "2 leptons", "pT(l2) > 3.5 (5) GeV for muon (electron)", "Y veto", "pT(ll) > 3 GeV", "1 jet", "2/3 < met/HT < 1.4", "HT > 100 GeV", "200 GeV < metcorr < 240 GeV", "trigger path combination (med)", "OS leptons", "Tight lepton ID", "No b-jets", "m(tautau) < 0. or m(tautau) > 160.", "1 GeV < mll < 50 GeV", "J/Psi veto", "3.5 (5) GeV < pT(l1) < 30.0 GeV", "deltaR < 0.3")
        DEFINE_SIGNAL_REGIONS("2lSThigh", 6, "2 leptons", "pT(l2) > 3.5 (5) GeV for muon (electron)", "Y veto", "pT(ll) > 3 GeV", "1 jet", "2/3 < met/HT < 1.4", "HT > 100 GeV", "240 GeV < metcorr < 290 GeV", "trigger path combination (high)", "OS leptons", "Tight lepton ID", "No b-jets", "m(tautau) < 0. or m(tautau) > 160.", "1 GeV < mll < 50 GeV", "J/Psi veto", "3.5 (5) GeV < pT(l1) < 30.0 GeV", "deltaR < 0.3")
        DEFINE_SIGNAL_REGIONS("2lSTultra",6, "2 leptons", "pT(l2) > 3.5 (5) GeV for muon (electron)", "Y veto", "pT(ll) > 3 GeV", "1 jet", "2/3 < met/HT < 1.4", "HT > 100 GeV", "290 GeV < metcorr", "trigger path combination (ultra)", "OS leptons", "Tight lepton ID", "No b-jets", "m(tautau) < 0. or m(tautau) > 160.", "1 GeV < mll < 50 GeV", "J/Psi veto", "3.5 (5) GeV < pT(l1) < 30.0 GeV", "deltaR < 0.3")
        DEFINE_SIGNAL_REGIONS("3lEWlow", 4, "3 leptons", "pT(l2) > 3.5 (5) for muon (electron)", "pT(l3) > 3.5 (5) for muon (electron)", "Y veto", "HT > 100 GeV", "met > 125 GeV && 125 GeV < metcorr < 200 GeV", "trigger path combination (low)", "1 OS SF pair", "4 GeV < min(MSFOS(ll)) < 50 GeV", "5 GeV < pT(l1) < 30.0 GeV", "Tight lepton ID", "No b-jets", "pT(l2) > 5 GeV", "2 muons", "max(MSFOS(ll) < 60 GeV") //TODO: Should the last cut be for any sign?
        DEFINE_SIGNAL_REGIONS("3lEWmed", 5, "3 leptons", "pT(l2) > 3.5 (5) for muon (electron)", "pT(l3) > 3.5 (5) for muon (electron)", "Y veto", "HT > 100 GeV", "200 GeV < metcorr", "trigger path combination (med)", "1 OS SF pair", "Tight lepton ID", "No b-jets", "1 GeV < min(MSFOS(ll) < 50 GeV", "J/Psi veto", "deltaR < 0.3", "3.5 (5) GeV < pT(l1) < 30.0 GeV")

        set_analysis_name("CMS_13TeV_2LEPsoft_137invfb");
        set_luminosity(137.);
      }

      void run(const HEPUtils::Event* event)
      {
        //std::cout << "run" << std::endl;

        //////////////////////
        // Baseline objects //

        BASELINE_PARTICLES(event->electrons(), baselineElectrons, 5., 0., 30., 2.5, CMS::eff2DEl.at("SUS-18-004"))
        BASELINE_PARTICLES(event->muons(), baselineMuons, 3.5, 0., 30., 2.4, CMS::eff2DMu.at("SUS-18-004"))
        BASELINE_PARTICLE_COMBINATION(baselineLeptons, baselineElectrons, baselineMuons)
        BASELINE_JETS(event->jets("antikt_R04"), baselineJets, 25., 0., DBL_MAX, 2.4)
        BASELINE_BJETS(event->jets("antikt_R04"), baselineBJets, 25., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("DeepCSVMedium"), CMS::misIDBJet.at("DeepCSVMedium"))

        size_t nBaselineMuons = baselineMuons.size();

        ////////////////////
        // Signal objects //
        SIGNAL_PARTICLES(baselineElectrons, signalElectrons)
        SIGNAL_PARTICLES(baselineMuons, signalMuons)
        SIGNAL_JETS(baselineJets, signalJets)
        SIGNAL_JETS(baselineBJets, signalBJets)

        // Construct signal leptons by only adding signal electrons and muons that satisfy isolation requirements
        // From the 36 invfb paper (1801.01846) I gather that the isolation criteria are:
        // - absolute: pT sum of other charged particle tracks (leptons?) within DeltaR < 0.3 < 5 GeV
        // - relative: pT sum of other charged particle tracks (leptons?) within DeltaR < 0.3 / pT < 0.5
        std::vector<const HEPUtils::Particle*> signalLeptons;
        for(auto &lep1: baselineLeptons)
        {
          double pTsum = 0;
          for(auto &lep2: baselineLeptons)
            if(lep1 != lep2 and deltaR_eta(lep1->mom(), lep2->mom()) < 0.3)
              pTsum += lep2->pT();
          for(auto &jet: baselineJets)
            if(deltaR_eta(lep1->mom(), jet->mom()) < 0.3)
              pTsum += jet->pT();

          if(pTsum < 5. and pTsum/lep1->pT() < 0.5)
            signalLeptons.push_back(lep1);
        }
        sortByPt(signalLeptons);



        // Pairs containers
        // - OS pairs, unique and ordered from lowest invariant mass
        std::vector<std::vector<const HEPUtils::Particle*> > OSpairs = getOSpairs(signalLeptons);
        uniquePairs(OSpairs);
        sortByParentMass(OSpairs, 0);

        // - OSSF pairs, unique and ordered from lowest invariant mass
        std::vector<std::vector<const HEPUtils::Particle*> > OSSFpairs = getSFOSpairs(signalLeptons);
        uniquePairs(OSSFpairs);
        sortByParentMass(OSSFpairs, 0);

        // - SF pairs, unique and ordered from highest invariant mass
        std::vector<std::vector<const HEPUtils::Particle*> > SFpairs = getSFpairs(signalLeptons);
        uniquePairs(SFpairs);
        sortByParentMass(SFpairs, DBL_MAX);


        ///////////////////////////////
        // Common variables and cuts //

        double met = event->met();
        P4 mmom = event->missingmom();

        size_t nSignalLeptons = signalLeptons.size();
        size_t nSignalMuons = signalMuons.size();
        size_t nSignalJets = signalJets.size();
        size_t nSignalBJets = signalBJets.size();
        size_t nOSpairs = OSpairs.size();
        size_t nOSSFpairs = OSSFpairs.size();
        size_t nSFpairs = SFpairs.size();

        // Muon corrected ETmiss
        double metcorr = met;
        for(auto& muon : signalMuons)
          metcorr += sqrt(muon->mom().px() * muon->mom().px() + muon->mom().py() * muon->mom().py());

        // Invariant mass of the lowest-mass OS dilepton pair
        double mllOS = 0.;
        if(nOSpairs > 0) mllOS = (OSpairs.at(0).at(0)->mom() + OSpairs.at(0).at(1)->mom()).m();

        // Invariant mass of the lowest-mass OSSF dilepton pair
        double mllOSSF = 0.;
        if(nOSSFpairs > 0) mllOSSF = (OSSFpairs.at(0).at(0)->mom() + OSSFpairs.at(0).at(1)->mom()).m();

        // Invariant mass of the highest-mass SF dilepton pair
        double mllSF = 0.;
        if(nSFpairs > 0) mllSF = (SFpairs.at(0).at(0)->mom() + SFpairs.at(0).at(1)->mom()).m();

        // Transverse momentum of the lepton pair, only relevant for two leptons
        double pTll = 0.;
        if(nSignalLeptons == 2) pTll = (signalLeptons.at(0)->mom() + signalLeptons.at(1)->mom()).pT();

        // Scalar sum of transverse hadronic energy
        double HT = 0.;
        for (auto& jet: signalJets)
          HT += jet->pT();

        /// Veto events with invariant mass in the Y-meson or J/psi-meson mass range
        // Need this computed using the OS and OSSF pairs because the 2lST high MET region does not require having SF pairs
        bool JPsivetoOS = false;
        bool JPsivetoOSSF = false;
        bool YvetoOS = false;
        bool YvetoOSSF = false;
        if(nOSpairs > 0 and mllOS > 3. and mllOS < 3.2)
          JPsivetoOS = true;
        if(nOSSFpairs > 0 and mllOSSF > 3. and mllOSSF < 3.2)
          JPsivetoOSSF = true;
        if(nOSpairs > 0 and mllOS > 9. and mllOS < 10.5)
          YvetoOS = true;
        if(nOSSFpairs > 0 and mllOSSF > 9. and mllOSSF < 10.5)
          YvetoOSSF = true;

        // TODO: "Tight lepton veto" requirement: no idea how to implement
        bool tight_lepton_id = true;

        // Invariant mass of leptonic-decaying tau pairs
        double mTauTau=0;
        if (nSignalLeptons == 2 and nOSSFpairs > 0)
        {
          double determinant = signalLeptons.at(0)->mom().px() * signalLeptons.at(1)->mom().py() - signalLeptons.at(0)->mom().py() * signalLeptons.at(1)->mom().px();
          double xi_1 = (mmom.px() * signalLeptons.at(1)->mom().py() - signalLeptons.at(1)->mom().px() * mmom.py()) / determinant;
          double xi_2 = (mmom.py() * signalLeptons.at(0)->mom().px() - signalLeptons.at(0)->mom().py() * mmom.px()) / determinant;
          mTauTau = (1.+xi_1) * (1.+xi_2) * 2. * signalLeptons.at(0)->mom().dot(signalLeptons.at(1)->mom());
          if(mTauTau > 0) mTauTau = sqrt(mTauTau);
          if(mTauTau < 0) mTauTau = -sqrt(-mTauTau);
        }

        // Transverse mass between each lepton and MET, ordered from largest to smallest
        std::vector<double> mT;
        for(auto& lep: signalLeptons)
          mT.push_back(sqrt(2. * lep->pT() * met * (1. - cos(lep->phi() - mmom.phi())) ));
        std::sort(mT.rbegin(), mT.rend());   // note: reverse iterators


        // Delta R of different leptons, ordered from smallest to largest
        std::vector<double> DeltaRll;
        for(auto &ospair : OSpairs)
          DeltaRll.push_back(deltaR_eta(ospair.at(0)->mom(), ospair.at(1)->mom()));
        std::sort(DeltaRll.begin(), DeltaRll.end());

        // Trigger paths
        bool trigger_path_1 = metcorr > 120;
        // TODO: Using baseline muons for this as otherwise the dimuon cut will be useless
        bool trigger_path_2 = metcorr > 60. and met > 50. and  nBaselineMuons >= 2 and baselineMuons.at(0)->pT() > 3 and baselineMuons.at(1)->pT() > 3 and
             (baselineMuons.at(0)->mom() + baselineMuons.at(1)->mom()).m() > 3.8 and  (baselineMuons.at(0)->mom() + baselineMuons.at(1)->mom()).m() < 56;
        // TODO: Trigger path only important for WZ regions, check if it matters
        //bool trigger_path_3 = metcorr > 60. and met > 50. and  nSignalMuons > 2 and signalMuons.at(0)->pT() > 17 and signalMuons.at(1)->pT() > 8;
        //if(not trigger_path_1 and not trigger_path_2/* and not trigger_path_3*/) return;


        ///////////////////
        // Preselection //
        BEGIN_PRESELECTION
        END_PRESELECTION

        //if(nSignalLeptons < 2 or nSignalLeptons > 3) return;
        //if(nOSpairs < 1) return;

        ////////////////////
        // Signal Regions //

        // 2lEW, low MET,  signal regions
        bool cuts = true;
        cuts = cuts and nSignalLeptons == 2;
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and ( (amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5) );
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (mllOSSF > 4. and mllOSSF < 50.);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (not YvetoOSSF);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (pTll > 3.);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (nSignalJets > 0);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (metcorr/HT > 2./3 and metcorr/HT < 1.4);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (HT > 100.);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (met > 125. and metcorr > 125. and metcorr < 200.);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (trigger_path_2);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (nOSpairs > 0);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (signalLeptons.at(0)->pT() > 5. and signalLeptons.at(0)->pT() < 30.);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (tight_lepton_id);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (nSignalBJets == 0);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and ((mTauTau <= 0 or mTauTau >= 160));
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (mT[0] < 70.);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (nOSSFpairs > 0);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (nSignalMuons == 2);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        cuts = cuts and (signalLeptons.at(1)->pT() > 5.);
        LOG_CUTS_N(cuts, "2lEWlow", 4)
        if(cuts)
        {
          if(mllOSSF > 4.  and mllOSSF <= 10.) { FILL_SIGNAL_REGION("2lEWlow1"); }
          if(mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("2lEWlow2"); }
          if(mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("2lEWlow3"); }
          if(mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("2lEWlow4"); }
        }
        //std::cout << "2l low done" << std::endl;

        // 2lEW, med MET, signal regions
        cuts = true;
        cuts = cuts and nSignalLeptons == 2;
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and ( (amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5) );
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (not YvetoOSSF);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (pTll > 3);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (nSignalJets > 0);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (metcorr/HT  > 2./3 and metcorr/HT < 1.4);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (HT > 100.);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (metcorr > 200. and metcorr < 240.);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (trigger_path_1);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (nOSpairs > 0);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (tight_lepton_id);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (nSignalBJets == 0);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (mTauTau <= 0 or mTauTau >= 160);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (mT[0] < 70.);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (nOSSFpairs > 0);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (mllOSSF > 1. and mllOSSF < 50.);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (not JPsivetoOSSF);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (((amIanElectron(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 5.) or (amIaMuon(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 3.5) ) and signalLeptons.at(0)->pT() < 30.);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        cuts = cuts and (DeltaRll[0] > 0.3);
        LOG_CUTS_N(cuts, "2lEWmed", 5)
        if(cuts)
        {
          if(mllOSSF > 1.  and mllOSSF <=  4.) { FILL_SIGNAL_REGION("2lEWmed1"); }
          if(mllOSSF > 4.  and mllOSSF <= 10.) { FILL_SIGNAL_REGION("2lEWmed2"); }
          if(mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("2lEWmed3"); }
          if(mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("2lEWmed4"); }
          if(mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("2lEWmed5"); }
        }
        //std::cout << "2l med done" << std::endl;

        // 2lEW, high MET, signal regions
        cuts = true;
        cuts = cuts and nSignalLeptons == 2;
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and ( (amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5) );
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (not YvetoOSSF);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (pTll > 3);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (nSignalJets > 0);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (metcorr/HT  > 2./3 and metcorr/HT < 1.4);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (HT > 100.);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (metcorr > 240. and metcorr <= 290.);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (trigger_path_1);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (nOSpairs > 0);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (tight_lepton_id);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (nSignalBJets == 0);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (mTauTau <= 0 or mTauTau >= 160);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (mT[0] < 70.);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (nOSSFpairs > 0);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (mllOSSF > 1. and mllOSSF < 50.);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (not JPsivetoOSSF);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (((amIanElectron(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 5.) or (amIaMuon(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 3.5) ) and signalLeptons.at(0)->pT() < 30.);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        cuts = cuts and (DeltaRll[0] > 0.3);
        LOG_CUTS_N(cuts, "2lEWhigh", 5)
        if(cuts)
        {
          if(mllOSSF > 1.  and mllOSSF <=  4.) { FILL_SIGNAL_REGION("2lEWhigh1"); }
          if(mllOSSF > 4.  and mllOSSF <= 10.) { FILL_SIGNAL_REGION("2lEWhigh2"); }
          if(mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("2lEWhigh3"); }
          if(mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("2lEWhigh4"); }
          if(mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("2lEWhigh5"); }
        }
        //std::cout << "2l high done" << std::endl;

        // 2lEW, ultra high MET, signal regions
        cuts = true;
        cuts = cuts and nSignalLeptons == 2;
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and ( (amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5) );
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (not YvetoOSSF);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (pTll > 3);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (nSignalJets > 0);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (metcorr/HT  > 2./3 and metcorr/HT < 1.4);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (HT > 100.);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (metcorr > 290.);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (trigger_path_1);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (nOSpairs > 0);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (tight_lepton_id);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (nSignalBJets == 0);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (mTauTau <= 0 or mTauTau >= 160);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (mT[0] < 70.);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (nOSSFpairs > 0);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (mllOSSF > 1. and mllOSSF < 50.);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (not JPsivetoOSSF);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (((amIanElectron(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 5.) or (amIaMuon(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 3.5) ) and signalLeptons.at(0)->pT() < 30.);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        cuts = cuts and (DeltaRll[0] > 0.3);
        LOG_CUTS_N(cuts, "2lEWultra", 5)
        if(cuts)
        {
          if(mllOSSF > 1.  and mllOSSF <=  4.) { FILL_SIGNAL_REGION("2lEWultra1"); }
          if(mllOSSF > 4.  and mllOSSF <= 10.) { FILL_SIGNAL_REGION("2lEWultra2"); }
          if(mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("2lEWultra3"); }
          if(mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("2lEWultra4"); }
          if(mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("2lEWultra5"); }
        }
        //std::cout << "2l ultra done" << std::endl;

        // 2lST, low MET, signal regions
        cuts = true;
        cuts = cuts and (nSignalLeptons == 2);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and ((amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5));
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (mllOSSF > 4. and mllOSSF < 50.);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (not YvetoOS);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (pTll > 3.);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (nSignalJets > 0);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (metcorr/HT  > 2./3 and metcorr/HT < 1.4);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (HT > 100.);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (met > 125. and metcorr > 125. and metcorr <= 200.);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (trigger_path_2);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (nOSpairs > 0);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (signalLeptons.at(0)->pT() > 5. and signalLeptons.at(0)->pT() < 30.);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (tight_lepton_id);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (nSignalBJets == 0 );
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (mTauTau <= 0 or mTauTau >= 160);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (nSignalMuons == 2);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        cuts = cuts and (signalLeptons.at(1)->pT() > 5);
        LOG_CUTS_N(cuts, "2lSTlow", 6)
        if(cuts)
        {
          if(signalLeptons.at(0)->pT() >  3.5 and signalLeptons.at(0)->pT() <=  8.) { FILL_SIGNAL_REGION("2lSTlow1"); }
          if(signalLeptons.at(0)->pT() >  8.  and signalLeptons.at(0)->pT() <= 12.) { FILL_SIGNAL_REGION("2lSTlow2"); }
          if(signalLeptons.at(0)->pT() > 12.  and signalLeptons.at(0)->pT() <= 16.) { FILL_SIGNAL_REGION("2lSTlow3"); }
          if(signalLeptons.at(0)->pT() > 16.  and signalLeptons.at(0)->pT() <= 20.) { FILL_SIGNAL_REGION("2lSTlow4"); }
          if(signalLeptons.at(0)->pT() > 20.  and signalLeptons.at(0)->pT() <= 25.) { FILL_SIGNAL_REGION("2lSTlow5"); }
          if(signalLeptons.at(0)->pT() > 25.  and signalLeptons.at(0)->pT() <  30.) { FILL_SIGNAL_REGION("2lSTlow6"); }
        }
        //std::cout << "2st low done" << std::endl;

        // 2lST, med MET, signal regions
        cuts = true;
        cuts = cuts and (nSignalLeptons == 2);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and ((amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5));
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (not YvetoOS);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (pTll > 3.);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (nSignalJets > 0);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (metcorr/HT  > 2./3 and metcorr/HT < 1.4);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (HT > 100.);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (metcorr > 200. and metcorr < 290.);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (trigger_path_1);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (nOSpairs > 0);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (tight_lepton_id);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (nSignalBJets == 0);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (mTauTau <= 0 or mTauTau >= 160);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (mllOS > 1. and mllOS < 50.);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (not JPsivetoOS);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (((amIanElectron(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 5.) or (amIaMuon(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 3.5)) and signalLeptons.at(0)->pT() < 30.);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        cuts = cuts and (DeltaRll[0] > 0.3);
        LOG_CUTS_N(cuts, "2lSTmed", 6)
        if(cuts)
        {
          if(signalLeptons.at(0)->pT() >  3.5 and signalLeptons.at(0)->pT() <=  8.) { FILL_SIGNAL_REGION("2lSTmed1"); }
          if(signalLeptons.at(0)->pT() >  8.  and signalLeptons.at(0)->pT() <= 12.) { FILL_SIGNAL_REGION("2lSTmed2"); }
          if(signalLeptons.at(0)->pT() > 12.  and signalLeptons.at(0)->pT() <= 16.) { FILL_SIGNAL_REGION("2lSTmed3"); }
          if(signalLeptons.at(0)->pT() > 16.  and signalLeptons.at(0)->pT() <= 20.) { FILL_SIGNAL_REGION("2lSTmed4"); }
          if(signalLeptons.at(0)->pT() > 20.  and signalLeptons.at(0)->pT() <= 25.) { FILL_SIGNAL_REGION("2lSTmed5"); }
          if(signalLeptons.at(0)->pT() > 25.  and signalLeptons.at(0)->pT() <  30.) { FILL_SIGNAL_REGION("2lSTmed6"); }
        }
        //std::cout << "2st med done" << std::endl;

        // 2lST, high MET, signal regions
        cuts = true;
        cuts = cuts and (nSignalLeptons == 2);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and ((amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5));
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (not YvetoOS);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (pTll > 3.);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (nSignalJets > 0);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (metcorr/HT  > 2./3 and metcorr/HT < 1.4);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (HT > 100.);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (metcorr > 290. and metcorr < 340.);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (trigger_path_1);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (nOSpairs > 0);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (tight_lepton_id);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (nSignalBJets == 0);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (mTauTau <= 0 or mTauTau >= 160);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (mllOS > 1. and mllOS < 50.);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (not JPsivetoOS);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (((amIanElectron(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 5.) or (amIaMuon(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 3.5)) and signalLeptons.at(0)->pT() < 30.);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        cuts = cuts and (DeltaRll[0] > 0.3);
        LOG_CUTS_N(cuts, "2lSThigh", 6)
        if(cuts)
        {
          if(signalLeptons.at(0)->pT() >  3.5 and signalLeptons.at(0)->pT() <=  8.) { FILL_SIGNAL_REGION("2lST13"); }
          if(signalLeptons.at(0)->pT() >  8.  and signalLeptons.at(0)->pT() <= 12.) { FILL_SIGNAL_REGION("2lST14"); }
          if(signalLeptons.at(0)->pT() > 12.  and signalLeptons.at(0)->pT() <= 16.) { FILL_SIGNAL_REGION("2lST15"); }
          if(signalLeptons.at(0)->pT() > 16.  and signalLeptons.at(0)->pT() <= 20.) { FILL_SIGNAL_REGION("2lST16"); }
          if(signalLeptons.at(0)->pT() > 20.  and signalLeptons.at(0)->pT() <= 25.) { FILL_SIGNAL_REGION("2lST17"); }
          if(signalLeptons.at(0)->pT() > 25.  and signalLeptons.at(0)->pT() <  30.) { FILL_SIGNAL_REGION("2lST18"); }
        }
        //std::cout << "2st high done" << std::endl;

        // 2lST, ultra-high MET, signal regions
        cuts = true;
        cuts = cuts and (nSignalLeptons == 2);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and ((amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5));
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (not YvetoOS);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (pTll > 3.);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (nSignalJets > 0);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (metcorr/HT  > 2./3 and metcorr/HT < 1.4);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (HT > 100.);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (metcorr > 340.);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (trigger_path_1);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (nOSpairs > 0);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (tight_lepton_id);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (nSignalBJets == 0);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (mTauTau <= 0 or mTauTau >= 160);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (mllOS > 1. and mllOS < 50.);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (not JPsivetoOS);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (((amIanElectron(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 5.) or (amIaMuon(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 3.5)) and signalLeptons.at(0)->pT() < 30.);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        cuts = cuts and (DeltaRll[0] > 0.3);
        LOG_CUTS_N(cuts, "2lSTultra", 6)
        if(cuts)
        {
          if(signalLeptons.at(0)->pT() >  3.5 and signalLeptons.at(0)->pT() <=  8.) { FILL_SIGNAL_REGION("2lST19"); }
          if(signalLeptons.at(0)->pT() >  8.  and signalLeptons.at(0)->pT() <= 12.) { FILL_SIGNAL_REGION("2lST20"); }
          if(signalLeptons.at(0)->pT() > 12.  and signalLeptons.at(0)->pT() <= 16.) { FILL_SIGNAL_REGION("2lST21"); }
          if(signalLeptons.at(0)->pT() > 16.  and signalLeptons.at(0)->pT() <= 20.) { FILL_SIGNAL_REGION("2lST22"); }
          if(signalLeptons.at(0)->pT() > 20.  and signalLeptons.at(0)->pT() <= 25.) { FILL_SIGNAL_REGION("2lST23"); }
          if(signalLeptons.at(0)->pT() > 25.  and signalLeptons.at(0)->pT() <  30.) { FILL_SIGNAL_REGION("2lST24"); }
        }
        //std::cout << "2st ultra done" << std::endl;

        // 3lEW, low MET, signal regions
        cuts = true;
        cuts = cuts and (nSignalLeptons == 3);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and ((amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5));
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and ((amIanElectron(signalLeptons.at(2)) and signalLeptons.at(2)->pT() > 5.) or (amIaMuon(signalLeptons.at(2)) and signalLeptons.at(2)->pT() > 3.5));
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (not YvetoOSSF);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (HT > 100.);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (met > 125. and metcorr > 125. and metcorr <= 200.);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (trigger_path_2);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (nOSpairs > 0 and nOSSFpairs > 0);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (mllOSSF > 4. and mllOSSF < 50.);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (signalLeptons.at(0)->pT() > 5. and signalLeptons.at(0)->pT() < 30.);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (tight_lepton_id);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (nSignalBJets == 0);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (signalLeptons.at(1)->pT() > 5.);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (nSignalMuons == 2);
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        cuts = cuts and (mllOSSF < 60.); //TODO: Should the last cut be for any sign, i.e. mllSF?
        LOG_CUTS_N(cuts, "3lEWlow", 4)
        if(cuts)
        {
          if(mllOSSF >  4. and mllOSSF <= 10.) { FILL_SIGNAL_REGION("3lEWlow1"); }
          if(mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("3lEWlow2"); }
          if(mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("3lEWlow3"); }
          if(mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("3lEWlow4"); }
        }
        //std::cout << "3l low done" << std::endl;

        // 3lEW, med MET, signal regions
        cuts = true;
        cuts = cuts and (nSignalLeptons == 3);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and ((amIanElectron(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 5.) or (amIaMuon(signalLeptons.at(1)) and signalLeptons.at(1)->pT() > 3.5));
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and ((amIanElectron(signalLeptons.at(2)) and signalLeptons.at(2)->pT() > 5.) or (amIaMuon(signalLeptons.at(2)) and signalLeptons.at(2)->pT() > 3.5));
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (not YvetoOSSF);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (HT > 100.);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (metcorr > 200.);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (trigger_path_1);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (nOSpairs > 0 and nOSSFpairs);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (tight_lepton_id);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (nSignalBJets == 0);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (mllOSSF > 1. and mllOSSF < 50.);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (not JPsivetoOSSF);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (DeltaRll[0] > 0.3);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (( (amIanElectron(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 5.) or (amIaMuon(signalLeptons.at(0)) and signalLeptons.at(0)->pT() > 3.5)) and signalLeptons.at(0)->pT() < 30.);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        if(cuts)
        {
          if(mllOSSF >  1. and mllOSSF <=  4.) { FILL_SIGNAL_REGION("3lEWmed1"); }
          if(mllOSSF >  4. and mllOSSF <= 10.) { FILL_SIGNAL_REGION("3lEWmed2"); }
          if(mllOSSF > 10. and mllOSSF <= 20.) { FILL_SIGNAL_REGION("3lEWmed3"); }
          if(mllOSSF > 20. and mllOSSF <= 30.) { FILL_SIGNAL_REGION("3lEWmed4"); }
          if(mllOSSF > 30. and mllOSSF <  50.) { FILL_SIGNAL_REGION("3lEWmed5"); }
        }
        //std::cout << "3l med done" << std::endl;

      }


      virtual void collect_results()
      {

        /// 2lEW signal regions
        COMMIT_SIGNAL_REGION("2lEWlow1",  73., 68.7, 8.7)
        COMMIT_SIGNAL_REGION("2lEWlow2",  165., 151., 13.)
        COMMIT_SIGNAL_REGION("2lEWlow3",  156., 151., 13.)
        COMMIT_SIGNAL_REGION("2lEWlow4",  80., 82.9, 9.6)
        COMMIT_SIGNAL_REGION("2lEWmed1",  2., 5.5, 2.5)
        COMMIT_SIGNAL_REGION("2lEWmed2",  19., 17.8, 4.4)
        COMMIT_SIGNAL_REGION("2lEWmed3",  59., 60.1, 8.3)
        COMMIT_SIGNAL_REGION("2lEWmed4",  47., 44.3, 7.1)
        COMMIT_SIGNAL_REGION("2lEWmed5",  24., 27.7, 5.6)
        COMMIT_SIGNAL_REGION("2lEWhigh1", 2., 2.7, 1.9)
        COMMIT_SIGNAL_REGION("2lEWhigh2", 11., 7.7, 3.9)
        COMMIT_SIGNAL_REGION("2lEWhigh3", 19., 23.8, 5.4)
        COMMIT_SIGNAL_REGION("2lEWhigh4", 13., 17.0, 4.5)
        COMMIT_SIGNAL_REGION("2lEWhigh5", 10., 11.6, 5.8)
        COMMIT_SIGNAL_REGION("2lEWultra1", 1., 1.5, 1.3)
        COMMIT_SIGNAL_REGION("2lEWultra2", 3., 5.2, 2.5)
        COMMIT_SIGNAL_REGION("2lEWultra3", 15., 13.5, 4.1)
        COMMIT_SIGNAL_REGION("2lEWultra4", 13., 8.8, 3.2)
        COMMIT_SIGNAL_REGION("2lEWultra5", 9., 6.8, 3.0)

        /// 3lEW signal regions
        COMMIT_SIGNAL_REGION("3lEWlow1", 3., 5.7, 2.2)
        COMMIT_SIGNAL_REGION("3lEWlow2", 7., 4.9, 2.2)
        COMMIT_SIGNAL_REGION("3lEWlow3", 4., 2.4, 1.5)
        COMMIT_SIGNAL_REGION("3lEWlow4", 1., 1.8, 1.4)
        COMMIT_SIGNAL_REGION("3lEWmed1", 3., 1.7, 1.2)
        COMMIT_SIGNAL_REGION("3lEWmed2", 1., 4.0, 1.8)
        COMMIT_SIGNAL_REGION("3lEWmed3", 5., 4.2, 2.0)
        COMMIT_SIGNAL_REGION("3lEWmed4", 2., 1.7, 1.3)
        COMMIT_SIGNAL_REGION("3lEWmed5", 1., 1.3, 1.1)

        /// WZ signal regions
        //COMMIT_SIGNAL_REGION("WZ1", 4., 3.5, 1.8)
        //COMMIT_SIGNAL_REGION("WZ2", 11., 6.1, 2.3)
        //COMMIT_SIGNAL_REGION("WZ3", 9., 7.8, 2.6)
        //COMMIT_SIGNAL_REGION("WZ4", 0., 0.78, 0.97) // TODO: Can we do asymmetric errors?
        //COMMIT_SIGNAL_REGION("WZ5", 3., 3.1, 1.6)
        //COMMIT_SIGNAL_REGION("WZ6", 19., 14.0, 3.4)
        //COMMIT_SIGNAL_REGION("WZ7", 23., 21.0, 4.2)

        /// 2lST signal regions
        COMMIT_SIGNAL_REGION("2lSTlow1",  52.,  49.9, 7.2)
        COMMIT_SIGNAL_REGION("2lSTlow2",  156., 144., 12.)
        COMMIT_SIGNAL_REGION("2lSTlow3",  196., 180., 14.)
        COMMIT_SIGNAL_REGION("2lSTlow4",  238., 229., 16.)
        COMMIT_SIGNAL_REGION("2lSTlow5",  285., 273., 18.)
        COMMIT_SIGNAL_REGION("2lSTlow6",  246., 256., 17.)
        COMMIT_SIGNAL_REGION("2lSTmed1",  53.,  49.9, 7.3)
        COMMIT_SIGNAL_REGION("2lSTmed2",  130., 129., 12.)
        COMMIT_SIGNAL_REGION("2lSTmed3",  153., 156., 13.)
        COMMIT_SIGNAL_REGION("2lSTmed4", 163., 177., 14.)
        COMMIT_SIGNAL_REGION("2lSTmed5", 220., 220., 16.)
        COMMIT_SIGNAL_REGION("2lSTmed6", 219., 218., 16.)
        COMMIT_SIGNAL_REGION("2lSThigh1", 4.,   4.1,  2.1)
        COMMIT_SIGNAL_REGION("2lSThigh2", 15.,  15.0, 4.1)
        COMMIT_SIGNAL_REGION("2lSThigh3", 16.,  14.8, 4.1)
        COMMIT_SIGNAL_REGION("2lSThigh4", 23.,  24.6, 5.2)
        COMMIT_SIGNAL_REGION("2lSThigh5", 30.,  28.8, 5.8)
        COMMIT_SIGNAL_REGION("2lSThigh6", 38.,  31.5, 6.0)
        COMMIT_SIGNAL_REGION("2lSTultra1", 7.,   4.7,  2.3)
        COMMIT_SIGNAL_REGION("2lSTultra2", 11.,  12.2, 3.6)
        COMMIT_SIGNAL_REGION("2lSTultra3", 14.,  11.6, 3.6)
        COMMIT_SIGNAL_REGION("2lSTultra4", 11.,  16.7, 4.4)
        COMMIT_SIGNAL_REGION("2lSTultra5", 26.,  25.7, 5.5)
        COMMIT_SIGNAL_REGION("2lSTultra6", 26.,  27.9, 5.7)

        /// Cutflows
        COMMIT_CUTFLOWS
      }


    protected:

      void analysis_specific_reset()
      {

        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2LEPsoft_137invfb)


    // Only EW signal regions with covariance matrix
    class Analysis_CMS_13TeV_2LEPsoft_ewinos_137invfb : public Analysis_CMS_13TeV_2LEPsoft_137invfb
    {
      public:
      Analysis_CMS_13TeV_2LEPsoft_ewinos_137invfb()
      {
        set_analysis_name("CMS_13TeV_2LEPsoft_ewinos_137invfb");
      }

      virtual void collect_results()
      {
        /// 2lEW signal regions
        COMMIT_SIGNAL_REGION("2lEWlow1",  73., 68.7, 8.7)
        COMMIT_SIGNAL_REGION("2lEWlow2",  165., 151., 13.)
        COMMIT_SIGNAL_REGION("2lEWlow3",  156., 151., 13.)
        COMMIT_SIGNAL_REGION("2lEWlow4",  80., 82.9, 9.6)
        COMMIT_SIGNAL_REGION("2lEWmed1",  2., 5.5, 2.5)
        COMMIT_SIGNAL_REGION("2lEWmed2",  19., 17.8, 4.4)
        COMMIT_SIGNAL_REGION("2lEWmed3",  59., 60.1, 8.3)
        COMMIT_SIGNAL_REGION("2lEWmed4",  47., 44.3, 7.1)
        COMMIT_SIGNAL_REGION("2lEWmed5",  24., 27.7, 5.6)
        COMMIT_SIGNAL_REGION("2lEWhigh1", 2., 2.7, 1.9)
        COMMIT_SIGNAL_REGION("2lEWhigh2", 11., 7.7, 3.9)
        COMMIT_SIGNAL_REGION("2lEWhigh3", 19., 23.8, 5.4)
        COMMIT_SIGNAL_REGION("2lEWhigh4", 13., 17.0, 4.5)
        COMMIT_SIGNAL_REGION("2lEWhigh5", 10., 11.6, 5.8)
        COMMIT_SIGNAL_REGION("2lEWultra1", 1., 1.5, 1.3)
        COMMIT_SIGNAL_REGION("2lEWultra2", 3., 5.2, 2.5)
        COMMIT_SIGNAL_REGION("2lEWultra3", 15., 13.5, 4.1)
        COMMIT_SIGNAL_REGION("2lEWultra4", 13., 8.8, 3.2)
        COMMIT_SIGNAL_REGION("2lEWultra5", 9., 6.8, 3.0)

        /// 3lEW signal regions
        COMMIT_SIGNAL_REGION("3lEWlow1", 3., 5.7, 2.2)
        COMMIT_SIGNAL_REGION("3lEWlow2", 7., 4.9, 2.2)
        COMMIT_SIGNAL_REGION("3lEWlow3", 4., 2.4, 1.5)
        COMMIT_SIGNAL_REGION("3lEWlow4", 1., 1.8, 1.4)
        COMMIT_SIGNAL_REGION("3lEWmed1", 3., 1.7, 1.2)
        COMMIT_SIGNAL_REGION("3lEWmed2", 1., 4.0, 1.8)
        COMMIT_SIGNAL_REGION("3lEWmed3", 5., 4.2, 2.0)
        COMMIT_SIGNAL_REGION("3lEWmed4", 2., 1.7, 1.3)
        COMMIT_SIGNAL_REGION("3lEWmed5", 1., 1.3, 1.1)

        /// Cutflows
        COMMIT_CUTFLOWS

        // Covariance matrix
        static const vector< vector<double> > BKGCOV = {
          { 0 },
        };

        //COMMIT_COVARIANCE_MATRIX(BKGCOV);

      }
    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2LEPsoft_ewinos_137invfb)

    // Only stop signal regions
    class Analysis_CMS_13TeV_2LEPsoft_stop_137invfb : public Analysis_CMS_13TeV_2LEPsoft_137invfb
    {
      public:
      Analysis_CMS_13TeV_2LEPsoft_stop_137invfb()
      {
        set_analysis_name("CMS_13TeV_2LEPsoft_stop_137invfb");
      }

      virtual void collect_results()
      {
        /// 2lST signal regions
        COMMIT_SIGNAL_REGION("2lSTlow1",  52.,  49.9, 7.2)
        COMMIT_SIGNAL_REGION("2lSTlow2",  156., 144., 12.)
        COMMIT_SIGNAL_REGION("2lSTlow3",  196., 180., 14.)
        COMMIT_SIGNAL_REGION("2lSTlow4",  238., 229., 16.)
        COMMIT_SIGNAL_REGION("2lSTlow5",  285., 273., 18.)
        COMMIT_SIGNAL_REGION("2lSTlow6",  246., 256., 17.)
        COMMIT_SIGNAL_REGION("2lSTmed1",  53.,  49.9, 7.3)
        COMMIT_SIGNAL_REGION("2lSTmed2",  130., 129., 12.)
        COMMIT_SIGNAL_REGION("2lSTmed3",  153., 156., 13.)
        COMMIT_SIGNAL_REGION("2lSTmed4", 163., 177., 14.)
        COMMIT_SIGNAL_REGION("2lSTmed5", 220., 220., 16.)
        COMMIT_SIGNAL_REGION("2lSTmed6", 219., 218., 16.)
        COMMIT_SIGNAL_REGION("2lSThigh1", 4.,   4.1,  2.1)
        COMMIT_SIGNAL_REGION("2lSThigh2", 15.,  15.0, 4.1)
        COMMIT_SIGNAL_REGION("2lSThigh3", 16.,  14.8, 4.1)
        COMMIT_SIGNAL_REGION("2lSThigh4", 23.,  24.6, 5.2)
        COMMIT_SIGNAL_REGION("2lSThigh5", 30.,  28.8, 5.8)
        COMMIT_SIGNAL_REGION("2lSThigh6", 38.,  31.5, 6.0)
        COMMIT_SIGNAL_REGION("2lSTultra1", 7.,   4.7,  2.3)
        COMMIT_SIGNAL_REGION("2lSTultra2", 11.,  12.2, 3.6)
        COMMIT_SIGNAL_REGION("2lSTultra3", 14.,  11.6, 3.6)
        COMMIT_SIGNAL_REGION("2lSTultra4", 11.,  16.7, 4.4)
        COMMIT_SIGNAL_REGION("2lSTultra5", 26.,  25.7, 5.5)
        COMMIT_SIGNAL_REGION("2lSTultra6", 26.,  27.9, 5.7)

        /// Cutflows
        COMMIT_CUTFLOWS

      }
    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2LEPsoft_stop_137invfb)

  }
}
