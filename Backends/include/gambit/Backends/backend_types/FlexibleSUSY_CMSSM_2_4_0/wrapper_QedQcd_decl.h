#ifndef __wrapper_QedQcd_decl_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_QedQcd_decl_FlexibleSUSY_CMSSM_2_4_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_QedQcd.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace softsusy
    {
        
        class QedQcd : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static softsusy::Abstract_QedQcd* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void setPoleMt(double mt);
        
                void setPoleMb(double mb);
        
                void setPoleMtau(double mtau);
        
                void setPoleMmuon(double m);
        
                void setPoleMel(double m);
        
                void setMbMb(double mb);
        
                void setMcMc(double mc);
        
                void setMu2GeV(double mu);
        
                void setMd2GeV(double md);
        
                void setMs2GeV(double ms);
        
                void setPoleMW(double mw);
        
                void setPoleMZ(double mz);
        
                void setNeutrinoPoleMass(int i, double m);
        
                void setAlphaEmInput(double a);
        
                void setAlphaSInput(double a);
        
                void setFermiConstant(double gf);
        
                double displayPoleMt() const;
        
                double displayPoleMtau() const;
        
                double displayPoleMmuon() const;
        
                double displayPoleMel() const;
        
                double displayPoleMb() const;
        
                double displayPoleMW() const;
        
                double displayPoleMZ() const;
        
                double displayNeutrinoPoleMass(int i) const;
        
                double displayAlphaEmInput() const;
        
                double displayAlphaSInput() const;
        
                double displayFermiConstant() const;
        
                double displayMbMb() const;
        
                double displayMcMc() const;
        
                double displayMu2GeV() const;
        
                double displayMd2GeV() const;
        
                double displayMs2GeV() const;
        
                void toMz();
        
                void to(double scale, double tol, int max_iterations);
        
                void to(double scale, double tol);
        
                void to(double scale);
        
        
                // Wrappers for original constructors: 
            public:
                QedQcd();
        
                // Special pointer-based constructor: 
                QedQcd(softsusy::Abstract_QedQcd* in);
        
                // Copy constructor: 
                QedQcd(const QedQcd& in);
        
                // Assignment operator: 
                QedQcd& operator=(const QedQcd& in);
        
                // Destructor: 
                ~QedQcd();
        
                // Returns correctly casted pointer to Abstract class: 
                softsusy::Abstract_QedQcd* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_QedQcd_decl_FlexibleSUSY_CMSSM_2_4_0_h__ */
