#!/usr/bin/env python

"""Test plotting of the spartan_multinest_hdf5.yaml results"""

#import numpy as np
import h5py
import numpy as np
from scipy.stats import mode, binned_statistic
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import sys

def usage():
   print ("\nusage: python plot_timing.py <path-to-hdf5-file> <group-containing-datasets> [sort-by-runtime (1/0)]\n"
          "\n"
          "Plots basic timing data for a gambit run\n. Note; not optimised for extremely large datasets, could run out of memory.")
   quit()  
 
if(  len(sys.argv)!=3
 and len(sys.argv)!=4): usage()

filename = sys.argv[1]
groupname = sys.argv[2]
sortbyruntime = True
if len(sys.argv)>3: 
   sortbyruntime = sys.argv[3]=="1"
if len(sys.argv)>4: 
   outname = sys.argv[4]
print "Opening file {0}...".format(filename)
f = h5py.File(filename,'r')
print "Opening group {0}...".format(groupname)
group = f[groupname]

# Basic timing groups

interloop         =          group["Runtime(ms) interloop"]
interloop_isvalid = np.array(group["Runtime(ms) interloop_isvalid"],dtype=np.bool)
intraloop         =          group["Runtime(ms) intraloop"]
intraloop_isvalid = np.array(group["Runtime(ms) intraloop_isvalid"],dtype=np.bool)
totalloop         =          group["Runtime(ms) totalloop"]
totalloop_isvalid = np.array(group["Runtime(ms) totalloop_isvalid"],dtype=np.bool)
loglike           =          group["LogLike"]
loglike_isvalid   = np.array(group["LogLike_isvalid"],dtype=np.bool)

# Should be timing data for EVERY point, check this.
# Use unitCube parameters to check against, should have these for every point attempted
unitp0           =          group["unitCubeParameters[0]"]
unitp0_isvalid   = np.array(group["unitCubeParameters[0]_isvalid"],dtype=np.bool)

# I think the timing data is always missing for one dataset, probably first or last. Turn off warning for now
#if(np.sum(interloop_isvalid) != np.sum(unitp0_isvalid)):
#   print "Warning! Number of timing (interloop) dataset entries ({0}) is inconsistent with number of parameter dataset entries ({1})!".format(np.sum(interloop_isvalid),np.sum(unitp0_isvalid))
#if(np.sum(intraloop_isvalid) != np.sum(unitp0_isvalid)):
#   print "Warning! Number of timing (intraloop) dataset entries ({0}) is inconsistent with number of parameter dataset entries ({1})!".format(np.sum(intraloop_isvalid),np.sum(unitp0_isvalid))
#if(np.sum(totalloop_isvalid) != np.sum(unitp0_isvalid)):
#   print "Warning! Number of timing (totalloop) dataset entries ({0}) is inconsistent with number of parameter dataset entries ({1})!".format(np.sum(totalloop_isvalid),np.sum(unitp0_isvalid))

mask = intraloop_isvalid & interloop_isvalid & totalloop_isvalid
Ntot = np.sum(mask)

# Compute basic stats for these quantites

def getstats(N,data,name,multiplier,unit):
   return u"{0:.1f}%: {1:8.2g} ({2:8.2g}) {3} {4:8.2g} {5} ; [{6:8.2g}, {7:8.2g}] {5} -- {8}".format(
         N*100,
         np.mean(data)*multiplier,
         np.median(data)*multiplier,
         pm,
         np.std(data)*multiplier,
         unit,
         np.min(data)*multiplier,
         np.max(data)*multiplier,
         name)

# Mean and standard deviation
pm = u"\u00B1"
print
print u"% of points timed: Mean (median) {0} standard deviation ; [min,max] of timing variables:".format(pm)
print u"Total number of samples: {0}".format(Ntot)
print "------------------------------------------------"
print getstats(1, interloop[mask], "Inter-loop time"           ,1e-3,"s") #convert milliseconds to seconds
print getstats(1, intraloop[mask], "Likelihood evaluation time",1e-3,"s")
print getstats(1, totalloop[mask], "Total time per iteration"  ,1e-3,"s")

# Now do it for all functors
# Compile list:
functor_name = []
functor_timing_data = []
functor_timing_data_isvalid = []
strstart = "Runtime(ns) for "
for itemname in group: 
   item = group[itemname]
   if isinstance(item,h5py.Dataset):
      if itemname.startswith(strstart) and not itemname.endswith("_isvalid"):
         functor_name += [itemname[len(strstart):]]
         functor_timing_data         += [itemname]
         functor_timing_data_isvalid += [itemname+"_isvalid"]

