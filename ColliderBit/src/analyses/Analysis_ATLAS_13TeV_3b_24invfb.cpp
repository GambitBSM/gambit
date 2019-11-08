///
///  \author Are Raklev
///  \date 2018 June
///
///  Based on the search presented in 1806.04030.
///  Only the low mass analysis is implemented here.
///  This analysis has overlapping exclusion and discovery signal regions,
///  the discovery regions are separated into a derived class.
///  *********************************************

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

// #define CHECK_CUTFLOW

using namespace std;

// TODO: See if we can get some further improvement by joining muons to b-jets

namespace Gambit {
  namespace ColliderBit {


    class Analysis_ATLAS_13TeV_3b_24invfb : public Analysis {

    protected:
      // Signal region map
      std::map<string,double> _numSR = {
        {"meff160_ETmiss0", 0.},        // Exclusion regions
        {"meff160_ETmiss20", 0.},
        {"meff200_ETmiss0", 0.},
        {"meff200_ETmiss20", 0.},
        {"meff200_ETmiss45", 0.},
        {"meff200_ETmiss70", 0.},
        {"meff260_ETmiss0", 0.},
        {"meff260_ETmiss20", 0.},
        {"meff260_ETmiss45", 0.},
        {"meff260_ETmiss70", 0.},
        {"meff260_ETmiss100", 0.},
        {"meff340_ETmiss0", 0.},
        {"meff340_ETmiss20", 0.},
        {"meff340_ETmiss45", 0.},
        {"meff340_ETmiss70", 0.},
        {"meff340_ETmiss100", 0.},
        {"meff340_ETmiss150", 0.},
        {"meff340_ETmiss200", 0.},
        {"meff440_ETmiss0", 0.},
        {"meff440_ETmiss20", 0.},
        {"meff440_ETmiss45", 0.},
        {"meff440_ETmiss70", 0.},
        {"meff440_ETmiss100", 0.},
        {"meff440_ETmiss150", 0.},
        {"meff440_ETmiss200", 0.},
        {"meff560_ETmiss0", 0.},
        {"meff560_ETmiss20", 0.},
        {"meff560_ETmiss45", 0.},
        {"meff560_ETmiss70", 0.},
        {"meff560_ETmiss100", 0.},
        {"meff560_ETmiss150", 0.},
        {"meff560_ETmiss200", 0.},
        {"meff700_ETmiss0", 0.},
        {"meff700_ETmiss20", 0.},
        {"meff700_ETmiss45", 0.},
        {"meff700_ETmiss70", 0.},
        {"meff700_ETmiss100", 0.},
        {"meff700_ETmiss150", 0.},
        {"meff700_ETmiss200", 0.},
        {"meff860_ETmiss0", 0.},
        {"meff860_ETmiss20", 0.},
        {"meff860_ETmiss45", 0.},
        {"meff860_ETmiss70", 0.},
        {"meff860_ETmiss100", 0.},
        {"meff860_ETmiss150", 0.},
        {"meff860_ETmiss200", 0.},
        {"low-SR-MET0meff440", 0.},       // Discovery regions
        {"low-SR-MET150meff440", 0.}
      };

    private:

      #ifdef CHECK_CUTFLOW
        // Cut-flow variables
        size_t NCUTS;
        vector<int> cutFlowVector;
        vector<string> cutFlowVector_str;
        vector<double> cutFlowVectorATLAS;
      #endif

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_3b_24invfb() {

        set_analysis_name("ATLAS_13TeV_3b_24invfb");
        set_luminosity(24.3);

        #ifdef CHECK_CUTFLOW
          NCUTS=9;
          for(size_t i=0;i<NCUTS;i++){
            cutFlowVector.push_back(0);
            cutFlowVectorATLAS.push_back(0);
            cutFlowVector_str.push_back("");
          }
        #endif
      }

