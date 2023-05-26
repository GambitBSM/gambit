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


# Run Event Generation with MadGraph
def MG_RunEvents(mg5_dir, script_name, commands):

    # Add MG directory to path
    sys.path.append(mg5_dir)
    
    # Remove Pre-existing output folder, if it exists
    if (os.path.exists(mg5_dir + script_name + "/Events/run_01")):
        shutil.rmtree(mg5_dir + script_name + "/Events/run_01")
    if (os.path.exists(mg5_dir + script_name + "/HTML/run_01")):
        shutil.rmtree(mg5_dir + script_name + "/HTML/run_01")

    Cmd = "import command " + mg5_dir + script_name + ".mg5"
    
    launch = mi.MasterCmd(mgme_dir = mg5_dir)
    
    # Prevent automatic html opening in a browser
    launch.exec_cmd("set automatic_html_opening False")
    
    # Run each additional setting provided from the yaml
    for cmd in commands:
      launch.exec_cmd(cmd)
    
    # Run the main command
    launch.exec_cmd(Cmd)
    
    return(0)



""" Current Commands inside of the mg5 file:
launch MyMadGraphTesting
  set nevents 10
launch MyMadGraphTesting -i
  print_results --path=./cross_section_top.txt --format=short
"""


