
#include "gambit/cmake/cmake_variables.hpp"
#ifndef EXCLUDE_ROOT
#ifndef EXCLUDE_RESTFRAMES

#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

#include "RestFrames/RestFrames.hh"
#include "TLorentzVector.h"

using namespace std;

/* The ATLAS 13 TeV 3 lepton low mass recursive jigsaw search

   Based on code kindly supplied by Abhishek Sharma

   Note that use of ROOT is compulsory for the RestFrames package

   Based on: https://arxiv.org/pdf/1806.02293.pdf

   Code adapted by Martin White

   KNOWN ISSUES

   1) Need to check overlap removal step when the paper comes out. For now, have assumed it is the same as the stop analysis.

*/

namespace Gambit {
  namespace ColliderBit {

    bool sortByPT_RJ3L(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->pT() > jet2->pT()); }
    bool sortLepByPT_RJ3L(const HEPUtils::Particle* lep1, const HEPUtils::Particle* lep2) { return (lep1->pT() > lep2->pT());}
    //bool sortByMass(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2) { return (jet1->mass() > jet2->mass()); }

    bool SortLeptons(const pair<TLorentzVector,int> lv1, const pair<TLorentzVector,int> lv2)
    //bool VariableConstruction::SortLeptons(const lep lv1, const lep lv2)
    {
      return lv1.first.Pt() > lv2.first.Pt();
    }

    bool SortJets(const TLorentzVector jv1, const TLorentzVector jv2)
    {
      return jv1.Pt() > jv2.Pt();
    }


    class Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb : public Analysis {

    protected:
      // Numbers passing cuts
      std::map<string, EventCounter> _counters = {
        {"2L2JHIGH", EventCounter("2L2JHIGH")},
        {"2L2JINT", EventCounter("2L2JINT")},
        {"2L2JLOW", EventCounter("2L2JLOW")},
        {"2L2JCOMP", EventCounter("2L2JCOMP")},
        {"3LHIGH", EventCounter("3LHIGH")},
        {"3LINT", EventCounter("3LINT")},
        {"3LLOW", EventCounter("3LLOW")},
        {"3LCOMP", EventCounter("3LCOMP")},
      };

    private:

      vector<int> cutFlowVector;
      vector<string> cutFlowVector_str;
      int NCUTS; //=16;

      // Recursive jigsaw objects (using RestFrames)

      ///////////////////////////////////////////////////////////////////////
      /// 1. Create RJigsaw for C1N2 -> WZN1N1 -> 2L+2J+MET High mass region
      ///////////////////////////////////////////////////////////////////////

      unique_ptr<RestFrames::LabRecoFrame>       LAB_2L2J;
      unique_ptr<RestFrames::DecayRecoFrame>     C1N2_2L2J;
      unique_ptr<RestFrames::DecayRecoFrame>     C1a_2L2J;
      unique_ptr<RestFrames::DecayRecoFrame>     N2b_2L2J;

      unique_ptr<RestFrames::DecayRecoFrame>     Wa_2L2J;
      unique_ptr<RestFrames::DecayRecoFrame>     Zb_2L2J;

      unique_ptr<RestFrames::VisibleRecoFrame>   J1_2L2J;
      unique_ptr<RestFrames::VisibleRecoFrame>   J2_2L2J;
      unique_ptr<RestFrames::VisibleRecoFrame>   L1_2L2J;
      unique_ptr<RestFrames::VisibleRecoFrame>   L2_2L2J;

      unique_ptr<RestFrames::InvisibleRecoFrame> X1a_2L2J;
      unique_ptr<RestFrames::InvisibleRecoFrame> X1b_2L2J;

      unique_ptr<RestFrames::InvisibleGroup>    INV_2L2J;

      unique_ptr<RestFrames::SetMassInvJigsaw>     X1_mass_2L2J;
      unique_ptr<RestFrames::SetRapidityInvJigsaw> X1_eta_2L2J;

      unique_ptr<RestFrames::ContraBoostInvJigsaw> X1X1_contra_2L2J;

      ///////////////////////////////////////////////////////////////////////
      /// 2. Create RJigsaw for C1N2 -> WZN1N1 -> 3L + MET High mass region
      ///////////////////////////////////////////////////////////////////////

      unique_ptr<RestFrames::LabRecoFrame>       LAB_3L;
      unique_ptr<RestFrames::DecayRecoFrame>     C1N2_3L;
      unique_ptr<RestFrames::DecayRecoFrame>     C1a_3L;
      unique_ptr<RestFrames::DecayRecoFrame>     N2b_3L;

      // unique_ptr<RestFrames::DecayRecoFrame>     Wa_3L;
      // unique_ptr<RestFrames::DecayRecoFrame>     Zb_3L;

      unique_ptr<RestFrames::VisibleRecoFrame>   L1a_3L;
      unique_ptr<RestFrames::VisibleRecoFrame>   L1b_3L;
      unique_ptr<RestFrames::VisibleRecoFrame>   L2b_3L;

      unique_ptr<RestFrames::InvisibleRecoFrame> X1a_3L;
      unique_ptr<RestFrames::InvisibleRecoFrame> X1b_3L;

      unique_ptr<RestFrames::InvisibleGroup>    INV_3L;

      unique_ptr<RestFrames::SetMassInvJigsaw>     X1_mass_3L;
      unique_ptr<RestFrames::SetRapidityInvJigsaw> X1_eta_3L;

      unique_ptr<RestFrames::ContraBoostInvJigsaw> X1X1_contra_3L;

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

      // 2L+1L tree (Z->ll + Z/W->l)
      unique_ptr<RestFrames::LabRecoFrame>        LAB_2L1L;
      unique_ptr<RestFrames::DecayRecoFrame>      CM_2L1L;
      unique_ptr<RestFrames::DecayRecoFrame>      S_2L1L;
      unique_ptr<RestFrames::VisibleRecoFrame>    ISR_2L1L;

      unique_ptr<RestFrames::DecayRecoFrame>      Ca_2L1L;
      unique_ptr<RestFrames::DecayRecoFrame>      Z_2L1L;
      unique_ptr<RestFrames::VisibleRecoFrame>    L1_2L1L;
      unique_ptr<RestFrames::VisibleRecoFrame>    L2_2L1L;

      unique_ptr<RestFrames::DecayRecoFrame>      Cb_2L1L;
      unique_ptr<RestFrames::VisibleRecoFrame>    Lb_2L1L;

      unique_ptr<RestFrames::InvisibleRecoFrame>  Ia_2L1L;
      unique_ptr<RestFrames::InvisibleRecoFrame>  Ib_2L1L;

      unique_ptr<RestFrames::InvisibleGroup>       INV_2L1L;
      unique_ptr<RestFrames::SetMassInvJigsaw>     InvMass_2L1L;
      unique_ptr<RestFrames::SetRapidityInvJigsaw> InvRapidity_2L1L;
      unique_ptr<RestFrames::ContraBoostInvJigsaw> SplitINV_2L1L;

      // Debug histos

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

      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec, double DeltaRMax) {
        //Routine to do lepton-jet check
        //Discards leptons if they are within DeltaRMax of a jet

        vector<const HEPUtils::Particle*> Survivors;

        for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
          bool overlap = false;
          HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
          for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
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


    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb() {

        set_analysis_name("ATLAS_13TeV_RJ3L_lowmass_36invfb");
        set_luminosity(36.);

        NCUTS=70;

        for(int i=0;i<NCUTS;i++){
          cutFlowVector.push_back(0);
          cutFlowVector_str.push_back("");
        }


        // Recursive jigsaw stuff
        #pragma omp critical (init_ATLAS_13TeV_RJ3L_lowmass_36invfb)
        {

          // // DEBUG:
          // RestFrames::SetLogPrint(RestFrames::LogDebug, true);
          // RestFrames::SetLogPrint(RestFrames::LogVerbose, true);

          LAB_2L2J.reset(new RestFrames::LabRecoFrame("LAB_2L2J","lab2L2J"));
          C1N2_2L2J.reset(new RestFrames::DecayRecoFrame("C1N2_2L2J","#tilde{#chi}^{ #pm}_{1} #tilde{#chi}^{ 0}_{2}"));
          C1a_2L2J.reset(new RestFrames::DecayRecoFrame("C1a_2L2J","#tilde{#chi}^{ #pm}_{1}"));
          N2b_2L2J.reset(new RestFrames::DecayRecoFrame("N2b_2L2J","#tilde{#chi}^{ 0}_{2}"));

          Wa_2L2J.reset(new RestFrames::DecayRecoFrame("Wa_2L2J","W_{a}"));
          Zb_2L2J.reset(new RestFrames::DecayRecoFrame("Zb_2L2J","Z_{b}"));

          J1_2L2J.reset(new RestFrames::VisibleRecoFrame("J1_2L2J","#it{j}_{1}"));
          J2_2L2J.reset(new RestFrames::VisibleRecoFrame("J2_2L2J","#it{j}_{2}"));
          L1_2L2J.reset(new RestFrames::VisibleRecoFrame("L1_2L2J","#it{l}_{1}"));
          L2_2L2J.reset(new RestFrames::VisibleRecoFrame("L2_2L2J","#it{l}_{2}"));

          X1a_2L2J.reset(new RestFrames::InvisibleRecoFrame("X1a_2L2J","#tilde{#chi}^{ 0}_{1 a}"));
          X1b_2L2J.reset(new RestFrames::InvisibleRecoFrame("X1b_2L2J","#tilde{#chi}^{ 0}_{1 b}"));

          LAB_2L2J->SetChildFrame(*C1N2_2L2J);

          C1N2_2L2J->AddChildFrame(*C1a_2L2J);
          C1N2_2L2J->AddChildFrame(*N2b_2L2J);

          C1a_2L2J->AddChildFrame(*Wa_2L2J);
          C1a_2L2J->AddChildFrame(*X1a_2L2J);

          N2b_2L2J->AddChildFrame(*Zb_2L2J);
          N2b_2L2J->AddChildFrame(*X1b_2L2J);

          Wa_2L2J->AddChildFrame(*J1_2L2J);
          Wa_2L2J->AddChildFrame(*J2_2L2J);

          Zb_2L2J->AddChildFrame(*L1_2L2J);
          Zb_2L2J->AddChildFrame(*L2_2L2J);


          if(!LAB_2L2J->InitializeTree())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_2L2J->InitializeTree() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }


          //////////////////////////////
          //Setting the invisible
          //////////////////////////////
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
          X1X1_contra_2L2J->AddInvisibleFrame(*X1a_2L2J, 0);
          X1X1_contra_2L2J->AddInvisibleFrame(*X1b_2L2J, 1);

          if(!LAB_2L2J->InitializeAnalysis())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_2L2J->InitializeAnalysis() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }


          LAB_3L.reset(new RestFrames::LabRecoFrame("LAB_3L","lab"));
          C1N2_3L.reset(new RestFrames::DecayRecoFrame("C1N2_3L","#tilde{#chi}^{ #pm}_{1} #tilde{#chi}^{ 0}_{2}"));
          C1a_3L.reset(new RestFrames::DecayRecoFrame("C1a_3L","#tilde{#chi}^{ #pm}_{1}"));
          N2b_3L.reset(new RestFrames::DecayRecoFrame("N2b_3L","#tilde{#chi}^{ 0}_{2}"));

          L1a_3L.reset(new RestFrames::VisibleRecoFrame("L1a_3L","#it{l}_{1a}"));
          L1b_3L.reset(new RestFrames::VisibleRecoFrame("L1b_3L","#it{l}_{1b}"));
          L2b_3L.reset(new RestFrames::VisibleRecoFrame("L2b_3L","#it{l}_{2b}"));

          X1a_3L.reset(new RestFrames::InvisibleRecoFrame("X1a_3L","#tilde{#chi}^{ 0}_{1 a} + #nu_{a}"));
          X1b_3L.reset(new RestFrames::InvisibleRecoFrame("X1b_3L","#tilde{#chi}^{ 0}_{1 b}"));


          LAB_3L->SetChildFrame(*C1N2_3L);

          C1N2_3L->AddChildFrame(*C1a_3L);
          C1N2_3L->AddChildFrame(*N2b_3L);

          C1a_3L->AddChildFrame(*L1a_3L);
          C1a_3L->AddChildFrame(*X1a_3L);

          N2b_3L->AddChildFrame(*L1b_3L);
          N2b_3L->AddChildFrame(*L2b_3L);
          N2b_3L->AddChildFrame(*X1b_3L);


          if(!LAB_3L->InitializeTree())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_3L->InitializeTree() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }


          //setting the invisible components
          INV_3L.reset(new RestFrames::InvisibleGroup("INV_3L","Invisible system LSP mass Jigsaw"));
          INV_3L->AddFrame(*X1a_3L);
          INV_3L->AddFrame(*X1b_3L);


