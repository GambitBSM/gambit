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

// File generated at Thu 10 May 2018 15:00:14

#include "MSSMNoFV_observables.hpp"
#include "MSSMNoFV_mass_eigenstates.hpp"
#include "MSSMNoFV_a_muon.hpp"
#include "MSSMNoFV_edm.hpp"
#include "MSSMNoFV_effective_couplings.hpp"
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

const int MSSMNoFV_observables::NUMBER_OF_OBSERVABLES;

MSSMNoFV_observables::MSSMNoFV_observables()
   : a_muon(0)
   , a_muon_gm2calc(0)
   , a_muon_gm2calc_uncertainty(0)

{
}

Eigen::ArrayXd MSSMNoFV_observables::get() const
{
   Eigen::ArrayXd vec(MSSMNoFV_observables::NUMBER_OF_OBSERVABLES);

   vec(0) = a_muon;
   vec(1) = a_muon_gm2calc;
   vec(2) = a_muon_gm2calc_uncertainty;

   return vec;
}

std::vector<std::string> MSSMNoFV_observables::get_names()
{
   std::vector<std::string> names(MSSMNoFV_observables::NUMBER_OF_OBSERVABLES);

   names[0] = "a_muon";
   names[1] = "a_muon_gm2calc";
   names[2] = "a_muon_gm2calc_uncertainty";

   return names;
}

void MSSMNoFV_observables::clear()
{
   a_muon = 0.;
   a_muon_gm2calc = 0.;
   a_muon_gm2calc_uncertainty = 0.;

}

void MSSMNoFV_observables::set(const Eigen::ArrayXd& vec)
{
   assert(vec.rows() == MSSMNoFV_observables::NUMBER_OF_OBSERVABLES);

   a_muon = vec(0);
   a_muon_gm2calc = vec(1);
   a_muon_gm2calc_uncertainty = vec(2);

}

MSSMNoFV_observables calculate_observables(const MSSMNoFV_mass_eigenstates& model,
                                              const softsusy::QedQcd& qedqcd,
                                              const Physical_input& physical_input,
                                              double scale)
{
   auto model_at_scale = model;

   if (scale > 0.)
      model_at_scale.run_to(scale);

   return calculate_observables(model_at_scale, qedqcd, physical_input);
}

MSSMNoFV_observables calculate_observables(const MSSMNoFV_mass_eigenstates& model,
                                              const softsusy::QedQcd& qedqcd,
                                              const Physical_input& physical_input)
{
   MSSMNoFV_observables observables;

   GM2Calc_data gm2calc_data;
   gm2calc_data.alpha_s_MZ = ALPHA_S_MZ;
   gm2calc_data.MZ    = MZPole;
   if (!is_zero(MODEL.get_physical().MVWm))
      gm2calc_data.MW = MODEL.get_physical().MVWm;
   else if (!is_zero(MWPole))
      gm2calc_data.MW = MWPole;
   gm2calc_data.mb_mb = MBMB;
   gm2calc_data.MT    = MTPole;
   gm2calc_data.MTau  = MTauPole;
   gm2calc_data.MM    = MMPole;
   gm2calc_data.MA0   = MODEL.get_physical().MAh(1);
   gm2calc_data.MSvm  = MODEL.get_physical().MSvmL;
   gm2calc_data.MSm   = MODEL.get_physical().MSm;
   gm2calc_data.MCha  = MODEL.get_physical().MCha;
   gm2calc_data.MChi  = MODEL.get_physical().MChi;
   gm2calc_data.scale = MODEL.get_scale();
   gm2calc_data.TB    = MODEL.get_vu() / MODEL.get_vd();
   gm2calc_data.Mu    = MODEL.get_Mu();
   gm2calc_data.M1    = MODEL.get_MassB();
   gm2calc_data.M2    = MODEL.get_MassWB();
   gm2calc_data.M3    = MODEL.get_MassG();
   gm2calc_data.mq2   = MODEL.get_mq2();
   gm2calc_data.mu2   = MODEL.get_mu2();
   gm2calc_data.md2   = MODEL.get_md2();
   gm2calc_data.ml2   = MODEL.get_ml2();
   gm2calc_data.me2   = MODEL.get_me2();
   gm2calc_data.Au    = div_safe(MODEL.get_TYu(), MODEL.get_Yu());
   gm2calc_data.Ad    = div_safe(MODEL.get_TYd(), MODEL.get_Yd());
   gm2calc_data.Ae    = div_safe(MODEL.get_TYe(), MODEL.get_Ye());

   observables.AMU = MSSMNoFV_a_muon::calculate_a_muon(MODEL);
   observables.AMUGM2CALC = gm2calc_calculate_amu(gm2calc_data);
   observables.AMUGM2CALCUNCERTAINTY = gm2calc_calculate_amu_uncertainty(gm2calc_data);

   return observables;
}

} // namespace flexiblesusy
