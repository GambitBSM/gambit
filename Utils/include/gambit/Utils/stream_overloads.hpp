//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Define overloadings of the stream operator for
///  various containers.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2013 Jan, Dec
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu)
///  \date 2013 Jun, 2016 Jan
///
///  *********************************************


#ifndef __stream_overloads_hpp__
#define __stream_overloads_hpp__

#include <map>
#include <set>
#include <string>
#include <vector>
#include <ostream>

namespace Gambit
{

  /// Spacing utility for stream overloads
  std::string spacing(int, int);

  /// Stream overload for pairs of any type that already has << defined.
  template <class Type1, class Type2>
  inline std::ostream& operator << (std::ostream& os, const std::pair<Type1, Type2>& p)
  {
    os << "( " << p.first << ", " << p.second << ")";
    return os;
  }

  /// Stream overload for sets of any type that already has << defined.
  template <class Type>
  inline std::ostream& operator << (std::ostream& os, const std::set<Type>& set)
  {
    os << "{";
    int length = set.size();
    if (length != 0)
    {
      typename std::set<Type>::const_iterator it, start, finish;
      start = set.begin();
      finish = set.end();
      os << *start;
      if (length != 1)
      {
        for (it = ++start; it != finish; it++) { os << ", " << *it; }
      }
    }
    os << "}";
    return os;
  }

  /// Stream overload for vectors of any type that already has << defined.
  template <class Type>
  inline std::ostream& operator << (std::ostream& os, const std::vector<Type>& v)
  {
    os << "[";
    int length = v.size();
    if (length != 0)
    {
      typename std::vector<Type>::const_iterator it, start, finish;
      start = v.begin();
      finish = v.end();
      os << *start;
      if (length != 1)
      {
        for (it = ++start; it != finish; it++) { os << ", " << *it; }
      }
    }
    os << " ]";
    return os;
  }

  /// Stream overload for map from string to any type that already has << defined
  template<class Type>
  std::ostream& operator << (std::ostream& os, const std::map<std::string,Type>& map)
  {
    unsigned int maxlen = 0;

    for (auto it = map.begin(); it != map.end(); it++)
    {
      if ((*it).first.length() > maxlen) maxlen = (*it).first.length();
    }

    for (auto it = map.begin(); it != map.end(); it++)
    {
      if (it != map.begin()) {os << std::endl;}
      os << " " << (*it).first << spacing((*it).first.length(), maxlen) << "(" << (*it).second << ")";
    }

    return os;
  }

}

#endif /* defined(__stream_overloads_hpp__) */

