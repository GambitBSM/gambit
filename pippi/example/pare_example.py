
#############################################################
# pippi: parse it, plot it
# ------------------------
# Example post-processing program for pippi.  You should write
# your own version of this routine to perform whatever 
# operations on your chain you are interested in.  Make sure
# your own parsing function respects the same calling 
# conventions as this one (ie don't expect pippi to play nice
# with you if you hook it up to a function that returns 
# 'pippi sucks' or similar, instead of a modified chain point). 
#
# Author: Pat Scott (patscott@physics.mcgill.ca)
# Originally developed: March 2012
#############################################################


def strip(chainPoint):

  # You will need to know the identities of your own chain columns at this stage to operate on them...

  # Suppose I have some particular vendetta against values < 1000 of the parameter in the third column,
  # and the multiplcity and likelihood are in the first and second columns, respectively: 

  if chainPoint[2] < 1e3:
    # This point is lame - kill it.
    chainPoint[0] = 0
    chainPoint[1] = 1e10

  return chainPoint
