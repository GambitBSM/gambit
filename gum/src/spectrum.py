#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Master module for all SpecBit related routines.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019, 2020
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2019, 2020
#
#  **************************************

from .setup import *
from .files import *
from .cmake_variables import *
from .colliderbit import *

def write_spectrum(gambit_model_name, model_parameters, spec,
                   add_higgs, with_spheno, gambit_pdgs,
                   neutral_higgses, charged_higgses, blockdict, 
                   particles, spheno_decays, partlist):
    """
    Writes the spectrum object wrapper for new model:
    SpecBit/src/SpecBit_<new_model_name>.cpp.

    GUM will create a basic spectrum container unless the user has
    specified SPheno output. If so the spectrum object will be built by 
    interfacing to SPheno. This also contains routines to interface to
    HiggsBounds/HiggsSignals via the GAMBIT HiggsCouplingTable.
    """

    modelSS = gambit_model_name + "SimpleSpec"
    modelclass = gambit_model_name + "Model"
    modelcont = gambit_model_name + "model"

    is_susy = True if "MSSM" in gambit_model_name else False
        
    intro_message = (
            "///  Implementation of SpecBit routines for \n"
            "///  " + gambit_model_name + "."
    )

    towrite = blame_gum(intro_message)

    higgsdefined = False

    # Simple spectrum wrapper for a new model with no SPheno interface.
    if not with_spheno:

        towrite += (
                "#include <string>\n"
                "#include <sstream>\n"
                "\n"
                "#include \"gambit/Elements/gambit_module_headers.hpp\"\n"
                "#include \"gambit/Elements/spectrum.hpp\"\n"
                "#include \"gambit/Elements/spectrum_factories.hpp\"\n"
                "#include \"gambit/Utils/stream_overloads.hpp\"\n"
                "#include \"gambit/Utils/util_macros.hpp\"\n"
                "\n"
                "#include \"gambit/SpecBit/SpecBit_rollcall.hpp\"\n"
                "#include \"gambit/SpecBit/SpecBit_helpers.hpp\"\n"
                "#include \"gambit/Models/SpectrumContents/RegisteredSpectra.hpp\""
                "\n"
                "#include \"gambit/SpecBit/QedQcdWrapper.hpp\"\n"
                "#include \"gambit/Models/SimpleSpectra/{0}.hpp\"\n"
        ).format(modelSS, gambit_model_name)

        # If there's a Higgs dependency 
        if add_higgs:
            towrite += (
                    "#include \"gambit/Models/SimpleSpectra/"
                    "SMHiggsSimpleSpec.hpp\"\n"
            )
        
        towrite += (
                "\n\n"
                "namespace Gambit\n"
                "{{\n"
                "\n"
                "namespace SpecBit\n"
                "{{\n"
                "using namespace LogTags;\n"
                "\n"
                "/// Get a (simple) Spectrum object wrapper for {0} model.\n"
                "void get_{0}(Spectrum& result)\n"
                "{{\n"
                "namespace myPipe = Pipes::get_{0};\n"
                "const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;\n"
                "\n"
                "// Initialise SLHAea object \n"
                "SLHAstruct slha;\n"
        ).format(spec, modelclass, modelcont)

        # List of added blocks
        addedblocks = []

        for block, entry in iteritems(blockdict):

            # Ignore the SM blocks, add them... en bloc (sorry) in a bit
            # Same with masses.
            if block in ["GAUGE", "SINTHETAW", "YU", "YE", "YD", 
                         "MASS", "SMINPUTS", "VEVS"]:
                continue

            # Don't add the SM Higgs vev if it's just a 1 Higgs SM extension
            if block == "HMIX" and add_higgs:
                continue

            matrix = False
            size = ""

            # If it's a matrix, flag it, and get the size. 
            if 'matrix' in entry:
                matrix = True
                size = entry['matrix']

            elif 'mixingmatrix' in entry:
                matrix = True
                size = entry['mixingmatrix']

            # TODO do we want mixing matrices in the SLHAea object here??
            if 'mixingmatrix' in entry:
                continue

            # Firstly create the block
            towrite += (
                    "\n"
                    "// Block {0}\n"
                    "SLHAea_add_block(slha, \"{0}\");\n"
            ).format(block)

            # Add it to the list
            addedblocks.append(block)

            # If we don't have a matrix, use the block indices
            if not matrix:
                for index, param in iteritems(entry):

                    paramdef = ""

                    # Try to find the corresponding model parameter
                    for i in range(0, len(model_parameters)):
                        par = model_parameters[i] 

                        # Don't have anything that's an output of spectrum
                        # computation as a scan parameter
                        if par.is_output: continue
                        
                        if par.fullname == param:
                            paramdef = "*myPipe::Param[\"{0}\"]".format(par.gb_in)

                    if not paramdef:
                        raise GumError("Parameter " + par.fullname + " not found.")

                    towrite += (
                            "SLHAea_add(slha, \"{0}\", {1}, {2});\n"
                    ).format(block, index, paramdef)

            # Matrix case.
            else:
                paramdef = ""

                # Get the size of the matrix
                x,y = size.split('x')

                for i in range(int(x)):
                    for j in range(int(y)):

                        towrite += (
                                "SLHAea_add(slha, \"{0}\", {1}, {2}, "
                                "*myPipe::Param[\"{3}_{1}x{2}\"], " 
                                "\"{3}({1},{2})\");\n"
                        ).format(block, i+1, j+1, entry['outputname'])

        # Create a dict of the GB input params - SARAH names
        d = {}
        savedparams = []
        for p in model_parameters:
            d[p.alt_name] = p.gb_in

        # Get the name of the SM Higgs vev
        smvevname = "vev"
        if add_higgs:
            for p in model_parameters:
                if p.block == "HMIX" and p.index == 3:
                    smvevname = p.name
            towrite += (
                "double {0} = 1. / sqrt(sqrt(2.)*sminputs.GF);\n"
                "double sqrt2v = pow(2.0,0.5)/{0};\n"
                "\n"
                "SLHAea_add_block(slha, \"VEVS\");\n"
                "SLHAea_add(slha, \"VEVS\", 1, {0});\n"
                "\n"
                "SLHAea_add_block(slha, \"HMIX\");\n"
                "SLHAea_add(slha, \"HMIX\", 3, {0});\n"
                "\n"
            ).format(smvevname)
            savedparams.append(smvevname)

        # Now do the mass block. 
        towrite += (
                "\n"
                "// Block MASS\n"
                "SLHAea_add_block(slha, \"MASS\");\n"
        ).format(smvevname)

        # Masses should also be input parameters in this setup, unless we have
        # a definition for their tree-level mass, defined by the other params.
        for particle in particles:

            mass = ""
            if particle.PDG_code == 25 and add_higgs: 
                mass = "*myPipe::Param[\"mH\"]"
            else:
                mass = "*myPipe::Param[\"{0}\"]".format(particle.mass)

            # Check to see if there is a tree-level mass description. If so
            # add it to the Spectrum src code.
            if particle.tree_mass:
                tree = particle.tree_mass

                # If the tree mass is NotValid is because the particle belongs
                # to a multiplet and SARAH's tree level mass will not give the 
                # correct mixings. In this case one should use a spectrum generator
                # We thus throw an error
                if tree == "NotValid":
                  raise GumError(("Particle {} is in a multiplet. "
                                  "Tree level masses do not work. "
                                  "Please select a spectrum generator (e.g. SPheno) as output."
                            ).format(particle.name))

                # Clean up the output of Mathematica's CForm...
                # Common replacements to actual C(++) syntax
                # Probably not complete, but the main culprits *should* be here
                tree = re.sub('ArcSin', 'asin', tree)
                tree = re.sub('ArcCos', 'acos', tree)
                tree = re.sub('ArcTan', 'atan', tree)
                tree = re.sub('Abs', 'abs', tree) 
                tree = re.sub('Sin', 'sin', tree)
                tree = re.sub('Cos', 'cos', tree)
                tree = re.sub('Tan', 'tan', tree)
                tree = re.sub('Sqrt', 'sqrt', tree)
                # If there's Power(param, num) -> pow(param, num)
                tree = re.sub(r'Power\(([a-zA-Z]+),([0-9])\)',r'pow(\1,\2)', tree)

                # Mass string is the stuff between the quotes.
                mass = re.findall(r'"(.*?)"', mass)[0] 

                # Also save each param that appears in these definitions
                strings = re.findall(r'\b\w+\b', tree)
                for s in strings:
                    if s in d:
                        if not s in savedparams:
                            savedparams.append(s)
                            towrite += (
                                "double {0} = *myPipe::Param[\"{1}\"];\n"
                            ).format(s, d[s])
                
                towrite += "double {0} = sqrt({1});\n".format(mass, tree)

                # Higgs is defined by other parameters, don't add it elsewhere.
                if particle.PDG_code == 25 and add_higgs:
                    higgsdefined = True

            towrite += (
                    "SLHAea_add(slha, \"MASS\", {0}, {1});\n"
            ).format(particle.PDG_code, mass)

        if add_higgs:
            towrite += add_simple_sminputs()

        towrite += (
                "// Retrieve any mass cuts\n"
                "static const Spectrum::mc_info mass_cut = "
                "myPipe::runOptions->getValueOrDef<Spectrum::mc_info>"
                "(Spectrum::mc_info(), \"mass_cut\");\n"
                "static const Spectrum::mr_info mass_ratio_cut = "
                "myPipe::runOptions->getValueOrDef<Spectrum::mr_info>"
                "(Spectrum::mr_info(), \"mass_ratio_cut\");\n"
                "\n"
                "// Construct the Spectrum object from the SLHAea inputs\n"
                "result = spectrum_from_SLHAea<Gambit::Models::{0}SimpleSpec,"
                " SLHAstruct>(slha,slha,mass_cut,mass_ratio_cut);\n"
                "}}\n\n"
        ).format(gambit_model_name)

    # If we have SPheno, make the spectrum use it.
    else:
        towrite += (
                "#include <cmath>\n"
                "#include \"gambit/Elements/gambit_module_headers.hpp\"\n"
                "#include \"gambit/Elements/spectrum_factories.hpp\"\n"
                "#include \"gambit/Elements/smlike_higgs.hpp\"\n"
                "#include \"gambit/Models/SimpleSpectra/{0}SimpleSpec.hpp\"\n"
                "#include \"gambit/SpecBit/SpecBit_rollcall.hpp\"\n"
                "#include \"gambit/SpecBit/SpecBit_helpers.hpp\"\n"
                "\n"
                "namespace Gambit\n"
                "{{\n"
                "\n"
                "namespace SpecBit\n"
                "{{\n"
                "using namespace LogTags;\n"
                "\n"
        ).format(gambit_model_name)

        towrite += write_spheno_spectrum_src(gambit_model_name, is_susy)

        # Add the HiggsCouplingTable via SPheno 
        towrite += write_spheno_higgsbounds_interface(gambit_model_name, 
                                                      gambit_pdgs,
                                                      neutral_higgses,
                                                      charged_higgses,
                                                      spheno_decays, partlist)

    towrite += '\n'

    # Printing, fill_map_from_spectrum, and wrap it up. 
    towrite += (
            "// Declaration: print spectrum out\n"
            "void fill_map_from_{2}_spectrum(std::map<std::string,double>&, "
            "const Spectrum&);\n\n"
            "void get_{2}_spectrum_as_map" 
            "(std::map<std::string,double>& specmap)\n"
            "{{\n"
            "namespace myPipe = Pipes::get_{3}_as_map;\n"
            "const Spectrum& spec(*myPipe::Dep::{3});\n"
            "fill_map_from_{2}_spectrum(specmap, spec);\n"
            "}}\n\n"
            "void fill_map_from_{2}_spectrum"
            "(std::map<std::string, double>& specmap, "
            "const Spectrum& spec)\n"
            "{{\n"
            "/// Use SpectrumContents routines to automate\n"
            "static const SpectrumContents::{2} contents;\n"
            "static const std::vector<SpectrumParameter> "
            "required_parameters = contents.all_parameters();\n\n"
            "for(std::vector<SpectrumParameter>::const_iterator "
            "it = required_parameters.begin(); "
            "it != required_parameters.end(); ++it)\n"
            "{{\n"
            "const Par::Tags        tag   = it->tag();\n"
            "const std::string      name  = it->name();\n"
            "const std::vector<int> shape = it->shape();\n"
            "\n"
            "// Scalar case\n"
            "if(shape.size()==1 and shape[0]==1)\n"
            "{{\n"
            "std::ostringstream label;\n"
            "label << name <<\" \"<< Par::toString.at(tag);\n"
            "specmap[label.str()] = spec.get_HE().get(tag,name);\n"
            "}}\n"
            "// Vector case\n"
            "else if(shape.size()==1 and shape[0]>1)\n"
            "{{\n"
            "for(int i = 1; i<=shape[0]; ++i)\n"
            "{{\n"
            "std::ostringstream label;\n"
            "label << name <<\"_\"<<i<<\" \"<< Par::toString.at(tag);\n"
            "specmap[label.str()] = spec.get_HE().get(tag,name,i);\n"
            "}}\n"
            "}}\n"
            "// Matrix case\n"
            "else if(shape.size()==2)\n"
            "{{\n"
            "for(int i = 1; i<=shape[0]; ++i)\n"
            "{{\n"
            "for(int j = 1; j<=shape[0]; ++j)\n"
            "{{\n"
            "std::ostringstream label;\n"
            "label << name <<\"_(\"<<i<<\",\"<<j<<\") \""
            "<<Par::toString.at(tag);\n"
            "specmap[label.str()] = spec.get_HE().get(tag,name,i,j);\n"
            "}}\n"
            "}}\n"
            "}}\n"
            "// Deal with all other cases\n"
            "else\n"
            "{{\n"
            "// ERROR\n"
            "std::ostringstream errmsg;\n"
            "errmsg << \"Invalid parameter received while converting " 
            "{3} to map of strings!\";\n"
            "errmsg << \"Problematic parameter was: \"<< tag "
            "<<\", \" << name << \", shape=\"<< shape;\n"
            "utils_error().forced_throw(LOCAL_INFO,errmsg.str());\n"
            "}}\n"
            "}}\n"
            "}}\n\n"
            "}}\n\n"
            "}}\n"
    ).format(modelSS, modelcont, gambit_model_name, spec)
            
    return indent(towrite), higgsdefined
    
    
