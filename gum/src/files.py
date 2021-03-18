#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Master module containing all routines for finding, creating,
#  amending, and reading files.
#
#  *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019, 2020
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2020 Feb
#
#  **************************************

import os
import re
import numpy as np
import yaml
from distutils.dir_util import remove_tree
from collections import defaultdict
import filecmp
import glob

from .setup import *

def remove_tree_quietly(path):
    """
    Deletes a directory if it exists
    """
    if os.path.exists(path):
        remove_tree(path)

def mkdir_if_absent(path, reset_dict={}, hard_reset=False):
    """
    Makes a new directory if the proposed path doesn't yet exist
    """
    try:
        os.makedirs(path)
    except OSError:
        if not os.path.isdir(path):
            raise

    if reset_dict != {}:
        if not hard_reset:
            reset_dict['new_dirs']['soft'].append(path)
        else:
            reset_dict['new_dirs']['hard'].append(path)

def full_filename(filename, module, overwrite_path = None):
    """
    Formats a gambit file correctly based on the filename, the
    module, and whether it is a header file.
    """

    # strip leading & trailing slashes
    filename.strip('/')
    module.strip('/')

    path = ""
    if filename.endswith(".hpp"):
        path = "include/gambit/{0}/".format(module)
    elif filename.endswith(".cpp"):
        path = "src/"
    elif filename.endswith(".py"):
        path = "scripts/"
    elif filename.endswith(".dif"):
        path = "patches/"
    else:
        path = ""

    location = "../{0}/{1}{2}".format(module, path, filename)

    # If the user specifies that the "path" should be overwritten based
    # on the filetype, then do so...
    if overwrite_path: 
        location = "../{0}/{1}{2}".format(module, overwrite_path, filename)

    return location

def find_file(filename, module):
    """
    Tries to find a file in a specified module.
    """

    location = full_filename(filename, module)

    if os.path.exists(location):
        return True
    else:
        return False

def find_capability(capability, module, filename=None):
    """
    Tries to find a CAPABILITY in a specified rollcall file.
    """

    module.strip('/')

    if not filename:
        filename = "{0}_rollcall.hpp".format(module)
    else:
        filename.strip('/')

    location = full_filename(filename, module)
    if find_file(filename, module):
        pass
    else:
        raise GumError(("\n\nCannot find capability {0} in rollcall header file"
                        " {1} as the file does not exist!!").format(capability,
                                                                    location))
    pat = r'#define CAPABILITY {}\b'.format(capability)

    with open(location) as f:
        for num, line in enumerate(f, 1):
            r = re.search(pat, line)
            if r:
                return True, num

    return False, 0

def amend_rollcall(capability, module, contents, reset_dict, filename=None):
    """
    Adds a new FUNCTION to an existing CAPABILITY in a rollcall header.
    """

    # Get the actual function name from the contents
    fpat = r'#define FUNCTION\s*(.*)\s*'
    s = re.search(fpat, contents)
    function = s.group(1) if s else ""
    if not function:
        raise GumError(("No FUNCTION found in contents of amend_rollcall for "
                        "CAPABILITY {0}!").format(capability))

    module.strip('/')

    if not filename:
        filename = "{0}_rollcall.hpp".format(module)
    else:
        filename.strip('/')

    location = full_filename(filename, module)
    if find_file(filename, module):
        pass
    else:
        raise GumError(("\n\nCannot find capability {0} in rollcall header file"
                        " {1} as the file does not exist!!").format(capability,
                                                                    location))

    pat = r'#define CAPABILITY {}\b'.format(capability)

    found = False

    with open(location) as f:
        for num, line in enumerate(f, 1):
            r = re.search(pat, line)
            if r:
                found = True
                break

    lookup = "#undef CAPABILITY"

    # Found the capability -> find the #undef
    if found == True:
        with open(location) as f:
            for i in range(num):
                next(f)
            for no, line in enumerate(f, 1+num):
                if lookup in line:
                    break

        amend_file(filename, module, contents, no-1, reset_dict,
                   is_capability = True, capability = capability, 
                   function = function)

    else:
        raise GumError(("\n\nCapability {0} not found in "
                        "{1}!").format(capability, filename))

