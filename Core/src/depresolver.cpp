//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Dependency resolution with boost graph library
///
///          unravels the un-unravelable
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 May, Jun, Jul, Sep
///  \date 2014 Feb, Mar, Apr
///
///  \author Pat Scott
///          (patrickcolinscott@gmail.com)
///  \date 2013 May, Jul, Aug, Nov
///        2014 Jan, Mar, Apr, Dec
///        2018 Sep, Nov
///        2022 Nov, Dec
///        2023 Jan
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu)
///  \date 2013 Sep
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2017 June
///        2019 May
///        2020 June
///        2021 Sep
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2020 May, Nov
///
///  *********************************************

#include "gambit/Core/depresolver.hpp"
#include "gambit/Core/observable.hpp"
#include "gambit/Core/rule.hpp"
#include "gambit/Models/models.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/version.hpp"
#include "gambit/Utils/bibtex_functions.hpp"
#include "gambit/Utils/citation_keys.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Backends/backend_singleton.hpp"
#include "gambit/cmake/cmake_variables.hpp"

#include <sstream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <utility>

#include <boost/format.hpp>
#include <boost/algorithm/string/replace.hpp>
#ifdef HAVE_GRAPHVIZ
  #include <boost/graph/graphviz.hpp>
#endif

// Dependency types
#define NORMAL_DEPENDENCY 1
#define LOOP_MANAGER_DEPENDENCY 2

// Debug flag
//#define DEPRES_DEBUG

// Verbose flag (not debug per se, just basic dependency resolution information)
//#define VERBOSE_DEP_RES

namespace Gambit
{

  namespace DRes
  {
    using namespace LogTags;

    ///////////////////////
    // Auxiliary classes
    //////////////////////

    /// Default constructor for QueueEntry
    QueueEntry::QueueEntry()
    : toVertex(0),
      obslike(NULL)
    {}

    /// Alternative constructor for QueueEntry
    QueueEntry::QueueEntry(sspair a, VertexID b, int c, bool d)
    : quantity(a),
      toVertex(b),
      dependency_type(c),
      printme(d),
      obslike(NULL)
    {}


    ///////////////////////
    // Auxiliary functions
    ///////////////////////

    //
    // Functions that act on a resolved dependency graph
    //

    /// Collect parent vertices recursively (excluding root vertex)
    void getParentVertices(const VertexID & vertex, const
        MasterGraphType & graph, std::set<VertexID> & myVertexList)
    {
      graph_traits<MasterGraphType>::in_edge_iterator it, iend;

      for (std::tie(it, iend) = in_edges(vertex, graph);
          it != iend; ++it)
      {
        if (std::find(myVertexList.begin(), myVertexList.end(), source(*it, graph)) == myVertexList.end() )
        {
          myVertexList.insert(source(*it, graph));
          getParentVertices(source(*it, graph), graph, myVertexList);
        }
      }
    }

    /// Sort given list of vertices (according to topological sort result)
    std::vector<VertexID> sortVertices(const std::set<VertexID> & set,
        const std::list<VertexID> & topoOrder)
    {
      std::vector<VertexID> result;
      for(const VertexID& v : topoOrder)
      {
        if (set.find(v) != set.end()) result.push_back(v);
      }
      return result;
    }

    /// Get sorted list of parent vertices
    std::vector<VertexID> getSortedParentVertices(const VertexID & vertex, const
        MasterGraphType & graph, const std::list<VertexID> & topoOrder)
    {
      std::set<VertexID> set;
      getParentVertices(vertex, graph, set);
      set.insert(vertex);
      return sortVertices(set, topoOrder);
    }

    //
    // Graphviz output
    //

    /// Graphviz output for edges/dependencies
    class edgeWriter
    {
      public:
        edgeWriter(const MasterGraphType*) {};
        void operator()(std::ostream&, const EdgeID&) const
        {
          //out << "[style=\"dotted\"]";
        }
    };

    /// Graphviz output for individual vertices/nodes/module functions
    class labelWriter
    {
      private:
        const MasterGraphType * myGraph;
      public:
        labelWriter(const MasterGraphType * masterGraph) : myGraph(masterGraph) {};
        void operator()(std::ostream& out, const VertexID& v) const
        {
          str type = Utils::fix_type((*myGraph)[v]->type());
          boost::replace_all(type, str("&"), str("&amp;"));
          boost::replace_all(type, str("<"), str("&lt;"));
          boost::replace_all(type, str(">"), str("&gt;"));
          out << "[fillcolor=\"#F0F0D0\", style=\"rounded,filled\", shape=box,";
          out << "label=< ";
          out << "<font point-size=\"20\" color=\"red\">" << (*myGraph)[v]->capability() << "</font><br/>";
          out <<  "Type: " << type << "<br/>";
          out <<  "Function: " << (*myGraph)[v]->name() << "<br/>";
          out <<  "Module: " << (*myGraph)[v]->origin();
          out << ">]";
        }
    };


    //
    // Misc
    //

    /// Return runtime estimate for a set of nodes
    double getTimeEstimate(const std::set<VertexID> & vertexList, const MasterGraphType &graph)
    {
      double result = 0;
      for (const VertexID& v : vertexList)
      {
        result += graph[v]->getRuntimeAverage();
      }
      return result;
    }



    ///////////////////////////////////////////////////
    // Public definitions of DependencyResolver class
    ///////////////////////////////////////////////////

    /// Constructor
    DependencyResolver::DependencyResolver(const gambit_core &core,
                                           const Models::ModelFunctorClaw &claw,
                                           const IniParser::IniFile &iniFile,
                                           const Utils::type_equivalency &equiv_classes,
                                                 Printers::BasePrinter &printer)
     : boundCore(&core),
       boundClaw(&claw),
       boundTEs(&equiv_classes),
       boundPrinter(&printer),
       boundIniFile(&iniFile),
       obslikes(boundIniFile->getObservables()),
       module_rules(boundIniFile->getModuleRules()),
       backend_rules(boundIniFile->getBackendRules()),
       index(get(vertex_index,masterGraph)),
       activeFunctorGraphFile(Utils::runtime_scratch()+"GAMBIT_active_functor_graph.gv")
    {
      addFunctors();
      logger() << LogTags::dependency_resolver << endl;
      logger() << "#######################################"   << endl;
      logger() << "#  List of Type Equivalency Classes   #"   << endl;
      logger() << "#######################################";
      for (const auto& equiv_class : boundTEs->equivalency_classes) logger() << endl << equiv_class;
      logger() << EOM;
    }


    //
    // Initialization stage
    //

    /// Main dependency resolution
    void DependencyResolver::doResolution()
    {
      // Queue of dependencies to be resolved
      std::queue<QueueEntry> resolutionQueue;

      // Set up list of target ObsLikes
      logger() << LogTags::dependency_resolver << endl;
      logger() << "#######################################"   << endl;
      logger() << "#        List of Target ObsLikes      #"   << endl;
      logger() << "#                                     #"   << endl;
      logger() << "# format: Capability (Type) [Purpose] #"   << endl;
      logger() << "#######################################";
      for (const Observable& obslike : obslikes)
      {
        // Format output
        logger() << LogTags::dependency_resolver << endl << obslike.capability << " (" << obslike.type << ") [" << obslike.purpose << "]";
        QueueEntry target;
        target.quantity.first = obslike.capability;
        target.quantity.second = obslike.type;
        target.obslike = &obslike;
        target.printme = obslike.printme;
        resolutionQueue.push(target);
      }
      logger() << EOM;

      // Activate functors compatible with model we scan over (and deactivate the rest)
      makeFunctorsModelCompatible();

      // Generate dependency tree (the core of the dependency resolution)
      generateTree(resolutionQueue);

      // Find one execution order for activated vertices that is compatible
      // with dependency structure
      function_order = run_topological_sort();

      // Loop manager initialization: Notify them about their nested functions
      for (const std::pair<const VertexID, std::set<VertexID>>& keyvalpair : loopManagerMap)
      {
        // Generate topologically sorted list of vertex IDs that are nested
        // within loop manager keyvalpair ...
        std::vector<VertexID> vertexList = sortVertices(keyvalpair.second, function_order);
        // ... convert that list into functor pointers...
        std::vector<functor*> functorList;
        for (const VertexID& v : vertexList)
        {
          functorList.push_back(masterGraph[v]);
        }
        // ...and store it into loop manager functor
        masterGraph[keyvalpair.first]->setNestedList(functorList);
      }

      // Initialise the printer object with a list of functors that are set to print
      initialisePrinter();

      #ifdef HAVE_GRAPHVIZ
        // Generate graphviz plot if running in dry-run mode.
        if (boundCore->show_runorder)
        {
          std::ofstream outf(activeFunctorGraphFile);
          write_graphviz(outf, masterGraph, labelWriter(&masterGraph), edgeWriter(&masterGraph));
        }
      #endif

      // Pre-compute the individually ordered vertex lists for each of the ObsLike entries.
      std::vector<VertexID> order = getObsLikeOrder();
      for(const auto& v : order)
      {
        SortedParentVertices[v] = getSortedParentVertices(v, masterGraph, function_order);
      }

      // Print list of backends required
      if (boundCore->show_backends)
      {
        printRequiredBackends();
      }

      // Get BibTeX key entries for backends, modules, etc
      getCitationKeys();

      // Get the scanID
      set_scanID();

      // Done
    }

    /// List of masterGraph content
    void DependencyResolver::printFunctorList()
    {
      // Activate functors compatible with model we scan over (and deactivate the rest)
      makeFunctorsModelCompatible();

      graph_traits<MasterGraphType>::vertex_iterator vi, vi_end;
      const str formatString = "%-20s %-32s %-32s %-32s %-15s %-7i %-5i %-5i\n";
      logger() << LogTags::dependency_resolver << endl << "Vertices registered in masterGraph" << endl;
      logger() << "----------------------------------" << endl;
      logger() << boost::format(formatString)%
       "MODULE"% "FUNCTION"% "CAPABILITY"% "TYPE"% "PURPOSE"% "STATUS"% "#DEPs"% "#BE_REQs";
      for (std::tie(vi, vi_end) = vertices(masterGraph); vi != vi_end; ++vi)
      {
        logger() << boost::format(formatString)%
         (*masterGraph[*vi]).origin()%
         (*masterGraph[*vi]).name()%
         (*masterGraph[*vi]).capability()%
         (*masterGraph[*vi]).type()%
         (*masterGraph[*vi]).purpose()%
         (*masterGraph[*vi]).status()%
         (*masterGraph[*vi]).dependencies().size()%
         (*masterGraph[*vi]).backendreqs().size();
      }
      logger() <<  "Registered Backend vertices" << endl;
      logger() <<  "---------------------------" << endl;
      logger() << printGenericFunctorList(boundCore->getBackendFunctors(), true);
      logger() << EOM;
    }

