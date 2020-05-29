//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Helper functions for converting between
///  different event types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///  \author Anders Kvellestad
///  \author Pat Scott
///  \author Martin White
///
///  *********************************************

#pragma once

#include "gambit/ColliderBit/colliders/Pythia8/Py8Utils.hpp"
#include "gambit/Elements/shared_types.hpp"//AddedTP Aug19 for debug

#include "HEPUtils/Event.h"
#include "HEPUtils/Particle.h"
#include "HEPUtils/FastJet.h"
#include "HEPUtils/FastJet.h"
#include "MCUtils/PIDCodes.h"

#ifndef EXCLUDE_HEPMC
#include "HepMC3/GenEvent.h"
#include "HepMC3/GenParticle.h"
#endif


#ifndef UNIFIED_FUNCTIONS
#define UNIFIED_FUNCTIONS

//Namespace for all the overloaded functions so that the convertParticleEvent function
//is fully general: basically, for every function there is a version for HEPMC::GenParticlePtr
//and a version for Pythia Particles (which are templated functions).
//Tomek Procter Oct 2019 - maybe it would be cleaner if all these functions were in another header?
namespace UnifiedEventConversionFunctions
{

  #ifndef EXCLUDE_HEPMC
  inline int get_unified_pid(const HepMC3::GenParticlePtr &gp)
  {
    return gp->pid();
  }
  #endif

  template<typename ParticleP>
  int get_unified_pid(ParticleP p)
  {
    return p.id();
  }


  #ifndef EXCLUDE_HEPMC
  inline bool get_unified_isFinal(const HepMC3::GenParticlePtr &gp)
  {
    return (gp->status() == 1);
  }
  #endif

  template<typename ParticleP>
  bool get_unified_isFinal(ParticleP p)
  {
    return (p.isFinal());
  }


  #ifndef EXCLUDE_HEPMC
  inline double get_unified_eta(const HepMC3::GenParticlePtr &gp)
  {
    //n.b. I'm writing this manually because using the function in MCUtils/HepMCVectors.h
    //at the moment seems to stop it compiling for some reason??
    const HepMC3::FourVector& hp4 = gp->momentum();
    double magnitude = sqrt(hp4.px()*hp4.px() + hp4.py()*hp4.py() + hp4.pz()*hp4.pz());
    return atanh(hp4.pz()/magnitude);
  }
  #endif

  template <typename ParticleP>
  inline double get_unified_eta(ParticleP p)
  {
    return p.eta();
  }


  #ifndef EXCLUDE_HEPMC
  inline HEPUtils::P4 get_unified_momentum(const HepMC3::GenParticlePtr &gp)
  {
    const HepMC3::FourVector& hp4 = gp->momentum();
    return HEPUtils::P4::mkXYZE(hp4.px(), hp4.py(), hp4.pz(), hp4.e());
  }
  #endif

  template <typename ParticleP>
  inline HEPUtils::P4 get_unified_momentum(ParticleP p)
  {
    return HEPUtils::P4::mkXYZE(p.px(), p.py(), p.pz(), p.e());
  }


  #ifndef EXCLUDE_HEPMC
  inline FJNS::PseudoJet get_unified_pseudojet(const HepMC3::GenParticlePtr &gp)
  {
    const HepMC3::FourVector& hp4 = gp->momentum();
    return FJNS::PseudoJet(hp4.px(), hp4.py(), hp4.pz(), hp4.e());
  }
  #endif

  template <typename ParticleP>
  inline FJNS::PseudoJet get_unified_pseudojet(ParticleP p)
  {
    FJNS::PseudoJet psej = FJNS::PseudoJet(p.p().px(), p.p().py(), p.p().pz(), p.p().e());
    return psej;
  }


  //Tomek Procter Aug 19. Note the MCUtils isParton function only checks
  // for quarks/gluons (while in pythia, the function used in Gambit includes
  //diquarks too), so I'm manually defining this function using the isParton
  //is diquark options in MCUtils
  inline bool HEPMC3_isParton(int pid)
  {
    return (MCUtils::PID::isParton(pid) || MCUtils::PID::isDiquark(pid));
  }