def find_function(function, capability, module, filename=None):
    """
    Tries to find a FUNCTION in a specified rollcall header file.
    """

    module.strip('/')

    if not filename:
        filename = "{0}_rollcall.hpp".format(module)
    else:
        filename.strip('/')

    location = full_filename(filename, module)

    # First check the capability exists...
    exists, num = find_capability(capability, module, filename)

    if not exists:
        return False, 0

    pat = r'#define FUNCTION {}\b'.format(function)
    terminate = "#undef CAPABILITY"

    with open(location) as f:
        for i in range(num):
            next(f)
        for no, line in enumerate(f, 1+num):
            r = re.search(pat, line)
            if r:
                return True, no
            if terminate in line:
                return False, 0

    return False, 0

def find_string(filename, module, string, filename_overwrite = ""):
    """
    Tries to find a generic string in a given file.
    """

    location = full_filename(filename, module)
    if filename_overwrite: location = filename_overwrite

    if find_file(filename, module):
        pass
    else:
        raise GumError(("\n\nCannot find string {0} in the file"
                        " {1} as the file does not exist!!").format(string,
                                                                    location))

    with open(location) as f:
        for num, line in enumerate(f, 1):
            if string in line:
                return True, num

    return False, 0

def write_file(filename, module, contents, reset_dict, overwrite_path = None):
    """
    Writes a file in a specified location.
    """

    location = full_filename(filename, module, overwrite_path)
    location_parts = os.path.split(location)

    if find_file(filename, module):
        raise GumError(("\n\nTried to write file " + location +
                        ", but it already exists."))

    reset_dict['new_files']['files'].append(location)

    # Save a temp mug file, incase something goes wrong.
    drop_mug_file("mug_files/temp.mug", reset_dict)

    # Make the directory if it doesn't exist
    mkdir_if_absent(location_parts[0])
    # Create new file
    open(location, 'w').write(contents)

    print("File {} successfully created.".format(location))

def copy_file(filename, module, output_dir, reset_dict, 
              existing=True, overwrite_path=None):
    """
    Copies an output file in a specified location.
    """
    import shutil

    location = full_filename(filename, module, overwrite_path=overwrite_path)
    location_parts = os.path.split(location)
    GUM_version = output_dir + '/' + location[3:]

    # Todo - do something with this. It's not doing anything right now.
    if existing:
        reset_dict['copied_amended_files']['files'].append(location)
    else:
        reset_dict['new_files']['files'].append(location)

    # Save a temp mug file, incase something goes wrong.
    drop_mug_file("mug_files/temp.mug", reset_dict)

    mkdir_if_absent(location_parts[0])
    # Copy the file
    shutil.copy(GUM_version, location)

    print("Copied "+GUM_version+" to "+location+".")

def delete_file(filename, module):
    """
    Deletes a file in a specified location.
    """

    location = full_filename(filename, module)

    if find_file(filename, module):
        os.remove(location)
        print("File {} successfully removed.".format(location))

def amend_file(filename, module, contents, line_number, reset_dict, 
               is_capability=False, capability="", function=""):
    """
    Amends a file in a specified location with 'contents', starting
    from a given line number.
    If it's a capability then add the capability and function names.
    """

    location = full_filename(filename, module)

    # Catch an error code
    if line_number < -1:
        raise GumError(("Error in amend_file routine. Received line_number"
                        " of " + line_number + " to write to the file "
                        "" + location + ". I think something is wrong."))

    # Find end of file
    if line_number == -1:
       temp_line_number = 0
       with open(location) as f:
            for line in f:
                temp_line_number += 1
       line_number = temp_line_number
      

    if not find_file(filename, module):
        raise GumError(("\n\nERROR: Tried to amend file " + location +
                        ", but it does not exist."))

    # If it's a capability, add this to the capability node
    if is_capability:
        reset_dict['capabilities'][location].append(capability+'|'+function)
        
    # Otherwise just the generic 'amended' stuff will do.
    else:
        # Check there's not already an identical entry - happens sometimes!
        present = False
        if location in reset_dict['amended_files']:
            if contents in reset_dict['amended_files'][location]:
                present = True

        if not present:
            reset_dict['amended_files'][location].append(contents)

    # Save a temp mug file, incase something goes wrong.
    drop_mug_file("mug_files/temp.mug", reset_dict)

    temp_location = location + "_temp"
    lines = open(location, 'r').readlines()

    with open(temp_location, 'w') as f:
        for i in range(line_number):
            f.write(lines[i])
        f.write(contents)
        for i in range(len(lines)-line_number):
            f.write(lines[i+line_number])

    os.remove(location)
    os.rename(temp_location, location)

    print("File {} successfully amended.".format(location))

