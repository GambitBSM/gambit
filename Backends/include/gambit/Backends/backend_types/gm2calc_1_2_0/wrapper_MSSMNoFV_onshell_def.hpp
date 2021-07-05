#ifndef __wrapper_MSSMNoFV_onshell_def_gm2calc_1_2_0_hpp__
#define __wrapper_MSSMNoFV_onshell_def_gm2calc_1_2_0_hpp__

#include <Eigen/Core>
#include "wrapper_MSSMNoFV_onshell_mass_eigenstates_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      // Member functions: 
      inline void MSSMNoFV_onshell::set_verbose_output(bool flag)
      {
         get_BEptr()->set_verbose_output(flag);
      }
      
      inline bool MSSMNoFV_onshell::do_verbose_output() const
      {
         return get_BEptr()->do_verbose_output();
      }
      
      inline void MSSMNoFV_onshell::set_alpha_MZ(double arg_1)
      {
         get_BEptr()->set_alpha_MZ(arg_1);
      }
      
      inline void MSSMNoFV_onshell::set_alpha_thompson(double arg_1)
      {
         get_BEptr()->set_alpha_thompson(arg_1);
      }
      
      inline void MSSMNoFV_onshell::set_Ae(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& A)
      {
         get_BEptr()->set_Ae(A);
      }
      
      inline void MSSMNoFV_onshell::set_Au(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& A)
      {
         get_BEptr()->set_Au(A);
      }
      
      inline void MSSMNoFV_onshell::set_Ad(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& A)
      {
         get_BEptr()->set_Ad(A);
      }
      
      inline void MSSMNoFV_onshell::set_Ae(unsigned int i, unsigned int k, double a)
      {
         get_BEptr()->set_Ae(i, k, a);
      }
      
      inline void MSSMNoFV_onshell::set_Au(unsigned int i, unsigned int k, double a)
      {
         get_BEptr()->set_Au(i, k, a);
      }
      
      inline void MSSMNoFV_onshell::set_Ad(unsigned int i, unsigned int k, double a)
      {
         get_BEptr()->set_Ad(i, k, a);
      }
      
      inline void MSSMNoFV_onshell::set_MA0(double m)
      {
         get_BEptr()->set_MA0(m);
      }
      
      inline void MSSMNoFV_onshell::set_TB(double arg_1)
      {
         get_BEptr()->set_TB(arg_1);
      }
      
      inline double MSSMNoFV_onshell::get_EL() const
      {
         return get_BEptr()->get_EL();
      }
      
      inline double MSSMNoFV_onshell::get_EL0() const
      {
         return get_BEptr()->get_EL0();
      }
      
      inline double MSSMNoFV_onshell::get_gY() const
      {
         return get_BEptr()->get_gY();
      }
      
      inline double MSSMNoFV_onshell::get_MUDIM() const
      {
         return get_BEptr()->get_MUDIM();
      }
      
      inline double MSSMNoFV_onshell::get_TB() const
      {
         return get_BEptr()->get_TB();
      }
      
      inline double MSSMNoFV_onshell::get_vev() const
      {
         return get_BEptr()->get_vev();
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& MSSMNoFV_onshell::get_Ae() const
      {
         return get_BEptr()->get_Ae();
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& MSSMNoFV_onshell::get_Au() const
      {
         return get_BEptr()->get_Au();
      }
      
      inline const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& MSSMNoFV_onshell::get_Ad() const
      {
         return get_BEptr()->get_Ad();
      }
      
      inline double MSSMNoFV_onshell::get_Ae(unsigned int i, unsigned int k) const
      {
         return get_BEptr()->get_Ae(i, k);
      }
      
      inline double MSSMNoFV_onshell::get_Au(unsigned int i, unsigned int k) const
      {
         return get_BEptr()->get_Au(i, k);
      }
      
      inline double MSSMNoFV_onshell::get_Ad(unsigned int i, unsigned int k) const
      {
         return get_BEptr()->get_Ad(i, k);
      }
      
      inline double MSSMNoFV_onshell::get_MW() const
      {
         return get_BEptr()->get_MW();
      }
      
      inline double MSSMNoFV_onshell::get_MZ() const
      {
         return get_BEptr()->get_MZ();
      }
      
      inline double MSSMNoFV_onshell::get_ME() const
      {
         return get_BEptr()->get_ME();
      }
      
      inline double MSSMNoFV_onshell::get_MM() const
      {
         return get_BEptr()->get_MM();
      }
      
      inline double MSSMNoFV_onshell::get_ML() const
      {
         return get_BEptr()->get_ML();
      }
      
      inline double MSSMNoFV_onshell::get_MU() const
      {
         return get_BEptr()->get_MU();
      }
      
      inline double MSSMNoFV_onshell::get_MC() const
      {
         return get_BEptr()->get_MC();
      }
      
      inline double MSSMNoFV_onshell::get_MT() const
      {
         return get_BEptr()->get_MT();
      }
      
      inline double MSSMNoFV_onshell::get_MD() const
      {
         return get_BEptr()->get_MD();
      }
      
      inline double MSSMNoFV_onshell::get_MS() const
      {
         return get_BEptr()->get_MS();
      }
      
      inline double MSSMNoFV_onshell::get_MBMB() const
      {
         return get_BEptr()->get_MBMB();
      }
      
      inline double MSSMNoFV_onshell::get_MB() const
      {
         return get_BEptr()->get_MB();
      }
      
      inline double MSSMNoFV_onshell::get_MA0() const
      {
         return get_BEptr()->get_MA0();
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& MSSMNoFV_onshell::get_USe() const
      {
         return get_BEptr()->get_USe();
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& MSSMNoFV_onshell::get_USm() const
      {
         return get_BEptr()->get_USm();
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& MSSMNoFV_onshell::get_UStau() const
      {
         return get_BEptr()->get_UStau();
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& MSSMNoFV_onshell::get_USu() const
      {
         return get_BEptr()->get_USu();
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& MSSMNoFV_onshell::get_USd() const
      {
         return get_BEptr()->get_USd();
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& MSSMNoFV_onshell::get_USc() const
      {
         return get_BEptr()->get_USc();
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& MSSMNoFV_onshell::get_USs() const
      {
         return get_BEptr()->get_USs();
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& MSSMNoFV_onshell::get_USb() const
      {
         return get_BEptr()->get_USb();
      }
      
      inline const ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& MSSMNoFV_onshell::get_USt() const
      {
         return get_BEptr()->get_USt();
      }
      
      inline void MSSMNoFV_onshell::convert_to_onshell(double precision, unsigned int max_iterations)
      {
         get_BEptr()->convert_to_onshell(precision, max_iterations);
      }
      
      inline void MSSMNoFV_onshell::convert_to_onshell(double precision)
      {
         get_BEptr()->convert_to_onshell__BOSS(precision);
      }
      
      inline void MSSMNoFV_onshell::convert_to_onshell()
      {
         get_BEptr()->convert_to_onshell__BOSS();
      }
      
      inline void MSSMNoFV_onshell::calculate_masses()
      {
         get_BEptr()->calculate_masses();
      }
      
      inline void MSSMNoFV_onshell::check_problems() const
      {
         get_BEptr()->check_problems();
      }
      
      inline void MSSMNoFV_onshell::convert_yukawa_couplings_treelevel()
      {
         get_BEptr()->convert_yukawa_couplings_treelevel();
      }
      
      
      // Wrappers for original constructors: 
      inline MSSMNoFV_onshell::MSSMNoFV_onshell() :
         MSSMNoFV_onshell_mass_eigenstates(__factory0())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      inline MSSMNoFV_onshell::MSSMNoFV_onshell(const gm2calc::MSSMNoFV_onshell_mass_eigenstates& arg_1) :
         MSSMNoFV_onshell_mass_eigenstates(__factory1(arg_1))
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Special pointer-based constructor: 
      inline MSSMNoFV_onshell::MSSMNoFV_onshell(Abstract_MSSMNoFV_onshell* in) :
         MSSMNoFV_onshell_mass_eigenstates(in)
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Copy constructor: 
      inline MSSMNoFV_onshell::MSSMNoFV_onshell(const MSSMNoFV_onshell& in) :
         MSSMNoFV_onshell_mass_eigenstates(in.get_BEptr()->pointer_copy__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Assignment operator: 
      inline MSSMNoFV_onshell& MSSMNoFV_onshell::operator=(const MSSMNoFV_onshell& in)
      {
         if (this != &in)
         {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
         }
         return *this;
      }
      
      
      // Destructor: 
      inline MSSMNoFV_onshell::~MSSMNoFV_onshell()
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
      inline Abstract_MSSMNoFV_onshell* gm2calc::MSSMNoFV_onshell::get_BEptr() const
      {
         return dynamic_cast<Abstract_MSSMNoFV_onshell*>(BEptr);
      }
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_def_gm2calc_1_2_0_hpp__ */
