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
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/THDMC_1_8_0.hpp"

BE_NAMESPACE
{
    void init_THDM_spectrum_container_CONV(THDM_spectrum_container &container, Spectrum &spec, int yukawa_type, double scale, int SM_like) {

        container.he = spec.clone_HE(); // Copy "high-energy" SubSpectrum

        if(scale>0.0) {
            container.he->RunToScale(scale);
        }

        container.SM = spec.clone_LE(); // Copy "low-energy" SubSpectrum 
        container.sminputs = spec.get_SMInputs();   

        if (SM_like < 1) {
            container.yukawa_type = yukawa_type;
        }
        else {
            container.yukawa_type = 1;
        }

        if (SM_like < 1) {
        // fill THDM class
            double lambda_1 = container.he->get(Par::mass1,"lambda_1");
            double lambda_2 = container.he->get(Par::mass1,"lambda_2");
            double lambda_3 = container.he->get(Par::mass1, "lambda_3");
            double lambda_4 = container.he->get(Par::mass1, "lambda_4");
            double lambda_5 = container.he->get(Par::mass1, "lambda_5");
            double tan_beta = container.he->get(Par::dimensionless, "tanb");
            double lambda_6 = container.he->get(Par::mass1, "lambda_6");
            double lambda_7 = container.he->get(Par::mass1, "lambda_7");
            double m12_2 = container.he->get(Par::mass1,"m12_2");
            double mh = container.he->get(Par::mass1, "h0", 1);
            double mH = container.he->get(Par::mass1, "h0", 2);
            double mA = container.he->get(Par::mass1, "A0");
            double mC = container.he->get(Par::mass1, "H+");
            double alpha = container.he->get(Par::dimensionless, "alpha");
            double sba = sin(container.he->get(Par::dimensionless, "beta") - alpha);
            container.THDM_object->set_param_full(lambda_1, lambda_2, lambda_3, lambda_4, lambda_5, lambda_6, lambda_7, \
                                    m12_2, tan_beta, mh, mH, mA, mC, sba);
            
        }
        container.THDM_object->set_yukawas_type(container.yukawa_type);

        // fill SM class
        THDMC_1_8_0::SM* SM_object = container.THDM_object->get_SM_pointer();

        SM_object->set_alpha(1/(container.sminputs.alphainv));
        SM_object->set_alpha_s(container.sminputs.alphaS);

        // get vev from high energy spectrum & set GF based off VEV
        double vev = container.he->get(Par::mass1, "vev");
        double GF = 1.0/(sqrt(2)*pow(vev,2.0));
        SM_object->set_GF(GF); //sminputs.GF);
        
        SM_object->set_MZ(container.SM->get(Par::Pole_Mass,"Z0"));
        SM_object->set_MW(container.SM->get(Par::Pole_Mass,"W+"));

        // lepton masses
        SM_object->set_lmass_pole(1,container.SM->get(Par::Pole_Mass,"e-_1"));
        SM_object->set_lmass_pole(2,container.SM->get(Par::Pole_Mass,"e-_2"));
        SM_object->set_lmass_pole(3,container.SM->get(Par::Pole_Mass,"e-_3"));

        // quark pole masses
        // SM_object->set_qmass_pole(3,SM->get(Par::Pole_Mass,"d_2")); //s
        // SM_object->set_qmass_pole(4,SM->get(Par::Pole_Mass,"u_2")); //c
        SM_object->set_qmass_pole(5,container.SM->get(Par::Pole_Mass,"d_3")); //b
        SM_object->set_qmass_pole(6,container.SM->get(Par::Pole_Mass,"u_3")); //t

        // quark running masses

        SM_object->set_qmass_msbar(3,container.sminputs.mS); //s
        SM_object->set_qmass_msbar(4,container.sminputs.mCmC); //c

        double tanb = container.he->get(Par::dimensionless, "tanb");
        const double sqrt2v = pow(2.0,0.5)/vev, b = atan(tanb);
        const double cb = cos(b), sb = sin(b);

        double beta_scaling_u = sb, beta_scaling_d = sb;
        
        switch(container.yukawa_type) {
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

        double Yd1 = container.he->get(Par::dimensionless, "Yd", 1, 1);
        double Yu1 = container.he->get(Par::dimensionless, "Yu", 1, 1);

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

        if (SM_like > 0) {
             // Set up neutral Higgses 
            const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
            const double m_h = container.he->get(Par::mass1, sHneut[SM_like]);
            container.THDM_object->set_param_sm(m_h);
        }

        // fill higgs basis for quick access
        container.higgs_pars.Lambda1 = container.he->get(Par::mass1,"Lambda_1");
        container.higgs_pars.Lambda2 = container.he->get(Par::mass1,"Lambda_2");
        container.higgs_pars.Lambda3 = container.he->get(Par::mass1,"Lambda_3");
        container.higgs_pars.Lambda4 = container.he->get(Par::mass1,"Lambda_4");
        container.higgs_pars.Lambda5 = container.he->get(Par::mass1,"Lambda_5");
        container.higgs_pars.Lambda6 = container.he->get(Par::mass1,"Lambda_6");
        container.higgs_pars.Lambda7 = container.he->get(Par::mass1,"Lambda_7");
        container.higgs_pars.M11_2 = container.he->get(Par::mass1,"M11_2");
        container.higgs_pars.M22_2 = container.he->get(Par::mass1,"M22_2");
        container.higgs_pars.M12_2 = container.he->get(Par::mass1,"M12_2");
    }

}
END_BE_NAMESPACE

// Initialisation function (definition)
// BE_INI_FUNCTION
// {

// }
// END_BE_INI_FUNCTION
