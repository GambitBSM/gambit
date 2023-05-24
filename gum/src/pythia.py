#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Contains all routines for Pythia output,
#  via the MadGraph interface.
#
#  *************************************
#
#  \author Pat Scott
#          (pat.scott@uq.edu.au)
#  \date 2018 Dec
#        2019 Jan
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2019 July
#        2020 June, July
#
#  **************************************

from .backends import *
from .setup import *
from .files import *
from .parse import *
from .cmake_variables import *

class PythiaMatch:
    """
    Class used for saving details about particles from ParticleData.xml
    """

    def __init__(self, pdg, name, antiname, spintype, chargetype, coltype):

        self.pdg = pdg
        self.name = name
        self.antiname = antiname
        self.spintype = spintype
        self.chargetype = chargetype
        self.coltype = coltype

def fix_pythia_lib(model, patched_dir, pythia_groups, particles, decays):
    """
    Routine to patch the new Pythia - adding new matrix elements to the
    Process Container -- and the shared library too.
    """

    # Move the matrix element sources and headers to where they will get compiled into the Pythia library
    process_dir = patched_dir+"/Processes_"+model+"/"
    source_dir = patched_dir+"/src/"
    inc_dir = patched_dir+"/include/"
    files = os.listdir(process_dir)
    headers = [x for x in files if x.endswith(".h")]
    sources = [x for x in files if x.endswith(".cc")]
    for x in headers:
        os.rename(process_dir+"/"+x, inc_dir+"/"+x)
    for x in sources:
        os.rename(process_dir+"/"+x, source_dir+"/"+x)

    # Scrape the list of processes from the header names
    processes = []
    for x in headers:
        if (x.startswith("Sigma_")):
            states = re.split("_", re.sub("Sigma_"+model+"_", "", re.sub("\.h", "", x)))
            with open(inc_dir+"/"+x) as f:
                for line in f:
                    if "// Process: " in line:
                        process_string = re.sub(" WEIGHTED.*\n", "", re.sub("// Process: ", "", line))
                        process_string = re.sub(">", "&rarr;", process_string)
                        states.append("<ei>"+process_string+"<\ei>")
            processes.append(states)

    # Get rid of the leftover process directory made by MadGraph
    remove_tree_quietly(process_dir)

    # Write the xml doc file for the new processes
    with open(patched_dir+"/share/Pythia8/xmldoc/"+model+"Processes.xml", 'w') as f:
        f.write("<flag name=\""+model+":all\" default=\"off\">\n")
        f.write("Common switch for production of "+model+" processes. Added by GAMBIT.\n")
        f.write("</flag>\n")

        # Go through pythia_groups to add each individual flag, to
        # select groups of subprocesses
        if pythia_groups:
            for group in pythia_groups:
                for k, v in group.items():
                    f.write("<flag name=\""+model+k+":all\" default=\"off\">\n")
                    f.write("Common switch for production of "+model+" processes, involving the group of particles ["+', '.join(v)+"] as external legs ONLY. Added by GAMBIT.\n")
                    f.write("</flag>\n")

        # Individual processes
        for x in processes:
            f.write("\n")
            f.write("<flag name=\""+model+":"+x[0]+"2"+x[1]+"\" default=\"off\">\n")
            f.write("Switch for "+model+" process "+x[2]+". Added by GAMBIT.\n")
            f.write("</flag>\n")

    # Add the new processes to the master Pythia index.xml file
    old = patched_dir+"/share/Pythia8/xmldoc/Index.xml"
    tmp = old+".temp"
    with open(old) as f_old, open(tmp, 'w') as f_new:
        for line in f_old:
            f_new.write(line)
            if "<aidx href=\"SUSYProcesses\">SUSY</aidx><br/>" in line:
                f_new.write("&nbsp;&nbsp;--&nbsp;&nbsp;\n")
                f_new.write("<aidx href=\""+model+"Processes\">"+model+"</aidx><br/>\n")
    os.remove(old)
    os.rename(tmp, old)

    # Add the new processes to the Pythia Process Container
    old = source_dir+"ProcessContainer.cc"
    tmp = old+".temp"
    with open(old) as f_old, open(tmp, 'w') as f_new:
        for line in f_old:
            f_new.write(line)
            if "#include \"Pythia8/SigmaSUSY.h\"" in line:
                for x in headers:
                    if x.startswith("Sigma"):
                        f_new.write("#include \""+x+"\"\n")

            if "// End of SUSY processes." in line:

                f_new.write("\n")
                f_new.write("  // Set up requested objects for "+model+" processes. Added by GAMBIT.\n")
                f_new.write("  bool "+model+" = settings.flag(\""+model+":all\");\n")

                # Go through pythia_groups to add each individual flag, to
                # select groups of subprocesses
                if pythia_groups:
                    for group in pythia_groups:
                        for k, v in group.items():
                            f_new.write("  bool "+model+k+" = settings.flag(\""+model+k+":all\");\n")

                # Add each process
                for x in processes:

                    process_syntax = x[2]
                    # Get the in and out states
                    in_states =  re.search('<ei>(.*)&rarr', process_syntax).group(1).split()
                    out_states = re.search(';(.*)<\\\\ei>', process_syntax).group(1).split()
                    external_states = in_states+out_states

                    # If any of the particles belong to any Pythia group,
                    # add them as a conditional to be selectable from
                    # the yaml file in a GAMBIT scan.

                    switches = ""
                    if pythia_groups:
                        for group in pythia_groups:
                            for k, v in group.items():
                                vtemp = [i.lower() for i in v] # Pythia makes everything lowercase
                                if any([i.lower() in vtemp for i in external_states]):
                                    switches += " {0} ||".format(model+k)

                    f_new.write("  if ("+model+" ||{0} settings.flag(\"".format(switches)+model+":"+x[0]+"2"+x[1]+"\")) {\n")
                    f_new.write("    sigmaPtr = new Sigma_"+model+"_"+x[0]+"_"+x[1]+"();\n")
                    f_new.write("    containerPtrs.push_back( new ProcessContainer(sigmaPtr) );\n")
                    f_new.write("  }\n")

    os.remove(old)
    os.rename(tmp, old)

    """
    S.B. 22/07/2020: commented the below out, as it looks like we actually
    _don't_ need to make changes to ParticleData.xml. Leaving it here just
    in case we change our minds again...


    # Add new particles to the ParticeData xml file, and their decay products
    # Firstly scrape the initial list of particles and check everything
    # is consistent
    xmold = patched_dir + "/share/Pythia8/xmldoc/ParticleData.xml"
    xmnew = patched_dir + "/share/Pythia8/xmldoc/ParticleData.xml_new"
    with open(xmold) as f:
        txt = f.read()

    pat = re.compile(r'<particle\s+(.*?)\n(.*?)>', re.MULTILINE)
    matches = re.findall(pat, txt)

    # Save a dict of PDG code : match object
    # Check consistency between the newly added particles and any definitions
    defined_particles = {}

    for match in matches:

        m = ''.join(match)

        pdg = re.search(r'id="(.*?)"', m).group(1)
        name = re.search(r'name="(.*?)"', m).group(1)
        spintype = re.search(r'spinType="(.*?)"', m).group(1)
        chargetype = re.search(r'chargeType="(.*?)"', m).group(1)
        coltype = re.search(r'colType="(.*?)"', m).group(1)
        a = re.search(r'antiName="(.*?)"', m)
        antiname = a.group(1) if a else ""

        pm = PythiaMatch(pdg, name, antiname, spintype, chargetype, coltype)

        defined_particles[int(pdg)] = pm

    # Iterate through the particle list and check to see if any are
    # already defined in Pythia.
    dp = []
    for p in particles:
        if p.PDG_code in defined_particles:

            dp.append(p.PDG_code)

            # Check the particle definition applies to the user's file...
            ppy = defined_particles[p.PDG_code]

            # Spin
            if p.spinX2+1 != int(ppy.spintype):
                raise GumError(("Particle with PDG code {0} is "
                                "already defined in Pythia's particle database."
                                "\nThe spin provided for this particle does "
                                "not match up with the definition in Pythia.\n"
                                "Pythia: {1}, you: {2}. (spin = 2s+1)\n"
                                "Please use a different PDG code."
                              ).format(str(p.PDG_code), ppy.spintype,
                                       str(p.spinX2+1)))

            # Charge
            if int(p.chargeX3) != int(ppy.chargetype):
                raise GumError(("Particle with PDG code {0} is "
                                "already defined in Pythia's particle database."
                                "\nThe charge provided for this particle does "
                                "not match up with the definition in Pythia.\n"
                                "Pythia: {1}, you: {2}. (charge x 3)\n"
                                "Please use a different PDG code."
                              ).format(str(p.PDG_code), ppy.chargetype,
                                       p.chargeX3))

            # Color
            pycolor = 0
            if p.color == 3: pycolor = 1
            elif p.color == -3: pycolor = -1
            elif p.color == 8: pycolor = 2
            elif p.color == 6: pycolor = 3
            elif p.color == -6: pycolor = -3
            if int(pycolor) != int(ppy.coltype):
                raise GumError(("Particle with PDG code {0} is "
                                "already defined in Pythia's particle database."
                                "\nThe color provided for this particle does "
                                "not match up with the definition in Pythia.\n"
                                "Pythia: {1}, you: {2}.\n"
                                "Please use a different PDG code."
                              ).format(str(p.PDG_code), ppy.coltype,
                                       pycolor))

            # Antiparticle
            if not p.is_sc():
                if not ppy.antiname:
                    raise GumError(("Particle with PDG code {0} is "
                                    "already defined in Pythia's particle "
                                    "database.\n"
                                    "It has no distinct antiparticle, "
                                    "whereas your model definition says it "
                                    "does.\nThis particle does not match up "
                                    "with the definition in Pythia.\n"
                                    "Please use a different PDG code."
                                  ).format(str(p.PDG_code)))
            else:
                if ppy.antiname:
                    raise GumError(("Particle with PDG code {0} is "
                                    "already defined in Pythia's particle "
                                    "database.\nIt has an antiparticle, "
                                    "whereas your model definition says it "
                                    "does not.\nThis particle does not match up "
                                    "with the definition in Pythia.\n"
                                    "Please use a different PDG code."
                                  ).format(str(p.PDG_code)))

    # Once we're satisfied there's no incorrect duplicates, we can
    # add new entries to the XML file.
    p_towrite = ""
    append_decays = {}
    for p in particles:

        # Don't need to add the particle if it already exists...
        if not p.PDG_code in dp:

            # If antiparticle is distinct, we want to save this information too.
            name = p.name
            if not p.is_sc():
                name += " antiname = {}".format(p.antiname)

            # Convert to Pythia's color basis:
            # 0 = uncolored, (-)1 = (anti)triplet, 2 = octet, (-)3 = (anti)sextet
            color = 0
            if p.color == 3: color = 1
            elif p.color == -3: color = -1
            elif p.color == 8: color = 2
            elif p.color == 6: color = 3
            elif p.color == -6: color = -3
            # All gucci. Save the particle
            p_towrite += (
                      "<particle id=\"{0}\" name=\"{1}\" spinType=\"{2}\" "
                      "chargeType=\"{3}\" colType=\"{4}\"\n"
                      "          m0=\"100.00000\">\n"
            ).format(p.PDG_code, name, p.spinX2+1, p.chargeX3, color)

            # Now for the decays...
            if p.PDG_code in decays:
                for d in decays[p.PDG_code]:
                    p_towrite += (
                              " <channel onMode=\"1\" bRatio=\"0.0000000\" "
                              "meMode=\"0\" products=\"{0}\"/>\n"
                    ).format(' '.join(str(x) for x in d))

            p_towrite += "</particle>\n\n"

        # If it already exists, just need to append the decays to the entry
        else:

            if p.PDG_code in decays:
                d_entry = ""
                for d in decays[p.PDG_code]:
                    d_entry += (
                              " <channel onMode=\"1\" bRatio=\"0.0000000\" "
                              "meMode=\"0\" products=\"{0}\"/>\n"
                    ).format(' '.join(str(x) for x in d))

                append_decays[p.PDG_code] = d_entry

    # Save the new .xml file
    waiting_for_braces = False
    with open(xmnew, 'w+') as f, open(xmold) as g:
        for line in g:
            # This is the end...
            if "</chapter>" in line:
                f.write(p_towrite)

            # If the particle definition is there, see if we need to add decays
            r = re.search(r'id="(.*?)"', line)
            if r:
                pdg = int(r.group(1))
                if pdg in append_decays:
                    waiting_for_braces = True

            if waiting_for_braces and "</particle>" in line:
                f.write(append_decays[pdg])
                waiting_for_braces = False

            f.write(line)

    os.remove(xmold)
    os.rename(xmnew, xmold)
    """

