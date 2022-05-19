#ifndef __wrapper_MSSMNoFV_onshell_physical_decl_gm2calc_1_3_0_hpp__
#define __wrapper_MSSMNoFV_onshell_physical_decl_gm2calc_1_3_0_hpp__

#include <cstddef>
#include <ostream>
#include <Eigen/Core>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_MSSMNoFV_onshell_physical.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      class MSSMNoFV_onshell_physical : public WrapperBase
      {
            // Member variables: 
         public:
            // -- Static factory pointers: 
            static Abstract_MSSMNoFV_onshell_physical* (*__factory0)();
      
            // -- Other member variables: 
         public:
            double& MVG;
            double& MGlu;
            double& MVP;
            double& MVZ;
            double& MFd;
            double& MFs;
            double& MFb;
            double& MFu;
            double& MFc;
            double& MFt;
            double& MFve;
            double& MFvm;
            double& MFvt;
            double& MFe;
            double& MFm;
            double& MFtau;
            double& MSveL;
            double& MSvmL;
            double& MSvtL;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MSd;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MSu;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MSe;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MSm;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MStau;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MSs;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MSc;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MSb;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MSt;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& Mhh;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MAh;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MHpm;
            ::Eigen::Array<double, 4, 1, 0, 4, 1>& MChi;
            ::Eigen::Array<double, 2, 1, 0, 2, 1>& MCha;
            double& MVWm;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZD;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZU;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZE;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZM;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZTau;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZS;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZC;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZB;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZT;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZH;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZA;
            ::Eigen::Matrix<double, 2, 2, 0, 2, 2>& ZP;
            ::Eigen::Matrix<std::complex<double>, 4, 4, 0, 4, 4>& ZN;
            ::Eigen::Matrix<std::complex<double>, 2, 2, 0, 2, 2>& UM;
            ::Eigen::Matrix<std::complex<double>, 2, 2, 0, 2, 2>& UP;
      
            // Member functions: 
         public:
            void clear();
      
            void convert_to_hk();
      
            void convert_to_slha();
      
            void print(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const;
      
      
            // Wrappers for original constructors: 
         public:
            MSSMNoFV_onshell_physical();
      
            // Special pointer-based constructor: 
            MSSMNoFV_onshell_physical(Abstract_MSSMNoFV_onshell_physical* in);
      
            // Copy constructor: 
            MSSMNoFV_onshell_physical(const MSSMNoFV_onshell_physical& in);
      
            // Assignment operator: 
            MSSMNoFV_onshell_physical& operator=(const MSSMNoFV_onshell_physical& in);
      
            // Destructor: 
            ~MSSMNoFV_onshell_physical();
      
            // Returns correctly casted pointer to Abstract class: 
            Abstract_MSSMNoFV_onshell_physical* get_BEptr() const;
      
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_physical_decl_gm2calc_1_3_0_hpp__ */
