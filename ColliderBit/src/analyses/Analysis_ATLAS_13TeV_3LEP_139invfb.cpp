///
///  \author Are Raklev
///  \date 2021 July
///
///
/// Based on the three-lepton search with the full Run 2 data set presented in 2106.01676.
///
/// The Recursive Jigsaw (RJR) signal regions are not included in this implementation as they are not
/// statistically independent from the rest of the signal regions, and believed to not be competitve in terms of
/// exclusion power.
///
/// TODO: Add weights for trigger and MC2data ratio to event counter
///  *********************************************

#define CHECK_CUTFLOW
//#define BENCHMARK "WZ_300_200"
//#define BENCHMARK "WZ_600_100"
#define BENCHMARK "Wh_190_60"


#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

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
        {"SR-Wh-1", EventCounter("SR-Wh-1")},
        {"SR-Wh-2", EventCounter("SR-Wh-2")},
        {"SR-Wh-3", EventCounter("SR-Wh-3")},
        {"SR-Wh-4", EventCounter("SR-Wh-4")},
        {"SR-Wh-5", EventCounter("SR-Wh-5")},
        {"SR-Wh-6", EventCounter("SR-Wh-6")},
        {"SR-Wh-7", EventCounter("SR-Wh-7")},
        {"SR-Wh-8", EventCounter("SR-Wh-8")},
        {"SR-Wh-9", EventCounter("SR-Wh-9")},
        {"SR-Wh-10", EventCounter("SR-Wh-10")},
        {"SR-Wh-11", EventCounter("SR-Wh-11")},
        {"SR-Wh-12", EventCounter("SR-Wh-12")},
        {"SR-Wh-13", EventCounter("SR-Wh-13")},
        {"SR-Wh-14", EventCounter("SR-Wh-14")},
        {"SR-Wh-15", EventCounter("SR-Wh-15")},
        {"SR-Wh-16", EventCounter("SR-Wh-16")},
        {"SR-Wh-17", EventCounter("SR-Wh-17")},
        {"SR-Wh-18", EventCounter("SR-Wh-18")},
        {"SR-Wh-19", EventCounter("SR-Wh-19")},
        {"SR-Wh-DFOS-1", EventCounter("SR-Wh-DFOS-1")},
        {"SR-Wh-DFOS-2", EventCounter("SR-Wh-DFOS-2")},
        // WZ off-shell
        // Inclusive SRs
      };
            
    private:

      // Struct to sort HEPUtils::Particles on pT in decending order
      struct ptComparison{
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;
      
      // Internally used Z-mass
      double mZ = 91.1876; // [GeV]

      
      #ifdef CHECK_CUTFLOW
      // Cut-flow variables
      string benchmark = BENCHMARK;
      size_t NCUTS=42;
      vector<double> _cutflow_GAMBIT{vector<double>(NCUTS)};
      vector<double> _cutflow_ATLAS{vector<double>(NCUTS)};
      vector<string> _cuts{vector<string>(NCUTS)};
      #endif
      
    public:
      
      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_3LEP_139invfb() {

        set_analysis_name("ATLAS_13TeV_3LEP_139invfb");
        set_luminosity(139.);

      }
      
      // Discards jets if they are within DeltaRMax of a lepton
      void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*> &jetvec, vector<const HEPUtils::Particle*> &lepvec, double DeltaRMax) {

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
      
      // Discards leptons if they are within DeltaRMax of a jet
      void LeptonJetOverlapRemoval(vector<const HEPUtils::Particle*> &lepvec, vector<const HEPUtils::Jet*> &jetvec, double DeltaRMax) {

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


      
      //
      // Main event analysis
      //
      void run(const HEPUtils::Event* event) {
        
        //
        // Baseline objects
        //

        // Get the missing energy in the event
        double met = event->met();
        HEPUtils::P4 metVec = event->missingmom();
        
        
        // Baseline electrons
        int nFilterLeptons = 0;  // This is just for checking ATLAS event generation
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 4.5 && fabs(electron->eta()) < 2.47){
            nFilterLeptons++;
            baselineElectrons.push_back(electron);
          }
        }
        // Apply electron reconstruction efficiency from 1908.00005
        ATLAS::applyElectronReconstructionEfficiency2020(baselineElectrons, "Candidate");
        // Baseline muons
        vector<const HEPUtils::Particle*> baselineMuons;
        int nHighEtaMuons = 0;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 3. && fabs(muon->eta()) < 2.5){
            baselineMuons.push_back(muon);
            nFilterLeptons++;
          }
          if (muon->pT() > 3. && fabs(muon->eta()) > 2.5 && fabs(muon->eta()) < 2.7){
            nHighEtaMuons++;
          }
        }
        // Apply muon ID efficiency from "Medium" criteria in 2012.00578
        ATLAS::applyMuonIDEfficiency2020(baselineMuons, "Medium");
        
        // Number of baseline leptons used in preselection
        // This also counts muons in 2.5 < |\eta| < 2.7
        int nBaselineLeptons = baselineElectrons.size() + baselineMuons.size() + nHighEtaMuons;
                
        // Baseline jets
        vector<const HEPUtils::Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.5 )
            baselineJets.push_back(jet);
        }

        
        //
        // Overlap removal
        //

        // Remove jets \Delta R < 0.2 from electrons
        JetLeptonOverlapRemoval(baselineJets, baselineElectrons, 0.2);
        // Remove leptons \Delta R < 0.4 from jets
        LeptonJetOverlapRemoval(baselineElectrons, baselineJets, 0.4);
        LeptonJetOverlapRemoval(baselineMuons, baselineJets, 0.4);
        
        
        //
        // Signal objects (and isolation)
        //
        
        // Apply cuts to get signal electrons
        // Apply electron ID efficiency from "Medium" criteria in 1908.00005
        ATLAS::applyElectronIDEfficiency2020(baselineElectrons, "Medium");
        // Apply electron isolation efficiency from "Tight" criteria in 1908.00005
        ATLAS::applyElectronIsolationEfficiency2020(baselineElectrons, "Tight");
        // Apply muon isolation efficiency from "Tight" criteria in 2012.00578
        ATLAS::applyMuonIsolationEfficiency2020(baselineMuons, "Tight");
        
        // Signal jets
        vector<const HEPUtils::Jet*> signalJets;
        for ( const HEPUtils::Jet* jet : baselineJets ) {
          if (fabs(jet->eta()) < 2.8 ){
            signalJets.push_back(jet);
          }
        }
        
        // Jet properties
        int njets = signalJets.size();
        double HT = scalarSumPt(signalJets);
        
       // b-jets
        double btag = 0.85; double cmisstag = 1/2.7; double misstag = 1./25.;
        int nb = 0;
        for ( const HEPUtils::Jet* jet : signalJets ) {
          // Kinematics criteria for candidate b-jets
          if ( fabs(jet->eta()) < 2.5 ){
            // Tag b-jet
            if( jet->btag() && random_bool(btag) ) nb++;
            // Misstag c-jet
            else if( !jet->btag() && jet->ctag() && random_bool(cmisstag) ) nb++;
            // Misstag light jet
            else if( !jet->btag() && !jet->ctag() && random_bool(misstag) ) nb++;
          }
        }
        
        
        // Joint vector for leptons
        vector<const HEPUtils::Particle*> leptons;
        leptons = baselineElectrons;
        leptons.insert(leptons.end(), baselineMuons.begin(), baselineMuons.end());
        // Sort leptons by pT
        sortByPt(leptons);
        size_t nLeptons = leptons.size();
        
        // Check lepton properties
        bool bpT1 = false; bool bpT2 = false; bool bpT3 = false;
        if(nLeptons == 3 && nBaselineLeptons == 3){
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
        
    
        
        //
        // Count signal region events
        //
        
        // Weights for trigger efficiency and MC to data comparison
        // Taken from WZ on-shell benchmark points (conservative choice)
        double weight_trigger_WZonshell = 0.98;
        double weight_trigger_Wh = 0.96;
        double weight_SR1_8 = 0.96;
        double weight_SR9_16 = 0.94;
        double weight_SR17_20 = 0.89;

        // First exclusive regions
        // Pre-selection for WZ on-shell SRs
        // TODO: Add trigger efficiency and MC to data ratio weight as a weight
//        double weight = event->weight();
        bool bPreselect = bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15 && mll > 75 && mll < 105;
        if(bPreselect){
          // Zero jet SRs
          if(njets == 0) {
            // Below does not work due to consrt nature of weight in event. Change?
            // weight *= weight_trigger_WZonshell*weight_SR1_8;
            // event->set_weight(weight);
            // OR, use EventCounter add_event(double w = 1.0, double werr = 0.0)
            // DANGER: This disregards event weight information from Event (!!!)
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
//            weight *= weight_trigger_WZonshell*weight_SR9_16;
//            event->set_weight(weight);
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
//            weight *= weight_trigger_WZonshell*weight_SR17_20;
//            event->set_weight(weight);
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
          if(benchmark ==  "WZ_300_200" || benchmark == "WZ_600_100"){
            if(
               (j==0) ||
               (j==1) ||
               (j==2  && nFilterLeptons > 1) ||
               (j==3  && bLeptons && met > 50) ||
               (j==4  && bLeptons && met > 50 && bSFOS)
               ) _cutflow_GAMBIT[j]++;
            if(
               (j==5  && bLeptons && met > 50 && bSFOS) ||
               (j==6  && bLeptons && met > 50 && bSFOS && nb == 0) ||
               (j==7  && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12) ||
               (j==8  && bLeptons && met > 50 && bSFOS && nb == 0 && mll > 12 && fabs(mlll-mZ) > 15) ||
               (j==9  && bPreselect)
               ) _cutflow_GAMBIT[j] += weight_trigger_WZonshell;
            if(
               (j==10 && bPreselect) ||
               (j==11 && bPreselect && njets == 0) ||
               (j==12 && bPreselect && njets == 0 && mT > 100 && mT < 160) ||
               (j==13 && bPreselect && njets == 0 && mT > 100 && mT < 160 && met > 50  && met < 100) ||
               (j==14 && bPreselect && njets == 0 && mT > 100 && mT < 160 && met > 100 && met < 150) ||
               (j==15 && bPreselect && njets == 0 && mT > 100 && mT < 160 && met > 150 && met < 200) ||
               (j==16 && bPreselect && njets == 0 && mT > 100 && mT < 160 && met > 200) ||
               (j==17 && bPreselect && njets == 0 && mT > 160) ||
               (j==18 && bPreselect && njets == 0 && mT > 160 && met > 50  && met < 150) ||
               (j==19 && bPreselect && njets == 0 && mT > 160 && met > 150 && met < 200) ||
               (j==20 && bPreselect && njets == 0 && mT > 160 && met > 200 && met < 350) ||
               (j==21 && bPreselect && njets == 0 && mT > 160 && met > 350) ||
               (j==22 && bPreselect && njets == 0 && mT > 100 && met > 50)
               ) _cutflow_GAMBIT[j] += weight_trigger_WZonshell*weight_SR1_8;
            if(
               (j==23 && bPreselect && njets > 0 && HT < 200) ||
               (j==24 && bPreselect && njets > 0 && HT < 200 && mT > 100 && mT < 160) ||
               (j==25 && bPreselect && njets > 0 && HT < 200 && mT > 100 && mT < 160 && met > 100 && met < 150) ||
               (j==26 && bPreselect && njets > 0 && HT < 200 && mT > 100 && mT < 160 && met > 150 && met < 250) ||
               (j==27 && bPreselect && njets > 0 && HT < 200 && mT > 100 && mT < 160 && met > 250 && met < 300) ||
               (j==28 && bPreselect && njets > 0 && HT < 200 && mT > 100 && mT < 160 && met > 300 ) ||
               (j==29 && bPreselect && njets > 0 && HT < 200 && mT > 160) ||
               (j==30 && bPreselect && njets > 0 && HT < 200 && mT > 160 && met > 50  && met < 150) ||
               (j==31 && bPreselect && njets > 0 && HT < 200 && mT > 160 && met > 150 && met < 250) ||
               (j==32 && bPreselect && njets > 0 && HT < 200 && mT > 160 && met > 250 && met < 400) ||
               (j==33 && bPreselect && njets > 0 && HT < 200 && mT > 160 && met > 400 )
               ) _cutflow_GAMBIT[j] += weight_trigger_WZonshell*weight_SR9_16;
            if(
               (j==34 && bPreselect && njets > 0 && HT > 200) ||
               (j==35 && bPreselect && njets > 0 && HT > 200 && HTlep < 350) ||
               (j==36 && bPreselect && njets > 0 && HT > 200 && HTlep < 350 && mT > 100) ||
               (j==37 && bPreselect && njets > 0 && HT > 200 && HTlep < 350 && mT > 100 && met > 150 && met < 200) ||
               (j==38 && bPreselect && njets > 0 && HT > 200 && HTlep < 350 && mT > 100 && met > 200 && met < 300) ||
               (j==39 && bPreselect && njets > 0 && HT > 200 && HTlep < 350 && mT > 100 && met > 300 && met < 400) ||
               (j==40 && bPreselect && njets > 0 && HT > 200 && HTlep < 350 && mT > 100 && met > 400 ) ||
               (j==41 && bPreselect && njets > 0 && mT > 100 && ( met > 100 || (mT > 160 && met > 50) || (HTlep < 350 && met > 150) ))  // TODO: Small bug here
               ) _cutflow_GAMBIT[j] += weight_trigger_WZonshell*weight_SR17_20;
          }
          if(benchmark == "Wh_190_60"){
            if(
            (j==0) ||
            (j==1) ||
            (j==2  && nFilterLeptons > 2) ||
            (j==3  && bLeptons && met > 50)
               ) _cutflow_GAMBIT[j]++;
            if(
            (j==4  && bLeptons && met > 50) ||
            (j==5  && bLeptons && met > 50 && nb == 0) ||
            (j==6  && bLeptons && met > 50 && nb == 0 && bSFOS) ||
            (j==7  && bLeptons && met > 50 && nb == 0 && bSFOS && mll > 12) ||
            (j==8  && bLeptons && met > 50 && nb == 0 && bSFOS && mll > 12 && fabs(mlll-mZ) > 15) ||
            (j==9  && bLeptons && met > 50 && nb == 0 && bSFOS && mll > 12 && fabs(mlll-mZ) > 15) ||
            (j==10 && bLeptons && met > 50 && nb == 0 && bSFOS && mll > 12 && fabs(mlll-mZ) > 15 && mll < 75) ||
            (j==11 && bLeptons && met > 50 && nb == 0 && bSFOS && mll > 12 && fabs(mlll-mZ) > 15 && mll < 75 && njets == 0) ||
            (j==12 && bLeptons && met > 50 && nb == 0 && bSFOS && mll > 12 && fabs(mlll-mZ) > 15 && mll < 75 && njets > 0)
               ) _cutflow_GAMBIT[j] += weight_trigger_Wh;
          }
        } // Ends loop over cuts
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
        cout << "Cut flow for " << benchmark << endl;
        
        double _xsec_model;
        double _lumi = luminosity();
        double _scale;
        double _scale_BR;
        // Z decay to leptons BR = 0.0335480+0.0335477+0.0334720=0.1005677
        // W decay to leptons BR = 0.1081014+0.1081011+0.1080222=0.3242247
        // SM h decay to WW (both leptonic), ZZ (both leptonic), \tau\tau BR = 0.3242*(0.2152*(0.3242)**2+0.02641*(0.1006)**2+0.06256) = 0.0277 ????
        double _BR_WZ_leptonic = 0.0327; // W and Z leptonic decays (& \tau leptonic decay)
        double _BR_Wh_leptonic = 0.0360; // W leptonic, SM Higgs to WW, ZZ and \tau \tau and leptonic decays
        //
        if(benchmark == "WZ_300_200"){
          _cutflow_ATLAS = {53784, 1760, 1322, 227, 226, 222, 209, 209, 203, 196, 186, 76.4, 26.7, 20.9, 4.86, 0.78, 0.14, 5.8, 4.64, 0.16, 0, 0, 31.4, 97.5, 29.6, 8.75, 3.46, 0.54, 0, 9.50, 7.19, 1.53, 0.09, 0, 22.2, 20.9, 10.8, 2.53, 3.12, 1.09, 1.13, 29.4};
          _cuts = {"Total events", "Total events x leptonic BR", "Total events x leptonic BR x lepton filter", "Leptons + ETmiss", "nSFOS", "Trigger", "n_bjets = 0", "m_ll > 12 GeV", "|m_3l-m_Z| > 15 GeV", "75 GeV < m_ll < 105 GeV", "\twith MC to data weight", "n_jets = 0", "\t100 GeV < m_T < 160 GeV", "\t\tSR^WZ-1", "\t\tSR^WZ-2", "\t\tSR^WZ-3", "\t\tSR^WZ-4", "\tm_T > 160 GeV", "\t\tSR^WZ-5", "\t\tSR^WZ-6", "\t\tSR^WZ-7", "\t\tSR^WZ-8", "SR^WZ_0j", "n_jets > 0, H_T < 200 GeV", "\t100 GeV < m_T < 160 GeV", "\t\tSR^WZ-9", "\t\tSR^WZ-10", "\t\tSR^WZ-11", "\t\tSR^WZ-12", "\tm_T > 160 GeV", "\t\tSR^WZ-13", "\t\tSR^WZ-14", "\t\tSR^WZ-15", "\t\tSR^WZ-16", "n_jets > 0, H_T > 200 GeV", "H_T^lep < 350 GeV", "\tm_T > 100 GeV", "\t\tSR^WZ-17", "\t\tSR^WZ-18", "\t\tSR^WZ-19", "\t\tSR^WZ-20", "SR^WZ_nj"
          };
          _xsec_model = 386.9;
          _scale = _xsec_model*_lumi/100000;
          _scale_BR = _scale*_BR_WZ_leptonic;
        }
        if(benchmark == "WZ_600_100"){
          _cutflow_ATLAS = {2799, 92, 69, 23.9, 23.7, 23.3, 21.9, 21.9, 21.7, 20.1, 19.2, 7.72, 0.90, 0.09, 0.11, 0.16, 0.54, 5.11, 0.37, 0.49, 2.21, 2.14, 6.11, 9.90, 1.19, 0.17, 0.32, 0.15, 0.38, 6.80, 0.49, 1.37, 2.77, 1.69, 2.40, 0.65, 0.47, 0.02, 0.11, 0.12, 0.13, 7.8};
          _cuts = {"Total events", "Total events x leptonic BR", "Total events x leptonic BR x lepton filter", "Leptons + ETmiss", "nSFOS", "Trigger", "n_bjets = 0", "m_ll > 12 GeV", "|m_3l-m_Z| > 15 GeV", "75 GeV < m_ll < 105 GeV", "\twith MC to data weight", "n_jets = 0", "\t100 GeV < m_T < 160 GeV", "\t\tSR^WZ-1", "\t\tSR^WZ-2", "\t\tSR^WZ-3", "\t\tSR^WZ-4", "\tm_T > 160 GeV", "\t\tSR^WZ-5", "\t\tSR^WZ-6", "\t\tSR^WZ-7", "\t\tSR^WZ-8", "SR^WZ_0j", "n_jets > 0, H_T < 200 GeV", "\t100 GeV < m_T < 160 GeV", "\t\tSR^WZ-9", "\t\tSR^WZ-10", "\t\tSR^WZ-11", "\t\tSR^WZ-12", "\tm_T > 160 GeV", "\t\tSR^WZ-13", "\t\tSR^WZ-14", "\t\tSR^WZ-15", "\t\tSR^WZ-16", "n_jets > 0, H_T > 200 GeV", "H_T^lep < 350 GeV", "\tm_T > 100 GeV", "\t\tSR^WZ-17", "\t\tSR^WZ-18", "\t\tSR^WZ-19", "\t\tSR^WZ-20", "SR^WZ_nj"
          };
          _xsec_model = 20.1372;
          _scale = _xsec_model*_lumi/100000;
          _scale_BR = _scale*_BR_WZ_leptonic;
        }
        if(benchmark == "Wh_190_60"){
          _cutflow_ATLAS = {303527, 10927, 1174, 192, 186, 171, 137, 133, 110, 104, 56.2, 22.3, 26.5};
          _cuts = {"Total events", "Total events x leptonic BR", "Total events x leptonic BR x lepton filter", "Leptons + ETmiss", "Trigger", "n_bjets = 0", "nSFOS > 0", "m_ll > 12 GeV", "|m_3l-m_Z| > 15 GeV", "\twith MC to data weight", "m_ll < 75 GeV", "n_jets = 0", "n_jets > 0"
          };
          _xsec_model = 2183.65;
          _scale = _xsec_model*_lumi/100000;
          _scale_BR = _scale*_BR_Wh_leptonic;
        }
        
        cout << "Event scaling factor: " << _scale_BR << endl;
        cout << fixed << setprecision(2);
        // Compare final event yield per cut
        cout << "    GAMBIT\t\tMC error\tATLAS\t\tRatio\t\tCut" <<endl;
        cout << 0 << ":  " << _cutflow_GAMBIT[0]*_scale << "\t\t" << 0 << "\t\t" << _cutflow_ATLAS[0] <<  "\t\t" << _cutflow_GAMBIT[0]*_scale/_cutflow_ATLAS[0]  << "\t\t" << _cuts[0] <<endl;
        cout << 1 << ":  " <<  _cutflow_GAMBIT[1]*_scale_BR << "\t\t" << 0 << "\t\t" << _cutflow_ATLAS[1] <<  "\t\t" << _cutflow_GAMBIT[1]*_scale_BR/_cutflow_ATLAS[1]  << "\t\t" << _cuts[1] <<endl;
        for (size_t i=2; i<NCUTS; i++) {
          cout << i << ":  " <<  _cutflow_GAMBIT[i]*_scale_BR << "\t\t" << sqrt(_cutflow_GAMBIT[i])*_scale_BR << "\t\t" << _cutflow_ATLAS[i] <<  "\t\t" << _cutflow_GAMBIT[i]*_scale_BR/_cutflow_ATLAS[i]  << "\t\t" << _cuts[i] <<endl;
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



/*
 
 Cut flow for WZ_300_200
 Event scaling factor: 0.00882
     GAMBIT    MC error  ATLAS    Ratio    Cut
 0:  53779.10    0    53784.00    1.00    Total events
 1:  1763.95    3.94    1760.00    1.00    Total events x leptonic BR
 2:  1316.94    3.41    1322.00    1.00    Total events x leptonic BR x lepton filter
 3:  250.74    1.49    227.00    1.10    Leptons + ETmiss
 4:  250.01    1.48    226.00    1.11    nSFOS
 5:  245.01    1.47    222.00    1.10    Trigger
 6:  230.30    1.43    209.00    1.10    n_bjets = 0
 7:  230.30    1.43    209.00    1.10    m_ll > 12 GeV
 8:  220.60    1.39    203.00    1.09    |m_3l-m_Z| > 15 GeV
 9:  211.67    1.37    196.00    1.08    75 GeV < m_ll < 105 GeV
 10:  203.20    1.34    186.00    1.09    MC to data weight
 11:  88.25    0.88    76.40    1.16    n_jets = 0
 12:  28.91    0.50    26.70    1.08      100 GeV < m_T < 160 GeV
 13:  22.71    0.45    20.90    1.09        SR^WZ-1
 14:  5.13    0.21    4.86    1.06        SR^WZ-2
 15:  0.84    0.09    0.78    1.07        SR^WZ-3
 16:  0.23    0.05    0.14    1.66        SR^WZ-4
 17:  6.12    0.23    5.80    1.06      m_T > 160 GeV
 18:  5.92    0.23    4.64    1.28        SR^WZ-5
 19:  0.16    0.04    0.16    0.99        SR^WZ-6
 20:  0.05    0.02    0.00    inf        SR^WZ-7
 21:  0.00    0.00    0.00    nan        SR^WZ-8
 22:  35.03    0.56    31.40    1.12    SR^WZ_0j
 23:  91.32    0.90    97.50    0.94    n_jets > 0, H_T < 200 GeV
 24:  28.83    0.50    29.60    0.97      100 GeV < m_T < 160 GeV
 25:  9.78    0.29    8.75    1.12        SR^WZ-9
 26:  3.79    0.18    3.46    1.10        SR^WZ-10
 27:  0.11    0.03    0.54    0.21        SR^WZ-11
 28:  0.10    0.03    0.00    inf        SR^WZ-12
 29:  8.99    0.28    9.50    0.95      m_T > 160 GeV
 30:  7.15    0.25    7.19    0.99        SR^WZ-13
 31:  1.82    0.13    1.53    1.19        SR^WZ-14
 32:  0.02    0.01    0.09    0.27        SR^WZ-15
 33:  0.00    0.00    0.00    nan        SR^WZ-16
 34:  20.10    0.42    22.20    0.91    n_jets > 0, H_T > 200 GeV
 35:  19.11    0.41    20.90    0.91    H_T^lep < 350 GeV
 36:  9.55    0.29    10.80    0.88      m_T > 100 GeV
 37:  2.02    0.13    2.53    0.80        SR^WZ-17
 38:  3.39    0.17    3.12    1.09        SR^WZ-18
 39:  1.58    0.12    1.09    1.45        SR^WZ-19
 40:  0.95    0.09    1.13    0.84        SR^WZ-20
 41:  31.49    0.53    29.40    1.07    SR^WZ_nj

 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-10__i9__signal: 125.58588
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-10__i9__signal_uncert: 5.8114216
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-11__i10__signal: 3.7648873
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-11__i10__signal_uncert: 1.0062085
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-12__i11__signal: 3.2270462
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-12__i11__signal_uncert: 0.93156801
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-13__i12__signal: 236.65006
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-13__i12__signal_uncert: 7.9774718
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-14__i13__signal: 60.238196
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-14__i13__signal_uncert: 4.0248338
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-15__i14__signal: 0.80676156
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-15__i14__signal_uncert: 0.465784
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-16__i15__signal: 0
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-16__i15__signal_uncert: 0
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-17__i16__signal: 70.726097
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-17__i16__signal_uncert: 4.361158
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-18__i17__signal: 118.59395
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-18__i17__signal_uncert: 5.6473309
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-19__i18__signal: 55.128707
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-19__i18__signal_uncert: 3.8503559
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-1__i0__signal: 736.03546
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-1__i0__signal_uncert: 14.068939
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-20__i19__signal: 33.077224
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-20__i19__signal_uncert: 2.9824728
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-2__i1__signal: 166.19288
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-2__i1__signal_uncert: 6.6852581
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-3__i2__signal: 27.160973
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-3__i2__signal_uncert: 2.7026178
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-4__i3__signal: 7.5297746
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-4__i3__signal_uncert: 1.4229936
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-5__i4__signal: 191.74033
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-5__i4__signal_uncert: 7.1807318
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-6__i5__signal: 5.1094899
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-6__i5__signal_uncert: 1.1721974
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-7__i6__signal: 1.6135231
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-7__i6__signal_uncert: 0.65871806
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-8__i7__signal: 0
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-8__i7__signal_uncert: 0
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-9__i8__signal: 323.78031
 0, 1: #LHC_signals @ColliderBit::calc_LHC_signals::ATLAS_13TeV_3LEP_139invfb__SR-WZ-9__i8__signal_uncert: 9.3311933

 Cut flow for WZ_600_100
 Event weight: 0.00184
 0:  2799.07    2799.00    1.00    Total events
 1:  91.81    92.00    1.00    Total events x leptonic BR
 2:  72.24    69.00    1.05    Total events x leptonic BR x lepton filter
 3:  26.00    23.90    1.09    Leptons + ETmiss
 4:  25.82    23.70    1.09    nSFOS
 5:  25.82    23.30    1.11    Trigger
 6:  24.28    21.90    1.11    n_bjets = 0
 7:  24.27    21.90    1.11    m_ll > 12 GeV
 8:  24.02    21.70    1.11    |m_3l-m_Z| > 15 GeV
 9:  21.67    20.10    1.08    75 < m_ll < 105
 10:  21.67    19.20    1.13    MC to data weight
 11:  9.60    7.72    1.24    n_jets = 0
 12:  1.32    0.90    1.47      100 < m_T < 160
 13:  0.10    0.09    1.14        SR^WZ-1
 14:  0.17    0.11    1.59        SR^WZ-2
 15:  0.22    0.16    1.37        SR^WZ-3
 16:  0.82    0.54    1.53        SR^WZ-4
 17:  6.40    5.11    1.25      m_T > 160 GeV
 18:  0.50    0.37    1.35        SR^WZ-5
 19:  0.58    0.49    1.19        SR^WZ-6
 20:  2.73    2.21    1.24        SR^WZ-7
 21:  2.59    2.14    1.21        SR^WZ-8
 22:  7.72    6.11    1.26    SR^WZ_0j
 23:  9.61    9.90    0.97    n_jets > 0, H_T < 200 GeV
 24:  1.20    1.19    1.01      100 < m_T < 160
 25:  0.17    0.17    0.97        SR^WZ-9
 26:  0.34    0.32    1.05        SR^WZ-10
 27:  0.15    0.15    0.97        SR^WZ-11
 28:  0.43    0.38    1.12        SR^WZ-12
 29:  6.43    6.80    0.95      m_T > 160 GeV
 30:  0.48    0.49    0.97        SR^WZ-13
 31:  1.43    1.37    1.04        SR^WZ-14
 32:  2.71    2.77    0.98        SR^WZ-15
 33:  1.81    1.69    1.07        SR^WZ-16
 34:  2.46    2.40    1.03    n_jets > 0, H_T > 200 GeV
 35:  0.70    0.65    1.07    H_T^lep < 350 GeV
 36:  0.49    0.47    1.04      m_T > 100 GeV
 37:  0.03    0.02    1.47        SR^WZ-17
 38:  0.11    0.11    1.00        SR^WZ-18
 39:  0.11    0.12    0.90        SR^WZ-19
 40:  0.19    0.13    1.48        SR^WZ-20
 41:  9.36    7.80    1.20    SR^WZ_nj
 
 

 */
