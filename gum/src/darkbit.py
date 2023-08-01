#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Master module for all DarkBit-related
#  routines.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018 Apr, Aug, Sep, Oct, Dec
#        2019 Feb, Oct, Nov,
#        2020 Feb, Apr, Jul
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2020
#
#  **************************************

import numpy as np
import shutil
from distutils.dir_util import copy_tree
from collections import defaultdict

from .setup import *
from .files import *
from .backends import *

class VertexMerger:

    """
    Class used for 2-2 processes
    """

    def __init__(self, vertexA, vertexB):

        self.vA = vertexA
        self.vB = vertexB
        self.v6 = vertexA + vertexB

    def has_dm_dmbar(self, dm):
        """
        Return whether a merged vertex has a DM particle and its conjugate
        """

        if not isinstance(dm, Particle):
            raise GumError("DM not passed over as instance of class Particle...")

        if dm.is_sc():
            if (self.v6.count(dm.PDG_code) > 1):
                return True
            else: return False
        else:
            if (self.v6.count(dm.PDG_code) > 0 and
                self.v6.count(dm.conjugate_PDG_code) > 0):
                return True
            else: return False

    def find_ann(self, dm, antiparticles, aux_particles, propagators, products):
        """
        For each particle in vertexA, check to see if its antiparticle
        is in vertexB. If so, we can consider this a propagator particle.
        Add this to the list of propagators and add the products to a list too
        """

        for particle in self.vA:

            # Create a copy of the six body mess, then remove an instance of DM and DMbar
            l = self.v6[:]
            l.remove(l[l.index(dm.PDG_code)])
            l.remove(l[l.index(dm.conjugate_PDG_code)])

            # Firstly check the type of the field
            # If it's an integer then it's a PDG code
            if isinstance(particle, int):
                # If we have DM + DMbar only accept this if it's a t-channel
                # exchange, (chi + X ---> chi/chi~ <--- X~ chi~)
                if (particle == dm.PDG_code or
                    particle == dm.conjugate_PDG_code):
                    if not dm.is_sc():
                        if not self.v6.count(dm.PDG_code) == 2: continue
                    elif dm.is_sc():
                        if not self.v6.count(dm.PDG_code) == 4: continue

                if antiparticles[particle] in self.vB:
                    propagators.append(particle)
                    propagators.append(antiparticles[particle])
                    # Get the products
                    l.remove(l[l.index(particle)])
                    l.remove(l[l.index(antiparticles[particle])])
                    products.append(l)

            # If it's a string it'll be an aux field
            elif isinstance(particle, str):
                if aux_particles[particle] in self.vB:
                    # Just add the products, don't want to earmark auxiliary
                    # particles for resonances
                    # Get the products
                    l.remove(l[l.index(particle)])
                    l.remove(l[l.index(aux_particles[particle])])
                    products.append(l)


def sort_annihilations(dm, three_fields, four_fields, aux_particles,
                       antiparticles):
    """
    Sorts BSM vertices, returns DM+DM -> X + Y and a list of propagator
    particles (not auxiliaries though -- the propagators are used for
    resonances)
    """

    if not isinstance(dm, Particle):
        GumError("\n\nDM not passed over as an instance of class Particle.")

    propagators = []
    products = []

    # Add all 4-pt vertices that are DM + DM -> X + Y
    # Shouldn't have to worry about auxiliary particles in a contact
    # interaction - sort of defeats the point.
    for i in range(0, len(four_fields)):

        if dm.is_sc() and four_fields[i].count(dm.PDG_code) == 2:
            p = [f for f in four_fields[i] if f not in {dm.PDG_code}]
            products.append(p)

        elif not dm.is_sc() and four_fields[i].count(dm.PDG_code) == 1 and \
                four_fields[i].count(dm.conjugate_PDG_code) == 1:
            p = [f for f in four_fields[i] if
                 f not in {dm.PDG_code, dm.conjugate_PDG_code}]
            products.append(p)

    """
    2 to 2 processes at tree-level.
    1. Create a big list of all possible combinations of 3 particle vertices
    2. Only keep those that have DM and DMbar in
    3. Check to see if they have a particle + antiparticle, coming from distinct
       three-body vertices
    """

    for i in three_fields:
        for j in three_fields:
            v = VertexMerger(i,j)

            # If there's at least one dm, and one dmbar,
            # then let's have a closer look
            if not v.has_dm_dmbar(dm):
                continue

            # Check to see if there is a DM+DMbar-> X + Y process in the
            # merged vertex, and record any (physical) propagators and products
            v.find_ann(dm, antiparticles, aux_particles, propagators, products)

    # Remove duplicates
    propagators = list(set(propagators))
    products = [list(x) for x in set(tuple(y)
                for y in [sorted(z) for z in products])]


    # Remove any DM-DM self-interactions
    # If these are important they should be dealt with by e.g. micrOMEGAs 5.0+
    # and the freeze-in routines, or Z3 models, etc.
    if [dm.PDG_code, dm.conjugate_PDG_code] in products:
        products.remove([dm.PDG_code, dm.conjugate_PDG_code])
    if [dm.conjugate_PDG_code, dm.PDG_code] in products:
        products.remove([dm.conjugate_PDG_code, dm.PDG_code])

    # Remove DM itself from the list of propagators
    if dm.PDG_code in propagators:
        propagators.remove(dm.PDG_code)
    if dm.conjugate_PDG_code in propagators:
        propagators.remove(dm.conjugate_PDG_code)

    return np.array(products), propagators

