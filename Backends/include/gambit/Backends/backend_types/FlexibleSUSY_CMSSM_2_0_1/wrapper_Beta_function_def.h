#ifndef __wrapper_Beta_function_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_Beta_function_def_FlexibleSUSY_CMSSM_2_0_1_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline void Beta_function::set_scale(double s)
        {
            get_BEptr()->set_scale(s);
        }
        
        inline void Beta_function::set_number_of_parameters(int pars)
        {
            get_BEptr()->set_number_of_parameters(pars);
        }
        
        inline void Beta_function::set_loops(int l)
        {
            get_BEptr()->set_loops(l);
        }
        
        inline void Beta_function::set_thresholds(int t)
        {
            get_BEptr()->set_thresholds(t);
        }
        
        inline void Beta_function::set_zero_threshold(double t)
        {
            get_BEptr()->set_zero_threshold(t);
        }
        
        inline double Beta_function::get_scale() const
        {
            return get_BEptr()->get_scale();
        }
        
        inline int Beta_function::get_number_of_parameters() const
        {
            return get_BEptr()->get_number_of_parameters();
        }
        
        inline int Beta_function::get_loops() const
        {
            return get_BEptr()->get_loops();
        }
        
        inline int Beta_function::get_thresholds() const
        {
            return get_BEptr()->get_thresholds();
        }
        
        inline double Beta_function::get_zero_threshold() const
        {
            return get_BEptr()->get_zero_threshold();
        }
        
        inline void Beta_function::reset()
        {
            get_BEptr()->reset();
        }
        
        inline void Beta_function::run(double arg_1, double arg_2, double eps)
        {
            get_BEptr()->run(arg_1, arg_2, eps);
        }
        
        inline void Beta_function::run(double arg_1, double arg_2)
        {
            get_BEptr()->run__BOSS(arg_1, arg_2);
        }
        
        inline void Beta_function::run_to(double arg_1, double eps)
        {
            get_BEptr()->run_to(arg_1, eps);
        }
        
        inline void Beta_function::run_to(double arg_1)
        {
            get_BEptr()->run_to__BOSS(arg_1);
        }
        
        
        // Wrappers for original constructors: 
        inline Beta_function::Beta_function() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Beta_function::Beta_function(Abstract_Beta_function* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Beta_function::Beta_function(const Beta_function& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Beta_function& Beta_function::operator=(const Beta_function& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Beta_function::~Beta_function()
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
        inline Abstract_Beta_function* flexiblesusy::Beta_function::get_BEptr() const
        {
            return dynamic_cast<Abstract_Beta_function*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Beta_function_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
