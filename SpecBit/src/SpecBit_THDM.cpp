//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit
///
///  SpecBit module functions related to the
///  THDM General, Type I, II, Lepton Specific & Flipped
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Filip Rajec
///  \date 2016-2018
///
///  *********************************************

#include <string>
#include <sstream>
#include <cmath>
#include <complex>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_permute.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Elements/slhaea_helpers.hpp"
#include "gambit/Utils/stream_overloads.hpp" // Just for more convenient output to logger
#include "gambit/Utils/util_macros.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/QedQcdWrapper.hpp"
#include "gambit/Models/SimpleSpectra/SMHiggsSimpleSpec.hpp"
#include "gambit/Models/SimpleSpectra/THDMSimpleSpec.hpp"
#include "gambit/SpecBit/THDMSpec.hpp"
#include "gambit/SpecBit/model_files_and_boxes.hpp"
#include "gambit/Utils/statistics.hpp"
//#include "gambit/Elements/numerical_constants.hpp"
// #TO DO# CREATE AND INCLUDE ANY HEADERS FOR THDM
//#include "gambit/SpecBit/SMskeleton.hpp"
#include "flexiblesusy/src/spectrum_generator_settings.hpp"
// Flexible SUSY stuff (should not be needed by the rest of gambit)
#include "flexiblesusy/src/ew_input.hpp"
#include "flexiblesusy/src/lowe.h" // From softsusy; used by flexiblesusy
#include "flexiblesusy/src/numerics2.hpp"
// #include "flexiblesusy/src/two_loop_corrections.hpp"
#include "flexiblesusy/models/THDM_II/THDM_II_input_parameters.hpp"
#include "flexiblesusy/src/problems.hpp"

#define L_MAX 1e50
#define PI 3.14159265

// Switch for debug mode
// #define SPECBIT_DEBUG
#define FS_THROW_POINT

#ifdef SPECBIT_DEBUG
  bool print_debug_checkpoints = true;
#else
  bool print_debug_checkpoints = false;
#endif

namespace Gambit
{

  namespace SpecBit
  {
    using namespace LogTags;
    using namespace flexiblesusy;
    using namespace std;

    enum string_code {
      //--CHI SQAURED Type
      less_than,
      greater_than,
      distance_from,
      observable,
      bound,
    };

    enum yukawa_type{
      type_I = 1,
      type_II,
      lepton_specific,
      flipped,
      type_III,
    };

    double get_chi(const double value, string_code type, string_code sign, const double value_bound, const double error) {
      double chi = 0.0;
      const bool use_one_sigma_bound = false;
      double sigma_limit = 0.64, sigma_rescale = 0.6;
      if (!use_one_sigma_bound) {
        sigma_limit = 1.; sigma_rescale = 1.;
      }

      switch (type) {
        case observable:
          switch (sign) {
                case less_than:
                    if(value<value_bound) {
                        return 0;
                    }
                    else {
                        return pow(((value-value_bound)/error),2);
                    }
                break;
                case greater_than:
                    if(value>value_bound) {
                        return 0;
                        }
                    else {
                        return pow(((value-value_bound)/error),2);
                    }
                break;
            case distance_from:
              chi = pow(((value-value_bound)/error),2);
                break;
            default:
              return chi;
            }
          break;
        case bound:
          switch (sign)
          {
            case less_than:
              if(value<(value_bound/sigma_limit)) {
                return 0;
              }
              else {
                return pow(((sigma_rescale*value)/(value_bound)-1.0),2);
              }
            break;
            case greater_than:
              if(value>(value_bound/sigma_limit)) {
                return 0;
              }
              else {
                return pow(((sigma_rescale*value)/(value_bound)-1.0),2);
              }
            break;
            case distance_from:
              return pow(((sigma_rescale*value)/(value_bound)-1.0),2);
            break;
            default:
              return chi;
          }
          break;
        default:
          return chi;
      }
      return chi;
    }

    void get_CKM_from_Wolfenstein_parameters(complex<double> CKM[2][2], double lambda, double A, double rho, double eta) {
      std::complex<double> i_eta(0, eta);
      CKM[0][0] = 1 - pow(lambda,2)/2;
      CKM[0][1] = lambda;
      CKM[0][2] = A*pow(lambda,3)*(rho-i_eta);
      CKM[1][0] = -lambda;
      CKM[1][1] = 1 - pow(lambda,2)/2;
      CKM[1][2] = A*pow(lambda,2);
      CKM[2][0] = A*pow(lambda,3)*(1-rho-i_eta);
      CKM[2][1] = -A*pow(lambda,2);
      CKM[2][2] = 1;
    }

    //calculate sba
    double get_sba(double tanb, double alpha) {
        return sin(atan(tanb)-alpha);
    }


    /// Get a Spectrum object wrapper for the THDM model
    void get_THDM_spectrum(Spectrum &result) { 
      if (print_debug_checkpoints) cout << "Checkpoint: 4" << endl;
      namespace myPipe = Pipes::get_THDM_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // SoftSUSY object used to set quark and lepton masses and gauge
      // couplings in QEDxQCD effective theory
      softsusy::QedQcd oneset;

      // Fill QedQcd object with SMInputs values
      setup_QedQcd(oneset,sminputs);

      // Run everything to Mz
      oneset.toMz();

      // Create a SubSpectrum object to wrap the qedqcd object
      // Attach the sminputs object as well, so that SM pole masses can be passed on (these aren't easily
      // extracted from the QedQcd object, so use the values that we put into it.)
      QedQcdWrapper qedqcdspec(oneset,sminputs);

      // Initialise an object to carry the THDM sector information
      Models::THDMModel thdm_model;

      double lambda_1 = *myPipe::Param.at("lambda_1");
      double lambda_2 = *myPipe::Param.at("lambda_2");
      double lambda_3 = *myPipe::Param.at("lambda_3");
      double lambda_4 = *myPipe::Param.at("lambda_4");
      double lambda_5 = *myPipe::Param.at("lambda_5");
      double lambda_6 = *myPipe::Param.at("lambda_6");
      double lambda_7 = *myPipe::Param.at("lambda_7");
      double m12_2 = *myPipe::Param.at("m12_2");
      double tan_beta = *myPipe::Param.at("tanb");

      //Check Yukawa Type Validity
      int yukawa_type = myPipe::runOptions->getValueOrDef<int>(1, "yukawa_type");
      if( yukawa_type < 1 || yukawa_type > 4 ) {
        std::ostringstream msg;
        msg << "Tried to set the Yukawa Type to "<< yukawa_type <<" . Yukawa Type should a number 1-4.";
        SpecBit_error().raise(LOCAL_INFO,msg.str());
        exit(1);
      }

      // quantities needed to fill container spectrum, intermediate calculations
      double alpha_em = 1.0 / sminputs.alphainv;
      double C = alpha_em * Pi / (sminputs.GF * pow(2,0.5));
      double sinW2 = 0.5 - pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double cosW2 = 0.5 + pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double e = pow( 4*Pi*( alpha_em ),0.5) ;

      thdm_model.lambda1           = lambda_1;
      thdm_model.lambda2           = lambda_2;
      thdm_model.lambda3           = lambda_3;
      thdm_model.lambda4           = lambda_4;
      thdm_model.lambda5           = lambda_5;
      thdm_model.tanb              = tan_beta;
      thdm_model.m12_2             = m12_2;
      thdm_model.lambda6           = lambda_6;
      thdm_model.lambda7           = lambda_7;

      // Standard model
      thdm_model.sinW2 = sinW2;

      // gauge couplings
      thdm_model.g1 = e / sinW2;
      thdm_model.g2 = e / cosW2;
      thdm_model.g3   = pow( 4*Pi*( sminputs.alphaS ),0.5) ;

      // Yukawas
      double vev        = 1. / sqrt(sqrt(2.)*sminputs.GF);
      double sqrt2v = pow(2.0,0.5)/vev;
      thdm_model.Yu[0] = sqrt2v * sminputs.mU;
      thdm_model.Yu[1] = sqrt2v * sminputs.mCmC;
      thdm_model.Yu[2] = sqrt2v * sminputs.mT;
      thdm_model.Ye[0] = sqrt2v * sminputs.mE;
      thdm_model.Ye[1] = sqrt2v * sminputs.mMu;
      thdm_model.Ye[2] = sqrt2v * sminputs.mTau;
      thdm_model.Yd[0] = sqrt2v * sminputs.mD;
      thdm_model.Yd[1] = sqrt2v * sminputs.mS;
      thdm_model.Yd[2] = sqrt2v * sminputs.mBmB;

      // Create a SubSpectrum object to wrap the EW sector information
      Models::THDMSimpleSpec thdm_spec(thdm_model);

      // Create full Spectrum object from components above
      // Note: SubSpectrum objects cannot be copied, but Spectrum
      // objects can due to a special copy constructor which does
      // the required cloning of the constituent SubSpectra.
      static Spectrum full_spectrum;

      // Note subtlety! There are TWO constructors for the Spectrum object:
      // If pointers to SubSpectrum objects are passed, it is assumed that
      // these objects are managed EXTERNALLY! So if we were to do this:
      //   full_spectrum = Spectrum(&qedqcdspec,&singletspec,sminputs);
      // then the SubSpectrum objects would end up DELETED at the end of
      // this scope, and we will get a segfault if we try to access them
      // later. INSTEAD, we should just pass the objects themselves, and
      // then they will be CLONED and the Spectrum object will take
      // possession of them:

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = myPipe::runOptions->getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = myPipe::runOptions->getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      full_spectrum = Spectrum(qedqcdspec,thdm_spec,sminputs,&myPipe::Param,mass_cut,mass_ratio_cut);

      result = full_spectrum;
    }

    void set_SM(const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, THDMC_1_7_0::THDM* THDM_object){
      THDMC_1_7_0::SM* SM_object = THDM_object->get_SM_pointer();
      const double md_p    = 0.0047;
      const double mu_p    = 0.0022;
      const double ms_p    = 0.096;
      const double mc_p    = 1.67; // (Borzumati: 1.41)
      const double mc_bar    = 1.273; //1802.04248
      const double alpha0   = 1./137.035999139;
      SM_object->set_alpha(1/(sminputs.alphainv));
      SM_object->set_alpha0(alpha0);
      SM_object->set_alpha_s(sminputs.alphaS);
      SM_object->set_GF(sminputs.GF);
      SM_object->set_MZ(SM->get(Par::Pole_Mass,"Z0"));
      SM_object->set_MW(SM->get(Par::Pole_Mass,"W+"));
      SM_object->set_lmass_pole(1,SM->get(Par::Pole_Mass,"e-_1"));
      SM_object->set_lmass_pole(2,SM->get(Par::Pole_Mass,"e-_2"));
      SM_object->set_lmass_pole(3,SM->get(Par::Pole_Mass,"e-_3"));
      SM_object->set_qmass_pole(1,md_p); //t
      SM_object->set_qmass_pole(2,mu_p); //b 
      SM_object->set_qmass_pole(3,ms_p); //t
      SM_object->set_qmass_pole(4,mc_p); //b  
      SM_object->set_qmass_pole(5,SM->get(Par::Pole_Mass,"d_3")); //t
      SM_object->set_qmass_pole(6,SM->get(Par::Pole_Mass,"u_3")); //b
      SM_object->set_qmass_msbar(1,SM->get(Par::mass1,"d_1")); //d
      SM_object->set_qmass_msbar(2,SM->get(Par::mass1,"u_1")); //u
      SM_object->set_qmass_msbar(3,SM->get(Par::mass1,"d_2")); //s
      SM_object->set_qmass_msbar(4,mc_bar); //c
      SM_object->set_qmass_msbar(5,SM->get(Par::mass1,"d_3")); //u
      SM_object->set_qmass_msbar(6,SM->get(Par::mass1,"u_3")); //s
    }

    //Takes in the spectrum and fills a THDM object which is defined
    //in 2HDMC. Any 2HDMC functions can then be called on this object.
    void init_THDM_object(const std::unique_ptr<SubSpectrum>& he, const std::unique_ptr<SubSpectrum>& SM, const SMInputs& sminputs, const int yukawa_type, THDMC_1_7_0::THDM* THDM_object) {
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
      double sba = sin(atan(tan_beta) - alpha);
      set_SM(SM,sminputs,THDM_object);
      THDM_object->set_param_full(lambda_1, lambda_2, lambda_3, lambda_4, lambda_5, lambda_6, lambda_7, \
                                  m12_2, tan_beta, mh, mH, mA, mC, sba);
      THDM_object->set_yukawas_type(yukawa_type);
    }

    struct THDM_spectrum_container {
      std::unique_ptr<SubSpectrum> he;
      std::unique_ptr<SubSpectrum> SM;
      SMInputs sminputs;
      THDMC_1_7_0::THDM* THDM_object;
      int yukawa_type;
    };

    void init_THDM_spectrum_container(THDM_spectrum_container& container, const Spectrum& spec, const int yukawa_type, const double scale) {
      container.he = spec.clone_HE(); // Copy "high-energy" SubSpectrum
      if(scale>0.0) container.he->RunToScale(scale);
      container.SM = spec.clone_LE(); // Copy "low-energy" SubSpectrum 
      container.sminputs = spec.get_SMInputs();   
      container.yukawa_type = yukawa_type;
      container.THDM_object = new THDMC_1_7_0::THDM();
      init_THDM_object(container.he, container.SM, container.sminputs, container.yukawa_type, container.THDM_object);
    }

    void fill_THDM_object(const Spectrum& spec, THDM& THDM_object, const int yukawa_type, double scale){
      // deprecated
        const std::unique_ptr<SubSpectrum> he = spec.clone_HE();
        if(scale>0.0) he->RunToScale(scale);
        const std::unique_ptr<SubSpectrum> SM = spec.clone_LE();
        const SMInputs sminputs = spec.get_SMInputs();   
        init_THDM_object(he, SM, sminputs, yukawa_type, &THDM_object);
    }

    void fill_THDM_object(const Spectrum& spec, THDM& THDM_object, const int yukawa_type){
        // deprecated
        fill_THDM_object(spec, THDM_object, yukawa_type, 0.0);
    }

    void fill_THDM_object_SM_Like_Model(const Spectrum& spec, THDM& THDM_object, int HiggsNumber, const int yukawa_type) { 
        // deprecated
        // TODO: requires rewrite of function
        if (HiggsNumber > 0 && HiggsNumber < 5) fill_THDM_object(spec, THDM_object, yukawa_type, 0.0);
            //Fills a 2HDMC object with SM-like input, makes use of the decoupling limit
            //
            // yukawa_type = 2; // for now hard code!
            // THDMC_1_7_0::SM* SM_object = THDM_object.get_SM();

            // const std::unique_ptr<SubSpectrum> SM = spec.clone_LE(); // Copy "low-energy" SubSpectrum 
            // const std::unique_ptr<SubSpectrum> he =  spec.clone_HE(); // Copy "high-energy" SubSpectrum
            // const SMInputs& sminputs   = spec.get_SMInputs();

            // // in the decoupling limit THDM-> SM
            // double m_h;

            // // which higgs mass to use as SM higgs
            // switch (HiggsNumber)
            // { if (print_debug_checkpoints) cout << "Checkpoint: 11" << endl;
            //   case 1:
            //     m_h = he->get(Par::Pole_Mass,"h0",1);
            //     break;
            //   case 2:
            //     m_h = he->get(Par::Pole_Mass,"h0",2);
            //     break;
            //   case 3:
            //     m_h = he->get(Par::Pole_Mass,"A0");
            //     break;
            //   default:
            //     m_h = he->get(Par::Pole_Mass,"h0",1);
            //     break;
            // }

            // // decouple
            // double m_H = m_h*100;
            // double m_A = m_h*100;
            // double m_Hp = m_h*100;
            // // set alignment
            // double sba = 1.0;
            // double lambda6 = 0.;
            // double lambda7 = 0.;
            // double m12_2 = 0.;
            // double tan_beta = 1.;

            // SM_object->set_alpha(1/(sminputs.alphainv));
            // SM_object->set_alpha_s(sminputs.alphaS);
            // SM_object->set_GF(sminputs.GF);
            // SM_object->set_MZ(SM->get(Par::Pole_Mass,"Z0"));
            // SM_object->set_MW(SM->get(Par::Pole_Mass,"W+"));

            // SM_object->set_lmass_pole(1,SM->get(Par::Pole_Mass,"e-_1"));
            // SM_object->set_lmass_pole(2,SM->get(Par::Pole_Mass,"e-_2"));
            // SM_object->set_lmass_pole(3,SM->get(Par::Pole_Mass,"e-_3"));

            // SM_object->set_qmass_msbar(2,sminputs.mU); //u
            // SM_object->set_qmass_msbar(1,sminputs.mD); //d
            // SM_object->set_qmass_msbar(4,sminputs.mCmC); //c
            // SM_object->set_qmass_msbar(3,sminputs.mS); //s
            // SM_object->set_qmass_pole(6,SM->get(Par::Pole_Mass,"u_3")); //t
            // SM_object->set_qmass_pole(5,SM->get(Par::Pole_Mass,"d_3")); //b

            // complex<double> CKMMatrix[2][2];
            // get_CKM_from_Wolfenstein_parameters(CKMMatrix, sminputs.CKM.lambda, sminputs.CKM.A, sminputs.CKM.rhobar, sminputs.CKM.etabar);
            // // SM_object->set_CKM(abs(CKMMatrix[0][0]), abs(CKMMatrix[0][1]), abs(CKMMatrix[0][2]), abs(CKMMatrix[1][0]), abs(CKMMatrix[1][1]),
            //         // abs(CKMMatrix[1][2]), abs(CKMMatrix[2][0]), abs(CKMMatrix[2][1]), abs(CKMMatrix[2][2]));

            // THDM_object.set_param_phys(m_h, m_H, m_A, m_Hp, sba, lambda6, lambda7, m12_2, tan_beta);
            // THDM_object.set_yukawas_type(yukawa_type);
      }

    // Constraint helper functions
    // Necessary forward declaration
    double Z_w(void * params);

    // Custom functions to extend GSL
    std::complex<double> gsl_complex_to_complex_double(const gsl_complex c) {
      return std::complex<double>(GSL_REAL(c), GSL_IMAG(c));
    }

    std::complex<double> gsl_matrix_complex_trace_complex(const gsl_matrix_complex* m1){
      return gsl_complex_to_complex_double(gsl_matrix_complex_get(m1,0,0)) + \
        gsl_complex_to_complex_double(gsl_matrix_complex_get(m1,1,1)) + \
        gsl_complex_to_complex_double(gsl_matrix_complex_get(m1,2,2));
    }

