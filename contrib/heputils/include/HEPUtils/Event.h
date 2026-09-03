// -*- C++ -*-
//
// This file is part of HEPUtils -- https://gitlab.com/hepcedar/heputils/
// Copyright (C) 2013-2026 Andy Buckley <andy.buckley@cern.ch>
//
// Embedding of HEPUtils code in other projects is permitted provided this
// notice is retained and the HEPUtils namespace and include path are changed.
//
#pragma once

#include "HEPUtils/Particle.h"
#include "HEPUtils/Jet.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <map>

namespace HEPUtils {


  /// Simple event class, separating particles into classes
  class Event {
  private:

    /// @name Internal particle / vector containers
    /// @{

    /// Event weights
    std::vector<double> _weights;
    std::vector<double> _weight_errs;

    /// @name Particle collections
    /// @{

    /// Typedef for multiple particle objects
    /// @todo Convert to unique/shared_ptr... but impacts API via vectors. Views?
    using Particles = std::vector<const Particle*>;

    /// Containers for various ~final-state particle-class collections
    mutable Particles _allparticles, _visibles, _invisibles, _photons, _electrons, _muons, _taus;
    mutable bool _stdparticles_sorted = true;

    /// Extensible map for non-standard particle collections
    std::map<std::string, Particles> _customparticles;
    mutable bool _customparticles_sorted = true;

    /// @}


    /// @name Jet collections
    /// @{

    /// Typedef for multiple jet objects
    /// @todo Convert to unique/shared_ptr... but impacts API via vectors. Views?
    using Jets = std::vector<const Jet*>;

    /// Jets collection(s) (mutable to allow sorting)
    mutable std::map<std::string, Jets> _jets;

    /// Typedef for the generic cluster-sequence type
    using CSeqBase = FJNS::ClusterSequence;
    /// Typedef for a smart ptr to the generic cluster-sequence type
    using CSeqBasePtr = std::shared_ptr<const FJNS::ClusterSequence>;
    
    /// Hold the cluster sequences corresponding to jets, to keep them alive
    std::map<std::string, CSeqBasePtr> _cseqs;

    /// @}


    /// Missing-momentum vector
    P4 _pmiss;

    /// @}


  private:

    /// Hide copy assignment, since shallow copies of Particle & Jet pointers create ownership/deletion problems
    /// @todo Reinstate as a deep copy uing cloneTo?
    void operator = (const Event& e) = delete;
    // {
    //   clear(); //< Delete current particles
    //   _weights = e._weights;
    //   _weight_errs = e._weight_errs;
    //   _stdparticles = e._stdparticles;
    //   _jets = e._jets;
    //   _cseqs = e._cseqs;
    //   _pmiss = e._pmiss;
    // }


  public:

    /// Default constructor
    Event() { clear(); }

    /// Constructor from list of Particles, plus (optional) event weights and weight errors
    Event(const std::vector<Particle*>& ps,
          const std::vector<double>& weights=std::vector<double>(),
          const std::vector<double>& weight_errs=std::vector<double>()) {
      clear();
      _weights = weights;
      _weight_errs = weight_errs;
      add_particles(ps);
    }

    /// Destructor (cleans up all passed Particles and calculated Jets)
    ~Event() {
      clear();
    }


    /// @name Cloning (= deep copy)
    /// @{

    /// Clone a copy on the heap
    Event* clone() const {
      Event* rtn = new Event();
      cloneTo(rtn);
      return rtn;
    }

    /// Clone a deep copy (new Particles and Jets allocated) into the provided event pointer
    void cloneTo(Event* e) const {
      assert(e != nullptr);
      cloneTo(*e);
    }


    /// Clone a deep copy (new Particles and Jets allocated) into the provided event object
    void cloneTo(Event& e) const {
      
      e.set_weights(_weights);
      e.set_weight_errs(_weight_errs);

      // Visibles+invisibles is the full set of std particles (avoids double-counting)
      e.add_particles(mkunconst(deepcopy(_visibles)));
      e.add_particles(mkunconst(deepcopy(_invisibles)));
      // The custom collections need to be cloned by name, and
      for (const auto& kv : _customparticles) {
        e.add_particles(mkunconst(deepcopy(particles(kv.first))), kv.first);
      }

      // Clone the jets, per-name
      for (const auto& kv : _jets) {
        const std::vector<const Jet*> js = jets(kv.first);
        for(size_t i = 0; i < js.size(); i++){
          e.add_jet(new Jet(*js[i]), kv.first);
        }
      }

      e._pmiss = _pmiss;
      e._cseqs = _cseqs; ///< @todo Cloneable?
      
    }

