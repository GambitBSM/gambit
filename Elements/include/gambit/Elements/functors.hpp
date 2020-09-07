//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functor class definitions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Apr-July, Dec
///  \date 2014 Jan, Mar-May, Sep
///  \date 2015 Jan
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///   \date 2013 Apr, Nov
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date 2013 May, June, July
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 July, Sep
///  \date 2014 Jan
///
///  \author Lars A. Dal
///          (l.a.dal@fys.uio.no)
///  \date 2015 Jan
///
///  *********************************************


#ifndef __functors_hpp__
#define __functors_hpp__

#include <map>
#include <set>
#include <vector>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <omp.h>

#include "gambit/Utils/util_types.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Utils/model_parameters.hpp"
#include "gambit/Logs/logger.hpp"
#include "gambit/Logs/logmaster.hpp" // Need full declaration of LogMaster class

/// Decay rate of average runtime estimate [(number of functor evaluations)^-1]
#define FUNCTORS_FADE_RATE 0.01
/// Minimum invaldiation rate (should be 0<...<<1)
#define FUNCTORS_BASE_INVALIDATION_RATE 0.01
/// Initial runtime estimate (s)
#define FUNCTORS_RUNTIME_INIT 0.000001

namespace Gambit
{

  /// Forward declaration of Printers::BasePrinter class for use in print functions.
  namespace Printers { class BasePrinter; }

  /// Forward declaration of Models::ModelFunctorClaw class for use in constructors.
  namespace Models { class ModelFunctorClaw; }

  /// Type redefinition to get around icc compiler bugs.
  template <typename TYPE, typename... ARGS>
  struct variadic_ptr { typedef TYPE(*type)(ARGS..., ...); };

  /// Forward declare helper friend functions
  class module_functor_common;
  namespace FunctorHelp {
    // void check_for_shutdown_signal(module_functor_common&);
    // bool emergency_shutdown_begun();
    void entering_multithreaded_region(module_functor_common&);
    void leaving_multithreaded_region(module_functor_common&);
  }

  // ======================== Base Functor =====================================

  /// Function wrapper (functor) base class
  class functor
  {

    public:

      /// Constructor
      functor(str, str, str, str, Models::ModelFunctorClaw&);

      //// Destructor
      virtual ~functor() {}

      /// Virtual calculate(); needs to be redefined in daughters.
      virtual void calculate();


      // It may be safer to have some of the following things accessible
      // only to the likelihood wrapper class and/or dependency resolver, i.e. so they cannot be used
      // from within module functions

      /// Interfaces for runtime optimization
      /// Need to be implemented by daughters
      /// @{
      virtual double getRuntimeAverage();
      virtual double getInvalidationRate();
      virtual void setFadeRate(double);
      virtual void notifyOfInvalidation(const str&);
      virtual void reset();
      /// @}

      /// Reset-then-recalculate method
      virtual void reset_and_calculate();

      /// Setter for status: -6 = required external tool absent (pybind11)
      ///                    -5 = required external tool absent (Mathematica)
      ///                    -4 = required backend absent (backend ini functions)
      ///                    -3 = required classes absent
      ///                    -2 = function absent
      ///                    -1 = origin absent
      ///                     0 = model incompatibility (default)
      ///                     1 = available
      ///                     2 = active
      void setStatus(int);
      /// Set the inUse flag (must be overridden in derived class to have any effect).
      virtual void setInUse(bool){};
      /// Setter for purpose (relevant only for next-to-output functors)
      void setPurpose(str);
      /// Setter for vertex ID (used in printer system)
      void setVertexID(int);
      /// Set ID for timing 'vertex' (used in printer system)
      void setTimingVertexID(int);
      /// Getter for the wrapped function's name
      str name() const;
      /// Getter for the wrapped function's reported capability
      str capability() const;
      /// Getter for the wrapped function's reported return type
      str type() const;
      /// Getter for the wrapped function's origin (module or backend name)
      str origin() const;
      /// Getter for the version of the wrapped function's origin (module or backend)
      str version() const;
      /// Getter for the 'safe' incarnation of the version of the wrapped function's origin (module or backend)
      virtual str safe_version() const;
      /// Getter for the wrapped function current status:
      ///                    -4 = required backend absent (backend ini functions)
      ///                    -3 = required classes absent
      ///                    -2 = function absent
      ///                    -1 = origin absent
      ///                     0 = model incompatibility (default)
      ///                     1 = available
      ///                     2 = active
      int status() const;
      /// Getter for the  overall quantity provided by the wrapped function (capability-type pair)
      sspair quantity() const;
      /// Getter for purpose (relevant for output nodes, aka helper structures for the dep. resolution)
      str purpose() const;
      /// Getter for vertex ID
      int vertexID() const;
      /// Getter for timing vertex ID
      int timingVertexID() const;
      /// Getter for string label
      str label() const;
      /// Getter for the printer timing label
      str timingLabel() const;
      /// Getter indicating if the wrapped function's result should to be printed
      virtual bool requiresPrinting() const;

