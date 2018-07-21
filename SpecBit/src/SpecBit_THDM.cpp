//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit
///
///  SpecBit module functions related to the
///  THDM
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Filip Ranec
///    \date 2016 July
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

#define PI 3.14159265

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


// Switch for debug mode
// #define SpecBit_DBUG
// #define SPECBIT_DEBUG
bool debug_THDM = true;

namespace Gambit
{

  namespace SpecBit
  {
    using namespace LogTags;
    using namespace flexiblesusy;
    using namespace std;

    void get_CKM_from_Wolfenstein_parameters(complex<double> CKM[2][2], double lambda, double A, double rho, double eta)
    { if (debug_THDM) cout << "DBG 3" << endl;
      complex<double> i_eta(0, eta);

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


    //forward declerations
    double get_sba(double tanb, double alpha);
    std::vector<double> convertToCouplingBasis(double m_h, double m_H, double m_A, double m_Hp, double tb, double alpha, double m12_2, double lambda6, double lambda7, double GF);


    /// Get a Spectrum object wrapper for the THDM model
    void get_THDM_spectrum(Spectrum &result)
    { if (debug_THDM) cout << "DBG 4" << endl;
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

      double m_h = *myPipe::Param.at("mh0");
      double m_H = *myPipe::Param.at("mH0");
      double m_A = *myPipe::Param.at("mA");
      double m_Hp = *myPipe::Param.at("mC");
      double alpha = *myPipe::Param.at("alpha");
      double lambda6 = *myPipe::Param.at("lambda_6");
      double lambda7 = *myPipe::Param.at("lambda_7");
      double m12_2 =*myPipe::Param.at("m12_2");
      double tan_beta = *myPipe::Param.at("tanb");

      //Check Yukawa Type Validity
      int YukawaType = myPipe::runOptions->getValueOrDef<int>(2, "YukawaType");
      if( YukawaType > 0 && YukawaType < 5 )
      { if (debug_THDM) cout << "DBG 5" << endl;
        //Yukawa Type is valid
      }
      else
      { if (debug_THDM) cout << "DBG 6" << endl;
        std::ostringstream msg;
        msg << "Tried to set the Yukawa Type to "<< YukawaType <<" . Yukawa Type should a number 1-4.";
        SpecBit_error().raise(LOCAL_INFO,msg.str());
        exit(1);
      }

      // quantities needed to fill container spectrum, intermediate calculations
      double alpha_em = 1.0 / sminputs.alphainv;
      double C = alpha_em * Pi / (sminputs.GF * pow(2,0.5));
      double sinW2 = 0.5 - pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double cosW2 = 0.5 + pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      double e = pow( 4*Pi*( alpha_em ),0.5) ;

      thdm_model.mh0           = m_h;
      thdm_model.mH0           = m_H;
      thdm_model.mA0           = m_A;
      thdm_model.mC            = m_Hp;
      thdm_model.tanb                     = tan_beta;
      thdm_model.m12_2                    = m12_2;
      thdm_model.lambda6                  = lambda6;
      thdm_model.lambda7                  = lambda7;
      thdm_model.alpha                    = alpha;

      std::vector<double> Lambda = convertToCouplingBasis(m_h, m_H, m_A, m_Hp, tan_beta, alpha, m12_2, lambda6, lambda7, sminputs.GF);

      thdm_model.lambda1 = Lambda[1];
      thdm_model.lambda2 = Lambda[2];
      thdm_model.lambda3 = Lambda[3];
      thdm_model.lambda4 = Lambda[4];
      thdm_model.lambda5 = Lambda[5];

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
      if (debug_THDM) cout << "DBG 4A" << endl;


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

      cout << endl << "###" << endl <<"GREAT START" << endl << "###" << endl << endl;
      }

      template <class A, class B>
      void fill_THDM_object(A& inputTHDM, B& inputSM, Spectrum& spec, int YukawaType)
      { if (debug_THDM) cout << "DBG 7" << endl;
        //Takes in the spectrum and fills a THDM object which is defined
        //in 2HDMC. Any 2HDMC functions can then be called on this object.

        const SubSpectrum& he = spec.get_HE();
        const SubSpectrum& SM = spec.get_LE();
        const SMInputs& sminputs   = spec.get_SMInputs();

        double m_h = he.get(Par::Pole_Mass,"h0",1);
        double m_H = he.get(Par::Pole_Mass,"h0",2);
        double m_A = he.get(Par::Pole_Mass, "A0");
        double m_Hp = he.get(Par::Pole_Mass, "H+");
        double alpha = he.get(Par::dimensionless, "alpha");
        double tan_beta = he.get(Par::dimensionless, "tanb");

        double lambda6 = he.get(Par::mass1, "lambda_6");
        double lambda7 = he.get(Par::mass1, "lambda_7");

        double m12_2 = he.get(Par::mass1,"m12_2");

        double sba = get_sba(tan_beta, alpha);

        inputSM.set_alpha(1/(sminputs.alphainv));
        inputSM.set_alpha_s(sminputs.alphaS);
        inputSM.set_GF(sminputs.GF);

        inputSM.set_MZ(SM.get(Par::Pole_Mass,"Z0"));
        inputSM.set_MW(SM.get(Par::Pole_Mass,"W+"));

        inputSM.set_gamma_Z(2.4952);
        inputSM.set_gamma_W(2.085);

        inputSM.set_lmass_pole(1,SM.get(Par::Pole_Mass,"e-_1"));
        inputSM.set_lmass_pole(2,SM.get(Par::Pole_Mass,"e-_2"));
        inputSM.set_lmass_pole(3,SM.get(Par::Pole_Mass,"e-_3"));

        // inputSM.set_qmass_msbar(2,SM.get(Par::mass1,"u_1")); //u
        // inputSM.set_qmass_msbar(1,SM.get(Par::mass1,"d_1")); //d
        // inputSM.set_qmass_msbar(4,SM.get(Par::mass1,"u_2")); //c
        // inputSM.set_qmass_msbar(3,SM.get(Par::mass1,"d_2")); //s

        inputSM.set_qmass_msbar(2,sminputs.mU); //u
        inputSM.set_qmass_msbar(1,sminputs.mD); //d
        inputSM.set_qmass_msbar(4,sminputs.mCmC); //c
        inputSM.set_qmass_msbar(3,sminputs.mS); //s
        inputSM.set_qmass_pole(6,SM.get(Par::Pole_Mass,"u_3")); //t
        inputSM.set_qmass_pole(5,SM.get(Par::Pole_Mass,"d_3")); //b

        complex<double> CKMMatrix[2][2];
        get_CKM_from_Wolfenstein_parameters(CKMMatrix, sminputs.CKM.lambda, sminputs.CKM.A, sminputs.CKM.rhobar, sminputs.CKM.etabar);
        inputSM.set_CKM(abs(CKMMatrix[0][0]), abs(CKMMatrix[0][1]), abs(CKMMatrix[0][2]), abs(CKMMatrix[1][0]), abs(CKMMatrix[1][1]),
                abs(CKMMatrix[1][2]), abs(CKMMatrix[2][0]), abs(CKMMatrix[2][1]), abs(CKMMatrix[2][2]));

        inputTHDM.set_SM(inputSM);

        inputTHDM.set_param_phys(m_h, m_H, m_A, m_Hp, sba, lambda6, lambda7, m12_2, tan_beta);
        inputTHDM.set_yukawas_type(YukawaType);

      }

      unique_ptr<SubSpectrum> returnHESubSpectrumAtScale(const Spectrum& spec, double scale)
      { if (debug_THDM) cout << "DBG 8" << endl;
        unique_ptr<SubSpectrum> SubSpectrumToScale = spec.clone_HE();

        SubSpectrumToScale -> RunToScale(scale);

        return SubSpectrumToScale;
      }

      template <class A, class B>
      void fill_THDM_object_AtScale(A& inputTHDM, B& inputSM, Spectrum& spec, int YukawaType, double scale)
      { if (debug_THDM) cout << "DBG 9" << endl;
        //Takes in the spectrum and fills a THDM object which is defined
        //in 2HDMC. Any 2HDMC functions can then be called on this object.

        const SubSpectrum& SM = spec.get_LE();
        const SMInputs& sminputs   = spec.get_SMInputs();

        unique_ptr<SubSpectrum> he = spec.clone_HE();

        he -> RunToScale(scale);

        double m_h = he->get(Par::Pole_Mass, "h0",1);
        double m_H = he->get(Par::Pole_Mass, "h0",2);
        double m_A = he->get(Par::Pole_Mass, "A0");
        double m_Hp = he->get(Par::Pole_Mass, "H+");
        double alpha = he->get(Par::dimensionless, "alpha");
        double tan_beta = he->get(Par::dimensionless, "tanb");

        double lambda6 = he->get(Par::mass1, "lambda_6");
        double lambda7 = he->get(Par::mass1, "lambda_7");

        double m12_2 = he->get(Par::mass1,"m12_2");

        double sba = get_sba(tan_beta, alpha);

        inputSM.set_alpha(1/(sminputs.alphainv));
        inputSM.set_alpha_s(sminputs.alphaS);
        inputSM.set_GF(sminputs.GF);

        inputSM.set_MZ(SM.get(Par::Pole_Mass,"Z0"));
        inputSM.set_MW(SM.get(Par::Pole_Mass,"W+"));

        inputSM.set_gamma_Z(2.4952);
        inputSM.set_gamma_W(2.085);

        inputSM.set_lmass_pole(1,SM.get(Par::Pole_Mass,"e-_1"));
        inputSM.set_lmass_pole(2,SM.get(Par::Pole_Mass,"e-_2"));
        inputSM.set_lmass_pole(3,SM.get(Par::Pole_Mass,"e-_3"));

        // inputSM.set_qmass_msbar(2,SM.get(Par::mass1,"u_1")); //u
        // inputSM.set_qmass_msbar(1,SM.get(Par::mass1,"d_1")); //d
        // inputSM.set_qmass_msbar(4,SM.get(Par::mass1,"u_2")); //c
        // inputSM.set_qmass_msbar(3,SM.get(Par::mass1,"d_2")); //s

        inputSM.set_qmass_msbar(2,sminputs.mU); //u
        inputSM.set_qmass_msbar(1,sminputs.mD); //d
        inputSM.set_qmass_msbar(4,sminputs.mCmC); //c
        inputSM.set_qmass_msbar(3,sminputs.mS); //s
        inputSM.set_qmass_pole(6,SM.get(Par::Pole_Mass,"u_3")); //t
        inputSM.set_qmass_pole(5,SM.get(Par::Pole_Mass,"d_3")); //b

        complex<double> CKMMatrix[2][2];
        get_CKM_from_Wolfenstein_parameters(CKMMatrix, sminputs.CKM.lambda, sminputs.CKM.A, sminputs.CKM.rhobar, sminputs.CKM.etabar);
        inputSM.set_CKM(abs(CKMMatrix[0][0]), abs(CKMMatrix[0][1]), abs(CKMMatrix[0][2]), abs(CKMMatrix[1][0]), abs(CKMMatrix[1][1]),
                abs(CKMMatrix[1][2]), abs(CKMMatrix[2][0]), abs(CKMMatrix[2][1]), abs(CKMMatrix[2][2]));

        inputTHDM.set_SM(inputSM);

        inputTHDM.set_param_phys(m_h, m_H, m_A, m_Hp, sba, lambda6, lambda7, m12_2, tan_beta);
        inputTHDM.set_yukawas_type(YukawaType);

      }

      template <class A, class B>
      void fill_THDM_object_SM_Like_Model(A& inputTHDM, B& inputSM, Spectrum& spec, int HiggsNumber, int YukawaType)
      { if (debug_THDM) cout << "DBG 10" << endl;
        //Fills a 2HDMC object with SM-like input, makes use of the decoupling limit

        const SubSpectrum& he = spec.get_HE();
        const SubSpectrum& SM = spec.get_LE();
        const SMInputs& sminputs   = spec.get_SMInputs();

        // in the decoupling limit THDM-> SM
        double m_h;

        // which higgs mass to use as SM higgs
        switch (HiggsNumber)
        { if (debug_THDM) cout << "DBG 11" << endl;
          case 1:
            m_h = he.get(Par::Pole_Mass,"h0",1);
            break;
          case 2:
            m_h = he.get(Par::Pole_Mass,"h0",2);
            break;
          case 3:
            m_h = he.get(Par::Pole_Mass,"A0");
            break;
          default:
            m_h = he.get(Par::Pole_Mass,"h0",1);
            break;
        }

        double m_H = m_h*100;
        double m_A = m_h*100;
        double m_Hp = m_h*100;
        double sba = 1.0;
        double lambda6 = 0.;
        double lambda7 = 0.;
        double m12_2 = 0.;
        double tan_beta = 1.;

        inputSM.set_alpha(1/(sminputs.alphainv));
        inputSM.set_alpha_s(sminputs.alphaS);
        inputSM.set_GF(sminputs.GF);
        inputSM.set_MZ(SM.get(Par::Pole_Mass,"Z0"));
        inputSM.set_MW(SM.get(Par::Pole_Mass,"W+"));

        inputSM.set_gamma_Z(2.4952);
        inputSM.set_gamma_W(2.085);

        inputSM.set_lmass_pole(1,SM.get(Par::Pole_Mass,"e-_1"));
        inputSM.set_lmass_pole(2,SM.get(Par::Pole_Mass,"e-_2"));
        inputSM.set_lmass_pole(3,SM.get(Par::Pole_Mass,"e-_3"));

        inputSM.set_qmass_msbar(2,sminputs.mU); //u
        inputSM.set_qmass_msbar(1,sminputs.mD); //d
        inputSM.set_qmass_msbar(4,sminputs.mCmC); //c
        inputSM.set_qmass_msbar(3,sminputs.mS); //s
        inputSM.set_qmass_pole(6,SM.get(Par::Pole_Mass,"u_3")); //t
        inputSM.set_qmass_pole(5,SM.get(Par::Pole_Mass,"d_3")); //b

        complex<double> CKMMatrix[2][2];
        get_CKM_from_Wolfenstein_parameters(CKMMatrix, sminputs.CKM.lambda, sminputs.CKM.A, sminputs.CKM.rhobar, sminputs.CKM.etabar);
        inputSM.set_CKM(abs(CKMMatrix[0][0]), abs(CKMMatrix[0][1]), abs(CKMMatrix[0][2]), abs(CKMMatrix[1][0]), abs(CKMMatrix[1][1]),
                abs(CKMMatrix[1][2]), abs(CKMMatrix[2][0]), abs(CKMMatrix[2][1]), abs(CKMMatrix[2][2]));

        inputTHDM.set_SM(inputSM);

        inputTHDM.set_param_phys(m_h, m_H, m_A, m_Hp, sba, lambda6, lambda7, m12_2, tan_beta);
        inputTHDM.set_yukawas_type(YukawaType);

      }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////USEFUL FUNCTIONS FOR PARAMETER CONVERSIONS////////////////////////////////////////////////////////////////

    double get_sba(double tanb, double alpha)
    { if (debug_THDM) cout << "DBG 12" << endl;
        return sin(atan(tanb)-alpha);
    }

    std::vector<double> convertToCouplingBasis(double m_h, double m_H, double m_A, double m_Hp, double tb, double alpha, double m12_2, double lambda6, double lambda7, double GF)
    { if (debug_THDM) cout << "DBG 13" << endl;
        // set up required quantities
        double sba = get_sba(tb, alpha);

        double beta = atan(tb);
        double ctb = 1./tb;
        double cb  = 1./sqrt(1.+tb*tb);
        double sb  = tb*cb;
        double sb2 = sb*sb;
        double cb2 = cb*cb;

        double sa  = sin(alpha);
        double sa2 = sa*sa;
        double ca  = cos(alpha);
        double ca2 = ca*ca;

        double cba = sqrt(1.-sba*sba);

        double v2= pow (1. / sqrt(sqrt(2.)*GF),2);

        double lambda_1=(m_H*m_H*ca2+m_h*m_h*sa2-m12_2*tb)/v2/cb2-1.5*lambda6*tb+0.5*lambda7*tb*tb*tb;
        double lambda_2=(m_H*m_H*sa2+m_h*m_h*ca2-m12_2*ctb)/v2/sb2+0.5*lambda6*ctb*ctb*ctb-1.5*lambda7*ctb;
        double lambda_3=((m_H*m_H-m_h*m_h)*ca*sa+2.*m_Hp*m_Hp*sb*cb-m12_2)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;
        double lambda_4=((m_A*m_A-2.*m_Hp*m_Hp)*cb*sb+m12_2)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;
        double lambda_5=(m12_2-m_A*m_A*sb*cb)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;

        std::vector<double> Lambda(6);
        Lambda[0] = 0.0;
        Lambda[1] = lambda_1;
        Lambda[2] = lambda_2;
        Lambda[3] = lambda_3;
        Lambda[4] = lambda_4;
        Lambda[5] = lambda_5;

        return Lambda;

    }

    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////THDM CONSTRAINT CALCULATION FUNCTIONS/////////////////////////////////////////////////////////////////////

      ///Error functions///
      // Error functions are used throughout to calculate the absolute distance
      // of a point or set of points from a given true value.

      double errorFunctionLessThan(double lessThanNumber, double value) { if (debug_THDM) cout << "DBG " << endl;
      	double error;

      	if(value<lessThanNumber)
      	{ if (debug_THDM) cout << "DBG 14" << endl;
      		return 0;
      		}
      	else
      	{ if (debug_THDM) cout << "DBG 15" << endl;
      		error = value-lessThanNumber;
      		return pow(error,1);
      	}
      }

      double errorFunctionGreaterThan(double greaterThanNumber, double value){ if (debug_THDM) cout << "DBG " << endl;
      	double error;

      	if(value>greaterThanNumber)
      	{ if (debug_THDM) cout << "DBG 16" << endl;
      		return 0;
      		}
      	else
      	{ if (debug_THDM) cout << "DBG 17" << endl;
      		error = abs(value-greaterThanNumber);
      		return pow(error,1);
      	}
      }

      double errorFunctionComplexGreaterThan(complex<double> greaterThanNumber, complex<double> value){ if (debug_THDM) cout << "DBG " << endl;

          double error = 0;

          double realGreaterThan = greaterThanNumber.real();
          double imagGreaterThan = greaterThanNumber.imag();

          double realValue = value.real();
          double imagValue = value.imag();

          if(realValue<realGreaterThan)
          { if (debug_THDM) cout << "DBG 18" << endl;
              error = error + abs(realValue - realGreaterThan);
          }

          if(imagValue<imagGreaterThan)
          { if (debug_THDM) cout << "DBG 19" << endl;
              error = error + abs(imagValue - imagGreaterThan);
          }

          return pow(error,1);
      }

      double totalErrorFunctionGreaterThan(double greaterThanNumber, double * valuesArray, int &numberOfErrors) { if (debug_THDM) cout << "DBG " << endl;
      	double error;
      	int ArraySize = valuesArray[0];
      	double result = 0;

      	for(int j=1; j<=ArraySize; j++)
      	{ if (debug_THDM) cout << "DBG 20" << endl;
      		if(valuesArray[j]>=greaterThanNumber)
      			result += 0; //result is unchanged
      		else
      		{ if (debug_THDM) cout << "DBG 21" << endl;
      			error = abs(valuesArray[j])-greaterThanNumber;
      			result += pow(error,1);
            numberOfErrors++;
      		}
      	}
        return result;
      }

      double totalErrorFunctionLessThan(double lessThanNumber, double * valuesArray, int &numberOfErrors) { if (debug_THDM) cout << "DBG " << endl;
        double error;
        int ArraySize = valuesArray[0];
        double result = 0;

        for(int j=1; j<=ArraySize; j++)
        { if (debug_THDM) cout << "DBG 22" << endl;
          if(abs(valuesArray[j])<=lessThanNumber)
            result += 0; //result is unchanged
          else
          { if (debug_THDM) cout << "DBG 23" << endl;
            error = abs(valuesArray[j])-lessThanNumber;
            result += pow(error,1);
            numberOfErrors++;
          }

        }
        return result;
      }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //one loop level beta functions for the lambda couplings

            double betaOne(std::vector<double> Lambda)
            { if (debug_THDM) cout << "DBG 24" << endl;
              double beta = 12*pow(Lambda[1],2) + 4*pow(Lambda[3],2) + 4*Lambda[3]*Lambda[4] + 2*pow(Lambda[4],2) + 2*pow(Lambda[5],2);
              return 1/(16*pow(PI,2))*beta;
            }

            double betaTwo(std::vector<double> Lambda)
            { if (debug_THDM) cout << "DBG 25" << endl;
              double beta = 12*pow(Lambda[2],2)+4*pow(Lambda[3],2)+4*Lambda[3]*Lambda[4]+2*pow(Lambda[4],2)+2*pow(Lambda[5],2);
              return 1/(16*pow(PI,2))*beta;
            }

            double betaThree(std::vector<double> Lambda)
            { if (debug_THDM) cout << "DBG 26" << endl;
              double beta = 4*pow(Lambda[3],2) +2*pow(Lambda[4],2) + (Lambda[1]+Lambda[2])*(6*Lambda[3]+2*Lambda[4]) + 2*pow(Lambda[5],2);
              return 1/(16*pow(PI,2))*beta;
            }

            double betaFour(std::vector<double> Lambda)
            { if (debug_THDM) cout << "DBG 27" << endl;
              double beta = (2*Lambda[1] + 2*Lambda[2] + 8*Lambda[3])*Lambda[4] + pow(Lambda[4],2) + 8*pow(Lambda[5],2);
              return 1/(16*pow(PI,2))*beta;
            }

            double betaFive(std::vector<double> Lambda)
            { if (debug_THDM) cout << "DBG 28" << endl;
              double beta = (2*Lambda[1] + 2*Lambda[2] + 8*Lambda[3] + 12*Lambda[4])*Lambda[5];
              return 1/(16*pow(PI,2))*beta;
            }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////GAMBIT FUNCTIONS////////////////////////////////////////////////////////////////////////////////

      void get_unitarity_constraint_likelihood_THDM(double& result)
      { if (debug_THDM) cout << "DBG 29" << endl;
        using namespace Pipes::get_unitarity_constraint_likelihood_THDM;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        //const Spectrum* spec = fullspectrum;

        if (debug_THDM) cout << "DBG 29A" << endl;

        THDMC_1_7_0::THDM thdmObject;
        THDMC_1_7_0::SM smObject = thdmObject.get_SM();

        if (debug_THDM) cout << "DBG 29AA" << endl;

        int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");

        if (debug_THDM) cout << "DBG 29B" << endl;

        // fill the THDM object with values from the input file
        fill_THDM_object(thdmObject,smObject,fullspectrum, YukawaType);

        //arrays to hold condtion values
        double unitarityConditions[13];

        //get arrays of values that need to each satisfy the conditions
        thdmObject.get_unitarity_conditions(unitarityConditions);

        //set constraint values
        //-----------------------------
        // all values < 16*PI for unitarity conditions
        double unitarityUpperLimit = 8*M_PI;
        int numberErrors = 0;
        //-----------------------------

        //calculate the total error of each point
        // for example the total error for points x_i with upper limit U (x_i no larger than U)
        // totalError = sum_over_i ( |U - x_i| )
        double unitarityError = totalErrorFunctionLessThan(unitarityUpperLimit, unitarityConditions, numberErrors);

        double sigmaUnitary = 1;

        if (numberErrors != 0) { if (debug_THDM) cout << "DBG 30" << endl; sigmaUnitary = numberErrors*sigmaUnitary; }

        // loglike function
        double loglike = -unitarityError/(pow(sigmaUnitary,2));

        result = loglike;
      }

      void get_NLO_unitarity_constraint_likelihood_THDM(double& result)
      { if (debug_THDM) cout << "DBG 31" << endl;

        using namespace Pipes::get_NLO_unitarity_constraint_likelihood_THDM;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        unique_ptr<SubSpectrum> spec = fullspectrum.clone_HE();

        if (debug_THDM) cout << "DBG 31A" << endl;
        double runToScale = *Param.at("QrunTo");

        if (debug_THDM) cout << "DBG 31B" << endl;
        spec -> RunToScale(runToScale);

        if (debug_THDM) cout << "DBG 31C" << endl;
        double lambda1 = spec->get(Par::mass1, "lambda_1");
        double lambda2 = spec->get(Par::mass1, "lambda_2");
        double lambda3 = spec->get(Par::mass1, "lambda_3");
        double lambda4 = spec->get(Par::mass1, "lambda_4");
        double lambda5 = spec->get(Par::mass1, "lambda_5");
        double lambda6 = spec->get(Par::mass1, "lambda_6");
        double lambda7 = spec->get(Par::mass1, "lambda_7");

        std::vector<double> Lambda(6);
        Lambda[0] = 0.0;
        Lambda[1] = lambda1;
        Lambda[2] = lambda2;
        Lambda[3] = lambda3;
        Lambda[4] = lambda4;
        Lambda[5] = lambda5;

        const complex<double> i(0.0,1.0);

        std::complex<double> B1 = -3*lambda1 + (9/2)*betaOne(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(9*pow(lambda1,2)+pow((2*lambda3+lambda4),2));

        // std::complex<double> B1_2 = -3*lambda1 + (9/2)*betaOne(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(9*pow(lambda1,2)+pow((2*lambda3+lambda4),2));

        std::complex<double> B2 = -3*lambda2 + (9/2)*betaTwo(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(9*pow(lambda2,2) + pow((2*lambda3+lambda4),2));

        // std::complex<double> B2_2 = -3*lambda2 + (9/2)*betaTwo(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(9*pow(lambda2,2)+pow((2*lambda3+lambda4),2));

        std::complex<double> B3 = - (2*lambda3+lambda4) + (3/2)*(2*betaThree(Lambda)+betaFour(Lambda)) + 3/(16*pow(PI,2))*(i*PI-1)*(lambda1+lambda2)*(2*lambda3+lambda4);

        // std::complex<double> B3_2 = -(2*lambda3+lambda4) + (3/2)*(2*betaThree(Lambda)+betaFour(Lambda)) + (3/(16*pow(PI,2)))*(i*PI-1)*(lambda1+lambda2)*(2*lambda3+lambda4);

        std::complex<double> B4 = - (lambda3 + 2*lambda4) + (3/2)*(betaThree(Lambda) + 2*betaFour(Lambda)) + (1/(16*pow(PI,2)))*(i*PI-1)*(pow(lambda3,2) + 4*lambda3*lambda4 + 4*pow(lambda4,2) + 9*pow(lambda5,2));

        // std::complex<double> B4_2 = - (lambda3 + 2*lambda4) + (3/2)*(betaThree(Lambda) + 2*betaFour(Lambda)) + (1/(16*pow(PI,2)))*(i*PI - 1)*(pow(lambda3,2) + 4*lambda3*lambda4 + 4*pow(lambda4,2) + 9*pow(lambda5,2));

        std::complex<double> B6 = -3*lambda5 + (9/2)*betaFive(Lambda) + (6/(16*pow(PI,2)))*(i*PI-1)*(lambda3 + 2*lambda4)*lambda5;

        // std::complex<double> B6_2 = -3*lambda5 + (9/2)*betaFive(Lambda) + (6/(16*pow(PI,2)))*(i*PI-1)*(lambda3 + 2*lambda4)*lambda5;

        std::complex<double> B7 = -lambda1 + (3/2)*betaOne(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(pow(lambda1,2)+pow(lambda4,2));

        // std::complex<double> B7_2 = -lambda1 + (3/2)*betaOne(Lambda) + (1/(16*pow(PI,2)))*(i*PI-1)*(pow(lambda1,2) + pow(lambda4,2));

        std::complex<double> B8 = -lambda2 + (3/2)*betaTwo(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(pow(lambda2,2)+pow(lambda4,2)); //copied from B7

        // std::complex<double> B8_2 = -lambda2 + (3/2)*betaTwo(Lambda) + (1/(16*pow(PI,2)))*(i*PI-1)*(pow(lambda2,2) + pow(lambda4,2)); //copied from B7

        std::complex<double> B9 = -lambda4 + (3/2)*betaFour(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(lambda1 + lambda2)*lambda4; //copied from B7

        // std::complex<double> B9_2 = -lambda4 + (3/2)*betaFour(Lambda) + (1/(16*pow(PI,2)))*(i*PI-1)*(lambda1 + lambda2)*lambda4; //copied from B7

        std::complex<double> B13 = -lambda3 + (3/2)*betaThree(Lambda) + (1/(16*pow(PI,2)))*(i*PI-1)*(pow(lambda3,2)+pow(lambda5,2));

        // std::complex<double> B13_2= -lambda3 + (3/2)*betaThree(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(pow(lambda3,2)+pow(lambda5,2)); //copied from B7

        std::complex<double> B15 = -lambda5 + (3/2)*betaFive(Lambda) + (2/(16*pow(PI,2)))*(i*PI-1)*lambda3*lambda5;

        // std::complex<double> B15_2 = -lambda5 + (3/2)*betaFive(Lambda) + (2/(16*pow(PI,2)))*(i*PI-1)*lambda3*lambda5;

        std::complex<double> B19 = -(lambda3-lambda4) + (3/2)*(betaThree(Lambda) - betaFour(Lambda)) + (1/(16*pow(PI,2)))*(i*PI-1)*pow((lambda3-lambda4),2);

        // std::complex<double> B19_2 = -(lambda3-lambda4) + (3/2)*(betaThree(Lambda) - betaFour(Lambda)) + (1/(16*pow(PI,2)))*(i*PI-1)*pow((lambda3-lambda4),2);

        std::complex<double> B20 = -lambda1 + (3/2)*betaOne(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(pow(lambda1,2) + pow(lambda5,2));

        // std::complex<double> B20_2 = -lambda1 + (3/2)*betaOne(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(pow(lambda1,2) + pow(lambda5,2));

        std::complex<double> B21 = -lambda2 + (3/2)*betaTwo(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(pow(lambda2,2) + pow(lambda5,2));

        // std::complex<double> B21_2 = -lambda2 + (3/2)*betaTwo(Lambda) + 1/(16*pow(PI,2))*(i*PI-1)*(pow(lambda2,2) + pow(lambda5,2));

        std::complex<double> B22 = -lambda5 + (3/2)*betaFive(Lambda) + (1/(16*pow(PI,2)))*(i*PI-1)*(lambda1 + lambda2)*lambda5;

        // std::complex<double> B22_2 = -lambda5 + (3/2)*betaFive(Lambda) + (1/(16*pow(PI,2)))*(i*PI-1)*(lambda1 + lambda2)*lambda5;

        std::complex<double> B30 = -(lambda3+lambda4) + (3/2)*(betaThree(Lambda)+betaFour(Lambda)) + (1/(16*pow(PI,2)))*(i*PI-1)*pow((lambda3+lambda4),2);

        // std::complex<double> B30_2 = -(lambda3+lambda4) + (3/2)*(betaThree(Lambda) + betaFour(Lambda)) + (1/(16*pow(PI,2)))*(i*PI-1)*pow((lambda3+lambda4),2);

        // eigenvalues

        std::complex<double> a00_even_plus = 1/(32*PI) * ((B1 + B2) + sqrt(pow((B1-B2),2) + 4*pow(B3,2)));
        std::complex<double> a00_even_minus = 1/(32*PI) * ((B1 + B2) - sqrt(pow((B1-B2),2) + 4*pow(B3,2)));

        // std::complex<double> a00_even_plus_2 = 1/(32*PI) * ((B1_2 + B2_2) + sqrt(pow((B1_2-B2_2),2) + 4*pow(B3_2,2)));
        // std::complex<double> a00_even_minus_2 = 1/(32*PI) * ((B1_2 + B2_2) - sqrt(pow((B1_2-B2_2),2) + 4*pow(B3_2,2)));

        std::complex<double> a00_odd_plus = 1/(32*PI) * (2*B4 + 2*B6);
        std::complex<double> a00_odd_minus = 1/(32*PI) * (2*B4 - 2*B6);

        // std::complex<double> a00_odd_plus_2 = 1/(32*PI) * (2*B4_2 + 2*B6_2);
        // std::complex<double> a00_odd_minus_2 = 1/(32*PI) * (2*B4_2 - 2*B6_2);

        std::complex<double> a01_even_plus = 1/(32*PI) * (B7 * B8 + sqrt(pow((B7-B8),2) + 4*pow(B9,2)));
        std::complex<double> a01_even_minus = 1/(32*PI) * (B7 * B8 - sqrt(pow((B7-B8),2) + 4*pow(B9,2)));

        // std::complex<double> a01_even_plus_2 = 1/(32*PI) * (B7_2 * B8_2 + sqrt(pow((B7_2-B8_2),2) + 4*pow(B9_2,2)));
        // std::complex<double> a01_even_minus_2 = 1/(32*PI) * (B7_2 * B8_2 - sqrt(pow((B7_2-B8_2),2) + 4*pow(B9_2,2)));

        std::complex<double> a01_odd_plus = 1/(32*PI) * (2*B13 + 2*B15);
        std::complex<double> a01_odd_minus = 1/(32*PI) * (2*B13 - 2*B15);

        // std::complex<double> a01_odd_plus_2 = 1/(32*PI) * (2*B13_2 + 2*B15_2);
        // std::complex<double> a01_odd_minus_2 = 1/(32*PI) * (2*B13_2 - 2*B15_2);

        std::complex<double> a10_odd = 1/(32*PI) * (2*B19);

        // std::complex<double> a10_odd_2 = 1/(32*PI) * (2*B19_2);

        std::complex<double> a11_even_plus = 1/(32*PI) * (B20 + B21 + sqrt(pow((B20-B21),2) + 4*pow(B22,2)) );
        std::complex<double> a11_even_minus = 1/(32*PI) * (B20 + B21 - sqrt(pow((B20-B21),2) + 4*pow(B22,2)) );

        // std::complex<double> a11_even_plus_2 = 1/(32*PI) * (B20_2 + B21_2 + sqrt(pow((B20_2-B21_2),2) + 4*pow(B22_2,2)) );
        // std::complex<double> a11_even_minus_2 = 1/(32*PI) * (B20_2 + B21_2 - sqrt(pow((B20_2-B21_2),2) + 4*pow(B22_2,2)) );

        std::complex<double> a11_odd = 1/(32*PI) * (2*B30);

        // std::complex<double> a11_odd_2 = 1/(32*PI) * (2*B30_2);

        //arrays to hold condtion values
        double unitarityConditions[13];
        unitarityConditions[0] = 12;

        unitarityConditions[1] = abs(a00_even_plus-i/2);
        unitarityConditions[2] = abs(a00_even_minus-i/2);
        unitarityConditions[3] = abs(a00_odd_plus-i/2);
        unitarityConditions[4] = abs(a00_odd_minus-i/2);
        unitarityConditions[5] = abs(a01_even_plus-i/2);
        unitarityConditions[6] = abs(a01_even_minus-i/2);
        unitarityConditions[7] = abs(a01_odd_plus-i/2);
        unitarityConditions[8] = abs(a01_odd_minus-i/2);
        unitarityConditions[9] = abs(a10_odd-i/2);
        unitarityConditions[10] = abs(a11_even_plus-i/2);
        unitarityConditions[11] = abs(a11_even_minus-i/2);
        unitarityConditions[12] = abs(a11_odd-i/2);

        //set constraint values
        //-----------------------------
        // all values < 1/2 for NLO unitarity conditions
        double unitarityUpperLimit = 1/2;
        int numberErrors = 0;
        //-----------------------------

        //calculate the total error of each point
        // for example the total error for points x_i with upper limit U (x_i no larger than U)
        // totalError = sum_over_i ( |U - x_i| )
        double unitarityError = totalErrorFunctionLessThan(unitarityUpperLimit, unitarityConditions, numberErrors);

        double sigmaUnitary = 1;

        if (numberErrors != 0) { if (debug_THDM) cout << "DBG 33" << endl; sigmaUnitary = numberErrors*sigmaUnitary; }

        // loglike function
        double loglike = -unitarityError/(pow(sigmaUnitary,2));

        result = loglike;

      }

      double get_perturbativity(Spectrum& spec, int YukawaType, double QrunTo)
      { if (debug_THDM) cout << "DBG 34" << endl;
        THDMC_1_7_0::THDM thdmObject;
        THDMC_1_7_0::SM smObject;

        // fill the THDM object with values from the input file
        if(QrunTo!=0)
        { if (debug_THDM) cout << "DBG 35" << endl;
            fill_THDM_object_AtScale(thdmObject,smObject,spec, YukawaType, QrunTo);
        }
        else
        { if (debug_THDM) cout << "DBG 36" << endl;
            fill_THDM_object(thdmObject,smObject,spec, YukawaType);
        }

        //arrays to hold condtion values
        double perturbativityConditions[257];

        //get arrays of values that need to each satisfy the conditions
        thdmObject.get_perturbativity_conditions(perturbativityConditions);

        //set constraint values
        //-----------------------------
        // all values < 4*PI for perturbativity conditions
        double perturbativityUpperLimit = 4*M_PI;
        int numberErrors = 0;
        //-----------------------------

        //calculate the total error of each point
        // for example the total error for points x_i with upper limit U (x_i no larger than U)
        // totalError = sum_over_i ( |U - x_i| )
      	double perturbativityError = totalErrorFunctionLessThan(perturbativityUpperLimit, perturbativityConditions, numberErrors);

        double sigmaPert = 1;

        if (numberErrors != 0) { if (debug_THDM) cout << "DBG 37" << endl; sigmaPert = numberErrors*sigmaPert; }

        // loglike function
        double loglike = -perturbativityError/(pow(sigmaPert,2));

        return loglike;
      }

      void get_perturbativity_constraint_likelihood_THDM(double& result)
      { if (debug_THDM) cout << "DBG 38" << endl;
        using namespace Pipes::get_perturbativity_constraint_likelihood_THDM;
        Spectrum fullspectrum = *Dep::THDM_spectrum;
        int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");
        bool atScale = runOptions->getValueOrDef<bool>(false, "atQrunToScale");
        double scale = 0;
          if (atScale)
          { if (debug_THDM) cout << "DBG 39" << endl;
              double scale = *Param.at("QrunTo");
          }
        result = get_perturbativity(fullspectrum, YukawaType, scale);
      }

      double get_stability_likelihood_THDM(Spectrum& spec, int YukawaType, double QrunTo)
      { if (debug_THDM) cout << "DBG 40" << endl;

        THDMC_1_7_0::THDM thdmObject;
        THDMC_1_7_0::SM smObject;

        // stability constrainst between mZ (91.2 GeV) & 750 GeV

        // fill the THDM object with values from the input file
        fill_THDM_object(thdmObject,smObject,spec, YukawaType);

        //arrays to hold condtion values
        double stabilityConditions[5];

        //get arrays of values that need to each satisfy the conditions
        thdmObject.get_stability_conditions(stabilityConditions);

        //set constraint values
        //-----------------------------
        // all values > 0 for stability conditions
        double stabilityLowerLimit = 0;
        int numberErrors = 0;
        //-----------------------------

        //calculate the total error of each point
        // for example the total error for points x_i with upper limit U (x_i no larger than U)
        // totalError = sum_over_i ( |U - x_i| )
      	double stabilityError = totalErrorFunctionGreaterThan(stabilityLowerLimit, stabilityConditions, numberErrors);

         //error at the moment
         if(QrunTo!=0)
         { if (debug_THDM) cout << "DBG 41" << endl;
           // fill for 750 GeV
           fill_THDM_object_AtScale(thdmObject,smObject,spec, YukawaType, QrunTo);
           thdmObject.get_stability_conditions(stabilityConditions);
           double stabilityErrorRunTo = totalErrorFunctionGreaterThan(stabilityLowerLimit, stabilityConditions, numberErrors);

           // select the largest of the two errors
           if (stabilityErrorRunTo > stabilityError)
           { if (debug_THDM) cout << "DBG 42" << endl;
             stabilityError = stabilityErrorRunTo;
           }
         }

        double sigmaStability = 1;

        if (numberErrors != 0) { if (debug_THDM) cout << "DBG 43" << endl; sigmaStability = numberErrors*sigmaStability; }

        // loglike function
        double loglike = -stabilityError/(pow(sigmaStability,2));

        return loglike;
      }

      void get_stability_likelihood_THDM(double& result)
      { if (debug_THDM) cout << "DBG 44" << endl;
        using namespace Pipes::get_stability_likelihood_THDM;
        Spectrum fullspectrum = *Dep::THDM_spectrum;
        int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");
        bool atScale = runOptions->getValueOrDef<bool>(false, "betweenQinAndQrunTo");
        double scale = 0;
        if (atScale)
        { if (debug_THDM) cout << "DBG 45" << endl;
            double scale = *Param.at("QrunTo");
        }
        result = get_stability_likelihood_THDM(fullspectrum ,YukawaType, scale);

      }

      void get_alignment_limit_likelihood_THDM(double& result)
      { if (debug_THDM) cout << "DBG 46" << endl;
        using namespace Pipes::get_alignment_limit_likelihood_THDM;

        if (debug_THDM) cout << "DBG 46B" << endl;
        Spectrum fullspectrum = *Dep::THDM_spectrum;

        if (debug_THDM) cout << "DBG 46C" << endl;
        SubSpectrum& he = fullspectrum.get_HE();

        if (debug_THDM) cout << "DBG 46D" << endl;
        double tan_beta = he.get(Par::dimensionless,"tanb");
        double alpha = he.get(Par::dimensionless,"alpha");

        cout << tan_beta << endl;
        cout << alpha << endl;

        double sba = get_sba(tan_beta, alpha);

        // sin(b-a) = 1 in alignment limit -distance from alignment limit:
        double sbaTol = 0.01;
        //-----------------------------

      	double sbaError = errorFunctionLessThan(sbaTol, 1-sba);

        double sigmaSba = 1.;

        // loglike function
        double loglike = -sbaError/(pow(sigmaSba,2));

        cout << "YIKES" << endl;

        result = loglike;
      }


      void get_oblique_parameters_likelihood_THDM(double& result)
      { if (debug_THDM) cout << "DBG 47" << endl;

        using namespace Pipes::get_oblique_parameters_likelihood_THDM;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        THDMC_1_7_0::THDM thdmObject;
        THDMC_1_7_0::SM smObject;

        int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");

        // fill the THDM object with values from the input file
        fill_THDM_object(thdmObject,smObject,fullspectrum, YukawaType);

        THDMC_1_7_0::Constraints constraintsObject(thdmObject);

        SubSpectrum& he = fullspectrum.get_HE();

        double mh = he.get(Par::Pole_Mass,"h0",1);
        double S;
        double T;
        double U;
        double V;
        double W;
        double X;

        constraintsObject.oblique_param(mh, S, T, U, V, W, X);

        double loglike = 0.0;

        // loglike +=  Stats::gaussian_loglikelihood_marginalised(S,0.014,0.0,0.10);

        loglike +=  Stats::gaussian_loglikelihood(S,0.014,0.0,0.10, true);
        loglike +=  Stats::gaussian_loglikelihood(T,0.03,0.0,0.11, true);
        loglike +=  Stats::gaussian_loglikelihood(U,0.06,0.0,0.10,true); // 0.2
        loglike +=  Stats::gaussian_loglikelihood(V,0.30,0.0,0.38, true); // 0.3
        loglike +=  Stats::gaussian_loglikelihood(W,0.11,0.0,4.7, true);
        loglike +=  Stats::gaussian_loglikelihood(X,0.38,0.0,0.59, true); // 0.2

        // std::cout<< "### oblique params errors (S,T,U,V,W,X): " << Stats::gaussian_loglikelihood(S,0.014,0.0,0.10) << ", " << Stats::gaussian_loglikelihood(T,0.03,0.0,0.11)
        //     << ", " << Stats::gaussian_loglikelihood(U,0.06,0.0,0.10)  <<", " <<  Stats::gaussian_loglikelihood(V,0.30,0.0,0.38)
        //      <<", " <<  Stats::gaussian_loglikelihood(W,0.11,0.0,4.7) <<", " << Stats::gaussian_loglikelihood(X,0.38,0.0,0.59) << std::endl;

        result = loglike;
      }

      template <class T>
      void fill_THDM_Couplings(thdmc_couplings &result, T& thdmObject)
      { if (debug_THDM) cout << "DBG 48" << endl;

        thdmc_couplings Couplings;

        complex<double> cs;
        complex<double> cp;
        complex<double> c;

        for (int h=1; h<5; h++)
        { if (debug_THDM) cout << "DBG 49" << endl;
          for (int f1=1; f1<4; f1++)
          { if (debug_THDM) cout << "DBG 50" << endl;
            for (int f2=1; f2<4; f2++)
            { if (debug_THDM) cout << "DBG 51" << endl;
              thdmObject.get_coupling_hdd(h,f1,f2,cs,cp);
              Couplings.hdd_cs[h][f1][f2] = cs;
              Couplings.hdd_cp[h][f1][f2] = cp;

              thdmObject.get_coupling_huu(h,f1,f2,cs,cp);
              Couplings.huu_cs[h][f1][f2] = cs;
              Couplings.huu_cp[h][f1][f2] = cp;

              thdmObject.get_coupling_hll(h,f1,f2,cs,cp);
              Couplings.hll_cs[h][f1][f2] = cs;
              Couplings.hll_cp[h][f1][f2] = cp;

              thdmObject.get_coupling_hdu(h,f1,f2,cs,cp);
              Couplings.hdu_cs[h][f1][f2] = cs;
              Couplings.hdu_cp[h][f1][f2] = cp;

              thdmObject.get_coupling_hln(h,f1,f2,cs,cp);
              Couplings.hln_cs[h][f1][f2] = cs;
              Couplings.hln_cp[h][f1][f2] = cp;
            }
          }

          for (int v1=1; v1<4; v1++)
          { if (debug_THDM) cout << "DBG 52" << endl;

            for (int v2=1; v2<4; v2++)
            { if (debug_THDM) cout << "DBG 53" << endl;
              thdmObject.get_coupling_vvh(v1,v2,h,c);
              Couplings.vvh[v1][v2][h] = c;

                for (int h2=1; h2<5; h2++)
                { if (debug_THDM) cout << "DBG 54" << endl;
                  thdmObject.get_coupling_vvhh(v1,v2,h,h2,c);
                  Couplings.vvhh[v1][v2][h][h2] = c;
                }
            }

            for (int h2=1; h2<5; h2++)
            { if (debug_THDM) cout << "DBG 55" << endl;
              thdmObject.get_coupling_vhh(v1,h,h2,c);
              Couplings.vhh[v1][h][h2] = c;

            }
          }

          for (int h2=1; h2<5; h2++)
          { if (debug_THDM) cout << "DBG 56" << endl;
            for (int h3=1; h3<5; h3++)
            { if (debug_THDM) cout << "DBG 57" << endl;
              thdmObject.get_coupling_hhh(h,h2,h3,c);
              Couplings.hhh[h][h2][h3] = c;

              for (int h4=1; h4<5; h4++)
              { if (debug_THDM) cout << "DBG 58" << endl;
                thdmObject.get_coupling_hhhh(h,h2,h3,h4,c);
                Couplings.hhhh[h][h2][h3][h4] = c;
              }

            }
          }

        }

        result = Couplings;
      }

      void get_global_minimum_discriminant_likelihood(double& result)
      { if (debug_THDM) cout << "DBG 59" << endl;

        // -----------
        //from arXiv 1303.5098v1
        //"Our vacuum is the global minimum of the potential if and only if D > 0
        //Therefore, if we only wish to make certain that we are in the global
        //minimum of the potential, regardless of the number of those minima,
        //requiring D > 0 is a necessary and sufficient condition."
        // -----------

        using namespace Pipes::get_global_minimum_discriminant_likelihood;

        Spectrum fullspectrum = *Dep::THDM_spectrum;
        const SMInputs& sminputs   = fullspectrum.get_SMInputs();

        unique_ptr<SubSpectrum> spec = fullspectrum.clone_HE();

        double runToScale = *Param.at("QrunTo");

        spec -> RunToScale(runToScale);

        double lambda1 = spec->get(Par::mass1, "lambda_1");
        double lambda2 = spec->get(Par::mass1, "lambda_2");
        double lambda3 = spec->get(Par::mass1, "lambda_3");
        double lambda4 = spec->get(Par::mass1, "lambda_4");
        double lambda5 = spec->get(Par::mass1, "lambda_5");
        double lambda6 = spec->get(Par::mass1, "lambda_6");
        double lambda7 = spec->get(Par::mass1, "lambda_7");
        double alpha = spec->get(Par::dimensionless, "alpha");
        double tb = spec->get(Par::dimensionless, "tanb");
        double m12_2 = spec->get(Par::mass1, "m12_2");

        double sba = get_sba(tb, alpha);

        // set up required quantities
        double beta = atan(tb);
        double ctb = 1./tb;
        double cb  = 1./sqrt(1.+tb*tb);
        double sb  = tb*cb;
        double sb2 = sb*sb;
        double cb2 = cb*cb;

//        double alpha = -asin(sba)+beta;
        double sa  = sin(alpha);
        double sa2 = sa*sa;
        double ca  = cos(alpha);
        double ca2 = ca*ca;

        double cba = sqrt(1.-sba*sba);

        double v2= pow (1. / sqrt(sqrt(2.)*sminputs.GF),2);

        //minimization conditions to recover m11^2 and m22^2
        double m11_2 = m12_2*tb - 1/(2*v2)*(lambda1*cb2 + (lambda3+lambda4+lambda5)*sb2 + 3*lambda6*sb*cb + lambda7*sb2*tb);
        double m22_2 = m12_2*ctb - 1/(2*v2)*(lambda2*sb2 + (lambda3+lambda4+lambda5)*cb2 + lambda6*cb2*ctb + 3*lambda7*sb*cb);

        complex<double> lambda1_i = lambda1;
        complex<double> lambda2_i = lambda2;

        complex<double> k = pow((lambda1_i/lambda2_i),0.25);

        // the 'dicriminant', if this value is greater than zero then we have only one vacuum and it is global
        complex<double> discriminant = m12_2*(m11_2 - pow(k,2)*m22_2)*(tb-k);

        complex<double> zero = 0;

        // find the error in the discriminant
        double error = errorFunctionComplexGreaterThan(zero,discriminant);

        double sigmaDiscriminant = 1.;

        // calculate loglike function
        double loglike = -error/(pow(sigmaDiscriminant,2));

        result = loglike;

      }


      template <class T>
      void fill_THDM_Couplings_For_HB(thdmc_couplings &result, T& thdmObject)
      { if (debug_THDM) cout << "DBG 60" << endl;
        // method to fill only those couplings required by HiggsBounds
        // using this method will save computational time vs full fill_THDM_Couplings function

        thdmc_couplings Couplings;

        complex<double> cs;
        complex<double> cp;
        complex<double> c;

        for (int h=1; h<5; h++)
        { if (debug_THDM) cout << "DBG 61" << endl;

          thdmObject.get_coupling_hdd(h,3,3,cs,cp);
          Couplings.hdd_cs[h][3][3] = cs;
          Couplings.hdd_cp[h][3][3] = cp;

          thdmObject.get_coupling_huu(h,3,3,cs,cp);
          Couplings.huu_cs[h][3][3] = cs;
          Couplings.huu_cp[h][3][3] = cp;


          thdmObject.get_coupling_vvh(2,2,h,c);
          Couplings.vvh[2][2][h] = c;

          thdmObject.get_coupling_vvh(3,3,h,c);
          Couplings.vvh[3][3][h] = c;


            for (int h2=1; h2<5; h2++)
            { if (debug_THDM) cout << "DBG 62" << endl;
              thdmObject.get_coupling_vhh(2,h,h2,c);
              Couplings.vhh[2][h][h2] = c;

            }
          }


        result = Couplings;
      }

      template <class T>
      void fill_THDM_Couplings_For_HB_SMLikeComponent(thdmc_couplings &result, T& thdmObject)
      { if (debug_THDM) cout << "DBG 63" << endl;
        // function to fill only those couplings required by HiggsBounds
        // and only those required for setup of the SM Like component of input.
        // Using this method will save computational time vs fill_THDM_Couplings
        // or fill_THDM_Couplings_For_HB functions.

        thdmc_couplings Couplings;

        complex<double> cs;
        complex<double> cp;

        thdmObject.get_coupling_hdd(1,3,3,cs,cp);
        Couplings.hdd_cs[1][3][3] = cs;
        Couplings.hdd_cp[1][3][3] = cp;

        result = Couplings;
      }

      void THDM_Couplings(thdmc_couplings &result)
      { if (debug_THDM) cout << "DBG 64" << endl;
        using namespace Pipes::THDM_Couplings;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        THDMC_1_7_0::THDM thdmObject;
        THDMC_1_7_0::SM smObject;

        int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");

        // fill the THDM object with values from the input file
        fill_THDM_object(thdmObject,smObject,fullspectrum, YukawaType);

        fill_THDM_Couplings(result,thdmObject);
      }

      void THDM_Couplings_For_HB(thdmc_couplings &result)
      { if (debug_THDM) cout << "DBG 65" << endl;
        using namespace Pipes::THDM_Couplings_For_HB;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        THDMC_1_7_0::THDM thdmObject;
        THDMC_1_7_0::SM smObject;

        int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");

        // fill the THDM object with values from the input file
        fill_THDM_object(thdmObject,smObject,fullspectrum, YukawaType);

        fill_THDM_Couplings_For_HB(result,thdmObject);
      }

      void THDM_Couplings_SM_Like_Model_h01(thdmc_couplings &result)
      { if (debug_THDM) cout << "DBG 66" << endl;
        using namespace Pipes::THDM_Couplings_SM_Like_Model_h01;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        THDMC_1_7_0::THDM thdmObject;
        THDMC_1_7_0::SM smObject;

        int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");

        // fill the THDM object with values from a SM like set of values
        fill_THDM_object_SM_Like_Model(thdmObject,smObject,fullspectrum,1,YukawaType);

        fill_THDM_Couplings_For_HB_SMLikeComponent(result,thdmObject);
      }

      void THDM_Couplings_SM_Like_Model_h02(thdmc_couplings &result)
      { if (debug_THDM) cout << "DBG 67" << endl;
        using namespace Pipes::THDM_Couplings_SM_Like_Model_h02;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        THDMC_1_7_0::THDM thdmObject;
        THDMC_1_7_0::SM smObject;

        int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");

        // fill the THDM object with values from a SM like set of values
        fill_THDM_object_SM_Like_Model(thdmObject,smObject,fullspectrum,2,YukawaType);

        fill_THDM_Couplings_For_HB_SMLikeComponent(result,thdmObject);
      }

      void THDM_Couplings_SM_Like_Model_A0(thdmc_couplings &result)
      { if (debug_THDM) cout << "DBG 68" << endl;
        using namespace Pipes::THDM_Couplings_SM_Like_Model_A0;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        THDMC_1_7_0::THDM thdmObject;
        THDMC_1_7_0::SM smObject;

        int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");

        // fill the THDM object with values from a SM like set of values
        fill_THDM_object_SM_Like_Model(thdmObject,smObject,fullspectrum,3,YukawaType);

        fill_THDM_Couplings_For_HB_SMLikeComponent(result,thdmObject);
      }

      void fill_THDM_SLHA(SLHAstruct &result)
      { if (debug_THDM) cout << "DBG 69" << endl;
        using namespace Pipes::fill_THDM_SLHA;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        THDMC_1_7_0::THDM thdmObject;
        THDMC_1_7_0::SM smObject;

        int YukawaType = runOptions->getValueOrDef<int>(1, "YukawaType");

        // fill the THDM object with values from the input file
        fill_THDM_object(thdmObject,smObject,fullspectrum,YukawaType);

        const SubSpectrum& he = fullspectrum.get_HE();
        const SubSpectrum& SM = fullspectrum.get_LE();
        const SMInputs& sminputs   = fullspectrum.get_SMInputs();

        double m_h = he.get(Par::Pole_Mass, "h0",1);
        double m_H = he.get(Par::Pole_Mass, "h0",2);
        double m_A = he.get(Par::Pole_Mass, "A0");
        double m_Hp = he.get(Par::Pole_Mass, "H+");
        double alpha = he.get(Par::dimensionless, "alpha");
        double tan_beta = he.get(Par::dimensionless, "tanb");

        double sba = get_sba(tan_beta, alpha);

        double lambda6 = he.get(Par::mass1,"lambda_6");
        double lambda7 = he.get(Par::mass1,"lambda_7");

        double m12_2 = he.get(Par::mass1,"m12_2");

        double alphaInv = sminputs.alphainv;
        double alphaS = sminputs.alphaS;
        double GF = sminputs.GF;

        double MZ = SM.get(Par::Pole_Mass,"Z0");
        double MW = SM.get(Par::Pole_Mass,"W+");

        double gammaZ = 2.4952;
        double gammaW = 2.085;

        double Me = SM.get(Par::Pole_Mass,"e-_1");
        double Mmu = SM.get(Par::Pole_Mass,"e-_2");
        double Mtau = SM.get(Par::Pole_Mass,"e-_3");

        double Mu = sminputs.mU; //u
        double Md = sminputs.mD; //d
        double Mc = sminputs.mCmC; //c
        double Ms = sminputs.mS; //s
        double Mt = SM.get(Par::Pole_Mass,"u_3"); //t
        double Mb = SM.get(Par::Pole_Mass,"d_3"); //b

        double lambda = sminputs.CKM.lambda;
        double A = sminputs.CKM.A;
        double rho = sminputs.CKM.rhobar;
        double eta = sminputs.CKM.etabar;

        double g_prime = smObject.get_gprime();
        double g = smObject.get_g();
        double g_3 = 4.*M_PI*alphaS;

        double lambda1, lambda2, lambda3, lambda4, lambda5;

        thdmObject.get_param_gen(lambda1,lambda2,lambda3,lambda4,lambda5,lambda6,lambda7,m12_2,tan_beta);

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
        SLHAea_add(slha, "MINPAR", 24, YukawaType, "yukawa type", true);

        SLHAea_add_block(slha, "VCKMIN");
        SLHAea_add(slha, "VCKMIN", 1, lambda, "lambda-CKM", true);
        SLHAea_add(slha, "VCKMIN", 2, A, "A-CKM", true);
        SLHAea_add(slha, "VCKMIN", 3, rho, "rhobar-CKM", true);
        SLHAea_add(slha, "VCKMIN", 4, eta, "etabar-CKM", true);

        SLHAea_add_block(slha, "MASS");
        SLHAea_add(slha, "MASS", 1, smObject.get_qmass_pole(1), "Md - pole", true);
        SLHAea_add(slha, "MASS", 2, smObject.get_qmass_pole(2), "Mu - pole", true);
        SLHAea_add(slha, "MASS", 3, smObject.get_qmass_pole(3), "Ms - pole", true);
        SLHAea_add(slha, "MASS", 4, smObject.get_qmass_pole(4), "Mc - pole", true);
        SLHAea_add(slha, "MASS", 5, smObject.get_qmass_pole(5), "Mb - pole", true);
        SLHAea_add(slha, "MASS", 6, smObject.get_qmass_pole(6), "Mt - pole", true);
        SLHAea_add(slha, "MASS", 11, smObject.get_lmass_pole(1), "Me - pole", true);
        SLHAea_add(slha, "MASS", 13, smObject.get_lmass_pole(2), "Mmu - pole", true);
        SLHAea_add(slha, "MASS", 15, smObject.get_lmass_pole(3), "Mtau - pole", true);
        SLHAea_add(slha, "MASS", 23, MZ, "MZ", true);
        SLHAea_add(slha, "MASS", 24, MW, "MW", true);
        SLHAea_add(slha, "MASS", 25, m_h, "Mh0_1", true);
        SLHAea_add(slha, "MASS", 35, m_H, "Mh0_2", true);
        SLHAea_add(slha, "MASS", 36, m_A, "MA0", true);
        SLHAea_add(slha, "MASS", 37, m_Hp, "MHc", true);

        SLHAea_add_block(slha, "ALPHA");
        SLHAea_add(slha, "ALPHA", 0, thdmObject.get_alpha(), "alpha", true);

        vector<double> matrix_u, matrix_d, matrix_l;

        for (int i=0;i<3;i++) { if (debug_THDM) cout << "DBG 70" << endl;
          for (int j=0;j<3;j++) { if (debug_THDM) cout << "DBG 71" << endl;
            matrix_u.push_back(0);
            matrix_d.push_back(0);
            matrix_l.push_back(0);
            // fills with 9 zeros
          }
        }

        // ---
        // adapted from 2HDMC code - THDMC.cpp
        double k1,k2,k3,r1,r2,r3;
        thdmObject.get_kappa_up(k1,k2,k3);
        thdmObject.get_yukawas_up(r1,r2,r3);
        (k1>0 ? matrix_u[0] = r1/k1 : matrix_u[0]=0.);
        (k2>0 ? matrix_u[4] = r2/k2 : matrix_u[4]=0.);
        (k3>0 ? matrix_u[8] = r3/k3 : matrix_u[8]=0.);

        thdmObject.get_kappa_down(k1,k2,k3);
        thdmObject.get_yukawas_down(r1,r2,r3);
        (k1>0 ? matrix_d[0] = r1/k1 : matrix_d[0]=0.);
        (k2>0 ? matrix_d[4] = r2/k2 : matrix_d[4]=0.);
        (k3>0 ? matrix_d[8] = r3/k3 : matrix_d[8]=0.);

        thdmObject.get_kappa_lepton(k1,k2,k3);
        thdmObject.get_yukawas_lepton(r1,r2,r3);
        (k1>0 ? matrix_l[0] = r1/k1 : matrix_l[0]=0.);
        (k2>0 ? matrix_l[4] = r2/k2 : matrix_l[4]=0.);
        (k3>0 ? matrix_l[8] = r3/k3 : matrix_l[8]=0.);
        // ---

        SLHAea_add_block(slha, "UCOUPL");
        SLHAea_add_matrix(slha, "UCOUPL", matrix_u, 3, 3, "LU", true);

        SLHAea_add_block(slha, "DCOUPL");
        SLHAea_add_matrix(slha, "DCOUPL", matrix_d, 3, 3, "LU", true);

        SLHAea_add_block(slha, "LCOUPL");
        SLHAea_add_matrix(slha, "LCOUPL", matrix_l, 3, 3, "LU", true);

        result = slha;
      }


      // functions to fill basis at QrunTo - only available for THDMatQ
      // used for printing thdm values for plotting/debug

      void fill_THDM_coupling_basis(thdm_coupling_basis &result)
      { if (debug_THDM) cout << "DBG 72" << endl;
        using namespace Pipes::fill_THDM_coupling_basis;

        thdm_coupling_basis couplingBasis;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        const SMInputs& sminputs   = fullspectrum.get_SMInputs();

        unique_ptr<SubSpectrum> spec = fullspectrum.clone_HE();

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
      { if (debug_THDM) cout << "DBG 73" << endl;
        using namespace Pipes::fill_THDM_phys_basis;

        thdm_physical_basis phys_basis;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        unique_ptr<SubSpectrum> spec = fullspectrum.clone_HE();

        double QrunTo = *Param.at("QrunTo");

        spec -> RunToScale(QrunTo);

        double m_h = spec->get(Par::Pole_Mass, "h0",1);
        double m_H = spec->get(Par::Pole_Mass, "h0",2);
        double m_A = spec->get(Par::Pole_Mass, "A0");
        double m_Hp = spec->get(Par::Pole_Mass, "H+");
        double alpha = spec->get(Par::dimensionless, "alpha");
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

      void print_lambda1_coupling_basis(double& result)
      { if (debug_THDM) cout << "DBG 74" << endl;

        cout << "BITE1" << endl;

        using namespace Pipes::print_lambda1_coupling_basis;

        cout << "BITE2" << endl;

        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;

        cout << "BITE3" << endl;

        result = couplingBasis.lambda1;

        cout << "BITE4" << endl;

      }

      void print_lambda2_coupling_basis(double& result)
      { if (debug_THDM) cout << "DBG 75" << endl;

        using namespace Pipes::print_lambda2_coupling_basis;

        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;

        result = couplingBasis.lambda2;

      }

      void print_lambda3_coupling_basis(double& result)
      { if (debug_THDM) cout << "DBG 76" << endl;

        using namespace Pipes::print_lambda3_coupling_basis;

        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;

        result = couplingBasis.lambda3;

      }

      void print_lambda4_coupling_basis(double& result)
      { if (debug_THDM) cout << "DBG 77" << endl;

        using namespace Pipes::print_lambda4_coupling_basis;

        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;

        result = couplingBasis.lambda4;

      }

      void print_lambda5_coupling_basis(double& result)
      { if (debug_THDM) cout << "DBG 78" << endl;

        using namespace Pipes::print_lambda5_coupling_basis;

        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;

        result = couplingBasis.lambda5;

      }

      void print_tanb_coupling_basis(double& result)
      { if (debug_THDM) cout << "DBG 79" << endl;

        using namespace Pipes::print_tanb_coupling_basis;

        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;

        result = couplingBasis.tanb;

      }

      void print_m12_2_coupling_basis(double& result)
      { if (debug_THDM) cout << "DBG 80" << endl;

        using namespace Pipes::print_m12_2_coupling_basis;

        const thdm_coupling_basis couplingBasis = *Dep::Coupling_Basis;

        result = couplingBasis.m12_2;

      }

      void print_mh0_phys_basis(double& result)
      { if (debug_THDM) cout << "DBG 81" << endl;

        using namespace Pipes::print_mh0_phys_basis;

        const thdm_physical_basis physBasis = *Dep::Physical_Basis;

        result = physBasis.mh0;

      }

      void print_mH0_phys_basis(double& result)
      { if (debug_THDM) cout << "DBG 82" << endl;

        using namespace Pipes::print_mH0_phys_basis;

        const thdm_physical_basis physBasis = *Dep::Physical_Basis;

        result = physBasis.mH0;

      }

      void print_mHp_phys_basis(double& result)
      { if (debug_THDM) cout << "DBG 83" << endl;

        using namespace Pipes::print_mHp_phys_basis;

        const thdm_physical_basis physBasis = *Dep::Physical_Basis;

        result = physBasis.mHp;

      }

      void print_mA_phys_basis(double& result)
      { if (debug_THDM) cout << "DBG 84" << endl;

        using namespace Pipes::print_mA_phys_basis;

        const thdm_physical_basis physBasis = *Dep::Physical_Basis;

        result = physBasis.mA;

      }

      void print_tanb_phys_basis(double& result)
      { if (debug_THDM) cout << "DBG 85" << endl;

        using namespace Pipes::print_tanb_phys_basis;

        const thdm_physical_basis physBasis = *Dep::Physical_Basis;

        result = physBasis.tanb;

      }

      void print_sba_phys_basis(double& result)
      { if (debug_THDM) cout << "DBG 86" << endl;

        using namespace Pipes::print_sba_phys_basis;

        const thdm_physical_basis physBasis = *Dep::Physical_Basis;

        result = physBasis.sba;

      }

      void print_m12_2_phys_basis(double& result)
      { if (debug_THDM) cout << "DBG 87" << endl;

        using namespace Pipes::print_m12_2_phys_basis;

        const thdm_physical_basis physBasis = *Dep::Physical_Basis;

        result = physBasis.m12_2;

      }


      /// Put together the Higgs couplings for the THDM, from partial widths only
      void THDM_higgs_couplings_pwid(HiggsCouplingsTable &result)
      { if (debug_THDM) cout << "DBG 88" << endl;
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
        { if (debug_THDM) cout << "DBG 89" << endl;
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
        { if (debug_THDM) cout << "DBG 90" << endl;
          double mhi = spec.get(Par::Pole_Mass, sHneut[i]);
          double mhj = spec.get(Par::Pole_Mass, sHneut[j]);
          if (mhi > mhj + mZ and result.get_neutral_decays(i).has_channel(sHneut[j], "Z0"))
          { if (debug_THDM) cout << "DBG 91" << endl;
            double gamma = result.get_neutral_decays(i).width_in_GeV*result.get_neutral_decays(i).BF(sHneut[j], "Z0");
            double k[2] = {(mhj + mZ)/mhi, (mhj - mZ)/mhi};
            for (int l = 0; l < 2; l++) k[l] = (1.0 - k[l]) * (1.0 + k[l]);
            double K = mhi*sqrt(k[0]*k[1]);
            result.C_hiZ2[i][j] = scaling / (K*K*K) * gamma;
          }
          else // If the channel is missing from the decays or kinematically disallowed, just return the SM result.
          { if (debug_THDM) cout << "DBG 93" << endl;
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
    { if (debug_THDM) cout << "DBG 94" << endl;
      // SoftSUSY object used to set quark and lepton masses and gauge
      // couplings in QEDxQCD effective theory
      // Will be initialised by default using values in lowe.h, which we will
      // override next.
      softsusy::QedQcd oneset;

      // Fill QedQcd object with SMInputs values
      setup_QedQcd(oneset,sminputs);

      cout << "SMINPUTS: " << sminputs.mU << endl;

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
      settings.set(Spectrum_generator_settings::calculate_sm_masses, runOptions.getValueOrDef<bool> (false, "calculate_sm_masses"));
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
      settings.set(Spectrum_generator_settings::threshold_corrections, runOptions.getValueOrDef<int>(1,"threshold_corrections"));

      
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

      
    //   // This object will COPY the interface data members into itself, so it is now the
    //   // one-stop-shop for all spectrum information, including the model interface object.
    //   MSSMSpec<MI> mssmspec(model_interface, "FlexibleSUSY", "2.0.beta");

    //   // Add extra information about the scales used to the wrapper object
    //   // (last parameter turns on the 'allow_new' option for the override setter, which allows
    //   //  us to set parameters that don't previously exist)
    //   mssmspec.set_override(Par::mass1,spectrum_generator.get_high_scale(),"high_scale",true);
    //   mssmspec.set_override(Par::mass1,spectrum_generator.get_susy_scale(),"susy_scale",true);
    //   mssmspec.set_override(Par::mass1,spectrum_generator.get_low_scale(), "low_scale", true);

      // This object will COPY the interface data members into itself, so it is now the
      // one-stop-shop for all spectrum information, including the model interface object.
      THDMSpec<MI> thdmspec(model_interface, "FlexibleSUSY", "2.0.beta");

      // Add extra information about the scales used to the wrapper object
      // (last parameter turns on the 'allow_new' option for the override setter, which allows
      //  us to set parameters that don't previously exist)
      thdmspec.set_override(Par::mass1,spectrum_generator.get_high_scale(),"high_scale",true);
      thdmspec.set_override(Par::mass1,spectrum_generator.get_susy_scale(),"susy_scale",true);
      thdmspec.set_override(Par::mass1,spectrum_generator.get_low_scale(), "low_scale", true);

      double sba = sin(atan(*input_Param.at("tanb")) - *input_Param.at("alpha"));

      thdmspec.set_override(Par::dimensionless, sba, "sba", true);

      thdmspec.set_override(Par::dimensionless, 2 , "YukawaType", true);
      //thdmspec.set_override(Par::dimensionless, *input_Param.at("YukawaType") , "YukawaType", true);

            //MSSM THEORY ERRORS//
    //   // Add theory errors
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
      //   { if (debug_THDM) cout << "DBG " << endl;
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
      { if (debug_THDM) cout << "DBG 95" << endl;
         if( runOptions.getValueOrDef<bool>(false,"invalid_point_fatal") )
         { if (debug_THDM) cout << "DBG 96" << endl;
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
         { if (debug_THDM) cout << "DBG 97" << endl;

            // //EXTRA DEBUG INFO
            // std::ostringstream errmsg;
            // cout << "FS DEBUG INFO:" << endl
            // problems.print_problems(errmsg);
            // problems.print_warnings(errmsg);
            // //---------------------

            /// Check what the problem was
            /// see: contrib/MassSpectra/flexiblesusy/src/problems.hpp
            std::ostringstream msg;
            cout << " FS message: " << msg.str() << endl;
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
         }
      }

      if( problems.have_warning() )
      { if (debug_THDM) cout << "DBG 98" << endl;
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

      cout << "filled spectrum" << endl;
      // Package QedQcd SubSpectrum object, MSSM SubSpectrum object, and SMInputs struct into a 'full' Spectrum object
        model_interface.model.print(cout);
        return Spectrum(qedqcdspec,thdmspec,sminputs,&input_Param,mass_cut,mass_ratio_cut);
    //   return Spectrum(qedqcdspec,mssmspec,sminputs,&input_Param,mass_cut,mass_ratio_cut);
    }


//   template <class MI>
//     Spectrum run_FS_spectrum_generator
//         ( const typename MI::InputParameters& input
//         , const SMInputs& sminputs
//         , const Options& runOptions
//         , const std::map<str, safe_ptr<double> >& input_Param
//         )
//     { if (debug_THDM) cout << "DBG " << endl;
//       // SoftSUSY object used to set quark and lepton masses and gauge
//       // couplings in QEDxQCD effective theory
//       // Will be initialised by default using values in lowe.h, which we will
//       // override next.
//       softsusy::QedQcd oneset;

//       // Fill QedQcd object with SMInputs values
//       setup_QedQcd(oneset,sminputs);

//       // Run everything to Mz
//       oneset.toMz();


//       // Create spectrum generator object
//       typename MI::SpectrumGenerator spectrum_generator;

//         //double PoleMassScale = *input_Param.at("QrunTo");


//       #define SPECGEN_SET(NAME,TYPE,DEFAULTVAL) \
//          CAT_2(spectrum_generator.set_, NAME) BOOST_PP_LPAREN() runOptions.getValueOrDef<TYPE> \
//                BOOST_PP_LPAREN() DEFAULTVAL BOOST_PP_COMMA() STRINGIFY(NAME) \
//                BOOST_PP_RPAREN() BOOST_PP_RPAREN()

//       SPECGEN_SET(precision_goal,                    double, 1.0e-4);
//       SPECGEN_SET(max_iterations,                    double, 0 );
//       SPECGEN_SET(calculate_sm_masses,               bool, false );
//       SPECGEN_SET(pole_mass_loop_order,              int, 2 );
//       SPECGEN_SET(ewsb_loop_order,                   int, 2 );
//       SPECGEN_SET(beta_loop_order,                   int, 2 );
//       SPECGEN_SET(threshold_corrections_loop_order,  int, 1 );
//       //SPECGEN_SET(pole_scale,                   double, PoleMassScale);

//       #undef SPECGEN_SET


//       // Higgs loop corrections are a little different... sort them out now
//       Two_loop_corrections two_loop_settings;


//       // alpha_t alpha_s
//       // alpha_b alpha_s
//       // alpha_t^2 + alpha_t alpha_b + alpha_b^2
//       // alpha_tau^2
//       two_loop_settings.higgs_at_as
//          = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_at_as");
//       two_loop_settings.higgs_ab_as
//          = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_ab_as");
//       two_loop_settings.higgs_at_at
//          = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_at_at");
//       two_loop_settings.higgs_atau_atau
//          = runOptions.getValueOrDef<bool>(true,"use_higgs_2loop_atau_atau");


//       spectrum_generator.set_two_loop_corrections(two_loop_settings);

//       // Generate spectrum
//       spectrum_generator.run(oneset, input);

//       // Extract report on problems...
//       const typename MI::Problems& problems = spectrum_generator.get_problems();

//       // Create Model_interface to carry the input and results, and know
//       // how to access the flexiblesusy routines.
//       // Note: Output of spectrum_generator.get_model() returns type, e.g. CMSSM.
//       // Need to convert it to type CMSSM_slha (which alters some conventions of
//       // parameters into SLHA format)
//       MI model_interface(spectrum_generator,oneset,input);

//       // Create SubSpectrum object to wrap flexiblesusy data
//       // THIS IS STATIC so that it lives on once we leave this module function. We
//       // therefore cannot run the same spectrum generator twice in the same loop and
//       // maintain the spectrum resulting from both. But we should never want to do
//       // this.
//       // A pointer to this object is what gets turned into a SubSpectrum pointer and
//       // passed around Gambit.
//       //
//       // This object will COPY the interface data members into itself, so it is now the
//       // one-stop-shop for all spectrum information, including the model interface object.
//       THDMSpec<MI> thdmspec(model_interface, "FlexibleSUSY", "1.5.1");

//       // Add extra information about the scales used to the wrapper object
//       // (last parameter turns on the 'allow_new' option for the override setter, which allows
//       //  us to set parameters that don't previously exist)
//       thdmspec.set_override(Par::mass1,spectrum_generator.get_high_scale(),"high_scale",true);
//       thdmspec.set_override(Par::mass1,spectrum_generator.get_susy_scale(),"susy_scale",true);
//       thdmspec.set_override(Par::mass1,spectrum_generator.get_low_scale(), "low_scale", true);

//       //thdmspec.set_override(Par::dimensionless,  *input_Param.at("sba"), "sba", true);

//       thdmspec.set_override(Par::dimensionless, *input_Param.at("YukawaType") , "YukawaType", true);

//       // Add theory errors


//       static const std::vector<int> i12     = initVector(1,2);
//       static const std::vector<int> i123    = initVector(1,2,3);
//       static const std::vector<int> i1234   = initVector(1,2,3,4);
//       static const std::vector<int> i123456 = initVector(1,2,3,4,5,6);


//       // Do the lightest Higgs mass separately.  The default in most codes is 3 GeV. That seems like
//       // an underestimate if the stop masses are heavy enough, but an overestimate for most points.
//       //double rd_mh1 = 2.0 / thdmspec.get(Par::Pole_Mass, ms.h0, 1);
//       //thdmspec.set_override(Par::Pole_Mass_1srd_high, rd_mh1, ms.h0, 1, true);
//       //thdmspec.set_override(Par::Pole_Mass_1srd_low,  rd_mh1, ms.h0, 1, true);

//       // Do the W mass separately.  Here we use 10 MeV based on the size of corrections from two-loop papers and advice from Dominik Stockinger.
//       double rd_mW = 0.01 / thdmspec.get(Par::Pole_Mass, "W+");
//       thdmspec.set_override(Par::Pole_Mass_1srd_high, rd_mW, "W+", true);
//       thdmspec.set_override(Par::Pole_Mass_1srd_low,  rd_mW, "W+", true);




//       // Create a second SubSpectrum object to wrap the qedqcd object used to initialise the spectrum generator
//       // Attach the sminputs object as well, so that SM pole masses can be passed on (these aren't easily
//       // extracted from the QedQcd object, so use the values that we put into it.)
//       QedQcdWrapper qedqcdspec(oneset,sminputs);

//       // Deal with points where spectrum generator encountered a problem
//       #ifdef SPECBIT_DEBUG
//         std::cout<<"Problem? "<<problems.have_problem()<<std::endl;
//       #endif
//       if( problems.have_problem() )
//       { if (debug_THDM) cout << "DBG " << endl;
//          if( runOptions.getValueOrDef<bool>(false,"invalid_point_fatal") )
//          { if (debug_THDM) cout << "DBG " << endl;
//             ///TODO: Need to tell gambit that the spectrum is not viable somehow. For now
//             /// just die.
//             std::ostringstream errmsg;
//             errmsg << "A serious problem was encountered during spectrum generation!; ";
//             errmsg << "Message from FlexibleSUSY below:" << std::endl;
//             problems.print_problems(errmsg);
//             problems.print_warnings(errmsg);
//             SpecBit_error().raise(LOCAL_INFO,errmsg.str());
//          }
//          else
//          { if (debug_THDM) cout << "DBG " << endl;
//             /// Check what the problem was
//             /// see: contrib/MassSpectra/flexiblesusy/src/problems.hpp
//             std::ostringstream msg;
//             //msg << "";
//             //if( have_bad_mass()      ) msg << "bad mass " << std::endl; // TODO: check which one
//             //if( have_tachyon()       ) msg << "tachyon" << std::endl;
//             //if( have_thrown()        ) msg << "error" << std::endl;
//             //if( have_non_perturbative_parameter()   ) msg << "non-perturb. param" << std::endl; // TODO: check which
//             //if( have_failed_pole_mass_convergence() ) msg << "fail pole mass converg." << std::endl; // TODO: check which
//             //if( no_ewsb()            ) msg << "no ewsb" << std::endl;
//             //if( no_convergence()     ) msg << "no converg." << std::endl;
//             //if( no_perturbative()    ) msg << "no pertub." << std::endl;
//             //if( no_rho_convergence() ) msg << "no rho converg." << std::endl;
//             //if( msg.str()=="" ) msg << " Unrecognised problem! ";

//             /// Fast way for now:
//             problems.print_problems(msg);
//             invalid_point().raise(msg.str()); //TODO: This message isn't ending up in the logs.
//          }
//       }

//       if( problems.have_warning() )
//       { if (debug_THDM) cout << "DBG " << endl;
//          std::ostringstream msg;
//          problems.print_warnings(msg);
//          SpecBit_warning().raise(LOCAL_INFO,msg.str()); //TODO: Is a warning the correct thing to do here?
//       }

//       // Retrieve any mass cuts
//       static const Spectrum::mc_info mass_cut = runOptions.getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), "mass_cut");
//       static const Spectrum::mr_info mass_ratio_cut = runOptions.getValueOrDef<Spectrum::mr_info>(Spectrum::mr_info(), "mass_ratio_cut");

//       // Package QedQcd SubSpectrum object, THDM SubSpectrum object, and SMInputs struct into a 'full' Spectrum object
//       return Spectrum(qedqcdspec,thdmspec,sminputs,&input_Param,mass_cut,mass_ratio_cut);
//     }

    template <class THDMInputStruct>
    void fill_THDM_input(THDMInputStruct &input, const std::map<str, safe_ptr<double> >& Param ,SMInputs sminputs)
    { if (debug_THDM) cout << "DBG 99" << endl;
      // read in THDM model parameters
      double m_h = *Param.at("mh0");
      if (debug_THDM) cout << "DBG 99A1" << endl;
      double m_H = *Param.at("mH0");
      if (debug_THDM) cout << "DBG 99A2" << endl;
      double m_A = *Param.at("mA");
      if (debug_THDM) cout << "DBG 99A3" << endl;
      double m_Hp = *Param.at("mC");
      if (debug_THDM) cout << "DBG 99A4" << endl;
      double alpha = *Param.at("alpha");
      double m12_2 = *Param.at("m12_2");
      double tb = *Param.at("tanb");
      double lambda6 = *Param.at("lambda_6");
      double lambda7 = *Param.at("lambda_7");

      if (debug_THDM) cout << "DBG 99A" << endl;

      double sba = get_sba(tb, alpha);
 
      // set up required quantities
      double beta = atan(tb);
      double ctb = 1./tb;
      double cb  = 1./sqrt(1.+tb*tb);
      double sb  = tb*cb;
      double sb2 = sb*sb;
      double cb2 = cb*cb;

      if (debug_THDM) cout << "DBG 99B" << endl;

      //      double betaAlpha = 0;
      //      //
      //      // if (sba > PI/2)
      //      // { if (debug_THDM) cout << "DBG " << endl;
      //        betaAlpha = acos(sba) + PI/2;
      //      // }
      //      // else if (sba < -PI/2)
      //      // { if (debug_THDM) cout << "DBG " << endl;
      //      //   betaAlpha = acos(sba) - PI/2;
      //      // }
      //      // else
      //      // { if (debug_THDM) cout << "DBG " << endl;
      //      //   betaAlpha = asin(sba);
      //      // }
      //
      //      double alpha = - betaAlpha + beta;
      double sa  = sin(alpha);
      double sa2 = sa*sa;
      double ca  = cos(alpha);
      double ca2 = ca*ca;

      double cba = sqrt(1.-sba*sba);

      double v2= pow (1. / sqrt(sqrt(2.)*sminputs.GF),2);

      // convert
      double lambda_1=(m_H*m_H*ca2+m_h*m_h*sa2-m12_2*tb)/v2/cb2-1.5*lambda6*tb+0.5*lambda7*tb*tb*tb;
      double lambda_2=(m_H*m_H*sa2+m_h*m_h*ca2-m12_2*ctb)/v2/sb2+0.5*lambda6*ctb*ctb*ctb-1.5*lambda7*ctb;
      double lambda_3=((m_H*m_H-m_h*m_h)*ca*sa+2.*m_Hp*m_Hp*sb*cb-m12_2)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;
      double lambda_4=((m_A*m_A-2.*m_Hp*m_Hp)*cb*sb+m12_2)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;
      double lambda_5=(m12_2-m_A*m_A*sb*cb)/v2/sb/cb-0.5*lambda6*ctb-0.5*lambda7*tb;

      if (debug_THDM) cout << "DBG 99C" << endl;

      //m22_2 = -0.5/sb*(pow(m_h,2)*ca*sba+pow(m_H,2)*sa*cba)+m12_2*ctb;
      //double valued parameters
      input.TanBeta     = tb;
      input.Lambda1IN      = lambda_1; // 1/2 to match FS conventions ** DELETED
      input.Lambda2IN      = lambda_2; // 1/2 to match FS conventions ** DELETED
      input.Lambda3IN      = lambda_3;
      input.Lambda4IN      = lambda_4;
      input.Lambda5IN      = lambda_5;
      input.Lambda6IN      = lambda6;
      input.Lambda7IN      = lambda7;

      if (debug_THDM) cout << "DBG 99D" << endl;

      cout << "*lambda_1 = " << lambda_1 << endl;
      cout << "*lambda_2 = " << lambda_2 << endl;
      cout << "*lambda_3 = " << lambda_3 << endl;
      cout << "*lambda_4 = " << lambda_4 << endl;
      cout << "*lambda_5 = " << lambda_5 << endl;


      input.M122IN      = m12_2;              // minus sign to match FS conventions ** DELETED
      input.QEWSB       = *Param.at("Qin");
      input.Qin         = *Param.at("Qin");   // set as option later

      // Sanity checks
      if(input.TanBeta<0)
      { if (debug_THDM) cout << "DBG 100" << endl;
         std::ostringstream msg;
         msg << "Tried to set TanBeta parameter to a negative value ("<<input.TanBeta<<")! This parameter must be positive. Please check your inifile and try again.";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }

    //      cout << "Track Lambda 1 (A): " << input.Lambda1IN << endl;
    //      cout << "Track Lambda 2 (A): " << input.Lambda2IN << endl;
    //      cout << "Track Lambda 3 (A): " << input.Lambda3IN << endl;
    //      cout << "Track Lambda 4 (A): " << input.Lambda4IN << endl;
    //      cout << "Track Lambda 5 (A): " << input.Lambda5IN << endl;
    }


    void get_THDM_spectrum_FS(Spectrum& result)
    { if (debug_THDM) cout << "DBG 101" << endl;

      using namespace softsusy;
      namespace myPipe = Pipes::get_THDM_spectrum_FS;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
      const Options& runOptions=*myPipe::runOptions;
    
      int YukawaType = myPipe::runOptions->getValueOrDef<int>(1, "YukawaType");
      YukawaType = 2;
      THDM_II_input_parameters input;
          fill_THDM_input(input,myPipe::Param,sminputs);

      switch(YukawaType)
      { if (debug_THDM) cout << "DBG 102" << endl;
        case 1:
        { if (debug_THDM) cout << "DBG 103" << endl;
          // THDM_I_input_parameters input;
          // fill_THDM_input(input,myPipe::Param,sminputs);
          // result = run_FS_spectrum_generator<THDM_I_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
          // break;
        }
        case 2:
        { if (debug_THDM) cout << "DBG 104" << endl;
          result = run_FS_spectrum_generator<THDM_II_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
          break;
        }
        case 3:
        { if (debug_THDM) cout << "DBG 105" << endl;
        //   THDM_lepton_input_parameters input;
        //   fill_THDM_input(input,myPipe::Param,sminputs);
        //   result = run_FS_spectrum_generator<THDM_lepton_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
          break;
        }
        case 4:
        { if (debug_THDM) cout << "DBG 106" << endl;
        //   THDM_flipped_input_parameters input;
        //   fill_THDM_input(input,myPipe::Param,sminputs);
        //   result = run_FS_spectrum_generator<THDM_flipped_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
          break;
        }
        default:
        { if (debug_THDM) cout << "DBG 107" << endl;
          std::ostringstream msg;
          msg << "Tried to set the Yukawa Type to "<< YukawaType <<" . Yukawa Type should be 1-4.";
          SpecBit_error().raise(LOCAL_INFO,msg.str());
          exit(1);
          break;
        }
      }

    }

    // void get_THDM_spectrum_FS(Spectrum& result)
    // { if (debug_THDM) cout << "DBG " << endl;
    //   using namespace softsusy;
    //   namespace myPipe = Pipes::get_THDM_spectrum_FS;
    //   const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;
    //   THDM_I_input_parameters input;
    //
    //   fill_THDM_I_input(input,myPipe::Param,sminputs);
    //
    //   result = run_FS_spectrum_generator<THDM_I_interface<ALGORITHM1>>(input,sminputs,*myPipe::runOptions,myPipe::Param);
    //
    // }

    void test_THDM_spectrum_1(double &result)
    { if (debug_THDM) cout << "DBG 108" << endl;
        using namespace Pipes::test_THDM_spectrum_1;

        Spectrum fullspectrum = *Dep::THDM_spectrum;

        unique_ptr<SubSpectrum> spec = fullspectrum.clone_HE();

        double QrunTo = *Param.at("QrunTo");

        cout << "---- running to scale: " << QrunTo << "GeV. "<< endl;

        cout << "mh0 = " <<  spec->get(Par::Pole_Mass, "h0", 1) << endl;
        cout <<  "mH0 = " << spec->get(Par::Pole_Mass, "h0", 2) << endl;
        cout <<  "mA = " << spec->get(Par::Pole_Mass, "A0") << endl;
        cout << "mC = " <<  spec->get(Par::Pole_Mass, "H+") << endl;
        cout << "alpha = " <<  spec->get(Par::dimensionless, "alpha") << endl;
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

        double pertubativity = true;
        for(int i=0; i<lambdas.size(); i++)
        {
          if(abs(lambdas[i]) > 4*PI) pertubativity = false ;
        }

        if(pertubativity)
        {

        spec -> RunToScale(750.0);

        double mh0_1 = spec->get(Par::Pole_Mass, "h0", 1);
        double mh0_2 = spec->get(Par::Pole_Mass, "h0", 2);
        double mA0 = spec->get(Par::Pole_Mass, "A0");
        double mHm = spec->get(Par::Pole_Mass, "H+");
        double alpha = spec->get(Par::dimensionless, "alpha");
        double tb = spec->get(Par::dimensionless, "tanb");
        double m12_2 = spec->get(Par::mass1, "m12_2");

       lambda_1 = spec->get(Par::mass1, "lambda_1");
       lambda_2 = spec->get(Par::mass1, "lambda_2");
       lambda_3 = spec->get(Par::mass1, "lambda_3");
       lambda_4 = spec->get(Par::mass1, "lambda_4");
       lambda_5 = spec->get(Par::mass1, "lambda_5");

        //double sba = get_sba(tb, alpha);

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
        cout << "lambda_1 = " << lambda_1 << endl;
        cout << "lambda_2 = " << lambda_2 << endl;
        cout << "lambda_3 = " << lambda_3 << endl;
        cout << "lambda_4 = " << lambda_4 << endl;
        cout << "lambda_5 = " << lambda_5 << endl;
        cout << "----------------------------------" << endl;
        }
        else
        {
          cout << "Perturbativity failed: Did not run to scale" << endl;
        }

        result = 0;
    }
    void test_THDM_spectrum_2(double &result)
    { if (debug_THDM) cout << "DBG 109" << endl;
      using namespace Pipes::test_THDM_spectrum_2;

      Spectrum fullspectrum = *Dep::THDM_spectrum;
      SubSpectrum& spec = fullspectrum.get_HE();
      double mh0_1 = spec.get(Par::Pole_Mass, "h0",1);
      double mh0_2 = spec.get(Par::Pole_Mass, "h0",2);
      double mA0 = spec.get(Par::Pole_Mass, "A0");
      double mHm = spec.get(Par::Pole_Mass, "H+");
      double alpha = spec.get(Par::dimensionless, "alpha");
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