    /// @}


    /// Empty the event's weight, particle, jet, and MET collections
    void clear() {

      // Weights
      _weights.clear();
      _weight_errs.clear();

      // Particles: first the canonical collections, then the custom
      for (const Particle* p : _allparticles) delete p;
      _allparticles.clear();
      _visibles.clear(); _invisibles.clear();
      _photons.clear();
      _electrons.clear(); _muons.clear(); _taus.clear();
      // for (auto& kv : _customparticles) {
      //   for (const Particle* p : kv.second) delete p;
      // }
      _customparticles.clear();

      // Jets
      for (const std::string& jc : jet_collections()) clear_jets(jc);
      _jets.clear();
      _cseqs.clear();

      // MET
      _pmiss.clear();
      
    }


    /// @name Weights
    /// @{

    /// Set the event weights (also possible directly via non-const reference)
    void set_weights(const std::vector<double>& ws) {
      _weights = ws;
    }

    /// Set the event weight errors (also possible directly via non-const reference)
    void set_weight_errs(const std::vector<double>& werrs) {
      _weight_errs = werrs;
    }
    /// Set the event weights to the single given weight
    void set_weight(double w) {
      _weights.clear();
      _weights.push_back(w);
    }

    /// Set the event weight errors to the single given error
    void set_weight_err(double werr) {
      _weight_errs.clear();
      _weight_errs.push_back(werr);
    }

    /// Get the event weights (const)
    const std::vector<double>& weights() const {
      return _weights;
    }

    /// Get the event weights (non-const)
    std::vector<double>& weights() {
      return _weights;
    }

    /// Get the event weight errors (const)
    const std::vector<double>& weight_errs() const {
      return _weight_errs;
    }

    /// Get the event weight errors (non-const)
    std::vector<double>& weight_errs() {
      return _weight_errs;
    }
    /// Get a single event weight -- the nominal, by default
    double weight(size_t i=0) const {
      if (_weights.empty()) {
        if (i == 0) return 1;
        throw std::runtime_error("Trying to access non-default weight from empty weight vector");
      }
      return _weights[i];
    }

    /// Get a single event weight error -- the nominal, by default
    double weight_err(size_t i=0) const {
      if (_weight_errs.empty()) {
        if (i == 0) return 0;
        throw std::runtime_error("Trying to access non-default weight error from empty weight errors vector");
      }
      return _weight_errs[i];
    }

    /// @}


    /// @name Particles
    /// @{

    /// Check if a custom-particle name is available
    bool has_custom_particle(const std::string& key) const {
      return _customparticles.find(key) != _customparticles.end();
    }

    /// Get the list of custom particle-collection names
    std::vector<std::string> custom_particle_names() const {
      std::vector<std::string> rtn;
      for (const auto& kv : _customparticles) rtn.push_back(kv.first);
      return rtn;
    }


    /// @brief Add a standard particle to the event
    ///
    /// Supplied particle should be new'd, and Event will take ownership.
    ///
    /// @warning The event takes ownership of all supplied Particles -- even
    /// those it chooses not to add to its collections, which will be
    /// immediately deleted. Accordingly, the pointer passed by user code
    /// must be considered potentially invalid from the moment this function is called.
    ///
    /// @note pT-sorting has been primarily moved to lazy sorting of the
    /// mutable containers upon retrieval
    ///
    /// @todo "Lock" at some point so that jet finding etc. only get done once
    void add_particle(const Particle* p, bool ptsort=false) {
      std::cout << "Called add_particle line 284 "  << std::endl;
      _stdparticles_sorted = false;

      // All particles (canonical collection)
      /// @todo Remove, replace with C++20 range view and shared ptrs
      _allparticles.push_back(p);

      // Caching collections
      if (!p->is_visible()) {
        if (p->is_prompt()) _invisibles.push_back(p);
      } else {
        _visibles.push_back(p);
        if (p->is_prompt()) {
          if (p->pid() == 22) _photons.push_back(p);
          else if (p->abspid() == 11) _electrons.push_back(p);
          else if (p->abspid() == 13) _muons.push_back(p);
          else if (p->abspid() == 15) _taus.push_back(p);
        }
      }

      // Sort the collections
      if (ptsort) sort_particles();
    }

    // Force no implicit conversions to bool in the method above
    //
    /// @todo Can remove when the bool arguments are removed.
    template <typename T>
    void add_particle(const Particle* p, T) = delete;

    
    /// @todo Add an emplace_particle


