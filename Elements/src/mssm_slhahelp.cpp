//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of routines to help users / Bits
///  translate between SLHA2 sfermions
///  and SLHA1 (or similar) sfermions
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Peter Athron
///          (peter.athron@coepp.org.au)
///  \date 2015
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///
///  *********************************************

#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/Elements/ini_functions.hpp"
#include "gambit/Utils/util_functions.hpp"

namespace Gambit
{

   namespace slhahelp
   {

      /// Known maps filled at initialisation
      /// @{
      const std::map<str, p_int_string> gauge_label_to_index_type = init_gauge_label_to_index_type();
      const std::map<str, p_int_string> mass_label_to_index_type = init_mass_label_to_index_type();
      const std::map<str, pair_string_ints> familystate_label = init_familystate_label();
      const std::map<p_int_string, std::vector<str> > type_family_to_gauge_states = init_type_family_to_gauge_states();
      const std::map<str,std::vector<str> > family_state_to_gauge_state = init_family_state_to_gauge_state();
      const std::map<str,std::vector<str> > gauge_es_to_family_states = init_gauge_es_to_family_states() ;
      const std::map<str,std::vector<str> > type_to_vec_of_mass_es = init_type_to_vec_of_mass_es();
      const std::map<str,std::vector<str> > type_to_vec_of_gauge_es = init_type_to_vec_of_gauge_es();
      /// @}

      // FIXME: these two should be made members of the spectrum object itself
      std::vector<double> get_Pole_Mixing_col(str type, int gauge_index, const SubSpectrum& mssm)
      {
         //extract info about indices for type using map
         std::vector<str> mass_es_strs = type_to_vec_of_mass_es.at(type);
         double col_length = mass_es_strs.size();
         std::vector<double> mass_state_content(col_length);
         //iterate over column in some way, e..g
         for(std::vector<int>::size_type i = 1; i <= col_length; i++)
         {
            //Mix_{row, col}. Iterate through row index with column index fixed
            mass_state_content[i - 1] = mssm.get(Par::Pole_Mixing,type, i, gauge_index);
         }
         return mass_state_content;
      }
      std::vector<double> get_Pole_Mixing_row(str type, int mass_index, const SubSpectrum& mssm)
      {
         std::vector<str> gauge_es_strs = type_to_vec_of_gauge_es.at(type);
         double row_length = gauge_es_strs.size();
         std::vector<double> gauge_state_content(row_length);
         for(std::vector<int>::size_type i = 1; i <= row_length; i++)
         {
            /// Mix_{row, col}. Iterate through column index with row index fixed
            gauge_state_content.at(i - 1) = mssm.get(Par::Pole_Mixing,type, mass_index, i);
         }
         return gauge_state_content;
      }

      /// Add a disclaimer about the absence of a MODSEL block in a generated SLHAea object
      void add_MODSEL_disclaimer(SLHAstruct& slha, const str& object)
      {
        slha.push_front("# depend on which calculator you intend this object or file to be used with.");
        slha.push_front("# Note that block MODSEL is not automatically emitted, as its contents");
        slha.push_front("# This SLHA(ea) object was created from a GAMBIT "+object+" object.");
      }

      /// Simple helper function for for adding missing SLHA1 2x2 family mixing matrices to an SLHAea object.
      void attempt_to_add_SLHA1_mixing(const str& block, SLHAstruct& slha, const str& type,
                                       const SubSpectrum& spec, double tol, str& s1, str& s2, bool pterror)
      {
        if (slha.find(block) == slha.end())
        {
          std::vector<double> matmix = slhahelp::family_state_mix_matrix(type, 3, s1, s2, spec, tol, LOCAL_INFO, pterror);
          SLHAea_add_matrix(slha, block, matmix, 2, 2);
        }
        else
        {
          std::map<str,str> family_to_3gen; // TODO: make const or something
          family_to_3gen["~u"] = "~t";
          family_to_3gen["~d"] = "~b";
          family_to_3gen["~e-"] = "~tau";
          s1 = slhahelp::mass_es_closest_to_family(family_to_3gen.at(type)+"_1", spec, tol, LOCAL_INFO, pterror);
          s2 = slhahelp::mass_es_closest_to_family(family_to_3gen.at(type)+"_2", spec, tol, LOCAL_INFO, pterror);
        }
      }

      /// returns vector representing composition of requested gauge state
      /// in terms of the slha2 mass eigenstates (~u_1 ...~u_6 etc)
      /// which is just a column in the mixing matrix
      std::vector<double> get_mass_comp_for_gauge(str gauge_es,
                                                  const SubSpectrum& mssm)
      {
         /// extract info from string via map
         p_int_string index_type = gauge_label_to_index_type.at(gauge_es);
         str type = index_type.second;
         int gauge_index  = index_type.first;

         std::vector<double> mass_state_content =
            get_Pole_Mixing_col(type, gauge_index, mssm);

         return mass_state_content;
      }

      ///routine to return mass state admixure for given gauge state
      /// in the end this is a trival routine but may help
      double get_mixing_element(str gauge_es, str mass_es, const SubSpectrum& mssm)
      {
         ///extract info from maps
         p_int_string mass_es_index_type = mass_label_to_index_type.at(mass_es);
         p_int_string gauge_es_index_type = gauge_label_to_index_type.at(gauge_es);
         int gauge_index = gauge_es_index_type.first;
         int mass_index = mass_es_index_type.first;
         /// types should match but getting both allows us to throw error
         str type = mass_es_index_type.second;
         str type_gauge = gauge_es_index_type.second;
         if(type!=type_gauge)
            {
               /// throw exception in gambit
               utils_error().raise(LOCAL_INFO, "function get_mixing_element "
               "called with types for the gauge eigenstate and mass eigenstate that don't match.");
            }
         /// will need to add mssm object to cal method in gambit
         double admix = mssm.get(Par::Pole_Mixing,type, mass_index,
                                                   gauge_index);
         return admix;
      }

      /// returns vector representing composition of requested mass eigenstate
      /// in terms of the slha2 gauge eigenstates (~u_L,~c_L,...~t_R etc)
      /// which is just a row in the mixing matrix
      /// just wraps get_Pole_Mixing_row after extracting info from string
      std::vector<double> get_gauge_comp_for_mass(str mass_es, const SubSpectrum& mssm)
      {
         /// extract info using map
         p_int_string index_type = mass_label_to_index_type.at(mass_es);
         int mass_index = index_type.first;
         str type = index_type.second;
         //fill vector with mixings
         std::vector<double> mass_state_content =
            get_Pole_Mixing_row(type, mass_index, mssm);

         return mass_state_content;
      }

      /// indentifies the state with largest gauge_es content
      /// also fills largest max_mixing and full gauge_composition
      str mass_es_from_gauge_es(str gauge_es, double & max_mixing,
                                std::vector<double> & gauge_composition,
                                const SubSpectrum& mssm)
      {
         /// passed in massstate to be set
         double temp_admix = 0.0;
         /// make sure this is zero to start
         max_mixing = 0;
         /// retrive type from the gauge_es string
         str type = (gauge_label_to_index_type.at(gauge_es)).second;
         str mass_es, temp_mass_es;
         /// iterate over vector of strings for mass states
         std::vector<str> mass_es_set = type_to_vec_of_mass_es.at(type);
         typedef std::vector<str>::iterator iter;
         for(iter it = mass_es_set.begin(); it != mass_es_set.end(); ++it){
            temp_mass_es = *it;
            temp_admix = get_mixing_element(gauge_es, temp_mass_es,
                                                    mssm);
            gauge_composition.push_back(temp_admix);
            //select largest
            if(fabs(temp_admix) > fabs(max_mixing))
               {
               max_mixing = temp_admix;
               mass_es = temp_mass_es;
            }
         } //end iteration over temp_mass_es

         return mass_es;
      }

