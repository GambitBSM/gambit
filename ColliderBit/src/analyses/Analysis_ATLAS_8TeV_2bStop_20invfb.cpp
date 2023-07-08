#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
//#include "gambit/ColliderBit/analyses/Perf_Plot.hpp"

using namespace std;


// The ATLAS 2b stop/bottom analysis (20fb^-1)
//
// based on: arXiv:1308.2631
//
//    Code by Martin White, Sky French.
//    Updated by Kelton Whiteaker, June 2020
//    Known errors:
//    a) The isolation is already applied in the simulation rather than after overlap removal -> the electron and muon veto technically require a veto on base-line electrons/muons not overlapping with jets
//
//    Known features:
//    a) Must run simulator with 60% b tagging efficiency and ?% mis-id rate. Note from Kelton: detailed pT- and eta-dependent efficiencies for 60% operating point not available from public ATLAS results.


namespace Gambit
{
  namespace ColliderBit
  {


    class Analysis_ATLAS_8TeV_2bStop_20invfb : public Analysis
    {
      private:

        // Numbers passing cuts
        double _numSRA, _numSRB;
        double _numSRA15, _numSRA20, _numSRA25, _numSRA30, _numSRA35;

        vector<int> cutFlowVector;
        vector<string> cutFlowVector_str;
        int NCUTS; //=2;

        // Debug histos

  //      Perf_Plot* plots_mct;
  //      Perf_Plot* plots_mbb;
  //      Perf_Plot* plots_met;
  //      Perf_Plot* plots_ht3;
  //      Perf_Plot* plots_allAcuts;
  //      Perf_Plot* plots_allBcuts;


      public:

        // Required detector sim
        static constexpr const char* detector = "ATLAS";

        // constructor
        Analysis_ATLAS_8TeV_2bStop_20invfb()
        {

          set_analysis_name("ATLAS_8TeV_2bStop_20invfb");
          set_luminosity(20.1);

          _numSRA = 0 ; _numSRB = 0; _numSRA15 = 0; _numSRA20 = 0; _numSRA25 = 0; _numSRA30 = 0; _numSRA35 = 0;
          NCUTS=30;

          for(int i=0;i<NCUTS;i++)
          {
            cutFlowVector.push_back(0);
            cutFlowVector_str.push_back("");
          }

  //        vector<const char*> variablesNames = {"met","mct","mbb","ht3"};
  //        plots_mct = new Perf_Plot(analysis_name()+"_SRA_no-mct-cut", &variablesNames);
  //        plots_mbb = new Perf_Plot(analysis_name()+"_SRA_no-mbb-cut", &variablesNames);
  //        plots_met = new Perf_Plot(analysis_name()+"_SRB_no-met-cut", &variablesNames);
  //        plots_ht3 = new Perf_Plot(analysis_name()+"_SRB_no-ht3-cut", &variablesNames);
  //        plots_allAcuts = new Perf_Plot(analysis_name()+"_SRA_all-cuts", &variablesNames);
  //        plots_allBcuts = new Perf_Plot(analysis_name()+"_SRB_all-cuts", &variablesNames);

        }


        void run(const HEPUtils::Event* event)
        {

          // Missing energy
          HEPUtils::P4 ptot = event->missingmom();
          double met = event->met();

          // Now define vector of baseline electrons
          vector<const HEPUtils::Particle*> baselineElectrons;
          for (const HEPUtils::Particle* electron : event->electrons())
          {
            if (electron->pT() > 7. && fabs(electron->eta()) < 2.47) baselineElectrons.push_back(electron);
          }

          // Apply electron efficiency
          ATLAS::applyElectronEff(baselineElectrons);

          // Now define vector of baseline muons
          vector<const HEPUtils::Particle*> baselineMuons;
          for (const HEPUtils::Particle* muon : event->muons())
          {
            if (muon->pT() > 6. && fabs(muon->eta()) < 2.4) baselineMuons.push_back(muon);
          }

          // Apply muon efficiency
          ATLAS::applyMuonEff(baselineMuons);

          const std::vector<double> a = {0,10.};
          const std::vector<double> b = {0,10000.};
          const std::vector<double> c = {0.60};  // b tagging efficiency
  //        const std::vector<double> a = {0,2.1,10.};
  //        const std::vector<double> b = {0,30.,40.,50.,70.,10000.};
  //        const std::vector<double> c = {0.54,0.63,0.67,0.7,0.75,0.35,0.42,0.44,0.46,0.49};  // b tagging efficiency for 70% WP (this analysis is 60%)
          HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);