          // Set di-LSP mass to minimum Lorentz-invariant expression
          X1_mass_3L.reset(new RestFrames::SetMassInvJigsaw("X1_mass_3L", "Set M_{#tilde{#chi}_{1}^{ 0} #tilde{#chi}_{1}^{ 0}} to minimum"));
          INV_3L->AddJigsaw(*X1_mass_3L);

          // Set di-LSP rapidity to that of visible particles and neutrino
          X1_eta_3L.reset(new RestFrames::SetRapidityInvJigsaw("X1_eta_3L", "#eta_{#tilde{#chi}_{1}^{ 0} #tilde{#chi}_{1}^{ 0}} = #eta_{3#it{l}}"));
          INV_3L->AddJigsaw(*X1_eta_3L);
          X1_eta_3L->AddVisibleFrames(C1N2_3L->GetListVisibleFrames());


          X1X1_contra_3L.reset(new RestFrames::ContraBoostInvJigsaw("X1X1_contra_3L","Contraboost invariant Jigsaw"));
          INV_3L->AddJigsaw(*X1X1_contra_3L);
          X1X1_contra_3L->AddVisibleFrames(C1a_3L->GetListVisibleFrames(),0);
          X1X1_contra_3L->AddVisibleFrames(N2b_3L->GetListVisibleFrames(),1);
          X1X1_contra_3L->AddInvisibleFrames(C1a_3L->GetListInvisibleFrames(),0);
          X1X1_contra_3L->AddInvisibleFrames(N2b_3L->GetListInvisibleFrames(),1);