      /// Getter indicating if the timing data for this function's execution should be printed
      virtual bool requiresTimingPrinting() const;

      /// Setter for indicating if the wrapped function's result should to be printed
      virtual void setPrintRequirement(bool);

      /// Setter for indicating if the timing data for this function's execution should be printed
      virtual void setTimingPrintRequirement(bool);

      /// Set the ordered list of pointers to other functors that should run nested in a loop managed by this one
      virtual void setNestedList (std::vector<functor*>&);

      /// Set the iteration number in a loop in which this functor runs
      virtual void setIteration (long long);

      /// Getter for revealing whether this is permitted to be a manager functor
      virtual bool canBeLoopManager();

      /// Getter for revealing the required capability of the wrapped function's loop manager
      virtual str loopManagerCapability();
      /// Getter for revealing the required type of the wrapped function's loop manager
      virtual str loopManagerType();
      /// Getter for revealing the name of the wrapped function's assigned loop manager
      virtual str loopManagerName();
      /// Getter for revealing the module of the wrapped function's assigned loop manager
      virtual str loopManagerOrigin();

      /// Tell the functor that the loop it manages should break now.
      virtual void breakLoop();

      /// Getter for listing currently activated dependencies
      virtual std::set<sspair> dependencies();
      /// Getter for listing backend requirement groups
      virtual std::set<str> backendgroups();
      /// Getter for listing all backend requirements
      virtual std::set<sspair> backendreqs();
      /// Getter for listing backend requirements from a specific group
      virtual std::set<sspair> backendreqs(str);
      /// Getter for listing permitted backends
      virtual std::set<sspair> backendspermitted(sspair);
      /// Getter for listing tags associated with backend requirements
      virtual std::set<str> backendreq_tags(sspair);
      /// Getter for listing backend requirements that must be resolved from the same backend
      virtual std::set<sspair> forcematchingbackend(str);

      /// Getter for listing backend-specific conditional dependencies (4-string version)
      virtual std::set<sspair> backend_conditional_dependencies (str, str, str, str);

      /// Getter for backend-specific conditional dependencies (3-string version)
      virtual std::set<sspair> backend_conditional_dependencies (str req, str type, str be);

      /// Getter for backend-specific conditional dependencies (backend functor pointer version)
      virtual std::set<sspair> backend_conditional_dependencies (functor*);

      /// Getter for listing model-specific conditional dependencies
      virtual std::set<sspair> model_conditional_dependencies (str);

      /// Getter for listing model-specific conditional backend requirements
      virtual std::set<sspair> model_conditional_backend_reqs (str);

      /// Resolve a dependency using a pointer to another functor object
      virtual void resolveDependency (functor*);

      /// Set this functor's loop manager (if it has one)
      virtual void resolveLoopManager (functor*);

      /// Resolve a backend requirement using a pointer to another functor object
      virtual void resolveBackendReq (functor*);

      /// Notify the functor that a certain model is being scanned, so that it can activate itself accordingly.
      virtual void notifyOfModel(str);

      /// Notify the functor that it is being used to fill a dependency of another functor
      virtual void notifyOfDependee(functor*);

      /// Indicate to the functor which backends are actually loaded and working
      virtual void notifyOfBackends(std::map<str, std::set<str> >);

      #ifndef NO_PRINTERS
        /// Printer function
        virtual void print(Printers::BasePrinter* printer, const int pointID, int thread_num);

        /// Printer function (no-thread-index short-circuit)
        virtual void print(Printers::BasePrinter* printer, const int pointID);
      #endif

      /// Retrieve the previously saved exception generated when this functor invalidated the current point in model space.
      virtual invalid_point_exception* retrieve_invalid_point_exception();

