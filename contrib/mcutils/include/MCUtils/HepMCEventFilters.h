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

/// @file Functions for filtering HepMC record contents
/// @author Andy Buckley <andy.buckley@cern.ch>

#include "HepMC3/GenEvent.h"
#include <vector>

#include "HEPUtils/Utils.h"
#include "MCUtils/HepMCParticleClassifiers.h"
#include "MCUtils/HepMCVertexClassifiers.h"
#include "MCUtils/HepMCParticleFilters.h"

namespace MCUtils {


  /// @name Get particles from a GenEvent which meet general PClassifier criteria
  //@{

  /// Get all the particles that match a supplied classifier
  inline GenParticlesC const_particles_match(const HepMC3::GenEvent* ge, const PClassifier& c) {
    std::vector<const HepMC3::GenParticle*> rtn;
    for (HepMC3::GenEvent::particle_const_iterator pi = ge->particles_begin(); pi != ge->particles_end(); ++pi) {
      if (c(*pi)) rtn.push_back(*pi);
    }
    return rtn;
  }


  /// Get all the particles that match a supplied classifier
  inline GenParticles particles_match(HepMC3::GenEvent* ge, const PClassifier& c) {
    return mk_unconst(const_particles_match(mk_const(ge), c));
  }


  /// Get the first particle that matches a supplied classifier
  inline const HepMC3::GenParticle* const_particle_match(const HepMC3::GenEvent* ge, const PClassifier& c) {
    for (HepMC3::GenEvent::particle_const_iterator pi = ge->particles_begin(); pi != ge->particles_end(); ++pi) {
      if (c(*pi)) return *pi;
    }
    return 0;
  }


  /// Get the first particle that matches a supplied classifier
  inline HepMC3::GenParticle* particle_match(HepMC3::GenEvent* ge, const PClassifier& c) {
    return mk_unconst(const_particle_match(mk_const(ge), c));
  }


  /// Get all the particles that match *any* of the supplied classifiers
  /// @todo Remove in favour of a single (lambda) function for simplicity and more general logical combinations.
  inline GenParticlesC const_particles_match_any(const HepMC3::GenEvent* ge, const std::vector<PClassifier>& classifiers) {
    std::vector<const HepMC3::GenParticle*> rtn;
    for (HepMC3::GenEvent::particle_const_iterator pi = ge->particles_begin(); pi != ge->particles_end(); ++pi) {
      for (const PClassifier& c : classifiers) {
        if (c(*pi)) {
          rtn.push_back(*pi);
          break;
        }
      }
    }
    return rtn;
  }


  /// Get all the particles that match *any* of the supplied classifiers
  /// @todo Remove in favour of a single (lambda) function for simplicity and more general logical combinations.
  inline GenParticles particles_match_any(HepMC3::GenEvent* ge, const std::vector<PClassifier>& classifiers) {
    return mk_unconst(const_particles_match_any(mk_const(ge), classifiers));
  }


  /// Get all the particles that match *all* of the supplied classifiers
  /// @todo Remove in favour of a single (lambda) function for simplicity and more general logical combinations.
  inline GenParticlesC const_particles_match_all(const HepMC3::GenEvent* ge, const std::vector<PClassifier>& classifiers) {
    std::vector<const HepMC3::GenParticle*> rtn;
    for (HepMC3::GenEvent::particle_const_iterator pi = ge->particles_begin(); pi != ge->particles_end(); ++pi) {
      bool allpassed = true;
      for (const PClassifier& c : classifiers) {
        if (!c(*pi)) {
          allpassed = false;
          break;
        }
        if (allpassed) rtn.push_back(*pi);
      }
    }
    return rtn;
  }


  /// Get all the particles that match *all* of the supplied classifiers
  /// @todo Remove in favour of a single (lambda) function for simplicity and more general logical combinations.
  inline GenParticles particles_match_all(HepMC3::GenEvent* ge, const std::vector<PClassifier>& classifiers) {
    return mk_unconst(const_particles_match_all(mk_const(ge), classifiers));
  }

