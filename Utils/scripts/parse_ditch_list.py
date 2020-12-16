#!/usr/bin/env python
#
#  GAMBIT: Global and Modular BSM Inference Tool
#  *********************************************
#  \file
#
#  Parses the config/ditched.dat and prepares
#  it to be used with the diagnostic system of
#  GAMBIT.
#
#*********************************************
#
#  Authors (add name and date if you modify):
#
#  \author Markus Prim
#          (markus.prim@cern.ch)
#  \date 2020 Dec
#
#*********************************************

import argparse
import yaml


def sanitize(list_to_sanitize, list_to_check_against, replacement):
    """Replace potential substrings with a defined string. And return a set, 
to avoid multiple entries.
    Args:
        list_to_sanitize: The list which will be modified.
        list_to_check_against: A list containing all strings which
            should be replaced by the replacement string.
        replacement: Replacement string for matches.
    """
    return set([x if x not in list_to_check_against else replacement 
        for x in list_to_sanitize])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="""Post-processes the 
ditched.dat produced by the CMake system to disentangle components, which
are either ditched explicitly or disabled due to missing requirements.""")
    parser.add_argument(
        "--file", 
        default="config/ditched.dat",
        help="""Path to the file which should be parsed. It will create a 
new yaml file in the same directory, e.g. config/ditched.yaml.""")
    parser.add_argument(
        "--ditch-string", 
        default="",
        help="""Based on the -Ditch string passed to CMake the components 
disabled because of missing requirements and ditched because of explicit
request will be distinguished. This expects the ${itch_with_commas} format.
""")

    args = parser.parse_args()

    # Translate the ${itch_with_commas} string into a list.
    requested_ditches = args.ditch_string.split(",")

    # Sanitize the ditch list to avoid over-matching, especially in the 
    # Mathematica case. These allowed strings to ditch pybind/mathematica 
    # are copied from the CMakeLists.txt.
    pybind_ditches = ["pybind", "pybind11", "Pybind", "Pybind11"]
    mathematica_ditches = ["M", "Ma", "Mat", "Math", "Mathe", "Mathem",
        "Mathema", "Mathemat", "Mathemati", "Mathematic", "Mathematica",
        "m", "ma", "mat", "math", "mathe", "mathem", "mathema", "mathemat",
        "mathemati", "mathematic", "mathematica"]

    requested_ditches = sanitize(requested_ditches, pybind_ditches, "pybind11")
    requested_ditches = sanitize(requested_ditches, mathematica_ditches, "mathematica")
    
    # Read in all disabled components from the file created by CMake.
    with open(args.file, "r") as f:
        disabled_components = set(filter(None, f.read().replace("\n", "").split(",")))

    # Go through all requested ditches and match them against the disabled components.
    ditched_components = []
    for requested_ditch in requested_ditches:
        # To simplify the comparison we force lower cases and match that way.
        ditched_components += [component for component in disabled_components 
        if requested_ditch.lower() in component.lower()]
    ditched_components = set(ditched_components)
    disabled_components = disabled_components - ditched_components

    with open(args.file.replace(".dat", ".yaml"), "w") as f:
        yaml.dump({
            "ditched": list(ditched_components),
            "disabled": list(disabled_components),
        }, f)
