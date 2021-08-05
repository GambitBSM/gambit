//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper functions for dealing with SLHAea objects
///
///  *********************************************
///
///  Authors:
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Mar
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Jul, Dec
///
///  *********************************************

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/version.hpp"
#include "gambit/Utils/slhaea_helpers.hpp"

namespace Gambit
{
  /// Read an SLHA file in to an SLHAea object with some error-checking
  SLHAstruct read_SLHA(str slha)
  {
    SLHAstruct slhaea;
    std::ifstream ifs(slha.c_str());
    if (!ifs.good())
    {
     std::ostringstream err;
     err << "ERROR: SLHA file " << slha << " not found.";
     utils_error().raise(LOCAL_INFO,err.str());
    }
    ifs >> slhaea;
    ifs.close();
    return slhaea;
  }

  /// Get an entry from an SLHAea object as a double, with some error checking
  double SLHAea_get(const SLHAstruct& slha, const str& block, const int index)
  {
    double output = 0.0;
    try
    {
      output = SLHAea::to<double>(slha.at(block).at(index).at(1));
    }
    catch (const std::out_of_range& e)
    {
      std::ostringstream errmsg;
      errmsg << "Error accessing data at index " << index << " of block " << block
             << ". Please check that the SLHAea object was properly filled." << std::endl
             << "(Received out_of_range error from SLHAea class with message: " << e.what() << ")";
      utils_error().raise(LOCAL_INFO,errmsg.str());
    }
    return output;
  }

  /// Get an entry from an SLHAea object as a double; raise a warning and use a default value if the entry is missing
  double SLHAea_get(const SLHAstruct& slha, const str& block, const int index, const double defvalue)
  {
    double output;
    try
    {
      output = SLHAea::to<double>(slha.at(block).at(index).at(1));
    }
    catch (const std::out_of_range& e)
    {
      std::ostringstream warn;
      warn << "Warning! No entry found at index "<<index<<" of block "<<block<<". Using default value: "<<defvalue<< std::endl;
      utils_warning().raise(LOCAL_INFO,warn.str());
      output = defvalue;
    }
    return output;
  }

  /// Add a new block to an SLHAea object, with or without a scale
  void SLHAea_add_block(SLHAstruct& slha, const str& name, const double scale)
  {
    if(scale==-1)
    {
      slha[name][""] << "BLOCK" << name;
    }
    else
    {
      slha[name][""] << "BLOCK" << name << "Q=" << scale;
    }
  }

  bool SLHAea_block_exists(SLHAstruct& slha, const str& block)
  {
    // Check if block exists
    bool found = false;
    if(slha.find(block) != slha.end()) found = true;
    return found;
  }

  bool SLHAea_check_block(SLHAstruct& slha, const str& block)
  {
    bool exists;
    if(SLHAea_block_exists(slha,block))
    {
      exists = true;
    }
    else
    {
      slha[block][""] << "BLOCK" << block;
      exists = false; // Didn't exist, but now it does.
    }
    return exists;
  }

  /// Check if a block exists in an SLHAea object, add it if not, and check if it has an entry at a given index
  // TODO: Ben: I just found this, and I can't say I understand the logic related to "overwrite". It also makes
  // overloading for two indices very difficult, so I'm going to delete it.
  bool SLHAea_check_block(SLHAstruct& slha, const str& block, const int index) /*, const bool overwrite)*/
  {
    bool found;
    // Check if block exists and create it if it doesn't
    SLHAea_check_block(slha, block);
    // Check for existing entry
    std::stringstream i;
    i<<index;
    SLHAea::Block::key_type key(1);
    key[0] = i.str();
    if( slha[block].find(key) != slha[block].end()) 
    {
      found = true;
    }
    else
    {
      found = false;
    }
    return found;
  }

  bool SLHAea_check_block(SLHAstruct& slha, const str& block, const int index1, const int index2) /*, const bool overwrite)*/
  {
    bool found;
    // Check if block exists and create it if it doesn't
    SLHAea_check_block(slha, block);
    // Check for existing entry
    std::stringstream i,j;
    i<<index1; j<<index2;
    SLHAea::Block::key_type key(2);
    key[0] = i.str();
    key[1] = j.str();
    if( slha[block].find(key) != slha[block].end() ) 
    {
      found = true;
    }
    else
    {
      found = false;
    }
    return found;
  }


  /// Delete a block entirely if it exists (TODO: actually only deletes first instance of the block found!)
  void SLHAea_delete_block(SLHAstruct& slha, const std::string& block)
  {
     auto it = slha.find(block);
     if(it!=slha.end()) slha.erase(it);
  }

  void SLHAea_add_GAMBIT_SPINFO(SLHAstruct& slha /*modify*/)
  {
     // For now we don't try to track where the data originally came from, we just label
     // it as GAMBIT-produced.
     std::ostringstream progname;
     if(not SLHAea_check_block(slha, "SPINFO", 1))
     {
        SLHAea_add(slha, "SPINFO", 1, "GAMBIT", "Program");
        SLHAea_add(slha, "SPINFO", 2, gambit_version(), "Version number");
     }
  }

  /// Add an entry to an SLHAea object (if overwrite=false, only if it doesn't already exist)
  /// @{
  void SLHAea_add(SLHAstruct& slha /*modify*/, const str& block, const int index,
   const double value, const str& comment, const bool overwrite)
  {
    if (SLHAea_check_block(slha, block, index) and not overwrite) return;
    SLHAea_overwrite_block(slha, block, index, value, (comment == "" ? "" : "# " + comment));
  }

  // string version
  void SLHAea_add(SLHAstruct& slha /*modify*/, const str& block, const int index,
   const str& value, const str& comment, const bool overwrite)
  {
    if (SLHAea_check_block(slha, block, index, overwrite)) return;
    SLHAea_overwrite_block(slha, block, index, value, (comment == "" ? "" : "# " + comment));
  }

  // int version
  void SLHAea_add(SLHAstruct& slha /*modify*/, const str& block, const int index,
   const int value, const str& comment, const bool overwrite)
  {
    if (SLHAea_check_block(slha, block, index, overwrite)) return;
    SLHAea_overwrite_block(slha, block, index, value, (comment == "" ? "" : "# " + comment));
  }

  // two index version
  void SLHAea_add(SLHAstruct& slha /*modify*/, const str& block, const int index1, const int index2,
   const double& value, const str& comment, const bool overwrite)
  {
    if (SLHAea_check_block(slha, block, index1, index2) and not overwrite) return;
    SLHAea_overwrite_block(slha, block, index1, index2, value, (comment == "" ? "" : "# " + comment));
  }

  /// @}

} 