          vector<const HEPUtils::Jet*> baselineJets;
          vector<const HEPUtils::Jet*> bJets;
          vector<const HEPUtils::Jet*> trueBJets; //for debugging

          for (const HEPUtils::Jet* jet : event->jets())
          {
            if (jet->pT() > 20. && fabs(jet->eta()) < 4.9) baselineJets.push_back(jet);
          }

          // Overlap removal
          vector<const HEPUtils::Particle*> signalElectrons;
          vector<const HEPUtils::Particle*> signalMuons;
          vector<const HEPUtils::Particle*> electronsForVeto;
          vector<const HEPUtils::Particle*> muonsForVeto;
          vector<const HEPUtils::Jet*> goodJets;
          vector<const HEPUtils::Jet*> signalJets;

          // Remove any jet within dR=0.2 of an electrons
          // preprocessing
          for (size_t iJet=0;iJet<baselineJets.size();iJet++)
          {
            bool overlap=false;
            HEPUtils::P4 jetVec=baselineJets.at(iJet)->mom();
            for (size_t iEl=0;iEl<baselineElectrons.size();iEl++)
            {
              HEPUtils::P4 elVec=baselineElectrons.at(iEl)->mom();
              if (fabs(elVec.deltaR_eta(jetVec))<0.2)overlap=true;
            }
            if (!overlap&&fabs(baselineJets.at(iJet)->eta())<2.8)goodJets.push_back(baselineJets.at(iJet));
            if (!overlap&&fabs(baselineJets.at(iJet)->eta())<2.8 && baselineJets.at(iJet)->pT()>20.)signalJets.push_back(baselineJets.at(iJet));
          }

          // Remove electrons with dR=0.4 or surviving jets
          for (size_t iEl=0;iEl<baselineElectrons.size();iEl++)
          {
            bool overlap=false;
            HEPUtils::P4 elVec=baselineElectrons.at(iEl)->mom();
            for (size_t iJet=0;iJet<goodJets.size();iJet++)
            {
              HEPUtils::P4 jetVec=goodJets.at(iJet)->mom();
              if (fabs(elVec.deltaR_eta(jetVec))<0.4)overlap=true;
            }
            if (!overlap && elVec.pT()>25.)signalElectrons.push_back(baselineElectrons.at(iEl));
            if(!overlap)electronsForVeto.push_back(baselineElectrons.at(iEl));
          }

          // Remove muons with dR=0.4 or surviving jets
          for (size_t iMu=0;iMu<baselineMuons.size();iMu++)
          {
            bool overlap=false;

            HEPUtils::P4 muVec=baselineMuons.at(iMu)->mom();

            for (size_t iJet=0;iJet<goodJets.size();iJet++)
            {
              HEPUtils::P4 jetVec=goodJets.at(iJet)->mom();
              if (fabs(muVec.deltaR_eta(jetVec))<0.4)overlap=true;
            }
            if (!overlap && muVec.pT()>25.)signalMuons.push_back(baselineMuons.at(iMu));
            if(!overlap)muonsForVeto.push_back(baselineMuons.at(iMu));
          }

          // for all signal (good) jets, b-tag if mc b hadron present
          // btag() is mc
          for (const HEPUtils::Jet* jet : signalJets)
          {
            bool hasTag=has_tag(_eff2d, fabs(jet->eta()), jet->pT());
            if(jet->btag() && hasTag && fabs(jet->eta()) < 2.5 && jet->pT() > 20.) bJets.push_back(jet);
          }

          // We now have the signal electrons, muons, jets and b jets- move on to the analysis

          // Calculate common variables and cuts first
          int nJets = signalJets.size();

          //Jet cuts for each SR
          bool passSRAJetCut=false;
          bool passSRBJetCut=false;
          bool passSRAbJetCut=false;
          bool passSRBbJetCut=false;

