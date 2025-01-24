///
///  \author Tomas Gonzalo
///  \date 2023 Aug
///
///  *********************************************

// Based on https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-18-004/index.html
// June 2024: Updated to match published paper, cutflows and other public data

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
        bool debug = false;

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_13TeV_2LEPsoft_137invfb()
      {
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
        //////////////////////
        // Baseline objects //

        BASELINE_PARTICLES(event->electrons(), baselineElectrons, 5., 0., 30., 2.5, CMS::eff2DEl.at("SUS-18-004"))
        BASELINE_PARTICLES(event->muons(), baselineMuons, 3.5, 0., 30., 2.4, CMS::eff2DMu.at("SUS-18-004"))
        // TODO: Test with looser constraints on lepton pTs at baseline selection
        //BASELINE_PARTICLES(event->electrons(), baselineElectrons, 1., 0., 50., 2.5, CMS::eff2DEl.at("SUS-18-004"))
        //BASELINE_PARTICLES(event->muons(), baselineMuons, 1., 0., 50., 2.4, CMS::eff2DMu.at("SUS-18-004"))
        // TODO: Test with no cut on baseline selection
        //BASELINE_PARTICLES(event->electrons(), baselineElectrons)
        //BASELINE_PARTICLES(event->muons(), baselineMuons)
        BASELINE_PARTICLE_COMBINATION(baselineLeptons, baselineElectrons, baselineMuons)
        BASELINE_JETS(event->jets("antikt_R04"), baselineJets, 25., 0., DBL_MAX, 2.4)
        BASELINE_BJETS(event->jets("antikt_R04"), baselineBJets, 25., 0., DBL_MAX, 2.4, CMS::eff2DBJet.at("DeepCSVMedium"), CMS::misIDBJet.at("DeepCSVMedium"))

        size_t nBaselineMuons = baselineMuons.size();
        size_t nBaselineLeptons = baselineLeptons.size();

        ////////////////////
        // Signal objects //
        // TODO: Move the lepton cuts here
        //SIGNAL_PARTICLES(baselineElectrons, signalElectrons)
        //SIGNAL_PARTICLES(baselineMuons, signalMuons)
        SIGNAL_PARTICLES(baselineElectrons, signalElectrons, true, 5., 0., 30., 2.5)
        applyEfficiency(signalElectrons, CMS::eff2DEl.at("SUS-18-004"));
        SIGNAL_PARTICLES(baselineMuons, signalMuons, true, 3.5, 0., 30., 2.4)
        applyEfficiency(signalMuons, CMS::eff2DMu.at("SUS-18-004"));
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
        // TODO: Tried corrected met with baseline muons
        double metcorr = 0;
        double metcorrx = mmom.px();
        double metcorry = mmom.py();
        //for(auto& muon : signalMuons)
        for(auto& muon: baselineMuons)
        {
          metcorrx += muon->mom().px();
          metcorry += muon->mom().py();
        }
        metcorr = sqrt(metcorrx*metcorrx + metcorry*metcorry);

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
        bool trigger_path_3 = nBaselineMuons >= 2 and baselineMuons.at(0)->pT() > 17 and baselineMuons.at(1)->pT() > 8;
        //if(not trigger_path_1 and not trigger_path_2/* and not trigger_path_3*/) return;

        static int count = 0;
        static int twosl, threesl = 0;
        count++;
        if(nSignalLeptons == 2) twosl++;
        if(nSignalLeptons == 3) threesl++;
        //if(!(count%1000)) std::cout << "events with 2 signal leptons = " << twosl << std::endl;
        //if(!(count%1000)) std::cout << "events with 3 signal leptons = " << threesl << std::endl;

        ///////////////////
        // Preselection //
        BEGIN_PRESELECTION
        if(nBaselineLeptons < 2 or (not trigger_path_1 and not trigger_path_2 and not trigger_path_3)) return;
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
        cuts = cuts and (trigger_path_1 or trigger_path_2 or trigger_path_3);
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
        if(debug) std::cout << "2l low done" << std::endl;

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
        cuts = cuts and (trigger_path_1 or trigger_path_2 or trigger_path_3);
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
        if(debug) std::cout << "2l med done" << std::endl;

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
        cuts = cuts and (trigger_path_1 or trigger_path_2 or trigger_path_3);
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
        if(debug) std::cout << "2l high done" << std::endl;

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
        cuts = cuts and (trigger_path_1 or trigger_path_2 or trigger_path_3);
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
        if(debug) std::cout << "2l ultra done" << std::endl;

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
        cuts = cuts and (trigger_path_1 or trigger_path_2 or trigger_path_3);
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
        if(debug) std::cout << "2st low done" << std::endl;

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
        cuts = cuts and (trigger_path_1 or trigger_path_2 or trigger_path_3);
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
        if(debug) std::cout << "2st med done" << std::endl;

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
        cuts = cuts and (trigger_path_1 or trigger_path_2 or trigger_path_3);
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
          if(signalLeptons.at(0)->pT() >  3.5 and signalLeptons.at(0)->pT() <=  8.) { FILL_SIGNAL_REGION("2lSThigh1"); }
          if(signalLeptons.at(0)->pT() >  8.  and signalLeptons.at(0)->pT() <= 12.) { FILL_SIGNAL_REGION("2lSThigh2"); }
          if(signalLeptons.at(0)->pT() > 12.  and signalLeptons.at(0)->pT() <= 16.) { FILL_SIGNAL_REGION("2lSThigh3"); }
          if(signalLeptons.at(0)->pT() > 16.  and signalLeptons.at(0)->pT() <= 20.) { FILL_SIGNAL_REGION("2lSThigh4"); }
          if(signalLeptons.at(0)->pT() > 20.  and signalLeptons.at(0)->pT() <= 25.) { FILL_SIGNAL_REGION("2lSThigh5"); }
          if(signalLeptons.at(0)->pT() > 25.  and signalLeptons.at(0)->pT() <  30.) { FILL_SIGNAL_REGION("2lSThigh6"); }
        }
        if(debug) std::cout << "2st high done" << std::endl;

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
        cuts = cuts and (trigger_path_1 or trigger_path_2 or trigger_path_3);
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
          if(signalLeptons.at(0)->pT() >  3.5 and signalLeptons.at(0)->pT() <=  8.) { FILL_SIGNAL_REGION("2lSTultra1"); }
          if(signalLeptons.at(0)->pT() >  8.  and signalLeptons.at(0)->pT() <= 12.) { FILL_SIGNAL_REGION("2lSTultra2"); }
          if(signalLeptons.at(0)->pT() > 12.  and signalLeptons.at(0)->pT() <= 16.) { FILL_SIGNAL_REGION("2lSTultra3"); }
          if(signalLeptons.at(0)->pT() > 16.  and signalLeptons.at(0)->pT() <= 20.) { FILL_SIGNAL_REGION("2lSTultra4"); }
          if(signalLeptons.at(0)->pT() > 20.  and signalLeptons.at(0)->pT() <= 25.) { FILL_SIGNAL_REGION("2lSTultra5"); }
          if(signalLeptons.at(0)->pT() > 25.  and signalLeptons.at(0)->pT() <  30.) { FILL_SIGNAL_REGION("2lSTultra6"); }
        }
        if(debug) std::cout << "2st ultra done" << std::endl;

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
        cuts = cuts and (trigger_path_1 or trigger_path_2 or trigger_path_3);
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
        if(debug) std::cout << "3l low done" << std::endl;

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
        cuts = cuts and (trigger_path_1 or trigger_path_2 or trigger_path_3);
        LOG_CUTS_N(cuts, "3lEWmed", 5)
        cuts = cuts and (nOSpairs > 0 and nOSSFpairs > 0);
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
        if(debug) std::cout << "3l med done" << std::endl;

      }


      virtual void collect_results()
      {

        /// 2lEW signal regions
        COMMIT_SIGNAL_REGION("2lEWlow1",  73., 68.719, 8.6862)
        COMMIT_SIGNAL_REGION("2lEWlow2",  165., 150.06, 12.769)
        COMMIT_SIGNAL_REGION("2lEWlow3",  156., 150.59, 12.99)
        COMMIT_SIGNAL_REGION("2lEWlow4",  80., 82.976, 9.5764)
        COMMIT_SIGNAL_REGION("2lEWmed1",  2., 5.5271, 2.4719)
        COMMIT_SIGNAL_REGION("2lEWmed2",  19., 17.814, 4.3529)
        COMMIT_SIGNAL_REGION("2lEWmed3",  59., 60.101, 8.2835)
        COMMIT_SIGNAL_REGION("2lEWmed4",  47., 44.311, 7.1009)
        COMMIT_SIGNAL_REGION("2lEWmed5",  24., 27.669, 5.589)
        COMMIT_SIGNAL_REGION("2lEWhigh1", 2., 2.7188, 1.8583)
        COMMIT_SIGNAL_REGION("2lEWhigh2", 11., 7.6974, 3.916)
        COMMIT_SIGNAL_REGION("2lEWhigh3", 19., 23.791, 5.377)
        COMMIT_SIGNAL_REGION("2lEWhigh4", 13., 17.005, 4.495)
        COMMIT_SIGNAL_REGION("2lEWhigh5", 10., 11.595, 5.8417)
        COMMIT_SIGNAL_REGION("2lEWultra1", 1., 1.4533, 1.2708)
        COMMIT_SIGNAL_REGION("2lEWultra2", 3., 5.1752, 2.4636)
        COMMIT_SIGNAL_REGION("2lEWultra3", 15., 13.485, 4.0899)
        COMMIT_SIGNAL_REGION("2lEWultra4", 13., 8.7493, 3.2078)
        COMMIT_SIGNAL_REGION("2lEWultra5", 9., 6.8343, 2.9575)

        /// 3lEW signal regions
        COMMIT_SIGNAL_REGION("3lEWlow1", 3., 5.7045, 2.1948)
        COMMIT_SIGNAL_REGION("3lEWlow2", 7., 4.8458, 2.2233)
        COMMIT_SIGNAL_REGION("3lEWlow3", 4., 2.3898, 1.5199)
        COMMIT_SIGNAL_REGION("3lEWlow4", 1., 1.8278, 1.3799)
        COMMIT_SIGNAL_REGION("3lEWmed1", 3., 1.6997, 1.1464)
        COMMIT_SIGNAL_REGION("3lEWmed2", 1., 3.9942, 1.8339)
        COMMIT_SIGNAL_REGION("3lEWmed3", 5., 4.1953, 1.9612)
        COMMIT_SIGNAL_REGION("3lEWmed4", 2., 1.6803, 1.2727)
        COMMIT_SIGNAL_REGION("3lEWmed5", 1., 1.3157, 1.1409)

        /// WZ signal regions
        //COMMIT_SIGNAL_REGION("WZ1", 4., 3.5, 1.8)
        //COMMIT_SIGNAL_REGION("WZ2", 11., 6.1, 2.3)
        //COMMIT_SIGNAL_REGION("WZ3", 9., 7.8, 2.6)
        //COMMIT_SIGNAL_REGION("WZ4", 0., 0.78, 0.97) // TODO: Can we do asymmetric errors?
        //COMMIT_SIGNAL_REGION("WZ5", 3., 3.1, 1.6)
        //COMMIT_SIGNAL_REGION("WZ6", 19., 14.0, 3.4)
        //COMMIT_SIGNAL_REGION("WZ7", 23., 21.0, 4.2)

        /// 2lST signal regions
        COMMIT_SIGNAL_REGION("2lSTlow1",  52.,  49.91, 7.2498)
        COMMIT_SIGNAL_REGION("2lSTlow2",  156., 144.51, 12.476)
        COMMIT_SIGNAL_REGION("2lSTlow3",  196., 180.67, 14.065)
        COMMIT_SIGNAL_REGION("2lSTlow4",  238., 229.03, 16.041)
        COMMIT_SIGNAL_REGION("2lSTlow5",  285., 273.25, 17.532)
        COMMIT_SIGNAL_REGION("2lSTlow6",  246., 255.81, 17.011)
        COMMIT_SIGNAL_REGION("2lSTmed1",  53.,  49.852, 7.2755)
        COMMIT_SIGNAL_REGION("2lSTmed2",  130., 129.23, 11.712)
        COMMIT_SIGNAL_REGION("2lSTmed3",  153., 156.43, 13.044)
        COMMIT_SIGNAL_REGION("2lSTmed4", 163., 176.61, 14.045)
        COMMIT_SIGNAL_REGION("2lSTmed5", 220., 220.33, 15.692)
        COMMIT_SIGNAL_REGION("2lSTmed6", 219., 217.74, 15.717)
        COMMIT_SIGNAL_REGION("2lSThigh1", 4.,   4.1401,  2.1116)
        COMMIT_SIGNAL_REGION("2lSThigh2", 15.,  15.032, 4.0793)
        COMMIT_SIGNAL_REGION("2lSThigh3", 16.,  14.843, 4.0923)
        COMMIT_SIGNAL_REGION("2lSThigh4", 23.,  24.577, 5.212)
        COMMIT_SIGNAL_REGION("2lSThigh5", 30.,  28.808, 5.7455)
        COMMIT_SIGNAL_REGION("2lSThigh6", 38.,  31.526, 6.0152)
        COMMIT_SIGNAL_REGION("2lSTultra1", 7.,   4.7143,  2.2795)
        COMMIT_SIGNAL_REGION("2lSTultra2", 11.,  12.219, 3.6377)
        COMMIT_SIGNAL_REGION("2lSTultra3", 14.,  11.639, 3.6336)
        COMMIT_SIGNAL_REGION("2lSTultra4", 11.,  16.704, 4.3992)
        COMMIT_SIGNAL_REGION("2lSTultra5", 26.,  25.659, 5.4629)
        COMMIT_SIGNAL_REGION("2lSTultra6", 25.,  27.869, 5.6947)

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
        COMMIT_SIGNAL_REGION("2lEWlow1",  73., 68.719, 8.6862)
        COMMIT_SIGNAL_REGION("2lEWlow2",  165., 150.06, 12.769)
        COMMIT_SIGNAL_REGION("2lEWlow3",  156., 150.59, 12.99)
        COMMIT_SIGNAL_REGION("2lEWlow4",  80., 82.976, 9.5764)
        COMMIT_SIGNAL_REGION("2lEWmed1",  2., 5.5271, 2.4719)
        COMMIT_SIGNAL_REGION("2lEWmed2",  19., 17.814, 4.3529)
        COMMIT_SIGNAL_REGION("2lEWmed3",  59., 60.101, 8.2835)
        COMMIT_SIGNAL_REGION("2lEWmed4",  47., 44.311, 7.1009)
        COMMIT_SIGNAL_REGION("2lEWmed5",  24., 27.669, 5.589)
        COMMIT_SIGNAL_REGION("2lEWhigh1", 2., 2.7188, 1.8583)
        COMMIT_SIGNAL_REGION("2lEWhigh2", 11., 7.6974, 3.916)
        COMMIT_SIGNAL_REGION("2lEWhigh3", 19., 23.791, 5.377)
        COMMIT_SIGNAL_REGION("2lEWhigh4", 13., 17.005, 4.495)
        COMMIT_SIGNAL_REGION("2lEWhigh5", 10., 11.595, 5.8417)
        COMMIT_SIGNAL_REGION("2lEWultra1", 1., 1.4533, 1.2708)
        COMMIT_SIGNAL_REGION("2lEWultra2", 3., 5.1752, 2.4636)
        COMMIT_SIGNAL_REGION("2lEWultra3", 15., 13.485, 4.0899)
        COMMIT_SIGNAL_REGION("2lEWultra4", 13., 8.7493, 3.2078)
        COMMIT_SIGNAL_REGION("2lEWultra5", 9., 6.8343, 2.9575)

        /// 3lEW signal regions
        COMMIT_SIGNAL_REGION("3lEWlow1", 3., 5.7045, 2.1948)
        COMMIT_SIGNAL_REGION("3lEWlow2", 7., 4.8458, 2.2233)
        COMMIT_SIGNAL_REGION("3lEWlow3", 4., 2.3898, 1.5199)
        COMMIT_SIGNAL_REGION("3lEWlow4", 1., 1.8278, 1.3799)
        COMMIT_SIGNAL_REGION("3lEWmed1", 3., 1.6997, 1.1464)
        COMMIT_SIGNAL_REGION("3lEWmed2", 1., 3.9942, 1.8339)
        COMMIT_SIGNAL_REGION("3lEWmed3", 5., 4.1953, 1.9612)
        COMMIT_SIGNAL_REGION("3lEWmed4", 2., 1.6803, 1.2727)
        COMMIT_SIGNAL_REGION("3lEWmed5", 1., 1.3157, 1.1409)

        /// Cutflows
        COMMIT_CUTFLOWS

        // Covariance matrix
        static const vector< vector<double> > BKGCOV = {
          {  2.352e+01,  9.277e+00,  1.163e+01,  7.513e+00, -3.469e-02,  3.040e-01,  7.431e-03,  8.432e-01, -6.512e-01,  1.812e-01,  1.476e-01, -3.148e-02, -9.607e-02, -3.102e-01,  6.163e-02, -2.558e-02, -5.001e-01,  9.034e-03,  3.827e-01,  2.031e-01,  1.899e-01,  1.594e-02, -2.808e-03, -7.981e-02, -4.865e-02, -3.109e-02,  3.301e-02,  7.268e-02},
          {  9.277e+00,  4.519e+01,  1.995e+01,  1.253e+01,  1.378e-02,  4.503e-01,  5.408e-01,  2.149e+00, -1.322e+00,  2.479e-01,  2.851e-01,  9.571e-02, -2.743e-01, -2.522e-01,  1.028e-01, -2.527e-01, -3.947e-01,  2.965e-01,  4.836e-01,  1.815e-01,  6.065e-02,  9.197e-02, -5.147e-02, -7.283e-02,  1.185e-02, -5.840e-02, -4.179e-03,  1.274e-01},
          {  1.163e+01,  1.995e+01,  7.084e+01,  1.838e+01,  7.858e-02,  8.097e-01, -4.230e-01,  3.574e+00, -2.471e+00, -2.281e-02,  9.074e-02,  8.068e-02, -8.667e-02, -2.118e-01,  1.585e-01, -2.741e-01, -9.930e-01,  3.847e-01,  7.171e-01,  9.697e-02,  4.098e-02,  5.452e-02, -1.746e-01, -2.953e-02,  3.420e-02, -1.003e-01, -3.905e-02,  1.924e-01},
          {  7.513e+00,  1.253e+01,  1.838e+01,  2.742e+01,  9.354e-02,  4.555e-01, -1.095e-01,  1.030e+00, -1.099e+00,  2.993e-02,  1.862e-01,  6.023e-02,  3.894e-01, -4.910e-02,  1.161e-01,  2.875e-02, -6.013e-01,  2.235e-01,  5.079e-01, -1.089e-01,  1.832e-03, -3.171e-03, -1.491e-01, -4.450e-02, -5.679e-02, -1.196e-01, -2.178e-02,  1.391e-01},
          { -3.469e-02,  1.378e-02,  7.858e-02,  9.354e-02,  1.803e+00,  8.106e-02,  3.169e-01,  2.105e-01,  8.413e-02,  3.341e-02,  3.067e-02,  1.877e-01,  1.423e-01,  6.552e-02,  1.357e-02,  3.771e-02,  1.123e-01,  7.462e-02,  1.540e-02,  3.356e-02,  2.528e-02,  1.648e-02,  1.201e-02,  1.894e-02,  1.524e-02,  2.420e-02,  9.420e-03,  8.120e-03},
          {  3.040e-01,  4.503e-01,  8.097e-01,  4.555e-01,  8.106e-02,  9.316e-01,  3.473e-01,  1.538e-01,  1.928e-01,  5.310e-02,  7.874e-02,  8.111e-02,  1.696e-01,  4.235e-02,  2.480e-02,  8.372e-02,  8.164e-02,  3.932e-02,  8.320e-02,  2.951e-02,  3.093e-02,  1.437e-02,  7.724e-03,  1.861e-02,  2.650e-02,  2.409e-02,  1.221e-02,  2.296e-03},
          {  7.431e-03,  5.408e-01, -4.230e-01, -1.095e-01,  3.169e-01,  3.473e-01,  1.345e+01,  1.177e+00,  1.318e+00,  1.705e-01,  1.461e-01,  3.642e-01,  5.553e-01,  4.907e-01,  2.387e-02,  1.924e-01,  5.766e-01,  4.059e-01,  2.333e-01,  1.867e-01,  1.973e-01,  8.772e-02,  1.104e-01,  4.486e-02,  1.317e-01,  1.058e-01,  3.388e-02, -3.699e-03},
          {  8.432e-01,  2.149e+00,  3.574e+00,  1.030e+00,  2.105e-01,  1.538e-01,  1.177e+00,  1.722e+01,  6.111e-01,  6.332e-02,  3.790e-02,  1.559e-01,  4.972e-01,  2.702e-01,  1.517e-02,  5.313e-02,  3.019e-01,  2.914e-01,  2.554e-01, -1.791e-02,  2.355e-02, -2.235e-03,  4.003e-02, -1.698e-02,  3.703e-02,  6.564e-02,  6.242e-03,  2.233e-02},
          { -6.512e-01, -1.322e+00, -2.471e+00, -1.099e+00,  8.413e-02,  1.928e-01,  1.318e+00,  6.111e-01,  8.033e+00,  1.196e-01,  1.609e-01,  3.065e-01,  6.447e-01,  4.387e-01,  2.217e-02,  2.135e-01,  5.272e-01,  2.873e-01,  2.073e-01,  9.775e-02,  7.443e-02,  3.189e-02,  9.525e-02,  3.356e-02,  8.581e-02,  6.595e-02,  2.642e-02, -2.661e-02},
          {  1.812e-01,  2.479e-01, -2.281e-02,  2.993e-02,  3.341e-02,  5.310e-02,  1.705e-01,  6.332e-02,  1.196e-01,  3.113e-01,  2.709e-02,  8.576e-02,  8.496e-02,  1.037e-02,  5.690e-03,  2.288e-02,  5.195e-02,  3.541e-02,  1.596e-02,  9.044e-03,  2.731e-03,  3.655e-03,  6.023e-03,  2.500e-03,  1.063e-02,  1.579e-02,  3.719e-04,  1.177e-03},
          {  1.476e-01,  2.851e-01,  9.074e-02,  1.862e-01,  3.067e-02,  7.874e-02,  1.461e-01,  3.790e-02,  1.609e-01,  2.709e-02,  1.593e-01,  6.517e-02,  7.381e-02,  9.872e-03,  1.494e-02,  5.169e-02,  8.060e-02,  3.560e-02,  3.629e-02,  1.214e-02,  1.727e-02, -3.158e-03,  3.739e-03,  6.727e-03,  1.341e-02,  1.296e-02,  5.108e-03, -2.392e-03},
          { -3.148e-02,  9.571e-02,  8.068e-02,  6.023e-02,  1.877e-01,  8.111e-02,  3.642e-01,  1.559e-01,  3.065e-01,  8.576e-02,  6.517e-02,  2.410e+00,  3.245e-01, -2.935e-02,  4.253e-02,  1.485e-01,  2.588e-01,  1.322e-01,  4.283e-02,  4.673e-03,  3.227e-02,  8.660e-03,  2.778e-02,  1.312e-02,  5.442e-02,  3.073e-02,  5.975e-03, -6.673e-03},
          { -9.607e-02, -2.743e-01, -8.667e-02,  3.894e-01,  1.423e-01,  1.696e-01,  5.553e-01,  4.972e-01,  6.447e-01,  8.496e-02,  7.381e-02,  3.245e-01,  2.628e+00,  1.718e-01,  4.683e-02,  1.860e-01,  2.015e-01,  1.074e-01,  1.585e-01,  1.680e-02,  4.268e-02,  6.537e-03,  3.308e-02,  5.195e-03,  1.442e-02,  5.837e-03,  3.624e-03,  7.213e-03},
          { -3.102e-01, -2.522e-01, -2.118e-01, -4.910e-02,  6.552e-02,  4.235e-02,  4.907e-01,  2.702e-01,  4.387e-01,  1.037e-02,  9.872e-03, -2.935e-02,  1.718e-01,  1.660e+00, -1.261e-02,  3.548e-02,  1.611e-01,  1.199e-01,  1.305e-01,  9.099e-02,  4.194e-02,  3.088e-02,  2.237e-02,  1.462e-02,  1.504e-02,  7.235e-02,  9.494e-03, -1.072e-02},
          {  6.163e-02,  1.028e-01,  1.585e-01,  1.161e-01,  1.357e-02,  2.480e-02,  2.387e-02,  1.517e-02,  2.217e-02,  5.690e-03,  1.494e-02,  4.253e-02,  4.683e-02, -1.261e-02,  2.967e-02,  2.479e-02,  1.761e-02,  6.370e-03,  1.160e-02, -2.128e-05,  5.090e-03, -1.332e-03, -2.264e-03,  1.017e-03,  3.940e-03,  1.030e-03, -6.360e-05,  2.365e-03},
          { -2.558e-02, -2.527e-01, -2.741e-01,  2.875e-02,  3.771e-02,  8.372e-02,  1.924e-01,  5.313e-02,  2.135e-01,  2.288e-02,  5.169e-02,  1.485e-01,  1.860e-01,  3.548e-02,  2.479e-02,  2.177e-01,  1.113e-01,  1.441e-02,  4.554e-02,  2.503e-02,  2.429e-02,  2.301e-03,  9.244e-03,  1.394e-02,  2.479e-02,  1.000e-02,  1.059e-03, -8.600e-04},
          { -5.001e-01, -3.947e-01, -9.930e-01, -6.013e-01,  1.123e-01,  8.164e-02,  5.766e-01,  3.019e-01,  5.272e-01,  5.195e-02,  8.060e-02,  2.588e-01,  2.015e-01,  1.611e-01,  1.761e-02,  1.113e-01,  1.213e+00,  9.772e-02,  7.312e-02,  5.369e-02,  7.066e-02,  2.242e-02,  2.660e-02,  2.701e-02,  2.804e-02,  4.688e-02,  5.219e-03, -6.265e-03},
          {  9.034e-03,  2.965e-01,  3.847e-01,  2.235e-01,  7.462e-02,  3.932e-02,  4.059e-01,  2.914e-01,  2.873e-01,  3.541e-02,  3.560e-02,  1.322e-01,  1.074e-01,  1.199e-01,  6.370e-03,  1.441e-02,  9.772e-02,  8.856e-01,  8.028e-02,  3.052e-02,  7.516e-05,  8.366e-03,  1.760e-02,  4.854e-03,  2.472e-02,  3.423e-02,  4.739e-03,  7.518e-04},
          {  3.827e-01,  4.836e-01,  7.171e-01,  5.079e-01,  1.540e-02,  8.320e-02,  2.333e-01,  2.554e-01,  2.073e-01,  1.596e-02,  3.629e-02,  4.283e-02,  1.585e-01,  1.305e-01,  1.160e-02,  4.554e-02,  7.312e-02,  8.028e-02,  6.860e-01,  2.700e-03,  3.718e-03,  6.484e-03,  4.410e-03,  6.928e-04,  1.025e-02,  1.087e-02,  3.155e-03, -1.639e-03},
          {  2.031e-01,  1.815e-01,  9.697e-02, -1.089e-01,  3.356e-02,  2.951e-02,  1.867e-01, -1.791e-02,  9.775e-02,  9.044e-03,  1.214e-02,  4.673e-03,  1.680e-02,  9.099e-02, -2.128e-05,  2.503e-02,  5.369e-02,  3.052e-02,  2.700e-03,  3.159e-01,  1.075e-01,  4.508e-02,  1.937e-02,  2.022e-02,  2.235e-02,  2.318e-02,  8.316e-03, -1.011e-03},
          {  1.899e-01,  6.065e-02,  4.098e-02,  1.832e-03,  2.528e-02,  3.093e-02,  1.973e-01,  2.355e-02,  7.443e-02,  2.731e-03,  1.727e-02,  3.227e-02,  4.268e-02,  4.194e-02,  5.090e-03,  2.429e-02,  7.066e-02,  7.516e-05,  3.718e-03,  1.075e-01,  3.017e-01,  2.183e-02,  1.218e-02,  1.378e-02,  2.901e-02,  2.599e-02,  6.542e-03,  5.806e-03},
          {  1.594e-02,  9.197e-02,  5.452e-02, -3.171e-03,  1.648e-02,  1.437e-02,  8.772e-02, -2.235e-03,  3.189e-02,  3.655e-03, -3.158e-03,  8.660e-03,  6.537e-03,  3.088e-02, -1.332e-03,  2.301e-03,  2.242e-02,  8.366e-03,  6.484e-03,  4.508e-02,  2.183e-02,  4.651e-02,  5.647e-03,  6.928e-03,  9.635e-03,  8.497e-03,  1.665e-03,  7.132e-04},
          { -2.808e-03, -5.147e-02, -1.746e-01, -1.491e-01,  1.201e-02,  7.724e-03,  1.104e-01,  4.003e-02,  9.525e-02,  6.023e-03,  3.739e-03,  2.778e-02,  3.308e-02,  2.237e-02, -2.264e-03,  9.244e-03,  2.660e-02,  1.760e-02,  4.410e-03,  1.937e-02,  1.218e-02,  5.647e-03,  5.099e-02,  1.638e-03,  5.363e-03,  2.322e-03,  3.788e-03, -2.340e-03},
          { -7.981e-02, -7.283e-02, -2.953e-02, -4.450e-02,  1.894e-02,  1.861e-02,  4.486e-02, -1.698e-02,  3.356e-02,  2.500e-03,  6.727e-03,  1.312e-02,  5.195e-03,  1.462e-02,  1.017e-03,  1.394e-02,  2.701e-02,  4.854e-03,  6.928e-04,  2.022e-02,  1.378e-02,  6.928e-03,  1.638e-03,  3.381e-02,  2.001e-02,  1.393e-02,  2.154e-03,  9.751e-04},
          { -4.865e-02,  1.185e-02,  3.420e-02, -5.679e-02,  1.524e-02,  2.650e-02,  1.317e-01,  3.703e-02,  8.581e-02,  1.063e-02,  1.341e-02,  5.442e-02,  1.442e-02,  1.504e-02,  3.940e-03,  2.479e-02,  2.804e-02,  2.472e-02,  1.025e-02,  2.235e-02,  2.901e-02,  9.635e-03,  5.363e-03,  2.001e-02,  1.552e-01,  2.599e-02,  5.718e-03,  2.095e-03},
          { -3.109e-02, -5.840e-02, -1.003e-01, -1.196e-01,  2.420e-02,  2.409e-02,  1.058e-01,  6.564e-02,  6.595e-02,  1.579e-02,  1.296e-02,  3.073e-02,  5.837e-03,  7.235e-02,  1.030e-03,  1.000e-02,  4.688e-02,  3.423e-02,  1.087e-02,  2.318e-02,  2.599e-02,  8.497e-03,  2.322e-03,  1.393e-02,  2.599e-02,  1.913e-01,  5.515e-03,  2.854e-03},
          {  3.301e-02, -4.179e-03, -3.905e-02, -2.178e-02,  9.420e-03,  1.221e-02,  3.388e-02,  6.242e-03,  2.642e-02,  3.719e-04,  5.108e-03,  5.975e-03,  3.624e-03,  9.494e-03, -6.360e-05,  1.059e-03,  5.219e-03,  4.739e-03,  3.155e-03,  8.316e-03,  6.542e-03,  1.665e-03,  3.788e-03,  2.154e-03,  5.718e-03,  5.515e-03,  3.781e-02,  9.790e-04},
          {  7.268e-02,  1.274e-01,  1.924e-01,  1.391e-01,  8.120e-03,  2.296e-03, -3.699e-03,  2.233e-02, -2.661e-02,  1.177e-03, -2.392e-03, -6.673e-03,  7.213e-03, -1.072e-02,  2.365e-03, -8.600e-04, -6.265e-03,  7.518e-04, -1.639e-03, -1.011e-03,  5.806e-03,  7.132e-04, -2.340e-03,  9.751e-04,  2.095e-03,  2.854e-03,  9.790e-04,  2.803e-02},
        };

        COMMIT_COVARIANCE_MATRIX(BKGCOV);

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
        COMMIT_SIGNAL_REGION("2lSTlow1",  52.,  49.91, 7.2498)
        COMMIT_SIGNAL_REGION("2lSTlow2",  156., 144.51, 12.476)
        COMMIT_SIGNAL_REGION("2lSTlow3",  196., 180.67, 14.065)
        COMMIT_SIGNAL_REGION("2lSTlow4",  238., 229.03, 16.041)
        COMMIT_SIGNAL_REGION("2lSTlow5",  285., 273.25, 17.532)
        COMMIT_SIGNAL_REGION("2lSTlow6",  246., 255.81, 17.011)
        COMMIT_SIGNAL_REGION("2lSTmed1",  53.,  49.852, 7.2755)
        COMMIT_SIGNAL_REGION("2lSTmed2",  130., 129.23, 11.712)
        COMMIT_SIGNAL_REGION("2lSTmed3",  153., 156.43, 13.044)
        COMMIT_SIGNAL_REGION("2lSTmed4", 163., 176.61, 14.045)
        COMMIT_SIGNAL_REGION("2lSTmed5", 220., 220.33, 15.692)
        COMMIT_SIGNAL_REGION("2lSTmed6", 219., 217.74, 15.717)
        COMMIT_SIGNAL_REGION("2lSThigh1", 4.,   4.1401,  2.1116)
        COMMIT_SIGNAL_REGION("2lSThigh2", 15.,  15.032, 4.0793)
        COMMIT_SIGNAL_REGION("2lSThigh3", 16.,  14.843, 4.0923)
        COMMIT_SIGNAL_REGION("2lSThigh4", 23.,  24.577, 5.212)
        COMMIT_SIGNAL_REGION("2lSThigh5", 30.,  28.808, 5.7455)
        COMMIT_SIGNAL_REGION("2lSThigh6", 38.,  31.526, 6.0152)
        COMMIT_SIGNAL_REGION("2lSTultra1", 7.,   4.7143,  2.2795)
        COMMIT_SIGNAL_REGION("2lSTultra2", 11.,  12.219, 3.6377)
        COMMIT_SIGNAL_REGION("2lSTultra3", 14.,  11.639, 3.6336)
        COMMIT_SIGNAL_REGION("2lSTultra4", 11.,  16.704, 4.3992)
        COMMIT_SIGNAL_REGION("2lSTultra5", 26.,  25.659, 5.4629)
        COMMIT_SIGNAL_REGION("2lSTultra6", 25.,  27.869, 5.6947)

        /// Cutflows
        COMMIT_CUTFLOWS

      }
    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_2LEPsoft_stop_137invfb)

  }
}
