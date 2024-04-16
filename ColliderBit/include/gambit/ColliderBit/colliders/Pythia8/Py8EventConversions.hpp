//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Helper functions for converting between
///  Pythia8 events and other event types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///  \author Anders Kvellestad
///  \author Pat Scott
///  \author Martin White
///  \author Are Raklev  June 2021
///  \author Chris Chang Nov 2023
///
///  *********************************************

#pragma once

#include "gambit/ColliderBit/colliders/EventConversionUtils.hpp"
#include "gambit/ColliderBit/colliders/BaseCollider.hpp"

//#define COLLIDERBIT_DEBUG


namespace Gambit
{

  namespace ColliderBit
  {

    using namespace EventConversion;

    /// Convert a hadron-level EventT into an unsmeared HEPUtils::Event
    /// @todo Overlap between jets and prompt containers: need some isolation in MET calculation
    template<typename EventT>
    void convertParticleEvent(const EventT& pevt, HEPUtils::Event& result, std::vector<jet_collection_settings> all_jet_collection_settings, str jetcollection_taus, double jet_pt_min)
    {
      result.clear();

      std::vector<FJNS::PseudoJet> bhadrons; //< for input to FastJet b-tagging
      std::vector<HEPUtils::Particle> bpartons, cpartons, tauCandidates, WCandidates, ZCandidates, hCandidates;
      HEPUtils::P4 pout; //< Sum of momenta outside acceptance
      std::vector<FJNS::PseudoJet> jetparticles;

      for (decltype(pevt.size()) i = 0; i < pevt.size(); i++)
      {
        const auto &p = pevt[i];
        const int pid = get_unified_pid(p);
        const int apid = abs(pid);
        const HEPUtils::P4 p4 = get_unified_momentum(p);

        //b, c and tau idenitification:

        // Find last b-hadrons in b decay chains as the best proxy for b-tagging
        /// @todo Temporarily using quark-based tagging instead -- fix
        if (apid == 5)
        {
          bool isGoodB = true;
          std::vector<int> childIDs;
          get_unified_child_ids(p, pevt, childIDs);
          for (int childID : childIDs)
          {
            if (abs(childID) == 5) isGoodB = false;
          }
          if (isGoodB) bpartons.push_back(HEPUtils::Particle(p4,pid));
        }

        // Find last c-hadrons in decay chains as the best proxy for c-tagging
        /// @todo Temporarily using quark-based tagging instead -- fix
        if (apid == 4)
        {
          bool isGoodC = true;
          std::vector<int> childIDs;
          get_unified_child_ids(p, pevt, childIDs);
          for (int childID : childIDs)
          {
            if (abs(childID) == 4) isGoodC = false;
          }
          if (isGoodC) cpartons.push_back(HEPUtils::Particle(p4,pid));
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
          if (isGoodTau) tauCandidates.push_back(HEPUtils::Particle(p4, pid));
        }

        // Find candidates for hadronically decaying bosons for fat jet searches
        if (apid == MCUtils::PID::Z0 || apid == MCUtils::PID::WPLUS || apid == MCUtils::PID::HIGGS)
        {
          bool isGoodBoson = true;
          std::vector<int> childIDs;
          get_unified_child_ids(p, pevt, childIDs);
          int abschildID;
          for (int childID : childIDs)
          {
            // Veto bosons not decaying into quarks or gluons
            abschildID = abs(childID);
            if (abschildID == MCUtils::PID::Z0 || abschildID == MCUtils::PID::WPLUS ||
                abschildID == MCUtils::PID::HIGGS || abschildID == MCUtils::PID::ELECTRON ||
                abschildID == MCUtils::PID::MUON || abschildID == MCUtils::PID::TAU ||
                abschildID == MCUtils::PID::NU_E || abschildID == MCUtils::PID::NU_MU ||
                abschildID == MCUtils::PID::NU_TAU || abschildID == MCUtils::PID::GAMMA)
            {
              isGoodBoson = false;
            }
          }
          // Check for reasonable on-shellness (only low masses discarded on purpose)
          if(apid == MCUtils::PID::Z0 && (mz_central_observed-p4.m() > 20.))
          {
            isGoodBoson = false;
          }
          if(apid == MCUtils::PID::WPLUS && (mw_central_observed-p4.m() > 20.))
          {
            isGoodBoson = false;
          }
          // Check that the vector bosons do not come from a Higgs boson or top quark
          // (in which case the tagging efficiency would be different)
          int absmotherID = abs(get_unified_mother1_pid(p, pevt));
          if(absmotherID == MCUtils::PID::HIGGS || absmotherID == MCUtils::PID::TQUARK)
          {
            isGoodBoson = false;
          }
          // Store candidate
          if (isGoodBoson)
          {
            if(apid == MCUtils::PID::Z0) ZCandidates.push_back(HEPUtils::Particle(p4,pid));
            if(apid == MCUtils::PID::WPLUS) WCandidates.push_back(HEPUtils::Particle(p4,pid));
            if(apid == MCUtils::PID::HIGGS) hCandidates.push_back(HEPUtils::Particle(p4,pid));
          }
        }

        //We only want final state particles:
        if (!get_unified_isFinal(p)) continue;

        //Check there's no partons.
        if (pid == 21 || abs(pid) <= 6)
        {
          std::ostringstream sid;
          bool gotmother = false;
          //HepMC seems to have no equivalent of the .mother1, .mother2 call, so the HepMC3 mother function will just
          //return 0, and gotmother will always be false - which means it won't try to print non-existent event info.
          if (get_unified_mother1(p) != 0 ){gotmother = true; sid << get_unified_mother1_pid(p, pevt);}
          if (get_unified_mother2(p) != 0 ){gotmother = true; sid << get_unified_mother2_pid(p, pevt);}
          if (gotmother) sid << " -> ";
          sid << pid;
          ColliderBit_error().forced_throw(LOCAL_INFO, "Found final-state parton " + sid.str() + " in particle-level event converter: "
              "reconfigure your generator to include hadronization, or Gambit to use the partonic event converter.");
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
        if (visible && apid != MCUtils::PID::MUON)
        {
          jetparticles.push_back(get_unified_pseudojet(p));
        }
      }

      /// Jet finding
      for (jet_collection_settings jetcollection : all_jet_collection_settings)
      {
        FJNS::JetAlgorithm jet_algorithm = FJalgorithm_map(jetcollection.algorithm);
        FJNS::Strategy jet_strategy = FJstrategy_map(jetcollection.strategy);
        FJNS::RecombinationScheme jet_recomscheme = FJRecomScheme_map(jetcollection.recombination_scheme);
        const FJNS::JetDefinition jet_def(jet_algorithm, jetcollection.R, jet_strategy, jet_recomscheme);

        /// Create and run a new cluster sequence for the given jet collection. 
        /// The HEPUtils::Event instance ('result') takes ownership of the 
        /// cluster sequence and a shared_ptr is returned here.
        std::shared_ptr<const FJNS::ClusterSequence> CSeqBasePtr = result.emplace_clusterseq(jetparticles, jet_def, jetcollection.key);
        /// Get the resulting pseudojets
        std::vector<FJNS::PseudoJet> pjets = sorted_by_pt(CSeqBasePtr->inclusive_jets(jet_pt_min));

        /// Do jet b-tagging, etc. and add to the Event
        /// @todo Use ghost tagging?
        /// @note We need to _remove_ this b-tag in the detector sim if outside the tracker acceptance!
        for (auto& pj : pjets)
        {
          HEPUtils::P4 jetMom = HEPUtils::mk_p4(pj);
          /// @todo Replace with HEPUtils::any(bhadrons, [&](const auto& pb){ pj.delta_R(pb) < 0.4 })
          bool isB = false;
          for (HEPUtils::Particle& pb : bpartons)
          {
            if (jetMom.deltaR_eta(pb.mom()) < 0.4) ///< @todo Hard-coded radius!!!
            {
              isB = true;
              break;
            }
          }

          bool isC = false;
          for (HEPUtils::Particle& pc : cpartons)
          {
            if (jetMom.deltaR_eta(pc.mom()) < 0.4) ///< @todo Hard-coded radius!!!
            {
              isC = true;
              break;
            }
          }

          bool isTau = false;
          int signedTauPID = MCUtils::PID::TAU;
          for (HEPUtils::Particle& ptau : tauCandidates)
          {
            if (jetMom.deltaR_eta(ptau.mom()) < 0.5) ///< @todo Hard-coded radius!!!
            {
              isTau = true;
              signedTauPID = ptau.pid();
              break;
            }
          }

          bool isW = false;
          for (HEPUtils::Particle& pW : WCandidates)
          {
            if (jetMom.deltaR_eta(pW.mom()) < 1.0) ///< @todo Hard-coded radius from ATLAS-CONF-2021-022, make selectable?
            {
              isW = true;
              break;
            }
          }

          bool isZ = false;
          for (HEPUtils::Particle& pZ : ZCandidates)
          {
            if (jetMom.deltaR_eta(pZ.mom()) < 1.0) ///< @todo Hard-coded radius from ATLAS-CONF-2021-022, make selectable?
            {
              isZ = true;
              break;
            }
          }


          bool ish = false;
          for (HEPUtils::Particle& ph : hCandidates)
          {
            if (jetMom.deltaR_eta(ph.mom()) < 1.0) ///< @todo Hard-coded radius from ATLAS-CONF-2021-022, make selectable?
            {
              ish = true;
              break;
            }
          }

          // Add to the event (use jet momentum for tau)
          // Only do this for a single jet collection
          if (isTau && (jetcollection.key == jetcollection_taus))
          {
            HEPUtils::Particle* gp = new HEPUtils::Particle(HEPUtils::mk_p4(pj), signedTauPID);
            gp->set_prompt();
            result.add_particle(gp);
          }

          // Add jet to collection including tags and PseudoJet
          HEPUtils::Jet::TagCounts tags{ {5,int(isB)}, {4,int(isC)}, {23,int(isZ)}, {24,int(isW)}, {25,int(ish)} };
          result.add_jet(new HEPUtils::Jet(pj, tags), jetcollection.key);
        }
      }

      /// Calculate missing momentum
      //
      // From balance of all visible momenta (requires isolation)
      // const std::vector<Particle*> visibles = result.visible_particles();
      // HEPUtils::P4 pvis;
      // for (size_t i = 0; i < visibles.size(); ++i)
      // {
      //   pvis += visibles[i]->mom();
      // }
      // for (size_t i = 0; i < result.jets.size(); ++i)
      // {
      //   pvis += result.jets[i]->mom();
      // }
      // set_missingmom(-pvis);
      //
      // From sum of invisibles, including those out of range
      for (size_t i = 0; i < result.invisible_particles().size(); ++i)
      {
        pout += result.invisible_particles()[i]->mom();
      }
      result.set_missingmom(pout);

      #ifdef COLLIDERBIT_DEBUG
        // Print event summary
        cout << "For jet Collection:  " << jetcollection.key << endl;
        cout << "  MET  = " << result.met() << " GeV" << endl;
        cout << "  #e   = " << result.electrons().size() << endl;
        cout << "  #mu  = " << result.muons().size() << endl;
        cout << "  #tau = " << result.taus().size() << endl;
        cout << "  #jet = " << result.jets(jetcollection.key).size() << endl;
        cout << "  #pho  = " << result.photons().size() << endl;
        cout << endl;
      #endif
    }


    /// Convert a partonic (no hadrons) EventT into an unsmeared HEPUtils::Event
    template<typename EventT>
    void convertPartonEvent(const EventT& pevt, HEPUtils::Event& result, std::vector<jet_collection_settings> all_jet_collection_settings, str jetcollection_taus, double jet_pt_min)
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
        if (std::abs(p.eta()) > 5.0)
        {
          pout += mk_p4(p.p());
          continue;
        }

        // Find electrons/muons/taus/photons to be treated as prompt (+ invisibles)
        /// @todo *Some* photons should be included in jets!!! Ignore for now since no FSR
        /// @todo Lepton dressing
        const bool prompt = isFinalPhoton(i, pevt) || (isFinalLepton(i, pevt)); // && std::abs(p.id()) != MCUtils::PID::TAU);
        const bool visible = MCUtils::PID::isStrongInteracting(p.id()) || MCUtils::PID::isEMInteracting(p.id());
        if (prompt || !visible)
        {
          HEPUtils::Particle* gp = new HEPUtils::Particle(mk_p4(p.p()), p.id());
          gp->set_prompt();
          result.add_particle(gp);
        }

        // Everything other than invisibles and muons, including taus & partons are jet constituents
        /// @todo Only include hadronic tau fraction?
        // if (visible && (isFinalParton(i, pevt) || isFinalTau(i, pevt))) {
        if (visible && p.idAbs() != MCUtils::PID::MUON)
        {
          FJNS::PseudoJet pj = mk_pseudojet(p.p());
          //pj.set_user_index(std::abs(p.id()));
          jetparticles.push_back(pj);
        }

      }