      /// Notify the functor about an instance of the options class that contains
      /// information from its corresponding ini-file entry in the auxiliaries or
      /// observables section.
      void notifyOfIniOptions(const Options&);

      /// Set an option for the functor directly (for use in standalone executables).
      template<typename TYPE>
      void setOption(const str& key, const TYPE val)
      {
        myOptions.setValue<str,TYPE>(key, val);
      }

      /// Return a safe pointer to the options that this functor is supposed to run with (e.g. from the ini file).
      safe_ptr<Options> getOptions();

      /// Notify the functor about an instance of the options class that contains sub-capability information
      void notifyOfSubCaps(const Options&);

      /// Set a sub-capability (subcap)for the functor directly (for use in standalone executables).
      template<typename TYPE>
      void setSubCap(const str& key, const TYPE val)
      {
        mySubCaps.setValue<str,TYPE>(key, val);
      }

      /// Return a safe pointer to the subcaps that this functor realises it is supposed to facilitate downstream calculation of.
      safe_ptr<Options> getSubCaps();

      /// Return a safe pointer to the vector of all capability,type pairs of functors arranged downstream of this one in the dependency tree.
      safe_ptr<std::set<sspair>> getDependees();

      /// Test whether the functor is allowed to be used with all models
      bool allModelsAllowed();

      /// Test whether the functor is always allowed (either explicitly or implicitly) to be used with a given model
      bool modelAllowed(str model);

      /// Test whether the functor is explictly always allowed to be used with a given model
      bool modelExplicitlyAllowed(str model);

      /// Add a model to the internal list of models for which this functor is allowed to be used.
      void setAllowedModel(str model);

      /// Test whether the functor is allowed (either explicitly or implicitly) to be used with a given combination of models
      bool modelComboAllowed(std::set<str> combo);

      /// Test whether the functor has been explictly allowed to be used with a given combination of models
      bool modelComboExplicitlyAllowed(std::set<str> combo);

      /// Add a model group definition to the internal list of model groups.
      void setModelGroup(str group, str contents);

      /// Add a combination of model groups to the internal list of combinations for which this functor is allowed to be used.
      void setAllowedModelGroupCombo(str groups);

    protected:

      /// Internal storage of the function name.
      str myName;
      /// Internal storage of exactly what the function calculates.
      str myCapability;
      /// Internal storage of the type of what the function calculates.
      str myType;
      /// Internal storage of the name of the module or backend to which the function belongs.
      str myOrigin;
      /// Internal storage of the version of the module or backend to which the function belongs.
      str myVersion;
      /// Purpose of the function (relevant for output and next-to-output functors)
      str myPurpose;
      /// Bound model functor claw, for checking relationships between models
      const Models::ModelFunctorClaw* myClaw;

      /// String label, used to label functor results for printer system
      const str myLabel;
      /// String label, used to label functor timing data for printer system
      const str myTimingLabel;
      /// Status:
      ///                    -4 = required backend absent (backend ini functions)
      ///                    -3 = required classes absent
      ///                    -2 = function absent
      ///                    -1 = origin absent
      ///                     0 = model incompatibility (default)
      ///                     1 = available
      ///                     2 = active
      int myStatus;
      /// Internal storage of the vertex ID number used by the printer system to identify functors
      int myVertexID;
      /// ID assigned by printers to the timing data output stream
      int myTimingVertexID;
      /// Debug flag
      bool verbose;

      /// Internal storage of function options, as a YAML node
      Options myOptions;

      /// Internal storage of function sub-capabilities, as a YAML node
      Options mySubCaps;

      /// List of all capability,type pairs of functors downstream of this one in the dependency tree
      std::set<sspair> myDependees;

      /// List of allowed models
      std::set<str> allowedModels;

      /// List of allowed model group combinations
      std::set<std::set<str> > allowedGroupCombos;

      /// Map from model group names to group contents
      std::map<str, std::set<str> > modelGroups;

      /// Attempt to retrieve a dependency or model parameter that has not been resolved
      static void failBigTime(str method);

      /// Test if there is a model in the functor's allowedModels list as which this model can be interpreted
      inline bool allowed_parent_or_friend_exists(str model);

      /// Check that a model is actually part of a combination that is allowed to be used with this functor.
      inline bool in_allowed_combo(str model);

      /// Test whether any of the entries in a given model group is a valid interpretation of any members in a given combination
      inline bool contains_anything_interpretable_as_member_of(std::set<str> combo, str group);

