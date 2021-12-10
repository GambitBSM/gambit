///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Object for carrying around particle spectrum
///  data.
///  Primarily an interface to SLHAea objects,
///  carrying SLHA style information.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Ben Farmer
///          (benjamin.farmer@imperial.ac.uk)
///  \date 2019 June
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Oct
///
///  *********************************************
///
///  \file
///

#include <sstream>
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Elements/slhaea_spec_helpers.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Models/partmap.hpp"

// Easy name for particle database access
#define PDB Models::ParticleDB()

//#define SPECTRUM_DEBUG

namespace Gambit
{
   /// Less confusing name for SLHAea container class
   typedef SLHAea::Coll SLHAstruct;

   /// @{ Spectrum class member function definitions

   /// @{ Constructors/destructors

   /// Default constructor
   Spectrum::Spectrum() : mySLHAea(), myContents() {}

   /// Construct from SLHAea object (also specifying what SpectrumContents should apply, which defines how to interpret the SLHAea blocks)
   Spectrum::Spectrum(const SLHAstruct& slha, const SpectrumContents::Contents& contents, const double scale_in, const bool ignore_input_transform)
    : mySLHAea(contents.transformInputSLHAea(slha,ignore_input_transform))
    , SMINPUTS(mySLHAea)
    , myContents(contents)
    , scale(scale_in)
   {
      /// DEBUG: Write internal file to disk so we can check problems raised by verify_contents
      std::ofstream ofs("pre_verify_contents_"+contents.getName()+".slha");
      ofs << mySLHAea;
      ofs.close();
      /// Make sure the supplied slhaea object contains everything that the contents definition requires
      contents.verify_contents(*this);
   }


   /// @}

   /// Return scale at which all running parameters are defined (in GeV)
   /// (except for certain parameters which are defined at fixed scales; these are not considered as "running")
   double Spectrum::GetScale() const { return scale; }

   /// Helper function for checking if a particle or ratio has been requested as an absolute value
   bool is_abs(str& s)
   {
      if (s.at(0) != '|' or *s.rbegin() != '|') return false;
      s = s.substr(1, s.size()-2);
      return true;
   }