def write_boss_configs_for_pythia(model, output_dir, reset_dict):
    """
    Writes the BOSS configs for Pythia.
    """

    # Sort out the paths
    path = "/Backends/scripts/BOSS/configs"
    full_output_dir = output_dir+path
    mkdir_if_absent(full_output_dir)
    filenames = ["/pythia_"+model.lower()+"_8_"+base_pythia_version+".py"]
    templates = [".."+path+"/pythia_8_"+base_pythia_version+".py"]
    outfiles = ["BOSS/configs"+f for f in filenames]

    # Write the actual BOSS config file
    for outfile, template in zip(outfiles, templates):

      to_write = ("")
      with open(template) as f_old:
        for line in f_old:
          if "gambit_backend_name      = 'Pythia'" in line:
              to_write += ("gambit_backend_name      = 'Pythia_"+model+"'\n")
          # Add the CombineMatchingInput class to the input files.
          elif "                  '../../../Backends/installed/'+gambit_backend_name.lower()+'/'+gambit_backend_version+'/include/Pythia8/Pythia.h'" in line:
              to_write += ("                  '../../../Backends/installed/'+gambit_backend_name.lower()+'/'+gambit_backend_version+'/include/Pythia8/Pythia.h',\n")
              to_write += ("                  '../../../Backends/installed/'+gambit_backend_name.lower()+'/'+gambit_backend_version+'/include/Pythia8Plugins/CombineMatchingInput.h',\n")
          else:
              to_write += (line)
          if "#  Configuration module for BOSS  #" in line:
              to_write += ("#  ----brought to you by GUM----  #\n")

          # Add in the Combine Matching Input Class
          if "    'Pythia8::BeamParticle'," in line:
              to_write += ("    'Pythia8::CombineMatchingInput',\n")

      write_file(outfile, "Backends", to_write, reset_dict)