def xsecs(dm, products, gambit_pdg_dict, gambit_model_name,
          calchep_pdg_dict, calchep_processes):
    """
    Writes all entries for <sigma v> within the Process Catalogue,
    utilising CalcHEP.
    """

    # DM mass parameter
    gb_id = pdg_to_particle(dm.PDG_code, gambit_pdg_dict)
    dm_mass = "m" + gb_id.strip('~').replace("\"", "")

    # Arrays of final states (GAMBIT names)
    out1g = np.array([pdg_to_particle(x, gambit_pdg_dict) for x in products[:,0]])
    out2g = np.array([pdg_to_particle(x, gambit_pdg_dict) for x in products[:,1]])
    # Arrays of final states (CalcHEP names)
    out1c = np.array([pdg_to_particle(x, calchep_pdg_dict) for x in products[:,0]])
    out2c = np.array([pdg_to_particle(x, calchep_pdg_dict) for x in products[:,1]])

    # DM (and conjugate) as known to CalcHEP
    dm_chep = pdg_to_particle(dm.PDG_code, calchep_pdg_dict)
    dm_chepc = pdg_to_particle(dm.conjugate_PDG_code, calchep_pdg_dict)

    # Save entry to calchep_processes
    calchep_processes['xsecs'][dm_chep, dm_chepc].append([list(i) for i in
                                                          zip(out1c, out2c)])

    towrite_class = (
            "// Annihilation cross-section. sigmav is a pointer to a"
            " CalcHEP backend function.\n"
            "double sv(str channel, DecayTable& tbl, "
            "double (*sigmav)(str&, std::vector<str>&, std::vector<str>&, "
            "double&, const DecayTable&), double v_rel)\n"
            "{{\n"
            "/// Returns sigma*v for a given channel.\n"
            "double GeV2tocm3s1 = gev2cm2*s2cm;\n\n"
            "// CalcHEP args\n"
            "str model = \"{0}\"; // CalcHEP model name\n"
            "std::vector<str> in = {{\"{1}\", \"{2}\"}}; // In states: DM+DMbar\n"
            "std::vector<str> out; // Out states\n"
    ).format(gambit_model_name, dm_chep, dm_chepc)

    # Add each channel individually for annihilation cross sections
    for i in np.arange(len(products)):
        towrite_class += (
                "if (channel == \"{0}, {1}\") "
                "out = {{\"{2}\", \"{3}\"}};\n"
        ).format(out1g[i], out2g[i], out1c[i], out2c[i])

    towrite_class += (
            "\n"
            "// Check the channel has been filled\n"
            "if (out.size() > 1) return "
            "sigmav(model, in, out, v_rel, tbl)*GeV2tocm3s1;\n"
            "else return 0;\n"
            "}\n\n"
    )

    channels = ', '.join("\"{}, {}\"".format(*t) for t in zip(out1g, out2g))
    p1 = ', '.join("\"{}\"".format(*t) for t in zip(out1g))
    p2 = ', '.join("\"{}\"".format(*t) for t in zip(out2g))

    towrite_pc = (
            "\n"
            "// Instantiate new {0} object.\n"
            "auto pc = boost::make_shared<{0}>();\n"
            "\n"
            "// Populate annihilation channel list and add "
            "thresholds to threshold list.\n"
            "process_ann.resonances_thresholds.threshold_energy"
            ".push_back(2*{1});\n"
            "auto channels = \n"
            "  daFunk::vec<string>({2});\n"
            "auto p1 = \n"
            "  daFunk::vec<string>({3});\n"
            "auto p2 = \n"
            "  daFunk::vec<string>({4});\n"
            "\n"
            "for (unsigned int i = 0; i < channels.size(); ++i)\n"
            "{{\n"
            "double mtot_final = \n"
            "catalog.getParticleProperty(p1[i]).mass + \n"
            "catalog.getParticleProperty(p2[i]).mass;  \n"
            "if ({1}*2 > mtot_final*0.5)\n"
            "{{\n"
            "daFunk::Funk kinematicFunction = daFunk::funcM("
            "pc, &{0}::sv, channels[i], tbl, \n"
            "BEreq::CH_Sigma_V.pointer(), daFunk::var(\"v\"));\n"
            "TH_Channel new_channel("
            "daFunk::vec<string>(p1[i], p2[i]), kinematicFunction);\n"
            "process_ann.channelList.push_back(new_channel);\n"
            "}}\n"
            "if ({1}*2 < mtot_final)\n"
            "{{\n"
            "process_ann.resonances_thresholds.threshold_energy.\n"
            "push_back(mtot_final);\n"
            "}}\n"
            "}}\n"
            "\n"
    ).format(gambit_model_name, dm_mass, channels, p1, p2)

    return towrite_class, towrite_pc

def decays(dm, products, gambit_pdg_dict):
    """
    Writes all entries for decays within the Process Catalogue,
    just using what's already been filled in the DecayTable.
    The DecayTable can come from either CalcHEP (tree-level)
    or SPheno (so can include loop decays).
    """

    decay_src = "\n"
    gb_id = pdg_to_particle(dm.PDG_code, gambit_pdg_dict)
    dm_mass = "m" + gb_id.strip('~').replace("\"", "")

    # Split products into 2-body and 3-body
    twobody = [x for x in products if len(x) == 2]
    threebody = [x for x in products if len(x) == 3]

    # 2-body decay - genRate = partial decay width.
    # Get it from the DecayTable total width * BF
    if twobody:
        out1g = np.array([pdg_to_particle(x[0], gambit_pdg_dict) for x in twobody])
        out2g = np.array([pdg_to_particle(x[1], gambit_pdg_dict) for x in twobody])
        p1 = ', '.join("\"{}\"".format(*t) for t in zip(out1g))
        p2 = ', '.join("\"{}\"".format(*t) for t in zip(out2g))

        decay_src += (
                  "// 2-body decays\n"
                  "auto p1 =  daFunk::vec<string>({0});\n"
                  "auto p2 =  daFunk::vec<string>({1});\n"
                  "\n"
                  "for (unsigned int i = 0; i < p1.size(); ++i)\n"
                  "{{\n"
                  "double mtot_final = "
                  "catalog.getParticleProperty(p1[i]).mass\n"
                  "                  + "
                  "catalog.getParticleProperty(p2[i]).mass;  \n"
                  "// Is the channel kinematically allowed?\n"
                  "if ({2} > mtot_final)\n"
                  "{{\n"
                  "TH_Channel dec_channel(daFunk::vec<string>(p1[i], p2[i]),\n"
                  "  daFunk::cnst(tbl.at(\"{3}\").width_in_GeV*tbl.at(\"{3}\")"
                  ".BF(p1[i], p2[i])));\n"
                  "process_dec.channelList.push_back(dec_channel);\n"
                  "}}\n"
                  "}}\n"
                  "\n"
        ).format(p1, p2, dm_mass, gb_id)

    # 3-body decay - genRate = partial decay width, with two variables,
    # Get it from the DecayTable total width * BF
    # NOTE: Decaying DM is disabled for the moment, so this will not be used
    if threebody:
        out1g = np.array([pdg_to_particle(x[0], gambit_pdg_dict) for x in threebody])
        out2g = np.array([pdg_to_particle(x[1], gambit_pdg_dict) for x in threebody])
        out3g = np.array([pdg_to_particle(x[2], gambit_pdg_dict) for x in threebody])
        p1 = ', '.join("\"{}\"".format(*t) for t in zip(out1g))
        p2 = ', '.join("\"{}\"".format(*t) for t in zip(out2g))
        p3 = ', '.join("\"{}\"".format(*t) for t in zip(out3g))

        decay_src += (
                  "// 3-body decays\n"
                  "auto p1_3b =  daFunk::vec<string>({0});\n"
                  "auto p2_3b =  daFunk::vec<string>({1});\n"
                  "auto p3_3b =  daFunk::vec<string>({2});\n"
                  "\n"
                  "for (unsigned int i = 0; i < p1.size(); ++i)\n"
                  "{{\n"
                  "double mtot_final = \n"
                  "catalog.getParticleProperty(p1_3b[i]).mass + \n"
                  "catalog.getParticleProperty(p2_3b[i]).mass +  \n"
                  "catalog.getParticleProperty(p3_3b[i]).mass;  \n"
                  "if ({3} > mtot_final)\n"
                  "{{\n"
                  "TH_Channel dec_channel(daFunk::vec<string>(p1_3b[i], "
                  "p2_3b[i], p3_3b[i]), daFunk::cnst("
                  "tbl.at(\"{4}\").width_in_GeV*tbl.at(\"{4}\")"
                  ".BF(p1[i], p2[i], p3[i])));\n"
                  "process_dec.channelList.push_back(dec_channel);\n"
                  "}}\n"
                  "}}\n"
                  "\n"
        ).format(p1, p2, p3, dm_mass, gb_id)

    return decay_src

