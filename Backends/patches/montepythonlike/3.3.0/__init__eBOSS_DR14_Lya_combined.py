import sys 
import os
sys.path.append('../../')
import numpy as np
#from montepython import io_mp
from montepython.likelihood_class import Likelihood
import scipy.constants as const
from scipy.interpolate import RectBivariateSpline

class eBOSS_DR14_Lya_combined(Likelihood):

    # initialization routine

    def __init__(self, path, data, command_line):

        Likelihood.__init__(self, path, data, command_line)

        # define array for values of z and data points
        self.corr_types = []
        self.z = np.array([], 'float64')
        self.types = []

        scan_locations = {}
        scan_locations['comb'] = self.data_directory + '/' + self.cf_scan

        # read redshifts and data points
        for line in open(os.path.join(
                self.data_directory, self.file), 'r'):
            if (line.strip().find('#') == -1) and (len(line.strip())>0) and (line.split()[0] == 'comb'):
                self.corr_types += [line.split()[0]]
                self.z = np.append(self.z, float(line.split()[1]))
                self.types += [set([int(line.split()[2]),int(line.split()[3])])]

        # number of data points
        self.num_points = np.shape(self.z)[0]

        #Make our interpolators
        self.chi2_interpolators = chi2_interpolators(scan_locations,self.transverse_fid,self.parallel_fid)

        # end of initialization

    # compute log likelihood
    def loglkl(self, cosmo, data):

        chi2 = 0.

        # for each point, compute angular distance da, radial distance dr,
        # volume distance dv, sound horizon at baryon drag rs_d,
        # theoretical prediction and chi2 contribution
        # classes: (D_V/rs=3, Dv/Mpc=4, DA/rs=5, c/Hrs=6, rs/D_v=7, D_M/rs=8, H rs/rs_fid=9, D_M rs_fid/rs=10)
        for i in range(self.num_points):

            #print("Redshift %e from %i with type %i"%(self.z[i], self.num_points))
            da = cosmo.angular_distance(self.z[i])
            dr = self.z[i] / cosmo.Hubble(self.z[i])
            H  = cosmo.Hubble(self.z[i]) * const.c / 1000.

            dv = pow(da * da * (1 + self.z[i]) * (1 + self.z[i]) * dr, 1. / 3.)
            dm = da * (1 + self.z[i])

            rd = cosmo.rs_drag() * self.rd_rescale

            if (self.types[i] == set([5,6])):
                transverse = da / rd
                parallel = (const.c / 1000.) / (H * rd)
                chi2 += self.chi2_interpolators.get_Dchi2_from_distances(transverse,parallel,corr_type=self.corr_types[i])
            elif (self.types[i] == set([8,6])):
                transverse = dm / rd
                parallel = (const.c / 1000.) / (H * rd)
                chi2 += self.chi2_interpolators.get_Dchi2_from_distances(transverse,parallel,corr_type=self.corr_types[i])
            else:
                raise io_mp.LikelihoodError(
                    "In likelihood %s. " % self.name +
                    "BAO data types %s " % self.types[i] +
                    "in %d-th line not appropriately chosen." % i)

        # return ln(L)
        lkl = - 0.5 * chi2

        return lkl


#Class to read alpha_t by alpha_p chi2 scans e.g. from BOSS and interpolate.
class chi2_interpolators():
    def __init__(self,scan_locations,transverse_fid,parallel_fid):
        """
        Arguments:
        scan_locations: dictionary of filepaths to the different scans, with
                        keys as scan types.
        transverse_fid: fiducial value of transverse separation used to
                        calculate alpha_t.
        parallel_fid:   fiducial value of parallel separation used to calculate
                        alpha_p.
        """

        #Create a dictionary containing an interpolator for each scan.
        interpolators = {}
        for corr_type in scan_locations:
            scan = np.loadtxt(scan_locations[corr_type])

            #Column numbers in scan for data points.
            ap_index = 0
            at_index = 1
            chi2_index = 2

            #Get the alphas and make the scan grid.
            ap = np.array(sorted(set(scan[:,ap_index])))
            at = np.array(sorted(set(scan[:,at_index])))
            N_ap = ap.shape[0]
            N_at = at.shape[0]
            grid = np.zeros((N_at,N_ap))

            for i in range(N_ap):
                #Filter the data to only those corresponding to the ap value.
                indices = (scan[:,ap_index]==ap[i])
                scan_chunk = scan[indices,:]
                #Ensure that they're sorted by at value.
                scan_chunk = scan_chunk[scan_chunk[:,at_index].argsort()]
                #Add the chi2 column to the grid.
                #Note that the grid is of shape (N_at,N_ap)
                grid[:,i] = scan_chunk[:,chi2_index]

            #Make the interpolator (x refers to at, y refers to ap).
            interpolators[corr_type] = RectBivariateSpline(at,ap,grid,kx=1,ky=1)

        #Add the dictionary to the object.
        self.interpolators = interpolators
        self.transverse_fid = transverse_fid
        self.parallel_fid = parallel_fid

        return

    #Function to return the interpolated value of chi2 given distance measures.
    def get_Dchi2_from_distances(self,transverse,parallel,corr_type='cf'):
        """
        Arguments:
        transverse: value of transverse separation to evaluate chi2 for.
        parallel:   value of parallel separation to evaluate chi2 for.
        corr_type:  which scan to interpolate.

        Returns:
        Dchi2:       value of delta chi2
        """

        #Convert distances to alphas.
        at = transverse/self.transverse_fid
        ap = parallel/self.parallel_fid

        #With the new alphas, get the log likelihood.
        Dchi2 = self.interpolators[corr_type](at,ap)

        return Dchi2
