#ifndef __abstract_Hist_Pythia_8_312_h__
#define __abstract_Hist_Pythia_8_312_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <functional>
#include <ostream>
#include <istream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Hist : public virtual AbstractBase
        {
            public:
    
                virtual Pythia8::Abstract_Hist& operator_equal__BOSS(const Pythia8::Abstract_Hist&) =0;
    
                virtual Pythia8::Abstract_Hist* plotFunc__BOSS(std::function<double (double)>, std::string, int, double, double, bool) =0;
    
                virtual Pythia8::Abstract_Hist* plotFunc__BOSS(std::function<double (double)>, std::string, int, double, double) =0;
    
                virtual void book(std::string, int, double, double, bool, bool) =0;
    
                virtual void book__BOSS(std::string, int, double, double, bool) =0;
    
                virtual void book__BOSS(std::string, int, double, double) =0;
    
                virtual void book__BOSS(std::string, int, double) =0;
    
                virtual void book__BOSS(std::string, int) =0;
    
                virtual void book__BOSS(std::string) =0;
    
                virtual void book__BOSS() =0;
    
                virtual void title(std::string) =0;
    
                virtual void title__BOSS() =0;
    
                virtual void null() =0;
    
                virtual void fill(double, double) =0;
    
                virtual void fill__BOSS(double) =0;
    
                virtual void table(std::ostream&, bool, bool, bool) const =0;
    
                virtual void table__BOSS(std::ostream&, bool, bool) const =0;
    
                virtual void table__BOSS(std::ostream&, bool) const =0;
    
                virtual void table__BOSS(std::ostream&) const =0;
    
                virtual void table__BOSS() const =0;
    
                virtual void table(std::string, bool, bool, bool) const =0;
    
                virtual void table__BOSS(std::string, bool, bool) const =0;
    
                virtual void table__BOSS(std::string, bool) const =0;
    
                virtual void table__BOSS(std::string) const =0;
    
                virtual void rivetTable(std::ostream&, bool) const =0;
    
                virtual void rivetTable__BOSS(std::ostream&) const =0;
    
                virtual void rivetTable__BOSS() const =0;
    
                virtual void rivetTable(std::string, bool) const =0;
    
                virtual void rivetTable__BOSS(std::string) const =0;
    
                virtual void pyplotTable(std::ostream&, bool, bool) const =0;
    
                virtual void pyplotTable__BOSS(std::ostream&, bool) const =0;
    
                virtual void pyplotTable__BOSS(std::ostream&) const =0;
    
                virtual void pyplotTable__BOSS() const =0;
    
                virtual void pyplotTable(std::string, bool, bool) const =0;
    
                virtual void pyplotTable__BOSS(std::string, bool) const =0;
    
                virtual void pyplotTable__BOSS(std::string) const =0;
    
                virtual void fillTable(std::istream&) =0;
    
                virtual void fillTable__BOSS() =0;
    
                virtual void fillTable(std::string) =0;
    
                virtual ::std::string getTitle() const =0;
    
                virtual int getBinNumber() const =0;
    
                virtual int getNonFinite() const =0;
    
                virtual bool getLinX() const =0;
    
                virtual double getXMin() const =0;
    
                virtual double getXMax() const =0;
    
                virtual double getYMin() const =0;
    
                virtual double getYMax() const =0;
    
                virtual double getYAbsMin() const =0;
    
                virtual double getXMean(bool) const =0;
    
                virtual double getXMean__BOSS() const =0;
    
                virtual double getXMeanErr(bool) const =0;
    
                virtual double getXMeanErr__BOSS() const =0;
    
                virtual double getXMedian(bool) const =0;
    
                virtual double getXMedian__BOSS() const =0;
    
                virtual double getXMedianErr(bool) const =0;
    
                virtual double getXMedianErr__BOSS() const =0;
    
                virtual double getYMean() const =0;
    
                virtual double getXRMN(int, bool) const =0;
    
                virtual double getXRMN__BOSS(int) const =0;
    
                virtual double getXRMN__BOSS() const =0;
    
                virtual double getXRMS(bool) const =0;
    
                virtual double getXRMS__BOSS() const =0;
    
                virtual double getXRMNErr(int, bool) const =0;
    
                virtual double getXRMNErr__BOSS(int) const =0;
    
                virtual double getXRMNErr__BOSS() const =0;
    
                virtual double getXRMSErr(bool) const =0;
    
                virtual double getXRMSErr__BOSS() const =0;
    
                virtual double getBinContent(int) const =0;
    
                virtual double getBinEdge(int) const =0;
    
                virtual double getBinWidth(int) const =0;
    
                virtual double getBinWidth__BOSS() const =0;
    
                virtual ::std::vector<double> getBinContents() const =0;
    
                virtual ::std::vector<double> getBinEdges() const =0;
    
                virtual int getEntries(bool) const =0;
    
                virtual int getEntries__BOSS() const =0;
    
                virtual double getWeightSum(bool) const =0;
    
                virtual double getWeightSum__BOSS() const =0;
    
                virtual double getNEffective() const =0;
    
                virtual bool sameSize__BOSS(const Pythia8::Abstract_Hist&) const =0;
    
                virtual void takeFunc(std::function<double (double)>) =0;
    
                virtual void takeLog(bool) =0;
    
                virtual void takeLog__BOSS() =0;
    
                virtual void takeSqrt() =0;
    
                virtual void normalize(double, bool) =0;
    
                virtual void normalize__BOSS(double) =0;
    
                virtual void normalize__BOSS() =0;
    
                virtual void normalizeIntegral(double, bool) =0;
    
                virtual void normalizeIntegral__BOSS(double) =0;
    
                virtual void normalizeIntegral__BOSS() =0;
    
                virtual void normalizeSpectrum(double) =0;
    
                virtual Pythia8::Abstract_Hist& operator_plus_equal__BOSS(const Pythia8::Abstract_Hist&) =0;
    
                virtual Pythia8::Abstract_Hist& operator_minus_equal__BOSS(const Pythia8::Abstract_Hist&) =0;
    
                virtual Pythia8::Abstract_Hist& operator_asterix_equal__BOSS(const Pythia8::Abstract_Hist&) =0;
    
                virtual Pythia8::Abstract_Hist& operator_slash_equal__BOSS(const Pythia8::Abstract_Hist&) =0;
    
                virtual Pythia8::Abstract_Hist& operator_plus_equal__BOSS(double) =0;
    
                virtual Pythia8::Abstract_Hist& operator_minus_equal__BOSS(double) =0;
    
                virtual Pythia8::Abstract_Hist& operator_asterix_equal__BOSS(double) =0;
    
                virtual Pythia8::Abstract_Hist& operator_slash_equal__BOSS(double) =0;
    
                virtual Pythia8::Abstract_Hist* operator_plus__BOSS(double) const =0;
    
                virtual Pythia8::Abstract_Hist* operator_plus__BOSS(const Pythia8::Abstract_Hist&) const =0;
    
                virtual Pythia8::Abstract_Hist* operator_minus__BOSS(double) const =0;
    
                virtual Pythia8::Abstract_Hist* operator_minus__BOSS(const Pythia8::Abstract_Hist&) const =0;
    
                virtual Pythia8::Abstract_Hist* operator_asterix__BOSS(double) const =0;
    
                virtual Pythia8::Abstract_Hist* operator_asterix__BOSS(const Pythia8::Abstract_Hist&) const =0;
    
                virtual Pythia8::Abstract_Hist* operator_slash__BOSS(double) const =0;
    
                virtual Pythia8::Abstract_Hist* operator_slash__BOSS(const Pythia8::Abstract_Hist&) const =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Hist*) =0;
                virtual Abstract_Hist* pointer_copy__BOSS() =0;
    
            private:
                Hist* wptr;
                bool delete_wrapper;
            public:
                Hist* get_wptr() { return wptr; }
                void set_wptr(Hist* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Hist()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Hist(const Abstract_Hist&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Hist& operator=(const Abstract_Hist&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Hist* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Hist& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Hist() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Hist_Pythia_8_312_h__ */