    /// Pretty print function evaluation order
    void DependencyResolver::printFunctorEvalOrder(bool toterminal)
    {
      // Running this lets us check the order of execution. Also helps
      // to verify that we actually have pointers to all the required
      // functors.

      // Get order of evaluation
      std::set<VertexID> parents;
      std::set<VertexID> done; //set of vertices already accounted for
      std::vector<VertexID> order = getObsLikeOrder();

      str formatString  = "%-5s %-25s %-25s %-25s\n";
      // Might need to check if terminal supports unicode characters...
      str formatString0 = "%-7s %-23s %-25s %-25s %-25s %-6s\n";  // header
      str formatString1a= "%-9s %-21s %-25s %-25s %-25s %-6s\n";  // target functors
      str formatString1b= "%-4s \u2514\u2500\u2500> %-21s %-25s %-25s %-25s %-6s\n";  // target functors
      str formatString2a= "     \u250C\u2500 %-23s %-25s %-25s %-25s %-6s\n";  // parents
      str formatString2b= "     \u251C\u2500 %-23s %-25s %-25s %-25s %-6s\n";
      str formatString3a= "     \u250CX %-23s %-25s %-25s %-25s %-6s\n"; // "already done" parents
      str formatString3b= "     \u251CX %-23s %-25s %-25s %-25s %-6s\n";

      int i = 0;

      // Show the order in which the target functors will be attacked.
      std::ostringstream ss;
      ss << endl << "Initial target functor evaluation order" << endl;
      ss << "----------------------------------" << endl;
      ss << boost::format(formatString)% "#"% "FUNCTION"% "CAPABILITY"% "ORIGIN";

      for (const VertexID& v : order)
      {
        ss << boost::format(formatString)%
         i%
         masterGraph[v]->name()%
         masterGraph[v]->capability()%
         masterGraph[v]->origin();
        i++;
      }

      ss << endl;

      i = 0; // Reset counter
      // Do another loop to show the full initial sequence of functor evaluation
      // This doesn't figure out the sequence within each target functor group; I'm not 100% sure where that is determined. This does, however, show which groups get evaluated first, and which functors are already evaluated.
      ss << endl << "Full initial functor evaluation order" << endl;
      ss << "----------------------------------" << endl;
      ss << boost::format(formatString0)% "#"% "FUNCTION"% "CAPABILITY"% "TYPE"% "ORIGIN"% "PRINT?";

      for (const VertexID& v : order)
      {
        // loop through parents of each target functor
        parents.clear();
        getParentVertices(v, masterGraph, parents);
        parents.insert(v);
        bool first = true;
        for (const VertexID& v2 : parents)
        {
            str formatstr;
            bool dowrite = false;
            // Check if parent functor has been ticked off the list
            bool is_done = done.find(v2) != done.end();
            if( (not is_done) and (v != v2) )
            {
                formatstr = formatString2b;
                if (first) formatstr = formatString2a;
                dowrite = true;
            }
            else if( v != v2)
            {
                // Might be better to just do nothing here, i.e. set dowrite=false. For now just flagging functor as done with a special format string.
                formatstr = formatString3b;
                if (first) formatstr = formatString3a;
                dowrite = true;
            }

            if (dowrite)
            {
              ss << boost::format(formatstr)%
                masterGraph[v2]->name()%
                masterGraph[v2]->capability()%
                masterGraph[v2]->type()%
                masterGraph[v2]->origin()%
                masterGraph[v2]->requiresPrinting();
            }
            done.insert(v2); // tick parent functor off the list
            first = false;
        }

        // Now show target functor info
        str formatstr;
        if(parents.size()==1) { formatstr = formatString1a; }
        else { formatstr = formatString1b; }
        ss << boost::format(formatstr)%
         i%
         masterGraph[v]->name()%
         masterGraph[v]->capability()%
         masterGraph[v]->type()%
         masterGraph[v]->origin()%
         masterGraph[v]->requiresPrinting();
        i++;

        done.insert(v); // tick this target functor off the list

      }
      ss << "(\"X\" indicates that the functor is pre-evaluated before the marked position)" << endl << endl;

      if (toterminal)
      {
        // There is a command line flag to get this information, since it is very
        // handy to check before launching a full job. It can always be checked via
        // the logs, but this feature is more convenient.
        cout << ss.str();
        #ifdef HAVE_GRAPHVIZ
          cout << "To get postscript plot of active functors, please run: " << endl;
          cout << GAMBIT_DIR << "/Core/scripts/./graphviz.sh " << activeFunctorGraphFile << " no-loners" << endl;
        #else
          cout << "To get postscript plot of active functors, please install graphviz, rerun cmake and remake GAMBIT." << endl << endl;
        #endif
      }

      logger() << LogTags::dependency_resolver << ss.str() << EOM;
    }

    /// Print the list of required backends
    void DependencyResolver::printRequiredBackends()
    {
      // Lists the required backends, indicating where several backends
      // can fulfil the same requirement
      std::stringstream ss;

      ss << endl << "Required backends to run file " << boundIniFile->filename() << std::endl;
      ss << "At least one backend candidate per row is required" << std::endl;
      ss << "--------------------------------------------------" << std::endl << std::endl;

      for(auto reqs : backendsRequired)
      {
        for(auto backend : reqs)
        {
          ss << boost::format("%-25s")%("("+backend.first+", "+backend.second+")");
        }
        ss << std::endl;
      }
      ss << std::endl;

      // Print to terminal
      std::cout << ss.str();

      // Print to logs
      logger() << LogTags::dependency_resolver << ss.str() << EOM;
    }

    /// Print the BibTeX citation keys
    void DependencyResolver::printCitationKeys()
    {

      // If the list is empty do not print anything
      if(citationKeys.empty()) return;

      std::stringstream ss;

      // Location of the bibtex file
      str bibtex_file_location = boundIniFile->getValueOrDef<str>(GAMBIT_DIR "/config/bibtex_entries.bib", "dependency_resolution", "bibtex_file_location");

      ss << "The scan you are about to run uses backends. Please make sure to cite all of them in your work." << std::endl;

      // Create a list of entries in the bibtex file
      BibTeX bibtex_file(bibtex_file_location);
      std::vector<str> entries = bibtex_file.getBibTeXEntries();

      // Make sure that each key has an entry on the bibtex file
      for(const auto& key : citationKeys)
      {
        // Now find each key in the list of entries
        if(std::find(entries.begin(), entries.end(), key) == entries.end())
        {
          std::ostringstream errmsg;
          errmsg << "The reference with key " << key << " cannot be found in the bibtex file " << bibtex_file_location << endl;
          errmsg << "Please make sure that the bibtex file contains the relevant bibtex entries." << endl;
          dependency_resolver_error().raise(LOCAL_INFO,errmsg.str());
        }
      }

      // Drop a bibtex file with the citation entries
      str bibtex_output_file = boundIniFile->getValueOrDef<str>("GAMBIT.bib", "dependency_resolution", "bibtex_output_file");
      bibtex_file.dropBibTeXFile(citationKeys, bibtex_output_file);

      // Drop a sample TeX file citing all backens
      str tex_output_file = boundIniFile->getValueOrDef<str>("GAMBIT.tex", "dependency_resolution", "tex_output_file");
      bibtex_file.dropTeXFile(citationKeys, tex_output_file, bibtex_output_file);

      ss << "You can find the list of references to include in " << bibtex_output_file << " and an example TeX file in " << tex_output_file << std::endl << std::endl;

      // Print to terminal
      std::cout << ss.str();

      // Print to logs
      logger() << LogTags::dependency_resolver << ss.str() << EOM;

    }

    //
    // Runtime
    //

    /// Returns list of ObsLike vertices in order of runtime
    std::vector<VertexID> DependencyResolver::getObsLikeOrder()
    {
      std::vector<VertexID> unsorted;
      std::vector<VertexID> sorted;
      std::set<VertexID> parents, colleagues, colleagues_min;
      // Copy unsorted vertexIDs --> unsorted
      for (const OutputVertex& ov : outputVertices)
      {
        unsorted.push_back(ov.vertex);
      }
      // Sort iteratively (unsorted --> sorted)
      while (unsorted.size() > 0)
      {
        double t2p_now;
        double t2p_min = -1;
        std::vector<VertexID>::iterator it_min;
        for (std::vector<VertexID>::iterator it = unsorted.begin(); it !=
            unsorted.end(); ++it)
        {
          parents.clear();
          getParentVertices(*it, masterGraph, parents);
          parents.insert(*it);
          // Remove vertices that were already calculated from the ist
          for (const auto& colleague : colleagues) parents.erase(colleague);
          t2p_now = (double) getTimeEstimate(parents, masterGraph);
          t2p_now /= masterGraph[*it]->getInvalidationRate();
          if (t2p_min < 0 or t2p_now < t2p_min)
          {
            t2p_min = t2p_now;
            it_min = it;
            colleagues_min = parents;
          }
        }
        // Extent list of calculated vertices
        colleagues.insert(colleagues_min.begin(), colleagues_min.end());
        double prop = masterGraph[*it_min]->getInvalidationRate();
        logger() << LogTags::dependency_resolver << "Estimated T [s]: " << t2p_min*prop << EOM;
        logger() << LogTags::dependency_resolver << "Estimated p: " << prop << EOM;
        sorted.push_back(*it_min);
        unsorted.erase(it_min);
      }
      return sorted;
    }

    /// Evaluates ObsLike vertex, and everything it depends on, and prints results
    void DependencyResolver::calcObsLike(VertexID vertex)
    {
      if (SortedParentVertices.find(vertex) == SortedParentVertices.end())
        core_error().raise(LOCAL_INFO, "Tried to calculate a function not in or not at top of dependency graph.");
      std::vector<VertexID> order = SortedParentVertices.at(vertex);

      for (const VertexID& v : order)
      {
        std::ostringstream ss;
        ss << "Calling " << masterGraph[v]->name() << " from " << masterGraph[v]->origin() << "...";
        logger() << LogTags::dependency_resolver << LogTags::info << LogTags::debug << ss.str() << EOM;
        masterGraph[v]->calculate();
        if (boundIniFile->getValueOrDef<bool>(
              false, "dependency_resolution", "log_runtime") )
        {
          double T = masterGraph[v]->getRuntimeAverage();
          logger() << LogTags::dependency_resolver << LogTags::info <<
            "Runtime, averaged over multiple calls [s]: " << T << EOM;
        }
        invalid_point_exception* e = masterGraph[v]->retrieve_invalid_point_exception();
        if (e != NULL) throw(*e);
      }
      // Reset the cout output precision, in case any backends have messed with it during the ObsLike evaluation.
      cout << std::setprecision(boundCore->get_outprec());
    }

    /// Prints the results of an ObsLike vertex
    void DependencyResolver::printObsLike(VertexID vertex, const int pointID)
    {
      // pointID is supplied by the scanner, and is used to tell the printer which model
      // point the results should be associated with.

      if (SortedParentVertices.find(vertex) == SortedParentVertices.end())
        core_error().raise(LOCAL_INFO, "Tried to calculate a function not in or not at top of dependency graph.");
      std::vector<VertexID> order = SortedParentVertices.at(vertex);

      for (const VertexID& v : order)
      {
        std::ostringstream ss;
        ss << "Printing " << masterGraph[v]->name() << " from " << masterGraph[v]->origin() << "...";
        logger() << LogTags::dependency_resolver << LogTags::info << LogTags::debug << ss.str() << EOM;

        if (not typeComp(masterGraph[v]->type(),  "void", *boundTEs))
        {
          // Note that this prints from thread index 0 only, i.e. results created by
          // threads other than the main one need to be accessed with
          //   masterGraph[*it]->print(boundPrinter,pointID,index);
          // where index is some integer s.t. 0 <= index <= number of hardware threads.
          // At the moment GAMBIT only prints results of thread 0, under the expectation
          // that nested module functions are all designed to gather their results into
          // thread 0.
          masterGraph[v]->print(boundPrinter,pointID);
        }
      }
    }

    /// Getter for print_timing flag (used by LikelihoodContainer)
    bool DependencyResolver::printTiming() { return print_timing; }

    /// Get the functor corresponding to a single VertexID
    functor* DependencyResolver::get_functor(VertexID id)
    {
      graph_traits<MasterGraphType>::vertex_iterator vi, vi_end;
      for (std::tie(vi, vi_end) = vertices(masterGraph); vi != vi_end; ++vi)
      {
        if (*vi == id) return masterGraph[id];
      }
      return NULL;
    }