          if(!LAB_3L->InitializeAnalysis())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_3L->InitializeAnalysis() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }


          /////////////////////////// INTERMEDIATE ///////////////////////////////////
          // RestFrames stuff

          // combinatoric (transverse) tree
          // for jet assignment
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
            errmsg  = "Some problem occurred when calling LAB_comb->InitializeTree() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }

          // 2L+NJ tree (Z->ll + W/Z->qq)
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
            errmsg  = "Some problem occurred when calling LAB_2LNJ->InitializeTree() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }


          // 2L+1L tree (Z->ll + Z/W->l)
          LAB_2L1L.reset(new RestFrames::LabRecoFrame("LAB_2L1L","LAB"));
          CM_2L1L.reset(new RestFrames::DecayRecoFrame("CM_2L1L","CM"));
          S_2L1L.reset(new RestFrames::DecayRecoFrame("S_2L1L","S"));
          ISR_2L1L.reset(new RestFrames::VisibleRecoFrame("ISR_2L1L","ISR"));
          Ca_2L1L.reset(new RestFrames::DecayRecoFrame("Ca_2L1L","C_{a}"));
          Z_2L1L.reset(new RestFrames::DecayRecoFrame("Z_2L1L","Z"));
          L1_2L1L.reset(new RestFrames::VisibleRecoFrame("L1_2L1L","#it{l}_{1}"));
          L2_2L1L.reset(new RestFrames::VisibleRecoFrame("L2_2L1L","#it{l}_{2}"));
          Cb_2L1L.reset(new RestFrames::DecayRecoFrame("Cb_2L1L","C_{b}"));
          Lb_2L1L.reset(new RestFrames::VisibleRecoFrame("Lb_2L1L","#it{l}_{b}"));
          Ia_2L1L.reset(new RestFrames::InvisibleRecoFrame("Ia_2L1L","I_{a}"));
          Ib_2L1L.reset(new RestFrames::InvisibleRecoFrame("Ia_2L1L","I_{b}"));

          LAB_2L1L->SetChildFrame(*CM_2L1L);
          CM_2L1L->AddChildFrame(*ISR_2L1L);
          CM_2L1L->AddChildFrame(*S_2L1L);
          S_2L1L->AddChildFrame(*Ca_2L1L);
          S_2L1L->AddChildFrame(*Cb_2L1L);
          Ca_2L1L->AddChildFrame(*Z_2L1L);
          Ca_2L1L->AddChildFrame(*Ia_2L1L);
          Z_2L1L->AddChildFrame(*L1_2L1L);
          Z_2L1L->AddChildFrame(*L2_2L1L);
          Cb_2L1L->AddChildFrame(*Lb_2L1L);
          Cb_2L1L->AddChildFrame(*Ib_2L1L);

          if(!LAB_2L1L->InitializeTree())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_2L1L->InitializeTree() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
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
          JETS_comb->SetNElementsForFrame(*ISR_comb, 1);
          JETS_comb->AddFrame(*J_comb);
          JETS_comb->SetNElementsForFrame(*J_comb, 0);

          SplitJETS_comb.reset(new RestFrames::MinMassesCombJigsaw("SplitJETS_comb", "Minimize M_{ISR} and M_{S} Jigsaw"));
          JETS_comb->AddJigsaw(*SplitJETS_comb);
          SplitJETS_comb->AddCombFrame(*ISR_comb, 0);
          SplitJETS_comb->AddCombFrame(*J_comb, 1);
          SplitJETS_comb->AddObjectFrame(*ISR_comb,0);
          SplitJETS_comb->AddObjectFrame(*S_comb,1);

          if(!LAB_comb->InitializeAnalysis())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_comb->InitializeAnalysis() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
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

          // 2L+1L tree (Z->ll + Z/W->l)
          INV_2L1L.reset(new RestFrames::InvisibleGroup("INV_2L1L","Invisible System"));
          INV_2L1L->AddFrame(*Ia_2L1L);
          INV_2L1L->AddFrame(*Ib_2L1L);

          InvMass_2L1L.reset(new RestFrames::SetMassInvJigsaw("InvMass_2L1L", "Invisible system mass Jigsaw"));
          INV_2L1L->AddJigsaw(*InvMass_2L1L);
          InvRapidity_2L1L.reset(new RestFrames::SetRapidityInvJigsaw("InvRapidity_2L1L", "Set inv. system rapidity"));
          INV_2L1L->AddJigsaw(*InvRapidity_2L1L);
          InvRapidity_2L1L->AddVisibleFrames(S_2L1L->GetListVisibleFrames());
          SplitINV_2L1L.reset(new RestFrames::ContraBoostInvJigsaw("SplitINV_2L1L", "INV -> I_{a}+ I_{b} jigsaw"));
          INV_2L1L->AddJigsaw(*SplitINV_2L1L);
          SplitINV_2L1L->AddVisibleFrames(Ca_2L1L->GetListVisibleFrames(), 0);
          SplitINV_2L1L->AddVisibleFrames(Cb_2L1L->GetListVisibleFrames(), 1);
          SplitINV_2L1L->AddInvisibleFrame(*Ia_2L1L, 0);
          SplitINV_2L1L->AddInvisibleFrame(*Ib_2L1L, 1);

          if(!LAB_2L1L->InitializeAnalysis())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_2L1L->InitializeAnalysis() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
            piped_errors.request(LOCAL_INFO, errmsg);
          }

        }
      }


      void run(const HEPUtils::Event* event) {

        // Clear
        LAB_2L2J->ClearEvent();
        LAB_comb->ClearEvent();
        LAB_2LNJ->ClearEvent();
        LAB_2L1L->ClearEvent();
        LAB_3L->ClearEvent();

        // Missing energy
        HEPUtils::P4 ptot = event->missingmom();
        TVector3 ETMiss;
        ETMiss.SetXYZ(ptot.px(),ptot.py(),0.0);

        // Baseline lepton objects
        vector<const HEPUtils::Particle*> baselineElectrons, baselineMuons, baselineTaus;

        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && electron->abseta() < 2.47) baselineElectrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(baselineElectrons);

        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && muon->abseta() < 2.4) baselineMuons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(baselineMuons);

        // Photons
        vector<const HEPUtils::Particle*> signalPhotons;
        for (const HEPUtils::Particle* photon : event->photons()) {
          signalPhotons.push_back(photon);
        }


        // No taus used in 13 TeV analysis?
        //for (const HEPUtils::Particle* tau : event->taus()) {
          //if (tau->pT() > 10. && tau->abseta() < 2.47) baselineTaus.push_back(tau);
        //}
        //ATLAS::applyTauEfficiencyR1(baselineTaus);


        // Jets
        vector<const HEPUtils::Jet*> bJets;
        vector<const HEPUtils::Jet*> nonBJets;

        // Get b jets
        /// @note We assume that b jets have previously been 100% tagged
        const std::vector<double>  a = {0,10.};
        const std::vector<double>  b = {0,10000.};
        const std::vector<double> c = {0.77}; // set b-tag efficiency to 77%
        HEPUtils::BinnedFn2D<double> _eff2d(a,b,c);
        for (const HEPUtils::Jet* jet : event->jets()) {
          bool hasTag=has_tag(_eff2d, jet->abseta(), jet->pT());
          if (jet->pT() > 20. && fabs(jet->eta()) < 2.4) {
            if(jet->btag() && hasTag){
              bJets.push_back(jet);
            } else {
              nonBJets.push_back(jet);
            }
          }
        }

        // Overlap removal is the same as the 8 TeV analysis
        JetLeptonOverlapRemoval(nonBJets,baselineElectrons,0.2);
        LeptonJetOverlapRemoval(baselineElectrons,nonBJets,0.4);
        LeptonJetOverlapRemoval(baselineElectrons,bJets,0.4);
        LeptonJetOverlapRemoval(baselineMuons,nonBJets,0.4);
        LeptonJetOverlapRemoval(baselineMuons,bJets,0.4);

        // Fill a jet-pointer-to-bool map to make it easy to check
        // if a given jet is treated as a b-jet in this analysis
        map<const HEPUtils::Jet*,bool> analysisBtags;
        for (const HEPUtils::Jet* jet : bJets) {
          analysisBtags[jet] = true;
        }
        for (const HEPUtils::Jet* jet : nonBJets) {
          analysisBtags[jet] = false;
        }

        // Signal object containers
        vector<const HEPUtils::Particle*> signalElectrons;
        vector<const HEPUtils::Particle*> signalMuons;
        vector<const HEPUtils::Particle*> signalLeptons;
        vector<const HEPUtils::Particle*> electronsForVeto;
        vector<const HEPUtils::Particle*> muonsForVeto;

        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBJets;
        vector<const HEPUtils::Jet*> signalNonBJets;

        for (const HEPUtils::Jet* jet : bJets) {
          // pT > 20 and |eta| < 2.4 already required for jets in bJets
          signalJets.push_back(jet);
          signalBJets.push_back(jet);
        }

        for (const HEPUtils::Jet* jet : nonBJets) {
          // pT > 20 and |eta| < 2.4 already required for jets in nonBJets
          signalJets.push_back(jet);
          signalNonBJets.push_back(jet);
        }

        //Put signal jets in pT order
        std::sort(signalJets.begin(), signalJets.end(), sortByPT_RJ3L);
        std::sort(signalBJets.begin(), signalBJets.end(), sortByPT_RJ3L);
        std::sort(signalNonBJets.begin(), signalNonBJets.end(), sortByPT_RJ3L);

        for (const HEPUtils::Particle* electron : baselineElectrons) {
          signalElectrons.push_back(electron);
          signalLeptons.push_back(electron);
        }

        for (const HEPUtils::Particle* muon : baselineMuons) {
          signalMuons.push_back(muon);
          signalLeptons.push_back(muon);
        }

        std::sort(signalLeptons.begin(), signalLeptons.end(), sortLepByPT_RJ3L);

        // We now have the signal electrons, muons, jets and b jets- move on to the analysis
        bool m_is2Lep=false;
        bool m_is2Lep2Jet=false;
        bool m_is2L2JInt=false;

        bool m_is3Lep=false;
        bool m_is3LInt=false;
        // bool m_is3Lep2Jet=false;
        // bool m_is3Lep3Jet=false;

        // bool m_is4Lep=false;
        // bool m_is4Lep2Jet=false;
        // bool m_is4Lep3Jet=false;

        bool m_foundSFOS=false;

        // double m_H2PP_visible = -999.;
        // double m_H2PP_invisible = -999.;
        // double m_IaPP = -999.;
        // double m_IbPP = -999.;
        // double m_IaPa = -999.;
        // double m_IbPb = -999.;
        // double m_IaLAB = -999;
        // double m_IbLAB = -999;
        // double m_H4PP_Lept1A = -999.;
        // double m_H4PP_Lept1B = -999.;
        // double m_H4PP_Lept2B = -999.;
        // double m_mu = -999;
        // double m_pileUp_weight = -999;


        //////Initialize variables
        // int m_nBaselineLeptons = -999;
        // int m_nSignalLeptons   = -999;

        double m_lept1Pt  = -999;
        // double m_lept1Eta = -999;
        // double m_lept1Phi =-999;
        double m_lept1sign=-999;
        // double m_lept1origin = -999;
        // double m_lept1type = -999;

        double m_lept2Pt =-999;
        // double m_lept2Eta=-999;
        // double m_lept2Phi =-999;
        double m_lept2sign =-999;
        // double m_lept2origin = -999;
        // double m_lept2type = -999;

        double m_lept3Pt =-999;
        // double m_lept3Eta =-999;
        // double m_lept3Phi =-999;
        double m_lept3sign =-999;
        // double m_lept3origin = -999;
        // double m_lept3type = -999;

        // double m_lept4Pt =-999;
        // double m_lept4Eta =-999;
        // double m_lept4Phi =-999;
        // double m_lept4sign =-999;
        // double m_lept4origin = -999;
        // double m_lept4type = -999;
        // double m_Zlep1Pt = -999;
        // double m_Zlep1Phi = -999;
        // double m_Zlep1Eta = -999;
        // double m_Zlep1No = -999;
        // double m_Zlep1sign = -999;

        // double m_Zlep2Pt = -999;
        // double m_Zlep2sign = -999;
        // double m_Zlep2Phi = -999;
        // double m_Zlep2Eta = -999;
        // double m_Zlep2No = -999;

        // double m_WlepPt = -999;
        // double m_WlepPhi = -999;
        // double m_WlepEta = -999;
        // double m_WlepNo = -999;
        // double m_Wlepsign = -999;

        // VR setup
        // double m_lept1Pt_VR = -999;
        // double m_lept1Eta_VR = -999;
        // double m_lept1Phi_VR = -999;
        // double m_lept1sign_VR = -999;

        // double m_lept2Pt_VR = -999;
        // double m_lept2Eta_VR = -999;
        // double m_lept2Phi_VR = -999;
        // double m_lept2sign_VR = -999;

        //Jet Variables
        int m_nJets=0;
        // int m_nBtagJets=0;

        double m_jet1Pt =-999;
        // double m_jet1Eta =-999;
        // double m_jet1Phi =-999;
        // double m_jet1M=-999;
        // double m_jet1origin=-999;
        // double m_jet1type=-999;

        double m_jet2Pt=-999;
        // double m_jet2Eta=-999;
        // double m_jet2Phi=-999;
        // double m_jet2M=-999;
        // double m_jet2origin=-999;
        // double m_jet2type=-999;

        // double m_jet3Pt=-999;
        // double m_jet3Eta=-999;
        // double m_jet3Phi=-999;
        // double m_jet3M=-999;
        // double m_jet3origin=-999;
        // double m_jet3type=-999;

        // double m_jet4Pt=-999;
        // double m_jet4Eta=-999;
        // double m_jet4Phi=-999;
        // double m_jet4M=-999;
        // double m_jet4origin=-999;
        // double m_jet4type=-999;

        //Di-Lepton System: Calculated for OS Pairs
        double m_mll=-999;
        // double m_mt2=-999;
        // double m_dRll=-999;
        // double m_ptll=-999;
        // double m_Zeta=-999;

        //Tri-Lepton System:
        // double m_mlll=-999;
        // double m_ptlll=-999;
        double m_mTW=-999;
        // double m_mTW_alt = -999;
        // double m_mll_alt = -999;
        //Di-Jet system: Calculated for the Two Leading Jets
        double m_mjj=-999;
        // double m_dRjj=-999;
        // double m_ptjj=-999;
        // double m_mj2j3 = -999;
        //calculation of overall jet mass
        // double m_mJ=-999;
        // double m_mjjW=-999;//closest to the W-boson mass

        //Cleaning Variable: If MET is in the same direction as the Jet
        double m_minDphi=-999;
        // Some lab frame angles and stuff
        // double m_dphill = -999;
        // double m_dphilep1MET = -999;
        // double m_dphilep2MET = -999;
        // double m_dphilep3MET = -999;
        // double m_dphiJMET = -999;
        // double m_dphilll = -999;
        // double m_dphilllMET = -999;
        // double m_dphillMET = -999;
        // double m_dphijj = -999;
        // double m_dphijet1MET = -999;
        // double m_dphijet2MET = -999;
        // double m_dphijjMET = -999;
        // double m_dphil3MET = -999;
        // double m_MET=-999;
        // double m_MET_phi = -999;
        // double m_METTST = -999;
        // double m_METTST_phi = -999;
        // double m_Meff=-999;
        // double m_LT=-999;

        // double m_MDR=-999;
        // double m_PP_VisShape=-999;
        // double m_gaminvPP=-999;
        // double m_MP=-999;

        // double m_mC1=-999;
        // double m_mN2=-999;

        // double m_mTW_Pa=-999;
        // double m_mTW_PP=-999;

        // double m_mTZ_Pb=-999;
        // double m_mTZ_PP=-999;

        // 3L CA
        // double m_min_mt = -999;
        // double m_pt_lll = -999;
        // double m_mTl3 = -999;
        //##############################//
        //# Recursive Jigsaw Variables #//
        //##############################//

        //Scale Variables
        double m_H2PP=-999;
        // double m_HT2PP=-999;
        // double m_H3PP=-999;
        // double m_HT3PP=-999;
        double m_H4PP=-999;
        double m_HT4PP=-999;
        double m_H5PP=-999;
        double m_HT5PP=-999;
        // double m_H6PP=-999;
        // double m_HT6PP=-999;

        double m_H2Pa=-999;
        double m_H2Pb=-999;
        double m_minH2P=-999;
        // double m_R_H2Pa_H2Pb=-999;
        double m_H3Pa=-999;
        double m_H3Pb=-999;
        double m_minH3P=-999;
        // double m_R_H3Pa_H3Pb=-999;
        double m_R_minH2P_minH3P=-999;
        // double m_minR_pT2i_HT3Pi=-999;
        // double m_maxR_H1PPi_H2PPi=-999;

        //Anglular Variables
        // double m_cosPP=-999;
        // double m_cosPa=-999;
        // double m_cosPb=-999;
        double m_dphiVP=-999;
        // double m_dphiPPV=-999;
        // double m_dphiPC1=-999;
        // double m_dphiPN2=-999;

        // double m_sangle=-999;
        // double m_dangle=-999;

        //Ratio Variables
        // double m_RPZ_HT4PP=-999;
        double m_RPT_HT4PP=-999;
        // double m_R_HT4PP_H4PP=-999;

        // double m_RPZ_HT5PP=-999;
        double m_RPT_HT5PP=-999;
        // double m_R_HT5PP_H5PP=-999;
        // double m_W_PP = -999;
        // double m_WZ_PP = -999;

        ///Variables for the compressed/Intermediate tree
        double m_PTCM=-999;
        double m_PTISR=-999;
        double m_PTI=-999;
        double m_RISR=-999;
        // double m_cosCM=-999;
        // double m_cosS=-999;
        // double m_MISR=-999;
        // double m_dphiCMI=-999;
        // double m_dphiSI=-999;
        double m_dphiISRI=-999;
        // double m_HN2S=-999;
        // double m_R_Ib_Ia=-999;
        // double m_H11S = -999.;
        // double m_HN1Ca = -999.;
        // double m_HN1Cb = -999.;
        // double m_H11Ca = -999.;
        // double m_H11Cb = -999.;
        // double m_cosC = -999.;
        // double m_Is_Z = -999.;
        // double m_Is_OS = -999;
        double m_MZ = -999.;
        double m_MJ = -999.;
        // double m_mTWComp =-999.;
        // double m_cosZ = -999.;
        // double m_cosJ = -999.;
        int m_NjS   = 0;
        int m_NjISR = 0;
        int m_NbS   = 0;
        int m_NbISR = 0;

        // double m_MZ_VR = -999;
        // double m_MJ_VR = -999;
        // double m_PTCM_VR = -999;
        // double m_PTISR_VR = -999;
        // double m_PTI_VR = -999;
        // double m_RISR_VR = -999;
        // double m_dphiISRI_VR = -999;
        // int m_NjS_VR = 0;
        // int m_NjISR_VR = 0;


        // double m_H2PP_VR = -999;
        // double m_H5PP_VR = -999;
        // double m_HT5PP_VR = -999;
        // double m_RPT_HT5PP_VR = -999;
        // double m_dphiVP_VR = -999;
        // double m_R_minH2P_minH3P_VR=-999;

        // double m_DPhi_METW = -999;
        //compressed
        // double m_WmassOnZ = -999;
        // double m_WptOnZ = -999;
        // double m_DPhi_METZ = -999;
        // double m_NonWJet_pT = -999;
        // double m_DPhi_METJetLeading = -999;
        // double m_DR_WOnZ2Jet = -999;
        // double m_DPhi_METNonWJet = -999;
        // double m_DPhi_METWonZ = -999;

        // Testing for low mass 3L
        // double m_M_I = -999;
        // double m_p_z_I = -999;
        // double m_p_z_Ia = -999;
        // double m_p_z_Ib = -999;
        // double m_boostx = -999;
        // double m_boosty = -999;
        // double m_boostz = -999;

        // Classify events

        m_nJets = signalJets.size();

        //if(signalLeptons.size()==2)std::cout << "m_nJets " << m_nJets << " signalLeptons.size() " << signalLeptons.size() << " pt1 " << signalLeptons[0]->pT() << " pt2 " << signalLeptons[1]->pT() <<  std::endl;

        if (signalLeptons.size()==2) m_is2Lep = true;
        else if (signalLeptons.size()==3) {m_is3Lep = true; //cout << "3L here" << endl;
        }
        // else if (signalLeptons.size()==4) m_is4Lep = true;
        //else return;

        if(m_is2Lep && m_nJets>1 ) m_is2Lep2Jet = true;
        if(m_is2Lep && m_nJets>2 && m_nJets<5) m_is2L2JInt = true;
        if(m_is3Lep && m_nJets>0 ) m_is3LInt = true;
        // if(m_is3Lep && m_nJets>1)  m_is3Lep2Jet = true; //
        // if(m_is3Lep && m_nJets>2)  m_is3Lep3Jet = true; //
        // if(m_is4Lep && m_nJets>1)  m_is4Lep2Jet = true; //
        // if(m_is4Lep && m_nJets>2)  m_is4Lep3Jet = true; //

        if(signalLeptons.size()==3)m_is3Lep=true;

        TLorentzVector metLV;
        //TLorentzVector bigFatJet;
        metLV.SetPxPyPzE(ptot.px(),ptot.py(),0.,sqrt(ptot.px()*ptot.px()+ptot.py()*ptot.py()));

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
          //temp.third = lepton_origin->at(lep_signal_index[ilep]);
          //temp.fourth = lepton_type->at(lep_signal_index[ilep]);
          //temp = make_tuple(tlv_temp,lepton_charge->at(lep_signal_index[ilep]),lepton_origin->at(lep_signal_index_[ilep]),lepton_type->at(lepton_sig_index[ilep]));
          myLeptons.push_back(temp);
        }

        sort(myJets.begin(), myJets.end(), SortJets);
        sort(myLeptons.begin(), myLeptons.end(), SortLeptons);

        if(m_is2Lep2Jet)
        {

          // if(myLeptons[0].first.Pt()<25.0 || myLeptons[1].first.Pt()<25.0) return;

          //Setting the Standard Variables
          //Di-Lepton System:
          m_lept1Pt   = myLeptons[0].first.Pt();
          // m_lept1Eta  = myLeptons[0].first.Eta();
          // m_lept1Phi  = myLeptons[0].first.Phi();
          m_lept1sign = myLeptons[0].second;

          m_lept2Pt   = myLeptons[1].first.Pt();
          // m_lept2Eta  = myLeptons[1].first.Eta();
          // m_lept2Phi  = myLeptons[1].first.Phi();
          m_lept2sign = myLeptons[1].second;

          m_mll  = (myLeptons[0].first+myLeptons[1].first).M();
          // m_ptll = (myLeptons[0].first+myLeptons[1].first).Pt();
          // m_dRll = myLeptons[0].first.DeltaR(myLeptons[1].first);
          // m_Zeta = fabs(myLeptons[0].first.Eta() - myLeptons[1].first.Eta());

          vector<TLorentzVector> vleptons;
          vleptons.push_back(myLeptons[0].first);
          vleptons.push_back(myLeptons[1].first);
          //m_mt2 = myTool.GetMt2(vleptons,metLV);

          //min{d#phi}
          double mindphi=100000;
          double dphi=0;
          TLorentzVector tempjet;
          for(unsigned int ijet=0; ijet<signalJets.size();ijet++)
          {
            tempjet.SetPtEtaPhiM(signalJets[ijet]->pT(),signalJets[ijet]->eta(),signalJets[ijet]->phi(),signalJets[ijet]->mass());

            dphi = fabs(metLV.DeltaPhi(tempjet));

            if(dphi<mindphi) mindphi=dphi;
          }

          m_minDphi = mindphi;//cleaning variable for missmeasured jets;

          //just use the two leading jets
          int indexJ1=0;
          int indexJ2=1;

          //Di-Jet System: Here we decide which jets to use as output. The leading and sub-leading jet pair, or the jet pair with invariant mass closest to the W-Mass
          //jet closest to the W-boson mass
          m_jet1Pt  = myJets[indexJ1].Pt();
          // m_jet1Eta = myJets[indexJ1].Eta();
          // m_jet1Phi = myJets[indexJ1].Phi();
          // m_jet1M   = myJets[indexJ1].M();

          m_jet2Pt  = myJets[indexJ2].Pt();
          // m_jet2Eta = myJets[indexJ2].Eta();
          // m_jet2Phi = myJets[indexJ2].Phi();
          // m_jet2M   = myJets[indexJ2].M();

          // if(m_nJets>2) {
          //   // m_jet3Pt  = myJets[2].Pt();
          //   // m_jet3Eta = myJets[2].Eta();
          //   // m_jet3Phi = myJets[2].Phi();
          //   // m_jet3M   = myJets[2].M();
          //   // m_mj2j3 = (myJets[1] + myJets[2]).M();
          //   if(m_nJets>3) {
          //           // m_jet4Pt  = myJets[3].Pt();
          //           // m_jet4Eta = myJets[3].Eta();
          //           // m_jet4Phi = myJets[3].Phi();
          //           // m_jet4M   = myJets[3].M();
          //   }
          // }

          m_mjj  = (myJets[indexJ1]+myJets[indexJ2]).M();
          // m_ptjj = (myJets[indexJ1]+myJets[indexJ2]).Pt();
          // m_dRjj = myJets[indexJ1].DeltaR(myJets[indexJ2]);


          //////////////////////////////////////////////////////////////////////////////
          //Variables for the conventional approach
          // m_DPhi_METW = fabs((myJets[indexJ1]+myJets[indexJ2]).DeltaPhi(metLV));
          //for the comrpessed tree
          // double min_dPhi = 1000;
          // int WindexJ1 = -999;
          // int WindexJ2 = 999;
          // for (int j0=0;j0<myJets.size();j0++) {

          //   double my_min_dphi= fabs(myJets[j0].DeltaPhi(metLV+myLeptons[0].first+myLeptons[1].first));
          //   if (min_dPhi>my_min_dphi) {
          //     min_dPhi = my_min_dphi;
          //     WindexJ1 = j0;
          //   }
          // }

          // min_dPhi = 1000;
          // for (int j1=0;j1<myJets.size();j1++) {
          //   double my_min_dphi= fabs(myJets[j1].DeltaPhi(metLV+myLeptons[0].first+myLeptons[1].first));

          //   if (min_dPhi>my_min_dphi) {
          //     if (j1!=WindexJ1) {
          //       min_dPhi = my_min_dphi;
          //       WindexJ2 = j1;
          //     }
          //   }
          // }

          // m_WmassOnZ=(myJets[WindexJ1]+myJets[WindexJ2]).M();
          // m_WptOnZ=(myJets[WindexJ1]+myJets[WindexJ2]).Pt();
          // m_DPhi_METZ=fabs((myLeptons[0].first+myLeptons[1].first).DeltaPhi(metLV));
          // TLorentzVector nonWjetsLV;
          // for(int kjet=0;kjet<myJets.size();kjet++) {
          //   if(kjet!=WindexJ1 && kjet!=WindexJ2) {
          //     nonWjetsLV+=myJets[kjet];
          //   }
          // }
          // if(m_nJets>2) {
          //   // m_NonWJet_pT=nonWjetsLV.Pt();
          //   // m_DPhi_METJetLeading = fabs(myJets[0].DeltaPhi(metLV));
          //   // m_DR_WOnZ2Jet = myJets[WindexJ1].DeltaR(myJets[WindexJ2]);
          //   // m_DPhi_METNonWJet = fabs(nonWjetsLV.DeltaPhi(metLV));
          //   // m_DPhi_METWonZ = fabs((myJets[WindexJ1]+myJets[WindexJ2]).DeltaPhi(metLV));
          // }
          //////////////////////////////////////////////////////////////////////////////


          L1_2L2J->SetLabFrameFourVector(myLeptons[0].first); // Set lepton 4-vectors
          L2_2L2J->SetLabFrameFourVector(myLeptons[1].first);
          J1_2L2J->SetLabFrameFourVector(myJets[indexJ1]); // Set jets 4-vectors
          J2_2L2J->SetLabFrameFourVector(myJets[indexJ2]);
          TVector3 MET = ETMiss;                     // Get the MET
          MET.SetZ(0.);
          INV_2L2J->SetLabFrameThreeVector(MET);                  // Set the MET in reco tree
          TLorentzVector lep1;
          TLorentzVector lep2;
          //////////////////////////////////////////////////
          //Lotentz vectors have been set, now do the boosts
          //////////////////////////////////////////////////

          // Analyze the event
          if(!LAB_2L2J->AnalyzeEvent())
          {
            str errmsg;
            errmsg  = "Some problem occurred when calling LAB_2L2J->AnalyzeEvent() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
            piped_warnings.request(LOCAL_INFO, errmsg);
            return;
          }


          //cout << L1_2L2J->GetFourVector(*LAB_2L2J).Pt() << endl;
          if (L1_2L2J->GetFourVector(*LAB_2L2J).Pt() > L2_2L2J->GetFourVector(*LAB_2L2J).Pt()){
            // m_Zlep1Pt = L1_2L2J->GetFourVector(*LAB_2L2J).Pt();
            // m_Zlep1sign = myLeptons[0].second;
            // m_Zlep1No = 0;
            // m_Zlep2Pt = L2_2L2J->GetFourVector(*LAB_2L2J).Pt();
            // m_Zlep2sign = myLeptons[1].second;
            // m_Zlep2No = 1;
            lep1 = L1_2L2J->GetFourVector(*LAB_2L2J);
            lep2 = L2_2L2J->GetFourVector(*LAB_2L2J);
          }
          else {
            // m_Zlep1Pt = L2_2L2J->GetFourVector(*LAB_2L2J).Pt();
            // m_Zlep1sign = myLeptons[1].second;
            // m_Zlep1No = 1;
            // m_Zlep2Pt = L1_2L2J->GetFourVector(*LAB_2L2J).Pt();
            // m_Zlep2sign = myLeptons[0].second;
            // m_Zlep2No = 0;

            lep1 = L2_2L2J->GetFourVector(*LAB_2L2J);
            lep2 = L1_2L2J->GetFourVector(*LAB_2L2J);
          }
          // set the jet lab frame 4-vector
          TLorentzVector jet1 = J1_2L2J->GetFourVector(*LAB_2L2J);
          TLorentzVector jet2 = J2_2L2J->GetFourVector(*LAB_2L2J);

          // Some lab frame stuff
          // m_dphill = lep1.DeltaPhi(lep2);
          // m_dphilep1MET = fabs(lep1.DeltaPhi(metLV));
          // m_dphilep2MET = fabs(lep2.DeltaPhi(metLV));
          // m_dphillMET = fabs((lep1 + lep2).DeltaPhi(metLV));
          // m_dphijet1MET = fabs(jet1.DeltaPhi(metLV));
          // m_dphijet2MET = fabs(jet2.DeltaPhi(metLV));
          // m_dphijj = fabs(jet1.DeltaPhi(jet2));
          // m_dphijjMET = fabs((jet1 + jet2).DeltaPhi(metLV));
          //... then by setting the Variables
          TLorentzVector vP_V1aPP = J1_2L2J->GetFourVector(*C1N2_2L2J);
          TLorentzVector vP_V2aPP = J2_2L2J->GetFourVector(*C1N2_2L2J);
          TLorentzVector vP_V1bPP = L1_2L2J->GetFourVector(*C1N2_2L2J);
          TLorentzVector vP_V2bPP = L2_2L2J->GetFourVector(*C1N2_2L2J);
          TLorentzVector vP_IaPP  = X1a_2L2J->GetFourVector(*C1N2_2L2J);
          TLorentzVector vP_IbPP  = X1b_2L2J->GetFourVector(*C1N2_2L2J);

          TLorentzVector vP_V1aPa = J1_2L2J->GetFourVector(*C1a_2L2J);
          TLorentzVector vP_V2aPa = J2_2L2J->GetFourVector(*C1a_2L2J);
          TLorentzVector vP_IaPa  = X1a_2L2J->GetFourVector(*C1a_2L2J);
          TLorentzVector vP_V1bPb = L1_2L2J->GetFourVector(*N2b_2L2J);
          TLorentzVector vP_V2bPb = L2_2L2J->GetFourVector(*N2b_2L2J);
          TLorentzVector vP_IbPb  = X1b_2L2J->GetFourVector(*N2b_2L2J);


          //Variables w/ 4 objects
          //Four vector sum of all visible objets + four vector sum of inv objects
          m_H2PP = (vP_V1aPP + vP_V2aPP + vP_V1bPP + vP_V2bPP).P() + (vP_IaPP+vP_IbPP).P();//H(1,1)PP
          // m_HT2PP = (vP_V1aPP + vP_V2aPP + vP_V1bPP + vP_V2bPP).Pt() + (vP_IaPP+vP_IbPP).Pt();//HT(1,1)PP
          //Scalar sum of all visible objects + vector sum of invisible momenta
          m_H5PP = vP_V1aPP.P() + vP_V2aPP.P() + vP_V1bPP.P() + vP_V2bPP.P() + (vP_IaPP + vP_IbPP).P();//H(4,1)PP
          m_HT5PP = vP_V1aPP.Pt() + vP_V2aPP.Pt() + vP_V1bPP.Pt() + vP_V2bPP.Pt() + (vP_IaPP + vP_IbPP).Pt();//HT(4,1)PP
          //scalar sum of all objects
          // m_H6PP = vP_V1aPP.P() + vP_V2aPP.P() + vP_V1bPP.P() + vP_V2bPP.P() + vP_IaPP.P() + vP_IbPP.P();//H(4,2)PP
          // m_HT6PP = vP_V1aPP.Pt() + vP_V2aPP.Pt() + vP_V1bPP.Pt() + vP_V2bPP.Pt() + vP_IaPP.Pt() + vP_IbPP.Pt();

          m_H2Pa = (vP_V1aPa + vP_V2aPa).P() + vP_IaPa.P();
          m_H2Pb = (vP_V1bPb + vP_V2bPb).P() + vP_IbPb.P();
          m_H3Pa = vP_V1aPa.P() + vP_V2aPa.P() + vP_IaPa.P();
          m_H3Pb = vP_V1bPb.P() + vP_V2bPb.P() + vP_IbPb.P();
          m_minH2P = std::min(m_H2Pa,m_H2Pb);
          m_minH3P = std::min(m_H3Pa,m_H3Pb);
          // m_R_H2Pa_H2Pb = m_H2Pa/m_H2Pb;
          // m_R_H3Pa_H3Pb = m_H3Pa/m_H3Pb;
          m_R_minH2P_minH3P = m_minH2P/m_minH3P;
          // std::cout << " m_R_minH2P_minH3P " << m_R_minH2P_minH3P << " " << m_minH2P << " " <<  m_minH3P << std::endl;
          // double H3PTa = vP_V1aPa.Pt() + vP_V2aPa.Pt() + vP_IaPa.Pt();

          // m_minR_pT2i_HT3Pi = std::min(vP_V1aPa.Pt()/H3PTa,vP_V2aPa.Pt()/H3PTa);


          // m_R_HT5PP_H5PP = m_HT5PP/m_H5PP;

          // Invisible in the PP frame, Px frames and lab frame
          TLorentzVector vP_IaLAB = X1a_2L2J->GetFourVector(*LAB_2L2J);
          TLorentzVector vP_IbLAB = X1b_2L2J->GetFourVector(*LAB_2L2J);
          // m_IaLAB = vP_IaLAB.P();
          // m_IbLAB = vP_IbLAB.P();
          // m_IaPP = vP_IaPP.P();
          // m_IbPP = vP_IbPP.P();
          // m_IaPa = vP_IaPa.P();
          // m_IbPb = vP_IbPb.P();

          // double jetMetphiP = (vP_V1aPa+vP_V2aPa).DeltaPhi(vP_IaPa);
          // m_mTW_Pa = sqrt(2*(vP_V1aPa+vP_V2aPa).Pt()*vP_IaPa.Pt()*(1-cos(jetMetphiP)));

          // double jetMetphiPP = (vP_V1aPP+vP_V2aPP).DeltaPhi(vP_IaPP+vP_IbPP);
          // m_mTW_PP = sqrt(2*(vP_V1aPP+vP_V2aPP).Pt()*(vP_IaPP+vP_IbPP).Pt()*(1-cos(jetMetphiPP)));

          // double dilepMetphiP = (vP_V1bPb+vP_V2bPb).DeltaPhi(vP_IbPb);
          // m_mTZ_Pb = sqrt(2*(vP_V1bPb+vP_V2bPb).Pt()*vP_IbPb.Pt()*(1-cos(dilepMetphiP)));

          // double dilepMetphiPP = (vP_V1bPP+vP_V2bPP).DeltaPhi(vP_IaPP+vP_IbPP);
          // m_mTZ_PP = sqrt(2*(vP_V1bPP+vP_V2bPP).Pt()*(vP_IaPP+vP_IbPP).Pt()*(1-cos(dilepMetphiPP)));


          // double H1PPa = (vP_V1aPP + vP_V2aPP).P();
          // double H1PPb = (vP_V1bPP + vP_V2bPP).P();
          // double H2PPa = vP_V1aPP.P() + vP_V2aPP.P();
          // double H2PPb = vP_V1bPP.P() + vP_V2bPP.P();
          // m_maxR_H1PPi_H2PPi = std::max(H1PPa/H2PPa,H1PPb/H2PPb);

          // signal variables
          TLorentzVector vP_Va = C1a_2L2J->GetVisibleFourVector(*C1a_2L2J);
          TLorentzVector vP_Vb = N2b_2L2J->GetVisibleFourVector(*N2b_2L2J);
          // m_MP = (vP_Va.M2()-vP_Vb.M2())/(2.*(vP_Va.E()-vP_Vb.E()));

          // double P_P = C1a_2L2J->GetMomentum(*C1N2_2L2J);

          // double MPP = 2.*sqrt(P_P*P_P + m_MP*m_MP);
          TVector3 vP_PP = C1N2_2L2J->GetFourVector(*LAB_2L2J).Vect();
          double Pt_PP = vP_PP.Pt();
          // double Pz_PP = fabs(vP_PP.Pz());
          m_RPT_HT5PP = Pt_PP / (Pt_PP + m_HT5PP);
          // m_RPZ_HT5PP = Pz_PP / (Pz_PP + m_HT5PP);

          // m_PP_VisShape = C1N2_2L2J->GetVisibleShape();

          // m_gaminvPP = 2.*m_MP/MPP;
          // m_MDR = m_PP_VisShape*C1N2_2L2J->GetMass();

          // m_mC1 = C1a_2L2J->GetMass();
          // m_mN2 = N2b_2L2J->GetMass();


          //Angular properties of the sparticles system
          // m_cosPP = C1N2_2L2J->GetCosDecayAngle(); //decay angle of the PP system
          // m_cosPa = C1a_2L2J->GetCosDecayAngle(*X1a_2L2J);//decay angle of the C1a system
          // m_cosPb = N2b_2L2J->GetCosDecayAngle(*X1b_2L2J);//decay angle of the N2b system

          //difference in azimuthal angle between the total sum of visible ojects in the C1N2 frame
          // m_dphiPPV = C1N2_2L2J->GetDeltaPhiBoostVisible();
          m_dphiVP = C1N2_2L2J->GetDeltaPhiDecayVisible();

          //hemisphere variables
          // m_dphiPC1 = C1a_2L2J->GetDeltaPhiDecayPlanes(*Wa_2L2J);
          // m_dphiPN2 = N2b_2L2J->GetDeltaPhiDecayPlanes(*Zb_2L2J);

          // m_sangle =(m_cosPa+(m_dphiVP-acos(-1.)/2.)/(acos(-1.)/2.))/2.;
          // m_dangle =(m_cosPa-(m_dphiVP-acos(-1.)/2.)/(acos(-1.)/2.))/2.;
        }//end is 2L2J event

        if(m_is3Lep){

          // bool m_pass3L_presel;

          // if(myLeptons[0].first.Pt()<25.0 || myLeptons[1].first.Pt()<25.0 || myLeptons[2].first.Pt()<20.0) {
          //   m_pass3L_presel=false;
          // }
          // else {
          //   m_pass3L_presel=true;
          // }

          //if(!m_pass3L_presel)return;

          //Tri-Lepton System
          //Here we choose leptons based on where they "come from"
          //lept1 and lept2 are the lepton pair with invariant mass closest to the Z-Mass
          //lept3 is the remaining lepton
          //This is meant to emulate lept1 and lept2 being produced by the Z, while lept3 is produced by the W

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

          if(!foundSFOS) {
            m_foundSFOS=false;
          }
          else {
            m_foundSFOS=true;
          }

          if(m_foundSFOS){

            int Wlep1 = -999;
            if( (Zlep1==0 && Zlep2==1) || (Zlep1==1 && Zlep2==0) ) Wlep1=2;
            else if( (Zlep1==0 && Zlep2==2) || (Zlep1==2 && Zlep2==0) ) Wlep1=1;
            else if((Zlep1==1 && Zlep2==2) || (Zlep1==2 && Zlep2==1) ) Wlep1=0;

            //Knowing the indices, we perform assignments
            m_lept1Pt   = myLeptons[0].first.Pt();
            m_lept1sign = myLeptons[0].second;

            m_lept2Pt   = myLeptons[1].first.Pt();
            m_lept2sign = myLeptons[1].second;

            m_lept3Pt   = myLeptons[2].first.Pt();
            m_lept3sign = myLeptons[2].second;


            m_mll  = Zmass; //based on mass minimization

            vector<TLorentzVector> Leptons;
            Leptons.push_back(myLeptons[Wlep1].first);
            Leptons.push_back(myLeptons[Zlep1].first);
            Leptons.push_back(myLeptons[Zlep2].first);


            double wlepMetphi = myLeptons[Wlep1].first.DeltaPhi(metLV);

            m_mTW = sqrt(2*myLeptons[Wlep1].first.Pt()*metLV.Pt()*(1-cos(wlepMetphi)));

            INV_3L->SetLabFrameThreeVector(ETMiss); //set the MET in the event


            L1a_3L->SetLabFrameFourVector(Leptons[0]); // Set lepton from W
            L1b_3L->SetLabFrameFourVector(Leptons[1]); // Set lepton1 from Z
            L2b_3L->SetLabFrameFourVector(Leptons[2]); // Set lepton2 from Z

            if(!LAB_3L->AnalyzeEvent())
            {
              str errmsg;
              errmsg  = "Some problem occurred when calling LAB_3L->AnalyzeEvent() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
              piped_warnings.request(LOCAL_INFO, errmsg);
              return;
            }


            TLorentzVector l1;
            TLorentzVector l2;
            TLorentzVector l3 = L1a_3L->GetFourVector(*LAB_3L);

            //if(DEBUG) cout << "WlepPt: " << m_WlepPt << " Wlepsign: " << m_Wlepsign << endl;
            if (L1b_3L->GetFourVector(*LAB_3L).Pt() > L2b_3L->GetFourVector(*LAB_3L).Pt()){
              l1 = L1b_3L->GetFourVector(*LAB_3L);
              l2 = L2b_3L->GetFourVector(*LAB_3L);
            }
            else {
              l2 = L1b_3L->GetFourVector(*LAB_3L);
              l1 = L2b_3L->GetFourVector(*LAB_3L);
            }

            // More lab frame stuff

            //if(DEBUG)  cout << "Zlep1: " << m_Zlep1Pt << " " << m_Zlep1sign << " Zlep2Pt: " << m_Zlep2Pt << " " << m_Zlep2sign << endl;
            TLorentzVector vP_V1aPP  = L1a_3L->GetFourVector(*C1N2_3L);
            TLorentzVector vP_V1bPP  = L1b_3L->GetFourVector(*C1N2_3L);
            TLorentzVector vP_V2bPP  = L2b_3L->GetFourVector(*C1N2_3L);
            TLorentzVector vP_I1aPP  = X1a_3L->GetFourVector(*C1N2_3L);
            TLorentzVector vP_I1bPP  = X1b_3L->GetFourVector(*C1N2_3L);

            TLorentzVector vP_V1aPa  = L1a_3L->GetFourVector(*C1a_3L);
            TLorentzVector vP_I1aPa  = X1a_3L->GetFourVector(*C1a_3L);

            TLorentzVector vP_V1bPb = L1b_3L->GetFourVector(*N2b_3L);
            TLorentzVector vP_V2bPb = L2b_3L->GetFourVector(*N2b_3L);
            TLorentzVector vP_I1bPb = X1b_3L->GetFourVector(*N2b_3L);



            //Variables w/ 4 objects

            /// Defined in the PP-frame
            //Four vector sum of all visible objets + four vector sum of inv objects

            //Scalar sum of all visible objects + vector sum of invisible momenta
            m_H4PP = vP_V1aPP.P() + vP_V1bPP.P() + vP_V2bPP.P() + (vP_I1aPP + vP_I1bPP).P();//H(3,1)PP
            m_HT4PP = vP_V1aPP.Pt() + vP_V1bPP.Pt() + vP_V2bPP.Pt() + (vP_I1aPP + vP_I1bPP).Pt();//HT(3,1)PP

            // Invisible components again
            TLorentzVector vP_IaLAB = X1a_3L->GetFourVector(*LAB_3L);
            TLorentzVector vP_IbLAB = X1b_3L->GetFourVector(*LAB_3L);


            // Testing for low mass 3L
            TLorentzVector p_Ia_Lab = X1a_3L->GetFourVector(*LAB_3L);
            TLorentzVector p_Ib_Lab = X1b_3L->GetFourVector(*LAB_3L);
            TVector3 lab_to_pp = C1N2_3L->GetBoostInParentFrame();

            /// Defined in the P-frame
            m_H2Pa = (vP_V1aPa).P() + (vP_I1aPa).P(); //H(1,1)P
            m_H2Pb = (vP_V1bPb + vP_V2bPb).P() + vP_I1bPb.P();//H(1,1)P

            m_H3Pa = vP_V1aPa.P() + vP_I1aPa.P();//H(1,1)P
            m_H3Pb = vP_V1bPb.P() + vP_V2bPb.P() + vP_I1bPb.P();//H(2,1)P

            m_minH2P = std::min(m_H2Pa,m_H2Pb);
            m_minH3P = std::min(m_H3Pa,m_H3Pb);
            // m_R_H2Pa_H2Pb = m_H2Pa/m_H2Pb;
            // m_R_H3Pa_H3Pb = m_H3Pa/m_H3Pb;
            m_R_minH2P_minH3P = m_H2Pb/m_H3Pb;

            // double H1PPa = (vP_V1aPP).P();
            // double H1PPb = (vP_V1bPP + vP_V2bPP).P();
            // double H2PPa = vP_V1aPP.P() + vP_I1aPP.P();
            // double H2PPb = (vP_V1bPP+vP_V2bPP).P() + vP_I1bPP.P();
            // m_maxR_H1PPi_H2PPi = std::max(H1PPa/H2PPa,H1PPb/H2PPb);

            ////Calculation of dRll_I_PP;
            //m_dRll_I_PP = (vP_V1bPP+vP_V1bPP).DeltaR(vP_I1bPP);
            //m_R_Ib_Ia = (vP_V1bPP + vP_V2bPP + vP_I1bPP).P()/(vP_V1aPP+vP_I1aPP).P();

            // signal variables
            TLorentzVector vP_Va = C1a_3L->GetVisibleFourVector(*C1a_3L);
            TLorentzVector vP_Vb = N2b_3L->GetVisibleFourVector(*N2b_3L);

            TVector3 vP_PP = C1N2_3L->GetFourVector(*LAB_3L).Vect();
            double Pt_PP = vP_PP.Pt();
            m_RPT_HT4PP = Pt_PP / (Pt_PP + m_HT4PP);


            // mt_min here

            /*double min0 = -999;
            double min1 = -999;
            double min2 = -999;
            double lepmetphi0 = myLeptons[0].first.DeltaPhi(metLV);
            double lepmetphi1 = myLeptons[1].first.DeltaPhi(metLV);
            double lepmetphi2 = myLeptons[2].first.DeltaPhi(metLV);

            if (myLeptons[0].second == -myLeptons[1].second) min0 =  sqrt(2*myLeptons[2].first.Pt()*metLV.Pt()*(1-cos(lepmetphi2)));
            if (myLeptons[0].second == -myLeptons[2].second) min1 =  sqrt(2*myLeptons[1].first.Pt()*metLV.Pt()*(1-cos(lepmetphi1)));
            if (myLeptons[1].second == -myLeptons[2].second) min2 =  sqrt(2*myLeptons[0].first.Pt()*metLV.Pt()*(1-cos(lepmetphi0)));

            if (min0 > 0 && min1 > 0) m_min_mt = min(min0,min1);
            else if (min0 > 0 && min2 > 0) m_min_mt = min(min0,min2);
            else if (min1 > 0 && min2 > 0) m_min_mt = min(min1,min2);
            else if (min0 > 0 && min1 < 0 && min2 < 0) m_min_mt = min0;
            else if (min1 > 0 && min0 < 0 && min2 < 0) m_min_mt = min1;
            else if (min2 > 0 && min0 < 0 && min1 <0) m_min_mt = min2;*/

          } // end of if(m_foundSFOS)
        } // end of m_is3Lep

        if(m_is3LInt || m_is2L2JInt) {

          //min{d#phi}
          double mindphi=100000;
          double dphi=0;
          TLorentzVector tempjet;
          for(unsigned int ijet=0; ijet<signalJets.size();ijet++)
          {
            tempjet.SetPtEtaPhiM(signalJets[ijet]->pT(),signalJets[ijet]->eta(),signalJets[ijet]->phi(),signalJets[ijet]->mass());

            dphi = fabs(metLV.DeltaPhi(tempjet));

            if(dphi<mindphi) mindphi=dphi;
          }

          m_minDphi = mindphi;//cleaning variable for missmeasured jets;
          //if( fabs(mindphi)<0.4) return;



          vector<RestFrames::RFKey> jetID;
          for(int i = 0; i < int(myJets.size()); i++){

                  TLorentzVector jet = myJets[i];

                  // transverse view of jet 4-vectors
                  jet.SetPtEtaPhiM(jet.Pt(),0.0,jet.Phi(),jet.M());
                  jetID.push_back(JETS_comb->AddLabFrameFourVector(jet));
          }

          TLorentzVector lepSys(0.,0.,0.,0.);
          for(int i = 0; i < int(myLeptons.size()); i++){
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
            errmsg  = "Some problem occurred when calling LAB_comb->AnalyzeEvent() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
            piped_warnings.request(LOCAL_INFO, errmsg);
            return;
          }

          for(int i = 0; i < int(signalJets.size()); i++){
            if(JETS_comb->GetFrame(jetID[i]) == *J_comb){
              m_NjS++;
              if( analysisBtags.at(signalJets[i]) ) m_NbS++;
            } else {
              m_NjISR++;
              if( analysisBtags.at(signalJets[i]) ) m_NbISR++;
            }
          }

          // 2LNJ analysis
          if(m_is2L2JInt){

            // put jets in their place
            int NJ = jetID.size();
            TLorentzVector vISR(0.,0.,0.,0.);
            for(int i = 0; i < NJ; i++){
              if(JETS_comb->GetFrame(jetID[i]) == *J_comb){
                JETS_2LNJ->AddLabFrameFourVector(myJets[i]);
              } else {
                vISR += myJets[i];
              }
            }

            ISR_2LNJ->SetLabFrameFourVector(vISR);

            // put leptons in their place
            L1_2LNJ->SetLabFrameFourVector(myLeptons[0].first);
            L2_2LNJ->SetLabFrameFourVector(myLeptons[1].first);

            INV_2LNJ->SetLabFrameThreeVector(ETMiss);

            if(!LAB_2LNJ->AnalyzeEvent())
            {
              str errmsg;
              errmsg  = "Some problem occurred when calling LAB_2LNJ->AnalyzeEvent() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
              piped_warnings.request(LOCAL_INFO, errmsg);
              return;
            }

          }

          // 2L1L analysis
          if(m_is3LInt){

            // put jets in their place
            int NJ = jetID.size();
            TLorentzVector vISR(0.,0.,0.,0.);
            for(int i = 0; i < NJ; i++){
              if(JETS_comb->GetFrame(jetID[i]) != *J_comb) vISR += myJets[i];
            }

            ISR_2L1L->SetLabFrameFourVector(vISR);

            // put leptons in their place
            // find min mass OS pair
            pair<int,int> iSFOS;
            double        mSFOS = -1.;
            for(int i = 0; i < 2; i++){
              for(int j = i+1; j < 3; j++){
                if((signbit(myLeptons[i].second) && !signbit(myLeptons[j].second)) || (!signbit(myLeptons[i].second) && signbit(myLeptons[j].second))){
                  if(mSFOS < 0. ||
                  (myLeptons[i].first+myLeptons[j].first).M() < mSFOS){
                    mSFOS = (myLeptons[i].first+myLeptons[j].first).M();
                    iSFOS.first  = i;
                    iSFOS.second = j;
                  }
                }
              }
            }

            for(int i = 0; i < 3; i++){
              if(i == iSFOS.first)
                L1_2L1L->SetLabFrameFourVector(myLeptons[i].first);
              if(i == iSFOS.second)
                L2_2L1L->SetLabFrameFourVector(myLeptons[i].first);
              if(i != iSFOS.first && i != iSFOS.second) {
                Lb_2L1L->SetLabFrameFourVector(myLeptons[i].first);
                //calculate the mTWComp with the remaining lepton
                TLorentzVector themetLV;
                themetLV.SetPxPyPzE(ETMiss.X(),ETMiss.Y(),0.,sqrt(ETMiss.X()*ETMiss.X()+ETMiss.Y()*ETMiss.Y()));
                // double wlepMetphi = myLeptons[i].first.DeltaPhi(themetLV);
                // m_mTWComp = sqrt(2*myLeptons[i].first.Pt()*themetLV.Pt()*(1-cos(wlepMetphi)));
              }
            }

            INV_2L1L->SetLabFrameThreeVector(ETMiss);

            if(!LAB_2L1L->AnalyzeEvent())
            {
              str errmsg;
              errmsg  = "Some problem occurred when calling LAB_2L1L->AnalyzeEvent() from the Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb analysis class.\n";
              piped_warnings.request(LOCAL_INFO, errmsg);
              return;
            }

          }

          TLorentzVector vP_CM;
          TLorentzVector vP_ISR;
          TLorentzVector vP_I;

          if(m_is2L2JInt){

            vP_CM  = CM_2LNJ->GetFourVector();
            vP_ISR = ISR_2LNJ->GetFourVector();
            vP_I   = (*Ia_2LNJ+*Ib_2LNJ).GetFourVector();

            // m_cosCM = CM_2LNJ->GetCosDecayAngle();
            // m_cosS  = S_2LNJ->GetCosDecayAngle();
            // m_MISR = ISR_2LNJ->GetMass();
            // m_dphiCMI = acos(-1.)-fabs(CM_2LNJ->GetDeltaPhiBoostVisible());
            // m_dphiSI  = acos(-1.)-fabs(S_2LNJ->GetDeltaPhiBoostVisible());

            // m_HN2S = //Z_2LNJ->GetFourVector(*S_2LNJ).E() +
            //   L1_2LNJ->GetFourVector(*S_2LNJ).E()+
            //   L2_2LNJ->GetFourVector(*S_2LNJ).E()+
            //   J_2LNJ->GetFourVector(*S_2LNJ).E() +
            //   Ia_2LNJ->GetFourVector(*S_2LNJ).P() +
            //   Ib_2LNJ->GetFourVector(*S_2LNJ).P();
            // m_H11S = 2.*(*Ia_2LNJ+*Ib_2LNJ).GetFourVector(*S_2LNJ).P();
            // m_HN1Ca = Z_2LNJ->GetFourVector(*Ca_2LNJ).E()+
            Ia_2LNJ->GetFourVector(*Ca_2LNJ).P();
            // m_HN1Cb = J_2LNJ->GetFourVector(*Cb_2LNJ).E()+
            //   Ib_2LNJ->GetFourVector(*Cb_2LNJ).P();
            // m_H11Ca = 2.*Ia_2LNJ->GetFourVector(*Ca_2LNJ).P();
            // m_H11Cb = 2.*Ib_2LNJ->GetFourVector(*Cb_2LNJ).P();
            // m_cosC  = Ca_2LNJ->GetCosDecayAngle();

            // if((signbit(myLeptons[0].second) && !signbit(myLeptons[1].second)) || (!signbit(myLeptons[0].second) && signbit(myLeptons[1].second))) m_Is_OS = 1;
            // if(myLeptons[0].second+myLeptons[1].second == 0) m_Is_Z = 1;
            m_MZ = Z_2LNJ->GetMass();
            m_MJ = J_2LNJ->GetMass();

            // m_cosZ = Z_2LNJ->GetCosDecayAngle();
            //if(m_NjS > 1)
            // m_cosJ = JSA_2LNJ->GetCosDecayAngle();
            // m_dphiJMET = fabs(J_2LNJ->GetFourVector(*LAB_2LNJ).DeltaPhi(metLV));
          }

          if(m_is3LInt){

            vP_CM  = CM_2L1L->GetFourVector();
            vP_ISR = ISR_2L1L->GetFourVector();
            vP_I   = (*Ia_2L1L+*Ib_2L1L).GetFourVector();

            // m_cosCM = CM_2L1L->GetCosDecayAngle();
            // m_cosS  = S_2L1L->GetCosDecayAngle();
            // m_MISR = ISR_2L1L->GetMass();
            // m_dphiCMI = acos(-1.)-fabs(CM_2L1L->GetDeltaPhiBoostVisible());
            // m_dphiSI  = acos(-1.)-fabs(S_2L1L->GetDeltaPhiBoostVisible());

            // m_HN2S = //Z_2L1L->GetFourVector(*S_2L1L).E() +
            //   L1_2L1L->GetFourVector(*S_2L1L).E() +
            //   L2_2L1L->GetFourVector(*S_2L1L).E() +
            //   Lb_2L1L->GetFourVector(*S_2L1L).E() +
            //   Ia_2L1L->GetFourVector(*S_2L1L).P() +
            //   Ib_2L1L->GetFourVector(*S_2L1L).P();
            // m_H11S = 2.*(*Ia_2L1L+*Ib_2L1L).GetFourVector(*S_2L1L).P();
            // m_HN1Ca = Z_2L1L->GetFourVector(*Ca_2L1L).E()+
            Ia_2L1L->GetFourVector(*Ca_2L1L).P();
            // m_HN1Cb = Lb_2L1L->GetFourVector(*Cb_2L1L).E()+
            //   Ib_2L1L->GetFourVector(*Cb_2L1L).P();
            // m_H11Ca = 2.*Ia_2L1L->GetFourVector(*Ca_2L1L).P();
            // m_H11Cb = 2.*Ib_2L1L->GetFourVector(*Cb_2L1L).P();
            // m_cosC  = Ca_2L1L->GetCosDecayAngle();
            // m_Is_OS = 1;
            // if(myLeptons[0].second+myLeptons[1].second == 0 ||
            //   myLeptons[0].second+myLeptons[2].second == 0 ||
            //   myLeptons[1].second+myLeptons[2].second == 0) m_Is_Z=1;
            m_MZ = Z_2L1L->GetMass();
            // m_cosZ = Z_2L1L->GetCosDecayAngle();
          }

          m_PTCM = vP_CM.Pt();

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

          m_PTISR =  vPt_ISR.Mag();
          m_RISR  = -vPt_I.Dot(vPt_ISR.Unit()) / m_PTISR;
          m_PTI = vPt_I.Mag();
          m_dphiISRI = fabs(vPt_ISR.Angle(vPt_I));

        }//end INTERMEDIATE

        // Cutflow check

        cutFlowVector_str[0] = "No cuts ";
        cutFlowVector_str[1] = "3LLOW: Preselection ";
        cutFlowVector_str[2] = "3LLOW: 75 GeV < mll < 105 GeV ";
        cutFlowVector_str[3] = "3LLOW: mTW > 100 GeV ";
        cutFlowVector_str[4] = "3LLOW: m_HT4PP/m_H4PP > 0.9 ";
        cutFlowVector_str[5] = "3LLOW: m_H4PP > 250 GeV ";
        cutFlowVector_str[6] = "3LLOW: pT_PP/(pT_PP + HT_PP(3,1)) ";
        cutFlowVector_str[7] = "2L2JLOW: Preselection ";
        cutFlowVector_str[8] = "2L2JLOW: mll ";
        cutFlowVector_str[9] = "2L2JLOW: mjj ";
        cutFlowVector_str[10] = "2L2JLOW: HT_PP(1,1)/HT_PP(4,1) ";
        cutFlowVector_str[11] = "2L2JLOW: pT_PP/(pT_PP + HT_PP(4,1)) ";
        cutFlowVector_str[12] = "2L2JLOW: minDPhi ";
        cutFlowVector_str[13] = "2L2JLOW: HPP(4,1) ";
        cutFlowVector_str[14] = "2L2JINT: Preselection ";
        cutFlowVector_str[15] = "2L2JINT: mll ";
        cutFlowVector_str[16] = "2L2JINT: mjj ";
        cutFlowVector_str[17] = "2L2JINT: HT_PP(1,1)/HT_PP(4,1) ";
        cutFlowVector_str[18] = "2L2JINT: pT_PP/(pT_PP + HT_PP(4,1)) ";
        cutFlowVector_str[19] = "2L2JINT: minDPhi ";
        cutFlowVector_str[20] = "2L2JINT: HPP(4,1) ";
        cutFlowVector_str[21] = "2L2JHIGH: Preselection ";
        cutFlowVector_str[22] = "2L2JHIGH: mll ";
        cutFlowVector_str[23] = "2L2JHIGH: mjj ";
        cutFlowVector_str[24] = "2L2JHIGH: m_R_minH2P_minH3P>0.8";
        cutFlowVector_str[25] = "2L2JHIGH: m_RPT_HT5PP < 0.05 ";
        cutFlowVector_str[26] = "2L2JHIGH: 0.3 < minDPhiVP > 2.8 ";
        cutFlowVector_str[27] = "2L2JHIGH: m_H5PP>800. ";
        cutFlowVector_str[28] = "2L2JCOMP: Preselection ";
        cutFlowVector_str[29] = "2L2JCOMP: mZ ";
        cutFlowVector_str[30] = "2L2JCOMP: mJ ";
        cutFlowVector_str[31] = "2L2JCOMP: dPhi_ISR_I ";
        cutFlowVector_str[32] = "2L2JCOMP: R_ISR ";
        cutFlowVector_str[33] = "2L2JCOMP: p_ISRT ";
        cutFlowVector_str[34] = "2L2JCOMP: p_IT ";
        cutFlowVector_str[35] = "2L2JCOMP: pT_CM ";
        cutFlowVector_str[36] = "3LHIGH: Preselection ";
        cutFlowVector_str[37] = "3LHIGH: mll  ";
        cutFlowVector_str[38] = "3LHIGH: mTW  ";
        cutFlowVector_str[39] = "3LHIGH: m_HT4PP/m_H4PP  ";
        cutFlowVector_str[40] = "3LHIGH: HPb(1,1)/HPb(2,1) ";
        cutFlowVector_str[41] = "3LHIGH: m_H4PP  ";
        cutFlowVector_str[42] = "3LHIGH: pT_PP/(pT_PP + HT_PP(3,1)) ";
        cutFlowVector_str[43] = "3LCOMP: Preselection ";
        cutFlowVector_str[44] = "3LCOMP: mll ";
        cutFlowVector_str[45] = "3LCOMP: mTW  ";
        cutFlowVector_str[46] = "3LCOMP: dPhi_ISRI ";
        cutFlowVector_str[47] = "3LCOMP: R_ISR ";
        cutFlowVector_str[48] = "3LCOMP: p_ISRT ";
        cutFlowVector_str[49] = "3LCOMP: p_IT ";
        cutFlowVector_str[50] = "3LCOMP: pT_CM ";
        cutFlowVector_str[51] = "3LINT: Preselection ";
        cutFlowVector_str[52] = "3LINT: mll ";
        cutFlowVector_str[53] = "3LINT: mTW  ";
        cutFlowVector_str[54] = "3LINT: m_HT4PP/m_H4PP  ";
        cutFlowVector_str[55] = "3LINT: HPb(1,1)/HPb(2,1) ";
        cutFlowVector_str[56] = "3LINT: m_H4PP ";
        cutFlowVector_str[57] = "3LINT: pT_PP/(pT_PP + HT_PP(3,1)) ";

        //std::cout << " m_is3Lep " << m_is3Lep <<  " m_is2Lep2Jet " << m_is2Lep2Jet << " m_is2L2JInt " << m_is2L2JInt << " m_is3LInt " << m_is3LInt << " m_is3Lep2Jet " << m_is3Lep2Jet << " m_is3Lep3Jet " << m_is3Lep3Jet << " m_is4Lep2Jet " << m_is4Lep2Jet << " m_is4Lep3Jet " << m_is4Lep3Jet << std::endl;

        //if(m_is3Lep)std::cout << " m_is3Lep " << m_is3Lep << " m_lept1sign " << m_lept1sign << " m_lept2sign " << m_lept2sign << " m_lept1Pt " << m_lept1Pt << " m_lept2Pt " << m_lept2Pt << " m_lept3Pt " << m_lept3Pt << " signalBJets.size() " << signalBJets.size() << " signalJets.size() " << signalJets.size() << std::endl;

        for(int j=0;j<NCUTS;j++){

          if( (j==0) ||

          (j==1 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>40. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()==0) ||

          (j==2 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>40. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()==0 && m_mll>75. && m_mll<105.) ||

          (j==3 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>40. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()==0 && m_mll>75. && m_mll<105. && m_mTW>100.) ||

          (j==4 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>40. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()==0 && m_mll>75. && m_mll<105. && m_mTW>100. && m_HT4PP/m_H4PP > 0.9) ||

          (j==5 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>40. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()==0 && m_mll>75. && m_mll<105. && m_mTW>100. && m_HT4PP/m_H4PP > 0.9 && m_H4PP > 250.) ||

          (j==6 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>40. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()==0 && m_mll>75. && m_mll<105. && m_mTW>100. && m_HT4PP/m_H4PP > 0.9 && m_H4PP > 250. && m_RPT_HT4PP < 0.05) ||

          /*cutFlowVector_str[7] = "2L2JLOW: Preselection ";
          cutFlowVector_str[8] = "2L2JLOW: 80 GeV < mll < 100 GeV";
          cutFlowVector_str[9] = "2L2JLOW: 70 GeV < mjj < 90 GeV ";
          cutFlowVector_str[10] = "2L2JLOW: HT_PP(1,1)/HT_PP(4,1) ";
          cutFlowVector_str[11] = "2L2JLOW: pT_PP/(pT_PP + HT_PP(4,1)) ";
          cutFlowVector_str[12] = "2L2JLOW: minDPhi ";
          cutFlowVector_str[13] = "2L2JLOW: HPP(4,1) ";*/

          (j==7 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()==2) ||

          (j==8 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()==2 && m_mll>80. && m_mll<100.) ||

          (j==9 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()==2 && m_mll>80. && m_mll<100. && m_mjj>70. && m_mjj<90.) ||

          (j==10 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()==2 && m_mll>80. && m_mll<100. && m_mjj>70. && m_mjj<90. && m_H2PP/m_H5PP>0.35 && m_H2PP/m_H5PP<0.6) ||

          (j==11 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()==2 && m_mll>80. && m_mll<100. && m_mjj>70. && m_mjj<90. && m_H2PP/m_H5PP>0.35 && m_H2PP/m_H5PP<0.6 && m_RPT_HT5PP<0.05) ||

          (j==12 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()==2 && m_mll>80. && m_mll<100. && m_mjj>70. && m_mjj<90. && m_H2PP/m_H5PP>0.35 && m_H2PP/m_H5PP<0.6 && m_RPT_HT5PP<0.05 && m_minDphi>2.4) ||

          (j==13 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()==2 && m_mll>80. && m_mll<100. && m_mjj>70. && m_mjj<90. && m_H2PP/m_H5PP>0.35 && m_H2PP/m_H5PP<0.6 && m_RPT_HT5PP<0.05 && m_minDphi>2.4 && m_H5PP>400.) ||

          /*cutFlowVector_str[14] = "2L2JINT: Preselection ";
          cutFlowVector_str[15] = "2L2JINT: mll ";
          cutFlowVector_str[16] = "2L2JINT: mjj ";
          cutFlowVector_str[17] = "2L2JINT: HT_PP(1,1)/HT_PP(4,1) ";
          cutFlowVector_str[18] = "2L2JINT: pT_PP/(pT_PP + HT_PP(4,1)) ";
          cutFlowVector_str[19] = "2L2JINT: minDPhi ";
          cutFlowVector_str[20] = "2L2JINT: HPP(4,1) ";*/

          (j==14 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2) ||

          (j==15 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100.) ||

          (j==16 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. &&  m_mjj>60. && m_mjj<100.) ||

          (j==17 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. &&  m_mjj>60. && m_mjj<100. && m_R_minH2P_minH3P>0.8 ) ||

          (j==18 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. &&  m_mjj>60. && m_mjj<100. && m_R_minH2P_minH3P>0.8 && m_RPT_HT5PP<0.05) ||

          (j==19 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. &&  m_mjj>60. && m_mjj<100. && m_R_minH2P_minH3P>0.8 && m_RPT_HT5PP<0.05 && m_dphiVP>0.6) ||

          (j==20 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. &&  m_mjj>60. && m_mjj<100. && m_R_minH2P_minH3P>0.8 && m_RPT_HT5PP<0.05 && m_dphiVP>0.6 && m_H5PP>600.) ||

          /* cutFlowVector_str[21] = "2L2JHIGH: Preselection ";
          cutFlowVector_str[22] = "2L2JHIGH: mll ";
          cutFlowVector_str[23] = "2L2JHIGH: mjj ";
          cutFlowVector_str[24] = "2L2JHIGH: m_R_minH2P_minH3P>0.8";
          cutFlowVector_str[25] = "2L2JHIGH: m_RPT_HT5PP < 0.05 ";
          cutFlowVector_str[26] = "2L2JHIGH: 0.3 < minDPhiVP > 2.8 ";
          cutFlowVector_str[27] = "2L2JHIGH: m_H5PP>800. ";*/

          (j==21 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2) ||

          (j==22 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100.) ||

          (j==23 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. && m_mjj>60. && m_mjj<100.) ||

          (j==24 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. && m_mjj>60. && m_mjj<100. && m_R_minH2P_minH3P>0.8) ||

          (j==25 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. && m_mjj>60. && m_mjj<100. && m_R_minH2P_minH3P>0.8 && m_RPT_HT5PP< 0.05) ||

          (j==26 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. && m_mjj>60. && m_mjj<100. && m_R_minH2P_minH3P>0.8 && m_RPT_HT5PP< 0.05 && m_dphiVP>0.3 && m_dphiVP<2.8 ) ||

          (j==27 && m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. && m_mjj>60. && m_mjj<100. && m_R_minH2P_minH3P>0.8 && m_RPT_HT5PP< 0.05 && m_dphiVP>0.3 && m_dphiVP<2.8 && m_H5PP>800.) ||

          /*cutFlowVector_str[28] = "2L2JCOMP: Preselection ";
          cutFlowVector_str[29] = "2L2JCOMP: mZ ";
          cutFlowVector_str[30] = "2L2JCOMP: mJ ";
          cutFlowVector_str[31] = "2L2JCOMP: dPhi_ISR_I ";
          cutFlowVector_str[32] = "2L2JCOMP: R_ISR ";
          cutFlowVector_str[33] = "2L2JCOMP: p_ISRT ";
          cutFlowVector_str[34] = "2L2JCOMP: p_IT ";
          cutFlowVector_str[35] = "2L2JCOMP: pT_CM ";*/

          (j==28 && m_is2L2JInt && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && m_NjS==2 && m_NjISR>0) ||

          (j==29 && m_is2L2JInt && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && m_NjS==2 && m_NjISR>0 && m_MZ>80. && m_MZ<100.) ||

          (j==30 && m_is2L2JInt && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && m_NjS==2 && m_NjISR>0 && m_MZ>80. && m_MZ<100. && m_MJ>50. && m_MJ<110.) ||

          (j==31 && m_is2L2JInt && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && m_NjS==2 && m_NjISR>0 && m_MZ>80. && m_MZ<100. && m_MJ>50. && m_MJ<110. && m_dphiISRI>2.8) ||

          (j==32 && m_is2L2JInt && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && m_NjS==2 && m_NjISR>0 && m_MZ>80. && m_MZ<100. && m_MJ>50. && m_MJ<110. && m_dphiISRI>2.8 && m_RISR > 0.40 && m_RISR < 0.75 ) ||

          (j==33 && m_is2L2JInt && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && m_NjS==2 && m_NjISR>0 && m_MZ>80. && m_MZ<100. && m_MJ>50. && m_MJ<110. && m_dphiISRI>2.8 && m_RISR > 0.40 && m_RISR < 0.75  &&  m_PTISR > 180.) ||

          (j==34 && m_is2L2JInt && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && m_NjS==2 && m_NjISR>0 && m_MZ>80. && m_MZ<100. && m_MJ>50. && m_MJ<110. && m_dphiISRI>2.8 && m_RISR > 0.40 && m_RISR < 0.75  &&  m_PTISR > 180. && m_PTI > 100.) ||

          (j==35 && m_is2L2JInt && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && m_NjS==2 && m_NjISR>0 && m_MZ>80. && m_MZ<100. && m_MJ>50. && m_MJ<110. && m_dphiISRI>2.8 && m_RISR > 0.40 && m_RISR < 0.75  &&  m_PTISR > 180. && m_PTI > 100. && m_PTCM < 20.) ||


          /* cutFlowVector_str[36] = "3LHIGH: Preselection ";
          cutFlowVector_str[37] = "3LHIGH: 75 GeV < mll < 105 GeV ";
          cutFlowVector_str[38] = "3LHIGH: mTW  ";
          cutFlowVector_str[39] = "3LHIGH: m_HT4PP/m_H4PP  ";
          cutFlowVector_str[40] = "3LHIGH: HPb(1,1)/HPb(2,1) ";
          cutFlowVector_str[41] = "3LHIGH: m_H4PP ";
          cutFlowVector_str[42] = "3LHIGH: pT_PP/(pT_PP + HT_PP(3,1)) ";*/


          (j==36 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>60. && m_lept3Pt>40. && signalBJets.size()==0 && signalJets.size()<3) ||

          (j==37 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>60. && m_lept3Pt>40. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105.) ||

          (j==38 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>60. && m_lept3Pt>40. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>150.) ||

          (j==39 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>60. && m_lept3Pt>40. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>150. && m_HT4PP/m_H4PP > 0.75) ||

          (j==40 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>60. && m_lept3Pt>40. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>150. && m_HT4PP/m_H4PP > 0.75 && m_R_minH2P_minH3P>0.8) ||

          (j==41 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>60. && m_lept3Pt>40. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>150. && m_R_minH2P_minH3P>0.8 && m_HT4PP/m_H4PP > 0.75 && m_H4PP > 550. ) ||

          (j==42 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>60. && m_lept3Pt>40. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>150. && m_R_minH2P_minH3P>0.8 && m_HT4PP/m_H4PP > 0.75 && m_H4PP > 550. && m_RPT_HT4PP < 0.2) ||

          /*cutFlowVector_str[43] = "3LCOMP: Preselection ";
          cutFlowVector_str[44] = "3LCOMP: mll ";
          cutFlowVector_str[45] = "3LCOMP: mTW  ";
          cutFlowVector_str[46] = "3LCOMP: dPhi_ISRI ";
          cutFlowVector_str[47] = "3LCOMP: R_ISR ";
          cutFlowVector_str[48] = "3LCOMP: p_ISRT ";
          cutFlowVector_str[49] = "3LCOMP: p_IT ";
          cutFlowVector_str[50] = "3LCOMP: pT_CM ";*/

          (j==43 && m_is3LInt && ((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign))) && m_lept1Pt>25. && m_lept2Pt>25. && m_lept3Pt>20. && signalBJets.size()==0 && signalJets.size()<4) ||

          (j==44 && m_is3LInt && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>25. && m_lept2Pt>25. && m_lept3Pt>20. && signalBJets.size()==0 && signalJets.size()<4 && m_mll>75. && m_mll<105.) ||

          (j==45 && m_is3LInt && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>25. && m_lept2Pt>25. && m_lept3Pt>20. && signalBJets.size()==0 && signalJets.size()<4 && m_mll>75. && m_mll<105. && m_mTW>100.) ||

          (j==46 && m_is3LInt && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>25. && m_lept2Pt>25. && m_lept3Pt>20. && signalBJets.size()==0 && signalJets.size()<4 && m_mll>75. && m_mll<105. && m_mTW>100. && m_dphiISRI>2.0) ||

          (j==47 && m_is3LInt && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>25. && m_lept2Pt>25. && m_lept3Pt>20. && signalBJets.size()==0 && signalJets.size()<4 && m_mll>75. && m_mll<105. && m_mTW>100. && m_dphiISRI>2.0 && m_RISR>0.55 && m_RISR<1.0) ||

          (j==48 && m_is3LInt && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>25. && m_lept2Pt>25. && m_lept3Pt>20. && signalBJets.size()==0 && signalJets.size()<4 && m_mll>75. && m_mll<105. && m_mTW>100. && m_dphiISRI>2.0 && m_RISR>0.55 && m_RISR<1.0 &&  m_PTISR>100.) ||

          (j==49 && m_is3LInt && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>25. && m_lept2Pt>25. && m_lept3Pt>20. && signalBJets.size()==0 && signalJets.size()<4 && m_mll>75. && m_mll<105. && m_mTW>100. && m_dphiISRI>2.0 && m_RISR>0.55 && m_RISR<1.0 &&  m_PTISR>100. && m_PTI>80.) ||

          (j==50 && m_is3LInt && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>25. && m_lept2Pt>25. && m_lept3Pt>20. && signalBJets.size()==0 && signalJets.size()<4 && m_mll>75. && m_mll<105. && m_mTW>100. && m_dphiISRI>2.0 && m_RISR>0.55 && m_RISR<1.0 &&  m_PTISR>100. && m_PTI>80. && m_PTCM<25.) ||

          /* cutFlowVector_str[51] = "3LINT: Preselection ";
          cutFlowVector_str[52] = "3LINT: mll ";
          cutFlowVector_str[53] = "3LINT: mTW  ";
          cutFlowVector_str[54] = "3LINT: m_HT4PP/m_H4PP  ";
          cutFlowVector_str[55] = "3LINT: HPb(1,1)/HPb(2,1) ";
          cutFlowVector_str[56] = "3LINT: m_H4PP ";
          cutFlowVector_str[57] = "3LINT: pT_PP/(pT_PP + HT_PP(3,1)) ";*/

          (j==51 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>50. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()<3) ||

          (j==52 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>50. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105.) ||

          (j==53 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>50. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>130.) ||

          (j==54 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>50. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>130. && m_HT4PP/m_H4PP > 0.8 ) ||

          (j==55 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>50. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>130. && m_HT4PP/m_H4PP > 0.8 && m_R_minH2P_minH3P>0.75) ||

          (j==56 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>50. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>130. && m_HT4PP/m_H4PP > 0.8 && m_R_minH2P_minH3P>0.75 && m_H4PP > 450. ) ||

          (j==57 && m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>50. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>130. && m_HT4PP/m_H4PP > 0.8 && m_R_minH2P_minH3P>0.75 && m_H4PP > 450. && m_RPT_HT4PP < 0.15)

          )cutFlowVector[j]++;
        }

        // Now apply the signal region cuts

        if(m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. && m_mjj>60. && m_mjj<100. && m_R_minH2P_minH3P>0.8 && m_RPT_HT5PP< 0.05 && m_dphiVP>0.3 && m_dphiVP<2.8 && m_H5PP>800.) _counters.at("2L2JHIGH").add_event(event);

        if(m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()>=2 && m_mll>80. && m_mll<100. && m_mjj>60. && m_mjj<100. && m_R_minH2P_minH3P>0.8 && m_RPT_HT5PP<0.05 && m_dphiVP>0.6 && m_dphiVP<2.6 && m_H5PP>600.) _counters.at("2L2JINT").add_event(event);


        if(m_is2Lep2Jet && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && signalJets.size()==2 && m_mll>80. && m_mll<100. && m_mjj>70. && m_mjj<90. && m_H2PP/m_H5PP>0.35 && m_H2PP/m_H5PP<0.6 && m_RPT_HT5PP<0.05 && m_minDphi>2.4 && m_H5PP>400.) _counters.at("2L2JLOW").add_event(event);

        if(m_is2L2JInt && m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign) && m_lept1Pt>25. && m_lept2Pt>25. && m_jet1Pt>30. && m_jet2Pt>30. && signalBJets.size()==0 && m_NjS==2 && m_NjISR>0 && m_MZ>80. && m_MZ<100. &&  m_MJ>50. && m_MJ<110. && m_dphiISRI>2.8 && m_RISR > 0.40 && m_RISR < 0.75 && m_PTISR > 180. && m_PTI > 100. && m_PTCM < 20.) _counters.at("2L2JCOMP").add_event(event);

        if(m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>60. && m_lept3Pt>40. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>150. && m_HT4PP/m_H4PP > 0.75 && m_R_minH2P_minH3P>0.8 && m_H4PP > 550. && m_RPT_HT4PP < 0.2) _counters.at("3LHIGH").add_event(event);

        if(m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>50. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()<3 && m_mll>75. && m_mll<105. && m_mTW>130. && m_HT4PP/m_H4PP > 0.8 && m_R_minH2P_minH3P>0.75 && m_H4PP > 450. && m_RPT_HT4PP < 0.15) _counters.at("3LINT").add_event(event);

        if(m_is3LInt && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>25. && m_lept2Pt>25. && m_lept3Pt>20. && signalBJets.size()==0 && signalJets.size()<4 && m_mll>75. && m_mll<105. && m_mTW>100. && m_dphiISRI>2.0 && m_RISR>0.55 && m_RISR<1.0 && m_PTISR>100. && m_PTI>80. && m_PTCM<25.) _counters.at("3LCOMP").add_event(event);

        if(m_is3Lep && (((m_lept1sign*m_lept2sign<0 && abs(m_lept1sign)==abs(m_lept2sign)) || (m_lept1sign*m_lept3sign<0 && abs(m_lept1sign)==abs(m_lept3sign)) || (m_lept2sign*m_lept3sign<0 && abs(m_lept2sign)==abs(m_lept3sign)))) && m_lept1Pt>60. && m_lept2Pt>40. && m_lept3Pt>30. && signalBJets.size()==0 && signalJets.size()==0 && m_mll>75. && m_mll<105. && m_mTW>100. && m_HT4PP/m_H4PP > 0.9 && m_H4PP > 250. && m_RPT_HT4PP < 0.05) _counters.at("3LLOW").add_event(event);

        return;

      } // end analyze method

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb* specificOther
          = dynamic_cast<const Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb*>(other);

        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }

        if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;

        for (int j=0; j<NCUTS; j++)
        {
          cutFlowVector[j] += specificOther->cutFlowVector[j];
          cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
        }

      }


      virtual void collect_results() {
/*
          double scale_by=1.;
          cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
          cout << "CUT FLOW: ATLAS 13 TeV 3 lep low mass RJ signal region "<<endl;
          cout << "------------------------------------------------------------------------------------------------------------------------------"<<endl;
          cout << right << setw(40) << "CUT" << setw(20) << "RAW" << setw(20) << "SCALED"
               << setw(20) << "%" << setw(20) << "clean adj RAW"<< setw(20) << "clean adj %" << endl;
          for (int j=0; j<NCUTS; j++) {
            cout << right << setw(40) << cutFlowVector_str[j].c_str() << setw(20)
                 << cutFlowVector[j] << setw(20) << cutFlowVector[j]*scale_by << setw(20)
                 << 100.*cutFlowVector[j]/cutFlowVector[0] << "%" << setw(20)
                 << cutFlowVector[j]*scale_by << setw(20) << 100.*cutFlowVector[j]/cutFlowVector[0]<< "%" << endl;
          }
          cout << "------------------------------------------------------------------------------------------------------------------------------ "<<endl;
*/

        add_result(SignalRegionData(_counters.at("2L2JHIGH"), 0,  {1.9, 0.8}));
        add_result(SignalRegionData(_counters.at("2L2JINT"),  1,  {2.4, 0.9}));
        add_result(SignalRegionData(_counters.at("2L2JLOW"),  19, {8.4, 5.8}));
        add_result(SignalRegionData(_counters.at("2L2JCOMP"), 11, {2.7, 2.7}));
        add_result(SignalRegionData(_counters.at("3LHIGH"),   2,  {1.1, 0.5}));
        add_result(SignalRegionData(_counters.at("3LINT"),    1,  {2.3, 0.5}));
        add_result(SignalRegionData(_counters.at("3LLOW"),    20, {10., 2.0}));
        add_result(SignalRegionData(_counters.at("3LCOMP"),   12, {3.9, 1.0}));

        return;
      }


    protected:
      void analysis_specific_reset() {

        for (auto& pair : _counters) { pair.second.reset(); }

        std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
      }

    }; // end class Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_RJ3L_lowmass_36invfb)


    //
    // Derived analysis class for the RJ3L_lowmass SRs
    //
    class Analysis_ATLAS_13TeV_RJ3L_2Lep2Jets_36invfb : public Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb {
    public:
      Analysis_ATLAS_13TeV_RJ3L_2Lep2Jets_36invfb() {
        set_analysis_name("ATLAS_13TeV_RJ3L_2Lep2Jets_36invfb");
      }
      virtual void collect_results() {
        add_result(SignalRegionData(_counters.at("2L2JHIGH"), 0,  {1.9, 0.8}));
        add_result(SignalRegionData(_counters.at("2L2JINT"),  1,  {2.4, 0.9}));
        add_result(SignalRegionData(_counters.at("2L2JLOW"),  19, {8.4, 5.8}));
        add_result(SignalRegionData(_counters.at("2L2JCOMP"), 11, {2.7, 2.7}));
      }

    };
    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_RJ3L_2Lep2Jets_36invfb)

    class Analysis_ATLAS_13TeV_RJ3L_3Lep_36invfb : public Analysis_ATLAS_13TeV_RJ3L_lowmass_36invfb {
    public:
      Analysis_ATLAS_13TeV_RJ3L_3Lep_36invfb() {
        set_analysis_name("ATLAS_13TeV_RJ3L_3Lep_36invfb");
      }
      virtual void collect_results() {
        add_result(SignalRegionData(_counters.at("3LHIGH"),   2,  {1.1, 0.5}));
        add_result(SignalRegionData(_counters.at("3LINT"),    1,  {2.3, 0.5}));
        add_result(SignalRegionData(_counters.at("3LLOW"),    20, {10., 2.0}));
        add_result(SignalRegionData(_counters.at("3LCOMP"),   12, {3.9, 1.0}));
      }

    };
    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_RJ3L_3Lep_36invfb)


  } // end namespace ColliderBit
} // end namespace Gambit

#endif
#endif
