///
///  \author Are Raklev
///  \date 2021 July
///
///
///  Based on the search presented in 2106.01676.
///
/// The Recursive Jigsaw (RJR) signal regions are not included in this implementation as they are not
/// statistically independent from the rest of the signal regions, and believed to not be competitve in terms of
/// exclusion power.
///
///  *********************************************

//#include <vector>
//#include <cmath>
//#include <memory>
//#include <iomanip>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

#define CHECK_CUTFLOW

using namespace std;

namespace Gambit {
  namespace ColliderBit {
  
    class Analysis_ATLAS_13TeV_3LEP_139invfb : public Analysis {

    protected:
      // Signal region map
      std::map<string, EventCounter> _counters = {
        // Exclusive SRs
        // WZ on-shell
        {"SR-WZ-1", EventCounter("SR-WZ-1")},
        {"SR-WZ-2", EventCounter("SR-WZ-2")},
        {"SR-WZ-3", EventCounter("SR-WZ-3")},
        {"SR-WZ-4", EventCounter("SR-WZ-4")},
        {"SR-WZ-5", EventCounter("SR-WZ-5")},
        {"SR-WZ-6", EventCounter("SR-WZ-6")},
        {"SR-WZ-7", EventCounter("SR-WZ-7")},
        {"SR-WZ-8", EventCounter("SR-WZ-8")},
        {"SR-WZ-9", EventCounter("SR-WZ-9")},
        {"SR-WZ-10", EventCounter("SR-WZ-10")},
        {"SR-WZ-11", EventCounter("SR-WZ-11")},
        {"SR-WZ-12", EventCounter("SR-WZ-12")},
        {"SR-WZ-13", EventCounter("SR-WZ-13")},
        {"SR-WZ-14", EventCounter("SR-WZ-14")},
        {"SR-WZ-15", EventCounter("SR-WZ-15")},
        {"SR-WZ-16", EventCounter("SR-WZ-16")},
        {"SR-WZ-17", EventCounter("SR-WZ-17")},
        {"SR-WZ-18", EventCounter("SR-WZ-18")},
        {"SR-WZ-19", EventCounter("SR-WZ-19")},
        {"SR-WZ-20", EventCounter("SR-WZ-20")},
        // Wh
        // WZ off-shell
        // Inclusive SRs
      };
            
    private:

      // Struct to sort on pT in decending order
      struct ptComparison
      {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;
      
      // Internally used Z-mass
      double mZ = 91.1876; // [GeV]

      
      #ifdef CHECK_CUTFLOW
      // Benchmark scenario
      string scenario = "";
      // Cut-flow variables
      size_t NCUTS;
      vector<int> cutFlowSig;
      vector<string> cutFlowStr = {"Total events", "Leptons + ETmiss", "nSFOS", "Trigger", "n_bjets = 0", "m_ll > 12 GeV", "|m_3l-m_Z| > 15 GeV", "75 < m_ll < 105", "MC to data weight", "n_jets = 0", "100 < m_T < 160", "50 < ETmiss < 100", "100 < ETmiss < 150", "150 < ETmiss < 200", "200 < ETmiss"};
      vector<double> cutFlowExp;

      #endif
      
    public:
      
      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_3LEP_139invfb() {

        set_analysis_name("ATLAS_13TeV_3LEP_139invfb");
        set_luminosity(139.);
        
        #ifdef CHECK_CUTFLOW
        scenario = "WZ_300_200";
        NCUTS=15;
        for(size_t i=0; i<NCUTS; i++){
          cutFlowSig.push_back(0);
          cutFlowExp.push_back(0);
          //cutFlowStr.push_back("");
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

      
      //
      // Main event analysis
      //
      void run(const HEPUtils::Event* event) {

        // Get the missing energy in the event
        double met = event->met();
        HEPUtils::P4 metVec = event->missingmom();
        
        // Define vectors of baseline leptons
        // Baseline electrons
        vector<const HEPUtils::Particle*> electrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 4.5
              && fabs(electron->eta()) < 2.47)
            electrons.push_back(electron);
        }
        // Apply electron efficiency from "Loose" criteria in 1902.04655
        ATLAS::applyElectronIDEfficiency2019(electrons, "Loose");
        // Baseline muons
        vector<const HEPUtils::Particle*> muons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 3.
              && fabs(muon->eta()) < 2.5)
            muons.push_back(muon);
        }
        // Apply muon efficiency from "Medium" criteria
        ATLAS::applyMuonEffR2(muons);
        
