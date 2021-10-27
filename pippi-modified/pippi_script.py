
#############################################################
# pippi: parse it, plot it
# ------------------------
# Program for creating plotting scripts for pippi.
#
# Author: Pat Scott (patscott@physics.mcgill.ca)
# Originally developed: March 2012
#############################################################

from pippi_read import *
from pippi_utils import *
import os
import subprocess

#Define pip file entries required from parsing
parsedir = dataObject('parse_dir', safe_string)

# Define script-specific pip file entries
scriptdir      = dataObject('script_dir', safe_string)
doComparison   = dataObject('plot_comparison', boolean)
postMeanOnPost = dataObject('plot_posterior_mean_on_posterior_pdf', boolean)
postMeanOnProf = dataObject('plot_posterior_mean_on_profile_like', boolean)
bestFitOnPost  = dataObject('plot_best_fit_on_posterior_pdf', boolean)
bestFitOnProf  = dataObject('plot_best_fit_on_profile_like', boolean)
doLegend1D     = dataObject('legend_on_1D', int_list)
doLegend2D     = dataObject('legend_on_2D', intuple_list)
legendLoc1D    = dataObject('legend_locations_1D', string_dictionary)
legendLoc2D    = dataObject('legend_locations_2D', int_pair_string_dictionary)
doKey1D        = dataObject('key_on_1D', int_list)
doKey2D        = dataObject('key_on_2D', intuple_list)
keyLoc1D       = dataObject('key_locations_1D', string_dictionary)
keyLoc2D       = dataObject('key_locations_2D', int_pair_string_dictionary)
doColourbar    = dataObject('plot_colourbar_2D', intuple_list)
doHistograms   = dataObject('plot_as_histograms_1D', boolean)
legendLines    = dataObject('extra_legend_lines', string_list)
plotSize       = dataObject('plot_size', string)
blame          = dataObject('blame', string)
logoFile       = dataObject('logo_file', string)
logoLoc        = dataObject('logo_loc', floatuple_list)
logoWidth      = dataObject('logo_width', floater)
colours        = dataObject('colour_scheme', internal)
axisRanges     = dataObject('axis_ranges', floatuple_dictionary)
yAxisAngle     = dataObject('yaxis_number_angle', floater)
refPoint       = dataObject('reference_point', float_dictionary)
refKey         = dataObject('reference_text', string)

keys = keys+[scriptdir, doComparison, postMeanOnPost, postMeanOnProf, bestFitOnPost,
             bestFitOnProf, doColourbar, doLegend1D, doLegend2D, legendLoc1D, legendLoc2D,
             doHistograms, legendLines, blame, colours, axisRanges, yAxisAngle, refPoint,
             refKey, doKey1D, doKey2D, keyLoc1D, keyLoc2D, parsedir, logoFile, logoLoc, logoWidth]

# Define pip file entries to be read from savedkeys file
labels = dataObject('quantity_labels', string_dictionary)
dataRanges = dataObject('data_ranges', floatuple_dictionary)
lookupKeys = dataObject('lookup_keys', int_dictionary)

# Constants
left_margin   = 0.16
right_margin  = 0.03
top_margin    = 0.05
bottom_margin = 0.16
plot_scale    = 1.1
blameFractionalVerticalOffset = 1.2e-2
PosteriorIsMainInComboPlot    = True
likeColourbarString           = 'Profile likelihood ratio $\Lambda=\mathcal{L}/\mathcal{L}_\mathrm{max}$'
postColourbarString           = 'Relative probability $P/P_\mathrm{max}$'
defaultLegendLocation         = 'bl'
defaultKeyLocation            = 'tr'
defaultRefKey                 = 'Ref.\ point'
keyYSep = 0.055
keyXSep = 0.04
keyYVals = {'t': [0.94 - x*keyYSep for x in range(3)], 'c': [
    0.44 + x*keyYSep for x in range(3)], 'b': [0.065 + x*keyYSep for x in range(3)]}
keyXVals = {'r': [0.74 + x*keyXSep for x in range(2)], 'c': [
    0.45 + x*keyXSep for x in range(2)], 'l': [0.06 + x*keyXSep for x in range(2)]}


class scriptDirectories:
  # the script directory + chain name (prefixes each script)
  baseScriptFilename = ""
  # the parse data directory + chain name (prefixes each parse data)
  parseFilename = ""
  # the relative path to parseFilename from script directory
  parseFilenameFromScriptFiledir = ""
  # the parse data directory with second chain name
  secParseFilename = ""
  # the relative path to secParseFilename from script directory
  secParseFilenameFromScriptFiledir = ""
  # # the relative path to logo file from script directory
  # logoFile = ""


def script(filename):
  # input:  filename = the name of the pip file

  # Parse pip file
  print()
  getIniData(filename, keys)

  # Make sure that comparison is turned off if comparison filename is missing
  if doComparison.value and secChain.value is None:
    print('  Warning: comparison curves requested but no comparison file specified.\n  Skipping comparison...\n')
    doComparison.value = False

  # Work out where the parse output is located
  if parsedir.value is None:
    # No parse_dir; default to searching the directory containing chain(s)
    parseFiledir = re.sub(r'/.*?$', '/', mainChain.value)
  else:
    # Search in parse_dir
    parseFiledir = parsedir.value+'/'

  # Work out where the script output is to be located
  if scriptdir.value is None:
    # No script_dir; default to parse directory
    baseScriptDir = parseFiledir
  else:
    # Save in script_dir
    baseScriptDir = scriptdir.value+'/'
    # Make sure script_dir exists, make it if not
    safe_dir(scriptdir.value)

  # Work out how to reference the parse dir from the script dir
  if parseFiledir[0] == '/' or parseFiledir[0] == '~':  # !!!!!
    # The parse output path is absolute; easy-peasy
    parseFiledirFromScriptFiledir = parseFiledir
  else:
    # The parse output path is a relative one
    if baseScriptDir[0] == '/' or baseScriptDir[0] == '~':
      # The script output is to be placed in an absolute path; need to convert the parse path to absolute too
      parseFiledirFromScriptFiledir = os.getcwd() + '/' + parseFiledir
    else:
      # The script output is also to be placed in a relative path
      parseFiledirFromScriptFiledir = re.sub(
          r'.+?/', '../', baseScriptDir+'/') + parseFiledir

  # Locate and scale logo (if any)
  if logoFile.value is not None:
    if logoFile.value == 'pippi':
      logoFile.value = sys.path[0]+'/pippi'
    # Work out how to reference the logo file from the script dir
    if logoFile.value[0] != '/':
      if baseScriptDir[0] == '/':
        # The script output is to be placed in an absolute path; need to convert the logo path to absolute too
        logoFile.value = os.getcwd() + '/' + logoFile.value
      else:
        # The script output is also to be placed in a relative path
        logoFile.value = re.sub(
            r'.+?/', '../', baseScriptDir+'/') + logoFile.value

  # setup directories that we need for our scripts
  dirs = scriptDirectories

  # Strip extensions off chain filenames
  dirs.baseScriptFilename = baseScriptDir + \
      re.sub(r'.*/|\..?.?.?$', '', mainChain.value)
  dirs.parseFilename = parseFiledir + \
      re.sub(r'.*/|\..?.?.?$', '', mainChain.value)
  dirs.parseFilenameFromScriptFiledir = parseFiledirFromScriptFiledir + \
      re.sub(r'.*/|\..?.?.?$', '', mainChain.value)
  if doComparison.value:
    dirs.secParseFilename = parseFiledir + \
        re.sub(r'.*/|\..?.?.?$', '', secChain.value) + '_comparison'
    dirs.secParseFilenameFromScriptFiledir = parseFiledirFromScriptFiledir + \
        re.sub(r'.*/|\..?.?.?$', '', secChain.value) + '_comparison'

  # Retrieve labels and data ranges saved in earlier parsing run
  getIniData([dirs.parseFilename+'_savedkeys.pip'],
             [labels, dataRanges, lookupKeys])

  #Work out whether to do posteriors and check that flags match up
  if doPosterior.value and not any(x in labels.value for x in permittedMults):
    print('  Warning: do_posterior_pdf = T but no multiplicity in chain labels.\n  Skipping posterior PDF...')
    doPosterior.value = False

  # set colour scheme if it is undefined
  if colours.value is None:
    colours.value = basic

  # Create 1D plotting scripts
  if oneDplots.value is not None:
    scriptOneDplots(dirs)

  # Create 2D plotting scripts
  if twoDplots.value is not None:
    scriptTwoDplots(dirs)

  # Create grid plotting scripts
  # scriptGridPlots(dirs)


def scriptGridPlots(dirs):

    # Set up filenames
    currentBase = dirs.baseScriptFilename+'_'+str(plot)
    currentParse = dirs.parseFilenameFromScriptFiledir+'_'+str(plot)
    currentBaseMinimal = re.sub(r'.*/', '', currentBase)
    if doComparison.value:
        currentSecParse = dirs.secParseFilenameFromScriptFiledir+'_'+str(plot)

    # # Get plot limits
    # xtrema = dictFallback(axisRanges, dataRanges, plot)
    # xRange = xtrema[1] - xtrema[0]
    # ytrema = [0.0, 1.0]
    # yRange = 1.0



    # read in grids from file
    # we need a grid of existing 1D or 2D plots
    # for now just use hard-coded array

    # read list of parse directories from file
    # or use current parse directory if none given

    # get list of colours from somewhere...
    # just hardcode for now

    # loop over grids (just the single hardedcoded one for now)

    # get grid size from file...
    plotSizeInternal = '26cm x 26cm'

    # get grid name from file...
    plotName = 'lambda_grid'
    gridSizeString = '5x5'
    # TODO: how to deal with margins and spacing ???

    # Open plotting shell script file for writing
    outfile = smart_open(currentBase+'_like1D.bsh', 'w')
    outfile.write('#!/usr/bin/env bash\n')
    outfile.write('# This plot script created by pippi '+pippiVersion +
                  ' on '+datetime.datetime.now().strftime('%c')+'\n')
    outfile.write('ctioga2\\\n')
    outfile.write('  --name '+currentBaseMinimal+'plotName')
    outfile.write('  --page-size \''+plotSizeInternal+'\'\\\n')
    outfile.write('  --setup-grid ' + gridSizeString + ' \'top=5mm /right=5mm /bottom=20mm /left=20mm /dx=2mm /dy=2mm \\\n')
    outfile.write('  --define-axis-style \'.grid-non-left axis.left\' /decoration=ticks /axis-label-text=\' \'  \\\n')
    outfile.write('  --define-axis-style \'.grid-non-bottom axis.bottom\' /decoration=ticks /axis-label-text=\' \'  \\\n')
    outfile.write('  --define-axis-style \'.grid-2-0 axis\' /decoration=None \\\n')

    # loop over grid dimensions

    # we want to re-use the code from below somehow
    # but do we need to remove stuff ???
    # seems like we have to recode since we must delete extra contours...
    # we dont want best fit star (or CL lines for 1D) if using multiple datasets
    # otherwise do include them

    # so need to extract star/CL lines/contours from code below..

    # if (x != y) out << "  --xyz-map \\\n";
    # else out << "  --xy-plot \\\n";

    # if (x == 0 && y == 0) out << "  --inset grid:0,0 \\\n";
    # else out << "  --next-inset grid:" << x << "," << y << " \\\n";
    # if (y == gridSize - 1) out << "    --xlabel '$\\lambda_" << x + 1 << "$' \\\n";
    # if (x == 0) out << "    --ylabel '$\\lambda_" << y + 1 << "$' /shift 1.9 \\\n";
    # if (y == gridSize - 1) out << "    --label-style x /scale 1.0 /shift 0.15 \\\n";
    # if (x == 0) out << "    --label-style y /scale 1.0 /shift 0.75 /angle -90.0  /valign 'midheight' \\\n";

    # // 1D hist
    # if (x == y)
    # {
    #   if (x <= 1) out << "    --xrange " << range12 << "\\\n";
    #   else out << "    --xrange " << range345 << "\\\n";
    #   out << "    --yrange 0:1 \\\n";
    #   out << "    --plot " << dirs[0] << "data_" << x + 1 << "_like1Dhist.ct2@1:2 /fill xaxis /fill-transparency 0.85 /fill-color Burgundy /color Blue /line-style Solid /line-width 0.9 \\\n";
    #   // CL lines
    #   // best fit star
    # }

    # // 2D contour plot
    # if (x != y)
    # {
    #   if (x <= 1) out << "    --xrange " << range12 << "\\\n";
    #   else out << "    --xrange " << range345 << "\\\n";
    #   if (y <= 1) out << "    --yrange " << range12 << "\\\n";
    #   else out << "    --yrange " << range345 << "\\\n";
    #   out << "    --plot " << dirs[0] << "data_" << x + 1 << "_" << y + 1 << "_like2D.ct2@1:2:3 /color-map '#fff--#fff(0.04599999999999993)--#f45(0.31700000000000006)--#612' \\\n";
    #   out << "    --draw-contour 0.0030000000000000044 /color " << colours[0] << " /style Solid /width 2 \\\n";
    #   // add rest of plots (transparent)
    #   // add contours (need to find them...)
    #   for (int k = 1; k < dirs.size(); ++k)
    #   {
    #     out << "    --plot " << dirs[k] << "data_" << x + 1 << "_" << y + 1 << "_like2D.ct2@1:2:3 /fill-transparency 1 \\\n";
    #     out << "    --draw-contour 0.0030000000000000044 /color " << colours[k] << " /style Solid /width 2 \\\n";
    #   }
    # }


