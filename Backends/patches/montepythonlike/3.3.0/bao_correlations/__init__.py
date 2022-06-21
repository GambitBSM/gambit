import os
import copy
import numpy as np
from montepython.likelihood_class import Likelihood
import montepython.io_mp as io_mp
import scipy.constants as conts
from scipy.interpolate import splrep, splev
from scipy.integrate import simps
from scipy.linalg.lapack import dgesv
from .findiff_py23 import FinDiff


class bao_correlations(Likelihood):
    '''

    BAO scale likelihood for BOSS DR12 and eBOSS data considering correlations
    between overlapping samples in the BAO scale measurements. This likelihood 
    takes into account the overlap of eBOSS LRG sample and BOSS DR12 galaxies,
    and the overlap of the eBOSS QSO sample with the LRGs on the sky & in redshift. 
    The non-zero correlations that should be accounted for between the measurements
    of (D_M/r_s)^{BOSS}, (Hr_s)^{BOSS}, (D_V/r_s)^{eBOSS,LRG}$, and (D_V/r_s)^{eBOSS,QSO}
    are calculated accounting for a variation in cosmological parameters. If you 
    use this likelihood, please cite GAMBIT Cosmology Workgroup: Stoecker et al. '20.

    To account for variation with cosmological parameters, this likelihood uses a
    novel method to compute the cross-correlation coefficients using Fisher matrices, 
    following BAO forecasting techniques (Seo & Eisenstein '07 {astro-ph/0701079}, 
    Font-Ribera et al. '14 {arXiv 1308.4164}). 
    Here, we sum the Fisher information that each sample contributes to the four
    overlapping measurements listed above, accounting for redshift and sky overlap. 
    Inverting the full Fisher matrix then gives the correlation coefficients. This 
    is done separately for every combination of cosmological parameters in the scan, 
    using the number density of objects, matter power spectrum and growth rate of 
    structure to model the BOSS/eBOSS galaxy power spectra and their covariance 
    matrices as a function of redshift. 
    
    For more details, see GAMBIT Cosmology Workgroup: Stoecker et al. '20, arXiv:2009.xxxxx. 

    '''

    # initialization routine

    def __init__(self, path, data, command_line):

        Likelihood.__init__(self, path, data, command_line)

        # define conflicting experiments
        conflicting_experiments = [
            'bao', 'bao_boss', 'bao_boss_dr12', 'bao_known_rs',
            'bao_boss_aniso', 'bao_boss_aniso_gauss_approx']
        for experiment in conflicting_experiments:
            if experiment in data.experiments:
                raise io_mp.LikelihoodError(
                    'conflicting BAO measurements')

        # define array for values of z and data points
        self.z = np.array([], 'float64')
        self.DM_rdfid_by_rd_in_Mpc = np.array([], 'float64')
        self.H_rd_by_rdfid_in_km_per_s_per_Mpc = np.array([], 'float64')
        self.Dv_by_rd = np.array([], 'float64')
        self.error = np.array([], 'float64')

        # read redshifts and data points for DR12
        with open(os.path.join(self.data_directory, self.dr12_data_file), 'r') as filein:
            for i, line in enumerate(filein):
                if line.strip() and line.find('#') == -1:
                    this_line = line.split()
                    # load redshifts and D_M * (r_s / r_s_fid)^-1 in Mpc
                    if this_line[1] == 'dM(rsfid/rs)':
                        self.z = np.append(self.z, float(this_line[0]))
                        self.DM_rdfid_by_rd_in_Mpc = np.append(
                            self.DM_rdfid_by_rd_in_Mpc, float(this_line[2]))
                        self.Dv_by_rd = np.append(self.Dv_by_rd, float(0.0))
                        self.error = np.append(self.error, float(0.0))
                    # load H(z) * (r_s / r_s_fid) in km s^-1 Mpc^-1
                    elif this_line[1] == 'Hz(rs/rsfid)':
                        self.H_rd_by_rdfid_in_km_per_s_per_Mpc = np.append(
                            self.H_rd_by_rdfid_in_km_per_s_per_Mpc, float(this_line[2]))


        # read the DR12 covariance matrix
        self.cov_data = np.loadtxt(os.path.join(self.data_directory, self.dr12_cov_file))

        # read redshifts and data points for DR114
        with open(os.path.join(self.data_directory, self.dr14_file), 'r') as filein:
            for line in filein:
                if line.strip() and line.find('#') == -1:
                    # the first entry of the line is the identifier
                    this_line = line.split()
                    self.z = np.append(self.z, float(this_line[0]))
                    self.Dv_by_rd = np.append(self.Dv_by_rd, float(this_line[1]))
                    self.error = np.append(self.error, float(this_line[2]))
                    self.DM_rdfid_by_rd_in_Mpc = np.append(
                        self.DM_rdfid_by_rd_in_Mpc, float(0.0))
                    self.H_rd_by_rdfid_in_km_per_s_per_Mpc = np.append(
                        self.H_rd_by_rdfid_in_km_per_s_per_Mpc, float(0.0))

        # number of bins
        self.num_bins_comb = np.shape(self.z)[0]
        self.num_bins = self.num_bins_comb - 2

        # Create extra rows for the eBOSS measurements
        self.num_points = np.shape(self.cov_data)[0]
        self.num_points_comb = self.num_points + 2
        self.cov_comb = np.zeros((self.num_points+2, self.num_points+2))
        self.cov_comb[:self.num_points, :self.num_points] = self.cov_data
        self.cov_comb[self.num_points:self.num_points+2, self.num_points:self.num_points+2] = np.diag(self.error[self.num_bins:self.num_bins+2])

        # Read in the data files for BOSS DR12, and eBOSS DR14 LRGs and QSOs and set up
        # some things for the cross-correlation calculation
        self.muvals = np.linspace(0.0, 1.0, 50)
        self.kvals = np.linspace(0.001, 0.3, 100)
        self.order, self.dalpha = 2, 0.002
        self.nz = np.loadtxt(os.path.join(self.data_directory, self.data_nz))
        self.kvalsalpha, self.kvalsalpha2d = self.set_kvals(self.order, self.dalpha)
        self.dPdalphaperp, self.dPdalphapar = FinDiff(0, self.dalpha), FinDiff(1, self.dalpha)
        self.BOSSbias, self.BOSSdamping = 1.54, np.exp(-0.5*np.outer(self.kvals**2, self.muvals**2*4.0**2 + (1.0 - self.muvals**2)*2.0**2))  # Worked out from Beutler 2017a,b
        self.eBOSSbias_LRG, self.eBOSSdamping_LRG = 2.3, np.exp(-0.5*np.outer(self.kvals**2, self.muvals**2*5.5**2 + (1.0 - self.muvals**2)*5.5**2))  # Based on Bautista 2017
        self.eBOSSbias_QSO, self.eBOSSdamping_QSO = 2.45, np.exp(-0.5*np.outer(self.kvals**2, self.muvals**2*6.0**2 + (1.0 - self.muvals**2)*6.0**2)) # Based on Ata 2017

        self.BOSS_area = 9376.0 * (np.pi / 180.0) ** 2
        self.eBOSS_LRG_area = 1845.0 * (np.pi / 180.0) ** 2
        self.eBOSS_QSO_area = 2113.0 * (np.pi / 180.0) ** 2

        # maximum redshift, needed to set mPk computing range
        self.zmax = max(self.z + 0.1)

        self.need_cosmo_arguments(data, {'non linear': 'halofit'})   
        self.need_cosmo_arguments(data, {'output': 'mPk'})
        self.need_cosmo_arguments(data, {'z_max_pk': self.zmax+0.5})  # (JR) had to add 0.5, otherwise class threw an out of range error
        # depending on the k values we need, we might have to adjust some
        # CLASS parameters that fix the k range (P_k_max_h/Mpc = 1.)
        self.need_cosmo_arguments(data, {'P_k_max_h/Mpc': 1.})

        # Dummy variables to store the latest version of the cross-correlation coefficients, and the likelihood
        # setting these cross-correlation coefficients to zero
        self.inv_cov_data = np.linalg.inv(self.cov_comb)
        self.uncorrelated_loglike = None
        self.correlation_coeffs = None

        # end of initialization


    # compute likelihood

    def loglkl(self, cosmo, data):

        # Extra routine needed to compute the cross-correlation coefficients between DR12 and DR14
        self.correlation_coeffs = self.compute_cross_corr_fisher(cosmo)
        cov_comb_corr = copy.copy(self.cov_comb)
        cov_comb_corr[4, 6] = self.correlation_coeffs[0] * np.sqrt(cov_comb_corr[4, 4]*cov_comb_corr[6, 6])
        cov_comb_corr[5, 6] = self.correlation_coeffs[1] * np.sqrt(cov_comb_corr[5, 5]*cov_comb_corr[6, 6])
        cov_comb_corr[7, 6] = self.correlation_coeffs[2] * np.sqrt(cov_comb_corr[7, 7]*cov_comb_corr[6, 6])
        cov_comb_corr[6, 4] = cov_comb_corr[4, 6]
        cov_comb_corr[6, 5] = cov_comb_corr[5, 6]
        cov_comb_corr[6, 7] = cov_comb_corr[7, 6]

        # define array for  values of D_M_diff = D_M^th - D_M^obs and H_diff = H^th - H^obs,
        # ordered by redshift bin (z=[0.38, 0.51, 0.61]) as following:
        # data_array = [DM_diff(z=0.38), H_diff(z=0.38), DM_diff(z=0.51), .., .., ..]
        data_array = np.array([], 'float64')

        # for each point, compute comoving angular diameter distance D_M = (1 + z) * D_A,
        # sound horizon at baryon drag rs_d, theoretical prediction
        for i in range(self.num_bins_comb):
            DM_at_z = cosmo.angular_distance(self.z[i]) * (1. + self.z[i])
            H_at_z = cosmo.Hubble(self.z[i]) * conts.c / 1000.0
            rd = cosmo.rs_drag() * self.dr12_rs_rescale

            if i < self.num_bins:

                theo_DM_rdfid_by_rd_in_Mpc = DM_at_z / rd * self.dr12_rd_fid_in_Mpc
                theo_H_rd_by_rdfid = H_at_z * rd / self.dr12_rd_fid_in_Mpc

                # calculate difference between the sampled point and observations
                DM_diff = theo_DM_rdfid_by_rd_in_Mpc - self.DM_rdfid_by_rd_in_Mpc[i]
                H_diff = theo_H_rd_by_rdfid - self.H_rd_by_rdfid_in_km_per_s_per_Mpc[i]

                # save to data array
                data_array = np.append(data_array, DM_diff)
                data_array = np.append(data_array, H_diff)

            else:

                DV_at_z = (DM_at_z**2 / H_at_z * conts.c / 1000.0 * self.z[i])**(1.0/3.0)
                theo_DV_by_rd_in_Mpc = DV_at_z / rd
                DV_diff = theo_DV_by_rd_in_Mpc - self.Dv_by_rd[i]
                data_array = np.append(data_array, DV_diff)

        # compute chi squared
        inv_cov_data_corr = np.linalg.inv(cov_comb_corr)
        chi2 = np.dot(np.dot(data_array,self.inv_cov_data),data_array)
        chi2_corr = np.dot(np.dot(data_array,inv_cov_data_corr),data_array)

        # return ln(L)
        self.uncorrelated_loglike = -0.5 * chi2
        loglkl = - 0.5 * chi2_corr

        return loglkl

    def compute_cross_corr_fisher(self, cosmo):

        h = cosmo.h()

        rlow = cosmo.z_of_r(self.nz[:,0])[0] * h  # Need to include h as fixed power spectrum values are in (Mpc/h)^3
        rhigh = cosmo.z_of_r(self.nz[:,2])[0] * h
        slice_volume = 1.0 / 3.0 * (rhigh ** 3 - rlow ** 3)

        # Compute the power spectrum, it's derivatives and scale-dependent growth rate at redshifts
        pksmoothallz, pkbaoallz, dpkdalphaallz, dpkdalphaperpallz, dpkdalphaparallz, fkallz = self.compute_pk(cosmo, self.nz[:,1])

        # Loop over each redshift bin in the three samples
        identity = np.eye(4)
        Fisher_tot = np.zeros((4, 4))    # Contains DA_BOSS, H_BOSS, DV_eBOSS_LRG, DV_eBOSS_QSO
        for i, data in enumerate(self.nz):

            z = data[1]

            pksmooth, pkbao, fk = pksmoothallz[:,i,None], pkbaoallz[:,i,None], fkallz[:,i,0]
            dpkdalpha, dpkdalphaperp, dpkdalphapar = dpkdalphaallz[:,i,None], dpkdalphaperpallz[:,i,:], dpkdalphaparallz[:,i,:]
            prefac = slice_volume[i]

            # Do the correct thing based on the various redshift regimes

            # BOSS only. For z < 0.6 BOSS galaxies contribute just to Da(z=0.61) and H(z=0.61) (and other lower z-bins,
            # but this is already accounted for in the main BOSS results).
            if z < 0.6:
                kaiserBOSS = (1.0 + np.outer(fk, self.muvals**2)/self.BOSSbias)
                pkBOSS = self.BOSSbias ** 2 * kaiserBOSS ** 2 * pksmooth * (1.0 + pkbao * self.BOSSdamping)
                cov_inv = 1.0/(pkBOSS + self.BOSS_area * slice_volume[i] / data[3]) ** 2
                derivs = self.get_derivsDaH(self.BOSSbias ** 2 * kaiserBOSS ** 2 * pksmooth * self.BOSSdamping, dpkdalphaperp, dpkdalphapar)
                for j in range(2):
                    Fisher = simps(self.kvals ** 2 * simps(derivs[j] * cov_inv * derivs, x=self.muvals, axis=-1), x = self.kvals, axis=-1)
                    Fisher *= self.BOSS_area * prefac
                    Fisher_tot[j, :2] += Fisher

            # For z > 0.6 things are a little more complicated. The BOSS galaxies outside the eBOSS sky area contribute only to
            # Da(z=0.61) and H(z=0.61), so lets add them on first. Then, the combined BOSS+eBOSS sample for z < 0.75 contributes
            # to all three measurements Da(z=0.61), H(z=0.61) and Dv(z=0.72) so add these in. There are actually two ways to
            # do this, we could alternatively work out the contribution from BOSS galaxies to all three measurements, then the extra
            # contribution from the eBOSS only galaxies. However, we don't know the bias and non-linear damping for the eBOSS-only
            # subsample (only the combined BOSS+eBOSS sample).
            elif z >= 0.60 and z <= 0.75:
                kaiserBOSS = (1.0 + np.outer(fk, self.muvals**2)/self.BOSSbias)
                pkBOSS = self.BOSSbias ** 2 * kaiserBOSS ** 2 * pksmooth * (1.0 + pkbao * self.BOSSdamping)
                cov_inv = 1.0/(pkBOSS + (self.BOSS_area - self.eBOSS_LRG_area) * slice_volume[i] / (data[3] - data[5])) ** 2
                derivs = self.get_derivsDaH(self.BOSSbias ** 2 * kaiserBOSS ** 2 * pksmooth * self.BOSSdamping, dpkdalphaperp, dpkdalphapar)
                for j in range(2):
                    Fisher = simps(self.kvals ** 2 * simps(derivs[j] * cov_inv * derivs, x=self.muvals, axis=-1), x = self.kvals, axis=-1)
                    Fisher *= (self.BOSS_area - self.eBOSS_LRG_area) * prefac
                    Fisher_tot[j, :2] += Fisher

                kaisereBOSS_LRG = (1.0 + np.outer(fk, self.muvals**2)/self.eBOSSbias_LRG)
                pkeBOSS_LRG = self.eBOSSbias_LRG ** 2 * kaisereBOSS_LRG ** 2 * pksmooth * (1.0 + pkbao * self.eBOSSdamping_LRG)
                cov_inv = 1.0/(pkeBOSS_LRG + self.eBOSS_LRG_area * slice_volume[i] / data[4]) ** 2
                derivs = self.get_derivsDaHDv(self.eBOSSbias_LRG ** 2 * kaisereBOSS_LRG ** 2 * pksmooth * self.eBOSSdamping_LRG, dpkdalpha, dpkdalphaperp, dpkdalphapar)
                for j in range(3):
                    Fisher = simps(self.kvals ** 2 * simps(derivs[j] * cov_inv * derivs, x=self.muvals, axis=-1), x = self.kvals, axis=-1)
                    Fisher *= self.eBOSS_LRG_area * prefac
                    Fisher_tot[j, :3] += Fisher

            # eBOSS LRG only. For 0.75 < z < 0.80, we only have to consider the eBOSS LRGs, which contribute to Dv(z=0.72)
            elif z > 0.75 and z < 0.8:
                kaisereBOSS_LRG = (1.0 + np.outer(fk, self.muvals**2)/self.eBOSSbias_LRG)
                pkeBOSS_LRG = self.eBOSSbias_LRG ** 2 * kaisereBOSS_LRG ** 2 * pksmooth * (1.0 + pkbao * self.eBOSSdamping_LRG)
                cov_inv = 1.0/(pkeBOSS_LRG + self.eBOSS_LRG_area * slice_volume[i] / data[4]) ** 2
                derivs = self.get_derivsDv(self.eBOSSbias_LRG ** 2 * kaisereBOSS_LRG ** 2 * pksmooth * self.eBOSSdamping_LRG, dpkdalpha)
                Fisher = simps(self.kvals ** 2 * simps(derivs * cov_inv * derivs, x=self.muvals, axis=-1), x=self.kvals, axis=-1)
                Fisher *= self.eBOSS_LRG_area * prefac
                Fisher_tot[2, 2] += Fisher

            # eBOSS_LRG+eBOSS_QSO. For z < 1.0 we have eBOSS LRGS and QSOs in the same region of space. As we have a slightly larger
            # QSO sky area than LRGs, we assume that the QSOs in the non-overlap area contribute only to Dv(z=1.52). In the overlap area
            # both the LRGs and the QSOs will contribute to Dv(z=0.72) and Dv(z=1.52). As the derivatives for each sample are the same
            # regardless of whether we are considering Dv(z=0.72) or Dv(z=1.52), we just add the eBOSS_LRG area to every relevant Fisher
            # matrix element (including the cross-terms) for both sample, then a little extra to Dv(z=1.52) for the QSO sample in the
            # non-overlap area. the eBOSS LRGs.
            elif z >= 0.80 and z <= 1.00:
                kaisereBOSS_LRG = (1.0 + np.outer(fk, self.muvals**2)/self.eBOSSbias_LRG)
                pkeBOSS_LRG = self.eBOSSbias_LRG ** 2 * kaisereBOSS_LRG ** 2 * pksmooth * (1.0 + pkbao * self.eBOSSdamping_LRG)
                cov_inv = 1.0/(pkeBOSS_LRG + self.eBOSS_LRG_area * slice_volume[i] / data[4]) ** 2
                derivs = self.get_derivsDv(self.eBOSSbias_LRG ** 2 * kaisereBOSS_LRG ** 2 * pksmooth * self.eBOSSdamping_LRG, dpkdalpha)
                Fisher = simps(self.kvals ** 2 * simps(derivs * cov_inv * derivs, x=self.muvals, axis=-1), x=self.kvals, axis=-1)
                Fisher *= self.eBOSS_LRG_area * prefac
                Fisher_tot[2:, 2:] += Fisher

                kaisereBOSS_QSO = (1.0 + np.outer(fk, self.muvals**2)/self.eBOSSbias_QSO)
                pkeBOSS_QSO = self.eBOSSbias_QSO ** 2 * kaisereBOSS_QSO ** 2 * pksmooth * (1.0 + pkbao * self.eBOSSdamping_QSO)
                cov_inv = 1.0/(pkeBOSS_QSO + self.eBOSS_QSO_area * slice_volume[i] / data[6]) ** 2
                derivs = self.get_derivsDv(self.eBOSSbias_QSO ** 2 * kaisereBOSS_QSO ** 2 * pksmooth * self.eBOSSdamping_QSO, dpkdalpha)
                Fisher = simps(self.kvals ** 2 * simps(derivs * cov_inv * derivs, x=self.muvals, axis=-1), x=self.kvals, axis=-1)
                Fisher *= prefac
                Fisher_tot[2:, 2:] += self.eBOSS_LRG_area*Fisher
                Fisher_tot[3, 3] += (self.eBOSS_QSO_area - self.eBOSS_LRG_area)*Fisher

            # Finally we can do the eBOSS QSO only sample for z > 1.00
            elif z >= 1.00:
                kaisereBOSS_QSO = (1.0 + np.outer(fk, self.muvals**2)/self.eBOSSbias_QSO)
                pkeBOSS_QSO = self.eBOSSbias_QSO ** 2 * kaisereBOSS_QSO ** 2 * pksmooth * (1.0 + pkbao * self.eBOSSdamping_QSO)
                cov_inv = 1.0/(pkeBOSS_QSO + self.eBOSS_QSO_area * slice_volume[i] / data[6]) ** 2
                derivs = self.get_derivsDv(self.eBOSSbias_QSO ** 2 * kaisereBOSS_QSO ** 2 * pksmooth * self.eBOSSdamping_QSO, dpkdalpha)
                Fisher = simps(self.kvals ** 2 * simps(derivs * cov_inv * derivs, x=self.muvals, axis=-1), x=self.kvals, axis=-1)
                Fisher *= self.eBOSS_QSO_area*prefac
                Fisher_tot[3, 3] += Fisher


        Fisher_tot[2, 3] *= -1   # Minus sign to ensure eBOSS_LRG and QSO correlation coefficient is positive, as
        Fisher_tot[3, 2] *= -1   # expected given they measure the same quantity, just in slightly different bins. See comment in get_derivsDaHDv
        Fisher_tot /= 4.0*np.pi**2

        cov_lu, pivots, cov, info = dgesv(Fisher_tot, identity)

        cross_corr_BOSS_Da_eBOSS_Dv = cov[0, 2]/np.sqrt(cov[0, 0]*cov[2, 2])
        cross_corr_BOSS_H_eBOSS_Dv = -cov[1, 2]/np.sqrt(cov[1, 1]*cov[2, 2])    # Minus sign to convert from coefficient for alpha_par to H(z)
        cross_corr_eBOSS_LRG_eBOSS_QSO = cov[2, 3]/np.sqrt(cov[2, 2]*cov[3, 3])
        return [cross_corr_BOSS_Da_eBOSS_Dv, cross_corr_BOSS_H_eBOSS_Dv, cross_corr_eBOSS_LRG_eBOSS_QSO]

    def set_kvals(self, order, dalpha):

        # Create some vectors of kprime values, shaped conveniently
        karray = np.empty((2*order+1, len(self.kvals), len(self.nz)))
        karray2d = np.empty((2*order+1, 2*order+1, len(self.kvals), len(self.muvals)))
        for i in range(-order, order+1):
            alpha = 1.0 + i * dalpha
            alpha_perp = 1.0 + i * dalpha
            karray[i + order] = (np.tile(self.kvals/alpha, (len(self.nz), 1))).T
            for j in range(-order, order+1):
                alpha_par = 1.0 + j * dalpha
                karray2d[i + order, j + order] = np.outer(self.kvals, np.sqrt((1.0 - self.muvals ** 2) / alpha_perp ** 2 + self.muvals ** 2 / alpha_par ** 2))

        return karray[:, :, :, None], karray2d[:, :, :, None, :]

    def smooth_hinton2017(self, ks, pk, degree=13, sigma=1, weight=0.5, **kwargs):
        """ Smooth power spectrum based on Hinton 2017 polynomial method """
        # logging.debug("Smoothing spectrum using Hinton 2017 method")
        log_ks = np.log(ks)
        log_pk = np.log(pk)
        index = np.argmax(pk)
        maxk2 = log_ks[index]
        gauss = np.exp(-0.5 * np.power(((log_ks - maxk2) / sigma), 2))
        w = np.ones(pk.size) - weight * gauss
        z = np.polyfit(log_ks, log_pk, degree, w=w)
        p = np.poly1d(z)
        polyval = p(log_ks)
        pk_smoothed = np.exp(polyval)
        return pk_smoothed

    def compute_pk(self, cosmo, zs):

        # We only take derivatives with respect to the BAO wiggles, so we run Sam Hinton's BAO smoothing method on
        # the models to extract the smooth component. We keep the smooth component for each separate redshift to allow for
        # non-linearities, however the BAO feature is smoothed separately so we need to constuct this using the linear power
        # spectrum. The plus side is that we only need to construct the derivatives at one redshift, as we can
        # then scale them using sigma8. So ultimately we only need to carry one set of pkbao derivatives, and the
        # non-linear smooth component at each redshift.
        pk = cosmo.h() ** 3 * cosmo.get_pk_cb(self.kvalsalpha[self.order] * cosmo.h(), zs, len(self.kvals), len(zs), 1)
        pklin = cosmo.h() ** 3 * cosmo.get_pk_cb_lin(self.kvalsalpha[self.order] * cosmo.h(), zs, len(self.kvals), len(zs), 1)
        pksmooth = np.array([self.smooth_hinton2017(self.kvals, pk[:,i,0]) for i in range(len(zs))]).T
        pksmoothlin = np.array([self.smooth_hinton2017(self.kvals, pklin[:,i,0]) for i in range(len(zs))]).T
        pkbao = pklin[:,:,0]/pksmoothlin - 1.0
        pkspline = [splrep(self.kvals, pkbao[:,i]) for i in range(len(zs))]

        # Use finite differences to get the derivatives of the BAO feature w.r.t. alpha/alpha_perp/alpha_par about alpha=1
        pkbaoarray = np.empty((2*self.order+1, len(self.kvals), len(self.nz)))
        pkbaoarray2d = np.empty((2*self.order+1, 2*self.order+1, len(self.kvals), len(self.nz), len(self.muvals)))
        for i in range(-self.order, self.order+1):
            pkbaoarray[i + self.order] = np.array([splev(self.kvalsalpha[i + self.order,:,0,0], pkspline[z]) for z in range(len(zs))]).T
            for j in range(-self.order, self.order+1):
                pkbaoarray2d[i + self.order, j + self.order] = np.transpose(np.array([splev(self.kvalsalpha2d[i + self.order, j + self.order, :, 0, :], pkspline[z]) for z in range(len(zs))]), axes=(1,0,2))

        dpkdalpha = self.dPdalphaperp(pkbaoarray)[self.order]
        dpkdalphaperp, dpkdalphapar = self.dPdalphaperp(pkbaoarray2d)[self.order, self.order], self.dPdalphapar(pkbaoarray2d)[self.order, self.order]

        # Compute the scale-dependent growth rate using more finite-differencing
        alow = 1.0 / (1.0 + (zs - 0.001))
        amid = 1.0 / (1.0 + zs)
        ahi = 1.0 / (1.0 + (zs + 0.001))
        Dlow = np.sqrt(cosmo.h() ** 3 * cosmo.get_pk_cb_lin(self.kvalsalpha[self.order] * cosmo.h(), zs - 0.001, len(self.kvals), len(zs), 1))
        Dmid = np.sqrt(cosmo.h() ** 3 * cosmo.get_pk_cb_lin(self.kvalsalpha[self.order] * cosmo.h(), zs, len(self.kvals), len(zs), 1))
        Dhigh = np.sqrt(cosmo.h() ** 3 * cosmo.get_pk_cb_lin(self.kvalsalpha[self.order] * cosmo.h(), zs + 0.001, len(self.kvals), len(zs), 1))
        fk = np.transpose(np.transpose(((Dhigh - Dlow) / Dmid), axes=(0,2,1)) * amid / (ahi - alow), axes=(0,2,1))

        return pksmooth, pkbao, dpkdalpha, dpkdalphaperp, dpkdalphapar, fk

    def get_derivsDv(self, prefac, dpkdalpha):

        # Derivative of model with respect to alpha.
        return prefac * dpkdalpha

    def get_derivsDaH(self, prefac, dpkdalphaperp, dpkdalphapar):

        # Derivatives with respect to Da and H
        derivs = np.empty((2, len(self.kvals), len(self.muvals)))
        derivs[0] = prefac * dpkdalphaperp
        derivs[1] = prefac * dpkdalphapar

        return derivs

    def get_derivsDaHDv(self, prefac, dpkdalpha, dpkdalphaperp, dpkdalphapar):

        # Derivatives with respect to Da, H and Dv
        derivs = np.zeros((3, len(self.kvals), len(self.muvals)))
        derivs[0] = prefac * dpkdalphaperp
        derivs[1] = prefac * dpkdalphapar
        derivs[2] = -prefac * dpkdalpha
        # Minus sign in derivs[2] ensures correlation coefficient matrix has positive sign.
        # We would expect Da and Dv to be positively correlated, so the cross-term in the Fisher matrix
        # should be negative. This is adhoc, as my way of adding information from each redshift slice to diagonal/off-diagonal
        # terms means the off- diagonal components are always positive, but I think the correct thing to do.
        # It is most obvious if you consider the eBOSS LRG and eBOSS QSO overlap. They are both measuring the same quantity,
        # and we would expect a high value in one to correspond to a high value in the other if they share cosmic variance.
        # But, if we let the Fisher information in the cross-term be positive, that means we would get a negative cross-
        # correlation coefficient. This way also gives cross-correlation coefficients equivalent to the Veff ratio
        # calculated in the eBOSS LRG paper.

        return derivs
