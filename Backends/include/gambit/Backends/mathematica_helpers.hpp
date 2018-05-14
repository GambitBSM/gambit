//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declarations of helper functions for
///  mathematica_function and mathematica_variable
///  classes.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Dec
///
///  *********************************************

#ifndef __mathematica_helpers_hpp__
#define __mathematica_helpers_hpp__

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Backends/backend_singleton.hpp"

#include MATHEMATICA_WSTP_H


namespace Gambit
{

  namespace Backends
  {

    /// Helper function to raise an appropriate warning or error in case of problems.
    void math_error(WSLINK, const str&, const str&);

    /// Helper function that indicates if a type is numerical or not
    template <typename T>
    bool is_numeric()
    {
      return (boost::is_same<T, int>::value or
              boost::is_same<T, const int>::value or
              boost::is_same<T, float>::value or
              boost::is_same<T, const float>::value or
              boost::is_same<T, double>::value or
              boost::is_same<T, const double>::value);
    }

    /// Sneaky template classes that allow one to declare dummy 'instances' of voids (as ints) in templates
    /// @{
    template <typename T>
    class instance_helper { public: T member; };
    template <>
    class instance_helper<void> { public: int member; };
    /// @}

    /// Overloaded functions to get data through WSTP
    /// @{
    int WSGetVariable(WSLINK WSlink, int* val);
    int WSGetVariable(WSLINK WSlink, float* val);
    int WSGetVariable(WSLINK WSlink, double* val);
    int WSGetVariable(WSLINK WSlink, bool* val);
    int WSGetVariable(WSLINK WSlink, char* val);
    int WSGetVariable(WSLINK WSlink, str* val);
    template <typename T> int WSGetVariable(WSLINK WSlink, std::vector<T>* val)
    {
      long int dim;
      if(!WSCheckFunction(WSlink, "List", &dim))
        return 0;
      for(int i=0; i<dim; i++)
      {
        T value;
        if(!WSGetVariable(WSlink, &value))
          return 0;
        val->push_back(value);
      }
      return 1;
    }
    /// @}

    /// Overloaded functions to put data through WSTP
    /// @{
    int WSPutVariable(WSLINK WSlink, int val);
    int WSPutVariable(WSLINK WSlink, float val);
    int WSPutVariable(WSLINK WSlink, double val);
    int WSPutVariable(WSLINK WSlink, bool val);
    int WSPutVariable(WSLINK WSlink, char val);
    int WSPutVariable(WSLINK WSlink, str val);
    template <typename T> int WSPutVariable(WSLINK WSlink, std::vector<T> val)
    {
      if(!WSPutFunction(WSlink, "List", val.size()))
        return 0;
      for(auto it = val.begin(); it != val.end(); it++)
        if(!WSPutVariable(WSlink, *it))
          return 0;
      return 1;
    }
    int WSPutVariables(WSLINK);
    template <typename T>
    int WSPutVariables(WSLINK WSlink, T last)
    {
      return WSPutVariable(WSlink, last);
    }
    template <typename T1, typename T2, typename... Others>
    int WSPutVariables(WSLINK WSlink, T1 first, T2 second, Others... args)
    {
      int i = WSPutVariable(WSlink, first);
      if (i == 0) return i;
      else return i * WSPutVariables(WSlink, second, args...);
    }
    /// @}


    /// @}

  }

}

#endif // defined __mathematica_helpers_hpp__