      /// Work out whether a given combination of models and a model group have any elements in common
      inline bool has_common_elements(std::set<str> combo, str group);

      /// Try to find a parent or friend model in some user-supplied map from models to sspair vectors
      str find_friend_or_parent_model_in_map(str model, std::map< str, std::set<sspair> > karta);

      /// Reset functor for one thread only
      virtual void reset(int);

  };


  // ======================== Module Functors =====================================

  /// Functor derived class for module functions
  class module_functor_common : public functor
  {

    public:

      /// Constructor
      module_functor_common(str, str, str, str, Models::ModelFunctorClaw&);

      /// Destructor
      virtual ~module_functor_common();

      /// Getter for averaged runtime
      double getRuntimeAverage();

      /// Reset functor
      void reset();

      /// Tell the functor that it invalidated the current point in model space, pass a message explaining why, and throw an exception.
      void notifyOfInvalidation(const str&);

      /// Getter for invalidation rate
      double getInvalidationRate();

      /// Setter for the fade rate
      void setFadeRate(double);

      /// Setter for indicating if the timing data for this function's execution should be printed
      void setTimingPrintRequirement(bool);

      /// Getter indicating if the timing data for this function's execution should be printed
      bool requiresTimingPrinting() const;

      /// Indicate whether or not a known model is activated or not.
      bool getActiveModelFlag(str);

      /// Return a safe pointer to a string indicating which backend requirement has been activated for a given backend group.
      safe_ptr<str> getChosenReqFromGroup(str);

      /// Execute a single iteration in the loop managed by this functor.
      virtual void iterate(long long iteration);

      /// Initialise the array holding the current iteration(s) of this functor.
      virtual void init_myCurrentIteration_if_NULL();
      /// Setter for setting the iteration number in the loop in which this functor runs
      virtual void setIteration (long long iteration);
      /// Return a safe pointer to the iteration number in the loop in which this functor runs.
      virtual omp_safe_ptr<long long> iterationPtr();

      /// Setter for specifying whether this is permitted to be a manager functor, which runs other functors nested in a loop.
      virtual void setCanBeLoopManager (bool canManage);
      /// Getter for revealing whether this is permitted to be a manager functor
      virtual bool canBeLoopManager();

      /// Setter for specifying the capability required of a manager functor, if it is to run this functor nested in a loop.
      virtual void setLoopManagerCapType (str cap, str t);
      /// Getter for revealing the required capability of the wrapped function's loop manager
      virtual str loopManagerCapability();
      /// Getter for revealing the required type of the wrapped function's loop manager
      virtual str loopManagerType();
      /// Getter for revealing the name of the wrapped function's assigned loop manager
      virtual str loopManagerName();
      /// Getter for revealing the module of the wrapped function's assigned loop manager
      virtual str loopManagerOrigin();

      /// Tell the manager of the loop in which this functor runs that it is time to break the loop.
      virtual void breakLoopFromManagedFunctor();
      /// Return a safe pointer to the flag indicating that a loop managed by this functor should break now.
      virtual safe_ptr<bool> loopIsDone();
      /// Provide a way to reset the flag indicating that a loop managed by this functor should break.
      virtual void resetLoop();
      /// Tell the functor that the loop it manages should break now.
      virtual void breakLoop();

      /// Getter for listing currently activated dependencies
      virtual std::set<sspair> dependencies();
      /// Getter for listing backend requirement groups
      virtual std::set<str> backendgroups();
      /// Getter for listing all backend requirements
      virtual std::set<sspair> backendreqs();
      /// Getter for listing backend requirements from a specific group
      virtual std::set<sspair> backendreqs(str);
      /// Getter for listing permitted backends
      virtual std::set<sspair> backendspermitted(sspair quant);
      /// Getter for listing tags associated with backend requirements
      virtual std::set<str> backendreq_tags(sspair);
      /// Getter for listing backend requirements that must be resolved from the same backend
      virtual std::set<sspair> forcematchingbackend(str);

      /// Getter for listing backend-specific conditional dependencies (4-string version)
      virtual std::set<sspair> backend_conditional_dependencies (str req, str type, str be, str ver);

      /// Getter for backend-specific conditional dependencies (3-string version)
      virtual std::set<sspair> backend_conditional_dependencies (str req, str type, str be);