    // TODO: conj needs to be added to dagger routine
    std::vector<std::complex<double>> get_trace_of_yukawa_matrices(THDM_spectrum_container& container) {
      std::vector<std::complex<double>> trace;
      std::complex<double> tr_u, tr_d, tr_l, tr_u2, tr_d2, tr_l2, tr_du;
      gsl_matrix_complex *y_u, *y_d, *y_l, *y_u_dagger, *y_d_dagger, *y_l_dagger;
      const int size = 3;

      const double mt = container.SM->get(Par::Pole_Mass, "u_3");
      const std::vector<double> m_u = {0.0,1.42,mt};
      const std::vector<double> m_d = {0.0,0.1,4.75};
      const std::vector<double> m_l = {0.510998918E-3,0.105658367,1.77684};
      const double beta = atan(container.he->get(Par::dimensionless, "tanb"));
      const double vev = 246.0;

      y_u = gsl_matrix_complex_alloc(size, size);
      y_d = gsl_matrix_complex_alloc(size, size);
      y_l = gsl_matrix_complex_alloc(size, size);
      y_u_dagger = gsl_matrix_complex_alloc(size, size);
      y_d_dagger = gsl_matrix_complex_alloc(size, size);
      y_l_dagger = gsl_matrix_complex_alloc(size, size);

      // set yukawa - up
      gsl_complex y_u_11;
      GSL_SET_REAL(&y_u_11, m_u[0]*sqrt(2)/vev/sin(beta));
      GSL_SET_IMAG(&y_u_11, 0.0);

      gsl_complex y_u_22;
      GSL_SET_REAL(&y_u_22, m_u[1]*sqrt(2)/vev/sin(beta));
      GSL_SET_IMAG(&y_u_22, 0.0);

      gsl_complex y_u_33;
      GSL_SET_REAL(&y_u_33, m_u[2]*sqrt(2)/vev/sin(beta));
      GSL_SET_IMAG(&y_u_33, 0.0);

      gsl_matrix_complex_set_zero(y_u);

      gsl_matrix_complex_set(y_u,0,0,y_u_11);
      gsl_matrix_complex_set(y_u,1,1,y_u_22);
      gsl_matrix_complex_set(y_u,2,2,y_u_33);

      gsl_matrix_complex_transpose_memcpy(y_u_dagger, y_u);

      // set yukawa - down
      gsl_complex y_d_11;
      GSL_SET_REAL(&y_d_11, m_d[0]*sqrt(2)/vev/cos(beta));
      GSL_SET_IMAG(&y_d_11, 0.0);

      gsl_complex y_d_22;
      GSL_SET_REAL(&y_d_22, m_d[1]*sqrt(2)/vev/cos(beta));
      GSL_SET_IMAG(&y_d_22, 0.0);

      gsl_complex y_d_33;
      GSL_SET_REAL(&y_d_33, m_d[2]*sqrt(2)/vev/cos(beta));
      GSL_SET_IMAG(&y_d_33, 0.0);

      gsl_matrix_complex_set_zero(y_d);

      gsl_matrix_complex_set(y_d,0,0,y_d_11);
      gsl_matrix_complex_set(y_d,1,1,y_d_22);
      gsl_matrix_complex_set(y_d,2,2,y_d_33);

      gsl_matrix_complex_transpose_memcpy(y_d_dagger, y_d);

      // set yukawa - lepton
      gsl_complex y_l_11;
      GSL_SET_REAL(&y_l_11, m_l[0]*sqrt(2)/vev/cos(beta));
      GSL_SET_IMAG(&y_l_11, 0.0);

      gsl_complex y_l_22;
      GSL_SET_REAL(&y_l_22, m_l[1]*sqrt(2)/vev/cos(beta));
      GSL_SET_IMAG(&y_l_22, 0.0);

      gsl_complex y_l_33;
      GSL_SET_REAL(&y_l_33, m_l[2]*sqrt(2)/vev/cos(beta));
      GSL_SET_IMAG(&y_l_33, 0.0);

      gsl_matrix_complex_set_zero(y_l);

      gsl_matrix_complex_set(y_l,0,0,y_l_11);
      gsl_matrix_complex_set(y_l,1,1,y_l_22);
      gsl_matrix_complex_set(y_l,2,2,y_l_33);

      // gsl_complex c = gsl_matrix_complex_get(y_l,2,2);
      gsl_matrix_complex_transpose_memcpy(y_l_dagger, y_l);

      //calculate traces - up
      gsl_matrix_complex *temp_u;
      gsl_matrix_complex *temp_u_2;
      temp_u = gsl_matrix_complex_alloc(size, size);
      temp_u_2 = gsl_matrix_complex_alloc(size, size);
      gsl_matrix_complex_memcpy(temp_u,y_u);

      gsl_matrix_complex_mul_elements(temp_u,y_u_dagger);
      tr_u =  gsl_matrix_complex_trace_complex(temp_u);

      gsl_matrix_complex_memcpy(temp_u_2,temp_u);
      gsl_matrix_complex_mul_elements(temp_u,temp_u);
      tr_u2 =  gsl_matrix_complex_trace_complex(temp_u);

      gsl_matrix_complex_free(temp_u);

      //calculate traces - down
      gsl_matrix_complex *temp_d;
      gsl_matrix_complex *temp_d_2;
      temp_d = gsl_matrix_complex_alloc(size, size);
      temp_d_2 = gsl_matrix_complex_alloc(size, size);
      gsl_matrix_complex_memcpy(temp_d,y_d);
      gsl_matrix_complex_memcpy(temp_d_2,y_d);

      gsl_matrix_complex_mul_elements(temp_d,y_d_dagger);
      tr_d =  gsl_matrix_complex_trace_complex(temp_d);

      gsl_matrix_complex_memcpy(temp_d_2,temp_u);
      gsl_matrix_complex_mul_elements(temp_d,temp_d);
      tr_d2 =  gsl_matrix_complex_trace_complex(temp_d);

      gsl_matrix_complex_free(temp_d);

      // caluculate trace for down*up
      gsl_matrix_complex_mul_elements(temp_d_2, temp_u_2);
      tr_du = gsl_matrix_complex_trace_complex(temp_d_2);

      gsl_matrix_complex_free(temp_d_2);
      gsl_matrix_complex_free(temp_u_2);

      //calculate traces - lepton
      gsl_matrix_complex *temp_l;
      temp_l = gsl_matrix_complex_alloc(size, size);
      gsl_matrix_complex_memcpy(temp_l,y_l);

      gsl_matrix_complex_mul_elements(temp_l,y_l_dagger);
      tr_l =  gsl_matrix_complex_trace_complex(temp_l);

      gsl_matrix_complex_mul_elements(temp_l,temp_l);
      tr_l2 =  gsl_matrix_complex_trace_complex(temp_l);

      gsl_matrix_complex_free(temp_l);

      trace.push_back(tr_u);
      trace.push_back(tr_d);
      trace.push_back(tr_l);
      trace.push_back(tr_u2);
      trace.push_back(tr_d2);
      trace.push_back(tr_l2);
      trace.push_back(tr_du);

      return trace;
    }

    std::vector<double> get_alphas_for_type(const int type){
      std::vector<double> a = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
      switch (type)
        {
          case 1:
            a[1] = 0; a[2] = 0; a[3] = 0; a[4] = 0; a[5] = 0; a[6] = 0;
            a[7] = 1; a[8] = 1; a[9] = 1; a[10] = 1; a[11] = 1; a[12] = 1;
            a[13] = 1; a[14] = 1; a[15] = 1; a[16] = 0;
            a[17] = 1; a[18] = 1; a[19] = 1; a[20] = 0;
            a[21] = 1; a[22] = 1; a[23] = 1;
            break;
          case 2:
            a[1] = 1; a[2] = 1; a[3] = 0; a[4] = 1; a[5] = 1; a[6] = 0;
            a[7] = 0; a[8] = 0; a[9] = 1; a[10] = 0; a[11] = 0; a[12] = 1;
            a[13] = 1; a[14] = 1; a[15] = 1; a[16] = 1;
            a[17] = 1; a[18] = 1; a[19] = 1; a[20] = 1;
            a[21] = 1; a[22] = 1; a[23] = 1;
            break;
          case 3:
            a[1] = 1; a[2] = 0; a[3] = 0; a[4] = 1; a[5] = 0; a[6] = 0;
            a[7] = 0; a[8] = 1; a[9] = 1; a[10] = 0; a[11] = 1; a[12] = 1;
            a[13] = 1; a[14] = 1; a[15] = 1; a[16] = 0;
            a[17] = 1; a[18] = 1; a[19] = 1; a[20] = 0;
            a[21] = 1; a[22] = 1; a[23] = 1;
            break;
          case 4:
            a[1] = 0; a[2] = 1; a[3] = 0; a[4] = 0; a[5] = 1; a[6] = 0;
            a[7] = 1; a[8] = 1; a[9] = 0; a[10] = 1; a[11] = 1; a[12] = 0;
            a[13] = 1; a[14] = 1; a[15] = 1; a[16] = 1;
            a[17] = 1; a[18] = 1; a[19] = 1; a[20] = 1;
            a[21] = 1; a[22] = 1; a[23] = 1;
            break;
          case -1:
            break;
          default:
            break;
        }
        return a;
    }

    struct physical_basis_input{
      double mh; double mH; double mA; double mC; double tanb; double alpha; double m122;
    };

    template <class T>
    void fill_physical_basis(T& input, THDM_spectrum_container& container) { 
      input.mh = container.he->get(Par::mass1, "h0", 1);
      input.mH = container.he->get(Par::mass1, "h0", 2);
      input.mA = container.he->get(Par::mass1, "A0");
      input.mC = container.he->get(Par::mass1, "H+");
      input.tanb = container.he->get(Par::dimensionless, "tanb");
      input.alpha = container.he->get(Par::dimensionless, "alpha");
      input.m122 = container.he->get(Par::mass1, "m12_2");
    }

    physical_basis_input fill_physical_basis_input(THDM_spectrum_container& container){
      physical_basis_input input;
      fill_physical_basis(input,container);
      return input;
    }

    std::vector<std::complex<double>> get_cubic_couplings(THDM_spectrum_container& container) {
      const int size = 17;
      std::vector<std::complex<double>> cubic_couplings (size+1);
      std::fill(cubic_couplings.begin(),cubic_couplings.end(),0.0);
      
      const physical_basis_input input_pars = fill_physical_basis_input(container);
      const double mh = input_pars.mh, mH = input_pars.mH, mA = input_pars.mA, mC = input_pars.mC;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2), mC2 = pow(mC,2);
      const double b = atan(input_pars.tanb), a = input_pars.alpha;
      const double sba = sin(b-a), cba = cos(b-a);
      const double v = sqrt((container.THDM_object->get_SM_pointer())->get_v2());
      const std::complex<double> i(0.0,1.0);

      cubic_couplings[1] = 1.0/v * (-1.0*mh2 * sba);
      cubic_couplings[2] = cubic_couplings[1];
      cubic_couplings[3] = 1.0/v * (-1.0*mH2 * cba);
      cubic_couplings[4] = cubic_couplings[3];
      cubic_couplings[5] = 1.0/v * (-1.0*(mh2-mC2) * cba);
      cubic_couplings[6] = 1.0/v * (-1.0*(mh2-mA2) * cba);
      cubic_couplings[7] = 1.0/v * (-1.0*(mH2-mC2) * sba);
      cubic_couplings[8] = 1.0/v * (-1.0*(mH2-mA2) * sba);
      cubic_couplings[9] = 1.0/v * (-1.0*i*(mA2-mC2));
      container.THDM_object->get_coupling_hhh(1,4,4,cubic_couplings[10]);
      container.THDM_object->get_coupling_hhh(1,3,3,cubic_couplings[11]);
      container.THDM_object->get_coupling_hhh(2,4,4,cubic_couplings[12]);
      container.THDM_object->get_coupling_hhh(2,3,3,cubic_couplings[13]);
      container.THDM_object->get_coupling_hhh(1,1,1,cubic_couplings[14]);
      container.THDM_object->get_coupling_hhh(1,1,2,cubic_couplings[15]);
      container.THDM_object->get_coupling_hhh(1,2,2,cubic_couplings[16]);
      container.THDM_object->get_coupling_hhh(2,2,2,cubic_couplings[17]);
      return cubic_couplings;
    }

    std::vector<std::complex<double>> get_quartic_couplings(THDM_spectrum_container& container) {
      const int size = 22;
      std::vector<std::complex<double>> quartic_couplings (size+1);
      std::fill(quartic_couplings.begin(),quartic_couplings.end(),0.0);
      
      const physical_basis_input input_pars = fill_physical_basis_input(container);
      const double mh = input_pars.mh, mH = input_pars.mH, mA = input_pars.mA, mC = input_pars.mC, m122 = input_pars.m122;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2), mC2 = pow(mC,2);
      const double b = atan(input_pars.tanb), a = input_pars.alpha;
      const double sba = sin(b-a), cba = cos(b-a), sba2 = pow(sba,2), cba2 = pow(cba,2), t2binv = 1.0/(tan(2.0*b)), sbinv = 1.0/sin(b), cbinv = 1.0/cos(b);
      const double s2b = sin(2.0*b), s2a = sin(2.0*a), s2b2a = sin(2.0*b-2.0*a), s2a2b = sin(2.0*a-2.0*b);
      const double c2b = cos(2.0*b), c2a = cos(2.0*a);
      const double v2 = container.THDM_object->get_SM_pointer()->get_v2();
      const std::complex<double> i(0.0,1.0);

