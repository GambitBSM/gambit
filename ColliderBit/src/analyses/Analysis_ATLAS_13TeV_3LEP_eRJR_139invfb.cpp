///
///  \author Martin White
///  \date 2023 August
///
///
/// Based on the three-lepton search with the full Run 2 data set presented in https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/PAPERS/SUSY-2018-06/
///
/// This uses emulations of the RJR variables to prove the RJR excesses in the previous dataset
///  *********************************************

//#define CHECK_CUTFLOW
//#define BENCHMARK "WZ_300_200"
//#define BENCHMARK "WZ_600_100"
// #define BENCHMARK "Wh_190_60"


#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_ATLAS_13TeV_3LEP_eRJR_139invfb : public Analysis
    {

      protected:

      private:

      public:

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        // Discards leptons overlapping with jets, following the description in the paper
        void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec)
        {

          vector<const HEPUtils::Particle*> Survivors;

          for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++)
          {
            bool overlap = false;
            HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
            for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++)
            {
              HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
              double dR;

              dR=jetmom.deltaR_rap(lepmom);

              // Need to define DeltaRMax based on pT of lepton
              double DeltaRMax = 0.;
              double pt = lepvec.at(itlep)->pT();
              if(pt<=25.)DeltaRMax = 0.4;
              if(pt>25. && pt<=50.)DeltaRMax = 0.6-(0.2/25.)*pt;

              if(fabs(dR) <= DeltaRMax) overlap=true;
            }
            if(overlap) continue;
            Survivors.push_back(lepvec.at(itlep));
          }
          lepvec=Survivors;

          return;
        }


        struct ptComparison
        {
          bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
        } comparePt;

        struct ptJetComparison
        {
          bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
        } compareJetPt;


        Cutflows _cutflows;

        Analysis_ATLAS_13TeV_3LEP_eRJR_139invfb()
        {
          // Signal region map
          _counters["SR-low"] = EventCounter("SR-low");
          _counters["SR-ISR"] = EventCounter("SR-ISR");


          set_analysis_name("ATLAS_13TeV_3LEP_eRJR_139invfb");
          set_luminosity(139.);

          /*_cutflows.addCutflow("SR-ISR", {"Trigger (one photon pT > 140 GeV)",
                                           "At least one photon", "Lepton veto",
                                           "Leading photon pT > 145 GeV", "MET > 250 GeV",
                                           "njets >= 5", "dPhi(jet,MET) > 0.4",
             "dPhi(gamma,MET)>0.4", "HT > 2000 GeV", "RT4<0.9",});*/



          _cutflows.addCutflow("SR-ISR", {"3 leptons with >=1 SFOS pair",
            "Dilepton triggers",
            "b-jet veto",
            "m3l > 105 GeV",
            "lepton pT > 25,25,20 GeV",
            "75 GeV < mll < 105 GeV",
            "njets > 0",
            "njets < 4",
            "dPhi(met,jets) > 2.0",
            "0.55 < R(met, jets) < 1.0",
            "ptjets > 100 GeV",
            "met > 80 GeV",
            "mT > 100 GeV","pTsoft < 25 GeV",});

          _cutflows.addCutflow("SR-low", {"3 leptons with >=1 SFOS pair",
            "Dilepton triggers",
            "b-jet veto",
            "m3l > 105 GeV",
            "lepton pT > 60,40,30 GeV",
            "75 GeV < mll < 105 GeV",
            "njets == 0",
            "Hboost > 250 GeV",
            "pTsoft/(pTsoft+m3l_eff) < 0.05",
            "m3l_eff/Hboost > 0.9",
            "mT > 100 GeV",});



        }

        //
        // Main event analysis
        //
        void run(const HEPUtils::Event* event)
        {

          //
          // Baseline objects
          //
          // Get the missing energy in the event
          double met = event->met();
          HEPUtils::P4 metVec = event->missingmom();

          // Baseline electrons
          vector<const HEPUtils::Particle*> baselineElectrons;
          for (const HEPUtils::Particle* electron : event->electrons())
          {
            if (electron->pT() > 10. && electron->abseta() < 2.47) baselineElectrons.push_back(electron);

          }
          // Apply electron efficiency
          // Loose electron ID selection
          applyEfficiency(baselineElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Loose"));

          // Baseline muons have satisfy "medium" criteria and have pT > 3 GeV and |eta| < 2.7
          vector<const HEPUtils::Particle*> baselineMuons;
          for (const HEPUtils::Particle* muon : event->muons())
          {
            if (muon->pT() > 10. && muon->abseta() < 2.4) baselineMuons.push_back(muon);
          }

          // Apply muon efficiency
          // Missing: "Medium" muon ID criteria
          applyEfficiency(baselineMuons, ATLAS::eff2DMu.at("R2"));

          // Baseline jets
          vector<const HEPUtils::Jet*> baselineJets;
          for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
          {
            if (jet->pT() > 20. && fabs(jet->eta()) < 4.5 )
              baselineJets.push_back(jet);
          }

          //
          // Overlap removal
          //

          int tmp_nlep = baselineElectrons.size()+baselineMuons.size();
          removeOverlap(baselineElectrons, baselineMuons, 0.01);
          removeOverlap(baselineJets, baselineElectrons, 0.2);
          removeOverlap(baselineJets, baselineMuons, 0.2);
          auto lambda = [](double lepton_pT) { return std::min(0.4, 0.04 + 10./(lepton_pT) ); };
          removeOverlap(baselineElectrons, baselineJets, lambda);
          //LeptonJetOverlapRemoval(baselineElectrons,baselineJets);
          removeOverlap(baselineMuons, baselineJets, lambda);
          //LeptonJetOverlapRemoval(baselineMuons,baselineJets);

          // Collect all baseline leptons
          vector<const HEPUtils::Particle*> baselineLeptons = baselineElectrons;
          baselineLeptons.insert(baselineLeptons.end(), baselineMuons.begin(), baselineMuons.end());

          vector<const HEPUtils::Particle*> signalElectrons;
          vector<const HEPUtils::Particle*> signalMuons;
          vector<const HEPUtils::Particle*> signalLeptons;
          vector<const HEPUtils::Jet*> signalJets;
          vector<const HEPUtils::Jet*> signalBJets;
          vector<const HEPUtils::Jet*> signalNonBJets;

          // Signal electrons must satisfy the “medium” identification requirement as defined in arXiv: 1902.04655 [hep-ex]

          for (const HEPUtils::Particle* signalElectron : baselineElectrons)
          {
            if (signalElectron->pT() > 20.) signalElectrons.push_back(signalElectron);
          }

          applyEfficiency(signalElectrons, ATLAS::eff1DEl.at("PERF_2017_01_ID_Medium"));


          // Signal muons must have pT > 25 GeV.
          for (const HEPUtils::Particle* signalMuon : baselineMuons)
          {
            if (signalMuon->pT() > 20.) signalMuons.push_back(signalMuon);
          }

          for (const HEPUtils::Jet* signalJet : baselineJets)
          {
            if (signalJet->pT() > 20. && fabs(signalJet->eta()) < 2.4) signalJets.push_back(signalJet);
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

          // Sort by pT
          sort(signalJets.begin(), signalJets.end(), compareJetPt);
          sort(signalLeptons.begin(), signalLeptons.end(), comparePt);

          int nbaselineleptons = baselineLeptons.size();
          int nleptons   = signalLeptons.size();
          int nelectrons = signalElectrons.size();
          int nmuons     = signalMuons.size();
          int njets      = signalJets.size();
          int nbjets     = signalBJets.size();

          // exactly 3 baseline and signal leptons
          bool cut_3lep=true;
          if (nbaselineleptons != 3)cut_3lep=false;
          if (nleptons != 3)cut_3lep=false;

          // b-jet veto
          bool cut_bjet=true;
          if (nbjets>0)cut_bjet=false;

          //lepton pT cuts
          bool cut_leppt = false;
          bool cut_leppt_high = false;
          if(cut_3lep)
          {
            if ( (signalLeptons.at(0)->pT()>25.) && (signalLeptons.at(1)->pT()>25.) && (signalLeptons.at(2)->pT()>20.) )cut_leppt=true;
            if ( (signalLeptons.at(0)->pT()>60.) && (signalLeptons.at(1)->pT()>40.) && (signalLeptons.at(2)->pT()>30.) )cut_leppt_high=true;
          }

          // Calculate variables if pre-selection cuts are passed
          bool cut_SFOS=true;
          bool cut_mlll=true;
          bool cut_Zpeak=true;
          double pTjets(-999), dphijetsinv(-999), Rjetsinv(-999), pTsoft(-999);
          double mTW = 0.;
          double H_boost(-999), HTratio(-999), pTratio(-999);

          if(cut_3lep && cut_bjet && cut_leppt)
          {

            //do assignment by closest to mZ
            double mZ  = 91.1876;
            double mll = -999.;
            double mdiff = 1e6;
            int nSFOS = 0;
            int iZ1(-1), iZ2(-1), iW(-1);

            for (int ilep=0; ilep<nleptons-1; ilep++)
            {
              for (int jlep=ilep+1; jlep<nleptons; jlep++)
              {
                int klep = nleptons - ilep - jlep;

                if ( (signalLeptons.at(ilep)->abspid() == signalLeptons.at(jlep)->abspid()) && (signalLeptons.at(ilep)->pid() != signalLeptons.at(jlep)->pid()) )
                {
                  nSFOS++;
                  //
                  double imll = (signalLeptons.at(ilep)->mom()+signalLeptons.at(jlep)->mom()).m();

                  double imdiff = fabs(mZ - imll);
                  //
                  if (imdiff < mdiff)
                  {
                    mdiff = imdiff;
                    mll   = imll;
                    iZ1   = ilep;
                    iZ2   = jlep;
                    iW    = klep;
                  }
                }
              }
            }

            if (nSFOS==0)cut_SFOS=false;

            // mlll > 105 GeV
            double mlll = (signalLeptons.at(0)->mom()+signalLeptons.at(1)->mom()+signalLeptons.at(2)->mom()).m();
            if (mlll < 105.)cut_mlll=false;

            // require the Zpeak [75,105]
            if ( mll < 75. || mll > 105. )cut_Zpeak=false;

            //====================================================================================================
            // require mTW
            if(cut_SFOS)mTW = sqrt( 2*metVec.pT()*signalLeptons.at(iW)->pT()*(1 - cos(signalLeptons.at(iW)->phi() - metVec.phi())) );

            //====================================================================================================
            // additional variables:
            // Note: have rewritten the ATLAS version to remove TLorentzVectors
            // ISR system

            HEPUtils::P4 vISR;
            for (int ijet=0; ijet<(int)signalJets.size(); ++ijet)
            {
              HEPUtils::P4 jet;
              jet.setEtaPhiMPt(signalJets.at(ijet)->eta(),signalJets.at(ijet)->phi(),signalJets.at(ijet)->mass(),signalJets.at(ijet)->pT());
              vISR += jet;
            }
            // LEP system (massive leptons)
            HEPUtils::P4 vLEP;
            for (int ilep=0; ilep<(int)signalLeptons.size(); ++ilep)
            {
              HEPUtils::P4 lep;
              lep.setEtaPhiMPt(signalLeptons.at(ilep)->eta(),signalLeptons.at(ilep)->phi(),signalLeptons.at(ilep)->mass(),signalLeptons.at(ilep)->pT());
              vLEP += lep;
            }

            HEPUtils::P4 vMET;
            vMET.setPE(metVec.px(), metVec.py(), 0., sqrt(metVec.px()*metVec.px()+metVec.py()*metVec.py()));

            //double pTjets(-999), dphijetsinv(-999), Rjetsinv(-999), pTsoft(-999);
            if (signalJets.size()>0)
            {
              pTjets      = vISR.pT();
              dphijetsinv = vISR.deltaPhi(vMET);
              Rjetsinv    = fabs(vMET.px()*vISR.px() + vMET.py()*vISR.py()) / fabs(pTjets*pTjets);
              pTsoft      = (vLEP + vMET + vISR).pT();
            }

            double pTsoftPP(-999), meff3l(-999), long_inv(-999), pI(-999), boostx(-999), boosty(-999), boostz(-999);
            pTsoftPP = (vLEP + vMET).pT();
            meff3l   = signalLeptons.at(0)->pT()+ signalLeptons.at(1)->pT() + signalLeptons.at(2)->pT() + met;

            //calculating Z-component of the missing energy vector
            long_inv = vLEP.pz()*sqrt(met*met) / sqrt(vLEP.pT()*vLEP.pT()+vLEP.m()*vLEP.m());
            pI = sqrt(vMET.px()*vMET.px() + vMET.py()*vMET.py() + long_inv*long_inv);

            //calculating the boost
            boostx = (vLEP.px() + vMET.px()) / (vLEP.E() + sqrt(pI*pI));
            boosty = (vLEP.py() + vMET.py()) / (vLEP.E() + sqrt(pI*pI));
            boostz = (vLEP.pz() + long_inv) / (vLEP.E() + sqrt(pI*pI));

            HEPUtils::P4 vMETprime;
            vMETprime.setPM(vMET.px(), vMET.py(), long_inv, 0.);

            //

            double bx = -boostx;
            double by = -boosty;
            double bz = -boostz;
            double b2 = bx*bx + by*by + bz*bz;
            double gamma = 1.0 / sqrt(1.0 - b2);

            double metX = vMETprime.px();
            double metY = vMETprime.py();
            double metZ = vMETprime.pz();
            double metT = vMETprime.E();

            double met_bp = bx*metX + by*metY + bz*metZ;
            double met_gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

            // Boost the MET
            // Note that there is a mistake in the ATLAS code snippet
            // They forget to boost this
            vMETprime.setXYZE(metX + met_gamma2*met_bp*bx + gamma*bx*metT,
                  metY + met_gamma2*met_bp*by + gamma*by*metT,
                  metZ + met_gamma2*met_bp*bz + gamma*bz*metT,
                  gamma*(metT + met_bp));

            std::vector<HEPUtils::P4> leptons_boost(3,HEPUtils::P4(0.,0.,0.,0.));

            for (int ilep=0; ilep<3; ilep++)
            {

              double X = signalLeptons[ilep]->mom().px();
              double Y = signalLeptons[ilep]->mom().py();
              double Z = signalLeptons[ilep]->mom().pz();
              double T = signalLeptons[ilep]->mom().E();

              double bp = bx*X + by*Y + bz*Z;
              double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;


              leptons_boost[ilep].setXYZE(X + gamma2*bp*bx + gamma*bx*T,
                  Y + gamma2*bp*by + gamma*by*T,
                  Z + gamma2*bp*bz + gamma*bz*T,
                  gamma*(T + bp));

            }

            H_boost  = leptons_boost[0].p() + leptons_boost[1].p() + leptons_boost[2].p() + vMETprime.p();

            HTratio = meff3l / H_boost;
            pTratio = pTsoftPP / (pTsoftPP + meff3l);

            // Signal regions
            if (signalLeptons.at(0)->pT()>60. && signalLeptons.at(1)->pT()>40. && signalLeptons.at(2)->pT()>30. && njets==0 && mTW>100. && H_boost>250. && pTratio<0.05 && HTratio>0.9)_counters.at("SR-low").add_event(event);
            if (signalLeptons.at(0)->pT()>25. && signalLeptons.at(1)->pT()>25. && signalLeptons.at(2)->pT()>20. && njets>0 && njets<4 && mTW>100. && fabs(dphijetsinv)>2.0 && Rjetsinv>0.55 && Rjetsinv<1.0  && pTjets>100. && met>80. && pTsoft<25.)_counters.at("SR-ISR").add_event(event);


          }

          // Increment cutflows for debugging

          const double w = event->weight();
          _cutflows.fillinit(w);

          bool cut_trigger=true;

          if (_cutflows["SR-ISR"].fillnext({
                        cut_3lep && cut_SFOS,
            cut_trigger,
            cut_bjet,
            cut_mlll,
            cut_leppt,
            cut_Zpeak,
            njets > 0,
            njets < 4,
            fabs(dphijetsinv)>2.0,
            Rjetsinv>0.55 && Rjetsinv<1.0,
            pTjets>100.,
            met > 80.,
            mTW > 100.,
            pTsoft < 25.}, w))_counters.at("SR-ISR").add_event(event);

          if (_cutflows["SR-low"].fillnext({
                        cut_3lep && cut_SFOS,
            cut_trigger,
                        cut_bjet,
            cut_mlll,
                        cut_leppt_high,
            cut_Zpeak,
            njets == 0,
            H_boost>250.,
            pTratio<0.05,
            HTratio>0.9,
            mTW > 100.}, w))_counters.at("SR-low").add_event(event);

          return;
        } // End of event analysis



      void collect_results()
      {
        // Fill a results object with the results for each SR
        // WZ on-shell
        add_result(SignalRegionData(_counters.at("SR-low"), 51., {46. , 5.}));
        add_result(SignalRegionData(_counters.at("SR-ISR"),  30., { 23.4 ,  2.1}));

  // Cutflow printout
        #ifdef CHECK_CUTFLOW
         _cutflows["SR-ISR"].normalize(1370, 1);
   _cutflows["SR-low"].normalize(1370, 1);
   cout << "\nCUTFLOWS:\n" << _cutflows << endl;
         cout << "\nSRCOUNTS:\n";
         // for (double x : _srnums) cout << x << "  ";
         for (auto& pair : _counters) cout << pair.second.weight_sum() << "  ";
         cout << "\n" << endl;
        #endif


      }

      void analysis_specific_reset()
      {
        // Clear signal regions
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_3LEP_eRJR_139invfb)

  }
}


