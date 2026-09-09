"""
Grid scannner written in Python
===============================
"""

# This is an example for a python scanner.  This example uses 
# the "splug.scanner" base class t9 interface with ScannerBit.
# But, in the comments, is also provided an example on how to
# interact with ScannerBit at a lower level.

# Imports the ScannerBit plugin interface
import scanner_plugin as splug

# Currently, there are three utilities: 
#   MPI: loads mpi4py and defines "with_mpi" global variable
#   copydoc: provides methods to easy copy doc strings 
#   version: provides methods to easy copy version information
from utils import MPI

import numpy as np


class Grid(splug.scanner):
# doc strings for the class, __init__, and run function will
# automatically be used in the Gambit diagnostics output.
    """
Python implimentation of a simple grid scanner.  Evaluation points along a user-defined grid.

YAML options:
    grid_pts:       A YAML map from "<model>::<param>" to integer, giving
                    the number of grid points along each axis.  Every
                    scanned parameter must appear as a key.  Example:
                      grid_pts:
                        NormalDist::mu: 5
                        NormalDist::sigma: 3
    like:           Use the functors that correspond to the specified purpose.
    parameters:     Specifies the order of parameters that corresponds to the grid points specified by the tag "grid_pts".
"""

    # This specifies the version number.
    __version__="1.0.0"
    
    # All the inifile options are passed into the construct as arguments.
    # Optionally, you can interface directly with ScannerBit to get this.
    # A Constructor that takes in arguments is required.
    def __init__(self, grid_pts=10, parameters=[], **options):
        
        super().__init__(use_mpi=True, use_resume=False)

        # You can access plugin data without using base class as follows:
        #
        # # Find mpi values:
        # self.mpi_rank = scannerbit.rank()
        # self.mpi_size = scannerbit.numtasks()
        # 
        # # Get dimension of hyper cube:
        # self.dim = splug.get_dimension()
        # 
        # # Get inifile value corresponding to "like" key:
        # purpose = options["like"]
        #
        # # Or alternatively, you can access the inifile options directly by:
        # purpose = splug.get_inifile_value("like", dtype=str)
        #
        # # Get likelihood corresponding to the purpose "purpose":
        # # self.like = splug.get_purpose(purpose)
        #
        # # Get grids pt number from inifile (returns a dict of {param: int}):
        # # grid_pts = options["grid_pts"]   
        # 
        # # Or alternatively, you can access the inifile options directly by:
        # # grid_pts = splug.get_inifile_value("grid_pts", dtype=dict)

        if not isinstance(grid_pts, dict):
            raise RuntimeError(
                "Grid scanner: \"grid_pts\" must be a YAML map from "
                "\"<model>::<param>\" to integer, e.g.\n"
                "    grid_pts:\n"
                "      NormalDist::mu: 5\n"
                "      NormalDist::sigma: 3")

        param_names = self.parameter_names
        # Non-base class version:
        # # Get the parameters names from the prior:
        # param_names = splug.get_prior().getShownParameters()

        # Helper: splits a (possibly "+"-joined) shown parameter name into
        # its constituent names, mirroring parse_sames() in the C++ grid
        # scanner.  This lets users reference any one name of a "same_as"
        # group when keying grid_pts.
        def _name_set(joined):
            return set(joined.split("+"))

        N = [None] * self.dim

        for key, value in grid_pts.items():
            matched_index = None
            for i, joined in enumerate(param_names):
                if key in _name_set(joined):
                    matched_index = i
                    break
            if matched_index is None:
                raise RuntimeError(
                    "Grid scanner: parameter \"{0}\" listed in grid_pts "
                    "is not a scanned parameter.".format(key))
            if N[matched_index] is not None:
                raise RuntimeError(
                    "Grid scanner: parameter \"{0}\" is specified more "
                    "than once in grid_pts.".format(key))
            N[matched_index] = int(value)

        for i, joined in enumerate(param_names):
            if N[i] is None:
                raise RuntimeError(
                    "Grid scanner: number of grid points for parameter "
                    "\"{0}\" is not specified in grid_pts.".format(joined))

        if self.mpi_rank == 0:
            print("Grid scanner: parameter -> number of grid points mapping:")
            for joined, n in zip(param_names, N):
                print("    {0} -> {1}".format(joined, n))

        self.size = int(np.prod(np.asarray(N)))
        self.vecs = [np.linspace(0.0, 1.0, n) for n in N]

    # This runs the scanner.  This method is required.
    def run(self):

        # scan the grid of points, divided evenly across the numper of MPI processes
        for pt in np.vstack(np.meshgrid(*self.vecs)).reshape(self.dim, -1).T[self.mpi_rank:self.size:self.mpi_size]:

            # run likelihood
            self.loglike_hypercube(pt)
            
            # prints value
            self.print(1.0, "Posterior")
            
            # # or equivalently, you can go the same if using the low-level interface:
            # self.like(pt)
            # id = self.like.getPtID()
            # splug.get_printer().get_stream().print(1.0, "mult", self.rank, id)
        
        return 0

# This variable takes ScannerBit the name and class of the scanner.
# Without this, Gambit will not know about the scanner.
__plugins__={"python_grid": Grid}
