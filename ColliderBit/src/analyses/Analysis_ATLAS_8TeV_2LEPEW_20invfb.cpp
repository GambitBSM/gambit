#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
//#include "gambit/ColliderBit/analyses/Perf_Plot.hpp"

// #define CUTFLOW


/* The ATLAS 2 lepton EW analysis (20fb^-1)

   based on: arXiv: 1403.5294

   Code by Martin White
   Updated by Kelton Whiteaker, August 2020

   Known features: Signal leptons in the paper have certain isolation plus ID cuts (these are ignored here by default)

   a) The trigger efficiencies are important! We need to multiply by these to get the correct yields (after which the cutflows agree rather well).

*/

namespace Gambit
{
  namespace ColliderBit
  {

    using namespace std;

    // double phi_mpi_pi_2lep(double x){
    //   while (x >= pi) x -= 2*M_PI;
    //   while (x < -pi) x += 2*M_PI;
    // }


    bool sortByPT_2lep(const HEPUtils::Particle* lep1, const HEPUtils::Particle* lep2) { return (lep1->pT() > lep2->pT()); }

    class Analysis_ATLAS_8TeV_2LEPEW_20invfb : public Analysis
    {
      private:

        // Numbers passing cuts (doubles because we will use the trigger eff)
        double _num_MT2_90_SF;
        double _num_MT2_90_DF;
        double _num_MT2_120_SF;
        double _num_MT2_120_DF;
        double _num_MT2_150_SF;
        double _num_MT2_150_DF;
        double _num_WWa_SF;
        double _num_WWa_DF;
        double _num_WWb_SF;
        double _num_WWb_DF;
        double _num_WWc_SF;
        double _num_WWc_DF;
        double _num_Zjets;

        vector<double> cutFlowVector;
        vector<double> cutFlowIncrements;
        vector<string> cutFlowVector_str;
        const static int NCUTS=90;

        // Debug histos
  //      Perf_Plot* plots_mt2_NOmt2_SF;  // SR-mT2, no mt2 cut, SF
  //      Perf_Plot* plots_mt2_NOmt2_DF;  // SR-mT2, no mt2 cut, DF
  //      Perf_Plot* plots_Zjets_NOmet_SF;  // SR-Zjets, no met cut, SF
  //      Perf_Plot* plots_WWa_NOmll_SF;  // SR-WWa, no mll cut, SF
  //      Perf_Plot* plots_WWa_NOmll_DF;  // SR-WWa, no mll cut, DF
  //      Perf_Plot* plots_WWa_NOmllORmet_SF;  // SR-WWa, no mll cut or met cut, SF
  //      Perf_Plot* plots_WWa_NOmllORmet_DF;  // SR-WWa, no mll cut or met cut, DF

      public:

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        Analysis_ATLAS_8TeV_2LEPEW_20invfb()
        {

          set_analysis_name("ATLAS_8TeV_2LEPEW_20invfb");
          set_luminosity(20.3);

          _num_MT2_90_SF=0;
          _num_MT2_90_DF=0;
          _num_MT2_120_SF=0;
          _num_MT2_120_DF=0;
          _num_MT2_150_SF=0;
          _num_MT2_150_DF=0;
          _num_WWa_SF=0;
          _num_WWa_DF=0;
          _num_WWb_SF=0;
          _num_WWb_DF=0;
          _num_WWc_SF=0;
          _num_WWc_DF=0;
          _num_Zjets=0;

          for(int i=0;i<NCUTS;i++)
          {
            cutFlowVector.push_back(0);
            cutFlowVector_str.push_back("");
            cutFlowIncrements.push_back(0.);

  //        vector<const char*> variablesNames = {"mll","met","mt2"};
  //        plots_mt2_NOmt2_SF = new Perf_Plot(analysis_name()+"_SF_SR-mT2_no-mt2-cut", &variablesNames);
  //        plots_mt2_NOmt2_DF = new Perf_Plot(analysis_name()+"_DF_SR-mT2_no-mt2-cut", &variablesNames);
  //        plots_Zjets_NOmet_SF = new Perf_Plot(analysis_name()+"_SF_SR-Zjets_no-met-cut", &variablesNames);
  //        plots_WWa_NOmll_SF = new Perf_Plot(analysis_name()+"_SF_SR-WWa_no-mll-cut", &variablesNames);
  //        plots_WWa_NOmll_DF = new Perf_Plot(analysis_name()+"_DF_SR-WWa_no-mll-cut", &variablesNames);
  //        plots_WWa_NOmllORmet_SF = new Perf_Plot(analysis_name()+"_SF_SR-WWa_no-mll-met-cuts", &variablesNames);
  //        plots_WWa_NOmllORmet_DF = new Perf_Plot(analysis_name()+"_DF_SR-WWa_no-mll-met-cuts", &variablesNames);

          }

        }

        void EleEleOverlapRemoval(vector<const HEPUtils::Particle*> &vec1, vector<const HEPUtils::Particle*> &vec2, double DeltaRMax)
        {
          //Routine to do electron-electron overlap check
          //Discard lowest energy electron if two are found overlapping
          vector<const HEPUtils::Particle*> Survivors;

          for(unsigned int it1 = 0; it1 < vec1.size(); it1++)
          {
            bool overlap = false;
            HEPUtils::P4 lep1mom=vec1.at(it1)->mom();
            for(unsigned int it2 = 0; it2 < vec2.size(); it2++)
            {
              if(it1==it2)continue;
              HEPUtils::P4 lep2mom=vec2.at(it2)->mom();
              double dR;

              dR=lep1mom.deltaR_eta(lep2mom);

              if(fabs(dR) <= DeltaRMax && lep1mom.E()<lep2mom.E()) overlap=true;
            }
            if(overlap) continue;
            Survivors.push_back(vec1.at(it1));
          }
          vec1=Survivors;

          return;
        }

