//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Loop functions for flavour violating decays of charged leptons (from hep-ph/9403398)
///  And for RK from 1706.07570
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 Aug, 2018 Feb
///
///  \author Cristian Sierra 
///          (cristian.sierra@monash.edu)
///  \date 2020 Oct
///
///  \author Douglas Jacob
///          (douglas.jacob@monash.edu)
///  \date 2020 Nov, Dec
///
///  *********************************************

#include "gambit/Elements/shared_types.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Elements/flav_loop_functions.hpp"
#include "gambit/Elements/ini_functions.hpp"
#include "gambit/Utils/util_types.hpp"

namespace Gambit
{

  //Yukawas vertices for THDM
  namespace Vertices_THDM
  {
    std::complex<double> yff_h(int f, int fp, double mf, Eigen::Matrix3cd xi_f, double vev, double cosab)
    {
      Eigen::Matrix3i delta_ij;
      delta_ij << 1.0,  0.0,  0.0,
                  0.0,  1.0,  0.0,
                  0.0,  0.0,  1.0;

      return (mf/vev)*(std::sqrt(1-cosab*cosab))*delta_ij(f,fp) + (cosab/std::sqrt(2))*xi_f(f,fp);
    }

    std::complex<double> yff_H(int f, int fp, double mf, Eigen::Matrix3cd xi_f, double vev, double cosab)
    {
      Eigen::Matrix3i delta_ij;
      delta_ij << 1.0,  0.0,  0.0,
                  0.0,  1.0,  0.0,
                  0.0,  0.0,  1.0;

      return (mf/vev)*cosab*delta_ij(f,fp) - (std::sqrt(1-cosab*cosab)/std::sqrt(2))*xi_f(f,fp);
    }
  }

  //Auxiliary function to flip the sign and choose the scalar field in the fermion-fermion-Higgs vertex
  namespace Yukawas
  {
    std::complex<double> yff_phi(int f, int i, int j, int phi, double mf, Eigen::Matrix3cd xi_f, Eigen::Matrix3cd VCKM, double vev, double cosab)
    {
       std::complex<double> I(0,1);
       switch(phi)
       {
         case 0 :
           return Vertices_THDM::yff_h(i, j, mf, xi_f, vev, cosab);
         case 1 :
           return Vertices_THDM::yff_H(i, j, mf, xi_f, vev, cosab);
         case 2 :
           if (f==2)//flip sign if it is an up-like quark
           {
             return -I*(1/std::sqrt(2))*xi_f(i,j);
           }
           else
           {
             return I*(1/std::sqrt(2))*xi_f(i,j);
           }
         case 3 :
           std::complex<double> vertex_total(0,0);
           switch(f)
           {
             case 2 ://flip sign and include CKM Matrix if it is an up-like quark
               for (int kk = 0; kk <= 2; ++kk)
               {
                 vertex_total += -VCKM(i,kk)*xi_f(kk,j);
               }
               break;
             case 1 ://include CKM Matrix if it is an down-like quark
               for (int kk = 0; kk <= 2; ++kk)
               {
                 vertex_total += VCKM(i,kk)*xi_f(kk,j);
               }
               break;
             case 0 ://if it is a charged lepton
               vertex_total += xi_f(i,j);
               break;
           }
           return vertex_total;
       }
    }
  }

    //2-loop functions for BR(l>l' gamma) for the gTHDM
    namespace TwoLoopFunctions
    {
        std::complex<double> TwoLoopFH(std::complex<double> x)
        {
           std::complex<double> z(1 - 4*real(x),0);
           if (imag(std::sqrt(z))!=0 or std::real(std::sqrt(z))>0)
           {
             std::complex<double> one(1,0);
             std::complex<double> two(2,0);
             std::complex<double> z(1 - 4*real(x),0);
             std::complex<double> w1 = (-one + std::sqrt(z))/(one + std::sqrt(z));
             std::complex<double> w2 = (one + std::sqrt(z))/(-one + std::sqrt(z));
             std::complex<double> Logs = (-x/(two*std::sqrt(z)))*(-two*two*std::sqrt(z) - two*std::sqrt(z)*std::log(x) - std::log(w1)*std::log(x) + two*x*std::log(w1)*std::log(x) + std::log(w2)*std::log(x) - two*x*std::log(w2)*std::log(x));
             std::complex<double> w4 = (-two)/(-one + std::sqrt(z));
             std::complex<double> w5 = (two)/(one + std::sqrt(z));
             gsl_sf_result reD1, imD1;
             gsl_sf_result reD2, imD2;
             gsl_sf_complex_dilog_e(abs(w4), arg(w4), &reD1, &imD1);
             std::complex<double> Dilog1(reD1.val,imD1.val);
             gsl_sf_complex_dilog_e(abs(w5), arg(w5), &reD2, &imD2);
             std::complex<double> Dilog2(reD2.val,imD2.val);
             std::complex<double> Dilogs = (-x/(two*std::sqrt(z)))*((-two + two*two*x)*Dilog1 + (two - two*two*x)*Dilog2);
             // cout<<"OneLoopFH(x) = " << std::real(Logs+Dilogs) << endl;
             return std::real(Logs+Dilogs);
           }
           else
           {
             utils_error().raise(LOCAL_INFO, "1/0 in dilog OneLoopFH");
           }
         }

        std::complex<double> TwoLoopFA(std::complex<double> x)
        {
           std::complex<double> z(1 - 4*real(x),0);
           if (imag(std::sqrt(z))!=0 or std::real(std::sqrt(z))>0)
            {
             std::complex<double> one(1,0);
             std::complex<double> two(2,0);
             std::complex<double> z(1 - 4*real(x),0);
             std::complex<double> w1 = (-one + std::sqrt(z))/(one + std::sqrt(z));
             std::complex<double> w2 = (one + std::sqrt(z))/(-one + std::sqrt(z));
             std::complex<double> Logs = (-x/(two*std::sqrt(z)))*(-std::log(w1)+std::log(w2))*std::log(x);
             std::complex<double> w4 = (-two)/(-one + std::sqrt(z));
             std::complex<double> w5 = (two)/(one + std::sqrt(z));
             gsl_sf_result reD1, imD1;
             gsl_sf_result reD2, imD2;
             gsl_sf_complex_dilog_e(abs(w4), arg(w4), &reD1, &imD1);
             std::complex<double> Dilog1(reD1.val,imD1.val);
             gsl_sf_complex_dilog_e(abs(w5), arg(w5), &reD2, &imD2);
             std::complex<double> Dilog2(reD2.val,imD2.val);
             std::complex<double> Dilogs = (-x/(two*std::sqrt(z)))*(-two*Dilog1 + two*Dilog2);
             return std::real(Logs+Dilogs);
            }
            else
            {
              utils_error().raise(LOCAL_INFO, "1/0 in dilog TwoLoopFA");
            }
        }

        std::complex<double> TwoLoopGW(std::complex<double> x)
        {
           std::complex<double> z(1 - 4*real(x),0);
           if (imag(std::sqrt(z))!=0 or std::real(std::sqrt(z))>0)
           {
             std::complex<double> one(1,0);
             std::complex<double> two(2,0);
             std::complex<double> four(4,0);
             std::complex<double> z(1 - 4*real(x),0);
             std::complex<double> w1 = (-one + std::sqrt(z))/(one + std::sqrt(z));
             std::complex<double> w2 = (one + std::sqrt(z))/(-one + std::sqrt(z));
             std::complex<double> Logs =  - std::sqrt(-z)*std::log(-one - std::sqrt(z)) + four*x*std::sqrt(-z)*std::log(-one - std::sqrt(z))
                             + std::sqrt(-z)*std::log(one - std::sqrt(z)) - four*x*std::sqrt(-z)*std::log(one - std::sqrt(z))         
                             + std::sqrt(-z)*std::log(-one + std::sqrt(z)) - four*x*std::sqrt(-z)*std::log(-one + std::sqrt(z)) - std::sqrt(-z)*std::log(one + std::sqrt(z))
                             + four*x*std::sqrt(-z)*std::log(one + std::sqrt(z)) - two*std::sqrt(-std::pow(-z,2))*std::log(x)         
                             + two*x*std::sqrt(-z)*std::log(w1)*std::log(one/x) - two*x*std::sqrt(-z)*std::log(w2)*std::log(one/x);
             std::complex<double> w4 = (-two)/(-one + std::sqrt(z));
             std::complex<double> w5 = (two)/(one + std::sqrt(z));
             gsl_sf_result reD1, imD1;
             gsl_sf_result reD2, imD2;
             gsl_sf_complex_dilog_e(abs(w4), arg(w4), &reD1, &imD1);
             std::complex<double> Dilog1(reD1.val,imD1.val);
             gsl_sf_complex_dilog_e(abs(w5), arg(w5), &reD2, &imD2);
             std::complex<double> Dilog2(reD2.val,imD2.val);
             std::complex<double> Dilogs = four*x*std::sqrt(-z)*(-Dilog1 + Dilog2);
             std::complex<double> Atans = -four*std::sqrt(z)*atan(one/std::sqrt(-z))*(one-four*x);
             return std::real((x/(two*std::sqrt(z)*std::pow(-z,1.5)))*(Logs+Dilogs+Atans));
           }
           else
           {
             utils_error().raise(LOCAL_INFO, "1/0 in dilog TwoLoopGW");
           }
        }

      // Two Loop Functions for Muon g-2 for gTHDM
      //  Source:  1607.06292, eqn (68)
      std::complex<double> TwoLoopPhi(double m1, double m2, double m3)
      { 
        if (m3 != 0)
        {
          std::complex<double> argum  = std::complex<double> (std::pow(m1,4)+std::pow(m2,4)+std::pow(m3,4)-2*std::pow(m1*m2,2)-2*std::pow(m2*m3,2)-2*std::pow(m3*m1,2));
          std::complex<double> lambda = std::sqrt(argum);
          std::complex<double> alphap = (std::pow(m3,2)+std::pow(m1,2)-std::pow(m2,2)-lambda) / (2*std::pow(m3,2));
          std::complex<double> alpham = (std::pow(m3,2)-std::pow(m1,2)+std::pow(m2,2)-lambda) / (2*std::pow(m3,2));
          gsl_sf_result reD1, imD1;
          gsl_sf_complex_dilog_e(abs(alphap), arg(alphap), &reD1, &imD1);
          std::complex<double> Dilog1(reD1.val,imD1.val);
          gsl_sf_result reD2, imD2;
          gsl_sf_complex_dilog_e(abs(alpham), arg(alpham), &reD2, &imD2);
          std::complex<double> Dilog2(reD2.val,imD2.val);
          return lambda/2. * (2.*std::log(alphap)*std::log(alpham) - std::log(std::pow(m1/m3,2))*std::log(pow(m2/m3,2)) - 2.*Dilog1 - 2.*Dilog2 + std::pow(M_PI,2)/3.);
        } 
        else 
        { 
          utils_error().raise(LOCAL_INFO, "1/0 in dilog TwoLoopPhi");
        }
      }   
        
