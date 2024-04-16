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

/// @file Interactions between P4 and HepMC's simple vectors
/// @author Andy Buckley <andy.buckley@cern.ch>

#include "HepMC3/GenEvent.h"

#include "HEPUtils/Vectors.h"

namespace MCUtils {

  using HEPUtils::P4;


  /// @name Converters between HepMC and P4 momentum types
  //@{

  /// Convert a HepMC FourVector to a P4
  inline P4 mk_p4(const HepMC3::FourVector& p) {
    return P4(p.px(), p.py(), p.pz(), p.e());
  }

  /// Convert a HepMC GenParticle to a FastJet PseudoJet
  inline P4 mk_p4(const HepMC3::GenParticle* gp) {
    return mk_p4(gp->momentum());
  }

  /// Convert a vector of HepMC GenParticles to a vector of FastJet PseudoJets
  inline std::vector<P4> mk_p4s(const std::vector<const HepMC3::GenParticle*>& gps) {
    std::vector<P4> p4s;
    for (const HepMC3::GenParticle* gp : gps) {
      p4s.push_back( mk_p4(gp) );
    }
    return p4s;
  }

  //@}


  /// @name HepMC vector utils
  //@{

  /// Compute 3-vector magnitude-squared from a HepMC FourVector
  inline double mag2(const HepMC3::FourVector& v) {
    return mk_p4(v).p2();
  }

  /// Compute 3-vector magnitude from a HepMC FourVector
  inline double mag(const HepMC3::FourVector& v) {
    return mk_p4(v).p();
  }

  /// Compute pseudorapidity from a HepMC FourVector
  inline double eta(const HepMC3::FourVector& v) {
    return mk_p4(v).eta();
  }

  /// Compute rapidity from a HepMC FourVector
  inline double rap(const HepMC3::FourVector& v) {
    return mk_p4(v).rap();
  }

  //@}


}
