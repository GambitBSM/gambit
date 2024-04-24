import dill as pickle
import sys
import inspect
import logging
import os, errno

# stores a temporary copy of some arbitrary 'inputs' and 'outputs' 
# inside the cache directory. If the user provides an identical 
# set of inputs next time then the stored outputs will be used rather
# than having to recalculate them

# NOTE: deep equality is not yet working so using stored data still 
# requires an extra input option '--usecache'. In future it should
# be done automatically


# check if two arbitrary structures, v1 and v2, are equal
def deep_eq(v1,v2):
    return True

# remove file if it exists
def silentremove(filename):
    try:
        os.remove(filename)
    except OSError as e:
        if e.errno != errno.ENOENT:
            raise

# class to store the inputs used to calculate the outputs
class TheInputs:
  def __init__(self, name):
    self.name = name

# class used to store the outputs
class TheOutputs:
  def __init__(self, name):
    self.name = name

# loads a stored copy of TheOutputs if: (i) it exists, (ii) TheInputs are the same as last time
# otherwise recalculates TheOutputs using the provided function
def load_or_calc(inputs, func, force_recalc = False, size_limit = -1):

  input_unchanged = False
  stored_outputs_used = False

  if not os.path.exists('cache'):
    os.makedirs('cache')

  # check if stored inputs and data avaliable
  try:
    if force_recalc:
      print('DEBUG: forced recalc of ' + inputs.name)
      silentremove('cache/inputs_' + inputs.name + '.pkl')
      silentremove('cache/outputs_' + inputs.name + '.pkl')
      raise Exception("force_recalc")

    with open('cache/inputs_' + inputs.name + '.pkl', 'rb') as fin:
      inputs2 = pickle.load(fin)
      print('DEBUG: found stored inputs for ' + inputs.name)

      if deep_eq(inputs2,inputs):
        input_unchanged = True
        print('DEBUG: inputs for ' + inputs.name + ' are unchanged')
      else:
        print('DEBUG: deleting old stored inputs/outputs for ' + inputs.name)
        silentremove('cache/inputs_' + inputs.name + '.pkl')
        silentremove('cache/outputs_' + inputs.name + '.pkl')

      with open('cache/outputs_' + inputs.name + '.pkl', 'rb') as fin2:
        print('DEBUG: using stored outputs for ' + inputs.name)
        outputs = pickle.load(fin2)
        stored_outputs_used = True

  except:
    print('DEBUG: re-calculating ' + inputs.name)
    outputs = func(inputs)

    if (size_limit == -1 or get_size(inputs) <= size_limit):
      if not input_unchanged:
        with open('cache/inputs_' + inputs.name + '.pkl', 'wb') as fout:
          pickle.dump(inputs, fout, pickle.HIGHEST_PROTOCOL)
          print('DEBUG: caching inputs for ' + inputs.name)

      if (size_limit == -1 or get_size(outputs) <= size_limit):
        with open('cache/outputs_' + inputs.name + '.pkl', 'wb') as fout2:
          pickle.dump(outputs, fout2, pickle.HIGHEST_PROTOCOL)
          print('DEBUG: caching outputs for ' + inputs.name)
      else:
        print('DEBUG: wont store outputs_' + inputs.name + ' because it is too large')
    else:
      print('DEBUG: wont store inputs_' + inputs.name + ' because it is too large')

  return (outputs, input_unchanged, stored_outputs_used)


# Recursively finds size of objects in bytes
def get_size(obj, seen=None):
    size = sys.getsizeof(obj)
    if seen is None:
        seen = set()
    obj_id = id(obj)
    if obj_id in seen:
        return 0
    # Important mark as seen *before* entering recursion to gracefully handle
    # self-referential objects
    seen.add(obj_id)
    if hasattr(obj, '__dict__'):
        for cls in obj.__class__.__mro__:
            if '__dict__' in cls.__dict__:
                d = cls.__dict__['__dict__']
                if inspect.isgetsetdescriptor(d) or inspect.ismemberdescriptor(d):
                    size += get_size(obj.__dict__, seen)
                break
    if isinstance(obj, dict):
        size += sum((get_size(v, seen) for v in obj.values()))
        size += sum((get_size(k, seen) for k in obj.keys()))
    elif hasattr(obj, '__iter__') and not isinstance(obj, (str, bytes, bytearray)):
        try:
            size += sum((get_size(i, seen) for i in obj))
        except TypeError:
            logging.exception("Unable to get size of %r. This may lead to incorrect sizes. Please report this error.", obj)
    if hasattr(obj, '__slots__'): # can have __slots__ with __dict__
        size += sum(get_size(getattr(obj, s), seen) for s in obj.__slots__ if hasattr(obj, s))
        
    return size


