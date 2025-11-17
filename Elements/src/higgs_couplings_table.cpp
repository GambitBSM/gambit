//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Lightweight higgs partial widths container
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016 Sep
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2024 Feb
///
///  *********************************************

#include "gambit/Elements/higgs_couplings_table.hpp"


namespace Gambit
{

  /// Set the number of neutral Higgses
  void HiggsCouplingsTable::set_n_neutral_higgs(int n)
  {
    n_neutral_higgses = n;
    neutral_decays_SM_array.resize(n);
    neutral_decays_array.resize(n);
    CP.resize(n);
    C_WW.resize(n);
    C_ZZ.resize(n);
    C_tt2.resize(n);
    C_bb2.resize(n);
    C_cc2.resize(n);
    C_tautau2.resize(n);
    C_gaga2.resize(n);
    C_gg2.resize(n);
    C_mumu2.resize(n);
    C_Zga2.resize(n);
    C_ss2.resize(n);
    C_hiZ.resize(n);
    for (int i = 0; i < n; i++) C_hiZ[i].resize(n);
    C_tt_s.resize(n);
    C_tt_p.resize(n);
    C_bb_s.resize(n);
    C_bb_p.resize(n);
    C_cc_s.resize(n);
    C_cc_p.resize(n);
    C_ss_s.resize(n);
    C_ss_p.resize(n);
    C_tautau_s.resize(n);
    C_tautau_p.resize(n);
    C_mumu_s.resize(n);
    C_mumu_p.resize(n);

  }

  /// Set the number of charged Higgses
  void HiggsCouplingsTable::set_n_charged_higgs(int n)
  {
    n_charged_higgses = n;
    charged_decays_array.resize(n);
  }

  /// Retrieve number of neutral higgses
  int HiggsCouplingsTable::get_n_neutral_higgs() const { return n_neutral_higgses; }

  /// Retrieve number of charged higgses
  int HiggsCouplingsTable::get_n_charged_higgs() const { return n_charged_higgses; }

  /// Set all effective couplings to 1
  void HiggsCouplingsTable::set_effective_couplings_to_unity()
  {
    for (int i = 0; i < n_neutral_higgses; i++)
    {
      C_WW[i] = 1.0;
      C_ZZ[i] = 1.0;
      C_tt2[i] = 1.0;
      C_bb2[i] = 1.0;
      C_cc2[i] = 1.0;
      C_tautau2[i] = 1.0;
      C_gaga2[i] = 1.0;
      C_gg2[i] = 1.0;
      C_mumu2[i] = 1.0;
      C_Zga2[i] = 1.0;
      C_ss2[i] = 1.0;
      for(int j = 0; j < n_neutral_higgses; j++) C_hiZ[i][j] = 1.0;
      C_tt_s[i] = 1.0;
      C_tt_p[i] = 1.0;
      C_bb_s[i] = 1.0;
      C_bb_p[i] = 1.0;
      C_cc_s[i] = 1.0;
      C_cc_p[i] = 1.0;
      C_ss_s[i] = 1.0;
      C_ss_p[i] = 1.0;
      C_tautau_s[i] = 1.0;
      C_tautau_p[i] = 1.0;
      C_mumu_s[i] = 1.0;
      C_mumu_p[i] = 1.0;
    }
  }

  /// Assign SM decay entries to neutral higgses
  void HiggsCouplingsTable::set_neutral_decays_SM(int index, const str& name, const DecayTable::Entry& entry)
  {
    if (index > n_neutral_higgses - 1) utils_error().raise(LOCAL_INFO, "Requested index beyond n_neutral_higgses.");
    neutral_decays_SM_array[index] = &entry;
    neutral_decays_SM_map.insert(std::pair<str, const DecayTable::Entry&>(name,entry));
  }

  /// Assign decay entries to neutral higgses
  void HiggsCouplingsTable::set_neutral_decays(int index, const str& name, const DecayTable::Entry& entry)
  {
    if (index > n_neutral_higgses - 1) utils_error().raise(LOCAL_INFO, "Requested index beyond n_neutral_higgses.");
    neutral_decays_array[index] = &entry;
    neutral_decays_map.insert(std::pair<str, const DecayTable::Entry&>(name,entry));
  }

  /// Assign decay entries to charged higgses
  void HiggsCouplingsTable::set_charged_decays(int index, const str& name, const DecayTable::Entry& entry)
  {
    if (index > n_charged_higgses - 1) utils_error().raise(LOCAL_INFO, "Requested index beyond n_charged_higgses.");
    charged_decays_array[index] = &entry;
    charged_decays_map.insert(std::pair<str, const DecayTable::Entry&>(name,entry));
  }

  /// Assign decay entries to top
  void HiggsCouplingsTable::set_t_decays(const DecayTable::Entry& entry) { t_decays = &entry; }

  /// Retrieve SM decays of all neutral higgses
  const std::vector<const DecayTable::Entry*>& HiggsCouplingsTable::get_neutral_decays_SM_array() const
  {
    return neutral_decays_SM_array;
  }

  /// Retrieve SM decays of a specific neutral Higgs, by index
  const DecayTable::Entry& HiggsCouplingsTable::get_neutral_decays_SM(int index) const
  {
    if (index > n_neutral_higgses - 1) utils_error().raise(LOCAL_INFO, "Requested index beyond n_neutral_higgses.");
    return *neutral_decays_SM_array[index];
  }

