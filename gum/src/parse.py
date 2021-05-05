#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Contains all routines for parsing input .gum files and 
#  the SARAH/FeynRules model files.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019, 2020
#
#  \author Pat Scott
#          (pat.scott@uq.edu.au)
#  \date 2018, 2019
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2020 Jan
#
#  **************************************


# TODO add mass dimension for new parameters in .gum file

import yaml
import re
from distutils.dir_util import copy_tree
from collections import defaultdict

from .setup import *
from .cmake_variables import *

"""
.GUM FILE PARSING
"""

class Inputs:
    """
    All the inputs from the .GUM file. Returns the master
    "gum" object used internally.
    """

    def __init__(self, model_name, base_model, mathpackage,
                 wimp_candidate, invisibles, decaying_dm = False,
                 mathname = None, lagrangian = None, restriction = None):

        self.name = model_name.replace('-','_')
        self.base_model = base_model

        # Set the DM PDG code from either the decaying DM or WIMP candidate
        if decaying_dm:
            self.dm_pdg = decaying_dm
            self.dm_decays = True
        else:
            self.dm_pdg = wimp_candidate
            self.dm_decays = False

        self.invisibles_pdg = invisibles
        self.math = mathpackage
        self.restriction = None
        self.LTot = lagrangian
        self.spec = "{0}_spectrum".format(model_name.replace('-','_'))

        # If we want the new GAMBIT model to have a different 
        # name than the model file from Mathematica
        if mathname:
            self.mathname = mathname
        else:
            self.mathname = model_name

        if restriction:
            self.restriction = restriction
        else:
            self.restriction = ''


class Outputs:
    """
    Outputs for GUM to write.
    """

    def __init__(self, mathpackage, calchep = False, pythia = False,
                 micromegas = False, spheno = False,
                 vevacious = False, ufo = False, options = {}):

        self.ch = calchep
        self.pythia = pythia
        self.mo = micromegas
        self.spheno = spheno
        self.vev = vevacious
        self.ufo = ufo
        self.options = options

        # Overwrite these, as the output does not exist.
        if mathpackage == 'feynrules':
            self.spheno = False
            self.vev = False

        # If Pythia is set then we also have UFO files, of course
        if pythia == True: self.ufo = True

        # If vevacious is needed, we have to have SPheno too...
        if vevacious == True and spheno == False:
            raise GumError(("\n\nCurrently, gum needs SPheno output to be able "
                            "to produce Vevacious output.\nPlease change "
                            "your .gum file (and SARAH files, if necessary)."))

    def bes(self):
        backends = []
        if self.ch: backends.append('calchep')
        if self.pythia: backends.append('pythia')
        if self.mo: backends.append('micromegas')
        if self.spheno: backends.append('spheno')
        if self.vev: backends.append('vevacious')
        if self.ufo: backends.append('ufo')
        return backends


def check_gum_file(inputfile):
    """
    Checks the input .GUM file for all necessary inputs.
    """

    print("Attempting to parse {0}...".format(inputfile))

    if inputfile.endswith(".gum"):
        pass
    else:
        if inputfile.endswith(".mug"):
            raise GumError(("\n\nGUM called with a .mug file in normal mode --"
                            " you probably want to call gum with the -r flag:"
                            "\n\n  ./gum -r " + inputfile + "\n"))
        else:
            raise GumError("\n\nInput filetype must be .gum.")

    with open(inputfile, "r") as f:
        try:
            data = yaml.safe_load(f)
        except yaml.YAMLError as exc:
            print(exc)

        if not 'math' in data:
            raise GumError(("\n\n'math' node needed in .gum file."))

        if not 'package' in data['math']:
        # Don't know what to run...!
            raise GumError(("\n\nNo mathpackage input - what do you expect "
                            "GUM to do? Please check your .gum file. "
                            "Supported entries: sarah, feynrules."))

        if data['math']['package'] not in ["sarah", "feynrules"]:
            raise GumError(("\n\nYou must specify which mathpackage you want "
                            "GUM to use. Please check your .gum file. "
                            "Supported entries: sarah, feynrules."))

        if not 'model' in data['math']:
            raise GumError(("\n\nNo model file specified. "
                            "Please check your .gum file."))

        if not 'output' in data:
        # Don't know what to generate!
            raise GumError(("\n\nNo output specified! You need to tell GUM "
                            "what it is you'd like it to do!\n"
                            "Please change your .gum file!"))

    print("All required YAML nodes present...")

    return data