      quartic_couplings[1] = -1.0/v2 * (mH2*pow(cba,4) + 2.0*(mh2-mH2) * pow(cba,3)*sba*t2binv + mh2*pow(sba,4));
      quartic_couplings[1] += -1.0/v2 * cba2*( 2.0*mA2 - 2.0*sqrt(m122)*sbinv*cbinv + (3.0*mh2 - mH2)*sba2 );
      quartic_couplings[2] = -1.0/v2 * (mH2*pow(cba,4) + 2.0*(mh2-mH2) * pow(sba,3)*cba*t2binv + mh2*pow(sba,4));
      quartic_couplings[2] += -1.0/v2 * sba2*( 2.0*mA2 - 2.0*sqrt(m122)*sbinv*cbinv + (3.0*mH2 - mh2)*cba2 );
      quartic_couplings[3] = 1.0/v2 * (2.0*m122*sbinv*cbinv - 2.0*mC2 - mH2*cba2 - mh2*sba2 + (mH2 - mh2)*t2binv*s2b2a);
      quartic_couplings[4] = 1.0/v2 * (2.0*m122*sbinv*cbinv - (mH2 + 2.0*mh2)*cba2 - (mh2 + 2.0*mH2)*sba2 + (mH2 - mh2)*t2binv*s2b2a);
      quartic_couplings[5] = 1.0/(2.0*v2*s2b) * (mH2*s2b2a*s2a - mA2*s2b*s2a2b + cba*( 4.0*m122*cba*sbinv*cbinv*c2b - mh2*(cos(-1.0*b+3.0*a) + 3.0*cos(b+a)) ) );
      quartic_couplings[6] = 1.0/(2.0*v2*s2b) * (mh2*s2b2a*s2a + mA2*s2b*s2a2b + sba*( 4.0*m122*sba*sbinv*cbinv*c2b - mH2*(sin(-1.0*b+3.0*a) - 3.0*sin(b+a)) ) );
      quartic_couplings[7] = 1.0/(8.0*v2*s2b) * ( 32*m122*c2b + 2.0*(mH2-mh2)*(3.0*c2a + cos(4.0*b-2.0*a))*s2b - 4.0*(mh2+mH2)*sin(4.0*b) );
      quartic_couplings[8] = 3.0*quartic_couplings[7];
      container.THDM_object->get_coupling_hhhh(1,1,4,4,quartic_couplings[9]);
      container.THDM_object->get_coupling_hhhh(1,1,3,3,quartic_couplings[10]);
      container.THDM_object->get_coupling_hhhh(2,2,4,4,quartic_couplings[11]);
      container.THDM_object->get_coupling_hhhh(2,2,3,3,quartic_couplings[12]);
      container.THDM_object->get_coupling_hhhh(1,2,4,4,quartic_couplings[13]);
      container.THDM_object->get_coupling_hhhh(1,2,3,3,quartic_couplings[14]);
      container.THDM_object->get_coupling_hhhh(1,1,1,1,quartic_couplings[15]);
      container.THDM_object->get_coupling_hhhh(1,1,1,2,quartic_couplings[16]);
      container.THDM_object->get_coupling_hhhh(1,1,2,2,quartic_couplings[17]);
      container.THDM_object->get_coupling_hhhh(1,2,2,2,quartic_couplings[18]);
      container.THDM_object->get_coupling_hhhh(2,2,2,2,quartic_couplings[19]);
      container.THDM_object->get_coupling_hhhh(4,4,4,4,quartic_couplings[20]);
      container.THDM_object->get_coupling_hhhh(2,2,4,4,quartic_couplings[21]);
      container.THDM_object->get_coupling_hhhh(2,2,2,2,quartic_couplings[22]);
      return quartic_couplings;
    }

    std::vector<double> get_lambdas_from_spectrum(THDM_spectrum_container& container) {
      std::vector<double> Lambda(8);
      Lambda[1] = container.he->get(Par::mass1, "lambda_1");
      Lambda[2] = container.he->get(Par::mass1, "lambda_2");
      Lambda[3] = container.he->get(Par::mass1, "lambda_3");
      Lambda[4] = container.he->get(Par::mass1, "lambda_4");
      Lambda[5] = container.he->get(Par::mass1, "lambda_5");
      Lambda[6] = container.he->get(Par::mass1, "lambda_6");
      Lambda[7] = container.he->get(Par::mass1, "lambda_7");
      return Lambda;
    }

    double A0_bar(const double m2) {
      double mu2 = m2;
      return m2*(-log(m2/mu2) + 1.0);
    }
    struct B0_integration_variables{
      double x; double p2; double m12; double m22; double mu2; double z_plus;
    };

    double B0_bar_integration(const double x, void * params) {
      double integrand;
      B0_integration_variables* input_pars = static_cast<B0_integration_variables*>(params);
      double p2 = input_pars->p2, m12 = input_pars->m12, m22 = input_pars->m22, mu2 = input_pars->mu2, z_plus = input_pars->z_plus;
      double re = (p2*x*x - x*(p2-m12-m22) + m22)/mu2;
      double im = -z_plus/mu2;
      integrand = log(sqrt(re*re + im*im)) + atan(im/re);
      return integrand;
    }

    double B0_bar(const double p2, const double m12, const double m22) {
      const double MZ = 91.15349;
      double mu2 = pow(MZ,2);
      double z_plus = 0.01;
      double result, error;
      gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
      gsl_function B0_bar_int;
      B0_bar_int.function = &B0_bar_integration;
      B0_integration_variables input_pars;
      input_pars.p2 = p2; input_pars.m12 = m12; input_pars.m22 = m22; input_pars.mu2 = mu2; input_pars.z_plus = z_plus;
      B0_bar_int.params = &input_pars;

      gsl_integration_qags (&B0_bar_int, 0, 1.0, 0, 1e-7, 1000,
                            w, &result, &error);
      return result;
    }

    struct wavefunction_renormalization_input{
      double mh; double mH; double mA; double mC; double tanb; double alpha; double m122; std::vector<std::complex<double>> m; std::vector<std::complex<double>> g;
    };

    wavefunction_renormalization_input fill_wavefunction_renormalization_input(THDM_spectrum_container& container){
      wavefunction_renormalization_input input;
      fill_physical_basis(input,container);
      input.m = get_cubic_couplings(container); 
      input.g = get_quartic_couplings(container);
      return input;
    }

    enum wavefunction_renormalization{ wpwm, zz, wpHm, Hpwm, zA, Az, hh, HH, hH, Hh, HpHm, AA, };

    //mZw2
    double mZw2(const void * params){
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, tanb = input_pars->tanb, alpha = input_pars->alpha, m122 = input_pars->m122;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2);
      const double a = alpha, b = atan(tanb), sb = sin(b), cb = cos(b), sba = sin(b-a), cba = cos(b-a), s2b2a = sin(2.0*b - 2.0*a), t2b = tan(2.0*b);
      return 1.0/2.0*(mh2*pow(sba,2) + mH2*pow(cba,2) + (mh2 - mH2)*s2b2a*(1.0/t2b) - 2.0*pow(m122,2)*(1.0/sb)*(1.0/cb));
    }

    //Self energies & wavefunction renormalizations
    std::complex<double> Pi_tilde_wpwm(const double p2, void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2), mC2 = pow(mC,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = pow(m[1],2)*(B0_bar(p2,0.,mh2) - B0_bar(0.,0.,mh2)); 
      Pi+=pow(m[3],2)*(B0_bar(p2,0.,mh2) - B0_bar(0.,0.,mH2));
      Pi+=pow(m[5],2)*(B0_bar(p2,mC2,mh2) - B0_bar(0.,mC2,mh2));
      Pi+=pow(m[7],2)*(B0_bar(p2,mC2,mH2) - B0_bar(0.,mC2,mH2));
      Pi+=m[9]*std::conj(m[9])*(B0_bar(p2,mC2,mA2) - B0_bar(0.,mC2,mA2));
      return -1.0/(16.0*pow(PI,2))*Pi;
    }
    double Pi_tilde_wpwm_re(const double p2, void * params) { return Pi_tilde_wpwm(p2, params).real(); }
    double Pi_tilde_wpwm_im(const double p2, void * params) { return Pi_tilde_wpwm(p2, params).imag(); }

    std::complex<double> Pi_tilde_zz(const double p2, void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = pow(m[2],2)*(B0_bar(p2,0.,mh2) - B0_bar(0.,0.,mh2));
      Pi+=pow(m[4],2)*(B0_bar(p2,0.,mH2) - B0_bar(0.,0.,mH2));
      Pi+=pow(m[6],2)*(B0_bar(p2,mA2,mh2) - B0_bar(0.,mA2,mh2));
      Pi+=pow(m[8],2)*(B0_bar(p2,mA2,mH2) - B0_bar(0.,mA2,mH2));
      return -1.0/(16.0*pow(PI,2))*Pi;
    }
    double Pi_tilde_zz_re(const double p2, void * params) { return Pi_tilde_zz(p2, params).real(); }
    double Pi_tilde_zz_im(const double p2, void * params) { return Pi_tilde_zz(p2, params).imag(); }

    std::complex<double> Pi_tilde_wpHm(const double p2, void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mC = input_pars->mC;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mC2 = pow(mC,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = m[1]*m[5]*(B0_bar(p2,0.,mh2) - B0_bar(0.,0.,mh2));
      Pi+=m[3]*m[7]*(B0_bar(p2,0.,mH2) - B0_bar(0.,0.,mH2));
      Pi+=m[5]*m[10]*(B0_bar(p2,mC2,mh2) - B0_bar(0.,mC2,mh2));
      Pi+=m[7]*m[12]*(B0_bar(p2,mC2,mH2) - B0_bar(0.,mC2,mH2));
      return -1.0/(16.0*pow(PI,2))*Pi;
    }
    double Pi_tilde_wpHm_re(const double p2, void * params) { return Pi_tilde_wpHm(p2, params).real(); }
    double Pi_tilde_wpHm_im(const double p2, void * params) { return Pi_tilde_wpHm(p2, params).imag(); }

    std::complex<double> Pi_tilde_zA(const double p2, void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = m[2]*m[6]*(B0_bar(p2,0.,mh2) - B0_bar(0.,0.,mh2));
      Pi+=m[4]*m[8]*(B0_bar(p2,0.,mH2) - B0_bar(0.,0.,mH2));
      Pi+=m[6]*m[11]*(B0_bar(p2,mA2,mh2) - B0_bar(0.,mA2,mh2));
      Pi+=m[8]*m[13]*(B0_bar(p2,mA2,mH2) - B0_bar(0.,mA2,mH2));
      return -1.0/(16.0*pow(PI,2))*Pi;
    }
    double Pi_tilde_zA_re(const double p2, void * params) { return Pi_tilde_zA(p2, params).real(); }
    double Pi_tilde_zA_im(const double p2, void * params) { return Pi_tilde_zA(p2, params).imag(); }

    std::complex<double> Pi_zz(void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = 1.0/(32.0*pow(PI,2))*(g[1]*A0_bar(mh2) + g[2]*A0_bar(mH2) + 2.0*g[3]*A0_bar(mH2) + g[4]*A0_bar(mA2));
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[2],2)*B0_bar(0.,0.,mh2);
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[4],2)*B0_bar(0.,0.,mH2);
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[6],2)*B0_bar(0.,mA2,mh2);
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[8],2)*B0_bar(0.,mA2,mH2);
      return Pi;
    }
    double Pi_zz_re(void * params) { return Pi_zz(params).real(); }
    double Pi_zz_im(void * params) { return Pi_zz(params).imag(); }

    double Pi_wpwm_re(void * params) { return Pi_zz(params).real(); }
    double Pi_wpwm_im(void * params) { return Pi_zz(params).imag(); }

    std::complex<double> Pi_zA(void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = 1.0/(32.0*pow(PI,2))*(g[5]*A0_bar(mh2) + g[6]*A0_bar(mH2) + 2.0*g[7]*A0_bar(mH2) + g[8]*A0_bar(mA2));
      Pi+=-1.0/(16.0*pow(PI,2))*m[2]*m[6]*B0_bar(0.,0.,mh2);
      Pi+=-1.0/(16.0*pow(PI,2))*m[4]*m[8]*B0_bar(0.,0.,mH2);
      Pi+=-1.0/(16.0*pow(PI,2))*m[6]*m[11]*B0_bar(0.,mA2,mh2);
      Pi+=-1.0/(16.0*pow(PI,2))*m[8]*m[13]*B0_bar(0.,mA2,mH2);
      return Pi;
    }
    double Pi_zA_re(void * params) { return Pi_zA(params).real(); }
    double Pi_zA_im(void * params) { return Pi_zA(params).imag(); }

    double Pi_wpHm_re(void * params) { return Pi_zA(params).real(); }
    double Pi_wpHm_im(void * params) { return Pi_zA(params).imag(); }

    std::complex<double> Pi_tilde_hh(const double p2, void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC, tanb = input_pars->tanb, alpha = input_pars->alpha;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2), mC2 = pow(mC,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      const double beta = atan(tanb), sba = sin(beta-alpha), cba = cos(beta-alpha);
      std::complex<double> Pi = 1.0/(32.0*pow(PI,2))*(2.0*g[9]*A0_bar(mC2) + g[10]*A0_bar(mA2) + g[15]*A0_bar(mh2) + g[17]*A0_bar(mH2));
      Pi+=-1.0/(32.0*pow(PI,2))*(2.0*pow(m[1],2)+pow(m[2],2))*B0_bar(p2,0,0);
      Pi+=-1.0/(32.0*pow(PI,2))*4.0*pow(m[5],2)*B0_bar(p2,0.,mC2);
      Pi+=-1.0/(32.0*pow(PI,2))*2.0*pow(m[6],2)*B0_bar(p2,0.,mA2);
      Pi+=-1.0/(32.0*pow(PI,2))*2.0*pow(m[10],2)*B0_bar(p2,mC2,mC2);
      Pi+=-1.0/(32.0*pow(PI,2))*pow(m[11],2)*B0_bar(p2,mA2,mA2);
      Pi+=-1.0/(32.0*pow(PI,2))*pow(m[14],2)*B0_bar(p2,mh2,mh2);
      Pi+=-1.0/(32.0*pow(PI,2))*2.0*pow(m[15],2)*B0_bar(p2,mH2,mh2);
      Pi+=-1.0/(32.0*pow(PI,2))*pow(m[16],2)*B0_bar(p2,mH2,mH2);
      Pi+=-pow(sba,2)*Pi_zz(params) - 2.0*sba*cba*Pi_zA(params) + (Z_w(params)-1.0)*(mh2+pow(mZw2(params),2)*pow(cba,2));
      return Pi;
    }
    double Pi_tilde_hh_re(const double p2, void * params) { return Pi_tilde_hh(p2, params).real(); }
    double Pi_tilde_hh_im(const double p2, void * params) { return Pi_tilde_hh(p2, params).imag(); }

    std::complex<double> Pi_tilde_HH(const double p2, void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC, tanb = input_pars->tanb, alpha = input_pars->alpha;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2), mC2 = pow(mC,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      const double beta = atan(tanb), sba = sin(beta-alpha), cba = cos(beta-alpha);
      std::complex<double> Pi = 1.0/(32.0*pow(PI,2))*(2.0*g[11]*A0_bar(mC2) + g[12]*A0_bar(mA2) + g[17]*A0_bar(mh2) + g[19]*A0_bar(mH2));
      Pi+=-1.0/(32.0*pow(PI,2))*(2.0*pow(m[3],2)+pow(m[4],2))*B0_bar(p2,0,0);
      Pi+=-1.0/(32.0*pow(PI,2))*4.0*pow(m[7],2)*B0_bar(p2,0.,mC2);
      Pi+=-1.0/(32.0*pow(PI,2))*2.0*pow(m[8],2)*B0_bar(p2,0.,mA2);
      Pi+=-1.0/(32.0*pow(PI,2))*2.0*pow(m[12],2)*B0_bar(p2,mC2,mC2);
      Pi+=-1.0/(32.0*pow(PI,2))*pow(m[13],2)*B0_bar(p2,mA2,mA2);
      Pi+=-1.0/(32.0*pow(PI,2))*pow(m[15],2)*B0_bar(p2,mh2,mh2);
      Pi+=-1.0/(32.0*pow(PI,2))*2.0*pow(m[16],2)*B0_bar(p2,mH2,mh2);
      Pi+=-1.0/(32.0*pow(PI,2))*pow(m[17],2)*B0_bar(p2,mH2,mH2);
      Pi+=-pow(cba,2)*Pi_zz(params) + 2.0*sba*cba*Pi_zA(params) + (Z_w(params)-1.0)*(mH2+pow(mZw2(params),2)*pow(sba,2));
      return Pi;
    }
    double Pi_tilde_HH_re(const double p2, void * params) { return Pi_tilde_HH(p2, params).real(); }
    double Pi_tilde_HH_im(const double p2, void * params) { return Pi_tilde_HH(p2, params).imag(); }

    std::complex<double> Pi_tilde_hH(const double p2, void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC, tanb = input_pars->tanb, alpha = input_pars->alpha;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2), mC2 = pow(mC,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      const double beta = atan(tanb), sba = sin(beta-alpha), cba = cos(beta-alpha);
      std::complex<double> Pi = 1.0/(32.0*pow(PI,2))*(2.0*g[13]*A0_bar(mC2) + g[14]*A0_bar(mA2) + g[16]*A0_bar(mh2) + g[18]*A0_bar(mH2));
      Pi+=-1.0/(32.0*pow(PI,2))*(2.0*m[1]*m[3]+m[2]*m[4])*B0_bar(p2,0,0);
      Pi+=-1.0/(32.0*pow(PI,2))*4.0*m[5]*m[7]*B0_bar(p2,0.,mC2);
      Pi+=-1.0/(32.0*pow(PI,2))*2.0*m[6]*m[8]*B0_bar(p2,0.,mA2);
      Pi+=-1.0/(32.0*pow(PI,2))*2.0*m[10]*m[12]*B0_bar(p2,mC2,mC2);
      Pi+=-1.0/(32.0*pow(PI,2))*m[11]*m[13]*B0_bar(p2,mA2,mA2);
      Pi+=-1.0/(32.0*pow(PI,2))*m[14]*m[15]*B0_bar(p2,mh2,mh2);
      Pi+=-1.0/(32.0*pow(PI,2))*2.0*m[15]*m[16]*B0_bar(p2,mH2,mh2);
      Pi+=-1.0/(32.0*pow(PI,2))*m[16]*m[17]*B0_bar(p2,mH2,mH2);
      Pi+=-sba*cba*Pi_zz(params) - (pow(cba,2) - pow(sba,2))*Pi_zA(params) - (Z_w(params)-1.0)*(pow(mZw2(params),2)*sba*cba);
      return Pi;
    }
    double Pi_tilde_hH_re(const double p2, void * params) { return Pi_tilde_hH(p2, params).real(); }
    double Pi_tilde_hH_im(const double p2, void * params) { return Pi_tilde_hH(p2, params).imag(); }

    std::complex<double> Pi_tilde_HpHm(const double p2, void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2), mC2 = pow(mC,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = 1.0/(32.0*pow(PI,2))*(g[9]*A0_bar(mh2) + g[11]*A0_bar(mH2) + 2.0*g[20]*A0_bar(mC2) + g[21]*A0_bar(mA2));
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[5],2)*B0_bar(p2,0.,mh2);
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[7],2)*B0_bar(p2,0.,mH2);
      Pi+=-1.0/(16.0*pow(PI,2))*std::conj(m[9])*m[9]*B0_bar(p2,0.,mA2);
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[10],2)*B0_bar(p2,mC2,mh2);
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[12],2)*B0_bar(p2,mC2,mH2);
      Pi+=(Z_w(params)-1.0)*(mC2 + pow(mZw2(params),2));
      return Pi;
    }
    double Pi_tilde_HpHm_re(const double p2, void * params) { return Pi_tilde_HpHm(p2, params).real(); }
    double Pi_tilde_HpHm_im(const double p2, void * params) { return Pi_tilde_HpHm(p2, params).imag(); }

    std::complex<double> Pi_tilde_AA(const double p2, void * params) {
      const wavefunction_renormalization_input* input_pars = static_cast<const wavefunction_renormalization_input*>(params);
      const double mh = input_pars->mh, mH = input_pars->mH, mA = input_pars->mA, mC = input_pars->mC;
      const double mh2 = pow(mh,2), mH2 = pow(mH,2), mA2 = pow(mA,2), mC2 = pow(mC,2);
      const std::vector<std::complex<double>> m = input_pars->m, g = input_pars->g;
      std::complex<double> Pi = 1.0/(32.0*pow(PI,2))*(g[10]*A0_bar(mh2) + g[12]*A0_bar(mH2) + 2.0*g[21]*A0_bar(mC2) + g[22]*A0_bar(mA2));
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[6],2)*B0_bar(p2,0.,mh2);
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[8],2)*B0_bar(p2,0.,mH2);
      Pi+=-1.0/(16.0*pow(PI,2))*2.0*std::conj(m[9])*m[9]*B0_bar(p2,0.,mC2);
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[11],2)*B0_bar(p2,mA2,mh2);
      Pi+=-1.0/(16.0*pow(PI,2))*pow(m[13],2)*B0_bar(p2,mA2,mH2);
      Pi+=(Z_w(params)-1.0)*(mA2 + pow(mZw2(params),2));
      return Pi;
    }
    double Pi_tilde_AA_re(const double p2, void * params) { return Pi_tilde_AA(p2, params).real(); }
    double Pi_tilde_AA_im(const double p2, void * params) { return Pi_tilde_AA(p2, params).imag(); }

    std::complex<double> z_ii(const wavefunction_renormalization type, wavefunction_renormalization_input& params){
      gsl_function F_re; gsl_function F_im;
      F_re.params = &params; F_im.params = &params;
      double result_re, result_im, abserr_re, abserr_im;
      double m_in = 0.0;
      const std::complex<double> i(0.0,1.0);
      switch(type) {
        case wpwm:
          F_re.function = &Pi_tilde_wpwm_re;
          F_im.function = &Pi_tilde_wpwm_im;
          m_in = 0.0;
          break;
        case zz:
          F_re.function = &Pi_tilde_zz_re;
          F_im.function = &Pi_tilde_zz_im;
          m_in = 0.0;
          break;
        case hh:
          F_re.function = &Pi_tilde_hh_re;
          F_im.function = &Pi_tilde_hh_im;
          m_in = params.mh;
          break;
        case HH:
          F_re.function = &Pi_tilde_HH_re;
          F_im.function = &Pi_tilde_HH_im;
          m_in = params.mH;
          break;
        case HpHm:
          F_re.function = &Pi_tilde_HpHm_re;
          F_im.function = &Pi_tilde_HpHm_im;
          m_in = params.mC;
          break;
        case AA:
          F_re.function = &Pi_tilde_AA_re;
          F_im.function = &Pi_tilde_AA_im;
          m_in = params.mA;
          break;
        default:
          std::cerr << "WARNING: Unrecognized wavefunction renormalization particle pair sent to z_ij function. Returning 0." << std::endl;
          return 0.0;
      }
      gsl_deriv_central (&F_re, m_in, 1e-8, &result_re, &abserr_re);
      gsl_deriv_central (&F_im, m_in, 1e-8, &result_im, &abserr_im);
      const complex<double> Z_ii = 1.0 + 0.5*(result_re + i*result_im);
      return 16.0*pow(PI,2)*(Z_ii-1.0);
    }

    std::complex<double> z_ij(const wavefunction_renormalization type, THDM_spectrum_container& container){
      std::complex<double> z_ij = 0.0;
      double m1 = 0.0, m2 = 0.0;
      wavefunction_renormalization_input input_pars = fill_wavefunction_renormalization_input(container);
      switch(type) {
        case wpHm:
          m1 = 0.0; m2 = input_pars.mC;
          z_ij = Pi_tilde_wpHm(m1,&input_pars);
          break;
        case zA:
          m1 = 0.0; m2 = input_pars.mA;
          z_ij = Pi_tilde_zA(m1,&input_pars);
          break;
        case hH:
          m1 = input_pars.mh; m2 = input_pars.mH;
          z_ij = Pi_tilde_hH(m1,&input_pars);
          break;
        case Hpwm:
          m2 = 0.0; m1 = input_pars.mC;
          z_ij = Pi_tilde_wpHm(m1,&input_pars);
          break;
        case Az:
          m2 = 0.0; m1 = input_pars.mA;
          z_ij = Pi_tilde_zA(m1,&input_pars);
          break;
        case Hh:
          m2 = input_pars.mh; m1 = input_pars.mH;
          z_ij = Pi_tilde_hH(m1,&input_pars);
          break;
        default:
          z_ij = z_ii(type, input_pars);
          return z_ij;
      }
      return z_ij/(pow(m1,2) - pow(m2,2));
    }

    double Z_w(void * params){
      gsl_function F_re, F_im;
      F_re.params = params; F_im.params = params;
      F_re.function = &Pi_tilde_wpwm_re;
      F_im.function = &Pi_tilde_wpwm_im;
      double result_re, abserr_re, result_im, abserr_im;
      double m_in = 0.0;
      gsl_deriv_central (&F_re, m_in, 1e-8, &result_re, &abserr_re);
      gsl_deriv_central (&F_im, m_in, 1e-8, &result_im, &abserr_im);
      return 1.0 + 0.5*(result_re + result_im);
    }

    std::complex<double> beta_one(THDM_spectrum_container& container) {
      const std::vector<double> a = get_alphas_for_type(container.yukawa_type);
      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      const double g1 = container.he->get(Par::dimensionless, "g1"), g2 = container.he->get(Par::dimensionless, "g2");
      const std::vector<complex<double>> tr = get_trace_of_yukawa_matrices(container);
      int i = 0;
      const std::complex<double> tr_u = tr[i++], tr_d = tr[i++], tr_l = tr[i++], tr_u2 = tr[i++], tr_d2 = tr[i++], tr_l2 = tr[i++];
      std::complex<double> beta = 12.0*pow(Lambda[1],2) + 4.0*pow(Lambda[3],2) + 4.0*Lambda[3]*Lambda[4] + 2.0*pow(Lambda[4],2) + 2.0*pow(Lambda[5],2);
      beta += 3.0/4.0*pow(g1,4) + 3.0/2.0*pow(g1,2)*pow(g2,2) + 9.0/4.0*pow(g2,4) - 3.0*pow(g1,2)*Lambda[1] - 9.0*pow(g2,2)*Lambda[1];
      beta += 4.0*Lambda[1]*(a[1]*tr_l + 3.0*a[2]*tr_d + 3*a[3]*tr_u) - 4.0*(a[4]*tr_l2 + 3.0*a[5]*tr_d2 + 3*a[6]*tr_u2);
      return 1.0/(16.0*pow(PI,2))*(beta);
    }

    std::complex<double> beta_two(THDM_spectrum_container& container) {
      const std::vector<double> a = get_alphas_for_type(container.yukawa_type);
      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      const double g1 = container.he->get(Par::dimensionless, "g1"), g2 = container.he->get(Par::dimensionless, "g2");
      const std::vector<complex<double>> tr = get_trace_of_yukawa_matrices(container);
      int i = 0;
      const std::complex<double> tr_u = tr[i++], tr_d = tr[i++], tr_l = tr[i++], tr_u2 = tr[i++], tr_d2 = tr[i++], tr_l2 = tr[i++];
      std::complex<double> beta = 12.0*pow(Lambda[2],2)+4.0*pow(Lambda[3],2)+4*Lambda[3]*Lambda[4]+2.0*pow(Lambda[4],2)+2.0*pow(Lambda[5],2);
      beta += 3.0/4.0*pow(g1,4) + 3.0/2.0*pow(g1,2)*pow(g2,2) + 9.0/4.0*pow(g2,4) - 3.0*pow(g1,2)*Lambda[2] - 9.0*pow(g2,2)*Lambda[2];
      beta += 4.0*Lambda[2]*(a[7]*tr_l + 3.0*a[8]*tr_d + 3*a[9]*tr_u) - 4.0*(a[10]*tr_l2 + 3.0*a[11]*tr_d2 + 3*a[12]*tr_u2);
      return 1.0/(16.0*pow(PI,2))*beta;
    }

    std::complex<double> beta_three(THDM_spectrum_container& container) {
      const std::vector<double> a = get_alphas_for_type(container.yukawa_type);
      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      const double g1 = container.he->get(Par::dimensionless, "g1"), g2 = container.he->get(Par::dimensionless, "g2");
      const std::vector<complex<double>> tr = get_trace_of_yukawa_matrices(container);
      int i = 0;
      const std::complex<double> tr_u = tr[i++], tr_d = tr[i++], tr_l = tr[i++]; i++; i++; i++; std::complex<double> tr_du = tr[i++];
      std::complex<double> beta = 4.0*pow(Lambda[3],2) +2.0*pow(Lambda[4],2) + (Lambda[1]+Lambda[2])*(6.0*Lambda[3]+2.0*Lambda[4]) + 2.0*pow(Lambda[5],2);
      beta += -3.0*Lambda[3]*(3*pow(g2,2) + pow(g1,2)) + 9.0/4.0*pow(g2,4) + 3.0/4.0*pow(g1,4) - 3.0/2.0*pow(g1,2)*pow(g2,2);
      beta += 2*Lambda[3]*(a[13]*tr_l + 3.0*a[14]*tr_d + 3.0*a[15]*tr_u) - 12.0*a[16]*tr_du;
      return 1.0/(16.0*pow(PI,2))*beta;
    }

    std::complex<double> beta_four(THDM_spectrum_container& container) {
      const std::vector<double> a = get_alphas_for_type(container.yukawa_type);
      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      const double g1 = container.he->get(Par::dimensionless, "g1"), g2 = container.he->get(Par::dimensionless, "g2");
      const std::vector<complex<double>> tr = get_trace_of_yukawa_matrices(container);
      int i = 0;
      const std::complex<double> tr_u = tr[i++], tr_d = tr[i++], tr_l = tr[i++]; i++; i++; i++; std::complex<double> tr_du = tr[i++];
      std::complex<double> beta = (2.0*Lambda[1] + 2.0*Lambda[2] + 8.0*Lambda[3])*Lambda[4] + 4.0*pow(Lambda[4],2) + 8.0*pow(Lambda[5],2);
      beta += -3.0*Lambda[4]*(3.0*pow(g2,2) + pow(g1,2)) + 3.0*pow(g1,2)*pow(g1,2);
      beta += 2.0*Lambda[4]*(a[17]*tr_l + 3.0*a[18]*tr_d + 3.0*a[19]*tr_u) + 12.0*a[20]*tr_du;
      return 1.0/(16.0*pow(PI,2))*beta;
    }

    std::complex<double> beta_five(THDM_spectrum_container& container) {
      const std::vector<double> a = get_alphas_for_type(container.yukawa_type);
      const std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      const double g1 = container.he->get(Par::dimensionless, "g1"), g2 = container.he->get(Par::dimensionless, "g2");
      const std::vector<complex<double>> tr = get_trace_of_yukawa_matrices(container);
      int i = 0;
      const std::complex<double> tr_u = tr[i++], tr_d = tr[i++], tr_l = tr[i++];
      std::complex<double> beta = (2.0*Lambda[1] + 2.0*Lambda[2] + 8.0*Lambda[3] + 12.0*Lambda[4])*Lambda[5];
      beta += -3.0*Lambda[5]*(3.0*pow(g2,2) + pow(g1,2));
      beta += 2.0*Lambda[5]*(a[21]*tr_l +3.0*a[22]*tr_d + 3.0*a[23]*tr_u);
      return 1.0/(16.0*pow(PI,2))*beta;
    }