        void LepLepOverlapRemoval(vector<const HEPUtils::Particle*> &vec1, vector<const HEPUtils::Particle*> &vec2, double DeltaRMax)
        {
          //Routine to do lepton-lepton overlap check
          //Discard first lepton if overlap is found
          vector<const HEPUtils::Particle*> Survivors;

          for(unsigned int it1 = 0; it1 < vec1.size(); it1++)
          {
            bool overlap = false;
            HEPUtils::P4 lep1mom=vec1.at(it1)->mom();
            for(unsigned int it2 = 0; it2 < vec2.size(); it2++)
            {
              if(it1==it2)continue;
              HEPUtils::P4 lep2mom=vec2.at(it2)->mom();
              double dR;

              dR=lep1mom.deltaR_eta(lep2mom);

              if(fabs(dR) <= DeltaRMax)overlap=true;
            }
            if(overlap) continue;
            Survivors.push_back(vec1.at(it1));
          }
          vec1=Survivors;

          return;
        }

        void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &lepvec, double DeltaRMax)
        {
          //Routine to do jet-lepton check
          //Discards jets if they are within DeltaRMax of a lepton

          vector<const HEPUtils::Jet*> Survivors;

          for(unsigned int itjet = 0; itjet < jetvec.size(); itjet++)
          {
            bool overlap = false;
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++)
            {
              HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
              double dR=jetmom.deltaR_eta(lepmom);

              if(fabs(dR) <= DeltaRMax) overlap=true;
            }
            if(overlap) continue;
            Survivors.push_back(jetvec.at(itjet));
          }
          jetvec=Survivors;

          return;
        }

