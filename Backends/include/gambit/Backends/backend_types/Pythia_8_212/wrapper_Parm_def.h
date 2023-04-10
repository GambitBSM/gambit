#ifndef __wrapper_Parm_def_Pythia_8_212_h__
#define __wrapper_Parm_def_Pythia_8_212_h__

#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        
        // Wrappers for original constructors: 
        inline Parm::Parm(std::string nameIn, double defaultIn, bool hasMinIn, bool hasMaxIn, double minIn, double maxIn) :
            WrapperBase(__factory0(nameIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn)),
            name( get_BEptr()->name_ref__BOSS()),
            valNow( get_BEptr()->valNow_ref__BOSS()),
            valDefault( get_BEptr()->valDefault_ref__BOSS()),
            hasMin( get_BEptr()->hasMin_ref__BOSS()),
            hasMax( get_BEptr()->hasMax_ref__BOSS()),
            valMin( get_BEptr()->valMin_ref__BOSS()),
            valMax( get_BEptr()->valMax_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Parm::Parm(std::string nameIn, double defaultIn, bool hasMinIn, bool hasMaxIn, double minIn) :
            WrapperBase(__factory1(nameIn, defaultIn, hasMinIn, hasMaxIn, minIn)),
            name( get_BEptr()->name_ref__BOSS()),
            valNow( get_BEptr()->valNow_ref__BOSS()),
            valDefault( get_BEptr()->valDefault_ref__BOSS()),
            hasMin( get_BEptr()->hasMin_ref__BOSS()),
            hasMax( get_BEptr()->hasMax_ref__BOSS()),
            valMin( get_BEptr()->valMin_ref__BOSS()),
            valMax( get_BEptr()->valMax_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Parm::Parm(std::string nameIn, double defaultIn, bool hasMinIn, bool hasMaxIn) :
            WrapperBase(__factory2(nameIn, defaultIn, hasMinIn, hasMaxIn)),
            name( get_BEptr()->name_ref__BOSS()),
            valNow( get_BEptr()->valNow_ref__BOSS()),
            valDefault( get_BEptr()->valDefault_ref__BOSS()),
            hasMin( get_BEptr()->hasMin_ref__BOSS()),
            hasMax( get_BEptr()->hasMax_ref__BOSS()),
            valMin( get_BEptr()->valMin_ref__BOSS()),
            valMax( get_BEptr()->valMax_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Parm::Parm(std::string nameIn, double defaultIn, bool hasMinIn) :
            WrapperBase(__factory3(nameIn, defaultIn, hasMinIn)),
            name( get_BEptr()->name_ref__BOSS()),
            valNow( get_BEptr()->valNow_ref__BOSS()),
            valDefault( get_BEptr()->valDefault_ref__BOSS()),
            hasMin( get_BEptr()->hasMin_ref__BOSS()),
            hasMax( get_BEptr()->hasMax_ref__BOSS()),
            valMin( get_BEptr()->valMin_ref__BOSS()),
            valMax( get_BEptr()->valMax_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Parm::Parm(std::string nameIn, double defaultIn) :
            WrapperBase(__factory4(nameIn, defaultIn)),
            name( get_BEptr()->name_ref__BOSS()),
            valNow( get_BEptr()->valNow_ref__BOSS()),
            valDefault( get_BEptr()->valDefault_ref__BOSS()),
            hasMin( get_BEptr()->hasMin_ref__BOSS()),
            hasMax( get_BEptr()->hasMax_ref__BOSS()),
            valMin( get_BEptr()->valMin_ref__BOSS()),
            valMax( get_BEptr()->valMax_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Parm::Parm(std::string nameIn) :
            WrapperBase(__factory5(nameIn)),
            name( get_BEptr()->name_ref__BOSS()),
            valNow( get_BEptr()->valNow_ref__BOSS()),
            valDefault( get_BEptr()->valDefault_ref__BOSS()),
            hasMin( get_BEptr()->hasMin_ref__BOSS()),
            hasMax( get_BEptr()->hasMax_ref__BOSS()),
            valMin( get_BEptr()->valMin_ref__BOSS()),
            valMax( get_BEptr()->valMax_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Parm::Parm() :
            WrapperBase(__factory6()),
            name( get_BEptr()->name_ref__BOSS()),
            valNow( get_BEptr()->valNow_ref__BOSS()),
            valDefault( get_BEptr()->valDefault_ref__BOSS()),
            hasMin( get_BEptr()->hasMin_ref__BOSS()),
            hasMax( get_BEptr()->hasMax_ref__BOSS()),
            valMin( get_BEptr()->valMin_ref__BOSS()),
            valMax( get_BEptr()->valMax_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Parm::Parm(Abstract_Parm* in) :
            WrapperBase(in),
            name( get_BEptr()->name_ref__BOSS()),
            valNow( get_BEptr()->valNow_ref__BOSS()),
            valDefault( get_BEptr()->valDefault_ref__BOSS()),
            hasMin( get_BEptr()->hasMin_ref__BOSS()),
            hasMax( get_BEptr()->hasMax_ref__BOSS()),
            valMin( get_BEptr()->valMin_ref__BOSS()),
            valMax( get_BEptr()->valMax_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Parm::Parm(const Parm& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            name( get_BEptr()->name_ref__BOSS()),
            valNow( get_BEptr()->valNow_ref__BOSS()),
            valDefault( get_BEptr()->valDefault_ref__BOSS()),
            hasMin( get_BEptr()->hasMin_ref__BOSS()),
            hasMax( get_BEptr()->hasMax_ref__BOSS()),
            valMin( get_BEptr()->valMin_ref__BOSS()),
            valMax( get_BEptr()->valMax_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Parm& Parm::operator=(const Parm& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Parm::~Parm()
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
        inline Abstract_Parm* Pythia8::Parm::get_BEptr() const
        {
            return dynamic_cast<Abstract_Parm*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Parm_def_Pythia_8_212_h__ */