          double mbb=0;
          double mCT=0;

          //cout << "TEST njets " << nJets << " nbjets " << bJets.size() << endl;

          if(nJets>=2)
          {
            if(signalJets[0]->pT() > 130.
               && signalJets[1]->pT() > 50)
            {
              if(nJets==2)
              {
                passSRAJetCut=true;
                if(bJets.size()==2)
                {
                  passSRAbJetCut=true;

                  mbb = (bJets[0]->mom()+bJets[1]->mom()).m();

                  double bjet1_ET = sqrt(bJets[0]->mom().pT()*bJets[0]->mom().pT()+bJets[0]->mom().m()*bJets[0]->mom().m());
                  double bjet2_ET = sqrt(bJets[1]->mom().pT()*bJets[1]->mom().pT()+bJets[1]->mom().m()*bJets[1]->mom().m());

                  double modPTdiff_squared=(bJets[0]->mom().px()-bJets[1]->mom().px())*(bJets[0]->mom().px()-bJets[1]->mom().px())
                    +                      (bJets[0]->mom().py()-bJets[1]->mom().py())*(bJets[0]->mom().py()-bJets[1]->mom().py());

                  double mct_squared = pow(bjet1_ET+bjet2_ET,2)-modPTdiff_squared;
                  mCT = sqrt(mct_squared);
                }
              }
              if(nJets>2)
              {
                if(signalJets[2]->pT() < 50.)
                {
                  passSRAJetCut=true;
                  //Check that the two leading jets are the b jets
                  if(bJets.size()==2 && (signalJets[0]->pT()==bJets[0]->pT()) && (signalJets[1]->pT()==bJets[1]->pT()))
                  {
                    passSRAbJetCut=true;

                    mbb = (bJets[0]->mom()+bJets[1]->mom()).m();
                    double bjet1_ET = sqrt(bJets[0]->mom().pT()*bJets[0]->mom().pT()+bJets[0]->mom().m()*bJets[0]->mom().m());
                    double bjet2_ET = sqrt(bJets[1]->mom().pT()*bJets[1]->mom().pT()+bJets[1]->mom().m()*bJets[1]->mom().m());

                    double modPTdiff_squared=(bJets[0]->mom().px()-bJets[1]->mom().px())*(bJets[0]->mom().px()-bJets[1]->mom().px())
                      +                      (bJets[0]->mom().py()-bJets[1]->mom().py())*(bJets[0]->mom().py()-bJets[1]->mom().py());

                    double mct_squared = pow(bjet1_ET+bjet2_ET,2)-modPTdiff_squared;
                    mCT = sqrt(mct_squared);

                    //double bjet1_ET = sqrt(bjet1.Pt()*bjet1.Pt()+bjet1.M()*bjet1.M());
                    //double bjet2_ET = sqrt(bjet2.Pt()*bjet2.Pt()+bjet2.M()*bjet2.M());
                    //TVector2 bjet1_pT;
                    //TVector2 bjet2_pT;
                    //bjet1_pT.Set(bjet1.Px(),bjet1.Py());
                    //bjet2_pT.Set(bjet2.Px(),bjet2.Py());
                    //double mct_squared = pow(bjet1_ET+bjet2_ET,2)-(bjet1_pT-bjet2_pT).Mod2();
                    //mCT = sqrt(mct_squared);
                  }
                }
              }
            }
          }

