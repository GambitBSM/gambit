#ifndef __wrapper_Constraints_def_THDMC_1_7_0_h__
#define __wrapper_Constraints_def_THDMC_1_7_0_h__

#include "wrapper_THDM_decl.h"
#include "wrapper_SM_decl.h"
#include "wrapper_DecayTableTHDM_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    // Member functions: 
    inline void Constraints::init()
    {
        get_BEptr()->init();
    }
    
    inline void Constraints::set_THDM(THDM& mod)
    {
        get_BEptr()->set_THDM__BOSS(*mod.get_BEptr());
    }
    
    inline bool Constraints::check_unitarity(double unitarity_limit)
    {
        return get_BEptr()->check_unitarity(unitarity_limit);
    }
    
    inline bool Constraints::check_unitarity()
    {
        return get_BEptr()->check_unitarity__BOSS();
    }
    
    inline bool Constraints::check_perturbativity(double perturbativity_limit)
    {
        return get_BEptr()->check_perturbativity(perturbativity_limit);
    }
    
    inline bool Constraints::check_perturbativity()
    {
        return get_BEptr()->check_perturbativity__BOSS();
    }
    
    inline bool Constraints::check_stability()
    {
        return get_BEptr()->check_stability();
    }
    
    inline bool Constraints::check_positivity()
    {
        return get_BEptr()->check_positivity();
    }
    
    inline bool Constraints::check_masses()
    {
        return get_BEptr()->check_masses();
    }
    
    inline bool Constraints::check_lep()
    {
        return get_BEptr()->check_lep();
    }
    
    inline bool Constraints::check_charged(bool& HpHp, bool& HpHptau, bool& HpHpcs)
    {
        return get_BEptr()->check_charged(HpHp, HpHptau, HpHpcs);
    }
    
    inline double Constraints::delta_amu()
    {
        return get_BEptr()->delta_amu();
    }
    
    inline double Constraints::delta_rho(double mh)
    {
        return get_BEptr()->delta_rho(mh);
    }
    
    inline void Constraints::oblique_param(double mh, double& S, double& T, double& U, double& V, double& W, double& X)
    {
        get_BEptr()->oblique_param(mh, S, T, U, V, W, X);
    }
    
    inline void Constraints::print_all(double mh_ref)
    {
        get_BEptr()->print_all(mh_ref);
    }
    
    
    // Wrappers for original constructors: 
    inline Constraints::Constraints(THDM& mod) :
        WrapperBase(__factory0(mod)),
        model( get_BEptr()->model_ref__BOSS().get_init_wref()),
        sm( get_BEptr()->sm_ref__BOSS().get_init_wref()),
        table( get_BEptr()->table_ref__BOSS().get_init_wref())
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Special pointer-based constructor: 
    inline Constraints::Constraints(Abstract_Constraints* in) :
        WrapperBase(in),
        model( get_BEptr()->model_ref__BOSS().get_init_wref()),
        sm( get_BEptr()->sm_ref__BOSS().get_init_wref()),
        table( get_BEptr()->table_ref__BOSS().get_init_wref())
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Copy constructor: 
    inline Constraints::Constraints(const Constraints& in) :
        WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
        model( get_BEptr()->model_ref__BOSS().get_init_wref()),
        sm( get_BEptr()->sm_ref__BOSS().get_init_wref()),
        table( get_BEptr()->table_ref__BOSS().get_init_wref())
    {
        get_BEptr()->set_wptr(this);
        get_BEptr()->set_delete_wrapper(false);
    }
    
    // Assignment operator: 
    inline Constraints& Constraints::operator=(const Constraints& in)
    {
        if (this != &in)
        {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
        }
        return *this;
    }
    
    
    // Destructor: 
    inline Constraints::~Constraints()
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
    inline Abstract_Constraints* Constraints::get_BEptr() const
    {
        return dynamic_cast<Abstract_Constraints*>(BEptr);
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Constraints_def_THDMC_1_7_0_h__ */