   /// Check the that the spectrum satisifies any mass cuts requested from the yaml file.
   void Spectrum::check_mass_cuts(const Options &options)
   {
     // Retrieve mass cuts from options 
     mass_cuts = retrieve_mass_cuts(options);

     if (not mass_cuts.cuts.empty())
     {
       for (auto it = mass_cuts.cuts.begin(); it != mass_cuts.cuts.end(); ++it)
       {
         str p = it->first;
         bool absolute_value = is_abs(p);
         const double& low = it->second.first;
         const double& high = it->second.second;
         #ifdef SPECTRUM_DEBUG
           cout << "Applying mass cut " << low << " GeV < " << (absolute_value ? "|mass("+p+")|" : "mass("+p+")") << " < " << high << " GeV" << endl;
         #endif
         if (not has(Par::Pole_Mass, p)) utils_error().raise(LOCAL_INFO, "Cannot cut on mass of unrecognised particle: " + p);
         double m = get(Par::Pole_Mass, p);
         if (absolute_value) m = std::abs(m);
         #ifdef SPECTRUM_DEBUG
           cout << "Actual value: " << m << endl;
         #endif
         if (m < low or m > high) invalid_point().raise(p + " failed requested mass cut.");
       }
     }
     if (not mass_cuts.ratio_cuts.empty())
     {
       for (auto it = mass_cuts.ratio_cuts.begin(); it != mass_cuts.ratio_cuts.end(); ++it)
       {
         str p1 = it->first.first;
         str p2 = it->first.second;
         bool absolute_value1 = is_abs(p1);
         bool absolute_value2 = is_abs(p2);
         const double& low = it->second.first;
         const double& high = it->second.second;
         #ifdef SPECTRUM_DEBUG
           cout << "Applying mass ratio cut " << low << " < "
                << (absolute_value1 ? "|mass("+p1+")|" : "mass("+p1+")") << " / "
                << (absolute_value2 ? "|mass("+p2+")|" : "mass("+p2+")")
                << " < " << high << endl;
         #endif
         if (not has(Par::Pole_Mass, p1)) utils_error().raise(LOCAL_INFO, "Cannot cut on ratio with mass of unrecognised particle: " + p1);
         if (not has(Par::Pole_Mass, p2)) utils_error().raise(LOCAL_INFO, "Cannot cut on ratio with mass of unrecognised particle: " + p2);
         double m1 = get(Par::Pole_Mass, p1);
         double m2 = get(Par::Pole_Mass, p2);
         if (absolute_value1) m1 = std::abs(m1);
         if (absolute_value2) m2 = std::abs(m2);
         double mratio = m1/m2;
         #ifdef SPECTRUM_DEBUG
           cout << "Actual value: " << mratio << endl;
         #endif
         if (mratio < low or mratio > high) invalid_point().raise(p1 + "/" + p2 +" failed requested mass ratio cut.");
       }
     }
     if (not mass_cuts.diff_cuts.empty())
     {
       for (auto it = mass_cuts.diff_cuts.begin(); it != mass_cuts.diff_cuts.end(); ++it)
       {
         str p1 = it->first.first;
         str p2 = it->first.second;
         bool absolute_value1 = is_abs(p1);
         bool absolute_value2 = is_abs(p2);
         const double& low = it->second.first;
         const double& high = it->second.second;
         #ifdef SPECTRUM_DEBUG
           cout << "Applying mass diff cut " << low << " < |"
                << (absolute_value1 ? "|mass("+p1+")|" : "mass("+p1+")") << " - "
                << (absolute_value2 ? "|mass("+p2+")|" : "mass("+p2+")")
                << "| < " << high << endl;
         #endif
         if (not has(Par::Pole_Mass, p1)) utils_error().raise(LOCAL_INFO, "Cannot cut on ratio with mass of unrecognised particle: " + p1);
         if (not has(Par::Pole_Mass, p2)) utils_error().raise(LOCAL_INFO, "Cannot cut on ratio with mass of unrecognised particle: " + p2);
         double m1 = get(Par::Pole_Mass, p1);
         double m2 = get(Par::Pole_Mass, p2);
         if (absolute_value1) m1 = std::abs(m1);
         if (absolute_value2) m2 = std::abs(m2);
         double mdiff = std::abs(m1 - m2);
         #ifdef SPECTRUM_DEBUG
           cout << "Actual value: " << mdiff << endl;
         #endif
         if (mdiff < low or mdiff > high) invalid_point().raise("|" + p1 + "-" + p2 +"| failed requested mass diff cut.");
       }
     }

   }

   /// Overloade version of check_cuts with safe pointer
   void Spectrum::check_mass_cuts(const safe_ptr<Options> &options)
   {
     check_mass_cuts(*options);
   }
 
  /// Set constraints on masses and mass ratios that cause the spectrum to be declared "invalid" if they are violated
   void Spectrum::set_mass_cuts(const cuts_info& cuts)
   {
     mass_cuts.cuts       = cuts.cuts;
     mass_cuts.ratio_cuts = cuts.ratio_cuts;
     mass_cuts.diff_cuts  = cuts.diff_cuts;
   }
 
