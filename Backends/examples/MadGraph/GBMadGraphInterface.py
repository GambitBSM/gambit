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
mg5_dir = "/home/s4358844/GAMBIT/CB_Development/MadGraph_CB/FreshVersion/gambit/Backends/installed/MadGraph/3.4.2/"
sys.path.append(mg5_dir) #TODO: Need to do something like this

#mg5_dir2 = "/home/s4358844/GAMBIT/CB_Development/MadGraph_CB/FreshVersion/gambit/Backends/installed/MadGraph/"
#sys.path.append(mg5_dir2) #TODO: Need to do something like this

import madgraph.interface.master_interface as mi

# Test function to check that I can pass commands to MadGraph. TODO
def TestInterface():
    
    script_name = mg5_dir+"/MyMadGraphTesting.mg5"
    Cmd = "import command " + script_name # TODO: It seems that using this method makes you wait for passing options, it would be better to do it from a file (TODO: How to I do that without writing a file?)

    launch = mi.MasterCmd(mgme_dir = mg5_dir)

    # Execute the command
    print("Executing Commands ...")
    # Prevent automatic html opening in a browser
    launch.exec_cmd("set automatic_html_opening False")
    
    launch.exec_cmd(Cmd)

    return(0)

# Run Event Generation with MadGraph
def MG_RunEvents():

    print("DEBUG: I am starting the MadGraph Bit.....")
    
    script_name = mg5_dir + "../MyMadGraphTesting.mg5"
    
    print("DEBUG: script_name: ", script_name)
    
    #Cmd = "import command " + script_name
    Cmd = "import command /home/s4358844/GAMBIT/CB_Development/MadGraph_CB/FreshVersion/gambit/Backends/installed/MadGraph/MyMadGraphTesting.mg5"
    
    print("DEBUG: Cmd: ", Cmd)
    
    launch = mi.MasterCmd(mgme_dir = mg5_dir)
    
    print("DEBUG: I got here 2.")

    # Execute the command
    print("Executing Commands ...")
    # Prevent automatic html opening in a browser
    launch.exec_cmd("set automatic_html_opening False")
    
    print("DEBUG: I got here 3.")
    
    launch.exec_cmd(Cmd)
    
    print("DEBUG: I got here 4.")

    return(0)



""" Current Commands inside of the mg5 file:
launch MyMadGraphTesting
  set nevents 10
launch MyMadGraphTesting -i
  print_results --path=./cross_section_top.txt --format=short
"""


