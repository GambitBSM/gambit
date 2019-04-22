//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  THDM derived version of SubSpectrum class.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author James McKay
///          (j.mckay14@imperial.ac.uk)
///  \date 2016 Oct
///
///  \ modified:
///   Filip Rajec
///   Feb 2017-2019
///
///  *********************************************

#ifndef THDMSPEC_H
#define THDMSPEC_H

#include <memory>
#include <typeinfo>

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Elements/slhaea_helpers.hpp"
#include "gambit/Elements/thdm_slhahelp.hpp"
#include "gambit/Elements/subspectrum.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Utils/version.hpp"
#include "gambit/SpecBit/THDMSpec_head.hpp"

// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/config/config.h"


namespace Gambit
{


   namespace SpecBit
   {
      template <class MI>
      const int THDMSpec<MI>::_index_offset = MI::index_offset;

      // NOTE!! mi is COPIED into the object, so when we get the reference to the
      // actual Model object to store in 'model', we need to use the copy inside
      // the object. So also need to make sure 'model_interface' is initialised first
      // (i.e. it should be declared first)
      template <class MI>
      THDMSpec<MI>::THDMSpec(MI mi, str be_name, str be_version)
         : backend_name(be_name)
         , backend_version(be_version)
         , model_interface(mi)
      {}


      template <class MI>
      THDMSpec<MI>::THDMSpec()
      {}

      template <class MI>
      THDMSpec<MI>::~THDMSpec()
      {}


      template <class MI>
      void THDMSpec<MI>::RunToScaleOverride(double scale)
      {
        try {
          model_interface.model.run_to(scale);
        }
        catch(...){
          std::cout << "SpecBit throwing invalid point @ running" << std::endl;
          invalid_point().raise("FS Invalid Point: RunToScale Failed");
          //TODO: Terminal message here
        }
        // model_interface.model.calculate_DRbar_masses();

      }
      template <class MI>
      double THDMSpec<MI>::GetScale() const
      {
        return model_interface.model.get_scale();
      }


      template <class MI>
      void THDMSpec<MI>::SetScale(double scale)
      {
        model_interface.model.set_scale(scale);
      }

      // Fill an SLHAea object with spectrum information
      template <class MI>
      void THDMSpec<MI>::add_to_SLHAea(int slha_version, SLHAstruct& slha) const
      {
         std::ostringstream comment;

         // SPINFO block
         // TODO: This needs to become more sophisticated to deal with data potentially
         // produced by different LE and HE spectrum sources. For now whichever subspectrum
         // adds this block first will "win".
         if(not SLHAea_block_exists(slha, "SPINFO"))
         {
            SLHAea_add_block(slha, "SPINFO");
            SLHAea_add(slha, "SPINFO", 1, "GAMBIT, using "+backend_name);
            SLHAea_add(slha, "SPINFO", 2, gambit_version()+" (GAMBIT); "+backend_version+" ("+backend_name+")");
         }
 
         // All other THDM blocks
         slhahelp::add_THDM_spectrum_to_SLHAea(*this, slha, slha_version);
      }

      template <class MI>
      std::string THDMSpec<MI>::AccessError(std::string state) const
      {
        std::string errormsg;
        errormsg = "Error accessing "+ state + " element is out of bounds";
        return errormsg;
      }

      template <class Model>
      double get_sinthW2_MSbar(const Model& model) {
         double sthW2 = Utils::sqr(model.get_g1()) * 0.6 /
         (0.6 * Utils::sqr(model.get_g1()) +
         Utils::sqr(model.get_g2()));
         return sthW2;
      }

      template <class Model>
      double get_vev(const Model& model) {
         return sqrt(pow(model.get_v1(),2) + pow(model.get_v2(),2));
      }

      // function to compute TanBeta from VEVs
      template <class Model>
      double get_tanb(const Model& model) {
         return model.get_v2()/model.get_v1();
      }

      template <class Model>
      double get_mW_running(const Model& model) {
         return (model.get_DRbar_masses())(19);
      }

      template <class Model>
      double get_mW_pole_slha(const Model& model) {
         return model.get_MVWm_pole_slha();
      }

