//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A Mathematica backend example.
///
///  *********************************************
///
///  Authors (add name and sate if you modify):
///
///  \author Tomas Gonzalo
///  \date 2016 Sept
///
///  *********************************************

#define BACKENDNAME libMathematicaTest
#define BACKENDLANG MATHEMATICA
#define VERSION 1.0
#define SAFE_VERSION 1_0
#define REFERENCE GAMBIT:2017yxo

LOAD_LIBRARY

BE_ALLOW_MODELS(CMSSM)

BE_FUNCTION(CalculateSquare, MReal, (const MInteger&), "CalculateSquare","MathTest_CalculateSquare")
BE_FUNCTION(CalculateSum, MReal, (const MReal&, const MReal&), "CalculateSum", "MathTest_CalculateSum")
BE_FUNCTION(PrintVar, MInteger, (), "PrintVar", "MathTest_PrintVar")
BE_FUNCTION(PrintVarorVar2, MReal, (const MBool&), "PrintVarorVar2", "MathTest_PrintVarorVar2")
BE_FUNCTION(VarEqualVar2, MBool, (), "VarEqualVar2", "MathTest_VarEqualVar2")
BE_FUNCTION(StringTest, MString, (const MString&), "StringTest", "MathTest_StringTest")
BE_FUNCTION(VoidTest, MVoid, (), "VoidTest", "MathTest_VoidTest")
BE_FUNCTION(ExtractElement, MInteger, (const MList<MInteger>&, const MInteger&), "ExtractElement", "MathTest_ExtractElement")
BE_FUNCTION(SquareList, MList<MInteger>, (const MList<MInteger>&), "SquareList", "MathTest_SquareList")
BE_FUNCTION(Gammafunc, MInteger, (const MInteger&), "\\[CapitalGamma]func", "MathTest_Gammafunc")

BE_VARIABLE(Var, MInteger, "Var", "MathTest_Var")
BE_VARIABLE(Var2, MReal, "Var2", "MathTest_Var2")
BE_VARIABLE(deltavar, MInteger, "\\[Delta]var", "MathTest_deltabar")

/* Convenience functions (declarations) */
BE_CONV_FUNCTION(run_Mathematica_Test, double, (const int&, const int&), "MathTest")

// Undefine macros toa void conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
