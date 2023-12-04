// -*- C++ -*-
//
// This file is part of HEPUtils -- https://gitlab.com/hepcedar/heputils/
// Copyright (C) 2013-2022 Andy Buckley <andy.buckley@cern.ch>
//
// Embedding of HEPUtils code in other projects is permitted provided this
// notice is retained and the HEPUtils namespace and include path are changed.
//
#pragma once

#include <cstddef>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cassert>
#include <cmath>

namespace HEPUtils {


  /// Simple class just to do 1D bin index lookups. Not a container.
  /// @todo Extend to use a -inf .. +inf scheme... with what out-of-range default value?
  template <typename TX=double>
  class Binning1D {
  public:

    /// Constructor taking a list of bin edges
    Binning1D(const std::vector<TX>& binedges)
      : edges(binedges)
    {
      reset();
    }


    /// Get the number of bins
    size_t num_bins() const {
      check();
      return edges.size() - 1;
    }
    /// Get the number of bins
    size_t size() const {
      return num_bins();
    }


    /// Get the bin index enclosing position @a x
    /// @note This is where _all_ the bin searching intelligence lives
    size_t get_index(const TX& x) const {
      check();
      if (x < edges.front()) throw std::out_of_range("Bin position underflow");
      if (x > edges.back()) throw std::out_of_range("Bin position overflow");
      // Find the closest knot below the requested value, starting with intelligent guesses
      // First assume linear/uniform binning
      const TX xfrac = (x - edges.front()) / (edges.back() - edges.front());
      const size_t iguess = floor( num_bins() * xfrac );
      if (edges[iguess] <= x && edges[iguess+1] > x) return iguess;
      // Then we'll try for uniform binning in log space if the vector is big enough to justify the log calls
      if (edges.size() > 64) { //< @todo Optimise
        const TX lnxlow = log(edges.front());
        const TX lnxtot = log(edges.back()) - lnxlow;
        const TX dlnx = log(x) - lnxlow;
        const TX xfrac2 = dlnx / lnxtot;
        const size_t iguess2 = floor( num_bins() * xfrac2 );
        if (edges[iguess2] <= x && edges[iguess2+1] > x) return iguess2;
      }
      // Fall back to something more general
      /// @todo Specialise for a linear search if size < 32, otherwise binary split as below
      size_t i = upper_bound(edges.begin(), edges.end(), x) - edges.begin();
      if (i == edges.size()) i -= 1; // can't return the last knot index
      i -= 1; // have to step back to get the knot <= x behaviour
      return i;
    }


    /// Clear the bin contents (but leave the binning intact)
    void reset() {
      assert(edges.size() > 1);
      check();
    }

    /// Check consistency
    void check() const {
      if (edges.size() <= 1) throw std::length_error("There must be 2 or more bin edges");
    }

    /// The list of bin edges
    std::vector<TX> edges;

  };



  /// Simple class just to do 2D bin index lookups. Not a container.
  /// @todo Extend to use a -inf .. +inf scheme... with what out-of-range default value?
  template <typename TX=double, typename TY=double>
  class Binning2D {
  public:

    /// Constructor taking lists of bin edges
    Binning2D(const std::vector<TX>& xbinedges, const std::vector<TY>& ybinedges)
      : binningX(xbinedges), binningY(ybinedges)
    {
      reset();
    }

    /// Constructor taking 1D binnings
    Binning2D(const Binning1D<TX>& xbinning, const Binning1D<TY>& ybinning)
      : binningX(xbinning), binningY(ybinning)
    {
      reset();
    }


    /// Get the number of bins in x
    size_t num_bins_x() const {
      return binningX.num_bins();
    }

    /// Get the number of bins in y
    size_t num_bins_y() const {
      return binningY.num_bins();
    }

    /// Get the total number of bins
    size_t num_bins() const {
      return num_bins_x() * num_bins_y();
    }
    /// Get the total number of bins
    size_t size() const {
      return num_bins();
    }


    /// Get the x bin index enclosing position @a x
    size_t get_index_x(const TX& x) const {
      return binningX.get_index(x);
    }

    /// Get the y bin index enclosing position @a y
    size_t get_index_y(const TY& y) const {
      return binningY.get_index(y);
    }

    /// Get the (x,y) bin index pair enclosing position @a (x,y)
    std::pair<size_t,size_t> get_index_pair(const TX& x, const TY& y) const {
      return std::make_pair(get_index_x(x), get_index_y(y));
    }


    /// Clear the bin contents (but leave the binning intact)
    void reset() {
      binningX.reset();
      binningY.reset();
      check();
    }

    /// Check consistency
    void check() const {
      binningX.check();
      binningY.check();
    }

    /// The lists of bin edges
    Binning1D<TX> binningX;
    Binning1D<TY> binningY;

  };



  /// Binned container of Ts in 1D
  /// @todo Extend to -inf .. +inf coverage, with templated out-of-range default value?
  template <typename T, typename TX=double>
  class BinnedFn1D {
  public:

    /// Constructor taking a list of bin edges
    BinnedFn1D(const std::vector<TX>& binedges)
      : binning(binedges)
    {
      reset();
    }