def proc_cat(dm, sv, products, propagators, gambit_pdg_dict,
             gambit_model_name, calchep_pdg_dict, model_specific_particles,
             higgses, calchep_processes, does_DM_decay = False):
    """
    Writes all entries for the Process Catalogue for DarkBit.
    """

    towrite = ""
    gb_id = pdg_to_particle(dm.PDG_code, gambit_pdg_dict)
    gb_conj = pdg_to_particle(dm.conjugate_PDG_code, gambit_pdg_dict)

    if not does_DM_decay:
        towrite += (
                "class {0}\n"
                "{{\n"
                "public:\n"
                "/// Initialize {0} object (branching ratios etc)\n"
                "{0}() {{}};\n"
                "~{0}() {{}};\n\n"
        ).format(gambit_model_name)

    # If we need to write the annihilations, call the xsecs routine
    if sv:
        sv_class, sv_src = xsecs(dm, products, gambit_pdg_dict,
                                 gambit_model_name, calchep_pdg_dict,
                                 calchep_processes)
        # Add the Class definitions here. Only needed if we have annihilating DM
        towrite += sv_class
        towrite += "\n};\n\n"

    # Decaying DM doesn't need the Class stuff etc., waaaay easier.
    else:
        decay_src = decays(dm, products, gambit_pdg_dict)

    towrite += (
            "void TH_ProcessCatalog_{0}(TH_ProcessCatalog &result)\n"
            "{{\n"
            "using namespace Pipes::TH_ProcessCatalog_{0};\n"
            "using std::vector;\n"
            "using std::string;\n\n"
            "// Initialize empty catalog, main annihilation process\n"
            "TH_ProcessCatalog catalog;\n"
    ).format(gambit_model_name)

    # Add the correct process - either annihilation or decay.
    if does_DM_decay:
        towrite += "TH_Process process_dec(\"{0}\");\n".format(gb_id)
    else:
        towrite += "TH_Process process_ann(\"{0}\", \"{1}\");\n".format(gb_id,
                                                                        gb_conj)
        # Add flag for (non-)self-conjugate DM to rescale spectra properly
        if not dm.is_sc():
            towrite += (
                    "\n"
                    "// Explicitly state that Dirac DM is not self-conjugate "
                    "to add extra \n// factors of 1/2 where necessary\n"
                    "process_ann.isSelfConj = false;\n\n"
            )
        else:
            towrite += (
                    "\n"
                    "// Explicitly state that DM is self-conjugate\n"
                    "process_ann.isSelfConj = true;\n\n"
            )

    # NOTE: GUM may fail to generate all of the decays for non-self-conjugate
    # DM that is equal part DM and anti-DM. This will be enabled in the future

    towrite += add_SM_macros(gambit_model_name)

    # Add the new BSM particles to the Process Catalog
    dm_mass = "m" + gb_id.strip('~').replace("\"", "")

    towrite += (
            "// {0}-specific masses\n"
            "double {1} = spec.get(Par::Pole_Mass, \"{2}\");\n"
            "addParticle(\"{2}\", {1}, {3});\n"
    ).format(gambit_model_name, dm_mass, gb_id, dm.spinX2)

    # Add the antiparticle to the catalog too
    if not does_DM_decay:
        if not dm.is_sc():
            towrite += (
                    "addParticle(\"{1}\", {0}, {2});\n"
            ).format(dm_mass, gb_conj, dm.spinX2)

    for i in np.arange(len(model_specific_particles)):
        if model_specific_particles[i].PDG_code != dm.PDG_code:
            towrite += (
                    "addParticle(\"{0}\", spec.get(Par::Pole_Mass,"
                    " \"{1}\"), {2});\n"
            ).format(pdg_to_particle(model_specific_particles[i].PDG_code,
                                     gambit_pdg_dict),
                     pdg_to_particle(model_specific_particles[i].PDG_code,
                                     gambit_pdg_dict),
                     str(model_specific_particles[i].spinX2)
                     )
            if not model_specific_particles[i].is_sc():
                towrite += (
                        "addParticle(\"{0}\", spec.get(Par::Pole_Mass,"
                        " \"{1}\"), {2});\n"
                ).format(pdg_to_particle(model_specific_particles[i].conjugate_PDG_code,
                                         gambit_pdg_dict),
                         pdg_to_particle(model_specific_particles[i].conjugate_PDG_code,
                                         gambit_pdg_dict),
                         str(model_specific_particles[i].spinX2)
                         )
 
    towrite += (
            "\n"
            "// Get rid of convenience macros\n"
            "#undef getSMmass\n"
            "#undef addParticle\n"
            "\n"
            "// Import decay table from DecayBit\n"
            "DecayTable tbl = *Dep::decay_rates;\n"
    )

    # Use DarkBit_utils::ImportDecays to recursively import decays for final
    # state particles
    if higgses or propagators:

        towrite += (
                "\n"
                "// Set of imported decays\n"
                "std::set<string> importedDecays;\n"
                "\n"
                "// Minimum branching ratio to include\n"
                "double minBranching = runOptions->getValueOrDef<double>(0.0,"
                " \"ProcessCatalog_MinBranching\");\n"
                "\n"
                "// Import relevant decays\n"
                "using DarkBit_utils::ImportDecays;\n"
                "\n"
                "auto excludeDecays = daFunk::vec<std::string>("
                "\"Z0\", \"W+\", \"W-\", "
                "\"e+_3\", \"e-_3\", \"e+_2\", \"e-_2\");\n"
                "\n"
        )

        if does_DM_decay: propagators = []

        for particle in list(set(higgses+propagators)):

            towrite += (
                "ImportDecays(\"{0}\", catalog, importedDecays, &tbl, "
                "minBranching, excludeDecays);\n"
            ).format(pdg_to_particle(particle, gambit_pdg_dict))

    # Add the calls to the cross-sections if we're not decaying
    if sv:
        towrite += sv_src

        # Add all propagators as resonances.
        if propagators:
            for i in np.arange(len(propagators)):
                if abs(propagators[i]) != abs(dm.PDG_code):
                    towrite += (
                            "if ( (spec.has(Par::Pole_Mass, \"{0}\") ? spec.get(Par::Pole_Mass, \"{0}\") : spec.get(Par::mass1, \"{0}\")) >= 2*{1})\n"
                            "  process_ann.resonances_thresholds.resonances."
                            "push_back(TH_Resonance(spec.get(Par::Pole_Mass, "
                            "\"{0}\"), tbl.at(\"{0}\").width_in_GeV));\n"
                    ).format(pdg_to_particle(propagators[i], gambit_pdg_dict),
                             dm_mass)
    # Add the products of DM -> ...
    if does_DM_decay:
        towrite += decay_src

    if does_DM_decay:
        towrite += "catalog.processList.push_back(process_dec);\n\n"
    else:
        towrite += "\ncatalog.processList.push_back(process_ann);\n\n"

    # Wrap it up.
    towrite +=(
            "// Validate\n"
            "catalog.validate();\n\n"
            "result = catalog;\n"
            "} // function TH_ProcessCatalog\n"
    )

    return towrite

