// -*- C++ -*-
//
// This file is part of HEPUtils -- https://gitlab.com/hepcedar/heputils/
// Copyright (C) 2013-2022 Andy Buckley <andy.buckley@cern.ch>
//
// Embedding of HEPUtils code in other projects is permitted provided this
// notice is retained and the HEPUtils namespace and include path are changed.
//
#pragma once

#include "HEPUtils/MathUtils.h"
#include "HEPUtils/Vectors.h"

namespace HEPUtils {


  /// @brief Simple particle class, encapsulating a momentum 4-vector and adding some extra ID info
  ///
  /// @todo Derive from a PhysObj base class to centralise the momentum handling?
  class Particle {
  private:

    /// @name Storage
    /// @{

    /// Momentum vector
    P4 _p4;

    /// PDG ID code
    int _pid;

    /// Promptness flag
    bool _prompt;

    /// @}


  public:

    /// @name Constructors
    /// @{

    /// Default constructor
    Particle()
      : _pid(0), _prompt(false) { }

    /// "Cartesian" constructor
    Particle(double px, double py, double pz, double E, int pdgid)
      : _p4(px, py, pz, E), _pid(pdgid), _prompt(false) { }

    /// 4-mom + PDG ID constructor
    Particle(const P4& mom, int pdgid)
      : _p4(mom), _pid(pdgid), _prompt(false) { }

    /// Copy constructor
    Particle(const Particle& p)
      : _p4(p.mom()), _pid(p.pid()), _prompt(p.is_prompt()) { }

    /// Copy constructor from a pointer
    Particle(const Particle* p)
      : _p4(p->mom()), _pid(p->pid()), _prompt(p->is_prompt()) { }

    /// Copy assignment operator
    Particle& operator = (const Particle& p) {
      _p4 = p.mom();
      _pid = p.pid();
      _prompt = p.is_prompt();
      return *this;
    }

    /// @}


    /// @name Implicit casts
    /// @{

    operator const P4& () const { return mom(); }

    operator const P4* () const { return &mom(); }

    /// @}


    /// @name Momentum
    ///
    /// Access to the P4 object, plus convenience mapping of a few popular properties
    /// @{

    /// Get the 4 vector
    const P4& mom() const { return _p4; }
    /// Set the 4 vector
    void set_mom(const P4& p4) { _p4 = p4; }


    /// Get the mass (of the 4 vector)
    double mass() const { return _p4.m(); }
    /// Set the mass (of the 4 vector)
    void set_mass(double mass) { _p4.setM(mass); }


    /// Get the pseudorapidity
    double eta() const { return mom().eta(); }

    /// Get the abs pseudorapidity
    double abseta() const { return mom().abseta(); }

    /// Get the rapidity
    double rap() const { return mom().rap(); }

    /// Get the abs rapidity
    double absrap() const { return mom().absrap(); }

    /// Get the azimuthal angle
    double phi() const { return mom().phi(); }

    /// Get the energy
    double E() const { return mom().E(); }

    /// Get the squared transverse momentum
    double pT2() const { return mom().pT2(); }

    /// Get the squared transverse momentum
    double pT() const { return mom().pT(); }

    /// @}


    /// @name Promptness
    /// @{

    /// Is this particle connected to the hard process or from a hadron/tau decay?
    bool is_prompt() const { return _prompt; }
    /// Set promptness
    void set_prompt(bool isprompt=true) { _prompt = isprompt; }

    /// @}


    /// @name Particle ID
    /// @{

    /// Get PDG ID code
    int pid() const { return _pid; }
    /// Get abs PDG ID code
    int abspid() const { return abs(_pid); }
    /// Set PDG ID code
    void set_pid(int pdgid) { _pid = pdgid; }

    /// Is this particle usually visible in a detector?
    bool is_visible() {
      if (abspid() == 12 || abspid() == 14 || abspid() == 16) return false;
      if (pid() == 1000022 || pid() == 1000039) return false;
      if (in_range(abspid(), 50, 60)) return false; //< abspid zealousness since some -ve DM PIDs seen
      return true;
    }

    /// Is this particle usually invisible in a detector?
    bool is_invisible() {
      return !is_visible();
    }
    /// @}


    // /// @name Isolation of particle
    // /// @{

    // /// Get isolation
    // double isol() const { return _isol4;}
    // void set_isol(double isol) { _isol4 = isol;}

    // /// @}


  };


  /// @defgroup particle_const Particle constness conversion
  /// @{

  /// Convenience Particle cast to const
  inline const Particle* mkconst(Particle* particle) {
    return const_cast<const Particle*>(particle);
  }

  /// Convenience Particle cast to non-const
  inline Particle* mkunconst(const Particle* cparticle) {
    return const_cast<Particle*>(cparticle);
  }

  /// Get a reference to a vector of Particles, with each member const
  inline std::vector<const Particle*>& mkconst(const std::vector<Particle*>& particles) {
    return * (std::vector<const Particle*>*)(void*) (&particles);
  }

  /// Get a reference to a vector of Particles, with each member non-const
  inline std::vector<Particle*>& mkunconst(const std::vector<const Particle*>& cparticles) {
    return * (std::vector<Particle*>*) (void*) (&cparticles);
  }

  /// @}


  // /// Function/functor for container<const Particle*> sorting (cf. std::less)
  // inline bool _cmpPtDescParticle(const Particle* a, const Particle* b) {
  //   return a->pT2() >= b->pT2();
  // }


}
