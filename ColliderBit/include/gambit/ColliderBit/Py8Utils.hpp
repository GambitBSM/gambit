#pragma once

#include "gambit/Elements/shared_types.hpp"
#include "HEPUtils/Event.h"
#include "HEPUtils/Vectors.h"
#include "HEPUtils/FastJet.h"
#include "MCUtils/PIDUtils.h"

namespace Gambit {
  namespace ColliderBit {

    //using namespace MCUtils;

    /// @name Converters to/from Pythia8's native 4-vector
    //@{

    inline FJNS::PseudoJet mk_pseudojet(const Pythia8::Vec4& p) {
      return FJNS::PseudoJet(p.px(), p.py(), p.pz(), p.e());
    }

    inline HEPUtils::P4 mk_p4(const Pythia8::Vec4& p) {
      const double m = p.mCalc();
      if (m < -5e-3) throw std::domain_error("Negative mass vector from Pythia8");
      return HEPUtils::P4::mkXYZM(p.px(), p.py(), p.pz(), (m > 0) ? m : 0);
    }

    inline HEPUtils::P4 mk_p4(const Pythia8::Particle& p) {
      const double m = p.m();
      if (m < -5e-3) throw std::domain_error("Negative mass Particle from Pythia8");
      return HEPUtils::P4::mkXYZM(p.px(), p.py(), p.pz(), (m > 0) ? m : 0);
    }

    inline Pythia8::Vec4 mk_vec4(const FJNS::PseudoJet& p) {
      Pythia8::Vec4 rtn;
      rtn.p(p.px(), p.py(), p.pz(), p.e());
      return rtn;
    }

    //@}


    /// @name Convenience functions on Py8 objects
    //@{

    inline double deltaPhi(const Pythia8::Vec4& a, const Pythia8::Vec4& b) {
      return HEPUtils::deltaphi(a.phi(), b.phi());
    }

    inline double deltaR(const Pythia8::Vec4& a, const Pythia8::Vec4& b) {
      const double deta = fabs(a.eta() - b.eta());
      const double dphi = deltaPhi(a, b);
      return deta*deta + dphi*dphi;
    }

    //@}


    /// @name Detailed Pythia8 event record walking/mangling functions
    //@{


    /// @todo Rewrite using the Py8 > 176 particle-based methods
    inline bool fromBottom(int n, const Pythia8::Event& evt) {
      // Root particle is invalid
      if (n == 0) return false;
      const Pythia8::Particle& p = evt[n];
      if (abs(p.id()) == 5 || MCUtils::PID::hasBottom(p.id())) return true;
      /// @todo What about partonic decays?
      if (p.isParton()) return false; // stop the walking at hadron level
      for (int m : p.motherList()) {
        if (fromBottom(m, evt)) return true;
      }
      return false;
    }


    /// @todo Rewrite using the Py8 > 176 particle-based methods
    inline bool fromTau(int n, const Pythia8::Event& evt) {
      // Root particle is invalid
      if (n == 0) return false;
      const Pythia8::Particle& p = evt[n];
      if (abs(p.id()) == 15) return true;
      if (p.isParton()) return false; // stop the walking at the end of the hadron level
      for (int m : p.motherList()) {
        if (fromTau(m, evt)) return true;
      }
      return false;
    }


    /// @todo Rewrite using the Py8 > 176 particle-based methods
    inline bool fromHadron(int n, const Pythia8::Event& evt) {
      // Root particle is invalid
      if (n == 0) return false;
      const Pythia8::Particle& p = evt[n];
      if (p.isHadron()) return true;
      if (p.isParton()) return false; // stop the walking at the end of the hadron level
      for (int m : p.motherList()) {
        if (fromHadron(m, evt)) return true;
      }
      return false;
    }


    inline bool isReplica(int n, const Pythia8::Event& evt) {
      // Root particle is invalid
      if (n == 0) return false;
      const Pythia8::Particle& p = evt[n];
      return p.daughter1() != 0 && p.daughter1() == p.daughter2();
    }


    inline void finalDescendants(int n, const Pythia8::Event& evt, std::vector<int>& rtn) {
      const Pythia8::Particle& p = evt[n];
      //assert(!p.isParton());
      if (p.isParton()) std::cerr << "PARTON IN DESCENDANT CHAIN FROM HADRON! NUM, ID = " << n << ", " << p.id() << endl;
      for (int m : evt.daughterList(n)) {
        if (evt[m].isFinal()) {
          rtn.push_back(m);
        } else {
          finalDescendants(m, evt, rtn);
        }
      }
    }


    inline bool isFinalB(int n, const Pythia8::Event& evt) {
      // Root particle is invalid
      if (n == 0) return false;
      // *This* particle must be a b or b-hadron
      if (!MCUtils::PID::hasBottom(evt[n].id())) return false;
      // Daughters must *not* include a b or b-hadron
      for (int m : evt.daughterList(n)) {
        if (MCUtils::PID::hasBottom(evt[m].id())) return false;
      }
      return true;
    }


    inline bool isFinalTau(int n, const Pythia8::Event& evt) {
      // Root particle is invalid
      if (n == 0) return false;
      // *This* particle must be a tau
      if (abs(evt[n].id()) != 15) return false;
      // Daughters must *not* include a tau
      for (int m : evt.daughterList(n)) {
        if (abs(evt[m].id()) == 15) return false;
      }
      return true;
    }


    inline bool isParton(int n, const Pythia8::Event& evt) {
      // Root particle is invalid
      if (n == 0) return false;
      // This particle must be a parton (could use Py8 P::isParton() + apid == 6?)
      int apid = abs(evt[n].id());
      if (!HEPUtils::in_closed_range(apid, 1, 6) && apid != 21) return false;
      return true;
    }


