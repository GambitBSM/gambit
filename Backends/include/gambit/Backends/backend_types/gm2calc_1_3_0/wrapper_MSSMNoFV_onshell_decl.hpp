#ifndef __wrapper_MSSMNoFV_onshell_decl_gm2calc_1_3_0_hpp__
#define __wrapper_MSSMNoFV_onshell_decl_gm2calc_1_3_0_hpp__

#include <cstddef>
#include <Eigen/Core>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_MSSMNoFV_onshell.hpp"
#include "wrapper_MSSMNoFV_onshell_mass_eigenstates_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      class MSSMNoFV_onshell : public MSSMNoFV_onshell_mass_eigenstates
      {
            // Member variables: 
         public:
            // -- Static factory pointers: 
            static Abstract_MSSMNoFV_onshell* (*__factory0)();
            static Abstract_MSSMNoFV_onshell* (*__factory1)(const gm2calc::MSSMNoFV_onshell_mass_eigenstates&);
      
            // -- Other member variables: 
      
            // Member functions: 
         public:
            void set_verbose_output(bool flag);
      
            bool do_verbose_output() const;
      
            void set_alpha_MZ(double arg_1);
      
            void set_alpha_thompson(double arg_1);
      
            void set_Ae(const Eigen::Matrix<double, 3, 3, 0>& A);
      
            void set_Au(const Eigen::Matrix<double, 3, 3, 0>& A);
      
            void set_Ad(const Eigen::Matrix<double, 3, 3, 0>& A);
      
            void set_Ae(unsigned int i, unsigned int k, double a);
      
            void set_Au(unsigned int i, unsigned int k, double a);
      
            void set_Ad(unsigned int i, unsigned int k, double a);
      
            void set_MA0(double m);
      
            void set_TB(double arg_1);
      
            double get_EL() const;
      
            double get_EL0() const;
      
            double get_gY() const;
      
            double get_MUDIM() const;
      
            double get_TB() const;
      
            double get_vev() const;
      
            const ::Eigen::Matrix<double, 3, 3, 0>& get_Ae() const;
      
            const ::Eigen::Matrix<double, 3, 3, 0>& get_Au() const;
      
            const ::Eigen::Matrix<double, 3, 3, 0>& get_Ad() const;
      
            double get_Ae(unsigned int i, unsigned int k) const;
      
            double get_Au(unsigned int i, unsigned int k) const;
      
            double get_Ad(unsigned int i, unsigned int k) const;
      
            double get_MW() const;
      
            double get_MZ() const;
      
            double get_ME() const;
      
            double get_MM() const;
      
            double get_ML() const;
      
            double get_MU() const;
      
            double get_MC() const;
      
            double get_MT() const;
      
            double get_MD() const;
      
            double get_MS() const;
      
            double get_MBMB() const;
      
            double get_MB() const;
      
            double get_MA0() const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_USe() const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_USm() const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_UStau() const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_USu() const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_USd() const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_USc() const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_USs() const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_USb() const;
      
            const ::Eigen::Matrix<double, 2, 2, 0>& get_USt() const;
      
            void convert_to_onshell(double precision, unsigned int max_iterations);
      
            void convert_to_onshell(double precision);
      
            void convert_to_onshell();
      
            void calculate_masses();
      
            void check_problems() const;
      
            void convert_yukawa_couplings_treelevel();
      
      
            // Wrappers for original constructors: 
         public:
            MSSMNoFV_onshell();
            MSSMNoFV_onshell(const gm2calc::MSSMNoFV_onshell_mass_eigenstates& arg_1);
      
            // Special pointer-based constructor: 
            MSSMNoFV_onshell(Abstract_MSSMNoFV_onshell* in);
      
            // Copy constructor: 
            MSSMNoFV_onshell(const MSSMNoFV_onshell& in);
      
            // Assignment operator: 
            MSSMNoFV_onshell& operator=(const MSSMNoFV_onshell& in);
      
            // Destructor: 
            ~MSSMNoFV_onshell();
      
            // Returns correctly casted pointer to Abstract class: 
            Abstract_MSSMNoFV_onshell* get_BEptr() const;
      
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_decl_gm2calc_1_3_0_hpp__ */