        // Number of leptons
        size_t nMuons = muons.size();
        size_t nElectrons = electrons.size();
//        size_t nLeptons = nElectrons+nMuons;
        
        // Baseline jets
        vector<const HEPUtils::Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.5 ){
            baselineJets.push_back(jet);
          }
        }

        // Overlap removal (remove jets within DR=1 of electrons)
        JetLeptonOverlapRemoval(baselineJets, electrons, 0.4);
        //        size_t nfat = fatJets.size();

        
        int njets = baselineJets.size();
        double HT = 0;
        for(const HEPUtils::Jet* jet : baselineJets) HT += jet->pT();
        
        // Joint vector for leptons
        vector<const HEPUtils::Particle*> leptons;
        leptons = electrons;
        leptons.insert(leptons.end(), muons.begin(), muons.end());
        // Sort leptons by pT
        sortByPt(leptons);
        size_t nLeptons = leptons.size();
        
        // Check lepton pT
        bool bpT1 = false; bool bpT2 = false; bool bpT3 = false;
        if(nLeptons == 3){
         if( leptons[0]->pT() > 25.) bpT1 = true;
         if( leptons[1]->pT() > 20.) bpT2 = true;
         if( leptons[2]->pT() > 10.) bpT3 = true;
        }
        bool bLeptons = bpT1 && bpT2 && bpT3;
        