def add_capability(module, capability, function, reset_dict,
                   returntype, filename=None, dependencies=None, 
                   allowed_models=None, backend_reqs=None):
    """
    Finds a capability in a given module. If it already exists, then add 
    a new function entry to it. If it is not found, then add the 
    capability too.
    """

    cap_exists, cap_line = find_capability(capability, module, filename)

    # Get the function signature for the rollcall
    func = write_function(function, returntype, dependencies, 
                          allowed_models, backend_reqs)

    # If the capability is there...
    if cap_exists:
        # Check the function isn't already there too
        func_exists, func_line = find_function(function, capability, 
                                               module, filename)

        if func_exists:
            raise GumError(("The function "  + function + " already exists "
                            "in the capability " + capability + " in the "
                            "module " + module + "."))

        # If there's already the capability, then the only thing we need 
        # is the function. Add it to the existing capability.
        amend_file(filename, module, func, cap_line+1, reset_dict, 
                   is_capability = True, capability = capability, 
                   function = function)
        # The +1 takes into account the START_CAPABILITY line. Hopefully 
        # being a bit lazy here doesn't come back to bite me, but I doubt it.

    # Otherwise - add some capability tags either side and write it to the 
    # end of the file.
    else:
        contents = (
            "  #define CAPABILITY {0}\n"
            "  START_CAPABILITY\n"
            "  \n"
            "{1}"
            "  \n"
            "  #undef CAPABILITY\n"
        ).format(capability, func)

        n = -1
        location = full_filename(filename, module)
        with open(location) as f:
            for num, line in enumerate(f, 1):
                if "#undef CAPABILITY" in line: n = num
        amend_file(filename, module, contents, n+1, reset_dict,
                   is_capability = True, capability = capability, 
                   function = function)


def write_function(function, returntype, dependencies=None,
                   allowed_models=None, backend_reqs=None):
    """
    Writes a function for a rollcall header file.
    """

    extras = ""

    if dependencies:
        for i in np.arange(len(dependencies)):
            extras += "DEPENDENCY({0}, {1})\n".format(dependencies[i][0],
                                                      dependencies[i][1])
    if allowed_models:
        # List
        if isinstance(allowed_models, list):
            extras += "ALLOW_MODELS({0})\n".format(', '.join(allowed_models))
        else:
            extras += "ALLOW_MODELS({0})\n".format(allowed_models)

    if backend_reqs:
        for i in np.arange(len(backend_reqs)):
            bereq = backend_reqs[i]
            if not isinstance(bereq, BackendReq):
                raise GumError(("\n\nBackend requirement at position " + i +
                                "not passed as instance of class BackendReq."))

            add = ", ".join([bereq.capability,
                             "({0})".format(', '.join(bereq.tags)),
                             bereq.cpptype])

            if not bereq.var:
                add += ", ({0})".format(', '.join(bereq.args))

            extras += "BACKEND_REQ({0})\n".format(add)

    towrite = (
            "#define FUNCTION {0}\n"
            "  START_FUNCTION({1})\n"
            "{2}"
            "#undef FUNCTION\n"
    ).format(function, returntype, dumb_indent(2, extras))

    return dumb_indent(4, towrite)

def add_new_model_to_function(filename, module, capability, function, 
                              model_name, reset_dict, pattern="ALLOW_MODELS"):
    """
    Adds a new entry to the ALLOW_MODELS macro for a given (pre-existing)
    CAPABILITY and FUNCTION. Pattern can be overwritten by something else
    to match e.g. ALLOW_MODEL_DEPENDENCES
    """

    location = full_filename(filename, module)
    temp_location = location + "_temp"

    # Check the capability + function exist
    exists, num = find_function(function, capability, module, filename)
    if not exists:
        raise GumError(("Could not find function {0} in capability "
                        "{1} in {2}").format(function, capability, location))

    counter = 0
    take_it_slow = False
    modellist = ""
    adding_to_modellist = False
    done = False

    with open(location, 'r') as f, open(temp_location, 'w+') as g:
        # Write everything up to the function
        for line in f:
            counter += 1
            if counter > num and not done:
                # Be cool if we are nearby
                take_it_slow = True
            # If we're not nearby just go for it
            if not take_it_slow:
                g.write(line)
            # If we're nearby then go through line-by-line
            else:
                if pattern in line:
                    # Start adding to the list of models
                    adding_to_modellist = True
                elif not adding_to_modellist: 
                    g.write(line)
                if adding_to_modellist and not done:
                    modellist += line
                    # End of macro
                    if ")" in line: 
                        # Check there's no more than ten here. 
                        numentries = len(modellist.split(','))
                        # Add the model name to the end if there's
                        # less than ten (macro maximum)
                        if numentries < 10:
                            modellist = re.sub(r'\)', ", "+model_name+')', 
                                        modellist, 1) 
                        # Otherwise add a new entry altogether
                        else:
                            newentry = "\n      {0}({1})".format(pattern, 
                                                                 model_name)
                            g.write(newentry)
                        g.write(modellist)
                        adding_to_modellist = False
                        take_it_slow = False
                        done = True

    # Entry for the mug file to parse
    entry = location+'|'+capability+'|'+function+'|'+pattern
    # Add to the reset dictionary
    reset_dict['new_models'][entry].append(model_name)

    os.remove(location)
    os.rename(temp_location, location)

    print("Model {} added to capability {}.".format(model_name, capability))


