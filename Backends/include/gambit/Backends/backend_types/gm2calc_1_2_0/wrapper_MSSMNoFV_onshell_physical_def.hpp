#ifndef __wrapper_MSSMNoFV_onshell_physical_def_gm2calc_1_2_0_hpp__
#define __wrapper_MSSMNoFV_onshell_physical_def_gm2calc_1_2_0_hpp__

#include <ostream>
#include <Eigen/Core>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      // Member functions: 
      inline void MSSMNoFV_onshell_physical::clear()
      {
         get_BEptr()->clear();
      }
      
      inline void MSSMNoFV_onshell_physical::convert_to_hk()
      {
         get_BEptr()->convert_to_hk();
      }
      
      inline void MSSMNoFV_onshell_physical::convert_to_slha()
      {
         get_BEptr()->convert_to_slha();
      }
      
      inline void MSSMNoFV_onshell_physical::print(std::ostream& arg_1) const
      {
         get_BEptr()->print(arg_1);
      }
      
      
      // Wrappers for original constructors: 
      inline MSSMNoFV_onshell_physical::MSSMNoFV_onshell_physical() :
         WrapperBase(__factory0()),
         MVG( get_BEptr()->MVG_ref__BOSS()),
         MGlu( get_BEptr()->MGlu_ref__BOSS()),
         MVP( get_BEptr()->MVP_ref__BOSS()),
         MVZ( get_BEptr()->MVZ_ref__BOSS()),
         MFd( get_BEptr()->MFd_ref__BOSS()),
         MFs( get_BEptr()->MFs_ref__BOSS()),
         MFb( get_BEptr()->MFb_ref__BOSS()),
         MFu( get_BEptr()->MFu_ref__BOSS()),
         MFc( get_BEptr()->MFc_ref__BOSS()),
         MFt( get_BEptr()->MFt_ref__BOSS()),
         MFve( get_BEptr()->MFve_ref__BOSS()),
         MFvm( get_BEptr()->MFvm_ref__BOSS()),
         MFvt( get_BEptr()->MFvt_ref__BOSS()),
         MFe( get_BEptr()->MFe_ref__BOSS()),
         MFm( get_BEptr()->MFm_ref__BOSS()),
         MFtau( get_BEptr()->MFtau_ref__BOSS()),
         MSveL( get_BEptr()->MSveL_ref__BOSS()),
         MSvmL( get_BEptr()->MSvmL_ref__BOSS()),
         MSvtL( get_BEptr()->MSvtL_ref__BOSS()),
         MSd( get_BEptr()->MSd_ref__BOSS()),
         MSu( get_BEptr()->MSu_ref__BOSS()),
         MSe( get_BEptr()->MSe_ref__BOSS()),
         MSm( get_BEptr()->MSm_ref__BOSS()),
         MStau( get_BEptr()->MStau_ref__BOSS()),
         MSs( get_BEptr()->MSs_ref__BOSS()),
         MSc( get_BEptr()->MSc_ref__BOSS()),
         MSb( get_BEptr()->MSb_ref__BOSS()),
         MSt( get_BEptr()->MSt_ref__BOSS()),
         Mhh( get_BEptr()->Mhh_ref__BOSS()),
         MAh( get_BEptr()->MAh_ref__BOSS()),
         MHpm( get_BEptr()->MHpm_ref__BOSS()),
         MChi( get_BEptr()->MChi_ref__BOSS()),
         MCha( get_BEptr()->MCha_ref__BOSS()),
         MVWm( get_BEptr()->MVWm_ref__BOSS()),
         ZD( get_BEptr()->ZD_ref__BOSS()),
         ZU( get_BEptr()->ZU_ref__BOSS()),
         ZE( get_BEptr()->ZE_ref__BOSS()),
         ZM( get_BEptr()->ZM_ref__BOSS()),
         ZTau( get_BEptr()->ZTau_ref__BOSS()),
         ZS( get_BEptr()->ZS_ref__BOSS()),
         ZC( get_BEptr()->ZC_ref__BOSS()),
         ZB( get_BEptr()->ZB_ref__BOSS()),
         ZT( get_BEptr()->ZT_ref__BOSS()),
         ZH( get_BEptr()->ZH_ref__BOSS()),
         ZA( get_BEptr()->ZA_ref__BOSS()),
         ZP( get_BEptr()->ZP_ref__BOSS()),
         ZN( get_BEptr()->ZN_ref__BOSS()),
         UM( get_BEptr()->UM_ref__BOSS()),
         UP( get_BEptr()->UP_ref__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Special pointer-based constructor: 
      inline MSSMNoFV_onshell_physical::MSSMNoFV_onshell_physical(Abstract_MSSMNoFV_onshell_physical* in) :
         WrapperBase(in),
         MVG( get_BEptr()->MVG_ref__BOSS()),
         MGlu( get_BEptr()->MGlu_ref__BOSS()),
         MVP( get_BEptr()->MVP_ref__BOSS()),
         MVZ( get_BEptr()->MVZ_ref__BOSS()),
         MFd( get_BEptr()->MFd_ref__BOSS()),
         MFs( get_BEptr()->MFs_ref__BOSS()),
         MFb( get_BEptr()->MFb_ref__BOSS()),
         MFu( get_BEptr()->MFu_ref__BOSS()),
         MFc( get_BEptr()->MFc_ref__BOSS()),
         MFt( get_BEptr()->MFt_ref__BOSS()),
         MFve( get_BEptr()->MFve_ref__BOSS()),
         MFvm( get_BEptr()->MFvm_ref__BOSS()),
         MFvt( get_BEptr()->MFvt_ref__BOSS()),
         MFe( get_BEptr()->MFe_ref__BOSS()),
         MFm( get_BEptr()->MFm_ref__BOSS()),
         MFtau( get_BEptr()->MFtau_ref__BOSS()),
         MSveL( get_BEptr()->MSveL_ref__BOSS()),
         MSvmL( get_BEptr()->MSvmL_ref__BOSS()),
         MSvtL( get_BEptr()->MSvtL_ref__BOSS()),
         MSd( get_BEptr()->MSd_ref__BOSS()),
         MSu( get_BEptr()->MSu_ref__BOSS()),
         MSe( get_BEptr()->MSe_ref__BOSS()),
         MSm( get_BEptr()->MSm_ref__BOSS()),
         MStau( get_BEptr()->MStau_ref__BOSS()),
         MSs( get_BEptr()->MSs_ref__BOSS()),
         MSc( get_BEptr()->MSc_ref__BOSS()),
         MSb( get_BEptr()->MSb_ref__BOSS()),
         MSt( get_BEptr()->MSt_ref__BOSS()),
         Mhh( get_BEptr()->Mhh_ref__BOSS()),
         MAh( get_BEptr()->MAh_ref__BOSS()),
         MHpm( get_BEptr()->MHpm_ref__BOSS()),
         MChi( get_BEptr()->MChi_ref__BOSS()),
         MCha( get_BEptr()->MCha_ref__BOSS()),
         MVWm( get_BEptr()->MVWm_ref__BOSS()),
         ZD( get_BEptr()->ZD_ref__BOSS()),
         ZU( get_BEptr()->ZU_ref__BOSS()),
         ZE( get_BEptr()->ZE_ref__BOSS()),
         ZM( get_BEptr()->ZM_ref__BOSS()),
         ZTau( get_BEptr()->ZTau_ref__BOSS()),
         ZS( get_BEptr()->ZS_ref__BOSS()),
         ZC( get_BEptr()->ZC_ref__BOSS()),
         ZB( get_BEptr()->ZB_ref__BOSS()),
         ZT( get_BEptr()->ZT_ref__BOSS()),
         ZH( get_BEptr()->ZH_ref__BOSS()),
         ZA( get_BEptr()->ZA_ref__BOSS()),
         ZP( get_BEptr()->ZP_ref__BOSS()),
         ZN( get_BEptr()->ZN_ref__BOSS()),
         UM( get_BEptr()->UM_ref__BOSS()),
         UP( get_BEptr()->UP_ref__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Copy constructor: 
      inline MSSMNoFV_onshell_physical::MSSMNoFV_onshell_physical(const MSSMNoFV_onshell_physical& in) :
         WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
         MVG( get_BEptr()->MVG_ref__BOSS()),
         MGlu( get_BEptr()->MGlu_ref__BOSS()),
         MVP( get_BEptr()->MVP_ref__BOSS()),
         MVZ( get_BEptr()->MVZ_ref__BOSS()),
         MFd( get_BEptr()->MFd_ref__BOSS()),
         MFs( get_BEptr()->MFs_ref__BOSS()),
         MFb( get_BEptr()->MFb_ref__BOSS()),
         MFu( get_BEptr()->MFu_ref__BOSS()),
         MFc( get_BEptr()->MFc_ref__BOSS()),
         MFt( get_BEptr()->MFt_ref__BOSS()),
         MFve( get_BEptr()->MFve_ref__BOSS()),
         MFvm( get_BEptr()->MFvm_ref__BOSS()),
         MFvt( get_BEptr()->MFvt_ref__BOSS()),
         MFe( get_BEptr()->MFe_ref__BOSS()),
         MFm( get_BEptr()->MFm_ref__BOSS()),
         MFtau( get_BEptr()->MFtau_ref__BOSS()),
         MSveL( get_BEptr()->MSveL_ref__BOSS()),
         MSvmL( get_BEptr()->MSvmL_ref__BOSS()),
         MSvtL( get_BEptr()->MSvtL_ref__BOSS()),
         MSd( get_BEptr()->MSd_ref__BOSS()),
         MSu( get_BEptr()->MSu_ref__BOSS()),
         MSe( get_BEptr()->MSe_ref__BOSS()),
         MSm( get_BEptr()->MSm_ref__BOSS()),
         MStau( get_BEptr()->MStau_ref__BOSS()),
         MSs( get_BEptr()->MSs_ref__BOSS()),
         MSc( get_BEptr()->MSc_ref__BOSS()),
         MSb( get_BEptr()->MSb_ref__BOSS()),
         MSt( get_BEptr()->MSt_ref__BOSS()),
         Mhh( get_BEptr()->Mhh_ref__BOSS()),
         MAh( get_BEptr()->MAh_ref__BOSS()),
         MHpm( get_BEptr()->MHpm_ref__BOSS()),
         MChi( get_BEptr()->MChi_ref__BOSS()),
         MCha( get_BEptr()->MCha_ref__BOSS()),
         MVWm( get_BEptr()->MVWm_ref__BOSS()),
         ZD( get_BEptr()->ZD_ref__BOSS()),
         ZU( get_BEptr()->ZU_ref__BOSS()),
         ZE( get_BEptr()->ZE_ref__BOSS()),
         ZM( get_BEptr()->ZM_ref__BOSS()),
         ZTau( get_BEptr()->ZTau_ref__BOSS()),
         ZS( get_BEptr()->ZS_ref__BOSS()),
         ZC( get_BEptr()->ZC_ref__BOSS()),
         ZB( get_BEptr()->ZB_ref__BOSS()),
         ZT( get_BEptr()->ZT_ref__BOSS()),
         ZH( get_BEptr()->ZH_ref__BOSS()),
         ZA( get_BEptr()->ZA_ref__BOSS()),
         ZP( get_BEptr()->ZP_ref__BOSS()),
         ZN( get_BEptr()->ZN_ref__BOSS()),
         UM( get_BEptr()->UM_ref__BOSS()),
         UP( get_BEptr()->UP_ref__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Assignment operator: 
      inline MSSMNoFV_onshell_physical& MSSMNoFV_onshell_physical::operator=(const MSSMNoFV_onshell_physical& in)
      {
         if (this != &in)
         {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
         }
         return *this;
      }
      
      
      // Destructor: 
      inline MSSMNoFV_onshell_physical::~MSSMNoFV_onshell_physical()
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
      inline Abstract_MSSMNoFV_onshell_physical* gm2calc::MSSMNoFV_onshell_physical::get_BEptr() const
      {
         return dynamic_cast<Abstract_MSSMNoFV_onshell_physical*>(BEptr);
      }
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_physical_def_gm2calc_1_2_0_hpp__ */
