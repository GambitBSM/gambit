"""
Scipy scannners
===============
"""

from utils import copydoc, version, with_mpi
import numpy as np
from itertools import product
from collections import OrderedDict

try:
    import scipy.optimize
    scipy_version = version("scipy")
    scipy_optimize_dual_annealing = scipy.optimize.dual_annealing
    scipy_optimize_basinhopping = scipy.optimize.basinhopping
    scipy_optimize_differential_evolution = scipy.optimize.differential_evolution
    scipy_optimize_direct = scipy.optimize.direct
    scipy_optimize_shgo = scipy.optimize.shgo
    scipy_optimize_minimize = scipy.optimize.minimize
except:
    __error__ = 'scipy pkg (v1.9 or later) not installed'
    scipy_version = 'n/a'
    scipy_optimize_dual_annealing = None
    scipy_optimize_basinhopping = None
    scipy_optimize_differential_evolution = None
    scipy_optimize_direct = None
    scipy_optimize_shgo = None
    scipy_optimize_minimize = None

import scanner_plugin as splug


def print_optimization_summary(print_prefix, optimize_result, x_print, x0_print=None, bounds_print=None):
    """
Uility function for printing optimization results
    """
    print(f"\n{print_prefix} Optimization summary:")
    if bounds_print is not None:
        print(f"{print_prefix} - Bounds: {bounds_print}")    
    if x0_print is not None:
        print(f"{print_prefix} - Initial point: {x0_print}")    
    print(f"{print_prefix} - Optimal point: {x_print}")
    print(f"{print_prefix} - OptimizeResult from scipy, with x-coordinates in the unit hypercube:")
    optimize_result_text = str.join("\n", [f"{print_prefix}   {line}" for line in str(optimize_result).splitlines()])
    print(optimize_result_text, "\n")



class DualAnnealing(splug.scanner):
    """
Dual annealing optimizer from scipy.
    """

    __version__ = scipy_version
    __plugin_name__ = "scipy_dual_annealing"

    def __init__(self, **kwargs):
        super().__init__(use_mpi=True, use_resume=False)

    @copydoc(scipy_optimize_dual_annealing)
    def run(self):

        n_runs = self.mpi_size
        if 'n_runs' in self.run_args:
            n_runs = self.run_args.pop('n_runs')

        if self.mpi_size == 1:
            for run_id in range(1, n_runs + 1):
                self.run_internal(run_id)
        else:
            for run_id in range(self.mpi_rank + 1, n_runs + 1, self.mpi_size):
                self.run_internal(run_id)
        return 0

    def run_internal(self, run_id):

        print_prefix = f"MPI rank {self.mpi_rank}: {self.__plugin_name__}, run {run_id}:"

        # Make a local copy we can modify
        run_args = dict(self.run_args)

        # If an initial x0 is given, use it in the first run
        x0_unit = None
        if 'x0' in run_args:
            if run_id == 1:
                x0_phys = run_args.pop('x0')
                x0_unit = self.inverse_transform(x0_phys)
                run_args['x0'] = x0_unit
            else:
                del run_args['x0']

        bounds = [(0., 1.)] * self.dim

        def neg_loglike_hypercube(x):
            return -self.loglike_hypercube(x)

        res = scipy.optimize.dual_annealing(neg_loglike_hypercube, bounds, **run_args)

        x0_print = None
        if x0_unit is not None:
            x0_print = dict(zip(self.parameter_names, self.transform_to_vec(x0_unit)))
        x_print = dict(zip(self.parameter_names, self.transform_to_vec(res.x)))
        bounds_print_min = self.transform_to_vec(np.array([x[0] for x in bounds]))
        bounds_print_max = self.transform_to_vec(np.array([x[1] for x in bounds]))
        bounds_print = dict(zip(self.parameter_names, zip(bounds_print_min, bounds_print_max)))
        print_optimization_summary(print_prefix, res, x_print, x0_print=x0_print, bounds_print=bounds_print)



