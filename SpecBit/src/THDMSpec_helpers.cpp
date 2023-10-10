//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///
///  *********************************************
///
///  Authors:
///
///  \author A.S. Woodcock
///          (alex.woodcock@outlook.com)
///  \date   Feb 2022
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
///
///  **********************************************

// #include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/THDMSpec_helpers.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/numerical_constants.hpp"

#include "gambit/Elements/spectrum_types.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Utils/stream_overloads.hpp" // Just for more convenient output to logger
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/Models/SimpleSpectra/THDMSimpleSpec.hpp"
#include "gambit/Utils/numerical_constants.hpp"

#include "gambit/Elements/sminputs.hpp"
#include "gambit/Elements/spectrum.hpp"

#include "gambit/Utils/stream_overloads.hpp" // Just for more convenient output to logger
#include "gambit/Utils/util_macros.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"

// Flexible SUSY stuff (should not be needed by the rest of gambit)
//#include "flexiblesusy/src/ew_input.hpp"
#include "flexiblesusy/src/lowe.h" // From softsusy; used by flexiblesusy
//#include "flexiblesusy/src/numerics.hpp"

// GSL headers
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_deriv.h>


namespace Gambit
{

  using namespace Utils;

   namespace SpecBit
   {

    using std::vector;

      // imaginary unit
      constexpr complexd ii(0,1);

      // helper function to ensure that the 2HDM scalar sector is Z2 symmetric
      void check_Z2(const double lambda6, const double lambda7, const str calculation_name)
      {
        if (std::abs(lambda6) != 0.0 || std::abs(lambda7) != 0.0)
        {
          std::ostringstream msg;
          msg << "SpecBit error (fatal): " << calculation_name << " is only compatible with Z2 conserving models. \
          Please fix you yaml file."
              << std::endl;
          std::cerr << msg.str();
          SpecBit_error().raise(LOCAL_INFO, msg.str());
        }
      }

      bool map_contains(const std::map<str,double> themap, const str key)
      {
        return themap.find(key) != themap.end();
      }

      std::map<str, double> create_empty_THDM_basis()
      {
            const double EMPTY = -1E10;
            std::map<str, double> basis;
            // create a complete list of keys for basis
            const std::vector<str> basis_keys{"lambda1", "lambda2", "lambda3", "lambda4", "lambda5", "lambda6", "lambda7", "m12_2", "m11_2", "m22_2", \
                                                "Lambda1", "Lambda2", "Lambda3", "Lambda4", "Lambda5", "Lambda6", "Lambda7", "M12_2", "M11_2", "M22_2", \
                                                "m_h", "m_H", "m_A", "m_Hp", "tanb", "sba","alpha"};
            // fill entries in basis
            for(const auto& each_basis_key : basis_keys)
            {
               basis.insert(std::make_pair(each_basis_key, EMPTY));
            }
            return basis;
      }

      void print_THDM_spectrum(std::map<str, double>& basis)
      {
            const double EMPTY = -1E10;
            const std::vector<str> basis_keys{"lambda1", "lambda2", "lambda3", "lambda4", "lambda5", "lambda6", "lambda7", "m12_2", "m11_2", "m22_2", \
                                                "Lambda1", "Lambda2", "Lambda3", "Lambda4", "Lambda5", "Lambda6", "Lambda7", "M12_2", "M11_2", "M22_2", \
                                                "m_h", "m_H", "m_A", "m_Hp", "tanb", "sba","alpha"};
            // fill entries in basis
            for(const auto& each_basis_key : basis_keys)
            {
            std::cout << each_basis_key << ": ";
            if (basis[each_basis_key]!= EMPTY) std::cout << basis[each_basis_key] << std::endl;
            else std::cout << "entry not filled" << std::endl;
            }
      }

      bool check_basis(const std::vector<str> basis_keys, std::map<str, double> basis)
      {
         const double EMPTY = -1E10;
         for(const auto& each_basis_key : basis_keys){
            if (!map_contains(basis, each_basis_key) || basis[each_basis_key] == EMPTY) return false;
         }
         return true;
      }

