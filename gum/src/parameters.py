#  GUM: GAMBIT Universal Models Machine
#  ************************************
#  \file
#
#  Master module for all routines relating 
#  to parameters, manipulation, etc.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019 
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2019 Aug
#
#  **************************************

import re

from .setup import *

###############
## FEYNRULES ##
###############

def fr_part_to_gum_part(fr_bsm):
    """
    Converts all FeynRules::FRParticle to GUM::Particle.
    Returns whether or not to add a dependency on StandardModel_Higgs.
    """
    
    bsm_list = []
    add_higgs = False

    all_pdgs = [x.pdg() for x in fr_bsm]
    # If the SM higgs included but not a second Higgs, 
    # then we want a dependency on StandardModel_Higgs.
    # If it is a 2+HDM then we don't.
    if 25 in all_pdgs and 35 not in all_pdgs: 
        add_higgs = True

    for i in range(len(fr_bsm)):
        part = fr_bsm[i]
        bsm_list.append(Particle(part.name(), part.antiname(),
                                 part.spinX2(), part.pdg(), 
                                 part.mass(), part.chargeX3(), part.color()))
    
    return bsm_list, add_higgs

def fr_params(paramlist, add_higgs):
    """
    Removes all Standard Model parameters from those we wish
    to add to the GAMBIT model. This utilises the 'BlockName'
    tag (i.e. the SLHA Block the parameters will be placed in)
    to distinguish between Standard Model parameters, and 
    parameters the user has implemented in their own FeynRules
    model file.

    Behaviour mimics the SM.fr file that is delivered with 
    FeynRules by default. The following blocks will not be 
    considered BSM: 'SMINPUTS', 'YUKAWA' or 'CKMBLOCK'.
    Everything else is fair game. 

    Default assumption is that everything is a dimensionless
    parameter. 
    TODO. Since there are no spectra, this should be ok.
    Maybe worth adding a new parameter tag, like Par::unspecified.
    """

    unsorted_params = []
    params = []

    # Add all parameters from the parameter list from FeynRules
    for i in range(len(paramlist)):
        p = paramlist[i]
        if (    (p.block() != 'YUKAWA')
            and (p.block() != 'SMINPUTS')
            and (p.block() != 'CKMBLOCK')):
            
            # Create a new instance of SpectrumParameter
            # Everything is scalar by default. This can change later if we 
            # identify a matrix or vector of parameters
            x = SpectrumParameter(p.name(), "dimensionless", shape = "scalar",
                                  block=p.block(), index=p.index())
            unsorted_params.append(x)

    # Now all of the parameters have been extracted, look to see if any of them
    # are elements of a matrix.

    # Firstly, get the name of each block
    blocks = list(set([i.block for i in unsorted_params]))

    # For each block, add the parameters to a dictionary...
    from collections import defaultdict
    blockdict = defaultdict(list)

    for i in blocks:
        for j in unsorted_params:
            if j.block == i:
                blockdict[i].append(j.name)

    # Parameters that GUM decides are (square) matrices
    matrices = {}

    # Go through each entry in the dictionary, and try and group them
    for k, v in iteritems(blockdict):

        # FeynRules splits a matrix M into M1x1, M1x2, ..., Mdxd.
        # Find any matches to M1x1 to start with.
        r = re.compile(r'(.*)1x1')
        first_entries = list(filter(r.match, v))

        # Now go through the list, to see how big the (square) matrix is.
        # Could generalise this to non-square matrices, if they're ever needed
        for i in first_entries:
            size = 1
            while (i[:-1] + str(size+1)) in v:
                size += 1
            matrices[i[:-3]] = "m{0}x{0}".format(str(size))

    # Delete duplicates from the original set of parameters
    keys = matrices.keys()
    added = [] # Dirty check to see a parameter's been added 
    for i in unsorted_params:
        present = False
        for k in keys:
            if k in i.name:
                present = True
                if k not in added:
                    added.append(k)
                    params.append(SpectrumParameter(k, "dimensionless", 
                                                    i.block, i.index, 
                                                    shape=matrices[k]))
            
        # If the parameter name doesn't match any of the matrix keys,
        # then just copy the parameter over from the unsorted list
        if not present:
            params.append(i)
        else: continue

    # Now add some Standard Model stuff that's in every SimpleSpectrum, for now.
    if add_higgs:
        params.append(SpectrumParameter("vev", "mass1", shape="scalar", 
                                        block="VEVS", sm=True))

    # Add gauge couplings and Yukawas here
    params.append(SpectrumParameter("g1", "dimensionless", block="GAUGE", 
                                    index=1, shape="scalar", sm=True))
    params.append(SpectrumParameter("g2", "dimensionless", block="GAUGE", 
                                    index=2, shape="scalar", sm=True))
    params.append(SpectrumParameter("g3", "dimensionless", block="GAUGE", 
                                    index=3, shape="scalar", sm=True))
    params.append(SpectrumParameter("sinW2", "dimensionless", block="SINTHETAW",
                                    shape="scalar", sm=True))
    params.append(SpectrumParameter("Yd", "dimensionless", block="YD", 
                                    shape="m3x3", sm=True))
    params.append(SpectrumParameter("Yu", "dimensionless", block="YU", 
                                    shape="m3x3", sm=True))
    params.append(SpectrumParameter("Ye", "dimensionless", block="YE", 
                                    shape="m3x3", sm=True))
    
    return params


