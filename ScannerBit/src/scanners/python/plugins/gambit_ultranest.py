"""
Ultranest scanners
==================
"""

import pickle
import numpy as np
from packaging.version import parse    
from utils import copydoc, version, get_directory, store_pt_data, with_mpi
if with_mpi:
    from utils import MPI

try:
    import ultranest
    ultranest_version = version(ultranest)
    ultranest_ReactiveNestedSampler = ultranest.ReactiveNestedSampler
    ultranest_ReactiveNestedSampler_run = ultranest.ReactiveNestedSampler.run
except:
    __error__ = 'ultranest pkg not installed'
    ultranest_version = 'n/a'
    ultranest_ReactiveNestedSampler = None
    ultranest_ReactiveNestedSampler_run = None

import scanner_plugin as splug


class ReactiveUltranest(splug.scanner):
    """
Ultranest reactive sampler.  See https://johannesbuchner.github.io/UltraNest/index.html

log_dir ('ultranest'):  output directory name.  Defined in given default path.
pkl_name ('ultranest.pkl'):  File name where results will be pickled
    """

    __version__ = ultranest_version
    
    def ultra_like(self, params):
        lnew = self.loglike_hypercube(params)
        self.ids.save(tuple(params), (self.mpi_rank, self.point_id))
        
        return lnew
    
    @copydoc(ultranest_ReactiveNestedSampler)
    def __init__(self, pkl_name='ultranest.pkl', log_dir="ultranest", **kwargs):
        
        super().__init__(use_mpi=True, use_resume=True)
        if self.mpi_size > 1 and parse(ultranest.__version__) < parse("3.6.3"):
            print("WARNING: UltraNest current version is {0}.  Versions < 3.6.3 are bugged when using MPI.".format(ultranest.__version__))
        
        self.assign_aux_numbers("Posterior")
        if self.mpi_rank == 0:
            self.pkl_name = pkl_name
            self.printer.new_stream("txt", synchronised=False)
            self.log_dir = get_directory(log_dir, **kwargs)
        else:
            self.log_dir = None
            
        if self.mpi_size > 1:
            self.log_dir = MPI.COMM_WORLD.bcast(self.log_dir, root=0)
            
        self.ids = store_pt_data(resume=self.printer.resume_mode(), log_dir=self.log_dir)

        self.sampler = ultranest.ReactiveNestedSampler(
            ["unit[{0}]".format(i) for i in range(self.dim)],
            self.ultra_like,
            resume='resume-similar' if self.printer.resume_mode() else 'overwrite',
            log_dir=self.log_dir,
            **self.init_args)
    
    def run_internal(self, **kwargs):
        
        self.sampler.run(**kwargs)
        self.ids.load_saves()
        
        if self.mpi_rank == 0:
            result = self.sampler.results
            wts = result["weighted_samples"]["weights"]
            pts = result["weighted_samples"]["points"]
            stream = self.printer.get_stream("txt")
            stream.reset()
            for wt, pt in zip(wts, pts):
                if tuple(pt) in self.ids.saves:
                    save = self.ids.saves[tuple(pt)]
                    stream.print(wt, "Posterior", save[0], save[1])
                else:
                    print("warning: point ", tuple(pt), " has no correponding id.")
            stream.flush()
            
            if self.pkl_name:
                for i in range(self.dim):
                    result["weighted_samples"]["points"][i] = self.transform_to_vec(pts[i])
                result["weighted_samples"]["parameter_names"] = self.parameter_names
                with open(self.log_dir + self.pkl_name, "wb") as f:
                    pickle.dump(result, f)
    
    @copydoc(ultranest_ReactiveNestedSampler_run)
    def run(self):
        self.run_internal(**self.run_args)
        return 0


__plugins__ = {"reactive_ultranest": ReactiveUltranest}
