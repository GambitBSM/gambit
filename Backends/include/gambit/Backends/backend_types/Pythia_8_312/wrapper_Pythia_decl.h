#ifndef __wrapper_Pythia_decl_Pythia_8_312_h__
#define __wrapper_Pythia_decl_Pythia_8_312_h__

#include <cstddef>
#include <string>
#include <istream>
#include <vector>
#include <ostream>
#include <sstream>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Pythia.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Logger_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_CoupSM_decl.h"
#include "wrapper_CoupSUSY_decl.h"
#include "wrapper_SLHAinterface_decl.h"
#include "wrapper_BeamParticle_decl.h"
#include "wrapper_PartonLevel_decl.h"
#include "wrapper_SigmaTotal_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Pythia : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Pythia* (*__factory0)(std::string, bool);
                static Abstract_Pythia* (*__factory1)(std::string);
                static Abstract_Pythia* (*__factory2)();
                static Abstract_Pythia* (*__factory3)(Pythia8::Settings&, Pythia8::ParticleData&, bool);
                static Abstract_Pythia* (*__factory4)(Pythia8::Settings&, Pythia8::ParticleData&);
                static Abstract_Pythia* (*__factory5)(std::istream&, std::istream&, bool);
                static Abstract_Pythia* (*__factory6)(std::istream&, std::istream&);
        
                // -- Other member variables: 
            public:
                Pythia8::Event& process;
                Pythia8::Event& event;
                const Pythia8::Info& info;
                Pythia8::Logger& logger;
                Pythia8::Settings& settings;
                Pythia8::ParticleData& particleData;
                Pythia8::Rndm& rndm;
                Pythia8::CoupSM& coupSM;
                Pythia8::CoupSUSY& coupSUSY;
                Pythia8::SLHAinterface& slhaInterface;
                const Pythia8::BeamParticle& beamA;
                const Pythia8::BeamParticle& beamB;
        
                // Member functions: 
            public:
                bool checkVersion();
        
                bool readString(std::string arg_1, bool warn, int subrun);
        
                bool readString(std::string arg_1, bool warn);
        
                bool readString(std::string arg_1);
        
                bool readFile(std::string fileName, bool warn, int subrun);
        
                bool readFile(std::string fileName, bool warn);
        
                bool readFile(std::string fileName);
        
                bool readFile(std::string fileName, int subrun);
        
                bool readFile(std::istream& is, bool warn, int subrun);
        
                bool readFile(std::istream& is, bool warn);
        
                bool readFile(std::istream& is);
        
                bool readFile();
        
                bool readFile(std::istream& is, int subrun);
        
                bool init(std::ostream& os);
        
                bool init();
        
                bool next();
        
                bool next(int procTypeIn);
        
                bool setBeamIDs(int idAin, int idBin);
        
                bool setBeamIDs(int idAin);
        
                bool setKinematics(double eCMIn);
        
                bool setKinematics(double eAIn, double eBIn);
        
                bool setKinematics(double pxAIn, double pyAIn, double pzAIn, double pxBIn, double pyBIn, double pzBIn);
        
                bool setKinematics(Pythia8::Vec4 pAIn, Pythia8::Vec4 pBIn);
        
                int forceTimeShower(int iBeg, int iEnd, double pTmax, int nBranchMax);
        
                int forceTimeShower(int iBeg, int iEnd, double pTmax);
        
                bool forceHadronLevel(bool findJunctions);
        
                bool forceHadronLevel();
        
                bool moreDecays();
        
                bool moreDecays(int index);
        
                bool forceRHadronDecays();
        
                bool doLowEnergyProcess(int i1, int i2, int procTypeIn);
        
                double getSigmaTotal();
        
                double getSigmaTotal(double eCM12, int mixLoHi);
        
                double getSigmaTotal(double eCM12);
        
                double getSigmaTotal(int id1, int id2, double eCM12, int mixLoHi);
        
                double getSigmaTotal(int id1, int id2, double eCM12);
        
                double getSigmaTotal(int id1, int id2, double eCM12, double m1, double m2, int mixLoHi);
        
                double getSigmaTotal(int id1, int id2, double eCM12, double m1, double m2);
        
                double getSigmaPartial(int procTypeIn);
        
                double getSigmaPartial(double eCM12, int procTypeIn, int mixLoHi);
        
                double getSigmaPartial(double eCM12, int procTypeIn);
        
                double getSigmaPartial(int id1, int id2, double eCM12, int procTypeIn, int mixLoHi);
        
                double getSigmaPartial(int id1, int id2, double eCM12, int procTypeIn);
        
                double getSigmaPartial(int id1, int id2, double eCM12, double m1, double m2, int procTypeIn, int mixLoHi);
        
                double getSigmaPartial(int id1, int id2, double eCM12, double m1, double m2, int procTypeIn);
        
                void LHAeventList();
        
                bool LHAeventSkip(int nSkip);
        
                void stat();
        
                bool flag(std::string key);
        
                int mode(std::string key);
        
                double parm(std::string key);
        
                ::std::string word(std::string key);
        
                double getSigmaMaxSum();
        
        
                // Wrappers for original constructors: 
            public:
                Pythia(std::string xmlDir, bool printBanner);
                Pythia(std::string xmlDir);
                Pythia();
                Pythia(Pythia8::Settings& settingsIn, Pythia8::ParticleData& particleDataIn, bool printBanner);
                Pythia(Pythia8::Settings& settingsIn, Pythia8::ParticleData& particleDataIn);
                Pythia(std::istream& settingsStrings, std::istream& particleDataStrings, bool printBanner);
                Pythia(std::istream& settingsStrings, std::istream& particleDataStrings);
        
                // Special pointer-based constructor: 
                Pythia(Abstract_Pythia* in);
        
                // Destructor: 
                ~Pythia();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Pythia* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Pythia_decl_Pythia_8_312_h__ */
