#ifndef __abstract_MSSMNoFV_onshell_physical_gm2calc_1_2_0_hpp__
#define __abstract_MSSMNoFV_onshell_physical_gm2calc_1_2_0_hpp__

#include <cstddef>
#include <iostream>
#include <ostream>
#include <Eigen/Core>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   namespace gm2calc
   {
      class Abstract_MSSMNoFV_onshell_physical : public virtual AbstractBase
      {
         public:
   
            virtual void clear() =0;
   
            virtual void convert_to_hk() =0;
   
            virtual void convert_to_slha() =0;
   
            virtual void print(std::ostream&) const =0;
   
            virtual double& MVG_ref__BOSS() =0;
   
            virtual double& MGlu_ref__BOSS() =0;
   
            virtual double& MVP_ref__BOSS() =0;
   
            virtual double& MVZ_ref__BOSS() =0;
   
            virtual double& MFd_ref__BOSS() =0;
   
            virtual double& MFs_ref__BOSS() =0;
   
            virtual double& MFb_ref__BOSS() =0;
   
            virtual double& MFu_ref__BOSS() =0;
   
            virtual double& MFc_ref__BOSS() =0;
   
            virtual double& MFt_ref__BOSS() =0;
   
            virtual double& MFve_ref__BOSS() =0;
   
            virtual double& MFvm_ref__BOSS() =0;
   
            virtual double& MFvt_ref__BOSS() =0;
   
            virtual double& MFe_ref__BOSS() =0;
   
            virtual double& MFm_ref__BOSS() =0;
   
            virtual double& MFtau_ref__BOSS() =0;
   
            virtual double& MSveL_ref__BOSS() =0;
   
            virtual double& MSvmL_ref__BOSS() =0;
   
            virtual double& MSvtL_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MSd_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MSu_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MSe_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MSm_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MStau_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MSs_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MSc_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MSb_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MSt_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& Mhh_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MAh_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MHpm_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 4, 1, 0>& MChi_ref__BOSS() =0;
   
            virtual ::Eigen::Array<double, 2, 1, 0>& MCha_ref__BOSS() =0;
   
            virtual double& MVWm_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZD_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZU_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZE_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZM_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZTau_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZS_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZC_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZB_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZT_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZH_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZA_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<double, 2, 2, 0>& ZP_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<std::complex<double>, 4, 4, 0>& ZN_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<std::complex<double>, 2, 2, 0>& UM_ref__BOSS() =0;
   
            virtual ::Eigen::Matrix<std::complex<double>, 2, 2, 0>& UP_ref__BOSS() =0;
   
         public:
            virtual void pointer_assign__BOSS(Abstract_MSSMNoFV_onshell_physical*) =0;
            virtual Abstract_MSSMNoFV_onshell_physical* pointer_copy__BOSS() =0;
   
         private:
            MSSMNoFV_onshell_physical* wptr;
            bool delete_wrapper;
         public:
            MSSMNoFV_onshell_physical* get_wptr() { return wptr; }
            void set_wptr(MSSMNoFV_onshell_physical* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
         public:
            Abstract_MSSMNoFV_onshell_physical()
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell_physical(const Abstract_MSSMNoFV_onshell_physical&)
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell_physical& operator=(const Abstract_MSSMNoFV_onshell_physical&) { return *this; }
   
            virtual void init_wrapper() =0;
   
            MSSMNoFV_onshell_physical* get_init_wptr()
            {
               init_wrapper();
               return wptr;
            }
   
            MSSMNoFV_onshell_physical& get_init_wref()
            {
               init_wrapper();
               return *wptr;
            }
   
            virtual ~Abstract_MSSMNoFV_onshell_physical() =0;
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_MSSMNoFV_onshell_physical_gm2calc_1_2_0_hpp__ */
