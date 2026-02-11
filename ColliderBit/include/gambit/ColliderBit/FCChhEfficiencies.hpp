//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///
///  \file
///  Functions that do super fast FCC-hh detector
///  simulation based on four-vector smearing.
///  Based on ATLASEfficiencies.hpp; functions from
///  -https://cds.cern.ch/record/2717698/files/CERN-FCC-PHYS-2020-0003.pdf
///  -https://github.com/delphes/delphes/blob/master/cards/FCC
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///  \author Abram Krislock
///  \author Anders Kvellestad
///  \author Matthias Danninger
///  \author Rose Kudzman-Blais
///  \author Pat Scott
///  \author Tomas Gonzalo
///  \author Tore Klungland
///
///  *********************************************


#pragma once

#include <cfloat>

#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/Utils/threadsafe_rng.hpp"

#include "HEPUtils/MathUtils.h"
#include "HEPUtils/BinnedFn.h"
#include "HEPUtils/Event.h"

#include "gambit/ColliderBit/FCChhResolution.hpp"

namespace Gambit
{

  namespace ColliderBit
  {


    /// FCC-hh-specific efficiency and smearing functions for super fast detector simulation
    namespace FCChh
    {



        /// Randomly filter the supplied particle list by parameterised electron efficiency
        /// @note Should be applied after the electron energy smearing
        inline void applyElectronEff(std::vector<const HEPUtils::Particle*>& electrons) {
          static HEPUtils::BinnedFn2D<double> _elEff2d({{0,2.5,4.0,6.0,DBL_MAX}}, //< |eta|
                                                       {{0,4.,DBL_MAX}}, //< pT
                                                       {{0., 0.95,
                                                         0., 0.90,
                                                         0., 0.85,
                                                         0., 0.}});
          filtereff_etapt(electrons, _elEff2d);
        }



        /// Randomly filter the supplied particle list by parameterised muon efficiency
        inline void applyMuonEff(std::vector<const HEPUtils::Particle*>& muons) {
          static HEPUtils::BinnedFn2D<double> _muEff2d({{0,2.5,4.0,6.0,DBL_MAX}}, //< |eta|
                                                       {{0,4.0,DBL_MAX}}, //< pT
                                                       {{0., 0.99,
                                                         0., 0.99,
                                                         0., 0.99,
                                                         0., 0.}});
          filtereff_etapt(muons, _muEff2d);
        }


        /// Randomly filter the supplied particle list by parameterised photon efficiency
        /// NOTE: ID efficiency only listed from pT>1 GeV; assuming 0 below this
        inline void applyPhotonEfficiency(std::vector<const HEPUtils::Particle*>& photons) {
          static HEPUtils::BinnedFn2D<double> _phEff2d({{0,2.5,4.0,6.0,DBL_MAX}}, //< |eta|
                                                       {{0.,1.0,5.0,10.0,DBL_MAX}}, //< pT
                                                       {{0., 0.70, 0.85, 0.95,
                                                         0., 0.60, 0.80, 0.90,
                                                         0., 0.50, 0.70, 0.80,
                                                         0., 0.50, 0.70, 0.80}});
          filtereff_etapt(photons, _phEff2d);
        }


        /// Randomly smear the supplied electrons' momenta by parameterised resolutions
        inline void smearElectronEnergy(std::vector<HEPUtils::Particle*>& electrons) {
          // Function that mimics the DELPHES electron energy resolution
          // We need to smear E, then recalculate pT, then reset 4 vector

          // Now loop over the electrons and smear the 4-vectors
          for (HEPUtils::Particle* e : electrons) {
            if (e->abseta() >= 6) continue;
            // Look up / calculate resolution
            const double resolution = electronMomentumResolution(e->eta(),e->E());
            // Smear by a Gaussian centered on the current energy, with width given by the resolution
            std::normal_distribution<> d(e->E(), resolution*e->E());
            double smeared_E = d(Random::rng());
            if (smeared_E < e->mass()) smeared_E = 1.01*e->mass();
            // double smeared_pt = smeared_E/cosh(e->eta()); ///< @todo Should be cosh(|eta|)?
            e->set_mom(HEPUtils::P4::mkEtaPhiME(e->eta(), e->phi(), e->mass(), smeared_E));
          }
        }


