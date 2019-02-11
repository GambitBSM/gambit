#!/usr/bin/env python
"""
Convolve chi-squared in a data file with a fractional theory error
==================================================================

python convolve_with_theory.py <file> <frac-error> <min> <max>

prints (parameter, convolved chi-squared) from a file containing
(parameter, chi-squared).
"""

import sys
import numpy as np
from scipy.interpolate import interp1d
from scipy.stats import norm, lognorm
from scipy.integrate import quad


def convolve(file_name, frac_error=0.1, min_=0., max_=1., log_normal=True):
    """
    Convolve chi-squared in a data file with a fractional theory error

    Args:
        file_name (str): Data file with columns (parameter, chi-squared).
        frac_error (float, optional): Fractional theory error on the parameter.
        min_ (float, optional): Minimum value of parameter.
        max_ (float, optional): Maximum value of parameter.
        log_normal (bool, optional): Whether to use log-normal or normal error.

    Returns:
        list(tuples): List of (parameter, convolved chi-squared)
    """
    # Unpack data
    param, chi_squared = np.loadtxt(file_name, unpack=True)

    # Interpolate likelihood function
    like = interp1d(param, np.exp(-0.5 * chi_squared),
        kind='linear', bounds_error=False, fill_value="extrapolate")

    # Make prior for true prediction
    def prior(x, mu):
        if log_normal:
            sigma = np.log(1. + frac_error)
            dist = lognorm(sigma, scale=mu)
        else:
            sigma = frac_error * mu
            dist = norm(mu, sigma)
        return dist.pdf(x)

    # Make functions for convolution
    integrand = lambda x, mu: like(x) * prior(x, mu)
    convolved = lambda mu: -2. * np.log(
        quad(integrand, min_, max_, args=(mu))[0]
        / quad(prior, min_, max_, args=(mu))[0])

    # Perform convolution
    return [(p, convolved(p)) for p in param]

if __name__ == "__main__":

    try:
        FILE_NAME = sys.argv[1]
    except IndexError:
        raise RuntimeError(__doc__)

    ARGS = map(float, sys.argv[2:])

    for p, c in convolve(FILE_NAME, *ARGS):
        print p, c
