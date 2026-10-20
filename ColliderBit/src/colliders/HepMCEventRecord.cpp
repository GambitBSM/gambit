//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Filling of a generator-neutral event record from a HepMC3 event.
///  See colliders/HepMCEventRecord.hpp.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author The GAMBIT Collaboration
///  \date 2026 Oct
///
///  *********************************************

#include "gambit/ColliderBit/colliders/HepMCEventRecord.hpp"

#ifndef EXCLUDE_HEPMC

#include <cstdlib>
#include <unordered_map>

#include "HepMC3/FourVector.h"
#include "HepMC3/GenParticle.h"
#include "MCUtils/PIDUtils.h"

namespace Gambit
{
  namespace ColliderBit
  {

    void fillEventRecord(const HepMC3::GenEvent& event, EventRecord& record)
    {
      const std::vector<HepMC3::ConstGenParticlePtr>& particles = event.particles();

      record.particles.assign(particles.size() + 1, EventRecord::Particle());

      // Map each HepMC particle to its index in the record
      std::unordered_map<const HepMC3::GenParticle*, int> index;
      index.reserve(particles.size());
      for (size_t i = 0; i < particles.size(); ++i) index[particles[i].get()] = static_cast<int>(i) + 1;

      for (size_t i = 0; i < particles.size(); ++i)
      {
        const HepMC3::ConstGenParticlePtr& gp = particles[i];
        EventRecord::Particle& r = record.particles[i + 1];
        const int pid = gp->pid();
        r.id = pid;
        r.is_final = (gp->status() == 1);
        // MCUtils' isParton only covers quarks and gluons, whereas Pythia's definition includes diquarks
        r.is_parton = MCUtils::PID::isParton(std::abs(pid)) || MCUtils::PID::isDiquark(std::abs(pid));
        r.is_hadron = MCUtils::PID::isHadron(pid);
        const HepMC3::FourVector& mom = gp->momentum();
        r.px = mom.px();
        r.py = mom.py();
        r.pz = mom.pz();
        r.e = mom.e();
        // Using generated mass rather than the four-vector mass, as this may be incorrect for zero mass particles
        r.m = gp->generated_mass();
        // HepMC has no equivalent of Pythia's two mother indices
        r.mother1 = 0;
        r.mother2 = 0;
        for (const HepMC3::ConstGenParticlePtr& parent : gp->parents()) r.mothers.push_back(index.at(parent.get()));
        for (const HepMC3::ConstGenParticlePtr& child : gp->children()) r.daughters.push_back(index.at(child.get()));
      }
    }

  }
}

#endif // EXCLUDE_HEPMC
