#!/usr/bin/env python
#
# GAMBIT: Global and Modular BSM Inference Tool
# *********************************************
# \file
#
#  Tools for harvester scripts.
#
# *********************************************
#
#  Authors (add name and date if you modify):
#
#  \author Ben Farmer
#          (b.farmer@imperial.ac.uk)
#    \date 2013 Sep
#          2014 Jan
#          2015 Jul
#          2018 Oct
#
#  \author Pat Scott
#          (patscott@physics.mcgill.ca)
#    \date 2013 Oct, Nov
#    \date 2014 Jan, Nov
#    \date 2015 Feb
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#    \date 2018 Oct
#    \date 2021 Mar
#
# *********************************************
import os
import re
import datetime
import sys
import getopt
import itertools
import shutil
import ctypes
import io
from itertools import zip_longest

default_bossed_versions = "./Backends/include/gambit/Backends/default_bossed_versions.hpp"
equiv_config = "./config/resolution_type_equivalency_classes.yaml"


def get_default_boss_namespaces():
    """Load the default_bossed_versions.hpp header, and work out the namespace aliases."""
    result = dict()
    # Load the default_bossed_version header.
    with (io.open(default_bossed_versions, encoding='utf-8')) as f:
        for newline in readlines_nocomments(f):
            newline = newline.strip()
            if not newline.startswith("#define"):
                continue
            line = neatsplit(r'\s', newline)
            if not line[1].startswith("Default_"):
                continue
            key = line[1][len("Default_"):]
            result[key] = line[2]
    return result


def get_type_equivalencies(nses):
    """Load type equivalencies yaml file and return a dictionary containing all the equivalency classes. Just use regex rather than pyYAML, as the latter chokes on :: in scalar entries >:-/"""
    from collections import defaultdict
    result = defaultdict(list)
    # Load the equivalencies yaml file
    with io.open(equiv_config, encoding='utf-8') as f:
        for newline in readlines_nocomments(f):
            newline = newline.strip()
            if newline == "" or newline.startswith("#"):
                continue
            newline = re.sub(r"^\[\s*|\s*\]", "", newline)
            equivalency_class = list()
            for member in re.findall(r"[^,]*?\(.*?\)[^,]*?\(.*?\).*?,|[^,]*?<[^>]*?<.*?>[^<]*?>.*?,|[^,]*?<.*?>.*?,|[^,]*?\(.*?\).*?,|[^>\)]*?,", newline+","):
              member = re.sub("\"","",member[:-1].strip())
              # Convert the leading BOSSed namespace for the default version to the explicit namespace of the actual version
              for key in nses:
                ns_default = key+"_default"+"::"
                ns_true = key+"_"+nses[key]+"::"
                if member.startswith(ns_default): member = ns_true+member[len(ns_default):]
                member = re.sub(r"\s"+ns_default," "+ns_true,member)

              # If the type is an alias of a native int then add int to the equivalency class
              if re.match(r"int[0-9]+_t", member):
                if ( ctypes.sizeof(ctypes.c_int) == 8 and re.search("64", member) ) or ( ctypes.sizeof(ctypes.c_int) == 4 and re.search("32", member) ) or ( ctypes.sizeof(ctypes.c_int) == 2 and re.search("16", member) ) :
                  if 'int' not in equivalency_class:
                    equivalency_class+=['int']
              if member not in equivalency_class:
                equivalency_class += [member]
            for member in equivalency_class: result[member] = equivalency_class

    # Debug output
    # print('Type equivalencies:')
    # print(result)
    return result



def comment_remover(text):
    """Remove C/C++ comments from 'text' (From http://stackoverflow.com/questions/241327/python-snippet-to-remove-c-and-c-comments)"""
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return ""
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text[:])


def readlines_nocomments(f):
    """Replacement for f.readlines(), which removes all C/C++ comments from the text before returning a list of all the lines (as f.readlines() does)"""
    processed_text = comment_remover(f.read())
    return processed_text.splitlines()


def neatsplit(regex, string):
    """No empties from re.split"""
    return [x for x in re.split(regex, string) if x != '']


