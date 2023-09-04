#!/usr/bin/env python

"""Combine data from several hdf5 files created by HDF5Printer into a single file"""
import signal
def sigint_handler(signum, frame):
    print('CTRL+C is blocked while the HDF5Printer combine script runs! Signal received, but ignored.')
signal.signal(signal.SIGINT, sigint_handler)

from hdf5tools import *
import math
import numpy as np
import h5py
import os
import sys

chunksize = 1000

bufferlength = 100                # Must match setting in hdf5printer.hpp
max_ppidpairs = 10*bufferlength   #   "  "

def usage():
   print("  Usage: python combine_hdf5.py <path-to-target-hdf5-file> <root group in hdf5 files> <tmp file 1> <tmp file 2> ...")
   print()
   print("  Attempts to combine the data in a group of hdf5 files produced by HDF5Printer in separate processes during a GAMBIT run.")
   print("  Use --delete_tmp flag to delete input files upon successful combination.")
   print("  Use --runchecks flag to run some extra validity checks on the input and output data (warning: may be slow for large datasets)")
   print("  Use --metadata_group <group> to select a custom name for the metadata group (default /metadata)")
   exit(1)

#====Begin "main"=================================

#if len(sys.argv)!=6 and len(sys.argv)!=7: usage()
#
runchecks=False
delete_tmp=False
if len(sys.argv)<3:
      usage()

# I dont think this works right...
if "--runchecks" in sys.argv:
  runchecks=True
  sys.argv.remove("--runchecks")

if "--delete_tmp" in sys.argv:
  delete_tmp=True
  sys.argv.remove("--delete_tmp")

if "--metadata_group" in sys.argv:
  metadata_group = sys.argv[sys.argv.index("--metadata_group")+1]
  sys.argv.remove("--metadata_group")
  sys.argv.remove(metadata_group)
  if metadata_group[0] != "/":
    metadata_group = "/" + metadata_group
else:
  metadata_group = "/metadata"

outfname = sys.argv[1]
group = sys.argv[2]
tmp_files = sys.argv[3:]
N = len(tmp_files)
RA_group = group + "/RA"

print("Working directory: ", (os.getcwd()))
print("Target combined filename:", outfname)
print("Root group: ", group)
print("Number of files to combine: ", N)
print("Files to combine: ", tmp_files)
print("")
print("Analysing input files...")

files = {}

sync_dsets = [set([]) for i in range(N)]
RA_dsets = [set([]) for i in range(N)]
RA_dsets_exclude = set(["RA_pointID","RA_pointID_isvalid","RA_MPIrank","RA_MPIrank_isvalid"])
metadata_dsets = [set([]) for i in range(N)]
sync_lengths = [0 for i in range(N)]
RA_lengths = [0 for i in range(N)]
metadata_lengths = [0 for i in range(N)]
fnames = tmp_files

for i,fname in enumerate(fnames):
   print("   Opening: {0}".format(fname))
   f = h5py.File(fname,'r')
   files[fname] = f
   if runchecks:
      print("Checking temporary file for duplicates...")
      check_for_duplicates(f,group)
   print("      Analysing...")
   datasets = []
   tmp_dset_metadata = {}
   tmp_RA_dset_metadata = {}
   tmp_metadata_dset_metadata = {}
   # First get total lengths of the sync datasets
   if group in f:
      get_dset_lengths(tmp_dset_metadata,f[group],sync_dsets[i])
      sync_lengths[i] = check_lengths(tmp_dset_metadata)
   else:
      raise ValueError("File '{0}' does not contain the group '{1}!'".format(fname,group))
   # Next get total lengths of the RA datasets
   if RA_group in f:
      get_dset_lengths(tmp_RA_dset_metadata,f[RA_group],RA_dsets[i])
      RA_lengths[i] = check_lengths(tmp_RA_dset_metadata)
   else:
      RA_lengths[i] = 0
      # No RA data in this file, but that's ok, it happens sometimes.
      #raise ValueError("File '{0}' does not contain the group '{1}!'".format(fname,RA_group))
   if metadata_group in f:
      get_dset_lengths(tmp_metadata_dset_metadata, f[metadata_group], metadata_dsets[i])
      metadata_lengths[i] = check_lengths(tmp_metadata_dset_metadata)
   else:
      raise ValueError("File '{0}' does not contain the metadata group '{1}!'".format(fname,metadata_group))
   print("      ...done")

