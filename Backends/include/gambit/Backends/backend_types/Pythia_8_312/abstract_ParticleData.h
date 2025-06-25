#ifndef __abstract_ParticleData_Pythia_8_312_h__
#define __abstract_ParticleData_Pythia_8_312_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <istream>
#include <ostream>
#include <vector>
#include <map>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Logger_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_CoupSM_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_ParticleData : public virtual AbstractBase
        {
            public:
    
                virtual Pythia8::Abstract_ParticleData& operator_equal__BOSS(const Pythia8::Abstract_ParticleData&) =0;
    
                virtual void initPtrs__BOSS(Pythia8::Abstract_Info*) =0;
    
                virtual bool init(std::string) =0;
    
                virtual bool init__BOSS() =0;
    
                virtual bool init__BOSS(const Pythia8::Abstract_ParticleData&) =0;
    
                virtual bool init(std::istream&) =0;
    
                virtual bool reInit(std::string, bool) =0;
    
                virtual bool reInit__BOSS(std::string) =0;
    
                virtual bool readXML(std::string, bool) =0;
    
                virtual bool readXML__BOSS(std::string) =0;
    
                virtual void listXML(std::string) =0;
    
                virtual bool readXML(std::istream&, bool) =0;
    
                virtual bool readXML__BOSS(std::istream&) =0;
    
                virtual bool copyXML__BOSS(const Pythia8::Abstract_ParticleData&) =0;
    
                virtual bool loadXML(std::string, bool) =0;
    
                virtual bool loadXML__BOSS(std::string) =0;
    
                virtual bool loadXML(std::istream&, bool) =0;
    
                virtual bool loadXML__BOSS(std::istream&) =0;
    
                virtual bool processXML(bool) =0;
    
                virtual bool processXML__BOSS() =0;
    
                virtual bool readFF(std::string, bool) =0;
    
                virtual bool readFF__BOSS(std::string) =0;
    
                virtual bool readFF(std::istream&, bool) =0;
    
                virtual bool readFF__BOSS(std::istream&) =0;
    
                virtual void listFF(std::string) =0;
    
                virtual bool readString(std::string, bool) =0;
    
                virtual bool readString__BOSS(std::string) =0;
    
                virtual bool readingFailed() =0;
    
                virtual void listAll(std::ostream&) =0;
    
                virtual void listAll() =0;
    
                virtual void listChanged(bool) =0;
    
                virtual void listChanged__BOSS() =0;
    
                virtual void list(std::ostream&, bool, bool) =0;
    
                virtual void list__BOSS(std::ostream&, bool) =0;
    
                virtual void list__BOSS(std::ostream&) =0;
    
                virtual void list(bool, bool) =0;
    
                virtual void list__BOSS(bool) =0;
    
                virtual void list__BOSS() =0;
    
                virtual void list(int) =0;
    
                virtual void list(std::vector<int>) =0;
    
                virtual ::std::vector<std::string> getReadHistory(int) =0;
    
                virtual ::std::vector<std::string> getReadHistory__BOSS() =0;
    
                virtual void checkTable(int) =0;
    
                virtual void checkTable__BOSS() =0;
    
                virtual void addParticle(int, std::string, int, int, int, double, double, double, double, double, bool) =0;
    
                virtual void addParticle__BOSS(int, std::string, int, int, int, double, double, double, double, double) =0;
    
                virtual void addParticle__BOSS(int, std::string, int, int, int, double, double, double, double) =0;
    
                virtual void addParticle__BOSS(int, std::string, int, int, int, double, double, double) =0;
    
                virtual void addParticle__BOSS(int, std::string, int, int, int, double, double) =0;
    
                virtual void addParticle__BOSS(int, std::string, int, int, int, double) =0;
    
                virtual void addParticle__BOSS(int, std::string, int, int, int) =0;
    
                virtual void addParticle__BOSS(int, std::string, int, int) =0;
    
                virtual void addParticle__BOSS(int, std::string, int) =0;
    
                virtual void addParticle__BOSS(int, std::string) =0;
    
                virtual void addParticle__BOSS(int) =0;
    
                virtual void addParticle(int, std::string, std::string, int, int, int, double, double, double, double, double, bool) =0;
    
                virtual void addParticle__BOSS(int, std::string, std::string, int, int, int, double, double, double, double, double) =0;
    
                virtual void addParticle__BOSS(int, std::string, std::string, int, int, int, double, double, double, double) =0;
    
                virtual void addParticle__BOSS(int, std::string, std::string, int, int, int, double, double, double) =0;
    
                virtual void addParticle__BOSS(int, std::string, std::string, int, int, int, double, double) =0;
    
                virtual void addParticle__BOSS(int, std::string, std::string, int, int, int, double) =0;
    
                virtual void addParticle__BOSS(int, std::string, std::string, int, int, int) =0;
    
                virtual void addParticle__BOSS(int, std::string, std::string, int, int) =0;
    
                virtual void addParticle__BOSS(int, std::string, std::string, int) =0;
    
                virtual void addParticle__BOSS(int, std::string, std::string) =0;
    
                virtual void setAll(int, std::string, std::string, int, int, int, double, double, double, double, double, bool) =0;
    
                virtual void setAll__BOSS(int, std::string, std::string, int, int, int, double, double, double, double, double) =0;
    
                virtual void setAll__BOSS(int, std::string, std::string, int, int, int, double, double, double, double) =0;
    
                virtual void setAll__BOSS(int, std::string, std::string, int, int, int, double, double, double) =0;
    
                virtual void setAll__BOSS(int, std::string, std::string, int, int, int, double, double) =0;
    
                virtual void setAll__BOSS(int, std::string, std::string, int, int, int, double) =0;
    
                virtual void setAll__BOSS(int, std::string, std::string, int, int, int) =0;
    
                virtual void setAll__BOSS(int, std::string, std::string, int, int) =0;
    
                virtual void setAll__BOSS(int, std::string, std::string, int) =0;
    
                virtual void setAll__BOSS(int, std::string, std::string) =0;
    
                virtual bool isParticle(int) const =0;
    
                virtual int nextId(int) const =0;
    
                virtual void name(int, std::string) =0;
    
                virtual void antiName(int, std::string) =0;
    
                virtual void names(int, std::string, std::string) =0;
    
                virtual void spinType(int, int) =0;
    
                virtual void chargeType(int, int) =0;
    
                virtual void colType(int, int) =0;
    
                virtual void m0(int, double) =0;
    
                virtual void mWidth(int, double) =0;
    
                virtual void mMin(int, double) =0;
    
                virtual void mMax(int, double) =0;
    
                virtual void tau0(int, double) =0;
    
                virtual void isResonance(int, bool) =0;
    
                virtual void mayDecay(int, bool) =0;
    
                virtual void tauCalc(int, bool) =0;
    
                virtual void doExternalDecay(int, bool) =0;
    
                virtual void varWidth(int, bool) =0;
    
                virtual void isVisible(int, bool) =0;
    
                virtual void doForceWidth(int, bool) =0;
    
                virtual void hasChanged(int, bool) =0;
    
                virtual bool hasAnti(int) const =0;
    
                virtual int antiId(int) const =0;
    
                virtual ::std::string name(int) const =0;
    
                virtual int spinType(int) const =0;
    
                virtual int chargeType(int) const =0;
    
                virtual double charge(int) const =0;
    
                virtual int colType(int) const =0;
    
                virtual double m0(int) const =0;
    
                virtual double mWidth(int) const =0;
    
                virtual double mMin(int) const =0;
    
                virtual double m0Min(int) const =0;
    
                virtual double mMax(int) const =0;
    
                virtual double m0Max(int) const =0;
    
                virtual double tau0(int) const =0;
    
                virtual bool isResonance(int) const =0;
    
                virtual bool mayDecay(int) const =0;
    
                virtual bool tauCalc(int) const =0;
    
                virtual bool doExternalDecay(int) const =0;
    
                virtual bool isVisible(int) const =0;
    
                virtual bool doForceWidth(int) const =0;
    
                virtual bool hasChanged(int) const =0;
    
                virtual bool hasChangedMMin(int) const =0;
    
                virtual bool hasChangedMMax(int) const =0;
    
                virtual bool useBreitWigner(int) const =0;
    
                virtual bool varWidth(int) const =0;
    
                virtual double constituentMass(int) const =0;
    
                virtual double mSel(int) const =0;
    
                virtual double mRun(int, double) const =0;
    
                virtual bool canDecay(int) const =0;
    
                virtual bool isLepton(int) const =0;
    
                virtual bool isQuark(int) const =0;
    
                virtual bool isGluon(int) const =0;
    
                virtual bool isDiquark(int) const =0;
    
                virtual bool isParton(int) const =0;
    
                virtual bool isHadron(int) const =0;
    
                virtual bool isMeson(int) const =0;
    
                virtual bool isBaryon(int) const =0;
    
                virtual bool isOnium(int) const =0;
    
                virtual bool isExotic(int) const =0;
    
                virtual bool isOctetHadron(int) const =0;
    
                virtual int heaviestQuark(int) const =0;
    
                virtual int baryonNumberType(int) const =0;
    
                virtual int nQuarksInCode(int, int) const =0;
    
                virtual void rescaleBR(int, double) =0;
    
                virtual void rescaleBR__BOSS(int) =0;
    
                virtual void resInit(int) =0;
    
                virtual double resWidth(int, double, int, bool, bool) =0;
    
                virtual double resWidth__BOSS(int, double, int, bool) =0;
    
                virtual double resWidth__BOSS(int, double, int) =0;
    
                virtual double resWidth__BOSS(int, double) =0;
    
                virtual double resWidthOpen(int, double, int) =0;
    
                virtual double resWidthOpen__BOSS(int, double) =0;
    
                virtual double resWidthStore(int, double, int) =0;
    
                virtual double resWidthStore__BOSS(int, double) =0;
    
                virtual double resOpenFrac(int, int, int) =0;
    
                virtual double resOpenFrac__BOSS(int, int) =0;
    
                virtual double resOpenFrac__BOSS(int) =0;
    
                virtual double resWidthRescaleFactor(int) =0;
    
                virtual double resWidthChan(int, double, int, int) =0;
    
                virtual double resWidthChan__BOSS(int, double, int) =0;
    
                virtual double resWidthChan__BOSS(int, double) =0;
    
                virtual bool getIsInit() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_ParticleData*) =0;
                virtual Abstract_ParticleData* pointer_copy__BOSS() =0;
    
            private:
                ParticleData* wptr;
                bool delete_wrapper;
            public:
                ParticleData* get_wptr() { return wptr; }
                void set_wptr(ParticleData* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_ParticleData()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_ParticleData(const Abstract_ParticleData&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_ParticleData& operator=(const Abstract_ParticleData&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                ParticleData* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                ParticleData& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_ParticleData() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ParticleData_Pythia_8_312_h__ */