// Likelihood Functions

    double unitarity_likelihood_THDM(THDM_spectrum_container& container);
    double NLO_unitarity_likelihood_THDM(THDM_spectrum_container& container);
    double perturbativity_likelihood_THDM(THDM_spectrum_container& container);
    double stability_likelihood_THDM(THDM_spectrum_container& container);
    double alignment_likelihood_THDM(THDM_spectrum_container& container);
    double oblique_parameters_likelihood_THDM(THDM_spectrum_container& container);
    double global_minimum_discriminant_likelihood_THDM(THDM_spectrum_container& container);

    double get_likelihood(std::function<double(THDM_spectrum_container&)> likelihood_function, const Spectrum& spec, const double scale, const int yukawa_type) { 
      THDM_spectrum_container container;
      init_THDM_spectrum_container(container, spec, yukawa_type, 0.0);
      const double chi_2 = likelihood_function(container);
      double chi_2_at_Q = -L_MAX;
      if (scale>0.0) {
        THDM_spectrum_container container_at_scale;
        init_THDM_spectrum_container(container_at_scale, spec, yukawa_type, scale);
        chi_2_at_Q = likelihood_function(container_at_scale);
      }
      delete container.THDM_object; // must be deleted upon the of container usage or memory will overflow
      return std::max(chi_2,chi_2_at_Q);
    }

    void get_unitarity_likelihood_THDM(double& result) {
      using namespace Pipes::get_unitarity_likelihood_THDM;
      double scale = *Param.at("QrunTo");
      if (!runOptions->getValueOrDef<bool>(false, "check_all_scales")) scale = 0.0;
      std::function<double(THDM_spectrum_container&)> likelihood_function = unitarity_likelihood_THDM;
      result = get_likelihood(likelihood_function, *Dep::THDM_spectrum, scale, runOptions->getValueOrDef<int>(1, "yukawa_type"));  
    }

    void get_NLO_unitarity_likelihood_THDM(double& result) {
      using namespace Pipes::get_NLO_unitarity_likelihood_THDM;
      double scale = *Param.at("QrunTo");
      if (!runOptions->getValueOrDef<bool>(false, "check_all_scales")) scale = 0.0;
      std::function<double(THDM_spectrum_container&)> likelihood_function = NLO_unitarity_likelihood_THDM;
      result = get_likelihood(likelihood_function, *Dep::THDM_spectrum, scale, runOptions->getValueOrDef<int>(1, "yukawa_type"));  
    }

    void get_perturbativity_likelihood_THDM(double& result) {
      using namespace Pipes::get_perturbativity_likelihood_THDM;
      double scale = *Param.at("QrunTo");
      if (!runOptions->getValueOrDef<bool>(false, "check_all_scales")) scale = 0.0;
      std::function<double(THDM_spectrum_container&)> likelihood_function = perturbativity_likelihood_THDM;
      result = get_likelihood(likelihood_function, *Dep::THDM_spectrum, scale, runOptions->getValueOrDef<int>(1, "yukawa_type"));  
    }

    void get_stability_likelihood_THDM(double& result) {
      using namespace Pipes::get_stability_likelihood_THDM;
      double scale = *Param.at("QrunTo");
      if (!runOptions->getValueOrDef<bool>(false, "check_all_scales")) scale = 0.0;
      std::function<double(THDM_spectrum_container&)> likelihood_function = stability_likelihood_THDM;
      result = get_likelihood(likelihood_function, *Dep::THDM_spectrum, scale, runOptions->getValueOrDef<int>(1, "yukawa_type"));  
    }

    void get_alignment_likelihood_THDM(double& result) {
      using namespace Pipes::get_alignment_likelihood_THDM;
      double scale = *Param.at("QrunTo");
      if (!runOptions->getValueOrDef<bool>(false, "check_all_scales")) scale = 0.0;
      std::function<double(THDM_spectrum_container&)> likelihood_function = alignment_likelihood_THDM;
      result = get_likelihood(likelihood_function, *Dep::THDM_spectrum, scale, runOptions->getValueOrDef<int>(1, "yukawa_type"));  
    }

    void get_oblique_parameters_likelihood_THDM(double& result) {
      using namespace Pipes::get_oblique_parameters_likelihood_THDM;
      double scale = *Param.at("QrunTo");
      if (!runOptions->getValueOrDef<bool>(false, "check_all_scales")) scale = 0.0;
      std::function<double(THDM_spectrum_container&)> likelihood_function = oblique_parameters_likelihood_THDM;
      result = get_likelihood(likelihood_function, *Dep::THDM_spectrum, scale, runOptions->getValueOrDef<int>(1, "yukawa_type"));  
    }

    void get_global_minimum_discriminant_likelihood(double& result) {
      using namespace Pipes::get_global_minimum_discriminant_likelihood;
      double scale = *Param.at("QrunTo");
      if (!runOptions->getValueOrDef<bool>(false, "check_all_scales")) scale = 0.0;
      std::function<double(THDM_spectrum_container&)> likelihood_function = global_minimum_discriminant_likelihood_THDM;
      result = get_likelihood(likelihood_function, *Dep::THDM_spectrum, scale, runOptions->getValueOrDef<int>(1, "yukawa_type"));  
    }

    double unitarity_likelihood_THDM(THDM_spectrum_container& container) { 
      if (print_debug_checkpoints) cout << "Checkpoint: 29" << endl;

      std::vector<double> lambda;
      lambda.push_back(0.0); //empty s.t. lambda_i matches index i
      lambda.push_back(container.he->get(Par::mass1, "lambda_1"));
      lambda.push_back(container.he->get(Par::mass1, "lambda_2"));
      lambda.push_back(container.he->get(Par::mass1, "lambda_3"));
      lambda.push_back(container.he->get(Par::mass1, "lambda_4"));
      lambda.push_back(container.he->get(Par::mass1, "lambda_5"));
      lambda.push_back(container.he->get(Par::mass1, "lambda_6"));
      lambda.push_back(container.he->get(Par::mass1, "lambda_7"));

      const int array_size = 12;
      double eigs[array_size+1];
      eigs[0] = array_size;

      // S-Matrices from Ginzburg and Ivanov, hep-ph/0508020
      eigs[1] = lambda[3]-lambda[4];
      //if (abs(S20) > abs(egmax)) egmax = S20;

      double s2 = sqrt(2.);

      double S21_data[] = { lambda[1],    lambda[5],    s2*lambda[6],
                            lambda[5],    lambda[2],    s2*lambda[7],
                            s2*lambda[6], s2*lambda[7], lambda[3]+lambda[4] };

      double S01_data[] = { lambda[1],  lambda[4],  lambda[6],  lambda[6],
                            lambda[4],  lambda[2],  lambda[7],  lambda[7],
                            lambda[6],  lambda[7],  lambda[3],  lambda[5],
                            lambda[6],  lambda[7],  lambda[5],  lambda[3] };

      double S00_data[] = { 3.*lambda[1],2.*lambda[3]+lambda[4],3.*lambda[6],3.*lambda[6],
                            2.*lambda[3]+lambda[4],3.*lambda[2],3.*lambda[7],3.*lambda[7],
                            3.*lambda[6],3.*lambda[7],lambda[3]+2.*lambda[4],3.*lambda[5],
                            3.*lambda[6],3.*lambda[7],3.*lambda[5],lambda[3]+2.*lambda[4] };

      gsl_matrix_view S21 = gsl_matrix_view_array(S21_data,3,3);
      gsl_matrix_view S01 = gsl_matrix_view_array(S01_data,4,4);
      gsl_matrix_view S00 = gsl_matrix_view_array(S00_data,4,4);

      gsl_eigen_symm_workspace *w3 = gsl_eigen_symm_alloc(3);
      gsl_eigen_symm_workspace *w4 = gsl_eigen_symm_alloc(4);
      gsl_vector *eval3 = gsl_vector_alloc(3);
      gsl_vector *eval4 = gsl_vector_alloc(4);

      gsl_eigen_symm(&S21.matrix,eval3,w3);
      for (int i=0;i<3;i++) {
        eigs[i+2]=gsl_vector_get(eval3,i);
        //if (abs(eg)>abs(egmax)) egmax = eg;
      }

      gsl_eigen_symm(&S01.matrix,eval4,w4);
      for (int i=0;i<4;i++) {
        eigs[i+5] = gsl_vector_get(eval4,i);
        //if (abs(eg)>abs(egmax)) egmax = eg;
      }

      gsl_eigen_symm(&S00.matrix,eval4,w4);
      for (int i=0;i<4;i++) {
        eigs[i+9] = gsl_vector_get(eval4,i);
        //if (abs(eg)>abs(egmax)) egmax = eg;
      }

      gsl_eigen_symm_free(w3);
      gsl_eigen_symm_free(w4);
      gsl_vector_free(eval3);
      gsl_vector_free(eval4);

      //set constraint values
      //-----------------------------
      // all values < 16*PI for unitarity conditions
      double unitarity_upper_limit = 16*M_PI; // 16 pi using conditions given in ivanov paper (used by 2hdmc)
      double sigma = 4.0*M_PI;
      //-----------------------------
      //calculate the total error of each point
      double chi2 = 0.0;
      for (auto eachEig : eigs) {
            chi2 += get_chi(abs(eachEig),bound,less_than,unitarity_upper_limit,sigma);
      }
      return -chi2;
    }

    double NLO_unitarity_likelihood_THDM(THDM_spectrum_container& container) { 
      if (print_debug_checkpoints) cout << "Checkpoint: 31" << endl;
      const std::complex<double> i(0.0,1.0);

      std::vector<double> Lambda = get_lambdas_from_spectrum(container);
      double b = atan(container.he->get(Par::dimensionless, "tanb")), a= container.he->get(Par::dimensionless, "alpha");
      double c2a = cos(2.0*a), c2b = cos(2.0*b), s2a = sin(2.0*a), s2b = sin(2.0*b);

      // to avoid having to recalculate
      const std::complex<double> b_one = beta_one(container);
      const std::complex<double> b_two = beta_two(container);
      const std::complex<double> b_three = beta_three(container);
      const std::complex<double> b_four = beta_four(container);
      const std::complex<double> b_five = beta_five(container);

      const std::complex<double> zij_wpwm = z_ij(wpwm, container);
      const std::complex<double> zij_zz = z_ij(zz, container);
      const std::complex<double> zij_Hpwm = z_ij(Hpwm, container);
      const std::complex<double> zij_Az = z_ij(Az, container);
      const std::complex<double> zij_hh = z_ij(hh, container);
      const std::complex<double> zij_HH = z_ij(HH, container);
      const std::complex<double> zij_hH = z_ij(hH, container);
      const std::complex<double> zij_Hh = z_ij(Hh, container);
      const std::complex<double> zij_HpHm = z_ij(HpHm, container);
      const std::complex<double> zij_AA = z_ij(AA, container);

      std::complex<double> B1 = -3.0*Lambda[1] + (9.0/2.0)*b_one + 1.0/(16.0*pow(PI,2))*(i*PI-1.)*(9.0*pow(Lambda[1],2)+pow((2.0*Lambda[3]+Lambda[4]),2));
      std::complex<double> B1_z = 1.0/(16.0*pow(PI,2)) * (zij_AA + zij_hh + 2.0*zij_HpHm + zij_HH + 2.0*zij_wpwm + zij_zz - (zij_HH - zij_hh)*c2a);
      B1_z += 1.0/(16.0*pow(PI,2)) * ((2.0*zij_wpwm - 2.0*zij_HpHm + zij_zz - zij_AA)*c2b - (zij_Hh + zij_hH)*s2a - (2.0*zij_Hpwm + zij_Az)*s2b);
      B1 += -3.0/2.0 * Lambda[1] * B1_z;

      std::complex<double> B2 = -3.0*Lambda[2] + (9.0/2.0)*b_two + 1.0/(16.0*pow(PI,2))*(i*PI-1.)*(9.0*pow(Lambda[2],2) + pow((2.0*Lambda[3]+Lambda[4]),2));
      std::complex<double> B2_z = 1.0/(16.0*pow(PI,2)) * (zij_AA + zij_hh + 2.0*zij_HpHm + zij_HH + 2.0*zij_wpwm + zij_zz - (zij_HH - zij_hh)*c2a);
      B2_z += 1.0/(16.0*pow(PI,2)) * (-(2.0*zij_wpwm - 2.0*zij_HpHm + zij_zz - zij_AA)*c2b + (zij_Hh + zij_hH)*s2a + (2.0*zij_Hpwm + zij_Az)*s2b);
      B2 += -3.0/2.0 * Lambda[2] * B2_z;

      std::complex<double> B3 = - (2.0*Lambda[3]+Lambda[4]) + (3.0/2.0)*(2.0*b_three+b_four) + 3.0/(16.0*pow(PI,2))*(i*PI-1.)*(Lambda[1]+Lambda[2])*(2.0*Lambda[3]+Lambda[4]);
      std::complex<double> B3_z = 1.0/(16.0*pow(PI,2)) * ( zij_AA + zij_hh + 2.0*zij_HpHm + zij_HH + 2.0*zij_wpwm + zij_zz );
      B3 += -1.0/2.0 * (2.0*Lambda[3]+Lambda[4]) * B3_z;

      std::complex<double> B4 = - (Lambda[3] + 2.0*Lambda[4]) + (3.0/2.0)*(b_three + 2.0*b_four) + (1.0/(16.0*pow(PI,2)))*(i*PI-1.)*(pow(Lambda[3],2) + 4.0*Lambda[3]*Lambda[4] + 4.0*pow(Lambda[4],2) + 9.0*pow(Lambda[5],2));
      B4 += -1.0/2.0 * (Lambda[3]+Lambda[4]+Lambda[5]) * B3_z;
      
      std::complex<double> B6 = -3.0*Lambda[5] + (9.0/2.0)*b_five + (6.0/(16.0*pow(PI,2)))*(i*PI-1.)*(Lambda[3] + 2.0*Lambda[4])*Lambda[5];
      B6 += -1.0/2.0 * (Lambda[4]+2.0*Lambda[5]) * B3_z;
      
      std::complex<double> B7 = -Lambda[1] + (3.0/2.0)*b_one + 1.0/(16.0*pow(PI,2))*(i*PI-1.)*(pow(Lambda[1],2)+pow(Lambda[4],2));
      B7 += -1.0/2.0 * Lambda[1] * B1_z;

      std::complex<double> B8 = -Lambda[2] + (3.0/2.0)*b_two + 1.0/(16.0*pow(PI,2))*(i*PI-1.)*(pow(Lambda[2],2)+pow(Lambda[4],2));
      B8 += -1.0/2.0 * Lambda[2] * B2_z;

      std::complex<double> B9 = -Lambda[4] + (3.0/2.0)*b_four + 1.0/(16.0*pow(PI,2))*(i*PI-1.)*(Lambda[1] + Lambda[2])*Lambda[4]; 
      B9 += -1.0/2.0 * Lambda[4] * B3_z;

      std::complex<double> B13 = -Lambda[3] + (3.0/2.0)*b_three + (1.0/(16.0*pow(PI,2)))*(i*PI-1.)*(pow(Lambda[3],2)+pow(Lambda[5],2));
      B13 += -1.0/2.0 * (Lambda[3]+Lambda[4]+Lambda[5]) * B3_z;

      std::complex<double> B15 = -Lambda[5] + (3.0/2.0)*b_five + (2.0/(16.0*pow(PI,2)))*(i*PI-1.)*Lambda[3]*Lambda[5];
      B15 += -1.0/2.0 * (Lambda[4]-2.0*Lambda[5]) * B3_z;

      std::complex<double> B19 = -(Lambda[3]-Lambda[4]) + (3.0/2.0)*(b_three - b_four) + (1.0/(16.0*pow(PI,2)))*(i*PI-1.)*pow((Lambda[3]-Lambda[4]),2);
      B19 += -1.0/2.0 * (Lambda[3]-Lambda[5]) * B3_z;

      std::complex<double> B20 = -Lambda[1] + (3.0/2.0)*b_one + 1.0/(16.0*pow(PI,2))*(i*PI-1.)*(pow(Lambda[1],2) + pow(Lambda[5],2));
      std::complex<double> B20_z = 1.0/(16.0*pow(PI,2)) * (zij_AA + zij_hh + zij_HH + zij_zz + (zij_HH - zij_hh)*c2a + (zij_zz - zij_AA)*c2b - (zij_Hh - zij_hH)*s2a - zij_Az*s2b);
      B20 += -1.0 * Lambda[1] * B20_z;

      std::complex<double> B21 = -Lambda[2] + (3.0/2.0)*b_two + 1.0/(16.0*pow(PI,2))*(i*PI-1.)*(pow(Lambda[2],2) + pow(Lambda[5],2));
      std::complex<double> B21_z = 1.0/(16.0*pow(PI,2)) * (zij_AA + zij_hh + zij_HH + zij_zz + (zij_HH - zij_hh)*c2a - (zij_zz - zij_AA)*c2b + (zij_Hh - zij_hH)*s2a + zij_Az*s2b);
      B21 += -1.0 * Lambda[2] * B21_z;

      std::complex<double> B22 = -Lambda[5] + (3.0/2.0)*b_five + (1.0/(16.0*pow(PI,2)))*(i*PI-1.)*(Lambda[1] + Lambda[2])*Lambda[5];
      std::complex<double> B22_z = 1.0/(16.0*pow(PI,2)) * (zij_AA + zij_hh + zij_HH + zij_zz);
      B22 += -1.0 * Lambda[5] * B22_z;
      
      std::complex<double> B30 = -(Lambda[3]+Lambda[4]) + (3.0/2.0)*(b_three+b_four) + (1.0/(16.0*pow(PI,2)))*(i*PI-1.)*pow((Lambda[3]+Lambda[4]),2);
      B30 += -1.0 * (Lambda[3] + Lambda[4]) * B22_z;
      
      // eigenvalues
      std::complex<double> a00_even_plus = 1.0/(32.0*PI) * ((B1 + B2) + sqrt(pow((B1-B2),2) + 4.*pow(B3,2)));
      std::complex<double> a00_even_minus = 1.0/(32.0*PI) * ((B1 + B2) - sqrt(pow((B1-B2),2) + 4.*pow(B3,2)));
      std::complex<double> a00_odd_plus = 1.0/(32.0*PI) * (2.*B4 + 2.*B6);
      std::complex<double> a00_odd_minus = 1.0/(32.0*PI) * (2.*B4 - 2.*B6);
      std::complex<double> a01_even_plus = 1.0/(32.0*PI) * (B7 + B8 + sqrt(pow((B7-B8),2) + 4.*pow(B9,2)));
      std::complex<double> a01_even_minus = 1.0/(32.0*PI) * (B7 + B8 - sqrt(pow((B7-B8),2) + 4.*pow(B9,2)));
      std::complex<double> a01_odd_plus = 1.0/(32.0*PI) * (2.*B13 + 2.*B15);
      std::complex<double> a01_odd_minus = 1.0/(32.0*PI) * (2.*B13 - 2.*B15);
      std::complex<double> a10_odd = 1.0/(32.0*PI) * (2.*B19);
      std::complex<double> a11_even_plus = 1.0/(32.0*PI) * (B20 + B21 + sqrt(pow((B20-B21),2) + 4.*pow(B22,2)) );
      std::complex<double> a11_even_minus = 1.0/(32.0*PI) * (B20 + B21 - sqrt(pow((B20-B21),2) + 4.*pow(B22,2)) );
      std::complex<double> a11_odd = 1.0/(32.0*PI) * (2.*B30);

      const double unitarity_upper_limit = 0.5;
      const double sigma = 1;
      double chi2 = 0.0;

      std::vector<std::complex<double>> eigenvalues = {a00_even_plus, a00_even_minus, a00_odd_plus, a00_odd_minus, a01_even_plus, \
        a01_even_minus, a01_odd_plus, a01_odd_minus, a10_odd, a11_even_plus, a11_even_minus, a11_odd};

      for(auto const& eig: eigenvalues) {
        chi2 += get_chi((abs(eig-i/2.0)),bound,less_than,unitarity_upper_limit,sigma) * pow(10,6);
      }

      #ifdef SPECBIT_DEBUG
        std::cout << "alpha THDMC: " << container.THDM_object->get_alpha() << std::endl;
        std::cout << "alpha FS: " << (container.he->get(Par::dimensionless, "alpha")) << std::endl;
        const std::vector<std::string> eigenvalue_keys = {"a00_even_plus","a00_even_minus","a00_odd_plus","a00_odd_minus","a01_even_plus", \
          "a01_even_minus","a01_odd_plus","a01_odd_minus","a10_odd","a11_even_plus","a11_even_minus","a11_odd"};
        for(unsigned j=0; j < eigenvalues.size(); j++) {
            std::cout  <<  eigenvalue_keys[j] << " | " << eigenvalues[j] << " | " << abs(eigenvalues[j]-i/2.0) << \
            " | chi^2 = " << get_chi((abs(eigenvalues[j]-i/2.0)),bound,less_than,unitarity_upper_limit,sigma) * pow(10,6) << std::endl;
        }
      #endif

      return -chi2;
  }

    double perturbativity_likelihood_THDM(THDM_spectrum_container& container) { 
      if (print_debug_checkpoints) cout << "Checkpoint: 38" << endl;
      // fill the THDM object with values from the input file
      //set constraint values
      //-----------------------------
      // all values < 4*PI for perturbativity conditions
      double perturbativity_upper_limit = 4*M_PI;
      double sigma = 4*M_PI;
      //-----------------------------

      double chi_2 = 0.0;

      complex<double> hhhh_coupling;
      // double mh0, mH, mA, mHp, sba, lambda6, lambda7, m122, tan_beta;
      // container.THDM_object->get_param_phys(mh0, mH, mA, mHp, sba, lambda6, lambda7, m122, tan_beta);

      // calculate the chi^2 from all possible 4 higgs interactions
      for (int i=1;i<5;i++) {
        for (int j=1;j<5;j++) {
          for (int k=1;k<5;k++) {
            for (int l=1;l<5;l++) {
                // TODO: This (may be) slow; prefer filling a coupling spectrum and then attaining from there
                container.THDM_object->get_coupling_hhhh(i,j,k,l,hhhh_coupling);
                chi_2 += get_chi(abs(hhhh_coupling),bound,less_than,perturbativity_upper_limit,sigma);
            }
          }
        }
      }

      return -chi_2;
    }

    double stability_likelihood_THDM(THDM_spectrum_container& container) {
      if (print_debug_checkpoints) cout << "Checkpoint: 40" << endl;// Get Yukawa Type & scale from YAML
      std::vector<double> lambda(8);
      double m122, tanb;

      container.THDM_object->get_param_gen(lambda[1], lambda[2], lambda[3], lambda[4], lambda[5], lambda[6], lambda[7], m122, tanb);

      //do the full check first - if fails continue with chi^2 calculation to guide scanner
      if (container.THDM_object->check_stability()){
        return 0.0;
      }

        double chi_2 = 0;
        double sigma = 4*M_PI;
        //observable likelihood used as this should be covered by prior and has a central value of zero
        chi_2 += get_chi(lambda[1],observable,greater_than,0,sigma);
        chi_2 += get_chi(lambda[2],observable,greater_than,0,sigma);

        if (std::isnan(sqrt(lambda[1]*lambda[2]))) {
            chi_2 = L_MAX;
        }
        else {
            chi_2 += get_chi(lambda[3],bound,greater_than,-sqrt(lambda[1]*lambda[2]),sigma);
            if (lambda[6] == 0.0 && lambda[7]==0.0) {
              chi_2 += get_chi(lambda[3]+lambda[4]-abs(lambda[5]),observable, greater_than, -sqrt(lambda[1]*lambda[2]),sigma);
            }
            else {
              chi_2 += get_chi(lambda[3]+lambda[4]-lambda[5],observable, greater_than, -sqrt(lambda[1]*lambda[2]),sigma);
            }
            // TODO: Check the need for the below..
            // loglike += get_chi(2*abs(lambda[6]+lambda[7]), observable, less_than, 1/2*(lambda[1]+lambda[2])+ lambda[3] + lambda[4] + lambda[5] ,4*PI);
        }
        return -chi_2;
    }

    double alignment_likelihood_THDM(THDM_spectrum_container& container) { 
      if (print_debug_checkpoints) cout << "Checkpoint: 46" << endl;
      //-----------------------------
      // sin(b-a) = 1 in alignment limit -distance from alignment limit:
      double sbaTol = 0.01;
      double sigma = 1.;
      //-----------------------------
      // chi2 function
      double chi2 = get_chi((1.0 - container.THDM_object->get_sba()),bound,less_than,sbaTol,sigma);
      return -chi2;
    }


    double oblique_parameters_likelihood_THDM(THDM_spectrum_container& container) { 
      if (print_debug_checkpoints) cout << "Checkpoint: 47" << endl;
      THDMC_1_7_0::Constraints constraints_object(*(container.THDM_object));

      double mh_ref = 125.0; //container.he.get(Par::Pole_Mass,"h0",1);
      double S, T, U, V, W, X;
      constraints_object.oblique_param(mh_ref, S, T, U, V, W, X);

      double chi_2 = 0.0;
      chi_2 +=  Stats::gaussian_loglikelihood(S,0.014,0.0,0.10, true);
      chi_2 +=  Stats::gaussian_loglikelihood(T,0.03,0.0,0.11, true);
      chi_2 +=  Stats::gaussian_loglikelihood(U,0.06,0.0,0.10,true); // 0.2
      chi_2 +=  Stats::gaussian_loglikelihood(V,0.30,0.0,0.38, true); // 0.3
      chi_2 +=  Stats::gaussian_loglikelihood(W,0.11,0.0,4.7, true);
      chi_2 +=  Stats::gaussian_loglikelihood(X,0.38,0.0,0.59, true); // 0.2

      return chi_2;
    }

    template <class T>
    void fill_THDM_Couplings(thdmc_couplings &result, T& THDM_object) { 
      if (print_debug_checkpoints) cout << "Checkpoint: 48" << endl;
      thdmc_couplings Couplings;
      complex<double> cs, cp, c;

      for (int h=1; h<5; h++) { if (print_debug_checkpoints) cout << "Checkpoint: 49" << endl;

        for (int f1=1; f1<4; f1++) { if (print_debug_checkpoints) cout << "Checkpoint: 50" << endl;
          for (int f2=1; f2<4; f2++) { if (print_debug_checkpoints) cout << "Checkpoint: 51" << endl;
            THDM_object.get_coupling_hdd(h,f1,f2,cs,cp);
            Couplings.hdd_cs[h][f1][f2] = cs;
            Couplings.hdd_cp[h][f1][f2] = cp;
            THDM_object.get_coupling_huu(h,f1,f2,cs,cp);
            Couplings.huu_cs[h][f1][f2] = cs;
            Couplings.huu_cp[h][f1][f2] = cp;
            THDM_object.get_coupling_hll(h,f1,f2,cs,cp);
            Couplings.hll_cs[h][f1][f2] = cs;
            Couplings.hll_cp[h][f1][f2] = cp;
            THDM_object.get_coupling_hdu(h,f1,f2,cs,cp);
            Couplings.hdu_cs[h][f1][f2] = cs;
            Couplings.hdu_cp[h][f1][f2] = cp;
            THDM_object.get_coupling_hln(h,f1,f2,cs,cp);
            Couplings.hln_cs[h][f1][f2] = cs;
            Couplings.hln_cp[h][f1][f2] = cp;
          }
        }

        for (int v1=1; v1<4; v1++) { if (print_debug_checkpoints) cout << "Checkpoint: 52" << endl;
          for (int v2=1; v2<4; v2++) { if (print_debug_checkpoints) cout << "Checkpoint: 53" << endl;
            THDM_object.get_coupling_vvh(v1,v2,h,c);
            Couplings.vvh[v1][v2][h] = c;
              for (int h2=1; h2<5; h2++) { if (print_debug_checkpoints) cout << "Checkpoint: 54" << endl;
                THDM_object.get_coupling_vvhh(v1,v2,h,h2,c);
                Couplings.vvhh[v1][v2][h][h2] = c;
              }
          }

          for (int h2=1; h2<5; h2++) { if (print_debug_checkpoints) cout << "Checkpoint: 55" << endl;
            THDM_object.get_coupling_vhh(v1,h,h2,c);
            Couplings.vhh[v1][h][h2] = c;

          }
        }

        for (int h2=1; h2<5; h2++) { if (print_debug_checkpoints) cout << "Checkpoint: 56" << endl;
          for (int h3=1; h3<5; h3++) { if (print_debug_checkpoints) cout << "Checkpoint: 57" << endl;
            THDM_object.get_coupling_hhh(h,h2,h3,c);
            Couplings.hhh[h][h2][h3] = c;
            for (int h4=1; h4<5; h4++) { if (print_debug_checkpoints) cout << "Checkpoint: 58" << endl;
              THDM_object.get_coupling_hhhh(h,h2,h3,h4,c);
              Couplings.hhhh[h][h2][h3][h4] = c;
            }
          }
        }

      }
      result = Couplings;
    }

      double global_minimum_discriminant_likelihood_THDM(THDM_spectrum_container& container) { 
        if (print_debug_checkpoints) cout << "Checkpoint: 59" << endl;
        // -----------
        //from arXiv 1303.5098v1
        //"Our vacuum is the global minimum of the potential if and only if D > 0
        //Therefore, if we only wish to make certain that we are in the global
        //minimum of the potential, regardless of the number of those minima,
        //requiring D > 0 is a necessary and sufficient condition."
        // -----------
        double lambda1 = container.he->get(Par::mass1, "lambda_1");
        double lambda2 = container.he->get(Par::mass1, "lambda_2");
        double lambda3 = container.he->get(Par::mass1, "lambda_3");
        double lambda4 = container.he->get(Par::mass1, "lambda_4");
        double lambda5 = container.he->get(Par::mass1, "lambda_5");
        double lambda6 = container.he->get(Par::mass1, "lambda_6");
        double lambda7 = container.he->get(Par::mass1, "lambda_7");
        double tb = container.he->get(Par::dimensionless, "tanb");
        double m12_2 = container.he->get(Par::mass1, "m12_2");

        // set up required quantities
        double ctb = 1./tb;
        double cb  = 1./sqrt(1.+tb*tb);
        double sb  = tb*cb;
        double sb2 = sb*sb;
        double cb2 = cb*cb;

        double v2= pow (1. / sqrt(sqrt(2.)*container.sminputs.GF),2);

        //minimization conditions to recover m11^2 and m22^2
        double m11_2 = m12_2*tb - 1/(2*v2)*(lambda1*cb2 + (lambda3+lambda4+lambda5)*sb2 + 3*lambda6*sb*cb + lambda7*sb2*tb);
        double m22_2 = m12_2*ctb - 1/(2*v2)*(lambda2*sb2 + (lambda3+lambda4+lambda5)*cb2 + lambda6*cb2*ctb + 3*lambda7*sb*cb);

        complex<double> lambda1_i = lambda1;
        complex<double> lambda2_i = lambda2;

        complex<double> k = pow((lambda1_i/lambda2_i),0.25);

        // the 'dicriminant', if this value is greater than zero then we have only one vacuum and it is global
        complex<double> discriminant = m12_2*(m11_2 - pow(k,2)*m22_2)*(tb-k);

        double sigma = 1.;
        double chi2 = 0.0;

         // calculate chi2
         // observable used due to zero being limit
        chi2 += get_chi(discriminant.real(),observable,greater_than,0.0,sigma);
        chi2 += get_chi(discriminant.imag(),observable,greater_than,0.0,sigma);

        return -chi2;
      }


      template <class T>
      void fill_THDM_Couplings_For_HB(thdmc_couplings &result, T& THDM_object)
      { if (print_debug_checkpoints) cout << "Checkpoint: 60" << endl;
        // method to fill only those couplings required by HiggsBounds
        // using this method will save computational time vs full fill_THDM_Couplings function

        thdmc_couplings Couplings;

        complex<double> cs;
        complex<double> cp;
        complex<double> c;

        for (int h=1; h<5; h++)
        { if (print_debug_checkpoints) cout << "Checkpoint: 61" << endl;

          THDM_object.get_coupling_hdd(h,3,3,cs,cp);
          Couplings.hdd_cs[h][3][3] = cs;
          Couplings.hdd_cp[h][3][3] = cp;

          THDM_object.get_coupling_huu(h,3,3,cs,cp);
          Couplings.huu_cs[h][3][3] = cs;
          Couplings.huu_cp[h][3][3] = cp;


          THDM_object.get_coupling_vvh(2,2,h,c);
          Couplings.vvh[2][2][h] = c;

          THDM_object.get_coupling_vvh(3,3,h,c);
          Couplings.vvh[3][3][h] = c;


            for (int h2=1; h2<5; h2++)
            { if (print_debug_checkpoints) cout << "Checkpoint: 62" << endl;
              THDM_object.get_coupling_vhh(2,h,h2,c);
              Couplings.vhh[2][h][h2] = c;

            }
          }


        result = Couplings;
      }

      template <class T>
      void fill_THDM_Couplings_For_HB_SMLikeComponent(thdmc_couplings &result, T& THDM_object)
      { if (print_debug_checkpoints) cout << "Checkpoint: 63" << endl;
        // function to fill only those couplings required by HiggsBounds
        // and only those required for setup of the SM Like component of input.
        // Using this method will save computational time vs fill_THDM_Couplings
        // or fill_THDM_Couplings_For_HB functions.
        thdmc_couplings Couplings;
        complex<double> cs;
        complex<double> cp;
        THDM_object.get_coupling_hdd(1,3,3,cs,cp);
        Couplings.hdd_cs[1][3][3] = cs;
        Couplings.hdd_cp[1][3][3] = cp;
        result = Couplings;
      }

      void THDM_Couplings(thdmc_couplings &result)
      { if (print_debug_checkpoints) cout << "Checkpoint: 64" << endl;
        using namespace Pipes::THDM_Couplings;
        Spectrum fullspectrum = *Dep::THDM_spectrum;
        THDMC_1_7_0::THDM THDM_object;
        THDMC_1_7_0::SM SM_object;
        int yukawa_type = runOptions->getValueOrDef<int>(1, "yukawa_type");
        // fill the THDM object with values from the input file
        fill_THDM_object(fullspectrum, THDM_object, yukawa_type);
        fill_THDM_Couplings(result,THDM_object);
      }

      void THDM_Couplings_For_HB(thdmc_couplings &result) { 
        if (print_debug_checkpoints) cout << "Checkpoint: 65" << endl;
        using namespace Pipes::THDM_Couplings_For_HB;
        Spectrum fullspectrum = *Dep::THDM_spectrum;
        THDMC_1_7_0::THDM THDM_object;
        THDMC_1_7_0::SM SM_object;
        int yukawa_type = runOptions->getValueOrDef<int>(1, "yukawa_type");
        // fill the THDM object with values from the input file
        fill_THDM_object(fullspectrum, THDM_object, yukawa_type);
        fill_THDM_Couplings_For_HB(result,THDM_object);
      }

      void THDM_Couplings_SM_Like_Model_h01(thdmc_couplings &result) { 
        if (print_debug_checkpoints) cout << "Checkpoint: 66" << endl;
        using namespace Pipes::THDM_Couplings_SM_Like_Model_h01;
        Spectrum fullspectrum = *Dep::THDM_spectrum;
        THDMC_1_7_0::THDM THDM_object;
        THDMC_1_7_0::SM SM_object;
        int yukawa_type = runOptions->getValueOrDef<int>(1, "yukawa_type");
        // fill the THDM object with values from a SM like set of values
        fill_THDM_object_SM_Like_Model(fullspectrum,THDM_object,1,yukawa_type);
        fill_THDM_Couplings_For_HB_SMLikeComponent(result,THDM_object);
      }

      void THDM_Couplings_SM_Like_Model_h02(thdmc_couplings &result) { 
        if (print_debug_checkpoints) cout << "Checkpoint: 67" << endl;
        using namespace Pipes::THDM_Couplings_SM_Like_Model_h02;
        Spectrum fullspectrum = *Dep::THDM_spectrum;
        THDMC_1_7_0::THDM THDM_object;
        THDMC_1_7_0::SM SM_object;
        int yukawa_type = runOptions->getValueOrDef<int>(1, "yukawa_type");
        // fill the THDM object with values from a SM like set of values
        fill_THDM_object_SM_Like_Model(fullspectrum,THDM_object,2,yukawa_type);
        fill_THDM_Couplings_For_HB_SMLikeComponent(result,THDM_object);
      }

      void THDM_Couplings_SM_Like_Model_A0(thdmc_couplings &result) { 
        if (print_debug_checkpoints) cout << "Checkpoint: 68" << endl;
        using namespace Pipes::THDM_Couplings_SM_Like_Model_A0;
        Spectrum fullspectrum = *Dep::THDM_spectrum;
        THDMC_1_7_0::THDM THDM_object;
        THDMC_1_7_0::SM SM_object;
        int yukawa_type = runOptions->getValueOrDef<int>(1, "yukawa_type");
        // fill the THDM object with values from a SM like set of values
        fill_THDM_object_SM_Like_Model(fullspectrum,THDM_object,3,yukawa_type);
        fill_THDM_Couplings_For_HB_SMLikeComponent(result,THDM_object);
      }

      void fill_THDM_SLHA(SLHAstruct &result)
      { if (print_debug_checkpoints) cout << "Checkpoint: 69" << endl;
        using namespace Pipes::fill_THDM_SLHA;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        THDMC_1_7_0::THDM THDM_object;
        THDMC_1_7_0::SM SM_object;

        int yukawa_type = runOptions->getValueOrDef<int>(1, "yukawa_type");

        // fill the THDM object with values from the input file
        fill_THDM_object(fullspectrum, THDM_object, yukawa_type);

        const SubSpectrum& he = fullspectrum.get_HE();
        const SubSpectrum& SM = fullspectrum.get_LE();
        const SMInputs& sminputs   = fullspectrum.get_SMInputs();

        double m_h = he.get(Par::Pole_Mass, "h0",1);
        double m_H = he.get(Par::Pole_Mass, "h0",2);
        double m_A = he.get(Par::Pole_Mass, "A0");
        double m_Hp = he.get(Par::Pole_Mass, "H+");
        double alpha = 0.0;//he.get(Par::dimensionless, "alpha");
        double tan_beta = he.get(Par::dimensionless, "tanb");

        double lambda1 = he.get(Par::mass1, "lambda_1");
        double lambda2 = he.get(Par::mass1, "lambda_2");
        double lambda3 = he.get(Par::mass1, "lambda_3");
        double lambda4 = he.get(Par::mass1, "lambda_4");
        double lambda5 = he.get(Par::mass1, "lambda_5");

        double sba = get_sba(tan_beta, alpha);

        double lambda6 = he.get(Par::mass1,"lambda_6");
        double lambda7 = he.get(Par::mass1,"lambda_7");

        double m12_2 = he.get(Par::mass1,"m12_2");

        double alphaInv = sminputs.alphainv;
        double alphaS = sminputs.alphaS;
        double GF = sminputs.GF;

        double MZ = SM.get(Par::Pole_Mass,"Z0");
        double MW = SM.get(Par::Pole_Mass,"W+");

        // double gammaZ = 2.4952;
        // double gammaW = 2.085;

        // double Me = SM.get(Par::Pole_Mass,"e-_1");
        // double Mmu = SM.get(Par::Pole_Mass,"e-_2");
        double Mtau = SM.get(Par::Pole_Mass,"e-_3");

        // double Mu = sminputs.mU; //u
        // double Md = sminputs.mD; //d
        // double Mc = sminputs.mCmC; //c
        // double Ms = sminputs.mS; //s
        double Mt = SM.get(Par::Pole_Mass,"u_3"); //t
        double Mb = SM.get(Par::Pole_Mass,"d_3"); //b

        double lambda = sminputs.CKM.lambda;
        double A = sminputs.CKM.A;
        double rho = sminputs.CKM.rhobar;
        double eta = sminputs.CKM.etabar;

        double g_prime = SM_object.get_gprime();
        double g = SM_object.get_g();
        double g_3 = 4.*M_PI*alphaS;

        SLHAstruct slha;

        SLHAea_add_block(slha, "MODSEL");;
        SLHAea_add(slha, "MODSEL", 0, 10, "2HDM", true);

        SLHAea_add_block(slha, "FMODSEL");
        SLHAea_add(slha, "FMODSEL", 1, 32, "2HDM", true);
        SLHAea_add(slha, "FMODSEL", 5, 0, "No CP-violation", true);

        SLHAea_add_block(slha, "SMINPUTS");
        SLHAea_add(slha, "SMINPUTS", 1, alphaInv, "1/alpha_em", true);
        SLHAea_add(slha, "SMINPUTS", 2, GF, "GF", true);
        SLHAea_add(slha, "SMINPUTS", 3, alphaS, "alphaS", true);
        SLHAea_add(slha, "SMINPUTS", 4, MZ, "MZ", true);
        SLHAea_add(slha, "SMINPUTS", 5, Mb, "Mb", true);
        SLHAea_add(slha, "SMINPUTS", 6, Mt, "Mt - pole", true);
        SLHAea_add(slha, "SMINPUTS", 7, Mtau, "Mtau - pole", true);

        SLHAea_add_block(slha, "GAUGE");
        SLHAea_add(slha, "GAUGE", 1, g, "g", true);
        SLHAea_add(slha, "GAUGE", 2, g_prime, "g'", true);
        SLHAea_add(slha, "GAUGE", 3, g_3, "g_3'", true);

        SLHAea_add_block(slha, "MINPAR");
        SLHAea_add(slha, "MINPAR", 3, tan_beta, "tanb", true);
        SLHAea_add(slha, "MINPAR", 11, lambda1, "lambda1", true);
        SLHAea_add(slha, "MINPAR", 12, lambda2, "lambda2", true);
        SLHAea_add(slha, "MINPAR", 13, lambda3, "lambda3", true);
        SLHAea_add(slha, "MINPAR", 14, lambda4, "lambda4", true);
        SLHAea_add(slha, "MINPAR", 15, lambda5, "lambda5", true);
        SLHAea_add(slha, "MINPAR", 16, lambda6, "lambda6", true);
        SLHAea_add(slha, "MINPAR", 17, lambda7, "lambda7", true);
        SLHAea_add(slha, "MINPAR", 18, m12_2, "m12^2", true);
        SLHAea_add(slha, "MINPAR", 20, sba, "sin(b-a)", true);
        SLHAea_add(slha, "MINPAR", 21, sqrt(1.-pow(sba,2)), "cos(b-a)", true);
        SLHAea_add(slha, "MINPAR", 24, yukawa_type, "yukawa type", true);

        SLHAea_add_block(slha, "VCKMIN");
        SLHAea_add(slha, "VCKMIN", 1, lambda, "lambda-CKM", true);
        SLHAea_add(slha, "VCKMIN", 2, A, "A-CKM", true);
        SLHAea_add(slha, "VCKMIN", 3, rho, "rhobar-CKM", true);
        SLHAea_add(slha, "VCKMIN", 4, eta, "etabar-CKM", true);

        SLHAea_add_block(slha, "MASS");
        SLHAea_add(slha, "MASS", 1, SM_object.get_qmass_pole(1), "Md - pole", true);
        SLHAea_add(slha, "MASS", 2, SM_object.get_qmass_pole(2), "Mu - pole", true);
        SLHAea_add(slha, "MASS", 3, SM_object.get_qmass_pole(3), "Ms - pole", true);
        SLHAea_add(slha, "MASS", 4, SM_object.get_qmass_pole(4), "Mc - pole", true);
        SLHAea_add(slha, "MASS", 5, SM_object.get_qmass_pole(5), "Mb - pole", true);
        SLHAea_add(slha, "MASS", 6, SM_object.get_qmass_pole(6), "Mt - pole", true);
        SLHAea_add(slha, "MASS", 11, SM_object.get_lmass_pole(1), "Me - pole", true);
        SLHAea_add(slha, "MASS", 13, SM_object.get_lmass_pole(2), "Mmu - pole", true);
        SLHAea_add(slha, "MASS", 15, SM_object.get_lmass_pole(3), "Mtau - pole", true);
        SLHAea_add(slha, "MASS", 23, MZ, "MZ", true);
        SLHAea_add(slha, "MASS", 24, MW, "MW", true);
        SLHAea_add(slha, "MASS", 25, m_h, "Mh0_1", true);
        SLHAea_add(slha, "MASS", 35, m_H, "Mh0_2", true);
        SLHAea_add(slha, "MASS", 36, m_A, "MA0", true);
        SLHAea_add(slha, "MASS", 37, m_Hp, "MHc", true);

        SLHAea_add_block(slha, "ALPHA");
        SLHAea_add(slha, "ALPHA", 0, THDM_object.get_alpha(), "alpha", true);

        vector<double> matrix_u, matrix_d, matrix_l;

        for (int i=0;i<3;i++) { if (print_debug_checkpoints) cout << "Checkpoint: 70" << endl;
          for (int j=0;j<3;j++) { if (print_debug_checkpoints) cout << "Checkpoint: 71" << endl;
            matrix_u.push_back(0);
            matrix_d.push_back(0);
            matrix_l.push_back(0);
            // fills with 9 zeros
          }
        }

        // TODO: fix below for complex kappa & gamma yukawa matrices
        // ---
        // adapted from 2HDMC code - THDMC.cpp
        // double k1,k2,k3,r1,r2,r3;
        // THDM_object.get_kappa_up(k1,k2,k3);
        // THDM_object.get_yukawas_up(r1,r2,r3);
        // (k1>0 ? matrix_u[0] = r1/k1 : matrix_u[0]=0.);
        // (k2>0 ? matrix_u[4] = r2/k2 : matrix_u[4]=0.);
        // (k3>0 ? matrix_u[8] = r3/k3 : matrix_u[8]=0.);

        // THDM_object.get_kappa_down(k1,k2,k3);
        // THDM_object.get_yukawas_down(r1,r2,r3);
        // (k1>0 ? matrix_d[0] = r1/k1 : matrix_d[0]=0.);
        // (k2>0 ? matrix_d[4] = r2/k2 : matrix_d[4]=0.);
        // (k3>0 ? matrix_d[8] = r3/k3 : matrix_d[8]=0.);

        // THDM_object.get_kappa_lepton(k1,k2,k3);
        // THDM_object.get_yukawas_lepton(r1,r2,r3);
        // (k1>0 ? matrix_l[0] = r1/k1 : matrix_l[0]=0.);
        // (k2>0 ? matrix_l[4] = r2/k2 : matrix_l[4]=0.);
        // (k3>0 ? matrix_l[8] = r3/k3 : matrix_l[8]=0.);
        // // ---

        // SLHAea_add_block(slha, "UCOUPL");
        // SLHAea_add_matrix(slha, "UCOUPL", matrix_u, 3, 3, "LU", true);

        // SLHAea_add_block(slha, "DCOUPL");
        // SLHAea_add_matrix(slha, "DCOUPL", matrix_d, 3, 3, "LU", true);

        // SLHAea_add_block(slha, "LCOUPL");
        // SLHAea_add_matrix(slha, "LCOUPL", matrix_l, 3, 3, "LU", true);

        result = slha;
      }


      // functions to fill basis at QrunTo - only available for THDMatQ
      // used for printing thdm values for plotting/debug

      void fill_THDM_coupling_basis(thdm_coupling_basis &result) { 
        if (print_debug_checkpoints) cout << "Checkpoint: 72" << endl;
        using namespace Pipes::fill_THDM_coupling_basis;
        thdm_coupling_basis couplingBasis;
        Spectrum fullspectrum = *Dep::THDM_spectrum;
        // const SMInputs& sminputs   = fullspectrum.get_SMInputs();
        std::unique_ptr<SubSpectrum> spec = fullspectrum.clone_HE();
        double runToScale = *Param.at("QrunTo");

        spec -> RunToScale(runToScale);

        double lambda1 = spec->get(Par::mass1, "lambda_1");
        double lambda2 = spec->get(Par::mass1, "lambda_2");
        double lambda3 = spec->get(Par::mass1, "lambda_3");
        double lambda4 = spec->get(Par::mass1, "lambda_4");
        double lambda5 = spec->get(Par::mass1, "lambda_5");
        double tb = spec->get(Par::dimensionless, "tanb");
        double m12_2 = spec->get(Par::mass1, "m12_2");
        double lambda6 = spec->get(Par::mass1,"lambda_6");
        double lambda7 = spec->get(Par::mass1,"lambda_7");

        couplingBasis.lambda1 = lambda1;
        couplingBasis.lambda2 = lambda2;
        couplingBasis.lambda3 = lambda3;
        couplingBasis.lambda4 = lambda4;
        couplingBasis.lambda5 = lambda5;
        couplingBasis.lambda6 = lambda6;
        couplingBasis.lambda7 = lambda7;
        couplingBasis.tanb = tb;
        couplingBasis.m12_2 = m12_2;

        result = couplingBasis;
      }

      void fill_THDM_phys_basis(thdm_physical_basis& result)
      { if (print_debug_checkpoints) cout << "Checkpoint: 73" << endl;
        using namespace Pipes::fill_THDM_phys_basis;

        thdm_physical_basis phys_basis;
        Spectrum fullspectrum = *Dep::THDM_spectrum;
        std::unique_ptr<SubSpectrum> spec = fullspectrum.clone_HE();
        double QrunTo = *Param.at("QrunTo");

        spec -> RunToScale(QrunTo);

        double m_h = spec->get(Par::Pole_Mass, "h0",1);
        double m_H = spec->get(Par::Pole_Mass, "h0",2);
        double m_A = spec->get(Par::Pole_Mass, "A0");
        double m_Hp = spec->get(Par::Pole_Mass, "H+");
        double alpha = 0.0;//spec->get(Par::dimensionless, "alpha");
        double tb = spec->get(Par::dimensionless, "tanb");
        double m12_2 = spec->get(Par::mass1, "m12_2");
        double sba = get_sba(tb, alpha);
        double lambda6 = spec->get(Par::mass1,"lambda_6");
        double lambda7 = spec->get(Par::mass1,"lambda_7");

        phys_basis.mh0 = m_h;
        phys_basis.mH0 = m_H;
        phys_basis.mA = m_A;
        phys_basis.mHp = m_Hp;
        phys_basis.sba = sba;
        phys_basis.tanb = tb;
        phys_basis.lambda6 = lambda6;
        phys_basis.lambda7 = lambda7;
        phys_basis.m12_2 = m12_2;

        result = phys_basis;
      }

      // functions to print values in coupling and physical bases
      // for testing purposes

      void print_lambda1_coupling_basis(double& result) {
        using namespace Pipes::print_lambda1_coupling_basis;
        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;
        result = couplingBasis.lambda1;
      }

      void print_lambda2_coupling_basis(double& result) {
        using namespace Pipes::print_lambda2_coupling_basis;
        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;
        result = couplingBasis.lambda2;
      }

      void print_lambda3_coupling_basis(double& result) {
        using namespace Pipes::print_lambda3_coupling_basis;
        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;
        result = couplingBasis.lambda3;
      }

      void print_lambda4_coupling_basis(double& result) {
        using namespace Pipes::print_lambda4_coupling_basis;
        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;
        result = couplingBasis.lambda4;
      }

      void print_lambda5_coupling_basis(double& result) {
        using namespace Pipes::print_lambda5_coupling_basis;
        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;
        result = couplingBasis.lambda5;
      }

      void print_tanb_coupling_basis(double& result) { 
        using namespace Pipes::print_tanb_coupling_basis;
        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;
        result = couplingBasis.tanb;
      }

      void print_m12_2_coupling_basis(double& result) {
        using namespace Pipes::print_m12_2_coupling_basis;
        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;
        result = couplingBasis.m12_2;
      }

      void print_mh0_phys_basis(double& result) {
        using namespace Pipes::print_mh0_phys_basis;
        const thdm_physical_basis physBasis = *Dep::Physical_Basis;
        result = physBasis.mh0;
      }

      void print_mH0_phys_basis(double& result) {
        using namespace Pipes::print_mH0_phys_basis;
        const thdm_physical_basis physBasis = *Dep::Physical_Basis;
        result = physBasis.mH0;
      }

      void print_mHp_phys_basis(double& result) {
        using namespace Pipes::print_mHp_phys_basis;
        const thdm_physical_basis physBasis = *Dep::Physical_Basis;
        result = physBasis.mHp;
      }

      void print_mA_phys_basis(double& result) { 
        using namespace Pipes::print_mA_phys_basis;
        const thdm_physical_basis physBasis = *Dep::Physical_Basis;
        result = physBasis.mA;
      }

      void print_tanb_phys_basis(double& result) {
        using namespace Pipes::print_tanb_phys_basis;
        const thdm_physical_basis physBasis = *Dep::Physical_Basis;
        result = physBasis.tanb;
      }

      void print_sba_phys_basis(double& result) {
        using namespace Pipes::print_sba_phys_basis;
        const thdm_physical_basis physBasis = *Dep::Physical_Basis;
        result = physBasis.sba;
      }

      void print_m12_2_phys_basis(double& result) {
        using namespace Pipes::print_m12_2_phys_basis;
        const thdm_physical_basis physBasis = *Dep::Physical_Basis;
        result = physBasis.m12_2;
      }

      /// Put together the Higgs couplings for the THDM, from partial widths only
      void THDM_higgs_couplings_pwid(HiggsCouplingsTable &result)
      { if (print_debug_checkpoints) cout << "Checkpoint: 88" << endl;
        using namespace Pipes::THDM_higgs_couplings_pwid;

        // Retrieve spectrum contents
        const Spectrum* fullspectrum = *Dep::THDM_spectrum;

        //const DecayTable::Entry& decays = *Dep::Higgs_decay_rates;
        const SubSpectrum& spec = fullspectrum->get_HE();

        // Set up neutral Higgses
        static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

        // Set the CP of the Higgs states.  Note that this would need to be more sophisticated to deal with the complex MSSM!
        result.CP[0] = 1;  //h0_1
        result.CP[1] = 1;  //h0_2
        result.CP[2] = -1; //A0

        // Work out which SM values correspond to which SUSY Higgs
        //int higgs = (*Dep::SMlike_Higgs_PDG_code == 25 ? 0 : 1);
        //int other_higgs = (higgs == 0 ? 1 : 0);
        int higgs = 0;
        int other_higgs = 1;

        // Set the decays
        result.set_neutral_decays_SM(higgs, sHneut[higgs], *Dep::Reference_SM_Higgs_decay_rates);
        result.set_neutral_decays_SM(other_higgs, sHneut[other_higgs], *Dep::Reference_SM_other_Higgs_decay_rates);
        result.set_neutral_decays_SM(2, sHneut[2], *Dep::Reference_SM_A0_decay_rates);
        result.set_neutral_decays(0, sHneut[0],  *Dep::Higgs_decay_rates);
        result.set_neutral_decays(1, sHneut[1], *Dep::h0_2_decay_rates);
        result.set_neutral_decays(2, sHneut[2], *Dep::A0_decay_rates);
        result.set_charged_decays(0, "H+", *Dep::H_plus_decay_rates);
        result.set_t_decays(*Dep::t_decay_rates);

        // Use them to compute effective couplings for all neutral higgses, except for hhZ.
        for (int i = 0; i < 3; i++)
        { if (print_debug_checkpoints) cout << "Checkpoint: 89" << endl;
          result.C_WW2[i] = result.compute_effective_coupling(i, std::pair<int,int>(24, 0), std::pair<int,int>(-24, 0));
          result.C_ZZ2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(23, 0));
          result.C_tt2[i] = result.compute_effective_coupling(i, std::pair<int,int>(6, 1), std::pair<int,int>(-6, 1));
          result.C_bb2[i] = result.compute_effective_coupling(i, std::pair<int,int>(5, 1), std::pair<int,int>(-5, 1));
          result.C_cc2[i] = result.compute_effective_coupling(i, std::pair<int,int>(4, 1), std::pair<int,int>(-4, 1));
          result.C_tautau2[i] = result.compute_effective_coupling(i, std::pair<int,int>(15, 1), std::pair<int,int>(-15, 1));
          result.C_gaga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(22, 0), std::pair<int,int>(22, 0));
          result.C_gg2[i] = result.compute_effective_coupling(i, std::pair<int,int>(21, 0), std::pair<int,int>(21, 0));
          result.C_mumu2[i] = result.compute_effective_coupling(i, std::pair<int,int>(13, 1), std::pair<int,int>(-13, 1));
          result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(21, 0));
          result.C_ss2[i] = result.compute_effective_coupling(i, std::pair<int,int>(3, 1), std::pair<int,int>(-3, 1));
        }

        // Calculate hhZ effective couplings.  Here we scale out the kinematic prefactor
        // of the decay width, assuming we are well above threshold if the channel is open.
        // If not, we simply assume SM couplings.
        const double mZ = fullspectrum->get(Par::Pole_Mass,23,0);
        const double scaling = 8.*sqrt(2.)*pi/fullspectrum->get_SMInputs().GF;
        for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        { if (print_debug_checkpoints) cout << "Checkpoint: 90" << endl;
          double mhi = spec.get(Par::Pole_Mass, sHneut[i]);
          double mhj = spec.get(Par::Pole_Mass, sHneut[j]);
          if (mhi > mhj + mZ and result.get_neutral_decays(i).has_channel(sHneut[j], "Z0"))
          { if (print_debug_checkpoints) cout << "Checkpoint: 91" << endl;
            double gamma = result.get_neutral_decays(i).width_in_GeV*result.get_neutral_decays(i).BF(sHneut[j], "Z0");
            double k[2] = {(mhj + mZ)/mhi, (mhj - mZ)/mhi};
            for (int l = 0; l < 2; l++) k[l] = (1.0 - k[l]) * (1.0 + k[l]);
            double K = mhi*sqrt(k[0]*k[1]);
            result.C_hiZ2[i][j] = scaling / (K*K*K) * gamma;
          }
          else // If the channel is missing from the decays or kinematically disallowed, just return the SM result.
          { if (print_debug_checkpoints) cout << "Checkpoint: 93" << endl;
            result.C_hiZ2[i][j] = 1.;
          }
        }

        // Work out which invisible decays are possible
        //result.invisibles = get_invisibles(spec);
      }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////// FlexibleSUSY spectrum //////////////////////////////////////////////////////////////////////////////


    /// Compute an MSSM spectrum using flexiblesusy
    // In GAMBIT there are THREE flexiblesusy MSSM spectrum generators currently in
    // use, for each of three possible boundary condition types:
    //   - GUT scale input
    //   - Electroweak symmetry breaking scale input
    //   - Intermediate scale Q input
    // These each require slightly different setup, but once that is done the rest
    // of the code required to run them is the same; this is what is contained in
    // the below template function.
    // MI for Model Interface, as defined in model_files_and_boxes.hpp
    template <class MI>
    Spectrum run_FS_spectrum_generator
        ( const typename MI::InputParameters& input
        , const SMInputs& sminputs
        , const Options& runOptions
        , const std::map<str, safe_ptr<double> >& input_Param
        )
    { if (print_debug_checkpoints) cout << "Checkpoint: 94" << endl;
      // SoftSUSY object used to set quark and lepton masses and gauge
      // couplings in QEDxQCD effective theory
      // Will be initialised by default using values in lowe.h, which we will
      // override next.
      softsusy::QedQcd oneset;

      // Fill QedQcd object with SMInputs values
      setup_QedQcd(oneset,sminputs);

      // Run everything to Mz
      oneset.toMz();

      // Create spectrum generator object
      typename MI::SpectrumGenerator spectrum_generator;

      // Spectrum generator settings
      // Default options copied from flexiblesusy/src/spectrum_generator_settings.hpp
      //
      // | enum                             | possible values              | default value   |
      // |----------------------------------|------------------------------|-----------------|
      // | precision                        | any positive double          | 1.0e-4          |
      // | max_iterations                   | any positive double          | 0 (= automatic) |
      // | algorithm                        | 0 (two-scale) or 1 (lattice) | 0 (= two-scale) |
      // | calculate_sm_masses              | 0 (no) or 1 (yes)            | 0 (= no)        |
      // | pole_mass_loop_order             | 0, 1, 2                      | 2 (= 2-loop)    |
      // | ewsb_loop_order                  | 0, 1, 2                      | 2 (= 2-loop)    |
      // | beta_loop_order                  | 0, 1, 2                      | 2 (= 2-loop)    |
      // | threshold_corrections_loop_order | 0, 1                         | 1 (= 1-loop)    |
      // | higgs_2loop_correction_at_as     | 0, 1                         | 1 (= enabled)   |
      // | higgs_2loop_correction_ab_as     | 0, 1                         | 1 (= enabled)   |
      // | higgs_2loop_correction_at_at     | 0, 1                         | 1 (= enabled)   |
      // | higgs_2loop_correction_atau_atau | 0, 1                         | 1 (= enabled)   |

      Spectrum_generator_settings settings;
      settings.set(Spectrum_generator_settings::precision, runOptions.getValueOrDef<double>(1.0e-4,"precision_goal"));
      settings.set(Spectrum_generator_settings::max_iterations, runOptions.getValueOrDef<double>(0,"max_iterations"));
      settings.set(Spectrum_generator_settings::calculate_sm_masses, runOptions.getValueOrDef<bool> (true, "calculate_sm_masses"));
      settings.set(Spectrum_generator_settings::pole_mass_loop_order, runOptions.getValueOrDef<int>(2,"pole_mass_loop_order"));
      settings.set(Spectrum_generator_settings::pole_mass_loop_order, runOptions.getValueOrDef<int>(2,"ewsb_loop_order"));
      settings.set(Spectrum_generator_settings::beta_loop_order, runOptions.getValueOrDef<int>(2,"beta_loop_order"));
      settings.set(Spectrum_generator_settings::threshold_corrections_loop_order, runOptions.getValueOrDef<int>(2,"threshold_corrections_loop_order"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_as, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_at_as"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_ab_as, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_ab_as"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_at_at, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_at_at"));
      settings.set(Spectrum_generator_settings::higgs_2loop_correction_atau_atau, runOptions.getValueOrDef<int>(1,"higgs_2loop_correction_atau_atau"));
      settings.set(Spectrum_generator_settings::top_pole_qcd_corrections, runOptions.getValueOrDef<int>(1,"top_pole_qcd_corrections"));
      settings.set(Spectrum_generator_settings::beta_zero_threshold, runOptions.getValueOrDef<int>(1.000000000e-14,"beta_zero_threshold"));
      settings.set(Spectrum_generator_settings::eft_matching_loop_order_up, runOptions.getValueOrDef<int>(1,"eft_matching_loop_order_up"));
      settings.set(Spectrum_generator_settings::eft_matching_loop_order_down, runOptions.getValueOrDef<int>(1,"eft_matching_loop_order_down"));
      settings.set(Spectrum_generator_settings::threshold_corrections, runOptions.getValueOrDef<int>(123111321,"threshold_corrections"));

      spectrum_generator.set_settings(settings);

      // Generate spectrum
      spectrum_generator.run(oneset, input);
     
      // Extract report on problems...
      const typename MI::Problems& problems = spectrum_generator.get_problems();

      // Create Model_interface to carry the input and results, and know
      // how to access the flexiblesusy routines.
      // Note: Output of spectrum_generator.get_model() returns type, e.g. CMSSM.
      // Need to convert it to type CMSSM_slha (which alters some conventions of
      // parameters into SLHA format)
      MI model_interface(spectrum_generator,oneset,input);

      // Create SubSpectrum object to wrap flexiblesusy data
      // THIS IS STATIC so that it lives on once we leave this module function. We
      // therefore cannot run the same spectrum generator twice in the same loop and
      // maintain the spectrum resulting from both. But we should never want to do
      // this.
      // A pointer to this object is what gets turned into a SubSpectrum pointer and
      // passed around Gambit.
      //
      // This object will COPY the interface data members into itself, so it is now the
      // one-stop-shop for all spectrum information, including the model interface object.
      THDMSpec<MI> thdmspec(model_interface, "FlexibleSUSY", "2.0.beta");

      // Add extra information about the scales used to the wrapper object
      // (last parameter turns on the 'allow_new' option for the override setter, which allows
      //  us to set parameters that don't previously exist)
      thdmspec.set_override(Par::mass1,spectrum_generator.get_high_scale(),"high_scale",true);
      thdmspec.set_override(Par::mass1,spectrum_generator.get_susy_scale(),"susy_scale",true);
      thdmspec.set_override(Par::mass1,spectrum_generator.get_low_scale(), "low_scale", true);

      // double sba = sin(atan(*input_Param.at("tanb")) - *input_Param.at("alpha"));
      // thdmspec.set_override(Par::dimensionless, sba, "sba", true);

      thdmspec.set_override(Par::dimensionless, 2 , "yukawa_type", true); // hardcode for now
      //thdmspec.set_override(Par::dimensionless, *input_Param.at("yukawa_type") , "yukawa_type", true);
      // **THDM THEORY ERRORS
      // ** Add theory errors

      //   static const MSSM_strs ms;

      //   static const std::vector<int> i12     = initVector(1,2);
      //   static const std::vector<int> i123    = initVector(1,2,3);
      //   static const std::vector<int> i1234   = initVector(1,2,3,4);
      //   static const std::vector<int> i123456 = initVector(1,2,3,4,5,6);

      //   // 3% theory "error"
      //   mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_pred, true);
      //   mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_pred, true);
      //   mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_6, i123456, true);
      //   mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_6, i123456, true);
      //   mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, "~chi0", i1234, true);
      //   mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, "~chi0", i1234, true);
      //   mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_3, i123, true);
      //   mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_3, i123, true);
      //   mssmspec.set_override_vector(Par::Pole_Mass_1srd_high, 0.03, ms.pole_mass_strs_1_2, i12,  true);
      //   mssmspec.set_override_vector(Par::Pole_Mass_1srd_low,  0.03, ms.pole_mass_strs_1_2, i12,  true);

      //   // Do the lightest Higgs mass separately.  The default in most codes is 3 GeV. That seems like
      //   // an underestimate if the stop masses are heavy enough, but an overestimate for most points.
      //   double rd_mh1 = 2.0 / mssmspec.get(Par::Pole_Mass, ms.h0, 1);
      //   mssmspec.set_override(Par::Pole_Mass_1srd_high, rd_mh1, ms.h0, 1, true);
      //   mssmspec.set_override(Par::Pole_Mass_1srd_low,  rd_mh1, ms.h0, 1, true);

      // Do the W mass separately.  Here we use 10 MeV based on the size of corrections from two-loop papers and advice from Dominik Stockinger.
      // double rd_mW = 0.01 / thdmspec.get(Par::Pole_Mass, "W+");
      // thdmspec.set_override(Par::Pole_Mass_1srd_high, rd_mW, "W+", true);
      // thdmspec.set_override(Par::Pole_Mass_1srd_low,  rd_mW, "W+", true);

      // Save the input value of TanBeta
      // Probably need to make it a full requirement of the MSSM SpectrumContents
      //   if(input_Param.find("TanBeta") != input_Param.end())
      //   { if (print_debug_checkpoints) cout << "Checkpoint: " << endl;
      //     thdmspec.set_override(Par::dimensionless, *input_Param.at("TanBeta"), "tanbeta(mZ)", true);
      //   }

      // Create a second SubSpectrum object to wrap the qedqcd object used to initialise the spectrum generator
      // Attach the sminputs object as well, so that SM pole masses can be passed on (these aren't easily
      // extracted from the QedQcd object, so use the values that we put into it.)
      QedQcdWrapper qedqcdspec(oneset,sminputs);

      // Deal with points where spectrum generator encountered a problem
      #ifdef SPECBIT_DEBUG
        std::cout<<"Problem? "<<problems.have_problem()<<std::endl;
      #endif
      if( problems.have_problem() )
      { if (print_debug_checkpoints) cout << "Checkpoint: 95" << endl;
         if( runOptions.getValueOrDef<bool>(false,"invalid_point_fatal") )
         { if (print_debug_checkpoints) cout << "Checkpoint: 96" << endl;
            ///TODO: Need to tell gambit that the spectrum is not viable somehow. For now
            /// just die.
            std::ostringstream errmsg;
            errmsg << "A serious problem was encountered during spectrum generation!; ";
            errmsg << "Message from FlexibleSUSY below:" << std::endl;
            problems.print_problems(errmsg);
            problems.print_warnings(errmsg);
            SpecBit_error().raise(LOCAL_INFO,errmsg.str());
         }
         else
         { if (print_debug_checkpoints) cout << "Checkpoint: 97" << endl;
            #ifdef FS_THROW_POINT
            // EXTRA DEBUG INFO
            // std::ostringstream errmsg;
            // problems.print_problems(errmsg);
            // problems.print_warnings(errmsg);
            //---------------------

            /// Check what the problem was
            /// see: contrib/MassSpectra/flexiblesusy/src/problems.hpp
            std::ostringstream msg;
            //msg << "";
            // if( have_bad_mass()      ) msg << "bad mass " << std::endl; // TODO: check which one
            //if( have_tachyon()       ) msg << "tachyon" << std::endl;
            //if( have_thrown()        ) msg << "error" << std::endl;
            //if( have_non_perturbative_parameter()   ) msg << "non-perturb. param" << std::endl; // TODO: check which
            //if( have_failed_pole_mass_convergence() ) msg << "fail pole mass converg." << std::endl; // TODO: check which
            //if( no_ewsb()            ) msg << "no ewsb" << std::endl;
            //if( no_convergence()     ) msg << "no converg." << std::endl;
            //if( no_perturbative()    ) msg << "no pertub." << std::endl;
            //if( no_rho_convergence() ) msg << "no rho converg." << std::endl;
            //if( msg.str()=="" ) msg << " Unrecognised problem! ";

            /// Fast way for now:
            problems.print_problems(msg);
            invalid_point().raise(msg.str()); //TODO: This message isn't ending up in the logs.
            #endif 
            // invalid_point().raise(msg.str());
         }
      }

      if( problems.have_warning() )
      { if (print_debug_checkpoints) cout << "Checkpoint: 98" << endl;
         std::ostringstream msg;
         problems.print_warnings(msg);
         SpecBit_warning().raise(LOCAL_INFO,msg.str()); //TODO: Is a warning the correct thing to do here?
      }

      // Write SLHA file (for debugging purposes...)
      #ifdef SPECBIT_DEBUG
         typename MI::SlhaIo slha_io;
         slha_io.set_spinfo(problems);
         slha_io.set_sminputs(oneset);
        //  slha_io.set_minpar(input);
        //  slha_io.set_extpar(input);
         slha_io.set_spectrum(thdmspec.model_interface.model);
         slha_io.write_to_file("SpecBit/initial_THDM_spectrum->slha");
      #endif

      // Retrieve any mass cuts
      static const Spectrum::mc_info mass_cut = runOptions.getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
      static const Spectrum::mr_info mass_ratio_cut = runOptions.getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

      // Package QedQcd SubSpectrum object, MSSM SubSpectrum object, and SMInputs struct into a 'full' Spectrum object
        if (print_debug_checkpoints) model_interface.model.print(cout);
        return Spectrum(qedqcdspec,thdmspec,sminputs,&input_Param,mass_cut,mass_ratio_cut);
    }


    template <class THDMInputStruct>
    void fill_THDM_input(THDMInputStruct &input, const std::map<str, safe_ptr<double> >& Param)
    { if (print_debug_checkpoints) cout << "Checkpoint: 99" << endl;
      // read in THDM model parameters
      double lambda_1 = *Param.at("lambda_1");
      double lambda_2 = *Param.at("lambda_2");
      double lambda_3 = *Param.at("lambda_3");
      double lambda_4 = *Param.at("lambda_4");
      double lambda_5 = *Param.at("lambda_5");
      double m12_2 = *Param.at("m12_2");
      double tb = *Param.at("tanb");
      double lambda_6 = *Param.at("lambda_6");
      double lambda_7 = *Param.at("lambda_7");

      //double valued parameters
      input.TanBeta     = tb;
      input.Lambda1IN      = lambda_1; 
      input.Lambda2IN      = lambda_2; 
      input.Lambda3IN      = lambda_3;
      input.Lambda4IN      = lambda_4;
      input.Lambda5IN      = lambda_5;
      input.Lambda6IN      = lambda_6;
      input.Lambda7IN      = lambda_7;

      if (print_debug_checkpoints) cout << "Checkpoint: 99D" << endl;

      input.M122IN      = m12_2;           
      input.Qin         = *Param.at("Qin"); 

      // Sanity checks
      if(input.TanBeta<0)
      { if (print_debug_checkpoints) cout << "Checkpoint: 100" << endl;
         std::ostringstream msg;
         msg << "Tried to set TanBeta parameter to a negative value ("<<input.TanBeta<<")! This parameter must be positive. Please check your inifile and try again.";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }
    }

    void get_THDM_spectrum_FS(Spectrum& result) { 
      if (print_debug_checkpoints) cout << "Checkpoint: 101" << endl;

      using namespace softsusy;
      namespace myPipe = Pipes::get_THDM_spectrum_FS;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      // const Options& runOptions=*myPipe::runOptions;
    
      int yukawa_type = myPipe::runOptions->getValueOrDef<int>(1, "yukawa_type");
      yukawa_type = 2;
      THDM_II_input_parameters input;
      fill_THDM_input(input,myPipe::Param);

      switch(yukawa_type)
      { if (print_debug_checkpoints) cout << "Checkpoint: 102" << endl;
        case 1:
        { if (print_debug_checkpoints) cout << "Checkpoint: 103" << endl;
          // THDM_I_input_parameters input;
          // fill_THDM_input(input,myPipe::Param);
          // result = run_FS_spectrum_generator<THDM_I_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
          // break;
        }
        case 2:
        { if (print_debug_checkpoints) cout << "Checkpoint: 104" << endl;
          result = run_FS_spectrum_generator<THDM_II_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
          break;
        }
        case 3:
        { if (print_debug_checkpoints) cout << "Checkpoint: 105" << endl;
        //   THDM_lepton_input_parameters input;
        //   fill_THDM_input(input,myPipe::Param);
        //   result = run_FS_spectrum_generator<THDM_lepton_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
          break;
        }
        case 4:
        { if (print_debug_checkpoints) cout << "Checkpoint: 106" << endl;
        //   THDM_flipped_input_parameters input;
        //   fill_THDM_input(input,myPipe::Param);
        //   result = run_FS_spectrum_generator<THDM_flipped_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
          break;
        }
        default:
        { if (print_debug_checkpoints) cout << "Checkpoint: 107" << endl;
          std::ostringstream msg;
          msg << "Tried to set the Yukawa Type to "<< yukawa_type <<" . Yukawa Type should be 1-4.";
          SpecBit_error().raise(LOCAL_INFO,msg.str());
          exit(1);
          break;
        }
      }

    }

    void test_THDM_spectrum_1(double &result) { 
        using namespace Pipes::test_THDM_spectrum_1;
        Spectrum fullspectrum = *Dep::THDM_spectrum;
        std::unique_ptr<SubSpectrum> spec = fullspectrum.clone_HE();
        double QrunTo = *Param.at("QrunTo");

        cout << "---- running to scale: " << QrunTo << "GeV. "<< endl;
        cout << "mh0 = " <<  spec->get(Par::Pole_Mass, "h0", 1) << endl;
        cout <<  "mH0 = " << spec->get(Par::Pole_Mass, "h0", 2) << endl;
        cout <<  "mA = " << spec->get(Par::Pole_Mass, "A0") << endl;
        cout << "mC = " <<  spec->get(Par::Pole_Mass, "H+") << endl;
        // cout << "alpha = " <<  spec->get(Par::dimensionless, "alpha") << endl;
        cout << "tan(beta) = " <<  spec->get(Par::dimensionless, "tanb") << endl;
        cout <<  "m12_2 = " << spec->get(Par::mass1, "m12_2") << endl;
        cout <<  "sin(theta_W) = " << spec->get(Par::dimensionless, "sinW2") << endl;
        double lambda_1 = spec->get(Par::mass1, "lambda_1");
        double lambda_2 = spec->get(Par::mass1, "lambda_2");
        double lambda_3 = spec->get(Par::mass1, "lambda_3");
        double lambda_4 = spec->get(Par::mass1, "lambda_4");
        double lambda_5 = spec->get(Par::mass1, "lambda_5");
        cout << "lambda_1 = " << lambda_1 << endl;
        cout << "lambda_2 = " << lambda_2 << endl;
        cout << "lambda_3 = " << lambda_3 << endl;
        cout << "lambda_4 = " << lambda_4 << endl;
        cout << "lambda_5 = " << lambda_5 << endl;

        std::vector<double> lambdas = {lambda_1,lambda_2,lambda_3,lambda_4,lambda_5};
        double check_pertubativity = true;
        for(int i=0; i<int(lambdas.size()); i++) {
          if(abs(lambdas[i]) > 4*PI) check_pertubativity = false ;
        }

        if(check_pertubativity) {
          spec -> RunToScale(QrunTo);

          double mh0_1 = spec->get(Par::Pole_Mass, "h0", 1);
          double mh0_2 = spec->get(Par::Pole_Mass, "h0", 2);
          double mA0 = spec->get(Par::Pole_Mass, "A0");
          double mHm = spec->get(Par::Pole_Mass, "H+");
          double alpha = 0.0;//spec->get(Par::dimensionless, "alpha");
          double tb = spec->get(Par::dimensionless, "tanb");
          double m12_2 = spec->get(Par::mass1, "m12_2");
          double mh0_1_run = spec->get(Par::mass1, "h0", 1);
          double mh0_2_run = spec->get(Par::mass1, "h0", 2);
          double mA0_run = spec->get(Par::mass1, "A0");
          double mHm_run = spec->get(Par::mass1, "H+");
          lambda_1 = spec->get(Par::mass1, "lambda_1");
          lambda_2 = spec->get(Par::mass1, "lambda_2");
          lambda_3 = spec->get(Par::mass1, "lambda_3");
          lambda_4 = spec->get(Par::mass1, "lambda_4");
          lambda_5 = spec->get(Par::mass1, "lambda_5");
          cout << "---- after running to scale: " << QrunTo << "GeV. "<< endl;
          cout << "----------------------------------" << endl;
          cout << "The FlexibleSUSY generated spectrum is, using tree-level input relations:" << endl;
          cout << "mh0_1 = " << mh0_1 << endl;
          cout << "mh0_2 = " << mh0_2 << endl;
          cout << "mA0 = " << mA0 << endl;
          cout << "mHm = " << mHm << endl;
          cout << "alpha = " << alpha << endl;
          cout << "tb = " << tb << endl;
          cout << "m12_2 = " << m12_2 << endl;
          cout << "----------------------------------" << endl;
          cout << "mh0_1_run = " << mh0_1_run << endl;
          cout << "mh0_2_run = " << mh0_2_run << endl;
          cout << "mA0_run = " << mA0_run << endl;
          cout << "mHm_run = " << mHm_run << endl;
          cout << "----------------------------------" << endl;
          cout << "lambda_1 = " << lambda_1 << endl;
          cout << "lambda_2 = " << lambda_2 << endl;
          cout << "lambda_3 = " << lambda_3 << endl;
          cout << "lambda_4 = " << lambda_4 << endl;
          cout << "lambda_5 = " << lambda_5 << endl;
          cout << "----------------------------------" << endl;
        }
        else {
          cout << "Perturbativity failed: Did not run to scale.. Would most likely fail at FS level." << endl;
        }
        result = 0;
    }

    void test_THDM_spectrum_2(double &result) {
      using namespace Pipes::test_THDM_spectrum_2;
      Spectrum fullspectrum = *Dep::THDM_spectrum;
      SubSpectrum& spec = fullspectrum.get_HE();
      double mh0_1 = spec.get(Par::Pole_Mass, "h0",1);
      double mh0_2 = spec.get(Par::Pole_Mass, "h0",2);
      double mA0 = spec.get(Par::Pole_Mass, "A0");
      double mHm = spec.get(Par::Pole_Mass, "H+");
      double alpha = 0.0;//;spec.get(Par::dimensionless, "alpha");
      double tb = spec.get(Par::dimensionless, "tanb");
      cout << "----------------------------------" << endl;
      cout << "The simple container spectrum is:" << endl;
      double sba = get_sba(tb, alpha);
      cout << "mh0_1 = " << mh0_1 << endl;
      cout << "mh0_2 = " << mh0_2 << endl;
      cout << "mA0 = " << mA0 << endl;
      cout << "mHm = " << mHm << endl;
      cout << "sba = " << sba << endl;
      cout << "tb = " << tb << endl;
      cout << "----------------------------------" << endl;
      result = 0;
    }


    void fill_map_from_THDMspectrum(std::map<std::string,double>& specmap, const Spectrum& thdmspec);

    void get_THDM_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_THDM_spectrum_as_map;
      const Spectrum& thdmspec(*myPipe::Dep::THDM_spectrum);
      fill_map_from_THDMspectrum(specmap, thdmspec);
    }

    void fill_map_from_THDMspectrum(std::map<std::string,double>& specmap, const Spectrum& thdmspec)
    {
      /// Add everything... use spectrum contents routines to automate task
      static const SpectrumContents::THDM contents;
      static const std::vector<SpectrumParameter> required_parameters = contents.all_parameters();

      for(std::vector<SpectrumParameter>::const_iterator it = required_parameters.begin();
           it != required_parameters.end(); ++it)
      {
         const Par::Tags        tag   = it->tag();
         const std::string      name  = it->name();
         const std::vector<int> shape = it->shape();

         /// Verification routine should have taken care of invalid shapes etc, so won't check for that here.

         // Check scalar case
         if(shape.size()==1 and shape[0]==1)
         {
           std::ostringstream label;
           label << name <<" "<< Par::toString.at(tag);
           specmap[label.str()] = thdmspec.get_HE().get(tag,name);
         }
         // Check vector case
         else if(shape.size()==1 and shape[0]>1)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             std::ostringstream label;
             label << name <<"_"<<i<<" "<< Par::toString.at(tag);
             specmap[label.str()] = thdmspec.get_HE().get(tag,name,i);
           }
         }
         // Check matrix case
         else if(shape.size()==2)
         {
           for(int i = 1; i<=shape[0]; ++i) {
             for(int j = 1; j<=shape[0]; ++j) {
               std::ostringstream label;
               label << name <<"_("<<i<<","<<j<<") "<<Par::toString.at(tag);
               specmap[label.str()] = thdmspec.get_HE().get(tag,name,i,j);
             }
           }
         }
         // Deal with all other cases
         else
         {
           // ERROR
           std::ostringstream errmsg;
           errmsg << "Error, invalid parameter received while converting THDMspectrum to map of strings! This should no be possible if the spectrum content verification routines were working correctly; they must be buggy, please report this.";
           errmsg << "Problematic parameter was: "<< tag <<", " << name << ", shape="<< shape;
           utils_error().forced_throw(LOCAL_INFO,errmsg.str());
         }
      }

    }

  } // end namespace SpecBit
} // end namespace Gambit
