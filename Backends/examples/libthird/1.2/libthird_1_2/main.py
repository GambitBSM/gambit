#
# A dummy python library for testing GAMBIT backend setup
# Mimics the functionality of libfirst
#
# \author Pat Scott
# \date 2018-10
#
#

from __future__ import print_function
import numpy as np

#
# Some global variables:
#
array_length = 10
someInt = 0
someDouble = 0
someVector = []
isInitialized = False
prefix = "libthird 1.2: "

#
# Some functions:
#

# 'initialization'
def initialize(a):
  global someInt
  global someArray
  global isInitialized
  print
  print(prefix, "This is function 'initialize'.")
  someInt = a
  someArray = np.array([2.0*x for x in range(array_length)])
  someVector.append(1.5)
  someVector.append(1.6)
  isInitialized = True
  print(prefix, "Initialization done. Variable 'someInt' set to: ", someInt)

# 'calculation'
def someFunction():
  global someDouble
  print
  print(prefix, "This is function 'someFunction'.")
  if (isInitialized):
    print(prefix, "Will now perform a calculation...")
    someDouble = 3.1415*someInt
    print(prefix, "Result stored in variable 'someDouble' is: ", someDouble)
  else:
    print(prefix, "Not initialized. Cannot perform calculation.")

# return 'result'
def returnResult():
  print("I'm returnResult() from libthird.py, and I'm feeling well.")
  return someDouble



# Gaussian loglike function used for testing python scanners.
# Used by the module function "lnL_gaussian_python" in ExampleBit_A/src/ExampleBit_A.cpp, 
# and similar to the function "lnL_gaussian" in the same file.
def lnL_gaussian_libthird(input_dict):
  result = 0.0

  print("LibThird 1.2: lnL_gaussian_libthird:  input_dict:", input_dict)

  mu = input_dict["mu"]
  sig = input_dict["sigma"]

  data = np.array([21.32034213,  20.39713359,  19.27957134,  19.81839231,
                   20.89474358,  20.11058756,  22.38214557,  21.41479798,
                   23.49896999,  17.55991187,  24.9921142 ,  23.90166585,
                   20.97913273,  18.59180551,  23.49038072,  19.08201714,
                   21.19538797,  16.42544039,  18.93568891,  22.40925288])

  for x in data:
    result += -0.5 * np.log(sig * sig) - 0.5 * (x-mu)**2 / (sig*sig);

  print("LibThird 1.2: lnL_gaussian_libthird:  result:", result)

  return result;