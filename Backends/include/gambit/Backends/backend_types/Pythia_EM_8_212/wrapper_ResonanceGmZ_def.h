#ifndef __wrapper_ResonanceGmZ_def_Pythia_EM_8_212_h__
#define __wrapper_ResonanceGmZ_def_Pythia_EM_8_212_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        
        // Wrappers for original constructors: 
        inline Pythia8::ResonanceGmZ::ResonanceGmZ(int idResIn) :
            WrapperBase(__factory0(idResIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Pythia8::ResonanceGmZ::ResonanceGmZ(Pythia8::Abstract_ResonanceGmZ* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Pythia8::ResonanceGmZ::ResonanceGmZ(const ResonanceGmZ& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Pythia8::ResonanceGmZ& ResonanceGmZ::operator=(const ResonanceGmZ& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Pythia8::ResonanceGmZ::~ResonanceGmZ()
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
        inline Pythia8::Abstract_ResonanceGmZ* Pythia8::ResonanceGmZ::get_BEptr() const
        {
            return dynamic_cast<Pythia8::Abstract_ResonanceGmZ*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ResonanceGmZ_def_Pythia_EM_8_212_h__ */
