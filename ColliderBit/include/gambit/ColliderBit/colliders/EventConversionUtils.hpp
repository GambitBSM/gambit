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

#include "HEPUtils/Event.h"
#include "HEPUtils/Particle.h"
#include "HEPUtils/FastJet.h"
#include "HEPUtils/FastJet.h"
#include "MCUtils/PIDUtils.h"

#ifndef EXCLUDE_HEPMC
  #include "HepMC3/GenEvent.h"
  #include "HepMC3/GenParticle.h"
  #include "MCUtils/HepMCVectors.h"
#endif


namespace Gambit
{

  namespace ColliderBit
  {


    //Overloaded functions so that the convertParticleEvent function is fully general. For every function there is a version for
    //HEPMC::GenParticlePtr and a templated version for other particle types (such as Pythia Particles).

    namespace EventConversion
    {

      template<typename ParticleP>
      int get_unified_pid(ParticleP p) { return p.id(); }

      template<typename ParticleP>
      bool get_unified_isFinal(ParticleP p) { return (p.isFinal()); }

      template <typename ParticleP>
      inline double get_unified_eta(ParticleP p) { return p.eta(); }

      template <typename ParticleP>
      inline HEPUtils::P4 get_unified_momentum(ParticleP p) { return HEPUtils::P4::mkXYZE(p.px(), p.py(), p.pz(), p.e()); }

      template <typename ParticleP>
      inline FJNS::PseudoJet get_unified_pseudojet(ParticleP p) { return FJNS::PseudoJet(p.p().px(), p.p().py(), p.p().pz(), p.p().e()); }

      template <typename ParticleP, typename EventT>
      inline bool get_unified_fromHadron(ParticleP&, const EventT &pevt, int i)  { return fromHadron(i, pevt); }

      template <typename ParticleP>
      inline int get_unified_mother1(ParticleP &p) { return p.mother1(); }
      template <typename ParticleP>
      inline int get_unified_mother2(ParticleP &p) { return p.mother2(); }

      template <typename ParticleP, typename EventT>
      inline int get_unified_mother1_pid(ParticleP &p, EventT &pevt) { return pevt[p.mother1()].id(); }
      template <typename ParticleP, typename EventT>
      inline int get_unified_mother2_pid(ParticleP &p, EventT &pevt) { return pevt[p.mother2()].id(); }

      template<typename ParticleP, typename EventT>
      void get_unified_child_ids(ParticleP &p, EventT &pevt, std::vector<int> &unified_child_id_results)
      {
        //Note! The unified_child_id_results MUST BE EMPTY as we don't clear them in the function.
        std::vector<int> daughter_list = p.daughterList();
        for (int daughter : daughter_list)
        {
          unified_child_id_results.push_back(pevt[daughter].id());
        }
      }


      #ifndef EXCLUDE_HEPMC

        ///The MCUtils isParton function only checks for quarks/gluons, whereas the Pythia function used in Gambit
        ///includes diquarks too, so we manually define this function using the isParton and isDiquark options in MCUtils.
        inline bool HEPMC3_isParton(int pid) { return (MCUtils::PID::isParton(pid) || MCUtils::PID::isDiquark(pid)); }

        inline int get_unified_pid(const HepMC3::GenParticlePtr &gp) { return gp->pid(); }

        inline bool get_unified_isFinal(const HepMC3::GenParticlePtr &gp) { return (gp->status() == 1); }

        inline HEPUtils::P4 get_unified_momentum(const HepMC3::GenParticlePtr &gp)
        {
          const HepMC3::FourVector& hp4 = gp->momentum();
          return HEPUtils::P4::mkXYZE(hp4.px(), hp4.py(), hp4.pz(), hp4.e());
        }

        inline FJNS::PseudoJet get_unified_pseudojet(const HepMC3::GenParticlePtr &gp)
        {
          const HepMC3::FourVector& hp4 = gp->momentum();
          return FJNS::PseudoJet(hp4.px(), hp4.py(), hp4.pz(), hp4.e());
        }

        inline double get_unified_eta(const HepMC3::GenParticlePtr &gp) { return MCUtils::eta(gp->momentum()); }

        inline bool get_unified_fromHadron(const HepMC3::GenParticlePtr &gp, const std::vector<HepMC3::GenParticlePtr> &pevt, int i)
        {
          // This function mimics exactly what the Py8Utils.cpp function does, but for HepMC3 events.
          // This seems highly unlikely to change - apparently this is just the standard way it's done.
          // Note that the meaningless int argument is to make sure that the same function call works both for HepMC3
          // and Pythia.
          if (MCUtils::PID::isHadron(gp->pid())) return true;
          if (HEPMC3_isParton(abs(gp->pid()))) return false; // stop the walking at the end of the hadron level
          auto parent_vector = (gp->parents());
          if (parent_vector.size() == 0) return false;
          for (const HepMC3::GenParticlePtr& parent : parent_vector)
          {
            if (get_unified_fromHadron(parent, pevt, i)) return true;
          }
          return false;
        }

        inline int get_unified_mother1(const HepMC3::GenParticlePtr&) { return 0; }
        inline int get_unified_mother2(const HepMC3::GenParticlePtr&) { return 0; }

        ///Shouldn't ever need to call a HepMC3 version of this, but for safety here's one that just returns 0.
        inline int get_unified_mother1_pid(const HepMC3::GenParticlePtr&, const std::vector<HepMC3::GenParticlePtr>&) { return 0; }
        ///Shouldn't ever need to call a HepMC3 version of this, but for safety here's one that just returns 0.
        inline int get_unified_mother2_pid(const HepMC3::GenParticlePtr&, const std::vector<HepMC3::GenParticlePtr>&) { return 0; }

        inline void get_unified_child_ids(const HepMC3::GenParticlePtr &gp, const std::vector<HepMC3::GenParticlePtr>&, std::vector<int> &unified_child_id_results)
        {
          //Note! The unified_child_id_results MUST BE EMPTY as we don't clear them in the function.
          auto child_vector = gp->children();
          for (const HepMC3::GenParticlePtr& child: child_vector)
          {
            unified_child_id_results.push_back(child->pid());
          }
        }

      #endif

    }

  }

}




