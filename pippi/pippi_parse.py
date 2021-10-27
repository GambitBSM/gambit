
#############################################################
# pippi: parse it, plot it
# ------------------------
# Parsing program for pippi.
#
# Author: Pat Scott (patscott@physics.mcgill.ca)
# Originally developed: March 2012
#############################################################

import subprocess
from pippi_utils import *
from pippi_read import *
from scipy import version as scipyCurrent
from scipy.special import gammaincinv as deltaLnLike
from scipy.interpolate import InterpolatedUnivariateSpline as oneDspline
from scipy.interpolate import RectBivariateSpline as twoDbilinear

from distutils.version import StrictVersion
if StrictVersion(scipyCurrent.version) >= StrictVersion("0.9.0"):
  from scipy.interpolate import CloughTocher2DInterpolator as twoDspline

# Define parse-specific pip file entries
parsedir = dataObject('parse_dir',safe_string)
cutOnAnyInvalid = dataObject('cut_on_invalid_observables',boolean)
labelFile = dataObject('labels_from_file',string)
col_assignments = dataObject('assign_to_pippi_datastream',string_dictionary)
labels = dataObject('quantity_labels',string_dictionary)
logPlots = dataObject('use_log_scale',int_list)

rescalings = dataObject('quantity_rescalings',float_dictionary)
defaultBins = dataObject('default_bins',integer)
specificBins = dataObject('number_of_bins',int_dictionary)
resolution = dataObject('interpolated_resolution',integer)
intMethod = dataObject('interpolation_method',string)
chainType = dataObject('chain_type',internal)
doEvidence = dataObject('compute_evidence',boolean)
data_ranges = dataObject('data_ranges',floatuple_dictionary)
preamble = dataObject('preamble',string)
alt_best_fit = dataObject('bf_lnlike_for_profile_like',float)
keys = keys+[parsedir,labelFile,cutOnAnyInvalid,defaultBins,specificBins,intMethod,chainType,resolution,doEvidence,labels,col_assignments,logPlots,rescalings,data_ranges,preamble,alt_best_fit]

# Initialise variables
doPosteriorMean = True
firstLikeKey = None
ObsFloor = 0.0

