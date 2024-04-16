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

/// @file FastJet clustering on HepMC events
/// @author Andy Buckley <andy.buckley@cern.ch>

#include "HEPUtils/FastJet.h"
#include "MCUtils/HepMCEventUtils.h"

namespace MCUtils {


  /// @name Converters between HepMC and FastJet momentum types
  //@{

  /// Convert a HepMC FourVector to a FastJet PseudoJet
  inline fastjet::PseudoJet mk_pseudojet(const HepMC3::FourVector& p4) {
    return fastjet::PseudoJet(p4.px(), p4.py(), p4.pz(), p4.e());
  }

  /// Convert a HepMC GenParticle to a FastJet PseudoJet
  inline fastjet::PseudoJet mk_pseudojet(const HepMC3::GenParticle* gp) {
    fastjet::PseudoJet pj = mk_pseudojet(gp->momentum());
    //pj.set_user_info(new HepMCInfo(p));
    return pj;
  }

  /// Convert a vector of HepMC GenParticles to a vector of FastJet PseudoJets
  inline std::vector<fastjet::PseudoJet> mk_pseudojets(const GenParticlesC& gps) {
    std::vector<fastjet::PseudoJet> pjs;
    for (const HepMC3::GenParticle* gp : gps) {
      pjs.push_back( mk_pseudojet(gp) );
    }
    return pjs;
  }

  //@}


  /// @name Jet builders from HepMC input types
  //@{

  /// Construct pT-sorted jets using the @a alg measure with jet @a R parameter, and min pT @a ptmin (in MeV)
  inline std::vector<fastjet::PseudoJet> get_jets(const GenParticlesC& particles, double R, double ptmin,
                                                  fastjet::JetAlgorithm alg=fastjet::antikt_algorithm) {
    /// @todo Convert to use filter_jet_inputs
    return HEPUtils::get_jets(mk_pseudojets(filter_stable(particles)), R, ptmin, alg);
  }


  /// Construct pT-sorted jets using the @a alg measure with jet @a R parameter, and min pT @a ptmin (in MeV)
  inline std::vector<fastjet::PseudoJet> get_jets(const HepMC3::GenEvent* evt, double R, double ptmin,
                                                  fastjet::JetAlgorithm alg=fastjet::antikt_algorithm) {
    /// @todo Convert to use get_jet_inputs
    return HEPUtils::get_jets(mk_pseudojets(get_stable(evt)), R, ptmin, alg);
  }

  //@}


  /// @todo Make safe photon clustering for charged leptons

  /// @todo Make tau, B, top and W/Z finders (both safe and direct versions)


}
