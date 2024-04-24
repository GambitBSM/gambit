//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author A.S. Woodcock
///          (alex.woodcock@outlook.com)
///  \date   2023
///
///  *********************************************


#ifndef __coupling_table_hpp__
#define __coupling_table_hpp__

#include "gambit/Elements/spectrum.hpp"

#include <vector>
#include <string>
#include <complex>
#include <map>
#include <ostream>

namespace Gambit
{
  struct ComparitorStruct
  {
    bool operator()(const std::vector<std::string>& a, const std::vector<std::string>& b) const;
  };
  

  class CouplingTable
  {
    private:


    public: // data

      // helper function to update the coupling map
      using CalcFunc = std::function<void(const Spectrum&, CouplingTable&)>;
      CalcFunc calculator;

      // a copy of the full spectrum; needed for running the couplings
      Spectrum spectrum;

      // indicates whether we should update coupling table upon next access
      bool needsRecalculating = true;

      // map of <particle-names> --- coupling pairs
      using CouplingMap = std::map<std::vector<std::string>, std::complex<double>, ComparitorStruct>;
      CouplingMap table;

    public: // functions

      void init(const Spectrum& spec, const CalcFunc calc);

      // force an update of the table; only needed if you want to access the table directly
      void update();

      // insert coupling for the given particles
      void insert(const std::vector<std::string>& particles, const std::complex<double> coupling);

      // get coupling of the given particles
      std::complex<double> get(const std::vector<std::string>& particles);
      std::complex<double> getSafe(const std::vector<std::string>& particles) const;

      // run coupling table to the given scale
      void runToScale(const double scale);

  };


  std::map<std::string,double> to_map(const CouplingTable& tbl);

  std::ostream& operator<< (std::ostream &os, const CouplingTable &tbl);

}

#endif // __coupling_table_hpp__
