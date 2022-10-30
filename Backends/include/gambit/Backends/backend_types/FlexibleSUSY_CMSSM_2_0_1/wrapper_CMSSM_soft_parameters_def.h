#ifndef __wrapper_CMSSM_soft_parameters_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_soft_parameters_def_FlexibleSUSY_CMSSM_2_0_1_h__

#include <ostream>
#include "wrapper_CMSSM_input_parameters_decl.h"
#include "wrapper_CMSSM_susy_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline void CMSSM_soft_parameters::print(::std::basic_ostream<char>& arg_1) const
        {
            get_BEptr()->print(arg_1);
        }
        
        inline CMSSM_soft_parameters CMSSM_soft_parameters::calc_beta() const
        {
            return CMSSM_soft_parameters( const_cast<const Abstract_CMSSM_soft_parameters*>(get_BEptr())->calc_beta__BOSS() );
        }
        
        inline CMSSM_soft_parameters CMSSM_soft_parameters::calc_beta(int arg_1) const
        {
            return CMSSM_soft_parameters( const_cast<const Abstract_CMSSM_soft_parameters*>(get_BEptr())->calc_beta__BOSS(arg_1) );
        }
        
        inline void CMSSM_soft_parameters::clear()
        {
            get_BEptr()->clear();
        }
        
        inline void CMSSM_soft_parameters::set_TYd(int i, int k, const double& value)
        {
            get_BEptr()->set_TYd(i, k, value);
        }
        
        inline void CMSSM_soft_parameters::set_TYe(int i, int k, const double& value)
        {
            get_BEptr()->set_TYe(i, k, value);
        }
        
        inline void CMSSM_soft_parameters::set_TYu(int i, int k, const double& value)
        {
            get_BEptr()->set_TYu(i, k, value);
        }
        
        inline void CMSSM_soft_parameters::set_BMu(double BMu_)
        {
            get_BEptr()->set_BMu(BMu_);
        }
        
        inline void CMSSM_soft_parameters::set_mq2(int i, int k, const double& value)
        {
            get_BEptr()->set_mq2(i, k, value);
        }
        
        inline void CMSSM_soft_parameters::set_ml2(int i, int k, const double& value)
        {
            get_BEptr()->set_ml2(i, k, value);
        }
        
        inline void CMSSM_soft_parameters::set_mHd2(double mHd2_)
        {
            get_BEptr()->set_mHd2(mHd2_);
        }
        
        inline void CMSSM_soft_parameters::set_mHu2(double mHu2_)
        {
            get_BEptr()->set_mHu2(mHu2_);
        }
        
        inline void CMSSM_soft_parameters::set_md2(int i, int k, const double& value)
        {
            get_BEptr()->set_md2(i, k, value);
        }
        
        inline void CMSSM_soft_parameters::set_mu2(int i, int k, const double& value)
        {
            get_BEptr()->set_mu2(i, k, value);
        }
        
        inline void CMSSM_soft_parameters::set_me2(int i, int k, const double& value)
        {
            get_BEptr()->set_me2(i, k, value);
        }
        
        inline void CMSSM_soft_parameters::set_MassB(double MassB_)
        {
            get_BEptr()->set_MassB(MassB_);
        }
        
        inline void CMSSM_soft_parameters::set_MassWB(double MassWB_)
        {
            get_BEptr()->set_MassWB(MassWB_);
        }
        
        inline void CMSSM_soft_parameters::set_MassG(double MassG_)
        {
            get_BEptr()->set_MassG(MassG_);
        }
        
        inline double CMSSM_soft_parameters::get_TYd(int i, int k) const
        {
            return get_BEptr()->get_TYd(i, k);
        }
        
        inline double CMSSM_soft_parameters::get_TYe(int i, int k) const
        {
            return get_BEptr()->get_TYe(i, k);
        }
        
        inline double CMSSM_soft_parameters::get_TYu(int i, int k) const
        {
            return get_BEptr()->get_TYu(i, k);
        }
        
        inline double CMSSM_soft_parameters::get_BMu() const
        {
            return get_BEptr()->get_BMu();
        }
        
        inline double CMSSM_soft_parameters::get_mq2(int i, int k) const
        {
            return get_BEptr()->get_mq2(i, k);
        }
        
        inline double CMSSM_soft_parameters::get_ml2(int i, int k) const
        {
            return get_BEptr()->get_ml2(i, k);
        }
        
        inline double CMSSM_soft_parameters::get_mHd2() const
        {
            return get_BEptr()->get_mHd2();
        }
        
        inline double CMSSM_soft_parameters::get_mHu2() const
        {
            return get_BEptr()->get_mHu2();
        }
        
        inline double CMSSM_soft_parameters::get_md2(int i, int k) const
        {
            return get_BEptr()->get_md2(i, k);
        }
        
        inline double CMSSM_soft_parameters::get_mu2(int i, int k) const
        {
            return get_BEptr()->get_mu2(i, k);
        }
        
        inline double CMSSM_soft_parameters::get_me2(int i, int k) const
        {
            return get_BEptr()->get_me2(i, k);
        }
        
        inline double CMSSM_soft_parameters::get_MassB() const
        {
            return get_BEptr()->get_MassB();
        }
        
        inline double CMSSM_soft_parameters::get_MassWB() const
        {
            return get_BEptr()->get_MassWB();
        }
        
        inline double CMSSM_soft_parameters::get_MassG() const
        {
            return get_BEptr()->get_MassG();
        }
        
        
        // Wrappers for original constructors: 
        inline CMSSM_soft_parameters::CMSSM_soft_parameters(const flexiblesusy::CMSSM_input_parameters& input_) :
            CMSSM_susy_parameters(__factory0(input_))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline CMSSM_soft_parameters::CMSSM_soft_parameters() :
            CMSSM_susy_parameters(__factory1())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline CMSSM_soft_parameters::CMSSM_soft_parameters(Abstract_CMSSM_soft_parameters* in) :
            CMSSM_susy_parameters(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline CMSSM_soft_parameters::CMSSM_soft_parameters(const CMSSM_soft_parameters& in) :
            CMSSM_susy_parameters(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline CMSSM_soft_parameters& CMSSM_soft_parameters::operator=(const CMSSM_soft_parameters& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline CMSSM_soft_parameters::~CMSSM_soft_parameters()
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
        inline Abstract_CMSSM_soft_parameters* flexiblesusy::CMSSM_soft_parameters::get_BEptr() const
        {
            return dynamic_cast<Abstract_CMSSM_soft_parameters*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_soft_parameters_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
