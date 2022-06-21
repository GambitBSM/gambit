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

#include "HEPUtils/Vectors.h"
#include "HEPUtils/Utils.h"
#include "MCUtils/HepMCEventUtils.h"

namespace MCUtils {


  /// @name Friendlier HepMC type typedefs
  //@{
  typedef std::vector<HepMC3::GenVertex*> GenVertices;
  typedef std::vector<const HepMC3::GenVertex*> GenVerticesC;
  //@}


  /// @name Vertex constness converters
  ///
  /// @note These are just syntactic sugar: this is already not so inconvenient!
  //@{
  inline const HepMC3::GenVertex* mk_const(HepMC3::GenVertex* gv) { return const_cast<const HepMC3::GenVertex*>(gv); }
  inline HepMC3::GenVertex* mk_unconst(const HepMC3::GenVertex* const_gv) { return const_cast<HepMC3::GenVertex*>(const_gv); }
  //@}


  /// @name Container constness converters
  ///
  /// @note Pointers in containers will still point to the same objects after
  /// const conversion!
  ///
  /// @note Due to constness rules, new vectors have to be made and
  /// populated. So this is not super-efficient, but seems to be necessary.
  //@{

  inline GenVerticesC mk_const(const GenVertices& gvs) {
    GenVerticesC rtn;
    rtn.reserve(gvs.size());
    for (const HepMC3::GenVertex* gv : gvs) {
      rtn.push_back(gv);
    }
    return rtn;
  }

  inline GenVertices mk_unconst(const GenVerticesC& const_gps) {
    GenVertices rtn;
    rtn.reserve(const_gps.size());
    for (const HepMC3::GenVertex* const_gp : const_gps) {
      rtn.push_back(const_cast<HepMC3::GenVertex*>(const_gp));
    }
    return rtn;
  }

  //@}


}
