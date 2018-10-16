#
# A dummy python library for testing GAMBIT backend setup
# Mimics the functionality of libfirst
#
# \author Pat Scott
# \date 2017-12
#
#

import numpy as np

#
# Some global variables:
#
array_length = 10
someInt = 0
someDouble = 0
someVector = []
isInitialized = False
prefix = "libthird 1.1: "

#
# Some functions:
#

# 'initialization'
def initialize(a):
  global someInt
  global someArray
  global isInitialized
  print
  print prefix, "This is function 'initialize'."
  someInt = a;
  someArray = np.array([2.0*x for x in range(array_length)])
  someVector.append(1.5)
  someVector.append(1.6)
  isInitialized = True
  print prefix, "Initialization done. Variable 'someInt' set to: ", someInt

# 'calculation'
def someFunction():
  global someDouble
  print
  print prefix, "This is function 'someFunction'.";
  if (isInitialized):
    print prefix, "Will now perform a calculation..."
    someDouble = 3.1415*someInt;
    print prefix, "Result stored in variable 'someDouble' is: ", someDouble;
  else:
    print prefix, "Not initialized. Cannot perform calculation.";


# 'byRefExample'
#double byRefExample (double& input)
#  std::cout << prefix << "This is function 'byRefExample'." << std::endl;
#  input = someDouble = 2.0*someInt;
#  return 2.1*someInt;


# 'byRefExample2'
#void byRefExample2 (double& input, double input2)
#  std::cout << prefix << "This is function 'byRefExample2'." << std::endl;
#  input = someDouble = 2.3*someInt + input2;

# return 'result'
def returnResult():
  print "I'm returnResult() from libthird.py, and I'm feeling well."
  return someDouble