def write_wimp_props(model_name):

    wimp_prop_h = dumb_indent(4, (
              "MODEL_CONDITIONAL_DEPENDENCY({0}_spectrum, Spectrum, {0})\n"
              "ALLOW_MODELS({0})\n"
    ).format(model_name))

    wimp_prop_c = dumb_indent(6, (
              "else if(ModelInUse(\"{0}\"))\n"
              "  props.mass = Dep::{0}_spectrum->get(Par::Pole_Mass, props.name);\n"
    ).format(model_name))

    return wimp_prop_h, wimp_prop_c


def write_darkbit_src(dm, pc, sv, products, propagators, does_DM_decay,
                      gambit_pdg_dict, gambit_model_name, calchep_pdg_dict,
                      model_specific_particles, higgses, calchep_processes):
    """
    Collects all source for DarkBit:
        - process catalogue
        - DM ID
        - ...
    """

    gb_id = pdg_to_particle(dm.PDG_code, gambit_pdg_dict)
    gb_conj = pdg_to_particle(dm.conjugate_PDG_code, gambit_pdg_dict)

    if not isinstance(dm, Particle):
        print("DM not passed over as an instance of class Particle.")
        exit()

    intro_message = (
            "///  Implementation of {0}\n"
            "///  DarkBit routines."
    ).format(gambit_model_name)

    towrite = blame_gum(intro_message)

    towrite += (
            "#include \"gambit/Elements/gambit_module_headers.hpp\"\n"
            "#include \"gambit/DarkBit/DarkBit_rollcall.hpp\"\n"
            "#include \"gambit/Utils/ascii_table_reader.hpp\"\n"
            "#include \"boost/make_shared.hpp\"\n"
            "#include \"gambit/DarkBit/DarkBit_utils.hpp\"\n"
            "\n"
            "namespace Gambit\n"
            "{\n"
            "namespace DarkBit\n"
            "{\n"
    )

    # Process Catalogue
    if pc:
        towrite += proc_cat(dm, sv, products, propagators,
                            gambit_pdg_dict, gambit_model_name,
                            calchep_pdg_dict, model_specific_particles,
                            higgses, calchep_processes, does_DM_decay)

    # Add the DM ID (plus its conjugate, if not decaying)
    towrite += write_dm_id(gambit_model_name, gb_id, gb_conj)

    towrite += (
            "} //namespace DarkBit\n\n"
            "} //namespace Gambit\n"
            "\n"
    )

    return indent(towrite)

def write_dm_id(model_name, dm_id, dm_conj = None):
    """
    Returns entry for DarkMatter_ID in DarkBit.
    """

    towrite = (
            "\n"
            "void DarkMatter_ID_{0}(std::string& result)"
            "{{ result = \"{1}\"; }}"
            "\n"
    ).format(model_name, dm_id)
    if dm_conj:
        towrite += (
                "\n"
                "void DarkMatterConj_ID_{0}(std::string& result)"
                "{{ result = \"{1}\"; }}"
                "\n\n"
        ).format(model_name, dm_conj)

    return towrite

