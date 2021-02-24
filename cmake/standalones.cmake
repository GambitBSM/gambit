# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake configuration script for standalone
#  programs that use some GAMBIT libraries.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2016
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2020
#
#************************************************

# Add some programs that use the GAMBIT physics libraries but not GAMBIT itself.
add_standalone(ExampleBit_A_standalone SOURCES ExampleBit_A/examples/ExampleBit_A_standalone_example.cpp MODULES ExampleBit_A)
add_standalone(DarkBit_standalone_MSSM SOURCES DarkBit/examples/DarkBit_standalone_MSSM.cpp MODULES DarkBit)
add_standalone(DarkBit_standalone_ScalarSingletDM_Z2 SOURCES DarkBit/examples/DarkBit_standalone_ScalarSingletDM_Z2.cpp MODULES DarkBit)
add_standalone(DarkBit_standalone_WIMP SOURCES DarkBit/examples/DarkBit_standalone_WIMP.cpp MODULES DarkBit)
add_standalone(3bithit SOURCES DecayBit/examples/3bithit.cpp MODULES DecayBit SpecBit PrecisionBit)
add_standalone(FlavBit_standalone SOURCES FlavBit/examples/FlavBit_standalone_example.cpp MODULES FlavBit)