def fill_gum_object(data):
    """
    Returns a model of type Inputs for GUM to work with. 'data' is the
    parsed data from check_gum_file.
    """

    math = data['math']
    mathpackage = math['package']
    lagrangian = ""
    if mathpackage == "feynrules":
        if 'lagrangian' in data['math']:
            # Check the Lagrangian makes sense (i.e. is all alphanumeric)
            lagrangian = data['math']['lagrangian']
            L = lagrangian.split('+')
            for l in L:
                if not l.strip(' ').isalnum():
                    raise GumError(("Non-alphanumeric character detected in "
                                    " the Lagrangian. Please check your .gum "
                                    "file."))
        else:
            raise GumError(("\n\nYou must specify the Lagrangian for your "
                            "model!\n This can be either a single entry like "
                            "'LTotal', or a sum of strings, like 'LSM + LDM'. "
                            "Please amend your .gum file."))

    gambit_model = math['model']

    # Overwrite the GAMBIT model if specified
    mathname = ""
    if 'gambit_opts' in data:
        if 'model_name' in data['gambit_opts']:
            mathname = gambit_model
            gambit_model = data['gambit_opts']['model_name']

    # FeynRules specific -- a "base" model to build a pheno model on top of.
    # Typically this is the SM, plus the BSM contribution defined in a 
    # separate file.
    if 'base_model' in data['math']:
        base_model = data['math']['base_model']
    else:
        base_model = ""

    if 'wimp_candidate' in data:
        wimp_candidate = data['wimp_candidate']
    else:
        wimp_candidate = None

    if 'invisibles' in data:
        invisibles = data['invisibles']
    else:
        invisibles = []

    backends = ['calchep', 'pythia', 'spheno', 'ufo',
                'micromegas', 'vevacious']

    opts = {}
    # The outputs GUM should hook up to GAMBIT, if specified
    if 'output' in data:
        for i in backends:
            if i in data['output']:
                opts[i] = data['output'][i]
            else:
                opts[i] = False
        if all(value == False for value in list(opts.values())):
            raise GumError(("\n\nAll backend output set to false in your .gum "
                            "file.\nGive GUM something to do!\n"
                            "Please change your .gum file."))

    options = {}
    # Options for the outputs declared
    if 'output_options' in data:
        for output in data['output_options']:
            if output not in opts.keys():
                raise GumError(("\n\nOptions given to output " + output + " "
                                "which is not declared as gum output.\n"
                                "Please change your .gum file."))
            options[output] = data['output_options'][output]

    # If we've got this far, we'll also force some decays to be written,
    # either by SPheno or by CalcHEP.
    # N.B. vevacious is conditional on SPheno
    # This now means if any of: Pythia(ufo) or MicrOMEGAs are requested, 
    # then we'll default to activating CalcHEP (unless SPheno requested)
    set_calchep = True
    if mathpackage == 'sarah' and opts['spheno'] == True:
        set_calchep = False
    if set_calchep: 
        opts['calchep'] = True

    outputs = Outputs(mathpackage, options=options, **opts)

    # See if we're told DM is a decaying particle or not...
    if 'decaying_dm_candidate' in data:
        decaying_dm = data['decaying_dm_candidate']
    else:
        decaying_dm = None

    # If decaying DM + WIMP candidate -> throw error
    if decaying_dm and wimp_candidate:
        raise GumError(("\n\nYou have specified both a WIMP candidate and "
                        "a decaying DM candidate.\nGUM can only handle one "
                        "of these at present. Please amend your .gum file.\n"))

    # If the user wants MicrOMEGAs output but hasn't specified a DM candidate
    if not (wimp_candidate or decaying_dm) and outputs.mo:
        raise GumError(("\n\nYou have asked for MicrOMEGAs output but have not "
                        "specified which particle is meant to be the DM "
                        "candidate! Please add an entry to your .gum file "
                        "like:\n\nwimp_candidate: 9900001 "
                        "# <--- Desired PDG code here.\n"))

    # FeynRules restriction files
    restriction = None
    if 'restriction' in math and mathpackage == 'feynrules':
        restriction = math['restriction']

    gum_info = Inputs(gambit_model, base_model, mathpackage, 
                      wimp_candidate, invisibles, decaying_dm,
                      mathname, lagrangian, restriction)

    print("Parse successful.")

    return gum_info, outputs

"""
FEYNRULES PARSING
"""

