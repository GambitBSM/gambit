#ifndef __wrapper_CoupSUSY_def_Pythia_8_212_h__
#define __wrapper_CoupSUSY_def_Pythia_8_212_h__

#include <complex>
#include "wrapper_SusyLesHouches_decl.h"
#include "wrapper_Info_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Settings_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void CoupSUSY::initSUSY(Pythia8::SusyLesHouches* slhaPtrIn, Pythia8::Info* infoPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Settings* settingsPtrIn)
        {
            get_BEptr()->initSUSY__BOSS((*slhaPtrIn).get_BEptr(), (*infoPtrIn).get_BEptr(), (*particleDataPtrIn).get_BEptr(), (*settingsPtrIn).get_BEptr());
        }
        
        inline ::std::complex<double> CoupSUSY::getLsqqG(int iGenSq, int idQ)
        {
            return get_BEptr()->getLsqqG(iGenSq, idQ);
        }
        
        inline ::std::complex<double> CoupSUSY::getRsqqG(int iGenSq, int idQ)
        {
            return get_BEptr()->getRsqqG(iGenSq, idQ);
        }
        
        inline ::std::complex<double> CoupSUSY::getLsqsqZ(int idSq1, int idSq2)
        {
            return get_BEptr()->getLsqsqZ(idSq1, idSq2);
        }
        
        inline ::std::complex<double> CoupSUSY::getRsqsqZ(int idSq1, int idSq2)
        {
            return get_BEptr()->getRsqsqZ(idSq1, idSq2);
        }
        
        inline ::std::complex<double> CoupSUSY::getLsqqX(int iSq, int idQ, int iNeut)
        {
            return get_BEptr()->getLsqqX(iSq, idQ, iNeut);
        }
        
        inline ::std::complex<double> CoupSUSY::getRsqqX(int iSq, int idQ, int iNeut)
        {
            return get_BEptr()->getRsqqX(iSq, idQ, iNeut);
        }
        
        inline int CoupSUSY::idNeut(int idChi)
        {
            return get_BEptr()->idNeut(idChi);
        }
        
        inline int CoupSUSY::idChar(int idChi)
        {
            return get_BEptr()->idChar(idChi);
        }
        
        inline int CoupSUSY::idSup(int iSup)
        {
            return get_BEptr()->idSup(iSup);
        }
        
        inline int CoupSUSY::idSdown(int iSdown)
        {
            return get_BEptr()->idSdown(iSdown);
        }
        
        inline int CoupSUSY::idSlep(int iSlep)
        {
            return get_BEptr()->idSlep(iSlep);
        }
        
        inline int CoupSUSY::typeNeut(int idPDG)
        {
            return get_BEptr()->typeNeut(idPDG);
        }
        
        inline int CoupSUSY::typeChar(int idPDG)
        {
            return get_BEptr()->typeChar(idPDG);
        }
        
        
        // Wrappers for original constructors: 
        inline CoupSUSY::CoupSUSY() :
            Couplings(__factory0()),
            isInit( get_BEptr()->isInit_ref__BOSS()),
            isNMSSM( get_BEptr()->isNMSSM_ref__BOSS()),
            mWpole( get_BEptr()->mWpole_ref__BOSS()),
            wWpole( get_BEptr()->wWpole_ref__BOSS()),
            mZpole( get_BEptr()->mZpole_ref__BOSS()),
            wZpole( get_BEptr()->wZpole_ref__BOSS()),
            mW( get_BEptr()->mW_ref__BOSS()),
            mZ( get_BEptr()->mZ_ref__BOSS()),
            sin2W( get_BEptr()->sin2W_ref__BOSS()),
            sinW( get_BEptr()->sinW_ref__BOSS()),
            cosW( get_BEptr()->cosW_ref__BOSS()),
            tanb( get_BEptr()->tanb_ref__BOSS()),
            cosb( get_BEptr()->cosb_ref__BOSS()),
            sinb( get_BEptr()->sinb_ref__BOSS()),
            muHiggs( get_BEptr()->muHiggs_ref__BOSS()),
            alphaHiggs( get_BEptr()->alphaHiggs_ref__BOSS()),
            mAHiggs( get_BEptr()->mAHiggs_ref__BOSS()),
            LsddG( get_BEptr()->LsddG_ref__BOSS()),
            RsddG( get_BEptr()->RsddG_ref__BOSS()),
            LsuuG( get_BEptr()->LsuuG_ref__BOSS()),
            RsuuG( get_BEptr()->RsuuG_ref__BOSS()),
            OLpp( get_BEptr()->OLpp_ref__BOSS()),
            ORpp( get_BEptr()->ORpp_ref__BOSS()),
            OLp( get_BEptr()->OLp_ref__BOSS()),
            ORp( get_BEptr()->ORp_ref__BOSS()),
            OL( get_BEptr()->OL_ref__BOSS()),
            OR( get_BEptr()->OR_ref__BOSS()),
            LqqZ( get_BEptr()->LqqZ_ref__BOSS()),
            RqqZ( get_BEptr()->RqqZ_ref__BOSS()),
            LsdsdZ( get_BEptr()->LsdsdZ_ref__BOSS()),
            RsdsdZ( get_BEptr()->RsdsdZ_ref__BOSS()),
            LsusuZ( get_BEptr()->LsusuZ_ref__BOSS()),
            RsusuZ( get_BEptr()->RsusuZ_ref__BOSS()),
            LudW( get_BEptr()->LudW_ref__BOSS()),
            RudW( get_BEptr()->RudW_ref__BOSS()),
            LsusdW( get_BEptr()->LsusdW_ref__BOSS()),
            RsusdW( get_BEptr()->RsusdW_ref__BOSS()),
            LsddX( get_BEptr()->LsddX_ref__BOSS()),
            RsddX( get_BEptr()->RsddX_ref__BOSS()),
            LsuuX( get_BEptr()->LsuuX_ref__BOSS()),
            RsuuX( get_BEptr()->RsuuX_ref__BOSS()),
            LsduX( get_BEptr()->LsduX_ref__BOSS()),
            RsduX( get_BEptr()->RsduX_ref__BOSS()),
            LsudX( get_BEptr()->LsudX_ref__BOSS()),
            RsudX( get_BEptr()->RsudX_ref__BOSS()),
            LllZ( get_BEptr()->LllZ_ref__BOSS()),
            RllZ( get_BEptr()->RllZ_ref__BOSS()),
            LlvW( get_BEptr()->LlvW_ref__BOSS()),
            RlvW( get_BEptr()->RlvW_ref__BOSS()),
            LslslZ( get_BEptr()->LslslZ_ref__BOSS()),
            RslslZ( get_BEptr()->RslslZ_ref__BOSS()),
            LsvsvZ( get_BEptr()->LsvsvZ_ref__BOSS()),
            RsvsvZ( get_BEptr()->RsvsvZ_ref__BOSS()),
            LslsvW( get_BEptr()->LslsvW_ref__BOSS()),
            RslsvW( get_BEptr()->RslsvW_ref__BOSS()),
            LsvvX( get_BEptr()->LsvvX_ref__BOSS()),
            RsvvX( get_BEptr()->RsvvX_ref__BOSS()),
            LsllX( get_BEptr()->LsllX_ref__BOSS()),
            RsllX( get_BEptr()->RsllX_ref__BOSS()),
            LsvlX( get_BEptr()->LsvlX_ref__BOSS()),
            RsvlX( get_BEptr()->RsvlX_ref__BOSS()),
            LslvX( get_BEptr()->LslvX_ref__BOSS()),
            RslvX( get_BEptr()->RslvX_ref__BOSS()),
            rvLLE( get_BEptr()->rvLLE_ref__BOSS()),
            rvLQD( get_BEptr()->rvLQD_ref__BOSS()),
            rvUDD( get_BEptr()->rvUDD_ref__BOSS()),
            isLLE( get_BEptr()->isLLE_ref__BOSS()),
            isLQD( get_BEptr()->isLQD_ref__BOSS()),
            isUDD( get_BEptr()->isUDD_ref__BOSS()),
            Rusq( get_BEptr()->Rusq_ref__BOSS()),
            Rdsq( get_BEptr()->Rdsq_ref__BOSS()),
            Rsl( get_BEptr()->Rsl_ref__BOSS()),
            Rsv( get_BEptr()->Rsv_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline CoupSUSY::CoupSUSY(Abstract_CoupSUSY* in) :
            Couplings(in),
            isInit( get_BEptr()->isInit_ref__BOSS()),
            isNMSSM( get_BEptr()->isNMSSM_ref__BOSS()),
            mWpole( get_BEptr()->mWpole_ref__BOSS()),
            wWpole( get_BEptr()->wWpole_ref__BOSS()),
            mZpole( get_BEptr()->mZpole_ref__BOSS()),
            wZpole( get_BEptr()->wZpole_ref__BOSS()),
            mW( get_BEptr()->mW_ref__BOSS()),
            mZ( get_BEptr()->mZ_ref__BOSS()),
            sin2W( get_BEptr()->sin2W_ref__BOSS()),
            sinW( get_BEptr()->sinW_ref__BOSS()),
            cosW( get_BEptr()->cosW_ref__BOSS()),
            tanb( get_BEptr()->tanb_ref__BOSS()),
            cosb( get_BEptr()->cosb_ref__BOSS()),
            sinb( get_BEptr()->sinb_ref__BOSS()),
            muHiggs( get_BEptr()->muHiggs_ref__BOSS()),
            alphaHiggs( get_BEptr()->alphaHiggs_ref__BOSS()),
            mAHiggs( get_BEptr()->mAHiggs_ref__BOSS()),
            LsddG( get_BEptr()->LsddG_ref__BOSS()),
            RsddG( get_BEptr()->RsddG_ref__BOSS()),
            LsuuG( get_BEptr()->LsuuG_ref__BOSS()),
            RsuuG( get_BEptr()->RsuuG_ref__BOSS()),
            OLpp( get_BEptr()->OLpp_ref__BOSS()),
            ORpp( get_BEptr()->ORpp_ref__BOSS()),
            OLp( get_BEptr()->OLp_ref__BOSS()),
            ORp( get_BEptr()->ORp_ref__BOSS()),
            OL( get_BEptr()->OL_ref__BOSS()),
            OR( get_BEptr()->OR_ref__BOSS()),
            LqqZ( get_BEptr()->LqqZ_ref__BOSS()),
            RqqZ( get_BEptr()->RqqZ_ref__BOSS()),
            LsdsdZ( get_BEptr()->LsdsdZ_ref__BOSS()),
            RsdsdZ( get_BEptr()->RsdsdZ_ref__BOSS()),
            LsusuZ( get_BEptr()->LsusuZ_ref__BOSS()),
            RsusuZ( get_BEptr()->RsusuZ_ref__BOSS()),
            LudW( get_BEptr()->LudW_ref__BOSS()),
            RudW( get_BEptr()->RudW_ref__BOSS()),
            LsusdW( get_BEptr()->LsusdW_ref__BOSS()),
            RsusdW( get_BEptr()->RsusdW_ref__BOSS()),
            LsddX( get_BEptr()->LsddX_ref__BOSS()),
            RsddX( get_BEptr()->RsddX_ref__BOSS()),
            LsuuX( get_BEptr()->LsuuX_ref__BOSS()),
            RsuuX( get_BEptr()->RsuuX_ref__BOSS()),
            LsduX( get_BEptr()->LsduX_ref__BOSS()),
            RsduX( get_BEptr()->RsduX_ref__BOSS()),
            LsudX( get_BEptr()->LsudX_ref__BOSS()),
            RsudX( get_BEptr()->RsudX_ref__BOSS()),
            LllZ( get_BEptr()->LllZ_ref__BOSS()),
            RllZ( get_BEptr()->RllZ_ref__BOSS()),
            LlvW( get_BEptr()->LlvW_ref__BOSS()),
            RlvW( get_BEptr()->RlvW_ref__BOSS()),
            LslslZ( get_BEptr()->LslslZ_ref__BOSS()),
            RslslZ( get_BEptr()->RslslZ_ref__BOSS()),
            LsvsvZ( get_BEptr()->LsvsvZ_ref__BOSS()),
            RsvsvZ( get_BEptr()->RsvsvZ_ref__BOSS()),
            LslsvW( get_BEptr()->LslsvW_ref__BOSS()),
            RslsvW( get_BEptr()->RslsvW_ref__BOSS()),
            LsvvX( get_BEptr()->LsvvX_ref__BOSS()),
            RsvvX( get_BEptr()->RsvvX_ref__BOSS()),
            LsllX( get_BEptr()->LsllX_ref__BOSS()),
            RsllX( get_BEptr()->RsllX_ref__BOSS()),
            LsvlX( get_BEptr()->LsvlX_ref__BOSS()),
            RsvlX( get_BEptr()->RsvlX_ref__BOSS()),
            LslvX( get_BEptr()->LslvX_ref__BOSS()),
            RslvX( get_BEptr()->RslvX_ref__BOSS()),
            rvLLE( get_BEptr()->rvLLE_ref__BOSS()),
            rvLQD( get_BEptr()->rvLQD_ref__BOSS()),
            rvUDD( get_BEptr()->rvUDD_ref__BOSS()),
            isLLE( get_BEptr()->isLLE_ref__BOSS()),
            isLQD( get_BEptr()->isLQD_ref__BOSS()),
            isUDD( get_BEptr()->isUDD_ref__BOSS()),
            Rusq( get_BEptr()->Rusq_ref__BOSS()),
            Rdsq( get_BEptr()->Rdsq_ref__BOSS()),
            Rsl( get_BEptr()->Rsl_ref__BOSS()),
            Rsv( get_BEptr()->Rsv_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline CoupSUSY::CoupSUSY(const CoupSUSY& in) :
            Couplings(in.get_BEptr()->pointer_copy__BOSS()),
            isInit( get_BEptr()->isInit_ref__BOSS()),
            isNMSSM( get_BEptr()->isNMSSM_ref__BOSS()),
            mWpole( get_BEptr()->mWpole_ref__BOSS()),
            wWpole( get_BEptr()->wWpole_ref__BOSS()),
            mZpole( get_BEptr()->mZpole_ref__BOSS()),
            wZpole( get_BEptr()->wZpole_ref__BOSS()),
            mW( get_BEptr()->mW_ref__BOSS()),
            mZ( get_BEptr()->mZ_ref__BOSS()),
            sin2W( get_BEptr()->sin2W_ref__BOSS()),
            sinW( get_BEptr()->sinW_ref__BOSS()),
            cosW( get_BEptr()->cosW_ref__BOSS()),
            tanb( get_BEptr()->tanb_ref__BOSS()),
            cosb( get_BEptr()->cosb_ref__BOSS()),
            sinb( get_BEptr()->sinb_ref__BOSS()),
            muHiggs( get_BEptr()->muHiggs_ref__BOSS()),
            alphaHiggs( get_BEptr()->alphaHiggs_ref__BOSS()),
            mAHiggs( get_BEptr()->mAHiggs_ref__BOSS()),
            LsddG( get_BEptr()->LsddG_ref__BOSS()),
            RsddG( get_BEptr()->RsddG_ref__BOSS()),
            LsuuG( get_BEptr()->LsuuG_ref__BOSS()),
            RsuuG( get_BEptr()->RsuuG_ref__BOSS()),
            OLpp( get_BEptr()->OLpp_ref__BOSS()),
            ORpp( get_BEptr()->ORpp_ref__BOSS()),
            OLp( get_BEptr()->OLp_ref__BOSS()),
            ORp( get_BEptr()->ORp_ref__BOSS()),
            OL( get_BEptr()->OL_ref__BOSS()),
            OR( get_BEptr()->OR_ref__BOSS()),
            LqqZ( get_BEptr()->LqqZ_ref__BOSS()),
            RqqZ( get_BEptr()->RqqZ_ref__BOSS()),
            LsdsdZ( get_BEptr()->LsdsdZ_ref__BOSS()),
            RsdsdZ( get_BEptr()->RsdsdZ_ref__BOSS()),
            LsusuZ( get_BEptr()->LsusuZ_ref__BOSS()),
            RsusuZ( get_BEptr()->RsusuZ_ref__BOSS()),
            LudW( get_BEptr()->LudW_ref__BOSS()),
            RudW( get_BEptr()->RudW_ref__BOSS()),
            LsusdW( get_BEptr()->LsusdW_ref__BOSS()),
            RsusdW( get_BEptr()->RsusdW_ref__BOSS()),
            LsddX( get_BEptr()->LsddX_ref__BOSS()),
            RsddX( get_BEptr()->RsddX_ref__BOSS()),
            LsuuX( get_BEptr()->LsuuX_ref__BOSS()),
            RsuuX( get_BEptr()->RsuuX_ref__BOSS()),
            LsduX( get_BEptr()->LsduX_ref__BOSS()),
            RsduX( get_BEptr()->RsduX_ref__BOSS()),
            LsudX( get_BEptr()->LsudX_ref__BOSS()),
            RsudX( get_BEptr()->RsudX_ref__BOSS()),
            LllZ( get_BEptr()->LllZ_ref__BOSS()),
            RllZ( get_BEptr()->RllZ_ref__BOSS()),
            LlvW( get_BEptr()->LlvW_ref__BOSS()),
            RlvW( get_BEptr()->RlvW_ref__BOSS()),
            LslslZ( get_BEptr()->LslslZ_ref__BOSS()),
            RslslZ( get_BEptr()->RslslZ_ref__BOSS()),
            LsvsvZ( get_BEptr()->LsvsvZ_ref__BOSS()),
            RsvsvZ( get_BEptr()->RsvsvZ_ref__BOSS()),
            LslsvW( get_BEptr()->LslsvW_ref__BOSS()),
            RslsvW( get_BEptr()->RslsvW_ref__BOSS()),
            LsvvX( get_BEptr()->LsvvX_ref__BOSS()),
            RsvvX( get_BEptr()->RsvvX_ref__BOSS()),
            LsllX( get_BEptr()->LsllX_ref__BOSS()),
            RsllX( get_BEptr()->RsllX_ref__BOSS()),
            LsvlX( get_BEptr()->LsvlX_ref__BOSS()),
            RsvlX( get_BEptr()->RsvlX_ref__BOSS()),
            LslvX( get_BEptr()->LslvX_ref__BOSS()),
            RslvX( get_BEptr()->RslvX_ref__BOSS()),
            rvLLE( get_BEptr()->rvLLE_ref__BOSS()),
            rvLQD( get_BEptr()->rvLQD_ref__BOSS()),
            rvUDD( get_BEptr()->rvUDD_ref__BOSS()),
            isLLE( get_BEptr()->isLLE_ref__BOSS()),
            isLQD( get_BEptr()->isLQD_ref__BOSS()),
            isUDD( get_BEptr()->isUDD_ref__BOSS()),
            Rusq( get_BEptr()->Rusq_ref__BOSS()),
            Rdsq( get_BEptr()->Rdsq_ref__BOSS()),
            Rsl( get_BEptr()->Rsl_ref__BOSS()),
            Rsv( get_BEptr()->Rsv_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline CoupSUSY& CoupSUSY::operator=(const CoupSUSY& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline CoupSUSY::~CoupSUSY()
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
        inline Abstract_CoupSUSY* Pythia8::CoupSUSY::get_BEptr() const
        {
            return dynamic_cast<Abstract_CoupSUSY*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CoupSUSY_def_Pythia_8_212_h__ */
