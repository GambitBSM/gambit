//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Useful ColliderBit specific macros.
///
///  @todo Wouldn't the analysis ones be better in the single .cpp file where they're used?
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  *********************************************

#ifndef __ColliderBit_macros_hpp__
#define __ColliderBit_macros_hpp__

/// For analysis factory function declaration
#define DECLARE_ANALYSIS_FACTORY(ANAME)                                    \
  HEPUtilsAnalysis* create_Analysis_ ## ANAME();
/// For analysis factory function definition
#define DEFINE_ANALYSIS_FACTORY(ANAME)                                     \
  HEPUtilsAnalysis* create_Analysis_ ## ANAME() {                          \
    return new Analysis_ ## ANAME();                                       \
  }
/// For the string based factory function mkAnalysis()
#define IF_X_RTN_CREATE_ANA_X(A)                                           \
  if (name == #A) return create_Analysis_ ## A();

/// For the string based analysis check checkAnalysis
#define IF_X_RTN_TRUE(A)                                                   \
  if (name == #A) return true;

/// For the string based SpecializablePythia function resetSpecialization()
#define IF_X_SPECIALIZEX(X)                                                \
  if (specName == #X) { _specialInit = X::init; return; }

/// Raise (local) exception if two vectors are not of equal length
#define CHECK_EQUAL_VECTOR_LENGTH(VEC1, VEC2)                              \
if (VEC1.size() != VEC2.size())                                            \
{                                                                          \
  std::stringstream errmsg;                                                \
  errmsg << "The number of elements in option '" << #VEC1 << "'" << endl   \
         << "must match the number of elements in option '" << #VEC2       \
         << "'." << endl;                                                  \
  ColliderBit_error().raise(LOCAL_INFO, errmsg.str());                     \
}                                                                          \

#endif /* defined __ColliderBit_macros_hpp__ */
