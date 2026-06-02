//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Lightweight 1D and 2D histogram classes for
///  ColliderBit analyses.  Follows the same design
///  pattern as the Cutflow / Cutflows classes:
///  header-only, weighted fill, runtime enable/disable,
///  scale, combine, and text representation.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pengxuan Zhu
///          (pengxuan.zhu@adelaide.edu.au)
///  \date 2025 May
///
///  *********************************************

#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Gambit
{
  namespace ColliderBit
  {

    // =========================================================================
    //  Histogram1D
    // =========================================================================

    /// A weighted 1D histogram with variable-width bins,
    /// under/overflow tracking, and sum-of-weights-squared
    /// error propagation.
    struct Histogram1D
    {

      // ----- Runtime enable / disable (shared with Histogram2D) -----

      static void set_check_histogram(bool enabled)
      {
        check_histogram_flag() = enabled;
      }

      static bool check_histogram()
      {
        return check_histogram_flag();
      }

      // ----- Data members -----

      std::string name;
      std::string x_label;

      std::vector<double> edges;   ///< N+1 bin edges for N bins (monotonically increasing)
      std::vector<double> counts;  ///< N bin contents (sum of weights)
      std::vector<double> sumw2;   ///< N sum-of-weights-squared per bin

      double underflow;
      double overflow;
      double underflow_sumw2;
      double overflow_sumw2;

      // ----- Constructors -----

      /// Default (no-op) constructor for STL containers
      Histogram1D()
        : underflow(0), overflow(0),
          underflow_sumw2(0), overflow_sumw2(0)
      {}

      /// Variable-width-bin constructor
      Histogram1D(const std::string& hname,
                  const std::vector<double>& bin_edges,
                  const std::string& xlabel = "")
        : name(hname), x_label(xlabel), edges(bin_edges),
          counts(bin_edges.size() > 1 ? bin_edges.size() - 1 : 0, 0.0),
          sumw2(bin_edges.size() > 1 ? bin_edges.size() - 1 : 0, 0.0),
          underflow(0), overflow(0),
          underflow_sumw2(0), overflow_sumw2(0)
      {
        assert(edges.size() >= 2);
        for (size_t i = 1; i < edges.size(); ++i)
          assert(edges[i] > edges[i - 1]);
      }

      /// Uniform-bin convenience constructor
      Histogram1D(const std::string& hname,
                  size_t nbins, double xlo, double xhi,
                  const std::string& xlabel = "")
        : name(hname), x_label(xlabel),
          edges(nbins + 1), counts(nbins, 0.0), sumw2(nbins, 0.0),
          underflow(0), overflow(0),
          underflow_sumw2(0), overflow_sumw2(0)
      {
        assert(nbins > 0);
        assert(xhi > xlo);
        const double width = (xhi - xlo) / static_cast<double>(nbins);
        for (size_t i = 0; i <= nbins; ++i)
          edges[i] = xlo + static_cast<double>(i) * width;
      }

      // ----- Fill -----

      /// Fill the histogram with value @a x and event weight @a weight.
      void fill(double x, double weight = 1.0)
      {
        if (!check_histogram()) return;

        const size_t bin = find_bin(x);
        if (bin == BIN_UNDERFLOW)
        {
          underflow += weight;
          underflow_sumw2 += weight * weight;
        }
        else if (bin == BIN_OVERFLOW)
        {
          overflow += weight;
          overflow_sumw2 += weight * weight;
        }
        else
        {
          counts[bin] += weight;
          sumw2[bin] += weight * weight;
        }
      }

      // ----- Scaling -----

      /// Scale all bin contents (and sumw2) by @a factor.
      /// After scaling, counts hold luminosity-scaled event counts.
      void scale(double factor)
      {
        const double f2 = factor * factor;
        for (size_t i = 0; i < counts.size(); ++i)
        {
          counts[i] *= factor;
          sumw2[i] *= f2;
        }
        underflow *= factor;
        overflow *= factor;
        underflow_sumw2 *= f2;
        overflow_sumw2 *= f2;
      }

      // ----- Combining -----

      /// Add the contents of another histogram to this one
      /// (for merging parallel runs or batch files).
      void combine(const Histogram1D& other)
      {
        assert(counts.size() == other.counts.size());
        for (size_t i = 0; i < counts.size(); ++i)
        {
          counts[i] += other.counts[i];
          sumw2[i] += other.sumw2[i];
        }
        underflow += other.underflow;
        overflow += other.overflow;
        underflow_sumw2 += other.underflow_sumw2;
        overflow_sumw2 += other.overflow_sumw2;
      }

      // ----- Accessors -----

      size_t nbins() const { return counts.size(); }

      double bin_center(size_t i) const
      {
        return 0.5 * (edges[i] + edges[i + 1]);
      }

      double bin_width(size_t i) const
      {
        return edges[i + 1] - edges[i];
      }

      double bin_error(size_t i) const
      {
        return std::sqrt(sumw2[i]);
      }

      double integral() const
      {
        double sum = 0.0;
        for (double c : counts) sum += c;
        return sum;
      }

      // ----- String representation -----

      std::string str() const
      {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2);
        ss << "Histogram1D \"" << name << "\"";
        if (!x_label.empty()) ss << " [" << x_label << "]";
        ss << "  (" << nbins() << " bins)\n";
        ss << "  underflow: " << underflow << "\n";

        size_t maxlen = 0;
        for (size_t i = 0; i < nbins(); ++i)
        {
          std::stringstream tmp;
          tmp << "[" << edges[i] << ", " << edges[i + 1] << ")";
          maxlen = std::max(maxlen, tmp.str().size());
        }

        for (size_t i = 0; i < nbins(); ++i)
        {
          std::stringstream label;
          label << "[" << edges[i] << ", " << edges[i + 1] << ")";
          ss << "  " << std::setw(static_cast<int>(maxlen)) << std::left << label.str()
             << "  " << std::setw(10) << std::right << counts[i]
             << " +/- " << std::setw(8) << bin_error(i)
             << "\n";
        }
        ss << "  overflow:  " << overflow << "\n";
        ss << "  integral:  " << integral() << "\n";
        return ss.str();
      }

      void print(std::ostream& os) const { os << str() << std::flush; }

    private:

      static constexpr size_t BIN_UNDERFLOW = static_cast<size_t>(-2);
      static constexpr size_t BIN_OVERFLOW = static_cast<size_t>(-1);

      /// Find the bin index for value @a x.
      /// Returns BIN_UNDERFLOW / BIN_OVERFLOW for out-of-range values.
      size_t find_bin(double x) const
      {
        if (x < edges.front()) return BIN_UNDERFLOW;
        if (x >= edges.back()) return BIN_OVERFLOW;
        // upper_bound returns iterator to first edge > x
        auto it = std::upper_bound(edges.begin(), edges.end(), x);
        return static_cast<size_t>(it - edges.begin()) - 1;
      }

      static bool& check_histogram_flag()
      {
        static bool enabled = true;
        return enabled;
      }
    };

    /// Print a Histogram1D to a stream
    inline std::ostream& operator<<(std::ostream& os, const Histogram1D& h)
    {
      return os << h.str();
    }


    // =========================================================================
    //  Histogram2D
    // =========================================================================

    /// A weighted 2D histogram with variable-width bins,
    /// overflow tracking, and sum-of-weights-squared error
    /// propagation.
    struct Histogram2D
    {

      // ----- Data members -----

      std::string name;
      std::string x_label;
      std::string y_label;

      std::vector<double> x_edges;
      std::vector<double> y_edges;

      std::vector<std::vector<double>> counts;  ///< [nx][ny]
      std::vector<std::vector<double>> sumw2;   ///< [nx][ny]

      double overflow_total;
      double overflow_total_sumw2;

      // ----- Constructors -----

      /// Default constructor
      Histogram2D()
        : overflow_total(0), overflow_total_sumw2(0)
      {}

      /// Variable-width-bin constructor
      Histogram2D(const std::string& hname,
                  const std::vector<double>& xedges,
                  const std::vector<double>& yedges,
                  const std::string& xlabel = "",
                  const std::string& ylabel = "")
        : name(hname), x_label(xlabel), y_label(ylabel),
          x_edges(xedges), y_edges(yedges),
          overflow_total(0), overflow_total_sumw2(0)
      {
        assert(x_edges.size() >= 2);
        assert(y_edges.size() >= 2);
        const size_t nx = x_edges.size() - 1;
        const size_t ny = y_edges.size() - 1;
        counts.assign(nx, std::vector<double>(ny, 0.0));
        sumw2.assign(nx, std::vector<double>(ny, 0.0));
      }

      /// Uniform-bin convenience constructor
      Histogram2D(const std::string& hname,
                  size_t nxbins, double xlo, double xhi,
                  size_t nybins, double ylo, double yhi,
                  const std::string& xlabel = "",
                  const std::string& ylabel = "")
        : name(hname), x_label(xlabel), y_label(ylabel),
          x_edges(nxbins + 1), y_edges(nybins + 1),
          overflow_total(0), overflow_total_sumw2(0)
      {
        assert(nxbins > 0 && nybins > 0);
        assert(xhi > xlo && yhi > ylo);
        const double xw = (xhi - xlo) / static_cast<double>(nxbins);
        const double yw = (yhi - ylo) / static_cast<double>(nybins);
        for (size_t i = 0; i <= nxbins; ++i)
          x_edges[i] = xlo + static_cast<double>(i) * xw;
        for (size_t j = 0; j <= nybins; ++j)
          y_edges[j] = ylo + static_cast<double>(j) * yw;
        counts.assign(nxbins, std::vector<double>(nybins, 0.0));
        sumw2.assign(nxbins, std::vector<double>(nybins, 0.0));
      }

      // ----- Fill -----

      void fill(double x, double y, double weight = 1.0)
      {
        if (!Histogram1D::check_histogram()) return;

        const size_t ix = find_x_bin(x);
        const size_t iy = find_y_bin(y);
        const size_t nx = x_edges.size() - 1;
        const size_t ny = y_edges.size() - 1;

        if (ix < nx && iy < ny)
        {
          counts[ix][iy] += weight;
          sumw2[ix][iy] += weight * weight;
        }
        else
        {
          overflow_total += weight;
          overflow_total_sumw2 += weight * weight;
        }
      }

      // ----- Scaling -----

      void scale(double factor)
      {
        const double f2 = factor * factor;
        for (size_t ix = 0; ix < nx_bins(); ++ix)
        {
          for (size_t iy = 0; iy < ny_bins(); ++iy)
          {
            counts[ix][iy] *= factor;
            sumw2[ix][iy] *= f2;
          }
        }
        overflow_total *= factor;
        overflow_total_sumw2 *= f2;
      }

      // ----- Combining -----

      void combine(const Histogram2D& other)
      {
        assert(nx_bins() == other.nx_bins() && ny_bins() == other.ny_bins());
        for (size_t ix = 0; ix < nx_bins(); ++ix)
        {
          for (size_t iy = 0; iy < ny_bins(); ++iy)
          {
            counts[ix][iy] += other.counts[ix][iy];
            sumw2[ix][iy] += other.sumw2[ix][iy];
          }
        }
        overflow_total += other.overflow_total;
        overflow_total_sumw2 += other.overflow_total_sumw2;
      }

      // ----- Accessors -----

      size_t nx_bins() const { return counts.size(); }
      size_t ny_bins() const { return counts.empty() ? 0 : counts[0].size(); }

      double bin_error(size_t ix, size_t iy) const
      {
        return std::sqrt(sumw2[ix][iy]);
      }

      double integral() const
      {
        double sum = 0.0;
        for (size_t ix = 0; ix < nx_bins(); ++ix)
          for (size_t iy = 0; iy < ny_bins(); ++iy)
            sum += counts[ix][iy];
        return sum;
      }

      // ----- String representation -----

      std::string str() const
      {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2);
        ss << "Histogram2D \"" << name << "\"";
        if (!x_label.empty()) ss << " x=[" << x_label << "]";
        if (!y_label.empty()) ss << " y=[" << y_label << "]";
        ss << "  (" << nx_bins() << " x " << ny_bins() << " bins)\n";
        ss << "  integral: " << integral()
           << ", overflow: " << overflow_total << "\n";
        return ss.str();
      }

      void print(std::ostream& os) const { os << str() << std::flush; }

    private:

      size_t find_x_bin(double x) const
      {
        if (x < x_edges.front()) return x_edges.size(); // out of range
        if (x >= x_edges.back()) return x_edges.size();
        auto it = std::upper_bound(x_edges.begin(), x_edges.end(), x);
        return static_cast<size_t>(it - x_edges.begin()) - 1;
      }

      size_t find_y_bin(double y) const
      {
        if (y < y_edges.front()) return y_edges.size();
        if (y >= y_edges.back()) return y_edges.size();
        auto it = std::upper_bound(y_edges.begin(), y_edges.end(), y);
        return static_cast<size_t>(it - y_edges.begin()) - 1;
      }
    };

    /// Print a Histogram2D to a stream
    inline std::ostream& operator<<(std::ostream& os, const Histogram2D& h)
    {
      return os << h.str();
    }


    // =========================================================================
    //  Histograms (container)
    // =========================================================================

    /// A container for Histogram1D and Histogram2D objects,
    /// with batch scale / combine operations.
    struct Histograms
    {

      /// Default constructor
      Histograms() {}

      /// Populating constructor
      Histograms(const std::vector<Histogram1D>& h1ds,
                 const std::vector<Histogram2D>& h2ds)
        : histos1d(h1ds), histos2d(h2ds)
      {}

      // ----- Add histograms -----

      void addHistogram(const Histogram1D& h)
      {
        histos1d.push_back(h);
      }

      void addHistogram(const std::string& hname,
                        const std::vector<double>& bin_edges,
                        const std::string& xlabel = "")
      {
        histos1d.push_back(Histogram1D(hname, bin_edges, xlabel));
      }

      void addHistogram(const std::string& hname,
                        size_t nbins, double xlo, double xhi,
                        const std::string& xlabel = "")
      {
        histos1d.push_back(Histogram1D(hname, nbins, xlo, xhi, xlabel));
      }

      void addHistogram(const Histogram2D& h)
      {
        histos2d.push_back(h);
      }

      // ----- Access by index -----

      Histogram1D& h1d(size_t i) { return histos1d[i]; }
      const Histogram1D& h1d(size_t i) const { return histos1d[i]; }

      Histogram2D& h2d(size_t i) { return histos2d[i]; }
      const Histogram2D& h2d(size_t i) const { return histos2d[i]; }

      // ----- Access by name -----

      Histogram1D& h1d(const std::string& hname)
      {
        for (Histogram1D& h : histos1d)
          if (h.name == hname) return h;
        throw std::runtime_error("Histogram1D '" + hname + "' not found.");
      }

      const Histogram1D& h1d(const std::string& hname) const
      {
        for (const Histogram1D& h : histos1d)
          if (h.name == hname) return h;
        throw std::runtime_error("Histogram1D '" + hname + "' not found.");
      }

      Histogram2D& h2d(const std::string& hname)
      {
        for (Histogram2D& h : histos2d)
          if (h.name == hname) return h;
        throw std::runtime_error("Histogram2D '" + hname + "' not found.");
      }

      const Histogram2D& h2d(const std::string& hname) const
      {
        for (const Histogram2D& h : histos2d)
          if (h.name == hname) return h;
        throw std::runtime_error("Histogram2D '" + hname + "' not found.");
      }

      // ----- Batch operations -----

      void scale(double factor)
      {
        for (Histogram1D& h : histos1d) h.scale(factor);
        for (Histogram2D& h : histos2d) h.scale(factor);
      }

      void combine(const Histograms& other)
      {
        // If this container is empty, initialize from the other
        if (histos1d.empty() && histos2d.empty())
        {
          histos1d = other.histos1d;
          histos2d = other.histos2d;
          return;
        }

        if (histos1d.size() != other.histos1d.size() ||
            histos2d.size() != other.histos2d.size())
        {
          throw std::runtime_error("Cannot combine Histograms containers of different sizes.");
        }

        for (size_t i = 0; i < histos1d.size(); ++i)
          histos1d[i].combine(other.histos1d[i]);
        for (size_t i = 0; i < histos2d.size(); ++i)
          histos2d[i].combine(other.histos2d[i]);
      }

      // ----- String representation -----

      std::string str() const
      {
        std::stringstream ss;
        for (const Histogram1D& h : histos1d) ss << h << "\n";
        for (const Histogram2D& h : histos2d) ss << h << "\n";
        return ss.str();
      }

      void print(std::ostream& os) const { os << str() << std::flush; }

      // ----- Data -----

      std::vector<Histogram1D> histos1d;
      std::vector<Histogram2D> histos2d;
    };

    /// Print Histograms to a stream
    inline std::ostream& operator<<(std::ostream& os, const Histograms& hs)
    {
      return os << hs.str();
    }

  } // namespace ColliderBit
} // namespace Gambit
