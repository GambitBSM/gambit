//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  BuckFast smearing functions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///  \author Abram Krislock
///  \author Anders Kvellestad
///  \author Pat Scott
///  \author Martin White
///
///  *********************************************

#include "gambit/ColliderBit/detectors/BuckFast.hpp"
#include "gambit/ColliderBit/detectors/Py8Utils.hpp"

#include "MCUtils/PIDCodes.h"

namespace Gambit
{

  namespace ColliderBit
  {

    /// Process an event with BuckFast
    template<typename EventT>
    void BuckFast<EventT>::processEvent(const EventT& eventIn, HEPUtils::Event& eventOut) const
    {
      if (partonOnly)
        convertPartonEvent(eventIn, eventOut);
      else
        convertParticleEvent(eventIn, eventOut);

      // Electron smearing and efficiency
      /// @todo Run-dependence?
      if (smearElectronEnergy != NULL) smearElectronEnergy(eventOut.electrons());

      // Muon smearing and efficiency
      /// @todo Run-dependence?
      if (smearMuonMomentum != NULL) smearMuonMomentum(eventOut.muons());

      //Smear taus
      if (smearTaus != NULL) smearTaus(eventOut.taus());

      // Smear jet momenta
      if (smearJets != NULL) smearJets(eventOut.jets());

      // Unset b-tags outside |eta|=2.5
      for (HEPUtils::Jet* j : eventOut.jets())
      {
        if (j->abseta() > 2.5) j->set_btag(false);
      }
    }