    /// Constructor taking lists of bin edges and values
    BinnedFn1D(const std::vector<TX>& binedges, const std::vector<T>& binvalues)
      : binning(binedges), values(binvalues)
    {
      check();
    }


    /// Get the number of bins
    size_t num_bins() const {
      return binning.num_bins();
    }

    /// Get the bin index enclosing position @a x
    size_t get_index(const TX& x) const {
      return binning.get_index(x);
    }

    /// Get the value in bin number @a ix
    const T& get_at_index(size_t ix) const {
      check();
      return values[ix];
    }

    /// Get the value in the bin at position @a x
    const T& get_at(const TX& x) const {
      return get_at_index(get_index(x));
    }

    /// Set the value in bin number @a ix
    void set_at_index(size_t ix, const T& val) {
      check();
      values[ix] = val;
    }

    /// Set the value in the bin at position @a x
    void set_at(const TX& x, const T& val) {
      set_at_index(get_index(x), val);
    }


    /// Clear the bin contents (but leave the binning intact)
    void reset() {
      // binning.reset();
      values.clear();
      values.resize(num_bins());
      check();
    }

    /// Check consistency of the edges and values vectors
    void check() const {
      binning.check();
      if (values.size() < 1) throw std::length_error("There must be 1 or more bin values");
      if (binning.size() != values.size()) throw std::length_error("There must be one more bin edge than there are bin values");
    }


    /// The list of bin edges
    Binning1D<TX> binning;

    /// The list of values
    std::vector<T> values;

  };



  /// Binned container of Ts in 2D
  /// @todo Extend to -inf .. +inf coverage, with templated out-of-range default value?
  template <typename T, typename TX=double, typename TY=double>
  class BinnedFn2D {
  public:

    /// Constructor taking a list of bin edges
    BinnedFn2D(const std::vector<TX>& xbinedges, const std::vector<TY>& ybinedges)
      : binning(xbinedges, ybinedges)
    {
      reset();
    }

    /// Constructor taking lists of bin edges and values
    BinnedFn2D(const std::vector<TX>& xbinedges, const std::vector<TY>& ybinedges, const std::vector<T>& binvalues)
      : binning(xbinedges, ybinedges), values(binvalues)
    {
      check();
    }


    /// Get the number of bins
    size_t num_bins() const {
      return binning.num_bins();
    }
    /// Get the number of bins in x
    size_t num_bins_x() const {
      return binning.num_bins_x();
    }
    /// Get the number of bins in y
    size_t num_bins_y() const {
      return binning.num_bins_y();
    }


    /// Get the x bin index enclosing position @a x
    size_t get_index_x(const TX& x) const {
      return binning.get_index_x(x);
    }

    /// Get the y bin index enclosing position @a y
    size_t get_index_y(const TY& y) const {
      return binning.get_index_y(y);
    }

    /// Get the x,y bin index pair enclosing position @a (x,y)
    std::pair<size_t,size_t> get_index_pair(const TX& x, const TY& y) const {
      return binning.get_index_pair(x, y);
    }

    /// Get the global bin index enclosing position @a (x,y)
    size_t get_index(const TX& x, const TY& y) const {
      return global_index(get_index_pair(x, y));
    }


    /// Get the global bin index from individual indices @a ix and @a iy
    size_t global_index(size_t ix, size_t iy) const {
      return ix*num_bins_y() + iy;
    }
    /// Get the global bin index from individual indices @a ix and @a iy
    size_t global_index(const std::pair<size_t,size_t>& ixiy) const {
      return global_index(ixiy.first, ixiy.second);
    }



    /// Get the value in global bin number @a i
    const T& get_at_index(size_t i) const {
      check();
      return values[i];
    }

    /// Get the value in bin number pair @a (ix, iy)
    const T& get_at_index(size_t ix, size_t iy) const {
      return get_at_index(global_index(ix, iy));
    }

    /// Get the value in the bin at position @a (x,y)
    const T& get_at(const TX& x, const TY& y) const {
      return get_at_index(get_index(x, y));
    }


    /// Set the value in global bin number @a ix
    void set_at_index(size_t i, const T& val) {
      check();
      values[i] = val;
    }

    /// Set the value in bin number pair @a (ix, iy)
    void set_at_index(size_t ix, size_t iy, const T& val) {
      set_at_index(global_index(ix, iy), val);
    }

    /// Set the value in the bin at position @a (x,y)
    void set_at(const TX& x, const TY& y, const T& val) {
      set_at_index(get_index(x,y), val);
    }


    /// Clear the bin contents (but leave the binning intact)
    void reset() {
      // binning.reset();
      values.clear();
      values.resize(num_bins());
      check();
    }

    /// Check consistency of the edges and values vectors
    void check() const {
      binning.check();
      if (values.size() < 1) throw std::length_error("There must be 1 or more bin values");
      if (binning.size() != values.size()) throw std::length_error("There must be one more bin edge than there are bin values");
    }


    /// The list of bin edges
    Binning2D<TX, TY> binning;

    /// The list of values
    std::vector<T> values;

  };


}
