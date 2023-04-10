#  \file
#
#  ATLAS full likelihoods with pyhf
#
#  *************************************
#
#  \author Chris Chang
#          (christopher.chang@uqconnect.edu.au)
#  \date 2021
#
#  **************************************

"""
Based on:
- https://cds.cern.ch/record/2684863
- pyhf: https://github.com/scikit-hep/pyhf

This takes the signal data that will be output by ColliderBit and patches the 
background data. It then uses pyhf to find the LogLike. Python 3.6 or greater required (needed for pyhf more recent versions).
Required:
  - Signal data per signal region
  - Background only data json file
  - python >= v3.6 + pyhf
Outputs:
  - Loglike (s+b) - Loglike (b) 
todo/Notes:
  - Calculating the loglike gives a pyhf Runtime warning about an invalid value inside of the calculation (may be unavoidable)
  - Double Check that this works in the case of multiple analyses (needs more than 1 analysis using it)
  - metadata is specific to the analysis (but makes no difference to the result). Only needs to be something with right format/number of characters.
    Decide on some standard values to put there.
"""

import pyhf as pyhf
import json
import jsonpatch
import jsonschema
import numpy as np
pyhf.set_backend("numpy")

# Store global background data and info about number/organisation of JSON channels
ws = {}
Nsamplesdict = {}
Nbindict = {}

# Check whether this a particular analysis has been initialised
def FileExists(AnalysisName):
    global ws

    if AnalysisName in ws.keys():
        return True
    else:
        return False


# Resets the contents for a given analysis
# TODO: This is not currently being used
def Reset(AnalysisName):
    global ws
    global Nsamplesdict
    global Nbindict
    
    del ws[AnalysisName]
    del Nsamplesdict[AnalysisName]
    del Nbindict[AnalysisName]
    return 0


# Read in background JSON files and store this in ws dictionary
def ReadIn(AnalysisName,bkgpath):
    global ws
    global Nsamplesdict
    global Nbindict
    
    # First check that it hasn't already been loaded
    if FileExists(AnalysisName):
        print("FullLikes Error: Analysis ",AnalysisName," has been loaded twice")
        return(-1)
    
    # Try to open the analysis bkg json file
    try:
      with open(bkgpath,'r') as bkg:
        workspace = json.load(bkg)

        # Create empty dictionaries for the analysis
        Nsamplesdict[AnalysisName] = {}
        Nbindict[AnalysisName] = {}

        # Finding the location to add patch for a given signal region.
        for i,channel in enumerate(workspace["channels"]):
          Nsamplesdict[AnalysisName][channel["name"]] = (i,len(channel["samples"]))

      # Count how many bins exist for a given data entry
      for channel in workspace["observations"]:
        Nbindict[AnalysisName][channel["name"]] = len(channel["data"])

      # Load json scheme
      with open('Backends/examples/ATLAS_FullLikes/1.0/workspace.json','r') as wk:
        schema = json.load(wk)

      # Validate the workspace against a scheme (only needed for testing new bkg files)
      #jsonschema.validate(instance=workspace, schema=schema)
      
      # Store the bkg info in a pyhf workspace
      ws[AnalysisName] = pyhf.Workspace(workspace)

    except:
      return(1)

    return(0)


# Evaluate a Likelihood for a given analysis and set of signal counts
def Evaluate(mydict,AnalysisName):
  # Creating the json patch
  data = {}
  
  # metadata must meet requirement in json scheme
  # These aren't used in the calculation, but need to match the right format.
  data['metadata'] = {
      "description": "signal patchset for ColliderBit Analysis",
      "digests": {
              "sha256": "2563672e1a165384faf49f1431e921d88c9c07ec10f150d5045576564f98f820"
          },
      "labels": [
              "somenumber" # TODO: This doesn't matter what we choose, so what should we pick?
          ],
          "references": {
              "hepdata": "ins1755298"
          }
      }

  data['patches'] = []
  data["version"] = "1.0.0"

  Signal = {}
      
  # Add in the signal data to a patch
  for key,value in Nsamplesdict[AnalysisName].items():
    Signal[str(value[0])+"_"+str(value[1])] = []
    for i in range(Nbindict[AnalysisName][key]):
      Signal[str(value[0])+"_"+str(value[1])].append(mydict[key+"_"+str(i)])

  data['patches'].append({
          "metadata":
              {
              "name": "SignalData",
              "values": [0.0]
              },})
  

  data['patches'][0]['patch'] = []

  # First calculating the LogLike for background only, by adding in a patch with a data entry of zero.
  for key,value in Nsamplesdict[AnalysisName].items():
    BKG = []
    for i in range(Nbindict[AnalysisName][key]):
      BKG.append(0.0)
  
    data['patches'][0]['patch'].append(
              {
                  "op": "add",
                  "path": "/channels/{0}/samples/{1}".format(value[0],value[1]),
                  "value": {
                      "data": 
                          BKG
                      ,
                      "modifiers": [
                          {
                              "data": None,
                              "name": "mu_SIG",
                              "type": "normfactor"
                          },
                          {
                              "data": None,
                              "name": "lumi",
                              "type": "lumi"
                          }                          
                      ],
                      "name": "Zero for calculating BKG likelihood"
                  }
              },)
  PatchJson = pyhf.patchset.PatchSet(data)
  model = ws[AnalysisName].model(patches=PatchJson)
  bestfit_pars, twice_nll_b = pyhf.infer.mle.fixed_poi_fit(1.,ws[AnalysisName].data(model),model, return_fitted_val=True)
  
  # Appending for each separate path
  for key,value in Nsamplesdict[AnalysisName].items():
    data['patches'][0]['patch'].append(
              {
                  "op": "add",
                  "path": "/channels/{0}/samples/{1}".format(value[0],value[1]+1),
                  "value": {
                      "data": 
                          Signal["{0}_{1}".format(value[0],value[1])]
                      ,
                      "modifiers": [
                          {
                              "data": None,
                              "name": "mu_SIG",
                              "type": "normfactor"
                          },
                          {
                              "data": None,
                              "name": "lumi",
                              "type": "lumi"
                          } 
                      ],
                      "name": "SignalData"
                  }
              },)

  # Patching the background data and setting the model
  PatchJson = pyhf.patchset.PatchSet(data)
  model = ws[AnalysisName].model(patches=PatchJson)
  bestfit_pars, twice_nll_sb = pyhf.infer.mle.fixed_poi_fit(1.,ws[AnalysisName].data(model),model, return_fitted_val=True)

  dll = (-0.5*twice_nll_sb) - (-0.5*twice_nll_b)

  return(dll)