    /// Convert a hadron-level EventT into an unsmeared HEPUtils::Event
    /// @todo Overlap between jets and prompt containers: need some isolation in MET calculation
    template<typename EventT>
    void BuckFast<EventT>::convertParticleEvent(const EventT& pevt, HEPUtils::Event& result) const
    {
      result.clear();

      std::vector<FJNS::PseudoJet> bhadrons; //< for input to FastJet b-tagging
      std::vector<HEPUtils::Particle> bpartons, cpartons, tauCandidates;
      HEPUtils::P4 pout; //< Sum of momenta outside acceptance

      // Make a first pass of non-final particles to gather b-hadrons and taus
      for (int i = 0; i < pevt.size(); ++i)
      {
        const auto& p = pevt[i];

        // Find last b-hadrons in b decay chains as the best proxy for b-tagging
        /// @todo Temporarily using quark-based tagging instead -- fix
        if (p.idAbs() == 5) {
          bool isGoodB = true;
          const std::vector<int> bDaughterList = p.daughterList();
          for (size_t daughter = 0; daughter < bDaughterList.size(); daughter++)
          {
            const auto& pDaughter = pevt[bDaughterList[daughter]];
            int daughterID = pDaughter.idAbs();
            if (daughterID == 5) isGoodB = false;
          }
          if (isGoodB)
            bpartons.push_back(HEPUtils::Particle(mk_p4(p.p()), p.id()));
        }

        // Find last c-hadrons in decay chains as the best proxy for c-tagging
        /// @todo Temporarily using quark-based tagging instead -- fix
        if (p.idAbs() == 4) {
          bool isGoodC = true;
          const std::vector<int> cDaughterList = p.daughterList();
          for (size_t daughter = 0; daughter < cDaughterList.size(); daughter++)
          {
            const auto& pDaughter = pevt[cDaughterList[daughter]];
            int daughterID = pDaughter.idAbs();
            if (daughterID == 4) isGoodC = false;
          }
          if (isGoodC)
            cpartons.push_back(HEPUtils::Particle(mk_p4(p.p()), p.id()));
        }

        // Find tau candidates
        if (p.idAbs() == MCUtils::PID::TAU) {
          HEPUtils::P4 tmpMomentum;
          bool isGoodTau=true;
          const std::vector<int> tauDaughterList = p.daughterList();
          for (size_t daughter = 0; daughter < tauDaughterList.size(); daughter++)
          {
            const auto& pDaughter = pevt[tauDaughterList[daughter]];
            int daughterID = pDaughter.idAbs();
            // Veto leptonic taus
            /// @todo What's wrong with having a W daughter? Doesn't that just mark a final tau?
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

      // Loop over final state particles for jet inputs and MET
      std::vector<FJNS::PseudoJet> jetparticles;
      for (int i = 0; i < pevt.size(); ++i)
      {
        const auto& p = pevt[i];

        // Only consider final state particles
        if (!p.isFinal()) continue;

        // Check there's no partons!!
        if (p.id() == 21 || abs(p.id()) <= 6) {
          std::ostringstream sid;
          bool gotmother = false;
          if (p.mother1() != 0) { gotmother = true; sid << pevt[p.mother1()].id() << " "; }
          if (p.mother2() != 0) { gotmother = true; sid << pevt[p.mother2()].id() << " "; }
          if (gotmother) sid << " -> ";
          sid << p.id();
          ColliderBit_error().forced_throw(LOCAL_INFO, "Found final-state parton " + sid.str() + " in particle-level event converter: "
                                   "reconfigure your generator to include hadronization, or Gambit to use the partonic event converter.");
        }

        // Add particle outside ATLAS/CMS acceptance to MET
        /// @todo Move out-of-acceptance MET contribution to BuckFast
        if (std::abs(p.eta()) > 5.0) {
          pout += mk_p4(p.p());
          continue;
        }

        // Promptness: for leptons and photons we're only interested if they don't come from hadron/tau decays
        const bool prompt = !fromHadron(i, pevt); //&& !fromTau(i, pevt);
        const bool visible = MCUtils::PID::isStrongInteracting(p.id()) || MCUtils::PID::isEMInteracting(p.id());

        // Add prompt and invisible particles as individual particles
        if (prompt || !visible) {
          HEPUtils::Particle* gp = new HEPUtils::Particle(mk_p4(p.p()), p.id());
          gp->set_prompt();
          result.add_particle(gp);
        }

        // All particles other than invisibles and muons are jet constituents
        // Matthias added test to keep non-prompt particles
        if (visible && p.idAbs() != MCUtils::PID::MUON) jetparticles.push_back(mk_pseudojet(p.p()));
        // next case are visible non-prompt muons
        //if (visible && p.idAbs() == MCUtils::PID::MUON && !prompt) jetparticles.push_back(mk_pseudojet(p.p()));
        // next case are non-prompt neutrinos
        //if (!visible && !prompt) jetparticles.push_back(mk_pseudojet(p.p()));
      }

      /// Jet finding
      /// @todo Choose jet algorithm via detector _settings? Run several algs?
      const FJNS::JetDefinition jet_def(FJNS::antikt_algorithm, antiktR);
      FJNS::ClusterSequence cseq(jetparticles, jet_def);
      std::vector<FJNS::PseudoJet> pjets = sorted_by_pt(cseq.inclusive_jets(10));

      /// Do jet b-tagging, etc. and add to the Event
      /// @todo Use ghost tagging?
      /// @note We need to _remove_ this b-tag in the detector sim if outside the tracker acceptance!
      for (auto& pj : pjets) {
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
          if (jetMom.deltaR_eta(ptau.mom()) < 0.5){
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
    }

    /// Convert a partonic (no hadrons) EventT into an unsmeared HEPUtils::Event
    template<typename EventT>
    void BuckFast<EventT>::convertPartonEvent(const EventT& pevt, HEPUtils::Event& result) const
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
          pj.set_user_index(std::abs(p.id()));
          jetparticles.push_back(pj);
        }

      }

      /// Jet finding
      /// @todo choose jet algorithm via _settings?
      const FJNS::JetDefinition jet_def(FJNS::antikt_algorithm, antiktR);
      FJNS::ClusterSequence cseq(jetparticles, jet_def);
      std::vector<FJNS::PseudoJet> pjets = sorted_by_pt(cseq.inclusive_jets(10));
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
