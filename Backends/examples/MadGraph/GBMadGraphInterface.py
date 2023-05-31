#  \file
#
#  Early version of my MadGraph5 Backend.
#  This is a python script with functions
#  to send certain commands to MG5
#
#  *************************************
#
#  \author Chris Chang
#          (christopher.chang@uqconnect.edu.au)
#  \date 2023
#
#  **************************************


import sys
import os
import shutil

import madgraph.interface.master_interface as mi

# Generate the run script
def generate_runscript(mg5_dir, script_name, commands, PassParamsToMG):

    with open(mg5_dir + script_name + ".mg5", "w") as FileOut:
        FileOut.write("launch " + script_name + "\n")

        # Add each additional setting provided from the yaml
        for cmd in commands:
          FileOut.write("  " + cmd + "\n")
        
        # Set each parameter value
        for par in PassParamsToMG:
          FileOut.write("  set " + par + " " + str(PassParamsToMG[par]) + "\n")
          
        FileOut.write("launch " + script_name + " -i\n")
        FileOut.write("  print_results --path=./cross_section_top.txt --format=short") # TODO: I probably want to change this so it doesn't print at all
    
    return


# Run Event Generation with MadGraph
def MG_RunEvents(mg5_dir, script_name, commands, PassParamsToMG, rank):

    # Add MG directory to path
    sys.path.append(mg5_dir)
    
    # If not present, copy the output directory for each MPI rank
    script_name_rank = script_name + "_" +  str(rank)
    if not (os.path.exists(mg5_dir + script_name_rank)):
      shutil.copytree(mg5_dir + script_name, mg5_dir + script_name_rank)
    
    # Remove Pre-existing event folder, if it exists
    if (os.path.exists(mg5_dir + script_name_rank + "/Events/run_01")):
        shutil.rmtree(mg5_dir + script_name_rank + "/Events/run_01")
    if (os.path.exists(mg5_dir + script_name_rank + "/HTML/run_01")):
        shutil.rmtree(mg5_dir + script_name_rank + "/HTML/run_01")

    Cmd = "import command " + mg5_dir + script_name_rank + ".mg5"
    
    launch = mi.MasterCmd(mgme_dir = mg5_dir)
    
    # Prevent automatic html opening in a browser
    launch.exec_cmd("set automatic_html_opening False")
    
    generate_runscript(mg5_dir, script_name_rank, commands, PassParamsToMG)
    
    # Run the main command
    launch.exec_cmd(Cmd)
    
    return(0)

