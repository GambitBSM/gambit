"""
Nessai scanner
==============
"""

import pickle
import numpy as np
from utils import copydoc, get_directory, version, with_mpi, store_pt_data
if with_mpi:
    from utils import MPIPool, MPI

try:
    import nessai
    from nessai.flowsampler import FlowSampler
    from nessai.model import Model
    from nessai.utils import setup_logger
    from nessai.utils.multiprocessing import initialise_pool_variables
    nessai_version = version(nessai)
    FlowSampler_run = FlowSampler.run
except:
    __error__ = 'nessai pkg not installed'
    nessai_version = 'n/a'
    FlowSampler = None
    FlowSampler_run = None
    class Model:
        pass

import scanner_plugin as splug


class Gambit_Model(Model):
    def __init__(self, gambit):
        self.names = ["unit_{0}".format(i) for i in range(gambit.dim)]
        self.bounds = {n: [0.0, 1.0] for n in self.names}
        self.gambit = gambit
        self.pt = np.zeros(len(self.names))

    def log_prior(self, params):
        return np.log(self.in_bounds(params), dtype="float")

    def log_likelihood(self, params):
        for i in range(len(self.names)):
            self.pt[i] = params[self.names[i]]
        lnew = self.gambit.loglike_hypercube(self.pt)
        self.gambit.ids.save((tuple(self.pt)), (self.gambit.mpi_rank, self.gambit.point_id))
        
        return lnew


class GambitFlowSampler(splug.scanner):
    """
Nessai nested sampler. This operates on the unit hypercube as the nessai implementation requires bounds for each parameter, which may not exist in physical parameters.  See https://nessai.readthedocs.io/en/latest/index.html

We defined the additional parameters:
    output ('nessai'):  output directory name.  Defined in given default path.
    logger (True):  Whether to use the logger
    pkl_name ('nessai.pkl'):  File name where results will be pickled
    """

    __version__ = nessai_version

    @copydoc(FlowSampler)
    def __init__(self, logger=True, pkl_name='nessai.pkl', output="nessai", **kwargs):

        super().__init__(use_mpi=True, use_resume=True)
        
        self.assign_aux_numbers("Posterior")
        if self.mpi_rank == 0:
            self.printer.new_stream("txt", synchronised=False)
            self.pkl_name = pkl_name
            self.output_dir = get_directory(output, **kwargs)
        else:
            self.output_dir = None
            
        if self.mpi_size > 1:
            self.output_dir = MPI.COMM_WORLD.bcast(self.output_dir, root=0)
            
        self.ids = store_pt_data(resume=self.printer.resume_mode(), log_dir=self.output_dir)
        
        if logger:
            setup_logger(output=self.output_dir)

    def run_internal(self, **kwargs):
        model = Gambit_Model(self)
        
        if self.mpi_size == 1:
            self.sampler = FlowSampler(model,
                                       resume=self.printer.resume_mode(),
                                       output=self.output_dir,
                                       **self.init_args)
            self.sampler.run(**kwargs)
        else:
            initialise_pool_variables(model)
            with MPIPool(use_join=True) as pool:
                if pool.is_master():
                    self.sampler = FlowSampler(model, 
                                               pool=pool,
                                               resume=self.printer.resume_mode(),
                                               output=self.output_dir, 
                                               **self.init_args)
                    self.sampler.run(**kwargs)
                else:
                    pool.wait()
                    
        
        self.ids.load_saves()
                
        if self.mpi_rank == 0:
            stream = self.printer.get_stream("txt")
            stream.reset()
            
            results = self.sampler.nested_samples
            samples_u = np.array([[result[p] for p in model.names] for result in results])

            for pt in samples_u:
                if tuple(pt) in self.ids.saves:
                    save = self.ids.saves[tuple(pt)]
                    stream.print(1.0, "Posterior", save[0], save[1])
                else:
                    print("warning: point ", tuple(pt), " has no correponding id.")
            stream.flush()
            
            if self.pkl_name:
                results = {
                    "samples_u": samples_u,
                    "samples": np.array([self.transform_to_vec(pt) for pt in samples_u]),
                    "parameter_names": self.parameter_names
                }
                with open(self.output_dir + self.pkl_name, "wb") as f:
                    pickle.dump(results, f)

    @copydoc(FlowSampler_run)
    def run(self):
        self.run_internal(**self.run_args)
        return 0


__plugins__ = {"nessai_flow_sampler": GambitFlowSampler}