          if(nJets>=3)
          {
            if(signalJets[0]->pT() > 150.
               && signalJets[1]->pT() > 30.
               && signalJets[2]->pT() > 30.)
            {
              passSRBJetCut=true;
              //Check that the 2nd and 3rd leading jets are the b jets
              if(bJets.size()==2 && (bJets[0]->pT()==signalJets[1]->pT()) && (bJets[1]->pT()==signalJets[2]->pT()))
              {
                passSRBbJetCut=true;

                mbb = (bJets[0]->mom()+bJets[1]->mom()).m();
                double bjet1_ET = sqrt(bJets[0]->mom().pT()*bJets[0]->mom().pT()+bJets[0]->mom().m()*bJets[0]->mom().m());
                double bjet2_ET = sqrt(bJets[1]->mom().pT()*bJets[1]->mom().pT()+bJets[1]->mom().m()*bJets[1]->mom().m());

                double modPTdiff_squared=(bJets[0]->mom().px()-bJets[1]->mom().px())*(bJets[0]->mom().px()-bJets[1]->mom().px())
                  +                      (bJets[0]->mom().py()-bJets[1]->mom().py())*(bJets[0]->mom().py()-bJets[1]->mom().py());

                double mct_squared = pow(bjet1_ET+bjet2_ET,2)-modPTdiff_squared;
                mCT = sqrt(mct_squared);


                //mbb = (bjet1+bjet2).M();
                //double bjet1_ET = sqrt(bjet1.Pt()*bjet1.Pt()+bjet1.M()*bjet1.M());
                //double bjet2_ET = sqrt(bjet2.Pt()*bjet2.Pt()+bjet2.M()*bjet2.M());
                //TVector2 bjet1_pT;
                //TVector2 bjet2_pT;
                //bjet1_pT.Set(bjet1.Px(),bjet1.Py());
                //bjet2_pT.Set(bjet2.Px(),bjet2.Py());
                //double mct_squared = pow(bjet1_ET+bjet2_ET,2)-(bjet1_pT-bjet2_pT).Mod2();
                //mCT = sqrt(mct_squared);

              }
            }

          }

          //Calculate dphi(jet,met) for the three leading jets
          double dphi_jetmet1=9999;
          if(nJets>0)dphi_jetmet1=std::acos(std::cos(signalJets.at(0)->phi()-ptot.phi()));
          double dphi_jetmet2=9999;
          if(nJets>1)dphi_jetmet2=std::acos(std::cos(signalJets.at(1)->phi()-ptot.phi()));
          double dphi_jetmet3=9999;
          if(nJets>2)dphi_jetmet3=std::acos(std::cos(signalJets.at(2)->phi()-ptot.phi()));

          double dphi_min = min(dphi_jetmet1,dphi_jetmet2);
          dphi_min = min(dphi_min,dphi_jetmet3);

          //Calculate meff (all jets with pT>20 GeV, and met)
          //double meff = met; (Unused)
          //for (const HEPUtils::Jet* jet : signalJets) { (Unused)
          //  if(jet->pT()>20.)meff += jet->pT(); (Unused)
          //} (Unused)
          double meff2 = met; double meff3 = met; int nummeff=0;
          for (const HEPUtils::Jet* jet : signalJets)
          {
            nummeff++;
            if(nummeff<=2 && jet->pT()>20.)meff2 += jet->pT();
            if(nummeff<=3 && jet->pT()>20.)meff3 += jet->pT();
          }


          //Calculate HT,3 (all jets except 3 highest pT)
          double ht3 = 0; int num=0;
          for (const HEPUtils::Jet* jet : signalJets)
          {
            num++;
            if(num>3 && jet->pT()>20.)ht3 += jet->pT();
          }


          //Cutflow flags
          bool cut_ElectronVeto=false;
          bool cut_MuonVeto=false;
          //bool cut_2jets=false;
          //bool cut_3jets=false;
          bool cut_dPhiJet1=false;
          bool cut_METGt150=false;
          bool cut_METGt250=false;
          bool cut_dPhiJets=false;
          bool cut_METmeff2=false;
          bool cut_METmeff3=false;

          if(electronsForVeto.size()==0)cut_ElectronVeto=true;
          if(muonsForVeto.size()==0)cut_MuonVeto=true;
          //if(passSRAJetCut)cut_2jets=true;
          //if(passSRBJetCut)cut_3jets=true;
          if(dphi_jetmet1>2.5)cut_dPhiJet1=true;
          if(dphi_min>0.4)cut_dPhiJets=true;
          if(met>150.)cut_METGt150=true;
          if(met>250.)cut_METGt250=true;
          if(met/meff2>0.25)cut_METmeff2=true;
          if(met/meff3>0.25)cut_METmeff3=true;


