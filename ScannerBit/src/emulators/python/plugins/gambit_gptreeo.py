import emulator_plugin as eplug
import numpy as np
import os
import sys
import time
import traceback
import csv
import collections
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
both. With n_predictors = P > 0 (needs P+1 egg ranks) ranks 0..P-1 predict and
rank P trains; the plugin makes sure each predict request is answered by exactly
one predictor, see n_predictors below. The trainer writes the tree to a joblib file and the predictor reloads
it whenever the file has changed. By default (save_on_retrain_only) the file is
only rewritten when a leaf GP was actually refitted, so the predictor's model
changes only upon retraining, not after every added point.

YAML options:
    routing: 'legacy' (default) or 'master'. With 'master' (set under
        Emulation: emulators: <capability>:) gambit sends every message only to
        egg rank 0, the master, and the plugin's master() decides where it goes:
        a predict request is forwarded to one predictor, which replies to the
        gambit rank directly; training points are collected in a cache on the
        master and sent to the trainer in batches (see train_batch_size).
        Roles by number of egg ranks: 1 rank: it does everything. 2 ranks: the
        master also predicts and rank 1 trains. 3 or more ranks: the master
        only routes (a dedicated master never waits for its own prediction),
        ranks 1..N-2 predict and the last rank trains. master_predicts:
        true/false overrides this choice.
    master_predicts: (routing: master) Whether the master also predicts.
        Defaults to true for up to 2 egg ranks and false for 3 or more.
    train_batch_size: (routing: master) Number of training points the master
        collects before it sends them to the trainer. Defaults to 20. The
        trainer updates the tree with them one by one but writes the model
        file once per batch (if a leaf GP was refitted), so retrain_every_n_points
        and this setting together decide how often the predictors see a new model.
    max_cache_age_seconds: (routing: master) Send the cache to the trainer
        when its oldest point is this old, even if it has fewer than
        train_batch_size points. Defaults to 10. Checked when a message
        arrives and by egg's timer (master_tick_interval, egg setting). Points
        still in the cache at shutdown are lost.
    max_queued_batches, max_in_flight_batches, release_order: (routing: master)
        Full batches wait in a queue on the master and are released to the trainer
        only when it has room, so a trainer that cannot keep up never builds up a
        backlog of stale points in MPI buffers. The trainer reports every finished
        batch with a small message on the plugin's own communicator (mpi4py).
        max_in_flight_batches (default 2) is the number of batches the master has
        handed to the trainer and not yet seen finished. max_queued_batches
        (default 20) is the size of the waiting queue; when it is full the OLDEST
        waiting batch is dropped. release_order 'newest' (default) sends the newest
        waiting batch first, 'oldest' the oldest first. If mpi4py cannot be set up
        the plugin prints a warning and sends batches without throttling (egg's
        max_pending_batches then applies, which drops the newest batches).
        master_status_interval (default 60 s, 0 = off) prints the queue state.
        predictor_log_interval (default 10 s, 0 = off) appends, on every predictor, where
        its predict() time went (waiting between calls, model file check, model reload,
        the GP evaluation) to <default_output_path>/predictor_timing_rank<N>.csv.
        master_log_interval (default 10 s, 0 = off) appends the queue state to
        <default_output_path>/master_queue.csv (queued, in flight, released and
        dropped batches and points), which emulator_message_timing.py reads.
    predict_routing: (routing: master) 'round_robin' (default) or 'source'
        (gambit rank % number of predictors, as in legacy routing).
    n_predictors: Number of predictor ranks. With routing: master the default
        is all ranks but the trainer (and the master, if it is dedicated); the
        predictors are the ranks right after the master (or from rank 0 if the
        master predicts) and the trainer is the rank after the last predictor.
        With legacy routing (default 0 = off: rank 0 predicts, rank 1 trains),
        P > 0 means egg ranks 0..P-1 predict and rank P trains.
        Gambit sends every message to every egg rank and egg passes every
        message on to the plugin together with the world rank of the sender
        (flag.source). The plugin decides: predictor (gambit rank % P) answers
        a predict request, all other ranks leave it unanswered (a rank that
        does not set flag.result gets no reply sent), so gambit gets exactly
        one reply per request. Only the trainer handles train messages. Needs
        at least P+1 egg ranks. With P > 1 each predictor writes its own
        emu_predictions_rank<N>.csv.
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
    max_memory_mb: Memory the tree stays within, in MB (GPTree max_memory_mb;
        needs a pygptreeo that has it). Applies to the tree in RAM, not to the
        model file. Defaults to no limit.
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
        self._rng = np.random.default_rng(int(kwargs.get('validation_seed', 12345)) + int(self.mpi_rank))
        self.adaptive_validation = bool(kwargs.get('adaptive_validation', False))
        thr = kwargs.get('uncertainty', None)
        thr = float(thr[0]) if isinstance(thr, (list, tuple)) and len(thr) else (float(thr) if thr is not None else None)
        self.val_tol_sigma = float(kwargs.get('validation_tolerance_sigma', thr if thr is not None else 0.03))
        self.val_tol = float(kwargs.get('validation_tolerance', 2.0 * self.val_tol_sigma))
        self.val_tail_target = float(kwargs.get('validation_tail_target', 0.1))
        self.val_window = int(kwargs.get('validation_window', 25))
        self.val_frac_min = float(kwargs.get('validation_fraction_min', 0.01))
        self.val_frac_max = float(kwargs.get('validation_fraction_max', 0.2))

        # Roles of the egg ranks
        self.n_predictors = int(kwargs.get('n_predictors', 0))
        self.master_mode = kwargs.get('routing', 'legacy') == 'master'
        if self.master_mode:
            # routing: master. Rank 0 is the master (it routes messages). With 1 egg rank it does everything;
            # with 2 it also predicts; with 3 or more it only routes (master_predicts: false by default)
            # so that a burst of requests never waits for one of its own predictions. The last rank trains and
            # the ranks in between predict.
            n = self.mpi_size
            master_predicts = bool(kwargs.get('master_predicts', n <= 2))
            if n == 1:
                self.predictor_ranks, self.trainer_rank = [0], 0
            else:
                first = 0 if master_predicts else 1
                n_pred = self.n_predictors if self.n_predictors > 0 else n - 1 - first
                if n_pred < 1 or first + n_pred > n - 1:
                    raise ValueError(f"routing: master with {n} egg ranks"
                                     f"{'' if master_predicts else ' and a dedicated master'} cannot have "
                                     f"n_predictors = {n_pred} (ranks {first}..{first + n_pred - 1} predict, rank {first + n_pred} trains).")
                self.predictor_ranks = list(range(first, first + n_pred))
                self.trainer_rank = first + n_pred
            self.n_predictors = len(self.predictor_ranks)
        else:
            # legacy routing, must match egg's handling: with n_predictors = P > 0 ranks 0..P-1 predict and
            # rank P trains; with P = 0 rank 0 predicts and rank 1 trains (one rank does both)
            if self.n_predictors < 0 or (self.n_predictors > 0 and self.n_predictors >= self.mpi_size):
                raise ValueError(f"n_predictors = {self.n_predictors} needs at least {self.n_predictors + 1} egg ranks "
                                 f"(n_predictors predictors + 1 trainer), but there are {self.mpi_size}.")
            if self.n_predictors > 0:
                self.predictor_ranks, self.trainer_rank = list(range(self.n_predictors)), self.n_predictors
            elif self.mpi_size == 1:
                self.predictor_ranks, self.trainer_rank = [0], 0
            else:
                self.predictor_ranks, self.trainer_rank = [0], 1
        self.is_predictor = self.mpi_rank in self.predictor_ranks
        self.is_trainer = self.mpi_rank == self.trainer_rank

        # Master side (routing: master): cache of training points and predict routing state
        self.train_batch_size = max(1, int(kwargs.get('train_batch_size', 20)))
        self.max_cache_age = float(kwargs.get('max_cache_age_seconds', 10))
        self.predict_routing = kwargs.get('predict_routing', 'round_robin')
        if self.predict_routing not in ('round_robin', 'source'):
            raise ValueError(f"Unknown predict_routing '{self.predict_routing}'. Use 'round_robin' or 'source'.")
        self._cache_x, self._cache_y, self._cache_z = [], [], []
        self._cache_t0 = None
        self._next_predictor_idx = 0
        self._n_batches_sent = 0

        # Batch queue on the master (routing: master). Full batches wait here until the trainer has room,
        # so that when the trainer cannot keep up it is the OLDEST waiting batches that are dropped, not the
        # newest ones (the scan moves, newer points are the relevant ones). The trainer reports every batch
        # it has finished with a small message on the plugin's own communicator (ack).
        self.max_queued_batches = max(1, int(kwargs.get('max_queued_batches', 20)))
        self.max_in_flight_batches = max(1, int(kwargs.get('max_in_flight_batches', 2)))
        self.release_order = kwargs.get('release_order', 'newest')
        if self.release_order not in ('newest', 'oldest'):
            raise ValueError(f"Unknown release_order '{self.release_order}'. Use 'newest' or 'oldest'.")
        self.master_status_interval = float(kwargs.get('master_status_interval', 60))
        self._queue = collections.deque()
        self._in_flight = 0
        self._n_released = 0
        self._n_dropped_queued = 0
        self._last_status = time.time()
        # CSV with the state of the master's queue over time (read by the emulator_message_timing plot)
        self.master_log_interval = float(kwargs.get('master_log_interval', 10))
        self._n_trains_taken = 0
        self._n_released_points = 0
        self._n_dropped_points = 0
        self._master_csv = None
        self._last_master_csv = 0.0
        self._master_csv_path = os.path.join(output_path, 'master_queue.csv')
        # Where a predictor spends its time (predictor_timing_rank<N>.csv, one row per predictor_log_interval)
        self.predictor_log_interval = float(kwargs.get('predictor_log_interval', 10))
        self._predictor_csv_path = os.path.join(output_path, f'predictor_timing_rank{self.mpi_rank}.csv')
        self._predictor_csv = None
        self._last_predictor_csv = time.time()
        self._pc_last_end = None
        self._pt = dict(n=0, between=0.0, check=0.0, n_reloads=0, reload=0.0, reload_max=0.0, gp=0.0, total=0.0)
        self._n_leaves = 0
        self._model_mb = 0.0
        self._comm = None
        self._ack_reqs = []
        if self.master_mode and self.mpi_size > 1:
            try:
                import mpi4py
                mpi4py.rc.initialize = False   # MPI is already initialised by egg
                mpi4py.rc.finalize = False     # and is finalised by egg
                from mpi4py import MPI
                if not MPI.Is_initialized():
                    raise RuntimeError("MPI is not initialised in this process")
                self._MPI = MPI
                self._comm = MPI.Comm.f2py(self.mpi_comm)
            except Exception as e:
                self._comm = None
                print(f"[pygptreeo] WARNING: could not set up mpi4py on the plugin communicator ({e!r}). "
                      f"Batches are sent to the trainer without throttling and none are dropped by the plugin; "
                      f"egg's max_pending_batches is the only limit (it drops the newest batches).", flush=True)

        self.gpt = self._make_tree(kwargs)

        if self.is_trainer:
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
            if not hasattr(self.gpt, 'n_points_seen'):
                self.gpt.emu_n_points = getattr(self.gpt, 'emu_n_points', 0)
            self._save_tree()

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
            if self.is_predictor:
                pred_name = 'emu_predictions.csv' if self.n_predictors <= 1 else f'emu_predictions_rank{self.mpi_rank}.csv'
                self._pred_csv_file = open(os.path.join(output_path, pred_name), 'w', newline='')
                self._pred_csv_writer = csv.writer(self._pred_csv_file)
                self._pred_header_written = False

            if self.is_trainer:
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

        extra = {}
        if kwargs.get('max_memory_mb', None) is not None:
            extra['max_memory_mb'] = float(kwargs['max_memory_mb'])

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
            **extra,
        )

    def _answers_request_from(self, source):
        """Predictor side: True if this rank is the one that answers a predict request sent by the
        process with world rank 'source'. With several predictors, gambit rank g is served by
        predictor g % n_predictors, so that every request gets exactly one reply."""
        if self.n_predictors <= 1:
            return True
        return int(source) % self.n_predictors == self.mpi_rank

    def _n_training_points(self):
        """Number of points the (possibly reloaded) tree has been trained on."""
        n = getattr(self.gpt, 'n_points_seen', None)    # newer pygptreeo counts these itself
        if n is None:
            n = getattr(self.gpt, 'emu_n_points', 0)    # otherwise the plugin's own counter, saved with the tree
        return int(n)

    def _save_tree(self):
        """Write the tree to the model file so that a concurrent reader never sees a partial file.
        Uses GPTree.atomic_save when the installed pygptreeo has it, otherwise writes a temporary
        file in the same directory and renames it into place (atomic on POSIX)."""
        if hasattr(self.gpt, 'atomic_save'):
            self.gpt.atomic_save(self.tree_filename)
            return
        tmp = f"{self.tree_filename}.tmp.{os.getpid()}"
        try:
            joblib.dump(self.gpt, tmp)
            os.replace(tmp, self.tree_filename)
        finally:
            if os.path.exists(tmp):
                os.remove(tmp)

    def master(self, x, y, z, flag):
        """Master rank only (routing: master). Called by egg for every message from gambit and on a timer
        with neither flag.train nor flag.predict set. Returns (destination, n_rows, X, Y, Z):
        destination is an egg rank (-1: send nothing); n_rows == 0 means 'forward this predict request
        to destination', n_rows > 0 means 'send these n_rows training points (row-major) to destination'."""
        none = np.zeros(0)
        if flag.predict:
            return (self._pick_predictor(flag.source), 0, none, none, none)

        now = time.time()
        if flag.train and self.training_enabled:
            # copies: the arrays wrap C++ memory that is released after this call
            self._cache_x.append(np.array(x, dtype=float).reshape(-1))
            self._cache_y.append(np.array(y, dtype=float).reshape(-1))
            self._cache_z.append(np.array(z, dtype=float).reshape(-1))
            self._n_trains_taken += 1
            if self._cache_t0 is None:
                self._cache_t0 = now

        # 1. cache -> batch -> queue
        n = len(self._cache_x)
        if n and (n >= self.train_batch_size or now - self._cache_t0 >= self.max_cache_age):
            X, Y, Z = np.concatenate(self._cache_x), np.concatenate(self._cache_y), np.concatenate(self._cache_z)
            self._cache_x, self._cache_y, self._cache_z = [], [], []
            self._cache_t0 = None
            self._queue.append((n, X, Y, Z))
            while len(self._queue) > self.max_queued_batches:
                dropped = self._queue.popleft()     # the oldest waiting batch is the least relevant one
                self._n_dropped_queued += 1
                self._n_dropped_points += dropped[0]
                if self._n_dropped_queued == 1 or self._n_dropped_queued % 50 == 0:
                    print(f"[pygptreeo] master: trainer is behind, dropped the oldest queued batch of {dropped[0]} points "
                          f"({self._n_dropped_queued} dropped so far)", flush=True)

        # 2. batches the trainer has finished
        self._collect_acks()

        # 3. release one batch if the trainer has room (no throttling if there is no plugin communicator)
        out = (-1, 0, none, none, none)
        if self._queue and (self._comm is None or self._in_flight < self.max_in_flight_batches):
            n, X, Y, Z = self._queue.pop() if self.release_order == 'newest' else self._queue.popleft()
            self._in_flight += 1
            self._n_released += 1
            self._n_released_points += n
            self._n_batches_sent += 1
            if self.verbose:
                print(f"[pygptreeo] master: sending batch #{self._n_batches_sent} of {n} points to rank {self._trainer_rank()}", flush=True)
            out = (self._trainer_rank(), n, X, Y, Z)

        self._log_master_queue(now)
        if self.master_status_interval > 0 and now - self._last_status >= self.master_status_interval:
            self._last_status = now
            print(f"[pygptreeo] master: queued batches {len(self._queue)}, in flight {self._in_flight}, "
                  f"released {self._n_released}, dropped {self._n_dropped_queued}", flush=True)
        return out

    def _log_master_queue(self, now):
        """Master: append one row with the state of the batch queue to master_queue.csv every master_log_interval
        seconds (0 = off). 'wall' uses the format of the gambit and egg logs so that the plots can line them up."""
        if self.master_log_interval <= 0 or now - self._last_master_csv < self.master_log_interval:
            return
        self._last_master_csv = now
        try:
            if self._master_csv is None:
                new = not os.path.exists(self._master_csv_path)
                self._master_csv = open(self._master_csv_path, 'a', buffering=1)
                if new:
                    self._master_csv.write('wall,cache_points,queued_batches,queued_points,in_flight_batches,'
                                           'released_batches,released_points,dropped_batches,dropped_points,'
                                           'train_points_taken\n')
            self._master_csv.write('%s,%d,%d,%d,%d,%d,%d,%d,%d,%d\n' % (
                time.strftime('%a %b %d %H:%M:%S %Y', time.localtime(now)), len(self._cache_x), len(self._queue),
                sum(b[0] for b in self._queue), self._in_flight, self._n_released, self._n_released_points,
                self._n_dropped_queued, self._n_dropped_points, self._n_trains_taken))
        except OSError:
            self.master_log_interval = 0     # cannot write: stop trying

    def _log_predictor_timing(self, now):
        """Predictor: append one row with where the time went since the last row, then reset the sums. Columns (seconds):
        between = outside predict() (waiting for a request, egg's receive and reply), check = stat() of the model
        file, reload = joblib.load of a new model, gp = tree.predict, total = whole predict()."""
        self._last_predictor_csv = now
        pt = self._pt
        try:
            if self._predictor_csv is None:
                new = not os.path.exists(self._predictor_csv_path)
                self._predictor_csv = open(self._predictor_csv_path, 'a', buffering=1)
                if new:
                    self._predictor_csv.write('wall,interval_s,n_predicts,between_s,check_s,n_reloads,reload_s,'
                                              'reload_max_s,gp_s,total_s,n_leaves,model_mb\n')
            self._predictor_csv.write('%s,%.3f,%d,%.4f,%.4f,%d,%.4f,%.4f,%.4f,%.4f,%d,%.1f\n' % (
                time.strftime('%a %b %d %H:%M:%S %Y', time.localtime(now)), self.predictor_log_interval,
                pt['n'], pt['between'], pt['check'], pt['n_reloads'], pt['reload'], pt['reload_max'], pt['gp'],
                pt['total'], self._n_leaves, self._model_mb))
        except OSError:
            self.predictor_log_interval = 0
        self._pt = dict(n=0, between=0.0, check=0.0, n_reloads=0, reload=0.0, reload_max=0.0, gp=0.0, total=0.0)

    def _collect_acks(self):
        """Master: count the batches the trainer has reported as finished (non-blocking)."""
        if self._comm is None:
            self._in_flight = 0
            return
        MPI = self._MPI
        buf = np.zeros(1, dtype='i')
        while self._comm.Iprobe(source=self.trainer_rank, tag=self._ACK_TAG):
            self._comm.Recv([buf, MPI.INT], source=self.trainer_rank, tag=self._ACK_TAG)
            self._in_flight = max(0, self._in_flight - 1)

    def _send_ack(self):
        """Trainer: tell the master that a batch has been processed."""
        if self._comm is None:
            return
        MPI = self._MPI
        self._ack_reqs = [r for r in self._ack_reqs if not r[0].Test()]
        buf = np.ones(1, dtype='i')
        self._ack_reqs.append((self._comm.Isend([buf, MPI.INT], dest=0, tag=self._ACK_TAG), buf))

    _ACK_TAG = 77

    def _trainer_rank(self):
        """Egg rank that trains."""
        return self.trainer_rank

    def _predictor_ranks(self):
        return self.predictor_ranks

    def _pick_predictor(self, source):
        preds = self._predictor_ranks()
        if self.predict_routing == 'source':
            return preds[int(source) % len(preds)]
        self._next_predictor_idx = (self._next_predictor_idx + 1) % len(preds)
        return preds[self._next_predictor_idx]

    def train(self, x, y, z, flag):
        if not self.training_enabled:
            print("Training is disabled for this emulator instance.")
            return
        if not self.is_trainer:
            return

        # Copies, not views: the arrays GAMBIT hands over wrap C++ memory that
        # is released after this call, and the tree may keep the rows.
        # A message from gambit is one point; a batch from the master has flag.n_rows rows.
        n_rows = int(flag.n_rows)
        try:
            self._train_batch(x, y, z, n_rows)
        finally:
            # always report the batch as done, also after an error, so that the master keeps sending
            if self.master_mode and flag.batch:
                self._send_ack()

    def _train_batch(self, x, y, z, n_rows):
        x = np.array(x, dtype=float).reshape(n_rows, -1)
        y = np.array(y, dtype=float).reshape(n_rows, -1)
        z = np.array(z, dtype=float).reshape(n_rows, -1)

        retrains_before = _retrain_count[0]
        rows = [self._update_point(x[i].copy(), y[i].copy(), z[i].copy()) for i in range(n_rows)]

        # Publish the model to the predictors only if a GP was refitted (or always,
        # if save_on_retrain_only is off). Otherwise the saved model, and hence
        # the predictions, stay as they were at the last retrain. For a batch, once per batch.
        t_save = float('nan')
        if not (self.save_on_retrain_only and _retrain_count[0] == retrains_before):
            t0 = time.time()
            self._save_tree()
            t_save = time.time() - t0
            self._n_saved_points = self._n_training_points()

        for k, (row, t_update) in enumerate(rows):
            # the save time belongs to the last point of the batch
            self._log_train_row(row, t_update, t_save if k == len(rows) - 1 else float('nan'), self._n_saved_points)

    def _update_point(self, x, y, sigma):
        """Trainer side: add one point to the tree. Returns (log row, time spent in the update)."""
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
                return (row, nan)
            sigma = sigma / y
            y = np.log(y)

        if self.adaptive_validation and self._n_training_points() >= self.min_train_points:
            self._record_validation_error(x, y_lin)

        t0 = time.time()
        try:
            self.gpt.update_tree(x.reshape(1, -1), y.reshape(1, -1),
                                 float(sigma[0]) if sigma.size == 1 else sigma)
            if not hasattr(self.gpt, 'n_points_seen'):
                self.gpt.emu_n_points = getattr(self.gpt, 'emu_n_points', 0) + 1
        except (FloatingPointError, RuntimeWarning, np.linalg.LinAlgError) as e:
            print(f"[pygptreeo] training point skipped after numerical error: {e}", flush=True)
            traceback.print_exc(limit=-8)
            sys.stdout.flush()
            return (row, nan)
        return (row, time.time() - t0)

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
        # with routing: master the master already picked this rank, so only check the role
        if not self.is_predictor or (not self.master_mode and not self._answers_request_from(flag.source)):
            # not our request: leave flag.result unset, so egg sends no reply
            return (np.array([None]), np.array([None]))

        flag.result = True
        self.n_pred += 1
        t_start = time.time()
        pc0 = time.perf_counter()
        pt = self._pt
        if self._pc_last_end is not None:
            pt['between'] += pc0 - self._pc_last_end     # time outside predict(): waiting for a request, egg's MPI, reply

        # Reload the tree if the trainer has written a newer one
        reload_dt = 0.0
        if os.path.exists(self.tree_filename):
            current_mtime = os.path.getmtime(self.tree_filename)
            if current_mtime != self.last_mtime:
                try:
                    pcr = time.perf_counter()
                    self.gpt = joblib.load(self.tree_filename)
                    reload_dt = time.perf_counter() - pcr
                    self.last_mtime = current_mtime
                    pt['n_reloads'] += 1
                    pt['reload'] += reload_dt
                    pt['reload_max'] = max(pt['reload_max'], reload_dt)
                    try:
                        self._n_leaves = len(self.gpt.root.leaves)
                        self._model_mb = os.path.getsize(self.tree_filename) / 1e6
                    except Exception:
                        pass
                except Exception as e:
                    # A load can fail if the file is replaced mid-read; keep the old tree.
                    print(f"[pygptreeo] could not reload model file: {e}", flush=True)

        x = np.array(x, dtype=float).reshape(-1)
        X_test = x.reshape(1, -1)
        pc1 = time.perf_counter()
        pt['check'] += (pc1 - pc0) - reload_dt          # stat() of the model file
        try:
            y_pred, y_std = self.gpt.predict(X_test)
            pt['gp'] += time.perf_counter() - pc1
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
        pc_end = time.perf_counter()
        pt['total'] += pc_end - pc0
        pt['n'] += 1
        self._pc_last_end = pc_end
        if self.predictor_log_interval > 0 and t_start - self._last_predictor_csv >= self.predictor_log_interval:
            self._log_predictor_timing(t_start)
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