def parse_feynrules_model_file(model_name, base_model, outputs):
    """
    Parses a FeynRules model file. Checks for the following:
        - Every parameter has an LH block and an index
        - No particles have an external name with underscores etc.
        - Every parameter has an interaction order specified *if* the user
          requests UFO output
        - ComplexParameters and CalcHEP output

    TODO check base_model too
    """

    # Figure out the path pointing to the FeynRules file
    # First - check for it in the FeynRules directory 
    fr_file_path = FEYNRULES_PATH + ("/Models/{0}/{0}.fr").format(model_name)

    # If it doesn't exist, try the GUM models folder
    if not os.path.isfile(fr_file_path):
        fr_file_path = GUM_DIR + ("/Models/{0}/{0}.fr").format(model_name)
        if not os.path.isfile(fr_file_path):
            raise GumError(("GUM Error: Unable to find the model {0} in either "
                            "the FeynRules model directory, or the GUM model "
                            "directory!\nPlease move it to one of "
                            "these locations.").format(model_name))

    payattn = False

    # Read the input in
    with open(fr_file_path, 'r') as f:
        lines = f.readlines()

    # Flatten the string
    contents = "".join(lines).replace("\n","")

    # Parse the contents

    # 1. Parameters
    blocks = {}
    interactionorders = {}

    # Remove all the stuff before parameters
    s1 = contents[contents.find('M$Parameters'):]

    # Search through the string and count the number of curly braces. 
    # When we get to zero then we're done.
    numbraces = 0
    started = False
    commenting = False
    s2 = ""
    for i in range(len(s1)):
        char = s1[i]
        chars = s1[i] + s1[i+1]
        if numbraces > 0: started = True
        if char == "{" and not commenting:   numbraces += 1
        elif char == "}" and not commenting: numbraces -= 1
        # Don't count braces if we're in a comment, just in case someone is 
        # truly twisted
        elif chars == "(*" or chars == "*)": commenting = not commenting
        if started: s2 += char
        if numbraces == 0 and started: break

    # Get the param names
    params = []
    for i in s2.split('==')[:-1]:
        params.append( i.strip(' ').split(' ')[-1])

    # Add two curly braces to the params, as we're done now, to extract
    # information for the last parameter
    params.append('\}\s*\}')
    
    # Get the contents between each parameter
    matches = []
    for i in range(len(params)-1):
        pat = r'{}\s*==\s*(.*?){}'.format(params[i], params[i+1])
        if re.search(pat, s2):
            matches.append( re.search(pat, s2).group(1) )
        else:
            raise GumError(("Can't get the parameter definition for "
                            "the parameter {0}.\n"
                            "I tried using the pattern: {1}."
                            ).format(params[i], pat))

    for i in range(len(matches)):
        match = matches[i]
        paramtype = re.search(r'ParameterType\s*->(.*?),', match)
        p = paramtype.group(1).strip(' ')
        blockmatch = re.search(r'BlockName\s*->(.*?),', match)
        ordermatch = re.search(r'OrderBlock\s*->(.*?),', match)
        if blockmatch:
            if ordermatch: 
                blocks[ params[i] ] = { blockmatch.group(1).strip(' ') : 
                                        ordermatch.group(1).strip(' ') }
            else:
                blocks[ params[i] ] = blockmatch.group(1).strip(' ')
        # Don't need a blockname if it's an internal parameter
        elif not blockmatch and p == "Internal":
            pass
        # But if it's external and no block - gum can't use it
        else:
            raise GumError(("No BlockName specified for the parameter "
                            "{0}. GUM and GAMBIT need this information "
                            "so please change your .fr file!"
                            ).format(params[i]))
        interactionmatch = re.search(r'InteractionOrder\s*->\s*\{(.*?),(.*?)\}',
                                     match)
        if interactionmatch:
            interactionorders[ params[i] ] = interactionmatch.group(1).strip(' ')
        elif not interactionmatch and p == "Internal":
            interactionorders[ params[i] ] = p
        elif blockmatch.group(1).strip(' ').lower() == "yukawa":
            interactionorders[ params[i] ] = "yukawa"       
        elif blockmatch.group(1).strip(' ').lower() == "ckmblock":
            interactionorders[ params[i] ] = "ckm"
        else:
            interactionorders[ params[i] ] = "NULL"

        # Does it have an external name?
        # First try and match a set of parameter names
        #print match
        paramname = re.search(r'ParameterName\s*->\s*\{(.*?)\}', match)
        alnums = ""
        # This is the case where the ParameterName is a list, so parse like one
        if paramname:
            pn = paramname.group(1)
            # Pattern looks like: parameter[i,j] -> ...
            pattern = r'{}\[(\d),(\d)]\s*->\s*((.*?)+)(,|$)'.format(params[i])
            if re.findall(pattern, pn):
                defs = re.findall(pattern, pn)
                for d in defs:
                    alnums += ''.join(x for x in d[2] if not x.isalnum() 
                                      and not x == '_')
            else:
                raise GumError(("Can't parse the ParameterName entry for "
                                "the parameter {0}.").format(params[i]))

        else:
            paramname = re.search(r'ParameterName\s*->(.*?),', match)
            if paramname:
                # Does it have any non-alphanumeric characters?
                pn = paramname.group(1).strip(' ')
                alnums = ''.join(x for x in pn if not x.isalnum() 
                                 and not x == '_')
        if alnums:
            raise GumError(("Non-alphanumeric characters found in the "
                            "ParameterName entry for parameter {0}.\n"
                            "Please change this entry."
                            ).format(params[i]))


    justblocks = []
    paramsbyblock = {}
    # Go through blocks and check for no double definitions
    for param, blockentry in iteritems(blocks):
        if isinstance(blockentry, dict): 
            for block, index in iteritems(blockentry):
                if block in paramsbyblock:
                    l = paramsbyblock[block] # This is a list
                    if index in l:
                        raise GumError(("Index {0} defined twice for the "
                                        "block {1}.\nPlease change your "
                                        "FeynRules file.").format(index, block))
                    else:
                        l.append(index)
                        paramsbyblock[block] = l
                else:
                    paramsbyblock[block] = [index]
        else:
            if blockentry in justblocks:
                raise GumError(("The block {0} (with no entry) already exists."
                                "\nPlease add some indices to all entries with "
                                "this block in your FeynRules file."
                                ).format(blockentry))
            justblocks.append(blockentry)

    # Check for InteractionOrder
    # If it's Yukawa or CKM then this will work fine. Demand it for the rest.
    if outputs.ufo:
        for param, orders in iteritems(interactionorders):
            if orders in ["Internal", "yukawa", "ckm"]:
                continue
            if orders == "NULL":
                raise GumError(("No interaction order specified for the "
                                "parameter {0}, and you have asked for UFO "
                                "output. If you want to use UFO output, every "
                                "parameter needs an InteractionOrder specified."
                                " Please consult the FeynRules and/or MadGraph "
                                "manuals for details.").format(param))

    # 2. Particles
    smpdgs = [1, 2, 3, 4, 5, 6,        # Quarks
              11, 12, 13, 14, 15, 16,  # Leptons
              21, 22, 23, 24,          # Gauge bosons
              25,                      # SM Higgs
              82, 250, 251             # SM Ghosts
              ]

    # Remove all the stuff before parameters
    s3 = contents[contents.find('M$ClassesDescription'):]

    # Search through the string and count the number of curly braces. 
    # When we get to zero then we're done.
    numbraces = 0
    started = False
    commenting = False
    s4 = ""
    for char in s3:
        if numbraces > 0: started = True
        if char == "{" and not commenting:   numbraces += 1
        elif char == "}" and not commenting: numbraces -= 1
        # Don't count braces if we're in a comment, just in case someone is 
        # truly twisted
        elif char == "\"": commenting = not commenting
        if started: s4 += char
        if numbraces == 0 and started: break

    # Get the particles names
    particles = []
    for i in s4.split('==')[:-1]:
        particles.append( i.strip(' ').split(' ')[-1])
    
    # Get the contents between each parameter
    partmatches = []
    for i in range(len(particles)-1):
        p1 = particles[i].replace('[',r'\[').replace(']',r'\]')
        p2 = particles[i+1].replace('[',r'\[').replace(']',r'\]')
        pat = r'{}(.*?){}'.format(p1, p2)
        partmatches.append( re.search(pat, s4).group(1) )
    partmatches.append( s4[s4.find(particles[-1]):])

    for i in range(len(partmatches)):
        # PDG codes for ghosts don't matter
        if re.match(r'U\[\d*\]', particles[i]):
            continue
        match = partmatches[i]
        # Unphysical fields don't matter either
        unphysmatch = re.search(r'Unphysical\s*->\s*True', match)
        if unphysmatch:
            continue
        partmatch = re.search(r'ClassName\s*->(.*?),', match)
        if not partmatch:
            raise GumError(("The particle with description {0} "
                            "does not have a class name. Your FeynRules "
                            "file shouldn't work..."
                             ).format(particles[i]))
        # Try to match a set of PDG codes first
        pdgmatch = re.search(r'PDG\s*->\s*\{(.*?)\}\s*', match)
        if not pdgmatch:
            pdgmatch = re.search(r'PDG\s*->(.*?)\s*,', match)

        if not pdgmatch:
            raise GumError(("Particle {0} does not have a PDG code; "
                            "please give it one in your .fr file, as "
                            "GUM and GAMBIT need this information."
                            ).format(particles[i]))

        # Is it self-conjugate?
        sc = None
        scmatch = re.search(r'SelfConjugate\s*->\s*(\w+)', match)
        if scmatch:
            sc = scmatch.group(1).strip(' ')

        # Try to get the quantum numbers - but only if it's a BSM particle.
        # First get those PDG codes.
        pdgcodes = [int(s) for s in re.split(',| ', pdgmatch.groups()[0]) 
                    if s.isdigit()]

        # Then - are they all in the SM PDG code list?
        if (set(map(abs, pdgcodes)) <= set(smpdgs)):
            continue
        # Also check to see if the particle is self-conjugate: if it is, 
        # it doesn't have electric charge, so doesn't matter
        elif sc == 'True':
            continue
        else:
            qnumsmatch = re.search(r'QuantumNumbers\s*->\s*{(.*?)}', match)
            if qnumsmatch:
                # Try to match the electric charge now.
                # Go for a fraction first.
                qmatch = re.search(r'Q\s*->\s*-?(\d+/\d+)', qnumsmatch.group(1))
                if not qmatch:
                    qmatch = re.search(r'Q\s*->-?\s*(\d+)', qnumsmatch.group(1))
                if qmatch:
                    continue
                else:
                    raise GumError(("Particle {0} does not have quantum numbers"
                                    " defined; GUM and GAMBIT need this info!"
                                    "\nPlease give it one in your .fr "
                                    "file, via the entry:\n\t "
                                    "QuantumNumbers -> {{Q -> ...}},\n"
                                    "and don't forget to assign a value to Q!"
                                    ).format(particles[i]))
            else:
                raise GumError(("Particle {0} does not have its electric "
                                "charge defined; GUM and GAMBIT need this "
                                "info!\nPlease give it one in your .fr "
                                "file, via the entry:\n\t "
                                "QuantumNumbers -> {{Q -> ...}}."
                                ).format(particles[i]))                    

    print("FeynRules file seems ok; firing up a Mathematica kernel...")

