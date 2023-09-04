// -*- C++ -*-
//
// This file is part of MCUtils -- https://bitbucket.org/andybuckley/mcutils
// Copyright (C) 2013-2016 Andy Buckley <andy.buckley@cern.ch>
//
// Embedding of MCUtils code in other projects is permitted provided this
// notice is retained and the MCUtils namespace and include path are changed.
//
#pragma once

#if __cplusplus <= 199711L
#error "This library needs at least a C++11 compliant compiler: are you using -std=c++11?"
#endif

/// @file Functions for filtering and classifying HepMC record contents
/// @author Andy Buckley <andy.buckley@cern.ch>
/// @author Nataliia Kondrashova <Nataliia.Kondrashova@cern.ch>

#include "HepMC3/GenEvent.h"
#include <vector>
#include <functional>

#include "MCUtils/HepMCEventUtils.h"
#include "MCUtils/PIDUtils.h"

// Macro to map HepMC functions to PID:: functions of the same name
#define HEPMC_TO_PID_FN(fname) fname (const HepMC3::GenParticle* p) { return PID:: fname (p->pdg_id()); }

namespace MCUtils {

  using HEPUtils::in_range;

  // Fwd declaration
  bool _isDecayedHFHadronOrTau(const HepMC3::GenParticle* p);


  /// @name GenParticle classifier functions
  //@{

  /// Convenient type name for a generic classifier function / function object
  typedef std::function<bool(const HepMC3::GenParticle*)> PClassifier;


  /// Is this particle species charged?
  inline bool HEPMC_TO_PID_FN(isCharged)

  /// Is this particle species neutral?
  inline bool HEPMC_TO_PID_FN(isNeutral)


  /// Is this a neutrino?
  inline bool HEPMC_TO_PID_FN(isNeutrino)

  /// Determine if the PID is that of a charged lepton
  inline bool HEPMC_TO_PID_FN(isChLepton)

  /// Determine if the PID is that of a photon
  inline bool HEPMC_TO_PID_FN(isPhoton)

  /// Determine if the PID is that of an electron or positron
  inline bool HEPMC_TO_PID_FN(isElectron)

  /// Determine if the PID is that of an muon or antimuon
  inline bool HEPMC_TO_PID_FN(isMuon)

  /// Determine if the PID is that of an tau or antitau
  inline bool HEPMC_TO_PID_FN(isTau)

  /// Determine if the PID is that of a hadron
  inline bool HEPMC_TO_PID_FN(isHadron)

  /// Determine if the PID is that of a meson
  inline bool HEPMC_TO_PID_FN(isMeson)

  /// Determine if the PID is that of a baryon
  inline bool HEPMC_TO_PID_FN(isBaryon)

  /// Determine if the PID is that of a quark
  inline bool HEPMC_TO_PID_FN(isQuark)

  /// Determine if the PID is that of a gluon
  inline bool HEPMC_TO_PID_FN(isGluon)

  /// Determine if the PID is that of a parton (quark or gluon)
  inline bool HEPMC_TO_PID_FN(isParton)



  /// Determine if the PID is that of a W+
  inline bool HEPMC_TO_PID_FN(isWplus)

  /// Determine if the PID is that of a W-
  inline bool HEPMC_TO_PID_FN(isWminus)

  /// Determine if the PID is that of a W+-
  inline bool HEPMC_TO_PID_FN(isW)

  /// Determine if the PID is that of a Z0
  inline bool HEPMC_TO_PID_FN(isZ)

  /// Determine if the PID is that of an SM/lightest SUSY Higgs
  inline bool HEPMC_TO_PID_FN(isHiggs)

  /// Determine if the PID is that of a t/tbar
  inline bool HEPMC_TO_PID_FN(isTop)


  /// Determine if the particle is a heavy flavour hadron or parton
  inline bool HEPMC_TO_PID_FN(isHeavyFlavour)

  /// Determine if the PID is that of a heavy parton (c,b,t)
  inline bool HEPMC_TO_PID_FN(isHeavyParton)

