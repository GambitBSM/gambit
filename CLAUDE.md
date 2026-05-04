# Build

If you need to build/rebuild GAMBIT to perform some test, you can check 
**[MINIMAL_BUILD.md](MINIMAL_BUILD.md)** for an end-to-end build recipe.
It covers system packages, Python setup, cmake flags, backend ordering, 
smoke test, and timing.


# Run example

```
OMP_NUM_THREADS=1 ./gambit -rf yaml_files/spartan.yaml
```

(For multi-process MPI runs, re-configure cmake with `-DWITH_MPI=True`
and use `mpiexec -np <N> ./gambit ...`.)

