#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Master module containing class information, auto-writing codes, etc.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019
#
#  **************************************

from __future__ import print_function
from future.utils import iteritems

import datetime
import os
import sys

class GumError(Exception):
  pass

# Banner
def banner() :
  return " ***********************************\n"\
         " GUM: GAMBIT Universal Model Machine\n"\
         " ***********************************\n"\
         "\n"\
         " Created by:\n"\
         "\n"\
         " Sanjay Bloor\n"\
         "   (sanjay.bloor12@imperial.ac.uk)\n"\
         " Tomas Gonzalo\n"\
         "   (gonzalo@physik.rwth-aachen.de)\n"\
         " Pat Scott\n"\
         "   (pat.scott@uq.edu.au)\n"\
         "\n"\
         " ***********************************\n"\
         "\n"\
         " GUM 1.0 is open source and under\n"\
         " the terms of the standard 3-clause\n"\
         " BSD license.\n"\
         "\n"\
         " Documentation and details for GUM\n"\
         " can be found at\n"\
         "   S. Bloor et al, arXiv:2107.00030,\n"\
         "   Eur. Phys. J. C 81 (2021), 1103\n"\
         "\n"\
         " ***********************************\n"\
         "\n"


class Particle:
    """
    Particle class for internal use in GUM.
    """

    def __init__(self, name, antiname, spinx2, pdg_code, mass_name,
                 chargex3, color,
                 alt_name = None, alt_mass_name = None, tree_mass = None):

        self.name = name
        self.antiname = antiname
        self.spinX2 = spinx2
        self.chargeX3 = chargex3
        self.color = color
        self.PDG_code = pdg_code
        self.mass = mass_name
        self.alt_name = alt_name
        self.alt_mass_name = alt_mass_name
        self.tree_mass = tree_mass

        self.own_conjugate = None
        if (name == antiname):
            self.own_conjugate = True
        else:
            self.own_conjugate = False

        # If a particle is self-conjugate -> the conjugate PDG code is same.
        if self.own_conjugate:
            self.conjugate_PDG_code = self.PDG_code
        else:
            self.conjugate_PDG_code = -self.PDG_code

    def is_sc(self):
        """
        Boolean to flag if a particle is self conjugate.
        """

        return self.own_conjugate

def pdg_to_particle(pdg_code, pdg_dict):
    """
    Returns the particle name from the PDG code, from either
    a GAMBIT or CalcHEP dict, wrapped in quotation marks.
    """

    for name, pdg_val in iteritems(pdg_dict) :
        if pdg_code == pdg_val:
            return name

    # If not found -> return None & deal with this on case-by-case
    return None

class Vertex:
    """
    Vertex class for internal use in GUM.
    """

    def __init__(self):
        self.particles = []
        self.SM = True

    def is_sm(self):
        """
        Boolean to flag if an interaction is Standard Model.
        """
        return self.SM

    def num_particles(self):
        """
        Returns number of particles in vertex.
        """
        return len(self.particles)

class SpectrumParameter:
    """
    Spectrum Parameter class for use in GUM. Contains information about the
    Par::tag of parameter, read from a FeynRules or SARAH file, to be used
    in SpecBit and in Models.
    """

    def __init__(self, name, tag, block=None, index=1,
                 shape=None, fullname=None,
                 sm=False, gb_input=None,
                 alt_name=None, bcs=None,
                 is_output=False, is_real=False,
                 fullparticlename = None,
                 default = 0.1):

        self.name = name
        self.tag = tag
        self.shape = shape
        self.block = block
        self.index = index
        self.sm = sm
        self.is_output = is_output
        self.is_real = is_real
        self.fullparticlename = fullparticlename
        self.default = default

        if not fullname:
            self.fullname = name
        else:
            self.fullname = fullname
        if not gb_input:
            self.gb_in = name
        else:
            self.gb_in = gb_input
        if not alt_name:
            self.alt_name = name
        else:
            self.alt_name = alt_name
        self.bcs = bcs

class BackendReq:
    """
    Backend requirement class for rollcall files. Assumes default
    behaviour is a BE_VARIABLE requiring no arguments.
    """

    def __init__(self, capability, cpptype, tags=[], variable=True,
                 args=[]):
        self.capability = capability
        self.cpptype = cpptype
        self.args = args
        self.tags = tags

        if variable:
            self.var = True
            self.args = None
        elif not variable:
            self.var = False
            self.args = args


class Dependency:
    """
    Dependency class used for rollcall files.
    """

    def __init__(self, name, cpptype):
        self.name = name
        self.cpptype = cpptype

# Block & enable printing
def blockPrint():
    sys.stdout = open(os.devnull, 'w')

def enablePrint():
    sys.stdout = sys.__stdout__
