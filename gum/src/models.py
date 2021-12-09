#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Master module for all Models related routines.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2019 July
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2019 Sep
#

import numpy as np
import re

from .setup import *
from .files import *

def get_model_parameters(parameters, add_higgs):
    """
    Extracts the model (scan) parameters out of the full parameter list
    """

    model_parameters = []

    for param in parameters:
 
        # if the parameter is in MINPAR or EXTPAR or in any BLOCKIN it's not a
        # model parameter
        if param.block == "MINPAR" or param.block == "EXTPAR" :
            continue
        if param.block != None and param.block.endswith("IN") : 
            continue

        # Nor if it's an output
        if param.is_output :
            continue

        # If there's just a single (SM) Higgs, don't add the vev 
        if add_higgs:
            if param.block == "HMIX" and param.index == 3:
                continue

        # Replace all trailing + and - with pm
        param.name = re.sub(r'(.*)[-+]', r'\1pm', param.name)

        # Don't want the SM-like Higgs mass a fundamental parameter, nor any
        # of the SM Yukawas etc, nor any Pole_Mixings.
        if param.gb_in == "mH" and param.tag == "Pole_Mass": continue
        if param.tag == "Pole_Mixing": continue
        if param.sm == True: continue


        model_parameters.append(param)

    return model_parameters

def get_spectrum_parameters(parameters, params_by_block, bsm_partlist,
                            partlist, gambit_pdgs, with_spheno):
    """
    Extracts the spectrum parameters out of the full parameter list
    """

    # Classes make life easier
    class SpecGetAndSet:

        def __init__(self, shape, size, name, getter, setter, block, index, 
                     tag):
            self.shape = shape
            self.size = size
            self.name = name
            self.getter = getter
            self.setter = setter
            self.block = block
            self.index = index
            self.tag = tag

    spectrum_parameters = []

    # Keep track of which masses we've added
    addedpdgs = []

    for par in parameters:
                
        # TODO: TG: Should we add parameters without block?
        # Parameters without block break at runtime cause there's no way to 
        # access the spectrum info as internally it's a SLHA structure
        if par.block == None:
            continue

        # if the parameter is in MINPAR or EXTPAR or in any BLOCKIN it's not a
        # spectrum parameter
        if par.block == "MINPAR" or par.block == "EXTPAR" :
            continue
        if par.block != None and par.block.endswith("IN") :                  
            continue

        if not isinstance(par, SpectrumParameter):
            raise GumError(("\n\nModel Parameters at position " + str(i) +
                            " not passed as instance of class "
                            "SpectrumParameter."))

        shape = "scalar"
        size = 1

        if par.shape:
            if re.match("v[2-9]", par.shape):
                shape = "vector"
                size = par.shape[-1]
            elif re.match("m[2-9]x[2-9]", par.shape):
                # Assuming all matrices will be square...
                shape = "matrix"
                size = par.shape[-1]

        if par.tag == "Pole_Mass":
            setter = "set_" + par.fullname[1:].strip('~') + "PoleMass"
            getter = "get_" + par.fullname[1:].strip('~') + "PoleMass"
        else:
            setter = "set_" + par.fullname
            getter = "get_" + par.fullname

        name = ""
        if par.tag == "Pole_Mass":
            name = par.fullparticlename
        elif par.tag == "Pole_Mixing":
            # If not using SPheno, don't have mixing matrices as output.
            if not with_spheno:
                continue
            for v in list(params_by_block.values()):
                if not 'mixingmatrix' in v: continue
                if par.name == "sinW2": name = par.name
                elif v['outputname'] == par.name:
                    for p in partlist:
                        if p.alt_name().strip('0123456789') == v['particles']:
                            name = pdg_to_particle(p.pdg(),
                                                   gambit_pdgs).split('_')[0]
        else:
            name = par.name

        # Replace all plusses and minuses with 'pm'
        setter = setter.replace("-","pm").replace("+","pm")
        getter = getter.replace("-","pm").replace("+","pm")

        # Get the block and index if relevant
        block = par.block
        index = par.index

        # Save PDG codes so we don't double count
        if par.tag == "Pole_Mass":
            addedpdgs.append(par.index)

        x = SpecGetAndSet(shape, size, name, getter, setter, block, index, 
                          par.tag)
        spectrum_parameters.append(x)

    # Go through BSM particle list and add the pole masses to the list of 
    # params a spectrum object should interface to 
    for particle in bsm_partlist:

        # Don't double count particles!
        if particle.PDG_code in addedpdgs: 
            continue

        pname = particle.name.strip('~')

        setter = "set_" + pname + "PoleMass"
        getter = "get_" + pname + "PoleMass"

        # Replace all plusses and minuses with 'pm'
        setter = setter.replace("-","pm").replace("+","pm")
        getter = getter.replace("-","pm").replace("+","pm")

        name = pdg_to_particle(particle.PDG_code, gambit_pdgs)
 
        block = "MASS"
        index = abs(particle.PDG_code)

        x = SpecGetAndSet("scalar", 1, name, getter, setter, block, index, 
                          "Pole_Mass")
        spectrum_parameters.append(x)


    return spectrum_parameters


