#ifndef __wrapper_MSSMNoFV_onshell_soft_parameters_def_gm2calc_1_3_0_hpp__
#define __wrapper_MSSMNoFV_onshell_soft_parameters_def_gm2calc_1_3_0_hpp__

#include <Eigen/Core>
#include <ostream>
#include "wrapper_MSSMNoFV_onshell_susy_parameters_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      // Member functions: 
      inline void MSSMNoFV_onshell_soft_parameters::print(std::ostream& arg_1) const
      {
         get_BEptr()->print(arg_1);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::clear()
      {
         get_BEptr()->clear();
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_TYd(const Eigen::Matrix<double, 3, 3, 0>& TYd_)
      {
         get_BEptr()->set_TYd(TYd_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_TYd(int i, int k, double value)
      {
         get_BEptr()->set_TYd(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_TYe(const Eigen::Matrix<double, 3, 3, 0>& TYe_)
      {
         get_BEptr()->set_TYe(TYe_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_TYe(int i, int k, double value)
      {
         get_BEptr()->set_TYe(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_TYu(const Eigen::Matrix<double, 3, 3, 0>& TYu_)
      {
         get_BEptr()->set_TYu(TYu_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_TYu(int i, int k, double value)
      {
         get_BEptr()->set_TYu(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_BMu(double BMu_)
      {
         get_BEptr()->set_BMu(BMu_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_mq2(const Eigen::Matrix<double, 3, 3, 0>& mq2_)
      {
         get_BEptr()->set_mq2(mq2_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_mq2(int i, int k, double value)
      {
         get_BEptr()->set_mq2(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_ml2(const Eigen::Matrix<double, 3, 3, 0>& ml2_)
      {
         get_BEptr()->set_ml2(ml2_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_ml2(int i, int k, double value)
      {
         get_BEptr()->set_ml2(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_mHd2(double mHd2_)
      {
         get_BEptr()->set_mHd2(mHd2_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_mHu2(double mHu2_)
      {
         get_BEptr()->set_mHu2(mHu2_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_md2(const Eigen::Matrix<double, 3, 3, 0>& md2_)
      {
         get_BEptr()->set_md2(md2_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_md2(int i, int k, double value)
      {
         get_BEptr()->set_md2(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_mu2(const Eigen::Matrix<double, 3, 3, 0>& mu2_)
      {
         get_BEptr()->set_mu2(mu2_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_mu2(int i, int k, double value)
      {
         get_BEptr()->set_mu2(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_me2(const Eigen::Matrix<double, 3, 3, 0>& me2_)
      {
         get_BEptr()->set_me2(me2_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_me2(int i, int k, double value)
      {
         get_BEptr()->set_me2(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_MassB(double MassB_)
      {
         get_BEptr()->set_MassB(MassB_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_MassWB(double MassWB_)
      {
         get_BEptr()->set_MassWB(MassWB_);
      }
      
      inline void MSSMNoFV_onshell_soft_parameters::set_MassG(double MassG_)
      {
         get_BEptr()->set_MassG(MassG_);
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_soft_parameters::get_TYd() const
      {
         return get_BEptr()->get_TYd();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_TYd(int i, int k) const
      {
         return get_BEptr()->get_TYd(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_soft_parameters::get_TYe() const
      {
         return get_BEptr()->get_TYe();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_TYe(int i, int k) const
      {
         return get_BEptr()->get_TYe(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_soft_parameters::get_TYu() const
      {
         return get_BEptr()->get_TYu();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_TYu(int i, int k) const
      {
         return get_BEptr()->get_TYu(i, k);
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_BMu() const
      {
         return get_BEptr()->get_BMu();
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_soft_parameters::get_mq2() const
      {
         return get_BEptr()->get_mq2();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_mq2(int i, int k) const
      {
         return get_BEptr()->get_mq2(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_soft_parameters::get_ml2() const
      {
         return get_BEptr()->get_ml2();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_ml2(int i, int k) const
      {
         return get_BEptr()->get_ml2(i, k);
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_mHd2() const
      {
         return get_BEptr()->get_mHd2();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_mHu2() const
      {
         return get_BEptr()->get_mHu2();
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_soft_parameters::get_md2() const
      {
         return get_BEptr()->get_md2();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_md2(int i, int k) const
      {
         return get_BEptr()->get_md2(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_soft_parameters::get_mu2() const
      {
         return get_BEptr()->get_mu2();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_mu2(int i, int k) const
      {
         return get_BEptr()->get_mu2(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_soft_parameters::get_me2() const
      {
         return get_BEptr()->get_me2();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_me2(int i, int k) const
      {
         return get_BEptr()->get_me2(i, k);
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_MassB() const
      {
         return get_BEptr()->get_MassB();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_MassWB() const
      {
         return get_BEptr()->get_MassWB();
      }
      
      inline double MSSMNoFV_onshell_soft_parameters::get_MassG() const
      {
         return get_BEptr()->get_MassG();
      }
      
      
      // Wrappers for original constructors: 
      inline MSSMNoFV_onshell_soft_parameters::MSSMNoFV_onshell_soft_parameters() :
         MSSMNoFV_onshell_susy_parameters(__factory0())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      inline MSSMNoFV_onshell_soft_parameters::MSSMNoFV_onshell_soft_parameters(const gm2calc::MSSMNoFV_onshell_susy_parameters& arg_1, const Eigen::Matrix<double, 3, 3, 0>& TYd_, const Eigen::Matrix<double, 3, 3, 0>& TYe_, const Eigen::Matrix<double, 3, 3, 0>& TYu_, double BMu_, const Eigen::Matrix<double, 3, 3, 0>& mq2_, const Eigen::Matrix<double, 3, 3, 0>& ml2_, double mHd2_, double mHu2_, const Eigen::Matrix<double, 3, 3, 0>& md2_, const Eigen::Matrix<double, 3, 3, 0>& mu2_, const Eigen::Matrix<double, 3, 3, 0>& me2_, double MassB_, double MassWB_, double MassG_) :
         MSSMNoFV_onshell_susy_parameters(__factory1(arg_1, TYd_, TYe_, TYu_, BMu_, mq2_, ml2_, mHd2_, mHu2_, md2_, mu2_, me2_, MassB_, MassWB_, MassG_))
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Special pointer-based constructor: 
      inline MSSMNoFV_onshell_soft_parameters::MSSMNoFV_onshell_soft_parameters(Abstract_MSSMNoFV_onshell_soft_parameters* in) :
         MSSMNoFV_onshell_susy_parameters(in)
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Copy constructor: 
      inline MSSMNoFV_onshell_soft_parameters::MSSMNoFV_onshell_soft_parameters(const MSSMNoFV_onshell_soft_parameters& in) :
         MSSMNoFV_onshell_susy_parameters(in.get_BEptr()->pointer_copy__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Assignment operator: 
      inline MSSMNoFV_onshell_soft_parameters& MSSMNoFV_onshell_soft_parameters::operator=(const MSSMNoFV_onshell_soft_parameters& in)
      {
         if (this != &in)
         {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
         }
         return *this;
      }
      
      
      // Destructor: 
      inline MSSMNoFV_onshell_soft_parameters::~MSSMNoFV_onshell_soft_parameters()
      {
         if (get_BEptr() != 0)
         {
            get_BEptr()->set_delete_wrapper(false);
            if (can_delete_BEptr())
            {
               delete BEptr;
               BEptr = 0;
            }
         }
         set_delete_BEptr(false);
      }
      
      // Returns correctly casted pointer to Abstract class: 
      inline Abstract_MSSMNoFV_onshell_soft_parameters* gm2calc::MSSMNoFV_onshell_soft_parameters::get_BEptr() const
      {
         return dynamic_cast<Abstract_MSSMNoFV_onshell_soft_parameters*>(BEptr);
      }
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_soft_parameters_def_gm2calc_1_3_0_hpp__ */
