//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Decay table class definitions.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2015 Jan
///
///  *********************************************

#include <fstream>

#include "gambit/Elements/decay_table.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/version.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Core/point_counter.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/assign.hpp>

namespace Gambit
{

  // Local helper functions

  void get_calculator_info(const SLHAstruct& slha, str& calculator, str& calculator_version)
  {
    auto dcinfo = slha.find("DCINFO");
    if (dcinfo != slha.end())
    {
      if (dcinfo->size() > 1)
      {
        for (unsigned int i = 1; i < dcinfo->at(1).size(); ++i)
        {
          str s(dcinfo->at(1).at(i));
          if (s[0] != '#') calculator += s;
        }
      }
      if (dcinfo->size() > 2)
      {
        for (unsigned int i = 1; i < dcinfo->at(2).size(); ++i)
        {
          str s(dcinfo->at(2).at(i));
          if (s[0] != '#') calculator_version += s;
        }
      }
    }
  }


  // DecayTable methods

  /// Create a DecayTable from an SLHA file
  DecayTable::DecayTable(str slha, int context, bool force_SM_fermion_gauge_eigenstates)
   : DecayTable(read_SLHA(slha), context, force_SM_fermion_gauge_eigenstates)
  {}

  /// Create a DecayTable from an SLHA file, with PDG code remapping
  DecayTable::DecayTable(str slha, const std::map<int, int>& PDG_map, int context, bool force_SM_fermion_gauge_eigenstates)
   : DecayTable(read_SLHA(slha), PDG_map, context, force_SM_fermion_gauge_eigenstates)
  {}

  /// Create a DecayTable from an SLHAea object containing DECAY blocks
  DecayTable::DecayTable(const SLHAstruct& slha, int context, bool force_SM_fermion_gauge_eigenstates)
  {
    // Extract the calculator info if it exists
    str calculator, calculator_version;
    get_calculator_info(slha, calculator, calculator_version);

    // Iterate over all blocks in the file, ignoring everything except DECAY blocks
    for (auto block = slha.begin(); block != slha.end(); ++block)
    {
      auto block_def = block->find_block_def();
      if (block_def != block->end())
      {
        if(block_def->at(0) == "DECAY")
        {
          // Make sure the block definition has the particle's width and PDG code
          if (block_def->size() < 3) utils_error().raise(LOCAL_INFO,
           "SLHAea object has DECAY block with < 3 entries in its block definition.");
          int pdg = SLHAea::to<int>(block_def->at(1));
          // Add an entry containing the info in this block
          int local_context = context;
          if (force_SM_fermion_gauge_eigenstates)
          {
            int abspdg = std::abs(pdg);
            // Select SM fermions, including 4th gen, and force gauge eigenstates (context = 1).
            if (abspdg < 19 and abspdg != 9 and abspdg != 10) local_context = 1;
          }
          operator()(std::pair<int,int>(pdg,local_context)) = Entry(*block, block_def, context,
           force_SM_fermion_gauge_eigenstates, calculator, calculator_version);
        }
      }
    }
  }

