#ifndef __abstract_MSSMNoFV_onshell_susy_parameters_gm2calc_1_2_0_hpp__
#define __abstract_MSSMNoFV_onshell_susy_parameters_gm2calc_1_2_0_hpp__

#include <cstddef>
#include <iostream>
#include <Eigen/Core>
#include <ostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   namespace gm2calc
   {
      class Abstract_MSSMNoFV_onshell_susy_parameters : public virtual AbstractBase
      {
         public:
   
            virtual void print(std::ostream&) const =0;
   
            virtual void clear() =0;
   
            virtual void set_scale(double) =0;
   
            virtual double get_scale() const =0;
   
            virtual void set_Yd(const Eigen::Matrix<double, 3, 3, 0>&) =0;
   
            virtual void set_Yd(int, int, double) =0;
   
            virtual void set_Ye(const Eigen::Matrix<double, 3, 3, 0>&) =0;
   
            virtual void set_Ye(int, int, double) =0;
   
            virtual void set_Yu(const Eigen::Matrix<double, 3, 3, 0>&) =0;
   
            virtual void set_Yu(int, int, double) =0;
   
            virtual void set_Mu(double) =0;
   
            virtual void set_g1(double) =0;
   
            virtual void set_g2(double) =0;
   
            virtual void set_g3(double) =0;
   
            virtual void set_vd(double) =0;
   
            virtual void set_vu(double) =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0>& get_Yd() const =0;
   
            virtual double get_Yd(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0>& get_Ye() const =0;
   
            virtual double get_Ye(int, int) const =0;
   
            virtual const ::Eigen::Matrix<double, 3, 3, 0>& get_Yu() const =0;
   
            virtual double get_Yu(int, int) const =0;
   
            virtual double get_Mu() const =0;
   
            virtual double get_g1() const =0;
   
            virtual double get_g2() const =0;
   
            virtual double get_g3() const =0;
   
            virtual double get_vd() const =0;
   
            virtual double get_vu() const =0;
   
         public:
            virtual void pointer_assign__BOSS(Abstract_MSSMNoFV_onshell_susy_parameters*) =0;
            virtual Abstract_MSSMNoFV_onshell_susy_parameters* pointer_copy__BOSS() =0;
   
         private:
            MSSMNoFV_onshell_susy_parameters* wptr;
            bool delete_wrapper;
         public:
            MSSMNoFV_onshell_susy_parameters* get_wptr() { return wptr; }
            void set_wptr(MSSMNoFV_onshell_susy_parameters* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
         public:
            Abstract_MSSMNoFV_onshell_susy_parameters()
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell_susy_parameters(const Abstract_MSSMNoFV_onshell_susy_parameters&)
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell_susy_parameters& operator=(const Abstract_MSSMNoFV_onshell_susy_parameters&) { return *this; }
   
            virtual void init_wrapper() =0;
   
            MSSMNoFV_onshell_susy_parameters* get_init_wptr()
            {
               init_wrapper();
               return wptr;
            }
   
            MSSMNoFV_onshell_susy_parameters& get_init_wref()
            {
               init_wrapper();
               return *wptr;
            }
   
            virtual ~Abstract_MSSMNoFV_onshell_susy_parameters() =0;
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_MSSMNoFV_onshell_susy_parameters_gm2calc_1_2_0_hpp__ */