      // The following section copied from Analysis_ATLAS_1LEPStop_20invfb.cpp
      void JetLeptonOverlapRemoval(vector<HEPUtils::Jet*> &jetvec, vector<HEPUtils::Particle*> &lepvec, double DeltaRMax) {
        //Routine to do jet-lepton check
        //Discards jets if they are within DeltaRMax of a lepton

        vector<HEPUtils::Jet*> Survivors;

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

      void LeptonJetOverlapRemoval(vector<HEPUtils::Particle*> &lepvec, vector<HEPUtils::Jet*> &jetvec) {
        //Routine to do lepton-jet check
        //Discards leptons if they are within dR of a jet as defined in analysis paper

        vector<HEPUtils::Particle*> Survivors;

        for(unsigned int itlep = 0; itlep < lepvec.size(); itlep++) {
          bool overlap = false;
          HEPUtils::P4 lepmom=lepvec.at(itlep)->mom();
          for(unsigned int itjet= 0; itjet < jetvec.size(); itjet++) {
            HEPUtils::P4 jetmom=jetvec.at(itjet)->mom();
            double dR;
            double DeltaRMax = std::min(0.4, 0.04 + 10 / lepmom.pT());
            dR=jetmom.deltaR_eta(lepmom);

            if(fabs(dR) <= DeltaRMax) overlap=true;
          }
          if(overlap) continue;
          Survivors.push_back(lepvec.at(itlep));
        }
        lepvec=Survivors;

        return;
      }


      void run(const HEPUtils::Event* event) {

        // Get the missing energy in the event
        double met = event->met();

        // Now define vectors of baseline objects, including:
        // - retrieval of electron, muon and jets from the event
        // - application of basic pT and eta cuts

        // Electrons
        vector<HEPUtils::Particle*> electrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 5.
              && fabs(electron->eta()) < 2.47)
            electrons.push_back(electron);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(electrons);

        // Muons
        vector<HEPUtils::Particle*> muons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 5.
              && fabs(muon->eta()) < 2.5)
            muons.push_back(muon);
        }

        // Apply muon efficiency
        ATLAS::applyMuonEff(muons);

