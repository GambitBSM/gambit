# from utils import copydoc, version, with_mpi
import numpy as np
from itertools import product
from collections import OrderedDict
import os
import joblib
from mpi4py import MPI
import time

import sys
sys.path.insert(0, '../pygptreeo_project')
from pygptreeo import GPTree, Default_GPR

class pyGPtreeoEmulator():
    """
    pygptreeo
    """
    __version__ = "0.1.0"
    __plugin_name__ = "pygptreeo"

    def __init__(self, mpi_comm, **kwargs):
        # super().__init__(use_mpi=True)
        # mpi stuff
        self.mpiComm = mpi_comm
        self.mpi_rank = mpi_comm.Get_rank()
        self.mpi_size = mpi_comm.Get_size()

        # TODO: read tree filename 
        self.tree_filename = 'pygptreeo_model.joblib'
        self.max_cache_size = 10  # maximum number of points to cache before training

        # TODO: read all GPT parameters from kwargs
        self.gpt = GPTree(
            GPR=Default_GPR(), 
            Nbar=50,
            theta=1e-4, 
            split_position_method='median',
            split_dimension_criteria='max_variance',
            retrain_every_n_points=20,
            use_calibrated_sigma=True,
            splitting_strategy='gradual',
        )

        if self.mpi_size == 1 or self.mpi_rank == 1:
            self.gpt.save(self.tree_filename)

        self.last_mtime = os.path.getmtime(self.tree_filename)
        
        self.Xcache = []
        self.Ycache = []

    # @copydoc(scipy_optimize_dual_annealing)
    # update tree with buffer values
    def train(self, x, y):

        if self.mpi_size == 1  or self.mpi_rank == 1:
            X_train = x.reshape(-1, 1)
            y_train = y.reshape(-1, 1)

            # add points to cache
            if len(self.Xcache) < self.max_cache_size-1:
                self.Xcache.append(X_train[0])
                self.Ycache.append(y_train[0])
            # cache is full, train the tree
            else:
                # add current point
                self.Xcache.append(X_train[0])
                self.Ycache.append(y_train[0])

                # Feed data points to the tree sequentially
                for i in range(self.max_cache_size):
                    x_sample = np.array(self.Xcache)[i:i+1, :]
                    y_sample = np.array(self.Ycache)[i:i+1, :]
                    self.gpt.update_tree(x_sample, y_sample)

                # clear cache
                self.Xcache = []
                self.Ycache = []

                # store file
                self.gpt.save(self.tree_filename)
                time.sleep(1)
                

    # predict for x
    def predict(self, x):
        if self.mpi_size == 1 or self.mpi_rank == 0:
            # load tree if file was updated
            time.sleep(1)
            
            current_mtime = os.path.getmtime(self.tree_filename)
            # print("Current mtime:", current_mtime, "Last mtime:", self.last_mtime)
            if current_mtime != self.last_mtime:
                print("File was updated, reloading...")
                self.gpt = joblib.load(self.tree_filename)
                self.last_mtime = current_mtime

            # predict
            X_test = x.reshape(-1,1)
            y_pred, y_std = self.gpt.predict(X_test)

            return y_pred, y_std
        else:
            return None, None
    