    /// Add a set of standard particles to the event
    ///
    /// @note See add_particle for details.
    ///
    /// @warning Supplied particles should be new'd, and Event will take ownership.
    void add_particles(const std::vector<Particle*>& ps, bool ptsort=true) {
      // Add each particle, without sorting each time
      /// @todo This is not taking ownership!
      // for (const Particle* p : ps) add_particle(new Particle(*p), false);
      for (const Particle* p : ps) add_particle(p, false);

      // Finally sort the collections, once all new particles are in place
      if (ptsort) sort_particles();
    }


    /// @brief Add a custom particle of type `key` to the event
    ///
    /// Supplied particle should be new'd, and Event will take ownership.
    ///
    /// @warning The event takes ownership of all supplied Particles -- even
    /// those it chooses not to add to its collections, which will be
    /// immediately deleted. Accordingly, the pointer passed by user code
    /// must be considered potentially invalid from the moment this function is called.
    ///
    /// @note pT-sorting has been primarily moved to lazy sorting of the
    /// mutable containers upon retrieval
    ///
    /// @todo "Lock" at some point so that jet finding etc. only get done once
    void add_particle(const Particle* p, const std::string& key, bool ptsort=false) {
      std::cout << "Called add_particle line 348 with key " << key << std::endl;
      _customparticles_sorted = false;

      // Insert into both the canonical list and the custom
      _allparticles.push_back(p);
      _customparticles[key].push_back(p);

      // Sort if requested
      if (ptsort) sort_particles();
    }

    // Make sure that a char* key directs here rather than converting to bool!
    //
    /// @todo Can remove when the bool arguments are removed.
    void add_particle(const Particle* p, const char* key, bool ptsort=false) {
      std::cout << "Called add_particle line 363 with key " << key << std::endl;
      add_particle(p, std::string(key), ptsort);
    }

    /// Alias for backward-compatibility
    ///
    /// @deprecated ptsort will be removed eventually
    /// @todo Can remove when the bool arguments are removed.
    void add_particle(const Particle* p, bool ptsort, const std::string& key) {
      std::cout << "Called add_particle line 372 with key " << key << std::endl;
      add_particle(p, key, ptsort);
    }


    /// Add a set of custom particles of type `key` to the event
    ///
    /// @note See add_particle for details.
    ///
    /// @warning Supplied particles should be new'd, and Event will take ownership.
    void add_particles(const std::vector<Particle*>& ps, const std::string& key, bool ptsort=true) {
      // Add each particle, without sorting each time
      /// @todo This is not taking ownership!
      // for (const Particle* p : ps) add_particle(new Particle(*p), key, false);
      for (const Particle* p : ps) add_particle(p, key, false);

      // Finally sort the collections, once all new particles are in place
      if (ptsort) sort_particles();
    }

    /// Alias for backward-compatibility
    ///
    /// @deprecated ptsort will be removed eventually
    /// @todo Can remove when the bool arguments are removed.
    void add_particles(const std::vector<Particle*>& ps, bool ptsort, const std::string& key) {
      add_particles(ps, key, ptsort);
    }


    /// A mostly-internal function to sort the particle-vector caches
    void sort_particles() {
      if (_stdparticles_sorted && _customparticles_sorted) return;
      std::sort(_allparticles.begin(), _allparticles.end(), _cmpPtDescPtr<Particle>);

      if (!_stdparticles_sorted) {
        std::sort(_invisibles.begin(), _invisibles.end(), _cmpPtDescPtr<Particle>);
        std::sort(_photons.begin(), _photons.end(), _cmpPtDescPtr<Particle>);
        std::sort(_electrons.begin(), _electrons.end(), _cmpPtDescPtr<Particle>);
        std::sort(_muons.begin(), _muons.end(), _cmpPtDescPtr<Particle>);
        std::sort(_taus.begin(), _taus.end(), _cmpPtDescPtr<Particle>);
        _stdparticles_sorted = true;
      }

      if (!_customparticles_sorted) {
        for (auto& kv : _customparticles) {
          std::sort(kv.second.begin(), kv.second.end(), _cmpPtDescPtr<Particle>);
          _customparticles_sorted = true;
        }
      }

    }


    /// @brief Get all known particles
    ///
    /// @note Particles may overlap via parentage
    const std::vector<const Particle*>& particles() const {
      return _allparticles;
    }


    /// @brief Get named custom particles
    const std::vector<const Particle*>& particles(const std::string& key) const {
      return _customparticles.at(key);
    }
    /// @brief Get named custom particles as a more specific templated ptr type
    ///
    /// @note Returns as a copy, due to need to rewrite the vector type.
    /// @todo Surely not necessary, it's the same ptrs? But you can't dynamic_cast a vector...
    template <typename P>
    std::vector<const P*> particles(const std::string& key) const {
      const std::vector<const Particle*>& ps = particles(key);
      std::vector<const P*> rtn;  rtn.reserve(ps.size());
      for (const Particle* p : ps) rtn.push_back( dynamic_cast<const P*>(p) );
      return rtn;
    }