      template <class Model>
      double get_mA_running(const Model& model) {
         return (model.get_DRbar_masses())(7);
      }

      template <class Model>
      double get_mA_pole_slha(const Model& model) {
         return model.get_MAh_pole_slha(1);
      }

      template <class Model>
      double get_mA_goldstone_running(const Model& model) {
         return (model.get_DRbar_masses())(6);
      }

      template <class Model>
      double get_mA_goldstone_pole_slha(const Model& model) {
         return model.get_MAh_pole_slha(0);
      }

      template <class Model>
      double get_mh_1_running(const Model& model) {
         return (model.get_DRbar_masses())(4);
      }

      template <class Model>
      double get_mh_1_pole_slha(const Model& model) {
         return model.get_Mhh_pole_slha(0);
      }

      template <class Model>
      double get_mh_2_running(const Model& model) {
         return (model.get_DRbar_masses())(5);
      }

      template <class Model>
      double get_mh_2_pole_slha(const Model& model) {
         return model.get_Mhh_pole_slha(1);
      }

      template <class Model>
      double get_mHpm_running(const Model& model) {
         return (model.get_DRbar_masses())(9);
      }

      template <class Model>
      double get_mHpm_pole_slha(const Model& model) {
         return model.get_MHm_pole_slha(1);
      }

      template <class Model>
      double get_mHpm_goldstone_running(const Model& model) {
         return (model.get_DRbar_masses())(8);
      }

      template <class Model>
      double get_mHpm_goldstone_pole_slha(const Model& model) {
         return model.get_MHm_pole_slha(0);
      }
      // get lambdas (running) from FS

      template <class Model>
      double get_Lambda1(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam345 = model.get_Lambda3() + model.get_Lambda4() + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return lam1*pow(cb,4) + lam2*pow(sb,4) + 0.5*lam345*pow(s2b,2) + 2.*s2b*(pow(cb,2)*lam6+pow(sb,2)*lam7);
      }

      template <class Model>
      double get_Lambda2(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam345 = model.get_Lambda3() + model.get_Lambda4() + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return lam1*pow(sb,4) + lam2*pow(cb,4) + 0.5*lam345*pow(s2b,2) - 2.*s2b*(pow(sb,2)*lam6+pow(cb,2)*lam7);
      }

      template <class Model>
      double get_Lambda3(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam3 = model.get_Lambda3(), lam345 = lam3 + model.get_Lambda4() + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam3 - s2b*c2b*(lam6-lam7);
      }

      template <class Model>
      double get_Lambda4(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam4 = model.get_Lambda4(), lam345 = model.get_Lambda3() + lam4 + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam4 - s2b*c2b*(lam6-lam7);
      }

      template <class Model>
      double get_Lambda5(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam5 = model.get_Lambda5(), lam345 = model.get_Lambda3() + model.get_Lambda4() + lam5;
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return 0.25*pow(s2b,2)*(lam1+lam2-2.*lam345) + lam5 - s2b*c2b*(lam6-lam7);
      }

      template <class Model>
      double get_Lambda6(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam345 = model.get_Lambda3() + model.get_Lambda4() + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return -0.5*s2b*(lam1*pow(cb,2)-lam2*pow(sb,2)-lam345*c2b) + cb*cos(3.*b)*lam6 + sb*sin(3.*b)*lam7;
      }

      template <class Model>
      double get_Lambda7(const Model& model) {
         double lam1 = model.get_Lambda1(), lam2 = model.get_Lambda2(), lam345 = model.get_Lambda3() + model.get_Lambda4() + model.get_Lambda5();
         double lam6 = model.get_Lambda6(), lam7 = model.get_Lambda7(), b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return -0.5*s2b*(lam1*sb*sb-lam2*cb*cb+lam345*c2b)+sb*sin(3.*b)*lam6+cb*cos(3.*b)*lam7;
      }

      template <class Model>
      double get_M12_2(const Model& model) {
         double m12_2 = model.get_M122(), m11_2 = model.get_M112(), m22_2 = model.get_M222();
         double b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return 0.5*(m11_2-m22_2)*s2b + m12_2*c2b;
      }

