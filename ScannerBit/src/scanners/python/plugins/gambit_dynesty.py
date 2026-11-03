"""
Dynesty scanners
================

The static and dynamic Dynesty classes are implemented separately.

We don't use the Dynesty checkpointing/saving functionality, as it
attempts to pickle the loglikelihood function etc.
"""

import pickle
import numpy as np
import copy
from utils import copydoc, version, with_mpi, get_directory
if with_mpi:
    from utils import MPIPool

try:
    import dynesty
    dynesty_version = version(dynesty)
    dynesty_NestedSampler = dynesty.NestedSampler
    dynesty_NestedSampler_run_nested = dynesty.NestedSampler.run_nested
    dynesty_DynamicNestedSampler = dynesty.DynamicNestedSampler
    dynesty_DynamicNestedSampler_run_nested = dynesty.DynamicNestedSampler.run_nested
except:
    __error__ = 'dynesty pkg not installed'
    dynesty_version = 'n/a'
    dynesty_NestedSampler = None
    dynesty_NestedSampler_run_nested = None
    dynesty_DynamicNestedSampler = None
    dynesty_DynamicNestedSampler_run_nested = None

import scanner_plugin as splug


class StaticDynesty(splug.scanner):
    """
Dynesty nested sampler with static number of live points.  See https://dynesty.readthedocs.io/en/latest/index.html

We add these additional parameters:

    pkl_name ('static_dynesty.pkl'):  File name where results will be pickled
    filename ('dynesty.save'):  Filename where temp data will be stored
    """

    __version__ = dynesty_version

    @copydoc(dynesty_NestedSampler)
    def __init__(self, pkl_name='static_dynesty.pkl', filename='dynesty.save', **kwargs):
        super().__init__(use_mpi=True, use_resume=True)
        
        self.assign_aux_numbers("Posterior")
        if self.mpi_rank == 0:
            self.log_dir = get_directory("StaticDynesty", **kwargs)
            self.pkl_name = pkl_name
            self.printer.new_stream("txt", synchronised=False)
            self.filename = self.log_dir + filename
        
    @classmethod
    def gambit_loglike(cls, params):
        lnew = cls.loglike_hypercube(params)
        
        return (lnew, np.array([cls.mpi_rank, cls.point_id]))
    
    @staticmethod
    def gambit_transform(params):
        return params

    @copydoc(dynesty_NestedSampler_run_nested)
    def run(self):
        if self.mpi_size == 1:
            if self.printer.resume_mode():
                self.sampler = dynesty.NestedSampler.restore(self.filename)
                
                self.sampler.run_nested(checkpoint_file=self.filename, resume=True, **self.run_args)
            else:
                self.sampler = dynesty.NestedSampler(
                    self.gambit_loglike,
                    self.gambit_transform,
                    self.dim, 
                    blob=True, 
                    **self.init_args)
                
                self.sampler.run_nested(checkpoint_file=self.filename, **self.run_args)
        
        else:
            with MPIPool() as pool:
                if self.printer.resume_mode():
                    self.sampler = dynesty.NestedSampler.restore(self.filename, pool=pool)
                
                    self.sampler.run_nested(checkpoint_file=self.filename, resume=True, **self.run_args)
                else:
                    if pool.is_master():
                        self.sampler = dynesty.NestedSampler(
                            self.gambit_loglike,
                            self.gambit_transform,
                            self.dim, 
                            blob=True, 
                            pool=pool, 
                            **self.init_args)
                        
                        self.sampler.run_nested(checkpoint_file=self.filename, **self.run_args)
                    else:
                        pool.wait()

        if self.mpi_rank == 0:

            wts = self.sampler.results["logwt"]
            blobs = self.sampler.results["blob"]
            
            stream = self.printer.get_stream("txt")
            stream.reset()
            
            for wt, blob in zip(wts, blobs):
                stream.print(np.exp(wt), "Posterior", blob[0], blob[1])
                
            stream.flush()
            
            if self.pkl_name:
                results = {
                    "results": self.sampler.results,
                    "samples": np.array([self.transform_to_vec(p) for p in self.sampler.results["samples_u"]]),
                    "parameter_names": self.parameter_names
                    }
                
                with open(self.log_dir + self.pkl_name, "wb") as f:
                    pickle.dump(results, f)
                    
        return 0

class DynamicDynesty(splug.scanner):
    """
    Dynesty nested sampler with dynamic number of live points.  See https://dynesty.readthedocs.io/en/latest/index.html

    We add these additional parameters:

        pkl_name ('dynamic_dynesty.pkl'):  File name where results will be pickled
        filename ('dynesty.save'):  Filename where temp data will be stored
    """

    __version__ = dynesty_version

    @copydoc(dynesty_DynamicNestedSampler)
    def __init__(self, pkl_name='dynamic_dynesty.pkl', filename='dynesty.save', **kwargs):
        super().__init__(use_mpi=True, use_resume=True)
        
        self.assign_aux_numbers("Posterior")
        if self.mpi_rank == 0:
            self.log_dir = get_directory("DynamicDynesty", **kwargs)
            self.pkl_name = pkl_name
            self.printer.new_stream("txt", synchronised=False)
            self.filename = self.log_dir + filename
    
    @classmethod
    def gambit_loglike(cls, params):
        lnew = cls.loglike_hypercube(params)
        
        return (lnew, np.array([cls.mpi_rank, cls.point_id]))

    @staticmethod
    def gambit_transform(params):
        return params

    @copydoc(dynesty_DynamicNestedSampler_run_nested)
    def run(self):
        if self.mpi_size == 1:
            if self.printer.resume_mode():
                self.sampler = dynesty.DynamicNestedSampler.restore(self.filename)
                
                self.sampler.run_nested(checkpoint_file=self.filename, resume=True, **self.run_args)
            else:
                self.sampler = dynesty.DynamicNestedSampler(
                    self.gambit_loglike,
                    self.gambit_transform,
                    self.dim, 
                    blob=True, 
                    **self.init_args)
                
                self.sampler.run_nested(checkpoint_file=self.filename, **self.run_args)
        
        else:
            with MPIPool() as pool:
                if self.printer.resume_mode():
                    self.sampler = dynesty.DynamicNestedSampler.restore(self.filename, pool=pool)
                
                    self.sampler.run_nested(checkpoint_file=self.filename, resume=True, **self.run_args)
                else:
                    if pool.is_master():
                        self.sampler = dynesty.DynamicNestedSampler(
                            self.gambit_loglike,
                            self.gambit_transform,
                            self.dim, 
                            blob=True, 
                            pool=pool, 
                            **self.init_args)
                        
                        self.sampler.run_nested(checkpoint_file=self.filename, **self.run_args)
                    else:
                        pool.wait()

        if self.mpi_rank == 0:

            wts = self.sampler.results["logwt"]
            blobs = self.sampler.results["blob"]
            
            stream = self.printer.get_stream("txt")
            stream.reset()
            
            for wt, blob in zip(wts, blobs):
                stream.print(np.exp(wt), "Posterior", blob[0], blob[1])
                
            stream.flush()
            
            if self.pkl_name:
                results = {
                    "results": self.sampler.results,
                    "samples": np.array([self.transform_to_vec(p) for p in self.sampler.results["samples_u"]]),
                    "parameter_names": self.parameter_names
                    }
                
                with open(self.log_dir + self.pkl_name, "wb") as f:
                    pickle.dump(results, f)
                    
        return 0


__plugins__ = {"static_dynesty": StaticDynesty,
               "dynamic_dynesty": DynamicDynesty}