  /// Retrieve SM decays of a specific neutral Higgs, by name
  const DecayTable::Entry& HiggsCouplingsTable::get_neutral_decays_SM(const str& name) const
  {
    if (neutral_decays_SM_map.find(name) == neutral_decays_SM_map.end()) utils_error().raise(LOCAL_INFO, "Requested higgs not found.");
    return neutral_decays_SM_map.at(name);
  }

  /// Retrieve decays of all neutral higgses
  const std::vector<const DecayTable::Entry*>& HiggsCouplingsTable::get_neutral_decays_array() const
  {
    return neutral_decays_array;
  }

  /// Retrieve decays of a specific neutral Higgs, by index
  const DecayTable::Entry& HiggsCouplingsTable::get_neutral_decays(int index) const
  {
    if (index > n_neutral_higgses - 1) utils_error().raise(LOCAL_INFO, "Requested index beyond n_neutral_higgses.");
    return *neutral_decays_array[index];
  }

  /// Retrieve decays of a specific neutral Higgs, by name
  const DecayTable::Entry& HiggsCouplingsTable::get_neutral_decays(const str& name) const
  {
    if (neutral_decays_map.find(name) == neutral_decays_map.end()) utils_error().raise(LOCAL_INFO, "Requested higgs not found.");
    return neutral_decays_map.at(name);
  }

  /// Retrieve decays of all charged higgses
  const std::vector<const DecayTable::Entry*>& HiggsCouplingsTable::get_charged_decays_array() const
  {
    return charged_decays_array;
  }

  /// Retrieve decays of a specific charged Higgs, by index
  const DecayTable::Entry& HiggsCouplingsTable::get_charged_decays(int index) const
  {
    if (index > n_charged_higgses - 1) utils_error().raise(LOCAL_INFO, "Requested index beyond n_charged_higgses.");
    return *charged_decays_array[index];
  }

  /// Retrieve decays of a specific charged Higgs, by name
  const DecayTable::Entry& HiggsCouplingsTable::get_charged_decays(const str& name) const
  {
    if (charged_decays_map.find(name) == charged_decays_map.end()) utils_error().raise(LOCAL_INFO, "Requested higgs not found.");
    return charged_decays_map.at(name);
  }

  /// Retrieve decays of the top quark
  const DecayTable::Entry& HiggsCouplingsTable::get_t_decays() const
  {
    return *t_decays;
  }

  /// Print Higgs coupling table to a map
  map_str_dbl HiggsCouplingsTable::to_map() const
  {
    map_str_dbl couplings_map;

    for(int i=0; i<n_neutral_higgses; i++)
    {
      couplings_map["h"+std::to_string(i)+"WW"] = C_WW[i];
      couplings_map["h"+std::to_string(i)+"ZZ"] = C_ZZ[i];
      couplings_map["h"+std::to_string(i)+"tt^2"] = C_tt2[i];
      couplings_map["h"+std::to_string(i)+"bb^2"] = C_bb2[i];
      couplings_map["h"+std::to_string(i)+"cc^2"] = C_cc2[i];
      couplings_map["h"+std::to_string(i)+"tautau^2"] = C_tautau2[i];
      couplings_map["h"+std::to_string(i)+"gaga^2"] = C_gaga2[i];
      couplings_map["h"+std::to_string(i)+"gg^2"] = C_gg2[i];
      couplings_map["h"+std::to_string(i)+"mumu^2"] = C_mumu2[i];
      couplings_map["h"+std::to_string(i)+"Zga^2"] = C_Zga2[i];
      couplings_map["h"+std::to_string(i)+"ss^2"] = C_ss2[i];
      for(int j=0; j<n_neutral_higgses; j++)
        couplings_map["h"+std::to_string(i)+"h"+std::to_string(j)+"Z"] = C_hiZ[i][j];
      couplings_map["h"+std::to_string(i)+"tt_s"] = C_tt_s[i];
      couplings_map["h"+std::to_string(i)+"tt_p"] = C_tt_p[i];
      couplings_map["h"+std::to_string(i)+"bb_s"] = C_bb_s[i];
      couplings_map["h"+std::to_string(i)+"bb_p"] = C_bb_p[i];
      couplings_map["h"+std::to_string(i)+"cc_s"] = C_cc_s[i];
      couplings_map["h"+std::to_string(i)+"cc_p"] = C_cc_p[i];
      couplings_map["h"+std::to_string(i)+"ss_s"] = C_ss_s[i];
      couplings_map["h"+std::to_string(i)+"ss_p"] = C_ss_p[i];
      couplings_map["h"+std::to_string(i)+"tautau_s"] = C_tautau_s[i];
      couplings_map["h"+std::to_string(i)+"tautau_p"] = C_tautau_p[i];
      couplings_map["h"+std::to_string(i)+"mumu_s"] = C_mumu_s[i];
      couplings_map["h"+std::to_string(i)+"mumu_p"] = C_mumu_p[i];

    }

    return couplings_map;
  }

  void HiggsCouplingsTable::print() const
  {
    auto c = to_map();

    for (auto& i : c)
    {
      std::cerr << i.first << "  " << i.second << std::endl;
    }
  }



}