class BasinHopping(splug.scanner):
    """
Basin-hopping optimizer from scipy.
    """

    __version__ = scipy_version
    __plugin_name__ = "scipy_basin_hopping"

    def __init__(self, **kwargs):
        super().__init__(use_mpi=True, use_resume=False)

    @copydoc(scipy_optimize_basinhopping)
    def run(self):

        n_runs = self.mpi_size
        if 'n_runs' in self.run_args:
            n_runs = self.run_args.pop('n_runs')

        if self.mpi_size == 1:
            for run_id in range(1, n_runs + 1):
                self.run_internal(run_id)
        else:
            for run_id in range(self.mpi_rank + 1, n_runs + 1, self.mpi_size):
                self.run_internal(run_id)
        return 0

    def run_internal(self, run_id):

        print_prefix = f"MPI rank {self.mpi_rank}: {self.__plugin_name__}, run {run_id}:"

        # Make a local copy we can modify
        run_args = dict(self.run_args)

        # If an initial x0 is given, use it in the first run
        x0_unit = np.random.rand(self.dim)
        if 'x0' in run_args:
            if run_id == 1:
                x0_phys = run_args.pop('x0')
                x0_unit = self.inverse_transform(x0_phys)
            else:
                del run_args['x0']

        def neg_loglike_hypercube(x):
            return -self.loglike_hypercube(x)

        res = scipy.optimize.basinhopping(neg_loglike_hypercube, x0_unit, **run_args)

        x0_print = dict(zip(self.parameter_names, self.transform_to_vec(x0_unit)))
        x_print = dict(zip(self.parameter_names, self.transform_to_vec(res.x)))
        print_optimization_summary(print_prefix, res, x_print, x0_print=x0_print)



class DifferentialEvolution(splug.scanner):
    """
Differential evolution optimizer from scipy.
    """

    __version__ = scipy_version
    __plugin_name__ = "scipy_differential_evolution"

    def __init__(self, **kwargs):
        super().__init__(use_mpi=True, use_resume=False)

    @copydoc(scipy_optimize_differential_evolution)
    def run(self):

        n_runs = self.mpi_size
        if 'n_runs' in self.run_args:
            n_runs = self.run_args.pop('n_runs')

        if self.mpi_size == 1:
            for run_id in range(1, n_runs + 1):
                self.run_internal(run_id)
        else:
            for run_id in range(self.mpi_rank + 1, n_runs + 1, self.mpi_size):
                self.run_internal(run_id)
        return 0

    def run_internal(self, run_id):

        print_prefix = f"MPI rank {self.mpi_rank}: {self.__plugin_name__}, run {run_id}:"

        # Make a local copy we can modify
        run_args = dict(self.run_args)

        # If an initial x0 is given, use it in the first run
        x0_unit = None
        if 'x0' in run_args:
            if run_id == 1:
                x0_phys = run_args.pop('x0')
                x0_unit = self.inverse_transform(x0_phys)
                run_args['x0'] = x0_unit
            else:
                del run_args['x0']

        bounds = [(0., 1.)] * self.dim

        def neg_loglike_hypercube(x):
            return -self.loglike_hypercube(x)

        res = scipy.optimize.differential_evolution(neg_loglike_hypercube, bounds, **run_args)

        x0_print = None
        if x0_unit is not None:
            x0_print = dict(zip(self.parameter_names, self.transform_to_vec(x0_unit)))
        x_print = dict(zip(self.parameter_names, self.transform_to_vec(res.x)))
        bounds_print_min = self.transform_to_vec(np.array([x[0] for x in bounds]))
        bounds_print_max = self.transform_to_vec(np.array([x[1] for x in bounds]))
        bounds_print = dict(zip(self.parameter_names, zip(bounds_print_min, bounds_print_max)))
        print_optimization_summary(print_prefix, res, x_print, x0_print=x0_print, bounds_print=bounds_print)



class Direct(splug.scanner):
    """
The DIRECT optimizer from scipy.
    """

    __version__ = scipy_version
    __plugin_name__ = "scipy_direct"
    
    def __init__(self, **kwargs):
        super().__init__(use_mpi=True, use_resume=False)

    @copydoc(scipy_optimize_direct)
    def run(self):

        n_runs = self.mpi_size
        if 'n_runs' in self.run_args:
            n_runs = self.run_args.pop('n_runs')

        if self.mpi_size == 1:
            for run_id in range(1, n_runs + 1):
                self.run_internal(run_id)
        else:
            for run_id in range(self.mpi_rank + 1, n_runs + 1, self.mpi_size):
                self.run_internal(run_id)
        return 0

    def run_internal(self, run_id):

        print_prefix = f"MPI rank {self.mpi_rank}: {self.__plugin_name__}, run {run_id}:"

        bounds = [(0., 1.)] * self.dim

        def neg_loglike_hypercube(x):
            return -self.loglike_hypercube(x)

        res = scipy.optimize.direct(neg_loglike_hypercube, bounds, **self.run_args)

        x_print = dict(zip(self.parameter_names, self.transform_to_vec(res.x)))
        bounds_print_min = self.transform_to_vec(np.array([x[0] for x in bounds]))
        bounds_print_max = self.transform_to_vec(np.array([x[1] for x in bounds]))
        bounds_print = dict(zip(self.parameter_names, zip(bounds_print_min, bounds_print_max)))
        print_optimization_summary(print_prefix, res, x_print, bounds_print=bounds_print)



