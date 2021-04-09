//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for 2HDMC 1.8.0 backend
///
///  *********************************************
///
///  Authors (add name and sate if you modify):
///
///  \author Filip Rjaec
///  \date 2020 Jan
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Apr
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/THDMC_1_8_0.hpp"

// #define THDMC_DEBUG

BE_NAMESPACE
{
  // fills the THDM spectrum container
  // if the scale value is greater than zero we run our spectrum to this enegry
  // for an SM-like model set SM_like to the Higgs number that you would like to use as the SM-Higgs
  void init_THDM_spectrum_container_CONV(THDM_spectrum_container &container, const Spectrum &spec, int yukawa_type, double scale=0.0, int SM_like=0)
  {
      
    // copy over the high energy, low energy spectra and sm inputs into the container
    container.he = spec.clone_HE(); 
    container.SM = spec.clone_LE();
    container.sminputs = spec.get_SMInputs();  

    // if we want to run the spectrum to scale do so here
    if(scale>0.0)
    {
      container.he->RunToScale(scale);
    }

    // copy the Yukawa type into the container
    if (SM_like < 1)
    {
      container.yukawa_type = yukawa_type;
    }

    // for a SM-like model the yukawa type is 1
    else
    {
      container.yukawa_type = 1;
    }

    // add the Higgs basis parameters to the container via the higgs par struct
    // TODO: This is not needed in THDMC as far as I can see
    /*container.higgs_pars.Lambda1 = container.he->get(Par::mass1,"Lambda1");
    container.higgs_pars.Lambda2 = container.he->get(Par::dimensionless,"Lambda2");
    container.higgs_pars.Lambda3 = container.he->get(Par::dimensionless,"Lambda3");
    container.higgs_pars.Lambda4 = container.he->get(Par::dimensionless,"Lambda4");
    container.higgs_pars.Lambda5 = container.he->get(Par::dimensionless,"Lambda5");
    container.higgs_pars.Lambda6 = container.he->get(Par::dimensionless,"Lambda6");
    container.higgs_pars.Lambda7 = container.he->get(Par::dimensionless,"Lambda7");
    container.higgs_pars.M11_2 = container.he->get(Par::mass1,"M11_2");
    container.higgs_pars.M22_2 = container.he->get(Par::mass1,"M22_2");
    container.higgs_pars.M12_2 = container.he->get(Par::mass1,"M12_2");*/

    // fill THDM parameters into the 2HDMC
    // both generic and physical parameters are filled using the added set_param_full method
    // the use of basis transformations between the generic and physical basis have been patched
    // to not occur when set_param_full has been used
    if (SM_like < 1)
    {
      double lambda1 = container.he->get(Par::dimensionless, "lambda1");
      double lambda2 = container.he->get(Par::dimensionless, "lambda2");
      double lambda3 = container.he->get(Par::dimensionless, "lambda3");
      double lambda4 = container.he->get(Par::dimensionless, "lambda4");
      double lambda5 = container.he->get(Par::dimensionless, "lambda5");
      double tan_beta = container.he->get(Par::dimensionless, "tanb");
      double lambda6 = container.he->get(Par::dimensionless, "lambda6");
      double lambda7 = container.he->get(Par::dimensionless, "lambda7");
      double m12_2 = container.he->get(Par::mass1,"m12_2");
      // TODO: Why running masses and not pole masses?
      double mh = container.he->get(Par::mass1, "h0", 1);
      double mH = container.he->get(Par::mass1, "h0", 2);
      double mA = container.he->get(Par::mass1, "A0");
      double mC = container.he->get(Par::mass1, "H+");
      double alpha = container.he->get(Par::dimensionless, "alpha");
      double beta = container.he->get(Par::dimensionless, "beta");
      double sba = sin(beta - alpha);
      container.THDM_object->set_param_full(lambda1, lambda2, lambda3, lambda4, lambda5, lambda6, lambda7, \
                              m12_2, tan_beta, mh, mH, mA, mC, sba);
    }

    // set yukawa type in 2HDMC
    container.THDM_object->set_yukawas_type(container.yukawa_type);

    // we may not want to set the SM (use the default 2hdmc values) when debugging
    bool set_SM = true;
    #ifdef THDMC_DEBUG
      set_SM = false;
    #endif
    if (set_SM)
    {
      // get a pointer to the 2HDMC SM class
      THDMC_1_8_0::SM* SM_object = container.THDM_object->get_SM_pointer();

      // set parameters in the SM class to match ours
      SM_object->set_alpha(1/(container.sminputs.alphainv));
      SM_object->set_alpha_s(container.sminputs.alphaS);
      // get vev from high energy spectrum & set GF based off VEV
      double vev = container.he->get(Par::mass1, "vev");
      double GF = 1.0/(sqrt(2)*pow(vev,2.0));
      SM_object->set_GF(GF);
      SM_object->set_MZ(container.SM->get(Par::Pole_Mass,"Z0"));
      SM_object->set_MW(container.SM->get(Par::Pole_Mass,"W+"));

      // set lepton pole masses
      SM_object->set_lmass_pole(1,container.SM->get(Par::Pole_Mass,"e-_1"));
      SM_object->set_lmass_pole(2,container.SM->get(Par::Pole_Mass,"e-_2"));
      SM_object->set_lmass_pole(3,container.SM->get(Par::Pole_Mass,"e-_3"));

      // bottom (pole) mass - from low energy spectrum
      SM_object->set_qmass_pole(5,container.SM->get(Par::Pole_Mass,"d_3"));
      // top (pole) mass - from low energy spectrum
      SM_object->set_qmass_pole(6,container.SM->get(Par::Pole_Mass,"u_3"));

      // strange and charm (ms_bar) masses - from sm inputs
      SM_object->set_qmass_msbar(3,container.sminputs.mS);
      SM_object->set_qmass_msbar(4,container.sminputs.mCmC);

      // up and down ma (ms_bar) masses are calculated from the Yukawa's in the high energy spectrum
      // TODO: All unnecessary, remove it
      /*double tanb = container.he->get(Par::dimensionless, "tanb");
      const double sqrt2v = pow(2.0,0.5)/vev, b = atan(tanb);
      const double cb = cos(b), sb = sin(b);
      double beta_scaling_u = sb, beta_scaling_d = sb;
      switch(container.yukawa_type)
      {
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
      }*/
      // TODO: This is redundant and does not work
      /*const double Yd1 = container.he->get(Par::dimensionless, "Yd", 1, 1);
      const double Yu1 = container.he->get(Par::dimensionless, "Yu", 1, 1);
      const double mu1 = Yu1 * beta_scaling_u/sqrt2v;
      const double md1 = Yd1 * beta_scaling_d/sqrt2v;
      SM_object->set_qmass_msbar(1,md1);
      SM_object->set_qmass_msbar(2,mu1);*/
      SM_object->set_qmass_msbar(1,container.he->get(Par::mass1, "d_1"));
      SM_object->set_qmass_msbar(2,container.he->get(Par::mass1, "u_1"));
    }

    // Set up an SM like model if the SM_like parameter is set to a neutral Higgs number
    if (SM_like > 0 && SM_like < 4)
    {
      // fetch the neutral Higgs mass & set up the SM-like THDM in the 2HDMC based upon this
      const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
      const double m_h = container.he->get(Par::mass1, sHneut[SM_like-1]);
      container.THDM_object->set_param_sm(m_h);
    }

    #ifdef THDMC_DEBUG
      if (SM_like == 0)
      {
        // params in all bases
        container.THDM_object->print_param_phys();
        container.THDM_object->print_param_gen();
        container.THDM_object->print_param_higgs();
        container.THDM_object->get_alpha();
        // set up decay table
        THDMC_1_8_0::DecayTableTHDM decay_table_2hdmc(*(container.THDM_object));
        // widths
        decay_table_2hdmc.print_width(1);
        decay_table_2hdmc.print_width(2);
        decay_table_2hdmc.print_width(3);
        decay_table_2hdmc.print_width(4);
        // decays
        decay_table_2hdmc.print_decays(1);
        decay_table_2hdmc.print_decays(2);
        decay_table_2hdmc.print_decays(3);
        decay_table_2hdmc.print_decays(4);
      }
    #endif

  }

}
END_BE_NAMESPACE

// Initialisation function (definition)
BE_INI_FUNCTION
{

}
END_BE_INI_FUNCTION
