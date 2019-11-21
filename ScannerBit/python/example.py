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

print("WITH_MPI=",scan.WITH_MPI) # Test if ScannerBit was compiled with MPI enabled

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

myscan.run(inifile=settings, lnlike={"LogLike": like}, prior=prior, restart=True)

###
### can run diagnostics
### NOTE: can specify any number of object to run diagnostics on
###       e.g. myscan.diagnostics("twalk", "multinest", "ais", "priors", "scanners", ...)
###
# myscan.diagnostics("twalk")

###
### can use with pyyaml!
### NOTE: yaml vector keys, [...], must be preceded by !!/python/tuple 
###
# with open("ScannerBit.yaml", 'r') as f:
#     try:
#         inifile = yaml.load(f)
#     except yaml.YAMLError as exc:
#         print(exc)
# 
# myscan.run(inifile=inifile, lnlike={"LogLike": like}, prior=prior, restart=True)

###
### or can also run multiple proposes
###
# lnlike = {
#     "LogLike1": like1
#     "LogLike2": like2
# }
# myscan.run(inifile="ScannerBit.yaml", lnlike=lnlike, prior=prior, restart=True)