def write_spectrum_header(model_name, add_higgs, with_spheno, higgses, cap_def={}):
    """
    Writes the header for spectrum object,
    SpecBit/include/gambit/SpecBit/SpecBit_<model>_rollcall.hpp
    """

    clean_model_name = model_name.replace('-','').replace('_','')
    
    towrite = blame_gum(("///  Rollcall declarations for routines declared \n"
                         "///  in SpecBit_{0}.cpp.".format(model_name)))
    
    towrite += (
            "#ifndef __SpecBit_{0}_hpp__\n"
            "#define __SpecBit_{0}_hpp__\n"
            "\n"
            "  // Spectrum object\n"
            "  #define CAPABILITY {0}_spectrum\n"
            "  START_CAPABILITY\n"
            "\n"
    ).format(model_name)

    # Add a conditional Higgs dependency if necessary
    if add_higgs and not with_spheno:
       modelentry = (
                "ALLOW_MODEL_DEPENDENCE(StandardModel_Higgs, {0})\n"
                "MODEL_GROUP(higgs, (StandardModel_Higgs))\n"
                "MODEL_GROUP({1}, ({0}))\n"
                "ALLOW_MODEL_COMBINATION(higgs, {1})\n"
        ).format(model_name, model_name + "_group")
    else:
        modelentry = "ALLOW_MODELS("+model_name+")\n"

    if with_spheno:
        towrite += dumb_indent(4, (
                "// =========================\n"
                "// {0} spectrum (from SARAH-generated SPheno)\n"
                "//\n"
                "#define FUNCTION get_{0}_spectrum_SPheno\n"
                "START_FUNCTION(Spectrum)\n"
                "{3}"
                "DEPENDENCY(SMINPUTS, SMInputs)\n"
                "BACKEND_REQ(SARAHSPheno_{0}_spectrum, (libSPheno{2}), int, "
                "(Spectrum&, const Finputs&) )\n"
                "BACKEND_OPTION((SARAHSPheno_{0}, {1}), (libSPheno{2}))\n"
                "#undef FUNCTION\n"
                "\n"
        ).format(model_name, SPHENO_VERSION, clean_model_name, modelentry))
    # If we want to make a simple container spectrum only.
    else:
        towrite += dumb_indent(4, (
            "// Create simple object from SMInputs & new params.\n"
            "#define FUNCTION get_{0}_spectrum\n"
            "START_FUNCTION(Spectrum)\n"
            "DEPENDENCY(SMINPUTS, SMInputs)\n"
            "{1}"
            "#undef FUNCTION\n"
            "\n"
        ).format(model_name, modelentry))

    towrite += (
        "    // Map for Spectrum, for printing.\n"
        "    #define FUNCTION get_{0}_spectrum_as_map\n"
        "    START_FUNCTION(map_str_dbl)\n"
        "    DEPENDENCY({0}_spectrum, Spectrum)\n"
        "    ALLOW_MODELS({0})\n"
        "    #undef FUNCTION\n"
        "\n"
        "  #undef CAPABILITY\n"
        "\n"
    ).format(model_name)

    if with_spheno:

        # HiggsBounds output
        towrite += dumb_indent(2, (
                "// Generalised Higgs couplings\n"
                "#define CAPABILITY Higgs_Couplings\n"
                "\n"
                "  // From partial widths\n"
                "  #define FUNCTION {0}_higgs_couplings_SPheno\n"
                "  START_FUNCTION(HiggsCouplingsTable)\n"
                "  DEPENDENCY({0}_spectrum, Spectrum)\n"
                "  // DecayTable to provide us with the decays\n"
                "  DEPENDENCY(decay_rates, DecayTable)\n"
                "  BACKEND_REQ(SARAHSPheno_{0}_HiggsCouplingsTable, (libSPheno{0}), int, (const Spectrum&, HiggsCouplingsTable&, const Finputs&) )\n"
                "  ALLOW_MODELS({0})\n"
                "  #undef FUNCTION\n"
                "\n"
                "#undef CAPABILITY\n"
                "\n"
        ).format(model_name))

    towrite += "#endif\n"

    # Add capability definitions
    cap_def[model_name + '_spectrum'] = 'Create spectrum object for ' + model_name + ' model.'

    return towrite
    