    /// Ensure that the type of a given vertex is equivalent to at least one of a provided list, and return the match.
    str DependencyResolver::checkTypeMatch(VertexID vertex, const str& purpose, const std::vector<str>& types)
    {
      for (const auto& t : types)
      {
        if (typeComp(t, masterGraph[vertex]->type(), *boundTEs)) return t;
      }
      std::stringstream msg;
      msg << "All quantities with purpose \"" << purpose << "\" in your yaml file must have one " << endl
          << "of the following types: " << endl << "  " << types << endl
          << "You have tried to assign this purpose to " << masterGraph[vertex]->origin() << "::"
          << masterGraph[vertex]->name() << "," << endl << "which has capability: " << endl
          << "  " << masterGraph[vertex]->capability() << endl << "and result type: " << endl
          << "  [" << masterGraph[vertex]->type() << "]" << endl << "Please assign a different purpose to this entry.";
      core_error().raise(LOCAL_INFO, msg.str());
      return "If you make core errors non-fatal you deserve what you get.";
    }

    /// Return the purpose associated with a given functor.
    const str& DependencyResolver::getPurpose(VertexID v)
    {
      for (const OutputVertex& ov : outputVertices)
      {
        if (ov.vertex == v) return ov.purpose;
      }
      /// '__no_purpose' if the functor does not correspond to an ObsLike entry in the ini file.
      static const str none("__no_purpose");
      return none;
    }

    /// Tell functor that it invalidated the current point in model space (due to a large or NaN contribution to lnL)
    void DependencyResolver::invalidatePointAt(VertexID vertex, bool isnan)
    {
      if (isnan)
      {
        masterGraph[vertex]->notifyOfInvalidation("NaN returned for likelihood value.");
      }
      else
      {
        masterGraph[vertex]->notifyOfInvalidation("Cumulative log-likelihood pushed below threshold.");
      }
    }

    /// Reset all active functors and delete existing results.
    void DependencyResolver::resetAll()
    {
      graph_traits<MasterGraphType>::vertex_iterator vi, vi_end;
      for (std::tie(vi, vi_end) = vertices(masterGraph); vi != vi_end; ++vi)
      {
        if (masterGraph[*vi]->isActive()) masterGraph[*vi]->reset();
      }
    }


    ////////////////////////////////////////////////////
    // Private definitions of DependencyResolver class
    ////////////////////////////////////////////////////

    str DependencyResolver::printQuantityToBeResolved(const QueueEntry& entry)
    {
        str s = entry.quantity.first + " (" + entry.quantity.second + ")";
        s += ", required by ";
        if ( entry.obslike == NULL )
        {
            s += masterGraph[entry.toVertex]->capability() + " (";
            s += masterGraph[entry.toVertex]->type() + ") [";
            s += masterGraph[entry.toVertex]->name() + ", ";
            s += masterGraph[entry.toVertex]->origin() + "]";
        }
        else
            s += "ObsLike section of yaml file";
        return s;
    }

    /// Generic printer of the contents of a vector of functors as vertices
    str DependencyResolver::printGenericFunctorList(const std::vector<VertexID> & vertexIDs, bool print_version)
    {
        std::vector<functor*> functorList;
        for (const auto& vid : vertexIDs)
        {
          functorList.push_back(masterGraph[vid]);
        }
        return printGenericFunctorList(functorList, print_version);
    }

    /// Generic printer of the contents of a vector of functor-as-vertex, bool pairs
    str DependencyResolver::printGenericFunctorList(const std::vector<std::pair<VertexID, bool>> & vertexIDs, bool print_version)
    {
        std::vector<functor*> functorList;
        for (const auto& vid : vertexIDs)
        {
          functorList.push_back(masterGraph[vid.first]);
        }
        return printGenericFunctorList(functorList, print_version);
    }

    /// Generic printer of the contents of a vector of functors
    str DependencyResolver::printGenericFunctorList(const std::vector<functor*>& functorList, bool print_version)
    {
      const str formatString = "%-20s %-32s %-48s %-32s %-7i\n";
      str vtstring = (print_version ? "ORIGIN (VERSION)" : "ORIGIN");
      std::ostringstream stream;
      stream << boost::format(formatString)%vtstring% "FUNCTION"% "CAPABILITY"% "TYPE"% "STATUS";
      for (const functor* f : functorList)
      {
        str vstring = (print_version ? " (" + f->version() + ")" : "");
        stream << boost::format(formatString)%
         (f->origin() + vstring) %
         f->name()%
         f->capability()%
         f->type()%
         f->status();
      }
      return stream.str();
    }

    /// Generic printer of the contents of a vector of functor, bool pairs
    str DependencyResolver::printGenericFunctorList(const std::vector<std::pair<functor*, bool>> & vertexIDs, bool print_version)
    {
        std::vector<functor*> functorList;
        for (const auto& vid : vertexIDs)
        {
          functorList.push_back(vid.first);
        }
        return printGenericFunctorList(functorList, print_version);
    }

    /// Add module and primary model functors in bound core to class-internal
    /// masterGraph object
    void DependencyResolver::addFunctors()
    {
      // Add primary model functors to masterGraph
      for (const auto& f : boundCore->getPrimaryModelFunctors())
      {
        // Ignore functors with status set to 0 or less in order to ignore primary_model_functors
        // that are not to be used for the scan.
        if ( f->isAvailable() )
        {
          #ifdef DEPRES_DEBUG
            std::cout << "Adding primary model functor " << f->origin() << "::" << f->name() << " to masterGraph." << std::endl;
          #endif
          boost::add_vertex(f, this->masterGraph);
        }
      }
      // Add module functors to masterGraph
      for (const auto& f : boundCore->getModuleFunctors())
      {
          #ifdef DEPRES_DEBUG
            std::cout << "Adding module functor " << f->origin() << "::" << f->name() << " to masterGraph." << std::endl;
          #endif
          boost::add_vertex(f, this->masterGraph);
      }
    }

    /// Activate functors that are allowed to be used with one or more of the models being scanned.
    /// Also activate the model-conditional dependencies and backend requirements of those functors.
    void DependencyResolver::makeFunctorsModelCompatible()
    {
      // Run just once
      static bool already_run = false;
      if (already_run) return;

      graph_traits<MasterGraphType>::vertex_iterator vi, vi_end;
      std::set<str> modelList = boundClaw->get_activemodels();

      // Activate those module functors that match the combination of models being scanned.
      for (std::tie(vi, vi_end) = vertices(masterGraph); vi != vi_end; ++vi)
      {
        if (masterGraph[*vi]->isEnabled() and masterGraph[*vi]->modelComboAllowed(modelList))
        {
          for (const str& model : modelList)
          {
            masterGraph[*vi]->notifyOfModel(model);
            masterGraph[*vi]->setStatus(FunctorStatus::Available);
          }
        }
      }

      // Activate those backend functors that match one of the models being scanned.
      for (const str& model : modelList)
      {
        for (functor* f : boundCore->getBackendFunctors())
        {
          // Activate if the backend vertex permits the model and has not been (severely) disabled by the backend system
          if ( f->isEnabled() and f->modelAllowed(model) )
          {
            f->setStatus(FunctorStatus::Available);
          }
        }
      }
      already_run = true;
    }

    /// Set up printer object
    /// (i.e. give it the list of functors that need printing)
    void DependencyResolver::initialisePrinter()
    {
      // Send the state of the "print_unitcube" flag to the printer
      boundPrinter->set_printUnitcube(print_unitcube);

      std::vector<int> functors_to_print;
      graph_traits<MasterGraphType>::vertex_iterator vi, vi_end;
      //IndexMap index = get(vertex_index, masterGraph); // Now done in the constructor
      //Err does that make sense? There is nothing in masterGraph at that point surely... maybe put this back.
      //Ok well it does seem to work in the constructor, not sure why though...

      for (std::tie(vi, vi_end) = vertices(masterGraph); vi != vi_end; ++vi)
      {
        // Inform the active functors of the vertex ID that the masterGraph has assigned to them
        // (so that later on they can pass this to the printer object to identify themselves)
        //masterGraph[*vi]->setVertexID(index[*vi]); // Ugh cannot do this, needs to be consistent with get_param_id
        std::string label = masterGraph[*vi]->label();
        masterGraph[*vi]->setVertexID(Printers::get_param_id(label));
        // Same for timing output ID, but get ID number from printer system
        std::string timing_label = masterGraph[*vi]->timingLabel();
        masterGraph[*vi]->setTimingVertexID(Printers::get_param_id(timing_label));

        // Check for non-void type and whether functor is active (after the dependency resolution) to print only active, printable functors.
        // TODO: this doesn't currently check for non-void type; that is done at the time of printing in calcObsLike.
        if( masterGraph[*vi]->requiresPrinting() and masterGraph[*vi]->isActive() )
        {
          functors_to_print.push_back(index[*vi]); // TODO: Probably obsolete
          boundPrinter->addToPrintList(label); // Needed mainly by postprocessor.
          // Trigger a dummy print call for all printable functors. This is used by some printers
          // to set up buffers for each of these output streams.
          //logger() << LogTags::dependency_resolver << "Triggering dummy print for functor '"<<masterGraph[*vi]->capability()<<"' ("<<masterGraph[*vi]->type()<<")..." << EOM;

          //masterGraph[*vi]->print(boundPrinter,-1);
        }
      }

      // Force-reset the printer to erase the dummy calls
      // (but don't do this if we are in resume mode!)
      //if(not boundCore->resume) boundPrinter->reset(true);
      //boundPrinter->reset(true); // Actually *do* do it in resume mode as well. Printers should only reset new data, not destroy old data.

      // sent vector of ID's of functors to be printed to printer.
      // (if we want to only print functor output sometimes, and dynamically
      // switch this on and off, we'll have to rethink the strategy here a
      // little... for now if the print function of a functor does not get
      // called, it is up to the printer how it deals with the missing result.
      // Similarly for extra results, i.e. from any functors not in this
      // initial list, whose "requiresPrinting" flag later gets set to 'true'
      // somehow.)
      boundPrinter->initialise(functors_to_print); // TODO: Probably obsolete
    }

    std::vector<std::pair<VertexID,bool>> DependencyResolver::closestCandidateForModel(std::vector<std::pair<VertexID,bool>> candidates)
    {
      // In case of doubt (and if not explicitely disabled in the ini-file), prefer functors
      // that are more specifically tailored for the model being scanned. Do not consider functors
      // that are accessible via INTERPRET_AS_X links, as these are all considered to be equally 'far'
      // from the model being scanned, with the 'distance' being one step further than the most distant
      // ancestor.

      // Work up the model ancestry one step at a time, and stop as soon as one or more valid model-specific functors is
      // found at a given level in the hierarchy.
      std::vector<std::pair<VertexID,bool>> newCandidates;
      std::set<str> s = boundClaw->get_activemodels();
      std::vector<str> parentModelList(s.begin(), s.end());
      while (newCandidates.size() == 0 and not parentModelList.empty())
      {
        for (str& model : parentModelList)
        {
          // Test each vertex candidate to see if it has been explicitly set up to work with the model
          for (const auto& candidate : candidates)
          {
            if (masterGraph[candidate.first]->modelExplicitlyAllowed(model)) newCandidates.push_back({candidate.first, true});
          }
          // Step up a level in the model hierarchy for this model.
          model = boundClaw->get_parent(model);
        }
        parentModelList.erase(std::remove(parentModelList.begin(), parentModelList.end(), "none"), parentModelList.end());
      }
      if (newCandidates.size() != 0)
        return newCandidates;
      else
        return candidates;
    }

