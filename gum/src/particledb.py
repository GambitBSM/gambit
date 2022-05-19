#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Contains scripts for manipulating the particle database. This includes
#  scraping the information about existing particles as well as adding
#  new particles to the database.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019, 2020
#
#  **************************************

import yaml
import os
import itertools
import sys

from .setup import *

def get_gambit_particle_pdg_dict():
    """
    Return dict of GAMBIT particle names & PDG-context pairs from
    particle_database.yaml.
    """

    # TODO: Error checking of lengths of arrays etc.

    with open("./../config/particle_database.yaml", "r") as f:

        try:
            data = yaml.safe_load(f)
        except yaml.YAMLError as exc:
            print(exc)

    gambit_pdg_codes = {}
    decaybit_dict = {}

    # Firstly deal with particles
    particles = data['StandardModel']['Particles'] \
              + data['OtherModels']['Particles']

    for i in range(0, len(particles)):
    
        part = particles[i]

        # Filter out comments, etc. Only care about those with a 
        # PDG_context pair (plus a name).
        if 'PDG_context' in part:
            
            # Only add mass eigenstates
            if not (part['PDG_context'][1] == 0):
                continue
            
            PDG_code = part['PDG_context'][0]
        
            # If the particle is already in the dictionary, don't add it again
            if PDG_code in list(gambit_pdg_codes.values()):
                continue
                
            # Add to GAMBIT dict.
            gambit_pdg_codes[part['name']] = PDG_code

            # Add the conjugate as well.
            if 'conjugate' in part:
                gambit_pdg_codes[part['conjugate']] = -PDG_code

            # Is there a DecayBit entry?
            if 'DecayBit' in part:

                # If particle has decays
                if part['DecayBit']['Decays'] == True:

                    # If particle has DecayBit name specified
                    if 'name' in part['DecayBit']:
                        decaybit_dict[part['DecayBit']['name']] = PDG_code
                    else:
                        decaybit_dict[part['name']] = PDG_code

                    # Likewise for conjugates
                    if 'conjugate' in part:
                        if 'conjugate' in part['DecayBit']:
                            decaybit_dict[part['DecayBit']['conjugate']] = -PDG_code
                        else:
                            decaybit_dict[part['conjugate']] = -PDG_code

    # Now the particle sets
    sets = data['StandardModel']['Sets'] + data['OtherModels']['Sets']

    for i in range(0, len(sets)):
    
        cset = sets[i]

        if 'PDG_context' in cset:
        
            PDG_codes = [x[0] for x in cset['PDG_context']]
            
            # Only add mass eigenstates.
            # TODO - figure out what to do with e.g. nu_RPV.
            if not (cset['PDG_context'][0][1] == 0):
                continue
            
            for PDG_code in PDG_codes:
                        
                # Don't add duplicates. Shouldn't be any, anyway...
                if PDG_code in list(gambit_pdg_codes.values()):
                    continue
                    
                name = cset['name']
        
                for j in range(0, len(cset['PDG_context'])):
                    gambit_pdg_codes[name + "_" + str(j+1)] = cset['PDG_context'][j][0]
    
                if 'conjugate' in cset:
                    for j in range(0, len(cset['PDG_context'])):
                        gambit_pdg_codes[cset['conjugate'] + "_" + str(j+1)] = -cset['PDG_context'][j][0]
    
                # If a particle set has Decays
                if 'DecayBit' in cset:
    
                    # Do we care about the Decays?
                    if cset['DecayBit']['Decays'] == True:
    
                        # If the name is specified, use these
                        if 'name' in cset['DecayBit']:
    
                            # If each particle in the set has a different DecayBit
                            # rollcall name (e.g. Higgs, h0_2) then parse on a
                            # case-by-case
                            if type(cset['DecayBit']['name']) is list:
                                for j in range(0, len(cset['PDG_context'])):
                                    decaybit_dict[cset['DecayBit']['name'][j]] = cset['PDG_context'][j][0]
    
                            # Otherwise iterate over the set (part_1, part_2, etc.)
                            elif type(cset['DecayBit']['name']) is str:
                                for j in range(0, len(cset['PDG_context'])):
                                    decaybit_dict[cset['DecayBit']['name'] + "_" + str(j+1)] = cset['PDG_context'][j][0]
    
                        # If the name is unspecified, use the default
                        else:
                            if type(cset['name']) is list:
                                for j in range(0, len(cset['PDG_context'])):
                                    decaybit_dict[cset['name'][j]] = cset['PDG_context'][j][0]
    
                            elif type(cset['name']) is str:
                                for j in range(0, len(cset['PDG_context'])):
                                    decaybit_dict[cset['name'] + "_" + str(j+1)] = cset['PDG_context'][j][0]
    
                        # Conjugates
                        if 'conjugate' in cset:
    
                            # If specified names, use these
                            if 'conjugate' in cset['DecayBit']:
    
                                if type(cset['DecayBit']['conjugate']) is list:
                                    for j in range(0, len(cset['PDG_context'])):
                                        decaybit_dict[cset['DecayBit']['conjugate'][j]] = - cset['PDG_context'][j][0]
                                        
                                elif type(cset['DecayBit']['conjugate']) is str:
                                    for j in range(0, len(cset['PDG_context'])):
                                        decaybit_dict[cset['DecayBit']['conjugate'] + "_" + str(j+1)] = -cset['PDG_context'][j][0]
    
                            # Otherwise default
                            else:
    
                                if type(cset['conjugate']) is list:
                                    for j in range(0, len(cset['PDG_context'])):
                                        decaybit_dict[cset['conjugate'][j]] = - cset['PDG_context'][j][0]
                                elif type(cset['conjugate']) is str:
                                    for j in range(0, len(cset['PDG_context'])):
                                        decaybit_dict[cset['conjugate'] + "_" + str(j+1)] = -cset['PDG_context'][j][0]

    return gambit_pdg_codes, decaybit_dict