   /// Master checker function to see if a parameter request matches the spectrum contents
   bool Spectrum::has(const Par::Tags partype, const std::string& name_in, const std::vector<int>& indices_in, bool auto_check_antiparticle_name) const
   {
      bool found(true);
      std::string name;
      std::vector<int> indices;
      #ifdef SPECTRUM_DEBUG
      std::cout<<"Checking if "<<Par::toString.at(partype)<<" "<<name_in<<" "<<indices_in<<" is in this Spectrum object..."<<std::endl; 
      #endif

      // First figure out which version of this parameter is supposed to 
      // be in this Spectrum according to the Contents object.
      bool success;
      std::pair<std::string,std::vector<int>> new_name_and_indices;
      new_name_and_indices = myContents.find_matching_parameter(partype, name_in, indices_in, success);
      if(success)
      {
         name = new_name_and_indices.first;
         indices = new_name_and_indices.second;
         #ifdef SPECTRUM_DEBUG
         std::cout<<"Contents DOES contain "<<Par::toString.at(partype)<<" "<<name<<" "<<indices<<"; should therefore be in this Spectrum object..."<<std::endl; 
         #endif
 
         // Spectrum should have this type and name, and indices are within bounds (if any indices)
         // Now check if the entry actually exists in the wrapped
         // SLHAea object.
         // This will be an error if it fails, because it is *supposed* to exist.
         std::pair<std::string,std::vector<int>> slha_loc = myContents.get_SLHA_indices(partype,name,indices);
         std::string      block        = slha_loc.first;
         std::vector<int> SLHA_indices = slha_loc.second;

         #ifdef SPECTRUM_DEBUG
         std::cout<<"Parameter is expected at SLHA location: "<<block<<", "<<SLHA_indices<<std::endl;
         #endif
 
         // First check if the required block even exists
         if(SLHAea_block_exists(mySLHAea, block))
         {
            bool in_slhaea(false);
            switch(SLHA_indices.size())
            {
               case 0:
               {
                  // I think there are some weird SLHA cases of things with no indices
                  // Will ignore them for now. Raise error to get user to ask for this feature
                  std::ostringstream errmsg;
                  errmsg<<"Error while checking for existence of Spectrum entry "<<Par::toString.at(partype)<<" '"<<name<<"'! It seems like this parameter has been defined as being associated with an SLHA block but no index. This is allowed by SLHA, but Spectrum objects are not currently compatible with them. Please file a bug report to request this feature if you need it.";
                  utils_error().raise(LOCAL_INFO,errmsg.str());
                  break;
               }
               case 1:
               { 
                  if(SLHAea_entry_exists(mySLHAea, block, SLHA_indices.at(0))) in_slhaea = true;
                  break;
               }
               case 2:
               {
                  if(SLHAea_entry_exists(mySLHAea, block, SLHA_indices.at(0), SLHA_indices.at(1))) in_slhaea = true;
                  break;
               }
            }

            if(in_slhaea)
            {
               found = true;
            }
            else
            {
               // Required entry doesn't exist!
               std::ostringstream errmsg;
               errmsg<<"Error while checking for existence of Spectrum entry "<<Par::toString.at(partype)<<" '"<<name<<"'! A parameter with this tag, name, and indices should exist in this spectrum, however no entry was found in the wrapped SLHAea object at the expected location (BLOCK "<<block<<", indices: "<<SLHA_indices<<")";
               utils_error().raise(LOCAL_INFO,errmsg.str());
            }
         }
         else
         {
            // Required block doesn't even exist! So parameter definitely doesn't.
            // But this block *should* exist according to the contents, so this is
            // an error.
            std::ostringstream errmsg;
            errmsg<<"Error while checking for existence of Spectrum entry "<<Par::toString.at(partype)<<" '"<<name<<"'! A parameter with this tag and name should exist in this spectrum, however the wrapped SLHAea object is missing the required block (BLOCK "<<block<<")";
            utils_error().raise(LOCAL_INFO,errmsg.str());
         }

      }
      else
      {
         // No parameter by this name found, or any particle database transformation of it.
         found = false;
      }

      return found;
   }

   /// Master getter function to retrieve parameters from Spectrum object (digging them out of the wrapped SLHAea object)
   double Spectrum::get(const Par::Tags partype, const std::string& name_in, const std::vector<int>& indices_in) const
   {
      double entry;
      // First convert to name and indices matching interal use by SpectrumContents
      // Also checks that entry is compatible with declared contents
      std::pair<std::string,std::vector<int>> matched_name_and_indices;
      bool success;
      matched_name_and_indices = myContents.find_matching_parameter(partype, name_in, indices_in, success);
      if(success)
      { 
         std::string      name    = matched_name_and_indices.first;
         std::vector<int> indices = matched_name_and_indices.second;
       
         // Now entry has been confirmed to exist, can retrieve it.
         // Should be safe to rely on the error checking that occurs in the 'has' function
         std::pair<std::string,std::vector<int>> slha_loc = myContents.get_SLHA_indices(partype,name,indices);
         std::string      block        = slha_loc.first;
         std::vector<int> SLHA_indices = slha_loc.second;
         switch(SLHA_indices.size())
         {
            case 0:
            {
               // I think there are some weird SLHA cases of things with no indices
               // Will ignore them for now. Raise error to get user to ask for this feature
               std::ostringstream errmsg;
               errmsg<<"Error retrieving Spectrum entry "<<Par::toString.at(partype)<<" '"<<name<<"'! It seems like this parameter has been defined as being associated with an SLHA block but no index. This is allowed by SLHA, but Spectrum objects are not currently compatible with them. Please file a bug report to request this feature if you need it.";
               utils_error().raise(LOCAL_INFO,errmsg.str());
               break;
            }
            case 1:
            {
               entry = SLHAea_get(mySLHAea, block, SLHA_indices.at(0));
               break;
            }
            case 2:
            {
               entry = SLHAea_get(mySLHAea, block, SLHA_indices.at(0), SLHA_indices.at(1));
               break;
            }
         }
      }
      else
      {
         std::ostringstream errmsg;
         errmsg<<"Error retrieving Spectrum entry "<<Par::toString.at(partype)<<" '"<<name_in<<indices_in<<"'! No matching parameter is defined in the SpectrumContents assigned to this spectrum ("<<myContents.getName()<<")."; 
         utils_error().raise(LOCAL_INFO,errmsg.str());       
      }
      return entry;
   }