    /// Collect ini options
    Options DependencyResolver::collectIniOptions(const VertexID & vertex)
    {
      functor* f = masterGraph[vertex];
      YAML::Node nodes;

      #ifdef DEPRES_DEBUG
        cout << "Searching options for " << f->capability() << endl;
      #endif

      for (const ModuleRule* rule : f->getMatchedModuleRules())
      {
        #ifdef DEPRES_DEBUG
          cout << "Getting option from: " << rule->capability << " " << rule->type << endl;
        #endif
        // Option is a new addition to collector node
        for (const auto& opt : rule->options)
        {
          if (not nodes[opt.first.as<std::string>()])
          {
            #ifdef DEPRES_DEBUG
              cout << opt.first.as<std::string>() << ": " << opt.second << endl;
            #endif
            nodes[opt.first.as<std::string>()] = opt.second;
          }
          else // Option already exists in collector node
          {
            // Throw an error if the existing value differs from the new value
            if (nodes[opt.first.as<std::string>()] != opt.second)
            {
              str errmsg = str("ERROR! Multiple option values for key: ") + opt.first.as<str>();
              dependency_resolver_error().raise(LOCAL_INFO, errmsg);
            }
          }
        }
      }
      return Options(nodes);
    }

    /// Collect sub-capabilities
    Options DependencyResolver::collectSubCaps(const VertexID& v)
    {
      functor* f = masterGraph[v];
      YAML::Node nodes;

      #ifdef DEPRES_DEBUG
        cout << "Searching for subcaps of " << f->capability() << endl;
      #endif

      // Iterate over all ObsLikes entries that match this functor
      for (const Observable* obslike : f->getMatchedObservables())
      {
        // Select only those entries that actually have subcaps
        if (not obslike->subcaps.IsNull())
        {
          #ifdef DEPRES_DEBUG
            cout << "Found subcaps for " << f->capability() << " " << f->type() << " " << f->origin() << ":" << endl;
          #endif
          // The user has given just a single entry as a subcap
          if (obslike->subcaps.IsScalar())
          {
            str key = obslike->subcaps.as<str>();
            if (nodes[key]) dependency_resolver_error().raise(LOCAL_INFO,"Duplicate sub-capability for " + key + ".");
            nodes[key] = YAML::Node();
          }
          // The user has passed a simple list of subcaps
          else if (obslike->subcaps.IsSequence())
          {
            for (const auto& subcap : obslike->subcaps)
            {
              if (not subcap.IsScalar())
               dependency_resolver_error().raise(LOCAL_INFO,"Attempt to pass map using sequence syntax for subcaps of "+obslike->capability+".");
              str key = subcap.as<str>();
              if (nodes[key]) dependency_resolver_error().raise(LOCAL_INFO,"Duplicate sub-capability for " + key + ".");
              nodes[key] = YAML::Node();
            }
          }
          // The user has passed some more complicated subcap structure than just a list of strings
          else if (obslike->subcaps.IsMap())
          {
            for (const auto& subcap : obslike->subcaps)
            {
              str key = subcap.first.as<str>();
              if (nodes[key]) dependency_resolver_error().raise(LOCAL_INFO,"Duplicate sub-capability for " + key + ".");
              nodes[key] = subcap.second.as<YAML::Node>();
            }
          }
          #ifdef DEPRES_DEBUG
            cout << nodes << endl;
          #endif
        }
      }
      return Options(nodes);
    }

    /// Helper function to update vertex candidate lists in resolveDependencyFromRules
    void DependencyResolver::updateCandidates(bool match, const VertexID& v, int i,
                                              std::vector<std::pair<VertexID, bool>>& allowed,
                                              std::vector<std::pair<VertexID, bool>>& disabled)
    {
      if (match)
      {
        // Add the vertex to the active list of vertex candidates if
        //   a) vertex is not disabled in any way;
        //   b) we only want the list of backends, and the vertex comes from an ini function;
        //   c) we only want the list of backends, and the vertex comes from a function that relies on classes from a disabled backend.
        // Otherwise, the vertex would have been fine except that it is disabled, so save it for printing in diagnostic messages.
        bool vertex_allowed = masterGraph[v]->isAvailable();
        if (!vertex_allowed)
        {
          FunctorStatus status = masterGraph[v]->status();
          vertex_allowed = boundCore->show_backends && (status == FunctorStatus::Classes_missing || status == FunctorStatus::Backend_missing);
        }
        allowed[i] = {v, vertex_allowed};
        disabled[i] = {v, not vertex_allowed};
      }
      else
      {
        allowed[i] = {v, false};
        disabled[i] = {v, false};
      }
    }


    /// Resolve dependencies by matching capability, type pair of input queue entry, ensuring consistency with all obslike entries and subjugate rules.
    /// As non-subjugate rules have global applicability, all (strong) instances are assumed to have already been applied before this function is called.
    std::vector<VertexID> DependencyResolver::resolveDependencyFromRules(const QueueEntry& entry, const std::vector<VertexID>& vertexCandidates)
    {
      // Candidate vertices after applying rules
      std::vector<std::pair<VertexID, bool>> allowedVertexCandidates(vertexCandidates.size());
      std::vector<std::pair<VertexID, bool>> disabledVertexCandidates(vertexCandidates.size());

      // If the dependency to be resolved comes from the ObsLike section, apply the conditions found in its ObsLike entry.
      if (entry.obslike != NULL)
      {
        // Iterate over all candidates
        #pragma omp parallel for
        for (unsigned int i = 0; i < vertexCandidates.size(); ++i)
        {
          const VertexID& v = vertexCandidates[i];
          // Require match to entry.quantity, and forbid self-resolution
          bool match = (v != entry.toVertex and entry.obslike->matches(masterGraph[v], *boundTEs));
          updateCandidates(match, v, i, allowedVertexCandidates, disabledVertexCandidates);
        }
      }
      else
      {
        // If this dependency does not come from an ObsLike entry, make a temporary rule to filter
        // vertexCandidates down to only those that match the passed quantity. This rule has the format
        // if:
        //   module: any
        // then:
        //   capability: quantity.first
        //   type: quantity.second
        ModuleRule dep_rule;
        dep_rule.has_if = dep_rule.if_module = dep_rule.has_then = dep_rule.then_capability = dep_rule.then_type = true;
        dep_rule.module = "any";
        dep_rule.capability = entry.quantity.first;
        dep_rule.type = entry.quantity.second;
        // Don't let functors log this rule when it is matched, as it is only a temporary rule.
        dep_rule.log_matches = false;

        // Iterate over all candidates
        #pragma omp parallel for
        for (unsigned int i = 0; i < vertexCandidates.size(); ++i)
        {
          const VertexID& v = vertexCandidates[i];
          // Require match to quantity, and forbid self-resolution
          bool match = (v != entry.toVertex and dep_rule.allows(masterGraph[v], *boundTEs));
          updateCandidates(match, v, i, allowedVertexCandidates, disabledVertexCandidates);
        }
      }
      Utils::masked_erase(allowedVertexCandidates);
      Utils::masked_erase(disabledVertexCandidates);

      // Bail now if we are already down to zero candidates.
      if (allowedVertexCandidates.size() == 0)
      {
        std::ostringstream errmsg;
        errmsg << "No candidates found while trying to resolve:" << endl;
        errmsg << printQuantityToBeResolved(entry) << endl;
        if (disabledVertexCandidates.size() != 0)
        {
          errmsg << "\nNote that potentially viable candidates exist that have been disabled:\n"
                 << printGenericFunctorList(disabledVertexCandidates)
                 << endl
          << "Status flags:" << endl
          << " 0: This function is not compatible with any model you are scanning." << endl
          << "-3: This function requires a BOSSed class that is missing. The " << endl
          << "    backend that provides the class is missing (most likely), the " << endl
          << "    class is missing from the backend, or the factory functions" << endl
          << "    for this class have not been BOSSed and loaded correctly." << endl;
        }
        errmsg << "Please check your yaml file for typos, and make sure that the" << endl
        << "models you are scanning are compatible with at least one function" << endl
        << "that provides this capability (they may all have been deactivated" << endl
        << "due to having ALLOW_MODELS declarations that are" << endl
        << "incompatible with the models selected for scanning)." << endl;
        dependency_resolver_error().raise(LOCAL_INFO,errmsg.str());
      }

      logger() << LogTags::dependency_resolver;
      logger() << "List of candidate vertices:" << endl;
      logger() << printGenericFunctorList(allowedVertexCandidates) << EOM;

      // Apply any conditions imposed by subjugate rules and function chains.
      // Note that it is not possible to write a subjugate rule nor a functionChain
      // that constrains the identity of the functor used to resolve an ObsLike entry.
      if (entry.obslike == NULL)
      {
        #pragma omp parallel for
        for (unsigned int i = 0; i < allowedVertexCandidates.size(); ++i)
        {
          const VertexID& v = allowedVertexCandidates[i].first;
          bool& allowed = allowedVertexCandidates[i].second;

          // Iterate over all obslikes that matched the entry.toVertex.
          for (const Observable* match : masterGraph[entry.toVertex]->getMatchedObservables())
          {
            // Allow only candidates that are allowed by all subjugate module rules of all rules that matched the entry.toVertex
            allowed = allowed and match->dependencies_allow(masterGraph[v], *boundTEs);
          }

          // Iterate over all obslikes in order to check if they have functionChain entries that are relevant.
          for (const Observable& obs : obslikes)
          {
            // Check that the candidate is consistent with any functionChain included in the obslike entry.
            allowed = allowed and obs.function_chain_allows(masterGraph[v], masterGraph[entry.toVertex], *boundTEs);
          }

          // Iterate over all rules that matched the entry.toVertex.
          for (const ModuleRule* match : masterGraph[entry.toVertex]->getMatchedModuleRules())
          {
            // Allow only candidates that match all subjugate module rules of all rules that matched the entry.toVertex
            allowed = allowed and match->dependencies_allow(masterGraph[v], *boundTEs);
          }

          // Iterate over all rules in order to check if they have functionChain entries that are relevant.
          for (const ModuleRule& rule : module_rules)
          {
            // Check that the candidate is consistent with any functionChain included in the obslike entry.
            allowed = allowed and rule.function_chain_allows(masterGraph[v], masterGraph[entry.toVertex], *boundTEs);
          }
        }
        Utils::masked_erase(allowedVertexCandidates);
      }

      logger() << LogTags::dependency_resolver;
      logger() << "List of candidate vertices after applying subjugate rules and functionChain constraints:" << endl;
      logger() << printGenericFunctorList(allowedVertexCandidates) << EOM;

      // Apply model-specific filter
      unsigned int remaining = allowedVertexCandidates.size();
      if (remaining > 1 and boundIniFile->getValueOrDef<bool>(true, "dependency_resolution", "prefer_model_specific_functions"))
      {
        allowedVertexCandidates = closestCandidateForModel(allowedVertexCandidates);
        if (allowedVertexCandidates.size() < remaining)
        {
          logger() << "A subset of vertex candidates is tailor-made for the scanned model." << endl;
          logger() << "After using this as an additional constraint, the remaining vertices are:" << endl;
          logger() << printGenericFunctorList(allowedVertexCandidates) << EOM;
        }
      }

      // As a last resort, try applying weak rules (both subjugate and non-subjugate).
      if (allowedVertexCandidates.size() > 1 and entry.obslike == NULL)
      {
        logger() << "Applying rules declared as '!weak' in final attempt to resolve dependency." << endl;

        #pragma omp parallel for
        for (unsigned int i = 0; i < allowedVertexCandidates.size(); ++i)
        {
          const VertexID& v = allowedVertexCandidates[i].first;
          bool& allowed = allowedVertexCandidates[i].second;

          // Filter out vertices that fail any non-subjugate (undirected) rules.
          for (const ModuleRule& rule : module_rules)
          {
            if (rule.weakrule and allowed) allowed = rule.allows(masterGraph[v], *boundTEs, false);
          }

          // Iterate over all obslikes that matched the entry.toVertex.
          for (const Observable* match : masterGraph[entry.toVertex]->getMatchedObservables())
          {
            // Allow only candidates that are allowed by all subjugate module rules of all rules that matched the entry.toVertex
            allowed = allowed and match->dependencies_allow(masterGraph[v], *boundTEs, false);
            // Check that the candidate is consistent with any functionChain included in the obslike entry.
            allowed = allowed and match->function_chain_allows(masterGraph[v], masterGraph[entry.toVertex], *boundTEs);
          }

          // Iterate over all rules that matched the entry.toVertex.
          for (const ModuleRule* match : masterGraph[entry.toVertex]->getMatchedModuleRules())
          {
            // Allow only candidates that match all subjugate module rules of all rules that matched the entry.toVertex
            if (match->weakrule and allowed) allowed = match->dependencies_allow(masterGraph[v], *boundTEs, false);
            // Check that the candidate is consistent with any functionChain included in the rule.
            if (match->weakrule and allowed) allowed = match->function_chain_allows(masterGraph[v], masterGraph[entry.toVertex], *boundTEs, false);
          }
        }
        Utils::masked_erase(allowedVertexCandidates);

        logger() << "Candidate vertices after applying weak rules:" << endl;
        logger() << printGenericFunctorList(allowedVertexCandidates) << EOM;
      }

      // Nothing left?
      if (allowedVertexCandidates.size() == 0)
      {
        str errmsg = "None of the vertex candidates for";
        errmsg += "\n" + printQuantityToBeResolved(entry);
        errmsg += "\nfulfills all rules in the YAML file.";
        errmsg += "\nPlease check your YAML file for contradictory rules, and";
        errmsg += "\nensure that you have built GAMBIT in the first place with";
        errmsg += "\nall of the components that you are trying to use.";
        dependency_resolver_error().raise(LOCAL_INFO,errmsg);
      }

      // At least one left.
      logger() << "Candidate vertices that fulfill all rules:" << endl;
      logger() << printGenericFunctorList(allowedVertexCandidates) << EOM;

      // Is more than one result OK?
      if (entry.obslike != NULL and entry.obslike->include_all)
      {
        std::vector<VertexID> retv;
        for (auto v : allowedVertexCandidates) retv.push_back(v.first);
        return retv;
      }

      // First remaining candidate.
      const VertexID v = allowedVertexCandidates[0].first;

      // Did we get down to one vertex?
      if (allowedVertexCandidates.size() == 1) return std::vector<VertexID>(1, v);

      // Failure - still more than one left.
      const functor* f = masterGraph[v];
      str errmsg = "Unfortunately, the dependency resolution for";
      errmsg += "\n" + printQuantityToBeResolved(entry);
      errmsg += "\nis still ambiguous.\n";
      errmsg += "\nThe candidate vertices are:\n";
      errmsg += printGenericFunctorList(allowedVertexCandidates) +"\n";
      if (entry.obslike != NULL) 
      {
        errmsg += "\nNote that because the failed resolution is for an ObsLike entry,\n";
        errmsg += "you could accept all of the above candidates by using !include_all.\n";
        
      }
      errmsg += "\nSee logger output for details on the attempted (but failed) dependency resolution.\n";
      errmsg += "\nAn entry in the ObsLike or Rules section of your YAML file that would";
      errmsg += "\ne.g. select the first of the above candidates could read ";
      if (entry.obslike == NULL)
      {
        errmsg += "as a targeted rule:\n";
        errmsg += "\n  - if:";
        errmsg += "\n      capability: "+masterGraph[entry.toVertex]->capability();
        errmsg += "\n      function: "+masterGraph[entry.toVertex]->name();
        errmsg += "\n    then:";
        errmsg += "\n      dependencies:";
        errmsg += "\n        - if:";
        errmsg += "\n            capability: " +f->capability();
        errmsg += "\n          then:";
        errmsg += "\n            module: " +f->origin();
        errmsg += "\n            function: " +f->name() +"\n\nor ";
        errmsg += "as an untargeted rule:\n";
      }
      errmsg += "\n  - if:";
      errmsg += "\n      capability: "+f->capability();
      errmsg += "\n      type: "+Utils::quote_if_contains_commas(f->type());
      errmsg += "\n    then:";
      errmsg += "\n      module: " +f->origin();
      errmsg += "\n      function: "+f->name() + "\n";
      dependency_resolver_error().raise(LOCAL_INFO,errmsg);

      return std::vector<VertexID>(1, 0);
    }


