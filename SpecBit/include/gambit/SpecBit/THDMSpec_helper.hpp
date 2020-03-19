//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  "Header" declarations for THDMSpec class
///  (definitions in another header file due to
///  this being a template class)
///
///  *********************************************
///
///  Authors: 
///  <!-- add name and date if you modify -->
///
///  \author Filip Rajec
///          filip.rajec@adelaide.edu.au
///  \date 2019 Nov
///
///  *********************************************

#include "gambit/SpecBit/THDMSpec.hpp"

#ifndef THDMSPEC_HELPER_H
#define THDMSPEC_HELPER_H

namespace Gambit 
{
   namespace SpecBit
   {

      // ----------
      // Spectrum and tree-level basis transformation functions
      // To use:
      // 1. Include this helper header.
      // 2. If not in SpecBit namespace append to function.
      // 
      // These functions exist to improve code reuse (at a developer level).
      // They are inline to avoid multiple library linking,
      // unfortunately this means they do not improve code reuse in the build 
      // ----------

      // ----------
      // **  THDM container functions
      // functions to create and distribute THDM container
      // the THDM container combines the Spectrum and THDMC objects to optimise code efficiency
      // ----------
      struct higgs_basis_pars { 
         double Lambda1, Lambda2, Lambda3, Lambda4, Lambda5, Lambda6, Lambda7;
         double M11_2, M22_2, M12_2;
      };

      struct THDM_spectrum_container {
         std::unique_ptr<SubSpectrum> he;
         std::unique_ptr<SubSpectrum> SM;
         SMInputs sminputs;
         THDMC_1_7_0::THDM* THDM_object;
         higgs_basis_pars higgs_pars;
         int yukawa_type;
         THDM_spectrum_container() {
            THDM_object = new THDMC_1_7_0::THDM();
         }
         ~THDM_spectrum_container() {
            delete THDM_object;
         }
      };

      // creates & fills to 2HDMC SM object
      inline void set_SM(const std::unique_ptr<SubSpectrum>& he, 
         const std::unique_ptr<SubSpectrum>& SM, 
         const SMInputs& sminputs, THDMC_1_7_0::THDM* THDM_object);

      // Takes in the spectrum and fills a THDM object which is defined
      // in 2HDMC. Any 2HDMC functions can then be called on this object.
      inline void init_THDM_object(const std::unique_ptr<SubSpectrum>& he, 
         const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, 
         const int yukawa_type, THDMC_1_7_0::THDM* THDM_object);

      // Initializes the THDM pars struct 
      inline void init_higgs_basis_pars(const std::unique_ptr<SubSpectrum>& he, 
         higgs_basis_pars& higgs_pars);

      // create a THDM object in the SM limit
      inline void init_THDM_object_SM_like(const double m_h, 
         const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, 
         THDMC_1_7_0::THDM* THDM_object);

      // Creates a THDM Spectrum Constainer with no runnning scale
      inline void init_THDM_spectrum_container(THDM_spectrum_container& container, 
         const Spectrum& spec, const int yukawa_type);

      // Creates a THDM Spectrum Container
      inline void init_THDM_spectrum_container(THDM_spectrum_container& container, 
         const Spectrum& spec, const int yukawa_type, const double scale);

      // ----------
      // ** THDM tree-level basis transformation functions
      // ----------

      // for C++<20 (in use) we cannot use contains on std::map instead we write basis_map_contains function
      inline bool basis_map_contains(std::map<std::string, double> basis, std::string par_key);

      // initiate a THDM basis map
      inline std::map<std::string, double> create_empty_THDM_basis();

      // print a THDM basis map
      inline void print_THDM_spectrum(std::map<std::string, double>& basis);

      // checks that the basis map contains all necessary basis keys
      inline bool check_basis(const std::vector<std::string> basis_keys, std::map<std::string, double> basis);

      // fills the generic basis parameters in a THDM basis map
      // input basis must have either Higgs or physical basis filled (or both)
      inline void fill_generic_THDM_basis(std::map<std::string, double>& input_basis, const SMInputs& sminputs);