  /// Create a DecayTable from an SLHAea object containing DECAY blocks, and remap PDG codes according to provided map
  DecayTable::DecayTable(const SLHAstruct& slha_in, const std::map<int, int>& PDG_map, int context, bool force_SM_fermion_gauge_eigenstates)
  {
    // Make a local copy so we can mess with it
    SLHAstruct slha(slha_in);

    // Extract the calculator info if it exists
    str calculator, calculator_version;
    get_calculator_info(slha, calculator, calculator_version);

    // Iterate over all blocks in the file, ignoring everything except DECAY blocks
    for (auto block = slha.begin(); block != slha.end(); ++block)
    {
      auto block_def = block->find_block_def();
      if (block_def != block->end())
      {
        if(block_def->at(0) == "DECAY")
        {
          // Make sure the block definition has the particle's width and PDG code
          if (block_def->size() < 3) utils_error().raise(LOCAL_INFO, "SLHAea object has DECAY block with < 3 entries in its block definition.");
          int pdg = SLHAea::to<int>(block_def->at(1));
          if (PDG_map.find(pdg) != PDG_map.end())
          {
            pdg = PDG_map.at(pdg);
            (*block_def)[1] = boost::lexical_cast<str>(pdg);
          }
          // Step through the block and convert any final state PDG codes that need to be remapped
          for (auto line = block->begin() + 1; line != block->end(); ++line)
          {
            if (not line->is_comment_line())
            {
              for (int i = 2; i < 2 + SLHAea::to<int>(line->at(1)); i++)
              {
                int local_pdg = SLHAea::to<int>(line->at(i));
                if (PDG_map.find(local_pdg) != PDG_map.end()) (*line)[i] = boost::lexical_cast<str>(PDG_map.at(local_pdg));
              }
            }
          }
          // Add an entry containing the info in this block
          operator()(std::pair<int,int>(pdg,context)) = Entry(*block, block_def, context,
           force_SM_fermion_gauge_eigenstates, calculator, calculator_version);
        }
      }
    }
  }

  /// Output entire decay table as an SLHA file full of DECAY blocks
  void DecayTable::writeSLHAfile(int SLHA_version, const str& filename, bool include_zero_bfs, const mass_es_pseudonyms& psn) const
  {
    Utils::FileLock mylock(filename);
    mylock.get_lock();
    std::ofstream ofs(filename);
    ofs << getSLHAea(SLHA_version, include_zero_bfs, psn);
    ofs.close();
    mylock.release_lock();
  }

  /// Output entire decay table as an SLHAea file full of DECAY blocks
  SLHAstruct DecayTable::getSLHAea(int SLHA_version, bool include_zero_bfs, const mass_es_pseudonyms& psn) const
  {
    SLHAstruct slha;
    std::map<str, std::set<str> > calculator_map;
    str calculators = "GAMBIT, using: ";
    str versions = gambit_version() + ": ";

    // Add the decay info
    for (auto particle = particles.begin(); particle != particles.end(); ++particle)
    {
      auto entry = particle->second;
      if (entry.calculator != "") calculator_map[entry.calculator].insert(entry.calculator_version);
      slha.push_back(entry.getSLHAea_block(SLHA_version, particle->first, include_zero_bfs, psn));
    }

    // Construct the calculator info
    for (auto be = calculator_map.begin(); be != calculator_map.end(); ++be)
    {
      if (be != calculator_map.begin())
      {
        calculators += " | ";
        versions += " | ";
      }
      calculators += be->first;
      for (auto ver = be->second.begin(); ver != be->second.end(); ++ver)
      {
        if (*ver != "")
        {
          if (ver != be->second.begin()) versions += ", ";
          versions += *ver;
        }
      }
    }

    // Add the calculator info
    SLHAea::Block DCblock("DCINFO");
    DCblock.push_back("BLOCK DCINFO              # Decay Program information");
    SLHAea::Line line1, line2;
    line1 << 1 << calculators << "# Decay calculators";
    line2 << 2 << versions << "# Version numbers";
    DCblock.push_back(line1);
    DCblock.push_back(line2);
    slha.push_front(DCblock);

    // Add a disclaimer about the absence of a MODSEL block
    slhahelp::add_MODSEL_disclaimer(slha, "DecayTable");

    return slha;
  }

