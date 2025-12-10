"""
Grid scannner written in Python
===============================
"""

# This is an example for a python scanner.  This example uses 
# the "splug.scanner" base class t9 interface with ScannerBit.
# But, in the comments, is also provided an example on how to
# interact with ScannerBit at a lower level.

# Imports the ScannerBit plugin interface
import emulator_plugin as eplug

# Currently, there are three utilities: 
#   MPI: loads mpi4py and defines "with_mpi" global variable
#   copydoc: provides methods to easy copy doc strings 
#   version: provides methods to easy copy version information
from utils import MPI

import numpy as np


class Test(eplug.emulator):
# doc strings for the class, __init__, and run function will
# automatically be used in the Gambit diagnostics output.
    """
Python implimentation of a simple grid scanner.  Evaluation points along a user-defined grid.

YAML options:
    grid_pts[10]: The number of points along each dimension on the grid.  A vector is given with each element corresponding to each dimension.
    like:            Use the functors that correspond to the specified purpose.
    parameters:      Specifies the order of parameters that corresponds to the grid points specified by the tag "grid_pts".
"""

    # This specifies the version number.
    __version__="1.0.0"
    
    # All the inifile options are passed into the construct as arguments.
    # Optionally, you can interface directly with ScannerBit to get this.
    # A Constructor that takes in arguments is required.
    def __init__(self, **options):
        
        #super().__init__()
        print("starting test emulator plugin")
    
    # This runs the scanner.  This method is required.
    def train(self, x, y, sigs):
        
        print(f"training inputed points, x: {x}; y: {y}; sigs: {sigs}")

        return

    def predict(self, x):

        print(f"predicted input, x: {x}")

        return tuple(np.array([3.5], np.array("0.2")))

# This variable takes ScannerBit the name and class of the scanner.
# Without this, Gambit will not know about the scanner.
__plugins__={"emutest": Test}