  /// Determine if the PID is that of a light parton (u,d,s)
  inline bool HEPMC_TO_PID_FN(isLightParton)


  /// Determine if the PID is that of a heavy flavour (b or c) meson
  inline bool HEPMC_TO_PID_FN(isHeavyMeson)

  /// Determine if the PID is that of a heavy flavour (b or c) baryon
  inline bool HEPMC_TO_PID_FN(isHeavyBaryon)

  /// Determine if the PID is that of a heavy flavour (b or c) hadron
  inline bool HEPMC_TO_PID_FN(isHeavyHadron)


  /// Determine if the PID is that of a light flavour (not b or c) meson
  inline bool HEPMC_TO_PID_FN(isLightMeson)

  /// Determine if the PID is that of a light flavour (not b or c) baryon
  inline bool HEPMC_TO_PID_FN(isLightBaryon)

  /// Determine if the PID is that of a light flavour (not b or c) hadron
  inline bool HEPMC_TO_PID_FN(isLightHadron)


  /// Determine if the PID is that of a b-meson.
  inline bool HEPMC_TO_PID_FN(isBottomMeson)

  /// Determine if the PID is that of a b-baryon.
  inline bool HEPMC_TO_PID_FN(isBottomBaryon)

  /// Determine if the PID is that of a b-hadron.
  inline bool HEPMC_TO_PID_FN(isBottomHadron)


  /// @brief Determine if the PID is that of a c-meson.
  ///
  /// Specifically, the _heaviest_ quark is a c: a B_c is a b-meson and NOT a c-meson.
  /// Charmonia (closed charm) are counted as c-mesons here.
  inline bool HEPMC_TO_PID_FN(isCharmMeson)

  /// @brief Determine if the PID is that of a c-baryon.
  ///
  /// Specifically, the _heaviest_ quark is a c: a baryon containing a b & c
  /// is a b-baryon and NOT a c-baryon. To test for the simpler case, just use
  /// a combination of hasCharm() and isBaryon().
  inline bool HEPMC_TO_PID_FN(isCharmBaryon)

  /// Determine if the PID is that of a c-hadron.
  inline bool HEPMC_TO_PID_FN(isCharmHadron)


  /// Determine if the PID is that of a strange meson
  inline bool HEPMC_TO_PID_FN(isStrangeMeson)

  /// Determine if the PID is that of a strange baryon
  inline bool HEPMC_TO_PID_FN(isStrangeBaryon)

  /// Determine if the PID is that of a strange hadron
  inline bool HEPMC_TO_PID_FN(isStrangeHadron)



  /// Is this a pomeron, odderon, or generic reggeon?
  inline bool HEPMC_TO_PID_FN(isReggeon)

  /// Determine if the PID is that of a diquark (used in hadronization models)
  inline bool HEPMC_TO_PID_FN(isDiquark)

  /// Determine if the PID is that of a pentaquark (hypothetical hadron)
  inline bool HEPMC_TO_PID_FN(isPentaquark)

  /// Is this a fundamental SUSY particle?
  inline bool HEPMC_TO_PID_FN(isSUSY)

  /// Is this an R-hadron?
  inline bool HEPMC_TO_PID_FN(isRhadron)

  /// Is this a technicolor particle?
  inline bool HEPMC_TO_PID_FN(isTechnicolor)

  /// Is this an excited (composite) quark or lepton?
  inline bool HEPMC_TO_PID_FN(isExcited)

  /// Is this a Kaluza-Klein excitation?
  inline bool HEPMC_TO_PID_FN(isKK)

  /// Is this a graviton?
  inline bool HEPMC_TO_PID_FN(isGraviton)

  /// Is this a BSM particle (including graviton)?
  inline bool HEPMC_TO_PID_FN(isBSM)



  /// Determine if the PID is in the generator-specific range
  inline bool HEPMC_TO_PID_FN(isGenSpecific)

  /// Determine if the PID is that of an EW scale resonance
  inline bool HEPMC_TO_PID_FN(isResonance)

