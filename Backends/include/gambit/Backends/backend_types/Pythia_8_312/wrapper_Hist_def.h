#ifndef __wrapper_Hist_def_Pythia_8_312_h__
#define __wrapper_Hist_def_Pythia_8_312_h__

#include <string>
#include <functional>
#include <ostream>
#include <istream>
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline Pythia8::Hist Hist::plotFunc(std::function<double (double)> f, std::string titleIn, int nBinIn, double xMinIn, double xMaxIn, bool logXIn)
        {
            return Pythia8::Hist( get_BEptr()->plotFunc__BOSS(f, titleIn, nBinIn, xMinIn, xMaxIn, logXIn) );
        }
        
        inline Pythia8::Hist Hist::plotFunc(std::function<double (double)> f, std::string titleIn, int nBinIn, double xMinIn, double xMaxIn)
        {
            return Pythia8::Hist( get_BEptr()->plotFunc__BOSS(f, titleIn, nBinIn, xMinIn, xMaxIn) );
        }
        
        inline void Hist::book(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn, bool logXIn, bool doStatsIn)
        {
            get_BEptr()->book(titleIn, nBinIn, xMinIn, xMaxIn, logXIn, doStatsIn);
        }
        
        inline void Hist::book(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn, bool logXIn)
        {
            get_BEptr()->book__BOSS(titleIn, nBinIn, xMinIn, xMaxIn, logXIn);
        }
        
        inline void Hist::book(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn)
        {
            get_BEptr()->book__BOSS(titleIn, nBinIn, xMinIn, xMaxIn);
        }
        
        inline void Hist::book(std::string titleIn, int nBinIn, double xMinIn)
        {
            get_BEptr()->book__BOSS(titleIn, nBinIn, xMinIn);
        }
        
        inline void Hist::book(std::string titleIn, int nBinIn)
        {
            get_BEptr()->book__BOSS(titleIn, nBinIn);
        }
        
        inline void Hist::book(std::string titleIn)
        {
            get_BEptr()->book__BOSS(titleIn);
        }
        
        inline void Hist::book()
        {
            get_BEptr()->book__BOSS();
        }
        
        inline void Hist::title(std::string titleIn)
        {
            get_BEptr()->title(titleIn);
        }
        
        inline void Hist::title()
        {
            get_BEptr()->title__BOSS();
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
        
        inline void Hist::table(std::ostream& os, bool printOverUnder, bool xMidBin, bool printError) const
        {
            get_BEptr()->table(os, printOverUnder, xMidBin, printError);
        }
        
        inline void Hist::table(std::ostream& os, bool printOverUnder, bool xMidBin) const
        {
            get_BEptr()->table__BOSS(os, printOverUnder, xMidBin);
        }
        
        inline void Hist::table(std::ostream& os, bool printOverUnder) const
        {
            get_BEptr()->table__BOSS(os, printOverUnder);
        }
        
        inline void Hist::table(std::ostream& os) const
        {
            get_BEptr()->table__BOSS(os);
        }
        
        inline void Hist::table() const
        {
            get_BEptr()->table__BOSS();
        }
        
        inline void Hist::table(std::string fileName, bool printOverUnder, bool xMidBin, bool printError) const
        {
            get_BEptr()->table(fileName, printOverUnder, xMidBin, printError);
        }
        
        inline void Hist::table(std::string fileName, bool printOverUnder, bool xMidBin) const
        {
            get_BEptr()->table__BOSS(fileName, printOverUnder, xMidBin);
        }
        
        inline void Hist::table(std::string fileName, bool printOverUnder) const
        {
            get_BEptr()->table__BOSS(fileName, printOverUnder);
        }
        
        inline void Hist::table(std::string fileName) const
        {
            get_BEptr()->table__BOSS(fileName);
        }
        
        inline void Hist::rivetTable(std::ostream& os, bool printError) const
        {
            get_BEptr()->rivetTable(os, printError);
        }
        
        inline void Hist::rivetTable(std::ostream& os) const
        {
            get_BEptr()->rivetTable__BOSS(os);
        }
        
        inline void Hist::rivetTable() const
        {
            get_BEptr()->rivetTable__BOSS();
        }
        
        inline void Hist::rivetTable(std::string fileName, bool printError) const
        {
            get_BEptr()->rivetTable(fileName, printError);
        }
        
        inline void Hist::rivetTable(std::string fileName) const
        {
            get_BEptr()->rivetTable__BOSS(fileName);
        }
        
        inline void Hist::pyplotTable(std::ostream& os, bool isHist, bool printError) const
        {
            get_BEptr()->pyplotTable(os, isHist, printError);
        }
        
        inline void Hist::pyplotTable(std::ostream& os, bool isHist) const
        {
            get_BEptr()->pyplotTable__BOSS(os, isHist);
        }
        
        inline void Hist::pyplotTable(std::ostream& os) const
        {
            get_BEptr()->pyplotTable__BOSS(os);
        }
        
        inline void Hist::pyplotTable() const
        {
            get_BEptr()->pyplotTable__BOSS();
        }
        
        inline void Hist::pyplotTable(std::string fileName, bool isHist, bool printError) const
        {
            get_BEptr()->pyplotTable(fileName, isHist, printError);
        }
        
        inline void Hist::pyplotTable(std::string fileName, bool isHist) const
        {
            get_BEptr()->pyplotTable__BOSS(fileName, isHist);
        }
        
        inline void Hist::pyplotTable(std::string fileName) const
        {
            get_BEptr()->pyplotTable__BOSS(fileName);
        }
        
        inline void Hist::fillTable(std::istream& is)
        {
            get_BEptr()->fillTable(is);
        }
        
        inline void Hist::fillTable()
        {
            get_BEptr()->fillTable__BOSS();
        }
        
        inline void Hist::fillTable(std::string fileName)
        {
            get_BEptr()->fillTable(fileName);
        }
        
        inline ::std::string Hist::getTitle() const
        {
            return get_BEptr()->getTitle();
        }
        
        inline int Hist::getBinNumber() const
        {
            return get_BEptr()->getBinNumber();
        }
        
        inline int Hist::getNonFinite() const
        {
            return get_BEptr()->getNonFinite();
        }
        
        inline bool Hist::getLinX() const
        {
            return get_BEptr()->getLinX();
        }
        
        inline double Hist::getXMin() const
        {
            return get_BEptr()->getXMin();
        }
        
        inline double Hist::getXMax() const
        {
            return get_BEptr()->getXMax();
        }
        
        inline double Hist::getYMin() const
        {
            return get_BEptr()->getYMin();
        }
        
        inline double Hist::getYMax() const
        {
            return get_BEptr()->getYMax();
        }
        
        inline double Hist::getYAbsMin() const
        {
            return get_BEptr()->getYAbsMin();
        }
        
        inline double Hist::getXMean(bool unbinned) const
        {
            return get_BEptr()->getXMean(unbinned);
        }
        
        inline double Hist::getXMean() const
        {
            return get_BEptr()->getXMean__BOSS();
        }
        
        inline double Hist::getXMeanErr(bool unbinned) const
        {
            return get_BEptr()->getXMeanErr(unbinned);
        }
        
        inline double Hist::getXMeanErr() const
        {
            return get_BEptr()->getXMeanErr__BOSS();
        }
        
        inline double Hist::getXMedian(bool includeOverUnder) const
        {
            return get_BEptr()->getXMedian(includeOverUnder);
        }
        
        inline double Hist::getXMedian() const
        {
            return get_BEptr()->getXMedian__BOSS();
        }
        
        inline double Hist::getXMedianErr(bool unbinned) const
        {
            return get_BEptr()->getXMedianErr(unbinned);
        }
        
        inline double Hist::getXMedianErr() const
        {
            return get_BEptr()->getXMedianErr__BOSS();
        }
        
        inline double Hist::getYMean() const
        {
            return get_BEptr()->getYMean();
        }
        
        inline double Hist::getXRMN(int n, bool unbinned) const
        {
            return get_BEptr()->getXRMN(n, unbinned);
        }
        
        inline double Hist::getXRMN(int n) const
        {
            return get_BEptr()->getXRMN__BOSS(n);
        }
        
        inline double Hist::getXRMN() const
        {
            return get_BEptr()->getXRMN__BOSS();
        }
        
        inline double Hist::getXRMS(bool unbinned) const
        {
            return get_BEptr()->getXRMS(unbinned);
        }
        
        inline double Hist::getXRMS() const
        {
            return get_BEptr()->getXRMS__BOSS();
        }
        
        inline double Hist::getXRMNErr(int n, bool unbinned) const
        {
            return get_BEptr()->getXRMNErr(n, unbinned);
        }
        
        inline double Hist::getXRMNErr(int n) const
        {
            return get_BEptr()->getXRMNErr__BOSS(n);
        }
        
        inline double Hist::getXRMNErr() const
        {
            return get_BEptr()->getXRMNErr__BOSS();
        }
        
        inline double Hist::getXRMSErr(bool unbinned) const
        {
            return get_BEptr()->getXRMSErr(unbinned);
        }
        
        inline double Hist::getXRMSErr() const
        {
            return get_BEptr()->getXRMSErr__BOSS();
        }
        
        inline double Hist::getBinContent(int iBin) const
        {
            return get_BEptr()->getBinContent(iBin);
        }
        
        inline double Hist::getBinEdge(int iBin) const
        {
            return get_BEptr()->getBinEdge(iBin);
        }
        
        inline double Hist::getBinWidth(int iBin) const
        {
            return get_BEptr()->getBinWidth(iBin);
        }
        
        inline double Hist::getBinWidth() const
        {
            return get_BEptr()->getBinWidth__BOSS();
        }
        
        inline ::std::vector<double> Hist::getBinContents() const
        {
            return get_BEptr()->getBinContents();
        }
        
        inline ::std::vector<double> Hist::getBinEdges() const
        {
            return get_BEptr()->getBinEdges();
        }
        
        inline int Hist::getEntries(bool alsoNonFinite) const
        {
            return get_BEptr()->getEntries(alsoNonFinite);
        }
        
        inline int Hist::getEntries() const
        {
            return get_BEptr()->getEntries__BOSS();
        }
        
        inline double Hist::getWeightSum(bool alsoOverUnder) const
        {
            return get_BEptr()->getWeightSum(alsoOverUnder);
        }
        
        inline double Hist::getWeightSum() const
        {
            return get_BEptr()->getWeightSum__BOSS();
        }
        
        inline double Hist::getNEffective() const
        {
            return get_BEptr()->getNEffective();
        }
        
        inline bool Hist::sameSize(const Pythia8::Hist& h) const
        {
            return get_BEptr()->sameSize__BOSS(*h.get_BEptr());
        }
        
        inline void Hist::takeFunc(std::function<double (double)> func)
        {
            get_BEptr()->takeFunc(func);
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
        
        inline void Hist::normalize(double f, bool overflow)
        {
            get_BEptr()->normalize(f, overflow);
        }
        
        inline void Hist::normalize(double f)
        {
            get_BEptr()->normalize__BOSS(f);
        }
        
        inline void Hist::normalize()
        {
            get_BEptr()->normalize__BOSS();
        }
        
        inline void Hist::normalizeIntegral(double f, bool overflow)
        {
            get_BEptr()->normalizeIntegral(f, overflow);
        }
        
        inline void Hist::normalizeIntegral(double f)
        {
            get_BEptr()->normalizeIntegral__BOSS(f);
        }
        
        inline void Hist::normalizeIntegral()
        {
            get_BEptr()->normalizeIntegral__BOSS();
        }
        
        inline void Hist::normalizeSpectrum(double wtSum)
        {
            get_BEptr()->normalizeSpectrum(wtSum);
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
        
        inline Pythia8::Hist Hist::operator+(double f) const
        {
            return Pythia8::Hist( const_cast<const Abstract_Hist*>(get_BEptr())->operator_plus__BOSS(f) );
        }
        
        inline Pythia8::Hist Hist::operator+(const Pythia8::Hist& h2) const
        {
            return Pythia8::Hist( const_cast<const Abstract_Hist*>(get_BEptr())->operator_plus__BOSS(*h2.get_BEptr()) );
        }
        
        inline Pythia8::Hist Hist::operator-(double f) const
        {
            return Pythia8::Hist( const_cast<const Abstract_Hist*>(get_BEptr())->operator_minus__BOSS(f) );
        }
        
        inline Pythia8::Hist Hist::operator-(const Pythia8::Hist& h2) const
        {
            return Pythia8::Hist( const_cast<const Abstract_Hist*>(get_BEptr())->operator_minus__BOSS(*h2.get_BEptr()) );
        }
        
        inline Pythia8::Hist Hist::operator*(double f) const
        {
            return Pythia8::Hist( const_cast<const Abstract_Hist*>(get_BEptr())->operator_asterix__BOSS(f) );
        }
        
        inline Pythia8::Hist Hist::operator*(const Pythia8::Hist& h2) const
        {
            return Pythia8::Hist( const_cast<const Abstract_Hist*>(get_BEptr())->operator_asterix__BOSS(*h2.get_BEptr()) );
        }
        
        inline Pythia8::Hist Hist::operator/(double f) const
        {
            return Pythia8::Hist( const_cast<const Abstract_Hist*>(get_BEptr())->operator_slash__BOSS(f) );
        }
        
        inline Pythia8::Hist Hist::operator/(const Pythia8::Hist& h2) const
        {
            return Pythia8::Hist( const_cast<const Abstract_Hist*>(get_BEptr())->operator_slash__BOSS(*h2.get_BEptr()) );
        }
        
        
        // Wrappers for original constructors: 
        inline Hist::Hist() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn, bool logXIn, bool doStatsIn) :
            WrapperBase(__factory1(titleIn, nBinIn, xMinIn, xMaxIn, logXIn, doStatsIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn, bool logXIn) :
            WrapperBase(__factory2(titleIn, nBinIn, xMinIn, xMaxIn, logXIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn) :
            WrapperBase(__factory3(titleIn, nBinIn, xMinIn, xMaxIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(std::string titleIn, int nBinIn, double xMinIn) :
            WrapperBase(__factory4(titleIn, nBinIn, xMinIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(std::string titleIn, int nBinIn) :
            WrapperBase(__factory5(titleIn, nBinIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(std::string titleIn) :
            WrapperBase(__factory6(titleIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Hist::Hist(std::string titleIn, const Pythia8::Hist& h) :
            WrapperBase(__factory7(titleIn, h))
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

#endif /* __wrapper_Hist_def_Pythia_8_312_h__ */
