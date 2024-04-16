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

#include "HepMC3/GenEvent.h"

#include "HEPUtils/Utils.h"
#include "HEPUtils/Vectors.h"

namespace MCUtils {


  /// @name Generic in-place filtering and GenParticle classifying functions
  //@{

  /// Filter a vector of GenParticle pointers to only contain those for which fkeep(const GenParticle*) returns true
  /// @todo Refine using std::function
  template <typename FN>
  inline GenParticlesC& filter_keep(GenParticlesC& particles, FN fkeep) {
    // Reimplementation of std::remove_if with inverted predicate logic
    std::vector<const HepMC3::GenParticle*>::iterator itr = particles.begin();
    std::vector<const HepMC3::GenParticle*>::iterator last = particles.end();
    std::vector<const HepMC3::GenParticle*>::iterator newend = itr;
    for ( ; itr != last; ++itr)
      if (fkeep(*itr)) *newend++ = *itr;
    particles.resize(newend - particles.begin());
    return particles;
  }

  /// Filter a vector of GenParticle pointers to only contain those for which fremove(const GenParticle*) returns false
  /// @todo Refine using std::function
  template <typename FN>
  inline GenParticlesC& filter_remove(GenParticlesC& particles, FN fremove) {
    // Reimplementation of std::remove_if, for equivalence to filter_keep
    std::vector<const HepMC3::GenParticle*>::iterator itr = particles.begin();
    std::vector<const HepMC3::GenParticle*>::iterator last = particles.end();
    std::vector<const HepMC3::GenParticle*>::iterator newend = itr;
    for ( ; itr != last; ++itr)
      if (!fremove(*itr)) *newend++ = *itr;
    particles.resize(newend - particles.begin());
    return particles;
  }

  //@}



  /// @name Filter particles from a list according to various criteria
  //@{

  /// Filter a vector of GenParticle pointers to only contain final state particles
  inline GenParticlesC& ifilter_stable(GenParticlesC& particles) {
    return filter_keep(particles, isStable);
  }

  /// Filter a vector of GenParticle pointers to only contain final state particles
  inline GenParticlesC filter_stable(const GenParticlesC& particles) {
    GenParticlesC rtn = particles;
    return ifilter_stable(rtn);
  }


  /// Filter a vector of GenParticle pointers to only contain particles with a given status
  inline GenParticlesC& ifilter_status(GenParticlesC& particles, int status) {
    return filter_keep(particles, HasStatus(status));
  }

  /// Filter a vector of GenParticle pointers to only contain particles with a given status
  inline GenParticlesC filter_status(const GenParticlesC& particles, int status) {
    GenParticlesC rtn = particles;
    return ifilter_status(rtn, status);
  }


  /// Filter a vector of GenParticle pointers to only contain specific particle species
  inline GenParticlesC& ifilter_ids(GenParticlesC& particles, const std::vector<long>& pids) {
    return filter_keep(particles, HasPID(pids));
  }

  /// Filter a vector of GenParticle pointers to only contain specific particle species
  inline GenParticlesC filter_ids(const GenParticlesC& particles, const std::vector<long>& pids) {
    GenParticlesC rtn = particles;
    return ifilter_ids(rtn, pids);
  }


  /// Filter a vector of GenParticle pointers to only contain a specific particle species
  inline GenParticlesC& ifilter_id(GenParticlesC& particles, long pid) {
    return filter_keep(particles, HasPID(pid));
  }

  /// Filter a vector of GenParticle pointers to only contain a specific particle species
  inline GenParticlesC filter_id(const GenParticlesC& particles, long pid) {
    GenParticlesC rtn = particles;
    return ifilter_id(rtn, pid);
  }


  /// Filter a vector of GenParticle pointers to only contain specific particle (and antiparticle) species
  inline GenParticlesC& ifilter_absids(GenParticlesC& particles, const std::vector<long>& pids) {
    return filter_keep(particles, HasAbsPID(pids));
  }

  /// Filter a vector of GenParticle pointers to only contain specific particle (and antiparticle) species
  inline GenParticlesC filter_absids(const GenParticlesC& particles, const std::vector<long>& pids) {
    GenParticlesC rtn = particles;
    return ifilter_absids(rtn, pids);
  }