  /// Output a decay table entry as an SLHAea DECAY block
  /// @{
  SLHAea::Block DecayTable::getSLHAea_block(int v, std::pair<int,int> p, bool z, const mass_es_pseudonyms& psn) const
  { return particles.at(p).getSLHAea_block(v, Models::ParticleDB().long_name(p), z, psn); }
  SLHAea::Block DecayTable::getSLHAea_block(int v, str p, bool z, const mass_es_pseudonyms& psn)                const
  { return particles.at(Models::ParticleDB().pdg_pair(p)).getSLHAea_block(v, p, z, psn); }
  SLHAea::Block DecayTable::getSLHAea_block(int v, str p, int i, bool z, const mass_es_pseudonyms& psn)         const
  { return particles.at(Models::ParticleDB().pdg_pair(p,i)).getSLHAea_block(v, Models::ParticleDB().long_name(p,i), z, psn); }
  /// @}


  // DecayTable::Entry subclass methods

  /// Constructor creating a DecayTable Entry from an SLHAea DECAY block; full version
  DecayTable::Entry::Entry(const SLHAea::Block& block, int context,
   bool force_SM_fermion_gauge_eigenstates, str calc, str calc_ver) :
   positive_error(0.0),
   negative_error(0.0),
   calculator(calc),
   calculator_version(calc_ver),
   warnings(""),
   errors("")
  {
    auto block_def = block.find_block_def();
    if (block_def->at(0) != "DECAY" or  block_def->size() < 3)
     utils_error().raise(LOCAL_INFO, "SLHAea block is not DECAY or has < 3 entries in its block definition.");
    width_in_GeV = SLHAea::to<double>(block_def->at(2));
    init(block, context, force_SM_fermion_gauge_eigenstates);
  }

  /// Constructor creating a DecayTable Entry from an SLHAea DECAY block; full version;
  /// version assuming block def is already known
  DecayTable::Entry::Entry(const SLHAea::Block& block, SLHAea::Block::const_iterator block_def,
   int context, bool force_SM_fermion_gauge_eigenstates, str calc, str calc_ver) :
   width_in_GeV (SLHAea::to<double>(block_def->at(2))),
   positive_error(0.0),
   negative_error(0.0),
   calculator(calc),
   calculator_version(calc_ver),
   warnings(""),
   errors("")
  {
    init(block, context, force_SM_fermion_gauge_eigenstates);
  }

  /// Initialise a DecayTable Entry using an SLHAea DECAY block
  void DecayTable::Entry::init(const SLHAea::Block& block, int context, bool force_SM_fermion_gauge_eigenstates)
  {
    for (auto channel = block.begin(); channel != block.end(); ++channel)
    {
      str first_entry(channel->at(0));
      if (first_entry != "DECAY" and first_entry[0] != '#')
      {
        if (channel->size() < 4) utils_error().raise(LOCAL_INFO, "SLHAea DECAY block line has < 4 entries!");
        double BF = SLHAea::to<double>(first_entry);
        int n_daughters = SLHAea::to<int>(channel->at(1));
        std::vector<std::pair<int,int> > daughter_pdg_codes;
        for (int i = 2; i < n_daughters+2; ++i)
        {
          int pdg = SLHAea::to<int>(channel->at(i));
          int context_local = context;
          if (force_SM_fermion_gauge_eigenstates)
          {
            int abspdg = std::abs(pdg);
            // Select SM fermions, including 4th gen, and force gauge eigenstates (context = 1).
            if (abspdg < 19 and abspdg != 9 and abspdg != 10) context_local = 1;
          }
          std::pair<int,int> pdg_pair(pdg, context_local);
          daughter_pdg_codes.push_back(pdg_pair);
        }
        set_BF(BF, 0.0, daughter_pdg_codes);
      }
    }
  }

  /// Make sure all particles listed in a set are actually known to the GAMBIT particle database
  void DecayTable::Entry::check_particles_exist(std::multiset< std::pair<int,int> >& particles) const
  {
    for (auto final_state = particles.begin(); final_state != particles.end(); ++final_state)
    {
      if (not Models::ParticleDB().has_particle(*final_state))
      {
        std::ostringstream err;
        err << "Particle with PDG code" << final_state->first << " and context integer " << endl
            << final_state->second << " is not in the in GAMBIT particle database." << endl
            << "Please add such a particle to Models/src/particle_database.cpp and recompile.";
        model_error().raise(LOCAL_INFO,err.str());
      }
    }
  }

