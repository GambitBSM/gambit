
# Introduce
short

# Quick start examples
### Full Likelihood emulation
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

### Two emulated capabilities example
Emulation of one or more physics capabilities require the implementation of [emulation functions](#Makeing-capabilities-emu-able). A simple example using the ExampleBit_A module to emulate two capabilities is already implemented in the module. 
The two capabilities *nevents_pred* and *lnL_gaussian* are implemented, and in this example they both use the same example pygptreeo emulator plugin as in the likelihood example. Each emulatable capability needs its own block with emulator settings, and can be specified in the following way:

```yaml

Emulation:

  use_emulator:
  - nevents_pred
  - lnL_gaussian

  emulators:
    nevents_pred:
      plugin: pygptreeo
      ...
    lnL_gaussian:
      plugin: pygptreeo
      ...

```

To run the example with two capabilities emulated at the same time, one can use the following command:
```bash
mpirun -np 4 ./gambit -f yaml_files/two_emulators_spartan.yaml : -np 2 ./egg -c nevents_pred : -np 2 ./egg -c lnL_gaussian
```

# Running emus
In order to use emulation on already emulatable capabilities, one needs to construct the commandline arguments including specifying MPI configuration and constructing the emulator section of the yaml/inifile.

## Commandline arguments

The emulator system is MPI parallelized using MPMD (Multiple Program, Multiple Data) launch syntax, using the colon syntax ```mpirun -np N1 ./executable1 : -np N2 ./executable2```. This means that the executables are launched separately with a specified number of MPI processes for each of the executables. No new processes are spawned for the emulators, they are allocated at start-up. 

The emulator system is designed to work with 1 or more MPI processes, regardless of the number of MPI processes of the main GAMBIT exectutable. The design of the emulator plugin decides how the MPI processes of the emulator is utilized, but a typical setup is one MPI process for training the emulator and one for prediction. 

One executable has to be launched for each different capability one wish to emulate. In order for the emulator executables to know which capability they are emulating the capability has to be specified in the commandline in the following way:
```bash
mpirun -np N ./gambit ... : -np N1 ./egg -c <capability_name1> : -np N2 ./egg -c <capability_name2>
```

Help can be found by running ```./egg -h```.

## Inifile (yaml setup)
The inifile has to include emulator specific setting for each capability. A separate *Emulator* block in the yaml file specifies which capabilities are to be emulated and the settings of the emulator plugin specifically for that capability. 

The general set-up of such a inifile section is as follows:
```yaml
Emulation:
  use_emulator:
  - capability1
  - capability2

  emulators:
    capability1:
      plugin: plugin_name
      train: true/false
      pre_trained: true/false
      predict: true/false
      uncertainty:
        - 0.01
      timeout: 300s
      plugin_settings: ...

    capability2: 
      plugin: plugin_name
      train: true/false
      pre_trained: true/false
      predict: true/false
      uncertainty:
        - 0.01
      timeout: 300s
      plugin_settings: ...

```

Each capability has to specify the plugin, whether its training, predicting or has a pre-trained emulator. One also has to specify the uncertainty threshold for the capability, with one uncertainty for each value emulated. For capabilities with more than one output, one has to specify the uncertainty for both values. **OBS: what do we do if only one output is accepted?**

It is also possible to specify a timeout, where the default is 300s, where the run shuts down if there is no reply from the emulator side. This is to ensure that freezes in the emulator framework or miscommunication with the main processes causes the entire run to abort.


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