  /// Check the PID for usability in transport codes like Geant4
  inline bool HEPMC_TO_PID_FN(isTransportable)



  /// Does this particle contain an up quark?
  inline bool HEPMC_TO_PID_FN(hasUp)

  /// Does this particle contain a down quark?
  inline bool HEPMC_TO_PID_FN(hasDown)

  /// Does this particle contain a strange quark?
  inline bool HEPMC_TO_PID_FN(hasStrange)

  /// Does this particle contain a charm quark?
  inline bool HEPMC_TO_PID_FN(hasCharm)

  /// Does this particle contain a bottom quark?
  inline bool HEPMC_TO_PID_FN(hasBottom)

  /// Does this particle contain a top quark?
  inline bool HEPMC_TO_PID_FN(hasTop)


  /// Does this particle interact strongly?
  inline bool HEPMC_TO_PID_FN(isStrongInteracting)

  /// Does this particle interact electromagnetically?
  inline bool HEPMC_TO_PID_FN(isEMInteracting)

  /// Does this particle interact weakly?
  inline bool HEPMC_TO_PID_FN(isWeakInteracting)


  /// jSpin returns 2J+1, where J is the total spin
  inline int HEPMC_TO_PID_FN(jSpin)

  /// sSpin returns 2S+1, where S is the spin
  inline int HEPMC_TO_PID_FN(sSpin)

  /// lSpin returns 2L+1, where L is the orbital angular momentum
  inline int HEPMC_TO_PID_FN(lSpin)


  /// Return 3 times the charge (3 x quark charge is an int)
  inline int HEPMC_TO_PID_FN(threeCharge)

  /// Return the charge
  inline double HEPMC_TO_PID_FN(charge)


  /// @brief Is this particle the first in the 'decay' chain to match property F?
  ///
  /// i.e. classifier(const GenParticle* p) is true, and p has no parents which match F
  template <typename F>
  inline bool isFirstWith(const HepMC3::GenParticle* p, const F& classifier) {
    if (!classifier(p)) return false; // p doesn't have property F so it can't be the first particle with it
    if (!p->production_vertex()) return true; // p has no parents, so it's the first
    for (const HepMC3::GenParticle* parent : const_parents(p->production_vertex())) {
      if (classifier(parent)) return false; // if its parent has property F, p can't be the first
    }
    return true; // p has F and no parents do
  }

  /// @brief Is this particle the last in the 'decay' chain to match property F?
  ///
  /// i.e. classifier(const GenParticle* p) is true, and p has no children which match F
  template <typename F>
  inline bool isLastWith(const HepMC3::GenParticle* p, const F& classifier) {
    if (!classifier(p)) return false; // p doesn't have property F so it can't be the last particle with it
    if (!p->end_vertex()) return true; // p has no children, so it's the last
    for (const HepMC3::GenParticle* child : const_children(p->end_vertex())) {
      if (classifier(child)) return false; // if its child has property F, p can't be the first
    }
    return true; // p has F and no children do
  }


  /// @brief Is this particle the first of its type in the 'decay' chain?
  ///
  /// i.e. it has no parents with the same PID
  inline bool isFirstReplica(const HepMC3::GenParticle* p) {
    /// @todo Rewrite with isFirstWith and a lambda based on matching p->pdg_id
    if (!p->production_vertex()) return true;
    bool isfirst = true;
    for (const HepMC3::GenParticle* m : const_parents(p->production_vertex())) {
      if (m->pdg_id() == p->pdg_id()) {
        isfirst = false;
        break;
      }
    }
    return isfirst;
  }

  /// @brief Is this particle the last of its type in the 'decay' chain?
  ///
  /// i.e. it has no daughters with the same PID
  inline bool isLastReplica(const HepMC3::GenParticle* p) {
    /// @todo Rewrite with isLastWith and a lambda based on matching p->pdg_id
    if (!p->end_vertex()) return true;
    bool islast = true;
    for (const HepMC3::GenParticle* d : const_children(p->end_vertex())) {
      if (d->pdg_id() == p->pdg_id()) {
        islast = false;
        break;
      }
    }
    return islast;
  }




