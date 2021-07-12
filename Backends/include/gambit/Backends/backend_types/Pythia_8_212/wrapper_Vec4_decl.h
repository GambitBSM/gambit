#ifndef __wrapper_Vec4_decl_Pythia_8_212_h__
#define __wrapper_Vec4_decl_Pythia_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Vec4.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Vec4 : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Vec4* (*__factory0)(double, double, double, double);
                static Abstract_Vec4* (*__factory1)(double, double, double);
                static Abstract_Vec4* (*__factory2)(double, double);
                static Abstract_Vec4* (*__factory3)(double);
                static Abstract_Vec4* (*__factory4)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void reset();
        
                void p(double xIn, double yIn, double zIn, double tIn);
        
                void p(Pythia8::Vec4 pIn);
        
                void px(double xIn);
        
                void py(double yIn);
        
                void pz(double zIn);
        
                void e(double tIn);
        
                double px() const;
        
                double py() const;
        
                double pz() const;
        
                double e() const;
        
                double& operator[](int i);
        
                double mCalc() const;
        
                double m2Calc() const;
        
                double pT() const;
        
                double pT2() const;
        
                double pAbs() const;
        
                double pAbs2() const;
        
                double eT() const;
        
                double eT2() const;
        
                double theta() const;
        
                double phi() const;
        
                double thetaXZ() const;
        
                double pPos() const;
        
                double pNeg() const;
        
                double rap() const;
        
                double eta() const;
        
                void rescale3(double fac);
        
                void rescale4(double fac);
        
                void flip3();
        
                void flip4();
        
                void rot(double thetaIn, double phiIn);
        
                void rotaxis(double phiIn, double nx, double ny, double nz);
        
                void rotaxis(double phiIn, const Pythia8::Vec4& n);
        
                void bst(double betaX, double betaY, double betaZ);
        
                void bst(double betaX, double betaY, double betaZ, double gamma);
        
                void bst(const Pythia8::Vec4& pIn);
        
                void bst(const Pythia8::Vec4& pIn, double mIn);
        
                void bstback(const Pythia8::Vec4& pIn);
        
                void bstback(const Pythia8::Vec4& pIn, double mIn);
        
                Pythia8::Vec4 operator-();
        
                Pythia8::Vec4& operator+=(const Pythia8::Vec4& v);
        
                Pythia8::Vec4& operator-=(const Pythia8::Vec4& v);
        
                Pythia8::Vec4& operator*=(double f);
        
                Pythia8::Vec4& operator/=(double f);
        
        
                // Wrappers for original constructors: 
            public:
                Vec4(double xIn, double yIn, double zIn, double tIn);
                Vec4(double xIn, double yIn, double zIn);
                Vec4(double xIn, double yIn);
                Vec4(double xIn);
                Vec4();
        
                // Special pointer-based constructor: 
                Vec4(Abstract_Vec4* in);
        
                // Copy constructor: 
                Vec4(const Vec4& in);
        
                // Assignment operator: 
                Vec4& operator=(const Vec4& in);
        
                // Destructor: 
                ~Vec4();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Vec4* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Vec4_decl_Pythia_8_212_h__ */
