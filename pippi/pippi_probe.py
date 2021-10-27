
#############################################################
# pippi: parse it, plot it
# ------------------------
# Simple HDF5 probing program for pippi.
#
# Author: Pat Scott (p.scott@imperial.ac.uk)
# Originally developed: Oct 2015
#############################################################

from pippi_read import *

# Define probe-specific pip file entries
col_assignments = dataObject('assign_to_pippi_datastream',string_dictionary)
keys = keys+[col_assignments]

#input:   filename = the name of the pip file
def probe(filename):
  #Parse pip file
  getIniData(filename,keys)
  # Open main chain and read in contents
  mainArray = getChainData(mainChain.value, assignments=col_assignments, probe_only=True)
