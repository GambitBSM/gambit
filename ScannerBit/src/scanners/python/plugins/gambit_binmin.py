"""
Binminpy scanners
=================
"""

import numpy as np
from utils import copydoc, version, with_mpi
try:
    import binminpy
    binminpy_version = version(binminpy)
    from binminpy.BinMinBottomUp import BinMinBottomUp as binminpy_BinMinBottomUp
except:
    __error__ = "The binminpy package is not installed. To install it, run: pip install git+https://github.com/anderkve/binminpy.git"
    binminpy_version = "n/a"
    binminpy_BinMinBottomUp = None

import scanner_plugin as splug



class BinMinBottomUp(splug.scanner):
"""
Sampling and optimization based on the "bottom-up" mode of binminpy, where the
parameter space is binned by working outwards from all identified local optima.

See https://github.com/anderkve/binminpy

YAML options:
  like:           Use the functors thats corresponds to the specified purpose.
  run:
    n_bins:               Number of bins for each parameter, given as a list on the form "model::parameter: <number of bins>" 
    sampled_parameters:   List of the parameters that should be sampled within each bin, e.g ["model::par_1", "model::par_2"] 
    optimized_parameters: List of the parameters that should be sampled within each bin, e.g ["model::par_3", "model::par_4"] 
    sampler:              Choice of sampler for sampling parameters within each bin
    optimizer             Choice of optimizer for optimizing parameters within each bin
    optimizer_kwargs:     Keyword arguments to be forwarded to the optimzer
    n_initial_points:     Number of starting points for the initial search for local optima
    n_sampler_points_per_bin:     Number of sampled points within each bin
    accept_loglike_above:         Only add neighbouring bins for bins that have a highest loglike above this threshold
    accept_delta_loglike_above:   Only add neighbouring bins for delta loglike (difference to best-fit point) is within this threshold
    contour_guide:        Settings to only allow bins that include points with loglike value close to a chosen value, for tracing loglike contours
      loglike_contour_central_value:    Loglike contour value
      loglike_contour_width:            Spread around loglike contour value
    inherit_best_init_point_within_bin:  When optimizing parameters, start optimization from the current best point within the given bin
    n_optim_restarts_per_bin:     Number of repeated attempts at optimizing parameters per bin
    n_tasks_per_batch:            Number of tasks (bins) assigned to each MPI worker process at a time
    print_progress_every_n_batch:   How frequently the progress message is printed
"""

    __version__ = binminpy_version
    __plugin_name__ = "binminpy"


    def __init__(self, **kwargs):
        super().__init__(use_mpi=True, use_resume=False)

        self.print_prefix = f"{BinMinBottomUp.__plugin_name__} scanner plugin:"


    def run(self):

        # Define target function: this is where we call the GAMBIT loglike function
        def target_function(x, *args):
            return -self.loglike_hypercube(x)

        # Get the parameter ordering from GAMBIT
        par_indices = {par_name:idx for idx,par_name in enumerate(self.parameter_names)}

        # Set up the list of binning tuples
        binning_tuples = []
        if not "n_bins" in self.run_args:
            raise RuntimeError(f"{self.print_prefix} The run argument 'n_bins' is missing.")
        for param_name in self.parameter_names:
            if not param_name in self.run_args["n_bins"]:
                raise RuntimeError(f"{self.print_prefix} The argument 'n_bins' is missing an entry for the parameter '{param_name}'.")
            par_n_bins = self.run_args["n_bins"][param_name]
            binning_tuples.append([0., 1., par_n_bins])  # <-- Working in the unit hypercube

        # Read list of sampled and optimized parameters, and remove any duplicate entries
        sampled_parameter_names = list(set(self.run_args.get("sampled_parameters", [])))
        optimized_parameter_names = list(set(self.run_args.get("optimized_parameters", [])))

        # Remove any parameter that is not scanned by GAMBIT
        sampled_parameter_names = [par_name for par_name in sampled_parameter_names if par_name in self.parameter_names]
        optimized_parameter_names = [par_name for par_name in optimized_parameter_names if par_name in self.parameter_names]

        # Deal with parameters that are not listed in "sampled_parameters" or "optimized_parameters"
        if (len(sampled_parameter_names) == 0) and (len(optimized_parameter_names) == 0):
            sampled_parameter_names = self.parameter_names
            optimized_parameter_names = []
        elif (len(sampled_parameter_names) == 0) and (len(optimized_parameter_names) > 0):
            sampled_parameter_names = list(set(self.parameter_names).difference(optimized_parameter_names))
        elif (len(sampled_parameter_names) > 0) and (len(optimized_parameter_names) == 0):
            optimized_parameter_names = list(set(self.parameter_names).difference(sampled_parameter_names))

        if self.mpi_rank == 0:
            print(f"{self.print_prefix} Parameters that will be *sampled* in each bin: {sampled_parameter_names}", flush=True)
            print(f"{self.print_prefix} Parameters that will be *optimized* in each bin: {optimized_parameter_names}", flush=True)

        # Parse options for restricting the set of parameter bins
        accept_target_below = -np.inf
        if "accept_loglike_above" in self.run_args:
            accept_target_below = -1.0 * self.run_args["accept_loglike_above"]

        accept_delta_target_below = -np.inf
        if "accept_delta_loglike_above" in self.run_args:
            accept_delta_target_below = -1.0 * self.run_args["accept_delta_loglike_above"]

        # Set up guide function, if requested
        guide_function = None
        accept_guide_below = -np.inf
        accept_delta_guide_below = -np.inf
        if "contour_guide" in self.run_args:
            if "loglike_contour_central_value" not in self.run_args["contour_guide"]:
                raise RuntimeError(f"{self.print_prefix} The argument 'contour_guide' is missing the entry 'loglike_contour_central_value'.")
            if "loglike_contour_width" not in self.run_args["contour_guide"]:
                raise RuntimeError(f"{self.print_prefix} The argument 'contour_guide' is missing the entry 'loglike_contour_width'.")
            neg_contour_central_value = -1.0 * self.run_args["contour_guide"]["loglike_contour_central_value"]
            contour_width = self.run_args["contour_guide"]["loglike_contour_width"]
            def guide_function(x, y, *args):
                contour_chi2 = (y - neg_contour_central_value)**2 / (0.5 * contour_width)**2
                return contour_chi2
            accept_target_below = -np.inf
            accept_delta_target_below = -np.inf
            accept_guide_below = 4.0
            accept_delta_guide_below = -np.inf

        if ((accept_target_below == -np.inf) and (accept_delta_target_below == -np.inf)
            and (accept_guide_below == -np.inf) and (accept_delta_guide_below == -np.inf)):
            if self.mpi_rank == 0:
                print(f"{self.print_prefix} Running with no restrictions on the set of parameter space bins.", flush=True)
            accept_target_below = np.inf
            accept_delta_target_below = np.inf
            accept_guide_below = np.inf
            accept_delta_guide_below = np.inf

        # Create the BinMinBottomUp instance
        binned_opt = binminpy_BinMinBottomUp(
            target_function,
            binning_tuples,
            args=(),
            guide_function=guide_function,
            sampler=self.run_args.get("sampler", "latinhypercube"),
            optimizer=self.run_args.get("optimizer", "minimize"),
            optimizer_kwargs=self.run_args.get("optimizer_kwargs", {}),
            sampled_parameters=tuple(par_indices[par_name] for par_name in sampled_parameter_names),
            optimized_parameters=tuple(par_indices[par_name] for par_name in optimized_parameter_names),
            n_initial_points=self.run_args.get("n_initial_points", self.mpi_size),
            n_sampler_points_per_bin=self.run_args.get("n_sampler_points_per_bin", 10),
            inherit_best_init_point_within_bin=self.run_args.get("inherit_best_init_point_within_bin", False),
            accept_target_below=accept_target_below, 
            accept_delta_target_below=accept_delta_target_below,
            accept_guide_below=accept_guide_below,
            accept_delta_guide_below=accept_delta_guide_below,
            save_evals=self.run_args.get("save_evals", False),
            return_evals=False,
            return_bin_centers=False,
            optima_comparison_rtol=self.run_args.get("optima_comparison_rtol", 1e-9),
            optima_comparison_atol=self.run_args.get("optima_comparison_atol", 0.0),
            n_optim_restarts_per_bin=self.run_args.get("n_optim_restarts_per_bin", 1),
            n_tasks_per_batch=self.run_args.get("n_tasks_per_batch", 10),
            print_progress_every_n_batch=self.run_args.get("print_progress_every_n_batch", 1000),
            max_tasks_per_worker=self.run_args.get("max_tasks_per_worker", np.inf),
            max_n_bins=self.run_args.get("max_n_bins", np.inf),
        )

        # Run the scan!
        result = binned_opt.run()

        # Print a summary
        if self.mpi_rank == 0:
            best_bins = result["optimal_bins"]
            print()
            print(f"{self.print_prefix} # Global optima found in bin(s) {best_bins}:", flush=True)
            for i, bin_index_tuple in enumerate(best_bins):
                x_opt_physical = self.transform_to_vec(result['x_optimal'][i])
                x_print_dict = dict(zip(self.parameter_names, x_opt_physical.tolist()))
                print(f"{self.print_prefix} - Bin {bin_index_tuple}:", flush=True)
                print(f"{self.print_prefix}   - Parameters:", flush=True)
                for key, val in x_print_dict.items():
                    print(f"{self.print_prefix}     - {key}: {val}")
                print(f"{self.print_prefix}   - Log-likelihood: {result['y_optimal'][i]}", flush=True)
            print()
            n_bins_evaluated = len(result["bin_tuples"])
            max_n_bins = np.prod([bt[2] for bt in binning_tuples])
            print(f"{self.print_prefix} Bins evaluated: {n_bins_evaluated} / {max_n_bins}", flush=True)
            print(f"{self.print_prefix} Target function calls: {result['n_target_calls']}", flush=True)
            print()

        return 0


__plugins__ = {BinMinBottomUp.__plugin_name__: BinMinBottomUp}
