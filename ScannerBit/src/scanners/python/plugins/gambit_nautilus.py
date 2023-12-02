"""
Nautilus scanner
================
"""

from utils import copydoc, version, with_mpi, get_directory
import pickle
import numpy as np
if with_mpi:
    from utils import MPIPool
    
try:
    import nautilus
    nautilus_version = version(nautilus)
    nautilus_Sampler = nautilus.Sampler
    nautilus_Sampler_run = nautilus.Sampler.run
except:
    __error__ = "nautilus-sampler pkg not installed"
    nautilus_version = "n/a"
    nautilus_Sampler = None
    nautilus_Sampler_run = None

import scanner_plugin as splug

class Nautilus(splug.scanner):
    """
A nested sampler that selects points by training a neural net using the live points.  See https://nautilus-sampler.readthedocs.io/en/stable/index.html

We defined the additional parameters:
    filename ('nautilus.h5'): For passing the name of a h5 file to which to save results using the nautilus writer.
    pkl_name ('nautilus.pkl'):  File name where results will be pickled
    """
    __version__ = nautilus_version
    
    @copydoc(nautilus_Sampler)
    def __init__(self, pkl_name = "nautilus.pkl", filename='nautilus.hdf5', **kwargs):
        super().__init__(use_mpi=True, use_resume=True)
        
        self.assign_aux_numbers("Posterior")
        if self.mpi_rank == 0:
            self.prior = nautilus.Prior()
            names = ["unit[{0}]".format(i) for i in range(self.dim)]
            for key in names:
                self.prior.add_parameter(key)
            self.printer.new_stream("txt", synchronised=False)
            self.pkl_name = pkl_name
            self.log_dir = get_directory("nautilus", **kwargs)
            self.filename = self.log_dir + filename
            
    @classmethod
    def my_like(cls, params):
        lnew = cls.loglike_hypercube(params)

        return (lnew, cls.mpi_rank, cls.point_id)

    @copydoc(nautilus_Sampler_run)
    def run(self):
        
        if self.mpi_size == 1:
            sampler = nautilus.Sampler(self.prior, 
                                       self.my_like, 
                                       filepath=self.filename, 
                                       resume=self.printer.resume_mode(), 
                                       pass_dict=False, 
                                       **self.init_args)
            sampler.run(**self.run_args)
        else:
            with MPIPool() as pool:
                if pool.is_master():
                    sampler = nautilus.Sampler(self.prior, 
                                               self.my_like, 
                                               filepath=self.filename, 
                                               resume=self.printer.resume_mode(), 
                                               pass_dict=False, 
                                               pool=pool,
                                               **self.init_args)
                    sampler.run(**self.run_args)
                else:
                    pool.wait()
            
        if self.mpi_rank == 0:
            pts, log_ws, log_ls, blobs = sampler.posterior(return_blobs=True)
            
            stream = self.printer.get_stream("txt")
            stream.reset()
            
            for log_w, blob in zip(log_ws, blobs):
                stream.print(np.exp(log_w), "Posterior", blob[0], blob[1])
            
            stream.flush()
            
            if self.pkl_name:
                results = {
                    "samples_u": pts,
                    "log_w": log_ws,
                    "log_likes": log_ls,
                    "blobs": blobs,
                    "samples": np.array([self.transform_to_vec(pt) for pt in pts])
                    }
                with open(self.log_dir + self.pkl_name, "wb") as f:
                    pickle.dump(results, f)
        
        return 0


__plugins__={"nautilus": Nautilus}
