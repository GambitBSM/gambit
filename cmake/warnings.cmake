# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Cmake configuration script to arrange warning
#  options when compiling GAMBIT.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2014 Sep, Oct, Nov
#
#  \author Andy Buckley
#          (andy.buckley@cern.ch)
#  \date 2016 Feb
#
#************************************************

option(WERROR "WERROR" OFF)

include(CheckCXXCompilerFlag)

macro(set_compiler_warning warning current_flags)
  CHECK_CXX_COMPILER_FLAG("-W${warning}" CXX_SUPPORTS_${warning})
  if (CXX_SUPPORTS_${warning})
    set(${current_flags} "${${current_flags}} -W${warning}")
  endif()
endmacro()