# # TODO: code still not working
# def deep_eq(s, s2):

#   members = [attr for attr in dir(s) if not callable(getattr(s, attr)) and not attr.startswith("__")]
#   members2 = [attr for attr in dir(s2) if not callable(getattr(s2, attr)) and not attr.startswith("__")]
#   if len(members) != len(members2):
#     return False
#   for i in range(0,len(members2)):
#     if not deep_eq_builtin(members[i], members2[i]):
#       return False

#   return True

# def deep_eq_builtin(_v1, _v2):

#   import operator, types

#   if _v1 == _v1:
#     return True
  
#   def _deep_dict_eq(d1, d2):
#     k1 = sorted(d1.keys())
#     k2 = sorted(d2.keys())
#     if k1 != k2: # keys should be exactly equal
#       return False
#     return sum(deep_eq(d1[k], d2[k]) for k in k1) == len(k1)
  
#   def _deep_iter_eq(l1, l2):
#     if len(l1) != len(l2):
#       return False
#     return sum(deep_eq(v1, v2) for v1, v2 in zip(l1, l2)) == len(l1)
  
#   op = operator.eq
#   c1, c2 = (_v1, _v2)
  
#   # guard against strings because they are also iterable
#   # and will consistently cause a RuntimeError (maximum recursion limit reached)
#   for t in types.StringTypes:
#     if isinstance(_v1, t):
#       return op(c1, c2)

#   if isinstance(_v1, types.DictType):
#     op = _deep_dict_eq
#   else:
#     try:
#       c1, c2 = (list(iter(_v1)), list(iter(_v2)))
#     except TypeError:
#       c1, c2 = _v1, _v2
#     else:
#       op = _deep_iter_eq
  
#   return op(c1, c2)

# logger = logging.getLogger(__name__)



# stuff below used to convert boost classes into standard python classes.
# note that boost classes do not properly support pickle

class sarah_class:
  def __init__(self,name):
    self.name = name

  def add(self,other,name,ttype):
    setattr(self,"_"+name, ttype(getattr(other,name)()))
    setattr(self,name,lambda :getattr(self,"_"+name))


def decode_SARAH_partlist(obj):
    output_full = []
    for i in range(len(obj)):
        output = sarah_class("Particle")
        output.add(obj[i],"pdg",int)
        output.add(obj[i],"name",str)
        output.add(obj[i],"SM",bool)
        output.add(obj[i],"spinX2",int)
        output.add(obj[i],"chargeX3",int)
        output.add(obj[i],"color",int)
        output.add(obj[i],"mass",str)
        output.add(obj[i],"SC",bool)
        output.add(obj[i],"antiname",str)
        output.add(obj[i],"alt_name",str)
        output.add(obj[i],"alt_mass",str)
        output.add(obj[i],"tree_mass",str)
        output_full.append(output)
    return output_full


def decode_SARAH_paramlist(obj):
    output_full = []
    for i in range(len(obj)):
        output = sarah_class("Parameter")
        output.add(obj[i],"name",str)
        output.add(obj[i],"block",str)
        output.add(obj[i],"index",int)
        output.add(obj[i],"alt_name",str)
        output.add(obj[i],"bcs",str)
        output.add(obj[i],"shape",str)
        output.add(obj[i],"is_output",bool)
        output.add(obj[i],"is_real",bool)
        output.add(obj[i],"defvalue",float)
        output_full.append(output)
    return output_full


# def decode_SARAHOptions(obj):
#   output = sarah_class("Options")
#   output.add(obj,"package",str)
#   output.add(obj,"model",str)
#   return output


def docode_SARAHOutputs(obj):
  output = sarah_class("Options")
  output.add(obj,"get_ch",str)
  output.add(obj,"get_mg",str)
  output.add(obj,"get_sph",str)
  output.add(obj,"get_vev",str)
  # output.add(obj,"set_ch",str)
  # output.add(obj,"set_mg",str)
  # output.add(obj,"set_sph",str)
  # output.add(obj,"set_vev",str)
  return output


# def decode_SARAHError(obj):
#   output = sarah_class("Options")
#   output.add(obj,"is_error",bool)
#   output.add(obj,"what",str)
#   return output

def decode_SARAHMapStrBool(obj):
  return {m.key():m.data() for m in obj}

def decode_SARAHMapStrStr(obj):
  return {m.key():m.data() for m in obj}