print("sync_lengths: ", sync_lengths)
total_sync_length = sum(sync_lengths)
# Make sure all sync dsets have the same length

print("Sync dsets:")
for i,fname in enumerate(fnames):
   print(" In {0}".format(fname))
   if len(sync_dsets[i])==0:
      print("   - None")
   else:
      for item in sorted(sync_dsets[i]):
         print("   - ", item)
      print("   sync_length = {0}".format(sync_lengths[i]))

print("RA dsets:")
for i,fname in enumerate(fnames):
   print(" In {0}".format(fname))
   if len(RA_dsets[i])==0:
      print("   - None")
   else:
      for item in sorted(RA_dsets[i]):
         print("   - ", item)
      print("   RA_length = {0}".format(RA_lengths[i]))

print("Metadata dsets:")
for i, fname in enumerate(fnames):
   print(" In {0}".format(fname))
   if len(metadata_dsets[i])==0:
      print("   - None")
   else:
      for item in sorted(metadata_dsets[i]):
         print("   - ", item)
      print("   metadata_length = {0}".format(metadata_lengths[i]))

print("Combined sync length = ", total_sync_length)

print("Opening file for adding combined data:")
print("   {0}".format(outfname))
fout = h5py.File(outfname,'a')

if not group in fout:
   gout = fout.create_group(group)
else:
   if runchecks:
      print("Checking existing combined output for duplicates...")
      check_for_duplicates(fout,group)
   gout = fout[group]

# Check for existing dsets in the output (and get their lengths if they exist)
existing_dsets = {}
dsetlengths = {}
for name in gout:
   if isinstance(gout[name],h5py.Dataset):
      print("   Accessing existing dset:", name)
      existing_dsets[name] = gout[name]
      dsetlengths[name]   = gout[name].shape[0]

# check that the existing dsets have a consistent length
if len(dsetlengths)!=0:
   init_output_length = check_lengths(dsetlengths)
   print("Existing datasets have length ", init_output_length)
else:
   init_output_length = 0


# Resize the existing dsets to accommodate the new data
for dsetname,dset in existing_dsets.items():
   print("   Extending existing dset '{0}' to length {1}+{2}={3} to accommodate new data...".format(dsetname,init_output_length,total_sync_length,init_output_length+total_sync_length))
   dset.resize((init_output_length+total_sync_length,))

# Create dataset to match every sync and RA dataset
target_dsets = {}
all_sync_dsets = set([]).union(*sync_dsets)
all_RA_dsets   = set([]).union(*RA_dsets)
for dsetname,dt in sorted(all_sync_dsets):
   if not dsetname in gout:
      print("   Creating empty dset:", dsetname)
      target_dsets[dsetname] = gout.create_dataset(dsetname, (init_output_length+total_sync_length,), chunks=(chunksize,), dtype=dt, maxshape=(None,))
   else:
      target_dsets[dsetname] = gout[dsetname]
for dsetname,dt in sorted(all_RA_dsets):
   if not dsetname in RA_dsets_exclude:
      if not dsetname in gout:
         print("   Creating empty dset:", dsetname)
         target_dsets[dsetname] = gout.create_dataset(dsetname, (init_output_length+total_sync_length,), chunks=(chunksize,), dtype=dt, maxshape=(None,))
      else:
         target_dsets[dsetname] = gout[dsetname]

# Copy data from separate sync datasets into combined datasets
nextempty=init_output_length
for fname in fnames:
   print("Copying sync data from file:")
   print("   {0}".format(fname))
   print("to file:")
   print("   {0}".format(outfname))
   fin = files[fname]

   if runchecks:
     print("Checking {0}[{1}] for duplicate entries".format(fname,group))
     check_for_duplicates(fin,group)
     print("No duplicates, proceeding with copy")

   dset_length=None
   for itemname in fin[group]:
      item = fin[group][itemname]
      if isinstance(item,h5py.Dataset):
        #print itemname,"is a Dataset"
         if dset_length==None:
            dset_length=item.shape[0]
         #Do the copy
         copy_dset_whole(item,gout[itemname],nextempty)
   if(dset_length==None):
      print("No sync dsets found! Nothing copied!")
   else:
      if runchecks:
         print("Re-checking combined file for duplicates...")
         check_for_duplicates(fout,group)
      nextempty+=dset_length


