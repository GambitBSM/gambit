import emulator_plugin as eplug
import numpy as np
import os
import sys
import time
import traceback
import csv
import atexit
import warnings
import faulthandler

try:
    import joblib
except ImportError:
    __error__ = "joblib not installed"

try:
    from pygptreeo import GPTree, Default_GPR, AdditiveMaternKernel
except ImportError:
    __error__ = "pygptreeo not installed."

# Count the leaf-GP refits pygptreeo performs, so that the trainer can tell
# whether an update actually changed what the predictor would predict. This
# wraps GPNode.fit_my_GPR (which returns True when it trained); it only adds a
# counter and does not alter pygptreeo's behaviour. Wrapped once per process.
_retrain_count = [0]
try:
    from pygptreeo.gpnode import GPNode
    if not getattr(GPNode.fit_my_GPR, '_gambit_counting', False):
        _orig_fit_my_GPR = GPNode.fit_my_GPR

        def _counting_fit_my_GPR(self, *args, **kwargs):
            trained = _orig_fit_my_GPR(self, *args, **kwargs)
            if trained:
                _retrain_count[0] += 1
            return trained

        _counting_fit_my_GPR._gambit_counting = True
        GPNode.fit_my_GPR = _counting_fit_my_GPR
except ImportError:
    pass


warnings.filterwarnings("error", category=RuntimeWarning)
np.seterr(over='raise', invalid='raise')


