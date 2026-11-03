"""
Emcee scanner
=============
"""

import numpy as np
import pickle
from utils import copydoc, version, get_directory, with_mpi
if with_mpi:
    from utils import MPIPool
    
try:
    import emcee
    emcee_version = version(emcee)
    emcee_EnsembleSampler = emcee.EnsembleSampler
    emcee_EnsembleSampler_run_mcmc = emcee.EnsembleSampler.run_mcmc
except:
    __error__ = 'emcee pkg not installed'
    emcee_version = 'n/a'
    emcee_EnsembleSampler = None
    emcee_EnsembleSampler_run_mcmc = None

import scanner_plugin as splug

class Emcee(splug.scanner):
    """
An affine invariant ensemble sampler.  See https://emcee.readthedocs.io/en/stable/

There are additional arguments:
    
    nwalkers (1):  Number of walkers
    filename ('emcee.h5'): For passing the name of a h5 file to which to save results using the emcee writer.
    pkl_name ('emcee.pkl'):  File name where results will be pickled
    """
    
    __version__ = emcee_version
    
    def backend(self, filename, reset):
        """
        :returns: Backend with h5 file to save results
        """
        if not filename:
            return None

        backend = emcee.backends.HDFBackend(filename)
        if reset:
            backend.reset(self.nwalkers, self.dim)

        return backend
        
    @classmethod
    def my_like(cls, params):
        
        if ((params < 1.0) & (params > 0.0)).all():
            lnew = cls.loglike_hypercube(params)
            
            return (lnew, cls.mpi_rank, cls.point_id)
        else:
            return  (-np.inf, -1, -1)

    @copydoc(emcee_EnsembleSampler)
    def __init__(self, nwalkers=1, pkl_name='emcee.pkl', filename='emcee.h5', **kwargs):
        
        super().__init__(use_mpi=True, use_resume=True)
        
        self.assign_aux_numbers("Posterior")
        if self.mpi_rank == 0:
            self.printer.new_stream("txt", synchronised=False)
        
            self.nwalkers = nwalkers
            if 'nwalkers' in self.init_args:
                self.nwalkers = self.init_args['nwalkers']
                del self.init_args['nwalkers']
            
            self.log_dir = get_directory("Emcee", **kwargs)
            self.filename = self.log_dir + filename
            self.reset = not self.printer.resume_mode()
            self.pkl_name = pkl_name
        

    def run_internal(self, nsteps=5000, progress=True, initial_state=None, **kwargs):
        if self.mpi_size == 1:
            if initial_state is None:
                initial_state = np.random.rand(self.nwalkers, self.dim)
                
            self.sampler = emcee.EnsembleSampler(self.nwalkers,
                                                 self.dim,
                                                 self.my_like,
                                                 backend=self.backend(self.filename, self.reset),
                                                 **self.init_args)
            
            self.sampler.run_mcmc(initial_state, nsteps,
                                progress=progress, **kwargs)
        else:
            with MPIPool() as pool:
                if pool.is_master():
                    if initial_state is None:
                        initial_state = np.random.rand(self.nwalkers, self.dim)
                        
                    self.sampler = emcee.EnsembleSampler(self.nwalkers,
                                                         self.dim,
                                                         self.my_like,
                                                         backend=self.backend(self.filename, self.reset),
                                                         pool=pool,
                                                         **self.init_args)
                    
                    self.sampler.run_mcmc(initial_state, nsteps,
                                        progress=progress, **kwargs)
                else:
                    pool.wait()
        
        if self.mpi_rank == 0:
            stream = self.printer.get_stream("txt")
            stream.reset()
            blobs = np.array(self.sampler.get_blobs(flat=True))
            
            for i in range(self.mpi_size):
                us, cs = np.unique(blobs[blobs[:, 0]==i, 1], return_counts=True)
                
                for u, c in zip(us, cs):
                    stream.print(c, "Posterior", i, u)
            stream.flush()
            
            if self.pkl_name:
                results = {
                    "samples_u": self.sampler.get_chain(flat=True),
                    "samples": np.array([self.transform_to_vec(p) for p in self.sampler.get_chain(flat=True)]),
                    "parameter_names": self.parameter_names
                }
                with open(self.log_dir + self.pkl_name, "wb") as f:
                    pickle.dump(results, f)
        
    @copydoc(emcee_EnsembleSampler_run_mcmc)
    def run(self):
        self.run_internal(**self.run_args)
        return 0


__plugins__ = {"emcee": Emcee}
