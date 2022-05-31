#ifndef __wrapper_SigmaProcess_def_Pythia_8_212_h__
#define __wrapper_SigmaProcess_def_Pythia_8_212_h__

#include <string>
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_BeamParticle_decl.h"
#include "wrapper_Couplings_decl.h"
#include "wrapper_SigmaTotal_decl.h"
#include "wrapper_SLHAinterface_decl.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Particle_decl.h"
#include "wrapper_SusyLesHouches_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void SigmaProcess::init(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Rndm* rndmPtrIn, Pythia8::BeamParticle* beamAPtrIn, Pythia8::BeamParticle* beamBPtrIn, Pythia8::Couplings* couplings, Pythia8::SigmaTotal* sigmaTotPtrIn, Pythia8::SLHAinterface* slhaInterfacePtrIn)
        {
            get_BEptr()->init__BOSS((*infoPtrIn).get_BEptr(), (*settingsPtrIn).get_BEptr(), (*particleDataPtrIn).get_BEptr(), (*rndmPtrIn).get_BEptr(), (*beamAPtrIn).get_BEptr(), (*beamBPtrIn).get_BEptr(), (*couplings).get_BEptr(), (*sigmaTotPtrIn).get_BEptr(), (*slhaInterfacePtrIn).get_BEptr());
        }
        
        inline void SigmaProcess::init(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Rndm* rndmPtrIn, Pythia8::BeamParticle* beamAPtrIn, Pythia8::BeamParticle* beamBPtrIn, Pythia8::Couplings* couplings, Pythia8::SigmaTotal* sigmaTotPtrIn)
        {
            get_BEptr()->init__BOSS((*infoPtrIn).get_BEptr(), (*settingsPtrIn).get_BEptr(), (*particleDataPtrIn).get_BEptr(), (*rndmPtrIn).get_BEptr(), (*beamAPtrIn).get_BEptr(), (*beamBPtrIn).get_BEptr(), (*couplings).get_BEptr(), (*sigmaTotPtrIn).get_BEptr());
        }
        
        inline void SigmaProcess::init(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Rndm* rndmPtrIn, Pythia8::BeamParticle* beamAPtrIn, Pythia8::BeamParticle* beamBPtrIn, Pythia8::Couplings* couplings)
        {
            get_BEptr()->init__BOSS((*infoPtrIn).get_BEptr(), (*settingsPtrIn).get_BEptr(), (*particleDataPtrIn).get_BEptr(), (*rndmPtrIn).get_BEptr(), (*beamAPtrIn).get_BEptr(), (*beamBPtrIn).get_BEptr(), (*couplings).get_BEptr());
        }
        
        inline void SigmaProcess::initProc()
        {
            get_BEptr()->initProc();
        }
        
        inline bool SigmaProcess::initFlux()
        {
            return get_BEptr()->initFlux();
        }
        
        inline void SigmaProcess::set1Kin(double arg_1, double arg_2, double arg_3)
        {
            get_BEptr()->set1Kin(arg_1, arg_2, arg_3);
        }
        
        inline void SigmaProcess::set2Kin(double arg_1, double arg_2, double arg_3, double arg_4, double arg_5, double arg_6, double arg_7, double arg_8)
        {
            get_BEptr()->set2Kin(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8);
        }
        
        inline void SigmaProcess::set2KinMPI(double arg_1, double arg_2, double arg_3, double arg_4, double arg_5, double arg_6, double arg_7, bool arg_8, double arg_9, double arg_10)
        {
            get_BEptr()->set2KinMPI(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10);
        }
        
        inline void SigmaProcess::set3Kin(double arg_1, double arg_2, double arg_3, Pythia8::Vec4 arg_4, Pythia8::Vec4 arg_5, Pythia8::Vec4 arg_6, double arg_7, double arg_8, double arg_9, double arg_10, double arg_11, double arg_12)
        {
            get_BEptr()->set3Kin__BOSS(arg_1, arg_2, arg_3, *arg_4.get_BEptr(), *arg_5.get_BEptr(), *arg_6.get_BEptr(), arg_7, arg_8, arg_9, arg_10, arg_11, arg_12);
        }
        
        inline void SigmaProcess::sigmaKin()
        {
            get_BEptr()->sigmaKin();
        }
        
        inline double SigmaProcess::sigmaHat()
        {
            return get_BEptr()->sigmaHat();
        }
        
        inline double SigmaProcess::sigmaHatWrap(int id1in, int id2in)
        {
            return get_BEptr()->sigmaHatWrap(id1in, id2in);
        }
        
        inline double SigmaProcess::sigmaHatWrap(int id1in)
        {
            return get_BEptr()->sigmaHatWrap__BOSS(id1in);
        }
        
        inline double SigmaProcess::sigmaHatWrap()
        {
            return get_BEptr()->sigmaHatWrap__BOSS();
        }
        
        inline double SigmaProcess::sigmaPDF()
        {
            return get_BEptr()->sigmaPDF();
        }
        
        inline void SigmaProcess::pickInState(int id1in, int id2in)
        {
            get_BEptr()->pickInState(id1in, id2in);
        }
        
        inline void SigmaProcess::pickInState(int id1in)
        {
            get_BEptr()->pickInState__BOSS(id1in);
        }
        
        inline void SigmaProcess::pickInState()
        {
            get_BEptr()->pickInState__BOSS();
        }
        
        inline void SigmaProcess::setIdColAcol()
        {
            get_BEptr()->setIdColAcol();
        }
        
        inline bool SigmaProcess::final2KinMPI(int arg_1, int arg_2, Pythia8::Vec4 arg_3, Pythia8::Vec4 arg_4, double arg_5, double arg_6)
        {
            return get_BEptr()->final2KinMPI__BOSS(arg_1, arg_2, *arg_3.get_BEptr(), *arg_4.get_BEptr(), arg_5, arg_6);
        }
        
        inline bool SigmaProcess::final2KinMPI(int arg_1, int arg_2, Pythia8::Vec4 arg_3, Pythia8::Vec4 arg_4, double arg_5)
        {
            return get_BEptr()->final2KinMPI__BOSS(arg_1, arg_2, *arg_3.get_BEptr(), *arg_4.get_BEptr(), arg_5);
        }
        
        inline bool SigmaProcess::final2KinMPI(int arg_1, int arg_2, Pythia8::Vec4 arg_3, Pythia8::Vec4 arg_4)
        {
            return get_BEptr()->final2KinMPI__BOSS(arg_1, arg_2, *arg_3.get_BEptr(), *arg_4.get_BEptr());
        }
        
        inline bool SigmaProcess::final2KinMPI(int arg_1, int arg_2, Pythia8::Vec4 arg_3)
        {
            return get_BEptr()->final2KinMPI__BOSS(arg_1, arg_2, *arg_3.get_BEptr());
        }
        
        inline bool SigmaProcess::final2KinMPI(int arg_1, int arg_2)
        {
            return get_BEptr()->final2KinMPI__BOSS(arg_1, arg_2);
        }
        
        inline bool SigmaProcess::final2KinMPI(int arg_1)
        {
            return get_BEptr()->final2KinMPI__BOSS(arg_1);
        }
        
        inline bool SigmaProcess::final2KinMPI()
        {
            return get_BEptr()->final2KinMPI__BOSS();
        }
        
        inline double SigmaProcess::weightDecayFlav(Pythia8::Event& arg_1)
        {
            return get_BEptr()->weightDecayFlav__BOSS(*arg_1.get_BEptr());
        }
        
        inline double SigmaProcess::weightDecay(Pythia8::Event& arg_1, int arg_2, int arg_3)
        {
            return get_BEptr()->weightDecay__BOSS(*arg_1.get_BEptr(), arg_2, arg_3);
        }
        
        inline void SigmaProcess::setScale()
        {
            get_BEptr()->setScale();
        }
        
        inline ::std::basic_string<char> SigmaProcess::name() const
        {
            return get_BEptr()->name();
        }
        
        inline int SigmaProcess::code() const
        {
            return get_BEptr()->code();
        }
        
        inline int SigmaProcess::nFinal() const
        {
            return get_BEptr()->nFinal();
        }
        
        inline ::std::basic_string<char> SigmaProcess::inFlux() const
        {
            return get_BEptr()->inFlux();
        }
        
        inline bool SigmaProcess::convert2mb() const
        {
            return get_BEptr()->convert2mb();
        }
        
        inline bool SigmaProcess::convertM2() const
        {
            return get_BEptr()->convertM2();
        }
        
        inline bool SigmaProcess::isLHA() const
        {
            return get_BEptr()->isLHA();
        }
        
        inline bool SigmaProcess::isNonDiff() const
        {
            return get_BEptr()->isNonDiff();
        }
        
        inline bool SigmaProcess::isResolved() const
        {
            return get_BEptr()->isResolved();
        }
        
        inline bool SigmaProcess::isDiffA() const
        {
            return get_BEptr()->isDiffA();
        }
        
        inline bool SigmaProcess::isDiffB() const
        {
            return get_BEptr()->isDiffB();
        }
        
        inline bool SigmaProcess::isDiffC() const
        {
            return get_BEptr()->isDiffC();
        }
        
        inline bool SigmaProcess::isSUSY() const
        {
            return get_BEptr()->isSUSY();
        }
        
        inline bool SigmaProcess::allowNegativeSigma() const
        {
            return get_BEptr()->allowNegativeSigma();
        }
        
        inline int SigmaProcess::id3Mass() const
        {
            return get_BEptr()->id3Mass();
        }
        
        inline int SigmaProcess::id4Mass() const
        {
            return get_BEptr()->id4Mass();
        }
        
        inline int SigmaProcess::id5Mass() const
        {
            return get_BEptr()->id5Mass();
        }
        
        inline int SigmaProcess::resonanceA() const
        {
            return get_BEptr()->resonanceA();
        }
        
        inline int SigmaProcess::resonanceB() const
        {
            return get_BEptr()->resonanceB();
        }
        
        inline bool SigmaProcess::isSChannel() const
        {
            return get_BEptr()->isSChannel();
        }
        
        inline int SigmaProcess::idSChannel() const
        {
            return get_BEptr()->idSChannel();
        }
        
        inline bool SigmaProcess::isQCD3body() const
        {
            return get_BEptr()->isQCD3body();
        }
        
        inline int SigmaProcess::idTchan1() const
        {
            return get_BEptr()->idTchan1();
        }
        
        inline int SigmaProcess::idTchan2() const
        {
            return get_BEptr()->idTchan2();
        }
        
        inline double SigmaProcess::tChanFracPow1() const
        {
            return get_BEptr()->tChanFracPow1();
        }
        
        inline double SigmaProcess::tChanFracPow2() const
        {
            return get_BEptr()->tChanFracPow2();
        }
        
        inline bool SigmaProcess::useMirrorWeight() const
        {
            return get_BEptr()->useMirrorWeight();
        }
        
        inline int SigmaProcess::gmZmode() const
        {
            return get_BEptr()->gmZmode();
        }
        
        inline bool SigmaProcess::swappedTU() const
        {
            return get_BEptr()->swappedTU();
        }
        
        inline int SigmaProcess::id(int i) const
        {
            return get_BEptr()->id(i);
        }
        
        inline int SigmaProcess::col(int i) const
        {
            return get_BEptr()->col(i);
        }
        
        inline int SigmaProcess::acol(int i) const
        {
            return get_BEptr()->acol(i);
        }
        
        inline double SigmaProcess::m(int i) const
        {
            return get_BEptr()->m(i);
        }
        
        inline Pythia8::Particle SigmaProcess::getParton(int i) const
        {
            return Pythia8::Particle( const_cast<const Abstract_SigmaProcess*>(get_BEptr())->getParton__BOSS(i) );
        }
        
        inline double SigmaProcess::Q2Ren() const
        {
            return get_BEptr()->Q2Ren();
        }
        
        inline double SigmaProcess::alphaEMRen() const
        {
            return get_BEptr()->alphaEMRen();
        }
        
        inline double SigmaProcess::alphaSRen() const
        {
            return get_BEptr()->alphaSRen();
        }
        
        inline double SigmaProcess::Q2Fac() const
        {
            return get_BEptr()->Q2Fac();
        }
        
        inline double SigmaProcess::pdf1() const
        {
            return get_BEptr()->pdf1();
        }
        
        inline double SigmaProcess::pdf2() const
        {
            return get_BEptr()->pdf2();
        }
        
        inline double SigmaProcess::thetaMPI() const
        {
            return get_BEptr()->thetaMPI();
        }
        
        inline double SigmaProcess::phiMPI() const
        {
            return get_BEptr()->phiMPI();
        }
        
        inline double SigmaProcess::sHBetaMPI() const
        {
            return get_BEptr()->sHBetaMPI();
        }
        
        inline double SigmaProcess::pT2MPI() const
        {
            return get_BEptr()->pT2MPI();
        }
        
        inline double SigmaProcess::pTMPIFin() const
        {
            return get_BEptr()->pTMPIFin();
        }
        
        inline void SigmaProcess::saveKin()
        {
            get_BEptr()->saveKin();
        }
        
        inline void SigmaProcess::loadKin()
        {
            get_BEptr()->loadKin();
        }
        
        inline void SigmaProcess::swapKin()
        {
            get_BEptr()->swapKin();
        }
        
        
        // Wrappers for original constructors: 
        inline SigmaProcess::SigmaProcess(const Pythia8::SigmaProcess& arg_1) :
            WrapperBase(__factory0(arg_1))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline SigmaProcess::SigmaProcess(Abstract_SigmaProcess* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline SigmaProcess& SigmaProcess::operator=(const SigmaProcess& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline SigmaProcess::~SigmaProcess()
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
        inline Abstract_SigmaProcess* Pythia8::SigmaProcess::get_BEptr() const
        {
            return dynamic_cast<Abstract_SigmaProcess*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SigmaProcess_def_Pythia_8_212_h__ */
