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

#ifndef __higgs_couplings_table_hpp__
#define __higgs_couplings_table_hpp__

#include "gambit/Utils/util_types.hpp"
#include "gambit/Elements/decay_table.hpp"


namespace Gambit
{

  /// GAMBIT native higgs coupling table class.
  class HiggsCouplingsTable
  {

    private:

      /// SM neutral higgs decays
      /// @{
      std::vector<const DecayTable::Entry*> neutral_decays_SM_array;
      std::map<str, const DecayTable::Entry&> neutral_decays_SM_map;
      /// @}

      /// BSM higgs decays
      /// @{
      std::vector<const DecayTable::Entry*> neutral_decays_array;
      std::vector<const DecayTable::Entry*> charged_decays_array;
      std::map<str, const DecayTable::Entry&> neutral_decays_map;
      std::map<str, const DecayTable::Entry&> charged_decays_map;
      /// @}

      /// t decays (as t can decay to h)
      const DecayTable::Entry* t_decays;

      /// Number of neutral Higgs bosons
      int n_neutral_higgses;

      /// Number of charged Higgs bosons
      int n_charged_higgses;

    public:

      /// CP of neutral higgses
      std::vector<double> CP;

      /// Particles that higgses can decay invisibly to
      std::vector<std::pair<str,str>> invisibles;

      /// Effective couplings for neutral higgses
      /// @{
      std::vector<double> C_WW2;
      std::vector<double> C_ZZ2;
      std::vector<double> C_tt2;
      std::vector<double> C_bb2;
      std::vector<double> C_cc2;
      std::vector<double> C_tautau2;
      std::vector<double> C_gaga2;
      std::vector<double> C_gg2;
      std::vector<double> C_mumu2;
      std::vector<double> C_Zga2;
      std::vector<double> C_ss2;
      std::vector<std::vector<double>> C_hiZ2;
      /// @}

      /// Constructor
      HiggsCouplingsTable() {};

      /// Set the number of neutral Higgses
      void set_n_neutral_higgs(int);

      /// Set the number of charged Higgses
      void set_n_charged_higgs(int);

      /// Retrieve number of neutral higgses
      int get_n_neutral_higgs() const;

      /// Retrieve number of charged higgses
      int get_n_charged_higgs() const;

      /// Set all effective couplings to 1
      void set_effective_couplings_to_unity();

      /// Compute a neutral higgs effective coupling from the current two-body neutral higgs decays
      /// @{
      template <typename T>
      double compute_effective_coupling(int index, const T& p1, const T& p2)
      {
        if (index > n_neutral_higgses - 1) utils_error().raise(LOCAL_INFO, "Requested index beyond n_neutral_higgses.");
        // If channel is missing from either SM or BSM decays, return unity.
        if (!neutral_decays_SM_array[index]->has_channel(p1, p2) or !neutral_decays_array[index]->has_channel(p1, p2)) return 1.;
        double smwidth = neutral_decays_SM_array[index]->width_in_GeV;
        double smbf = neutral_decays_SM_array[index]->BF(p1, p2);
        if (smwidth <= 0. or smbf <= 0.) return 1.;
        double total_width_ratio = neutral_decays_array[index]->width_in_GeV / smwidth;
        double BF_ratio = neutral_decays_array[index]->BF(p1, p2) / smbf;
        return total_width_ratio * BF_ratio;
      }
      template <typename T>
      double compute_effective_coupling(str name, const T& p1, const T& p2)
      {
        if (neutral_decays_SM_map.find(name) == neutral_decays_SM_map.end() or
            neutral_decays_map.find(name) == neutral_decays_map.end())
         utils_error().raise(LOCAL_INFO, "Requested higgs not found.");
        // If channel is missing from either SM or BSM decays, return unity.
        if (!neutral_decays_SM_map.at(name).has_channel(p1, p2) or !neutral_decays_map.at(name).has_channel(p1, p2)) return 1.;
        double smwidth = neutral_decays_SM_map.at(name).width_in_GeV;
        double smbf = neutral_decays_SM_map.at(name).BF(p1, p2);
        if (smwidth <= 0. or smbf <= 0.) return 1.;
        double total_width_ratio = neutral_decays_map.at(name).width_in_GeV / smwidth;
        double BF_ratio = neutral_decays_map.at(name).BF(p1, p2) / smbf;
        return total_width_ratio * BF_ratio;
      }
      /// @}


      /// Assign decay entries to the various table components
      /// @{
      void set_neutral_decays_SM(int, const str&, const DecayTable::Entry&);
      void set_neutral_decays(int, const str&, const DecayTable::Entry&);
      void set_charged_decays(int, const str&, const DecayTable::Entry&);
      void set_t_decays(const DecayTable::Entry&);
      /// @}

      /// Retrieve decay sets
      /// @{
      const std::vector<const DecayTable::Entry*>& get_neutral_decays_SM_array() const;
      const DecayTable::Entry& get_neutral_decays_SM(int) const;
      const DecayTable::Entry& get_neutral_decays_SM(const str&) const;
      const std::vector<const DecayTable::Entry*>& get_neutral_decays_array() const;
      const DecayTable::Entry& get_neutral_decays(int) const;
      const DecayTable::Entry& get_neutral_decays(const str&) const;
      const std::vector<const DecayTable::Entry*>& get_charged_decays_array() const;
      const DecayTable::Entry& get_charged_decays(int) const;
      const DecayTable::Entry& get_charged_decays(const str&) const;
      const DecayTable::Entry& get_t_decays() const;
      /// @}

  };

}

#endif //__higgs_couplings_table_hpp__