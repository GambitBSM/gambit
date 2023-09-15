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

#include "METSignificance/METSignificance.hpp"

#include "METSignificance/objres/JERData16EMTopo.h"
#include "METSignificance/objres/JERMC16EMTopo.h"

#include "METSignificance/objres/jetphi100.h"
#include "METSignificance/objres/jetphi20.h"
#include "METSignificance/objres/jetphi50.h"

#include "METSignificance/objres/r0_MS_MC_BARREL.h"
#include "METSignificance/objres/r1_ID_MC_BARREL.h"
#include "METSignificance/objres/r1_MS_MC_BARREL.h"
#include "METSignificance/objres/r2_ID_MC_BARREL.h"
#include "METSignificance/objres/r2_MS_MC_BARREL.h"

#include "METSignificance/objres/r0_MS_MC_ENDCAP.h"
#include "METSignificance/objres/r1_ID_MC_ENDCAP.h"
#include "METSignificance/objres/r1_MS_MC_ENDCAP.h"
#include "METSignificance/objres/r2_ID_MC_ENDCAP.h"
#include "METSignificance/objres/r2_MS_MC_ENDCAP.h"

#include "METSignificance/objres/electronConst90.h"
#include "METSignificance/objres/electronNoise90.h"
#include "METSignificance/objres/electronSampling90.h"

#include "METSignificance/objres/photonConst90.h"
#include "METSignificance/objres/photonNoise90.h"
#include "METSignificance/objres/photonSampling90.h"

#include "METSignificance/objres/tauRes1p0nBin0.h"
#include "METSignificance/objres/tauRes1p0nBin1.h"
#include "METSignificance/objres/tauRes1p0nBin2.h"
#include "METSignificance/objres/tauRes1p0nBin3.h"
#include "METSignificance/objres/tauRes1p0nBin4.h"

namespace Gambit
{
  namespace ColliderBit
  {


    // This replicates the function in TLorentzVector
    double Et(double E, double pT2, double pz)
    {
      
      if (pT2 == 0) {return 0.0;}
      double et = E < 0 ? -sqrt(E * E * pT2 / (pT2 + pz*pz)) : sqrt(E * E * pT2 / (pT2 + pz*pz));
      return et;
    }

    static double getHistValue(double *histdata, double x, double y,
                               bool interpolateX = false) {
      int nBinsX = int(histdata[0]);
      int nBinsY = int(histdata[1]);
      double *xbins = histdata + 2;
      double *ybins = histdata + 2 + nBinsX + 1;
      double *values = histdata + 2 + nBinsX + 1 + nBinsY + 1;
      x = std::min(x, xbins[nBinsX]);
      if (x < xbins[0] || x > xbins[nBinsX]) {
        std::cout << "x=" << x << " out of range [" << xbins[0] << ":"
                  << xbins[nBinsX] << "]" << std::endl;
        return 0;
      }
      if (y < ybins[0] || y > ybins[nBinsY]) {
        std::cout << "y=" << y << " out of range [" << ybins[0] << ":"
                  << ybins[nBinsY] << "]" << std::endl;
        return 0;
      }
      int xbin = 0;
      for (; xbin < nBinsX; xbin++)
        if (x < xbins[xbin + 1])
          break;
      int ybin = 0;
      for (; ybin < nBinsY; ybin++)
        if (y < ybins[ybin + 1])
          break;
      double value = values[xbin + ybin * nBinsX];
      if (interpolateX) {
        int nextbin = xbin + 1;
        if (nextbin < nBinsX && x < (xbins[nextbin] + xbins[xbin]) /
                                        2.) { // should interpolate to previous bin
          xbin = xbin - 1;
          value = values[xbin + ybin * nBinsX];
        }
        if (xbin >= 0 &&
            xbin < nBinsX - 1) { // simple linear interpolation like TGraph would do
          double value2 = values[xbin + 1 + ybin * nBinsX];
          double x1 = 0.5 * (xbins[xbin] + xbins[xbin + 1]);
          double x2 = 0.5 * (xbins[xbin + 1] + xbins[xbin + 2]);
          double frac = (x - x1) / (x2 - x1);
          value = (1 - frac) * value + frac * value2;
        }
      }
      return value;
    }

    static double getJetPtResolution(const HEPUtils::Jet* obj) {
      double et = std::min(3000., std::max(17., Et(obj->E(),obj->pT2(),obj->mom().pz()))); // constraint 5-50 GeV
      double eta = std::min(4.5, fabs(obj->eta()));
      double dataRes = getHistValue(hist_JERData16EMTopo, et, eta, true);
      double MCRes = getHistValue(hist_JERMC16EMTopo, et, eta, true);
      return std::max(dataRes, MCRes);
    }

    static double getJetPhiResolution(const HEPUtils::Jet* &obj) {
      if (obj->pT() < 50)
        return getHistValue(hist_jetphi20, obj->eta(), obj->phi());
      if (obj->pT() < 100)
        return getHistValue(hist_jetphi50, obj->eta(), obj->phi());
      return getHistValue(hist_jetphi100, obj->eta(), obj->phi());
    }