      template <class Model>
      double get_M11_2(const Model& model) {
         double m12_2 = model.get_M122(), m11_2 = model.get_M112(), m22_2 = model.get_M222();
         double b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return m11_2*pow(cb,2) + m22_2*pow(sb,2) - m12_2*s2b;
      }

      template <class Model>
      double get_M22_2(const Model& model) {
         double m12_2 = model.get_M122(), m11_2 = model.get_M112(), m22_2 = model.get_M222();
         double b = atan(get_tanb(model)), cb = cos(b), sb = sin(b), c2b = cos(2.*b), s2b = sin(2.*b);
         return m11_2*pow(sb,2) + m22_2*pow(cb,2) + m12_2*s2b;
      }

      template <class Model>
      double get_lambda1(const Model& model) {
         return model.get_Lambda1();
      }

      template <class Model>
      double get_lambda2(const Model& model) {
         return model.get_Lambda2();
      }

      template <class Model>
      double get_lambda3(const Model& model) {
         return model.get_Lambda3();
      }

      template <class Model>
      double get_lambda4(const Model& model) {
         return model.get_Lambda4();
      }

      template <class Model>
      double get_lambda5(const Model& model) {
         return model.get_Lambda5();
      }

      template <class Model>
      double get_lambda6(const Model& model) {
         return model.get_Lambda6();
      }

      template <class Model>
      double get_lambda7(const Model& model) {
         return model.get_Lambda7();
      }

      template <class Model>
      double get_m12_2(const Model& model) {
         return model.get_M122();
      }

      template <class Model>
      double get_m11_2(const Model& model) {
         return model.get_M112();
      }

      template <class Model>
      double get_m22_2(const Model& model) {
         return model.get_M222();
      }

      template <class Model>
      double get_sinthW2_DRbar(const Model& model) {
         double sthW2 = Utils::sqr(model.get_g1()) * 0.6 /
         (0.6 * Utils::sqr(model.get_g1()) +
         Utils::sqr(model.get_g2()));
         return sthW2;
      }

      template <class Model>
      double get_yukawa_coupling(const Model& model) {
         std::string spec_class_type = typeid(model).name();
         if (spec_class_type == "N12flexiblesusy11THDM_I_slhaINS_6THDM_IINS_9Two_scaleEEEEE"){
            return 1;
         }
         else if (spec_class_type == "N12flexiblesusy12THDM_II_slhaINS_7THDM_IIINS_9Two_scaleEEEEE"){
            return 2;
         }
         else if (spec_class_type == "N12flexiblesusy16THDM_lepton_slhaINS_11THDM_leptonINS_9Two_scaleEEEEE"){
            return 3;
         }
         else if (spec_class_type == "N12flexiblesusy17THDM_flipped_slhaINS_12THDM_flippedINS_9Two_scaleEEEEE"){
            return 4;
         }
         else {
           utils_error().raise(LOCAL_INFO,"Unknown spectrum generator requested for THDM."); return -1;
            exit(0);
         }
      }

      // function to calculate alpha from mixing matrix
      template <class Model>
      double get_alpha(const Model& model) {
         // double cosa = (model.get_DRbar_masses_and_mixings())(22);
         // double sina =  (model.get_DRbar_masses_and_mixings())(23);
         // double a = acos(cosa);
         // if (a<0){
         //    a = a+M_PI;
         // }
         // return a;
         double v_1 = model.get_v1(), v_2 = model.get_v2();
         double b = atan(v_2/v_1);
         double v2 = pow(v_1,2) + pow(v_2,2);
         double mA = get_mA_pole_slha(model);
         double mA_2 = pow(mA,2);
         double Lam1 = get_Lambda1(model), Lam5 = get_Lambda5(model), Lam6 = get_Lambda6(model);

         double tan2ba = (2.0*Lam6*v2)/(mA_2 + (Lam5-Lam1)*v2);
         double s2ba = -(2.0*Lam6*v2)/sqrt(pow((mA_2 + (Lam5-Lam1)*v2),2) + 4.0*pow(Lam6,2)*v2*v2);
         double c2ba = s2ba/tan2ba;

         double ba = 0.5*acos(c2ba);
         double alpha = b - ba;

         return alpha;
      }

