#ifndef __wrapper_Model_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_Model_def_FlexibleSUSY_CMSSM_2_0_1_h__

#include <string>
#include <ostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline void Model::calculate_spectrum()
        {
            get_BEptr()->calculate_spectrum();
        }
        
        inline void Model::clear_problems()
        {
            get_BEptr()->clear_problems();
        }
        
        inline ::std::basic_string<char> Model::name() const
        {
            return get_BEptr()->name();
        }
        
        inline void Model::print(::std::basic_ostream<char>& out) const
        {
            get_BEptr()->print(out);
        }
        
        inline void Model::print() const
        {
            get_BEptr()->print__BOSS();
        }
        
        inline void Model::run_to(double arg_1, double eps)
        {
            get_BEptr()->run_to(arg_1, eps);
        }
        
        inline void Model::run_to(double arg_1)
        {
            get_BEptr()->run_to__BOSS(arg_1);
        }
        
        inline void Model::set_precision(double arg_1)
        {
            get_BEptr()->set_precision(arg_1);
        }
        
        
        // Wrappers for original constructors: 
        inline Model::Model() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Model::Model(Abstract_Model* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Model::Model(const Model& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Model& Model::operator=(const Model& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Model::~Model()
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
        inline Abstract_Model* flexiblesusy::Model::get_BEptr() const
        {
            return dynamic_cast<Abstract_Model*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Model_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