  /// A function object with state of the status code to be tested for
  /// @todo Generalise to allow comparison to multiple statuses
  struct HasStatus {
    HasStatus(int status) : status(status) { }
    bool operator()(const HepMC3::GenParticle* p) {
      return p->status() == status;
    }
    int status;
  };

  /// A function object with state of the PID codes to be tested for
  struct HasPID {
    HasPID(long pid) { pids.push_back(pid); }
    HasPID(const std::vector<long>& pids) : pids(pids) { }
    bool operator()(const HepMC3::GenParticle* p) {
      return std::find(pids.begin(), pids.end(), p->pdg_id()) != pids.end();
    }
    std::vector<long> pids;
  };

  /// A function object with state of the PID codes to be tested for (including antiparticles)
  struct HasAbsPID {
    HasAbsPID(long pid) { pids.push_back(pid); }
    HasAbsPID(const std::vector<long>& pids) : pids(pids) { }
    bool operator()(const HepMC3::GenParticle* p) {
      return (std::find(pids.begin(), pids.end(), p->pdg_id()) != pids.end()) ||
        (std::find(pids.begin(), pids.end(), -p->pdg_id()) != pids.end());
    }
    std::vector<long> pids;
  };


  /// @todo Specify and handle units
  inline bool ptLess(const HepMC3::GenParticle* p, double ptmax) {
    return p->momentum().perp() < ptmax;
  }
  /// @todo Specify and handle units
  struct PtLess {
    PtLess(double ptmax) : ptmax(ptmax) { }
    bool operator()(const HepMC3::GenParticle* p) {
      return ptLess(p, ptmax);
    }
    double ptmax;
  };


  /// @todo Specify and handle units
  inline bool ptGtr(const HepMC3::GenParticle* p, double ptmin) {
    return p->momentum().perp() >= ptmin;
  }
  /// @todo Specify and handle units
  struct PtGtr {
    PtGtr(double ptmin) : ptmin(ptmin) { }
    bool operator()(const HepMC3::GenParticle* p) {
      return ptGtr(p, ptmin);
    }
    double ptmin;
  };


  inline bool inEtaRange(const HepMC3::GenParticle* p, double etamin, double etamax) {
    return HEPUtils::in_range(eta(p->momentum()), etamin, etamax);
  }
  struct InEtaRange {
    InEtaRange(double etamin, double etamax) : etamin(etamin), etamax(etamax) { }
    bool operator()(const HepMC3::GenParticle* p) {
      return inEtaRange(p, etamin, etamax);
    }
    double etamin, etamax;
  };
  struct NotInEtaRange {
    NotInEtaRange(double etamin, double etamax) : etamin(etamin), etamax(etamax) { }
    bool operator()(const HepMC3::GenParticle* p) {
      return !inEtaRange(p, etamin, etamax);
    }
    double etamin, etamax;
  };


  inline bool inRapRange(const HepMC3::GenParticle* p, double ymin, double ymax) {
    return HEPUtils::in_range(rap(p->momentum()), ymin, ymax);
  }
  struct InRapRange {
    InRapRange(double ymin, double ymax) : ymin(ymin), ymax(ymax) { }
    bool operator()(const HepMC3::GenParticle* p) {
      return inRapRange(p, ymin, ymax);
    }
    double ymin, ymax;
  };
  struct NotInRapRange {
    NotInRapRange(double ymin, double ymax) : ymin(ymin), ymax(ymax) { }
    bool operator()(const HepMC3::GenParticle* p) {
      return !inRapRange(p, ymin, ymax);
    }
    double ymin, ymax;
  };

  //@}



  /// @name Non-PID-based particle classifiers
  //@{

  /// Determine whether the particle is stable
  inline bool isStable(const HepMC3::GenParticle* p) {
    return p->status() == 1;
  }

  /// Determine whether the particle is physical but decayed
  inline bool isDecayed(const HepMC3::GenParticle* p) {
    return p->status() == 2;
  }