      // ----------
      // THDM tree-level basis transformations for use throughout GAMBIT
      // to use these functions you must include this header
      // ----------

      // for C++<20 we cannot use contains on std::map instead we write basis_map_contains fucntion
      inline bool basis_map_contains(std::map<std::string, double> basis, std::string par_key) {
         std::map<std::string, double>::iterator it = basis.find(par_key);
         if(it != basis.end()) return true; //found
         return false;
      }

      inline std::map<std::string, double> create_empty_THDM_basis(){
         const double EMPTY = -1E10;
         std::map<std::string, double> basis;
         // create a complete list of keys for basis
         const std::vector<std::string> basis_keys{"lambda1", "lambda2", "lambda3", "lambda4", "lambda5", "lambda6", "lambda7", "m12_2", "m11_2", "m22_2", \
                                             "Lambda1", "Lambda2", "Lambda3", "Lambda4", "Lambda5", "Lambda6", "Lambda7", "M12_2", "M11_2", "M22_2", \
                                             "m_h", "m_H", "m_A", "m_Hp", "tanb", "sba","alpha"};
         // fill entries in basis
         for(const auto& each_basis_key : basis_keys){
           basis.insert(std::make_pair(each_basis_key, EMPTY));
         }
         return basis;
      }

      inline void print_THDM_spectrum(std::map<std::string, double>& basis){
         const double EMPTY = -1E10;
         const std::vector<std::string> basis_keys{"lambda1", "lambda2", "lambda3", "lambda4", "lambda5", "lambda6", "lambda7", "m12_2", "m11_2", "m22_2", \
                                             "Lambda1", "Lambda2", "Lambda3", "Lambda4", "Lambda5", "Lambda6", "Lambda7", "M12_2", "M11_2", "M22_2", \
                                             "m_h", "m_H", "m_A", "m_Hp", "tanb", "sba","alpha"};
         // fill entries in basis
         for(const auto& each_basis_key : basis_keys){
           std::cout << each_basis_key << ": ";
           if (basis[each_basis_key]!= EMPTY) std::cout << basis[each_basis_key] << std::endl;
           else std::cout << "NOT FILLED" << std::endl;
         }
      }

      inline bool check_basis(const std::vector<std::string> basis_keys, std::map<std::string, double> basis){
         const double EMPTY = -1E10;
         for(const auto& each_basis_key : basis_keys){
            if (!basis_map_contains(basis, each_basis_key) || basis[each_basis_key] == EMPTY) return false;
         }
         return true;
      }

