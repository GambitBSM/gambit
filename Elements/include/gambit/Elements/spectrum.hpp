//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  This class is used to deliver both information defined in the Standard
///  Model (or potentially just QED X QCD) as a low-energy effective theory (as
///  opposed to correspending information defined in a high-energy model) as well as a
///  corresponding high-energy theory. Parameters defined in the low-energy model are
///  often used as input to a physics calculators. In addition, parameters used
///  to define the Standard Model, in SLHA2 format, are provided in the
///  SMINPUTS data member.
///
///  Access to the pole masses of either SubSpectrum is provided by the
///  "get_Pole_Mass" function, which will search both subspectra for a match.
///  For running parameters, one should access them via the getters of "LE" or
///  "HE" subspectra.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Mar
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 May
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///  \date 2016 Feb
///
///  *********************************************

#ifndef __Spectrum_hpp__
#define __Spectrum_hpp__

#include <complex>

#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/yaml_options.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/Elements/subspectrum.hpp"
#include "gambit/Elements/slhaea_spec_helpers.hpp"
#include "gambit/Models/partmap.hpp"
#include "gambit/Models/safe_param_map.hpp"

/// YAML overloads for mass cut and mass cut ratio constituents
namespace YAML
{

  typedef std::pair<std::string, std::pair<double, double> > sdd;
  typedef std::pair<std::pair<std::string,std::string>, std::pair<double, double> > ssdd;

  template<>
  struct convert<sdd>
  {
    static Node encode(const sdd& rhs)
    {
      Node node;
      node.push_back(rhs.first);
      node.push_back(rhs.second.first);
      node.push_back(rhs.second.second);
      return node;
    }

    static bool decode(const Node& node, sdd& rhs)
    {
      if(!node.IsSequence() || node.size() != 3) return false;
      rhs.first         = node[0].as<std::string>();
      rhs.second.first  = node[1].as<double>();
      rhs.second.second = node[2].as<double>();
      return true;
    }
  };

  template<>
  struct convert<ssdd>
  {
    static Node encode(const ssdd& rhs)
    {
      Node node;
      node.push_back(rhs.first.first);
      node.push_back(rhs.first.second);
      node.push_back(rhs.second.first);
      node.push_back(rhs.second.second);
      return node;
    }

    static bool decode(const Node& node, ssdd& rhs)
    {
      if(!node.IsSequence() || node.size() != 4) return false;
      rhs.first.first   = node[0].as<std::string>();
      rhs.first.second  = node[1].as<std::string>();
      rhs.second.first  = node[2].as<double>();
      rhs.second.second = node[3].as<double>();
      return true;
    }
  };

}


namespace Gambit
{

   /// "Standard Model" (low-energy) plus high-energy model container class
   class Spectrum
   {
      /// Friend function: swap resources of two Spectrum objects
      friend void swap(Spectrum& first, Spectrum& second);

      public:

         /// Typedefs for making it easier to manipulate mass cut and mass ratio cut info.
         /// @{
         typedef std::vector<YAML::sdd>  mc_info;
         typedef std::vector<YAML::ssdd> mr_info;
         /// @}

      private:

         /// Variables
         /// @{
         std::unique_ptr<SubSpectrum> LE_new; // low energy model
         std::unique_ptr<SubSpectrum> HE_new; // high energy model
         SubSpectrum* LE;
         SubSpectrum* HE;
         SMInputs SMINPUTS;
         const std::map<str, safe_ptr<const double> >* input_Param;
         const mc_info* mass_cuts;
         const mr_info* mass_ratio_cuts;
         bool initialised;
         /// @}

         /// Check if object has been fully initialised
         void check_init() const;

         ///Calculate Wolfenstein rho+i*eta from rhobar and etabar
         static std::complex<double> rhoplusieta(double, double, double, double);

      public:

         /// @{ Constructors/Destructors
         /// Need custom copy and move constructors plus copy-assignment operator
         /// in order to manage the unique_ptrs properly.

         /// Default constructor
         Spectrum();
         /// Construct new object, cloning the SubSpectrum objects supplied and taking possession of them.
         Spectrum(const SubSpectrum& le, const SubSpectrum& he, const SMInputs& smi, const std::map<str, safe_ptr<const double> >* input_Param, const mc_info&, const mr_info&);
         /// Construct new object, wrapping existing SubSpectrum objects
         ///  Make sure the original objects don't get deleted before this wrapper does!
         Spectrum(SubSpectrum* const le, SubSpectrum* const he, const SMInputs& smi, const std::map<str, safe_ptr<const double> >* input_Param, const mc_info&, const mr_info&);

