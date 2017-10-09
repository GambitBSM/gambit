"""A rudimentary tool for parsing the model hierarchy source files and
   trying to reconstruct the parameter translation sequence.

   I decided to try it this way because it is currently impossible to do
   from within GAMBIT itself, yet it would be very useful to see what
   the parameter translation sequence really looks like. 

   This will only ever be useful as a sort of debugging tool. It should not be
   considered as a guarantee that the parameter translation actually happens
   as we reconstruct it here, because there are many ways that one could
   write the translation functions such that we cannot automatically detect
   which parameters go where. It isn't a full C++ parser.

   Ok so how can this work? Suppose we just want to pick a model, and see
   where its parameters end up. Need to do the following:

   1. Parse the model header files to reconstruct the model hierarchy for
      the requested model
   2. For each model in the tree, look for the translation functions, e.g.
      the declarations like
       INTERPRET_AS_PARENT_FUNCTION(MSSM19atQ_to_MSSM24atQ)
       INTERPRET_AS_X_FUNCTION(MSSM20atQ, MSSM19atQ_to_MSSM20atQ)
   3. Find the source files containing those functions
   4. Parse the translation functions and try to figure out which parameters
      are converted into which.
      - This will only ever be partially possible, because all kinds of
        bizarre manipulations will be possible. Will have to just check for
        e.g. the following:
        - Direct setting of all common parameters
          e.g. targetP.setValues(myP,false);
        - Direct setting of one parameter to another (can extract surrounding math also)
          e.g. targetP.setValue("mq2_1",  myP["mq2_12"] )
        - Direct setting of one parameter to a value
          e.g. targetP.setValue("Ae_12",  0.0 );
        - In all other cases, will have to just default to showing whatever C++
          code is found in the setValue or setValues, or set_many_to_one, arguments. 
          This will break the tree, but might still be clear what is happening.

"""

import os
import operator
import subprocess as sp
from StringIO import StringIO
execfile("./Utils/scripts/harvesting_tools.py")

modeldir = "./Models/include/gambit/Models/models"
model_source_dir = "./Models/src/models"

#--- Helper functions ---

class Model:

   def __init__(self,MODEL,PARENT,header):
      self.name = MODEL
      self.parent = PARENT
      self.parameters = set([])
      self.IAPfunc = None
      self.IAPfunc_code = None
      self.header = header

def get_expanded_source(fname):
   """Runs the C preprocessor over a source file, expanding all the macros defined
      ***in that file*** (all includes are first commented out)"""

   # Combine the CAT definitions with the desired source file
   #command = 'cat Utils/include/gambit/Utils/cats.hpp {0} \
   #           | sed "s/#include/\/\/#include/g" \
   #           | gcc -xc -E - '.format(fname)

   step1 = sp.Popen(('cat', 'Utils/include/gambit/Utils/cats.hpp', fname), stdout=sp.PIPE)
   step2 = sp.Popen(('sed', "s/#include/\/\/#include/g"), stdin=step1.stdout, stdout=sp.PIPE)
   step3 = sp.check_output(('gcc', '-xc', '-w', '-E', '-'), stdin=step2.stdout) #-w for no warnings
   step1.wait()
   step2.wait()
   # Gah need to put the include statements back in, we rely on them while checking the hierarchy structure
   return step3 

def get_between(firstline,f,pleft,pright,stripnewlines=True):
   """Extract everything between matching parentheses, removing any newlines found on the way.
      Assumes that the file 'f' has had 'firstline' extracted and now points at the next line.
      Begins extraction from the next pleft found. 
   """
   line = firstline
   openbrace = False
   while openbrace==False:
      opencheck = line.split(pleft)
      if len(opencheck)>1:
         openbrace = True
      if not openbrace:
         line = f.next()
         if line=="": 
             return None # No opening parenthesis found!
         elif stripnewlines:
            line = line.rstrip('\r\n')
   # Found opening parenthesis; begin extracting stuff until closing parenthesis found
   closebrace = False
   line = line.split(pleft)[1] # Start looking after opening parenthesis
   extracted_string = ""
   while closebrace==False:
      closecheck = line.split(pright)
      if len(closecheck)>1:
         closebrace = True
      if not closebrace:
         extracted_string += line
         line = f.next()
         if line=="":
             raise IOError("Opening parenthesis found, but no closing parenthesis before end of file!")
         elif stripnewlines:
            line = line.rstrip('\r\n')
      else:
         extracted_string += line.split(pright)[0]
   return extracted_string, line.split(pright)[1] # Return the latter half of the last line parsed as well, in case more parsing of the same line needs to happen

