#!/usr/bin/env python
#
# GAMBIT: Global and Modular BSM Inference Tool
#*********************************************
# \file
#
#  Script to find scanner (and test function)
#  libraries and write various ScannerBit-
#  related config and compilation files.
#
#*********************************************
#
#  Authors (add name and date if you modify):
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2014 Dec
#  \date 2015 Jan
#
#  \author Jonathan Cornell
#  \date 2015 February (removed -rdynamic from
#                       OSX linker flags)
#
#  \author Greg Martinez
#  \date 2015
#
#  \author Ben Farmer
#          (b.farmer@imperial.ac.uk)
#  \date 2018 Oct
#
#*********************************************
import re
import os
import yaml
import shutil
import itertools
import datetime
import sys
import getopt

toolsfile="./Utils/scripts/harvesting_tools.py"
exec(compile(open(toolsfile, "rb").read(), toolsfile, 'exec')) # Python 2/3 compatible version of 'execfile'

# Updater program
def main(argv):

    exclude_plugins=set([])
    plugins = []
    static_links = ""
    flag = {"missing": "0", "found": "1", "excluded": "2"}

    # Handle command line options
    verbose = False
    try:
        build_dir = argv[0]
        opts, args = getopt.getopt(argv[1:],"vx:",["verbose","exclude-scanners="])
    except getopt.GetoptError:
        print( 'Usage: scanner+_harvester.py build_dir [flags]' )
        print( ' flags:' )
        print( '        -v                       : More verbose output' )
        print( '        -x scanner1,scanner2,... : Exclude scanner1, scanner2, etc.' )
        sys.exit(2)
    for opt, arg in opts:
        if opt in ('-v','--verbose'):
            verbose = True
            print('scanner+_harvester.py: verbose=True')
        elif opt in ('-x','--exclude-plugins','--exclude-plugin'):
            exclude_plugins.update(neatsplit(",",arg))
    # info for the different plugin types
    src_paths = sorted(["./ScannerBit/src/scanners", "./ScannerBit/src/objectives"])#, "./ScannerBit/src/interps"])
    inc_paths = sorted(["./ScannerBit/include/gambit/ScannerBit/scanners", "./ScannerBit/include/gambit/ScannerBit/objectives"])#, "./ScannerBit/include/gambit/ScannerBit/interps"])
    plug_type = sorted(["scanner", "objective"]) #, "interp"])
    config_files = []
    for ptype in plug_type:
        config_files += ["./config/" + ptype + "_locations.yaml"]

    # these map the linking flags and library paths to the appropriate plugin library
    scanbit_plugins = dict()
    scanbit_incs = dict()
    scanbit_libs = dict()
    scanbit_links = dict()
    scanbit_reqs = dict()
    scanbit_auto_libs = dict()
    scanbit_auto_incs = dict()
    scanbit_link_libs = dict()
    scanbit_lib_hints = dict()
    scanbit_inc_files = dict()
    scanbit_flags = dict()
    scanbit_cxx_flags = dict()
    #scanbit_static_links = dict()

    ## begin adding scannerbit files to CMakeLists.txt ##
    scanbit_srcs = [ name for name in os.listdir("./ScannerBit/src") if os.path.isfile('./ScannerBit/src/' + name) if name.endswith(".cpp") or name.endswith(".c") or name.endswith(".cc") or name.endswith(".cxx") ]
    scanbit_hdrs = [ name for name in os.listdir("./ScannerBit/include/gambit/ScannerBit") if os.path.isfile('./ScannerBit/include/gambit/ScannerBit/' + name) if name.endswith(".hpp") or name.endswith(".h") ]
    prior_srcs = []
    prior_hdrs = []

    if os.path.exists("./ScannerBit/src/priors"):
                 prior_srcs = [ root + "/" + f for root,dirs,files in os.walk("./ScannerBit/src/priors") for f in files if f.endswith(".cpp") or f.endswith(".c") or f.endswith(".cc") or f.endswith(".cxx") ]
    if os.path.exists("./ScannerBit/include/gambit/ScannerBit/priors"):
                 prior_hdrs = [ root + "/" + f for root,dirs,files in os.walk("./ScannerBit/include/gambit/ScannerBit/priors") for f in files if f.endswith(".hpp") or f.endswith(".h") ]

    cmakelist_txt_out = """
set( scannerbit_sources"""
    for source in sorted(scanbit_srcs):
        cmakelist_txt_out += """
                src/{0}""".format(source)
    for source in sorted(prior_srcs):
        cmakelist_txt_out += """
                src/{0}""".format(source.split('/ScannerBit/src/')[1])
    cmakelist_txt_out += """
)
"""

    cmakelist_txt_out += """
set( scannerbit_headers"""
    for header in sorted(scanbit_hdrs):
        cmakelist_txt_out += """
                include/gambit/ScannerBit/{0}""".format(header)
    for header in sorted(prior_hdrs):
        cmakelist_txt_out += """
                include/gambit/ScannerBit/{0}""".format(header.split('/ScannerBit/include/gambit/ScannerBit/')[1])
    cmakelist_txt_out += """
)

add_gambit_library( ScannerBit OPTION OBJECT SOURCES ${scannerbit_sources} HEADERS ${scannerbit_headers} )
if(${CMAKE_VERSION} VERSION_GREATER 2.8.10)
    target_include_directories( ScannerBit PUBLIC ${EIGEN3_INCLUDE_DIR})
endif()
"""
    ## end adding scannerbit files to CMakeLists.txt ##

    ## begin adding scanlibs to CMakeLists.txt ##
    scan_helper_srcs = []
    scan_helper_hdrs = []

    if os.path.exists("./ScannerBit/src/scanlibs"):
                 scan_helper_srcs = [ root + "/" + f for root,dirs,files in os.walk("./ScannerBit/src/scanlibs") for f in files if f.endswith(".cpp") or f.endswith(".c") or f.endswith(".cc") or f.endswith(".cxx") ]

    if os.path.exists("./ScannerBit/include/gambit/ScannerBit/scanlibs"):
                 scan_helper_hdrs = [ root + "/" + f for root,dirs,files in os.walk("./ScannerBit/include/gambit/ScannerBit/scanlibs") for f in files if f.endswith(".hpp") or f.endswith(".h") ]

    cmakelist_txt_out += """
set( scanner_scanlibs_sources"""
    for source in sorted(scan_helper_srcs):
        cmakelist_txt_out += """
                src/{0}""".format(source.split('/ScannerBit/src/')[1])
    cmakelist_txt_out += """
)
"""

    cmakelist_txt_out += """
set( scanner_scanlibs_headers"""
    for header in sorted(scan_helper_hdrs):
        cmakelist_txt_out += """
                include/gambit/ScannerBit/{0}""".format(header.split('/ScannerBit/include/gambit/ScannerBit/')[1])
    cmakelist_txt_out += """
)
"""
    ## end adding scanlibs to CMakeLists.txt ##

    # loop through the different plugin types
    for i in range(len(plug_type)):
        scanbit_plugins[plug_type[i]] = dict()
        scanbit_incs[plug_type[i]] = dict()
        scanbit_libs[plug_type[i]] = dict()
        scanbit_links[plug_type[i]] = dict()
        scanbit_reqs[plug_type[i]] = dict()
        scanbit_auto_libs[plug_type[i]] = dict()
        scanbit_auto_incs[plug_type[i]] = dict()
        scanbit_link_libs[plug_type[i]] = dict()
        scanbit_lib_hints[plug_type[i]] = dict()
        scanbit_inc_files[plug_type[i]] = dict()
        scanbit_flags[plug_type[i]] = dict()
        scanbit_cxx_flags[plug_type[i]] = dict()
        #scanbit_static_links[plug_type[i]] = dict()

    # loop through the different plugin types
    for i in range(len(plug_type)):
        scanbit_plugins[plug_type[i]] = dict()
        #scanbit_static_links[plug_type[i]] = dict()
        directories = [ name for name in os.listdir(src_paths[i]) if os.path.isdir(src_paths[i] + "/" + name) ]

        for directory in sorted(directories):
            scanbit_plugins[plug_type[i]][directory] = []
            exclude_list = []
            cmakelist_txt_out_tmp = ""
            # Find all source files in the ScannerBit scanner and test_function plugin directories
            sources = [ root + "/" + f for root,dirs,files in os.walk(src_paths[i] + "/" + directory) for f in files if f.endswith(".cpp") or f.endswith(".c") or f.endswith(".cc") or f.endswith(".cxx") ]
            headers = []
            if os.path.exists(inc_paths[i] + "/" + directory):
                 headers = [ root + "/" + f for root,dirs,files in os.walk(inc_paths[i] + "/" + directory) for f in files if f.endswith(".hpp") or f.endswith(".h") ]

            # Work through the source files to find all plugins that need external linkage
            for source in sorted(sources):
                with open(source) as f:
                    last_plugin = ""
                    last_version= ""
                    last_plugin_file=[]
                    processed = False
                    if verbose: print("  Scanning source file {0} for ScannerBit plugin declarations.".format(source))
                    text = comment_remover(f.read())
                    it = re.finditer(r'\breqd_inifile_entries\s*?\(.*?\)|\bREQD_INIFILE_ENTRIES\s*?\(.*?\)', text, re.DOTALL)
                    ini_finds = [[m.span()[0], -1, re.sub(r'\s', '', m.group())] for m in it]
                    #it = re.finditer(r'\binterp_plugin\s*?\(.*?\)\s*?\{|\bINTERP_PLUGIN\s*?\(.*?\)\s*?\{', text, re.DOTALL)
                    #interp_finds = [[m.span()[0], 0, m.group()] for m in it]
                    it = re.finditer(r'\bobjective_plugin\s*?\(.*?\)\s*?\{|\bOBJECTIVE_PLUGIN\s*?\(.*?\)\s*?\{', text, re.DOTALL)
                    obj_finds = [[m.span()[0], 0, m.group()] for m in it]
                    it = re.finditer(r'\bscanner_plugin\s*?\(.*?\)\s*?\{|\bSCANNER_PLUGIN\s*?\(.*?\)\s*?\{', text, re.DOTALL)
                    scan_finds = [[m.span()[0], 1, m.group()] for m in it]
                    it = re.finditer(r'\breqd_libraries\s*?\(.*?\)|\bREQD_LIBRARIES\s*?\(.*?\)', text, re.DOTALL)
                    lib_finds = [[m.span()[0], -2, re.sub(r'\s', '', m.group())] for m in it]
                    it = re.finditer(r'\breqd_headers\s*?\(.*?\)|\bREQD_HEADERS\s*?\(.*?\)', text, re.DOTALL)
                    inc_finds = [[m.span()[0], -3, re.sub(r'\s', '', m.group())] for m in it]
                    it = re.finditer(r'\bset_flag\s*?\(.*?\)|\bSET_FLAG\s*?\(.*?\)', text, re.DOTALL)
                    flag_finds = [[m.span()[0], -4, re.sub(r'\s', '', m.group())] for m in it]
                    it = re.finditer(r'\bcxx_flags\s*?\(.*?\)|\bCXX_FLAGS\s*?\(.*?\)', text, re.DOTALL)
                    cxx_finds = [[m.span()[0], -5, re.sub(r'\s|"', '', m.group())] for m in it]
                    all_finds  = sorted(scan_finds + obj_finds + ini_finds + lib_finds + inc_finds + flag_finds + cxx_finds) # + interp_finds 
                    for find in all_finds:
                        if find[1] >= 0:
                            processed = False
                            splitline = neatsplit(r'\(|\)|,|\s|\{',find[2])
                            if len(splitline) != 0:
                                plugin_name = splitline[1]
                                mod_version = ["0","0","0",""]
                                plugin_type = plug_type[find[1]];
                                if splitline[2] == "version": mod_version[0:len(splitline[3:])] = splitline[3:]
                                token = plugin_name+"__t__"+plugin_type+"__v__"+"_".join([x for x in mod_version])
                                status = "ok"
                                for x in exclude_plugins:
                                    if (plugin_name+"_"+"_".join([y for y in mod_version])).startswith(x):
                                        status = "excluded"

                                last_plugin_file=[plugin_name, plugin_type, mod_version, status, token, [], directory, plug_type[i]]
                                scanbit_plugins[plug_type[i]][directory] += [last_plugin_file]

                                last_plugin = plugin_name

                                last_version = mod_version[0]
                                if mod_version[1] != "": last_version += "." + mod_version[1]
                                if mod_version[2] != "": last_version += "." + mod_version[2]
                                if mod_version[3] != "": last_version += "-" + mod_version[3]

                        elif find[1] == -1:
                            if not last_plugin in scanbit_reqs[plug_type[i]]:
                                scanbit_reqs[plug_type[i]][last_plugin] = dict()
                            if last_version in scanbit_reqs[plug_type[i]][last_plugin]:
                                if scanbit_reqs[plug_type[i]][last_plugin][last_version][0] == "":
                                    scanbit_reqs[plug_type[i]][last_plugin][last_version][0] = find[2][21:-1]
                                else:
                                    scanbit_reqs[plug_type[i]][last_plugin][last_version][0] += "," + find[2][21:-1]
                            else:
                                scanbit_reqs[plug_type[i]][last_plugin][last_version] = [find[2][21:-1], "", "", [], [], [], []]

                        elif find[1] == -2:
                            if not directory in scanbit_auto_libs[plug_type[i]]:
                                scanbit_auto_libs[plug_type[i]][directory] = neatsplit(',|\"', find[2][15:-1])
                            else:
                                scanbit_auto_libs[plug_type[i]][directory] += neatsplit(',|\"', find[2][15:-1])

                            if not last_plugin in scanbit_reqs[plug_type[i]]:
                                scanbit_reqs[plug_type[i]][last_plugin] = dict()
                            if last_version in scanbit_reqs[plug_type[i]][last_plugin]:
                                if scanbit_reqs[plug_type[i]][last_plugin][last_version][1] == "":
                                    scanbit_reqs[plug_type[i]][last_plugin][last_version][1] = find[2][15:-1]
                                else:
                                    scanbit_reqs[plug_type[i]][last_plugin][last_version][1] += "," + find[2][15:-1]
                            else:
                                scanbit_reqs[plug_type[i]][last_plugin][last_version] = ["", find[2][15:-1], "", [], [], [], []]

                            if (not processed) and (last_plugin_file[3] != "excluded"):
                                last_plugin_file[3] = "link_needed"
                                processed = True
                                plugins += [last_plugin_file]

                        elif find[1] == -3:
                            if not directory in scanbit_auto_incs[plug_type[i]]:
                                scanbit_auto_incs[plug_type[i]][directory] = neatsplit(',|\"', find[2][13:-1])
                            else:
                                scanbit_auto_incs[plug_type[i]][directory] += neatsplit(',|\"', find[2][13:-1])

                            if not last_plugin in scanbit_reqs[plug_type[i]]:
                                scanbit_reqs[plug_type[i]][last_plugin] = dict()
                            if last_version in scanbit_reqs[plug_type[i]][last_plugin]:
                                if scanbit_reqs[plug_type[i]][last_plugin][last_version][2] == "":
                                    scanbit_reqs[plug_type[i]][last_plugin][last_version][2] = find[2][13:-1]
                                else:
                                    scanbit_reqs[plug_type[i]][last_plugin][last_version][2] += "," + find[2][13:-1]
                            else:
                                scanbit_reqs[plug_type[i]][last_plugin][last_version] = ["", "", find[2][13:-1], [], [], [], []]

                            if (not processed) and (last_plugin_file[3] != "excluded"):
                                processed = True
                                plugins += [last_plugin_file]

                        elif find[1] == -4:
                            flags = neatsplit(",", find[2][9:-1]);
                            if len(flags) > 0:
                                if not last_plugin in scanbit_flags[plug_type[i]]:
                                    scanbit_flags[plug_type[i]][last_plugin] = dict()
                                if not last_version in scanbit_flags[plug_type[i]][last_plugin]:
                                    scanbit_flags[plug_type[i]][last_plugin][last_version] = dict()
                                    scanbit_flags[plug_type[i]][last_plugin][last_version][flags[0]] = []
                                scanbit_flags[plug_type[i]][last_plugin][last_version][flags[0]] += flags[1:]

                        elif find[1] == -5:
                            flags = neatsplit(",", find[2][10:-1]);
                            if len(flags) > 0:
                                if not directory in scanbit_cxx_flags[plug_type[i]]:
                                    scanbit_cxx_flags[plug_type[i]][directory] = []
                                scanbit_cxx_flags[plug_type[i]][directory] += flags

                # Add plugin source files to CMakeLists.txt.  Only add those for non-excluded plugins.
                # bjf> added "!=[]" to the conditional due to error during cmake. Hope it makes sense.
                if(last_plugin_file!=[] and last_plugin_file[3] == "excluded"):
                    exclude_list += [last_plugin_file[0]+" "+".".join([y for y in last_plugin_file[2] if y != ""])]
                else:
                    cmakelist_txt_out_tmp += """
                src/{0}""".format(source.split('/ScannerBit/src/')[1])

            # Add entries for this plugin only if there are non-excluded sources found.
            if (cmakelist_txt_out_tmp != ""):
              # First do the sources
              cmakelist_txt_out += """
set( {0}_plugin_sources_{1}{2}
)
""".format(plug_type[i], directory, cmakelist_txt_out_tmp)
              # Now do the headers
              cmakelist_txt_out += """
set( {0}_plugin_headers_{1}""".format(plug_type[i], directory)
              for header in sorted(headers):
                  cmakelist_txt_out += """
                include/gambit/ScannerBit/{0}""".format(header.split('/ScannerBit/include/gambit/ScannerBit/')[1])
              cmakelist_txt_out += """
)
"""
            # Otherwise notify that the plugin is ditched.
            else:
              for x in exclude_list:
                cmakelist_txt_out += """
message(\"${{BoldCyan}} X Excluding {0} from ScannerBit configuration.${{ColourReset}}\")
""".format(x)

    # Loop over all plugin types
    for config_file, plugin_type in zip(config_files, plug_type):

        # Check for the user-defined version of the location file.
        location_files = []
        if os.path.isfile(config_file):
            location_files += [config_file]

        # Now make sure the default version of the locations yaml file is present.
        if not os.path.isfile(config_file+".default"):
            print("ERROR: "+config_file+".default not found!")
            sys.exit(2)
        location_files += [config_file+".default"]

        # Loop over all the plugins of this type
        for plugin in plugins:

            plugin_name = plugin[0]
            inc_commands = []
            auto_libs = []
            auto_incs = []
            linkcommands = ""
            linklibs = []
            #staticlinkcommands = ""
            linkdirs = []
            linkhints = []
            inc_files = []
            detected_plugins = [("none","none")]

            # Loop over the found yaml location files
            for current_location_file in location_files:

                # Load the locations yaml file, and work out which libs are present
                yaml_loader = yaml.full_load if hasattr(yaml, 'full_load') else yaml.load
                yaml_file = yaml_loader(open(current_location_file))

                if yaml_file:
                    if plugin_name in yaml_file and plugin[1] == plugin_type:
                        version_bits = plugin[2]
                        maj_version = int(".".join([x for x in version_bits[0:1]]))
                        min_version = float(".".join([x for x in version_bits[0:2]]))
                        pat_version = ".".join([x for x in version_bits[0:3]])
                        ful_version = "-".join([pat_version, version_bits[3]])
                        version = ".".join([x for x in version_bits[0:3]])
                        if (version_bits[3] != ""):
                            version = "-".join([version, version_bits[3]])
                        ini_version = ""
                        if ful_version in yaml_file[plugin_name]:
                            ini_version = ful_version
                        elif pat_version in yaml_file[plugin_name]:
                            ini_version = pat_version
                        elif min_version in yaml_file[plugin_name]:
                            ini_version = min_version
                        elif maj_version in yaml_file[plugin_name]:
                            ini_version = maj_version
                        elif "any_version" in yaml_file[plugin_name]:
                            ini_version = "any_version"

                        if ini_version != "" and (plugin_name, ini_version) not in detected_plugins:
                            detected_plugins += [(plugin_name, ini_version)]
                            options_list = yaml_file[plugin_name][ini_version]
                            if type(options_list) is dict: #not list:
                                options_list = [options_list,]
                            for f in options_list:
                                if type(f) is dict:
                                    for key, value in f.items():
                                        if key in ("lib", "libs", "library", "libraries", "library_path", "library_paths", "-lib", "-libs", "-library", "-libraries", "-library_path", "-library_paths"):
                                            libs = neatsplit(',|\\s|;', value)
                                            for lib in libs:
                                                if os.path.isfile(lib):
                                                    lib_full = os.path.abspath(lib)
                                                    print("   Found library {0} needed for ScannerBit plugin {1} v{2}".format(lib,plugin_name,version))
                                                    if lib_full.endswith(".a"):
                                                        static_links += lib_full + " "
                                                        [libdir, lib] = os.path.split(lib_full)
                                                        lib = re.sub(r"^lib|\..*$","",lib)
                                                        #staticlinkcommands += "-L" + libdir + " -l" + lib + " "
                                                    else:
                                                        [libdir, lib] = os.path.split(lib_full)
                                                        lib = re.sub(r"^lib|\..*$","",lib)
                                                        linkcommands += "-L" + libdir + " -l" + lib + " "
                                                        linkdirs += [libdir]

                                                    linklibs += [[lib, lib_full]]
                                                    scanbit_reqs[plugin[7]][plugin_name][version][3] += [lib]
                                                elif os.path.isdir(lib):
                                                    lib = os.path.abspath(lib)
                                                    print("   Found library path {0} needed for ScannerBit plugin {1} v{2}".format(lib,plugin_name,version))
                                                    linkhints += [lib]
                                                elif lib == "ROOT" or lib == "GSL":
                                                    auto_libs += [lib]
                                                    #scanbit_reqs[plugin[7]][plugin_name][version][3] += [lib]
                                                    if scanbit_reqs[plugin[7]][plugin_name][version][1] == "":
                                                        scanbit_reqs[plugin[7]][plugin_name][version][1] = "\"" + lib + "\""
                                                    else:
                                                        scanbit_reqs[plugin[7]][plugin_name][version][1] += ",\"" + lib + "\""
                                                else:
                                                    [libdir, lib] = os.path.split(lib)
                                                    #lib = re.sub("^lib|\..*$","",lib)
                                                    lib = "\"" + lib + "\""
                                                    scanbit_reqs[plugin[7]][plugin_name][version][4] += [lib]

                                        elif key in ("inc", "incs", "include", "includes", "include_path", "include_paths", "-inc", "-incs", "-include", "-includes", "-include_path", "-include_paths", "hdr", "hdrs", "header", "headers", "-hdr", "-hdrs", "-header", "-headers"):
                                            incs = neatsplit(',|\\s|;', value)
                                            for inc in incs:
                                                if os.path.isdir(inc):
                                                    inc = os.path.abspath(inc)
                                                    print("   Found include path {0} needed for ScannerBit plugin {1} v{2}".format(inc,plugin_name,version))
                                                    inc_commands += [inc]
                                                    scanbit_reqs[plugin[7]][plugin_name][version][5] += [inc]
                                                elif os.path.isfile(inc):
                                                    inc = os.path.abspath(inc)
                                                    print("   Found include file {0} needed for ScannerBit plugin {1} v{2}".format(inc,plugin_name,version))
                                                    [incdir, inc] = os.path.split(inc)
                                                    inc_commands += [incdir]
                                                    scanbit_reqs[plugin[7]][plugin_name][version][5] += [incdir]
                                                    inc_files += [[inc, incdir]]
                                                elif inc == "ROOT" or inc == "GSL" or inc == "pybind11" or inc == "Python" or inc == "PYTHONLIBS":
                                                    auto_incs += [inc]
                                                    #scanbit_reqs[plugin[7]][plugin_name][version][5] += [inc]
                                                    if scanbit_reqs[plugin[7]][plugin_name][version][2] == "":
                                                        scanbit_reqs[plugin[7]][plugin_name][version][2] = "\"" + inc + "\""
                                                    else:
                                                        scanbit_reqs[plugin[7]][plugin_name][version][2] += ",\"" + inc + "\""
                                                else:
                                                    plugin[3] = "missing"
                                                    scanbit_reqs[plugin[7]][plugin_name][version][6] += [inc]
                                        else:
                                            print("   Unknown infile option \"{0}\" needed for ScannerBit plugin {1} v{2}".format(key,plugin_name,version))
                                else:
                                    print("   Unknown YAML format in file {0}.".format(currrent_location_file))

                            # add links commands to map (keys: {plug_type, directory}) to be linked to later
                            #if staticlinkcommands != "":
                            #    if plugin[6] in scanbit_static_links[plugin[7]]:
                            #        scanbit_static_links[plugin[7]][plugin[6]] += staticlinkcommands
                            #    else:
                            #        scanbit_static_links[plugin[7]][plugin[6]] = staticlinkcommands
                            if inc_commands != []:
                                if plugin[6] in scanbit_incs[plugin[7]]:
                                    scanbit_incs[plugin[7]][plugin[6]] += inc_commands
                                else:
                                    scanbit_incs[plugin[7]][plugin[6]] = inc_commands
                            if linkcommands != "":
                                if plugin[6] in scanbit_links[plugin[7]]:
                                    scanbit_links[plugin[7]][plugin[6]] += linkcommands
                                else:
                                    scanbit_links[plugin[7]][plugin[6]] = linkcommands
                            if linkdirs != []:
                                if plugin[6] in scanbit_libs[plugin[7]]:
                                    scanbit_libs[plugin[7]][plugin[6]] += linkdirs
                                else:
                                    scanbit_libs[plugin[7]][plugin[6]] = linkdirs
                            if auto_libs != []:
                                if plugin[6] in scanbit_auto_libs[plugin[7]]:
                                    scanbit_auto_libs[plugin[7]][plugin[6]] += auto_libs
                                else:
                                    scanbit_auto_libs[plugin[7]][plugin[6]] = auto_libs
                            if auto_incs != []:
                                if plugin[6] in scanbit_auto_incs[plugin[7]]:
                                    scanbit_auto_incs[plugin[7]][plugin[6]] += auto_incs
                                else:
                                    scanbit_auto_incs[plugin[7]][plugin[6]] = auto_incs
                            if linklibs != []:
                                if plugin[6] in scanbit_link_libs[plugin[7]]:
                                    scanbit_link_libs[plugin[7]][plugin[6]] += linklibs
                                else:
                                    scanbit_link_libs[plugin[7]][plugin[6]] = linklibs
                            if linkhints != []:
                                if plugin[6] in scanbit_lib_hints[plugin[7]]:
                                    scanbit_lib_hints[plugin[7]][plugin[6]] += linkhints
                                else:
                                    scanbit_lib_hints[plugin[7]][plugin[6]] = linkhints
                            if inc_files != []:
                                if plugin[6] in scanbit_inc_files[plugin[7]]:
                                    scanbit_inc_files[plugin[7]][plugin[6]] += inc_files
                                else:
                                    scanbit_inc_files[plugin[7]][plugin[6]] = inc_files

    # Make a candidate priors_rollcall.hpp file
    towrite = """// GAMBIT: Global and Modular BSM Inference Tool  
//************************************************
/// \\file                                        
///                                               
///  Priors rollcall file for ScannerBit.         
///                                               
///  This file has been automatically generated by
///  scanner+_harvester.py.  Please do not modify.
///                                               
///***********************************************
///                                               
///  Authors:                                     
///                                               
///  \\author The GAMBIT Collaboration            
///  \\date {0}
///                                               
///***********************************************
""".format(datetime.datetime.now().strftime("%I:%M%p on %B %d, %Y"))

    prior_txt_out = """
#ifndef PRIOR_LIST_HPP
#define PRIOR_LIST_HPP
"""
    for header in sorted(prior_hdrs):
        prior_txt_out += """
#include \"gambit/ScannerBit/{0}\"""".format(header.split('/ScannerBit/include/gambit/ScannerBit/')[1])
    prior_txt_out += """

#endif
"""

    towrite += prior_txt_out

    header = "./ScannerBit/include/gambit/ScannerBit/priors_rollcall.hpp"
    candidate = build_dir+"/priors_rollcall.hpp.candidate"
    with open(candidate,"w") as f: f.write(towrite)
    update_only_if_different(header, candidate)

    if verbose: print("Finished writing ScannerBit/include/gambit/ScannerBit/priors_rollcall.hpp")

    # Make a candidate ScannerBit CMakelists.txt file

    library_names = []

    towrite = """# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \\file
#
#  Cmake CMakeLists.txt file for ScannerBit.
#
#  This file has been automatically generated by
#  scanner+_harvester.py.  Please do not modify.
#
#************************************************
#
#  Authors:
#
#  \\author The GAMBIT Collaboration
#  \\date {0}
#
#************************************************
""".format(datetime.datetime.now().strftime("%I:%M%p on %B %d, %Y"))

    towrite += cmakelist_txt_out
    towrite += """
# Add the ScannerBit linking flag utility
add_executable(scanlibs ${scanner_scanlibs_sources} ${scanner_scanlibs_headers})
if(${CMAKE_VERSION} VERSION_GREATER 2.8.10)
    target_include_directories(scanlibs PUBLIC ${PROJECT_SOURCE_DIR}/cmake/include)
else()
    include_directories(${PROJECT_SOURCE_DIR}/cmake/include)
endif()
add_dependencies(scanlibs yaml-cpp)
target_link_libraries(scanlibs yaml-cpp)
set_target_properties(scanlibs PROPERTIES RUNTIME_OUTPUT_DIRECTORY \"${PROJECT_SOURCE_DIR}/ScannerBit/bin\")

# Specify known plugin include paths
set( PLUGIN_INCLUDE_DIRECTORIES
                ${PROJECT_BINARY_DIR}
                ${PROJECT_BINARY_DIR}/cmake
                ${GAMBIT_INCDIRS}
                ${mkpath_INCLUDE_DIR}
                ${yaml_INCLUDE_DIR}
                ${Boost_INCLUDE_DIR}
                ${GSL_INCLUDE_DIRS}
                ${ROOT_INCLUDE_DIR}
                ${ROOT_INCLUDE_DIRS}
                ${EIGEN3_INCLUDE_DIR}
                ${BREW_LIBOMP_PREFIX}/include
                ${PROJECT_SOURCE_DIR}/ScannerBit/include/gambit/ScannerBit
)

if( ${PLUG_VERBOSE} )
    message(\"*** begin PLUG_INCLUDE_DIRECTORIES ***\")
    foreach(dir ${PLUGIN_INCLUDE_DIRECTORIES})
        message(STATUS \"dir='${dir}'\")
    endforeach()
    message(\"*** end PLUG_INCLUDE_DIRECTORIES ***\")
endif()

set( reqd_lib_output )
set( exclude_lib_output )
set( PLUGIN_COMPILE_FLAGS \"${BACKEND_CXX_FLAGS} ${OpenMP_CXX_FLAGS}\")

if(MPI_C_FOUND)
    set( PLUGIN_COMPILE_FLAGS \"${PLUGIN_COMPILE_FLAGS} ${MPI_C_COMPILE_FLAGS}\" )
    set( PLUGIN_COMPILE_DIRECTORIES
                ${PLUGIN_COMPILE_DIRECTORIES}
                ${MPI_C_COMPILE_PATH}
    )
    set( PLUGIN_INCLUDE_DIRECTORIES
                ${PLUGIN_INCLUDE_DIRECTORIES}
                ${MPI_C_INCLUDE_PATH}
    )
endif()

if(MPI_CXX_FOUND)
    set( PLUGIN_COMPILE_FLAGS \"${PLUGIN_COMPILE_FLAGS} ${MPI_CXX_COMPILE_FLAGS}\" )
    set( PLUGIN_COMPILE_DIRECTORIES
                ${PLUGIN_COMPILE_DIRECTORIES}
                ${MPI_CXX_COMPILE_PATH}
    )
    set( PLUGIN_INCLUDE_DIRECTORIES
                ${PLUGIN_INCLUDE_DIRECTORIES}
                ${MPI_CXX_INCLUDE_PATH}
    )
endif()
"""

    # now link the shared libraries to their respective plugin libraries
    for i in range(len(plug_type)):
        directories = [ name for name in os.listdir(src_paths[i]) if os.path.isdir(src_paths[i] + "/" + name) ]
        for directory in sorted(directories):
            library_names.append("lib" + plug_type[i] + "_" + directory + ".so")

            towrite += """
#################### lib{0}_{1}.so ####################

set ({0}_ok_flag_{1} \"\")

set ({0}_compile_flags_{1} \"${{PLUGIN_COMPILE_FLAGS}}""".format(plug_type[i], directory)
            if plug_type[i] in scanbit_cxx_flags:
                if directory in scanbit_cxx_flags[plug_type[i]]:
                    towrite += """ {0}""".format(" ".join(scanbit_cxx_flags[plug_type[i]][directory]))
            towrite += """\")
"""

            for plug in scanbit_plugins[plug_type[i]][directory]:
                if plug[3] == "excluded":
                    towrite += """
set ({0}_ok_flag_{1} \"\\n    - user excluded plugin: \\\"{2}\\\"\")
""".format(plug_type[i], directory, plug[4].split("__t__")[0])
                    if verbose: print("excluding ", plug[4])
                
            towrite += """
set ({0}_plugin_libraries_{1}""".format(plug_type[i], directory)
            if plug_type[i] in scanbit_libs:
                if directory in scanbit_libs[plug_type[i]]:
                    towrite += """ 
                \"{0}\"""".format(scanbit_links[plug_type[i]][directory])
            towrite += """
)
"""

            towrite += """
set ({0}_plugin_lib_paths_{1}""".format(plug_type[i], directory)
            if plug_type[i] in scanbit_lib_hints:
                if directory in scanbit_lib_hints[plug_type[i]]:
                    for lib in scanbit_lib_hints[plug_type[i]][directory]:
                        towrite += """
                {0}""".format(lib)
            towrite += """
)
"""

            towrite += """
if (${{CMAKE_SYSTEM_NAME}} MATCHES \"Darwin\")""".format()
            if plug_type[i] in scanbit_link_libs:
                if directory in scanbit_link_libs[plug_type[i]]:
                    unique_libdirs = set(p[1] for p in scanbit_link_libs[plug_type[i]][directory])
                    if unique_libdirs:
                        for libdir in unique_libdirs:
                            towrite += """
    execute_process(RESULT_VARIABLE result 
                    COMMAND ${{CMAKE_INSTALL_NAME_TOOL}} -id \"{0}\" {1} 
                    WORKING_DIRECTORY ${{PROJECT_SOURCE_DIR}}
    )
    """.format("@rpath/" + libdir.split("/")[-1], libdir)
            towrite += """
    set ({0}_plugin_rpath_{1}""".format(plug_type[i], directory)
            if plug_type[i] in scanbit_libs:
                if directory in scanbit_libs[plug_type[i]]:
                    unique_libdirs = set(p for p in scanbit_libs[plug_type[i]][directory])
                    if unique_libdirs:
                        for libdir in unique_libdirs:
                            towrite += """
                @loader_path/../../ScannerBit/{0}""".format(libdir.split("ScannerBit/")[-1])
            towrite += """
    )
else()
    set ({0}_plugin_rpath_{1}""".format(plug_type[i], directory)
            if plug_type[i] in scanbit_libs:
                if directory in scanbit_libs[plug_type[i]]:
                    unique_libdirs = set(p for p in scanbit_libs[plug_type[i]][directory])
                    if unique_libdirs:
                        for libdir in unique_libdirs:
                            towrite += """
                $ORIGIN/../../ScannerBit/{0}""".format(libdir.split("ScannerBit/")[-1])
            towrite += """
    )
endif()
"""
# NOTE: may need to add the flag -Wl,-z,origin for linux for ORIGIN to work.

            towrite += """
set ({0}_plugin_includes_{1}
                ${{PLUGIN_INCLUDE_DIRECTORIES}}
                ${{CMAKE_CURRENT_SOURCE_DIR}}/include/gambit/ScannerBit/{0}s/{1}""".format(plug_type[i], directory)
            if plug_type[i] in scanbit_incs:
                if directory in scanbit_incs[plug_type[i]]:
                    for inc in scanbit_incs[plug_type[i]][directory]:
                        towrite += """
                {0}""".format(inc)
            towrite += """
)
"""

            towrite += """
set ({0}_plugin_linked_libs_{1} \"\")
""".format(plug_type[i], directory)
            if plug_type[i] in scanbit_link_libs:
                if directory in scanbit_link_libs[plug_type[i]]:
                    for lib in scanbit_link_libs[plug_type[i]][directory]:
                        towrite += """
set ({0}_plugin_linked_libs_{1} \"${{{0}_plugin_linked_libs_{1}}}    {2}: {3}\\n\")
""".format(plug_type[i], directory, lib[0], lib[1])
            towrite += """
set ({0}_plugin_lib_full_paths_{1}""".format(plug_type[i], directory)
            if plug_type[i] in scanbit_link_libs:
                if directory in scanbit_link_libs[plug_type[i]]:
                    for lib in scanbit_link_libs[plug_type[i]][directory]:
                        towrite += """
                {0}""".format(lib[1])
            towrite += """
)
"""

            towrite += """
set ({0}_plugin_found_incs_{1} \"\")
""".format(plug_type[i], directory)
            if plug_type[i] in scanbit_incs:
                if directory in scanbit_incs[plug_type[i]]:
                    for inc in scanbit_incs[plug_type[i]][directory]:
                        towrite += """
set ({0}_plugin_found_incs_{1} \"${{{0}_plugin_found_incs_{1}}}    \\\"{0}_locations.yaml\\\": {2}\\n\")
""".format(plug_type[i], directory, inc)
            if plug_type[i] in scanbit_inc_files:
                if directory in scanbit_inc_files[plug_type[i]]:
                    for inc in scanbit_inc_files[plug_type[i]][directory]:
                        towrite += """
set ({0}_plugin_found_incs_{1} \"${{{0}_plugin_found_incs_{1}}}    \\\"{2}\\\": {3}\\n\")
""".format(plug_type[i], directory, inc[0], inc[1])

            towrite += "\n"

            if plug_type[i] in scanbit_auto_libs:
                if directory in scanbit_auto_libs[plug_type[i]]:
                    if plug_type[i] in scanbit_link_libs:
                        if directory in scanbit_link_libs[plug_type[i]]:
                            temp = [p[0] for p in scanbit_link_libs[plug_type[i]][directory]]
                            scanbit_auto_libs[plug_type[i]][directory] = set(lib for lib in scanbit_auto_libs[plug_type[i]][directory] if not lib in temp);

                    temp = set(lib for lib in scanbit_auto_libs[plug_type[i]][directory])
                    for lib in temp:
                        if lib == "ROOT":
                            towrite += """
if ({2}_FOUND)
    foreach ({2}_LIB ${{{2}_LIBRARIES}})
        get_filename_component(lib_path ${{{2}_LIB}} PATH)
        get_filename_component(lib_name ${{{2}_LIB}} NAME_WE)
        string (REGEX REPLACE \"^lib\" \"\" lib_name ${{lib_name}})
        set ({0}_plugin_libraries_{1} \"${{{0}_plugin_libraries_{1}}} -L${{lib_path}} -l${{lib_name}}\")
        set ({0}_plugin_lib_full_paths_{1} ${{{0}_plugin_lib_full_paths_{1}}} ${{{2}_LIBRARIES}})
        set ({0}_plugin_linked_libs_{1} \"${{{0}_plugin_linked_libs_{1}}}    {2}: ${{2}_LIB}\\n\")
    endforeach()
    set ({0}_plugin_rpath_{1} \"${{{0}_plugin_rpath_{1}}};${{{2}_LIBRARY_DIR}}\")
endif()
""".format(plug_type[i], directory, lib)
                        else:
                            towrite += """
unset({0}_{1}_{2}_LIBRARY CACHE)
find_library( {0}_{1}_{2}_LIBRARY {2} HINTS ${{{0}_plugin_lib_paths_{1}}} )
if( {0}_{1}_{2}_LIBRARY STREQUAL \"{0}_{1}_{2}_LIBRARY-NOTFOUND\" )
    message(\"-- Did not find {0} library {2} for {1}. Disabling scanners that depend on this.\")
    # next line will exclude plugins if no lib found.  Note that if you un-comment this line
    # all plugins plugins defined in this library will be excluded.
    # set ({0}_ok_flag_{1} \"${{{0}_ok_flag_{1}}} \\n    - library missing: \\\"lib{2}.so\\\"\")
else()
    get_filename_component(lib_path ${{{0}_{1}_{2}_LIBRARY}} PATH)
    get_filename_component(lib_name ${{{0}_{1}_{2}_LIBRARY}} NAME_WE)
    string (REGEX REPLACE \"^lib\" \"\" lib_name ${{lib_name}})
    set ({0}_plugin_libraries_{1} \"${{{0}_plugin_libraries_{1}}} -L${{lib_path}} -l${{lib_name}}\")
    set ({0}_plugin_lib_full_paths_{1} ${{{0}_plugin_lib_full_paths_{1}}} ${{{0}_{1}_{2}_LIBRARY}})
    set ({0}_plugin_rpath_{1} \"${{{0}_plugin_rpath_{1}}};${{lib_path}}\")
    set ({0}_plugin_linked_libs_{1} \"${{{0}_plugin_linked_libs_{1}}}    {2}: ${{{0}_{1}_{2}_LIBRARY}}\\n\")
    message(\"-- Found {0} library: ${{{0}_{1}_{2}_LIBRARY}}\")
endif()
""".format(plug_type[i], directory, lib)

            if plug_type[i] in scanbit_auto_incs:
                if directory in scanbit_auto_incs[plug_type[i]]:
                    if plug_type[i] in scanbit_inc_files:
                        if directory in scanbit_inc_files[plug_type[i]]:
                            temp = [p[0] for p in scanbit_inc_files[plug_type[i]][directory]]
                            scanbit_auto_incs[plug_type[i]][directory] = set(inc for inc in scanbit_auto_incs[plug_type[i]][directory] if not inc in temp);

                    temp = set(inc for inc in scanbit_auto_incs[plug_type[i]][directory])
                    for inc in temp:
                        if inc == "ROOT" or inc == "Python":
                            towrite += """
if ({2}_FOUND)
    set ({0}_plugin_includes_{1}
        ${{{0}_plugin_includes_{1}}}
        ${{{2}_INCLUDE_DIRS}}
    )
    set ({0}_plugin_found_incs_{1} \"${{{0}_plugin_found_incs_{1}}}    \\\"{2}\\\": ${{{2}_INCLUDE_DIRS}}\\n\")
else()
    message(\"-- Did not find {0} header {2}. Disabling scanners that depend on this.\")
    set ({0}_ok_flag_{1} \"${{{0}_ok_flag_{1}}} \\n    - file missing: \\\"{2}\\\"\")
endif()
""".format(plug_type[i], directory, inc)
                        elif inc == "pybind11":
                            towrite += """
if ({2}_FOUND)
    set ({2}_REAL_INCLUDE_DIR ${{{2}_INCLUDE_DIR}} ${{{3}_INCLUDE_DIR}})
    set ({0}_plugin_includes_{1}
        ${{{0}_plugin_includes_{1}}}
        ${{{2}_REAL_INCLUDE_DIR}}
    )
    set ({0}_plugin_found_incs_{1} \"${{{0}_plugin_found_incs_{1}}}    \\\"{2}\\\": ${{{2}_REAL_INCLUDE_DIR}}\\n\")
else()
    message(\"-- Did not find {0} header {2}. Disabling scanners that depend on this.\")
    set ({0}_ok_flag_{1} \"${{{0}_ok_flag_{1}}} \\n    - file missing: \\\"{2}\\\"\")
endif()
""".format(plug_type[i], directory, inc, "PYBIND11")
                        elif inc == "PYTHONLIBS":
                            towrite += """
if ({2}_FOUND)
    set ({0}_plugin_includes_{1}
        ${{{0}_plugin_includes_{1}}}
        ${{{3}_INCLUDE_DIRS}}
    )
    set ({0}_plugin_found_incs_{1} \"${{{0}_plugin_found_incs_{1}}}    \\\"{2}\\\": ${{{3}_INCLUDE_DIRS}}\\n\")
else()
    message(\"-- Did not find {0} header {2}. Disabling scanners that depend on this.\")
    set ({0}_ok_flag_{1} \"${{{0}_ok_flag_{1}}} \\n    - file missing: \\\"{2}\\\"\")
endif()
""".format(plug_type[i], directory, inc, "PYTHON")
                        else:
                            towrite += """
unset({0}_{1}_{3}_INCLUDE_PATH CACHE)
find_path( {0}_{1}_{3}_INCLUDE_PATH \"{2}\" HINTS ${{{0}_plugin_includes_{1}}})
if( NOT {0}_{1}_{3}_INCLUDE_PATH STREQUAL \"{0}_{1}_{3}_INCLUDE_PATH-NOTFOUND\" )
    set ({0}_plugin_includes_{1}
        ${{{0}_plugin_includes_{1}}}
        ${{{0}_{1}_{3}_INCLUDE_PATH}}
    )
    set ({0}_plugin_found_incs_{1} \"${{{0}_plugin_found_incs_{1}}}    \\\"{2}\\\": ${{{0}_{1}_{3}_INCLUDE_PATH}}\\n\")
    message(\"-- Found {0} header: ${{{0}_{1}_{3}_INCLUDE_PATH}}/{2}\")
else()
    message(\"-- Did not find {0} header {2}. Disabling scanners that depend on this.\")
    set ({0}_ok_flag_{1} \"${{{0}_ok_flag_{1}}} \\n    - file missing: \\\"{2}\\\"\")
endif()
""".format(plug_type[i], directory, inc, re.sub(r";|/|\.", "_", inc))

            towrite += """
if( NOT {0}_plugin_linked_libs_{1} STREQUAL \"\" OR NOT {0}_plugin_found_incs_{1} STREQUAL \"\")
    set ( reqd_lib_output \"${{reqd_lib_output}}lib{0}_{1}.so:\\n\" )
    if( NOT {0}_plugin_linked_libs_{1} STREQUAL \"\" )
        set ( reqd_lib_output \"${{reqd_lib_output}}  linked_libs: \\n${{{0}_plugin_linked_libs_{1}}}\")
    endif()
    if( NOT {0}_plugin_found_incs_{1} STREQUAL \"\" )
        set ( reqd_lib_output \"${{reqd_lib_output}}  found_incs: \\n${{{0}_plugin_found_incs_{1}}}\")
    endif()
endif()

if ( {0}_ok_flag_{1} STREQUAL \"\" )
    add_gambit_library( {0}_{1} VISIBLE OPTION SHARED SOURCES ${{{0}_plugin_sources_{1}}} HEADERS ${{{0}_plugin_headers_{1}}} )
    set_target_properties( {0}_{1}
                       PROPERTIES
                       INSTALL_RPATH \"${{{0}_plugin_rpath_{1}}}\"
                       COMPILE_FLAGS \"${{{0}_compile_flags_{1}}}\"
                       INCLUDE_DIRECTORIES \"${{{0}_plugin_includes_{1}}}\"
                       ARCHIVE_OUTPUT_DIRECTORY \"${{CMAKE_CURRENT_SOURCE_DIR}}/lib\"
                       LIBRARY_OUTPUT_DIRECTORY \"${{CMAKE_CURRENT_SOURCE_DIR}}/lib\")
    target_link_libraries( {0}_{1} ${{{0}_plugin_lib_full_paths_{1}}})
    set (SCANNERBIT_PLUGINS ${{SCANNERBIT_PLUGINS}} {0}_{1})
else()
    set ( exclude_lib_output \"${{exclude_lib_output}}lib{0}_{1}.so:\\n  plugins:\\n{2}  reason: ${{{0}_ok_flag_{1}}}\\n\\n\" )
endif()
""".format(plug_type[i], directory, "".join(["    - " + plug[4] + "\\n" for plug in scanbit_plugins[plug_type[i]][directory]]))

    towrite += """
set(SCANNERBIT_PLUGINS ${{SCANNERBIT_PLUGINS}} PARENT_SCOPE)
file( WRITE ${{PROJECT_SOURCE_DIR}}/scratch/build_time/scanbit_excluded_libs.yaml \"${{exclude_lib_output}}\" )
file( WRITE ${{PROJECT_SOURCE_DIR}}/scratch/build_time/scanbit_linked_libs.yaml \"${{reqd_lib_output}}\" )

#################################################################################

foreach (plugin ${{SCANNERBIT_PLUGINS}})
    add_dependencies(ScannerBit ${{plugin}})
endforeach()

option(WITH_PYTHON_SCANNERBIT \"Build ScannerBit's Python interface when building ScannerBit\" OFF)
if(WITH_PYTHON_SCANNERBIT)
    message(\"${{BoldYellow}}-- Enabling the ScannerBit_python_interface build target.${{ColourReset}}")
    add_subdirectory(python) 
else()
    message(\"${{BoldCyan}} X The ScannerBit_python_interface build target is not activated. Use -DWITH_PYTHON_SCANNERBIT=ON to enable it.${{ColourReset}}")
endif()
""".format() # To include scan_python and scan_boost_python targets, for pyScannerBit interface. 

    cmake = "./ScannerBit/CMakeLists.txt"
    candidate = build_dir+"/ScannerBit_CMakeLists.txt.candidate"
    with open(candidate,"w") as f: f.write(towrite)
    update_only_if_different(cmake, candidate)

    towrite = "\n".join(library_names)
    cmake = "./ScannerBit/lib/plugin_libraries.list"
    candidate = build_dir+"/ScannerBit_lib_plugin_libraries.list.candidate"
    with open(candidate,"w") as f: f.write(towrite)
    update_only_if_different(cmake, candidate)

    if verbose: print("Finished writing ScannerBit/CMakeLists.txt")

    # Make a candidate scanbit_reqd_entries.yaml file
    towrite = """# GAMBIT: Global and Modular BSM Inference Tool  
#************************************************
# \\file                                         
#                                                
#  Scanner required arguments for GAMBIT.        
#                                                
#  This file has been automatically generated by 
#  scanner+_harvester.py.  Please do not modify. 
#                                                
#************************************************
#                                                
#  Authors:                                      
#                                                
#  \\author The GAMBIT Collaboration             
#  \\date {0}
#                                                
#************************************************
""".format(datetime.datetime.now().strftime("%I:%M%p on %B %d, %Y"))

    for type_key in scanbit_reqs:
        towrite += """
{0}:""".format(type_key)
        for plug_key in scanbit_reqs[type_key]:
            towrite += """
  {0}:""".format(plug_key)
            for version_key in scanbit_reqs[type_key][plug_key]:
                towrite += """    
    {0}:
      reqd_inifile_entries: [{1}]
      reqd_libraries: [{2}]
      reqd_include_paths: [{3}]
      linked_libraries: [{4}]
      not_linked_libraries: [{5}]
      found_include_paths: [{6}]
      not_found_include_paths: [{7}]
""".format( version_key, 
            scanbit_reqs[type_key][plug_key][version_key][0], 
            scanbit_reqs[type_key][plug_key][version_key][1], 
            scanbit_reqs[type_key][plug_key][version_key][2], 
            ",".join(scanbit_reqs[type_key][plug_key][version_key][3]), 
            ",".join(scanbit_reqs[type_key][plug_key][version_key][4]), 
            ",".join(scanbit_reqs[type_key][plug_key][version_key][5]), 
            ",".join(scanbit_reqs[type_key][plug_key][version_key][6]))

    req_entries = "./scratch/build_time/scanbit_reqd_entries.yaml"
    candidate = build_dir+"/scanbit_reqd_entries.yaml.candidate"
    with open(candidate,"w") as f: f.write(towrite)
    update_only_if_different(req_entries, candidate)

    if verbose: print("Finished writing scratch/build_time/scanbit_reqd_entries.yaml")

    # Make a candidate scanbit_reqd_entries.yaml file
    towrite = """# GAMBIT: Global and Modular BSM Inference Tool  
#************************************************
# \\file                                         
#                                                
#  Scanner flags for GAMBIT.                     
#                                                
#  This file has been automatically generated by 
#  scanner+_harvester.py.  Please do not modify. 
#                                                
#************************************************
#                                                
#  Authors:                                      
#                                                
#  \\author The GAMBIT Collaboration             
#  \\date {0}
#                                                
#************************************************
""".format(datetime.datetime.now().strftime("%I:%M%p on %B %d, %Y"))

    for type_key in scanbit_flags:
        towrite += """
{0}:""".format(type_key)
        for plug_key in scanbit_flags[type_key]:
            towrite += """
  {0}:""".format(plug_key)
            for version_key in scanbit_flags[type_key][plug_key]:
                towrite += """
    {0}""".format(version_key)
                for flag in scanbit_flags[type_key][plug_key][version_key]:
                    if len(scanbit_flags[type_key][plug_key][version_key][flag]) > 1:
                        towrite += """
      {0}: [{1}]""".format(flag, ", ".join(scanbit_flags[type_key][plug_key][version_key][flag]))
                    else:
                        towrite += """ 
      {0}: {1}""".format(flag, scanbit_flags[type_key][plug_key][version_key][flag][0])
        towrite += "\n"

    flag_entries = "./scratch/build_time/scanbit_flags.yaml"
    candidate = build_dir+"/scanbit_flags.yaml.candidate"
    with open(candidate,"w") as f: f.write(towrite)
    update_only_if_different(flag_entries, candidate)

    if verbose: print("Finished writing scratch/build_time/scanbit_flags.yaml")

    # Make a candidate linkedout.cmake file
    towrite = """# GAMBIT: Global and Modular BSM Inference Tool  
#************************************************
# \\file                                         
#                                                
#  Cmake linking and rpath commands for GAMBIT.  
#                                                
#  This file has been automatically generated by 
#  scanner+_harvester.py.  Please do not modify. 
#                                                
#************************************************
#                                                
#  Authors:                                      
#                                                
#  \\author The GAMBIT Collaboration             
#  \\date {0}
#                                                
#************************************************
                                                 
if (${{CMAKE_SYSTEM_NAME}} MATCHES \"Darwin\")""".format(datetime.datetime.now().strftime("%I:%M%p on %B %d, %Y"))

    if static_links != "":
        towrite += """
    foreach(program ${{uses_scannerbit}})
        target_link_libraries( ${{program}} -Wl,-force_load {0})
    endforeach()""".format(static_links)
    towrite += """
else()"""
    if static_links != "":
        towrite += """
    foreach(program ${{uses_scannerbit}})
        target_link_libraries( ${{program}} -Wl,--whole-archive {0} -Wl,--no-whole-archive )
    endforeach()""".format(static_links)
    towrite += """
endif()
"""

    linked_out = build_dir+"/linkedout.cmake"
    candidate = linked_out+".candidate"
    with open(candidate,"w") as f: f.write(towrite)
    update_only_if_different(linked_out, candidate)

    if verbose: print("Finished writing linkedout.cmake")

# Handle command line arguments (verbosity)
if __name__ == "__main__":
   main(sys.argv[1:])
