//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  The Cutflow and Cutflows classes
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///          (andy.buckley@cern.ch)
///
///  *********************************************

#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "gambit/ColliderBit/Utils.hpp"


namespace Gambit
{
  namespace ColliderBit
  {

    using namespace std;


    /// A tracker of numbers & fractions of events passing sequential cuts
    struct Cutflow
    {

      /// @brief Default constructor
      ///
      /// Does nothing! Just to allow storage in STL containers and use as a member variable without using the init list
      Cutflow() {}

      /// Proper constructor
      Cutflow(const string& cfname, const vector<string>& cutnames)
        : name(cfname), ncuts(cutnames.size()), cuts(cutnames), counts(ncuts+1, 0), icurr(0)
      {  }

      /// @brief Fill the pre-cut counter
      void fillinit(double weight=1.)
      {
        counts[0] += weight;
        icurr = 1;
      }

      /// @brief Fill the @a {icut}'th post-cut counter, starting at icut=1 for first cut
      ///
      /// @note Returns the cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fill(size_t icut, bool cutresult=true, double weight=1.)
      {
        // if (icut == 0)
        //   throw RangeError("Cut number must be greater than 0");
        if (cutresult) counts.at(icut) += weight;
        icurr = icut + 1;
        return cutresult;
      }

      /// @brief Fill the @a {icut}'th post-cut counter, starting at icut=1 for first cut (cutvalue=true overload)
      ///
      /// This version exists to allow calling fill(i, weight) without the weight
      /// getting cast to a bool, or having to explicitly add a 'true' middle arg.
      ///
      /// @note Returns the cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fill(size_t icut, double weight)
      {
        return fill(icut, true, weight);
      }

      /// @brief Fill cut-state counters from an n-element results vector, starting at icut
      ///
      /// @note Returns the overall cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fill(size_t icut, const vector<bool>& cutresults, double weight=1.)
      {
        //   throw RangeError("Cut number must be greater than 0");
        // if (cutresults.size() > ncuts-icut)
        //   throw RangeError("Number of filled cut results needs to match the Cutflow construction");
        bool rtn = true;
        for (size_t i = 0; i < cutresults.size(); ++i)
          if (!fill(icut+i, cutresults[i], weight)) { rtn = false; break; }
        icurr = icut + cutresults.size();
        return rtn;
      }


      /// @brief Fill all cut-state counters from an Ncut-element results vector, starting at icut=1
      bool fillall(const vector<bool>& cutresults, double weight=1.)
      {
        // if (cutresults.size() != ncuts)
        //   throw RangeError("Number of filled cut results needs to match the Cutflow construction");
        // if (icut == 0) { fillinit(weight); icut = 1; }
        return fill(1, cutresults, weight);
      }

      /// @brief Fill the next post-cut counter
      ///
      /// @note Returns the cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fillnext(bool cutresult, double weight=1.)
      {
        return fill(icurr, cutresult, weight);
      }

      /// @brief Fill the next post-cut counter, assuming a true result
      ///
      /// @note Returns the cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fillnext(double weight=1.)
      {
        return fill(icurr, true, weight);
      }

      /// @brief Fill the next cut-state counters from an n-element results vector
      ///
      /// @note Returns the cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fillnext(const vector<bool>& cutresults, double weight=1.)
      {
        return fill(icurr, cutresults, weight);
      }


      /// @brief Fill the N trailing post-cut counters, when supplied with an N-element results vector
      ///
      /// The @a cutresults vector represents the boolean results of the last N cuts. This function
      /// allows mixing of cut-flow filling with higher-level analyze() function escapes such as
      /// the vetoEvent directive. The initial state (state 0) is not incremented.
      ///
      /// @deprecated Now prefer to use vector fillnext()
      ///
      /// @note Returns the overall cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool filltail(const vector<bool>& cutresults, double weight=1.)
      {
        return fill(ncuts+1-cutresults.size(), cutresults, weight);
      }

      /// Scale the cutflow weights by the given factor
      void scale(double factor)
      {
        for (double& x : counts) x *= factor;
      }

      /// Scale the cutflow weights so that the weight count after cut @a icut is @a norm
      void normalize(double norm, size_t icut=0)
      {
        scale(norm/counts.at(icut));
      }

      /// Create a string representation
      string str() const
      {
        using namespace std;
        stringstream ss;
        ss << fixed << std::setprecision(1) << counts.front();
        const size_t count0len = ss.str().length();
        ss.str("");
        ss << name << " cut-flow:\n";
        size_t maxnamelen = 0;
        for (const string& t : cuts)
          maxnamelen = max(t.length(), maxnamelen);
        ss << setw(maxnamelen+5) << "" << "   "
           << setw(count0len) << right << "Count" << "    "
           << setw(6) << right << "A_cumu" << "    "
           << setw(6) << right << "A_incr";
        for (size_t i = 0; i <= ncuts; ++i)
        {
          const int pcttot = (counts.front() == 0) ? -1 : round(100*counts.at(i)/double(counts.front()));
          const int pctinc = (i == 0 || counts.at(i-1) == 0) ? -1 : round(100*counts.at(i)/double(counts.at(i-1)));
          stringstream ss2;
          ss2 << fixed << setprecision(1) << counts.at(i);
          const string countstr = ss2.str(); ss2.str("");
          ss2 << fixed << setprecision(3) << pcttot << "%";
          const string pcttotstr = ss2.str(); ss2.str("");
          ss2 << fixed << setprecision(3) << pctinc << "%";
          const string pctincstr = ss2.str();
          ss << "\n"
             << setw(maxnamelen+5) << left << (i == 0 ? "" : "Pass "+cuts.at(i-1)) << "   "
             << setw(count0len) << right << countstr << "    "
             << setw(6) << right << (pcttot < 0 ? "- " : pcttotstr) << "    "
             << setw(6) << right << (pctinc < 0 ? "- " : pctincstr);
        }
        return ss.str();
      }

