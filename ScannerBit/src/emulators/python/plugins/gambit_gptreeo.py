# from utils import copydoc, version, with_mpi
import emulator_plugin as eplug
import numpy as np
import os
import joblib
from mpi4py import MPI
import time
import tempfile


import sys
sys.path.insert(0, '../pygptreeo_project')
from pygptreeo import GPTree, Default_GPR


# incase atomic save doesnt get added to gptreeo
def atomic_joblib_dump(obj, path):
    dir_name = os.path.dirname(path)
    fd, tmp_path = tempfile.mkstemp(dir=dir_name, suffix=".joblib")
    os.close(fd)  # joblib will reopen it
    obj.save(tmp_path)
    os.replace(tmp_path, path)  # atomic replace


class pyGPtreeoEmulator(eplug.emulator):
    """
gptreeo emulator

YAML options:
    train: Option to enable/disable training
    predict: Option to enable/disable prediction
    uncertainty: Prediction uncertainty threshold for GAMBIT
    max_cache_size: Maximum number of points in cache before re-training the tree
    Nbar: Maximum number of training points a node
        can hold before splitting. Defaults to 100.
    theta: Parameter influencing the overlap region
        between sibling nodes. The overlap is calculated as
        theta * range_of_split_dimension. Defaults to 0.0001.
    use_calibrated_sigma: If True, enables sigma
        calibration in GPNode predictions. Defaults to True.
    split_dimension_criteria: Method to select split
        dimension. Options: 'max_spread', 'max_variance', 'max_uncertainty',
        'random'. Defaults to 'max_spread'.
    splitting_strategy: Strategy for splitting nodes.
        'standard' or 'gradual'. Defaults to 'standard'.
    pre_trained: Boolean option to load a pre-trained model
    pre_trained_path: Path to pre-trained model file. OBS: new model file 
        will be written and stored in run folder.
"""

    __version__ = "1.0.0"
    __plugin_name__ = "pygptreeo"

    def __init__(self, **kwargs):
        super().__init__()

        # Get filename and max cache size from kwargs
        self.tree_filename = kwargs['default_output_path']+'pygptreeo_model.joblib'
        self.max_cache_size = kwargs['max_cache_size']  # maximum number of points to cache before training

        # Read all GPT parameters from kwargs
        self.gpt = GPTree(
            GPR=Default_GPR(),
            Nbar=kwargs['Nbar'],
            theta=kwargs['theta'],
            split_position_method=kwargs['split_position_method'],
            split_dimension_criteria=kwargs['split_dimension_criteria'],
            retrain_every_n_points=kwargs['retrain_every_n_points'],
            use_calibrated_sigma=kwargs['use_calibrated_sigma'],
            splitting_strategy=kwargs['splitting_strategy'],
        )

        if self.mpi_size == 1 or self.mpi_rank == 1:
            if kwargs.get('pre_trained', False):
                pre_trained_path = kwargs.get('pre_trained_path', self.tree_filename)
                print(f"Loading pre-trained model from {pre_trained_path}...")
                if os.path.exists(pre_trained_path):
                    self.gpt = joblib.load(pre_trained_path)
                self.gpt.atomic_save(self.tree_filename)
                # atomic_joblib_dump(self.gpt, self.tree_filename)
            else:
                print("Initializing GPTreeO emulator and saving initial model...")
                self.gpt.atomic_save(self.tree_filename)
                # atomic_joblib_dump(self.gpt, self.tree_filename)

        self.last_mtime = os.path.getmtime(self.tree_filename)

        self.Xcache = []
        self.Ycache = []

        self.training_enabled = kwargs.get('train', True)
        self.prediction_enabled = kwargs.get('predict', True)

    # update tree with buffer values
    def train(self, x, y, z):
        if self.training_enabled:
            if self.mpi_size == 1  or self.mpi_rank == 1:
                X_train = x.reshape(1, -1)
                y_train = y.reshape(1, -1)

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
                    self.gpt.atomic_save(self.tree_filename)
                    # atomic_joblib_dump(self.gpt, self.tree_filename)
        else:
            print("Training is disabled for this emulator instance.")
    
    # predict for x
    def predict(self, x):
        if self.prediction_enabled:
            if self.mpi_size == 1 or self.mpi_rank == 0:

                # load tree if file was updated
                current_mtime = os.path.getmtime(self.tree_filename)
                if current_mtime != self.last_mtime:
                    self.gpt = joblib.load(self.tree_filename)
                    self.last_mtime = current_mtime

                # predict
                X_test = x.reshape(1,-1)
                y_pred, y_std = self.gpt.predict(X_test)

                return (y_pred[0], y_std[0])
            else:
                return (np.array([None]), np.array([None]))
        else:
            print("Prediction is disabled for this emulator instance.")
            return (np.array([None]), np.array([None]))


__plugins__ = {"pygptreeo": pyGPtreeoEmulator}