def add_SM_macros(gambit_model_name):
    """
    Adds Standard Model macros to the Process Catalogue.
    """

    towrite = (
            "\n"
            "// Import particle masses \n"
            "\n"
            "// Convenience macros\n"
            "#define getSMmass(Name, spinX2) "
            "catalog.particleProperties.insert(std::pair<string, "
            "TH_ParticleProperty> (Name, TH_ParticleProperty"
            "(SM.get(Par::Pole_Mass,Name), spinX2)));\n"
            "#define addParticle(Name, Mass, spinX2) "
            "catalog.particleProperties.insert(std::pair<string, "
            "TH_ParticleProperty> (Name, "
            "TH_ParticleProperty(Mass, spinX2)));\n"
            "\n"
            "// Import Spectrum objects\n"
            "const Spectrum& spec = *Dep::{0}_spectrum;\n"
            "const SubSpectrum& SM = spec.get_LE();\n"
            "const SMInputs& SMI   = spec.get_SMInputs();\n"
            "\n"
            "// Get SM pole masses\n"
            "getSMmass(\"e-_1\",     1)\n"
            "getSMmass(\"e+_1\",     1)\n"
            "getSMmass(\"e-_2\",     1)\n"
            "getSMmass(\"e+_2\",     1)\n"
            "getSMmass(\"e-_3\",     1)\n"
            "getSMmass(\"e+_3\",     1)\n"
            "getSMmass(\"Z0\",       2)\n"
            "getSMmass(\"W+\",       2)\n"
            "getSMmass(\"W-\",       2)\n"
            "getSMmass(\"g\",        2)\n"
            "getSMmass(\"gamma\",    2)\n"
            "getSMmass(\"u_3\",      1)\n"
            "getSMmass(\"ubar_3\",   1)\n"
            "getSMmass(\"d_3\",      1)\n"
            "getSMmass(\"dbar_3\",   1)\n"
            "\n"
            "// Pole masses not available for the light quarks.\n"
            "addParticle(\"u_1\"   , SMI.mU,  1) // mu(2 GeV)^MS-bar\n"
            "addParticle(\"ubar_1\", SMI.mU,  1) // mu(2 GeV)^MS-bar\n"
            "addParticle(\"d_1\"   , SMI.mD,  1) // md(2 GeV)^MS-bar\n"
            "addParticle(\"dbar_1\", SMI.mD,  1) // md(2 GeV)^MS-bar\n"
            "addParticle(\"u_2\"   , SMI.mCmC,1) // mc(mc)^MS-bar\n"
            "addParticle(\"ubar_2\", SMI.mCmC,1) // mc(mc)^MS-bar\n"
            "addParticle(\"d_2\"   , SMI.mS,  1) // ms(2 GeV)^MS-bar\n"
            "addParticle(\"dbar_2\", SMI.mS,  1) // ms(2 GeV)^MS-bar\n"
            "\n"
            "// Masses for neutrino flavour eigenstates. Set to zero.\n"
            "// (presently not required)\n"
            "addParticle(\"nu_e\",     0.0, 1)\n"
            "addParticle(\"nubar_e\",  0.0, 1)\n"
            "addParticle(\"nu_mu\",    0.0, 1)\n"
            "addParticle(\"nubar_mu\", 0.0, 1)\n"
            "addParticle(\"nu_tau\",   0.0, 1)\n"
            "addParticle(\"nubar_tau\",0.0, 1)\n"
            "\n"
            "// Meson masses\n"
            "addParticle(\"pi0\",   meson_masses.pi0,       0)\n"
            "addParticle(\"pi+\",   meson_masses.pi_plus,   0)\n"
            "addParticle(\"pi-\",   meson_masses.pi_minus,  0)\n"
            "addParticle(\"eta\",   meson_masses.eta,       0)\n"
            "addParticle(\"rho0\",  meson_masses.rho0,      1)\n"
            "addParticle(\"rho+\",  meson_masses.rho_plus,  1)\n"
            "addParticle(\"rho-\",  meson_masses.rho_minus, 1)\n"
            "addParticle(\"omega\", meson_masses.omega,     1)\n"
            "\n"
    ).format(gambit_model_name)

    return towrite

def write_darkbit_rollcall(model_name, pc, does_DM_decay):
    """
    Writes the rollcall header entries for new DarkBit entry.
    """

    if pc:
        # Do we need to add a BACKEND_REQ to the rollcall header? Only when
        # DM is annihilating; else it comes from the DecayTable already.
        bereq = ""
        if not does_DM_decay:
            bereq = (
                  "  BACKEND_REQ(CH_Sigma_V, (), double, (str&, "
                  "std::vector<str>&, std::vector<str>&, double&, "
                  "const DecayTable&))\n"
            )
        pro_cat = dumb_indent(4, (
                "#define FUNCTION TH_ProcessCatalog_{0}\n"
                "  START_FUNCTION(TH_ProcessCatalog)\n"
                "  DEPENDENCY(WIMP_properties, WIMPprops)\n"
                "  DEPENDENCY(decay_rates, DecayTable)\n"
                "  DEPENDENCY({0}_spectrum, Spectrum)\n"
                "{1}"
                "  ALLOW_MODELS({0})\n"
                "#undef FUNCTION\n"
        ).format(model_name, bereq))
    else:
        pro_cat = None

    dm_id = dumb_indent(4, (
            "#define FUNCTION DarkMatter_ID_{0}\n"
            "START_FUNCTION(std::string)\n"
            "ALLOW_MODELS({0})\n"
            "#undef FUNCTION\n"
    ).format(model_name))

    dm_conj = dumb_indent(4, (
              "#define FUNCTION DarkMatterConj_ID_{0}\n"
              "START_FUNCTION(std::string)\n"
              "ALLOW_MODELS({0})\n"
              "#undef FUNCTION\n"
    ).format(model_name))

    return pro_cat, dm_id, dm_conj



"""
MICROMEGAS
"""

mo_version = "3.6.9.2"
mo_safe_version = "3_6_9_2"

