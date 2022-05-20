#ifndef __abstract_BeamParticle_Pythia_8_212_h__
#define __abstract_BeamParticle_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <ostream>
#include <vector>
#include <utility>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_BeamParticle : public virtual AbstractBase
        {
            public:
    
                virtual void newValenceContent() =0;
    
                virtual void newPzE(double, double) =0;
    
                virtual int id() const =0;
    
                virtual Pythia8::Abstract_Vec4* p__BOSS() const =0;
    
                virtual double px() const =0;
    
                virtual double py() const =0;
    
                virtual double pz() const =0;
    
                virtual double e() const =0;
    
                virtual double m() const =0;
    
                virtual bool isLepton() const =0;
    
                virtual bool isUnresolved() const =0;
    
                virtual bool isHadron() const =0;
    
                virtual bool isMeson() const =0;
    
                virtual bool isBaryon() const =0;
    
                virtual double xMax(int) =0;
    
                virtual double xMax__BOSS() =0;
    
                virtual double xfHard(int, double, double) =0;
    
                virtual double xf(int, double, double) =0;
    
                virtual double xfVal(int, double, double) =0;
    
                virtual double xfSea(int, double, double) =0;
    
                virtual double xfMPI(int, double, double) =0;
    
                virtual double xfISR(int, int, double, double) =0;
    
                virtual bool insideBounds(double, double) =0;
    
                virtual double alphaS(double) =0;
    
                virtual double mQuarkPDF(int) =0;
    
                virtual int pickValSeaComp() =0;
    
                virtual void initBeamKind() =0;
    
                virtual int size() const =0;
    
                virtual int sizeInit() const =0;
    
                virtual void clear() =0;
    
                virtual int append(int, int, double, int) =0;
    
                virtual int append__BOSS(int, int, double) =0;
    
                virtual void list(::std::basic_ostream<char, std::char_traits<char> >&) const =0;
    
                virtual void list__BOSS() const =0;
    
                virtual int nValenceKinds() const =0;
    
                virtual int nValence(int) const =0;
    
                virtual bool isUnresolvedLepton() =0;
    
                virtual bool remnantFlavours__BOSS(Pythia8::Abstract_Event&, bool) =0;
    
                virtual bool remnantFlavours__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual bool remnantColours__BOSS(Pythia8::Abstract_Event&, ::std::vector<int, std::allocator<int> >&, ::std::vector<int, std::allocator<int> >&) =0;
    
                virtual double xRemnant(int) =0;
    
                virtual bool hasJunction() const =0;
    
                virtual int junctionCol(int) const =0;
    
                virtual void junctionCol(int, int) =0;
    
                virtual bool pickGluon(double) =0;
    
                virtual int pickValence() =0;
    
                virtual int pickRemnant() const =0;
    
                virtual double zShare(double, double, double) =0;
    
                virtual double pxShare() const =0;
    
                virtual double pyShare() const =0;
    
                virtual bool remnantFlavoursNew__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual void findColSetup__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual void setInitialCol__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual void updateCol(::std::vector<std::pair<int, int>, std::allocator<std::pair<int, int> > >) =0;
    
                virtual ::std::vector<std::pair<int, int>, std::allocator<std::pair<int, int> > > getColUpdates() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_BeamParticle*) =0;
                virtual Abstract_BeamParticle* pointer_copy__BOSS() =0;
    
            private:
                BeamParticle* wptr;
                bool delete_wrapper;
            public:
                BeamParticle* get_wptr() { return wptr; }
                void set_wptr(BeamParticle* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_BeamParticle()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_BeamParticle(const Abstract_BeamParticle&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_BeamParticle& operator=(const Abstract_BeamParticle&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                BeamParticle* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                BeamParticle& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_BeamParticle() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_BeamParticle_Pythia_8_212_h__ */
