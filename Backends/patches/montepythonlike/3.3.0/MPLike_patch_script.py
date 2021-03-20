'''   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///  script to patch MontePython to work with gambit
///
///   - harvest all likelihoods included in montepython/likelihoods folder
///   - create list of available likelihoods
///   - replace import statement in each __init__ file to import MontePhytonLike instead of montepython.likelihood_class
///
///   Note: for simplicity the Data object is also defined in MontePythonLike (extra file in standard MontePython)
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2019 June
///  \date 2020 Sep
///
///  *********************************************

'''
import os
import sys
import re


def replace(file, pattern, subst, append_to_beginning=""):
    # Read contents from file as a single string
    file_handle = open(file, 'r')

    future_import,file_string = "",""

    # problem: all __future__ imports have to appear 
    # in the beginning of the file -> can't insert 
    # the extra sys import into the beginning of 
    # a file if __future__ package is imported
    # -> remove these lines from the file and 
    # add them to the beginning later
    for line in file_handle:
        if "__future__" in line:
            future_import += line
        else:
            file_string += line
    file_handle.close()

    # Use RE package to allow for replacement (also allowing for (multi-line) REGEX)
    file_string = (re.sub(pattern, subst, file_string))

    # Write contents to file; Using mode 'w' truncates the file.
    file_handle = open(file, 'w')
    file_handle.write(future_import+append_to_beginning+file_string)
    file_handle.close()


# patch MontePythonLike to work with GAMBIT in a few lines -- just classy!
if __name__ == '__main__':
    
    # create list with all likelihood names contained in montepython/likelihoods/ folder
    output = [dI for dI in os.listdir("montepython/likelihoods/") if os.path.isdir(os.path.join('montepython/likelihoods/',dI))]
    
    abspath = os.path.dirname(os.path.abspath(__file__))

    for like in output:
        # replace importin of montepython.likelihood_class with import of MontePythonLike
        # Note that the system path has to be inserted in the begining of the file as well
        replace("montepython/likelihoods/"+like+"/__init__.py", "from montepython.likelihood_class import", 
            "from MontePythonLike_3_3_0 import", append_to_beginning="import sys \nsys.path.append('"+abspath+"')\n" )
        # also replace importing of io_mp module (only contains input/output stream so safe to use with GAMBIT)
        replace("montepython/likelihoods/"+like+"/__init__.py", "import montepython.io_mp as io_mp", "import io_mp")