      /// Jet finding
      for (jet_collection_settings jetcollection : all_jet_collection_settings)
      {
        FJNS::JetAlgorithm jet_algorithm = FJalgorithm_map(jetcollection.algorithm);
        FJNS::Strategy jet_strategy = FJstrategy_map(jetcollection.strategy);
        FJNS::RecombinationScheme jet_recomscheme = FJRecomScheme_map(jetcollection.recombination_scheme);
        const FJNS::JetDefinition jet_def(jet_algorithm, jetcollection.R, jet_strategy, jet_recomscheme);
        std::shared_ptr<const FJNS::ClusterSequence> CSeqBasePtr = result.emplace_clusterseq(jetparticles, jet_def, jetcollection.key);
        std::vector<FJNS::PseudoJet> pjets = sorted_by_pt(CSeqBasePtr->inclusive_jets(jet_pt_min));

        // Add to the event, with b-tagging info"
        for (const FJNS::PseudoJet& pj : pjets)
        {
          // Do jet b-tagging, etc. by looking for b quark constituents (i.e. user index = |parton ID| = 5)
          /// @note This b-tag is removed in the detector sim if outside the tracker acceptance!
          const bool isB = HEPUtils::any(pj.constituents(),
                   [](const FJNS::PseudoJet& c){ return c.user_index() == MCUtils::PID::BQUARK; });
          const bool isC = HEPUtils::any(pj.constituents(),
                   [](const FJNS::PseudoJet& c){ return c.user_index() == MCUtils::PID::CQUARK; });
          result.add_jet(new HEPUtils::Jet(HEPUtils::mk_p4(pj), isB, isC), jetcollection.key); // This does not currently deal with boson tagging

          bool isTau=false;
          int signedTauPID = MCUtils::PID::TAU;
          for (auto& ptau : tauCandidates)
          {
            HEPUtils::P4 jetMom = HEPUtils::mk_p4(pj);
            if (jetMom.deltaR_eta(ptau.mom()) < 0.5)
            {
              isTau=true;
              signedTauPID = ptau.pid();
              break;
            }
          }
          // Add to the event (use jet momentum for tau)
          // Only do this for a single jet collection
          if (isTau && (jetcollection.key == jetcollection_taus))
          {
            HEPUtils::Particle* gp = new HEPUtils::Particle(HEPUtils::mk_p4(pj), signedTauPID);
            gp->set_prompt();
            result.add_particle(gp);
          }
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
      for (const HEPUtils::Particle* p : result.invisible_particles()) pout += p->mom();
      result.set_missingmom(pout);
    }

  }

}