def excluded(string, st):
    """Check if a string matches the start of any entry in a set"""
    for x in st:
        if string.startswith(x): return True
        if string.lower().startswith(x.lower()): return True
        if string.lower().startswith(x.lower().replace('.','_')): return True
    return False


def sorted_nicely(l):
    """Nice sorting function (from http://stackoverflow.com/a/2669120/1447953)
Sort the given iterable in the way that humans expect."""
    def convert(text):
        return int(text) if text.isdigit() else text

    def alphanum_key(key):
        return [convert(c) for c in re.split('([0-9]+)', key)]
    return sorted(l, key=alphanum_key)


def check_for_declaration(input_snippet, module, all_modules, local_namespace, candidate_type):
    """Parse a string to see if it has a class, struct or typedef declaration"""
    splitline = neatsplit(r'\s|\(|\)|\*|\&|\;', input_snippet)
    candidate_type = re.sub(r"^\s*|\s*$", "", candidate_type)
    candidate_parts = neatsplit('::', re.sub(
        r"^.*\s", "", re.sub(r"<.*>", "", candidate_type)))
    namespace_parts = neatsplit('::', local_namespace)
    right_class = False
    # Work out if we are in the module namespace, and if any sub-namespace matches the candidate type.
    in_module_and_namespace_matches = False
    if local_namespace and namespace_parts[0] == module:
        if candidate_type.startswith(local_namespace):
            in_module_and_namespace_matches = True
        if len(namespace_parts) == 1:
            in_module_and_namespace_matches = True
        else:
            addon = 0
            if candidate_parts[0] == module:
                addon = 1
            if candidate_parts[0] == "Gambit":
                addon = 2
            if len(candidate_parts) == len(namespace_parts) + addon:
                in_module_and_namespace_matches = True
    # Continue only if the input snippet is long enough to contain a declaration and there are no namespace issues
    if len(splitline) > 1 and (not local_namespace or namespace_parts[0] not in all_modules or in_module_and_namespace_matches):
        # Look for class/struct declarations
        if splitline[0] in ["class", "struct"]:
            allowed_matches = (splitline[1], splitline[1]+"*")
            if candidate_type in allowed_matches or candidate_parts[0] in allowed_matches:
                right_class = True
            elif len(candidate_parts) > 1 and candidate_parts[-1] in allowed_matches:
                if (candidate_parts[:-1] == namespace_parts[1-len(candidate_parts):]):
                    right_class = True
        # Look for typedefs
        if len(splitline) > 2 and splitline[0] == "typedef":
            if (candidate_type in splitline[2:]):
                right_class = True
            elif len(candidate_parts) > 1 and candidate_parts[-1] in splitline[2:]:
                if (candidate_parts[:-1] == namespace_parts[1-len(candidate_parts):]):
                    right_class = True
        # The class declared at this line matches the candidate class
        if right_class and local_namespace and local_namespace != "Gambit":
            main_class = candidate_parts[-1]
            template_args = re.findall(r"<.*>\*?", candidate_type)
            if template_args == []:
                template_args = ""
            else:
                template_args = template_args[0]
                main_class = re.sub(r"\*$", "", candidate_parts[-1])
            qualifiers = re.findall(
                r"^.*\s", re.sub(r"<.*>\*?", "", candidate_type))
            qualifiers = "" if qualifiers == [] else qualifiers[0]
            candidate_type = qualifiers + local_namespace + "::" + main_class + template_args
    return (right_class, candidate_type)


def check_for_namespace(input_snippet, local_namespace):
    """Parse a string to see if it has a namespace declaration"""
# TODO: This is really limited. E.g. a forward declaration in a small, temporary namespace will get appended to local_namespace,
# and this function has no way to notice when that namespace ends, so all subsequent types in some different namespace will be
# screwed up.
    # Exit if the line just defines a namespace alias
    if "=" in input_snippet:
        return local_namespace
    splitline = neatsplit(r'\s', input_snippet)
    if len(splitline) > 1:
        # If the line starts by declaring a namespace, return it appended to the current namespace
        if splitline[0] == "namespace":
            if local_namespace.endswith(splitline[1]):
                return local_namespace
            elif local_namespace and local_namespace != "Gambit" and splitline[1] not in local_namespace:
                return local_namespace+"::"+splitline[1]
            else:
                return splitline[1]
    return local_namespace