      /// as above but doesn't fill a gauge_composition vector
      /// would have a slight efficiency saving if we didn't use wrapper and
      /// avoided skipped gauge_composition entirely but at the cost of a lot of
      /// code duplication
      str mass_es_from_gauge_es(str gauge_es, double & max_mixing,
                                const SubSpectrum& mssm)
      {
         std::vector<double> gauge_composition;
         str mass_es = mass_es_from_gauge_es(gauge_es, max_mixing,
                                             gauge_composition, mssm);
         return mass_es;

      }

      /// as above but doesn't fill max_mixing
      /// would have a slight efficiency saving if we didn't use wrapper and
      /// avoided skipped max_mixing entirely but at the cost of a lot of
      /// code duplication
      str mass_es_from_gauge_es(str gauge_es,
                                std::vector<double> & gauge_composition,
                                const SubSpectrum& mssm)
      {
         double max_mixing = 0;
         str mass_es =  mass_es_from_gauge_es(gauge_es, max_mixing,
                                              gauge_composition, mssm);

         return mass_es;
      }

      /// as above but doesn't fill max_mixing or gauge_composition
      /// would have a slight efficiency saving if we didn't use wrapper and
      /// avoided skipped max_mixing entirely but at the cost of a lot of
      /// code duplication
      str mass_es_from_gauge_es(str gauge_es,
                                const SubSpectrum& mssm)
      {
         double max_mixing = 0;
         std::vector<double> gauge_composition;
         str mass_es =  mass_es_from_gauge_es(gauge_es, max_mixing,
                                              gauge_composition, mssm);
         return mass_es;
      }

      /// as above but do test against tol internally
      str mass_es_from_gauge_es(str gauge_es, const SubSpectrum& mssm,
                                double tol, str context, bool pterror)
      {
         double max_mixing = 0;
         std::vector<double> gauge_composition;
         str mass_es = mass_es_from_gauge_es(gauge_es, max_mixing,
                                             gauge_composition, mssm);
         if((max_mixing*max_mixing) <= 1-tol)
         {
           const str errmsg = "Mass_es_from_gauge_es requested when mixing "
                              "away from closest gauge_es is greater than tol.";
           str full_context = LOCAL_INFO + " called from " + context;
           if (pterror)
           {
             invalid_point().raise(errmsg+"  Raised at: "+full_context);
           }
           else
           {
             utils_error().raise(full_context, errmsg);
           }
         }
         return mass_es;
      }

      /// identifies gauge_es with largest mass_es content
      /// also fills largest max_mixing and full mass_composition
      str gauge_es_from_mass_es(str mass_es, double & max_mixing,
                                std::vector<double> & mass_composition,
                                const SubSpectrum& mssm)
      {
         /// passed in massstate to be set
         double temp_admix = 0.0;
         /// start with zero
         max_mixing = 0;
         /// retrive type from the gauge_es string
         str type = (mass_label_to_index_type.at(mass_es)).second;
         str gauge_es, temp_gauge_es;
         /// iterate over vector of strings for mass states
         std::vector<str> gauge_es_vec = type_to_vec_of_gauge_es.at(type);
         typedef std::vector<str>::iterator iter;
         for(iter it = gauge_es_vec.begin(); it != gauge_es_vec.end(); ++it)
            {
            temp_gauge_es = *it;
            temp_admix = get_mixing_element(temp_gauge_es, mass_es,  mssm);
            mass_composition.push_back(temp_admix);
            //select largest
            if(fabs(temp_admix) > fabs(max_mixing))
               {
               max_mixing = temp_admix;
               gauge_es = temp_gauge_es;
               }
         } //end iteration over temp_mass_es

         //return string for closest gauge_es
         return gauge_es;
      }

      /// as above but doesn't fill a gauge_composition vector
      /// would have a slight efficiency saving if we didn't use wrapper and
      /// avoided skipped gauge_composition entirely but at the cost of a lot of
      /// code duplication
      str gauge_es_from_mass_es(str mass_es, double & max_mixing,
                                const SubSpectrum& mssm)
      {
         std::vector<double> mass_composition;
         str gauge_es = gauge_es_from_mass_es(mass_es, max_mixing,
                                              mass_composition, mssm);
         return gauge_es;

      }

      /// as above but doesn't fill max_mixing
      /// would have a slight efficiency saving if we didn't use wrapper and
      /// avoided skipped max_mixing entirely but at the cost of a lot of
      /// code duplication
      str gauge_es_from_mass_es(str mass_es,
                                std::vector<double> & mass_composition,
                                const SubSpectrum& mssm)
      {
         double max_mixing;
         str gauge_es =  gauge_es_from_mass_es(mass_es, max_mixing,
                                           mass_composition, mssm);

         return gauge_es;
      }

      /// as above but doesn't fill max_mixing or gauge_composition
      /// would have a slight efficiency saving if we didn't use wrapper and
      /// avoided skipped max_mixing entirely but at the cost of a lot of
      /// code duplication
      str gauge_es_from_mass_es(str mass_es,
                                const SubSpectrum& mssm)
      {
         double max_mixing;
         std::vector<double> mass_composition;
         str gauge_es =  gauge_es_from_mass_es(mass_es, max_mixing,
                                               mass_composition, mssm);

         return gauge_es;
      }

      /// as above but do test against tol internally
      str gauge_es_from_mass_es(str mass_es, const SubSpectrum& mssm,
                                double tol, str context, bool pterror)
      {
         double max_mixing;
         std::vector<double> mass_composition;
         str gauge_es = gauge_es_from_mass_es(mass_es, max_mixing,
                                              mass_composition, mssm);
         if((max_mixing*max_mixing) <= 1-tol)
         {
           const str errmsg = "Gauge_es from mass_es requested when mxing away "
                              "from closest mass_es is greater than tol";
           str full_context = LOCAL_INFO + " called from " + context;
           if (pterror)
           {
             invalid_point().raise(errmsg+"  Raised at: "+full_context);
           }
           else
           {
             utils_error().raise(full_context, errmsg);
           }
         }
         return gauge_es;
      }

      /// identify the two mass eigenstate corresponding to the approximate
      /// family states, e.g. stops ("~u",3), smuons ("~mu", 2) etc
      /// Note: when there is family mixing there's no good definition ~t_1,
      /// ~t_2 etc if defined as the states you get from diagonalising a 2by2
      /// mass (sub)matrix then extensive manipulations would be required
      /// So here we identify the mass eigenstates closest to the family ones
      /// which is a better defined question when there is family mixing prsesent
      /// and more useful here anyway
      /// returns a pair of strings labling the lighter one first
      sspair identify_mass_ess_for_family(str type,
                                          int family,
                                          const SubSpectrum& mssm)
      {
         /// need to turn type and family into a string
         /// need to simplify the number of translations we do.
         p_int_string gen_type(family,type);
         std::vector<str> gauge_states;
         try { gauge_states = type_family_to_gauge_states.at(gen_type); }
         catch (std::out_of_range&) { utils_error().raise(LOCAL_INFO, "Sfermion type or generation index not recognised; use type=~u,~d,~e-, gen=1,2,3."); }
         str gauge_esL=gauge_states[0];
         str gauge_esR=gauge_states[1];

         /// finds the mass_es with the largets mixing to
         /// passed gauge_es
         str mass_esL = mass_es_from_gauge_es(gauge_esL, mssm);
         str mass_esR = mass_es_from_gauge_es(gauge_esR, mssm);

         sspair answer;
         int mass_index_L = (mass_label_to_index_type.at(mass_esL)).first;
         int mass_index_R = (mass_label_to_index_type.at(mass_esR)).first;
         // order pair by mass
         if(mass_index_L < mass_index_R)
            answer = std::make_pair(mass_esL,mass_esR);
         else answer = std::make_pair(mass_esR,mass_esL);

         return answer;
      }

