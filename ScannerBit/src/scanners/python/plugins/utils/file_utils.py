import os
import pickle
import atexit
from .mpi import with_mpi
if with_mpi:
    from mpi4py import MPI

def get_directory(path, default_output_path=".", **kwargs):
    defpath = os.path.abspath((default_output_path + "/" + path).strip())

    if not os.path.exists(defpath):
        os.makedirs(defpath)
        
    return defpath + "/"

class store_pt_data:
    
    def __init__(self, resume=False, log_dir="./"):
        if with_mpi:
            self.comm = MPI.COMM_WORLD
            self.mpi_rank = self.comm.Get_rank()
            self.mpi_size = self.comm.Get_size()
        else:
            self.mpi_rank=0
        self.id_filename = log_dir + "/temp_saved_pt_data_{0}.pkl".format(self.mpi_rank)
        
        if resume:
            self.f = open(self.id_filename, 'ab')
        else:
            self.f = open(self.id_filename, 'wb')
            
        atexit.register(lambda: store_pt_data.close(self))
        
    def close(self):
        self.f.close()
            
    def save(self, pt, id):
        pickle.dump((pt, id), self.f)
        
    def load_saves(self):
        self.saves = {}
        self.f.close()
        with open(self.id_filename, 'rb') as f:
            while True:
                try:
                    data = pickle.load(f)
                    self.saves[data[0]] = data[1]
                except:
                    break
        self.transfer_saves()
    
    def transfer_saves(self):
        if with_mpi:
            if self.mpi_rank == 0:
                for i in range(1, self.mpi_size):
                    data = self.comm.recv(source=i, tag=1)
                    self.saves.update(data)
            else:
                self.comm.send(self.saves, dest=0, tag=1)
