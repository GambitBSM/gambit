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

/**
 * @file MSSMNoFVatMGUT_model_slha.hpp
 * @brief contains wrapper class for model class in SLHA convention
 */

// File generated at Thu 10 May 2018 14:51:53

#ifndef MSSMNoFVatMGUT_SLHA_H
#define MSSMNoFVatMGUT_SLHA_H

#include "MSSMNoFVatMGUT_input_parameters.hpp"
#include "MSSMNoFVatMGUT_mass_eigenstates.hpp"
#include "MSSMNoFVatMGUT_physical.hpp"

#include "ckm.hpp"
#include "linalg2.hpp"
#include "pmns.hpp"
#include "slha_io.hpp"
#include "wrappers.hpp"

#define LOCALPHYSICAL(p) physical.p
#define MODELPARAMETER(p) this->p
#define PHYSICAL_SLHA(p) physical_slha.p
#define PHYSICAL_SLHA_REAL(p) Re(physical_slha.p)

namespace flexiblesusy {

/**
 * @class MSSMNoFVatMGUT_slha<T>
 * @brief model class wrapper in SLHA convention
 *
 * @tparam Model model class to wrap
 */

template <class Model>
class MSSMNoFVatMGUT_slha : public Model {
public:
   explicit MSSMNoFVatMGUT_slha(const MSSMNoFVatMGUT_input_parameters& input_ = MSSMNoFVatMGUT_input_parameters());
   explicit MSSMNoFVatMGUT_slha(const Model&, bool do_convert_masses_to_slha = true);
   MSSMNoFVatMGUT_slha(const MSSMNoFVatMGUT_slha&) = default;
   MSSMNoFVatMGUT_slha(MSSMNoFVatMGUT_slha&&) = default;
   virtual ~MSSMNoFVatMGUT_slha() = default;
   MSSMNoFVatMGUT_slha& operator=(const MSSMNoFVatMGUT_slha&) = default;
   MSSMNoFVatMGUT_slha& operator=(MSSMNoFVatMGUT_slha&&) = default;

   virtual void clear() override;
   void convert_to_slha(); ///< converts pole masses and couplings to SLHA convention
   const Eigen::Matrix<std::complex<double>,3,3>& get_ckm_matrix() const { return ckm; }
   const Eigen::Matrix<std::complex<double>,3,3>& get_pmns_matrix() const { return pmns; }
   const MSSMNoFVatMGUT_physical& get_physical_slha() const; ///< returns pole masses to SLHA convention
   MSSMNoFVatMGUT_physical& get_physical_slha(); ///< returns pole masses to SLHA convention
   void set_convert_masses_to_slha(bool); ///< allow/disallow for negative majoran fermion masses

   // interface functions
   virtual void calculate_spectrum() override;
   virtual void print(std::ostream&) const override;