      //  Source:  1607.06292, eqns (54-57)
      std::complex<double> TwoLoopfgammaphi(int Nc, double Qf, double alph, double mmu, double mf, double mphi, double mW, double mZ)
      {
        double sw2 = 1-std::pow(mW/mZ,2);
        std::complex<double> Fphi = -2. + std::log(std::pow(mphi/mf,2)) - (std::pow(mphi,2)-2.*std::pow(mf,2))/std::pow(mphi,2) * TwoLoopFunctions::TwoLoopPhi(mphi,mf,mf)/(std::pow(mphi,2)-4.*std::pow(mf,2));
        return Nc * std::pow(Qf * alph * mmu,2) / pow(2.*M_PI*mW,2) / sw2 * std::pow(mf/mphi,2) * Fphi;
      }

      std::complex<double> TwoLoopfZbosonphi(int Nc, double Qf, double alph, double mmu, double mf, double mphi, double mW, double mZ, double glv, double gfv)
      {
        double sw2 = 1-std::pow(mW/mZ,2);
        double cw2 = 1-sw2;
        std::complex<double> Fphi = -2. + std::log(std::pow(mphi/mf,2)) - (std::pow(mphi,2)-2.*std::pow(mf,2))/std::pow(mphi,2) * TwoLoopFunctions::TwoLoopPhi(mphi,mf,mf)/(std::pow(mphi,2)-4.*std::pow(mf,2));
        std::complex<double> FZ   = -2. + std::log(std::pow(mZ/mf,2)) - (std::pow(mZ,2)-2.*std::pow(mf,2))/std::pow(mZ,2) * TwoLoopFunctions::TwoLoopPhi(mZ,mf,mf)/(std::pow(mZ,2)-4.*std::pow(mf,2));
        return -Nc * Qf * glv * gfv * std::pow(alph * mmu,2) / std::pow(2.*M_PI*mW*sw2,2) / cw2 * std::pow(mf,2)/(std::pow(mphi,2)-std::pow(mZ,2)) * (Fphi-FZ);
      }

      std::complex<double> TwoLoopfgammaA(int Nc, double Qf, double alph, double mmu, double mf, double mphi, double mW, double mZ)
      {
        double sw2 = 1-std::pow(mW/mZ,2);
        std::complex<double> Fphi = TwoLoopFunctions::TwoLoopPhi(mphi,mf,mf)/(std::pow(mphi,2)-4.*std::pow(mf,2));
        return Nc * std::pow(Qf * alph * mmu,2) / pow(2.*M_PI*mW,2) / sw2 * std::pow(mf/mphi,2) * Fphi;
      }

      std::complex<double> TwoLoopfZbosonA(int Nc, double Qf, double alph, double mmu, double mf, double mphi, double mW, double mZ, double glv, double gfv)
      {
        double sw2 = 1-std::pow(mW/mZ,2);
        double cw2 = 1-sw2;
        std::complex<double> Fphi = TwoLoopFunctions::TwoLoopPhi(mphi,mf,mf)/(std::pow(mphi,2)-4.*std::pow(mf,2));
        std::complex<double> FZ   = TwoLoopFunctions::TwoLoopPhi(mZ,mf,mf)/(std::pow(mZ,2)-4.*std::pow(mf,2));
        return -Nc * Qf * glv * gfv * std::pow(alph * mmu,2) / std::pow(2.*M_PI*mW*sw2,2) / cw2 * std::pow(mf,2)/(std::pow(mphi,2)-std::pow(mZ,2)) * (Fphi-FZ);
      }

      //  Source:  1607.06292, eqns (60-62)
      std::complex<double> TwoLoopfCl(double xl)
      {
        std::complex<double> z = 1.-1./xl;
        if (z != 0.)
        {
          gsl_sf_result reD, imD;
          gsl_sf_complex_dilog_e(abs(z), arg(z), &reD, &imD);
          std::complex<double> Dilog(reD.val,imD.val);
          return xl + xl * (xl-1.) * (Dilog-std::pow(M_PI,2)/6.) + (xl-0.5)*std::log(xl);
        }
        else
        {
          utils_error().raise(LOCAL_INFO, "1/0 in dilog TwoLoopfCl");
        }
      }

      std::complex<double> TwoLoopfCd(double xu, double xd, double Qu, double Qd)
      {
        double y  = std::pow(xu-xd,2) - 2.*(xu+xd) + 1.;
        double s  = (Qu + Qd) / 4.;
        double c  = std::pow(xu-xd,2) - Qu*xu + Qd*xd;
        double cb = (xu-Qu)*xu - (xd+Qd)*xd;
        std::complex<double> z = 1.-xd/xu;
        if (z != 0.)
        {
          gsl_sf_result reD, imD;
          gsl_sf_complex_dilog_e(abs(z), arg(z), &reD, &imD);
          std::complex<double> Dilog(reD.val,imD.val);
          return -(xu-xd) + (cb/y-c*(xu-xd)/y) * TwoLoopFunctions::TwoLoopPhi(std::sqrt(xd),std::sqrt(xu),1.) \
                 + c * (Dilog - 0.5*std::log(xu)*std::log(xd/xu) * TwoLoopFunctions::TwoLoopPhi(std::sqrt(xd),std::sqrt(xu),1.)) \
                 + (s+xd) * std::log(xd) + (s-xu)*std::log(xu);
        }
        else
        {
          utils_error().raise(LOCAL_INFO, "1/0 in dilog TwoLoopfCd");
        }      
      }

      std::complex<double> TwoLoopfCu(double xu, double xd, double Qu, double Qd)
      {
        double y  = std::pow(xu-xd,2) - 2.*(xu+xd) + 1.;
        double s  = (Qu + 2. + Qd + 2.) / 4.;
        double c  = std::pow(xu-xd,2) - (Qu+2.)*xu + (Qd+2.)*xd;
        double cb = (xu-Qu-2.)*xu - (xd+Qd+2.)*xd;
        std::complex<double> z = 1.-xd/xu;
        if (z != 0.)
        {
          gsl_sf_result reD, imD;
          gsl_sf_complex_dilog_e(abs(z), arg(z), &reD, &imD);
          std::complex<double> Dilog(reD.val,imD.val);
          return -(xu-xd) + (cb/y-c*(xu-xd)/y) * TwoLoopFunctions::TwoLoopPhi(std::sqrt(xd),std::sqrt(xu),1.) \
                 + c * (Dilog - 0.5*std::log(xu)*std::log(xd/xu) * TwoLoopFunctions::TwoLoopPhi(std::sqrt(xd),std::sqrt(xu),1.)) \
                 + (s+xd) * std::log(xd) + (s-xu)*std::log(xu) \
                 - 4./3. * (xu-xd-1.)/y * TwoLoopFunctions::TwoLoopPhi(std::sqrt(xd),std::sqrt(xu),1.) - 1./3.*(std::pow(std::log(xd),2)-std::pow(std::log(xu),2));
        }
        else
        {
          utils_error().raise(LOCAL_INFO, "1/0 in dilog TwoLoopfCu");
        }
      }

      std::complex<double> TwoLoopfC(int lf, int Nc, double Qu, double Qd, double alph, double mmu, std::vector<double> mf, double mphi, double mW, double mZ)
      {
        double sw2 = 1-std::pow(mW/mZ,2);
        if (lf == 0)
        {
          const double xlC = std::pow(mf[lf]/mphi,2);
          const double xlW = std::pow(mf[lf]/mW,2);
          return std::pow((alph*mmu)*mf[f]/(M_PI*mW*sw2),2) * Nc / (std::pow(mphi,2)-std::pow(mW,2)) / 32. * (TwoLoopFunctions::TwoLoopfCl(xlC) - TwoLoopFunctions::TwoLoopfCl(xlW));
        } 
        else if (lf == 1)
        {
          const double xuC = std::pow(mf[2]/mphi,2);
          const double xdC = std::pow(mf[1]/mphi,2);
          const double xuW = std::pow(mf[2]/mW,2);
          const double xdW = std::pow(mf[1]/mW,2);
          return std::pow((alph*mmu)*mf[lf]/(M_PI*mW*sw2),2) * Nc / (std::pow(mphi,2)-std::pow(mW,2)) / 32. * (TwoLoopFunctions::TwoLoopfCd(xuC, xdC, Qu, Qd) - TwoLoopFunctions::TwoLoopfCd(xuW, xdW, Qu, Qd));
        }
        else if (lf == 2)
        {          
          const double xuC = std::pow(mf[2]/mphi,2);
          const double xdC = std::pow(mf[1]/mphi,2);
          const double xuW = std::pow(mf[2]/mW,2);
          const double xdW = std::pow(mf[1]/mW,2);
          return std::pow((alph*mmu)*mf[lf]/(M_PI*mW*sw2),2) * Nc / (std::pow(mphi,2)-std::pow(mW,2)) / 32. * (TwoLoopFunctions::TwoLoopfCu(xuC, xdC, Qu, Qd) - TwoLoopFunctions::TwoLoopfCu(xuW, xdW, Qu, Qd));
        }
      }

      //  Source:  1502.04199, eqn (25-29)
      double TwoLoopf1(double x, void * params)
      {
        double w = *(double *) params;
        return w/2. * (2.*x*(1.-x)-1.) / (w-x*(1.-x)) * std::log(w/(x*(1.-x)));
      }

      double TwoLoopf2(double x, void * params)
      {
        double w = *(double *) params;
        return 1./2. * x*(x-1.) / (w-x*(1.-x)) * std::log(w/(x*(1.-x)));
      }

      double TwoLoopf3(double x, void * params)
      {
        double w = *(double *) params;
        return 1./2. * (x*w*(3.*x*(4.*x-1.)+10.)-x*(1.-x)) / (w-x*(1.-x)) * std::log(w/(x*(1.-x)));
      }

      double TwoLoopf4(double x, void * params)
      {
        double w = *(double *) params;
        return w/2. * 1. / (w-x*(1.-x)) * std::log(w/(x*(1.-x)));
      }
      
      double TwoLoopF1(double w)
      {
        // Integral of w/2 * integral((2*x*(1-x)-1) / (w-x*(1-x)) * log(w/(x*(1-x))),{x,0,1})
        double result, error;
        const int alloc = 1000;
        gsl_integration_workspace * work = gsl_integration_workspace_alloc (alloc);
        gsl_function fun;
        fun.function = &TwoLoopf1;
        fun.params = &w;
        gsl_integration_qags (&fun, 0, 1, 0, 1e-7, alloc, work, &result, &error);
        gsl_integration_workspace_free(work);

        return result;
      }

      double TwoLoopF2(double w)
      {
        // Integral of 1/2 * integral(x*(x-1) / (w-x*(1-x)) * log(w/(x*(1-x))),{x,0,1})
        double result, error;
        const int alloc = 1000;
        gsl_integration_workspace * work = gsl_integration_workspace_alloc (alloc);
        gsl_function fun;
        fun.function = &TwoLoopf2;
        fun.params = &w;
        gsl_integration_qags (&fun, 0, 1, 0, 1e-7, alloc, work, &result, &error);
        gsl_integration_workspace_free(work);

        return result;
      }