      /// identify the mass eigenstate corresponding to family state
      /// takes string and returns only requested state
      /// I suspect this is the more useful one
      str mass_es_closest_to_family(str familystate,
                                    const SubSpectrum& mssm)
      {
         std::vector<str> family_gauge_states;
         try { family_gauge_states = family_state_to_gauge_state.at(familystate); }
         catch (std::out_of_range&) { utils_error().raise(LOCAL_INFO, "Unrecognised family state. ('"+familystate+"' was requested)"); }
         str gauge_esL = family_gauge_states[0];
         str gauge_esR = family_gauge_states[1];

         // finds the mass_es with the largets mixing to
         // passed gauge_es
         str mass_esL = mass_es_from_gauge_es(gauge_esL, mssm);
         str mass_esR = mass_es_from_gauge_es(gauge_esR, mssm);

         // extract mass order (1 or 2) from string via map
         pair_string_ints type_family_massorder =
            familystate_label.at(familystate);
         pair_ints family_massorder = type_family_massorder.second;
         int mass_order = family_massorder.second;
         // if massorder is 1 choose select from masstateL and mass_esR the one
         // with the lowest index else take highest
         int massorderL = (mass_label_to_index_type.at(mass_esL)).first;
         int massorderR = (mass_label_to_index_type.at(mass_esR)).first;
         str answer;
         if( (mass_order == 1 && massorderL < massorderR) ||
             (mass_order == 2 && massorderL > massorderR) ) answer = mass_esL;
         else answer = mass_esR;

         return answer;
      }

      /// returns vector with composition of closest the mass eigenstate
      /// to give family state in terms of gauge eigenstates and stores
      /// mass eigenstate in mass_es
      std::vector<double> get_gauge_comp_for_family_state(str familystate,
                                                          str & mass_es,
                                                          const SubSpectrum& mssm)
      {
         //get mass_es using one of our routines
         mass_es = mass_es_closest_to_family(familystate, mssm);
         /// extract info from strings via maps
         int mass_index = (mass_label_to_index_type.at(mass_es)).first;
         pair_string_ints state_info = familystate_label.at(familystate);
         str type = state_info.first;
         std::vector<double> gauge_es_content =
            get_Pole_Mixing_row(type, mass_index,mssm);

         return gauge_es_content;

      }

      /// identifies the mass_es that is closest match to specified family state
      /// and fills mixture of the two gauge states with same family into
      /// std::vector gauge_composition
      /// also fills remaining off-family mixings into a second vector
      str mass_es_closest_to_family(str familystate,
                                    std::vector<double> & gauge_composition,
                                    std::vector<double> & off_family_mixing,
                                    const SubSpectrum& mssm)
      {
         //get mass_es using one of our routines
         str mass_es = mass_es_closest_to_family(familystate, mssm);
         /// extract info from strings via maps
         std::vector<str> gauge_states;
         try { gauge_states = family_state_to_gauge_state.at(familystate); }
         catch (std::out_of_range&) { utils_error().raise(LOCAL_INFO, "Unrecognised family state. ('"+familystate+"' was requested)"); }
         str gauge_state_L = gauge_states[0];
         str gauge_state_R = gauge_states[1];

         p_int_string gauge_Lindex_type =
            gauge_label_to_index_type.at(gauge_state_L);
         unsigned int gauge_L_index = gauge_Lindex_type.first;
         str type = gauge_Lindex_type.second;
         unsigned int gauge_R_index
            = (gauge_label_to_index_type.at(gauge_state_R)).first;
         int mass_index = (mass_label_to_index_type.at(mass_es)).first;
         std::vector<str> gauge_es_strs = type_to_vec_of_gauge_es.at(type);
         double row_length = gauge_es_strs.size();
         for(std::vector<int>::size_type i = 1; i <= row_length; i++)
            {
               double temp = mssm.get(Par::Pole_Mixing,type, mass_index, i);
               if(i == gauge_L_index || i == gauge_R_index)
                  gauge_composition.push_back(temp);
               else off_family_mixing.push_back(temp);
            }

         return mass_es;

      }

      /// identifies the mass_es that is closest match to specified family state
      /// and fills mixture of the two gauge states with same family into
      /// std::vector gauge_composition
      str mass_es_closest_to_family(str familystate,
                                    std::vector<double> & gauge_composition,
                                    const SubSpectrum& mssm)
      {
         std::vector<double> off_family_mixing;
         str mass_es = mass_es_closest_to_family(familystate, gauge_composition,
                                                 off_family_mixing, mssm);
         return mass_es;

      }

      /// identifies the mass_es that is closest match to specified family state
      /// and fills sqr_sum_mix with the square sum of each of the two mixings
      /// into gauge_es of that family
      str mass_es_closest_to_family(str familystate,
                                    double & sqr_sum_mix,
                                    const SubSpectrum& mssm)
      {
         std::vector<double> off_family_mixing;
         std::vector<double>  gauge_composition;
         str mass_es = mass_es_closest_to_family(familystate, gauge_composition,
                                                 off_family_mixing, mssm);
         sqr_sum_mix = gauge_composition[0] * gauge_composition[0];
         sqr_sum_mix += gauge_composition[1] * gauge_composition[1];
         return mass_es;

      }

      /// identifies the mass_es that is closest match to specified family
      /// does tol-test internally to check correctness of assumptions
      str mass_es_closest_to_family(str familystate, const SubSpectrum& mssm,
                                    double tol, str context, bool pterror)
      {
        std::vector<double> off_family_mixing;
        std::vector<double>  gauge_composition;
        str mass_es = mass_es_closest_to_family(familystate, gauge_composition,
                                                off_family_mixing, mssm);
        double sqr_sum_mix = gauge_composition[0] * gauge_composition[0];
        sqr_sum_mix += gauge_composition[1] * gauge_composition[1];
        if(sqr_sum_mix <= 1-tol)
        {
          const str errmsg = "Mass_es_closest_to_family requested when family "
                              "mixing away from closest mass_es is greater than tol";
          str full_context = LOCAL_INFO + " called from " + context;
          if (pterror)
          {
            invalid_point().raise(errmsg+"  Raised at: "+full_context);
          }
          else
          {
            utils_error().raise(full_context, errmsg);
          }
        }

        return mass_es;

      }

      /// Get the family mixing matrix and corresponding mass eigenstates, then check for interfamily mixing.
      std::vector<double> family_state_mix_matrix(str type /*"~u", "~d" or "~e-"*/, int generation,
                                                  str & mass_es1, str & mass_es2, const SubSpectrum& mssm,
                                                  double tol, str context, bool pterror)
      {
        std::vector<double> m = family_state_mix_matrix(type, generation, mass_es1, mass_es2, mssm);
        if (m[0]*m[0] + m[1]*m[1] < 1-tol || m[2]*m[2] + m[3]*m[3] < 1-tol)
        {
          const str errmsg = "Too much interfamily mixing to safely determine "
                             "intrafamily mixing matrix.";
          str full_context = LOCAL_INFO + " called from " + context;
          if (pterror)
          {
            invalid_point().raise(errmsg+"  Raised at: "+full_context);
          }
          else
          {
            utils_error().raise(full_context, errmsg);
          }
        }
        return m;
      }

