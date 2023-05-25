#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Master routines for all MadGraph related routines.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019, 2020
#
#  \author Pat Scott
#          (pat.scott@uq.edu.au)
#  \date 2019 Jan
#
#  **************************************

import os
import sys
from distutils.dir_util import copy_tree

from .files import mkdir_if_absent, remove_tree_quietly

script_name = "generate_matrix_elements.mg5"

def make_madgraph_script(mg5_dir, mg5_output_dir, model_name, processes, multiparticles, patchedpythia = True):
    """
    Writes a script to be used when calling MadGraph.
    """

    model_path = mg5_dir + "/models/" + model_name

    if patchedpythia:
        filename = mg5_output_dir + "/" + script_name
    else:
        filename = mg5_output_dir + "/" + "generate_matrix_elements_MG_"+ model_name+".mg5"

    print("Generating {}.".format(filename))

    # First convert the model to python3 if needed
    if (sys.version_info[0] < 3 or not patchedpythia):
        towrite = ""
    else:
        towrite = "convert model " + model_path + "\n"

    # Then, import the model
    towrite += "import model " + model_name + "\n"

    # Import any multiparticles
    if multiparticles:
        for multi in multiparticles:
            for k, v in multi.items():
               towrite += ("define {0} = {1}\n".format(k, ' '.join(v)))

    # Tell MadGraph to generate the first process
    towrite += "generate " + processes[0] + "\n"
    # If there are more processes, tell MadGraph to add them too
    if len(processes) > 1:
        for x in processes[1:]:
            towrite += "add process " + x + "\n"

    if patchedpythia:
        # Write eps files of all the Feynman diagrams of the generated matrix elements
        towrite += "display diagrams diagrams\n"

        # Generate matrix element code in Pythia 8 format
        towrite += "output pythia8 Pythia_patched\n"

    # Put it on wax.
    open(filename, 'w').write(towrite)

    print("File {} successfully created.".format(filename))


def call_madgraph(mg5_dir, mg5_output_dir, mi):
    """
    Calls MadGraph.
    """

    # Clear the diagram dir and remake it
    remove_tree_quietly(mg5_output_dir + "/diagrams")
    os.makedirs(mg5_output_dir + "/diagrams")

    # Go to the MadGraph output directory
    cwd = os.getcwd()
    os.chdir(mg5_output_dir)

    # Launch interactive interface to MadGraph
    print("Launching MadGraph...")
    launch = mi.MasterCmd(mgme_dir = mg5_dir)

    # Execute the script
    launch.exec_cmd("import command " + script_name)

    # Return to the previous working directory
    os.chdir(cwd)

    print("Pythia output created from MadGraph.")


def copy_madgraph_files(mg5_dir, model_name):
    """
    Copies all MadGraph files into the contrib/MadGraph directory.
    """

    model_name.strip('/')

    target = './contrib/MadGraph/models/' + model_name

    copy_tree(mg5_dir, target)

    print("MadGraph files moved to correct directory.")

def write_MadGraph_cmake_entry(model, output_dir):
    """
    Writes MadGraph entry for cmake/backends.cmake
    """

    # The string that will commence the block to be added by GUM
    # This will be placed directly below the MadGraph entry
    # TODO: For now, I am leaving the name of the output folder as MyMadGraphTesting. Perhaps this could be an entry from the gum_file
    to_write = "# Custom model target generated with GUM.\n"\
               "set(name \"MadGraph\")\n"\
               "set(ver \"3.4.2\")\n"\
               "set(dir \"${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}\")\n"\
               "set(gum_dir \"${PROJECT_SOURCE_DIR}/gum/\")\n"\
               "add_custom_target(MadGraph_"+model.lower()+"\n"\
               "    COMMAND ${CMAKE_COMMAND} -E copy_directory ${gum_dir}/contrib/MadGraph/models/"+model+" ${dir}/models/"+model+"\n"\
               "    COMMAND ${CMAKE_COMMAND} -E copy ${gum_dir}/Outputs/"+model+"/MadGraph5_aMC/generate_matrix_elements_MG_"+model+".mg5 ${dir}/\n"\
               "    COMMAND echo \"output ${dir}/MyMadGraphTesting\" >> ${dir}/generate_matrix_elements_MG_"+model+".mg5"\
               "    COMMAND ${dir}/bin/mg5_aMC ${dir}/generate_matrix_elements_MG_"+model+".mg5\n"\
               "    DEPENDS ${name}_${ver})\n\n\n"

    return to_write