      // fills the Higgs basis parameters in a THDM basis map
      // input basis must have generic basis filled
      // TODO: allow physical basis
      inline void fill_higgs_THDM_basis(std::map<std::string, double>& input_basis, const SMInputs& sminputs);

      // fills the physical basis parameters in a THDM basis map
      // input basis must have generic basis filled
      // TODO: allow higgs basis (currently in dev.)
      inline void fill_physical_THDM_basis(std::map<std::string, double>& input_basis, const SMInputs& sminputs);
      
      // this is the main method called to generate a THDM spectrum (tree-level)
      // takes in an THDM basis map with at least one filled in basis
      // and returns a complete THDM basis map
      // this routines also calculates alpha
      inline void generate_THDM_spectrum_tree_level(std::map<std::string, double>& basis, const SMInputs& sminputs);

    // ----------------------------------------------------------------------
    // ***
    // Function definitions below

    inline void set_SM(const std::unique_ptr<SubSpectrum>& he, const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, THDMC_1_7_0::THDM* THDM_object){
      THDMC_1_7_0::SM* SM_object = THDM_object->get_SM_pointer();
      SM_object->set_alpha(1/(sminputs.alphainv));
      SM_object->set_alpha_s(sminputs.alphaS);
      // get vev from high energy spectrum & set GF based off VEV
      double vev = he->get(Par::mass1, "vev");
      double GF = 1.0/(sqrt(2)*pow(vev,2.0));
      SM_object->set_GF(GF); //sminputs.GF);
      
      SM_object->set_MZ(SM->get(Par::Pole_Mass,"Z0"));
      SM_object->set_MW(SM->get(Par::Pole_Mass,"W+"));

      SM_object->set_lmass_pole(1,SM->get(Par::Pole_Mass,"e-_1"));
      SM_object->set_lmass_pole(2,SM->get(Par::Pole_Mass,"e-_2"));
      SM_object->set_lmass_pole(3,SM->get(Par::Pole_Mass,"e-_3"));
      SM_object->set_qmass_pole(5,SM->get(Par::Pole_Mass,"d_3")); //u
      SM_object->set_qmass_pole(6,SM->get(Par::Pole_Mass,"u_3")); //s

      // set running masses
      double tanb = he->get(Par::dimensionless, "tanb");
      const double sqrt2v = pow(2.0,0.5)/vev, b = atan(tanb);
      const double cb = cos(b), sb = sin(b);

      double beta_scaling_u = sb, beta_scaling_d = sb, beta_scaling_e = sb;
      
      switch(THDM_object->get_yukawas_type()) {
         case 1:
            break;
         case 2:
            beta_scaling_d = cb;
            beta_scaling_e = cb;
            break;
         case 3:
            beta_scaling_e = cb;
            break;
         case 4:
            beta_scaling_d = cb;
            break;
         }

      double Yd1 = he->get(Par::dimensionless, "Yd", 1, 1);
      double Yu1 = he->get(Par::dimensionless, "Yu", 1, 1);

      double Yd2 = he->get(Par::dimensionless, "Yd", 2, 2);
      double Yu2 = he->get(Par::dimensionless, "Yu", 2, 2);

      double mu1 = Yu1 * beta_scaling_u/sqrt2v;
      double mu2 = Yu2 * beta_scaling_u/sqrt2v;

      double md1 = Yd1 * beta_scaling_d/sqrt2v;
      double md2 = Yd2 * beta_scaling_d/sqrt2v;

      SM_object->set_qmass_pole(1,md1); //d
      SM_object->set_qmass_pole(2,mu1); //u
      SM_object->set_qmass_pole(3,md2); //s
      SM_object->set_qmass_pole(4,mu2); //c

    }