def write_specbit_rollcall(model_name):
    """
    Writes the entry for the SpecBit rollcall header.
    """
    
    towrite = (
            "\n"
            "/// Module function declarations for SpecBit_{0}.cpp\n"
            "#include \"gambit/SpecBit/SpecBit_{0}_rollcall.hpp\"\n"
            "\n"    
    ).format(model_name)
    
    return dumb_indent(2, towrite)
    
def add_simple_sminputs():
    """
    Adds simple SMInputs definitions to a spectrum object.
    """

    towrite = (
            "\n"
            "// quantities needed to fill container spectrum\n"
            "double alpha_em = 1.0 / sminputs.alphainv;\n"
            "double C = alpha_em * pi / (sminputs.GF * pow(2,0.5));\n"
            "double sinW2 = 0.5 - pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);\n"
            "double cosW2 = 0.5 + pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);\n"
            "double e = pow( 4*pi*( alpha_em ),0.5);\n"
            "\n"
            "SLHAea_add_block(slha, \"GAUGE\");\n"
            "SLHAea_add(slha, \"GAUGE\", 1, sqrt(5/3) * e / sqrt(cosW2) );\n"
            "SLHAea_add(slha, \"GAUGE\", 2, e / sqrt(sinW2));\n"
            "SLHAea_add(slha, \"GAUGE\", 3, pow( 4*pi*sminputs.alphaS,0.5) );\n"
            "\n"
            "SLHAea_add_block(slha, \"SINTHETAW\");\n"
            "SLHAea_add(slha, \"SINTHETAW\", 1, sinW2);\n"
            "\n"
            "SLHAea_add_block(slha, \"YU\");\n"
            "SLHAea_add(slha, \"YU\", 1, 1, sqrt2v*sminputs.mU, \"u\");\n"
            "SLHAea_add(slha, \"YU\", 1, 2, 0., \"\");\n"
            "SLHAea_add(slha, \"YU\", 1, 3, 0., \"\");\n"
            "SLHAea_add(slha, \"YU\", 2, 1, 0., \"\");\n"
            "SLHAea_add(slha, \"YU\", 2, 2, sqrt2v*sminputs.mCmC, \"c\");\n"
            "SLHAea_add(slha, \"YU\", 2, 3, 0., \"\");\n"
            "SLHAea_add(slha, \"YU\", 3, 1, 0., \"\");\n"
            "SLHAea_add(slha, \"YU\", 3, 2, 0., \"\");\n"
            "SLHAea_add(slha, \"YU\", 3, 3, sqrt2v*sminputs.mT, \"t\");\n"
            "\n"
            "SLHAea_add_block(slha, \"YE\");\n"
            "SLHAea_add(slha, \"YE\", 1, 1, sqrt2v*sminputs.mE, \"e\");\n"
            "SLHAea_add(slha, \"YE\", 1, 2, 0., \"\");\n"
            "SLHAea_add(slha, \"YE\", 1, 3, 0., \"\");\n"
            "SLHAea_add(slha, \"YE\", 2, 1, 0., \"\");\n"
            "SLHAea_add(slha, \"YE\", 2, 2, sqrt2v*sminputs.mMu, \"mu\");\n"
            "SLHAea_add(slha, \"YE\", 2, 3, 0., \"\");\n"
            "SLHAea_add(slha, \"YE\", 3, 1, 0., \"\");\n"
            "SLHAea_add(slha, \"YE\", 3, 2, 0., \"\");\n"
            "SLHAea_add(slha, \"YE\", 3, 3, sqrt2v*sminputs.mTau, \"tau\");\n"
            "\n"
            "SLHAea_add_block(slha, \"YD\");\n"
            "SLHAea_add(slha, \"YD\", 1, 1, sqrt2v*sminputs.mD, \"d\");\n"
            "SLHAea_add(slha, \"YD\", 1, 2, 0., \"\");\n"
            "SLHAea_add(slha, \"YD\", 1, 3, 0., \"\");\n"
            "SLHAea_add(slha, \"YD\", 2, 1, 0., \"\");\n"
            "SLHAea_add(slha, \"YD\", 2, 2, sqrt2v*sminputs.mS, \"s\");\n"
            "SLHAea_add(slha, \"YD\", 2, 3, 0., \"\");\n"
            "SLHAea_add(slha, \"YD\", 3, 1, 0., \"\");\n"
            "SLHAea_add(slha, \"YD\", 3, 2, 0., \"\");\n"
            "SLHAea_add(slha, \"YD\", 3, 3, sqrt2v*sminputs.mBmB, \"b\");\n"
            "\n"
            "// Block SMINPUTS\n"
            "SLHAea_add_block(slha, \"SMINPUTS\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 1, sminputs.alphainv, \"# alpha_em^-1(MZ)^MSbar\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 2, sminputs.GF, \"# G_mu [GeV^-2]\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 3, sminputs.alphaS, \"# alpha_s(MZ)^MSbar\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 4, sminputs.mZ, \"# m_Z(pole)\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 5, sminputs.mBmB, \"# m_b(m_b), MSbar\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 6, sminputs.mT, \"# m_t(pole)\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 7, sminputs.mTau, \"# m_tau(pole)\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 8, sminputs.mNu3, \"# m_nu_3\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 11, sminputs.mE, \"# m_e(pole)\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 12, sminputs.mNu1, \"# m_nu_1\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 13, sminputs.mMu, \"# m_muon(pole)\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 14, sminputs.mNu2, \"# m_nu_2\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 21, sminputs.mD, \"# m_d(2 GeV), MSbar\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 22, sminputs.mU, \"# m_u(2 GeV), MSbar\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 23, sminputs.mS, \"# m_s(2 GeV), MSbar\");\n"
            "SLHAea_add(slha, \"SMINPUTS\", 24, sminputs.mCmC, \"# m_c(m_c), MSbar\");\n"
            "\n"
            "// And the W for good measure\n"
            "SLHAea_add(slha, \"MASS\", 24, sminputs.mW);\n"
            "\n"
    )
      
    return towrite
    