  /// @brief Determine whether the particle is outside the physical status code range
  ///
  /// If the answer is "true", use with extreme, generator-specific care!
  inline bool hasNonStandardStatus(const HepMC3::GenParticle* p) { return !in_range(p->status(), 1, 5); }

  /// Is this a physically reliable final state particle? (as opposed to a debugging entry)
  inline bool isPhysical(const HepMC3::GenParticle* p) {
    return isStable(p) || isDecayed(p);
  }

  /// Is this a physically reliable hadron? (as opposed to a debugging entry)
  inline bool isPhysicalHadron(const HepMC3::GenParticle* p) {
    return isHadron(p) && isPhysical(p);
  }
  /// Determine if the particle is a decayed hadron
  inline bool isDecayedHadron(const HepMC3::GenParticle* p) {
    return isDecayed(p) && isHadron(p);
  }

  /// Determine if the particle is a decayed tau
  inline bool isDecayedTau(const HepMC3::GenParticle* p) {
    return isDecayed(p) && isTau(p);
  }

  //@}



  /// @name Classifiers for particles based on their relationships to others
  //@{

  /// @brief Determine whether the given particle has an ancestor that matches the given classifier
  inline bool fromAncestorWith(const HepMC3::GenParticle* p, const PClassifier& c) {
    /// @todo *sigh* Missing const methods in HepMC...
    HepMC3::GenVertex* gv = const_cast<HepMC3::GenVertex*>(p->production_vertex());
    if (gv == NULL) return false;
    /// @todo HepMC needs const versions of these iterator methods :-/
    for (HepMC3::GenVertex::particle_iterator pi = gv->particles_begin(HepMC3::ancestors); pi != gv->particles_end(HepMC3::ancestors); ++pi) {
      if (c(*pi)) return true;
    }
    return false;
  }

  /// @brief Determine whether the given particle has a descendant that matches the given classifier
  inline bool hasDescendantWith(const HepMC3::GenParticle* p, const PClassifier& c) {
    /// @todo *sigh* Missing const methods in HepMC...
    HepMC3::GenVertex* gv = const_cast<HepMC3::GenVertex*>(p->end_vertex());
    if (gv == NULL) return false;
    /// @todo HepMC needs const versions of these iterator methods :-/
    for (HepMC3::GenVertex::particle_iterator pi = gv->particles_begin(HepMC3::descendants); pi != gv->particles_end(HepMC3::descendants); ++pi) {
      if (c(*pi)) return true;
    }
    return false;
  }


  /// Determine if the particle is a hadronically decayed tau
  inline bool isHadronicTau(const HepMC3::GenParticle* p) {
    return isDecayedTau(p) && hasDescendantWith(p, isHadron);
  }
  /// Determine if the particle is a leptonically decayed tau
  inline bool isLeptonicTau(const HepMC3::GenParticle* p) {
    return isDecayedTau(p) && !hasDescendantWith(p, isHadron);
  }


  /// @brief Helper function used in detecting hadron/tau decay daughters
  ///
  /// @todo Use C++11 lambda when available
  inline bool _isDecayedHadronOrTau(const HepMC3::GenParticle* p) {
    return isDecayed(p) && (isTau(p) || isHadron(p));
  }
  /// @brief Determine whether the given particle is from a hadron or tau decay
  ///
  /// @todo Use a better, more explicit name?
  /// Specifically, walk up the ancestor chain until a status 2 hadron or tau is found, if at all.
  inline bool fromDecay(const HepMC3::GenParticle* p) {
    return fromAncestorWith(p, _isDecayedHadronOrTau);
  }


  /// @brief Determine whether the given particle is from a hadron decay
  ///
  /// Specifically, walk up the ancestor chain until a status 2 hadron is found, if at all.
  inline bool fromHadronDecay(const HepMC3::GenParticle* p) {
    return fromAncestorWith(p, isDecayedHadron);
  }

