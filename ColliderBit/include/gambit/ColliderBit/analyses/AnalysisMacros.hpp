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
///  \date 2023 July
///
///  *********************************************

#pragma once

/// Min and max values of eta and pT
#define ETAMIN 0
#define PTMIN 0
#define ETAMAX DBL_MAX
#define PTMAX DBL_MAX

/// Define a signal region by initialzing the counter and cutflow
#define DEFINE_SIGNAL_REGION(NAME)                                                \
  _counters[NAME] =  EventCounter(NAME);                                          \
  _cutflows.addCutflow(NAME, {"Preselection", "Final"});

/// Define multiple signal regions that share a common name and
/// only vary on sequential numbering
#define DEFINE_SIGNAL_REGIONS(NAME, N)                                            \
  for(size_t i=1; i<=N; ++i)                                                      \
  {                                                                               \
    str basename(NAME);                                                           \
    str name = i < 10 ? basename + "0" + std::to_string(i) : basename + std::to_string(i); \
    DEFINE_SIGNAL_REGION(name)                                                    \
  }

/// Commit values for the signal region: predictions, observed and backgrounds
#define COMMIT_SIGNAL_REGION(NAME, OBS, BKG_CENTRAL, BKG_ERR)                     \
  add_result(SignalRegionData(_counters.at(NAME), OBS, {BKG_CENTRAL, BKG_ERR}));

/// Commit a covariance matrix
#define COMMIT_COVARIANCE_MATRIX(COV)                                             \
  set_covariance(COV);

/// Commit cutflows
#define COMMIT_CUTFLOWS                                                           \
  add_cutflows(_cutflows);


