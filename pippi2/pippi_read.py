#############################################################
# pippi: parse it, plot it
# ------------------------
# Module for reading data and options for pippi.
#
# Author: Pat Scott (patscott@physics.mcgill.ca)
# Originally developed: March 2012
# Modified: Christoph Weniger, 2015
#           Pat Scott, 2016
#############################################################

import datetime
import sys
from pippi_utils import *
if sys.path[0] != '': sys.path.insert(0, '')

def getIniData(filename,keys,savekeys=None,savedir=None):
  #Read initialisation data from pip file filename into keys

  if (len(filename) != 1):
    usage()
    return
  filename = filename[0]

  #Try to open pip file
  pipfile = safe_open(filename)
  #Get the contents
  original_parse_options = pipfile.readlines()
  #Shut it
  pipfile.close
  #Remove all comments
  for i,line in enumerate(original_parse_options): original_parse_options[i] = re.sub(r';.*$', '', line)
  #Stitch together multi-line lines
  parse_options = list([])
  oldline = ""
  for i,line in enumerate(original_parse_options):
    newline = line.rstrip()
    oldline += newline
    if (oldline != "" and oldline[-1] == "\\"):
      oldline = oldline[:-1]
    else:
      parse_options.append(oldline+"\n")
      oldline = ""

  #Find relevant bits in pipfile
  for i,key in enumerate(keys):
    lines = filter(key.seek,parse_options)
    if (len(lines) == 0):
      sys.exit('Error: field '+key.pipFileKey+' required for requested operation not found in '+filename+'.  Quitting...\n')
    if (len(lines) > 1):
      sys.exit('Error: field '+key.pipFileKey+' required for requested operation duplicated in '+filename+'.  Quitting...\n')
    # Convert key entries to correct internal data format
    key.convert(re.sub(r'.*=', '', lines[0]))

  # Save requested keys
  if savekeys is not None:

    # Make sure saving is actually possible
    if not mainChain in keys:
      print '\n  Warning: saving of keys not possible because mainChain is undefined.\n  Skipping save...'
      return

    # Open the file keys will be saved to
    if savedir is None or not savedir in keys or savedir.value is None:
      outfile = smart_open(re.sub(r"\..?.?.?$", '', mainChain.value)+'_savedkeys.pip','w')
    else:
      # Make sure savedir exists, make it if not
      safe_dir(savedir.value)
      outfile = smart_open(savedir.value+'/'+re.sub(r'.*/|\..?.?.?$', '', mainChain.value)+'_savedkeys.pip','w')
    outfile.write(';This file of saved keys created by pippi '\
                +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')

    # Parse the pip file again and save the requested keys
    for key in savekeys:
      lines = filter(key.seek,parse_options)
      # Save keys verbatim to the savedkeys pip file
      if savekeys is not None and key in savekeys: outfile.write(lines[0])

  # Clean up
  if savekeys is not None: outfile.close

def getChainData(filename, cut_all_invalid=None, requested_cols=None, assignments=None, labels=None, silent=False,
 probe_only=False, data_ranges=None, log_plots=None, obs_plots=None, rescalings=None, preamble=None):
  # Open a chain file and read it into memory

  column_names=None
  all_best_fit_data = []

  # Regular ASCII chain
  if filename.split(":")[0][-5:] != '.hdf5':

    # Make sure the user is not trying to probe a non-hdf5 file.
    if probe_only:
      sys.exit('ERROR: you cannot use pippi probe with ASCII files. (Why would you need to?)')

    #Try to open chain file
    chainfile = safe_open(filename)

    #Read the first line, and check that the inline assignments are sensible.
    i = 0
    just_comments = True
    while just_comments:
      line = chainfile.readline()
      lines = line.split()
      if line != [] and line[0] not in ['#',';','!',]: just_comments = False
    ncols = len(lines)
    n_extra_cols = 0
    if assignments is not None and assignments.value is not None:
      for index in assignments.value:
        if castable_to_int(index):
          if ncols+n_extra_cols not in assignments.value:
            print 'ERROR: When working with ASCII chains and trying to assign function'
            print 'results to datastreams, all functional datastreams must be assigned indices'
            print 'in continuous ascending order starting from the index of the last'
            print 'column in the ASCII file. In this case, that means you must start with'
            print str(ncols)+' and go up by one for each subsequent functional stream.'
            sys.exit("")
          if not is_functional_assignment(assignments.value[ncols+n_extra_cols]):
            sys.exit('ERROR: When working with ASCII chains, all entries in assign_to_pippi_datastream\nmust be functional assignments.')
          n_extra_cols += 1
    chainfile.seek(0)

    #Read each line into a new list, and save that within a bigger list
    data=[]
    for line in chainfile:
      lines = line.split()
      if lines != [] and line[0] not in ['#',';','!',]:
        if not any(x == "none" for x in lines): # For now we just exclude all points with any invalid entries.
          data.append(lines + ['0' for x in range(n_extra_cols)])

    #Close the chainfile and indicate success
    chainfile.close
    if not silent:
      print
      print '  Read chain '+filename
      print

    #Turn the whole lot into a numpy array of doubles
    data = np.array(data, dtype=np.float64)
    # Find the lookup keys
    lookup_key = np.arange(data.shape[1])

    # Compute the derived quantities
    if assignments is not None:
      for i in [ncols + x for x in range(n_extra_cols)]:
        expression = parse_functional_assignment(assignments.value[i], 'data[:,$]')
        try:
          # Read in any python preamble specified in the pip file.
          if preamble is not None: exec(preamble)
          exec('data[:,'+str(i)+'] = '+expression)
        except KeyError, e:
          print 'ERROR: Datastream '+str(e)+', which you have tried to define a function of'
          print 'in assign_to_pippi_datastream, is not itself defined as a datastream.'
          print 'This usually happens because it does not exist in the chain you are trying'
          print 'to parse. Please fix assignment "'+assignments.value[i]+'".'
          sys.exit("")
        except:
          print 'ERROR: something in one of the functions of datastreams you defined in '
          print 'assign_to_pippi_datastream is buggy.  Please fix the expression: '
          print assignments.value[i]
          print 'Now raising the original error, so you can see the stacktrace for yourself...'
          raise

    # Filter out points inside the requested data ranges
    cut = None
    if data_ranges is not None and data_ranges.value:
      for key, value in data_ranges.value.iteritems():
        lowercut = value[0]
        uppercut = value[1]
        if log_plots.value is not None and key in log_plots.value:
          lowercut = pow(10.0,lowercut)
          uppercut = pow(10.0,uppercut)
        if rescalings.value is not None and key in rescalings.value:
          lowercut *= rescalings.value[key]
          uppercut *= rescalings.value[key]
        if cut is None:
          cut = np.logical_and(data[:,key] >= lowercut, data[:,key] <= uppercut)
        else:
          cut = np.logical_and(cut, np.logical_and(data[:,key] >= lowercut, data[:,key] <= uppercut))
      # Print the details of the cuts
      rescaling = 1.0
      print "  Total samples: ", data.shape[0]
      if cut is not None:
        data = data[cut,:]
        sumcut = sum(cut)
        print "  Total samples within requested data ranges: ", sumcut
        if sumcut <= 0.0: sys.exit('Requested data cuts leave no remaining samples!')
        rescaling = 1.0*sumcut/len(cut)
      print "  Fraction of samples within requested data ranges: %.4f"%(rescaling)

  # HDF5 file
  else:
    filename, groupname = filename.split(":")
    if not silent:
      print
      print "  Reading HDF5 chain file"
      print "    filename:", filename
      print "    group:", groupname
      print

    # Parse group entry
    groups = groupname.split('/')
    if groups[0] != "" or groupname == "":
      raise ValueError("Group identifier should start with '/'")
    else:
      groups = groups[1:]

    # Open HDF5 file
    try:
      import h5py
      f = h5py.File(filename,'r')
    except IOError:
      sys.exit("ERROR while reading hdf5 file.  Check filename and file format.")

    # Get relevant group entries and column names
    entries = f
    if groups[0] != "":
      for key in groups:
        try:
          entries = entries[key]
        except KeyError:
          sys.exit("ERROR: requested group \""+key+"\" does not exist in hdf5 file.")
    column_names = filter(lambda x: x[-8:] != "_isvalid", list(entries))

    # Reorganize MPIrank, pointID and other requested entries for convenience.
    indices = []
    all_indices = []
    functional_assignment_indices = []
    index_count = 0
    primary_column_names = ['MPIrank', 'pointID']
    sorted_column_names = primary_column_names + [x for x in column_names if x not in primary_column_names]
    for column_name in sorted_column_names:
      if assignments.value is not None:
        while index_count in assignments.value:
          if is_functional_assignment(assignments.value[index_count]):
            functional_assignment_indices.append(index_count)
            all_indices.append(index_count)
          else:
            try_append(indices, column_names, assignments.value[index_count])
            try_append(all_indices, column_names, assignments.value[index_count])
          index_count += 1
      if assignments.value is None or column_name not in assignments.value:
        try_append(indices, column_names, column_name)
        try_append(all_indices, column_names, column_name)
        index_count += 1
    # Fill in any remaining entries up to the largest in the hdf5 file
    if assignments.value is not None:
      while index_count in assignments.value:
        if is_functional_assignment(assignments.value[index_count]):
          functional_assignment_indices.append(index_count)
          all_indices.append(index_count)
        else:
          try_append(indices, column_names, assignments.value[index_count])
          try_append(all_indices, column_names, assignments.value[index_count])
        index_count += 1
    # Rearrange the column names into the order we want them in.
    column_names = np.array(column_names)[all_indices]
    # Pick up all the datastreams with indices larger than the largest index in the hdf5 file
    if assignments.value is not None:
      for index, assignment in assignments.value.iteritems():
        if castable_to_int(index) and index >= index_count:
          if is_functional_assignment(assignment):
            functional_assignment_indices.append(index)
            all_indices.append(index)
          else:
            try_append(indices, column_names, assignment)
            try_append(all_indices, column_names, assignment)
    # Pad the column names with empties past the end of the hdf5 indices
    hdf5_length = len(column_names)
    column_names = np.append(column_names, np.array(['' for x in range(np.max(all_indices)-hdf5_length+1)]))
    # Fill in the functionals
    for i, column_name in enumerate(column_names):
      if i in functional_assignment_indices: column_names[i] = assignments.value[i]

    # Print probed contents and split
    if probe_only:
      for i, column_name in enumerate(column_names):
        if column_name != '': print "   ", i, ":", column_name
      print
      quit()

    # Identify any likelihood or multiplicity indicated by the labels.
    if labels:
      likelihood_index = [value for key, value in labels.value.iteritems() if key in permittedLikes]
      if not likelihood_index: likelihood_index = [key for key, value in labels.value.iteritems() if value in permittedLikes]
      if likelihood_index:
        likelihood_index = likelihood_index[0]
        if likelihood_index not in requested_cols: requested_cols.add(likelihood_index)
      multiplicity_index = [value for key, value in labels.value.iteritems() if key in permittedMults]
      if not multiplicity_index: multiplicity_index = [key for key, value in labels.value.iteritems() if value in permittedMults]
      if multiplicity_index:
        multiplicity_index = multiplicity_index[0]
        if multiplicity_index not in requested_cols: requested_cols.add(multiplicity_index)

    # Get data, reading only those columns requested in the pip file.
    data = []
    data_isvalid = []
    index_count = 0
    lookup_key = {}
    for index in requested_cols:
      if index in functional_assignment_indices:
        # If this is a functional assignment, just hold this space for now by appending a placeholder string.
        data.append('functional')
        data_isvalid.append('functional')
      else:
        if index >= hdf5_length:
          sys.exit('ERROR: Requested column number '+str(index)+' does not exist in chain '+mainChain.value+'.\nQuitting...\n')
        try:
          data.append(np.array(entries[column_names[index]], dtype=np.float64))
        except AttributeError:
          sys.exit("ERROR: \""+column_name+"\" in group \""+groupname+"\" is not convertible to a float.\nProbably you gave the wrong group in your pip file.")
        data_isvalid.append(np.array(entries[column_names[index]+"_isvalid"], dtype=np.float64))
      lookup_key[index] = index_count
      index_count += 1
    non_functional_cols = [i for i, elem in enumerate(data) if data[i] is not 'functional']
    if not non_functional_cols:
      print "ERROR: At least one non-function assignment is needed in"
      print "assign_to_pippi_datastream, or a multiplicity or likelihood"
      print "identification in quantity_labels."
      sys.exit("")
    # Print the raw number of samples in the hdf5 file
    total_samples = data[non_functional_cols[0]].size
    print "  Total samples: ", total_samples
    # Fill in the functional columns with zeros.  Note that this uses more memory than doing it after validity
    # cuts, but should actually be faster (I think; haven't actually tested that). It makes the code simpler too.
    for i, elem in enumerate(data):
      if elem is 'functional':
        data[i] = np.zeros(total_samples, dtype=np.float64)
      else:
        # Do some pruning to deal with cases where the some datasets have extra entries (although this arguably indicates a bug in the sampler)
        data[i] = elem[:total_samples]
    for i, elem in enumerate(data_isvalid):
      if elem is 'functional':
        data_isvalid[i] = np.ones(total_samples, dtype=np.float64)
      else:
        # Do some pruning to deal with cases where the some datasets have extra entries (although this arguably indicates a bug in the sampler)
        data_isvalid[i] = elem[:total_samples]
    # Make everything a neat numpy array
    data = np.array(data, dtype=np.float64)
    data_isvalid = np.array(data_isvalid, dtype=np.float64)

    # Save likelihood column before filtering on validity or data ranges
    if likelihood_index is not None: old_likelihood_column = data[lookup_key[likelihood_index],:]

    # Filter out invalid points if called with labels provided
    cut = None
    if labels:
      if cut_all_invalid:
        # Based on all entries.
        cut = (data_isvalid.prod(axis=0) == 1)
      else:
        # Based on the likelihood entry only
        if likelihood_index is not None:
          cut = (data_isvalid[lookup_key[likelihood_index]] == 1)
    print "  Total valid samples: ", sum(cut)

    # Fill in the derived quantities specified via functional assignments
    for i in sorted(functional_assignment_indices, key=int):
      expression = parse_functional_assignment(assignments.value[i], 'data[lookup_key[$]]')
      try:
        # Read in any python preamble specified in the pip file.
        if preamble is not None: exec(preamble)
        exec('data[lookup_key['+str(i)+']] = '+expression)
      except KeyError, e:
        print 'ERROR: Datastream '+str(e)+', which you have tried to define a function of'
        print 'in assign_to_pippi_datastream, is not itself defined as a datastream.'
        print 'This usually happens because you have not requested it for plotting in'
        print 'either oneD_plot_quantities or twoD_plot_quantities, so it has not been'
        print 'extracted from the hdf5 file.  Please add it to one of these lists if you'
        print 'really want to do the calculation "'+assignments.value[i]+'"'
        sys.exit("")
      except:
        print 'ERROR: something in one of the functions of datastreams you defined in '
        print 'assign_to_pippi_datastream is buggy.  Please fix the expression: '
        print assignments.value[i]
        print 'Now raising the original error, so you can see the stacktrace for yourself...'
        raise

    # Filter out points inside the requested data ranges
    if data_ranges.value:
      for key, value in data_ranges.value.iteritems():
        if key not in requested_cols:
          print 'ERROR: '+str(key)+' mentioned in data_ranges does not'
          print 'appear in requested_cols!  Please report this as a pippi bug.'
        lowercut = value[0]
        uppercut = value[1]
        if log_plots.value is not None and key in log_plots.value:
          lowercut = pow(10.0,lowercut)
          uppercut = pow(10.0,uppercut)
        if rescalings.value is not None and key in rescalings.value:
          lowercut *= rescalings.value[key]
          uppercut *= rescalings.value[key]
        if cut is None:
          cut = np.logical_and(data[lookup_key[key],:] >= lowercut, data[lookup_key[key],:] <= uppercut)
        else:
          cut = np.logical_and(cut, np.logical_and(data[lookup_key[key],:] >= lowercut, data[lookup_key[key],:] <= uppercut))

    # Print the details of the cuts
    rescaling = 1.0
    if cut is not None:
      data = data[:,cut]
      data_isvalid = data_isvalid[:,cut]
      sumcut = sum(cut)
      print "  Total valid samples within requested data ranges: ", sumcut
      if sumcut == 0: sys.exit('  You cut out all your samples!  Pippi can\'t do much more from here.\n')
      rescaling = 1.0*sumcut/len(cut)
      # Find the full details of the best-fit point
      if likelihood_index is not None:
        if likelihood_index in labels.value:
          findMin = labels.value[likelihood_index] in permittedLikes_samesign
        else:
          findMin = [value for key, value in labels.value.iteritems() if key in permittedLikes_samesign]
        if findMin:
          bestfit_any_index = np.ma.array(old_likelihood_column, mask=~cut).argmin()
          bestfit_index = data[lookup_key[likelihood_index]].argmin()
        else:
          bestfit_any_index = np.ma.array(old_likelihood_column, mask=~cut).argmax()
          bestfit_index = data[lookup_key[likelihood_index]].argmax()
        for i, column_name in enumerate(column_names):
          if i in functional_assignment_indices:
            all_best_fit_data.append(str(data[lookup_key[i]][bestfit_index]))
          else:
            if column_name != '': all_best_fit_data.append(str(entries[column_name][bestfit_any_index]))
    print "  Fraction of samples deemed valid and within requested data ranges: %.4f"%(rescaling)

    # Print list of contents for convenience
    if not silent:
      for key, value in sorted(lookup_key.iteritems()):
        print "   ",key, ":", column_names[key]
        print "        mean: %.2e  min: %.2e  max %.2e"%(np.mean(data[value]), np.min(data[value]), np.max(data[value]))
        print "        Fraction of valid points where this is invalid: %.4f"%(1.0-data_isvalid[value].mean())
      print

    # Flip 'em.
    data = np.array(data.T, dtype=np.float64)

  return (data, column_names, lookup_key, all_best_fit_data)