def get_model_definitions(header):
   #print "Parsing {0}".format(header)
   models = []
   current_MODEL = None
   current_PARENT = None
   current = -1
   fullheader = "{0}/{1}".format(modeldir,header)
   with open(fullheader,'r') as f:
    for line in f:
      line = line.rstrip('\r\n') # remove trailing newline characters
      words = line.split()
      if len(words)>0:
         # Check for MODEL and PARENT macro definitions
         if words[0].lower() == "#define":
            if words[1] == "MODEL":
               current_MODEL = words[2]
            if words[1] == "PARENT":
               current_PARENT = words[2]
         elif words[0].lower() == "#undef":
            if words[1] == "MODEL":
               current_MODEL = None
            if words[1] == "PARENT":
               current_PARENT = None
         # Check for START_MODEL macro
         elif words[0] == "START_MODEL":
            models += [Model(current_MODEL,current_PARENT,header)]
            current += 1 # Move index for active model object
            #print "  Added model {0} with parent {1} to hierarchy".format(current_MODEL,current_PARENT)
         # Check for parameter definitions
         elif words[0].split("(")[0] == "DEFINEPARS":
            parlines, lastline = get_between(line,f,"(",")")
            parwords = parlines.replace(" ","").split(",")
            parwords = [p for p in parwords if p!=""] # Remove empty entries (appear depending on exact comma placement)
            models[current].parameters.update(parwords)
         # Check for "interpret at parent" function declarations
         if words[0].split("(")[0] == "INTERPRET_AS_PARENT_FUNCTION":
            funcname = words[0].replace("("," ").replace(")"," ").split()[1]
            models[current].IAPfunc = funcname
   return models

def expand_MODEL_NAMESPACE(MODEL):
   """Simulate this particular C macro expansion"""  
   return "Gambit::Models::{0}".format(MODEL)

def find_IAPfunc(f,model):
   """Search a source file for an 'interpret as parent' function for a particular model"""
   current_MODEL = None
   model_header_found = False
   IAPfunc_string = None # The source code for the requested IAPfunc, once found.
   varnames = (None, None) # Arguments names used in the IAPfunc, once found
   for line in f:
        line = line.rstrip('\r\n') # remove trailing newline characters
        # Check for the model header include statement (if this is missing, cannot be the right file)
        if not model_header_found:
           tmpline = line.replace(" ","").replace("\"","'")
           if tmpline=="#include'gambit/Models/models/{0}'".format(model.header):
              model_header_found = True
        else:
           # Ok this is at least potentially the right file. Now look for the actual function definition
           words = line.split()
           if len(words)>0:
              # Check for MODEL and PARENT macro definitions
              if words[0].lower() == "#define":
                 if words[1] == "MODEL":
                    current_MODEL = words[2]
              elif words[0] == "void":
                 # Ok this might be the beginning of the definition. Look for the function signature
                 # This could be done in a million ways, but I am just going to assume that the MODEL_NAMESPACE
                 # macro is used to do this.
                 splitline = line.replace("MODEL_NAMESPACE",expand_MODEL_NAMESPACE(current_MODEL)).replace("::"," ").replace("("," ").split()
                 if splitline[1]=="Gambit" and splitline[2]=="Models" and splitline[3]==model.name:
                    # Looks like this is it; now get the variable names used in the function signature
                    varlines, lastline = get_between(line,f,"(",")")
                    print "extracted:", varlines
                    var1, var2 = varlines.replace("&","").split(",")
                    svar1 = var1.split()
                    if svar1[0]=="const" and svar1[1]=="ModelParameters":
                       myP = svar1[2]
                    else:
                       ValueError("Error parsing IAP function! Function signature was not parsed as expected!")
                    svar2 = var2.split()
                    if svar2[0]=="ModelParameters":
                       targetP = svar2[1]
                    else:
                       ValueError("Error parsing IAP function! Function signature was not parsed as expected!")
                    varnames = (myP, targetP)
                    IAPfunc_string, lastline = get_between(lastline,f,"{","}",False) # Get the body of the function definition, without stripping newlines this time
   return IAPfunc_string, varnames

#--- Step 1: Obtain the model hierarchy by parsing the source ---

# Get all the model headers (just runs a part of the model_harvester.py script)
model_headers=set([])
exclude_models=set([])
verbose = False
model_headers.update(retrieve_generic_headers(verbose,modeldir,"model",exclude_models))

# Parse all the headers for model definitions, along with PARENT declarations
models = []
for header in model_headers:
   models += get_model_definitions(header)

#--- Step 2: Parse the "interpret as parent" functions
for root,dirs,files in os.walk(model_source_dir):
   for name in files:
       source = get_expanded_source("{0}/{1}".format(root,name)) # Expand certain macros in the source
       file_like_io = StringIO(source)
       for m in models:
           if not m.IAPfunc_code:
              file_like_io.seek(0)
              fstring, varnames = find_IAPfunc(file_like_io,m)
              if fstring:
                 print "Found IAP func for {0} (func name is {1})".format(m.name,m.IAPfunc)
                 m.IAPfunc_code = (varnames, fstring)

 # Check what was learned
for m in models:
   print "Model: {0}".format(m.name)
   print "  Header: {0}".format(m.header)
   print "  Parent: {0}".format(m.parent)
   print "  Parameters (number={0}): {1}".format(len(m.parameters),sorted(m.parameters))
   print "  IAPfunc: {0}".format(m.IAPfunc)
   if m.IAPfunc:
      if m.IAPfunc_code:
         print "  IAPfunc_code: {0}".format(m.IAPfunc_code[0])
         print "                {0}".format(m.IAPfunc_code[1])
      else:
         print "  Failed to find or parse IAP function code"
             