# Copy data from RA datasets into combined dataset
for fname in fnames:
   fin = files[fname]
   if RA_group in fin and "RA_MPIrank" in fin[RA_group]:
      print("RA data detected in file:")
      print("   {0}".format(fname))
      print("Copying it to file:")
      print("   {0}".format(outfname))

      # Get write targets
      dset_length=fin[RA_group]["RA_MPIrank"].shape[0]

      # Do this in chunks matching the max_ppidpairs value in hdf5printer.hpp
      nchunks = np.ceil(dset_length / (1.*max_ppidpairs))
      for i in range(int(nchunks)):
         imin = i*max_ppidpairs
         imax = np.min([(i+1)*max_ppidpairs, dset_length])

         pointIDs_in         = fin[RA_group]["RA_pointID"][imin:imax]
         mpiranks_in         = fin[RA_group]["RA_MPIrank"][imin:imax]
         pointIDs_isvalid_in = np.array(fin[RA_group]["RA_pointID_isvalid"][imin:imax],dtype=np.bool)
         mpiranks_isvalid_in = np.array(fin[RA_group]["RA_MPIrank_isvalid"][imin:imax],dtype=np.bool)

         mask_in = (pointIDs_isvalid_in & mpiranks_isvalid_in)
         print("...{0} scheduled RA writes found.".format(np.sum(mask_in)))

         # convert entries to single values to facilitate fast comparison
         IDs_in = cantor_pairing(pointIDs_in[mask_in],mpiranks_in[mask_in])

         #if runchecks:
         #   print "   checking input selection for duplicate keys..."
         #   ids  = IDs_in
         #   pid  = pointIDs_in[mask_in]
         #   rank = mpiranks_in[mask_in]
         #   for ID,p,r in zip(ids,pid,rank):
         #      Nmatches = np.sum(ID==ids)
         #      if Nmatches>1:
         #         print "   Warning!", ID, "is duplicated {0} times!".format(Nmatches)
         #         pMatch = np.sum(p==pid)
         #         rMatch = np.sum(r==rank)
         #         if pMatch>1 or rMatch>1:
         #           print "   ...pointID duplicate count: ", pMatch
         #           print "   ...MPIrank duplicate count: ", rMatch

         # Find them in the target output file
         # TODO: this part could still cause memory issues if the output datasets are too big
         pointIDs_out         = fout[group]["pointID"]
         mpiranks_out         = fout[group]["MPIrank"]
         pointIDs_isvalid_out = np.array(fout[group]["pointID_isvalid"][:],dtype=np.bool)
         mpiranks_isvalid_out = np.array(fout[group]["MPIrank_isvalid"][:],dtype=np.bool)

         mask_out = (pointIDs_isvalid_out & mpiranks_isvalid_out)
         print("...{0} possible RA targets found.".format(np.sum(mask_out)))

         # convert entries to single values to facilitate fast comparison
         IDs_out = cantor_pairing(
                     np.array(pointIDs_out[mask_out],dtype=np.longlong),
                     np.array(mpiranks_out[mask_out],dtype=np.longlong)
                     )
         # check that the pairing has not overflowed
         if np.any(IDs_out<0):
            raise ValueError("Error while computing cantor pairing for RA to SYNC matching! Integer overflow detected, so matching will fail! Please increase the size of the integer type used!")

         if runchecks:
            print("   checking output selection for duplicate keys...")
            ids  = IDs_out
            pid  = pointIDs_out[mask_out]
            rank = mpiranks_out[mask_out]
            for ID,p,r in zip(ids,pid,rank):
               Nmatches = np.sum(ID==ids)
               if Nmatches>1:
                  print("   Warning!", ID, "is duplicated {0} times!".format(Nmatches))
                  Match = np.sum((p==pid) & (r==rank))
                  if Match>1:
                    print("   ...MPIrank/pointID duplicate count: ", Match)

         # Find which IDs in the output dataset are write targets
         target_mask_small = np.in1d(IDs_out,IDs_in)

         # Cast the mask back so that it works on the original dataset
         # (TODO: is there a more efficient way to do this? "target_mask[mask_out][target_mask_small] = True" does not work.)
         target_length = fout[group]["pointID"].shape[0]
         alltargetindices = np.arange(target_length)
         maskindices = alltargetindices[mask_out][target_mask_small]

         target_mask = np.zeros(target_length, dtype=bool)
         target_mask[maskindices] = True

         if runchecks:
            print("   Double-checking that all selected input dset entries have matching targets in the output dsets...")
            for ID,pid,rank in zip(IDs_in,pointIDs_in[mask_in],mpiranks_in[mask_in]):
               if ID not in IDs_out: #[target_mask_small]:
                  print("   Warning! No target for ID {0} found in output selection! ({1},{2})".format(ID,pid,rank))
                  indexid = np.where( (np.array(IDs_out)==ID) )
                  index   = np.where( (np.array(pointIDs_out[mask_out])==pid) &
                                      (np.array(mpiranks_out[mask_out])==rank) )
                  print("index of match by ID       = ", indexid)
                  print("index of match by pid,rank = ", index)
                  print("pid,rank =",pid,rank)
                  print("pointID? ", pointIDs_out[mask_out][index])
                  print("valid? ",   pointIDs_isvalid_out[mask_out][index])
                  print("rank? ",  mpiranks_out[mask_out][index])
                  print("valid? ", mpiranks_isvalid_out[mask_out][index])
                  print("cantor =", cantor_pairing(pid,rank))
                  print("cantor==ID? ", cantor_pairing(pid,rank)==ID)


         # Number of "true" elements in target mask should match number of elements in 'in' arrays (after masking)
         # Check this
         ntargets = np.sum(target_mask)
         nsources = np.sum(mask_in)
         if ntargets!=nsources:
            raise ValueError("Error while computing targets for RA writes! Number of target matches for writes in the output dataset ({0}) does not match the number of elements scheduled for copying {1}!".format(ntargets,nsources))

         ## Just some test code which I decided to keep around since it is helpful
         ## for understand how the rearrangment of the input data to match the output
         ## selection works.
         ##
         ## \code
         ## # Compute sorting index array for rearranging the source entries to match the target locations
         ## # The way this works is a bit trippy, but it is fast.
         ## #y = target (IDs_out)
         ## #x = sources (IDs_in)
         ## #result = array of length(y), containing positions of
         ## #e.g.
         ## #x = np.array([3,5,7,1 ,9  ,8,6,6])
         ## #y = np.array([2,1,5,10,100,6])
         ## # out = [ - 3 1 - - 6 ]
         ## # i.e. "1" in y, is in position index 3 of x.
         ## x1 = np.array([0,1,2,3,4,5,6,7,8])
         ## y1 = np.array([4,3,5,0,1,2,6,8,7])
         ## # where in x is each element of y?
         ## # should give back y, since e.g. 4 is at index 4 in x
         ## # then using ypos as indices on x[sort1], should again return y.
         ## xsort1 = np.argsort(x1)
         ## ypos1 = np.searchsorted(x1[xsort1], y1)
         ## print "verifying..."
         ## print y1
         ## print ypos1
         ## print xsort1[ypos1]
         ## # less trivial test:
         ## x2 = np.array([0,1,7,2,7,8,6,4])
         ## y2 = np.array([4,0,1,2,6,8,7])
         ## # indices array should be:
         ## #            [8,1,2,3,7,5,2]
         ## # (but in our case we don't want duplicates in either the target or input arrays!)
         ## xsort2 = np.argsort(x2)
         ## ypos2 = np.searchsorted(x2[xsort2], y2)
         ## indices = xsort2[ypos2]
         ## print "verifying..."
         ## print x2
         ## print xsort2
         ## print x2[xsort2]
         ## print "y2"
         ## print y2
         ## print ypos2
         ## print indices
         ## print x2[indices]
         ## \endcode

         print("   Sorting input data to match order in output selection...")
         xsort = np.argsort(IDs_in)
         yindex = np.searchsorted(IDs_in[xsort], IDs_out[target_mask_small])
         fancyindices = xsort[yindex]

         if runchecks:
            print("   Checking that matching of input data to output selection has succeeded...")
            print(yindex[:10])
            for k,(i,j) in enumerate(zip(IDs_out[target_mask_small][:100],IDs_in[fancyindices[:100]])):
              if i!=j:
                print("   Warning! Mismatch found. At position {0}, input ID ({1}) != output ID ({2})".format(k,i,j))
                #print i,j
                #print IDs_out[k-1:k+2]
                #print IDs_in[fancyindices[k-1:k+2]]
                #print "pids and ranks:"
                #print pointIDs_in[mask_in][fancyindices[k-1:k+2]]
                #print mpiranks_in[mask_in][fancyindices[k-1:k+2]]

         # Copy the data from the source to the target, after first
         # rearraging the source according to the index array we just created
         for itemname in fin[RA_group]:
            item = fin[RA_group][itemname]
            if isinstance(item,h5py.Dataset) and not itemname in RA_dsets_exclude:
               #Do the copy
               indset = item[imin:imax]
               #(TODO: figure out how to chunk this...)
               outdset = fout[group][itemname]
               #Check that types match
               if indset.dtype!=outdset.dtype:
                  raise ValueError("Type mismatch detected between dataset {0} in file {1} (dtype={2}), and matching dataset in output file {3} (dtype={3})".format(itemname,fname,indset.dtype,outfname,outdset.dtype))
               #can't do the fancy list-indexing directly on the hdf5 dataset (the boolean assignment should be ok though)
               print("   Copying RA data for dataset", itemname)
               outdset[target_mask] = indset[mask_in][fancyindices]

