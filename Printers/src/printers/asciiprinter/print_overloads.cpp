//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ASCII printer print function overloads.
///  Add a new overload of the _print function
///  in this file if you want to be able to print
///  a new type.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2013 Jul, Sep, 2014 Jan
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Jan
///  \date 2017 Mar
///
///  *********************************************

#include "gambit/Printers/printers/asciiprinter.hpp"

namespace Gambit
{

  namespace Printers
  {

    /// @{ PRINT FUNCTIONS
    /// Need to define one of these for every type we want to print!
    /// Could use macros again to generate identical print functions
    /// for all types that have a << operator already defined.

    /// Template for print functions of "simple" types
    template<class T>
    void asciiPrinter::template_print(T const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    {
      std::vector<double> vdvalue(1,value); // For now everything has to end up as a vector of doubles
      std::vector<std::string> labels(1,label);
      addtobuffer(vdvalue,labels,IDcode,thread,pointID);
    }

    /// Template for print functions of vectors of "simple" types
    template<class T>
    void asciiPrinter::template_print_vec(std::vector<T> const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    {
      std::vector<std::string> labels;
      std::vector<double> d_values; // Values need to be converted to doubles for printing with asciiPrinter.
      labels.reserve(value.size());
      d_values.reserve(value.size());
      for(unsigned int i=0;i<value.size();i++)
      {
        // Might want to find some way to avoid doing this every single loop, seems kind of wasteful.
        std::stringstream ss;
        ss<<label<<"["<<i<<"]";
        labels.push_back(ss.str());
        d_values.push_back(value.at(i)); // Convert to double
      }
      addtobuffer(d_values,labels,IDcode,thread,pointID);
    }

    /// Macros to add all the simple print functions that just use the above templates
    #define ASIMPLEPRINT(r,data,elem) \
      void asciiPrinter::_print(elem const& value, const std::string& label, \
                           const int IDcode, const uint rank, \
                           const ulong pointID) \
      { \
        template_print(value,label,IDcode,rank,pointID); \
      }
    #define ASIMPLEPRINT_VEC(r,data,elem) \
      void asciiPrinter::_print(elem const& value, const std::string& label, \
                           const int IDcode, const uint rank, \
                           const ulong pointID) \
      { \
        template_print_vec(value,label,IDcode,rank,pointID); \
      }

    #define ADD_ASCII_SIMPLE_PRINTS(TYPES) BOOST_PP_SEQ_FOR_EACH(ASIMPLEPRINT, _, TYPES)
    #define ADD_ASCII_VECTOR_PRINTS(TYPES) BOOST_PP_SEQ_FOR_EACH(ASIMPLEPRINT_VEC, _, TYPES)
    ADD_ASCII_SIMPLE_PRINTS(SCANNER_SIMPLE_TYPES)
    ADD_ASCII_VECTOR_PRINTS(SCANNER_VECTOR_TYPES)

    void asciiPrinter::_print(map_str_dbl const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    {
      std::vector<std::string> names;
      std::vector<double> vdvalue;
      names.reserve(value.size());
      vdvalue.reserve(value.size());
      for (map_str_dbl::const_iterator it = value.begin(); it != value.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first;
        names.push_back( ss.str() );
        vdvalue.push_back( it->second );
      }
      addtobuffer(vdvalue,names,IDcode,thread,pointID);
    }

    void asciiPrinter::_print(ModelParameters const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      std::map<std::string, double> parameter_map = value.getValues();
      _print(parameter_map, label, vID, mpirank, pointID);
    }

    void asciiPrinter::_print(triplet<double> const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
    {
      std::map<std::string, double> m;
      m["central"] = value.central;
      m["lower"] = value.lower;
      m["upper"] = value.upper;
      _print(m, label, vID, mpirank, pointID);
    }

    void asciiPrinter::_print(map_intpair_dbl const& value, const std::string& label, const int IDcode, const uint thread, const ulong pointID)
    {
      std::vector<std::string> channels;
      std::vector<double> vdvalue;
      channels.reserve(value.size());
      vdvalue.reserve(value.size());
      for (map_intpair_dbl::const_iterator it = value.begin(); it != value.end(); it++)
      {
        std::stringstream ss;
        ss<<label<<"::"<<it->first.first<<it->first.second;
        channels.push_back( ss.str() );
        vdvalue.push_back( it->second );
      }
      addtobuffer(vdvalue,channels,IDcode,thread,pointID);
    }

    #ifndef SCANNER_STANDALONE // All the types inside ASCII_MODULE_BACKEND_TYPES need to go inside this def guard.

      void asciiPrinter::_print(DM_nucleon_couplings const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        m["Gp_SI"] = value.gps;
        m["Gn_SI"] = value.gns;
        m["Gp_SD"] = value.gpa;
        m["Gn_SD"] = value.gna;
        _print(m, label, vID, mpirank, pointID);
      }

      void asciiPrinter::_print(DM_nucleon_couplings_fermionic_HP const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        m["Gp_SI"] = value.gps;
        m["Gn_SI"] = value.gns;
        m["Gp_q2"] = value.gp_q2;
        m["Gn_q2"] = value.gn_q2;
        _print(m, label, vID, mpirank, pointID);
      }

      void asciiPrinter::_print(Flav_KstarMuMu_obs const& value, const std::string& label, const int vID, const unsigned int mpirank, const unsigned long pointID)
      {
        std::map<std::string, double> m;
        std::ostringstream bins;
        bins << value.q2_min << "_" << value.q2_max;
        m["BR_"+bins.str()] = value.BR;
        m["AFB_"+bins.str()] = value.AFB;
        m["FL_"+bins.str()] = value.FL;
        m["S3_"+bins.str()] = value.S3;
        m["S4_"+bins.str()] = value.S4;
        m["S5_"+bins.str()] = value.S5;
        m["S7_"+bins.str()] = value.S7;
        m["S8_"+bins.str()] = value.S8;
        m["S9_"+bins.str()] = value.S9;
        _print(m, label, vID, mpirank, pointID);
      }

    #endif

    /// @}

  }
}