def write_pythia_cmake_entry(model, output_dir):
    """
    Writes Pythia entry for cmake/backends.cmake
    """

    # The string that will commence the block to be added by GUM
    to_write = "# Pythia with matrix elements for "+model+" (brought to you today by the letters G, U and M).\n"\
               "set(model \""+model.lower()+"\")\n"\
               "set(name \"pythia_${model}\")\n"\
               "set(ver \"8."+base_pythia_version+"\")\n"\
               "set(lib \"libpythia8\")\n"\
               "set(dl \"https://pythia.org/download/pythia82/pythia8"+base_pythia_version+".tgz\")\n"\
               "set(md5 \""+pythia_md5+"\")\n"\
               "set(dir \"${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}\")\n"\
               "set(model_specific_patch \"${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif\")\n"\
               "check_ditch_status(${name} ${ver} ${dir})\n"\
               "if(NOT ditched_${name}_${ver})\n"\
               "  ExternalProject_Add(${name}_${ver}\n"\
               "    DEPENDS hepmc\n"\
               "    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}\n"\
               "    SOURCE_DIR ${dir}\n"\
               "    BUILD_IN_SOURCE 1\n"\
               "    PATCH_COMMAND patch -p1 < ${model_specific_patch}\n"\
               "          COMMAND patch -p1 < ${patch}\n"\
               "          COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}.py\n"\
               "    CONFIGURE_COMMAND ./configure ${EXTRA_CONFIG} --enable-shared --cxx=\"${CMAKE_CXX_COMPILER}\" --cxx-common=\"${pythia_CXXFLAGS}\" --cxx-shared=\"${pythia_CXX_SHARED_FLAGS}\" --cxx-soname=\"${pythia_CXX_SONAME_FLAGS}\" --lib-suffix=\".so\"\n"\
               "    BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} CXX=\"${CMAKE_CXX_COMPILER}\" lib/${lib}.so\n"\
               "    INSTALL_COMMAND \"\"\n"\
               "  )\n"\
               "  BOSS_backend(${name} ${ver} \"\")\n"\
               "  add_extra_targets(\"backend\" ${name} ${ver} ${dir} ${dl} distclean)\n"\
               "  set_as_default_version(\"backend\" ${name} ${ver})\n"\
               "endif()\n\n"

    return to_write