/// Define baseline objects with min pT and min eta
#define BASELINE_OBJECTS_5(TYPE, OBJECT, NAME, MINPT, MINETA)                     \
  std::vector<const HEPUtils::TYPE*> NAME;                                        \
  for (const HEPUtils::TYPE* object : event->OBJECT())                            \
  {                                                                               \
    if (object->pT() > MINPT and                                                  \
        fabs(object->eta()) > MINETA)                                             \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline objects with min pT, min eta and selection efficiency
#define BASELINE_OBJECTS_6(TYPE, OBJECT, NAME, MINPT, MINETA, EFF)                \
  std::vector<const HEPUtils::TYPE*> NAME;                                        \
  for (const HEPUtils::TYPE* object : event->OBJECT())                            \
  {                                                                               \
    if (object->pT() > MINPT and                                                  \
        fabs(object->eta()) > MINETA and                                          \
        has_tag(EFF, fabs(object->eta()), object->pT()))                          \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline objects with min pT, min eta, max pT and max eta
#define BASELINE_OBJECTS_7(TYPE, OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA)      \
  std::vector<const HEPUtils::TYPE*> NAME;                                        \
  for (const HEPUtils::TYPE* object : event->OBJECT())                            \
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
#define BASELINE_OBJECTS_8(TYPE, OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF) \
  std::vector<const HEPUtils::TYPE*> NAME;                                        \
  for (const HEPUtils::TYPE* object : event->OBJECT())                            \
  {                                                                               \
    if (object->pT() > MINPT and                                                  \
        object->pT() < MAXPT and                                                  \
        fabs(object->eta()) > MINETA and                                          \
        fabs(object->eta()) < MAXETA and                                          \
        has_tag(EFF, fabs(object->eta()), object->pT()))                          \
    {                                                                             \
      NAME.push_back(object);                                                   \
    }                                                                             \
  }

/// Define baseline particles with min pT and min et
#define BASELINE_PARTICLES_4(OBJECT, NAME, MINPT, MINETA)                         \
  BASELINE_OBJECTS_5(Particle, OBJECT, NAME, MINPT, MINETA)

/// Define baseline particles with min pT, min eta and selection efficiency
#define BASELINE_PARTICLES_5(OBJECT, NAME, MINPT, MINETA, EFF)                    \
  BASELINE_OBJECTS_6(Particle, OBJECT, NAME, MINPT, MINETA, EFF)

/// Define baseline particles with min pT, min eta, max pT and max eta
#define BASELINE_PARTICLES_6(OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA)          \
  BASELINE_OBJECTS_7(Particle, OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA)

/// Define baseline particles with min pT, min eta, max pT, max eta and selection efficiency
#define BASELINE_PARTICLES_7(OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF)     \
  BASELINE_OBJECTS_8(Particle, OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF)

/// Define baseline jets with a min pT and a min eta
#define BASELINE_JETS_4(OBJECT, NAME, MINPT, MINETA)                              \
  BASELINE_OBJECTS_5(Jet, OBJECT, NAME, MINPT, MINETA)

/// Define baseline jets with a min pT, a min eta and selection efficiency
#define BASELINE_JETS_5(OBJECT, NAME, MINPT, MINETA, EFF)                         \
  BASELINE_OBJECTS_6(Jet, OBJECT, NAME, MINPT, MINETA, EFF)

/// Define baseline jets with a min pT, a min eta, max pT and max eta
#define BASELINE_JETS_6(OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA)               \
  BASELINE_OBJECTS_7(Jet, OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA)

/// Define baseline jets with a min pT, a min eta, max pT, max eta and selection efficiency
#define BASELINE_JETS_7(OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF)          \
  BASELINE_OBJECTS_8(Jet, OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF)

/// Redirection macro
#define BASELINE_PARTICLES(...)      VARARG(BASELINE_PARTICLES, __VA_ARGS__)
#define BASELINE_JETS(...)           VARARG(BASELINE_JETS, __VA_ARGS__)
#define BASELINE_OBJECTS(...)        VARARG(BASELINE_OBJECTS, __VA_ARGS__)

/// Define baseline bjets with a min pT and a min eta
#define BASELINE_BJETS_4(OBJECT, NAME, MINPT, MINETA)                             \
  std::vector<const HEPUtils::Jet*> NAME;                                         \
  for (const HEPUtils::Jet* object : event->OBJECT())                             \
  {                                                                               \
    if (object->btag() and                                                        \
        object->pT() > MINPT and                                                  \
        fabs(object->eta()) > MINETA)                                             \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline bjets with a min pT, a min eta and selection efficiency
#define BASELINE_BJETS_5(OBJECT, NAME, MINPT, MINETA, EFF)                        \
  std::vector<const HEPUtils::Jet*> NAME;                                         \
  for (const HEPUtils::Jet* object : event->OBJECT())                             \
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
#define BASELINE_BJETS_6(OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA)              \
  std::vector<const HEPUtils::Jet*> NAME;                                         \
  for (const HEPUtils::Jet* object : event->OBJECT())                             \
  {                                                                               \
    if (object->btag() and                                                        \
        object->pT() > MINPT and                                                  \
        object->pT() < MAXPT and                                                  \
        fabs(object->eta()) > MINETA and                                          \
        fabs(object->eta()) < MAXETA)                          \
    {                                                                             \
      NAME.push_back(object);                                                     \
    }                                                                             \
  }

/// Define baseline bjets with a min pT, a min eta, a max pT, a max eta and selection efficiency
#define BASELINE_BJETS_7(OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF)         \
  std::vector<const HEPUtils::Jet*> NAME;                                         \
  for (const HEPUtils::Jet* object : event->OBJECT())                             \
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
#define BASELINE_BJETS_8(OBJECT, NAME, MINPT, MINETA, MAXPT, MAXETA, EFF, MISSID) \
  std::vector<const HEPUtils::Jet*> NAME;                                         \
  for (const HEPUtils::Jet* object : event->OBJECT())                             \
  {                                                                               \
    if ((object->btag() or has_tag(MISSID)) and                                   \
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
#define SIGNAL_OBJECT_COMBINATION(TYPE, TARGET, OBJECT1, OBJECT2)       \
  std::vector<const HEPUtils::TYPE*> TARGET = OBJECT1;                  \
  TARGET.insert(TARGET.end(), OBJECT2.begin(), OBJECT2.end());          \
  sortByPt(TARGET);

/// Define a combination of signal particles
#define SIGNAL_PARTICLE_COMBINATION(TARGET, OBJECT1, OBJECT2)           \
  SIGNAL_OBJECT_COMBINATION(Particle, TARGET, OBJECT1, OBJECT2)

/// Define a combination of signal jets
#define SIGNAL_JET_COMBINATION(TARGET, OBJECT1, OBJECT2)                \
  SIGNAL_OBJECT_COMBINATION(Jet, TARGET, OBJECT1, OBJECT2)