      void fill_generic_THDM_basis(std::map<str, double>& input_basis, const SMInputs& sminputs)
      {
         const std::vector<str> higgs_basis_keys{"Lambda1","Lambda2","Lambda3","Lambda4","Lambda5","Lambda6","Lambda7","M12_2","tanb"};
         const std::vector<str> physical_basis_keys{"m_h","m_H","m_A","m_Hp","tanb","m12_2","sba"};
         // necessary definitions
         double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
         double tanb  = input_basis["tanb"];
         double beta = atan(tanb);
         double sb = sin(beta), cb = cos(beta), tb = tan(beta);
         double sb2 = sb*sb, cb2 = cb*cb, ctb = 1./tb;
         double s2b = sin(2.*beta), c2b = cos(2.*beta);
         //initially try to fill from Higgs basis
         if (check_basis(higgs_basis_keys, input_basis))
         {
            // get values from higgs basis
            double Lambda1 = input_basis["Lambda1"], Lambda2 = input_basis["Lambda2"], Lambda3 = input_basis["Lambda3"], Lambda4 = input_basis["Lambda4"], Lambda5 = input_basis["Lambda5"];
            double Lambda6 = input_basis["Lambda6"], Lambda7 = input_basis["Lambda7"], M12_2 = input_basis["M12_2"];
            // set values of coupling basis
            double Lam345 = Lambda3 + Lambda4 + Lambda5;
            double M11_2 = M12_2*tb - 0.5*v2 * (Lambda1*cb*cb + Lam345*sb*sb + 3.0*Lambda6*sb*cb + Lambda7*sb*sb*tb);
            double M22_2 = M12_2*ctb - 0.5*v2 * (Lambda2*sb*sb + Lam345*cb*cb + Lambda6*cb*cb*ctb + 3.0*Lambda7*sb*cb);
            input_basis["m12_2"] = (M11_2-M22_2)*s2b + M12_2*c2b;
            // do the basis conversion here
            input_basis["lambda1"] = Lambda1*pow(cb,4) + Lambda2*pow(sb,4) + 0.5*Lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*Lambda6+pow(sb,2)*Lambda7);
            input_basis["lambda2"] = Lambda1*pow(sb,4) + Lambda2*pow(cb,4) + 0.5*Lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*Lambda6+pow(cb,2)*Lambda7);
            input_basis["lambda3"] = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda3 - s2b*c2b*(Lambda6-Lambda7);
            input_basis["lambda4"] = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda4 - s2b*c2b*(Lambda6-Lambda7);
            input_basis["lambda5"] = 0.25*pow(s2b,2)*(Lambda1+Lambda2-2.*Lam345) + Lambda5 - s2b*c2b*(Lambda6-Lambda7);
            input_basis["lambda6"] = -0.5*s2b*(Lambda1*pow(cb,2)-Lambda2*pow(sb,2)-Lam345*c2b) + cb*cos(3.*beta)*Lambda6 + sb*sin(3.*beta)*Lambda7;
            input_basis["lambda7"] = -0.5*s2b*(Lambda1*pow(sb,2)-Lambda2*pow(cb,2)+Lam345*c2b) + sb*sin(3.*beta)*Lambda6 + cb*cos(3.*beta)*Lambda7;
            // fill extra inputs
            input_basis["m11_2"] = M11_2*pow(cb,2) + M22_2*pow(sb,2) - M12_2*s2b;
            input_basis["m22_2"] = M11_2*pow(sb,2) + M22_2*pow(cb,2) + M12_2*s2b;
         }
         //otherwise try to fill from physical basis
         else if(check_basis(physical_basis_keys, input_basis))
         {
            // get values from physical basis
            double m_h = input_basis["m_h"], m_H = input_basis["m_H"], m_A = input_basis["m_A"], m_Hp = input_basis["m_Hp"];
            double lambda6 = input_basis["lambda6"], lambda7 = input_basis["lambda7"], m12_2 = input_basis["m12_2"];
            // TODO : check that sba follows through here
            // set values of coupling basis
            double alpha = beta - asin(input_basis["sba"]);
            double ca = cos(alpha), sa = sin(alpha);
            double ca2 = ca*ca, sa2 = sa*sa;
            input_basis["lambda1"] = (m_H*m_H*ca2+m_h*m_h*sa2-m12_2*tb)/v2/cb2-1.5*lambda6*tb+0.5*lambda7*tb*tb*tb;
            input_basis["lambda2"] = (m_H*m_H*sa2+m_h*m_h*ca2-m12_2*ctb)/v2/sb2+0.5*lambda6*ctb*ctb*ctb-1.5*lambda7*ctb;
            input_basis["lambda3"] = ((m_H*m_H-m_h*m_h)*ca*sa+2.*m_Hp*m_Hp*sb*cb-m12_2)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;
            input_basis["lambda4"] = ((m_A*m_A-2.*m_Hp*m_Hp)*cb*sb+m12_2)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;
            input_basis["lambda5"] = (m12_2-m_A*m_A*sb*cb)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;
            // fill extra inputs
            double lam345 = input_basis["lambda3"] + input_basis["lambda4"] + input_basis["lambda5"];
            input_basis["m11_2"] = m12_2*tb - 0.5*v2 * (input_basis["lambda1"]*cb*cb + lam345*sb*sb + 3.0*input_basis["lambda6"]*sb*cb + input_basis["lambda7"]*sb*sb*tb);
            input_basis["m22_2"] = m12_2*ctb - 0.5*v2 * (input_basis["lambda2"]*sb*sb + lam345*cb*cb + input_basis["lambda6"]*cb*cb*ctb + 3.0*input_basis["lambda7"]*sb*cb);
         }
         else
         {
            SpecBit_error().raise(LOCAL_INFO, "Cannot fill generic THDM basis");
         }
      }

      void fill_higgs_THDM_basis(std::map<str, double>& input_basis, const SMInputs& sminputs)
      {
         const std::vector<str> physical_basis_keys{"m_h","m_H","m_A","m_Hp","tanb","m12_2","sba"};
         const std::vector<str> generic_basis_keys{"lambda1","lambda2","lambda3","lambda4","lambda5","m12_2","tanb"};
         // necessary definitions
         double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
         double tanb  = input_basis["tanb"];
         double beta = atan(tanb);
         double sb = sin(beta), cb = cos(beta), tb = tan(beta);
         double ctb = 1./tb;
         double s2b = sin(2.*beta), c2b = cos(2.*beta);
         //initially try to fill from scalar basis
         if (check_basis(generic_basis_keys, input_basis))
         {
            // get values from coupling basis
            double lam1 = input_basis["lambda1"], lam2 = input_basis["lambda2"], lam3 = input_basis["lambda3"], lam4 = input_basis["lambda4"], lam5 = input_basis["lambda5"];
            double lam6 = input_basis["lambda6"], lam7 = input_basis["lambda7"], m12_2 = input_basis["m12_2"];
            double lam345 = lam3 + lam4 + lam5;
            // (also fill these in case they haven't been calculated)
            double m11_2 = m12_2*tb - 0.5*v2 * (lam1*cb*cb + lam345*sb*sb + 3.0*lam6*sb*cb + lam7*sb*sb*tb); input_basis["m11_2"] = m11_2;
            double m22_2 = m12_2*ctb - 0.5*v2 * (lam2*sb*sb + lam345*cb*cb + lam6*cb*cb*ctb + 3.0*lam7*sb*cb); input_basis["m22_2"] = m22_2;
            input_basis["M12_2"] = (m11_2-m22_2)*s2b + m12_2*c2b;
            input_basis["M11_2"] = m11_2*pow(cb,2) + m22_2*pow(sb,2) - m12_2*s2b;
            input_basis["M22_2"] = m11_2*pow(sb,2) + m22_2*pow(cb,2) + m12_2*s2b;
            // do the basis conversion here
            input_basis["Lambda1"] = lam1*pow(cb,4) + lam2*pow(sb,4) + 0.5*lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*lam6+pow(sb,2)*lam7);
            input_basis["Lambda2"] = lam1*pow(sb,4) + lam2*pow(cb,4) + 0.5*lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*lam6+pow(cb,2)*lam7);
            input_basis["Lambda3"] = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam3 - s2b*c2b*(lam6-lam7);
            input_basis["Lambda4"] = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam4 - s2b*c2b*(lam6-lam7);
            input_basis["Lambda5"] = 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam5 - s2b*c2b*(lam6-lam7);
            input_basis["Lambda6"] = -0.5*s2b*(lam1*pow(cb,2)-lam2*pow(sb,2)-lam345*c2b) + cb*cos(3.*beta)*lam6 + sb*sin(3.*beta)*lam7;
            input_basis["Lambda7"] = -0.5*s2b*(lam1*pow(sb,2)-lam2*pow(cb,2)+lam345*c2b) + sb*sin(3.*beta)*lam6 + cb*cos(3.*beta)*lam7;
         }
         //otherwise try to fill from physical basis
         else if(check_basis(physical_basis_keys, input_basis))
         {
            fill_generic_THDM_basis(input_basis, sminputs);
            fill_higgs_THDM_basis(input_basis, sminputs);
         }
         else
         {
            SpecBit_error().raise(LOCAL_INFO, "Cannot fill higgs THDM basis");
         }
      }

      void fill_physical_THDM_basis(std::map<str, double>& input_basis, const SMInputs& sminputs)
      {
         const std::vector<str> higgs_basis_keys{"Lambda1","Lambda2","Lambda3","Lambda4","Lambda5","M12_2","tanb"};
         const std::vector<str> generic_basis_keys{"lambda1","lambda2","lambda3","lambda4","lambda5","m12_2","tanb"};
         // necessary definitions
         double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
         double tanb  = input_basis["tanb"];
         double beta = atan(tanb);
         double sb = sin(beta), cb = cos(beta), tb = tan(beta);
         double sb2 = sb*sb, cb2 = cb*cb, ctb = 1./tb;
         //initially try to fill from higgs basis
         if(check_basis(generic_basis_keys, input_basis))
         {
            // get values from coupling basis
            double lam1 = input_basis["lambda1"], lam2 = input_basis["lambda2"], lam3 = input_basis["lambda3"], lam4 = input_basis["lambda4"], lam5 = input_basis["lambda5"];
            double lam6 = input_basis["lambda6"], lam7 = input_basis["lambda7"], m12_2 = input_basis["m12_2"];
            double lam345 = lam3 + lam4 + lam5;
            // do the basis conversion
            double m11_2 = m12_2*tb - 0.5*v2 * (lam1*cb*cb + lam345*sb*sb + 3.0*lam6*sb*cb + lam7*sb*sb*tb); input_basis["m11_2"] = m11_2;
            double m22_2 = m12_2*ctb - 0.5*v2 * (lam2*sb*sb + lam345*cb*cb + lam6*cb*cb*ctb + 3.0*lam7*sb*cb); input_basis["m22_2"] = m22_2;
            double m_A2;
            if (tb>0) m_A2 = m12_2/sb/cb-0.5*v2*(2*lam5+lam6*ctb+lam7*tb);
            else m_A2 = m22_2+0.5*v2*(lam3+lam4-lam5);
            double m_Hp2 = m_A2+0.5*v2*(lam5-lam4);
            double M112 = m_A2*sb2+v2*(lam1*cb2+2.*lam6*sb*cb+lam5*sb2);
            double M122 = -m_A2*sb*cb+v2*((lam3+lam4)*sb*cb+lam6*cb2+lam7*sb2);
            double M222 = m_A2*cb2+v2*(lam2*sb2+2.*lam7*sb*cb+lam5*cb2);
            double m_h2 = 0.5*(M112+M222-sqrt((M112-M222)*(M112-M222)+4.*M122*M122));
            double m_H2 = 0.5*(M112+M222+sqrt((M112-M222)*(M112-M222)+4.*M122*M122));
            // set the masses
            // invalidate point at this stage?
            if (m_h2 < 0.0) input_basis["m_h"] = -sqrt(-m_h2);
            else input_basis["m_h"] = sqrt(m_h2);
            if (m_H2 < 0.0) input_basis["m_H"] = -sqrt(-m_H2);
            else input_basis["m_H"] = sqrt(m_H2);
            if (m_A2 < 0.0) input_basis["m_A"] = -sqrt(-m_A2);
            else input_basis["m_A"] = sqrt(m_A2);
            if (m_Hp2 < 0.0) input_basis["m_Hp"] = -sqrt(-m_Hp2);
            else input_basis["m_Hp"] = sqrt(m_Hp2);
         }
         //otherwise try to fill from higgs basis
         else if (check_basis(higgs_basis_keys, input_basis))
         {
            fill_generic_THDM_basis(input_basis, sminputs);
            fill_physical_THDM_basis(input_basis, sminputs);
         }
         else
         {
            SpecBit_error().raise(LOCAL_INFO, "Cannot fill physical THDM basis");
         }
      }

      void generate_THDM_spectrum_tree_level(std::map<str, double>& basis, const SMInputs& sminputs)
      {
         const double EMPTY = -1E10;
         // validate basis entries
         // create a complete list of keys for basis
         const std::vector<str> basis_keys{"lambda1", "lambda2", "lambda3", "lambda4", "lambda5", "lambda6", "lambda7,", "m12_2", "m11_2", "m22_2", \
                                             "Lambda1", "Lambda2", "Lambda3", "Lambda4", "Lambda5", "Lambda6", "Lambda7", "M12_2", "M11_2", "M22_2", \
                                             "m_h", "m_H", "m_A", "m_Hp", "tanb", "sba","alpha"};
         // validate entries in basis
         for(const auto& each_basis_key : basis_keys)
         {
            if (!map_contains(basis, each_basis_key)) basis.insert(std::make_pair(each_basis_key, EMPTY));
         }

         // create a seperate list of keys for basis
         const std::vector<str> higgs_basis_keys{"Lambda1","Lambda2","Lambda3","Lambda4","Lambda5","M12_2","tanb"};
         const std::vector<str> generic_basis_keys{"lambda1","lambda2","lambda3","lambda4","lambda5","m12_2","tanb"};
         const std::vector<str> physical_basis_keys{"m_h","m_H","m_A","m_Hp","tanb","m12_2","sba"};

         // are the minimum requirements for a filled coupling basis satsified?
         bool coupling_filled = check_basis(generic_basis_keys, basis);
         // are the minimum requirements for a filled higgs basis satsified?
         bool higgs_filled = check_basis(higgs_basis_keys, basis);
         // are the minimum requirements for a filled physical basis satsified?
         bool physical_filled = check_basis(physical_basis_keys, basis);

         if (!coupling_filled && !higgs_filled && !physical_filled)
         {
            std::ostringstream errmsg;
            errmsg << "A problem was encountered during spectrum generation." << std::endl;
            errmsg << "Incomplete basis was sent to tree-level generator." << std::endl;
            SpecBit_error().raise(LOCAL_INFO, errmsg.str());
         }

         if (!coupling_filled) fill_generic_THDM_basis(basis, sminputs);
         if (!higgs_filled) fill_higgs_THDM_basis(basis, sminputs);
         if (!physical_filled) fill_physical_THDM_basis(basis, sminputs);

         // calculate alpha
         double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
         double tanb  = basis["tanb"];
         double beta = atan(tanb);
         double Lambda1 = basis["Lambda1"], Lambda3 = basis["Lambda3"], Lambda4 = basis["Lambda4"], Lambda5 = basis["Lambda5"];
         double Lambda6 = basis["Lambda6"], M22_2 = basis["M22_2"];
         double mC_2 = M22_2 + 0.5*v2*Lambda3;
         double mA_2 = mC_2 - 0.5*v2*(Lambda5 - Lambda4);
         double s2ba = -2.*Lambda6*v2, c2ba = -(mA_2+(Lambda5-Lambda1)*v2);
         double ba = 0.5*atan2(s2ba,c2ba);
         double alpha = beta - ba;
         if (alpha>M_PI/2.0)
         {
            alpha =  alpha-M_PI;
         }
         // fill basis
         basis["sba"] = sin(ba);
         basis["beta"] = beta;
         basis["alpha"] = alpha;
      }


    // returns the symmetry factor for a set of particels
    int get_symmetry_factor(std::vector<int> n_identical_particles)
    {
      int symm_factor = 1;
      for (const auto &n_identical : n_identical_particles)
      {
        symm_factor *= Utils::factorial(n_identical);
      }
      return symm_factor;
    }

    // is a particle neutral?
    bool is_neutral(int p1)
    {
      if (p1 == h0 || p1 == H0 || p1 == A0 || p1 == G0)
        return true;
      return false;
    }

    // is a particle a goldstone boson?
    bool is_goldstone(int p1)
    {
      if (p1 == G0 || p1 == Gp || p1 == Gm)
        return true;
      return false;
    }

    // returns all partical permutations for a set of neutral particles
    // includes the symmetry factor for number of times particles are outputed
    // expects particle input to be ordered
    std::vector<std::vector<scalar_type>> get_neutral_particle_permutations(std::vector<scalar_type> particles)
    {
      int neutral_index = 0, neutral_index_identical = 0, identical_counter = 0;
      vector<vector<scalar_type>> particle_permutations;
      // check if particle 0 is neutral
      if (!is_neutral(particles[0]))
        return {particles};
      // cycle through particles to find index of last neutral particle that is not a Goldstone boson
      while (is_neutral(particles[neutral_index]) && !is_goldstone(particles[neutral_index]) && neutral_index < (signed)(particles.size()))
      {
        neutral_index++;
      }
      neutral_index--; // fix to machine index
      // count identical neutral particles in the particles vector
      // retuurns vector with number of identical particles in order
      // starts at the first index of the particle array
      vector<int> identical_particles;
      while (neutral_index_identical < (signed)particles.size())
      {
        identical_counter = 1;
        if (particles[neutral_index_identical] != particles[neutral_index_identical + 1])
        {
          // the particle to the right is different
          identical_particles.push_back(identical_counter);
          neutral_index_identical++;
        }
        else
        {
          // the particle to the right is identical
          // keep searching right until a different particle is found
          while (neutral_index_identical < (signed)particles.size() - 1 && particles[neutral_index_identical] == particles[neutral_index_identical + 1])
          {
            neutral_index_identical++;
            identical_counter++;
          }
          neutral_index_identical++;
          identical_particles.push_back(identical_counter);
        }
      }

      const int symmetry_factor = get_symmetry_factor(identical_particles);
      // start permutating the neutral particles that are not Goldstone particles
      do
      {
        // append permutation *symmetry factor* number of times
        for (int j = 0; j < symmetry_factor; j++)
          particle_permutations.push_back(particles);
      } while (std::next_permutation(particles.begin(), particles.begin() + neutral_index + 1));

      return particle_permutations;
    }

    // helper function for == between particles
    bool particles_match(const std::vector<scalar_type> particles, const std::vector<scalar_type> test_particles)
    {
      return particles == test_particles;
    }

    void check_coupling_calcs(const ThdmSpec &s)
    {
      // check cubic couplings

      std::vector<str> names = {"h0GpGm", "h0GpGm", "H0GpGm", "H0GpGm", "h0GpHm", "h0G0A0", "H0GpHm", "H0G0A0", "A0GpHm", "h0HpHm", "h0A0A0", "H0HpHm", "H0A0A0", "h0h0h0", "h0h0H0", "h0H0H0", "H0H0H0", };

      auto couplings_physical = get_cubic_coupling_higgs(s, true);
      auto couplings_higgs = get_cubic_coupling_higgs(s, false);

      for (size_t i=0; i<names.size(); ++i)
      {
        double mag = 0.5 * (abs(couplings_higgs[i+1]) + abs(couplings_physical[i+1]) +1e-6);
        double err = abs(couplings_higgs[i+1] - couplings_physical[i+1]) / mag;
        if (err > 1e-7) std::cerr << "coupling mismatch (" << names[i] << "): " << std::fixed << std::setprecision(4) << err << std::endl;
      }

      // check quartic couplings

      std::vector<str> names2 = { "h0h0G0G0", "HpHmG0G0", "A0A0G0G0", "h0h0G0A0", "H0H0G0A0", "HpHmG0A0", "A0A0G0A0", "A0A0G0A0", "h0h0HpHm", "h0h0A0A0", "H0H0HpHm", "H0H0A0A0", "h0H0HpHm", "h0H0A0A0", "h0h0h0h0", "h0h0h0H0", "h0h0H0H0", "h0H0H0H0", "H0H0H0H0", "HpHmHpHm", "HpHmHpHm", "HpHmHpHm" };
      
      couplings_physical = get_quartic_couplings(s, true);
      couplings_higgs = get_quartic_couplings(s, false);

      for (size_t i=0; i<names2.size(); ++i)
      {
        double mag = 0.5 * (abs(couplings_higgs[i]) + abs(couplings_physical[i]) + 1e-6);
        double err = abs(couplings_higgs[i] - couplings_physical[i]) / mag;
        if (err > 1e-7) std::cerr << "coupling mismatch (" << names2[i] << "): " << std::fixed << std::setprecision(4) << err << std::endl;
      }
    }

    ThdmSpec::ThdmSpec(const SubSpectrum& he, const int fill_type)
    {
      if ((fill_type & FILL_GENERIC) != 0)
      {
          lam1 = he.get(Par::dimensionless,"lambda1");
          lam2 = he.get(Par::dimensionless,"lambda2");
          lam3 = he.get(Par::dimensionless,"lambda3");
          lam4 = he.get(Par::dimensionless,"lambda4");
          lam5 = he.get(Par::dimensionless,"lambda5");
          lam6 = he.get(Par::dimensionless,"lambda6");
          lam7 = he.get(Par::dimensionless,"lambda7");
      }

      if ((fill_type & FILL_HIGGS) != 0)
      {
          Lam1 = he.get(Par::dimensionless,"Lambda1");
          Lam2 = he.get(Par::dimensionless,"Lambda2");
          Lam3 = he.get(Par::dimensionless,"Lambda3");
          Lam4 = he.get(Par::dimensionless,"Lambda4");
          Lam5 = he.get(Par::dimensionless,"Lambda5");
          Lam6 = he.get(Par::dimensionless,"Lambda6");
          Lam7 = he.get(Par::dimensionless,"Lambda7");
      }

      if ((fill_type & FILL_PHYSICAL) != 0)
      {
          mh = he.get(Par::mass1,"h0_1");
          mH = he.get(Par::mass1,"h0_2");
          mA = he.get(Par::mass1,"A0");
          mHp = he.get(Par::mass1,"H+");
          mG = he.get(Par::mass1,"G0");
          mGp = he.get(Par::mass1,"G+");
          v = he.get(Par::mass1,"vev");
          v2 = v*v;
          m122 = he.get(Par::mass1,"m12_2");
          m112 = he.get(Par::mass1,"m11_2");
          m222 = he.get(Par::mass1,"m22_2");
      }

      if ((fill_type & FILL_ANGLES) != 0)
      {
          beta = he.get(Par::dimensionless,"beta");
          alpha = he.get(Par::dimensionless,"alpha");
          tanb = he.get(Par::dimensionless,"tanb");
          cosba = cos(beta-alpha);
          sinba = sin(beta-alpha);
      }

      // if ((fill_type & FILL_TYPE) != 0) ;

      if ((fill_type & FILL_YUKAWAS) != 0)
      {
          Ye = std::vector<double>({he.get(Par::dimensionless,"Ye",1,1),he.get(Par::dimensionless,"Ye",2,2),he.get(Par::dimensionless,"Ye",3,3)});
          Yu = std::vector<double>({he.get(Par::dimensionless,"Yu",1,1),he.get(Par::dimensionless,"Yu",2,2),he.get(Par::dimensionless,"Yu",3,3)});
          Yd = std::vector<double>({he.get(Par::dimensionless,"Yd",1,1),he.get(Par::dimensionless,"Yd",2,2),he.get(Par::dimensionless,"Yd",3,3)});
          model_type = he.get(Par::dimensionless,"model_type");
          g1 = he.get(Par::dimensionless,"g1");
          g2 = he.get(Par::dimensionless,"g2");
          g3 = he.get(Par::dimensionless,"g3");
      }
    }

    using q_matrix = std::vector<std::vector<complexd>>;

    // returns Class I q_ij matrix based upon Higgs basis
    q_matrix get_qij(const double ba, const double Lam6)
    {
      const double sba = sin(ba), cba = abs(cos(ba));
      q_matrix q = {{0.0, 0.0, 0.0}, {0.0, sba, (double)sgn(Lam6) * cba}, {0.0, -(double)sgn(Lam6) * cba, sba}, {0.0, 0.0, ii}, {0.0, ii, 0.0}};
      return q;
    }


    /// =================================================================================
    /// == Higgs couplings calculated using the Higgs basis (ref arXiv:hep-ph/0602242) ==
    /// =================================================================================


    // hhh coupling using Higgs basis
    complexd get_cubic_coupling_higgs_hhh(const ThdmSpec &s, const q_matrix &q, std::vector<scalar_type> particles)
    {
      const scalar_type j = particles[0], k = particles[1], l = particles[2];

      const double Lam1 = s.Lam1, Lam34 = s.Lam3 + s.Lam4;
      const double Lam5 = s.Lam5, Lam6 = s.Lam6, Lam7 = s.Lam7;
      complexd c(0.0, 0.0);

      c += q[j][1] * std::conj(q[k][1]) * (q[l][1]).real() * Lam1;
      c += q[j][2] * std::conj(q[k][2]) * (q[l][1]).real() * Lam34;
      c += (std::conj(q[j][1]) * q[k][2] * q[l][2] * Lam5).real();
      c += ((2.0 * q[j][1] + std::conj(q[j][1])) * std::conj(q[k][1]) * q[l][2] * Lam6 * (double)sgn(Lam6)).real();
      c += (std::conj(q[j][2]) * q[k][2] * q[l][2] * Lam7 * (double)sgn(Lam6)).real();
      c *= 0.5 * s.v;
      return c;
    }

    // hH+H- coupling
    complexd get_cubic_coupling_higgs_hHpHm(const ThdmSpec &s, const q_matrix &q, scalar_type k)
    {
      return s.v * ((q[k][1]).real() * s.Lam3 + (q[k][2] * (double)sgn(s.Lam6) * s.Lam7).real());
    }

    // hG+G- coupling
    complexd get_cubic_coupling_higgs_hGpGm(const ThdmSpec &s, const q_matrix &q, scalar_type k)
    {
      double Lambda6 = s.Lam6;
      return s.v * ((q[k][1]).real() * s.Lam1 + (q[k][2] * (double)sgn(Lambda6) * Lambda6).real());
    }

    // hG-H+ coupling
    complexd get_cubic_coupling_higgs_hGmHp(const ThdmSpec &s, const q_matrix &q, scalar_type k)
    {
      double Lambda6 = s.Lam6;
      return s.v * 0.5 * (double)sgn(Lambda6) * (std::conj(q[k][2]) * s.Lam4 + q[k][2] * s.Lam5 + 2.0 * (q[k][1]).real() * Lambda6 * (double)sgn(Lambda6));
    }

    // hhG0 coupling
    complexd get_cubic_coupling_higgs_hhG0(const ThdmSpec &s, const q_matrix &q, vector<scalar_type> particles)
    {
      const scalar_type k = particles[0], l = particles[1];
      double Lambda6 = s.Lam6;
      return s.v * 0.5 * ((q[k][2] * q[l][2] * s.Lam5).imag() + 2.0 * q[k][1] * (q[l][2] * Lambda6 * (double)sgn(Lambda6)).imag());
    }

    // hG0G0 coupling
    complexd get_cubic_coupling_higgs_hG0G0(const ThdmSpec &s, const q_matrix &q, scalar_type k)
    {
      double Lambda6 = s.Lam6;
      return 0.5 * s.v * (q[k][1] * s.Lam1 + (q[k][2] * Lambda6 * (double)sgn(Lambda6)).real());
    }

    // hhhh coupling
    complexd get_quartic_coupling_higgs_hhhh(const ThdmSpec &s, const q_matrix &q, vector<scalar_type> particles)
    {
      const scalar_type j = particles[0], k = particles[1], l = particles[2], m = particles[3];
      const double Lam1 = s.Lam1, Lam2 = s.Lam2, Lam34 = s.Lam3 + s.Lam4;
      const double Lam5 = s.Lam5, Lam6 = s.Lam6, Lam7 = s.Lam7;
      complexd c(0.0, 0.0);

      c += q[j][1] * q[k][1] * std::conj(q[l][1]) * std::conj(q[m][1]) * Lam1;
      c += q[j][2] * q[k][2] * std::conj(q[l][2]) * std::conj(q[m][2]) * Lam2;
      c += 2.0 * q[j][1] * std::conj(q[k][1]) * q[l][2] * std::conj(q[m][2]) * Lam34;
      c += 2.0 * (std::conj(q[j][1]) * std::conj(q[k][1]) * q[l][2] * q[m][2] * Lam5).real();
      c += 4.0 * (q[j][1] * std::conj(q[k][1]) * std::conj(q[l][1]) * q[m][2] * Lam6 * (double)sgn(Lam6)).real();
      // TODO: I feel this should be sgn(Lam7), where do these equations come from?
      c += 4.0 * (std::conj(q[j][1]) * q[k][2] * q[l][2] * std::conj(q[m][2]) * Lam7 * (double)sgn(Lam6)).real();
      return 0.125 * c;
    }

    // hhG+G- coupling
    complexd get_quartic_coupling_higgs_hhGpGm(const ThdmSpec &s, const q_matrix &q, std::vector<scalar_type> particles)
    {
      const scalar_type j = particles[0], k = particles[1];
      const double Lambda6 = s.Lam6;
      return 0.5 * (q[j][1] * std::conj(q[k][1]) * s.Lam1 + q[j][2] * std::conj(q[k][2]) * s.Lam3 + 2.0 * (q[j][1] * q[k][2] * Lambda6 * (double)sgn(Lambda6)).real());
    }

    // hhH+H- coupling
    complexd get_quartic_coupling_higgs_hhHpHm(const ThdmSpec &s, const q_matrix &q, std::vector<scalar_type> particles)
    {
      const scalar_type j = particles[0], k = particles[1];
      return 0.5 * (q[j][2] * std::conj(q[k][2]) * s.Lam2 + q[j][1] * std::conj(q[k][1]) * s.Lam3 + 2.0 * (q[j][1] * q[k][2] * s.Lam7 * (double)sgn(s.Lam6)).real());
    }

    // hhG+H- coupling
    complexd get_quartic_coupling_higgs_hhGmHp(const ThdmSpec &s, const q_matrix &q, std::vector<scalar_type> particles)
    {
      const scalar_type j = particles[0], k = particles[1];
      const double Lam4 = s.Lam4, Lam5 = s.Lam5, Lam6 = s.Lam6, Lam7 = s.Lam7;
      complexd c(0.0, 0.0);
      c += (double)sgn(Lam6) * q[j][1] * std::conj(q[k][2]) * Lam4;
      c += std::conj(q[j][1]) * q[k][2] * Lam5;
      c += q[j][1] * std::conj(q[k][1]) * Lam6 * (double)sgn(Lam6);
      c += q[j][2] * std::conj(q[k][2]) * Lam7 * (double)sgn(Lam6);
      return 0.5 * c;
    }

    // hG0G0G0 coupling
    complexd get_quartic_coupling_higgs_hG0G0G0(const ThdmSpec &s, const q_matrix &q, scalar_type m)
    {
      const double Lam6 = s.Lam6;
      return 0.5 * (q[m][2] * Lam6 * (double)sgn(Lam6)).imag();
    }

    // hhG0G0 coupling
    complexd get_quartic_coupling_higgs_hhG0G0(const ThdmSpec &s, const q_matrix &q, std::vector<scalar_type> particles)
    {
      const scalar_type l = particles[0], m = particles[1];
      const double Lam6 = s.Lam6;
      complexd c(0.0, 0.0);
      c = (q[l][1] * q[m][1] * s.Lam1 + q[l][2] * std::conj(q[m][2]) * (s.Lam3 + s.Lam4));
      c += -(q[l][2] * q[m][2] * s.Lam5).real() + 2.0 * q[l][1] * (q[m][2] * Lam6 * (double)sgn(Lam6)).real();
      return 0.25 * c;
    }

    // hhhG0 coupling
    complexd get_quartic_coupling_higgs_hhhG0(const ThdmSpec &s, const q_matrix &q, std::vector<scalar_type> particles)
    {
      const scalar_type k = particles[1], l = particles[1], m = particles[2];
      const double Lam6 = s.Lam6;
      complexd c(0.0, 0.0);
      c = q[k][1] * (q[l][2] * q[m][2] * s.Lam5).real() + q[k][1] * q[l][1] * (q[m][2] * Lam6 * (double)sgn(Lam6)).real();
      c += (q[k][2] * q[l][2] * std::conj(q[m][2]) * s.Lam7 * (double)sgn(Lam6)).real();
      return 0.5 * c;
    }


    /// ===========================================================
    /// === Higgs couplings calculated using the physical basis ===
    /// ===========================================================


    // h0G+G- coupling using physical basis
    complexd get_cubic_coupling_physical_h0GpGm(const ThdmSpec &s)
    {
      const double mh = s.mh;
      const double mh2 = pow(mh, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double v = s.v;
      return 1.0 / v * (-1.0 * mh2 * sba);
    }

    // H0G+G- coupling using physical basiss
    complexd get_cubic_coupling_physical_H0GpGm(const ThdmSpec &s)
    {
      const double mH = s.mH;
      const double mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = (cos(b - a));
      const double v = s.v;
      return 1.0 / v * (-1.0 * mH2 * cba);
    }

    // h0G+H- coupling using physical basis
    complexd get_cubic_coupling_physical_h0GpHm(const ThdmSpec &s)
    {
      const double mh = s.mh, mC = s.mHp;
      const double mh2 = pow(mh, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = (cos(b - a));
      const double v = s.v;
      return 1.0 / v * (-1.0 * (mh2 - mC2) * cba);
    }

    // h0G0A0 coupling using physical basis
    complexd get_cubic_coupling_physical_h0G0A0(const ThdmSpec &s)
    {
      const double mh = s.mh, mA = s.mA;
      const double mh2 = pow(mh, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = (cos(b - a));
      const double v = s.v;
      return 1.0 / v * (-1.0 * (mh2 - mA2) * cba);
    }

    // H0G+H- coupling using physical basis
    complexd get_cubic_coupling_physical_H0GpHm(const ThdmSpec &s)
    {
      const double mH = s.mH, mC = s.mHp;
      const double mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double v = s.v;
      return 1.0 / v * (1.0 * (mH2 - mC2) * sba);
    }

    // H0G0A0 coupling using physical basis
    complexd get_cubic_coupling_physical_H0G0A0(const ThdmSpec &s)
    {
      const double mH = s.mH, mA = s.mA;
      const double mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double v = s.v;
      return 1.0 / v * (1.0 * (mH2 - mA2) * sba);
    }

    // A0G+H- coupling using physical basis
    complexd get_cubic_coupling_physical_A0GpHm(const ThdmSpec &s)
    {
      const double mA = s.mA, mC = s.mHp;
      const double mA2 = pow(mA, 2), mC2 = pow(mC, 2);
      const double v = s.v;
      return 1.0 / v * (-1.0 * ii * (mA2 - mC2));
    }

    // h0H+H- coupling using physical basis
    complexd get_cubic_coupling_physical_h0HpHm(const ThdmSpec &s)
    {
      const double mh = s.mh, mC = s.mHp, m122 = s.m122;
      const double mh2 = pow(mh, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), cbap = cos(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = s.v;
      return 1.0 / v * (sbinv * cbinv * (m122 * cbap * sbinv * cbinv - mh2 * c2b * cba) - (mh2 + 2.0 * mC2) * sba);
    }

    // h0A0A0 coupling using physical basis
    complexd get_cubic_coupling_physical_h0A0A0(const ThdmSpec &s)
    {
      const double mh = s.mh, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), cbap = cos(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = s.v;
      return 1.0 / v * (sbinv * cbinv * (m122 * cbap * sbinv * cbinv - mh2 * c2b * cba) - (mh2 + 2.0 * mA2) * sba);
    }

    // H0H+H- coupling using physical basis
    complexd get_cubic_coupling_physical_H0HpHm(const ThdmSpec &s)
    {
      const double mH = s.mH, mC = s.mHp, m122 = s.m122;
      const double mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), sbap = sin(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = s.v;
      return 1.0 / v * (sbinv * cbinv * (m122 * sbap * sbinv * cbinv + mH2 * c2b * sba) - (mH2 + 2.0 * mC2) * cba);
    }

    // H0A0A0 coupling using physical basis
    complexd get_cubic_coupling_physical_H0A0A0(const ThdmSpec &s)
    {
      const double mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), sbap = sin(b + a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double c2b = cos(2.0 * b);
      const double v = s.v;
      return 1.0 / v * (sbinv * cbinv * (m122 * sbap * sbinv * cbinv + mH2 * c2b * sba) - (mH2 + 2.0 * mA2) * cba);
    }

    // h0h0h0 coupling using physical basis
    complexd get_cubic_coupling_physical_h0h0h0(const ThdmSpec &s)
    {
      const double mh = s.mh, m122 = s.m122;
      const double mh2 = pow(mh, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), cbap = cos(b + a);
      const double cba2 = pow(cba, 2);
      const double s2b = sin(2.0 * b);
      const double v = s.v;
      return 3.0 / (4.0 * v * s2b * s2b) * (16.0 * m122 * cbap * cba2 - mh2 * (3.0 * sin(3.0 * b + a) + 3.0 * sba + sin(3.0 * b - 3.0 * a) + sin(b + 3.0 * a)));
    }

    // h0h0H0 coupling using physical basis
    complexd get_cubic_coupling_physical_h0h0H0(const ThdmSpec &s)
    {
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = (cos(b - a));
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v = s.v;
      return -cba / (s2b * v) * (2.0 * m122 + (mH2 + 2.0 * mh2 - 3.0 * m122 * sbinv * cbinv) * s2a);
    }

    // h0H0H0 coupling using physical basis
    complexd get_cubic_coupling_physical_h0H0H0(const ThdmSpec &s)
    {
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v = s.v;
      return sba / (s2b * v) * (-2.0 * m122 + (mh2 + 2.0 * mH2 - 3.0 * m122 * sbinv * cbinv) * s2a);
    }

    // H0H0H0 coupling using physical basis
    complexd get_cubic_coupling_physical_H0H0H0(const ThdmSpec &s)
    {
      const double mH = s.mH, m122 = s.m122;
      const double mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = (cos(b - a)), sbap = sin(b + a);
      const double sba2 = pow(sba, 2);
      const double s2b = sin(2.0 * b);
      const double v = s.v;
      return 3.0 / (4.0 * v * s2b * s2b) * (16.0 * m122 * sbap * sba2 + mH2 * (3.0 * cos(3.0 * b + a) - 3.0 * cba + cos(3.0 * b - 3.0 * a) - cos(b + 3.0 * a)));
    }

    // h0h0G0G0 coupling using physical basis
    complexd get_quartic_coupling_physical_h0h0G0G0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double t2binv = 1.0 / (tan(2.0 * b));
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = -1.0 / v2 * (mH2 * pow(cba, 4) + 2.0 * (mh2 - mH2) * pow(cba, 3) * sba * t2binv + mh2 * pow(sba, 4));
      coupling += -1.0 / v2 * cba2 * (2.0 * mA2 - 2.0 * m122 * sbinv * cbinv + (3.0 * mh2 - mH2) * sba2);
      return coupling;
    }

    // h0h0G0G0 coupling using physical basis
    complexd get_quartic_coupling_physical_HpHmG0G0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double t2binv = 1.0 / (tan(2.0 * b)), sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = -1.0 / v2 * (mH2 * pow(cba, 4) + 2.0 * (mh2 - mH2) * pow(sba, 3) * cba * t2binv + mh2 * pow(sba, 4));
      coupling += -1.0 / v2 * sba2 * (2.0 * mA2 - 2.0 * m122 * sbinv * cbinv + (3.0 * mH2 - mh2) * cba2);
      return coupling;
    }

    // A0A0G0G0 coupling using physical basis
    complexd get_quartic_coupling_physical_A0A0G0G0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mC = s.mHp, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double t2binv = 1.0 / (tan(2.0 * b));
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / v2 * (2.0 * m122 * sbinv * cbinv - 2.0 * mC2 - mH2 * cba2 - mh2 * sba2 + (mH2 - mh2) * t2binv * s2b2a);
      return coupling;
    }

    // h0h0G0A0 coupling using physical basis
    complexd get_quartic_coupling_physical_h0h0G0A0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double t2binv = 1.0 / (tan(2.0 * b)), sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / v2 * (2.0 * m122 * sbinv * cbinv - (mH2 + 2.0 * mh2) * cba2 - (mh2 + 2.0 * mH2) * sba2 + (mH2 - mh2) * t2binv * s2b2a);
      return coupling;
    }

    // H0H0G0A0 coupling using physical basis
    complexd get_quartic_coupling_physical_H0H0G0A0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = cos(b - a);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a), s2a2b = sin(2.0 * a - 2.0 * b);
      const double c2b = cos(2.0 * b);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b) * (mH2 * s2b2a * s2a - mA2 * s2b * s2a2b + cba * (4.0 * m122 * cba * sbinv * cbinv * c2b - mh2 * (cos(-1.0 * b + 3.0 * a) + 3.0 * cos(b + a))));
      return coupling;
    }

    // HpHmG0A0 coupling using physical basis
    complexd get_quartic_coupling_physical_HpHmG0A0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a), s2a2b = sin(2.0 * a - 2.0 * b);
      const double c2b = cos(2.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b) * (mh2 * s2b2a * s2a + mA2 * s2b * s2a2b + sba * (4.0 * m122 * sba * sbinv * cbinv * c2b - mH2 * (sin(-1.0 * b + 3.0 * a) - 3.0 * sin(b + a))));
      return coupling;
    }

    // A0A0G0A0 coupling using physical basis
    complexd get_quartic_coupling_physical_A0A0G0A0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double s2b = sin(2.0 * b);
      const double c2b = cos(2.0 * b), c2a = cos(2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b * s2b) * (32 * m122 * c2b + 2.0 * (mH2 - mh2) * (3.0 * c2a + cos(4.0 * b - 2.0 * a)) * s2b - 4.0 * (mh2 + mH2) * sin(4.0 * b));
      return coupling;
    }

    // h0h0HpHm coupling using physical basis
    complexd get_quartic_coupling_physical_h0h0HpHm(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mC = s.mHp, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sab = sin(a - b), sab2 = pow(sab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 + c2a2b + c4b) + 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a + 6.0 * c2a2b + c4a4b + 3.0 * c4b + 10.0 * c2a2bp) * mh2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) + 2.0 * s2b) * mH2 + 32.0 * sab2 * s2b * mC2);
      return coupling;
    }

    // h0h0A0A0 coupling using physical basis
    complexd get_quartic_coupling_physical_h0h0A0A0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sab = sin(a - b), sab2 = pow(sab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 + c2a2b + c4b) + 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a + 6.0 * c2a2b + c4a4b + 3.0 * c4b + 10.0 * c2a2bp) * mh2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) + 2.0 * s2b) * mH2 + 32.0 * sab2 * s2b * mA2);
      return coupling;
    }

    // H0H0HpHm coupling using physical basis
    complexd get_quartic_coupling_physical_H0H0HpHm(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mC = s.mHp, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double cab = cos(a - b), cab2 = pow(cab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (-cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 - c2a2b + c4b) - 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a - 6.0 * c2a2b + c4a4b + 3.0 * c4b - 10.0 * c2a2bp) * mH2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) - 2.0 * s2b) * mh2 + 32.0 * cab2 * s2b * mC2);
      return coupling;
    }

    // H0H0A0A0 coupling using physical basis
    complexd get_quartic_coupling_physical_H0H0A0A0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double cab = cos(a - b), cab2 = pow(cab, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b), sbinv2 = pow(sbinv, 2), cbinv2 = pow(cbinv, 2);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2a2b = cos(2.0 * a - 2.0 * b), c2a2bp = cos(2.0 * a + 2.0 * b);
      const double c4a4b = cos(4.0 * a - 4.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (16.0 * v2 * s2b) * 2.0 * sbinv2 * cbinv2 * (-cos(2.0 * a - 6.0 * b) + 2.0 * (3.0 - c2a2b + c4b) - 5.0 * c2a2bp) * m122;
      coupling += -1.0 / (16.0 * v2 * s2b) * sbinv * cbinv * (9.0 + 3.0 * c4a - 6.0 * c2a2b + c4a4b + 3.0 * c4b - 10.0 * c2a2bp) * mH2;
      coupling += -1.0 / (16.0 * v2 * s2b) * (2.0 * sbinv * cbinv * s2a * (3.0 * s2a + sin(2.0 * a - 4.0 * b) - 2.0 * s2b) * mh2 + 32.0 * cab2 * s2b * mA2);
      return coupling;
    }

    // h0H0HpHm coupling using physical basis
    complexd get_quartic_coupling_physical_h0H0HpHm(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mC = s.mHp, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mC2 = pow(mC, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), cba = cos(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s4b = sin(4.0 * b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double s3b3a = sin(3.0 * b - 3.0 * a);
      const double c4b = cos(4.0 * b);
      const double c2b2a = cos(2.0 * b - 2.0 * a);
      const double c3b3a = cos(3.0 * b - 3.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b) * cba * sbinv * cbinv * (3.0 * sba + s3b3a - 3.0 * sin(b + 3.0 * a) - sin(3.0 * b + a)) * mh2;
      coupling += 1.0 / (8.0 * v2 * s2b) * sba * sbinv * cbinv * (3.0 * cba - c3b3a - 3.0 * cos(b + 3.0 * a) + cos(3.0 * b + a)) * mH2;
      coupling += -1.0 / (8.0 * v2 * s2b) * (8.0 * s2b2a * s2b * mC2 + 4.0 * pow(1.0 / s2b, 2) * (2.0 * (1.0 + 3.0 * c4b) * s2b2a - 4.0 * c2b2a * s4b) * m122);
      return coupling;
    }

    // h0H0A0A0 coupling using physical basis
    complexd get_quartic_coupling_physical_h0H0A0A0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, mA = s.mA, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2), mA2 = pow(mA, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double cba = cos(b - a);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s4b = sin(4.0 * b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double s3b3a = sin(3.0 * b - 3.0 * a);
      const double c4b = cos(4.0 * b);
      const double c2b2a = cos(2.0 * b - 2.0 * a);
      const double c3b3a = cos(3.0 * b - 3.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b) * cba * sbinv * cbinv * (3.0 * sba + s3b3a - 3.0 * sin(b + 3.0 * a) - sin(3.0 * b + a)) * mh2;
      coupling += 1.0 / (8.0 * v2 * s2b) * sba * sbinv * cbinv * (3.0 * cba - c3b3a - 3.0 * cos(b + 3.0 * a) + cos(3.0 * b + a)) * mH2;
      coupling += -1.0 / (8.0 * v2 * s2b) * (8.0 * s2b2a * s2b * mA2 + 4.0 * pow(1.0 / s2b, 2) * (2.0 * (1.0 + 3.0 * c4b) * s2b2a - 4.0 * c2b2a * s4b) * m122);
      return coupling;
    }

    // h0h0h0h0 coupling using physical basis
    complexd get_quartic_coupling_physical_h0h0h0h0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double cba = cos(b - a), cbap = cos(b + a), cba2 = pow(cba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 3.0 / (4.0 * v2 * s2b * s2b) * 4.0 * cba2 * (4.0 * m122 * sbinv * cbinv * pow(cbap, 2) - mH2 * pow(s2a, 2));
      coupling += -3.0 / (4.0 * v2 * s2b * s2b) * mh2 * pow((cos(-b + 3.0 * a) + 3.0 * cbap), 2);
      return coupling;
    }

    // h0h0h0H0 coupling using physical basis
    complexd get_quartic_coupling_physical_h0h0h0H0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a);
      const double cba = cos(b - a), cbap = cos(b + a);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b * s2b) * 3.0 * s2a * (mH2 * s2a * s2b2a - mh2 * cba * (cos(-b + 3.0 * a) + 3.0 * cbap));
      coupling += 1.0 / (2.0 * v2 * s2b * s2b) * 12.0 * m122 * (1.0 / s2b) * cba * (sin(b + 3.0 * a) - sba);
      return coupling;
    }

    // h0h0H0H0 coupling using physical basis
    complexd get_quartic_coupling_physical_h0h0H0H0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b);
      const double c4b = cos(4.0 * b), c4a = cos(4.0 * a);
      const double c2b2a = cos(2.0 * b - 2.0 * a), c2b2ap = cos(2.0 * b + 2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (8.0 * v2 * s2b * s2b) * (4.0 * sbinv * cbinv * (2.0 + c4b - 3.0 * c4a) * m122 + 6.0 * (c4a - 1.0) * (mh2 + mH2));
      coupling += 1.0 / (8.0 * v2 * s2b * s2b) * (3.0 * cos(-2.0 * b + 6.0 * a) - c2b2ap - 2.0 * c2b2a) * (mh2 - mH2);
      return coupling;
    }

    // h0H0H0H0 coupling using physical basis
    complexd get_quartic_coupling_physical_h0H0H0H0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sbap = sin(b + a);
      const double cba = cos(b - a);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 1.0 / (2.0 * v2 * s2b * s2b) * 3.0 * s2a * (mh2 * s2a * s2b2a - mH2 * sba * (sin(-b + 3.0 * a) - 3.0 * sbap));
      coupling += 1.0 / (2.0 * v2 * s2b * s2b) * 12.0 * m122 * (1.0 / s2b) * sba * (cos(b + 3.0 * a) - cba);
      return coupling;
    }

    // H0H0H0H0 coupling using physical basis
    complexd get_quartic_coupling_physical_H0H0H0H0(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sbap = sin(b + a), sba2 = pow(sba, 2);
      const double sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b = sin(2.0 * b), s2a = sin(2.0 * a);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 3.0 / (4.0 * v2 * s2b * s2b) * 4.0 * sba2 * (4.0 * m122 * sbinv * cbinv * pow(sbap, 2) - mh2 * pow(s2a, 2));
      coupling += -3.0 / (4.0 * v2 * s2b * s2b) * mH2 * pow((sin(-b + 3.0 * a) - 3.0 * sbap), 2);
      return coupling;
    }

    // HpHmHpHm coupling using physical basis
    complexd get_quartic_coupling_physical_HpHmHpHm(const ThdmSpec &s)
    {
      // extract parameters
      const double mh = s.mh, mH = s.mH, m122 = s.m122;
      const double mh2 = pow(mh, 2), mH2 = pow(mH, 2);
      const double b = s.beta, a = s.alpha;
      const double sba = sin(b - a), sba2 = pow(sba, 2);
      const double cba = cos(b - a), cba2 = pow(cba, 2);
      const double t2binv = 1.0 / (tan(2.0 * b)), sbinv = 1.0 / sin(b), cbinv = 1.0 / cos(b);
      const double s2b2a = sin(2.0 * b - 2.0 * a);
      const double c2b = cos(2.0 * b);
      const double v2 = pow(s.v,2);
      // calculate coupling
      complexd coupling = 0.0;
      coupling = 2.0 / v2 * ((mH2 - mh2) * c2b * sbinv * cbinv * s2b2a - mh2 * sba2);
      coupling += -2.0 / v2 * (cba2 * (mH2 + 4.0 * mh2 * pow(t2binv, 2)) + 4.0 * pow(t2binv, 2) * (mH2 * sba2 - m122 * sbinv * cbinv));
      return coupling;
    }


    ///  ===========================================================
    ///  == helper functions to get couplings in more generic way ==
    ///  ===========================================================


    // main function to get cubic higgs coupling
    complexd get_cubic_coupling_higgs(const ThdmSpec &s, scalar_type p1, scalar_type p2, scalar_type p3)
    {
      complexd c(0.0, 0.0);
      const double ba = s.beta - s.alpha;
      const double Lam6 = s.Lam6;
      const q_matrix q = get_qij(ba, Lam6);

      std::vector<scalar_type> particles = {p1, p2, p3};
      std::sort(particles.begin(), particles.end()); // order particles
      p1 = particles[0];
      p2 = particles[1];
      p3 = particles[2];

      // Get a sign factor based on particles involved in the coupling
      // - based up Class I
      int sign = 1;
      for (auto const &each_part : particles)
      {
        if (each_part == H0)
          sign *= -(double)sgn(Lam6);
        else if (each_part == A0)
          sign *= (double)sgn(Lam6);
      }

      // Get coupling
      if (is_neutral(p1) && is_neutral(p2) && is_neutral(p3))
      {
        for (auto const &particles_perm : get_neutral_particle_permutations(particles))
        {
          if (particles_match(particles, {p1, G0, G0}))
            c += get_cubic_coupling_higgs_hG0G0(s, q, p1);
          else if (particles_match(particles, {p1, p2, G0}))
            c += get_cubic_coupling_higgs_hhG0(s, q, particles_perm);
          else
            c += get_cubic_coupling_higgs_hhh(s, q, particles_perm);
        }
      }
      else if (is_neutral(p1) && !is_neutral(p2) && !is_neutral(p3))
      {
        if (particles_match(particles, {p1, Hp, Hm}))
          c += get_cubic_coupling_higgs_hHpHm(s, q, p1);
        else if (particles_match(particles, {p1, Gp, Gm}))
          c += get_cubic_coupling_higgs_hGpGm(s, q, p1);
        else if (particles_match(particles, {p1, Hp, Gm}))
          c += get_cubic_coupling_higgs_hGmHp(s, q, p1);
        else if (particles_match(particles, {p1, Hm, Gp}))
          c += std::conj(get_cubic_coupling_higgs_hGmHp(s, q, p1));
      }

      return -ii * c * (double)sign;
    }

    // main function to get quartic higgs couplings
    complexd get_quartic_coupling_higgs(const ThdmSpec &s, scalar_type p1, scalar_type p2, scalar_type p3, scalar_type p4)
    {
      complexd c(0.0, 0.0);
      const double ba = s.beta - s.alpha;
      const double Lam1 = s.Lam4, Lam2 = s.Lam2, Lam3 = s.Lam3;
      const double Lam4 = s.Lam4, Lam5 = s.Lam5, Lam6 = s.Lam6, Lam7 = s.Lam7;
      const q_matrix q = get_qij(ba, Lam6);

      std::vector<scalar_type> particles = {p1, p2, p3, p4};
      std::sort(particles.begin(), particles.end()); // order particles
      p1 = particles[0];
      p2 = particles[1];
      p3 = particles[2];
      p4 = particles[3];

      // Get a sign factor based on particles involved in the coupling
      // - based up Class I
      int sign = 1;
      for (auto const &each_part : particles)
      {
        if (each_part == H0)
          sign *= -(double)sgn(Lam6);
        else if (each_part == A0)
          sign *= (double)sgn(Lam6);
      }

      // Get coupling
      for (auto const &particles_perm : get_neutral_particle_permutations(particles))
      {
        if (is_neutral(p1) && is_neutral(p2) && is_neutral(p3) && is_neutral(p4))
        {
          if (particles_match(particles, {p1, G0, G0, G0}))
            c += get_quartic_coupling_higgs_hG0G0G0(s, q, p1);
          else if (particles_match(particles, {p1, p2, G0, G0}))
            c += get_quartic_coupling_higgs_hhG0G0(s, q, particles_perm);
          else if (particles_match(particles, {p1, p2, p3, G0}))
            c += get_quartic_coupling_higgs_hhhG0(s, q, particles_perm);
          else
            c += get_quartic_coupling_higgs_hhhh(s, q, particles_perm);
        }
        else if (is_neutral(p1) && is_neutral(p2) && !is_neutral(p3) && !is_neutral(p4))
        {
          if (particles_match(particles, {G0, G0, Hp, Hm}))
            c += 0.5 * Lam3;
          else if (particles_match(particles, {p1, G0, Hp, Hm}))
            c += -(q[p1][2] * Lam7 * (double)sgn(Lam6)).imag();
          else if (particles_match(particles, {p1, p2, Hp, Hm}))
            c += get_quartic_coupling_higgs_hhHpHm(s, q, particles_perm);
          else if (particles_match(particles, {p1, p2, Gp, Gm}))
            c += get_quartic_coupling_higgs_hhGpGm(s, q, particles_perm);
          else if (particles_match(particles, {p1, p2, Hp, Gm}))
            c += get_quartic_coupling_higgs_hhGmHp(s, q, particles_perm);
          else if (particles_match(particles, {p1, p2, Hm, Gp}))
            c += std::conj(get_quartic_coupling_higgs_hhGmHp(s, q, particles_perm));
        }
        else if (!is_neutral(p1) && !is_neutral(p2) && !is_neutral(p3) && !is_neutral(p4))
        {
          if (particles_match(particles, {Gp, Gp, Gm, Gm}))
            c += 4.0 * 0.5 * Lam1;
          else if (particles_match(particles, {Hp, Hp, Hm, Hm}))
            c += 4.0 * 0.5 * Lam2;
          else if (particles_match(particles, {Hp, Hm, Gp, Gm}))
            c += 4.0 * (Lam3 + Lam4);
          else if (particles_match(particles, {Hp, Hp, Gm, Gm}))
            c += 0.5 * Lam5;
          else if (particles_match(particles, {Hm, Hm, Gp, Gp}))
            c += std::conj(0.5 * Lam5);
          else if (particles_match(particles, {Hp, Gp, Gm, Gm}))
            c += 2.0 * Lam6;
          else if (particles_match(particles, {Hm, Gp, Gp, Gm}))
            c += 4.0 * std::conj(1.0 * Lam6);
          else if (particles_match(particles, {Hp, Hp, Hm, Gm}))
            c += 2.0 * Lam7;
          else if (particles_match(particles, {Hp, Hm, Hm, Gp}))
            c += 4.0 * std::conj(1.0 * Lam7);
        }
      }

      return -ii * c * (double)sign;
    }

    // puts together a vector of cubic higgs couplings (necessary for NLO unitarity calculation)
    std::vector<complexd> get_cubic_coupling_higgs(const ThdmSpec &s, const bool use_physical_basis)
    {
      const int size = 17;
      vector<complexd> result(size+1,0.);
      
      // couplings calculated using the physical basis
      if (use_physical_basis)
      {
        result[1] = get_cubic_coupling_physical_h0GpGm(s); // h0GpGm
        result[2] = get_cubic_coupling_physical_h0GpGm(s); // h0G0G0
        result[3] = get_cubic_coupling_physical_H0GpGm(s); // H0GpGm
        result[4] = get_cubic_coupling_physical_H0GpGm(s); // H0GpGm
        result[5] = get_cubic_coupling_physical_h0GpHm(s);
        result[6] = get_cubic_coupling_physical_h0G0A0(s);
        result[7] = get_cubic_coupling_physical_H0GpHm(s);
        result[8] = get_cubic_coupling_physical_H0G0A0(s);
        result[9] = get_cubic_coupling_physical_A0GpHm(s);
        result[10] = get_cubic_coupling_physical_h0HpHm(s);
        result[11] = get_cubic_coupling_physical_h0A0A0(s);
        result[12] = get_cubic_coupling_physical_H0HpHm(s);
        result[13] = get_cubic_coupling_physical_H0A0A0(s);
        result[14] = get_cubic_coupling_physical_h0h0h0(s);
        result[15] = get_cubic_coupling_physical_h0h0H0(s);
        result[16] = get_cubic_coupling_physical_h0H0H0(s);
        result[17] = get_cubic_coupling_physical_H0H0H0(s);
      }

      // couplings caluclated using the Higgs basis
      else
      {
        result[1] = get_cubic_coupling_higgs(s,h0,Gp,Gm);
        result[2] = get_cubic_coupling_higgs(s,h0,G0,G0);
        result[3] = get_cubic_coupling_higgs(s,H0,Gp,Gm);
        result[4] = get_cubic_coupling_higgs(s,H0,G0,G0);
        result[5] = get_cubic_coupling_higgs(s,h0,Gp,Hm);
        result[6] = get_cubic_coupling_higgs(s,h0,G0,A0);
        result[7] = get_cubic_coupling_higgs(s,H0,Gp,Hm);
        result[8] = get_cubic_coupling_higgs(s,H0,G0,A0);
        result[9] = get_cubic_coupling_higgs(s,A0,Gp,Hm);
        result[10] = get_cubic_coupling_higgs(s,h0,Hp,Hm);
        result[11] = get_cubic_coupling_higgs(s,h0,A0,A0);
        result[12] = get_cubic_coupling_higgs(s,H0,Hp,Hm);
        result[13] = get_cubic_coupling_higgs(s,H0,A0,A0);
        result[14] = get_cubic_coupling_higgs(s,h0,h0,h0);
        result[15] = get_cubic_coupling_higgs(s,h0,h0,H0);
        result[16] = get_cubic_coupling_higgs(s,h0,H0,H0);
        result[17] = get_cubic_coupling_higgs(s,H0,H0,H0);
        for (int j = 1; j <= size; j++)
          result[j] = -ii * result[j];
      }

      return result;
    }

    // puts together a vector of quartic higgs couplings (necessary for NLO unitarity calculation)
    std::vector<complexd> get_quartic_couplings(const ThdmSpec &s, const bool use_physical_basis)
    {
      const int size = 22;
      vector<complexd> result(size+1,0.);

      // couplings calculated using the physical basis
      if (use_physical_basis)
      {
        result[1] = get_quartic_coupling_physical_h0h0G0G0(s);
        result[2] = get_quartic_coupling_physical_HpHmG0G0(s); // X
        result[3] = get_quartic_coupling_physical_A0A0G0G0(s);
        result[4] = get_quartic_coupling_physical_h0h0G0A0(s);
        result[5] = get_quartic_coupling_physical_H0H0G0A0(s);
        result[6] = get_quartic_coupling_physical_HpHmG0A0(s); // X
        result[7] = get_quartic_coupling_physical_A0A0G0A0(s); // X
        result[8] = 3.0 * get_quartic_coupling_physical_A0A0G0A0(s); // X
        result[9] = get_quartic_coupling_physical_h0h0HpHm(s); // X
        result[10] = get_quartic_coupling_physical_h0h0A0A0(s);
        result[11] = get_quartic_coupling_physical_H0H0HpHm(s);
        result[12] = get_quartic_coupling_physical_H0H0A0A0(s);
        result[13] = get_quartic_coupling_physical_h0H0HpHm(s);
        result[14] = get_quartic_coupling_physical_h0H0A0A0(s);
        result[15] = get_quartic_coupling_physical_h0h0h0h0(s);
        result[16] = get_quartic_coupling_physical_h0h0h0H0(s);
        result[17] = get_quartic_coupling_physical_h0h0H0H0(s);
        result[18] = get_quartic_coupling_physical_h0H0H0H0(s);
        result[19] = get_quartic_coupling_physical_H0H0H0H0(s);
        result[20] = get_quartic_coupling_physical_HpHmHpHm(s);
        result[21] = get_quartic_coupling_physical_HpHmHpHm(s) / 2.0;
        result[22] = 3.0 * get_quartic_coupling_physical_HpHmHpHm(s) / 2.0;
      }

      // couplings caluclated using the Higgs basis
      else
      {
        result[1] = get_quartic_coupling_higgs(s,h0,h0,G0,G0);
        result[2] = get_quartic_coupling_higgs(s,H0,H0,G0,G0);
        result[3] = get_quartic_coupling_higgs(s,Hp,Hm,G0,G0); // X
        result[4] = get_quartic_coupling_higgs(s,A0,A0,G0,G0);
        result[5] = get_quartic_coupling_higgs(s,h0,h0,G0,A0); // differs
        result[6] = get_quartic_coupling_higgs(s,H0,H0,G0,A0); // differs
        result[7] = get_quartic_coupling_higgs(s,Hp,Hm,G0,A0); // X equal if third term in equation is .imag() not .real()
        result[8] = get_quartic_coupling_higgs(s,A0,A0,G0,A0); // X is different by a factor of sign(Lam6)
        result[9] = get_quartic_coupling_higgs(s,h0,h0,Hp,Hm);
        result[10] = get_quartic_coupling_higgs(s,h0,h0,A0,A0);
        result[11] = get_quartic_coupling_higgs(s,H0,H0,Hp,Hm);
        result[12] = get_quartic_coupling_higgs(s,H0,H0,A0,A0);
        result[13] = get_quartic_coupling_higgs(s,h0,H0,Hp,Hm);
        result[14] = get_quartic_coupling_higgs(s,h0,H0,A0,A0);
        result[15] = get_quartic_coupling_higgs(s,h0,h0,h0,h0);
        result[16] = get_quartic_coupling_higgs(s,h0,h0,h0,H0);
        result[17] = get_quartic_coupling_higgs(s,h0,h0,H0,H0);
        result[18] = get_quartic_coupling_higgs(s,h0,H0,H0,H0);
        result[19] = get_quartic_coupling_higgs(s,H0,H0,H0,H0);
        result[20] = get_quartic_coupling_higgs(s,Hp,Hm,Hp,Hm);
        result[21] = get_quartic_coupling_higgs(s,A0,A0,Hp,Hm);
        result[22] = get_quartic_coupling_higgs(s,A0,A0,A0,A0);
        for (int j = 1; j <= size; j++)
          result[j] = -ii * result[j];
      }

      return result;
    }

    ///  ===============================================================
    ///  == functions to fill parameters for NLO unitarity likelihood ==
    ///  ===============================================================

    enum wavefunction_renorm_type
    {
      wpwm,
      zz,
      wpHm,
      Hpwm,
      zA,
      Az,
      hh,
      HH,
      hH,
      Hh,
      HpHm,
      AA,
    };

    // structs for GSL differentiator / integrator

    typedef double(*gsl_funn)(double, void*); 

    struct B0_integration_vars
    {
      double x;
      double p2;
      double m12;
      double m22;
      double mu2;
      double z_plus;
    };
    
    struct wavefunction_renorm_vars
    {
      const ThdmSpec& s;
      const std::vector<complexd>& C3;
      const std::vector<complexd>& C4;
      wavefunction_renorm_vars(const ThdmSpec& s, const std::vector<complexd>& C3, const std::vector<complexd>& C4) : s(s), C3(C3), C4(C4) {}
    };

    // -- Custom functions to extend GSL

    complexd gsl_complex_to_complex_double(const gsl_complex c)
    {
      return complexd(GSL_REAL(c), GSL_IMAG(c));
    }

    complexd gsl_matrix_complex_trace_complex(const gsl_matrix_complex *m1)
    {
      return gsl_complex_to_complex_double(gsl_matrix_complex_get(m1, 0, 0)) +
             gsl_complex_to_complex_double(gsl_matrix_complex_get(m1, 1, 1)) +
             gsl_complex_to_complex_double(gsl_matrix_complex_get(m1, 2, 2));
    }


    // -------------------------------------------------------------------
    // wavefunction corrections to beta functions
    // -------------------------------------------------------------------


    double A0_bar(const double m2)
    {
      const double MZ = 91.15349; // get this from FS
      double mu2 = pow(MZ, 2);
      return m2 * (-log(m2 / mu2) + 1.0);
    }

    double B0_bar_integration_real(const double x, const B0_integration_vars* p)
    {
      double re = (p->p2 * x * x - x * (p->p2 - p->m12 - p->m22) + p->m22) / p->mu2;
      double im = -p->z_plus / p->mu2;
      return log(sqrt(re * re + im * im));
    }

    double B0_bar_integration_imag(const double x, const B0_integration_vars* p)
    {
      double re = (p->p2 * x * x - x * (p->p2 - p->m12 - p->m22) + p->m22) / p->mu2;
      double im = -p->z_plus / p->mu2;
      return atan(im / re);
    }

    complexd B0_bar(const double p2, const double m12, const double m22)
    {
      const double MZ = 91.15349; // get this from FS
      double mu2 = pow(MZ, 2);
      double z_plus = 1E-10;
      double result_real, error_real, result_imag, error_imag;
      // real
      gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);
      gsl_function B0_bar_int;
      B0_bar_int.function = reinterpret_cast<gsl_funn>(&B0_bar_integration_real);
      B0_integration_vars input_pars;
      input_pars.p2 = p2;
      input_pars.m12 = m12;
      input_pars.m22 = m22;
      input_pars.mu2 = mu2;
      input_pars.z_plus = z_plus;
      B0_bar_int.params = &input_pars;
      gsl_integration_qag(&B0_bar_int, 0, 1.0, 1e-7, 1e-7, 1000, 1, w, &result_real, &error_real);
      gsl_integration_workspace_free(w);
      // imag
      gsl_integration_workspace *w_imag = gsl_integration_workspace_alloc(1000);
      gsl_function B0_bar_int_imag;
      B0_bar_int_imag.function = reinterpret_cast<gsl_funn>(&B0_bar_integration_imag);
      B0_bar_int_imag.params = &input_pars;
      gsl_integration_qag(&B0_bar_int_imag, 0, 1.0, 1e-7, 1e-7, 1000, 1, w_imag, &result_imag, &error_imag);
      gsl_integration_workspace_free(w_imag);

      return (result_real + ii * result_imag);
    }

    double mZw2(const ThdmSpec &s)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), sb = sin(s.beta), cb = cos(s.beta), s2b2a = sin(2.0 * s.beta - 2.0 * s.alpha), t2b = tan(2.0 * s.beta);
      return 1.0 / 2.0 * (mh2 * sqr(s.sinba) + mH2 * sqr(s.cosba) + (mh2 - mH2) * s2b2a * (1.0 / t2b) - 2.0 * s.m122 * (1.0 / sb) * (1.0 / cb));
    }

    double Z_w(const ThdmSpec &s, const std::vector<complexd>& C3, const std::vector<complexd>& C4); // Necessary forward declaration


    // -- Self energies & wavefunction renormalizations


    complexd Pi_tilde_wpwm(const double p2, const ThdmSpec &s, const std::vector<complexd>& C3, const std::vector<complexd>& )
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      complexd Pi = sqr(C3[1]) * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += sqr(C3[3]) * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += sqr(C3[5]) * (B0_bar(p2, mC2, mh2) - B0_bar(0., mC2, mh2));
      Pi += sqr(C3[7]) * (B0_bar(p2, mC2, mH2) - B0_bar(0., mC2, mH2));
      Pi += C3[9] * std::conj(C3[9]) * (B0_bar(p2, mC2, mA2) - B0_bar(0., mC2, mA2));
      return -1.0 / (16.0 * sqr(pi)) * Pi;
    }

    complexd Pi_tilde_zz(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>&)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA);
      complexd Pi = sqr(C3[2]) * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += sqr(C3[4]) * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += sqr(C3[6]) * (B0_bar(p2, mA2, mh2) - B0_bar(0., mA2, mh2));
      Pi += sqr(C3[8]) * (B0_bar(p2, mA2, mH2) - B0_bar(0., mA2, mH2));
      return -1.0 / (16.0 * sqr(pi)) * Pi;
    }

    complexd Pi_tilde_wpHm(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>&)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mC2 = sqr(s.mHp);
      complexd Pi = C3[1] * C3[5] * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += C3[3] * C3[7] * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += C3[5] * C3[10] * (B0_bar(p2, mC2, mh2) - B0_bar(0., mC2, mh2));
      Pi += C3[7] * C3[12] * (B0_bar(p2, mC2, mH2) - B0_bar(0., mC2, mH2));
      return -1.0 / (16.0 * sqr(pi)) * Pi;
    }

    complexd Pi_tilde_zA(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>&)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA);
      complexd Pi = C3[2] * C3[6] * (B0_bar(p2, 0., mh2) - B0_bar(0., 0., mh2));
      Pi += C3[4] * C3[8] * (B0_bar(p2, 0., mH2) - B0_bar(0., 0., mH2));
      Pi += C3[6] * C3[11] * (B0_bar(p2, mA2, mh2) - B0_bar(0., mA2, mh2));
      Pi += C3[8] * C3[13] * (B0_bar(p2, mA2, mH2) - B0_bar(0., mA2, mH2));
      return -1.0 / (16.0 * sqr(pi)) * Pi;
    }

    complexd Pi_zz(const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (C4[1] * A0_bar(mh2) + C4[2] * A0_bar(mH2) + 2.0 * C4[3] * A0_bar(mC2) + C4[4] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[2]) * B0_bar(0., 0., mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[4]) * B0_bar(0., 0., mH2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[6]) * B0_bar(0., mA2, mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[8]) * B0_bar(0., mA2, mH2);
      return Pi;
    }

    complexd Pi_zA(const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (C4[5] * A0_bar(mh2) + C4[6] * A0_bar(mH2) + 2.0 * C4[7] * A0_bar(mC2) + C4[8] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * sqr(pi)) * C3[2] * C3[6] * B0_bar(0., 0., mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * C3[4] * C3[8] * B0_bar(0., 0., mH2);
      Pi += -1.0 / (16.0 * sqr(pi)) * C3[6] * C3[11] * B0_bar(0., mA2, mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * C3[8] * C3[13] * B0_bar(0., mA2, mH2);
      return Pi;
    }

    complexd Pi_tilde_hh(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      const double sba = sin(s.beta - s.alpha), cba = abs(cos(s.beta - s.alpha));
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (2.0 * C4[9] * A0_bar(mC2) + C4[10] * A0_bar(mA2) + C4[15] * A0_bar(mh2) + C4[17] * A0_bar(mH2));
      Pi += -1.0 / (32.0 * sqr(pi)) * (2.0 * sqr(C3[1]) + sqr(C3[2])) * B0_bar(p2, 0, 0);
      Pi += -1.0 / (32.0 * sqr(pi)) * 4.0 * sqr(C3[5]) * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[6]) * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[10]) * B0_bar(p2, mC2, mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[11]) * B0_bar(p2, mA2, mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[14]) * B0_bar(p2, mh2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[15]) * B0_bar(p2, mH2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[16]) * B0_bar(p2, mH2, mH2);
      Pi += -sqr(sba) * Pi_zz(s,C3,C4) - 2.0 * sba * cba * Pi_zA(s,C3,C4) + (Z_w(s,C3,C4) - 1.0) * (mh2 + mZw2(s) * sqr(cba));
      return Pi;
    }

    complexd Pi_tilde_HH(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      const double sba = sin(s.beta - s.alpha), cba = abs(cos(s.beta - s.alpha));
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (2.0 * C4[11] * A0_bar(mC2) + C4[12] * A0_bar(mA2) + C4[17] * A0_bar(mh2) + C4[19] * A0_bar(mH2));
      Pi += -1.0 / (32.0 * sqr(pi)) * (2.0 * sqr(C3[3]) + sqr(C3[4])) * B0_bar(p2, 0, 0);
      Pi += -1.0 / (32.0 * sqr(pi)) * 4.0 * sqr(C3[7]) * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[8]) * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[12]) * B0_bar(p2, mC2, mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[13]) * B0_bar(p2, mA2, mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[15]) * B0_bar(p2, mh2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * sqr(C3[16]) * B0_bar(p2, mH2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * sqr(C3[17]) * B0_bar(p2, mH2, mH2);
      Pi += -sqr(cba) * Pi_zz(s,C3,C4) + 2.0 * sba * cba * Pi_zA(s,C3,C4) + (Z_w(s,C3,C4) - 1.0) * (mH2 + mZw2(s) * sqr(sba));
      return Pi;
    }

    complexd Pi_tilde_hH(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      const double sba = sin(s.beta - s.alpha), cba = abs(cos(s.beta - s.alpha));
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (2.0 * C4[13] * A0_bar(mC2) + C4[14] * A0_bar(mA2) + C4[16] * A0_bar(mh2) + C4[18] * A0_bar(mH2));
      Pi += -1.0 / (32.0 * sqr(pi)) * (2.0 * C3[1] * C3[3] + C3[2] * C3[4]) * B0_bar(p2, 0, 0);
      Pi += -1.0 / (32.0 * sqr(pi)) * 4.0 * C3[5] * C3[7] * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * C3[6] * C3[8] * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * C3[10] * C3[12] * B0_bar(p2, mC2, mC2);
      Pi += -1.0 / (32.0 * sqr(pi)) * C3[11] * C3[13] * B0_bar(p2, mA2, mA2);
      Pi += -1.0 / (32.0 * sqr(pi)) * C3[14] * C3[15] * B0_bar(p2, mh2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * 2.0 * C3[15] * C3[16] * B0_bar(p2, mH2, mh2);
      Pi += -1.0 / (32.0 * sqr(pi)) * C3[16] * C3[17] * B0_bar(p2, mH2, mH2);
      Pi += -sba * cba * Pi_zz(s,C3,C4) - (sqr(cba) - sqr(sba)) * Pi_zA(s,C3,C4) - (Z_w(s,C3,C4) - 1.0) * (mZw2(s) * sba * cba);
      return Pi;
    }

    complexd Pi_tilde_HpHm(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (C4[9] * A0_bar(mh2) + C4[11] * A0_bar(mH2) + 2.0 * C4[20] * A0_bar(mC2) + C4[21] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[5]) * B0_bar(p2, 0., mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[7]) * B0_bar(p2, 0., mH2);
      Pi += -1.0 / (16.0 * sqr(pi)) * std::conj(C3[9]) * C3[9] * B0_bar(p2, 0., mA2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[10]) * B0_bar(p2, mC2, mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[12]) * B0_bar(p2, mC2, mH2);
      Pi += (Z_w(s,C3,C4) - 1.0) * (mC2 + mZw2(s));
      return Pi;
    }

    complexd Pi_tilde_AA(const double p2, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      const double mh2 = sqr(s.mh), mH2 = sqr(s.mH), mA2 = sqr(s.mA), mC2 = sqr(s.mHp);
      complexd Pi = 1.0 / (32.0 * sqr(pi)) * (C4[10] * A0_bar(mh2) + C4[12] * A0_bar(mH2) + 2.0 * C4[21] * A0_bar(mC2) + C4[22] * A0_bar(mA2));
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[6]) * B0_bar(p2, 0., mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[8]) * B0_bar(p2, 0., mH2);
      Pi += -1.0 / (16.0 * sqr(pi)) * 2.0 * std::conj(C3[9]) * C3[9] * B0_bar(p2, 0., mC2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[11]) * B0_bar(p2, mA2, mh2);
      Pi += -1.0 / (16.0 * sqr(pi)) * sqr(C3[13]) * B0_bar(p2, mA2, mH2);
      Pi += (Z_w(s,C3,C4) - 1.0) * (mA2 + mZw2(s));
      return Pi;
    }

    double Pi_tilde_wpwm_re(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_wpwm(p2, p->s, p->C3, p->C4).real(); }
    double Pi_tilde_wpwm_im(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_wpwm(p2, p->s, p->C3, p->C4).imag(); }
    double Pi_tilde_zz_re(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_zz(p2, p->s, p->C3, p->C4).real(); }
    double Pi_tilde_zz_im(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_zz(p2, p->s, p->C3, p->C4).imag(); }
    double Pi_tilde_hh_re(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_hh(p2, p->s, p->C3, p->C4).real(); }
    double Pi_tilde_hh_im(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_hh(p2, p->s, p->C3, p->C4).imag(); }
    double Pi_tilde_HH_re(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_HH(p2, p->s, p->C3, p->C4).real(); }
    double Pi_tilde_HH_im(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_HH(p2, p->s, p->C3, p->C4).imag(); }
    double Pi_tilde_HpHm_re(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_HpHm(p2, p->s, p->C3, p->C4).real(); }
    double Pi_tilde_HpHm_im(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_HpHm(p2, p->s, p->C3, p->C4).imag(); }
    double Pi_tilde_AA_re(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_AA(p2, p->s, p->C3, p->C4).real(); }
    double Pi_tilde_AA_im(double p2, const wavefunction_renorm_vars* p) { return Pi_tilde_AA(p2, p->s, p->C3, p->C4).imag(); }

    complexd z_ii(const wavefunction_renorm_type type, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      wavefunction_renorm_vars params { s, C3, C4 };
      gsl_function F_re;
      gsl_function F_im;
      F_re.params = &params;
      F_im.params = &params;
      double result_re, result_im, abserr_re, abserr_im;
      double m_in = 0.0;

      switch (type)
      {
      case wpwm:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_wpwm_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_wpwm_im);
        m_in = s.mGp;
        break;
      case zz:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_zz_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_zz_im);
        m_in = s.mG;
        break;
      case hh:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_hh_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_hh_im);
        m_in = s.mh;
        break;
      case HH:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_HH_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_HH_im);
        m_in = s.mH;
        break;
      case HpHm:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_HpHm_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_HpHm_im);
        m_in = s.mHp;
        break;
      case AA:
        F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_AA_re);
        F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_AA_im);
        m_in = s.mA;
        break;
      default:
        std::cerr << "WARNING: Unrecognized wavefunction renormalization particle pair sent to z_ij function. Returning 0." << std::endl;
        return 0.0;
      }
      gsl_deriv_central(&F_re, pow(m_in, 2), 1e-8, &result_re, &abserr_re);
      gsl_deriv_central(&F_im, pow(m_in, 2), 1e-8, &result_im, &abserr_im);
      const complexd Z_ii = 1.0 + 0.5 * (result_re + ii * result_im);
      return 16.0 * sqr(pi) * (Z_ii - 1.0);
    }

    complexd z_ij(const wavefunction_renorm_type type, const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      complexd z_ij = 0.0;
      double m1 = 0.0, m2 = 0.0;

      switch (type)
      {
      case wpHm:
        m1 = s.mGp;
        m2 = s.mHp;
        z_ij = Pi_tilde_wpHm(m1, s, C3, C4);
        break;
      case zA:
        m1 = s.mG;
        m2 = s.mA;
        z_ij = Pi_tilde_zA(m1, s, C3, C4);
        break;
      case hH:
        m1 = s.mh;
        m2 = s.mH;
        z_ij = Pi_tilde_hH(m1, s, C3, C4);
        break;
      case Hpwm:
        m1 = s.mHp;
        m2 = s.mGp;
        z_ij = Pi_tilde_wpHm(m1, s, C3, C4);
        break;
      case Az:
        m1 = s.mA;
        m2 = s.mG;
        z_ij = Pi_tilde_zA(m1, s, C3, C4);
        break;
      case Hh:
        m1 = s.mH;
        m2 = s.mh;
        z_ij = Pi_tilde_hH(m1, s, C3, C4);
        break;
      default:
        z_ij = z_ii(type, s, C3, C4);
        return z_ij;
      }
      return 16.0 * sqr(pi) * z_ij / (pow(m1, 2) - pow(m2, 2));
    }

    double Z_w(const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4)
    {
      wavefunction_renorm_vars params { s, C3, C4 };
      gsl_function F_re, F_im;
      F_re.params = &params;
      F_im.params = &params;
      F_re.function = reinterpret_cast<gsl_funn>(&Pi_tilde_wpwm_re);
      F_im.function = reinterpret_cast<gsl_funn>(&Pi_tilde_wpwm_im);
      double result_re, abserr_re, result_im, abserr_im;
      double m_in = 0.0;
      gsl_deriv_central(&F_re, m_in, 1e-8, &result_re, &abserr_re);
      gsl_deriv_central(&F_im, m_in, 1e-8, &result_im, &abserr_im);
      return 1.0 + 0.5 * (result_re + result_im);
    }


    // -------------------------------------------------------------------
    // LO beta functions for lambdas
    // -------------------------------------------------------------------


    // UNUSED
    // gets Yukawa traces required for LO corrections to lambdai beta functions
    //- easily extendable to Yukawas with off-diagonals
    std::map<str, complexd> get_traces_of_y(const ThdmSpec &s)
    {
      complexd tr_u2, tr_d2, tr_l2, tr_u4, tr_d4, tr_l4, tr_du;
      gsl_matrix_complex *y_u, *y_d, *y_l, *y_u_dagger, *y_d_dagger, *y_l_dagger;
      const int size = 3;

      y_u = gsl_matrix_complex_alloc(size, size);
      y_d = gsl_matrix_complex_alloc(size, size);
      y_l = gsl_matrix_complex_alloc(size, size);
      y_u_dagger = gsl_matrix_complex_alloc(size, size);
      y_d_dagger = gsl_matrix_complex_alloc(size, size);
      y_l_dagger = gsl_matrix_complex_alloc(size, size);

      // set yukawa - up
      gsl_complex y_u_11;
      GSL_SET_REAL(&y_u_11, s.Yu[0]);
      GSL_SET_IMAG(&y_u_11, 0.0);

      gsl_complex y_u_22;
      GSL_SET_REAL(&y_u_22, s.Yu[1]);
      GSL_SET_IMAG(&y_u_22, 0.0);

      gsl_complex y_u_33;
      GSL_SET_REAL(&y_u_33, s.Yu[2]);
      GSL_SET_IMAG(&y_u_33, 0.0);

      gsl_matrix_complex_set_zero(y_u);

      gsl_matrix_complex_set(y_u, 0, 0, y_u_11);
      gsl_matrix_complex_set(y_u, 1, 1, y_u_22);
      gsl_matrix_complex_set(y_u, 2, 2, y_u_33);

      // take dagger -> all components currently real so no need to conjugate
      gsl_matrix_complex_transpose_memcpy(y_u_dagger, y_u);

      // set yukawa - down
      gsl_complex y_d_11;
      GSL_SET_REAL(&y_d_11, s.Yd[0]);
      GSL_SET_IMAG(&y_d_11, 0.0);

      gsl_complex y_d_22;
      GSL_SET_REAL(&y_d_22, s.Yd[1]);
      GSL_SET_IMAG(&y_d_22, 0.0);

      gsl_complex y_d_33;
      GSL_SET_REAL(&y_d_33, s.Yd[2]);
      GSL_SET_IMAG(&y_d_33, 0.0);

      gsl_matrix_complex_set_zero(y_d);

      gsl_matrix_complex_set(y_d, 0, 0, y_d_11);
      gsl_matrix_complex_set(y_d, 1, 1, y_d_22);
      gsl_matrix_complex_set(y_d, 2, 2, y_d_33);

      // take dagger -> all components currently real so no need to conjugate
      gsl_matrix_complex_transpose_memcpy(y_d_dagger, y_d);

      // set yukawa - lepton
      gsl_complex y_l_11;
      GSL_SET_REAL(&y_l_11, s.Ye[0]);
      GSL_SET_IMAG(&y_l_11, 0.0);

      gsl_complex y_l_22;
      GSL_SET_REAL(&y_l_22, s.Ye[1]);
      GSL_SET_IMAG(&y_l_22, 0.0);

      gsl_complex y_l_33;
      GSL_SET_REAL(&y_l_33, s.Ye[2]);
      GSL_SET_IMAG(&y_l_33, 0.0);

      gsl_matrix_complex_set_zero(y_l);

      gsl_matrix_complex_set(y_l, 0, 0, y_l_11);
      gsl_matrix_complex_set(y_l, 1, 1, y_l_22);
      gsl_matrix_complex_set(y_l, 2, 2, y_l_33);

      // take dagger -> all components currently real so no need to conjugate
      gsl_matrix_complex_transpose_memcpy(y_l_dagger, y_l);

      //calculate traces - up
      gsl_matrix_complex *y_u2;
      gsl_matrix_complex *y_u4;
      y_u2 = gsl_matrix_complex_alloc(size, size);
      y_u4 = gsl_matrix_complex_alloc(size, size);

      gsl_matrix_complex_memcpy(y_u2, y_u);
      gsl_matrix_complex_mul_elements(y_u2, y_u_dagger);
      tr_u2 = gsl_matrix_complex_trace_complex(y_u2);

      gsl_matrix_complex_memcpy(y_u4, y_u2);
      gsl_matrix_complex_mul_elements(y_u4, y_u2);
      tr_d4 = gsl_matrix_complex_trace_complex(y_u4);

      //calculate traces - down
      gsl_matrix_complex *y_d2;
      gsl_matrix_complex *y_d4;
      y_d2 = gsl_matrix_complex_alloc(size, size);
      y_d4 = gsl_matrix_complex_alloc(size, size);

      gsl_matrix_complex_memcpy(y_d2, y_d);
      gsl_matrix_complex_mul_elements(y_d2, y_d_dagger);
      tr_d2 = gsl_matrix_complex_trace_complex(y_d2);

      gsl_matrix_complex_memcpy(y_d4, y_d2);
      gsl_matrix_complex_mul_elements(y_d4, y_d2);
      tr_d4 = gsl_matrix_complex_trace_complex(y_d4);

      // calculate trace for down*up
      gsl_matrix_complex_mul_elements(y_d2, y_u2);
      tr_du = gsl_matrix_complex_trace_complex(y_d2);

      gsl_matrix_complex_free(y_d2);
      gsl_matrix_complex_free(y_u2);
      gsl_matrix_complex_free(y_d4);
      gsl_matrix_complex_free(y_u4);

      //calculate traces - lepton
      gsl_matrix_complex *y_l2;
      y_l2 = gsl_matrix_complex_alloc(size, size);
      gsl_matrix_complex_memcpy(y_l2, y_l);

      gsl_matrix_complex_mul_elements(y_l2, y_l_dagger);
      tr_l2 = gsl_matrix_complex_trace_complex(y_l2);

      gsl_matrix_complex_mul_elements(y_l2, y_l2); // y_l^2 is now y_l^4
      tr_l4 = gsl_matrix_complex_trace_complex(y_l2);

      gsl_matrix_complex_free(y_l2);

      gsl_matrix_complex_free(y_u);
      gsl_matrix_complex_free(y_d);
      gsl_matrix_complex_free(y_l);
      gsl_matrix_complex_free(y_u_dagger);
      gsl_matrix_complex_free(y_d_dagger);
      gsl_matrix_complex_free(y_l_dagger);

      return {{"tr_u2", tr_u2},
              {"tr_d2", tr_d2},
              {"tr_l2", tr_l2},
              {"tr_u4", tr_u4},
              {"tr_d4", tr_d4},
              {"tr_l4", tr_l4},
              {"tr_du", tr_du}};
    }

    // returns model specific coeffiecients (a_i) to Yukawa terms
    // appearing in the LO corrections to lambdai beta functions
    // see Nucl.Phys.B 262 (1985) 517-537
    vector<double> get_alphas_for_type(const int type)
    {
      switch (type)
      {
      case 1:
        return {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1};
      case 2:
        return {0,1,1,0,1,1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1};
      case 3:
        return {0,1,0,0,1,0,0,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1};
      case 4:
        return {0,0,1,0,0,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1};
      case -1:
        return {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
      default:
        return {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
      }
    }

    // gets Yukawa traces required for LO corrections to lambdai beta functions
    double get_tr_pow(const vector<double>& Yuk, const int pow_N)
    {
      double tr = 0.0;
      for (int i = 0; i < 3; i++)
      {
        tr += pow(Yuk[i], pow_N);
      }
      return tr;
    }

    // gets Yukawa traces required for LO corrections to lambdai beta functions
    double get_tr_dduu(const ThdmSpec &s)
    {
      double tr = 0.0;
      for (int i = 0; i < 3; i++)
      {
        tr += sqr(s.Yd[i]*s.Yu[i]);
      }
      return tr;
    }

    // LO beta function for lambda1
    complexd beta_one(const ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      vector<double> a = get_alphas_for_type(s.model_type);
      const complexd tr_u2 = get_tr_pow(s.Yu, 2), tr_d2 = get_tr_pow(s.Yd, 2), tr_l2 = get_tr_pow(s.Ye, 2);
      const complexd tr_u4 = get_tr_pow(s.Yu, 4), tr_d4 = get_tr_pow(s.Yd, 4), tr_l4 = get_tr_pow(s.Ye, 4);
      complexd beta = 12.0 * pow(s.lam1, 2) + 4.0 * pow(s.lam3, 2) + 4.0 * s.lam3 * s.lam4 + 2.0 * pow(s.lam4, 2) + 2.0 * pow(s.lam5, 2);
      if (gauge_correction)
        beta += 3.0 / 4.0 * pow(s.g1, 4) + 3.0 / 2.0 * sqr(s.g1*s.g2) + 9.0 / 4.0 * pow(s.g2, 4) - 3.0 * sqr(s.g1) * s.lam1 - 9.0 * sqr(s.g2) * s.lam1;
      if (yukawa_correction)
        beta += 4.0 * s.lam1 * (a[1] * tr_l2 + 3.0 * a[2] * tr_d2 + 3.0 * a[3] * tr_u2) - 4.0 * (a[4] * tr_l4 + 3.0 * a[5] * tr_d4 + 3.0 * a[6] * tr_u4);
      return 1.0 / (16.0 * sqr(pi)) * (beta);
    }

    // LO beta function for lambda2
    complexd beta_two(const ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      const vector<double> a = get_alphas_for_type(s.model_type);
      const complexd tr_u2 = get_tr_pow(s.Yu, 2), tr_d2 = get_tr_pow(s.Yd, 2), tr_l2 = get_tr_pow(s.Ye, 2);
      const complexd tr_u4 = get_tr_pow(s.Yu, 4), tr_d4 = get_tr_pow(s.Yd, 4), tr_l4 = get_tr_pow(s.Ye, 4);
      complexd beta = 12.0 * pow(s.lam2, 2) + 4.0 * pow(s.lam3, 2) + 4.0 * s.lam3 * s.lam4 + 2.0 * pow(s.lam4, 2) + 2.0 * pow(s.lam5, 2);
      if (gauge_correction)
        beta += 3.0 / 4.0 * pow(s.g1, 4) + 3.0 / 2.0 * sqr(s.g1*s.g2) + 9.0 / 4.0 * pow(s.g2, 4) - 3.0 * sqr(s.g1) * s.lam2 - 9.0 * sqr(s.g2) * s.lam2;
      if (yukawa_correction)
        beta += 4.0 * s.lam2 * (a[7] * tr_l2 + 3.0 * a[8] * tr_d2 + 3.0 * a[9] * tr_u2) - 4.0 * (a[10] * tr_l4 + 3.0 * a[11] * tr_d4 + 3.0 * a[12] * tr_u4);
      return 1.0 / (16.0 * sqr(pi)) * beta;
    }

    // LO beta function for lambda3
    complexd beta_three(const ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      const vector<double> a = get_alphas_for_type(s.model_type);
      const complexd tr_u2 = get_tr_pow(s.Yu, 2), tr_d2 = get_tr_pow(s.Yd, 2), tr_l2 = get_tr_pow(s.Ye, 2);
      const complexd tr_du = get_tr_dduu(s);
      complexd beta = 4.0 * pow(s.lam3, 2) + 2.0 * pow(s.lam4, 2) + (s.lam1 + s.lam2) * (6.0 * s.lam3 + 2.0 * s.lam4) + 2.0 * pow(s.lam5, 2);
      if (gauge_correction)
        beta += -3.0 * s.lam3 * (3.0 * sqr(s.g2) + sqr(s.g1)) + 9.0 / 4.0 * pow(s.g2, 4) + 3.0 / 4.0 * pow(s.g1, 4) - 3.0 / 2.0 * sqr(s.g1*s.g2);
      if (yukawa_correction)
        beta += 2 * s.lam3 * (a[13] * tr_l2 + 3.0 * a[14] * tr_d2 + 3.0 * a[15] * tr_u2) - 12.0 * a[16] * tr_du;
      return 1.0 / (16.0 * sqr(pi)) * beta;
    }

    // LO beta function for lambda4
    complexd beta_four(const ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      const vector<double> a = get_alphas_for_type(s.model_type);
      const complexd tr_u2 = get_tr_pow(s.Yu, 2), tr_d2 = get_tr_pow(s.Yd, 2), tr_l2 = get_tr_pow(s.Ye, 2);
      const complexd tr_du = get_tr_dduu(s);
      complexd beta = (2.0 * s.lam1 + 2.0 * s.lam2 + 8.0 * s.lam3) * s.lam4 + 4.0 * pow(s.lam4, 2) + 8.0 * pow(s.lam5, 2);
      if (gauge_correction)
        beta += -3.0 * s.lam4 * (3.0 * sqr(s.g2) + sqr(s.g1)) + 3.0 * sqr(s.g1*s.g2);
      if (yukawa_correction)
        beta += 2.0 * s.lam4 * (a[17] * tr_l2 + 3.0 * a[18] * tr_d2 + 3.0 * a[19] * tr_u2) + 12.0 * a[20] * tr_du;
      return 1.0 / (16.0 * sqr(pi)) * beta;
    }

    // LO beta function for lambda5
    complexd beta_five(const ThdmSpec &s, const bool gauge_correction, const bool yukawa_correction)
    {
      const vector<double> a = get_alphas_for_type(s.model_type);
      const complexd tr_u2 = get_tr_pow(s.Yu, 2), tr_d2 = get_tr_pow(s.Yd, 2), tr_l2 = get_tr_pow(s.Ye, 2);
      complexd beta = (2.0 * s.lam1 + 2.0 * s.lam2 + 8.0 * s.lam3 + 12.0 * s.lam4) * s.lam5;
      if (gauge_correction)
        beta += -3.0 * s.lam5 * (3.0 * sqr(s.g2) + sqr(s.g1));
      if (yukawa_correction)
        beta += 2.0 * s.lam5 * (a[21] * tr_l2 + 3.0 * a[22] * tr_d2 + 3.0 * a[23] * tr_u2);
      return 1.0 / (16.0 * sqr(pi)) * beta;
    }

    // put everything together to get the NLO unitarity scattering eigenvalues
    vector<complexd> get_NLO_scattering_eigenvalues(const ThdmSpec &s, const vector<complexd>& C3, const vector<complexd>& C4, const bool wave_function_corrections, const bool gauge_corrections, const bool yukawa_corrections)
    {
      // ensure that we have a Z2-symmetric scalar sector
      check_Z2(s.lam6, s.lam7, "get_NLO_unitarity_LogLikelihood_THDM");

      double c2a = cos(2.0 * s.alpha), c2b = cos(2.0 * s.beta), s2a = sin(2.0 * s.alpha), s2b = sin(2.0 * s.beta);

      // calculate LO beta functions
      const complexd b_one = beta_one(s, gauge_corrections, yukawa_corrections);
      const complexd b_two = beta_two(s, gauge_corrections, yukawa_corrections);
      const complexd b_three = beta_three(s, gauge_corrections, yukawa_corrections);
      const complexd b_four = beta_four(s, gauge_corrections, yukawa_corrections);
      const complexd b_five = beta_five(s, gauge_corrections, yukawa_corrections);

      // wavefunction functions
      complexd zij_wpwm, zij_zz, zij_Hpwm, zij_Az, zij_hh, zij_HH, zij_hH, zij_Hh, zij_HpHm, zij_AA;
      complexd B1_z, B2_z, B3_z, B20_z, B21_z, B22_z;
      if (wave_function_corrections)
      {
        zij_wpwm = z_ij(wpwm, s, C3, C4);
        zij_zz = z_ij(zz, s, C3, C4);
        zij_Hpwm = z_ij(Hpwm, s, C3, C4);
        zij_Az = z_ij(Az, s, C3, C4);
        zij_hh = z_ij(hh, s, C3, C4);
        zij_HH = z_ij(HH, s, C3, C4);
        zij_hH = z_ij(hH, s, C3, C4);
        zij_Hh = z_ij(Hh, s, C3, C4);
        zij_HpHm = z_ij(HpHm, s, C3, C4);
        zij_AA = z_ij(AA, s, C3, C4);
      }

      complexd B1 = -3.0 * s.lam1 + (9.0 / 2.0) * b_one + 1.0 / (16.0 * sqr(pi)) * (ii * pi - 1.) * (9.0 * pow(s.lam1, 2) + pow((2.0 * s.lam3 + s.lam4), 2));
      if (wave_function_corrections)
      {
        B1_z = 1.0 / (16.0 * sqr(pi)) * (zij_AA + zij_hh + 2.0 * zij_HpHm + zij_HH + 2.0 * zij_wpwm + zij_zz - (zij_HH - zij_hh) * c2a);
        B1_z += 1.0 / (16.0 * sqr(pi)) * ((2.0 * zij_wpwm - 2.0 * zij_HpHm + zij_zz - zij_AA) * c2b - (zij_Hh + zij_hH) * s2a - (2.0 * zij_Hpwm + zij_Az) * s2b);
        B1 += -3.0 / 2.0 * s.lam1 * B1_z;
      }

      complexd B2 = -3.0 * s.lam2 + (9.0 / 2.0) * b_two + 1.0 / (16.0 * sqr(pi)) * (ii * pi - 1.) * (9.0 * pow(s.lam2, 2) + pow((2.0 * s.lam3 + s.lam4), 2));
      if (wave_function_corrections)
      {
        B2_z = 1.0 / (16.0 * sqr(pi)) * (zij_AA + zij_hh + 2.0 * zij_HpHm + zij_HH + 2.0 * zij_wpwm + zij_zz - (zij_HH - zij_hh) * c2a);
        B2_z += 1.0 / (16.0 * sqr(pi)) * (-(2.0 * zij_wpwm - 2.0 * zij_HpHm + zij_zz - zij_AA) * c2b + (zij_Hh + zij_hH) * s2a + (2.0 * zij_Hpwm + zij_Az) * s2b);
        B2 += -3.0 / 2.0 * s.lam2 * B2_z;
      }

      complexd B3 = -(2.0 * s.lam3 + s.lam4) + (3.0 / 2.0) * (2.0 * b_three + b_four) + 3.0 / (16.0 * sqr(pi)) * (ii * pi - 1.) * (s.lam1 + s.lam2) * (2.0 * s.lam3 + s.lam4);
      if (wave_function_corrections)
      {
        complexd B3_z = 1.0 / (16.0 * sqr(pi)) * (zij_AA + zij_hh + 2.0 * zij_HpHm + zij_HH + 2.0 * zij_wpwm + zij_zz);
        B3 += -1.0 / 2.0 * (2.0 * s.lam3 + s.lam4) * B3_z;
      }

      complexd B4 = -(s.lam3 + 2.0 * s.lam4) + (3.0 / 2.0) * (b_three + 2.0 * b_four) + (1.0 / (16.0 * sqr(pi))) * (ii * pi - 1.) * (pow(s.lam3, 2) + 4.0 * s.lam3 * s.lam4 + 4.0 * pow(s.lam4, 2) + 9.0 * pow(s.lam5, 2));
      if (wave_function_corrections)
      {
        B4 += -1.0 / 2.0 * (s.lam3 + s.lam4 + s.lam5) * B3_z;
      }

      complexd B6 = -3.0 * s.lam5 + (9.0 / 2.0) * b_five + (6.0 / (16.0 * sqr(pi))) * (ii * pi - 1.) * (s.lam3 + 2.0 * s.lam4) * s.lam5;
      if (wave_function_corrections)
      {
        B6 += -1.0 / 2.0 * (s.lam4 + 2.0 * s.lam5) * B3_z;
      }

      complexd B7 = -s.lam1 + (3.0 / 2.0) * b_one + 1.0 / (16.0 * sqr(pi)) * (ii * pi - 1.) * (pow(s.lam1, 2) + pow(s.lam4, 2));
      if (wave_function_corrections)
      {
        B7 += -1.0 / 2.0 * s.lam1 * B1_z;
      }

      complexd B8 = -s.lam2 + (3.0 / 2.0) * b_two + 1.0 / (16.0 * sqr(pi)) * (ii * pi - 1.) * (pow(s.lam2, 2) + pow(s.lam4, 2));
      if (wave_function_corrections)
      {
        B8 += -1.0 / 2.0 * s.lam2 * B2_z;
      }

      complexd B9 = -s.lam4 + (3.0 / 2.0) * b_four + 1.0 / (16.0 * sqr(pi)) * (ii * pi - 1.) * (s.lam1 + s.lam2) * s.lam4;
      if (wave_function_corrections)
      {
        B9 += -1.0 / 2.0 * s.lam4 * B3_z;
      }

      complexd B13 = -s.lam3 + (3.0 / 2.0) * b_three + (1.0 / (16.0 * sqr(pi))) * (ii * pi - 1.) * (pow(s.lam3, 2) + pow(s.lam5, 2));
      if (wave_function_corrections)
      {
        B13 += -1.0 / 2.0 * (s.lam3 + s.lam4 + s.lam5) * B3_z;
      }

      complexd B15 = -s.lam5 + (3.0 / 2.0) * b_five + (2.0 / (16.0 * sqr(pi))) * (ii * pi - 1.) * s.lam3 * s.lam5;
      if (wave_function_corrections)
      {
        B15 += -1.0 / 2.0 * (s.lam4 - 2.0 * s.lam5) * B3_z;
      }

      complexd B19 = -(s.lam3 - s.lam4) + (3.0 / 2.0) * (b_three - b_four) + (1.0 / (16.0 * sqr(pi))) * (ii * pi - 1.) * pow((s.lam3 - s.lam4), 2);
      if (wave_function_corrections)
      {
        B19 += -1.0 / 2.0 * (s.lam3 - s.lam5) * B3_z;
      }

      complexd B20 = -s.lam1 + (3.0 / 2.0) * b_one + 1.0 / (16.0 * sqr(pi)) * (ii * pi - 1.) * (pow(s.lam1, 2) + pow(s.lam5, 2));
      if (wave_function_corrections)
      {
        B20_z = 1.0 / (16.0 * sqr(pi)) * (zij_AA + zij_hh + zij_HH + zij_zz + (zij_HH - zij_hh) * c2a + (zij_zz - zij_AA) * c2b - (zij_Hh - zij_hH) * s2a - zij_Az * s2b);
        B20 += -1.0 * s.lam1 * B20_z;
      }

      complexd B21 = -s.lam2 + (3.0 / 2.0) * b_two + 1.0 / (16.0 * sqr(pi)) * (ii * pi - 1.) * (pow(s.lam2, 2) + pow(s.lam5, 2));
      if (wave_function_corrections)
      {
        B21_z = 1.0 / (16.0 * sqr(pi)) * (zij_AA + zij_hh + zij_HH + zij_zz + (zij_HH - zij_hh) * c2a - (zij_zz - zij_AA) * c2b + (zij_Hh - zij_hH) * s2a + zij_Az * s2b);
        B21 += -1.0 * s.lam2 * B21_z;
      }

      complexd B22 = -s.lam5 + (3.0 / 2.0) * b_five + (1.0 / (16.0 * sqr(pi))) * (ii * pi - 1.) * (s.lam1 + s.lam2) * s.lam5;
      if (wave_function_corrections)
      {
        B22_z = 1.0 / (16.0 * sqr(pi)) * (zij_AA + zij_hh + zij_HH + zij_zz);
        B22 += -1.0 * s.lam5 * B22_z;
      }

      complexd B30 = -(s.lam3 + s.lam4) + (3.0 / 2.0) * (b_three + b_four) + (1.0 / (16.0 * sqr(pi))) * (ii * pi - 1.) * pow((s.lam3 + s.lam4), 2);
      if (wave_function_corrections)
      {
        B30 += -1.0 * (s.lam3 + s.lam4) * B22_z;
      }

      // eigenvalues
      complexd a00_even_plus = 1.0 / (32.0 * pi) * ((B1 + B2) + sqrt(pow((B1 - B2), 2) + 4. * pow(B3, 2)));
      complexd a00_even_minus = 1.0 / (32.0 * pi) * ((B1 + B2) - sqrt(pow((B1 - B2), 2) + 4. * pow(B3, 2)));
      complexd a00_odd_plus = 1.0 / (32.0 * pi) * (2. * B4 + 2. * B6);
      complexd a00_odd_minus = 1.0 / (32.0 * pi) * (2. * B4 - 2. * B6);
      complexd a01_even_plus = 1.0 / (32.0 * pi) * (B7 + B8 + sqrt(pow((B7 - B8), 2) + 4. * pow(B9, 2)));
      complexd a01_even_minus = 1.0 / (32.0 * pi) * (B7 + B8 - sqrt(pow((B7 - B8), 2) + 4. * pow(B9, 2)));
      complexd a01_odd_plus = 1.0 / (32.0 * pi) * (2. * B13 + 2. * B15);
      complexd a01_odd_minus = 1.0 / (32.0 * pi) * (2. * B13 - 2. * B15);
      complexd a10_odd = 1.0 / (32.0 * pi) * (2. * B19);
      complexd a11_even_plus = 1.0 / (32.0 * pi) * (B20 + B21 + sqrt(pow((B20 - B21), 2) + 4. * pow(B22, 2)));
      complexd a11_even_minus = 1.0 / (32.0 * pi) * (B20 + B21 - sqrt(pow((B20 - B21), 2) + 4. * pow(B22, 2)));
      complexd a11_odd = 1.0 / (32.0 * pi) * (2. * B30);

      return {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus,
              a01_even_minus, a01_odd_plus, a01_odd_minus, a10_odd, a11_even_plus, a11_even_minus, a11_odd};
    }

   }

}
