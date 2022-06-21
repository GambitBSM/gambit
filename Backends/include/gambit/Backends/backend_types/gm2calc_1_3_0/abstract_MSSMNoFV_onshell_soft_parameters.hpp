#ifndef __abstract_MSSMNoFV_onshell_soft_parameters_gm2calc_1_3_0_hpp__
#define __abstract_MSSMNoFV_onshell_soft_parameters_gm2calc_1_3_0_hpp__

#include <cstddef>
#include <iostream>
#include <Eigen/Core>
#include <ostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_MSSMNoFV_onshell_susy_parameters_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   namespace gm2calc
   {
      class Abstract_MSSMNoFV_onshell_soft_parameters : virtual public gm2calc::Abstract_MSSMNoFV_onshell_susy_parameters
      {
         public:
   
            virtual void print(::std::basic_ostream<char, std::char_traits<char> >&) const =0;
   
            virtual void clear() =0;
   
            virtual void set_TYd(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&) =0;
   
            virtual void set_TYd(int, int, double) =0;
   
            virtual void set_TYe(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&) =0;
   
            virtual void set_TYe(int, int, double) =0;
   
            virtual void set_TYu(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&) =0;
   
            virtual void set_TYu(int, int, double) =0;
   
            virtual void set_BMu(double) =0;
   
            virtual void set_mq2(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&) =0;
   
            virtual void set_mq2(int, int, double) =0;
   
            virtual void set_ml2(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&) =0;
   
            virtual void set_ml2(int, int, double) =0;
   
            virtual void set_mHd2(double) =0;
   
            virtual void set_mHu2(double) =0;
   
            virtual void set_md2(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&) =0;
   
            virtual void set_md2(int, int, double) =0;
   
            virtual void set_mu2(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&) =0;
   
            virtual void set_mu2(int, int, double) =0;
   
            virtual void set_me2(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&) =0;
   
            virtual void set_me2(int, int, double) =0;
   
            virtual void set_MassB(double) =0;
   
            virtual void set_MassWB(double) =0;
   
            virtual void set_MassG(double) =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_TYd() const =0;
   
            virtual double get_TYd(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_TYe() const =0;
   
            virtual double get_TYe(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_TYu() const =0;
   
            virtual double get_TYu(int, int) const =0;
   
            virtual double get_BMu() const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_mq2() const =0;
   
            virtual double get_mq2(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_ml2() const =0;
   
            virtual double get_ml2(int, int) const =0;
   
            virtual double get_mHd2() const =0;
   
            virtual double get_mHu2() const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_md2() const =0;
   
            virtual double get_md2(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_mu2() const =0;
   
            virtual double get_mu2(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_me2() const =0;
   
            virtual double get_me2(int, int) const =0;
   
            virtual double get_MassB() const =0;
   
            virtual double get_MassWB() const =0;
   
            virtual double get_MassG() const =0;
   
         public:
            using gm2calc::Abstract_MSSMNoFV_onshell_susy_parameters::pointer_assign__BOSS;
            virtual void pointer_assign__BOSS(Abstract_MSSMNoFV_onshell_soft_parameters*) =0;
            virtual Abstract_MSSMNoFV_onshell_soft_parameters* pointer_copy__BOSS() =0;
   
         private:
            MSSMNoFV_onshell_soft_parameters* wptr;
            bool delete_wrapper;
         public:
            MSSMNoFV_onshell_soft_parameters* get_wptr() { return wptr; }
            void set_wptr(MSSMNoFV_onshell_soft_parameters* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
         public:
            Abstract_MSSMNoFV_onshell_soft_parameters()
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell_soft_parameters(const Abstract_MSSMNoFV_onshell_soft_parameters& in) : 
               gm2calc::Abstract_MSSMNoFV_onshell_susy_parameters(in)
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell_soft_parameters& operator=(const Abstract_MSSMNoFV_onshell_soft_parameters&) { return *this; }
   
            virtual void init_wrapper() =0;
   
            MSSMNoFV_onshell_soft_parameters* get_init_wptr()
            {
               init_wrapper();
               return wptr;
            }
   
            MSSMNoFV_onshell_soft_parameters& get_init_wref()
            {
               init_wrapper();
               return *wptr;
            }
   
            virtual ~Abstract_MSSMNoFV_onshell_soft_parameters() =0;
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_MSSMNoFV_onshell_soft_parameters_gm2calc_1_3_0_hpp__ */
