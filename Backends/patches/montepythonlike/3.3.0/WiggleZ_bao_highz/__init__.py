import sys 
from montepython.likelihood_class import Likelihood
import numpy as np
from math import log
import os


class WiggleZ_bao_highz(Likelihood):
    """From 1401.0358v2"""

    def __init__(self, path, data, command_line):

        Likelihood.__init__(self, path, data, command_line)


    def loglkl(self, cosmo, data):
        # Modes
        z, Dv = self.high_z, self.high_z_Dv

        da = cosmo.angular_distance(z)
        dr = z/cosmo.Hubble(z)
        dv = pow(da**2*(1.+z)**2*dr, 1./3)
        rs = cosmo.rs_drag()
        difference = Dv - dv/rs*self.rs_fiducial

        chi2 = (difference / self.high_z_sigma)**2
        lkl = - 0.5 *chi2
        return lkl
