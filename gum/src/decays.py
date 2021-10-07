#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Master module for all DecayBit-related 
#  routines.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018 Apr, Nov
#        2019 Mar, Jul, Oct, Nov
#        2020 Feb, Apr, Jul
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2020 Mar
#
#  \author Chris Chang
#  \date 2021 Jul
#
#  **************************************

import numpy as np
import re
from collections import Counter
from collections import defaultdict

from .setup import *
from .files import *
from .cmake_variables import *

"""
CALCHEP-ONLY ROUTINES
"""

def find_decay_type(vertex):
    """
    Determines whether a 2-body decay is an A->A,A, A->B,B, A->B,Bbar,
    or A->B,C process, and correctly orders the vertex to reflect this.
    """

    # Case 1. All three are identical -> self-interaction.
    if len(Counter(vertex).values()) == 1:
        return vertex, "AAA"

    # Case 2. A-> B, B process. Return the array in the order for 1->2 process.
    elif len(Counter(vertex).values()) == 2:
        if list(Counter(vertex).values())[0] == 1:
            return vertex, "ABB"
        elif list(Counter(vertex).values())[0] == 2:
            return [list(Counter(vertex).keys())[1],
                    list(Counter(vertex).keys())[0],
                    list(Counter(vertex).keys())[0]], "ABB"


    # Case 3. A -> B, C process.
    elif len(Counter(vertex).values()) == 3:
        # Subcase (i). A -> B, BBar process
        if vertex[0] == -vertex[1]:
            return [vertex[2], vertex[0], vertex[1]], "ABBar"
        elif vertex[0] == -vertex[2]:
            return [vertex[1], vertex[0], vertex[2]], "ABBar"
        elif vertex[1] == -vertex[2]:
            return vertex, "ABBar"
        # Subcase (ii). Just an A -> B, C.
        else:
            return vertex, "ABC"

    # Case 4. Error. Shouldn't happen.
    else:
        raise GumError(("\n\nOnly 3 body vertices currently supported by GUM."
                        "\n\nAttempted to use vertex " + vertex))


def decay_grouper(decays, antiparticle_dict):
    """
    Groups a list of decays into groups for each particle.
    """

    annihilations = []
    others = []

    # CalcHEP convention is that everything in the vertex list is an incoming particle,
    # so for A -> B Bbar decays this is fine, but for A -> B B or A -> B C, we need
    # to conjugate the outgoing particles to A -> Bbar Bbar or A -> Bbar Cbar.

    for i in range(0, len(decays)):
        if decays[i][1] == "ABBar":
            annihilations.append(decays[i][0])
    
        elif decays[i][1] == "ABB":
            # Outgoing particles
            p1 = antiparticle_dict.get(decays[i][0][1])
            p2 = antiparticle_dict.get(decays[i][0][2])
            
            annihilations.append([decays[i][0][0], p1, p2])
        
        elif decays[i][1] == "ABC":
            # Take all three possible decays from this vertex
            for j in decays[i][0]:
                index = decays[i][0].index(j)
                # Outgoing particles
                p1 = antiparticle_dict.get(decays[i][0][index - 1])
                p2 = antiparticle_dict.get(decays[i][0][index - 2])

                others.append([decays[i][0][index], p1, p2])

    # Produce a list of all particles which need a module function writing.
    # Those with annihilations
    decaying_a_to_bb = list(set([i[0] for i in annihilations]))
    # Those less easy to categorise
    decaying_a_to_bc = list(set([i[0] for i in others]) - set(decaying_a_to_bb))

    channels = []

    for j in decaying_a_to_bb:
        products = []
        for i in range(0, len(annihilations)):
            if j == annihilations[i][0]:
                products.append([annihilations[i][1], annihilations[i][2]])
        for i in range(0, len(others)):
            if j == others[i][0]:
                products.append([others[i][1], others[i][2]])
        channels.append([j, products])

    for j in decaying_a_to_bc:
        products = []
        for i in range(0, len(others)):
            if j == others[i][0]:
                products.append([others[i][1], others[i][2]])
        channels.append([j, products]) 

    # Return list of all channels per particle.
    return channels