  #ifndef EXCLUDE_HEPMC
  inline bool get_unified_fromHadron(const HepMC3::GenParticlePtr gp, const std::vector<HepMC3::GenParticlePtr> &pevt, int i)
  {
    // For HepMC3 events, I wrote this function, it mimics exactly what the Py8Utils.cpp function does.
    // This seems highly unlikely to change - apparently this is just the standard way its done.
    // Looping through parents is tricky so I won't unify it unless absolutely necesarry.
    // note the meaningless int argument to make sure the same function call works both for hepmc3
    // and pythia.
    if (MCUtils::PID::isHadron(gp->pid())) return true;
    if (HEPMC3_isParton(abs(gp->pid()))) return false; // stop the walking at the end of the hadron level
    auto parent_vector = (gp->parents());
    if (parent_vector.size() == 0) return false;
    for (const HepMC3::GenParticlePtr parent : parent_vector)
    {
      if (get_unified_fromHadron(parent, pevt, i)) return true;
    }
    return false;
  }
  #endif

  template <typename ParticleP, typename EventT>
  inline bool get_unified_fromHadron(ParticleP&, const EventT &pevt, int i)
  {
    //Just call the function in Py8Utils.cpp
    return Gambit::ColliderBit::fromHadron(i, pevt);
  }

  #ifndef EXCLUDE_HEPMC
  inline int get_unified_mother1(const HepMC3::GenParticlePtr&)
  {
    return 0;
  }
  inline int get_unified_mother2(const HepMC3::GenParticlePtr&)
  {
    return 0;
  }
  #endif

  template <typename ParticleP>
  inline int get_unified_mother1(ParticleP &p)
  {
    return p.mother1();
  }
  template <typename ParticleP>
  inline int get_unified_mother2(ParticleP &p)
  {
    return p.mother2();
  }

  template <typename ParticleP, typename EventT>
  inline int get_unified_mother1_pid(ParticleP &p, EventT &pevt)
  {
    return pevt[p.mother1()].id();
  }
  template <typename ParticleP, typename EventT>
  inline int get_unified_mother2_pid(ParticleP &p, EventT &pevt)
  {
    return pevt[p.mother2()].id();
  }

  #ifndef EXCLUDE_HEPMC
  //shouldn't ever need to call a hepmc3 version but for safety here's one that just returns 0.
  inline int get_unified_mother1_pid(const HepMC3::GenParticlePtr&, const std::vector<HepMC3::GenParticlePtr>&)
  {
    return 0;
  }
  //shouldn't ever need to call a hepmc3 version but for safety here's one that just returns 0.
  inline int get_unified_mother2_pid(const HepMC3::GenParticlePtr&, const std::vector<HepMC3::GenParticlePtr>&)
  {
    return 0;
  }
  #endif


  #ifndef EXCLUDE_HEPMC
  //Note! The unified_child_id_results MUST BE EMPTY as I don't clear it in the function.
  inline void get_unified_child_ids(const HepMC3::GenParticlePtr &gp, const std::vector<HepMC3::GenParticlePtr>&, std::vector<int> &unified_child_id_results)
  {
    auto child_vector = gp->children();
    for (const HepMC3::GenParticlePtr child: child_vector)
    {
      unified_child_id_results.push_back(child->pid());
    }
  }
  #endif

  //Note! The unified_child_id_results MUST BE EMPTY as I don't clear it in the function.
  template<typename ParticleP, typename EventT>
  void get_unified_child_ids(ParticleP &p, EventT &pevt, std::vector<int> &unified_child_id_results)
  {
    std::vector<int> daughter_list = p.daughterList();
    for (int daughter : daughter_list)
    {
      unified_child_id_results.push_back(pevt[daughter].id());
    }
  }
}

#endif






namespace Gambit
{

  namespace ColliderBit
  {

    using namespace UnifiedEventConversionFunctions;

