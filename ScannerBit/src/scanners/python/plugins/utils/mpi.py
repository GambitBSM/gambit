import scannerbit

# Figure out if we can use mpi4py
try:
    from mpi4py import MPI
    if scannerbit.with_mpi:
        with_mpi = True
    else:
        with_mpi = False
except ImportError:
    if scannerbit.with_mpi:
        if scannerbit.numtasks() > 1:
            raise Exception(f"GAMBIT is compiled with MPI parallelisation enabled (WITH_MPI=1), "
                            f"but {__file__} failed to import the python module mpi4py. "
                            f"If you want to run this scanner with multiple MPI processes, "
                            f"please install mpi4py.")
        else:
            print(f"WARNING: GAMBIT is compiled with MPI parallelisation enabled (WITH_MPI=1), "
                  f"but {__file__} failed to import the python module mpi4py. If you want to "
                  f"run this scanner with multiple MPI processes, please install mpi4py.")
    else:
        print(f"WARNING: The scanner plugin failed to import mpi4py in {__file__}, "
              f"but that's OK since GAMBIT anyway is running in serial mode (-DWITH_MPI=0).", flush=True)
    with_mpi = False

if with_mpi:
    from .mpipool import MPIPool
