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
    public:

      /// The maximal Higgs sector manageable by this class; update as needed.
      /// @{
      const static int max_neutral_higgses = 3;
      const static int max_charged_higgses = 1;
      /// @}

    private:

      /// SM neutral higgs decays
      /// @{
      const DecayTable::Entry* neutral_decays_SM_array[max_neutral_higgses];
      std::map<str, const DecayTable::Entry&> neutral_decays_SM_map;
      /// @}

      /// BSM higgs decays
      /// @{
      const DecayTable::Entry* neutral_decays_array[max_neutral_higgses];
      const DecayTable::Entry* charged_decays_array[max_charged_higgses];
      std::map<str, const DecayTable::Entry&> neutral_decays_map;
      std::map<str, const DecayTable::Entry&> charged_decays_map;
      /// @}

      /// t decays (as t can decay to h)
      const DecayTable::Entry* t_decays;

    public:

      /// Types to make returning decay arrays easier
      /// @{
      typedef const DecayTable::Entry* h0_decay_array_type[max_neutral_higgses];
      typedef const DecayTable::Entry* hp_decay_array_type[max_charged_higgses];
      /// @}

      /// CP of neutral higgses
      double CP[max_neutral_higgses];

      /// Particles that higgses can decay invisibly to
      std::vector<str> invisibles;

      /// Effective couplings for neutral higgses
      /// @{
      double C_WW2[max_neutral_higgses];
      double C_ZZ2[max_neutral_higgses];
      double C_tt2[max_neutral_higgses];
      double C_bb2[max_neutral_higgses];
      double C_cc2[max_neutral_higgses];
      double C_tautau2[max_neutral_higgses];
      double C_gaga2[max_neutral_higgses];
      double C_gg2[max_neutral_higgses];
      double C_mumu2[max_neutral_higgses];
      double C_Zga2[max_neutral_higgses];
      double C_ss2[max_neutral_higgses];
      double C_hiZ2[max_neutral_higgses][max_neutral_higgses];
      /// Pseudoscalar and scalar effective couplings (not squared)
      double C_tt_s[max_neutral_higgses];
      double C_tt_p[max_neutral_higgses];
      double C_bb_s[max_neutral_higgses];
      double C_bb_p[max_neutral_higgses];
      double C_cc_s[max_neutral_higgses];
      double C_cc_p[max_neutral_higgses];
      double C_ss_s[max_neutral_higgses];
      double C_ss_p[max_neutral_higgses];
      double C_tautau_s[max_neutral_higgses];
      double C_tautau_p[max_neutral_higgses];
      double C_mumu_s[max_neutral_higgses];
      double C_mumu_p[max_neutral_higgses];
      /// @}

      /// Constructor
      HiggsCouplingsTable();

      /// Compute a neutral higgs effective coupling from the current two-body neutral higgs decays
      /// @{
      template <typename T>
      double compute_effective_coupling(int index, const T& p1, const T& p2)
      {
        if (index > max_neutral_higgses - 1) utils_error().raise(LOCAL_INFO, "Requested index beyond max_neutral_higgses.");
        // If channel is missing from either SM or BSM decays, return unity.
        if (!neutral_decays_SM_array[index]->has_channel(p1, p2) or !neutral_decays_array[index]->has_channel(p1, p2)) {
          std::cout << "[compute_effective_coupling] channel missing" << std::endl;
          std::cout << "[compute_effective_coupling] neutral_decays_SM_array " << p1 << " "<< p2 << ": " << neutral_decays_SM_array[index]->has_channel(p1, p2) << std::endl;
          std::cout << "[compute_effective_coupling] neutral_decays_array " << p1 << " "<< p2 << ": " << neutral_decays_array[index]->has_channel(p1, p2) << std::endl;
          return 1.;
        }
        double smwidth = neutral_decays_SM_array[index]->width_in_GeV;
        double smbf = neutral_decays_SM_array[index]->BF(p1, p2);
        if (smwidth <= 0. or smbf <= 0.) {
          std::cout << "[compute_effective_coupling] negative width" << std::endl;
          std::cout << "[compute_effective_coupling] smwidth: " << smwidth << std::endl;
          std::cout << "[compute_effective_coupling] smbf: " << smbf << std::endl;
          return 1.;
        }
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
      const h0_decay_array_type& get_neutral_decays_SM_array(int) const;
      const DecayTable::Entry& get_neutral_decays_SM(int) const;
      const DecayTable::Entry& get_neutral_decays_SM(const str&) const;
      const h0_decay_array_type& get_neutral_decays_array(int) const;
      const DecayTable::Entry& get_neutral_decays(int) const;
      const DecayTable::Entry& get_neutral_decays(const str&) const;
      const hp_decay_array_type& get_charged_decays_array(int) const;
      const DecayTable::Entry& get_charged_decays(int) const;
      const DecayTable::Entry& get_charged_decays(const str&) const;
      const DecayTable::Entry& get_t_decays() const;
      /// @}

  };

}

#endif //__higgs_couplings_table_hpp__