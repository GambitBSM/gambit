#!/usr/bin/env python
#
# GAMBIT: Global and Modular BSM Inference Tool
#*********************************************
# \file
#
# Simple script for generating parameter value 
# lists for the 'raster' scanner, when used
# to perform "SLHA scans" of simplified models
# with ColliderBit.
#
#*********************************************
#
#  Authors (add name and date if you modify):
#
#  \author Anders Kvellestad
#          (a.kvellestad@imperial.ac.uk)
#    \date 2019 Jul
#
#*********************************************

# 
# Example: 
#   
#   m1 : mass of neutralino1
#   m2 : mass of chargino1 = mass of neutralino2
#   xsec_fb: NLO+NLL cross-section [fb] for wino-like chi1pm + chi10 production at 13 TeV.
#   xsec_uncert_fb: absolute cross-section uncertainty [fb]
#
#   Cross-section values and uncertainties are taken from 
#   https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SUSYCrossSections13TeVn2x1wino#Envelope_of_CTEQ6_6_and_MSTW2008
#   

from __future__ import print_function

m2_data = [100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 425, 450, 475, 500, 525, 550, 575, 600, 625, 650, 675, 700, 725, 750, 775, 800, 825, 850, 875, 900, 925, 950, 975, 1000]
xsec_fb_data = [22670.1, 10034.8, 5180.86, 2953.28, 1807.39, 1165.09, 782.487, 543.03, 386.936, 281.911, 209.439, 158.06, 121.013, 93.771, 73.4361, 58.0811, 46.3533, 37.2636, 30.1656, 24.5798, 20.1372, 16.5706, 13.7303, 11.3975, 9.51032, 7.9595, 6.69356, 5.63562, 4.75843, 4.02646, 3.42026, 2.90547, 2.49667, 2.12907, 1.8164, 1.56893, 1.34352]
xsec_uncert_fb_data = [973.967, 457.604, 253.223, 154.386, 101.316, 68.8042, 48.7463, 35.4083, 26.3602, 20.0201, 15.4539, 12.0956, 9.61659, 7.73547, 6.2389, 5.05005, 4.16461, 3.46763, 2.88065, 2.40183, 2.04438, 1.70195, 1.43519, 1.21937, 1.04092, 0.885243, 0.769988, 0.654544, 0.564061, 0.478362, 0.412315, 0.366257, 0.314019, 0.26801, 0.242682, 0.217618, 0.175604]

assert len(m2_data) == len(xsec_fb_data)
assert len(m2_data) == len(xsec_uncert_fb_data)


# Pick out every n-th point, and no more than N different m2 values
n = 2
N = 8
m2 = m2_data[::n][:N]
xsec_fb = xsec_fb_data[::n][:N]
xsec_uncert_fb = xsec_uncert_fb_data[::n][:N]

# Steps in m1 for every m2
m1_min = 25.
m1_step = 50.

# Generate lists
m1_raster = []
m2_raster = []
xsec_fb_raster = []
xsec_uncert_fb_raster = []
# xsec_fractional_uncert_raster = []

for i in range(len(m2)):

    m1 = m1_min
    while (m1 < m2[i]):
        m1_raster.append(m1)
        m2_raster.append(m2[i])
        xsec_fb_raster.append(xsec_fb[i])
        xsec_uncert_fb_raster.append(xsec_uncert_fb[i])
        # xsec_fractional_uncert_raster.append(xsec_uncert_fb[i] / xsec_fb[i])
        m1 += m1_step


# Format parameter lists for output
model_name= "ColliderBit_SLHA_scan_model"

m1_str = "\"" + model_name + "::m1\"" + ": ["
for x in m1_raster:
    m1_str += "%.1f, " % x
m1_str = m1_str[:-2] + "]"

m2_str = "\"" + model_name + "::m2\"" + ": ["
for x in m2_raster:
    m2_str += "%.1f, " % x
m2_str = m2_str[:-2] + "]"

xsec_fb_str = "\"" + model_name + "::xsec_fb\"" + ": ["
for x in xsec_fb_raster:
    xsec_fb_str += "%.1f, " % x
xsec_fb_str = xsec_fb_str[:-2] + "]"

xsec_uncert_fb_str = "\"" + model_name + "::xsec_uncert_fb\"" + ": ["
for x in xsec_uncert_fb_raster:
    xsec_uncert_fb_str += "%.2f, " % x
xsec_uncert_fb_str = xsec_uncert_fb_str[:-2] + "]"

# xsec_fractional_uncert_str = "\"" + model_name + "::p4\"" + ": ["
# for x in xsec_fractional_uncert_raster:
#     xsec_fractional_uncert_str += "%.2f, " % x
# xsec_fractional_uncert_str = xsec_fractional_uncert_str[:-2] + "]"


# Print output
output  = """

Scanner:

  use_scanner: raster

  scanners:

    raster:
      plugin: raster
      like: LogLike
      parameters:
        {}
        {}
        {}
        {}

""".format(m1_str, m2_str, xsec_fb_str, xsec_uncert_fb_str) 
# """.format(m1_str, m2_str, xsec_fb_str, xsec_fractional_uncert_str) 

print(output)