    /// @brief Get named custom particles (non-const)
    std::vector<Particle*>& particles(const std::string& key) {
      return mkunconst(_customparticles[key]);
    }
    /// @brief Get named custom particles as a more specific templated ptr type (non-const)
    ///
    /// @note Returns as a copy, due to need to rewrite the vector type.
    /// @todo Surely not necessary, it's the same ptrs? But you can't dynamic_cast a vector...
    template <typename P>
    std::vector<P*> particles(const std::string& key) {
      std::vector<Particle*>& ps = mkunconst(_customparticles[key]);
      std::vector<P*> rtn;  rtn.reserve(ps.size());
      for (Particle* p : ps) rtn.push_back( dynamic_cast<P*>(p) );
      return rtn;
    }


    // /// @brief Get all final state particles (requires C++20 range concat)
    // ///
    // /// @note Small overlap of taus and e/mu?
    // const std::vector<const Particle*> fsparticles() const {
    //   return ...;
    // }


    /// @brief Get visible final-state particles
    ///
    /// @note Small overlap of taus and e/mu?
    const std::vector<const Particle*>& visible_particles() const {
      return _visibles;
    }
    /// Get visible final-state particles (non-const)
    std::vector<Particle*>& visible_particles() {
      return mkunconst(_visibles);
    }


    /// @brief Get invisible final-state particles
    ///
    /// @note Both prompt and non-prompt... correct?
    const std::vector<const Particle*>& invisible_particles() const {
      return _invisibles;
    }
    /// Get invisible final-state particles (non-const)
    std::vector<Particle*>& invisible_particles() {
      return mkunconst(_invisibles);
    }


    /// Get prompt electrons
    const std::vector<const Particle*>& electrons() const {
      return _electrons;
    }
    /// Get prompt electrons (non-const)
    std::vector<Particle*>& electrons() {
      return mkunconst(_electrons);
    }


    /// Get muons
    const std::vector<const Particle*>& muons() const {
      return _muons;
    }
    /// Get muons (non-const)
    std::vector<Particle*>& muons() {
      return mkunconst(_muons);
    }


    /// Get prompt (hadronic) taus
    const std::vector<const Particle*>& taus() const {
      return _taus;
    }
    /// Get prompt (hadronic) taus (non-const)
    std::vector<Particle*>& taus() {
      return mkunconst(_taus);
    }


    /// Get prompt photons
    const std::vector<const Particle*>& photons() const {
      return _photons;
    }
    /// Get prompt photons (non-const)
    std::vector<Particle*>& photons() {
      return mkunconst(_photons);
    }

    /// @}


    /// @name Jets
    ///
    /// @{

    /// Get the list of jet-collection names
    std::vector<std::string> jet_collections() const {
      std::vector<std::string> rtn;
      for (const auto& kv : _jets) rtn.push_back(kv.first);
      return rtn;
    }
    /// Alias
    std::vector<std::string> jet_names() const {
      return jet_collections();
    }

    /// Check if a jet-collection name is available
    bool has_jets(const std::string& key) const {
      return _jets.find(key) != _jets.end();
    }


    // Implementation function, to avoid const/non-const duplication below
    std::vector<const Jet*>& _get_jets(const std::string& key) const {
      std::vector<const Jet*>& rtn = _jets[key];
      // std::sort(rtn.begin(), rtn.end(), _cmpPtDescPtr<Jet>); //< not thread-safe!
      return rtn;
    }

    /// @brief Get a jet collection (not including charged leptons or photons)
    const std::vector<const Jet*>& jets(const std::string& key) const {
      return _get_jets(key);
    }

    /// @brief Get a jet collection (not including charged leptons or photons) (non-const)
    std::vector<Jet*>& jets(const std::string& key) {
      return mkunconst(_get_jets(key));
    }

    
    /// @brief Set a jet collection
    ///
    /// @warning The Jets should be new'd; Event will take ownership.
    ///
    /// @todo "Lock" at some point so that jet finding etc. only get done once
    ///
    /// @note This resets the cluster sequence, but as a shared_ptr is used for storage,
    ///   any existing shared_ptr links to the previous one will keep it alive.
    void set_jets(const std::vector<const Jet*>& jets, const std::string& key) {
      _jets[key] = jets;
      std::sort(_jets[key].begin(), _jets[key].end(), _cmpPtDescPtr<Jet>);
      set_clusterseq(jets.front()->clusterseq(), key);
    }
    // /// @brief Set the jets collection (non-const input)
    // void set_jets(const std::vector<Jet*>& jets, const std::string& key) {
    //   set_jets(mkconst(jets), key);
    // }


