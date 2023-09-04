#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Contains all routines for Vevacious output from SARAH.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019, 2020
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2020
#
#  **************************************

import shutil
import os

from .setup import *
from .files import *

def copy_vevacious_files(model_name, vevdir, reset_dict):
    """
    Moves vevacious files from the SARAH output to the backend folder.
    """

    gb_target = "./../Backends/patches/vevacious/1.0/VevaciousPlusPlus/ModelFiles/" + model_name
    mkdir_if_absent(gb_target, reset_dict)

    file = [f for f in os.listdir(vevdir) if f.endswith(".vin")]
    if len(file) > 1:
        raise GumError(("Too many .vin files in vevacious output."))
    if len(file) == 0:
        raise GumError(("No .vin files in vevacious output."))

    # Move files to the Vevacious *patch* directory
    shutil.copyfile(vevdir + "/" + file[0], gb_target + "/" + model_name + ".vin")
    shutil.copyfile(vevdir + "/ScaleAndBlock.xml", gb_target + "/ScaleAndBlock.xml")

    # Add files to reset dictionary
    reset_dict["new_files"]["files"].append(gb_target + "/" + model_name + ".vin")
    reset_dict["new_files"]["files"].append(gb_target + "/ScaleAndBlock.xml")

def write_vevacious_src(model_name, vevdir, spectrum, params_by_block):
    """
    Writes source code for a new vevacious model.
    To go in SpecBit/src/SpecBit_VS.cpp.
    """

    towrite = (
        "\n"
        "\n"
        "/******************************/\n"
        "/* {0:^26} */\n"
        "/******************************/\n"
        "\n"
        "/// Tell GAMBIT which files to work with for the {0} model.\n"
        "void vevacious_file_location_{0}(map_str_str &result)\n"
        "{{\n"
        "namespace myPipe = Pipes::vevacious_file_location_{0};\n"
        "const Options& runOptions = *myPipe::runOptions;\n"
        "\n"
        "int rank;\n"
        "// Get mpi rank\n"
        "#ifdef WITH_MPI\n"
        "    MPI_Comm_rank(MPI_COMM_WORLD, &rank);\n"
        "#else\n"
        "    rank = 0;\n"
        "#endif\n"
        "\n"
        "// Creating string with rank number\n"
        "std::string rankstring = std::to_string(rank);\n"
        "\n"
        "// Get the path to the library and results dir\n"
        "std::string vevaciouslibpath = Backends::backendInfo().path_dir("
        "\"vevacious\", \"1.0\");\n"
        "std::string vevaciouspath = vevaciouslibpath + \"/../\";\n"
        "std::string vevaciousresultspath = vevaciouspath + \"/results\";\n"
        "\n"
        "// Getting the run folder for saving initialization files\n"
        "std::string inputspath = runOptions.getValueOrDef<std::string>("
        "vevaciousresultspath, \"where_to_save_input\");\n"
        "result[\"inputspath\"] = inputspath;\n"
        "std::string modelfilesPath = inputspath + \"/ModelFiles/mpirank_\"+ "
        "rankstring + \"/\";\n"
        "\n"
        "result[\"ScaleAndBlockFileSource\"] = vevaciouspath + "
        "\"ModelFiles/{0}/ScaleAndBlock.xml\";\n"
        "result[\"ModelFileSource\"] = vevaciouspath + "
        "\"ModelFiles/{0}/{0}.vin\";\n"
        "result[\"ScaleAndBlockFile\"] = modelfilesPath + "
        "\"ScaleAndBlockFile.xml\";\n"
        "result[\"ModelFile\"] = modelfilesPath + \"ModelFile.vin\";\n"
        "}}\n"
        "\n"
        "// This function gives back the result for absolute stability, either"
        " \"Stable\" or \"Metastable\".\n"
        "void prepare_pass_{0}_spectrum_to_vevacious("
        "SpecBit::SpectrumEntriesForVevacious &result)\n"
        "{{\n"
        "namespace myPipe = Pipes::prepare_pass_{0}_spectrum_to_vevacious;\n"
        "\n"
        "//static std::string inputspath =  *myPipe::Dep::make_"
        "vevaciousPlusPlus_inputs;\n"
        "static std::string inputspath =  *myPipe::Dep::init_vevacious;\n"
        "\n"
        "// Getting mpi rank\n"
        "int rank;\n"
        "#ifdef WITH_MPI\n"
        "            MPI_Comm_rank(MPI_COMM_WORLD, &rank);\n"
        "#else\n"
        "            rank = 0;\n"
        "#endif\n"
        "\n"
        "std::string rankstring = std::to_string(rank);\n"
        "\n"
        "std::string inputFilename = inputspath + \"/InitializationFiles/"
        "VevaciousPlusPlusObjectInitialization_mpirank_\"+ rankstring "
        "+\".xml\";\n"
        "result.set_inputFilename(inputFilename);\n"
        "result.set_inputPath(inputspath);\n"
        "\n"
        "// Get the spectrum object\n"
        "const Spectrum& fullspectrum = *myPipe::Dep::{2};\n"
        "const SubSpectrum& spectrumHE = fullspectrum.get_HE();\n"
        "\n"
        "// Get the SLHAea::Coll object from the spectrum.\n"
        "SLHAea::Coll slhaea = spectrumHE.getSLHAea(2);\n"
        "\n"
        "double scale = spectrumHE.GetScale();\n"
        "result.set_scale(scale);\n"
        "\n"
    ).format(model_name, vevdir, spectrum)

    # Now we go through each SLHA BLOCK that we have in the model, and use
    # the vevacious ReadLhaBlock routine from the SLHAea object, to pass the
    # potential parameters to vevacious.
    towrite += (
        "// Here we start passing the parameters form the SLHAea::Coll object."
        "\n"
    )

    # Dict of blocks - add the LHA reading routines to each
    for block, contents in iteritems(params_by_block):

        towrite += write_readlhablock(block, contents)

    towrite += "}\n"

    return dumb_indent(4, indent(towrite))