def get_model_par_name(paramname, parameters):
    """
    Get the output name of the model parameter with 
    name or alt_name equal to paramname
    """
    
    for name, param in iteritems(parameters):
        if paramname == param.bcs :
            return name
    for name, param in iteritems(parameters):
        if paramname == param.name or paramname == param.alt_name :
            return param.name


def add_to_model_hierarchy(spectrum_name, model_name, model_params, 
                           model_def = {}, cap_def = {}):
    """
    Adds a model to the model hierarchy. This means we create any
    new header files in the model directory, i.e.
    Models/include/gambit/Models/models/<new_model>.hpp
    """

    print("Writing new spectrum, {0}".format(spectrum_name))

    towrite_header = blame_gum("/// Header file for {0}".format(model_name))
    towrite_header += (
                   "#ifndef __{0}_hpp__\n"
                   "#define __{0}_hpp__\n"
                   "\n"
    ).format(model_name)
    towrite_source = blame_gum("/// Source file for {0}".format(model_name))

    module = "Models"

    towrite_header += (
    			   "#define MODEL {0}"
    			   "\n"
    			   "  START_MODEL\n"
    			   "\n"
    ).format(model_name)

    params = []

    for i in model_params:
        if i.shape == 'scalar' or i.shape == None: params.append(i.gb_in)
        elif re.match("m[2-9]x[2-9]", i.shape): 
            size = int(i.shape[-1])
            for j in range(size):
                for k in range(size):
                    params.append(i.gb_in + '_' + str(j+1) + 'x' + str(k+1))
        elif re.match("v[2-9]", i.shape): 
            size = int(i.shape[-1])
            for j in range(size):
                params.append(i.gb_in + '_' + str(j+1))

    # No double counting (also want to preserve the order)
    norepeats = []
    [norepeats.append(i) for i in params if not i in norepeats]


    # Chunk this up into groups of no more than 9, so the DEFINEPARS macro works
    definepars = [norepeats[i:i+9] for i in range(0,len(norepeats),9)]

    for i in range(len(definepars)):
        towrite_header += "  DEFINEPARS({0})\n".format(', '.join(definepars[i]))

    towrite_header += (
                   "\n"
                   "#undef MODEL\n"
                   "\n"
                   "#endif\n"
    )

    # Add to model and capability definitions
    model_def[model_name] = model_name + " model, created by GUM, with parameters: "
    model_def[model_name] += ", ".join(norepeats)
    cap_def[model_name + '_parameters'] = 'Parameters for the model ' + model_name + ' (see ./gambit ' + model_name + ').'

    return towrite_header

def find_parents_params(parent):
    """
    Returns all params in the parent model.
    """

    module = "Models"
    fname = "models/" + parent + ".hpp"
    location = full_filename(fname, module)

    lookup = "#define MODEL " + parent
    term = "#undef MODEL"

    num = find_string(fname, module, lookup)[1]

    parent_params = []

    with open(location, 'r') as f:
        for num, line in enumerate(f, 1+num):
            if "DEFINEPARS" in line:
                params = re.compile(r"\((.*)\)").search(line).group(1)
                parent_params += params.split(",")
            if term in line:
                break

    return parent_params

