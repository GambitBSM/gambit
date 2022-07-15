#ifndef __abstract_Event_Pythia_8_212_h__
#define __abstract_Event_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Particle_decl.h"
#include "wrapper_Vec4_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Event : public virtual AbstractBase
        {
            public:
    
                virtual Pythia8::Abstract_Event& operator_equal__BOSS(const Pythia8::Abstract_Event&) =0;
    
                virtual void init__BOSS(::std::basic_string<char>, Pythia8::Abstract_ParticleData*, int) =0;
    
                virtual void init__BOSS(::std::basic_string<char>, Pythia8::Abstract_ParticleData*) =0;
    
                virtual void init__BOSS(::std::basic_string<char>) =0;
    
                virtual void init__BOSS() =0;
    
                virtual void clear() =0;
    
                virtual void reset() =0;
    
                virtual Pythia8::Abstract_Particle& operator_square_bracket_pair__BOSS(int) =0;
    
                virtual const Pythia8::Abstract_Particle& operator_square_bracket_pair__BOSS(int) const =0;
    
                virtual Pythia8::Abstract_Particle& front__BOSS() =0;
    
                virtual Pythia8::Abstract_Particle& at__BOSS(int) =0;
    
                virtual Pythia8::Abstract_Particle& back__BOSS() =0;
    
                virtual int size() const =0;
    
                virtual int append__BOSS(Pythia8::Abstract_Particle&) =0;
    
                virtual int append(int, int, int, int, int, int, int, int, double, double, double, double, double, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, int, int, int, int, double, double, double, double, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, int, int, int, int, double, double, double, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, int, int, int, int, double, double, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, int, int, int, int, Pythia8::Abstract_Vec4&, double, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, int, int, int, int, Pythia8::Abstract_Vec4&, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, int, int, int, int, Pythia8::Abstract_Vec4&, double) =0;
    
                virtual int append__BOSS(int, int, int, int, int, int, int, int, Pythia8::Abstract_Vec4&) =0;
    
                virtual int append(int, int, int, int, double, double, double, double, double, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, double, double, double, double, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, double, double, double, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, double, double, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, Pythia8::Abstract_Vec4&, double, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, Pythia8::Abstract_Vec4&, double, double) =0;
    
                virtual int append__BOSS(int, int, int, int, Pythia8::Abstract_Vec4&, double) =0;
    
                virtual int append__BOSS(int, int, int, int, Pythia8::Abstract_Vec4&) =0;
    
                virtual void setEvtPtr(int) =0;
    
                virtual void setEvtPtr__BOSS() =0;
    
                virtual int copy(int, int) =0;
    
                virtual int copy__BOSS(int) =0;
    
                virtual void list(int) const =0;
    
                virtual void list__BOSS() const =0;
    
                virtual void list(::std::basic_ostream<char>&, int) const =0;
    
                virtual void list__BOSS(::std::basic_ostream<char>&) const =0;
    
                virtual void list(bool, bool, int) const =0;
    
                virtual void list__BOSS(bool, bool) const =0;
    
                virtual void list__BOSS(bool) const =0;
    
                virtual void list(bool, bool, ::std::basic_ostream<char>&, int) const =0;
    
                virtual void list__BOSS(bool, bool, ::std::basic_ostream<char>&) const =0;
    
                virtual void popBack(int) =0;
    
                virtual void popBack__BOSS() =0;
    
                virtual void remove(int, int) =0;
    
                virtual void restorePtrs() =0;
    
                virtual void saveSize() =0;
    
                virtual void restoreSize() =0;
    
                virtual int savedSizeValue() =0;
    
                virtual void initColTag(int) =0;
    
                virtual void initColTag__BOSS() =0;
    
                virtual int lastColTag() const =0;
    
                virtual int nextColTag() =0;
    
                virtual void scale(double) =0;
    
                virtual double scale() const =0;
    
                virtual void scaleSecond(double) =0;
    
                virtual double scaleSecond() const =0;
    
                virtual ::std::vector<int> daughterList(int) const =0;
    
                virtual void rot(double, double) =0;
    
                virtual void bst(double, double, double) =0;
    
                virtual void bst(double, double, double, double) =0;
    
                virtual void bst__BOSS(const Pythia8::Abstract_Vec4&) =0;
    
                virtual void clearJunctions() =0;
    
                virtual int appendJunction(int, int, int, int) =0;
    
                virtual int sizeJunction() const =0;
    
                virtual bool remainsJunction(int) const =0;
    
                virtual void remainsJunction(int, bool) =0;
    
                virtual int kindJunction(int) const =0;
    
                virtual int colJunction(int, int) const =0;
    
                virtual void colJunction(int, int, int) =0;
    
                virtual int endColJunction(int, int) const =0;
    
                virtual void endColJunction(int, int, int) =0;
    
                virtual int statusJunction(int, int) const =0;
    
                virtual void statusJunction(int, int, int) =0;
    
                virtual void eraseJunction(int) =0;
    
                virtual void saveJunctionSize() =0;
    
                virtual void restoreJunctionSize() =0;
    
                virtual void listJunctions(::std::basic_ostream<char>&) const =0;
    
                virtual void listJunctions__BOSS() const =0;
    
                virtual void savePartonLevelSize() =0;
    
                virtual Pythia8::Abstract_Event& operator_plus_equal__BOSS(const Pythia8::Abstract_Event&) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Event*) =0;
                virtual Abstract_Event* pointer_copy__BOSS() =0;
    
            private:
                Event* wptr;
                bool delete_wrapper;
            public:
                Event* get_wptr() { return wptr; }
                void set_wptr(Event* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Event()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Event(const Abstract_Event&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Event& operator=(const Abstract_Event&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Event* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Event& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Event() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Event_Pythia_8_212_h__ */