      /// Getter for backend-specific conditional dependencies (backend functor pointer version)
      virtual std::set<sspair> backend_conditional_dependencies (functor* be_functor);

      /// Getter for listing model-specific conditional dependencies
      virtual std::set<sspair> model_conditional_dependencies (str model);

      /// Getter for listing model-specific conditional backend requirements
      virtual std::set<sspair> model_conditional_backend_reqs (str model);

      /// Add and activate unconditional dependencies.
      void setDependency(str, str, void(*)(functor*, module_functor_common*), str purpose= "");

      /// Add conditional dependency-type pairs in advance of later conditions.
      void setConditionalDependency(str, str);

      /// Add a backend conditional dependency for multiple backend versions
      void setBackendConditionalDependency(str, str, str, str, void(*)(functor*, module_functor_common*));

      /// Add a backend conditional dependency for a single backend version
      void setBackendConditionalDependencySingular(str, str, str, str, void(*)(functor*, module_functor_common*));

      /// Add a model conditional dependency for multiple models
      void setModelConditionalDependency(str, str, void(*)(functor*, module_functor_common*));

      /// Add a model conditional dependency for a single model
      void setModelConditionalDependencySingular(str, str, void(*)(functor*, module_functor_common*));

      /// Add a rule for activating backend requirements according to the model being scanned.
      void makeBackendRuleForModel(str, str);

      /// Add an unconditional backend requirement
      /// The info gets updated later if this turns out to be contitional on a model.
      void setBackendReq(str, str, str, str, void(*)(functor*));

      /// Add a model conditional backend requirement for multiple models
      void setModelConditionalBackendReq(str model, str req, str type);

      /// Add a model conditional backend requirement for a single model
      void setModelConditionalBackendReqSingular(str model, str req, str type);

      /// Add a rule for dictating which backends can be used to fulfill which backend requirements.
      void makeBackendOptionRule(str, str);

      /// Add a single permitted backend version
      void setPermittedBackend(str req, str be, str ver);

      /// Add one or more rules for forcing backends reqs with the same tags to always be resolved from the same backend.
      void makeBackendMatchingRule(str tag);

      /// Add a rule indicating that classes from a given backend must be available
      void setRequiredClassloader(str, str, str);

      /// Indicate to the functor which backends are actually loaded and working
      void notifyOfBackends(std::map<str, std::set<str> >);

      /// Set the ordered list of pointers to other functors that should run nested in a loop managed by this one
      virtual void setNestedList (std::vector<functor*> &newNestedList);

      /// Resolve a dependency using a pointer to another functor object
      virtual void resolveDependency (functor* dep_functor);

      /// Set this functor's loop manager (if it has one)
      virtual void resolveLoopManager (functor*);

      /// Resolve a backend requirement using a pointer to another functor object
      virtual void resolveBackendReq (functor* be_functor);

      /// Notify the functor that a certain model is being scanned, so that it can activate its dependencies and backend reqs accordingly.
      virtual void notifyOfModel(str model);

      /// Notify the functor that another functor depends on it
      virtual void notifyOfDependee (functor*);

      /// Retrieve the previously saved exception generated when this functor invalidated the current point in model space.
      virtual invalid_point_exception* retrieve_invalid_point_exception();


    protected:

      /// Reset functor for one thread only
      void reset(int);

      /// Acknowledge that this functor invalidated the current point in model space.
      virtual void acknowledgeInvalidation(invalid_point_exception&, functor* f = NULL);

      /// Do pre-calculate timing things
      virtual void startTiming(int);

      /// Do post-calculate timing things
      virtual void finishTiming(int);

      /// Flag to select whether or not the timing data for this function's execution should be printed;
      bool myTimingPrintFlag;

      /// Initialise the memory of this functor.
      virtual void init_memory();

      /// Construct the list of known models only if it doesn't yet exist
      void fill_activeModelFlags();

      /// Retrieve full conditional dependency-type pair from conditional dependency only
      sspair retrieve_conditional_dep_type_pair(str);

      /// Beginning and end timing points
      std::chrono::time_point<std::chrono::system_clock> *start, *end;

      /// A flag indicating whether or not this functor has invalidated the current point
      bool point_exception_raised;

      /// An exception raised because this functor has invalidated the current point
      invalid_point_exception raised_point_exception;

      /// Averaged runtime in ns
      double runtime_average;

