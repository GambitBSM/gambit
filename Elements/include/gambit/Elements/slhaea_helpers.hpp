//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Nicer alias for SLHAea container class, and
///  some convenient helper functions that add
///  or retrieve the contents of an SLHAea::Coll
///  with some basic error-checking.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu)
///  \date 2015
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015
///
///  *********************************************

#ifndef __slha_helpers_hpp__
#define __slha_helpers_hpp__

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/util_types.hpp"
#include "gambit/Elements/spectrum_helpers.hpp"

#include "SLHAea/slhaea.h"


namespace Gambit
{
  /// Forward declare SubSpectrum class
  class SubSpectrum;

  /// Less confusing name for SLHAea container class
  typedef SLHAea::Coll SLHAstruct;

  /// Read an SLHA file in to an SLHAea object with some error-checking
  SLHAstruct read_SLHA(str slha); 

  /// Get an entry from an SLHAea object as a double, with some error checking
  double SLHAea_get(const SLHAstruct& slha, const str& block, const int index);

  /// Get an entry from an SLHAea object as a double; raise a warning and use a default value if the entry is missing
  double SLHAea_get(const SLHAstruct& slha, const str& block, const int index, const double defvalue);

  /// Add a new block to an SLHAea object, with our without a scale
  void SLHAea_add_block(SLHAstruct&, const str& name, const double scale = -1);

  /// Delete an entire block from an SLHAea object, if it exists (actually just the first block matching the given name)
  void SLHAea_delete_block(SLHAstruct& slha, const std::string& block);

  /// Check if a block exists in an SLHAea object
  bool SLHAea_block_exists(SLHAstruct& slha, const str& block);
  /// Check if a block exists in an SLHAea object, add it if not
  bool SLHAea_check_block(SLHAstruct& slha, const str& block);
  /// Check if a block exists in an SLHAea object, add it if not, and check if it has an entry at a given index
  bool SLHAea_check_block(SLHAstruct& slha, const str& block, const int index); /*, const bool overwrite)*/
  bool SLHAea_check_block(SLHAstruct& slha, const str& block, const int index1, const int index2);

  /// Write the SPINFO block with GAMBIT name and version number
  void SLHAea_add_GAMBIT_SPINFO(SLHAstruct& slha /*modify*/);

  /// Add an entry to an SLHAea object (if overwrite=false, only if it doesn't already exist)
  /// @{
  void SLHAea_add(SLHAstruct& slha /*modify*/, const str& block, const int index, const double value,
   const str& comment="", const bool overwrite=false);
  void SLHAea_add(SLHAstruct& slha /*modify*/, const str& block, const int index, const str& value,
   const str& comment="", const bool overwrite=false);
  void SLHAea_add(SLHAstruct& slha /*modify*/, const str& block, const int index, const int value,
   const str& comment="", const bool overwrite=false);
  // two index version
  void SLHAea_add(SLHAstruct& slha /*modify*/, const str& block, const int index1, const int index2,
   const double& value, const str& comment, const bool overwrite=false);
  /// @}

  /// Add a whole matrix to an SLHAea object if it doesn't already exist
  template<typename T>
  void SLHAea_add_matrix(SLHAstruct& slha /*modify*/, const str& block, const std::vector<T>& matrix,
                 const int rows, const int cols, const str& comment="", const bool overwrite=false)
  {
   if (SLHAea_check_block(slha, block, 1, overwrite)) return;
   std::ostringstream commentwhash;
   if (comment != "") commentwhash << "# " << comment;
   for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++)
   {
     slha[block][""] << i+1 << j+1 << matrix.at(i*rows + j) << commentwhash.str();
   }
   return;
  }

  /// Add an entry from a subspectrum getter to an SLHAea object; SLHA index given by pdg code
  void SLHAea_add_from_subspec(SLHAstruct& slha /*modify*/, const str local_info, const SubSpectrum& subspec,
   const Par::Tags partype, const std::pair<int, int>& pdg_pair, const str& block, const str& comment,
   const bool error_if_missing = true, const double rescale = 1.0);

  /// Add an entry from a subspectrum getter to an SLHAea object; 1 SLHA index
  void SLHAea_add_from_subspec(SLHAstruct& slha /*modify*/, const str local_info, const SubSpectrum& subspec,
   const Par::Tags partype, const str& name, const str& block, const int slha_index,
   const str& comment, const bool error_if_missing = true, const double rescale = 1.0);

  /// Add an entry from a subspectrum getter to an SLHAea object; two SubSpectrum getter indices, two SLHA indices
  void SLHAea_add_from_subspec(SLHAstruct& slha /*modify*/, const str local_info, const SubSpectrum& subspec,
   const Par::Tags partype, const str& name, const int index1, const int index2, const str& block,
   const int slha_index1, const int slha_index2, const str& comment, const bool error_if_missing = true, const double rescale = 1.0);

}

#endif //defined __slhaea_helpers_hpp__



