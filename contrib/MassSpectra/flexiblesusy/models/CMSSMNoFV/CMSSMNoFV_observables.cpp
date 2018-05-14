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

// File generated at Thu 10 May 2018 14:56:11

#include "CMSSMNoFV_observables.hpp"
#include "CMSSMNoFV_mass_eigenstates.hpp"
#include "CMSSMNoFV_a_muon.hpp"
#include "CMSSMNoFV_edm.hpp"
#include "CMSSMNoFV_effective_couplings.hpp"
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

const int CMSSMNoFV_observables::NUMBER_OF_OBSERVABLES;

CMSSMNoFV_observables::CMSSMNoFV_observables()
   : a_muon(0)
   , a_muon_uncertainty(0)
   , a_muon_gm2calc(0)
   , a_muon_gm2calc_uncertainty(0)
   , eff_cp_higgs_photon_photon(Eigen::Array<std::complex<double>,2,1>::Zero())
   , eff_cp_higgs_gluon_gluon(Eigen::Array<std::complex<double>,2,1>::Zero())
   , eff_cp_pseudoscalar_photon_photon(0)
   , eff_cp_pseudoscalar_gluon_gluon(0)

{
}

Eigen::ArrayXd CMSSMNoFV_observables::get() const
{
   Eigen::ArrayXd vec(CMSSMNoFV_observables::NUMBER_OF_OBSERVABLES);

   vec(0) = a_muon;
   vec(1) = a_muon_uncertainty;
   vec(2) = a_muon_gm2calc;
   vec(3) = a_muon_gm2calc_uncertainty;
   vec(4) = Re(eff_cp_higgs_photon_photon(0));
   vec(5) = Im(eff_cp_higgs_photon_photon(0));
   vec(6) = Re(eff_cp_higgs_photon_photon(1));
   vec(7) = Im(eff_cp_higgs_photon_photon(1));
   vec(8) = Re(eff_cp_higgs_gluon_gluon(0));
   vec(9) = Im(eff_cp_higgs_gluon_gluon(0));
   vec(10) = Re(eff_cp_higgs_gluon_gluon(1));
   vec(11) = Im(eff_cp_higgs_gluon_gluon(1));
   vec(12) = Re(eff_cp_pseudoscalar_photon_photon);
   vec(13) = Im(eff_cp_pseudoscalar_photon_photon);
   vec(14) = Re(eff_cp_pseudoscalar_gluon_gluon);
   vec(15) = Im(eff_cp_pseudoscalar_gluon_gluon);

   return vec;
}

std::vector<std::string> CMSSMNoFV_observables::get_names()
{
   std::vector<std::string> names(CMSSMNoFV_observables::NUMBER_OF_OBSERVABLES);

   names[0] = "a_muon";
   names[1] = "a_muon_uncertainty";
   names[2] = "a_muon_gm2calc";
   names[3] = "a_muon_gm2calc_uncertainty";
   names[4] = "Re(eff_cp_higgs_photon_photon(0))";
   names[5] = "Im(eff_cp_higgs_photon_photon(0))";
   names[6] = "Re(eff_cp_higgs_photon_photon(1))";
   names[7] = "Im(eff_cp_higgs_photon_photon(1))";
   names[8] = "Re(eff_cp_higgs_gluon_gluon(0))";
   names[9] = "Im(eff_cp_higgs_gluon_gluon(0))";
   names[10] = "Re(eff_cp_higgs_gluon_gluon(1))";
   names[11] = "Im(eff_cp_higgs_gluon_gluon(1))";
   names[12] = "Re(eff_cp_pseudoscalar_photon_photon)";
   names[13] = "Im(eff_cp_pseudoscalar_photon_photon)";
   names[14] = "Re(eff_cp_pseudoscalar_gluon_gluon)";
   names[15] = "Im(eff_cp_pseudoscalar_gluon_gluon)";

   return names;
}

void CMSSMNoFV_observables::clear()
{
   a_muon = 0.;
   a_muon_uncertainty = 0.;
   a_muon_gm2calc = 0.;
   a_muon_gm2calc_uncertainty = 0.;
   eff_cp_higgs_photon_photon = Eigen::Array<std::complex<double>,2,1>::Zero();
   eff_cp_higgs_gluon_gluon = Eigen::Array<std::complex<double>,2,1>::Zero();
   eff_cp_pseudoscalar_photon_photon = std::complex<double>(0.,0.);
   eff_cp_pseudoscalar_gluon_gluon = std::complex<double>(0.,0.);

}

void CMSSMNoFV_observables::set(const Eigen::ArrayXd& vec)
{
   assert(vec.rows() == CMSSMNoFV_observables::NUMBER_OF_OBSERVABLES);

   a_muon = vec(0);
   a_muon_uncertainty = vec(1);
   a_muon_gm2calc = vec(2);
   a_muon_gm2calc_uncertainty = vec(3);
   eff_cp_higgs_photon_photon(0) = std::complex<double>(vec(4), vec(5));
   eff_cp_higgs_photon_photon(1) = std::complex<double>(vec(6), vec(7));
   eff_cp_higgs_gluon_gluon(0) = std::complex<double>(vec(8), vec(9));
   eff_cp_higgs_gluon_gluon(1) = std::complex<double>(vec(10), vec(11));
   eff_cp_pseudoscalar_photon_photon = std::complex<double>(vec(12), vec(13));
   eff_cp_pseudoscalar_gluon_gluon = std::complex<double>(vec(14), vec(15));

}

CMSSMNoFV_observables calculate_observables(const CMSSMNoFV_mass_eigenstates& model,
                                              const softsusy::QedQcd& qedqcd,
                                              const Physical_input& physical_input,
                                              double scale)
{
   auto model_at_scale = model;

   if (scale > 0.)
      model_at_scale.run_to(scale);

   return calculate_observables(model_at_scale, qedqcd, physical_input);
}

CMSSMNoFV_observables calculate_observables(const CMSSMNoFV_mass_eigenstates& model,
                                              const softsusy::QedQcd& qedqcd,
                                              const Physical_input& physical_input)
{
   CMSSMNoFV_observables observables;

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
   CMSSMNoFV_effective_couplings effective_couplings(model, qedqcd, physical_input);
   effective_couplings.calculate_effective_couplings();

   observables.AMU = CMSSMNoFV_a_muon::calculate_a_muon(MODEL);
   observables.AMUUNCERTAINTY = CMSSMNoFV_a_muon::calculate_a_muon_uncertainty(MODEL);
   observables.AMUGM2CALC = gm2calc_calculate_amu(gm2calc_data);
   observables.AMUGM2CALCUNCERTAINTY = gm2calc_calculate_amu_uncertainty(gm2calc_data);
   observables.EFFCPHIGGSPHOTONPHOTON(0) = effective_couplings.get_eff_CphhVPVP(0);
   observables.EFFCPHIGGSPHOTONPHOTON(1) = effective_couplings.get_eff_CphhVPVP(1);
   observables.EFFCPHIGGSGLUONGLUON(0) = effective_couplings.get_eff_CphhVGVG(0);
   observables.EFFCPHIGGSGLUONGLUON(1) = effective_couplings.get_eff_CphhVGVG(1);
   observables.EFFCPPSEUDOSCALARPHOTONPHOTON = effective_couplings.get_eff_CpAhVPVP(1);
   observables.EFFCPPSEUDOSCALARGLUONGLUON = effective_couplings.get_eff_CpAhVGVG(1);

   return observables;
}

} // namespace flexiblesusy
