//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Utils for ColliderBit analyses.
///
///  *********************************************
///
///  \author Daniel Steiner
///  \date 2018 Jul
///
///  *********************************************


#include "gambit/ColliderBit/Utils.hpp"
#include "HEPUtils/Event.h"

namespace Gambit
{
  namespace ColliderBit
  {

    class AnalysisUtil
    {

      public:

        static bool sortParticlesByPt(const HEPUtils::Particle *particle1, const HEPUtils::Particle *particle2)
        {
          return (particle1->pT() > particle2->pT());
        }

        static bool sortJetsByPt(const HEPUtils::Jet* jet1, const HEPUtils::Jet* jet2)
        {
          return (jet1->pT() > jet2->pT());
        }

        static std::vector<const HEPUtils::Jet*> filterPtEta(std::vector<const HEPUtils::Jet*> jets, double pT, double absEta)
        {
          std::vector<const HEPUtils::Jet*> outJets;
          for (const HEPUtils::Jet* jet : jets)
          {
            if (jet->pT() > pT && jet->abseta() < absEta)
            {
              outJets.push_back(jet);
            }
          }
          return outJets;
        }

        static std::vector<const HEPUtils::Particle*> filterPtEta(std::vector<const HEPUtils::Particle*> particles, double pT, double absEta)
        {
          std::vector<const HEPUtils::Particle*> outParticles;
          for (const HEPUtils::Particle* particle : particles)
          {
            if (particle->pT() > pT && particle->abseta() < absEta)
            {
              outParticles.push_back(particle);
            }
          }
          return outParticles;
        }

        static std::vector<const HEPUtils::Jet*> jetLeptonOverlapRemoval(std::vector<const HEPUtils::Jet*> jets, std::vector<const HEPUtils::Particle*> leptons, double dR)
        {
          std::vector<const HEPUtils::Jet*> outJets;
          for (const HEPUtils::Jet* jet : jets)
          {
            bool overlap = false;
            for (const HEPUtils::Particle* lepton : leptons)
            {
              double dRJetElectron = lepton->mom().deltaR_eta(jet->mom());
              if (fabs(dRJetElectron) < dR)
              {
                overlap = true;
              }
            }
            if (overlap) continue;
            outJets.push_back(jet);
          }
          return outJets;
        }

        static std::vector<const HEPUtils::Particle*> leptonJetOverlapRemoval(std::vector<const HEPUtils::Particle*> leptons, std::vector<const HEPUtils::Jet*> jets, double dR)
        {
          std::vector<const HEPUtils::Particle*> outLeptons;
          for (const HEPUtils::Particle* lepton : leptons)
          {
            bool overlap = false;
            for (const HEPUtils::Jet* jet : jets)
            {
              double dRLeptonJet = lepton->mom().deltaR_eta(jet->mom());
              if (fabs(dRLeptonJet) < dR)
              {
                overlap = true;
              }
            }
            if (overlap) continue;
            outLeptons.push_back(lepton);
          }
          return outLeptons;
        }

        static bool isSingleParticleTriggered(std::vector<const HEPUtils::Particle*> particles, double pTrequirement)
        {
          for (const HEPUtils::Particle* particle : particles)
          {
            if (particle->pT() > pTrequirement)
            {
              return true;
            }
          }
          return false;
        }

        static bool isMultipleParticleTriggered(std::vector<const HEPUtils::Particle*> particles, std::vector<double> pTrequirements)
        {
          size_t numTriggers = 0;
          for (const HEPUtils::Particle* particle : particles)
          {
            for (double pTrequirement : pTrequirements)
            {
              if (particle->pT() > pTrequirement)
              {
                numTriggers++;
                break;
              }
            }
          }
          return numTriggers >= pTrequirements.size();
        }

        static std::vector<const HEPUtils::Particle*> getSortedLeptons(const std::vector<std::vector<const HEPUtils::Particle*>> allLeptons)
        {
          std::vector<const HEPUtils::Particle*> leptons;
          for (std::vector<const HEPUtils::Particle*> setOfLeptons : allLeptons)
          {
            leptons.insert(leptons.end(), setOfLeptons.begin(), setOfLeptons.end());
          }
          std::sort(leptons.begin(), leptons.end(), sortParticlesByPt);
          return leptons;
        }

        static double dot2D(HEPUtils::P4 mom1, HEPUtils::P4 mom2)
        {
          return mom1.px() * mom2.px() + mom1.py() * mom2.py();
        }

        static std::vector<const HEPUtils::Jet*> filterMaxEta(const std::vector<const HEPUtils::Jet*>& jets, double maxAbsEta)
        {
          std::vector<const HEPUtils::Jet*> outJets;
          for (const HEPUtils::Jet* jet : jets)
          {
            if (jet->abseta() < maxAbsEta)
            {
              outJets.push_back(jet);
            }
          }
          return outJets;
        }

        static bool muonFilter7TeV(const std::vector<const HEPUtils::Particle*>& muons)
        {
          double effProduct = 1.0;
          for (const HEPUtils::Particle* muon : muons)
          {
            if (muon->abseta() < 1.05)
            {
              effProduct *= (1 - 0.7);
            }
            else
            {
              effProduct *= (1 - 0.95);
            }
          }
          double efficiency = 1 - effProduct;
          return random_bool(efficiency);
        }

        static bool oppositeSign(const HEPUtils::Particle* a, const HEPUtils::Particle* b)
        {
          return a->pid() * b->pid() < 0;
        }

    };

  }
}
