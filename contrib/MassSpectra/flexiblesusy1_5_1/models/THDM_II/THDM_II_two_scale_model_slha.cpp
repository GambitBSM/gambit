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

// File generated at Wed 29 Mar 2017 15:36:56

/**
 * @file THDM_II_two_scale_model_slha.cpp
 * @brief THDM_II model class wrapper for SLHA conversion
 */

#include "THDM_II_two_scale_model_slha.hpp"
#include "slha_io.hpp"
#include "ckm.hpp"
#include "pmns.hpp"

namespace flexiblesusy {

#define CLASSNAME THDM_II_slha<Two_scale>
#define LOCALPHYSICAL(p) physical.p

CLASSNAME::THDM_II_slha(const THDM_II_input_parameters& input_)
   : THDM_II<Two_scale>(input_)
   , physical_slha()
   , ckm(Eigen::Matrix<std::complex<double>,3,3>::Identity())
   , pmns(Eigen::Matrix<std::complex<double>,3,3>::Identity())
   , convert_masses_to_slha(true)
{
}

/**
 * Copy constructor.  Copies from base class (two-scale model class in
 * BPMZ convention) and converts parameters to SLHA.
 *
 * @param model_ model class in BPMZ convention
 * @param do_convert_masses_to_slha whether to convert majorana
 *    fermion masses to SLHA convention (allow them to be negative)
 */
CLASSNAME::THDM_II_slha(const THDM_II<Two_scale>& model_,
                            bool do_convert_masses_to_slha)
   : THDM_II<Two_scale>(model_)
   , convert_masses_to_slha(do_convert_masses_to_slha)
{
   convert_to_slha();
}

CLASSNAME::~THDM_II_slha()
{
}

void CLASSNAME::clear()
{
   THDM_II<Two_scale>::clear();
   physical_slha.clear();
}

void CLASSNAME::calculate_spectrum()
{
   THDM_II<Two_scale>::calculate_spectrum();
   convert_to_slha();
}

void CLASSNAME::convert_to_slha()
{
   physical_slha = get_physical();

   if (convert_masses_to_slha)
      physical_slha.convert_to_slha();

   convert_yukawa_couplings_to_slha();
   calculate_ckm_matrix();
   calculate_pmns_matrix();
   convert_trilinear_couplings_to_slha();
   convert_soft_squared_masses_to_slha();
}

void CLASSNAME::calculate_ckm_matrix()
{
   ckm = Vu_slha * Vd_slha.adjoint();
   CKM_parameters::to_pdg_convention(ckm, Vu_slha, Vd_slha, Uu_slha, Ud_slha);

}

void CLASSNAME::calculate_pmns_matrix()
{
   pmns << 1, 0, 0, 0, 1, 0, 0, 0, 1;

}

/**
 * Convert Yukawa couplings to SLHA convention
 */
void CLASSNAME::convert_yukawa_couplings_to_slha()
{
   fs_svd(Yu, Yu_slha, Uu_slha, Vu_slha);
   fs_svd(Yd, Yd_slha, Ud_slha, Vd_slha);
   fs_svd(Ye, Ye_slha, Ue_slha, Ve_slha);

}

/**
 * Convert trilinear couplings to SLHA convention
 */
void CLASSNAME::convert_trilinear_couplings_to_slha()
{

}

/**
 * Convert trilinear couplings to SLHA convention
 */
void CLASSNAME::convert_soft_squared_masses_to_slha()
{

}

const THDM_II_physical& CLASSNAME::get_physical_slha() const
{
   return physical_slha;
}

THDM_II_physical& CLASSNAME::get_physical_slha()
{
   return physical_slha;
}

void CLASSNAME::print(std::ostream& ostr) const
{
   THDM_II<Two_scale>::print(ostr);

   ostr << "----------------------------------------\n"
           "SLHA convention:\n"
           "----------------------------------------\n";
   physical_slha.print(ostr);
}

void CLASSNAME::set_convert_masses_to_slha(bool flag)
{
   convert_masses_to_slha = flag;
}

std::ostream& operator<<(std::ostream& ostr, const THDM_II_slha<Two_scale>& model)
{
   model.print(ostr);
   return ostr;
}

} // namespace flexiblesusy