        /// Randomly smear the supplied muons' momenta by parameterised resolutions
        inline void smearMuonMomentum(std::vector<HEPUtils::Particle*>& muons) {
          // Function that mimics the DELPHES muon momentum resolution
          // We need to smear pT, then recalculate E, then reset 4 vector

          // Now loop over the muons and smear the 4-vectors
          for (HEPUtils::Particle* mu : muons) {
            if (mu->abseta() >= 6) continue;
            // Look up / calculate resolution
            const double resolution = muonMomentumResolution(mu->eta(),mu->E());
            // Smear by a Gaussian centered on the current energy, with width given by the resolution
            std::normal_distribution<> d(mu->pT(), resolution*mu->pT());
            double smeared_pt = d(Random::rng());
            if (smeared_pt < 0) smeared_pt = 0;
            // const double smeared_E = smeared_pt*cosh(mu->eta()); ///< @todo Should be cosh(|eta|)?
            // std::cout << "Muon pt " << mu_pt << " smeared " << smeared_pt << endl;
            mu->set_mom(HEPUtils::P4::mkEtaPhiMPt(mu->eta(), mu->phi(), mu->mass(), smeared_pt));
          }
        }


        /// Randomly smear the supplied jets' momenta by parameterised resolutions
        inline void smearJets(std::vector<HEPUtils::Jet*>& jets) {
          // Function that mimics the DELPHES jet energy resolution
          // We need to smear pT, then recalculate E, then reset 4 vector

          // Now loop over the jets and smear the 4-vectors
          for (HEPUtils::Jet* jet : jets) {
            if (jet->abseta() >= 6) continue;
            // Look up / calculate resolution
            const double resolution = jetMomentumResolution(jet->eta(),jet->E());
            // Smear by a Gaussian centered on the current energy, with width given by the resolution
            std::normal_distribution<> d(jet->pT(), resolution*jet->pT());
            double smeared_pt = d(Random::rng());
            if (smeared_pt < 0) smeared_pt = 0;
            // const double smeared_E = smeared_pt*cosh(mu->eta()); ///< @todo Should be cosh(|eta|)?
            // std::cout << "Muon pt " << mu_pt << " smeared " << smeared_pt << endl;
            jet->set_mom(HEPUtils::P4::mkEtaPhiMPt(jet->eta(), jet->phi(), jet->mass(), smeared_pt));
          }
        }


        /// Randomly smear the MET vector by parameterised resolutions
        inline void smearMET(HEPUtils::P4& pmiss, double set) {
          // Smearing function from ATLAS Run 1 performance paper, converted from Rivet
          // cf. https://arxiv.org/pdf/1108.5602v2.pdf, Figs 14 and 15

          /// TODO: Put something here (?)
        }


        /// Randomly smear the supplied taus' momenta by parameterised resolutions
        inline void smearTaus(std::vector<HEPUtils::Particle*>& taus) {
          // Note: Currently just copied directly from ATLAS
          // We need to smear pT, then recalculate E, then reset the 4-vector.
          // Same as for jets, but on a vector of particles. (?)
          // Const resolution for now
          const double resolution = 0.03;

          // Now loop over the jets and smear the 4-vectors
          std::normal_distribution<> d(1., resolution);
          for (HEPUtils::Particle* p : taus) {
            // Smear by a Gaussian centered on 1 with width given by the (fractional) resolution
            double smear_factor = d(Random::rng());
            /// @todo Is this the best way to smear? Should we preserve the mean jet energy, or pT, or direction?
            p->set_mom(HEPUtils::P4::mkXYZM(p->mom().px()*smear_factor, p->mom().py()*smear_factor, p->mom().pz()*smear_factor, p->mass()));
          }
        }

        /// Efficiency function for Loose ID electrons
        /// @note Numbers digitised from Fig 3 of 13 TeV note (ATL-PHYS-PUB-2015-041)
        /// @todo What about faking by jets or non-electrons?
        inline void applyLooseIDElectronSelectionR2(std::vector<const HEPUtils::Particle*>& electrons) {
          /// TODO: Put something here (?)
        }

        /// Alias to allow non-const particle vectors
        inline void applyLooseIDElectronSelectionR2(std::vector<HEPUtils::Particle*>& electrons) {
          applyLooseIDElectronSelectionR2(reinterpret_cast<std::vector<const HEPUtils::Particle*>&>(electrons));
        }