def patch_pythia_patch(model_parameters, model_name, reset_dict):
    """
    Writes a generic patch to the existing GAMBIT Pythia patch.
    This adds new LesHouches block entries for a new model.
    """

    pp_source = "\n        \"      // LH blocks added by GUM\\n\"\n"
    pp_header = "\n        \"  // LH blocks added by GUM\\n\"\n"

    blocks = []

    for i in model_parameters:

        if (i.sm) or (i.tag == "Pole_Mass" and i.block == "") or i.block in blocks or i.block.lower() == "mass":
            continue

        pp_source += (
                "        \"      if (blockName == \\\"{0}\\\") ifail={0}.set(linestream);\\n\"\n"
        ).format(i.block.lower())

        # Scalars
        if i.shape == "scalar" or i.shape == None:
            pp_header += "        \"  LHblock<double> {0};\\n\"\n".format(i.block.lower())
        # Matrices
        elif re.match("m[2-9]x[2-9]", i.shape):
            pp_header += "        \"  LHmatrixBlock<{0}> {1};\\n\"\n".format(i.shape[-1], i.block.lower())
        # Wtfs
        else:
            raise GumError("Unknown shape for block " + i.block.lower() + ".")

        blocks.append(i.block)

    # This is the output to add to the post-GAMBIT patched Pythia.

    patch_contents = (
        "import os\n"
        "\n"
        "location = \"src/SusyLesHouches.cc\"\n"
        "temp_location = location + \"_temp\"\n"
        "\n"
        "lines = open(location, 'r').readlines()\n"
        "\n"
        "# Find where the GAMBIT patch ends.\n"
        "linenum = 0\n"
        "with open(location) as f:\n"
        "    for num, line in enumerate(f, 1):\n"
        "        if \"(blockName == \\\"nmssmrun\\\") ifail=nmssmrun.set(linestream)\" in line:\n"
        "            linenum = num+1\n"
        "            break\n"
        "\n"
        "with open(temp_location, 'w') as f:\n"
        "    # Write the stuff at the beginning...\n"
        "    for i in range(linenum):\n"
        "        f.write(lines[i])\n"
        "    # Write the source specific to the model...\n"
        "    f.write(("
        "{2}"
        "        \"\\n\"\n"
        "    ))\n"
        "    # Then write the rest. Voila: the cheap man's patch.\n"
        "    for i in range(len(lines)-linenum):\n"
        "        f.write(lines[i+linenum])\n"
        "\n"
        "os.remove(location)\n"
        "os.rename(temp_location, location)\n"
        "\n"
        "location = \"include/Pythia8/SusyLesHouches.h\"\n"
        "temp_location = location + \"_temp\"\n"
        "\n"
        "lines = open(location, 'r').readlines()\n"
        "\n"
        "# Find where the GAMBIT patch ends.\n"
        "linenum = 0\n"
        "with open(location) as f:\n"
        "    for num, line in enumerate(f, 1):\n"
        "        if \"LHmatrixBlock<5> imnmnmix;\" in line:\n"
        "            linenum = num\n"
        "            break\n"
        "\n"
        "with open(temp_location, 'w') as f:\n"
        "    # Write the stuff at the beginning...\n"
        "    for i in range(linenum):\n"
        "        f.write(lines[i])\n"
        "    # Write the stuff specific to the model.\n"
        "    f.write(("
        "{3}"
        "        \"\\n\"\n"
        "    ))\n"
        "    # Then write the rest. Voila: the cheap man's patch.\n"
        "    for i in range(len(lines)-linenum):\n"
        "        f.write(lines[i+linenum])\n"
        "\n"
        "os.remove(location)\n"
        "os.rename(temp_location, location)\n"
    ).format(model_name.lower(), base_pythia_version, pp_source, pp_header)

    filename = "pythia_{0}/8.{1}/patch_pythia_{0}.py".format(model_name.lower(), base_pythia_version)
    write_file(filename, "Backends", patch_contents, reset_dict, overwrite_path = "patches/")

def write_pythia_capability_defs(model, cap_def):
    # Add capability definitions
    cap_def['Pythia_' + model + "_8_" + base_pythia_version + '_init'] = 'Initialise the Pythia 8.' + base_pythia_version + ' ' + model + ' backend.'