   /// @{ getters/checkers/setters for spectrum parameters, with various numbers of indices
   ///    All call the 'master' getter/checker/setter functions in the end
   bool Spectrum::has(const Par::Tags partype, const std::string& name) const
   {
      std::vector<int> no_indices;  
      return has(partype,name,no_indices);
   }

   double Spectrum::get(const Par::Tags partype, const std::string& name) const
   {
      std::vector<int> no_indices;  
      return get(partype,name,no_indices);
   }
 
   void Spectrum::set(const double value, const Par::Tags partype, const std::string& name)
   {
      std::vector<int> no_indices;  
      set(value,partype,name,no_indices);
   }

   bool Spectrum::has(const Par::Tags partype, const std::string& name, const int index) const
   {
      std::vector<int> one_index;
      one_index.push_back(index);  
      return has(partype,name,one_index);
   }

   double Spectrum::get(const Par::Tags partype, const std::string& name, const int index) const
   {
      std::vector<int> one_index;
      one_index.push_back(index);  
      return get(partype,name,one_index);
   }

   void Spectrum::set(const double value, const Par::Tags partype, const std::string& name, const int index)
   {
      std::vector<int> one_index;
      one_index.push_back(index);  
      set(value,partype,name,one_index);
   }


   bool Spectrum::has(const Par::Tags partype, const std::string& name, const int index1, const int index2) const
   {
      std::vector<int> two_indices;
      two_indices.push_back(index1);
      two_indices.push_back(index2);  
      return has(partype,name,two_indices);
   }

   double Spectrum::get(const Par::Tags partype, const std::string& name, const int index1, const int index2) const
   {
      std::vector<int> two_indices;
      two_indices.push_back(index1);
      two_indices.push_back(index2);  
      return get(partype,name,two_indices);
   }

   void Spectrum::set(const double value, const Par::Tags partype, const std::string& name, const int index1, const int index2)
   {
      std::vector<int> two_indices;
      two_indices.push_back(index1);
      two_indices.push_back(index2);  
      set(value,partype,name,two_indices);
   }


   /// @{ PDB getter/checker/setter overloads

   /* Input PDG code plus context integer as separate arguments */
   bool Spectrum::has(const Par::Tags partype,
                        const int pdg_code, const int context) const
   {
      return has( partype, std::make_pair(pdg_code,context) );
   }

   /* Input PDG code plus context integer as separate arguments */
   double Spectrum::get(const Par::Tags partype,
                        const int pdg_code, const int context) const
   {
      return get( partype, std::make_pair(pdg_code,context) );
   }

   /* Input PDG code plus context integer as separate arguments */
   void Spectrum::set(const double value, const Par::Tags partype,
                        const int pdg_code, const int context)
   {
      set(value, partype, std::make_pair(pdg_code,context) );
   }


   /* Input PDG code plus context integer as pair */
   bool Spectrum::has(const Par::Tags partype,
                        const std::pair<int,int> pdgpr) const
   {
      /* If there is a short name, then retrieve that plus the index */
      if( Models::ParticleDB().has_short_name(pdgpr) )
      {
        return has( partype, Models::ParticleDB().short_name_pair(pdgpr) );
      }
      else /* Use the long name with no index instead */
      {
        return has( partype, Models::ParticleDB().long_name(pdgpr) );
      }
   }

   /* Input PDG code plus context integer as pair */
   double Spectrum::get(const Par::Tags partype,
                        const std::pair<int,int> pdgpr) const
   {
      /* If there is a short name, then retrieve that plus the index */
      if( Models::ParticleDB().has_short_name(pdgpr) )
      {
        return get( partype, Models::ParticleDB().short_name_pair(pdgpr) );
      }
      else /* Use the long name with no index instead */
      {
        return get( partype, Models::ParticleDB().long_name(pdgpr) );
      }
   }

