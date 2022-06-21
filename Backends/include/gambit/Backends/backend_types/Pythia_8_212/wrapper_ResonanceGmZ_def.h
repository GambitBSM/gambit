#ifndef __wrapper_ResonanceGmZ_def_Pythia_8_212_h__
#define __wrapper_ResonanceGmZ_def_Pythia_8_212_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        
        // Wrappers for original constructors: 
        inline ResonanceGmZ::ResonanceGmZ(int idResIn) :
            ResonanceWidths(__factory0(idResIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline ResonanceGmZ::ResonanceGmZ(Abstract_ResonanceGmZ* in) :
            ResonanceWidths(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline ResonanceGmZ::ResonanceGmZ(const ResonanceGmZ& in) :
            ResonanceWidths(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline ResonanceGmZ& ResonanceGmZ::operator=(const ResonanceGmZ& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline ResonanceGmZ::~ResonanceGmZ()
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
        inline Abstract_ResonanceGmZ* Pythia8::ResonanceGmZ::get_BEptr() const
        {
            return dynamic_cast<Abstract_ResonanceGmZ*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ResonanceGmZ_def_Pythia_8_212_h__ */
