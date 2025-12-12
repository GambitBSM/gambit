"""
PocoMC scanner
==============
"""

import pickle
import numpy as np
import os

from utils import copydoc, version, with_mpi, get_directory
if with_mpi:
    from utils import MPIPool, MPI
    
try:
    import pocomc
    from scipy.stats import uniform
    pocomc_version = version(pocomc)
    pocomc_Sampler = pocomc.Sampler
    pocomc_Sampler_run = pocomc.Sampler.run
except:
    __error__ = "pocomc pkg not installed"
    pocomc_version = "n/a"
    pocomc_Sampler = None
    pocomc_Sampler_run = None

import scanner_plugin as splug

class PocoMC(splug.scanner):
    """
A Python implementation of Preconditioned Monte Carlo.  Note, this scanner only uses single precision.  See https://pocomc.readthedocs.io/en/latest/index.html

There are additional arguments:

pkl_name ('ocomc.pkl'):  File name where results will be pickled
    """
    __version__ = pocomc_version
    ids=None

    @copydoc(pocomc_Sampler)
    def __init__(self, pkl_name="pocomc.pkl", **kwargs):
        
        super().__init__(use_mpi=True, use_resume=True)
        
        self.assign_aux_numbers("Posterior")
        if self.mpi_rank == 0:
            self.printer.new_stream("txt", synchronised=False)
            
            self.log_dir = get_directory("PocoMC", **kwargs)
            self.pkl_name = pkl_name
        else:
            self.log_dir = None
            
        if self.mpi_size > 1:
            self.log_dir = MPI.COMM_WORLD.bcast(self.log_dir, root=0)
        
    @classmethod
    def my_like(cls, params):
        lnew = cls.loglike_hypercube(params)

        return lnew, cls.mpi_rank, cls.point_id
    
    def make_sampler(self, *arg, output_label="pmc", **kwargs):
        self.output_label = output_label

        return pocomc.Sampler(*arg, output_label=output_label, **kwargs)
    
    def get_last_save(self, save_every, resume_state_path):
        
        if not self.printer.resume_mode():
            i = save_every
            while(True):
                path = os.path.abspath("{0}_{1}.state".format(self.log_dir + self.output_label, i).strip())
                if os.path.exists(path):
                    os.remove(path)
                    i += save_every
                else:
                    break
            return None
        elif resume_state_path:
            print("using resume_state_path =", resume_state_path)
            return resume_state_path
        else:
            i = save_every
            while(True):
                path = os.path.abspath("{0}_{1}.state".format(self.log_dir + self.output_label, i).strip())
                if os.path.exists(path):
                    resume_state_path = path
                    i += save_every
                else:
                    break
                
            print("using resume_state_path =", resume_state_path)
            return resume_state_path
            
    def run_internal(self, prior_samples=None, save_every=1, resume_state_path=None, **kwargs):

        if self.mpi_size == 1:
            self.sampler = self.make_sampler(pocomc.Prior(self.dim*[uniform(loc=0.0, scale=1.0)]),
                                             self.my_like,
                                             n_dim=self.dim,
                                             blobs_dtype=[("rank", int), ("point_id", int)],
                                             output_dir=self.log_dir,
                                             **self.init_args)

            if self.printer.resume_mode():
                self.sampler.run(save_every=save_every,
                             resume_state_path=self.get_last_save(save_every, resume_state_path),
                             **self.run_args)
            else:
                self.sampler.run(save_every=save_every,
                             **self.run_args)
        else:
            with MPIPool(comm=self.mpi_comm) as pool:
                if pool.is_master():
                    self.sampler = self.make_sampler(pocomc.Prior(self.dim*[uniform(loc=0.0, scale=1.0)]),
                                                     self.my_like,
                                                     n_dim=self.dim,
                                                     blobs_dtype=[("rank", int), ("point_id", int)],
                                                     output_dir=self.log_dir,
                                                     pool=pool,
                                                     **self.init_args)
                    if self.printer.resume_mode():
                        self.sampler.run(save_every=save_every,
                                        resume_state_path=self.get_last_save(save_every, resume_state_path),
                                        **self.run_args)
                    else:
                        self.sampler.run(save_every=save_every,
                                        **self.run_args)
                else:
                    pool.wait()
        
        if self.mpi_rank == 0:

            samples, weights, logl, logp, blobs = self.sampler.posterior(return_blobs=True)

            stream = self.printer.get_stream("txt")
            stream.reset()
            
            for weight, rank, pointid in zip(weights, blobs["rank"], blobs["point_id"]):
                stream.print(weight, "Posterior", rank, pointid)

            stream.flush()
            
            if self.pkl_name:
                results = {}
                results["phys_samples"] = np.array([self.transform_to_vec(pt) for pt in samples])
                results["weights"] = weights
                results["parameter_names"] = self.parameter_names
                with open(self.log_dir + self.pkl_name, "wb") as f:
                    pickle.dump(results, f)

    @copydoc(pocomc_Sampler_run)
    def run(self):
        self.run_internal(**self.run_args)
        return 0


__plugins__ = {"pocomc": PocoMC}