  /// Filter a vector of GenParticle pointers to only contain a specific particle (and antiparticle) species
  inline GenParticlesC& ifilter_absid(GenParticlesC& particles, long pid) {
    return filter_keep(particles, HasAbsPID(pid));
  }

  /// Filter a vector of GenParticle pointers to only contain a specific particle (and antiparticle) species
  inline GenParticlesC filter_absid(const GenParticlesC& particles, long pid) {
    GenParticlesC rtn = particles;
    return ifilter_absid(rtn, pid);
  }


  /// Filter a vector of GenParticle pointers to only contain charged particles
  inline GenParticlesC& ifilter_charged(GenParticlesC& particles) {
    return filter_keep(particles, isCharged);
  }

  /// Filter a vector of GenParticle pointers to only contain charged particles
  inline GenParticlesC filter_charged(const GenParticlesC& particles) {
    GenParticlesC rtn = particles;
    return ifilter_charged(rtn);
  }


  /// Filter a vector of GenParticle pointers to only contain neutral particles
  inline GenParticlesC& ifilter_neutral(GenParticlesC& particles) {
    return filter_keep(particles, isNeutral);
  }

  /// Filter a vector of GenParticle pointers to only contain neutral particles
  inline GenParticlesC filter_neutral(const GenParticlesC& particles) {
    GenParticlesC rtn = particles;
    return ifilter_neutral(rtn);
  }


  /// Filter a vector of GenParticle pointers to only contain those with at least a given pT
  inline GenParticlesC& ifilter_pt(GenParticlesC& particles, double ptmin) {
    return filter_keep(particles, PtGtr(ptmin));
  }

  /// Filter a vector of GenParticle pointers to only contain those with at least a given pT
  inline GenParticlesC filter_pt(const GenParticlesC& particles, double ptmin) {
    GenParticlesC rtn = particles;
    return ifilter_pt(rtn, ptmin);
  }


  /// Filter a vector of GenParticle pointers to only contain those within a given eta range
  inline GenParticlesC& ifilter_eta(GenParticlesC& particles, double etamin, double etamax) {
    return filter_keep(particles, InEtaRange(etamin, etamax));
  }

  /// Filter a vector of GenParticle pointers to only contain those within a given eta range
  inline GenParticlesC filter_eta(const GenParticlesC& particles, double etamin, double etamax) {
    GenParticlesC rtn = particles;
    return ifilter_eta(rtn, etamin, etamax);
  }


  /// Filter a vector of GenParticle pointers to only contain those within a given rap range
  inline GenParticlesC& ifilter_rap(GenParticlesC& particles, double ymin, double ymax) {
    return filter_keep(particles, InRapRange(ymin, ymax));
  }

  /// Filter a vector of GenParticle pointers to only contain those within a given rap range
  inline GenParticlesC filter_rap(const GenParticlesC& particles, double ymin, double ymax) {
    GenParticlesC rtn = particles;
    return ifilter_rap(rtn, ymin, ymax);
  }


  /// Filter a vector of GenParticle pointers to only retain neutrinos
  inline GenParticlesC& ifilter_neutrinos(GenParticlesC& particles) {
    return filter_keep(particles, isNeutrino);
  }

  /// Filter a vector of GenParticle pointers to only retain neutrinos
  inline GenParticlesC filter_neutrinos(const GenParticlesC& particles) {
    GenParticlesC rtn = particles;
    return ifilter_neutrinos(rtn);
  }


  /// Filter a vector of GenParticle pointers to only retain neutrinos
  inline GenParticlesC& ifilter_hadrons(GenParticlesC& particles) {
    return filter_keep(particles, isHadron);
  }

  /// Filter a vector of GenParticle pointers to only retain neutrinos
  inline GenParticlesC filter_hadrons(const GenParticlesC& particles) {
    GenParticlesC rtn = particles;
    return ifilter_hadrons(rtn);
  }


  /// @todo Add filter_jet_inputs?

  /// @todo filter_lsp

  /// @todo filter_visible, filter_invisible

  //@}


}