def scriptOneDplots(dirs):

  # Determine whether histograms are required or not
  histString = '' if doHistograms.value is None or not doHistograms.value else 'hist'

  # Loop over requested plots
  for plot in oneDplots.value:

    print('    Writing scripts for 1D plots of quantity ', plot)

    # Set up filenames
    currentBase = dirs.baseScriptFilename+'_'+str(plot)
    currentParse = dirs.parseFilenameFromScriptFiledir+'_'+str(plot)
    currentBaseMinimal = re.sub(r'.*/', '', currentBase)
    if doComparison.value:
        currentSecParse = dirs.secParseFilenameFromScriptFiledir+'_'+str(plot)

    # Get plot limits
    xtrema = dictFallback(axisRanges, dataRanges, plot)
    xRange = xtrema[1] - xtrema[0]
    ytrema = [0.0, 1.0]
    yRange = 1.0

    # Locate and scale logo (if any)
    if logoFile.value is not None:
      logoCoords = [xtrema[0]+logoLoc.value[0]
                    [0]*xRange, logoLoc.value[0][1]]
      logoString = '\'\\includegraphics[width = ' + \
          str(logoWidth.value*8.8)+'cm]{'+logoFile.value+'}\''

    # Determine reference point
    if refPoint.value is not None and plot in refPoint.value:
      plotRef = True
      refString = '  --draw-marker '+str(refPoint.value[plot])+','+str(yRange*colours.value.referenceMarkerInnerScale/40.0)+' ' +\
          colours.value.referenceMarkerInner+' /color \''+colours.value.referenceMarkerInnerColour +\
          '\' /scale '+str(colours.value.referenceMarkerInnerScale)+' \\\n' +\
                  '  --draw-marker '+str(refPoint.value[plot])+','+str(yRange*colours.value.referenceMarkerOuterScale/40.0)+' ' +\
          colours.value.referenceMarkerOuter+' /color \''+colours.value.referenceMarkerOuterColour +\
          '\' /scale ' + \
          str(colours.value.referenceMarkerOuterScale)+' \\\n'
    else:
      plotRef = False

    # Determine plot size
    if plotSize.value is None or plotSize.value is '':
        plotSizeInternal = '11cm x 4in'
    else:
        plotSizeInternal = plotSize.value

    # Make profile likelihood plotting scripts
    if doProfile.value:

      # Get contours
      if contours1D.value is not None:
        contourLevels = getContours(dirs.parseFilename, plot, 'like')

      # Determine keys
      keyString = ''
      if doKey1D.value is not None and plot in doKey1D.value:
        # Get gross key location
        try:
          keyLoc = keyLoc1D.value[plot]
        except (KeyError, TypeError):
          keyLoc = defaultKeyLocation
        # Get text to be used for reference point
        refText = defaultRefKey if refKey.value is None else refKey.value
        # Get x and y coordinates for 3 possible keys (for markers and text)
        yVals = ytrema[0] + np.array(keyYVals[keyLoc[0]])*yRange
        xVals = xtrema[0] + np.array(keyXVals[keyLoc[1]])*xRange
        markers = []
        # Get details of key for reference point
        if plotRef:
            markers.append([colours.value.referenceMarkerOuter, colours.value.referenceMarkerOuterColour,
                            colours.value.referenceMarkerOuterScale, refText, colours.value.referenceMarkerInner,
                            colours.value.referenceMarkerInnerColour, colours.value.referenceMarkerInnerScale /
                            colours.value.referenceMarkerOuterScale])
        # Get details of key for posterior mean
        if postMeanOnProf.value:
            markers.append([colours.value.mainPostMeanMarker, colours.value.mainPostMeanColour1D,
                            colours.value.mainPostMeanMarkerScale, 'Mean'])
        # Get details of key for best fit
        if bestFitOnProf.value:
            markers.append([colours.value.mainBestFitMarker, colours.value.mainBestFitColour1D,
                            colours.value.mainBestFitMarkerScale, 'Best fit'])
        # Reverse vertical ordering if keys are to be placed at the top of the page, so as to fill from the top down
        if keyLoc[0] == 't':
            markers.reverse()
        # Construct ctioga2 command for each key
        for i, key in enumerate(markers):
          if key[0] == 'Bullet' or key[0] == 'BulletOpen':
              key[2] /= 1.5
          if key[2] > 1.0:
              key[2] = 1.0
          # Write the extra marker overlay for the reference point
          if len(key) == 7:
              keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[4]+' /color \'' +\
                  key[5]+'\' /scale '+str(key[6]*key[2])+'\\\n'
          # Write the main marker
          keyString += '  --draw-marker '+str(xVals[0])+','+str(
              yVals[i])+' '+key[0]+' /color \''+key[1]+'\' /scale '+str(key[2])+'\\\n'
          # Write the key text
          keyString += '  --draw-text ' + \
              str(xVals[1])+','+str(yVals[i])+' \''+key[3] + \
              '\'  /color \''+colours.value.keyTextColour1D
          keyString += '\' /justification left /scale 0.75 /alignment center \\\n'

      # Open plotting shell script file for writing
      outfile = smart_open(currentBase+'_like1D.bsh', 'w')
      outfile.write('#!/usr/bin/env bash\n')
      outfile.write('# This plot script created by pippi '+pippiVersion +
                    ' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('ctioga2 \\\n')
      outfile.write('  --name '+currentBaseMinimal+'_like1D')
      outfile.write('  --plot-scale \''+str(plot_scale)+'\'\\\n')
      outfile.write('  --page-size \''+plotSizeInternal+'\'\\\n')
      outfile.write('  --frame-margins '+str(left_margin)+','
                                        + str(right_margin)+','
                                        + str(top_margin)+','
                                        + str(bottom_margin)+'\\\n')
      outfile.write('  --xrange '+str(xtrema[0])+':'+str(xtrema[1])+'\\\n')
      outfile.write('  --yrange 0:1\\\n')
      outfile.write(
          '  --ylabel \'Profile likelihood ratio $\Lambda=\mathcal{L}/\mathcal{L}_\mathrm{max}$\' /shift 2.1\\\n')
      outfile.write('  --xlabel \''+labels.value[plot]+'\'\\\n')
      outfile.write(
          '  --label-style x /scale 1.0 /shift 0.15 --label-style y /scale 1.0 /shift 0.15')
      if yAxisAngle.value is not None:
          outfile.write(' /angle '+str(yAxisAngle.value))
      outfile.write('\\\n')
      if contours1D is not None:
        for i, contour in enumerate(contourLevels):
          outfile.write('  --draw-line '+str(xtrema[0])+','+contour+' '+str(xtrema[1])+','+contour+' /color \'Black\' ' +
                        '/style Dashes /width '+str(float(colours.value.lineWidth1D)*0.5)+'\\\n')
          outfile.write('  --draw-text '+str(xtrema[0]+0.045*(xtrema[1]-xtrema[0]))+','+str(float(contour)+0.005)+' \''+str(contours1D.value[i]) +
                        '\%CL\' /color \'Black\' /scale 0.5 /justification left /alignment bottom\\\n')
      if doComparison.value:
        # Do everything for comparison chain
        outfile.write('  --plot '+currentSecParse+'_like1D'+histString+'.ct2@1:2 /fill xaxis /fill-transparency '+colours.value.fillTransparency1D +
                      ' /fill-color '+colours.value.comparisonProfColour1D+' /color '+colours.value.comparisonProfColour1D +
                      ' /line-style '+colours.value.comparison1DLineStyle+' /line-width '+colours.value.lineWidth1D+'\\\n')
        if bestFitOnProf.value and colours.value.comparisonBestFitMarker is not None:
          # Get best-fit point and plot it
          bestFit = getCentralVal(
              dirs.secParseFilename, plot, 'like', lookupKeys)
          outfile.write('  --draw-marker '+str(bestFit)+','+str(yRange*colours.value.comparisonBestFitMarkerScale/40.0)+' ' +
                        colours.value.comparisonBestFitMarker+' /color \''+colours.value.comparisonBestFitColour +
                        '\' /scale '+str(colours.value.comparisonBestFitMarkerScale)+' \\\n')
        if postMeanOnProf.value and colours.value.comparisonPostMeanMarker is not None:
          # Get posterior mean and plot it
          postMean = getCentralVal(
              dirs.secParseFilename, plot, 'post', lookupKeys)
          if not postMean:
              sys.exit(
                  'Error: plot_posterior_mean_on_profile_like = T but no multiplicity given!')
          outfile.write('  --draw-marker '+str(postMean)+','+str(yRange*colours.value.comparisonPostMeanMarkerScale/40.0)+' ' +
                        colours.value.comparisonPostMeanMarker+' /color \''+colours.value.comparisonPostMeanColour +
                        '\' /scale '+str(colours.value.comparisonPostMeanMarkerScale)+' \\\n')
      outfile.write('  --plot '+currentParse+'_like1D'+histString+'.ct2@1:2 /fill xaxis /fill-transparency '+colours.value.fillTransparency1D +
                    ' /fill-color '+colours.value.mainProfColour1D+' /color '+colours.value.mainProfColour1D +
                    ' /line-style '+colours.value.main1DLineStyle+' /line-width '+colours.value.lineWidth1D+'\\\n')
      
      if doLegend1D.value is not None and plot in doLegend1D.value:
        # Write legend
        try:
          legendLocation = legendLoc1D.value[plot]
        except (KeyError, TypeError):
          legendLocation = defaultLegendLocation
        outfile.write('  --legend-inside \''+legendLocation +
                      '\' /scale 1.0 /vpadding 0.1\\\n')
        if legendLines.value is not None:
          for x in legendLines.value:
              outfile.write('  --legend-line \''+x+'\' /color \'' +
                            colours.value.legendTextColour1D+'\'\\\n')
        outfile.write('  --legend-line \'Prof.~likelihood\' /color \'' +
                      colours.value.legendTextColour1D+'\'\\\n')
      
      if bestFitOnProf.value:
        # Get best-fit point and plot it
        bestFit = getCentralVal(dirs.parseFilename, plot, 'like', lookupKeys)
        outfile.write('  --draw-marker '+str(bestFit)+','+str(yRange*colours.value.mainBestFitMarkerScale/40.0)+' ' +
                      colours.value.mainBestFitMarker+' /color \''+colours.value.mainBestFitColour1D +
                      '\' /scale '+str(colours.value.mainBestFitMarkerScale)+' \\\n')
      
      if postMeanOnProf.value:
        # Get posterior mean and plot it
        postMean = getCentralVal(dirs.parseFilename, plot, 'post', lookupKeys)
        if not postMean:
            sys.exit('Error: plot_posterior_mean_on_profile_like = T but no multiplicity given!')
        outfile.write('  --draw-marker '+str(postMean)+','+str(yRange*colours.value.mainPostMeanMarkerScale/40.0)+' ' +
                      colours.value.mainPostMeanMarker+' /color \''+colours.value.mainPostMeanColour1D +
                      '\' /scale '+str(colours.value.mainPostMeanMarkerScale)+' \\\n')
     
      # Plot reference point
      if plotRef:
          outfile.write(refString)

      # Draw key
      outfile.write(keyString)

      # Write credits
      if blame.value is not None:
        blameYCoordinate = str(
            blameFractionalVerticalOffset * yRange + ytrema[1])
        outfile.write('  --draw-text '+str(xtrema[1])+','+blameYCoordinate +
                      ' \''+blame.value+'\' /scale 0.5 /justification right\\\n')
      # Add logo
      if logoFile.value is not None:
        outfile.write('  --draw-text '+str(logoCoords[0])+','+str(logoCoords[1])+' '+logoString+'\\\n')
      
      # Set axis colours
      for x in ['top', 'bottom', 'left', 'right']:
        outfile.write('  --axis-style '+x+' /stroke_color \'' + colours.value.axisColour1D+'\'\\\n')
      
      outfile.close
      subprocess.call('chmod +x '+currentBase+'_like1D.bsh', shell=True)

    # Make posterior pdf plotting scripts
    if doPosterior.value:

      # Get contours
      if contours1D.value is not None:
        mainContourLevels = getContours(dirs.parseFilename, plot, 'post')
        if doComparison.value:
            secContourLevels = getContours(dirs.secParseFilename, plot, 'post')

      # Determine keys
      keyString = ''
      if doKey1D.value is not None and plot in doKey1D.value:
        # Get gross key location
        try:
          keyLoc = keyLoc1D.value[plot]
        except (KeyError, TypeError):
          keyLoc = defaultKeyLocation
        # Get text to be used for reference point
        refText = defaultRefKey if refKey.value is None else refKey.value
        # Get x and y coordinates for 3 possible keys (for markers and text)
        yVals = ytrema[0] + np.array(keyYVals[keyLoc[0]])*yRange
        xVals = xtrema[0] + np.array(keyXVals[keyLoc[1]])*xRange
        markers = []
        # Get details of key for reference point
        if plotRef:
            markers.append([colours.value.referenceMarkerOuter, colours.value.referenceMarkerOuterColour,
                            colours.value.referenceMarkerOuterScale, refText, colours.value.referenceMarkerInner,
                            colours.value.referenceMarkerInnerColour, colours.value.referenceMarkerInnerScale /
                            colours.value.referenceMarkerOuterScale])
        # Get details of key for posterior mean
        if postMeanOnPost.value:
            markers.append([colours.value.mainPostMeanMarker, colours.value.mainPostMeanColour1D,
                            colours.value.mainPostMeanMarkerScale, 'Mean'])
        # Get details of key for best fit
        if bestFitOnPost.value:
            markers.append([colours.value.mainBestFitMarker, colours.value.mainBestFitColour1D,
                            colours.value.mainBestFitMarkerScale, 'Best fit'])
        # Reverse vertical ordering if keys are to be placed at the top of the page, so as to fill from the top down
        if keyLoc[0] == 't':
            markers.reverse()
        # Construct ctioga2 command for each key
        for i, key in enumerate(markers):
          if key[0] == 'Bullet' or key[0] == 'BulletOpen':
              key[2] /= 1.5
          if key[2] > 1.0:
              key[2] = 1.0
          # Write the extra marker overlay for the reference point
          if len(key) == 7:
              keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[4]+' /color \'' +\
                  key[5]+'\' /scale '+str(key[6]*key[2])+'\\\n'
          # Write the main marker
          keyString += '  --draw-marker '+str(xVals[0])+','+str(
              yVals[i])+' '+key[0]+' /color \''+key[1]+'\' /scale '+str(key[2])+'\\\n'
          # Write the key text
          keyString += '  --draw-text ' + \
              str(xVals[1])+','+str(yVals[i])+' \''+key[3] + \
              '\'  /color \''+colours.value.keyTextColour1D
          keyString += '\' /justification left /scale 0.75 /alignment center \\\n'

      # Open plotting shell script file for writing
      outfile = smart_open(currentBase+'_post1D.bsh', 'w')
      outfile.write('#!/usr/bin/env bash\n')
      outfile.write('# This plot script created by pippi '+pippiVersion +
                    ' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('ctioga2\\\n')
      outfile.write('  --name '+currentBaseMinimal+'_post1D')
      outfile.write('  --plot-scale \''+str(plot_scale)+'\'\\\n')
      outfile.write('  --page-size \''+plotSizeInternal+'\'\\\n')
      outfile.write('  --frame-margins '+str(left_margin)+','
                                        + str(right_margin)+','
                                        + str(top_margin)+','
                                        + str(bottom_margin)+'\\\n')
      outfile.write('  --xrange '+str(xtrema[0])+':'+str(xtrema[1])+'\\\n')
      outfile.write('  --yrange 0:1\\\n')
      outfile.write(
          '  --ylabel \'Relative probability $P/P_\mathrm{max}$\' /shift 2.1\\\n')
      outfile.write('  --xlabel \''+labels.value[plot]+'\'\\\n')
      outfile.write(
          '  --label-style x /scale 1.0 /shift 0.15 --label-style y /scale 1.0 /shift 0.15')
      if yAxisAngle.value is not None:
          outfile.write(' /angle '+str(yAxisAngle.value))
      outfile.write('\\\n')
      if contours1D is not None:
        for i, contour in enumerate(mainContourLevels):
          outfile.write('  --draw-line '+str(xtrema[0])+','+contour+' '+str(xtrema[1])+','+contour+' /color \''+colours.value.mainPostColour1D +
                        '\' /style Dashes /width '+str(float(colours.value.lineWidth1D)*0.5)+'\\\n')
          outfile.write('  --draw-text '+str(xtrema[0]+0.045*(xtrema[1]-xtrema[0]))+','+str(float(contour)+0.005)+' \''+str(contours1D.value[i]) +
                        '\%CR\' /color \''+colours.value.mainPostColour1D+'\' /scale 0.5 /justification left /alignment bottom\\\n')
      if doComparison.value:
        # Do everything for comparison chain
        if contours1D is not None:
          for i, contour in enumerate(secContourLevels):
            outfile.write('  --draw-line '+str(xtrema[0])+','+contour+' '+str(xtrema[1])+','+contour+' /color \''+colours.value.comparisonPostColour1D +
                          '\' /style Dashes /width '+str(float(colours.value.lineWidth1D)*0.5)+'\\\n')
            outfile.write('  --draw-text '+str(xtrema[0]+0.045*(xtrema[1]-xtrema[0]))+','+str(float(contour)+0.005)+' \''+str(contours1D.value[i]) +
                          '\%CR\' /color \''+colours.value.comparisonPostColour1D+'\' /scale 0.5 /justification left /alignment bottom\\\n')
        outfile.write('  --plot '+currentSecParse+'_post1D'+histString+'.ct2@1:2 /fill xaxis /fill-transparency '+colours.value.fillTransparency1D +
                      ' /fill-color '+colours.value.comparisonPostColour1D+' /color '+colours.value.comparisonPostColour1D +
                      ' /line-style '+colours.value.comparison1DLineStyle+' /line-width '+colours.value.lineWidth1D+'\\\n')
        if bestFitOnPost.value and colours.value.comparisonBestFitMarker is not None:
          # Get best-fit point and plot it
          bestFit = getCentralVal(dirs.secParseFilename, plot, 'like', lookupKeys)
          outfile.write('  --draw-marker '+str(bestFit)+','+str(yRange*colours.value.comparisonBestFitMarkerScale/40.0)+' ' +
                        colours.value.comparisonBestFitMarker+' /color \''+colours.value.comparisonBestFitColour +
                        '\' /scale '+str(colours.value.comparisonBestFitMarkerScale)+' \\\n')
        if postMeanOnPost.value and colours.value.comparisonPostMeanMarker is not None:
          # Get posterior mean and plot it
          postMean = getCentralVal(
              dirs.secParseFilename, plot, 'post', lookupKeys)
          if not postMean:
              sys.exit(
                  'Error: plot_posterior_mean_on_posterior_pdf = T but no multiplicity given!')
          outfile.write('  --draw-marker '+str(postMean)+','+str(yRange*colours.value.comparisonPostMeanMarkerScale/40.0)+' ' +
                        colours.value.comparisonPostMeanMarker+' /color \''+colours.value.comparisonPostMeanColour +
                        '\' /scale '+str(colours.value.comparisonPostMeanMarkerScale)+' \\\n')
      outfile.write('  --plot '+currentParse+'_post1D'+histString+'.ct2@1:2 /fill xaxis /fill-transparency '+colours.value.fillTransparency1D +
                    ' /fill-color '+colours.value.mainPostColour1D+' /color '+colours.value.mainPostColour1D +
                    ' /line-style '+colours.value.main1DLineStyle+' /line-width '+colours.value.lineWidth1D+'\\\n')
      if doLegend1D.value is not None and plot in doLegend1D.value:
        # Write legend
        try:
          legendLocation = legendLoc1D.value[plot]
        except (KeyError, TypeError):
          legendLocation = defaultLegendLocation
        outfile.write('  --legend-inside \''+legendLocation +
                      '\' /scale 1.0 /vpadding 0.1\\\n')
        if legendLines.value is not None:
          for x in legendLines.value:
              outfile.write('  --legend-line \''+x+'\' /color \'' +
                            colours.value.legendTextColour1D+'\'\\\n')
        outfile.write('  --legend-line \'Marg.~posterior\' /color \'' +
                      colours.value.legendTextColour1D+'\'\\\n')
      if bestFitOnPost.value:
        # Get best-fit point and plot it
        bestFit = getCentralVal(dirs.parseFilename, plot, 'like', lookupKeys)
        outfile.write('  --draw-marker '+str(bestFit)+','+str(yRange*colours.value.mainBestFitMarkerScale/40.0)+' ' +
                      colours.value.mainBestFitMarker+' /color \''+colours.value.mainBestFitColour1D +
                      '\' /scale '+str(colours.value.mainBestFitMarkerScale)+' \\\n')
      if postMeanOnPost.value:
        # Get posterior mean and plot it
        postMean = getCentralVal(dirs.parseFilename, plot, 'post', lookupKeys)
        if not postMean:
            sys.exit(
                'Error: plot_posterior_mean_on_posterior_pdf = T but no multiplicity given!')
        outfile.write('  --draw-marker '+str(postMean)+','+str(yRange*colours.value.mainPostMeanMarkerScale/40.0)+' ' +
                      colours.value.mainPostMeanMarker+' /color \''+colours.value.mainPostMeanColour1D +
                      '\' /scale '+str(colours.value.mainPostMeanMarkerScale)+' \\\n')
      # Plot reference point
      if plotRef:
          outfile.write(refString)
      # Draw key
      outfile.write(keyString)
      # Write credits
      if blame.value is not None:
        blameYCoordinate = str(
            blameFractionalVerticalOffset * yRange + ytrema[1])
        outfile.write('  --draw-text '+str(xtrema[1])+','+blameYCoordinate +
                      ' \''+blame.value+'\' /scale 0.5 /justification right\\\n')
      # Add logo
      if logoFile.value is not None:
        outfile.write(
            '  --draw-text '+str(logoCoords[0])+','+str(logoCoords[1])+' '+logoString+'\\\n')
      # Set axis colours
      for x in ['top', 'bottom', 'left', 'right']:
        outfile.write('  --axis-style '+x+' /stroke_color \'' +
                      colours.value.axisColour1D+'\'\\\n')
      outfile.close
      subprocess.call('chmod +x '+currentBase+'_post1D.bsh', shell=True)

    # Make profile-posterior comparison plotting scripts
    if doProfile.value and doPosterior.value:

      bestFitData = [colours.value.mainBestFitMarker, colours.value.mainBestFitColour1D,
                     colours.value.mainBestFitMarkerScale, colours.value.mainProfColour1D]
      postMeanData = [colours.value.mainPostMeanMarker, colours.value.mainPostMeanColour1D,
                      colours.value.mainPostMeanMarkerScale, colours.value.mainPostColour1D]

      # Work out which is the main and which is the comparison
      if PosteriorIsMainInComboPlot:
        [main, sec] = ['post', 'like']
        [mainData, secData] = [postMeanData, bestFitData]
      else:
        [main, sec] = ['like', 'post']
        [mainData, secData] = [bestFitData, postMeanData]

      # Get contours
      if contours1D.value is not None:
        mainContourLevels = getContours(dirs.parseFilename, plot, main)
        secContourLevels = getContours(dirs.parseFilename, plot, sec)

      # Determine keys
      keyString = ''
      if doKey1D.value is not None and plot in doKey1D.value:
        markers = []
        # Get details of key for reference point
        if plotRef:
            markers.append([colours.value.referenceMarkerOuter, colours.value.referenceMarkerOuterColour,
                            colours.value.referenceMarkerOuterScale, refText, colours.value.referenceMarkerInner,
                            colours.value.referenceMarkerInnerColour, colours.value.referenceMarkerInnerScale /
                            colours.value.referenceMarkerOuterScale])
        # Get details of key for posterior mean
        markers.append(
            [postMeanData[0], postMeanData[1], postMeanData[2], 'Mean'])
        # Get details of key for best fit
        markers.append([bestFitData[0], bestFitData[1],
                        bestFitData[2], 'Best fit'])
        # Reverse vertical ordering if keys are to be placed at the top of the page, so as to fill from the top down
        if keyLoc[0] == 't':
            markers.reverse()
        # Construct ctioga2 command for each key
        for i, key in enumerate(markers):
          if key[0] == 'Bullet' or key[0] == 'BulletOpen':
              key[2] /= 1.5
          if key[2] > 1.0:
              key[2] = 1.0
          # Write the extra marker overlay for the reference point
          if len(key) == 7:
              keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[4]+' /color \'' +\
                  key[5]+'\' /scale '+str(key[6]*key[2])+'\\\n'
          # Write the main marker
          keyString += '  --draw-marker '+str(xVals[0])+','+str(
              yVals[i])+' '+key[0]+' /color \''+key[1]+'\' /scale '+str(key[2])+'\\\n'
          # Write the key text
          keyString += '  --draw-text ' + \
              str(xVals[1])+','+str(yVals[i])+' \''+key[3] + \
              '\'  /color \''+colours.value.keyTextColour1D
          keyString += '\' /justification left /scale 0.75 /alignment center \\\n'

      # Open plotting shell script file for writing
      outfile = smart_open(currentBase+'_combo1D.bsh', 'w')
      outfile.write('#!/usr/bin/env bash\n')
      outfile.write('# This plot script created by pippi '+pippiVersion +
                    ' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('ctioga2\\\n')
      outfile.write('  --name '+currentBaseMinimal+'_combo1D')
      outfile.write('  --plot-scale \''+str(plot_scale)+'\'\\\n')
      outfile.write('  --page-size \''+plotSizeInternal+'\'\\\n')
      outfile.write('  --frame-margins '+str(left_margin)+','
                                        + str(right_margin)+','
                                        + str(top_margin)+','
                                        + str(bottom_margin)+'\\\n')
      outfile.write('  --xrange '+str(xtrema[0])+':'+str(xtrema[1])+'\\\n')
      outfile.write('  --yrange 0:1\\\n')
      outfile.write(
          '  --ylabel \'Relative probability $P/P_\mathrm{max}$\' /shift 2.1\\\n')
      outfile.write('  --xlabel \''+labels.value[plot]+'\'\\\n')
      outfile.write(
          '  --label-style x /scale 1.0 /shift 0.15 --label-style y /scale 1.0 /shift 0.15')
      if yAxisAngle.value is not None:
          outfile.write(' /angle '+str(yAxisAngle.value))
      outfile.write('\\\n')
      if contours1D is not None:
        if main == 'like':
          main_colour = colours.value.mainProfColour1D
          main_text = 'CL'
          sec_colour = colours.value.mainPostColour1D
          sec_text = 'CR'
        else:
          main_colour = colours.value.mainPostColour1D
          main_text = 'CR'
          sec_colour = colours.value.mainProfColour1D
          sec_text = 'CL'
        for i, contour in enumerate(mainContourLevels):
          outfile.write('  --draw-line '+str(xtrema[0])+','+contour+' '+str(xtrema[1])+','+contour+' /color \''+main_colour +
                        '\' /style Dashes /width '+str(float(colours.value.lineWidth1D)*0.5)+'\\\n')
          outfile.write('  --draw-text '+str(xtrema[0]+0.045*(xtrema[1]-xtrema[0]))+','+str(float(contour)+0.005)+' \''+str(contours1D.value[i]) +
                        '\%'+main_text+'\' /color \''+main_colour+'\' /scale 0.5 /justification left /alignment bottom\\\n')
        for i, contour in enumerate(secContourLevels):
          outfile.write('  --draw-line '+str(xtrema[0])+','+contour+' '+str(xtrema[1])+','+contour+' /color \''+sec_colour +
                        '\' /style Dashes /width '+str(float(colours.value.lineWidth1D)*0.5)+'\\\n')
          outfile.write('  --draw-text '+str(xtrema[0]+0.045*(xtrema[1]-xtrema[0]))+','+str(float(contour)+0.005)+' \''+str(contours1D.value[i]) +
                        '\%'+sec_text+'\' /color \''+sec_colour+'\' /scale 0.5 /justification left /alignment bottom\\\n')
      # Plot comparison distribution
      outfile.write('  --plot '+currentParse+'_'+sec+'1D'+histString+'.ct2@1:2 /fill xaxis /fill-transparency '+colours.value.fillTransparency1D +
                    ' /fill-color '+secData[3]+' /color '+secData[3] +
                    ' /line-style '+colours.value.comparison1DLineStyle+' /line-width '+colours.value.lineWidth1D+'\\\n')
      # Plot main distribution
      outfile.write('  --plot '+currentParse+'_'+main+'1D'+histString+'.ct2@1:2 /fill xaxis /fill-transparency '+colours.value.fillTransparency1D +
                    ' /fill-color '+mainData[3]+' /color '+mainData[3] +
                    ' /line-style '+colours.value.main1DLineStyle+' /line-width '+colours.value.lineWidth1D+'\\\n')
      if doLegend1D.value is not None and plot in doLegend1D.value:
        # Write legend
        try:
          legendLocation = legendLoc1D.value[plot]
        except (KeyError, TypeError):
          legendLocation = defaultLegendLocation
        outfile.write('  --legend-inside \''+legendLocation +
                      '\' /scale 1.0 /vpadding 0.1\\\n')
        if legendLines.value is not None:
          for x in legendLines.value:
              outfile.write('  --legend-line \''+x+'\' /color \'' +
                            colours.value.legendTextColour1D+'\'\\\n')
        outfile.write('  --legend-line \'Like vs. Posterior\' /color \'' +
                      colours.value.legendTextColour1D+'\'\\\n')
      # Get best-fit point
      bestFit = getCentralVal(dirs.parseFilename, plot, 'like', lookupKeys)
      # Get posterior mean
      postMean = getCentralVal(dirs.parseFilename, plot, 'post', lookupKeys)
      # Always plot both best fit and posterior mean on comparison plot
      outfile.write('  --draw-marker '+str(bestFit)+','+str(yRange*bestFitData[2]/40.0)+' '+bestFitData[0]+' /color \''+bestFitData[1] +
                    '\' /scale '+str(bestFitData[2])+' \\\n')
      if postMean:
          outfile.write('  --draw-marker '+str(postMean)+','+str(yRange*postMeanData[2]/40.0)+' '+postMeanData[0]+' /color \''+postMeanData[1] +
                        '\' /scale '+str(postMeanData[2])+' \\\n')
      # Plot reference point
      if plotRef:
          outfile.write(refString)
      # Draw key
      outfile.write(keyString)
      # Write credits
      if blame.value is not None:
        blameYCoordinate = str(
            blameFractionalVerticalOffset * yRange + ytrema[1])
        outfile.write('  --draw-text '+str(xtrema[1])+','+blameYCoordinate +
                      ' \''+blame.value+'\' /scale 0.5 /justification right\\\n')
      # Add logo
      if logoFile.value is not None:
        outfile.write(
            '  --draw-text '+str(logoCoords[0])+','+str(logoCoords[1])+' '+logoString+'\\\n')
      # Set axis colours
      for x in ['top', 'bottom', 'left', 'right']:
        outfile.write('  --axis-style '+x+' /stroke_color \'' +
                      colours.value.axisColour1D+'\'\\\n')
      outfile.close
      subprocess.call('chmod +x '+currentBase+'_combo1D.bsh', shell=True)


def scriptTwoDplots(dirs):

  # Loop over requested plots
  for plot in twoDplots.value:

    print('    Writing scripts for 2D plots of quantities ', plot)

    # Set up filenames
    currentBase = dirs.baseScriptFilename+'_'+'_'.join([str(x) for x in plot])
    currentParse = dirs.parseFilenameFromScriptFiledir + \
        '_'+'_'.join([str(x) for x in plot])
    currentBaseMinimal = re.sub(r'.*/', '', currentBase)
    if doComparison.value:
        currentSecParse = dirs.secParseFilenameFromScriptFiledir + \
            '_'+'_'.join([str(x) for x in plot])

    # Get plot limits
    xtrema = dictFallback(axisRanges, dataRanges, plot[0])
    ytrema = dictFallback(axisRanges, dataRanges, plot[1])
    xRange = xtrema[1] - xtrema[0]
    yRange = ytrema[1] - ytrema[0]

    # Locate and scale logo (if any)
    if logoFile.value is not None:
      logoCoords = [xtrema[0]+logoLoc.value[0][0] *
                    xRange, ytrema[0]+logoLoc.value[0][1]*yRange]
      logoString = '\'\\includegraphics[width = ' + \
          str(logoWidth.value*8.8)+'cm]{'+logoFile.value+'}\''

    # Determine reference point
    if refPoint.value is not None and all([x in refPoint.value for x in plot]):
      plotRef = True
      refString = '  --draw-marker '+str(refPoint.value[plot[0]])+','+str(refPoint.value[plot[1]])+' ' +\
          colours.value.referenceMarkerInner+' /color \''+colours.value.referenceMarkerInnerColour +\
          '\' /scale '+str(colours.value.referenceMarkerInnerScale)+' \\\n' +\
                  '  --draw-marker '+str(refPoint.value[plot[0]])+','+str(refPoint.value[plot[1]])+' ' +\
          colours.value.referenceMarkerOuter+' /color \''+colours.value.referenceMarkerOuterColour +\
          '\' /scale ' + \
          str(colours.value.referenceMarkerOuterScale)+' \\\n'
    else:
      plotRef = False

    # Determine plot size
    if plotSize.value is None or plotSize.value is '':
      if doColourbar.value is not None and plot in doColourbar.value:
        plotSizeInternal = '12.5cm x 4in'
      else:
        plotSizeInternal = '11cm x 4in'
    else:
        plotSizeInternal = plotSize.value

    # Make profile likelihood plotting scripts
    if doProfile.value:

      # Get contours
      if contours2D.value is not None:
        contourLevels = getContours(dirs.parseFilename, plot, 'like')

      # Determine keys
      keyString = ''
      if doKey2D.value is not None and plot in doKey2D.value:
        # Get gross key location
        try:
          keyLoc = keyLoc2D.value[plot[0]][plot[1]]
        except (KeyError, TypeError):
          keyLoc = defaultKeyLocation
        # Get text to be used for reference point
        refText = defaultRefKey if refKey.value is None else refKey.value
        # Get x and y coordinates for 3 possible keys (for markers and text)
        yVals = ytrema[0] + np.array(keyYVals[keyLoc[0]])*yRange
        xVals = xtrema[0] + np.array(keyXVals[keyLoc[1]])*xRange
        markers = []
        # Get details of key for reference point
        if plotRef:
            markers.append([colours.value.referenceMarkerOuter,
                            colours.value.referenceMarkerOuterColour,
                            colours.value.referenceMarkerOuterColour,
                            colours.value.referenceMarkerOuterScale,
                            refText,
                            colours.value.referenceMarkerInner,
                            colours.value.referenceMarkerInnerColour,
                            colours.value.referenceMarkerInnerScale/colours.value.referenceMarkerOuterScale])
        # Get details of key for posterior mean
        if postMeanOnProf.value:
            markers.append([colours.value.mainPostMeanMarker,
                            colours.value.mainPostMeanColour2D,
                            colours.value.mainPostMeanColourOutline2D,
                            colours.value.mainPostMeanMarkerScale,
                            'Mean'])
        # Get details of key for best fit
        if bestFitOnProf.value:
            markers.append([colours.value.mainBestFitMarker,
                            colours.value.mainBestFitColour2D,
                            colours.value.mainBestFitColourOutline2D,
                            colours.value.mainBestFitMarkerScale,
                            'Best fit'])
        # Reverse vertical ordering if keys are to be placed at the top of the page, so as to fill from the top down
        if keyLoc[0] == 't':
            markers.reverse()
        # Construct ctioga2 command for each key
        for i, key in enumerate(markers):
          if key[0] == 'Bullet' or key[0] == 'BulletOpen':
              key[3] /= 1.5
          if key[3] > 1.0:
              key[3] = 1.0
          # Write the extra marker overlay for the reference point
          if len(key) == 8:
              keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[5]+' /color \'' +\
                  key[6]+'\' /scale '+str(key[7]*key[3])+'\\\n'
          # Write the main marker
          keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[0]+' /fill-color \''+str(
              key[1])+'\' /stroke-color \''+str(key[2])+'\' /scale '+str(key[3])+'\\\n'
          # Write the key text
          keyString += '  --draw-text ' + \
              str(xVals[1])+','+str(yVals[i])+' \''+key[4] + \
              '\'  /color \''+colours.value.keyTextColour2D
          keyString += '\' /justification left /scale 0.75 /alignment center \\\n'

      # Open plotting shell script file for writing
      outfile = smart_open(currentBase+'_like2D.bsh', 'w')
      outfile.write('#!/usr/bin/env bash\n')
      outfile.write('# This plot script created by pippi '+pippiVersion +
                    ' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('ctioga2\\\n')
      outfile.write('  --name '+currentBaseMinimal+'_like2D')
      outfile.write('  --plot-scale \''+str(plot_scale)+'\'\\\n')
      outfile.write('  --page-size \''+plotSizeInternal+'\'\\\n')
      if doColourbar.value is not None and plot in doColourbar.value:
        outfile.write('  --frame-margins '+str(left_margin+0.03)+','
                                          + str(right_margin+0.15)+','
                                          + str(top_margin)+','
                                          + str(bottom_margin)+'\\\n')
      else:
        outfile.write('  --frame-margins '+str(left_margin+0.05)+','
                                          + str(right_margin+0.02)+','
                                          + str(top_margin)+','
                                          + str(bottom_margin)+'\\\n')
      outfile.write('  --xrange '+str(xtrema[0])+':'+str(xtrema[1])+'\\\n')
      outfile.write('  --yrange '+str(ytrema[0])+':'+str(ytrema[1])+'\\\n')
      outfile.write('  --ylabel \'' +
                    labels.value[plot[1]]+'\' /shift 2.9\\\n')
      outfile.write('  --xlabel \''+labels.value[plot[0]]+'\'\\\n')
      outfile.write(
          '  --label-style x /scale 1.0 /shift 0.15 --label-style y /scale 1.0 /shift 0.75')
      if yAxisAngle.value is not None:
          outfile.write(' /angle '+str(yAxisAngle.value))
      outfile.write("  /valign 'midheight'")
      outfile.write('\\\n  --xyz-map\\\n')
      if doColourbar.value is not None and plot in doColourbar.value:
        outfile.write(
            '  --new-zaxis zvalues /location right /bar_size \'0.5cm\'\\\n')
        outfile.write(
            "  --label-style zvalues /angle 270 /shift 0.4 /valign 'midheight'\\\n")
      outfile.write('  --plot '+currentParse+'_like2D.ct2@1:2:3 ')
      if doColourbar.value is not None and plot in doColourbar.value:
          outfile.write('/zaxis zvalues ')
      outfile.write('/color-map \'' +
                    colours.value.colourMap(contourLevels, 'like')+'\'\\\n')
      if doComparison.value:
        # Do everything for comparison chain
        if contours2D.value is not None:
          # Plot contours
          outfile.write('  --plot '+currentSecParse +
                        '_like2D.ct2@1:2:3 /fill-transparency 1\\\n')
          for contour in contourLevels:
            outfile.write('  --draw-contour '+contour+' /color '+colours.value.comparisonProfContourColour2D +
                          ' /style '+colours.value.comparisonContourStyle+' /width '+colours.value.lineWidth2D+'\\\n')
        if bestFitOnProf.value and colours.value.comparisonBestFitMarker is not None:
          # Get best-fit point and plot it
          bestFit = getCentralVal(
              dirs.secParseFilename, plot, 'like', lookupKeys)
          outfile.write('  --draw-marker '+str(bestFit[0])+','+str(bestFit[1])+' ' +
                        colours.value.comparisonBestFitMarker+' /color \''+colours.value.comparisonBestFitColour +
                        '\' /scale '+str(colours.value.comparisonBestFitMarkerScale)+' \\\n')
        if postMeanOnProf.value and colours.value.comparisonPostMeanMarker is not None:
          # Get posterior mean and plot it
          postMean = getCentralVal(
              dirs.secParseFilename, plot, 'post', lookupKeys)
          if not postMean:
              sys.exit(
                  'Error: plot_posterior_mean_on_profile_like = T but no multiplicity given!')
          outfile.write('  --draw-marker '+str(postMean[0])+','+str(postMean[1])+' ' +
                        colours.value.comparisonPostMeanMarker+' /color \''+colours.value.comparisonPostMeanColour +
                        '\' /scale '+str(colours.value.comparisonPostMeanMarkerScale)+' \\\n')
      outfile.write('  --plot '+currentParse +
                    '_like2D.ct2@1:2:3 /fill-transparency 1\\\n')
      if contours2D.value is not None:
        # Plot contours
        for contour in contourLevels:
          outfile.write('  --draw-contour '+contour+' /color '+colours.value.mainProfContourColour2D +
                        ' /style '+colours.value.mainContourStyle+' /width '+colours.value.lineWidth2D+'\\\n')
      if doLegend2D.value is not None and plot in doLegend2D.value:
        # Write legend
        try:
          legendLocation = legendLoc2D.value[plot[0]][plot[1]]
        except (KeyError, TypeError):
          legendLocation = defaultLegendLocation
        outfile.write('  --legend-inside \''+legendLocation +
                      '\' /scale 1.0 /vpadding 0.1\\\n')
        if legendLines.value is not None:
          for x in legendLines.value:
              outfile.write('  --legend-line \''+x+'\' /color \'' +
                            colours.value.legendTextColour2D+'\'\\\n')
        outfile.write('  --legend-line \'Prof.~likelihood\' /color \'' +
                      colours.value.legendTextColour2D+'\'\\\n')
      if bestFitOnProf.value:
        # Get best-fit point and plot it
        bestFit = getCentralVal(dirs.parseFilename, plot, 'like', lookupKeys)
        outfile.write('  --draw-marker '+str(bestFit[0])+','+str(bestFit[1])+' ' +
                      colours.value.mainBestFitMarker+' /fill-color \''+str(colours.value.mainBestFitColour2D)+'\' /stroke-color \''+str(colours.value.mainBestFitColourOutline2D) +
                      '\' /scale '+str(colours.value.mainBestFitMarkerScale)+' \\\n')
      if postMeanOnProf.value:
        # Get posterior mean and plot it
        postMean = getCentralVal(dirs.parseFilename, plot, 'post', lookupKeys)
        if not postMean:
            sys.exit(
                'Error: plot_posterior_mean_on_profile_like = T but no multiplicity given!')
        outfile.write('  --draw-marker '+str(postMean[0])+','+str(postMean[1])+' ' +
                      colours.value.mainPostMeanMarker+' /fill-color \''+str(colours.value.mainPostMeanColour2D)+'\' /stroke-color \''+str(colours.value.mainPostMeanColourOutline2D) +
                      '\' /scale '+str(colours.value.mainPostMeanMarkerScale)+' \\\n')
      # Plot reference point
      if plotRef:
          outfile.write(refString)
      # Draw key
      outfile.write(keyString)
      # Write credits
      if blame.value is not None:
        blameYCoordinate = str(
            blameFractionalVerticalOffset * yRange + ytrema[1])
        outfile.write('  --draw-text '+str(xtrema[1])+','+blameYCoordinate +
                      ' \''+blame.value+'\' /scale 0.5 /justification right\\\n')
      # Add logo
      if logoFile.value is not None:
        outfile.write(
            '  --draw-text '+str(logoCoords[0])+','+str(logoCoords[1])+' '+logoString+'\\\n')
      # Set axis colours
      for x in ['top', 'bottom', 'left', 'right']:
        outfile.write('  --axis-style '+x+' /stroke_color \'' +
                      colours.value.axisColour2D+'\'\\\n')
      if doColourbar.value is not None and plot in doColourbar.value:
        # Do labelling for colourbar
        outfile.write('  --y2 --plot '+currentParse +
                      '_like2D.ct2@1:2:3 /fill-transparency 1\\\n')
        outfile.write('  --axis-style y /decoration ticks --yrange ' +
                      str(ytrema[0])+':'+str(ytrema[1])+'\\\n')
        outfile.write('  --ylabel \''+likeColourbarString +
                      '\' /shift 3.5 /angle 180 /scale 0.8\\\n')
      outfile.close
      subprocess.call('chmod +x '+currentBase+'_like2D.bsh', shell=True)

    # Make posterior pdf plotting scripts
    if doPosterior.value:

      # Get contours
      if contours2D.value is not None:
        mainContourLevels = getContours(dirs.parseFilename, plot, 'post')
        if doComparison.value:
            secContourLevels = getContours(dirs.secParseFilename, plot, 'post')

      # Determine keys
      keyString = ''
      if doKey2D.value is not None and plot in doKey2D.value:
        # Get gross key location
        try:
          keyLoc = keyLoc2D.value[plot[0]][plot[1]]
        except (KeyError, TypeError):
          keyLoc = defaultKeyLocation
        # Get text to be used for reference point
        refText = defaultRefKey if refKey.value is None else refKey.value
        # Get x and y coordinates for 3 possible keys (for markers and text)
        yVals = ytrema[0] + np.array(keyYVals[keyLoc[0]])*yRange
        xVals = xtrema[0] + np.array(keyXVals[keyLoc[1]])*xRange
        markers = []
        # Get details of key for reference point
        if plotRef:
            markers.append([colours.value.referenceMarkerOuter,
                            colours.value.referenceMarkerOuterColour,
                            colours.value.referenceMarkerOuterColour,
                            colours.value.referenceMarkerOuterScale,
                            refText,
                            colours.value.referenceMarkerInner,
                            colours.value.referenceMarkerInnerColour,
                            colours.value.referenceMarkerInnerScale/colours.value.referenceMarkerOuterScale])
        # Get details of key for posterior mean
        if postMeanOnPost.value:
            markers.append([colours.value.mainPostMeanMarker,
                            colours.value.mainPostMeanColour2D,
                            colours.value.mainPostMeanColourOutline2D,
                            colours.value.mainPostMeanMarkerScale,
                            'Mean'])
        # Get details of key for best fit
        if bestFitOnPost.value:
            markers.append([colours.value.mainBestFitMarker,
                            colours.value.mainBestFitColour2D,
                            colours.value.mainBestFitColourOutline2D,
                            colours.value.mainBestFitMarkerScale,
                            'Best fit'])
        # Reverse vertical ordering if keys are to be placed at the top of the page, so as to fill from the top down
        if keyLoc[0] == 't':
            markers.reverse()
        # Construct ctioga2 command for each key
        for i, key in enumerate(markers):
          if key[0] == 'Bullet' or key[0] == 'BulletOpen':
              key[3] /= 1.5
          if key[3] > 1.0:
              key[3] = 1.0
          # Write the extra marker overlay for the reference point
          if len(key) == 8:
              keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[5]+' /color \'' +\
                  key[6]+'\' /scale '+str(key[7]*key[3])+'\\\n'
          # Write the main marker
          keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[0]+' /fill-color \''+str(
              key[1])+'\' /stroke-color \''+str(key[2])+'\' /scale '+str(key[3])+'\\\n'
          # Write the key text
          keyString += '  --draw-text ' + \
              str(xVals[1])+','+str(yVals[i])+' \''+key[4] + \
              '\'  /color \''+colours.value.keyTextColour2D
          keyString += '\' /justification left /scale 0.75 /alignment center \\\n'

      # Open plotting shell script file for writing
      outfile = smart_open(currentBase+'_post2D.bsh', 'w')
      outfile.write('#!/usr/bin/env bash\n')
      outfile.write('# This plot script created by pippi '+pippiVersion +
                    ' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('ctioga2\\\n')
      outfile.write('  --name '+currentBaseMinimal+'_post2D')
      outfile.write('  --plot-scale \''+str(plot_scale)+'\'\\\n')
      outfile.write('  --page-size \''+plotSizeInternal+'\'\\\n')
      if doColourbar.value is not None and plot in doColourbar.value:
        outfile.write('  --frame-margins '+str(left_margin+0.03)+','
                                          + str(right_margin+0.15)+','
                                          + str(top_margin)+','
                                          + str(bottom_margin)+'\\\n')
      else:
        outfile.write('  --frame-margins '+str(left_margin+0.05)+','
                                          + str(right_margin+0.02)+','
                                          + str(top_margin)+','
                                          + str(bottom_margin)+'\\\n')
      outfile.write('  --xrange '+str(xtrema[0])+':'+str(xtrema[1])+'\\\n')
      outfile.write('  --yrange '+str(ytrema[0])+':'+str(ytrema[1])+'\\\n')
      outfile.write('  --ylabel \'' +
                    labels.value[plot[1]]+'\' /shift 2.9\\\n')
      outfile.write('  --xlabel \''+labels.value[plot[0]]+'\'\\\n')
      outfile.write(
          '  --label-style x /scale 1.0 /shift 0.15 --label-style y /scale 1.0 /shift 0.75')
      if yAxisAngle.value is not None:
          outfile.write(' /angle '+str(yAxisAngle.value))
      outfile.write("  /valign 'midheight'")
      outfile.write('\\\n  --xyz-map\\\n')
      if doColourbar.value is not None and plot in doColourbar.value:
        outfile.write(
            '  --new-zaxis zvalues /location right /bar_size \'0.5cm\'\\\n')
        outfile.write(
            "  --label-style zvalues /angle 270 /shift 0.4  /valign 'midheight'\\\n")
      outfile.write('  --plot '+currentParse+'_post2D.ct2@1:2:3 ')
      if doColourbar.value is not None and plot in doColourbar.value:
          outfile.write('/zaxis zvalues ')
      outfile.write(
          '/color-map \''+colours.value.colourMap(mainContourLevels, 'post')+'\'\\\n')
      if doComparison.value:
        # Do everything for comparison chain
        if contours2D.value is not None:
          # Plot contours
          outfile.write('  --plot '+currentSecParse +
                        '_post2D.ct2@1:2:3 /fill-transparency 1\\\n')
          for contour in secContourLevels:
            outfile.write('  --draw-contour '+contour+' /color '+colours.value.comparisonPostContourColour2D +
                          ' /style '+colours.value.comparisonContourStyle+' /width '+colours.value.lineWidth2D+'\\\n')
        if bestFitOnPost.value and colours.value.comparisonBestFitMarker is not None:
          # Get best-fit point and plot it
          bestFit = getCentralVal(dirs.secParseFilename, plot, 'like', lookupKeys)
          outfile.write('  --draw-marker '+str(bestFit[0])+','+str(bestFit[1])+' ' +
                        colours.value.comparisonBestFitMarker+' /color \''+colours.value.comparisonBestFitColour +
                        '\' /scale '+str(colours.value.comparisonBestFitMarkerScale)+' \\\n')
        if postMeanOnPost.value and colours.value.comparisonPostMeanMarker is not None:
          # Get posterior mean and plot it
          postMean = getCentralVal(
              dirs.secParseFilename, plot, 'post', lookupKeys)
          outfile.write('  --draw-marker '+str(postMean[0])+','+str(postMean[1])+' ' +
                        colours.value.comparisonPostMeanMarker+' /color \''+colours.value.comparisonPostMeanColour +
                        '\' /scale '+str(colours.value.comparisonPostMeanMarkerScale)+' \\\n')
      outfile.write('  --plot '+currentParse +
                    '_post2D.ct2@1:2:3 /fill-transparency 1\\\n')
      if contours2D.value is not None:
        # Plot contours
        for contour in mainContourLevels:
          outfile.write('  --draw-contour '+contour+' /color '+colours.value.mainPostContourColour2D +
                        ' /style '+colours.value.mainContourStyle+' /width '+colours.value.lineWidth2D+'\\\n')
      if doLegend2D.value is not None and plot in doLegend2D.value:
        # Write legend
        try:
          legendLocation = legendLoc2D.value[plot[0]][plot[1]]
        except (KeyError, TypeError):
          legendLocation = defaultLegendLocation
        outfile.write('  --legend-inside \''+legendLocation +
                      '\' /scale 1.0 /vpadding 0.1\\\n')
        if legendLines.value is not None:
          for x in legendLines.value:
              outfile.write('  --legend-line \''+x+'\' /color \'' +
                            colours.value.legendTextColour2D+'\'\\\n')
        outfile.write('  --legend-line \'Marg.~posterior\' /color \'' +
                      colours.value.legendTextColour2D+'\'\\\n')
      if bestFitOnPost.value:
        # Get best-fit point and plot it
        bestFit = getCentralVal(dirs.parseFilename, plot, 'like', lookupKeys)
        outfile.write('  --draw-marker '+str(bestFit[0])+','+str(bestFit[1])+' ' +
                      colours.value.mainBestFitMarker+' /fill-color \''+str(colours.value.mainBestFitColour2D)+'\' /stroke-color \''+str(colours.value.mainBestFitColourOutline2D) +
                      '\' /scale '+str(colours.value.mainBestFitMarkerScale)+' \\\n')
      if postMeanOnPost.value:
        # Get posterior mean and plot it
        postMean = getCentralVal(dirs.parseFilename, plot, 'post', lookupKeys)
        outfile.write('  --draw-marker '+str(postMean[0])+','+str(postMean[1])+' ' +
                      colours.value.mainPostMeanMarker+' /fill-color \''+str(colours.value.mainPostMeanColour2D)+'\' /stroke-color \''+str(colours.value.mainPostMeanColourOutline2D) +
                      '\' /scale '+str(colours.value.mainPostMeanMarkerScale)+' \\\n')
      # Plot reference point
      if plotRef:
          outfile.write(refString)
      # Draw key
      outfile.write(keyString)
      # Write credits
      if blame.value is not None:
        blameYCoordinate = str(
            blameFractionalVerticalOffset * yRange + ytrema[1])
        outfile.write('  --draw-text '+str(xtrema[1])+','+blameYCoordinate +
                      ' \''+blame.value+'\' /scale 0.5 /justification right\\\n')
      # Add logo
      if logoFile.value is not None:
        outfile.write(
            '  --draw-text '+str(logoCoords[0])+','+str(logoCoords[1])+' '+logoString+'\\\n')
      # Set axis colours
      for x in ['top', 'bottom', 'left', 'right']:
        outfile.write('  --axis-style '+x+' /stroke_color \'' +
                      colours.value.axisColour2D+'\'\\\n')
      if doColourbar.value is not None and plot in doColourbar.value:
        # Do labelling for colourbar
        outfile.write('  --y2 --plot '+currentParse +
                      '_post2D.ct2@1:2:3 /fill-transparency 1\\\n')
        outfile.write('  --axis-style y /decoration ticks --yrange ' +
                      str(ytrema[0])+':'+str(ytrema[1])+'\\\n')
        outfile.write('  --ylabel \''+postColourbarString +
                      '\' /shift 3.5 /angle 180 /scale 0.8\\\n')
      outfile.close
      subprocess.call('chmod +x '+currentBase+'_post2D.bsh', shell=True)

    # Make observable plotting scripts

    #if doObservable.value:
    if obsPlots.value is not None:
        for column in obsPlots.value:

          # Get contours
          if contours2D.value is not None:
            contourLevelsLike = getContours(dirs.parseFilename, plot, 'like')
          contourLevelsObs = getContours_obs(dirs.parseFilename, plot, column)
          # Determine keys
          keyString = ''
          if doKey2D.value is not None and plot in doKey2D.value:
            # Get gross key location
            try:
              keyLoc = keyLoc2D.value[plot[0]][plot[1]]
            except (KeyError, TypeError):
              keyLoc = defaultKeyLocation
            # Get text to be used for reference point
            refText = defaultRefKey if refKey.value is None else refKey.value
            # Get x and y coordinates for 3 possible keys (for markers and text)
            yVals = ytrema[0] + np.array(keyYVals[keyLoc[0]])*yRange
            xVals = xtrema[0] + np.array(keyXVals[keyLoc[1]])*xRange
            markers = []
            # Get details of key for reference point
            if plotRef:
                markers.append([colours.value.referenceMarkerOuter,
                                colours.value.referenceMarkerOuterColour,
                                colours.value.referenceMarkerOuterColour,
                                colours.value.referenceMarkerOuterScale,
                                refText,
                                colours.value.referenceMarkerInner,
                                colours.value.referenceMarkerInnerColour,
                                colours.value.referenceMarkerInnerScale/colours.value.referenceMarkerOuterScale])
            # Get details of key for posterior mean
            if postMeanOnProf.value:
                markers.append([colours.value.mainPostMeanMarker,
                                colours.value.mainPostMeanColour2D,
                                colours.value.mainPostMeanColourOutline2D,
                                colours.value.mainPostMeanMarkerScale,
                                'Mean'])
            # Get details of key for best fit
            if bestFitOnProf.value:
                markers.append([colours.value.mainBestFitMarker,
                                colours.value.mainBestFitColour2D,
                                colours.value.mainBestFitColourOutline2D,
                                colours.value.mainBestFitMarkerScale,
                                'Best fit'])
            # Reverse vertical ordering if keys are to be placed at the top of the page, so as to fill from the top down
            if keyLoc[0] == 't':
                markers.reverse()
            # Construct ctioga2 command for each key
            for i, key in enumerate(markers):
              if key[0] == 'Bullet' or key[0] == 'BulletOpen':
                  key[3] /= 1.5
              if key[3] > 1.0:
                  key[3] = 1.0
              # Write the extra marker overlay for the reference point
              if len(key) == 8:
                  keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[5]+' /color \'' +\
                      key[6]+'\' /scale '+str(key[7]*key[3])+'\\\n'
              # Write the main marker
              keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[0]+' /fill-color \''+str(
                  key[1])+'\' /stroke-color \''+str(key[2])+'\' /scale '+str(key[3])+'\\\n'
              # Write the key text
              keyString += '  --draw-text ' + \
                  str(xVals[1])+','+str(yVals[i])+' \''+key[4] + \
                  '\'  /color \''+colours.value.keyTextColour2D
              keyString += '\' /justification left /scale 0.75 /alignment center \\\n'

          # Open plotting shell script file for writing
          outfile = smart_open(currentBase+'_obs2D_'+str(column)+'.bsh', 'w')
          outfile.write('#!/usr/bin/env bash\n')
          outfile.write('# This plot script created by pippi '+pippiVersion +
                        ' on '+datetime.datetime.now().strftime('%c')+'\n')
          outfile.write('ctioga2\\\n')
          outfile.write('  --name '+currentBaseMinimal+'_obs2D_'+str(column))
          outfile.write('  --plot-scale \''+str(plot_scale)+'\'\\\n')
          outfile.write('  --page-size \''+plotSizeInternal+'\'\\\n')
          if doColourbar.value is not None and plot in doColourbar.value:
            outfile.write('  --frame-margins '+str(left_margin+0.03)+','
                                              + str(right_margin+0.15)+','
                                              + str(top_margin)+','
                                              + str(bottom_margin)+'\\\n')
          else:
            outfile.write('  --frame-margins '+str(left_margin+0.05)+','
                                              + str(right_margin+0.02)+','
                                              + str(top_margin)+','
                                              + str(bottom_margin)+'\\\n')
          outfile.write(
              '  --xrange '+str(xtrema[0])+':'+str(xtrema[1])+'\\\n')
          outfile.write(
              '  --yrange '+str(ytrema[0])+':'+str(ytrema[1])+'\\\n')
          outfile.write('  --ylabel \'' +
                        labels.value[plot[1]]+'\' /shift 2.9\\\n')
          outfile.write('  --xlabel \''+labels.value[plot[0]]+'\'\\\n')
          outfile.write(
              '  --label-style x /scale 1.0 /shift 0.15 --label-style y /scale 1.0 /shift 0.75')
          if yAxisAngle.value is not None:
              outfile.write(' /angle '+str(yAxisAngle.value))
          outfile.write("  /valign 'midheight'")
          outfile.write('\\\n  --xyz-map\\\n')
          outfile.write('  --plot '+currentParse +
                        '_obs2D_'+str(column)+'.ct2@1:2:3 ')
          #if doColourbar.value is not None and plot in doColourbar.value: outfile.write('/zaxis zvalues ')
          outfile.write(
              '/color-map \''+colours.value.colourMap(contourLevelsObs, 'obs')+'\'\\\n')
          if doComparison.value:
            # Do everything for comparison chain
            if contours2D.value is not None:
              # Plot contours
              outfile.write('  --plot '+currentSecParse +
                            '_like2D.ct2@1:2:3 /fill-transparency 1\\\n')
              for contour in contourLevels:
                outfile.write('  --draw-contour '+contour+' /color '+colours.value.comparisonProfContourColour2D +
                              ' /style '+colours.value.comparisonContourStyle+' /width '+colours.value.lineWidth2D+'\\\n')
            if bestFitOnProf.value and colours.value.comparisonBestFitMarker is not None:
              # Get best-fit point and plot it
              bestFit = getCentralVal(
                  dirs.secParseFilename, plot, 'like', lookupKeys)
              outfile.write('  --draw-marker '+str(bestFit[0])+','+str(bestFit[1])+' ' +
                            colours.value.comparisonBestFitMarker+' /color \''+colours.value.comparisonBestFitColour +
                            '\' /scale '+str(colours.value.comparisonBestFitMarkerScale)+' \\\n')
            if postMeanOnProf.value and colours.value.comparisonPostMeanMarker is not None:
              # Get posterior mean and plot it
              postMean = getCentralVal(
                  dirs.secParseFilename, plot, 'post', lookupKeys)
              if not postMean:
                  sys.exit(
                      'Error: plot_posterior_mean_on_profile_like = T but no multiplicity given!')
              outfile.write('  --draw-marker '+str(postMean[0])+','+str(postMean[1])+' ' +
                            colours.value.comparisonPostMeanMarker+' /color \''+colours.value.comparisonPostMeanColour +
                            '\' /scale '+str(colours.value.comparisonPostMeanMarkerScale)+' \\\n')
          outfile.write('  --plot '+currentParse +
                        '_like2D.ct2@1:2:3 /fill-transparency 1\\\n')
          if contours2D.value is not None:
            # Plot contours
            for contour in contourLevelsLike:
              outfile.write('  --draw-contour '+contour+' /color '+colours.value.mainProfContourColour2D +
                            ' /style '+colours.value.mainContourStyle+' /width '+colours.value.lineWidth2D+'\\\n')
          if doLegend2D.value is not None and plot in doLegend2D.value:
            # Write legend
            try:
              legendLocation = legendLoc2D.value[plot[0]][plot[1]]
            except (KeyError, TypeError):
              legendLocation = defaultLegendLocation
            outfile.write('  --legend-inside \''+legendLocation +
                          '\' /scale 1.0 /vpadding 0.1\\\n')
            if legendLines.value is not None:
              for x in legendLines.value:
                  outfile.write('  --legend-line \''+x+'\' /color \'' +
                                colours.value.legendTextColour2D+'\'\\\n')
            outfile.write('  --legend-line \'Prof.~likelihood\' /color \'' +
                          colours.value.legendTextColour2D+'\'\\\n')
          if bestFitOnProf.value:
            # Get best-fit point and plot it
            bestFit = getCentralVal(
                dirs.parseFilename, plot, 'like', lookupKeys)
            outfile.write('  --draw-marker '+str(bestFit[0])+','+str(bestFit[1])+' ' +
                          colours.value.mainBestFitMarker+' /fill-color \''+str(colours.value.mainBestFitColour2D)+'\' /stroke-color \''+str(colours.value.mainBestFitColourOutline2D) +
                          '\' /scale '+str(colours.value.mainBestFitMarkerScale)+' \\\n')
          if postMeanOnProf.value:
            # Get posterior mean and plot it
            postMean = getCentralVal(
                dirs.parseFilename, plot, 'post', lookupKeys)
            if not postMean:
                sys.exit(
                    'Error: plot_posterior_mean_on_profile_like = T but no multiplicity given!')
            outfile.write('  --draw-marker '+str(postMean[0])+','+str(postMean[1])+' ' +
                          colours.value.mainPostMeanMarker+' /fill-color \''+str(colours.value.mainPostMeanColour2D)+'\' /stroke-color \''+str(colours.value.mainPostMeanColourOutline2D) +
                          '\' /scale '+str(colours.value.mainPostMeanMarkerScale)+' \\\n')
          # Plot reference point
          if plotRef:
              outfile.write(refString)
          # Draw key
          outfile.write(keyString)
          # Write credits
          if blame.value is not None:
            blameYCoordinate = str(
                blameFractionalVerticalOffset * yRange + ytrema[1])
            outfile.write('  --draw-text '+str(xtrema[1])+','+blameYCoordinate +
                          ' \''+blame.value+'\' /scale 0.5 /justification right\\\n')
          # Add logo
          if logoFile.value is not None:
            outfile.write(
                '  --draw-text '+str(logoCoords[0])+','+str(logoCoords[1])+' '+logoString+'\\\n')
          # Set axis colours
          for x in ['top', 'bottom', 'left', 'right']:
            outfile.write('  --axis-style '+x+' /stroke_color \'' +
                          colours.value.axisColour2D+'\'\\\n')
          if doColourbar.value is not None and plot in doColourbar.value:
            # Do colourbar
            outfile.write('  --xyz-map\\\n')
            outfile.write(
                '  --new-zaxis zvalues /location right /bar_size \'0.5cm\'\\\n')
            outfile.write(
                "  --label-style zvalues /angle 270 /shift 0.4  /valign 'midheight'\\\n")
            outfile.write('  --y2 --plot '+currentParse+'_obs2D_' +
                          str(column)+'_colorbar.ct2@1:2:3 /zaxis zvalues ')
            outfile.write('/color-map \''+colours.value.colourMap(
                contourLevelsObs, 'obs')+'\' /fill-transparency 1\\\n')
            outfile.write('  --axis-style y /decoration ticks --yrange ' +
                          str(ytrema[0])+':'+str(ytrema[1])+'\\\n')
            outfile.write(
                '  --ylabel \''+labels.value[column]+'\' /shift 3.5 /angle 180 /scale 0.8\\\n')
          outfile.close
          subprocess.call('chmod +x '+currentBase+'_obs2D_' +
                          str(column)+'.bsh', shell=True)

    # Make profile-posterior comparison plotting scripts
    if doProfile.value and doPosterior.value:

      # Work out which is the main and which is the comparison
      [main, sec] = ['post', 'like'] if PosteriorIsMainInComboPlot else ['like', 'post']

      # Get contours
      if contours2D.value is not None:
        mainContourLevels = getContours(dirs.parseFilename, plot, main)
        secContourLevels = getContours(dirs.parseFilename, plot, sec)

      # Determine keys
      keyString = ''
      if doKey2D.value is not None and plot in doKey2D.value:
        markers = []
        # Get details of key for reference point
        if plotRef:
            markers.append([colours.value.referenceMarkerOuter,
                            colours.value.referenceMarkerOuterColour,
                            colours.value.referenceMarkerOuterColour,
                            colours.value.referenceMarkerOuterScale,
                            refText,
                            colours.value.referenceMarkerInner,
                            colours.value.referenceMarkerInnerColour,
                            colours.value.referenceMarkerInnerScale/colours.value.referenceMarkerOuterScale])
        if PosteriorIsMainInComboPlot:
          # Get details of key for posterior mean
          markers.append([colours.value.mainPostMeanMarker,
                          colours.value.mainPostMeanColour2D,
                          colours.value.mainPostMeanColourOutline2D,
                          colours.value.mainPostMeanMarkerScale,
                          'Mean'])
          # Get details of key for best fit
          markers.append([colours.value.comparisonBestFitMarker,
                          colours.value.comparisonBestFitColour,
                          colours.value.comparisonBestFitColour,
                          colours.value.comparisonBestFitMarkerScale,
                          'Best fit'])
        else:
          # Get details of key for posterior mean
          markers.append([colours.value.comparisonPostMeanMarker,
                          colours.value.comparisonPostMeanColour,
                          colours.value.comparisonPostMeanColour,
                          colours.value.comparisonPostMeanMarkerScale,
                          'Mean'])
          # Get details of key for best fit
          markers.append([colours.value.mainBestFitMarker,
                          colours.value.mainBestFitColour2D,
                          colours.value.mainBestFitColourOutline2D,
                          colours.value.mainBestFitMarkerScale,
                          'Best fit'])

        # Reverse vertical ordering if keys are to be placed at the top of the page, so as to fill from the top down
        if keyLoc[0] == 't':
            markers.reverse()
        # Construct ctioga2 command for each key
        for i, key in enumerate(markers):
          if key[0] == 'Bullet' or key[0] == 'BulletOpen':
              key[3] /= 1.5
          if key[3] > 1.0:
              key[3] = 1.0
          # Write the extra marker overlay for the reference point
          if len(key) == 8:
              keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[5]+' /color \'' +\
                  key[6]+'\' /scale '+str(key[7]*key[3])+'\\\n'
          # Write the main marker
          keyString += '  --draw-marker '+str(xVals[0])+','+str(yVals[i])+' '+key[0]+' /fill-color \''+str(
              key[1])+'\' /stroke-color \''+str(key[2])+'\' /scale '+str(key[3])+'\\\n'
          # Write the key text
          keyString += '  --draw-text ' + \
              str(xVals[1])+','+str(yVals[i])+' \''+key[4] + \
              '\'  /color \''+colours.value.keyTextColour2D
          keyString += '\' /justification left /scale 0.75 /alignment center \\\n'

      # Open plotting shell script file for writing
      outfile = smart_open(
          dirs.baseScriptFilename+'_'+'_'.join([str(x) for x in plot])+'_combo2D.bsh', 'w')
      outfile.write('#!/usr/bin/env bash\n')
      outfile.write('# This plot script created by pippi '+pippiVersion +
                    ' on '+datetime.datetime.now().strftime('%c')+'\n')
      outfile.write('ctioga2\\\n')
      outfile.write('  --name '+currentBaseMinimal+'_combo2D')
      outfile.write('  --plot-scale \''+str(plot_scale)+'\'\\\n')
      outfile.write('  --page-size \''+plotSizeInternal+'\'\\\n')
      if doColourbar.value is not None and plot in doColourbar.value:
        outfile.write('  --frame-margins '+str(left_margin+0.03)+','
                                          + str(right_margin+0.15)+','
                                          + str(top_margin)+','
                                          + str(bottom_margin)+'\\\n')
      else:
        outfile.write('  --frame-margins '+str(left_margin+0.05)+','
                                          + str(right_margin+0.02)+','
                                          + str(top_margin)+','
                                          + str(bottom_margin)+'\\\n')
      outfile.write('  --xrange '+str(xtrema[0])+':'+str(xtrema[1])+'\\\n')
      outfile.write('  --yrange '+str(ytrema[0])+':'+str(ytrema[1])+'\\\n')
      outfile.write('  --ylabel \'' +
                    labels.value[plot[1]]+'\' /shift 2.9\\\n')
      outfile.write('  --xlabel \''+labels.value[plot[0]]+'\'\\\n')
      outfile.write(
          '  --label-style x /scale 1.0 /shift 0.15 --label-style y /scale 1.0 /shift 0.75')
      if yAxisAngle.value is not None:
          outfile.write(' /angle '+str(yAxisAngle.value))
      outfile.write('\\\n  --xyz-map\\\n')
      if doColourbar.value is not None and plot in doColourbar.value:
        outfile.write(
            '  --new-zaxis zvalues /location right /bar_size \'0.5cm\'\\\n')
        outfile.write(
            "  --label-style zvalues /angle 270 /shift 0.4  /valign 'midheight'\\\n")
      outfile.write('  --plot '+currentParse+'_'+main+'2D.ct2@1:2:3 ')
      if doColourbar.value is not None and plot in doColourbar.value:
          outfile.write('/zaxis zvalues ')
      outfile.write(
          '/color-map \''+colours.value.colourMap(mainContourLevels, main)+'\'\\\n')
      if contours2D.value is not None:
        # Plot comparison contours
        outfile.write('  --plot '+currentParse+'_'+sec +
                      '2D.ct2@1:2:3 /fill-transparency 1\\\n')
        for contour in secContourLevels:
          outfile.write('  --draw-contour '+contour+' /color '+colours.value.comparisonPostContourColour2D +
                        ' /style '+colours.value.comparisonContourStyle+' /width '+colours.value.lineWidth2D+'\\\n')
      outfile.write('  --plot '+currentParse+'_'+main +
                    '2D.ct2@1:2:3 /fill-transparency 1\\\n')
      if contours2D.value is not None:
        # Plot contours
        for contour in mainContourLevels:
          outfile.write('  --draw-contour '+contour+' /color '+colours.value.mainPostContourColour2D +
                        ' /style '+colours.value.mainContourStyle+' /width '+colours.value.lineWidth2D+'\\\n')
      if doLegend2D.value is not None and plot in doLegend2D.value:
        # Write legend
        try:
          legendLocation = legendLoc2D.value[plot[0]][plot[1]]
        except (KeyError, TypeError):
          legendLocation = defaultLegendLocation
        outfile.write('  --legend-inside \''+legendLocation +
                      '\' /scale 1.0 /vpadding 0.1\\\n')
        if legendLines.value is not None:
          for x in legendLines.value:
              outfile.write('  --legend-line \''+x+'\' /color \'' +
                            colours.value.legendTextColour2D+'\'\\\n')
        outfile.write('  --legend-line \'Like vs. Posterior\' /color \'' +
                      colours.value.legendTextColour2D+'\'\\\n')
      # Get best-fit point
      bestFit = getCentralVal(dirs.parseFilename, plot, 'like', lookupKeys)
      # Get posterior mean
      postMean = getCentralVal(dirs.parseFilename, plot, 'post', lookupKeys)
      # Always plot both best fit and posterior mean on comparison plot
      if PosteriorIsMainInComboPlot:
        bestFitData = [colours.value.comparisonBestFitMarker, colours.value.comparisonBestFitColour,
                       colours.value.comparisonBestFitColour, colours.value.comparisonBestFitMarkerScale]
        postMeanData = [colours.value.mainPostMeanMarker, colours.value.mainPostMeanColour2D,
                        colours.value.mainPostMeanColourOutline2D, colours.value.mainPostMeanMarkerScale]
      else:
        bestFitData = [colours.value.mainBestFitMarker, colours.value.mainBestFitColour2D,
                       colours.value.mainBestFitColourOutline2D, colours.value.mainBestFitMarkerScale]
        postMeanData = [colours.value.comparisonPostMeanMarker, colours.value.comparisonPostMeanColour,
                        colours.value.comparisonPostMeanColour, colours.value.comparisonPostMeanMarkerScale]
      outfile.write('  --draw-marker '+str(bestFit[0])+','+str(bestFit[1])+' '+bestFitData[0]+' /fill-color \''+str(bestFitData[1])+'\' /stroke-color \''+str(bestFitData[2]) +
                    '\' /scale '+str(bestFitData[3])+' \\\n')
      if postMean:
          outfile.write('  --draw-marker '+str(postMean[0])+','+str(postMean[1])+' '+postMeanData[0]+' /fill-color \''+str(postMeanData[1])+'\' /stroke-color \''+str(postMeanData[2]) +
                        '\' /scale '+str(postMeanData[3])+' \\\n')
      # Plot reference point
      if plotRef:
          outfile.write(refString)
      # Draw key
      outfile.write(keyString)
      # Write credits
      if blame.value is not None:
        blameYCoordinate = str(
            blameFractionalVerticalOffset * yRange + ytrema[1])
        outfile.write('  --draw-text '+str(xtrema[1])+','+blameYCoordinate +
                      ' \''+blame.value+'\' /scale 0.5 /justification right\\\n')
      # Add logo
      if logoFile.value is not None:
        outfile.write(
            '  --draw-text '+str(logoCoords[0])+','+str(logoCoords[1])+' '+logoString+'\\\n')
      # Set axis colours
      for x in ['top', 'bottom', 'left', 'right']:
        outfile.write('  --axis-style '+x+' /stroke_color \'' +
                      colours.value.axisColour2D+'\'\\\n')
      if doColourbar.value is not None and plot in doColourbar.value:
        # Do labelling for colourbar
        outfile.write('  --y2 --plot '+currentParse+'_'+main +
                      '2D.ct2@1:2:3 /fill-transparency 1\\\n')
        outfile.write('  --axis-style y /decoration ticks --yrange ' +
                      str(ytrema[0])+':'+str(ytrema[1])+'\\\n')
        outfile.write('  --ylabel \''+postColourbarString +
                      '\' /shift 3.5 /angle 180 /scale 0.8\\\n')
      outfile.close
      subprocess.call('chmod +x '+currentBase+'_combo2D.bsh', shell=True)


def getContours(parseFilename, plot, statistic):
  # Construct dimensionality of plot and string indicating specific plot (if any)
  if type(plot) == list:
    [dim, plot] = [str(len(plot)), '' if statistic ==
                   'like' else '_'+'_'.join([str(x) for x in plot])]
  else:
    [dim, plot] = ['1', '' if statistic == 'like' else '_'+str(plot)]
  # Open contour file
  contourfile = safe_open(parseFilename+plot+'_'+statistic+dim+'D.contours')
  # Read contents
  fileContents = contourfile.readline()
  while fileContents[0] == '#':
    fileContents = contourfile.readline()
  #Shut it
  contourfile.close
  levels = fileContents.split()
  return levels


def getContours_obs(parseFilename, plot, observable):
  # Construct dimensionality of plot and string indicating specific plot (if any)
  if type(plot) == list:
    [dim, plot] = [str(len(plot)), '_'+'_'.join([str(x) for x in plot])]
  # Open contour file
  contourfile = safe_open(parseFilename+plot+'_obs' +
                          dim+'D_' + str(observable) + '.contours')
  # Read contents
  fileContents = contourfile.readline()
  while fileContents[0] == '#':
    fileContents = contourfile.readline()
  #Shut it
  contourfile.close
  levels = fileContents.split()
  return levels


def getCentralVal(parseFilename, plot, statistic, lk):
  # Find central value (either best fit or posterior mean) for requested plot
  # Open .best file
  bestfile = safe_open(parseFilename+'.best')
  # Read contents
  fileContents = bestfile.readline()
  while fileContents[0] == '#':
    fileContents = bestfile.readline()
  fileContents = bestfile.readlines()
  # Shut it
  bestfile.close
  if statistic == 'like':
    # Extract best fit
    point = fileContents[1].split()
  elif statistic == 'post':
    try:
      # Extract posterior pdf
      point = fileContents[3].split()
    except IndexError:
      return None
  else:
    # Never get here
    sys.exit(
        'Error: unrecognised statistic in pippi_script.getCentralVal.\nQuitting...')
  # Choose the coordinates corresponding to the axes of the current plot
  if type(plot) == list:
    coordinates = [point[lk.value[x]] for x in plot]
  else:
    coordinates = point[lk.value[plot]]
  return coordinates


def dictFallback(risky, safe, key):
  # Try to extract entry corresponding to key from risky dataObject, otherwise use safe dataObject
  try:
    return risky.value[key]
  except (KeyError, TypeError):
    return safe.value[key]

