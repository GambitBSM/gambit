#ifndef __wrapper_AlphaEM_def_Pythia_EM_8_212_h__
#define __wrapper_AlphaEM_def_Pythia_EM_8_212_h__

#include "wrapper_Settings_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void AlphaEM::init(int orderIn, Pythia8::Settings* settingsPtr)
        {
            get_BEptr()->init__BOSS(orderIn, (*settingsPtr).get_BEptr());
        }
        
        inline double AlphaEM::alphaEM(double scale2)
        {
            return get_BEptr()->alphaEM(scale2);
        }
        
        
        // Wrappers for original constructors: 
        inline Pythia8::AlphaEM::AlphaEM() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Pythia8::AlphaEM::AlphaEM(Pythia8::Abstract_AlphaEM* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Pythia8::AlphaEM::AlphaEM(const AlphaEM& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Pythia8::AlphaEM& AlphaEM::operator=(const AlphaEM& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Pythia8::AlphaEM::~AlphaEM()
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
        inline Pythia8::Abstract_AlphaEM* Pythia8::AlphaEM::get_BEptr() const
        {
            return dynamic_cast<Pythia8::Abstract_AlphaEM*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_AlphaEM_def_Pythia_EM_8_212_h__ */