      /// Fade rate for average runtime
      double fadeRate;

      /// Probability that functors invalidates point in model parameter space
      double pInvalidation;

      /// Needs recalculating or not?
      bool* needs_recalculating;

      /// Has result already been sent to the printer?
      bool* already_printed;

      /// Has timing data already been sent to the printer?
      bool* already_printed_timing;

      /// Flag indicating whether this function can manage a loop over other functions
      bool iCanManageLoops;

      /// Flag indicating whether this function is ready to finish its loop (only relevant if iCanManageLoops = true)
      bool myLoopIsDone;

      /// Flag indicating whether this function can run nested in a loop over functions
      bool iRunNested;

      /// Capability of a function that mangages a loop that this function can run inside of.
      str myLoopManagerCapability;
      /// Capability of a function that mangages a loop that this function can run inside of.
      str myLoopManagerType;
      /// Pointer to the functor that mangages the loop that this function runs inside of.
      functor* myLoopManager;

      /// Vector of functors that have been set up to run nested within this one.
      std::vector<functor*> myNestedFunctorList;

      /// Pointer to counters for iterations of nested functor loop.
      long long* myCurrentIteration;

      /// Maximum number of OpenMP threads this MPI process is permitted to launch in total.
      const int globlMaxThreads;

      /// Internal list of backend groups that this functor's requirements fall into.
      std::set<str> myGroups;

      /// Map from groups to backend reqs, indicating which backend req has been activated for which backend group.
      std::map<str,str> chosenReqsFromGroups;

      /// Set of all backend requirement-type string pairs.
      std::set<sspair> myBackendReqs;

      /// Set of all backend requirement-type string pairs currently available for resolution.
      std::set<sspair> myResolvableBackendReqs;

      /// Set of backend requirement-type string pairs for specific backend groups
      std::map<str,std::set<sspair> > myGroupedBackendReqs;

      /// Vector of dependency-type string pairs
      std::set<sspair> myDependencies;

      /// Map of conditional dependencies to their types
      std::map<str,str> myConditionalDependencies;

      /// Map from (vector with 4 strings: backend req, type, backend, version) to (set of {conditional dependency-type} pairs)
      std::map< std::vector<str>, std::set<sspair> > myBackendConditionalDependencies;

      /// Map from models to (set of {conditional dependency-type} pairs)
      std::map< str, std::set<sspair> > myModelConditionalDependencies;

      /// Map from models to (set of {conditional backend requirement-type} pairs)
      std::map< str, std::set<sspair> > myModelConditionalBackendReqs;

      /// Map from known models to flags indicating if they are activated or not (known = allowed, in allowed groups or conditions for conditional dependencies)
      std::map<str, bool> activeModelFlags;

      /// Map from (dependency-type pairs) to (pointers to templated void functions
      /// that set dependency functor pointers)
      std::map<sspair, void(*)(functor*, module_functor_common*)> dependency_map;

      /// Map from (dependency-type pairs) to pointers to functors used to resolve them
      /// that set dependency functor pointers)
      std::map<sspair, functor*> dependency_functor_map;

      /// Map from backend requirements to their required types
      std::map<str, str> backendreq_types;

      /// Map from backend requirements to their designated groups
      std::map<sspair, str> backendreq_groups;

      /// Map from backend requirements to their rule tags
      std::map<sspair, std::set<str> > backendreq_tagmap;

      /// Map from (backend requirement-type pairs) to (pointers to templated void functions
      /// that set backend requirement functor pointers)
      std::map<sspair, void(*)(functor*)> backendreq_map;

      /// Map from (backend requirement-type pairs) to (set of permitted {backend-version} pairs)
      std::map< sspair, std::set<sspair> > permitted_map;

      /// Map from tags to sets of matching (backend requirement-type pairs) that are forced to use the same backend
      std::map< str, std::set<sspair> > myForcedMatches;

      /// Map from required classloading backends to their versions
      std::map< str, std::set<str> > required_classloading_backends;

      /// Vector of required backends currently missing
      std::vector<str> missing_backends;

      /// Internal timespec object
      timespec tp;

      /// Integer LogTag, for tagging log messages
      int myLogTag;

      /// Check if an appropriate LogTag for this functor is missing from the logging system.
      void check_missing_LogTag();