    /// Convert a hadron-level EventT into an unsmeared HEPUtils::Event
    /// @todo Overlap between jets and prompt containers: need some isolation in MET calculation
    template<typename EventT>
    void convertParticleEvent(const EventT& pevt, HEPUtils::Event& result, double antiktR, double jet_pt_min)
    {
      result.clear();

      std::vector<FJNS::PseudoJet> bhadrons; //< for input to FastJet b-tagging
      std::vector<HEPUtils::Particle> bpartons, cpartons, tauCandidates;
      HEPUtils::P4 pout; //< Sum of momenta outside acceptance
      std::vector<FJNS::PseudoJet> jetparticles;

      for (int i = 0; i < pevt.size(); i++)
      {
        const auto &p = pevt[i];
        const int pid = get_unified_pid(p);
        const int apid = abs(pid);
        const HEPUtils::P4 p4 = get_unified_momentum(p);


      //b, c and tau idenitification:

    // Find last b-hadrons in b decay chains as the best proxy for b-tagging
    /// @todo Temporarily using quark-based tagging instead -- fix
        if (apid == 5){
          bool isGoodB = true;
          std::vector<int> childIDs;
          get_unified_child_ids(p, pevt, childIDs);
          for (int childID : childIDs)
          {
            if (abs(childID) == 5) isGoodB = false;
          }
          if (isGoodB)
          {
            bpartons.push_back(HEPUtils::Particle(p4,pid));
          }
        }
    // Find last c-hadrons in decay chains as the best proxy for c-tagging
      /// @todo Temporarily using quark-based tagging instead -- fix
        if (apid == 4) {
          bool isGoodC = true;
          std::vector<int> childIDs;
          get_unified_child_ids(p, pevt, childIDs);
          for (int childID : childIDs)
          {
            if (abs(childID) == 4) isGoodC = false;
          }
          if (isGoodC)
          {
            cpartons.push_back(HEPUtils::Particle(p4,pid));
          }
        }
        // Find tau candidates
        if (apid == MCUtils::PID::TAU)
        {
          bool isGoodTau=true;
          std::vector<int> childIDs;
          get_unified_child_ids(p, pevt, childIDs);
          int abschildID;
          for (int childID : childIDs)
          {
            // Veto leptonic taus
            /// @todo What's wrong with having a W daughter? Doesn't that just mark a final tau?
            abschildID = abs(childID);
            if (abschildID == MCUtils::PID::ELECTRON || abschildID == MCUtils::PID::MUON ||
                abschildID == MCUtils::PID::WPLUSBOSON || abschildID == MCUtils::PID::TAU)
              {
                isGoodTau = false;
              }
          }
          if (isGoodTau) {
            tauCandidates.push_back(HEPUtils::Particle(p4, pid));
          }
        }

        //Now we consider final state particle for jet inputs and MET: Gambit originally
        //did this in two loops, but CBS in just the one. I'm doing just one, it avoids a
        //few redfinitions, I don't think it makes a huge difference either way?

        //We only want final state particles:
        if (!get_unified_isFinal(p)) continue;

        //Check there's no partons.
        //This wasn't implemented in CBS, but for completeness here it is.
        if (pid == 21 || abs(pid) <= 6)
        {
          std::ostringstream sid;
          bool gotmother = false;
          //HepMC has no equivalent of the .mother1, .mother2 call as far as I can see,
          //so the HepMC3 mother function will just return 0, and gotmother will always
          //be false - which means it won't try and print non-existent event info.
          if (get_unified_mother1(p) != 0 ){gotmother = true; sid << get_unified_mother1_pid(p, pevt);}
          if (get_unified_mother2(p) != 0 ){gotmother = true; sid << get_unified_mother2_pid(p, pevt);}
          if (gotmother) sid << " -> ";
          sid << pid;
          ColliderBit_error().forced_throw(LOCAL_INFO, "Found final-state parton " + sid.str() + " in particle-level event converter: "
              "reconfigure your generator to include hadronization, or Gambit to use the partonic event converter.");
          //Tomek Procter October 2019: This needs to be fixed so you can throw the error in BOTH CBS and Gambit (or else not to try and
          //throw it in CBS, as it wasn't there before and didn't make any difference)
          //commented out for now so I can get everything else working.
        }


        // Add particle outside ATLAS/CMS acceptance to MET and then ignore said particle.
        /// @todo Move out-of-acceptance MET contribution to BuckFast
        if (std::abs(get_unified_eta(p)) > 5.0)
        {
          pout += p4;
          continue;
        }

        // Promptness: for leptons and photons we're only interested if they don't come from hadron/tau decays
        const bool prompt = !get_unified_fromHadron(p, pevt, i);
        const bool visible = MCUtils::PID::isStrongInteracting(pid) || MCUtils::PID::isEMInteracting(pid);

        // Add prompt and invisible particles as individual particles
        if (prompt || !visible)
        {
          HEPUtils::Particle* gp = new HEPUtils::Particle(p4, pid);
          gp->set_prompt();
          result.add_particle(gp);
        }

        // All particles other than invisibles and muons are jet constituents
        // Matthias added test to keep non-prompt particles
        if (visible && apid != MCUtils::PID::MUON)
        {
          jetparticles.push_back(get_unified_pseudojet(p));
        }
      }

      /// Jet finding
      /// @todo Choose jet algorithm via detector _settings? Run several algs?
      const FJNS::JetDefinition jet_def(FJNS::antikt_algorithm, antiktR);
      FJNS::ClusterSequence cseq(jetparticles, jet_def);
      std::vector<FJNS::PseudoJet> pjets = sorted_by_pt(cseq.inclusive_jets(jet_pt_min));



      /// Do jet b-tagging, etc. and add to the Event
      /// @todo Use ghost tagging?
      /// @note We need to _remove_ this b-tag in the detector sim if outside the tracker acceptance!
      for (auto& pj : pjets)
      {
        HEPUtils::P4 jetMom = HEPUtils::mk_p4(pj);
        /// @todo Replace with HEPUtils::any(bhadrons, [&](const auto& pb){ pj.delta_R(pb) < 0.4 })
        bool isB = false;
        for (HEPUtils::Particle& pb : bpartons) {
          if (jetMom.deltaR_eta(pb.mom()) < 0.4) { ///< @todo Hard-coded radius!!!
            isB = true;
            break;
          }
        }

        bool isC = false;
        for (HEPUtils::Particle& pc : cpartons) {
          if (jetMom.deltaR_eta(pc.mom()) < 0.4) { ///< @todo Hard-coded radius!!!
            isC = true;
            break;
          }
        }

        bool isTau = false;
        for (HEPUtils::Particle& ptau : tauCandidates){
          if (jetMom.deltaR_eta(ptau.mom()) < 0.5){ ///< @todo Hard-coded radius!!!
            isTau = true;
            break;
          }
        }

        // Add to the event (use jet momentum for tau)
        if (isTau) {
          HEPUtils::Particle* gp = new HEPUtils::Particle(HEPUtils::mk_p4(pj), MCUtils::PID::TAU);
          gp->set_prompt();
          result.add_particle(gp);
        }
        result.add_jet(new HEPUtils::Jet(HEPUtils::mk_p4(pj), isB, isC));
      }

      /// Calculate missing momentum
      //
      // From balance of all visible momenta (requires isolation)
      // const std::vector<Particle*> visibles = result.visible_particles();
      // HEPUtils::P4 pvis;
      // for (size_t i = 0; i < visibles.size(); ++i) {
      //   pvis += visibles[i]->mom();
      // }
      // for (size_t i = 0; i < result.jets.size(); ++i) {
      //   pvis += result.jets[i]->mom();
      // }
      // set_missingmom(-pvis);
      //
      // From sum of invisibles, including those out of range
      for (size_t i = 0; i < result.invisible_particles().size(); ++i) {
        pout += result.invisible_particles()[i]->mom();
      }
      result.set_missingmom(pout);

      #ifdef COLLIDERBIT_DEBUG
        // Print event summary
        cout << "  MET  = " << result.met() << " GeV" << endl;
        cout << "  #e   = " << result.electrons().size() << endl;
        cout << "  #mu  = " << result.muons().size() << endl;
        cout << "  #tau = " << result.taus().size() << endl;
        cout << "  #jet = " << result.jets().size() << endl;
        cout << "  #pho  = " << result.photons().size() << endl;
        cout << endl;
      #endif
    }



