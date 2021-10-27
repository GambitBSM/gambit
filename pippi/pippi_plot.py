
#############################################################
# pippi: parse it, plot it
# ------------------------
# Plotting program for pippi.
#
# Author: Pat Scott (patscott@physics.mcgill.ca)
# Originally developed: March 2012
#############################################################

import subprocess
from pippi_utils import *
from pippi_read import *

#Define pip file entries required from parsing
parsedir = dataObject('parse_dir',safe_string)
labels = dataObject('quantity_labels',string_dictionary)

#Define pip file entries required from scripting
scriptdir = dataObject('script_dir',safe_string)

#Define plot-specific pip file entries
outdir = dataObject('plot_dir',safe_string)
prepend = dataObject('file_prefix',safe_string)
append = dataObject('file_suffix',safe_string)
keys = keys+[parsedir,scriptdir,outdir,prepend,append]

def plot(filename):

  print

  # Parse pip file
  getIniData(filename,keys)

  # Make sure outdir exists, make it if not
  if outdir.value is not None: safe_dir(outdir.value)

  # Work out where the scripts are located
  if scriptdir.value is None:
    # No script_dir; default to searching parse_dir
    if parsedir.value is None:
      # No parse_dir either; default to searching the directory containing chain(s)
      baseFiledir = re.sub(r'/.*?$', '/', mainChain.value)
    else:
      # Search in parse_dir
      baseFiledir = parsedir.value+'/'
  else:
    # Search in script_dir
    baseFiledir = scriptdir.value+'/'

  # Extract main chain filename, without extension
  baseFilename = re.sub(r'.*/|\..?.?.?$', '', mainChain.value)

  # Retrieve labels saved in earlier parsing run
  if parsedir.value:
    savedkeys = parsedir.value + '/' + baseFilename+'_savedkeys.pip'
  else:
    savedkeys = baseFiledir + baseFilename+'_savedkeys.pip'
  getIniData([savedkeys],[labels])

  #Work out whether to do posteriors check that flags match up for posterior pdf
  if doPosterior.value and not any(x in labels.value for x in permittedMults):
    print '  Warning: do_posterior_pdf = T but no multiplicity in chain labels.\n  Skipping posterior PDF...'
    doPosterior.value = False

  # Set defaults for prepend and append string
  outdirectory = '.' if outdir.value is None else outdir.value
  prestring = '' if prepend.value is None else prepend.value
  appstring = '' if append.value is None else append.value

  # Run 1D plotting scripts
  if oneDplots.value is not None:
    # Work through 1D plotting scripts
    for plot in oneDplots.value:
      print '    Running plotting scripts for 1D plots of quantity ',plot
      # Set up filenames
      currentBase = baseFilename+'_'+str(plot)
      # Make profile likelihood plots
      if doProfile.value:
        subprocess.check_call('cd '+baseFiledir+'; ./'+currentBase+'_like1D.bsh', shell=True)
        subprocess.check_call('mv '+baseFiledir+currentBase+'_like1D.pdf '+
         outdirectory+'/'+prestring+currentBase+'_like1D'+appstring+'.pdf', shell=True)
      # Make posterior pdf plots
      if doPosterior.value:
        subprocess.check_call('cd '+baseFiledir+'; ./'+currentBase+'_post1D.bsh', shell=True)
        subprocess.check_call('mv '+baseFiledir+currentBase+'_post1D.pdf '+
         outdirectory+'/'+prestring+currentBase+'_post1D'+appstring+'.pdf', shell=True)
      # Make profile-posterior comparison plots
      if doProfile.value and doPosterior.value:
        subprocess.check_call('cd '+baseFiledir+'; ./'+currentBase+'_combo1D.bsh', shell=True)
        subprocess.check_call('mv '+baseFiledir+currentBase+'_combo1D.pdf '+
         outdirectory+'/'+prestring+currentBase+'_combo1D'+appstring+'.pdf', shell=True)

  # Run 2D plotting scripts
  if twoDplots.value is not None:
    # Loop over requested plots
    for plot in twoDplots.value:
      print '    Running plotting scripts for 2D plots of quantity ',plot
      # Set up filenames
      currentBase = baseFilename+'_'+'_'.join([str(x) for x in plot])
      # Make profile likelihood plots
      if doProfile.value:
        subprocess.check_call('cd '+baseFiledir+'; ./'+currentBase+'_like2D.bsh', shell=True)
        subprocess.check_call('mv '+baseFiledir+currentBase+'_like2D.pdf '+
         outdirectory+'/'+prestring+currentBase+'_like2D'+appstring+'.pdf', shell=True)
      # Make posterior pdf plots
      if doPosterior.value:
        subprocess.check_call('cd '+baseFiledir+'; ./'+currentBase+'_post2D.bsh', shell=True)
        subprocess.check_call('mv '+baseFiledir+currentBase+'_post2D.pdf '+
         outdirectory+'/'+prestring+currentBase+'_post2D'+appstring+'.pdf', shell=True)
      
      #if doObservable.value:
      if obsPlots.value is not None:
          for column in obsPlots.value:
            subprocess.call('cd '+baseFiledir+'; ./'+currentBase+'_obs2D_'+str(column)+'.bsh', shell=True)
            subprocess.call('mv '+baseFiledir+currentBase+'_obs2D_'+str(column)+'.pdf '+
            outdirectory+'/'+prestring+currentBase+'_obs2D_' + str(column) + appstring +'.pdf', shell=True)
      # Make profile-posterior comparison plots
      if doProfile.value and doPosterior.value:
        subprocess.check_call('cd '+baseFiledir+'; ./'+currentBase+'_combo2D.bsh', shell=True)
        subprocess.check_call('mv '+baseFiledir+currentBase+'_combo2D.pdf '+
         outdirectory+'/'+prestring+currentBase+'_combo2D'+appstring+'.pdf', shell=True)

