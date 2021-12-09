#ifndef __abstract_QedQcd_FlexibleSUSY_CMSSM_2_4_0_h__
#define __abstract_QedQcd_FlexibleSUSY_CMSSM_2_4_0_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace softsusy
    {
        class Abstract_QedQcd : public virtual AbstractBase
        {
            public:
    
                virtual softsusy::Abstract_QedQcd& operator_equal__BOSS(const softsusy::Abstract_QedQcd&) =0;
    
                virtual void setPoleMt(double) =0;
    
                virtual void setPoleMb(double) =0;
    
                virtual void setPoleMtau(double) =0;
    
                virtual void setPoleMmuon(double) =0;
    
                virtual void setPoleMel(double) =0;
    
                virtual void setMbMb(double) =0;
    
                virtual void setMcMc(double) =0;
    
                virtual void setMu2GeV(double) =0;
    
                virtual void setMd2GeV(double) =0;
    
                virtual void setMs2GeV(double) =0;
    
                virtual void setPoleMW(double) =0;
    
                virtual void setPoleMZ(double) =0;
    
                virtual void setNeutrinoPoleMass(int, double) =0;
    
                virtual void setAlphaEmInput(double) =0;
    
                virtual void setAlphaSInput(double) =0;
    
                virtual void setFermiConstant(double) =0;
    
                virtual double displayPoleMt() const =0;
    
                virtual double displayPoleMtau() const =0;
    
                virtual double displayPoleMmuon() const =0;
    
                virtual double displayPoleMel() const =0;
    
                virtual double displayPoleMb() const =0;
    
                virtual double displayPoleMW() const =0;
    
                virtual double displayPoleMZ() const =0;
    
                virtual double displayNeutrinoPoleMass(int) const =0;
    
                virtual double displayAlphaEmInput() const =0;
    
                virtual double displayAlphaSInput() const =0;
    
                virtual double displayFermiConstant() const =0;
    
                virtual double displayMbMb() const =0;
    
                virtual double displayMcMc() const =0;
    
                virtual double displayMu2GeV() const =0;
    
                virtual double displayMd2GeV() const =0;
    
                virtual double displayMs2GeV() const =0;
    
                virtual void toMz() =0;
    
                virtual void to(double, double, int) =0;
    
                virtual void to__BOSS(double, double) =0;
    
                virtual void to__BOSS(double) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_QedQcd*) =0;
                virtual Abstract_QedQcd* pointer_copy__BOSS() =0;
    
            private:
                QedQcd* wptr;
                bool delete_wrapper;
            public:
                QedQcd* get_wptr() { return wptr; }
                void set_wptr(QedQcd* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_QedQcd()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_QedQcd(const Abstract_QedQcd&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_QedQcd& operator=(const Abstract_QedQcd&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                QedQcd* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                QedQcd& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_QedQcd() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_QedQcd_FlexibleSUSY_CMSSM_2_4_0_h__ */
