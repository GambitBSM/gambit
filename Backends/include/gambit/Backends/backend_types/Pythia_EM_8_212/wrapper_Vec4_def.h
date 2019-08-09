#ifndef __wrapper_Vec4_def_Pythia_EM_8_212_h__
#define __wrapper_Vec4_def_Pythia_EM_8_212_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void Vec4::reset()
        {
            get_BEptr()->reset();
        }
        
        inline void Vec4::p(double xIn, double yIn, double zIn, double tIn)
        {
            get_BEptr()->p(xIn, yIn, zIn, tIn);
        }
        
        inline void Vec4::p(Pythia8::Vec4 pIn)
        {
            get_BEptr()->p__BOSS(*pIn.get_BEptr());
        }
        
        inline void Vec4::px(double xIn)
        {
            get_BEptr()->px(xIn);
        }
        
        inline void Vec4::py(double yIn)
        {
            get_BEptr()->py(yIn);
        }
        
        inline void Vec4::pz(double zIn)
        {
            get_BEptr()->pz(zIn);
        }
        
        inline void Vec4::e(double tIn)
        {
            get_BEptr()->e(tIn);
        }
        
        inline double Vec4::px() const
        {
            return get_BEptr()->px();
        }
        
        inline double Vec4::py() const
        {
            return get_BEptr()->py();
        }
        
        inline double Vec4::pz() const
        {
            return get_BEptr()->pz();
        }
        
        inline double Vec4::e() const
        {
            return get_BEptr()->e();
        }
        
        inline double& Vec4::operator[](int i)
        {
            return get_BEptr()->operator[](i);
        }
        
        inline double Vec4::mCalc() const
        {
            return get_BEptr()->mCalc();
        }
        
        inline double Vec4::m2Calc() const
        {
            return get_BEptr()->m2Calc();
        }
        
        inline double Vec4::pT() const
        {
            return get_BEptr()->pT();
        }
        
        inline double Vec4::pT2() const
        {
            return get_BEptr()->pT2();
        }
        
        inline double Vec4::pAbs() const
        {
            return get_BEptr()->pAbs();
        }
        
        inline double Vec4::pAbs2() const
        {
            return get_BEptr()->pAbs2();
        }
        
        inline double Vec4::eT() const
        {
            return get_BEptr()->eT();
        }
        
        inline double Vec4::eT2() const
        {
            return get_BEptr()->eT2();
        }
        
        inline double Vec4::theta() const
        {
            return get_BEptr()->theta();
        }
        
        inline double Vec4::phi() const
        {
            return get_BEptr()->phi();
        }
        
        inline double Vec4::thetaXZ() const
        {
            return get_BEptr()->thetaXZ();
        }
        
        inline double Vec4::pPos() const
        {
            return get_BEptr()->pPos();
        }
        
        inline double Vec4::pNeg() const
        {
            return get_BEptr()->pNeg();
        }
        
        inline double Vec4::rap() const
        {
            return get_BEptr()->rap();
        }
        
        inline double Vec4::eta() const
        {
            return get_BEptr()->eta();
        }
        
        inline void Vec4::rescale3(double fac)
        {
            get_BEptr()->rescale3(fac);
        }
        
        inline void Vec4::rescale4(double fac)
        {
            get_BEptr()->rescale4(fac);
        }
        
        inline void Vec4::flip3()
        {
            get_BEptr()->flip3();
        }
        
        inline void Vec4::flip4()
        {
            get_BEptr()->flip4();
        }
        
        inline void Vec4::rot(double thetaIn, double phiIn)
        {
            get_BEptr()->rot(thetaIn, phiIn);
        }
        
        inline void Vec4::rotaxis(double phiIn, double nx, double ny, double nz)
        {
            get_BEptr()->rotaxis(phiIn, nx, ny, nz);
        }
        
        inline void Vec4::rotaxis(double phiIn, const Pythia8::Vec4& n)
        {
            get_BEptr()->rotaxis__BOSS(phiIn, *n.get_BEptr());
        }
        
        inline void Vec4::bst(double betaX, double betaY, double betaZ)
        {
            get_BEptr()->bst(betaX, betaY, betaZ);
        }
        
        inline void Vec4::bst(double betaX, double betaY, double betaZ, double gamma)
        {
            get_BEptr()->bst(betaX, betaY, betaZ, gamma);
        }
        
        inline void Vec4::bst(const Pythia8::Vec4& pIn)
        {
            get_BEptr()->bst__BOSS(*pIn.get_BEptr());
        }
        
        inline void Vec4::bst(const Pythia8::Vec4& pIn, double mIn)
        {
            get_BEptr()->bst__BOSS(*pIn.get_BEptr(), mIn);
        }
        
        inline void Vec4::bstback(const Pythia8::Vec4& pIn)
        {
            get_BEptr()->bstback__BOSS(*pIn.get_BEptr());
        }
        
        inline void Vec4::bstback(const Pythia8::Vec4& pIn, double mIn)
        {
            get_BEptr()->bstback__BOSS(*pIn.get_BEptr(), mIn);
        }
        
        inline Pythia8::Vec4 Vec4::operator-()
        {
            return Pythia8::Vec4( get_BEptr()->operator_minus__BOSS() );
        }
        
        inline Pythia8::Vec4& Vec4::operator+=(const Pythia8::Vec4& v)
        {
            return get_BEptr()->operator_plus_equal__BOSS(*v.get_BEptr()).get_init_wref();
        }
        
        inline Pythia8::Vec4& Vec4::operator-=(const Pythia8::Vec4& v)
        {
            return get_BEptr()->operator_minus_equal__BOSS(*v.get_BEptr()).get_init_wref();
        }
        
        inline Pythia8::Vec4& Vec4::operator*=(double f)
        {
            return get_BEptr()->operator_asterix_equal__BOSS(f).get_init_wref();
        }
        
        inline Pythia8::Vec4& Vec4::operator/=(double f)
        {
            return get_BEptr()->operator_slash_equal__BOSS(f).get_init_wref();
        }
        
        
        // Wrappers for original constructors: 
        inline Pythia8::Vec4::Vec4(double xIn, double yIn, double zIn, double tIn) :
            WrapperBase(__factory0(xIn, yIn, zIn, tIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Vec4::Vec4(double xIn, double yIn, double zIn) :
            WrapperBase(__factory1(xIn, yIn, zIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Vec4::Vec4(double xIn, double yIn) :
            WrapperBase(__factory2(xIn, yIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Vec4::Vec4(double xIn) :
            WrapperBase(__factory3(xIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Vec4::Vec4() :
            WrapperBase(__factory4())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Pythia8::Vec4::Vec4(Pythia8::Abstract_Vec4* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Pythia8::Vec4::Vec4(const Vec4& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Pythia8::Vec4& Vec4::operator=(const Vec4& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Pythia8::Vec4::~Vec4()
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
        inline Pythia8::Abstract_Vec4* Pythia8::Vec4::get_BEptr() const
        {
            return dynamic_cast<Pythia8::Abstract_Vec4*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Vec4_def_Pythia_EM_8_212_h__ */