   double get_MVG_pole_slha() const { return PHYSICAL_SLHA(MVG); }
   double get_MGlu_pole_slha() const { return PHYSICAL_SLHA(MGlu); }
   double get_MFd_pole_slha() const { return PHYSICAL_SLHA(MFd); }
   double get_MFs_pole_slha() const { return PHYSICAL_SLHA(MFs); }
   double get_MFb_pole_slha() const { return PHYSICAL_SLHA(MFb); }
   double get_MFu_pole_slha() const { return PHYSICAL_SLHA(MFu); }
   double get_MFc_pole_slha() const { return PHYSICAL_SLHA(MFc); }
   double get_MFt_pole_slha() const { return PHYSICAL_SLHA(MFt); }
   double get_MFve_pole_slha() const { return PHYSICAL_SLHA(MFve); }
   double get_MFvm_pole_slha() const { return PHYSICAL_SLHA(MFvm); }
   double get_MFvt_pole_slha() const { return PHYSICAL_SLHA(MFvt); }
   double get_MFe_pole_slha() const { return PHYSICAL_SLHA(MFe); }
   double get_MFm_pole_slha() const { return PHYSICAL_SLHA(MFm); }
   double get_MFtau_pole_slha() const { return PHYSICAL_SLHA(MFtau); }
   double get_MSveL_pole_slha() const { return PHYSICAL_SLHA(MSveL); }
   double get_MSvmL_pole_slha() const { return PHYSICAL_SLHA(MSvmL); }
   double get_MSvtL_pole_slha() const { return PHYSICAL_SLHA(MSvtL); }
   const Eigen::Array<double,2,1>& get_MSd_pole_slha() const { return PHYSICAL_SLHA(MSd); }
   double get_MSd_pole_slha(int i) const { return PHYSICAL_SLHA(MSd(i)); }
   const Eigen::Array<double,2,1>& get_MSu_pole_slha() const { return PHYSICAL_SLHA(MSu); }
   double get_MSu_pole_slha(int i) const { return PHYSICAL_SLHA(MSu(i)); }
   const Eigen::Array<double,2,1>& get_MSe_pole_slha() const { return PHYSICAL_SLHA(MSe); }
   double get_MSe_pole_slha(int i) const { return PHYSICAL_SLHA(MSe(i)); }
   const Eigen::Array<double,2,1>& get_MSm_pole_slha() const { return PHYSICAL_SLHA(MSm); }
   double get_MSm_pole_slha(int i) const { return PHYSICAL_SLHA(MSm(i)); }
   const Eigen::Array<double,2,1>& get_MStau_pole_slha() const { return PHYSICAL_SLHA(MStau); }
   double get_MStau_pole_slha(int i) const { return PHYSICAL_SLHA(MStau(i)); }
   const Eigen::Array<double,2,1>& get_MSs_pole_slha() const { return PHYSICAL_SLHA(MSs); }
   double get_MSs_pole_slha(int i) const { return PHYSICAL_SLHA(MSs(i)); }
   const Eigen::Array<double,2,1>& get_MSc_pole_slha() const { return PHYSICAL_SLHA(MSc); }
   double get_MSc_pole_slha(int i) const { return PHYSICAL_SLHA(MSc(i)); }
   const Eigen::Array<double,2,1>& get_MSb_pole_slha() const { return PHYSICAL_SLHA(MSb); }
   double get_MSb_pole_slha(int i) const { return PHYSICAL_SLHA(MSb(i)); }
   const Eigen::Array<double,2,1>& get_MSt_pole_slha() const { return PHYSICAL_SLHA(MSt); }
   double get_MSt_pole_slha(int i) const { return PHYSICAL_SLHA(MSt(i)); }
   const Eigen::Array<double,2,1>& get_Mhh_pole_slha() const { return PHYSICAL_SLHA(Mhh); }
   double get_Mhh_pole_slha(int i) const { return PHYSICAL_SLHA(Mhh(i)); }
   const Eigen::Array<double,2,1>& get_MAh_pole_slha() const { return PHYSICAL_SLHA(MAh); }
   double get_MAh_pole_slha(int i) const { return PHYSICAL_SLHA(MAh(i)); }
   const Eigen::Array<double,2,1>& get_MHpm_pole_slha() const { return PHYSICAL_SLHA(MHpm); }
   double get_MHpm_pole_slha(int i) const { return PHYSICAL_SLHA(MHpm(i)); }
   const Eigen::Array<double,4,1>& get_MChi_pole_slha() const { return PHYSICAL_SLHA(MChi); }
   double get_MChi_pole_slha(int i) const { return PHYSICAL_SLHA(MChi(i)); }
   const Eigen::Array<double,2,1>& get_MCha_pole_slha() const { return PHYSICAL_SLHA(MCha); }
   double get_MCha_pole_slha(int i) const { return PHYSICAL_SLHA(MCha(i)); }
   double get_MVWm_pole_slha() const { return PHYSICAL_SLHA(MVWm); }
   double get_MVP_pole_slha() const { return PHYSICAL_SLHA(MVP); }
   double get_MVZ_pole_slha() const { return PHYSICAL_SLHA(MVZ); }