      inline void fill_generic_THDM_basis(std::map<std::string, double>& input_basis, const SMInputs& sminputs){
         const std::vector<std::string> higgs_basis_keys{"Lambda1","Lambda2","Lambda3","Lambda4","Lambda5","M12_2","tanb"};
         const std::vector<std::string> physical_basis_keys{"m_h","m_H","m_A","m_Hp","tanb","m12_2","sba"};
         // necessary definitions
         double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
         double tanb  = input_basis["tanb"];
         double beta = atan(tanb);
         double sb = sin(beta), cb = cos(beta), tb = tan(beta);
         double sb2 = sb*sb, cb2 = cb*cb, ctb = 1./tb;
         double s2b = sin(2.*beta), c2b = cos(2.*beta);
         //initially try to fill from Higgs basis
         if (check_basis(higgs_basis_keys, input_basis)) {
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
         else if(check_basis(physical_basis_keys, input_basis)) {
            // get values from physical basis
            double m_h = input_basis["m_h"], m_H = input_basis["m_H"], m_A = input_basis["m_A"], m_Hp = input_basis["m_Hp"];
            double lambda6 = input_basis["lambda6"], lambda7 = input_basis["lambda7"], sba = input_basis["sba"], m12_2 = input_basis["m12_2"];
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
         else{
            // fail
         }

      }

      inline void fill_higgs_THDM_basis(std::map<std::string, double>& input_basis, const SMInputs& sminputs){
         const std::vector<std::string> physical_basis_keys{"m_h","m_H","m_A","m_Hp","tanb","m12_2","sba"};
         const std::vector<std::string> generic_basis_keys{"lambda1","lambda2","lambda3","lambda4","lambda5","m12_2","tanb"};
          // necessary definitions
         double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
         double tanb  = input_basis["tanb"];
         double beta = atan(tanb);
         double sb = sin(beta), cb = cos(beta), tb = tan(beta);
         double ctb = 1./tb;
         double s2b = sin(2.*beta), c2b = cos(2.*beta);
         //initially try to fill from scalar basis
         if (check_basis(generic_basis_keys, input_basis)) {
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
         else if(check_basis(physical_basis_keys, input_basis)) {
            // get values from physical basis
            // double m_h = input_basis["m_h"], m_H = input_basis["m_H"], m_A = input_basis["m_A"], m_Hp = input_basis["m_Hp"];
            // double sba = input_basis["sba"], m12_2 = input_basis["m12_2"];
            // -----TODO------ implement this
         }
         else{
            // fail
         }
      }

      inline void fill_physical_THDM_basis(std::map<std::string, double>& input_basis, const SMInputs& sminputs){
         const std::vector<std::string> higgs_basis_keys{"Lambda1","Lambda2","Lambda3","Lambda4","Lambda5","M12_2","tanb"};
         const std::vector<std::string> generic_basis_keys{"lambda1","lambda2","lambda3","lambda4","lambda5","m12_2","tanb"};
         // necessary definitions
         double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
         double tanb  = input_basis["tanb"];
         double beta = atan(tanb);
         double sb = sin(beta), cb = cos(beta), tb = tan(beta);
         double sb2 = sb*sb, cb2 = cb*cb, ctb = 1./tb;
         //initially try to fill from higgs basis
         if(check_basis(generic_basis_keys, input_basis)) {
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
         else if (check_basis(higgs_basis_keys, input_basis)) {
            // current method does not match in results (Why?)
            // -----TODO------ implement this

            // const std::complex<double> i(0.0,1.0);
            // const std::vector<std::vector<complex<double>>> q = {{0.0, 0.0, 0.0}, {0.0, sba, -cba}, {0.0, cba, sba}, {0.0, 0.0, i}, {0.0, i, 0.0}};

            //  // double A_h0_2 = M22_2 + 0.5*v2*(Lam3 + Lam4 - Lam5);
            // std::vector<double> mh0_2_k;
            // for(int k=1; k<4; k++) {
            //    double mk = 0.0;
            //   // --------
            //   // METHOD 1
            //   // original method for calculating these masses for GAMBIT:
            //   // this method is consistent with Higgs Basis masses
            //   // NOTE: will revert to METHOD 1 later
            //   // -------
            //   //  (q[k][2] * std::conj(q[k][2]) * A_h0_2).real();
            //   //  mk += v2 * pow(q[k][1],2).real() * Lam1;
            //   //  mk += v2 * (q[k][2]).real() * (q[k][2]*Lam5).real();
            //   //  mk += v2 * 2.0 * q[k][1].real() * (q[k][2]*Lam6).real();
            //   // --------
            //    mh0_2_k.push_back(mk);
            // }

         }
         else{
            // fail
         }
      }
      
      inline void generate_THDM_spectrum_tree_level(std::map<std::string, double>& basis, const SMInputs& sminputs)
      {
         const double EMPTY = -1E10;
         // validate basis entries
         // create a complete list of keys for basis
         const std::vector<std::string> basis_keys{"lambda1", "lambda2", "lambda3", "lambda4", "lambda5", "lambda6", "lambda7,", "m12_2", "m11_2", "m22_2", \
                                             "Lambda1", "Lambda2", "Lambda3", "Lambda4", "Lambda5", "Lambda6", "Lambda7", "M12_2", "M11_2", "M22_2", \
                                             "m_h", "m_H", "m_A", "m_Hp", "tanb", "sba","alpha"};
         // validate entries in basis
         for(const auto& each_basis_key : basis_keys){
            if (!basis_map_contains(basis, each_basis_key)) basis.insert(std::make_pair(each_basis_key, EMPTY));
         }

         // create a seperate list of keys for basis
         const std::vector<std::string> higgs_basis_keys{"Lambda1","Lambda2","Lambda3","Lambda4","Lambda5","M12_2","tanb"};
         const std::vector<std::string> generic_basis_keys{"lambda1","lambda2","lambda3","lambda4","lambda5","m12_2","tanb"};
         const std::vector<std::string> physical_basis_keys{"m_h","m_H","m_A","m_Hp","tanb","m12_2","sba"};

         // are the minimum requirements for a filled coupling basis satsified?
         bool coupling_filled = check_basis(generic_basis_keys, basis);
         // are the minimum requirements for a filled higgs basis satsified?
         bool higgs_filled = check_basis(higgs_basis_keys, basis);
         // are the minimum requirements for a filled physical basis satsified?
         bool physical_filled = check_basis(physical_basis_keys, basis);

         if (!coupling_filled && !higgs_filled && !physical_filled){
            std::ostringstream errmsg;
            errmsg << "SpecBit error (fatal): A problem was encountered during spectrum generation." << std::endl;
            errmsg << "Incomplete basis was sent to tree-level generator." << std::endl;
            // SpecBit_error().raise(LOCAL_INFO,errmsg.str());
            std::cout << "SpecBit error (fatal): A problem was encountered during spectrum generation." << std::endl;
            std::cout << "Incomplete basis was sent to tree-level generator." << std::endl;
            std::cout << "Force Exiting SpecBit!" << std::endl;
            exit(0);
            return;
         }

         if (!coupling_filled) fill_generic_THDM_basis(basis, sminputs);
         if (!higgs_filled) fill_higgs_THDM_basis(basis, sminputs);
         if (!physical_filled) fill_physical_THDM_basis(basis, sminputs);

         // calculate alpha 2 methods for now
         // fill alpha
         double v2 = 1.0/(sqrt(2.0)*sminputs.GF);
         double tanb  = basis["tanb"];
         double beta = atan(tanb);
         double sb = sin(beta), cb = cos(beta), tb = tan(beta);
         double Lambda1 = basis["Lambda1"], Lambda3 = basis["Lambda3"], Lambda4 = basis["Lambda4"], Lambda5 = basis["Lambda5"];
         double Lambda6 = basis["Lambda6"], M22_2 = basis["M22_2"];
         double mC_2 = M22_2 + 0.5*v2*Lambda3;
         double mA_2 = mC_2 - 0.5*v2*(Lambda5 - Lambda4);
         double tan2ba = (2.0*Lambda6*v2)/(mA_2 + (Lambda5-Lambda1)*v2);
         double s2ba = -(2.0*Lambda6*v2)/sqrt(pow((mA_2 + (Lambda5-Lambda1)*v2),2) + 4.0*pow(Lambda6,2)*v2*v2);
         double c2ba = s2ba/tan2ba;
         double ba = 0.5*acos(c2ba);
         double alpha = beta - ba;
         if (alpha > M_PI/2) alpha = alpha - M_PI;
         basis["alpha"] = alpha;
         basis["sba"] = sin(beta - alpha);
      }

      template <class MI>
      typename THDMSpec<MI>::GetterMaps THDMSpec<MI>::fill_getter_maps()
      {
        typename THDMSpec<MI>::GetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTget::FInfo1 FInfo1;
         typedef typename MTget::FInfo2 FInfo2;

         static const int i01v[] = {0,1};
         static const std::set<int> i01(i01v, Utils::endA(i01v));

         static const int i012v[] = {0,1,2};
         static const std::set<int> i012(i012v, Utils::endA(i012v));

         static const int i0123v[] = {0,1,2,3};
         static const std::set<int> i0123(i0123v, Utils::endA(i0123v));

         static const int i012345v[] = {0,1,2,3,4,5};
         static const std::set<int> i012345(i012345v, Utils::endA(i012345v));

         /// @{ mass1 - mass dimension 1 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;

            

            map_collection[Par::mass1].map0 = tmp_map;
         }

          // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;
            // coupling basis potential parameters
            tmp_map["m11_2"]= &get_m11_2<Model>;
            tmp_map["m22_2"]= &get_m22_2<Model>;
            tmp_map["m12_2"]= &get_m12_2<Model>;
            tmp_map["lambda_1"]= &get_lambda1<Model>;
            tmp_map["lambda_2"]= &get_lambda2<Model>;
            tmp_map["lambda_3"]= &get_lambda3<Model>;
            tmp_map["lambda_4"]= &get_lambda4<Model>;
            tmp_map["lambda_5"]= &get_lambda5<Model>;
            tmp_map["lambda_6"]= &get_lambda6<Model>;
            tmp_map["lambda_7"]= &get_lambda7<Model>;
            // higgs basis potential parameters
            tmp_map["M11_2"]= &get_M11_2<Model>;
            tmp_map["M22_2"]= &get_M22_2<Model>;
            tmp_map["M12_2"]= &get_M12_2<Model>;
            tmp_map["Lambda_1"]= &get_Lambda1<Model>;
            tmp_map["Lambda_2"]= &get_Lambda2<Model>;
            tmp_map["Lambda_3"]= &get_Lambda3<Model>;
            tmp_map["Lambda_4"]= &get_Lambda4<Model>;
            tmp_map["Lambda_5"]= &get_Lambda5<Model>;
            tmp_map["Lambda_6"]= &get_Lambda6<Model>;
            tmp_map["Lambda_7"]= &get_Lambda7<Model>;
            // physical basis running masses
            tmp_map["A0"] = &get_mA_running<Model>;
            tmp_map["H+"] = &get_mHpm_running<Model>;
            tmp_map["H-"] = &get_mHpm_running<Model>;
            tmp_map["G0"] = &get_mA_goldstone_running<Model>;
            tmp_map["G+"] = &get_mHpm_goldstone_running<Model>;
            tmp_map["G-"] = &get_mHpm_goldstone_running<Model>;
            tmp_map["W+"] = &get_mW_running<Model>;
            tmp_map["W-"] = &get_mW_running<Model>;
            // vev
            tmp_map["vev"]= &get_vev<Model>;

            map_collection[Par::mass1].map0_extraM = tmp_map;
         }

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
        {
            typename MTget::fmap1 tmp_map;

            tmp_map["h0"] =  FInfo1( &Model::get_Mhh, i01 );
            
            map_collection[Par::mass1].map1 = tmp_map;
         }

         /// @}

         // @{ dimensionless - mass dimension 0 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;
            tmp_map["g1"]= &Model::get_g1;
            tmp_map["g2"]= &Model::get_g2;
            tmp_map["g3"]= &Model::get_g3;

            // tmp_map["tanb"]= &Model::get_tanb;

            map_collection[Par::dimensionless].map0 = tmp_map;
         }

         // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;
            tmp_map["sinW2"] = &get_sinthW2_DRbar<Model>;
            tmp_map["tanb"]= &get_tanb<Model>;
            tmp_map["alpha"]= &get_alpha<Model>;
            tmp_map["yukawaCoupling"]= &get_yukawa_coupling<Model>;
            map_collection[Par::dimensionless].map0_extraM = tmp_map;
         }

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTget::fmap2 tmp_map;

            tmp_map["Yd"]= FInfo2( &Model::get_Yd, i012, i012);
            tmp_map["Yu"]= FInfo2( &Model::get_Yu, i012, i012);
            tmp_map["Ye"]= FInfo2( &Model::get_Ye, i012, i012);

            map_collection[Par::dimensionless].map2 = tmp_map;
         }
         /// @}

