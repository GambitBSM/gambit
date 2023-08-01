#ifndef __wrapper_MSSMNoFV_onshell_susy_parameters_def_gm2calc_1_3_0_hpp__
#define __wrapper_MSSMNoFV_onshell_susy_parameters_def_gm2calc_1_3_0_hpp__

#include <Eigen/Core>
#include <ostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      // Member functions: 
      inline void MSSMNoFV_onshell_susy_parameters::print(std::ostream& arg_1) const
      {
         get_BEptr()->print(arg_1);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::clear()
      {
         get_BEptr()->clear();
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_scale(double s)
      {
         get_BEptr()->set_scale(s);
      }
      
      inline double MSSMNoFV_onshell_susy_parameters::get_scale() const
      {
         return get_BEptr()->get_scale();
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_Yd(const Eigen::Matrix<double, 3, 3, 0>& Yd_)
      {
         get_BEptr()->set_Yd(Yd_);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_Yd(int i, int k, double value)
      {
         get_BEptr()->set_Yd(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_Ye(const Eigen::Matrix<double, 3, 3, 0>& Ye_)
      {
         get_BEptr()->set_Ye(Ye_);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_Ye(int i, int k, double value)
      {
         get_BEptr()->set_Ye(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_Yu(const Eigen::Matrix<double, 3, 3, 0>& Yu_)
      {
         get_BEptr()->set_Yu(Yu_);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_Yu(int i, int k, double value)
      {
         get_BEptr()->set_Yu(i, k, value);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_Mu(double Mu_)
      {
         get_BEptr()->set_Mu(Mu_);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_g1(double g1_)
      {
         get_BEptr()->set_g1(g1_);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_g2(double g2_)
      {
         get_BEptr()->set_g2(g2_);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_g3(double g3_)
      {
         get_BEptr()->set_g3(g3_);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_vd(double vd_)
      {
         get_BEptr()->set_vd(vd_);
      }
      
      inline void MSSMNoFV_onshell_susy_parameters::set_vu(double vu_)
      {
         get_BEptr()->set_vu(vu_);
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_susy_parameters::get_Yd() const
      {
         return get_BEptr()->get_Yd();
      }
      
      inline double MSSMNoFV_onshell_susy_parameters::get_Yd(int i, int k) const
      {
         return get_BEptr()->get_Yd(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_susy_parameters::get_Ye() const
      {
         return get_BEptr()->get_Ye();
      }
      
      inline double MSSMNoFV_onshell_susy_parameters::get_Ye(int i, int k) const
      {
         return get_BEptr()->get_Ye(i, k);
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0>& MSSMNoFV_onshell_susy_parameters::get_Yu() const
      {
         return get_BEptr()->get_Yu();
      }
      
      inline double MSSMNoFV_onshell_susy_parameters::get_Yu(int i, int k) const
      {
         return get_BEptr()->get_Yu(i, k);
      }
      
      inline double MSSMNoFV_onshell_susy_parameters::get_Mu() const
      {
         return get_BEptr()->get_Mu();
      }
      
      inline double MSSMNoFV_onshell_susy_parameters::get_g1() const
      {
         return get_BEptr()->get_g1();
      }
      
      inline double MSSMNoFV_onshell_susy_parameters::get_g2() const
      {
         return get_BEptr()->get_g2();
      }
      
      inline double MSSMNoFV_onshell_susy_parameters::get_g3() const
      {
         return get_BEptr()->get_g3();
      }
      
      inline double MSSMNoFV_onshell_susy_parameters::get_vd() const
      {
         return get_BEptr()->get_vd();
      }
      
      inline double MSSMNoFV_onshell_susy_parameters::get_vu() const
      {
         return get_BEptr()->get_vu();
      }
      
      
      // Wrappers for original constructors: 
      inline MSSMNoFV_onshell_susy_parameters::MSSMNoFV_onshell_susy_parameters() :
         WrapperBase(__factory0())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      inline MSSMNoFV_onshell_susy_parameters::MSSMNoFV_onshell_susy_parameters(double scale_, const Eigen::Matrix<double, 3, 3, 0>& Yd_, const Eigen::Matrix<double, 3, 3, 0>& Ye_, const Eigen::Matrix<double, 3, 3, 0>& Yu_, double Mu_, double g1_, double g2_, double g3_, double vd_, double vu_) :
         WrapperBase(__factory1(scale_, Yd_, Ye_, Yu_, Mu_, g1_, g2_, g3_, vd_, vu_))
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Special pointer-based constructor: 
      inline MSSMNoFV_onshell_susy_parameters::MSSMNoFV_onshell_susy_parameters(Abstract_MSSMNoFV_onshell_susy_parameters* in) :
         WrapperBase(in)
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Copy constructor: 
      inline MSSMNoFV_onshell_susy_parameters::MSSMNoFV_onshell_susy_parameters(const MSSMNoFV_onshell_susy_parameters& in) :
         WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Assignment operator: 
      inline MSSMNoFV_onshell_susy_parameters& MSSMNoFV_onshell_susy_parameters::operator=(const MSSMNoFV_onshell_susy_parameters& in)
      {
         if (this != &in)
         {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
         }
         return *this;
      }
      
      
      // Destructor: 
      inline MSSMNoFV_onshell_susy_parameters::~MSSMNoFV_onshell_susy_parameters()
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
      inline Abstract_MSSMNoFV_onshell_susy_parameters* gm2calc::MSSMNoFV_onshell_susy_parameters::get_BEptr() const
      {
         return dynamic_cast<Abstract_MSSMNoFV_onshell_susy_parameters*>(BEptr);
      }
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_susy_parameters_def_gm2calc_1_3_0_hpp__ */
