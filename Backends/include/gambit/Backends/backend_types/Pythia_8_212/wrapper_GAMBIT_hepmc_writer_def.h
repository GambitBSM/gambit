#ifndef __wrapper_GAMBIT_hepmc_writer_def_Pythia_8_212_h__
#define __wrapper_GAMBIT_hepmc_writer_def_Pythia_8_212_h__

#include <string>
#include "wrapper_Pythia_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void GAMBIT_hepmc_writer::init(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > filename_in, bool HepMC2, bool HepMC3)
        {
            get_BEptr()->init(filename_in, HepMC2, HepMC3);
        }
        
        inline void GAMBIT_hepmc_writer::write_event_HepMC3(Pythia8::Pythia* pythia)
        {
            get_BEptr()->write_event_HepMC3__BOSS((*pythia).get_BEptr());
        }
        
        inline void GAMBIT_hepmc_writer::write_event_HepMC2(Pythia8::Pythia* pythia)
        {
            get_BEptr()->write_event_HepMC2__BOSS((*pythia).get_BEptr());
        }
        
        
        // Wrappers for original constructors: 
        inline GAMBIT_hepmc_writer::GAMBIT_hepmc_writer() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline GAMBIT_hepmc_writer::GAMBIT_hepmc_writer(Abstract_GAMBIT_hepmc_writer* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline GAMBIT_hepmc_writer::GAMBIT_hepmc_writer(const GAMBIT_hepmc_writer& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline GAMBIT_hepmc_writer& GAMBIT_hepmc_writer::operator=(const GAMBIT_hepmc_writer& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline GAMBIT_hepmc_writer::~GAMBIT_hepmc_writer()
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
        inline Abstract_GAMBIT_hepmc_writer* Pythia8::GAMBIT_hepmc_writer::get_BEptr() const
        {
            return dynamic_cast<Abstract_GAMBIT_hepmc_writer*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_GAMBIT_hepmc_writer_def_Pythia_8_212_h__ */