   const Eigen::Matrix<double,2,2>& get_ZD_pole_slha() const { return PHYSICAL_SLHA(ZD); }
   double get_ZD_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZD(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZU_pole_slha() const { return PHYSICAL_SLHA(ZU); }
   double get_ZU_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZU(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZE_pole_slha() const { return PHYSICAL_SLHA(ZE); }
   double get_ZE_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZE(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZM_pole_slha() const { return PHYSICAL_SLHA(ZM); }
   double get_ZM_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZM(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZTau_pole_slha() const { return PHYSICAL_SLHA(ZTau); }
   double get_ZTau_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZTau(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZS_pole_slha() const { return PHYSICAL_SLHA(ZS); }
   double get_ZS_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZS(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZC_pole_slha() const { return PHYSICAL_SLHA(ZC); }
   double get_ZC_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZC(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZB_pole_slha() const { return PHYSICAL_SLHA(ZB); }
   double get_ZB_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZB(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZT_pole_slha() const { return PHYSICAL_SLHA(ZT); }
   double get_ZT_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZT(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZH_pole_slha() const { return PHYSICAL_SLHA(ZH); }
   double get_ZH_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZH(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZA_pole_slha() const { return PHYSICAL_SLHA(ZA); }
   double get_ZA_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZA(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZP_pole_slha() const { return PHYSICAL_SLHA(ZP); }
   double get_ZP_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZP(i,k)); }
   const Eigen::Matrix<std::complex<double>,4,4>& get_ZN_pole_slha() const { return PHYSICAL_SLHA(ZN); }
   double get_ZN_pole_slha(int i, int k) const { return PHYSICAL_SLHA_REAL(ZN(i,k)); }
   const Eigen::Matrix<std::complex<double>,2,2>& get_UM_pole_slha() const { return PHYSICAL_SLHA(UM); }
   double get_UM_pole_slha(int i, int k) const { return PHYSICAL_SLHA_REAL(UM(i,k)); }
   const Eigen::Matrix<std::complex<double>,2,2>& get_UP_pole_slha() const { return PHYSICAL_SLHA(UP); }
   double get_UP_pole_slha(int i, int k) const { return PHYSICAL_SLHA_REAL(UP(i,k)); }
   const Eigen::Matrix<double,2,2>& get_ZZ_pole_slha() const { return PHYSICAL_SLHA(ZZ); }
   double get_ZZ_pole_slha(int i, int k) const { return PHYSICAL_SLHA(ZZ(i,k)); }

   const Eigen::Array<double,3,1>& get_Yu_slha() const { return Yu_slha; }
   double get_Yu_slha(int i) const { return Yu_slha(i); }
   const Eigen::Array<double,3,1>& get_Yd_slha() const { return Yd_slha; }
   double get_Yd_slha(int i) const { return Yd_slha(i); }
   const Eigen::Array<double,3,1>& get_Ye_slha() const { return Ye_slha; }
   double get_Ye_slha(int i) const { return Ye_slha(i); }

   const Eigen::Matrix<double,3,3>& get_TYu_slha() const { return TYu_slha; }
   double get_TYu_slha(int i, int k) const { return TYu_slha(i,k); }
   const Eigen::Matrix<double,3,3>& get_TYd_slha() const { return TYd_slha; }
   double get_TYd_slha(int i, int k) const { return TYd_slha(i,k); }
   const Eigen::Matrix<double,3,3>& get_TYe_slha() const { return TYe_slha; }
   double get_TYe_slha(int i, int k) const { return TYe_slha(i,k); }

   const Eigen::Matrix<double,3,3>& get_mq2_slha() const { return mq2_slha; }
   double get_mq2_slha(int i, int k) const { return mq2_slha(i,k); }
   const Eigen::Matrix<double,3,3>& get_mu2_slha() const { return mu2_slha; }
   double get_mu2_slha(int i, int k) const { return mu2_slha(i,k); }
   const Eigen::Matrix<double,3,3>& get_md2_slha() const { return md2_slha; }
   double get_md2_slha(int i, int k) const { return md2_slha(i,k); }
   const Eigen::Matrix<double,3,3>& get_ml2_slha() const { return ml2_slha; }
   double get_ml2_slha(int i, int k) const { return ml2_slha(i,k); }
   const Eigen::Matrix<double,3,3>& get_me2_slha() const { return me2_slha; }
   double get_me2_slha(int i, int k) const { return me2_slha(i,k); }



private:
   MSSMNoFVatMGUT_physical physical_slha{}; ///< contains the pole masses and mixings in slha convention
   Eigen::Matrix<std::complex<double>,3,3> ckm{Eigen::Matrix<std::complex<double>,3,3>::Identity()};
   Eigen::Matrix<std::complex<double>,3,3> pmns{Eigen::Matrix<std::complex<double>,3,3>::Identity()};
   bool convert_masses_to_slha{true};    ///< allow/disallow for negative majoran fermion masses
   Eigen::Array<double,3,1> Yu_slha{Eigen::Array<double,3,1>::Zero()};
   Eigen::Array<double,3,1> Yd_slha{Eigen::Array<double,3,1>::Zero()};
   Eigen::Array<double,3,1> Ye_slha{Eigen::Array<double,3,1>::Zero()};


   Eigen::Matrix<double,3,3> TYu_slha{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> TYd_slha{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> TYe_slha{Eigen::Matrix<double,3,3>::Zero()};

   Eigen::Matrix<double,3,3> mq2_slha{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> mu2_slha{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> md2_slha{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> ml2_slha{Eigen::Matrix<double,3,3>::Zero()};
   Eigen::Matrix<double,3,3> me2_slha{Eigen::Matrix<double,3,3>::Zero()};


   void calculate_ckm_matrix();
   void calculate_pmns_matrix();
   void convert_yukawa_couplings_to_slha();
   void convert_trilinear_couplings_to_slha();
   void convert_soft_squared_masses_to_slha();
};

template <class Model>
MSSMNoFVatMGUT_slha<Model>::MSSMNoFVatMGUT_slha(const MSSMNoFVatMGUT_input_parameters& input_)
   : Model(input_)
{
}

/**
 * Copy constructor.  Copies from base class (model class in
 * BPMZ convention) and converts parameters to SLHA.
 *
 * @param model_ model class in BPMZ convention
 * @param do_convert_masses_to_slha whether to convert majorana
 *    fermion masses to SLHA convention (allow them to be negative)
 */
template <class Model>
MSSMNoFVatMGUT_slha<Model>::MSSMNoFVatMGUT_slha(const Model& model_,
                            bool do_convert_masses_to_slha)
   : Model(model_)
   , convert_masses_to_slha(do_convert_masses_to_slha)
{
   convert_to_slha();
}

template <class Model>
void MSSMNoFVatMGUT_slha<Model>::clear()
{
   Model::clear();
   physical_slha.clear();
}

template <class Model>
void MSSMNoFVatMGUT_slha<Model>::calculate_spectrum()
{
   Model::calculate_spectrum();
   convert_to_slha();
}

template <class Model>
void MSSMNoFVatMGUT_slha<Model>::convert_to_slha()
{
   physical_slha = this->get_physical();

   if (convert_masses_to_slha)
      physical_slha.convert_to_slha();

   convert_yukawa_couplings_to_slha();
   calculate_ckm_matrix();
   calculate_pmns_matrix();
   convert_trilinear_couplings_to_slha();
   convert_soft_squared_masses_to_slha();
}

template <class Model>
void MSSMNoFVatMGUT_slha<Model>::calculate_ckm_matrix()
{

}

template <class Model>
void MSSMNoFVatMGUT_slha<Model>::calculate_pmns_matrix()
{
   pmns << 1, 0, 0, 0, 1, 0, 0, 0, 1;

}

/**
 * Convert Yukawa couplings to SLHA convention
 */
template <class Model>
void MSSMNoFVatMGUT_slha<Model>::convert_yukawa_couplings_to_slha()
{
   Yu_slha = MODELPARAMETER(Yu).diagonal().real();
   Yd_slha = MODELPARAMETER(Yd).diagonal().real();
   Ye_slha = MODELPARAMETER(Ye).diagonal().real();

}

/**
 * Convert trilinear couplings to SLHA convention
 */
template <class Model>
void MSSMNoFVatMGUT_slha<Model>::convert_trilinear_couplings_to_slha()
{
   TYu_slha = (MODELPARAMETER(TYu)).real();
   TYd_slha = (MODELPARAMETER(TYd)).real();
   TYe_slha = (MODELPARAMETER(TYe)).real();

}

/**
 * Convert soft-breaking squared mass parameters to SLHA convention
 */
template <class Model>
void MSSMNoFVatMGUT_slha<Model>::convert_soft_squared_masses_to_slha()
{
   mq2_slha = (MODELPARAMETER(mq2)).real();
   mu2_slha = (MODELPARAMETER(mu2)).real();
   md2_slha = (MODELPARAMETER(md2)).real();
   ml2_slha = (MODELPARAMETER(ml2)).real();
   me2_slha = (MODELPARAMETER(me2)).real();

}

template <class Model>
const MSSMNoFVatMGUT_physical& MSSMNoFVatMGUT_slha<Model>::get_physical_slha() const
{
   return physical_slha;
}

template <class Model>
MSSMNoFVatMGUT_physical& MSSMNoFVatMGUT_slha<Model>::get_physical_slha()
{
   return physical_slha;
}

template <class Model>
void MSSMNoFVatMGUT_slha<Model>::print(std::ostream& ostr) const
{
   Model::print(ostr);

   ostr << "----------------------------------------\n"
           "SLHA convention:\n"
           "----------------------------------------\n";
   physical_slha.print(ostr);
}

template <class Model>
void MSSMNoFVatMGUT_slha<Model>::set_convert_masses_to_slha(bool flag)
{
   convert_masses_to_slha = flag;
}

template <class Model>
std::ostream& operator<<(std::ostream& ostr, const MSSMNoFVatMGUT_slha<Model>& model)
{
   model.print(ostr);
   return ostr;
}

} // namespace flexiblesusy

#undef LOCALPHYSICAL
#undef MODELPARAMETER
#undef PHYSICAL_SLHA
#undef PHYSICAL_SLHA_REAL

#endif