  // ~~ hidden ~~
  /// Make sure no NaNs have been passed to the DecayTable by nefarious backends
  void DecayTable::Entry::check_BF_validity(double BF, double error, std::multiset< std::pair<int,int> >& key) const
  {
    static point_counter count("NaN BR or BR err"); count.count();

    if ((Utils::isnan(BF) or Utils::isnan(error))) // ~~ !!!!!!!
    {
      count.count_invalid();

      std::ostringstream msg;
      msg << "NaN detected in attempt to set decay table branching fraction. " << endl
          << "Final states are: " << endl;
      for(auto it = key.begin(); it !=key.end(); ++it)
      {
        msg << "  " << Models::ParticleDB().long_name(*it) << endl;
      }
      msg << "BF: " << BF << endl << "error: " << error << endl;
      msg << "Total width (GeV): " << width_in_GeV << " +" << positive_error << " -" << negative_error << endl;
      msg << "Decay calculator: " << calculator << " " << calculator_version;
      utils_error().raise(LOCAL_INFO, msg.str());
    }
  }

  /// Set branching fraction for decay to a given final state. 1. PDG-context integer pairs (vector)
  void DecayTable::Entry::set_BF(double BF, double error, const std::vector<std::pair<int,int> >& daughters)
  {
    std::multiset< std::pair<int,int> > key(daughters.begin(), daughters.end());
    check_particles_exist(key);
    check_BF_validity(BF, error, key);
    channels[key] = std::pair<double, double>(BF, error);
  }

  /// Set branching fraction for decay to a given final state. 2. full particle names (vector)
  void DecayTable::Entry::set_BF(double BF, double error, const std::vector<str>& daughters)
  {
    std::multiset< std::pair<int,int> > key;
    for (auto p = daughters.begin(); p != daughters.end(); ++p) key.insert(Models::ParticleDB().pdg_pair(*p));
    check_particles_exist(key);
    check_BF_validity(BF, error, key);
    channels[key] = std::pair<double, double>(BF, error);
  }

  /// Check if a given final state exists in this DecayTable::Entry. 1. PDG-context integer pairs (vector)
  bool DecayTable::Entry::has_channel(const std::vector<std::pair<int,int> >& daughters) const
  {
    std::multiset< std::pair<int,int> > key(daughters.begin(), daughters.end());
    check_particles_exist(key);
    return channels.find(key) != channels.end();
  }

  /// Check if a given final state exists in this DecayTable::Entry. 2. full particle names (vector)
  bool DecayTable::Entry::has_channel(const std::vector<str>& daughters) const
  {
    std::multiset< std::pair<int,int> > key;
    for (auto p = daughters.begin(); p != daughters.end(); ++p) key.insert(Models::ParticleDB().pdg_pair(*p));
    check_particles_exist(key);
    return channels.find(key) != channels.end();
  }

  /// Retrieve branching fraction for decay to a given final state. 1. PDG-context integer pairs (vector)
  double DecayTable::Entry::BF(const std::vector<std::pair<int, int> >& daughters) const
  {
    std::multiset< std::pair<int,int> > key(daughters.begin(), daughters.end());
    check_particles_exist(key);
    return channels.at(key).first;
  }

  /// Retrieve branching fraction for decay to a given final state. 2. full particle names (vector)
  double DecayTable::Entry::BF(const std::vector<str>& daughters) const
  {
    std::multiset< std::pair<int,int> > key;
    for (auto p = daughters.begin(); p != daughters.end(); ++p) key.insert(Models::ParticleDB().pdg_pair(*p));
    check_particles_exist(key);
    return channels.at(key).first;
  }


