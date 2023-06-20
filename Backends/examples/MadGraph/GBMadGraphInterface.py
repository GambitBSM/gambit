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
import math

import madgraph.interface.master_interface as mi
import madgraph.various.lhe_parser as parser

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

# Call the lhe file splitter function from MadGraph
def Splitfile(path, nevents, npartitions):
    
    # partition should be a list of numbers of events in each file.
    partition = []
    n_per_file = math.floor(nevents/npartitions) # Number of events per split file, if number of events splits equally
    remainder = nevents - n_per_file*npartitions
    # Form the array of how many events per file, with remainder events across multiple files
    for i in range(npartitions):
      if (remainder == 0):
        partition.append(n_per_file)
      else:
        partition.append(n_per_file+1)
        remainder = remainder - 1
    
    parser.EventFile(path).split(nb_event=nevents, partition=partition, cwd=path, zip=False)

    return(0)