def parse(filename):
  #input:   filename = the name of the pip file
  global doPosteriorMean

  # Parse pip file
  getIniData(filename,keys,savekeys=[labels],savedir=parsedir)

  # Make a local copy of data_ranges
  dataRanges = {} if not data_ranges.value else dict(data_ranges.value)

  # Work out where the parse output is to be located
  if parsedir.value is None:
    # No parse_dir; default to the directory containing chain(s)
    baseFiledir = re.sub(r'/.*?$', '/', mainChain.value)
  else:
    # Save in parse_dir
    baseFiledir = parsedir.value+'/'

  # Check that the requested interpolation method is available
  if twoDplots.value is not None:
    if intMethod.value is None: intMethod.value = allowedIntMethods[0]
    if intMethod.value not in allowedIntMethods: sys.exit('Error: unrecognised interpolation_method.')
    if intMethod.value == 'spline' and StrictVersion(scipyCurrent.version) < StrictVersion("0.9.0"):
      sys.exit('Sorry, Clough-Tocher 2D interpolation is not supported in SciPy \n'+
               'v0.8 or lower; please upgrade your installation to use this option.')

  #Read in label data if it is not in the pip file
  if labelFile.value is not None: getIniData(labelFile.value,[labels])

  #Check that flags match up for profile likelihood
  if all(x not in labels.value for x in permittedLikes) and doProfile.value:
    print '  Warning: no likelihood in chain labels.\n  Skipping profile likelihood...'
    doProfile.value = False

  #Work out whether to do posterior mean and check that flags match up for posterior pdf
  doPosteriorMean = any(x in labels.value for x in permittedMults)
  if doPosterior.value and not doPosteriorMean:
    print '  Warning: do_posterior_pdf = T but no multiplicity in chain labels.\n  Skipping posterior PDF...'
    doPosterior.value = False

  #Check that flags match up for evidence
  if doEvidence.value:
    if chainType.value is mcmc:
      if all(x not in labels.value for x in permittedLikes) or \
         all(x not in labels.value for x in permittedMults) or \
         all(x not in labels.value for x in permittedPriors):
        print '  The evidence cannot be calculated without multiplicity, prior and likelihood.\n  Skipping evidence...'
        doEvidence.value = False
    else:
      print '  The evidence can only be calculated from an MCMC chain.\n  Skipping evidence...'
      doEvidence.value = False

  #Check that flags and match up for quantities selected for plotting
  oneDlist = [] if oneDplots.value is None else oneDplots.value
  twoDlist = [] if twoDplots.value is None else twoDplots.value
  obslist = [] if obsPlots.value is None else obsPlots.value
  datarangelist = [] if data_ranges.value is None else data_ranges.value.keys()
  partialSetOfRequestedColumns = set(oneDlist + [y for x in twoDlist for y in x])
  setOfRequestedColumns = set.union(partialSetOfRequestedColumns, set(datarangelist),obslist)

  # Check that labels for all the requested columns are present.
  for plot in partialSetOfRequestedColumns:
    try:
      label = labels.value[plot]
    except (KeyError, TypeError):
      sys.exit('Error: please provide a label for column '+str(plot)+' if you want to plot it.\nQuitting...\n')

  # Work out what binning to use in each dimension
  nBins = {}
  for x in setOfRequestedColumns:
    nBins[x] = defaultBins.value if (not specificBins.value or x not in specificBins.value) else specificBins.value[x]

  # Open main chain and read in contents
  (mainArray, hdf5_names, lookupKey, all_best_fit_data) = getChainData(mainChain.value, cut_all_invalid=cutOnAnyInvalid.value,
   requested_cols=setOfRequestedColumns, labels=labels, assignments=col_assignments, data_ranges=data_ranges, log_plots=logPlots,obs_plots=obsPlots,
   rescalings=rescalings, preamble=preamble.value)

  # Parse main chain
  outputBaseFilename = baseFiledir+re.sub(r'.*/|\..?.?.?$', '', mainChain.value)
  doParse(mainArray,lookupKey,outputBaseFilename,setOfRequestedColumns,hdf5_names,dataRanges,all_best_fit_data,nBins,alt_best_fit)

  # If a comparison chain is specified, parse it too
  if secChain.value is not None:
    # Open secondary chain and read in contents
    outputBaseFilename = baseFiledir+re.sub(r'.*/|\..?.?.?$', '', secChain.value)+'_comparison'
    (mainArray, hdf5_names, lookupKey, all_best_fit_data) = getChainData(secChain.value, cut_all_invalid=cutOnAnyInvalid.value,
     requested_cols=setOfRequestedColumns, labels=labels, assignments=col_assignments, data_ranges=data_ranges, log_plots=logPlots,obs_plots=obsPlots,
     rescalings=rescalings, preamble=preamble.value)
    # Switch depending on whether the comparison file is hdf5 or ascii
    min_array_length = max(setOfRequestedColumns) if hdf5_names is None else len(setOfRequestedColumns)
    if mainArray.shape[1] >= min_array_length:
      # Clear savedkeys file for this chain
      subprocess.call('rm -rf '+outputBaseFilename+'_savedkeys.pip', shell=True)
      # Parse comparison chain
      doParse(mainArray,lookupKey,outputBaseFilename,setOfRequestedColumns,hdf5_names,dataRanges,all_best_fit_data,nBins,alt_best_fit)
    else:
      print '    Chain '+secChain.value+' has less columns than required to do all requested plots.'
      print '    Skipping parsing of this chain...'


def doParse(dataArray,lk,outputBaseFilename,setOfRequestedColumns,column_names,dataRanges,all_best_fit_data,nBins,alt_best_fit):
  #Perform all numerical operations required for chain parsing

  # Determine the minimum log-likelihood requested as an isocontour in 2D plots
  min_contour = None
  if doProfile.value and twoDplots.value and contours2D.value:
    min_contour = deltaLnLike(1.0,0.01*max(contours2D.value))

  # Standardise likelihood, prior and multiplicity labels, and rescale likelihood and columns if necessary
  standardise(dataArray,lk)
  # Sort array if required
  doSort(dataArray,lk)
  # Find best-fit point
  [bestFit,worstFit,bestFitIndex] = getBestFit(dataArray,lk,outputBaseFilename,column_names,all_best_fit_data,alt_best_fit,min_contour)
  # Find posterior mean
  [totalMult, posteriorMean] = getPosteriorMean(dataArray,lk,outputBaseFilename)
  # Get evidence for mcmc
  [lnZMain,lnZMainError] = getEvidence(dataArray,lk,bestFit,totalMult,outputBaseFilename)
  # Save data minima and maxima
  saveExtrema(dataArray,lk,outputBaseFilename,setOfRequestedColumns,dataRanges)
  # Save lookup keys for parameters
  saveLookupKeys(lk,outputBaseFilename)
  # Do binning for 1D plots
  oneDsampler(dataArray,lk,bestFit,worstFit,outputBaseFilename,dataRanges,nBins)
  # Do binning for 2D plots
  twoDsampler(dataArray,lk,bestFit,worstFit,outputBaseFilename,dataRanges,nBins)


