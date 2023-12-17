// -*- C++ -*-
//
// This file is part of HEPUtils -- https://gitlab.com/hepcedar/heputils/
// Copyright (C) 2013-2022 Andy Buckley <andy.buckley@cern.ch>
//
// Embedding of HEPUtils code in other projects is permitted provided this
// notice is retained and the HEPUtils namespace and include path are changed.
//
#pragma once

#if  __cplusplus < 201103L
#pragma message "This library needs at least a C++11 compliant compiler"
#endif


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


  /// @}


}