def add_masses_to_params(parameters, bsm_particle_list, gambit_pdgs, add_higgs):
    """
    Adds the pole masses to the list of parameters. 
    If the parameter name exists already, it is removed.
    Double counting is known to occur in the following circumstances:

      1) FeynRules: a shared tree-level mass term for a multiplet.

    """

    parameters_by_name = [x.name for x in parameters]

    for i in range(len(bsm_particle_list)):
        p = bsm_particle_list[i]
        
        # Mass block convention is the index of a *pole mass* is the PDG code
        index = p.PDG_code 
        block = "MASS"

        # Check to see if the parameter name is in the list of model parameters 
        # currently. If it is, remove it
        if p.mass in parameters_by_name:
            for i, o in enumerate(parameters):
                if o.name == p.mass:
                    block = o.block
                    index = o.index
                    del parameters[i]
                    break

        # Overwrite the parameter name for the Higgs mass, 
        # to match the name within GAMBIT, 
        # if this is a 1HDM.
        if p.PDG_code == 25: 
            if add_higgs:
                p.mass = "mH"

        mass = "m"+pdg_to_particle(p.PDG_code, gambit_pdgs).strip('~')

        # Add the new parameter to the list of model parameters.
        # Save the particle name as 
        x = SpectrumParameter(mass, "Pole_Mass", gb_input=p.mass, block=block, 
                              index=index, shape="scalar", 
                              fullparticlename = pdg_to_particle(p.PDG_code, 
                                                                 gambit_pdgs)
                              )
        parameters.append(x)

    return parameters


###########
## SARAH ##
###########

def sarah_part_to_gum_part(particles):
    """
    Converts all SARAH::SARAHParticle to GUM::Particle.
    """
    
    sm_list = []
    bsm_list = []
    add_higgs = False

    all_pdgs = [x.pdg() for x in particles]
    # If the SM higgs included but not a second Higgs, 
    # then we want a dependency on StandardModel_Higgs.
    # If it is a 2+HDM then we don't.
    if 25 in all_pdgs and 35 not in all_pdgs: 
        add_higgs = True
    
    for i in range(len(particles)):
        part = particles[i]
        if particles[i].SM():
            sm_list.append(Particle(part.name(), part.antiname(),
                            part.spinX2(), part.pdg(),
                            part.mass(), part.chargeX3(), part.color(),
                            part.alt_name(), part.alt_mass(), part.tree_mass()))
        else:
            bsm_list.append(Particle(part.name(), part.antiname(),
                            part.spinX2(), part.pdg(),
                            part.mass(), part.chargeX3(), part.color(),
                            part.alt_name(), part.alt_mass(), part.tree_mass()))
    
    return sm_list, bsm_list, add_higgs