def standardise(dataArray,lk):
  global firstLikeKey
  # Standardise likelihood, prior and multiplicity labels, rescale likelihood if necessary,
  for key, entry in labels.value.copy().iteritems():
    if any(key == mult for mult in permittedMults):
      labels.value[refMult] = labels.value[key]
      if key != refMult: del labels.value[key]
    if any(key == prior for prior in permittedPriors):
      labels.value[refPrior] = labels.value[key]
      if key != refPrior: del labels.value[key]
    #if any(key == obs for obs in permittedObs):
    #  labels.value[refObs] = labels.value[key]
    #  if key != refObs: del labels.value[key]
    if any(key == like for like in permittedLikes):
      if firstLikeKey is None: firstLikeKey = key
      dataArray[:,lk[labels.value[key]]] = mapToRefLike(firstLikeKey,dataArray[:,lk[labels.value[key]]])
      labels.value[refLike] = labels.value[key]
      if key != refLike: del labels.value[key]
    if any(entry == mult for mult in permittedMults): labels.value[key] = refMult
    if any(entry == prior for prior in permittedPriors): labels.value[key] = refPrior
    if any(entry == like for like in permittedLikes): labels.value[key] = refLike
    #if any(entry == obs for obs in permittedObs): labels.value[key] = refObs
  # Rescale columns if requested
  if rescalings.value is not None:
    for key, entry in rescalings.value.iteritems(): dataArray[:,lk[key]] *= entry
  # Convert columns to log if requested
  if logPlots.value is not None:
    for column in logPlots.value:
      if column in lk:
        if any(dataArray[:,lk[column]] <= 0.0):
          print "Error: column {0} requested for log plotting has non-positive values!".format(column)
          bad_indices = np.where(dataArray[:,lk[column]] <= 0.0)[0]
          print "Here is the first point with bad values, for example: "
          for i,val in enumerate(dataArray[bad_indices[0],:]):
            index = i
            for x in lk:
              if lk[x] == i:
                index = x
            print "  col {0}: {1}".format(index,val)
          sys.exit('\nPlease fix log settings (or your data) and rerun pippi.')
        dataArray[:,lk[column]] = np.log10(dataArray[:,lk[column]])


def doSort(dataArray,lk):
  # Sort chain in order of increasing posterior mass (i.e. multiplicity)
  if doPosterior.value and (contours1D.value is not None or contours2D.value is not None):
    viewString = 'float64' + ',float64' * (dataArray.shape[1]-1)
    dataArray.view(viewString).sort(order = ['f'+str(lk[labels.value[refMult]])], axis=0)


