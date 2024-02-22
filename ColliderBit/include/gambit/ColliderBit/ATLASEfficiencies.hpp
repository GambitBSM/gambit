//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///
///  \file
///  Functions that do super fast ATLAS detector
///  simulation based on four-vector smearing.
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
///
///  *********************************************


#pragma once

#include <cfloat>

#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/Utils/threadsafe_rng.hpp"
#include "gambit/Utils/util_functions.hpp"

#include "HEPUtils/MathUtils.h"
#include "HEPUtils/BinnedFn.h"
#include "HEPUtils/Event.h"

namespace Gambit
{

  namespace ColliderBit
  {

    /// ATLAS-specific efficiency and smearing functions for super fast detector simulation
    namespace ATLAS
    {

      /// @name ATLAS detector smearing functions
      /// @{

        /// Randomly smear the supplied electrons' momenta by parameterised resolutions
        inline void smearElectronEnergy(std::vector<HEPUtils::Particle*>& electrons)
        {
          // Function that mimics the DELPHES electron energy resolution
          // We need to smear E, then recalculate pT, then reset 4 vector

          static HEPUtils::BinnedFn2D<double> coeffE2({{0, 2.5, 3., 5.}}, //< |eta|
                                                      {{0, 0.1, 25., DBL_MAX}}, //< pT
                                                      {{0.,          0.015*0.015, 0.005*0.005,
                                                        0.005*0.005, 0.005*0.005, 0.005*0.005,
                                                        0.107*0.107, 0.107*0.107, 0.107*0.107}});

          static HEPUtils::BinnedFn2D<double> coeffE({{0, 2.5, 3., 5.}}, //< |eta|
                                                     {{0, 0.1, 25., DBL_MAX}}, //< pT
                                                     {{0.,        0.,        0.05*0.05,
                                                       0.05*0.05, 0.05*0.05, 0.05*0.05,
                                                       2.08*2.08, 2.08*2.08, 2.08*2.08}});

          static HEPUtils::BinnedFn2D<double> coeffC({{0, 2.5, 3., 5.}}, //< |eta|
                                                     {{0, 0.1, 25., DBL_MAX}}, //< pT
                                                     {{0.,       0.,       0.25*0.25,
                                                       0.25*0.25,0.25*0.25,0.25*0.25,
                                                       0.,       0.,       0.}});

          // Now loop over the electrons and smear the 4-vectors
          for (HEPUtils::Particle* e : electrons)
          {
            if (e->abseta() > 5) continue;

            // Look up / calculate resolution
            const double c1 = coeffE2.get_at(e->abseta(), e->pT());
            const double c2 = coeffE.get_at(e->abseta(), e->pT());
            const double c3 = coeffC.get_at(e->abseta(), e->pT());
            const double resolution = sqrt(c1*HEPUtils::sqr(e->E()) + c2*e->E() + c3);

            // Smear by a Gaussian centered on the current energy, with width given by the resolution
            std::normal_distribution<> d(e->E(), resolution);
            double smeared_E = d(Random::rng());
            if (smeared_E < e->mass()) smeared_E = 1.01*e->mass();
            // double smeared_pt = smeared_E/cosh(e->eta()); ///< @todo Should be cosh(|eta|)?
            e->set_mom(HEPUtils::P4::mkEtaPhiME(e->eta(), e->phi(), e->mass(), smeared_E));
          }
        }


