#ifndef __wrapper_AnalysisHandler_def_Rivet_4_0_1_hh__
#define __wrapper_AnalysisHandler_def_Rivet_4_0_1_hh__

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <istream>
#include <ostream>
#include <fstream>
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
    
    inline double AnalysisHandler::effNumEvents() const
    {
      return get_BEptr()->effNumEvents();
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
    
    inline void AnalysisHandler::setWeightNames(const std::vector<std::string>& weightNames)
    {
      get_BEptr()->setWeightNames(weightNames);
    }
    
    inline long unsigned int AnalysisHandler::defaultWeightIndex() const
    {
      return get_BEptr()->defaultWeightIndex();
    }
    
    inline ::std::vector<double> AnalysisHandler::weightSumWs() const
    {
      return get_BEptr()->weightSumWs();
    }
    
    inline void AnalysisHandler::setWeightCap(const double maxWeight)
    {
      get_BEptr()->setWeightCap(maxWeight);
    }
    
    inline void AnalysisHandler::setNominalWeightName(const std::string& name)
    {
      get_BEptr()->setNominalWeightName(name);
    }
    
    inline void AnalysisHandler::skipMultiWeights(bool skip)
    {
      get_BEptr()->skipMultiWeights(skip);
    }
    
    inline void AnalysisHandler::skipMultiWeights()
    {
      get_BEptr()->skipMultiWeights__BOSS();
    }
    
    inline void AnalysisHandler::matchWeightNames(const std::string& patterns)
    {
      get_BEptr()->matchWeightNames(patterns);
    }
    
    inline void AnalysisHandler::unmatchWeightNames(const std::string& patterns)
    {
      get_BEptr()->unmatchWeightNames(patterns);
    }
    
    inline void AnalysisHandler::setNLOSmearing(double frac)
    {
      get_BEptr()->setNLOSmearing(frac);
    }
    
    inline void AnalysisHandler::setCrossSection(const std::vector<std::pair<double, double>>& xsecs, bool isUserSupplied)
    {
      get_BEptr()->setCrossSection(xsecs, isUserSupplied);
    }
    
    inline void AnalysisHandler::setCrossSection(const std::vector<std::pair<double, double>>& xsecs)
    {
      get_BEptr()->setCrossSection__BOSS(xsecs);
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
    
    inline void AnalysisHandler::updateCrossSection()
    {
      get_BEptr()->updateCrossSection();
    }
    
    inline void AnalysisHandler::notifyEndOfFile()
    {
      get_BEptr()->notifyEndOfFile();
    }
    
    inline double AnalysisHandler::nominalCrossSection() const
    {
      return get_BEptr()->nominalCrossSection();
    }
    
    inline double AnalysisHandler::nominalCrossSectionError() const
    {
      return get_BEptr()->nominalCrossSectionError();
    }
    
    inline ::std::pair<int, int> AnalysisHandler::runBeamIDs() const
    {
      return get_BEptr()->runBeamIDs();
    }
    
    inline ::std::pair<double, double> AnalysisHandler::runBeamEnergies() const
    {
      return get_BEptr()->runBeamEnergies();
    }
    
    inline double AnalysisHandler::runSqrtS() const
    {
      return get_BEptr()->runSqrtS();
    }
    
    inline void AnalysisHandler::setCheckBeams(bool check)
    {
      get_BEptr()->setCheckBeams(check);
    }
    
    inline void AnalysisHandler::setCheckBeams()
    {
      get_BEptr()->setCheckBeams__BOSS();
    }
    
    inline ::std::vector<std::string> AnalysisHandler::annotations() const
    {
      return get_BEptr()->annotations();
    }
    
    inline bool AnalysisHandler::hasAnnotation(const std::string& name) const
    {
      return get_BEptr()->hasAnnotation(name);
    }
    
    inline const ::std::string& AnalysisHandler::annotation(const std::string& name) const
    {
      return get_BEptr()->annotation(name);
    }
    
    inline const ::std::string& AnalysisHandler::annotation(const std::string& name, const std::string& defaultreturn) const
    {
      return get_BEptr()->annotation(name, defaultreturn);
    }
    
    inline void AnalysisHandler::setAnnotations(const std::map<std::string, std::string>& anns)
    {
      get_BEptr()->setAnnotations(anns);
    }
    
    inline void AnalysisHandler::rmAnnotation(const std::string& name)
    {
      get_BEptr()->rmAnnotation(name);
    }
    
    inline void AnalysisHandler::clearAnnotations()
    {
      get_BEptr()->clearAnnotations();
    }
    
    inline bool AnalysisHandler::copyAO(std::shared_ptr<YODA::AnalysisObject> src, std::shared_ptr<YODA::AnalysisObject> dst, const double scale)
    {
      return get_BEptr()->copyAO(src, dst, scale);
    }
    
    inline bool AnalysisHandler::copyAO(std::shared_ptr<YODA::AnalysisObject> src, std::shared_ptr<YODA::AnalysisObject> dst)
    {
      return get_BEptr()->copyAO__BOSS(src, dst);
    }
    
    inline bool AnalysisHandler::addAO(std::shared_ptr<YODA::AnalysisObject> src, std::shared_ptr<YODA::AnalysisObject>& dst, const double scale)
    {
      return get_BEptr()->addAO(src, dst, scale);
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
    
    inline void AnalysisHandler::analyze(HepMC3::GenEvent& event)
    {
      get_BEptr()->analyze(event);
    }
    
    inline void AnalysisHandler::analyze(HepMC3::GenEvent* event)
    {
      get_BEptr()->analyze(event);
    }
    
    inline void AnalysisHandler::finalize()
    {
      get_BEptr()->finalize();
    }
    
    inline void AnalysisHandler::collapseEventGroup()
    {
      get_BEptr()->collapseEventGroup();
    }
    
    inline void AnalysisHandler::readData(std::istream& istr, const std::string& fmt, bool preload)
    {
      get_BEptr()->readData(istr, fmt, preload);
    }
    
    inline void AnalysisHandler::readData(std::istream& istr, const std::string& fmt)
    {
      get_BEptr()->readData__BOSS(istr, fmt);
    }
    
    inline void AnalysisHandler::readData(const std::string& filename, bool preload)
    {
      get_BEptr()->readData(filename, preload);
    }
    
    inline void AnalysisHandler::readData(const std::string& filename)
    {
      get_BEptr()->readData__BOSS(filename);
    }
    
    inline ::std::vector<std::shared_ptr<YODA::AnalysisObject>> AnalysisHandler::getYodaAOs(const bool includeraw, const bool mkinert) const
    {
      return get_BEptr()->getYodaAOs(includeraw, mkinert);
    }
    
    inline ::std::vector<std::shared_ptr<YODA::AnalysisObject>> AnalysisHandler::getYodaAOs(const bool includeraw) const
    {
      return get_BEptr()->getYodaAOs__BOSS(includeraw);
    }
    
    inline ::std::vector<std::shared_ptr<YODA::AnalysisObject>> AnalysisHandler::getYodaAOs() const
    {
      return get_BEptr()->getYodaAOs__BOSS();
    }
    
    inline ::std::vector<std::shared_ptr<YODA::AnalysisObject>> AnalysisHandler::getRawAOs() const
    {
      return get_BEptr()->getRawAOs();
    }
    
    inline ::std::vector<std::string> AnalysisHandler::getRawAOPaths() const
    {
      return get_BEptr()->getRawAOPaths();
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
    
    inline void AnalysisHandler::setFinalizePeriod(const std::string& dumpfile, int period)
    {
      get_BEptr()->setFinalizePeriod(dumpfile, period);
    }
    
    inline void AnalysisHandler::setNoFinalizePeriod()
    {
      get_BEptr()->setNoFinalizePeriod();
    }
    
    inline void AnalysisHandler::setBootstrapFilename(const std::string& filename)
    {
      get_BEptr()->setBootstrapFilename(filename);
    }
    
    inline ::std::vector<std::pair<std::basic_string<char>, unsigned long>> AnalysisHandler::fillLayout() const
    {
      return get_BEptr()->fillLayout();
    }
    
    inline ::std::vector<bool> AnalysisHandler::fillOutcomes() const
    {
      return get_BEptr()->fillOutcomes();
    }
    
    inline ::std::vector<double> AnalysisHandler::fillFractions() const
    {
      return get_BEptr()->fillFractions();
    }
    
    inline void AnalysisHandler::mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches, const std::vector<std::string>& unmatches, const bool equiv, const bool reentrantOnly)
    {
      get_BEptr()->mergeYODAs(aofiles, delopts, addopts, matches, unmatches, equiv, reentrantOnly);
    }
    
    inline void AnalysisHandler::mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches, const std::vector<std::string>& unmatches, const bool equiv)
    {
      get_BEptr()->mergeYODAs__BOSS(aofiles, delopts, addopts, matches, unmatches, equiv);
    }
    
    inline void AnalysisHandler::mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches, const std::vector<std::string>& unmatches)
    {
      get_BEptr()->mergeYODAs__BOSS(aofiles, delopts, addopts, matches, unmatches);
    }
    
    inline void AnalysisHandler::mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts, const std::vector<std::string>& matches)
    {
      get_BEptr()->mergeYODAs__BOSS(aofiles, delopts, addopts, matches);
    }
    
    inline void AnalysisHandler::mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts, const std::vector<std::string>& addopts)
    {
      get_BEptr()->mergeYODAs__BOSS(aofiles, delopts, addopts);
    }
    
    inline void AnalysisHandler::mergeYODAs(const std::vector<std::string>& aofiles, const std::vector<std::string>& delopts)
    {
      get_BEptr()->mergeYODAs__BOSS(aofiles, delopts);
    }
    
    inline void AnalysisHandler::mergeYODAs(const std::vector<std::string>& aofiles)
    {
      get_BEptr()->mergeYODAs__BOSS(aofiles);
    }
    
    inline void AnalysisHandler::merge(Rivet::AnalysisHandler& other)
    {
      get_BEptr()->merge__BOSS(*other.get_BEptr());
    }
    
    inline void AnalysisHandler::loadAOs(const std::vector<std::string>& aoPaths, const std::vector<double>& aoData)
    {
      get_BEptr()->loadAOs(aoPaths, aoData);
    }
    
    inline ::std::vector<double> AnalysisHandler::serializeContent(bool fixed_length)
    {
      return get_BEptr()->serializeContent(fixed_length);
    }
    
    inline ::std::vector<double> AnalysisHandler::serializeContent()
    {
      return get_BEptr()->serializeContent__BOSS();
    }
    
    inline void AnalysisHandler::deserializeContent(const std::vector<double>& data, long unsigned int nprocs)
    {
      get_BEptr()->deserializeContent(data, nprocs);
    }
    
    inline void AnalysisHandler::deserializeContent(const std::vector<double>& data)
    {
      get_BEptr()->deserializeContent__BOSS(data);
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

#endif /* __wrapper_AnalysisHandler_def_Rivet_4_0_1_hh__ */
