
#############################################################
# pippi: parse it, plot it
# ------------------------
# Merge program for pippi.
#
# Author: Pat Scott (patscott@physics.mcgill.ca)
# Originally developed: March 2012
#############################################################

from pippi_utils import *

def merge(filenames):
  #Functions to merge multiple chains.  If these are ascii files,
  #spit them out to stdout (for e.g. piping into a file, or some
  #other program).  Basically just 'cat' with a little bit of
  #error checking.  If these are hdf5 files, then cat the matching
  #records of the files and spit them out into the last argument.

  if (len(filenames) == 0):
    usage()
    return

  files = {}
  dataset_collection = []
  dataset_set_collection = []

  # Work out whether we are doing an hdf5 merge or an ascii merge
  try:
    import h5py
    f = h5py.File(filenames[0],'r')
    h5merge = True
    print
    print "Files identified as hdf5.  Interpreting final argument as output filename."
    print
    print "Concatenating common datasets and outputting to {0}...".format(filenames[-1])
    print
  except:
    h5merge = False

  if any(x.endswith(".hdf5") for x in filenames) and not h5merge:
    sys.exit("ERROR: Python package h5py not detected, but judging from the filenames you're trying to merge hdf5 files.")


  if h5merge:
    # We are doing an hdf5 merge.

    # Try to open the output file (the last filename given)
    try:
      fout = h5py.File(filenames[-1],'w-')
    except:
      print "Could not create output file {0}!".format(filenames[-1])
      print "Please make sure it does not exist already."
      print
      return

    print "  Determining common datasets..."
    for fname in filenames[0:-1]:
      print "    Opening: {0}".format(fname)
      try:
        f = h5py.File(fname,'r')
      except:
        print "Could not open file {0}!".format(fname)
        print
        return
      files[fname] = f
      datasets = {}
      # Identify the datasets in the file
      get_datasets(f,datasets)
      dataset_collection.append(datasets)
      dataset_set_collection.append(set(datasets))

    #Find all common datasets, ensuring they have the same types and shapes
    common_datasets = set()
    for x in set.intersection(*dataset_set_collection):
      datatype = dataset_collection[0][x].dtype
      datashape = dataset_collection[0][x].shape
      if all(f[x].dtype == datatype and f[x].shape[1:] == datashape[1:] for f in dataset_collection):
        common_datasets.add(x)
    print
    print "  Common datasets: "
    for x in common_datasets: print "    {0}".format(x)
    print

    #Find the length of each dataset and create it (empty) in the new file
    print "  Creating empty datasets of required lengths in {0}...".format(filenames[-1])
    out_dsets = {}
    for ds in common_datasets:
      length = 0
      for f in dataset_collection: length += f[ds].len()
      datatype = dataset_collection[0][ds].dtype
      datashape = (length,) + dataset_collection[0][ds].shape[1:]
      out_dsets[ds] = fout.create_dataset(ds, datashape, dtype=datatype)
    print

    #Copy the data over to the new file
    print "  Adding data to empty datasets in {0}...".format(filenames[-1])
    for ds in common_datasets:
      print "    Populating {0}".format(ds)
      index_low = 0
      for f in dataset_collection:
        index_high = index_low + f[ds].len()
        out_dsets[ds][index_low:index_high,...] = f[ds][...]
        index_low = index_high

    print
    print "Done."
    print


  else:    # We are doing an ASCII merge

    firstLine = True

    for filename in filenames:

      #Try to open input file
      infile = safe_open(filename)

      #Read the first line
      line = infile.readline()

      #Skip comments at the beginning of the file
      while (line[0] == '#'):
        line = infile.readline()

      #Work out the number of columns in the first valid line
      columns = len(line.split())

      while (columns != 0):
        try:
          if (firstLine):
            #Save the number of columns if this is the first line of the first chain
            columnsPredicted = columns
            firstLine = False
          elif (columns != columnsPredicted):
            #Crash if a later chain or line has a different number of columns to the first one
            sys.exit('Error: chains do not match (number of columns differ).  Quitting...')
          #Output the current line to stdout and get the next one
          print line.rstrip('\n')
          #Read the next line
          line = infile.readline()
          #Work out the number of columns in the next line
          columns = len(line.split())
        except IOError:
          break

      #Shut the chain file and move on to the next
      infile.close

def get_datasets(g,datasets):
  import h5py
  for name, item in g.iteritems():
    if isinstance(item,h5py.Group): get_datasets(item,datasets)
    if isinstance(item,h5py.Dataset): datasets[item.name] = item
