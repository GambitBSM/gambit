#ifndef __wrapper_AnalysisHandler_def_Rivet_3_1_5_hh__
#define __wrapper_AnalysisHandler_def_Rivet_3_1_5_hh__

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <ostream>
#include "HepMC3/GenEvent.h"
#include "YODA/AnalysisObject.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace Rivet
   {
      
      // Member functions: 
      inline ::std::string AnalysisHandler::runName() const
      {
         return get_BEptr()->runName();
      }
      
      inline long unsigned int AnalysisHandler::numEvents() const
      {
         return get_BEptr()->numEvents();
      }
      
      inline double AnalysisHandler::sumW() const
      {
         return get_BEptr()->sumW();
      }
      
      inline double AnalysisHandler::sumW2() const
      {
         return get_BEptr()->sumW2();
      }
      
      inline const ::std::vector<std::string>& AnalysisHandler::weightNames() const
      {
         return get_BEptr()->weightNames();
      }
      
      inline long unsigned int AnalysisHandler::numWeights() const
      {
         return get_BEptr()->numWeights();
      }
      
      inline bool AnalysisHandler::haveNamedWeights() const
      {
         return get_BEptr()->haveNamedWeights();
      }
      
      inline void AnalysisHandler::setWeightNames(const HepMC3::GenEvent& ge)
      {
         get_BEptr()->setWeightNames(ge);
      }
      
      inline long unsigned int AnalysisHandler::defaultWeightIndex() const
      {
         return get_BEptr()->defaultWeightIndex();
      }
      
      inline void AnalysisHandler::setWeightCap(const double maxWeight)
      {
         get_BEptr()->setWeightCap(maxWeight);
      }
      
      inline void AnalysisHandler::setNLOSmearing(double frac)
      {
         get_BEptr()->setNLOSmearing(frac);
      }
      
      inline void AnalysisHandler::skipMultiWeights(bool ignore)
      {
         get_BEptr()->skipMultiWeights(ignore);
      }
      
      inline void AnalysisHandler::skipMultiWeights()
      {
         get_BEptr()->skipMultiWeights__BOSS();
      }
      
      inline void AnalysisHandler::selectMultiWeights(std::string patterns)
      {
         get_BEptr()->selectMultiWeights(patterns);
      }
      
      inline void AnalysisHandler::selectMultiWeights()
      {
         get_BEptr()->selectMultiWeights__BOSS();
      }
      
      inline void AnalysisHandler::deselectMultiWeights(std::string patterns)
      {
         get_BEptr()->deselectMultiWeights(patterns);
      }
      
      inline void AnalysisHandler::deselectMultiWeights()
      {
         get_BEptr()->deselectMultiWeights__BOSS();
      }
      
      inline void AnalysisHandler::setNominalWeightName(std::string name)
      {
         get_BEptr()->setNominalWeightName(name);
      }
      
      inline void AnalysisHandler::setNominalWeightName()
      {
         get_BEptr()->setNominalWeightName__BOSS();
      }
      
      inline void AnalysisHandler::setCrossSection(const std::pair<double, double>& xsec, bool isUserSupplied)
      {
         get_BEptr()->setCrossSection(xsec, isUserSupplied);
      }
      
      inline void AnalysisHandler::setCrossSection(const std::pair<double, double>& xsec)
      {
         get_BEptr()->setCrossSection__BOSS(xsec);
      }
      
      inline void AnalysisHandler::setCrossSection(double xsec, double xsecerr, bool isUserSupplied)
      {
         get_BEptr()->setCrossSection(xsec, xsecerr, isUserSupplied);
      }
      
      inline void AnalysisHandler::setCrossSection(double xsec, double xsecerr)
      {
         get_BEptr()->setCrossSection__BOSS(xsec, xsecerr);
      }
      
      inline double AnalysisHandler::nominalCrossSection() const
      {
         return get_BEptr()->nominalCrossSection();
      }
      
      inline ::std::pair<int, int> AnalysisHandler::beamIds() const
      {
         return get_BEptr()->beamIds();
      }
      
      inline double AnalysisHandler::sqrtS() const
      {
         return get_BEptr()->sqrtS();
      }
      
      inline void AnalysisHandler::checkBeams(bool check)
      {
         get_BEptr()->checkBeams(check);
      }
      
      inline void AnalysisHandler::checkBeams()
      {
         get_BEptr()->checkBeams__BOSS();
      }
      
      inline void AnalysisHandler::setIgnoreBeams(bool ignore)
      {
         get_BEptr()->setIgnoreBeams(ignore);
      }
      
      inline void AnalysisHandler::setIgnoreBeams()
      {
         get_BEptr()->setIgnoreBeams__BOSS();
      }
      
      inline ::std::vector<std::string> AnalysisHandler::analysisNames() const
      {
         return get_BEptr()->analysisNames();
      }
      
      inline ::std::vector<std::string> AnalysisHandler::stdAnalysisNames() const
      {
         return get_BEptr()->stdAnalysisNames();
      }
      
      inline Rivet::AnalysisHandler& AnalysisHandler::addAnalysis(const std::string& analysisname)
      {
         return get_BEptr()->addAnalysis__BOSS(analysisname).get_init_wref();
      }
      
      inline Rivet::AnalysisHandler& AnalysisHandler::addAnalysis(const std::string& analysisname, std::map<std::string, std::string> pars)
      {
         return get_BEptr()->addAnalysis__BOSS(analysisname, pars).get_init_wref();
      }
      
      inline Rivet::AnalysisHandler& AnalysisHandler::addAnalyses(const std::vector<std::string>& analysisnames)
      {
         return get_BEptr()->addAnalyses__BOSS(analysisnames).get_init_wref();
      }
      
      inline Rivet::AnalysisHandler& AnalysisHandler::removeAnalysis(const std::string& analysisname)
      {
         return get_BEptr()->removeAnalysis__BOSS(analysisname).get_init_wref();
      }
      
      inline Rivet::AnalysisHandler& AnalysisHandler::removeAnalyses(const std::vector<std::string>& analysisnames)
      {
         return get_BEptr()->removeAnalyses__BOSS(analysisnames).get_init_wref();
      }
      
      inline void AnalysisHandler::init(const HepMC3::GenEvent& event)
      {
         get_BEptr()->init(event);
      }
      
      inline void AnalysisHandler::analyze(const HepMC3::GenEvent& event)
      {
         get_BEptr()->analyze(event);
      }
      
      inline void AnalysisHandler::analyze(const HepMC3::GenEvent* event)
      {
         get_BEptr()->analyze(event);
      }
      
      inline void AnalysisHandler::finalize()
      {
         get_BEptr()->finalize();
      }
      
      inline void AnalysisHandler::readData(const std::string& filename)
      {
         get_BEptr()->readData(filename);
      }
      
      inline ::std::vector<std::shared_ptr<YODA::AnalysisObject>> AnalysisHandler::getYodaAOs(bool includeraw) const
      {
         return get_BEptr()->getYodaAOs(includeraw);
      }
      
      inline ::std::vector<std::shared_ptr<YODA::AnalysisObject>> AnalysisHandler::getYodaAOs() const
      {
         return get_BEptr()->getYodaAOs__BOSS();
      }
      
      inline void AnalysisHandler::writeData(std::ostream& ostr, const std::string& fmt) const
      {
         get_BEptr()->writeData(ostr, fmt);
      }
      
      inline void AnalysisHandler::writeData(const std::string& filename) const
      {
         get_BEptr()->writeData(filename);
      }
      
      inline void AnalysisHandler::dummy(YODA::AnalysisObject* arg_1) const
      {
         get_BEptr()->dummy(arg_1);
      }
      
      inline void AnalysisHandler::setAODump(const std::string& dumpfile, int period)
      {
         get_BEptr()->setAODump(dumpfile, period);
      }
      
      inline void AnalysisHandler::setNoAODump()
      {
         get_BEptr()->setNoAODump();
      }
      
      inline void AnalysisHandler::dump(const std::string& dumpfile, int period)
      {
         get_BEptr()->dump(dumpfile, period);
      }
      
      inline void AnalysisHandler::mergeYodas(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches, const std::vector<std::string>& unmatches, bool equiv)
      {
         get_BEptr()->mergeYodas(aofiles, delopts, addopts, matches, unmatches, equiv);
      }
      
      inline void AnalysisHandler::mergeYodas(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches, const std::vector<std::string>& unmatches)
      {
         get_BEptr()->mergeYodas__BOSS(aofiles, delopts, addopts, matches, unmatches);
      }
      
      inline void AnalysisHandler::mergeYodas(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches)
      {
         get_BEptr()->mergeYodas__BOSS(aofiles, delopts, addopts, matches);
      }
      
      inline void AnalysisHandler::mergeYodas(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts)
      {
         get_BEptr()->mergeYodas__BOSS(aofiles, delopts, addopts);
      }
      
      inline void AnalysisHandler::mergeYodas(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts)
      {
         get_BEptr()->mergeYodas__BOSS(aofiles, delopts);
      }
      
      inline void AnalysisHandler::mergeYodas(const std::vector<std::string>& aofiles)
      {
         get_BEptr()->mergeYodas__BOSS(aofiles);
      }
      
      
      // Wrappers for original constructors: 
      inline AnalysisHandler::AnalysisHandler(const std::string& runname) :
         WrapperBase(__factory0(runname))
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      inline AnalysisHandler::AnalysisHandler() :
         WrapperBase(__factory1())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Special pointer-based constructor: 
      inline AnalysisHandler::AnalysisHandler(Abstract_AnalysisHandler* in) :
         WrapperBase(in)
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Copy constructor: 
      inline AnalysisHandler::AnalysisHandler(const AnalysisHandler& in) :
         WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Assignment operator: 
      inline AnalysisHandler& AnalysisHandler::operator=(const AnalysisHandler& in)
      {
         if (this != &in)
         {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
         }
         return *this;
      }
      
      
      // Destructor: 
      inline AnalysisHandler::~AnalysisHandler()
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
      inline Abstract_AnalysisHandler* Rivet::AnalysisHandler::get_BEptr() const
      {
         return dynamic_cast<Abstract_AnalysisHandler*>(BEptr);
      }
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_AnalysisHandler_def_Rivet_3_1_5_hh__ */
