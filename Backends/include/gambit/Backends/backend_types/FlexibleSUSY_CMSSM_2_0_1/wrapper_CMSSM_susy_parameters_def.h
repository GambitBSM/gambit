#ifndef __wrapper_CMSSM_susy_parameters_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_susy_parameters_def_FlexibleSUSY_CMSSM_2_0_1_h__

#include <ostream>
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline void CMSSM_susy_parameters::print(::std::basic_ostream<char>& arg_1) const
        {
            get_BEptr()->print(arg_1);
        }
        
        inline const CMSSM_input_parameters& CMSSM_susy_parameters::get_input() const
        {
            return const_cast<CMSSM_input_parameters&>(const_cast<const Abstract_CMSSM_susy_parameters*>(get_BEptr())->get_input__BOSS()).get_init_wref();
        }
        
        inline CMSSM_input_parameters& CMSSM_susy_parameters::get_input()
        {
            return get_BEptr()->get_input__BOSS().get_init_wref();
        }
        
        inline void CMSSM_susy_parameters::set_input_parameters(const flexiblesusy::CMSSM_input_parameters& arg_1)
        {
            get_BEptr()->set_input_parameters__BOSS(*arg_1.get_BEptr());
        }
        
        inline CMSSM_susy_parameters CMSSM_susy_parameters::calc_beta() const
        {
            return CMSSM_susy_parameters( const_cast<const Abstract_CMSSM_susy_parameters*>(get_BEptr())->calc_beta__BOSS() );
        }
        
        inline CMSSM_susy_parameters CMSSM_susy_parameters::calc_beta(int arg_1) const
        {
            return CMSSM_susy_parameters( const_cast<const Abstract_CMSSM_susy_parameters*>(get_BEptr())->calc_beta__BOSS(arg_1) );
        }
        
        inline void CMSSM_susy_parameters::clear()
        {
            get_BEptr()->clear();
        }
        
        inline void CMSSM_susy_parameters::set_Yd(int i, int k, const double& value)
        {
            get_BEptr()->set_Yd(i, k, value);
        }
        
        inline void CMSSM_susy_parameters::set_Ye(int i, int k, const double& value)
        {
            get_BEptr()->set_Ye(i, k, value);
        }
        
        inline void CMSSM_susy_parameters::set_Yu(int i, int k, const double& value)
        {
            get_BEptr()->set_Yu(i, k, value);
        }
        
        inline void CMSSM_susy_parameters::set_Mu(double Mu_)
        {
            get_BEptr()->set_Mu(Mu_);
        }
        
        inline void CMSSM_susy_parameters::set_g1(double g1_)
        {
            get_BEptr()->set_g1(g1_);
        }
        
        inline void CMSSM_susy_parameters::set_g2(double g2_)
        {
            get_BEptr()->set_g2(g2_);
        }
        
        inline void CMSSM_susy_parameters::set_g3(double g3_)
        {
            get_BEptr()->set_g3(g3_);
        }
        
        inline void CMSSM_susy_parameters::set_vd(double vd_)
        {
            get_BEptr()->set_vd(vd_);
        }
        
        inline void CMSSM_susy_parameters::set_vu(double vu_)
        {
            get_BEptr()->set_vu(vu_);
        }
        
        inline double CMSSM_susy_parameters::get_Yd(int i, int k) const
        {
            return get_BEptr()->get_Yd(i, k);
        }
        
        inline double CMSSM_susy_parameters::get_Ye(int i, int k) const
        {
            return get_BEptr()->get_Ye(i, k);
        }
        
        inline double CMSSM_susy_parameters::get_Yu(int i, int k) const
        {
            return get_BEptr()->get_Yu(i, k);
        }
        
        inline double CMSSM_susy_parameters::get_Mu() const
        {
            return get_BEptr()->get_Mu();
        }
        
        inline double CMSSM_susy_parameters::get_g1() const
        {
            return get_BEptr()->get_g1();
        }
        
        inline double CMSSM_susy_parameters::get_g2() const
        {
            return get_BEptr()->get_g2();
        }
        
        inline double CMSSM_susy_parameters::get_g3() const
        {
            return get_BEptr()->get_g3();
        }
        
        inline double CMSSM_susy_parameters::get_vd() const
        {
            return get_BEptr()->get_vd();
        }
        
        inline double CMSSM_susy_parameters::get_vu() const
        {
            return get_BEptr()->get_vu();
        }
        
        inline double CMSSM_susy_parameters::get_SHdSHd() const
        {
            return get_BEptr()->get_SHdSHd();
        }
        
        inline double CMSSM_susy_parameters::get_SHuSHu() const
        {
            return get_BEptr()->get_SHuSHu();
        }
        
        
        // Wrappers for original constructors: 
        inline CMSSM_susy_parameters::CMSSM_susy_parameters(const flexiblesusy::CMSSM_input_parameters& input_) :
            Beta_function(__factory0(input_))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline CMSSM_susy_parameters::CMSSM_susy_parameters() :
            Beta_function(__factory1())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline CMSSM_susy_parameters::CMSSM_susy_parameters(Abstract_CMSSM_susy_parameters* in) :
            Beta_function(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline CMSSM_susy_parameters::CMSSM_susy_parameters(const CMSSM_susy_parameters& in) :
            Beta_function(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline CMSSM_susy_parameters& CMSSM_susy_parameters::operator=(const CMSSM_susy_parameters& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline CMSSM_susy_parameters::~CMSSM_susy_parameters()
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
        inline Abstract_CMSSM_susy_parameters* flexiblesusy::CMSSM_susy_parameters::get_BEptr() const
        {
            return dynamic_cast<Abstract_CMSSM_susy_parameters*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_susy_parameters_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