    inline bool isFinalParton(int n, const Pythia8::Event& evt) {
      // Root particle is invalid
      if (n == 0) return false;
      // Check if it's a parton at all & early exit
      if (!isParton(n, evt)) return false;
      // Daughters must *not* be partons
      for (int m : evt.daughterList(n)) {
        if (m == 0) continue; // 0 shouldn't be possible here, but just to be sure...
        if (isParton(m, evt)) return false;
      }
      return true;
    }


    inline bool isFinalPhoton(int n, const Pythia8::Event& evt) {
      // Root particle is invalid
      if (n == 0) return false;
      const Pythia8::Particle& p = evt[n];
      // Check if it's a photon at all & early exit
      if (p.id() != 22) return false;
      // Must have no daughters
      return evt.daughterList(n).empty();
    }


    inline bool isFinalLepton(int n, const Pythia8::Event& evt) {
      // Root particle is invalid
      if (n == 0) return false;
      const Pythia8::Particle& p = evt[n];
      // Check if it's a lepton at all (including taus and neutrinos) & early exit
      if (!HEPUtils::in_closed_range(abs(p.id()), 11, 16)) return false;
      // Must have no daughters
      return evt.daughterList(n).empty();
    }


    // inline std::vector<int> get_anaparticles(const Pythia8::Event& evt) {
    //   // Get the most physical b hadron and tau IDs
    //   std::vector<int> unstables;
    //   for (int n = 0; n < evt.size(); ++n) {
    //     if (isFinalB(n, evt)) unstables.push_back(n);
    //     if (isFinalTau(n, evt)) unstables.push_back(n);
    //   }
    //   // Identify the final state particles from those decays
    //   std::vector<int> rmparticles;
    //   // for (int n : unstables) finalDescendants(n, evt, rmparticles);
    //   for (size_t i = 0; i < unstables.size(); ++i) finalDescendants(unstables[i], evt, rmparticles);
    //   // Identify all final state particles, except those from b and tau decays where the parents are used
    //   std::vector<int> rtn = unstables;
    //   for (int n = 0; n < evt.size(); ++n) {
    //     if (!evt[n].isFinal()) continue;
    //     if (find(rmparticles.begin(), rmparticles.end(), n) == rmparticles.end()) rtn.push_back(n);
    //   }
    //   sort(rtn.begin(), rtn.end());
    //   return rtn;
    // }

    //@}






    // /// Fill a Gambit::Event from a Pythia8 event
    // inline void fillGambitEvent(const Pythia8::Event& pevt, HEPUtils::Event& gevt) {
    //   Pythia8::Vec4 ptot;
    //   std::vector<FJNS::PseudoJet> jetparticles;
    //   std::vector<FJNS::PseudoJet> bhadrons, taus;
    //
    //   // Make a first pass to gather unstable final B hadrons and taus
    //   for (int i = 0; i < pevt.size(); ++i) {
    //     const Pythia8::Particle& p = pevt[i];
    //
    //     // Find last b-hadrons in b decay chains as the best proxy for b-tagging
    //     if (isFinalB(i, pevt)) bhadrons.push_back(mk_pseudojet(p.p()));
    //
    //     // Find last tau in tau replica chains as a proxy for tau-tagging
    //     // Also require that the tau are prompt
    //     /// @todo Only accept hadronically decaying taus?
    //     if (isFinalTau(i, pevt) && !fromHadron(i, pevt)) {
    //       taus.push_back(mk_pseudojet(p.p()));
    //       HEPUtils::Particle* gp = new HEPUtils::Particle(mk_p4(p.p()), p.id());
    //       gp->set_prompt();
    //       gevt.add_particle(gp); // Will be automatically categorised
    //     }
    //   }
    //
    //   for (int i = 0; i < pevt.size(); ++i) {
    //     const Pythia8::Particle& p = pevt[i];
    //
    //     // Only consider final state particles within ATLAS/CMS acceptance
    //     if (!p.isFinal()) continue;
    //     if (std::abs(p.eta()) > 5.0) continue;
    //     // Add to total final state momentum
    //     ptot += p.p();
    //
    //     // Promptness: for leptons and photons we're only interested if they don't come from hadron/tau decays
    //     /// @todo Don't exclude tau decay products, apparently: ATLAS treats them as jets
    //     const bool prompt = !fromHadron(i, pevt) && !fromTau(i, pevt);
    //
    //     if (prompt) {
    //       HEPUtils::Particle* gp = new HEPUtils::Particle(mk_p4(p.p()), p.id());
    //       gp->set_prompt();
    //       gevt.add_particle(gp); // Will be automatically categorised
    //     } else {
    //       jetparticles.push_back(mk_pseudojet(p.p()));
    //     }
    //
    //   }
    //
    //   // Jet finding
    //   // Currently hard-coded to use anti-kT R=0.4 jets above 30 GeV
    //   const FJNS::JetDefinition jet_def(FJNS::antikt_algorithm, 0.4);
    //   FJNS::ClusterSequence cseq(jetparticles, jet_def);
    //   std::vector<FJNS::PseudoJet> pjets = sorted_by_pt(cseq.inclusive_jets(30));
    //
    //   // Do jet b-tagging, etc. and add to the Event
    //   for (auto& pj : pjets) {
    //     bool isB = false;
    //     for (auto& pb : bhadrons) {
    //       if (pj.delta_R(pb) < 0.3) {
    //         isB = true;
    //         break;
    //       }
    //     }
    //     /// Add to the event
    //     const P4 p4 = mk_p4(pj);
    //     gevt.add_jet(new HEPUtils::Jet(p4, isB));
    //   }
    //
    //   // MET (not equal to sum of prompt invisibles)
    //   gevt.set_missingmom(-mk_p4(ptot));
    // }

  }
}
