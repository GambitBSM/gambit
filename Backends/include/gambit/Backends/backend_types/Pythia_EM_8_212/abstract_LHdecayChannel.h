#ifndef __abstract_LHdecayChannel_Pythia_EM_8_212_h__
#define __abstract_LHdecayChannel_Pythia_EM_8_212_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include <vector>
#include <string>
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_LHdecayChannel : public virtual AbstractBase
        {
            public:
    
                virtual void setChannel(double, int, ::std::vector<int, std::allocator<int> >, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >) =0;
    
                virtual void setChannel__BOSS(double, int, ::std::vector<int, std::allocator<int> >) =0;
    
                virtual void setBrat(double) =0;
    
                virtual void setIdDa(::std::vector<int, std::allocator<int> >) =0;
    
                virtual double getBrat() =0;
    
                virtual int getNDa() =0;
    
                virtual ::std::vector<int, std::allocator<int> > getIdDa() =0;
    
                virtual ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > getComment() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_LHdecayChannel*) =0;
                virtual Abstract_LHdecayChannel* pointer_copy__BOSS() =0;
    
            private:
                LHdecayChannel* wptr;
                bool delete_wrapper;
            public:
                LHdecayChannel* get_wptr() { return wptr; }
                void set_wptr(LHdecayChannel* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_LHdecayChannel()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_LHdecayChannel(const Abstract_LHdecayChannel&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_LHdecayChannel& operator=(const Abstract_LHdecayChannel&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                LHdecayChannel* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                LHdecayChannel& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_LHdecayChannel() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_LHdecayChannel_Pythia_EM_8_212_h__ */