        /// Efficiency function for Loose ID electrons
        /// @note Numbers digitised from Fig 3 of 13 TeV note (ATL-PHYS-PUB-2015-041)
        inline void applyMediumIDElectronSelectionR2(std::vector<const HEPUtils::Particle*>& electrons) {
          /// TODO: Put something here (?)
        }

        /// Alias to allow non-const particle vectors
        inline void applyMediumIDElectronSelectionR2(std::vector<HEPUtils::Particle*>& electrons) {
          applyMediumIDElectronSelectionR2(reinterpret_cast<std::vector<const HEPUtils::Particle*>&>(electrons));
        }

        /// Efficiency function for Medium ID electrons
        /// @note Numbers digitised from 8 TeV note (ATLAS-CONF-2014-032)
        inline void applyMediumIDElectronSelection(std::vector<const HEPUtils::Particle*>& electrons) {
          /// TODO: Put something here (?)
        }


        /// Alias to allow non-const particle vectors
        inline void applyMediumIDElectronSelection(std::vector<HEPUtils::Particle*>& electrons) {
          applyMediumIDElectronSelection(reinterpret_cast<std::vector<const HEPUtils::Particle*>&>(electrons));
        }


        /// Efficiency function for Tight ID electrons
        /// @note Numbers digitised from 8 TeV note (ATLAS-CONF-2014-032)
        inline void applyTightIDElectronSelection(std::vector<const HEPUtils::Particle*>& electrons) {
          /// TODO: Put something here (?)
        }


        /// Alias to allow non-const particle vectors
        inline void applyTightIDElectronSelection(std::vector<HEPUtils::Particle*>& electrons) {
          /// TODO: Put something here (?)
        }


        /// Electron 2019 ID efficiency functions from https://arxiv.org/pdf/1902.04655.pdf
        /// @note These efficiencies are 1D efficiencies so only pT is used
        inline void applyElectronIDEfficiency2019(std::vector<const HEPUtils::Particle*>& electrons, str operating_point)
        {
          /// TODO: Put something here (?)

        }

        /// Electron 2019 Isolation efficiency functions from https://arxiv.org/pdf/1902.04655.pdf
        /// @note These efficiencies are 1D efficiencies so only pT is used
        inline void applyElectronIsolationEfficiency2019(std::vector<const HEPUtils::Particle*>& electrons, str operating_point)
        {
          /// TODO: Put something here (?)
        }
 

        /// Electron 2020 reconstruction efficiency functions in 1908.00005 using 81 fb^-1 of Run 2 data
        /// @note These efficiencies are 1D efficiencies so only dependence on p_T is used
        inline void applyElectronReconstructionEfficiency2020(std::vector<const HEPUtils::Particle*>& electrons, str operating_point){
          /// TODO: Put something here (?)
        }


        
        /// Electron 2020 ID efficiency functions in 1908.00005 using 81 fb^-1 of Run 2 data
        /// @note These efficiencies are 1D efficiencies so only dependence on p_T is used
        inline void applyElectronIDEfficiency2020(std::vector<const HEPUtils::Particle*>& electrons, str operating_point){
          /// TODO: Put something here (?)
        }


        /// Electron 2020 isolation efficiency functions in 1908.00005 using 81 fb^-1 of Run 2 data
        /// @note These efficiencies are 1D efficiencies so only dependence on p_T is used
        inline void applyElectronIsolationEfficiency2020(std::vector<const HEPUtils::Particle*>& electrons, str operating_point){
          /// TODO: Put something here (?)
        }


        /// Muon 2020 identification efficiency functions from full Run2 dataset released in 2012.00578
        /// @note These efficiencies are 1D efficiencies so only dependence on p_T is used
        inline void applyMuonIDEfficiency2020(std::vector<const HEPUtils::Particle*>& muons, str operating_point){
          /// TODO: Put something here (?)
        }

        /// Muon 2020 isolation efficiency functions from full Run2 dataset released in 2012.00578
        /// @note These efficiencies are 1D efficiencies so only dependence on p_T is used
        inline void applyMuonIsolationEfficiency2020(std::vector<const HEPUtils::Particle*>& muons, str operating_point){
          /// TODO: Put something here (?)
        }

        ///@}

      }
   }
}
