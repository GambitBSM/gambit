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
    C_WW2.resize(n);
    C_ZZ2.resize(n);
    C_tt2.resize(n);
    C_bb2.resize(n);
    C_cc2.resize(n);
    C_tautau2.resize(n);
    C_gaga2.resize(n);
    C_gg2.resize(n);
    C_mumu2.resize(n);
    C_Zga2.resize(n);
    C_ss2.resize(n);
    C_hiZ2.resize(n);
    for (int i = 0; i < n; i++) C_hiZ2[i].resize(n);
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
      C_WW2[i] = 1.0;
      C_ZZ2[i] = 1.0;
      C_tt2[i] = 1.0;
      C_bb2[i] = 1.0;
      C_cc2[i] = 1.0;
      C_tautau2[i] = 1.0;
      C_gaga2[i] = 1.0;
      C_gg2[i] = 1.0;
      C_mumu2[i] = 1.0;
      C_Zga2[i] = 1.0;
      C_ss2[i] = 1.0;
      for(int j = 0; j < n_neutral_higgses; j++) C_hiZ2[i][j] = 1.0;
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

}