def getBestFit(dataArray,lk,outputBaseFilename,column_names,all_best_fit_data,alt_best_fit,min_contour):
  # Find best-fit point
  bestFitIndex = dataArray[:,lk[labels.value[refLike]]].argmin()
  bestFit = dataArray[bestFitIndex,lk[labels.value[refLike]]]
  worstFit = dataArray[:,lk[labels.value[refLike]]].max()
  print '    Best fit -lnlike: ',bestFit
  outfile = smart_open(outputBaseFilename+'.best','w')
  outfile.write('# This best-fit/posterior mean file created by pippi '
           +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
  outfile.write('Best-fit log-likelihood: '+str(-bestFit)+'\n')
  outfile.write('Best-fit point:\n')
  outfile.write(' '.join([str(x) for x in dataArray[bestFitIndex,:]])+'\n')
  outfile.close
  outfile = smart_open(outputBaseFilename+'.best_all','w')
  outfile.write('# This best-fit file created by pippi '\
           +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
  if (column_names is None) :
    # Just a regular ASCII chain from MultiNest or similar
    for i, x in enumerate(dataArray[bestFitIndex,:]):
       outfile.write(str(i)+': '+str(x)+'\n')
  else:
    # HDF5 file from GAMBIT or similar, with proper data record identifiers
    parameter_sets = {}
    i = 0
    for x in column_names:
       if "primary_parameters" in x:
         model = re.sub(".*@|::.*", '', x)
         par = re.sub(".*::", '', x)
         if not model in parameter_sets: parameter_sets[model] = []
         parameter_sets[model].append('    '+ par + ': ' + all_best_fit_data[i])
       if x != '':
         outfile.write(x.lstrip('#')+': '+all_best_fit_data[i]+'\n')
         i += 1
    if parameter_sets != {}:
      outfile2 = smart_open(outputBaseFilename+'.best_parameters.yaml','w')
      outfile2.write('# This best-fit file created in GAMBIT yaml format by pippi '
                     +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile2.write('# Best-fit log-likelihood: '+str(-bestFit)+'\n\n')
      for model, parameters in parameter_sets.iteritems():
        outfile2.write('    ' + model + ':\n')
        for parval in parameters: outfile2.write('  ' + parval + '\n')
      outfile2.close
  outfile.close
  if alt_best_fit.value is not None:
    halt = (min_contour is not None) and (bestFit+alt_best_fit.value > min_contour)
    bestFit = -alt_best_fit.value
    print '    Best fit -lnlike to be used to define profile likelihood ratio: ',bestFit
    if halt: sys.exit('\n  The highest CL likelihood likelihood contour you have requested contains no samples! No more pippi for you.\n')
  return [bestFit,worstFit,bestFitIndex]


def getPosteriorMean(dataArray,lk,outputBaseFilename):
  # Find posterior mean
  if doPosteriorMean:
    posteriorMean = []
    # Get total multiplicity for entire chain
    totalMult = np.sum(dataArray[:,lk[labels.value[refMult]]])
    if (totalMult == 0.0):
      sys.exit('Error: total multiplicity equal to zero.  Please make sure you have assigned posterior/weight columns correctly.\n')
    # Calculate posterior mean as weighted average of each point's contribution to each variable
    for i in range(dataArray.shape[1]):
      posteriorMean.append(np.sum(dataArray[:,lk[labels.value[refMult]]] * dataArray[:,i])/totalMult)
    outfile = smart_open(outputBaseFilename+'.best','a')
    outfile.write('Posterior mean:\n')
    outfile.write(' '.join([str(x) for x in posteriorMean])+'\n')
    outfile.close
    return [totalMult, posteriorMean]
  else:
    return [None, None]


def getEvidence(dataArray,lk,bestFit,totalMult,outputBaseFilename):
  # Get evidence (sum of mult*prior*like for mcmc)
  if doEvidence.value:
    if chainType.value is mcmc:
      lnZ = np.log(np.sum(dataArray[:,lk[labels.value[refMult]]]  * \
                          dataArray[:,lk[labels.value[refPrior]]] * \
                          np.exp(bestFit-dataArray[:,lk[labels.value[refLike]]]))) \
                          - bestFit - np.log(totalMult)
      lnZError = np.log(1.0 - pow(totalMult,-0.5))
      print '    ln(evidence): ',lnZ,'+/-',lnZError
    else:
      sys.exit('Error: evidence calculation only possible for MCMC (should never get here).')
    outfile = smart_open(outputBaseFilename+'.lnZ','w')
    outfile.write('# This evidence file created by pippi '\
                     +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
    outfile.write('ln(evidence): '+str(lnZ)+' +/- '+str(lnZError)+'\n')
    outfile.close
    return [lnZ, lnZError]
  else:
    return [None, None]


def saveExtrema(dataArray,lk,outputBaseFilename,setOfRequestedColumns,dataRanges):
  # Save the maxima and minima for each parameter requested for plotting
  outfile = smart_open(outputBaseFilename+'_savedkeys.pip','a')
  outfile.write('data_ranges =')
  for column in setOfRequestedColumns:
    extrema = [dataArray[:,lk[column]].min(), dataArray[:,lk[column]].max()]
    if column in dataRanges: extrema = [max(dataRanges[column][0], extrema[0]), min(dataRanges[column][1], extrema[1])]
    dataRanges[column] = extrema
    outfile.write(' '+str(column)+':{'+str(extrema[0])+', '+str(extrema[1])+'}')
  outfile.write('\n')
  outfile.close


def saveLookupKeys(lk,outputBaseFilename):
  # Save the lookup keys for all the requested parameters
  outfile = smart_open(outputBaseFilename+'_savedkeys.pip','a')
  outfile.write('lookup_keys =')
  if type(lk) == dict:
    for key, value in lk.iteritems(): outfile.write(' '+str(key)+':'+str(value))
  else:
    for i in lk: outfile.write(' '+str(i)+':'+str(i))
  outfile.write('\n')
  outfile.close


def oneDsampler(dataArray,lk,bestFit,worstFit,outputBaseFilename,dataRanges,nAllBins):
  # Do sample sorting for 1D plots

  if oneDplots.value is None: return

  if contours1D.value is not None:
    # Determine profile likelihood contour levels (same for all plots of a given dimensionality)
    profContourLevels = [np.exp(-deltaLnLike(0.5,0.01*contour)) for contour in contours1D.value]
    outfile = smart_open(outputBaseFilename+'_like1D.contours','w')
    outfile.write('# This 1D profile likelihood ratio contours file created by pippi '\
                  +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
    outfile.write(' '.join([str(x) for x in profContourLevels])+'\n')
    outfile.close

  for plot in oneDplots.value:

    print '    Parsing data for 1D plots of quantity ',plot

    nBins = nAllBins[plot]

    likeGrid = np.empty((nBins), dtype=np.float64)
    likeGrid[:] = worstFit + 100.0
    postGrid = np.zeros((nBins), dtype=np.float64)

    # Work out maximum and minimum values of parameter/derived quantity
    minVal = dataRanges[plot][0]
    maxVal = dataRanges[plot][1]
    rangeOfVals = maxVal - minVal
    # Fix things if the range of values is a delta function
    if (rangeOfVals <= 0): rangeOfVals = maxVal * 1e-3
    binSep = rangeOfVals / nBins

    # Calculate bin centres
    binCentresOrig = np.array([minVal + (x+0.5)*rangeOfVals/nBins for x in range(nBins)])
    binCentresInterp = np.array([binCentresOrig[0] + x*(binCentresOrig[-1]-binCentresOrig[0])\
                                 /(resolution.value-1) for x in range(resolution.value)])

    # Loop over points in chain
    for i in range(dataArray.shape[0]-1,-1,-1):
      index = min(int((dataArray[i,lk[plot]]-minVal)/rangeOfVals*nBins),nBins-1)

      # Profile over likelihoods
      if doProfile.value: likeGrid[index] = min(dataArray[i,lk[labels.value[refLike]]],likeGrid[index])

      if doPosterior.value:
        # Marginalise by addding to posterior sample count
        postGrid[index] += dataArray[i,lk[labels.value[refMult]]]

    # Convert -log(profile likelihoods) to profile likelihood ratio
    if doProfile.value: likeGrid = np.exp(bestFit - likeGrid)
    # Rescale posterior pdf to maximum 1
    if doPosterior.value: postGrid = postGrid / postGrid.max()

    # Save raw binned profile likelihood and posterior pdf for outputting in histogram files
    if doProfile.value: likeGridHistogram = likeGrid
    if doPosterior.value: postGridHistogram = postGrid

    # Interpolate profile likelihoods and posterior pdfs to requested resolution
    if doProfile.value:
      interpolator = oneDspline(binCentresOrig, likeGrid)
      likeGrid = interpolator(binCentresInterp)
      # Fix any points sent NaN by scipy's crappy interpolators
      likeGrid[np.isnan(likeGrid)] = 0.0
      # Kill off any points that have been sent negative due to ringing
      likeGrid[np.isneginf(likeGrid)] = 0.0
      likeGrid[likeGrid<0] = 0.0
      # Fix any points that have been sent >1 due to ringing
      likeGrid[np.isposinf(likeGrid)] = 1.0
      likeGrid[likeGrid>1] = 1.0

    if doPosterior.value:
      interpolator = oneDspline(binCentresOrig, postGrid)
      postGrid = interpolator(binCentresInterp)
      # Kill off any points that have been sent negative due to ringing
      postGrid[~np.isfinite(postGrid)] = 0.0
      postGrid[postGrid<0] = 0.0
      # Rescale posterior pdf  so that it has maximum 1
      postGrid = postGrid / postGrid.max()

    # Find posterior pdf contour levels
    if contours1D.value is not None and doPosterior.value:
      # Zero posterior contour levels
      postContourLevels = [None for contour in contours1D.value]
      # Zero posterior integral
      integratedPosterior = 0.0
      # Sort bins in order of posterior mass
      sortedPostGrid = np.ma.sort(postGrid)
      # Work out the new total multiplicity
      totalMult = np.sum(sortedPostGrid)
      # Work through bins backwards until total posterior mass adds up to the requested confidence levels
      for i in range(sortedPostGrid.shape[0]-1,-1,-1):
        integratedPosterior += sortedPostGrid[i]/totalMult
        for j,contour in enumerate(contours1D.value):
          if 100*integratedPosterior >= contour and postContourLevels[j] is None:
            postContourLevels[j] = sortedPostGrid[i]
        if all([x is not None for x in postContourLevels]): break

    # Write profile likelihood to file
    if doProfile.value:
      outfile = smart_open(outputBaseFilename+'_'+str(plot)+'_like1D.ct2','w')
      outfile.write('# This 1D binned profile likelihood ratio file created by pippi '\
                     +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('\n'.join([str(binCentresInterp[i])+'\t'+str(x) for i,x in enumerate(likeGrid)]))
      outfile.close
      outfile = smart_open(outputBaseFilename+'_'+str(plot)+'_like1Dhist.ct2','w')
      outfile.write('# This 1D binned profile likelihood ratio file created by pippi '\
                     +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('\n'.join([str(binCentresOrig[i]-0.5*binSep)+'\t'+str(x)+'\n'+
                               str(binCentresOrig[i]+0.5*binSep)+'\t'+str(x) for i,x in enumerate(likeGridHistogram)]))
      outfile.close

    # Write posterior pdf and contours to file
    if doPosterior.value:
      outfile = smart_open(outputBaseFilename+'_'+str(plot)+'_post1D.ct2','w')
      outfile.write('# This 1D binned posterior pdf file created by pippi '\
                     +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('\n'.join([str(binCentresInterp[i])+'\t'+str(x) for i,x in enumerate(postGrid)]))
      outfile.close
      outfile = smart_open(outputBaseFilename+'_'+str(plot)+'_post1Dhist.ct2','w')
      outfile.write('# This 1D binned posterior pdf file created by pippi '\
                     +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('\n'.join([str(binCentresOrig[i]-0.5*binSep)+'\t'+str(x)+'\n'+
                               str(binCentresOrig[i]+0.5*binSep)+'\t'+str(x) for i,x in enumerate(postGridHistogram)]))
      outfile.close
      if contours1D.value is not None:
        outfile = smart_open(outputBaseFilename+'_'+str(plot)+'_post1D.contours','w')
        outfile.write('# This 1D posterior pdf contours file created by pippi '\
                     +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
        outfile.write(' '.join([str(x) for x in postContourLevels])+'\n')
        outfile.close


def twoDsampler(dataArray,lk,bestFit,worstFit,outputBaseFilename,dataRanges,nAllBins):
  # Do sample sorting for 2D plots

  if twoDplots.value is None: return

  # Determine profile likelihood contour levels (same for all plots of a given dimensionality)
  if contours2D.value is not None:
    profContourLevels = [np.exp(-deltaLnLike(1.0,0.01*contour)) for contour in contours2D.value]
    outName = outputBaseFilename+'_like2D.contours'
    outfile = smart_open(outName,'w')
    outfile.write('# This 2D profile likelihood ratio contours file created by pippi '\
                  +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
    outfile.write(' '.join([str(x) for x in profContourLevels]))
    outfile.close

  for plot in twoDplots.value:

    print '    Parsing data for 2D plots of quantities ',plot

    nBins = [nAllBins[plot[j]] for j in range(2)]

    likeGrid = np.empty((nBins[0],nBins[1]), dtype=np.float64)
    likeGrid[:,:] = worstFit + 100.0
    postGrid = np.zeros((nBins[0],nBins[1]), dtype=np.float64)


    num_obs = 0

    if obsPlots.value is not None:
      for column in obsPlots.value:
        if column in lk:
          num_obs = num_obs+1

    obsGrid = np.zeros((num_obs,nBins[0],nBins[1]), dtype=np.float64)
    k = -1
    minimum_obs = np.zeros(num_obs)
    obsMinVal = np.zeros(num_obs)
    obsMaxVal = np.zeros(num_obs)
    obsFloor = np.zeros(num_obs)
    if obsPlots.value is not None:
      for column in obsPlots.value:
        if column in lk:
          k = k+1

          obsMinVal[k] = dataArray[:,lk[column]].min()
          obsMaxVal[k] = dataArray[:,lk[column]].max()

          # temporarily set the whole grid to a very low value
          obsGrid[k,:,:] = obsMinVal[k] - 100

          # set a value just below the actual minimum
          if obsMinVal[k] < 0:
            obsFloor[k] = obsMinVal[k]*1.01
          if obsMinVal[k] > 0:
            obsFloor[k] = obsMinVal[k]*0.99
          if obsMinVal[k] == 0:
            obsFloor[k] = -0.01

    # Work out maximum and minimum values of parameters/derived quantities
    minVal = [dataRanges[plot[j]][0] for j in range(2)]
    maxVal = [dataRanges[plot[j]][1] for j in range(2)]
    rangeOfVals = [maxVal[j] - minVal[j] for j in range(2)]
    # Pad edges of grid
    binSep = [rangeOfVals[j]/(nBins[j]-2) for j in range(2)]
    minVal = [minVal[j] - binSep[j] for j in range(2)]
    maxVal = [maxVal[j] + binSep[j] for j in range(2)]
    rangeOfVals = [rangeOfVals[j] + 2.0 * binSep[j] for j in range(2)]

    # Calculate bin centres
    binCentresOrig = []
    binCentresInterp = []
    for j in range(2): binCentresOrig.append(np.array([minVal[j] + (x+0.5)*rangeOfVals[j]/nBins[j] for x in range(nBins[j])]))
    for j in range(2): binCentresInterp.append(np.array([binCentresOrig[j][0] + x*(binCentresOrig[j][-1]-binCentresOrig[j][0])\
                                 /(resolution.value-1) for x in range(resolution.value)]))

    # Loop over points in chain
    for i in range(dataArray.shape[0]-1,-1,-1):
      [in1,in2] = [min(int((dataArray[i,lk[plot[j]]]-minVal[j])/rangeOfVals[j]*nBins[j]),nBins[j]-2) for j in range(2)]

      # Take observable at maximum likelihood for this bin
      if dataArray[i,lk[labels.value[refLike]]] < likeGrid[in1,in2]:
        if obsPlots.value is not None:
          k = -1
          for column in obsPlots.value:
            if column in lk:
              k = k + 1
              obsGrid[k,in1,in2] = dataArray[i,lk[column]]

      # Profile over likelihoods
      if doProfile.value: likeGrid[in1,in2] = min(dataArray[i,lk[labels.value[refLike]]],likeGrid[in1,in2])

      # Marginalise by addding to posterior sample count
      if doPosterior.value: postGrid[in1,in2] += dataArray[i,lk[labels.value[refMult]]]

    # Convert -log(profile likelihoods) to profile likelihood ratio
    likeGrid = np.exp(bestFit - likeGrid)

    #obsFloor = np.zeros(k+1)
    k = -1
    if obsPlots.value is not None:
        for column in obsPlots.value:
          if column in lk:
            k = k + 1

            obsContourLevels = [obsFloor[k],obsMinVal[k],obsMaxVal[k]]
            outName = outputBaseFilename+'_'+'_'.join([str(x) for x in plot])+'_obs2D_' + str(column) + '.contours'
            outfile = smart_open(outName,'w')
            outfile.write('# This 2D observable color-map levels file created by pippi '\
                          +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
            outfile.write(' '.join([str(x) for x in obsContourLevels]))
            outfile.close


    # Precompute co-ordinate grids for splines to avoid repetition
    if intMethod.value == 'spline':
      oldCoords = np.array([[binCentresOrig[0][i], binCentresOrig[1][j]] for i in range(nBins[0]) for j in range(nBins[1])])
      newCoords = [[binCentresInterp[0][i], binCentresInterp[1][j]] for i in range(resolution.value) for j in range(resolution.value)]

    # Interpolate posterior pdf, profile likelihood and observable to requested display resolution
    if doProfile.value:
      if intMethod.value == 'spline':
        likeGrid = np.array(likeGrid).reshape(nBins[0]*nBins[1])
        interpolator = twoDspline(oldCoords,likeGrid)
        likeGrid = np.array(interpolator(newCoords)).reshape(resolution.value,resolution.value)
      else:
        interpolator = twoDbilinear(binCentresOrig[0], binCentresOrig[1], likeGrid, ky = 1, kx = 1)
        likeGrid = np.array([interpolator(binCentresInterp[0][j], binCentresInterp[1][i])
                   for j in range(resolution.value) for i in range(resolution.value)]).reshape(resolution.value,resolution.value)

      # Fix any points sent NaN by scipy's crappy interpolators
      likeGrid[np.isnan(likeGrid)] = 0.0
      # Kill off any points that have been sent negative due to ringing
      likeGrid[np.isneginf(likeGrid)] = 0.0
      likeGrid[likeGrid<0] = 0.0
      # Fix any points that have been sent >1 due to ringing
      likeGrid[np.isposinf(likeGrid)] = 1.0
      likeGrid[likeGrid>1] = 1.0
      # Make sure we haven't erased the best-fit point by interpolating over it
      likeGrid[np.unravel_index(likeGrid.argmax(),likeGrid.shape)] = 1.0

    if doPosterior.value:
      if intMethod.value == 'spline':
        postGrid = np.array(postGrid).reshape(nBins[0]*nBins[1])
        interpolator = twoDspline(oldCoords,postGrid)
        postGrid = np.array(interpolator(newCoords)).reshape(resolution.value,resolution.value)
      else:
        interpolator = twoDbilinear(binCentresOrig[0], binCentresOrig[1], postGrid, ky = 1, kx = 1)
        postGrid = np.array([interpolator(binCentresInterp[0][j], binCentresInterp[1][i])
                   for j in range(resolution.value) for i in range(resolution.value)]).reshape(resolution.value,resolution.value)

      # Kill off any points that have been sent negative due to ringing
      postGrid[~np.isfinite(postGrid)] = 0.0
      postGrid[postGrid<0] = 0.0
      # Rescale posterior pdf back into the range [0,1]
      postGrid = postGrid / postGrid.max()

    if obsPlots.value is not None:
        k = -1
        for column in obsPlots.value:
          if column in lk:
            k = k + 1
            obsGrid_temp = obsGrid[k,:,:]

            obsGrid_temp[obsGrid_temp == (obsMinVal[k]-100) ] = obsMinVal[k]

            if intMethod.value == 'spline':
                    obsGrid_temp = np.array(obsGrid_temp).reshape(nBins[0]*nBins[1])
                    interpolator = twoDspline(oldCoords,obsGrid_temp)
                    obsGrid_temp = np.array(interpolator(newCoords)).reshape(resolution.value,resolution.value)
            else:
                    interpolator = twoDbilinear(binCentresOrig[0], binCentresOrig[1], obsGrid_temp, ky = 1, kx = 1)
                    obsGrid_temp = np.array([interpolator(binCentresInterp[0][j], binCentresInterp[1][i])
                               for j in range(resolution.value) for i in range(resolution.value)]).reshape(resolution.value,resolution.value)

            obsGrid_temp[obsGrid_temp < obsMinVal[k] ] = obsMinVal[k]

            # set points outside the contours to the floor value (effectively "no data")
            obsGrid_temp[likeGrid<min(profContourLevels)] = obsFloor[k]

            # Write observable to file

            outName = outputBaseFilename+'_'+'_'.join([str(x) for x in plot])+'_obs2D_'+str(column)+'.ct2'
            outfile = smart_open(outName,'w')
            outfile.write('# This 2D binned observable file created by pippi '\
                           +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
            outfile.write('\n'.join([str(binCentresInterp[0][i])+'\t'+str(binCentresInterp[1][j])+'\t'+str(obsGrid_temp[i,j]) \
                                     for i in range(obsGrid_temp.shape[0]) for j in range(obsGrid_temp.shape[1])]))
            outfile.close

            # make a dummy grid with maximum and minimum values (of the reduced grid) to use for colorbar
            obsGrid_temp_list = obsGrid_temp.reshape(obsGrid_temp.shape[1] * obsGrid_temp.shape[0] )
            obsGrid_temp_list = obsGrid_temp_list[obsGrid_temp_list != obsFloor[k]]
            obsMinValReduced = obsGrid_temp_list.min()
            obsMaxValReduced = obsGrid_temp_list.max()
            dummyGrid = np.zeros([2, 3])
            dummyGrid[0,0] = binCentresInterp[0][0]
            dummyGrid[0,1] = binCentresInterp[0][0]
            dummyGrid[0,2] = obsMinValReduced
            dummyGrid[1,0] = binCentresInterp[0][1]
            dummyGrid[1,1] = binCentresInterp[0][1]
            dummyGrid[1,2] = obsMaxValReduced
            outName = outputBaseFilename+'_'+'_'.join([str(x) for x in plot])+'_obs2D_'+str(column)+'_colorbar.ct2'
            outfile = smart_open(outName,'w')
            outfile.write('# This 2D binned observable file created by pippi '\
                           +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
            outfile.write('\n'.join([str(dummyGrid[i,0])+'\t'+str(dummyGrid[i,1])+'\t'+str(dummyGrid[i,2]) \
                                     for i in range(2) ]))
            outfile.close




    # Find posterior pdf contour levels
    if contours2D.value is not None and doPosterior.value:
      # Zero posterior contour levels
      postContourLevels = [None for contour in contours2D.value]
      # Zero posterior integral
      integratedPosterior = 0.0
      # Sort bins in order of posterior mass
      sortedPostGrid = np.ma.sort(postGrid.flatten())
      # Work out the new total multiplicity
      totalMult = np.sum(sortedPostGrid)
      # Work through bins backwards until total posterior mass adds up to the requested confidence levels
      for i in range(sortedPostGrid.shape[0]-1,-1,-1):
        integratedPosterior += sortedPostGrid[i]/totalMult
        for j,contour in enumerate(contours2D.value):
          if 100*integratedPosterior >= contour and postContourLevels[j] is None:
            postContourLevels[j] = sortedPostGrid[i]
        if all([x is not None for x in postContourLevels]): break

    # Write profile likelihood to file
    if doProfile.value:
      outName = outputBaseFilename+'_'+'_'.join([str(x) for x in plot])+'_like2D.ct2'
      outfile = smart_open(outName,'w')
      outfile.write('# This 2D binned profile likelihood ratio file created by pippi '\
                     +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('\n'.join([str(binCentresInterp[0][i])+'\t'+str(binCentresInterp[1][j])+'\t'+str(likeGrid[i,j]) \
                               for i in range(likeGrid.shape[0]) for j in range(likeGrid.shape[1])]))
      outfile.close

    # Write posterior pdf and contours to file
    if doPosterior.value:
      outName = outputBaseFilename+'_'+'_'.join([str(x) for x in plot])+'_post2D.ct2'
      outfile = smart_open(outName,'w')
      outfile.write('# This 2D binned posterior pdf file created by pippi '\
                     +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('\n'.join([str(binCentresInterp[0][i])+'\t'+str(binCentresInterp[1][j])+'\t'+str(postGrid[i,j]) \
                               for i in range(postGrid.shape[0]) for j in range(postGrid.shape[1])]))
      outfile.close
      if contours2D.value is not None:
        outName = outputBaseFilename+'_'+'_'.join([str(x) for x in plot])+'_post2D.contours'
        outfile = smart_open(outName,'w')
        outfile.write('# This 2D posterior pdf contours file created by pippi '\
                     +pippiVersion+' on '+datetime.datetime.now().strftime('%c')+'\n')
        outfile.write(' '.join([str(x) for x in postContourLevels]))
        outfile.close



