"""Demonstrations of bugs in current interface"""

# Setup ================
import os
import sys
import ctypes
import yaml

flags = sys.getdlopenflags()
sys.setdlopenflags(flags | ctypes.RTLD_GLOBAL)

# NOTE: If you want to ScannerBit from a different directory
#       put this directory (ScannerBit/python) in the
#       python environment variable "PYTHONPATH".
import ScannerBit as scan 

# define likelihood, technically optional
def like(m):
    a = m["model1::x"]
    scan.print("my_param", 0.5) # can print custom parameters 
    
    return -a*a/2.0

# define prior, optional
def prior(vec, map):
    # tell ScannerBit that the hypergrid dimension is 1
    scan.ensure_size(vec, 1) # this needs to be the first line!
    
    map["model1::x"] = 5.0 - 10.0*vec[0]

# declare scan object
myscan = scan.scan(True)

# run scan
#myscan.run(inifile="ScannerBit.yaml", lnlike={"LogLike": like}, prior=prior, restart=True)

# Run scan from dict instead of YAML file
settings = {
"Parameters": {
  "model1": {
    "x": None,
    }
  },
"Priors": {
  "x_prior": {
    "prior_type": 'flat',
    "parameters": ['model1::x'],
    "range": [1.0, 40.0],
    }
  },
"Printer": {
  "printer": "hdf5",
  "options": {
    "output_file": "results.hdf5",
    "group": "/",
    "delete_file_on_restart": "true",
    }
  },
"Scanner": {
  "scanners": {
    "twalk": {
      "plugin": "twalk",
      "like": "LogLike",
      "tolerance": 1.003,
      "kwalk_ratio": 0.9,
      "projection_dimension": 4
      }
    },    
  "use_scanner": "twalk",
  "objectives": {
    "gaussian": {
      "plugin": "gaussian",
      "purpose": "LogLike",
      "parameters": {
        "param...20": None,
        "range": [-5, 5]
        }
      }
    }
  },
"KeyValues": {
  "default_output_path": "pyscannerbit_run_data/",
  "likelihood": {
    "model_invalid_for_lnlike_below": -1e6
    }
  }
}
# ============================
#  Bugs

#1. Cannot omit prior function despite prior specified in settings

#myscan.run(inifile=settings, lnlike={"LogLike": like}, prior=None, restart=True) # Error: Parameter model1::x requested by x_prior is either not defined by the inifile, is fixed, or is the "same as" another parameter.
#myscan.run(inifile=settings, lnlike={"LogLike": like}, prior="", restart=True) # Error: Parameter model1::x requested by x_prior is either not defined by the inifile, is fixed, or is the "same as" another parameter. 
myscan.run(inifile=settings, lnlike={"LogLike": like}, restart=True) # Error: Parameter model1::x requested by x_prior is either not defined by the inifile, is fixed, or is the "same as" another parameter. 

#2.