    /// Set up dependency tree
    void DependencyResolver::generateTree(std::queue<QueueEntry>& resolutionQueue)
    {
      OutputVertex outVertex;
      std::vector<VertexID> fromVertices;
      EdgeID edge;
      bool ok;

      logger() << LogTags::dependency_resolver << endl;
      logger() << "################################################" << endl;
      logger() << "#         Starting dependency resolution       #" << endl;
      logger() << "#                                              #" << endl;
      logger() << "# format: Capability (Type) [Function, Module] #" << endl;
      logger() << "################################################" << EOM;

      // Print something to stdout as well
      #ifdef DEPRES_DEBUG
        std::cout << "Resolving dependency graph..." << std::endl;
      #endif

      // Read ini entries
      print_timing   = boundIniFile->getValueOrDef<bool>(false, "print_timing_data");
      print_unitcube = boundIniFile->getValueOrDef<bool>(false, "print_unitcube");

      if ( print_timing   ) logger() << "Will output timing information for all functors (via printer system)" << EOM;
      if ( print_unitcube ) logger() << "Printing of unitCubeParameters will be enabled." << EOM;

      // Generate a list of module functors able to participate in dependency resolution.
      std::vector<VertexID> vertexCandidates;
      #pragma omp parallel for
      for (auto vi = vertices(masterGraph).first; vi != vertices(masterGraph).second; ++vi)
      {
        bool allowed = true;

        for (const ModuleRule& rule : module_rules)
        {
          // Filter out vertices that fail any non-subjugate (undirected) rules.
          allowed = allowed and rule.allows(masterGraph[*vi], *boundTEs);
        }

        if (allowed)
        {
          #pragma omp critical (vertexCandidates)
          vertexCandidates.push_back(*vi);
        }
      }

      // Generate a list of backend functors able to participate in dependency resolution.
      std::vector<functor*> backendFunctorCandidates;
      #pragma omp parallel for
      for(functor* f: boundCore->getBackendFunctors())
      {
        bool allowed = true;

        for (const BackendRule& rule : backend_rules)
        {
          // Filter out backend functors that fail any non-subjugate (undirected) rules.
          allowed = allowed and rule.allows(f, *boundTEs, "any");
        }

        if (allowed)
        {
          #pragma omp critical (vertexCandidates)
          backendFunctorCandidates.push_back(f);
        }
      }


      //
      // Main loop: repeat until dependency queue is empty
      //

      while (not resolutionQueue.empty())
      {

        // Retrieve dependency of interest
        const QueueEntry& entry = resolutionQueue.front();

        // Print information about required quantity and dependent vertex
        logger() << LogTags::dependency_resolver;
        logger() << "Resolving ";
        logger() << printQuantityToBeResolved(entry) << endl << endl;

        // Extra verbose output to terminal
        #ifdef VERBOSE_DEP_RES
          std::cout << "Resolving dependency "<<printQuantityToBeResolved(entry)<<"..." <<std::endl;
        #endif

        // Figure out how to resolve dependency
        fromVertices = resolveDependencyFromRules(entry, vertexCandidates);

        // If there is more than one result, log that fact.
        if (fromVertices.size() > 1)
        {
          logger() << LogTags::dependency_resolver;
          logger() << "Due to include_all tag, " << printQuantityToBeResolved(entry);
          logger() << " will be resolved by " << fromVertices.size() << " functions." << endl;
        }

        // Step through all results
        for (VertexID fromVertex : fromVertices)
        {

          // Print user info.
          logger() << LogTags::dependency_resolver;
          logger() << printQuantityToBeResolved(entry) << "resolved by: [";
          logger() << (*masterGraph[fromVertex]).name() << ", ";
          logger() << (*masterGraph[fromVertex]).origin() << "]" << endl;

          // Extra verbose output to terminal
          #ifdef VERBOSE_DEP_RES
            std::cout << "   ...resolved by ["<<(*masterGraph[fromVertex]).name()<<", "<<(*masterGraph[fromVertex]).origin()<<"]"<<std::endl;
          #endif

          // Check if we wanted to output this observable to the printer system.
          if (entry.obslike != NULL) masterGraph[fromVertex]->setPrintRequirement(entry.printme);
          // Check if the flag to output timing data is set
          if(print_timing) masterGraph[fromVertex]->setTimingPrintRequirement(true);

          // Apply resolved dependency to masterGraph and functors
          if (entry.obslike == NULL)
          {
            // Resolve the dependency at the functor level.
            // Default is to resolve dependency at functor level for entry.toVertex.
            if (entry.dependency_type != LOOP_MANAGER_DEPENDENCY)
            {
              (*masterGraph[entry.toVertex]).resolveDependency(masterGraph[fromVertex]);
            }
            // In case the fromVertex is a loop manager, store nested function
            // temporarily in loopManagerMap (they have to be sorted later)
            else
            {
              // Check whether fromVertex is allowed to manage loops
              if (not masterGraph[fromVertex]->canBeLoopManager())
              {
                str errmsg = "Trying to resolve dependency on loop manager with\n"
                 "module function that is not declared as loop manager.\n"
                 + printGenericFunctorList(initVector<functor*>(masterGraph[fromVertex]));
                dependency_resolver_error().raise(LOCAL_INFO,errmsg);
              }
              std::set<VertexID> v;
              if (loopManagerMap.count(fromVertex) == 1)
              {
                v = loopManagerMap[fromVertex];
              }
              v.insert(entry.toVertex);
              loopManagerMap[fromVertex] = v;
              (*masterGraph[entry.toVertex]).resolveLoopManager(masterGraph[fromVertex]);

              // Take any dependencies of loop-managed vertices that have already been resolved,
              // and add them as "hidden" dependencies to this loop manager.
              if (edges_to_force_on_manager.find(entry.toVertex) != edges_to_force_on_manager.end())
              {
                for (auto it = edges_to_force_on_manager.at(entry.toVertex).begin();
                     it != edges_to_force_on_manager.at(entry.toVertex).end(); ++it)
                {
                  logger() << "Dynamically adding dependency of " << masterGraph[fromVertex]->origin()
                           << "::" << masterGraph[fromVertex]->name() << " on "
                           << masterGraph[*it]->origin() << "::" << masterGraph[*it]->name() << endl;
                  std::tie(edge, ok) = add_edge(*it, fromVertex, masterGraph);
                }
              }
            }
            // Now save the resolved dependency into the masterGraph.
            std::tie(edge, ok) = add_edge(fromVertex, entry.toVertex, masterGraph);

            // In the case that entry.toVertex is a nested function, add fromVertex to
            // the edges of entry.toVertex's loop manager.
            str to_lmcap = (*masterGraph[entry.toVertex]).loopManagerCapability();
            str to_lmtype = (*masterGraph[entry.toVertex]).loopManagerType();
            str from_lmcap = (*masterGraph[fromVertex]).loopManagerCapability();
            str from_lmtype = (*masterGraph[fromVertex]).loopManagerType();
            bool is_same_lmcap = to_lmcap == from_lmcap;
            bool is_same_lmtype = to_lmtype == "any" or from_lmtype == "any" or to_lmtype == from_lmtype;
            if (to_lmcap != "none")
            {
              // This function runs nested.  Check if its loop manager has been resolved yet.
              if ((*masterGraph[entry.toVertex]).loopManagerName() == "none")
              {
                // entry.toVertex's loop manager has not yet been determined.
                // Add the edge to the list to deal with when the loop manager dependency is resolved,
                // as long as entry.toVertex and fromVertex cannot end up inside the same loop.
                if (!is_same_lmcap or !is_same_lmtype)
                {
                  if (edges_to_force_on_manager.find(entry.toVertex) == edges_to_force_on_manager.end())
                   edges_to_force_on_manager[entry.toVertex] = std::set<VertexID>();
                  edges_to_force_on_manager.at(entry.toVertex).insert(fromVertex);
                }
              }
              else
              {
                // entry.toVertex's loop manager has already been resolved.
                // If fromVertex is not the manager itself, and is not
                // itself a nested function that has the possibility to
                // end up in the same loop as entry.toVertex, then add
                // fromVertex as an edge of the manager.
                str name = (*masterGraph[entry.toVertex]).loopManagerName();
                str origin = (*masterGraph[entry.toVertex]).loopManagerOrigin();
                bool is_itself = (name == (*masterGraph[fromVertex]).name() and origin == (*masterGraph[fromVertex]).origin());
                if (!is_itself and (!is_same_lmcap or !is_same_lmtype) )
                {
                  // Hunt through the edges of entry.toVertex and find the one that corresponds to its loop manager.
                  graph_traits<MasterGraphType>::in_edge_iterator ibegin, iend;
                  std::tie(ibegin, iend) = in_edges(entry.toVertex, masterGraph);
                  if (ibegin != iend)
                  {
                    VertexID managerVertex;
                    for (; ibegin != iend; ++ibegin)
                    {
                      managerVertex = source(*ibegin, masterGraph);
                      if ((*masterGraph[managerVertex]).name() == name and
                          (*masterGraph[managerVertex]).origin() == origin) break;
                    }
                    logger() << "Dynamically adding dependency of " << (*masterGraph[managerVertex]).origin()
                             << "::" << (*masterGraph[managerVertex]).name() << " on "
                             << (*masterGraph[fromVertex]).origin() << "::" << (*masterGraph[fromVertex]).name() << endl;
                    std::tie(edge, ok) = add_edge(fromVertex, managerVertex, masterGraph);
                  }
                  else
                  {
                    dependency_resolver_error().raise(LOCAL_INFO, "entry.toVertex has no edges! So its loop manager hasn't been added as a dependency?!");
                  }
                }
              }
            }
          }
          else // if output vertex
          {
            outVertex.vertex = fromVertex;
            outVertex.purpose = entry.obslike->purpose;;
            outputVertices.push_back(outVertex);
            // Don't need subcaps during dry-run
            if (not boundCore->show_runorder)
            {
              Options mySubCaps = collectSubCaps(fromVertex);
              masterGraph[fromVertex]->notifyOfSubCaps(mySubCaps);
            }
          }

          // If fromVertex is new, activate it
          if ( !masterGraph[fromVertex]->isActive() )
          {
            logger() << LogTags::dependency_resolver << "Activate new module function" << endl;
            masterGraph[fromVertex]->setStatus(FunctorStatus::Active);
            resolveVertexBackend(fromVertex, backendFunctorCandidates);
            resolveVertexClassLoading(fromVertex);

            // Don't need options during dry-run, so skip this (just to simplify terminal output)
            if(not boundCore->show_runorder)
            {
              Options myOptions = collectIniOptions(fromVertex);
              masterGraph[fromVertex]->notifyOfIniOptions(myOptions);
            }
            // Fill parameter queue with dependencies of fromVertex
            fillResolutionQueue(resolutionQueue, fromVertex);
          }
        }

        // Done.
        logger() << EOM;
        resolutionQueue.pop();
      }
    }