         /// @{ Pole_Mass - Pole mass parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTget::fmap0 tmp_map;

	    /// PA: W mass is a prediction in most spectrum generators
	    /// so we need this.  One tricky question is how to interface
	    /// spectrum generators which have different input / outputs
	    /// *may* be ok to still mimic the FS way
            

            map_collection[Par::Pole_Mass].map0 = tmp_map;
         }

         // Functions utilising the "extraM" function signature
         // (Zero index, model object as argument)
         {
            typename MTget::fmap0_extraM tmp_map;

            // Using wrapper functions defined above
            tmp_map["A0"] = &get_mA_pole_slha<Model>;
            tmp_map["H+"] = &get_mHpm_pole_slha<Model>;
            tmp_map["H-"] = &get_mHpm_pole_slha<Model>;
            tmp_map["G0"] = &get_mA_goldstone_pole_slha<Model>;
            tmp_map["G+"] = &get_mHpm_goldstone_pole_slha<Model>;
            tmp_map["G-"] = &get_mHpm_goldstone_pole_slha<Model>;
            tmp_map["W+"] = &get_mW_pole_slha<Model>;
            tmp_map["W-"] = &get_mW_pole_slha<Model>;

            map_collection[Par::Pole_Mass].map0_extraM = tmp_map;
         }