    /// @brief Clear a jet collection
    ///
    /// @note This resets the cluster sequence, but as a shared_ptr is used for storage,
    ///   any existing shared_ptr links to the previous one will keep it alive.
    void clear_jets(const std::string& key) {
      for (const Jet* j : jets(key)) delete j;
      _jets.erase(key);
      _cseqs.erase(key);
    }
    

    /// @brief Add a jet to a jet collection
    ///
    /// @warning The Jet should be new'd; Event will take ownership.
    ///
    /// @todo "Lock" at some point so that jet finding etc. only get done once
    void add_jet(const Jet* j, const std::string& key) {
      _jets[key].push_back(j);
      std::sort(_jets[key].begin(), _jets[key].end(), _cmpPtDescPtr<Jet>);
      // Check that the CSeq on the added jet is consistent with this collection
      /// @todo Needs more care that the cseq pointer is live
      // if (_cseqs.find(key) != _cseqs.end() && _cseqs.at(key) &&
      //     !_jets.at(key).empty() && !_jets.at(key).front()->clusterseq() &&
      //     _cseqs.at(key) != _jets.at(key).front()->clusterseq()) {
      //   throw std::runtime_error("Event::add_jet() received a jet whose cluster sequence mismatched the active one for that collection");
      // }
    }
    // /// @brief Add a jet to the jets collection (non-const input)
    // void add_jet(Jet* j, const std::string& key) {
    //   add_jet(mkconst(j), key);
    // }

    
    /// @brief Access the jets' ClusterSequence object if possible (can be null)
    ///
    /// Optional template arg can be used to cast to a specific derived CS type if wanted.
    template <typename CS=FJNS::ClusterSequence>
    typename std::shared_ptr<const CS> clusterseq(const std::string& key) const {
      return std::dynamic_pointer_cast<const CS>(_cseqs.find(key)->second);
    }

    // /// @brief Non-const access to the jets' ClusterSequence object if possible (can be null)
    // ///
    // /// Optional template arg can be used to cast to a specific derived CS type if wanted.
    // template <typename CS=FJNS::ClusterSequence>
    // std::shared_ptr<CS> clusterseq(const std::string& key) {
    //   return std::dynamic_pointer_cast<CS>(_cseq->find(key).second);
    // }

    /// Set a specific cluster sequence for the named jet collection (which must currently be empty)
    ///
    /// @warning The CS should be new'd; Event will take ownership via a shared_ptr
    template <typename CS=FJNS::ClusterSequence>
    void set_clusterseq(std::shared_ptr<const CS> cseq, const std::string& key) {
      if (_cseqs.find(key) != _cseqs.end() && !_cseqs.empty()) {
	throw std::runtime_error("Event::set_clusterseq() called for a non-empty jet collection");
      }
      _cseqs[key] =  cseq;
    }

    
    /// Create and run a new cluster sequence for the named jet collection
    ///
    /// @warning The CS will be new'd, and Event will take ownership via a shared_ptr
    ///
    /// @note The resulting pseudojets from this still need to be manually set as Jets.
    ///
    /// @todo How to run a more advanced CS like the active- or Voronoi-area ones?
    template <typename CS=FJNS::ClusterSequence>
    CSeqBasePtr emplace_clusterseq(std::vector<FJNS::PseudoJet>& jetparticles, const FJNS::JetDefinition& jetdef, const std::string& key) {
      if (_cseqs.find(key) != _cseqs.end() && !_cseqs.empty()) {
	throw std::runtime_error("Event::emplace_clusterseq() called for a non-empty jet collection");
      }
      _cseqs[key] = std::make_shared<CS>(jetparticles, jetdef);
      return _cseqs[key];
    }
   
    /// @}


    /// @name Missing momentum
    /// @{

    /// Get the missing momentum vector
    /// @note Not _necessarily_ the sum over momenta of final state invisibles
    const P4& missingmom() const {
      return _pmiss;
    }

    /// Set the missing momentum vector
    /// @todo Not _necessarily_ the sum over momenta of final state invisibles
    void set_missingmom(const P4& pmiss) {
      _pmiss = pmiss;
    }

    /// Get the missing transverse momentum in GeV
    double met() const {
      return missingmom().pT();
    }

    /// @}


  };


}