  //@}


  /// @name Get particles from a GenEvent which meet specific criteria
  //@{

  /// Get a vector of GenParticle pointers to particles with given status
  inline GenParticlesC get_with_status(const HepMC3::GenEvent* evt, int status) {
    return filter_status(const_particles(evt), status);
  }

  /// Get a vector of GenParticle pointers to final state particles
  inline GenParticlesC get_stable(const HepMC3::GenEvent* evt) {
    return filter_stable(const_particles(evt));
  }

  /// Get a vector of GenParticle pointers to stable particles with given PDG ID code
  inline GenParticlesC get_id(const HepMC3::GenEvent* evt, long pid) {
    return filter_id(const_particles(evt), pid);
  }

  /// Get a vector of GenParticle pointers to stable particles with given PDG ID code
  inline GenParticlesC get_stable_id(const HepMC3::GenEvent* evt, long pid) {
    return filter_id(get_stable(evt), pid);
  }

  /// Get a vector of GenParticle pointers to particles with given absolute PDG ID code
  inline GenParticlesC get_absid(const HepMC3::GenEvent* evt, long pid) {
    return filter_absid(const_particles(evt), pid);
  }

  /// Get a vector of GenParticle pointers to stable particles with given absolute PDG ID code
  inline GenParticlesC get_stable_absid(const HepMC3::GenEvent* evt, long pid) {
    return filter_absid(get_stable(evt), pid);
  }

  /// Get a vector of GenParticle pointers to charged final state particles
  inline GenParticlesC get_stable_charged(const HepMC3::GenEvent* evt) {
    return filter_charged(get_stable(evt));
  }

  /// Get a vector of GenParticle pointers to neutral final state particles
  inline GenParticlesC get_stable_neutral(const HepMC3::GenEvent* evt) {
    return filter_neutral(get_stable(evt));
  }

  /// Get a vector of GenParticle pointers to final state electrons
  inline GenParticlesC get_stable_electrons(const HepMC3::GenEvent* evt) {
    return filter_absid(get_stable(evt), 11);
  }

  /// Get a vector of GenParticle pointers to final state muons
  inline GenParticlesC get_stable_muons(const HepMC3::GenEvent* evt) {
    return filter_absid(get_stable(evt), 13);
  }

  /// Get a vector of GenParticle pointers to final state charged leptons (not counting taus)
  inline GenParticlesC get_stable_chleptons(const HepMC3::GenEvent* evt) {
    std::vector<long> apids;
    apids.push_back(11);
    apids.push_back(13);
    return filter_absids(get_stable(evt), apids);
    // C++11 version: return filter_absids(get_stable(evt), {{11, 13}});
  }

  /// Get a vector of GenParticle pointers to final state neutrinos
  inline GenParticlesC get_stable_neutrinos(const HepMC3::GenEvent* evt) {
    return filter_neutrinos(get_stable(evt));
  }

  /// Get a vector of GenParticle pointers to decayed taus
  inline GenParticlesC get_decayed_taus(const HepMC3::GenEvent* evt) {
    /// @todo Make sure there aren't duplicates from a single decay chain
    return filter_absid(get_with_status(evt, 2), 15);
  }

  /// Get a vector of GenParticle pointers to final state photons
  inline GenParticlesC get_stable_photons(const HepMC3::GenEvent* evt) {
    return filter_id(get_stable(evt), 22);
  }

  /// Get a vector of GenParticle pointers to final state hadrons
  inline GenParticlesC get_stable_hadrons(const HepMC3::GenEvent* evt) {
    return filter_hadrons(get_stable(evt));
  }

  /// @todo Add get_jet_inputs. Treatments for neutrinos, muons (depends on their history?), and photons?

  /// @todo get_decayed_hadrons, decayed_taus ---- needs the work to clean up decay chains etc.

  /// @todo get_tops --- need work to identify "correct" top

  /// @todo get_Ws, get_Zs --- reco vs. direct... get correct copy for direct way

  //@}



  /// @name Get vertices from a GenEvent which meet general VClassifier criteria
  //@{

