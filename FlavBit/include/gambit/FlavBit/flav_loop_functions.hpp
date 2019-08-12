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
///  *********************************************

#ifndef __flav_loop_functions_hpp
#define __flav_loop_functions_hpp

namespace Gambit
{

  namespace FlavBit
  {
    using namespace std;

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
          return (-7. + 33.*x - 57.*x*x + 31.*x*x*x + 6.*x*x*(1. - 3*x)*log(x))/(12.*pow(1.-x,4));
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
          return (6.*a*a*(a-3.*b)*log(a/b) - (a-b)*(5.*a*a - 22.*a*b + 5.*b*b))/(9.*pow(a-b,4));
      }

      double B1(const double a, const double b, const double Q)
      {
        if(a == b)
          return 0.5 * log(b / pow(Q,2));
        else if(a == 0)
          return -0.25 + 0.5*log(b / pow(Q,2));
        else
          return -0.5 + 0.5*log(b / pow(Q,2)) - (a*a - b*b + 2.*a*a*log(b/a)) / (4.*pow(a-b,2));
      }

      double B0(const double a, const double b, const double Q)
      {
        // TODO: behaviour when a = 0 and b = 0 undefined
        if(a == 0 and b == 0)
          return 0;
        else if(a == b)
          return -log(b / pow(Q,2));
        else if(a == 0)
          return 1. - log(b / pow(Q,2));
        else if(b == 0)
          return 1. - log(a) - log(1./pow(Q,2));
        else
          return 1. - log(b / pow(Q,2)) + 1./(b-a) * a * log(a/b);
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
          return (-b + c- c*log(c/b)) / pow(b-c,2);
        else if(a == c and b != 0)
          return C0(a,c,b);
        else if(a == c and b == 0)
          return -1./c;
        else if(b == c and a != 0)
          return (a - c + a*log(c/a)) / pow(a-c,2);
        else if(b == c and a == 0)
          return -1./c;
        else if(a == 0)
          return (-log(b) + log(c)) / (b-c);
        else if(b == 0)
          return log(c/a)/(a-c);
        else
          return -1. / (a-b)*(a-c)*(b-c)*( b*(c-a)*log(b/a) + c*(a-b)*log(c/a));
      }

      double C00(const double a, const double b, const double c, const double Q)
      {
        // TODO: behaviour when all three parameters are zero is undefined, set it to zero
        if(a == 0 and b == 0 and c == 0)
          return 0;
        else if(b == 0 and c == 0)
          return 0.125*(3. - 2.*log(a/pow(Q,2)));
        else if(a == 0 and b == 0)
          return 0.125*(3. - 2.*log(c) - 2.*log(1./pow(Q,2)));
        else if(c == 0)
          return C00(a,c,b,Q);
        else if(a == b and b == c)
          return -0.25*log(c/pow(Q,2));
        else if(a == b)
          return - (2.*c*c*log(c/b) + (b-c)*(-b + 3.*c + 2.*(b-c)*log(b/pow(Q,2))))/(8.*pow(b-c,2));
        else if(a == c and b != 0)
          return C00(a,c,b,Q);
        else if(a == c and b == 0)
          return 0.125*(1. - 2.*log(c/pow(Q,2)));
        else if(b == c and a != 0)
          return (2.*(2.*a-c)*c*log(c/a)-(a-c)*(-3.*a+c+2.*(a-c)*log(a/pow(Q,2))))/(8.*pow(a-c,2));
        else if(b == c and a == 0)
          return 0.125*(1. - 2.*log(c) - 2.*log(1./pow(Q,2)));
        else if(a == 0)
          return -(2.*b*log(b) - 2.*c*log(c) + (b-c)*(-3.+2.*log(1./pow(Q,2))))/(8.*(b-c));
        else if(b == 0)
          return (2.*c*log(c/a) - (a-c)*(-3. + 2.*log(a/pow(Q,2))))/(8.*(a-c));
        else
          return 1. / (8.*(a-b)*(a-c)*(b-c)) * ( (c-a)*((a-b)*(2.*log(a/pow(Q,2))-3.)*(b-c) - 2.*b*b*log(b/a)) + 2.*c*c*(b-a)*log(c/a));
      }