# Print data
tag = ""
if sortbyruntime:
  tag = " (sorted by mean runtime, slowest first)"
  datadict = {}
print "Functors{0}:".format(tag)
for name, dataname, dataname_isvalid in zip(functor_name, functor_timing_data, functor_timing_data_isvalid):
   data =          group[dataname]
   mask = np.array(group[dataname_isvalid],dtype=np.bool)
   N = float(np.sum(mask))
   if sortbyruntime:
      mean = np.mean(data[mask])
      datadict[mean] = (N/Ntot, data[mask], name, 1e-6, "ms")
   else:     
      print getstats(N/Ntot, data[mask], name, 1e-6, "ms") #convert nanoseconds to milliseconds
if sortbyruntime:
   for key, value in iter(sorted(datadict.iteritems(),reverse=True)):
       print getstats(*value)
print
print "Generating timing graphs..."

fig = plt.figure(figsize=(12,12))

all_iterations = np.arange(len(totalloop))
def add_logl_timing_data(ax,lmask,title,do_bins=True):
   labels = ["likelihood evaluation","inter-loop"]
   if do_bins:
      Nbins = 100
      p1, bin_edges1, binindices = binned_statistic(all_iterations[lmask], intraloop[lmask], statistic='mean', bins=Nbins)
      p2, bin_edges2, binindices = binned_statistic(all_iterations[lmask], interloop[lmask], statistic='mean', bins=Nbins)
      p3, bin_edges3, binindices = binned_statistic(all_iterations[lmask], totalloop[lmask], statistic='mean', bins=Nbins)
      x = bin_edges1[:-1]
      ax.set_ylabel("Average run-time per bin (ms)")
   else:
      p1 = intraloop[lmask]
      p2 = interloop[lmask]
      p3 = totalloop[lmask]
      x  = all_iterations[lmask]
      ax.set_ylabel("Point run-time (ms)")
   ax.stackplot(x, p1, p2, labels=labels)
   ax.plot(x, p3, c='k', lw=1.5, label="Total")
   ax.set_xlabel("iteration")
   ax.set_title(title)

dumper_data = group["Runtime(ns) for MultiNest: dumper"]
dumper_mask = np.array(group["Runtime(ns) for MultiNest: dumper_isvalid"],dtype=np.bool)
dumper_y = dumper_data[dumper_mask] * 1e-6 # convert to milliseconds
dumper_x = all_iterations[dumper_mask]

N=4
ax = fig.add_subplot(N,1,1)
add_logl_timing_data(ax,mask,"Binned mean runtime, all points")
plt.legend()

ax = fig.add_subplot(N,1,2)
add_logl_timing_data(ax,mask,"Unbinned runtime, all points",do_bins=False)
ax.plot(dumper_x,dumper_y,'o',c='r',ms=4,mew=0,label="dumper function")
plt.legend()

ax = fig.add_subplot(N,1,3)
# Need to shift mask to get interloop time for next point
dumper_mask2 = np.zeros(len(dumper_mask),dtype=np.bool)
dumper_mask2[1:] = dumper_mask[:-1]
dumper_mask3 = np.zeros(len(dumper_mask),dtype=np.bool)
dumper_mask3[:-1] = dumper_mask[1:]
add_logl_timing_data(ax,dumper_mask2,"Unbinned runtime, dumper iterations only",do_bins=False)
ax.plot(dumper_x,dumper_y,'o',c='r',ms=4,mew=0,label="dumper function")
plt.legend()

ax = fig.add_subplot(N,1,4)
non_dumper_mask = mask & (~dumper_mask2)
add_logl_timing_data(ax,non_dumper_mask,"Unbinned runtime, non-dumper iterations", do_bins=False)
plt.legend()

#data = np.vstack([interloop[mask], intraloop[mask]]).T
#ax.hist(data, 1000, histtype='step', stacked=True, fill=True, label=labels)

#ax.stackplot(iterations[mask], interloop[mask], intraloop[mask], labels=["inter-loop","likelihood evaluation"])
#ax.plot(iterations[mask], totalloop[mask], c='k', lw=3, label="Total")
plt.tight_layout()
fig.savefig("timing_graphs.png")
print "Done! Saved 'timing_graphs.png'"
print
