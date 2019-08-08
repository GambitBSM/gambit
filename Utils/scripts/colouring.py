#!/usr/bin/env python
#
# GAMBIT: Global and Modular BSM Inference Tool
#*********************************************
# \file
#
#  The GAMBIT Colouring-in Book
#
#  A script for priming pippi runs and patching
#  together their outputs. Designed to allow
#  one to highlight specific regions of preferred
#  parameter space, and then overplot them
#  (e.g. relic density mechanisms).
#
#*********************************************
#
#  Authors (add name and date if you modify):
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#    \date 2017 Feb
#
#*********************************************

import sys
import yaml
import os
import copy
import re
import datetime
import stat
from multiprocessing import cpu_count

# Global constants
verbose = False
default_contour = 95.4
default_contour_style = "Solid"
default_contour_width = 2
default_colour = "blue"
default_n_contours = 150
n_threads = cpu_count()

# Checks for the presence of one or more keys in a YAML node
def check_node(node, name, keys):
  is_ok = False
  if isinstance(keys, basestring):
    error = "  Region \""+name+"\" must have key \""+str(keys)+"\"."
    is_ok = (keys in node)
  else:
    error = "  Region \""+name+"\" must have at least one of the keys "+str(keys)+"."
    for x in keys:
      if (x in node):
        is_ok = True
        break
  if not is_ok: sys.exit(error)


def usage():
  sys.exit('\n  Usage: colouring [prime/combine] file1 file2\n  where file1 is a YAML file that defines the regions you want to find.\n        file2 is the pip file that defines the pippi run to modify.\n')


def main(arguments):
  #Starting routine

  commandLineOptions = { 'prime':prime, 'combine':combine }

  if (len(arguments) is not 4):
    #Print usage info and quit if pippi is invoked without an argument
    usage()

  else:

    try:
      #Check if colouring has been invoked with one of the two known specific commands
      command = commandLineOptions[arguments[1]]
      command(arguments[2], arguments[3])
    except KeyError:
      print
      print 'Unrecognised colouring mode: '+arguments[1]
      usage()

  sys.exit()


# Prepare separate pippi runs for each region
def prime(region_file, pip_file):

  print

  # Load up the regions from the yaml file, and the template for pippi runs from the pip file.
  yaml_loader = yaml.full_load if hasattr(yaml, 'full_load') else yaml.load
  regions = yaml_loader(file(region_file, 'r'))
  pip = file(pip_file, 'r').read()

  # Get the drawing order
  if regions["drawing_order"]:
    drawing_order = regions["drawing_order"]
  else:
    sys.exit('ERROR: No drawing_order specified in '+region_file)

  # Retrieve the best fit in the base scan.
  #First work out where the best fit file is.  Start with the dir.
  parse_dir = re.search('parse_dir\s*=\s*("(.*)"|\'(.*)\')', pip)
  parse_dir = parse_dir.group(2 if parse_dir.group(2) else 3)
  # Now infer the filename from the chain name.
  chain_name = re.search('main_chain\s*=\s*("(.*)"|\'(.*)\')', pip)
  chain_name = chain_name.group(2 if chain_name.group(2) else 3)
  chain_name = re.sub(r'.*/|\..?.?.?$', '', chain_name)
  best_filename = parse_dir+"/"+chain_name+".best"
  # Now open the file and read in the best fit.
  best_file = file(best_filename, 'r')
  for x in best_file.readlines():
    if not x.startswith('#'):
      parts = x.split(':')
      bestFit = float(parts[1])
      break


  # Iterate over the regions defined in the yaml file
  for name in drawing_order:
    if (verbose): print "Priming pippi run for extracting region: "+name
    mechanism = regions[name]

    # Check that the mechanism is sufficiently specified
    check_node(mechanism, name, ["extra_1D_plots", "extra_2D_plots"])
    check_node(mechanism, name, "datastream")
    check_node(mechanism, name, "cut")
    check_node(mechanism, name, "label")

    # Make a new pip file for this region
    newpip = copy.deepcopy(pip)

    # Replace the necessary parts of it, starting with the common section
    contour = default_contour
    if ("contour_levels" in mechanism): contour = mechanism["contour_levels"]
    newpip = re.sub('contour_levels\s*=.*\n', 'contour_levels = '+str(contour)+'\n', newpip)
    if ("extra_1D_plots" in mechanism): newpip = re.sub('oneD_plot_quantities\s*=\s*', 'oneD_plot_quantities = '+str(mechanism["extra_1D_plots"])+' ', newpip)
    if ("extra_2D_plots" in mechanism): newpip = re.sub('twoD_plot_quantities\s*=\s*', 'twoD_plot_quantities = '+str(mechanism["extra_2D_plots"])+' ', newpip)
    newpip = re.sub("bf_lnlike_for_profile_like\s*=\s*", "bf_lnlike_for_profile_like = "+str(bestFit)+" ", newpip)

    # Now the parse section
    newpip = re.sub('parse_dir\s*=.*\n', 'parse_dir = \'parse_'+name+'\'\n', newpip)
    newpip = re.sub('data_ranges\s*=\s*', 'data_ranges = '+mechanism["cut"]+' ', newpip)
    if ("preamble" in mechanism): newpip = re.sub('preamble\s*=.*\n', 'preamble = \''+mechanism["preamble"]+'\'\n', newpip)
    newpip = re.sub('assign_to_pippi_datastream\s*=\s*', 'assign_to_pippi_datastream =   '
     +mechanism["datastream"]+' \\\n                               ', newpip)
    newpip = re.sub('quantity_labels\s*=\s*', 'quantity_labels =   '
     +mechanism["label"]+' \\\n                    ', newpip)

    # Now the script section
    newpip = re.sub('script_dir\s*=.*\n', 'script_dir = \'scripts_'+name+'\'\n', newpip)
    colour = default_colour
    if ("colour" in mechanism): colour = mechanism["colour"]
    newpip = re.sub('colour_scheme\s*=.*\n', 'colour_scheme = Blockshading_'+colour+'\n', newpip)

    # Now the plot section
    newpip = re.sub('plot_dir\s*=.*\n', 'plot_dir = \'plots_'+name+'\'\n', newpip)

    # Output the new pip file
    filename = os.path.splitext(pip_file)
    filename = filename[0]+"_"+name+filename[1]
    with open(filename,"w") as f:
      f.write(newpip)
      print "  Generated new pip file "+filename

  print


