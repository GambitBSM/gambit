"""
Random fast/slow scannner written in Python
===============================
"""

import scanner_plugin as splug
import numpy as np

class Random_Fast_Slow(splug.scanner):
    """
Python implimentation of a random fast/slow scanner.

YAML options:
    like:                       Use the functors that correspond to the specified purpose.
    point_number [10]:          Number of random points.
    fast_repeats [1]:           Number of repeats for fast parameters.
    slow_speed_threshold [5]:   Speed value that is considered "fast".
"""

    __version__="1.0.0"
    
    def __init__(self, point_number=10, fast_repeats=1, slow_speed_threshold=5, **options):
        
        super().__init__(use_mpi=True, use_resume=False)

        self.point_number = point_number
        self.fast_repeats = fast_repeats
        self.speedPos = self.getSpeedPositions(slow_speed_threshold)
        # # This will set speedPos to a tuple
        # self.speedPos = self.getSpeedPositions(0, slow_speed_threshold, -1)
        # # This will set speedPos to a list
        # self.speedPos = self.getSpeedPositions([0, slow_speed_threshold, -1])
    
    def run(self):

        for pt in np.random.uniform(size=(self.point_number, self.dim))[self.mpi_rank:self.point_number:self.mpi_size]:

            self.loglike_hypercube(pt)

            for fast_pt in np.random.uniform(size=(self.fast_repeats, self.dim-self.speedPos)):
                pt[self.speedPos:self.dim] = fast_pt
                self.loglike_hypercube(pt)

        return 0

__plugins__={"python_random_fast_slow": Random_Fast_Slow}
