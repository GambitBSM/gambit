# Imported MPIPool and BasePool from Schwimmbad.  See https://github.com/adrn/schwimmbad

# Standard library
import abc

__all__ = ['BasePool']

def batch_tasks(n_batches, n_tasks=None, arr=None, args=None, start_idx=0,
                include_idx=True):
    """Split tasks into some number of batches to send out to workers.

    By default, returns index ranges that split the number of tasks into the
    specified number of batches. If an array is passed in via ``arr``, it splits
    the array directly along ``axis=0`` into the specified number of batches.

    Parameters
    ----------
    n_batches : int
        The number of batches to split the tasks into. Often, you may want to do
        ``n_batches=pool.size`` for equal sharing amongst MPI workers.
    n_tasks : int (optional)
        The total number of tasks to divide.
    arr : iterable (optional)
        Instead of returning indices that specify the batches, you can also
        directly split an array into batches.
    args : iterable (optional)
        Other arguments to add to each task.
    start_idx : int (optional)
        What index in the tasks to start from?
    include_idx : bool (optional)
        If passing an array in, this determines whether to include the indices
        of each batch with each task.
    """
    if args is None:
        args = tuple()
    args = tuple(args)

    if ((n_tasks is None and arr is None) or
            (n_tasks is not None and arr is not None)):
        raise ValueError("you must pass one of n_tasks or arr (not both)")
    elif n_tasks is None:
        n_tasks = len(arr)

    if n_batches <= 0 or n_tasks <= 0:
        raise ValueError("n_batches and n_tasks must be > 0")

    if n_batches > n_tasks:
        # TODO: add a warning?
        n_batches = n_tasks

    # Chunk by the number of batches, often the pool size
    base_batch_size = n_tasks // n_batches
    rmdr = n_tasks % n_batches

    i1 = start_idx
    indices = []
    for i in range(n_batches):
        i2 = i1 + base_batch_size
        if i < rmdr:
            i2 += 1

        indices.append((i1, i2))
        i1 = i2

    # Add args, possible slice input array:
    tasks = []
    for idx in indices:
        if arr is not None and not args and not include_idx:
            tasks.append(arr[idx[0]:idx[1]])
            continue

        extra = list()
        if arr is not None:
            extra.append(arr[idx[0]:idx[1]])
        if args:
            extra.extend(args)

        if extra and include_idx:
            tasks.append(tuple([idx] + extra))
        elif extra and not include_idx:
            tasks.append(extra)
        else:
            tasks.append(idx)

    return tasks


def _callback_wrapper(callback, generator):
    for element in generator:
        callback(element)
        yield element


class BasePool(metaclass=abc.ABCMeta):
    """ A base class multiprocessing pool with a ``map`` method. """

    def __init__(self, **kwargs):
        self.rank = 0

    @staticmethod
    def enabled():
        return False

    def is_master(self):
        return self.rank == 0

    def is_worker(self):
        return self.rank != 0

    def wait(self):
        return

    @abc.abstractmethod
    def map(self, *args, **kwargs):
        return

    def batched_map(self, worker, tasks, *args, **kwargs):
        batches = batch_tasks(n_batches=self.size, arr=tasks)
        return self.map(worker, batches, *args, **kwargs)

    def close(self):
        pass

    def __enter__(self):
        return self

    def __exit__(self, *args):
        self.close()

    def _call_callback(self, callback, generator):
        if callback is None:
            return generator
        return _callback_wrapper(callback, generator)