  /// Output a decay table entry as an SLHAea DECAY block
  /// @{
  SLHAea::Block DecayTable::Entry::getSLHAea_block(int v, str p, bool z, const mass_es_pseudonyms& psn)         const
  { return getSLHAea_block(v, Models::ParticleDB().pdg_pair(p), z, psn); }
  SLHAea::Block DecayTable::Entry::getSLHAea_block(int v, str p, int i, bool z, const mass_es_pseudonyms& psn)  const
  { return getSLHAea_block(v, Models::ParticleDB().pdg_pair(p,i), z, psn); }
  SLHAea::Block DecayTable::Entry::getSLHAea_block(int v, std::pair<int,int> p, bool include_zero_bfs, const mass_es_pseudonyms& psn) const
  {
    const std::map<str, int> slha1_pdgs = boost::assign::map_list_of
     ("~t_1"     , 1000006)
     ("~t_2"	   , 2000006)
     ("~b_1"	   , 1000005)
     ("~b_2"	   , 2000005)
     ("~tau_1"   , 1000015)
     ("~tau_2"   , 2000015)
     ("~nu_e_L"  , 1000012)
     ("~nu_mu_L" , 1000014)
     ("~nu_tau_L", 1000016)
     ("~d_L"	   , 1000001)
     ("~s_L"	   , 1000003)
     ("~d_R"	   , 2000001)
     ("~s_R"	   , 2000003)
     ("~e_L"	   , 1000011)
     ("~mu_L"	   , 1000013)
     ("~e_R"	   , 2000011)
     ("~mu_R"	   , 2000013)
     ("~u_L"	   , 1000002)
     ("~c_L"	   , 1000004)
     ("~u_R"	   , 2000002)
     ("~c_R"	   , 2000004)
     ("~tbar_1"     , -1000006)
     ("~tbar_2"	    , -2000006)
     ("~bbar_1"	    , -1000005)
     ("~bbar_2"	    , -2000005)
     ("~taubar_1"   , -1000015)
     ("~taubar_2"   , -2000015)
     ("~nu_ebar_L"  , -1000012)
     ("~nu_mubar_L" , -1000014)
     ("~nu_taubar_L", -1000016)
     ("~dbar_L"	    , -1000001)
     ("~sbar_L"	    , -1000003)
     ("~dbar_R"	    , -2000001)
     ("~sbar_R"	    , -2000003)
     ("~ebar_L"	    , -1000011)
     ("~mubar_L"	  , -1000013)
     ("~ebar_R"	    , -2000011)
     ("~mubar_R"	  , -2000013)
     ("~ubar_L"	    , -1000002)
     ("~cbar_L"	    , -1000004)
     ("~ubar_R"	    , -2000002)
     ("~cbar_R"	    , -2000004);

    // Make sure the particle actually exists in the database
    if (not Models::ParticleDB().has_particle(p))
    {
      std::stringstream ss;
      ss << "GAMBIT particle database does not have particle with (PDG,context) codes (" << p.first << "," << p.second << ").";
      utils_error().raise(LOCAL_INFO, ss.str());
    }

    // Add the info about the decay in general
    int pdg = p.first;
    str long_name = Models::ParticleDB().long_name(p);
    SLHAea::Line line;
    if (v == 1)
    {
      if (not psn.filled) utils_error().raise(LOCAL_INFO, "Non-empty mass_es_pseudonyms must be provided for SLHA1 DecayTable output.");
      if (psn.gauge_family_eigenstates.find(long_name) != psn.gauge_family_eigenstates.end())
      {
        long_name = psn.gauge_family_eigenstates.at(long_name);

        pdg = slha1_pdgs.at(long_name);
      }
    }
    else if (v != 2) utils_error().raise(LOCAL_INFO, "Unrecognised SLHA version requested.  Expected 1 or 2.");
    line << "DECAY" << pdg << this->width_in_GeV << "# " + long_name + " decays";
    SLHAea::Block block(std::to_string(p.first));
    block.push_back(line);
    block.insert(block.begin(),SLHAea::Line("#     PDG         Width (GeV)"));
    block.push_back("#          BF              NDA Daughter PDG codes");

    // Add the branching fraction and daughter particle PDG codes for each decay channel
    for (auto channel = channels.begin(); channel != channels.end(); ++channel)
    {
      // Skip this channel if its BF is NaN (undefined) or zero (on request)
      double BF = (channel->second).first;
      if (not Utils::isnan(BF))
      {
        if (BF > 0.0 or include_zero_bfs)
        {
          auto daughters = channel->first;
          str comment = "# BF(" + long_name + " --> ";
          line.clear();
          // Get the branching fraction and number of particles in the final state
          line << BF << daughters.size();
          // Get the PDG code for each daughter particle
          for (auto daughter = daughters.begin(); daughter != daughters.end(); ++daughter)
          {
            int daughter_pdg = daughter->first;
            str daughter_long_name = Models::ParticleDB().long_name(*daughter);
            if (v == 1)
            {
              if (psn.gauge_family_eigenstates.find(daughter_long_name) != psn.gauge_family_eigenstates.end())
              {
                daughter_long_name = psn.gauge_family_eigenstates.at(daughter_long_name);
                daughter_pdg = slha1_pdgs.at(daughter_long_name);
              }
            }
            line << daughter_pdg;
            comment += daughter_long_name + " ";
          }
          comment[comment.size()-1] = ')';
          line << comment;
          block.push_back(line);
        }
      }
    }

    return block;

  }
  /// @}

