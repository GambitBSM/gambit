#
# Work in progress: Backend interface for xsec
#   github.com/jeriek/xsec
#   arxiv:2006.16273
#
from __future__ import print_function
import numpy as np
import xsec
from math import sqrt

# Prefix for screen output
prefix = "xsecBE_gambit:"

# # This will run when this backend is first loaded, i.e. during GAMBIT startup
# print(prefix, "Starting up...")

# TODO: xsec.init should be run from within GAMBIT, to avoid the hardcoded path here
xsec.init(data_dir="Backends/installed/xsecBE/1.0.2/gprocs/")


#
# Import SLHA content as string
#
def import_slha_string(slha_string):

    print("Reading SLHA input...")
    xsec.import_slha_string(slha_string)
    print("...done")


#
# Set parameters
#
def set_parameters(params):

    for k,v in params.items():
        xsec.set_parameter(k, v)


#
# Return the cross-section for a given process, identified by a PID pair
#
def get_xsection(proc):

    # Load process
    known_process = True
    processes = [proc]
    print("Load process:", proc)
    try:
        xsec.load_processes(processes)
    except KeyError:
        print("Unknown process", proc, "-- setting cross-section to 0")
        known_process = False

    # Evaluate cross-section
    if known_process:
        result_array = xsec.eval_xsection(verbose=1, check_consistency=False)
    else:
        result_array = np.zeros((9,1))
    print("Cross-section array for process", proc, ":", result_array)

    # Construct result dictionary
    # The uncertainties from xsec are relative *deviances*, i.e. (central +/- err) / central
    # Turn them into relative *errors* here:
    result_dict = {}
    result_dict["central"] = result_array[0]
    result_dict["regdown_rel"] = result_array[1]
    result_dict["regup_rel"] = result_array[2]
    result_dict["scaledown_rel"] = result_array[3]
    result_dict["scaleup_rel"] = result_array[4]
    result_dict["pdfdown_rel"] = result_array[5]
    result_dict["pdfup_rel"] = result_array[6]
    result_dict["alphasdown_rel"] = result_array[7]
    result_dict["alphasup_rel"] = result_array[8]

    result_dict["tot_err_down"] = result_dict["central"] * sqrt(result_dict["regdown_rel"]**2 
                                                                + result_dict["scaledown_rel"]**2 
                                                                + result_dict["pdfdown_rel"]**2
                                                                + result_dict["alphasdown_rel"]**2)

    result_dict["tot_err_up"] = result_dict["central"] * sqrt(result_dict["regup_rel"]**2 
                                                                + result_dict["scaleup_rel"]**2 
                                                                + result_dict["pdfup_rel"]**2
                                                                + result_dict["alphasup_rel"]**2)

    return result_dict

