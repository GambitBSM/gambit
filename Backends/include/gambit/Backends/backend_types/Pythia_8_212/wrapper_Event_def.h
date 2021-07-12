#ifndef __wrapper_Event_def_Pythia_8_212_h__
#define __wrapper_Event_def_Pythia_8_212_h__

#include <string>
#include <ostream>
#include <vector>
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Particle_decl.h"
#include "wrapper_Vec4_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void Event::init(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > headerIn, Pythia8::ParticleData* particleDataPtrIn, int startColTagIn)
        {
            get_BEptr()->init__BOSS(headerIn, (*particleDataPtrIn).get_BEptr(), startColTagIn);
        }
        
        inline void Event::init(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > headerIn, Pythia8::ParticleData* particleDataPtrIn)
        {
            get_BEptr()->init__BOSS(headerIn, (*particleDataPtrIn).get_BEptr());
        }
        
        inline void Event::init(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > headerIn)
        {
            get_BEptr()->init__BOSS(headerIn);
        }
        
        inline void Event::init()
        {
            get_BEptr()->init__BOSS();
        }
        
        inline void Event::clear()
        {
            get_BEptr()->clear();
        }
        
        inline void Event::reset()
        {
            get_BEptr()->reset();
        }
        
        inline Pythia8::Particle& Event::operator[](int i)
        {
            return get_BEptr()->operator_square_bracket_pair__BOSS(i).get_init_wref();
        }
        
        inline const Pythia8::Particle& Event::operator[](int i) const
        {
            return const_cast<Pythia8::Abstract_Particle&>(const_cast<const Abstract_Event*>(get_BEptr())->operator_square_bracket_pair__BOSS(i)).get_init_wref();
        }
        
        inline Pythia8::Particle& Event::front()
        {
            return get_BEptr()->front__BOSS().get_init_wref();
        }
        
        inline Pythia8::Particle& Event::at(int i)
        {
            return get_BEptr()->at__BOSS(i).get_init_wref();
        }
        
        inline Pythia8::Particle& Event::back()
        {
            return get_BEptr()->back__BOSS().get_init_wref();
        }
        
        inline int Event::size() const
        {
            return get_BEptr()->size();
        }
        
        inline int Event::append(Pythia8::Particle entryIn)
        {
            return get_BEptr()->append__BOSS(*entryIn.get_BEptr());
        }
        
        inline int Event::append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, double px, double py, double pz, double e, double m, double scaleIn, double polIn)
        {
            return get_BEptr()->append(id, status, mother1, mother2, daughter1, daughter2, col, acol, px, py, pz, e, m, scaleIn, polIn);
        }
        
        inline int Event::append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, double px, double py, double pz, double e, double m, double scaleIn)
        {
            return get_BEptr()->append__BOSS(id, status, mother1, mother2, daughter1, daughter2, col, acol, px, py, pz, e, m, scaleIn);
        }
        
        inline int Event::append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, double px, double py, double pz, double e, double m)
        {
            return get_BEptr()->append__BOSS(id, status, mother1, mother2, daughter1, daughter2, col, acol, px, py, pz, e, m);
        }
        
        inline int Event::append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, double px, double py, double pz, double e)
        {
            return get_BEptr()->append__BOSS(id, status, mother1, mother2, daughter1, daughter2, col, acol, px, py, pz, e);
        }
        
        inline int Event::append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, Pythia8::Vec4 p, double m, double scaleIn, double polIn)
        {
            return get_BEptr()->append__BOSS(id, status, mother1, mother2, daughter1, daughter2, col, acol, *p.get_BEptr(), m, scaleIn, polIn);
        }
        
        inline int Event::append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, Pythia8::Vec4 p, double m, double scaleIn)
        {
            return get_BEptr()->append__BOSS(id, status, mother1, mother2, daughter1, daughter2, col, acol, *p.get_BEptr(), m, scaleIn);
        }
        
        inline int Event::append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, Pythia8::Vec4 p, double m)
        {
            return get_BEptr()->append__BOSS(id, status, mother1, mother2, daughter1, daughter2, col, acol, *p.get_BEptr(), m);
        }
        
        inline int Event::append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, Pythia8::Vec4 p)
        {
            return get_BEptr()->append__BOSS(id, status, mother1, mother2, daughter1, daughter2, col, acol, *p.get_BEptr());
        }
        
        inline int Event::append(int id, int status, int col, int acol, double px, double py, double pz, double e, double m, double scaleIn, double polIn)
        {
            return get_BEptr()->append(id, status, col, acol, px, py, pz, e, m, scaleIn, polIn);
        }
        
        inline int Event::append(int id, int status, int col, int acol, double px, double py, double pz, double e, double m, double scaleIn)
        {
            return get_BEptr()->append__BOSS(id, status, col, acol, px, py, pz, e, m, scaleIn);
        }
        
        inline int Event::append(int id, int status, int col, int acol, double px, double py, double pz, double e, double m)
        {
            return get_BEptr()->append__BOSS(id, status, col, acol, px, py, pz, e, m);
        }
        
        inline int Event::append(int id, int status, int col, int acol, double px, double py, double pz, double e)
        {
            return get_BEptr()->append__BOSS(id, status, col, acol, px, py, pz, e);
        }
        
        inline int Event::append(int id, int status, int col, int acol, Pythia8::Vec4 p, double m, double scaleIn, double polIn)
        {
            return get_BEptr()->append__BOSS(id, status, col, acol, *p.get_BEptr(), m, scaleIn, polIn);
        }
        
        inline int Event::append(int id, int status, int col, int acol, Pythia8::Vec4 p, double m, double scaleIn)
        {
            return get_BEptr()->append__BOSS(id, status, col, acol, *p.get_BEptr(), m, scaleIn);
        }
        
        inline int Event::append(int id, int status, int col, int acol, Pythia8::Vec4 p, double m)
        {
            return get_BEptr()->append__BOSS(id, status, col, acol, *p.get_BEptr(), m);
        }
        
        inline int Event::append(int id, int status, int col, int acol, Pythia8::Vec4 p)
        {
            return get_BEptr()->append__BOSS(id, status, col, acol, *p.get_BEptr());
        }
        
        inline void Event::setEvtPtr(int iSet)
        {
            get_BEptr()->setEvtPtr(iSet);
        }
        
        inline void Event::setEvtPtr()
        {
            get_BEptr()->setEvtPtr__BOSS();
        }
        
        inline int Event::copy(int iCopy, int newStatus)
        {
            return get_BEptr()->copy(iCopy, newStatus);
        }
        
        inline int Event::copy(int iCopy)
        {
            return get_BEptr()->copy__BOSS(iCopy);
        }
        
        inline void Event::list(int precision) const
        {
            get_BEptr()->list(precision);
        }
        
        inline void Event::list() const
        {
            get_BEptr()->list__BOSS();
        }
        
        inline void Event::list(::std::basic_ostream<char, std::char_traits<char> >& os, int precision) const
        {
            get_BEptr()->list(os, precision);
        }
        
        inline void Event::list(::std::basic_ostream<char, std::char_traits<char> >& os) const
        {
            get_BEptr()->list__BOSS(os);
        }
        
        inline void Event::list(bool showScaleAndVertex, bool showMothersAndDaughters, int precision) const
        {
            get_BEptr()->list(showScaleAndVertex, showMothersAndDaughters, precision);
        }
        
        inline void Event::list(bool showScaleAndVertex, bool showMothersAndDaughters) const
        {
            get_BEptr()->list__BOSS(showScaleAndVertex, showMothersAndDaughters);
        }
        
        inline void Event::list(bool showScaleAndVertex) const
        {
            get_BEptr()->list__BOSS(showScaleAndVertex);
        }
        
        inline void Event::list(bool showScaleAndVertex, bool showMothersAndDaughters, ::std::basic_ostream<char, std::char_traits<char> >& os, int precision) const
        {
            get_BEptr()->list(showScaleAndVertex, showMothersAndDaughters, os, precision);
        }
        
        inline void Event::list(bool showScaleAndVertex, bool showMothersAndDaughters, ::std::basic_ostream<char, std::char_traits<char> >& os) const
        {
            get_BEptr()->list__BOSS(showScaleAndVertex, showMothersAndDaughters, os);
        }
        
        inline void Event::popBack(int nRemove)
        {
            get_BEptr()->popBack(nRemove);
        }
        
        inline void Event::popBack()
        {
            get_BEptr()->popBack__BOSS();
        }
        
        inline void Event::remove(int iFirst, int iLast)
        {
            get_BEptr()->remove(iFirst, iLast);
        }
        
        inline void Event::restorePtrs()
        {
            get_BEptr()->restorePtrs();
        }
        
        inline void Event::saveSize()
        {
            get_BEptr()->saveSize();
        }
        
        inline void Event::restoreSize()
        {
            get_BEptr()->restoreSize();
        }
        
        inline int Event::savedSizeValue()
        {
            return get_BEptr()->savedSizeValue();
        }
        
        inline void Event::initColTag(int colTag)
        {
            get_BEptr()->initColTag(colTag);
        }
        
        inline void Event::initColTag()
        {
            get_BEptr()->initColTag__BOSS();
        }
        
        inline int Event::lastColTag() const
        {
            return get_BEptr()->lastColTag();
        }
        
        inline int Event::nextColTag()
        {
            return get_BEptr()->nextColTag();
        }
        
        inline void Event::scale(double scaleIn)
        {
            get_BEptr()->scale(scaleIn);
        }
        
        inline double Event::scale() const
        {
            return get_BEptr()->scale();
        }
        
        inline void Event::scaleSecond(double scaleSecondIn)
        {
            get_BEptr()->scaleSecond(scaleSecondIn);
        }
        
        inline double Event::scaleSecond() const
        {
            return get_BEptr()->scaleSecond();
        }
        
        inline ::std::vector<int, std::allocator<int> > Event::daughterList(int i) const
        {
            return get_BEptr()->daughterList(i);
        }
        
        inline void Event::rot(double theta, double phi)
        {
            get_BEptr()->rot(theta, phi);
        }
        
        inline void Event::bst(double betaX, double betaY, double betaZ)
        {
            get_BEptr()->bst(betaX, betaY, betaZ);
        }
        
        inline void Event::bst(double betaX, double betaY, double betaZ, double gamma)
        {
            get_BEptr()->bst(betaX, betaY, betaZ, gamma);
        }
        
        inline void Event::bst(const Pythia8::Vec4& vec)
        {
            get_BEptr()->bst__BOSS(*vec.get_BEptr());
        }
        
        inline void Event::clearJunctions()
        {
            get_BEptr()->clearJunctions();
        }
        
        inline int Event::appendJunction(int kind, int col0, int col1, int col2)
        {
            return get_BEptr()->appendJunction(kind, col0, col1, col2);
        }
        
        inline int Event::sizeJunction() const
        {
            return get_BEptr()->sizeJunction();
        }
        
        inline bool Event::remainsJunction(int i) const
        {
            return get_BEptr()->remainsJunction(i);
        }
        
        inline void Event::remainsJunction(int i, bool remainsIn)
        {
            get_BEptr()->remainsJunction(i, remainsIn);
        }
        
        inline int Event::kindJunction(int i) const
        {
            return get_BEptr()->kindJunction(i);
        }
        
        inline int Event::colJunction(int i, int j) const
        {
            return get_BEptr()->colJunction(i, j);
        }
        
        inline void Event::colJunction(int i, int j, int colIn)
        {
            get_BEptr()->colJunction(i, j, colIn);
        }
        
        inline int Event::endColJunction(int i, int j) const
        {
            return get_BEptr()->endColJunction(i, j);
        }
        
        inline void Event::endColJunction(int i, int j, int endColIn)
        {
            get_BEptr()->endColJunction(i, j, endColIn);
        }
        
        inline int Event::statusJunction(int i, int j) const
        {
            return get_BEptr()->statusJunction(i, j);
        }
        
        inline void Event::statusJunction(int i, int j, int statusIn)
        {
            get_BEptr()->statusJunction(i, j, statusIn);
        }
        
        inline void Event::eraseJunction(int i)
        {
            get_BEptr()->eraseJunction(i);
        }
        
        inline void Event::saveJunctionSize()
        {
            get_BEptr()->saveJunctionSize();
        }
        
        inline void Event::restoreJunctionSize()
        {
            get_BEptr()->restoreJunctionSize();
        }
        
        inline void Event::listJunctions(::std::basic_ostream<char, std::char_traits<char> >& os) const
        {
            get_BEptr()->listJunctions(os);
        }
        
        inline void Event::listJunctions() const
        {
            get_BEptr()->listJunctions__BOSS();
        }
        
        inline void Event::savePartonLevelSize()
        {
            get_BEptr()->savePartonLevelSize();
        }
        
        inline Pythia8::Event& Event::operator+=(const Pythia8::Event& addEvent)
        {
            return get_BEptr()->operator_plus_equal__BOSS(*addEvent.get_BEptr()).get_init_wref();
        }
        
        
        // Wrappers for original constructors: 
        inline Event::Event(int capacity) :
            WrapperBase(__factory0(capacity))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Event::Event() :
            WrapperBase(__factory1())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Event::Event(Abstract_Event* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Event::Event(const Event& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Event& Event::operator=(const Event& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Event::~Event()
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
        inline Abstract_Event* Pythia8::Event::get_BEptr() const
        {
            return dynamic_cast<Abstract_Event*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Event_def_Pythia_8_212_h__ */