def find_tree_root(parent):
    """
    Traces up a model tree to find the 'root' of the model tree,
    i.e. which existing Spectrum a new model is allowed to use.
    """

    module = "Models"
    fname = "models/" + newmodel + ".hpp"

    newmodel = parent
    root = False
    lookup = "#define PARENT "

    while root == False:
        location = full_filename(fname, module)
        if lookup in open(location, 'r').read():
            lines = open(location, 'r').readlines()
            for line in lines:
              if lookup in line:
                newmodel = line.split(' ')[-1].strip('\n')
        else:
            root = True

    return newmodel

def write_spectrumcontents(gambit_model_name, spectrum_parameters):
    """
    Writes SpectrumContents for a new model:
    Models/src/SpectrumContents/<gambit_model>.cpp.
    """

    intro = (
          "///  Class defining the parameters that SubSpectrum\n"
          "///  objects providing " + gambit_model_name + "\n"
          "///  spectrum data must provide."
    )

    towrite = blame_gum(intro)


    towrite += (
            "#ifndef __{0}_contents_hpp__\n"
            "#define __{0}_contents_hpp__\n\n"
            "#include \"gambit/Models/SpectrumContents/RegisteredSpectra.hpp\""
            "\n"
            "\n"
            "namespace Gambit\n"
            "{{\n"
            "SpectrumContents::{0}::{0}()\n"
            "{{\n"
            "setName(\"{0}\");\n"
            "\n"
    ).format(gambit_model_name)

    # Sort out shapes and sizes
    s = False
    v = False
    m = False
    vsizes = []
    msizes = []
    for sp in spectrum_parameters:
        if sp.shape == "scalar":
            s = True
        if sp.shape == "vector":
            v = True
            vsizes.append(sp.size)
        elif sp.shape == "matrix":
            m = True
            msizes.append(sp.size)

    # Scalars first...
    if s:
        towrite += (
                "std::vector<int> scalar = initVector(1);"
                " // i.e. get(Par::Tag, \"name\")\n"
        )

    if v:
        vsizes = list(set(vsizes))
        for size in vsizes:
            towrite += (
                    "std::vector<int> v{0}    = initVector({0});"
                    " // i.e. get(Par::Tag, \"name\", i)\n"
            ).format(size)
            continue
    if m:
        msizes = list(set(msizes))
        for size in msizes:
            towrite += (
                    "std::vector<int> m{0}x{0}  = initVector({0},{0});"
                    " // i.e. get(Par::Tag, \"name\", i, j)\n"
            ).format(size)
            continue

    towrite += "\n"

    # Now add each parameter to the model file.
    for i in np.arange(len(spectrum_parameters)):

        sp = spectrum_parameters[i]
        
        shape = sp.shape
        if sp.shape == "vector":
            shape = "v" + str(sp.size)
        if sp.shape == "matrix":
            shape = "m" + str(sp.size) + "x" + str(sp.size)

        # If we've extracted some information about the block, then
        # add the information to the addParameter macro
        if sp.block:
            extra = ", \"" + sp.block + "\", " + str(sp.index)
        else: extra = ""

        # Write the addParameter macro to initialise each SpectrumParameter
        # object within the SubSpectrum.

        #e = mp.fullparticlename if mp.tag == "Pole_Mass" else mp.name
        towrite += (
                "addParameter(Par::{0}, \"{1}\", {2}{3});\n"
                ).format(sp.tag.replace("\"",""), sp.name,
                         shape, extra)


    towrite += (
            "\n"
            "} // namespace Models\n"
            "} // namespace Gambit\n"
            "#endif\n"
    )

    contents = indent(towrite)
    return contents

