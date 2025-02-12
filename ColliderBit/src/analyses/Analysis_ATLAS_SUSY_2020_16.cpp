///
///  \author Are Raklev
///  \date 2024 February
///
///  Based on SUSY-2020-16 presented in 2401.14922.
///  Only the low mass analysis is currently implemented here.
///  The high mass analysis uses a BDT and reclusters jets to R=0.8.
///  *********************************************

#include <vector>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

// #define CHECK_CUTFLOW

using namespace std;

namespace Gambit {
  namespace ColliderBit {


    class Analysis_ATLAS_SUSY_2020_16 : public Analysis {

    protected:

    private:

      #ifdef CHECK_CUTFLOW
        // Cut-flow variables
        size_t NCUTS;
        vector<int> cutFlowVector;
        vector<string> cutFlowVector_str;
        vector<double> cutFlowVectorATLAS;
      #endif

      // Signal region bin edges
      vector<int> year_bins = {2016, 2017, 2018};
      vector<int> ETmiss_bins = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, INT_MAX};
      vector<int> meff_bins = {160, 200, 260, 340, 440, 560, 700, 860, INT_MAX};
      
      // b-jet trigger availability
      double trigger_availability = 126.0/139.;
      
      // Data fractions per year
      double f2016 = 24.6/126.0;
      double f2017 = 43.7/126.0;
      //double f2018 = 57.7/126.0;

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_SUSY_2020_16() {

        // Signal region map
        // Exclusion regions
        for(auto & year : year_bins){
          for(unsigned int i = 0; i < meff_bins.size() - 1; ++i){
            for(unsigned int j = 0; j < ETmiss_bins.size() - 1; ++j){
              string SR_name = to_string(year) + "_ETmiss" + to_string(ETmiss_bins[j]) + "_meff" + to_string(meff_bins[i]);
              _counters[SR_name] = EventCounter(SR_name);
            }
          }
        }

        // Discovery regions
        _counters["SR_LM_150"] = EventCounter("SR_LM_150");
        _counters["SR_LM_300"] = EventCounter("SR_LM_300");

        set_analysis_name("ATLAS_SUSY_2020_16");
        set_luminosity(139.);

        #ifdef CHECK_CUTFLOW
          NCUTS=11;
          for(size_t i=0;i<NCUTS;i++){
            cutFlowVector.push_back(0);
            cutFlowVectorATLAS.push_back(0);
            cutFlowVector_str.push_back("");
          }
        #endif
      }