def sarah_params(paramlist, mixings, add_higgs, gambit_pdgs,
                 particles, boundary_conditions):
    """
    Removes all Standard Model parameters from those we wish
    to add to the GAMBIT model. This utilises the 'BlockName'
    tag (i.e. the SLHA Block the parameters will be placed in)
    to distinguish between Standard Model parameters, and 
    parameters the user has implemented in their own SARAH
    model file.

    Behaviour mimics the default imported SARAH conventions, which
    for some strange reason uses the description tag of parameters
    as protected variables. 
    The procudure is:
    - read in a new model
    - read in $SARAH/Models/parameters.m (and particles.m)
    - overwrite any parameter definitions that have the same
     *descriptions* in both files with that from the defaults.
    Anything that is given in the following blocks will be ignored:

    'SMINPUTS', 'CKMBLOCK', 'SM', 'VCKM', 'GAUGE', 'YE', 'YU', 'YD'...
    
    Everything else is fair game. 

    Default assumption is that everything is a dimensionless
    parameter. 
    TODO. This is a problem for SARAH, and actual spectrum objects.
    Hmmm......
    Maybe worth adding a new parameter tag, like Par::unspecified.
    """

    params = []

    # Convert the C++ dict to python properly
    mixingdict = dict((m.key(),m.data()) for m in mixings)
    bcs = dict((bc.data(),bc.key()) for bc in boundary_conditions)
    
    # List of parameters which have been added. Dupes can arise
    # from the Pole_Mixings for multiple particles
    addedpars = []

    # Save the SM vev name, we might need it
    smvevname = "vev"

    # Add all parameters from the parameter list from SARAH
    for i in range(len(paramlist)):
        p = paramlist[i]

        # If it's the Higgs vev, don't add it! We'll do it ourselves. 
        # Save the name though.
        if add_higgs and p.block() == "HMIX" and p.index() == 3:
            smvevname = p.name()
            continue

        # Remove SM parameters here
        # TODO: SM is not a SLHA block. SM parameters are in sminputs
        # Parameters in this made-up SM block are not actually fixed
        #if (    (p.block().lower() != 'sm')
        #    and (p.block().lower() != 'sminputs')
        if (    (p.block().lower() != 'sminputs')
            and (p.block().lower() != 'vckm')
            and (p.block().lower() != 'gauge')
            and (p.block().lower() != 'ye')
            and (p.block().lower() != 'yu')
            and (p.block().lower() != 'yd')
            ):

            # Mixing matrices
            tag = "Pole_Mixing" if (p.is_output() == True and 
                p.shape().startswith("m")) else "dimensionless"

            name = p.name()

            # If the parameter has a boundary condition, share the default value
            default = p.defvalue()

            if name in bcs.keys(): 
                 default = [param.defvalue() for param in paramlist if param.name() == bcs[name] or param.alt_name() == bcs[name]]
                 if default:
                    default = default[0]
                 else:
                    default = 0.1
            elif p.alt_name() in bcs.keys():
                 default = [param.defvalue() for param in paramlist if param.name() == bcs[p.alt_name()] or param.alt_name() == bcs[p.alt_name()]]
                 if default:
                    default = default[0]
                 else:
                    default = 0.1

            # If there are more than one parameter with the same name, take 
            # the not default one
            if default == 0.1:
                other_defaults = [param.defvalue() for param in paramlist if 
                                  param.name() == name or 
                                  param.alt_name() == name]
                default = [d for d in other_defaults if d != 0.1]
                if default:
                    default = default[0]
                else: 
                    default = 0.1

            # Create a new instance of SpectrumParameter
            x = SpectrumParameter(name, tag, block=p.block(),
                                  index=p.index(), alt_name = p.alt_name(),
                                  bcs = p.bcs(), shape = p.shape(), 
                                  is_output = p.is_output(), 
                                  is_real = p.is_real(), default = default)
            params.append(x)
    
    # Now add some Standard Model stuff that's in every SimpleSpectrum, for now.
    if add_higgs:
        params.append(SpectrumParameter(smvevname, "mass1", shape="scalar", 
                                        sm=True, is_real=True, block="HMIX",
                                        index=3))

    params.append(SpectrumParameter("g1", "dimensionless", block="GAUGE", 
                                    index=1, shape="scalar", sm=True, 
                                    is_real=True))
    params.append(SpectrumParameter("g2", "dimensionless", block="GAUGE", 
                                    index=2, shape="scalar", sm=True, 
                                    is_real=True))
    params.append(SpectrumParameter("g3", "dimensionless", block="GAUGE", 
                                    index=3, shape="scalar", sm=True, 
                                    is_real=True))
    params.append(SpectrumParameter("sinW2", "Pole_Mixing", shape="scalar", 
                                    sm=True, is_real=True))
    # TODO: TG: Yukawas do not seem to be real, at least for the test model
    params.append(SpectrumParameter("Yd", "dimensionless", block="YD", 
                                    shape="m3x3", sm=True, is_real=False))
    params.append(SpectrumParameter("Yu", "dimensionless", block="YU", 
                                    shape="m3x3", sm=True, is_real=False))
    params.append(SpectrumParameter("Ye", "dimensionless", block="YE", 
                                    shape="m3x3", sm=True, is_real=False))
    
    return params




