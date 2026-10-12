#ifndef __abstract_AnalysisHandler_Rivet_4_1_0_hh__
#define __abstract_AnalysisHandler_Rivet_4_1_0_hh__

#include <cstddef>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <istream>
#include <ostream>
#include <fstream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hh"
#include "forward_decls_wrapper_classes.hh"
#include "HepMC3/GenEvent.h"
#include "YODA/AnalysisObject.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  namespace Rivet
  {
    class Abstract_AnalysisHandler : public virtual AbstractBase
    {
      public:
  
        virtual long unsigned int numEvents() const =0;
  
        virtual double effNumEvents() const =0;
  
        virtual double sumW() const =0;
  
        virtual double sumW2() const =0;
  
        virtual const ::std::vector<std::string>& weightNames() const =0;
  
        virtual long unsigned int numWeights() const =0;
  
        virtual bool haveNamedWeights() const =0;
  
        virtual void setWeightNames(const HepMC3::GenEvent&) =0;
  
        virtual void setWeightNames(const std::vector<std::string>&) =0;
  
        virtual long unsigned int defaultWeightIndex() const =0;
  
        virtual ::std::vector<double> weightSumWs() const =0;
  
        virtual void setWeightCap(const double) =0;
  
        virtual void setNominalWeightName(const std::string&) =0;
  
        virtual void skipMultiWeights(bool) =0;
  
        virtual void skipMultiWeights__BOSS() =0;
  
        virtual void matchWeightNames(const std::string&) =0;
  
        virtual void unmatchWeightNames(const std::string&) =0;
  
        virtual void setNLOSmearing(double) =0;
  
        virtual void setCrossSection(const std::vector<std::pair<double, double>>&, bool) =0;
  
        virtual void setCrossSection__BOSS(const std::vector<std::pair<double, double>>&) =0;
  
        virtual void setCrossSection(const std::pair<double, double>&, bool) =0;
  
        virtual void setCrossSection__BOSS(const std::pair<double, double>&) =0;
  
        virtual void setCrossSection(double, double, bool) =0;
  
        virtual void setCrossSection__BOSS(double, double) =0;
  
        virtual void updateCrossSection() =0;
  
        virtual void notifyEndOfFile() =0;
  
        virtual double nominalCrossSection() const =0;
  
        virtual double nominalCrossSectionError() const =0;
  
        virtual ::std::pair<int, int> runBeamIDs() const =0;
  
        virtual ::std::pair<double, double> runBeamEnergies() const =0;
  
        virtual double runSqrtS() const =0;
  
        virtual void setCheckBeams(bool) =0;
  
        virtual void setCheckBeams__BOSS() =0;
  
        virtual ::std::vector<std::string> annotations() const =0;
  
        virtual bool hasAnnotation(const std::string&) const =0;
  
        virtual const ::std::string& annotation(const std::string&) const =0;
  
        virtual const ::std::string& annotation(const std::string&, const std::string&) const =0;
  
        virtual void setAnnotations(const std::map<std::string, std::string>&) =0;
  
        virtual void rmAnnotation(const std::string&) =0;
  
        virtual void clearAnnotations() =0;
  
        virtual bool copyAO(std::shared_ptr<YODA::AnalysisObject>, std::shared_ptr<YODA::AnalysisObject>, const double) =0;
  
        virtual bool copyAO__BOSS(std::shared_ptr<YODA::AnalysisObject>, std::shared_ptr<YODA::AnalysisObject>) =0;
  
        virtual bool addAO(std::shared_ptr<YODA::AnalysisObject>, std::shared_ptr<YODA::AnalysisObject>&, const double) =0;
  
        virtual ::std::vector<std::string> analysisNames() const =0;
  
        virtual ::std::vector<std::string> stdAnalysisNames() const =0;
  
        virtual Rivet::Abstract_AnalysisHandler& addAnalysis__BOSS(const std::string&) =0;
  
        virtual Rivet::Abstract_AnalysisHandler& addAnalysis__BOSS(const std::string&, std::map<std::string, std::string>) =0;
  
        virtual Rivet::Abstract_AnalysisHandler& addAnalyses__BOSS(const std::vector<std::string>&) =0;
  
        virtual Rivet::Abstract_AnalysisHandler& removeAnalysis__BOSS(const std::string&) =0;
  
        virtual Rivet::Abstract_AnalysisHandler& removeAnalyses__BOSS(const std::vector<std::string>&) =0;
  
        virtual void init(const HepMC3::GenEvent&) =0;
  
        virtual void analyze(HepMC3::GenEvent&) =0;
  
        virtual void analyze(HepMC3::GenEvent*) =0;
  
        virtual void finalize() =0;
  
        virtual void collapseEventGroup() =0;
  
        virtual void readData(std::istream&, const std::string&, bool) =0;
  
        virtual void readData__BOSS(std::istream&, const std::string&) =0;
  
        virtual void readData(const std::string&, bool) =0;
  
        virtual void readData__BOSS(const std::string&) =0;
  
        virtual ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getYodaAOs(const bool, const bool) const =0;
  
        virtual ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getYodaAOs__BOSS(const bool) const =0;
  
        virtual ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getYodaAOs__BOSS() const =0;
  
        virtual ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getRawAOs() const =0;
  
        virtual ::std::vector<std::string> getRawAOPaths() const =0;
  
        virtual void writeData(std::ostream&, const std::string&) const =0;
  
        virtual void writeData(const std::string&) const =0;
  
        virtual void dummy(YODA::AnalysisObject*) const =0;
  
        virtual void setFinalizePeriod(const std::string&, int) =0;
  
        virtual void setNoFinalizePeriod() =0;
  
        virtual void setBootstrapFilename(const std::string&) =0;
  
        virtual ::std::vector<std::pair<std::basic_string<char>, unsigned long>> fillLayout() const =0;
  
        virtual ::std::vector<bool> fillOutcomes() const =0;
  
        virtual ::std::vector<double> fillFractions() const =0;
  
        virtual void mergeYODAs(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const bool, const bool) =0;
  
        virtual void mergeYODAs__BOSS(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const bool) =0;
  
        virtual void mergeYODAs__BOSS(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&) =0;
  
        virtual void mergeYODAs__BOSS(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&) =0;
  
        virtual void mergeYODAs__BOSS(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&) =0;
  
        virtual void mergeYODAs__BOSS(const std::vector<std::string>&, const std::vector<std::string>&) =0;
  
        virtual void mergeYODAs__BOSS(const std::vector<std::string>&) =0;
  
        virtual void merge__BOSS(Rivet::Abstract_AnalysisHandler&) =0;
  
        virtual void loadAOs(const std::vector<std::string>&, const std::vector<double>&) =0;
  
        virtual ::std::vector<double> serializeContent(bool) =0;
  
        virtual ::std::vector<double> serializeContent__BOSS() =0;
  
        virtual void deserializeContent(const std::vector<double>&, long unsigned int) =0;
  
        virtual void deserializeContent__BOSS(const std::vector<double>&) =0;
  
  
      private:
        AnalysisHandler* wptr;
        bool delete_wrapper;
      public:
        AnalysisHandler* get_wptr() { return wptr; }
        void set_wptr(AnalysisHandler* wptr_in) { wptr = wptr_in; }
        bool get_delete_wrapper() { return delete_wrapper; }
        void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
      public:
        Abstract_AnalysisHandler()
        {
          wptr = 0;
          delete_wrapper = false;
        }
  
        Abstract_AnalysisHandler(const Abstract_AnalysisHandler&)
        {
          wptr = 0;
          delete_wrapper = false;
        }
  
        Abstract_AnalysisHandler& operator=(const Abstract_AnalysisHandler&) { return *this; }
  
        virtual void init_wrapper() =0;
  
        AnalysisHandler* get_init_wptr()
        {
          init_wrapper();
          return wptr;
        }
  
        AnalysisHandler& get_init_wref()
        {
          init_wrapper();
          return *wptr;
        }
  
        virtual ~Abstract_AnalysisHandler() =0;
    };
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_AnalysisHandler_Rivet_4_1_0_hh__ */