      // The following section copied from Analysis_ATLAS_1LEPStop_20invfb.cpp
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

      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec) {
        //Routine to do lepton-jet check
        //Discards leptons if they are within dR of a jet as defined in analysis paper

        vector<const HEPUtils::Particle*> Survivors;

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
        vector<const HEPUtils::Particle*> electrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 7.
              && fabs(electron->eta()) < 2.47)
            electrons.push_back(electron);
        }

        // Apply electron efficiency
        applyEfficiency(electrons, ATLAS::eff2DEl.at("Generic"));

        // Muons
        vector<const HEPUtils::Particle*> muons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 6.
              && fabs(muon->eta()) < 2.5)
            muons.push_back(muon);
        }

        // Apply muon efficiency
        applyEfficiency(muons, ATLAS::eff2DMu.at("Generic"));

        // Candidate jets
        vector<const HEPUtils::Jet*> candJets;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04")) {
          if (jet->pT() > 40. && fabs(jet->eta()) < 2.8)
            candJets.push_back(jet);
        }

        // Overlap removal
        JetLeptonOverlapRemoval(candJets,electrons,0.2);
        LeptonJetOverlapRemoval(electrons,candJets);
        JetLeptonOverlapRemoval(candJets,muons,0.2);
        LeptonJetOverlapRemoval(muons,candJets);

        // Jets
        vector<const HEPUtils::Jet*> bJets;
        vector<const HEPUtils::Jet*> nonbJets;

        // Find b-jets
        double btag = 0.77; double cmisstag = 1/4.9; double misstag = 1./130.;
        for (const HEPUtils::Jet* jet : candJets) {
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
        vector<const HEPUtils::Particle*> vetoElectrons;
        for (const HEPUtils::Particle* electron : electrons) {
          if (electron->pT() > 20.) vetoElectrons.push_back(electron);
        }
        vector<const HEPUtils::Particle*> vetoMuons;
        for (const HEPUtils::Particle* muon : muons) {
          if (muon->pT() > 20.) vetoMuons.push_back(muon);
        }

        // Restrict jets to pT > 40 GeV after overlap removal
        vector<const HEPUtils::Jet*> bJets_survivors;
        for (const HEPUtils::Jet* jet : bJets) {
          if(jet->pT() > 40.) bJets_survivors.push_back(jet);
        }
        vector<const HEPUtils::Jet*> nonbJets_survivors;
        for (const HEPUtils::Jet* jet : nonbJets) {
          if(jet->pT() > 40.) nonbJets_survivors.push_back(jet);
        }

        // Number of objects
        size_t nMuons=vetoMuons.size();
        size_t nElectrons=vetoElectrons.size();
        size_t nLeptons = nElectrons+nMuons;
        size_t nbJets = bJets_survivors.size();
        size_t nnonbJets = nonbJets_survivors.size();

        // Effective mass (using the four b-jets used in Higgses)
        double meff = met;
        for(int i = 0; i < min(4,(int)nbJets); i++){
          meff += bJets_survivors.at(i)->pT();
        }

        // Find top candidates
        double XWt = 100;
        // Outer loop over b-jets candidates for top
        for(int i = 0; i < min(4,(int)nbJets); i++){
          // Central loop over b-tagged jets which may go into W
          for(int j = 0; j < min(4,(int)nbJets) && j != i; j++){
            // Inner loop over non b-jets for W
            for(size_t k = 0; k < nnonbJets; k++){
              double mW = (bJets_survivors.at(j)->mom()+nonbJets_survivors.at(k)->mom()).m();
              double mt = (bJets_survivors.at(i)->mom()+bJets_survivors.at(j)->mom()+nonbJets_survivors.at(k)->mom()).m();
              double XWt_current = sqrt( pow((mW-80.4)/(0.1*mW),2)+pow((mt-172.5)/(0.1*mt),2) );
              if(XWt_current < XWt) XWt = XWt_current;
            }
          }
          // Central loop over jets non b-tagged jets that may go into W
          for(size_t j = 0; j < nnonbJets; j++){
            // Inner loop over non b-jets for W
            for(size_t k = 0; k < nnonbJets && k != j; k++){
              double mW = (nonbJets_survivors.at(j)->mom()+nonbJets_survivors.at(k)->mom()).m();
              double mt = (bJets_survivors.at(i)->mom()+nonbJets_survivors.at(j)->mom()+nonbJets_survivors.at(k)->mom()).m();
              double XWt_current = sqrt( pow((mW-80.4)/(0.1*mW),2)+pow((mt-172.5)/(0.1*mt),2) );
              if(XWt_current < XWt) XWt = XWt_current;
            }
          }
        }

        // Find best Higgs (if any) candidates and calculate value of Xhh used in cuts
        double DRmax = 100;
        double Xhh = 100;
        HEPUtils::P4 Higgs1, Higgs2;  // The two Higgs candidate four vectors
        if(nbJets >= 4){
          // Loop over all b-jet combinations to find the one with smallest DRmax
          for(int i = 0; i < 3; i++){
            // Magic indexing which will give all possible pairs
            int i1 = i; int i2=(i+1)%3; int i3=(i+2)%3; int i4=3;
            // Find leading and subleading Higgs candidate
            double pT1 = (bJets_survivors.at(i1)->mom()+bJets_survivors.at(i2)->mom()).pT();
            double DR1 = bJets_survivors.at(i1)->mom().deltaR_eta(bJets_survivors.at(i2)->mom());
            double pT2 = (bJets_survivors.at(i3)->mom()+bJets_survivors.at(i4)->mom()).pT();
            double DR2 = bJets_survivors.at(i3)->mom().deltaR_eta(bJets_survivors.at(i4)->mom());
            // Choose this pair if better
            if(max(DR1,DR2) < DRmax){
              DRmax = max(DR1,DR2);
              if(pT1 > pT2){
                Higgs1 = bJets_survivors.at(i1)->mom()+bJets_survivors.at(i2)->mom();
                Higgs2 = bJets_survivors.at(i3)->mom()+bJets_survivors.at(i4)->mom();
              }
              else{
                Higgs1 = bJets_survivors.at(i3)->mom()+bJets_survivors.at(i4)->mom();
                Higgs2 = bJets_survivors.at(i1)->mom()+bJets_survivors.at(i2)->mom();
              }
            }
          }
          // Calculate the cut value
          double mlead = Higgs1.m();
          double msubl = Higgs2.m();
          Xhh = sqrt( pow((mlead-120.)/(0.1*mlead),2)+pow((msubl-110.)/(0.1*msubl),2) );
        }
        
        // b-trigger availability
        bool btrigger = random_bool(trigger_availability);
        
        #ifdef CHECK_CUTFLOW

          // Increment cutFlowVector elements
          cutFlowVector_str[0]  = "Total";
          cutFlowVector_str[1]  = "Pre-selection skim";
          cutFlowVector_str[2]  = "$hh2$ evnets";
          cutFlowVector_str[3]  = "$b$-jet trigger available";
          cutFlowVector_str[4]  = "Trigger";
          cutFlowVector_str[5]  = "$\\ge 4$ $b$-jets";
          cutFlowVector_str[6]  = "Lepton veto";
          cutFlowVector_str[7]  = "$X_{Wt} > 1.8$";
          cutFlowVector_str[8]  = "$X_{hh}^{SR} < 1.6$";
          cutFlowVector_str[9]  = "SR_LM_150";
          cutFlowVector_str[10] = "SR_LM_300";

          // Cut flow from paper
          // Higgsino 130 GeV
          cutFlowVectorATLAS[0] = 966801;
          cutFlowVectorATLAS[1] = 160991;
          cutFlowVectorATLAS[2] =  70293.3;
          cutFlowVectorATLAS[3] =  63604.5;
          cutFlowVectorATLAS[4] =  38222.2;
          cutFlowVectorATLAS[5] =   5197.09;
          cutFlowVectorATLAS[6] =   4982.43;
          cutFlowVectorATLAS[7] =   4586.51;
          cutFlowVectorATLAS[8] =   1880.02;
          cutFlowVectorATLAS[9] =    422.866;
          cutFlowVectorATLAS[10] =     2.25276;
          // // Higgsino 200 GeV
          cutFlowVectorATLAS[0] = 185651;
          cutFlowVectorATLAS[1] =  65105.87;
          cutFlowVectorATLAS[2] =  29148.68;
          cutFlowVectorATLAS[3] =  26471.40;
          cutFlowVectorATLAS[4] =  13170.29;
          cutFlowVectorATLAS[5] =   1609.17;
          cutFlowVectorATLAS[6] =   1535.25;
          cutFlowVectorATLAS[7] =   1378.63;
          cutFlowVectorATLAS[8] =    525.32;
          cutFlowVectorATLAS[9] =    200.97;
          cutFlowVectorATLAS[10] =    74.83;
          // // Higgsino 500 GeV
          cutFlowVectorATLAS[0] =  4703.58;
          cutFlowVectorATLAS[1] =  4082.65;
          cutFlowVectorATLAS[2] =  1746.35;
          cutFlowVectorATLAS[3] =  1579.91;
          cutFlowVectorATLAS[4] =   677.12;
          cutFlowVectorATLAS[5] =   115.77;
          cutFlowVectorATLAS[6] =   107.67;
          cutFlowVectorATLAS[7] =    97.10;
          cutFlowVectorATLAS[8] =    43.02;
          cutFlowVectorATLAS[9] =    39.29;
          cutFlowVectorATLAS[10] =   32.83;
          // // Higgsino 1100 GeV
//          cutFlowVectorATLAS[0] = 74.7827;
//          cutFlowVectorATLAS[1] = 59.2854;
//          cutFlowVectorATLAS[2] = 26.6107;
//          cutFlowVectorATLAS[3] = 24.1126;
//          cutFlowVectorATLAS[4] = 11.6798;
//          cutFlowVectorATLAS[5] =  1.96688;
//          cutFlowVectorATLAS[6] =  1.79592;
//          cutFlowVectorATLAS[7] =  1.67386;
//          cutFlowVectorATLAS[8] =  0.780557;
//          cutFlowVectorATLAS[9] =  0.775711;
//          cutFlowVectorATLAS[10] = 0.713743;
        
          // Apply cutflow
          for(size_t j=0;j<NCUTS;j++){
            if(
              (j==0) ||

              (j==1) ||

              (j==2) ||

              (j==3 && btrigger) ||

              (j==4 && btrigger) ||

              (j==5 && btrigger && nbJets > 3) ||

              (j==6 && btrigger && nbJets > 3 && nLeptons == 0) ||

              (j==7 && btrigger && nbJets > 3 && nLeptons == 0 && XWt > 1.8) ||

              (j==8 && btrigger && nbJets > 3 && nLeptons == 0 && XWt > 1.8 && Xhh < 1.6) ||
               
              (j==9 && btrigger && nbJets > 3 && nLeptons == 0 && XWt > 1.8 && Xhh < 1.6 && meff > 560. && met > 20.) ||
               
              (j==10 && btrigger && nbJets > 3 && nLeptons == 0 && XWt > 1.8 && Xhh < 1.6 && meff > 340. && met > 150.)

              ) cutFlowVector[j]++;
          }

        #endif

        // Now increment signal region variables
        // Common selection criteria
        if(btrigger && nbJets >= 4 && nLeptons == 0 && XWt > 1.8 && Xhh < 1.6){
          
          // Which year to bin in (SRs are divided by year)
          int year;
          double r = Random::draw();
          if(r < f2016) year = 2016;
          else if(r < f2016+f2017) year = 2017;
          else year = 2018;
          
          // First exclusion regions
          for(unsigned int i = 0; i < meff_bins.size()-1; i++){
            if( meff > meff_bins[i] && meff < meff_bins[i+1] ){
              for(unsigned int j = 0; j < ETmiss_bins.size()-1; j++){
                if( met > ETmiss_bins[j] && met < ETmiss_bins[j+1] ) {
                  string SR_name = to_string(year)+"_ETmiss"+to_string(ETmiss_bins[j])+"_meff"+to_string(meff_bins[i]);
                  _counters.at(SR_name).add_event(event);
                }
              }
            }
          }
          
          // Discovery regions
          if(met  > 20  && meff > 560.) _counters.at("SR_LM_150").add_event(event);
          if(met > 150. && meff > 340.) _counters.at("SR_LM_300").add_event(event);
        }
           
        return;
      } // End of analyze


      virtual void collect_results() {

        #ifdef CHECK_CUTFLOW
          double L = 139.;
          //double xsec = 6955.; // 130 GeV
          //double xsec = 1335.62; // 200 GeV
          double xsec = 33.8387; // 500 GeV
          //double xsec = 0.538; // 1100 GeV

          cout << "DEBUG:" << endl;
          for (size_t i=0; i<NCUTS; i++)
          {
            double ATLAS_abs = cutFlowVectorATLAS[i];

            double eff = (double)cutFlowVector[i] / (double)cutFlowVector[0];

            double GAMBIT_scaled = eff * xsec * L;

            double ratio = GAMBIT_scaled/ATLAS_abs;
            cout << "DEBUG 1: i: " << i << ":   " << setprecision(4) << ATLAS_abs << "\t\t\t" << GAMBIT_scaled << "\t\t\t" << ratio << "\t\t\t" << cutFlowVector[i] << "\t\t\t" << cutFlowVector_str[i] << endl;
          }
          cout << "DEBUG:" << endl;
        #endif


        // Now fill a results object with the results for each SR
        // Only exclusion regions here
        
        add_result(SignalRegionData(_counters.at("2016_ETmiss0_meff160"),    7., {    6.26,  1.08 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss0_meff200"),  425., {  441.28,  7.47 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss0_meff260"),  818., {  842.96, 11.3  }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss0_meff340"),  349., {  380.43,  6.9  }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss0_meff440"),  139., {  134.49,  3.43 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss0_meff560"),   44., {   44.8 ,  1.73 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss0_meff700"),   15., {   13.07,  0.9  }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss0_meff860"),    3., {    3.25,  1.35 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss20_meff160"),   1., {    0.25,  0.36 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss20_meff200"), 311., {  327.72,  5.87 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss20_meff260"),1302., { 1287.74, 10.98 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss20_meff340"), 752., {  739.34,  9.81 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss20_meff440"), 248., {  269.81,  5.8  }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss20_meff560"),  80., {   92.56,  2.78 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss20_meff700"),  30., {   28.56,  1.41 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss20_meff860"),  11., {    7.36,  0.7  }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss40_meff160"),   0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss40_meff200"),  36., {   48.19,  1.34 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss40_meff260"), 577., {  581.73, 14.97 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss40_meff340"), 496., {  503.15,  7.03 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss40_meff440"), 199., {  204.62, 10.83 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss40_meff560"),  58., {   78.36,  2.43 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss40_meff700"),  21., {   25.21,  1.24 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss40_meff860"),   8., {    8.48,  2.74 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss60_meff160"),   0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss60_meff200"),   2., {    1.82,  0.14 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss60_meff260"), 149., {  140.93,  3.31 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss60_meff340"), 202., {  212.4 ,  9.28 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss60_meff440"),  97., {  106.18,  3.25 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss60_meff560"),  39., {   45.23,  1.82 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss60_meff700"),  14., {   17.6 ,  2.12 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss60_meff860"),  11., {    6.46,  2.24 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss80_meff160"),   0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss80_meff200"),   0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss80_meff260"),  23., {   22.77,  3.1  }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss80_meff340"),  66., {   68.99,  1.99 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss80_meff440"),  48., {   43.58,  6.7  }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss80_meff560"),  22., {   21.63,  2.49 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss80_meff700"),   4., {    9.48,  1.73 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss80_meff860"),   5., {    3.77,  1.92 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss100_meff160"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss100_meff200"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss100_meff260"),  2., {    2.51,  1.11 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss100_meff340"), 17., {   18.98,  0.72 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss100_meff440"), 15., {   16.29,  0.89 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss100_meff560"), 11., {    9.27,  1.33 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss100_meff700"),  5., {    4.09,  2.17 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss100_meff860"),  1., {    2.08,  0.62 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss120_meff160"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss120_meff200"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss120_meff260"),  0., {    0.2 ,  0.04 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss120_meff340"),  4., {    4.98,  1.49 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss120_meff440"),  5., {    5.84,  1.2  }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss120_meff560"),  2., {    3.83,  0.39 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss120_meff700"),  5., {    2.32,  0.55 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss120_meff860"),  1., {    0.97,  0.18 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss140_meff160"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss140_meff200"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss140_meff260"),  0., {    0.01,  0.01 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss140_meff340"),  2., {    1.42,  0.81 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss140_meff440"),  3., {    2.97,  0.24 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss140_meff560"),  5., {    2.29,  1.49 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss140_meff700"),  3., {    1.22,  0.56 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss140_meff860"),  1., {    0.8 ,  0.19 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss160_meff160"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss160_meff200"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss160_meff260"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss160_meff340"),  1., {    0.27,  0.06 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss160_meff440"),  0., {    1.43,  0.15 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss160_meff560"),  0., {    1.09,  0.18 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss160_meff700"),  1., {    0.74,  0.64 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss160_meff860"),  1., {    0.43,  0.12 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss180_meff160"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss180_meff200"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss180_meff260"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss180_meff340"),  0., {    0.09,  0.03 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss180_meff440"),  0., {    0.69,  0.11 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss180_meff560"),  0., {    0.66,  0.37 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss180_meff700"),  0., {    0.31,  0.21 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss180_meff860"),  2., {    0.27,  0.62 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss200_meff160"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss200_meff200"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss200_meff260"),  0., {    0   ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss200_meff340"),  0., {    0.0 ,  0    }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss200_meff440"),  1., {    0.64,  0.67 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss200_meff560"),  1., {    1.25,  1.1  }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss200_meff700"),  2., {    1.25,  0.22 }));
        add_result(SignalRegionData(_counters.at("2016_ETmiss200_meff860"),  2., {    1.05,  0.2  }));
        
        add_result(SignalRegionData(_counters.at("2017_ETmiss0_meff160"),     6., {   3.85,  0.30 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss0_meff200"),   395., { 405.80,  8.44 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss0_meff260"),   946., { 971.72, 13.83 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss0_meff340"),   474., { 510.50, 22.39 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss0_meff440"),   150., { 175.17,  8.67 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss0_meff560"),    45., {  58.56,  2.21 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss0_meff700"),    22., {  18.88,  1.16 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss0_meff860"),     5., {   6.14,  0.72 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss20_meff160"),    0., {   0.19,  0.20 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss20_meff200"),  281., { 309.25,  6.28 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss20_meff260"), 1496., {1538.18, 17.89 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss20_meff340"),  947., {1033.39, 22.84 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss20_meff440"),  388., { 380.75, 12.13 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss20_meff560"),  118., { 126.60,  3.85 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss20_meff700"),   34., {  39.47,  1.89 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss20_meff860"),   12., {  15.78,  1.35 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss40_meff160"),    0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss40_meff200"),   33., {  47.12,  1.43 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss40_meff260"),  742., { 752.14, 29.99 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss40_meff340"),  718., { 749.81,  9.58 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss40_meff440"),  308., { 311.87,  6.61 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss40_meff560"),  116., { 113.04,  3.38 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss40_meff700"),   31., {  39.23,  4.37 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss40_meff860"),   15., {  15.41,  1.21 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss60_meff160"),    0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss60_meff200"),    1., {   2.06,  0.19 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss60_meff260"),  208., { 207.44,  4.17 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss60_meff340"),  348., { 353.00,  6.42 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss60_meff440"),  159., { 172.17, 12.08 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss60_meff560"),   57., {  69.96,  2.53 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss60_meff700"),   23., {  27.11,  1.51 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss60_meff860"),   21., {  10.82,  2.56 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss80_meff160"),    0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss80_meff200"),    0., {   0.02,  0.01 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss80_meff260"),   38., {  40.23,  1.26 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss80_meff340"),  103., { 123.45,  5.74 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss80_meff440"),   79., {  77.26,  4.55 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss80_meff560"),   36., {  34.42,  4.07 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss80_meff700"),   14., {  13.57,  0.99 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss80_meff860"),   10., {   6.12,  0.56 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss100_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss100_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss100_meff260"),   5., {   5.05,  0.32 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss100_meff340"),  41., {  41.30,  2.99 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss100_meff440"),  26., {  31.82,  1.40 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss100_meff560"),  14., {  17.89,  3.09 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss100_meff700"),   9., {   7.50,  1.54 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss100_meff860"),  10., {   4.02,  0.56 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss120_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss120_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss120_meff260"),   0., {   0.44,  0.09 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss120_meff340"),  18., {  13.19,  0.65 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss120_meff440"),   8., {  15.52,  0.89 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss120_meff560"),   9., {   8.60,  2.38 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss120_meff700"),   5., {   3.69,  0.44 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss120_meff860"),   2., {   2.51,  1.58 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss140_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss140_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss140_meff260"),   0., {   0.02,  0.02 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss140_meff340"),   2., {   3.52,  0.33 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss140_meff440"),  10., {   6.34,  0.50 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss140_meff560"),   5., {   4.19,  0.44 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss140_meff700"),   2., {   1.69,  0.26 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss140_meff860"),   1., {   1.54,  0.34 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss160_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss160_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss160_meff260"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss160_meff340"),   4., {   0.85,  0.14 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss160_meff440"),   0., {   2.96,  0.35 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss160_meff560"),   4., {   1.88,  0.25 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss160_meff700"),   1., {   0.95,  0.23 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss160_meff860"),   3., {   0.71,  0.40 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss180_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss180_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss180_meff260"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss180_meff340"),   0., {   0.20,  0.21 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss180_meff440"),   1., {   1.25,  0.20 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss180_meff560"),   0., {   1.24,  0.25 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss180_meff700"),   1., {   0.86,  0.20 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss180_meff860"),   1., {   0.74,  0.19 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss200_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss200_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss200_meff260"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss200_meff340"),   0., {   0.06,  0.03 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss200_meff440"),   2., {   0.82,  0.17 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss200_meff560"),   1., {   1.72,  0.72 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss200_meff700"),   1., {   1.31,  0.62 }));
        add_result(SignalRegionData(_counters.at("2017_ETmiss200_meff860"),   6., {   1.51,  0.35 }));

        add_result(SignalRegionData(_counters.at("2018_ETmiss0_meff160"),    10., {   8.13,  0.38 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss0_meff200"),   755., { 775.39, 13.80 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss0_meff260"),  1805., {1756.68, 20.17 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss0_meff340"),   840., { 890.75, 35.88 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss0_meff440"),   281., { 304.61, 16.83 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss0_meff560"),    87., {  94.22,  3.06 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss0_meff700"),    23., {  28.13,  7.89 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss0_meff860"),    13., {   7.33,  1.70 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss20_meff160"),    0., {   0.30,  0.19 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss20_meff200"),  617., { 602.04, 10.29 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss20_meff260"), 2714., {2790.87, 89.53 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss20_meff340"), 1727., {1813.19, 43.69 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss20_meff440"),  582., { 644.07, 28.53 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss20_meff560"),  225., { 203.80,  4.82 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss20_meff700"),   58., {  63.85,  2.76 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss20_meff860"),   24., {  16.65,  1.27 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss40_meff160"),    0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss40_meff200"),   87., {  92.37,  2.29 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss40_meff260"), 1412., {1378.89, 35.64 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss40_meff340"), 1324., {1313.88, 23.22 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss40_meff440"),  502., { 529.60, 20.31 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss40_meff560"),  162., { 183.19,  4.87 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss40_meff700"),   61., {  61.58,  5.30 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss40_meff860"),   18., {  16.79,  3.02 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss60_meff160"),    0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss60_meff200"),    4., {   3.94,  0.22 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss60_meff260"),  385., { 383.90,  5.67 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss60_meff340"),  613., { 601.25, 19.62 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss60_meff440"),  271., { 292.39, 15.44 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss60_meff560"),   91., { 116.97,  8.12 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss60_meff700"),   44., {  42.20,  2.20 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss60_meff860"),   10., {  13.87,  1.29 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss80_meff160"),    0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss80_meff200"),    0., {   0.01,  0.01 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss80_meff260"),   68., {  72.33,  7.93 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss80_meff340"),  220., { 215.09,  3.84 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss80_meff440"),  119., { 127.83,  5.92 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss80_meff560"),   59., {  57.67,  2.16 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss80_meff700"),   28., {  23.28,  1.35 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss80_meff860"),   13., {   8.60,  0.86 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss100_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss100_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss100_meff260"),   8., {   9.81,  0.41 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss100_meff340"),  71., {  67.81,  1.74 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss100_meff440"),  54., {  52.55,  6.79 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss100_meff560"),  21., {  27.39,  1.49 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss100_meff700"),  11., {  11.94,  2.04 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss100_meff860"),   2., {   5.18,  0.70 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss120_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss120_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss120_meff260"),   0., {   0.84,  0.10 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss120_meff340"),  15., {  19.52,  4.38 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss120_meff440"),  17., {  20.47,  0.92 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss120_meff560"),   9., {  12.36,  1.81 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss120_meff700"),   8., {   6.01,  1.46 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss120_meff860"),   5., {   3.20,  0.48 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss140_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss140_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss140_meff260"),   0., {   0.03,  0.01 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss140_meff340"),   5., {   5.56,  0.37 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss140_meff440"),  12., {   9.93,  0.56 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss140_meff560"),   4., {   5.48,  1.19 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss140_meff700"),   5., {   3.27,  1.77 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss140_meff860"),   2., {   2.03,  0.36 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss160_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss160_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss160_meff260"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss160_meff340"),   1., {   1.51,  0.17 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss160_meff440"),   4., {   4.52,  0.38 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss160_meff560"),   2., {   3.64,  0.38 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss160_meff700"),   5., {   1.61,  0.26 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss160_meff860"),   2., {   1.71,  1.96 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss180_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss180_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss180_meff260"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss180_meff340"),   0., {   0.37,  0.08 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss180_meff440"),   4., {   2.10,  0.75 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss180_meff560"),   1., {   2.15,  0.24 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss180_meff700"),   1., {   1.03,  0.17 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss180_meff860"),   2., {   0.79,  0.26 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss200_meff160"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss200_meff200"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss200_meff260"),   0., {   0.00,  0.00 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss200_meff340"),   0., {   0.08,  0.03 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss200_meff440"),   3., {   1.34,  0.19 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss200_meff560"),   0., {   3.28,  0.40 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss200_meff700"),   4., {   2.70,  0.37 }));
        add_result(SignalRegionData(_counters.at("2018_ETmiss200_meff860"),   5., {   2.09,  0.41 }));
        
        return;
      }

      void analysis_specific_reset() {
        // Clear signal regions
        for (auto& pair : _counters) { pair.second.reset(); }

        #ifdef CHECK_CUTFLOW
          // Clear cut flow vector
          std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
        #endif
      }



    };

    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2020_16)


    //
    // Class for collecting results for the exclusion regions combined across the three years
    //

    class Analysis_ATLAS_SUSY_2020_16_allyears : public Analysis_ATLAS_SUSY_2020_16 {

    public:
      Analysis_ATLAS_SUSY_2020_16_allyears() {
        set_analysis_name("ATLAS_SUSY_2020_16_allyears");
      }

      virtual void collect_results() {

        add_result(SignalRegionData( _counters.at(  "2016_ETmiss0_meff160").combine(_counters.at("2017_ETmiss0_meff160")  ).combine(_counters.at("2018_ETmiss0_meff160")  ) ,    6. +      7. +  10.     , {    3.85  +     6.26  +     8.13 , std::sqrt(  std::pow(0.30,2)  +  std::pow(1.08,2)  +  std::pow(0.38,2)) }));
        add_result(SignalRegionData( _counters.at(  "2016_ETmiss0_meff200").combine(_counters.at("2017_ETmiss0_meff200")  ).combine(_counters.at("2018_ETmiss0_meff200")  ) ,  395. +    425. +  755.    , {  405.80  +   441.28  +   775.39 , std::sqrt(  std::pow(8.44,2)  +  std::pow(7.47,2)  + std::pow(13.80,2)) }));
        add_result(SignalRegionData( _counters.at(  "2016_ETmiss0_meff260").combine(_counters.at("2017_ETmiss0_meff260")  ).combine(_counters.at("2018_ETmiss0_meff260")  ) ,  946. +    818. +  1805.   , {  971.72  +   842.96  +  1756.68 , std::sqrt( std::pow(13.83,2)  + std::pow(11.3,2)   + std::pow(20.17,2)) }));
        add_result(SignalRegionData( _counters.at(  "2016_ETmiss0_meff340").combine(_counters.at("2017_ETmiss0_meff340")  ).combine(_counters.at("2018_ETmiss0_meff340")  ) ,  474. +    349. +  840.    , {  510.50  +   380.43  +   890.75 , std::sqrt( std::pow(22.39,2)  +  std::pow(6.9,2)   + std::pow(35.88,2)) }));
        add_result(SignalRegionData( _counters.at(  "2016_ETmiss0_meff440").combine(_counters.at("2017_ETmiss0_meff440")  ).combine(_counters.at("2018_ETmiss0_meff440")  ) ,  150. +    139. +  281.    , {  175.17  +   134.49  +   304.61 , std::sqrt(  std::pow(8.67,2)  +  std::pow(3.43,2)  + std::pow(16.83,2)) }));
        add_result(SignalRegionData( _counters.at(  "2016_ETmiss0_meff560").combine(_counters.at("2017_ETmiss0_meff560")  ).combine(_counters.at("2018_ETmiss0_meff560")  ) ,   45. +     44. +  87.     , {   58.56  +    44.8   +    94.22 , std::sqrt(  std::pow(2.21,2)  +  std::pow(1.73,2)  +  std::pow(3.06,2)) }));
        add_result(SignalRegionData( _counters.at(  "2016_ETmiss0_meff700").combine(_counters.at("2017_ETmiss0_meff700")  ).combine(_counters.at("2018_ETmiss0_meff700")  ) ,   22. +     15. +  23.     , {   18.88  +    13.07  +    28.13 , std::sqrt(  std::pow(1.16,2)  +  std::pow(0.9,2)   +  std::pow(7.89,2)) }));
        add_result(SignalRegionData( _counters.at(  "2016_ETmiss0_meff860").combine(_counters.at("2017_ETmiss0_meff860")  ).combine(_counters.at("2018_ETmiss0_meff860")  ) ,    5. +      3. +  13.     , {    6.14  +     3.25  +     7.33 , std::sqrt(  std::pow(0.72,2)  +  std::pow(1.35,2)  +  std::pow(1.70,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss20_meff160").combine(_counters.at("2017_ETmiss20_meff160") ).combine(_counters.at("2018_ETmiss20_meff160") ) ,    0. +     1.  +  0.      , {    0.19  +     0.25  +     0.30 , std::sqrt(  std::pow(0.20,2)  +  std::pow(0.36,2)  +  std::pow(0.19,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss20_meff200").combine(_counters.at("2017_ETmiss20_meff200") ).combine(_counters.at("2018_ETmiss20_meff200") ) ,  281. +   311.  +  617.    , {  309.25  +   327.72  +   602.04 , std::sqrt(  std::pow(6.28,2)  +  std::pow(5.87,2)  + std::pow(10.29,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss20_meff260").combine(_counters.at("2017_ETmiss20_meff260") ).combine(_counters.at("2018_ETmiss20_meff260") ) , 1496. +  1302.  +  2714.   , { 1538.18  +  1287.74  +  2790.87 , std::sqrt( std::pow(17.89,2)  + std::pow(10.98,2)  + std::pow(89.53,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss20_meff340").combine(_counters.at("2017_ETmiss20_meff340") ).combine(_counters.at("2018_ETmiss20_meff340") ) ,  947. +   752.  +  1727.   , { 1033.39  +   739.34  +  1813.19 , std::sqrt( std::pow(22.84,2)  +  std::pow(9.81,2)  + std::pow(43.69,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss20_meff440").combine(_counters.at("2017_ETmiss20_meff440") ).combine(_counters.at("2018_ETmiss20_meff440") ) ,  388. +   248.  +  582.    , {  380.75  +   269.81  +   644.07 , std::sqrt( std::pow(12.13,2)  +  std::pow(5.8,2)   + std::pow(28.53,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss20_meff560").combine(_counters.at("2017_ETmiss20_meff560") ).combine(_counters.at("2018_ETmiss20_meff560") ) ,  118. +    80.  +  225.    , {  126.60  +    92.56  +   203.80 , std::sqrt(  std::pow(3.85,2)  +  std::pow(2.78,2)  +  std::pow(4.82,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss20_meff700").combine(_counters.at("2017_ETmiss20_meff700") ).combine(_counters.at("2018_ETmiss20_meff700") ) ,   34. +    30.  +  58.     , {   39.47  +    28.56  +    63.85 , std::sqrt(  std::pow(1.89,2)  +  std::pow(1.41,2)  +  std::pow(2.76,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss20_meff860").combine(_counters.at("2017_ETmiss20_meff860") ).combine(_counters.at("2018_ETmiss20_meff860") ) ,   12. +    11.  +  24.     , {   15.78  +     7.36  +    16.65 , std::sqrt(  std::pow(1.35,2)  +  std::pow(0.7,2)   +  std::pow(1.27,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss40_meff160").combine(_counters.at("2017_ETmiss40_meff160") ).combine(_counters.at("2018_ETmiss40_meff160") ) ,    0. +     0.  +  0.      , {    0.00  +     0     +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss40_meff200").combine(_counters.at("2017_ETmiss40_meff200") ).combine(_counters.at("2018_ETmiss40_meff200") ) ,   33. +    36.  +  87.     , {   47.12  +    48.19  +    92.37 , std::sqrt(  std::pow(1.43,2)  +  std::pow(1.34,2)  +  std::pow(2.29,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss40_meff260").combine(_counters.at("2017_ETmiss40_meff260") ).combine(_counters.at("2018_ETmiss40_meff260") ) ,  742. +   577.  +  1412.   , {  752.14  +   581.73  +  1378.89 , std::sqrt( std::pow(29.99,2)  + std::pow(14.97,2)  + std::pow(35.64,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss40_meff340").combine(_counters.at("2017_ETmiss40_meff340") ).combine(_counters.at("2018_ETmiss40_meff340") ) ,  718. +   496.  +  1324.   , {  749.81  +   503.15  +  1313.88 , std::sqrt(  std::pow(9.58,2)  +  std::pow(7.03,2)  + std::pow(23.22,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss40_meff440").combine(_counters.at("2017_ETmiss40_meff440") ).combine(_counters.at("2018_ETmiss40_meff440") ) ,  308. +   199.  +  502.    , {  311.87  +   204.62  +   529.60 , std::sqrt(  std::pow(6.61,2)  + std::pow(10.83,2)  + std::pow(20.31,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss40_meff560").combine(_counters.at("2017_ETmiss40_meff560") ).combine(_counters.at("2018_ETmiss40_meff560") ) ,  116. +    58.  +  162.    , {  113.04  +    78.36  +   183.19 , std::sqrt(  std::pow(3.38,2)  +  std::pow(2.43,2)  +  std::pow(4.87,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss40_meff700").combine(_counters.at("2017_ETmiss40_meff700") ).combine(_counters.at("2018_ETmiss40_meff700") ) ,   31. +    21.  +  61.     , {   39.23  +    25.21  +    61.58 , std::sqrt(  std::pow(4.37,2)  +  std::pow(1.24,2)  +  std::pow(5.30,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss40_meff860").combine(_counters.at("2017_ETmiss40_meff860") ).combine(_counters.at("2018_ETmiss40_meff860") ) ,   15. +     8.  +  18.     , {   15.41  +     8.48  +    16.79 , std::sqrt(  std::pow(1.21,2)  +  std::pow(2.74,2)  +  std::pow(3.02,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss60_meff160").combine(_counters.at("2017_ETmiss60_meff160") ).combine(_counters.at("2018_ETmiss60_meff160") ) ,    0. +     0.  +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss60_meff200").combine(_counters.at("2017_ETmiss60_meff200") ).combine(_counters.at("2018_ETmiss60_meff200") ) ,    1. +     2.  +  4.      , {    2.06  +     1.82  +     3.94 , std::sqrt(  std::pow(0.19,2)  +  std::pow(0.14,2)  +  std::pow(0.22,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss60_meff260").combine(_counters.at("2017_ETmiss60_meff260") ).combine(_counters.at("2018_ETmiss60_meff260") ) ,  208. +   149.  +  385.    , {  207.44  +   140.93  +   383.90 , std::sqrt(  std::pow(4.17,2)  +  std::pow(3.31,2)  +  std::pow(5.67,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss60_meff340").combine(_counters.at("2017_ETmiss60_meff340") ).combine(_counters.at("2018_ETmiss60_meff340") ) ,  348. +   202.  +  613.    , {  353.00  +   212.4   +   601.25 , std::sqrt(  std::pow(6.42,2)  +  std::pow(9.28,2)  + std::pow(19.62,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss60_meff440").combine(_counters.at("2017_ETmiss60_meff440") ).combine(_counters.at("2018_ETmiss60_meff440") ) ,  159. +    97.  +  271.    , {  172.17  +   106.18  +   292.39 , std::sqrt( std::pow(12.08,2)  +  std::pow(3.25,2)  + std::pow(15.44,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss60_meff560").combine(_counters.at("2017_ETmiss60_meff560") ).combine(_counters.at("2018_ETmiss60_meff560") ) ,   57. +    39.  +  91.     , {   69.96  +    45.23  +   116.97 , std::sqrt(  std::pow(2.53,2)  +  std::pow(1.82,2)  +  std::pow(8.12,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss60_meff700").combine(_counters.at("2017_ETmiss60_meff700") ).combine(_counters.at("2018_ETmiss60_meff700") ) ,   23. +    14.  +  44.     , {   27.11  +    17.6   +    42.20 , std::sqrt(  std::pow(1.51,2)  +  std::pow(2.12,2)  +  std::pow(2.20,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss60_meff860").combine(_counters.at("2017_ETmiss60_meff860") ).combine(_counters.at("2018_ETmiss60_meff860") ) ,   21. +    11.  +  10.     , {   10.82  +     6.46  +    13.87 , std::sqrt(  std::pow(2.56,2)  +  std::pow(2.24,2)  +  std::pow(1.29,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss80_meff160").combine(_counters.at("2017_ETmiss80_meff160") ).combine(_counters.at("2018_ETmiss80_meff160") ) ,    0. +     0.  +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss80_meff200").combine(_counters.at("2017_ETmiss80_meff200") ).combine(_counters.at("2018_ETmiss80_meff200") ) ,    0. +     0.  +  0.      , {    0.02  +     0.0   +     0.01 , std::sqrt(  std::pow(0.01,2)  +  std::pow(0.0,2)   +  std::pow(0.01,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss80_meff260").combine(_counters.at("2017_ETmiss80_meff260") ).combine(_counters.at("2018_ETmiss80_meff260") ) ,   38. +    23.  +  68.     , {   40.23  +    22.77  +    72.33 , std::sqrt(  std::pow(1.26,2)  +  std::pow(3.1,2)   +  std::pow(7.93,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss80_meff340").combine(_counters.at("2017_ETmiss80_meff340") ).combine(_counters.at("2018_ETmiss80_meff340") ) ,  103. +    66.  +  220.    , {  123.45  +    68.99  +   215.09 , std::sqrt(  std::pow(5.74,2)  +  std::pow(1.99,2)  +  std::pow(3.84,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss80_meff440").combine(_counters.at("2017_ETmiss80_meff440") ).combine(_counters.at("2018_ETmiss80_meff440") ) ,   79. +    48.  +  119.    , {   77.26  +    43.58  +   127.83 , std::sqrt(  std::pow(4.55,2)  +  std::pow(6.7,2)   +  std::pow(5.92,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss80_meff560").combine(_counters.at("2017_ETmiss80_meff560") ).combine(_counters.at("2018_ETmiss80_meff560") ) ,   36. +    22.  +  59.     , {   34.42  +    21.63  +    57.67 , std::sqrt(  std::pow(4.07,2)  +  std::pow(2.49,2)  +  std::pow(2.16,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss80_meff700").combine(_counters.at("2017_ETmiss80_meff700") ).combine(_counters.at("2018_ETmiss80_meff700") ) ,   14. +     4.  +  28.     , {   13.57  +     9.48  +    23.28 , std::sqrt(  std::pow(0.99,2)  +  std::pow(1.73,2)  +  std::pow(1.35,2)) }));
        add_result(SignalRegionData( _counters.at( "2016_ETmiss80_meff860").combine(_counters.at("2017_ETmiss80_meff860") ).combine(_counters.at("2018_ETmiss80_meff860") ) ,   10. +     5.  +  13.     , {    6.12  +     3.77  +     8.60 , std::sqrt(  std::pow(0.56,2)  +  std::pow(1.92,2)  +  std::pow(0.86,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss100_meff160").combine(_counters.at("2017_ETmiss100_meff160")).combine(_counters.at("2018_ETmiss100_meff160")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss100_meff200").combine(_counters.at("2017_ETmiss100_meff200")).combine(_counters.at("2018_ETmiss100_meff200")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss100_meff260").combine(_counters.at("2017_ETmiss100_meff260")).combine(_counters.at("2018_ETmiss100_meff260")) ,    5. +    2.   +  8.      , {    5.05  +     2.51  +     9.81 , std::sqrt(  std::pow(0.32,2)  +  std::pow(1.11,2)  +  std::pow(0.41,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss100_meff340").combine(_counters.at("2017_ETmiss100_meff340")).combine(_counters.at("2018_ETmiss100_meff340")) ,   41. +   17.   +  71.     , {   41.30  +    18.98  +    67.81 , std::sqrt(  std::pow(2.99,2)  +  std::pow(0.72,2)  +  std::pow(1.74,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss100_meff440").combine(_counters.at("2017_ETmiss100_meff440")).combine(_counters.at("2018_ETmiss100_meff440")) ,   26. +   15.   +  54.     , {   31.82  +    16.29  +    52.55 , std::sqrt(  std::pow(1.40,2)  +  std::pow(0.89,2)  +  std::pow(6.79,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss100_meff560").combine(_counters.at("2017_ETmiss100_meff560")).combine(_counters.at("2018_ETmiss100_meff560")) ,   14. +   11.   +  21.     , {   17.89  +     9.27  +    27.39 , std::sqrt(  std::pow(3.09,2)  +  std::pow(1.33,2)  +  std::pow(1.49,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss100_meff700").combine(_counters.at("2017_ETmiss100_meff700")).combine(_counters.at("2018_ETmiss100_meff700")) ,    9. +    5.   +  11.     , {    7.50  +     4.09  +    11.94 , std::sqrt(  std::pow(1.54,2)  +  std::pow(2.17,2)  +  std::pow(2.04,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss100_meff860").combine(_counters.at("2017_ETmiss100_meff860")).combine(_counters.at("2018_ETmiss100_meff860")) ,   10. +    1.   +  2.      , {    4.02  +     2.08  +     5.18 , std::sqrt(  std::pow(0.56,2)  +  std::pow(0.62,2)  +  std::pow(0.70,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss120_meff160").combine(_counters.at("2017_ETmiss120_meff160")).combine(_counters.at("2018_ETmiss120_meff160")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss120_meff200").combine(_counters.at("2017_ETmiss120_meff200")).combine(_counters.at("2018_ETmiss120_meff200")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss120_meff260").combine(_counters.at("2017_ETmiss120_meff260")).combine(_counters.at("2018_ETmiss120_meff260")) ,    0. +    0.   +  0.      , {    0.44  +     0.2   +     0.84 , std::sqrt(  std::pow(0.09,2)  +  std::pow(0.04,2)  +  std::pow(0.10,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss120_meff340").combine(_counters.at("2017_ETmiss120_meff340")).combine(_counters.at("2018_ETmiss120_meff340")) ,   18. +    4.   +  15.     , {   13.19  +     4.98  +    19.52 , std::sqrt(  std::pow(0.65,2)  +  std::pow(1.49,2)  +  std::pow(4.38,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss120_meff440").combine(_counters.at("2017_ETmiss120_meff440")).combine(_counters.at("2018_ETmiss120_meff440")) ,    8. +    5.   +  17.     , {   15.52  +     5.84  +    20.47 , std::sqrt(  std::pow(0.89,2)  +  std::pow(1.2,2)   +  std::pow(0.92,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss120_meff560").combine(_counters.at("2017_ETmiss120_meff560")).combine(_counters.at("2018_ETmiss120_meff560")) ,    9. +    2.   +  9.      , {    8.60  +     3.83  +    12.36 , std::sqrt(  std::pow(2.38,2)  +  std::pow(0.39,2)  +  std::pow(1.81,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss120_meff700").combine(_counters.at("2017_ETmiss120_meff700")).combine(_counters.at("2018_ETmiss120_meff700")) ,    5. +    5.   +  8.      , {    3.69  +     2.32  +     6.01 , std::sqrt(  std::pow(0.44,2)  +  std::pow(0.55,2)  +  std::pow(1.46,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss120_meff860").combine(_counters.at("2017_ETmiss120_meff860")).combine(_counters.at("2018_ETmiss120_meff860")) ,    2. +    1.   +  5.      , {    2.51  +     0.97  +     3.20 , std::sqrt(  std::pow(1.58,2)  +  std::pow(0.18,2)  +  std::pow(0.48,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss140_meff160").combine(_counters.at("2017_ETmiss140_meff160")).combine(_counters.at("2018_ETmiss140_meff160")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss140_meff200").combine(_counters.at("2017_ETmiss140_meff200")).combine(_counters.at("2018_ETmiss140_meff200")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss140_meff260").combine(_counters.at("2017_ETmiss140_meff260")).combine(_counters.at("2018_ETmiss140_meff260")) ,    0. +    0.   +  0.      , {    0.02  +     0.01  +     0.03 , std::sqrt(  std::pow(0.02,2)  +  std::pow(0.01,2)  +  std::pow(0.01,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss140_meff340").combine(_counters.at("2017_ETmiss140_meff340")).combine(_counters.at("2018_ETmiss140_meff340")) ,    2. +    2.   +  5.      , {    3.52  +     1.42  +     5.56 , std::sqrt(  std::pow(0.33,2)  +  std::pow(0.81,2)  +  std::pow(0.37,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss140_meff440").combine(_counters.at("2017_ETmiss140_meff440")).combine(_counters.at("2018_ETmiss140_meff440")) ,   10. +    3.   +  12.     , {    6.34  +     2.97  +     9.93 , std::sqrt(  std::pow(0.50,2)  +  std::pow(0.24,2)  +  std::pow(0.56,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss140_meff560").combine(_counters.at("2017_ETmiss140_meff560")).combine(_counters.at("2018_ETmiss140_meff560")) ,    5. +    5.   +  4.      , {    4.19  +     2.29  +     5.48 , std::sqrt(  std::pow(0.44,2)  +  std::pow(1.49,2)  +  std::pow(1.19,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss140_meff700").combine(_counters.at("2017_ETmiss140_meff700")).combine(_counters.at("2018_ETmiss140_meff700")) ,    2. +    3.   +  5.      , {    1.69  +     1.22  +     3.27 , std::sqrt(  std::pow(0.26,2)  +  std::pow(0.56,2)  +  std::pow(1.77,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss140_meff860").combine(_counters.at("2017_ETmiss140_meff860")).combine(_counters.at("2018_ETmiss140_meff860")) ,    1. +    1.   +  2.      , {    1.54  +     0.8   +     2.03 , std::sqrt(  std::pow(0.34,2)  +  std::pow(0.19,2)  +  std::pow(0.36,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss160_meff160").combine(_counters.at("2017_ETmiss160_meff160")).combine(_counters.at("2018_ETmiss160_meff160")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss160_meff200").combine(_counters.at("2017_ETmiss160_meff200")).combine(_counters.at("2018_ETmiss160_meff200")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss160_meff260").combine(_counters.at("2017_ETmiss160_meff260")).combine(_counters.at("2018_ETmiss160_meff260")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss160_meff340").combine(_counters.at("2017_ETmiss160_meff340")).combine(_counters.at("2018_ETmiss160_meff340")) ,    4. +    1.   +  1.      , {    0.85  +     0.27  +     1.51 , std::sqrt(  std::pow(0.14,2)  +  std::pow(0.06,2)  +  std::pow(0.17,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss160_meff440").combine(_counters.at("2017_ETmiss160_meff440")).combine(_counters.at("2018_ETmiss160_meff440")) ,    0. +    0.   +  4.      , {    2.96  +     1.43  +     4.52 , std::sqrt(  std::pow(0.35,2)  +  std::pow(0.15,2)  +  std::pow(0.38,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss160_meff560").combine(_counters.at("2017_ETmiss160_meff560")).combine(_counters.at("2018_ETmiss160_meff560")) ,    4. +    0.   +  2.      , {    1.88  +     1.09  +     3.64 , std::sqrt(  std::pow(0.25,2)  +  std::pow(0.18,2)  +  std::pow(0.38,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss160_meff700").combine(_counters.at("2017_ETmiss160_meff700")).combine(_counters.at("2018_ETmiss160_meff700")) ,    1. +    1.   +  5.      , {    0.95  +     0.74  +     1.61 , std::sqrt(  std::pow(0.23,2)  +  std::pow(0.64,2)  +  std::pow(0.26,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss160_meff860").combine(_counters.at("2017_ETmiss160_meff860")).combine(_counters.at("2018_ETmiss160_meff860")) ,    3. +    1.   +  2.      , {    0.71  +     0.43  +     1.71 , std::sqrt(  std::pow(0.40,2)  +  std::pow(0.12,2)  +  std::pow(1.96,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss180_meff160").combine(_counters.at("2017_ETmiss180_meff160")).combine(_counters.at("2018_ETmiss180_meff160")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss180_meff200").combine(_counters.at("2017_ETmiss180_meff200")).combine(_counters.at("2018_ETmiss180_meff200")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss180_meff260").combine(_counters.at("2017_ETmiss180_meff260")).combine(_counters.at("2018_ETmiss180_meff260")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss180_meff340").combine(_counters.at("2017_ETmiss180_meff340")).combine(_counters.at("2018_ETmiss180_meff340")) ,    0. +    0.   +  0.      , {    0.20  +     0.09  +     0.37 , std::sqrt(  std::pow(0.21,2)  +  std::pow(0.03,2)  +  std::pow(0.08,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss180_meff440").combine(_counters.at("2017_ETmiss180_meff440")).combine(_counters.at("2018_ETmiss180_meff440")) ,    1. +    0.   +  4.      , {    1.25  +     0.69  +     2.10 , std::sqrt(  std::pow(0.20,2)  +  std::pow(0.11,2)  +  std::pow(0.75,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss180_meff560").combine(_counters.at("2017_ETmiss180_meff560")).combine(_counters.at("2018_ETmiss180_meff560")) ,    0. +    0.   +  1.      , {    1.24  +     0.66  +     2.15 , std::sqrt(  std::pow(0.25,2)  +  std::pow(0.37,2)  +  std::pow(0.24,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss180_meff700").combine(_counters.at("2017_ETmiss180_meff700")).combine(_counters.at("2018_ETmiss180_meff700")) ,    1. +    0.   +  1.      , {    0.86  +     0.31  +     1.03 , std::sqrt(  std::pow(0.20,2)  +  std::pow(0.21,2)  +  std::pow(0.17,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss180_meff860").combine(_counters.at("2017_ETmiss180_meff860")).combine(_counters.at("2018_ETmiss180_meff860")) ,    1. +    2.   +  2.      , {    0.74  +     0.27  +     0.79 , std::sqrt(  std::pow(0.19,2)  +  std::pow(0.62,2)  +  std::pow(0.26,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss200_meff160").combine(_counters.at("2017_ETmiss200_meff160")).combine(_counters.at("2018_ETmiss200_meff160")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss200_meff200").combine(_counters.at("2017_ETmiss200_meff200")).combine(_counters.at("2018_ETmiss200_meff200")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss200_meff260").combine(_counters.at("2017_ETmiss200_meff260")).combine(_counters.at("2018_ETmiss200_meff260")) ,    0. +    0.   +  0.      , {    0.00  +     0.0   +     0.00 , std::sqrt(  std::pow(0.00,2)  +  std::pow(0.0,2)   +  std::pow(0.00,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss200_meff340").combine(_counters.at("2017_ETmiss200_meff340")).combine(_counters.at("2018_ETmiss200_meff340")) ,    0. +    0.   +  0.      , {    0.06  +     0.0   +     0.08 , std::sqrt(  std::pow(0.03,2)  +  std::pow(0.0,2)   +  std::pow(0.03,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss200_meff440").combine(_counters.at("2017_ETmiss200_meff440")).combine(_counters.at("2018_ETmiss200_meff440")) ,    2. +    1.   +  3.      , {    0.82  +     0.64  +     1.34 , std::sqrt(  std::pow(0.17,2)  +  std::pow(0.67,2)  +  std::pow(0.19,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss200_meff560").combine(_counters.at("2017_ETmiss200_meff560")).combine(_counters.at("2018_ETmiss200_meff560")) ,    1. +    1.   +  0.      , {    1.72  +     1.25  +     3.28 , std::sqrt(  std::pow(0.72,2)  +  std::pow(1.1,2)   +  std::pow(0.40,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss200_meff700").combine(_counters.at("2017_ETmiss200_meff700")).combine(_counters.at("2018_ETmiss200_meff700")) ,    1. +    2.   +  4.      , {    1.31  +     1.25  +     2.70 , std::sqrt(  std::pow(0.62,2)  +  std::pow(0.22,2)  +  std::pow(0.37,2)) }));
        add_result(SignalRegionData( _counters.at("2016_ETmiss200_meff860").combine(_counters.at("2017_ETmiss200_meff860")).combine(_counters.at("2018_ETmiss200_meff860")) ,    6. +    2.   +  5.      , {    1.51  +     1.05  +     2.09 , std::sqrt(  std::pow(0.35,2)  +  std::pow(0.2,2)   +  std::pow(0.41,2)) }));

      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2020_16_allyears)



    //
    // Class for collecting results for discovery regions as a derived class
    //

    class Analysis_ATLAS_SUSY_2020_16_discoverySR : public Analysis_ATLAS_SUSY_2020_16 {

    public:
      Analysis_ATLAS_SUSY_2020_16_discoverySR() {
        set_analysis_name("ATLAS_SUSY_2020_16_discoverySR");
      }

      virtual void collect_results() {
        add_result(SignalRegionData(_counters.at("SR_LM_150"), 1790., {1860., 50.}));
        add_result(SignalRegionData(_counters.at("SR_LM_300"),   97., {  77.,  5.3}));
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_SUSY_2020_16_discoverySR)

  }
}