def blame_gum(message):
    """
    Writes function to dump at the beginning of a new GAMBIT file.
    Blames GUM. Takes a message to describe the new file.
    """

    if not message.startswith("///"):
        message = "/// " + message

    towrite = (
            "//   GAMBIT: Global and Modular BSM Inference Tool\n"
            "//   *********************************************\n"
            "///  \\file\n"
            "///\n"
            + message +
            "\n"
            "///\n"
            "///  Authors (add name and date if you modify):    \n"
            "///       *** Automatically created by GUM ***     \n"
            "///                                                \n"
            "///  \\author The GAMBIT Collaboration             \n"
            "///  \\date " +
            datetime.datetime.now().strftime("%I:%M%p on %B %d, %Y") +
            "\n"
            "///                                                \n"
            "///  ********************************************* \n"
            "\n"
    )

    return towrite

def dumb_indent(numspaces, text):
    """
    Indents input text by specified number of spaces.
    """

    lines = text.splitlines(True)
    out = ""
    for line in lines:
       for i in range(0, numspaces):
           out += " "
       out += line

    return out

def indent(text, numspaces=0):
    """
    Increases indents of text every time it detects an open
    curly brace {, and decreases every time it detects a closed
    curly brace }. Does nothing if there is a {}.
    """

    lines = text.splitlines(True)
    out = ""

    for line in lines:

        if numspaces < 0:
            raise GumError(("\n\nTried to indent a negative number of spaces. "
                            "Please check for rogue braces."))

        num_open = line.count("{")
        num_closed = line.count("}")
        if num_open != num_closed:
            numspaces -= (num_closed*2)
        for i in range(0, numspaces):
            out += " "
        if num_open != num_closed:
            numspaces += (num_open*2)
        out += line

    return out