class pyGPtreeoEmulator(eplug.emulator):
    """
pygptreeo emulator

With two MPI ranks, rank 1 trains and rank 0 predicts; with one rank it does
both. The trainer writes the tree to a joblib file and the predictor reloads
it whenever the file has changed. By default (save_on_retrain_only) the file is
only rewritten when a leaf GP was actually refitted, so the predictor's model
changes only upon retraining, not after every added point.

YAML options:
    train: Option to enable/disable training
    predict: Option to enable/disable prediction
    uncertainty: Prediction uncertainty threshold for GAMBIT
    Nbar: Maximum number of training points a node can hold before
        splitting. Defaults to 100.
    theta: Parameter controlling the overlap region between sibling nodes
        (theta * range of the split dimension). Defaults to 0.0001.
    use_calibrated_sigma: If True, enables sigma calibration in GPNode
        predictions. Defaults to True.
    split_dimension_criteria: Method to select the split dimension. Options:
        'min_lengthscale', 'max_spread', 'max_variance', 'max_uncertainty',
        'random'. Defaults to 'min_lengthscale'.
    split_position_method: Where to split a node. Defaults to 'median'.
    splitting_strategy: 'standard' or 'gradual'. Defaults to 'standard'.
    retrain_every_n_points: Refit a leaf GP after this many new points.
        Defaults to 1.
    kernel: Leaf kernel. 'matern' (default) or 'additive' (additive + Matern
        catch-all; requires n_inputs).
    n_inputs: Number of emulator inputs (only needed for kernel: additive).
    additive_order: Highest interaction order of the additive kernel.
        Defaults to 2.
    global_mean: None (default) or 'additive_gp' for a tree-wide global
        model whose residual the leaves learn.
    global_mean_kwargs: Dict of options for the global model learner.
    n_restarts_optimizer: Optimizer restarts for each leaf GP fit. Defaults to 0.
    model_filename: Name of the model file (written to the run's
        emulator_plugins directory). Defaults to 'pygptreeo_model.joblib'.
    pre_trained: Boolean option to load a pre-trained model
    pre_trained_path: Path to pre-trained model file. OBS: new model file
        will be written and stored in run folder.
    log_emulator_data: If True, writes emu_predictions.csv and emu_training.csv
        to the output path for post-run comparison of emulated vs actual values.
        Defaults to False.
    save_on_retrain_only: If True (default), the model file read by predict is
        only rewritten when pygptreeo refitted at least one leaf GP (see
        retrain_every_n_points); points that are just stored in between do not
        change the predictor's model. If False, the file is written after every
        point.
    log_cache_size: Number of rows of emu_predictions.csv and emu_training.csv
        (counted separately for each file) kept in memory before they are
        written to disk (only used with log_emulator_data). The files can
        therefore lag the run by up to this many rows, and rows still in the
        cache are lost if the job is killed (e.g. by MPI_Abort); a normal
        shutdown writes everything. 1 writes after every row. Defaults to 100.
    stack_dump_interval: If > 0, write the Python stack of this rank to
        stacks_rank<N>.txt in the output path every this many seconds.
        Defaults to 0 (off).
    log_target: If True, the tree models log(y) instead of y (for positive
        targets spanning orders of magnitude). The prediction is mapped back
        to y, but the uncertainty returned to GAMBIT is the log-space sigma,
        i.e. the *relative* uncertainty of the prediction, so the yaml
        uncertainty threshold is then a relative one. Defaults to False.
    min_train_points: Do not offer predictions (report them as not valid,
        so GAMBIT does the real calculation and trains on it) until the
        tree has seen this many training points. Guards against the
        over-confident sigma of a barely trained tree, which would otherwise
        stop all training as soon as its predictions get accepted.
        Defaults to 100.
    validation_fraction: Report this fraction of predictions as not valid
        even when the tree is confident, chosen at random, so a stream of
        real evaluations keeps training the tree and gives an unbiased
        check of the accepted predictions' accuracy in the logs (rows with
        forced=1 in emu_predictions.csv). Defaults to 0.05.
    validation_seed: Seed of the random number generator used for the
        validation draw. Defaults to 12345.
    adaptive_validation: If True, the validation fraction is adjusted during
        the run from the errors of the predictions GAMBIT would have accepted.
        The trainer evaluates the tree at every incoming training point before
        the update; if the predicted (relative, with log_target) sigma was below
        validation_tolerance_sigma, its error is added to a rolling
        window. Each time the window has refreshed, the fraction is halved if
        at most validation_tail_target of the errors exceed
        validation_tolerance, and doubled otherwise, within
        [validation_fraction_min, validation_fraction_max]. The window and the
        current fraction are stored on the tree, so the predicting rank picks
        them up with the model file. Starts after min_train_points.
        Defaults to False.
    validation_tolerance_sigma: Sigma below which a prediction counts as one
        GAMBIT would accept. Defaults to the first yaml uncertainty threshold.
    validation_tolerance: Error (relative with log_target, absolute otherwise) above which a validation point counts
        as a miss. Defaults to twice validation_tolerance_sigma: the calibrated
        sigma is a 68% width, so errors up to ~2 sigma are expected.
    validation_tail_target: Allowed fraction of misses. Defaults to 0.1.
    validation_window: Number of validation errors per decision. Defaults to 25.
    validation_fraction_min, validation_fraction_max: Bounds on the adapted
        fraction. Default 0.01 and 0.2.
    target_relative_uncertainty: If set, replaces the target uncertainty sent
        by GAMBIT with this fraction of |y| for every training point (e.g.
        1.0e-4 to treat the targets as exact). For tests; default None.
    verbose: Print every training point and prediction. Defaults to False.

The CSV logs carry a wall-clock time column 't' per row, so the time between
a rejected prediction and the training point that follows it measures the
cost of the real calculation. The predictions log also has 'dt', the time
spent in predict (including any reload of the model file).
"""

    __version__ = "1.1.0"

    def __init__(self, **kwargs):
        super().__init__()

        output_path = kwargs['default_output_path']
        model_filename = kwargs.get('model_filename', 'pygptreeo_model.joblib')
        self.tree_filename = os.path.join(output_path, model_filename)
        self.verbose = kwargs.get('verbose', False)

        # Periodic stack dump of this rank, to find out where a stalled rank is stuck.
        stack_dump_interval = float(kwargs.get('stack_dump_interval', 0))
        if stack_dump_interval > 0:
            self._stack_file = open(os.path.join(output_path, f'stacks_rank{self.mpi_rank}.txt'), 'w')
            faulthandler.dump_traceback_later(stack_dump_interval, repeat=True, file=self._stack_file)
        self._n_saved_points = 0
        self.save_on_retrain_only = bool(kwargs.get('save_on_retrain_only', True))
        self.log_target = kwargs.get('log_target', False)
        self.target_relative_uncertainty = kwargs.get('target_relative_uncertainty', None)
        self.min_train_points = int(kwargs.get('min_train_points', 100))
        self.validation_fraction = float(kwargs.get('validation_fraction', 0.05))
        self._rng = np.random.default_rng(int(kwargs.get('validation_seed', 12345)))
        self.adaptive_validation = bool(kwargs.get('adaptive_validation', False))
        thr = kwargs.get('uncertainty', None)
        thr = float(thr[0]) if isinstance(thr, (list, tuple)) and len(thr) else (float(thr) if thr is not None else None)
        self.val_tol_sigma = float(kwargs.get('validation_tolerance_sigma', thr if thr is not None else 0.03))
        self.val_tol = float(kwargs.get('validation_tolerance', 2.0 * self.val_tol_sigma))
        self.val_tail_target = float(kwargs.get('validation_tail_target', 0.1))
        self.val_window = int(kwargs.get('validation_window', 25))
        self.val_frac_min = float(kwargs.get('validation_fraction_min', 0.01))
        self.val_frac_max = float(kwargs.get('validation_fraction_max', 0.2))

        self.gpt = self._make_tree(kwargs)

        if self.mpi_size == 1 or self.mpi_rank == 1:
            if kwargs.get('pre_trained', False):
                pre_trained_path = kwargs.get('pre_trained_path', self.tree_filename)
                print(f"Loading pre-trained model from {pre_trained_path}...")
                if os.path.exists(pre_trained_path):
                    self.gpt = joblib.load(pre_trained_path)
            else:
                print("Initializing GPTreeO emulator and saving initial model...")
            # State of the adaptive validation controller travels with the tree
            self.gpt.emu_validation_fraction = self.validation_fraction
            self.gpt.emu_val_errors = []
            self.gpt.emu_val_new = 0
            self.gpt.atomic_save(self.tree_filename)

        if os.path.exists(self.tree_filename):
            self.last_mtime = os.path.getmtime(self.tree_filename)
        else:
            self.last_mtime = time.time()

        self.training_enabled = kwargs.get('train', True)
        self.prediction_enabled = kwargs.get('predict', True)
        self.logging_enabled = kwargs.get('log_emulator_data', False)
        self.log_cache_size = max(1, int(kwargs.get('log_cache_size', 100)))
        self._log_rows_cached = {'pred': 0, 'train': 0}
        self.n_train = 0
        self.n_pred = 0

        # CSV logging: predictions written by rank 0, training data written by rank 1
        if self.logging_enabled:
            if self.mpi_size == 1 or self.mpi_rank == 0:
                self._pred_csv_file = open(os.path.join(output_path, 'emu_predictions.csv'), 'w', newline='')
                self._pred_csv_writer = csv.writer(self._pred_csv_file)
                self._pred_header_written = False

            if self.mpi_size == 1 or self.mpi_rank == 1:
                self._train_csv_file = open(os.path.join(output_path, 'emu_training.csv'), 'w', newline='')
                self._train_csv_writer = csv.writer(self._train_csv_file)
                self._train_header_written = False

            # make sure buffered rows reach the disk on a normal shutdown
            atexit.register(self._flush_logs, True)

    def _flush_logs(self, force=False, which=None):
        """Write the cached CSV rows to disk. Without force this counts one new row for the file
        given by which ('pred' or 'train') and flushes it once log_cache_size rows are cached;
        with force it flushes the file(s) (both if which is None) regardless."""
        for key, attr in (('pred', '_pred_csv_file'), ('train', '_train_csv_file')):
            if which not in (None, key):
                continue
            f = getattr(self, attr, None)
            if f is None or f.closed:
                continue
            if not force:
                self._log_rows_cached[key] += 1
            if force or self._log_rows_cached[key] >= self.log_cache_size:
                f.flush()
                self._log_rows_cached[key] = 0

    @staticmethod
    def _make_tree(kwargs):
        """Builds a GPTree from the yaml options."""
        kernel_name = kwargs.get('kernel', 'matern')
        if kernel_name == 'matern':
            kernel = None
        elif kernel_name == 'additive':
            if 'n_inputs' not in kwargs:
                raise ValueError("kernel: additive needs the n_inputs option")
            kernel = AdditiveMaternKernel(d=int(kwargs['n_inputs']),
                                          order=int(kwargs.get('additive_order', 2)))
        else:
            raise ValueError(f"Unknown kernel option '{kernel_name}'. Use 'matern' or 'additive'.")

        gpr = Default_GPR(kernel=kernel,
                          n_restarts_optimizer=int(kwargs.get('n_restarts_optimizer', 0)))

        return GPTree(
            GPR=gpr,
            Nbar=int(kwargs.get('Nbar', 100)),
            theta=float(kwargs.get('theta', 1e-4)),
            use_calibrated_sigma=kwargs.get('use_calibrated_sigma', True),
            split_dimension_criteria=kwargs.get('split_dimension_criteria', 'min_lengthscale'),
            splitting_strategy=kwargs.get('splitting_strategy', 'standard'),
            global_mean=kwargs.get('global_mean', None),
            global_mean_kwargs=kwargs.get('global_mean_kwargs', None),
            split_position_method=kwargs.get('split_position_method', 'median'),
            retrain_every_n_points=int(kwargs.get('retrain_every_n_points', 1)),
        )

    def _n_training_points(self):
        """Number of points the (possibly reloaded) tree has been trained on."""
        return int(getattr(self.gpt, 'n_points_seen', 0))

    def train(self, x, y, z, flag):
        if not self.training_enabled:
            print("Training is disabled for this emulator instance.")
            return
        if not (self.mpi_size == 1 or self.mpi_rank == 1):
            return

        # Copies, not views: the arrays GAMBIT hands over wrap C++ memory that
        # is released after this call, and the tree may keep the rows.
        x = np.array(x, dtype=float).reshape(-1)
        y = np.array(y, dtype=float).reshape(-1)
        sigma = np.array(z, dtype=float).reshape(-1)
        if self.target_relative_uncertainty is not None:
            sigma = float(self.target_relative_uncertainty) * np.abs(y)
        self.n_train += 1
        if self.verbose:
            print(f"[pygptreeo] train #{self.n_train}: x={x} y={y} sigma={sigma}", flush=True)

        t_received = time.time()
        row = [t_received] + list(x) + list(y) + list(sigma)
        self._train_dims = (len(x), len(y), len(sigma))
        nan = float('nan')

        y_lin = y.copy()
        if self.log_target:
            if np.any(y <= 0):
                print(f"[pygptreeo] training point skipped: log_target needs y > 0, got {y}", flush=True)
                self._log_train_row(row, nan, nan, nan)
                return
            sigma = sigma / y
            y = np.log(y)

        if self.adaptive_validation and self._n_training_points() >= self.min_train_points:
            self._record_validation_error(x, y_lin)

        retrains_before = _retrain_count[0]
        t0 = time.time()
        try:
            self.gpt.update_tree(x.reshape(1, -1), y.reshape(1, -1),
                                 float(sigma[0]) if sigma.size == 1 else sigma)
        except (FloatingPointError, RuntimeWarning, np.linalg.LinAlgError) as e:
            print(f"[pygptreeo] training point skipped after numerical error: {e}", flush=True)
            traceback.print_exc(limit=-8)
            sys.stdout.flush()
            self._log_train_row(row, time.time() - t0, float('nan'), float('nan'))
            return
        t_update = time.time() - t0

        # Publish the model to the predictor only if a GP was refitted (or always,
        # if save_on_retrain_only is off). Otherwise the saved model, and hence
        # the predictions, stay as they were at the last retrain.
        if self.save_on_retrain_only and _retrain_count[0] == retrains_before:
            self._log_train_row(row, t_update, float('nan'), self._n_saved_points)
            return

        t0 = time.time()
        self.gpt.atomic_save(self.tree_filename)
        t_save = time.time() - t0
        self._n_saved_points = self._n_training_points()
        self._log_train_row(row, t_update, t_save, self._n_saved_points)

    def _log_train_row(self, row, t_update, t_save, n_points_after):
        """Write one emu_training.csv row. Besides the data it records how long the
        tree update and the model save took, and the number of points in the saved
        model, so that the staleness of the predictor's model can be reconstructed."""
        if not self.logging_enabled:
            return
        if not self._train_header_written:
            n_x, n_y, n_z = self._train_dims
            header = (['t'] + [f'x_{i}' for i in range(n_x)]
                      + [f'y_{i}' for i in range(n_y)]
                      + [f'z_{i}' for i in range(n_z)]
                      + ['t_update', 't_save', 'n_points_model', 't_done'])
            self._train_csv_writer.writerow(header)
            self._train_header_written = True
        self._train_csv_writer.writerow(row + [t_update, t_save, n_points_after, time.time()])
        self._flush_logs(which='train')

    def _record_validation_error(self, x, y_lin):
        """Trainer side: error of the current tree at a new truth, if it was confident."""
        try:
            mu, sd = self.gpt.predict(x.reshape(1, -1))
        except Exception:
            return
        mu = float(np.asarray(mu).reshape(-1)[0])
        sd = float(np.asarray(sd).reshape(-1)[0])
        y = float(y_lin[0])
        if self.log_target:
            # sd is the relative sigma; use the relative error, like the yaml threshold
            mu = np.exp(mu)
            err = abs(mu - y) / max(abs(y), 1e-300)
        else:
            # sd, the error and the tolerances are absolute, like the yaml threshold
            err = abs(mu - y)
        if not (sd < self.val_tol_sigma):
            return
        errs = getattr(self.gpt, 'emu_val_errors', [])
        errs.append(err)
        self.gpt.emu_val_errors = errs[-self.val_window:]
        self.gpt.emu_val_new = getattr(self.gpt, 'emu_val_new', 0) + 1
        if self.gpt.emu_val_new >= self.val_window and len(self.gpt.emu_val_errors) >= self.val_window:
            tail = float(np.mean(np.array(self.gpt.emu_val_errors) > self.val_tol))
            f = getattr(self.gpt, 'emu_validation_fraction', self.validation_fraction)
            f_new = f / 2 if tail <= self.val_tail_target else f * 2
            f_new = min(max(f_new, self.val_frac_min), self.val_frac_max)
            self.gpt.emu_validation_fraction = f_new
            self.gpt.emu_val_new = 0
            print(f"[pygptreeo] validation window: {100 * tail:.0f}% of {self.val_window} confident predictions "
                  f"off by > {self.val_tol:g}; validation fraction {f:.3f} -> {f_new:.3f}", flush=True)

    def _current_validation_fraction(self):
        if self.adaptive_validation:
            return float(getattr(self.gpt, 'emu_validation_fraction', self.validation_fraction))
        return self.validation_fraction

    def predict(self, x, flag):
        if not self.prediction_enabled:
            print("Prediction is disabled for this emulator instance.")
            return (np.array([None]), np.array([None]))
        if not (self.mpi_size == 1 or self.mpi_rank == 0):
            return (np.array([None]), np.array([None]))

        flag.result = True
        self.n_pred += 1
        t_start = time.time()

        # Reload the tree if the trainer has written a newer one
        if os.path.exists(self.tree_filename):
            current_mtime = os.path.getmtime(self.tree_filename)
            if current_mtime != self.last_mtime:
                try:
                    self.gpt = joblib.load(self.tree_filename)
                    self.last_mtime = current_mtime
                except Exception as e:
                    # A load can fail if the file is replaced mid-read; keep the old tree.
                    print(f"[pygptreeo] could not reload model file: {e}", flush=True)

        x = np.array(x, dtype=float).reshape(-1)
        X_test = x.reshape(1, -1)
        try:
            y_pred, y_std = self.gpt.predict(X_test)
        except (FloatingPointError, RuntimeWarning, np.linalg.LinAlgError) as e:
            print(f"[pygptreeo] prediction invalid after numerical error: {e}", flush=True)
            flag.not_valid = True
            return (np.array([0.0]), np.array([0.0]))

        y_pred = np.asarray(y_pred[0], dtype=float).reshape(-1)
        y_std = np.asarray(y_std[0], dtype=float).reshape(-1)
        if self.log_target:
            # y_std stays the log-space sigma, i.e. the relative uncertainty
            y_pred = np.exp(y_pred)

        # Force the real calculation while the tree is young, and for a random
        # validation fraction of the requests thereafter
        n_seen = self._n_training_points()
        val_frac = self._current_validation_fraction()
        forced = 0
        if n_seen < self.min_train_points:
            forced = 1
        elif val_frac > 0 and self._rng.random() < val_frac:
            forced = 2
        if forced:
            flag.not_valid = True
        if self.verbose:
            print(f"[pygptreeo] predict #{self.n_pred}: x={x} y={y_pred} sigma={y_std}", flush=True)

        if self.logging_enabled:
            if not self._pred_header_written:
                header = (['t', 'dt', 'forced', 'val_frac'] + [f'x_{i}' for i in range(len(x))]
                          + [f'y_pred_{i}' for i in range(len(y_pred))]
                          + [f'y_std_{i}' for i in range(len(y_std))]
                          + ['n_points_model', 'model_mtime'])
                self._pred_csv_writer.writerow(header)
                self._pred_header_written = True
            now = time.time()
            self._pred_csv_writer.writerow([now, now - t_start, forced, val_frac] + list(x) + list(y_pred) + list(y_std)
                                         + [n_seen, self.last_mtime])
            self._flush_logs(which='pred')

        return (y_pred, y_std)


__plugins__ = {"pygptreeo": pyGPtreeoEmulator}
