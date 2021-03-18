#ifndef __abstract_SlowJet_Pythia_8_212_h__
#define __abstract_SlowJet_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <ostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Vec4_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_SlowJet : public virtual AbstractBase
        {
            public:
    
                virtual bool analyze__BOSS(const Pythia8::Abstract_Event&) =0;
    
                virtual bool setup__BOSS(const Pythia8::Abstract_Event&) =0;
    
                virtual bool doStep() =0;
    
                virtual bool doNSteps(int) =0;
    
                virtual bool stopAtN(int) =0;
    
                virtual int sizeOrig() const =0;
    
                virtual int sizeJet() const =0;
    
                virtual int sizeAll() const =0;
    
                virtual double pT(int) const =0;
    
                virtual double y(int) const =0;
    
                virtual double phi(int) const =0;
    
                virtual Pythia8::Abstract_Vec4* p__BOSS(int) const =0;
    
                virtual double m(int) const =0;
    
                virtual int multiplicity(int) const =0;
    
                virtual int iNext() const =0;
    
                virtual int jNext() const =0;
    
                virtual double dNext() const =0;
    
                virtual void list(bool, ::std::basic_ostream<char, std::char_traits<char> >&) const =0;
    
                virtual void list__BOSS(bool) const =0;
    
                virtual void list__BOSS() const =0;
    
                virtual ::std::vector<int, std::allocator<int> > constituents(int) =0;
    
                virtual ::std::vector<int, std::allocator<int> > clusConstituents(int) =0;
    
                virtual int jetAssignment(int) =0;
    
                virtual void removeJet(int) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_SlowJet*) =0;
                virtual Abstract_SlowJet* pointer_copy__BOSS() =0;
    
            private:
                SlowJet* wptr;
                bool delete_wrapper;
            public:
                SlowJet* get_wptr() { return wptr; }
                void set_wptr(SlowJet* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_SlowJet()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_SlowJet(const Abstract_SlowJet&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_SlowJet& operator=(const Abstract_SlowJet&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                SlowJet* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                SlowJet& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_SlowJet() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_SlowJet_Pythia_8_212_h__ */
