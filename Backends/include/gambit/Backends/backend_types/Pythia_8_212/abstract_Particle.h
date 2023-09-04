#ifndef __abstract_Particle_Pythia_8_212_h__
#define __abstract_Particle_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_ParticleDataEntry_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Particle : public virtual AbstractBase
        {
            public:
    
                virtual Pythia8::Abstract_Particle& operator_equal__BOSS(const Pythia8::Abstract_Particle&) =0;
    
                virtual void setEvtPtr__BOSS(Pythia8::Abstract_Event*) =0;
    
                virtual void setPDEPtr__BOSS(Pythia8::Abstract_ParticleDataEntry*) =0;
    
                virtual void setPDEPtr__BOSS() =0;
    
                virtual void id(int) =0;
    
                virtual void status(int) =0;
    
                virtual void statusPos() =0;
    
                virtual void statusNeg() =0;
    
                virtual void statusCode(int) =0;
    
                virtual void mother1(int) =0;
    
                virtual void mother2(int) =0;
    
                virtual void mothers(int, int) =0;
    
                virtual void mothers__BOSS(int) =0;
    
                virtual void mothers__BOSS() =0;
    
                virtual void daughter1(int) =0;
    
                virtual void daughter2(int) =0;
    
                virtual void daughters(int, int) =0;
    
                virtual void daughters__BOSS(int) =0;
    
                virtual void daughters__BOSS() =0;
    
                virtual void col(int) =0;
    
                virtual void acol(int) =0;
    
                virtual void cols(int, int) =0;
    
                virtual void cols__BOSS(int) =0;
    
                virtual void cols__BOSS() =0;
    
                virtual void p__BOSS(Pythia8::Abstract_Vec4&) =0;
    
                virtual void p(double, double, double, double) =0;
    
                virtual void px(double) =0;
    
                virtual void py(double) =0;
    
                virtual void pz(double) =0;
    
                virtual void e(double) =0;
    
                virtual void m(double) =0;
    
                virtual void scale(double) =0;
    
                virtual void pol(double) =0;
    
                virtual void vProd__BOSS(Pythia8::Abstract_Vec4&) =0;
    
                virtual void vProd(double, double, double, double) =0;
    
                virtual void xProd(double) =0;
    
                virtual void yProd(double) =0;
    
                virtual void zProd(double) =0;
    
                virtual void tProd(double) =0;
    
                virtual void tau(double) =0;
    
                virtual int id() const =0;
    
                virtual int status() const =0;
    
                virtual int mother1() const =0;
    
                virtual int mother2() const =0;
    
                virtual int daughter1() const =0;
    
                virtual int daughter2() const =0;
    
                virtual int col() const =0;
    
                virtual int acol() const =0;
    
                virtual Pythia8::Abstract_Vec4* p__BOSS() const =0;
    
                virtual double px() const =0;
    
                virtual double py() const =0;
    
                virtual double pz() const =0;
    
                virtual double e() const =0;
    
                virtual double m() const =0;
    
                virtual double scale() const =0;
    
                virtual double pol() const =0;
    
                virtual bool hasVertex() const =0;
    
                virtual Pythia8::Abstract_Vec4* vProd__BOSS() const =0;
    
                virtual double xProd() const =0;
    
                virtual double yProd() const =0;
    
                virtual double zProd() const =0;
    
                virtual double tProd() const =0;
    
                virtual double tau() const =0;
    
                virtual int idAbs() const =0;
    
                virtual int statusAbs() const =0;
    
                virtual bool isFinal() const =0;
    
                virtual bool isRescatteredIncoming() const =0;
    
                virtual double m2() const =0;
    
                virtual double mCalc() const =0;
    
                virtual double m2Calc() const =0;
    
                virtual double eCalc() const =0;
    
                virtual double pT() const =0;
    
                virtual double pT2() const =0;
    
                virtual double mT() const =0;
    
                virtual double mT2() const =0;
    
                virtual double pAbs() const =0;
    
                virtual double pAbs2() const =0;
    
                virtual double eT() const =0;
    
                virtual double eT2() const =0;
    
                virtual double theta() const =0;
    
                virtual double phi() const =0;
    
                virtual double thetaXZ() const =0;
    
                virtual double pPos() const =0;
    
                virtual double pNeg() const =0;
    
                virtual double y() const =0;
    
                virtual double eta() const =0;
    
                virtual Pythia8::Abstract_Vec4* vDec__BOSS() const =0;
    
                virtual double xDec() const =0;
    
                virtual double yDec() const =0;
    
                virtual double zDec() const =0;
    
                virtual double tDec() const =0;
    
                virtual int index() const =0;
    
                virtual int iTopCopy() const =0;
    
                virtual int iBotCopy() const =0;
    
                virtual int iTopCopyId(bool) const =0;
    
                virtual int iTopCopyId__BOSS() const =0;
    
                virtual int iBotCopyId(bool) const =0;
    
                virtual int iBotCopyId__BOSS() const =0;
    
                virtual ::std::vector<int> motherList() const =0;
    
                virtual ::std::vector<int> daughterList() const =0;
    
                virtual ::std::vector<int> sisterList(bool) const =0;
    
                virtual ::std::vector<int> sisterList__BOSS() const =0;
    
                virtual bool isAncestor(int) const =0;
    
                virtual int statusHepMC() const =0;
    
                virtual bool isFinalPartonLevel() const =0;
    
                virtual bool undoDecay() =0;
    
                virtual ::std::string name() const =0;
    
                virtual ::std::string nameWithStatus(int) const =0;
    
                virtual ::std::string nameWithStatus__BOSS() const =0;
    
                virtual int spinType() const =0;
    
                virtual int chargeType() const =0;
    
                virtual double charge() const =0;
    
                virtual bool isCharged() const =0;
    
                virtual bool isNeutral() const =0;
    
                virtual int colType() const =0;
    
                virtual double m0() const =0;
    
                virtual double mWidth() const =0;
    
                virtual double mMin() const =0;
    
                virtual double mMax() const =0;
    
                virtual double mSel() const =0;
    
                virtual double constituentMass() const =0;
    
                virtual double tau0() const =0;
    
                virtual bool mayDecay() const =0;
    
                virtual bool canDecay() const =0;
    
                virtual bool doExternalDecay() const =0;
    
                virtual bool isResonance() const =0;
    
                virtual bool isVisible() const =0;
    
                virtual bool isLepton() const =0;
    
                virtual bool isQuark() const =0;
    
                virtual bool isGluon() const =0;
    
                virtual bool isDiquark() const =0;
    
                virtual bool isParton() const =0;
    
                virtual bool isHadron() const =0;
    
                virtual Pythia8::Abstract_ParticleDataEntry& particleDataEntry__BOSS() const =0;
    
                virtual void rescale3(double) =0;
    
                virtual void rescale4(double) =0;
    
                virtual void rescale5(double) =0;
    
                virtual void rot(double, double) =0;
    
                virtual void bst(double, double, double) =0;
    
                virtual void bst(double, double, double, double) =0;
    
                virtual void bst__BOSS(const Pythia8::Abstract_Vec4&) =0;
    
                virtual void bst__BOSS(const Pythia8::Abstract_Vec4&, double) =0;
    
                virtual void bstback__BOSS(const Pythia8::Abstract_Vec4&) =0;
    
                virtual void bstback__BOSS(const Pythia8::Abstract_Vec4&, double) =0;
    
                virtual void offsetHistory(int, int, int, int) =0;
    
                virtual void offsetCol(int) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Particle*) =0;
                virtual Abstract_Particle* pointer_copy__BOSS() =0;
    
            private:
                Particle* wptr;
                bool delete_wrapper;
            public:
                Particle* get_wptr() { return wptr; }
                void set_wptr(Particle* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Particle()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Particle(const Abstract_Particle&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Particle& operator=(const Abstract_Particle&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Particle* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Particle& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Particle() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Particle_Pythia_8_212_h__ */
