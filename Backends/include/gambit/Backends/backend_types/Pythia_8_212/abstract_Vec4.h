#ifndef __abstract_Vec4_Pythia_8_212_h__
#define __abstract_Vec4_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Vec4 : public virtual AbstractBase
        {
            public:
    
                virtual Pythia8::Abstract_Vec4& operator_equal__BOSS(const Pythia8::Abstract_Vec4&) =0;
    
                virtual Pythia8::Abstract_Vec4& operator_equal__BOSS(double) =0;
    
                virtual void reset() =0;
    
                virtual void p(double, double, double, double) =0;
    
                virtual void p__BOSS(Pythia8::Abstract_Vec4&) =0;
    
                virtual void px(double) =0;
    
                virtual void py(double) =0;
    
                virtual void pz(double) =0;
    
                virtual void e(double) =0;
    
                virtual double px() const =0;
    
                virtual double py() const =0;
    
                virtual double pz() const =0;
    
                virtual double e() const =0;
    
                virtual double& operator[](int) =0;
    
                virtual double mCalc() const =0;
    
                virtual double m2Calc() const =0;
    
                virtual double pT() const =0;
    
                virtual double pT2() const =0;
    
                virtual double pAbs() const =0;
    
                virtual double pAbs2() const =0;
    
                virtual double eT() const =0;
    
                virtual double eT2() const =0;
    
                virtual double theta() const =0;
    
                virtual double phi() const =0;
    
                virtual double thetaXZ() const =0;
    
                virtual double pPos() const =0;
    
                virtual double pNeg() const =0;
    
                virtual double rap() const =0;
    
                virtual double eta() const =0;
    
                virtual void rescale3(double) =0;
    
                virtual void rescale4(double) =0;
    
                virtual void flip3() =0;
    
                virtual void flip4() =0;
    
                virtual void rot(double, double) =0;
    
                virtual void rotaxis(double, double, double, double) =0;
    
                virtual void rotaxis__BOSS(double, const Pythia8::Abstract_Vec4&) =0;
    
                virtual void bst(double, double, double) =0;
    
                virtual void bst(double, double, double, double) =0;
    
                virtual void bst__BOSS(const Pythia8::Abstract_Vec4&) =0;
    
                virtual void bst__BOSS(const Pythia8::Abstract_Vec4&, double) =0;
    
                virtual void bstback__BOSS(const Pythia8::Abstract_Vec4&) =0;
    
                virtual void bstback__BOSS(const Pythia8::Abstract_Vec4&, double) =0;
    
                virtual Pythia8::Abstract_Vec4* operator_minus__BOSS() =0;
    
                virtual Pythia8::Abstract_Vec4& operator_plus_equal__BOSS(const Pythia8::Abstract_Vec4&) =0;
    
                virtual Pythia8::Abstract_Vec4& operator_minus_equal__BOSS(const Pythia8::Abstract_Vec4&) =0;
    
                virtual Pythia8::Abstract_Vec4& operator_asterix_equal__BOSS(double) =0;
    
                virtual Pythia8::Abstract_Vec4& operator_slash_equal__BOSS(double) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Vec4*) =0;
                virtual Abstract_Vec4* pointer_copy__BOSS() =0;
    
            private:
                Vec4* wptr;
                bool delete_wrapper;
            public:
                Vec4* get_wptr() { return wptr; }
                void set_wptr(Vec4* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Vec4()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Vec4(const Abstract_Vec4&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Vec4& operator=(const Abstract_Vec4&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Vec4* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Vec4& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Vec4() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Vec4_Pythia_8_212_h__ */