  //        vector<double> variables={met, mCT, mbb, ht3};
  //        if(met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2 && mbb > 200.)plots_mct->fill(&variables);
  //        if(met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2 && mCT > 150.)plots_mbb->fill(&variables);
  //        if(met>80. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut && cut_dPhiJet1 && passSRBbJetCut && cut_dPhiJets && cut_METmeff3 && ht3<50.)plots_met->fill(&variables);
  //        if(met>250. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut && cut_dPhiJet1 && passSRBbJetCut && cut_dPhiJets && cut_METmeff3)plots_ht3->fill(&variables);
  //        if(met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2 && mbb > 200. && mCT > 150.)plots_allAcuts->fill(&variables);
  //        if(met>250. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut && cut_dPhiJet1 && passSRBbJetCut && cut_dPhiJets && cut_METmeff3 && ht3<50.)plots_allBcuts->fill(&variables);


          cutFlowVector_str[0] = "No cuts ";
          cutFlowVector_str[1] = "MET > 80 ";
          cutFlowVector_str[2] = "SRA: Lepton veto ";
          cutFlowVector_str[3] = "SRA: MET > 150 ";
          cutFlowVector_str[4] = "SRA: Jet selection  ";
          cutFlowVector_str[5] = "SRA: B jet selection  ";
          cutFlowVector_str[6] = "SRA: dPhi_min > 0.4 ";
          cutFlowVector_str[7] = "SRA: MET/meff(2) > 0.25 ";
          cutFlowVector_str[8] = "SRA: mbb > 200 ";
          cutFlowVector_str[9] = "SRA: mCT > 150 ";
          cutFlowVector_str[10] = "SRA: mCT > 200 ";
          cutFlowVector_str[11] = "SRA: mCT > 250 ";
          cutFlowVector_str[12] = "SRA: mCT > 300 ";
          cutFlowVector_str[13] = "SRB: lepton veto ";
          cutFlowVector_str[14] = "SRB: MET > 250 ";
          cutFlowVector_str[15] = "SRB: Jet selection ";
          cutFlowVector_str[16] = "SRB: dPhi(pTmiss,j1) > 2.5 ";
          cutFlowVector_str[17] = "SRB: B jet selection ";
          cutFlowVector_str[18] = "SRB: dPhi_min > 0.4 ";
          cutFlowVector_str[19] = "SRB: MET/meff(3) > 0.25 ";
          cutFlowVector_str[20] = "SRB: HT3 < 50  ";


          for(int j=0;j<NCUTS;j++)
          {
            if(
               (j==0) ||

               (j==1 && met>80.) ||

               (j==2 && met>80. && cut_MuonVeto && cut_ElectronVeto) ||

               (j==3 && met>150. && cut_MuonVeto && cut_ElectronVeto) ||

               (j==4 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut) ||

               (j==5 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut) ||

               (j==6 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut && cut_dPhiJets) ||

               (j==7 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2) ||

               (j==8 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2 && mbb > 200.) ||

               (j==9 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2 && mbb > 200. && mCT > 150.) ||

               (j==10 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2 && mbb > 200. && mCT > 200.) ||

               (j==11 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2 && mbb > 200. && mCT > 250.) ||

               (j==12 && met>150. && cut_MuonVeto && cut_ElectronVeto && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2 && mbb > 200. && mCT > 300.) ||

               (j==13 && met>80. && cut_MuonVeto && cut_ElectronVeto) ||

               (j==14 && met>250. && cut_MuonVeto && cut_ElectronVeto) ||

               (j==15 && met>250. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut) ||

               (j==16 && met>250. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut && cut_dPhiJet1) ||

               (j==17 && met>250. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut && cut_dPhiJet1 && passSRBbJetCut) ||

               (j==18 && met>250. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut && cut_dPhiJet1 && passSRBbJetCut && cut_dPhiJets) ||

               (j==19 && met>250. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut && cut_dPhiJet1 && passSRBbJetCut && cut_dPhiJets && cut_METmeff3) ||

               (j==20 && met>250. && cut_MuonVeto && cut_ElectronVeto && passSRBJetCut && cut_dPhiJet1 && passSRBbJetCut && cut_dPhiJets && cut_METmeff3 && ht3<50.)

               )cutFlowVector[j]++;
          }

          //We're now ready to apply the cuts for each signal region
          //_numSRA, _numSRB, _numSRA15, _numSRA20, _numSRA25, _numSRA30, _numSRA35;