    /// Convert a partonic (no hadrons) EventT into an unsmeared HEPUtils::Event
    template<typename EventT>
    void convertPartonEvent(const EventT& pevt, HEPUtils::Event& result, double antiktR, double jet_pt_min)
    {
      result.clear();

      std::vector<HEPUtils::Particle> tauCandidates;

      // Make a first pass of non-final particles to gather taus
      for (int i = 0; i < pevt.size(); ++i)
      {
        const auto& p = pevt[i];

        // Find last tau in prompt tau replica chains as a proxy for tau-tagging
        if (p.idAbs() == MCUtils::PID::TAU) {
          std::vector<int> tauDaughterList = p.daughterList();
          HEPUtils::P4 tmpMomentum;
          bool isGoodTau=true;

          for (size_t daughter = 0; daughter < tauDaughterList.size(); daughter++)
          {
            const auto& pDaughter = pevt[tauDaughterList[daughter]];
            int daughterID = pDaughter.idAbs();
            if (daughterID == MCUtils::PID::ELECTRON || daughterID == MCUtils::PID::MUON ||
                daughterID == MCUtils::PID::WPLUSBOSON || daughterID == MCUtils::PID::TAU)
              isGoodTau = false;
            if (daughterID != MCUtils::PID::TAU) tmpMomentum += mk_p4(pDaughter.p());
          }

          if (isGoodTau) {
            tauCandidates.push_back(HEPUtils::Particle(mk_p4(p.p()), p.id()));
          }
        }
      }

      std::vector<FJNS::PseudoJet> jetparticles; //< Pseudojets for input to FastJet
      HEPUtils::P4 pout; //< Sum of momenta outside acceptance

      // Make a single pass over the event to gather final leptons, partons, and photons
      for (int i = 0; i < pevt.size(); ++i)
      {
        const auto& p = pevt[i];

        // We only use "final" partons, i.e. those with no children. So Py8 must have hadronization disabled
        if (!p.isFinal()) continue;

        // Only consider partons within ATLAS/CMS acceptance
        /// @todo We should leave this for the detector sim / analysis to deal with
        if (std::abs(p.eta()) > 5.0) {
          pout += mk_p4(p.p());
          continue;
        }

        // Find electrons/muons/taus/photons to be treated as prompt (+ invisibles)
        /// @todo *Some* photons should be included in jets!!! Ignore for now since no FSR
        /// @todo Lepton dressing
        const bool prompt = isFinalPhoton(i, pevt) || (isFinalLepton(i, pevt)); // && std::abs(p.id()) != MCUtils::PID::TAU);
        const bool visible = MCUtils::PID::isStrongInteracting(p.id()) || MCUtils::PID::isEMInteracting(p.id());
        if (prompt || !visible) {
          HEPUtils::Particle* gp = new HEPUtils::Particle(mk_p4(p.p()), p.id());
          gp->set_prompt();
          result.add_particle(gp);
        }

        // Everything other than invisibles and muons, including taus & partons are jet constituents
        /// @todo Only include hadronic tau fraction?
        // if (visible && (isFinalParton(i, pevt) || isFinalTau(i, pevt))) {
        if (visible && p.idAbs() != MCUtils::PID::MUON) {
          FJNS::PseudoJet pj = mk_pseudojet(p.p());
          //pj.set_user_index(std::abs(p.id()));
          jetparticles.push_back(pj);

        }

      }

      /// Jet finding
      /// @todo choose jet algorithm via _settings?
      const FJNS::JetDefinition jet_def(FJNS::antikt_algorithm, antiktR);
      FJNS::ClusterSequence cseq(jetparticles, jet_def);
      std::vector<FJNS::PseudoJet> pjets = sorted_by_pt(cseq.inclusive_jets(jet_pt_min));

      // Add to the event, with b-tagging info"
      for (const FJNS::PseudoJet& pj : pjets) {
        // Do jet b-tagging, etc. by looking for b quark constituents (i.e. user index = |parton ID| = 5)
        /// @note This b-tag is removed in the detector sim if outside the tracker acceptance!
        const bool isB = HEPUtils::any(pj.constituents(),
                 [](const FJNS::PseudoJet& c){ return c.user_index() == MCUtils::PID::BQUARK; });
        const bool isC = HEPUtils::any(pj.constituents(),
                 [](const FJNS::PseudoJet& c){ return c.user_index() == MCUtils::PID::CQUARK; });
        result.add_jet(new HEPUtils::Jet(HEPUtils::mk_p4(pj), isB, isC));

        bool isTau=false;
        for(auto& ptau : tauCandidates){
          HEPUtils::P4 jetMom = HEPUtils::mk_p4(pj);
          if(jetMom.deltaR_eta(ptau.mom()) < 0.5){
            isTau=true;
            break;
          }
        }
        // Add to the event (use jet momentum for tau)
        if (isTau) {
          HEPUtils::Particle* gp = new HEPUtils::Particle(HEPUtils::mk_p4(pj), MCUtils::PID::TAU);
          gp->set_prompt();
          result.add_particle(gp);
        }
      }

      /// Calculate missing momentum
      //
      // From balance of all visible momenta (requires isolation)
      // const std::vector<Particle*> visibles = result.visible_particles();
      // HEPUtils::P4 pvis;
      // for (size_t i = 0; i < visibles.size(); ++i) {
      //   pvis += visibles[i]->mom();
      // }
      // for (size_t i = 0; i < result.jets.size(); ++i) {
      //   pvis += result.jets[i]->mom();
      // }
      // set_missingmom(-pvis);
      //
      // From sum of invisibles, including those out of range
      for (const HEPUtils::Particle* p : result.invisible_particles())
        pout += p->mom();
      result.set_missingmom(pout);
    }

  }

}
