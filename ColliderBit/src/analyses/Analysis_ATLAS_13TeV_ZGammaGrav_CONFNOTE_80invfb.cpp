#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/ATLASEfficiencies.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"
using namespace std;

namespace Gambit {
  namespace ColliderBit {


    /// @brief ATLAS ZH(->photon+gravitino) (79.8 fb^-1)
    ///
    /// Based on:
    ///  - https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2018-019/
    ///  - https://cds.cern.ch/record/2621481/files/ATLAS-CONF-2018-019.pdf
    ///
    /// @author Andy Buckley
    ///
    /// @note Conservative underestimate of yield in benchmark point cutflow 5.2 vs 8.7
    /// passing all cuts: underestimation of MET and satisfaction of angular/balance cuts.
    /// Adding MET smearing doesn't appear to have helped.
    ///
    class Analysis_ATLAS_13TeV_ZGammaGrav_CONFNOTE_80invfb : public Analysis {
    public:

      // Required detector sim
      static constexpr const char* detector = "ATLAS";

      Analysis_ATLAS_13TeV_ZGammaGrav_CONFNOTE_80invfb() {
        set_analysis_name("ATLAS_13TeV_ZGammaGrav_CONFNOTE_80invfb");
        set_luminosity(79.8);
        analysis_specific_reset();
      }


      void run(const Event* event) {

        // Electrons
        ParticlePtrs electrons;
        for (Particle* e : event->electrons()) {
          const bool crack = e->abseta() > 1.37 && e->abseta() < 1.52;
          if (e->pT() > 10. && e->abseta() < 2.47 && !crack)
            electrons.push_back(e);
        }

        // Apply electron efficiency
        ATLAS::applyElectronEff(electrons);

        // Apply medium electron selection
        ATLAS::applyMediumIDElectronSelection(electrons);

        // Muons
        // NB. medium muon ID for pT > 10 ~ 99%: https://cds.cern.ch/record/2047831/files/ATL-PHYS-PUB-2015-037.pdf
        ParticlePtrs muons;
        for (Particle* m : event->muons())
          if (m->pT() > 10. && m->abseta() < 2.7 && random_bool(0.99))
            muons.push_back(m);

        // Apply muon efficiency
        ATLAS::applyMuonEff(muons);

        // Photons
        ParticlePtrs photons;
        for (Particle* y : event->photons())
          if (y->pT() > 20.)
            photons.push_back(y);
        ATLAS::applyPhotonEfficiencyR2(photons);

        // Jets
        JetPtrs jets;
        for (Jet* j : event->jets())
          if (j->pT() > 20. && j->absrap() < 4.4)
            jets.push_back(j);

        // cout <<  "#J = " << jets.size()
        //      << " #Y = " << photons.size()
        //      << " #E = " << electrons.size()
        //      << " #M = " << muons.size()
        //      << endl;

        // Overlap removal
        removeOverlap(jets, electrons, 0.2);
        removeOverlap(electrons, jets, 0.4);
        removeOverlap(electrons, jets, 0.4);
        removeOverlap(photons, electrons, 0.4);
        removeOverlap(photons, muons, 0.4);
        removeOverlap(jets, photons, 0.4);

        // Put objects in pT order
        sortByPt(jets);
        sortByPt(electrons);
        sortByPt(muons);
        sortByPt(photons);

        // Missing energy
        double ht = 0;
        for (const Particle* p : event->visible_particles()) ht += p->pT();
        P4 pmiss = event->missingmom();
        ATLAS::smearMET(pmiss, ht);
        const double met = pmiss.pT();


        /////////////////

        size_t ncut = 0;

        // Find the Z system
        if (electrons.size() + muons.size() != 2) return; //< must be exactly two leptons
        if (!electrons.empty() && !muons.empty()) return; //< the two leptons must be same-flavour
        const ParticlePtrs& leps = electrons.empty() ? muons : electrons;

        // The dilepton mass must be within 10 GeV of the Z mass
        const P4 pZ = leps[0]->mom() + leps[1]->mom();
        if (fabs(pZ.m() - 91.2) > 10.) return;
        cutflow[ncut++] += 1;

        // There must be a prompt photon with pT > 25 GeV
        if (photons.empty()) return;
        if (photons[0]->pT() < 25) return;
        cutflow[ncut++] += 1;

        // MET and jet requirements
        if (met < 95) return;
        if (!jets.empty() && jets[0]->pT() > 30) return;
        cutflow[ncut++] += 1;

        // Require separation of the Z and the MET+photon(s) systems
        const P4 pYMET = pmiss + photons[0]->mom() +
          (photons.size() > 1 ? photons[1]->mom() : P4());
        if (fabs(pZ.pT()-pYMET.pT())/pYMET.pT() > 0.2) return;
        cutflow[ncut++] += 1;
        if (deltaPhi(pZ, pYMET) < 2.8) return;
        cutflow[ncut++] += 1;

        // Check lepton pTs and require small delta_phi
        if (leps[0]->pT() < 25 || leps[1]->pT() < 20) return;
        if (deltaPhi(leps[0]->mom(), leps[1]->mom()) > 1.4) return;
        cutflow[ncut++] += 1;

        // Signal count
        nsig += 1;

      }

      /// Combine the variables of another copy of this analysis (typically on another thread) into this one.
      void combine(const Analysis* other)
      {
        const Analysis_ATLAS_13TeV_ZGammaGrav_CONFNOTE_80invfb* specificOther
          = dynamic_cast<const Analysis_ATLAS_13TeV_ZGammaGrav_CONFNOTE_80invfb*>(other);
        for (size_t j = 0; j < NCUTS; ++j) cutflow[j] += specificOther->cutflow[j];
        nsig += specificOther->nsig;
      }


      void collect_results() {

        SignalRegionData results;
        results.sr_label = "SR";
        results.n_observed = 3.;
        results.n_background = 2.1;
        results.background_sys = 0.5;
        results.signal_sys = 0.;
        results.n_signal = nsig;
        add_result(results);

        cout << "\nCUTFLOW" << endl;
        const string cutnames[NCUTS] = {"mll near mZ", "y1 > 25 GeV", "MET > 95 GeV", "ZH pT balance", "ZH dphi", "ll dphi"};
        const double sf_cutflow = 85.92 / cutflow[0];
        for (size_t i = 0; i < NCUTS; ++i) cout << i+1 << ". " << cutflow[i] * sf_cutflow << " (" << cutnames[i] << ")" << endl;

      }


      void analysis_specific_reset() {
        nsig = 0;
        for (size_t i = 0; i < NCUTS; ++i) cutflow[i] = 0;
      }


    private:

      // Numbers passing cuts
      int nsig = 0;

      // Cut flow
      const static int NCUTS = 6;
      double cutflow[NCUTS];
      // vector<string> cutFlowVector_str;

    };



    DEFINE_ANALYSIS_FACTORY(ATLAS_13TeV_ZGammaGrav_CONFNOTE_80invfb);


  }
}
