#ifndef __wrapper_CoupSM_def_Pythia_EM_8_212_h__
#define __wrapper_CoupSM_def_Pythia_EM_8_212_h__

#include "wrapper_Settings_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_AlphaStrong_decl.h"
#include "wrapper_AlphaEM_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void CoupSM::init(Pythia8::Settings& settings, Pythia8::Rndm* rndmPtrIn)
        {
            get_BEptr()->init__BOSS(*settings.get_BEptr(), (*rndmPtrIn).get_BEptr());
        }
        
        inline double CoupSM::alphaS(double scale2)
        {
            return get_BEptr()->alphaS(scale2);
        }
        
        inline double CoupSM::alphaS1Ord(double scale2)
        {
            return get_BEptr()->alphaS1Ord(scale2);
        }
        
        inline double CoupSM::alphaS2OrdCorr(double scale2)
        {
            return get_BEptr()->alphaS2OrdCorr(scale2);
        }
        
        inline double CoupSM::Lambda3() const
        {
            return get_BEptr()->Lambda3();
        }
        
        inline double CoupSM::Lambda4() const
        {
            return get_BEptr()->Lambda4();
        }
        
        inline double CoupSM::Lambda5() const
        {
            return get_BEptr()->Lambda5();
        }
        
        inline double CoupSM::alphaEM(double scale2)
        {
            return get_BEptr()->alphaEM(scale2);
        }
        
        inline double CoupSM::sin2thetaW()
        {
            return get_BEptr()->sin2thetaW();
        }
        
        inline double CoupSM::cos2thetaW()
        {
            return get_BEptr()->cos2thetaW();
        }
        
        inline double CoupSM::sin2thetaWbar()
        {
            return get_BEptr()->sin2thetaWbar();
        }
        
        inline double CoupSM::GF()
        {
            return get_BEptr()->GF();
        }
        
        inline double CoupSM::ef(int idAbs)
        {
            return get_BEptr()->ef(idAbs);
        }
        
        inline double CoupSM::vf(int idAbs)
        {
            return get_BEptr()->vf(idAbs);
        }
        
        inline double CoupSM::af(int idAbs)
        {
            return get_BEptr()->af(idAbs);
        }
        
        inline double CoupSM::t3f(int idAbs)
        {
            return get_BEptr()->t3f(idAbs);
        }
        
        inline double CoupSM::lf(int idAbs)
        {
            return get_BEptr()->lf(idAbs);
        }
        
        inline double CoupSM::rf(int idAbs)
        {
            return get_BEptr()->rf(idAbs);
        }
        
        inline double CoupSM::ef2(int idAbs)
        {
            return get_BEptr()->ef2(idAbs);
        }
        
        inline double CoupSM::vf2(int idAbs)
        {
            return get_BEptr()->vf2(idAbs);
        }
        
        inline double CoupSM::af2(int idAbs)
        {
            return get_BEptr()->af2(idAbs);
        }
        
        inline double CoupSM::efvf(int idAbs)
        {
            return get_BEptr()->efvf(idAbs);
        }
        
        inline double CoupSM::vf2af2(int idAbs)
        {
            return get_BEptr()->vf2af2(idAbs);
        }
        
        inline double CoupSM::VCKMgen(int genU, int genD)
        {
            return get_BEptr()->VCKMgen(genU, genD);
        }
        
        inline double CoupSM::V2CKMgen(int genU, int genD)
        {
            return get_BEptr()->V2CKMgen(genU, genD);
        }
        
        inline double CoupSM::VCKMid(int id1, int id2)
        {
            return get_BEptr()->VCKMid(id1, id2);
        }
        
        inline double CoupSM::V2CKMid(int id1, int id2)
        {
            return get_BEptr()->V2CKMid(id1, id2);
        }
        
        inline double CoupSM::V2CKMsum(int id)
        {
            return get_BEptr()->V2CKMsum(id);
        }
        
        inline int CoupSM::V2CKMpick(int id)
        {
            return get_BEptr()->V2CKMpick(id);
        }
        
        
        // Wrappers for original constructors: 
        inline Pythia8::CoupSM::CoupSM() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Pythia8::CoupSM::CoupSM(Pythia8::Abstract_CoupSM* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Pythia8::CoupSM::CoupSM(const CoupSM& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Pythia8::CoupSM& CoupSM::operator=(const CoupSM& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Pythia8::CoupSM::~CoupSM()
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
        inline Pythia8::Abstract_CoupSM* Pythia8::CoupSM::get_BEptr() const
        {
            return dynamic_cast<Pythia8::Abstract_CoupSM*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CoupSM_def_Pythia_EM_8_212_h__ */
