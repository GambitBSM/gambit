//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Macros for ColliderBit analyses.
///  These macros define an analysis language that
///  simplify writing analyses and avoid code
///  repetition.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2023 July, Aug
///
///  *********************************************

#pragma once

/// Min and max values of eta and pT
#define ETAMIN 0
#define PTMIN 0
#define ETAMAX DBL_MAX
#define PTMAX DBL_MAX

/// Add a cutflow the the list of cutflows
#define ADD_CUTFLOW(SR, ...)                                                      \
  _cutflows.addCutflow(SR, {"Preselection", ## __VA_ARGS__, "Final"});

/// Define a signal region by initialzing the counter and cutflow
#define DEFINE_SIGNAL_REGION(NAME, ...)                                           \
  _counters[NAME] = EventCounter(NAME);                                           \
  ADD_CUTFLOW(NAME, ## __VA_ARGS__)

/// Define multiple signal regions that share a common name and
/// only vary on sequential numbering
#define DEFINE_SIGNAL_REGIONS(NAME, N, ...)                                       \
  for(size_t i=1; i<=N; ++i)                                                      \
  {                                                                               \
    str basename(NAME);                                                           \
    str name = basename + std::to_string(i);                                      \
    DEFINE_SIGNAL_REGION(name, ## __VA_ARGS__)                                    \
  }

/// Define baseline objects with min pT and min eta
#define BASELINE_OBJECTS_5(TYPE, OBJECTS, NAME, MINPT, MINETA)                    \
  std::vector<const HEPUtils::TYPE*> NAME;                                        \
  for (const HEPUtils::TYPE* object : OBJECTS)                                    \
  {                                                                               \
    if (object->pT() > MINPT and                                                  \
        fabs(object->eta()) > MINETA)                                             \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline objects with min pT, min eta and selection efficiency
#define BASELINE_OBJECTS_6(TYPE, OBJECTS, NAME, MINPT, MINETA, EFF)               \
  std::vector<const HEPUtils::TYPE*> NAME;                                        \
  for (const HEPUtils::TYPE* object : OBJECTS)                                    \
  {                                                                               \
    if (object->pT() > MINPT and                                                  \
        fabs(object->eta()) > MINETA and                                          \
        has_tag(EFF, fabs(object->eta()), object->pT()))                          \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline objects with min pT, min eta, max pT and max eta
#define BASELINE_OBJECTS_7(TYPE, OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA)     \
  std::vector<const HEPUtils::TYPE*> NAME;                                        \
  for (const HEPUtils::TYPE* object : OBJECTS)                                    \
  {                                                                               \
    if(object->pT() > MINPT and                                                   \
       object->pT() < MAXPT and                                                   \
       fabs(object->eta()) > MINETA and                                           \
       fabs(object->eta()) < MAXETA)                                              \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline objects with min pT, min eta, max pT, max eta and selection efficiency
#define BASELINE_OBJECTS_8(TYPE, OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF) \
  std::vector<const HEPUtils::TYPE*> NAME;                                        \
  for (const HEPUtils::TYPE* object : OBJECTS)                                    \
  {                                                                               \
    if (object->pT() > MINPT and                                                  \
        object->pT() < MAXPT and                                                  \
        fabs(object->eta()) > MINETA and                                          \
        fabs(object->eta()) < MAXETA and                                          \
        has_tag(EFF, fabs(object->eta()), object->pT()))                          \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline particles with min pT and min et
#define BASELINE_PARTICLES_4(OBJECTS, NAME, MINPT, MINETA)                         \
  BASELINE_OBJECTS_5(Particle, OBJECTS, NAME, MINPT, MINETA)

/// Define baseline particles with min pT, min eta and selection efficiency
#define BASELINE_PARTICLES_5(OBJECTS, NAME, MINPT, MINETA, EFF)                    \
  BASELINE_OBJECTS_6(Particle, OBJECTS, NAME, MINPT, MINETA, EFF)

/// Define baseline particles with min pT, min eta, max pT and max eta
#define BASELINE_PARTICLES_6(OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA)          \
  BASELINE_OBJECTS_7(Particle, OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA)

/// Define baseline particles with min pT, min eta, max pT, max eta and selection efficiency
#define BASELINE_PARTICLES_7(OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF)     \
  BASELINE_OBJECTS_8(Particle, OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF)

/// Define baseline jets with a min pT and a min eta
#define BASELINE_JETS_4(OBJECTS, NAME, MINPT, MINETA)                              \
  BASELINE_OBJECTS_5(Jet, OBJECTS, NAME, MINPT, MINETA)

/// Define baseline jets with a min pT, a min eta and selection efficiency
#define BASELINE_JETS_5(OBJECTS, NAME, MINPT, MINETA, EFF)                         \
  BASELINE_OBJECTS_6(Jet, OBJECTS, NAME, MINPT, MINETA, EFF)

/// Define baseline jets with a min pT, a min eta, max pT and max eta
#define BASELINE_JETS_6(OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA)               \
  BASELINE_OBJECTS_7(Jet, OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA)

/// Define baseline jets with a min pT, a min eta, max pT, max eta and selection efficiency
#define BASELINE_JETS_7(OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF)          \
  BASELINE_OBJECTS_8(Jet, OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF)

/// Redirection macro
#define BASELINE_PARTICLES(...)      VARARG(BASELINE_PARTICLES, __VA_ARGS__)
#define BASELINE_JETS(...)           VARARG(BASELINE_JETS, __VA_ARGS__)
#define BASELINE_OBJECTS(...)        VARARG(BASELINE_OBJECTS, __VA_ARGS__)

/// Define baseline bjets with a min pT and a min eta
#define BASELINE_BJETS_4(OBJECTS, NAME, MINPT, MINETA)                            \
  std::vector<const HEPUtils::Jet*> NAME;                                         \
  for (const HEPUtils::Jet* object : OBJECTS)                                     \
  {                                                                               \
    if (object->btag() and                                                        \
        object->pT() > MINPT and                                                  \
        fabs(object->eta()) > MINETA)                                             \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline bjets with a min pT, a min eta and selection efficiency
#define BASELINE_BJETS_5(OBJECTS, NAME, MINPT, MINETA, EFF)                       \
  std::vector<const HEPUtils::Jet*> NAME;                                         \
  for (const HEPUtils::Jet* object : OBJECTS)                                     \
  {                                                                               \
    if (object->btag() and                                                        \
        object->pT() > MINPT and                                                  \
        fabs(object->eta()) > MINETA and                                          \
        has_tag(EFF, fabs(object->eta()), object->pT()))                          \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline bjets with a min pT, a min eta, a max pT and a max eta
#define BASELINE_BJETS_6(OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA)             \
  std::vector<const HEPUtils::Jet*> NAME;                                         \
  for (const HEPUtils::Jet* object : OBJECTS)                                     \
  {                                                                               \
    if (object->btag() and                                                        \
        object->pT() > MINPT and                                                  \
        object->pT() < MAXPT and                                                  \
        fabs(object->eta()) > MINETA and                                          \
        fabs(object->eta()) < MAXETA)                                             \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline bjets with a min pT, a min eta, a max pT, a max eta and selection efficiency
#define BASELINE_BJETS_7(OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF)        \
  std::vector<const HEPUtils::Jet*> NAME;                                         \
  for (const HEPUtils::Jet* object : OBJECTS)                                     \
  {                                                                               \
    if (object->btag() and                                                        \
        object->pT() > MINPT and                                                  \
        object->pT() < MAXPT and                                                  \
        fabs(object->eta()) > MINETA and                                          \
        fabs(object->eta()) < MAXETA and                                          \
        has_tag(EFF, fabs(object->eta()), object->pT()))                          \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline bjets with a min pT, a min eta, a max pT, a max eta,
/// a selection efficiency and a misidentification efficiency
#define BASELINE_BJETS_8(OBJECTS, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF, MISID) \
  std::vector<const HEPUtils::Jet*> NAME;                                         \
  for (const HEPUtils::Jet* object : OBJECTS)                                     \
  {                                                                               \
    if ((object->btag() or has_tag(MISID)) and                                    \
        object->pT() > MINPT and                                                  \
        object->pT() < MAXPT and                                                  \
        fabs(object->eta()) > MINETA and                                          \
        fabs(object->eta()) < MAXETA and                                          \
        has_tag(EFF, fabs(object->eta()), object->pT()))                          \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }


#define BASELINE_BJETS(...)          VARARG(BASELINE_BJETS, __VA_ARGS__)


/// Define a combination of baseline objects
#define BASELINE_OBJECT_COMBINATION(TYPE, TARGET, OBJECT1, OBJECT2)               \
  std::vector<const HEPUtils::TYPE*> TARGET;                                      \
  for(const HEPUtils::TYPE* obj1 : OBJECT1)                                       \
    TARGET.push_back(obj1);                                                       \
  for(const HEPUtils::TYPE* obj2 : OBJECT2)                                       \
    TARGET.push_back(obj2);

/// Define a combination of baseline particles
#define BASELINE_PARTICLE_COMBINATION(TARGET, OBJECT1, OBJECT2)                   \
  BASELINE_OBJECT_COMBINATION(Particle, TARGET, OBJECT1, OBJECT2)

/// Define a combination of baseline jets
#define BASELINE_JET_COMBINATION(TARGET, OBJECT1, OBJECT2)                        \
  BASELINE_OBJECT_COMBINATION(Jet, TARGET, OBJECT1, OBJECT2)

/// Define a (potentially sorted) signal objects from baseline objects
#define SIGNAL_OBJECTS_4(TYPE, BASELINE, SIGNAL, SORTED)                          \
  std::vector<const HEPUtils::TYPE*> SIGNAL(BASELINE);                            \
  if(SORTED) sortByPt(SIGNAL);

/// Define a (potentially sorted) signal particles from baseline particles
#define SIGNAL_PARTICLES_3(BASELINE, SIGNAL, SORTED)                              \
  SIGNAL_OBJECTS_4(Particle, BASELINE, SIGNAL, SORTED)                            \

/// Define a (potentially sorted) signal jets from a baseline jets
#define SIGNAL_JETS_3(BASELINE, SIGNAL, SORTED)                                   \
  SIGNAL_OBJECTS_4(Jet, BASELINE, SIGNAL, SORTED)

/// Define a sorted signal objects from a baseline objects
#define SIGNAL_OBJECTS_3(TYPE, BASELINE, SIGNAL)                                  \
  SIGNAL_OBJECTS_4(TYPE, BASELINE, SIGNAL, 1)

/// Define sorted signal particles from baseline particles
#define SIGNAL_PARTICLES_2(BASELINE, SIGNAL)                                      \
  SIGNAL_OBJECTS_3(Particle, BASELINE, SIGNAL)

/// Define a signal jets from a baseline jets
#define SIGNAL_JETS_2(BASELINE, SIGNAL)                                           \
  SIGNAL_OBJECTS_3(Jet, BASELINE, SIGNAL)

/// Redirection macros
#define SIGNAL_PARTICLES(...)    VARARG(SIGNAL_PARTICLES, __VA_ARGS__)
#define SIGNAL_JETS(...)         VARARG(SIGNAL_JETS, __VA_ARGS__)
#define SIGNAL_OBJECTS(...)      VARARG(SIGNAL_OBJECTS, __VA_ARGS__)

/// Define a combination of signal objects
#define SIGNAL_OBJECT_COMBINATION(TYPE, TARGET, OBJECT1, OBJECT2)                 \
  std::vector<const HEPUtils::TYPE*> TARGET = OBJECT1;                            \
  TARGET.insert(TARGET.end(), OBJECT2.begin(), OBJECT2.end());                    \
  sortByPt(TARGET);

/// Define a combination of signal particles
#define SIGNAL_PARTICLE_COMBINATION(TARGET, OBJECT1, OBJECT2)                     \
  SIGNAL_OBJECT_COMBINATION(Particle, TARGET, OBJECT1, OBJECT2)

/// Define a combination of signal jets
#define SIGNAL_JET_COMBINATION(TARGET, OBJECT1, OBJECT2)                          \
  SIGNAL_OBJECT_COMBINATION(Jet, TARGET, OBJECT1, OBJECT2)

/// Types of predefined pairs
/*#define OS    1  // opposite sign
#define SS    2  // same sign
#define SF    3  // same flavour
#define OSSF  4  // opposite sign, same flavour
#define SSSF  5  // ssame sign, same flavour
*/
/// Create a container for pairs
#define CREATE_PAIR(TYPE, SOURCE, CONTAINER, UNIQUE)                              \
  typedef std::vector<std::vector<const HEPUtils::Particle*>> ParticleContainer;  \
  ParticleContainer CONTAINER = CAT_3(get,TYPE,pairs)(SOURCE);                    \
  if(UNIQUE)                                                                      \
    uniquePairs(CONTAINER);

/// Preselection, at the start initialize cutflows, at the end fill preselection cutflow
#define BEGIN_PRESELECTION                                                        \
  _cutflows.fillinit(event->weight());

#define END_PRESELECTION                                                          \
  _cutflows.fillnext(event->weight());

/// Log cuts for one or more signal regions
#define LOG_CUT_1(A)                      _cutflows[A].fillnext(event->weight());
#define LOG_CUT_2(A,B)                    LOG_CUT_1(A) LOG_CUT_1(B)
#define LOG_CUT_3(A,B,C)                  LOG_CUT_1(A) LOG_CUT_2(B,C)
#define LOG_CUT_4(A,B,C,D)                LOG_CUT_1(A) LOG_CUT_3(B,C,D)
#define LOG_CUT_5(A,B,C,D,E)              LOG_CUT_1(A) LOG_CUT_4(B,C,D,E)
#define LOG_CUT_6(A,B,C,D,E,F)            LOG_CUT_1(A) LOG_CUT_5(B,C,D,E,F)
#define LOG_CUT_7(A,B,C,D,E,F,G)          LOG_CUT_1(A) LOG_CUT_6(B,C,D,E,F,G)
#define LOG_CUT_8(A,B,C,D,E,F,G,H)        LOG_CUT_1(A) LOG_CUT_7(B,C,D,E,F,G,H)
#define LOG_CUT_9(A,B,C,D,E,F,G,H,I)      LOG_CUT_1(A) LOG_CUT_8(B,C,D,E,F,G,H,I)
#define LOG_CUT_10(A,B,C,D,E,F,G,H,I,J)   LOG_CUT_1(A) LOG_CUT_9(B,C,D,E,F,G,H,I,J)
#define LOG_CUT(...)      VARARG(LOG_CUT, __VA_ARGS__)

/// Fill signal region and cutflow
#define FILL_SIGNAL_REGION(NAME)                                                  \
  _cutflows[NAME].fillnext(event->weight());                                      \
  _counters.at(NAME).add_event(event);

/// TODO: Chris Chang (My test)
/// Add the signal region to the list of signal regions filled TODO: Could be called inside of the Fill_Signal_Region() macro
/// Also fill a map relating SR name to an integer
#define Add_SR_INT_MAP_ENTRY(NAME) \
  { \
    int SR_int_map_size = SR_int_map.size(); \
    SR_int_map[NAME] = SR_int_map_size; \
    int_SR_map[SR_int_map_size] = NAME; \
  }

// Push back an empty vector to indicate that a new event is about to be run
#define ADD_NEW_EVENT \
  passed_any_cuts = false; \
  n_MC += 1;

// TODO: This will only work if the signal regions were created at the start of the run function with an empty vector TODO: Put this in the FILL_SIGNAL_REGION(NAME) Macro
#define LOG_FILLED_SIGNAL_REGION(NAME) \
  int SRint = SR_int_map.at(NAME); \
  if (!passed_any_cuts) _filled_SR.push_back(std::vector<int>()); \
  _filled_SR.back().push_back(SRint); \
  passed_any_cuts = true; \

/// Commit values for the signal region: predictions, observed and backgrounds
#define COMMIT_SIGNAL_REGION(NAME, OBS, BKG_CENTRAL, BKG_ERR)                     \
  add_result(SignalRegionData(_counters.at(NAME), OBS, {BKG_CENTRAL, BKG_ERR}));

/// Commit a covariance matrix
#define COMMIT_COVARIANCE_MATRIX(COV)                                             \
  set_covariance(COV);

/// Commit cutflows
#define COMMIT_CUTFLOWS                                                           \
  add_cutflows(_cutflows);