        // Identify the roles of the leptons
        bool bSFOS = false;
        int iZ1 = -1; int iZ2 = -1; int iW = -1;
        double dmZ = 999.; double mll = 0; double mlll = 0; double mT = 0; double HTlep = 999.;
        // Only bother if we have three OK leptons
        if(bLeptons){
          // Find SFOS from Z under given criteria
          for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
              // Check for SFOS
              if(leptons[i]->pid() + leptons[j]->pid() == 0){
                // Check invariant mass
                double mll_test = (leptons[i]->mom()+leptons[j]->mom()).m();
                if(fabs(mll_test-mZ) < dmZ){
                  iZ1 = i; iZ2 = j; dmZ = fabs(mll_test-mZ); mll = mll_test;
                  bSFOS = true;
                }
              }
            }
          }
          
          // Find lepton from W
          if( iZ1 == 0 && iZ2 == 1) iW = 2;
          if( iZ1 == 1 && iZ2 == 2) iW = 0;
          if( iZ1 == 0 && iZ2 == 2) iW = 1;
          
          // If SFOS pair from Z and W-lepton found, calculate some kinematics
          if(bSFOS && iW != -1) {
            HEPUtils::P4 plW = leptons[iW]->mom();
            mlll = (leptons[iZ1]->mom()+leptons[iZ2]->mom()+plW).m();
            // Calculate m_T between W-lepton and missing momentum vector
            mT = sqrt( 2.*plW.pT()*met*( 1.-cos( plW.deltaPhi(metVec) ) ) );
            HTlep = leptons[iZ1]->pT() + leptons[iZ2]->pT() + plW.pT();
          }
        }
        //cout << iZ1 << " " << iZ2 << " " << iW << " " << mll << endl;
        
        
  	    // b-jet tagging
        double btag = 0.85; double cmisstag = 1/2.7; double misstag = 1./25.;
        int nb = 0;
        for ( const HEPUtils::Jet* jet : event->jets() ) {
          // Kinematics criteria for candidate b-jets
          if (jet->pT() > 20. && fabs(jet->eta()) < 2.5 ){
            // Tag b-jet
            if( jet->btag() && random_bool(btag) ) nb++;
            // Misstag c-jet
            else if( !jet->btag() && jet->ctag() && random_bool(cmisstag) ) nb++;
            // Misstag light jet
            else if( !jet->btag() && !jet->ctag() && random_bool(misstag) ) nb++;
          }
        }
        
        
        //
        // Count signal region events
        //
        
        // First exclusive regions
        // Pre-selection for WZ on-shell SRs
        if(bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15 && mll > 75 && mll < 105){
          // Zero jet SRs
          if(njets == 0) {
            if(mT > 100 && mT < 160){
              if(             met < 100) _counters.at("SR-WZ-1").add_event(event);
              if(met > 100 && met < 150) _counters.at("SR-WZ-2").add_event(event);
              if(met > 150 && met < 200) _counters.at("SR-WZ-3").add_event(event);
              if(met > 200             ) _counters.at("SR-WZ-4").add_event(event);
            }
            if(mT > 160){
              if(             met < 150) _counters.at("SR-WZ-5").add_event(event);
              if(met > 150 && met < 200) _counters.at("SR-WZ-6").add_event(event);
              if(met > 200 && met < 350) _counters.at("SR-WZ-7").add_event(event);
              if(met > 350             ) _counters.at("SR-WZ-8").add_event(event);
            }
          }
          if(njets > 0 && HT < 200){
            if(mT > 100 && mT < 160){
              if(met > 100 && met < 150) _counters.at("SR-WZ-9").add_event(event);
              if(met > 150 && met < 250) _counters.at("SR-WZ-10").add_event(event);
              if(met > 250 && met < 300) _counters.at("SR-WZ-11").add_event(event);
              if(met > 300             ) _counters.at("SR-WZ-12").add_event(event);
            }
            if(mT > 160){
              if(             met < 150) _counters.at("SR-WZ-13").add_event(event);
              if(met > 150 && met < 250) _counters.at("SR-WZ-14").add_event(event);
              if(met > 250 && met < 400) _counters.at("SR-WZ-15").add_event(event);
              if(met > 400             ) _counters.at("SR-WZ-16").add_event(event);
            }
          }
          if(njets > 0 && HT > 200 && HTlep < 350){
            if(mT > 100){
              if(met > 150 && met < 200) _counters.at("SR-WZ-17").add_event(event);
              if(met > 200 && met < 300) _counters.at("SR-WZ-18").add_event(event);
              if(met > 300 && met < 400) _counters.at("SR-WZ-19").add_event(event);
              if(met > 400             ) _counters.at("SR-WZ-20").add_event(event);
            }
          }
        }
        // Then inclusive regions
        
        
        #ifdef CHECK_CUTFLOW
        for(size_t j=0; j<NCUTS; j++){
          if(
            (j==0) ||
            (j==1 && bLeptons && met > 50) ||
            (j==2 && bLeptons && met > 50 && bSFOS) ||
            (j==3 && bLeptons && met > 50 && bSFOS) ||
            (j==4 && bLeptons && met > 50 && bSFOS && nb == 0) ||
            (j==5 && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12) ||
            (j==6 && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15) ||
            (j==7 && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15 && mll > 75 && mll < 105) ||
            (j==8 && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15 && mll > 75 && mll < 105) ||
            (j==9 && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15 && mll > 75 && mll < 105 && njets == 0) ||
            (j==10 && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15 && mll > 75 && mll < 105 && njets == 0 && mT > 100 && mT < 160) ||
            (j==11 && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15 && mll > 75 && mll < 105 && njets == 0 && mT > 100 && mT < 160 && met > 50 && met < 100) ||
            (j==12 && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15 && mll > 75 && mll < 105 && njets == 0 && mT > 100 && mT < 160 && met > 100 && met < 150) ||
            (j==13 && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15 && mll > 75 && mll < 105 && njets == 0 && mT > 100 && mT < 160 && met > 150 && met < 200) ||
            (j==14 && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15 && mll > 75 && mll < 105 && njets == 0 && mT > 100 && mT < 160 && met > 200)
            ) cutFlowSig[j]++;
        }
        #endif
        

      } // End of event analysis

      
      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_3LEP_139invfb* specificOther = dynamic_cast<const Analysis_ATLAS_13TeV_3LEP_139invfb*>(other);
        for (auto& pair : _counters) { pair.second += specificOther->_counters.at(pair.first); }
      }


      void collect_results() {

        // Now fill a results object with the results for each SR
        add_result(SignalRegionData(_counters.at("SR-WZ-1"), 331., {314. , 33.}));
        add_result(SignalRegionData(_counters.at("SR-WZ-2"),  31., { 35. ,  6.}));
        add_result(SignalRegionData(_counters.at("SR-WZ-3"),   3., {  4.1,  1.0}));
        add_result(SignalRegionData(_counters.at("SR-WZ-4"),   2., {  1.2,  0.5}));
        add_result(SignalRegionData(_counters.at("SR-WZ-5"),  42., { 58. ,  5.}));
        add_result(SignalRegionData(_counters.at("SR-WZ-6"),   7., {  8.0,  0.9}));
        add_result(SignalRegionData(_counters.at("SR-WZ-7"),   3., {  5.8,  1.0}));
        add_result(SignalRegionData(_counters.at("SR-WZ-8"),   1., {  0.8,  0.4}));
        add_result(SignalRegionData(_counters.at("SR-WZ-9"),  77., { 90. , 20.}));
        add_result(SignalRegionData(_counters.at("SR-WZ-10"), 11., { 13.4,  2.4}));
        add_result(SignalRegionData(_counters.at("SR-WZ-11"),  0., {  0.5,  0.4}));
        add_result(SignalRegionData(_counters.at("SR-WZ-12"),  0., {  0.49, 0.24}));
        add_result(SignalRegionData(_counters.at("SR-WZ-13"),111., { 89. , 11.}));
        add_result(SignalRegionData(_counters.at("SR-WZ-14"), 19., { 16.0,  1.4}));
        add_result(SignalRegionData(_counters.at("SR-WZ-15"),  5., {  2.8,  0.6}));
        add_result(SignalRegionData(_counters.at("SR-WZ-16"),  1., {  1.3,  0.27}));
        add_result(SignalRegionData(_counters.at("SR-WZ-17"), 13., { 13.7,  2.6}));
        add_result(SignalRegionData(_counters.at("SR-WZ-18"),  9., {  9.2,  1.3}));
        add_result(SignalRegionData(_counters.at("SR-WZ-19"),  3., {  2.3,  0.4}));
        add_result(SignalRegionData(_counters.at("SR-WZ-20"),  1., {  1.09, 0.13}));


        #ifdef CHECK_CUTFLOW
        cout << "Cut-flow output" << endl;
        
        double _xsec_model;
        double lumi = luminosity();

        vector<double> _yield_model(12);
        if(scenario == "WZ_300_200"){
          _yield_model = {53784, 227, 226, 222, 209, 209, 203, 196, 186, 76.4, 26.7, 20.9, 4.86, 0.78, 0.14};
          _xsec_model = 386.9;
        }

        double weight = _xsec_model*lumi/10000;
        
        // Compare final event yield per SR for model
        for (size_t i=0; i<NCUTS; i++) {
          
          cout << i << ":  " << setprecision(4) << cutFlowSig[i]*weight << "\t\t" << _yield_model[i] <<  "\t\t" << cutFlowSig[i]*weight/_yield_model[i]  << "\t\t" << cutFlowStr[i] <<endl;
          
//          double ATLAS_abs = cutFlowVectorATLAS[i];
//          double eff = (double)cutFlowVector[i] / (double)cutFlowVector[0];
//          //if(i > 0) eff *= 0.90; // Lower trigger efficiency for 130 GeV
//          double GAMBIT_scaled = eff * xsec * L;
//          double ratio = GAMBIT_scaled/ATLAS_abs;
//          cout << "DEBUG 1: i: " << i << ":   " << setprecision(4) << ATLAS_abs << "\t\t\t" << GAMBIT_scaled << "\t\t\t" << ratio << "\t\t\t" << cutFlowVector[i] << "\t\t\t" << cutFlowVector_str[i] << endl;
        }


        #endif
        
      }

      void analysis_specific_reset() {
        // Clear signal regions
        for (auto& pair : _counters) { pair.second.reset(); }
      }

    };


    // Factory fn
    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_3LEP_139invfb)

  }
}