def addifheader(line, headerset, exclude_set, verbose=False):
    """Harvest header filename from an include statement"""
    splitline = line.split()
    if len(splitline) > 1 and splitline[0] == "#include":
        # dig the file name out of the enclosing <> or ""
        split2 = neatsplit(r'"|<|>', splitline[1])
        split3 = neatsplit(r'/', split2[0])
        if split2[0] not in exclude_set and split3[-1] not in exclude_set:
            headerset.add(split2[0])
            if verbose:
                print("  Added header '{0}' to set".format(split2[0]))


def update_module(line, module):
    """Harvest module names from rollcall headers"""
    splitline = neatsplit(r'\(|\)|,|\s', line)
    if len(splitline) > 2:
        if splitline[0] == "#define" and splitline[1] == "MODULE":
            # This line defines a module, return its name instead of bothering to look for a START_FUNCTION
            return splitline[2]
    return module


def first_simple_type_equivalent(candidate_in, equivs, nses, existing):
    """Check for an existing or type equivalent entry. Preferentially return
    1. the existing equivalent entry
    2. the first equivalent entry that does not contain a comma
    3. the original type
    """
    if candidate_in in existing:
        return candidate_in
    candidate = candidate_in
    candidate.strip()
    # Convert the leading BOSSed namespace for the default version to the explicit namespace of the actual version
    for key in nses:
        ns_default = key+"_default"+"::"
        ns_true = key+"_"+nses[key]+"::"
        if candidate.startswith(ns_default):
            candidate = ns_true+candidate[len(ns_default):]
        candidate = re.sub(r"\s"+ns_default, " "+ns_true, candidate)

    # Exists in the equivalency classes

    candidate_prefix = ""
    candidate_suffix = ""

    # Qualifiers up front, e.g const
    if "const" in candidate[:6]:
      candidate_prefix = "const "
      candidate = re.sub("const ","",candidate)

    # Pointer or reference to something that exists in the equivalency classes
    if candidate[-1] == "&" or candidate[-1] == "*":
        candidate_suffix = candidate[-1:]
        candidate = candidate[:-1]

    # Just not there
    if candidate not in equivs:
        return candidate_prefix+candidate+candidate_suffix

    equivalency_class = equivs[candidate]
    common_elements = set.intersection(set(equivalency_class), existing)
    if not common_elements:
        for index in range(len(equivalency_class)):
            equivalent = equivalency_class[index]
            if "," not in equivalent:
                return candidate_prefix+equivalent+candidate_suffix
        print("Error: all equivalent types found have commas in them!  Please typedef one without a comma.")
        print("Types are: ", equivalency_class)
        sys.exit(1)
    if len(common_elements) != 1:
        print("Error: existing types and equivalency class have more than one element in common!")
        sys.exit(1)
    return candidate_prefix+common_elements.pop()+candidate_suffix


def strip_ws(s, qualifiers):
    """Strips all whitespaces from a string, but re-inserts a single regular space after "const" or "struct"."""
    for q in qualifiers:
        s = re.sub(q+r"\s*", q+"__TEMP_SPACE__", s)
        s = re.sub(r"\s*", "", s)
    return re.sub("__TEMP_SPACE__", " ", s)


