#ifndef __abstract_Hist_Pythia_8_212_h__
#define __abstract_Hist_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Hist : public virtual AbstractBase
        {
            public:
    
                virtual Pythia8::Abstract_Hist& operator_equal__BOSS(const Pythia8::Abstract_Hist&) =0;
    
                virtual void book(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int, double, double) =0;
    
                virtual void book__BOSS(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int, double) =0;
    
                virtual void book__BOSS(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int) =0;
    
                virtual void book__BOSS(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >) =0;
    
                virtual void book__BOSS() =0;
    
                virtual void name(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >) =0;
    
                virtual void name__BOSS() =0;
    
                virtual void null() =0;
    
                virtual void fill(double, double) =0;
    
                virtual void fill__BOSS(double) =0;
    
                virtual void table(::std::basic_ostream<char, std::char_traits<char> >&, bool, bool) const =0;
    
                virtual void table__BOSS(::std::basic_ostream<char, std::char_traits<char> >&, bool) const =0;
    
                virtual void table__BOSS(::std::basic_ostream<char, std::char_traits<char> >&) const =0;
    
                virtual void table__BOSS() const =0;
    
                virtual void table(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >, bool, bool) const =0;
    
                virtual void table__BOSS(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >, bool) const =0;
    
                virtual void table__BOSS(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >) const =0;
    
                virtual double getBinContent(int) const =0;
    
                virtual int getEntries() const =0;
    
                virtual bool sameSize__BOSS(const Pythia8::Abstract_Hist&) const =0;
    
                virtual void takeLog(bool) =0;
    
                virtual void takeLog__BOSS() =0;
    
                virtual void takeSqrt() =0;
    
                virtual Pythia8::Abstract_Hist& operator_plus_equal__BOSS(const Pythia8::Abstract_Hist&) =0;
    
                virtual Pythia8::Abstract_Hist& operator_minus_equal__BOSS(const Pythia8::Abstract_Hist&) =0;
    
                virtual Pythia8::Abstract_Hist& operator_asterix_equal__BOSS(const Pythia8::Abstract_Hist&) =0;
    
                virtual Pythia8::Abstract_Hist& operator_slash_equal__BOSS(const Pythia8::Abstract_Hist&) =0;
    
                virtual Pythia8::Abstract_Hist& operator_plus_equal__BOSS(double) =0;
    
                virtual Pythia8::Abstract_Hist& operator_minus_equal__BOSS(double) =0;
    
                virtual Pythia8::Abstract_Hist& operator_asterix_equal__BOSS(double) =0;
    
                virtual Pythia8::Abstract_Hist& operator_slash_equal__BOSS(double) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Hist*) =0;
                virtual Abstract_Hist* pointer_copy__BOSS() =0;
    
            private:
                Hist* wptr;
                bool delete_wrapper;
            public:
                Hist* get_wptr() { return wptr; }
                void set_wptr(Hist* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Hist()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Hist(const Abstract_Hist&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Hist& operator=(const Abstract_Hist&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Hist* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Hist& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Hist() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Hist_Pythia_8_212_h__ */
