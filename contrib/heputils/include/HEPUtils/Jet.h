// -*- C++ -*-
//
// This file is part of HEPUtils -- https://gitlab.com/hepcedar/heputils/
// Copyright (C) 2013-2023 Andy Buckley <andy.buckley@cern.ch>
//
// Embedding of HEPUtils code in other projects is permitted provided this
// notice is retained and the HEPUtils namespace and include path are changed.
//
#pragma once

#include "HEPUtils/FastJet.h"
#include "HEPUtils/MathUtils.h"
#include "HEPUtils/Vectors.h"

namespace HEPUtils {


  /// Simple jet class, encapsulating a momentum 4-vector and with some extra b-tag info
  ///
  /// @todo Derive from a PhysObj base class to centralise the momentum handling
  class Jet {
  public:

    /// Typedef for tag PID -> counts dictionary
    using TagCounts = std::map<int, int>;


  private:

    /// @name Storage
    /// @{

    /// Momentum vector
    P4 _p4;

    /// Tagging counts
    TagCounts _tags;

    /// Optional FastJet PJ (contains link to ClusterSeq)
    /// @todo Use std::optional when C++17 allowed
    FJNS::PseudoJet _pj;

    /// @}


  public:

    /// @name Constructors
    /// @{

    /// Constructor for a light jet without explicit constituents
    Jet(const P4& mom, bool isB=false, bool isC=false)
      : _p4(mom)
    { set_btag(int(isB)); set_ctag(int(isC)); }

    /// "Cartesian" constructor
    Jet(double px, double py, double pz, double E, bool isB=false, bool isC=false)
      : _p4(px, py, pz, E)
    { set_btag(int(isB)); set_ctag(int(isC)); }

    /// "PseudoJet" constructor
    Jet(const FJNS::PseudoJet& pj, bool isB=false, bool isC=false)
      : _p4(mk_p4(pj)), _pj(pj)
    { set_btag(int(isB)); set_ctag(int(isC)); }


    /// Constructor for a light jet without explicit constituents, with a general tags map
    Jet(const P4& mom, const TagCounts& tags)
      : _p4(mom), _tags(tags) {  }

    /// "Cartesian" constructor, with a general tags map
    Jet(double px, double py, double pz, double E, const TagCounts& tags)
      : _p4(px, py, pz, E), _tags(tags) {  }

    /// "PseudoJet" constructor, with a general tags map
    Jet(const FJNS::PseudoJet& pj, const TagCounts& tags)
      : _p4(mk_p4(pj)), _tags(tags), _pj(pj) {  }

    /// @}


    /// @name Implicit casts
    /// @{

    operator const P4& () const { return mom(); }

    operator const P4* () const { return &mom(); }

    /// @}


    /// @name Momentum
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


    /// @name Tagging
    /// @{

    /// Get the tags map (const)
    const std::map<int,int>& tags() const { return _tags; }
    /// Get the tags map (const)
    std::map<int,int>& tags() { return _tags; }

    /// Get the number of tags for the given PDG ID
    int ntags(int pdgid) const { auto it = _tags.find(pdgid); return (it == _tags.end()) ? 0 : it->second; }
    /// Get whether there is a non-zero number of tags for the given PDG ID
    bool tagged(int pdgid) const { return (ntags(pdgid) > 0); }
    /// Set the number of tags for the given PDG ID
    void set_ntags(int pdgid, int ntag) { _tags[pdgid] = ntag; }

    /// Is this particle tagged as a b?
    bool btag() const { return tagged(5); }
    /// Set b-tag value
    void set_btag(int ntag=1) { set_ntags(5, ntag); }

    /// Is this particle tagged as a c?
    ///
    /// @note Can be simultaneously b-tagged unless the optional bool is set true
    bool ctag(bool not_if_b=false) const {
      if (not_if_b) return tagged(5) ? false : tagged(4);
      return tagged(4);
    }
    /// Set c-tag value
    void set_ctag(int ntag=1) { set_ntags(4, ntag); }

    /// @}


    /// @name FastJet information
    /// @{

    /// Get the contained PseudoJet object (const)
    const FJNS::PseudoJet& pseudojet() const { return _pj; }

    /// Get the contained PseudoJet object
    FJNS::PseudoJet& pseudojet() { return _pj; }

    /// Set the contained PseudoJet object
    void set_pseudojet(const FJNS::PseudoJet& pj) { _pj = pj; }

    /// @brief Access the ClusterSequence object if possible (can be null)
    ///
    /// Optional template arg can be used to cast to a specific derived CS type if wanted.
    template <typename CS=FJNS::ClusterSequence>
    typename std::shared_ptr<const CS> clusterseq() const {  
      return std::shared_ptr<const CS>(clusterseq_raw<CS>());
    }
    
    /// @brief Access the ClusterSequence object if possible (can be null)
    ///
    /// Optional template arg can be used to cast to a specific derived CS type if wanted.
    template <typename CS=FJNS::ClusterSequence>
    const CS* clusterseq_raw() const {
      return dynamic_cast<const CS*>(_pj.associated_cs());
    }

    /// @}

  };


  /// @defgroup jet_const Jet constness conversion
  /// @{

  /// Convenience Jet cast to const
  inline const Jet* mkconst(Jet* jet) {
    return const_cast<const Jet*>(jet);
  }

  /// Convenience Jet cast to non-const
  inline Jet* mkunconst(const Jet* cjet) {
    return const_cast<Jet*>(cjet);
  }

  /// Get a reference to a vector of Jets, with each member const
  inline std::vector<const Jet*>& mkconst(const std::vector<Jet*>& jets) {
    return * (std::vector<const Jet*>*)(void*) (&jets);
  }

  /// Get a reference to a vector of Jets, with each member non-const
  inline std::vector<Jet*>& mkunconst(const std::vector<const Jet*>& cjets) {
    return * (std::vector<Jet*>*) (void*) (&cjets);
  }

  /// @}



  // /// Function/functor for container<const Jet*> sorting (cf. std::less)
  // inline bool _cmpPtDescJet(const Jet* a, const Jet* b) {
  //   return a->pT2() >= b->pT2();
  // }


}
