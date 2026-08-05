
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
The emulators only accept input in the form of vectors of doubles. If the input to the capability is of a different form, for example a set of different values, the user needs to define a translation function for converting from whichever format into a vector of doubles. This should be defined in the module namespace as ```capability_EmulatorTranslateInput(std::vector<double> &input)```. 

The predicted output for the capability is also a vector of doubles, and requires a translation function to the capability's output format. This is defined in the module namespace as a function called ```capability_EmulatorTranslatePrediction(std::vector<double>& prediction, std::vector<double>& uncertainty, type& result)```, which takes the prediction and prediction uncertainty, and insert the values into the correct format in ```results```.  

During training both the input and the target value (with uncertainty) needs to be translated before sending it to the emulator training function. The function ``` capability_EmulatorTranslateTarget(std::vector<double>& target, type& result, std::vector<double>& uncertainty)```, takes the result from the capability evaluation (with uncertainty if possible), and insert it into a target vector of doubles. 

## Defining Threshold function (optional)
The function for accepting or rejecting the emulator prediction can also be user specified, but there is a default threshold function which automatically checks the uncertainty of the prediction to the uncertainty threshold specified in the yaml file. 

To create a threshold function for a capabilty, the module namespace must include a function called ```capability_EmulatorCheckThreshold(str& name, std::vector<double>& uncertainty)```. The name of the capability has to be taken as an input in order to access the correct uncertainty threshold from the inifile, as well as the prediction uncertainty.


# Making emulators
## Overview
The emulator executable is called EGG (full name), and is the interface between GAMBIT and the emulator system. EGG receives messages from the GAMBIT MPI processes, evaluates the requests using the emulator plugins and sends the predictions from the emulators back to the same process. The plugin is connected to the EGG through a C interface, since the plugins are Python based.

The internal usage of the allocated MPI processes for EGG is determined mainly by the plugins. The emulator system is designed so that all MPI processes corresponding to one capability's EGG receives the predict/train message, and the plugin decides what those MPI processes do internally. The most simple system is a 2 process EGG, with one process dedicated to training and one to prediction, but this is coded into the python emulator plugin. The most important part is that only one MPI processes from the EGG sends the prediction back to the waiting GAMBIT process. 

**On the GAMBIT side, exactly one prediction is expected.** If none arrive, then the process wait for a timeout period before shutting down the entire run. If two arrives, then the second prediction will be queued until that same GAMBIT rank requests a prediction next time, and will cause failure/desyncronization. A flag that has to be set in the emulator plugin to determine which rank should send the message back to GAMBIT, which is checked in EGG. If the flag is set for more than one process, this will double-stack the predictions silently since there are currently no checks to avoid this. 

## Python Plugin
When designing a python emulator plugin, the plugin needs to include two main functions: *train* and *predict*.

The ```train`` function has to receive the input parameters, the training target (evaluated function output), the uncertainty of the training target and a flag. The function does not return anything, and GAMBIT is not expecting any reply. 

The ```predict``` function has to receive the input parameters only and a flag. If the specified rank does perform the prediction, then the flag has to be set to true in order to trigger a prediction reply in the EGG. The ```predict``` function has to return a vector of doubles for the prediction results and one vector of doubles for the uncertainty. If the prediction is invalid or NaN, a flag is returned to GAMBIT identifying the invalidity, and that flag can be set inside the plugin, but will automatically be added to the MPI message if the resulting prediction is NaN/inf. 

In both the ```train`` and ```predict`` functions, the plugin designer can decide how the MPI processes are utilized. In the example ```pygptreeo```plugin, the rank 0 is used for prediction and rank 1 for training, if the emulator is run with 2 processes for the EGG. If the EGG only has one process, then that process will do both training and prediction. Future work includes making a emulator plugin with master-worker patterns, but it should be possible without too much hassle. 

Examples of a minimal plugin set-up:
```py
import emulator_plugin as eplug
import numpy as np


class Test(eplug.emulator):

    __version__="1.0.0"

    def __init__(self, **options):

        super().__init__()
        print("starting test emulator plugin x")

    def train(self, x, y, sigs, flag):

        print(f"training inputed points, x: {x}; y: {y}; sigs: {sigs}, train: {flag.train}, predict: {flag.predict}")

        return

    def predict(self, x, flag):

        print(f"predicted input, x: {x}, train: {flag.train}, predict: {flag.predict}")

        flag.result = True
        
        return (np.array([3.5]), np.array([0.2]))

__plugins__={"emutest": Test}
```

## c interface (enter at own risk)
TODO: Greg