      /// While locked, prevent this function switching off threadsafe* emergency signal handling.
      /// *The emergency signal handling cannot be made completely threadsafe; it can still cause
      /// lockups and memory corruption if it occurs at an inopportune time. "soft" shutdown is
      /// always preferable.
      bool signal_mode_locked = true;
      /// @}

      /// Connectors to external helper functions (to decouple signal handling from this class)
      // friend void FunctorHelp::check_for_shutdown_signal(module_functor_common&);
      // friend bool FunctorHelp::emergency_shutdown_begun();
      friend void FunctorHelp::entering_multithreaded_region(module_functor_common&);
      friend void FunctorHelp::leaving_multithreaded_region(module_functor_common&);
      // void check_for_shutdown_signal(){ FunctorHelp::check_for_shutdown_signal(*this); }
      // bool emergency_shutdown_begun(){ return FunctorHelp::emergency_shutdown_begun(); }
      void entering_multithreaded_region(){ FunctorHelp::entering_multithreaded_region(*this); }
      void leaving_multithreaded_region(){ FunctorHelp::leaving_multithreaded_region(*this); }

  };


  /// Actual module functor type for all but TYPE=void
  template <typename TYPE>
  class module_functor : public module_functor_common
  {

    public:

      /// Constructor
      module_functor(void(*)(TYPE &), str, str, str, str, Models::ModelFunctorClaw&);

      /// Destructor
      virtual ~module_functor();

      /// Setter for indicating if the wrapped function's result should to be printed
      virtual void setPrintRequirement(bool flag);

      /// Getter indicating if the wrapped function's result should to be printed
      virtual bool requiresPrinting() const;

      /// Calculate method
      void calculate();

      /// Operation (return value)
      const TYPE& operator()(int index);

      /// Alternative to operation (returns a safe pointer to value)
      safe_ptr<TYPE> valuePtr();

      #ifndef NO_PRINTERS
        /// Printer function
        virtual void print(Printers::BasePrinter* printer, const int pointID, int index);

        /// Printer function (no-thread-index short-circuit)
        virtual void print(Printers::BasePrinter* printer, const int pointID);
      #endif


    protected:

      /// Internal storage of function pointer
      void (*myFunction)(TYPE &);

      /// Internal pointer to storage location of function value
      TYPE* myValue;

      /// Flag to select whether or not the results of this functor should be sent to the printer object.
      bool myPrintFlag;

      /// Initialise the memory of this functor.
      virtual void init_memory();

  };


  /// Actual module functor type for TYPE=void
  template <>
  class module_functor<void> : public module_functor_common
  {

    public:

      /// Constructor
      module_functor(void (*)(), str, str, str, str, Models::ModelFunctorClaw&);

      /// Destructor
      virtual ~module_functor() {}

      /// Calculate method
      void calculate();

      #ifndef NO_PRINTERS
        /// Blank print method
        virtual void print(Printers::BasePrinter*, const int, int);

        /// Blank print method
        virtual void print(Printers::BasePrinter*, const int);
      #endif

    protected:

      /// Internal storage of function pointer
      void (*myFunction)();

  };


  // ======================== Backend Functors =====================================

  /// Backend functor class for functions with result type TYPE and argumentlist ARGS
  template <typename PTR_TYPE, typename TYPE, typename... ARGS>
  class backend_functor_common : public functor
  {

    protected:

      /// Set the inUse flag.
      virtual void setInUse(bool);

      /// Type of the function pointer being encapsulated
      typedef PTR_TYPE funcPtrType;

      /// Internal storage of function pointer
      funcPtrType myFunction;

      /// Integer LogTag, for tagging log messages
      int myLogTag;

      /// Internal storage of the 'safe' version of the version (for use in namespaces, variable names, etc).
      str mySafeVersion;

      /// Flag indicating if this backend functor is actually in use in a given scan
      bool inUse;

    public:

      /// Constructor
      backend_functor_common (funcPtrType, str, str, str, str, str, str, Models::ModelFunctorClaw&);

      /// Destructor
      virtual ~backend_functor_common() {}

      /// Update the internal function pointer wrapped by the functor
      void updatePointer(funcPtrType);

      /// Hand out the internal function pointer wrapped by the functor
      funcPtrType handoutFunctionPointer();

      /// Hand out a safe pointer to this backend functor's inUse flag.
      safe_ptr<bool> inUsePtr();

      /// Getter for the 'safe' incarnation of the version of the wrapped function's origin (module or backend)
      virtual str safe_version() const;

  };