        void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec, double DeltaRMax)
        {
          //Routine to do lepton-jet check
          //Discards leptons if they are within DeltaRMax of a jet

          vector<const HEPUtils::Particle*> Survivors;

          for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++)
          {
            bool overlap = false;
            HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
            for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++)
            {
              HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
              double dR;

              dR=jetmom.deltaR_eta(lepmom);

              if(fabs(dR) <= DeltaRMax) overlap=true;
            }
            if(overlap) continue;
            Survivors.push_back(lepvec.at(itlep));
          }
          lepvec=Survivors;

          return;
        }

        void RemoveLeptonsMllLt12(vector<const HEPUtils::Particle*> &lepvec)
        {

          ssize_t removeLep1=-1;
          ssize_t removeLep2=-1;
          vector<const HEPUtils::Particle*> Survivors;

          //Function removes SF lepton pairs with m_ll < 12 GeV
          for(unsigned int itlep1 = 0; itlep1 < lepvec.size(); itlep1++)
          {
            HEPUtils::P4 lepmom1=lepvec.at(itlep1)->mom();
            for(unsigned int itlep2= itlep1; itlep2 < lepvec.size(); itlep2++)
            {
              if(itlep1!=itlep2)
              {
                HEPUtils::P4 lepmom2=lepvec.at(itlep2)->mom();
                double mass=(lepmom1+lepmom2).m();
                if(mass<12.)
                {
                  removeLep1=itlep1;
                  removeLep2=itlep2;
                }
              }
            }
          }
          for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++)
          {
            if(itlep!=removeLep1 && itlep!=removeLep2) Survivors.push_back(lepvec.at(itlep));
          }

          lepvec=Survivors;
        }

        void run(const HEPUtils::Event* event)
        {

          // Missing energy
          HEPUtils::P4 ptot = event->missingmom();
          double met = event->met();

          // Now define vector of baseline electrons
          vector<const HEPUtils::Particle*> signalElectrons;
          for (const HEPUtils::Particle* electron : event->electrons())
          {
            if (electron->pT() > 10. && fabs(electron->eta()) < 2.47) signalElectrons.push_back(electron);
          }

          // Apply electron efficiency
          ATLAS::applyElectronEff(signalElectrons);

          // Now define vector of baseline muons
          vector<const HEPUtils::Particle*> signalMuons;
          for (const HEPUtils::Particle* muon : event->muons())
          {
            if (muon->pT() > 10. && fabs(muon->eta()) < 2.4) signalMuons.push_back(muon);
          }

          // Apply muon efficiency
          ATLAS::applyMuonEff(signalMuons);

          vector<const HEPUtils::Jet*> signalJets;
          for (const HEPUtils::Jet* jet : event->jets())
          {
            if (jet->pT() > 20. && fabs(jet->eta()) < 4.5) signalJets.push_back(jet);
            //if(jet->btag() && fabs(jet->eta()) < 2.5 && jet->pT() > 20.) bJets.push_back(jet);
          }

          vector<const HEPUtils::Particle*> signalTaus;
          for (const HEPUtils::Particle* tau : event->taus())
          {
            if (tau->pT() > 20. && tau->abseta() < 2.5) signalTaus.push_back(tau);
          }
          ATLAS::applyTauEfficiencyR1(signalTaus);

          // Overlap removal

          //Note that ATLAS use |eta|<10 for removing jets close to electrons
          //Then 2.8 is used for the rest of the overlap process
          //Then the signal cut is applied for signal jets

          EleEleOverlapRemoval(signalElectrons,signalElectrons,0.05);
          JetLeptonOverlapRemoval(signalJets,signalElectrons,0.2);
          LepLepOverlapRemoval(signalTaus,signalElectrons,0.2);
          LepLepOverlapRemoval(signalTaus,signalMuons,0.2);
          LeptonJetOverlapRemoval(signalElectrons,signalJets,0.4);
          LeptonJetOverlapRemoval(signalMuons,signalJets,0.4);
          //Note have not bothered with close-by electron and muon pairs (bremsstrahlung probably not significant in signal MC)

          RemoveLeptonsMllLt12(signalElectrons);
          RemoveLeptonsMllLt12(signalMuons);
          JetLeptonOverlapRemoval(signalJets,signalTaus,0.2);

          // Make lists of candidate electrons/muons for later cuts on num candidates
          vector<const HEPUtils::Particle*> candidateElectrons;
          vector<const HEPUtils::Particle*> candidateMuons;
          candidateElectrons = signalElectrons;
          candidateMuons = signalMuons;
          vector<const HEPUtils::Particle*> candidateLeptons;
          for (const HEPUtils::Particle* ele : candidateElectrons)
          {
            candidateLeptons.push_back(ele);
          }
          for (const HEPUtils::Particle* muo : candidateMuons)
          {
            candidateLeptons.push_back(muo);
          }

          ATLAS::applyTightIDElectronSelection(signalElectrons);

          int numElectrons=signalElectrons.size();
          int numMuons=signalMuons.size();
          int numTaus=signalTaus.size();

          //Search for at least one SFOS pair
          //m_SFOS must be > 12 GeV


          //Classify jets into various categories
          vector<const HEPUtils::Jet*> centralBJets;
          vector<const HEPUtils::Jet*> centralNonBJets;
          vector<const HEPUtils::Jet*> forwardJets;

          const std::vector<double> a = {0,10.};
          const std::vector<double> b = {0,10000.};
          const std::vector<double> c = {0.8};
          HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);

          for (const HEPUtils::Jet* jet : signalJets)
          {
            bool hasTag=has_tag(_eff2d, jet->abseta(), jet->pT());
            if(fabs(jet->eta()) < 2.4)
            {
              if(jet->btag() && hasTag)
              {
                centralBJets.push_back(jet);
              }
              else
              {
                centralNonBJets.push_back(jet);
              }
            }
            if(fabs(jet->eta()) > 2.4 && jet->pT()>30.)forwardJets.push_back(jet);
          }

          //Common cuts for all signal regions

          bool leptonPTCut=false;
          vector<const HEPUtils::Particle*> signalLeptons;
          for (const HEPUtils::Particle* ele : signalElectrons)
          {
            signalLeptons.push_back(ele);
          }

          for (const HEPUtils::Particle* muo : signalMuons)
          {
            signalLeptons.push_back(muo);
          }

          std::sort(signalLeptons.begin(), signalLeptons.end(), sortByPT_2lep);

          if(signalLeptons.size()==2 && signalLeptons[0]->pT()>35. && signalLeptons[1]->pT()>20. && candidateLeptons.size()==2)leptonPTCut=true;
          //if(signalLeptons.size()==2 && signalLeptons[0]->pT()>35. && signalLeptons[1]->pT()>20.)leptonPTCut=true;  // if you don't want the candidates cut

          bool mllCut=false;
          if(signalLeptons.size()==2 && (signalLeptons[0]->mom()+signalLeptons[1]->mom()).m() > 20.)mllCut=true;

          bool isOS=false;
          if(signalLeptons.size()==2 && (signalLeptons[0]->pid()*signalLeptons[1]->pid()<0))isOS=true;

          bool passZVeto=true;
          double mLepLep=0.;
          if(signalLeptons.size()==2)mLepLep=(signalLeptons[0]->mom()+signalLeptons[1]->mom()).m();
          if(mLepLep>81.2 && mLepLep<101.2)passZVeto=false;

          bool cut_SRMT290=false;
          bool cut_SRMT2120=false;
          bool cut_SRMT2150=false;

          bool tauVeto=false;
          if(numTaus==0)tauVeto=true;

          int numCentralNonBJets=centralNonBJets.size();
          int numCentralBJets=centralBJets.size();
          int numForwardJets=forwardJets.size();

          // need to initialize these in this scope to use them when filling perf_plots later
          double mt2 = 0.0;
          double dPhiMin=9999;
          double ETmiss_rel = 0.0;
          double mll = mLepLep;

          //Now do the MT2 signal regions

          if(leptonPTCut && mllCut && isOS && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0)
          {

            //Calculate MT2
            double pa[3] = { 0, signalLeptons[0]->mom().px(), signalLeptons[0]->mom().py() };
            double pb[3] = { 0, signalLeptons[1]->mom().px(), signalLeptons[1]->mom().py() };
            double pmiss[3] = { 0, ptot.px(), ptot.py() };
            double mn = 0.;

            mt2_bisect::mt2 mt2_calc;

            mt2_calc.set_momenta(pa,pb,pmiss);
            mt2_calc.set_mn(mn);
            mt2 = mt2_calc.get_mt2();
  //          double mt2 = mt2_calc.get_mt2();  // was already initialized

            mll=(signalLeptons[0]->mom() + signalLeptons[1]->mom()).m();
  //          double mll=(signalLeptons[0]->mom() + signalLeptons[1]->mom()).m();


            if(mt2>90.)cut_SRMT290=true;
            if(mt2>120.)cut_SRMT2120=true;
            if(mt2>150.)cut_SRMT2150=true;

            //Signal region increments use the trigger efficiencies for ee, emu and mumu triggers
            if(mt2 > 90. && (numElectrons==1 && numMuons==1)) _num_MT2_90_DF += event->weight() * 0.89;
            if(passZVeto && mt2 > 90. && (numElectrons==2 && fabs(mll-91.)>10)) _num_MT2_90_SF += event->weight() * 0.97;
            if(passZVeto && mt2 > 90. && (numMuons==2 && fabs(mll-91.)>10)) _num_MT2_90_SF += event->weight() * 0.75;

            if(mt2 > 120. && (numElectrons==1 && numMuons==1)) _num_MT2_120_DF += event->weight() * 0.89;
            if(passZVeto && mt2 > 120. && (numElectrons==2 && fabs(mll-91.)>10)) _num_MT2_120_SF += event->weight() * 0.97;
            if(passZVeto && mt2 > 120. &&  (numMuons==2 && fabs(mll-91.)>10)) _num_MT2_120_SF += event->weight() * 0.75;

            if(mt2 > 150. && (numElectrons==1 && numMuons==1)) _num_MT2_150_DF += event->weight() * 0.89;
            if(passZVeto && mt2 > 150. && (numElectrons==2 && fabs(mll-91.)>10)) _num_MT2_150_SF += event->weight() * 0.97;
            if(passZVeto && mt2 > 150. && (numMuons==2 && fabs(mll-91.)>10)) _num_MT2_150_SF += event->weight() * 0.75;

          }

          //Now do the WW channels
          bool passZVeto_WWa=false;
          bool passPTll_WWa=false;
          bool passMetRel_WWa=false;
          bool passMll_WWa=false;

          bool passMT2_WWb=false;
          bool passMT2_WWc=false;
          bool passMll_WWb=false;

          if(leptonPTCut && mllCut && isOS && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0)
          {

            //Calculate ETmiss_rel
            dPhiMin=9999;
  //          double dPhiMin=9999;
            for(const HEPUtils::Jet* jet : centralBJets)
            {
              double dphi=fabs(jet->mom().deltaPhi(ptot));
              if(fabs(dphi)<dPhiMin)dPhiMin=dphi;
            }

            for(const HEPUtils::Jet* jet : centralNonBJets)
            {
              double dphi=fabs(jet->mom().deltaPhi(ptot));
              if(fabs(dphi)<dPhiMin)dPhiMin=dphi;
            }

            for(const HEPUtils::Particle* lep : signalLeptons)
            {
              double dphi=fabs(lep->mom().deltaPhi(ptot));
              if(fabs(dphi)<dPhiMin)dPhiMin=dphi;
            }

            ETmiss_rel=0;
  //          double ETmiss_rel=0;
            if(dPhiMin<(3.14/2))
            {
              ETmiss_rel=met*sin(dPhiMin);
            }
            else
            {
              ETmiss_rel=met;
            }

            //Calculate MT2
            double pa[3] = { 0, signalLeptons[0]->mom().px(), signalLeptons[0]->mom().py() };
            double pb[3] = { 0, signalLeptons[1]->mom().px(), signalLeptons[1]->mom().py() };
            double pmiss[3] = { 0, ptot.px(), ptot.py() };
            double mn = 0.;

            mt2_bisect::mt2 mt2_calc;

            mt2_calc.set_momenta(pa,pb,pmiss);
            mt2_calc.set_mn(mn);
            mt2 = mt2_calc.get_mt2();
  //          double mt2 = mt2_calc.get_mt2();

            mll=(signalLeptons[0]->mom() + signalLeptons[1]->mom()).m();
  //          double mll=(signalLeptons[0]->mom() + signalLeptons[1]->mom()).m();

            //Variables for cutflow debugging

            if(fabs(mll-91.2)>10.)passZVeto_WWa=true;
            if((signalLeptons[0]->mom() + signalLeptons[1]->mom()).pT() > 80.)passPTll_WWa=true;
            if(ETmiss_rel > 80.)passMetRel_WWa=true;
            if(mll < 120.) passMll_WWa=true;

            if(mt2 > 90.)passMT2_WWb=true;
            if(mll < 170.)passMll_WWb=true;

            if(mt2 > 100.)passMT2_WWc=true;


            if((signalLeptons[0]->mom() + signalLeptons[1]->mom()).pT() > 80. &&
               ETmiss_rel > 80. &&
               mll < 120. &&
               (numElectrons==1 && numMuons==1)) _num_WWa_DF += event->weight() * 0.89;

            if((signalLeptons[0]->mom() + signalLeptons[1]->mom()).pT() > 80. &&
               ETmiss_rel > 80. &&
               mll < 120. &&
               (numElectrons==2 && fabs(mll-91.)>10.)) _num_WWa_SF += event->weight() * 0.97;

            if((signalLeptons[0]->mom() + signalLeptons[1]->mom()).pT() > 80. &&
               ETmiss_rel > 80. &&
               mll < 120. &&
               (numMuons==2 && fabs(mll-91.)>10.)) _num_WWa_SF += event->weight() * 0.75;

            if(mt2 > 90. &&
               mll < 170. &&
               (numElectrons==1 && numMuons==1)) _num_WWb_DF += event->weight() * 0.89;

            if(mt2 > 90. &&
               mll < 170. &&
               (numElectrons==2 && fabs(mll-91.)>10.)) _num_WWb_SF += event->weight() * 0.97;


            if(mt2 > 90. &&
               mll < 170. &&
               (numMuons==2 && fabs(mll-91.)>10.)) _num_WWb_SF += event->weight() * 0.75;

            if(mt2 > 100. && (numElectrons==1 && numMuons==1)) _num_WWc_DF += event->weight() * 0.89;

            if(mt2 > 100. && (numElectrons==2 && fabs(mll-91.)>10.)) _num_WWc_SF += event->weight() * 0.97;

            if(mt2 > 100. && (numMuons==2 && fabs(mll-91.)>10.)) _num_WWc_SF += event->weight() * 0.75;

          }

          //Finally, do the Z+jets signal region

          bool passZWindow=true;
          bool passPTll=true;
          bool passETmissRel=true;
          bool passdRll=true;
          bool passMjj=true;
          bool passJetPT=true;

          if(leptonPTCut && mllCut && isOS && tauVeto && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0)
          {

            mll=(signalLeptons[0]->mom() + signalLeptons[1]->mom()).m();
  //          double mll=(signalLeptons[0]->mom() + signalLeptons[1]->mom()).m();

            //Calculate ETmiss_rel
            dPhiMin=9999;
  //          double dPhiMin=9999;
            for(const HEPUtils::Jet* jet : centralBJets)
            {
              double dphi=jet->mom().deltaPhi(ptot);
              if(dphi<dPhiMin)dPhiMin=dphi;
            }

            for(const HEPUtils::Jet* jet : centralNonBJets)
            {
              double dphi=jet->mom().deltaPhi(ptot);
              if(dphi<dPhiMin)dPhiMin=dphi;
            }

            for(const HEPUtils::Particle* lep : signalLeptons)
            {
              double dphi=lep->mom().deltaPhi(ptot);
              if(dphi<dPhiMin)dPhiMin=dphi;
            }

            ETmiss_rel=0;
  //          double ETmiss_rel=0;
            if(dPhiMin<(3.14/2))
            {
              ETmiss_rel=met*sin(dPhiMin);
            }
            else
            {
              ETmiss_rel=met;
            }


            double dRll = signalLeptons[0]->mom().deltaR_eta(signalLeptons[1]->mom());

            double mjj = (centralNonBJets[0]->mom()+centralNonBJets[1]->mom()).m();


            //Cuts for cutflow debugging
            if(ETmiss_rel<=80.)passETmissRel=false;
            if(fabs(mll-91.)>10.)passZWindow=false;
            if((signalLeptons[0]->mom()+signalLeptons[1]->mom()).pT()<=80.)passPTll=false;
            if(!(dRll > 0.3 && dRll < 1.5))passdRll=false;
            if(!(mjj > 50. && mjj<100.))passMjj=false;
            if(!(centralNonBJets[0]->pT()>45. && centralNonBJets[1]->pT()>45.))passJetPT=false;

            if(fabs(mll-91.)<10 && ETmiss_rel>80. && (signalLeptons[0]->mom()+signalLeptons[1]->mom()).pT()>80. && dRll > 0.3 && dRll < 1.5 && mjj > 50. && mjj<100. && passJetPT && (numElectrons==2 && numMuons==0)) _num_Zjets += event->weight() * 0.97;

            if(fabs(mll-91.)<10 && ETmiss_rel>80. && (signalLeptons[0]->mom()+signalLeptons[1]->mom()).pT()>80. && dRll > 0.3 && dRll < 1.5 && mjj > 50. && mjj<100. && passJetPT && (numElectrons==0 && numMuons==2)) _num_Zjets += event->weight() * 0.75;

          }

  //        vector<double> variables={mll, ETmiss_rel, mt2};
  //        if(leptonPTCut && mllCut && isOS && ((numElectrons==0 && numMuons==2) || (numElectrons==2 && numMuons==0)) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto)plots_mt2_NOmt2_SF->fill(&variables);
  //        if(leptonPTCut && mllCut && isOS && tauVeto && signalElectrons.size()==1 && signalMuons.size()==1 && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0)plots_mt2_NOmt2_DF->fill(&variables);
  //        if(tauVeto && leptonPTCut && mllCut && isOS && ((numElectrons==0 && numMuons==2) || (numElectrons==2 && numMuons==0)) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll && passdRll && passMjj && passJetPT)plots_Zjets_NOmet_SF->fill(&variables);
  //        if(tauVeto && leptonPTCut && mllCut && isOS && ((numElectrons==0 && numMuons==2) || (numElectrons==2 && numMuons==0)) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passPTll_WWa && passMetRel_WWa)plots_WWa_NOmll_SF->fill(&variables);
  //        if(tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passPTll_WWa && passMetRel_WWa)plots_WWa_NOmll_DF->fill(&variables);
  //        if(tauVeto && leptonPTCut && mllCut && isOS && ((numElectrons==0 && numMuons==2) || (numElectrons==2 && numMuons==0)) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passPTll_WWa)plots_WWa_NOmllORmet_SF->fill(&variables);
  //        if(tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passPTll_WWa)plots_WWa_NOmllORmet_DF->fill(&variables);

          cutFlowVector_str[0] = "No cuts ";
          cutFlowVector_str[1] = "2 electrons ";
          cutFlowVector_str[2] = "Lepton pT cuts (trigger) ";
          cutFlowVector_str[3] = "mll cuts ";
          cutFlowVector_str[4] = "OS leptons ";
          cutFlowVector_str[5] = "tau veto ";
          cutFlowVector_str[6] = "e+e-: Jet veto ";
          cutFlowVector_str[7] = "e+e-: Z veto ";
          cutFlowVector_str[8] = "e+e-: SR-MT290 ";
          cutFlowVector_str[9] = "e+e-: SR-MT2120 ";
          cutFlowVector_str[10] = "e+e-: SR-MT2150 ";
          cutFlowVector_str[11] = "mu+mu-: 2 signal leptons ";
          cutFlowVector_str[12] = "mu+mu-: Jet veto ";
          cutFlowVector_str[13] = "mu+mu-: Z veto ";
          cutFlowVector_str[14] = "mu+mu-: SR-MT290 ";
          cutFlowVector_str[15] = "mu+mu-: SR-MT2120 ";
          cutFlowVector_str[16] = "mu+mu-: SR-MT2150 ";
          cutFlowVector_str[17] = "e+-mu-+: 2 signal leptons ";
          cutFlowVector_str[18] = "e+-mu-+: Jet veto ";
          cutFlowVector_str[19] = "e+-mu-+: SR-MT290 ";
          cutFlowVector_str[20] = "e+-mu-+: SR-MT2120 ";
          cutFlowVector_str[21] = "e+-mu-+: SR-MT2150 ";
          cutFlowVector_str[22] = "SRZjets e+e-: 2 signal leptons ";
          cutFlowVector_str[23] = "SRZjets e+e-: >=2 light jets ";
          cutFlowVector_str[24] = "SRZjets e+e-: No b and forward jets ";
          cutFlowVector_str[25] = "SRZjets e+e-: Z window ";
          cutFlowVector_str[26] = "SRZjets e+e-: pTll > 80 ";
          cutFlowVector_str[27] = "SRZjets e+e-: ETmissrel ";
          cutFlowVector_str[28] = "SRZjets e+e-: dRll ";
          cutFlowVector_str[29] = "SRZjets e+e-: mjj ";
          cutFlowVector_str[30] = "SRZjets e+e-: jet pT ";
          cutFlowVector_str[31] = "SRZjets mu+mu-: 2 signal leptons ";
          cutFlowVector_str[32] = "SRZjets mu+mu-: >=2 light jets ";
          cutFlowVector_str[33] = "SRZjets mu+mu-: No b and forward jets ";
          cutFlowVector_str[34] = "SRZjets mu+mu-: Z window ";
          cutFlowVector_str[35] = "SRZjets mu+mu-: pTll > 80 ";
          cutFlowVector_str[36] = "SRZjets mu+mu-: ETmissrel ";
          cutFlowVector_str[37] = "SRZjets mu+mu-: dRll ";
          cutFlowVector_str[38] = "SRZjets mu+mu-: mjj ";
          cutFlowVector_str[39] = "SRZjets mu+mu-: jet pT ";
          cutFlowVector_str[40] = "SRWWa e+e-: 2 leptons ";
          cutFlowVector_str[41] = "SRWWa e+e-: Jet veto ";
          cutFlowVector_str[42] = "SRWWa e+e-: Z veto ";
          cutFlowVector_str[43] = "SRWWa e+e-: pTll ";
          cutFlowVector_str[44] = "SRWWa e+e-: ETmissrel ";
          cutFlowVector_str[45] = "SRWWa e+e-: mll ";
          cutFlowVector_str[46] = "SRWWa mu+mu-: 2 leptons ";
          cutFlowVector_str[47] = "SRWWa mu+mu-: Jet veto ";
          cutFlowVector_str[48] = "SRWWa mu+mu-: Z veto ";
          cutFlowVector_str[49] = "SRWWa mu+mu-: pTll ";
          cutFlowVector_str[50] = "SRWWa mu+mu-: ETmissrel ";
          cutFlowVector_str[51] = "SRWWa mu+mu-: mll ";
          cutFlowVector_str[52] = "SRWWa e+mu-: 2 leptons ";
          cutFlowVector_str[53] = "SRWWa e+mu-: Jet veto ";
          cutFlowVector_str[54] = "SRWWa e+mu-: pTll ";
          cutFlowVector_str[55] = "SRWWa e+mu-: ETmissrel ";
          cutFlowVector_str[56] = "SRWWa e+mu-: mll ";
          cutFlowVector_str[57] = "SRWWb e+e-: 2 leptons ";
          cutFlowVector_str[58] = "SRWWb e+e-: Jet veto ";
          cutFlowVector_str[59] = "SRWWb e+e-: Z veto ";
          cutFlowVector_str[60] = "SRWWb e+e-: mT2 > 90 ";
          cutFlowVector_str[61] = "SRWWb e+e-: mll < 170 ";
          cutFlowVector_str[62] = "SRWWb mu+mu-: 2 leptons ";
          cutFlowVector_str[63] = "SRWWb mu+mu-: Jet veto ";
          cutFlowVector_str[64] = "SRWWb mu+mu-: Z veto ";
          cutFlowVector_str[65] = "SRWWb mu+mu-: mT2 > 90 ";
          cutFlowVector_str[66] = "SRWWb mu+mu-: mll < 170 ";
          cutFlowVector_str[67] = "SRWWb e+mu-: 2 leptons ";
          cutFlowVector_str[68] = "SRWWb e+mu-: Jet veto ";
          cutFlowVector_str[69] = "SRWWb e+mu-: mT2 > 90 ";
          cutFlowVector_str[70] = "SRWWb e+mu-: mll < 170 ";
          cutFlowVector_str[71] = "SRWWc e+e-: 2 leptons ";
          cutFlowVector_str[72] = "SRWWc e+e-: Jet veto ";
          cutFlowVector_str[73] = "SRWWc e+e-: Z veto ";
          cutFlowVector_str[74] = "SRWWc e+e-: mT2 > 100 ";
          cutFlowVector_str[75] = "SRWWc mu+mu-: 2 leptons ";
          cutFlowVector_str[76] = "SRWWc mu+mu-: Jet veto ";
          cutFlowVector_str[77] = "SRWWc mu+mu-: Z veto ";
          cutFlowVector_str[78] = "SRWWc mu+mu-: mT2 > 100 ";
          cutFlowVector_str[79] = "SRWWc e+mu-: 2 leptons ";
          cutFlowVector_str[80] = "SRWWc e+mu-: Jet veto ";
          cutFlowVector_str[81] = "SRWWc e+mu-: mT2 > 100 ";

          for(int j=0;j<NCUTS;j++)
          {
            if(j>=0 && j<=10)cutFlowIncrements[j]=0.97;
            if(j>=11 && j<=16)cutFlowIncrements[j]=0.75;
            if(j>=17 && j<=21)cutFlowIncrements[j]=0.89;

            if(j>=22 && j<=30)cutFlowIncrements[j]=0.97;
            if(j>=31 && j<=39)cutFlowIncrements[j]=0.75;

            if(j>=40 && j<=45)cutFlowIncrements[j]=0.97;
            if(j>=46 && j<=51)cutFlowIncrements[j]=0.75;
            if(j>=52 && j<=56)cutFlowIncrements[j]=0.89;

            if(j>=57 && j<=61)cutFlowIncrements[j]=0.97;
            if(j>=62 && j<=66)cutFlowIncrements[j]=0.75;
            if(j>=67 && j<=70)cutFlowIncrements[j]=0.89;

            if(j>=71 && j<=74)cutFlowIncrements[j]=0.97;
            if(j>=75 && j<=78)cutFlowIncrements[j]=0.75;
            if(j>=79 && j<=81)cutFlowIncrements[j]=0.89;
          }


          for(int j=0;j<NCUTS;j++)
          {
            if( (j==0) ||

                (j==1 && (numElectrons==2 && numMuons==0)) ||

                (j==2 && (numElectrons==2 && numMuons==0) && leptonPTCut) ||

                (j==3 && (numElectrons==2 && numMuons==0) && leptonPTCut && mllCut) ||

                (j==4 && (numElectrons==2 && numMuons==0) && leptonPTCut && mllCut && isOS) ||

                (j==5 && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && tauVeto) ||

                (j==6 && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==7 && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto) ||

                (j==8 && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto && cut_SRMT290) ||

                (j==9 && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto && cut_SRMT2120) ||

                (j==10 && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto && cut_SRMT2150) ||

                //mumu MT2 regions

                (j==11 && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && tauVeto) ||

                (j==12 && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==13 && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto) ||

                (j==14 && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto && cut_SRMT290) ||

                (j==15 && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto && cut_SRMT2120) ||

                (j==16 && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && tauVeto && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto && cut_SRMT2150) ||

                //emu MT2 regions

                (j==17 && leptonPTCut && mllCut && isOS && tauVeto && signalElectrons.size()==1 && signalMuons.size()==1 && tauVeto) ||

                (j==18 && leptonPTCut && mllCut && isOS && tauVeto && signalElectrons.size()==1 && signalMuons.size()==1 && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==19 && leptonPTCut && mllCut && isOS && tauVeto && signalElectrons.size()==1 && signalMuons.size()==1 && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && cut_SRMT290) ||

                (j==20 && leptonPTCut && mllCut && isOS && tauVeto && signalElectrons.size()==1 && signalMuons.size()==1 && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && cut_SRMT2120) ||

                (j==21 && leptonPTCut && mllCut && isOS && tauVeto && signalElectrons.size()==1 && signalMuons.size()==1 && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && cut_SRMT2150) ||

                //Start SR Z jets e+e-
                (j==22 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0)) ||

                (j==23 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets>=2) ||

                (j==24 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0) ||

                (j==25 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow) ||

                (j==26 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll) ||

                (j==27 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll && passETmissRel) ||

                (j==28 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll && passETmissRel && passdRll) ||

                (j==29 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll && passETmissRel && passdRll && passMjj) ||

                (j==30 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll && passETmissRel && passdRll && passMjj && passJetPT) ||

                //Start SR Z jets mu+mu-
                (j==31 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2)) ||

                (j==32 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets>=2) ||

                (j==33 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0) ||

                (j==34 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow) ||

                (j==35 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll) ||

                (j==36 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll && passETmissRel) ||

                (j==37 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll && passETmissRel && passdRll) ||

                (j==38 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll && passETmissRel && passdRll && passMjj) ||

                (j==39 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets>=2 && numCentralBJets==0 && numForwardJets==0 && passZWindow && passPTll && passETmissRel && passdRll && passMjj && passJetPT) ||

                //Now start WWa e+e-
                (j==40 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0)) ||

                (j==41 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==42 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa) ||

                (j==43 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passPTll_WWa) ||

                (j==44 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passPTll_WWa && passMetRel_WWa) ||

                (j==45 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passPTll_WWa && passMetRel_WWa && passMll_WWa) ||

                //Now start WWa mu+mu-
                (j==46 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2)) ||

                (j==47 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==48 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa) ||

                (j==49 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passPTll_WWa) ||

                (j==50 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passPTll_WWa && passMetRel_WWa) ||

                (j==51 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passPTll_WWa && passMetRel_WWa && passMll_WWa) ||

                //Now start WWa e+mu-
                (j==52 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1)) ||

                (j==53 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==54 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passPTll_WWa) ||

                (j==55 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passPTll_WWa && passMetRel_WWa) ||

                (j==56 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passPTll_WWa && passMetRel_WWa && passMll_WWa) ||

                //WWb e+ e-
                (j==57 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0)) ||

                (j==58 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==59 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa) ||

                (j==60 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passMT2_WWb) ||

                (j==61 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passMT2_WWb && passMll_WWb) ||

                //WWb mu+ mu-
                (j==62 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2)) ||

                (j==63 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==64 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa) ||

                (j==65 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passMT2_WWb) ||

                (j==66 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passMT2_WWb && passMll_WWb) ||

                //WWb e+mu-

                (j==67 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1)) ||

                (j==68 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==69 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passMT2_WWb) ||

                (j==70 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passMT2_WWb && passMll_WWb) ||

                //WWc e+ e-
                (j==71 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0)) ||

                (j==72 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==73 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa) ||

                (j==74 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==2 && numMuons==0) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passMT2_WWc) ||

                //WWc mu+ mu-
                (j==75 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2)) ||

                (j==76 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==77 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa) ||

                (j==78 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==0 && numMuons==2) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passZVeto_WWa && passMT2_WWc) ||

                //WWc e+mu-

                (j==79 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1)) ||

                (j==80 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0) ||

                (j==81 && tauVeto && leptonPTCut && mllCut && isOS && (numElectrons==1 && numMuons==1) && numCentralNonBJets==0 && numCentralBJets==0 && numForwardJets==0 && passMT2_WWc)

                )cutFlowVector[j]=cutFlowVector[j]+cutFlowIncrements[j];

          }
          return;
        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
          const Analysis_ATLAS_8TeV_2LEPEW_20invfb* specificOther
                  = dynamic_cast<const Analysis_ATLAS_8TeV_2LEPEW_20invfb*>(other);

          for (int j=0; j<NCUTS; j++)
          {
            cutFlowVector[j] += specificOther->cutFlowVector[j];
            cutFlowIncrements[j] += specificOther->cutFlowIncrements[j];
            cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
          }

          _num_MT2_90_SF += specificOther->_num_MT2_90_SF;
          _num_MT2_90_DF += specificOther->_num_MT2_90_DF;
          _num_MT2_120_SF += specificOther->_num_MT2_120_SF;
          _num_MT2_120_DF += specificOther->_num_MT2_120_DF;
          _num_MT2_150_SF += specificOther->_num_MT2_150_SF;
          _num_MT2_150_DF += specificOther->_num_MT2_150_DF;
          _num_WWa_SF += specificOther->_num_WWa_SF;
          _num_WWa_DF += specificOther->_num_WWa_DF;
          _num_WWb_SF += specificOther->_num_WWb_SF;
          _num_WWb_DF += specificOther->_num_WWb_DF;
          _num_WWc_SF += specificOther->_num_WWc_SF;
          _num_WWc_DF += specificOther->_num_WWc_DF;
          _num_Zjets += specificOther->_num_Zjets;
        }


        void collect_results()
        {

          #ifdef CUTFLOW
            double scale_by=1.;
            cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
            cout << "CUT FLOW: ATLAS 8 TeV 2-lepton EW paper SUSY-2013-11"<<endl;
            cout << "------------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<< right << setw(40) << "CUT" <<  "," << setw(20) << "RAW" <<  "," << setw(20) << "SCALED"
            <<  "," << setw(20) << "%" <<  "," << setw(20) << endl;
            for (int j=0; j<NCUTS; j++)
            {
                cout << right <<  setw(40) << cutFlowVector_str[j].c_str() <<  "," << setw(20)
                << cutFlowVector[j] <<  "," << setw(20) << cutFlowVector[j]*scale_by <<  "," << setw(20)
                << 100.*cutFlowVector[j]/cutFlowVector[0] << "%" << endl;
            }
            cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
          #endif

          // add_result(SignalRegionData("SR label", n_obs, {n_sig_MC, n_sig_MC_sys}, {n_bkg, n_bkg_err}));

          add_result(SignalRegionData("MT2_90_SF", 33., {_num_MT2_90_SF, 0.}, {38.2, 5.1}));
          add_result(SignalRegionData("MT2_90_DF", 21., {_num_MT2_90_DF, 0.}, {23.3, 3.7}));
          add_result(SignalRegionData("MT2_120_SF", 5., {_num_MT2_120_SF, 0.}, {8.9, 2.1}));
          add_result(SignalRegionData("MT2_120_DF", 5., {_num_MT2_120_DF, 0.}, {3.6, 1.2}));
          add_result(SignalRegionData("MT2_150_SF", 3., {_num_MT2_150_SF, 0.}, {3.2, 0.7}));
          add_result(SignalRegionData("MT2_150_DF", 2., {_num_MT2_150_DF, 0.}, {1.0, 0.5}));
          add_result(SignalRegionData("WWa_SF", 73., {_num_WWa_SF, 0.}, {86.5, 7.4}));
          add_result(SignalRegionData("WWa_DF", 70., {_num_WWa_DF, 0.}, {73.6, 7.9}));
          add_result(SignalRegionData("WWb_SF", 26., {_num_WWb_SF, 0.}, {30.2, 3.5}));
          add_result(SignalRegionData("WWb_DF", 17., {_num_WWb_DF, 0.}, {18.1, 2.6}));
          add_result(SignalRegionData("WWc_SF", 10., {_num_WWc_SF, 0.}, {20.3, 3.5}));
          add_result(SignalRegionData("WWc_DF", 11., {_num_WWc_DF, 0.}, {9.0, 2.2}));
          add_result(SignalRegionData("Zjets", 1., {_num_Zjets, 0.}, {1.4, 0.6}));

  //        plots_mt2_NOmt2_SF->createFile(luminosity(),(34.38103/50000));
  //        plots_mt2_NOmt2_DF->createFile(luminosity(),(34.38103/50000));
  //        plots_Zjets_NOmet_SF->createFile(luminosity(),(310.76/50000));
  //        plots_WWa_NOmll_SF->createFile(luminosity(),(5550.178/50000));
  //        plots_WWa_NOmll_DF->createFile(luminosity(),(5550.178/50000));
  //        plots_WWa_NOmllORmet_SF->createFile(luminosity(),(5550.178/50000));
  //        plots_WWa_NOmllORmet_DF->createFile(luminosity(),(5550.178/50000));

          return;
        }


      protected:
        void analysis_specific_reset()
        {
          _num_MT2_90_SF=0;
          _num_MT2_90_DF=0;
          _num_MT2_120_SF=0;
          _num_MT2_120_DF=0;
          _num_MT2_150_SF=0;
          _num_MT2_150_DF=0;
          _num_WWa_SF=0;
          _num_WWa_DF=0;
          _num_WWb_SF=0;
          _num_WWb_DF=0;
          _num_WWc_SF=0;
          _num_WWc_DF=0;
          _num_Zjets=0;

          std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
        }

    };


    DEFINE_ANALYSIS_FACTORY(ATLAS_8TeV_2LEPEW_20invfb)


  }
}