      double TwoLoopF3(double w)
      {
        // Integral of 1/2 * integral((x*w*(3*x*(4*x-1)+10)-x*(1-x)) / (w-x*(1.-x)) * log(w/(x*(1-x))),{x,0,1})
        double result, error;
        const int alloc = 1000;
        gsl_integration_workspace * work = gsl_integration_workspace_alloc (alloc);
        gsl_function fun;
        fun.function = &TwoLoopf3;
        fun.params = &w;
        gsl_integration_qags (&fun, 0, 1, 0, 1e-7, alloc, work, &result, &error);
        gsl_integration_workspace_free(work);

        return result;
      }

      double TwoLoopF4(double w)
      {
        // Integral of w/2 * integral(1 / (w-x*(1-x)) * log(w/(x*(1-x))),{x,0,1})
        double result, error;
        const int alloc = 1000;
        gsl_integration_workspace * work = gsl_integration_workspace_alloc (alloc);
        gsl_function fun;
        fun.function = &TwoLoopf4;
        fun.params = &w;
        gsl_integration_qags (&fun, 0, 1, 0, 1e-7, alloc, work, &result, &error);
        gsl_integration_workspace_free(work);

        return result;
      }

      double TwoLoopg(double x, void * params)
      {
        struct G_params * p = (struct G_params *) params;
        double wa = (p->wa);
        double wb = (p->wb);
        int    n  = (p->n);
        return std::pow(x,n) * std::log((wa*x+wb*(1.-x)) / (x*(1.-x))) / (x*(1.-x)-wa*x-wb*(1.-x));
      }

      double TwoLoopG(double wa, double wb, int n)
      {
        // Integral of std::pow(x,n) * log((wa*x+wb*(1-x)) / (x*(1-x))) / (x*(1-x)-wa*x-wb*(1-x))
        double result, error;
        const int alloc = 1000;
        gsl_integration_workspace * work = gsl_integration_workspace_alloc (alloc);

        gsl_function fun;
        struct G_params params = {wa, wb, n};
        fun.function = &TwoLoopg;
        fun.params = &params;

        gsl_integration_qags (&fun, 0, 1, 0, 1e-7, alloc, work, &result, &error);

        gsl_integration_workspace_free(work);

        return result;
      }

    }

    // Loop functions for one loop diagrams
    // Source: FlexibleSUSY v2 manual 1710.03760, eqns (40-43)
    namespace OneLoopFunctions
    {
      double OneLoopB(const double x)
      {
        if(x == 0)
          return 2.;
        else if(x == 1)
          return 1.;
        else if(std::isinf(x))
          return 0.;
        else
          return 2.*(1. - 6.*x + 3.*x*x + 2.*x*x*x - 6.*x*x*std::log(x))/(std::pow(1.-x,4));
      }

      double OneLoopC(const double x)
      {
        if(x == 0)
          return 3.;
        else if(x == 1)
          return 1.;
        else if(std::isinf(x))
          return 0.;
        else
          return 3.*(1. - 1.*x*x + 2.*x*std::log(x))/(std::pow(1.-x,3));
      }

      double OneLoopE(const double x)
      {
        if(x == 0)
          return 4.;
        else if(x == 1)
          return 1.;
        else if(std::isinf(x))
          return 0.;
        else
          return 2.*(2. + 3.*x - 6.*x*x + 1.*x*x*x + 6.*x*std::log(x))/(std::pow(1.-x,4));
      }

      double OneLoopF(const double x)
      {
        if(x == 0)
          return 1./0.;
        else if(x == 1)
          return 1.;
        else if(std::isinf(x))
          return 0.;
        else
          return 3.*(-3. + 4.*x - 1.*x*x - 2.*std::log(x))/(2.*std::pow(1.-x,3));
      }
    }

    // Amplitudes for BR(l>l' gamma) for the gTHDM
    namespace Amplitudes
    {
      //1-loop AL and AR amplitudes
      std::complex<double> A_loop1L(int f, int l, int li, int lp, int phi, std::vector<double> mnu, std::vector<double> ml, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab)
      {
        // f = 0,1,2 for electron,down,up families for external fermion
        // l,li,lp = 0,1,2 are the generation numbers of incoming,internal,outgoing lepton
        // phi = 0,1,2,3 for h,H,A,H+
        // mnu,ml is mass of neutrino,lepton in loop
        // mphi is array of Higgs boson masses
        //Incoming fermion is the dominant contribution here (can be generalized).
        //complex<double> Log(std::log(std::pow(mphi/ml[l],2))-(3./2.),0);
        //complex<double> six(6,0);
        //return  conj(Yukawas::yff_phi(f, l, lp, phi, ml[l], xi_L, VCKM, vev, cosab))*(conj(Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, vev, cosab))*Log+(Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, vev, cosab)/six));
        //General contribution
        if ((phi == 0) or (phi == 1) or (phi == 2))
        {
          //FFS diagram
          double x = std::pow(ml[li]/mphi,2);
          std::complex<double> term1(ml[l]*ml[l]/std::pow(ml[l],2)  * OneLoopFunctions::OneLoopE(x)/24.,0.);
          std::complex<double> term2(ml[l]*ml[lp]/std::pow(ml[l],2) * OneLoopFunctions::OneLoopE(x)/24.,0.);
          std::complex<double> term3(ml[l]*ml[li]/std::pow(ml[l],2) * OneLoopFunctions::OneLoopF(x)/3., 0.);
          return term1*conj(Yukawas::yff_phi(f,li,lp,phi,ml[li],xi_L,VCKM,vev,cosab))*Yukawas::yff_phi(f,li,l,phi,ml[li],xi_L,VCKM,vev,cosab) \
                 + term2*conj(Yukawas::yff_phi(f,l,li,phi,ml[l],xi_L,VCKM,vev,cosab)) *Yukawas::yff_phi(f,lp,li,phi,ml[lp],xi_L,VCKM,vev,cosab) \
                 + term3*conj(Yukawas::yff_phi(f,li,lp,phi,ml[li],xi_L,VCKM,vev,cosab))*conj(Yukawas::yff_phi(f,l,li,phi,ml[l],xi_L,VCKM,vev,cosab));
        }
        else if (phi == 3)
        {
          //SSF diagram
          double x = std::pow(mnu[li]/mphi,2);
          std::complex<double> term1(ml[l]/ml[l] * OneLoopFunctions::OneLoopB(x)/24.,0.);
          return term1*conj(Yukawas::yff_phi(f,li,lp,phi,ml[li],xi_L,VCKM,vev,cosab))*Yukawas::yff_phi(f,li,l,phi,ml[li],xi_L,VCKM,vev,cosab);
        }
      }

      std::complex<double> A_loop1R(int f, int l, int li, int lp, int phi, std::vector<double> mnu, std::vector<double> ml, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab)
      {
        // f = 0,1,2 for electron,down,up families for external fermion
        // l,li,lp = 0,1,2 are the generation numbers of incoming,internal,outgoing lepton
        // phi = 0,1,2,3 for h,H,A,H+
        // mnu,ml is mass of neutrino,lepton in loop
        // mphi is array of Higgs boson masses
        //complex<double> Log(std::log(std::pow(mphi/ml[l],2))-(3./2.),0);
        //complex<double> six(6.,0);
        //return Yukawas::yff_phi(f, l, lp, phi, ml[l], xi_L, VCKM, vev, cosab)*(Yukawas::yff_phi(f, l, l, phi, ml[l], VCKM, xi_L, vev, cosab)*Log+(conj(Yukawas::yff_phi(f, l, l, phi, ml[l], VCKM, xi_L, vev, cosab))/six));
        //General contribution
        if ((phi == 0) or (phi == 1) or (phi == 2))
        {
          //FFS diagram
          double x = std::pow(ml[li]/mphi,2);
          std::complex<double> term1(ml[l]*ml[l]/std::pow(ml[l],2)  * OneLoopFunctions::OneLoopE(x)/24.,0.);
          std::complex<double> term2(ml[l]*ml[lp]/std::pow(ml[l],2) * OneLoopFunctions::OneLoopE(x)/24.,0.);
          std::complex<double> term3(ml[l]*ml[li]/std::pow(ml[l],2) * OneLoopFunctions::OneLoopF(x)/3., 0.);
          return term1*conj(Yukawas::yff_phi(f,l,li,phi,ml[l],xi_L,VCKM,vev,cosab))*Yukawas::yff_phi(f,lp,li,phi,ml[lp],xi_L,VCKM,vev,cosab) \
                 + term2*conj(Yukawas::yff_phi(f,li,lp,phi,ml[li],xi_L,VCKM,vev,cosab)) *Yukawas::yff_phi(f,li,l,phi,ml[li],xi_L,VCKM,vev,cosab) \
                 + term3*Yukawas::yff_phi(f,li,l,phi,ml[li],xi_L,VCKM,vev,cosab)*Yukawas::yff_phi(f,lp,li,phi,ml[lp],xi_L,VCKM,vev,cosab);
        }
        else if (phi == 3)
        {
          //SSF diagram
          double x = std::pow(mnu[l]/mphi,2);
          std::complex<double> term1(ml[lp]/ml[l] * OneLoopFunctions::OneLoopB(x)/24.,0.);
          return term1*conj(Yukawas::yff_phi(f,li,lp,phi,ml[li],xi_L,VCKM,vev,cosab))*Yukawas::yff_phi(f,li,l,phi,ml[li],xi_L,VCKM,vev,cosab);
        }
      }

    //2-loop fermionic contribution
    //AL
    std::complex<double> A_loop2fL(int fe, int lf, int l, int lp, int phi, double ml, double mlf, double mphi, double mZ, double Qf, double QfZ, double sw2, Eigen::Matrix3cd xi_f, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab)
    {
        std::complex<double> I(0,1);
        const int gi = 2; // Internal generation is the heaviest
        double xfphi = std::pow(mlf/mphi,2);
        double xfZ   = std::pow(mlf/mZ,2);
        std::complex<double> FHm = (xfphi*TwoLoopFunctions::TwoLoopFH(xfZ)-xfZ*TwoLoopFunctions::TwoLoopFH(xfphi))/(xfphi-xfZ);
        std::complex<double> FAm = (xfphi*TwoLoopFunctions::TwoLoopFA(xfZ)-xfZ*TwoLoopFunctions::TwoLoopFA(xfphi))/(xfphi-xfZ);
        return conj(Yukawas::yff_phi(fe, l, lp, phi, ml, xi_L, VCKM, vev, cosab))*(real(Yukawas::yff_phi(lf, gi, gi, phi, mlf, xi_f, VCKM, vev, cosab)) * (Qf*TwoLoopFunctions::TwoLoopFH(std::pow(mlf/mphi,2))+(1.-4.*sw2)*QfZ/(16.*sw2*(1-sw2))*FHm)-I*imag(Yukawas::yff_phi(lf, gi, gi, phi, mlf, xi_f, VCKM, vev, cosab)) * (Qf*TwoLoopFunctions::TwoLoopFA(std::pow(mlf/mphi,2))+(1.-4.*sw2)*QfZ/(16.*sw2*(1-sw2))*FAm));
    }
    