    static double getMuonPtResolution(const HEPUtils::Particle* obj) {
      double *resHistsBarrel[] = {
          hist_r1_ID_MC_BARREL, hist_r2_ID_MC_BARREL, hist_r0_MS_MC_BARREL,
          hist_r1_MS_MC_BARREL, hist_r2_MS_MC_BARREL,
      };
      double *resHistsEndcap[] = {
          hist_r1_ID_MC_ENDCAP, hist_r2_ID_MC_ENDCAP, hist_r0_MS_MC_ENDCAP,
          hist_r1_MS_MC_ENDCAP, hist_r2_MS_MC_ENDCAP,
      };
      double **resHists = resHistsEndcap;
      if (fabs(obj->eta()) < 1.05)
        resHists = resHistsBarrel;
      double pars[5];
      for (int ii = 0; ii < 5; ii++)
        pars[ii] = getHistValue(resHists[ii], obj->phi(), obj->eta());
      // we use same muon pt for everything, i.e. ignore energy loss before MS
      double IDResSq = pow(pars[0], 2) + pow(pars[1] * obj->pT(), 2);
      double MSResSq =
          pow(pars[2] / obj->pT(), 2) + pow(pars[3], 2) + pow(pars[4] * obj->pT(), 2);
      return sqrt(IDResSq * MSResSq / (IDResSq + MSResSq));
    }

    static double getElectronEtResolution(const HEPUtils::Particle* obj) {
      const double rsampling =
          getHistValue(hist_electronSampling90, fabs(obj->eta()), 0);
      const double rnoise = getHistValue(hist_electronNoise90, fabs(obj->eta()), 0);
      const double rconst = getHistValue(hist_electronConst90, fabs(obj->eta()), 0);
      const double energy = obj->E();
      double sigma2 = rsampling * rsampling / energy +
                      rnoise * rnoise / energy / energy + rconst * rconst;
      double et = std::min(50., std::max(5., Et(obj->E(),obj->pT2(),obj->mom().pz()))); // constraint 5-50 GeV

      double pileupNoiseMeV = sqrt(32.) * (60. + 40. * log(et / 10.) / log(5.));
      double pileupSigma2 = pow(pileupNoiseMeV / 1000. / Et(obj->E(),obj->pT2(),obj->mom().pz()),2); // not clear why Egamma uses Et and not E here?
      return sqrt(sigma2 + pileupSigma2);
    }

    static double getPhotonEtResolution(const HEPUtils::Particle* obj) {
      // photon resolution is taken from true unconverted photons
      const double rsampling =
          getHistValue(hist_photonSampling90, fabs(obj->eta()), 0);
      const double rnoise = getHistValue(hist_photonNoise90, fabs(obj->eta()), 0);
      const double rconst = getHistValue(hist_photonConst90, fabs(obj->eta()), 0);
      const double energy = obj->E();
      double sigma2 = rsampling * rsampling / energy +
                      rnoise * rnoise / energy / energy + rconst * rconst;
      double et = std::min(50., std::max(5., Et(obj->E(),obj->pT2(),obj->mom().pz()))); // constraint 5-50 GeV

      double pileupNoiseMeV = sqrt(32.) * (60. + 40. * log(et / 10.) / log(5.));
      double pileupSigma2 = pow(pileupNoiseMeV / 1000. / Et(obj->E(),obj->pT2(),obj->mom().pz()), 2); // not clear why Egamma group uses Et and not E here?
      return sqrt(sigma2 + pileupSigma2);
    }

    static double getTauPtResolution(const HEPUtils::Particle* obj) {
      double eta = fabs(obj->eta());
      double ptMeV = 1000. * std::min(499., std::max(15., obj->pT())); // only defined for 15-499 GeV
      double *hist = hist_tauRes1p0nBin0;
      if (eta > 0.3)
        hist = hist_tauRes1p0nBin1;
      if (eta > 0.8)
        hist = hist_tauRes1p0nBin2;
      if (eta > 1.3)
        hist = hist_tauRes1p0nBin3;
      if (eta > 1.6)
        hist = hist_tauRes1p0nBin4;
      double res = getHistValue(hist, ptMeV, 0, true);
      return res;
    }


    void getElectronResolution(const HEPUtils::Particle* obj, double &pt_reso,double &phi_reso) {
      pt_reso = getElectronEtResolution(obj);
      phi_reso = 0.004;
    }

    void getMuonResolution(const HEPUtils::Particle* obj, double &pt_reso,double &phi_reso) {
      pt_reso = getMuonPtResolution(obj);
      phi_reso = 0.001;
    }

    void getTauResolution(const HEPUtils::Particle* obj, double &pt_reso, double &phi_reso) {
      pt_reso = getTauPtResolution(obj);
      phi_reso = 0.01;
    }

    void getPhotonResolution(const HEPUtils::Particle* obj, double &pt_reso,double &phi_reso) {
      pt_reso = getPhotonEtResolution(obj);
      phi_reso = 0.004;
    }

    void getJetResolution(const HEPUtils::Jet* obj, double &pt_reso,double &phi_reso) {
      pt_reso = getJetPtResolution(obj);
      phi_reso = getJetPhiResolution(obj);
    }


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


  }
}
