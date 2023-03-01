#ifndef __abstract_MSSMNoFV_onshell_gm2calc_1_2_0_hpp__
#define __abstract_MSSMNoFV_onshell_gm2calc_1_2_0_hpp__

#include <cstddef>
#include <iostream>
#include <Eigen/Core>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_MSSMNoFV_onshell_mass_eigenstates_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   namespace gm2calc
   {
      class Abstract_MSSMNoFV_onshell : virtual public gm2calc::Abstract_MSSMNoFV_onshell_mass_eigenstates
      {
         public:
   
            virtual void set_verbose_output(bool) =0;
   
            virtual bool do_verbose_output() const =0;
   
            virtual void set_alpha_MZ(double) =0;
   
            virtual void set_alpha_thompson(double) =0;
   
            virtual void set_Ae(const ::Eigen::Matrix<double, 3, 3, 0>&) =0;
   
            virtual void set_Au(const ::Eigen::Matrix<double, 3, 3, 0>&) =0;
   
            virtual void set_Ad(const ::Eigen::Matrix<double, 3, 3, 0>&) =0;
   
            virtual void set_Ae(unsigned int, unsigned int, double) =0;
   
            virtual void set_Au(unsigned int, unsigned int, double) =0;
   
            virtual void set_Ad(unsigned int, unsigned int, double) =0;
   
            virtual void set_MA0(double) =0;
   
            virtual void set_TB(double) =0;
   
            virtual double get_EL() const =0;
   
            virtual double get_EL0() const =0;
   
            virtual double get_gY() const =0;
   
            virtual double get_MUDIM() const =0;
   
            virtual double get_TB() const =0;
   
            virtual double get_vev() const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0>& get_Ae() const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0>& get_Au() const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0>& get_Ad() const =0;
   
            virtual double get_Ae(unsigned int, unsigned int) const =0;
   
            virtual double get_Au(unsigned int, unsigned int) const =0;
   
            virtual double get_Ad(unsigned int, unsigned int) const =0;
   
            virtual double get_MW() const =0;
   
            virtual double get_MZ() const =0;
   
            virtual double get_ME() const =0;
   
            virtual double get_MM() const =0;
   
            virtual double get_ML() const =0;
   
            virtual double get_MU() const =0;
   
            virtual double get_MC() const =0;
   
            virtual double get_MT() const =0;
   
            virtual double get_MD() const =0;
   
            virtual double get_MS() const =0;
   
            virtual double get_MBMB() const =0;
   
            virtual double get_MB() const =0;
   
            virtual double get_MA0() const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_USe() const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_USm() const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_UStau() const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_USu() const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_USd() const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_USc() const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_USs() const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_USb() const =0;
   
            virtual const ::Eigen::Matrix<double, 2, 2, 0>& get_USt() const =0;
   
            virtual void convert_to_onshell(double, unsigned int) =0;
   
            virtual void convert_to_onshell__BOSS(double) =0;
   
            virtual void convert_to_onshell__BOSS() =0;
   
            virtual void calculate_masses() =0;
   
            virtual void check_problems() const =0;
   
            virtual void convert_yukawa_couplings_treelevel() =0;
   
         public:
            using gm2calc::Abstract_MSSMNoFV_onshell_mass_eigenstates::pointer_assign__BOSS;
            virtual void pointer_assign__BOSS(Abstract_MSSMNoFV_onshell*) =0;
            virtual Abstract_MSSMNoFV_onshell* pointer_copy__BOSS() =0;
   
         private:
            MSSMNoFV_onshell* wptr;
            bool delete_wrapper;
         public:
            MSSMNoFV_onshell* get_wptr() { return wptr; }
            void set_wptr(MSSMNoFV_onshell* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
         public:
            Abstract_MSSMNoFV_onshell()
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell(const Abstract_MSSMNoFV_onshell& in) : 
               gm2calc::Abstract_MSSMNoFV_onshell_susy_parameters(in), gm2calc::Abstract_MSSMNoFV_onshell_soft_parameters(in), gm2calc::Abstract_MSSMNoFV_onshell_mass_eigenstates(in)
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell& operator=(const Abstract_MSSMNoFV_onshell&) { return *this; }
   
            virtual void init_wrapper() =0;
   
            MSSMNoFV_onshell* get_init_wptr()
            {
               init_wrapper();
               return wptr;
            }
   
            MSSMNoFV_onshell& get_init_wref()
            {
               init_wrapper();
               return *wptr;
            }
   
            virtual ~Abstract_MSSMNoFV_onshell() =0;
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_MSSMNoFV_onshell_gm2calc_1_2_0_hpp__ */