##################
# Other routines #
##################

def sort_params_by_block(parameters, mixings):
    """
    Returns a dictionary of the LH blocks of a new model,
    with all entries.

    The dict looks like: 

    {
        # A block with many entries
        SMINPUTS : { 1: alphainv, 2: GF, 3: alphaS, ... }, 

        # A block with just one entry, i.e. matrices:
        YE : { matrix: 3x3 },         # e.g. Yukawas

        # A matrix block with a different outputname in SPheno,
        # e.g. for the THDM
        SCALARMIX : { mixingmatrix: 2x2, outputname: ZH }
        ...
    }
    """

    params_by_block = {}

    for par in parameters:

        # If there's no block, we can't really add it to this dict.
        if not par.block:
            continue

        shape = par.shape

        matrix = False
        vector = False
        if shape:
            if shape.startswith('m'): 
                matrix = True
            elif shape.startswith('v'):
                vector = True

        try:
          mixings[par.name]
          is_mixing = True
        except:
          is_mixing = False

        # If it's a matrix then it will be a new block
        if matrix:
            # if it's a mixing matrix, save the outputname (SPheno) and the
            # particle eigenstates (as known by SARAH) to the entry.
            if par.is_output and is_mixing :
                newentry = { "mixingmatrix": shape[1:], 
                             "outputname": par.name,
                             "particles" : mixings[par.name] }
            else:
                newentry = { "matrix": shape[1:], 
                             "outputname": par.name }
            params_by_block[par.block] = newentry

        # If it's not a matrix, it could be a vector, and it will be a new block
        elif vector:
            newentry = { "vector": shape[1:],
                         "outputname": par.name }
            params_by_block[par.block] = newentry

        # If it's not a matrix or a vector and is a new block, then create the entry
        elif par.block not in params_by_block:
            newentry = { par.index : par.name }
            params_by_block[par.block] = newentry

        # If the block already exists, add to it
        elif par.block in params_by_block:
            params_by_block[par.block][par.index] = par.name

    return params_by_block

def parameter_reality_dict(parameters):
    """
    Get a dict of whether a parameter is most definitely real, or not.
    """

    reality_dict = {}

    for param in parameters:
        reality_dict[param.name] = param.is_real

    return reality_dict

def spheno_dependencies(sphenodeps):
    """
    Clean the spheno dependencies scraped from SARAH.
    Here 'clean' means tidying up the CForm output Mathematica gives us.
    Returns a dict of parameter-definition key-value pairs.
    """    

    deps = {}

    # each p is an instance of SARAHParameter
    for p in sphenodeps:

        # Don't need the block. index etc, we're using internal SPheno params
        name = p.name() # As known to SPheno

        description = p.alt_name()

        # Common replacements to actual C(++) syntax
        # Probably not complete, but the main culprits *should* be here
        description = re.sub('ArcSin', 'asin', description)
        description = re.sub('ArcCos', 'acos', description)
        description = re.sub('ArcTan', 'atan', description)
        description = re.sub('Abs', 'abs', description) 
        description = re.sub('Sin', 'sin', description)
        description = re.sub('Cos', 'cos', description)
        description = re.sub('Tan', 'tan', description)
        #description = re.sub('Power', 'pow', description)
        description = re.sub('Sqrt', 'sqrt', description)

        # If there's something that looks like param(i,j) make this (param)(i,j)
        description = re.sub(r'([a-zA-Z]+)\(([0-9]),([0-9])\)',r'(*\1)(\2,\3)',
                             description)

        # If there's Power(param, num) -> pow(*param, num)
        description = re.sub(r'Power\(([a-zA-Z]+),([0-9])\)',r'pow(*\1,\2)',
                             description)

        deps[name] = description

    return deps