def check_all_particles_present(partlist, gambit_pdg_codes):
    """
    Checks all particles exist in the particle_database.yaml.
    """
    
    absent = []
    
    for i in range(len(partlist)):
        if not partlist[i].pdg() in list(gambit_pdg_codes.values()):
            absent.append(partlist[i])

    absent_by_pdg = [x.pdg() for x in absent]
    
    if len(absent) == 0:
        print("All particles are in the GAMBIT database.")
    else:
        print(("\nThe following particles (by PDG code) are missing from the "
               "particle database: {0}. GUM is now adding them to "
               "../config/particle_database.yaml.\n").format(absent_by_pdg))

    return absent
        

def add_new_particleDB_entry(particles, dm_pdg, gambit_pdg_codes,
                             decaybit_dict, reset_dict, modelname,
                             dm_decays):
    """
    Adds a list of particles to the particle database.
    """
    particleDB = (
           "# YAML file containing all particles for the particle database.\n\n"
           "# particle_database.cpp is constructed from this YAML file at compile time, via particle_harvester.py.\n\n"
           "# New entries should look like:\n"
           "#\n"
           "#   - name: \"X+\"                         The name used within GAMBIT, in the particleDB.\n"
           "#     PDG_context: [10, 4]                 The PDG-context pair used for a single particle.\n"
           "#     conjugate: \"X-\"                    The name for the conjugate particle, also added to the particleDB.\n"
           "#     description: \"New particle\"        Optional - adds a C++ comment to particle_database.cpp. For readability.\n"
           "#     chargex3: 0                          Three times the electric charge.\n"
           "#     spinx2: 1                            Twice the spin.\n"
           "#     color:  3                            The color representation (1 = singlet; 3 = triplet; 6 = sextet; 8 = octet).\n"
           "#     DecayBit:\n"
           "#       Decays: True                       Flag to show whether or not to include a particle's Decays in DecayBit.\n"
           "#       name: \"X_plus\"                   The name used as CAPABILITES in DecayBit_rollcall.hpp for the specific particle.\n"
           "#       conjugate: \"X_minus\"             And the name used for it's conjugate.\n"
           "#\n"
           "# The syntax for adding sets is identical - GAMBIT automatically numbers each particle in a set.\n"
           "#\n"
           "#   - name: \"h0\"\n"
           "#     PDG_context:\n"
           "#     - [25, 0]      (This line-by-line format is equivalent to a list of lists)\n"
           "#     - [35, 0]      Creates entries for \"h0_1\" and \"h0_2\" in the particleDB.\n"
           "#     DecayBit:\n"
           "#       Decays: True\n"
           "#       name: \"h0\"                       Creates rollcall entries for \"h0_1_decay_rates\" and \"h0_2_decay_rates\" CAPABILITIES.\n"
           "#       name: [\"Higgs\", \"h0_2\"]        Alternative syntax - if particles within sets have different names - creating CAPABILITIES \"Higgs_decay_rates\" and \"h0_2_decay_rates\".\n"
           "#\n"
           "# Note: If there is no entry for the 'DecayBit' field, GAMBIT will use the 'name' and 'conjugate' fields by default.\n"
           "# TODO: Decide if Decays belong here, or elsewhere (GUM)\n\n"
    )

    with open("./../config/particle_database.yaml", "r") as f:
        data = yaml.safe_load(f)
        
        for i in range(len(particles)):
            part = particles[i]

            # Check there is no clash of names here, otherwise macros will fail
            if part.name() in gambit_pdg_codes.keys():
                raise GumError(("\n\nClash of particle names with the "
                                "existing particle database in GAMBIT!\n"
                                "Please rename the particle {} in your "
                                "model file."
                                ).format(part.name()))

            # Add the new particle to the GAMBIT dicts
            gambit_pdg_codes[part.name()] = part.pdg()

            entry = {}

            entry['name'] = part.name()
            entry['PDG_context'] = [part.pdg(), 0] # Always assuming mass ES.

            # Add charge, color, spin
            entry['spinx2'] = part.spinX2()
            entry['chargex3'] = part.chargeX3()
            entry['color'] = part.color()
            entry['description'] = part.name() + " (" + modelname + ")"

            # Add conjugate field if it is distinct
            if not (part.name() == part.antiname()):
                entry['conjugate'] = part.antiname()
                # And add antiparticle to the PDG list
                gambit_pdg_codes[part.antiname()] = -part.pdg()

            # Add the entry to the reset dict so gum can remove them later
            # if called in reset mode.
            sig = part.name() + "|" + modelname # Signature to parse
            reset_dict['particles']['particles'].append(sig)

            # Assume a new particle decays *unless* it is explicitly given as
            # a dark matter candidate, or unless it's decaying DM.
            if dm_decays or (part.pdg() != dm_pdg and not dm_decays):

                # Add the new particle to the DecayBit dict too
                decaybit_dict[part.name()] = part.pdg()
                if (part.name() != part.antiname()):
                    decaybit_dict[part.antiname()] = -part.pdg()

                db = {'Decays': True}

                entry['DecayBit'] = db

                name = part.name()
                antiname = part.antiname()

                # Trim off stuff that would be illegal in a C++ function

                # Tildes: at the start, just strip the tilde -- this is a 
                # symmetry thing
                if name.startswith('~'):
                    name = name[1:]
                if antiname.startswith('~'):
                    antiname = antiname[1:]
                
                # FeynRules adds a tilde for a conjugate.
                if (name != antiname):
                    if (antiname.endswith('~') and '~' not in name):
                        antiname = antiname.strip('~') + 'bar'
                    elif (name.endswith('~') and '~' not in antiname):
                        name = name.strip('~') + 'bar'

                # Plus / minus (let's assume nothing more than triply charged..)
                for i in [name, antiname]:
                    if i.endswith('+++'):
                        i = i.strip('+++') + '_plusplusplus'                    
                    if i.endswith('++'):
                        i = i.strip('++') + '_plusplus'                
                    if i.endswith('+'):
                        i = i.strip('+') + '_plus'
                    if i.endswith('---'):
                        i = i.strip('---') + '_minusminusminus'
                    if i.endswith('--'):
                        i = i.strip('--') + '_minusminus'
                    if i.endswith('-'):
                        i = i.strip('-') + '_minus'

                # Add 'name' and 'conjugate' fields to DecayBit entry.
                db['name'] = name
                if (antiname != name):
                    db['conjugate'] = antiname


            # Add new entry to the data structure
            data['OtherModels']['Particles'].append(entry)

    # Overwrite the particle database file
    particleDB += yaml.dump(data).replace('\n  - ', '\n\n  - ')

    return gambit_pdg_codes, decaybit_dict, particleDB