def addiffunctormacro(line, module, all_modules, typedict, typeheaders, intrinsic_types, exclude_types, equiv_classes, equiv_ns, verbose=False):
    """Harvest type from a START_FUNCTION or QUICK_FUNCTION macro call"""
    command_index = {"START_FUNCTION": 1,
                     "QUICK_FUNCTION": 5,
                     "DEPENDENCY": 2,
                     "MODEL_CONDITIONAL_DEPENDENCY": 2,
                     "INTERPRET_AS_PARENT_DEPENDENCY": 2,
                     "INTERPRET_AS_X_DEPENDENCY": 3,
                     "START_CONDITIONAL_DEPENDENCY": 1,
                     "BE_INI_DEPENDENCY": 2,
                     "BE_INI_CONDITIONAL_DEPENDENCY": 2}

    line = re.sub(";", "", line)
    splitline = neatsplit(r'\(|\)|,|\s', line)

    qualifier_list = ["const", "struct"]
    typeset = typedict["all"]

    if len(splitline) > 1 and splitline[0] in command_index.keys():
        # This line defines a function and one or more of the arguments defines a candidate type
        index = command_index[splitline[0]]
        if splitline[index] in qualifier_list:
            candidate_types = set(
                [splitline[index]+" "+strip_ws(splitline[index+1], qualifier_list)])
        else:
            candidate_types = set([strip_ws(splitline[index], qualifier_list)])
        if splitline[0] == "QUICK_FUNCTION" and len(splitline) > 6:
            # Get the dep types out of a QUICK_FUNCTION command
            splitline = re.findall(
                r"\(.*?\)", re.sub(r"QUICK_FUNCTION\(", "", re.sub(r"\)\)\s*$", ")", line)))
            for dep in splitline[1:]:
                splitdep = neatsplit(r'\(|\)|,', dep)
                candidate_types.add(splitdep[1].strip())
        # Remove excluded types from the set
        candidate_types.difference_update(exclude_types)

        # Iterate over all the candidate types and remove any leading Gambit namespace
        new_candidate_types = []
        for candidate_type in candidate_types:
            new_candidate_types.append(re.sub("^Gambit::", "", candidate_type))

        # Iterate over all the candidate types and check if they are defined.
        for candidate_type in new_candidate_types:
            candidate_type = first_simple_type_equivalent(
                candidate_type, equiv_classes, equiv_ns, typeset)
            # Skip out now if the type is already found.
            if (candidate_type in typeset or
                module+"::"+candidate_type in typeset or
                    "Gambit::"+module+"::"+candidate_type in typeset):
                continue
            # If the type is not an intrinsic, check if it is declared in any of the module type headers
            if (candidate_type not in intrinsic_types):
                if verbose:
                    print("    {0} located, searching for declaration of {1}...".format(
                        line.strip(), candidate_type))
                for header in typeheaders:
                    local_namespace = ""
                    found_declaration = False
                    with io.open(header, encoding='utf-8') as f:
                        for newline in readlines_nocomments(f):
                            splitline = neatsplit(r'\{|\}|:|;', newline)
                            # Determine the local namespace and look for a class or struct matching the candidate type
                            for i in range(5):
                                if len(splitline) > i:
                                    local_namespace = check_for_namespace(
                                        splitline[i], local_namespace)
                                    if not found_declaration:
                                        (found_declaration, candidate_type) = check_for_declaration(
                                            splitline[i], module, all_modules, local_namespace, candidate_type)
                            # The loop above misses some of the typedefs, so we need to re-parse the whole line for these.
                            if not found_declaration:
                                (found_declaration, candidate_type) = check_for_declaration(
                                    newline, module, all_modules, local_namespace, candidate_type)
                            if found_declaration:
                                break
                    # If the type was declared in this header, and this is a module header, save the type into the list of types for this module.
                    if found_declaration and re.sub(".*?/include/gambit/", "", header).startswith(module):
                        if module not in typedict:
                            typedict[module] = set([])
                        typedict[module].add(candidate_type)
                        break
                # If the type was not identified with any module, save it as a non-module type.
                if module not in typedict or candidate_type not in typedict[module]:
                    typedict["non_module"].add(candidate_type)
            else:
                # Type is intrinsic, so must be a non-module type.
                typedict["non_module"].add(candidate_type)
            # Add the type to the list of all types from everywhere.
            typeset.add(candidate_type)