def write_subspectrum_wrapper(gambit_model_name, spectrum_parameters):

    """
    Writes spectrum object wrapper for new model:
    Models/include/gambit/Models/SimpleSpectra/<new_model_name>SimpleSpec.hpp.
    """

    modelSS = gambit_model_name + "SimpleSpec"
    modelclass = gambit_model_name + "Model"

    # Go through model, and create down all members of the model object,
    # all getter functions, all setter functions, all sizes...

    intro_message = (
            "///  A simple SubSpectrum wrapper for\n"
            "///  " + gambit_model_name + ". No RGEs included."
    )

    towrite = blame_gum(intro_message)

    towrite += (
            "#ifndef __{0}_hpp__\n"
            "#define __{0}_hpp__\n"
            "\n"
            "#include \"gambit/Elements/spec.hpp\"\n"
            "#include \"gambit/Models/SpectrumContents/"
            "RegisteredSpectra.hpp\"\n"
            "\n"
            "namespace Gambit\n"
            "{{\n"
            "namespace Models\n"
            "{{\n"
            "/// Simple {1} model object.\n"
            "class {2} : public SLHAeaModel\n"
            "{{\n"
            "\n"
            "public:\n"
            "\n"
            "/// Default uncertainty\n"
            "double default_uncert = 0.3;\n"
            "\n"
            "  /// @{{ Constructors\n"
            "{2}(const SLHAstruct &input)\n"
            " : SLHAeaModel(input)\n"
            "{{}}\n"
            "  /// @}}\n"
            "\n"
            "  /// @{{ Getters for {1} information\n"
    ).format(modelSS, gambit_model_name, modelclass)

    # Getter functions
    for i in np.arange(len(spectrum_parameters)):

        sp = spectrum_parameters[i]

        if sp.shape == "scalar":
            size = ""
            indices = sp.index
        if sp.shape == "vector":
            size = "int i"
            indices = "i"
        elif sp.shape == "matrix":
            size = "int i, int j"
            indices = "i,j"

        towrite += (
          "double {0}({1}) const {{ return getdata(\"{2}\",{3}); }}\n"
        ).format(sp.getter, size, sp.block, indices)

        # For pole masses add uncertainty
        if "PoleMass" in sp.getter:
            getter_low = sp.getter + '_1srd_low'
            getter_high = sp.getter + '_1srd_high'
            dmassblock = 'DMASS'
            towrite += (
                "double {0}({2}) const\n"
                "{{\n"
                "if (checkdata(\"{3}\",{4})) return getdata(\"{3}\",{4});\n"
                "else return default_uncert;\n"
                "}}\n"
                "double {1}({2}) const\n"
                "{{\n"
                "if (checkdata(\"{3}\",{4})) return getdata(\"{3}\",{4});\n"
                "else return default_uncert;\n"
                "}}\n"
            ).format(getter_low, getter_high, size, dmassblock, indices)

    towrite += "  /// @}}\n\n"

    towrite += (
            "}};\n"
            "\n"
            "/// Forward declare the wrapper class so that we can use it\n"
            "/// as the template parameter for the SpecTraits specialisation.\n"
            "class {0};\n"
            "}}"
            "\n"
            "\n"
            "/// Specialisation of traits class needed to inform "
            "base spectrum class of the Model and Input types\n"
            "template <> \n"
            "struct SpecTraits<Models::{0}> : DefaultTraits\n"
            "{{\n"
            "static std::string name() {{ return \"{0}\"; }}\n"
            "typedef SpectrumContents::{1} Contents;\n"
            "typedef Models::{2} Model;\n"
            "}};\n"
            "\n"
            "namespace Models\n"
            "{{\n"
            "class {0} : public SLHASimpleSpec<{0}>\n"
            "{{\n"
            "\n"
            "public:\n"
            "  /// @{{\n"
            "/// Constructor via SLHAea object\n"
            "{0}(const SLHAea::Coll& input)\n"
            " : SLHASimpleSpec(input)\n"
            "{{}}\n"
            "\n"
            "/// Copy constructor\n"
            "{0}(const {0}& other)\n"
            " : SLHASimpleSpec(other)\n"
            "{{}}\n"
            "\n"
            "/// Destructor\n"
            "virtual ~{0}() {{}};\n"
            "\n"
            "static int index_offset() {{return 0;}}\n"
            "\n"
            "/// Construct the SubSpectrumContents\n"
            "const SpectrumContents::{1} contents;\n"
            "\n"
            "/// Add SLHAea object using the SimpleSpec_to_SLHAea routine\n"
            "void add_to_SLHAea(int /*slha_version*/, SLHAea::Coll& slha) "
            "const\n"
            "{{\n"
            "// Add SPINFO data if not already present\n"
            "SLHAea_add_GAMBIT_SPINFO(slha);\n"
            "\n"
            "// All blocks given in the SimpleSpec\n"
            "\nadd_SimpleSpec_to_SLHAea(*this, slha, contents);\n"
            "}}\n"
            "\n" 
            "/// Wrapper functions to parameter object.\n"
    ).format(modelSS, gambit_model_name, modelclass)

    towrite += (
            "\n"
            "/// Map fillers\n"
            "static GetterMaps fill_getter_maps()\n"
            "{\n"
            "GetterMaps getters;\n"
            "\n"
    )

    # Add necessary function pointer maps.
    v = False
    m = False
    sizes = []
    for i in range(0, len(spectrum_parameters)):
        sp = spectrum_parameters[i]
        if sp.shape == "vector":
            v = True
            sizes.append(sp.size)
        elif sp.shape == "matrix":
            m = True
            sizes.append(sp.size)

    if m:
        towrite += "typedef typename MTget::FInfo2 FInfo2;\n"
    if v:
        towrite += "typedef typename MTget::FInfo1 FInfo1;\n"

    # Remove all duplicates. These values tell us which indices we need to
    # include for the FInfo routines.
    sizes = list(set(sizes))

    for i in np.arange(len(sizes)):
        fnname = "i" + "".join(str(j+1) for j in np.arange(int(sizes[i])))

        towrite += (
                "static const int {0}v[] = {{{1}}};\n"
                "static const std::set<int> {0}({0}v, Utils::endA({0}v));"
                "\n"
        ).format(fnname, ",".join(str(j+1) for j in np.arange(int(sizes[i]))))

    towrite += "\nusing namespace Par;\n\n"

    # Now add getter maps
    for sp in spectrum_parameters:

        if sp.shape == "scalar":
            size = "0"
            finf = " &Model::{}".format(sp.getter)
        elif sp.shape == "vector":
            size = "1"
            index = "i" + "".join(str(j+1) for j in np.arange(int(sp.size)))
            finf = "FInfo1(&Model::{0}, {1})".format(sp.getter, index)
        elif sp.shape == "matrix":
            size = "2"
            index = "i" + "".join(str(j+1) for j in np.arange(int(sp.size)))
            finf = "FInfo2(&Model::{0}, {1}, {1})".format(sp.getter, index)

        towrite += (
                "getters[{0}].map{1}"
                "[\"{2}\"] = {3};\n"
        ).format(sp.tag, size, sp.name, finf)

        # Add uncertainties for pole masses
        if sp.tag == "Pole_Mass" and size == "0":
            tag_low = sp.tag + '_1srd_low'
            tag_high = sp.tag + '_1srd_high'
            finf_low = finf + '_1srd_low'
            finf_high = finf + '_1srd_high'
            towrite += (
                    "getters[{0}].map{2}"
                    "[\"{3}\"] = {4};\n"
                    "getters[{1}].map{2}"
                    "[\"{3}\"] = {5};\n"
            ).format(tag_low, tag_high, size, sp.name, finf_low, finf_high)

    towrite += (
            "\n"
            "return getters;\n"
            "}\n"
            "\n"
    )

    towrite += (
            "};\n"
            "}\n"
            "} // namespace Gambit\n"
            "#endif\n"
    )

    contents = indent(towrite)
    return contents

def add_to_registered_spectra(gambit_model):
    """
    Adds new model entry to RegisteredSpectra.hpp
    """

    lookup = "SubSpectrumContents"
    newentry = (
             "    struct {0:21}: SubSpectrumContents {{ {0}(); }};\n"
    ).format(gambit_model)
    filename = "SpectrumContents/RegisteredSpectra.hpp"
    module = "Models"
    location = full_filename(filename, module)
    linenum = 0 # Position of last entry in RegisteredSpectra
    with open(location) as f:
        for num, line in enumerate(f, 1):
            if lookup in line:
                linenum = num
            if newentry in line:
                raise GumError(("\n\nModel {0} already exists in GAMBIT."
                               ).format(gambit_model))

    return newentry, linenum
