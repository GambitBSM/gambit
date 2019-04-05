// -*- C++ -*-
//
// This file is part of HEPUtils -- https://bitbucket.org/andybuckley/heputils
// Copyright (C) 2013-2018 Andy Buckley <andy.buckley@cern.ch>
//
// Embedding of HEPUtils code in other projects is permitted provided this
// notice is retained and the HEPUtils namespace and include path are changed.
//
#pragma once

/// @file FastJet helper routines
/// @author Andy Buckley <andy.buckley@cern.ch>
///
/// These routines are written to use the FastJet headers and namespace by default;
/// if the minimal fjcore is being used, then set the -DFJCORE compiler flag to switch
/// to the fjcore header and namespace. A macro FJNS is defined to the active namespace.

#include "HEPUtils/Utils.h"
#include "HEPUtils/Vectors.h"
#include <stdexcept>

#ifndef FJCORE
#ifndef FJNS
#define FJNS fastjet
#endif
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#else
#include "fjcore.hh"
#ifndef FJNS
#define FJNS fjcore
#endif
#endif

namespace HEPUtils {


  /// @name Converters between HEPUtils and FastJet momentum types
  //@{

  /// @todo Enable... conditionally on FJ version?
  // /// For attaching the GenParticle provenance info to a PseudoJet
  // struct HepMCInfo : public PseudoJet::UserInfoBase {
  //     HepMCInfo(const HepMC::GenParticle* gp) : genparticle(gp) { }
  //     const HepMC::GenParticle* genparticle;
  // };
  //
  // // Usage: const GenParticle* gp = pj.user_info<HepMCInfo>().genparticle;


  /// Convert a P4 to a FastJet PseudoJet
  inline FJNS::PseudoJet mk_pseudojet(const P4& p) {
    return FJNS::PseudoJet(p.px(), p.py(), p.pz(), p.E());
  }
  /// Alias for mk_pseudojet
  inline FJNS::PseudoJet mk_pj(const P4& p) { return mk_pseudojet(p); }


  /// Convert a FastJet PseudoJet to a P4
  inline P4 mk_p4(const FJNS::PseudoJet& p) {
    const double m = p.m();
    /// @todo These units aren't defined -- should just make it a < 0 threshold
    if (m < -5e-3) throw std::domain_error("Negative mass vector from FastJet");
    return P4::mkXYZM(p.px(), p.py(), p.pz(), (m >= 0) ? m : 0);
  }

  //@}


  /// @name Jet builders
  //@{

  /// Construct pT-sorted jets using the @a alg measure with jet @a R parameter, and min pT @a ptmin (in MeV)
  inline std::vector<FJNS::PseudoJet> get_jets(const std::vector<FJNS::PseudoJet>& particles, double R, double ptmin,
                                               FJNS::JetAlgorithm alg=FJNS::antikt_algorithm) {
    const FJNS::JetDefinition jet_def(alg, R);
    /// @todo Add area definition? And filtering?
    FJNS::ClusterSequence cseq(particles, jet_def); //< @todo Need new + auto/unique_ptr?
    return sorted_by_pt(cseq.inclusive_jets(ptmin));
  }

  //@}


}