def parse_sarah_model_file(model_name, outputs):
    """
    Parses a SARAH model file. Checks for the following:
        - ...
    """

    # Figure out where the SARAH files live
    # First - check for them in the SARAH directory 

    sarahdir = SARAH_PATH + ("/Models/{0}/").format(model_name)
    gumdir = GUM_DIR + ("/Models/{0}/").format(model_name)
    sarahfolder = sarahdir

    sarah_file_path = sarahdir + ("{0}.m").format(model_name)
    # If it doesn't exist, try the GUM models folder
    if not os.path.isfile(sarah_file_path):
        sarah_file_path = gumdir + ("{0}.m").format(model_name)
        if not os.path.isfile(sarah_file_path):
            raise GumError(("GUM Error: Unable to find the model {0} in either "
                            "the SARAH model directory, or the GUM model "
                            "directory!\nPlease move it to one of "
                            "these locations.").format(model_name))
        # Copy the files to the SARAH directory, then we should be good to go
        copy_tree(gumdir, sarahdir)

    # Read the inputs in
    paramfile = sarahdir + "/parameters.m"
    partfile = sarahdir + "/particles.m"
    sphenofile = sarahdir + "/SPheno.m"

    if outputs.spheno:
        if not os.path.isfile(sphenofile):
            raise GumError(("No SPheno.m file found within the SARAH model "
                            "directory,\nbut SPheno output has been requested."
                            "\nPlease fix this...!"))

    with open(paramfile, 'r') as f:
        paramlines = f.readlines()

    with open(partfile, 'r') as f:
        partlines = f.readlines()

    # The hard-coded/protected descriptions for particles
    safeparticles = [
                    "Left Down-Squarks", 
                    "Right Down-Squarks", 
                    "Left Up-Squarks", 
                    "Right Up-Squarks", 
                    "Left Selectron", 
                    "Right Selectron", 
                    "Left Sneutrino",  
                    "Neutral Down-Higgs", 
                    "Charged Down-Higgs",
                    "Neutral Up-Higgs",
                    "Charged Up-Higgs",
                    "B-Boson",
                    "Gluon",
                    "W-Bosons",
                    "B-Boson Ghost",
                    "Gluon Ghost",
                    "W-Boson Ghost",
                    "Wino", 
                    "Bino", 
                    "Neutral Higgsinos",
                    "Charged Higgsinos",
                    "Down-Squarks",  
                    "Up-Squarks",
                    "Sleptons",   
                    "Sneutrinos",  
                    "Higgs",
                    "Pseudo-Scalar Higgs",
                    "Charged Higgs", 
                    "Photon", 
                    "Z-Boson",
                    "Gluon",
                    "W-Boson",
                    "W+ - Boson",
                    "Photon Ghost",
                    "Negative W-Boson Ghost",
                    "Positive W-Boson Ghost", 
                    "Positive W+ - Boson Ghost",
                    "Negative W+ - Boson Ghost", 
                    "Z-Boson Ghost",
                    "Gluino",
                    "Neutralinos",
                    "Charginos",
                    "Down-Quarks",
                    "Up-Quarks",
                    "Leptons",
                    "Neutrinos",
                    "Neutral Down-Higgsino",
                    "Neutral Up-Higgsino",
                    "Charged Down-Higgsino",
                    "Charged Up-Higgsino",
                    "Neutralino Weyl-Spinor",
                    "Negative Chargino Weyl-Spinor",
                    "Positive Chargino Weyl-Spinor",
                    "Gluino Weyl-Spinor",
                    "Wino Weyl-Spinor",
                    "Neutral Wino",
                    "Negative Wino",
                    "Positive Wino",
                    "Bino Weyl-Spinor",
                    "Left Electron", 
                    "Left Neutrino", 
                    "Right Electron", 
                    "Left Down-Quark", 
                    "Right Down-Quark", 
                    "Left Up-Quark", 
                    "Right Up-Quark", 
                    "Left-Neutrino-Masseigenstate", 
                    "Rotated Left Electron", 
                    "Rotated Right Electron", 
                    "Rotated Left Up-Quark", 
                    "Rotated Right Up-Quark", 
                    "Rotated Left Down-Quark", 
                    "Rotated Right Down-Quark", 
                    "Dirac Left Up-Quark",
                    "Dirac Right Up-Quark",
                    "Dirac Left Down-Quark",
                    "Dirac Right Down-Quark",
                    "Dirac Left Electron",
                    "Dirac Right Electron",
                    "Dirac Left Neutrino",
                    "Dirac Right Neutrino",
                    "Left Leptons", 
                    "Left Quarks", 
                    "Down-Higgsino", 
                    "Up-Higgsino", 
                    "Scalar Down", 
                    "Scalar Up", 
                    "Pseudo Scalar Down", 
                    "Pseudo Scalar Up", 
                    "Down-Higgs", 
                    "Up-Higgs", 
                    "Left Slepton", 
                    "Left Squark", 
                    "Right Electron Superfield", 
                    "Right Down-Quark Superfield", 
                    "Left Quark Superfield", 
                    "Right Up-Quark Superfield", 
                    "left Lepton Superfield", 
                    "Down-Higgs Superfield", 
                    "Up-Higgs Superfield", 
                    "Gluon Superfield", 
                    "B Superfield", 
                    "W Superfield", 
                    "Singlino", 
                    "Singlet", 
                    "Weyl Spinor of Singlino", 
                    "Scalar Singlet", 
                    "Pseudo Scalar Singlet", 
                    "Singlet Superfield",
                    "Scalar Sneutrino",
                    "Pseudo Scalar Sneutrino",
                    "Right Scalar Sneutrino",
                    "Right Pseudo Scalar Sneutrino",
                    "Right Neutrino",
                    "Right Sneutrino",
                    "Right Neutrino Superfield",
                    "CP-even Sneutrino",
                    "CP-odd Sneutrino",
                    "Bino'",
                    "B'-Boson",
                    "B'-Boson Ghost",
                    "Z'-Boson",
                    "Z'-Ghost",  
                    "Gravitino",
                    "Goldstino",
                    "Weyl Gravitino",
                    "Weyl Goldstino",
                    "W'-Boson",
                    "Negative W'-Boson Ghost",
                    "Positive W'-Boson Ghost"]

    # And for parameters
    safeparameters = [
                    "Hypercharge-Coupling", 
                    "Left-Coupling", 
                    "inverse weak coupling constant at mZ",
                    "Fermi's constant",
                    "electric charge",
                    "Weinberg-Angle",
                    "Strong-Coupling", 
                    "Alpha Strong", 
                    "Up-Yukawa-Coupling",
                    "Down-Yukawa-Coupling",
                    "Lepton-Yukawa-Coupling",
                    "Trilinear-Lepton-Coupling",
                    "Trilinear-Down-Coupling",
                    "Trilinear-Up-Coupling",
                    "Mu-parameter",
                    "Bmu-parameter",
                    "Hypercharge FI-Term", 
                    "Softbreaking left Squark Mass",
                    "Softbreaking right Slepton Mass",
                    "Softbreaking left Slepton Mass",
                    "Softbreaking right Up-Squark Mass",
                    "Softbreaking right Down-Squark Mass",
                    "Softbreaking Down-Higgs Mass",
                    "Softbreaking Up-Higgs Mass",
                    "Bino Mass parameter",
                    "Wino Mass parameter",
                    "Gluino Mass parameter",
                    "Down-VEV",
                    "Up-VEV", 
                    "EW-VEV",
                    "Pseudo Scalar mixing angle",
                    "Tan Beta" ,
                    "Scalar mixing angle",
                    "Photon-Z Mixing Matrix",
                    "W Mixing Matrix",
                    "Wino Mixing Matrix",
                    "Down-Squark-Mixing-Matrix",
                    "Up-Squark-Mixing-Matrix",
                    "Slepton-Mixing-Matrix",
                    "Neutralino Mixing-Matrix",
                    "Sneutrino Mixing-Matrix",
                    "Chargino-plus Mixing-Matrix",
                    "Chargino-minus Mixing-Matrix",
                    "Scalar-Mixing-Matrix", 
                    "Pseudo-Scalar-Mixing-Matrix", 
                    "Charged-Mixing-Matrix", 
                    "Left-Lepton-Mixing-Matrix", 
                    "Right-Lepton-Mixing-Matrix", 
                    "Left-Down-Mixing-Matrix", 
                    "Right-Down-Mixing-Matrix", 
                    "Left-Up-Mixing-Matrix", 
                    "Right-Up-Mixing-Matrix", 
                    "Neutrino-Mixing-Matrix", 
                    "PMNS Matrix", 
                    "CKM Matrix", 
                    "Complex CKM Matrix", 
                    "Wolfenstein Parameter eta", 
                    "Wolfenstein Parameter A", 
                    "Wolfenstein Parameter lambda", 
                    "Wolfenstein Parameter rho", 
                    "SCKM Up-Yukawa-Coupling",
                    "SCKM Down-Yukawa-Coupling",
                    "SCKM Trilinear-Down-Coupling",
                    "SCKM Trilinear-Up-Coupling",
                    "SCKM Softbreaking left Squark Mass",
                    "SCKM Softbreaking right Up-Squark Mass",
                    "SCKM Softbreaking right Down-Squark Mass",
                    "PMNS Electron-Yukawa-Coupling",
                    "PMNS Trilinear-Lepton-Coupling",
                    "PMNS Softbreaking right Slepton Mass",
                    "PMNS Softbreaking left Slepton Mass",
                    "Gluino-Phase",
                    "Theta'",
                    "U(1)' Gauge Coupling",
                    "Photon-Z-Z' Mixing Matrix",
                    "Photon-Z-Z' Mixing Matrix",
                    "B-L-Coupling", 
                    "Mixed Gauge Coupling 1",
                    "Mixed Gauge Coupling 2",
                    "Z' mass", 
                    "Bino' Mass",
                    "Mixed Gaugino Mass 1",
                    "Mixed Gaugino Mass 2",
                    "Mu' Parameter",
                    "B' Parameter",
                    "Bilepton 1 Soft-Breaking mass",
                    "Bilepton 2 Soft-Breaking mass",
                    "Bilepton 1 VEV",
                    "Bilepton 2 VEV",
                    "Bilepton VEV",
                    "Bilepton Scalar Mixing Angle",
                    "Bilepton Pseudo Scalar Mixing Angle",
                    "Neutrino-X-Yukawa-Coupling",
                    "Trilinear-Neutrino-X-Coupling",
                    "Bilepton Scalar Mixing Matrix",
                    "Bilepton Pseudo Scalar Mixing Matrix", 
                    "Singlet Self-Interaction",
                    "Softbreaking Singlet Self-Interaction",
                    "Singlet-Higgs-Interaction",
                    "Softbreaking Singlet-Higgs-Interaction",
                    "Softbreaking Singlet Mass", 
                    "Singlet-VEV", 
                    "Sneutrino-VEV",
                    "Right Sneutrino-VEV",
                    "Bilinear RpV-Parameter",
                    "Softbreaking Bilinear RpV-Parameter",
                    "Soft-breaking Higgs Slepton Mixing Term",
                    "Neutrino-Yukawa-Coupling",
                    "Trilinear-Neutrino-Coupling",
                    "Softbreaking right Sneutrino Mass",
                    "Weinberg Operator",
                    "Soft Breaking Weinberg Operator",
                    "SM Mu Parameter",
                    "SM Higgs Selfcouplings",
                    "SM Higgs Mass Parameter",
                    "Gravitino Mass",
                    "Planck Mass"]

    # 1. Parameters

    # Flatten the string
    contents = "".join(partlines).replace("\n","")

    # Remove all the stuff before the EWSB particle defs. All we need I think...
    s1 = contents[contents.find('ParticleDefinitions[EWSB]'):]

    # Search through the string and count the number of curly braces. 
    # When we get to zero then we're done.
    numbraces = 0
    started = False
    commenting = False
    s2 = ""
    for i in range(len(s1)):
        char = s1[i]
        chars = s1[i] + s1[i+1]
        if numbraces > 0: started = True
        if char == "{" and not commenting:   numbraces += 1
        elif char == "}" and not commenting: numbraces -= 1
        # Don't count braces if we're in a comment, just in case someone is 
        # truly twisted
        elif chars == "(*" or chars == "*)": commenting = not commenting
        if started: s2 += char
        if numbraces == 0 and started: break

    # Get the particle names
    # Pattern looks like:
    # {particlename, {...} }
    particles = {}
    pat = r'{\s*(.*?)\s*,\s*{(.*?)}\s*}\s*(,|$)'

    # Get all particle names + definitions 
    for match in re.findall(pat, s2):
        particles[match[0]] = match[1]

    # Any numerical dependences should be given in the parameters list, save 'em
    massdeps = defaultdict(list)

    for particle, entry in iteritems(particles):

        # The particle description
        desc = re.search(r'Description\s*->\s*"(.*?)"', entry)

        if not desc:
            raise GumError(("No description for particle {0}.\n"
                            "Please update your SARAH file.").format(particle))

        # PDG codes
        pdg = re.search(r'PDG\s*->\s*{(.*?)}', entry)

        # Mass
        # Try to get something between braces first
        mass = re.search(r'Mass\s*->\s*{(.*?)}', entry)
        if not mass:
            mass = re.search(r'Mass\s*->\s*(.*?)(,|$)', entry)

        # If there's no PDG code and no mass parameter, check to see if the
        # particle properties are defined elsewhere in SARAH. These are done by
        # the mutual "Description" field for some reason
        if not pdg or not mass:

            if desc:
                # If it's there - all good
                if desc.group(1) in safeparticles:
                    continue

            else:
                raise GumError(("There is either no PDG code or mass given for "
                                "particle {0}, and SARAH\n doesn't have it "
                                "internally defined. Please update your SARAH "
                                "file.").format(particle))

        # Check PDG code entry.

        # Get the PDG code(s)
        pdgcodes = pdg.group(1).split(',')
        pdgcodes = [int(x.strip(' ')) for x in pdgcodes]

        # If all PDG codes are 0 then these are unphysical particles: 
        # their entries don't matter...
        if all(pdg == 0 for pdg in pdgcodes): continue

        # Check the mass entry
        massentry = mass.group(1).split(',')
        massentry = [x.strip(' ') for x in massentry]

        # Acceptable entries for Mass:
        # ["Automatic", "LesHouches", numerical value (can be array), parameter name,
        # "Dependence" (this then requires the MassDependence entry)]
        for m in massentry:
            if not m.strip(' ') in ["LesHouches", "Automatic", "Dependence"] and not m.isdigit():
                massdeps[particle].append(m)

        # Electric charge -- we need this
        q = re.search(r'ElectricCharge\s*->\s*(.*?)', entry)

        if not q:
            raise GumError(("No electric charge defined for particle {0}.\n"
                            "Please update your SARAH file.").format(particle))
       
        # Output name -- this one's optional
        output = re.search(r'OutputName\s*->\s*"(.*?)"', entry)

        if output:
            # Check for no non-alphanumeric characters
            oname = output.group(1)
            alnums = ''.join(x for x in oname if not x.isalnum() 
                             and not x == '_')
            if alnums:
                raise GumError(("Non-alphanumeric characters found in the "
                                "OutputName entry for particle {0}.\n"
                                "Please change this entry."
                                ).format(particle))


    # 2. Parameters

    # Flatten the string
    contents = "".join(paramlines).replace("\n","")

    # Remove all the stuff before the EWSB particle defs. All we need I think...
    s1 = contents[contents.find('ParameterDefinitions'):]

    # Search through the string and count the number of curly braces. 
    # When we get to zero then we're done.
    numbraces = 0
    started = False
    commenting = False
    s2 = ""
    for i in range(len(s1)):
        char = s1[i]
        chars = s1[i] + s1[i+1]
        if numbraces > 0: started = True
        if char == "{" and not commenting:   numbraces += 1
        elif char == "}" and not commenting: numbraces -= 1
        # Don't count braces if we're in a comment, just in case someone is 
        # truly twisted
        elif chars == "(*" or chars == "*)": commenting = not commenting
        if started: s2 += char
        if numbraces == 0 and started: break

    # Get the parameter names
    # Pattern looks like:
    # {parametername, {...} }
    parameters = {}
    pat = r'{\s*(.*?)\s*,\s*{(.*?)}\s*}\s*(,|$)'
    # Get all particle names + definitions 
    for match in re.findall(pat, s2):
        parameters[match[0]] = match[1]

    for parameter, entry in iteritems(parameters):

        # The parameter description
        desc = re.search(r'Description\s*->\s*"(.*?)"', entry)

        # The output name
        output = re.search(r'OutputName\s*->\s*(.*?)\s*(,|})', entry)

        # Any dependence on other parameters?
        dep = re.search(r'DependenceNum\s*->\s*(.*?)\s*(,|})', entry)

        # LH block
        block = re.search(r'LesHouches\s*->\s*{(.*?)}', entry)
    
        if desc:
            # If it's there - all good, it's known to SARAH
            if desc.group(1) in safeparameters:
                continue
        # If not - check to see if there's an LH block (and entry) associated
        # with the parameter. If there's not, then we can't do anything. 
        else:
            if not block:
                raise GumError(("There is no LesHouches entry given for "
                                "parameter {0}, and SARAH\n doesn't have it "
                                "internally defined. Please update your SARAH "
                                "file.").format(parameter))

