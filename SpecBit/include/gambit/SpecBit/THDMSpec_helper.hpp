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
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
///
///  *****************************å****************

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
      // 2. If not in SpecBit namespace append to function. [MODULARITY BREAKING]
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

      // creates & fills to 2HDMC SM object
      inline void set_SM(const std::unique_ptr<SubSpectrum>& he, 
         const std::unique_ptr<SubSpectrum>& SM, 
         const SMInputs& sminputs, THDMC_1_8_0::THDM* THDM_object);

      // Takes in the spectrum and fills a THDM object which is defined
      // in 2HDMC. Any 2HDMC functions can then be called on this object.
      inline void init_THDM_object(const std::unique_ptr<SubSpectrum>& he, 
         const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, 
         const int yukawa_type, THDMC_1_8_0::THDM* THDM_object);

      // // Initializes the THDM pars struct 
      // inline void init_higgs_basis_pars(const std::unique_ptr<SubSpectrum>& he, 
      //    higgs_basis_pars& higgs_pars);

      // create a THDM object in the SM limit
      inline void init_THDM_object_SM_like(const double m_h, 
         const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, 
         THDMC_1_8_0::THDM* THDM_object);

      // Creates a THDM Spectrum Constainer with no runnning scale
      inline void init_THDM_spectrum_container(THDM_spectrum_container& container, 
         const Spectrum& spec, const int yukawa_type);

      // Creates a THDM Spectrum Container
      inline void init_THDM_spectrum_container(THDM_spectrum_container& container, 
         const Spectrum& spec, const int yukawa_type, const double scale);

      // function definitions

      inline void set_SM(const std::unique_ptr<SubSpectrum>& he, const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, THDMC_1_8_0::THDM* THDM_object){
      THDMC_1_8_0::SM* SM_object = THDM_object->get_SM_pointer();

      SM_object->set_alpha(1/(sminputs.alphainv));
      SM_object->set_alpha_s(sminputs.alphaS);

      // get vev from high energy spectrum & set GF based off VEV
      double vev = he->get(Par::mass1, "vev");
      double GF = 1.0/(sqrt(2)*pow(vev,2.0));
      SM_object->set_GF(GF); //sminputs.GF);
      
      SM_object->set_MZ(SM->get(Par::Pole_Mass,"Z0"));
      SM_object->set_MW(SM->get(Par::Pole_Mass,"W+"));

      // lepton masses
      SM_object->set_lmass_pole(1,SM->get(Par::Pole_Mass,"e-_1"));
      SM_object->set_lmass_pole(2,SM->get(Par::Pole_Mass,"e-_2"));
      SM_object->set_lmass_pole(3,SM->get(Par::Pole_Mass,"e-_3"));

      // quark pole masses
      // SM_object->set_qmass_pole(3,SM->get(Par::Pole_Mass,"d_2")); //s
      // SM_object->set_qmass_pole(4,SM->get(Par::Pole_Mass,"u_2")); //c
      SM_object->set_qmass_pole(5,SM->get(Par::Pole_Mass,"d_3")); //b
      SM_object->set_qmass_pole(6,SM->get(Par::Pole_Mass,"u_3")); //t

      // quark running masses

      SM_object->set_qmass_msbar(3,sminputs.mS); //s
      SM_object->set_qmass_msbar(4,sminputs.mCmC); //c

      double tanb = he->get(Par::dimensionless, "tanb");
      const double sqrt2v = pow(2.0,0.5)/vev, b = atan(tanb);
      const double cb = cos(b), sb = sin(b);

      double beta_scaling_u = sb, beta_scaling_d = sb;
      
      switch(THDM_object->get_yukawas_type()) {
         case 1:
            break;
         case 2:
            beta_scaling_d = cb;
            break;
         case 3:
            break;
         case 4:
            beta_scaling_d = cb;
            break;
         }

      double Yd1 = he->get(Par::dimensionless, "Yd", 1, 1);
      double Yu1 = he->get(Par::dimensionless, "Yu", 1, 1);

      // double Yd2 = he->get(Par::dimensionless, "Yd", 2, 2);
      // double Yu2 = he->get(Par::dimensionless, "Yu", 2, 2);

      double mu1 = Yu1 * beta_scaling_u/sqrt2v;
      // double mu2 = Yu2 * beta_scaling_u/sqrt2v;

      double md1 = Yd1 * beta_scaling_d/sqrt2v;
      // double md2 = Yd2 * beta_scaling_d/sqrt2v;

      SM_object->set_qmass_msbar(1,md1); //d
      SM_object->set_qmass_msbar(2,mu1); //u
      // SM_object->set_qmass_pole(3,md2); //s
      // SM_object->set_qmass_pole(4,mu2); //c

    }

    inline void init_THDM_object(const std::unique_ptr<SubSpectrum>& he, const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, const int yukawa_type, THDMC_1_8_0::THDM* THDM_object) {
      double lambda_1 = he->get(Par::mass1,"lambda_1");
      double lambda_2 = he->get(Par::mass1,"lambda_2");
      double lambda_3 = he->get(Par::mass1, "lambda_3");
      double lambda_4 = he->get(Par::mass1, "lambda_4");
      double lambda_5 = he->get(Par::mass1, "lambda_5");
      double tan_beta = he->get(Par::dimensionless, "tanb");
      double lambda_6 = he->get(Par::mass1, "lambda_6");
      double lambda_7 = he->get(Par::mass1, "lambda_7");
      double m12_2 = he->get(Par::mass1,"m12_2");
      double mh = he->get(Par::mass1, "h0", 1);
      double mH = he->get(Par::mass1, "h0", 2);
      double mA = he->get(Par::mass1, "A0");
      double mC = he->get(Par::mass1, "H+");
      double alpha = he->get(Par::dimensionless, "alpha");
      double sba = sin(he->get(Par::dimensionless, "beta") - alpha);
      THDM_object->set_param_full(lambda_1, lambda_2, lambda_3, lambda_4, lambda_5, lambda_6, lambda_7, \
                                  m12_2, tan_beta, mh, mH, mA, mC, sba);
      THDM_object->set_yukawas_type(yukawa_type);
      set_SM(he,SM,sminputs,THDM_object);  
    }

    inline void init_THDM_object_SM_like(const double m_h, const std::unique_ptr<SubSpectrum>& he, const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, THDMC_1_8_0::THDM* THDM_object) {
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

   } // end SpecBit namespace
} // end Gambit namespace

#endif