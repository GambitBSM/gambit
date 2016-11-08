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
def runningMeanFast(x, N):
    return np.convolve(x, np.ones((N,))/N)[(N-1):]

all_iterations = np.arange(len(totalloop))
def add_logl_timing_data(ax,lmask,title,mode=None):
   labels = ["likelihood evaluation","inter-loop"]
   Nbins = 100
   if mode=='bin':
      p1, bin_edges1, binindices = binned_statistic(all_iterations[lmask], intraloop[lmask], statistic='mean', bins=Nbins)
      p2, bin_edges2, binindices = binned_statistic(all_iterations[lmask], interloop[lmask], statistic='mean', bins=Nbins)
      p3, bin_edges3, binindices = binned_statistic(all_iterations[lmask], totalloop[lmask], statistic='mean', bins=Nbins)
      x = bin_edges1[:-1]
      ax.set_ylabel("Average run-time\nper bin (ms)")
   elif mode=='running_mean':
      p1 = runningMeanFast(intraloop[lmask], Nbins)
      p2 = runningMeanFast(interloop[lmask], Nbins)
      p3 = runningMeanFast(totalloop[lmask], Nbins)
      x = all_iterations[lmask] # remove transient at beginning
      ax.set_ylabel("Running mean run-time\n(N={0}) (ms)".format(Nbins))
      print p3.shape, x.shape
   else:
      p1 = intraloop[lmask]
      p2 = interloop[lmask]
      p3 = totalloop[lmask]
      x  = all_iterations[lmask]
      ax.set_ylabel("Point run-time (ms)")
   ax.fill_between(x, 0, p3, facecolor='darkred', label="Total")
   ax.stackplot(x, p1, p2, labels=labels, lw=0)
   ax.set_xlabel("iteration")
   ax.set_title(title)

try:
  dumper_data = group["Runtime(ns) for MultiNest: dumper"]
  dumper_mask = np.array(group["Runtime(ns) for MultiNest: dumper_isvalid"],dtype=np.bool)
  dumper_y = dumper_data[dumper_mask] * 1e-6 # convert to milliseconds
  dumper_x = all_iterations[dumper_mask]
  fig = plt.figure(figsize=(12,12))
  N=5
  have_dumper=True
except KeyError:
  fig = plt.figure(figsize=(12,6))
  N=3
  have_dumper=False

def add_timefraction_plot(ax,lmask,title):
   # --- Evolving time-fraction plot ---
   # The idea: show what fraction of runtime is spent on various tasks,
   # as a function of (approximate) real-time. Real-time count will assume
   # that the total loop-time measurements are accurate, i.e. no runtime time 
   # is unaccounted for. It also assumes that we have all primary timing
   # measurements for all likelihood evaluations.
   
   # I think the easiest way to do this is to break up the run into a series of
   # time-slices, and compute the properties of each slice.
   # This also assumes we are only looking at data from one process at a time.
   # Might look bizarre on combined data.
   
   Nslices = 200.
   cum_runtime = np.cumsum(totalloop[lmask])
   total_runtime = cum_runtime[-1]
   slice_time = total_runtime/Nslices
   
   # Determine which iterations mark the endpoints of the slices
   Niter = len(cum_runtime)
   slice_times = np.arange(0,total_runtime+slice_time,slice_time)
   
   # Bin up the timing data according to these bin edges
   p1, bin_edges, binindices = binned_statistic(cum_runtime, intraloop[lmask], statistic='sum', bins=slice_times)
   p2, bin_edges, binindices = binned_statistic(cum_runtime, interloop[lmask], statistic='sum', bins=slice_times)
   p3, bin_edges, binindices = binned_statistic(cum_runtime, totalloop[lmask], statistic='sum', bins=slice_times)

   # Plot!
   x = bin_edges[:-1] * 1e-3 / 60. # bin left in minutes
   labels = ["likelihood evaluation","inter-loop"]
   ax.stackplot(x, p1/p3, p2/p3, labels=labels, lw=0, step='pre')
   ax.set_xlabel("Total runtime (minutes)")
   ax.set_ylabel("Use fraction")
   ax.set_title(title,y=1.3)

   # Add ticks every few bins labelling what iteration was reached by that point
   # First get the maximum iteration reached in each bin, then just pick some to show
   iters, bin_edges, binindices = binned_statistic(cum_runtime, all_iterations[lmask], statistic=np.max, bins=slice_times)
   iter_x = bin_edges[::20]
   iter_label = iters[::20]
   ax2 = ax.twiny()
   ax2.set_xlim(ax.get_xlim())
   ax2.set_xticks(iter_x)
   ax2.set_xticklabels([int(x) for x in iter_label])
   ax2.set_xlabel("Iteration reached")


# --- "Normal" timing plots ---


ax = fig.add_subplot(N,1,1)
add_timefraction_plot(ax,mask,"CPU usage distribution")
ax.legend(loc=1, frameon=False, framealpha=0,prop={'size':8})

ax = fig.add_subplot(N,1,2)
add_logl_timing_data(ax,mask,"Running mean runtime, all points",mode='running_mean')
plt.legend(loc=1, frameon=False, framealpha=0,prop={'size':8})

ax = fig.add_subplot(N,1,3)
add_logl_timing_data(ax,mask,"Unbinned runtime, all points")
if have_dumper: ax.plot(dumper_x,dumper_y,'o',c='r',ms=4,mew=0,label="dumper function")
plt.legend(loc=1, frameon=False, framealpha=0,prop={'size':8})

if have_dumper:
  ax = fig.add_subplot(N,1,4)
  # Need to shift mask to get interloop time for next point
  dumper_mask2 = np.zeros(len(dumper_mask),dtype=np.bool)
  dumper_mask2[1:] = dumper_mask[:-1]
  dumper_mask3 = np.zeros(len(dumper_mask),dtype=np.bool)
  dumper_mask3[:-1] = dumper_mask[1:]
  add_logl_timing_data(ax,dumper_mask2,"Unbinned runtime, dumper iterations only")
  ax.plot(dumper_x,dumper_y,'o',c='r',ms=4,mew=0,label="dumper function")
  plt.legend(loc=1, frameon=False, framealpha=0,prop={'size':8})
  
  ax = fig.add_subplot(N,1,5)
  non_dumper_mask = mask & (~dumper_mask2)
  add_logl_timing_data(ax,non_dumper_mask,"Unbinned runtime, non-dumper iterations")
  plt.legend(loc=1, frameon=False, framealpha=0,prop={'size':8})

#data = np.vstack([interloop[mask], intraloop[mask]]).T
#ax.hist(data, 1000, histtype='step', stacked=True, fill=True, label=labels)

#ax.stackplot(iterations[mask], interloop[mask], intraloop[mask], labels=["inter-loop","likelihood evaluation"])
#ax.plot(iterations[mask], totalloop[mask], c='k', lw=3, label="Total")
plt.tight_layout()
fig.savefig("timing_graphs.png")
print "Done! Saved 'timing_graphs.png'"
print