"""
SPHENO-SPECTRA
"""

def write_spheno_spectrum_src(model_name, is_susy):
    """
    Writes SpecBit/src/SpecBit_<MODEL>.cpp
    for a Spectrum object interface to SPheno.
    """

    towrite = (
            "void get_{0}_spectrum_SPheno(Spectrum& spectrum)\n"
            "{{\n"
            "namespace myPipe = Pipes::get_{0}_spectrum_SPheno;\n"
            "const SMInputs &sminputs = *myPipe::Dep::SMINPUTS;\n"
            "\n"
            "// Set up the input structure\n"
            "Finputs inputs;\n"
            "inputs.sminputs = sminputs;\n"
            "inputs.param = myPipe::Param;\n"
            "inputs.options = myPipe::runOptions;\n"
            "\n"
            "// Retrieve any mass cuts\n"
            "static const Spectrum::mc_info mass_cuts = myPipe::runOptions->"
            "getValueOrDef<Spectrum::mc_info>(Spectrum::mc_info(), \"mass_cut\""
            ");\n"
            "\n"
            "// Get the spectrum from the Backend\n"
            "myPipe::BEreq::SARAHSPheno_{0}_spectrum(spectrum, inputs);\n"
            "\n"
            "// Drop SLHA files if requested\n"
            "spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "
            "\"GAMBIT_unimproved_spectrum\");\n"
    ).format(model_name)

    # If it's a susy model, GAMBIT only supports neutralino LSP (for now)
    if (is_susy):
        towrite += (
            "\n"
            "// Only allow neutralino LSPs.\n"
            "if (not has_neutralino_LSP(spectrum)) invalid_point().raise("
            "\"Neutralino is not LSP.\");\n"
        )

    towrite += "}\n"
    
    return towrite


