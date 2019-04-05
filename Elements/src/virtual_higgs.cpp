//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Simple function for returning SM Higgs partial
///  and total widths as a function of virtuality,
///  as read from data files from CERN Yellow
///  Paper arXiv:1307.1347.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christoph Weniger
///          <c.weniger@uva.nl>
///  \date 2014 Dec
///
///  \author Pat Scott
///          <p.scott@imperial.ac.uk>
///  \date 2015 May
///
///  *********************************************

#include <map>
#include <vector>
#include <sstream>

#include "gambit/Elements/virtual_higgs.hpp"
#include "gambit/Utils/ascii_table_reader.hpp"
#include "gambit/cmake/cmake_variables.hpp"

namespace Gambit
{

  /// Higgs branching ratios and total width Gamma [GeV], as function of mass [GeV] (90 - 300 GeV)
  double virtual_SMHiggs_widths(str channel, double mh)
  {
    // Paths to files containing virtual Higgs width tables.
    const str virtualH_tabfile = GAMBIT_DIR "/Elements/data/Higgs_decay_1307.1347.dat";
    const str virtualH_highmass = GAMBIT_DIR "/Elements/data/Higgs_decay_multiTeV_supplement.dat";
    const str virtualH_lowmass = GAMBIT_DIR "/Elements/data/Higgs_decay_lowmass_supplement.dat";

    // Initialise, reading in the data tables and setting up the interpolators.
    static ASCIItableReader table(virtualH_tabfile);
    static ASCIItableReader table_highmass(virtualH_highmass);
    static ASCIItableReader table_lowmass(virtualH_lowmass);
    static std::map<std::string, daFunk::Funk> f_vs_mass;
    static std::map<std::string, daFunk::Funk> f_vs_mass_highmass;
    static std::map<std::string, daFunk::Funk> f_vs_mass_lowmass;
    static bool initialised = false;
    static double minmass, midmass_low, midmass_high, maxmass;
    const static std::vector<str> non_highmass_channels = initVector<std::string>("ss","gg","bb","mumu");
    const static std::vector<str> colnames = initVector<std::string>("mass",
     "bb", "bb+", "bb-", "tautau", "tautau+", "tautau-", "mumu", "mumu+", "mumu-",
     "ss", "ss+", "ss-", "cc", "cc+", "cc-", "tt", "tt+", "tt-", "gg", "gg+", "gg-",
     "gammagamma", "gammagamma+", "gammagamma-", "Zgamma", "Zgamma+", "Zgamma-",
     "WW", "WW+", "WW-", "ZZ", "ZZ+", "ZZ-", "Gamma", "Gamma+", "Gamma-");
    const static std::vector<str> colnames_extended = initVector<std::string>("mass",
     "bb", "tautau", "mumu", "ss", "cc", "tt", "gg", "gammagamma", "Zgamma",
     "WW", "ZZ", "Gamma");
    if (not initialised)
    {
      table.setcolnames(colnames);
      for (auto it = colnames.begin(); it != colnames.end(); it++)
      {
        f_vs_mass[*it] = daFunk::interp("mass", table["mass"], table[*it]);
      }
      table_highmass.setcolnames(colnames_extended);
      table_lowmass.setcolnames(colnames_extended);
      for (auto it = colnames_extended.begin(); it != colnames_extended.end(); it++)
      {
        f_vs_mass_highmass[*it] = daFunk::interp("mass", table_highmass["mass"], table_highmass[*it]);
        f_vs_mass_lowmass[*it] = daFunk::interp("mass", table_lowmass["mass"], table_lowmass[*it]);
      }
      minmass = table_lowmass["mass"][0];
      midmass_low = table["mass"][0];
      midmass_high = table_highmass["mass"][0];
      maxmass = table_highmass["mass"][table_highmass.getnrow()-1];
      if (table_lowmass["mass"][table_lowmass.getnrow()-1] != midmass_low)
        utils_error().raise(LOCAL_INFO, "low-mass and intermediate SM higgs tables do not meet cleanly.");
      if (table["mass"][table.getnrow()-1] != midmass_high)
        utils_error().raise(LOCAL_INFO, "intermediate and high-mass SM higgs tables do not meet cleanly.");
      initialised = true;
    }
		/*
    if (channel == "Sh")
    {
			return 0;
		}
		*/
		
    // Exit if the requested channel is unknown.
    if (std::find(colnames.begin(), colnames.end(), channel) == colnames.end())
    {
      std::stringstream msg;
      msg << "Unknown Higgs decay channel: " << channel << ".  Recognised channel codes are:";
      for (auto it = colnames.begin(); it != colnames.end(); it++) if (*it != "mass") msg << endl << "  " << *it;
      utils_error().raise(LOCAL_INFO, msg.str());
    }
    

    // Exit if the requested mass is out of range.
    if (mh < minmass or mh > maxmass)
    {
      std::stringstream msg;
      msg << "Requested Higgs virtuality is " << mh << "; allowed range is " << minmass << "--" << maxmass << " GeV!";
      utils_error().raise(LOCAL_INFO, msg.str());
    }

    // Retrieve the interpolated result.
    double f;
    if (mh <= midmass_low)
    {
      f = f_vs_mass_lowmass[channel]->bind("mass")->eval(mh);
    }
    else if (mh >= midmass_low and mh <= midmass_high)
    {
      f = f_vs_mass[channel]->bind("mass")->eval(mh);
    }
    else
    {
      if (std::find(non_highmass_channels.begin(), non_highmass_channels.end(), channel) != non_highmass_channels.end()) return 0.;
      f = f_vs_mass_highmass[channel]->bind("mass")->eval(mh);
    }
    return f;

  }

}
