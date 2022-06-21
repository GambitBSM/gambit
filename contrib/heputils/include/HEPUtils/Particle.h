// -*- C++ -*-
//
// This file is part of HEPUtils -- https://bitbucket.org/andybuckley/heputils
// Copyright (C) 2013-2018 Andy Buckley <andy.buckley@cern.ch>
//
// Embedding of HEPUtils code in other projects is permitted provided this
// notice is retained and the HEPUtils namespace and include path are changed.
//
#pragma once

#include "HEPUtils/MathUtils.h"
#include "HEPUtils/Vectors.h"

namespace HEPUtils {


  /// Simple particle class, encapsulating a momentum 4-vector and adding some extra ID info
  /// @todo Derive from a PhysObj base class to centralise the momentum handling
  /// @todo Provide cast operators to P4 and P4*
  class Particle {
  private:

    /// @name Storage
    //@{
    /// Momentum vector
    P4 _p4;
    /// PDG ID code
    int _pdgId;
    /// Promptness flag
    bool _prompt;
    // /// Isolation value
    // double _isol4;
    //@}


  public:

    /// @name Constructors
    //@{

    /// Default constructor
    Particle()
      : _pdgId(0), _prompt(false) { } //, _isol4(0.0) {  }

    /// "Cartesian" constructor
    Particle(double px, double py, double pz, double E, int pdgid)
      : _p4(px, py, pz, E), _pdgId(pdgid), _prompt(false) { } //, _isol4(0.0) {  }

    /// "Cartesian" constructor for massless particles - or close enough
    /// @todo AB: WTF?
    // Particle(double px, double py, double pz, int pdgid)
    //   : _p4(px, py, pz), _pdgId(pdgid), _prompt(false), _isol4(0.0) {  }

    /// 4-mom + PDG ID constructor
    Particle(const P4& mom, int pdgid)
      : _p4(mom), _pdgId(pdgid), _prompt(false) { } //, _isol4(0.0) {  }

    /// Copy constructor
    Particle(const Particle& p)
      : _p4(p.mom()), _pdgId(p.pid()), _prompt(p.is_prompt()) { } //, _isol4(p.isol()) {  }

    /// Copy constructor from a pointer
    Particle(const Particle* p)
      : _p4(p->mom()), _pdgId(p->pid()), _prompt(p->is_prompt()) { } //, _isol4(p->isol()) {  }

    /// Copy assignment operator
    Particle& operator=(const Particle& p) {
      _p4 = p.mom();
      _pdgId = p.pid();
      _prompt = p.is_prompt();
      //_isol4 = p.isol();
      return *this;
    }

    //@}


    /// @name Implicit casts
    //@{

    operator const P4& () const { return mom(); }

    operator const P4* () const { return &mom(); }

    //@}


    /// @name Momentum
    ///
    /// Access to the P4 object, plus convenience mapping of a few popular properties
    //@{

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

    //@}


    /// @name Promptness
    //@{

    /// Is this particle connected to the hard process or from a hadron/tau decay?
    bool is_prompt() const { return _prompt; }
    /// Set promptness
    void set_prompt(bool isprompt=true) { _prompt = isprompt; }

    //@}


    /// @name Particle ID
    //@{

    /// Get PDG ID code
    int pid() const { return _pdgId; }
    /// Get abs PDG ID code
    int abspid() const { return abs(_pdgId); }
    /// Set PDG ID code
    void set_pid(int pid) { _pdgId = pid; }

    //@}


    // /// @name Isolation of particle
    // //@{

    // /// Get isolation
    // double isol() const { return _isol4;}
    // void set_isol(double isol) { _isol4 = isol;}

    // //@}


  };


}