   /* Input PDG code plus context integer as pair */
   void Spectrum::set(const double value, const Par::Tags partype,
                        const std::pair<int,int> pdgpr)
   {
      /* If there is a short name, then retrieve that plus the index */
      if( Models::ParticleDB().has_short_name(pdgpr) )
      {
        set(value, partype, Models::ParticleDB().short_name_pair(pdgpr) );
      }
      else /* Use the long name with no index instead */
      {
        set(value, partype, Models::ParticleDB().long_name(pdgpr) );
      }
   }


   /* Input short name plus index as pair */
   bool Spectrum::has(const Par::Tags partype,
                        const std::pair<str,int> shortpr) const
   {
      return has( partype, shortpr.first, shortpr.second);
   }

   /* Input short name plus index as pair */
   double Spectrum::get(const Par::Tags partype,
                        const std::pair<str,int> shortpr) const
   {
      return get( partype, shortpr.first, shortpr.second);
   }

   /* Input short name plus index as pair */
   void Spectrum::set(const double value, const Par::Tags partype,
                        const std::pair<str,int> shortpr)
   {
      set(value, partype, shortpr.first, shortpr.second);
   }


   /// @}

   /// @{ Getters which first check the sanity of the thing they are returning

   double Spectrum::safeget(const Par::Tags partype,
                            const std::string& mass) const
   {
      double result = get(partype, mass);
      if (Utils::isnan(result))
         utils_error().raise(LOCAL_INFO,"Spectrum parameter is nan!!");
      return result;
   }

   double Spectrum::safeget(const Par::Tags partype,
                            const std::string& mass, const int index) const
   {
      double result = get(partype, mass, index);
      if (Utils::isnan(result))
         utils_error().raise(LOCAL_INFO,"Spectrum parameter is nan!!");
      return result;
   }

   double Spectrum::safeget(const Par::Tags partype,
                            const std::string& mass, 
                            const int index1, const int index2) const
   {
      double result = get(partype, mass, index1, index2);
      if (Utils::isnan(result))
         utils_error().raise(LOCAL_INFO,"Spectrum parameter is nan!!");
      return result;
   }

   double Spectrum::safeget(const Par::Tags partype,
                            const int pdg_code, const int context) const
   {
      double result = get(partype, pdg_code, context);
      if (Utils::isnan(result))
         utils_error().raise(LOCAL_INFO,"Spectrum parameter is nan!!");
      return result;
   }

   double Spectrum::safeget(const Par::Tags partype,
                            const std::pair<int,int> pdgpr) const
   {
      double result = get(partype, pdgpr);
      if (Utils::isnan(result))
         utils_error().raise(LOCAL_INFO,"Spectrum parameter is nan!!");
      return result;
   }

   double Spectrum::safeget(const Par::Tags partype,
                            const std::pair<str,int> shortpr) const
   {
      double result = get(partype, shortpr);
      if (Utils::isnan(result))
         utils_error().raise(LOCAL_INFO,"Spectrum parameter is nan!!");
      return result;
   }

   /// @}

   /// @{ Setter functions