          if(cut_ElectronVeto && cut_MuonVeto && cut_METGt150 && passSRAJetCut && passSRAbJetCut && cut_dPhiJets && cut_METmeff2 && mbb>200.)
          {
            _numSRA += event->weight();
            if(mCT>150.) _numSRA15 += event->weight();
            if(mCT>200.) _numSRA20 += event->weight();
            if(mCT>250.) _numSRA25 += event->weight();
            if(mCT>300.) _numSRA30 += event->weight();
            if(mCT>350.) _numSRA35 += event->weight();
          }
          if(cut_ElectronVeto && cut_MuonVeto && cut_METGt250 && passSRBJetCut && cut_dPhiJet1 && passSRBbJetCut && cut_dPhiJets && cut_METmeff3 && ht3<50.) _numSRB += event->weight();


          return;

        }

        /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
        void combine(const Analysis* other)
        {
          const Analysis_ATLAS_8TeV_2bStop_20invfb* specificOther
                  = dynamic_cast<const Analysis_ATLAS_8TeV_2bStop_20invfb*>(other);

          if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
          for (int j=0; j<NCUTS; j++)
          {
            cutFlowVector[j] += specificOther->cutFlowVector[j];
            cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
          }
          _numSRA += specificOther->_numSRA;
          _numSRB += specificOther->_numSRB;
          _numSRA15 += specificOther->_numSRA15;
          _numSRA20 += specificOther->_numSRA20;
          _numSRA25 += specificOther->_numSRA25;
          _numSRA30 += specificOther->_numSRA30;
          _numSRA35 += specificOther->_numSRA35;
        }


        void collect_results()
        {

          double scale_by=1.;
          cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
          cout << "CUT FLOW: ATLAS 8 TeV 2b stop paper SUSY-2013-05"<<endl;
          cout << "------------------------------------------------------------------------------------------------------------------------------"<<endl;
          cout<< right << setw(40) << "CUT" <<  "," << setw(20) << "RAW" <<  "," << setw(20) << "SCALED"
          <<  "," << setw(20) << "%" <<  "," << setw(20) << endl;
          for (int j=0; j<NCUTS; j++) {
              cout << right <<  setw(40) << cutFlowVector_str[j].c_str() <<  "," << setw(20)
              << cutFlowVector[j] <<  "," << setw(20) << cutFlowVector[j]*scale_by <<  "," << setw(20)
              << 100.*cutFlowVector[j]/cutFlowVector[0] << "%" << endl;
          }
          cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;

          // add_result(SignalRegionData("SR label", n_obs, {n_sig_MC, n_sig_MC_sys}, {n_bkg, n_bkg_err}));

          add_result(SignalRegionData("SRA15", 102., {_numSRA15, 0.}, { 94., 13.}));
          add_result(SignalRegionData("SRA20", 48., {_numSRA20, 0.}, { 39., 6.}));
          add_result(SignalRegionData("SRA25", 14., {_numSRA25, 0.}, { 15.8, 2.8}));
          add_result(SignalRegionData("SRA30", 7., {_numSRA30, 0.}, { 5.9, 1.1}));
          add_result(SignalRegionData("SRA35", 3., {_numSRA35, 0.}, { 2.5, 0.6}));
          add_result(SignalRegionData("SRB", 65., {_numSRB, 0.}, { 64., 10.}));

  //        plots_mct->createFile(luminosity(),(85.5847/50000));
  //        plots_mbb->createFile(luminosity(),(85.5847/50000));
  //        plots_met->createFile(luminosity(),(85.5847/50000));
  //        plots_ht3->createFile(luminosity(),(85.5847/50000));
  //        plots_allAcuts->createFile(luminosity(),(85.5847/50000));
  //        plots_allBcuts->createFile(luminosity(),(85.5847/50000));

          return;
        }


      protected:
        void analysis_specific_reset()
        {
          _numSRA = 0 ; _numSRB = 0; _numSRA15 = 0; _numSRA20 = 0; _numSRA25 = 0; _numSRA30 = 0; _numSRA35 = 0;

          std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
        }

    };


    DEFINE_ANALYSIS_FACTORY(ATLAS_8TeV_2bStop_20invfb)


  }
}