    /// Put module function dependencies into the resolution queue
    void DependencyResolver::fillResolutionQueue(std::queue<QueueEntry>& resolutionQueue, VertexID vertex)
    {
      // Set the default printing flag for functors to pass to the resolutionQueue constructor.
      bool printme_default = false;

      // Tell the logger what the following messages are about.
      logger() << LogTags::dependency_resolver;

      // Digest capability of loop manager (if defined)
      str lmcap = masterGraph[vertex]->loopManagerCapability();
      str lmtype = masterGraph[vertex]->loopManagerType();
      if (lmcap != "none")
      {
        logger() << "Adding module function loop manager to resolution queue:" << endl;
        logger() << lmcap << " ()" << endl;
        resolutionQueue.push(QueueEntry(sspair(lmcap, lmtype), vertex, LOOP_MANAGER_DEPENDENCY, printme_default));
      }

      // Digest regular dependencies
      std::set<sspair> s = masterGraph[vertex]->dependencies();
      if (s.size() > 0) logger() << "Add dependencies of new module function to queue" << endl;
      for (const sspair& ss : s)
      {
        // If the loop manager requirement exists and is type-specific, it is a true depencency,
        // and thus appears in the output of functor.dependencies(). So, we need to take care
        // not to double-count it for entry into the resolutionQueue.
        if (lmcap == "none" or lmtype == "any" or lmcap != ss.first or lmtype != ss.second)
        {
          logger() << ss.first << " (" << ss.second << ")" << endl;
          resolutionQueue.push(QueueEntry(ss, vertex, NORMAL_DEPENDENCY, printme_default));
        }
      }

      // Tell the logger we're done here.
      logger() << EOM;
    }

    /// Boost lib topological sort
    std::list<VertexID> DependencyResolver::run_topological_sort()
    {
      std::list<VertexID> topo_order;
      topological_sort(masterGraph, front_inserter(topo_order));
      return topo_order;
    }

    /// Node-by-node backend resolution
    void DependencyResolver::resolveVertexBackend(VertexID vertex, const std::vector<functor*>& backendFunctorCandidates)
    {
      functor* solution;
      std::vector<functor*> previous_successes;
      std::set<str> remaining_groups;
      std::set<sspair> remaining_reqs;
      bool allow_deferral = true;

      // If there are no backend requirements, and thus nothing to do, return.
      if (masterGraph[vertex]->backendreqs().size() == 0) return;

      // Get started.
      logger() << LogTags::dependency_resolver << "Doing backend function resolution..." << EOM;

      // Collect the list of groups that the backend requirements of this vertex exist in.
      std::set<str> groups = masterGraph[vertex]->backendgroups();

      // Collect the list of orphan (i.e. groupless) backend requirements.
      std::set<sspair> orphan_reqs = masterGraph[vertex]->backendreqs("none");

      // Loop until no further backend resolutions are possible, or no more are required.
      while ( not ( groups.empty() and orphan_reqs.empty() ) )
      {

        // Loop over all groups, including the null group (group="none").
        for (const str& group : groups)
        {
          // Switch depending on whether this is a real group or not.
          if (group == "none")
          {
            // Loop over all the orphan requirements.
            for (const sspair& req : orphan_reqs)
            {
              logger() << LogTags::dependency_resolver;
              logger() << "Resolving ungrouped requirement " << req.first;
              logger() << " (" << req.second << ")..." << EOM;

              // Find a backend function that fulfills the backend requirement.
              std::set<sspair> reqsubset;
              reqsubset.insert(req);
              solution = solveRequirement(reqsubset,vertex,backendFunctorCandidates,previous_successes,allow_deferral);

              // Check if a valid solution has been returned
              if (solution != NULL)
              {
                // It has, so resolve the backend requirement with that function and add it to the list of successful resolutions.
                resolveRequirement(solution,vertex);
                previous_successes.push_back(solution);

                // If req is in remaining_reqs, remove it
                if (remaining_reqs.find(req) != remaining_reqs.end())
                {
                  remaining_reqs.erase(req);
                }
              }
              else // No valid solution found, but deferral has been suggested - so defer resolution of this group until later.
              {
                remaining_reqs.insert(req);
                logger() << LogTags::dependency_resolver;
                logger() << "Resolution of ungrouped requirement " << req.first;
                logger() << " (" << req.second << ") deferred until later." << EOM;
              }
            }
            if (not remaining_reqs.empty()) remaining_groups.insert(group);
          }
          else
          {
            logger() << LogTags::dependency_resolver;
            logger() << "Resolving from group " << group << "..." << EOM;

            // Collect the list of backend requirements in this group.
            std::set<sspair> reqs = masterGraph[vertex]->backendreqs(group);

            // Find a backend function that fulfills one of the backend requirements in the group.
            solution = solveRequirement(reqs,vertex,backendFunctorCandidates,previous_successes,allow_deferral,group);

            // Check if a valid solution has been returned
            if (solution != NULL)
            {
              // It has, so resolve the backend requirement with that function and add it to the list of successful resolutions.
              resolveRequirement(solution,vertex);
              previous_successes.push_back(solution);
            }
            else // No valid solution found, but deferral has been suggested - so defer resolution of this group until later.
            {
              remaining_groups.insert(group);
              logger() << LogTags::dependency_resolver;
              logger() << "Resolution from group " << group;
              logger() << "deferred until later." << EOM;
            }
          }
        }

        // If there has been no improvement this round, turn off deferral and make the next round the last attempt.
        if (orphan_reqs == remaining_reqs and groups == remaining_groups)
        {
          allow_deferral = false;
        }
        else // Otherwise try again to resolve the remaining groups and orphan requirements, now that some others are known.
        {
          orphan_reqs = remaining_reqs;
          groups = remaining_groups;
          remaining_reqs.clear();
          remaining_groups.clear();
        }
      }
    }