def addifbefunctormacro(line, be_typeset, type_pack_set, equiv_classes, equiv_ns, verbose=False):
    """Harvest type from a BE_VARIABLE, BE_FUNCTION or BE_CONV_FUNCTION macro call"""

    command_index = {"BE_VARIABLE": 2,
                     "BE_FUNCTION": 2,
                     "BE_CONV_FUNCTION": 2,
                     "BACKEND_REQ": 0,
                     "BACKEND_REQ_FROM_GROUP": 0}

    line = re.sub(";", "", line)
    splitline = neatsplit(r'\(|\)|,|\s', line)

    qualifier_list = ["const", "struct"]

    if len(splitline) > 1 and splitline[0] in command_index.keys():
        # This line defines a backend functor and one or more of the arguments defines a candidate type

        if splitline[0].startswith("BACKEND_REQ"):
            args = re.sub(
                r"\s*BACKEND_REQ(_FROM_GROUP)?\s*\(.*?,\s*\(.*?\)\s*,\s*", "", re.sub(r"\s*\)\s*$", "", line))
            args = args.strip()
            if re.search(r"\)\s*\)\s*$", line):
                # This is a backend function requirement
                leading_type = strip_ws(
                    re.sub(r"\s*,\s*\(.*?\)\s*$", "", args), qualifier_list)
                leading_type = first_simple_type_equivalent(
                    leading_type, equiv_classes, equiv_ns, be_typeset)
                functor_template_types = list([leading_type])
                args = re.sub(
                    r".*?,\s*\(\s*", "", re.sub(r"\s*\)\s*$", "", args))
                for arg in re.findall(r"[^,]*?\(.*?\)[^,]*?\(.*?\).*?,|[^,]*?<.*?>.*?,|[^,]*?\(.*?\).*?,|[^>\)]*?,", args+","):
                    arg = arg[:-1].strip()
                    if arg != "":
                        if arg == "etc":
                            arg = "..."
                        arg_list = neatsplit(r'\s', arg)
                        if arg_list[0] in ("class", "struct", "typename"):
                            arg = arg_list[1]
                        arg = first_simple_type_equivalent(
                            strip_ws(arg, qualifier_list), equiv_classes, equiv_ns, be_typeset)
                        functor_template_types.append(arg)
            else:
                # This is a backend variable requirement
                args = first_simple_type_equivalent(
                    strip_ws(args, qualifier_list), equiv_classes, equiv_ns, be_typeset)
                functor_template_types = list([args+"*"])

        else:
            # If function/variable type has qualifier, combine elements in splitline
            cmd_i = command_index[splitline[0]]
            if splitline[cmd_i].strip() in qualifier_list:
                splitline[cmd_i:cmd_i+2] = [" ".join(splitline[cmd_i:cmd_i+2])]

            functor_template_types = list(
                [strip_ws(splitline[command_index[splitline[0]]], qualifier_list)])
            functor_template_types[0] = first_simple_type_equivalent(
                functor_template_types[0], equiv_classes, equiv_ns, be_typeset)
            if splitline[0].endswith("FUNCTION"):
                # Get the argument types out of a BE_FUNCTION or BE_CONV_FUNCTION command
                args = re.sub(
                    r"\s*BE_(CONV_)?FUNCTION\s*\(.*?,.*?,\s*?\(", "", line)
                args = re.sub(r"\([^\(]*?\)\s*\)\s*$", r"\)", args)
                if splitline[0] == "BE_FUNCTION":
                    args = re.sub(r"\)\s*,[^\)]*?,[^\)]*?\)\s*$", "", args)
                else:
                    args = re.sub(r"\)\s*,[^\)]*?\)\s*$", "", args)
                for arg in re.findall(r"[^,]*?\(.*?\)[^,]*?\(.*?\).*?,|[^,]*?<[^>]*?<.*?>[^<]*?>.*?,|[^,]*?<.*?>.*?,|[^,]*?\(.*?\).*?,|[^>\)]*?,", args+","):
                    arg = arg[:-1].strip()
                    if arg != "" and not arg.startswith("\"") and not arg.startswith("("):
                        if arg == "etc":
                            arg = "..."
                        arg_list = neatsplit(r'\s', arg)
                        if arg_list[0] in ("class", "struct", "typename"):
                            arg = arg_list[1]
                        arg = first_simple_type_equivalent(
                            strip_ws(arg, qualifier_list), equiv_classes, equiv_ns, be_typeset)
                        functor_template_types.append(arg)
            else:
                # Convert the type to a pointer if this is a backend variable functor rather than a backend function functor
                functor_template_types[0] += "*"


        # Iterate over all the candidate types and remove any leading Gambit namespace
        candidate_types = set(functor_template_types)
        new_candidate_types = []
        for candidate_type in candidate_types:
            new_candidate_types.append(re.sub("^Gambit::", "", candidate_type))

        # Iterate over all the candidate types and check if they are defined.
        for candidate_type in new_candidate_types:
            candidate_type = first_simple_type_equivalent(
                strip_ws(candidate_type, qualifier_list), equiv_classes, equiv_ns, be_typeset)
            initial_candidate = candidate_type
            # Skip to the end if the type is already found.
            if ("Gambit::"+candidate_type in be_typeset):
                candidate_type = "Gambit::"+candidate_type
            elif (candidate_type not in be_typeset):
                be_typeset.add(candidate_type)
            # Replace the argument types in the functor_template_types with the fully-qualified versions if required.
            functor_template_types = [
                candidate_type if entry == initial_candidate else entry for entry in functor_template_types]

        ptr_args = ",".join(functor_template_types[1:])
        arg_list = ",".join(
            [x for x in functor_template_types[1:] if x != "..."])
        type_pack = functor_template_types[0] + \
            "(*)(" + ptr_args + ")," + functor_template_types[0]
        if arg_list != "":
            type_pack += "," + arg_list
        type_pack_set.add(type_pack)


