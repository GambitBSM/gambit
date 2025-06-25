#ifndef __wrapper_SLHAinterface_def_Pythia_8_312_h__
#define __wrapper_SLHAinterface_def_Pythia_8_312_h__

#include <sstream>
#include "wrapper_Info_decl.h"
#include "wrapper_SusyLesHouches_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Logger_decl.h"
#include "wrapper_CoupSM_decl.h"
#include "wrapper_CoupSUSY_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void SLHAinterface::setPtr(Pythia8::Info* infoPtrIn)
        {
            get_BEptr()->setPtr__BOSS((*infoPtrIn).get_BEptr());
        }
        
        inline void SLHAinterface::init(bool& useSHLAcouplings, std::stringstream& ParticleDataBuffer)
        {
            get_BEptr()->init(useSHLAcouplings, ParticleDataBuffer);
        }
        
        inline bool SLHAinterface::initSLHA()
        {
            return get_BEptr()->initSLHA();
        }
        
        inline void SLHAinterface::pythia2slha()
        {
            get_BEptr()->pythia2slha();
        }
        
        
        // Wrappers for original constructors: 
        inline SLHAinterface::SLHAinterface() :
            WrapperBase(__factory0()),
            slha( get_BEptr()->slha_ref__BOSS().get_init_wref()),
            meMode( get_BEptr()->meMode_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline SLHAinterface::SLHAinterface(Abstract_SLHAinterface* in) :
            WrapperBase(in),
            slha( get_BEptr()->slha_ref__BOSS().get_init_wref()),
            meMode( get_BEptr()->meMode_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline SLHAinterface::SLHAinterface(const SLHAinterface& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            slha( get_BEptr()->slha_ref__BOSS().get_init_wref()),
            meMode( get_BEptr()->meMode_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline SLHAinterface& SLHAinterface::operator=(const SLHAinterface& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline SLHAinterface::~SLHAinterface()
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
        inline Abstract_SLHAinterface* Pythia8::SLHAinterface::get_BEptr() const
        {
            return dynamic_cast<Abstract_SLHAinterface*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SLHAinterface_def_Pythia_8_312_h__ */