  /// @brief Determine whether the given particle is from a heavy hadron decay
  ///
  /// Specifically, walk up the ancestor chain until a status 2 heavy hadron is found, if at all.
  inline bool fromHeavyHadronDecay(const HepMC3::GenParticle* p) {
    return fromAncestorWith(p, isHeavyHadron);
  }

  /// @brief Determine whether the given particle is from a bottom hadron decay
  ///
  /// Specifically, walk up the ancestor chain until a status 2 bottom hadron is found, if at all.
  inline bool fromBottomHadronDecay(const HepMC3::GenParticle* p) {
    return fromAncestorWith(p, isBottomHadron);
  }

  /// @brief Determine whether the given particle is from a charm hadron decay
  ///
  /// Specifically, walk up the ancestor chain until a status 2 charm hadron is found, if at all.
  inline bool fromCharmHadronDecay(const HepMC3::GenParticle* p) {
    return fromAncestorWith(p, isCharmHadron);
  }

  /// @brief Determine whether the given particle is from a tau decay
  ///
  /// Specifically, walk up the ancestor chain until a tau is found, if at all.
  /// If @a only_prompt_taus is true then return false if the tau itself was from a hadron decay.
  inline bool fromTauDecay(const HepMC3::GenParticle* p, bool only_prompt_taus=false) {
    // If the tau was non-prompt, there will also be a hadron in the history:
    if (only_prompt_taus && fromHadronDecay(p)) return false;
    // Else...
    return fromAncestorWith(p, isDecayedTau);
  }

  /// @brief Determine whether the given particle is from a prompt tau decay
  ///
  /// @note Syntactic sugar for fromTauDecay(p, true)
  inline bool fromPromptTauDecay(const HepMC3::GenParticle* p) {
    return fromTauDecay(p, true);
  }

  /// @brief Determine whether the given particle is from a hadronic tau decay
  ///
  /// Specifically, walk up the ancestor chain until a status 2 tau is found, if at all.
  /// If @a only_prompt_taus is true then return false if the tau itself was from a hadron decay.
  inline bool fromHadronicTauDecay(const HepMC3::GenParticle* p, bool only_prompt_taus=false) {
    // If the tau was non-prompt, there will also be a hadron in the history:
    if (only_prompt_taus && fromHadronDecay(p)) return false;
    // Else...
    return fromAncestorWith(p, isHadronicTau);
  }

  /// @brief Determine whether the given particle is from a prompt tau decay
  ///
  /// @note Syntactic sugar for fromHadronicTauDecay(p, true)
  inline bool fromPromptHadronicTauDecay(const HepMC3::GenParticle* p) {
    return fromHadronicTauDecay(p, true);
  }


  /// @brief Determine whether the given particle is from a HF hadron or tau decay
  ///
  /// Specifically, walk up the ancestor chain until a status 2 c/b hadron or tau is found, if at all.
  /// If @a only_prompt_taus is true then return false if the tau itself was from a hadron decay.
  inline bool fromTauOrHFDecay(const HepMC3::GenParticle* p, bool only_prompt_taus=false) {
    return fromHeavyHadronDecay(p) || fromTauDecay(p, only_prompt_taus); //< Evaluation order & short-circuiting are important!!
  }



  /// Return if the give particle is prompt, defined as a physical particle emitted directly from the hard process
  ///
  /// The full and specific definition used is that the particle must be
  /// physical (status 1 or 2), a photon or lepton (hadrons are never considered
  /// prompt in this definition), and must not come from the decay of a hadron
  /// or non-prompt tau. By default leptons and photons emitted from a prompt
  /// tau are themselves considered prompt; changing the optional boolean
  /// parameter to false will result in such particles being reported as
  /// non-prompt (i.e. isPrompt = false).
  inline bool isPrompt(const HepMC3::GenParticle* p, bool accept_prompt_tau_decay_leptons=true) {
    if (!isPhysical(p) || isHadron(p)) return false;
    if (fromHadronDecay(p)) return false;
    if (!accept_prompt_tau_decay_leptons && fromTauDecay(p, true)) return false;
    return true;
  }

  //@}


}
