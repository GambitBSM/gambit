#ifndef __abstract_SigmaTotal_Pythia_8_312_h__
#define __abstract_SigmaTotal_Pythia_8_312_h__

#include <cstddef>
#include <iostream>
#include <utility>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_SigmaTotal : public virtual AbstractBase
        {
            public:
    
                virtual void init() =0;
    
                virtual bool calc(int, int, double) =0;
    
                virtual bool hasSigmaTot() =0;
    
                virtual double sigmaTot() =0;
    
                virtual double rho() =0;
    
                virtual double sigmaEl() =0;
    
                virtual bool bElIsExp() =0;
    
                virtual double bSlopeEl() =0;
    
                virtual bool hasCoulomb() =0;
    
                virtual bool calcTotEl(int, int, double, double, double) =0;
    
                virtual double dsigmaEl(double, bool, bool) =0;
    
                virtual double dsigmaEl__BOSS(double, bool) =0;
    
                virtual double dsigmaEl__BOSS(double) =0;
    
                virtual double sigmaXB() const =0;
    
                virtual double sigmaAX() const =0;
    
                virtual double sigmaXX() const =0;
    
                virtual double sigmaAXB() const =0;
    
                virtual double sigmaND() const =0;
    
                virtual double dsigmaSD(double, double, bool, int) =0;
    
                virtual double dsigmaSD__BOSS(double, double, bool) =0;
    
                virtual double dsigmaSD__BOSS(double, double) =0;
    
                virtual bool splitDiff() =0;
    
                virtual double dsigmaDD(double, double, double, int) =0;
    
                virtual double dsigmaDD__BOSS(double, double, double) =0;
    
                virtual double dsigmaCD(double, double, double, double, int) =0;
    
                virtual double dsigmaCD__BOSS(double, double, double, double) =0;
    
                virtual double mMinCD() =0;
    
                virtual void chooseVMDstates(int, int, double, int) =0;
    
                virtual ::std::pair<double, double> tRange(double, double, double, double, double) =0;
    
                virtual bool tInRange(double, double, double, double, double, double) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_SigmaTotal*) =0;
                virtual Abstract_SigmaTotal* pointer_copy__BOSS() =0;
    
            private:
                SigmaTotal* wptr;
                bool delete_wrapper;
            public:
                SigmaTotal* get_wptr() { return wptr; }
                void set_wptr(SigmaTotal* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_SigmaTotal()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_SigmaTotal(const Abstract_SigmaTotal&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_SigmaTotal& operator=(const Abstract_SigmaTotal&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                SigmaTotal* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                SigmaTotal& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_SigmaTotal() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_SigmaTotal_Pythia_8_312_h__ */
