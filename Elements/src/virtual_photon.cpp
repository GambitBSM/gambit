//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Simple function for returning the cross section ratio 
///  R = sigma(e+e- -> hadrons)/sigma(e+e- -> mu+mu-)
///  as a function of the photon virtuality,
///  as read from data files from the PDG 
///  https://pdg.lbl.gov/2020/hadronic-xsections/hadron.html
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Felix Kahlhoefer
///  2022 May
///
///  *********************************************

#include <map>
#include <vector>
#include <sstream>

#include "gambit/Elements/virtual_photon.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/cmake/cmake_variables.hpp"

namespace Gambit
{
  /// Hadronic cross section ratio as function of centre-of-mass energy [GeV] (0.3 - 188 GeV)
  double hadronic_cross_section_ratio(double sqrts, bool smooth)
  {
    // Path to file containing cross section ratio tables.
    const str R_tabfile_raw = GAMBIT_DIR "/Elements/data/rpp2020-hadronicrpp_page1001_removed-duplicates.dat";
    // Path to file containing cross section ratio tables.
    const str R_tabfile_smooth = GAMBIT_DIR "/Elements/data/darkcast_hadronicrpp.dat";

    // Initialise, reading in the data tables and setting up the interpolators.
    static ASCIItableReader table = (smooth)? ASCIItableReader(R_tabfile_smooth): ASCIItableReader(R_tabfile_raw);
    static std::map<std::string, daFunk::Funk> R_vs_sqrts;
    static bool initialised = false;
    static double minsqrts, maxsqrts;
    const static std::vector<str> colnames = initVector<std::string>("sqrts", "R");
    if (not initialised)
    {
      table.setcolnames(colnames);
      for (auto it = colnames.begin(); it != colnames.end(); it++)
      {
        R_vs_sqrts[*it] = daFunk::interp("sqrts", table["sqrts"], table[*it]);
      }
      minsqrts = table["sqrts"][0];
      maxsqrts = table["sqrts"][table.getnrow()-1];
      initialised = true;
    }    

    // Exit if the requested mass is out of range.
    if (sqrts < minsqrts)
    {
      return 0;
    }

    if (sqrts > maxsqrts)
    {
      std::stringstream msg;
      msg << "Requested cross section ratio for sqrt(s) = " << sqrts << "; allowed range is sqrt(s) < " << maxsqrts << " GeV!";
      utils_error().raise(LOCAL_INFO, msg.str());
    }

    // Retrieve the interpolated result.
    double f;
    f = R_vs_sqrts["R"]->bind("sqrts")->eval(sqrts);
    return f;

  }

}
