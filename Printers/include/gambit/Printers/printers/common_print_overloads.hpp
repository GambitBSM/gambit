//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Printer overloads that do not differ from
///  printer to printer in the way they utilise
///  existing printer abilities.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Sept
///
///  *********************************************

#pragma once

#include "gambit/Utils/stream_overloads.hpp"

namespace Gambit
{

  namespace Printers
  {

    /// Macro to call to activate a specific common print overload
    #define USE_COMMON_PRINT_OVERLOAD(PRINTER, TYPE)                                                                                             \
    void PRINTER :: _print (TYPE const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID) \
    { _common_print<PRINTER>(*this,value,label,vID,mpirank,pointID); }

    /// Common print overload template
    template<typename P, typename T>
    void _common_print(P&, T const&, const std::string&, const int, const unsigned int, const unsigned long);

    /// Vector-of-doubles print overload
    template<typename P>
    void _common_print(P& printer, std::vector<double> const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      for(unsigned int i=0;i<value.size();i++)
      {
        std::stringstream ss;
        ss<<label<<"["<<i<<"]";
        printer._print(value[i],ss.str(),vID,mpirank,pointID);
      }
    }

    /// String-to-double map print overload
    template<typename P>
    void _common_print(P& printer, const map_const_str_dbl& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      for (map_const_str_dbl::const_iterator
           it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        printer._print(it->second,ss.str(),vID,mpirank,pointID);
      }
    }
    template<typename P>
    void _common_print(P& printer, const map_str_dbl& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      for (map_str_dbl::const_iterator
           it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        printer._print(it->second,ss.str(),vID,mpirank,pointID);
      }
    }

    /// String-to-map print overload (where map is string-to-double)
    template<typename P>
    void _common_print(P& printer, const map_const_str_map_const_str_dbl& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      for (map_const_str_map_const_str_dbl::const_iterator
           it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        printer._print(it->second,ss.str(),vID,mpirank,pointID);
      }
    }
    template<typename P>
    void _common_print(P& printer, const map_str_map_str_dbl& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      for (map_str_map_str_dbl::const_iterator
           it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        printer._print(it->second,ss.str(),vID,mpirank,pointID);
      }
    }

    /// String-to-string map print overload
    template<typename P>
    void _common_print(P& printer, const map_str_str& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      for (std::map<std::string, std::string>::const_iterator
           it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first<<":"<<it->second;
        printer._print(0,ss.str(),vID,mpirank,pointID);
      }
    }

    /// Integer pair-to-double map print overload
    template<typename P>
    void _common_print(P& printer, map_intpair_dbl const& map, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      for (map_intpair_dbl::const_iterator it = map.begin(); it != map.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        printer._print(it->second,ss.str(),vID,mpirank,pointID);
      }
    }

    /// ModelParameters print overload
    template<typename P>
    void _common_print(P& printer, ModelParameters const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      std::map<std::string, double> parameter_map = value.getValues();
      printer._print(parameter_map, label, vID, mpirank, pointID);
    }

    /// Triplet print overload
    template<typename P>
    void _common_print(P& printer, triplet<double> const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      std::map<std::string, double> m;
      m["central"] = value.central;
      m["lower"] = value.lower;
      m["upper"] = value.upper;
      printer._print(m, label, vID, mpirank, pointID);
    }

    #ifndef SCANNER_STANDALONE

      /// DM-nucleon coupling print overload
      template<typename P>
      void _common_print(P& printer, DM_nucleon_couplings const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        m["Gp_SI"] = value.gps;
        m["Gn_SI"] = value.gns;
        m["Gp_SD"] = value.gpa;
        m["Gn_SD"] = value.gna;
        printer._print(m, label, vID, mpirank, pointID);
      }

      /// Generic flavour prediction print overload
      template<typename P>
      void _common_print(P& printer, flav_prediction const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        printer._print(value.central_values, label + "::central", vID, mpirank, pointID);
        printer._print(value.covariance, label + "::covariance", vID, mpirank, pointID);
      }

      /// BBN observables print overload
      template<typename P>
      void _common_print(P& printer, BBN_container const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        for (const str& i : value.get_active_isotopes())
        {
          int index = value.get_abund_map().at(i);
          m[i] = value.get_BBN_abund(index);
          m[i+"::1sigma_err"] = sqrt(value.get_BBN_covmat(index, index));
        }
        printer._print(m, label, vID, mpirank, pointID);
      }

    #endif

  }

}