        vector<HEPUtils::Jet*> candJets;
        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 25. && fabs(jet->eta()) < 2.5)
            candJets.push_back(jet);
        }

        // Overlap removal
        JetLeptonOverlapRemoval(candJets,electrons,0.2);
        LeptonJetOverlapRemoval(electrons,candJets);
        JetLeptonOverlapRemoval(candJets,muons,0.2);
        LeptonJetOverlapRemoval(muons,candJets);

   	    // Jets
        vector<HEPUtils::Jet*> bJets;
        vector<HEPUtils::Jet*> nonbJets;

        // Find b-jets
        double btag = 0.70; double cmisstag = 1/12.; double misstag = 1./381.;
        for (HEPUtils::Jet* jet : candJets) {
          // Tag
          if( jet->btag() && random_bool(btag) ) bJets.push_back(jet);
          // Misstag c-jet
          else if( jet->ctag() && random_bool(cmisstag) ) bJets.push_back(jet);
          // Misstag light jet
          else if( random_bool(misstag) ) bJets.push_back(jet);
          // Non b-jet
          else nonbJets.push_back(jet);
        }


        // Find veto leptons with pT > 20 GeV
        vector<HEPUtils::Particle*> vetoElectrons;
        for (HEPUtils::Particle* electron : electrons) {
          if (electron->pT() > 20.) vetoElectrons.push_back(electron);
        }
        vector<HEPUtils::Particle*> vetoMuons;
        for (HEPUtils::Particle* muon : muons) {
          if (muon->pT() > 20.) vetoMuons.push_back(muon);
        }

        // Restrict jets to pT > 40 GeV after overlap removal
        vector<HEPUtils::Jet*> bJets_survivors;
        for (HEPUtils::Jet* jet : bJets) {
          if(jet->pT() > 40.) bJets_survivors.push_back(jet);
        }
        vector<HEPUtils::Jet*> nonbJets_survivors;
        for (HEPUtils::Jet* jet : nonbJets) {
          if(jet->pT() > 40.) nonbJets_survivors.push_back(jet);
        }

        // Number of objects
        size_t nMuons=vetoMuons.size();
        size_t nElectrons=vetoElectrons.size();
        size_t nLeptons = nElectrons+nMuons;
        size_t nbJets = bJets_survivors.size();
        size_t nnonbJets = nonbJets_survivors.size();
        #ifdef CHECK_CUTFLOW
          size_t nJets = nbJets+nnonbJets;
        #endif

        // Effective mass (using the four jets used in Higgses)
        double meff = met;
        for(int i = 0; i < min(4,(int)nbJets); i++){
          meff += bJets_survivors.at(i)->pT();
        }

        // Find top candidates
        bool notop = true;
        // Outer loop over b-jets candidates for top
        for(size_t i = 0; i < nbJets; i++){
          // Central loop over b-tagged jets which may go into W
          for(size_t j = 0; j < nbJets && j != i; j++){
            // Inner loop over non b-jets for W
            for(size_t k = 0; k < nnonbJets; k++){
              double mW = (bJets_survivors.at(j)->mom()+nonbJets_survivors.at(k)->mom()).m();
              double mt = (bJets_survivors.at(i)->mom()+bJets_survivors.at(j)->mom()+nonbJets_survivors.at(k)->mom()).m();
              double XWt = sqrt( pow((mW-80.4)/(0.1*mW),2)+pow((mt-172.5)/(0.1*mt),2) );
              if(XWt < 1.8) notop = false;
            }
          }
          // Central loop over jets non b-tagged jets that may go into W
          for(size_t j = 0; j < nnonbJets; j++){
            // Inner loop over non b-jets for W
            for(size_t k = 0; k < nnonbJets && k != j; k++){
              double mW = (nonbJets_survivors.at(j)->mom()+nonbJets_survivors.at(k)->mom()).m();
              double mt = (bJets_survivors.at(i)->mom()+nonbJets_survivors.at(j)->mom()+nonbJets_survivors.at(k)->mom()).m();
              double XWt = sqrt( pow((mW-80.4)/(0.1*mW),2)+pow((mt-172.5)/(0.1*mt),2) );
              if(XWt < 1.8) notop = false;
           }
          }
        }

        // Find best Higgs (if any) candidates and calculate value of Xhh used in cuts
        bool higgs = false;
        double Dhhmin = 1000;
        double Xhh = 10;
        if(nbJets >= 4){
          // First find \Delta R criteria
          double h1DRjjMin = 0.;
          double h1DRjjMax = 1.00;
          double h2DRjjMin = 0.;
          double h2DRjjMax = 1.05;
          double mhh = (bJets_survivors.at(0)->mom()+bJets_survivors.at(1)->mom()+bJets_survivors.at(2)->mom()+bJets_survivors.at(3)->mom()).m();
          if(mhh < 1250.){
            h1DRjjMin = 360/mhh-0.50;
            h1DRjjMax = 655/mhh+0.50;
            h2DRjjMin = 235/mhh;
            h2DRjjMax = 875/mhh + 0.35;
          }
          // Loop over all b-jet combinations
          for(int i = 0; i < 3; i++){
            double DRlead = 10; double DRsubl = 10;
            double mlead = 0; double msubl = 0;
            int i1 = i; int i2=(i+1)%3; int i3=(i+2)%3; int i4=3;
            // Find leading and subleading higgs candidate
            double pT1 = bJets_survivors.at(i1)->mom().pT()+bJets_survivors.at(i2)->mom().pT();
            double pT2 = bJets_survivors.at(i3)->mom().pT()+bJets_survivors.at(i4)->mom().pT();
            // Find inter-jet distance and di-jet mass for leading and subleading candidate combinations
            if(pT1 > pT2){
              DRlead = bJets_survivors.at(i1)->mom().deltaR_eta(bJets_survivors.at(i2)->mom());
              DRsubl = bJets_survivors.at(i3)->mom().deltaR_eta(bJets_survivors.at(i4)->mom());
              mlead = (bJets_survivors.at(i1)->mom()+bJets_survivors.at(i2)->mom()).m();
              msubl = (bJets_survivors.at(i3)->mom()+bJets_survivors.at(i4)->mom()).m();
            }
            else{
              DRsubl = bJets_survivors.at(i1)->mom().deltaR_eta(bJets_survivors.at(i2)->mom());
              DRlead = bJets_survivors.at(i3)->mom().deltaR_eta(bJets_survivors.at(i4)->mom());
              mlead = (bJets_survivors.at(i3)->mom()+bJets_survivors.at(i4)->mom()).m();
              msubl = (bJets_survivors.at(i1)->mom()+bJets_survivors.at(i2)->mom()).m();
            }
            // Check if Higgs candidates are acceptable
            if(DRlead < h1DRjjMax && DRlead > h1DRjjMin && DRsubl < h2DRjjMax && DRsubl > h2DRjjMin ){
              higgs = true;
              double Dhh = abs(mlead-12./11.*msubl);
              if(Dhh < Dhhmin){
                Dhhmin = Dhh;
                Xhh = sqrt( pow((mlead-120.)/(0.1*mlead),2)+pow((msubl-110.)/(0.1*msubl),2) );
              }
            }
          }
        }

        #ifdef CHECK_CUTFLOW

          // Increment cutFlowVector elements
          cutFlowVector_str[0]  = "No cuts ";
          cutFlowVector_str[1]  = "Trigger, 4 jets ($p_T > 40$ GeV, 2 b-tags)";
          cutFlowVector_str[2]  = "$\\ge 4$ b-tags";
          cutFlowVector_str[3]  = "$\\ge 2$ Higgses ";
          cutFlowVector_str[4]  = "Lepton veto";
          cutFlowVector_str[5]  = "$X_{Wt} > 1.8$";
          cutFlowVector_str[6]  = "$X_{hh}^{SR} < 1.6$";
          cutFlowVector_str[7]  = "low-SR-MET0meff440";
          cutFlowVector_str[8]  = "low-SR-MET150meff440";

          // Cut flow from paper
          // Higgsino 130 GeV
          cutFlowVectorATLAS[0] = 169015.8;
          cutFlowVectorATLAS[1] =  11206.7;
          cutFlowVectorATLAS[2] =   1250.8;
          cutFlowVectorATLAS[3] =   1015.9;
          cutFlowVectorATLAS[4] =   1015.9;
          cutFlowVectorATLAS[5] =    961.9;
          cutFlowVectorATLAS[6] =    559.8;
          cutFlowVectorATLAS[7] =    217.4;
          cutFlowVectorATLAS[8] =      0.0;
          // // Higgsino 150 GeV
          // cutFlowVectorATLAS[0] = 93125.1;
          // cutFlowVectorATLAS[1] =  6630.9;
          // cutFlowVectorATLAS[2] =   687.8;
          // cutFlowVectorATLAS[3] =   558.6;
          // cutFlowVectorATLAS[4] =   558.6;
          // cutFlowVectorATLAS[5] =   489.4;
          // cutFlowVectorATLAS[6] =   266.5;
          // cutFlowVectorATLAS[7] =   112.5;
          // cutFlowVectorATLAS[8] =     1.8;
          // // Higgsino 200 GeV
          // cutFlowVectorATLAS[0] = 32455.5;
          // cutFlowVectorATLAS[1] =  2895.6;
          // cutFlowVectorATLAS[2] =   300.4;
          // cutFlowVectorATLAS[3] =   240.9;
          // cutFlowVectorATLAS[4] =   240.9;
          // cutFlowVectorATLAS[5] =   212.6;
          // cutFlowVectorATLAS[6] =   116.9;
          // cutFlowVectorATLAS[7] =    62.5;
          // cutFlowVectorATLAS[8] =     8.7;
          // // Higgsino 250 GeV
          // cutFlowVectorATLAS[0] = 14028.7;
          // cutFlowVectorATLAS[1] =  1454.7;
          // cutFlowVectorATLAS[2] =   163.0;
          // cutFlowVectorATLAS[3] =   126.4;
          // cutFlowVectorATLAS[4] =   126.1;
          // cutFlowVectorATLAS[5] =   108.4;
          // cutFlowVectorATLAS[6] =    53.4;
          // cutFlowVectorATLAS[7] =    37.0;
          // cutFlowVectorATLAS[8] =    14.2;
          // // Higgsino 300 GeV
          // cutFlowVectorATLAS[0] = 6922.0;
          // cutFlowVectorATLAS[1] =  877.3;
          // cutFlowVectorATLAS[2] =   90.6;
          // cutFlowVectorATLAS[3] =   70.1;
          // cutFlowVectorATLAS[4] =   70.0;
          // cutFlowVectorATLAS[5] =   63.3;
          // cutFlowVectorATLAS[6] =   34.0;
          // cutFlowVectorATLAS[7] =   26.7;
          // cutFlowVectorATLAS[8] =   14.6;
          // // Higgsino 400 GeV
          // cutFlowVectorATLAS[0] = 2156.2;
          // cutFlowVectorATLAS[1] =  366.2;
          // cutFlowVectorATLAS[2] =   41.7;
          // cutFlowVectorATLAS[3] =   32.3;
          // cutFlowVectorATLAS[4] =   31.9;
          // cutFlowVectorATLAS[5] =   28.1;
          // cutFlowVectorATLAS[6] =   14.4;
          // cutFlowVectorATLAS[7] =   13.6;
          // cutFlowVectorATLAS[8] =    9.6;
          // // Higgsino 600 GeV
          // cutFlowVectorATLAS[0] = 356.4;
          // cutFlowVectorATLAS[1] =  82.2;
          // cutFlowVectorATLAS[2] =   9.0;
          // cutFlowVectorATLAS[3] =   6.5;
          // cutFlowVectorATLAS[4] =   6.4;
          // cutFlowVectorATLAS[5] =   5.9;
          // cutFlowVectorATLAS[6] =   3.2;
          // cutFlowVectorATLAS[7] =   3.2;
          // cutFlowVectorATLAS[8] =   2.6;
          // // Higgsino 800 GeV
          // cutFlowVectorATLAS[0] =  84.1;
          // cutFlowVectorATLAS[1] =  22.4;
          // cutFlowVectorATLAS[2] =   2.2;
          // cutFlowVectorATLAS[3] =   1.6;
          // cutFlowVectorATLAS[4] =   1.6;
          // cutFlowVectorATLAS[5] =   1.5;
          // cutFlowVectorATLAS[6] =   0.8;
          // cutFlowVectorATLAS[7] =   0.8;
          // cutFlowVectorATLAS[8] =   0.7;

          // Apply cutflow
          for(size_t j=0;j<NCUTS;j++){
            if(
              (j==0) ||

              (j==1 && nJets > 3 && nbJets > 1) ||

              (j==2 && nbJets > 3) ||

              (j==3 && nbJets > 3 && higgs) ||

              (j==4 && nbJets > 3 && higgs && nLeptons == 0) ||

              (j==5 && nbJets > 3 && higgs && nLeptons == 0 && notop) ||

              (j==6 && nbJets > 3 && higgs && nLeptons == 0 && notop && Xhh < 1.6) ||

              (j==7 && nbJets > 3 && higgs && nLeptons == 0 && notop && Xhh < 1.6 && meff > 440.) ||

              (j==8 && nbJets > 3 && higgs && nLeptons == 0 && notop && Xhh < 1.6 && meff > 440. && met > 150.)

              ) cutFlowVector[j]++;
          }

        #endif

        // Now increment signal region variables
        // First exclusion regions
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 160. && meff < 200. && met < 20.) _numSR["meff160_ETmiss0"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 160. && meff < 200. && met > 20. && met < 45.) _numSR["meff160_ETmiss20"]++;

        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 200. && meff < 260. && met < 20.) _numSR["meff200_ETmiss0"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 200. && meff < 260. && met > 20. && met < 45.) _numSR["meff200_ETmiss20"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 200. && meff < 260. && met > 45. && met < 70.) _numSR["meff200_ETmiss45"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 200. && meff < 260. && met > 70. && met < 100.) _numSR["meff200_ETmiss70"]++;

        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 260. && meff < 340. && met < 20.) _numSR["meff260_ETmiss0"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 260. && meff < 340. && met > 20. && met < 45.) _numSR["meff260_ETmiss20"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 260. && meff < 340. && met > 45. && met < 70.) _numSR["meff260_ETmiss45"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 260. && meff < 340. && met > 70. && met < 100.) _numSR["meff260_ETmiss70"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 260. && meff < 340. && met > 100. && met < 150.) _numSR["meff260_ETmiss100"]++;

        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 340. && meff < 440. && met < 20.) _numSR["meff340_ETmiss0"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 340. && meff < 440. && met > 20. && met < 45.) _numSR["meff340_ETmiss20"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 340. && meff < 440. && met > 45. && met < 70.) _numSR["meff340_ETmiss45"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 340. && meff < 440. && met > 70. && met < 100.) _numSR["meff340_ETmiss70"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 340. && meff < 440. && met > 100. && met < 150.) _numSR["meff340_ETmiss100"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 340. && meff < 440. && met > 150. && met < 200.) _numSR["meff340_ETmiss150"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 340. && meff < 440. && met > 200.) _numSR["meff340_ETmiss200"]++;

        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 440. && meff < 560. && met < 20.) _numSR["meff440_ETmiss0"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 440. && meff < 560. && met > 20. && met < 45.) _numSR["meff440_ETmiss20"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 440. && meff < 560. && met > 45. && met < 70.) _numSR["meff440_ETmiss45"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 440. && meff < 560. && met > 70. && met < 100.) _numSR["meff440_ETmiss70"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 440. && meff < 560. && met > 100. && met < 150.) _numSR["meff440_ETmiss100"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 440. && meff < 560. && met > 150. && met < 200.) _numSR["meff440_ETmiss150"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 440. && meff < 560. && met > 200.) _numSR["meff440_ETmiss200"]++;

        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 560. && meff < 700. && met < 20.) _numSR["meff560_ETmiss0"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 560. && meff < 700. && met > 20. && met < 45.) _numSR["meff560_ETmiss20"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 560. && meff < 700. && met > 45. && met < 70.) _numSR["meff560_ETmiss45"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 560. && meff < 700. && met > 70. && met < 100.) _numSR["meff560_ETmiss70"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 560. && meff < 700. && met > 100. && met < 150.) _numSR["meff560_ETmiss100"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 560. && meff < 700. && met > 150. && met < 200.) _numSR["meff560_ETmiss150"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 560. && meff < 700. && met > 200.) _numSR["meff560_ETmiss200"]++;

        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 700. && meff < 860. && met < 20.) _numSR["meff700_ETmiss0"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 700. && meff < 860. && met > 20. && met < 45.) _numSR["meff700_ETmiss20"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 700. && meff < 860. && met > 45. && met < 70.) _numSR["meff700_ETmiss45"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 700. && meff < 860. && met > 70. && met < 100.) _numSR["meff700_ETmiss70"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 700. && meff < 860. && met > 100. && met < 150.) _numSR["meff700_ETmiss100"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 700. && meff < 860. && met > 150. && met < 200.) _numSR["meff700_ETmiss150"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 700. && meff < 860. && met > 200.) _numSR["meff700_ETmiss200"]++;

        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 860. && met < 20.) _numSR["meff860_ETmiss0"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 860. && met > 20. && met < 45.) _numSR["meff860_ETmiss20"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 860. && met > 45. && met < 70.) _numSR["meff860_ETmiss45"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 860. && met > 70. && met < 100.) _numSR["meff860_ETmiss70"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 860. && met > 100. && met < 150.) _numSR["meff860_ETmiss100"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 860. && met > 150. && met < 200.) _numSR["meff860_ETmiss150"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 860. && met > 200.) _numSR["meff860_ETmiss200"]++;

        // Discovery regions
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 440.) _numSR["low-SR-MET0meff440"]++;
        if(nbJets > 3 && nLeptons == 0 && notop && higgs && Xhh < 1.6 && meff > 440. && met > 150.) _numSR["low-SR-MET150meff440"]++;

        return;

      } // End of analyze

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_3b_24invfb* specificOther
          = dynamic_cast<const Analysis_ATLAS_13TeV_3b_24invfb*>(other);

        #ifdef CHECK_CUTFLOW
          if (NCUTS != specificOther->NCUTS) NCUTS = specificOther->NCUTS;
          for (size_t j=0; j<NCUTS; j++) {
            cutFlowVector[j] += specificOther->cutFlowVector[j];
            cutFlowVector_str[j] = specificOther->cutFlowVector_str[j];
          }
        #endif

        for (auto& el : _numSR)
        {
          el.second += specificOther->_numSR.at(el.first);
        }

      }


      virtual void collect_results() {

        #ifdef CHECK_CUTFLOW
          double L = 24.3;
          double xsec = 6955.; // 130 GeV
          // double xsec = 3830.; // 150 GeV
          // double xsec = 1336.; // 200 GeV
          // double xsec =  577.3; // 250 GeV
          // double xsec =  284.9; // 300 GeV
          // double xsec =   88.73; // 400 GeV
          // double xsec = 14.67; // 600 GeV
          // double xsec = 3.461; // 800 GeV

          cout << "DEBUG:" << endl;
          for (size_t i=0; i<NCUTS; i++)
          {
            double ATLAS_abs = cutFlowVectorATLAS[i];

            double eff = (double)cutFlowVector[i] / (double)cutFlowVector[0];
            //if(i > 0) eff *= 0.90; // Lower trigger efficiency for 130 GeV

            double GAMBIT_scaled = eff * xsec * L;

            double ratio = GAMBIT_scaled/ATLAS_abs;
            cout << "DEBUG 1: i: " << i << ":   " << setprecision(4) << ATLAS_abs << "\t" << GAMBIT_scaled << "\t" << "\t" << ratio << "\t\t" << cutFlowVector_str[i] << endl;
          }
          cout << "DEBUG:" << endl;
        #endif


        // Now fill a results object with the results for each SR
        // Only exclusion regions here
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("meff160_ETmiss0",    20., {_numSR["meff160_ETmiss0"], 0.}, {16.21, 0.11}));
        add_result(SignalRegionData("meff160_ETmiss20",    3., {_numSR["meff160_ETmiss20"], 0.}, {0.6503, 0.0747}));

        add_result(SignalRegionData("meff200_ETmiss0",  1503., {_numSR["meff200_ETmiss0"], 0.},  {1480., 26.}));
        add_result(SignalRegionData("meff200_ETmiss20", 1137., {_numSR["meff200_ETmiss20"], 0.}, {1088.,  7.}));
        add_result(SignalRegionData("meff200_ETmiss45",   65., {_numSR["meff200_ETmiss45"], 0.}, {58.05, 0.39}));
        add_result(SignalRegionData("meff200_ETmiss70",    0., {_numSR["meff200_ETmiss70"], 0.}, {0.2691, 0.0547}));

        add_result(SignalRegionData("meff260_ETmiss0",  1329., {_numSR["meff260_ETmiss0"], 0.},  {1297.,  8.}));
        add_result(SignalRegionData("meff260_ETmiss20", 2877., {_numSR["meff260_ETmiss20"], 0.}, {2860., 36.}));
        add_result(SignalRegionData("meff260_ETmiss45",  951., {_numSR["meff260_ETmiss45"], 0.}, { 991., 6.5}));
        add_result(SignalRegionData("meff260_ETmiss70",  150., {_numSR["meff260_ETmiss70"], 0.}, {149.4, 1.0}));
        add_result(SignalRegionData("meff260_ETmiss100",   2., {_numSR["meff260_ETmiss100"], 0.}, {2.024, 1.426}));

        add_result(SignalRegionData("meff340_ETmiss0",   373., {_numSR["meff340_ETmiss0"], 0.},  {390.1,  2.6}));
        add_result(SignalRegionData("meff340_ETmiss20",  873., {_numSR["meff340_ETmiss20"], 0.}, {884.6, 13.1}));
        add_result(SignalRegionData("meff340_ETmiss45",  444., {_numSR["meff340_ETmiss45"], 0.}, {472.6,  3.0}));
        add_result(SignalRegionData("meff340_ETmiss70",  164., {_numSR["meff340_ETmiss70"], 0.}, {171.1,  1.1}));
        add_result(SignalRegionData("meff340_ETmiss100",  40., {_numSR["meff340_ETmiss100"], 0.}, {36.24, 0.24}));
        add_result(SignalRegionData("meff340_ETmiss150",   3., {_numSR["meff340_ETmiss150"], 0.}, {1.457, 0.111}));
        add_result(SignalRegionData("meff340_ETmiss200",   0., {_numSR["meff340_ETmiss200"], 0.}, {0.006531, 0.004409}));

        add_result(SignalRegionData("meff440_ETmiss0",   121., {_numSR["meff440_ETmiss0"], 0.},  {130.3,  0.8}));
        add_result(SignalRegionData("meff440_ETmiss20",  304., {_numSR["meff440_ETmiss20"], 0.}, {310.8,  9.5}));
        add_result(SignalRegionData("meff440_ETmiss45",  170., {_numSR["meff440_ETmiss45"], 0.}, {176.6,  1.2}));
        add_result(SignalRegionData("meff440_ETmiss70",   62., {_numSR["meff440_ETmiss70"], 0.}, { 65.1,  1.1}));
        add_result(SignalRegionData("meff440_ETmiss100",  31., {_numSR["meff440_ETmiss100"], 0.}, {22.16, 6.03}));
        add_result(SignalRegionData("meff440_ETmiss150",   3., {_numSR["meff440_ETmiss150"], 0.}, {3.895, 0.14}));
        add_result(SignalRegionData("meff440_ETmiss200",   1., {_numSR["meff440_ETmiss200"], 0.}, {0.4816, 0.0551}));

        add_result(SignalRegionData("meff560_ETmiss0",    40., {_numSR["meff560_ETmiss0"], 0.},  { 43.46,   0.29}));
        add_result(SignalRegionData("meff560_ETmiss20",   95., {_numSR["meff560_ETmiss20"], 0.}, {102.6,    6.6}));
        add_result(SignalRegionData("meff560_ETmiss45",   75., {_numSR["meff560_ETmiss45"], 0.}, { 68.03,   0.45}));
        add_result(SignalRegionData("meff560_ETmiss70",   20., {_numSR["meff560_ETmiss70"], 0.}, { 30.72,   0.2}));
        add_result(SignalRegionData("meff560_ETmiss100",  15., {_numSR["meff560_ETmiss100"], 0.},{ 14.13,   3.19}));
        add_result(SignalRegionData("meff560_ETmiss150",   2., {_numSR["meff560_ETmiss150"], 0.},{  2.358,  1.02}));
        add_result(SignalRegionData("meff560_ETmiss200",   2., {_numSR["meff560_ETmiss200"], 0.},{  1.08,   0.23}));

        add_result(SignalRegionData("meff700_ETmiss0",    17., {_numSR["meff700_ETmiss0"], 0.},  { 13.56,   0.09}));
        add_result(SignalRegionData("meff700_ETmiss20",   30., {_numSR["meff700_ETmiss20"], 0.}, { 32.67,   3.39}));
        add_result(SignalRegionData("meff700_ETmiss45",   22., {_numSR["meff700_ETmiss45"], 0.}, { 23.78,   0.15}));
        add_result(SignalRegionData("meff700_ETmiss70",   12., {_numSR["meff700_ETmiss70"], 0.}, { 12.47,   0.08}));
        add_result(SignalRegionData("meff700_ETmiss100",   6., {_numSR["meff700_ETmiss100"], 0.},{  5.549,  0.873}));
        add_result(SignalRegionData("meff700_ETmiss150",   2., {_numSR["meff700_ETmiss150"], 0.},{  1.728,  0.879}));
        add_result(SignalRegionData("meff700_ETmiss200",   2., {_numSR["meff700_ETmiss200"], 0.},{  0.8551, 0.1211}));

        add_result(SignalRegionData("meff860_ETmiss0",     2., {_numSR["meff860_ETmiss0"], 0.},  {  2.816,   0.246}));
        add_result(SignalRegionData("meff860_ETmiss20",    7., {_numSR["meff860_ETmiss20"], 0.}, {  7.766,   2.114}));
        add_result(SignalRegionData("meff860_ETmiss45",   10., {_numSR["meff860_ETmiss45"], 0.}, {  8.968,   2.332}));
        add_result(SignalRegionData("meff860_ETmiss70",    5., {_numSR["meff860_ETmiss70"], 0.}, {  4.297,   0.335}));
        add_result(SignalRegionData("meff860_ETmiss100",   2., {_numSR["meff860_ETmiss100"], 0.},{  2.785,   0.29}));
        add_result(SignalRegionData("meff860_ETmiss150",   4., {_numSR["meff860_ETmiss150"], 0.},{  0.9345,  0.2345}));
        add_result(SignalRegionData("meff860_ETmiss200",   1., {_numSR["meff860_ETmiss200"], 0.},{  0.4297,  0.0719}));

        return;
      }

      void analysis_specific_reset() {
        // Clear signal regions
        for (auto& el : _numSR) { el.second = 0.;}

        #ifdef CHECK_CUTFLOW
          // Clear cut flow vector
          std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
        #endif
      }



    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_3b_24invfb)


    //
    // Class for collecting results for discovery regions as a derived class
    //

    class Analysis_ATLAS_13TeV_3b_discoverySR_24invfb : public Analysis_ATLAS_13TeV_3b_24invfb {

    public:
      Analysis_ATLAS_13TeV_3b_discoverySR_24invfb() {
        set_analysis_name("ATLAS_13TeV_3b_discoverySR_24invfb");
      }

      virtual void collect_results() {
        // add_result(SignalRegionData("SR label", n_obs, {s, s_sys}, {b, b_sys}));
        add_result(SignalRegionData("low-SR-MET0meff440", 1063., {_numSR["low-SR-MET0meff440"], 0.}, {1100., 25.}));
        add_result(SignalRegionData("low-SR-MET150meff440", 17., {_numSR["low-SR-MET150meff440"], 0.}, {12., 8.}));
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_3b_discoverySR_24invfb)

  }
}
