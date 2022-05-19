#ifndef __wrapper_MSSMNoFV_onshell_susy_parameters_decl_gm2calc_1_3_0_hpp__
#define __wrapper_MSSMNoFV_onshell_susy_parameters_decl_gm2calc_1_3_0_hpp__

#include <cstddef>
#include <Eigen/Core>
#include <ostream>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_MSSMNoFV_onshell_susy_parameters.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      class MSSMNoFV_onshell_susy_parameters : public WrapperBase
      {
            // Member variables: 
         public:
            // -- Static factory pointers: 
            static Abstract_MSSMNoFV_onshell_susy_parameters* (*__factory0)();
            static Abstract_MSSMNoFV_onshell_susy_parameters* (*__factory1)(double, const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&, const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&, const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>&, double, double, double, double, double, double);
      
            // -- Other member variables: 
      
            // Member functions: 
         public:
            void print(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const;
      
            void clear();
      
            void set_scale(double s);
      
            double get_scale() const;
      
            void set_Yd(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& Yd_);
      
            void set_Yd(int i, int k, double value);
      
            void set_Ye(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& Ye_);
      
            void set_Ye(int i, int k, double value);
      
            void set_Yu(const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& Yu_);
      
            void set_Yu(int i, int k, double value);
      
            void set_Mu(double Mu_);
      
            void set_g1(double g1_);
      
            void set_g2(double g2_);
      
            void set_g3(double g3_);
      
            void set_vd(double vd_);
      
            void set_vu(double vu_);
      
            const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_Yd() const;
      
            double get_Yd(int i, int k) const;
      
            const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_Ye() const;
      
            double get_Ye(int i, int k) const;
      
            const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& get_Yu() const;
      
            double get_Yu(int i, int k) const;
      
            double get_Mu() const;
      
            double get_g1() const;
      
            double get_g2() const;
      
            double get_g3() const;
      
            double get_vd() const;
      
            double get_vu() const;
      
      
            // Wrappers for original constructors: 
         public:
            MSSMNoFV_onshell_susy_parameters();
            MSSMNoFV_onshell_susy_parameters(double scale_, const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& Yd_, const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& Ye_, const ::Eigen::Matrix<double, 3, 3, 0, 3, 3>& Yu_, double Mu_, double g1_, double g2_, double g3_, double vd_, double vu_);
      
            // Special pointer-based constructor: 
            MSSMNoFV_onshell_susy_parameters(Abstract_MSSMNoFV_onshell_susy_parameters* in);
      
            // Copy constructor: 
            MSSMNoFV_onshell_susy_parameters(const MSSMNoFV_onshell_susy_parameters& in);
      
            // Assignment operator: 
            MSSMNoFV_onshell_susy_parameters& operator=(const MSSMNoFV_onshell_susy_parameters& in);
      
            // Destructor: 
            ~MSSMNoFV_onshell_susy_parameters();
      
            // Returns correctly casted pointer to Abstract class: 
            Abstract_MSSMNoFV_onshell_susy_parameters* get_BEptr() const;
      
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_susy_parameters_decl_gm2calc_1_3_0_hpp__ */