def write_vevacious_rollcall(model_name, spectrum, reset_dict):
    """
    Writes rollcall headers for vevacious.
    """

    # vevacious_file_location
    add_capability(module="SpecBit",filename="SpecBit_VS_rollcall.hpp", 
                   capability="vevacious_file_location",
                   function="vevacious_file_location_"+model_name,
                   reset_dict=reset_dict, returntype="map_str_str",
                   allowed_models=model_name)

    # pass_spectrum_to_vevacious
    add_capability(module="SpecBit",filename="SpecBit_VS_rollcall.hpp", 
                   capability="pass_spectrum_to_vevacious",
                   function="prepare_pass_"+model_name+"_spectrum_to_vevacious",
                   reset_dict=reset_dict,
                   returntype="SpecBit::SpectrumEntriesForVevacious",
                   dependencies=[[spectrum, "Spectrum"],
                                 ["init_vevacious", "std::string"]],
                   allowed_models=model_name)

def write_readlhablock(block, contents):
    """
    Writes the ReadLhaBlock routine for a given block.
    """
    
    # Size of padding. Let's be aesthetically pleasing here.
    pad = 38 + len(block)
    entries = []

    towrite = "  std::vector<std::pair<int,double>> {0} = {{ ".format(block)

    # Don't need MINPAR or EXTPAR, or any of the SM mixing matrices. 
    # Vevacious gets mixing matrices from diagonlising masses.
    if block in ["MINPAR", "EXTPAR", 
                 "UULMIX", "UURMIX", "UDLMIX", "UDRMIX", "UELMIX", "UERMIX"]:
        return ""
    # And input blocks
    elif block.endswith("IN"):
        return ""

    # Matrix case
    if "matrix" in contents:

        size = int( contents["matrix"].split('x')[0] )

        # Now do each element of the matrix
        for i in range(size):
            for j in range(size):
                entry = (
                    "{{ {0}{1}, SLHAea::to<double>(slhaea.at(\"{2}\")"
                    ".at({0},{1}).at(2))}}"
                ).format(i+1, j+1, block)
                entries.append(entry)

        # Wrap it up.
        towrite += ",\n{:>{width}}".format("",width=pad).join(entries) +"\n};\n"
        towrite += (
                "result.add_entry(\"{0}\", {0}, 2);\n\n"
                #"vevaciousPlusPlus.ReadLhaBlock(\"{0}\", scale, {0}, 2);\n\n"
        ).format(block)
    
    elif "mixingmatrix" in contents:

        # S.B. don't need mixing matrices for vevacious
        return ""
    
        size = int( contents["mixingmatrix"].split('x')[0] )

        # Now do each element of the matrix
        for i in range(size):
            for j in range(size):
                entry = (
                    "{{ {0}{1}, SLHAea::to<double>(slhaea.at(\"{2}\")"
                    ".at({0},{1}).at(2))}}"
                ).format(i+1, j+1, block)
                entries.append(entry)

        # Wrap it up.
        towrite += ",\n{:>{width}}".format("",width=pad).join(entries) +"\n};\n"
        towrite += (
                "result.add_entry(\"{0}\", {0}, 2);\n\n"
                #"vevaciousPlusPlus.ReadLhaBlock(\"{0}\", scale, {0}, 2);\n\n"
        ).format(block)


    # Otherwise, piecewise
    else:

        for index, name in iteritems(contents):
            entry = (
                    "{{ {0}, SLHAea::to<double>(slhaea.at(\"{1}\")"
                    ".at({0}).at(1))}}"
            ).format(index, block)
            # ).format(index, name)
            entries.append(entry)      

        # Wrap it up.
        towrite += ",\n{:>{width}}".format("",width=pad).join(entries) +"\n};\n"
        towrite += (
                "result.add_entry(\"{0}\", {0}, 1);\n\n"
                #"vevaciousPlusPlus.ReadLhaBlock(\"{0}\", scale, {0}, 1);\n\n"
        ).format(block)
    
    return towrite