        /// Randomly smear the supplied muons' momenta by parameterised resolutions
        inline void smearMuonMomentum(std::vector<HEPUtils::Particle*>& muons)
        {
          // Function that mimics the DELPHES muon momentum resolution
          // We need to smear pT, then recalculate E, then reset 4 vector

          static HEPUtils::BinnedFn2D<double> _muEff({{0,1.5,2.5}},
                                                     {{0,0.1,1.,10.,200.,DBL_MAX}},
                                                     {{0.,0.03,0.02,0.03,0.05,
                                                       0.,0.04,0.03,0.04,0.05}});

          // Now loop over the muons and smear the 4-vectors
          for (HEPUtils::Particle* mu : muons)
          {
            if (mu->abseta() > 2.5) continue;

            // Look up resolution
            const double resolution = _muEff.get_at(mu->abseta(), mu->pT());

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
        inline void smearJets(std::vector<HEPUtils::Jet*>& jets)
        {
          // Function that mimics the DELPHES jet momentum resolution.
          // We need to smear pT, then recalculate E, then reset the 4-vector.
          // Const resolution for now
          //const double resolution = 0.03;

          // Matthias jet smearing implemented roughly from
          // https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2015-017/
          // Parameterisation can be still improved, but eta dependence is minimal
          const std::vector<double>  binedges_eta = {0, DBL_MAX};
          const std::vector<double>  binedges_pt = {0., 50., 70., 100., 150., 200., 1000., DBL_MAX};
          const std::vector<double> JetsJER = {0.145, 0.115, 0.095, 0.075, 0.07, 0.05, 0.04};
          static HEPUtils::BinnedFn2D<double> _resJets2D(binedges_eta, binedges_pt, JetsJER);

          // Now loop over the jets and smear the 4-vectors
          for (HEPUtils::Jet* jet : jets)
          {
            const double resolution = _resJets2D.get_at(jet->abseta(), jet->pT());
            std::normal_distribution<> d(1., resolution);
            // Smear by a Gaussian centered on 1 with width given by the (fractional) resolution
            double smear_factor = d(Random::rng());
            /// @todo Is this the best way to smear? Should we preserve the mean jet energy, or pT, or direction?
            jet->set_mom(HEPUtils::P4::mkXYZM(jet->mom().px()*smear_factor, jet->mom().py()*smear_factor, jet->mom().pz()*smear_factor, jet->mass()));
          }
        }


        /// Randomly smear the MET vector by parameterised resolutions
        inline void smearMET(HEPUtils::P4& pmiss, double set)
        {
          // Smearing function from ATLAS Run 1 performance paper, converted from Rivet
          // cf. https://arxiv.org/pdf/1108.5602v2.pdf, Figs 14 and 15

          // Linearity offset (Fig 14)
          if (pmiss.pT() < 25) pmiss *= 1.05;
          else if (pmiss.pT() < 40) pmiss *= (1.05 - (0.04/15)*(pmiss.pT() - 25)); //< linear decrease
          else pmiss *= 1.01;

          // Smear by a Gaussian with width given by the resolution(sumEt) ~ 0.45 sqrt(sumEt) GeV
          const double resolution = 0.45 * sqrt(set);
          std::normal_distribution<> d(pmiss.pT(), resolution);
          const double smearedmet = std::max(d(Random::rng()), 0.);

          pmiss *= smearedmet / pmiss.pT();
        }


        /// Randomly smear the supplied taus' momenta by parameterised resolutions
        inline void smearTaus(std::vector<HEPUtils::Particle*>& taus)
        {
          // We need to smear pT, then recalculate E, then reset the 4-vector.
          // Same as for jets, but on a vector of particles. (?)
          // Const resolution for now
          const double resolution = 0.03;

          // Now loop over the jets and smear the 4-vectors
          std::normal_distribution<> d(1., resolution);
          for (HEPUtils::Particle* p : taus)
          {
            // Smear by a Gaussian centered on 1 with width given by the (fractional) resolution
            double smear_factor = d(Random::rng());
            /// @todo Is this the best way to smear? Should we preserve the mean jet energy, or pT, or direction?
            p->set_mom(HEPUtils::P4::mkXYZM(p->mom().px()*smear_factor, p->mom().py()*smear_factor, p->mom().pz()*smear_factor, p->mass()));
          }
        }


      /// @}


      /// @name ATLAS detector efficiency functions
      /// @{

      /// ATLAS trigger efficiencies
      /// @{

        /// MET trigger efficiency, from CERN-EP-2016-241 (1611.09661)
        /// Binned in MET
        static const HEPUtils::BinnedFn1D<double> eff1DMET_CERN_EP_2015_241(
          {0, 30, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 170, 190, 210, 230, 250, 300, 400, DBL_MAX},
          {0.01, 0.01, 0.04, 0.07, 0.17, 0.30, 0.47, 0.63, 0.75, 0.85, 0.90, 0.95, 0.97, 0.98, 0.99, 0.98, 0.99, 1.00, 1.00}
        );

      /// @}

      /// ATLAS Electron, Muon, Tau and Photon efficiencies for the WPs of the identification techniques used in SUSY analyses

      /// Electron efficiencies
      /// @{

        /// Generic electron efficiency
        /// Randomly filter the supplied particle list by parameterised electron efficiency
        /// @note Should be applied after the electron energy smearing
        static const HEPUtils::BinnedFn2D<double> eff2DEl_Generic(
          {0,1.5,2.5,DBL_MAX}, //< |eta|
          {0,10.,DBL_MAX}, //< pT
          {
            0., 0.95,
            0., 0.85,
            0., 0.
          }
        );


        /// Efficiency function for Medium ID electrons
        /// @note Numbers digitised from 8 TeV note (ATLAS-CONF-2014-032)
        /// Digitized from Figs 11-12
        /// Combined in 2D efficiency
        static const HEPUtils::BinnedFn2D<double> eff2DEl_ATLAS_CONF_2014_032_Medium(
          {-2.5, -2.37, -2.01, -1.81, -1.52, -1.37, -1.15, -0.8, -0.6, -0.1, 0, 0.1, 0.6, 0.8, 1.15, 1.37, 1.52, 1.81, 2.01, 2.37, 2.5},   // Bin edges in eta
          {0, 7., 10., 15., 20., 25., 30., 35., 40., 45., 50., 60., 80., DBL_MAX},    // Bin edges in pT
          {
            // pT:   (0,7),  (7,10),  (10,15),  (15,20),  (20,25),  (25,30),  (30,35),  (35,40),  (40,45),  (45,50),  (50,60),  (60,80),  (80,inf)
                     0.000,   0.887,    0.778,    0.827,    0.828,    0.842,    0.848,    0.839,    0.837,    0.807,    0.783,    0.775,    0.949,  // eta: {-2.5, -2.37}
                     0.000,   0.887,    0.778,    0.827,    0.790,    0.826,    0.838,    0.857,    0.870,    0.892,    0.892,    0.894,    0.927,  // eta: {-2.37, -2.01}
                     0.000,   0.736,    0.768,    0.794,    0.795,    0.831,    0.851,    0.868,    0.882,    0.896,    0.900,    0.903,    0.935,  // eta: {-2.01, -1.81}
                     0.000,   0.736,    0.768,    0.794,    0.778,    0.817,    0.840,    0.867,    0.896,    0.912,    0.917,    0.922,    0.946,  // eta: {-1.81, -1.52}
                     0.000,   0.675,    0.569,    0.695,    0.725,    0.756,    0.771,    0.799,    0.840,    0.874,    0.879,    0.893,    0.908,  // eta: {-1.52, -1.37}
                     0.000,   0.775,    0.773,    0.811,    0.802,    0.842,    0.874,    0.897,    0.909,    0.925,    0.927,    0.927,    0.950,  // eta: {-1.37, -1.15}
                     0.000,   0.775,    0.773,    0.811,    0.799,    0.837,    0.867,    0.889,    0.898,    0.911,    0.919,    0.921,    0.953,  // eta: {-1.15, -0.8}
                     0.000,   0.832,    0.782,    0.820,    0.814,    0.847,    0.877,    0.895,    0.908,    0.918,    0.919,    0.921,    0.950,  // eta: {-0.8, -0.6}
                     0.000,   0.832,    0.782,    0.820,    0.812,    0.850,    0.879,    0.897,    0.908,    0.918,    0.923,    0.928,    0.941,  // eta: {-0.6, -0.1}
                     0.000,   0.823,    0.736,    0.786,    0.805,    0.836,    0.870,    0.886,    0.899,    0.907,    0.909,    0.904,    0.936,  // eta: {-0.1, 0}
                     0.000,   0.823,    0.736,    0.786,    0.781,    0.826,    0.857,    0.868,    0.888,    0.895,    0.897,    0.893,    0.931,  // eta: {0, 0.1}
                     0.000,   0.832,    0.782,    0.820,    0.821,    0.851,    0.878,    0.896,    0.908,    0.921,    0.923,    0.926,    0.945,  // eta: {0.1, 0.6}
                     0.000,   0.832,    0.782,    0.820,    0.817,    0.850,    0.882,    0.901,    0.912,    0.925,    0.928,    0.927,    0.954,  // eta: {0.6, 0.8}
                     0.000,   0.775,    0.773,    0.811,    0.795,    0.838,    0.867,    0.891,    0.902,    0.913,    0.919,    0.921,    0.949,  // eta: {0.8, 1.15}
                     0.000,   0.775,    0.773,    0.811,    0.790,    0.842,    0.872,    0.895,    0.908,    0.920,    0.923,    0.928,    0.951,  // eta: {1.15, 1.37}
                     0.000,   0.675,    0.569,    0.695,    0.770,    0.765,    0.776,    0.804,    0.842,    0.872,    0.884,    0.898,    0.914,  // eta: {1.37, 1.52}
                     0.000,   0.736,    0.768,    0.794,    0.777,    0.815,    0.838,    0.864,    0.892,    0.906,    0.913,    0.920,    0.945,  // eta: {1.52, 1.81}
                     0.000,   0.736,    0.768,    0.794,    0.796,    0.835,    0.851,    0.869,    0.884,    0.896,    0.902,    0.904,    0.924,  // eta: {1.81, 2.01}
                     0.000,   0.887,    0.778,    0.827,    0.791,    0.823,    0.839,    0.858,    0.870,    0.888,    0.884,    0.889,    0.924,  // eta: {2.01, 2.37}
                     0.000,   0.887,    0.778,    0.827,    0.823,    0.836,    0.831,    0.826,    0.817,    0.783,    0.759,    0.741,    0.944,  // eta: {2.37, 2.5}
          }
        );

        /// Efficiency function for Tight ID electrons
        /// @note Numbers digitised from 8 TeV note (ATLAS-CONF-2014-032)
        /// Digitized from Figs 11-12
        /// Combined in 2D efficiency
        static const HEPUtils::BinnedFn2D<double> eff2DEl_ATLAS_CONF_2014_032_Tight(
          {-2.5, -2.37, -2.01, -1.81, -1.52, -1.37, -1.15, -0.8, -0.6, -0.1, 0, 0.1, 0.6, 0.8, 1.15, 1.37, 1.52, 1.81, 2.01, 2.37, 2.5},   // Bin edges in eta
          {0, 7., 10., 15., 20., 25., 30., 35., 40., 45., 50., 60., 80., DBL_MAX},    // Bin edges in pT
          {
            // pT:   (0,7),  (7,10),  (10,15),  (15,20),  (20,25),  (25,30),  (30,35),  (35,40),  (40,45),  (45,50),  (50,60),  (60,80),  (80,inf)
                     0.000,   0.820,    0.687,    0.736,    0.679,    0.684,    0.694,    0.685,    0.694,    0.677,    0.665,    0.658,    0.857,  // eta: {-2.5, -2.37}
                     0.000,   0.820,    0.687,    0.736,    0.710,    0.741,    0.746,    0.759,    0.781,    0.808,    0.813,    0.812,    0.874,  // eta: {-2.37, -2.01}
                     0.000,   0.566,    0.644,    0.670,    0.655,    0.684,    0.715,    0.727,    0.759,    0.781,    0.796,    0.801,    0.858,  // eta: {-2.01, -1.81}
                     0.000,   0.566,    0.644,    0.670,    0.655,    0.696,    0.726,    0.752,    0.785,    0.807,    0.820,    0.834,    0.886,  // eta: {-1.81, -1.52}
                     0.000,   0.535,    0.455,    0.570,    0.603,    0.634,    0.659,    0.685,    0.730,    0.765,    0.784,    0.794,    0.839,  // eta: {-1.52, -1.37}
                     0.000,   0.608,    0.658,    0.702,    0.684,    0.721,    0.748,    0.773,    0.799,    0.817,    0.841,    0.845,    0.899,  // eta: {-1.37, -1.15}
                     0.000,   0.608,    0.658,    0.702,    0.696,    0.735,    0.772,    0.793,    0.803,    0.822,    0.842,    0.853,    0.903,  // eta: {-1.15, -0.8}
                     0.000,   0.712,    0.692,    0.733,    0.730,    0.762,    0.803,    0.822,    0.837,    0.850,    0.860,    0.868,    0.906,  // eta: {-0.8, -0.6}
                     0.000,   0.712,    0.692,    0.733,    0.734,    0.769,    0.803,    0.820,    0.809,    0.827,    0.845,    0.858,    0.887,  // eta: {-0.6, -0.1}
                     0.000,   0.619,    0.581,    0.642,    0.667,    0.698,    0.733,    0.749,    0.746,    0.762,    0.778,    0.779,    0.812,  // eta: {-0.1, 0}
                     0.000,   0.619,    0.581,    0.642,    0.641,    0.685,    0.716,    0.727,    0.734,    0.752,    0.766,    0.766,    0.816,  // eta: {0, 0.1}
                     0.000,   0.712,    0.692,    0.733,    0.744,    0.773,    0.803,    0.821,    0.804,    0.823,    0.843,    0.856,    0.894,  // eta: {0.1, 0.6}
                     0.000,   0.712,    0.692,    0.733,    0.735,    0.772,    0.812,    0.831,    0.844,    0.858,    0.878,    0.877,    0.911,  // eta: {0.6, 0.8}
                     0.000,   0.608,    0.658,    0.702,    0.697,    0.737,    0.775,    0.798,    0.807,    0.826,    0.851,    0.855,    0.903,  // eta: {0.8, 1.15}
                     0.000,   0.608,    0.658,    0.702,    0.672,    0.721,    0.749,    0.774,    0.798,    0.818,    0.842,    0.850,    0.892,  // eta: {1.15, 1.37}
                     0.000,   0.535,    0.455,    0.570,    0.589,    0.639,    0.660,    0.693,    0.730,    0.766,    0.790,    0.801,    0.841,  // eta: {1.37, 1.52}
                     0.000,   0.566,    0.644,    0.670,    0.661,    0.696,    0.725,    0.751,    0.780,    0.803,    0.817,    0.835,    0.888,  // eta: {1.52, 1.81}
                     0.000,   0.566,    0.644,    0.670,    0.645,    0.688,    0.715,    0.733,    0.761,    0.782,    0.802,    0.804,    0.860,  // eta: {1.81, 2.01}
                     0.000,   0.820,    0.687,    0.736,    0.709,    0.733,    0.746,    0.759,    0.781,    0.802,    0.805,    0.803,    0.876,  // eta: {2.01, 2.37}
                     0.000,   0.820,    0.687,    0.736,    0.670,    0.678,    0.675,    0.669,    0.675,    0.652,    0.649,    0.627,    0.857,  // eta: {2.37, 2.5}
          }
        );

        /// Efficiency function for Loose ID electrons
        /// @note Numbers digitised from Fig 3 of 13 TeV note (ATL-PHYS-PUB-2015-041)
        /// @todo What about faking by jets or non-electrons?
        /// @note Manually symmetrised eta eff histogram
        const static std::vector<double> bineffs_eta_Loose  = { 0.950, 0.965, 0.955, 0.885, 0.950, 0.935, 0.90, 0 };
        /// @note Et eff histogram (10-20 GeV bin added by hand)
        /// normalisation factor as approximate double differential
        const static std::vector<double> bineffs_et_Loose  = {0.0, 0.90/0.95, 0.91/0.95, 0.92/0.95, 0.94/0.95, 0.95/0.95, 0.955/0.95, 0.965/0.95, 0.97/0.95, 0.98/0.95, 0.98/0.95 };
        static const HEPUtils::BinnedFn2D<double> eff2DEl_ATLAS_PHYS_PUB_2015_041_Loose(
          {0.0,   0.1,   0.8,   1.37,  1.52,  2.01,  2.37,  2.47, DBL_MAX},   // Bin edges in eta
          {0,  10,   20,   25,   30,   35,   40,    45,    50,   60,  80, DBL_MAX},   // Bin edges in pT
          Utils::outer_product(bineffs_eta_Loose, bineffs_et_Loose)
//          {
//            0.0, 0.9, 0.91, 0.92, 0.94, 0.95, 0.955, 0.965, 0.97, 0.98, 0.98,
//            0.0, 0.914, 0.924, 0.935, 0.955, 0.965, 0.97, 0.98, 0.985, 0.995, 0.995,
//            0.0, 0.905, 0.915, 0.925, 0.945, 0.955, 0.96, 0.97, 0.975, 0.985, 0.985,
//            0.0, 0.838, 0.848, 0.857, 0.876, 0.885, 0.89, 0.899, 0.904, 0.913, 0.913,
//            0.0, 0.9, 0.91, 0.92, 0.94, 0.95, 0.955, 0.965, 0.97, 0.98, 0.98, 0.886,
//            0.0, 0.896, 0.905, 0.925, 0.935, 0.94, 0.95, 0.955, 0.965, 0.965, 0.853,
//            0.0, 0.862, 0.872, 0.891, 0.9, 0.905, 0.914, 0.919, 0.928, 0.928,
//            0.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//          }
        );

        /// Efficiency function for Medium ID electrons
        /// @note Numbers digitised from Fig 3 of 13 TeV note (ATL-PHYS-PUB-2015-041)
        /// @note Manually symmetrised eta eff histogram
        const static std::vector<double> bineffs_eta_Medium  = { 0.900, 0.930, 0.905, 0.830, 0.900, 0.880, 0.85, 0 };
        /// @note Et eff histogram (10-20 GeV bin added by hand)
        /// normalisation factor as approximate double differential
        const static std::vector<double> bineffs_et_Medium  = {0.0, 0.83/0.95, 0.845/0.95, 0.87/0.95, 0.89/0.95, 0.90/0.95, 0.91/0.95, 0.92/0.95, 0.93/0.95, 0.95/0.95, 0.95/0.95};
        static const HEPUtils::BinnedFn2D<double> eff2DEl_ATLAS_PHYS_PUB_2015_041_Medium(
          {0.0,   0.1,   0.8,   1.37,  1.52,  2.01,  2.37,  2.47, DBL_MAX},   // Bin edges in eta
          {0, 10,   20,   25,   30,   35,   40,    45,    50,   60,  80, DBL_MAX},   // Bin edges in pT
          Utils::outer_product(bineffs_eta_Medium, bineffs_et_Medium)
        );


        /// Electron 2019 ID efficiency functions from https://arxiv.org/pdf/1902.04655.pdf
        /// @note These efficiencies are 1D efficiencies so only pT is used
        /// Digitised from Fig 8

        // VeryLoose
        static const HEPUtils::BinnedFn1D<double> eff1DEl_PERF_2017_01_ID_VeryLoose(
          {0.0, 6.668795911849248, 9.673354432217419, 14.643593391597225, 19.57318312476409, 24.71356813100665, 29.655352632037403, 34.594233616910074, 39.73636073284749, 44.68221015649952, 49.6292209866148, 59.52440405330856, 79.51859702099242, DBL_MAX},
          {0.9054376657824932, 0.9267904509283819, 0.8757294429708221, 0.8450928381962863, 0.8775862068965516, 0.889655172413793, 0.9035809018567638, 0.9193633952254641, 0.929575596816976, 0.9370026525198938, 0.942572944297082, 0.9509283819628646, 0.9592838196286471}
        );

        // Loose
        static const HEPUtils::BinnedFn1D<double> eff1DEl_PERF_2017_01_ID_Loose(
          {0.0, 6.668795911849248, 9.673354432217419, 14.643593391597225, 19.57318312476409, 24.71356813100665, 29.655352632037403, 34.594233616910074, 39.73636073284749, 44.68221015649952, 49.6292209866148, 59.52440405330856, 79.51859702099242, DBL_MAX},
          {0.9054376657824932, 0.9267904509283819, 0.8757294429708221, 0.8450928381962863, 0.8775862068965516, 0.889655172413793, 0.9035809018567638, 0.9193633952254641, 0.929575596816976, 0.9370026525198938, 0.942572944297082, 0.9509283819628646, 0.9592838196286471}
        );

        // Medium
        static const HEPUtils::BinnedFn1D<double> eff1DEl_PERF_2017_01_ID_Medium(
          {0.0, 6.668795911849248, 9.673354432217419, 14.643593391597225, 19.57318312476409, 24.71356813100665, 29.655352632037403, 34.594233616910074, 39.73636073284749, 44.68221015649952, 49.6292209866148, 59.52440405330856, 79.51859702099242, DBL_MAX},
          { 0.7355437665782492, 0.7912466843501325, 0.7986737400530503, 0.7717506631299733, 0.8135278514588858, 0.8348806366047744, 0.8525198938992041, 0.8692307692307691, 0.8822281167108752, 0.889655172413793, 0.902652519893899, 0.9230769230769229, 0.9407161803713526 }
        );

        // Tight
        static const HEPUtils::BinnedFn1D<double> eff1DEl_PERF_2017_01_ID_Tight(
          {0.0, 6.668795911849248, 9.673354432217419, 14.643593391597225, 19.57318312476409, 24.71356813100665, 29.655352632037403, 34.594233616910074, 39.73636073284749, 44.68221015649952, 49.6292209866148, 59.52440405330856, 79.51859702099242, DBL_MAX},
          { 0.5572944297082227, 0.6213527851458884, 0.6547745358090185, 0.6714854111405835, 0.699336870026525, 0.7299734748010609, 0.7559681697612731, 0.7754641909814322, 0.7921750663129972, 0.8079575596816975, 0.8311671087533155, 0.8710875331564986, 0.8989389920424402 }
        );


        /// Electron 2019 Isolation efficiency functions from https://arxiv.org/pdf/1902.04655.pdf
        /// @note These efficiencies are 1D efficiencies so only pT is used
        /// Digitised from Fig 12

        // LooseTrackOnly
        static const HEPUtils::BinnedFn1D<double> eff1DEl_PERF_2017_01_Iso_LooseTrackOnly(
          {0.0, 6.548307897301772, 9.706735099256047, 14.643593391597225, 19.611982283197417, 24.561829913760132, 29.71154676569653, 34.461525174885566, 39.61370954807349, 44.56047277707178, 49.5109372879474, 59.60803424919497, 79.4086585320716, DBL_MAX},
          {0.9694027334287603, 0.9841898810834618, 0.9915715839022242, 0.9890807366218896, 0.9875756991852016, 0.9875509249064084, 0.9875261506276152, 0.9879947974014535, 0.9884634441752919, 0.9884386698964986, 0.9888959617925568, 0.9907953231667035, 0.9930404921823388}
        );

        // Loose
        static const HEPUtils::BinnedFn1D<double> eff1DEl_PERF_2017_01_Iso_Loose(
          {0.0, 6.548307897301772, 9.706735099256047, 14.643593391597225, 19.611982283197417, 24.561829913760132, 29.71154676569653, 34.461525174885566, 39.61370954807349, 44.56047277707178, 49.5109372879474, 59.60803424919497, 79.4086585320716, DBL_MAX},
          {0.9595332801145123, 0.9812303870292888, 0.9891055109006828, 0.9875994412023784, 0.9856020149746753, 0.9826167143800926, 0.9820985190486677, 0.9820737447698745, 0.9820489704910813, 0.9825186495265361, 0.9829749091609778, 0.9903008698524555, 0.9930394599207224}
        );

        // GradientLoose
        static const HEPUtils::BinnedFn1D<double> eff1DEl_PERF_2017_01_Iso_GradientLoose(
          {0.0, 6.548307897301772, 9.706735099256047, 14.643593391597225, 19.611982283197417, 24.561829913760132, 29.71154676569653, 34.461525174885566, 39.61370954807349, 44.56047277707178, 49.5109372879474, 59.60803424919497, 79.4086585320716, DBL_MAX},
          {0.8973632597445498, 0.9471843343977098, 0.9693676365338032, 0.9466465260955738, 0.947115172869412, 0.9485706617485136, 0.9539735190486678, 0.9593784408720547, 0.9642868448579609, 0.9706755120017618, 0.9780417308962784, 0.9843808494824929, 0.9851457553402335}
        );

        // Gradient
        static const HEPUtils::BinnedFn1D<double> eff1DEl_PERF_2017_01_Iso_Gradient(
          {0.0, 6.548307897301772, 9.706735099256047, 14.643593391597225, 19.611982283197417, 24.561829913760132, 29.71154676569653, 34.461525174885566, 39.61370954807349, 44.56047277707178, 49.5109372879474, 59.60803424919497, 79.4086585320716, DBL_MAX},
          {0.8425935229024444, 0.9082030389781987, 0.944204195111209, 0.9007573359392205, 0.9081359419731337, 0.9145235768553183, 0.924368255890773, 0.9351987447698745, 0.9460292336489761, 0.9573531435807092, 0.9716251926888351, 0.9838874284298613, 0.9851457553402335}
        );


        /// Electron 2020 reconstruction efficiency functions in 1908.00005 using 81 fb^-1 of Run 2 data
        /// @note These efficiencies are 1D efficiencies so only dependence on p_T is used
        /// Digitised from Fig 5
        static const HEPUtils::BinnedFn1D<double> eff1DEl_EGAM_2018_01_Recon(
          {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0, 14.5, 15.0, 15.5, 16.0, 16.5, 17.0, 17.5, 18.0, 18.5, 19.0, 19.5, 20.0, 20.5, 21.0, 21.5, 22.0, 22.5, 23.0, 23.5, 24.0, 24.5, DBL_MAX},   // Bin edges in pT
          {0.0, 0.0, 0.0, 0.0, 0.003218, 0.049709, 0.203532, 0.388353, 0.546803, 0.662459, 0.749662, 0.807719, 0.850278, 0.875487, 0.893757, 0.907169, 0.919424, 0.926128, 0.932831, 0.936759, 0.940224, 0.944846, 0.947386, 0.949695, 0.951078, 0.953849, 0.955695, 0.956847, 0.958924, 0.959845, 0.962154, 0.96238, 0.96492, 0.966766, 0.966762, 0.967914, 0.967678, 0.970912, 0.970676, 0.97229, 0.972286, 0.97205, 0.973664, 0.97366, 0.973655, 0.973419, 0.975496, 0.976417, 0.977106, 0.976639}
        );

        /// Electron 2020 ID efficiency functions in 1908.00005 using 81 fb^-1 of Run 2 data
        /// @note These efficiencies are 1D efficiencies so only dependence on p_T is used
        /// Digitised from Fig 23a

        // Loose
        static const HEPUtils::BinnedFn1D<double> eff1DEl_EGAM_2018_01_ID_Loose(
          {4.5, 7.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 80.0, DBL_MAX},   // Bin edeges in pT
          {0.976333, 0.928653, 0.882698, 0.830078, 0.86466, 0.884306, 0.901769, 0.920381, 0.930032, 0.936581, 0.938994, 0.943589, 0.949449}
        );

        // Medium
        static const HEPUtils::BinnedFn1D<double> eff1DEl_EGAM_2018_01_ID_Medium(
          {4.5, 7.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 80.0, DBL_MAX},   // Bin edeges in pT
          {0.790671, 0.797679, 0.816062, 0.752183, 0.794807, 0.82801, 0.847541, 0.868796, 0.882008, 0.887868, 0.897518, 0.916475, 0.93233}
        );

        // Tight
        static const HEPUtils::BinnedFn1D<double> eff1DEl_EGAM_2018_01_ID_Tight(
          {4.5, 7.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 80.0, DBL_MAX},   // Bin edeges in pT
          {0.582835, 0.608686, 0.670726, 0.651999, 0.684283, 0.716567, 0.747358, 0.768038, 0.782399, 0.795381, 0.815832, 0.853631, 0.884536}
        );


        /// Electron 2020 isolation efficiency functions in 1908.00005 using 81 fb^-1 of Run 2 data, EGAM-2018-01
        /// @note These efficiencies are 1D efficiencies so only dependence on p_T is used
        /// Digitize from Fig 16

        // Gradient
        static const HEPUtils::BinnedFn1D<double> eff1DEl_EGAM_2018_01_Iso_Gradient(
          {4.5, 7.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 80.0, 150.0, 200.0, 250.0, 300.0, 350.0, DBL_MAX},   // Bin egdes in pT
          {0.800008, 0.880847, 0.927209, 0.879823, 0.888724, 0.895806, 0.908012, 0.9198, 0.929307, 0.941235, 0.960432, 0.979162, 0.982515, 0.993515, 0.994261, 0.995376, 0.993139, 0.992581}
        );

        // Loose
        static const HEPUtils::BinnedFn1D<double> eff1DEl_EGAM_2018_01_Iso_Loose(
          {4.5, 7.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 80.0, 150.0, 200.0, 250.0, 300.0, 350.0, DBL_MAX},   // Bin egdes in pT
          {0.740555, 0.826427, 0.905545, 0.951997, 0.972965, 0.983728, 0.990392, 0.994352, 0.996819, 0.997565, 0.997844, 0.998311, 0.99859, 0.99859, 0.999057, 0.999105, 0.996589, 0.997614}
        );

        // Tight
        static const HEPUtils::BinnedFn1D<double> eff1DEl_EGAM_2018_01_Iso_Tight(
          {4.5, 7.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 80.0, 150.0, 200.0, 250.0, 300.0, 350.0, DBL_MAX},   // Bin egdes in pT
          {0.458893, 0.541276, 0.617828, 0.698061, 0.769957, 0.822, 0.862863, 0.895528, 0.924554, 0.940538, 0.95321, 0.970449, 0.985547, 0.992351, 0.993187, 0.993606, 0.991326, 0.991326}
        );

        // HighPtCaloOnly
        static const HEPUtils::BinnedFn1D<double> eff1DEl_EGAM_2018_01_Iso_HighPtCaloOnly(
          {4.5, 7.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 80.0, 150.0, 200.0, 250.0, 300.0, 350.0, DBL_MAX},   // Bin egdes in pT
          {0.982097, 0.975105, 0.969703, 0.967933, 0.966908, 0.965137, 0.965416, 0.966859, 0.970449, 0.970358, 0.967138, 0.962014, 0.950973, 0.926185, 0.904053, 0.908291, 0.925906, 0.929168}
        );


        // FIXME: Where is this from and is it used?
        // VeryLoose WP from
        //static const HEPUtils::BinnedFn2D<double> eff2DEl_VeryLoose(
        //  {0., DBL_MAX},   // Bin edges in eta
        //  {0., 25., 40., 60., 80., 100., 150., 200., 250., 300., 400., 500.,DBL_MAX },   // Bin edges in pT
        //  {
        //    // pT: (0,25),  (25,40),  (40,60),  (60,80),  (80,100),  (100,150),  (150,200),  (200,250),  (250,300),  (300,400),  (400,500),  (500,inf)
        //            0.0,      0.78,     0.80,     0.82,     0.83,       0.84,      0.825,       0.82,       0.81,       0.8,       0.795,       0.79   // eta: (0, DBL_MAX)
        //  }
        //);


      /// @}


      /// Muon efficiencies
      /// @{

        /// Generic muon efficiency
        /// Randomly filter the supplied particle list by parameterised muon efficiency
        static const HEPUtils::BinnedFn2D<double> eff2DMu_Generic(
          {0,1.5,2.7,DBL_MAX}, //< |eta|
          {0,10.0,DBL_MAX}, //< pT
          {
            0., 0.95,
            0., 0.85,
            0., 0.
          }
        );

        /// Generic R2 muon efficiency
        /// Randomly filter the supplied particle list by parameterised muon efficiency
        static const HEPUtils::BinnedFn2D<double> eff2DMu_R2(
          {0, 2.7, DBL_MAX}, //< |eta|
          {0., 3.5, 4., 5., 6., 7., 8., 10., DBL_MAX}, //< pT
          {
            0.00, 0.76, 0.94, 0.97, 0.98, 0.98, 0.98, 0.99,//
            0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00
          }
        );

        /// Muon 2020 identification efficiency functions from full Run2 dataset released in 2012.00578, MUON-2018-03
        /// @note These efficiencies are 1D efficiencies so only dependence on p_T is used
        /// Digitised from Fig 11a

        // Loose WP
        static const HEPUtils::BinnedFn1D<double> eff1DMu_MUON_2018_03_ID_Loose(
          {3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 14.0, 16.0, 18.0, DBL_MAX},   // Bin edges in pT
          {0.87075, 0.93129, 0.97241, 0.98851, 0.99157, 0.98851, 0.98799, 0.98799, 0.98799, 0.98748, 0.98672, 0.98748, 0.98927}
        );

        // Medium WP
        static const HEPUtils::BinnedFn1D<double> eff1DMu_MUON_2018_03_ID_Medium(
          {3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 14.0, 16.0, 18.0, DBL_MAX},   // Bin edges in pT
          {0.45262, 0.61328, 0.80766, 0.9387, 0.96245, 0.97063, 0.97165, 0.97216, 0.97292, 0.97292, 0.97216, 0.97114, 0.97522}
        );

        // Tight WP
        static const HEPUtils::BinnedFn1D<double> eff1DMu_MUON_2018_03_ID_Tight(
          {3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 14.0, 16.0, 18.0, DBL_MAX},   // Bin edges in pT
          {0.0, 0.0, 0.66948, 0.8143, 0.85466, 0.87816, 0.89246, 0.90421, 0.91418, 0.91877, 0.92031, 0.92669, 0.93972}
        );


        /// Muon 2020 isolation efficiency functions from full Run2 dataset released in 2012.00578, MUON-2018-03
        /// @note These efficiencies are 1D efficiencies so only real dependence on p_T is used
        /// Digitised from Fig 19a

        // Loose WP
        static const HEPUtils::BinnedFn1D<double> eff1DMu_MUON_2018_03_Iso_Loose(
          // Digitised from Fig 19a
          {3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 15.0, 20.0, 30.0, 40.0, 55.0, 70.0, 90.0, 150.0, DBL_MAX},   // Bin edges in pT
          {0.655349, 0.725581, 0.765116, 0.788605, 0.82093, 0.851395, 0.877907, 0.92, 0.956279, 0.981163, 0.992558, 0.996744, 0.997442, 0.997442, 0.997674, 0.995116}
        );


        // Tight WP
        static const HEPUtils::BinnedFn1D<double> eff1DMu_MUON_2018_03_Iso_Tight(
          // Digitised from Fig 19a
          {3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 15.0, 20.0, 30.0, 40.0, 55.0, 70.0, 90.0, 150.0, DBL_MAX},   // Bin edges in pT
          {0.56788, 0.63355, 0.66702, 0.68974, 0.70173, 0.71814, 0.7314, 0.75917, 0.79262, 0.84313, 0.9189, 0.96941, 0.9915, 0.99653, 0.99649, 0.99517}
        );


        /// Muon 2020 identification efficiencies for very low transverse momentum, from ATL-PHYS-PUB-2020-002
        /// @note: These are efficiencies binned in eta, so make sure to use the correct function form (applyEfficiency(...,...,false))
        /// Digitised from Fig 2a

        // Medium WP
        static const HEPUtils::BinnedFn1D<double> eff1DMu_ATLAS_PHYS_PUB_2020_002_Medium(
          {-2.5, -2.4, -2.3, -2.2, -2.1, -2.0, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5},   // Bin edges in eta
          {90.74, 94.48, 93.50, 95.47, 93.10, 92.91, 94.09, 93.69, 95.07, 91.33, 87.34, 76.55, 54.88, 56.26, 72.61, 71.82, 74.58, 73.99, 65.91, 69.85, 70.84, 73.00, 73.99, 69.06, 69.46, 68.67, 71.43, 74.38, 70.84, 70.44, 65.32, 64.93, 74.58, 75.76, 74.38, 73.20, 60.20, 55.86, 77.54, 87.19, 90.34, 94.48, 94.88, 95.07, 94.88, 95.07, 96.26, 96.26, 96.26, 93.89}
        );

        // LowPT WP
        static const HEPUtils::BinnedFn1D<double> eff1DMu_ATLAS_PHYS_PUB_2020_002_LowPT(
          {-2.5, -2.4, -2.3, -2.2, -2.1, -2.0, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5},   // Bin edges in eta
          {87.59, 91.72, 90.94, 93.50, 90.34, 90.54, 91.92, 90.34, 91.92, 90.34, 89.75, 87.19, 83.05, 73.60, 86.01, 93.10, 91.92, 92.12, 85.62, 88.37, 90.15, 91.53, 92.12, 88.37, 72.41, 72.22, 88.18, 92.12, 92.12, 90.94, 86.80, 84.24, 91.33, 91.33, 93.89, 87.98, 75.96, 80.69, 86.80, 90.74, 89.56, 90.74, 92.51, 92.51, 91.92, 91.33, 94.68, 93.69, 94.09, 90.74}
        );

      /// @}

      /// Tau efficiencies
      /// @{

        /// Generic tau efficiency
        /// Randomly filter the supplied particle list by parameterised Run 1 tau efficiency
        /// @note From Delphes 3.1.2
        /// @todo Use https://cds.cern.ch/record/1233743/files/ATL-PHYS-PUB-2010-001.pdf -- it is more accurate and has pT-dependence
        static const double effTau_R1 = 0.40;

        /// Randomly filter the supplied particle list by parameterised Run 2 tau efficiency
        /// @note From Delphes 3.3.2 & ATL-PHYS-PUB-2015-045, 60% for 1-prong, 70% for multi-prong: this is *wrong*!!
        /// @note No delete, because this should only ever be applied to copies of the Event Particle* vectors in Analysis routines
        // Delphes 3.3.2 config:
        //   set DeltaR 0.2
        //   set DeltaRTrack 0.2
        //   set TrackPTMin 1.0
        //   set TauPTMin 1.0
        //   set TauEtaMax 2.5
        //   # instructions: {n-prongs} {eff}
        //   # 1 - one prong efficiency
        //   # 2 - two or more efficiency
        //   # -1 - one prong mistag rate
        //   # -2 - two or more mistag rate
        //   set BitNumber 0
        //   # taken from ATL-PHYS-PUB-2015-045 (medium working point)
        //   add EfficiencyFormula {1} {0.70}
        //   add EfficiencyFormula {2} {0.60}
        //   add EfficiencyFormula {-1} {0.02}
        //   add EfficiencyFormula {-2} {0.01}
        // filtereff(taus, 0.65);

        // Distributions from ATL-PHYS-PUB-2015-045, Fig 10
        const static std::vector<double> binedges_pt    = { 0.,  20.,  40.,   60.,   120.,  160.,   220.,   280.,   380.,    500.,  DBL_MAX };
        // TG: Commented these because they are not used
        //const static std::vector<double> bineffs_pt_1p  = { 0.,  .54,  .55,   .56,    .58,   .57,    .56,    .54,     .51,     0. };
        //const static std::vector<double> bineffs_pt_3p  = { 0.,  .40,  .41,   .42,    .46,   .46,    .43,    .39,     .33,     0. };
        //const static HEPUtils::BinnedFn1D<double> _eff_pt_1p(binedges_pt, bineffs_pt_1p);
        //const static HEPUtils::BinnedFn1D<double> _eff_pt_3p(binedges_pt, bineffs_pt_3p);
        // 85% 1-prong, 15% >=3-prong
        const static std::vector<double> bineffs_pt_avg = { 0.,  .52,  .53,   .54,    .56,   .55,    .54,    .52,     .48,     0. };
        const static HEPUtils::BinnedFn1D<double> eff1DTau_R2(binedges_pt, bineffs_pt_avg);


        /// Randomly filter the supplied particle list by parameterised Run 2 RNN tau efficiency
        /// @note this is the newer RNN Tau ID Algorithm, use the other function for the older BDT Tau ID Algorithm.
        /// @note by design these Tau ID working points have flat signal efficiencies in eta and phi
        /// @note using https://cds.cern.ch/record/2688062/files/ATL-PHYS-PUB-2019-033.pdf
        /// @note assuming frequency: 85% 1-prong, 15% >=3-prong
        const static double effTau_R2_RNN_Tight     = 0.58;  // 0.6 (0.45) for 1 (3) prongs
        const static double effTau_R2_RNN_Medium    = 0.73;  // 0.75 (0.6) for 1 (3) prongs
        const static double effTau_R2_RNN_Loose     = 0.84;  // 0.85 (0.75) for 1 (3) prongs
        const static double effTau_R2_RNN_VeryLoose = 0.95;  // 0.95 (0.95) for 1 (3) prongs

      /// @}

      /// Track efficiencies from ATL-PHYS-PUB-2015-051
      /// Digitised and made 2d from figs 1a and 1b
      /// @{

        // Tight Primary WP
        const static HEPUtils::BinnedFn2D<double> eff2DTrack_ATL_PHYS_PUB_2015_051_Tight_Primary(
          {-2.5, -2.3, -2.1, -1.9, -1.7, -1.5, -1.3, -1.1, -0.9, -0.7, -0.5, -0.3, -0.1, 0.1, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1, 2.3, 2.5},    // Bin edges in eta
          {0, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 2, 2.5, 3.0, 3.5, 4.0, 5, DBL_MAX},    // Bin edges in pT
          {0.63*0.73, 0.63*0.79, 0.63*0.79, 0.63*0.80, 0.63*0.81, 0.63*0.81, 0.63*0.81, 0.63*0.82, 0.63*0.82, 0.63*0.82, 0.63*0.82, 0.63*0.83, 0.63*0.84, 0.63*0.84, 0.63*0.85, 0.63*0.85, 0.63*0.85, 0.,
           0.71*0.73, 0.71*0.79, 0.71*0.79, 0.71*0.80, 0.71*0.81, 0.71*0.81, 0.71*0.81, 0.71*0.82, 0.71*0.82, 0.71*0.82, 0.71*0.82, 0.71*0.83, 0.71*0.84, 0.71*0.84, 0.71*0.85, 0.71*0.85, 0.71*0.85, 0.,
           0.70*0.73, 0.70*0.79, 0.70*0.79, 0.70*0.80, 0.70*0.81, 0.70*0.81, 0.70*0.81, 0.70*0.82, 0.70*0.82, 0.70*0.82, 0.70*0.82, 0.70*0.83, 0.70*0.84, 0.70*0.84, 0.70*0.85, 0.70*0.85, 0.70*0.85, 0.,
           0.71*0.73, 0.71*0.79, 0.71*0.79, 0.71*0.80, 0.71*0.81, 0.71*0.81, 0.71*0.81, 0.71*0.82, 0.71*0.82, 0.71*0.82, 0.71*0.82, 0.71*0.83, 0.71*0.84, 0.71*0.84, 0.71*0.85, 0.71*0.85, 0.71*0.85, 0.,
           0.75*0.73, 0.75*0.79, 0.75*0.79, 0.75*0.80, 0.75*0.81, 0.75*0.81, 0.75*0.81, 0.75*0.82, 0.75*0.82, 0.75*0.82, 0.75*0.82, 0.75*0.83, 0.75*0.84, 0.75*0.84, 0.75*0.85, 0.75*0.85, 0.75*0.85, 0.,
           0.79*0.73, 0.79*0.79, 0.79*0.79, 0.79*0.80, 0.79*0.81, 0.79*0.81, 0.79*0.81, 0.79*0.82, 0.79*0.82, 0.79*0.82, 0.79*0.82, 0.79*0.83, 0.79*0.84, 0.79*0.84, 0.79*0.85, 0.79*0.85, 0.79*0.85, 0.,
           0.82*0.73, 0.82*0.79, 0.82*0.79, 0.82*0.80, 0.82*0.81, 0.82*0.81, 0.82*0.81, 0.82*0.82, 0.82*0.82, 0.82*0.82, 0.82*0.82, 0.82*0.83, 0.82*0.84, 0.82*0.84, 0.82*0.85, 0.82*0.85, 0.82*0.85, 0.,
           0.84*0.73, 0.84*0.79, 0.84*0.79, 0.84*0.80, 0.84*0.81, 0.84*0.81, 0.84*0.81, 0.84*0.82, 0.84*0.82, 0.84*0.82, 0.84*0.82, 0.84*0.83, 0.84*0.84, 0.84*0.84, 0.84*0.85, 0.84*0.85, 0.84*0.85, 0.,
           0.86*0.73, 0.86*0.79, 0.86*0.79, 0.86*0.80, 0.86*0.81, 0.86*0.81, 0.86*0.81, 0.86*0.82, 0.86*0.82, 0.86*0.82, 0.86*0.82, 0.86*0.83, 0.86*0.84, 0.86*0.84, 0.86*0.85, 0.86*0.85, 0.86*0.85, 0.,
           0.86*0.73, 0.86*0.79, 0.86*0.79, 0.86*0.80, 0.86*0.81, 0.86*0.81, 0.86*0.81, 0.86*0.82, 0.86*0.82, 0.86*0.82, 0.86*0.82, 0.86*0.83, 0.86*0.84, 0.86*0.84, 0.86*0.85, 0.86*0.85, 0.86*0.85, 0.,
           0.87*0.73, 0.87*0.79, 0.87*0.79, 0.87*0.80, 0.87*0.81, 0.87*0.81, 0.87*0.81, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.83, 0.87*0.84, 0.87*0.84, 0.87*0.85, 0.87*0.85, 0.87*0.85, 0.,
           0.87*0.73, 0.87*0.79, 0.87*0.79, 0.87*0.80, 0.87*0.81, 0.87*0.81, 0.87*0.81, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.83, 0.87*0.84, 0.87*0.84, 0.87*0.85, 0.87*0.85, 0.87*0.85, 0.,
           0.87*0.73, 0.87*0.79, 0.87*0.79, 0.87*0.80, 0.87*0.81, 0.87*0.81, 0.87*0.81, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.83, 0.87*0.84, 0.87*0.84, 0.87*0.85, 0.87*0.85, 0.87*0.85, 0.,
           0.87*0.73, 0.87*0.79, 0.87*0.79, 0.87*0.80, 0.87*0.81, 0.87*0.81, 0.87*0.81, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.83, 0.87*0.84, 0.87*0.84, 0.87*0.85, 0.87*0.85, 0.87*0.85, 0.,
           0.87*0.73, 0.87*0.79, 0.87*0.79, 0.87*0.80, 0.87*0.81, 0.87*0.81, 0.87*0.81, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.83, 0.87*0.84, 0.87*0.84, 0.87*0.85, 0.87*0.85, 0.87*0.85, 0.,
           0.87*0.73, 0.87*0.79, 0.87*0.79, 0.87*0.80, 0.87*0.81, 0.87*0.81, 0.87*0.81, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.82, 0.87*0.83, 0.87*0.84, 0.87*0.84, 0.87*0.85, 0.87*0.85, 0.87*0.85, 0.,
           0.86*0.73, 0.86*0.79, 0.86*0.79, 0.86*0.80, 0.86*0.81, 0.86*0.81, 0.86*0.81, 0.86*0.82, 0.86*0.82, 0.86*0.82, 0.86*0.82, 0.86*0.83, 0.86*0.84, 0.86*0.84, 0.86*0.85, 0.86*0.85, 0.86*0.85, 0.,
           0.84*0.73, 0.84*0.79, 0.84*0.79, 0.84*0.80, 0.84*0.81, 0.84*0.81, 0.84*0.81, 0.84*0.82, 0.84*0.82, 0.84*0.82, 0.84*0.82, 0.84*0.83, 0.84*0.84, 0.84*0.84, 0.84*0.85, 0.84*0.85, 0.84*0.85, 0.,
           0.82*0.73, 0.82*0.79, 0.82*0.79, 0.82*0.80, 0.82*0.81, 0.82*0.81, 0.82*0.81, 0.82*0.82, 0.82*0.82, 0.82*0.82, 0.82*0.82, 0.82*0.83, 0.82*0.84, 0.82*0.84, 0.82*0.85, 0.82*0.85, 0.82*0.85, 0.,
           0.79*0.73, 0.79*0.79, 0.79*0.79, 0.79*0.80, 0.79*0.81, 0.79*0.81, 0.79*0.81, 0.79*0.82, 0.79*0.82, 0.79*0.82, 0.79*0.82, 0.79*0.83, 0.79*0.84, 0.79*0.84, 0.79*0.85, 0.79*0.85, 0.79*0.85, 0.,
           0.76*0.73, 0.76*0.79, 0.76*0.79, 0.76*0.80, 0.76*0.81, 0.76*0.81, 0.76*0.81, 0.76*0.82, 0.76*0.82, 0.76*0.82, 0.76*0.82, 0.76*0.83, 0.76*0.84, 0.76*0.84, 0.76*0.85, 0.76*0.85, 0.76*0.85, 0.,
           0.71*0.73, 0.71*0.79, 0.71*0.79, 0.71*0.80, 0.71*0.81, 0.71*0.81, 0.71*0.81, 0.71*0.82, 0.71*0.82, 0.71*0.82, 0.71*0.82, 0.71*0.83, 0.71*0.84, 0.71*0.84, 0.71*0.85, 0.71*0.85, 0.71*0.85, 0.,
           0.71*0.73, 0.71*0.79, 0.71*0.79, 0.71*0.80, 0.71*0.81, 0.71*0.81, 0.71*0.81, 0.71*0.82, 0.71*0.82, 0.71*0.82, 0.71*0.82, 0.71*0.83, 0.71*0.84, 0.71*0.84, 0.71*0.85, 0.71*0.85, 0.71*0.85, 0.,
           0.71*0.73, 0.71*0.79, 0.71*0.79, 0.71*0.80, 0.71*0.81, 0.71*0.81, 0.71*0.81, 0.71*0.82, 0.71*0.82, 0.71*0.82, 0.71*0.82, 0.71*0.83, 0.71*0.84, 0.71*0.84, 0.71*0.85, 0.71*0.85, 0.71*0.85, 0.,
           0.63*0.73, 0.63*0.79, 0.63*0.79, 0.63*0.80, 0.63*0.81, 0.63*0.81, 0.63*0.81, 0.63*0.82, 0.63*0.82, 0.63*0.82, 0.63*0.82, 0.63*0.83, 0.63*0.84, 0.63*0.84, 0.63*0.85, 0.63*0.85, 0.63*0.85, 0.}
        );

        // Loose WP
        const static HEPUtils::BinnedFn2D<double> eff2DTrack_ATL_PHYS_PUB_2015_051_Loose(
          {-2.5, -2.3, -2.1, -1.9, -1.7, -1.5, -1.3, -1.1, -0.9, -0.7, -0.5, -0.3, -0.1, 0.1, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1, 2.3, 2.5},    // Bin edges in eta
          {0, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 2, 2.5, 3.0, 3.5, 4.0, 5, DBL_MAX},    // Bin edges in pT
          {0.73*0.78, 0.73*0.84, 0.73*0.85, 0.73*0.86, 0.73*0.86, 0.73*0.86, 0.73*0.87, 0.73*0.87, 0.73*0.87, 0.73*0.87, 0.73*0.88, 0.73*0.88, 0.73*0.88, 0.73*0.89, 0.73*0.89, 0.73*0.89, 0.73*0.90, 0.,
           0.79*0.78, 0.79*0.84, 0.79*0.85, 0.79*0.86, 0.79*0.86, 0.79*0.86, 0.79*0.87, 0.79*0.87, 0.79*0.87, 0.79*0.87, 0.79*0.88, 0.79*0.88, 0.79*0.88, 0.79*0.89, 0.79*0.89, 0.79*0.89, 0.79*0.90, 0.,
           0.78*0.78, 0.78*0.84, 0.78*0.85, 0.78*0.86, 0.78*0.86, 0.78*0.86, 0.78*0.87, 0.78*0.87, 0.78*0.87, 0.78*0.87, 0.78*0.88, 0.78*0.88, 0.78*0.88, 0.78*0.89, 0.78*0.89, 0.78*0.89, 0.78*0.90, 0.,
           0.78*0.78, 0.78*0.84, 0.78*0.85, 0.78*0.86, 0.78*0.86, 0.78*0.86, 0.78*0.87, 0.78*0.87, 0.78*0.87, 0.78*0.87, 0.78*0.88, 0.78*0.88, 0.78*0.88, 0.78*0.89, 0.78*0.89, 0.78*0.89, 0.78*0.90, 0.,
           0.80*0.78, 0.80*0.84, 0.80*0.85, 0.80*0.86, 0.80*0.86, 0.80*0.86, 0.80*0.87, 0.80*0.87, 0.80*0.87, 0.80*0.87, 0.80*0.88, 0.80*0.88, 0.80*0.88, 0.80*0.89, 0.80*0.89, 0.80*0.89, 0.80*0.90, 0.,
           0.84*0.78, 0.84*0.84, 0.84*0.85, 0.84*0.86, 0.84*0.86, 0.84*0.86, 0.84*0.87, 0.84*0.87, 0.84*0.87, 0.84*0.87, 0.84*0.88, 0.84*0.88, 0.84*0.88, 0.84*0.89, 0.84*0.89, 0.84*0.89, 0.84*0.90, 0.,
           0.87*0.78, 0.87*0.84, 0.87*0.85, 0.87*0.86, 0.87*0.86, 0.87*0.86, 0.87*0.87, 0.87*0.87, 0.87*0.87, 0.87*0.87, 0.87*0.88, 0.87*0.88, 0.87*0.88, 0.87*0.89, 0.87*0.89, 0.87*0.89, 0.87*0.90, 0.,
           0.88*0.78, 0.88*0.84, 0.88*0.85, 0.88*0.86, 0.88*0.86, 0.88*0.86, 0.88*0.87, 0.88*0.87, 0.88*0.87, 0.88*0.87, 0.88*0.88, 0.88*0.88, 0.88*0.88, 0.88*0.89, 0.88*0.89, 0.88*0.89, 0.88*0.90, 0.,
           0.90*0.78, 0.90*0.84, 0.90*0.85, 0.90*0.86, 0.90*0.86, 0.90*0.86, 0.90*0.87, 0.90*0.87, 0.90*0.87, 0.90*0.87, 0.90*0.88, 0.90*0.88, 0.90*0.88, 0.90*0.89, 0.90*0.89, 0.90*0.89, 0.90*0.90, 0.,
           0.90*0.78, 0.90*0.84, 0.90*0.85, 0.90*0.86, 0.90*0.86, 0.90*0.86, 0.90*0.87, 0.90*0.87, 0.90*0.87, 0.90*0.87, 0.90*0.88, 0.90*0.88, 0.90*0.88, 0.90*0.89, 0.90*0.89, 0.90*0.89, 0.90*0.90, 0.,
           0.91*0.78, 0.91*0.84, 0.91*0.85, 0.91*0.86, 0.91*0.86, 0.91*0.86, 0.91*0.87, 0.91*0.87, 0.91*0.87, 0.91*0.87, 0.91*0.88, 0.91*0.88, 0.91*0.88, 0.91*0.89, 0.91*0.89, 0.91*0.89, 0.91*0.90, 0.,
           0.91*0.78, 0.91*0.84, 0.91*0.85, 0.91*0.86, 0.91*0.86, 0.91*0.86, 0.91*0.87, 0.91*0.87, 0.91*0.87, 0.91*0.87, 0.91*0.88, 0.91*0.88, 0.91*0.88, 0.91*0.89, 0.91*0.89, 0.91*0.89, 0.91*0.90, 0.,
           0.91*0.78, 0.91*0.84, 0.91*0.85, 0.91*0.86, 0.91*0.86, 0.91*0.86, 0.91*0.87, 0.91*0.87, 0.91*0.87, 0.91*0.87, 0.91*0.88, 0.91*0.88, 0.91*0.88, 0.91*0.89, 0.91*0.89, 0.91*0.89, 0.91*0.90, 0.,
           0.91*0.78, 0.91*0.84, 0.91*0.85, 0.91*0.86, 0.91*0.86, 0.91*0.86, 0.91*0.87, 0.91*0.87, 0.91*0.87, 0.91*0.87, 0.91*0.88, 0.91*0.88, 0.91*0.88, 0.91*0.89, 0.91*0.89, 0.91*0.89, 0.91*0.90, 0.,
           0.91*0.78, 0.91*0.84, 0.91*0.85, 0.91*0.86, 0.91*0.86, 0.91*0.86, 0.91*0.87, 0.91*0.87, 0.91*0.87, 0.91*0.87, 0.91*0.88, 0.91*0.88, 0.91*0.88, 0.91*0.89, 0.91*0.89, 0.91*0.89, 0.91*0.90, 0.,
           0.90*0.78, 0.90*0.84, 0.90*0.85, 0.90*0.86, 0.90*0.86, 0.90*0.86, 0.90*0.87, 0.90*0.87, 0.90*0.87, 0.90*0.87, 0.90*0.88, 0.90*0.88, 0.90*0.88, 0.90*0.89, 0.90*0.89, 0.90*0.89, 0.90*0.90, 0.,
           0.90*0.78, 0.90*0.84, 0.90*0.85, 0.90*0.86, 0.90*0.86, 0.90*0.86, 0.90*0.87, 0.90*0.87, 0.90*0.87, 0.90*0.87, 0.90*0.88, 0.90*0.88, 0.90*0.88, 0.90*0.89, 0.90*0.89, 0.90*0.89, 0.90*0.90, 0.,
           0.88*0.78, 0.88*0.84, 0.88*0.85, 0.88*0.86, 0.88*0.86, 0.88*0.86, 0.88*0.87, 0.88*0.87, 0.88*0.87, 0.88*0.87, 0.88*0.88, 0.88*0.88, 0.88*0.88, 0.88*0.89, 0.88*0.89, 0.88*0.89, 0.88*0.90, 0.,
           0.87*0.78, 0.87*0.84, 0.87*0.85, 0.87*0.86, 0.87*0.86, 0.87*0.86, 0.87*0.87, 0.87*0.87, 0.87*0.87, 0.87*0.87, 0.87*0.88, 0.87*0.88, 0.87*0.88, 0.87*0.89, 0.87*0.89, 0.87*0.89, 0.87*0.90, 0.,
           0.84*0.78, 0.84*0.84, 0.84*0.85, 0.84*0.86, 0.84*0.86, 0.84*0.86, 0.84*0.87, 0.84*0.87, 0.84*0.87, 0.84*0.87, 0.84*0.88, 0.84*0.88, 0.84*0.88, 0.84*0.89, 0.84*0.89, 0.84*0.89, 0.84*0.90, 0.,
           0.80*0.78, 0.80*0.84, 0.80*0.85, 0.80*0.86, 0.80*0.86, 0.80*0.86, 0.80*0.87, 0.80*0.87, 0.80*0.87, 0.80*0.87, 0.80*0.88, 0.80*0.88, 0.80*0.88, 0.80*0.89, 0.80*0.89, 0.80*0.89, 0.80*0.90, 0.,
           0.78*0.78, 0.78*0.84, 0.78*0.85, 0.78*0.86, 0.78*0.86, 0.78*0.86, 0.78*0.87, 0.78*0.87, 0.78*0.87, 0.78*0.87, 0.78*0.88, 0.78*0.88, 0.78*0.88, 0.78*0.89, 0.78*0.89, 0.78*0.89, 0.78*0.90, 0.,
           0.78*0.78, 0.78*0.84, 0.78*0.85, 0.78*0.86, 0.78*0.86, 0.78*0.86, 0.78*0.87, 0.78*0.87, 0.78*0.87, 0.78*0.87, 0.78*0.88, 0.78*0.88, 0.78*0.88, 0.78*0.89, 0.78*0.89, 0.78*0.89, 0.78*0.90, 0.,
           0.79*0.78, 0.79*0.84, 0.79*0.85, 0.79*0.86, 0.79*0.86, 0.79*0.86, 0.79*0.87, 0.79*0.87, 0.79*0.87, 0.79*0.87, 0.79*0.88, 0.79*0.88, 0.79*0.88, 0.79*0.89, 0.79*0.89, 0.79*0.89, 0.79*0.90, 0.,
           0.72*0.78, 0.72*0.84, 0.72*0.85, 0.72*0.86, 0.72*0.86, 0.72*0.86, 0.72*0.87, 0.72*0.87, 0.72*0.87, 0.72*0.87, 0.72*0.88, 0.72*0.88, 0.72*0.88, 0.72*0.89, 0.72*0.89, 0.72*0.89, 0.72*0.90, 0.}
        );

      /// @}


      /// Photon efficiencies
      /// @{

        const static HEPUtils::BinnedFn2D<double> eff2DPhoton_R2(
          { 0., 0.6, 1.37, 1.52, 1.81, 2.37, DBL_MAX },
          { 0., 10., 15., 20., 25., 30., 35., 40., 45., 50., 60., 80., 100., 125., 150., 175., 250., DBL_MAX },
          {
            0.00, 0.55, 0.70, 0.85, 0.89, 0.93, 0.95, 0.96, 0.96, 0.97, 0.97, 0.98, 0.97, 0.97, 0.97, 0.97, 0.97,
            0.00, 0.47, 0.66, 0.79, 0.86, 0.89, 0.94, 0.96, 0.97, 0.97, 0.98, 0.97, 0.98, 0.98, 0.98, 0.98, 0.98,
            0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
            0.00, 0.54, 0.71, 0.84, 0.88, 0.92, 0.93, 0.94, 0.95, 0.96, 0.96, 0.96, 0.96, 0.96, 0.96, 0.96, 0.96,
            0.00, 0.61, 0.74, 0.83, 0.88, 0.91, 0.94, 0.95, 0.96, 0.97, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98,
            0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00
          }
        );

      /// @}

      /////////////////////////
      // ATLAS Efficiency maps //

      // Map of MET 1D trigger efficiencies
      static const efficiency_map<HEPUtils::BinnedFn1D<double> > eff1DMET(
      {
        {"CERN_EP_2015_241",   eff1DMET_CERN_EP_2015_241},
      });

      // Map of electron 1D efficiencies
      static const efficiency_map<HEPUtils::BinnedFn1D<double> > eff1DEl(
      {
        {"PERF_2017_01_ID_VeryLoose",        eff1DEl_PERF_2017_01_ID_VeryLoose},
        {"PERF_2017_01_ID_Loose",            eff1DEl_PERF_2017_01_ID_Loose},
        {"PERF_2017_01_ID_Medium",           eff1DEl_PERF_2017_01_ID_Medium},
        {"PERF_2017_01_ID_Tight",            eff1DEl_PERF_2017_01_ID_Tight},
        {"PERF_2017_01_Iso_LooseTrackOnly",  eff1DEl_PERF_2017_01_Iso_LooseTrackOnly},
        {"PERF_2017_01_Iso_Loose",           eff1DEl_PERF_2017_01_Iso_Loose},
        {"PERF_2017_01_Iso_GradientLoose",   eff1DEl_PERF_2017_01_Iso_GradientLoose},
        {"PERF_2017_01_Iso_Gradient",        eff1DEl_PERF_2017_01_Iso_Gradient},
        {"EGAM_2018_01_Recon",               eff1DEl_EGAM_2018_01_Recon},
        {"EGAM_2018_01_ID_Loose",            eff1DEl_EGAM_2018_01_ID_Loose},
        {"EGAM_2018_01_ID_Medium",           eff1DEl_EGAM_2018_01_ID_Medium},
        {"EGAM_2018_01_ID_Tight",            eff1DEl_EGAM_2018_01_ID_Tight},
        {"EGAM_2018_01_Iso_Gradient",        eff1DEl_EGAM_2018_01_Iso_Gradient},
        {"EGAM_2018_01_Iso_Loose",           eff1DEl_EGAM_2018_01_Iso_Loose},
        {"EGAM_2018_01_Iso_Tight",           eff1DEl_EGAM_2018_01_Iso_Tight},
        {"EGAM_2018_01_Iso_HighPtCaloOnly",  eff1DEl_EGAM_2018_01_Iso_HighPtCaloOnly},
//        {"VeryLoose", eff2DEl_VeryLoose},
//        {"Medium", eff2DEl_Medium}
      });

      // Map of electron 2D efficiencies
      static const efficiency_map<HEPUtils::BinnedFn2D<double> > eff2DEl(
      {
        {"Generic",                        eff2DEl_Generic},
        {"ATLAS_CONF_2014_032_Medium",     eff2DEl_ATLAS_CONF_2014_032_Medium},
        {"ATLAS_CONF_2014_032_Tight",      eff2DEl_ATLAS_CONF_2014_032_Tight},
        {"ATLAS_PHYS_PUB_2015_041_Loose",  eff2DEl_ATLAS_PHYS_PUB_2015_041_Loose},
        {"ATLAS_PHYS_PUB_2015_041_Medium", eff2DEl_ATLAS_PHYS_PUB_2015_041_Medium}
      });


      // Map of muon 1D efficiencies
      static const efficiency_map<HEPUtils::BinnedFn1D<double> > eff1DMu(
      {
        {"MUON_2018_03_Iso_Loose", eff1DMu_MUON_2018_03_Iso_Loose},
        {"MUON_2018_03_Iso_Tight", eff1DMu_MUON_2018_03_Iso_Tight},
        {"MUON_2018_03_ID_Loose",  eff1DMu_MUON_2018_03_ID_Loose},
        {"MUON_2018_03_ID_Medium", eff1DMu_MUON_2018_03_ID_Medium},
        {"MUON_2018_03_ID_Tight",  eff1DMu_MUON_2018_03_ID_Tight},
        {"ATLAS_PHYS_PUB_2020_002_Medium", eff1DMu_ATLAS_PHYS_PUB_2020_002_Medium},
        {"ATLAS_PHYS_PUB_2020_002_LowPT", eff1DMu_ATLAS_PHYS_PUB_2020_002_LowPT},
      });

      // Map of muon 2D efficiencies
      static const efficiency_map<HEPUtils::BinnedFn2D<double> > eff2DMu(
      {
        {"Generic",    eff2DMu_Generic},
        {"R2",         eff2DMu_R2}
      });

      // Map of tau scalar efficiencies
      static const efficiency_map<double> effTau(
      {
        {"R1",                effTau_R1},
        {"R2_RNN_Tight",      effTau_R2_RNN_Tight},
        {"R2_RNN_Medium",     effTau_R2_RNN_Medium},
        {"R2_RNN_Loose",      effTau_R2_RNN_Loose},
        {"R2_RNN_VeryLoose",  effTau_R2_RNN_VeryLoose},
      });

      // Map of tau 1D efficiencies
      static const efficiency_map<HEPUtils::BinnedFn1D<double> > eff1DTau(
      {
        {"R2",            eff1DTau_R2},
      });

      // Map of track 2D efficiencies
      static const efficiency_map<HEPUtils::BinnedFn2D<double> > eff2DTrack(
      {
        {"ATL_PHYS_PUB_2015_051_Tight_Primary",   eff2DTrack_ATL_PHYS_PUB_2015_051_Tight_Primary},
        {"ATL_PHYS_PUB_2015_051_Loose",           eff2DTrack_ATL_PHYS_PUB_2015_051_Loose},
      });

      // Map of photon 2D efficiencies
      static const efficiency_map<HEPUtils::BinnedFn2D<double> > eff2DPhoton(
      {
        {"R2",           eff2DPhoton_R2},
      });
    }
  }
}