def get_headers(path, header_set, exclude_set, verbose=False):
    """Harvest the list of rollcall headers to be searched, and the list of type headers to be searched."""
    # Parse the file at 'path' and add any headers that are "include"ed therin to the set 'header_set'
    with open(path) as f:
        #print( "  Parsing header '{0}' for further includes...".format(path) )
        for line in readlines_nocomments(f):
            addifheader(line, header_set, exclude_set, verbose=verbose)


def find_and_harvest_headers(header_set, fullheadlist, exclude_set, dir_exclude_set, verbose=False):
    """Locate 'init_headers' in gambit source tree, then read through them and add any headers that are "include"ed in them to headlist
    Args:
    header_set - set of file names of headers to parse
    fullheadlist - list to which full paths of both init_headers, and any subsequently found headers, should be added.
    exclude_set - set of names of headers to ignore if we find them.
    dir_exclude_set - set of directory names to skip over during the os.walk
    """
    full_header_paths = []
    # Locate the header in the GAMBIT directory structure...
    # (we should technically search all the include paths in the make file; could pass these in to this script)
    # Ignores any headers that cannot be found (assumed to be external libraries, etc.)
    for root, dirs, files in os.walk(".", topdown=True):
        # Delete any directories from the traverse list if they are in the exclude list
        [dirs.remove(d) for d in list(dirs) if d in dir_exclude_set]
        for name in files:
            for header in header_set:
                if os.path.join(root, name).endswith(header):
                    if verbose:
                        print("  Located header '{0}' at path '{1}'".format(
                            name, os.path.join(root, name)))
                    full_header_paths += [os.path.join(root, name)]

    # Add newly found paths to output list
    fullheadlist += full_header_paths

    new_headers = set()
    for path in full_header_paths:
        get_headers(path, new_headers, exclude_set, verbose=verbose)

    # Add headers that we started with to the 'exclude_set' so that we don't search them again.
    new_exclude_set = set()
    new_exclude_set.update(exclude_set)
    new_exclude_set.update(header_set)

    # Delete elements of 'new_exclude_set' from 'new_headers'
    new_headers.difference_update(new_exclude_set)

    # Do this again for all the headers we just found, if we found any
    if len(new_headers) > 0:
        if verbose:
            print("  Harvested the following new headers:")
        for header in new_headers:
            if verbose:
                print("    "+header)
        find_and_harvest_headers(
            new_headers, fullheadlist, new_exclude_set, dir_exclude_set, verbose=verbose)


