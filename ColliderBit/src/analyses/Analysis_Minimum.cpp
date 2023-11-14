#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"

namespace Gambit
{
  namespace ColliderBit
  {
    using namespace std;


    /// Basic analysis code for copying
    class Analysis_Minimum : public Analysis
    {
    private:

    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_Minimum()
      {

        // Signal region counter
        _counters["SR"] = EventCounter("SR");

        // Set the analysis name
        set_analysis_name("Minimum");

        // Set the LHC luminosity
        set_luminosity(20.3);


      }


      void run(const HEPUtils::Event* event)
      {

        // Get the missing energy in the event
        double met = event->met();

        // Now define vectors of baseline objects,  including:
        // - retrieval of electron, muon and jets from the event)
        // - application of basic pT and eta cuts

        // Baseline electrons
        vector<const HEPUtils::Particle*> baselineElectrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && fabs(electron->eta()) < 2.47) baselineElectrons.push_back(electron);
        }

        // Baseline muons
        vector<const HEPUtils::Particle*> baselineMuons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && fabs(muon->eta()) < 2.4) baselineMuons.push_back(muon);
        }

        // Baseline jets
        vector<const HEPUtils::Jet*> baselineJets;
        for (const HEPUtils::Jet* jet : event->jets()) {
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

        if((nElectrons+nMuons)==0 && nJets==2 && met>150.) _counters["SR"].add_event(event);

      }


      void collect_results() {

        // Now fill a results object with the result for our signal region
        // We have made up a number of observed events
        // We have also made up a number of predicted background events (with a made up uncertainty)

        // add_result(SignalRegionData(_counters["SR label"], n_obs, {n_bkg, n_bkg_err}));
        add_result(SignalRegionData(_counters["SR"], 100., {95., 9.5}));
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
      }

      ///////////////////

    };

    DEFINE_ANALYSIS_FACTORY(Minimum)

  }
}
