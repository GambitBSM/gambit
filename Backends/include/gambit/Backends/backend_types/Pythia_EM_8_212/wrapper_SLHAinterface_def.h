#ifndef __wrapper_SLHAinterface_def_Pythia_EM_8_212_h__
#define __wrapper_SLHAinterface_def_Pythia_EM_8_212_h__

#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Couplings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include <sstream>
#include "wrapper_SusyLesHouches_decl.h"
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
        
        inline void SLHAinterface::init(Pythia8::Settings& settings, Pythia8::Rndm* rndmPtr, Pythia8::Couplings* couplingsPtrIn, Pythia8::ParticleData* particleDataPtr, bool& useSHLAcouplings, ::std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >& ParticleDataBuffer)
        {
            get_BEptr()->init__BOSS(*settings.get_BEptr(), (*rndmPtr).get_BEptr(), (*couplingsPtrIn).get_BEptr(), (*particleDataPtr).get_BEptr(), useSHLAcouplings, ParticleDataBuffer);
        }
        
        inline bool SLHAinterface::initSLHA(Pythia8::Settings& settings, Pythia8::ParticleData* particleDataPtr)
        {
            return get_BEptr()->initSLHA__BOSS(*settings.get_BEptr(), (*particleDataPtr).get_BEptr());
        }
        
        inline void SLHAinterface::pythia2slha(Pythia8::ParticleData* particleDataPtr)
        {
            get_BEptr()->pythia2slha__BOSS((*particleDataPtr).get_BEptr());
        }
        
        
        // Wrappers for original constructors: 
        inline Pythia8::SLHAinterface::SLHAinterface() :
            WrapperBase(__factory0()),
            slha( get_BEptr()->slha_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            meMode( get_BEptr()->meMode_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Pythia8::SLHAinterface::SLHAinterface(Pythia8::Abstract_SLHAinterface* in) :
            WrapperBase(in),
            slha( get_BEptr()->slha_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            meMode( get_BEptr()->meMode_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Pythia8::SLHAinterface::SLHAinterface(const SLHAinterface& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            slha( get_BEptr()->slha_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            meMode( get_BEptr()->meMode_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Pythia8::SLHAinterface& SLHAinterface::operator=(const SLHAinterface& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Pythia8::SLHAinterface::~SLHAinterface()
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
        inline Pythia8::Abstract_SLHAinterface* Pythia8::SLHAinterface::get_BEptr() const
        {
            return dynamic_cast<Pythia8::Abstract_SLHAinterface*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SLHAinterface_def_Pythia_EM_8_212_h__ */
