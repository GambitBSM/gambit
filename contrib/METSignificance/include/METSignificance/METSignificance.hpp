//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  MET Significance functions, based on those provided at
///  https://gitlab.cern.ch/atlas-sa/framework
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date 2023 August
///
///  *********************************************

//#include "METSignificance/ObjectResolutions.hpp"

#include "HEPUtils/Jet.h"
#include "HEPUtils/Vectors.h"
#include "HEPUtils/Particle.h"

namespace Gambit
{

  namespace ColliderBit
  {

    void getElectronResolution(const HEPUtils::Particle*, double &, double &);

    void getMuonResolution(const HEPUtils::Particle*, double &, double &);

    void getTauResolution(const HEPUtils::Particle*, double &, double &);

    void getPhotonResolution(const HEPUtils::Particle*, double &, double &);

    void getJetResolution(const HEPUtils::Jet*, double &, double &);


    //static void rotateXY(std::vector<std::vector<double>> &mat, std::vector<std::vector<double>> &, double );
    
    double calcMETSignificance(std::vector<const HEPUtils::Particle*>, std::vector<const HEPUtils::Particle*>,
                               std::vector<const HEPUtils::Particle*>, std::vector<const HEPUtils::Jet*>,
                               std::vector<const HEPUtils::Particle*>, HEPUtils::P4&);
    
/*
    static void rotateXY(std::vector<std::vector<double>> &mat, std::vector<std::vector<double>> &mat_new, double phi) {
      double c = cos(phi);
      double s = sin(phi);
      double cc = c * c;
      double ss = s * s;
      double cs = c * s;

      mat_new[0][0] = mat[0][0] * cc + mat[1][1] * ss - cs * (mat[1][0] + mat[0][1]);
      mat_new[0][1] = mat[0][1] * cc - mat[1][0] * ss + cs * (mat[0][0] - mat[1][1]);
      mat_new[1][0] = mat[1][0] * cc - mat[0][1] * ss + cs * (mat[0][0] - mat[1][1]);
      mat_new[1][1] = mat[0][0] * ss + mat[1][1] * cc + cs * (mat[1][0] + mat[0][1]);
    }

    double calcMETSignificance(std::vector<const HEPUtils::Particle*> electrons, std::vector<const HEPUtils::Particle*> photons,
                               std::vector<const HEPUtils::Particle*> muons, std::vector<const HEPUtils::Jet*> jets,
                               std::vector<const HEPUtils::Particle*> taus, HEPUtils::P4 &metVec) {

      HEPUtils::P4 softVec = metVec;
      double met = metVec.pT();

      // Initialise 2D vectors
      std::vector<std::vector<double>> cov_sum = {{0.0,0.0},{0.0,0.0}};
      std::vector<std::vector<double>> particle_u = {{0.0,0.0},{0.0,0.0}};
      std::vector<std::vector<double>> particle_u_rot = {{0.0,0.0},{0.0,0.0}};
  
      // Electrons
      for (const HEPUtils::Particle* obj : electrons) {
        softVec += obj->mom(); // soft term is everything not included in hard objects
        double pt_reso = 0.0, phi_reso = 0.0;
        getElectronResolution(obj, pt_reso, phi_reso);
        particle_u[0][0] = pow(pt_reso * obj->pT(), 2);
        particle_u[1][1] = pow(phi_reso * obj->pT(), 2);
        rotateXY(particle_u, particle_u_rot, metVec.deltaPhi(obj->mom()));
        cov_sum[0][0] += particle_u_rot[0][0];
        cov_sum[0][1] += particle_u_rot[0][1];
        cov_sum[1][0] += particle_u_rot[1][0];
        cov_sum[1][1] += particle_u_rot[1][1];
      }
  
      // Muons
      for (const HEPUtils::Particle* obj : muons) {
        softVec += obj->mom(); // soft term is everything not included in hard objects
        double pt_reso = 0.0, phi_reso = 0.0;
        getMuonResolution(obj, pt_reso, phi_reso);
        particle_u[0][0] = pow(pt_reso * obj->pT(), 2);
        particle_u[1][1] = pow(phi_reso * obj->pT(), 2);
        rotateXY(particle_u, particle_u_rot, metVec.deltaPhi(obj->mom()));
        cov_sum[0][0] += particle_u_rot[0][0];
        cov_sum[0][1] += particle_u_rot[0][1];
        cov_sum[1][0] += particle_u_rot[1][0];
        cov_sum[1][1] += particle_u_rot[1][1];
      }
  
      // Taus
      for (const HEPUtils::Particle* obj : taus) {
        softVec += obj->mom(); // soft term is everything not included in hard objects
        double pt_reso = 0.0, phi_reso = 0.0;
        getTauResolution(obj, pt_reso, phi_reso);
        particle_u[0][0] = pow(pt_reso * obj->pT(), 2);
        particle_u[1][1] = pow(phi_reso * obj->pT(), 2);
        rotateXY(particle_u, particle_u_rot, metVec.deltaPhi(obj->mom()));
        cov_sum[0][0] += particle_u_rot[0][0];
        cov_sum[0][1] += particle_u_rot[0][1];
        cov_sum[1][0] += particle_u_rot[1][0];
        cov_sum[1][1] += particle_u_rot[1][1];
      }
  
      // Photons
      for (const HEPUtils::Particle* obj : photons) {
        softVec += obj->mom(); // soft term is everything not included in hard objects
        double pt_reso = 0.0, phi_reso = 0.0;
        getPhotonResolution(obj, pt_reso, phi_reso);
        particle_u[0][0] = pow(pt_reso * obj->pT(), 2);
        particle_u[1][1] = pow(phi_reso * obj->pT(), 2);
        rotateXY(particle_u, particle_u_rot, metVec.deltaPhi(obj->mom()));
        cov_sum[0][0] += particle_u_rot[0][0];
        cov_sum[0][1] += particle_u_rot[0][1];
        cov_sum[1][0] += particle_u_rot[1][0];
        cov_sum[1][1] += particle_u_rot[1][1];
      }
  
      // Jets
      for (const HEPUtils::Jet* obj : jets) {
        softVec += obj->mom(); // soft term is everything not included in hard objects
        double pt_reso = 0.0, phi_reso = 0.0;
        getJetResolution(obj, pt_reso, phi_reso);
        particle_u[0][0] = pow(pt_reso * obj->pT(), 2);
        particle_u[1][1] = pow(phi_reso * obj->pT(), 2);
        rotateXY(particle_u, particle_u_rot, metVec.deltaPhi(obj->mom()));
        cov_sum[0][0] += particle_u_rot[0][0];
        cov_sum[0][1] += particle_u_rot[0][1];
        cov_sum[1][0] += particle_u_rot[1][0];
        cov_sum[1][1] += particle_u_rot[1][1];
      }

      // add soft term resolution (fixed 10 GeV)
      particle_u[0][0] = 10 * 10;
      particle_u[1][1] = 10 * 10;
      rotateXY(particle_u, particle_u_rot, metVec.deltaPhi(softVec));
      cov_sum[0][0] += particle_u_rot[0][0];
      cov_sum[0][1] += particle_u_rot[0][1];
      cov_sum[1][0] += particle_u_rot[1][0];
      cov_sum[1][1] += particle_u_rot[1][1];

      // calculate significance
      double varL = cov_sum[0][0];
      double varT = cov_sum[1][1];
      double covLT = cov_sum[0][1];

      double significance = 0;
      double rho = 0;
      if (varL != 0) {
        rho = covLT / sqrt(varL * varT);
        if (fabs(rho) >= 0.9)
          rho = 0; // too large - ignore it
        significance = met / sqrt((varL * (1 - pow(rho, 2))));
      }
      return significance;
    }
*/

  }
}