  /// Get all the vertices that match a supplied classifier
  inline GenVerticesC const_vertices_match(const HepMC3::GenEvent* ge, const VClassifier& c) {
    std::vector<const HepMC3::GenVertex*> rtn;
    for (HepMC3::GenEvent::vertex_const_iterator vi = ge->vertices_begin(); vi != ge->vertices_end(); ++vi) {
      if (c(*vi)) rtn.push_back(*vi);
    }
    return rtn;
  }


  /// Get all the vertices that match a supplied classifier
  inline GenVertices vertices_match(HepMC3::GenEvent* ge, const VClassifier& c) {
    return mk_unconst(const_vertices_match(mk_const(ge), c));
  }


  /// Get the first vertex that matches a supplied classifier
  inline const HepMC3::GenVertex* const_vertex_match(const HepMC3::GenEvent* ge, const VClassifier& c) {
    for (HepMC3::GenEvent::vertex_const_iterator vi = ge->vertices_begin(); vi != ge->vertices_end(); ++vi) {
      if (c(*vi)) return *vi;
    }
    return 0;
  }


  /// Get the first vertex that matches a supplied classifier
  inline HepMC3::GenVertex* vertex_match(HepMC3::GenEvent* ge, const VClassifier& c) {
    return mk_unconst(const_vertex_match(mk_const(ge), c));
  }

  //@}



  /// @name Event reduction functions
  //@{

  /// Remove an unwanted particle from the event, collapsing the graph structure consistently
  inline void reduce(HepMC3::GenEvent* ge, HepMC3::GenParticle* gp) {
    // Do nothing if for some reason this particle is not actually in this event
    if (gp->parent_event() != ge) return;

    // Get start and end vertices
    HepMC3::GenVertex* vstart = gp->production_vertex();
    HepMC3::GenVertex* vend = gp->end_vertex();

    // Disconnect the unwanted particle from its vertices and delete it
    if (vstart != NULL) vstart->remove_particle(gp);
    if (vend != NULL) vend->remove_particle(gp);
    delete gp;

    // If start/end vertices are valid and distinct, and this was the only particle that
    // connected them, then reassign the end vertex decay products to the start vertex
    // and rewrite the vertex position as most appropriate.
    /// @note The disconnected end vertex will be picked up by the final "sweeper" loop if necessary.
    /// @note We do the reassigning this way since GV::add_particle_*() modifies the end vertex
    if (vstart != NULL && vend != NULL && vend != vstart) {
      bool is_only_link = true;
      for (const HepMC3::GenParticle* pchild : const_particles(vstart, HepMC3::children)) {
        if (pchild->end_vertex() == vend) is_only_link = false;
      }
      if (is_only_link) {
        if (vend->position() != HepMC3::FourVector())
          vstart->set_position(vend->position()); //< @todo Always use end position if defined... ok?
        while (vend->particles_out_size() > 0) {
          vstart->add_particle_out(*vend->particles_out_const_begin());
        }
        while (vend->particles_in_size() > 0) {
          vstart->add_particle_in(*vend->particles_in_const_begin());
        }
      }
    }

    // Sweep up any vertices orphaned by the particle removal
    /// @todo Can we be a bit more efficient rather than having to run over all vertices every time?
    ///       Or allow disabling of this clean-up, with a single clean being run at the end of filtering.
    /// @todo Use neater looping via vertices_match (or iterated vertex_match)
    /// @todo Also look for and report changes in number of no-parent and no-child vertices
    std::vector<HepMC3::GenVertex*> orphaned_vtxs;
    for (HepMC3::GenEvent::vertex_const_iterator vi = ge->vertices_begin(); vi != ge->vertices_end(); ++vi) {
      if ((*vi)->particles_in_size() == 0 && (*vi)->particles_out_size() == 0) orphaned_vtxs.push_back(*vi);
    }
    for (HepMC3::GenVertex* gv : orphaned_vtxs) delete gv;
  }