         /// Construct new object, automatically creating an SMSimpleSpec as the LE subspectrum, and cloning the HE SubSpectrum object supplied and taking possession of it.
         /// (won't make a version of this taking a pointer, since this is an "advanced" task, let people use the full contructor to do it.)
         Spectrum(const SubSpectrum& he, const SMInputs& smi, const std::map<str, safe_ptr<const double> >* input_Param, const mc_info&, const mr_info&);

         /// Copy constructor, clones SubSpectrum objects.
         /// Make a non-const copy in order to use e.g. RunBothToScale function.
         Spectrum(const Spectrum& other);
         /// Copy-assignment
         /// Using "copy-and-swap" idiom
         Spectrum& operator=(const Spectrum& other);
         /// Move constructor
         Spectrum(Spectrum&& other);

         /// @}

         /// Linked running
         /// Only possible with non-const object
         void RunBothToScale(double scale);

         /// Check the that the spectrum satisifies any mass cuts requested from the yaml file.
         void check_mass_cuts();

         /// @{ Standard SubSpectrum getters
         /// Return references to internal data members. Make sure original Spectrum object doesn't
         /// get destroyed before you finish using these or you will cause a segfault.
         SubSpectrum& get_LE();
         SubSpectrum& get_HE();
         SMInputs&    get_SMInputs();
         // const versions
         const SubSpectrum& get_LE() const;
         const SubSpectrum& get_HE() const;
         const SMInputs& get_SMInputs() const;
         /// @}

         /// @{ Clone SubSpectrum getters
         /// To clone whole object, just use copy constructor.
         std::unique_ptr<SubSpectrum> clone_LE() const;
         std::unique_ptr<SubSpectrum> clone_HE() const;
         /// @}

         /// @{ Pole mass getters
         /// "Shortcut" getters to access pole masses in hosted SubSpectrum objects.
         /// HE object given higher priority; if no match found, LE object will be
         /// checked. If still no match, error is thrown.
         bool   has(const Par::Tags partype, const std::string& mass) const;
         double get(const Par::Tags partype, const std::string& mass) const;
         bool   has(const Par::Tags partype, const std::string& mass, const int index) const;
         double get(const Par::Tags partype, const std::string& mass, const int index) const;
         bool   has(const Par::Tags partype, const std::string& mass, const int index1, const int index2) const;
         double get(const Par::Tags partype, const std::string& mass, const int index1, const int index2) const;

         /// @{ PDB getter/checker overloads
         bool   has(const Par::Tags partype, const int pdg_code, const int context) const;
         double get(const Par::Tags partype, const int pdg_code, const int context) const;
         bool   has(const Par::Tags partype, const std::pair<int,int> pdgpr) const;
         double get(const Par::Tags partype, const std::pair<int,int> pdgpr) const;
         bool   has(const Par::Tags partype, const std::pair<str,int> shortpr) const;
         double get(const Par::Tags partype, const std::pair<str,int> shortpr) const;
         /// @}

         /// @{ Getters which first check the sanity of the thing they are returning
         double safeget(const Par::Tags partype, const std::string& mass) const;
         double safeget(const Par::Tags partype, const std::string& mass, const int index) const;
         double safeget(const Par::Tags partype, const int pdg_code, const int context) const;
         double safeget(const Par::Tags partype, const std::pair<int,int> pdgpr) const;
         double safeget(const Par::Tags partype, const std::pair<str,int> shortpr) const;
         /// @}

         /// @}

         /// SLHAea object getter
         /// First constructs an SLHAea object from the SMINPUTS object, then adds the info from
         /// the LE subspectrum (if possible), followed by the HE subspectrum (if possible). Any duplicate
         /// entries are overwritten at each step, so HE takes precendence over LE, and LE takes precedence
         /// over SMINPUTS.
         SLHAstruct getSLHAea(int) const;

         /// Output spectrum contents as an SLHA file, using getSLHAea.
         void writeSLHAfile(int, const str&) const;

         /// Helper function to drop SLHA files
         void drop_SLHAs_if_requested(const safe_ptr<Options>&, const str&);

         /// PDG code translation map, for special cases where an SLHA file has been read in and the PDG codes changed.
         const std::map<int, int>& PDG_translator() const;

         /// CKM Wolfenstein (lambda, A, rhobar, etabar) --> V_qq standard parameterisation convertors
         /// @{
         static double Wolf2V_ud(double, double, double, double);
         static double Wolf2V_us(double, double, double, double);
         static std::complex<double> Wolf2V_ub(double, double, double, double);
         static std::complex<double> Wolf2V_cd(double, double, double, double);
         static std::complex<double> Wolf2V_cs(double, double, double, double);
         static double Wolf2V_cb(double, double, double, double);
         static std::complex<double> Wolf2V_td(double, double, double, double);
         static std::complex<double> Wolf2V_ts(double, double, double, double);
         static double Wolf2V_tb(double, double, double, double);
         /// @}
   };

} // end namespace Gambit


#endif