def revert(reset_file):
    """
    Go back to the previous save point.
    """

    import shutil

    print("GUM called in reset mode.")

    if not reset_file.endswith('.mug'):
        raise GumError(("\n\n\tPlease use a generated .mug "
                       "file if using the reset function."))

    with open(reset_file, "r") as f:

        try:
            data = yaml.safe_load(f)
        except yaml.YAMLError as exc:
            raise(exc)

        # The files GUM wrote as new.
        # GUM can just simply delete these.
        new_files = data['new_files']['files']

        for i in new_files:
            if os.path.isfile(i):

                # If deleted file is a BOSS config file, BOSS might have been run
                if "BOSS/config" in i:

                    from .backends import get_boss_backend_name_and_version, force_backend_rebuild

                    be_name, be_ver = get_boss_backend_name_and_version(i)
                    be_name_ver_safe = be_name + "_" + be_ver.replace('.','_')

                    boss_reset_file = 'reset_info.' + be_name_ver_safe + ".boss"

                    boss_dir = '/'.join(i.split('/')[:-2]) + '/'
                    gambit_build_dir = "../build/"

                    # If there is a reset file on GAMBIT's build directory, BOSS was run
                    if os.path.exists(gambit_build_dir + boss_reset_file) :

                        # TODO: This only removes changes to the backend, not the main gambit tree, so I don't think it's needed
                        #call_boss_reset(gambit_build_dir, boss_dir, reset_file_name)

                        # Remove BOSS-generated files in the main GAMBIT tree
                        backend_types_dir = "../Backends/include/gambit/Backends/backend_types/" + be_name_ver_safe
                        if os.path.isdir(backend_types_dir):
                            shutil.rmtree(backend_types_dir, ignore_errors=True)
                            print("Deleting backend types for " + be_name_ver_safe + "...")
                        frontend_header_file = "../Backends/include/gambit/Backends/frontends/" + be_name_ver_safe + ".hpp"
                        if os.path.isfile(frontend_header_file):
                            os.remove(frontend_header_file)
                            print("Deleting " + frontend_header_file + "...")

                        # Remove reset file
                        os.remove(gambit_build_dir + boss_reset_file)

                    # In case it was built but not nuked, force it to rebuild from scratch
                    force_backend_rebuild(be_name.lower(), be_ver)

                print("Deleting {0}...".format(i))
                os.remove(i)

            else:
                print(("Tried deleting {0}, but it seems to have already been "
                      "removed.".format(i)))
        
        # Go through the new capabilities and functions
        if 'capabilities' in data:
            capabilities = data['capabilities']
            for filename, entries in iteritems(capabilities):

                temp_file = filename + "_temp"
                with open(filename, 'r') as original_file:
                    text = original_file.read()
                    lines = text.splitlines()

                for entry in entries:
                    capability, function = entry.split('|')
                    print((
                           "Removing FUNCTION: {0}, in CAPABILITY: {1}, in "
                           "file {2}..."
                           ).format(capability, function, filename))

                    # 1. Find the FUNCTION within the CAPABILITY
                    func_line = find_string("","",function,filename)
                    if not func_line[0]:
                        print(("Tried deleting the FUNCTION {0}:\n from "
                              "file {1}, but I could not find it -- "
                              "perhaps it has already been removed?"
                              ).format(function, filename))
                    # 2. Remove the strings between the #define FUNCTION
                    # and #undef FUNCTION lines
                    else:
                        tomatch_start = "#define FUNCTION " + function
                        tomatch_end = "#undef FUNCTION"
                        writing = False
                        s = ""
                        for line in lines:
                            if tomatch_start in line:
                                writing = True
                            if writing:
                                if "START_CAPABILITY" in line: continue
                                else: s += line + "\n"
                            if writing:
                                if tomatch_end in line: writing = False
                        text = text.replace(s, '')
                        new_file = open(temp_file, 'w')
                        new_file.write(text)
                        new_file.close()
                        os.remove(filename)
                        os.rename(temp_file, filename)
                        # 3. Check to see if the CAPABILITY is empty - 
                        # nuke it if so
                        with open(filename, 'r') as original_file:
                            text = original_file.read()
                            lines = text.splitlines()

                        cap_line = find_string("","",capability,filename)
                        if not cap_line[0]:
                            print(("Tried deleting the CAPABILITY {0} from "
                                  "file {1}, but I could not find it -- "
                                  "perhaps it has already been removed?"
                                  ).format(function, filename))
                        else:
                            writing = False
                            tomatch_start = "#define CAPABILITY " + capability
                            tomatch_end = "#undef CAPABILITY"
                            pat = '{}(.*?){}'.format(tomatch_start, tomatch_end)
                            newtext = re.search(pat, text, re.DOTALL).group(1)
                            s = ""
                            t = newtext.strip()
                            if t == "START_CAPABILITY":
                                for line in lines:
                                    if tomatch_start in line:
                                        writing = True
                                    if writing:
                                        s += line + "\n"
                                    if writing:
                                        if tomatch_end in line: writing = False
                                text = text.replace(s, '')
                                new_file = open(temp_file, 'w')
                                new_file.write(text)
                                new_file.close()
                                os.remove(filename)
                                os.rename(temp_file, filename)

        # The files that existed previously, that GUM added stuff to.
        # These are a little more annoying to deal with.
        amended_files = data['amended_files']

        # We want to match strings and not line numbers or anything like that.
        # This way, there is no order needed to perform resets in.
        for filename, v in iteritems(amended_files):

            print("Amending {0}...".format(filename))

            temp_file = filename + "_temp"
            with open(filename, 'r') as original_file:
                text = original_file.read()

            # This is the YAML node for the strings needing to be deleted
            for string in v:

                # If we find it, kill it
                if string in text:
                    text = text.replace(string, '')
                # Otherwise assume someone has messed with it
                else:
                    print(("Tried deleting the following entry from "
                           "{0}, but I could not find it:\n\n{1}\n\n"
                           "Perhaps it has already been removed."
                           ).format(filename, string))

            # Write the new amended file
            new_file = open(temp_file, 'w')
            new_file.write(text)

            os.remove(filename)
            os.rename(temp_file, filename)

        # Now go through those amendments that are adding new models to an 
        # existing ALLOW_MODELS (or similar) macro for a given capability
        if 'new_models' in data:
            amended_capabilities = data['new_models']

            for loc_cap_func_pattern, model in iteritems(amended_capabilities):
                
                location, capability, function, pattern = \
                                                 loc_cap_func_pattern.split('|')
                module = location.split('/')[1]
                filename = location.split('/')[-1]

                print(("Removing model {3} from capability {0}; function {1};"
                       " in {2}..."
                       ).format(capability, function, module, model[0]))

                temp_file = location + "_temp"
                
                exists, num = find_function(function, capability, module, 
                                            filename)

                if not exists:
                    print(("Could not find capability {0} in location {1}! "
                           "Continuing...").format(capability, location)) 
                    continue
                
                counter = 0
                done = False
                take_it_slow = False
                modellist = ""
                taking_from_modellist = False
                
                with open(location, 'r') as f, open(temp_file, 'w+') as g:
                    for line in f:
                        counter += 1
                        if counter > num and not done: 
                            take_it_slow = True
                        if not take_it_slow: 
                            g.write(line)
                        else:
                            if pattern in line: 
                                taking_from_modellist = True 
                            elif not taking_from_modellist: g.write(line)
                            if taking_from_modellist and not done:
                                modellist += line
                                if ")" in line: 
                                    # Take the model out of the list
                                    modellist = re.sub(', '+model[0], '', 
                                                       modellist)
                                    g.write(modellist)
                                    taking_from_modellist = False
                                    take_it_slow = False
                                    done = True

                os.remove(location)
                os.rename(temp_file, location)

        # Clean up the particle database
        if 'particles' in data:
            particles = data['particles']

            # If there's anything, that is...
            if len(particles) > 0:

                # Fire it up!
                with open("./../config/particle_database.yaml", "r") as f:
                    particledata = yaml.safe_load(f)
                    # particledata is a dict

                # This is a list of dictionaries
                parts = particledata['OtherModels']['Particles']

                # List of particles to remove
                toremove = list(particles.values())[0]
                toremove_name = [x.split('|')[0] for x in toremove]
                toremove_model = toremove[0].split('|')[1]

                print("Removing the following particles from the particle DB:")
                print(toremove_name)
                
                # Remove them - belt and bracers with the model name!
                newparts = [x for x in parts if x['name'] not in toremove_name
                            and x['description'].find(toremove_model)]
                particledata['OtherModels']['Particles'] = newparts

                stream = (
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
                       "#       name: \"h0\"                         Creates rollcall entries for \"h0_1_decay_rates\" and \"h0_2_decay_rates\" CAPABILITIES.\n"
                       "#       name: [\"Higgs\", \"h0_2\"]            Alternative syntax - if particles within sets have different names - creating CAPABILITIES \"Higgs_decay_rates\" and \"h0_2_decay_rates\".\n"
                       "#\n"
                       "# Note: If there is no entry for the 'DecayBit' field, GAMBIT will use the 'name' and 'conjugate' fields by default.\n"
                       "# TODO: Decide if Decays belong here, or elsewhere (GUM)\n\n"
                )


                # Overwrite the particle database YAML file
                stream += yaml.dump(particledata).replace('\n  - ', '\n\n  - ')

                with open("./../config/particle_database.yaml", "w") as f:
                    f.write(stream)

        # If there are any new dirs remove them if empty, as well as any empty directories on the same tree
        # Hard reset wipes out directory with contents
        if 'hard' in data['new_dirs']:
            for new_dir in data['new_dirs']['hard']:
                if os.path.isdir(new_dir):
                    shutil.rmtree(new_dir, ignore_errors=True)
                    print("Deleting full directory tree {0}...".format(new_dir))

        # Soft reset only deletes empty directories
        if 'soft' in data['new_dirs']:

            for new_dir in data['new_dirs']['soft']:
                empty = True
                while(empty):
                    if os.path.isdir(new_dir):
                        try:
                            os.rmdir(new_dir)
                            print("Deleting directory {0}...".format(new_dir))
                        except OSError:
                            empty = False;
                        new_dir = os.path.dirname(new_dir)
                    else:
                        empty = False

    return

