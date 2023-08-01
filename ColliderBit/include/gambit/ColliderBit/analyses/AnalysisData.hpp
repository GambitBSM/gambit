//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  AnalysisData struct.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  \author Andy Buckley
///          (andy.buckley@cern.ch)
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date often
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Feb
///
///  *********************************************

#pragma once

#include "gambit/Utils/begin_ignore_warnings_eigen.hpp"
#include "Eigen/Core"
#include "gambit/Utils/end_ignore_warnings.hpp"

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <limits>
#include <memory>
#include <iomanip>
#include <algorithm>
#include "gambit/ColliderBit/analyses/SignalRegionData.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    /// A container for the result of an analysis, potentially with many signal regions and correlations
    ///
    /// @todo Access by name?
    /// @todo Guarantee ordering?
    /// @todo How to combine covariance matrices -- require?
    struct AnalysisData
    {

      /// Default constructor
      AnalysisData()
      {
        clear();
      }

      /// Constructor with analysis name
      AnalysisData(const std::string& name) :
        analysis_name(name)
      {
        clear();
      }

      /// @brief Constructor from a list of SignalRegionData and an optional correlation (or covariance?) matrix
      ///
      /// If corrs is a null matrix (the default), this AnalysisData is to be interpreted as having no correlation
      /// information, and hence the likelihood calculation should use the single best-expected-limit SR.
      AnalysisData(const std::vector<SignalRegionData>& srds, const Eigen::MatrixXd& cov=Eigen::MatrixXd(),const std::string path="")
        : srdata(srds), srcov(cov), bkgjson_path(path)
      {
        check();
      }

      /// Clear the list of SignalRegionData, and nullify the covariance matrix
      /// @todo It'd be good to *not* have to re-enter most of the SRData and the covariance on every point: they don't change
      void clear()
      {
        for (auto& sr : srdata)
        {
          sr.n_sig_MC = 0;
          sr.n_sig_scaled = 0;
          sr.n_sig_MC_sys = 0;
        }
        srcov = Eigen::MatrixXd();
        bkgjson_path = "";
      }

      /// Number of analyses
      size_t size() const
      {
        // check();
        return srdata.size();
      }

      /// Is this container empty of signal regions?
      bool empty() const { return size() == 0; }

      /// Is there non-null correlation data?
      bool hasCorrs() const
      {
        // check(); // bjf> This was wrong! Needs to be !=, not ==
        return srcov.rows() != 0;
      }
      
      /// Is there non-null correlation data?
      bool hasFullLikes() const
      {
        return (!bkgjson_path.empty());
      }

      /// @brief Add a SignalRegionData
      /// @todo Allow naming the SRs?
      void add(const SignalRegionData& srd)
      {
        auto loc = srdata_identifiers.find(srd.sr_label);
        if (loc == srdata_identifiers.end())
        {
          // If the signal region doesn't exist in this object yet, add it
          srdata.push_back(srd);
          srdata_identifiers[srd.sr_label] = srdata.size() - 1;
        }
        else
        {
          // If it does, just update the signal count in the existing SignalRegionData object
          srdata[loc->second].n_sig_MC = srd.n_sig_MC;
        }
        check();
      }

      /// Check that the SRData list and the covariance matrix are consistent
      bool check() const
      {
        for (const SignalRegionData& srd : srdata) srd.check();
        assert(srcov.rows() == 0 || srcov.rows() == (int) srdata.size());
        return true;
      }

      bool event_gen_BYPASS = false;


      /// bjf> Experimental! But already useful for helping me convert the key
      /// numbers from these analyses to Python for the p-value calculuations.
      void pythonize_me() const;

      /// Analysis name
      std::string analysis_name;
      
      /// Access the i'th signal region's data
      SignalRegionData& operator[] (size_t i) { return srdata[i]; }
      /// Access the i'th signal region's data (const)
      const SignalRegionData& operator[] (size_t i) const { return srdata[i]; }

      /// Iterators (sugar for direct access to this->srdata)
      std::vector<SignalRegionData>::iterator begin() { return srdata.begin(); }
      std::vector<SignalRegionData>::const_iterator begin() const { return srdata.begin(); }
      std::vector<SignalRegionData>::iterator end() { return srdata.end(); }
      std::vector<SignalRegionData>::const_iterator end() const { return srdata.end(); }

      /// List of signal regions' data summaries
      std::vector<SignalRegionData> srdata;

      /// Map of names and indices of all entries in srdata, for easy lookup
      std::map<std::string, int> srdata_identifiers;

      /// Optional covariance matrix between SRs (0x0 null matrix = no correlation info)
      Eigen::MatrixXd srcov;
      
      /// FullLikes bkg json file path realtive to the GAMBIT directory
      std::string bkgjson_path;

    };


  }
}