      /// identifies the two mass_es which best matches specified family state
      /// storing them in strings and then returns
      /// the 2by2 mixing matrix for that family state in the form
      /// (Mix_{11}, Mix_{12}, Mix_{21}, Mix_{22})
      /// It also  stores the mixing elements for the gauge states that don't
      /// belong to the correct family for this state in a std::vector
      /// The latter should have entries which are zero in absense of
      /// family mixing
      std::vector<double> family_state_mix_matrix(str type,
                                                  int family,
                                                  str & mass_es1,
                                                  str & mass_es2,
                                                  const SubSpectrum& mssm)
      {
         /// get mass_es using one of our routines
         sspair mass_ess = identify_mass_ess_for_family(type, family, mssm);
         mass_es1 = mass_ess.first;
         mass_es2 = mass_ess.second;

         /// need to turn type and family into a string
         /// should simplify the number of translations we do!
         p_int_string gen_type(family,type);
         std::vector<str> gauge_states;
         try { gauge_states = type_family_to_gauge_states.at(gen_type); }
         catch (std::out_of_range&) { utils_error().raise(LOCAL_INFO, "Sfermion type or generation index not recognised; use type=~u,~d,~e-, gen=1,2,3."); }
         str gauge_es_L=gauge_states[0];
         str gauge_es_R=gauge_states[1];
         /// get index of right family states (ie gauge states with
         ///same family as requested family state
         p_int_string gauge_Lindex_type =
            gauge_label_to_index_type.at(gauge_es_L);
         unsigned int gauge_L_index = gauge_Lindex_type.first;
         unsigned int gauge_R_index
            = (gauge_label_to_index_type.at(gauge_es_R)).first;

         str type_L = gauge_Lindex_type.second;
         int mass_index1 = (mass_label_to_index_type.at(mass_es1)).first;
         int mass_index2 = (mass_label_to_index_type.at(mass_es2)).first;
         std::vector<double> mix_row_1;
         std::vector<double> mix_row_2;
         std::vector<str> gauge_es_strs = type_to_vec_of_gauge_es.at(type);
         double row_length = gauge_es_strs.size();
         for(std::vector<int>::size_type i = 1; i <= row_length; i++)
            {
               double temp1 = mssm.get(Par::Pole_Mixing,type, mass_index1, i);
               double temp2 = mssm.get(Par::Pole_Mixing,type, mass_index2, i);
               if(i == gauge_L_index || i == gauge_R_index)
                  {
                     mix_row_1.push_back(temp1);
                     mix_row_2.push_back(temp2);
                  }
            }

         ///Put row 1 and row 2 into the same vector to return
         mix_row_1.insert(mix_row_1.end(), mix_row_2.begin(), mix_row_2.end());

         return mix_row_1;
      }

      /// returns admix of gauge eigenstate in the mass eigenstate
      /// closest to the given family state and stores
      /// mass eigenstate in mass_es
      double get_gauge_admix_for_family_state(str familystate,
                                              str gauge_es,
                                              str & mass_es,
                                              const SubSpectrum& mssm)
      {
         pair_string_ints type_family_massorder;
         try { type_family_massorder = familystate_label.at(familystate); }
         catch (std::out_of_range&) { utils_error().raise(LOCAL_INFO, "Unrecognised family state."); }
         str family_type = type_family_massorder.first;
         p_int_string gauge_es_index_type = gauge_label_to_index_type.at(gauge_es);
         int gauge_index = gauge_es_index_type.first;
         /// types should match but getting both allows us to throw error
         str type_gauge = gauge_es_index_type.second;
         if(family_type!=type_gauge)
            { /// throw error in gambit
               utils_error().raise(LOCAL_INFO, "function get_gauge_admix_for_family_state "
                "called with types for the family state and mass eigenstate that don't match.");
            }
         ///get mass_es using one of our routines
         mass_es = mass_es_closest_to_family(familystate, mssm);
         /// extract info from strings via maps
         int mass_index = (mass_label_to_index_type.at(mass_es)).first;
         double admix = mssm.get(Par::Pole_Mixing,type_gauge, mass_index,
                                                   gauge_index);
         return admix;
      }

      /// returns family state that best matches the given mass_es
      /// fills a double with the sum of the square mixings to gauge_es
      /// of the matching family
      /// and fills the mixing of the matching gauge_es into mass eigenstates
      str family_state_closest_to_mass_es(str mass_es, double & sum_sq_mix,
                                          std::vector<double> & mass_comp,
                                          const SubSpectrum& mssm)
      {
         /// get gauge_es with largest mixing to this mass_es
         str gauge_es = gauge_es_from_mass_es(mass_es, mass_comp, mssm);
         /// get family states for the same generation as this gauge_es
         std::vector<str> family_states = gauge_es_to_family_states.at(gauge_es);
         str family_state1 = family_states[0];
         str family_state2 = family_states[1];
         std::vector<str> gauge_states = family_state_to_gauge_state.at(family_state1);
         str gauge_es_L = gauge_states[0];
         str gauge_es_R = gauge_states[1];
         str mass_es_other;
         if(gauge_es == gauge_es_L)
            mass_es_other = mass_es_from_gauge_es(gauge_es_R, mssm);
         else mass_es_other = mass_es_from_gauge_es(gauge_es_L, mssm);
         /// extractindex of mass-es and mass_ess_other from strings
         int mass_index = (mass_label_to_index_type.at(mass_es)).first;
         int mass_index_other = (mass_label_to_index_type.at(mass_es_other)).first;
         str fam_state;
         /// choose mass ordering for family state which matches
         /// mass ordering of mass_es
         if(mass_index < mass_index_other) fam_state = family_state1;
         else fam_state = family_state2;

         //get gauge_indices to sum correct mixing elements
         int gauge_index_L = (gauge_label_to_index_type.at(gauge_es_L)).first;
         int gauge_index_R = (gauge_label_to_index_type.at(gauge_es_R)).first;
         /// subrtact 1 fgrom indices to deal with different indexing
         sum_sq_mix = mass_comp.at(gauge_index_L-1) * mass_comp.at(gauge_index_L-1);
         sum_sq_mix += mass_comp.at(gauge_index_R-1) * mass_comp.at(gauge_index_R-1);

         return fam_state;
      }

      /// wrapper for overloaded version
      /// returns family state that best matches the given mass_es
      /// fills a double with the sum of the square mixings to gauge_es
      /// of the matching family
      str family_state_closest_to_mass_es(str mass_es, double & sum_sq_mix,
                                           const SubSpectrum& mssm)
      {
         std::vector<double> mass_comp;
         str fs = family_state_closest_to_mass_es(mass_es, sum_sq_mix,
                                                  mass_comp, mssm);
         return fs;
      }

      /// wrapper for overloaded version
      /// returns family state that best matches the given mass_es
      /// and fills the mixing of the matching mass_es into gauge eigenstates
      str family_state_closest_to_mass_es(str mass_es,
                                           std::vector<double> & mass_comp,
                                           const SubSpectrum& mssm)
      {
         double sum_sq_mix;
         str fs = family_state_closest_to_mass_es(mass_es, sum_sq_mix, mass_comp,
                                                  mssm);
         return fs;
      }

      /// wrapper for overloaded version
      /// returns family state that best matches the given mass_es
      /// and fills the mixing of the matching mass_es into gauge eigenstates
      str family_state_closest_to_mass_es(str mass_es, const SubSpectrum& mssm,
                                          double tol, str context, bool pterror)
      {
         double sum_sq_mix;
         std::vector<double> mass_comp;
         str fs = family_state_closest_to_mass_es(mass_es, sum_sq_mix,
                                                  mass_comp, mssm);
         if(sum_sq_mix <= 1-tol)
         {
           const str errmsg = "Family_state_closest_to_mass_es called when family "
                              "mixing away from closest mass_es is greater than tol.";
           str full_context = LOCAL_INFO + " called from " + context;
           if (pterror)
           {
             invalid_point().raise(errmsg+"  Raised at: "+full_context);
           }
           else
           {
             utils_error().raise(full_context, errmsg);
           }
         }
         return fs;
      }