def check_for_existing_entries(model_name, darkbit, colliderbit, output_opts):
    """
    Checks for existing entries within GAMBIT, for a new model.
    """

    # Models entries
    m = "Models"
    if ( find_file("models/" + model_name + ".hpp", m) or
         find_file("SpectrumContents/" + model_name + ".cpp", m) or 
         find_file("SimpleSpectra/" + model_name + "SimpleSpec" + ".hpp", m)
       ):
       raise GumError(("Model {0} already exists in {1}").format(model_name, m))
    m = "SpecBit"
    if (
         find_file("SpecBit_" + model_name + ".cpp", m) or 
         find_file("SpecBit_" + model_name + "_rollcall.hpp", m)
       ):
       raise GumError(("Model {0} already exists in {1}").format(model_name, m))

    if darkbit:
        m = "DarkBit"
        if find_file(model_name + ".cpp", m):
            raise GumError(("Model {0} already exists in {1}"
                            ).format(model_name))
        if output_opts.mo:
            ver = "3.6.9.2"
            f = "frontends/MicrOmegas_{0}_{1}".format(model_name, 
                                                      ver.replace('.','_'))
            if ( find_file(f+".cpp", "Backends") or 
                 find_file(f+".hpp", "Backends")
               ):
                raise GumError((
                                "MicrOmegas entry already exists for model {0}"
                               ).format(model_name))

