#ifndef __wrapper_Rndm_def_Pythia_8_212_h__
#define __wrapper_Rndm_def_Pythia_8_212_h__

#include <utility>
#include <vector>
#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void Rndm::init(int seedIn)
        {
            get_BEptr()->init(seedIn);
        }
        
        inline void Rndm::init()
        {
            get_BEptr()->init__BOSS();
        }
        
        inline double Rndm::flat()
        {
            return get_BEptr()->flat();
        }
        
        inline double Rndm::exp()
        {
            return get_BEptr()->exp();
        }
        
        inline double Rndm::xexp()
        {
            return get_BEptr()->xexp();
        }
        
        inline double Rndm::gauss()
        {
            return get_BEptr()->gauss();
        }
        
        inline ::std::pair<double, double> Rndm::gauss2()
        {
            return get_BEptr()->gauss2();
        }
        
        inline int Rndm::pick(const std::vector<double>& prob)
        {
            return get_BEptr()->pick(prob);
        }
        
        inline bool Rndm::dumpState(std::string fileName)
        {
            return get_BEptr()->dumpState(fileName);
        }
        
        inline bool Rndm::readState(std::string fileName)
        {
            return get_BEptr()->readState(fileName);
        }
        
        
        // Wrappers for original constructors: 
        inline Rndm::Rndm() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Rndm::Rndm(int seedIn) :
            WrapperBase(__factory1(seedIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Rndm::Rndm(Abstract_Rndm* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Rndm::Rndm(const Rndm& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Rndm& Rndm::operator=(const Rndm& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Rndm::~Rndm()
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
        inline Abstract_Rndm* Pythia8::Rndm::get_BEptr() const
        {
            return dynamic_cast<Abstract_Rndm*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Rndm_def_Pythia_8_212_h__ */