  /// Actual backend functor type
  template <typename PTR_TYPE, typename TYPE, typename... ARGS> class backend_functor;

  /// Template specialisation for non-variadic, non-void backend functions
  template <typename TYPE, typename... ARGS>
  class backend_functor<TYPE(*)(ARGS...), TYPE, ARGS...> : public backend_functor_common<TYPE(*)(ARGS...), TYPE, ARGS...>
  {

    public:

      /// Constructor
      backend_functor (TYPE(*)(ARGS...), str, str, str, str, str, str, Models::ModelFunctorClaw&);

      /// Destructor
      virtual ~backend_functor() {}

      /// Operation (execute function and return value)
      TYPE operator()(ARGS&&... args);

  };


  /// Template specialisation for non-variadic, void backend functions
  template <typename... ARGS>
  class backend_functor<void(*)(ARGS...), void, ARGS...> : public backend_functor_common<void(*)(ARGS...), void, ARGS...>
  {

    public:

      /// Constructor
      backend_functor (void (*)(ARGS...), str, str, str, str, str, str, Models::ModelFunctorClaw&);

      /// Destructor
      virtual ~backend_functor() {}

      /// Operation (execute function)
      void operator()(ARGS&&... args);

  };

  /// Template specialisation for variadic, non-void backend functions
  template <typename TYPE, typename... ARGS>
  class backend_functor<typename variadic_ptr<TYPE,ARGS...>::type, TYPE, ARGS...>
   : public backend_functor_common<typename variadic_ptr<TYPE,ARGS...>::type, TYPE, ARGS...>
  {

    public:

      /// Constructor
      backend_functor(typename variadic_ptr<TYPE,ARGS...>::type, str, str, str, str, str, str, Models::ModelFunctorClaw&);

      /// Destructor
      virtual ~backend_functor() {}

      /// Operation (execute function and return value)
      template <typename... VARARGS>
      TYPE operator()(VARARGS&&... varargs)
      {
        logger().entering_backend(this->myLogTag);
        TYPE tmp = this->myFunction(std::forward<VARARGS>(varargs)...);
        logger().leaving_backend();
        return tmp;
      }

  };

  /// Template specialisation for variadic void backend functions
  template <typename... ARGS>
  class backend_functor<typename variadic_ptr<void,ARGS...>::type, void, ARGS...>
   : public backend_functor_common<typename variadic_ptr<void,ARGS...>::type, void, ARGS...>
  {

    public:

      /// Constructor
      backend_functor(typename variadic_ptr<void,ARGS...>::type, str, str, str, str, str, str, Models::ModelFunctorClaw&);

      /// Destructor
      virtual ~backend_functor() {}

      /// Operation (execute function)
      template <typename... VARARGS>
      void operator()(VARARGS&&... varargs)
      {
        logger().entering_backend(this->myLogTag);
        this->myFunction(std::forward<VARARGS>(varargs)...);
        logger().leaving_backend();
      }

  };


  // ======================== Model Functors =====================================

  /// Functors specific to ModelParameters objects
  class model_functor : public module_functor<ModelParameters>
  {

    public:

      /// Constructor
      model_functor(void (*)(ModelParameters &), str, str, str, str, Models::ModelFunctorClaw&);

      /// Destructor
      virtual ~model_functor() {}

      /// Function for setting the model name for a ModelParameters object. Mainly for better error messages.
      void setModelName(str model_name);

      /// Function for adding a new parameter to the map inside the ModelParameters object
      void addParameter(str parname);

      /// Function for handing over parameter identities to another model_functor
      void donateParameters(model_functor &receiver);

  };


  /// Functors specific to primary ModelParameters objects
  ///
  /// These allow direct access to the functor contents via a raw pointer, so
  /// that the parameter values can be set (not allowed via safe pointers).
  class primary_model_functor : public model_functor
  {

    public:

      /// Constructor
      primary_model_functor(void (*)(ModelParameters &), str, str, str, str, Models::ModelFunctorClaw&);

      /// Destructor
      virtual ~primary_model_functor() {}

      /// Functor contents raw pointer "get" function
      /// Returns a raw pointer to myValue, so that the contents may be
      /// modified (intended for setting parameter values in primary
      /// ModelParameters objects)
      ModelParameters* getcontentsPtr();

  };

}

#endif /* defined(__functors_hpp__) */