def combine(region_file, pip_file):

  # Load up the regions from the yaml file, and the template for pippi runs from the pip file.
  regions = yaml.load(file(region_file, 'r'))
  pip = file(pip_file, 'r').read()

  # Get the drawing order
  if regions["drawing_order"]:
    drawing_order = regions["drawing_order"]
  else:
    sys.exit('ERROR: No drawing_order specified in '+region_file)

  # Find the filenames of all the 2D profile likelihood scripts
  script_dir = re.search('script_dir\s*=\s*("(.*)"|\'(.*)\')', pip)
  script_dir = script_dir.group(2 if script_dir.group(2) else 3)
  like2D_scripts = [x for x in os.listdir(script_dir) if "like2D" in x]

  # Make a new scripts dir for the combined scripts
  combo_dir = script_dir+'_combined'
  if not os.path.isdir(combo_dir): os.mkdir(combo_dir)

  # Make a new plots dir for the combined plots
  plot_dir = re.search('plot_dir\s*=\s*("(.*)"|\'(.*)\')', pip)
  plot_dir = plot_dir.group(2 if plot_dir.group(2) else 3)
  plot_combo_dir = plot_dir+'_combined'
  if not os.path.isdir(plot_combo_dir): os.mkdir(plot_combo_dir)

  # Make a bulk script that calls all of the combined plotting scripts
  bulkscript_name = 'make_combined_'+re.sub('\.pip', '', pip_file)+'_plots.bsh'
  bulkscript = file(bulkscript_name, 'w')
  bulkscript.write('cd '+combo_dir+'\n')

  # Iterate over the different scripts
  for script_index, script_name in enumerate(like2D_scripts):

    # Initialise empty lists of the things that will vary with region
    marker_commands = []
    plot_commands = []
    fill_colours = []
    contour_commands = []
    min_contours = []
    region_names = []
    regional_script = None

    # Iterate over all the regions mentioned in the drawing order
    for name in drawing_order:

      # Open the script file, cycling if it doesn't exist
      fullname = script_dir+'_'+name+'/'+script_name
      if not os.path.isfile(fullname): continue
      regional_script = file(fullname, 'r').read()

      # Save the name of the region
      region_names.append(name)

      # Save the line style for the region
      contour_style = regions[name]["contour_style"] if "contour_style" in regions[name] else default_contour_style

      # Extract the marker command
      marker_command = re.findall('\s\s--draw-marker.*\n', regional_script)
      if marker_command: marker_commands.append(marker_command[0])

      # Extract the fill colour
      fill_colour = re.findall('--#...', regional_script)
      fill_colours.append(fill_colour[1][2:])

      # Extract the plot command
      plot_command = re.findall('\s\s--plot.*fill-transparency 1.*\n', regional_script)
      plot_commands.append(plot_command[0])

      # Extract the contour command
      contour_command_list = re.findall('\s\s--draw-contour.*\n', regional_script)
      min_contour = 1.0
      for i,x in enumerate(contour_command_list):
        contour_command_list[i] = re.sub('width.*\n', 'width '+str(default_contour_width)+'\\\n', x)
        contour_command_list[i] = re.sub('style\s*.*?\s', 'style '+contour_style+' ', contour_command_list[i])
        min_contour = min(min_contour, float(re.search('--draw-contour\s(.*?)\s', contour_command_list[i]).group(1)))
      contour_commands.append(contour_command_list)
      min_contours.append(min_contour)

    # If this script is not present for any of the regions, go on to the next one.
    if (regional_script is None): continue

    # Extract the axis styles from the last regional script
    axis_styles = re.findall('\s\s--axis-style\s*[^y]*\n', regional_script)

    # Read in the original script
    base_script = file(script_dir+'/'+script_name, 'r').readlines()

    # Extract preamble from original script
    preamble = ''
    for x in base_script[2:]:
     preamble = preamble+x
     if x.startswith('  --xyz-map'): break

    # Extract textual annotations from the original script
    text = [re.sub('White','Black',x) for x in base_script if x.startswith('  --draw-text') or x.startswith('  --legend')]

    outfile = open(combo_dir+'/'+script_name,'w')
    outfile.write('#!/usr/bin/env bash\n')
    outfile.write('# This plot script created by the pippi scripter \'colouring\' on '+datetime.datetime.now().strftime('%c')+'\n')

    # Write the number of fill steps to be used
    for region in region_names: outfile.write('n_contours_'+re.sub('-','_',region)+'='+str(default_n_contours)+'\n')

    # Write the fist half of the ctioga2 command
    outfile.write(preamble)

    # Draw the filled regions, using many closely-packed contours
    for region, plot_command in enumerate(plot_commands):
      outfile.write('  --color \''+fill_colours[region]+'\' \\\n')
      outfile.write(plot_command)
      outfile.write('    $(echo $(for (( i=0; i<$n_contours_'+re.sub('-','_',region_names[region])+'; i++ )); do echo "--draw-contour '
                    '$(echo "'+str(min_contours[region])+' + '+str(1.0-min_contours[region])+'*$i/($n_contours_'
                    +re.sub('-','_',region_names[region])+'-1)" | bc -l) /style Solid /width '+str(default_contour_width)+' "; done)) \\\n')
      outfile.write('  --draw-contour 1.000 /style Solid /width '+str(default_contour_width)+'\\\n')

    # Draw the actual outline contours on top of all the filled regions
    for region, plot_command in enumerate(plot_commands):
      outfile.write(plot_command)
      for x in contour_commands[region]: outfile.write(x)

    # Draw any markers
    for marker_command in marker_commands:
      outfile.write(marker_command)

    # Write any textual annotations, and set the axes up in the manner of the region plots
    for x in text: outfile.write(x)
    for x in axis_styles: outfile.write(x)

    # Add an entry to the bulk plotting script
    pdf_name = re.sub("\.bsh", ".pdf", script_name)
    bulkscript.write('(echo "./'+script_name+'" && ./' + script_name +
    ' && gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/screen -dNOPAUSE -dQUIET -dBATCH -sOutputFile='+
    '../' + plot_combo_dir + '/' + pdf_name + ' ' + pdf_name +
    ' && rm ' + pdf_name + ') &\n')
    if (script_index%n_threads == n_threads - 1 ): bulkscript.write('wait\n')

    # Done!  Close the new script file and make it executable for both user and group.
    outfile.close
    os.chmod(combo_dir+'/'+script_name, stat.S_IRWXU | stat.S_IRWXG)

  # All over red rover.  Go write a paper.
  bulkscript.write('wait\n')
  bulkscript.write('echo "Generated all combined plots.  Now go write a paper!"\n')
  bulkscript.close
  os.chmod(bulkscript_name, stat.S_IRWXU | stat.S_IRWXG)

#Actual program launched on invocation
main(sys.argv)