    inline void init_THDM_object(const std::unique_ptr<SubSpectrum>& he, const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, const int yukawa_type, THDMC_1_7_0::THDM* THDM_object) {
      double lambda_1 = he->get(Par::mass1,"lambda_1");
      double lambda_2 = he->get(Par::mass1,"lambda_2");
      double lambda_3 = he->get(Par::mass1, "lambda_3");
      double lambda_4 = he->get(Par::mass1, "lambda_4");
      double lambda_5 = he->get(Par::mass1, "lambda_5");
      double tan_beta = he->get(Par::dimensionless, "tanb");
      double lambda_6 = he->get(Par::mass1, "lambda_6");
      double lambda_7 = he->get(Par::mass1, "lambda_7");
      double m12_2 = he->get(Par::mass1,"m12_2");
      double mh = he->get(Par::Pole_Mass, "h0", 1);
      double mH = he->get(Par::Pole_Mass, "h0", 2);
      double mA = he->get(Par::Pole_Mass, "A0");
      double mC = he->get(Par::Pole_Mass, "H+");
      double mh_run = he->get(Par::mass1, "h0", 1);
      double mH_run = he->get(Par::mass1, "h0", 2);
      double mA_run = he->get(Par::mass1, "A0");
      double mC_run = he->get(Par::mass1, "H+");
      double alpha = he->get(Par::dimensionless, "alpha");
      double sba = sin(atan(tan_beta) - alpha);

      THDM_object->set_yukawas_type(yukawa_type);
      set_SM(he,SM,sminputs,THDM_object);    
      THDM_object->set_param_gen(lambda_1,lambda_2,lambda_3,lambda_4,lambda_5,lambda_6,lambda_7,m12_2,tan_beta);
      
      // double mh_temp,mH_temp,mA_temp,mC_temp,sba_temp,l6_temp,l7_temp,m12_2_temp,tb_temp;
      // double alpha_temp = THDM_object->get_alpha();
      // THDM_object->get_param_phys(mh_temp,mH_temp,mA_temp,mC_temp,sba_temp,l6_temp,l7_temp,m12_2_temp,tb_temp);
      // std::cout << "2HDMC: " << mh_temp << " | " << mH_temp << " | " << mA_temp << " | " << mC_temp << " | " << sba_temp << " | " << m12_2_temp << " | " << tb_temp << " | " << alpha_temp << std::endl;
      // std::cout << "GAMBIT: " << mh << " | " << mH << " | " << mA << " | " << mC << " | " << sba << " | " << m12_2 << " | " << tan_beta << " | " << alpha << std::endl;
      // std::cout << "GAMBIT (run): " << mh_run << " | " << mH_run << " | " << mA_run << " | " << mC_run << " | " << sba << " | " << m12_2 << " | " << tan_beta << " | " << alpha << std::endl;
      
      THDM_object->set_param_full(lambda_1, lambda_2, lambda_3, lambda_4, lambda_5, lambda_6, lambda_7, \
                                  m12_2, tan_beta, mh, mH, mA, mC, sba);
      
    }

    inline void init_higgs_basis_pars(const std::unique_ptr<SubSpectrum>& he, higgs_basis_pars& higgs_pars) {
        higgs_pars.Lambda1 = he->get(Par::mass1,"Lambda_1");
        higgs_pars.Lambda2 = he->get(Par::mass1,"Lambda_2");
        higgs_pars.Lambda3 = he->get(Par::mass1,"Lambda_3");
        higgs_pars.Lambda4 = he->get(Par::mass1,"Lambda_4");
        higgs_pars.Lambda5 = he->get(Par::mass1,"Lambda_5");
        higgs_pars.Lambda6 = he->get(Par::mass1,"Lambda_6");
        higgs_pars.Lambda7 = he->get(Par::mass1,"Lambda_7");
        higgs_pars.M11_2 = he->get(Par::mass1,"M11_2");
        higgs_pars.M22_2 = he->get(Par::mass1,"M22_2");
        higgs_pars.M12_2 = he->get(Par::mass1,"M12_2");
    }

    inline void init_THDM_object_SM_like(const double m_h, const std::unique_ptr<SubSpectrum>& he, const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, THDMC_1_7_0::THDM* THDM_object) {
      THDM_object->set_yukawas_type(1);
      set_SM(he,SM,sminputs,THDM_object);
      THDM_object->set_param_sm(m_h);
    }

