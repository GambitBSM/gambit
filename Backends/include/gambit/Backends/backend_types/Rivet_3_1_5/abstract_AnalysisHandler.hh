#ifndef __abstract_AnalysisHandler_Rivet_3_1_5_hh__
#define __abstract_AnalysisHandler_Rivet_3_1_5_hh__

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <ostream>
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
   
            virtual ::std::string runName() const =0;
   
            virtual long unsigned int numEvents() const =0;
   
            virtual double sumW() const =0;
   
            virtual double sumW2() const =0;
   
            virtual const ::std::vector<std::string>& weightNames() const =0;
   
            virtual long unsigned int numWeights() const =0;
   
            virtual bool haveNamedWeights() const =0;
   
            virtual void setWeightNames(const HepMC3::GenEvent&) =0;
   
            virtual long unsigned int defaultWeightIndex() const =0;
   
            virtual void setWeightCap(const double) =0;
   
            virtual void setNLOSmearing(double) =0;
   
            virtual void skipMultiWeights(bool) =0;
   
            virtual void skipMultiWeights__BOSS() =0;
   
            virtual void selectMultiWeights(std::string) =0;
   
            virtual void selectMultiWeights__BOSS() =0;
   
            virtual void deselectMultiWeights(std::string) =0;
   
            virtual void deselectMultiWeights__BOSS() =0;
   
            virtual void setNominalWeightName(std::string) =0;
   
            virtual void setNominalWeightName__BOSS() =0;
   
            virtual void setCrossSection(const std::pair<double, double>&, bool) =0;
   
            virtual void setCrossSection__BOSS(const std::pair<double, double>&) =0;
   
            virtual void setCrossSection(double, double, bool) =0;
   
            virtual void setCrossSection__BOSS(double, double) =0;
   
            virtual double nominalCrossSection() const =0;
   
            virtual ::std::pair<int, int> beamIds() const =0;
   
            virtual double sqrtS() const =0;
   
            virtual void checkBeams(bool) =0;
   
            virtual void checkBeams__BOSS() =0;
   
            virtual void setIgnoreBeams(bool) =0;
   
            virtual void setIgnoreBeams__BOSS() =0;
   
            virtual ::std::vector<std::string> analysisNames() const =0;
   
            virtual ::std::vector<std::string> stdAnalysisNames() const =0;
   
            virtual Rivet::Abstract_AnalysisHandler& addAnalysis__BOSS(const std::string&) =0;
   
            virtual Rivet::Abstract_AnalysisHandler& addAnalysis__BOSS(const std::string&, std::map<std::string, std::string>) =0;
   
            virtual Rivet::Abstract_AnalysisHandler& addAnalyses__BOSS(const std::vector<std::string>&) =0;
   
            virtual Rivet::Abstract_AnalysisHandler& removeAnalysis__BOSS(const std::string&) =0;
   
            virtual Rivet::Abstract_AnalysisHandler& removeAnalyses__BOSS(const std::vector<std::string>&) =0;
   
            virtual void init(const HepMC3::GenEvent&) =0;
   
            virtual void analyze(const HepMC3::GenEvent&) =0;
   
            virtual void analyze(const HepMC3::GenEvent*) =0;
   
            virtual void finalize() =0;
   
            virtual void readData(const std::string&) =0;
   
            virtual ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getYodaAOs(bool) const =0;
   
            virtual ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getYodaAOs__BOSS() const =0;
   
            virtual void writeData(std::ostream&, const std::string&) const =0;
   
            virtual void writeData(const std::string&) const =0;
   
            virtual void dummy(YODA::AnalysisObject*) const =0;
   
            virtual void setAODump(const std::string&, int) =0;
   
            virtual void setNoAODump() =0;
   
            virtual void dump(const std::string&, int) =0;
   
            virtual void mergeYodas(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, bool) =0;
   
            virtual void mergeYodas__BOSS(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&) =0;
   
            virtual void mergeYodas__BOSS(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&) =0;
   
            virtual void mergeYodas__BOSS(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<std::string>&) =0;
   
            virtual void mergeYodas__BOSS(const std::vector<std::string>&, const std::vector<std::string>&) =0;
   
            virtual void mergeYodas__BOSS(const std::vector<std::string>&) =0;
   
         public:
            virtual void pointer_assign__BOSS(Abstract_AnalysisHandler*) =0;
            virtual Abstract_AnalysisHandler* pointer_copy__BOSS() =0;
   
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


#endif /* __abstract_AnalysisHandler_Rivet_3_1_5_hh__ */
