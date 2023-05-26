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
#  \date 2021
#
#  **************************************


import sys

# TODO: Make this pass in from GB in an initialisation stage
#mg5_dir = "/home/s4358844/GAMBIT/CB_Development/MadGraph_CB/FreshVersion/gambit/Backends/installed/MadGraph/3.4.2/"
#sys.path.append(mg5_dir)

import madgraph.interface.master_interface as mi


# Run Event Generation with MadGraph
def MG_RunEvents(mg5_dir, script_name):

    # Add MG directory to path
    sys.path.append(mg5_dir)

    Cmd = "import command " + mg5_dir + script_name
    
    launch = mi.MasterCmd(mgme_dir = mg5_dir)
    
    # Execute the command
    # Prevent automatic html opening in a browser
    launch.exec_cmd("set automatic_html_opening False")
    
    launch.exec_cmd(Cmd)
    
    return(0)



""" Current Commands inside of the mg5 file:
launch MyMadGraphTesting
  set nevents 10
launch MyMadGraphTesting -i
  print_results --path=./cross_section_top.txt --format=short
"""


