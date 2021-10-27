#############################################################
# pippi: parse it, plot it
# ------------------------
# Utilities module for pippi.
#
# Author: Pat Scott (patscott@physics.mcgill.ca)
# Originally developed: March 2012
#############################################################

import sys
import os.path
import re
import numpy as np
from pippi_colours import *

def mapToRefLike(otherlike,array):
  #Map from one permitted likelihood form to another
  return [permittedLikes[otherlike](member) for member in array]

def safe_dir(dirname):
  #Check that dirname exists, if not then make it
  if not os.path.exists(dirname):
    os.makedirs(os.path.abspath(dirname))

def try_append(indices, cols, x):
  try:
    indices.append(cols.index(x))
  except:
    sys.exit("ERROR: hdf5 file does not contain a field titled \""+x+"\".")

def castable_to_int(x):
  try:
    int(x)
    return True
  except ValueError:
    return False

def usage():
  #Print pippi usage information
  print
  print 'You must be new here (or have fat fingers).  You can use pippi to'
  print
  print '  merge two or more chains:'
  print '    pippi merge <chain1> <chain2> ... <chainx>'
  print
  print '  post-process a chain:'
  print '    pippi pare <chain> <name_of_python_module> <name_of_function_in_module>'
  print
  print '  parse a chain using options in iniFile.pip:'
  print '    pippi parse iniFile.pip'
  print
  print '  write plotting scipts for a chain using options in iniFile.pip:'
  print '    pippi script iniFile.pip'
  print
  print '  run plotting scipts for a chain using options in iniFile.pip:'
  print '    pippi plot iniFile.pip'
  print
  print '  print an hdf5 file\'s computed column indices, using options in iniFile.pip:'
  print '    pippi probe iniFile.pip'
  print
  print '  parse, script and plot in one go:'
  print '    pippi iniFile.pip'
  print

def safe_open(filename):
  #Try to open input file
  try:
    infile = open(filename,"r")
    return infile
  except IOError:
    #Crash if file does not exist
    sys.exit('\n  Sorry, file '+filename+' not found or read-protected.  Quitting...\n')

def smart_open(filename,mode):
  #Try to open file for output
  try:
    outfile = open(filename,mode)
    return outfile
  except IOError:
    #Crash if file cannot be opened the way requested
    sys.exit('\n  Sorry, file '+filename+' cannot be opened for writing.\nCheck disk space and folder permissions.  Quitting...\n')

def is_functional_assignment(assignment):
  return len(re.findall("\$", assignment)) != len(re.findall("[\\\]\$", assignment))

def parse_functional_assignment(assignment, replacement):
  replacement_parts = replacement.split('$')
  return re.sub("\$([0-9]*)", replacement_parts[0]+'\\1'+replacement_parts[1], assignment)

class dataObject:
  #Class for pip file entries, containing their values, keys and expected data types

  pipFileKey = value = dataType = ''

  def __init__(self,pipEntry,dataType):
    #Save key and expected data type for new pip file field
    self.pipFileKey = pipEntry
    self.conversion = dataType

  def seek(self,string):
    #Look for field's key in string
    if self.pipFileKey in string: return True
    return False

  def convert(self,string):
    #Convert string to appropriate data format for pip file field
    string = string.strip()
    try:
      if string == '':
        self.value = None
      else:
        self.value = self.conversion(string)
    except:
      print "Failed to convert string:"
      print string
      sys.exit('Error: invalid data format in field '+self.pipFileKey+'. Quitting...\n')

#Conversion functions for parsing pip file entries

def integer(x):
  x = re.sub(r"[':;,]", '', x)
  if len(x.split()) != 1: raise Exception
  return int(x)

def floater(x):
  x = re.sub(r"[':;,]", '', x)
  if len(x.split()) != 1: raise Exception
  return float(x)

def string(x):
  if len(re.findall("'", x)) != 2: raise Exception
  return re.sub(r"^.*?'|'.*?$", '', x)

def safe_string(x):
  if len(re.findall("'", x)) != 2 or ';' in x: raise Exception
  return re.sub(r"^.*?'|'.*?$", '', x)

def boolean(x):
  x = re.sub(r"[':;,]", '', x)
  if len(x.split()) != 1: raise Exception
  if x.lower().strip() in ("yes", "true", "t", "1"):
    return True
  elif x.lower().strip() in ("no", "false", "f", "0"):
    return False
  else: raise Exception

def int_list(x): return single_list(x,integer)
def float_list(x): return single_list(x,floater)
def single_list(x,singleType):
  x = re.sub(r"[':;,]", ' ', x)
  returnVal = []
  for entry in x.split():
    returnVal.append(singleType(entry))
  return returnVal

def intuple_list(x): return tuple_list(x,integer)
def floatuple_list(x): return tuple_list(x,floater)
def tuple_list(x,tupleType):
  if len(re.findall("\{", x)) != len(re.findall("\}", x)): raise Exception
  x = re.findall("\{.+?\}", x)
  for i, pair in enumerate(x):
    pair = re.sub(r"[':;,\}\{]", ' ', pair).split()
    if len(pair) < 2: raise Exception
    x[i] = [tupleType(j) for j in pair]
  return x