  /// Get entry in decay table for a given particle, adding the particle to the table if it is absent.
  /// Three access methods: PDG-context integer pair, full particle name, short particle name + index integer.
  /// @{
  DecayTable::Entry& DecayTable::operator()(std::pair<int,int> p)              { return particles[p]; }
  DecayTable::Entry& DecayTable::operator()(str p)                             { return particles[Models::ParticleDB().pdg_pair(p)]; }
  DecayTable::Entry& DecayTable::operator()(str p, int i)                      { return particles[Models::ParticleDB().pdg_pair(p,i)]; }
  const DecayTable::Entry& DecayTable::operator()(std::pair<int,int> p) const  { return particles.at(p); }
  const DecayTable::Entry& DecayTable::operator()(str p) const                 { return particles.at(Models::ParticleDB().pdg_pair(p)); }
  const DecayTable::Entry& DecayTable::operator()(str p, int i) const          { return particles.at(Models::ParticleDB().pdg_pair(p,i)); }
  /// @}

  /// Get entry in decay table for a give particle, throwing an error if particle is absent.
  /// Three access methods: PDG-context integer pair, full particle name, short particle name + index integer.
  /// @{
  DecayTable::Entry& DecayTable::at(std::pair<int,int> p)              { return particles.at(p); }
  DecayTable::Entry& DecayTable::at(str p)                             { return particles.at(Models::ParticleDB().pdg_pair(p)); }
  DecayTable::Entry& DecayTable::at(str p, int i)                      { return particles.at(Models::ParticleDB().pdg_pair(p,i)); }
  const DecayTable::Entry& DecayTable::at(std::pair<int,int> p) const  { return particles.at(p); }
  const DecayTable::Entry& DecayTable::at(str p) const                 { return particles.at(Models::ParticleDB().pdg_pair(p)); }
  const DecayTable::Entry& DecayTable::at(str p, int i) const          { return particles.at(Models::ParticleDB().pdg_pair(p,i)); }
  /// @}


  /// Sum up the branching fractions for a single particle's entry and return the result.
  double DecayTable::Entry::sum_BF() const
  {
    double sum = 0.0;
    for (auto channel = channels.begin(); channel != channels.end(); ++channel)
    {
      sum += (channel->second).first;
    }
    return sum;
  }

}