  /// Remove unwanted particles from the event, collapsing the graph structure consistently
  inline void reduce(HepMC3::GenEvent* ge, std::vector<HepMC3::GenParticle*> toremove) {
    while (toremove.size()) {
      HepMC3::GenParticle* gp = toremove.back();
      toremove.pop_back();
      reduce(ge, gp);
    }
  }


  /// @brief Remove unwanted particles from the event, collapsing the graph structure consistently
  ///
  /// This version operates in-place on a GenEvent, using a vector of particle
  /// barcodes to define which particles are to be removed (it's therefore a bit
  /// more robust but also less efficient than the pointer-based version).
  inline void reduce(HepMC3::GenEvent* ge, const std::vector<int>& barcodes_toremove) {
    std::vector<HepMC3::GenParticle*> toremove;
    for (int barcode : barcodes_toremove) {
      HepMC3::GenParticle* gp = ge->barcode_to_particle(barcode);
      if (gp != NULL) toremove.push_back(gp);
    }
    reduce(ge, toremove);
  }


  /// @brief Remove unwanted particles from the event, collapsing the graph structure consistently
  ///
  /// This version operates on a const GenEvent with return by value of a
  /// reduced heap-allocated *copy*, using a vector of particle barcodes to
  /// define which particles are to be removed (it's therefore a bit more robust
  /// but also less efficient than the pointer-based version).
  ///
  /// The user is responsible for ensuring that the memory associated with the
  /// returned event copy is freed.
  inline HepMC3::GenEvent* reduce(const HepMC3::GenEvent* ge, const std::vector<int>& barcodes_toremove) {
    HepMC3::GenEvent* rtnevt = new HepMC3::GenEvent(*ge);
    reduce(rtnevt, barcodes_toremove);
    return rtnevt;
  }


  /// @brief Remove unwanted particles from the event, collapsing the graph structure consistently
  ///
  /// This version operates on a const GenEvent, returning a reduced heap-allocated *copy*. The user is responsible
  /// for ensuring that the memory associated with the returned event is freed.
  inline HepMC3::GenEvent* reduce(const HepMC3::GenEvent* ge, const std::vector<HepMC3::GenParticle*>& toremove) {
    std::vector<int> barcodes_toremove;
    for (const HepMC3::GenParticle* gp : toremove) {
      if (gp != NULL) barcodes_toremove.push_back(gp->barcode());
    }
    return reduce(ge, barcodes_toremove);
  }


  /// Remove particles from the event which match a classifier function, collapsing the graph structure consistently
  ///
  /// The @c iterative argument determines whether a single pass (iterative =
  /// false) or multi-pass (iterative = true) approach will be taken to the
  /// event reduction. The iterative form is accurate but SLOW!
  inline void reduce(HepMC3::GenEvent* ge, const PClassifier& c, bool iterative=false) {
    if (iterative) {
      // Remove one particle, search for a new match, remove, etc. until no matches... SLOW!
      HepMC3::GenParticle* gp = particle_match(ge, c);
      while (gp != 0) {
        reduce(ge, gp); // Reduce in-place
        gp = particle_match(ge, c); // Get next matching particle
      }
    } else {
      // Identify many particles in one run, then remove them all. Might not catch all problem structures
      GenParticles gps = particles_match(ge, c);
      reduce(ge, gps);
    }
  }


  /// @brief Remove unwanted particles from the event, collapsing the graph structure consistently
  ///
  /// The @c iterative argument determines whether a single pass (iterative =
  /// false) or multi-pass (iterative = true) approach will be taken to the
  /// event reduction. The iterative form is accurate but SLOW!
  ///
  /// This version operates on a const GenEvent, returning a reduced heap-allocated *copy*. The user is responsible
  /// for ensuring that the memory associated with the returned event is freed.
  inline HepMC3::GenEvent* reduce(const HepMC3::GenEvent* ge, const PClassifier& c, bool iterative=false) {
    HepMC3::GenEvent* rtnevt = new HepMC3::GenEvent(*ge);
    reduce(rtnevt, c, iterative);
    return rtnevt;
  }

  //@}


}
