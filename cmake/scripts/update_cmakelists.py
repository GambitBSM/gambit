#!/usr/bin/env python
#
# GAMBIT: Global and Modular BSM Inference Tool
#*********************************************
# \file
#
#  Script to create the CMakeLists.txt files
#  for GAMBIT modules.
#
#*********************************************
#
#  Authors (add name and date if you modify):
#
#  \author Pat Scott
#          (patscott@physics.mcgill.ca)
#    \date 2014 Nov
#
#  \author Ben Farmer
#          (b.farmer@imperial.ac.uk)
#  \date 2018 Oct
#
#*********************************************
import os

toolsfile="./Utils/scripts/harvesting_tools.py"
exec(compile(open(toolsfile, "rb").read(), toolsfile, 'exec')) # Python 2/3 compatible version of 'execfile'

# Search the source tree to determine which modules are present
def module_census(verbose,install_dir,excludes):
    modules=[]
    for root,dirs,files in os.walk(install_dir):
        for mod in dirs:
            exclude = False
            for x in excludes:
                if mod.startswith(x): exclude = True
            if not exclude and mod.lower().find("bit") != -1 and mod.lower().find(".dsym") == -1:
                if verbose: print("Located GAMBIT module '{0}'.".format(mod))
                modules+=[mod]
        break
    return modules

def hidden(filename):
    return (filename.endswith("~") or filename.startswith("."))

# Actual updater program
def main(argv):

    # Lists of modules to exclude; anything starting with one of these strings is excluded.
    exclude_modules=set(["ScannerBit"])

    # List of printers to exclude; subdirectories within the Printers directory
    # that match these strings will be ignored.
    exclude_printers=set([]) # -Ditch'ed printers

    # List of backends to exclude; subdirectories within the Backends/frontends directories
    # that match these strings will be ignored.
    exclude_backends=set([]) # -Ditch'ed backends

    # Handle command line options
    verbose = False
    try:
        opts, args = getopt.getopt(argv,"vx:",["verbose","exclude-modules="])
    except getopt.GetoptError:
        print('Usage: update_cmakelists.py [flags]')
        print(' flags:')
        print('  -v                                      : More verbose output')
        print('  -x module1,backendA,printer2,modelX,... : Exclude module1, backendA, printer2, modelX, etc.')
        sys.exit(2)
    for opt, arg in opts:
        if opt in ('-v','--verbose'):
            verbose = True
            print('update_cmakelists.py: verbose=True')
        elif opt in ('-x','--exclude','--exclude'):
            exclude_modules.update(neatsplit(",",arg))
            exclude_printers.update(neatsplit(",",arg))
            exclude_backends.update(neatsplit(",",arg))

    # Find all the modules.
    modules = module_census(verbose,".",exclude_modules)

    # Add the Backends, Models and Printers dirs only if present
    for x in ["Backends", "Models", "Printers"]:
      if os.path.isdir(x): modules += [x]

    # Loop over the found modules.
    for mod in modules:

        # Clear the excluded components
        excluded_components = set([])

        # Retrieve the list of module source files.
        srcs = []
        for root,dirs,files in os.walk("./"+mod+"/src"):
            current_dirname =  os.path.basename(os.path.normpath(root))
            if mod=="Printers" and excluded(current_dirname, exclude_printers):
                if verbose: print("    Ignoring source files for printer {0}".format(current_dirname))
                continue # skip this directory
            for name in files:
                if (name.endswith(".c") or name.endswith(".cc") or name.endswith(".cpp")) and not hidden(name):
                    short_root = re.sub("\\./"+mod+"/src/?","",root)
                    if short_root != "" : short_root += "/"
                    if mod in ["Backends"] and "/backend_types/" not in short_root and excluded(name, exclude_backends):
                        if verbose: print("    Ignoring {0} source file '{1}'".format(mod,short_root+name))
                        excluded_components.add(os.path.splitext(name)[0])
                        continue # skip this file
                    if verbose: print("    Located {0} source file '{1}'".format(mod,short_root+name))
                    srcs+=[short_root+name]

        # Retrieve the list of module header files.
        headers = []
        for root,dirs,files in os.walk("./"+mod+"/include"):
            current_dirname =  os.path.basename(os.path.normpath(root))
            if mod=="Printers" and excluded(current_dirname, exclude_printers):
                if verbose: print("    Ignoring header files for printer {0}".format(current_dirname))
                excluded_components.add(current_dirname)
                continue # skip this directory
            for name in files:
                short_root = re.sub("\\./"+mod+"/include/?","",root)
                if short_root != "" : short_root += "/"
                if mod in ["Backends", "Printers"] and "/backend_types/" not in short_root and excluded(name, exclude_backends | exclude_printers):
                    if verbose: print("    Ignoring {0} header file '{1}'".format(mod,short_root+name))
                    excluded_components.add(os.path.splitext(name)[0])
                    continue # skip this file
                if (name.endswith(".h") or name.endswith(".hh") or name.endswith(".hpp")) and not hidden(name):
                    if verbose: print("    Located {0} header file '{1}'".format(mod,short_root+name))
                    headers+=[short_root+name]

        # If no sources or headers were found, this wasn't actually a module
        if srcs == [] and headers == []: continue

        # Make a candidate CMakeLists.txt file for this module.
        towrite = "\
# GAMBIT: Global and Modular BSM Inference Tool \n\
#***********************************************\n\
#  \\file                                       \n\
#                                               \n\
#  CMake list of source and header files in     \n"
        if (mod == "Backends"):
            towrite += "\
#  GAMBIT backends directory.                   \n"
        elif (mod == "Printers"):
            towrite += "\
#  GAMBIT printers directory.                   \n"
        elif (mod == "Models"):
            towrite += "\
#  GAMBIT models directory.                     \n"
        else:
            towrite += "\
#  GAMBIT module "+mod+".                       \n"
        towrite += "\
#                                               \n\
#  This file was automatically generated by     \n\
#  update_cmakelists.py. Do not modify.         \n\
#                                               \n\
#  Do not add to this if you want to add a new  \n\
#  source or header file to the make system --  \n\
#  just rerun cmake instead.                    \n\
#                                               \n\
#***********************************************\n\
#                                               \n\
#  Authors:                                     \n\
#                                               \n\
#  \\author The GAMBIT Collaboration            \n\
#  \\date "+datetime.datetime.now().strftime("%I:%M%p on %B %d, %Y")+"\n\
#                                               \n\
#***********************************************\n\
                                                \n"
        towrite+= "\
set(source_files                                \n"
        for cpp in srcs: towrite+='src/{0}\n'.format(cpp)
        towrite+=")\n\nset(header_files\n"
        for hpp in headers: towrite+='include/{0}\n'.format(hpp)
        towrite+=")\n\n"
        towrite+="add_gambit_library("+mod+" OPTION OBJECT SOURCES ${source_files} HEADERS ${header_files})\n"
        if (mod == "Backends"):
          towrite+= "\n\
include(../cmake/toy_backends.cmake)          \n"
        cmakelist = "./"+mod+"/CMakeLists.txt"
        candidate = "./scratch/build_time/"+mod+"_CMakeLists.txt"
        with open(candidate,"w") as f: f.write(towrite)
        update_only_if_different(cmakelist, candidate)

    if verbose: print("Finished updating module CMakeLists.txt files.")

# Handle command line arguments (verbosity)
if __name__ == "__main__":
   main(sys.argv[1:])

