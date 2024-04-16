#!/usr/bin/env python
#
#  GAMBIT: Global and Modular BSM Inference Tool
#  *********************************************
#  \file
#
#  Reads SPheno's InputOutput_<Model>.f90
#  file and creates the decay table
#
#*********************************************
#
#  Authors (add name and date if you modify):
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2010 Aug
#
#*********************************************

import os
import sys

def CustomError(message) :
  print "Unable to create decay table. " + message
  sys.exit(1)

# Get backend info
try:

  be_name = sys.argv[1]
  be_ver = sys.argv[2]
  if len(sys.argv) > 2:
    gambit_dir = sys.argv[3]

except IndexError:
  CustomError("Wrong number of arguments.\n    Usage: " + os.path.basename(__file__) + " <be_name> <be_ver> [<gambit_dir>]")

# Extract the model and path names
if len(be_name.split('_')) > 1 :
  be_model = '_'.join(be_name.split('_')[1::])
  be_model_no_underscore = be_model.replace('_','')
else :
  CustomError("Wrong name of backend.")

if "SARAHSPheno" in be_name :
  be_path = 'sarah-spheno'
elif "SPheno" in be_name :
  be_path = 'spheno'
else :
  CustomError("Wrong name of backend.")

# Get safe version
safe_ver = be_ver.split(".")
safe_ver = "_".join(safe_ver)

# Get path to SPheno file
this_path = os.path.dirname(os.path.abspath(__file__))
if gambit_dir:
  IO_file = gambit_dir + '/Backends/installed/' + be_path + '/' + be_ver + '/' + be_model + '/' + be_model_no_underscore + '/InputOutput_' + be_model_no_underscore + '.f90'
else:
  IO_file = this_path + '/../installed/' + be_path + '/' + be_ver + '/' + be_model + '/' + be_model_no_underscore + '/InputOutput_' + be_model_no_underscore + '.f90'

if not os.path.exists(IO_file) :
  CustomError("File doesn't exist.")

# Get path to output decay file
decay_file = this_path + '/' + be_name + '_' + safe_ver + '_decays_info.dat'

# Initialisation
pdgs = {}
names = {}

print "Printing decay table for " + be_model + " model"

with open(IO_file, 'r') as f_in, open(decay_file, 'w') as f_out:

  f_out.write(
    '# This file contains a list of all the NMSSM decays calculated by sarah-spheno_NMSSM,\n'\
    '# along with the spheno array index (INDEX) used internally in sarah-spheno_NMSSM.\n'\
    '# For each decay there is also a correction factor (CORRF) which tells us\n'\
    '# whether the BR on that line should be corrected to account for charge conjugate\n'\
    '# final states (CORRF=0.5) or not (CORRF=1.0)\n\n')

  decays = False
  indices = []

  # Iterate over lines
  for line in f_in:

    # Get the PDGs
    if line.startswith("PDG") :
      particle = line.split('=')[0][3:]
      pdg = line.split('=')[1][0:-1]
      pdgs[particle] = pdg
      if pdg[0]=='-' :
        pdgs["-"+particle] = pdg[1:]
      else :
        pdgs["-"+particle] = "-"+pdg 
      pdgs["--"+particle] = pdg
 
    # Get names of particles
    if line.startswith("NameParticle") :
      particle = line.split('=')[0][12:] 
      name = line.split('=')[1][1:-2]
      names[particle] =  name
      names["-"+particle] = name+"^*"
      names["--"+particle] = name

    # Now find the decays entries
    if line.startswith("If ((gT") :

      # Start reading decays
      decays = True
      count = 0

      # get particle
      subline = line.split('.')[0]
      part = subline[7::]

      decaypdg = int(pdgs[part])
      if decaypdg < 0:
          decaypdg = -decaypdg
          part = "-"+part

      # print block entry
      f_out.write(
        'DECAY        ' +  str(decaypdg) + '     0.0000000E+00   # ' + names[part] + '\n'
        '#    INDEX  NDA      ID1      ID2     CORRF\n')

    # Ignore 1 loop decays
    if line.startswith("If(gT1L") :
      decays = False

    # Get indices
    if "Do gt" in line and decays:

      indices.append( line.split('=')[1][0:-1].split(',') )

    # End of index loop
    if "End Do" in line and decays:
      indices = indices[:-1]

    # Get daugthers
    if line.startswith("CurrentPDG") and decays :

      print line
      ndaughters = int(line[10])
      daughters = []
 
      for i in range(ndaughters):
        daughter = line.split("=")[1][:-2]
        print daughter
        if daughter[1] == '-' :
          daughters.append('-'+daughter[5:])
        else :
          daughters.append(daughter[4:])
        line = next(f_in)

      # Check for repeated print lines to add correction factors
      corrf = "1.00"
      if line.startswith("Write") :
        line = next(f_in)
        line = next(f_in)
        if line.startswith("Write") :
          corrf = "0.50"

      # List of processes
      processes = [daughters]

      # Loop over indices
      if len(indices) > 0 :
        processes = processes[:-1]
        di = 0 if "gt" in daughters[0] else 1 if "gt" in daughters[1] else 2
        for i in range(int(indices[0][0]),int(indices[0][1])+1) :
          process =  [daught.replace("gt" + str(di+1),str(i)) for daught in daughters] 
          processes.append(process)
          if len(indices) > 1 :
            processes = processes[:-1]
            dj = (1 if "gt" in daughters[1] else 2) if di == 0 else 2
            try:
              j1 = int(indices[1][0])
            except ValueError:
              j1 = i
            for j in range(j1,int(indices[1][1])+1) :
              new_process = [proc.replace("gt" + str(dj+1),str(j)) for proc in process]
              processes.append(new_process)
              if len(indices) > 2 :
                processes = processes[:-1]
                try:
                  k1 = int(indices[2][0])
                except ValueError:
                  k1 = j
                for k in range(k1,int(indices[2][1])+1) :
                  new_new_process = [proc.replace("gt3",str(k)) for proc in new_process]
                  processes.append(new_new_process)
 
      # Print processes
      for process in processes:
        count += 1
        proc_str = str(count).rjust(8) + str(ndaughters).rjust(5) + "  "
        for daughter in process :
          proc_str += pdgs[daughter].rjust(11)
        proc_str +=  corrf.rjust(7) + "  # BR(" + names[part] + "-> "
        for daughter in process :
          proc_str += names[daughter] + " "
        proc_str += ")\n"
        f_out.write(proc_str)
        if corrf == "0.50" :
          proc_str = str(count).rjust(8) + str(ndaughters).rjust(5) + "  "
          for daughter in process :
            proc_str += pdgs["-"+daughter].rjust(11)
          proc_str +=  corrf.rjust(7) + "  # BR(" + names[part] + "-> "
          for daughter in process :
            proc_str += names["-"+daughter] + " "
          proc_str += ")\n"
          f_out.write(proc_str)
          
        

    # Key to stop reading decays
    if line.startswith('End Subroutine LesHouches_Out'):
      decays = False
      print "Decay table for " + be_model + " model finished!"

