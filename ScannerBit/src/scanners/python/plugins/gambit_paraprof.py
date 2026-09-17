"""
ParaProf scanner
================

ScannerBit plugin wrapping the paraprof package
(https://github.com/anderkve/paraprof) for parallel grid-based profile
likelihood scans inside GAMBIT.

ParaProf places populations on a regular grid over a user-chosen subset of
parameters and dynamically activates the region of interest, optimising the
profiled parameters at each grid point with differential evolution or
L-BFGS-B. The plugin uses paraprof's master/worker MPI scheme: rank 0 acts as
the orchestrator and ranks 1+ evaluate the GAMBIT loglike via
``self.loglike_hypercube``. Because the bound loglike cannot be pickled, the
target function is supplied to the workers directly rather than broadcast.

Drop this file into ``ScannerBit/src/scanners/python/plugins/`` in your GAMBIT
source tree. Requires ``mpi4py`` and the ``paraprof`` package installed in the
Python environment GAMBIT is using.
"""

import numpy as np

from scannerbit import with_mpi as scannerbit_with_mpi
from utils import copydoc, version, get_directory, with_mpi

try:
    import paraprof
    paraprof_version = version(paraprof)
    paraprof_ProfileProjector = paraprof.ProfileProjector
    paraprof_run_scan = paraprof.run_scan
    paraprof_worker_main = paraprof.worker_main
except Exception:
    __error__ = ("The paraprof package is not installed. To install it, run: "
                 "pip install git+https://github.com/anderkve/paraprof.git")
    paraprof_version = "n/a"
    paraprof_ProfileProjector = None
    paraprof_run_scan = None
    paraprof_worker_main = None

import scanner_plugin as splug