    //AR
    std::complex<double> A_loop2fR(int fe, int lf, int l, int lp, int phi, double ml, double mlf, double mphi, double mZ, double Qf, double QfZ, double sw2, Eigen::Matrix3cd xi_f, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab)
    {
        std::complex<double> I(0,1);
        const int gi = 2; // Internal generation is the heaviest
        double xfphi = std::pow(mlf/mphi,2);
        double xfZ   = std::pow(mlf/mZ,2);
        std::complex<double> FHm = (xfphi*TwoLoopFunctions::TwoLoopFH(xfZ)-xfZ*TwoLoopFunctions::TwoLoopFH(xfphi))/(xfphi-xfZ);
        std::complex<double> FAm = (xfphi*TwoLoopFunctions::TwoLoopFA(xfZ)-xfZ*TwoLoopFunctions::TwoLoopFA(xfphi))/(xfphi-xfZ);
        return Yukawas::yff_phi(fe, l, lp, phi, ml, xi_L, VCKM, vev, cosab)*(real(Yukawas::yff_phi(lf, gi, gi, phi, mlf, xi_f, VCKM, vev, cosab)) * (Qf*TwoLoopFunctions::TwoLoopFH(std::pow(mlf/mphi,2))+(1.-4.*sw2)*QfZ/(16.*sw2*(1-sw2))*FHm)-I*imag(Yukawas::yff_phi(lf, gi, gi, phi, mlf, xi_f, VCKM, vev, cosab)) * (Qf*TwoLoopFunctions::TwoLoopFA(std::pow(mlf/mphi,2))+(1.-4.*sw2)*QfZ/(16.*sw2*(1-sw2))*FAm));
    }

      //2-loop bosonic contribution
      //AL
      std::complex<double> A_loop2bL(int f, int l, int lp, int phi, double ml, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab, double mW, double mZ)
      {
        double sw2 = 1-std::pow(mW/mZ,2);
        double tw2 = sw2/(1-sw2);
        std::complex<double> xWphi(std::pow(mW/mphi,2),0);
        std::complex<double> xWZ(std::pow(mW/mZ,2),0);
        std::complex<double> FHm = (xWphi*TwoLoopFunctions::TwoLoopFH(xWZ)-xWZ*TwoLoopFunctions::TwoLoopFH(xWphi))/(xWphi-xWZ);
        std::complex<double> FAm = (xWphi*TwoLoopFunctions::TwoLoopFA(xWZ)-xWZ*TwoLoopFunctions::TwoLoopFA(xWphi))/(xWphi-xWZ);
        std::complex<double> pH(5-tw2+(1-tw2)/(2*std::pow(mW/mphi,2)),0);
        std::complex<double> pA(7-3*tw2-(1-tw2)/(2*std::pow(mW/mphi,2)),0);
        std::complex<double> onehalf(0.5,0);
        std::complex<double> two(2,0);
        std::complex<double> three(3,0);
        std::complex<double> four(4,0);
        std::complex<double> twenty3(23,0);
        return  conj(Yukawas::yff_phi(f, l, lp, phi, ml, xi_L, VCKM, vev, cosab))*(three*TwoLoopFunctions::TwoLoopFH(xWphi)+(twenty3/four)*TwoLoopFunctions::TwoLoopFA(xWphi)+(three/four)*TwoLoopFunctions::TwoLoopGW(xWphi)+(onehalf)*std::pow(mphi/mW,2)*(TwoLoopFunctions::TwoLoopFH(xWphi)-TwoLoopFunctions::TwoLoopFA(xWphi))+((1-4*sw2)/(8*sw2))*(pH*FHm + pA*FAm + (three/two)*(TwoLoopFunctions::TwoLoopFA(xWphi)+TwoLoopFunctions::TwoLoopGW(xWphi))));
      }
      //AR
      std::complex<double> A_loop2bR(int f, int l, int lp, int phi, double ml, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab, double mW, double mZ)
      {
        double sw2 = 1-std::pow(mW/mZ,2);
        double tw2 = sw2/(1-sw2);
        std::complex<double> xWphi(std::pow(mW/mphi,2),0);
        std::complex<double> xWZ(std::pow(mW/mZ,2),0);
        std::complex<double> FHm = (xWphi*TwoLoopFunctions::TwoLoopFH(xWZ)-xWZ*TwoLoopFunctions::TwoLoopFH(xWphi))/(xWphi-xWZ);
        std::complex<double> FAm = (xWphi*TwoLoopFunctions::TwoLoopFA(xWZ)-xWZ*TwoLoopFunctions::TwoLoopFA(xWphi))/(xWphi-xWZ);
        std::complex<double> pH(5-tw2+(1-tw2)/(2*std::pow(mW/mphi,2)),0);
        std::complex<double> pA(7-3*tw2-(1-tw2)/(2*std::pow(mW/mphi,2)),0);
        std::complex<double> onehalf(0.5,0);
        std::complex<double> two(2,0);
        std::complex<double> three(3,0);
        std::complex<double> four(4,0);
        std::complex<double> twenty3(23,0);
        return  Yukawas::yff_phi(f, l, lp, phi, ml, xi_L, VCKM, vev, cosab)*(three*TwoLoopFunctions::TwoLoopFH(xWphi)+(twenty3/four)*TwoLoopFunctions::TwoLoopFA(xWphi)+(three/four)*TwoLoopFunctions::TwoLoopGW(xWphi)+(onehalf)*std::pow(mphi/mW,2)*(TwoLoopFunctions::TwoLoopFH(xWphi)-TwoLoopFunctions::TwoLoopFA(xWphi))+((1-4*sw2)/(8*sw2))*(pH*FHm + pA*FAm + (three/two)*(TwoLoopFunctions::TwoLoopFA(xWphi)+TwoLoopFunctions::TwoLoopGW(xWphi))));
      }
    }

