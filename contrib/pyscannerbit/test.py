# --- pyscannerbit import
import sys
import ctypes
flags = sys.getdlopenflags()
sys.setdlopenflags(flags | ctypes.RTLD_GLOBAL)
import pyscannerbit as sb
# ---

# ---  Tools for opening results and plotting
import h5py
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
# ---

# Choose YAML file to run
yaml = "/net/archive/groups/plgggambit/ben/repos/gambit/yaml_files/ScannerBit_test.yaml"

# Test function
def test(pars):
  x = pars["test_model::x"]
  y = pars["test_model::y"]
  z = pars["test_model::z"]
  #print "pars: ", x, y, z
  
  return -0.5*( (x-10)**2 + (y-15)**2 + (z+3)**2 ) # fitness function to maximise (log-likelihood)

#print sb.run_test.__doc__

skip_scan = False
if not skip_scan:
   sb.run_test(yaml,test)

# Open the output file and examine scan results
f = h5py.File("runs/ScannerBit/samples/gambit_output.hdf5",'r')
group = f["/test"]

# Inspect output datasets
print [par for par in group]

# Helper function to simplify parameter extraction
def get_entry(name):
   x = group[name]
   x_isvalid = np.array(group[name+"_isvalid"],dtype=np.bool)
   return x, x_isvalid

x, mx = get_entry("test_model::x")
y, my = get_entry("test_model::y")
z, mz = get_entry("test_model::z")
loglike, ml = get_entry("LogLike")

m = ml & mx & my & mz # mask for points with all valid parameters and likelihood

# Simple scatter plot
fig = plt.figure(figsize=(8,6))
ax = fig.add_subplot(111)
ax.scatter(x[m],y[m],facecolor='k',edgecolor='',alpha=0.5,s=2)
ax.set_xlabel("x")
ax.set_ylabel("y")
fig.savefig("test_output_xy_scatter.png")