   /// Master setter function (general case)
   void Spectrum::set(const double value, const Par::Tags partype, const str& name_in, const std::vector<int>& indices_in)
   {
      // First convert to name and indices matching interal use by SpectrumContents
      // Also checks that entry is compatible with declared contents
      std::pair<std::string,std::vector<int>> matched_name_and_indices;
      bool success;
      matched_name_and_indices = myContents.find_matching_parameter(partype, name_in, indices_in, success);
      if(success)
      {
         std::string      name    = matched_name_and_indices.first;
         std::vector<int> indices = matched_name_and_indices.second;
 
         // Debug
         //std::cout<<"Parameter "<<name_in<<indices_in<<" has been matched to name "<<name<<indices<<"; will search for SLHA location of the latter and assign the value "<<value<<" there."<<std::endl;

         // Now entry has been confirmed to exist, can set its value.
         // Should be safe to rely on the error checking that occurs in the 'has' function
         std::pair<std::string,std::vector<int>> slha_loc = myContents.get_SLHA_indices(partype,name,indices);
         std::string      block        = slha_loc.first;
         std::vector<int> SLHA_indices = slha_loc.second;

         // Debug
         //std::cout<<"Located parameter "<<name<<indices<<" SLHA position: BLOCK "<<block<<" "<<SLHA_indices<<std::endl;

         std::stringstream comment;
         comment << name;
         if(indices.size()>0) comment << indices;
         comment << " ("<<Par::toString.at(partype)<<") ***modified manually***";

         switch(SLHA_indices.size())
         {
            case 0:
            {
               // I think there are some weird SLHA cases of things with no indices
               // Will ignore them for now. Raise error to get user to ask for this feature
               std::ostringstream errmsg;
               errmsg<<"Error retrieving Spectrum entry "<<Par::toString.at(partype)<<" '"<<name<<"'! It seems like this parameter has been defined as being associated with an SLHA block but no index. This is allowed by SLHA, but Spectrum objects are not currently compatible with them. Please file a bug report to request this feature if you need it.";
               utils_error().raise(LOCAL_INFO,errmsg.str());
               break;
            }
            case 1:
            {
               int index = SLHA_indices.at(0);
               SLHAea_add(mySLHAea, block, index, value, comment.str(), true);
               break;
            }
            case 2:
            {
               int index1 = SLHA_indices.at(0);
               int index2 = SLHA_indices.at(1);
               SLHAea_add(mySLHAea, block, index1, index2, value, comment.str(), true);
               break;
            }
         }
      }
      else
      {
         std::ostringstream errmsg;
         errmsg<<"Error setting Spectrum entry "<<Par::toString.at(partype)<<" '"<<name_in<<indices_in<<" to value "<<value<<"'! No matching parameter is defined in the SpectrumContents assigned to this spectrum ("<<myContents.getName()<<")."; 
         utils_error().raise(LOCAL_INFO,errmsg.str());       
      }
   }

   //void Spectrum::set(const Par::Tags, const double, const str&);
   //void Spectrum::set(const Par::Tags, const double, const str&, const int);
   //void Spectrum::set(const Par::Tags, const double, const str&, const int, const int);

   //
   ///* Setters for setting values of many parameters at once, by iterating over the supplied string names or indices, or both */
   ///// Master set_many function (general case)
   //void Spectrum::set_many(const Par::Tags, const double, const std::vector<str>&, const std::vector<int>);
   //void Spectrum::set_many(const Par::Tags, const double, const std::vector<str>&);
   //void Spectrum::set_many(const Par::Tags, const double, const std::vector<str>&, const int);
   //void Spectrum::set_many(const Par::Tags, const double, const str&, const std::vector<int>);



   /// @}

   /// SLHAea object getter
   /// Retrieves wrapped SLHAea object. 
   SLHAstruct Spectrum::getRawSLHAea() const
   {
      return mySLHAea;
   }

   /// Return an SLHA-compliant (or similar) SLHAea object
   /// Takes an integer specifying version of standard to use
   SLHAstruct Spectrum::getSLHAea(const int version) const
   {
      return myContents.generateOutputSLHAea(*this,version);
   }

   /// Output spectrum contents as an SLHA file, using getSLHAea.
   void Spectrum::writeSLHAfile(const str& filename, const int version) const
   {
      Utils::FileLock mylock(filename);
      mylock.get_lock();
      std::ofstream ofs(filename);
      ofs << getSLHAea(version); 
      ofs.close();
      mylock.release_lock();
   }

   /// Helper function to drop SLHA files
   void Spectrum::drop_SLHAs_if_requested(const safe_ptr<Options>& runOptions, const str& default_name)
   {
      if (runOptions->getValueOrDef<bool>(false, "drop_SLHA_file"))
      {
         // Spit out the full spectrum as SLHA file.
         str prefix   = runOptions->getValueOrDef<str>("", "SLHA_output_prefix");
         str filename = runOptions->getValueOrDef<str>(default_name, "SLHA_output_filename");
         int version  = runOptions->getValueOrDef<int>(2, "SLHA_version");
         std::stringstream ss;
         ss<<prefix<<filename<<".slha"<<version;
         writeSLHAfile(ss.str(),version);
      }
   }

   /// Get the SMINPUTS struct
   // TODO: Check with Ben if this is the right way
   const SMInputs& Spectrum::get_SMInputs() const {return SMINPUTS;}

   /// Get the SpectrumContents
   const SpectrumContents::Contents& Spectrum::get_SpectrumContents() const { return myContents; }