    inline void init_THDM_spectrum_container(THDM_spectrum_container& container, const Spectrum& spec, const int yukawa_type, const double scale) {
      container.he = spec.clone_HE(); // Copy "high-energy" SubSpectrum
      if(scale>0.0) container.he->RunToScale(scale);
      container.SM = spec.clone_LE(); // Copy "low-energy" SubSpectrum 
      container.sminputs = spec.get_SMInputs();   
      container.yukawa_type = yukawa_type;
      init_higgs_basis_pars(container.he, container.higgs_pars);
      init_THDM_object(container.he, container.SM, container.sminputs, container.yukawa_type, container.THDM_object);
    }

    inline void init_THDM_spectrum_container(THDM_spectrum_container& container, const Spectrum& spec, const int yukawa_type) {
      init_THDM_spectrum_container(container, spec, yukawa_type, 0.0);
    }

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
         else std::cout << "entry not filled" << std::endl;
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
         const std::vector<std::string> higgs_basis_keys{"Lambda1","Lambda2","Lambda3","Lambda4","Lambda5","Lambda6","Lambda7","M12_2","tanb"};
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
         else{
            // fail // TODO: Handle this case better
            std::cout << "THDM_Spec_helper throwing error: " << "Cannot fill_generic_THDM_basis" << std::endl; 
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
            fill_generic_THDM_basis(input_basis, sminputs);
            fill_higgs_THDM_basis(input_basis, sminputs);
         }
         else{
            // fail
            std::cout << "THDM_Spec_helper throwing error: " << "Cannot fill_higgs_THDM_basis" << std::endl; 
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
            std::cout << "GAMBIT(mA2): " << m12_2 << " | " << sb << " | " << cb << " | " << v2 << " | " << lam5 << " | " << lam6 << " | " << ctb<< " | " << lam7 << " | " << tb << std::endl;
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
            fill_generic_THDM_basis(input_basis, sminputs);
            fill_physical_THDM_basis(input_basis, sminputs);
         }
         else{
            // fail
            std::cout << "THDM_Spec_helper throwing error: " << "Cannot fill_physical_THDM_basis" << std::endl; 
         }
    }
      
    inline void generate_THDM_spectrum_tree_level(std::map<std::string, double>& basis, const SMInputs& sminputs) {
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
         double Lambda1 = basis["Lambda1"], Lambda3 = basis["Lambda3"], Lambda4 = basis["Lambda4"], Lambda5 = basis["Lambda5"];
         double Lambda6 = basis["Lambda6"], M22_2 = basis["M22_2"];
         double mC_2 = M22_2 + 0.5*v2*Lambda3;
         double mA_2 = mC_2 - 0.5*v2*(Lambda5 - Lambda4);
         // double tan2ba = (2.0*Lambda6*v2)/(mA_2 + (Lambda5-Lambda1)*v2);
         // double s2ba = (2.0*Lambda6*v2)/sqrt(pow((mA_2 + (Lambda5-Lambda1)*v2),2) + 4.0*pow(Lambda6,2)*v2*v2);
         // double c2ba = -(mA_2+(Lambda5-Lambda1)*v2)/sqrt(pow((mA_2 + (Lambda5-Lambda1)*v2),2) + 4.0*pow(Lambda6,2)*v2*v2);
         // double ba = 0.5*acos(c2ba);
         // double alpha = beta - ba;

         double s2ba = -2.*Lambda6*v2, c2ba = -(mA_2+(Lambda5-Lambda1)*v2);
         // std::cout << "GAMBIT | s2ba: " << s2ba << " | c2ba " << c2ba << std::endl;
         double ba = 0.5*atan2(s2ba,c2ba);
         double alpha = beta - ba;

         // if (alpha > M_PI/2) alpha = alpha - M_PI;
         basis["alpha"] = alpha;
         basis["sba"] = sin(beta-alpha);
    }

   } // end SpecBit namespace
} // end Gambit namespace

#endif