def drop_mug_file(mug_file, contents):
    """
    Drops a .mug (reset) file from the reset contents saved by GUM.
    """

    # Make the folder for mug files. 
    mkdir_if_absent("mug_files")

    d = dict(contents)

    if 'new_files' in d:
        new_files = dict(d['new_files'])
    else:
        new_files = {}
    if 'amended_files' in d:
        amended_files = dict(d['amended_files'])
    else:
        amended_files = {}
    if 'new_models' in d:
        new_models = dict(d['new_models'])
    else:
        new_models = {}
    if 'capabilities' in d:
        capabilities = dict(d['capabilities'])
    else:
        capabilities = {}
    if 'particles' in d:
        particles = dict(d['particles'])
    else:
        particles = {}
    if 'new_dirs' in d:
        new_dirs = dict(d['new_dirs'])
    else:
        new_dirs = {}
        
    new_contents = {'new_files': new_files, 'amended_files': amended_files, 
                    'new_models' : new_models, 'capabilities' : capabilities,
                    'particles' : particles, 'new_dirs' : new_dirs}

    with open(mug_file, 'w') as f:
        yaml.dump(new_contents, f, default_flow_style=False)


def drop_yaml_file(model_name, model_parameters, add_higgs, reset_contents,
                   spectrum, with_spheno):
    """
    Drops an example YAML file with all decays of a new model
    added.
    """

    towrite = (
        "####################################################################\n"
        "## GAMBIT configuration for a random scan of the {0} model\n"
        "##\n"
        "## Simply prints the spectrum of the new model.\n"
        "####################################################################\n"
        "\n"
        "\n"
        "Parameters:\n"
        "\n"
        "  # SM parameters.\n"
        "  StandardModel_SLHA2: !import "
        "include/StandardModel_SLHA2_defaults.yaml\n"
        "\n"
    ).format(model_name)

    if add_higgs and not with_spheno:
        towrite+= (
            "  StandardModel_Higgs:\n"
            "    mH: 125.09\n"
            "\n"
        )

    towrite += ("  {0}:\n").format(model_name)

    # Don't want the SM-like Higgs mass a fundamental parameter
    bsm_params = [x for x in model_parameters if x.name != 'mH'
                  and x.sm == False]
    params = {}

    for i in bsm_params:
        if i.shape == 'scalar' or i.shape == None: params[i.gb_in] = i.default
        elif re.match("m[2-9]x[2-9]", i.shape): 
            size = int(i.shape[-1])
            for j in range(size):
                for k in range(size):
                    params[i.gb_in + '_' + str(j+1) + 'x' + str(k+1)] = i.default
        elif re.match("v[2-9]", i.shape): 
            size = int(i.shape[-1])
            for j in range(size):
                params[i.gb_in + '_' + str(j+1)] = i.default

    # No double counting (also want to preserve the order)
    norepeats = {}
    for i,val in params.items():
      if i not in norepeats.keys():
        norepeats[i] = val

    # Do this in alphabetical order, so it looks nice.
    for i,val in sorted(norepeats.items()):
        towrite += ("    {0}: {1}\n").format(i,str(val))

    towrite += (
        "\n"
        "Priors:\n"
        "\n"
        "  # All the priors are simple for this scan, so they "
        "are specified directly in the Parameters section.\n"
        "\n"
        "\n"
        "Printer:\n"
        "\n"
        "  printer: cout\n"
        "\n"
        "Scanner:\n"
        "\n"
        "  use_scanner: random\n"
        "\n"
        "  scanners:\n"
        "\n"
        "    random:\n"
        "      plugin: random\n"
        "      point_number: 1\n"
        "      like:  LogLike\n"
        "\n"
        "ObsLikes:\n"
        "\n"
        "  - purpose:      Observable\n"
        "    capability:   {1}\n"
        "    type:         map_str_dbl\n"
        "\n"
        "Rules:\n"
        "  # None needed\n"
        "\n"
        "Logger:\n"
        "\n"
        "  redirection:\n"
        "    [Backends] : \"backends.log\"\n"
        "    [Default] : \"default.log\"\n"
        "    [DecayBit] : \"DecayBit.log\"\n"
        "    [PrecisionBit] : \"PrecisionBit.log\"\n"
        "    [Scanner] : \"ScannerBit.log\"\n"
        "    [SpecBit] : \"SpecBit.log\"\n"
        "    [Dependency Resolver] : \"dep_resolver.log\"\n"
        "    [Error] : \"errors.log\"\n"
        "    [Warning] : \"warnings.log\"\n"
        "    [Utilities] : \"utils.log\"\n"
        "\n"
        "KeyValues:\n"
        "\n"
        "  dependency_resolution:\n"
        "    prefer_model_specific_functions: true\n"
        "\n"
        "  likelihood:\n"
        "    model_invalid_for_lnlike_below: -5e5\n"
        "    model_invalid_for_lnlike_below_alt: -1e5\n"
        "\n"
        "  default_output_path: \"runs/{0}/\"\n"
        "\n"
        "  debug: false\n"
        "\n"
    ).format(model_name, spectrum)

    write_file(model_name + '_example.yaml', 'yaml_files', 
               towrite, reset_contents)

