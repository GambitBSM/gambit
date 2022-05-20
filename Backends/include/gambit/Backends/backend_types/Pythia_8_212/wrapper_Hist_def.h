#ifndef __wrapper_Hist_def_Pythia_8_212_h__
#define __wrapper_Hist_def_Pythia_8_212_h__

#include <string>
#include <ostream>
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void Hist::book(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn, double xMinIn, double xMaxIn)
        {
            get_BEptr()->book(titleIn, nBinIn, xMinIn, xMaxIn);
        }
        
        inline void Hist::book(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn, double xMinIn)
        {
            get_BEptr()->book__BOSS(titleIn, nBinIn, xMinIn);
        }
        
        inline void Hist::book(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn)
        {
            get_BEptr()->book__BOSS(titleIn, nBinIn);
        }
        
        inline void Hist::book(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn)
        {
            get_BEptr()->book__BOSS(titleIn);
        }
        
        inline void Hist::book()
        {
            get_BEptr()->book__BOSS();
        }
        
        inline void Hist::name(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn)
        {
            get_BEptr()->name(titleIn);
        }
        
        inline void Hist::name()
        {
            get_BEptr()->name__BOSS();
        }
        
        inline void Hist::null()
        {
            get_BEptr()->null();
        }
        
        inline void Hist::fill(double x, double w)
        {
            get_BEptr()->fill(x, w);
        }
        
        inline void Hist::fill(double x)
        {
            get_BEptr()->fill__BOSS(x);
        }
        
        inline void Hist::table(::std::basic_ostream<char, std::char_traits<char> >& os, bool printOverUnder, bool xMidBin) const
        {
            get_BEptr()->table(os, printOverUnder, xMidBin);
        }
        
        inline void Hist::table(::std::basic_ostream<char, std::char_traits<char> >& os, bool printOverUnder) const
        {
            get_BEptr()->table__BOSS(os, printOverUnder);
        }
        
        inline void Hist::table(::std::basic_ostream<char, std::char_traits<char> >& os) const
        {
            get_BEptr()->table__BOSS(os);
        }
        
        inline void Hist::table() const
        {
            get_BEptr()->table__BOSS();
        }
        
        inline void Hist::table(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > fileName, bool printOverUnder, bool xMidBin) const
        {
            get_BEptr()->table(fileName, printOverUnder, xMidBin);
        }
        
        inline void Hist::table(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > fileName, bool printOverUnder) const
        {
            get_BEptr()->table__BOSS(fileName, printOverUnder);
        }
        
        inline void Hist::table(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > fileName) const
        {
            get_BEptr()->table__BOSS(fileName);
        }
        
        inline double Hist::getBinContent(int iBin) const
        {
            return get_BEptr()->getBinContent(iBin);
        }
        
        inline int Hist::getEntries() const
        {
            return get_BEptr()->getEntries();
        }
        
        inline bool Hist::sameSize(const Pythia8::Hist& h) const
        {
            return get_BEptr()->sameSize__BOSS(*h.get_BEptr());
        }
        
        inline void Hist::takeLog(bool tenLog)
        {
            get_BEptr()->takeLog(tenLog);
        }
        
        inline void Hist::takeLog()
        {
            get_BEptr()->takeLog__BOSS();
        }
        
        inline void Hist::takeSqrt()
        {
            get_BEptr()->takeSqrt();
        }
        
        inline Pythia8::Hist& Hist::operator+=(const Pythia8::Hist& h)
        {
            return get_BEptr()->operator_plus_equal__BOSS(*h.get_BEptr()).get_init_wref();
        }
        
        inline Pythia8::Hist& Hist::operator-=(const Pythia8::Hist& h)
        {
            return get_BEptr()->operator_minus_equal__BOSS(*h.get_BEptr()).get_init_wref();
        }
        
        inline Pythia8::Hist& Hist::operator*=(const Pythia8::Hist& h)
        {
            return get_BEptr()->operator_asterix_equal__BOSS(*h.get_BEptr()).get_init_wref();
        }
        
        inline Pythia8::Hist& Hist::operator/=(const Pythia8::Hist& h)
        {
            return get_BEptr()->operator_slash_equal__BOSS(*h.get_BEptr()).get_init_wref();
        }
        
        inline Pythia8::Hist& Hist::operator+=(double f)
        {
            return get_BEptr()->operator_plus_equal__BOSS(f).get_init_wref();
        }
        
        inline Pythia8::Hist& Hist::operator-=(double f)
        {
            return get_BEptr()->operator_minus_equal__BOSS(f).get_init_wref();
        }
        
        inline Pythia8::Hist& Hist::operator*=(double f)
        {
            return get_BEptr()->operator_asterix_equal__BOSS(f).get_init_wref();
        }
        
        inline Pythia8::Hist& Hist::operator/=(double f)
        {
            return get_BEptr()->operator_slash_equal__BOSS(f).get_init_wref();
        }
        
        
        // Wrappers for original constructors: 
        inline Hist::Hist() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn, double xMinIn, double xMaxIn) :
            WrapperBase(__factory1(titleIn, nBinIn, xMinIn, xMaxIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn, double xMinIn) :
            WrapperBase(__factory2(titleIn, nBinIn, xMinIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn) :
            WrapperBase(__factory3(titleIn, nBinIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn) :
            WrapperBase(__factory4(titleIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, const Pythia8::Hist& h) :
            WrapperBase(__factory5(titleIn, h))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Hist::Hist(Abstract_Hist* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Hist::Hist(const Hist& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Hist& Hist::operator=(const Hist& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Hist::~Hist()
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
        inline Abstract_Hist* Pythia8::Hist::get_BEptr() const
        {
            return dynamic_cast<Abstract_Hist*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Hist_def_Pythia_8_212_h__ */
