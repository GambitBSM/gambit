// -*- C++ -*-
//
// This file is part of HEPUtils -- https://gitlab.com/hepcedar/heputils/
// Copyright (C) 2013-2026 Andy Buckley <andy.buckley@cern.ch>
//
// Embedding of HEPUtils code in other projects is permitted provided this
// notice is retained and the HEPUtils namespace and include path are changed.
//
#pragma once

#if  __cplusplus < 201103L
#pragma message "This library needs at least a C++11 compliant compiler"
#endif

#include <vector>


/// @file Utility functions
/// @author Andy Buckley <andy.buckley@cern.ch>

namespace HEPUtils {


  /// @defgroup utils_container Container utils
  /// @{

  /// Return true if f(x) is true for any x in container c, otherwise false.
  template <typename CONTAINER, typename FN>
  inline bool any(const CONTAINER& c, const FN& f) {
    for (const typename CONTAINER::value_type& val : c) {
      if (f(val)) return true;
    }
    return false;
  }

  /// Return true if f(x) is true for all x in container c, otherwise false.
  template <typename CONTAINER, typename FN>
  inline bool all(const CONTAINER& c, const FN& f) {
    for (const typename CONTAINER::value_type& val : c) {
      if (!f(val)) return false;
    }
    return true;
  }

  /// Return true if x is found in container c, otherwise false.
  template <typename CONTAINER, typename T>
  inline bool contains(const CONTAINER& c, const T& x) {
    for (const typename CONTAINER::value_type& val : c) {
      if (val == x) return true;
    }
    return false;
  }


  /// @brief Deep-copy each element of the from vector into the to vector, via new
  ///
  /// The to vector doesn't have to be empty; if already populated, new clones will be appended.
  template <typename T>
  void deepcopy(const std::vector<T*>& from, std::vector<T*>& to) {
    //from.clear();
    to.reserve(from.size()+to.size()); //< allow appending
    for (const T* t : from) to.push_back(new T(*t));
  }

  /// @brief Deep-copy each element of the from vector into a returned vector, via new
  ///
  /// The to vector doesn't have to be empty; if already populated, new clones will be appended.
  template <typename T>
  std::vector<T*> deepcopy(const std::vector<T*>& from) {
    std::vector<T*> rtn;
    deepcopy(from, rtn);
    return rtn;
  }

  /// @}


}
