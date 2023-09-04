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

/// @file Functions for filtering and classifying HepMC GenVertex objects
/// @author Andy Buckley <andy.buckley@cern.ch>

#include "HepMC3/GenEvent.h"
#include <vector>
#include <functional>

namespace MCUtils {


  /// @name GenVertex classifier functions
  //@{

  /// Convenient type name for a generic classifier function / function object
  typedef std::function<bool(const HepMC3::GenVertex*)> VClassifier;


  /// Determine if the vertex has no incoming particles
  inline bool hasNoParents(const HepMC3::GenVertex* v) {
    return v->particles_in_size() == 0;
  }

  /// Determine if the vertex has no outgoing particles
  inline bool hasNoChildren(const HepMC3::GenVertex* v) {
    return v->particles_out_size() == 0;
  }

  /// Determine if the vertex has no connected particles
  inline bool isDisconnected(const HepMC3::GenVertex* v) {
    return v->particles_in_size() == 0 && v->particles_out_size() == 0;
  }

  //@}


}
