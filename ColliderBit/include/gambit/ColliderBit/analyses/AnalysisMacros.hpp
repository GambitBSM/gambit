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

/// Define a signal region by initialzing the counter and cutflow
#define DEFINE_SIGNAL_REGION(NAME)                             \
  _counters[NAME] =  EventCounter(NAME);                       \
  _cutflows.addCutflow(NAME, {"Preselection", "Final"});

/// Define multiple signal regions that share a common name and
/// only vary on sequential numbering
#define DEFINE_SIGNAL_REGIONS(NAME, N)                         \
  for(size_t i=1; i<=N; ++i)                                   \
  {                                                            \
    str basename(NAME);                                        \
    str name = i < 10 ? basename + "0" + std::to_string(i) : basename + std::to_string(i); \
    DEFINE_SIGNAL_REGION(name)                                 \
  }


/// Define a baseline object with min pT, min eta and selection efficiency
#define BASELINE_OBJECT_5(TYPE, OBJECT, NAME, MINPT, MINETA, EFF)        \
  std::vector<const HEPUtils::TYPE*> NAME;                               \
  for (const HEPUtils::TYPE* object : event->OBJECT())                   \
  {                                                                      \
    bool isObject = has_tag(EFF, fabs(object->eta()), object->pT());     \
    if (object->pT() > MINPT and fabs(object->eta()) < MINETA)           \
    {                                                                    \
      if(isObject)                                                       \
        NAME.push_back(object);                                          \
    }                                                                    \
  }


/// Define a baseline particle with min pT, min eta and selection efficiency
#define BASELINE_PARTICLE_5(OBJECT, NAME, MINPT, MINETA, EFF)            \
  BASELINE_OBJECT_5(Particle, OBJECT, NAME, MINPT, MINETA, EFF)

/// Define a baseline jet with a min pT, a min eta and selection efficiency
#define BASELINE_JET_5(OBJECT, NAME, MINPT, MINETA, EFF)                 \
  BASELINE_OBJECT_5(Jet, OBJECT, NAME, MINPT, MINETA, EFF)

/// Define a baseline object with min pT and min eta
#define BASELINE_OBJECT_4(TYPE, OBJECT, NAME, MINPT, MINETA)             \
  std::vector<const HEPUtils::TYPE*> NAME;                               \
  for (const HEPUtils::TYPE* object : event->OBJECT())                   \
  {                                                                      \
    if (object->pT() > MINPT and fabs(object->eta()) < MINETA)           \
    {                                                                    \
      NAME.push_back(object);                                            \
    }                                                                    \
  }

/// Define a baseline particle with min pT and min eta
#define BASELINE_PARTICLE_4(OBJECT, NAME, MINPT, MINETA)                 \
  BASELINE_OBJECT_4(Particle, OBJECT, NAME, MINPT, MINETA)

/// Define a baseline jet with a min pT and a min eta
#define BASELINE_JET_4(OBJECT, NAME, MINPT, MINETA)                      \
  BASELINE_OBJECT_4(Jet, OBJECT, NAME, MINPT, MINETA)

// Redirection macro
#define BASELINE_PARTICLE(...)      VARARG(BASELINE_PARTICLE, __VA_ARGS__)
#define BASELINE_JET(...)           VARARG(BASELINE_JET, __VA_ARGS__)
#define BASELINE_OBJECT(...)        VARARG(BASELINE_OBJECT, __VA_ARGS__)


/// Define a combination of baseline objects
#define BASELINE_OBJECT_COMBINATION(TYPE, TARGET, OBJECT1, OBJECT2)     \
  std::vector<const HEPUtils::TYPE*> TARGET;                            \
  for(const HEPUtils::TYPE* obj1 : OBJECT1)                             \
    TARGET.push_back(obj1);                                             \
  for(const HEPUtils::TYPE* obj2 : OBJECT2)                             \
    TARGET.push_back(obj2);

/// Define a combination of baseline particles
#define BASELINE_PARTICLE_COMBINATION(TARGET, OBJECT1, OBJECT2)         \
  BASELINE_OBJECT_COMBINATION(Particle, TARGET, OBJECT1, OBJECT2)

/// Define a combination of baseline jets
#define BASELINE_JET_COMBINATION(TARGET, OBJECT1, OBJECT2)              \
  BASELINE_OBJECT_COMBINATION(Jet, TARGET, OBJECT1, OBJECT2)
