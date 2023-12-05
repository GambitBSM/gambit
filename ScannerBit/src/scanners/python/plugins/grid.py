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
    grid_pts[10]: The number of points along each dimension on the grid.  A vector is given with each element corresponding to each dimension.
    like:            Use the functors thats corresponds to the specified purpose.
    parameters:      Specifies the order of parameters that corresponds to the grid points specified by the tag "grid_pts".
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
        # # find mpi values
        # self.mpi_rank = scannerbit.rank()
        # self.mpi_size = scannerbit.numtasks()
        # # gets dimension of hyper cube.
        # self.dim = splug.get_dimension()
        
        # # gets inifile value corresponding to "like" key
        # purpose = options["like"]
        #
        # # or alternatively you can access the inifile options directly by:
        # purpose = splug.get_inifile_value("like", dtype=str)
        #
        # # gets likelihood corresponding to the purpose "purpose"
        # # self.like = splug.get_purpose(purpose)
        #
        # # get grids pt number from inifile. Return a list of ints
        # # grid_pts = options["grid_pts"]
        
        # # or alternatively you can access the inifile options directly by:
        # # grid_pts = splug.get_inifile_value("grid_pts", dtype=list, etype=int)
        
        # # gets "parameters" infile value with a default of []. Returns a list of strings
        # # parameters = splug.get_inifile_value("parameters", dtype=list, etype=str, default=list());
        
        if isinstance(grid_pts, int):
            grid_points = [grid_pts] * self.dim
        
        if len(grid_pts) != self.dim:
            raise RuntimeError("Grid scanner: The dimension of gambit ({0}) does not match the dimension of the inputed grid_pts ({1}).".format(self.dim, len(grid_pts)))
        
        self.size = np.prod(np.asarray(grid_pts))
                
        self.vecs=[]

        # prepare the grid of points
        if len(parameters) > 0:
            param_names = self.parameter_names
            # non-base class version:
            # # get the parameters names from the prior
            # param_names = splug.get_prior().getShownParameters()
            
            if len(param_names) != len(parameters):
                raise RuntimeError("Grid scanner: The dimension of gambit ({0}) does not match the dimension of the inputed parameters ({1}).".format(len(param_names), len(parameters)))
            
            for param in param_names:
                if param in parameters:
                    self.vecs.append(np.linspace(0.0, 1.0, grid_pts[parameters.index(param)]))
                else:
                    raise RuntimeError("Grid scanner: parameter \"{0}\" is not provided.".format(param))

        else:
            for n in grid_pts:
                self.vecs.append(np.linspace(0.0, 1.0, n))
    
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