def retrieve_rollcall_headers(verbose, install_dir, excludes, retrieve_excluded=False):
    """Search the source tree to determine which modules are present, and write a module_rollcall header if the GAMBIT Core exists.

    If the option `retrieve_excluded` is set to true, it will search for excluded modules.
    This feature is used for the diagnostic system.
    """
    rollcall_headers = []
    core_exists = False
    exclude_dirs = ["build", ".git", "runs", "scratch", "contrib", "Backends", ".github", "Logs", "pippi", "Models", "yaml_files", "Printers", "config", "doc", "Utils", "Elements", "cmake"]
    for root, dirs, files in os.walk(install_dir, topdown=True):
        # bit confusing, but avoids descending into excluded directories
        [dirs.remove(d) for d in list(dirs) if d in exclude_dirs]
        if (not core_exists and root == install_dir+"/Core/include/gambit/Core"):
            core_exists = True
        for name in files:
            prefix = re.sub(r"_rollcall\.h.*", "", name)
            if ((name.lower().endswith("_rollcall.hpp") or
                 name.lower().endswith("_rollcall.h") or
                 name.lower().endswith("_rollcall.hh")) and name.lower().find("bit") != -1 and root.endswith(prefix)):
                exclude = False
                for x in excludes:
                    if name.startswith(x):
                        exclude = True
                if not exclude and not retrieve_excluded:
                    if verbose:
                        print("  Located module rollcall header '{0}' at path '{1}'".format(
                            name, os.path.join(root, name)))
                    rel_name = re.sub(
                        ".*?/include/", "", os.path.relpath(os.path.join(root, name), install_dir))
                    rollcall_headers += [rel_name]
                if exclude and retrieve_excluded:
                    if verbose:
                        print("  Located module rollcall header '{0}' at path '{1}'".format(
                            name, os.path.join(root, name)))
                    rel_name = re.sub(
                        ".*?/include/", "", os.path.relpath(os.path.join(root, name), install_dir))
                    rollcall_headers += [rel_name]
    if core_exists and not retrieve_excluded:
        make_module_rollcall(rollcall_headers, verbose)
    return rollcall_headers


def retrieve_module_type_headers(verbose, install_dir, excludes):
    """Search the source tree to determine which modules type headers are present."""
    type_headers = []
    exclude_dirs = ["build", ".git", "runs", "scratch", "contrib", "Backends", ".github", "Logs", "pippi", "Models", "yaml_files", "Printers", "config", "doc", "Utils", "Elements", "cmake"]
    for root, dirs, files in os.walk(install_dir, topdown=True):
        # bit confusing, but avoids descending into excluded directories
        [dirs.remove(d) for d in list(dirs) if d in exclude_dirs]
        for name in files:
            if ((name.lower().endswith("_types.hpp") or
                 name.lower().endswith("_types.h") or
                 name.lower().endswith("_types.hh")) and name.lower().find("bit") != -1):
                exclude = False
                bare_name = re.sub(".*_types\\.[h|hpp|hh]$", "", name)
                for x in excludes:
                    if bare_name.startswith(x):
                        exclude = True
                if (not exclude):
                    if verbose:
                        print("  Located module type header '{0}' at path '{1}'".format(
                            name, os.path.join(root, name)))
                    rel_name = re.sub(
                        ".*?/include/", "", os.path.relpath(os.path.join(root, name), install_dir))
                    type_headers += [rel_name]
    return type_headers


def get_all_files_with_ext(verbose, starting_dir, ext_set, kind):
    """Get all files in a directory tree with one of a given set of extensions"""
    results = []
    for root, dirs, files in os.walk(starting_dir):
        for name in files:
            for ext in ext_set:
                if name.endswith(ext):
                    if verbose:
                        print(
                            "  Located "+kind+" file '{0}' at path '{1}'".format(name, os.path.join(root, name)))
                    results += [os.path.join(root, name)]
    return results


