//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of containers for BBN
///  calculations.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2019 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  *********************************************

#include "gambit/Backends/backend_types/AlterBBN.hpp"


namespace Gambit
{

  /// Constructor
  BBN_container::BBN_container() : abund_map{{"H2",3}, {"D",3}, {"H3",4}, {"He3",5}, {"He4",6}, {"Yp",6}, {"Li6",7}, {"Li7",8}, {"Be7",9}, {"Li8",10}}
  {}

  /// Initialize sizes of vectors (get NNUC, number of computed element abundances, from AlterBBN)
  void BBN_container::init_arr_size(int nnuc)
  {
    NNUC = nnuc;
    BBN_abund.resize(NNUC+1, 0.);
    BBN_covmat.resize(NNUC+1, std::vector<double>(NNUC+1,0.));
  }

  /// Initialise the translation map from element name to position in abundance vector
  void BBN_container::set_abund_map(map_str_int map_in) {abund_map = map_in;}

  /// Setter function for abundance vector using position 
  void BBN_container::set_BBN_abund(int pos, double val) {BBN_abund[pos] = val;}

  /// Setter function for abundance vector using string name
  void BBN_container::set_BBN_abund(str iso, double val) {BBN_abund[abund_map.at(iso)] = val;}

  /// Setter function for covariance matrix
  void BBN_container::set_BBN_covmat(int row, int col, double val) {BBN_covmat[row][col] = val;}

  /// Global parameter in AlterBBN; holds number of computed element abundances
  int BBN_container::get_NNUC() const {return NNUC;};

  /// Getter for map from isotope names to position in BBN_abundance vector
  const std::map<std::string,int>& BBN_container::get_abund_map() const {return abund_map;};

  /// Getter for abundance
  double BBN_container::get_BBN_abund(int pos) const {return BBN_abund[pos];}

  /// Getter for abundance
  double BBN_container::get_BBN_abund(str iso) const {return BBN_abund[abund_map.at(iso)];}

  /// Getter for covariance matrix
  double BBN_container::get_BBN_covmat(int row, int col) const {return BBN_covmat[row][col];}

  /// Setter for active isotopes
  void BBN_container::set_active_isotopes(std::set<str> isos)
  {
    active_isotopes.clear();
    active_isotope_indices.clear();
    for (const str& s : isos)
    {
      if (abund_map.find(s) != abund_map.end())
      {
       active_isotopes.insert(s);
       active_isotope_indices.insert(abund_map.at(s));
      }
    }
  }

  /// Getter for active isotopes
  const std::set<str>& BBN_container::get_active_isotopes() const {return active_isotopes;}

  /// Getter for indices of active isotopes in BBN_abundance vector
  const std::set<int>& BBN_container::get_active_isotope_indices() const {return active_isotope_indices;}

}