    /// Find a backend function that matches any one of a vector of capability-type pairs,
    /// ensuring consistency with all subjugate backend rules. As non-subjugate rules have
    /// global applicability, all instances are assumed to have already been applied before
    /// this function is called.
    functor* DependencyResolver::solveRequirement(std::set<sspair> reqs, VertexID toVertex,
     const std::vector<functor*>& backendFunctorCandidates, std::vector<functor*> previous_successes,
     bool allow_deferral, str group_being_resolved)
    {
      // Candidate vertices after applying rules
      std::vector<std::pair<functor*, bool>> allowedBackendFunctorCandidates(backendFunctorCandidates.size());
      std::vector<std::pair<functor*, bool>> disabledBackendFunctorCandidates(backendFunctorCandidates.size());

      // Loop over all existing backend vertices, retaining only functors
      // that are available and fulfill the backend requirement.
      #pragma omp parallel for
      for (unsigned int i = 0; i < backendFunctorCandidates.size(); ++i)
      {
        functor* f = backendFunctorCandidates[i];
        bool allowed = false;

        // Look for a basic match to at least one backend requirement, taking into account type equivalency classes.
        for (const sspair& req : reqs)
        {
          // Make a temporary rule to filter down to only those that match the requirement. This rule has the format
          // if:
          //   group: group_being_resolved
          // then:
          //   capability: req.first
          //   type: req.second
          BackendRule req_rule;
          req_rule.has_if = req_rule.has_then = req_rule.if_group = req_rule.then_capability = req_rule.then_type = true;
          req_rule.group = group_being_resolved;
          req_rule.capability = req.first;
          req_rule.type = req.second;
          // Don't let functors log this rule when it is matched, as it is only a temporary rule.
          req_rule.log_matches = false;
          if (req_rule.allows(f, *boundTEs, group_being_resolved))
          {
            allowed = true;
            break;
          }
        }

        // Move on to the next candidate immediately if the current one doesn't even constitute a basic match to the requirement.
        if (not allowed) continue;

        // Continue to allow the backend vertex if it is available, or if we only want to show a list of backends.
        allowed = boundCore->show_backends or f->isAvailable();

        // Is the candidate permitted to fill a backend requirement of toVertex, given any specification of permitted
        // backends and permitted versions in the basic rollcall declaration of this requirement?
        if (allowed)
        {
          // First we create the backend-version pair for the backend vertex.
          sspair f_signature(f->origin(), f->version());
          // Next we create its semi-generic form, where any version is OK.
          sspair f_generic(f->origin(), "any");
          // Then we find the set of backend-version pairs that are permitted.
          std::set<sspair> permitted_bes = masterGraph[toVertex]->backendspermitted(f->quantity());

          // Now we see if any match.  First we test for generic matches, where any version of any backend is allowed.
          allowed = ( permitted_bes.empty()
           // Next we test for semi-generic matches, where the backend matches and any version of that backend is allowed.
           or std::find(permitted_bes.begin(), permitted_bes.end(), f_generic) != permitted_bes.end()
           // Finally we test for specific matches, where both the backend and version match what is allowed.
           or std::find(permitted_bes.begin(), permitted_bes.end(), f_signature) != permitted_bes.end() );
        }

        // Now we check if the candidate is compatible with all applicable subjugate backend rules.
        // Iterate over all observables that matched toVertex.
        for (const Observable* match : masterGraph[toVertex]->getMatchedObservables())
        {
          // Allow only candidates that match all subjugate backend rules of all observables that matched the entry.toVertex
          allowed = allowed and match->backend_reqs_allow(f, *boundTEs, group_being_resolved);
        }
        // Iterate over all module rules that matched toVertex.
        for (const ModuleRule* match : masterGraph[toVertex]->getMatchedModuleRules())
        {
          // Allow only candidates that match all subjugate backend rules of all rules that matched the entry.toVertex
          allowed = allowed and match->backend_reqs_allow(f, *boundTEs, group_being_resolved);
        }

        // Next, we purge all candidates that conflict with a backend-matching rule given in the rollcall declaration.
        if (allowed)
        {
          // Retrieve the tags of the candidate.
          std::set<str> tags = masterGraph[toVertex]->backendreq_tags(f->quantity());
          // Loop over the tags
          for (const str& tag : tags)
          {
            // Find out which other backend requirements exhibiting this tag must be filled from the same backend as the req this candidate would fill.
            std::set<sspair> must_match = masterGraph[toVertex]->forcematchingbackend(tag);
            // Set up a flag to keep track of whether any of the other backend reqs have already been filled.
            bool others_filled = false;
            // Set up a string to keep track of which backend the other backend reqs have been filled from (if any).
            str common_backend_and_version;
            // Loop over the other backend reqs.
            for (const sspair& bereq_must_match : must_match)
            {
              // Set up a flag to indicate if the other backend req in question has been filled yet.
              bool other_filled = false;
              // Set up a string to keep track of which backend the other backend req in question has been filled from (if any).
              str filled_from;
              // Loop over the backend functors that have successfully filled backend reqs already for this funcition
              for (const functor* previous_success : previous_successes)
              {
                // Check if the current previous success was of the same backend requirement as the
                // current one of the backend requirements (bereq_must_match) that must be filled from the same backend as the current candidate (f).
                if (previous_success->quantity() == bereq_must_match)
                {
                  // Note that bereq_must_match (the current backend req that must be filled from the same backend as the current candidate) has indeed been filled, by previous_success
                  other_filled = true;
                  // Note which backend bereq_must_match has been filled from (i.e. where does previous_success come from?)
                  filled_from = previous_success->origin() + " v" + previous_success->version();
                  break;
                }
              }
              // If the other req has been filled, update the tracker of whether any of the reqs linked to this flag have been filled,
              // and compare the filling backend to the one used to fill any other reqs associated with this tag.
              if (other_filled)
              {
                others_filled = true;
                if (common_backend_and_version.empty()) common_backend_and_version = filled_from; // Save the filling backend
                if (filled_from != common_backend_and_version) // Something buggy has happened and the rule is already broken(!)
                {
                  str errmsg = "A backend-matching rule has been violated!";
                  errmsg  += "\nFound whilst checking which backends have been used"
                             "\nto fill requirements with tag " + tag + " in function "
                             "\n" + masterGraph[toVertex]->name() + " of " + masterGraph[toVertex]->origin() + "."
                             "\nOne requirement was filled from " + common_backend_and_version + ", "
                             "\nwhereas another was filled from " + filled_from + "."
                             "\nThis should not happen and is probably a bug in GAMBIT.";
                  dependency_resolver_error().raise(LOCAL_INFO,errmsg);
                }
              }
            }
            // Keep this candidate if it comes from the same backend as those already filled, or if none of the others are filled yet.
            allowed = (not others_filled or common_backend_and_version == f->origin() + " v" + f->version());
            if (not allowed) break;
          }
        }

        // Finally, save the verdict.
        allowedBackendFunctorCandidates[i] = {f, allowed};
        disabledBackendFunctorCandidates[i] = {f, not allowed};
      }
      Utils::masked_erase(allowedBackendFunctorCandidates);
      Utils::masked_erase(disabledBackendFunctorCandidates);

      // Only print the status flags -5 or -6 if any of the disabled vertices has it
      bool printMathematicaStatus = false;
      bool printPythonStatus = false;
      for (const auto& c : disabledBackendFunctorCandidates)
      {
        if (c.first->status() == FunctorStatus::Mathematica_missing) printMathematicaStatus = true;
        if (c.first->status() == FunctorStatus::Pybind_missing) printPythonStatus = true;
      }

      // No candidates? Death.
      if (allowedBackendFunctorCandidates.size() == 0)
      {
        std::ostringstream errmsg;
        errmsg
          << "Found no candidates for backend requirements of "
          << masterGraph[toVertex]->origin() << "::" << masterGraph[toVertex]->name() << ":\n"
          << reqs << "\nfrom group: " << group_being_resolved;
        if (disabledBackendFunctorCandidates.size() != 0)
        {
          errmsg << "\nNote that viable candidates exist but have been disabled:\n"
                 <<     printGenericFunctorList(disabledBackendFunctorCandidates, true)
                 << endl
                 << "Status flags:" << endl
                 << " 1: This function is available, but the backend and/or its version are " << endl
                 << "    not compatible with all relevant rollcall declarations and YAML rules." << endl
                 << " 0: This function is not compatible with any model you are scanning." << endl
                 << "-1: The backend that provides this function is missing." << endl
                 << "-2: The backend is present, but function is absent or broken." << endl;
         if(printMathematicaStatus)
            errmsg << "-5: The backend requires Mathematica, but Mathematica is absent." << endl;
         if(printPythonStatus)
            errmsg << "-6: The backend requires Python, but pybind11 is absent." << endl;
          errmsg << endl
                 << "Make sure to check your YAML file, especially the rules" << endl
                 << "pertaining to backends."  << endl
                 << endl
                 << "Please also check that all shared objects exist for the"  << endl
                 << "necessary backends, and that they contain all the"  << endl
                 << "necessary functions required for this scan.  You may"  << endl
                 << "check the status of different backends by running"  << endl
                 << "  ./gambit backends"  << endl
                 << "You may also wish to check the specified search paths for each" << endl
                 << "backend shared library in "  << endl;
          if (Backends::backendInfo().custom_locations_exist())
          {
            errmsg << "  " << Backends::backendInfo().backend_locations()  << endl << "and"  << endl;
          }
          errmsg << "  " << Backends::backendInfo().default_backend_locations()  << endl;
        }
        dependency_resolver_error().raise(LOCAL_INFO,errmsg.str());
      }

      // Still more than one candidate...
      if (allowedBackendFunctorCandidates.size() > 1)
      {
        // Check whether any of the remaining candidates is subject to a backend-matching rule,
        // and might therefore be uniquely chosen over the other(s) if resolution for this req is attempted again, after
        // another of the reqs subject to the same rule is resolved.
        bool rule_exists = false;
        // Loop over the remaining candidates.
        for (const auto& c : allowedBackendFunctorCandidates)
        {
          // Retrieve the tags of the candidate.
          std::set<str> tags = masterGraph[toVertex]->backendreq_tags(c.first->quantity());
          // Loop over the tags
          for (const str& tag : tags)
          {
            // Find if there is a backend-matching rule associated with this tag.
            rule_exists = not masterGraph[toVertex]->forcematchingbackend(tag).empty();
            if (rule_exists) break;
          }
          if (rule_exists) break;
        }

        // If deferral is allowed and appears to be potentially useful, defer resolution until later.
        if (allow_deferral and rule_exists)
        {
          return NULL;
        }

        // If not, we have just one more trick up our sleeves... use the models scanned to narrow things down.
        if (boundIniFile->getValueOrDef<bool>(true, "dependency_resolution", "prefer_model_specific_functions"))
        {
          // Prefer backend functors that are more specifically tailored for the model being scanned. Do not
          // consider backend functors that are accessible via INTERPRET_AS_X links, as these are all considered
          // to be equally 'far' from the model being scanned, with the 'distance' being one step further than
          // the most distant ancestor.
          std::vector<std::pair<functor*, bool>> newCandidates;
          std::set<str> s = boundClaw->get_activemodels();
          std::vector<str> parentModelList(s.begin(), s.end());
          while (newCandidates.size() == 0 and not parentModelList.empty())
          {
            for (str& model : parentModelList)
            {
              // Test each vertex candidate to see if it has been explicitly set up to work with model
              for (const auto& c : allowedBackendFunctorCandidates)
              {
                if (c.first->modelExplicitlyAllowed(model)) newCandidates.push_back({c.first, true});
              }
              // Step up a level in the model hierarchy for this model.
              model = boundClaw->get_parent(model);
            }
            parentModelList.erase(std::remove(parentModelList.begin(), parentModelList.end(), "none"), parentModelList.end());
          }
          if (newCandidates.size() != 0) allowedBackendFunctorCandidates = newCandidates;
        }

        // Still more than one candidate, so the game is up (unless we only want the list of required backends).
        if (allowedBackendFunctorCandidates.size() > 1 and not boundCore->show_backends)
        {
          str errmsg = "Found too many candidates for backend requirement ";
          if (reqs.size() == 1) errmsg += reqs.begin()->first + " (" + reqs.begin()->second + ")";
          else errmsg += "group " + group_being_resolved;
          errmsg += " of module function " + masterGraph[toVertex]->origin() + "::" + masterGraph[toVertex]->name()
           + "\nViable candidates are:\n" + printGenericFunctorList(allowedBackendFunctorCandidates, true);
          errmsg += "\nIf you don't need all the above backends, you can resolve the ambiguity simply by";
          errmsg += "\nuninstalling the backends that you don't want to use.";
          errmsg += "\n\nAlternatively, you can add an entry in your YAML file that selects which backend";
          errmsg += "\nthe module function " + masterGraph[toVertex]->origin() + "::" + masterGraph[toVertex]->name() + " should use. A YAML entry in the Rules section";
          errmsg += "\nthat selects e.g. the first candidate above could read\n";
          errmsg += "\n  - if";
          errmsg += "\n      capability: "+masterGraph[toVertex]->capability();
          errmsg += "\n      function: "+masterGraph[toVertex]->name();
          errmsg += "\n    then:";
          errmsg += "\n      backends:";
          errmsg += "\n        - if:";
          errmsg += "\n            capability: "+allowedBackendFunctorCandidates.at(0).first->capability();
          errmsg += "\n            type: "+Utils::quote_if_contains_commas(allowedBackendFunctorCandidates.at(0).first->type());
          errmsg += "\n          then:";
          errmsg += "\n            backend: "+allowedBackendFunctorCandidates.at(0).first->origin();
          errmsg += "\n            version: "+allowedBackendFunctorCandidates.at(0).first->version() + "\n";
          dependency_resolver_error().raise(LOCAL_INFO,errmsg);
        }
      }

      // Store the resolved backend requirements
      std::vector<sspair> resolvedBackends;
      for (const auto& c : allowedBackendFunctorCandidates)
      {
        sspair backend(c.first->origin(), c.first->version());
        resolvedBackends.push_back(backend);
      }

      bool found = false;
      for (const auto& br : backendsRequired)
      {
        found = true;
        for (auto backend : resolvedBackends)
        {
          if (std::find(br.begin(), br.end(), backend) == br.end())
            found = false;
        }
        if (found) break;
      }
      if (not found)
      {
        backendsRequired.push_back(resolvedBackends);
      }

      // Just one candidate.  Jackpot.
      return allowedBackendFunctorCandidates[0].first;
    }

