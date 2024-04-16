#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Master file containing all routines for modifying Backend interfaces.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019
#
#  \author Pat Scott
#          (pat.scott@uq.edu.au)
#  \date 2018 Dec, 2019 Jan
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2019 July, August
#
#  **************************************


import os
import re

from .setup import *
from .files import *
from .parse import *
from .cmake_variables import *

def check_backends(outputs):
    """
    Diagonostics to check all backends exist in the GAMBIT repository.
    """

    if not isinstance(outputs, Outputs):
        raise GumError("\nRequested output not passed as class Outputs.\n")

    print("Checking for backends before we get going...")

    # CalcHEP
    if outputs.ch:

        if os.path.exists("./../Backends/installed/calchep/3.6.27/models/"):
            print("Found CalcHEP.")
        else:
            raise GumError(("\n\nNo CalcHEP installation found. Please go to into"
                            " the GAMBIT build directory and do"
                            ":\n   make calchep"))

    print("All backends found -- connecting to Mathematica!\n")


def write_backend_patch(output_dir, pristine_dir, patched_dir, backend, version,
                        fullpath = "", fullfile = ""):
    """
    Writes a backend patch (i.e. just a diff) from a pristine 
    and a modified version of a backend.
    """

    import subprocess

    if fullpath:
        full_output_dir = output_dir + "/" + fullpath
    else:
        full_output_dir = output_dir+"/Backends/patches/"+backend+"/"+version

    mkdir_if_absent(full_output_dir)

    if fullfile:
        outfile = full_output_dir+"/"+fullfile+".dif"
    else:
        outfile = full_output_dir+"/patch_"+backend+"_"+version+".dif"

    pristine_parts = os.path.split(pristine_dir)
    cwd = os.getcwd()
    os.chdir(pristine_parts[0])
    command = "diff -rupN "+pristine_parts[1]+" "+patched_dir+" > "+outfile
    subprocess.call(command, shell=True)
    os.chdir(cwd)


def add_to_default_bossed_version(backend, version, reset_dict):

    import re

    filename = "default_bossed_versions.hpp"
    module = "Backends"

    # The contents to add
    contents = "#define  Default_" + backend+" " + re.sub(r"\.", "_", version)+"\n"

    string_to_find = "// Defaults added by GUM (do not remove this comment)."

    present, linenum = find_string(filename, module, string_to_find)
    if not present: 
      linenum = -1

    amend_file(filename, module, contents, linenum, reset_dict)

def add_to_backend_locations(backend_name, backend_location, version_number, 
                             reset_dict):
    """
    Adds an entry to backend_locations.yaml for a new backend.
    """

    # Check to see if backend_locations.yaml exists; if not then we'll use
    # backend_locations.yaml.default (as long as it hasn't been removed)

    if not os.path.isfile("./../config/backend_locations.yaml.default"):
        raise GumError(("backend_locations.yaml.default is missing. What have "
                        "you done to GAMBIT!?"))

    target = "backend_locations.yaml"

    if not os.path.isfile("./../config/"+target):
        target = "backend_locations.yaml.default"

    # Add the new backend before the examples stuff.
    linenum = 0
    with open("./../config/"+target) as f:
      for num, line in enumerate(f, 1):
          if "Example" in line:
              linenum = num
              break

    contents = ("# Added by GUM\n"
                "{0}:\n"
                "  {1:13}./Backends/installed/{2}"
                "\n"
                "\n"
                ).format(backend_name, version_number+":", backend_location)

    # Write the changes
    amend_file(target, "config", contents, linenum-1, reset_dict)


def add_to_backends_cmake(contents, reset_dict, linenum=0, string_to_find=""):
    """
    Adds an entry to backends.cmake, either with a line number
    or with a string to find, then write afterwards.
    """

    if ((linenum == 0) and (string_to_find == "")):
        raise GumError(("\n\tYou need to pass either a line number, or a "
                        "string for me to find, if you want to amend "
                        "backends.cmake."))

    # If the user specifies a line number
    if (linenum != 0):
        amend_file("backends.cmake", "cmake", contents, linenum-1, reset_dict)

    # If the user specifies a string to match, then patch before
    else:
        present, linenum = find_string("backends.cmake", "cmake", 
                                       string_to_find)
        if present: amend_file("backends.cmake", "cmake", contents, 
                               linenum-1, reset_dict)

def check_backend_rebuild(be_name, be_ver, be_install_dir, gum_patched_dir, rebuild_backends, file_endings=(), build_dir='../build'):
    """
    Checks if a backend needs rebuilding by comparing some patched files.
    """

    if not compare_patched_files(be_install_dir, gum_patched_dir, file_endings):
      rebuild_backends.append(be_name)
      force_backend_rebuild(be_name, be_ver, to_touch='mkdir', build_dir=build_dir)

def force_backend_rebuild(be_name, be_ver, to_touch="mkdir", build_dir="../build"):
    """
    Forces the rebuild of a backend by touching the stamp files
    at the step given by to_touch (defaults to download)
    """

    touchable = ['build','install','patch','verify','configure','download','mkdir','update']

    if to_touch not in touchable:
        raise GumError(("\n\tThe stamp target does not exist,"
                        "it should be one of the followinig: "
                        "build, configure, download, install, "
                        "mkdir, patch, update or verify"))

    be = be_name + '_' + be_ver
    stamp_dir = os.path.join(build_dir, be + '-prefix/src', be + '-stamp')
    stamp_file = os.path.join(stamp_dir, be + '-' + to_touch)

    # If stamp file does not exist, no need to do anyting, it will rebuild on its own
    if os.path.isdir(stamp_dir) and os.path.exists(stamp_file) :
        os.utime(stamp_file, None)


def get_boss_backend_name_and_version(configfile):
    """
    Gets the name and version of a backend from its BOSS config file
    """

    with open(configfile, 'r') as config:
        for line in config:
            if len(line.split("=")) > 1 and "gambit_backend_name" in line.split("=")[0]:
                be_name = line.split('=')[1].strip().strip("'").strip('"')
            if len(line.split("=")) > 1 and "gambit_backend_version" in line.split("=")[0]:
                be_ver = line.split('=')[1].strip().strip("'").strip('"')

    return be_name, be_ver

def call_boss_reset(gambit_build_dir, boss_path, reset_file):
    """
    Calls BOSS in reset mode
    """

    import subprocess

    print("BOSS has been run on main GAMBIT tree, resetting BOSS files...")

    cwd = os.getcwd()
    os.chdir(gambit_build_dir)
    command = "python " + boss_path + "/boss.py -r " + reset_file
    subprocess.call(command, shell=True)
    os.chdir(cwd)

    print("Finished running BOSS in reset mode")