def write_particleDB(particleDB):
    """
    Write the new particle DB to file, overwriting the existing one
    """

    with open("./../config/particle_database.yaml", "w") as f:
        f.write(particleDB)


def get_antiparticles(partlist):
    """
    Retuns a dictionary of (k, v) = (particle, antiparticle)
    by PDG code. k==v for self-conjugate particles.
    """

    conjdict = {}

    for i in range(len(partlist)):
        p = partlist[i]

        # If it's self-conjugate, just add it once
        if ( p.name() == p.antiname() ):
            conjdict[p.pdg()] = p.pdg()

        # Otherwise add both ways
        else:
            conjdict[p.pdg()] = -p.pdg()
            conjdict[-p.pdg()] = p.pdg()

    return conjdict

def get_higgses(partlist):
    """
    Returns a list of all Higgses in the model, based on 
    the existing entries in the GAMBIT particle database.

    Please extend if needed...
    14/10/2019: NMSSM-like Higgses - 3 scalars, 2 pseudoscalars, 1 charged
    """

    neutral_higgses_by_pdg = [
                              25, 35, 45,  # h0_1, h0_2, h0_3
                              36, 46,      # A0_1, A0_2
                             ]
    charged_higgses_by_pdg = [
                              37, -37      # H+, H-
                             ]

    neutral_higgses = [x.PDG_code for x in partlist if x.PDG_code in 
                       neutral_higgses_by_pdg]
    charged_higgses = [x.PDG_code for x in partlist if x.PDG_code in 
                       charged_higgses_by_pdg]
    higgses = neutral_higgses + charged_higgses

    return higgses, neutral_higgses, charged_higgses
    
def get_invisibles(invisible_pdgs):
    """
    Get the PDG codes of invisibles particles to write to 'contrib/heputils/include/HEPUtils/Event.h'
    Will not write for photons, leptons or existing invisibles in Event.h
    """
    
    # Create list of existing particle
    existing_invisibles = [22,11,-11,13,-13,15,-15]
    existing_invisibles.extend([12,-12,14,-14,16,-16,1000022,1000039,50,-50,51,-51,52,-52,53,-53,54,-54,55,-55,56,-56,57,-57,58,-58,59,-59])
    
    new_invisibles = [pdg for pdg in invisible_pdgs if pdg not in
                      existing_invisibles]
    to_write = ""

    if (len(new_invisibles) != 0):
        pdg_string = "p->pid() == {0}".format(new_invisibles[0])
        for i,pdg in enumerate(new_invisibles):
            if i != 0:
                pdg_string = pdg_string + "|| p->pid() == {0} ".format(pdg)
    
        to_write = ("      else if (" + pdg_string + ") \n"
        "      { \n"
        "        _invisibles.push_back(p); \n"
        "        _cinvisibles.push_back(p); \n"
        "      } \n")
    
    return to_write
