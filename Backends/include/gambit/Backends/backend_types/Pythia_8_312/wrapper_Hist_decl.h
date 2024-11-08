#ifndef __wrapper_Hist_decl_Pythia_8_312_h__
#define __wrapper_Hist_decl_Pythia_8_312_h__

#include <cstddef>
#include <string>
#include <functional>
#include <ostream>
#include <istream>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Hist.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Hist : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Hist* (*__factory0)();
                static Abstract_Hist* (*__factory1)(std::string, int, double, double, bool, bool);
                static Abstract_Hist* (*__factory2)(std::string, int, double, double, bool);
                static Abstract_Hist* (*__factory3)(std::string, int, double, double);
                static Abstract_Hist* (*__factory4)(std::string, int, double);
                static Abstract_Hist* (*__factory5)(std::string, int);
                static Abstract_Hist* (*__factory6)(std::string);
                static Abstract_Hist* (*__factory7)(std::string, const Pythia8::Hist&);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                Pythia8::Hist plotFunc(std::function<double (double)> f, std::string titleIn, int nBinIn, double xMinIn, double xMaxIn, bool logXIn);
        
                Pythia8::Hist plotFunc(std::function<double (double)> f, std::string titleIn, int nBinIn, double xMinIn, double xMaxIn);
        
                void book(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn, bool logXIn, bool doStatsIn);
        
                void book(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn, bool logXIn);
        
                void book(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn);
        
                void book(std::string titleIn, int nBinIn, double xMinIn);
        
                void book(std::string titleIn, int nBinIn);
        
                void book(std::string titleIn);
        
                void book();
        
                void title(std::string titleIn);
        
                void title();
        
                void null();
        
                void fill(double x, double w);
        
                void fill(double x);
        
                void table(std::ostream& os, bool printOverUnder, bool xMidBin, bool printError) const;
        
                void table(std::ostream& os, bool printOverUnder, bool xMidBin) const;
        
                void table(std::ostream& os, bool printOverUnder) const;
        
                void table(std::ostream& os) const;
        
                void table() const;
        
                void table(std::string fileName, bool printOverUnder, bool xMidBin, bool printError) const;
        
                void table(std::string fileName, bool printOverUnder, bool xMidBin) const;
        
                void table(std::string fileName, bool printOverUnder) const;
        
                void table(std::string fileName) const;
        
                void rivetTable(std::ostream& os, bool printError) const;
        
                void rivetTable(std::ostream& os) const;
        
                void rivetTable() const;
        
                void rivetTable(std::string fileName, bool printError) const;
        
                void rivetTable(std::string fileName) const;
        
                void pyplotTable(std::ostream& os, bool isHist, bool printError) const;
        
                void pyplotTable(std::ostream& os, bool isHist) const;
        
                void pyplotTable(std::ostream& os) const;
        
                void pyplotTable() const;
        
                void pyplotTable(std::string fileName, bool isHist, bool printError) const;
        
                void pyplotTable(std::string fileName, bool isHist) const;
        
                void pyplotTable(std::string fileName) const;
        
                void fillTable(std::istream& is);
        
                void fillTable();
        
                void fillTable(std::string fileName);
        
                ::std::string getTitle() const;
        
                int getBinNumber() const;
        
                int getNonFinite() const;
        
                bool getLinX() const;
        
                double getXMin() const;
        
                double getXMax() const;
        
                double getYMin() const;
        
                double getYMax() const;
        
                double getYAbsMin() const;
        
                double getXMean(bool unbinned) const;
        
                double getXMean() const;
        
                double getXMeanErr(bool unbinned) const;
        
                double getXMeanErr() const;
        
                double getXMedian(bool includeOverUnder) const;
        
                double getXMedian() const;
        
                double getXMedianErr(bool unbinned) const;
        
                double getXMedianErr() const;
        
                double getYMean() const;
        
                double getXRMN(int n, bool unbinned) const;
        
                double getXRMN(int n) const;
        
                double getXRMN() const;
        
                double getXRMS(bool unbinned) const;
        
                double getXRMS() const;
        
                double getXRMNErr(int n, bool unbinned) const;
        
                double getXRMNErr(int n) const;
        
                double getXRMNErr() const;
        
                double getXRMSErr(bool unbinned) const;
        
                double getXRMSErr() const;
        
                double getBinContent(int iBin) const;
        
                double getBinEdge(int iBin) const;
        
                double getBinWidth(int iBin) const;
        
                double getBinWidth() const;
        
                ::std::vector<double> getBinContents() const;
        
                ::std::vector<double> getBinEdges() const;
        
                int getEntries(bool alsoNonFinite) const;
        
                int getEntries() const;
        
                double getWeightSum(bool alsoOverUnder) const;
        
                double getWeightSum() const;
        
                double getNEffective() const;
        
                bool sameSize(const Pythia8::Hist& h) const;
        
                void takeFunc(std::function<double (double)> func);
        
                void takeLog(bool tenLog);
        
                void takeLog();
        
                void takeSqrt();
        
                void normalize(double f, bool overflow);
        
                void normalize(double f);
        
                void normalize();
        
                void normalizeIntegral(double f, bool overflow);
        
                void normalizeIntegral(double f);
        
                void normalizeIntegral();
        
                void normalizeSpectrum(double wtSum);
        
                Pythia8::Hist& operator+=(const Pythia8::Hist& h);
        
                Pythia8::Hist& operator-=(const Pythia8::Hist& h);
        
                Pythia8::Hist& operator*=(const Pythia8::Hist& h);
        
                Pythia8::Hist& operator/=(const Pythia8::Hist& h);
        
                Pythia8::Hist& operator+=(double f);
        
                Pythia8::Hist& operator-=(double f);
        
                Pythia8::Hist& operator*=(double f);
        
                Pythia8::Hist& operator/=(double f);
        
                Pythia8::Hist operator+(double f) const;
        
                Pythia8::Hist operator+(const Pythia8::Hist& h2) const;
        
                Pythia8::Hist operator-(double f) const;
        
                Pythia8::Hist operator-(const Pythia8::Hist& h2) const;
        
                Pythia8::Hist operator*(double f) const;
        
                Pythia8::Hist operator*(const Pythia8::Hist& h2) const;
        
                Pythia8::Hist operator/(double f) const;
        
                Pythia8::Hist operator/(const Pythia8::Hist& h2) const;
        
        
                // Wrappers for original constructors: 
            public:
                Hist();
                Hist(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn, bool logXIn, bool doStatsIn);
                Hist(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn, bool logXIn);
                Hist(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn);
                Hist(std::string titleIn, int nBinIn, double xMinIn);
                Hist(std::string titleIn, int nBinIn);
                Hist(std::string titleIn);
                Hist(std::string titleIn, const Pythia8::Hist& h);
        
                // Special pointer-based constructor: 
                Hist(Abstract_Hist* in);
        
                // Copy constructor: 
                Hist(const Hist& in);
        
                // Assignment operator: 
                Hist& operator=(const Hist& in);
        
                // Destructor: 
                ~Hist();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Hist* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Hist_decl_Pythia_8_312_h__ */
