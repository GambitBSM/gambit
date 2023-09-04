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
///  \author Tomas Gonzalo
///         (tomas.gonzalo@monash.edu)
///  \date 2020
///
///  *********************************************

#ifndef __slha_helpers_hpp__
#define __slha_helpers_hpp__

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/util_types.hpp"

#include "SLHAea/slhaea.h"

#include <boost/serialization/strong_typedef.hpp>

namespace Gambit
{
  /// Less confusing name for SLHAea container class
  typedef SLHAea::Coll SLHAstruct;

  /// Create a strong typedef (different classes underneath, but can be assigned to each other etc.)
  /// that lets us create e.g. different print/retrieve functions for different sorts of 
  /// spectrum information
  BOOST_STRONG_TYPEDEF(SLHAstruct, MSSM_SLHAstruct)
  BOOST_STRONG_TYPEDEF(SLHAstruct, SMslha_SLHAstruct)

  /// Read an SLHA file in to an SLHAea object with some error-checking
  SLHAstruct read_SLHA(str slha); 

  /// Get an entry from an SLHAea object as a double, with some error checking
  double SLHAea_get(const SLHAstruct& slha, const str& block, const int index);

  /// Get an entry from an SLHAea object as a double; raise a warning and use a default value if the entry is missing
  double SLHAea_get(const SLHAstruct& slha, const str& block, const int index, const double defvalue);

  /// Add a new block to an SLHAea object, with or without a scale
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


  /// Check if a line exists in an SLHAea block, then overwrite it if it does.  Otherwise add the line.
  template <class T>
  void SLHAea_overwrite_block(SLHAstruct& slha /*modify*/, const str& block, int index,
   T value, const str& comment)
  {
    if(SLHAea_check_block(slha, block, index))
    {
      // entry exists already, delete it
      slha.at(block).at(index).at(1);
      auto& line = slha[block][index];
      line.clear();
      line << index << value << comment;
    }
    else
    {
      // Doesn't already exist, add it
      slha[block][""] << index << value << comment;
    }
  }

  /// Check if a line exists in an SLHAea block, then overwrite it if it does.  Otherwise add the line.
  template <class T>
  void SLHAea_overwrite_block(SLHAstruct& slha /*modify*/, const str& block, int index1, int index2,
   T value, const str& comment)
  {
    //std::vector<int> indices = initVector<int>(index1, index2);
    if(SLHAea_check_block(slha, block, index1, index2))
    {
      // entry exists already, delete it
      //slha.at(block).at(indices).at(1); // Is this actually a valid way to use SLHAea? I don't see it in their documentation.
      std::stringstream i,j;
      i<<index1; j<<index2;
      SLHAea::Block::key_type key(2);
      key[0] = i.str();
      key[1] = j.str();
      auto& line = slha[block][key];
      line.clear();
      line << index1 << index2 << value << comment;
    }
    else
    {
      // Doesn't exist, add it
      slha[block][""] << index1 << index2 << value << comment;
    }
  }



}

#endif //defined __slhaea_helpers_hpp__



