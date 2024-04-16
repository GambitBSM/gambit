"""
Zeus scanner
============
"""

import numpy as np
import pickle
from utils import copydoc, version, get_directory, with_mpi
if with_mpi:
    from utils import MPIPool

try:
    import zeus
    zeus_version = version(zeus)
    zeus_EnsembleSampler = zeus.EnsembleSampler
    zeus_EnsembleSampler_run_mcmc = zeus.EnsembleSampler.run_mcmc
    MinIter_Callback = zeus.callbacks.MinIterCallback
    ParallelSplitR_Callback = zeus.callbacks.ParallelSplitRCallback
    SplitR_Callback = zeus.callbacks.SplitRCallback
    Autocorrelation_Callback = zeus.callbacks.AutocorrelationCallback
    SaveProgress_Callback = zeus.callbacks.SaveProgressCallback
    if with_mpi:
        from zeus import ChainManager
except:
    __error__='zeus-mcmc pkg not installed'
    zeus_version ='n/a'
    zeus_EnsembleSampler = None
    zeus_EnsembleSampler_run_mcmc = None
    MinIter_Callback = None
    ParallelSplitR_Callback = None
    SplitR_Callback = None
    Autocorrelation_Callback = None
    SaveProgress_Callback = None

import scanner_plugin as splug

@copydoc(MinIter_Callback, prefix="MinIterCallback:\n")
@copydoc(ParallelSplitR_Callback, prefix="ParallelSplitRCallback:\n")
@copydoc(SplitR_Callback, prefix="SplitRCallback:\n")
@copydoc(Autocorrelation_Callback, prefix="AutocorrelationCallback:\n")
@copydoc(SaveProgress_Callback, prefix="SaveProgressCallback:\n")
class Zeus(splug.scanner):
    """
An ensamble slice sampler.  Unfortunately, resume does not work on this sampler.  See https://zeus-mcmc.readthedocs.io/en/latest/index.html

There are additional arguments:
    
    nwalkers (8):  Number of walkers
    pkl_name ('zeus.pkl'):  File name where results will be pickled
    use_chain_manager (False):  Use the internal chain manager to manage mpi processes.  This will run mpi_size chains in parrellel
    
AVAILABLE CALLBACKS
-------------------"""

    __version__ = zeus_version

    def callbacks(self, kwargs, chainmaster=None):
        """
        :returns: Callback that saves results
        """
        
        ret = []
        
        if 'SaveProgressCallback' in kwargs:
            if 'filename' in kwargs['SaveProgressCallback']:
                kwargs['SaveProgressCallback']['filename'] = self.log_dir + kwargs['SaveProgressCallback']['filename']
            else:
                kwargs['SaveProgressCallback']['filename'] = self.log_dir + "chains.h5"
            
            ret.append(zeus.callbacks.SaveProgressCallback(**kwargs['SaveProgressCallback']))
    
        if 'AutocorrelationCallback' in kwargs:
            ret.append(zeus.callbacks.AutocorrelationCallback(**kwargs['AutocorrelationCallback']))
            
        if 'SplitRCallback' in kwargs:
            ret.append(zeus.callbacks.SplitRCallback(**kwargs['SplitRCallback']))
            
        if 'ParallelSplitRCallback' in kwargs:
            ret.append(zeus.callbacks.ParallelSplitRCallback(chainmaster=chainmaseter, **kwargs['ParallelSplitRCallback']))
            
        if 'MinIterCallback' in kwargs:
            ret.append(zeus.callbacks.MinIterCallback(**kwargs['MinIterCallback']))
            
        if len(ret) == 0:
            return None
        else:
            return ret
    
    @classmethod
    def my_like(cls, params):
        
        if ((params < 1.0) & (params > 0.0)).all():
            lnew = cls.loglike_hypercube(params)
            
            return (lnew, cls.mpi_rank, cls.point_id)
        else:
            return  (-np.inf, -1, -1)

    @copydoc(zeus_EnsembleSampler)
    def __init__(self, nwalkers=8, pkl_name='zeus.pkl', use_chain_manager=False, **kwargs):
        super().__init__(use_mpi=True, use_resume=False)

        self.nwalkers = nwalkers
        if 'nwalkers' in self.init_args:
            self.nwalkers = self.init_args['nwalkers']
            del self.init_args['nwalkers']
        
        self.use_cm = use_chain_manager
        self.assign_aux_numbers("Posterior")
        if self.mpi_rank == 0 or self.use_cm:
            self.log_dir = get_directory("Zeus", **kwargs)
            self.pkl_name = pkl_name
            self.printer.new_stream("txt", synchronised=False)


    def run_internal(self, nsteps=1000, start=None, **kwargs):
            
        if self.mpi_size == 1:
            if start is None:
                start = np.random.rand(self.nwalkers, self.dim)
            self.sampler = zeus.EnsembleSampler(self.nwalkers, 
                                                self.dim, 
                                                self.my_like, 
                                                blobs_dtype=[("rank", int), ("ptid", int)], 
                                                **self.init_args)
            self.sampler.run_mcmc(start, 
                                  nsteps, 
                                  callbacks=self.callbacks(self.args), 
                                  **kwargs)
        else:
            if self.use_cm:
                with ChainManager(self.mpi_size) as cm:
                    if start is None:
                        start = np.random.rand(self.nwalkers, self.dim)
                    self.sampler = zeus.EnsembleSampler(self.nwalkers, 
                                                        self.dim, 
                                                        self.my_like, 
                                                        blobs_dtype=[("rank", int), ("ptid", int)], pool=cm.get_pool, 
                                                        **self.init_args)
                    self.sampler.run_mcmc(start,
                                          nsteps,
                                          callbacks=self.callbacks(self.args, chainmaster=cm), 
                                          **kwargs)
            else:
                with MPIPool() as pool:
                    if pool.is_master():
                        if start is None:
                            start = np.random.rand(self.nwalkers, self.dim)
                        self.sampler = zeus.EnsembleSampler(self.nwalkers, 
                                                            self.dim, 
                                                            self.my_like, 
                                                            blobs_dtype=[("rank", int), ("ptid", int)], pool=pool, **self.init_args)
                        self.sampler.run_mcmc(start, 
                                              nsteps,
                                              callbacks=self.callbacks(self.args), 
                                              **kwargs)
                    else:
                        pool.wait()
        
        if self.mpi_rank == 0 or self.use_cm:
            stream = self.printer.get_stream("txt")
            stream.reset()
            blobs = self.sampler.get_blobs(flat=True)
            blobs = np.array([blobs['rank'], blobs["ptid"]])
            
            for i in range(self.mpi_size):
                us, cs = np.unique(blobs[1, blobs[0, :]==i], return_counts=True)
                
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

    @copydoc(zeus_EnsembleSampler_run_mcmc)
    def run(self):
        self.run_internal(**self.run_args)
        return 0
        

__plugins__ = {"zeus": Zeus}