class SHGO(splug.scanner):
    """
The SHGO optimizer from scipy.
    """

    __version__ = scipy_version
    __plugin_name__ = "scipy_shgo"
    
    def __init__(self, **kwargs):
        super().__init__(use_mpi=True, use_resume=False)

    @copydoc(scipy_optimize_direct)
    def run(self):

        # Subdivide the parameter space based on the user
        # setting "split_param_space". Each partition becomes
        # a separate optimizer run, and the different runs
        # are distributed evently across MPI processes.
        n_split_steps = [1] * self.dim
        if 'split_param_space' in self.run_args:
            split_param_space = self.run_args.pop('split_param_space')
            for i, par_name in enumerate(self.parameter_names):
                n_split_steps[i] = split_param_space[par_name]
        n_runs = np.prod(n_split_steps)
        
        all_bounds = []
        for d in range(self.dim):
            n_split_steps_d = n_split_steps[d]
            split_points = np.linspace(0, 1, n_split_steps_d + 1)
            d_bounds = []
            for s in range(n_split_steps_d):
                d_bounds.append((split_points[s],split_points[s + 1]))
            all_bounds.append(d_bounds)
        all_bounds = list(product(*all_bounds))

        if self.mpi_size == 1:
            for run_id in range(1, n_runs + 1):
                self.run_internal(run_id, all_bounds[run_id - 1])
        else:
            for run_id in range(self.mpi_rank + 1, n_runs + 1, self.mpi_size):
                self.run_internal(run_id, all_bounds[run_id - 1])
        return 0

    def run_internal(self, run_id, bounds):

        print_prefix = f"MPI rank {self.mpi_rank}: {self.__plugin_name__}, run {run_id}:"

        def neg_loglike_hypercube(x):
            return -self.loglike_hypercube(x)
        
        res = scipy.optimize.shgo(neg_loglike_hypercube, bounds, **self.run_args)

        x_print = dict(zip(self.parameter_names, self.transform_to_vec(res.x)))
        bounds_print_min = self.transform_to_vec(np.array([x[0] for x in bounds]))
        bounds_print_max = self.transform_to_vec(np.array([x[1] for x in bounds]))
        bounds_print = dict(zip(self.parameter_names, zip(bounds_print_min, bounds_print_max)))
        print_optimization_summary(print_prefix, res, x_print, bounds_print=bounds_print)



class Minimize(splug.scanner):
    """
Local optimization from scipy.
    """

    __version__ = scipy_version
    __plugin_name__ = "scipy_minimize"

    def __init__(self, **kwargs):
        super().__init__(use_mpi=True, use_resume=False)

    @copydoc(scipy_optimize_minimize)
    def run(self):

        n_runs = self.mpi_size
        if 'n_runs' in self.run_args:
            n_runs = self.run_args.pop('n_runs')

        if self.mpi_size == 1:
            for run_id in range(1, n_runs + 1):
                self.run_internal(run_id)
        else:
            for run_id in range(self.mpi_rank + 1, n_runs + 1, self.mpi_size):
                self.run_internal(run_id)
        return 0

    def run_internal(self, run_id):

        print_prefix = f"MPI rank {self.mpi_rank}: {self.__plugin_name__}, run {run_id}:"

        # Make a local copy we can modify
        run_args = dict(self.run_args)

        # If an initial x0 is given, use it in the first run
        x0_unit = np.random.rand(self.dim)
        if 'x0' in run_args:
            if run_id == 1:
                x0_phys = run_args.pop('x0')
                x0_unit = self.inverse_transform(x0_phys)
            else:
                del run_args['x0']

        # The bounds are set in the Parameters node of the YAML file,
        # not the scanner options, so should use the entire unit hypercube
        bounds = [(0., 1.)] * self.dim
        if 'bounds' in run_args:
            del run_args['bound']

        def neg_loglike_hypercube(x):
            return -self.loglike_hypercube(x)

        res = scipy.optimize.minimize(neg_loglike_hypercube, x0_unit, bounds=bounds, **run_args)

        x0_print = dict(zip(self.parameter_names, self.transform_to_vec(x0_unit)))
        x_print = dict(zip(self.parameter_names, self.transform_to_vec(res.x)))
        bounds_print_min = self.transform_to_vec(np.array([x[0] for x in bounds]))
        bounds_print_max = self.transform_to_vec(np.array([x[1] for x in bounds]))
        bounds_print = dict(zip(self.parameter_names, zip(bounds_print_min, bounds_print_max)))
        print_optimization_summary(print_prefix, res, x_print, x0_print=x0_print, bounds_print=bounds_print)
        


__plugins__ = {DualAnnealing.__plugin_name__: DualAnnealing,
               BasinHopping.__plugin_name__: BasinHopping,
               DifferentialEvolution.__plugin_name__: DifferentialEvolution,
               Direct.__plugin_name__: Direct,
               SHGO.__plugin_name__: SHGO,
               Minimize.__plugin_name__: Minimize}