   // The expressions in all of the following CKM functions are from the CKMFitter paper hep-ph/0406184v3.

   ///Helper function to calculate Wolfenstein rho+i*eta from rhobar and etabar
   std::complex<double> Spectrum::rhoplusieta(double lambda, double A, double rhobar, double etabar)
   {
     std::complex<double> x(rhobar, etabar);
     double y = pow(A*lambda*lambda,2);
     return sqrt((1.0-y)/(1.0-lambda*lambda))*x/(1.0-x*y);
   }

   /// CKM Wolfenstein --> V_ud standard parameterisation convertor
   double Spectrum::Wolf2V_ud(double l, double A, double rhobar, double etabar)
   {
     double norm = std::norm(rhoplusieta(l,A,rhobar,etabar));
     return 1.0 - 0.5*pow(l,2) - 0.125*pow(l,4) - 0.0625*pow(l,6)*(1.0+8.0*A*A*norm)
            - 0.0078125*pow(l,8)*(5.0-32.0*A*A*norm);
   }

   /// CKM Wolfenstein --> V_us standard parameterisation convertor
   double Spectrum::Wolf2V_us(double l, double A, double rhobar, double etabar)
   {
     double norm = std::norm(rhoplusieta(l,A,rhobar,etabar));
     return l - 0.5*A*A*pow(l,7)*norm;
   }

   /// CKM Wolfenstein --> V_ub standard parameterisation convertor
   std::complex<double> Spectrum::Wolf2V_ub(double l, double A, double rhobar, double etabar)
   {
     return A*pow(l,3)*std::conj(rhoplusieta(l,A,rhobar,etabar));
   }

   /// CKM Wolfenstein --> V_cd standard parameterisation convertor
   std::complex<double> Spectrum::Wolf2V_cd(double l, double A, double rhobar, double etabar)
   {
     std::complex<double> x(rhoplusieta(l,A,rhobar,etabar));
     return 0.5*pow(A*l,2)*(pow(l,3)*(1.0-2.0*x) + pow(l,5)*x) - l;
   }

   /// CKM Wolfenstein --> V_cs standard parameterisation convertor
   std::complex<double> Spectrum::Wolf2V_cs(double l, double A, double rhobar, double etabar)
   {
     double l2 = l*l;
     double fA2 = 4.0*A*A;
     return 1.0 - 0.5*l2 - 0.125*l2*l2*(1.0+fA2)
            - 0.0625*pow(l2,3)*(1.0-fA2+4.0*fA2*rhoplusieta(l,A,rhobar,etabar))
            - 0.0078125*pow(l2,4)*(5.0-fA2*(2.0+4.0*fA2));
   }

   /// CKM Wolfenstein --> V_cb standard parameterisation convertor
   double Spectrum::Wolf2V_cb(double l, double A, double rhobar, double etabar)
   {
     return A*l*l * (1.0 - 0.5*A*A*pow(l,6)*std::norm(rhoplusieta(l,A,rhobar,etabar)));
   }

   /// CKM Wolfenstein --> V_td standard parameterisation convertor
   std::complex<double> Spectrum::Wolf2V_td(double l, double A, double rhobar, double etabar)
   {
     std::complex<double> x(rhoplusieta(l,A,rhobar,etabar));
     return A*l*l * (l*(1.0-x) + 0.5*pow(l,3)*x + 0.125*pow(l,5)*(1.0+4.0*A*A)*x);
   }

   /// CKM Wolfenstein --> V_ts standard parameterisation convertor
   std::complex<double> Spectrum::Wolf2V_ts(double l, double A, double rhobar, double etabar)
   {
     std::complex<double> x(rhoplusieta(l,A,rhobar,etabar));
     return A*l*l * (0.5*pow(l,2)*(1.0-2.0*x) + 0.125*pow(l,4) + 0.0625*pow(l,6)*(1.0+8.0*A*A*x) - 1.0);
   }

   /// CKM Wolfenstein --> V_tb standard parameterisation convertor
   double Spectrum::Wolf2V_tb(double l, double A, double rhobar, double etabar)
   {
     double norm = std::norm(rhoplusieta(l,A,rhobar,etabar));
     double l4 = pow(l,4);
     return 1.0 - 0.5*A*A*l4 * (1.0 + l*l*norm + 0.25*A*A*l4);
   }

} // end namespace Gambit

#undef PDB
