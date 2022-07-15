#ifndef __wrapper_SusyLesHouches_def_Pythia_8_212_h__
#define __wrapper_SusyLesHouches_def_Pythia_8_212_h__

#include <string>
#include <istream>
#include <map>
#include <vector>
#include "SLHAea/slhaea.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline int SusyLesHouches::readFile(::std::basic_string<char> slhaFileIn, int verboseIn, bool useDecayIn)
        {
            return get_BEptr()->readFile(slhaFileIn, verboseIn, useDecayIn);
        }
        
        inline int SusyLesHouches::readFile(::std::basic_string<char> slhaFileIn, int verboseIn)
        {
            return get_BEptr()->readFile__BOSS(slhaFileIn, verboseIn);
        }
        
        inline int SusyLesHouches::readFile(::std::basic_string<char> slhaFileIn)
        {
            return get_BEptr()->readFile__BOSS(slhaFileIn);
        }
        
        inline int SusyLesHouches::readFile()
        {
            return get_BEptr()->readFile__BOSS();
        }
        
        inline int SusyLesHouches::readFile(::std::basic_istream<char>& arg_1, int verboseIn, bool useDecayIn)
        {
            return get_BEptr()->readFile(arg_1, verboseIn, useDecayIn);
        }
        
        inline int SusyLesHouches::readFile(::std::basic_istream<char>& arg_1, int verboseIn)
        {
            return get_BEptr()->readFile__BOSS(arg_1, verboseIn);
        }
        
        inline int SusyLesHouches::readFile(::std::basic_istream<char>& arg_1)
        {
            return get_BEptr()->readFile__BOSS(arg_1);
        }
        
        inline void SusyLesHouches::setSLHAea(const ::SLHAea::Coll* inputSLHAea)
        {
            get_BEptr()->setSLHAea(inputSLHAea);
        }
        
        inline void SusyLesHouches::printHeader()
        {
            get_BEptr()->printHeader();
        }
        
        inline void SusyLesHouches::printFooter()
        {
            get_BEptr()->printFooter();
        }
        
        inline void SusyLesHouches::printSpectrum(int ifail)
        {
            get_BEptr()->printSpectrum(ifail);
        }
        
        inline void SusyLesHouches::printSpectrum()
        {
            get_BEptr()->printSpectrum__BOSS();
        }
        
        inline int SusyLesHouches::checkSpectrum()
        {
            return get_BEptr()->checkSpectrum();
        }
        
        inline int SusyLesHouches::verbose()
        {
            return get_BEptr()->verbose();
        }
        
        inline void SusyLesHouches::verbose(int verboseIn)
        {
            get_BEptr()->verbose(verboseIn);
        }
        
        inline void SusyLesHouches::message(int arg_1, ::std::basic_string<char> arg_2, ::std::basic_string<char> arg_3, int line)
        {
            get_BEptr()->message(arg_1, arg_2, arg_3, line);
        }
        
        inline void SusyLesHouches::message(int arg_1, ::std::basic_string<char> arg_2, ::std::basic_string<char> arg_3)
        {
            get_BEptr()->message__BOSS(arg_1, arg_2, arg_3);
        }
        
        inline void SusyLesHouches::toLower(::std::basic_string<char>& name)
        {
            get_BEptr()->toLower(name);
        }
        
        
        // Wrappers for original constructors: 
        inline SusyLesHouches::SusyLesHouches(int verboseIn) :
            WrapperBase(__factory0(verboseIn)),
            slhaFile( get_BEptr()->slhaFile_ref__BOSS()),
            decayIndices( get_BEptr()->decayIndices_ref__BOSS()),
            qnumbersName( get_BEptr()->qnumbersName_ref__BOSS()),
            qnumbersAntiName( get_BEptr()->qnumbersAntiName_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline SusyLesHouches::SusyLesHouches() :
            WrapperBase(__factory1()),
            slhaFile( get_BEptr()->slhaFile_ref__BOSS()),
            decayIndices( get_BEptr()->decayIndices_ref__BOSS()),
            qnumbersName( get_BEptr()->qnumbersName_ref__BOSS()),
            qnumbersAntiName( get_BEptr()->qnumbersAntiName_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline SusyLesHouches::SusyLesHouches(::std::basic_string<char> filename, int verboseIn) :
            WrapperBase(__factory2(filename, verboseIn)),
            slhaFile( get_BEptr()->slhaFile_ref__BOSS()),
            decayIndices( get_BEptr()->decayIndices_ref__BOSS()),
            qnumbersName( get_BEptr()->qnumbersName_ref__BOSS()),
            qnumbersAntiName( get_BEptr()->qnumbersAntiName_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline SusyLesHouches::SusyLesHouches(::std::basic_string<char> filename) :
            WrapperBase(__factory3(filename)),
            slhaFile( get_BEptr()->slhaFile_ref__BOSS()),
            decayIndices( get_BEptr()->decayIndices_ref__BOSS()),
            qnumbersName( get_BEptr()->qnumbersName_ref__BOSS()),
            qnumbersAntiName( get_BEptr()->qnumbersAntiName_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline SusyLesHouches::SusyLesHouches(Abstract_SusyLesHouches* in) :
            WrapperBase(in),
            slhaFile( get_BEptr()->slhaFile_ref__BOSS()),
            decayIndices( get_BEptr()->decayIndices_ref__BOSS()),
            qnumbersName( get_BEptr()->qnumbersName_ref__BOSS()),
            qnumbersAntiName( get_BEptr()->qnumbersAntiName_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline SusyLesHouches::SusyLesHouches(const SusyLesHouches& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            slhaFile( get_BEptr()->slhaFile_ref__BOSS()),
            decayIndices( get_BEptr()->decayIndices_ref__BOSS()),
            qnumbersName( get_BEptr()->qnumbersName_ref__BOSS()),
            qnumbersAntiName( get_BEptr()->qnumbersAntiName_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline SusyLesHouches& SusyLesHouches::operator=(const SusyLesHouches& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline SusyLesHouches::~SusyLesHouches()
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
        inline Abstract_SusyLesHouches* Pythia8::SusyLesHouches::get_BEptr() const
        {
            return dynamic_cast<Abstract_SusyLesHouches*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SusyLesHouches_def_Pythia_8_212_h__ */
