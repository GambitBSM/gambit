#ifndef __wrapper_AnalysisHandler_decl_Rivet_3_1_5_hh__
#define __wrapper_AnalysisHandler_decl_Rivet_3_1_5_hh__

#include <cstddef>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <ostream>
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
      
            double sumW() const;
      
            double sumW2() const;
      
            const ::std::vector<std::string>& weightNames() const;
      
            long unsigned int numWeights() const;
      
            bool haveNamedWeights() const;
      
            void setWeightNames(const HepMC3::GenEvent& ge);
      
            long unsigned int defaultWeightIndex() const;
      
            void setWeightCap(const double maxWeight);
      
            void setNLOSmearing(double frac);
      
            void skipMultiWeights(bool ignore);
      
            void skipMultiWeights();
      
            void selectMultiWeights(std::string patterns);
      
            void selectMultiWeights();
      
            void deselectMultiWeights(std::string patterns);
      
            void deselectMultiWeights();
      
            void setNominalWeightName(std::string name);
      
            void setNominalWeightName();
      
            void setCrossSection(const std::pair<double, double>& xsec, bool isUserSupplied);
      
            void setCrossSection(const std::pair<double, double>& xsec);
      
            void setCrossSection(double xsec, double xsecerr, bool isUserSupplied);
      
            void setCrossSection(double xsec, double xsecerr);
      
            double nominalCrossSection() const;
      
            ::std::pair<int, int> beamIds() const;
      
            double sqrtS() const;
      
            void checkBeams(bool check);
      
            void checkBeams();
      
            void setIgnoreBeams(bool ignore);
      
            void setIgnoreBeams();
      
            ::std::vector<std::string> analysisNames() const;
      
            ::std::vector<std::string> stdAnalysisNames() const;
      
            Rivet::AnalysisHandler& addAnalysis(const std::string& analysisname);
      
            Rivet::AnalysisHandler& addAnalysis(const std::string& analysisname, std::map<std::string, std::string> pars);
      
            Rivet::AnalysisHandler& addAnalyses(const std::vector<std::string>& analysisnames);
      
            Rivet::AnalysisHandler& removeAnalysis(const std::string& analysisname);
      
            Rivet::AnalysisHandler& removeAnalyses(const std::vector<std::string>& analysisnames);
      
            void init(const HepMC3::GenEvent& event);
      
            void analyze(const HepMC3::GenEvent& event);
      
            void analyze(const HepMC3::GenEvent* event);
      
            void finalize();
      
            void readData(const std::string& filename);
      
            ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getYodaAOs(bool includeraw) const;
      
            ::std::vector<std::shared_ptr<YODA::AnalysisObject>> getYodaAOs() const;
      
            void writeData(std::ostream& ostr, const std::string& fmt) const;
      
            void writeData(const std::string& filename) const;
      
            void dummy(YODA::AnalysisObject* arg_1) const;
      
            void setAODump(const std::string& dumpfile, int period);
      
            void setNoAODump();
      
            void dump(const std::string& dumpfile, int period);
      
            void mergeYodas(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches, const std::vector<std::string>& unmatches, bool equiv);
      
            void mergeYodas(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches, const std::vector<std::string>& unmatches);
      
            void mergeYodas(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches);
      
            void mergeYodas(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts);
      
            void mergeYodas(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts);
      
            void mergeYodas(const std::vector<std::string>& aofiles);
      
      
            // Wrappers for original constructors: 
         public:
            AnalysisHandler(const std::string& runname);
            AnalysisHandler();
      
            // Special pointer-based constructor: 
            AnalysisHandler(Abstract_AnalysisHandler* in);
      
            // Copy constructor: 
            AnalysisHandler(const AnalysisHandler& in);
      
            // Assignment operator: 
            AnalysisHandler& operator=(const AnalysisHandler& in);
      
            // Destructor: 
            ~AnalysisHandler();
      
            // Returns correctly casted pointer to Abstract class: 
            Abstract_AnalysisHandler* get_BEptr() const;
      
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_AnalysisHandler_decl_Rivet_3_1_5_hh__ */