# DEBUGGING
# Check for duplicates in combined output
if runchecks:
   print("Checking final combined output for duplicates...")
   check_for_duplicates(fout,group)

# Open metadata group in existing output
if not metadata_group in fout:
   mout = fout.create_group(metadata_group)
else:
   mout = fout[metadata_group]

# Check for existing dsets in the output (and get their lengths if they exist)
existing_metadata_dsets = {}
metadata_dsetlengths = {}
existing_dates = []
for name in mout:
   if isinstance(mout[name],h5py.Dataset):
      print("   Accessing existing metadata dset:", name)
      existing_metadata_dsets[name] = mout[name]
      metadata_dsetlengths[name]   = mout[name].shape[0]
      if name == "Date":
        existing_dates.append(mout["Date"])

# check that the existing dsets have a consistent length
if len(metadata_dsetlengths)!=0:
   init_output_metadata_length = check_lengths(metadata_dsetlengths)
   print("Existing metadata_datasets have length ", init_output_metadata_length)
else:
   init_output_metadata_length = 0

total_metadata_length = init_output_metadata_length
marked_for_copy = [[] for i in range(N)]
print("Computing total required metadata length")
for i, fname in enumerate(fnames):
   fin = files[fname]
   if "Date" in fin[metadata_group]:
     dates = fin[metadata_group]["Date"]
     dates_length = dates.shape[0]
     marked_for_copy[i] = [False]*dates_length
     for j in range(dates_length):
       if dates[j] not in existing_dates:
         total_metadata_length += 1
         existing_dates.append(dates[j])
         marked_for_copy[i][j] = True
   else:
      total_metadata_length += metadata_lengths[i]
