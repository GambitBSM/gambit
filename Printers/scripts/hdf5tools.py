#!/usr/bin/env python

"""Tools for reading/writing data from HDF5 files"""

import h5py
import math
import sys

# Buffer variables
chunksize = 1000
bufferlength = 100                # Must match setting in hdf5printer.hpp
max_ppidpairs = 10*bufferlength   #   "  "

def get_dset_lengths(d,group,dsets):
   for itemname in group: 
      item = group[itemname]
      if isinstance(item,h5py.Dataset):
         #print itemname,"is a Dataset"
         dsets.add((itemname,item.dtype))
         if itemname in d:
            d[itemname] += item.shape[0]
         else:
            d[itemname] = item.shape[0]
      if isinstance(item,h5py.Group):
         #print itemname,"is a Group"
         pass

def check_lengths(d):
   length = None
   for key,value in d.items():
      if length==None: 
         length=value
      elif length!=value:
         raise ValueError("Length of dataset '{0}' is inconsistent with the others in the target group! (length was {1}; previous dataset had length={2})".format(key,value,length)) 
   if length==None:
      # No datasets found; manually set length to zero
      length = 0
   return length 

def copy_dset(indset,outdset,nextempty,basemsg=""):
   lengthtocopy = indset.shape[0]
   chunksleft = math.ceil(lengthtocopy/float(chunksize))
   remainder = lengthtocopy % chunksize
   start = 0
   stride = chunksize
   Nchunks=chunksleft
   while(chunksleft!=0):
      if(chunksleft % 1 == 0): 
        sys.stdout.write("{0}: {1}%         \r".format(basemsg,int(100*(Nchunks-chunksleft)/Nchunks)))
        sys.stdout.flush()
      if(remainder!=0 and chunksleft==1):
         stride=remainder
      outdset[nextempty+start:nextempty+start+stride] = indset[start:start+stride]
      start+=stride
      chunksleft-=1

# As above, but copied the whole input dataset into memory before writing it out
# This is mainly for performance comparison purposes.
def copy_dset_whole(indset,outdset,nextempty,basemsg=""):
   lengthtocopy = indset.shape[0]
   start = 0
   sys.stdout.write("{0}         \r".format(basemsg))
   sys.stdout.flush()
   outdset[nextempty:nextempty+lengthtocopy] = indset

# Combine two integers into one integer with unique mapping
def cantor_pairing(x,y):
   return (x+y)*(x+y+1)//2 + y

# Check for duplicate entries in datasets
def check_for_duplicates(fout,group):
   pointIDs_out         = fout[group]["pointID"]
   mpiranks_out         = fout[group]["MPIrank"]
   pointIDs_isvalid_out = np.array(fout[group]["pointID_isvalid"][:],dtype=np.bool)
   mpiranks_isvalid_out = np.array(fout[group]["MPIrank_isvalid"][:],dtype=np.bool)
   mask_out = (pointIDs_isvalid_out & mpiranks_isvalid_out) 
   # convert entries to single values to facilitate fast comparison
   IDs_out = cantor_pairing( 
               np.array(pointIDs_out[mask_out],dtype=np.longlong),
               np.array(mpiranks_out[mask_out],dtype=np.longlong)
               )
   ids  = IDs_out
   pid  = pointIDs_out[mask_out]
   rank = mpiranks_out[mask_out]
   error = False
   for ID,p,r in zip(ids,pid,rank):
      if(p==1 and r==0):
         print("   Spotted first entry ({0},{1})".format(r,p))
      Nmatches = np.sum(ID==ids)
      if Nmatches>1:
         print("   Error! ID", ID, "is duplicated {0} times!".format(Nmatches))
         error = True
         matches = (p==pid) & (r==rank)
         Nmatches2 = np.sum(matches)
         if Nmatches2>1:
           print("   ...MPIrank/pointID ({0},{1}) duplicate count: {2}".format(r,p,Nmatches2))
           dup_locs = np.where(matches)
           print("      Indices of duplicates are:", dup_locs)
         else:
           print("   ...No duplicate pid and rank pairs detected! This seems to indicate that something is screwed up in the Cantor pairing")
  
      if error==True:
         raise ValueError("Duplicates detected in output dataset!")



