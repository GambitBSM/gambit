//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper functions for dealing with SLHAea and
///  spectrum objects
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
#include "gambit/Elements/slhaea_spec_helpers.hpp"
#include "gambit/Elements/subspectrum.hpp"

namespace Gambit
{

  /// Add an entry from a subspectrum getter to an SLHAea object; SLHA index given by pdg code
  void SLHAea_add_from_subspec(SLHAstruct& slha /*modify*/, const str local_info, const SubSpectrum& subspec,
   const Par::Tags partype, const std::pair<int, int>& pdg_pair, const str& block, const str& comment,
   const bool error_if_missing, const double rescale)
  {
     if(subspec.has(partype,pdg_pair))
     {
       SLHAea_overwrite_block(slha, block, pdg_pair.first, subspec.get(partype,pdg_pair)*rescale, (comment == "" ? "" : "# " + comment));
     }
     else if(error_if_missing)
     {
        std::ostringstream errmsg;
        errmsg << "Error creating SLHAea output from SubSpectrum object! Required entry not found (paramtype="<<Par::toString.at(partype)
               <<", pdg:context="<<pdg_pair.first<<":"<<pdg_pair.second<<")";
        utils_error().raise(local_info,errmsg.str());
     }
     // else skip this entry
     return;
  }

  /// Add an entry from a subspectrum getter to an SLHAea object; 1 SLHA index
  void SLHAea_add_from_subspec(SLHAstruct& slha /*modify*/, const str local_info, const SubSpectrum& subspec,
   const Par::Tags partype, const str& name, const str& block, const int slha_index,
   const str& comment, const bool error_if_missing, const double rescale)
  {
     if(subspec.has(partype,name))
     {
       SLHAea_overwrite_block(slha, block, slha_index, subspec.get(partype,name)*rescale, (comment == "" ? "" : "# " + comment));
     }
     else if(error_if_missing)
     {
        std::ostringstream errmsg;
        errmsg << "Error creating SLHAea output from SubSpectrum object! Required entry not found (paramtype="<<Par::toString.at(partype)<<", name="<<name<<")";
        utils_error().raise(local_info,errmsg.str());
     }
     // else skip this entry
     return;
  }

  /// Add an entry from a subspectrum getter to an SLHAea object; two SubSpectrum getter indices, two SLHA indices
  void SLHAea_add_from_subspec(SLHAstruct& slha /*modify*/, const str local_info, const SubSpectrum& subspec,
   const Par::Tags partype, const str& name, const int index1, const int index2, const str& block,
   const int slha_index1, const int slha_index2, const str& comment, const bool error_if_missing, const double rescale)
  {
    if(subspec.has(partype,name,index1,index2))
    {
      SLHAea_overwrite_block(slha, block, slha_index1, slha_index2, subspec.get(partype,name,index1,index2)*rescale, (comment == "" ? "" : "# " + comment));
    }
    else if(error_if_missing)
    {
      std::ostringstream errmsg;
      errmsg << "Error creating SLHAea output from SubSpectrum object! Required entry not found (paramtype="<<Par::toString.at(partype)<<", name="<<name<<", index1="<<index1<<", index2="<<index2;
      utils_error().raise(local_info,errmsg.str());
    }
    // else skip this entry
    return;
  }

  /// Adds QNUMBERS entry for a particle, SLHA index given by the PDG code
  void SLHAea_add_QNumbers_from_subspec(SLHAstruct& slha, const SubSpectrum& subspec, 
   const std::pair<int,int> pdg_pair)
  {
    if (subspec.has(Par::Pole_Mass,pdg_pair))
    {
      str long_name = Models::ParticleDB().long_name(pdg_pair);
      int spinx2 = Models::ParticleDB().get_spinx2(long_name);
      int chargex3 = Models::ParticleDB().get_chargex3(long_name);
      int color = Models::ParticleDB().get_color(long_name);
      bool is_anti = Models::ParticleDB().has_antiparticle(long_name);

      SLHAea::Block QNblock("QNUMBERS");
      SLHAea::Line line1, line2, line3, line4, line5;
      line1 << "BLOCK" << "QNUMBERS" << pdg_pair.first << "# " + long_name;
      line2 << 1 << chargex3 << "# 3 times electric charge";
      line3 << 2 << spinx2+1 << "# number of spin states (2S+1)";
      line4 << 3 << color    << "# colour rep (1: singlet, 3: triplet, 8: octet)";
      line5 << 4 << is_anti  << "# Particle/Antiparticle distinction (0=own anti)";
      QNblock.push_back(line1);
      QNblock.push_back(line2);
      QNblock.push_back(line3);
      QNblock.push_back(line4);
      QNblock.push_back(line5);
      slha.push_front(QNblock);

    }
  }

  /// Write a SimpleSpectrum to an SLHAea object.
  void add_SimpleSpec_to_SLHAea(const SubSpectrum& subspec, SLHAstruct& slha, const SubSpectrumContents& contents)
  {

    // Pick out the parameters whose SLHA block name is not: SMINPUTS, CKMBLOCK, YUKAWA, or empty.
    std::vector<SpectrumParameter> bsm = contents.all_BSM_parameters();

    // Then assign them to the correct part of the SLHAea object
    for (std::vector<SpectrumParameter>::const_iterator it = bsm.begin(); it != bsm.end(); ++it)
    {
      // The SLHAea comment changes based on the ParType
      std::ostringstream comment;

      // If it's a mass, we always want to write it to the MASS block. Otherwise use what's been specified explicitly.
      str blockname = (it->tag() == Par::Pole_Mass ? "MASS" : it->blockname());

      // Masses
      if (it->tag() == Par::Pole_Mass)
      { 
        comment << it->name() << " mass.";
        std::pair<int, int> pdg_pair = Models::ParticleDB().pdg_pair(it->name());
        SLHAea_add_from_subspec(slha, LOCAL_INFO, subspec, it->tag(), pdg_pair, blockname, comment.str());
        SLHAea_add_QNumbers_from_subspec(slha, subspec, pdg_pair);
      }
      // The rest
      else 
      {
        // Scalar case
        if (it->shape().size()==1 and it->shape()[0]==1) 
        {
          SLHAea_add_from_subspec(slha, LOCAL_INFO, subspec, it->tag(), it->name(), blockname, it->blockindex(), comment.str());
        }
        // Vector (1 index) 
        else if (it->shape().size() == 1 and it->shape()[0] > 1)
        {
          for (int i=1; i<it->shape()[0]+1; ++i)
          { 
            // Increment +1 to each entry for the BLOCKNAME
            SLHAea_add_from_subspec(slha, LOCAL_INFO, subspec, it->tag(), it->name(), blockname, it->blockindex()+i, comment.str());
          }
        }
        // Matrix (2 indices) -- blockindex() should just start from 1.
        else if (it->shape().size() == 2)
        {
          for (int i=1; i<it->shape()[0]+1; ++i)
          { 
            for (int j=1; j<it->shape()[0]+1; ++j)
            {
              SLHAea_add_from_subspec(slha, LOCAL_INFO, subspec, it->tag(), it->name(), i, j, blockname, i, j, comment.str());
            }
          }
        }
      }
    }

  } 

} 