      /// Print string representation to a stream
      void print(std::ostream& os) const
      {
        os << str() << std::flush;
      }

      string name;
      size_t ncuts;
      vector<string> cuts;
      vector<double> counts;
      size_t icurr;

    };


    /// Print a Cutflow to a stream
    inline std::ostream& operator << (std::ostream& os, const Cutflow& cf)
    {
      return os << cf.str();
    }



    /// A container for several Cutflow objects, with some convenient batch access
    struct Cutflows
    {

      /// Do-nothing default constructor
      Cutflows() {  }

      /// Populating constructor
      Cutflows(const vector<Cutflow>& cutflows) : cfs(cutflows) {  }

      /// Append a provided Cutflow to the list
      void addCutflow(const Cutflow& cf)
      {
        cfs.push_back(cf);
      }

      /// Append a newly constructed Cutflow to the list
      void addCutflow(const string& cfname, const vector<string>& cutnames)
      {
        cfs.push_back(Cutflow(cfname, cutnames));
      }

      /// Access the @a i'th Cutflow
      Cutflow& operator [] (size_t i) { return cfs[i]; }
      /// Access the @a i'th Cutflow (const)
      const Cutflow& operator [] (size_t i) const { return cfs[i]; }

      /// Access the Cutflow whose name is @a name
      Cutflow& operator [] (const string& name)
      {
        for (Cutflow& cf : cfs)
          if (cf.name == name) return cf;
        // throw UserError("Requested cut-flow name '" + name + "' does not exist");
        throw 0;
      }
      /// Access the @a i'th Cutflow (const)
      const Cutflow& operator [] (const string& name) const
      {
        for (const Cutflow& cf : cfs)
          if (cf.name == name) return cf;
        // throw UserError("Requested cut-flow name '" + name + "' does not exist");
        throw 0;
      }

      /// Fill the pre-cuts state counter for all contained {Cutflow}s
      void fillinit(double weight=1.)
      {
        for (Cutflow& cf : cfs) cf.fillinit(weight);
      }

      /// @brief Fill the @a {icut}'th post-cut counter, starting at icut=1 for first cut, with the same result for all {Cutflow}s
      bool fill(size_t icut, bool cutresult=true, double weight=1.)
      {
        for (Cutflow& cf : cfs) cf.fill(icut, cutresult, weight);
        return cutresult;
      }

      /// @brief Fill the @a {icut}'th post-cut counter, starting at icut=1 for first cut, with the same result for all {Cutflow}s (cutresult=true overload)
      ///
      /// This version exists to allow calling fill(i, weight) without the weight
      /// getting cast to a bool, or having to explicitly add a 'true' middle arg.
      ///
      /// @note Returns the cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fill(size_t icut, double weight)
      {
        return fill(icut, true, weight);
      }

      /// @brief Fill cut-state counters from an n-element results vector, starting at icut
      ///
      /// @note Returns the overall cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fill(size_t icut, const vector<bool>& cutresults, double weight=1.)
      {
        bool rtn = true;
        for (Cutflow& cf : cfs) rtn = cf.fill(icut, cutresults, weight);
        return rtn;
      }


      /// @brief Fill all cut-state counters from an Ncut-element results vector, starting at icut=1
      bool fillall(const vector<bool>& cutresults, double weight=1.)
      {
        bool rtn = true;
        for (Cutflow& cf : cfs) rtn = cf.fillall(cutresults, weight);
        return rtn;
      }

      /// @brief Fill the next post-cut counter
      ///
      /// @note Returns the cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fillnext(bool cutresult, double weight=1.) {
        for (Cutflow& cf : cfs) cf.fillnext(cutresult, weight);
        return cutresult;
      }

      /// @brief Fill the next post-cut counter, assuming a true result
      ///
      /// @note Returns the cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fillnext(double weight=1.)
      {
        for (Cutflow& cf : cfs) cf.fillnext(weight);
        return true;
      }

      /// @brief Fill the next cut-state counters from an n-element results vector
      ///
      /// @note Returns the cut result to allow 'side-effect' cut-flow filling in an if-statement
      bool fillnext(const vector<bool>& cutresults, double weight=1.)
      {
        bool rtn = true;
        for (Cutflow& cf : cfs) rtn = cf.fillnext(cutresults, weight);
        return rtn;
      }


      /// Scale the contained {Cutflow}s by the given factor
      void scale(double factor)
      {
        for (Cutflow& cf : cfs) cf.scale(factor);
      }

      /// Scale the cutflow weights so that all the weight counts after cut @a icut are @a norm
      /// @todo Provide a version that takes a vector of norms?
      void normalize(double norm, size_t icut=0)
      {
        for (Cutflow& cf : cfs) cf.normalize(norm, icut);
      }

      /// Create a string representation
      string str() const
      {
        stringstream ss;
        for (const Cutflow& cf : cfs)
          ss << cf << "\n\n";
        return ss.str();
      }

      /// Print string representation to a stream
      void print(std::ostream& os) const
      {
        os << str() << std::flush;
      }


      vector<Cutflow> cfs;

    };


    /// Print a Cutflows to a stream
    inline std::ostream& operator << (std::ostream& os, const Cutflows& cfs)
    {
      return os << cfs.str();
    }


  }
}
