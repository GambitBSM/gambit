Readme for Pippi v2.1
---------------------

#############################################################
# pippi: parse it, plot it
# ------------------------
# A program for operating on MCMC chains and related lists of
# samples from a function or distribution.  Pippi can merge,
# parse and plot sample ensembles ('chains'), either in terms
# of the likelihood/fitness function directly, or as implied
# posterior probability densities.  With the addition of a
# user-defined function, it can also post-process ('pare')
# chains.
#
# Author: Pat Scott (patscott@physics.mcgill.ca)
# License: see end of readme.
# Originally developed: March 2012
#############################################################


Installation
------------

Pippi requires almost no installation.

1. Make sure you have the following already installed:
   * Python v2.7 or later
   * NumPy and SciPy libraries for python (NumPy v0.9.0 or
     greater is required for full functionality)
   * ctioga2 v0.8 or later
   * bash
   * if you want to use pippi with hdf5 files: the h5py library for python

2. Extract the full pippi source directory and save it
   somewhere.

3. Add the path to wherever you've just saved the
   pippi source files to your $PATH variable.

4. Hit it.


Usage
-----
You can use pippi to do the following:

Merge two or more chains:

  pippi merge <chain1> <chain2> ... <chainx>

  Pippi will simply concatenate the two chains, doing a bit of basic
  error-checking along the way, and spit out a new merged chain to stdout.


Post-process a chain:

  pippi pare <chain> <name_of_python_module> <name_of_function_in_module>

  Pippi will dynamically load the python module <name_of_python_module>,
  find function <name_of_function_in_module> within it, and use this
  function to operate on each point in the chosen chain, spitting out
  the resulting post-processed chain to stdout.  The returned chain need
  not contain the same parameters/observables or even the same number of
  them as the initial chain.


Parse a chain using options in iniFile.pip:

  pippi parse iniFile.pip

  Pippi will automatically perform the binning, profiling, marginalising etc
  of the requested chain(s) indicated in iniFile.pip, and save them as
  datafiles. Note that iniFile.pip or the labels file it specifies must
  contain labels that indicate in which column and form pippi can find
  the mulitiplicities and/or likelihoods in the chain in question.


Write plotting scipts for a chain using options in iniFile.pip:

  pippi script iniFile.pip

  Pippi will write bash scripts for running ctioga2 on the data files
  produced in a pippi parse operation, using the options in iniFile.pip.


Run plotting scipts for a chain using options in iniFile.pip:

  pippi plot iniFile.pip

  Pippi will run the bash scripts written in a pippi script operation
  to generate pdf plots with ctioga2, then move and rename the plots as per
  the options in iniFile.pip.

Parse, script and plot in one go:

  pippi iniFile.pip

  Equivalent to running
    pippi parse iniFile.pip
    pippi script iniFile.pip
    pippi plot iniFile.pip


Examples
--------

Examples can be found in the example folder.  Run these examples to
see how pippi works and how to use it - look at the input and output files
involved to get an idea of what is happening and how you can tinker with it.
example/example.pip in particular has a full list of available options.

First download the example chain, using e.g. wget under linux, and save it
to the example/chains directory:
wget https://zenodo.org/record/2581331/files/oldchain.txt?download=1 -O example/chains/oldchain.txt

Post-process the CMSSM chain 'oldchain' in order to remove all points with
m_0 < 1 TeV, and save the new chain as 'newchain':
cd example
pippi pare chains/oldchain.txt pare_example.py strip > chains/newchain.txt

Make some plots comparing the distributions of m_0, m_half, A_0 and tanbeta in
oldchain and newchain:
pippi example.pip

If there are no errors, the plots will appear in 'example/plots'.  If you
want to change visual aspects of the plots like legends, etc, you can get
away with just running script and plot, as there is no need to redo the
parsing that is also included in "pippi example.pip":
pippi script example.pip
pippi plot example.pip

In general, options in later sections of example.pip do not affect the
operations corresponding to earlier sections, e.g. changing things in the
'plot' section means there is no need to rerun pippi parse or pippi script,
just pippi plot.  The opposite is not true; if you want changes you make
to options in the 'parse' section to be implemented, you will need to
rerun parse, script and plot.

You can also find an example_diver.pip file, which uses the output of the
C++ example in the Diver distribution (see https://diver.hepforge.org).


Version history
---------------
v2.1
Added Diver example pip file and dataset
Added the ability to indicate confidence / credibility level percentages in 1D plots
Added the ability to choose the outline colour for best fit and posterior mean markers
Improved some error and warning messages
Various bug fixes

v2.0
Made hdf5 routines operate out of core
Made binning configurable on per-column basis
Added inline post-processing from the .pip file
Added per-column data cuts
Added best-fit output in GAMBIT-compatible yaml format

v1.1
Added human-readable best fit output
Upgraded to compatibility with ctioga2 v0.8
Upgraded pip file parsing to support multi-line entries
Added pippi probe operation for hdf5 archives
Added hdf5 support (thanks to Christoph Weniger for first version of this code)

v1.0
Finished 1D plots
Expanded colour schemes
Added logo option
Tidied up example setup
Removed from DEvoPack and LDMBayes repos, given own repo

v0.3
Added posterior mean and best-fit key options
Added/improved treatment of directory options

v0.2
Added proper script and plot functions for 2D plots, 1D plots still need finishing
Fixed various bugs in parse
Uploaded to git repo for DEvoPack and LDMBayes

v0.1
First alpha, only parse, pare and merge genuinely functional
Uploaded to git repo for LDMBayes


Standard BSD License
--------------------

Copyright (c) 2012 onwards, Patrick Scott
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
