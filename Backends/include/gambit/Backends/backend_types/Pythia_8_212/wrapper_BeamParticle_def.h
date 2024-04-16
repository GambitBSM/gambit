#ifndef __wrapper_BeamParticle_def_Pythia_8_212_h__
#define __wrapper_BeamParticle_def_Pythia_8_212_h__

#include <ostream>
#include <vector>
#include <utility>
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
        
        // Member functions: 
        inline void BeamParticle::newValenceContent()
        {
            get_BEptr()->newValenceContent();
        }
        
        inline void BeamParticle::newPzE(double pzIn, double eIn)
        {
            get_BEptr()->newPzE(pzIn, eIn);
        }
        
        inline int BeamParticle::id() const
        {
            return get_BEptr()->id();
        }
        
        inline Pythia8::Vec4 BeamParticle::p() const
        {
            return Pythia8::Vec4( const_cast<const Abstract_BeamParticle*>(get_BEptr())->p__BOSS() );
        }
        
        inline double BeamParticle::px() const
        {
            return get_BEptr()->px();
        }
        
        inline double BeamParticle::py() const
        {
            return get_BEptr()->py();
        }
        
        inline double BeamParticle::pz() const
        {
            return get_BEptr()->pz();
        }
        
        inline double BeamParticle::e() const
        {
            return get_BEptr()->e();
        }
        
        inline double BeamParticle::m() const
        {
            return get_BEptr()->m();
        }
        
        inline bool BeamParticle::isLepton() const
        {
            return get_BEptr()->isLepton();
        }
        
        inline bool BeamParticle::isUnresolved() const
        {
            return get_BEptr()->isUnresolved();
        }
        
        inline bool BeamParticle::isHadron() const
        {
            return get_BEptr()->isHadron();
        }
        
        inline bool BeamParticle::isMeson() const
        {
            return get_BEptr()->isMeson();
        }
        
        inline bool BeamParticle::isBaryon() const
        {
            return get_BEptr()->isBaryon();
        }
        
        inline double BeamParticle::xMax(int iSkip)
        {
            return get_BEptr()->xMax(iSkip);
        }
        
        inline double BeamParticle::xMax()
        {
            return get_BEptr()->xMax__BOSS();
        }
        
        inline double BeamParticle::xfHard(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfHard(idIn, x, Q2);
        }
        
        inline double BeamParticle::xf(int idIn, double x, double Q2)
        {
            return get_BEptr()->xf(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfVal(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfVal(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfSea(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfSea(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfMPI(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfMPI(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfISR(int indexMPI, int idIn, double x, double Q2)
        {
            return get_BEptr()->xfISR(indexMPI, idIn, x, Q2);
        }
        
        inline bool BeamParticle::insideBounds(double x, double Q2)
        {
            return get_BEptr()->insideBounds(x, Q2);
        }
        
        inline double BeamParticle::alphaS(double Q2)
        {
            return get_BEptr()->alphaS(Q2);
        }
        
        inline double BeamParticle::mQuarkPDF(int idIn)
        {
            return get_BEptr()->mQuarkPDF(idIn);
        }
        
        inline int BeamParticle::pickValSeaComp()
        {
            return get_BEptr()->pickValSeaComp();
        }
        
        inline void BeamParticle::initBeamKind()
        {
            get_BEptr()->initBeamKind();
        }
        
        inline int BeamParticle::size() const
        {
            return get_BEptr()->size();
        }
        
        inline int BeamParticle::sizeInit() const
        {
            return get_BEptr()->sizeInit();
        }
        
        inline void BeamParticle::clear()
        {
            get_BEptr()->clear();
        }
        
        inline int BeamParticle::append(int iPos, int idIn, double x, int companion)
        {
            return get_BEptr()->append(iPos, idIn, x, companion);
        }
        
        inline int BeamParticle::append(int iPos, int idIn, double x)
        {
            return get_BEptr()->append__BOSS(iPos, idIn, x);
        }
        
        inline void BeamParticle::list(std::ostream& os) const
        {
            get_BEptr()->list(os);
        }
        
        inline void BeamParticle::list() const
        {
            get_BEptr()->list__BOSS();
        }
        
        inline int BeamParticle::nValenceKinds() const
        {
            return get_BEptr()->nValenceKinds();
        }
        
        inline int BeamParticle::nValence(int idIn) const
        {
            return get_BEptr()->nValence(idIn);
        }
        
        inline bool BeamParticle::isUnresolvedLepton()
        {
            return get_BEptr()->isUnresolvedLepton();
        }
        
        inline bool BeamParticle::remnantFlavours(Pythia8::Event& event, bool isDIS)
        {
            return get_BEptr()->remnantFlavours__BOSS(*event.get_BEptr(), isDIS);
        }
        
        inline bool BeamParticle::remnantFlavours(Pythia8::Event& event)
        {
            return get_BEptr()->remnantFlavours__BOSS(*event.get_BEptr());
        }
        
        inline bool BeamParticle::remnantColours(Pythia8::Event& event, std::vector<int>& colFrom, std::vector<int>& colTo)
        {
            return get_BEptr()->remnantColours__BOSS(*event.get_BEptr(), colFrom, colTo);
        }
        
        inline double BeamParticle::xRemnant(int i)
        {
            return get_BEptr()->xRemnant(i);
        }
        
        inline bool BeamParticle::hasJunction() const
        {
            return get_BEptr()->hasJunction();
        }
        
        inline int BeamParticle::junctionCol(int i) const
        {
            return get_BEptr()->junctionCol(i);
        }
        
        inline void BeamParticle::junctionCol(int i, int col)
        {
            get_BEptr()->junctionCol(i, col);
        }
        
        inline bool BeamParticle::pickGluon(double mDiff)
        {
            return get_BEptr()->pickGluon(mDiff);
        }
        
        inline int BeamParticle::pickValence()
        {
            return get_BEptr()->pickValence();
        }
        
        inline int BeamParticle::pickRemnant() const
        {
            return get_BEptr()->pickRemnant();
        }
        
        inline double BeamParticle::zShare(double mDiff, double m1, double m2)
        {
            return get_BEptr()->zShare(mDiff, m1, m2);
        }
        
        inline double BeamParticle::pxShare() const
        {
            return get_BEptr()->pxShare();
        }
        
        inline double BeamParticle::pyShare() const
        {
            return get_BEptr()->pyShare();
        }
        
        inline bool BeamParticle::remnantFlavoursNew(Pythia8::Event& event)
        {
            return get_BEptr()->remnantFlavoursNew__BOSS(*event.get_BEptr());
        }
        
        inline void BeamParticle::findColSetup(Pythia8::Event& event)
        {
            get_BEptr()->findColSetup__BOSS(*event.get_BEptr());
        }
        
        inline void BeamParticle::setInitialCol(Pythia8::Event& event)
        {
            get_BEptr()->setInitialCol__BOSS(*event.get_BEptr());
        }
        
        inline void BeamParticle::updateCol(std::vector<std::pair<int, int>> colourChanges)
        {
            get_BEptr()->updateCol(colourChanges);
        }
        
        inline ::std::vector<std::pair<int, int>> BeamParticle::getColUpdates()
        {
            return get_BEptr()->getColUpdates();
        }
        
        
        // Wrappers for original constructors: 
        inline BeamParticle::BeamParticle() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline BeamParticle::BeamParticle(Abstract_BeamParticle* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline BeamParticle::BeamParticle(const BeamParticle& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline BeamParticle& BeamParticle::operator=(const BeamParticle& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline BeamParticle::~BeamParticle()
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
        inline Abstract_BeamParticle* Pythia8::BeamParticle::get_BEptr() const
        {
            return dynamic_cast<Abstract_BeamParticle*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_BeamParticle_def_Pythia_8_212_h__ */
