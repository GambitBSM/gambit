#ifndef __wrapper_SlowJet_def_Pythia_8_212_h__
#define __wrapper_SlowJet_def_Pythia_8_212_h__

#include <ostream>
#include <vector>
#include "wrapper_Event_decl.h"
#include "wrapper_Vec4_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline bool SlowJet::analyze(const Pythia8::Event& event)
        {
            return get_BEptr()->analyze__BOSS(*event.get_BEptr());
        }
        
        inline bool SlowJet::setup(const Pythia8::Event& event)
        {
            return get_BEptr()->setup__BOSS(*event.get_BEptr());
        }
        
        inline bool SlowJet::doStep()
        {
            return get_BEptr()->doStep();
        }
        
        inline bool SlowJet::doNSteps(int nStep)
        {
            return get_BEptr()->doNSteps(nStep);
        }
        
        inline bool SlowJet::stopAtN(int nStop)
        {
            return get_BEptr()->stopAtN(nStop);
        }
        
        inline int SlowJet::sizeOrig() const
        {
            return get_BEptr()->sizeOrig();
        }
        
        inline int SlowJet::sizeJet() const
        {
            return get_BEptr()->sizeJet();
        }
        
        inline int SlowJet::sizeAll() const
        {
            return get_BEptr()->sizeAll();
        }
        
        inline double SlowJet::pT(int i) const
        {
            return get_BEptr()->pT(i);
        }
        
        inline double SlowJet::y(int i) const
        {
            return get_BEptr()->y(i);
        }
        
        inline double SlowJet::phi(int i) const
        {
            return get_BEptr()->phi(i);
        }
        
        inline Pythia8::Vec4 SlowJet::p(int i) const
        {
            return Pythia8::Vec4( const_cast<const Abstract_SlowJet*>(get_BEptr())->p__BOSS(i) );
        }
        
        inline double SlowJet::m(int i) const
        {
            return get_BEptr()->m(i);
        }
        
        inline int SlowJet::multiplicity(int i) const
        {
            return get_BEptr()->multiplicity(i);
        }
        
        inline int SlowJet::iNext() const
        {
            return get_BEptr()->iNext();
        }
        
        inline int SlowJet::jNext() const
        {
            return get_BEptr()->jNext();
        }
        
        inline double SlowJet::dNext() const
        {
            return get_BEptr()->dNext();
        }
        
        inline void SlowJet::list(bool listAll, std::ostream& os) const
        {
            get_BEptr()->list(listAll, os);
        }
        
        inline void SlowJet::list(bool listAll) const
        {
            get_BEptr()->list__BOSS(listAll);
        }
        
        inline void SlowJet::list() const
        {
            get_BEptr()->list__BOSS();
        }
        
        inline ::std::vector<int> SlowJet::constituents(int j)
        {
            return get_BEptr()->constituents(j);
        }
        
        inline ::std::vector<int> SlowJet::clusConstituents(int j)
        {
            return get_BEptr()->clusConstituents(j);
        }
        
        inline int SlowJet::jetAssignment(int i)
        {
            return get_BEptr()->jetAssignment(i);
        }
        
        inline void SlowJet::removeJet(int i)
        {
            get_BEptr()->removeJet(i);
        }
        
        
        // Wrappers for original constructors: 
        inline SlowJet::SlowJet(int powerIn, double Rin, double pTjetMinIn, double etaMaxIn, int selectIn, int massSetIn) :
            WrapperBase(__factory0(powerIn, Rin, pTjetMinIn, etaMaxIn, selectIn, massSetIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline SlowJet::SlowJet(int powerIn, double Rin, double pTjetMinIn, double etaMaxIn, int selectIn) :
            WrapperBase(__factory1(powerIn, Rin, pTjetMinIn, etaMaxIn, selectIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline SlowJet::SlowJet(int powerIn, double Rin, double pTjetMinIn, double etaMaxIn) :
            WrapperBase(__factory2(powerIn, Rin, pTjetMinIn, etaMaxIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline SlowJet::SlowJet(int powerIn, double Rin, double pTjetMinIn) :
            WrapperBase(__factory3(powerIn, Rin, pTjetMinIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline SlowJet::SlowJet(int powerIn, double Rin) :
            WrapperBase(__factory4(powerIn, Rin))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline SlowJet::SlowJet(Abstract_SlowJet* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline SlowJet::SlowJet(const SlowJet& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline SlowJet& SlowJet::operator=(const SlowJet& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline SlowJet::~SlowJet()
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
        inline Abstract_SlowJet* Pythia8::SlowJet::get_BEptr() const
        {
            return dynamic_cast<Abstract_SlowJet*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SlowJet_def_Pythia_8_212_h__ */
