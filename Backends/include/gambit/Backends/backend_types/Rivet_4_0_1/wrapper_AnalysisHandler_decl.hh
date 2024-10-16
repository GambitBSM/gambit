#ifndef __wrapper_AnalysisHandler_decl_Rivet_4_0_1_hh__
#define __wrapper_AnalysisHandler_decl_Rivet_4_0_1_hh__

#include <cstddef>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <istream>
#include <ostream>
#include <fstream>
#include "forward_decls_wrapper_classes.hh"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_AnalysisHandler.hh"
#include "HepMC3/GenEvent.h"
#include "YODA/AnalysisObject.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  namespace Rivet
  {
    
    class AnalysisHandler : public WrapperBase
    {
        // Member variables: 
      public:
        // -- Static factory pointers: 
        static Abstract_AnalysisHandler* (*__factory0)(const std::string&);
        static Abstract_AnalysisHandler* (*__factory1)();
    
        // -- Other member variables: 
    
        // Member functions: 
      public:
        ::std::string runName() const;
    
        long unsigned int numEvents() const;
    
        double effNumEvents() const;
    
        double sumW() const;
    
        double sumW2() const;
    
        const ::std::vector<std::string>& weightNames() const;
    
        long unsigned int numWeights() const;
    
        bool haveNamedWeights() const;
    
        void setWeightNames(const HepMC3::GenEvent& ge);
    
        void setWeightNames(const std::vector<std::string>& weightNames);
    
        long unsigned int defaultWeightIndex() const;
    
        ::std::vector<double> weightSumWs() const;
    
        void setWeightCap(const double maxWeight);
    
        void setNominalWeightName(const std::string& name);
    
        void skipMultiWeights(bool skip);
    
        void skipMultiWeights();
    
        void matchWeightNames(const std::string& patterns);
    
        void unmatchWeightNames(const std::string& patterns);
    
        void setNLOSmearing(double frac);
    
        void setCrossSection(const std::vector<std::pair<double, double>>& xsecs, bool isUserSupplied);
    
        void setCrossSection(const std::vector<std::pair<double, double>>& xsecs);
    
        void setCrossSection(const std::pair<double, double>& xsec, bool isUserSupplied);
    
        void setCrossSection(const std::pair<double, double>& xsec);
    
        void setCrossSection(double xsec, double xsecerr, bool isUserSupplied);
    
        void setCrossSection(double xsec, double xsecerr);
    
        void updateCrossSection();
    
        void notifyEndOfFile();
    
        double nominalCrossSection() const;
    
        double nominalCrossSectionError() const;
    
        ::std::pair<int, int> runBeamIDs() const;
    
        ::std::pair<double, double> runBeamEnergies() const;
    
        double runSqrtS() const;
    
        void setCheckBeams(bool check);
    
        void setCheckBeams();
    
        ::std::vector<std::string> annotations() const;
    
        bool hasAnnotation(const std::string& name) const;
    
        const ::std::string& annotation(const std::string& name) const;
    
        const ::std::string& annotation(const std::string& name, const std::string& defaultreturn) const;
    
        void setAnnotations(const std::map<std::string, std::string>& anns);
    
        void rmAnnotation(const std::string& name);
    
        void clearAnnotations();
    
        bool copyAO(std::shared_ptr<YODA::AnalysisObject> src, std::shared_ptr<YODA::AnalysisObject> dst, const double scale);
    
        bool copyAO(std::shared_ptr<YODA::AnalysisObject> src, std::shared_ptr<YODA::AnalysisObject> dst);
    
        bool addAO(std::shared_ptr<YODA::AnalysisObject> src, std::shared_ptr<YODA::AnalysisObject>& dst, const double scale);
    
        ::std::vector<std::string> analysisNames() const;
    
        ::std::vector<std::string> stdAnalysisNames() const;
    
        Rivet::AnalysisHandler& addAnalysis(const std::string& analysisname);
    
        Rivet::AnalysisHandler& addAnalysis(const std::string& analysisname, std::map<std::string, std::string> pars);
    
        Rivet::AnalysisHandler& addAnalyses(const std::vector<std::string>& analysisnames);
    
        Rivet::AnalysisHandler& removeAnalysis(const std::string& analysisname);
    
        Rivet::AnalysisHandler& removeAnalyses(const std::vector<std::string>& analysisnames);
    
        void init(const HepMC3::GenEvent& event);
    
        void analyze(HepMC3::GenEvent& event);
    
        void analyze(HepMC3::GenEvent* event);
    
        void finalize();
    
        void collapseEventGroup();
    
        void readData(std::istream& istr, const std::string& fmt, bool preload);
    
        void readData(std::istream& istr, const std::string& fmt);
    
        void readData(const std::string& filename, bool preload);
    
        void readData(const std::string& filename);
    
        ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getYodaAOs(const bool includeraw, const bool mkinert) const;
    
        ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getYodaAOs(const bool includeraw) const;
    
        ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getYodaAOs() const;
    
        ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getRawAOs() const;
    
        ::std::vector<std::string> getRawAOPaths() const;
    
        void writeData(std::ostream& ostr, const std::string& fmt) const;
    
        void writeData(const std::string& filename) const;
    
        void dummy(YODA::AnalysisObject* arg_1) const;
    
        void setFinalizePeriod(const std::string& dumpfile, int period);
    
        void setNoFinalizePeriod();
    
        void setBootstrapFilename(const std::string& filename);
    
        ::std::vector<std::pair<std::basic_string<char>, unsigned long>> fillLayout() const;
    
        ::std::vector<bool> fillOutcomes() const;
    
        ::std::vector<double> fillFractions() const;
    
        void mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches, const std::vector<std::string>& unmatches, const bool equiv, const bool reentrantOnly);
    
        void mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches, const std::vector<std::string>& unmatches, const bool equiv);
    
        void mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches, const std::vector<std::string>& unmatches);
    
        void mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches);
    
        void mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts);
    
        void mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts);
    
        void mergeYODAs(const std::vector<std::string>& aofiles);
    
        void merge(Rivet::AnalysisHandler& other);
    
        void loadAOs(const std::vector<std::string>& aoPaths, const std::vector<double>& aoData);
    
        ::std::vector<double> serializeContent(bool fixed_length);
    
        ::std::vector<double> serializeContent();
    
        void deserializeContent(const std::vector<double>& data, long unsigned int nprocs);
    
        void deserializeContent(const std::vector<double>& data);
    
    
        // Wrappers for original constructors: 
      public:
        AnalysisHandler(const std::string& runname);
        AnalysisHandler();
    
        // Special pointer-based constructor: 
        AnalysisHandler(Abstract_AnalysisHandler* in);
    
        // Destructor: 
        ~AnalysisHandler();
    
        // Returns correctly casted pointer to Abstract class: 
        Abstract_AnalysisHandler* get_BEptr() const;
    
    };
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_AnalysisHandler_decl_Rivet_4_0_1_hh__ */