def write_micromegas_src(gambit_model_name, spectrum, mathpackage, params,
                         particles, gambit_pdg_codes, calchep_masses,
                         calchep_widths):
    """
    Writes frontend source and header files for a new MicrOmegas model.

    Needs to know whether the source code is generated by FeynRules or SARAH
    since SM-ish things like quark masses, gauge couplings, etc are hard-coded.
    """

    ## Frontend source file
    intro_message = (
            "///  Frontend for MicrOmegas {0}\n"
            "///  {1} backend."
    ).format(gambit_model_name, mo_version)

    mo_src = blame_gum(intro_message)

    mo_src += (
            "#include \"gambit/Backends/frontend_macros.hpp\"\n"
            "#include \"gambit/Backends/frontends/MicrOmegas_{0}_{1}.hpp\""
            "\n"
            "#include <unistd.h>\n"
            "\n"
            "// Convenience functions (definitions)\n"
            "BE_NAMESPACE\n"
            "{{\n"
            "double dNdE(double Ecm, double E, int inP, int outN)\n"
            "{{\n"
            "// outN 0-5: gamma, e+, p-, nu_e, nu_mu, nu_tau\n"
            "// inP:  0 - 6: glu, d, u, s, c, b, t\n"
            "//       7 - 9: e, m, l\n"
            "//       10 - 15: Z, ZT, ZL, W, WT, WL\n"
            "double tab[250];  // NZ = 250\n"
            "// readSpectra() moved to initialization function.\n"
            "// Must be inside critical block if used here!\n"
            "// readSpectra();\n"
            "mInterp(Ecm/2, inP, outN, tab);\n"
            "return zInterp(log(E/Ecm*2), tab);\n"
            "}}\n"
            "\n"
            "/// Assigns gambit value to parameter, with error-checking.\n"
            "void Assign_Value(std::string parameter, double value)\n"
            "{{\n"
            "int error;\n"
            "char *param = &parameter[0];\n"
            "error = assignVal(param, value);\n"
            "if (error != 0) backend_error().raise(LOCAL_INFO, \""
            "Unable to set \" + std::string(parameter) +\n"
            "    \" in MicrOmegas. MicrOmegas error code: \" + "
            "std::to_string(error)"
            "+ \". Please check your model files.\\n\");\n"
            "}}\n\n"
            "}}\n"
            "END_BE_NAMESPACE\n"
            "\n"
            "// Initialisation function (definition)\n"
            "BE_INI_FUNCTION\n"
            "{{\n"
            "int error;\n"
            "char cdmName[10];\n"
            "\n"
            "const Spectrum& spec = *Dep::{2};\n"
            "const SMInputs& sminputs = spec.get_SMInputs();\n"
            "\n"
            "// YAML options for 3-body final states\n"
            "int VZdecayOpt, VWdecayOpt; // 0=no 3 body final states\n"
            "                            // 1=3 body final states in "
            "annihlations\n"
            "                            // 2=3 body final states in "
            "co-annihilations\n"
            "VZdecayOpt = runOptions->getValueOrDef<int>(1, \"VZdecay\");\n"
            "VWdecayOpt = runOptions->getValueOrDef<int>(1, \"VWdecay\");\n"
            "*VZdecay = VZdecayOpt;\n"
            "*VWdecay = VWdecayOpt;\n"
            "\n"
            "logger() << LogTags::debug << \""
            "Initializing MicrOmegas {0} with \";\n"
            "logger() << \"VWdecay: \" << VWdecay << \" VZdecay: \" << VZdecay"
            " << EOM;\n"
            "\n"
            "// Uncomment below to force MicrOmegas to do calculations in "
            "unitary gauge\n"
            "*ForceUG=1;\n"
            "\n"
            "// BSM parameters\n"
    ).format(gambit_model_name, mo_safe_version, spectrum)


    donotassign = ["vev", "sinW2", "Yu", "Ye", "Yd", "g1", "g2", "g3"]

    # Firstly assign all BSM model parameters
    for param in params:

        # Internally computed
        if param.name in donotassign: continue

        # Ignore the pole masses - do these separately
        if  param.tag == "Pole_Mass": continue

        # Scalar case
        if param.shape == "scalar":
            mo_src += (
                    "Assign_Value(\"{0}\", spec.get(Par::{1}, \"{2}\"));\n"
            ).format(param.name, param.tag, param.alt_name)

        # Vector case
        if param.shape.startswith('v'):
            size = param.shape[1:]
            mo_src += (
                "for(int i=1; i<{0}; i++)\n{{\n"
                "std::string paramname = \"{2}\" + std::to_string(i);\n"
                "Assign_Value(paramname, spec.get(Par::{3}, \"{4}\"));\n"
                "}}\n"
            ).format(i, j, param.name, param.tag, param.alt_name)

        # Matrix case
        if param.shape.startswith('m'):
            size = param.shape[1:]
            i,j = size.split('x')

            mo_src += (
                "for(int i=1; i<{0}; i++)\n{{\n"
                "for(int j=1; j<{1}; j++)\n{{\n"
                "std::string paramname = \"{2}\" + std::to_string(i) + "
                "std::to_string(j);\n"
                "Assign_Value(paramname, spec.get(Par::{3}, \"{4}\"));\n"
                "}}\n}}\n"
            ).format(i, j, param.name, param.tag, param.alt_name)


    # Do pole masses now
    mo_src += "// Masses\n"
    for part in particles:

        chname = calchep_masses[part.PDG_code]
        gbname = pdg_to_particle(part.PDG_code, gambit_pdg_codes)

        mo_src += (
               "Assign_Value(\"{0}\", spec.get(Par::Pole_Mass, \"{1}\"));\n"
        ).format(chname, gbname)

    # SMInputs
    mo_src += "\n// SMInputs\n"

    SMinputs = {1 : 'mD', 2 : 'mU', 3 : 'mS', 4 : 'mCmC', 5:'mBmB', 6:'mT',
                11: 'mE', 13: 'mMu', 15: 'mTau', 23: 'mZ'}

    for pdg, chmass in iteritems(calchep_masses):
        if pdg in SMinputs:
            mo_src += (
                "Assign_Value(\"{0}\", sminputs.{1});\n"
            ).format(chmass, SMinputs[pdg])


    # These are handled slightly differently by SARAH and FeynRules
    if mathpackage == 'sarah':
        mo_src += (
            "\n"
            "// SMInputs constants"
            "Assign_Value(\"Gf\", sminputs.GF); "
            "// Fermi constant\n"
            "Assign_Value(\"aS\", sminputs.alphaS); "
            "// alphaS \n"
            "Assign_Value(\"alfSMZ\", sminputs.alphaS); "
            "// alphaS at mZ - for internal running\n"
            "Assign_Value(\"aEWinv\", sminputs.alphainv); "
            "// Fine structure constant\n\n"
        )
    elif mathpackage == 'feynrules':
        mo_src += (
            "\n"
            "// SMInputs constants"
            "Assign_Value(\"Gf\", sminputs.GF); "
            "// Fermi constant\n"
            "Assign_Value(\"aS\", sminputs.alphaS); "
            "// alphaS \n"
            "Assign_Value(\"aEWM1\", sminputs.alphainv); "
            "// Fine structure constant\n\n"
        )

    # Widths
    mo_src += (
            "\n"
            "// Set particle widths in micrOmegas\n"
            "const DecayTable* tbl = &(*Dep::decay_rates);\n"
            "double width = 0.0;\n"
            "bool present = true;\n"
            "\n"
    )

    for pdg, chwidth in iteritems(calchep_widths):
        # If a particle has zero width don't try and assign it
        if chwidth == "0": continue
        mo_src += (
               "try {{ width = tbl->at(\"{0}\").width_in_GeV; }}\n"
               "catch(std::exception& e) {{ present = false; }}\n"
               "if (present) Assign_Value(\"{1}\", width);\n"
               "present = true;\n\n"
        ).format(pdg_to_particle(pdg, gambit_pdg_codes), chwidth)



    # Get MicrOmegas to do it's thing.
    mo_src += (
            "// Initialise micrOMEGAs mass spectrum\n"
            "error = sortOddParticles(byVal(cdmName));\n"
            "if (error != 0) backend_error().raise(LOCAL_INFO, "
            "\"MicrOmegas function \"\n"
            "        \"sortOddParticles returned error code: \" + "
            "std::to_string(error));\n"
            "\n"
            "}\n"
            "END_BE_INI_FUNCTION\n"
    )

    return indent(mo_src)