    /// Resolve a backend requirement of a specific module function using a specific backend function.
    void DependencyResolver::resolveRequirement(functor* func, VertexID vertex)
    {
      masterGraph[vertex]->resolveBackendReq(func);
      logger() << LogTags::dependency_resolver;
      logger() << "Resolved by: [" << func->name() << ", ";
      logger() << func->origin() << " (" << func->version() << ")]";
      logger() << EOM;
    }

    /// Retrieve used or unused rules
    template<typename RuleT>
    std::set<const RuleT*> getUsedOrUnusedRules(bool find_used, const std::vector<RuleT>& rules, const MasterGraphType& masterGraph)
    {
      std::set<const RuleT*> returnRules;
      for(const auto& rule : rules)
      {
        #ifdef DEPRES_DEBUG
          std::cout << "Triggering for " << (find_used ? "used" : "unused") << " rules." << std::endl;
          std::cout << "Checking rule with capability " << rule.capability << std::endl;
        #endif
        graph_traits<MasterGraphType>::vertex_iterator vi, vi_end;
        bool unused = true;
        for (std::tie(vi, vi_end) = vertices(masterGraph); vi != vi_end; ++vi)
        {
          // Check only for enabled functors
          if (masterGraph[*vi]->isActive())
          {
            const std::set<const RuleT*>& matched = masterGraph[*vi]->getMatchedRules<const RuleT>();
            bool found = (std::find_if(matched.begin(), matched.end(), [&](const RuleT* r){ return r==&rule; } ) != matched.end());
            if (found)
            {
              unused = false;
              break;
            }
          }
        }
        if (unused xor find_used) returnRules.insert(&rule);
      }
      return returnRules;
    }
    template<typename RuleT>
    std::set<const RuleT*> getUsedRules(const std::vector<RuleT>& rules, const MasterGraphType& masterGraph)
    {
      return getUsedOrUnusedRules(true, rules, masterGraph);
    }
    template<typename RuleT>
    std::set<const RuleT*> getUnusedRules(const std::vector<RuleT>& rules, const MasterGraphType& masterGraph)
    {
      return getUsedOrUnusedRules(false, rules, masterGraph);
    }



    /// Check for unused rules and options
    void DependencyResolver::checkForUnusedRules()
    {
      // Retrieve sets of used and unused module and backend rules
      std::set<const ModuleRule*> usedModuleRules = getUsedRules(module_rules, masterGraph);
      std::set<const ModuleRule*> unusedModuleRules = getUnusedRules(module_rules, masterGraph);
      std::set<const BackendRule*> usedBackendRules = getUsedRules(backend_rules, masterGraph);
      std::set<const BackendRule*> unusedBackendRules = getUnusedRules(backend_rules, masterGraph);

      // Remove any unused module rules that are also backend rules, and have been used as such.
      while(true)
      {
        auto duplicate_rule = std::find_if(unusedModuleRules.begin(),
                                           unusedModuleRules.end(),
                                           [&](const ModuleRule* moduleRule)
                                           {
                                             for (const auto& backendRule : usedBackendRules)
                                             {
                                               if (moduleRule->yaml == backendRule->yaml) return true;
                                             }
                                             return false;
                                           });
        if (duplicate_rule == unusedModuleRules.end()) break;
        unusedModuleRules.erase(duplicate_rule);
      }

      // Remove any unused backend rules that are also module rules, and have been used as such.
      while(true)
      {
        auto duplicate_rule = std::find_if(unusedBackendRules.begin(),
                                           unusedBackendRules.end(),
                                           [&](const BackendRule* backendRule)
                                           {
                                             for (const auto& moduleRule : usedModuleRules)
                                             {
                                               if (moduleRule->yaml == backendRule->yaml) return true;
                                             }
                                             return false;
                                           });
        if (duplicate_rule == unusedBackendRules.end()) break;
        unusedBackendRules.erase(duplicate_rule);
      }

      // If any unused rules remain, trigger an error/warning.
      if(unusedModuleRules.size() > 0 or unusedBackendRules.size() > 0)
      {
        std::ostringstream msg;
        msg << "The following rules and options are not used in the current scan:" << endl;
        if (unusedModuleRules.size() > 0) msg << endl << "Module rules:" << endl;
        for (const ModuleRule* rule : unusedModuleRules) msg << endl << rule->yaml << endl;
        if (unusedBackendRules.size() > 0) msg << endl << "Backend rules:" << endl;
        for (const BackendRule* rule : unusedBackendRules) msg << endl << rule->yaml << endl;
        if (boundIniFile->getValueOrDef<bool>(true, "dependency_resolution", "unused_rule_is_an_error"))
          dependency_resolver_error().raise(LOCAL_INFO,msg.str());
        else dependency_resolver_warning().raise(LOCAL_INFO,msg.str());
      }
    }

    /// Construct metadata information from used observables, rules and options
    /// Note: No keys can be identical (or differing only by capitalisation)
    ///       to those printed in the main file, otherwise the sqlite printer fails
    map_str_str DependencyResolver::getMetadata()
    {
      map_str_str metadata;

      // Gambit version
      metadata["GAMBIT"] = gambit_version();

      // Date
      auto now = std::chrono::system_clock::now();
      auto in_time_t = std::chrono::system_clock::to_time_t(now);

      std::stringstream ss;
      ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M");
      metadata["Date"] =  ss.str();

      // scanID
      if (boundIniFile->getValueOrDef<bool>(true, "print_scanID"))
      {
        ss.str("");
        ss << scanID;
        metadata["Scan_ID"] = ss.str();
      }

      // Parameters
      YAML::Node parametersNode = boundIniFile->getParametersNode();
      Options(parametersNode).toMap(metadata, "Parameters");

      // Priors
      YAML::Node priorsNode = boundIniFile->getPriorsNode();
      Options(priorsNode).toMap(metadata, "Priors");

      // Printer
      YAML::Node printerNode = boundIniFile->getPrinterNode();
      Options(printerNode).toMap(metadata, "Printer");

      // Scanners
      YAML::Node scanNode = boundIniFile->getScannerNode();
      str scanner = scanNode["use_scanner"].as<str>();
      metadata["Scanner::scanner"] = scanner;
      for(const auto& entry : scanNode)
      {
        const str key = entry.first.as<str>();
        if(key == "scanners") Options(scanNode["scanners"][scanner]).toMap(metadata, "Scanner::options");
        else if(key != "use_scanner") Options(entry).toMap(metadata, "Scanner::" + key);
      }

      // ObsLikes
      for (const Observable& obslike : obslikes)
      {
        std::stringstream key;
        key << "ObsLikes::" << &obslike;
        Options(obslike.yaml).toMap(metadata, key.str());
      }

      // Used rules and options
      for (const ModuleRule* rule : getUsedRules(module_rules, masterGraph))
      {
        std::stringstream key;
        key << "Rule::" << rule->yaml;
        Options(rule->yaml).toMap(metadata, key.str());
      }
      for (const BackendRule* rule : getUsedRules(backend_rules, masterGraph))
      {
        std::stringstream key;
        key << "Rule::" << rule->yaml;
        Options(rule->yaml).toMap(metadata, key.str());
      }

      // Logger
      YAML::Node logNode = boundIniFile->getLoggerNode();
      Options(logNode).toMap(metadata,"Logger");

      // KeyValues
      YAML::Node keyvalue = boundIniFile->getKeyValuePairNode();
      Options(keyvalue).toMap(metadata,"KeyValue");

      // YAML file
      ss.str("");
      ss << boundIniFile->getYAMLNode();
      metadata["YAML"] = ss.str();

      return metadata;

    }

    // Resolve a dependency on backend classes
    void DependencyResolver::resolveVertexClassLoading(VertexID vertex)
    {
      // If there are no backend class loading requirements, and thus nothing to do, return.
      if (masterGraph[vertex]->backendclassloading().size() == 0) return;

      // If the backend is not present, this vertex has already been disabled, so from now just assume it hasn't
      // Unless the list of required backends is requested, in which case it is enabled, but it won't run a scan, so no worries

      // Add to the logger
      logger() << LogTags::dependency_resolver << "Doing backend class loading resolution..." << EOM;

      // Add the backends to list of required backends
      std::vector<sspair> resolvedBackends;
      for(auto backend : masterGraph[vertex]->backendclassloading())
        resolvedBackends.push_back(backend);

      bool found = false;
      for(const auto& br : backendsRequired)
      {
        found = true;
        for(auto backend : resolvedBackends)
        {
          if(std::find(br.begin(), br.end(), backend) == br.end())
            found = false;
        }
        if(found) break;
      }
      if(not found)
      {
        backendsRequired.push_back(resolvedBackends);
      }

    }

    // Set the Scan ID
    void DependencyResolver::set_scanID()
    {
      // Get the scanID from the yaml node.
      scanID = boundIniFile->getValueOrDef<int>(-1, "scanID");

      // If scanID is supplied by user, use that
      if (scanID != -1)
      {
        return;
      }
      else
      {
        const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds> (now.time_since_epoch()) - std::chrono::duration_cast<std::chrono::seconds> (now.time_since_epoch());
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%H%M%S");
        ss << ms.count();
        ss >> scanID;
      }
    }

    // Get BibTeX citation keys for backends, modules, etc
    void DependencyResolver::getCitationKeys()
    {
      // First add the necessary citation keys to use GAMBIT
      citationKeys.insert(citationKeys.end(), gambit_citation_keys.begin(), gambit_citation_keys.end());

      // Get the keys for the required backends
      for(auto backend : backendsRequired)
      {
        str bibkey = "";

        // Run over references of loaded backends
        for(auto beref : boundCore->getBackendCitationKeys())
        {
          str origin = beref.first.first;
          str version = beref.first.second;
          if (backend[0].first == origin and backend[0].second == version)
          {
            bibkey = beref.second;
            if (bibkey != "" and bibkey != "REFERENCE")
            {
              logger() << LogTags::dependency_resolver << "Found bibkey for backend " << origin << " version " << version << ": " << bibkey << EOM;
              BibTeX::addCitationKey(citationKeys, bibkey);
            }
          }
        }
        if (bibkey == "" or bibkey == "REFERENCE")
        {
          std::ostringstream errmsg;
          errmsg << "Missing reference for backend " << backend[0].first << "(" << backend[0].second << ")." << endl;
          errmsg << "Please add the bibkey to the frontend header, and full bibtex entry to ";
          errmsg << boundIniFile->getValueOrDef<str>("config/bibtex_entries.bib", "dependecy_resolution", "bibtex_file_location") << "." << endl;
          dependency_resolver_error().raise(LOCAL_INFO,errmsg.str());
        }
      }

      // Now look over activated vertices in the mastergraph and add any references to module, module functions, etc
      for (const VertexID& vertex : getObsLikeOrder())
      {
        std::set<VertexID> parents;
        getParentVertices(vertex, masterGraph, parents);
        parents.insert(vertex);
        for (const VertexID& vertex2 : parents)
        {

          // Add citation key for used modules
          for(const auto& key : boundCore->getModuleCitationKeys())
          {
            if(key.first == masterGraph[vertex2]->origin())
            {
              BibTeX::addCitationKey(citationKeys, key.second);
            }
          }

          // Add citation key for specific module functions
          if(masterGraph[vertex2]->citationKey() != "")
          {
            BibTeX::addCitationKey(citationKeys, masterGraph[vertex2]->citationKey());
          }

        }

      }
    }

  }

}
