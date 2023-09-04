//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  A replacement type for 'bool' which does not
///  allow automatic conversion to/from 'int' etc.
///
///  Doesn't do fancy stuff like allow comparisons,
///  but can use as the condition in 'if'
///  statements, and supports automatic conversion
///  to (but not from) bool.
///
///  Currently used in the SubSpectrum class to
///  resolve overload ambiguities between int and
///  bool arguments due to automatic conversions.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Oct
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Mar
///
///  *********************************************

#pragma once

namespace Gambit
{

  class SafeBool
  {
    bool _ok;
    public:
      explicit SafeBool(bool ok): _ok(ok) {}
      explicit operator bool() const { return _ok; }
  };

}
