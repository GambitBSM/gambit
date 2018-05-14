// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Thu 10 May 2018 14:47:57

#include "HSSUSY_observables.hpp"
#include "HSSUSY_mass_eigenstates.hpp"
#include "HSSUSY_a_muon.hpp"
#include "HSSUSY_edm.hpp"
#include "HSSUSY_effective_couplings.hpp"
#include "gm2calc_interface.hpp"
#include "eigen_utils.hpp"
#include "numerics2.hpp"
#include "wrappers.hpp"
#include "lowe.h"
#include "physical_input.hpp"

#define MODEL model
#define AMU a_muon
#define AMUUNCERTAINTY a_muon_uncertainty
#define AMUGM2CALC a_muon_gm2calc
#define AMUGM2CALCUNCERTAINTY a_muon_gm2calc_uncertainty
#define EDM0(p) edm_ ## p
#define EDM1(p,idx) edm_ ## p ## _ ## idx
#define EFFCPHIGGSPHOTONPHOTON eff_cp_higgs_photon_photon
#define EFFCPHIGGSGLUONGLUON eff_cp_higgs_gluon_gluon
#define EFFCPPSEUDOSCALARPHOTONPHOTON eff_cp_pseudoscalar_photon_photon
#define EFFCPPSEUDOSCALARGLUONGLUON eff_cp_pseudoscalar_gluon_gluon

#define ALPHA_S_MZ qedqcd.displayAlpha(softsusy::ALPHAS)
#define MWPole qedqcd.displayPoleMW()
#define MZPole qedqcd.displayPoleMZ()
#define MTPole qedqcd.displayPoleMt()
#define MBMB qedqcd.displayMbMb()
#define MTauPole qedqcd.displayPoleMtau()
#define MMPole qedqcd.displayPoleMmuon()

namespace flexiblesusy {

const int HSSUSY_observables::NUMBER_OF_OBSERVABLES;

HSSUSY_observables::HSSUSY_observables()
   : eff_cp_higgs_photon_photon(0)
   , eff_cp_higgs_gluon_gluon(0)

{
}

Eigen::ArrayXd HSSUSY_observables::get() const
{
   Eigen::ArrayXd vec(HSSUSY_observables::NUMBER_OF_OBSERVABLES);

   vec(0) = Re(eff_cp_higgs_photon_photon);
   vec(1) = Im(eff_cp_higgs_photon_photon);
   vec(2) = Re(eff_cp_higgs_gluon_gluon);
   vec(3) = Im(eff_cp_higgs_gluon_gluon);

   return vec;
}

std::vector<std::string> HSSUSY_observables::get_names()
{
   std::vector<std::string> names(HSSUSY_observables::NUMBER_OF_OBSERVABLES);

   names[0] = "Re(eff_cp_higgs_photon_photon)";
   names[1] = "Im(eff_cp_higgs_photon_photon)";
   names[2] = "Re(eff_cp_higgs_gluon_gluon)";
   names[3] = "Im(eff_cp_higgs_gluon_gluon)";

   return names;
}

void HSSUSY_observables::clear()
{
   eff_cp_higgs_photon_photon = std::complex<double>(0.,0.);
   eff_cp_higgs_gluon_gluon = std::complex<double>(0.,0.);

}

void HSSUSY_observables::set(const Eigen::ArrayXd& vec)
{
   assert(vec.rows() == HSSUSY_observables::NUMBER_OF_OBSERVABLES);

   eff_cp_higgs_photon_photon = std::complex<double>(vec(0), vec(1));
   eff_cp_higgs_gluon_gluon = std::complex<double>(vec(2), vec(3));

}

HSSUSY_observables calculate_observables(const HSSUSY_mass_eigenstates& model,
                                              const softsusy::QedQcd& qedqcd,
                                              const Physical_input& physical_input,
                                              double scale)
{
   auto model_at_scale = model;

   if (scale > 0.)
      model_at_scale.run_to(scale);

   return calculate_observables(model_at_scale, qedqcd, physical_input);
}

HSSUSY_observables calculate_observables(const HSSUSY_mass_eigenstates& model,
                                              const softsusy::QedQcd& qedqcd,
                                              const Physical_input& physical_input)
{
   HSSUSY_observables observables;

   HSSUSY_effective_couplings effective_couplings(model, qedqcd, physical_input);
   effective_couplings.calculate_effective_couplings();

   observables.EFFCPHIGGSPHOTONPHOTON = effective_couplings.get_eff_CphhVPVP();
   observables.EFFCPHIGGSGLUONGLUON = effective_couplings.get_eff_CphhVGVG();

   return observables;
}

} // namespace flexiblesusy
