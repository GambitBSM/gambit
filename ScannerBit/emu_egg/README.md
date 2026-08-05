
# Introduce
short

# quick start example
### Full Likelihood
Emulating the full likelihood. Regardless of what module one uses, the likelihood as a whole can be emulated. This requires no additional functions, but is built into the framework, so any example inifile can be used in this example (most simple is the spartant.yaml). To emulate the likelihood, we only needs to activate emulation by adding the emulator section in the inifile and running the correct commandline arguments.

A minimal example of the yaml settings with the existing pygptreeo plugin is:
```yaml
Emulation:

  use_emulator:
  - LogLike

  emulators:
    LogLike:
      plugin: pygptreeo
      model_filename: loglike_pred_model.joblib
      train: true
      predict: true
      uncertainty:
        - 0.01
      max_cache_size: 50
      Nbar: 30
      theta: 1e-4
      split_position_method: median
      split_dimension_criteria: max_variance
      retrain_every_n_points: 10
      use_calibrated_sigma: true
      splitting_strategy: gradual
      pre_trained: false
      timeout: 300
```

To run the spartan example with only emulating the likelihood, one can use the following command:
``` bash
mpirun -np 4 ./gambit -f yaml_files/emulation_test_likelihood.yaml : -np 2 ./egg -c LogLike
```

# Running emus
## comandline
## MPI commdline
## inifile

# Making capabilties emu-able

To declare a gambit function as emulatable for a given capability, the macro START_FUNCTION_EMULATABLE(return type) within the rollcall header entry is required (as opposed to the standard START_FUNCTION(return type) declaratation).

```
  #define FUNCTION function_name           // Name of an observable function
    START_FUNCTION_EMULATABLE(double)      // This function calculates a double precision variable
  #undef FUNCTION
```
This will expand to declare functions for translating between emulator and capability inputs, and to threshold functions used to determine whther the emulator prediction is satisfies uncertainty requirements.

## Defining Translation functions
## Defining Threshold function (optional)

# making emu
## overview
## Python Plugin
## c interface (enter at own risk)