def decay_sorter(three_diagrams, aux_particles, antiparticle_dict):
    """
    Returns ordered lists of decays for writing module functions.
    Removes those with auxiliary particles.
    """

    decays = []

    for i in np.arange(len(three_diagrams)):

        td = three_diagrams[i]

        # If there is any cross-over between the vertex, and the
        # auxiliary particles, then we do not want them to be used in decays.
        if any([particle in aux_particles for particle in td]):
            continue

        vertex, decaytype = find_decay_type(td)

        # Ignore self-interactions
        if decaytype == "AAA":
            pass
        else:
            decays.append([vertex, decaytype])

    return decay_grouper(decays, antiparticle_dict)

def ch_decays_to_dict(three_decays):
    """
    Recast the CalcHEP decays to the same dictionary format as those from
    SPheno, so they can be used by other backends (e.g. Pythia) and other
    writing routines (such as for decaying DM).

    This is just a dictionary:

    decays = {
               pdg_code : [products_1], [products_2], [products_3]
             }
    """

    decays = defaultdict(list)

    for entry in three_decays:
        key = entry[0]
        products = entry[1]

        for product in products:
            decays[key].append(product)

    return decays


def write_decaytable_entry_calchep(grouped_decays, gambit_model_name,
                                   calchep_pdg_codes, gambit_pdg_codes,
                                   decaybit_dict, calchep_processes):
    """
    Writes a DecayBit DecayTable::Entry module function for a given set of
    of particle decays.
    Here, grouped_decays is a list, where:
      1. The first element is the decaying particle.
      2. The remaining entries are pairs of decay products.
      e.g. grouped_decays = [h, [  [tau+, tau-], [b, bbar], [t, tbar] ]]
    """

    # Find the name of the particle as in DecayBit_rollcall.hpp
    decayparticle = pdg_to_particle(grouped_decays[0], decaybit_dict)
    chep_name = pdg_to_particle(grouped_decays[0], calchep_pdg_codes)

    # If the particle does not decay, according to the particle database,
    # then there is no need to write a capability.
    if decayparticle != None:
        pass
    else:
        return ""

    # TODO: proper support for BSM contributions to Z and W decays
    if decayparticle == "Z":
        return ""
    elif decayparticle == "W_plus":
        return ""
    elif decayparticle == "W_minus":
        return ""

    function_name = "CH_{0}_{1}_decays".format(gambit_model_name, decayparticle).replace('~','bar')
    spectrum = gambit_model_name + "_spectrum"

    # Definitely a nicer way to do this, but, this will do for now. 
    # Should make it a bit easier to add 3 body final states.
    # (Overloaded as a backend function?)
    products = np.array(grouped_decays[1])

    c_name = []
    g_name = []
    for i in np.arange(len(products)):
        c_name.append(map(lambda x:pdg_to_particle(x, calchep_pdg_codes),products[i]))
        g_name.append(map(lambda x:pdg_to_particle(x, gambit_pdg_codes), products[i]))

    out1c = np.array([pdg_to_particle(x, calchep_pdg_codes) for x in products[:,0]])
    out2c = np.array([pdg_to_particle(x, calchep_pdg_codes) for x in products[:,1]])

    c_strings = []
    g_strings = []
    for i in np.arange(len(c_name)):
        c_strings.append("{{{}}}".format(', '.join("\"{0}\"".format(x) for x in c_name[i])))
        g_strings.append("{{{}}}".format(', '.join("\"{0}\"".format(y) for y in g_name[i])))

    calchep_processes['decays'][chep_name].append([list(i) for i in zip(out1c, out2c)])

    towrite = (
            "void {0}(DecayTable::Entry& result)\n"
            "{{\n"
            "using namespace Pipes::{0};\n"
            "// Clear previous decays\n"
            "result = DecayTable::Entry();\n"
            "\n"
            "const Spectrum& spec = *Dep::{1};\n"
            "\n"
    ).format(function_name, spectrum)

    if decayparticle == "Higgs":
        towrite += "result = *Dep::Reference_SM_Higgs_decay_rates;\n\n"

    towrite += (
            "str model = \"{0}\";\n"
            "str in = \"{1}\";"
            " // In state: CalcHEP particle name\n"
            "std::vector<std::vector<str>> out_calchep = {{{2}}}; "
            "// Out states: CalcHEP particle names\n"
            "std::vector<std::vector<str>> out_gambit = {{{3}}}; "
            "// Out states: GAMBIT particle names\n\n"
            "for (unsigned int i=0; i<out_calchep.size(); i++)\n"
            "{{\n"
            "\n"
            "double gamma = BEreq::CH_Decay_Width(model, in, "
            "out_calchep[i]); // Partial width\n"
            "double newwidth = result.width_in_GeV + gamma;  "
            "// Adjust total width\n"
            "double wscaling = ( gamma == 0. ) ? 1 : result.width_in_GeV"
            "/newwidth; // Scaling for BFs, avoid NaNs\n"
            "result.width_in_GeV = newwidth;\n"
            "\n"
            "for (auto it = result.channels.begin(); "
            "it != result.channels.end(); ++it)\n"
            "{{\n"
            "it->second.first  *= wscaling; "
            "// rescale BF \n"
            "it->second.second *= wscaling; // rescale error on BF \n"
            "}}\n"
            "\n"
            "// Avoid NaNs!\n"
            "double BF = ( gamma == 0. ) ? 0. : gamma/result.width_in_GeV;\n"
            "\n"
            "result.set_BF(BF, 0.0, "
            "out_gambit[i][0], out_gambit[i][1]);\n"
            "\n"
            "}}\n"
            "\n"
            "check_width(LOCAL_INFO, result.width_in_GeV, "
            "runOptions->getValueOrDef<bool>(false, "
            "\"invalid_point_for_negative_width\"))"
            ";\n"
            "}}"
            "\n"
            "\n"
    ).format(gambit_model_name, chep_name, ", ".join(c_strings), 
             ", ".join(g_strings))
    
    return indent(towrite, 4)

