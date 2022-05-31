#ifndef __wrapper_SigmaProcess_decl_Pythia_8_212_h__
#define __wrapper_SigmaProcess_decl_Pythia_8_212_h__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_SigmaProcess.h"
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
        
        class SigmaProcess : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_SigmaProcess* (*__factory0)(const Pythia8::SigmaProcess&);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void init(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Rndm* rndmPtrIn, Pythia8::BeamParticle* beamAPtrIn, Pythia8::BeamParticle* beamBPtrIn, Pythia8::Couplings* couplings, Pythia8::SigmaTotal* sigmaTotPtrIn, Pythia8::SLHAinterface* slhaInterfacePtrIn);
        
                void init(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Rndm* rndmPtrIn, Pythia8::BeamParticle* beamAPtrIn, Pythia8::BeamParticle* beamBPtrIn, Pythia8::Couplings* couplings, Pythia8::SigmaTotal* sigmaTotPtrIn);
        
                void init(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Rndm* rndmPtrIn, Pythia8::BeamParticle* beamAPtrIn, Pythia8::BeamParticle* beamBPtrIn, Pythia8::Couplings* couplings);
        
                void initProc();
        
                bool initFlux();
        
                void set1Kin(double arg_1, double arg_2, double arg_3);
        
                void set2Kin(double arg_1, double arg_2, double arg_3, double arg_4, double arg_5, double arg_6, double arg_7, double arg_8);
        
                void set2KinMPI(double arg_1, double arg_2, double arg_3, double arg_4, double arg_5, double arg_6, double arg_7, bool arg_8, double arg_9, double arg_10);
        
                void set3Kin(double arg_1, double arg_2, double arg_3, Pythia8::Vec4 arg_4, Pythia8::Vec4 arg_5, Pythia8::Vec4 arg_6, double arg_7, double arg_8, double arg_9, double arg_10, double arg_11, double arg_12);
        
                void sigmaKin();
        
                double sigmaHat();
        
                double sigmaHatWrap(int id1in, int id2in);
        
                double sigmaHatWrap(int id1in);
        
                double sigmaHatWrap();
        
                double sigmaPDF();
        
                void pickInState(int id1in, int id2in);
        
                void pickInState(int id1in);
        
                void pickInState();
        
                void setIdColAcol();
        
                bool final2KinMPI(int arg_1, int arg_2, Pythia8::Vec4 arg_3, Pythia8::Vec4 arg_4, double arg_5, double arg_6);
        
                bool final2KinMPI(int arg_1, int arg_2, Pythia8::Vec4 arg_3, Pythia8::Vec4 arg_4, double arg_5);
        
                bool final2KinMPI(int arg_1, int arg_2, Pythia8::Vec4 arg_3, Pythia8::Vec4 arg_4);
        
                bool final2KinMPI(int arg_1, int arg_2, Pythia8::Vec4 arg_3);
        
                bool final2KinMPI(int arg_1, int arg_2);
        
                bool final2KinMPI(int arg_1);
        
                bool final2KinMPI();
        
                double weightDecayFlav(Pythia8::Event& arg_1);
        
                double weightDecay(Pythia8::Event& arg_1, int arg_2, int arg_3);
        
                void setScale();
        
                ::std::basic_string<char> name() const;
        
                int code() const;
        
                int nFinal() const;
        
                ::std::basic_string<char> inFlux() const;
        
                bool convert2mb() const;
        
                bool convertM2() const;
        
                bool isLHA() const;
        
                bool isNonDiff() const;
        
                bool isResolved() const;
        
                bool isDiffA() const;
        
                bool isDiffB() const;
        
                bool isDiffC() const;
        
                bool isSUSY() const;
        
                bool allowNegativeSigma() const;
        
                int id3Mass() const;
        
                int id4Mass() const;
        
                int id5Mass() const;
        
                int resonanceA() const;
        
                int resonanceB() const;
        
                bool isSChannel() const;
        
                int idSChannel() const;
        
                bool isQCD3body() const;
        
                int idTchan1() const;
        
                int idTchan2() const;
        
                double tChanFracPow1() const;
        
                double tChanFracPow2() const;
        
                bool useMirrorWeight() const;
        
                int gmZmode() const;
        
                bool swappedTU() const;
        
                int id(int i) const;
        
                int col(int i) const;
        
                int acol(int i) const;
        
                double m(int i) const;
        
                Pythia8::Particle getParton(int i) const;
        
                double Q2Ren() const;
        
                double alphaEMRen() const;
        
                double alphaSRen() const;
        
                double Q2Fac() const;
        
                double pdf1() const;
        
                double pdf2() const;
        
                double thetaMPI() const;
        
                double phiMPI() const;
        
                double sHBetaMPI() const;
        
                double pT2MPI() const;
        
                double pTMPIFin() const;
        
                void saveKin();
        
                void loadKin();
        
                void swapKin();
        
        
                // Wrappers for original constructors: 
            public:
                SigmaProcess(const Pythia8::SigmaProcess& arg_1);
        
                // Special pointer-based constructor: 
                SigmaProcess(Abstract_SigmaProcess* in);
        
                // Assignment operator: 
                SigmaProcess& operator=(const SigmaProcess& in);
        
                // Destructor: 
                ~SigmaProcess();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_SigmaProcess* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SigmaProcess_decl_Pythia_8_212_h__ */