    // Two Loop muon g-2 Contributions for gTHDM
    namespace TwoLoopContributions
    {
      // Source: 1607.06292, eqns (53,58)
      std::complex<double> gm2mu_loop2f(int fe, int lf, int l, int lp, int phi, double mmu, std::vector<double> mf, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd xi_f, Eigen::Matrix3cd VCKM, int Nc, std::vector<double> Qf, std::vector<double> gfv, double vev, double cosab, double mW, double mZ, double alph)
      { 
        // fe = 0,1,2 for electron,down,up families for external fermion
        // l,lf,lp = 0,1,2 are the generation numbers of incoming,loop,outgoing lepton
        // phi = 0,1,2,3 for h,H,A,H+
        // mf is array of loop fermion masses
        // mphi is array of Higgs boson masses
        // Qf is array of fermion electric charges
        // gfv is array of fermion Z-charges
        const int gi = 2; // Internal generation is the heaviest
        if ((phi == 0) or (phi == 1))
        {
          return (TwoLoopFunctions::TwoLoopfgammaphi(Nc, Qf[lf], alph, mmu, mf[lf], mphi, mW, mZ) + TwoLoopFunctions::TwoLoopfZbosonphi(Nc, Qf[lf], alph, mmu, mf[lf], mphi, mW, mZ, gfv[0], gfv[lf])) * vev / mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab) * vev / mf[lf] * Yukawas::yff_phi(lf, gi, gi, phi, mf[lf], xi_f, VCKM, vev, cosab);
        }
        else if (phi == 2)
        {
          return (TwoLoopFunctions::TwoLoopfgammaA(Nc, Qf[lf], alph, mmu, mf[lf], mphi, mW, mZ) + TwoLoopFunctions::TwoLoopfZbosonA(Nc, Qf[lf], alph, mmu, mf[lf], mphi, mW, mZ, gfv[0], gfv[lf])) * vev / mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab) * vev / mf[lf] * Yukawas::yff_phi(lf, gi, gi, phi, mf[lf], xi_f, VCKM, vev, cosab);
        }
        else if (phi == 3)
        {
          const double Qu = Qf[2], Qd = Qf[1];
          const std::complex<double> I(0,1);
          return TwoLoopFunctions::TwoLoopfC(lf, Nc, Qu, Qd, alph, mmu, mf, mphi, mW, mZ) * I * vev / mmu * Yukawas::yff_phi(fe, l, lp, 2, mmu, xi_L, VCKM, vev, cosab) * I * vev / mf[lf] * Yukawas::yff_phi(lf, gi, gi, 2, mf[lf], xi_f, VCKM, vev, cosab);
        }
      }

      // Source: 1502.04199, eqns (19-24)
      double gm2mu_barrzeephigammaf(int fe, int lf, int l, int lp, int phi, double mmu, double mf, double mphi, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd xi_f, Eigen::Matrix3cd VCKM, int Nc, double Qf, double vev, double cosab, double alph)
      {
        // fe = 0,1,2 for electron,down,up families for external fermion
        // l,lf,lp = 0,1,2 are the generation numbers of incoming,loop,outgoing lepton
        // phi = 0,1,2,3 for h,H,A,H+
        // mf is loop fermion mass
        // mphi is neutral scalar boson mass
        // Qf is loop fermion charge
        // Nc is loop fermion colour number
        const double x = std::pow(mf/mphi,2);
        const int gi = 2; // Internal generation is the heaviest
        double term1 = vev / mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab).real() * vev / mf * Yukawas::yff_phi(lf, gi, gi, phi, mf, xi_f, VCKM, vev, cosab).real() * TwoLoopFunctions::TwoLoopF1(x);
        double term2 = vev / mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab).imag() * vev / mf * Yukawas::yff_phi(lf, gi, gi, phi, mf, xi_f, VCKM, vev, cosab).imag() * TwoLoopFunctions::TwoLoopF4(x);
        return alph * Nc * std::pow(mmu * Qf / vev,2) / (4. * std::pow(M_PI,3)) * (term1 + term2);
      }

      double gm2mu_barrzeephigammaC(int fe, int l, int lp, int phi, double mmu, double mHp, double mphi, double couplingphiCC, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab, double alph)
      {
        // fe = 0,1,2 for electron,down,up families for external fermion
        // l,lp = 0,1,2 are the generation numbers of incoming,outgoing lepton
        // phi = 0,1,2,3 for h,H,A,H+
        // mphi is neutral scalar boson mass
        // couplingphiCC is the coupling between scalar phi and two H+
        const double x = std::pow(mHp/mphi,2);
        return alph * std::pow(mmu/mphi,2) / (8. * std::pow(M_PI,3)) * vev / mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab).real() * couplingphiCC * TwoLoopFunctions::TwoLoopF2(x);
      }
        
      double gm2mu_barrzeephigammaW(int fe, int l, int lp, int phi, double mmu, double mW, double mphi, double couplingphiWW, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab, double alph)
      {
        // fe = 0,1,2 for electron,down,up families for external fermion
        // l,lp = 0,1,2 are the generation numbers of incoming,outgoing lepton
        // phi = 0,1,2,3 for h,H,A,H+
        // mphi is neutral scalar boson mass
        // couplingphiWW is the coupling between scalar phi and two W+
        const double x = std::pow(mW/mphi,2);
        return alph * std::pow(mmu/vev,2) / (8. * std::pow(M_PI,3)) * vev / mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab).real() * couplingphiWW * TwoLoopFunctions::TwoLoopF3(x);
      }

      std::complex<double> gm2mu_barrzeeCHiggsWBosontb(int fe, int l, int lp, double mmu, std::vector<double> mf, double mHp, std::vector<double> Qf, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd xi_D, Eigen::Matrix3cd xi_U, Eigen::Matrix3cd VCKM, double vev, double cosab, double mW, double mZ, double alph)
      {
        // fe = 0,1,2 for electron,down,up families for external fermion
        // l,lp = 0,1,2 are the generation numbers of incoming,outgoing lepton
        // mf is the array of loop fermion masses
        // Qf is the array of loop fermion charges
        const double sw2 = 1 - std::pow(mW/mZ,2);
        const int phi = 2; // Use CP-odd Higgs boson
        const int fu = 2, fd = 1; // External fermions are both leptons
        const int gi = 2; // Internal generation is the heaviest
        const int Nc = 3; // Since internal fermions are top+bottom, number of colours is 3
        const double mt = mf[2], mb = mf[1];
        const double xtC = std::pow(mt/mHp,2);
        const double xbC = std::pow(mb/mHp,2);
        const double xtW = std::pow(mt/mW,2);
        const double xbW = std::pow(mb/mW,2);
        const double Qu = Qf[2], Qd = Qf[1];
        // Top contributions
        double term1 = std::pow(mt,2)*Qu * (std::conj(vev/mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab)) * vev/mt * Yukawas::yff_phi(fu, gi, gi, phi, mt, xi_U, VCKM, vev, cosab)).real() * (TwoLoopFunctions::TwoLoopG(xtC,xbC,2)+TwoLoopFunctions::TwoLoopG(xtC,xbC,3)-TwoLoopFunctions::TwoLoopG(xtW,xbW,2)-TwoLoopFunctions::TwoLoopG(xtW,xbW,3));
        double term2 = std::pow(mt,2)*Qd * (std::conj(vev/mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab)) * vev/mt * Yukawas::yff_phi(fu, gi, gi, phi, mt, xi_U, VCKM, vev, cosab)).real() * (TwoLoopFunctions::TwoLoopG(xtC,xbC,1)-TwoLoopFunctions::TwoLoopG(xtC,xbC,3)-TwoLoopFunctions::TwoLoopG(xtW,xbW,1)+TwoLoopFunctions::TwoLoopG(xtW,xbW,3));
        // Bottom contributions
        double term3 = std::pow(mb,2)*Qu * (std::conj(vev/mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab)) * vev/mb * Yukawas::yff_phi(fd, gi, gi, phi, mb, xi_D, VCKM, vev, cosab)).real() * (TwoLoopFunctions::TwoLoopG(xtC,xbC,2)-TwoLoopFunctions::TwoLoopG(xtC,xbC,3)-TwoLoopFunctions::TwoLoopG(xtW,xbW,2)+TwoLoopFunctions::TwoLoopG(xtW,xbW,3));
        double term4 = std::pow(mb,2)*Qd * (std::conj(vev/mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab)) * vev/mb * Yukawas::yff_phi(fd, gi, gi, phi, mb, xi_D, VCKM, vev, cosab)).real() * (TwoLoopFunctions::TwoLoopG(xtC,xbC,1)-2.*TwoLoopFunctions::TwoLoopG(xtC,xbC,2)+TwoLoopFunctions::TwoLoopG(xtC,xbC,3)-TwoLoopFunctions::TwoLoopG(xtW,xbW,1)+2.*TwoLoopFunctions::TwoLoopG(xtW,xbW,2)-TwoLoopFunctions::TwoLoopG(xtW,xbW,3));
        return alph*Nc*norm(VCKM(2,1))*std::pow(mmu/vev,2) / (32.*std::pow(M_PI,3)*sw2) / (std::pow(mHp,2)-std::pow(mW,2)) * (term1 + term2 + term3 + term4);
      }

      double gm2mu_barrzeeCHiggsWBosonC(int fe, int l, int lp, int phi, double mmu, double mHp, double mphi, double couplingphiCC, complex<double> couplingphiCW, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab, double mW, double mZ, double alph)
      {
        // fe = 0,1,2 for electron,down,up families for external fermion
        // l,lp = 0,1,2 are the generation numbers of incoming,outgoing lepton
        // phi = 0,1,2,3 for h,H,A,H+
        // mphi is neutral scalar boson mass
        // couplingphiCC is the coupling between scalar phi and two H+
        // couplingphiCW is the coupling between scalar phi, H+, and W+
        const double sw2 = 1 - std::pow(mW/mZ,2);
        const double xSC = std::pow(mphi/mHp, 2);
        const double xSW = std::pow(mphi/mW,  2);
        const double xCW = std::pow(mHp/mW,   2);
        double term1 = (TwoLoopFunctions::TwoLoopG(1.,xSC,3)-TwoLoopFunctions::TwoLoopG(xCW,xSW,3));
        double term2 = (TwoLoopFunctions::TwoLoopG(1.,xSC,2)-TwoLoopFunctions::TwoLoopG(xCW,xSW,2));
        return alph*std::pow(mmu,2) / (64.*std::pow(M_PI,3)*sw2) / (std::pow(mHp,2)-std::pow(mW,2)) * std::real(std::conj(vev / mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab)) * couplingphiCC * couplingphiCW) * (term1-term2);
      }

      double gm2mu_barrzeeCHiggsWBosonW(int fe, int l, int lp, int phi, double mmu, double mHp, double mphi, double couplingphiWW, complex<double> couplingphiCW, Eigen::Matrix3cd xi_L, Eigen::Matrix3cd VCKM, double vev, double cosab, double mW, double mZ, double alph)
      {
        // fe = 0,1,2 for electron,down,up families for external fermion
        // l,lp = 0,1,2 are the generation numbers of incoming,outgoing lepton
        // phi = 0,1,2,3 for h,H,A,H+
        // mphi is neutral scalar boson mass
        // couplingphiWW is the coupling between scalar phi and two W+
        // couplingphiCW is the coupling between scalar phi, H+, and W+
        const double sw2 = 1 - std::pow(mW/mZ,2);
        const double xSC = std::pow(mphi/mHp,2);
        const double xSW = std::pow(mphi/mW, 2);
        const double xWC = std::pow(mW/mHp,  2);
        double term1 = (std::pow(mHp,2)-3.*std::pow(mW,2)-std::pow(mphi,2)) * (TwoLoopFunctions::TwoLoopG(xWC,xSC,2)-TwoLoopFunctions::TwoLoopG(1.,xSW,2));
        double term2 = (std::pow(mHp,2)+   std::pow(mW,2)-std::pow(mphi,2)) * (TwoLoopFunctions::TwoLoopG(xWC,xSC,3)-TwoLoopFunctions::TwoLoopG(1.,xSW,3));
        return alph*std::pow(mmu/vev,2) / (64.*std::pow(M_PI,3)*sw2) / (std::pow(mHp,2)-std::pow(mW,2)) * std::real(std::conj(vev / mmu * Yukawas::yff_phi(fe, l, lp, phi, mmu, xi_L, VCKM, vev, cosab)) * couplingphiWW * couplingphiCW) * (term1-term2);
      }

    }

    // Loop functions for LFV diagrams
    namespace LoopFunctions
    {
      double G1(const double x)
      {
        if(x == 0)
          return -7./12.;
        if(x == 1)
          return -5./12.;
        else
          return (-7. + 33.*x - 57.*x*x + 31.*x*x*x + 6.*x*x*(1. - 3*x)*std::log(x))/(12.*std::pow(1.-x,4));
      }

      double G1(const double a, const double b, const double c)
      {
        if(b == c and b != 0)
          return G1(a/b)/b;
        else
          return 0; // TODO: 2C12 + 2C22 - C1 or 2C12 + C11 - C2
      }

      double MFVV(const double a, const double b)
      {
        if(a == b)
          return 1. / (3. * b);
        else if(a == 0)
          return 5. / (9. * b);
        else
          return (6.*a*a*(a-3.*b)*std::log(a/b) - (a-b)*(5.*a*a - 22.*a*b + 5.*b*b))/(9.*std::pow(a-b,4));
      }

      double B1(const double a, const double b, const double Q)
      {
        if(a == b)
          return 0.5 * std::log(b / std::pow(Q,2));
        else if(a == 0)
          return -0.25 + 0.5*std::log(b / std::pow(Q,2));
        else
          return -0.5 + 0.5*std::log(b / std::pow(Q,2)) - (a*a - b*b + 2.*a*a*std::log(b/a)) / (4.*std::pow(a-b,2));
      }

      double B0(const double a, const double b, const double Q)
      {
        // TODO: behaviour when a = 0 and b = 0 undefined
        if(a == 0 and b == 0)
          return 0;
        else if(a == b)
          return -std::log(b / std::pow(Q,2));
        else if(a == 0)
          return 1. - std::log(b / std::pow(Q,2));
        else if(b == 0)
          return 1. - std::log(a) - std::log(1./std::pow(Q,2));
        else
          return 1. - std::log(b / std::pow(Q,2)) + 1./(b-a) * a * std::log(a/b);
      }

      double C0(const double a, const double b, const double c)
      {
        // TODO: behaviour when two paramers are 0 undefined, set it to zero
        if(a == 0 and b == 0 and c == 0)
          return 0;
        if(a == 0 and b == 0) 
          return 0;
        else if(a == 0 and c == 0) 
          return 0;
        else if(b == 0 and c == 0)
          return 0;
        else if(c == 0)
          return C0(a,c,b);
        else if(a == b and b == c) 
          return - 1./(2*c);
        else if(a == b)
          return (-b + c- c*std::log(c/b)) / std::pow(b-c,2);
        else if(a == c and b != 0)
          return C0(a,c,b);
        else if(a == c and b == 0)
          return -1./c;
        else if(b == c and a != 0)
          return (a - c + a*std::log(c/a)) / std::pow(a-c,2);
        else if(b == c and a == 0)
          return -1./c;
        else if(a == 0)
          return (-std::log(b) + std::log(c)) / (b-c);
        else if(b == 0)
          return std::log(c/a)/(a-c);
        else
          return -1. / (a-b)*(a-c)*(b-c)*( b*(c-a)*std::log(b/a) + c*(a-b)*std::log(c/a));
      }

      double C00(const double a, const double b, const double c, const double Q)
      {
        // TODO: behaviour when all three parameters are zero is undefined, set it to zero
        if(a == 0 and b == 0 and c == 0)
          return 0;
        else if(b == 0 and c == 0)
          return 0.125*(3. - 2.*std::log(a/std::pow(Q,2)));
        else if(a == 0 and b == 0)
          return 0.125*(3. - 2.*std::log(c) - 2.*std::log(1./std::pow(Q,2)));
        else if(c == 0)
          return C00(a,c,b,Q);
        else if(a == b and b == c)
          return -0.25*std::log(c/std::pow(Q,2));
        else if(a == b)
          return - (2.*c*c*std::log(c/b) + (b-c)*(-b + 3.*c + 2.*(b-c)*std::log(b/std::pow(Q,2))))/(8.*std::pow(b-c,2));
        else if(a == c and b != 0)
          return C00(a,c,b,Q);
        else if(a == c and b == 0)
          return 0.125*(1. - 2.*std::log(c/std::pow(Q,2)));
        else if(b == c and a != 0)
          return (2.*(2.*a-c)*c*std::log(c/a)-(a-c)*(-3.*a+c+2.*(a-c)*std::log(a/std::pow(Q,2))))/(8.*std::pow(a-c,2));
        else if(b == c and a == 0)
          return 0.125*(1. - 2.*std::log(c) - 2.*std::log(1./std::pow(Q,2)));
        else if(a == 0)
          return -(2.*b*std::log(b) - 2.*c*std::log(c) + (b-c)*(-3.+2.*std::log(1./std::pow(Q,2))))/(8.*(b-c));
        else if(b == 0)
          return (2.*c*std::log(c/a) - (a-c)*(-3. + 2.*std::log(a/std::pow(Q,2))))/(8.*(a-c));
        else
          return 1. / (8.*(a-b)*(a-c)*(b-c)) * ( (c-a)*((a-b)*(2.*std::log(a/std::pow(Q,2))-3.)*(b-c) - 2.*b*b*std::log(b/a)) + 2.*c*c*(b-a)*std::log(c/a));
      }

      // Finite combination of loop functions that appears in VZw10
      double B02C00C0(const double a, const double b, const double c, const double Q)
      {
        if(a == 0 and b == 0)
          return 0.25*(1.0 - 2.0*std::log(c) - 2.0*std::log(1 / std::pow(Q,2)));
        else
          return B0(a,b,Q) - 2*C00(a,b,c,Q) + C0(a,b,c)*c;
      }

      double D0(const double a, const double b, const double c, const double d)
      {
        //TODO: behaviour when two or more parameters are zero is undefined, set it to zero
        if((!a and !b) or (!b and !c) or (!b and !d) or (!c and !d))
          return 0;
        else if(c == 0)
          return D0(a,c,b,d);
        else if(d == 0)
          return D0(a,d,c,b);
        else if(a == b and b == c and c == d)
          return 1. / (6.*d*d);
        else if(a == b and b == c)
          return D0(a,d,c,d);
        else if(a == b and b == d)
          return D0(a,c,b,d);
        else if(a == c and c == d and b == 0)
          return 1. / (2.*c*c);
        else if(a == c and c == d and b != 0)
          return (-b*b + c*c + 2.*b*c*std::log(b/c)) / (2.*c*std::pow(c-b,3));
        else if(b == c and c == d and a == 0)
          return 1. / (2.*d*d);
        else if(b == c and c == d and a != 0)
          return (a*a - d*d + 2.*a*d*std::log(d/a)) / (2.*d*std::pow(a-d,3));
        else if(a == d and b == c)
          return (-2*c + 2*d + (c+d)*std::log(c/d)) / std::pow(c-d,3);
        else if(a == d and b == 0)
          return (c - d -d*std::log(c/d)) / (std::pow(c-d,2)*d);
        else if(a == d)
          return 1./ ((b-d)*(d-c))-(b*std::log(b/d))/((b-c)*std::pow(b-d,2))+(c*std::log(c/d))/((b-c)*std::pow(c-d,2));
        else if(a == c)
          return D0(a,b,d,c);
        else if(a == b)
          return D0(a,d,c,b);
        else if(b == c)
          return D0(a,d,c,b);
        else if(b == d)
          return D0(a,c,b,d);
        else if(c == d and b == 0)
          return (a - d + d*std::log(d/a)) / (d*std::pow(a-d,2));
        else if(c == d and a == 0)
          return (b - d + d*std::log(d/b)) / (d*std::pow(b-d,2));
        else if(c == d)
          return (b*std::pow(a-d,2)*std::log(b/a) - (a-b)*( (a-d)*(b-d) + (a*b-d*d)*std::log(d/a) )) / ((a-b)*std::pow(a-d,2)*std::pow(b-d,2));
        else if(b == 0)
          return std::log(c/a)/((a-c)*(c-d)) + std::log(d/a)/((a-d)*(d-c));
        else if(a == 0)
          return ((d-c)*std::log(b) + (b-d)*std::log(c) + (c-b)*std::log(d))/((b-c)*(b-d)*(c-d));
        else
          return -(b*std::log(b/a)/((b-a)*(b-c)*(b-d)) + c*std::log(c/a)/((c-a)*(c-b)*(c-d)) + d*std::log(d/a)/((d-a)*(d-b)*(d-c)));
      }

      double D27(const double a, const double b, const double c, const double d)
      {
        //TODO: behaviour when three or more parameters are zero is undefined, set it to zero
        if((!a and !b and !c) or (!a and !b and !d) or (!a and !c and !d) or (!b and !c and !d))
          return 0; 
        if(a == b and b == c and c == d)
           return -1./(12.*d);
        if(a == d and c == d and b == 0)
           return -1. / (8.*d);
        if(a == d and c == d)
           return (3.*b*b - 4.*b*d + d*d - 2.*b*b*std::log(b/d))/(8.*std::pow(b-d,3));
        if(b == c and c == d)
           return D27(b,a,c,d);
        if(a == b and b == c)
           return D27(a,d,c,b);
        if(a == b and b == d)
           return D27(a,c,b,d);
        if(a == b and c == d and b == 0)
          return -1./(4.*d);
        if(a == b and c == d and d == 0)
          return -1./(4.*b);
        if(a == b and c == d) 
          return (-b*b + d*d -2.*b*d*std::log(d/b)) / (4.*std::pow(b-d,3));
        if(a == c and b == d)
          return D27(a,c,b,d);
        if(a == d and b == c)
          return D27(a,b,d,c);
        if(a == b and b == 0)
          return std::log(d/c)/(4.*(c-d));
        if(a == b and c == 0)
          return - (b -d +d*std::log(d/b))/(4.*std::pow(b-d,2));
        if(a == b and d == 0)
          return D27(a,b,d,c);
        if(a == b)
          return 0.25*(-c*c*std::log(c/b)/(std::pow(b-c,2)*(c-d)) + (b*(d-b)/(b-c) + d*d*std::log(d/b)/(c-d))/std::pow(b-d,2));
        if(a == c)
          return D27(a,c,b,d);
        if(a == d)
          return D27(a,d,c,b);
        if(b == c and a == 0)
          return (-c+d+d*std::log(c/d))/(4.*std::pow(c-d,2));
        if(b == c and c == 0)
          return std::log(d/a)/(4.*(a-d));
        if(b == c and d == 0)
          return (a-c+a*std::log(c/a))/(4.*std::pow(a-c,2));
        if(b == c)
          return (c*(a-d)*(a*(c-2.*d)+c*d)*std::log(c/a)+(a-c)*(c*(a-d)*(c-d)+(a-c)*d*d*std::log(d/a)))/(4.*std::pow(a-c,2)*(a-d)*std::pow(c-d,2));
        if(b == d)
          return D27(a,b,d,c);
        if(c == d)
          return D27(a,c,d,b);
        if(a == 0)
          return (b*(-c+d)*std::log(b)+c*(b-d)*std::log(c)+(-b+c)*d*std::log(d))/(4.*(b-c)*(b-d)*(c-d));
        if(b == 0)
          return ((c*std::log(c/a))/((a - c)*(c - d)) + (d*std::log(d/a))/((a - d)*(-c + d)))/4.;
        if(c == 0)
          return D27(a,c,b,d);
        if(d == 0)
          return D27(a,d,c,b);
        else
          return -0.25*(b*b*std::log(b/a)/((b-a)*(b-c)*(b-d)) + c*c*std::log(c/a)/((c-a)*(c-b)*(c-d)) + d*d*std::log(d/a)/((d-a)*(d-b)*(d-c)));
      }

      double IC0D0(const double a, const double b, const double c, const double d)
      {
        return C0(a,b,c) + d*D0(a,b,c,d);
      }
    }

    // Loop function for RK
    namespace LoopFunctions
    {
      double E(const double x, const double y)
      {
        if(x == 0 or y == 0)
          return 0.0;
        if(x == y)
          return (x*(-4.0 + 15.0*x - 12.0*std::pow(x,2) + std::pow(x,3) + 6.0*std::pow(x,2)*std::log(x)))/ (4.*std::pow(-1.0 + x,3));
        return x*y*(-3.0/(4.0*(1.0-x)*(1.0 - y)) + ((0.25 - 3.0/(4.0*std::pow(-1.0 + x,2)) - 3.0/(2.0*(-1.0 + x)))*std::log(x))/(x - y) + ((0.25 - 3.0/(4.0*std::pow(-1.0 + y,2)) - 3.0/(2.0*(-1 + y)))*std::log(y))/(-x + y));
      }

    }

    // Vertices for LFV diagrams
    namespace Vertices
    {
      // Fermion-std::vector vertices
      std::complex<double> VpL(int i, int j, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U)
      {
        double g2 = sminputs.mW * std::sqrt( 8. * sminputs.GF / std::sqrt(2));
        return  -1. / std::sqrt(2) * g2 * U(i,j);
      
      }

      double EL(int i,int j, Gambit::SMInputs sminputs)
      {
        if(i != j)  return 0; 

        double e = std::sqrt(4. * M_PI / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double g2 = sminputs.mW * std::sqrt( 8. * sminputs.GF / std::sqrt(2));
        double cw = sminputs.mW / sminputs.mZ;
        double sw = std::sqrt(1. - cw*cw);
        return 0.5 * (-g1*sw + g2*cw);
        
      }
 
      double ER(int i, int j, Gambit::SMInputs sminputs)
      {
        if(i != j) return 0;
 
        double e = std::sqrt(4. * M_PI / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double cw = sminputs.mW / sminputs.mZ;
        double sw = std::sqrt(1. - cw*cw);
        return - g1*sw; 
      }

      std::complex<double> VL(int i, int j, Gambit::SMInputs sminputs)
      {
        double e = std::sqrt(4. * M_PI / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double g2 = sminputs.mW * std::sqrt( 8. * sminputs.GF / std::sqrt(2));
        double cw = sminputs.mW / sminputs.mZ;
        double sw = std::sqrt(1. - cw*cw);

        if(i == j)
          return -0.5*(g1*sw + g2*cw);
        else
          return 0.;
      }

      std::complex<double> VR(int i, int j, Gambit::SMInputs sminputs)
      {
        double e = std::sqrt(4. * M_PI / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double g2 = sminputs.mW * std::sqrt( 8. * sminputs.GF / std::sqrt(2));
        double cw = sminputs.mW / sminputs.mZ;
        double sw = std::sqrt(1. - cw*cw);

        if(i == j)
          return 0.5*(g1*sw + g2*cw);
        else
          return 0.;
      }

      std::complex<double> DL(int i, int j, Gambit::SMInputs sminputs)
      {
        double e = std::sqrt(4. * M_PI / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double g2 = sminputs.mW * std::sqrt( 8. * sminputs.GF / std::sqrt(2));
        double cw = sminputs.mW / sminputs.mZ;
        double sw = std::sqrt(1. - cw*cw);

        if(i == j)
          return 1./6. * (3.*g2*cw + g1*sw);
        else
          return 0;
      }

      std::complex<double> DR(int i, int j, Gambit::SMInputs sminputs)
      {
        double e = std::sqrt(4. * M_PI / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double cw = sminputs.mW / sminputs.mZ;
        double sw = std::sqrt(1. - cw*cw);

        if(i == j)
          return -1./3.*g1*sw;
        else
          return 0.;
      }

      std::complex<double> UL(int i, int j, Gambit::SMInputs sminputs)
      {
        double e = std::sqrt(4. * M_PI / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double g2 = sminputs.mW * std::sqrt( 8. * sminputs.GF / std::sqrt(2));
        double cw = sminputs.mW / sminputs.mZ;
        double sw = std::sqrt(1. - cw*cw);

        if(i == j)
          return -1./6. * (3.*g2*cw - g1*sw);
        else
          return 0;
      }

      std::complex<double> UR(int i, int j, Gambit::SMInputs sminputs)
      {
        double e = std::sqrt(4. * M_PI / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double cw = sminputs.mW / sminputs.mZ;
        double sw = std::sqrt(1. - cw*cw);

        if(i == j)
          return 2./3.*g1*sw;
        else
          return 0.;
      }

      std::complex<double> VuL(int i, int j, Gambit::SMInputs sminputs)
      {
         double g2 = sminputs.mW * std::sqrt( 8. * sminputs.GF / std::sqrt(2));
         Eigen::Matrix3cd VCKM;
         double lambda = sminputs.CKM.lambda, A = sminputs.CKM.A;
         double rhobar = sminputs.CKM.rhobar, etabar = sminputs.CKM.etabar;
         std::complex<double> I(0,1);

         std::complex<double> Vub = std::real(rhobar + I*etabar)*std::sqrt(1.-A*A*std::pow(lambda,4))/(std::sqrt(1.-std::pow(lambda,2))*(1.- A*A*std::pow(lambda,4)*(rhobar+I*etabar)));
         double rho = std::real(Vub);
         double eta = imag(Vub);

         VCKM << 1. - 0.5*std::pow(lambda,2), lambda, A*std::pow(lambda,3)*(rho - I*eta),
                 -lambda, 1. - 0.5*std::pow(lambda,2), A*std::pow(lambda,2),
                 A*std::pow(lambda,3)*(1. - eta - I*eta), -A*std::pow(lambda,2), 1;

         return -1./std::sqrt(2) * g2 * VCKM(i,j);
      }

      // Vector vertices
      double Fw(Gambit::SMInputs sminputs)
      {
        return std::sqrt(4.* M_PI/ sminputs.alphainv);
      }

      double Zww(Gambit::SMInputs sminputs)
      {
        double g2 = sminputs.mW * std::sqrt( 8. * sminputs.GF / std::sqrt(2));
        return -g2 * sminputs.mW / sminputs.mZ;
      }

      // Scalar vertices
      double HL(int i, int j, Gambit::SMInputs sminputs)
      {
        double vev = 1. / std::sqrt(std::sqrt(2.)*sminputs.GF);
        
        if(i == 0 and j == 0)
          return -1. / vev * sminputs.mE;
        if(i == 1 and j == 1)
          return -1. / vev * sminputs.mMu;
        if(i == 2 and j == 2)
          return -1. / vev * sminputs.mTau;
        else 
          return 0;
      }

      double HR(int i, int j, Gambit::SMInputs sminputs)
      {
        return HL(i, j , sminputs);
      } 

      double HdL(int i, int j, Gambit::SMInputs sminputs)
      {
        double vev = 1. / std::sqrt(std::sqrt(2.)*sminputs.GF);

        if(i == 0 and j == 0)
          return -1. / vev * sminputs.mD;
        else if(i == 1 and j == 1)
          return -1. / vev * sminputs.mS;
        else if(i == 2 and j == 2)
          return -1. / vev * sminputs.mBmB;
        else
          return 0;
      }

      double HdR(int i, int j, Gambit::SMInputs sminputs)
      {
        return HdL(i, j, sminputs);
      }

      double HuL(int i, int j, Gambit::SMInputs sminputs)
      {
        double vev = 1. / std::sqrt(std::sqrt(2.)*sminputs.GF);

        if(i == 0 and j == 0)
          return -1. / vev * sminputs.mU;
        else if(i == 1 and j == 1)
          return -1. / vev * sminputs.mCmC;
        else if(i == 2 and j == 2)
          return -1. / vev * sminputs.mT;
        else
          return 0;
      }

      double HuR(int i, int j, Gambit::SMInputs sminputs)
      {
        return HuL(i, j, sminputs);
      }

    }

    // Penguin contributions
    namespace Penguins
    {
      // Fotonic penguins

      std::complex<double> A1R(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        std::complex<double> a1r = {0,0};

        for(int a=0; a<6; a++)
        {
          a1r += Vertices::Fw(sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(beta,a,sminputs,U)) * LoopFunctions::MFVV(std::pow(mnu[a],2), std::pow(sminputs.mW,2));
        }

        return a1r;
      }

      std::complex<double> A2L(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
         std::complex<double> a2l = {0,0};
         double mW = sminputs.mW;

         for(int a=0; a<6; a++)
           a2l += -2. * Vertices::Fw(sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(beta,a,sminputs,U)) * LoopFunctions::G1(std::pow(mnu[a],2), mW*mW, mW*mW) * ml[beta];

         return a2l;
      }

      std::complex<double> A2R(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
         std::complex<double> a2r = {0,0};
         double mW = sminputs.mW;
         for(int a=0; a<6; a++)
          a2r += -2. * Vertices::Fw(sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(beta,a,sminputs,U)) * LoopFunctions::G1(std::pow(mnu[a],2), mW*mW, mW*mW) * ml[alpha];

         return a2r;
      }

      // Z penguins
      std::complex<double> VZw2w4LL(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        std::complex<double> vzll = {0,0};
 
        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
          {
            // Use MZ for the renormalization scale Q
            if(beta == c)
              vzll += Vertices::EL(beta,c, sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(std::pow(mnu[a],2),std::pow(sminputs.mW,2),sminputs.mZ))* std::pow(ml[alpha],2) / (std::pow(ml[alpha],2) - std::pow(ml[c],2));
            if(alpha == c) 
              vzll += Vertices::EL(alpha,c, sminputs) * Vertices::VpL(beta,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(std::pow(mnu[a],2),std::pow(sminputs.mW,2),sminputs.mZ))* std::pow(ml[beta],2) / (std::pow(ml[beta],2) - std::pow(ml[c],2));
         }

         return vzll;
      }

      std::complex<double> VZw2w4LR(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return VZw2w4LL(alpha,beta,sminputs,U,ml,mnu);
      }
    
      std::complex<double> VZw2w4RR(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        std::complex<double> vzrr = {0,0};
 
        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
          {
            if(beta == c)
              vzrr += Vertices::ER(beta,c,sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(std::pow(mnu[a],2),std::pow(sminputs.mW,2),sminputs.mZ))* ml[c]*ml[alpha] / (std::pow(ml[alpha],2) - std::pow(ml[c],2));
            if(alpha == c)
              vzrr += Vertices::ER(alpha,c, sminputs) * Vertices::VpL(beta,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(std::pow(mnu[a],2),std::pow(sminputs.mW,2),sminputs.mZ))* ml[c]*ml[beta] / (std::pow(ml[beta],2) - std::pow(ml[c],2));
         }

         return vzrr;
      }

      std::complex<double> VZw2w4RL(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return VZw2w4RR(alpha, beta, sminputs, U, ml, mnu); 
      }

      std::complex<double> VZw8LL(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        std::complex<double> vzll = {0,0};
        double mW = sminputs.mW;

        // Use MZ as the renormalization scale Q
	for(int a=0; a<6; a++)
          vzll += Vertices::Zww(sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(beta,a,sminputs,U)) * (1. - 2.*(LoopFunctions::B0(mW*mW,mW*mW,sminputs.mZ) + 2.*LoopFunctions::C00(std::pow(mnu[a],2),mW*mW,mW*mW,sminputs.mZ) + LoopFunctions::C0(std::pow(mnu[a],2),mW*mW,mW*mW)*std::pow(mnu[a],2)));

        return vzll;
      }
    
      std::complex<double> VZw8LR(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        return VZw8LL(alpha, beta, sminputs, U, mnu);
      }

      std::complex<double> VZw10LL(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        std::complex<double> vzll = {0,0};
        double mW = sminputs.mW;
 
        // Use MZ as the renormalization scale Q
        for(int b=0; b<6; b++)
        {
          // Use different loop function in case that mnu[b] 0
          if(mnu[b])
            vzll += - Vertices::VpL(alpha,b,sminputs,U) * conj(Vertices::VpL(beta,b,sminputs,U)) * (2.* Vertices::VR(b,b,sminputs) * LoopFunctions::C0(std::pow(mnu[b],2),std::pow(mnu[b],2),mW*mW) * mnu[b] * mnu[b] + Vertices::VL(b,b,sminputs) * (1. - 2.*(LoopFunctions::B0(std::pow(mnu[b],2),std::pow(mnu[b],2),sminputs.mZ) - 2.*LoopFunctions::C00(std::pow(mnu[b],2),std::pow(mnu[b],2),mW*mW,sminputs.mZ) + LoopFunctions::C0(std::pow(mnu[b],2),std::pow(mnu[b],2),mW*mW)*mW*mW)));
          else
            vzll += - Vertices::VpL(alpha,b,sminputs,U) * conj(Vertices::VpL(beta,b,sminputs,U)) * Vertices::VL(b,b,sminputs) * (1. - 2.*(LoopFunctions::B02C00C0(std::pow(mnu[b],2),std::pow(mnu[b],2),mW*mW,sminputs.mZ)));
        }

        return vzll;
      }

      std::complex<double> VZw10LR(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        return VZw10LL(alpha, beta, sminputs, U, mnu);
      }

      // Sum over Z penguins
      std::complex<double> VZsumLL(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
       return 1. / (16.*std::pow(M_PI,2)) * (VZw2w4LL(alpha, beta, sminputs, U, ml, mnu) + VZw8LL(alpha, beta, sminputs, U, mnu) + VZw10LL(alpha, beta, sminputs, U, mnu));
      }

      std::complex<double> VZsumLR(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return 1. / (16.*std::pow(M_PI,2)) * (VZw2w4LR(alpha, beta, sminputs, U, ml, mnu) + VZw8LR(alpha, beta, sminputs, U, mnu) + VZw10LR(alpha, beta, sminputs, U, mnu));
      }

      std::complex<double> VZsumRL(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return 1. / (16.*std::pow(M_PI,2)) * (VZw2w4RL(alpha, beta, sminputs, U, ml, mnu));
      }

      std::complex<double> VZsumRR(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return 1. / (16.*std::pow(M_PI,2)) * (VZw2w4RR(alpha, beta, sminputs, U, ml, mnu));
      }

      // Scalar penguins
      std::complex<double> Shw2w4LL(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        std::complex<double> shll = {0,0};
        double mW = sminputs.mW;

        // Use mZ for the renormalisation scale Q
        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
          {
            if(beta == c)
              shll += - (Vertices::HL(beta,c,sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(std::pow(mnu[a],2),mW*mW, sminputs.mZ)) * std::pow(ml[alpha],2))/(std::pow(ml[alpha],2) - std::pow(ml[c],2));
            if(alpha == c)
              shll += - (Vertices::HL(alpha,c,sminputs) * Vertices::VpL(beta,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(std::pow(mnu[a],2),mW*mW, sminputs.mZ)) * std::pow(ml[beta],2))/(std::pow(ml[beta],2) - std::pow(ml[c],2));
          }

        return shll;
      }

      std::complex<double> Shw2w4LR(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Shw2w4LL(alpha, beta, sminputs, U, ml, mnu);
      }

      std::complex<double> Shw2w4RR(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        std::complex<double> shrr = {0,0};
        double mW = sminputs.mW;

        // Use mZ for the renormalisation scale Q
        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
          {
            if(beta == c)
              shrr += - (Vertices::HR(beta,c,sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(std::pow(mnu[a],2),mW*mW, sminputs.mZ)) * ml[c]*ml[alpha])/(std::pow(ml[alpha],2) - std::pow(ml[c],2));
            if(alpha == c)
              shrr += - (Vertices::HR(alpha,c,sminputs) * Vertices::VpL(beta,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(std::pow(mnu[a],2),mW*mW, sminputs.mZ)) * ml[c]*ml[beta])/(std::pow(ml[beta],2) - std::pow(ml[c],2));
          }

        return shrr;
      }

      std::complex<double> Shw2w4RL(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Shw2w4RR(alpha, beta, sminputs, U, ml, mnu);
      }

      // Sum over scalar penguins
      std::complex<double> ShsumLL(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return 1. / (16.*std::pow(M_PI,2)) * Shw2w4LL(alpha, beta, sminputs, U, ml, mnu);
      }    

      std::complex<double> ShsumLR(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return 1. / (16.*std::pow(M_PI,2)) * Shw2w4LR(alpha, beta, sminputs, U, ml, mnu);
      }    

      std::complex<double> ShsumRL(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return 1. / (16.*std::pow(M_PI,2)) * Shw2w4RL(alpha, beta, sminputs, U, ml, mnu);
      }    

      std::complex<double> ShsumRR(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return 1. / (16.*std::pow(M_PI,2)) * Shw2w4RR(alpha, beta, sminputs, U, ml, mnu);
      }    

    }

    // Box contributions
    namespace Boxes
    {
      std::complex<double> Vw4lLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        std::complex<double> vll = {0,0};
        double mW = sminputs.mW;

        for(int a=0; a<6; a++)
          for(int c=0; c<6; c++)
            vll += -4. * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(beta,a,sminputs,U)) * Vertices::VpL(gamma,c,sminputs,U) * conj(Vertices::VpL(delta,c,sminputs,U)) * (LoopFunctions::IC0D0(std::pow(mnu[c],2),mW*mW, mW*mW, std::pow(mnu[a],2)) - 3. * LoopFunctions::D27(std::pow(mnu[a],2),std::pow(mnu[c],2),mW*mW,mW*mW));

        return vll;
      }

      std::complex<double> Vw8lLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        std::complex<double> vll = {0,0};
        double mW = sminputs.mW;

        for(int a=0; a<6; a++)
          for(int c=0; c<6; c++)
            vll += -2. * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(delta,c,sminputs,U)) * Vertices::VpL(gamma,a,sminputs,U) * conj(Vertices::VpL(beta,c,sminputs,U)) * mnu[a] * mnu[c] * LoopFunctions::D0(std::pow(mnu[a],2),std::pow(mnu[c],2),mW*mW,mW*mW);

        return vll;
      }

      std::complex<double> Vw4lpLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        return Vw4lLL(alpha, delta, gamma, beta, sminputs, U, mnu);
      }

      std::complex<double> Vw8lpLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        return Vw8lLL(alpha, delta, gamma, beta, sminputs, U, mnu);
      }

      std::complex<double> Vw4dLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        std::complex<double> vll = {0,0};
        double mW = sminputs.mW;
        std::vector<double> mu = {sminputs.mU, sminputs.mCmC, sminputs.mT};

        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
            vll += -4.*Vertices::VpL(alpha,a,sminputs,U)*conj(Vertices::VpL(beta,a,sminputs,U))*Vertices::VuL(gamma,c,sminputs)*conj(Vertices::VuL(delta,c,sminputs))*(LoopFunctions::IC0D0(std::pow(mu[c],2),mW*mW, mW*mW, std::pow(mnu[a],2)) - 3.*LoopFunctions::D27(std::pow(mnu[a],2),std::pow(mu[c],2),mW*mW,mW*mW));

        return vll;
      }

      std::complex<double> Vw4uLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        std::complex<double> vll = {0,0};
        double mW = sminputs.mW;
        std::vector<double> md = {sminputs.mD, sminputs.mS, sminputs.mBmB};

        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
            vll += 16.*Vertices::VpL(alpha,a,sminputs,U)*conj(Vertices::VpL(beta,a,sminputs,U))*Vertices::VuL(delta,c,sminputs)*conj(Vertices::VuL(gamma,c,sminputs))*LoopFunctions::D27(std::pow(mnu[a],2),std::pow(md[c],2),mW*mW,mW*mW);

        return vll;
      }

      // Sum over boxes
      std::complex<double> VsumlLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        return 1. / (16.*std::pow(M_PI,2)) *( Vw4lLL(alpha, beta, gamma, delta, sminputs, U, mnu) + Vw8lLL(alpha, beta, gamma, delta, sminputs, U, mnu) + Vw4lpLL(alpha, beta, gamma, delta, sminputs, U, mnu) + Vw8lpLL(alpha, beta, gamma, delta, sminputs, U, mnu));
      }

      std::complex<double> VsumdLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        return 1./(16.*std::pow(M_PI,2)) *Vw4dLL(alpha, beta, gamma, delta, sminputs, U, mnu);
      }

      std::complex<double> VsumuLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        return 1./(16.*std::pow(M_PI,2)) *Vw4uLL(alpha, beta, gamma, delta, sminputs, U, mnu);
      }

    } // Diagrams


    // Form factors for LFV diagrams
    namespace FormFactors
    {

      std::complex<double> K1R(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> mnu)
      {
        double e = std::sqrt(4. * M_PI / sminputs.alphainv);
 
        return 1. / (16*std::pow(M_PI,2)*e) * Penguins::A1R(alpha, beta, sminputs, U, mnu);
      }

      std::complex<double> K2L(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        double e = std::sqrt(4. * M_PI / sminputs.alphainv);

        return 1. / (2. * 16.*std::pow(M_PI,2) * e * ml[alpha] ) * Penguins::A2L(alpha, beta, sminputs, U, ml, mnu);
      }

      std::complex<double> K2R(int alpha, int beta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        double e = std::sqrt(4. * M_PI / sminputs.alphainv);

        return 1. / (2. * 16.*std::pow(M_PI,2)*  e * ml[alpha] ) * Penguins::A2R(alpha, beta, sminputs, U, ml, mnu);
      }

      std::complex<double> AVLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::EL(gamma,delta,sminputs) / std::pow(sminputs.mZ,2) + Boxes::VsumlLL(alpha,beta,gamma,delta,sminputs,U,mnu);
      }

      std::complex<double> AVLR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::ER(gamma,delta,sminputs) / std::pow(sminputs.mZ,2);
      }

      std::complex<double> AVRL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::EL(gamma,delta,sminputs) / std::pow(sminputs.mZ,2);
      }

     std::complex<double> AVRR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::ER(gamma,delta,sminputs) / std::pow(sminputs.mZ,2);
      }

      std::complex<double> ASLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HL(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> ASLR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HR(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> ASRL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HL(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> ASRR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HR(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> BVLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::DL(gamma,delta,sminputs) / std::pow(sminputs.mZ,2) + Boxes::VsumdLL(alpha,beta,gamma,delta,sminputs,U,mnu);
      }

      std::complex<double> BVLR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::DR(gamma,delta,sminputs) / std::pow(sminputs.mZ,2);
      }

      std::complex<double> BVRL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::DL(gamma,delta,sminputs) / std::pow(sminputs.mZ,2);
      }

     std::complex<double> BVRR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::DR(gamma,delta,sminputs) / std::pow(sminputs.mZ,2);
      }

      std::complex<double> BSLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HdL(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> BSLR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HdR(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> BSRL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HdL(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> BSRR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HdR(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> CVLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::UL(gamma,delta,sminputs) / std::pow(sminputs.mZ,2) + Boxes::VsumuLL(alpha,beta,gamma,delta,sminputs,U,mnu);
      }

      std::complex<double> CVLR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::UR(gamma,delta,sminputs) / std::pow(sminputs.mZ,2);
      }

      std::complex<double> CVRL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::UL(gamma,delta,sminputs) / std::pow(sminputs.mZ,2);
      }

      std::complex<double> CVRR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu)
      {
        return Penguins::VZsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::UR(gamma,delta,sminputs) / std::pow(sminputs.mZ,2);
      }

      std::complex<double> CSLL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HuL(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> CSLR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HuR(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> CSRL(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HuL(gamma,delta,sminputs) / std::pow(mh,2);
      }

      std::complex<double> CSRR(int alpha, int beta, int gamma, int delta, Gambit::SMInputs sminputs, Eigen::Matrix<std::complex<double>,3,6> U, std::vector<double> ml, std::vector<double> mnu, double mh)
      {
        return Penguins::ShsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HuR(gamma,delta,sminputs) / std::pow(mh,2);
      }

    } // Form Factors
}