def write_decaybit_rollcall_entry_calchep(model_name, spectrum, newdecays, 
                                          decaybit_dict, gambit_dict,
                                          cap_def = {}):
    """
    Returns amendments for the  new rollcall entries for DecayBit as a 
    numpy array. The format of the array is:
    
    [ [ capability_name_1, towrite_1 ],
      [ capability_name_2, towrite_2 ], ... ]

    """
    
    rollcall_entries = []
    new_decays = []
     
    for i in range(len(newdecays)):
        decayparticle = newdecays[i][0]
        # TODO: support for BSM contribution to Z/W decays
        if decayparticle in [24, -24, 23]:
            continue
        gb_name = (pdg_to_particle(decayparticle, decaybit_dict))
        # If the particle does not decay, according to the particle database,
        # then there is no need to write a capability.
        if gb_name != None:
            pass
        else:
            continue
        cap = "{0}_decay_rates".format(gb_name).replace('~','bar')
        func = "CH_{0}_{1}_decays".format(model_name, 
                                          pdg_to_particle(decayparticle, 
                                                          decaybit_dict).replace('~','bar')
                                          )
        # If the capability already exists, see if the function already exists, 
        # only need to write the function
        if (find_capability(cap, "DecayBit")[0]  
        and not find_function(func, cap, "DecayBit")[0]):
            if decayparticle == 25:
                extra = (
                      "    DEPENDENCY(Reference_SM_Higgs_decay_rates, "
                      "DecayTable::Entry)\n"
                )
            else:
                extra = ""
            towrite = (
                    "    #define FUNCTION {0}\n"
                    "    START_FUNCTION(DecayTable::Entry)\n"
                    "    DEPENDENCY({1}, Spectrum)\n{2}"
                    "    BACKEND_REQ(CH_Decay_Width, (), double, (str&, str&, "
                    "std::vector<str>&))\n"
                    "    ALLOW_MODELS({3})\n"
                    "    #undef FUNCTION\n"
            ).format(func, spectrum, extra, model_name)
            rollcall_entries.append([cap, towrite])
        # If the capability doesn't exist => must write a new entry for it as 
        # well as the function
        elif not find_capability(cap, "DecayBit")[0]:
            towrite = (
                    "  #define CAPABILITY {0}\n"
                    "  START_CAPABILITY\n"
                    "\n"
                    "    #define FUNCTION {1}\n"
                    "    START_FUNCTION(DecayTable::Entry)\n"
                    "    DEPENDENCY({2}, Spectrum)\n"
                    "    BACKEND_REQ(CH_Decay_Width, (), double, (str&, str&, "
                    "std::vector<str>&))\n"
                    "    ALLOW_MODELS({3})\n"
                    "    #undef FUNCTION\n"
                    "\n"
                    "  #undef CAPABILITY\n"
            ).format(cap, func, spectrum, model_name)
            rollcall_entries.append([cap, towrite])
            gb_name = pdg_to_particle(decayparticle, gambit_dict)
            new_decays.append([cap, gb_name])

            # Add capability definition
            cap_def[cap] = 'All decay rates for particle ' + gb_name + '.'

    return rollcall_entries, new_decays