def write_spheno_higgsbounds_interface(model_name, gambit_pdgs, 
                                       neutral_higgses, charged_higgses,
                                       spheno_decays, partlist):
    """
    Writes the HiggsBounds (via SPheno) interface for 
    SpecBit/src/SpecBit_<NewModel>.cpp
    """

    # Add a helper function to get the invisible decays of Higgses
    towrite = get_higgs_invisibles(neutral_higgses, spheno_decays, partlist,
                                   gambit_pdgs, charged_higgses, model_name)
            

    towrite += (
            "\n"
            "\n"
            "/// Put together the Higgs couplings for the {0}, from SPheno\n"
            "void {0}_higgs_couplings_SPheno(HiggsCouplingsTable &result)\n"
            "{{\n"
            "namespace myPipe = Pipes::{0}_higgs_couplings_SPheno;\n"
            "\n"
            "// Retrieve spectrum contents\n"
            "const Spectrum& spec = *myPipe::Dep::{0}_spectrum;\n"
            "const SubSpectrum& he = spec.get_HE();\n"
            "const SMInputs &sminputs = spec.get_SMInputs();\n"
            "\n"
            "const DecayTable* tbl = &(*myPipe::Dep::decay_rates);\n"
            "\n"
            "// Set up the input structure for SPheno\n"
            "Finputs inputs;\n"
            "inputs.sminputs = sminputs;\n"
            "inputs.param = myPipe::Param;\n"
            "inputs.options = myPipe::runOptions;\n"
            "\n"
            "// Set up neutral Higgses\n"
            "static const std::vector<str> sHneut = initVector<str>("
    ).format(model_name)

    # Get the names of all neutral Higgses
    entry = []
    for higgs in neutral_higgses:
        entry.append("\""+pdg_to_particle(higgs, gambit_pdgs)+"\"")

    # Sort the higgses in numerical order - with the neutral ones first
    entry = sorted(entry, key=str.swapcase)

    towrite += ", ".join(entry) + ");\n"
    towrite += (
            "result.set_n_neutral_higgs({0});\n"
            "\n"
            "// Set the CP of the Higgs states. Note that this would\n"
            "// need to be more sophisticated to deal with complex models.\n"
    ).format(len(entry))

    # Assign the CP of each (neutral) Higgs...
    for i in range(len(entry)):
        if entry[i].strip("\"").startswith('h'):
            towrite += (
                "result.CP[{0}] = 1.;  // {1}\n"
            ).format(i, entry[i])
        elif entry[i].strip("\"").startswith('A'):
            towrite += (
                "result.CP[{0}] = -1.; // {1}\n"
            ).format(i, entry[i])
        else:
            raise GumError(("Neutral Higgs with name {} "
                            "found -- gum expects neutral Higgses "
                            "to be named h0_[n] or A0[_n]."
                            ).format(entry[i]))

    # Same deal with the charged Higgses -- if we have any
    if charged_higgses:        
        towrite += (
                "\n"
                "// Set up charged Higgses\n"
                "static const std::vector<str> sHchar = initVector<str>("
        )

        entry = []
        for higgs in charged_higgses:
            entry.append("\""+pdg_to_particle(abs(higgs), gambit_pdgs)+"\"")

        # Sort the higgses in numerical order - with the neutral ones first
        entry = sorted(entry, key=str.swapcase)

        towrite += ", ".join(entry) + ");\n"
        towrite += (
                "result.set_n_charged_higgs({0});\n"
                "\n"
        ).format(len(entry))

        # We don't need to add the CP for charged Higgses.

    # Get the most 'SM-like' Higgs, needed for HiggsBounds
    # This uses GAMBIT built in functions, only up to NMSSM-like
    # (as of 4/11/19)
    # If the user wishes to include more Higgses, they will need to amend
    # the GAMBIT function SMlike_higgs_PDG_code found in
    # Elements/src/smlike_higgs.cpp

    # Get number of CP even and odd higgses
    nEvenH = len ([pdg_to_particle(x, gambit_pdgs) for x in neutral_higgses if 
                   pdg_to_particle(x, gambit_pdgs).startswith('h')])
    nOddH = len ([pdg_to_particle(x, gambit_pdgs) for x in neutral_higgses if 
                  pdg_to_particle(x, gambit_pdgs).startswith('A')])

    # SM-like
    if nEvenH == 1:
        towrite += (
                "// Just the SM Higgs here. First (only) index = PDG 25.\n"
                "int higgs = 0;\n"
        )

    # MSSM-like
    elif nEvenH == 2:
        towrite += (
                "// Work out which SM values correspond to which Higgs\n"
                "int higgs = (SMlike_higgs_PDG_code(he) == 25 ? 0 : 1);\n"
                "int other_higgs = (higgs == 0 ? 1 : 0);\n"
                "\n"
        )

    # NMSSM-like
    elif nEvenH == 3:
        towrite += (
                "\n"
                "// Work out which SM values correspond to which Higgs\n"
                "int SMlike_higgs = SMlike_higgs_PDG_code(he);\n"
                "\n"
                "int higgs;\n"
                "int other_higgs;\n"
                "int yet_another_higgs;\n"
                "if      (SMlike_higgs == 25) { higgs = 0; other_higgs = 1; "
                "yet_another_higgs = 2; }\n"
                "else if (SMlike_higgs == 35) { higgs = 1; other_higgs = 0; "
                "yet_another_higgs = 2; }\n"
                "else if (SMlike_higgs == 45) { higgs = 2; other_higgs = 0; "
                "yet_another_higgs = 1; }\n"
                "\n"
        )

    # nEvenH > 3 
    else:
        raise GumError(("GAMBIT (and by induction, GUM) does not currently "
                        "support more than 3 CP even Higgses; your model has "
                        "{}."
                        ).format(nEvenH))

    # TODO check can just put h0_1 here
    towrite += (
            "\n"
            "// Set the Higgs sector decays from the DecayTable\n"
            "result.set_neutral_decays(higgs, sHneut[higgs], tbl->at(\"h0_1\"));\n"
    )
    if nEvenH > 1:
        towrite += (
                "result.set_neutral_decays(other_higgs, sHneut[other_higgs], "
                "tbl->at(\"h0_2\"));\n"
        )
    if nEvenH > 2:
        towrite += (
                "result.set_neutral_decays(yet_another_higgs, "
                "sHneut[yet_another_higgs], tbl->at(\"h0_3\"));\n"
        )
    if nOddH > 0:
        if nOddH == 1:
            towrite += (
                    "result.set_neutral_decays({0}, sHneut[{0}], tbl->at(\"A0\"));\n"
            ).format(nEvenH)
        else:
            towrite += (
                    "result.set_neutral_decays({0}, sHneut[{0}], tbl->at(\"A0_1\"));\n"
            ).format(nEvenH)
    if nOddH > 1:
        towrite += (
                "result.set_neutral_decays({0}, sHneut[{0}], tbl->at(\"A0_2\"));\n"
        ).format(nEvenH+1)
    # Not yet supported
    if nOddH > 2:
        raise GumError(("GAMBIT (and by induction, GUM) does not currently support "
                        "more than 2 CP odd Higgses; your model has {0}."
                        ).format(nOddH))

    towrite += "\n//Charged Higgses\n"

    # Charged higgses
    for i in range(len(charged_higgses)):
        towrite += (
            "result.set_charged_decays({0}, \"{1}\", tbl->at(\"{1}\"));\n"
        ).format(i, pdg_to_particle(abs(charged_higgses[i]), gambit_pdgs))

    # Add the top and wrap it up
    towrite += (
            "\n"
            "// Add t decays since t can decay to light Higgses\n"
            "result.set_t_decays(tbl->at(\"t\"));\n"
            "\n"
            "// Fill HiggsCouplingsTable object from SPheno backend\n"
            "// This fills the effective couplings (C_XX2)\n"
            "myPipe::BEreq::SARAHSPheno_{0}_HiggsCouplingsTable(spec, result, inputs);\n"
            "\n"
            "// The SPheno frontend provides the invisible width for each Higgs, however this requires\n"
            "// loads of additional function calls. Just use the helper function instead.\n"
            "result.invisibles = get_invisibles_{0}(he);\n"
            "}}\n\n"
    ).format(model_name)

    return towrite
