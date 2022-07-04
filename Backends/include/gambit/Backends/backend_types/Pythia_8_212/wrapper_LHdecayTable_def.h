#ifndef __wrapper_LHdecayTable_def_Pythia_8_212_h__
#define __wrapper_LHdecayTable_def_Pythia_8_212_h__

#include <vector>
#include <string>
#include "wrapper_LHdecayChannel_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline int LHdecayTable::getId()
        {
            return get_BEptr()->getId();
        }
        
        inline double LHdecayTable::getWidth()
        {
            return get_BEptr()->getWidth();
        }
        
        inline void LHdecayTable::setId(int idIn)
        {
            get_BEptr()->setId(idIn);
        }
        
        inline void LHdecayTable::setWidth(double widthIn)
        {
            get_BEptr()->setWidth(widthIn);
        }
        
        inline void LHdecayTable::reset(double widthIn)
        {
            get_BEptr()->reset(widthIn);
        }
        
        inline void LHdecayTable::reset()
        {
            get_BEptr()->reset__BOSS();
        }
        
        inline void LHdecayTable::addChannel(Pythia8::LHdecayChannel channelIn)
        {
            get_BEptr()->addChannel__BOSS(*channelIn.get_BEptr());
        }
        
        inline void LHdecayTable::addChannel(double bratIn, int nDaIn, ::std::vector<int> idDaIn, ::std::basic_string<char> cIn)
        {
            get_BEptr()->addChannel(bratIn, nDaIn, idDaIn, cIn);
        }
        
        inline void LHdecayTable::addChannel(double bratIn, int nDaIn, ::std::vector<int> idDaIn)
        {
            get_BEptr()->addChannel__BOSS(bratIn, nDaIn, idDaIn);
        }
        
        inline int LHdecayTable::size()
        {
            return get_BEptr()->size();
        }
        
        inline double LHdecayTable::getBrat(int iChannel)
        {
            return get_BEptr()->getBrat(iChannel);
        }
        
        inline ::std::vector<int> LHdecayTable::getIdDa(int iChannel)
        {
            return get_BEptr()->getIdDa(iChannel);
        }
        
        inline Pythia8::LHdecayChannel LHdecayTable::getChannel(int iChannel)
        {
            return Pythia8::LHdecayChannel( get_BEptr()->getChannel__BOSS(iChannel) );
        }
        
        
        // Wrappers for original constructors: 
        inline LHdecayTable::LHdecayTable() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline LHdecayTable::LHdecayTable(int idIn) :
            WrapperBase(__factory1(idIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline LHdecayTable::LHdecayTable(int idIn, double widthIn) :
            WrapperBase(__factory2(idIn, widthIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline LHdecayTable::LHdecayTable(Abstract_LHdecayTable* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline LHdecayTable::LHdecayTable(const LHdecayTable& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline LHdecayTable& LHdecayTable::operator=(const LHdecayTable& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline LHdecayTable::~LHdecayTable()
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
        inline Abstract_LHdecayTable* Pythia8::LHdecayTable::get_BEptr() const
        {
            return dynamic_cast<Abstract_LHdecayTable*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_LHdecayTable_def_Pythia_8_212_h__ */