def string_list(x):
  returnVal = []
  if len(re.findall("'", x))%2 != 0: raise Exception
  x = re.findall("'.+?'", x)
  for i, entry in enumerate(x):
    returnVal.append(string(entry))
  return returnVal

def int_dictionary(x):
  returnVal = {}
  x = re.findall(".+?:.+?[\s,;]+?|.+?:.+?$", x)
  for i, pair in enumerate(x):
    pair = re.sub("[\s,;]+$", '', pair).split(':')
    pair = [integer(pair[0]), integer(pair[1])]
    returnVal[pair[0]] = pair[1]
  return returnVal

def float_dictionary(x):
  returnVal = {}
  x = re.findall(".+?:.+?[\s,;]+?|.+?:.+?$", x)
  for i, pair in enumerate(x):
    pair = re.sub("[\s,;]+$", '', pair).split(':')
    pair = [integer(pair[0]), floater(pair[1])]
    returnVal[pair[0]] = pair[1]
  return returnVal

def floatuple_dictionary(x):
  returnVal = {}
  x = re.findall(".+?:{.+?}[\s,;]+?|.+?:{.+?}$", x)
  for i, pair in enumerate(x):
    pair = re.sub("[\s,;]+$", '', pair).split(':')
    pair = [integer(pair[0]), floatuple_list(pair[1])[0]]
    returnVal[pair[0]] = pair[1]
  return returnVal

def string_dictionary(x):
  returnVal = {}
  if len(re.findall("'", x))%2 != 0: raise Exception
  x = re.findall("(.+?\s*:\s*'.+?'[\s,;$]*?|'.+?'\s*:\s*.+?[\s,;]+?|'.+?'\s*:\s*.+?[\s,;]*?$)", x)
  for i, pair in enumerate(x):
    capture = re.findall("'.+?'", pair)
    if len(capture) > 1: raise Exception
    pair = re.sub("'.+?'", '__temp__', pair)
    pair = re.sub("[\s,;]+$", '', pair).split(':')
    for j, single in enumerate(pair):
      single.strip()
      if '__temp__' in single:
        pair[j] = string(capture[0].strip())
      else:
        pair[j] = integer(single)
    returnVal[pair[0]] = pair[1]
    returnVal[pair[1]] = pair[0]
  return returnVal

def int_pair_string_dictionary(x):
  returnVal = {}
  if len(re.findall("'", x))%2 != 0: raise Exception
  x = re.findall(".+?:'.+?'[\s,;]*", x)
  for i, pair in enumerate(x):
    pair = re.sub("[\s,;]+$", '', pair).split(':')
    for j, single in enumerate(pair):
      if single[0] == '\'':
        pair[j] = string(single)
      else:
        pair[j] = intuple_list(single)[0]
    if pair[0][0] in returnVal:
      returnVal[pair[0][0]][pair[0][1]] = pair[1]
    else:
      returnVal[pair[0][0]] = {pair[0][1]:pair[1]}
  return returnVal

def internal(x):
  return permittedInternals[re.sub(r"[':;,]", ' ', x).lower()]


#Global constants and simple one-liners
pippiVersion = 'v2.1'

def times1(x): return x
def half(x): return x*0.5
def negative(x): return -x
def negativehalf(x): return -x*0.5
def negln(x): return -np.log(x)
permittedLikes = {'-lnlike':times1,'lnlike':negative,'-2lnlike':half,'chi2':half,'2lnlike':negativehalf,'like':negln}
permittedLikes_samesign = ['-lnlike', '-2lnlike']
refLike = '-lnlike'

permittedMults = ['mult','mult.','multiplicity','multiplic.','mtpcty','Posterior']
refMult = permittedMults[0]

permittedPriors = ['prior','priors','pri.']
refPrior = permittedPriors[0]

mcmc = 'mcmc'
multinest = 'multinest'
other = 'other'
permittedInternals = {'mcmc':mcmc, 'multinest':multinest, 'other':other}
if permittedSchemes is not None: permittedInternals.update(permittedSchemes)
allowedIntMethods = ['bilinear', 'spline']

mainChain = dataObject('main_chain',safe_string)
secChain = dataObject('comparison_chain',safe_string)
doPosterior = dataObject('do_posterior_pdf',boolean)
doProfile = dataObject('do_profile_like',boolean)
oneDplots = dataObject('oneD_plot_quantities',int_list)
twoDplots = dataObject('twoD_plot_quantities',intuple_list)
contours1D = dataObject('oneD_contour_levels',float_list)
contours2D = dataObject('twoD_contour_levels',float_list)
obsPlots = dataObject('plot_observables',int_list)
keys = [mainChain,secChain,doPosterior,doProfile,oneDplots,twoDplots,contours1D,contours2D,obsPlots]