def write_micromegas_header(gambit_model_name, mathpackage, params, cap_def):
    """
    Writes a header file for micromegas.
    """

    ## Frontend source file
    intro_message = (
            "///  Frontend for MicrOmegas {0}\n"
            "///  {1} backend."
    ).format(gambit_model_name, mo_version)

    # Frontend header file
    mo_head = blame_gum(intro_message)

    mo_head += (
            "\n"
            "#define BACKENDNAME MicrOmegas_{0}\n"
            "#define BACKENDLANG CC\n"
            "#define VERSION {1}\n"
            "#define SAFE_VERSION {2}\n"
            "#define REFERENCE Belanger:2001fz,Belanger:2004yn,Belanger:2006is,Belanger:2008sj,Belanger:2010gh,Belanger:2013oya,Belanger:2014vza"
            "\n"
            "LOAD_LIBRARY\n"
            "\n"
            "BE_ALLOW_MODELS({0})\n"
            "\n"
            "BE_FUNCTION(assignVal, int, (char*,double),\"assignVal\",\"assignVal\")\n"
            "BE_FUNCTION(vSigma, double, (double, double, int), \"vSigma\",\"vSigma\")\n"
            "BE_FUNCTION(darkOmega, double, (double*, int, double), \"darkOmega\", \"oh2\")\n"
            "BE_FUNCTION(sortOddParticles, int, (char*), \"sortOddParticles\",\"mass_spectrum\")\n"
            "BE_FUNCTION(cleanDecayTable, void, (), \"cleanDecayTable\", \"cleanDecayTable\")\n"
            "BE_FUNCTION(nucleonAmplitudes, int, (double(*)(double,double,double,double), double*, double*, double*, double*), \"nucleonAmplitudes\", \"nucleonAmplitudes\")\n"
            "BE_FUNCTION(FeScLoop, double, (double, double, double, double), \"FeScLoop\", \"FeScLoop\")\n"
            "BE_FUNCTION(calcScalarQuarkFF, void, (double, double, double, double), \"calcScalarQuarkFF\", \"calcScalarQuarkFF\")\n"
            "BE_FUNCTION(calcSpectrum, double, (int, double*, double*, double*, double*, double*, double*, int*), \"calcSpectrum\", \"calcSpectrum\")\n"
            "BE_FUNCTION(printChannels, double, (double, double, double, int, FILE*), \"printChannels\", \"momegas_print_channels\")\n"
            "BE_FUNCTION(oneChannel, double, (double,double,char*,char*,char*,char*), \"oneChannel\", \"get_oneChannel\")\n"
            "BE_FUNCTION(mInterp, int, (double,int,int,double*) , \"mInterp\", \"mInterp\")\n"
            "BE_FUNCTION(zInterp, double, (double,double*) , \"zInterp\", \"zInterp\")\n"
            "BE_FUNCTION(readSpectra, int, (), \"readSpectra\", \"readSpectra\")\n"
            "\n"
            "BE_VARIABLE(mocommon_, MicrOmegas::MOcommonSTR, \"mocommon_\", \"MOcommon\")\n"
            "BE_VARIABLE(vSigmaCh, MicrOmegas::aChannel*, \"vSigmaCh\", \"vSigmaCh\")\n"
            "BE_VARIABLE(ForceUG, int, \"ForceUG\", \"ForceUG\")\n"
            "BE_VARIABLE(VZdecay, int, \"VZdecay\", \"VZdecay\")\n"
            "BE_VARIABLE(VWdecay, int, \"VWdecay\", \"VWdecay\")\n"
            "\n"
            "BE_CONV_FUNCTION(dNdE, double, (double,double,int,int), \"dNdE\")\n"
            "\n"
            "BE_INI_DEPENDENCY({0}_spectrum, Spectrum)\n"
            "BE_INI_DEPENDENCY(decay_rates, DecayTable)\n"
            "\n"
            "#include \"gambit/Backends/backend_undefs.hpp\"\n"
    ).format(gambit_model_name, mo_version, mo_safe_version)

    # Add capability definitions
    cap_def['MicrOmegas_' + gambit_model_name + '_' + mo_safe_version + '_init'] = 'Initialise MicrOmegas ' + gambit_model_name + ' backend.'

    return indent(mo_head)


def copy_micromegas_files(model_name, reset_dict):
    """
    Creates a copy of micrOMEGAs files in $BACKENDS/patches
    """

    # The location of the cleaned (GAMBIT-friendly) CH files
    ch_location = "./../Backends/patches/calchep/3.6.27/Models/" + model_name

    # Move the CH files to patches to copy across
    gb_target = "./../Backends/patches/micromegas/3.6.9.2/" + model_name + "/mdlfiles"
    mkdir_if_absent(gb_target, reset_dict)

    shutil.copyfile(ch_location + "/func1.mdl", gb_target + "/func1.mdl")
    shutil.copyfile(ch_location + "/vars1.mdl", gb_target + "/vars1.mdl")
    shutil.copyfile(ch_location + "/lgrng1.mdl", gb_target + "/lgrng1.mdl")
    shutil.copyfile(ch_location + "/prtcls1.mdl", gb_target + "/prtcls1.mdl")
    shutil.copyfile(ch_location + "/extlib1.mdl", gb_target + "/extlib1.mdl")

    reset_dict['new_files']['files'].append(gb_target + "/func1.mdl")
    reset_dict['new_files']['files'].append(gb_target + "/vars1.mdl")
    reset_dict['new_files']['files'].append(gb_target + "/lgrng1.mdl")
    reset_dict['new_files']['files'].append(gb_target + "/prtcls1.mdl")
    reset_dict['new_files']['files'].append(gb_target + "/extlib1.mdl")

    print("micrOMEGAs files moved to backend dir.")

