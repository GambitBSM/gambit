"""
PocoMC scanner
==============
"""

import pickle
import numpy as np
import os

from utils import copydoc, version, with_mpi, store_pt_data, get_directory
if with_mpi:
    from utils import MPIPool, MPI
    
try:
    import pocomc
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

n_particles (1000):  Number of preconditioned points
pkl_name ('ocomc.pkl'):  File name where results will be pickled
    """
    __version__ = pocomc_version
    ids=None

    @copydoc(pocomc_Sampler)
    def __init__(self, pkl_name="pocomc.pkl", n_particles=1000, **kwargs):
        
        super().__init__(use_mpi=True, use_resume=True)
        
        self.assign_aux_numbers("Posterior")
        if self.mpi_rank == 0:
            self.printer.new_stream("txt", synchronised=False)
        
            self.n_particles = n_particles
            if 'n_particles' in self.init_args:
                self.n_particles = self.init_args['n_particles']
                del self.init_args['n_particles']
            
            self.log_dir = get_directory("PocoMC", **kwargs)
            self.pkl_name = pkl_name
        else:
            self.log_dir = None
            
        if self.mpi_size > 1:
            self.log_dir = MPI.COMM_WORLD.bcast(self.log_dir, root=0)
        
        PocoMC.ids = store_pt_data(resume=self.printer.resume_mode(), log_dir=self.log_dir)
        
    @classmethod
    def my_like(cls, params):
        lnew = cls.loglike_hypercube(params)
        cls.ids.save(tuple(params), (cls.mpi_rank, cls.point_id))
        
        return lnew
        
    @staticmethod
    def log_prior(x):
        if np.any(x < 0.0) or np.any(x > 1.0):
            return -np.inf
        else:
            return 0.0
    
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
            if prior_samples is None:
                prior_samples = np.random.rand(self.n_particles, self.dim).astype(np.float32)
            self.sampler = self.make_sampler(self.n_particles,
                                             self.dim,
                                             log_likelihood=self.my_like,
                                             log_prior=self.log_prior,
                                             bounds=np.array([[0.0, 1.0]]*self.dim),
                                             vectorize_likelihood=False,
                                             vectorize_prior=False,
                                             infer_vectorization=False,
                                             output_dir=self.log_dir,
                                             **self.init_args)
            self.sampler.run(prior_samples, 
                             save_every=save_every, 
                             resume_state_path=self.get_last_save(save_every, resume_state_path),
                             **self.run_args)
        else:
            with MPIPool() as pool:
                if pool.is_master():
                    if prior_samples is None:
                        prior_samples = np.random.rand(self.n_particles, self.dim).astype(np.float32)
                    self.sampler = self.make_sampler(self.n_particles,
                                                     self.dim,
                                                     log_likelihood=self.my_like,
                                                     log_prior=self.log_prior,
                                                     bounds=np.array([[0.0, 1.0]]*self.dim),
                                                     vectorize_likelihood=False,
                                                     vectorize_prior=False,
                                                     infer_vectorization=False,
                                                     output_dir=self.log_dir,
                                                     pool=pool,
                                                     **self.init_args)
                    self.sampler.run(prior_samples, 
                                     save_every=save_every, 
                                     resume_state_path=self.get_last_save(save_every, resume_state_path),
                                     **self.run_args)
                else:
                    pool.wait()
            
        PocoMC.ids.load_saves()
        
        if self.mpi_rank == 0:
            
            results = self.sampler.results
            pts = results["samples"]
            wts = results["logw"]
            stream = self.printer.get_stream("txt")
            stream.reset()
            
            for pt in pts:
                if tuple(pt) in PocoMC.ids.saves:
                    save = PocoMC.ids.saves[tuple(pt)]
                    stream.print(1.0, "Posterior", save[0], save[1])
                else:
                    print("warning: point ", tuple(pt), " has no correponding id.")

            stream.flush()
            
            if self.pkl_name:
                results["phys_samples"] = np.array([self.transform_to_vec(pt) for pt in results["samples"]])
                results["parameter_names"] = self.parameter_names
                with open(self.log_dir + self.pkl_name, "wb") as f:
                    pickle.dump(self.sampler.results, f)

    @copydoc(pocomc_Sampler_run)
    def run(self):
        self.run_internal(**self.run_args)
        return 0


__plugins__ = {"pocomc": PocoMC}