class ParaProf(splug.scanner):
    """
Parallel grid-based profile likelihood scan with paraprof.

See https://github.com/anderkve/paraprof for the algorithm and tuning details.

Requires MPI with at least 2 processes (one master + one or more workers); the
master rank performs no target evaluations.

YAML options:
  like:                 Use the functors that correspond to the specified purpose.
  run:                  All paraprof-native settings live here. Required key:
    projections:          List of projection configurations. Each entry is a
                          dict with required keys 'dims' (list of parameter
                          names or indices) and 'grid_points' (list of ints,
                          same length as 'dims'). Optional per-projection keys:
                            optimization_method:    'de' (default) or 'lbfgsb'
                            grid_refinement_factor: int > 1 enables a refined run
                            refinement_method:      interpolation method (default 'linear')
                            patch_coarse_grid:      bool (default true)
                            patch_refined_grid:     bool (default false)
                        Optional ProfileProjector tuning keys:
    roi_threshold:           ROI cutoff in chi^2 units (default 3.0).
    pop_per_grid_point:      DE population size per grid cell (default 3).
    n_initial_optimizations: Global L-BFGS-B starts before grid optimization
                             (default min(100, 20*n_dims)).
    max_patching_waves:      Cap on patching iterations (default 10).
    lbfgsb_max_iter:         Max L-BFGS-B iterations per polish (default 50).
    lbfgsb_polish:           Apply L-BFGS-B polish after DE (default true).
    use_clustering:          Detect modes during refinement (default true).
    refinement_direct_eval:  Skip optimisation in refinement runs (default false).
    initial_points:          Optional list of starting points in physical
                             coordinates to activate explicitly.
    samples_output_file:     Optional CSV path; written by rank 0 only. Note that
                             GAMBIT's printers already record every evaluation,
                             so this is purely a paraprof-side diagnostic file.
    warm_start_file:         Optional CSV path read at the start of each projection
                             to pre-populate ``initial_maxima``, skipping the
                             global L-BFGS-B seeding step. Set equal to
                             ``samples_output_file`` to round-trip samples into
                             the next run.
    advanced_config:         Forwarded as-is to ProfileProjector. Sub-dicts:
                             'de', 'lbfgsb', 'clustering', 'cross_projection'
                             (multi-projection knowledge transfer),
                             'suspect_recheck' (wrong-optimum strip recheck).
                             See the paraprof README for the full key list.
                        Optional run-time keys:
    save_plots:              If true, paraprof writes its diagnostic plots to
                             the working directory after each projection.
    plot_settings:           Dict forwarded to paraprof's plotting helpers.
                             Common keys: dpi, filetype, vmin, vmax,
                             contour_levels, slice_mode, plot_profiled_params.

paraprof's ``grad_func`` is not exposed: ScannerBit's Python API surfaces
only the loglike value, so L-BFGS-B uses finite differences.
"""

    __version__ = paraprof_version
    __plugin_name__ = "paraprof"


    def __init__(self, **kwargs):
        if not scannerbit_with_mpi:
            raise Exception(
                "GAMBIT has been compiled with MPI disabled (WITH_MPI=0), but the "
                "paraprof scanner requires MPI parallelisation with >=2 MPI "
                "processes (1 master + >=1 worker). Rerun CMake with "
                "\"cmake -DWITH_MPI=1\" and recompile GAMBIT."
            )
        if not with_mpi:
            raise Exception(
                "The paraprof scanner requires MPI parallelisation. Make sure "
                "mpi4py is installed in the Python environment GAMBIT is using."
            )

        super().__init__(use_mpi=True, use_resume=False)

        if self.mpi_size < 2:
            raise Exception(
                "The paraprof scanner requires >=2 MPI processes (1 master + "
                ">=1 worker); the master rank performs no target evaluations. "
                f"Detected MPI size = {self.mpi_size}."
            )

        self.print_prefix = f"{ParaProf.__plugin_name__} scanner plugin:"

        # All paraprof-native settings live under the YAML 'run:' block; the
        # top level of the scanner block is reserved for ScannerBit itself.
        ra = self.run_args

        if "projections" not in ra:
            raise RuntimeError(
                f"{self.print_prefix} The required scanner option 'projections' "
                "is missing from the 'run:' block."
            )
        # Defensive copy so downstream mutation (string-dim resolution etc.)
        # doesn't disturb the YAML dict.
        self.projections = [dict(p) for p in ra["projections"]]
        for p in self.projections:
            for k in ('dims', 'grid_points'):
                if k in p and isinstance(p[k], tuple):
                    p[k] = list(p[k])

        # ProfileProjector tuning. Each is optional; we only forward keys the
        # user actually set so paraprof's own defaults stay authoritative.
        self.projector_kwargs = {}
        for key in (
            "roi_threshold", "pop_per_grid_point", "max_patching_waves",
            "lbfgsb_max_iter", "lbfgsb_polish", "n_initial_optimizations",
            "initial_points", "use_clustering", "refinement_direct_eval",
            "samples_output_file", "warm_start_file", "advanced_config",
        ):
            if key in ra:
                self.projector_kwargs[key] = ra[key]

        # Plot / output controls (paraprof-side, not GAMBIT printer side).
        self.save_plots = bool(ra.get("save_plots", False))
        self.plot_settings = ra.get("plot_settings", None)

        # Direct paraprof's plots into the dedicated ScannerBit output folder
        # <default_output_path>/paraprof/. Plots are only written by rank 0.
        if self.save_plots and self.mpi_rank == 0:
            if self.plot_settings is None:
                self.plot_settings = {}
            else:
                self.plot_settings = dict(self.plot_settings)  # defensive copy
            # Only set output_dir if the user didn't pin one explicitly.
            self.plot_settings.setdefault(
                "output_dir", get_directory(self.__plugin_name__, **kwargs)
            )


    @copydoc(paraprof_ProfileProjector)
    def run(self):
        from mpi4py import MPI
        comm = MPI.COMM_WORLD

        # The target function on every rank is GAMBIT's loglike, called via
        # the unit-hypercube convenience method. Wrapping it lets us emit a
        # weight=1 entry on the standard "Posterior" stream after each call,
        # mirroring grid.py / the other ScannerBit Python plugins.
        plugin = self  # bind into closure; avoids capturing self by name twice

        def target_func(x):
            lnL = plugin.loglike_hypercube(x)
            plugin.print(1.0, "Posterior")
            return lnL

        if self.mpi_rank != 0:
            # Worker rank: hand the target function over directly. No bcast.
            paraprof_worker_main(comm, self.mpi_rank, target_func=target_func)
            return 0

        # ---- Master rank ----
        # Bounds always live on the unit hypercube; physical-space bounds come
        # from the YAML Parameters node.
        bounds = [(0.0, 1.0)] * self.dim

        if self.mpi_rank == 0:
            print(f"{self.print_prefix} Starting paraprof scan with "
                  f"{len(self.projections)} projection(s) on {self.mpi_size - 1} "
                  f"worker rank(s).", flush=True)

        with paraprof_ProfileProjector(
            target_func=target_func,
            bounds=bounds,
            projections=self.projections,
            parameter_names=list(self.parameter_names),
            **self.projector_kwargs,
        ) as sampler:

            results = paraprof_run_scan(
                comm=comm,
                sampler=sampler,
                projections=self.projections,
                save_plots=self.save_plots,
                plot_settings=self.plot_settings,
                broadcast_target_func=False,  # workers already have target_func
                myrank=0,
            )

            self._print_summary(results)

        return 0


    def _print_summary(self, results):
        """Emit a per-projection summary on rank 0, in the scipy style."""
        prefix = self.print_prefix
        print()
        print(f"{prefix} === Scan summary ===", flush=True)
        for i, res in enumerate(results):
            cfg = res.get('projection_config', {})
            metrics = res.get('metrics', {})
            dims = cfg.get('dims', [])
            dim_names = [self.parameter_names[d] for d in dims]
            calls = metrics.get('total_target_calls', 'n/a')
            global_max = metrics.get('global_max', float('nan'))
            print(f"{prefix} - Projection {i + 1}:", flush=True)
            print(f"{prefix}     dims (indices):   {dims}", flush=True)
            print(f"{prefix}     dims (names):     {dim_names}", flush=True)
            print(f"{prefix}     grid_points:      {cfg.get('grid_points')}", flush=True)
            print(f"{prefix}     target calls:     {calls}", flush=True)
            print(f"{prefix}     best logL found:  {global_max:.6e}", flush=True)

            # Best-fit point: prefer the refined solution if available,
            # otherwise the coarse one. The exported solution dict doesn't
            # carry a "global best" field, so we derive it ourselves from the
            # global solution pool (capped pool of the best entries) and fall
            # back to the per-cell solutions table if the pool is empty.
            best_solution = (res.get('refined_solution')
                             or res.get('coarse_solution')
                             or {})
            best_x_unit = self._best_full_params(best_solution)
            if best_x_unit is not None:
                best_x_phys = self.transform_to_vec(np.asarray(best_x_unit))
                print(f"{prefix}     best-fit point (physical):", flush=True)
                for name, val in zip(self.parameter_names, best_x_phys):
                    print(f"{prefix}       {name}: {val}", flush=True)
        print()


    @staticmethod
    def _best_full_params(exported_solution):
        """Return the unit-hypercube parameter vector with the highest likelihood.

        Looks first in ``global_solution_pool`` (the capped pool of best
        entries), then falls back to scanning ``solutions``. Returns None if
        nothing is available.
        """
        if not exported_solution:
            return None

        pool = exported_solution.get('global_solution_pool') or []
        best_entry = None
        best_fitness = -float('inf')
        for entry in pool:
            f = entry.get('fitness', -float('inf'))
            if f > best_fitness:
                best_fitness = f
                best_entry = entry
        if best_entry is not None and 'full_params' in best_entry:
            return best_entry['full_params']

        solutions = exported_solution.get('solutions') or {}
        for sol in solutions.values():
            f = sol.get('likelihood', -float('inf'))
            if f > best_fitness:
                best_fitness = f
                best_entry = sol
        if best_entry is not None:
            return best_entry.get('full_params')
        return None


__plugins__ = {ParaProf.__plugin_name__: ParaProf}