def amend_all_decays_calchep(model_name, spectrum, new_decays):
    """
    Amends all_decays in DecayBit, both in source and in the rollcall
    header.
    """
    
    src = ""
    header = ""
    src_extra = ""
    
    for i in range(len(new_decays)):
        src_extra += (
                  "decays(\"{0}\") = *Dep::{1};\n"
        ).format(new_decays[i][1], new_decays[i][0])
    
    if len(new_decays) > 0:
        header += (
            "    MODEL_CONDITIONAL_DEPENDENCY({0}, Spectrum, {1})"
        ).format(spectrum, model_name)
        
        src += indent((
            "\n"
            "// {0}-specific\n"
            "if (ModelInUse(\"{0}\"))\n"
            "{{\n"
            "{1}"
            "}}\n"
        ).format(model_name, src_extra), 6)
    
    for i in range(len(new_decays)):
        header += (
               "\n    MODEL_CONDITIONAL_DEPENDENCY({0}, DecayTable::Entry, {1})"
        ).format(new_decays[i][0], model_name)

        
    header += "\n"
                
    return src, header
    

"""
SPHENO
"""

def write_spheno_decay_entry(model_name, clean_model_name):
    """
    Writes a DecayBit entry for SPheno decays.
    """

    towrite_src = (
        "\n"
        "/// Get all the decays from SPheno (for the {0} model).\n"
        "void all_{0}_decays_from_SPheno(DecayTable& decays)\n"
        "{{\n"
        "namespace myPipe = Pipes::all_{0}_decays_from_SPheno;\n"
        "\n"
        "// Get the spectrum object\n"
        "Spectrum spectrum = *myPipe::Dep::{0}_spectrum;\n"
        "\n"
        "// Set up the input structure\n"
        "Finputs inputs;\n"
        "inputs.param = myPipe::Param;\n"
        "inputs.options = myPipe::runOptions;\n"
        "\n"
        "// Use SPheno to fill the decay table\n"
        "myPipe::BEreq::SARAHSPheno_{0}_decays(spectrum, decays, inputs);\n"
        "\n"
        "// Add some SM decays\n"
        "decays(\"Z0\") = *myPipe::Dep::Z_decay_rates;           // Add the Z decays\n"
        "decays(\"W+\") = *myPipe::Dep::W_plus_decay_rates;      // Add the W decays for W+.\n"
        "decays(\"W-\") = *myPipe::Dep::W_minus_decay_rates;     // Add the W decays for W-\n"
        "\n"
        "/// Spit out the full decay table as an SLHA2 file.\n"
        "/// We do not provide SLHA1 as that requires knowledge of the pseudonyms, which we do not have in general.\n"
        "if (myPipe::runOptions->getValueOrDef<bool>(false, \"drop_SLHA_file\"))\n"
        "{{\n"
        "str prefix   = myPipe::runOptions->getValueOrDef<str>(\"\", \"SLHA_output_prefix\");\n"
        "str filename = myPipe::runOptions->getValueOrDef<str>(\"GAMBIT_decays\", \"SLHA_output_filename\");\n"
        "decays.writeSLHAfile(2,prefix+filename+\".slha2\",false);\n"
        "}}\n"
        "\n"
        "}}\n\n"
    ).format(model_name)

    towrite_header = (
                   "#define FUNCTION all_{0}_decays_from_SPheno\n"
                   "START_FUNCTION(DecayTable)\n"
                   "DEPENDENCY(W_minus_decay_rates, DecayTable::Entry)\n"
                   "DEPENDENCY(W_plus_decay_rates, DecayTable::Entry)\n"
                   "DEPENDENCY(Z_decay_rates, DecayTable::Entry)\n"
                   "DEPENDENCY({0}_spectrum, Spectrum)\n"
                   "BACKEND_REQ(SARAHSPheno_{0}_decays, (libSPheno{2}), int, "
                   "(const Spectrum&, DecayTable&, const Finputs&) )\n"
                   "BACKEND_OPTION((SARAHSPheno_{0}, {1}), (libSPheno{2}))\n"
                   "ALLOW_MODELS({0})\n"
                   "#undef FUNCTION\n"
                   "\n"
    ).format(model_name, SPHENO_VERSION, clean_model_name)

    return dumb_indent(4, indent(towrite_src)), dumb_indent(4, towrite_header)