         // Functions utilising the one-index "plain-vanilla" function signature
         // (One-index member functions of model object)s
         {
            typename MTget::fmap1 tmp_map;

            tmp_map["h0"] =  FInfo1( &Model::get_Mhh_pole_slha, i01 );
            
            map_collection[Par::Pole_Mass].map1 = tmp_map;
         }

         /// @}

         return map_collection;
      }

      // Filler function for setter function pointer maps
      template <class MI>
      typename THDMSpec<MI>::SetterMaps THDMSpec<MI>::fill_setter_maps()
      {
         typename THDMSpec<MI>::SetterMaps map_collection;
         typedef typename MI::Model Model;

         typedef typename MTset::FInfo2 FInfo2;

        //  typedef typename MTset::FInfo1M FInfo1M;
        //  typedef typename MTset::FInfo2M FInfo2M;

         static const std::set<int> i01 = initSet(0,1);
         static const std::set<int> i012 = initSet(0,1,2);
         static const std::set<int> i0123 = initSet(0,1,2,3);
         static const std::set<int> i012345 = initSet(0,1,2,3,4,5);


         /// @{ mass1 - mass dimension 1 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTset::fmap0 tmp_map;
            // tmp_map["vev"]= &Model::set_vev;

            map_collection[Par::mass1].map0 = tmp_map;
         }

         /// @}

         // @{ dimensionless - mass dimension 0 parameters
         //
         // Functions utilising the "plain-vanilla" function signature
         // (Zero index member functions of model object)
         {
            typename MTset::fmap0 tmp_map;
            tmp_map["g1"]= &Model::set_g1;
            tmp_map["g2"]= &Model::set_g2;
            tmp_map["g3"]= &Model::set_g3;

            // tmp_map["tanb"]= &Model::set_tanb;

            map_collection[Par::dimensionless].map0 = tmp_map;
         }

         

         // Functions utilising the two-index "plain-vanilla" function signature
         // (Two-index member functions of model object)
         {
            typename MTset::fmap2 tmp_map;

            tmp_map["Yd"]= FInfo2( &Model::set_Yd, i012, i012);
            tmp_map["Yu"]= FInfo2( &Model::set_Yu, i012, i012);
            tmp_map["Ye"]= FInfo2( &Model::set_Ye, i012, i012);

            // tmp_map["ReYd2"]= FInfo2( &Model::set_ReYd2, i012, i012);
            // tmp_map["ReYu2"]= FInfo2( &Model::set_ReYu2, i012, i012);
            // tmp_map["ReYe2"]= FInfo2( &Model::set_ReYe2, i012, i012);

            // tmp_map["ImYd2"]= FInfo2( &Model::set_ImYd2, i012, i012);
            // tmp_map["ImYu2"]= FInfo2( &Model::set_ImYu2, i012, i012);
            // tmp_map["ImYe2"]= FInfo2( &Model::set_ImYe2, i012, i012);

            map_collection[Par::dimensionless].map2 = tmp_map;
         }

        {
          typename MTset::fmap0_extraM tmp_map;
          // tmp_map["A0"] = &set_MAh1_pole_slha<Model>;
          // tmp_map["H+"] = &set_MHpm1_pole_slha<Model>;

          map_collection[Par::dimensionless].map0_extraM = tmp_map;
        }

        {
          typename MTset::fmap1_extraM tmp_map;

          // tmp_map["h0"] =  FInfo1M( &set_Mhh_pole_slha<Model>, i01 );

          map_collection[Par::Pole_Mass].map1_extraM = tmp_map;
        }

         return map_collection;
      }

   } // end SpecBit namespace


} // end Gambit namespace

#endif