def write_config_file(outputs, model_name, reset_contents, rebuild_backends=[]):
    """
    Drops a configuration file, which will build the correct backends, 
    and then GAMBIT, in the correct order.

    9/8/20: updated to just print these contents, not add to file.
    """

    towrite = (
        "\n"
        "The commands needed to build GAMBIT successfully (replacing '<n>' "
        "with\nthe number of logical cores available on your machine) are:\n"
        "\n"
        "cd ../build\n"
        "cmake ..\n"
    )

    backends = []
    if outputs.pythia:
        backends.append("pythia_{0}".format(model_name.lower()))

    if outputs.mo:
        backends.append("micromegas_{0}".format(model_name))

    if outputs.spheno:
        backends.append("sarah-spheno_{0}".format(model_name))
        backends.append("higgsbounds")
        backends.append("higgssignals")

    if outputs.vev:
        backends.append("vevacious")

    if outputs.ch:
        backends.append("calchep")

    # If any backend needs rebuilding, nuke them first
    bes = ""
    for be in backends:
      if be in rebuild_backends:
        towrite += ("make nuke-{0}\n").format(be)
      towrite += ("make {0}\n").format(be)

    # Have to cmake here because of Pythia headers.
    if outputs.pythia: towrite += "cmake ..\n"

    # Just GAMBIT to go.
    towrite += (
        "make -j<n> gambit\n"
    )

    print(towrite)

def compare_patched_files(gambit_dir, gum_dir, file_endings = ()):
    """
    Check if there is already a patched version of the backend files
    and if they are they same as the gum version.
    Returns True if the directory is empty or all files match
    Returns False if any files are different or missing
    """

    if not os.path.exists(gambit_dir) or len(os.listdir(gambit_dir)) == 0:
        return True

    # Get files from both directories
    gambit_files =  [f for f in glob.glob(gambit_dir+'**/*') if f.endswith(file_endings)]
    gum_files = [f for f in glob.glob(gum_dir+'**/*') if f.endswith(file_endings)]

    # If the number of files is different it needs recompiling
    if len(gambit_files) != len(gum_files):
      return False

    # Loop over files to and compare
    for gbf in gambit_files:

        gbfilename = gbf.replace(gambit_dir,'')

        for gumf in gum_files:
            gumfilename = gumf.replace(gum_dir,'')

            if gbfilename == gumfilename and not filecmp.cmp(gbf, gumf, shallow=False):
                  return False
            
    return True

def write_capability_definitions(filename, model_name, cap_def, reset_dict):
    """
    Writes entries in the capability definitions file
    """

    contents = "\n#####  " + model_name + " model #####\n\n"

    for key, text in cap_def.items():
        contents += key + ": |\n"\
                         "    " + text + "\n\n"

    amend_file(filename, "config", contents, -1, reset_dict)

def write_model_definitions(filename, model_name, model_def, reset_dict):
    """
    Writes entries in the model definitions file
    """

    contents = '\n'
    for key, text in model_def.items():
        contents += key + ": |\n"\
                         "    " + text + "\n\n"

    amend_file(filename, "config", contents, -1, reset_dict)

    