      /// Add an entire MSSM spectrum to an SLHAea object
      // Here we assume that all SM input info comes from the SMINPUT object,
      // and all low-E stuff (quark pole masses and the like) come from the LE subspectrum.
      // In other words all those things should be added to the SLHAea object via
      // different functions to this one. Here we add only MSSM information
      // NOTE: check the below statement:
       // Note that the SMINPUT object's dump-to-SLHAea function does not know how to discriminate
       // between SLHA1 and SLHA2, but that doesn't matter, as the SM parameters defined in SLHA2
       // just constitute additional blocks/block entries, not replacements for SLHA1 blocks.  In the
       // MSSM sector, this is not true, and we take care to write version-specific blocks here.
      //
      // slha_version - should be 1 or 2. Specifies whether to output closest-matching SLHA1 format
      // entries, or to maintain SLHA2 as is used internally.
      void add_MSSM_spectrum_to_SLHAea(const SubSpectrum& mssmspec, SLHAstruct& slha, int slha_version)
      {
         std::ostringstream comment;

         // Make sure to overwrite all entries if they exist already (from say a "hurriedly" copied SM subspectrum + unknown extra MSSM junk)

         //SPINFO block should be added separately.
         // MINPAR block; some programs need tanbeta(mZ), so we should output it here if possible
         SLHAea_check_block(slha, "MINPAR");
         if(mssmspec.has(Par::dimensionless,"tanbeta(mZ)"))
         {
            SLHAea_add_from_subspec(slha,LOCAL_INFO,mssmspec,Par::dimensionless,"tanbeta(mZ)","MINPAR",3,"# tanbeta(mZ)^DRbar");
         }
         int sgnmu = sgn(mssmspec.get(Par::mass1,"Mu")); // Mu isn't at the input scale anymore, but sign(mu) doesn't change with running.
         SLHAea_add(slha,"MINPAR",4,sgnmu,"# sign(mu)", true);

         // HMIX block
         SLHAea_delete_block(slha, "HMIX");
         SLHAea_add_block   (slha, "HMIX", mssmspec.GetScale());
         SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec,Par::mass1,"Mu","HMIX",1,"mu DRbar");
         SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec,Par::dimensionless,"tanbeta","HMIX",2,"tan(beta) = vu/vd DRbar");
         if (not mssmspec.has(Par::mass1,"vu")) utils_error().raise(LOCAL_INFO, "MSSM subspectrum does not contain vu!");
         if (not mssmspec.has(Par::mass1,"vd")) utils_error().raise(LOCAL_INFO, "MSSM subspectrum does not contain vd!");
         double vu = mssmspec.get(Par::mass1,"vu");
         double vd = mssmspec.get(Par::mass1,"vd");
         SLHAea_add(slha,"HMIX",3,sqrt(vu*vu + vd*vd),"v = sqrt(vd^2 + vu^2) DRbar", true);
         SLHAea_add_from_subspec(slha,LOCAL_INFO,mssmspec,Par::mass2,"mA2","HMIX",4,"m^2_A (tree)");
         SLHAea_add_from_subspec(slha,LOCAL_INFO,mssmspec,Par::mass2,"BMu","HMIX",101,"Bmu DRbar");
         SLHAea_add(slha,"HMIX",102,vd,"vd DRbar", true);
         SLHAea_add(slha,"HMIX",103,vu,"vu DRbar", true);
         // GAUGE block
         SLHAea_delete_block(slha, "GAUGE");
         SLHAea_add_block   (slha, "GAUGE", mssmspec.GetScale());
         // Scale gY is in SU(5)/GUT normalisation internally; convert it to SM normalisation for SLHA output by multiplying by sqrt(3/5).
         SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec,Par::dimensionless,"g1","GAUGE",1,"g'  = g1 = gY DRbar", true, sqrt(3./5.));
         SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec,Par::dimensionless,"g2","GAUGE",2,"g   = g2      DRbar");
         SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec,Par::dimensionless,"g3","GAUGE",3,"g_s = g3      DRbar");

         const int pdg_codes[33] = {24,25,35,37,36,1000021,1000024,1000037,1000022,1000023,1000025,1000035,1000006,2000006,1000005,2000005,1000015,2000015,1000012,1000014,1000016,1000001,1000003,
                                    2000001,2000003,1000011,1000013,2000011,2000013,1000002,1000004,2000002,2000004,};

         // Here we add the SLHA1-specific stuff, for backwards compatibility with backwards backends.
         if (slha_version == 1)
         {
           const str slha1_sfermions[21] = {"~t_1", "~t_2", "~b_1", "~b_2", "~tau_1", "~tau_2",
                                            "~nu_e_L", "~nu_mu_L", "~nu_tau_L",
                                             "~d_L", "~s_L", "~d_R", "~s_R", "~e_L", "~mu_L",
                                             "~e_R", "~mu_R", "~u_L", "~c_L", "~u_R", "~c_R"};
           str slha2_sfermions[21];

           // STOPMIX, SBOTMIX and STAUMIX blocks
           slhahelp::attempt_to_add_SLHA1_mixing("STOPMIX", slha, "~u", mssmspec, 1.0, slha2_sfermions[0], slha2_sfermions[1], true);
           slhahelp::attempt_to_add_SLHA1_mixing("SBOTMIX", slha, "~d", mssmspec, 1.0, slha2_sfermions[2], slha2_sfermions[3], true);
           slhahelp::attempt_to_add_SLHA1_mixing("STAUMIX", slha, "~e-", mssmspec, 1.0, slha2_sfermions[4], slha2_sfermions[5], true);

           // MASS block.  Do everything except sfermions the same way as SLHA2.
           for(int i=0;i<12;i++)
           {
             str comment(Models::ParticleDB().long_name(pdg_codes[i], 0));
             SLHAea_add_from_subspec(slha, LOCAL_INFO, mssmspec, Par::Pole_Mass, std::pair<int, int>(pdg_codes[i],0), "MASS", comment);
           }
           for(int i=0;i<21;i++)
           {
             if (i > 5)
             {
               double max_mixing; // Don't actually care about this; we're going to SLHA1 whether it is a good approximation or not.
               slha2_sfermions[i] = slhahelp::mass_es_from_gauge_es(slha1_sfermions[i], max_mixing, mssmspec);
             }
             SLHAea_add(slha, "MASS", pdg_codes[i+12], mssmspec.get(Par::Pole_Mass, slha2_sfermions[i]), slha1_sfermions[i], true);
           }
           if (mssmspec.has(Par::Pole_Mass, "~G")) SLHAea_add_from_subspec(slha, LOCAL_INFO, mssmspec, Par::Pole_Mass, std::pair<int, int>(1000039,0), "MASS", "~G");
         }
         else if (slha_version == 2)
         {
           // MASS block
           for(int i=0;i<33;i++)
           {
             str comment(Models::ParticleDB().long_name(pdg_codes[i], 0));
             SLHAea_add_from_subspec(slha, LOCAL_INFO, mssmspec, Par::Pole_Mass, std::pair<int, int>(pdg_codes[i],0), "MASS", comment);
           }
           if (mssmspec.has(Par::Pole_Mass, "~G")) SLHAea_add_from_subspec(slha, LOCAL_INFO, mssmspec, Par::Pole_Mass, std::pair<int, int>(1000039,0), "MASS", "~G");

           // USQMIX, DSQMIX, SELMIX
           sspair S[3] = {sspair("USQMIX","~u"), sspair("DSQMIX","~d"), sspair("SELMIX","~e-")};
           for (int k=0;k<3;k++)
           {
             SLHAea_delete_block(slha, S[k].first);
             SLHAea_add_block   (slha, S[k].first, mssmspec.GetScale());
             for(int i=1;i<7;i++) for(int j=1;j<7;j++)
             {
               comment.str(""); comment << S[k].second << "-type sfermion mixing (" << i << "," << j << ")";
               SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec, Par::Pole_Mixing, S[k].second, i, j, S[k].first, i, j, comment.str());
             }
           }

           // SNUMIX block
           sspair V("SNUMIX","~nu");
           SLHAea_delete_block(slha, V.first);
           SLHAea_add_block   (slha, V.first, mssmspec.GetScale());
           for(int i=1;i<4;i++) for(int j=1;j<4;j++)
           {
             comment.str(""); comment << V.second << " mixing matrix (" << i << "," << j << ")";
             SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec, Par::Pole_Mixing, V.second, i, j, V.first, i, j, comment.str());
           }

         }
         else
         {
           utils_error().raise(LOCAL_INFO, "Unrecognised version of SLHA standard; only SLHA1 and SLHA2 are permitted.");
         }

         // MSOFT block (SLHA1 and SLHA2) plus MSL2, MSE2, MSQ2, MSU2 and MSD2 blocks (SLHA2 only)
         if(not SLHAea_block_exists(slha,"MSOFT"))
         {
           SLHAea_add_block(slha, "MSOFT", mssmspec.GetScale());
         }
         SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec,Par::mass1,"M1","MSOFT",1,"bino mass parameter M1");
         SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec,Par::mass1,"M2","MSOFT",2,"wino mass parameter M2");
         SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec,Par::mass1,"M3","MSOFT",3,"gluino mass parameter M3");
         SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec,Par::mass2,"mHd2","MSOFT",21,"d-type Higgs mass parameter mHd2");
         SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec,Par::mass2,"mHu2","MSOFT",22,"u-type Higgs mass parameter mHu2");
         sspair M[5] = {sspair("MSL2","ml2"), sspair("MSE2","me2"), sspair("MSQ2","mq2"), sspair("MSU2","mu2"), sspair("MSD2","md2")};
         for (int k=0;k<5;k++)
         {
           SLHAea_delete_block(slha, M[k].first);
           if (slha_version == 2) SLHAea_add_block(slha, M[k].first, mssmspec.GetScale());
           for(int i=1;i<4;i++) for(int j=1;j<4;j++)
           {
             comment.str(""); comment << M[k].second << "(" << i << "," << j << ")";
             if (slha_version == 2) SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec, Par::mass2, M[k].second, i, j, M[k].first, i, j, comment.str());
             if (i== j)
             {
               double entry = mssmspec.get(Par::mass2, M[k].second, i, j);
               SLHAea_add(slha,"MSOFT",30+3*k+i+(k>1?4:0),sgn(entry)*sqrt(std::abs(entry)),"sqrt("+comment.str()+")", true);
             }
           }
         }

         // Yukawa and trilinear blocks.  YU, YD and YE, plus [YU, YD and YE; SLHA1 only], or [TU, TD and TE; SLHA2 only].
         sspair A[3] = {sspair("AU","Au"), sspair("AD","Ad"), sspair("AE","Ae")};
         sspair Y[3] = {sspair("YU","Yu"), sspair("YD","Yd"), sspair("YE","Ye")};
         sspair T[3] = {sspair("TU","TYu"), sspair("TD","TYd"), sspair("TE","TYe")};
         for (int k=0;k<3;k++)
         {
           // Erase these blocks if they already exist; we need them in the right format
           SLHAea_delete_block(slha, Y[k].first);
           SLHAea_delete_block(slha, A[k].first);
           SLHAea_delete_block(slha, T[k].first);
           // Now add them back
           SLHAea_add_block(slha, Y[k].first, mssmspec.GetScale());
           if (slha_version == 1) SLHAea_add_block(slha, A[k].first, mssmspec.GetScale());
           if (slha_version == 2) SLHAea_add_block(slha, T[k].first, mssmspec.GetScale());
           for(int i=1;i<4;i++)
           {
             // SLHA2 says to output only diagonal of Yukawa matrices, since we should be in a basis in which they are diagonal.
             // SLHA1 says to give only the 3,3 element, but we'll give the whole diagonal anyway, codes will ignore them if not
             // needed.
             comment.str(""); comment << Y[k].second << "(" << i << "," << i << ")";
             SLHAea_add_from_subspec(slha,LOCAL_INFO,mssmspec,Par::dimensionless,Y[k].second, i, i, Y[k].first, i, i, comment.str());

             if (slha_version == 1)
             {
               comment.str(""); comment << A[k].second << "(" << i << "," << i << ")";
               double invTii = 1.0/mssmspec.get(Par::dimensionless,Y[k].second,i,i);
               SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec, Par::mass1, T[k].second, i, i, A[k].first, i, i, comment.str(), true, invTii); // last argument is a rescaling factor
             }
             else if (slha_version == 2)
             {
                for(int j=1;j<4;j++)
                {
                   comment.str(""); comment << T[k].second << "(" << i << "," << j << ")";
                   SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec, Par::mass1, T[k].second, i, j, T[k].first, i, j, comment.str());
                }
             }
             else
             {
                std::ostringstream msg;
                msg << "Tried to ouput SLHA data, but SLHA version requested was invalid (should be 1 or 2, but received "<<slha_version<<")";
                utils_error().raise(LOCAL_INFO,msg.str());
             }
           }
         }

         // ALPHA block
         // if this exists already, delete it entirely
         auto it = slha.find("ALPHA");
         if(it!=slha.end()) slha.erase(it); // TODO: format of this call is confusing, perhaps write a wrapper for it.
         // ...and now add it back
         SLHAea_add_block(slha, "ALPHA", mssmspec.GetScale());
         slha["ALPHA"][""] << asin(mssmspec.get(Par::Pole_Mixing, "h0", 2, 2)) << "# sin^-1(SCALARMIX(2,2))";

         // UMIX and VMIX blocks, plus some FlexibleSUSY-only extensions: PSEUDOSCALARMIX, SCALARMIX and CHARGEMIX.
         sspair U[5] = {sspair("UMIX","~chi-"), sspair("VMIX","~chi+"), sspair("PSEUDOSCALARMIX","A0"), sspair("SCALARMIX","h0"), sspair("CHARGEMIX","H+")};
         for (int k=0;k<5;k++)
         {
           SLHAea_delete_block(slha, U[k].first);
           SLHAea_add_block(slha, U[k].first, mssmspec.GetScale());
           for(int i=1;i<3;i++) for(int j=1;j<3;j++)
           {
             comment.str(""); comment << U[k].second << " mixing matrix (" << i << "," << j << ")";
             SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec, Par::Pole_Mixing, U[k].second, i, j, U[k].first, i, j, comment.str());
           }
         }

         // NMIX block
         sspair N("NMIX","~chi0");
         SLHAea_delete_block(slha, N.first);
         SLHAea_add_block(slha, N.first, mssmspec.GetScale());
         for(int i=1;i<5;i++) for(int j=1;j<5;j++)
         {
           comment.str(""); comment << N.second << " mixing matrix (" << i << "," << j << ")";
           SLHAea_add_from_subspec(slha, LOCAL_INFO,mssmspec, Par::Pole_Mixing, N.second, i, j, N.first, i, j, comment.str());
         }
       }

   }  // namespace slhahelp


  // Definitions of methods for struct mass_es_pseudonyms

  /// Refill strings in struct
  void mass_es_pseudonyms::refill(const SubSpectrum& mssm, double tol, bool pt_error, bool debug)
  {
    filled = false;
    fill(mssm, tol, pt_error, debug);
  }

  /// Fill strings in struct
  void mass_es_pseudonyms::fill(const SubSpectrum& mssm, double tol, bool pt_error, bool debug)
  {
    if(filled == true) return;  // Don't refill unnecessarily

    fill_mass_es_psn_gauge (isdl, isdlbar, "~d_L", mssm, tol, pt_error, debug);
    fill_mass_es_psn_gauge (isul, isulbar, "~u_L", mssm, tol, pt_error, debug);
    fill_mass_es_psn_gauge (issl, isslbar, "~s_L", mssm, tol, pt_error, debug);
    fill_mass_es_psn_gauge (iscl, isclbar, "~c_L", mssm, tol, pt_error, debug);
    fill_mass_es_psn_family(isb1, isb1bar, "~b_1", mssm, tol, pt_error, debug);
    fill_mass_es_psn_family(ist1, ist1bar, "~t_1", mssm, tol, pt_error, debug);

    fill_mass_es_psn_gauge (isell,  isellbar,  "~e_L",   mssm, tol, pt_error, debug);
    fill_mass_es_psn_gauge (ismul,  ismulbar,  "~mu_L",  mssm, tol, pt_error, debug);
    fill_mass_es_psn_family(istau1, istau1bar, "~tau_1", mssm, tol, pt_error, debug);

    fill_mass_es_psn_gauge(isnel,   isnelbar,   "~nu_e_L",   mssm, tol, pt_error, debug);
    fill_mass_es_psn_gauge(isnmul,  isnmulbar,  "~nu_mu_L",  mssm, tol, pt_error, debug);
    fill_mass_es_psn_gauge(isntaul, isntaulbar, "~nu_tau_L", mssm, tol, pt_error, debug);

    fill_mass_es_psn_gauge (isdr, isdrbar, "~d_R", mssm, tol, pt_error, debug);
    fill_mass_es_psn_gauge (isur, isurbar, "~u_R", mssm, tol, pt_error, debug);
    fill_mass_es_psn_gauge (issr, issrbar, "~s_R", mssm, tol, pt_error, debug);
    fill_mass_es_psn_gauge (iscr, iscrbar, "~c_R", mssm, tol, pt_error, debug);
    fill_mass_es_psn_family(isb2, isb2bar, "~b_2", mssm, tol, pt_error, debug);
    fill_mass_es_psn_family(ist2, ist2bar, "~t_2", mssm, tol, pt_error, debug);

    fill_mass_es_psn_gauge (iselr, iselrbar,   "~e_R",   mssm, tol, pt_error, debug);
    fill_mass_es_psn_gauge (ismur, ismurbar,   "~mu_R",  mssm, tol, pt_error, debug);
    fill_mass_es_psn_family(istau2, istau2bar, "~tau_2", mssm, tol, pt_error, debug);

    filled = true;

    if (debug) debug_print(mssm);

  }

  /// Helper function for getting mass eigenstates from gauge eigenstates
  void mass_es_pseudonyms::fill_mass_es_psn_gauge(str& is, str& isbar, str gauge_es, const SubSpectrum& mssm,
                                                  double tol, bool pt_error_on_mixing_failure, bool debug)
  {
    double max_mix = 0;
    str mass_es = slhahelp::mass_es_from_gauge_es(gauge_es, max_mix, mssm);

    if((max_mix*max_mix) >= 1-tol)
    {
       is = mass_es;
       isbar = Models::ParticleDB().get_antiparticle(mass_es);
       gauge_family_eigenstates[is] = gauge_es;
       gauge_family_eigenstates[isbar] = gauge_es.substr(0,gauge_es.length()-2)+"bar"+gauge_es.substr(gauge_es.length()-2);
       mass_eigenstates[gauge_family_eigenstates[isbar]] = is;
       mass_eigenstates[gauge_family_eigenstates[isbar]] = isbar;
    }
    else
    {
       std::stringstream ss;
       ss << "MSSM mass(-squared) eigenstate " << mass_es << " is only " << max_mix*max_mix*100 << "% gauge eigenstate " << gauge_es << "." << endl
          << "The requested tolerance is " << tol*100 << " => too much sfermion mixing to assume that this is a pure gauge eigenstate.";
       if (pt_error_on_mixing_failure)
       {
         invalid_point().raise(ss.str());
       }
       else
       {
         utils_error().raise(LOCAL_INFO, ss.str());
       }
    }

    if (debug) debug_print_gauge(mssm, gauge_es, mass_es, max_mix);
  }

  /// Helper function for getting family states from gauge eigenstates
  void mass_es_pseudonyms::fill_mass_es_psn_family(str& is, str& isbar, str family_state, const SubSpectrum& mssm,
                                                   double tol, bool pt_error_on_mixing_failure, bool debug)
  {
    /// First identify the mass eigenstate that best matches the requested family state.
    /// Then get the decomposition of that mass eigenstate into the two gauge states from the same family as the family state.
    std::vector<double> right_fam_gauge_comp;
    str mass_es = slhahelp::mass_es_closest_to_family(family_state, right_fam_gauge_comp, mssm);

    /// Simplest possible test.
    double mix_mag_sq = 0.0;
    for(auto i = right_fam_gauge_comp.begin(); i != right_fam_gauge_comp.end(); i++)
    {
       double mix = *i;
       mix_mag_sq += mix*mix;
    }

    if(mix_mag_sq > 1-tol)
    {
      is = mass_es;
      isbar = Models::ParticleDB().get_antiparticle(mass_es);
      gauge_family_eigenstates[is] = family_state;
      gauge_family_eigenstates[isbar] = family_state.substr(0,family_state.length()-2)+"bar"+family_state.substr(family_state.length()-2);
      mass_eigenstates[gauge_family_eigenstates[isbar]] = is;
      mass_eigenstates[gauge_family_eigenstates[isbar]] = isbar;
    }
    else
    {
       std::stringstream ss;
       ss << "MSSM mass(-squared) eigenstate " << mass_es << " is only " << mix_mag_sq*100 << "% the same family as "
          << "family state " << family_state << "." << endl << "The requested tolerance is " << tol*100
          << "% => too much inter-family sfermion mixing to assume that this is a pure family state.";
       if (pt_error_on_mixing_failure)
       {
         invalid_point().raise(ss.str());
       }
       else
       {
         utils_error().raise(LOCAL_INFO, ss.str());
       }
    }

    if (debug) debug_print_family(mssm, family_state, mass_es, mix_mag_sq, tol);
  }

  /// General debug printer for pseudonyms
  void mass_es_pseudonyms::debug_print(const SubSpectrum& mssm)
  {
    std::cout.precision(8);
    std::cout << "Dmix :" << std::endl;;
    for(int i = 1; i <=6; i++)
    {
      for(int j = 1; j <=6; j++)
      {
        std::cout << "     " << i << j << " = "
                  << std::scientific << std::setw(10)
                  <<  mssm.get(Par::Pole_Mixing,"~d", i, j);
      }
      std::cout << std::endl;
    }

    std::cout << "Umix :" << std::endl;;
    for(int i = 1; i <=6; i++)
    {
      for(int j = 1; j <=6; j++)
      {
        std::cout << "     " << i << j << " = "
                  << mssm.get(Par::Pole_Mixing,"~u", i, j);
      }
      std::cout << std::endl;
    }

    std::cout << "Emix :" << std::endl;;
    for(int i = 1; i <=6; i++)
    {
      for(int j = 1; j <=6; j++)
      {
        std::cout << "     " << i << j << " = "
                  << mssm.get(Par::Pole_Mixing,"~e-", i, j);
      }
      std::cout << std::endl;
    }

    std::cout << "NUmix :" << std::endl;;
    for(int i = 1; i <=3; i++)
    {
      for(int j = 1; j <=3; j++)
      {
       std::cout << "     " << i << j << " = "
                 << mssm.get(Par::Pole_Mixing,"~nu", i, j);
      }
      std::cout << std::endl;
    }

    std::cout << "isdl = "  << isdl << std::endl;
    std::cout << "isdlbar = "  << isdlbar << std::endl;
    std::cout << "isdr = "  << isdr << std::endl;
    std::cout << "isdrbar = "  << isdrbar << std::endl;

    std::cout << "isul = "  << isul << std::endl;
    std::cout << "isulbar = "  << isulbar << std::endl;
    std::cout << "isur = "  << isur << std::endl;
    std::cout << "isurbar = "  << isurbar << std::endl;

    std::cout << "issl = "  << issl << std::endl;
    std::cout << "isslbar = "  << isslbar << std::endl;
    std::cout << "issr = "  << issr << std::endl;
    std::cout << "issrbar = "  << issrbar << std::endl;

    std::cout << "iscl = "  << iscl << std::endl;
    std::cout << "isclbar = "  << isclbar << std::endl;
    std::cout << "iscr = "  << iscr << std::endl;
    std::cout << "iscrbar = "  << iscrbar << std::endl;

    std::cout << "isb1 = "  << isb1 << std::endl;
    std::cout << "isb1bar = "  << isb1bar << std::endl;
    std::cout << "isb2 = "  << isb2 << std::endl;
    std::cout << "isb2bar = "  << isb2bar << std::endl;

    std::cout << "ist1 = "  << ist1 << std::endl;
    std::cout << "ist1bar = "  << ist1bar << std::endl;
    std::cout << "ist2 = "  << ist2 << std::endl;
    std::cout << "ist2bar = "  << ist2bar << std::endl;

    std::cout << "isell = "  << isell << std::endl;
    std::cout << "isellbar = "  << isellbar << std::endl;
    std::cout << "iselr = "  << iselr << std::endl;
    std::cout << "iselrbar = "  << iselrbar << std::endl;

    std::cout << "isnel = "  << isnel << std::endl;
    std::cout << "isnelbar = "  << isnelbar << std::endl;

    std::cout << "ismul = "  << ismul << std::endl;
    std::cout << "ismulbar = "  << ismulbar << std::endl;
    std::cout << "ismur = "  << ismur << std::endl;
    std::cout << "ismurbar = "  << ismurbar << std::endl;

    std::cout << "isnmull = "  << isnmul << std::endl;
    std::cout << "isnmullbar = "  << isnmulbar << std::endl;

    std::cout << "istau1 = "  << istau1 << std::endl;
    std::cout << "istau1bar = "  << istau1bar << std::endl;
    std::cout << "istau2 = "  << istau2 << std::endl;
    std::cout << "istau2bar = "  << istau2bar << std::endl;

    std::cout << "isntaul = "  << isntaul << std::endl;
    std::cout << "isntaulbar = "  << isntaulbar << std::endl;

  }

  /// Gauge state debug printer for pseudonyms
  void mass_es_pseudonyms::debug_print_gauge(const SubSpectrum& mssm, str& gauge_es, str& mass_es, double& max_mix)
  {
    std::cout << "******** Extra tests ********* " << std::endl;
    std::cout << "gauge_es = " << gauge_es << std::endl;
    std::cout << "mass_es = " << mass_es << std::endl;

    double max_mix_r = 0.0;
    str g_es = slhahelp::gauge_es_from_mass_es(mass_es, max_mix_r, mssm);
    std::cout << "g_es = " << g_es << std::endl;
    std::cout << "max_mix = "  << max_mix<< std::endl;
    std::cout << "max_mix_r = "  << max_mix_r << std::endl;
    if(g_es != gauge_es) std::cout << "g_s error! " << std::endl;
    if(max_mix_r != max_mix) std::cout << "g_s max_mix_r error! " << std::endl;

    str ges = slhahelp::gauge_es_from_mass_es(mass_es, mssm, 1e-3, LOCAL_INFO, false);
    std::cout << "ges = "  << ges << std::endl;
    if(ges != gauge_es) std::cout << "ges error! " << std::endl;
    str mes = slhahelp::mass_es_from_gauge_es(gauge_es, mssm, 1e-3, LOCAL_INFO, false);
    std::cout << "mes = "  << ges << std::endl;
    if(mes != mass_es) std::cout << "mes error! " << std::endl;
  }

  /// Family state debug printer for pseudonyms
  void mass_es_pseudonyms::debug_print_family(const SubSpectrum& mssm, str& family_state, str& mass_es, double& mix_mag_sq, double& tol)
  {
    std::cout << "******** Extra tests ********* " << std::endl;
    std::cout << "family_state = "  << family_state <<std::endl;
    std::cout << "mass_es obtained from family_state = "  << mass_es
              << std::endl;
    double sum_sq_mix;
    str fs = slhahelp::family_state_closest_to_mass_es(mass_es, sum_sq_mix,
                                                       mssm);
    std::cout << "fs obtained from mass_es = " << fs << std::endl;
    std::cout << "sum_sq_mix = " << sum_sq_mix << std::endl;
    std::cout << "mix_mag_sq = " << mix_mag_sq << std::endl;
    if(fs != family_state) std::cout << "fs error! = " << std::endl;
    str f_s = slhahelp::family_state_closest_to_mass_es(mass_es, mssm, 1e-3, LOCAL_INFO, false);
    std::cout << "f_s obtained from mass_es = " << f_s << std::endl;
    if(f_s != family_state) std::cout << "f_s error! = " << std::endl;

    str m_es = slhahelp::mass_es_closest_to_family(family_state, mssm, tol, LOCAL_INFO, false);
    std::cout << "m_es = "  << m_es << std::endl;
    if(m_es != mass_es) std::cout << "m_es error! = " << std::endl;

    std::cout << "******** Special family_state_mix_matrix tests ********"
              << std::endl;
    str mass_es1, mass_es2, type;
    str types[] = {"~u","~d", "~e-"};
    std::set<str> set_type = {types, types+3};
    std::set<str>::iterator it;
    for (it = set_type.begin(); it != set_type.end(); ++it)
    {
      type = *it;
      for(int gen = 1;  gen <=3; gen++)
      {
        std::cout << "entering type = " << type << " and gen "
                 << gen << std::endl;
        std::vector<double> f_mix_matrix = slhahelp::family_state_mix_matrix(type,gen, mass_es1, mass_es2, mssm);
        std::cout << "mass_es1 = " << mass_es1 << std::endl;
        std::cout << "mass_es2 = " << mass_es2 << std::endl;
        for(int i = 0;  i<=3; i++)
        {
          std::cout << "f_mix_matrix[" << i << "] = "
                    << f_mix_matrix[i] << std::endl;
        }
        double row1sq = f_mix_matrix[0] * f_mix_matrix[0];
        row1sq += f_mix_matrix[1] * f_mix_matrix[1];
        double row2sq = f_mix_matrix[2] * f_mix_matrix[2];
        row2sq += f_mix_matrix[3] * f_mix_matrix[3];
        std::cout << "row1sq = " <<  row1sq << "  row2sq = "
                  <<  row2sq << std::endl;
      }
    }
  }


} //namespace gambit