      // Finite combination of loop functions that appears in VZw10
      double B02C00C0(const double a, const double b, const double c, const double Q)
      {
        if(a == 0 and b == 0)
          return 0.25*(1.0 - 2.0*log(c) - 2.0*log(1 / pow(Q,2)));
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
          return (-b*b + c*c + 2.*b*c*log(b/c)) / (2.*c*pow(c-b,3));
        else if(b == c and c == d and a == 0)
          return 1. / (2.*d*d);
        else if(b == c and c == d and a != 0)
          return (a*a - d*d + 2.*a*d*log(d/a)) / (2.*d*pow(a-d,3));
        else if(a == d and b == c)
          return (-2*c + 2*d + (c+d)*log(c/d)) / pow(c-d,3);
        else if(a == d and b == 0)
          return (c - d -d*log(c/d)) / (pow(c-d,2)*d);
        else if(a == d)
          return 1./ ((b-d)*(d-c))-(b*log(b/d))/((b-c)*pow(b-d,2))+(c*log(c/d))/((b-c)*pow(c-d,2));
        else if(a == c)
          return D0(a,b,d,c);
        else if(a == b)
          return D0(a,d,c,b);
        else if(b == c)
          return D0(a,d,c,b);
        else if(b == d)
          return D0(a,c,b,d);
        else if(c == d and b == 0)
          return (a - d + d*log(d/a)) / (d*pow(a-d,2));
        else if(c == d and a == 0)
          return (b - d + d*log(d/b)) / (d*pow(b-d,2));
        else if(c == d)
          return (b*pow(a-d,2)*log(b/a) - (a-b)*( (a-d)*(b-d) + (a*b-d*d)*log(d/a) )) / ((a-b)*pow(a-d,2)*pow(b-d,2));
        else if(b == 0)
          return log(c/a)/((a-c)*(c-d)) + log(d/a)/((a-d)*(d-c));
        else if(a == 0)
          return ((d-c)*log(b) + (b-d)*log(c) + (c-b)*log(d))/((b-c)*(b-d)*(c-d));
        else
          return -(b*log(b/a)/((b-a)*(b-c)*(b-d)) + c*log(c/a)/((c-a)*(c-b)*(c-d)) + d*log(d/a)/((d-a)*(d-b)*(d-c)));
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
           return (3.*b*b - 4.*b*d + d*d - 2.*b*b*log(b/d))/(8.*pow(b-d,3));
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
          return (-b*b + d*d -2.*b*d*log(d/b)) / (4.*pow(b-d,3));
        if(a == c and b == d)
          return D27(a,c,b,d);
        if(a == d and b == c)
          return D27(a,b,d,c);
        if(a == b and b == 0)
          return log(d/c)/(4.*(c-d));
        if(a == b and c == 0)
          return - (b -d +d*log(d/b))/(4.*pow(b-d,2));
        if(a == b and d == 0)
          return D27(a,b,d,c);
        if(a == b)
          return 0.25*(-c*c*log(c/b)/(pow(b-c,2)*(c-d)) + (b*(d-b)/(b-c) + d*d*log(d/b)/(c-d))/pow(b-d,2));
        if(a == c)
          return D27(a,c,b,d);
        if(a == d)
          return D27(a,d,c,b);
        if(b == c and a == 0)
          return (-c+d+d*log(c/d))/(4.*pow(c-d,2));
        if(b == c and c == 0)
          return log(d/a)/(4.*(a-d));
        if(b == c and d == 0)
          return (a-c+a*log(c/a))/(4.*pow(a-c,2));
        if(b == c)
          return (c*(a-d)*(a*(c-2.*d)+c*d)*log(c/a)+(a-c)*(c*(a-d)*(c-d)+(a-c)*d*d*log(d/a)))/(4.*pow(a-c,2)*(a-d)*pow(c-d,2));
        if(b == d)
          return D27(a,b,d,c);
        if(c == d)
          return D27(a,c,d,b);
        if(a == 0)
          return (b*(-c+d)*log(b)+c*(b-d)*log(c)+(-b+c)*d*log(d))/(4.*(b-c)*(b-d)*(c-d));
        if(b == 0)
          return ((c*log(c/a))/((a - c)*(c - d)) + (d*log(d/a))/((a - d)*(-c + d)))/4.;
        if(c == 0)
          return D27(a,c,b,d);
        if(d == 0)
          return D27(a,d,c,b);
        else
          return -0.25*(b*b*log(b/a)/((b-a)*(b-c)*(b-d)) + c*c*log(c/a)/((c-a)*(c-b)*(c-d)) + d*d*log(d/a)/((d-a)*(d-b)*(d-c)));
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
          return (x*(-4.0 + 15.0*x - 12.0*pow(x,2) + pow(x,3) + 6.0*pow(x,2)*log(x)))/ (4.*pow(-1.0 + x,3));
        return x*y*(-3.0/(4.0*(1.0-x)*(1.0 - y)) + ((0.25 - 3.0/(4.0*pow(-1.0 + x,2)) - 3.0/(2.0*(-1.0 + x)))*log(x))/(x - y) + ((0.25 - 3.0/(4.0*pow(-1.0 + y,2)) - 3.0/(2.0*(-1 + y)))*log(y))/(-x + y));
      }

    }

    // Vertices for LFV diagrams
    namespace Vertices
    {
      // Fermion-vector vertices
      complex<double> VpL(int i, int j, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U)
      {
        double g2 = sminputs.mW * sqrt( 8. * sminputs.GF / sqrt(2));
        return  -1. / sqrt(2) * g2 * U(i,j);
      
      }

      double EL(int i,int j, SMInputs sminputs)
      {
        if(i != j)  return 0; 

        double e = sqrt(4. * pi / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double g2 = sminputs.mW * sqrt( 8. * sminputs.GF / sqrt(2));
        double cw = sminputs.mW / sminputs.mZ;
        double sw = sqrt(1. - cw*cw);
        return 0.5 * (-g1*sw + g2*cw);
        
      }
 
      double ER(int i, int j, SMInputs sminputs)
      {
        if(i != j) return 0;
 
        double e = sqrt(4. * pi / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double cw = sminputs.mW / sminputs.mZ;
        double sw = sqrt(1. - cw*cw);
        return - g1*sw; 
      }

      complex<double> VL(int i, int j, SMInputs sminputs)
      {
        double e = sqrt(4. * pi / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double g2 = sminputs.mW * sqrt( 8. * sminputs.GF / sqrt(2));
        double cw = sminputs.mW / sminputs.mZ;
        double sw = sqrt(1. - cw*cw);

        if(i == j)
          return -0.5*(g1*sw + g2*cw);
        else
          return 0.;
      }

      complex<double> VR(int i, int j, SMInputs sminputs)
      {
        double e = sqrt(4. * pi / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double g2 = sminputs.mW * sqrt( 8. * sminputs.GF / sqrt(2));
        double cw = sminputs.mW / sminputs.mZ;
        double sw = sqrt(1. - cw*cw);

        if(i == j)
          return 0.5*(g1*sw + g2*cw);
        else
          return 0.;
      }

      complex<double> DL(int i, int j, SMInputs sminputs)
      {
        double e = sqrt(4. * pi / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double g2 = sminputs.mW * sqrt( 8. * sminputs.GF / sqrt(2));
        double cw = sminputs.mW / sminputs.mZ;
        double sw = sqrt(1. - cw*cw);

        if(i == j)
          return 1./6. * (3.*g2*cw + g1*sw);
        else
          return 0;
      }

      complex<double> DR(int i, int j, SMInputs sminputs)
      {
        double e = sqrt(4. * pi / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double cw = sminputs.mW / sminputs.mZ;
        double sw = sqrt(1. - cw*cw);

        if(i == j)
          return -1./3.*g1*sw;
        else
          return 0.;
      }

      complex<double> UL(int i, int j, SMInputs sminputs)
      {
        double e = sqrt(4. * pi / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double g2 = sminputs.mW * sqrt( 8. * sminputs.GF / sqrt(2));
        double cw = sminputs.mW / sminputs.mZ;
        double sw = sqrt(1. - cw*cw);

        if(i == j)
          return -1./6. * (3.*g2*cw - g1*sw);
        else
          return 0;
      }

      complex<double> UR(int i, int j, SMInputs sminputs)
      {
        double e = sqrt(4. * pi / sminputs.alphainv);
        double g1 = e * sminputs.mZ / sminputs.mW;
        double cw = sminputs.mW / sminputs.mZ;
        double sw = sqrt(1. - cw*cw);

        if(i == j)
          return 2./3.*g1*sw;
        else
          return 0.;
      }

      complex<double> VuL(int i, int j, SMInputs sminputs)
      {
         double g2 = sminputs.mW * sqrt( 8. * sminputs.GF / sqrt(2));
         Eigen::Matrix3cd VCKM;
         double lambda = sminputs.CKM.lambda, A = sminputs.CKM.A;
         double rhobar = sminputs.CKM.rhobar, etabar = sminputs.CKM.etabar;
         complex<double> I = {0,1};

         complex<double> Vub = real(rhobar + I*etabar)*sqrt(1.-A*A*pow(lambda,4))/(sqrt(1.-pow(lambda,2))*(1.- A*A*pow(lambda,4)*(rhobar+I*etabar)));
         double rho = real(Vub);
         double eta = imag(Vub);

         VCKM << 1. - 0.5*pow(lambda,2), lambda, A*pow(lambda,3)*(rho - I*eta),
                 -lambda, 1. - 0.5*pow(lambda,2), A*pow(lambda,2),
                 A*pow(lambda,3)*(1. - eta - I*eta), -A*pow(lambda,2), 1;

         return -1./sqrt(2) * g2 * VCKM(i,j);
      }

      // Vector vertices
      double Fw(SMInputs sminputs)
      {
        return sqrt(4.* pi/ sminputs.alphainv);
      }

      double Zww(SMInputs sminputs)
      {
        double g2 = sminputs.mW * sqrt( 8. * sminputs.GF / sqrt(2));
        return -g2 * sminputs.mW / sminputs.mZ;
      }

      // Scalar vertices
      double HL(int i, int j, SMInputs sminputs)
      {
        double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);
        
        if(i == 0 and j == 0)
          return -1. / vev * sminputs.mE;
        if(i == 1 and j == 1)
          return -1. / vev * sminputs.mMu;
        if(i == 2 and j == 2)
          return -1. / vev * sminputs.mTau;
        else 
          return 0;
      }

      double HR(int i, int j, SMInputs sminputs)
      {
        return HL(i, j , sminputs);
      } 

      double HdL(int i, int j, SMInputs sminputs)
      {
        double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);

        if(i == 0 and j == 0)
          return -1. / vev * sminputs.mD;
        else if(i == 1 and j == 1)
          return -1. / vev * sminputs.mS;
        else if(i == 2 and j == 2)
          return -1. / vev * sminputs.mBmB;
        else
          return 0;
      }

      double HdR(int i, int j, SMInputs sminputs)
      {
        return HdL(i, j, sminputs);
      }

      double HuL(int i, int j, SMInputs sminputs)
      {
        double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);

        if(i == 0 and j == 0)
          return -1. / vev * sminputs.mU;
        else if(i == 1 and j == 1)
          return -1. / vev * sminputs.mCmC;
        else if(i == 2 and j == 2)
          return -1. / vev * sminputs.mT;
        else
          return 0;
      }

      double HuR(int i, int j, SMInputs sminputs)
      {
        return HuL(i, j, sminputs);
      }


    }

    // Penguin contributions
    namespace Penguins
    {
      // Fotonic penguins

      complex<double> A1R(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        complex<double> a1r = {0,0};

        for(int a=0; a<6; a++)
        {
          a1r += Vertices::Fw(sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(beta,a,sminputs,U)) * LoopFunctions::MFVV(pow(mnu[a],2), pow(sminputs.mW,2));
        }

        return a1r;
      }

      complex<double> A2L(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
         complex<double> a2l = {0,0};
         double mW = sminputs.mW;

         for(int a=0; a<6; a++)
           a2l += -2. * Vertices::Fw(sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(beta,a,sminputs,U)) * LoopFunctions::G1(pow(mnu[a],2), mW*mW, mW*mW) * ml[beta];

         return a2l;
      }

      complex<double> A2R(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
         complex<double> a2r = {0,0};
         double mW = sminputs.mW;
         for(int a=0; a<6; a++)
          a2r += -2. * Vertices::Fw(sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(beta,a,sminputs,U)) * LoopFunctions::G1(pow(mnu[a],2), mW*mW, mW*mW) * ml[alpha];

         return a2r;
      }

      // Z penguins
      complex<double> VZw2w4LL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        complex<double> vzll = {0,0};
 
        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
          {
            // Use MZ for the renormalization scale Q
            if(beta == c)
              vzll += Vertices::EL(beta,c, sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(pow(mnu[a],2),pow(sminputs.mW,2),sminputs.mZ))* pow(ml[alpha],2) / (pow(ml[alpha],2) - pow(ml[c],2));
            if(alpha == c) 
              vzll += Vertices::EL(alpha,c, sminputs) * Vertices::VpL(beta,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(pow(mnu[a],2),pow(sminputs.mW,2),sminputs.mZ))* pow(ml[beta],2) / (pow(ml[beta],2) - pow(ml[c],2));
         }

         return vzll;
      }

      complex<double> VZw2w4LR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return VZw2w4LL(alpha,beta,sminputs,U,ml,mnu);
      }
    
      complex<double> VZw2w4RR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        complex<double> vzrr = {0,0};
 
        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
          {
            if(beta == c)
              vzrr += Vertices::ER(beta,c,sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(pow(mnu[a],2),pow(sminputs.mW,2),sminputs.mZ))* ml[c]*ml[alpha] / (pow(ml[alpha],2) - pow(ml[c],2));
            if(alpha == c)
              vzrr += Vertices::ER(alpha,c, sminputs) * Vertices::VpL(beta,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(pow(mnu[a],2),pow(sminputs.mW,2),sminputs.mZ))* ml[c]*ml[beta] / (pow(ml[beta],2) - pow(ml[c],2));
         }

         return vzrr;
      }

      complex<double> VZw2w4RL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return VZw2w4RR(alpha, beta, sminputs, U, ml, mnu); 
      }

      complex<double> VZw8LL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        complex<double> vzll = {0,0};
        double mW = sminputs.mW;

        // Use MZ as the renormalization scale Q
	for(int a=0; a<6; a++)
          vzll += Vertices::Zww(sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(beta,a,sminputs,U)) * (1. - 2.*(LoopFunctions::B0(mW*mW,mW*mW,sminputs.mZ) + 2.*LoopFunctions::C00(pow(mnu[a],2),mW*mW,mW*mW,sminputs.mZ) + LoopFunctions::C0(pow(mnu[a],2),mW*mW,mW*mW)*pow(mnu[a],2)));

        return vzll;
      }
    
      complex<double> VZw8LR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        return VZw8LL(alpha, beta, sminputs, U, mnu);
      }

      complex<double> VZw10LL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        complex<double> vzll = {0,0};
        double mW = sminputs.mW;
 
        // Use MZ as the renormalization scale Q
        for(int b=0; b<6; b++)
        {
          // Use different loop function in case that mnu[b] 0
          if(mnu[b])
            vzll += - Vertices::VpL(alpha,b,sminputs,U) * conj(Vertices::VpL(beta,b,sminputs,U)) * (2.* Vertices::VR(b,b,sminputs) * LoopFunctions::C0(pow(mnu[b],2),pow(mnu[b],2),mW*mW) * mnu[b] * mnu[b] + Vertices::VL(b,b,sminputs) * (1. - 2.*(LoopFunctions::B0(pow(mnu[b],2),pow(mnu[b],2),sminputs.mZ) - 2.*LoopFunctions::C00(pow(mnu[b],2),pow(mnu[b],2),mW*mW,sminputs.mZ) + LoopFunctions::C0(pow(mnu[b],2),pow(mnu[b],2),mW*mW)*mW*mW)));
          else
            vzll += - Vertices::VpL(alpha,b,sminputs,U) * conj(Vertices::VpL(beta,b,sminputs,U)) * Vertices::VL(b,b,sminputs) * (1. - 2.*(LoopFunctions::B02C00C0(pow(mnu[b],2),pow(mnu[b],2),mW*mW,sminputs.mZ)));
        }

        return vzll;
      }

      complex<double> VZw10LR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        return VZw10LL(alpha, beta, sminputs, U, mnu);
      }

      // Sum over Z penguins
      complex<double> VZsumLL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
       return 1. / (16.*pow(pi,2)) * (VZw2w4LL(alpha, beta, sminputs, U, ml, mnu) + VZw8LL(alpha, beta, sminputs, U, mnu) + VZw10LL(alpha, beta, sminputs, U, mnu));
      }

      complex<double> VZsumLR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return 1. / (16.*pow(pi,2)) * (VZw2w4LR(alpha, beta, sminputs, U, ml, mnu) + VZw8LR(alpha, beta, sminputs, U, mnu) + VZw10LR(alpha, beta, sminputs, U, mnu));
      }

      complex<double> VZsumRL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return 1. / (16.*pow(pi,2)) * (VZw2w4RL(alpha, beta, sminputs, U, ml, mnu));
      }

      complex<double> VZsumRR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return 1. / (16.*pow(pi,2)) * (VZw2w4RR(alpha, beta, sminputs, U, ml, mnu));
      }

      // Scalar penguins
      complex<double> Shw2w4LL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        complex<double> shll = {0,0};
        double mW = sminputs.mW;

        // Use mZ for the renormalisation scale Q
        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
          {
            if(beta == c)
              shll += - (Vertices::HL(beta,c,sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(pow(mnu[a],2),mW*mW, sminputs.mZ)) * pow(ml[alpha],2))/(pow(ml[alpha],2) - pow(ml[c],2));
            if(alpha == c)
              shll += - (Vertices::HL(alpha,c,sminputs) * Vertices::VpL(beta,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(pow(mnu[a],2),mW*mW, sminputs.mZ)) * pow(ml[beta],2))/(pow(ml[beta],2) - pow(ml[c],2));
          }

        return shll;
      }

      complex<double> Shw2w4LR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Shw2w4LL(alpha, beta, sminputs, U, ml, mnu);
      }

      complex<double> Shw2w4RR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        complex<double> shrr = {0,0};
        double mW = sminputs.mW;

        // Use mZ for the renormalisation scale Q
        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
          {
            if(beta == c)
              shrr += - (Vertices::HR(beta,c,sminputs) * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(pow(mnu[a],2),mW*mW, sminputs.mZ)) * ml[c]*ml[alpha])/(pow(ml[alpha],2) - pow(ml[c],2));
            if(alpha == c)
              shrr += - (Vertices::HR(alpha,c,sminputs) * Vertices::VpL(beta,a,sminputs,U) * conj(Vertices::VpL(c,a,sminputs,U)) * (1. + 2.* LoopFunctions::B1(pow(mnu[a],2),mW*mW, sminputs.mZ)) * ml[c]*ml[beta])/(pow(ml[beta],2) - pow(ml[c],2));
          }

        return shrr;
      }

      complex<double> Shw2w4RL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Shw2w4RR(alpha, beta, sminputs, U, ml, mnu);
      }

      // Sum over scalar penguins
      complex<double> ShsumLL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return 1. / (16.*pow(pi,2)) * Shw2w4LL(alpha, beta, sminputs, U, ml, mnu);
      }    

      complex<double> ShsumLR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return 1. / (16.*pow(pi,2)) * Shw2w4LR(alpha, beta, sminputs, U, ml, mnu);
      }    

      complex<double> ShsumRL(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return 1. / (16.*pow(pi,2)) * Shw2w4RL(alpha, beta, sminputs, U, ml, mnu);
      }    

      complex<double> ShsumRR(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return 1. / (16.*pow(pi,2)) * Shw2w4RR(alpha, beta, sminputs, U, ml, mnu);
      }    

    }

    // Box contributions
    namespace Boxes
    {
      complex<double> Vw4lLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        complex<double> vll = {0,0};
        double mW = sminputs.mW;

        for(int a=0; a<6; a++)
          for(int c=0; c<6; c++)
            vll += -4. * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(beta,a,sminputs,U)) * Vertices::VpL(gamma,c,sminputs,U) * conj(Vertices::VpL(delta,c,sminputs,U)) * (LoopFunctions::IC0D0(pow(mnu[c],2),mW*mW, mW*mW, pow(mnu[a],2)) - 3. * LoopFunctions::D27(pow(mnu[a],2),pow(mnu[c],2),mW*mW,mW*mW));

        return vll;
      }

      complex<double> Vw8lLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        complex<double> vll = {0,0};
        double mW = sminputs.mW;

        for(int a=0; a<6; a++)
          for(int c=0; c<6; c++)
            vll += -2. * Vertices::VpL(alpha,a,sminputs,U) * conj(Vertices::VpL(delta,c,sminputs,U)) * Vertices::VpL(gamma,a,sminputs,U) * conj(Vertices::VpL(beta,c,sminputs,U)) * mnu[a] * mnu[c] * LoopFunctions::D0(pow(mnu[a],2),pow(mnu[c],2),mW*mW,mW*mW);

        return vll;
      }

      complex<double> Vw4lpLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        return Vw4lLL(alpha, delta, gamma, beta, sminputs, U, mnu);
      }

      complex<double> Vw8lpLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        return Vw8lLL(alpha, delta, gamma, beta, sminputs, U, mnu);
      }

      complex<double> Vw4dLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        complex<double> vll = {0,0};
        double mW = sminputs.mW;
        vector<double> mu = {sminputs.mU, sminputs.mCmC, sminputs.mT};

        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
            vll += -4.*Vertices::VpL(alpha,a,sminputs,U)*conj(Vertices::VpL(beta,a,sminputs,U))*Vertices::VuL(gamma,c,sminputs)*conj(Vertices::VuL(delta,c,sminputs))*(LoopFunctions::IC0D0(pow(mu[c],2),mW*mW, mW*mW, pow(mnu[a],2)) - 3.*LoopFunctions::D27(pow(mnu[a],2),pow(mu[c],2),mW*mW,mW*mW));

        return vll;
      }

      complex<double> Vw4uLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        complex<double> vll = {0,0};
        double mW = sminputs.mW;
        vector<double> md = {sminputs.mD, sminputs.mS, sminputs.mBmB};

        for(int a=0; a<6; a++)
          for(int c=0; c<3; c++)
            vll += 16.*Vertices::VpL(alpha,a,sminputs,U)*conj(Vertices::VpL(beta,a,sminputs,U))*Vertices::VuL(delta,c,sminputs)*conj(Vertices::VuL(gamma,c,sminputs))*LoopFunctions::D27(pow(mnu[a],2),pow(md[c],2),mW*mW,mW*mW);

        return vll;
      }

      // Sum over boxes
      complex<double> VsumlLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        return 1. / (16.*pow(pi,2)) *( Vw4lLL(alpha, beta, gamma, delta, sminputs, U, mnu) + Vw8lLL(alpha, beta, gamma, delta, sminputs, U, mnu) + Vw4lpLL(alpha, beta, gamma, delta, sminputs, U, mnu) + Vw8lpLL(alpha, beta, gamma, delta, sminputs, U, mnu));
      }

      complex<double> VsumdLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        return 1./(16.*pow(pi,2)) *Vw4dLL(alpha, beta, gamma, delta, sminputs, U, mnu);
      }

      complex<double> VsumuLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        return 1./(16.*pow(pi,2)) *Vw4uLL(alpha, beta, gamma, delta, sminputs, U, mnu);
      }

    } // Diagrams


    // Form factors for LFV diagrams
    namespace FormFactors
    {

      complex<double> K1R(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> mnu)
      {
        double e = sqrt(4. * pi / sminputs.alphainv);
 
        return 1. / (16*pow(pi,2)*e) * Penguins::A1R(alpha, beta, sminputs, U, mnu);
      }

      complex<double> K2L(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        double e = sqrt(4. * pi / sminputs.alphainv);

        return 1. / (2. * 16.*pow(pi,2) * e * ml[alpha] ) * Penguins::A2L(alpha, beta, sminputs, U, ml, mnu);
      }

      complex<double> K2R(int alpha, int beta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        double e = sqrt(4. * pi / sminputs.alphainv);

        return 1. / (2. * 16.*pow(pi,2)*  e * ml[alpha] ) * Penguins::A2R(alpha, beta, sminputs, U, ml, mnu);
      }

      complex<double> AVLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::EL(gamma,delta,sminputs) / pow(sminputs.mZ,2) + Boxes::VsumlLL(alpha,beta,gamma,delta,sminputs,U,mnu);
      }

      complex<double> AVLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::ER(gamma,delta,sminputs) / pow(sminputs.mZ,2);
      }

      complex<double> AVRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::EL(gamma,delta,sminputs) / pow(sminputs.mZ,2);
      }

     complex<double> AVRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::ER(gamma,delta,sminputs) / pow(sminputs.mZ,2);
      }

      complex<double> ASLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HL(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> ASLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HR(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> ASRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HL(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> ASRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HR(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> BVLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::DL(gamma,delta,sminputs) / pow(sminputs.mZ,2) + Boxes::VsumdLL(alpha,beta,gamma,delta,sminputs,U,mnu);
      }

      complex<double> BVLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::DR(gamma,delta,sminputs) / pow(sminputs.mZ,2);
      }

      complex<double> BVRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::DL(gamma,delta,sminputs) / pow(sminputs.mZ,2);
      }

     complex<double> BVRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::DR(gamma,delta,sminputs) / pow(sminputs.mZ,2);
      }

      complex<double> BSLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HdL(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> BSLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HdR(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> BSRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HdL(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> BSRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HdR(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> CVLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::UL(gamma,delta,sminputs) / pow(sminputs.mZ,2) + Boxes::VsumuLL(alpha,beta,gamma,delta,sminputs,U,mnu);
      }

      complex<double> CVLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::UR(gamma,delta,sminputs) / pow(sminputs.mZ,2);
      }

      complex<double> CVRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::UL(gamma,delta,sminputs) / pow(sminputs.mZ,2);
      }

      complex<double> CVRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu)
      {
        return Penguins::VZsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::UR(gamma,delta,sminputs) / pow(sminputs.mZ,2);
      }

      complex<double> CSLL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumLL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HuL(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> CSLR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumLR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HuR(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> CSRL(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumRL(alpha,beta,sminputs,U,ml,mnu)*Vertices::HuL(gamma,delta,sminputs) / pow(mh,2);
      }

      complex<double> CSRR(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix<complex<double>,3,6> U, vector<double> ml, vector<double> mnu, double mh)
      {
        return Penguins::ShsumRR(alpha,beta,sminputs,U,ml,mnu)*Vertices::HuR(gamma,delta,sminputs) / pow(mh,2);
      }

    } // Form Factors
  }
}

#endif //#defined __flav_loop_functions_hpp__