print("Combined metadata length = ", total_metadata_length)

# Resize the existing metadata dsets to accommodate the new data
for dsetname,dset in existing_metadata_dsets.items():
   print("   Extending existing metadata dset '{0}' to length {1} to accommodate new data...".format(dsetname,total_metadata_length))
   dset.resize((total_metadata_length,))

# Create dataset to match every metadata dataset
target_dsets = {}
all_metadata_dsets   = set([]).union(*metadata_dsets)
for dsetname,dt in sorted(all_metadata_dsets):
   if not dsetname in mout:
      print("   Creating empty metadata dset:", dsetname)
      target_dsets[dsetname] = mout.create_dataset(dsetname, (total_metadata_length,), chunks=(chunksize,), dtype=dt, maxshape=(None,))
   else:
      target_dsets[dsetname] = mout[dsetname]

# Copy data from separate sync datasets into combined datasets
for i, fname in enumerate(fnames):
   print("Copying metadata data from file:")
   print("   {0}".format(fname))
   print("to file:")
   print("   {0}".format(outfname))
   fin = files[fname]

   # If there is no info in marked for copy, there was no Date dataset, so copy everything
   if len(marked_for_copy[i]) == 0:
     dset_length=None
     for itemname in fin[metadata_group]:
        nextempty=init_output_metadata_length
        item = fin[metadata_group][itemname]
        if isinstance(item,h5py.Dataset):
           if dset_length==None:
              dset_length=item.shape[0]
           #Do the copy
           copy_dset_whole(item,mout[itemname],nextempty)
        nextempty+=dset_length

    # Otherwise copy only those that are marked
   else:
      for itemname in fin[metadata_group]:
        nextempty=init_output_metadata_length
        for j,item in enumerate(fin[metadata_group][itemname]):
          if marked_for_copy[i][j]:
             #Do the copy
             mout[itemname][nextempty] = item
             nextempty+=1


# If everything has been successful, delete the temporary files
if delete_tmp:
   print("Deleting temporary HDF5 files...")
   for fname in fnames:
      print("   {0}".format(fname))
      os.remove(fname)

print("Data combination completed")