def patch_micromegas(model_name, reset_dict):
    """
    Patches micrOMEGAs' Makefile to make it usable as a
    shared library. This is generic for every new model.
    """

    towrite = (
        "--- {0}/Makefile    2014-04-03 15:29:30.000000000 +0100\n"
        "+++ {0}/Makefile_patched    2019-10-08 16:23:45.576576545 +0100\n"
        "@@ -45,6 +45,13 @@ libs:\n"
        "    $(MAKE) -C work\n"
        "    $(MAKE) -C lib\n"
        "\n"
        "+sharedlib: all\n"
        "+ifeq (,$(main)) \n"
        "+\t@echo Main program is not specified. Use gmake main='<code of main program>'\n"
        "+else  \n"
        "+\t$(CXX) -shared -fPIC -o libmicromegas.so $(main) $(SSS) $(lDL)\n"
        "+endif\n"
        "+\n"
        " clean: \n"
        "    $(MAKE) -C lib  clean\n"
        "    $(MAKE) -C work clean \n"
    ).format(model_name)

    filename = "micromegas/3.6.9.2/"+model_name+"/patch_micromegas_3.6.9.2_"+model_name+".dif"

    write_file(filename, "Backends", towrite, reset_dict)

    print("micrOMEGAs files patched.")

def add_micromegas_to_cmake(model_name, reset_dict):
    """
    Add a new entry to cmake/backends.cmake for micrOMEGAs_<NEWMODEL>
    """

    towrite = (
            "\n"
            "# MicrOmegas "+model_name+" model\n"
            "set(model \""+model_name+"\")\n"
            "set(patch \"${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/"+model_name+"/patch_${name}_${ver}_${model}.dif\")\n"
            "set(patchdir \"${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/"+model_name+"\")\n"
            "check_ditch_status(${name}_${model} ${ver} ${dir})\n"
            "if(NOT ditched_${name}_${model}_${ver})\n"
            "  ExternalProject_Add(${name}_${model}_${ver}\n"
            "    DOWNLOAD_COMMAND \"\"\n"
            "    SOURCE_DIR ${dir}\n"
            "    BUILD_IN_SOURCE 1\n"
            "    PATCH_COMMAND ./newProject ${model} && patch -p0 < ${patch}\n"
            "    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E copy_directory ${patchdir}/mdlfiles ${dir}/${model}/work/models/\n"
            "    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${CMAKE_MAKE_PROGRAM} sharedlib main=main.c\n"
            "    INSTALL_COMMAND \"\"\n"
            "  )\n"
            "  add_extra_targets(\"backend model\" ${name} ${ver} ${dir}/${model} ${model} \"yes | clean\")\n"
            "  set_as_default_version(\"backend model\" ${name} ${ver} ${model})\n"
            "endif()\n"
            "\n"
    )

    add_to_backends_cmake(towrite, reset_dict, string_to_find="# MontePythonLike")

def add_micromegas_to_darkbit_rollcall(model_name, reset_dict, does_DM_decay):
    """
    Adds entries to the DarkBit rollcall for micrOMEGAs routines.
    - RD_oh2_Xf_MicrOmegas (for non-decaying DM)
        - new BACKEND_OPTION
        - adds to ALLOW_MODELS
    - DD_couplings_MicrOmegas
        - new BACKEND_OPTION
        - adds to ALLOW_MODEL_DEPENDENCE
        - adds to MODEL_GROUP(group2 (...))
    - sigmav_late_universe_MicrOmegas (for non-decaying DM)
        - new BACKEND
    """

    rollcall = full_filename("DarkBit_rollcall.hpp", "DarkBit")


                # Function                  # Capability    # String to write above
    entries = [ ["DD_couplings_MicrOmegas", "DD_couplings", "FORCE_SAME_BACKEND"] ]

    # Only add relic density calculation if DM isn't decaying
    if not does_DM_decay:
        entries.append(["RD_oh2_Xf_MicrOmegas", "RD_oh2_Xf", "ALLOW_MODELS"])
        entries.append(["sigmav_late_universe_MicrOmegas", "sigmav",
                        "FORCE_SAME_BACKEND"])

    # Add the backend options to each entry
    for entry in entries:
        function = entry[0]
        capability = entry[1]
        pattern = entry[2]

        # Find the CAPABILITY + FUNCTION RD_oh2_Xf_MicrOmegas
        exists, line = find_function(function, capability, "DarkBit")

        if not exists:
            raise GumError(("Function {0} not found in DarkBit_rollcall.hpp. "
                            "It should be there!").format(function))

        # Now find the ALLOW_MODELS for the CAPABILITY
        linenum = 0
        with open(rollcall, 'r') as f:
            # Start from the beginning of the FUNCTION
            for i in range(line):
                next(f)
            for num, line in enumerate(f, line):
                if pattern in line:
                    linenum = num
                    break

        # What we want to write
        towrite = (
            "      BACKEND_OPTION((MicrOmegas_{}),(gimmemicro))\n"
            ).format(model_name)
        if function == "RD_oh2_Xf_MicrOmegas":
          towrite += (
            "      ALLOW_MODEL({})\n"
            ).format(model_name)

        if linenum != 0:
            amend_file("DarkBit_rollcall.hpp", "DarkBit", towrite, linenum,
                       reset_dict)
        else:
            raise GumError(("Could not find the string ALLOW_MODELS in "
                            "DarkBit_rollcall, which is very weird."))

    # Add the model to the function arguments
    file = "DarkBit_rollcall.hpp"
    module = "DarkBit"
    add_new_model_to_function(file, module, "DD_couplings",
                              "DD_couplings_MicrOmegas", model_name,
                              reset_dict, pattern="ALLOW_MODEL_DEPENDENCE")
    add_new_model_to_function(file, module, "DD_couplings",
                              "DD_couplings_MicrOmegas", model_name,
                              reset_dict, pattern="MODEL_GROUP(group2")