def retrieve_generic_headers(verbose, starting_dir, kind, excludes, exclude_list=[], retrieve_excluded=False):
    """Search a directory for headers that are not excluded.

    If the option `retrieve_excluded` is set to true, it will search for excluded headers.
    This feature is used for the diagnostic system.
    """
    headers = []
    for root, dirs, files in os.walk(starting_dir):
        if root.endswith("shared_includes"):
            continue
        for name in files:
            exclude = False
            if excluded(name,excludes):
                exclude = True
            if kind == "BOSSed type" and not name.startswith("loaded_types"):
                exclude = True

            if name.endswith(".hpp") or name.endswith(".h") or name.endswith(".hh"):
                if not exclude and not retrieve_excluded:
                    if verbose:
                        print(
                            "  Located "+kind+" header '{0}' at path '{1}'".format(name, os.path.join(root, name)))
                    rel_name = re.sub(
                        ".*?/include/", "", os.path.relpath(os.path.join(root, name), starting_dir))
                    headers += [rel_name]
                if exclude and retrieve_excluded:
                    if verbose:
                        print(
                            "  Located "+kind+" header '{0}' at path '{1}'".format(name, os.path.join(root, name)))
                    rel_name = re.sub(
                        ".*?/include/", "", os.path.relpath(os.path.join(root, name), starting_dir))
                    headers += [rel_name]
        if kind != "BOSSed type":
            break
    return headers


def same(f1, f2):
    """Check whether or not two files differ in their contents except for the date line"""
    file1 = open(f1, "r")
    file2 = open(f2, "r")
    for l1, l2 in zip_longest(file1, file2, fillvalue=''):
        if l1 != l2:
            # remove spaces and make lowercase
            l1nospace = ''.join(l1.split()).lower()
            # print l1
            # print l2
            # print l1nospace
            if not l1nospace.startswith(r"#\date") \
                    and not l1nospace.startswith(r"#\\date") \
                    and not l1nospace.startswith(r"//\date") \
                    and not l1nospace.startswith(r"//\\date") \
                    and not l1nospace.startswith(r"///\date") \
                    and not l1nospace.startswith(r"///\\date"):
                # print "Doesn't match!", file1, file2
                # quit()
                return False
    return True

def update_only_if_different(existing, candidate, verbose=True):
    """Compare a candidate file to an existing file, replacing only if they differ."""
    if not os.path.isfile(existing):
         shutil.move(candidate,existing)
         if verbose:
             print( "\033[1;33m   Created "+re.sub("\\.\\/","",existing)+"\033[0m" )
    elif same(existing, candidate):
         os.remove(candidate)
         if verbose:
             print( "\033[1;33m   Existing "+re.sub("\\.\\/","",existing)+" is identical to candidate; leaving it untouched\033[0m" )
    else:
         shutil.move(candidate,existing)
         if verbose:
             print( "\033[1;33m   Updated "+re.sub("\\.\\/","",existing)+"\033[0m" )

def make_module_rollcall(rollcall_headers, verbose):
    """Create the module_rollcall header in the Core directory"""
    towrite = r"\
//   GAMBIT: Global and Modular BSM Inference Tool\n\
//   *********************************************\n\
///  \\file                                       \n\
///                                               \n\
///  Compile-time registration of GAMBIT modules. \n\
///                                               \n\
///  This file was automatically generated by     \n\
///  module_harvester.py. Do not modify.          \n\
///  The content is harvested from your local     \n\
///  installation.  If you want to add a new      \n\
///  module, just create it and make sure it      \n\
///  contains a rollcall header, and the          \n\
///  module_harvester.py script will make         \n\
///  sure it turns up here.                       \n\
///                                               \n\
///  By 'rollcall header', we mean a file         \n\
///  myBit/include/gambit/myBit/myBit_rollcall.hpp,\n\
///  where myBit is the name of your module.      \n\
///                                               \n\
///  *********************************************\n\
///                                               \n\
///  Authors:                                     \n\
///                                               \n\
///  \\author The GAMBIT Collaboration            \n\
///  \date "+datetime.datetime.now().strftime("%I:%M%p on %B %d, %Y")+"\n\
///                                               \n\
///  *********************************************\n\
                                                  \n\
#ifndef __module_rollcall_hpp__                   \n\
#define __module_rollcall_hpp__                   \n\
                                                  \n\
#include \"gambit/Elements/module_macros_incore.hpp\"\n\n"

    for h in rollcall_headers:
        towrite += '#include \"{0}\"\n'.format(h)
    towrite += "\n#endif // defined __module_rollcall_hpp__\n"

    with open("./Core/include/gambit/Core/module_rollcall.hpp", "w") as f:
        f.write(towrite)

    if verbose:
        print("Found GAMBIT Core.  Generated module_rollcall.hpp.\n")
