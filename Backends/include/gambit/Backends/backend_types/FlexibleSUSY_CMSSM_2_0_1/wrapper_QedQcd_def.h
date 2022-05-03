#ifndef __wrapper_QedQcd_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_QedQcd_def_FlexibleSUSY_CMSSM_2_0_1_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace softsusy
    {
        
        // Member functions: 
        inline void QedQcd::setPoleMt(double mt)
        {
            get_BEptr()->setPoleMt(mt);
        }
        
        inline void QedQcd::setPoleMb(double mb)
        {
            get_BEptr()->setPoleMb(mb);
        }
        
        inline void QedQcd::setPoleMtau(double mtau)
        {
            get_BEptr()->setPoleMtau(mtau);
        }
        
        inline void QedQcd::setPoleMmuon(double m)
        {
            get_BEptr()->setPoleMmuon(m);
        }
        
        inline void QedQcd::setPoleMel(double m)
        {
            get_BEptr()->setPoleMel(m);
        }
        
        inline void QedQcd::setMbMb(double mb)
        {
            get_BEptr()->setMbMb(mb);
        }
        
        inline void QedQcd::setMcMc(double mc)
        {
            get_BEptr()->setMcMc(mc);
        }
        
        inline void QedQcd::setMu2GeV(double mu)
        {
            get_BEptr()->setMu2GeV(mu);
        }
        
        inline void QedQcd::setMd2GeV(double md)
        {
            get_BEptr()->setMd2GeV(md);
        }
        
        inline void QedQcd::setMs2GeV(double ms)
        {
            get_BEptr()->setMs2GeV(ms);
        }
        
        inline void QedQcd::setPoleMW(double mw)
        {
            get_BEptr()->setPoleMW(mw);
        }
        
        inline void QedQcd::setPoleMZ(double mz)
        {
            get_BEptr()->setPoleMZ(mz);
        }
        
        inline void QedQcd::setMass(softsusy::mass mno, double m)
        {
            get_BEptr()->setMass(mno, m);
        }
        
        inline void QedQcd::setNeutrinoPoleMass(int i, double m)
        {
            get_BEptr()->setNeutrinoPoleMass(i, m);
        }
        
        inline void QedQcd::setAlpha(softsusy::leGauge ai, double ap)
        {
            get_BEptr()->setAlpha(ai, ap);
        }
        
        inline void QedQcd::setAlphaEmInput(double a)
        {
            get_BEptr()->setAlphaEmInput(a);
        }
        
        inline void QedQcd::setAlphaSInput(double a)
        {
            get_BEptr()->setAlphaSInput(a);
        }
        
        inline void QedQcd::setFermiConstant(double gf)
        {
            get_BEptr()->setFermiConstant(gf);
        }
        
        inline double QedQcd::displayPoleMt() const
        {
            return get_BEptr()->displayPoleMt();
        }
        
        inline double QedQcd::displayPoleMtau() const
        {
            return get_BEptr()->displayPoleMtau();
        }
        
        inline double QedQcd::displayPoleMmuon() const
        {
            return get_BEptr()->displayPoleMmuon();
        }
        
        inline double QedQcd::displayPoleMel() const
        {
            return get_BEptr()->displayPoleMel();
        }
        
        inline double QedQcd::displayPoleMb() const
        {
            return get_BEptr()->displayPoleMb();
        }
        
        inline double QedQcd::displayPoleMW() const
        {
            return get_BEptr()->displayPoleMW();
        }
        
        inline double QedQcd::displayPoleMZ() const
        {
            return get_BEptr()->displayPoleMZ();
        }
        
        inline double QedQcd::displayNeutrinoPoleMass(int i) const
        {
            return get_BEptr()->displayNeutrinoPoleMass(i);
        }
        
        inline double QedQcd::displayAlpha(softsusy::leGauge ai) const
        {
            return get_BEptr()->displayAlpha(ai);
        }
        
        inline double QedQcd::displayAlphaEmInput() const
        {
            return get_BEptr()->displayAlphaEmInput();
        }
        
        inline double QedQcd::displayAlphaSInput() const
        {
            return get_BEptr()->displayAlphaSInput();
        }
        
        inline double QedQcd::displayFermiConstant() const
        {
            return get_BEptr()->displayFermiConstant();
        }
        
        inline double QedQcd::displayMbMb() const
        {
            return get_BEptr()->displayMbMb();
        }
        
        inline double QedQcd::displayMcMc() const
        {
            return get_BEptr()->displayMcMc();
        }
        
        inline double QedQcd::displayMu2GeV() const
        {
            return get_BEptr()->displayMu2GeV();
        }
        
        inline double QedQcd::displayMd2GeV() const
        {
            return get_BEptr()->displayMd2GeV();
        }
        
        inline double QedQcd::displayMs2GeV() const
        {
            return get_BEptr()->displayMs2GeV();
        }
        
        inline void QedQcd::toMz()
        {
            get_BEptr()->toMz();
        }
        
        inline void QedQcd::to(double scale, double tol, int max_iterations)
        {
            get_BEptr()->to(scale, tol, max_iterations);
        }
        
        inline void QedQcd::to(double scale, double tol)
        {
            get_BEptr()->to__BOSS(scale, tol);
        }
        
        inline void QedQcd::to(double scale)
        {
            get_BEptr()->to__BOSS(scale);
        }
        
        
        // Wrappers for original constructors: 
        inline QedQcd::QedQcd() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline QedQcd::QedQcd(Abstract_QedQcd* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline QedQcd::QedQcd(const QedQcd& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline QedQcd& QedQcd::operator=(const QedQcd& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline QedQcd::~QedQcd()
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
        inline Abstract_QedQcd* softsusy::QedQcd::get_BEptr() const
        {
            return dynamic_cast<Abstract_QedQcd*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_QedQcd_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
