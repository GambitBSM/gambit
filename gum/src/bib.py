#  GUM: GAMBIT Universal Model Machine
#  ***********************************
#  \file
#
#  Contains all routines for generating
#  a list of bibtex tags for all used
#  software. 
#
#  *************************************
#
#  \author Christopher Chang
#  \date 2021
#
#  **************************************

def generate_bib_tags(output_opts,gum_math):
  """
  For each used piece of software relevant for gum,
  generate the list of bib tags.
  """
  
  bibtags = ""
  
  # GUM. TODO: Needs updating once published
  bibtags += "    \"Bloor:2021gtp\", // GUM 1.0 Paper\n"
  
  # FeynRules
  if gum_math == 'feynrules':

    bibtags += "    \"Alloul:2013bka\", // FeynRules 2.0 Manual\n"
    bibtags += "    \"Christensen:2008py\", // FeynRules made easy\n"
    bibtags += "    \"Christensen:2010wz\", // FeynRules: Whizard Interface\n"
    bibtags += "    \"Christensen:2009jx\", // FeynRules: CalcHEP, FeynArts, Sherpa interfaces\n"
    bibtags += "    \"Degrande:2011ua\", // Universal FeynRules Output\n"
    
  # SARAH
  if gum_math == 'sarah':

    bibtags += "    \"Staub:2013tta\", // SARAH 4.0\n"
    bibtags += "    \"Staub:2012pb\", // SARAH 3.2\n"
    bibtags += "    \"Staub:2008uz\", // SARAH\n"
    bibtags += "    \"Staub:2010jh\", // SARAH: Automatic Calc of SUSY RGE and Self Energies\n"
    bibtags += "    \"Staub:2015kfa\", // SARAH: Exploring new models in detail\n"

  # CalcHEP
  if output_opts.ch:

    bibtags += "    \"Pukhov:2004ca\", // Calchep 2.3\n"
    bibtags += "    \"Belyaev:2012qa\", // Calchep 3.4\n"

  # Vevacious
  if output_opts.vev:

    bibtags += "    \"Camargo-Molina:2013qva\", // Vevacious\n"
    
  # MadGraph
  if (output_opts.ufo and output_opts.pythia):
  
    bibtags += "    \"Stelzer:1994ta\", // MadGraph: Generation of Helicity Amplitudes\n"
    bibtags += "    \"Maltoni:2002qb\", // Event generation with MadEvent\n"
    bibtags += "    \"Alwall:2007st\", // MadGraph: Web Generation\n"
    bibtags += "    \"Alwall:2011uj\", // MadGraph 5: Going Beyond\n"
  
  # Pythia
  if output_opts.pythia:
  
    bibtags += "    \"Sjostrand:2014zea\", // Pythia\n"
    
  # Micromegas
  if output_opts.mo:

    bibtags += "    \"Belanger:2014vza\", // Micromegas 4.1\n"
    bibtags += "    \"Belanger:2013oya\", // Micromegas 3.0\n"
    bibtags += "    \"Belanger:2010gh\", // Micromegas 2.4\n"
    bibtags += "    \"Belanger:2008sj\", // Micromegas 2.2\n"
    bibtags += "    \"Belanger:2006is\", // Micromegas 2.0\n"
    bibtags += "    \"Belanger:2004yn\", // Micromegas 1.3\n"
    bibtags += "    \"Belanger:2001fz\", // Micromegas 1.0\n"
    
  # Spheno
  if output_opts.spheno:

    bibtags += "    \"Porod:2003um\", // Spheno\n"
    bibtags += "    \"Porod:2011nf\", // Spheno 3.1\n"
    
  return bibtags
