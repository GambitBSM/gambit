#include "gambit/ColliderBit/analyses/BaseAnalysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

namespace Gambit {
  namespace ColliderBit {
    using namespace std;


    /// Basic analysis code for copying
    class Analysis_Minimum : public HEPUtilsAnalysis {
    private:

      // Variables to hold the number of events passing signal region cuts
      double _numSR;

    public:

      Analysis_Minimum() {

        // Set the analysis name
        set_analysis_name("Minimum");

        // Set the LHC luminosity
        set_luminosity(20.3);

        // Set number of events passing cuts to zero upon initialisation
        _numSR = 0;


      }


      void analyze(const HEPUtils::Event* event) {
        HEPUtilsAnalysis::analyze(event);

        // Get the missing energy in the event
        double met = event->met();

        // Now define vectors of baseline objects,  including:
        // - retrieval of electron, muon and jets from the event)
        // - application of basic pT and eta cuts
        vector<HEPUtils::Particle*> baselineElectrons;
        for (HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && fabs(electron->eta()) < 2.47) baselineElectrons.push_back(electron);
        }
        vector<HEPUtils::Particle*> baselineMuons;
        for (HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && fabs(muon->eta()) < 2.4) baselineMuons.push_back(muon);
        }
        vector<HEPUtils::Jet*> baselineJets;
        for (HEPUtils::Jet* jet : event->jets()) {
          if (jet->pT() > 20. && fabs(jet->eta()) < 4.5) baselineJets.push_back(jet);
        }

        // Could add ATLAS style overlap removal here
        // See Analysis_ATLAS_0LEP_20invfb for example

        // Could add ATLAS or CMS efficiencies here
        // See Analysis_ATLAS_2LEPEW_20invfb.cpp for an example

        int nElectrons = baselineElectrons.size();
        int nMuons = baselineMuons.size();
        int nJets = baselineJets.size();

        std::cerr << "nElectrons " << nElectrons << " nMuons " << nMuons << " nJets " << nJets << " met " << met << std::endl;

        // Increment number of events passing signal region cuts
        // Dummy signal region: need 2 jets, met > 150 and no leptons

        if((nElectrons+nMuons)==0 && nJets==2 && met>150.)_numSR++;

      }


      void add(BaseAnalysis* other) {
        // The base class add function handles the signal region number and total # events combination across threads
        HEPUtilsAnalysis::add(other);

        Analysis_Minimum* specificOther = dynamic_cast<Analysis_Minimum*>(other);

        // Here we will add the subclass member variables:
        _numSR += specificOther->_numSR;
      }


      void collect_results() {

        // Now fill a results object with the result for our signal region
        // We have made up a number of observed events
        // We have also made up a number of predicted background events (with a made up uncertainty)
        SignalRegionData results_SR;
        results_SR.sr_label = "SR"; // label must be unique for each signal region
        results_SR.n_observed = 100.; // set number of observed events (in LHC paper)
        results_SR.n_background = 95.; // set number of predicted background events (in LHC paper)
        results_SR.background_sys = 9.5; // set background uncertainty (in LHC paper)
        results_SR.signal_sys = 0.; // set signal uncertainty
        results_SR.n_signal = _numSR; // set this to number of signal events incremented in the analysis above
        add_result(results_SR);

      }


    protected:
      void clear() {
        _numSR = 0;
      }

      ///////////////////

    };

    DEFINE_ANALYSIS_FACTORY(Minimum)

  }
}
